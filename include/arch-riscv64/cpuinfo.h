#ifndef _ARM64_CPUINFO_H
#define _ARM64_CPUINFO_H

/**
 * arch_cpuinfo.x86_cache_size first dimension indicies.
 * and
 * arch_cpuinfo.x86_tlbsize first dimension indicies.
 */
#define INST	0	/* Instruction */
#define DATA	1	/* Data */
#define UNIF	2	/* Unified Instruction and Data */

/**
 * arch_cpuinfo.x86_cache_size second dimension indices.
 * and
 * arch_cpuinfo.x86_tlbsize second dimension indices.
 */
#define L1	0
#define L2	1
#define L3	2
#define L4      3
#define L5      4
#define L6      5
#define L7      6


/**
 * arch_cpuinfo.x86_tlbsize third dimension indices.
 */
#define PAGE_4KB	0
#define PAGE_2MB	1
#define PAGE_1GB	2

/**
 * Architecture specific CPU information and hardware bug flags.
 * CPU info is kept separately for each CPU.
 */
struct arch_cpuinfo {
    uint8_t  riscv_vendor;          /* CPU vendor */
    uint8_t  riscv_variant;         /* CPU variant */
    uint8_t  riscv_arch;            /* CPU architecture */
    uint8_t  riscv_partnum;         /* CPU part number */
    uint8_t  riscv_revision;        /* CPU revision */
    uint16_t riscv_cache_size[3][7];  /* [I|D|U][LEVEL], in KB */
    uint16_t riscv_cache_line[3][7];  /* [I|D|U][LEVEL], in bytes */
    uint32_t riscv_capability;
    uint8_t  riscv_virt_bits;       /* Bits of virt address space */
    uint8_t  riscv_phys_bits;       /* Bits of phys address space */
    uint8_t  riscv_pkg_cores;         /* Number of cores in this CPU's package */
    uint32_t riscv_power;           /* Power management features */
    uint32_t cur_cpu_khz;           /* Current CPU freq. in KHz (need to calibrate) */
    uint32_t tsc_khz;
    uint32_t timer_hz; 		    /* Timer frequency in Hz */
    uint32_t cpu_phys_id;           /* linear cpu id */
    uint8_t  cpu_core_id;
    uint8_t  cpu_cluster_id;
    uint8_t  cpu_affinity_2;
    uint8_t  cpu_affinity_3;
};

extern struct cpuinfo boot_cpu_data;

struct cpuinfo;
extern void print_arch_cpuinfo(struct cpuinfo *);
extern void early_identify_cpu(struct cpuinfo *);

#endif
