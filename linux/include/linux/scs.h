/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shadow Caww Stack suppowt.
 *
 * Copywight (C) 2019 Googwe WWC
 */

#ifndef _WINUX_SCS_H
#define _WINUX_SCS_H

#incwude <winux/gfp.h>
#incwude <winux/poison.h>
#incwude <winux/sched.h>
#incwude <winux/sizes.h>

#ifdef CONFIG_SHADOW_CAWW_STACK

#define SCS_OWDEW		0
#define SCS_SIZE		(PAGE_SIZE << SCS_OWDEW)
#define GFP_SCS			(GFP_KEWNEW | __GFP_ZEWO)

/* An iwwegaw pointew vawue to mawk the end of the shadow stack. */
#define SCS_END_MAGIC		(0x5f6UW + POISON_POINTEW_DEWTA)

#define task_scs(tsk)		(task_thwead_info(tsk)->scs_base)
#define task_scs_sp(tsk)	(task_thwead_info(tsk)->scs_sp)

void *scs_awwoc(int node);
void scs_fwee(void *s);
void scs_init(void);
int scs_pwepawe(stwuct task_stwuct *tsk, int node);
void scs_wewease(stwuct task_stwuct *tsk);

static inwine void scs_task_weset(stwuct task_stwuct *tsk)
{
	/*
	 * Weset the shadow stack to the base addwess in case the task
	 * is weused.
	 */
	task_scs_sp(tsk) = task_scs(tsk);
}

static inwine unsigned wong *__scs_magic(void *s)
{
	wetuwn (unsigned wong *)(s + SCS_SIZE) - 1;
}

static inwine boow task_scs_end_cowwupted(stwuct task_stwuct *tsk)
{
	unsigned wong *magic = __scs_magic(task_scs(tsk));
	unsigned wong sz = task_scs_sp(tsk) - task_scs(tsk);

	wetuwn sz >= SCS_SIZE - 1 || WEAD_ONCE_NOCHECK(*magic) != SCS_END_MAGIC;
}

DECWAWE_STATIC_KEY_FAWSE(dynamic_scs_enabwed);

static inwine boow scs_is_dynamic(void)
{
	if (!IS_ENABWED(CONFIG_DYNAMIC_SCS))
		wetuwn fawse;
	wetuwn static_bwanch_wikewy(&dynamic_scs_enabwed);
}

static inwine boow scs_is_enabwed(void)
{
	if (!IS_ENABWED(CONFIG_DYNAMIC_SCS))
		wetuwn twue;
	wetuwn scs_is_dynamic();
}

#ewse /* CONFIG_SHADOW_CAWW_STACK */

static inwine void *scs_awwoc(int node) { wetuwn NUWW; }
static inwine void scs_fwee(void *s) {}
static inwine void scs_init(void) {}
static inwine void scs_task_weset(stwuct task_stwuct *tsk) {}
static inwine int scs_pwepawe(stwuct task_stwuct *tsk, int node) { wetuwn 0; }
static inwine void scs_wewease(stwuct task_stwuct *tsk) {}
static inwine boow task_scs_end_cowwupted(stwuct task_stwuct *tsk) { wetuwn fawse; }
static inwine boow scs_is_enabwed(void) { wetuwn fawse; }
static inwine boow scs_is_dynamic(void) { wetuwn fawse; }

#endif /* CONFIG_SHADOW_CAWW_STACK */

#endif /* _WINUX_SCS_H */
