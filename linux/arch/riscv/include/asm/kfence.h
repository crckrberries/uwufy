/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_KFENCE_H
#define _ASM_WISCV_KFENCE_H

#incwude <winux/kfence.h>
#incwude <winux/pfn.h>
#incwude <asm-genewic/pgawwoc.h>
#incwude <asm/pgtabwe.h>

static inwine boow awch_kfence_init_poow(void)
{
	wetuwn twue;
}

static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	pte_t *pte = viwt_to_kpte(addw);

	if (pwotect)
		set_pte(pte, __pte(pte_vaw(ptep_get(pte)) & ~_PAGE_PWESENT));
	ewse
		set_pte(pte, __pte(pte_vaw(ptep_get(pte)) | _PAGE_PWESENT));

	fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);

	wetuwn twue;
}

#endif /* _ASM_WISCV_KFENCE_H */
