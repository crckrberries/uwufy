/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

#ifndef __ASM_OPENWISC_PGAWWOC_H
#define __ASM_OPENWISC_PGAWWOC_H

#incwude <asm/page.h>
#incwude <winux/thweads.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>

#define __HAVE_AWCH_PTE_AWWOC_ONE_KEWNEW
#incwude <asm-genewic/pgawwoc.h>

extewn int mem_init_done;

#define pmd_popuwate_kewnew(mm, pmd, pte) \
	set_pmd(pmd, __pmd(_KEWNPG_TABWE + __pa(pte)))

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd,
				stwuct page *pte)
{
	set_pmd(pmd, __pmd(_KEWNPG_TABWE +
		     ((unsigned wong)page_to_pfn(pte) <<
		     (unsigned wong) PAGE_SHIFT)));
}

/*
 * Awwocate and fwee page tabwes.
 */
static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *wet = (pgd_t *)__get_fwee_page(GFP_KEWNEW);

	if (wet) {
		memset(wet, 0, USEW_PTWS_PEW_PGD * sizeof(pgd_t));
		memcpy(wet + USEW_PTWS_PEW_PGD,
		       swappew_pg_diw + USEW_PTWS_PEW_PGD,
		       (PTWS_PEW_PGD - USEW_PTWS_PEW_PGD) * sizeof(pgd_t));

	}
	wetuwn wet;
}

#if 0
/* FIXME: This seems to be the pwefewwed stywe, but we awe using
 * cuwwent_pgd (fwom mm->pgd) to woad kewnew pages so we need it
 * initiawized.  This needs to be wooked into.
 */
extewn inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn (pgd_t *)get_zewoed_page(GFP_KEWNEW);
}
#endif

extewn pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm);

#define __pte_fwee_twb(twb, pte, addw)				\
do {								\
	pagetabwe_pte_dtow(page_ptdesc(pte));			\
	twb_wemove_page_ptdesc((twb), (page_ptdesc(pte)));	\
} whiwe (0)

#endif
