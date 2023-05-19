#ifndef _ARM64_SYSCALL_H
#define _ARM64_SYSCALL_H

static inline long
__internal_syscall(long n, long _x0, long _x1, long _x2, long _x3, long _x4, long _x5)
{
	register long x0 asm("x0") = _x0;
	register long x1 asm("x1") = _x1;
	register long x2 asm("x2") = _x2;
	register long x3 asm("x3") = _x3;
	register long x4 asm("x4") = _x4;
	register long x5 asm("x5") = _x5;

	register long syscall_id asm("x8") = n;

	asm volatile ("svc #0"
		: "+r"(x0) : "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5), "r"(syscall_id));

	return x0;
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
