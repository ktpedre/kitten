/*
 * Nicholas Gordon, Sandia National Labs 2022
 * nicholasgordon@fastmail.com
 *
 * Adapted from ARM64 implementation by
 *   2021, Jack Lange <jacklange@cs.pitt.edu>
 */

#ifndef _RISCV_IRQCHIP_H
#define _RISCV_IRQCHIP_H

typedef enum {
	IRQ_LEVEL_TRIGGERED,
	IRQ_EDGE_TRIGGERED
} irq_trigger_mode_t;

typedef enum {
	IRQ_CONTROLLER_IPI,
	IRQ_CONTROLLER_EXTERNAL,
} irq_controller_type_t;


enum irq_type {
	IRQ_EXCEPTION = 0,
	IRQ_INTERRUPT = 1,
	IRQ_INVALID   = 2,
};

struct arch_irq {
	enum {ARCH_IRQ_INVALID,
				ARCH_IRQ_IPI,
	      ARCH_IRQ_EXT} type;

	uint32_t vector;
	uint64_t eoi_val;
};

struct irqchip {
	char * name;
	struct device_node * dt_node;
	int  (*core_init)(struct device_node * dt_node);
	void (*enable_irq)(uint32_t vector, irq_trigger_mode_t mode);
	void (*disable_irq)(uint32_t vector);
	void (*do_eoi)(struct arch_irq irq);
	struct arch_irq (*ack_irq)();

	void (*send_ipi)(int target_cpu, uint32_t vector);

	int  (*parse_devtree_irqs)(struct device_node * dt_node, uint32_t num_irqs, struct irq_def * irqs);

	void (*dump_state)(void);
	void (*print_pending_irqs)(void);
};

typedef int (*irqchip_init_fn)(struct device_node *);

int irqchip_register(struct irqchip * chip, irq_controller_type_t type);

int irqchip_global_init(void);
int irqchip_local_init(void);




void irqchip_enable_irq(uint32_t vector, irq_trigger_mode_t mode);
void irqchip_disable_irq(uint32_t vector);

void             irqchip_do_eoi(struct arch_irq irq);
struct arch_irq  irqchip_ack_irq(struct pt_regs* regs);
void             irqchip_send_ipi(int target_cpu, uint32_t vector);



struct irq_def {
	uint32_t           vector;
	irq_trigger_mode_t mode;
};

int parse_fdt_irqs(struct device_node * dt_node, 
		   uint32_t             num_irqs, 
		   struct irq_def     * irqs);

void probe_pending_irqs(void);
void irqchip_dump_state(void);


#endif
