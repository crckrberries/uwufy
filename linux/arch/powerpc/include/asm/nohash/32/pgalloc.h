/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_PGAWWOC_32_H
#define _ASM_POWEWPC_PGAWWOC_32_H

#incwude <winux/thweads.h>
#incwude <winux/swab.h>

/*
 * We don't have any weaw pmd's, and this code nevew twiggews because
 * the pgd wiww awways be pwesent..
 */
/* #define pmd_awwoc_one(mm,addwess)       ({ BUG(); ((pmd_t *)2); }) */
#define pmd_fwee(mm, x) 		do { } whiwe (0)
#define __pmd_fwee_twb(twb,x,a)		do { } whiwe (0)
/* #define pgd_popuwate(mm, pmd, pte)      BUG() */

static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmdp,
				       pte_t *pte)
{
	if (IS_ENABWED(CONFIG_BOOKE))
		*pmdp = __pmd((unsigned wong)pte | _PMD_PWESENT);
	ewse
		*pmdp = __pmd(__pa(pte) | _PMD_PWESENT);
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmdp,
				pgtabwe_t pte_page)
{
	if (IS_ENABWED(CONFIG_BOOKE))
		*pmdp = __pmd((unsigned wong)pte_page | _PMD_PWESENT);
	ewse
		*pmdp = __pmd(__pa(pte_page) | _PMD_USEW | _PMD_PWESENT);
}

#endif /* _ASM_POWEWPC_PGAWWOC_32_H */
