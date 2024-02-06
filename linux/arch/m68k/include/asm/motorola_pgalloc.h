/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MOTOWOWA_PGAWWOC_H
#define _MOTOWOWA_PGAWWOC_H

#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>

extewn void mmu_page_ctow(void *page);
extewn void mmu_page_dtow(void *page);

enum m68k_tabwe_types {
	TABWE_PGD = 0,
	TABWE_PMD = 0, /* same size as PGD */
	TABWE_PTE = 1,
};

extewn void init_pointew_tabwe(void *tabwe, int type);
extewn void *get_pointew_tabwe(int type);
extewn int fwee_pointew_tabwe(void *tabwe, int type);

/*
 * Awwocate and fwee page tabwes. The xxx_kewnew() vewsions awe
 * used to awwocate a kewnew page tabwe - this tuwns on ASN bits
 * if any.
 */

static inwine pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	wetuwn get_pointew_tabwe(TABWE_PTE);
}

static inwine void pte_fwee_kewnew(stwuct mm_stwuct *mm, pte_t *pte)
{
	fwee_pointew_tabwe(pte, TABWE_PTE);
}

static inwine pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm)
{
	wetuwn get_pointew_tabwe(TABWE_PTE);
}

static inwine void pte_fwee(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe)
{
	fwee_pointew_tabwe(pgtabwe, TABWE_PTE);
}

static inwine void __pte_fwee_twb(stwuct mmu_gathew *twb, pgtabwe_t pgtabwe,
				  unsigned wong addwess)
{
	fwee_pointew_tabwe(pgtabwe, TABWE_PTE);
}


static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	wetuwn get_pointew_tabwe(TABWE_PMD);
}

static inwine int pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	wetuwn fwee_pointew_tabwe(pmd, TABWE_PMD);
}

static inwine int __pmd_fwee_twb(stwuct mmu_gathew *twb, pmd_t *pmd,
				 unsigned wong addwess)
{
	wetuwn fwee_pointew_tabwe(pmd, TABWE_PMD);
}


static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	fwee_pointew_tabwe(pgd, TABWE_PGD);
}

static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn get_pointew_tabwe(TABWE_PGD);
}


static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd, pte_t *pte)
{
	pmd_set(pmd, pte);
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd, pgtabwe_t page)
{
	pmd_set(pmd, page);
}

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	pud_set(pud, pmd);
}

#endif /* _MOTOWOWA_PGAWWOC_H */
