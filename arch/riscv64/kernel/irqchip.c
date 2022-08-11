/*
 * Nicholas Gordon, Sandia National Labs 2022
 * nicholasgordon@fastmail.com
 *
 * Adapted from ARM64 implementation by
 *   Jack Lange <jack.lange@cs.pitt.edu>
 */

#include <lwk/kernel.h>
#include <lwk/init.h>
#include <lwk/resource.h>

#include <arch/msr.h>
#include <arch/irqchip.h>
#include <arch/irq_vectors.h>

#include <arch/of.h>
#include <arch/io.h>

static struct irqchip * irq_controller = NULL;
#define NR_CONTROLLERS 4
static struct irqchip controllers[4];

int __init
irqchip_local_init(void)
{
	irq_controller->core_init(irq_controller->dt_node);
}

static const struct of_device_id intr_ctrlr_of_match[]  = {
	{ .compatible = "riscv,clint0", .data = clint_global_init},
	{ .compatible = "riscv,plic0",  .data = plic_init},
	{},
};

int
irqchip_register(struct irqchip * chip, irq_controller_type_t type)
{
	if (controllers[type]) {
		panic("Failed to register irq controller. Already registered.\n");
	}

	printk("Registering IRQ Controller [%s] with type %d\n", chip->name, type);

	controllers[type] = chip;

	return 0;
}

int __init
irqchip_global_init(void)
{
	struct device_node  * dt_node    = NULL;
	struct of_device_id * matched_np = NULL;
	irqchip_init_fn init_fn;

	dt_node = of_find_matching_node_and_match(NULL, intr_ctrlr_of_match, &matched_np);

	if (!dt_node || !of_device_is_available(dt_node)) {
		panic("Could not find interrupt controller\n");
	//	return -ENODEV;
	}

	init_fn = (irqchip_init_fn)(matched_np->data);

	return init_fn(dt_node);
}

void probe_pending_irqs(void) {
	ASSERT(irq_controller->print_pending_irqs != NULL);
	irq_controller->print_pending_irqs();
}

void irqchip_dump_state(void)
{
	ASSERT(irq_controller->dump_state != NULL);
	irq_controller->dump_state();
}

void
irqchip_enable_irq(uint32_t           irq_num, 
	   	   irq_trigger_mode_t trigger_mode)
{
	ASSERT(irq_controller->enable_irq != NULL);
	irq_controller->enable_irq(irq_num, trigger_mode);
}

void
irqchip_do_eoi(struct arch_irq irq)
{
	ASSERT(irq_controller->do_eoi != NULL);
	irq_controller->do_eoi(irq);
}

struct arch_irq
irqchip_ack_irq(struct pt_regs * regs) {
	/* NMG Should iterate across all controllers and contain this ugly state */
	//ASSERT(irq_controller->ack_irq != NULL);

	/* Highest bit set to 1 is an interrupt. Otherwise, it's an exception */
	struct arch_irq irq = { .value = regs->cause };//irqchip_ack_irq();

	switch (irq.type) {
	case IRQ_EXCEPTION: {
		irq = controllers[IRQ_CONTROLLER_EXTERNAL].ack_irq();
		break;
	}
	case IRQ_INTERRUPT: {
		irq = controllers[IRQ_CONTROLLER_IPI].ack_irq();
		break;
	}
	default: {
		irq = { .value = 0 };
	}
	}

	return irq;
}

void 
irqchip_send_ipi(int target_cpu, 
		 uint32_t vector)
{
	ASSERT(irq_controller->send_ipi != NULL);
	return irq_controller->send_ipi(target_cpu, vector);

}


int 
parse_fdt_irqs(struct device_node *  dt_node, 
	       uint32_t              num_irqs, 
	       struct irq_def     *  irqs)
{
	ASSERT(irq_controller->parse_devtree_irqs != NULL);
	return irq_controller->parse_devtree_irqs(dt_node, num_irqs, irqs);
}
