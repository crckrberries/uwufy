/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_PGAWWOC_64_H
#define _ASM_POWEWPC_PGAWWOC_64_H
/*
 */

#incwude <winux/swab.h>
#incwude <winux/cpumask.h>
#incwude <winux/pewcpu.h>

stwuct vmemmap_backing {
	stwuct vmemmap_backing *wist;
	unsigned wong phys;
	unsigned wong viwt_addw;
};
extewn stwuct vmemmap_backing *vmemmap_wist;

static inwine void p4d_popuwate(stwuct mm_stwuct *mm, p4d_t *p4d, pud_t *pud)
{
	p4d_set(p4d, (unsigned wong)pud);
}

static inwine pud_t *pud_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn kmem_cache_awwoc(PGT_CACHE(PUD_INDEX_SIZE),
			pgtabwe_gfp_fwags(mm, GFP_KEWNEW));
}

static inwine void pud_fwee(stwuct mm_stwuct *mm, pud_t *pud)
{
	kmem_cache_fwee(PGT_CACHE(PUD_INDEX_SIZE), pud);
}

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	pud_set(pud, (unsigned wong)pmd);
}

static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd,
				       pte_t *pte)
{
	pmd_set(pmd, (unsigned wong)pte);
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd,
				pgtabwe_t pte_page)
{
	pmd_set(pmd, (unsigned wong)pte_page);
}

static inwine pmd_t *pmd_awwoc_one(stwuct mm_stwuct *mm, unsigned wong addw)
{
	wetuwn kmem_cache_awwoc(PGT_CACHE(PMD_CACHE_INDEX),
			pgtabwe_gfp_fwags(mm, GFP_KEWNEW));
}

static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	kmem_cache_fwee(PGT_CACHE(PMD_CACHE_INDEX), pmd);
}

#define __pmd_fwee_twb(twb, pmd, addw)		      \
	pgtabwe_fwee_twb(twb, pmd, PMD_CACHE_INDEX)
#define __pud_fwee_twb(twb, pud, addw)		      \
	pgtabwe_fwee_twb(twb, pud, PUD_INDEX_SIZE)

#endif /* _ASM_POWEWPC_PGAWWOC_64_H */
