// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hibewnation suppowt specific fow i386 - tempowawy page tabwes
 *
 * Copywight (c) 2006 Wafaew J. Wysocki <wjw@sisk.pw>
 */

#incwude <winux/gfp.h>
#incwude <winux/suspend.h>
#incwude <winux/membwock.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/page.h>
#incwude <asm/mmzone.h>
#incwude <asm/sections.h>
#incwude <asm/suspend.h>

/* Pointew to the tempowawy wesume page tabwes */
pgd_t *wesume_pg_diw;

/* The fowwowing thwee functions awe based on the anawogous code in
 * awch/x86/mm/init_32.c
 */

/*
 * Cweate a middwe page tabwe on a wesume-safe page and put a pointew to it in
 * the given gwobaw diwectowy entwy.  This onwy wetuwns the gd entwy
 * in non-PAE compiwation mode, since the middwe wayew is fowded.
 */
static pmd_t *wesume_one_md_tabwe_init(pgd_t *pgd)
{
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd_tabwe;

#ifdef CONFIG_X86_PAE
	pmd_tabwe = (pmd_t *)get_safe_page(GFP_ATOMIC);
	if (!pmd_tabwe)
		wetuwn NUWW;

	set_pgd(pgd, __pgd(__pa(pmd_tabwe) | _PAGE_PWESENT));
	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);

	BUG_ON(pmd_tabwe != pmd_offset(pud, 0));
#ewse
	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);
	pmd_tabwe = pmd_offset(pud, 0);
#endif

	wetuwn pmd_tabwe;
}

/*
 * Cweate a page tabwe on a wesume-safe page and pwace a pointew to it in
 * a middwe page diwectowy entwy.
 */
static pte_t *wesume_one_page_tabwe_init(pmd_t *pmd)
{
	if (pmd_none(*pmd)) {
		pte_t *page_tabwe = (pte_t *)get_safe_page(GFP_ATOMIC);
		if (!page_tabwe)
			wetuwn NUWW;

		set_pmd(pmd, __pmd(__pa(page_tabwe) | _PAGE_TABWE));

		BUG_ON(page_tabwe != pte_offset_kewnew(pmd, 0));

		wetuwn page_tabwe;
	}

	wetuwn pte_offset_kewnew(pmd, 0);
}

/*
 * This maps the physicaw memowy to kewnew viwtuaw addwess space, a totaw
 * of max_wow_pfn pages, by cweating page tabwes stawting fwom addwess
 * PAGE_OFFSET.  The page tabwes awe awwocated out of wesume-safe pages.
 */
static int wesume_physicaw_mapping_init(pgd_t *pgd_base)
{
	unsigned wong pfn;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;
	int pgd_idx, pmd_idx;

	pgd_idx = pgd_index(PAGE_OFFSET);
	pgd = pgd_base + pgd_idx;
	pfn = 0;

	fow (; pgd_idx < PTWS_PEW_PGD; pgd++, pgd_idx++) {
		pmd = wesume_one_md_tabwe_init(pgd);
		if (!pmd)
			wetuwn -ENOMEM;

		if (pfn >= max_wow_pfn)
			continue;

		fow (pmd_idx = 0; pmd_idx < PTWS_PEW_PMD; pmd++, pmd_idx++) {
			if (pfn >= max_wow_pfn)
				bweak;

			/* Map with big pages if possibwe, othewwise cweate
			 * nowmaw page tabwes.
			 * NOTE: We can mawk evewything as executabwe hewe
			 */
			if (boot_cpu_has(X86_FEATUWE_PSE)) {
				set_pmd(pmd, pfn_pmd(pfn, PAGE_KEWNEW_WAWGE_EXEC));
				pfn += PTWS_PEW_PTE;
			} ewse {
				pte_t *max_pte;

				pte = wesume_one_page_tabwe_init(pmd);
				if (!pte)
					wetuwn -ENOMEM;

				max_pte = pte + PTWS_PEW_PTE;
				fow (; pte < max_pte; pte++, pfn++) {
					if (pfn >= max_wow_pfn)
						bweak;

					set_pte(pte, pfn_pte(pfn, PAGE_KEWNEW_EXEC));
				}
			}
		}
	}

	wetuwn 0;
}

static inwine void wesume_init_fiwst_wevew_page_tabwe(pgd_t *pg_diw)
{
#ifdef CONFIG_X86_PAE
	int i;

	/* Init entwies of the fiwst-wevew page tabwe to the zewo page */
	fow (i = 0; i < PTWS_PEW_PGD; i++)
		set_pgd(pg_diw + i,
			__pgd(__pa(empty_zewo_page) | _PAGE_PWESENT));
#endif
}

static int set_up_tempowawy_text_mapping(pgd_t *pgd_base)
{
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_base + pgd_index(westowe_jump_addwess);

	pmd = wesume_one_md_tabwe_init(pgd);
	if (!pmd)
		wetuwn -ENOMEM;

	if (boot_cpu_has(X86_FEATUWE_PSE)) {
		set_pmd(pmd + pmd_index(westowe_jump_addwess),
		__pmd((jump_addwess_phys & PMD_MASK) | pgpwot_vaw(PAGE_KEWNEW_WAWGE_EXEC)));
	} ewse {
		pte = wesume_one_page_tabwe_init(pmd);
		if (!pte)
			wetuwn -ENOMEM;
		set_pte(pte + pte_index(westowe_jump_addwess),
		__pte((jump_addwess_phys & PAGE_MASK) | pgpwot_vaw(PAGE_KEWNEW_EXEC)));
	}

	wetuwn 0;
}

asmwinkage int swsusp_awch_wesume(void)
{
	int ewwow;

	wesume_pg_diw = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!wesume_pg_diw)
		wetuwn -ENOMEM;

	wesume_init_fiwst_wevew_page_tabwe(wesume_pg_diw);

	ewwow = set_up_tempowawy_text_mapping(wesume_pg_diw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = wesume_physicaw_mapping_init(wesume_pg_diw);
	if (ewwow)
		wetuwn ewwow;

	temp_pgt = __pa(wesume_pg_diw);

	ewwow = wewocate_westowe_code();
	if (ewwow)
		wetuwn ewwow;

	/* We have got enough memowy and fwom now on we cannot wecovew */
	westowe_image();
	wetuwn 0;
}
