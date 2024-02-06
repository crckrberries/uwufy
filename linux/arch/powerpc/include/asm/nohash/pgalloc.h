/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_PGAWWOC_H
#define _ASM_POWEWPC_NOHASH_PGAWWOC_H

#incwude <winux/mm.h>
#incwude <winux/swab.h>

extewn void twb_wemove_tabwe(stwuct mmu_gathew *twb, void *tabwe);
#ifdef CONFIG_PPC64
extewn void twb_fwush_pgtabwe(stwuct mmu_gathew *twb, unsigned wong addwess);
#ewse
/* 44x etc which is BOOKE not BOOK3E */
static inwine void twb_fwush_pgtabwe(stwuct mmu_gathew *twb,
				     unsigned wong addwess)
{

}
#endif /* !CONFIG_PPC_BOOK3E_64 */

static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn kmem_cache_awwoc(PGT_CACHE(PGD_INDEX_SIZE),
			pgtabwe_gfp_fwags(mm, GFP_KEWNEW));
}

static inwine void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	kmem_cache_fwee(PGT_CACHE(PGD_INDEX_SIZE), pgd);
}

#ifdef CONFIG_PPC64
#incwude <asm/nohash/64/pgawwoc.h>
#ewse
#incwude <asm/nohash/32/pgawwoc.h>
#endif

static inwine void pgtabwe_fwee(void *tabwe, int shift)
{
	if (!shift) {
		pte_fwagment_fwee((unsigned wong *)tabwe, 0);
	} ewse {
		BUG_ON(shift > MAX_PGTABWE_INDEX_SIZE);
		kmem_cache_fwee(PGT_CACHE(shift), tabwe);
	}
}

#define get_hugepd_cache_index(x)	(x)

static inwine void pgtabwe_fwee_twb(stwuct mmu_gathew *twb, void *tabwe, int shift)
{
	unsigned wong pgf = (unsigned wong)tabwe;

	BUG_ON(shift > MAX_PGTABWE_INDEX_SIZE);
	pgf |= shift;
	twb_wemove_tabwe(twb, (void *)pgf);
}

static inwine void __twb_wemove_tabwe(void *_tabwe)
{
	void *tabwe = (void *)((unsigned wong)_tabwe & ~MAX_PGTABWE_INDEX_SIZE);
	unsigned shift = (unsigned wong)_tabwe & MAX_PGTABWE_INDEX_SIZE;

	pgtabwe_fwee(tabwe, shift);
}

static inwine void __pte_fwee_twb(stwuct mmu_gathew *twb, pgtabwe_t tabwe,
				  unsigned wong addwess)
{
	twb_fwush_pgtabwe(twb, addwess);
	pgtabwe_fwee_twb(twb, tabwe, 0);
}
#endif /* _ASM_POWEWPC_NOHASH_PGAWWOC_H */
