/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2006  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (c) 2018  Jim Wilson (jimw@sifive.com)
 */

#ifndef _ASM_RISCV_FUTEX_H
#define _ASM_RISCV_FUTEX_H

#include <lwk/futex.h>
#include <arch/uaccess.h>
#include <lwk/errno.h>
#include <arch/asm.h>
#include <arch/asm-extable.h>

/* We don't even really need the extable code, but for now keep it simple */
#ifndef CONFIG_MMU
#define __enable_user_access()		do { } while (0)
#define __disable_user_access()		do { } while (0)
#endif

#define __futex_atomic_op(insn, ret, oldval, uaddr, oparg)	\
{								\
	__enable_user_access();					\
	__asm__ __volatile__ (					\
	"1:	" insn "				\n"	\
	"2:						\n"	\
	_ASM_EXTABLE(1b, 2b)			\
	: [r] "+r" (ret), [ov] "=&r" (oldval),			\
	  [u] "+m" (*uaddr)					\
	: [op] "Jr" (oparg)					\
	: "memory");						\
	__disable_user_access();				\
}

static inline int
arch_futex_atomic_op_inuser(int op, int oparg, int *oval, u32 __user *uaddr)
{
	int oldval = 0, ret = 0;

	if (!access_ok(VERIFY_WRITE, uaddr, sizeof(u32)))
		return -EFAULT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("amoswap.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		break;
	case FUTEX_OP_ADD:
		__futex_atomic_op("amoadd.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		break;
	case FUTEX_OP_OR:
		__futex_atomic_op("amoor.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		break;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("amoand.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, ~oparg);
		break;
	case FUTEX_OP_XOR:
		__futex_atomic_op("amoxor.w.aqrl %[ov],%z[op],%[u]",
				  ret, oldval, uaddr, oparg);
		break;
	default:
		ret = -ENOSYS;
	}

	if (!ret)
		*oval = oldval;

	return ret;
}

static int futex_atomic_op_inuser(unsigned int encoded_op, u32 __user *uaddr)
{
	unsigned int op =	  (encoded_op & 0x70000000) >> 28;
	unsigned int cmp =	  (encoded_op & 0x0f000000) >> 24;
	int oparg = sign_extend32((encoded_op & 0x00fff000) >> 12, 11);
	int cmparg = sign_extend32(encoded_op & 0x00000fff, 11);
	int oldval, ret;

	if (encoded_op & (FUTEX_OP_OPARG_SHIFT << 28)) {
		if (oparg < 0 || oparg > 31) {
			char comm[sizeof(current->comm)];
			/*
			 * kill this print and return -EINVAL when userspace
			 * is sane again
			 */
			/* pr_info_ratelimited("futex_wake_op: %s tries to shift op by %d; fix this program\n", */
			/* 		get_task_comm(comm, current), oparg); */
			oparg &= 31;
		}
		oparg = 1 << oparg;
	}

	/* if (!access_ok(VERIFY_WRITE, uaddr, sizeof(u32))) */
	/* 	return -EFAULT; */

	ret = arch_futex_atomic_op_inuser(op, oparg, &oldval, uaddr);
	if (ret)
		return ret;

	switch (cmp) {
	case FUTEX_OP_CMP_EQ:
		return oldval == cmparg;
	case FUTEX_OP_CMP_NE:
		return oldval != cmparg;
	case FUTEX_OP_CMP_LT:
		return oldval < cmparg;
	case FUTEX_OP_CMP_GE:
		return oldval >= cmparg;
	case FUTEX_OP_CMP_LE:
		return oldval <= cmparg;
	case FUTEX_OP_CMP_GT:
		return oldval > cmparg;
	default:
		return -ENOSYS;
	}
}


static inline int
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
{
	int ret = 0;
	u32 val;
	uintptr_t tmp;

	if (!access_ok(VERIFY_WRITE, uaddr, sizeof(u32)))
		return -EFAULT;

	__enable_user_access();
	__asm__ __volatile__ (
	"1:	lr.w.aqrl %[v],%[u]			\n"
	"	bne %[v],%z[ov],3f			\n"
	"2:	sc.w.aqrl %[t],%z[nv],%[u]		\n"
	"	bnez %[t],1b				\n"
	"3:						\n"
		_ASM_EXTABLE(1b, 3b) \
		_ASM_EXTABLE(2b, 3b) \
	: [r] "+r" (ret), [v] "=&r" (val), [u] "+m" (*uaddr), [t] "=&r" (tmp)
	: [ov] "Jr" (oldval), [nv] "Jr" (newval)
	: "memory");
	__disable_user_access();

	*uval = val;
	return ret;
}

#endif /* _ASM_RISCV_FUTEX_H */
