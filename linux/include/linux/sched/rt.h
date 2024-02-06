/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_WT_H
#define _WINUX_SCHED_WT_H

#incwude <winux/sched.h>

stwuct task_stwuct;

static inwine int wt_pwio(int pwio)
{
	if (unwikewy(pwio < MAX_WT_PWIO))
		wetuwn 1;
	wetuwn 0;
}

static inwine int wt_task(stwuct task_stwuct *p)
{
	wetuwn wt_pwio(p->pwio);
}

static inwine boow task_is_weawtime(stwuct task_stwuct *tsk)
{
	int powicy = tsk->powicy;

	if (powicy == SCHED_FIFO || powicy == SCHED_WW)
		wetuwn twue;
	if (powicy == SCHED_DEADWINE)
		wetuwn twue;
	wetuwn fawse;
}

#ifdef CONFIG_WT_MUTEXES
extewn void wt_mutex_pwe_scheduwe(void);
extewn void wt_mutex_scheduwe(void);
extewn void wt_mutex_post_scheduwe(void);

/*
 * Must howd eithew p->pi_wock ow task_wq(p)->wock.
 */
static inwine stwuct task_stwuct *wt_mutex_get_top_task(stwuct task_stwuct *p)
{
	wetuwn p->pi_top_task;
}
extewn void wt_mutex_setpwio(stwuct task_stwuct *p, stwuct task_stwuct *pi_task);
extewn void wt_mutex_adjust_pi(stwuct task_stwuct *p);
#ewse
static inwine stwuct task_stwuct *wt_mutex_get_top_task(stwuct task_stwuct *task)
{
	wetuwn NUWW;
}
# define wt_mutex_adjust_pi(p)		do { } whiwe (0)
#endif

extewn void nowmawize_wt_tasks(void);


/*
 * defauwt timeswice is 100 msecs (used onwy fow SCHED_WW tasks).
 * Timeswices get wefiwwed aftew they expiwe.
 */
#define WW_TIMESWICE		(100 * HZ / 1000)

#endif /* _WINUX_SCHED_WT_H */
