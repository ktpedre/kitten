#ifndef _X86_64_ATOMIC_H
#define _X86_64_ATOMIC_H

/* atomic_t should be 32 bit signed type */

/*
 * Atomic operations that C can't guarantee us.  Useful for
 * resource counting etc..
 */

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
typedef struct { volatile int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

/**
 * atomic_read - read atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically reads the value of @v.
 */ 
#define atomic_read(v)		((v)->counter)

/**
 * atomic_set - set atomic variable
 * @v: pointer of type atomic_t
 * @i: required value
 * 
 * Atomically sets the value of @v to @i.
 */ 
#define atomic_set(v,i)		(((v)->counter) = (i))

/**
 * atomic_add - add integer to atomic variable
 * @i: integer value to add
 * @v: pointer of type atomic_t
 * 
 * Atomically adds @i to @v.
 */
static __inline__ void atomic_add(int i, atomic_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; addl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
#endif
}

/**
 * atomic_sub - subtract the atomic variable
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 * 
 * Atomically subtracts @i from @v.
 */
static __inline__ void atomic_sub(int i, atomic_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; subl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
#endif
}

/**
 * atomic_sub_and_test - subtract value from variable and test result
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 * 
 * Atomically subtracts @i from @v and returns
 * true if the result is zero, or false for all
 * other cases.
 */
static __inline__ int atomic_sub_and_test(int i, atomic_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; subl %2,%0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
#endif
	return c;
}

/**
 * atomic_inc - increment atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically increments @v by 1.
 */ 
static __inline__ void atomic_inc(atomic_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; incl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
#endif
}

/**
 * atomic_dec - decrement atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically decrements @v by 1.
 */ 
static __inline__ void atomic_dec(atomic_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; decl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
#endif
}

/**
 * atomic_dec_and_test - decrement and test
 * @v: pointer of type atomic_t
 * 
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.
 */ 
static __inline__ int atomic_dec_and_test(atomic_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; decl %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
#endif
	return c != 0;
}

/**
 * atomic_inc_and_test - increment and test 
 * @v: pointer of type atomic_t
 * 
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */ 
static __inline__ int atomic_inc_and_test(atomic_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; incl %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
#endif
	return c != 0;
}

/**
 * atomic_add_negative - add and test if negative
 * @i: integer value to add
 * @v: pointer of type atomic_t
 * 
 * Atomically adds @i to @v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.
 */ 
static __inline__ int atomic_add_negative(int i, atomic_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; addl %2,%0; sets %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
#endif
	return c;
}

/**
 * atomic_add_return - add and return
 * @i: integer value to add
 * @v: pointer of type atomic_t
 *
 * Atomically adds @i to @v and returns @i + @v
 */
static __inline__ int atomic_add_return(int i, atomic_t *v)
{
	int __i = i;
#if 0
	__asm__ __volatile__(
		"lock ; xaddl %0, %1;"
		:"=r"(i)
		:"m"(v->counter), "0"(i));
#endif
	return i + __i;
}

static __inline__ int atomic_sub_return(int i, atomic_t *v)
{
	return atomic_add_return(-i,v);
}

#define atomic_inc_return(v)  (atomic_add_return(1,v))
#define atomic_dec_return(v)  (atomic_sub_return(1,v))

/* An 64bit atomic type */

typedef struct { volatile long counter; } atomic64_t;

#define ATOMIC64_INIT(i)	{ (i) }

/**
 * atomic64_read - read atomic64 variable
 * @v: pointer of type atomic64_t
 *
 * Atomically reads the value of @v.
 * Doesn't imply a read memory barrier.
 */
#define atomic64_read(v)		((v)->counter)

/**
 * atomic64_set - set atomic64 variable
 * @v: pointer to type atomic64_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
#define atomic64_set(v,i)		(((v)->counter) = (i))

/**
 * atomic64_add - add integer to atomic64 variable
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v.
 */
static __inline__ void atomic64_add(long i, atomic64_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; addq %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
#endif
}

/**
 * atomic64_sub - subtract the atomic64 variable
 * @i: integer value to subtract
 * @v: pointer to type atomic64_t
 *
 * Atomically subtracts @i from @v.
 */
static __inline__ void atomic64_sub(long i, atomic64_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; subq %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
#endif
}

/**
 * atomic64_sub_and_test - subtract value from variable and test result
 * @i: integer value to subtract
 * @v: pointer to type atomic64_t
 *
 * Atomically subtracts @i from @v and returns
 * true if the result is zero, or false for all
 * other cases.
 */
static __inline__ int atomic64_sub_and_test(long i, atomic64_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; subq %2,%0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
#endif
	return c;
}

/**
 * atomic64_inc - increment atomic64 variable
 * @v: pointer to type atomic64_t
 *
 * Atomically increments @v by 1.
 */
static __inline__ void atomic64_inc(atomic64_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; incq %0"
		:"=m" (v->counter)
		:"m" (v->counter));
#endif
}

/**
 * atomic64_dec - decrement atomic64 variable
 * @v: pointer to type atomic64_t
 *
 * Atomically decrements @v by 1.
 */
static __inline__ void atomic64_dec(atomic64_t *v)
{
#if 0
	__asm__ __volatile__(
		"lock ; decq %0"
		:"=m" (v->counter)
		:"m" (v->counter));
#endif
}

/**
 * atomic64_dec_and_test - decrement and test
 * @v: pointer to type atomic64_t
 *
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.
 */
static __inline__ int atomic64_dec_and_test(atomic64_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; decq %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
#endif
	return c != 0;
}

/**
 * atomic64_inc_and_test - increment and test
 * @v: pointer to type atomic64_t
 *
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */
static __inline__ int atomic64_inc_and_test(atomic64_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; incq %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
#endif
	return c != 0;
}

/**
 * atomic64_add_negative - add and test if negative
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.
 */
static __inline__ int atomic64_add_negative(long i, atomic64_t *v)
{
	unsigned char c;
#if 0
	__asm__ __volatile__(
		"lock ; addq %2,%0; sets %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
#endif
	return c;
}

/**
 * atomic64_add_return - add and return
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v and returns @i + @v
 */
static __inline__ long atomic64_add_return(long i, atomic64_t *v)
{
	long __i = i;
#if 0
	__asm__ __volatile__(
		"lock ; xaddq %0, %1;"
		:"=r"(i)
		:"m"(v->counter), "0"(i));
#endif
	return i + __i;
}

static __inline__ long atomic64_sub_return(long i, atomic64_t *v)
{
	return atomic64_add_return(-i,v);
}

#define atomic64_inc_return(v)  (atomic64_add_return(1,v))
#define atomic64_dec_return(v)  (atomic64_sub_return(1,v))

#define atomic_cmpxchg(v, old, new) ((int)cmpxchg(&((v)->counter), old, new))
#define atomic_xchg(v, new) (xchg(&((v)->counter), new))

/**
 * atomic_add_unless - add unless the number is a given value
 * @v: pointer of type atomic_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @v, so long as it was not @u.
 * Returns non-zero if @v was not @u, and zero otherwise.
 */
#define atomic_add_unless(v, a, u)				\
({								\
	int c, old;						\
	c = atomic_read(v);					\
	for (;;) {						\
		if (unlikely(c == (u)))				\
			break;					\
		old = atomic_cmpxchg((v), c, c + (a));		\
		if (likely(old == c))				\
			break;					\
		c = old;					\
	}							\
	c != (u);						\
})
#define atomic_inc_not_zero(v) atomic_add_unless((v), 1, 0)

/* These are x86-specific, used by some header files */
#define atomic_clear_mask(mask, addr)

#if 0
\
__asm__ __volatile__("lock ; andl %0,%1" \
: : "r" (~(mask)),"m" (*addr) : "memory")
#endif

#define atomic_set_mask(mask, addr)

#if 0
\
__asm__ __volatile__("lock ; orl %0,%1" \
: : "r" ((unsigned)mask),"m" (*(addr)) : "memory")
#endif

/* Atomic operations are already serializing on x86 */
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#define LOCK_PREFIX \
                ".section .smp_locks,\"a\"\n"   \
                ".balign 8\n"                 \
                ".quad 661f\n" /* address */ \
                ".previous\n"                   \
                "661:\n\tlock; "

#include <arch-generic/atomic.h>
#endif
