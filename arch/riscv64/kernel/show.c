#include <lwk/kernel.h>
#include <lwk/task.h>
#include <lwk/ptrace.h>
#include <lwk/version.h>
#include <lwk/kallsyms.h>
#include <arch/msr.h>


/**
 * Prints a kernel stack trace to the console.
 * If the base pointer passed in is zero the base pointer of the current
 * task used.
 */
static void
__arch_show_kstack(kaddr_t rbp)
{

/* #ifndef CONFIG_FRAME_POINTER */
/* 	printk( "Unable to generate stack trace " */
/* 		"(recompile with CONFIG_FRAME_POINTER)\n" ); */
/* 	return; */
/* #endif */

/* 	if (rbp == 0) */
/* 		asm("move %0, x30\n" : "=r" (rbp)); */

/* 	int max_depth = 16; */
/* 	printk(KERN_DEBUG "  Stack trace from RBP %016lx\n", rbp); */

/* 	while ((rbp >= PAGE_OFFSET) && max_depth--) { */
/* 		kaddr_t sym_addr = ((kaddr_t *)rbp)[1]; */
/* 		char sym_name[KSYM_SYMBOL_LEN]; */

/* 		kallsyms_sprint_symbol(sym_name, sym_addr); */
/* 		printk(KERN_DEBUG "    [<%016lx>] %s\n", sym_addr, sym_name); */

/* 		rbp = *((kaddr_t *)rbp); */
/* 	} */
}


/**
 * Prints a kernel stack trace of the current task to the console.
 */
void
arch_show_kstack(void)
{
	__arch_show_kstack(0);
}


/**
 * Prints ARM64 general purpose registers and friends to the console.
 * NOTE: This prints the CPU register values contained in the passed in
 *       'struct pt_regs *'.  It DOES NOT print the current values in
 *       the CPU's registers.
 */
void
arch_show_registers(struct pt_regs * regs)
{

	bool user_fault = (regs->epc < PAGE_OFFSET);
	char namebuf[128];

	printk("Task ID: %d   Task Name: %s   UTS_RELEASE: %s\n",
		current ? current->id : -1,
		current ? current->name : "BAD CURRENT",
		UTS_RELEASE
	);


	printk("PC:     %016lx (%s)\n", regs->epc,
		       (user_fault) ? "user-context"
             			  : kallsyms_lookup(regs->epc, NULL, NULL,  namebuf));
	printk("SP:     %016lx\n", regs->sp);
	printk("PSTATE: %016lx\n", regs->status);


	printk("RA: %016lx SP: %016lx GP: %016lx TP: %016lx\n", 
		regs->ra, regs->sp, regs->gp, regs->tp);
	printk("T0: %016lx T1: %016lx T2: %016lx S0: %016lx\n", 
		regs->t0, regs->t1, regs->t2, regs->s0);
	printk("S1: %016lx A0: %016lx A1: %016lx A2: %016lx\n", 
		regs->s1, regs->a0, regs->a1, regs->a2);
	printk("A3: %016lx A4: %016lx A5: %016lx A6: %016lx\n", 
		regs->a3, regs->a4, regs->a5, regs->a6);
	printk("A7: %016lx S2: %016lx S3: %016lx S4: %016lx\n", 
		regs->a7, regs->s2, regs->s3, regs->s4);
	printk("S5: %016lx S6: %016lx S7: %016lx S8: %016lx\n", 
		regs->s5, regs->s6, regs->s7, regs->s8);
	printk("S9: %016lx S10: %016lx S11: %016lx T3: %016lx\n", 
		regs->s9, regs->s10, regs->s11, regs->t3);
	printk("T4: %016lx T5: %016lx T6: \n",//%016lx X31: %016lx\n", 
		regs->t4, regs->t5, regs->t6);

	printk("orig_x0: %016lx, cause: %016lx\n", regs->orig_a0, regs->cause);


	if (!user_fault)
		__arch_show_kstack(regs->sp);

}
