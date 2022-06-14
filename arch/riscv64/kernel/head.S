/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 *
 * 2022: Adapted for use with Kitten LWK by Nick Gordon <nmgordo@sandia.gov>
 */

#include <lwk/linkage.h>
#include <lwk/init.h>

#include <arch/asm-offsets.h>
#include <arch/asm.h>

#include <arch/thread_info.h>
#include <arch/page.h>
#include <arch/pgtable.h>
#include <arch/csr.h>
#include <arch/cpu_ops_sbi.h>
//#include <arch/hwcap.h>
#include <arch/image.h>
//#include <arch/xip_fixup.h>
#include "efi-header.S"

//__HEAD
//ENTRY(_start)
	.text
	.section .bootstrap.text

  /*
	 * Image header expected by Linux boot-loaders. The image header data
	 * structure is described in asm/image.h.
	 * Do not modify it without modifying the structure and all bootloaders
	 * that expects this header format!!
	 */
#ifdef CONFIG_EFI
	/*
	 * This instruction decodes to "MZ" ASCII required by UEFI.
	 */
	c.li s4,-13
	j _start_kernel
#else
	/* jump to start kernel */
	j _start_kernel
	/* reserved */
	.word 0
#endif
	.balign 8
#if __riscv_xlen == 64
	/* Image load offset(2MB) from start of RAM */
	.dword 0x200000
#else
	/* Image load offset(4MB) from start of RAM */
	.dword 0x400000
#endif
	/* Effective size of kernel image */
	.dword _end - _start
	.dword __HEAD_FLAGS
	.word RISCV_HEADER_VERSION
	.word 0
	.dword 0
	.ascii RISCV_IMAGE_MAGIC
	.balign 4
	.ascii RISCV_IMAGE_MAGIC2
#ifdef CONFIG_EFI
	.word pe_head_start - _start
pe_head_start:

	__EFI_PE_HEADER
#else
	.word 0
#endif

.align 2
;; #ifdef CONFIG_MMU
	.global relocate_enable_mmu
relocate_enable_mmu:
	/* Relocate return address */
	la a1, kernel_map
	REG_L a1, KERNEL_MAP_VIRT_ADDR(a1)
	la a2, _start
	sub a1, a1, a2
	add ra, ra, a1

	/* Point stvec to virtual address of intruction after satp write */
	la a2, 1f
	add a2, a2, a1
	csrw CSR_TVEC, a2

	/* Compute satp for kernel page tables, but don't load it yet */
	srl a2, a0, PAGE_SHIFT
	la a1, satp_mode
	REG_L a1, 0(a1)
	or a2, a2, a1

	/*
	 * Load trampoline page directory, which will cause us to trap to
	 * stvec if VA != PA, or simply fall through if VA == PA.  We need a
	 * full fence here because setup_vm() just wrote these PTEs and we need
	 * to ensure the new translations are in use.
	 */
	la a0, trampoline_pg_dir
	srl a0, a0, PAGE_SHIFT
	or a0, a0, a1
	sfence.vma
	csrw CSR_SATP, a0
.align 2
1:
	/* Set trap vector to spin forever to help debug */
	la a0, .Lsecondary_park
	csrw CSR_TVEC, a0

	/* Reload the global pointer */
.option push
.option norelax
	la gp, __global_pointer$
.option pop

	/*
	 * Switch to kernel page tables.  A full fence is necessary in order to
	 * avoid using the trampoline translations, which are only correct for
	 * the first superpage.  Fetching the fence is guaranteed to work
	 * because that first superpage is translated the same way.
	 */

	csrw CSR_SATP, a2
	sfence.vma

	ret
;; #endif /* CONFIG_MMU */
#ifdef CONFIG_SMP
	.global secondary_start_sbi
secondary_start_sbi:
	/* Mask all interrupts */
	csrw CSR_IE, zero
	csrw CSR_IP, zero

	/* Load the global pointer */
	.option push
	.option norelax
		la gp, __global_pointer$
	.option pop

	/*
	 * Disable FPU to detect illegal usage of
	 * floating point in kernel space
	 */
	li t0, SR_FS
	csrc CSR_STATUS, t0

	/* Set trap vector to spin forever to help debug */
	la a3, .Lsecondary_park
	csrw CSR_TVEC, a3

	/* a0 contains the hartid & a1 contains boot data */
	li a2, SBI_HART_BOOT_TASK_PTR_OFFSET
	add a2, a2, a1
	REG_L tp, (a2)
	li a3, SBI_HART_BOOT_STACK_PTR_OFFSET
	add a3, a3, a1
	REG_L sp, (a3)

.Lsecondary_start_common:

;; #ifdef CONFIG_MMU
	/* Enable virtual memory and relocate to virtual address */
	la a0, swapper_pg_dir
	call relocate_enable_mmu
;; #endif
	call setup_trap_vector
	tail smp_callin
#endif /* CONFIG_SMP */

.align 2
setup_trap_vector:
	/* Set trap vector to exception handler */
	la a0, handle_exception
	csrw CSR_TVEC, a0

	/*
	 * Set sup0 scratch register to 0, indicating to exception vector that
	 * we are presently executing in kernel.
	 */
	csrw CSR_SCRATCH, zero
	ret

.align 2
.Lsecondary_park:
	/* We lack SMP support or have too many harts, so park this hart */
	wfi
	j .Lsecondary_park

//END(_start)

ENTRY(_start_kernel)
	/* Mask all interrupts */
	csrw CSR_IE, zero
	csrw CSR_IP, zero

	/* Load the global pointer */
.option push
.option norelax
	la gp, __global_pointer$
.option pop

	/*
	 * Disable FPU to detect illegal usage of
	 * floating point in kernel space
	 */
	li t0, SR_FS
	csrc CSR_STATUS, t0

	/* Clear BSS for flat non-ELF images */
	la a3, __bss_start
	la a4, __bss_stop
	ble a4, a3, clear_bss_done
clear_bss:
	REG_S zero, (a3)
	add a3, a3, RISCV_SZPTR
	blt a3, a4, clear_bss
clear_bss_done:
	/* Save hart ID and DTB physical address */
	mv s0, a0
	mv s1, a1

	la a2, boot_cpu_hartid
	REG_S a0, (a2)

	/* Initialize page table and relocate to virtual addresses */
	la sp, bootstrap_task_union + TASK_SIZE // -16 NMG:??? //init_thread_union + THREAD_SIZE
	mv a0, s1
	call setup_vm
;; #ifdef CONFIG_MMU
	la a0, early_pg_dir
	call relocate_enable_mmu
;; #endif /* CONFIG_MMU */

	call setup_trap_vector
	/* Restore C environment */
	la tp, init_task
	la sp, bootstrap_task_union + TASK_SIZE

	/* Start the kernel */
	call soc_early_init
	tail start_kernel

END(_start_kernel)
