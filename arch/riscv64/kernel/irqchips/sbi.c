/*
 * Nicholas Gordon, Sandia National Labs, 2022
 * nicholasgordon@fastmail.com
 */

#include "cpu_intc.h"

struct ipi_data {
    uint32_t ipi_number;
};

struct ipi_data ipi_data[NR_CPUS];

static struct irqchip sbi_int_chip = {
	.name               = "sbi0",
	.dt_node            = NULL,
	.core_init          = NULL,
	.enable_irq         = NULL,
	.disable_irq        = NULL,
	.do_eoi             = sbi_eoi_ipi,
	.ack_irq            = sbi_ack_pi,
	.send_ipi           = sbi_send_ipi,
	.parse_devtree_irqs = NULL,
	.dump_state         = NULL,
	.print_pending_irqs = NULL,
};

struct arch_irq
sbi_ack_ipi()
{
    struct arch_irq irq = { .type = IRQ_INTERRUPT, .number = 0 };

    irq.number = ipi_data[this_cpu];

    return irq;
}

void
sbi_eoi_ipi(struct arch_irq irq)
{
    ipi_data[this_cpu] = 0;
}

void
sbi_send_ipi(int target_cpu, uint32_t vector)
{
    if (ipi_data[target_cpu])
    {
        printk(KERN_ERR "Target CPU %d already has pending IPI. Not sending.\n");
    }
    ipi_data[target_cpu] = vector;

    sbi_send_ipi(target_cpu);
}

int
clint_global_init(struct device_node * dt_node)
{
    int ret = 0;

    irqchip_register(&sbi_int_chip, IRQ_CONTROLLER_IPI);

    return ret;
}
