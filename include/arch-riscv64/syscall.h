#ifndef _RISCV_SYSCALL_H //_ARM64_SYSCALL_H
#define _RISCV_SYSCALL_H //_ARM64_SYSCALL_H

#ifdef __KERNEL__
#include <lwk/init.h>

void __init vsyscall_map(void);
void __init vsyscall_init(void);


/**
 * Prototype for system call handler functions.
 */
typedef long (*syscall_ptr_t)(void);

/** Register a system call.
 *
 * Some system calls are registered at run-time rather than compile
 * time.
 *
 * \note The type signature for handler is generic for any number
 * of arguments and may require a cast.
 *
 * \todo Put this is a non-architecture specific file?
 */
extern void
syscall_register(
	unsigned		nr,
	syscall_ptr_t		handler
);

#endif /* __KERNEL__ */

/**
 * There is no way to specify inline assembly constraints for %r10 (arg4),
 * %r8 (arg5), and %r9 (arg6), so the macros below specify the registers
 * to use for local variables as a work-around.
 *
 * GCC BUG? -- For some unknown reason, the register specified to store
 *             a local variable is not always honored if the variable
 *             is assigned when it is declared.  Work-around by declaring
 *             and assigning on separate lines.
 */
#define SYSCALL0(name) 						\
int name(void) {						\
	int status;						\
	/*asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name)				\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}

#define SYSCALL1(name, type1) 					\
int name(type1 arg1) {						\
	int status = 0;						\
	/*register type1 rdi asm("rdi");				\
	rdi = arg1;						\
	asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name),				\
		  "r" (rdi)					\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}

#define SYSCALL2(name, type1, type2) 				\
int name(type1 arg1, type2 arg2) {				\
	int status = 0;						\
	/*register type1 rdi asm("rdi");				\
	register type2 rsi asm("rsi");				\
	rdi = arg1;						\
	rsi = arg2;						\
	asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name),				\
		  "r" (rdi),					\
		  "r" (rsi)					\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}

#define SYSCALL3(name, type1, type2, type3) 			\
int name(type1 arg1, type2 arg2, type3 arg3) {			\
	int status = 0;						\
	/*register type1 rdi asm("rdi");				\
	register type2 rsi asm("rsi");				\
	register type3 rdx asm("rdx");				\
	rdi = arg1;						\
	rsi = arg2;						\
	rdx = arg3;						\
	asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name),				\
		  "r" (rdi),					\
		  "r" (rsi),					\
		  "r" (rdx)					\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}

#define SYSCALL4(name, type1, type2, type3, type4) 		\
int name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {	\
	int status = 0;						\
	/*register type1 rdi asm("rdi");				\
	register type2 rsi asm("rsi");				\
	register type3 rdx asm("rdx");				\
	register type4 r10 asm("r10");				\
	rdi = arg1;						\
	rsi = arg2;						\
	rdx = arg3;						\
	r10 = arg4;						\
	asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name),				\
		  "r" (rdi),					\
		  "r" (rsi),					\
		  "r" (rdx),					\
		  "r" (r10)					\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}

#define SYSCALL5(name, type1, type2, type3, type4, type5) 	\
int name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
         type5 arg5) {						\
	int status = 0;						\
	/*register type1 rdi asm("rdi");				\
	register type2 rsi asm("rsi");				\
	register type3 rdx asm("rdx");				\
	register type4 r10 asm("r10");				\
	register type5 r8  asm("r8");				\
	rdi = arg1;						\
	rsi = arg2;						\
	rdx = arg3;						\
	r10 = arg4;						\
	r8  = arg5;						\
	asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name),				\
		  "r" (rdi),					\
		  "r" (rsi),					\
		  "r" (rdx),					\
		  "r" (r10),					\
		  "r" (r8)					\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}

#define SYSCALL6(name, type1, type2, type3, type4, type5, type6)\
int name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
         type5 arg5, type6 arg6) {				\
	int status = 0;						\
	/*register type1 rdi asm("rdi");				\
	register type2 rsi asm("rsi");				\
	register type3 rdx asm("rdx");				\
	register type4 r10 asm("r10");				\
	register type5 r8  asm("r8");				\
	register type6 r9  asm("r9");				\
	rdi = arg1;						\
	rsi = arg2;						\
	rdx = arg3;						\
	r10 = arg4;						\
	r8  = arg5;						\
	r9  = arg6;						\
	asm volatile(						\
		"syscall"					\
		: "=a" (status)					\
		: "0" (__NR_##name),				\
		  "r" (rdi),					\
		  "r" (rsi),					\
		  "r" (rdx),					\
		  "r" (r10),					\
		  "r" (r8),					\
		  "r" (r9)					\
		: "memory", "rcx", "r11", "cc"			\
	);*/							\
	return status;						\
}



#endif /* _RISCV_SYSCALL_H */
