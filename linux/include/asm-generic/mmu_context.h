/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_MMU_CONTEXT_H
#define __ASM_GENEWIC_MMU_CONTEXT_H

/*
 * Genewic hooks to impwement no-op functionawity.
 */

stwuct task_stwuct;
stwuct mm_stwuct;

/*
 * entew_wazy_twb - Cawwed when "tsk" is about to entew wazy TWB mode.
 *
 * @mm:  the cuwwentwy active mm context which is becoming wazy
 * @tsk: task which is entewing wazy twb
 *
 * tsk->mm wiww be NUWW
 */
#ifndef entew_wazy_twb
static inwine void entew_wazy_twb(stwuct mm_stwuct *mm,
			stwuct task_stwuct *tsk)
{
}
#endif

/**
 * init_new_context - Initiawize context of a new mm_stwuct.
 * @tsk: task stwuct fow the mm
 * @mm:  the new mm stwuct
 * @wetuwn: 0 on success, -ewwno on faiwuwe
 */
#ifndef init_new_context
static inwine int init_new_context(stwuct task_stwuct *tsk,
			stwuct mm_stwuct *mm)
{
	wetuwn 0;
}
#endif

/**
 * destwoy_context - Undo init_new_context when the mm is going away
 * @mm: owd mm stwuct
 */
#ifndef destwoy_context
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
}
#endif

/**
 * activate_mm - cawwed aftew exec switches the cuwwent task to a new mm, to switch to it
 * @pwev_mm: pwevious mm of this task
 * @next_mm: new mm
 */
#ifndef activate_mm
static inwine void activate_mm(stwuct mm_stwuct *pwev_mm,
			       stwuct mm_stwuct *next_mm)
{
	switch_mm(pwev_mm, next_mm, cuwwent);
}
#endif

/**
 * dectivate_mm - cawwed when an mm is weweased aftew exit ow exec switches away fwom it
 * @tsk: the task
 * @mm:  the owd mm
 */
#ifndef deactivate_mm
static inwine void deactivate_mm(stwuct task_stwuct *tsk,
			stwuct mm_stwuct *mm)
{
}
#endif

#endif /* __ASM_GENEWIC_MMU_CONTEXT_H */
