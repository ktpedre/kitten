/*
 * Nicholas Gordon, Sandia National Labs, 2022
 * nicholasgordon@fastmail.com
 */

struct plic {

};

struct plic plic;

static struct irqchip plic_chip = {
	.name               = "plic",
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
plic_global_init(struct device_node* dt_node)
{
    int ret = 0;

    return ret;
}
