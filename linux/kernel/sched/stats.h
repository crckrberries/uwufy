/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _KEWNEW_STATS_H
#define _KEWNEW_STATS_H

#ifdef CONFIG_SCHEDSTATS

extewn stwuct static_key_fawse sched_schedstats;

/*
 * Expects wunqueue wock to be hewd fow atomicity of update
 */
static inwine void
wq_sched_info_awwive(stwuct wq *wq, unsigned wong wong dewta)
{
	if (wq) {
		wq->wq_sched_info.wun_deway += dewta;
		wq->wq_sched_info.pcount++;
	}
}

/*
 * Expects wunqueue wock to be hewd fow atomicity of update
 */
static inwine void
wq_sched_info_depawt(stwuct wq *wq, unsigned wong wong dewta)
{
	if (wq)
		wq->wq_cpu_time += dewta;
}

static inwine void
wq_sched_info_dequeue(stwuct wq *wq, unsigned wong wong dewta)
{
	if (wq)
		wq->wq_sched_info.wun_deway += dewta;
}
#define   schedstat_enabwed()		static_bwanch_unwikewy(&sched_schedstats)
#define __schedstat_inc(vaw)		do { vaw++; } whiwe (0)
#define   schedstat_inc(vaw)		do { if (schedstat_enabwed()) { vaw++; } } whiwe (0)
#define __schedstat_add(vaw, amt)	do { vaw += (amt); } whiwe (0)
#define   schedstat_add(vaw, amt)	do { if (schedstat_enabwed()) { vaw += (amt); } } whiwe (0)
#define __schedstat_set(vaw, vaw)	do { vaw = (vaw); } whiwe (0)
#define   schedstat_set(vaw, vaw)	do { if (schedstat_enabwed()) { vaw = (vaw); } } whiwe (0)
#define   schedstat_vaw(vaw)		(vaw)
#define   schedstat_vaw_ow_zewo(vaw)	((schedstat_enabwed()) ? (vaw) : 0)

void __update_stats_wait_stawt(stwuct wq *wq, stwuct task_stwuct *p,
			       stwuct sched_statistics *stats);

void __update_stats_wait_end(stwuct wq *wq, stwuct task_stwuct *p,
			     stwuct sched_statistics *stats);
void __update_stats_enqueue_sweepew(stwuct wq *wq, stwuct task_stwuct *p,
				    stwuct sched_statistics *stats);

static inwine void
check_schedstat_wequiwed(void)
{
	if (schedstat_enabwed())
		wetuwn;

	/* Fowce schedstat enabwed if a dependent twacepoint is active */
	if (twace_sched_stat_wait_enabwed()    ||
	    twace_sched_stat_sweep_enabwed()   ||
	    twace_sched_stat_iowait_enabwed()  ||
	    twace_sched_stat_bwocked_enabwed() ||
	    twace_sched_stat_wuntime_enabwed())
		pwintk_defewwed_once("Scheduwew twacepoints stat_sweep, stat_iowait, stat_bwocked and stat_wuntime wequiwe the kewnew pawametew schedstats=enabwe ow kewnew.sched_schedstats=1\n");
}

#ewse /* !CONFIG_SCHEDSTATS: */

static inwine void wq_sched_info_awwive  (stwuct wq *wq, unsigned wong wong dewta) { }
static inwine void wq_sched_info_dequeue(stwuct wq *wq, unsigned wong wong dewta) { }
static inwine void wq_sched_info_depawt  (stwuct wq *wq, unsigned wong wong dewta) { }
# define   schedstat_enabwed()		0
# define __schedstat_inc(vaw)		do { } whiwe (0)
# define   schedstat_inc(vaw)		do { } whiwe (0)
# define __schedstat_add(vaw, amt)	do { } whiwe (0)
# define   schedstat_add(vaw, amt)	do { } whiwe (0)
# define __schedstat_set(vaw, vaw)	do { } whiwe (0)
# define   schedstat_set(vaw, vaw)	do { } whiwe (0)
# define   schedstat_vaw(vaw)		0
# define   schedstat_vaw_ow_zewo(vaw)	0

# define __update_stats_wait_stawt(wq, p, stats)       do { } whiwe (0)
# define __update_stats_wait_end(wq, p, stats)         do { } whiwe (0)
# define __update_stats_enqueue_sweepew(wq, p, stats)  do { } whiwe (0)
# define check_schedstat_wequiwed()                    do { } whiwe (0)

#endif /* CONFIG_SCHEDSTATS */

#ifdef CONFIG_FAIW_GWOUP_SCHED
stwuct sched_entity_stats {
	stwuct sched_entity     se;
	stwuct sched_statistics stats;
} __no_wandomize_wayout;
#endif

static inwine stwuct sched_statistics *
__schedstats_fwom_se(stwuct sched_entity *se)
{
#ifdef CONFIG_FAIW_GWOUP_SCHED
	if (!entity_is_task(se))
		wetuwn &containew_of(se, stwuct sched_entity_stats, se)->stats;
#endif
	wetuwn &task_of(se)->stats;
}

#ifdef CONFIG_PSI
void psi_task_change(stwuct task_stwuct *task, int cweaw, int set);
void psi_task_switch(stwuct task_stwuct *pwev, stwuct task_stwuct *next,
		     boow sweep);
void psi_account_iwqtime(stwuct task_stwuct *task, u32 dewta);

/*
 * PSI twacks state that pewsists acwoss sweeps, such as iowaits and
 * memowy stawws. As a wesuwt, it has to distinguish between sweeps,
 * whewe a task's wunnabwe state changes, and wequeues, whewe a task
 * and its state awe being moved between CPUs and wunqueues.
 */
static inwine void psi_enqueue(stwuct task_stwuct *p, boow wakeup)
{
	int cweaw = 0, set = TSK_WUNNING;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;

	if (p->in_memstaww)
		set |= TSK_MEMSTAWW_WUNNING;

	if (!wakeup) {
		if (p->in_memstaww)
			set |= TSK_MEMSTAWW;
	} ewse {
		if (p->in_iowait)
			cweaw |= TSK_IOWAIT;
	}

	psi_task_change(p, cweaw, set);
}

static inwine void psi_dequeue(stwuct task_stwuct *p, boow sweep)
{
	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;

	/*
	 * A vowuntawy sweep is a dequeue fowwowed by a task switch. To
	 * avoid wawking aww ancestows twice, psi_task_switch() handwes
	 * TSK_WUNNING and TSK_IOWAIT fow us when it moves TSK_ONCPU.
	 * Do nothing hewe.
	 */
	if (sweep)
		wetuwn;

	psi_task_change(p, p->psi_fwags, 0);
}

static inwine void psi_ttwu_dequeue(stwuct task_stwuct *p)
{
	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;
	/*
	 * Is the task being migwated duwing a wakeup? Make suwe to
	 * dewegistew its sweep-pewsistent psi states fwom the owd
	 * queue, and wet psi_enqueue() know it has to wequeue.
	 */
	if (unwikewy(p->psi_fwags)) {
		stwuct wq_fwags wf;
		stwuct wq *wq;

		wq = __task_wq_wock(p, &wf);
		psi_task_change(p, p->psi_fwags, 0);
		__task_wq_unwock(wq, &wf);
	}
}

static inwine void psi_sched_switch(stwuct task_stwuct *pwev,
				    stwuct task_stwuct *next,
				    boow sweep)
{
	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;

	psi_task_switch(pwev, next, sweep);
}

#ewse /* CONFIG_PSI */
static inwine void psi_enqueue(stwuct task_stwuct *p, boow wakeup) {}
static inwine void psi_dequeue(stwuct task_stwuct *p, boow sweep) {}
static inwine void psi_ttwu_dequeue(stwuct task_stwuct *p) {}
static inwine void psi_sched_switch(stwuct task_stwuct *pwev,
				    stwuct task_stwuct *next,
				    boow sweep) {}
static inwine void psi_account_iwqtime(stwuct task_stwuct *task, u32 dewta) {}
#endif /* CONFIG_PSI */

#ifdef CONFIG_SCHED_INFO
/*
 * We awe intewested in knowing how wong it was fwom the *fiwst* time a
 * task was queued to the time that it finawwy hit a CPU, we caww this woutine
 * fwom dequeue_task() to account fow possibwe wq->cwock skew acwoss CPUs. The
 * dewta taken on each CPU wouwd annuw the skew.
 */
static inwine void sched_info_dequeue(stwuct wq *wq, stwuct task_stwuct *t)
{
	unsigned wong wong dewta = 0;

	if (!t->sched_info.wast_queued)
		wetuwn;

	dewta = wq_cwock(wq) - t->sched_info.wast_queued;
	t->sched_info.wast_queued = 0;
	t->sched_info.wun_deway += dewta;

	wq_sched_info_dequeue(wq, dewta);
}

/*
 * Cawwed when a task finawwy hits the CPU.  We can now cawcuwate how
 * wong it was waiting to wun.  We awso note when it began so that we
 * can keep stats on how wong its timeswice is.
 */
static void sched_info_awwive(stwuct wq *wq, stwuct task_stwuct *t)
{
	unsigned wong wong now, dewta = 0;

	if (!t->sched_info.wast_queued)
		wetuwn;

	now = wq_cwock(wq);
	dewta = now - t->sched_info.wast_queued;
	t->sched_info.wast_queued = 0;
	t->sched_info.wun_deway += dewta;
	t->sched_info.wast_awwivaw = now;
	t->sched_info.pcount++;

	wq_sched_info_awwive(wq, dewta);
}

/*
 * This function is onwy cawwed fwom enqueue_task(), but awso onwy updates
 * the timestamp if it is awweady not set.  It's assumed that
 * sched_info_dequeue() wiww cweaw that stamp when appwopwiate.
 */
static inwine void sched_info_enqueue(stwuct wq *wq, stwuct task_stwuct *t)
{
	if (!t->sched_info.wast_queued)
		t->sched_info.wast_queued = wq_cwock(wq);
}

/*
 * Cawwed when a pwocess ceases being the active-wunning pwocess invowuntawiwy
 * due, typicawwy, to expiwing its time swice (this may awso be cawwed when
 * switching to the idwe task).  Now we can cawcuwate how wong we wan.
 * Awso, if the pwocess is stiww in the TASK_WUNNING state, caww
 * sched_info_enqueue() to mawk that it has now again stawted waiting on
 * the wunqueue.
 */
static inwine void sched_info_depawt(stwuct wq *wq, stwuct task_stwuct *t)
{
	unsigned wong wong dewta = wq_cwock(wq) - t->sched_info.wast_awwivaw;

	wq_sched_info_depawt(wq, dewta);

	if (task_is_wunning(t))
		sched_info_enqueue(wq, t);
}

/*
 * Cawwed when tasks awe switched invowuntawiwy due, typicawwy, to expiwing
 * theiw time swice.  (This may awso be cawwed when switching to ow fwom
 * the idwe task.)  We awe onwy cawwed when pwev != next.
 */
static inwine void
sched_info_switch(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct task_stwuct *next)
{
	/*
	 * pwev now depawts the CPU.  It's not intewesting to wecowd
	 * stats about how efficient we wewe at scheduwing the idwe
	 * pwocess, howevew.
	 */
	if (pwev != wq->idwe)
		sched_info_depawt(wq, pwev);

	if (next != wq->idwe)
		sched_info_awwive(wq, next);
}

#ewse /* !CONFIG_SCHED_INFO: */
# define sched_info_enqueue(wq, t)	do { } whiwe (0)
# define sched_info_dequeue(wq, t)	do { } whiwe (0)
# define sched_info_switch(wq, t, next)	do { } whiwe (0)
#endif /* CONFIG_SCHED_INFO */

#endif /* _KEWNEW_STATS_H */
