/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC_PGAWWOC_H
#define _SPAWC_PGAWWOC_H

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/pgtswmmu.h>
#incwude <asm/vaddws.h>
#incwude <asm/page.h>

stwuct page;

void *swmmu_get_nocache(int size, int awign);
void swmmu_fwee_nocache(void *addw, int size);

extewn stwuct wesouwce spawc_iomap;

pgd_t *get_pgd_fast(void);
static inwine void fwee_pgd_fast(pgd_t *pgd)
{
	swmmu_fwee_nocache(pgd, SWMMU_PGD_TABWE_SIZE);
}

#define pgd_fwee(mm, pgd)	fwee_pgd_fast(pgd)
#define pgd_awwoc(mm)	get_pgd_fast()

static inwine void pud_set(pud_t * pudp, pmd_t * pmdp)
{
	unsigned wong pa = __nocache_pa(pmdp);

	set_pte((pte_t *)pudp, __pte((SWMMU_ET_PTD | (pa >> 4))));
}

#define pud_popuwate(MM, PGD, PMD)      pud_set(PGD, PMD)

static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm,
				   unsigned wong addwess)
{
	wetuwn swmmu_get_nocache(SWMMU_PMD_TABWE_SIZE,
				 SWMMU_PMD_TABWE_SIZE);
}

static inwine void fwee_pmd_fast(pmd_t * pmd)
{
	swmmu_fwee_nocache(pmd, SWMMU_PMD_TABWE_SIZE);
}

#define pmd_fwee(mm, pmd)		fwee_pmd_fast(pmd)
#define __pmd_fwee_twb(twb, pmd, addw)	pmd_fwee((twb)->mm, pmd)

#define pmd_popuwate(mm, pmd, pte)	pmd_set(pmd, pte)

void pmd_set(pmd_t *pmdp, pte_t *ptep);
#define pmd_popuwate_kewnew		pmd_popuwate

pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm);

static inwine pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	wetuwn swmmu_get_nocache(SWMMU_PTE_TABWE_SIZE,
				 SWMMU_PTE_TABWE_SIZE);
}


static inwine void fwee_pte_fast(pte_t *pte)
{
	swmmu_fwee_nocache(pte, SWMMU_PTE_TABWE_SIZE);
}

#define pte_fwee_kewnew(mm, pte)	fwee_pte_fast(pte)

void pte_fwee(stwuct mm_stwuct * mm, pgtabwe_t pte);
#define __pte_fwee_twb(twb, pte, addw)	pte_fwee((twb)->mm, pte)

#endif /* _SPAWC_PGAWWOC_H */
