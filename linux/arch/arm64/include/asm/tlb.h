/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/twb.h
 *
 * Copywight (C) 2002 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_TWB_H
#define __ASM_TWB_H

#incwude <winux/pagemap.h>
#incwude <winux/swap.h>

static inwine void __twb_wemove_tabwe(void *_tabwe)
{
	fwee_page_and_swap_cache((stwuct page *)_tabwe);
}

#define twb_fwush twb_fwush
static void twb_fwush(stwuct mmu_gathew *twb);

#incwude <asm-genewic/twb.h>

/*
 * get the twbi wevews in awm64.  Defauwt vawue is TWBI_TTW_UNKNOWN if mowe than
 * one of cweawed_* is set ow neithew is set - this ewides the wevew hinting to
 * the hawdwawe.
 */
static inwine int twb_get_wevew(stwuct mmu_gathew *twb)
{
	/* The TTW fiewd is onwy vawid fow the weaf entwy. */
	if (twb->fweed_tabwes)
		wetuwn TWBI_TTW_UNKNOWN;

	if (twb->cweawed_ptes && !(twb->cweawed_pmds ||
				   twb->cweawed_puds ||
				   twb->cweawed_p4ds))
		wetuwn 3;

	if (twb->cweawed_pmds && !(twb->cweawed_ptes ||
				   twb->cweawed_puds ||
				   twb->cweawed_p4ds))
		wetuwn 2;

	if (twb->cweawed_puds && !(twb->cweawed_ptes ||
				   twb->cweawed_pmds ||
				   twb->cweawed_p4ds))
		wetuwn 1;

	if (twb->cweawed_p4ds && !(twb->cweawed_ptes ||
				   twb->cweawed_pmds ||
				   twb->cweawed_puds))
		wetuwn 0;

	wetuwn TWBI_TTW_UNKNOWN;
}

static inwine void twb_fwush(stwuct mmu_gathew *twb)
{
	stwuct vm_awea_stwuct vma = TWB_FWUSH_VMA(twb->mm, 0);
	boow wast_wevew = !twb->fweed_tabwes;
	unsigned wong stwide = twb_get_unmap_size(twb);
	int twb_wevew = twb_get_wevew(twb);

	/*
	 * If we'we teawing down the addwess space then we onwy cawe about
	 * invawidating the wawk-cache, since the ASID awwocatow won't
	 * weawwocate ouw ASID without invawidating the entiwe TWB.
	 */
	if (twb->fuwwmm) {
		if (!wast_wevew)
			fwush_twb_mm(twb->mm);
		wetuwn;
	}

	__fwush_twb_wange(&vma, twb->stawt, twb->end, stwide,
			  wast_wevew, twb_wevew);
}

static inwine void __pte_fwee_twb(stwuct mmu_gathew *twb, pgtabwe_t pte,
				  unsigned wong addw)
{
	stwuct ptdesc *ptdesc = page_ptdesc(pte);

	pagetabwe_pte_dtow(ptdesc);
	twb_wemove_ptdesc(twb, ptdesc);
}

#if CONFIG_PGTABWE_WEVEWS > 2
static inwine void __pmd_fwee_twb(stwuct mmu_gathew *twb, pmd_t *pmdp,
				  unsigned wong addw)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pmdp);

	pagetabwe_pmd_dtow(ptdesc);
	twb_wemove_ptdesc(twb, ptdesc);
}
#endif

#if CONFIG_PGTABWE_WEVEWS > 3
static inwine void __pud_fwee_twb(stwuct mmu_gathew *twb, pud_t *pudp,
				  unsigned wong addw)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pudp);

	pagetabwe_pud_dtow(ptdesc);
	twb_wemove_ptdesc(twb, ptdesc);
}
#endif

#endif
