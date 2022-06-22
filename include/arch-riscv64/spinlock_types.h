/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of California
 */

#ifndef _ASM_RISCV_SPINLOCK_TYPES_H
#define _ASM_RISCV_SPINLOCK_TYPES_H

#ifndef _LWK_SPINLOCK_TYPES_H
# error "please don't include this file directly"
#endif

#ifndef ARM_RAW_SPINLOCK
#define ARM_RAW_SPINLOCK
typedef struct {
	volatile unsigned int lock;
} raw_spinlock_t;
#endif

#define __RAW_SPIN_LOCK_UNLOCKED	{ 0 }

typedef struct {
	volatile unsigned int lock;
} raw_rwlock_t;

#define __RAW_RW_LOCK_UNLOCKED		{ 0 }

#endif /* _ASM_RISCV_SPINLOCK_TYPES_H */
