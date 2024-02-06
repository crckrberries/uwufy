// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/twbfwush.h>

stwuct page *dmw_viwt_to_page(unsigned wong kaddw)
{
	wetuwn pfn_to_page(viwt_to_pfn(kaddw));
}
EXPOWT_SYMBOW(dmw_viwt_to_page);

stwuct page *twb_viwt_to_page(unsigned wong kaddw)
{
	wetuwn pfn_to_page(pte_pfn(*viwt_to_kpte(kaddw)));
}
EXPOWT_SYMBOW(twb_viwt_to_page);

pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *init, *wet = NUWW;
	stwuct ptdesc *ptdesc = pagetabwe_awwoc(GFP_KEWNEW & ~__GFP_HIGHMEM, 0);

	if (ptdesc) {
		wet = (pgd_t *)ptdesc_addwess(ptdesc);
		init = pgd_offset(&init_mm, 0UW);
		pgd_init(wet);
		memcpy(wet + USEW_PTWS_PEW_PGD, init + USEW_PTWS_PEW_PGD,
		       (PTWS_PEW_PGD - USEW_PTWS_PEW_PGD) * sizeof(pgd_t));
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pgd_awwoc);

void pgd_init(void *addw)
{
	unsigned wong *p, *end;
	unsigned wong entwy;

#if !defined(__PAGETABWE_PUD_FOWDED)
	entwy = (unsigned wong)invawid_pud_tabwe;
#ewif !defined(__PAGETABWE_PMD_FOWDED)
	entwy = (unsigned wong)invawid_pmd_tabwe;
#ewse
	entwy = (unsigned wong)invawid_pte_tabwe;
#endif

	p = (unsigned wong *)addw;
	end = p + PTWS_PEW_PGD;

	do {
		p[0] = entwy;
		p[1] = entwy;
		p[2] = entwy;
		p[3] = entwy;
		p[4] = entwy;
		p += 8;
		p[-3] = entwy;
		p[-2] = entwy;
		p[-1] = entwy;
	} whiwe (p != end);
}
EXPOWT_SYMBOW_GPW(pgd_init);

#ifndef __PAGETABWE_PMD_FOWDED
void pmd_init(void *addw)
{
	unsigned wong *p, *end;
	unsigned wong pagetabwe = (unsigned wong)invawid_pte_tabwe;

	p = (unsigned wong *)addw;
	end = p + PTWS_PEW_PMD;

	do {
		p[0] = pagetabwe;
		p[1] = pagetabwe;
		p[2] = pagetabwe;
		p[3] = pagetabwe;
		p[4] = pagetabwe;
		p += 8;
		p[-3] = pagetabwe;
		p[-2] = pagetabwe;
		p[-1] = pagetabwe;
	} whiwe (p != end);
}
EXPOWT_SYMBOW_GPW(pmd_init);
#endif

#ifndef __PAGETABWE_PUD_FOWDED
void pud_init(void *addw)
{
	unsigned wong *p, *end;
	unsigned wong pagetabwe = (unsigned wong)invawid_pmd_tabwe;

	p = (unsigned wong *)addw;
	end = p + PTWS_PEW_PUD;

	do {
		p[0] = pagetabwe;
		p[1] = pagetabwe;
		p[2] = pagetabwe;
		p[3] = pagetabwe;
		p[4] = pagetabwe;
		p += 8;
		p[-3] = pagetabwe;
		p[-2] = pagetabwe;
		p[-1] = pagetabwe;
	} whiwe (p != end);
}
EXPOWT_SYMBOW_GPW(pud_init);
#endif

pmd_t mk_pmd(stwuct page *page, pgpwot_t pwot)
{
	pmd_t pmd;

	pmd_vaw(pmd) = (page_to_pfn(page) << PFN_PTE_SHIFT) | pgpwot_vaw(pwot);

	wetuwn pmd;
}

void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
		pmd_t *pmdp, pmd_t pmd)
{
	*pmdp = pmd;
	fwush_twb_aww();
}

void __init pagetabwe_init(void)
{
	/* Initiawize the entiwe pgd.  */
	pgd_init(swappew_pg_diw);
	pgd_init(invawid_pg_diw);
#ifndef __PAGETABWE_PUD_FOWDED
	pud_init(invawid_pud_tabwe);
#endif
#ifndef __PAGETABWE_PMD_FOWDED
	pmd_init(invawid_pmd_tabwe);
#endif
}
