/* Copyright (c) 2007,2008 Sandia National Laboratories */

#include <lwk/kernel.h>
#include <lwk/aspace.h>
#include <lwk/task.h>
#include <lwk/bootstrap.h>
#include <arch/page.h>      /* TODO: remove */
#include <arch/pgtable.h>   /* TODO: remove */
#include <arch/page_table.h>
#include <arch/tlbflush.h>
#include <arch/cacheflush.h>
#include <lwk/bootmem.h>

extern bool bootmem_destoyed;

#ifdef CONFIG_ARM64_64K_PAGES
#error "64KB pages not supported. Aspace needs to be fully re-designed to work."
#endif

extern bool _can_print;
/**
 * Architecture specific address space initialization. This allocates a new
 * page table root for the aspace and copies the kernel page tables into it.
 */
int
arch_aspace_create(
	struct aspace *	aspace
)
{
	unsigned int i;

	// Creates only a new user page table
	/* printk("Kernel page tables do not need to be copied on RISCV (?)\n"); */
	if ((aspace->arch.pgd = kmem_get_pages(0)) == NULL)
		return -ENOMEM;

		/* Copy the current kernel page tables into the address space */
	for (i = pgd_index(PAGE_OFFSET); i < PTRS_PER_PGD; i++)
		aspace->arch.pgd[i] = bootstrap_task.aspace->arch.pgd[i];

	return 0;
}



/**
 * Architecture specific address space destruction. This frees all page table
 * memory that the aspace was using.
 */
void
arch_aspace_destroy(
	struct aspace *	aspace
)
{
	panic("arch_aspace_destroy\n");
#if 0
	unsigned int i, j, k;

	xpte_t *pgd;	/* Page Global Directory: level 0 (root of tree) */
	xpte_t *pud;	/* Page Upper Directory:  level 1 */
	xpte_t *pmd;	/* Page Middle Directory: level 2 */
	xpte_t *ptd;	/* Page Table Directory:  level 3 */

	/* Walk and then free the Page Global Directory */
	pgd = aspace->arch.pgd;
	for (i = 0; i < pgd_index(PAGE_OFFSET); i++) {
		if (!pgd[i].valid)
			continue;

		/* Walk and then free the Page Upper Directory */
		pud = __va(pgd[i].base_paddr << 12);
		for (j = 0; j < 512; j++) {
			if (pud[j].valid == 0 || is_leaf(&pud[j]))
				continue;

			/* Walk and then free the Page Middle Directory */
			pmd = __va(pud[j].base_paddr << 12);
			for (k = 0; k < 512; k++) {
				if (pmd[k].valid || !pmd[k].type)
					continue;
				
				/* Free the last level Page Table Directory */
				ptd = __va(pmd[k].base_paddr << 12);
				kmem_free_pages(ptd, 0);
			}
			kmem_free_pages(pmd, 0);
		}
		kmem_free_pages(pud, 0);
	}
	kmem_free_pages(pgd, 0);
#endif
}


/**
 * Loads the address space object's root page table pointer into the calling
 * CPU's CR3 register, causing the aspace to become active.
 */
void
arch_aspace_activate(
	struct aspace *	aspace
)
{
	//printk("activate aspace [%d] at %p\n", aspace->id, aspace->arch.pgd);
	//printk("aspace->child_list %p\n",aspace->child_list);
	//printk("&aspace->child_list %p\n",&aspace->child_list);
	//printk("(&aspace->child_list)->prev %p\n",(&aspace->child_list)->prev);

	/* printk("aspace activate pgd %p pa %p pfndown %p satp %p\n", aspace->arch.pgd, __pa(aspace->arch.pgd), */
	/* 			 PFN_DOWN(__pa(aspace->arch.pgd)), PFN_DOWN(__pa(aspace->arch.pgd)) | satp_mode); */
	barrier();
	unsigned long long step1 = aspace->arch.pgd;
	unsigned long long step2 = __pa(step1);
	unsigned long long step3 = PFN_DOWN(step2);
	unsigned long long step4 = step3 | satp_mode;
	/* unsigned long new_satp = PFN_DOWN(__pa(aspace->arch.pgd)) | satp_mode; */
	barrier();
	if (aspace->id != BOOTSTRAP_ASPACE_ID) {
		csr_write(CSR_SATP, step4);
		local_flush_tlb_all();
		/* asm volatile( */
		/* 	"sfence.vma\n" */
		/* 	"csrw satp, %0\n" */
		/* 	"sfence.vma\n" */
		/* 	"fence.i\n" */
		/* 	: */
		/* 	: "r" (PFN_DOWN(__pa(aspace->arch.pgd)) | satp_mode) */
		/* 	: "memory" */
		/* 	); */
	} else {
		// Nothing to do for the bootstrap aspace
	}
}


/**
 * Allocates a new page table and links it to a parent page table entry.
 */
static xpte_t *
alloc_page_table(
	xpte_t        * parent_pte
)
{
	xpte_t *new_table;

	if (bootmem_destoyed == true) {
		new_table = kmem_get_pages(0);
	} else {
		new_table = alloc_bootmem_aligned(PAGE_SIZE_4KB, PAGE_SIZE_4KB);
	}

	if (!new_table)
		return NULL;

	/* Simple sanity checking */
	if (parent_pte) {
		xpte_t _pte;

		memset(&_pte, 0, sizeof(_pte));
		_pte.valid     = 1;


#if 0
		_pte.AF        = 1;
		// NOTE: original code set write to be 1 for x86-64 on ARM64 AP2 should be 0
		_pte.AP2         = 0;
		// NOTE: original code set user to be 1 for x86-64 on ARM64 AP1 should also be set to 1
		_pte.AP1        = 1;
#endif

		pte_paddr_t next_pa = (pte_paddr_t) { .value = __pa(new_table) };
		_pte.ppn2 = next_pa.ppn2;
		_pte.ppn1 = next_pa.ppn1;
		_pte.ppn0 = next_pa.ppn0;

		*parent_pte = _pte;
	}

	return new_table;
}

/**
 * Locates an existing page table entry or creates a new one if none exists.
 * Returns a pointer to the page table entry.
 */
static xpte_leaf_t *
find_or_create_pte(
	struct aspace *	aspace,
	vaddr_t		vaddr,
	vmpagesize_t	pagesz
)
{
	pte_vaddr_t pte_vaddr = { .value = (uint64_t)vaddr };

	xpte_t *pgd = NULL;	/* Page Global Directory: level 1 (root of tree) */
	xpte_t *pmd = NULL;	/* Page Middle Directory: level 2 */
	xpte_t *ptd = NULL;	/* Page Table Directory:  level 3 */

	xpte_t *pge = NULL;	/* Page Global Directory Entry */
	xpte_t *pme = NULL;	/* Page Middle Directory Entry */
	xpte_t *pte = NULL;	/* Page Table Directory Entry */

	/* Calculate indices into above directories based on vaddr specified */
	unsigned int pgd_index =  pte_vaddr.vpn2 & 0x1FF;
	unsigned int pmd_index =  pte_vaddr.vpn1 & 0x1FF;
	unsigned int ptd_index =  pte_vaddr.vpn0 & 0x1FF;


	/* /\* JRL: These should either be handled OK here, or be moved to initialization time checks *\/ */
	/* { */
	/* 	if ((tcr.t0sz < 25) || (tcr.t0sz > 33)) { */
	/* 		panic("Unable to handle this starting level\n"); */
	/* 	} else if (aspace->arch.pgd == NULL) { */
	/* 		panic("Aspace has NULL PGD\n"); */
	/* 	} */
	/* } */

	if (aspace->id == BOOTSTRAP_ASPACE_ID) {
		u64 msb_mask = ~(0xffffffffffffffff) >> 26;

		if ((vaddr & msb_mask) != msb_mask) {
			panic("Invalid Bootstrap Address [vaddr=%p]\n", vaddr);
		}
	} else {
		u64 msb_mask = ~(0xffffffffffffffff) >> 26;

		if ((vaddr & msb_mask) != 0) {
			panic("Invalid Kernel/Use Address [vaddr=%p]\n", vaddr);
		}
	}


	/* Traverse the Page Global Directory */
	pgd = aspace->arch.pgd;
	pge = &pgd[pgd_index];
	if (pagesz == VM_PAGE_1GB) {
		return pge;
	} else if (!pge->valid) {
		if (!alloc_page_table(pge)) {
				return NULL;
		}
	} else if (is_leaf(pge)) {
		panic("BUG: Can't follow PGD entry, entry is a leaf.");
	}

	/* Traverse the Page Middle Directory */
	pmd = __va(xpte_paddr(pge));
	pme = &pmd[pmd_index];
	if (pagesz == VM_PAGE_2MB) {
		return pme;
	} else if (!pme->valid) {
		if (!alloc_page_table(pme)) {
				return NULL;
		}
	} else if (is_leaf(pme)) {
		panic("BUG: Can't follow PMD entry, entry is a leaf.");
	}
	
	ptd = __va(xpte_paddr(pme));
	pte = &ptd[ptd_index];
out:
	return pte;
}


/**
 * Examines a page table to determine if it has any active entries. If not,
 * the page table is freed.
 */
static int
try_to_free_table(
	xpte_t *	table,
	xpte_t *	parent_pte
)
{
	int i;

	//printk("table %p parent %p\n",table,parent_pte);
	/* Determine if the table can be freed */
	for (i = 0; i < 512; i++) {
		if (table[i].valid)
			return -1; /* Nope */
	}

	//printk("freed! %p\n",table);
	/* Yup, free the page table */
	kmem_free_pages(table, 0);
	if (parent_pte != NULL) {
		memset(parent_pte, 0, sizeof(xpte_t));
	}
	return 0;
}


/**
 * Zeros a page table entry. If the page table that the PTE was in becomes
 * empty (contains no active mappings), it is freed. Page table freeing
 * continues up to the top of the page table tree (e.g., a single call may
 * result in a PTD, PMD, and PUD being freed; the PGD is never freed by this
 * function).
 */
static void
find_and_delete_pte(
	struct aspace *	aspace,
	vaddr_t		vaddr,
	vmpagesize_t	pagesz
)
{
	pte_vaddr_t pte_vaddr = { .value = (uint64_t)vaddr };

	xpte_t *pgd = NULL;	/* Page Global Directory: level 1 (root of tree) */
	xpte_t *pmd = NULL;	/* Page Middle Directory: level 2 */
	xpte_t *ptd = NULL;	/* Page Table Directory:  level 3 */

	xpte_t *pge = NULL;	/* Page Global Directory Entry */
	xpte_t *pme = NULL;	/* Page Middle Directory Entry */
	xpte_t *pte = NULL;	/* Page Table Directory Entry */

	/* Calculated Assuming a 4KB granule */
	unsigned int pgd_index =  (pte_vaddr.vpn0 >> 30) & 0x1FF;
	unsigned int pmd_index =  (pte_vaddr.vpn1 >> 21) & 0x1FF;
	unsigned int ptd_index =  (pte_vaddr.vpn2 >> 12) & 0x1FF;

	/* JRL: These should either be handled OK here, or be moved to initialization time checks */
	/* { */
	/* 	if ((tcr.t0sz < 25) || (tcr.t0sz > 33)) { */
	/* 		panic("Unable to handle this starting level\n"); */
	/* 	} else if (aspace->arch.pgd == NULL) { */
	/* 		panic("Aspace has NULL PGD\n"); */
	/* 	} */

	/* } */

	if (aspace->id == BOOTSTRAP_ASPACE_ID) {
		u64 msb_mask = ~(0xffffffffffffffff) >> 26;

		if ((vaddr & msb_mask) != msb_mask) {
			panic("Invalid Bootstrap Address [vaddr=%p]\n", vaddr);
		}
	} else {
		u64 msb_mask = ~(0xffffffffffffffff) >> 26;

		if ((vaddr & msb_mask) != 0) {
			panic("Invalid Kernel/Use Address [vaddr=%p]\n", vaddr);
		}
	}

	pgd = aspace->arch.pgd;
	pge = &pgd[pgd_index];

	/* Traverse the Page Global Directory */
	if (!pge->valid) {
		return;
	} else if (pagesz == VM_PAGE_1GB) {
		if (!is_leaf(pge)) {
			panic("BUG: 1GB PTE has child page table attached.\n");
		}

		/* Unmap the 1GB page that this PTE was mapping */
		memset(pge, 0, sizeof(xpte_t));

		return;
	}



	/* Traverse the Page Middle Directory */
	pmd = __va(xpte_paddr(pge));
	pme = &pmd[pmd_index];
	if (!pme->valid) {
		return;
	} else if (pagesz == VM_PAGE_2MB) {
		if (!is_leaf(pme)) {
			panic("BUG: 2MB PTE has child page table attached.\n");
		}

		/* Unmap the 2MB page that this PTE was mapping */
		memset(pme, 0, sizeof(xpte_t));

		/* Try to free the PUD that contained the PMD just freed */
		try_to_free_table(pmd, pge);
		return;
	}

	/* Traverse the Page Table Entry Directory */
	ptd = __va(xpte_paddr(pme));
	pte = &ptd[ptd_index];
	if (!pte->valid) {
		return;
	} else {
		/* Unmap the 4KB page that this PTE was mapping */
		memset(pte, 0, sizeof(xpte_t));

		/* Try to free the PTD that the PTE was in */
		if (try_to_free_table(ptd, pme))
			return;  /* nope, couldn't free it */

		/* Try to free the PGD that contained the PMD just freed */
		try_to_free_table(pmd, pge);
		return;
	}
	printk("6\n");
}


/**
 * Writes a new value to a PTE.
 * TODO: Determine if this is atomic enough.
 */
static void
write_pte(
	xpte_leaf_t *	pte,
	paddr_t		paddr,
	vmflags_t	flags,
	vmpagesize_t	pagesz
)
{
	pte_paddr_t pte_paddr = { .value = (uint64_t)paddr };
	xpte_leaf_t _pte;
	memset(&_pte, 0, sizeof(_pte));

	_pte.valid	= 1;
	_pte.read   = 1;
	_pte.write	= 1;
	_pte.global = 1;
	_pte.exec		= 1;
	_pte.acc    = 1;
	_pte.dirty  = 1;

	/* NMG Not sure how to model nocache/device memory in these page tables. */
/* 	if (flags & VM_NOCACHE) { */
/* 		// I'm not really sure this is what we want here.... */
/* //		_pte.attrIndx = MT_NORMAL_NC; */
/* 		_pte.attrIndx = MT_DEVICE_nGnRnE; */
/* 	} else { */
/* 		_pte.attrIndx = MT_NORMAL; */
/* 		_pte.SH0 = 1; */
/* 		_pte.SH1 = 1; */

/* 	} */

	switch (pagesz) {
	case VM_PAGE_4KB:
		_pte.ppn0 = pte_paddr.ppn0;
	case VM_PAGE_2MB:
		_pte.ppn1 = pte_paddr.ppn1;
	case VM_PAGE_1GB:
		_pte.ppn2 = pte_paddr.ppn2;
		break;
	default:
		printk("pagesz is a weird value! %p\n", pagesz);
		BUG();
		break;
	};

	// printk("Writing PTE [%p]\n", *(u64 *)&_pte);

	*pte = _pte;
}


/**
 * Maps a page into an address space.
 *
 * Arguments:
 *       [IN] aspace: Address space to map page into.
 *       [IN] start:  Address in aspace to map page to.
 *       [IN] paddr:  Physical address of the page to map.
 *       [IN] flags:  Protection and memory type flags.
 *       [IN] pagesz: Size of the page being mapped, in bytes.
 *
 * Returns:
 *       Success: 0
 *       Failure: Error Code, the page was not mapped.
 */
int
arch_aspace_map_page(
	struct aspace *	aspace,
	vaddr_t		start,
	paddr_t		paddr,
	vmflags_t	flags,
	vmpagesize_t	pagesz
)
{
	xpte_t *pte;

	//printk("Mapping Page [aspace=%d] (vaddr=%p) (paddr=%p) (pagesz=%d)\n", aspace->id, (void *)start, (void *)paddr, pagesz);

	/* Locate page table entry that needs to be updated to map the page */
	pte = find_or_create_pte(aspace, start, pagesz);
	if (!pte)
		return -ENOMEM;


	/* Update the page table entry */
	write_pte(pte, paddr, flags, pagesz);

	// TODO: Need to narrow down the page the entries that are being updated
	flush_cache_all();
	flush_tlb_all();
	local_flush_tlb_all();
	return 0;
}


/**
 * Unmaps a page from an address space.
 *
 * Arguments:
 *       [IN] aspace: Address space to unmap page from.
 *       [IN] start:  Address in aspace to unmap page from.
 *       [IN] pagesz: Size of the page to unmap.
 */
void
arch_aspace_unmap_page(
	struct aspace *	aspace,
	vaddr_t		start,
	vmpagesize_t	pagesz
)
{
	find_and_delete_pte(aspace, start, pagesz);
}

int
arch_aspace_smartmap(struct aspace *src, struct aspace *dst,
                     vaddr_t start, size_t extent)
{
	panic("arch aspace smartmap\n");
#if 0
	size_t n = extent / SMARTMAP_ALIGN;
	size_t i;
	xpte_t *src_pgd = src->arch.pgd;
	xpte_t *dst_pgd = dst->arch.pgd;
	xpte_t *src_pge, *dst_pge;

	printk("arch_aspace_smartmap: %llx\n",start);
	/* Make sure all of the source PGD entries are present */
	for (i = 0; i < n; i++) {
		src_pge = &src_pgd[i];
		if (!src_pge->valid && !alloc_page_table(src_pge))
			return -ENOMEM;
	}

	/* Perform the SMARTMAP... just copy src PGEs to the dst PGD */
	for (i = 0; i < n; i++) {
		src_pge = &src_pgd[i];
		dst_pge = &dst_pgd[(start >> 39) & 0x1FF];
		BUG_ON(dst_pge->valid);
		*dst_pge = *src_pge;
	}
#endif
	return 0;
}

int
arch_aspace_unsmartmap(struct aspace *src, struct aspace *dst,
                       vaddr_t start, size_t extent)
{
	panic("arch aspace unsmartmap\n");
#if 0
	size_t n = extent / SMARTMAP_ALIGN;
	size_t i;
	xpte_t *dst_pgd = dst->arch.pgd;
	xpte_t *dst_pge;

	/* Unmap the SMARTMAP PGEs */
	for (i = 0; i < n; i++) {
		dst_pge = &dst_pgd[(start >> 39) & 0x1FF];
		dst_pge->valid = 0;
		dst_pge->AF = 0;
	}
#endif
	return 0;
}

extern bool _can_print;

int
arch_aspace_virt_to_phys(struct aspace *aspace, vaddr_t vaddr, paddr_t *paddr)
{
	pte_vaddr_t pte_vaddr = { .value = (uint64_t)vaddr };

	xpte_t *pgd = NULL;	/* Page Global Directory: level 0 (root of tree) */
	xpte_t *pud = NULL;	/* Page Upper Directory:  level 1 */
	xpte_t *pmd = NULL;	/* Page Middle Directory: level 2 */
	xpte_t *ptd = NULL;	/* Page Table Directory:  level 3 */

	xpte_t *pge;	/* Page Global Directory Entry */
	xpte_t *pue;	/* Page Upper Directory Entry */
	xpte_t *pme;	/* Page Middle Directory Entry */
	xpte_t *pte;	/* Page Table Directory Entry */

	paddr_t result; /* The result of the translation */

	unsigned int pgd_index =  pte_vaddr.vpn2;
	unsigned int pmd_index =  pte_vaddr.vpn1;
	unsigned int ptd_index =  pte_vaddr.vpn0;

	struct ssatp satp = { .value = csr_read(CSR_SATP) };

	/* if ((tcr.t0sz < 25) || (tcr.t0sz > 33)) { */
	/* 	panic("Unable to handle this starting level\n"); */
	/* } */

	/* NMG Find if any of the upper bits in kernel-mode virtual
	 * addresses are *NOT* set. Kernel virtual addresses should have the
	 * upper bits all set to 1. Then, all the bits that must be equal
	 * should have the same bitness. For Sv39, that's bits 38-63 (26
	 * bits). The mask we check against is the upper 26 bits set. */
	if (aspace->id == BOOTSTRAP_ASPACE_ID) {
		u64 msb_mask = ~(0xffffffffffffffff) >> 26;

		if ((vaddr & msb_mask) != msb_mask) {
			panic("Invalid Bootstrap Address [vaddr=%p] [msb_mask=%p]\n", vaddr, msb_mask);
		}

		pgd = aspace->arch.pgd;

	} else {
		u64 msb_mask = ~(0xffffffffffffffff >> 26); /* NMG Get rid of these 26s as magic numbers */

		/* If the vaddr has all the same bits as the mask set, it is a kernel virtual address. */
		if ((vaddr & msb_mask) == msb_mask) {
			pgd = bootstrap_aspace.arch.pgd;
		/* If they share no bits, then it is a user virtual address */
		} else if ((vaddr & msb_mask) == 0) {
			pgd = aspace->arch.pgd;
		} else {
			panic("Invalid Kernel/User Address [vaddr=%p]\n", vaddr);
		}
	}


	/* if (tcr.tg0 == 0 && tcr.tg1 == 2) { */
	/* 	// 4k granule */
	/* 	pgd_index = (vaddr >> 39) & 0x1FF; */
	/* 	pud_index = (vaddr >> 30) & 0x1FF; */
	/* 	pmd_index = (vaddr >> 21) & 0x1FF; */
	/* 	ptd_index = (vaddr >> 12) & 0x1FF; */
	/* } else { */
	/* 	printk("Unable to handle non-4k granule sizes\n"); */
	/* 	goto out; */
	/* } */

	/* Traverse the Page Global Directory */
	if (pgd != NULL) {
		pge = &pgd[pgd_index];
		if (!pge->valid)
			return -ENOENT;
		if (is_leaf(pge)) {

			result = (xpte_paddr(pge) | (vaddr & (PAGE_SIZE_1GB-1)));
		}
//		printk("Traverse: xpte_paddr(pge): %p\n", xpte_paddr(pge));
		pmd = __va(xpte_paddr(pge));
		//pmd = __va(pge->base_paddr << 12);
	}

	/* Traverse the Page Middle Directory */
	if (pmd != NULL) {
		pme = &pmd[pmd_index];
		if (!pme->valid)
			return -ENOENT;
		if (is_leaf(pme)) {
			result = (xpte_paddr(pme) | (vaddr & (PAGE_SIZE_2MB-1)));
			goto out;
		}
	}

	/* Traverse the Page Table Entry Directory */
//	printk("Traverse: xpte_paddr(pme): %p\n", xpte_paddr(pme));
	ptd = __va(xpte_paddr(pme));
	pte = &ptd[ptd_index];
	if (!pte->valid)
		return -ENOENT;
//	printk("Traverse: xpte_paddr(pte): %p\n", xpte_paddr(pte));
	result = (xpte_paddr(pte) | (vaddr & (PAGE_SIZE_4KB-1)));

	out:
	if (paddr)
		*paddr = result;
	return 0;
}


/**
 * This maps a region of physical memory into the kernel virtual address space.
 * It assumes start and end are aligned to a 2 MB boundary and that the
 * kernel is using 2 MB pages to map physical memory into the kernel virtual
 * address space.
 */
int
arch_aspace_map_pmem_into_kernel(paddr_t start, paddr_t end)
{
	paddr_t paddr;
	int status;

	//printk("arch_aspace_map_pmem_into_kernel\n");
	for (paddr = start; paddr < end; paddr += VM_PAGE_2MB) {
		/* If the page isn't already mapped, we need to map it */
		if (arch_aspace_virt_to_phys(&bootstrap_aspace, (vaddr_t)__va(paddr), NULL) == -ENOENT) {
			printk(KERN_INFO "Missing kernel memory found, paddr=0x%016lx.\n", paddr);

			status =
			arch_aspace_map_page(
				&bootstrap_aspace,
				(vaddr_t)__va(paddr),
				paddr,
				VM_KERNEL,
				VM_PAGE_2MB
			);
			printk("pmem_into\n");

			if (status) {
				printk(KERN_ERR "Could not map kernel memory for paddr=0x%016lx.\n", paddr);
				printk(KERN_ERR "Kernel address space is now inconsistent.\n");
				return -1;
			}
		}
	}
	return 0;
}

/**
 * This unmaps a region of physical memory from the kernel virtual address
 * space.  It assumes start and end are aligned to a 2 MB boundary and that the
 * kernel is using 2 MB pages to map physical memory into the kernel virtual
 * address space.
 */

int
arch_aspace_unmap_pmem_from_kernel(paddr_t start, paddr_t end)
{
	paddr_t paddr;

	for (paddr = start; paddr < end; paddr += VM_PAGE_2MB) {
		/* If the page is mapped, we need to unmap it */
		if (arch_aspace_virt_to_phys(&bootstrap_aspace, (vaddr_t)__va(paddr), NULL) == 0) {
			arch_aspace_unmap_page(
				&bootstrap_aspace,
				(vaddr_t)__va(paddr),
				VM_PAGE_2MB
			);
		}
	}

	return 0;
}
