#include <arch/page.h>

extern unsigned long phys_base;

/**
 * This converts a kernel virtual address to a physical address.
 *
 * NOTE: This function only works for kernel virtual addresses in the kernel's
 *       identity mapping of all of physical memory. It will not work for the
 *       fixmap, vmalloc() areas, or any other type of virtual address.
 */

phys_addr_t __virt_to_phys(unsigned long x)
{
	/*
	 * Boundary checking aginst the kernel linear mapping space.
	 */
	WARN(!is_linear_mapping(x) && !is_kernel_mapping(x),
	     "virt_to_phys used for non-linear address: %pK (%pS)\n",
	     (void *)x, (void *)x);

	return __va_to_pa_nodebug(x);
}

phys_addr_t __phys_addr_symbol(unsigned long x)
{
	unsigned long kernel_start = kernel_map.virt_addr;
	unsigned long kernel_end = (unsigned long)_end;

	/*
	 * Boundary checking aginst the kernel image mapping.
	 * __pa_symbol should only be used on kernel symbol addresses.
	 */
	VIRTUAL_BUG_ON(x < kernel_start || x > kernel_end);

	return __va_to_pa_nodebug(x);
}
