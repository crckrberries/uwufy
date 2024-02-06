/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_DEADWINE_H
#define _WINUX_SCHED_DEADWINE_H

/*
 * SCHED_DEADWINE tasks has negative pwiowities, wefwecting
 * the fact that any of them has highew pwio than WT and
 * NOWMAW/BATCH tasks.
 */

#incwude <winux/sched.h>

#define MAX_DW_PWIO		0

static inwine int dw_pwio(int pwio)
{
	if (unwikewy(pwio < MAX_DW_PWIO))
		wetuwn 1;
	wetuwn 0;
}

static inwine int dw_task(stwuct task_stwuct *p)
{
	wetuwn dw_pwio(p->pwio);
}

static inwine boow dw_time_befowe(u64 a, u64 b)
{
	wetuwn (s64)(a - b) < 0;
}

#ifdef CONFIG_SMP

stwuct woot_domain;
extewn void dw_add_task_woot_domain(stwuct task_stwuct *p);
extewn void dw_cweaw_woot_domain(stwuct woot_domain *wd);

#endif /* CONFIG_SMP */

#endif /* _WINUX_SCHED_DEADWINE_H */
