/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2019 Western Digital Corporation or its affiliates.
 */

#ifndef _ASM_RISCV_FIXMAP_H
#define _ASM_RISCV_FIXMAP_H

#include <lwk/kernel.h>
#include <lwk/sizes.h>
#include <arch/pgtable.h>
#include <arch/page.h>

#ifdef CONFIG_MMU
/*
 * Here we define all the compile-time 'special' virtual addresses.
 * The point is to have a constant address at compile time, but to
 * set the physical address only in the boot process.
 *
 * These 'compile-time allocated' memory buffers are page-sized. Use
 * set_fixmap(idx,phys) to associate physical memory with fixmap indices.
 */
enum fixed_addresses {
	FIX_HOLE,
	FIX_PTE,
	FIX_PMD,
	FIX_PUD,
	FIX_P4D,
	FIX_TEXT_POKE1,
	FIX_TEXT_POKE0,
	FIX_EARLYCON_MEM_BASE,

	__end_of_permanent_fixed_addresses,
	/*
	 * Temporary boot-time mappings, used by early_ioremap(),
	 * before ioremap() is functional.
	 */
#define NR_FIX_BTMAPS		(SZ_256K / PAGE_SIZE)
#define FIX_BTMAPS_SLOTS	7
#define TOTAL_FIX_BTMAPS	(NR_FIX_BTMAPS * FIX_BTMAPS_SLOTS)

	FIX_BTMAP_END = __end_of_permanent_fixed_addresses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAL_FIX_BTMAPS - 1,

	__end_of_fixed_addresses
};

#define FIXMAP_PAGE_CLEAR __pgprot(0)

#define __early_set_fixmap	__set_fixmap

#define __late_set_fixmap	__set_fixmap
#define __late_clear_fixmap(idx) __set_fixmap((idx), 0, FIXMAP_PAGE_CLEAR)

#define set_fixmap(idx, phys) \
		__set_fixmap(idx, phys, PAGE_KERNEL)

extern void __set_fixmap(enum fixed_addresses idx,
			 phys_addr_t phys, pgprot_t prot);

extern void __this_fixmap_does_not_exist(void);

#define __fix_to_virt(x)	(FIXADDR_TOP - ((x) << PAGE_SHIFT))

static __always_inline unsigned long fix_to_virt(const unsigned int idx)
{
	/*
	 * this branch gets completely eliminated after inlining,
	 * except when someone tries to use fixaddr indices in an
	 * illegal way. (such as mixing up address types or using
	 * out-of-range indices).
	 *
	 * If it doesn't get removed, the linker will complain
	 * loudly with a reasonably clear error message..
	 */
	if (idx >= __end_of_fixed_addresses)
		__this_fixmap_does_not_exist();

	return __fix_to_virt(idx);
}

#define clear_fixmap(idx)			\
	__set_fixmap(idx, 0, FIXMAP_PAGE_CLEAR)

//#include <asm-generic/fixmap.h>

#endif /* CONFIG_MMU */
#endif /* _ASM_RISCV_FIXMAP_H */
