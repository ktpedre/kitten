/** \file
 * Initial C entry point for lwk.
 */
#include <lwk/init.h>
#include <lwk/kernel.h>
#include <lwk/string.h>
#include <lwk/screen_info.h>
#include <lwk/params.h>
#include <lwk/smp.h>
#include <lwk/cpuinfo.h>
#include <lwk/tlbflush.h>
#include <arch/bootsetup.h>
#include <arch/sections.h>
#include <arch/pda.h>
#include <arch/processor.h>
//#include <arch/desc.h>
#include <arch/proto.h>
#include <arch/page.h>
#include <arch/pgtable.h>

/**
 * Data passed to the kernel by the bootloader.
 *
 * NOTE: This is marked as __initdata so it goes away after the
 *       kernel bootstrap process is complete.
 */
char x86_boot_params[BOOT_PARAM_SIZE] __initdata = {0,};

/**
 * Interrupt Descriptor Table (IDT) descriptor.
 *
 * This descriptor contains the length of the IDT table and a
 * pointer to the table.  The lidt instruction (load IDT) requires
 * this format.
 */
//struct desc_ptr idt_descr = { 256 * 16 - 1, (unsigned long) idt_table };

/**
 * Array of pointers to each CPU's per-processor data area.
 * The array is indexed by CPU ID.
 */
struct ARM64_pda *_cpu_pda[NR_CPUS] __read_mostly;

/**
 * Array of per-processor data area structures, one per CPU.
 * The array is indexed by CPU ID.
 */
struct ARM64_pda boot_cpu_pda[NR_CPUS] __cacheline_aligned;

/**
 * This unmaps virtual addresses [0,512GB) by clearing the first entry in the
 * PGD/PML4T. After this executes, accesses to virtual addresses [0,512GB) will
 * cause a page fault.
 */
static void __init
zap_identity_mappings(void)
{
	//pgd_t *pgd = pgd_offset_k(0UL);
	//pgd_clear(pgd);
	//__flush_tlb();
}

/**
 * Determines the address of the kernel boot command line.
 */
static char * __init
find_command_line(void)
{
	unsigned long new_data;

	new_data = *(u32 *) (x86_boot_params + NEW_CL_POINTER);
	if (!new_data) {
		if (OLD_CL_MAGIC != * (u16 *) OLD_CL_MAGIC_ADDR) {
			return NULL;
		}
		new_data = OLD_CL_BASE_ADDR + * (u16 *) OLD_CL_OFFSET;
	}
	return __va(new_data);
}

