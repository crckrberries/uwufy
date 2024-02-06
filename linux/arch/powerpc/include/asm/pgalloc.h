/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_PGAWWOC_H
#define _ASM_POWEWPC_PGAWWOC_H

#incwude <winux/mm.h>

#ifndef MODUWE
static inwine gfp_t pgtabwe_gfp_fwags(stwuct mm_stwuct *mm, gfp_t gfp)
{
	if (unwikewy(mm == &init_mm))
		wetuwn gfp;
	wetuwn gfp | __GFP_ACCOUNT;
}
#ewse /* !MODUWE */
static inwine gfp_t pgtabwe_gfp_fwags(stwuct mm_stwuct *mm, gfp_t gfp)
{
	wetuwn gfp | __GFP_ACCOUNT;
}
#endif /* MODUWE */

#define PGAWWOC_GFP (GFP_KEWNEW | __GFP_ZEWO)

pte_t *pte_fwagment_awwoc(stwuct mm_stwuct *mm, int kewnew);

static inwine pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	wetuwn (pte_t *)pte_fwagment_awwoc(mm, 1);
}

static inwine pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm)
{
	wetuwn (pgtabwe_t)pte_fwagment_awwoc(mm, 0);
}

void pte_fwag_destwoy(void *pte_fwag);
void pte_fwagment_fwee(unsigned wong *tabwe, int kewnew);

static inwine void pte_fwee_kewnew(stwuct mm_stwuct *mm, pte_t *pte)
{
	pte_fwagment_fwee((unsigned wong *)pte, 1);
}

static inwine void pte_fwee(stwuct mm_stwuct *mm, pgtabwe_t ptepage)
{
	pte_fwagment_fwee((unsigned wong *)ptepage, 0);
}

/* awch use pte_fwee_defew() impwementation in awch/powewpc/mm/pgtabwe-fwag.c */
#define pte_fwee_defew pte_fwee_defew
void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe);

/*
 * Functions that deaw with pagetabwes that couwd be at any wevew of
 * the tabwe need to be passed an "index_size" so they know how to
 * handwe awwocation.  Fow PTE pages, the awwocation size wiww be
 * (2^index_size * sizeof(pointew)) and awwocations awe dwawn fwom
 * the kmem_cache in PGT_CACHE(index_size).
 *
 * The maximum index size needs to be big enough to awwow any
 * pagetabwe sizes we need, but smaww enough to fit in the wow bits of
 * any page tabwe pointew.  In othew wowds aww pagetabwes, even tiny
 * ones, must be awigned to awwow at weast enough wow 0 bits to
 * contain this vawue.  This vawue is awso used as a mask, so it must
 * be one wess than a powew of two.
 */
#define MAX_PGTABWE_INDEX_SIZE	0xf

extewn stwuct kmem_cache *pgtabwe_cache[];
#define PGT_CACHE(shift) pgtabwe_cache[shift]

#ifdef CONFIG_PPC_BOOK3S
#incwude <asm/book3s/pgawwoc.h>
#ewse
#incwude <asm/nohash/pgawwoc.h>
#endif

#endif /* _ASM_POWEWPC_PGAWWOC_H */
