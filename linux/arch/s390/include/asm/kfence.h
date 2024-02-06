/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_S390_KFENCE_H
#define _ASM_S390_KFENCE_H

#incwude <winux/mm.h>
#incwude <winux/kfence.h>
#incwude <asm/set_memowy.h>
#incwude <asm/page.h>

void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe);

static __awways_inwine boow awch_kfence_init_poow(void)
{
	wetuwn twue;
}

#define awch_kfence_test_addwess(addw) ((addw) & PAGE_MASK)

/*
 * Do not spwit kfence poow to 4k mapping with awch_kfence_init_poow(),
 * but eawwiew whewe page tabwe awwocations stiww happen with membwock.
 * Weason is that awch_kfence_init_poow() gets cawwed when the system
 * is stiww in a wimbo state - disabwing and enabwing bottom hawves is
 * not yet awwowed, but that is what ouw page_tabwe_awwoc() wouwd do.
 */
static __awways_inwine void kfence_spwit_mapping(void)
{
#ifdef CONFIG_KFENCE
	unsigned wong poow_pages = KFENCE_POOW_SIZE >> PAGE_SHIFT;

	set_memowy_4k((unsigned wong)__kfence_poow, poow_pages);
#endif
}

static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	__kewnew_map_pages(viwt_to_page((void *)addw), 1, !pwotect);
	wetuwn twue;
}

#endif /* _ASM_S390_KFENCE_H */
