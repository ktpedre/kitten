/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */

#include <lwk/init.h>
#include <lwk/linkage.h>

#include <arch/task.h>
#include <arch/asm.h>
#include <arch/csr.h>
#include <arch/unistd.h>
#include <arch/thread_info.h>
#include <arch/asm-offsets.h>
#include <arch/errata_list.h>

.set resume_kernel, restore_all

ENTRY(handle_exception)
	/*
	 * If coming from userspace, preserve the user thread pointer and load
	 * the kernel thread pointer.  If we came from the kernel, the scratch
	 * register will contain 0, and we should continue on the current TP.
	 */
	csrrw tp, CSR_SCRATCH, tp
	bnez tp, _save_context

_restore_kernel_tpsp:
	csrr tp, CSR_SCRATCH
	REG_S sp, TASK_THREAD_KERNEL_SP(tp)

_save_context:
	REG_S sp, TASK_THREAD_USER_SP(tp)
	REG_L sp, TASK_THREAD_KERNEL_SP(tp)
	addi sp, sp, -(PT_SIZE_ON_STACK)
	REG_S x1,  PT_RA(sp)
	REG_S x3,  PT_GP(sp)
	REG_S x5,  PT_T0(sp)
	REG_S x6,  PT_T1(sp)
	REG_S x7,  PT_T2(sp)
	REG_S x8,  PT_S0(sp)
	REG_S x9,  PT_S1(sp)
	REG_S x10, PT_A0(sp)
	REG_S x11, PT_A1(sp)
	REG_S x12, PT_A2(sp)
	REG_S x13, PT_A3(sp)
	REG_S x14, PT_A4(sp)
	REG_S x15, PT_A5(sp)
	REG_S x16, PT_A6(sp)
	REG_S x17, PT_A7(sp)
	REG_S x18, PT_S2(sp)
	REG_S x19, PT_S3(sp)
	REG_S x20, PT_S4(sp)
	REG_S x21, PT_S5(sp)
	REG_S x22, PT_S6(sp)
	REG_S x23, PT_S7(sp)
	REG_S x24, PT_S8(sp)
	REG_S x25, PT_S9(sp)
	REG_S x26, PT_S10(sp)
	REG_S x27, PT_S11(sp)
	REG_S x28, PT_T3(sp)
	REG_S x29, PT_T4(sp)
	REG_S x30, PT_T5(sp)
	REG_S x31, PT_T6(sp)

	/*
	 * Disable user-mode memory access as it should only be set in the
	 * actual user copy routines.
	 *
	 * Disable the FPU to detect illegal usage of floating point in kernel
	 * space.
	 */
  li t0, SR_SUM
  csrrs t0, CSR_STATUS, t0
  
	li t0, SR_SUM | SR_FS

	REG_L s0, TASK_THREAD_USER_SP(tp)
	csrrc s1, CSR_STATUS, t0
	csrr s2, CSR_EPC
	csrr s3, CSR_TVAL
	csrr s4, CSR_CAUSE
	csrr s5, CSR_SCRATCH
	REG_S s0, PT_SP(sp)
	REG_S s1, PT_STATUS(sp)
	REG_S s2, PT_EPC(sp)
	REG_S s3, PT_BADADDR(sp)
	REG_S s4, PT_CAUSE(sp)
	REG_S s5, PT_TP(sp)

	/*
	 * Set the scratch register to 0, so that if a recursive exception
	 * occurs, the exception vector knows it came from the kernel
	 */
	csrw CSR_SCRATCH, x0

	/* Load the global pointer */
.option push
.option norelax
	la gp, __global_pointer$
.option pop

//;; #ifdef CONFIG_TRACE_IRQFLAGS
//;; 	call __trace_hardirqs_off
//;; #endif

//;; #ifdef CONFIG_CONTEXT_TRACKING
//;; 	/* If previous state is in user mode, call context_tracking_user_exit. */
//;; 	li   a0, SR_PP
//;; 	and a0, s1, a0
//;; 	bnez a0, skip_context_tracking
//;; 	call context_tracking_user_exit
//;; skip_context_tracking:
//;; #endif

	/*
	 * MSB of cause differentiates between
	 * interrupts and exceptions
	 */
	bge s4, zero, 1f

	la ra, ret_from_exception

	/* Handle interrupts */
	move a0, sp /* pt_regs */
	la a1, handle_irq
	jr a1
1:
	/*
	 * Exceptions run with interrupts enabled or disabled depending on the
	 * state of SR_PIE in m/sstatus.
	 */
	andi t0, s1, SR_PIE
	beqz t0, 1f
	/* kprobes, entered via ebreak, must have interrupts disabled. */
	li t0, EXC_BREAKPOINT
	beq s4, t0, 1f
//;; #ifdef CONFIG_TRACE_IRQFLAGS
//;; 	call __trace_hardirqs_on
//;; #endif
	csrs CSR_STATUS, SR_IE

1:
	la ra, ret_from_exception
	/* Handle syscalls */
	li t0, EXC_SYSCALL
	beq s4, t0, handle_syscall

	/* Handle other exceptions */
	slli t0, s4, RISCV_LGPTR
	la t1, excp_vect_table
	la t2, excp_vect_table_end
	move a0, sp /* pt_regs */
	add t0, t1, t0
	/* Check if exception code lies within bounds */
	bgeu t0, t2, 1f
	REG_L t0, 0(t0)
	jr t0
1:
	tail do_trap_unknown

handle_syscall:
//;; #ifdef CONFIG_RISCV_M_MODE
//;; 	/*
//;; 	 * When running is M-Mode (no MMU config), MPIE does not get set.
//;; 	 * As a result, we need to force enable interrupts here because
//;; 	 * handle_exception did not do set SR_IE as it always sees SR_PIE
//;; 	 * being cleared.
//;; 	 */
//;; 	csrs CSR_STATUS, SR_IE
//;; #endif
//;; #if defined(CONFIG_TRACE_IRQFLAGS) || defined(CONFIG_CONTEXT_TRACKING)
//;; 	/* Recover a0 - a7 for system calls */
//;; 	REG_L a0, PT_A0(sp)
//;; 	REG_L a1, PT_A1(sp)
//;; 	REG_L a2, PT_A2(sp)
//;; 	REG_L a3, PT_A3(sp)
//;; 	REG_L a4, PT_A4(sp)
//;; 	REG_L a5, PT_A5(sp)
//;; 	REG_L a6, PT_A6(sp)
//;; 	REG_L a7, PT_A7(sp)
//;; #endif

  /* Allow the kernel to access user memory */
  li t0, SR_SUM
  csrrs t0, CSR_STATUS, t0
	 /* save the initial A0 value (needed in signal handlers) */
	REG_S a0, PT_ORIG_A0(sp)
	/*
	 * Advance SEPC to avoid executing the original
	 * scall instruction on sret
	 */
	addi s2, s2, 0x4
	REG_S s2, PT_EPC(sp)
	/* Trace syscalls, but only if requested by the user. */
	/*REG_L t0, TASK_THREAD_FLAGS(tp)
	andi t0, t0, _TIF_SYSCALL_WORK
	bnez t0, handle_syscall_trace_enter*/
check_syscall_nr:
	/* Check to make sure we don't jump to a bogus syscall number. */
	li t0, __NR_syscalls
	la s0, syscall_not_implemented
	/*
	 * Syscall number held in a7.
	 * If syscall number is above allowed value, redirect to ni_syscall.
	 */
	bgeu a7, t0, 3f
//;; #ifdef CONFIG_COMPAT
//;; 	REG_L s0, PT_STATUS(sp)
//;; 	srli s0, s0, SR_UXL_SHIFT
//;; 	andi s0, s0, (SR_UXL >> SR_UXL_SHIFT)
//;; 	li t0, (SR_UXL_32 >> SR_UXL_SHIFT)
//;; 	sub t0, s0, t0
//;; 	bnez t0, 1f

//;; 	/* Call compat_syscall */
//;; 	la s0, compat_sys_call_table
//;; 	j 2f
//;; 1:
//;; #endif
	/* Call syscall */
	la s0, sys_call_table
2:
	slli t0, a7, RISCV_LGPTR
	add s0, s0, t0
	REG_L s0, 0(s0)
3:
	jalr s0

ret_from_syscall:
	/* Set user a0 to kernel a0 */
	REG_S a0, PT_A0(sp)
	/*
	 * We didn't execute the actual syscall.
	 * Seccomp already set return value for the current task pt_regs.
	 * (If it was configured with SECCOMP_RET_ERRNO/TRACE)
	 */
ret_from_syscall_rejected:
//;; #ifdef CONFIG_DEBUG_RSEQ
//;; 	move a0, sp
//;; 	call rseq_syscall
//;; #endif
	/* Trace syscalls, but only if requested by the user. */
	REG_L t0, TASK_THREAD_FLAGS(tp)
	andi t0, t0, _TIF_SYSCALL_WORK
	bnez t0, handle_syscall_trace_exit

ret_from_exception:
	REG_L s0, PT_STATUS(sp)
	csrc CSR_STATUS, SR_IE
//;; #ifdef CONFIG_TRACE_IRQFLAGS
//;; 	call __trace_hardirqs_off
//;; #endif
//;; #ifdef CONFIG_RISCV_M_MODE
//;; 	/* the MPP value is too large to be used as an immediate arg for addi */
//;; 	li t0, SR_MPP
//;; 	and s0, s0, t0
//;; #else
	andi s0, s0, SR_SPP
//;; #endif
	bnez s0, resume_kernel

resume_userspace:
	/* Interrupts must be disabled here so flags are checked atomically */
	REG_L s0, TASK_THREAD_FLAGS(tp) /* current_thread_info->flags */
	andi s1, s0, _TIF_WORK_MASK
	bnez s1, work_pending

//;; #ifdef CONFIG_CONTEXT_TRACKING
//;; 	call context_tracking_user_enter
//;; #endif

	/* Save unwound kernel stack pointer in thread_info */
	addi s0, sp, PT_SIZE_ON_STACK
	REG_S s0, TASK_THREAD_KERNEL_SP(tp)

	/*
	 * Save TP into the scratch register , so we can find the kernel data
	 * structures again.
	 */
	csrw CSR_SCRATCH, tp

restore_all:
//;; #ifdef CONFIG_TRACE_IRQFLAGS
//;; 	REG_L s1, PT_STATUS(sp)
//;; 	andi t0, s1, SR_PIE
//;; 	beqz t0, 1f
//;; 	call __trace_hardirqs_on
//;; 	j 2f
//;; 1:
//;; 	call __trace_hardirqs_off
//;; 2:
//;; #endif
	REG_L a0, PT_STATUS(sp)
	/*
	 * The current load reservation is effectively part of the processor's
	 * state, in the sense that load reservations cannot be shared between
	 * different hart contexts.  We can't actually save and restore a load
	 * reservation, so instead here we clear any existing reservation --
	 * it's always legal for implementations to clear load reservations at
	 * any point (as long as the forward progress guarantee is kept, but
	 * we'll ignore that here).
	 *
	 * Dangling load reservations can be the result of taking a trap in the
	 * middle of an LR/SC sequence, but can also be the result of a taken
	 * forward branch around an SC -- which is how we implement CAS.  As a
	 * result we need to clear reservations between the last CAS and the
	 * jump back to the new context.  While it is unlikely the store
	 * completes, implementations are allowed to expand reservations to be
	 * arbitrarily large.
	 */
	REG_L  a2, PT_EPC(sp)
	REG_SC x0, a2, PT_EPC(sp)

	csrw CSR_STATUS, a0
	csrw CSR_EPC, a2

	REG_L x1,  PT_RA(sp)
	REG_L x3,  PT_GP(sp)
	REG_L x4,  PT_TP(sp)
	REG_L x5,  PT_T0(sp)
	REG_L x6,  PT_T1(sp)
	REG_L x7,  PT_T2(sp)
	REG_L x8,  PT_S0(sp)
	REG_L x9,  PT_S1(sp)
	REG_L x10, PT_A0(sp)
	REG_L x11, PT_A1(sp)
	REG_L x12, PT_A2(sp)
	REG_L x13, PT_A3(sp)
	REG_L x14, PT_A4(sp)
	REG_L x15, PT_A5(sp)
	REG_L x16, PT_A6(sp)
	REG_L x17, PT_A7(sp)
	REG_L x18, PT_S2(sp)
	REG_L x19, PT_S3(sp)
	REG_L x20, PT_S4(sp)
	REG_L x21, PT_S5(sp)
	REG_L x22, PT_S6(sp)
	REG_L x23, PT_S7(sp)
	REG_L x24, PT_S8(sp)
	REG_L x25, PT_S9(sp)
	REG_L x26, PT_S10(sp)
	REG_L x27, PT_S11(sp)
	REG_L x28, PT_T3(sp)
	REG_L x29, PT_T4(sp)
	REG_L x30, PT_T5(sp)
	REG_L x31, PT_T6(sp)

	REG_L x2,  PT_SP(sp)

//;; #ifdef CONFIG_RISCV_M_MODE
//;; 	mret
//;; #else
	sret
//;; #endif

work_pending:
	/* Enter slow path for supplementary processing */
	la ra, ret_from_exception
	andi s1, s0, _TIF_NEED_RESCHED
	bnez s1, work_resched
work_notifysig:
	/* Handle pending signals and notify-resume requests */
	csrs CSR_STATUS, SR_IE /* Enable interrupts for do_notify_resume() */
	move a0, sp /* pt_regs */
	move a1, s0 /* current_thread_info->flags */
	tail do_notify_resume
work_resched:
	tail schedule

/* Slow paths for ptrace. */
handle_syscall_trace_enter:
	move a0, sp
	/* call do_syscall_trace_enter */
	move t0, a0
	REG_L a0, PT_A0(sp)
	REG_L a1, PT_A1(sp)
	REG_L a2, PT_A2(sp)
	REG_L a3, PT_A3(sp)
	REG_L a4, PT_A4(sp)
	REG_L a5, PT_A5(sp)
	REG_L a6, PT_A6(sp)
	REG_L a7, PT_A7(sp)
	bnez t0, ret_from_syscall_rejected
	j check_syscall_nr
handle_syscall_trace_exit:
	move a0, sp
	/* call do_syscall_trace_exit */
	j ret_from_exception

END(handle_exception)

ENTRY(ret_from_fork)
	la ra, ret_from_exception
	tail schedule_new_task_tail
ENDPROC(ret_from_fork)

ENTRY(ret_from_kernel_thread)
	call schedule_new_task_tail
	/* Call fn(arg) */
	la ra, ret_from_exception
	move a0, s1
	jr s0
ENDPROC(ret_from_kernel_thread)

/*
 * Integer register context switch
 * The callee-saved registers must be saved and restored.
 *
 *   a0: previous task_struct (must be preserved across the switch)
 *   a1: next task_struct
 *
 * The value of a0 and a1 must be preserved by this function, as that's how
 * arguments are passed to schedule_tail.
 */

ENTRY(arch_context_switch)
	/* Save context into prev->thread */
	li    a4,  TASK_THREAD_RA
	add   a3, a0, a4
	add   a4, a1, a4
	REG_S sp,  TASK_THREAD_KERN_SP(a0)
	REG_S ra,  TASK_THREAD_RA_RA(a3)
	REG_S s0,  TASK_THREAD_S0_RA(a3)
	REG_S s1,  TASK_THREAD_S1_RA(a3)
	REG_S s2,  TASK_THREAD_S2_RA(a3)
	REG_S s3,  TASK_THREAD_S3_RA(a3)
	REG_S s4,  TASK_THREAD_S4_RA(a3)
	REG_S s5,  TASK_THREAD_S5_RA(a3)
	REG_S s6,  TASK_THREAD_S6_RA(a3)
	REG_S s7,  TASK_THREAD_S7_RA(a3)
	REG_S s8,  TASK_THREAD_S8_RA(a3)
	REG_S s9,  TASK_THREAD_S9_RA(a3)
	REG_S s10, TASK_THREAD_S10_RA(a3)
	REG_S s11, TASK_THREAD_S11_RA(a3)

	REG_L sp,  TASK_THREAD_KERN_SP(a1)
  REG_L ra,  TASK_THREAD_RA_RA(a4)
	REG_L s0,  TASK_THREAD_S0_RA(a4)
	REG_L s1,  TASK_THREAD_S1_RA(a4)
	REG_L s2,  TASK_THREAD_S2_RA(a4)
	REG_L s3,  TASK_THREAD_S3_RA(a4)
	REG_L s4,  TASK_THREAD_S4_RA(a4)
	REG_L s5,  TASK_THREAD_S5_RA(a4)
	REG_L s6,  TASK_THREAD_S6_RA(a4)
	REG_L s7,  TASK_THREAD_S7_RA(a4)
	REG_L s8,  TASK_THREAD_S8_RA(a4)
	REG_L s9,  TASK_THREAD_S9_RA(a4)
	REG_L s10, TASK_THREAD_S10_RA(a4)
	REG_L s11, TASK_THREAD_S11_RA(a4)
  /* NMG Need to call some __arch_context_switch?
  ARM64 code:
    - update tls
    - update the PDA
    - update FPU stuff
  */
  /* call __arch_context_switch */

	/* The offset of thread_info in task_struct is zero. */
  move tp, a1

	ret
//ENDPROC(__switch_to)
ENDPROC(arch_context_switch)
  
//ENTRY(__switch_to)
/* ENTRY(arch_context_switch) */
/* 	/\* Save context into prev->thread *\/ */
/* 	li    a4,  TASK_THREAD_RA */
/* 	add   a3, a0, a4 */
/* 	add   a4, a1, a4 */
/* 	REG_S ra,  TASK_THREAD_RA_RA(a3) */
/* 	REG_S sp,  TASK_THREAD_USER_SP_RA(a3) */
/* 	REG_S s0,  TASK_THREAD_S0_RA(a3) */
/* 	REG_S s1,  TASK_THREAD_S1_RA(a3) */
/* 	REG_S s2,  TASK_THREAD_S2_RA(a3) */
/* 	REG_S s3,  TASK_THREAD_S3_RA(a3) */
/* 	REG_S s4,  TASK_THREAD_S4_RA(a3) */
/* 	REG_S s5,  TASK_THREAD_S5_RA(a3) */
/* 	REG_S s6,  TASK_THREAD_S6_RA(a3) */
/* 	REG_S s7,  TASK_THREAD_S7_RA(a3) */
/* 	REG_S s8,  TASK_THREAD_S8_RA(a3) */
/* 	REG_S s9,  TASK_THREAD_S9_RA(a3) */
/* 	REG_S s10, TASK_THREAD_S10_RA(a3) */
/* 	REG_S s11, TASK_THREAD_S11_RA(a3) */

/*   /\* NMG Need to call some __arch_context_switch? */
/*   ARM64 code: */
/*     - update tls */
/*     - update the PDA */
/*     - update FPU stuff */
/*   *\/ */
/*   /\* call __arch_context_switch *\/ */

/*   /\* Check if a new task. Otherwise, jump straight to the end of the routine *\/ */
/*   REG_L t0, TASK_THREAD_FLAGS(a1) */
/*   andi t0, t0, TF_NEW_TASK_MASK */
/*   beqz t0, 1f */
/*   move s1, a1 */
/*   move s2, a4 */

/* kickstart_new_task: */
/*   jal ra, schedule_new_task_tail */

/*   move a1, s1 */
/*   move a4, s2 */

/* 	/\* The offset of thread_info in task_struct is zero. *\/ */
/*   move tp, a1 */

/*   REG_L a3, TASK_THREAD_KERNEL_SP0(a1) */
/*   addi a3, a3, -PT_SIZE */
/*   /\*REG_L x1,  PT_RA(sp)*\/ */
/* 	REG_L gp, PT_GP(a3) */
/* /\*	REG_L tp, PT_TP(a3)*\/ */
/* 	REG_L t0, PT_T0(a3) */
/* 	REG_L t1, PT_T1(a3) */
/* 	REG_L t2, PT_T2(a3) */
/* 	REG_L s0, PT_S0(a3) */
/* 	REG_L s1, PT_S1(a3) */
/* 	REG_L a0, PT_A0(a3) */
/* 	REG_L a1, PT_A1(a3) */
/* 	REG_L a2, PT_A2(a3) */
/* 	REG_L a5, PT_A5(a3) */
/* 	REG_L a6, PT_A6(a3) */
/* 	REG_L a7, PT_A7(a3) */
/* 	REG_L s2, PT_S2(a3) */
/* 	REG_L s3, PT_S3(a3) */
/* 	REG_L s4, PT_S4(a3) */
/* 	REG_L s5, PT_S5(a3) */
/* 	REG_L s6, PT_S6(a3) */
/* 	REG_L s7, PT_S7(a3) */
/* 	REG_L s8, PT_S8(a3) */
/* 	REG_L s9, PT_S9(a3) */
/* 	REG_L s10, PT_S10(a3) */
/* 	REG_L s11, PT_S11(a3) */
/* 	REG_L t3, PT_T3(a3) */
/* 	REG_L t4, PT_T4(a3) */
/* 	REG_L t5, PT_T5(a3) */
/* 	REG_L t6, PT_T6(a3) */

/* 	/\*REG_L sp,  PT_SP(sp)*\/ */
/* 1: */

/* 	/\* Restore context from next->thread *\/ */
/* 	REG_L ra,  TASK_THREAD_RA_RA(a4) */
/* 	REG_L s0,  TASK_THREAD_S0_RA(a4) */
/* 	REG_L s1,  TASK_THREAD_S1_RA(a4) */
/* 	REG_L s2,  TASK_THREAD_S2_RA(a4) */
/* 	REG_L s3,  TASK_THREAD_S3_RA(a4) */
/* 	REG_L s4,  TASK_THREAD_S4_RA(a4) */
/* 	REG_L s5,  TASK_THREAD_S5_RA(a4) */
/* 	REG_L s6,  TASK_THREAD_S6_RA(a4) */
/* 	REG_L s7,  TASK_THREAD_S7_RA(a4) */
/* 	REG_L s8,  TASK_THREAD_S8_RA(a4) */
/* 	REG_L s9,  TASK_THREAD_S9_RA(a4) */
/* 	REG_L s10, TASK_THREAD_S10_RA(a4) */
/* 	REG_L s11, TASK_THREAD_S11_RA(a4) */
/*   REG_L sp,  PT_SP(a3) */

/*   REG_L a4, PT_A4(a3) */
/*   REG_L a3, PT_A3(a3) */

/* 	ret */
/* //ENDPROC(__switch_to) */
/* ENDPROC(arch_context_switch) */

#ifndef CONFIG_MMU
#define do_page_fault do_trap_unknown
#endif

	.section ".rodata"
	.align LGREG
	/* Exception vector table */
ENTRY(excp_vect_table)
	RISCV_PTR do_trap_insn_misaligned
	ALT_INSN_FAULT(RISCV_PTR do_trap_insn_fault)
	RISCV_PTR do_trap_insn_illegal
	RISCV_PTR do_trap_break
	RISCV_PTR do_trap_load_misaligned
	RISCV_PTR do_trap_load_fault
	RISCV_PTR do_trap_store_misaligned
	RISCV_PTR do_trap_store_fault
	RISCV_PTR do_trap_ecall_u /* system call, gets intercepted */
	RISCV_PTR do_trap_ecall_s
	RISCV_PTR do_trap_unknown
	RISCV_PTR do_trap_ecall_m
	/* instruciton page fault */
	ALT_PAGE_FAULT(RISCV_PTR do_page_fault)
	RISCV_PTR do_page_fault   /* load page fault */
	RISCV_PTR do_trap_unknown
	RISCV_PTR do_page_fault   /* store page fault */
excp_vect_table_end:
END(excp_vect_table)

#ifndef CONFIG_MMU
ENTRY(__user_rt_sigreturn)
	li a7, __NR_rt_sigreturn
	scall
END(__user_rt_sigreturn)
#endif


	/* glibc is going to call the clone sys call with these params
	 * a0:flags, a1:newsp, a2:parenttidptr, a3:newtls, a4:childtid.
	 *
	 * We need the args like this:
	 *   a0:flags, a1:newsp, a2:parenttid, a3:childtid, a4:parentregs
	 *
	 */
ENTRY(asm_sys_clone)
	move a3, a4
	move a4, sp
	j    sys_clone
END(asm_sys_clone)
