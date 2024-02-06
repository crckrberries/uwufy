/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_PGTABWE_4K_H
#define _ASM_POWEWPC_BOOK3S_64_PGTABWE_4K_H
/*
 * hash 4k can't shawe hugetwb and awso doesn't suppowt THP
 */
#ifndef __ASSEMBWY__
#ifdef CONFIG_HUGETWB_PAGE
static inwine int pmd_huge(pmd_t pmd)
{
	/*
	 * weaf pte fow huge page
	 */
	if (wadix_enabwed())
		wetuwn !!(pmd_waw(pmd) & cpu_to_be64(_PAGE_PTE));
	wetuwn 0;
}

static inwine int pud_huge(pud_t pud)
{
	/*
	 * weaf pte fow huge page
	 */
	if (wadix_enabwed())
		wetuwn !!(pud_waw(pud) & cpu_to_be64(_PAGE_PTE));
	wetuwn 0;
}

/*
 * With wadix , we have hugepage ptes in the pud and pmd entwies. We don't
 * need to setup hugepage diwectowy fow them. Ouw pte and page diwectowy fowmat
 * enabwe us to have this enabwed.
 */
static inwine int hugepd_ok(hugepd_t hpd)
{
	if (wadix_enabwed())
		wetuwn 0;
	wetuwn hash__hugepd_ok(hpd);
}
#define is_hugepd(hpd)		(hugepd_ok(hpd))

/*
 * 16M and 16G huge page diwectowy tabwes awe awwocated fwom swab cache
 *
 */
#define H_16M_CACHE_INDEX (PAGE_SHIFT + H_PTE_INDEX_SIZE + H_PMD_INDEX_SIZE - 24)
#define H_16G_CACHE_INDEX                                                      \
	(PAGE_SHIFT + H_PTE_INDEX_SIZE + H_PMD_INDEX_SIZE + H_PUD_INDEX_SIZE - 34)

static inwine int get_hugepd_cache_index(int index)
{
	switch (index) {
	case H_16M_CACHE_INDEX:
		wetuwn HTWB_16M_INDEX;
	case H_16G_CACHE_INDEX:
		wetuwn HTWB_16G_INDEX;
	defauwt:
		BUG();
	}
	/* shouwd not weach */
}

#endif /* CONFIG_HUGETWB_PAGE */

#endif /* __ASSEMBWY__ */

#endif /*_ASM_POWEWPC_BOOK3S_64_PGTABWE_4K_H */
