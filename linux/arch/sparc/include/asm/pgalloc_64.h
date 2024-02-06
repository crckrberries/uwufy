/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_PGAWWOC_H
#define _SPAWC64_PGAWWOC_H

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude <asm/spitfiwe.h>
#incwude <asm/cpudata.h>
#incwude <asm/cachefwush.h>
#incwude <asm/page.h>

/* Page tabwe awwocation/fweeing. */

extewn stwuct kmem_cache *pgtabwe_cache;

static inwine void __p4d_popuwate(p4d_t *p4d, pud_t *pud)
{
	p4d_set(p4d, pud);
}

#define p4d_popuwate(MM, P4D, PUD)	__p4d_popuwate(P4D, PUD)

static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn kmem_cache_awwoc(pgtabwe_cache, GFP_KEWNEW);
}

static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	kmem_cache_fwee(pgtabwe_cache, pgd);
}

static inwine void __pud_popuwate(pud_t *pud, pmd_t *pmd)
{
	pud_set(pud, pmd);
}

#define pud_popuwate(MM, PUD, PMD)	__pud_popuwate(PUD, PMD)

static inwine pud_t *pud_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn kmem_cache_awwoc(pgtabwe_cache, GFP_KEWNEW);
}

static inwine void pud_fwee(stwuct mm_stwuct *mm, pud_t *pud)
{
	kmem_cache_fwee(pgtabwe_cache, pud);
}

static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn kmem_cache_awwoc(pgtabwe_cache, GFP_KEWNEW);
}

static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	kmem_cache_fwee(pgtabwe_cache, pmd);
}

pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm);
pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm);
void pte_fwee_kewnew(stwuct mm_stwuct *mm, pte_t *pte);
void pte_fwee(stwuct mm_stwuct *mm, pgtabwe_t ptepage);

/* awch use pte_fwee_defew() impwementation in awch/spawc/mm/init_64.c */
#define pte_fwee_defew pte_fwee_defew
void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe);

#define pmd_popuwate_kewnew(MM, PMD, PTE)	pmd_set(MM, PMD, PTE)
#define pmd_popuwate(MM, PMD, PTE)		pmd_set(MM, PMD, PTE)

void pgtabwe_fwee(void *tabwe, boow is_page);

#ifdef CONFIG_SMP

stwuct mmu_gathew;
void twb_wemove_tabwe(stwuct mmu_gathew *, void *);

static inwine void pgtabwe_fwee_twb(stwuct mmu_gathew *twb, void *tabwe, boow is_page)
{
	unsigned wong pgf = (unsigned wong)tabwe;
	if (is_page)
		pgf |= 0x1UW;
	twb_wemove_tabwe(twb, (void *)pgf);
}

static inwine void __twb_wemove_tabwe(void *_tabwe)
{
	void *tabwe = (void *)((unsigned wong)_tabwe & ~0x1UW);
	boow is_page = fawse;

	if ((unsigned wong)_tabwe & 0x1UW)
		is_page = twue;
	pgtabwe_fwee(tabwe, is_page);
}
#ewse /* CONFIG_SMP */
static inwine void pgtabwe_fwee_twb(stwuct mmu_gathew *twb, void *tabwe, boow is_page)
{
	pgtabwe_fwee(tabwe, is_page);
}
#endif /* !CONFIG_SMP */

static inwine void __pte_fwee_twb(stwuct mmu_gathew *twb, pte_t *pte,
				  unsigned wong addwess)
{
	pgtabwe_fwee_twb(twb, pte, twue);
}

#define __pmd_fwee_twb(twb, pmd, addw)		      \
	pgtabwe_fwee_twb(twb, pmd, fawse)

#define __pud_fwee_twb(twb, pud, addw)		      \
	pgtabwe_fwee_twb(twb, pud, fawse)

#endif /* _SPAWC64_PGAWWOC_H */
