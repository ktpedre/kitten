#include <lwk/types.h>

#include <arch/io.h>
#include <arch/secure.h>
#include <arch/memblock.h>

#define BIT(nr)				((unsigned long long)(1) << (nr))

#define REG_MSK_SHIFT	16

#ifndef WMSK_BIT
#define WMSK_BIT(nr)		BIT((nr) + REG_MSK_SHIFT)
#endif

/* set one bit with write mask */
#ifndef BIT_WITH_WMSK
#define BIT_WITH_WMSK(nr)	(BIT(nr) | WMSK_BIT(nr))
#endif

#ifndef BITS_SHIFT
#define BITS_SHIFT(bits, shift)	(bits << (shift))
#endif

#ifndef BITS_WITH_WMASK
#define BITS_WITH_WMASK(bits, msk, shift)\
	(BITS_SHIFT(bits, shift) | BITS_SHIFT(msk, (shift + REG_MSK_SHIFT)))
#endif

static void* sgrf_vaddr = NULL;

static void sgrf_ddr_rgn_global_bypass(uint32_t bypass)
{
	if (bypass)
		/* set bypass (non-secure regions) for whole ddr regions */
		writel(SGRF_DDR_RGN_BYPS,
		       sgrf_vaddr + SGRF_DDRRGN_CON0_16(16));
	else
		/* cancel bypass for whole ddr regions */
		writel(SGRF_DDR_RGN_NO_BYPS,
		       sgrf_vaddr + SGRF_DDRRGN_CON0_16(16));
}

/**
 * There are 8 + 1 regions for DDR secure control:
 * DDR_RGN_0 ~ DDR_RGN_7: Per DDR_RGNs grain size is 1MB
 * DDR_RGN_X - the memories of exclude DDR_RGN_0 ~ DDR_RGN_7
 *
 * DDR_RGN_0 - start address of the RGN0
 * DDR_RGN_8 - end address of the RGN0
 * DDR_RGN_1 - start address of the RGN1
 * DDR_RGN_9 - end address of the RGN1
 * ...
 * DDR_RGN_7 - start address of the RGN7
 * DDR_RGN_15 - end address of the RGN7
 * DDR_RGN_16 - bit 0 ~ 7 is bitmap for RGN0~7 secure,0: disable, 1: enable
 *              bit 8 is setting for RGNx, the rest of the memory and region
 *                which excludes RGN0~7, 0: disable, 1: enable
 *              bit 9, the global secure configuration via bypass, 0: disable
 *                bypass, 1: enable bypass
 *
 * @rgn - the DDR regions 0 ~ 7 which are can be configured.
 * @st - start address to set as secure
 * @sz - length of area to set as secure
 * The @st_mb and @ed_mb indicate the start and end addresses for which to set
 * the security, and the unit is megabyte. When the st_mb == 0, ed_mb == 0, the
 * address range 0x0 ~ 0xfffff is secure.
 *
 * For example, if we would like to set the range [0, 32MB) is security via
 * DDR_RGN0, then rgn == 0, st_mb == 0, ed_mb == 31.
 */
static void sgrf_ddr_rgn_config(uint32_t rgn,
				uintptr_t st, size_t sz)
{
	uintptr_t ed = st + sz;
	uintptr_t st_mb, ed_mb;

	/*
	 * assert(rgn <= 7);
	 * assert(st < ed);
	 * 
	 * /\* check aligned 1MB *\/
	 * assert(st % (1 << 20) == 0);
	 * assert(ed % (1 << 20));
	 */

	st_mb = st / (1 << 20);
	ed_mb = ed / (1 << 20);

	/* set ddr region addr start */
	printk("sgrf_vaddr 0x%p SGRF_DDRRGN_CON0_16(rgn) 0x%p\n", sgrf_vaddr, SGRF_DDRRGN_CON0_16(rgn));
	printk("sgrf_vaddr + SGRF_DDRRGN_CON0_16(rgn) 0x%p\n", sgrf_vaddr + SGRF_DDRRGN_CON0_16(rgn));
	writel(BITS_WITH_WMASK(st_mb, SGRF_DDR_RGN_0_16_WMSK, 0),
	       sgrf_vaddr + SGRF_DDRRGN_CON0_16(rgn));

	/* set ddr region addr end */
	printk("sgrf_vaddr 0x%p SGRF_DDRRGN_CON0_16(rgn + 8) 0x%p\n", sgrf_vaddr, SGRF_DDRRGN_CON0_16(rgn + 8));
	printk("sgrf_vaddr + SGRF_DDRRGN_CON0_16(rgn + 8) 0x%p\n", sgrf_vaddr + SGRF_DDRRGN_CON0_16(rgn + 8));
	writel(BITS_WITH_WMASK((ed_mb - 1), SGRF_DDR_RGN_0_16_WMSK, 0),
	       sgrf_vaddr + SGRF_DDRRGN_CON0_16(rgn + 8));

	printk("sgrf_vaddr 0x%p SGRF_DDRRGN_CON0_16(16) 0x%p\n", sgrf_vaddr, SGRF_DDRRGN_CON0_16(16));
	printk("sgrf_vaddr + SGRF_DDRRGN_CON0_16(16) 0x%p\n", sgrf_vaddr + SGRF_DDRRGN_CON0_16(16));
	writel(BIT_WITH_WMSK(rgn),
	       sgrf_vaddr + SGRF_DDRRGN_CON0_16(16));
}


int
setup_secure()
{
	int ret = 0;

	sgrf_vaddr = ioremap_nocache(SGRF_BASE, (64 * 1024));
	if (!sgrf_vaddr) {
		panic("Can't map in SGRF\n");
	}
	printk("SGRF physical: 0x%p\n", SGRF_BASE);
	printk("SGRF  virtual: 0x%p\n", sgrf_vaddr);

	return ret;
}

int
secure_memory(phys_addr_t start, phys_addr_t end)
{
	int ret = 0;

	sgrf_ddr_rgn_config(0, start, end-start);
	sgrf_ddr_rgn_global_bypass(0);

	return ret;
}
