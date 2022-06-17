/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Copyright (C) 2012 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */

#ifndef _ASM_RISCV_ATOMIC_H
#define _ASM_RISCV_ATOMIC_H

#include <arch/cmpxchg.h>
#include <arch/barrier.h>

#ifndef __ASSEMBLY__

typedef struct {
	int counter;
} atomic_t;

typedef struct {
	s64 counter;
} atomic64_t;

#define __atomic_acquire_fence()					\
	__asm__ __volatile__(RISCV_ACQUIRE_BARRIER "" ::: "memory")

#define __atomic_release_fence()					\
	__asm__ __volatile__(RISCV_RELEASE_BARRIER "" ::: "memory");

static __always_inline int atomic_read(const atomic_t *v)
{
	return READ_ONCE(v->counter);
}
static __always_inline void atomic_set(atomic_t *v, int i)
{
	WRITE_ONCE(v->counter, i);
}

#define ATOMIC64_INIT(i) { (i) }
static __always_inline s64 atomic64_read(const atomic64_t *v)
{
	return READ_ONCE(v->counter);
}
static __always_inline void atomic64_set(atomic64_t *v, s64 i)
{
	WRITE_ONCE(v->counter, i);
}

/*
 * First, the atomic ops that have no ordering constraints and therefor don't
 * have the AQ or RL bits set.  These don't return anything, so there's only
 * one version to worry about.
 */
#define ATOMIC_OP(op, asm_op, I, asm_type, c_type, prefix)		\
static __always_inline							\
void atomic##prefix##_##op(c_type i, atomic##prefix##_t *v)	\
{									\
	__asm__ __volatile__ (						\
		"	amo" #asm_op "." #asm_type " zero, %1, %0"	\
		: "+A" (v->counter)					\
		: "r" (I)						\
		: "memory");						\
}									\

#define ATOMIC_OPS(op, asm_op, I)					\
        ATOMIC_OP (op, asm_op, I, w, int,   )				\
        ATOMIC_OP (op, asm_op, I, d, s64, 64)

ATOMIC_OPS(add, add,  i)
ATOMIC_OPS(sub, add, -i)
ATOMIC_OPS(and, and,  i)
ATOMIC_OPS( or,  or,  i)
ATOMIC_OPS(xor, xor,  i)

#undef ATOMIC_OP
#undef ATOMIC_OPS

/*
 * Atomic ops that have ordered, relaxed, acquire, and release variants.
 * There's two flavors of these: the arithmatic ops have both fetch and return
 * versions, while the logical ops only have fetch versions.
 */
#define ATOMIC_FETCH_OP(op, asm_op, I, asm_type, c_type, prefix)	\
static __always_inline							\
c_type atomic##prefix##_fetch_##op##_relaxed(c_type i,		\
					     atomic##prefix##_t *v)	\
{									\
	register c_type ret;						\
	__asm__ __volatile__ (						\
		"	amo" #asm_op "." #asm_type " %1, %2, %0"	\
		: "+A" (v->counter), "=r" (ret)				\
		: "r" (I)						\
		: "memory");						\
	return ret;							\
}									\
static __always_inline							\
c_type atomic##prefix##_fetch_##op(c_type i, atomic##prefix##_t *v)	\
{									\
	register c_type ret;						\
	__asm__ __volatile__ (						\
		"	amo" #asm_op "." #asm_type ".aqrl  %1, %2, %0"	\
		: "+A" (v->counter), "=r" (ret)				\
		: "r" (I)						\
		: "memory");						\
	return ret;							\
}

#define ATOMIC_OP_RETURN(op, asm_op, c_op, I, asm_type, c_type, prefix)	\
static __always_inline							\
c_type atomic##prefix##_##op##_return_relaxed(c_type i,		\
					      atomic##prefix##_t *v)	\
{									\
        return atomic##prefix##_fetch_##op##_relaxed(i, v) c_op I;	\
}									\
static __always_inline							\
c_type atomic##prefix##_##op##_return(c_type i, atomic##prefix##_t *v)	\
{									\
        return atomic##prefix##_fetch_##op(i, v) c_op I;		\
}

#define ATOMIC_OPS(op, asm_op, c_op, I)					\
        ATOMIC_FETCH_OP( op, asm_op,       I, w, int,   )		\
        ATOMIC_OP_RETURN(op, asm_op, c_op, I, w, int,   )		\
        ATOMIC_FETCH_OP( op, asm_op,       I, d, s64, 64)		\
        ATOMIC_OP_RETURN(op, asm_op, c_op, I, d, s64, 64)

ATOMIC_OPS(add, add, +,  i)
ATOMIC_OPS(sub, add, +, -i)

#define atomic_add_return_relaxed	atomic_add_return_relaxed
#define atomic_sub_return_relaxed	atomic_sub_return_relaxed
#define atomic_add_return		atomic_add_return
#define atomic_sub_return		atomic_sub_return

#define atomic_fetch_add_relaxed	atomic_fetch_add_relaxed
#define atomic_fetch_sub_relaxed	atomic_fetch_sub_relaxed
#define atomic_fetch_add		atomic_fetch_add
#define atomic_fetch_sub		atomic_fetch_sub

#define atomic64_add_return_relaxed	atomic64_add_return_relaxed
#define atomic64_sub_return_relaxed	atomic64_sub_return_relaxed
#define atomic64_add_return		atomic64_add_return
#define atomic64_sub_return		atomic64_sub_return

#define atomic64_fetch_add_relaxed	atomic64_fetch_add_relaxed
#define atomic64_fetch_sub_relaxed	atomic64_fetch_sub_relaxed
#define atomic64_fetch_add		atomic64_fetch_add
#define atomic64_fetch_sub		atomic64_fetch_sub

#undef ATOMIC_OPS

#define ATOMIC_OPS(op, asm_op, I)					\
        ATOMIC_FETCH_OP(op, asm_op, I, w, int,   )			\
        ATOMIC_FETCH_OP(op, asm_op, I, d, s64, 64)

ATOMIC_OPS(and, and, i)
ATOMIC_OPS( or,  or, i)
ATOMIC_OPS(xor, xor, i)

#define atomic_fetch_and_relaxed	atomic_fetch_and_relaxed
#define atomic_fetch_or_relaxed	atomic_fetch_or_relaxed
#define atomic_fetch_xor_relaxed	atomic_fetch_xor_relaxed
#define atomic_fetch_and		atomic_fetch_and
#define atomic_fetch_or		atomic_fetch_or
#define atomic_fetch_xor		atomic_fetch_xor

#define atomic64_fetch_and_relaxed	atomic64_fetch_and_relaxed
#define atomic64_fetch_or_relaxed	atomic64_fetch_or_relaxed
#define atomic64_fetch_xor_relaxed	atomic64_fetch_xor_relaxed
#define atomic64_fetch_and		atomic64_fetch_and
#define atomic64_fetch_or		atomic64_fetch_or
#define atomic64_fetch_xor		atomic64_fetch_xor

#undef ATOMIC_OPS

#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_RETURN

/* This is required to provide a full barrier on success. */
static __always_inline int atomic_fetch_add_unless(atomic_t *v, int a, int u)
{
       int prev, rc;

	__asm__ __volatile__ (
		"0:	lr.w     %[p],  %[c]\n"
		"	beq      %[p],  %[u], 1f\n"
		"	add      %[rc], %[p], %[a]\n"
		"	sc.w.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		: [a]"r" (a), [u]"r" (u)
		: "memory");
	return prev;
}
#define atomic_fetch_add_unless atomic_fetch_add_unless

static __always_inline s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u)
{
       s64 prev;
       long rc;

	__asm__ __volatile__ (
		"0:	lr.d     %[p],  %[c]\n"
		"	beq      %[p],  %[u], 1f\n"
		"	add      %[rc], %[p], %[a]\n"
		"	sc.d.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		: [a]"r" (a), [u]"r" (u)
		: "memory");
	return prev;
}
#define atomic64_fetch_add_unless atomic64_fetch_add_unless

/*
 * atomic_{cmp,}xchg is required to have exactly the same ordering semantics as
 * {cmp,}xchg and the operations that return, so they need a full barrier.
 */
#define ATOMIC_OP(c_t, prefix, size)					\
static __always_inline							\
c_t atomic##prefix##_xchg_relaxed(atomic##prefix##_t *v, c_t n)	\
{									\
	return __xchg_relaxed(&(v->counter), n, size);			\
}									\
static __always_inline							\
c_t atomic##prefix##_xchg_acquire(atomic##prefix##_t *v, c_t n)	\
{									\
	return __xchg_acquire(&(v->counter), n, size);			\
}									\
static __always_inline							\
c_t atomic##prefix##_xchg_release(atomic##prefix##_t *v, c_t n)	\
{									\
	return __xchg_release(&(v->counter), n, size);			\
}									\
static __always_inline							\
c_t atomic##prefix##_xchg(atomic##prefix##_t *v, c_t n)		\
{									\
	return __xchg(&(v->counter), n, size);				\
}									\
static __always_inline							\
c_t atomic##prefix##_cmpxchg_relaxed(atomic##prefix##_t *v,	\
				     c_t o, c_t n)			\
{									\
	return __cmpxchg_relaxed(&(v->counter), o, n, size);		\
}									\
static __always_inline							\
c_t atomic##prefix##_cmpxchg_acquire(atomic##prefix##_t *v,	\
				     c_t o, c_t n)			\
{									\
	return __cmpxchg_acquire(&(v->counter), o, n, size);		\
}									\
static __always_inline							\
c_t atomic##prefix##_cmpxchg_release(atomic##prefix##_t *v,	\
				     c_t o, c_t n)			\
{									\
	return __cmpxchg_release(&(v->counter), o, n, size);		\
}									\
static __always_inline							\
c_t atomic##prefix##_cmpxchg(atomic##prefix##_t *v, c_t o, c_t n)	\
{									\
	return __cmpxchg(&(v->counter), o, n, size);			\
}

#define ATOMIC_OPS()							\
	ATOMIC_OP(int,   , 4)						\
	ATOMIC_OP(s64, 64, 8)

ATOMIC_OPS()

#define atomic_xchg_relaxed	atomic_xchg_relaxed
#define atomic_xchg_acquire	atomic_xchg_acquire
#define atomic_xchg_release	atomic_xchg_release
#define atomic_xchg		atomic_xchg
#define atomic_cmpxchg_relaxed	atomic_cmpxchg_relaxed
#define atomic_cmpxchg_acquire	atomic_cmpxchg_acquire
#define atomic_cmpxchg_release	atomic_cmpxchg_release
#define atomic_cmpxchg		atomic_cmpxchg

#undef ATOMIC_OPS
#undef ATOMIC_OP

static __always_inline bool atomic_inc_unless_negative(atomic_t *v)
{
	int prev, rc;

	__asm__ __volatile__ (
		"0:	lr.w      %[p],  %[c]\n"
		"	bltz      %[p],  1f\n"
		"	addi      %[rc], %[p], 1\n"
		"	sc.w.rl   %[rc], %[rc], %[c]\n"
		"	bnez      %[rc], 0b\n"
		"	fence     rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		:
		: "memory");
	return !(prev < 0);
}

#define atomic_inc_unless_negative atomic_inc_unless_negative

static __always_inline bool atomic_dec_unless_positive(atomic_t *v)
{
	int prev, rc;

	__asm__ __volatile__ (
		"0:	lr.w      %[p],  %[c]\n"
		"	bgtz      %[p],  1f\n"
		"	addi      %[rc], %[p], -1\n"
		"	sc.w.rl   %[rc], %[rc], %[c]\n"
		"	bnez      %[rc], 0b\n"
		"	fence     rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		:
		: "memory");
	return !(prev > 0);
}

#define atomic_dec_unless_positive atomic_dec_unless_positive

static __always_inline int atomic_dec_if_positive(atomic_t *v)
{
       int prev, rc;

	__asm__ __volatile__ (
		"0:	lr.w     %[p],  %[c]\n"
		"	addi     %[rc], %[p], -1\n"
		"	bltz     %[rc], 1f\n"
		"	sc.w.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		:
		: "memory");
	return prev - 1;
}

#define atomic_dec_if_positive atomic_dec_if_positive

static __always_inline bool atomic64_inc_unless_negative(atomic64_t *v)
{
	s64 prev;
	long rc;

	__asm__ __volatile__ (
		"0:	lr.d      %[p],  %[c]\n"
		"	bltz      %[p],  1f\n"
		"	addi      %[rc], %[p], 1\n"
		"	sc.d.rl   %[rc], %[rc], %[c]\n"
		"	bnez      %[rc], 0b\n"
		"	fence     rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		:
		: "memory");
	return !(prev < 0);
}

#define atomic64_inc_unless_negative atomic64_inc_unless_negative

static __always_inline bool atomic64_dec_unless_positive(atomic64_t *v)
{
	s64 prev;
	long rc;

	__asm__ __volatile__ (
		"0:	lr.d      %[p],  %[c]\n"
		"	bgtz      %[p],  1f\n"
		"	addi      %[rc], %[p], -1\n"
		"	sc.d.rl   %[rc], %[rc], %[c]\n"
		"	bnez      %[rc], 0b\n"
		"	fence     rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		:
		: "memory");
	return !(prev > 0);
}

#define atomic64_dec_unless_positive atomic64_dec_unless_positive

static __always_inline s64 atomic64_dec_if_positive(atomic64_t *v)
{
       s64 prev;
       long rc;

	__asm__ __volatile__ (
		"0:	lr.d     %[p],  %[c]\n"
		"	addi      %[rc], %[p], -1\n"
		"	bltz     %[rc], 1f\n"
		"	sc.d.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		:
		: "memory");
	return prev - 1;
}

#define atomic64_dec_if_positive	atomic64_dec_if_positive

#include <arch-generic/atomic.h>

#endif /* __ASSEMBLY__ */

#endif /* _ASM_RISCV_ATOMIC_H */
