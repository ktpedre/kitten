/*
   Nicholas Gordon, Sandia National Labs 2022
   nicholasgordon@fastmail.com
*/

#include <lwk/kernel.h>
#include <lwk/init.h>
#include <lwk/spinlock.h>
#include <lwk/cpuinfo.h>
#include <lwk/smp.h>
#include <lwk/time.h>
#include <lwk/interrupt.h>
#include <arch/io.h>
#include <arch/pda.h>

//#include <arch/irqchip.h>
#include <arch/time.h>
#include <arch/of.h>

#define MSIP_OFFSET_CLINT0     0x0
#define MTIMECMP_OFFSET_CLINT0 0x4000
#define MTIME_OFFSET_CLINT0    0xbff8

static vaddr_t clint0_base_vaddr = NULL;
static paddr_t clint0_base_paddr = NULL;
static unsigned long clint0_size = 0;

static vaddr_t my_mtimecmp = NULL;

static void
__reload_timer()
{
    *(unsigned long*)(clint0_base_vaddr+MTIME_OFFSET_CLINT0) = 0;
    csr_set(CSR_IE, IE_TIE);
    sbi_set_timer(get_cycles64()+read_pda(timer_reload_value));
}

static irqreturn_t
__timer_tick(int irq, void * dev_id)
{
    irqreturn_t irqret = IRQ_HANDLED;
    csr_clear(CSR_IE, IE_TIE);

    printk("Tick!\n");


    expire_timers();

    // This causes schedule() to be called right before
    // the next return to user-space
    set_bit(TF_NEED_RESCHED_BIT, &current->arch.flags);

    init_cycles2ns(1000000);

    __reload_timer();

    return irqret;
}

static void
__riscv_timer_core_init()
{
    my_mtimecmp = (unsigned long*)(clint0_base_vaddr+MTIMECMP_OFFSET_CLINT0)+this_cpu;
    irq_request(5, __timer_tick, 0, "timer", NULL);
    printk("Setting core-local mtimecmp register to 0x%p\n", my_mtimecmp);
}

static void
__riscv_timer_set_timer_freq(unsigned int hz)
{
    if (my_mtimecmp == NULL) {
        panic("Core-local init not done yet!\n");
    }

    printk("Setting timer frequency to %d HZ\n", hz);

    csr_set(CSR_IE, IE_TIE);
    sbi_set_timer(get_cycles64()+(hz*10000000));
    //my_mtimecmp = hz;

    write_pda(timer_reload_value, hz*10000000);

    printk("Timer enabled and running\n");
}

static struct arch_timer riscv_timer = {
	.name               = "RISCV",
	.dt_node            = NULL,
	.core_init          = __riscv_timer_core_init,
	.set_timer_freq     = __riscv_timer_set_timer_freq,
};

int
riscv_timer_init(struct device_node* dt_node)
{
    int ret = 0;
    u32 regs[8] = {[0 ... 7] = 0};

    ret = of_property_read_u32_array(dt_node, "reg", (u32 *)regs, 4);

    if (ret != 0) {
        printk("name %s\ntype %s\n", dt_node->name, dt_node->type);

        panic("Couldn't read clint0 registers from device tree (ret=%d)\n", ret);
    }

    clint0_base_paddr = (regs[0] << 32) | regs[1];
    clint0_size       = (regs[2] << 32) | regs[3];

    printk("CLINT0 at: 0x%p [%d bytes]\n", clint0_base_paddr, clint0_size);

    clint0_base_vaddr = ioremap_nocache(clint0_base_paddr, clint0_size);

    if (clint0_base_vaddr == NULL) {
        panic("Could not map CLINT0 MMIO into kernel aspace!\n");
    }

    printk("CLINT0 virt addr: 0x%p\n", clint0_base_vaddr);

    //struct arch_cpuinfo * const arch_info = &cpu_info[this_cpu].arch;

    /* NMG The CPU frequency appears to not be well-defined when on
     * QEMU; the timebase frequency is defined but clock_frequency,
     * which is supposed to contain this value, is not. There is not
     * an architectural register like on ARM that tells you the
     * frequency of the hart. */
    //arch_info->cur_cpu_khz = cpu_khz;

    riscv_timer.dt_node = dt_node;
    arch_timer_register(&riscv_timer);

    return ret;
}
