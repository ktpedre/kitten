/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Based on arm/arm64/include/asm/current.h
 *
 * Copyright (C) 2016 ARM
 * Copyright (C) 2017 SiFive
 */


#ifndef _ASM_RISCV_CURRENT_H
#define _ASM_RISCV_CURRENT_H

#include <arch/bug.h>
#include <lwk/compiler.h>

#ifndef __ASSEMBLY__

struct task_struct;

register struct task_struct *riscv_current_is_tp __asm__("tp");

/* This points to the current task struct */
static __always_inline struct task_struct *get_current(void)
{
	return riscv_current_is_tp;
}

#define current get_current()
#define get_current_via_RSP() get_current()

register unsigned long current_stack_pointer __asm__("sp");

#endif /* __ASSEMBLY__ */

#endif /* _ASM_RISCV_CURRENT_H */
