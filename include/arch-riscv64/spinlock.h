/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */

#ifndef _ASM_RISCV_SPINLOCK_H
#define _ASM_RISCV_SPINLOCK_H

#include <lwk/kernel.h>
#include <arch/current.h>
#include <arch/fence.h>

/*
 * Simple spin lock operations.  These provide no fairness guarantees.
 */

/* FIXME: Replace this with a ticket lock, like MIPS. */

#define __raw_spin_is_locked(x)	(READ_ONCE((x)->lock) != 0)

static inline void __raw_spin_unlock(raw_spinlock_t *lock)
{
	smp_store_release(&lock->lock, 0);
}

static inline int __raw_spin_trylock(raw_spinlock_t *lock)
{
	int tmp = 1, busy;

	__asm__ __volatile__ (
		"	amoswap.w %0, %2, %1\n"
		RISCV_ACQUIRE_BARRIER
		: "=r" (busy), "+A" (lock->lock)
		: "r" (tmp)
		: "memory");

	return !busy;
}

static inline void __raw_spin_lock(raw_spinlock_t *lock)
{
	while (1) {
		if (__raw_spin_is_locked(lock))
			continue;

		if (__raw_spin_trylock(lock))
			break;
	}
}

/***********************************************************/

static inline void __raw_read_lock(raw_rwlock_t *lock)
{
	int tmp;

	__asm__ __volatile__(
		"1:	lr.w	%1, %0\n"
		"	bltz	%1, 1b\n"
		"	addi	%1, %1, 1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		: "+A" (lock->lock), "=&r" (tmp)
		:: "memory");
}

static inline void __raw_write_lock(raw_rwlock_t *lock)
{
	int tmp;

	__asm__ __volatile__(
		"1:	lr.w	%1, %0\n"
		"	bnez	%1, 1b\n"
		"	li	%1, -1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		: "+A" (lock->lock), "=&r" (tmp)
		:: "memory");
}

static inline int __raw_read_trylock(raw_rwlock_t *lock)
{
	int busy;

	__asm__ __volatile__(
		"1:	lr.w	%1, %0\n"
		"	bltz	%1, 1f\n"
		"	addi	%1, %1, 1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		"1:\n"
		: "+A" (lock->lock), "=&r" (busy)
		:: "memory");

	return !busy;
}

static inline int __raw_write_trylock(raw_rwlock_t *lock)
{
	int busy;

	__asm__ __volatile__(
		"1:	lr.w	%1, %0\n"
		"	bnez	%1, 1f\n"
		"	li	%1, -1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		"1:\n"
		: "+A" (lock->lock), "=&r" (busy)
		:: "memory");

	return !busy;
}

static inline void __raw_read_unlock(raw_rwlock_t *lock)
{
	__asm__ __volatile__(
		RISCV_RELEASE_BARRIER
		"	amoadd.w x0, %1, %0\n"
		: "+A" (lock->lock)
		: "r" (-1)
		: "memory");
}

static inline void __raw_write_unlock(raw_rwlock_t *lock)
{
	smp_store_release(&lock->lock, 0);
}

/* read_can_lock - would read_trylock() succeed? */
#define arch_read_can_lock(x)		((x)->lock < 0x80000000)


#define arch_read_lock(lock)               __raw_read_lock(lock)
#define arch_write_lock(lock)              __raw_write_lock(lock)
#define arch_read_lock_flags(lock, flags)  __raw_read_lock(lock)
#define arch_write_lock_flags(lock, flags) __raw_write_lock(lock)

#define __raw_spin_lock_flags(lock, flags) __raw_spin_lock(lock)

#define arch_spin_relax(lock)	cpu_relax()
#define arch_read_relax(lock)	cpu_relax()
#define arch_write_relax(lock)	cpu_relax()


#endif /* _ASM_RISCV_SPINLOCK_H */
