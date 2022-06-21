#ifndef _ARCH_RISCV_PAGE_TABLE_H
#define _ARCH_RISCV_PAGE_TABLE_H

#include <arch/pgtable.h>

typedef struct {
				union {
								uint64_t value;
								struct {
												uint64_t offset : 12; // 00-11
												uint64_t vpn0   : 9;  // 12-20
												uint64_t vpn1   : 9;  // 21-28
												uint64_t vpn2   : 9;  // 28-37
												uint64_t rsvd   : 26; // 38-63
								};
				};
} pte_vaddr_t;

typedef struct {
				union {
								uint64_t value;
								struct {
												uint64_t offset : 12; // 00-11
												uint64_t ppn0   : 9;  // 12-20
												uint64_t ppn1   : 9;  // 21-28
												uint64_t ppn2   : 9;  // 28-37
												uint64_t rsvd   : 26; // 38-63
								};
				};
} pte_paddr_t;

typedef struct {
				union {
								uint64_t value;
								struct {
												uint64_t valid : 1;
												uint64_t read  : 1;
												uint64_t write : 1;
												uint64_t exec  : 1;
												uint64_t user  : 1;
												uint64_t global: 1;
												uint64_t acc   : 1;
												uint64_t dirty : 1;
												uint64_t rsw   : 2;
												uint64_t ppn0  : 9;
												uint64_t ppn1  : 9;
												uint64_t ppn2  : 26;
												uint64_t rsvd  : 10;
								};
				};
} xpte_t;

typedef xpte_t xpte_leaf_t;

/* Extract whatever this PTE thinks is the physical address of the
 * next page. This is a uniform action, making the page table
 * traversal simpler.
 */
static inline paddr_t
xpte_paddr (xpte_t* pte)
{
		return (paddr_t)( ( (pte->ppn2 << 28) ||
												(pte->ppn1 << 19) ||
												(pte->ppn0 << 10) )
											<< PAGE_SHIFT );
}

static inline bool
is_leaf (xpte_t* pte)
{
				return pte->read | pte->write | pte->exec;
}


#endif /* _ARCH_RISCV_PAGE_TABLE_H */
