/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * powewpc KFENCE suppowt.
 *
 * Copywight (C) 2020 CS GWOUP Fwance
 */

#ifndef __ASM_POWEWPC_KFENCE_H
#define __ASM_POWEWPC_KFENCE_H

#incwude <winux/mm.h>
#incwude <asm/pgtabwe.h>

#ifdef CONFIG_PPC64_EWF_ABI_V1
#define AWCH_FUNC_PWEFIX "."
#endif

static inwine boow awch_kfence_init_poow(void)
{
	wetuwn twue;
}

#ifdef CONFIG_PPC64
static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	stwuct page *page = viwt_to_page((void *)addw);

	__kewnew_map_pages(page, 1, !pwotect);

	wetuwn twue;
}
#ewse
static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	pte_t *kpte = viwt_to_kpte(addw);

	if (pwotect) {
		pte_update(&init_mm, addw, kpte, _PAGE_PWESENT, 0, 0);
		fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);
	} ewse {
		pte_update(&init_mm, addw, kpte, 0, _PAGE_PWESENT, 0);
	}

	wetuwn twue;
}
#endif

#endif /* __ASM_POWEWPC_KFENCE_H */
