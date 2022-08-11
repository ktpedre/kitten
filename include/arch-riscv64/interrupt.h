#ifndef _RISCV_INTERRUPT_H
#define _RISCV_INTERRUPT_H

#include <arch/pda.h>
//#include <arch/irq_vectors.h>

/* NMG Not finished, but for now it'll work */
#define NUM_IRQ_ENTRIES				1024
#define NUM_IPI_ENTRIES				16

/* NMG Both of these obviously wrong */
#define FIRST_AVAIL_VECTOR 0
#define FIRST_SYSTEM_VECTOR 0 


#define ARCH_NUM_IRQS	NUM_IRQ_ENTRIES

static inline bool
arch_in_interrupt(void)
{
	return (read_pda(irqcount) >= 0);
}

struct arch_irq {
	union {
		uint64_t value;
		struct {
			uint64_t irqnum : 63;
			uint64_t type  : 1;
		};
	};
};

#endif
