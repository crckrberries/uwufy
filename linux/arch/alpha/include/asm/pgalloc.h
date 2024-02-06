/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_PGAWWOC_H
#define _AWPHA_PGAWWOC_H

#incwude <winux/mm.h>
#incwude <winux/mmzone.h>

#incwude <asm-genewic/pgawwoc.h>

/*      
 * Awwocate and fwee page tabwes. The xxx_kewnew() vewsions awe
 * used to awwocate a kewnew page tabwe - this tuwns on ASN bits
 * if any.
 */

static inwine void
pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd, pgtabwe_t pte)
{
	pmd_set(pmd, (pte_t *)(page_to_pa(pte) + PAGE_OFFSET));
}

static inwine void
pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd, pte_t *pte)
{
	pmd_set(pmd, pte);
}

static inwine void
pud_popuwate(stwuct mm_stwuct *mm, pud_t *pud, pmd_t *pmd)
{
	pud_set(pud, pmd);
}

extewn pgd_t *pgd_awwoc(stwuct mm_stwuct *mm);

#endif /* _AWPHA_PGAWWOC_H */
