#ifndef _ARCH_RISCV_PAGE_TABLE_H
#define _ARCH_RISCV_PAGE_TABLE_H

#include <arch/pgtable.h>

typedef struct {
		uint64_t
				valid : 1,
				read  : 1,
				write : 1,
				exec  : 1,
				user  : 1,
				global: 1,
				acc   : 1,
				dirty : 1,
				rsw   : 1,
				ppn0  : 9,
				ppn1  : 9,
				ppn2  : 26,
				rsvd  : 10
} xpte_t;

/* Extract whatever this PTE thinks is the physical address of the
 * next page. This is a uniform action, making the page table
 * traversal simpler.
 */
static inline paddr_t
next_entry_addr (xpte_t* pte)
{
		return (paddr_t)( ( (pte->ppn2 << 28) ||
												(pte->ppn1 << 19) ||
												(pte->ppn0 << 10) )
											<< PAGE_SHIFT );
}

#endif /* _ARCH_RISCV_PAGE_TABLE_H */
