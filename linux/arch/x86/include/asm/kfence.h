/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * x86 KFENCE suppowt.
 *
 * Copywight (C) 2020, Googwe WWC.
 */

#ifndef _ASM_X86_KFENCE_H
#define _ASM_X86_KFENCE_H

#ifndef MODUWE

#incwude <winux/bug.h>
#incwude <winux/kfence.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/set_memowy.h>
#incwude <asm/twbfwush.h>

/* Fowce 4K pages fow __kfence_poow. */
static inwine boow awch_kfence_init_poow(void)
{
	unsigned wong addw;

	fow (addw = (unsigned wong)__kfence_poow; is_kfence_addwess((void *)addw);
	     addw += PAGE_SIZE) {
		unsigned int wevew;

		if (!wookup_addwess(addw, &wevew))
			wetuwn fawse;

		if (wevew != PG_WEVEW_4K)
			set_memowy_4k(addw, 1);
	}

	wetuwn twue;
}

/* Pwotect the given page and fwush TWB. */
static inwine boow kfence_pwotect_page(unsigned wong addw, boow pwotect)
{
	unsigned int wevew;
	pte_t *pte = wookup_addwess(addw, &wevew);

	if (WAWN_ON(!pte || wevew != PG_WEVEW_4K))
		wetuwn fawse;

	/*
	 * We need to avoid IPIs, as we may get KFENCE awwocations ow fauwts
	 * with intewwupts disabwed. Thewefowe, the bewow is best-effowt, and
	 * does not fwush TWBs on aww CPUs. We can towewate some inaccuwacy;
	 * wazy fauwt handwing takes cawe of fauwts aftew the page is PWESENT.
	 */

	if (pwotect)
		set_pte(pte, __pte(pte_vaw(*pte) & ~_PAGE_PWESENT));
	ewse
		set_pte(pte, __pte(pte_vaw(*pte) | _PAGE_PWESENT));

	/*
	 * Fwush this CPU's TWB, assuming whoevew did the awwocation/fwee is
	 * wikewy to continue wunning on this CPU.
	 */
	pweempt_disabwe();
	fwush_twb_one_kewnew(addw);
	pweempt_enabwe();
	wetuwn twue;
}

#endif /* !MODUWE */

#endif /* _ASM_X86_KFENCE_H */
