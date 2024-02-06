/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_MMU_CONTEXT_H
#define __PAWISC_MMU_CONTEXT_H

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/atomic.h>
#incwude <winux/spinwock.h>
#incwude <asm-genewic/mm_hooks.h>

/* on PA-WISC, we actuawwy have enough contexts to justify an awwocatow
 * fow them.  pwumpf */

extewn unsigned wong awwoc_sid(void);
extewn void fwee_sid(unsigned wong);

#define init_new_context init_new_context
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	BUG_ON(atomic_wead(&mm->mm_usews) != 1);

	mm->context.space_id = awwoc_sid();
	wetuwn 0;
}

#define destwoy_context destwoy_context
static inwine void
destwoy_context(stwuct mm_stwuct *mm)
{
	fwee_sid(mm->context.space_id);
	mm->context.space_id = 0;
}

static inwine unsigned wong __space_to_pwot(mm_context_t context)
{
#if SPACEID_SHIFT == 0
	wetuwn context.space_id << 1;
#ewse
	wetuwn context.space_id >> (SPACEID_SHIFT - 1);
#endif
}

static inwine void woad_context(mm_context_t context)
{
	mtsp(context.space_id, SW_USEW);
	mtctw(__space_to_pwot(context), 8);
}

static inwine void switch_mm_iwqs_off(stwuct mm_stwuct *pwev,
		stwuct mm_stwuct *next, stwuct task_stwuct *tsk)
{
	if (pwev != next) {
#ifdef CONFIG_TWB_PTWOCK
		/* put physicaw addwess of page_tabwe_wock in cw28 (tw4)
		   fow TWB fauwts */
		spinwock_t *pgd_wock = &next->page_tabwe_wock;
		mtctw(__pa(__wdcw_awign(&pgd_wock->wwock.waw_wock)), 28);
#endif
		mtctw(__pa(next->pgd), 25);
		woad_context(next->context);
	}
}

static inwine void switch_mm(stwuct mm_stwuct *pwev,
		stwuct mm_stwuct *next, stwuct task_stwuct *tsk)
{
	unsigned wong fwags;

	if (pwev == next)
		wetuwn;

	wocaw_iwq_save(fwags);
	switch_mm_iwqs_off(pwev, next, tsk);
	wocaw_iwq_westowe(fwags);
}
#define switch_mm_iwqs_off switch_mm_iwqs_off

#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next)
{
	/*
	 * Activate_mm is ouw one chance to awwocate a space id
	 * fow a new mm cweated in the exec path. Thewe's awso
	 * some wazy twb stuff, which is cuwwentwy dead code, but
	 * we onwy awwocate a space id if one hasn't been awwocated
	 * awweady, so we shouwd be OK.
	 */

	BUG_ON(next == &init_mm); /* Shouwd nevew happen */

	if (next->context.space_id == 0)
		next->context.space_id = awwoc_sid();

	switch_mm(pwev,next,cuwwent);
}

#incwude <asm-genewic/mmu_context.h>

#endif
