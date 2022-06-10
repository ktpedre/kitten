/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 */

#ifndef _ASM_RISCV_SMP_H
#define _ASM_RISCV_SMP_H

#include <lwk/cpumask.h>
// #include <lwk/irqreturn.h>
#include <arch/thread_info.h>
#include <lwk/init.h>
#include <lwk/linkage.h>

#define INVALID_HARTID ULONG_MAX

struct seq_file;
extern unsigned long boot_cpu_hartid;

struct riscv_ipi_ops {
	void (*ipi_inject)(const struct cpumask *target);
	void (*ipi_clear)(void);
};

/*
 * Mapping between linux logical cpu index and hartid.
 */
extern unsigned long __cpuid_to_hartid_map[NR_CPUS];
#define cpuid_to_hartid_map(cpu)    __cpuid_to_hartid_map[cpu]

/* print IPI stats */
void show_ipi_stats(struct seq_file *p, int prec);

/* SMP initialization hook for setup_arch */
void __init setup_smp(void);

/* Called from C code, this handles an IPI. */
void handle_IPI(struct pt_regs *regs);

/* Hook for the generic smp_call_function_many() routine. */
void arch_send_call_function_ipi_mask(struct cpumask *mask);

/* Hook for the generic smp_call_function_single() routine. */
void arch_send_call_function_single_ipi(int cpu);

int riscv_hartid_to_cpuid(int hartid);

/* Set custom IPI operations */
void riscv_set_ipi_ops(const struct riscv_ipi_ops *ops);

/* Clear IPI for current CPU */
void riscv_clear_ipi(void);

/* Secondary hart entry */
asmlinkage void smp_callin(void);

/*
 * Obtains the hart ID of the currently executing task.  This relies on
 * THREAD_INFO_IN_TASK, but we define that unconditionally.
 */
#define raw_smp_processor_id() read_pda(cpunumber)

#if defined CONFIG_HOTPLUG_CPU
int __cpu_disable(void);
void __cpu_die(unsigned int cpu);
#endif /* CONFIG_HOTPLUG_CPU */

#if defined(CONFIG_HOTPLUG_CPU) && (CONFIG_SMP)
bool cpu_has_hotplug(unsigned int cpu);
#else
static inline bool cpu_has_hotplug(unsigned int cpu)
{
	return false;
}
#endif

#endif /* _ASM_RISCV_SMP_H */
