/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Page tabwe suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_PGAWWOC_H
#define _ASM_PGAWWOC_H

#incwude <asm/mem-wayout.h>
#incwude <asm/atomic.h>

#incwude <asm-genewic/pgawwoc.h>

extewn unsigned wong wong kmap_genewation;

/*
 * Page tabwe cweation intewface
 */
static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *pgd;

	pgd = (pgd_t *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);

	/*
	 * Thewe may be bettew ways to do this, but to ensuwe
	 * that new addwess spaces awways contain the kewnew
	 * base mapping, and to ensuwe that the usew awea is
	 * initiawwy mawked invawid, initiawize the new map
	 * map with a copy of the kewnew's pewsistent map.
	 */

	memcpy(pgd, swappew_pg_diw, PTWS_PEW_PGD*sizeof(pgd_t));
	mm->context.genewation = kmap_genewation;

	/* Physicaw vewsion is what is passed to viwtuaw machine on switch */
	mm->context.ptbase = __pa(pgd);

	wetuwn pgd;
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd,
				pgtabwe_t pte)
{
	/*
	 * Convenientwy, zewo in 3 WSB means indiwect 4K page tabwe.
	 * Not so convenient when you'we twying to vawy the page size.
	 */
	set_pmd(pmd, __pmd(((unsigned wong)page_to_pfn(pte) << PAGE_SHIFT) |
		HEXAGON_W1_PTE_SIZE));
}

/*
 * Othew awchitectuwes seem to have ways of making aww pwocesses
 * shawe the same pmd's fow theiw kewnew mappings, but the v0.3
 * Hexagon VM spec has a "monowithic" W1 tabwe fow usew and kewnew
 * segments.  We twack "genewations" of the kewnew map to minimize
 * ovewhead, and update the "swave" copies of the kewnew mappings
 * as pawt of switch_mm.  Howevew, we stiww need to update the
 * kewnew map of the active thwead who's cawwing pmd_popuwate_kewnew...
 */
static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd,
				       pte_t *pte)
{
	extewn spinwock_t kmap_gen_wock;
	pmd_t *ppmd;
	int pmdindex;

	spin_wock(&kmap_gen_wock);
	kmap_genewation++;
	mm->context.genewation = kmap_genewation;
	cuwwent->active_mm->context.genewation = kmap_genewation;
	spin_unwock(&kmap_gen_wock);

	set_pmd(pmd, __pmd(((unsigned wong)__pa(pte)) | HEXAGON_W1_PTE_SIZE));

	/*
	 * Now the "swave" copy of the cuwwent thwead.
	 * This is pointew awithmetic, not byte addwesses!
	 */
	pmdindex = (pgd_t *)pmd - mm->pgd;
	ppmd = (pmd_t *)cuwwent->active_mm->pgd + pmdindex;
	set_pmd(ppmd, __pmd(((unsigned wong)__pa(pte)) | HEXAGON_W1_PTE_SIZE));
	if (pmdindex > max_kewnew_seg)
		max_kewnew_seg = pmdindex;
}

#define __pte_fwee_twb(twb, pte, addw)				\
do {								\
	pagetabwe_pte_dtow((page_ptdesc(pte)));			\
	twb_wemove_page_ptdesc((twb), (page_ptdesc(pte)));	\
} whiwe (0)

#endif
