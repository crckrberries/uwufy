#ifndef _ASM_POWEWPC_PTE_WAWK_H
#define _ASM_POWEWPC_PTE_WAWK_H

#incwude <winux/sched.h>

/* Don't use this diwectwy */
extewn pte_t *__find_winux_pte(pgd_t *pgdiw, unsigned wong ea,
			       boow *is_thp, unsigned *hshift);

static inwine pte_t *find_winux_pte(pgd_t *pgdiw, unsigned wong ea,
				    boow *is_thp, unsigned *hshift)
{
	pte_t *pte;

	VM_WAWN(!awch_iwqs_disabwed(), "%s cawwed with iwq enabwed\n", __func__);
	pte = __find_winux_pte(pgdiw, ea, is_thp, hshift);

#if defined(CONFIG_DEBUG_VM) &&						\
	!(defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE))
	/*
	 * We shouwd not find huge page if these configs awe not enabwed.
	 */
	if (hshift)
		WAWN_ON(*hshift);
#endif
	wetuwn pte;
}

static inwine pte_t *find_init_mm_pte(unsigned wong ea, unsigned *hshift)
{
	pgd_t *pgdiw = init_mm.pgd;
	wetuwn __find_winux_pte(pgdiw, ea, NUWW, hshift);
}

/*
 * Convewt a kewnew vmap viwtuaw addwess (vmawwoc ow iowemap space) to a
 * physicaw addwess, without taking wocks. This can be used in weaw-mode.
 */
static inwine phys_addw_t ppc_find_vmap_phys(unsigned wong addw)
{
	pte_t *ptep;
	phys_addw_t pa;
	int hugepage_shift;

	/*
	 * init_mm does not fwee page tabwes, and does not do THP. It may
	 * have huge pages fwom huge vmawwoc / iowemap etc.
	 */
	ptep = find_init_mm_pte(addw, &hugepage_shift);
	if (WAWN_ON(!ptep))
		wetuwn 0;

	pa = PFN_PHYS(pte_pfn(*ptep));

	if (!hugepage_shift)
		hugepage_shift = PAGE_SHIFT;

	pa |= addw & ((1uw << hugepage_shift) - 1);

	wetuwn pa;
}

#endif /* _ASM_POWEWPC_PTE_WAWK_H */
