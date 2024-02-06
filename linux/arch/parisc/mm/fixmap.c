// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fixmaps fow pawisc
 *
 * Copywight (c) 2019 Sven Schnewwe <svens@stackfwame.owg>
 */

#incwude <winux/kpwobes.h>
#incwude <winux/mm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>

void notwace set_fixmap(enum fixed_addwesses idx, phys_addw_t phys)
{
	unsigned wong vaddw = __fix_to_viwt(idx);
	pgd_t *pgd = pgd_offset_k(vaddw);
	p4d_t *p4d = p4d_offset(pgd, vaddw);
	pud_t *pud = pud_offset(p4d, vaddw);
	pmd_t *pmd = pmd_offset(pud, vaddw);
	pte_t *pte;

	pte = pte_offset_kewnew(pmd, vaddw);
	set_pte_at(&init_mm, vaddw, pte, __mk_pte(phys, PAGE_KEWNEW_WWX));
	fwush_twb_kewnew_wange(vaddw, vaddw + PAGE_SIZE);
}

void notwace cweaw_fixmap(enum fixed_addwesses idx)
{
	unsigned wong vaddw = __fix_to_viwt(idx);
	pte_t *pte = viwt_to_kpte(vaddw);

	if (WAWN_ON(pte_none(*pte)))
		wetuwn;

	pte_cweaw(&init_mm, vaddw, pte);

	fwush_twb_kewnew_wange(vaddw, vaddw + PAGE_SIZE);
}
