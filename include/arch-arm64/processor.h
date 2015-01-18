/*
 * include/asm-x86_64/processor.h
 *
 * Copyright (C) 1994 Linus Torvalds
 */

#ifndef _ARM_64_PROCESSOR_H
#define _ARM_64_PROCESSOR_H

#include <arch/segment.h>
#include <arch/page.h>
#include <arch/types.h>
#include <arch/sigcontext.h>
#include <arch/cpufeature.h>
/* #include <linux/threads.h> */
#include <arch/msr.h>
#include <arch/current.h>
#include <arch/system.h>
/* #include <arch/mmsegment.h> */
#include <arch/percpu.h>
/* #include <lwk/personality.h> */
#include <lwk/cpumask.h>
#include <lwk/cache.h>


typedef struct {
	uint64_t
		t0sz    :6,
		res0_0	:1,
		epd0	:1,
		irgn0	:2,
		orgn0	:2,
		sh0		:2,
		tg0		:2,
		t1sz	:6,
		a1		:1,
		epd1	:1,
		irgn1	:2,
		orgn1	:2,
		sh1		:2,
		tg1		:2,
		ips		:3,
		res0_1	:1,
		as		:1,
		tbi0	:1,
		tbi1	:1,
		resrved0:25;
} tcr_el1;

static inline tcr_el1 get_tcr_el1()
{
	tcr_el1 tcr;
	__asm__ __volatile__("mrs %0, tcr_el1\n":"=r"(tcr));
	return tcr;
}

static inline unsigned long get_ttbr1_el1()
{
	unsigned long tmp;
	__asm__ __volatile__("mrs %0, ttbr1_el1\n":"=r"(tmp));
	return tmp;
}

static inline unsigned long get_ttbr0_el1()
{
	unsigned long tmp;
	__asm__ __volatile__("mrs %0, ttbr0_el1\n":"=r"(tmp));
	return tmp;
}

struct cpu_context {
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long fp;
    unsigned long sp;
    unsigned long pc;
    unsigned long sp0;
    unsigned long usersp;
};

struct thread_struct {
    struct cpu_context  cpu_context;    /* cpu context */
    unsigned long       tp_value;
   // struct fpsimd_state fpsimd_state;
    unsigned long       fault_address;  /* fault info */
    //struct debug_info   debug;      /* debugging */
};

#define TF_MASK		0x00000100
#define IF_MASK		0x00000200
#define IOPL_MASK	0x00003000
#define NT_MASK		0x00004000
#define VM_MASK		0x00020000
#define AC_MASK		0x00040000
#define VIF_MASK	0x00080000	/* virtual interrupt flag */
#define VIP_MASK	0x00100000	/* virtual interrupt pending */
#define ID_MASK		0x00200000

#define desc_empty(desc) \
               (!((desc)->a | (desc)->b))

#define desc_equal(desc1, desc2) \
               (((desc1)->a == (desc2)->a) && ((desc1)->b == (desc2)->b))

/*
 * Default implementation of macro that returns current
 * instruction pointer ("program counter").
 */
#define current_text_addr()

//({ void *pc; asm volatile("leaq 1f(%%rip),%0\n1:":"=r"(pc)); pc; })

#define X86_VENDOR_INTEL 0
#define X86_VENDOR_CYRIX 1
#define X86_VENDOR_AMD 2
#define X86_VENDOR_UMC 3
#define X86_VENDOR_NEXGEN 4
#define X86_VENDOR_CENTAUR 5
#define X86_VENDOR_RISE 6
#define X86_VENDOR_TRANSMETA 7
#define X86_VENDOR_NUM 8
#define X86_VENDOR_UNKNOWN 0xff

extern char ignore_irq13;

extern void identify_cpu(void);

/*
 * EFLAGS bits
 */
#define X86_EFLAGS_CF	0x00000001 /* Carry Flag */
#define X86_EFLAGS_PF	0x00000004 /* Parity Flag */
#define X86_EFLAGS_AF	0x00000010 /* Auxillary carry Flag */
#define X86_EFLAGS_ZF	0x00000040 /* Zero Flag */
#define X86_EFLAGS_SF	0x00000080 /* Sign Flag */
#define X86_EFLAGS_TF	0x00000100 /* Trap Flag */
#define X86_EFLAGS_IF	0x00000200 /* Interrupt Flag */
#define X86_EFLAGS_DF	0x00000400 /* Direction Flag */
#define X86_EFLAGS_OF	0x00000800 /* Overflow Flag */
#define X86_EFLAGS_IOPL	0x00003000 /* IOPL mask */
#define X86_EFLAGS_NT	0x00004000 /* Nested Task */
#define X86_EFLAGS_RF	0x00010000 /* Resume Flag */
#define X86_EFLAGS_VM	0x00020000 /* Virtual Mode */
#define X86_EFLAGS_AC	0x00040000 /* Alignment Check */
#define X86_EFLAGS_VIF	0x00080000 /* Virtual Interrupt Flag */
#define X86_EFLAGS_VIP	0x00100000 /* Virtual Interrupt Pending */
#define X86_EFLAGS_ID	0x00200000 /* CPUID detection flag */

/*
 * Intel CPU features in CR4
 */
#define X86_CR4_VME		0x0001	/* enable vm86 extensions */
#define X86_CR4_PVI		0x0002	/* virtual interrupts flag enable */
#define X86_CR4_TSD		0x0004	/* disable time stamp at ipl 3 */
#define X86_CR4_DE		0x0008	/* enable debugging extensions */
#define X86_CR4_PSE		0x0010	/* enable page size extensions */
#define X86_CR4_PAE		0x0020	/* enable physical address extensions */
#define X86_CR4_MCE		0x0040	/* Machine check enable */
#define X86_CR4_PGE		0x0080	/* enable global pages */
#define X86_CR4_PCE		0x0100	/* enable performance counters at ipl 3 */
#define X86_CR4_OSFXSR		0x0200	/* enable fast FPU save and restore */
#define X86_CR4_OSXMMEXCPT	0x0400	/* enable unmasked SSE exceptions */

#ifdef CONFIG_VM86
#define X86_VM_MASK X86_EFLAGS_VM
#else
#define X86_VM_MASK 0 /* No VM86 support */
#endif



/*
 * Save the cr4 feature set we're using (ie
 * Pentium 4MB enable and PPro Global page
 * enable), so that any CPU's that boot up
 * after us can get the correct flags.
 */
extern unsigned long mmu_cr4_features;

static inline void set_in_cr4 (unsigned long mask)
{
	mmu_cr4_features |= mask;
#if 0
	__asm__("movq %%cr4,%%rax\n\t"
		"orq %0,%%rax\n\t"
		"movq %%rax,%%cr4\n"
		: : "irg" (mask)
		:"ax");
#endif
}

static inline void clear_in_cr4 (unsigned long mask)
{
	mmu_cr4_features &= ~mask;

#if 0
	__asm__("movq %%cr4,%%rax\n\t"
		"andq %0,%%rax\n\t"
		"movq %%rax,%%cr4\n"
		: : "irg" (~mask)
		:"ax");
#endif
}


/*
 * Size of io_bitmap.
 */
#define IO_BITMAP_BITS  65536
#define IO_BITMAP_BYTES (IO_BITMAP_BITS/8)
#define IO_BITMAP_LONGS (IO_BITMAP_BYTES/sizeof(long))
#define IO_BITMAP_OFFSET offsetof(struct tss_struct,io_bitmap)
#define INVALID_IO_BITMAP_OFFSET 0x8000

struct i387_fxsave_struct {
	u16	cwd;
	u16	swd;
	u16	twd;
	u16	fop;
	u64	rip;
	u64	rdp; 
	u32	mxcsr;
	u32	mxcsr_mask;
	u32	st_space[32];	/* 8*16 bytes for each FP-reg = 128 bytes */
	u32	xmm_space[64];	/* 16*16 bytes for each XMM-reg = 256 bytes */
	u32	padding[24];
} __attribute__ ((aligned (16)));

union i387_union {
	struct i387_fxsave_struct	fxsave;
};

struct tss_struct {
	u32 reserved1;
	u64 rsp0;	
	u64 rsp1;
	u64 rsp2;
	u64 reserved2;
	u64 ist[7];
	u32 reserved3;
	u32 reserved4;
	u16 reserved5;
	u16 io_bitmap_base;
	/*
	 * The extra 1 is there because the CPU will access an
	 * additional byte beyond the end of the IO permission
	 * bitmap. The extra byte must be all 1 bits, and must
	 * be within the limit. Thus we have:
	 *
	 * 128 bytes, the bitmap itself, for ports 0..0x3ff
	 * 8 bytes, for an extra "long" of ~0UL
	 */
	unsigned long io_bitmap[IO_BITMAP_LONGS + 1];
} __attribute__((packed));// ____cacheline_aligned;

DECLARE_PER_CPU(struct tss_struct,tss);

#ifdef CONFIG_X86_VSMP
#define ARCH_MIN_TASKALIGN	(1 << INTERNODE_CACHE_SHIFT)
#define ARCH_MIN_MMSTRUCT_ALIGN	(1 << INTERNODE_CACHE_SHIFT)
#else
#define ARCH_MIN_TASKALIGN	16
#define ARCH_MIN_MMSTRUCT_ALIGN	0
#endif

#if 0
struct thread_struct {
	unsigned long	rsp0;
	unsigned long	rsp;
	unsigned long 	userrsp;	/* Copy from PDA */ 
	unsigned long	fs;
	unsigned long	gs;
	unsigned short	es, ds, fsindex, gsindex;	
/* Hardware debugging registers */
	unsigned long	debugreg0;  
	unsigned long	debugreg1;  
	unsigned long	debugreg2;  
	unsigned long	debugreg3;  
	unsigned long	debugreg6;  
	unsigned long	debugreg7;  
/* fault info */
	unsigned long	cr2, trap_no, error_code;
/* floating point info */
	union i387_union	i387  __attribute__((aligned(16)));
/* IO permissions. the bitmap could be moved into the GDT, that would make
   switch faster for a limited number of ioperm using tasks. -AK */
	int		ioperm;
	unsigned long	*io_bitmap_ptr;
	unsigned io_bitmap_max;
/* cached TLS descriptors. */
	u64 tls_array[GDT_ENTRY_TLS_ENTRIES];
} __attribute__((aligned(16)));
#endif

#define BOOTSTRAP_THREAD  { \
	.rsp0 = (unsigned long)&bootstrap_stack + sizeof(bootstrap_stack) \
}

#define BOOTSTRAP_TSS  { \
	.rsp0 = (unsigned long)&bootstrap_stack + sizeof(bootstrap_stack) \
}

#define INIT_MMAP \
{ &init_mm, 0, 0, NULL, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL }

#define get_debugreg(var, register)

#if 0
\
		__asm__("movq %%db" #register ", %0"		\
			:"=r" (var))
#endif

#define set_debugreg(value, register)

#if 0
			 \
		__asm__("movq %0,%%db" #register		\
			: /* no output */			\
			:"r" (value))
#endif
struct mm_struct;

/* Free all resources held by a thread. */
extern void release_thread(struct task_struct *);

/* Prepare to copy thread state - unlazy all lazy status */
extern void prepare_to_copy(struct task_struct *tsk);

/*
 * create a kernel thread without removing it from tasklists
 */
extern long kernel_thread(int (*fn)(void *), void * arg, unsigned long flags);

/*
 * Return saved PC of a blocked thread.
 * What is this good for? it will be always the scheduler or ret_from_fork.
 */
#define thread_saved_pc(t) (*(unsigned long *)((t)->thread.rsp - 8))

extern unsigned long get_wchan(struct task_struct *p);
#define task_pt_regs(tsk) ((struct pt_regs *)(tsk)->thread.rsp0 - 1)
#define KSTK_EIP(tsk) (task_pt_regs(tsk)->rip)
#define KSTK_ESP(tsk) -1 /* sorry. doesn't work for syscall. */


struct microcode_header {
	unsigned int hdrver;
	unsigned int rev;
	unsigned int date;
	unsigned int sig;
	unsigned int cksum;
	unsigned int ldrver;
	unsigned int pf;
	unsigned int datasize;
	unsigned int totalsize;
	unsigned int reserved[3];
};

struct microcode {
	struct microcode_header hdr;
	unsigned int bits[0];
};

typedef struct microcode microcode_t;
typedef struct microcode_header microcode_header_t;

/* microcode format is extended from prescott processors */
struct extended_signature {
	unsigned int sig;
	unsigned int pf;
	unsigned int cksum;
};

struct extended_sigtable {
	unsigned int count;
	unsigned int cksum;
	unsigned int reserved[3];
	struct extended_signature sigs[0];
};


#define ASM_NOP1 K8_NOP1
#define ASM_NOP2 K8_NOP2
#define ASM_NOP3 K8_NOP3
#define ASM_NOP4 K8_NOP4
#define ASM_NOP5 K8_NOP5
#define ASM_NOP6 K8_NOP6
#define ASM_NOP7 K8_NOP7
#define ASM_NOP8 K8_NOP8

/* Opteron nops */
#define K8_NOP1 ".byte 0x90\n"
#define K8_NOP2	".byte 0x66,0x90\n" 
#define K8_NOP3	".byte 0x66,0x66,0x90\n" 
#define K8_NOP4	".byte 0x66,0x66,0x66,0x90\n" 
#define K8_NOP5	K8_NOP3 K8_NOP2 
#define K8_NOP6	K8_NOP3 K8_NOP3
#define K8_NOP7	K8_NOP4 K8_NOP3
#define K8_NOP8	K8_NOP4 K8_NOP4

#define ASM_NOP_MAX 8

/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static inline void rep_nop(void)
{
	//__asm__ __volatile__("rep;nop": : :"memory");
}

/* Stop speculative execution */
static inline void sync_core(void)
{ 
	int tmp;
	//asm volatile("cpuid" : "=a" (tmp) : "0" (1) : "ebx","ecx","edx","memory");
} 

#define cpu_has_fpu 1

#define ARCH_HAS_PREFETCH
static inline void prefetch(void *x) 
{ 
	//asm volatile("prefetcht0 %0" :: "m" (*(unsigned long *)x));
} 

#define ARCH_HAS_PREFETCHW 1
static inline void prefetchw(void *x) 
{ 
	//asm volatile("prefetchtw %0" :: "m" (*(unsigned long *)x));
} 

#define ARCH_HAS_SPINLOCK_PREFETCH 1

#define spin_lock_prefetch(x)  prefetchw(x)

#define cpu_relax()   rep_nop()

static inline void serialize_cpu(void)
{
	//__asm__ __volatile__ ("cpuid" : : : "ax", "bx", "cx", "dx");
}

static inline void __monitor(const void *eax, unsigned long ecx,
		unsigned long edx)
{
	/* "monitor %eax,%ecx,%edx;" */
#if 0
	asm volatile(
		".byte 0x0f,0x01,0xc8;"
		: :"a" (eax), "c" (ecx), "d"(edx));
#endif
}

static inline void __mwait(unsigned long eax, unsigned long ecx)
{
	/* "mwait %eax,%ecx;" */
#if 0
	asm volatile(
		".byte 0x0f,0x01,0xc9;"
		: :"a" (eax), "c" (ecx));
#endif
}

#define stack_current() \
({								\
	struct thread_info *ti;					\
	/*asm("andq %%rsp,%0; ":"=r" (ti) : "0" (CURRENT_MASK));*/	\
	ti->task;					\
})

#define cache_line_size() (boot_cpu_data.arch.x86_cache_alignment)

extern unsigned long boot_option_idle_override;
/* Boot loader type from the setup header */
extern int bootloader_type;

#define HAVE_ARCH_PICK_MMAP_LAYOUT 1

#endif /* _ARM_64_PROCESSOR_H */
