#include <lwk/kernel.h>
#include <lwk/aspace.h>
#include <lwk/task.h>
#include <arch/ptrace.h>
#include <arch/prctl.h>
#include <arch/unistd.h>
//#include <arch/i387.h>
#include <arch/string.h>
#include <lwk/pmem.h>


int
arch_task_init_tls(struct task_struct   * task, 
		   const struct pt_regs * parent_regs)
{
	return do_arch_prctl(task, ARCH_SET_TLS, parent_regs->tp);
}

int
arch_task_create(
	struct task_struct *	task,
	const start_state_t *	start_state,
	const struct pt_regs *	parent_regs
)
{
	/* Assume we entered via clone() syscall if parent_regs passed in */
	bool is_clone = (parent_regs != NULL);

	/*
	 * Put a pt_regs structure at the top of the new task's kernel stack.
	 * This is used by the CPU control unit and arch_context_switch()
	 * to setup the new task's register state.
 	 */
	struct pt_regs *regs =
		((struct pt_regs *)((kaddr_t)task + TASK_SIZE)) - 1;

	/* Initialize GPRs */
	if (start_state->use_args) {
		/* Pass C-style arguments to new task */
		regs->a0 = start_state->arg[0];
		regs->a1 = start_state->arg[1];
		regs->a2 = start_state->arg[2];
		regs->a3 = start_state->arg[3];
	} else if (is_clone) {
		*regs = *parent_regs;
		regs->a0 = 0;  /* set child's clone() return value to 0 */
	} else {
		/* Zero all registers */
		memset(regs, 0, sizeof(regs));
	}

	task->arch.thread.kern_sp = (kaddr_t)(regs + 1);    /* kstack top */
//task->arch.thread.cpu_context.kern_sp = (kaddr_t)regs;          /* kstack ptr */
	task->arch.thread.user_sp = start_state->stack_ptr; /* ustack ptr */

	/* Mark this as a new-task... arch_context_switch() checks this flag */
	task->arch.flags = TF_NEW_TASK_MASK;

	/* Task's address space is from [0, task->addr_limit) */
	task->arch.addr_limit = PAGE_OFFSET;

	/* Initialize FPU state */
	//reinit_fpu_state(task);

	/* Initialize register state */
	if (start_state->aspace_id == KERNEL_ASPACE_ID) {
		regs->sp     = (vaddr_t)task + TASK_SIZE;
		regs->status = SR_PP | SR_PIE;
	} else {
		regs->sp     = start_state->stack_ptr;
		regs->status = 0;
	}
//	regs->eflags = (1 << 9);  /* enable interrupts */
	regs->epc    = is_clone ? parent_regs->epc : start_state->entry_point;

	return 0;
}
