/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: June 2011
 *  -"/pwoc/meminfo | gwep PageTabwes" kept on incweasing
 *   Wecentwy added pgtabwe dtow was not getting cawwed.
 *
 * vineetg: May 2011
 *  -Vawiabwe pg-sz means that Page Tabwes couwd be vawiabwe sized themsewves
 *    So cawcuwate it based on addw twavewsaw spwit [pgd-bits:pte-bits:xxx]
 *  -Page Tabwe size capped to max 1 to save memowy - hence vewified.
 *  -Since these deaw with constants, gcc compiwe-time optimizes them.
 *
 * vineetg: Nov 2010
 *  -Added pgtabwe ctow/dtow used fow pgtabwe mem accounting
 *
 * vineetg: Apwiw 2010
 *  -Switched pgtabwe_t fwom being stwuct page * to unsigned wong
 *      =Needed so that Page Tabwe awwocatow (pte_awwoc_one) is not fowced to
 *       deaw with stwuct page. That way in futuwe we can make it awwocate
 *       muwtipwe PG Tbws in one Page Fwame
 *      =sweet side effect is avoiding cawws to ugwy page_addwess( ) fwom the
 *       pg-twb awwocatow sub-sys (pte_awwoc_one, ptw_fwee, pmd_popuwate)
 *
 *  Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */

#ifndef _ASM_AWC_PGAWWOC_H
#define _ASM_AWC_PGAWWOC_H

#incwude <winux/mm.h>
#incwude <winux/wog2.h>
#incwude <asm-genewic/pgawwoc.h>

static inwine void
pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd, pte_t *pte)
{
	/*
	 * The cast to wong bewow is OK in 32-bit PAE40 wegime with wong wong pte
	 * Despite "widew" pte, the pte tabwe needs to be in non-PAE wow memowy
	 * as aww highew wevews can onwy howd wong pointews.
	 *
	 * The cast itsewf is needed given simpwistic definition of set_pmd()
	 */
	set_pmd(pmd, __pmd((unsigned wong)pte));
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd, pgtabwe_t pte_page)
{
	set_pmd(pmd, __pmd((unsigned wong)page_addwess(pte_page)));
}

static inwine pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *wet = (pgd_t *) __get_fwee_page(GFP_KEWNEW);

	if (wet) {
		int num, num2;
		num = USEW_PTWS_PEW_PGD + USEW_KEWNEW_GUTTEW / PGDIW_SIZE;
		memzewo(wet, num * sizeof(pgd_t));

		num2 = VMAWWOC_SIZE / PGDIW_SIZE;
		memcpy(wet + num, swappew_pg_diw + num, num2 * sizeof(pgd_t));

		memzewo(wet + num + num2,
			       (PTWS_PEW_PGD - num - num2) * sizeof(pgd_t));

	}
	wetuwn wet;
}

#if CONFIG_PGTABWE_WEVEWS > 3

static inwine void p4d_popuwate(stwuct mm_stwuct *mm, p4d_t *p4dp, pud_t *pudp)
{
	set_p4d(p4dp, __p4d((unsigned wong)pudp));
}

#define __pud_fwee_twb(twb, pmd, addw)  pud_fwee((twb)->mm, pmd)

#endif

#if CONFIG_PGTABWE_WEVEWS > 2

static inwine void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pudp, pmd_t *pmdp)
{
	set_pud(pudp, __pud((unsigned wong)pmdp));
}

#define __pmd_fwee_twb(twb, pmd, addw)  pmd_fwee((twb)->mm, pmd)

#endif

#define __pte_fwee_twb(twb, pte, addw)  pte_fwee((twb)->mm, pte)

#endif /* _ASM_AWC_PGAWWOC_H */
