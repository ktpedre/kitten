#ifndef _RISCV_PDA_H/* #ifndef _ARM64_PDA_H */
#define _RISCV_PDA_H/* #define _ARM64_PDA_H */

#ifndef __ASSEMBLY__
#include <lwk/stddef.h>
#include <lwk/types.h>
#include <lwk/cache.h>
//#include <lwk/task.h>
#include <arch/page.h>
#include <lwk/idspace.h>

static inline u64 set_tp(u64 val)
{
	__asm__ __volatile__("mv tp, %0\n" :: "r"(val));
	return ;
}

static inline u64 get_tp()
{
	u64 tp;
	__asm__ __volatile__("mv %0, tp\n" : "=r"(tp));
	return tp;
}

/* Per processor datastructure. Each core stores its own version in the tpidr_el1 register. */ 
struct RISCV_pda {
	struct task_struct * pcurrent;	/* Current process */
	unsigned long data_offset;	/* Per cpu data offset from linker address */
	unsigned long kernelstack;  /* top of kernel stack for current */ 
	unsigned long oldsp; 	    /* user rsp for system call */
#if DEBUG_STKSZ > EXCEPTION_STKSZ
	unsigned long debugstack;   /* #DB/#BP stack. */
#endif
	int irqcount;		    /* Irq nesting counter. Starts with -1 */
	int cpunumber;		    /* Logical CPU number */
	char *irqstackptr;	/* top of irqstack */
	int nodenumber;		    /* number of current node */
	unsigned int __softirq_pending;
	unsigned int __nmi_count;	/* number of NMI on this CPUs */
	int mmu_state;
	struct aspace *active_aspace;
	unsigned int timer_reload_value;
	unsigned apic_timer_irqs;
}; // ____cacheline_aligned_in_smp;

extern struct RISCV_pda *_cpu_pda[];
extern struct RISCV_pda boot_cpu_pda[];

void pda_init(unsigned int cpu, struct task_struct *task);

#define cpu_pda(i) (_cpu_pda[i])

struct task_struct;

id_t get_cpu_id_from_task(struct task_struct*);

static inline u64
get_this_pda()
{
	u64 tp = get_tp();
	struct task_struct* ts = tp; /* struct task_struct* */
	//id_t cpu_id = ts->cpu_id;
	id_t cpu_id = get_cpu_id_from_task(ts);
//	id_t cpu_id = 0;
	struct RISCV_pda* pda_ptr = _cpu_pda[cpu_id];
	return (u64)pda_ptr;
}

/* 
 * There is no fast way to get the base address of the PDA, all the accesses
 * have to mention %fs/%gs.  So it needs to be done this Torvaldian way.
 */ 
#define sizeof_field(type,field)  (sizeof(((type *)0)->field))
#define typeof_field(type,field)  typeof(((type *)0)->field)

extern void __bad_pda_field(void);

#define pda_offset(field) offsetof(struct RISCV_pda, field)


#define pda_to_op(op,field,val)															\
do {																		\
	typedef typeof_field(struct RISCV_pda, field) T__;											\
	u64 pda = get_this_pda();																							\
	switch (sizeof_field(struct RISCV_pda, field)) {											\
		case 1:																\
			asm volatile(op "b %0, %2(%1)" :: "ri" ((T__)val), "r"(pda),  "i"(pda_offset(field)) : "memory"); break; 	\
		case 2:																\
			asm volatile(op "h %0, %2(%1)" :: "ri" ((T__)val), "r"(pda),  "i"(pda_offset(field)) : "memory"); break; 	\
		case 4:																\
			asm volatile(op "w %0, %2(%1)" :: "ri" ((T__)val), "r"(pda),  "i"(pda_offset(field)) : "memory"); break; 	\
		case 8:																\
			asm volatile(op "d %0,  %2(%1)" :: "ri" ((T__)val), "r"(pda),  "i"(pda_offset(field)) : "memory"); break; 	\
		default: __bad_pda_field();													\
       }																	\
} while (0)


#define pda_from_op(op,field) ({														\
        typeof_field(struct RISCV_pda, field) ret__; 												\
				u64 pda = get_this_pda();																				\
        switch (sizeof_field(struct RISCV_pda, field)) { 											\
		case 1: 															\
			asm volatile(op "b %0, %2(%1)": "=r" (ret__) : "r"(pda), "i"(pda_offset(field)):"memory"); break;		\
		case 2: 															\
			asm volatile(op "h %0, %2(%1)" : "=r" (ret__) : "r"(pda), "i"(pda_offset(field)):"memory"); break;		\
		case 4: 															\
			asm volatile(op "w %0, %2(%1)" : "=r" (ret__) : "r"(pda), "i"(pda_offset(field)):"memory"); break;		\
		case 8: 															\
			asm volatile(op "d %0,  %2(%1)" : "=r" (ret__) : "r"(pda), "i"(pda_offset(field)):"memory"); break;		\
		default: __bad_pda_field(); 													\
       } 																	\
       ret__; })


#define read_pda(field)      pda_from_op("l",field)
#define write_pda(field,val) pda_to_op("s",field,val)
#define add_pda(field,val)   pda_to_op("add",field,val)
#define sub_pda(field,val)   pda_to_op("sub",field,val)
#define or_pda(field,val)    pda_to_op("or",field,val)



#define early_write_pda(cpu, field, val) do { 													\
	typedef typeof_field(struct RISCV_pda, field) T__;											\
	switch (sizeof_field(struct RISCV_pda, field)) {											\
		case 1:																\
			asm volatile("sb %0, %2(%1)" :: "ri" ((T__)val), "r"(cpu_pda(cpu)),  "i"(pda_offset(field)) : "memory"); break; 	\
		case 2:																\
			asm volatile("sh %0, %2(%1)" :: "ri" ((T__)val), "r"(cpu_pda(cpu)),  "i"(pda_offset(field)) : "memory"); break; 	\
		case 4:																\
			asm volatile("sr  %0, %2(%1)" :: "ri" ((T__)val), "r"(cpu_pda(cpu)),  "i"(pda_offset(field)) : "memory"); break; 	\
		case 8:																\
			asm volatile("sr  %0,  %2(%1)" :: "ri" ((T__)val), "r"(cpu_pda(cpu)),  "i"(pda_offset(field)) : "memory"); break; 	\
		default: __bad_pda_field();													\
       }																	\
} while (0);


#define early_read_pda(cpu, field, val) do { 													\
	typedef typeof_field(struct RISCV_pda, field) T__;											\
	switch (sizeof_field(struct RISCV_pda, field)) {											\
		case 1: 															\
			asm volatile("lb %0, %2(%1)" : "=r" (ret__) : "r"(cpu_pda(cpu)), "i"(pda_offset(field)):"memory"); break;		\
		case 2: 															\
			asm volatile("lh %0, %2(%1)" : "=r" (ret__) : "r"(cpu_pda(cpu)), "i"(pda_offset(field)):"memory"); break;		\
		case 4: 															\
			asm volatile("lr  %0, %2(%1)" : "=r" (ret__) : "r"(cpu_pda(cpu)), "i"(pda_offset(field)):"memory"); break;		\
		case 8: 														\
			asm volatile("lr  %0,  %2(%1)" : "=r" (ret__) : "r"(cpu_pda(cpu)), "i"(pda_offset(field)):"memory"); break;		\
		default: __bad_pda_field(); 													\
       }																	\
} while (0);


#endif

#define PDA_STACKOFFSET (5*8)

#endif /* _RISCV_PDA_H */
