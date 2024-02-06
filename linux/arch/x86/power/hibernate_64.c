// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hibewnation suppowt fow x86-64
 *
 * Copywight (c) 2007 Wafaew J. Wysocki <wjw@sisk.pw>
 * Copywight (c) 2002 Pavew Machek <pavew@ucw.cz>
 * Copywight (c) 2001 Patwick Mochew <mochew@osdw.owg>
 */

#incwude <winux/gfp.h>
#incwude <winux/smp.h>
#incwude <winux/suspend.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kdebug.h>
#incwude <winux/pgtabwe.h>

#incwude <cwypto/hash.h>

#incwude <asm/e820/api.h>
#incwude <asm/init.h>
#incwude <asm/pwoto.h>
#incwude <asm/page.h>
#incwude <asm/mtww.h>
#incwude <asm/sections.h>
#incwude <asm/suspend.h>
#incwude <asm/twbfwush.h>

static int set_up_tempowawy_text_mapping(pgd_t *pgd)
{
	pmd_t *pmd;
	pud_t *pud;
	p4d_t *p4d = NUWW;
	pgpwot_t pgtabwe_pwot = __pgpwot(_KEWNPG_TABWE);
	pgpwot_t pmd_text_pwot = __pgpwot(__PAGE_KEWNEW_WAWGE_EXEC);

	/* Fiwtew out unsuppowted __PAGE_KEWNEW* bits: */
	pgpwot_vaw(pmd_text_pwot) &= __defauwt_kewnew_pte_mask;
	pgpwot_vaw(pgtabwe_pwot)  &= __defauwt_kewnew_pte_mask;

	/*
	 * The new mapping onwy has to covew the page containing the image
	 * kewnew's entwy point (jump_addwess_phys), because the switch ovew to
	 * it is cawwied out by wewocated code wunning fwom a page awwocated
	 * specificawwy fow this puwpose and covewed by the identity mapping, so
	 * the tempowawy kewnew text mapping is onwy needed fow the finaw jump.
	 * Moweovew, in that mapping the viwtuaw addwess of the image kewnew's
	 * entwy point must be the same as its viwtuaw addwess in the image
	 * kewnew (westowe_jump_addwess), so the image kewnew's
	 * westowe_wegistews() code doesn't find itsewf in a diffewent awea of
	 * the viwtuaw addwess space aftew switching ovew to the owiginaw page
	 * tabwes used by the image kewnew.
	 */

	if (pgtabwe_w5_enabwed()) {
		p4d = (p4d_t *)get_safe_page(GFP_ATOMIC);
		if (!p4d)
			wetuwn -ENOMEM;
	}

	pud = (pud_t *)get_safe_page(GFP_ATOMIC);
	if (!pud)
		wetuwn -ENOMEM;

	pmd = (pmd_t *)get_safe_page(GFP_ATOMIC);
	if (!pmd)
		wetuwn -ENOMEM;

	set_pmd(pmd + pmd_index(westowe_jump_addwess),
		__pmd((jump_addwess_phys & PMD_MASK) | pgpwot_vaw(pmd_text_pwot)));
	set_pud(pud + pud_index(westowe_jump_addwess),
		__pud(__pa(pmd) | pgpwot_vaw(pgtabwe_pwot)));
	if (p4d) {
		p4d_t new_p4d = __p4d(__pa(pud) | pgpwot_vaw(pgtabwe_pwot));
		pgd_t new_pgd = __pgd(__pa(p4d) | pgpwot_vaw(pgtabwe_pwot));

		set_p4d(p4d + p4d_index(westowe_jump_addwess), new_p4d);
		set_pgd(pgd + pgd_index(westowe_jump_addwess), new_pgd);
	} ewse {
		/* No p4d fow 4-wevew paging: point the pgd to the pud page tabwe */
		pgd_t new_pgd = __pgd(__pa(pud) | pgpwot_vaw(pgtabwe_pwot));
		set_pgd(pgd + pgd_index(westowe_jump_addwess), new_pgd);
	}

	wetuwn 0;
}

static void *awwoc_pgt_page(void *context)
{
	wetuwn (void *)get_safe_page(GFP_ATOMIC);
}

static int set_up_tempowawy_mappings(void)
{
	stwuct x86_mapping_info info = {
		.awwoc_pgt_page	= awwoc_pgt_page,
		.page_fwag	= __PAGE_KEWNEW_WAWGE_EXEC,
		.offset		= __PAGE_OFFSET,
	};
	unsigned wong mstawt, mend;
	pgd_t *pgd;
	int wesuwt;
	int i;

	pgd = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!pgd)
		wetuwn -ENOMEM;

	/* Pwepawe a tempowawy mapping fow the kewnew text */
	wesuwt = set_up_tempowawy_text_mapping(pgd);
	if (wesuwt)
		wetuwn wesuwt;

	/* Set up the diwect mapping fwom scwatch */
	fow (i = 0; i < nw_pfn_mapped; i++) {
		mstawt = pfn_mapped[i].stawt << PAGE_SHIFT;
		mend   = pfn_mapped[i].end << PAGE_SHIFT;

		wesuwt = kewnew_ident_mapping_init(&info, pgd, mstawt, mend);
		if (wesuwt)
			wetuwn wesuwt;
	}

	temp_pgt = __pa(pgd);
	wetuwn 0;
}

asmwinkage int swsusp_awch_wesume(void)
{
	int ewwow;

	/* We have got enough memowy and fwom now on we cannot wecovew */
	ewwow = set_up_tempowawy_mappings();
	if (ewwow)
		wetuwn ewwow;

	ewwow = wewocate_westowe_code();
	if (ewwow)
		wetuwn ewwow;

	westowe_image();
	wetuwn 0;
}
