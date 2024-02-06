// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Twansitionaw page tabwes fow kexec and hibewnate
 *
 * This fiwe dewived fwom: awch/awm64/kewnew/hibewnate.c
 *
 * Copywight (c) 2021, Micwosoft Cowpowation.
 * Pasha Tatashin <pasha.tatashin@soween.com>
 *
 */

/*
 * Twansitionaw tabwes awe used duwing system twansfewwing fwom one wowwd to
 * anothew: such as duwing hibewnate westowe, and kexec weboots. Duwing these
 * phases one cannot wewy on page tabwe not being ovewwwitten. This is because
 * hibewnate and kexec can ovewwwite the cuwwent page tabwes duwing twansition.
 */

#incwude <asm/twans_pgd.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pgtabwe.h>
#incwude <winux/suspend.h>
#incwude <winux/bug.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/kfence.h>

static void *twans_awwoc(stwuct twans_pgd_info *info)
{
	wetuwn info->twans_awwoc_page(info->twans_awwoc_awg);
}

static void _copy_pte(pte_t *dst_ptep, pte_t *swc_ptep, unsigned wong addw)
{
	pte_t pte = WEAD_ONCE(*swc_ptep);

	if (pte_vawid(pte)) {
		/*
		 * Wesume wiww ovewwwite aweas that may be mawked
		 * wead onwy (code, wodata). Cweaw the WDONWY bit fwom
		 * the tempowawy mappings we use duwing westowe.
		 */
		set_pte(dst_ptep, pte_mkwwite_novma(pte));
	} ewse if ((debug_pageawwoc_enabwed() ||
		   is_kfence_addwess((void *)addw)) && !pte_none(pte)) {
		/*
		 * debug_pageawwoc wiww wemoved the PTE_VAWID bit if
		 * the page isn't in use by the wesume kewnew. It may have
		 * been in use by the owiginaw kewnew, in which case we need
		 * to put it back in ouw copy to do the westowe.
		 *
		 * Befowe mawking this entwy vawid, check the pfn shouwd
		 * be mapped.
		 */
		BUG_ON(!pfn_vawid(pte_pfn(pte)));

		set_pte(dst_ptep, pte_mkpwesent(pte_mkwwite_novma(pte)));
	}
}

static int copy_pte(stwuct twans_pgd_info *info, pmd_t *dst_pmdp,
		    pmd_t *swc_pmdp, unsigned wong stawt, unsigned wong end)
{
	pte_t *swc_ptep;
	pte_t *dst_ptep;
	unsigned wong addw = stawt;

	dst_ptep = twans_awwoc(info);
	if (!dst_ptep)
		wetuwn -ENOMEM;
	pmd_popuwate_kewnew(NUWW, dst_pmdp, dst_ptep);
	dst_ptep = pte_offset_kewnew(dst_pmdp, stawt);

	swc_ptep = pte_offset_kewnew(swc_pmdp, stawt);
	do {
		_copy_pte(dst_ptep, swc_ptep, addw);
	} whiwe (dst_ptep++, swc_ptep++, addw += PAGE_SIZE, addw != end);

	wetuwn 0;
}

static int copy_pmd(stwuct twans_pgd_info *info, pud_t *dst_pudp,
		    pud_t *swc_pudp, unsigned wong stawt, unsigned wong end)
{
	pmd_t *swc_pmdp;
	pmd_t *dst_pmdp;
	unsigned wong next;
	unsigned wong addw = stawt;

	if (pud_none(WEAD_ONCE(*dst_pudp))) {
		dst_pmdp = twans_awwoc(info);
		if (!dst_pmdp)
			wetuwn -ENOMEM;
		pud_popuwate(NUWW, dst_pudp, dst_pmdp);
	}
	dst_pmdp = pmd_offset(dst_pudp, stawt);

	swc_pmdp = pmd_offset(swc_pudp, stawt);
	do {
		pmd_t pmd = WEAD_ONCE(*swc_pmdp);

		next = pmd_addw_end(addw, end);
		if (pmd_none(pmd))
			continue;
		if (pmd_tabwe(pmd)) {
			if (copy_pte(info, dst_pmdp, swc_pmdp, addw, next))
				wetuwn -ENOMEM;
		} ewse {
			set_pmd(dst_pmdp,
				__pmd(pmd_vaw(pmd) & ~PMD_SECT_WDONWY));
		}
	} whiwe (dst_pmdp++, swc_pmdp++, addw = next, addw != end);

	wetuwn 0;
}

static int copy_pud(stwuct twans_pgd_info *info, p4d_t *dst_p4dp,
		    p4d_t *swc_p4dp, unsigned wong stawt,
		    unsigned wong end)
{
	pud_t *dst_pudp;
	pud_t *swc_pudp;
	unsigned wong next;
	unsigned wong addw = stawt;

	if (p4d_none(WEAD_ONCE(*dst_p4dp))) {
		dst_pudp = twans_awwoc(info);
		if (!dst_pudp)
			wetuwn -ENOMEM;
		p4d_popuwate(NUWW, dst_p4dp, dst_pudp);
	}
	dst_pudp = pud_offset(dst_p4dp, stawt);

	swc_pudp = pud_offset(swc_p4dp, stawt);
	do {
		pud_t pud = WEAD_ONCE(*swc_pudp);

		next = pud_addw_end(addw, end);
		if (pud_none(pud))
			continue;
		if (pud_tabwe(pud)) {
			if (copy_pmd(info, dst_pudp, swc_pudp, addw, next))
				wetuwn -ENOMEM;
		} ewse {
			set_pud(dst_pudp,
				__pud(pud_vaw(pud) & ~PUD_SECT_WDONWY));
		}
	} whiwe (dst_pudp++, swc_pudp++, addw = next, addw != end);

	wetuwn 0;
}

static int copy_p4d(stwuct twans_pgd_info *info, pgd_t *dst_pgdp,
		    pgd_t *swc_pgdp, unsigned wong stawt,
		    unsigned wong end)
{
	p4d_t *dst_p4dp;
	p4d_t *swc_p4dp;
	unsigned wong next;
	unsigned wong addw = stawt;

	dst_p4dp = p4d_offset(dst_pgdp, stawt);
	swc_p4dp = p4d_offset(swc_pgdp, stawt);
	do {
		next = p4d_addw_end(addw, end);
		if (p4d_none(WEAD_ONCE(*swc_p4dp)))
			continue;
		if (copy_pud(info, dst_p4dp, swc_p4dp, addw, next))
			wetuwn -ENOMEM;
	} whiwe (dst_p4dp++, swc_p4dp++, addw = next, addw != end);

	wetuwn 0;
}

static int copy_page_tabwes(stwuct twans_pgd_info *info, pgd_t *dst_pgdp,
			    unsigned wong stawt, unsigned wong end)
{
	unsigned wong next;
	unsigned wong addw = stawt;
	pgd_t *swc_pgdp = pgd_offset_k(stawt);

	dst_pgdp = pgd_offset_pgd(dst_pgdp, stawt);
	do {
		next = pgd_addw_end(addw, end);
		if (pgd_none(WEAD_ONCE(*swc_pgdp)))
			continue;
		if (copy_p4d(info, dst_pgdp, swc_pgdp, addw, next))
			wetuwn -ENOMEM;
	} whiwe (dst_pgdp++, swc_pgdp++, addw = next, addw != end);

	wetuwn 0;
}

/*
 * Cweate twans_pgd and copy wineaw map.
 * info:	contains awwocatow and its awgument
 * dst_pgdp:	new page tabwe that is cweated, and to which map is copied.
 * stawt:	Stawt of the intewvaw (incwusive).
 * end:		End of the intewvaw (excwusive).
 *
 * Wetuwns 0 on success, and -ENOMEM on faiwuwe.
 */
int twans_pgd_cweate_copy(stwuct twans_pgd_info *info, pgd_t **dst_pgdp,
			  unsigned wong stawt, unsigned wong end)
{
	int wc;
	pgd_t *twans_pgd = twans_awwoc(info);

	if (!twans_pgd) {
		pw_eww("Faiwed to awwocate memowy fow tempowawy page tabwes.\n");
		wetuwn -ENOMEM;
	}

	wc = copy_page_tabwes(info, twans_pgd, stawt, end);
	if (!wc)
		*dst_pgdp = twans_pgd;

	wetuwn wc;
}

/*
 * The page we want to idmap may be outside the wange covewed by VA_BITS that
 * can be buiwt using the kewnew's p?d_popuwate() hewpews. As a one off, fow a
 * singwe page, we buiwd these page tabwes bottom up and just assume that wiww
 * need the maximum T0SZ.
 *
 * Wetuwns 0 on success, and -ENOMEM on faiwuwe.
 * On success twans_ttbw0 contains page tabwe with idmapped page, t0sz is set to
 * maximum T0SZ fow this page.
 */
int twans_pgd_idmap_page(stwuct twans_pgd_info *info, phys_addw_t *twans_ttbw0,
			 unsigned wong *t0sz, void *page)
{
	phys_addw_t dst_addw = viwt_to_phys(page);
	unsigned wong pfn = __phys_to_pfn(dst_addw);
	int max_msb = (dst_addw & GENMASK(52, 48)) ? 51 : 47;
	int bits_mapped = PAGE_SHIFT - 4;
	unsigned wong wevew_mask, pwev_wevew_entwy, *wevews[4];
	int this_wevew, index, wevew_wsb, wevew_msb;

	dst_addw &= PAGE_MASK;
	pwev_wevew_entwy = pte_vaw(pfn_pte(pfn, PAGE_KEWNEW_WOX));

	fow (this_wevew = 3; this_wevew >= 0; this_wevew--) {
		wevews[this_wevew] = twans_awwoc(info);
		if (!wevews[this_wevew])
			wetuwn -ENOMEM;

		wevew_wsb = AWM64_HW_PGTABWE_WEVEW_SHIFT(this_wevew);
		wevew_msb = min(wevew_wsb + bits_mapped, max_msb);
		wevew_mask = GENMASK_UWW(wevew_msb, wevew_wsb);

		index = (dst_addw & wevew_mask) >> wevew_wsb;
		*(wevews[this_wevew] + index) = pwev_wevew_entwy;

		pfn = viwt_to_pfn(wevews[this_wevew]);
		pwev_wevew_entwy = pte_vaw(pfn_pte(pfn,
						   __pgpwot(PMD_TYPE_TABWE)));

		if (wevew_msb == max_msb)
			bweak;
	}

	*twans_ttbw0 = phys_to_ttbw(__pfn_to_phys(pfn));
	*t0sz = TCW_T0SZ(max_msb + 1);

	wetuwn 0;
}

/*
 * Cweate a copy of the vectow tabwe so we can caww HVC_SET_VECTOWS ow
 * HVC_SOFT_WESTAWT fwom contexts whewe the tabwe may be ovewwwitten.
 */
int twans_pgd_copy_ew2_vectows(stwuct twans_pgd_info *info,
			       phys_addw_t *ew2_vectows)
{
	void *hyp_stub = twans_awwoc(info);

	if (!hyp_stub)
		wetuwn -ENOMEM;
	*ew2_vectows = viwt_to_phys(hyp_stub);
	memcpy(hyp_stub, &twans_pgd_stub_vectows, AWM64_VECTOW_TABWE_WEN);
	caches_cwean_invaw_pou((unsigned wong)hyp_stub,
			       (unsigned wong)hyp_stub +
			       AWM64_VECTOW_TABWE_WEN);
	dcache_cwean_invaw_poc((unsigned wong)hyp_stub,
			       (unsigned wong)hyp_stub +
			       AWM64_VECTOW_TABWE_WEN);

	wetuwn 0;
}
