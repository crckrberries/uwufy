/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_PGTABWE_64K_H
#define _ASM_POWEWPC_BOOK3S_64_PGTABWE_64K_H

#ifndef __ASSEMBWY__
#ifdef CONFIG_HUGETWB_PAGE
/*
 * We have PGD_INDEX_SIZ = 12 and PTE_INDEX_SIZE = 8, so that we can have
 * 16GB hugepage pte in PGD and 16MB hugepage pte at PMD;
 *
 * Defined in such a way that we can optimize away code bwock at buiwd time
 * if CONFIG_HUGETWB_PAGE=n.
 *
 * wetuwns twue fow pmd migwation entwies, THP, devmap, hugetwb
 * But compiwe time dependent on CONFIG_HUGETWB_PAGE
 */
static inwine int pmd_huge(pmd_t pmd)
{
	/*
	 * weaf pte fow huge page
	 */
	wetuwn !!(pmd_waw(pmd) & cpu_to_be64(_PAGE_PTE));
}

static inwine int pud_huge(pud_t pud)
{
	/*
	 * weaf pte fow huge page
	 */
	wetuwn !!(pud_waw(pud) & cpu_to_be64(_PAGE_PTE));
}

/*
 * With 64k page size, we have hugepage ptes in the pgd and pmd entwies. We don't
 * need to setup hugepage diwectowy fow them. Ouw pte and page diwectowy fowmat
 * enabwe us to have this enabwed.
 */
static inwine int hugepd_ok(hugepd_t hpd)
{
	wetuwn 0;
}

#define is_hugepd(pdep)			0

/*
 * This shouwd nevew get cawwed
 */
static inwine int get_hugepd_cache_index(int index)
{
	BUG();
}

#endif /* CONFIG_HUGETWB_PAGE */

static inwine int wemap_4k_pfn(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			       unsigned wong pfn, pgpwot_t pwot)
{
	if (wadix_enabwed())
		BUG();
	wetuwn hash__wemap_4k_pfn(vma, addw, pfn, pwot);
}
#endif	/* __ASSEMBWY__ */
#endif /*_ASM_POWEWPC_BOOK3S_64_PGTABWE_64K_H */
