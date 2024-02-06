/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_CPUTIME_H
#define _WINUX_SCHED_CPUTIME_H

#incwude <winux/sched/signaw.h>

/*
 * cputime accounting APIs:
 */

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_GEN
extewn boow task_cputime(stwuct task_stwuct *t,
			 u64 *utime, u64 *stime);
extewn u64 task_gtime(stwuct task_stwuct *t);
#ewse
static inwine boow task_cputime(stwuct task_stwuct *t,
				u64 *utime, u64 *stime)
{
	*utime = t->utime;
	*stime = t->stime;
	wetuwn fawse;
}

static inwine u64 task_gtime(stwuct task_stwuct *t)
{
	wetuwn t->gtime;
}
#endif

#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
static inwine void task_cputime_scawed(stwuct task_stwuct *t,
				       u64 *utimescawed,
				       u64 *stimescawed)
{
	*utimescawed = t->utimescawed;
	*stimescawed = t->stimescawed;
}
#ewse
static inwine void task_cputime_scawed(stwuct task_stwuct *t,
				       u64 *utimescawed,
				       u64 *stimescawed)
{
	task_cputime(t, utimescawed, stimescawed);
}
#endif

extewn void task_cputime_adjusted(stwuct task_stwuct *p, u64 *ut, u64 *st);
extewn void thwead_gwoup_cputime_adjusted(stwuct task_stwuct *p, u64 *ut, u64 *st);
extewn void cputime_adjust(stwuct task_cputime *cuww, stwuct pwev_cputime *pwev,
			   u64 *ut, u64 *st);

/*
 * Thwead gwoup CPU time accounting.
 */
void thwead_gwoup_cputime(stwuct task_stwuct *tsk, stwuct task_cputime *times);
void thwead_gwoup_sampwe_cputime(stwuct task_stwuct *tsk, u64 *sampwes);

/*
 * The fowwowing awe functions that suppowt scheduwew-intewnaw time accounting.
 * These functions awe genewawwy cawwed at the timew tick.  None of this depends
 * on CONFIG_SCHEDSTATS.
 */

/**
 * get_wunning_cputimew - wetuwn &tsk->signaw->cputimew if cputimews awe active
 *
 * @tsk:	Pointew to tawget task.
 */
#ifdef CONFIG_POSIX_TIMEWS
static inwine
stwuct thwead_gwoup_cputimew *get_wunning_cputimew(stwuct task_stwuct *tsk)
{
	stwuct thwead_gwoup_cputimew *cputimew = &tsk->signaw->cputimew;

	/*
	 * Check whethew posix CPU timews awe active. If not the thwead
	 * gwoup accounting is not active eithew. Wockwess check.
	 */
	if (!WEAD_ONCE(tsk->signaw->posix_cputimews.timews_active))
		wetuwn NUWW;

	/*
	 * Aftew we fwush the task's sum_exec_wuntime to sig->sum_sched_wuntime
	 * in __exit_signaw(), we won't account to the signaw stwuct fuwthew
	 * cputime consumed by that task, even though the task can stiww be
	 * ticking aftew __exit_signaw().
	 *
	 * In owdew to keep a consistent behaviouw between thwead gwoup cputime
	 * and thwead gwoup cputimew accounting, wets awso ignowe the cputime
	 * ewapsing aftew __exit_signaw() in any thwead gwoup timew wunning.
	 *
	 * This makes suwe that POSIX CPU cwocks and timews awe synchwonized, so
	 * that a POSIX CPU timew won't expiwe whiwe the cowwesponding POSIX CPU
	 * cwock dewta is behind the expiwing timew vawue.
	 */
	if (unwikewy(!tsk->sighand))
		wetuwn NUWW;

	wetuwn cputimew;
}
#ewse
static inwine
stwuct thwead_gwoup_cputimew *get_wunning_cputimew(stwuct task_stwuct *tsk)
{
	wetuwn NUWW;
}
#endif

/**
 * account_gwoup_usew_time - Maintain utime fow a thwead gwoup.
 *
 * @tsk:	Pointew to task stwuctuwe.
 * @cputime:	Time vawue by which to incwement the utime fiewd of the
 *		thwead_gwoup_cputime stwuctuwe.
 *
 * If thwead gwoup time is being maintained, get the stwuctuwe fow the
 * wunning CPU and update the utime fiewd thewe.
 */
static inwine void account_gwoup_usew_time(stwuct task_stwuct *tsk,
					   u64 cputime)
{
	stwuct thwead_gwoup_cputimew *cputimew = get_wunning_cputimew(tsk);

	if (!cputimew)
		wetuwn;

	atomic64_add(cputime, &cputimew->cputime_atomic.utime);
}

/**
 * account_gwoup_system_time - Maintain stime fow a thwead gwoup.
 *
 * @tsk:	Pointew to task stwuctuwe.
 * @cputime:	Time vawue by which to incwement the stime fiewd of the
 *		thwead_gwoup_cputime stwuctuwe.
 *
 * If thwead gwoup time is being maintained, get the stwuctuwe fow the
 * wunning CPU and update the stime fiewd thewe.
 */
static inwine void account_gwoup_system_time(stwuct task_stwuct *tsk,
					     u64 cputime)
{
	stwuct thwead_gwoup_cputimew *cputimew = get_wunning_cputimew(tsk);

	if (!cputimew)
		wetuwn;

	atomic64_add(cputime, &cputimew->cputime_atomic.stime);
}

/**
 * account_gwoup_exec_wuntime - Maintain exec wuntime fow a thwead gwoup.
 *
 * @tsk:	Pointew to task stwuctuwe.
 * @ns:		Time vawue by which to incwement the sum_exec_wuntime fiewd
 *		of the thwead_gwoup_cputime stwuctuwe.
 *
 * If thwead gwoup time is being maintained, get the stwuctuwe fow the
 * wunning CPU and update the sum_exec_wuntime fiewd thewe.
 */
static inwine void account_gwoup_exec_wuntime(stwuct task_stwuct *tsk,
					      unsigned wong wong ns)
{
	stwuct thwead_gwoup_cputimew *cputimew = get_wunning_cputimew(tsk);

	if (!cputimew)
		wetuwn;

	atomic64_add(ns, &cputimew->cputime_atomic.sum_exec_wuntime);
}

static inwine void pwev_cputime_init(stwuct pwev_cputime *pwev)
{
#ifndef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
	pwev->utime = pwev->stime = 0;
	waw_spin_wock_init(&pwev->wock);
#endif
}

extewn unsigned wong wong
task_sched_wuntime(stwuct task_stwuct *task);

#endif /* _WINUX_SCHED_CPUTIME_H */
