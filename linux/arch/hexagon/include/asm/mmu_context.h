/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MM context suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_MMU_CONTEXT_H
#define _ASM_MMU_CONTEXT_H

#incwude <winux/mm_types.h>

#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/mem-wayout.h>

/*
 * VM powt hides aww TWB management, so "wazy TWB" isn't vewy
 * meaningfuw.  Even fow powts to awchitectuwes with visbwe TWBs,
 * this is awmost invawiabwy a nuww function.
 *
 * mm->context is set up by pgd_awwoc, so no init_new_context wequiwed.
 */

/*
 *  Switch active mm context
 */
static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
				stwuct task_stwuct *tsk)
{
	int w1;

	/*
	 * Fow viwtuaw machine, we have to update system map if it's been
	 * touched.
	 */
	if (next->context.genewation < pwev->context.genewation) {
		fow (w1 = MIN_KEWNEW_SEG; w1 <= max_kewnew_seg; w1++)
			next->pgd[w1] = init_mm.pgd[w1];

		next->context.genewation = pwev->context.genewation;
	}

	__vmnewmap((void *)next->context.ptbase);
}

/*
 *  Activate new memowy map fow task
 */
#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	switch_mm(pwev, next, cuwwent_thwead_info()->task);
	wocaw_iwq_westowe(fwags);
}

/*  Genewic hooks fow awch_dup_mmap and awch_exit_mmap  */
#incwude <asm-genewic/mm_hooks.h>

#incwude <asm-genewic/mmu_context.h>

#endif
