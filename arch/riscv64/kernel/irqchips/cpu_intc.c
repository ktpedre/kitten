/*
 * Nicholas Gordon, Sandia National Labs, 2022
 * nicholasgordon@fastmail.com
 */

#include "cpu_intc.h"

struct cpu_intc {

};

struct cpu_intc intc;

static struct irqchip cpu_intc_chip = {
	.name               = "cpu-intc",
	.dt_node            = NULL,
	.core_init          = ,
	.enable_irq         = ,
	.disable_irq        = ,
	.do_eoi             = ,
	.ack_irq            = ,
	.send_ipi           = ,
	.parse_devtree_irqs = ,
	.dump_state         = ,
	.print_pending_irqs = ,
};

int
cpu_intc_global_init(struct device_node * dt_node)
{
    int ret = 0;



    return ret;
}
