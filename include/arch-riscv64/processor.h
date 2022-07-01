/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 */

#ifndef _ASM_RISCV_PROCESSOR_H
#define _ASM_RISCV_PROCESSOR_H

#include <lwk/const.h>
#include <arch/system.h>

// #include <vdso/processor.h>

#include <arch/uapi_ptrace.h>

/*
 * This decides where the kernel will search for a free chunk of vm
 * space during mmap's.
 */
//#define TASK_UNMAPPED_BASE	PAGE_ALIGN(TASK_SIZE / 3)

//#define STACK_TOP		TASK_SIZE
/* #ifdef CONFIG_64BIT */
#define STACK_TOP_MAX		TASK_SIZE_64
/* #else */
/* #define STACK_TOP_MAX		TASK_SIZE */
/* #endif */
#define STACK_ALIGN		16

#ifndef __ASSEMBLY__

struct task_struct;
struct pt_regs;

struct ssatp {
	union {
		uint64_t value;
		struct {
			uint64_t pgd_ppn : 44;
			uint64_t asid : 16;
			uint64_t mode : 4;
		};
	}
};

typedef enum {
	BARE = 0,
	SV39 = 8,
	SV48 = 9,
	SV57 = 10,
	SV64 = 11
} SSATP_MODE;

/* CPU-specific state of a task */
struct thread_struct {
	/* Callee-saved registers */
	unsigned long ra;
	unsigned long kern_sp;	/* Kernel mode stack */
	unsigned long user_sp; /* User-mode stack */
	unsigned long preempt_count;
	unsigned long tp;
	unsigned long s[12];	/* s[0]: frame pointer */
	struct __riscv_d_ext_state fstate;
	unsigned long bad_cause;
};

/* /\* Whitelist the fstate from the task_struct for hardened usercopy *\/ */
/* static inline void arch_thread_struct_whitelist(unsigned long *offset, */
/* 						unsigned long *size) */
/* { */
/* 	*offset = offsetof(struct thread_struct, fstate); */
/* 	*size = sizeof_field(struct thread_struct, fstate); */
/* } */

#define INIT_THREAD {					\
	.sp = sizeof(init_stack) + (long)&init_stack,	\
}

#define current_pt_regs()						\
	(struct pt_regs*)(((struct task_struct*)current)->arch.thread.kern_sp + sizeof(struct pt_regs))

/* #define KSTK_EIP(tsk)		(task_pt_regs(tsk)->epc) */
/* #define KSTK_ESP(tsk)		(task_pt_regs(tsk)->sp) */


/* Do necessary setup to start up a newly executed thread. */
extern void start_thread(struct pt_regs *regs,
			unsigned long pc, unsigned long sp);

/* Free all resources held by a thread. */
static inline void release_thread(struct task_struct *dead_task)
{
}
/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static inline void rep_nop(void)
{
	//__asm__ __volatile__("rep;nop": : :"memory");
}

/* NMG Whatever */
#define cpu_relax() barrier()

extern unsigned long __get_wchan(struct task_struct *p);


static inline void wait_for_interrupt(void)
{
	__asm__ __volatile__ ("wfi");
}

struct device_node;
int riscv_of_processor_hartid(struct device_node *node);
int riscv_of_parent_hartid(struct device_node *node);

extern void riscv_fill_hwcap(void);
extern int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src);

#endif /* __ASSEMBLY__ */

#endif /* _ASM_RISCV_PROCESSOR_H */
