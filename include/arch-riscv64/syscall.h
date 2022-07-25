#ifndef _RISCV_SYSCALL_H
#define _RISCV_SYSCALL_H

static inline long
__internal_syscall(long n, long _a0, long _a1, long _a2, long _a3, long _a4, long _a5)
{
  register long a0 asm("a0") = _a0;
  register long a1 asm("a1") = _a1;
  register long a2 asm("a2") = _a2;
  register long a3 asm("a3") = _a3;
  register long a4 asm("a4") = _a4;
  register long a5 asm("a5") = _a5;

#ifdef __riscv_32e
  register long syscall_id asm("t0") = n;
#else
  register long syscall_id asm("a7") = n;
#endif

  asm volatile ("scall"
		: "+r"(a0) : "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(syscall_id));

  return a0;
}

#define SYSCALL0(name) 						\
int name(void) {						\
	int status;						\
	status = __internal_syscall(__NR_##name, 0, 0, 0, 0, 0, 0); \
	return status;						\
}

#define SYSCALL1(name, type1) 					\
int name(type1 arg1) {						\
	int status = 0;						\
	status = __internal_syscall(__NR_##name, (long)arg1, 0, 0, 0, 0, 0); \
	return status;						\
}

#define SYSCALL2(name, type1, type2) 				\
int name(type1 arg1, type2 arg2) {				\
	int status = 0;						\
	status = __internal_syscall(__NR_##name, (long)arg1, (long)arg2, 0, 0, 0, 0); \
	return status;						\
}

#define SYSCALL3(name, type1, type2, type3) 			\
int name(type1 arg1, type2 arg2, type3 arg3) {			\
	int status = 0;						\
	status = __internal_syscall(__NR_##name, (long)arg1, (long)arg2, (long)arg3, 0, 0, 0); \
	return status;						\
}

#define SYSCALL4(name, type1, type2, type3, type4) 		\
int name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {	\
	int status = 0;						\
	status = __internal_syscall(__NR_##name, (long)arg1, (long)arg2, (long)arg3, (long)arg4, 0, 0); \
	return status;						\
}

#define SYSCALL5(name, type1, type2, type3, type4, type5) 	\
int name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
         type5 arg5) {						\
	int status = 0;						\
	status = __internal_syscall(__NR_##name, (long)arg1, (long)arg2, (long)arg3, (long)arg4, (long)arg5, 0); \
	return status;						\
}

#define SYSCALL6(name, type1, type2, type3, type4, type5, type6)\
int name(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
         type5 arg5, type6 arg6) {				\
	int status = 0;						\
	status = __internal_syscall(__NR_##name, (long)arg1, (long)arg2, (long)arg3, (long)arg4, (long)arg5, (long)arg6); \
	return status;						\
}

#endif
