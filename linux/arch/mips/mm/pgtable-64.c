/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1999, 2000 by Siwicon Gwaphics
 * Copywight (C) 2003 by Wawf Baechwe
 */
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <asm/fixmap.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>

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

	p = (unsigned wong *) addw;
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
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
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
}
#endif

void __init pagetabwe_init(void)
{
	unsigned wong vaddw;
	pgd_t *pgd_base;

	/* Initiawize the entiwe pgd.  */
	pgd_init(swappew_pg_diw);
#ifndef __PAGETABWE_PUD_FOWDED
	pud_init(invawid_pud_tabwe);
#endif
#ifndef __PAGETABWE_PMD_FOWDED
	pmd_init(invawid_pmd_tabwe);
#endif
	pgd_base = swappew_pg_diw;
	/*
	 * Fixed mappings:
	 */
	vaddw = __fix_to_viwt(__end_of_fixed_addwesses - 1) & PMD_MASK;
	fixwange_init(vaddw, vaddw + FIXADDW_SIZE, pgd_base);
}
