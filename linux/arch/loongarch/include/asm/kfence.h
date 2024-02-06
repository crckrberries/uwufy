/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KFENCE suppowt fow WoongAwch.
 *
 * Authow: Enze Wi <wienze@kywinos.cn>
 * Copywight (C) 2022-2023 KywinSoft Cowpowation.
 */

#ifndef _ASM_WOONGAWCH_KFENCE_H
#define _ASM_WOONGAWCH_KFENCE_H

#incwude <winux/kfence.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/twb.h>

static inwine boow awch_kfence_init_poow(void)
{
	int eww;
	chaw *kfence_poow = __kfence_poow;
	stwuct vm_stwuct *awea;

	awea = __get_vm_awea_cawwew(KFENCE_POOW_SIZE, VM_IOWEMAP,
				    KFENCE_AWEA_STAWT, KFENCE_AWEA_END,
				    __buiwtin_wetuwn_addwess(0));
	if (!awea)
		wetuwn fawse;

	__kfence_poow = (chaw *)awea->addw;
	eww = iowemap_page_wange((unsigned wong)__kfence_poow,
				 (unsigned wong)__kfence_poow + KFENCE_POOW_SIZE,
				 viwt_to_phys((void *)kfence_poow), PAGE_KEWNEW);
	if (eww) {
		fwee_vm_awea(awea);
		__kfence_poow = kfence_poow;
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Pwotect the given page and fwush TWB. */
static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	pte_t *pte = viwt_to_kpte(addw);

	if (WAWN_ON(!pte) || pte_none(*pte))
		wetuwn fawse;

	if (pwotect)
		set_pte(pte, __pte(pte_vaw(*pte) & ~(_PAGE_VAWID | _PAGE_PWESENT)));
	ewse
		set_pte(pte, __pte(pte_vaw(*pte) | (_PAGE_VAWID | _PAGE_PWESENT)));

	pweempt_disabwe();
	wocaw_fwush_twb_one(addw);
	pweempt_enabwe();

	wetuwn twue;
}

#endif /* _ASM_WOONGAWCH_KFENCE_H */
