/* 
 * 2021, Jack Lange <jacklange@cs.pitt.edu>
 */

#include <lwk/kernel.h>
#include <lwk/init.h>
#include <lwk/resource.h>
#include <lwk/cpuinfo.h>

#include <arch/irqchip.h>
#include <arch/msr.h>
#include <arch/of.h>
#include <arch/io.h>
#include <arch/irq_vectors.h>
#include <arch/topology.h>

#include <arch/hafnium/call.h>





struct hafnium_vintc {


};

static struct hafnium_vintc vintc;




static int
__hafnium_vintc_parse_irqs(struct device_node *  dt_node, 
                  uint32_t              num_irqs, 
                  struct irq_def     *  irqs);

static void 
__hafnium_vintc_print_pending_irqs(void)
{
}

static void 
__hafnium_vintc_dump_state(void)
{
	printk("Dumping hafnium_vintc state not implemented\n");
}

static void
__hafnium_vintc_enable_irq(uint32_t           irq_num, 
                          irq_trigger_mode_t trigger_mode)
{
    if (trigger_mode != IRQ_EDGE_TRIGGERED) {
        panic("only edge triggered interrupts supported in hafnium\n");
    }

    hf_interrupt_enable(irq_num, true);
}


static void
__hafnium_vintc_disable_irq(uint32_t vector)
{
    hf_interrupt_enable(vector, false);
}

static struct arch_irq 
__hafnium_vintc_ack_irq(void)
{
   	struct arch_irq irq = {.vector = hf_interrupt_get()};

	if (irq.vector < 16) {
		irq.type = ARCH_IRQ_IPI;
	} else {
		irq.type = ARCH_IRQ_EXT;
	}

    return irq;

}


static void
__hafnium_vintc_do_eoi(struct arch_irq irq)
{
    // do nothing?
}

static void
__hafnium_vintc_send_ipi(int target_cpu, uint32_t vector)
{
    hf_interrupt_inject(hf_vm_get_id(), target_cpu, vector);
}


static int 
__hafnium_vintc_core_init()
{


}



static struct irqchip hafnium_vintc_chip = {
	.name               = "hafnium_vintc",
	.dt_node            = NULL,
	.core_init          = __hafnium_vintc_core_init,
	.enable_irq         = __hafnium_vintc_enable_irq,
	.disable_irq        = __hafnium_vintc_disable_irq,
	.do_eoi             = __hafnium_vintc_do_eoi,
	.ack_irq            = __hafnium_vintc_ack_irq,
	.send_ipi           = __hafnium_vintc_send_ipi,
	.parse_devtree_irqs = __hafnium_vintc_parse_irqs,
	.dump_state         = __hafnium_vintc_dump_state, 
	.print_pending_irqs = __hafnium_vintc_print_pending_irqs
};



void 
hafnium_vintc_global_init(struct device_node * dt_node)
{

	hafnium_vintc_chip.dt_node = dt_node;
	irqchip_register(&hafnium_vintc_chip);
}




#include <dt-bindings/interrupt-controller/arm-gic.h>
static int
__hafnium_vintc_parse_irqs(struct device_node *  dt_node, 
                  uint32_t              num_irqs, 
                  struct irq_def     *  irqs)
{
	const __be32 * ip;
	uint32_t       irq_cells = 0;

	int i   = 0;
	int ret = 0;

	ip = of_get_property(hafnium_vintc_chip.dt_node, "#interrupt-cells", NULL);

	if (!ip) {
		printk("Could not find #interrupt-cells property\n");
		goto err;
	}

	irq_cells = be32_to_cpup(ip);

	if (irq_cells != 2) {
		printk("Interrupt Cell size of (%d) is not supported\n", irq_cells);
		goto err;
	}
	

	for (i = 0; i < num_irqs; i++) {
		uint32_t type   = 0;
		uint32_t vector = 0;
		uint32_t mode   = 0;
		
		ret |= of_property_read_u32_index(dt_node, "interrupts", &type,   (i * 3));
		ret |= of_property_read_u32_index(dt_node, "interrupts", &vector, (i * 3) + 1);

		if (ret != 0) {
			printk("Failed to fetch interrupt cell\n");
			goto err;
		}


		irqs[i].mode = IRQ_EDGE_TRIGGERED;


		if (type == GIC_PPI) {
			irqs[i].vector = vector + PPI_VECTOR_START;
		} else if (type == GIC_SPI) {
			irqs[i].vector = vector + SPI_VECTOR_START;
		} else {
			panic("Invalid IRQ Type\n");
		}
	}

	return 0;

err:
	return -1;	
}