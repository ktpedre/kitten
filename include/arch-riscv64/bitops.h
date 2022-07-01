/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 */

#ifndef _ASM_RISCV_BITOPS_H
#define _ASM_RISCV_BITOPS_H

#include <lwk/compiler.h>
#include <arch/barrier.h>
// #include <arch/bitsperlong.h>
 
//#include <asm-generic/bitops/__ffs.h>
// #include <arch/ffz.h>
#include <arch/fls.h>
//#include <asm-generic/bitops/__fls.h>
#include <arch/fls64.h>
//#include <arch/sched.h>
#include <arch/ffs.h>

#include <arch-generic/bitops/hweight.h>

#define ffz(x)  __ffs(~(x))

#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)


#define __AMO(op)	"amo" #op ".d"

#define __test_and_op_bit_ord(op, mod, nr, addr, ord)		\
({								\
	unsigned long __res, __mask;				\
	__mask = BIT_MASK(nr);					\
	__asm__ __volatile__ (					\
		__AMO(op) #ord " %0, %2, %1"			\
		: "=r" (__res), "+A" (addr[BIT_WORD(nr)])	\
		: "r" (mod(__mask))				\
		: "memory");					\
	((__res & __mask) != 0);				\
})

#define __op_bit_ord(op, mod, nr, addr, ord)			\
	__asm__ __volatile__ (					\
		__AMO(op) #ord " zero, %1, %0"			\
		: "+A" (addr[BIT_WORD(nr)])			\
		: "r" (mod(BIT_MASK(nr)))			\
		: "memory");

/**
 * sign_extend32 - sign extend a 32-bit value using specified bit as sign-bit
 * @value: value to sign extend
 * @index: 0 based bit index (0<=index<32) to sign bit
 *
 * This is safe to use for 16- and 8-bit types as well.
 */
static inline __s32 sign_extend32(__u32 value, int index)
{
	__u8 shift = 31 - index;
	return (__s32)(value << shift) >> shift;
}

/**
 * sign_extend64 - sign extend a 64-bit value using specified bit as sign-bit
 * @value: value to sign extend
 * @index: 0 based bit index (0<=index<64) to sign bit
 */
static inline __s64 sign_extend64(__u64 value, int index)
{
	__u8 shift = 63 - index;
	return (__s64)(value << shift) >> shift;
}

#define __test_and_op_bit(op, mod, nr, addr) 			\
	__test_and_op_bit_ord(op, mod, nr, addr, .aqrl)
#define __op_bit(op, mod, nr, addr)				\
	__op_bit_ord(op, mod, nr, addr, )

/* Bitmask modifiers */
#define __NOP(x)	(x)
#define __NOT(x)	(~(x))

/**
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation may be reordered on other architectures than x86.
 */
static inline int test_and_set_bit(int nr, volatile unsigned long *addr)
{
	return __test_and_op_bit(or, __NOP, nr, addr);
}

/**
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation can be reordered on other architectures other than x86.
 */
static inline int test_and_clear_bit(int nr, volatile unsigned long *addr)
{
	return __test_and_op_bit(and, __NOT, nr, addr);
}

/**
 * test_and_change_bit - Change a bit and return its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_change_bit(int nr, volatile unsigned long *addr)
{
	return __test_and_op_bit(xor, __NOP, nr, addr);
}

/**
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Note: there are no guarantees that this function will not be reordered
 * on non x86 architectures, so if you are writing portable code,
 * make sure not to rely on its reordering guarantees.
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void set_bit(int nr, volatile unsigned long *addr)
{
	__op_bit(or, __NOP, nr, addr);
}

/**
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * Note: there are no guarantees that this function will not be reordered
 * on non x86 architectures, so if you are writing portable code,
 * make sure not to rely on its reordering guarantees.
 */
static inline void clear_bit(int nr, volatile unsigned long *addr)
{
	__op_bit(and, __NOT, nr, addr);
}

/**
 * change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * change_bit()  may be reordered on other architectures than x86.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void change_bit(int nr, volatile unsigned long *addr)
{
	__op_bit(xor, __NOP, nr, addr);
}

/**
 * test_and_set_bit_lock - Set a bit and return its old value, for lock
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and provides acquire barrier semantics.
 * It can be used to implement bit locks.
 */
static inline int test_and_set_bit_lock(
	unsigned long nr, volatile unsigned long *addr)
{
	return __test_and_op_bit_ord(or, __NOP, nr, addr, .aq);
}

/**
 * clear_bit_unlock - Clear a bit in memory, for unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This operation is atomic and provides release barrier semantics.
 */
static inline void clear_bit_unlock(
	unsigned long nr, volatile unsigned long *addr)
{
	__op_bit_ord(and, __NOT, nr, addr, .rl);
}

/**
 * __clear_bit_unlock - Clear a bit in memory, for unlock
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This operation is like clear_bit_unlock, however it is not atomic.
 * It does provide release barrier semantics so it can be used to unlock
 * a bit lock, however it would only be used if no other CPU can modify
 * any bits in the memory until the lock is released (a good example is
 * if the bit lock itself protects access to the other bits in the word).
 *
 * On RISC-V systems there seems to be no benefit to taking advantage of the
 * non-atomic property here: it's a lot more instructions and we still have to
 * provide release semantics anyway.
 */
static inline void __clear_bit_unlock(
	unsigned long nr, volatile unsigned long *addr)
{
	clear_bit_unlock(nr, addr);
}

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static __always_inline int
test_bit(unsigned int nr, const volatile unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

#undef __test_and_op_bit
#undef __op_bit
#undef __NOP
#undef __NOT
#undef __AMO

#define __set_bit(nr,addr) \
	set_bit(nr,addr)
//void set_bit(int nr, volatile unsigned long *addr);

#define __clear_bit(nr, addr) \
	clear_bit(nr,addr)

//#include <asm-generic/bitops/non-atomic.h>
//#include <asm-generic/bitops/le.h>
//#include <asm-generic/bitops/ext2-atomic.h>

#endif /* _ASM_RISCV_BITOPS_H */
