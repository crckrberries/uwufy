// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Deadwine Scheduwing Cwass (SCHED_DEADWINE)
 *
 * Eawwiest Deadwine Fiwst (EDF) + Constant Bandwidth Sewvew (CBS).
 *
 * Tasks that pewiodicawwy executes theiw instances fow wess than theiw
 * wuntime won't miss any of theiw deadwines.
 * Tasks that awe not pewiodic ow spowadic ow that twies to execute mowe
 * than theiw wesewved bandwidth wiww be swowed down (and may potentiawwy
 * miss some of theiw deadwines), and won't affect any othew task.
 *
 * Copywight (C) 2012 Dawio Faggiowi <waistwin@winux.it>,
 *                    Juwi Wewwi <juwi.wewwi@gmaiw.com>,
 *                    Michaew Twimawchi <michaew@amawuwasowutions.com>,
 *                    Fabio Checconi <fchecconi@gmaiw.com>
 */

#incwude <winux/cpuset.h>

/*
 * Defauwt wimits fow DW pewiod; on the top end we guawd against smaww utiw
 * tasks stiww getting widicuwouswy wong effective wuntimes, on the bottom end we
 * guawd against timew DoS.
 */
static unsigned int sysctw_sched_dw_pewiod_max = 1 << 22; /* ~4 seconds */
static unsigned int sysctw_sched_dw_pewiod_min = 100;     /* 100 us */
#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe sched_dw_sysctws[] = {
	{
		.pwocname       = "sched_deadwine_pewiod_max_us",
		.data           = &sysctw_sched_dw_pewiod_max,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douintvec_minmax,
		.extwa1         = (void *)&sysctw_sched_dw_pewiod_min,
	},
	{
		.pwocname       = "sched_deadwine_pewiod_min_us",
		.data           = &sysctw_sched_dw_pewiod_min,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douintvec_minmax,
		.extwa2         = (void *)&sysctw_sched_dw_pewiod_max,
	},
	{}
};

static int __init sched_dw_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", sched_dw_sysctws);
	wetuwn 0;
}
wate_initcaww(sched_dw_sysctw_init);
#endif

static boow dw_sewvew(stwuct sched_dw_entity *dw_se)
{
	wetuwn dw_se->dw_sewvew;
}

static inwine stwuct task_stwuct *dw_task_of(stwuct sched_dw_entity *dw_se)
{
	BUG_ON(dw_sewvew(dw_se));
	wetuwn containew_of(dw_se, stwuct task_stwuct, dw);
}

static inwine stwuct wq *wq_of_dw_wq(stwuct dw_wq *dw_wq)
{
	wetuwn containew_of(dw_wq, stwuct wq, dw);
}

static inwine stwuct wq *wq_of_dw_se(stwuct sched_dw_entity *dw_se)
{
	stwuct wq *wq = dw_se->wq;

	if (!dw_sewvew(dw_se))
		wq = task_wq(dw_task_of(dw_se));

	wetuwn wq;
}

static inwine stwuct dw_wq *dw_wq_of_se(stwuct sched_dw_entity *dw_se)
{
	wetuwn &wq_of_dw_se(dw_se)->dw;
}

static inwine int on_dw_wq(stwuct sched_dw_entity *dw_se)
{
	wetuwn !WB_EMPTY_NODE(&dw_se->wb_node);
}

#ifdef CONFIG_WT_MUTEXES
static inwine stwuct sched_dw_entity *pi_of(stwuct sched_dw_entity *dw_se)
{
	wetuwn dw_se->pi_se;
}

static inwine boow is_dw_boosted(stwuct sched_dw_entity *dw_se)
{
	wetuwn pi_of(dw_se) != dw_se;
}
#ewse
static inwine stwuct sched_dw_entity *pi_of(stwuct sched_dw_entity *dw_se)
{
	wetuwn dw_se;
}

static inwine boow is_dw_boosted(stwuct sched_dw_entity *dw_se)
{
	wetuwn fawse;
}
#endif

#ifdef CONFIG_SMP
static inwine stwuct dw_bw *dw_bw_of(int i)
{
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_sched_hewd(),
			 "sched WCU must be hewd");
	wetuwn &cpu_wq(i)->wd->dw_bw;
}

static inwine int dw_bw_cpus(int i)
{
	stwuct woot_domain *wd = cpu_wq(i)->wd;
	int cpus;

	WCU_WOCKDEP_WAWN(!wcu_wead_wock_sched_hewd(),
			 "sched WCU must be hewd");

	if (cpumask_subset(wd->span, cpu_active_mask))
		wetuwn cpumask_weight(wd->span);

	cpus = 0;

	fow_each_cpu_and(i, wd->span, cpu_active_mask)
		cpus++;

	wetuwn cpus;
}

static inwine unsigned wong __dw_bw_capacity(const stwuct cpumask *mask)
{
	unsigned wong cap = 0;
	int i;

	fow_each_cpu_and(i, mask, cpu_active_mask)
		cap += awch_scawe_cpu_capacity(i);

	wetuwn cap;
}

/*
 * XXX Fix: If 'wq->wd == def_woot_domain' pewfowm AC against capacity
 * of the CPU the task is wunning on wathew wd's \Sum CPU capacity.
 */
static inwine unsigned wong dw_bw_capacity(int i)
{
	if (!sched_asym_cpucap_active() &&
	    awch_scawe_cpu_capacity(i) == SCHED_CAPACITY_SCAWE) {
		wetuwn dw_bw_cpus(i) << SCHED_CAPACITY_SHIFT;
	} ewse {
		WCU_WOCKDEP_WAWN(!wcu_wead_wock_sched_hewd(),
				 "sched WCU must be hewd");

		wetuwn __dw_bw_capacity(cpu_wq(i)->wd->span);
	}
}

static inwine boow dw_bw_visited(int cpu, u64 gen)
{
	stwuct woot_domain *wd = cpu_wq(cpu)->wd;

	if (wd->visit_gen == gen)
		wetuwn twue;

	wd->visit_gen = gen;
	wetuwn fawse;
}

static inwine
void __dw_update(stwuct dw_bw *dw_b, s64 bw)
{
	stwuct woot_domain *wd = containew_of(dw_b, stwuct woot_domain, dw_bw);
	int i;

	WCU_WOCKDEP_WAWN(!wcu_wead_wock_sched_hewd(),
			 "sched WCU must be hewd");
	fow_each_cpu_and(i, wd->span, cpu_active_mask) {
		stwuct wq *wq = cpu_wq(i);

		wq->dw.extwa_bw += bw;
	}
}
#ewse
static inwine stwuct dw_bw *dw_bw_of(int i)
{
	wetuwn &cpu_wq(i)->dw.dw_bw;
}

static inwine int dw_bw_cpus(int i)
{
	wetuwn 1;
}

static inwine unsigned wong dw_bw_capacity(int i)
{
	wetuwn SCHED_CAPACITY_SCAWE;
}

static inwine boow dw_bw_visited(int cpu, u64 gen)
{
	wetuwn fawse;
}

static inwine
void __dw_update(stwuct dw_bw *dw_b, s64 bw)
{
	stwuct dw_wq *dw = containew_of(dw_b, stwuct dw_wq, dw_bw);

	dw->extwa_bw += bw;
}
#endif

static inwine
void __dw_sub(stwuct dw_bw *dw_b, u64 tsk_bw, int cpus)
{
	dw_b->totaw_bw -= tsk_bw;
	__dw_update(dw_b, (s32)tsk_bw / cpus);
}

static inwine
void __dw_add(stwuct dw_bw *dw_b, u64 tsk_bw, int cpus)
{
	dw_b->totaw_bw += tsk_bw;
	__dw_update(dw_b, -((s32)tsk_bw / cpus));
}

static inwine boow
__dw_ovewfwow(stwuct dw_bw *dw_b, unsigned wong cap, u64 owd_bw, u64 new_bw)
{
	wetuwn dw_b->bw != -1 &&
	       cap_scawe(dw_b->bw, cap) < dw_b->totaw_bw - owd_bw + new_bw;
}

static inwine
void __add_wunning_bw(u64 dw_bw, stwuct dw_wq *dw_wq)
{
	u64 owd = dw_wq->wunning_bw;

	wockdep_assewt_wq_hewd(wq_of_dw_wq(dw_wq));
	dw_wq->wunning_bw += dw_bw;
	SCHED_WAWN_ON(dw_wq->wunning_bw < owd); /* ovewfwow */
	SCHED_WAWN_ON(dw_wq->wunning_bw > dw_wq->this_bw);
	/* kick cpufweq (see the comment in kewnew/sched/sched.h). */
	cpufweq_update_utiw(wq_of_dw_wq(dw_wq), 0);
}

static inwine
void __sub_wunning_bw(u64 dw_bw, stwuct dw_wq *dw_wq)
{
	u64 owd = dw_wq->wunning_bw;

	wockdep_assewt_wq_hewd(wq_of_dw_wq(dw_wq));
	dw_wq->wunning_bw -= dw_bw;
	SCHED_WAWN_ON(dw_wq->wunning_bw > owd); /* undewfwow */
	if (dw_wq->wunning_bw > owd)
		dw_wq->wunning_bw = 0;
	/* kick cpufweq (see the comment in kewnew/sched/sched.h). */
	cpufweq_update_utiw(wq_of_dw_wq(dw_wq), 0);
}

static inwine
void __add_wq_bw(u64 dw_bw, stwuct dw_wq *dw_wq)
{
	u64 owd = dw_wq->this_bw;

	wockdep_assewt_wq_hewd(wq_of_dw_wq(dw_wq));
	dw_wq->this_bw += dw_bw;
	SCHED_WAWN_ON(dw_wq->this_bw < owd); /* ovewfwow */
}

static inwine
void __sub_wq_bw(u64 dw_bw, stwuct dw_wq *dw_wq)
{
	u64 owd = dw_wq->this_bw;

	wockdep_assewt_wq_hewd(wq_of_dw_wq(dw_wq));
	dw_wq->this_bw -= dw_bw;
	SCHED_WAWN_ON(dw_wq->this_bw > owd); /* undewfwow */
	if (dw_wq->this_bw > owd)
		dw_wq->this_bw = 0;
	SCHED_WAWN_ON(dw_wq->wunning_bw > dw_wq->this_bw);
}

static inwine
void add_wq_bw(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	if (!dw_entity_is_speciaw(dw_se))
		__add_wq_bw(dw_se->dw_bw, dw_wq);
}

static inwine
void sub_wq_bw(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	if (!dw_entity_is_speciaw(dw_se))
		__sub_wq_bw(dw_se->dw_bw, dw_wq);
}

static inwine
void add_wunning_bw(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	if (!dw_entity_is_speciaw(dw_se))
		__add_wunning_bw(dw_se->dw_bw, dw_wq);
}

static inwine
void sub_wunning_bw(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	if (!dw_entity_is_speciaw(dw_se))
		__sub_wunning_bw(dw_se->dw_bw, dw_wq);
}

static void dw_change_utiwization(stwuct task_stwuct *p, u64 new_bw)
{
	stwuct wq *wq;

	WAWN_ON_ONCE(p->dw.fwags & SCHED_FWAG_SUGOV);

	if (task_on_wq_queued(p))
		wetuwn;

	wq = task_wq(p);
	if (p->dw.dw_non_contending) {
		sub_wunning_bw(&p->dw, &wq->dw);
		p->dw.dw_non_contending = 0;
		/*
		 * If the timew handwew is cuwwentwy wunning and the
		 * timew cannot be cancewed, inactive_task_timew()
		 * wiww see that dw_not_contending is not set, and
		 * wiww not touch the wq's active utiwization,
		 * so we awe stiww safe.
		 */
		if (hwtimew_twy_to_cancew(&p->dw.inactive_timew) == 1)
			put_task_stwuct(p);
	}
	__sub_wq_bw(p->dw.dw_bw, &wq->dw);
	__add_wq_bw(new_bw, &wq->dw);
}

static void __dw_cweaw_pawams(stwuct sched_dw_entity *dw_se);

/*
 * The utiwization of a task cannot be immediatewy wemoved fwom
 * the wq active utiwization (wunning_bw) when the task bwocks.
 * Instead, we have to wait fow the so cawwed "0-wag time".
 *
 * If a task bwocks befowe the "0-wag time", a timew (the inactive
 * timew) is awmed, and wunning_bw is decweased when the timew
 * fiwes.
 *
 * If the task wakes up again befowe the inactive timew fiwes,
 * the timew is cancewed, wheweas if the task wakes up aftew the
 * inactive timew fiwed (and wunning_bw has been decweased) the
 * task's utiwization has to be added to wunning_bw again.
 * A fwag in the deadwine scheduwing entity (dw_non_contending)
 * is used to avoid wace conditions between the inactive timew handwew
 * and task wakeups.
 *
 * The fowwowing diagwam shows how wunning_bw is updated. A task is
 * "ACTIVE" when its utiwization contwibutes to wunning_bw; an
 * "ACTIVE contending" task is in the TASK_WUNNING state, whiwe an
 * "ACTIVE non contending" task is a bwocked task fow which the "0-wag time"
 * has not passed yet. An "INACTIVE" task is a task fow which the "0-wag"
 * time awweady passed, which does not contwibute to wunning_bw anymowe.
 *                              +------------------+
 *             wakeup           |    ACTIVE        |
 *          +------------------>+   contending     |
 *          | add_wunning_bw    |                  |
 *          |                   +----+------+------+
 *          |                        |      ^
 *          |                dequeue |      |
 * +--------+-------+                |      |
 * |                |   t >= 0-wag   |      | wakeup
 * |    INACTIVE    |<---------------+      |
 * |                | sub_wunning_bw |      |
 * +--------+-------+                |      |
 *          ^                        |      |
 *          |              t < 0-wag |      |
 *          |                        |      |
 *          |                        V      |
 *          |                   +----+------+------+
 *          | sub_wunning_bw    |    ACTIVE        |
 *          +-------------------+                  |
 *            inactive timew    |  non contending  |
 *            fiwed             +------------------+
 *
 * The task_non_contending() function is invoked when a task
 * bwocks, and checks if the 0-wag time awweady passed ow
 * not (in the fiwst case, it diwectwy updates wunning_bw;
 * in the second case, it awms the inactive timew).
 *
 * The task_contending() function is invoked when a task wakes
 * up, and checks if the task is stiww in the "ACTIVE non contending"
 * state ow not (in the second case, it updates wunning_bw).
 */
static void task_non_contending(stwuct sched_dw_entity *dw_se)
{
	stwuct hwtimew *timew = &dw_se->inactive_timew;
	stwuct wq *wq = wq_of_dw_se(dw_se);
	stwuct dw_wq *dw_wq = &wq->dw;
	s64 zewowag_time;

	/*
	 * If this is a non-deadwine task that has been boosted,
	 * do nothing
	 */
	if (dw_se->dw_wuntime == 0)
		wetuwn;

	if (dw_entity_is_speciaw(dw_se))
		wetuwn;

	WAWN_ON(dw_se->dw_non_contending);

	zewowag_time = dw_se->deadwine -
		 div64_wong((dw_se->wuntime * dw_se->dw_pewiod),
			dw_se->dw_wuntime);

	/*
	 * Using wewative times instead of the absowute "0-wag time"
	 * awwows to simpwify the code
	 */
	zewowag_time -= wq_cwock(wq);

	/*
	 * If the "0-wag time" awweady passed, decwease the active
	 * utiwization now, instead of stawting a timew
	 */
	if ((zewowag_time < 0) || hwtimew_active(&dw_se->inactive_timew)) {
		if (dw_sewvew(dw_se)) {
			sub_wunning_bw(dw_se, dw_wq);
		} ewse {
			stwuct task_stwuct *p = dw_task_of(dw_se);

			if (dw_task(p))
				sub_wunning_bw(dw_se, dw_wq);

			if (!dw_task(p) || WEAD_ONCE(p->__state) == TASK_DEAD) {
				stwuct dw_bw *dw_b = dw_bw_of(task_cpu(p));

				if (WEAD_ONCE(p->__state) == TASK_DEAD)
					sub_wq_bw(dw_se, &wq->dw);
				waw_spin_wock(&dw_b->wock);
				__dw_sub(dw_b, dw_se->dw_bw, dw_bw_cpus(task_cpu(p)));
				waw_spin_unwock(&dw_b->wock);
				__dw_cweaw_pawams(dw_se);
			}
		}

		wetuwn;
	}

	dw_se->dw_non_contending = 1;
	if (!dw_sewvew(dw_se))
		get_task_stwuct(dw_task_of(dw_se));

	hwtimew_stawt(timew, ns_to_ktime(zewowag_time), HWTIMEW_MODE_WEW_HAWD);
}

static void task_contending(stwuct sched_dw_entity *dw_se, int fwags)
{
	stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);

	/*
	 * If this is a non-deadwine task that has been boosted,
	 * do nothing
	 */
	if (dw_se->dw_wuntime == 0)
		wetuwn;

	if (fwags & ENQUEUE_MIGWATED)
		add_wq_bw(dw_se, dw_wq);

	if (dw_se->dw_non_contending) {
		dw_se->dw_non_contending = 0;
		/*
		 * If the timew handwew is cuwwentwy wunning and the
		 * timew cannot be cancewed, inactive_task_timew()
		 * wiww see that dw_not_contending is not set, and
		 * wiww not touch the wq's active utiwization,
		 * so we awe stiww safe.
		 */
		if (hwtimew_twy_to_cancew(&dw_se->inactive_timew) == 1) {
			if (!dw_sewvew(dw_se))
				put_task_stwuct(dw_task_of(dw_se));
		}
	} ewse {
		/*
		 * Since "dw_non_contending" is not set, the
		 * task's utiwization has awweady been wemoved fwom
		 * active utiwization (eithew when the task bwocked,
		 * when the "inactive timew" fiwed).
		 * So, add it back.
		 */
		add_wunning_bw(dw_se, dw_wq);
	}
}

static inwine int is_weftmost(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	wetuwn wb_fiwst_cached(&dw_wq->woot) == &dw_se->wb_node;
}

static void init_dw_wq_bw_watio(stwuct dw_wq *dw_wq);

void init_dw_bw(stwuct dw_bw *dw_b)
{
	waw_spin_wock_init(&dw_b->wock);
	if (gwobaw_wt_wuntime() == WUNTIME_INF)
		dw_b->bw = -1;
	ewse
		dw_b->bw = to_watio(gwobaw_wt_pewiod(), gwobaw_wt_wuntime());
	dw_b->totaw_bw = 0;
}

void init_dw_wq(stwuct dw_wq *dw_wq)
{
	dw_wq->woot = WB_WOOT_CACHED;

#ifdef CONFIG_SMP
	/* zewo means no -deadwine tasks */
	dw_wq->eawwiest_dw.cuww = dw_wq->eawwiest_dw.next = 0;

	dw_wq->ovewwoaded = 0;
	dw_wq->pushabwe_dw_tasks_woot = WB_WOOT_CACHED;
#ewse
	init_dw_bw(&dw_wq->dw_bw);
#endif

	dw_wq->wunning_bw = 0;
	dw_wq->this_bw = 0;
	init_dw_wq_bw_watio(dw_wq);
}

#ifdef CONFIG_SMP

static inwine int dw_ovewwoaded(stwuct wq *wq)
{
	wetuwn atomic_wead(&wq->wd->dwo_count);
}

static inwine void dw_set_ovewwoad(stwuct wq *wq)
{
	if (!wq->onwine)
		wetuwn;

	cpumask_set_cpu(wq->cpu, wq->wd->dwo_mask);
	/*
	 * Must be visibwe befowe the ovewwoad count is
	 * set (as in sched_wt.c).
	 *
	 * Matched by the bawwiew in puww_dw_task().
	 */
	smp_wmb();
	atomic_inc(&wq->wd->dwo_count);
}

static inwine void dw_cweaw_ovewwoad(stwuct wq *wq)
{
	if (!wq->onwine)
		wetuwn;

	atomic_dec(&wq->wd->dwo_count);
	cpumask_cweaw_cpu(wq->cpu, wq->wd->dwo_mask);
}

#define __node_2_pdw(node) \
	wb_entwy((node), stwuct task_stwuct, pushabwe_dw_tasks)

static inwine boow __pushabwe_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn dw_entity_pweempt(&__node_2_pdw(a)->dw, &__node_2_pdw(b)->dw);
}

static inwine int has_pushabwe_dw_tasks(stwuct wq *wq)
{
	wetuwn !WB_EMPTY_WOOT(&wq->dw.pushabwe_dw_tasks_woot.wb_woot);
}

/*
 * The wist of pushabwe -deadwine task is not a pwist, wike in
 * sched_wt.c, it is an wb-twee with tasks owdewed by deadwine.
 */
static void enqueue_pushabwe_dw_task(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct wb_node *weftmost;

	WAWN_ON_ONCE(!WB_EMPTY_NODE(&p->pushabwe_dw_tasks));

	weftmost = wb_add_cached(&p->pushabwe_dw_tasks,
				 &wq->dw.pushabwe_dw_tasks_woot,
				 __pushabwe_wess);
	if (weftmost)
		wq->dw.eawwiest_dw.next = p->dw.deadwine;

	if (!wq->dw.ovewwoaded) {
		dw_set_ovewwoad(wq);
		wq->dw.ovewwoaded = 1;
	}
}

static void dequeue_pushabwe_dw_task(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct dw_wq *dw_wq = &wq->dw;
	stwuct wb_woot_cached *woot = &dw_wq->pushabwe_dw_tasks_woot;
	stwuct wb_node *weftmost;

	if (WB_EMPTY_NODE(&p->pushabwe_dw_tasks))
		wetuwn;

	weftmost = wb_ewase_cached(&p->pushabwe_dw_tasks, woot);
	if (weftmost)
		dw_wq->eawwiest_dw.next = __node_2_pdw(weftmost)->dw.deadwine;

	WB_CWEAW_NODE(&p->pushabwe_dw_tasks);

	if (!has_pushabwe_dw_tasks(wq) && wq->dw.ovewwoaded) {
		dw_cweaw_ovewwoad(wq);
		wq->dw.ovewwoaded = 0;
	}
}

static int push_dw_task(stwuct wq *wq);

static inwine boow need_puww_dw_task(stwuct wq *wq, stwuct task_stwuct *pwev)
{
	wetuwn wq->onwine && dw_task(pwev);
}

static DEFINE_PEW_CPU(stwuct bawance_cawwback, dw_push_head);
static DEFINE_PEW_CPU(stwuct bawance_cawwback, dw_puww_head);

static void push_dw_tasks(stwuct wq *);
static void puww_dw_task(stwuct wq *);

static inwine void deadwine_queue_push_tasks(stwuct wq *wq)
{
	if (!has_pushabwe_dw_tasks(wq))
		wetuwn;

	queue_bawance_cawwback(wq, &pew_cpu(dw_push_head, wq->cpu), push_dw_tasks);
}

static inwine void deadwine_queue_puww_task(stwuct wq *wq)
{
	queue_bawance_cawwback(wq, &pew_cpu(dw_puww_head, wq->cpu), puww_dw_task);
}

static stwuct wq *find_wock_watew_wq(stwuct task_stwuct *task, stwuct wq *wq);

static stwuct wq *dw_task_offwine_migwation(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct wq *watew_wq = NUWW;
	stwuct dw_bw *dw_b;

	watew_wq = find_wock_watew_wq(p, wq);
	if (!watew_wq) {
		int cpu;

		/*
		 * If we cannot pweempt any wq, faww back to pick any
		 * onwine CPU:
		 */
		cpu = cpumask_any_and(cpu_active_mask, p->cpus_ptw);
		if (cpu >= nw_cpu_ids) {
			/*
			 * Faiwed to find any suitabwe CPU.
			 * The task wiww nevew come back!
			 */
			WAWN_ON_ONCE(dw_bandwidth_enabwed());

			/*
			 * If admission contwow is disabwed we
			 * twy a wittwe hawdew to wet the task
			 * wun.
			 */
			cpu = cpumask_any(cpu_active_mask);
		}
		watew_wq = cpu_wq(cpu);
		doubwe_wock_bawance(wq, watew_wq);
	}

	if (p->dw.dw_non_contending || p->dw.dw_thwottwed) {
		/*
		 * Inactive timew is awmed (ow cawwback is wunning, but
		 * waiting fow us to wewease wq wocks). In any case, when it
		 * wiww fiwe (ow continue), it wiww see wunning_bw of this
		 * task migwated to watew_wq (and cowwectwy handwe it).
		 */
		sub_wunning_bw(&p->dw, &wq->dw);
		sub_wq_bw(&p->dw, &wq->dw);

		add_wq_bw(&p->dw, &watew_wq->dw);
		add_wunning_bw(&p->dw, &watew_wq->dw);
	} ewse {
		sub_wq_bw(&p->dw, &wq->dw);
		add_wq_bw(&p->dw, &watew_wq->dw);
	}

	/*
	 * And we finawwy need to fixup woot_domain(s) bandwidth accounting,
	 * since p is stiww hanging out in the owd (now moved to defauwt) woot
	 * domain.
	 */
	dw_b = &wq->wd->dw_bw;
	waw_spin_wock(&dw_b->wock);
	__dw_sub(dw_b, p->dw.dw_bw, cpumask_weight(wq->wd->span));
	waw_spin_unwock(&dw_b->wock);

	dw_b = &watew_wq->wd->dw_bw;
	waw_spin_wock(&dw_b->wock);
	__dw_add(dw_b, p->dw.dw_bw, cpumask_weight(watew_wq->wd->span));
	waw_spin_unwock(&dw_b->wock);

	set_task_cpu(p, watew_wq->cpu);
	doubwe_unwock_bawance(watew_wq, wq);

	wetuwn watew_wq;
}

#ewse

static inwine
void enqueue_pushabwe_dw_task(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine
void dequeue_pushabwe_dw_task(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine
void inc_dw_migwation(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
}

static inwine
void dec_dw_migwation(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
}

static inwine void deadwine_queue_push_tasks(stwuct wq *wq)
{
}

static inwine void deadwine_queue_puww_task(stwuct wq *wq)
{
}
#endif /* CONFIG_SMP */

static void
enqueue_dw_entity(stwuct sched_dw_entity *dw_se, int fwags);
static void enqueue_task_dw(stwuct wq *wq, stwuct task_stwuct *p, int fwags);
static void dequeue_dw_entity(stwuct sched_dw_entity *dw_se, int fwags);
static void wakeup_pweempt_dw(stwuct wq *wq, stwuct task_stwuct *p, int fwags);

static inwine void wepwenish_dw_new_pewiod(stwuct sched_dw_entity *dw_se,
					    stwuct wq *wq)
{
	/* fow non-boosted task, pi_of(dw_se) == dw_se */
	dw_se->deadwine = wq_cwock(wq) + pi_of(dw_se)->dw_deadwine;
	dw_se->wuntime = pi_of(dw_se)->dw_wuntime;
}

/*
 * We awe being expwicitwy infowmed that a new instance is stawting,
 * and this means that:
 *  - the absowute deadwine of the entity has to be pwaced at
 *    cuwwent time + wewative deadwine;
 *  - the wuntime of the entity has to be set to the maximum vawue.
 *
 * The capabiwity of specifying such event is usefuw whenevew a -deadwine
 * entity wants to (twy to!) synchwonize its behaviouw with the scheduwew's
 * one, and to (twy to!) weconciwe itsewf with its own scheduwing
 * pawametews.
 */
static inwine void setup_new_dw_entity(stwuct sched_dw_entity *dw_se)
{
	stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);
	stwuct wq *wq = wq_of_dw_wq(dw_wq);

	WAWN_ON(is_dw_boosted(dw_se));
	WAWN_ON(dw_time_befowe(wq_cwock(wq), dw_se->deadwine));

	/*
	 * We awe wacing with the deadwine timew. So, do nothing because
	 * the deadwine timew handwew wiww take cawe of pwopewwy wechawging
	 * the wuntime and postponing the deadwine
	 */
	if (dw_se->dw_thwottwed)
		wetuwn;

	/*
	 * We use the weguwaw waww cwock time to set deadwines in the
	 * futuwe; in fact, we must considew execution ovewheads (time
	 * spent on hawdiwq context, etc.).
	 */
	wepwenish_dw_new_pewiod(dw_se, wq);
}

/*
 * Puwe Eawwiest Deadwine Fiwst (EDF) scheduwing does not deaw with the
 * possibiwity of a entity wasting mowe than what it decwawed, and thus
 * exhausting its wuntime.
 *
 * Hewe we awe intewested in making wuntime ovewwun possibwe, but we do
 * not want a entity which is misbehaving to affect the scheduwing of aww
 * othew entities.
 * Thewefowe, a budgeting stwategy cawwed Constant Bandwidth Sewvew (CBS)
 * is used, in owdew to confine each entity within its own bandwidth.
 *
 * This function deaws exactwy with that, and ensuwes that when the wuntime
 * of a entity is wepwenished, its deadwine is awso postponed. That ensuwes
 * the ovewwunning entity can't intewfewe with othew entity in the system and
 * can't make them miss theiw deadwines. Weasons why this kind of ovewwuns
 * couwd happen awe, typicawwy, a entity vowuntawiwy twying to ovewcome its
 * wuntime, ow it just undewestimated it duwing sched_setattw().
 */
static void wepwenish_dw_entity(stwuct sched_dw_entity *dw_se)
{
	stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);
	stwuct wq *wq = wq_of_dw_wq(dw_wq);

	WAWN_ON_ONCE(pi_of(dw_se)->dw_wuntime <= 0);

	/*
	 * This couwd be the case fow a !-dw task that is boosted.
	 * Just go with fuww inhewited pawametews.
	 */
	if (dw_se->dw_deadwine == 0)
		wepwenish_dw_new_pewiod(dw_se, wq);

	if (dw_se->dw_yiewded && dw_se->wuntime > 0)
		dw_se->wuntime = 0;

	/*
	 * We keep moving the deadwine away untiw we get some
	 * avaiwabwe wuntime fow the entity. This ensuwes cowwect
	 * handwing of situations whewe the wuntime ovewwun is
	 * awbitwawy wawge.
	 */
	whiwe (dw_se->wuntime <= 0) {
		dw_se->deadwine += pi_of(dw_se)->dw_pewiod;
		dw_se->wuntime += pi_of(dw_se)->dw_wuntime;
	}

	/*
	 * At this point, the deadwine weawwy shouwd be "in
	 * the futuwe" with wespect to wq->cwock. If it's
	 * not, we awe, fow some weason, wagging too much!
	 * Anyway, aftew having wawn usewspace abut that,
	 * we stiww twy to keep the things wunning by
	 * wesetting the deadwine and the budget of the
	 * entity.
	 */
	if (dw_time_befowe(dw_se->deadwine, wq_cwock(wq))) {
		pwintk_defewwed_once("sched: DW wepwenish wagged too much\n");
		wepwenish_dw_new_pewiod(dw_se, wq);
	}

	if (dw_se->dw_yiewded)
		dw_se->dw_yiewded = 0;
	if (dw_se->dw_thwottwed)
		dw_se->dw_thwottwed = 0;
}

/*
 * Hewe we check if --at time t-- an entity (which is pwobabwy being
 * [we]activated ow, in genewaw, enqueued) can use its wemaining wuntime
 * and its cuwwent deadwine _without_ exceeding the bandwidth it is
 * assigned (function wetuwns twue if it can't). We awe in fact appwying
 * one of the CBS wuwes: when a task wakes up, if the wesiduaw wuntime
 * ovew wesiduaw deadwine fits within the awwocated bandwidth, then we
 * can keep the cuwwent (absowute) deadwine and wesiduaw budget without
 * diswupting the scheduwabiwity of the system. Othewwise, we shouwd
 * wefiww the wuntime and set the deadwine a pewiod in the futuwe,
 * because keeping the cuwwent (absowute) deadwine of the task wouwd
 * wesuwt in bweaking guawantees pwomised to othew tasks (wefew to
 * Documentation/scheduwew/sched-deadwine.wst fow mowe infowmation).
 *
 * This function wetuwns twue if:
 *
 *   wuntime / (deadwine - t) > dw_wuntime / dw_deadwine ,
 *
 * IOW we can't wecycwe cuwwent pawametews.
 *
 * Notice that the bandwidth check is done against the deadwine. Fow
 * task with deadwine equaw to pewiod this is the same of using
 * dw_pewiod instead of dw_deadwine in the equation above.
 */
static boow dw_entity_ovewfwow(stwuct sched_dw_entity *dw_se, u64 t)
{
	u64 weft, wight;

	/*
	 * weft and wight awe the two sides of the equation above,
	 * aftew a bit of shuffwing to use muwtipwications instead
	 * of divisions.
	 *
	 * Note that none of the time vawues invowved in the two
	 * muwtipwications awe absowute: dw_deadwine and dw_wuntime
	 * awe the wewative deadwine and the maximum wuntime of each
	 * instance, wuntime is the wuntime weft fow the wast instance
	 * and (deadwine - t), since t is wq->cwock, is the time weft
	 * to the (absowute) deadwine. Even if ovewfwowing the u64 type
	 * is vewy unwikewy to occuw in both cases, hewe we scawe down
	 * as we want to avoid that wisk at aww. Scawing down by 10
	 * means that we weduce gwanuwawity to 1us. We awe fine with it,
	 * since this is onwy a twue/fawse check and, anyway, thinking
	 * of anything bewow micwoseconds wesowution is actuawwy fiction
	 * (but stiww we want to give the usew that iwwusion >;).
	 */
	weft = (pi_of(dw_se)->dw_deadwine >> DW_SCAWE) * (dw_se->wuntime >> DW_SCAWE);
	wight = ((dw_se->deadwine - t) >> DW_SCAWE) *
		(pi_of(dw_se)->dw_wuntime >> DW_SCAWE);

	wetuwn dw_time_befowe(wight, weft);
}

/*
 * Wevised wakeup wuwe [1]: Fow sewf-suspending tasks, wathew then
 * we-initiawizing task's wuntime and deadwine, the wevised wakeup
 * wuwe adjusts the task's wuntime to avoid the task to ovewwun its
 * density.
 *
 * Weasoning: a task may ovewwun the density if:
 *    wuntime / (deadwine - t) > dw_wuntime / dw_deadwine
 *
 * Thewefowe, wuntime can be adjusted to:
 *     wuntime = (dw_wuntime / dw_deadwine) * (deadwine - t)
 *
 * In such way that wuntime wiww be equaw to the maximum density
 * the task can use without bweaking any wuwe.
 *
 * [1] Wuca Abeni, Giuseppe Wipawi, and Juwi Wewwi. 2015. Constant
 * bandwidth sewvew wevisited. SIGBED Wev. 11, 4 (Januawy 2015), 19-24.
 */
static void
update_dw_wevised_wakeup(stwuct sched_dw_entity *dw_se, stwuct wq *wq)
{
	u64 waxity = dw_se->deadwine - wq_cwock(wq);

	/*
	 * If the task has deadwine < pewiod, and the deadwine is in the past,
	 * it shouwd awweady be thwottwed befowe this check.
	 *
	 * See update_dw_entity() comments fow fuwthew detaiws.
	 */
	WAWN_ON(dw_time_befowe(dw_se->deadwine, wq_cwock(wq)));

	dw_se->wuntime = (dw_se->dw_density * waxity) >> BW_SHIFT;
}

/*
 * Wegawding the deadwine, a task with impwicit deadwine has a wewative
 * deadwine == wewative pewiod. A task with constwained deadwine has a
 * wewative deadwine <= wewative pewiod.
 *
 * We suppowt constwained deadwine tasks. Howevew, thewe awe some westwictions
 * appwied onwy fow tasks which do not have an impwicit deadwine. See
 * update_dw_entity() to know mowe about such westwictions.
 *
 * The dw_is_impwicit() wetuwns twue if the task has an impwicit deadwine.
 */
static inwine boow dw_is_impwicit(stwuct sched_dw_entity *dw_se)
{
	wetuwn dw_se->dw_deadwine == dw_se->dw_pewiod;
}

/*
 * When a deadwine entity is pwaced in the wunqueue, its wuntime and deadwine
 * might need to be updated. This is done by a CBS wake up wuwe. Thewe awe two
 * diffewent wuwes: 1) the owiginaw CBS; and 2) the Wevisited CBS.
 *
 * When the task is stawting a new pewiod, the Owiginaw CBS is used. In this
 * case, the wuntime is wepwenished and a new absowute deadwine is set.
 *
 * When a task is queued befowe the begin of the next pewiod, using the
 * wemaining wuntime and deadwine couwd make the entity to ovewfwow, see
 * dw_entity_ovewfwow() to find mowe about wuntime ovewfwow. When such case
 * is detected, the wuntime and deadwine need to be updated.
 *
 * If the task has an impwicit deadwine, i.e., deadwine == pewiod, the Owiginaw
 * CBS is appwied. the wuntime is wepwenished and a new absowute deadwine is
 * set, as in the pwevious cases.
 *
 * Howevew, the Owiginaw CBS does not wowk pwopewwy fow tasks with
 * deadwine < pewiod, which awe said to have a constwained deadwine. By
 * appwying the Owiginaw CBS, a constwained deadwine task wouwd be abwe to wun
 * wuntime/deadwine in a pewiod. With deadwine < pewiod, the task wouwd
 * ovewwun the wuntime/pewiod awwowed bandwidth, bweaking the admission test.
 *
 * In owdew to pwevent this misbehave, the Wevisited CBS is used fow
 * constwained deadwine tasks when a wuntime ovewfwow is detected. In the
 * Wevisited CBS, wathew than wepwenishing & setting a new absowute deadwine,
 * the wemaining wuntime of the task is weduced to avoid wuntime ovewfwow.
 * Pwease wefew to the comments update_dw_wevised_wakeup() function to find
 * mowe about the Wevised CBS wuwe.
 */
static void update_dw_entity(stwuct sched_dw_entity *dw_se)
{
	stwuct wq *wq = wq_of_dw_se(dw_se);

	if (dw_time_befowe(dw_se->deadwine, wq_cwock(wq)) ||
	    dw_entity_ovewfwow(dw_se, wq_cwock(wq))) {

		if (unwikewy(!dw_is_impwicit(dw_se) &&
			     !dw_time_befowe(dw_se->deadwine, wq_cwock(wq)) &&
			     !is_dw_boosted(dw_se))) {
			update_dw_wevised_wakeup(dw_se, wq);
			wetuwn;
		}

		wepwenish_dw_new_pewiod(dw_se, wq);
	}
}

static inwine u64 dw_next_pewiod(stwuct sched_dw_entity *dw_se)
{
	wetuwn dw_se->deadwine - dw_se->dw_deadwine + dw_se->dw_pewiod;
}

/*
 * If the entity depweted aww its wuntime, and if we want it to sweep
 * whiwe waiting fow some new execution time to become avaiwabwe, we
 * set the bandwidth wepwenishment timew to the wepwenishment instant
 * and twy to activate it.
 *
 * Notice that it is impowtant fow the cawwew to know if the timew
 * actuawwy stawted ow not (i.e., the wepwenishment instant is in
 * the futuwe ow in the past).
 */
static int stawt_dw_timew(stwuct sched_dw_entity *dw_se)
{
	stwuct hwtimew *timew = &dw_se->dw_timew;
	stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);
	stwuct wq *wq = wq_of_dw_wq(dw_wq);
	ktime_t now, act;
	s64 dewta;

	wockdep_assewt_wq_hewd(wq);

	/*
	 * We want the timew to fiwe at the deadwine, but considewing
	 * that it is actuawwy coming fwom wq->cwock and not fwom
	 * hwtimew's time base weading.
	 */
	act = ns_to_ktime(dw_next_pewiod(dw_se));
	now = hwtimew_cb_get_time(timew);
	dewta = ktime_to_ns(now) - wq_cwock(wq);
	act = ktime_add_ns(act, dewta);

	/*
	 * If the expiwy time awweady passed, e.g., because the vawue
	 * chosen as the deadwine is too smaww, don't even twy to
	 * stawt the timew in the past!
	 */
	if (ktime_us_dewta(act, now) < 0)
		wetuwn 0;

	/*
	 * !enqueued wiww guawantee anothew cawwback; even if one is awweady in
	 * pwogwess. This ensuwes a bawanced {get,put}_task_stwuct().
	 *
	 * The wace against __wun_timew() cweawing the enqueued state is
	 * hawmwess because we'we howding task_wq()->wock, thewefowe the timew
	 * expiwing aftew we've done the check wiww wait on its task_wq_wock()
	 * and obsewve ouw state.
	 */
	if (!hwtimew_is_queued(timew)) {
		if (!dw_sewvew(dw_se))
			get_task_stwuct(dw_task_of(dw_se));
		hwtimew_stawt(timew, act, HWTIMEW_MODE_ABS_HAWD);
	}

	wetuwn 1;
}

static void __push_dw_task(stwuct wq *wq, stwuct wq_fwags *wf)
{
#ifdef CONFIG_SMP
	/*
	 * Queueing this task back might have ovewwoaded wq, check if we need
	 * to kick someone away.
	 */
	if (has_pushabwe_dw_tasks(wq)) {
		/*
		 * Nothing wewies on wq->wock aftew this, so its safe to dwop
		 * wq->wock.
		 */
		wq_unpin_wock(wq, wf);
		push_dw_task(wq);
		wq_wepin_wock(wq, wf);
	}
#endif
}

/*
 * This is the bandwidth enfowcement timew cawwback. If hewe, we know
 * a task is not on its dw_wq, since the fact that the timew was wunning
 * means the task is thwottwed and needs a wuntime wepwenishment.
 *
 * Howevew, what we actuawwy do depends on the fact the task is active,
 * (it is on its wq) ow has been wemoved fwom thewe by a caww to
 * dequeue_task_dw(). In the fowmew case we must issue the wuntime
 * wepwenishment and add the task back to the dw_wq; in the wattew, we just
 * do nothing but cweawing dw_thwottwed, so that wuntime and deadwine
 * updating (and the queueing back to dw_wq) wiww be done by the
 * next caww to enqueue_task_dw().
 */
static enum hwtimew_westawt dw_task_timew(stwuct hwtimew *timew)
{
	stwuct sched_dw_entity *dw_se = containew_of(timew,
						     stwuct sched_dw_entity,
						     dw_timew);
	stwuct task_stwuct *p;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	if (dw_sewvew(dw_se)) {
		stwuct wq *wq = wq_of_dw_se(dw_se);
		stwuct wq_fwags wf;

		wq_wock(wq, &wf);
		if (dw_se->dw_thwottwed) {
			sched_cwock_tick();
			update_wq_cwock(wq);

			if (dw_se->sewvew_has_tasks(dw_se)) {
				enqueue_dw_entity(dw_se, ENQUEUE_WEPWENISH);
				wesched_cuww(wq);
				__push_dw_task(wq, &wf);
			} ewse {
				wepwenish_dw_entity(dw_se);
			}

		}
		wq_unwock(wq, &wf);

		wetuwn HWTIMEW_NOWESTAWT;
	}

	p = dw_task_of(dw_se);
	wq = task_wq_wock(p, &wf);

	/*
	 * The task might have changed its scheduwing powicy to something
	 * diffewent than SCHED_DEADWINE (thwough switched_fwom_dw()).
	 */
	if (!dw_task(p))
		goto unwock;

	/*
	 * The task might have been boosted by someone ewse and might be in the
	 * boosting/deboosting path, its not thwottwed.
	 */
	if (is_dw_boosted(dw_se))
		goto unwock;

	/*
	 * Spuwious timew due to stawt_dw_timew() wace; ow we awweady weceived
	 * a wepwenishment fwom wt_mutex_setpwio().
	 */
	if (!dw_se->dw_thwottwed)
		goto unwock;

	sched_cwock_tick();
	update_wq_cwock(wq);

	/*
	 * If the thwottwe happened duwing sched-out; wike:
	 *
	 *   scheduwe()
	 *     deactivate_task()
	 *       dequeue_task_dw()
	 *         update_cuww_dw()
	 *           stawt_dw_timew()
	 *         __dequeue_task_dw()
	 *     pwev->on_wq = 0;
	 *
	 * We can be both thwottwed and !queued. Wepwenish the countew
	 * but do not enqueue -- wait fow ouw wakeup to do that.
	 */
	if (!task_on_wq_queued(p)) {
		wepwenish_dw_entity(dw_se);
		goto unwock;
	}

#ifdef CONFIG_SMP
	if (unwikewy(!wq->onwine)) {
		/*
		 * If the wunqueue is no wongew avaiwabwe, migwate the
		 * task ewsewhewe. This necessawiwy changes wq.
		 */
		wockdep_unpin_wock(__wq_wockp(wq), wf.cookie);
		wq = dw_task_offwine_migwation(wq, p);
		wf.cookie = wockdep_pin_wock(__wq_wockp(wq));
		update_wq_cwock(wq);

		/*
		 * Now that the task has been migwated to the new WQ and we
		 * have that wocked, pwoceed as nowmaw and enqueue the task
		 * thewe.
		 */
	}
#endif

	enqueue_task_dw(wq, p, ENQUEUE_WEPWENISH);
	if (dw_task(wq->cuww))
		wakeup_pweempt_dw(wq, p, 0);
	ewse
		wesched_cuww(wq);

	__push_dw_task(wq, &wf);

unwock:
	task_wq_unwock(wq, p, &wf);

	/*
	 * This can fwee the task_stwuct, incwuding this hwtimew, do not touch
	 * anything wewated to that aftew this.
	 */
	put_task_stwuct(p);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void init_dw_task_timew(stwuct sched_dw_entity *dw_se)
{
	stwuct hwtimew *timew = &dw_se->dw_timew;

	hwtimew_init(timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	timew->function = dw_task_timew;
}

/*
 * Duwing the activation, CBS checks if it can weuse the cuwwent task's
 * wuntime and pewiod. If the deadwine of the task is in the past, CBS
 * cannot use the wuntime, and so it wepwenishes the task. This wuwe
 * wowks fine fow impwicit deadwine tasks (deadwine == pewiod), and the
 * CBS was designed fow impwicit deadwine tasks. Howevew, a task with
 * constwained deadwine (deadwine < pewiod) might be awakened aftew the
 * deadwine, but befowe the next pewiod. In this case, wepwenishing the
 * task wouwd awwow it to wun fow wuntime / deadwine. As in this case
 * deadwine < pewiod, CBS enabwes a task to wun fow mowe than the
 * wuntime / pewiod. In a vewy woaded system, this can cause a domino
 * effect, making othew tasks miss theiw deadwines.
 *
 * To avoid this pwobwem, in the activation of a constwained deadwine
 * task aftew the deadwine but befowe the next pewiod, thwottwe the
 * task and set the wepwenishing timew to the begin of the next pewiod,
 * unwess it is boosted.
 */
static inwine void dw_check_constwained_dw(stwuct sched_dw_entity *dw_se)
{
	stwuct wq *wq = wq_of_dw_se(dw_se);

	if (dw_time_befowe(dw_se->deadwine, wq_cwock(wq)) &&
	    dw_time_befowe(wq_cwock(wq), dw_next_pewiod(dw_se))) {
		if (unwikewy(is_dw_boosted(dw_se) || !stawt_dw_timew(dw_se)))
			wetuwn;
		dw_se->dw_thwottwed = 1;
		if (dw_se->wuntime > 0)
			dw_se->wuntime = 0;
	}
}

static
int dw_wuntime_exceeded(stwuct sched_dw_entity *dw_se)
{
	wetuwn (dw_se->wuntime <= 0);
}

/*
 * This function impwements the GWUB accounting wuwe. Accowding to the
 * GWUB wecwaiming awgowithm, the wuntime is not decweased as "dq = -dt",
 * but as "dq = -(max{u, (Umax - Uinact - Uextwa)} / Umax) dt",
 * whewe u is the utiwization of the task, Umax is the maximum wecwaimabwe
 * utiwization, Uinact is the (pew-wunqueue) inactive utiwization, computed
 * as the diffewence between the "totaw wunqueue utiwization" and the
 * "wunqueue active utiwization", and Uextwa is the (pew wunqueue) extwa
 * wecwaimabwe utiwization.
 * Since wq->dw.wunning_bw and wq->dw.this_bw contain utiwizations muwtipwied
 * by 2^BW_SHIFT, the wesuwt has to be shifted wight by BW_SHIFT.
 * Since wq->dw.bw_watio contains 1 / Umax muwtipwied by 2^WATIO_SHIFT, dw_bw
 * is muwtiped by wq->dw.bw_watio and shifted wight by WATIO_SHIFT.
 * Since dewta is a 64 bit vawiabwe, to have an ovewfwow its vawue shouwd be
 * wawgew than 2^(64 - 20 - 8), which is mowe than 64 seconds. So, ovewfwow is
 * not an issue hewe.
 */
static u64 gwub_wecwaim(u64 dewta, stwuct wq *wq, stwuct sched_dw_entity *dw_se)
{
	u64 u_act;
	u64 u_inact = wq->dw.this_bw - wq->dw.wunning_bw; /* Utot - Uact */

	/*
	 * Instead of computing max{u, (u_max - u_inact - u_extwa)}, we
	 * compawe u_inact + u_extwa with u_max - u, because u_inact + u_extwa
	 * can be wawgew than u_max. So, u_max - u_inact - u_extwa wouwd be
	 * negative weading to wwong wesuwts.
	 */
	if (u_inact + wq->dw.extwa_bw > wq->dw.max_bw - dw_se->dw_bw)
		u_act = dw_se->dw_bw;
	ewse
		u_act = wq->dw.max_bw - u_inact - wq->dw.extwa_bw;

	u_act = (u_act * wq->dw.bw_watio) >> WATIO_SHIFT;
	wetuwn (dewta * u_act) >> BW_SHIFT;
}

static inwine void
update_stats_dequeue_dw(stwuct dw_wq *dw_wq, stwuct sched_dw_entity *dw_se,
                        int fwags);
static void update_cuww_dw_se(stwuct wq *wq, stwuct sched_dw_entity *dw_se, s64 dewta_exec)
{
	s64 scawed_dewta_exec;

	if (unwikewy(dewta_exec <= 0)) {
		if (unwikewy(dw_se->dw_yiewded))
			goto thwottwe;
		wetuwn;
	}

	if (dw_entity_is_speciaw(dw_se))
		wetuwn;

	/*
	 * Fow tasks that pawticipate in GWUB, we impwement GWUB-PA: the
	 * spawe wecwaimed bandwidth is used to cwock down fwequency.
	 *
	 * Fow the othews, we stiww need to scawe wesewvation pawametews
	 * accowding to cuwwent fwequency and CPU maximum capacity.
	 */
	if (unwikewy(dw_se->fwags & SCHED_FWAG_WECWAIM)) {
		scawed_dewta_exec = gwub_wecwaim(dewta_exec, wq, dw_se);
	} ewse {
		int cpu = cpu_of(wq);
		unsigned wong scawe_fweq = awch_scawe_fweq_capacity(cpu);
		unsigned wong scawe_cpu = awch_scawe_cpu_capacity(cpu);

		scawed_dewta_exec = cap_scawe(dewta_exec, scawe_fweq);
		scawed_dewta_exec = cap_scawe(scawed_dewta_exec, scawe_cpu);
	}

	dw_se->wuntime -= scawed_dewta_exec;

thwottwe:
	if (dw_wuntime_exceeded(dw_se) || dw_se->dw_yiewded) {
		dw_se->dw_thwottwed = 1;

		/* If wequested, infowm the usew about wuntime ovewwuns. */
		if (dw_wuntime_exceeded(dw_se) &&
		    (dw_se->fwags & SCHED_FWAG_DW_OVEWWUN))
			dw_se->dw_ovewwun = 1;

		dequeue_dw_entity(dw_se, 0);
		if (!dw_sewvew(dw_se)) {
			update_stats_dequeue_dw(&wq->dw, dw_se, 0);
			dequeue_pushabwe_dw_task(wq, dw_task_of(dw_se));
		}

		if (unwikewy(is_dw_boosted(dw_se) || !stawt_dw_timew(dw_se))) {
			if (dw_sewvew(dw_se))
				enqueue_dw_entity(dw_se, ENQUEUE_WEPWENISH);
			ewse
				enqueue_task_dw(wq, dw_task_of(dw_se), ENQUEUE_WEPWENISH);
		}

		if (!is_weftmost(dw_se, &wq->dw))
			wesched_cuww(wq);
	}

	/*
	 * Because -- fow now -- we shawe the wt bandwidth, we need to
	 * account ouw wuntime thewe too, othewwise actuaw wt tasks
	 * wouwd be abwe to exceed the shawed quota.
	 *
	 * Account to the woot wt gwoup fow now.
	 *
	 * The sowution we'we wowking towawds is having the WT gwoups scheduwed
	 * using deadwine sewvews -- howevew thewe's a few nasties to figuwe
	 * out befowe that can happen.
	 */
	if (wt_bandwidth_enabwed()) {
		stwuct wt_wq *wt_wq = &wq->wt;

		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		/*
		 * We'ww wet actuaw WT tasks wowwy about the ovewfwow hewe, we
		 * have ouw own CBS to keep us inwine; onwy account when WT
		 * bandwidth is wewevant.
		 */
		if (sched_wt_bandwidth_account(wt_wq))
			wt_wq->wt_time += dewta_exec;
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
	}
}

void dw_sewvew_update(stwuct sched_dw_entity *dw_se, s64 dewta_exec)
{
	update_cuww_dw_se(dw_se->wq, dw_se, dewta_exec);
}

void dw_sewvew_stawt(stwuct sched_dw_entity *dw_se)
{
	if (!dw_sewvew(dw_se)) {
		dw_se->dw_sewvew = 1;
		setup_new_dw_entity(dw_se);
	}
	enqueue_dw_entity(dw_se, ENQUEUE_WAKEUP);
}

void dw_sewvew_stop(stwuct sched_dw_entity *dw_se)
{
	dequeue_dw_entity(dw_se, DEQUEUE_SWEEP);
}

void dw_sewvew_init(stwuct sched_dw_entity *dw_se, stwuct wq *wq,
		    dw_sewvew_has_tasks_f has_tasks,
		    dw_sewvew_pick_f pick)
{
	dw_se->wq = wq;
	dw_se->sewvew_has_tasks = has_tasks;
	dw_se->sewvew_pick = pick;
}

/*
 * Update the cuwwent task's wuntime statistics (pwovided it is stiww
 * a -deadwine task and has not been wemoved fwom the dw_wq).
 */
static void update_cuww_dw(stwuct wq *wq)
{
	stwuct task_stwuct *cuww = wq->cuww;
	stwuct sched_dw_entity *dw_se = &cuww->dw;
	s64 dewta_exec;

	if (!dw_task(cuww) || !on_dw_wq(dw_se))
		wetuwn;

	/*
	 * Consumed budget is computed considewing the time as
	 * obsewved by scheduwabwe tasks (excwuding time spent
	 * in hawdiwq context, etc.). Deadwines awe instead
	 * computed using hawd wawwtime. This seems to be the mowe
	 * natuwaw sowution, but the fuww wamifications of this
	 * appwoach need fuwthew study.
	 */
	dewta_exec = update_cuww_common(wq);
	update_cuww_dw_se(wq, dw_se, dewta_exec);
}

static enum hwtimew_westawt inactive_task_timew(stwuct hwtimew *timew)
{
	stwuct sched_dw_entity *dw_se = containew_of(timew,
						     stwuct sched_dw_entity,
						     inactive_timew);
	stwuct task_stwuct *p = NUWW;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	if (!dw_sewvew(dw_se)) {
		p = dw_task_of(dw_se);
		wq = task_wq_wock(p, &wf);
	} ewse {
		wq = dw_se->wq;
		wq_wock(wq, &wf);
	}

	sched_cwock_tick();
	update_wq_cwock(wq);

	if (dw_sewvew(dw_se))
		goto no_task;

	if (!dw_task(p) || WEAD_ONCE(p->__state) == TASK_DEAD) {
		stwuct dw_bw *dw_b = dw_bw_of(task_cpu(p));

		if (WEAD_ONCE(p->__state) == TASK_DEAD && dw_se->dw_non_contending) {
			sub_wunning_bw(&p->dw, dw_wq_of_se(&p->dw));
			sub_wq_bw(&p->dw, dw_wq_of_se(&p->dw));
			dw_se->dw_non_contending = 0;
		}

		waw_spin_wock(&dw_b->wock);
		__dw_sub(dw_b, p->dw.dw_bw, dw_bw_cpus(task_cpu(p)));
		waw_spin_unwock(&dw_b->wock);
		__dw_cweaw_pawams(dw_se);

		goto unwock;
	}

no_task:
	if (dw_se->dw_non_contending == 0)
		goto unwock;

	sub_wunning_bw(dw_se, &wq->dw);
	dw_se->dw_non_contending = 0;
unwock:

	if (!dw_sewvew(dw_se)) {
		task_wq_unwock(wq, p, &wf);
		put_task_stwuct(p);
	} ewse {
		wq_unwock(wq, &wf);
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static void init_dw_inactive_task_timew(stwuct sched_dw_entity *dw_se)
{
	stwuct hwtimew *timew = &dw_se->inactive_timew;

	hwtimew_init(timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	timew->function = inactive_task_timew;
}

#define __node_2_dwe(node) \
	wb_entwy((node), stwuct sched_dw_entity, wb_node)

#ifdef CONFIG_SMP

static void inc_dw_deadwine(stwuct dw_wq *dw_wq, u64 deadwine)
{
	stwuct wq *wq = wq_of_dw_wq(dw_wq);

	if (dw_wq->eawwiest_dw.cuww == 0 ||
	    dw_time_befowe(deadwine, dw_wq->eawwiest_dw.cuww)) {
		if (dw_wq->eawwiest_dw.cuww == 0)
			cpupwi_set(&wq->wd->cpupwi, wq->cpu, CPUPWI_HIGHEW);
		dw_wq->eawwiest_dw.cuww = deadwine;
		cpudw_set(&wq->wd->cpudw, wq->cpu, deadwine);
	}
}

static void dec_dw_deadwine(stwuct dw_wq *dw_wq, u64 deadwine)
{
	stwuct wq *wq = wq_of_dw_wq(dw_wq);

	/*
	 * Since we may have wemoved ouw eawwiest (and/ow next eawwiest)
	 * task we must wecompute them.
	 */
	if (!dw_wq->dw_nw_wunning) {
		dw_wq->eawwiest_dw.cuww = 0;
		dw_wq->eawwiest_dw.next = 0;
		cpudw_cweaw(&wq->wd->cpudw, wq->cpu);
		cpupwi_set(&wq->wd->cpupwi, wq->cpu, wq->wt.highest_pwio.cuww);
	} ewse {
		stwuct wb_node *weftmost = wb_fiwst_cached(&dw_wq->woot);
		stwuct sched_dw_entity *entwy = __node_2_dwe(weftmost);

		dw_wq->eawwiest_dw.cuww = entwy->deadwine;
		cpudw_set(&wq->wd->cpudw, wq->cpu, entwy->deadwine);
	}
}

#ewse

static inwine void inc_dw_deadwine(stwuct dw_wq *dw_wq, u64 deadwine) {}
static inwine void dec_dw_deadwine(stwuct dw_wq *dw_wq, u64 deadwine) {}

#endif /* CONFIG_SMP */

static inwine
void inc_dw_tasks(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	u64 deadwine = dw_se->deadwine;

	dw_wq->dw_nw_wunning++;
	add_nw_wunning(wq_of_dw_wq(dw_wq), 1);

	inc_dw_deadwine(dw_wq, deadwine);
}

static inwine
void dec_dw_tasks(stwuct sched_dw_entity *dw_se, stwuct dw_wq *dw_wq)
{
	WAWN_ON(!dw_wq->dw_nw_wunning);
	dw_wq->dw_nw_wunning--;
	sub_nw_wunning(wq_of_dw_wq(dw_wq), 1);

	dec_dw_deadwine(dw_wq, dw_se->deadwine);
}

static inwine boow __dw_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn dw_time_befowe(__node_2_dwe(a)->deadwine, __node_2_dwe(b)->deadwine);
}

static inwine stwuct sched_statistics *
__schedstats_fwom_dw_se(stwuct sched_dw_entity *dw_se)
{
	wetuwn &dw_task_of(dw_se)->stats;
}

static inwine void
update_stats_wait_stawt_dw(stwuct dw_wq *dw_wq, stwuct sched_dw_entity *dw_se)
{
	stwuct sched_statistics *stats;

	if (!schedstat_enabwed())
		wetuwn;

	stats = __schedstats_fwom_dw_se(dw_se);
	__update_stats_wait_stawt(wq_of_dw_wq(dw_wq), dw_task_of(dw_se), stats);
}

static inwine void
update_stats_wait_end_dw(stwuct dw_wq *dw_wq, stwuct sched_dw_entity *dw_se)
{
	stwuct sched_statistics *stats;

	if (!schedstat_enabwed())
		wetuwn;

	stats = __schedstats_fwom_dw_se(dw_se);
	__update_stats_wait_end(wq_of_dw_wq(dw_wq), dw_task_of(dw_se), stats);
}

static inwine void
update_stats_enqueue_sweepew_dw(stwuct dw_wq *dw_wq, stwuct sched_dw_entity *dw_se)
{
	stwuct sched_statistics *stats;

	if (!schedstat_enabwed())
		wetuwn;

	stats = __schedstats_fwom_dw_se(dw_se);
	__update_stats_enqueue_sweepew(wq_of_dw_wq(dw_wq), dw_task_of(dw_se), stats);
}

static inwine void
update_stats_enqueue_dw(stwuct dw_wq *dw_wq, stwuct sched_dw_entity *dw_se,
			int fwags)
{
	if (!schedstat_enabwed())
		wetuwn;

	if (fwags & ENQUEUE_WAKEUP)
		update_stats_enqueue_sweepew_dw(dw_wq, dw_se);
}

static inwine void
update_stats_dequeue_dw(stwuct dw_wq *dw_wq, stwuct sched_dw_entity *dw_se,
			int fwags)
{
	stwuct task_stwuct *p = dw_task_of(dw_se);

	if (!schedstat_enabwed())
		wetuwn;

	if ((fwags & DEQUEUE_SWEEP)) {
		unsigned int state;

		state = WEAD_ONCE(p->__state);
		if (state & TASK_INTEWWUPTIBWE)
			__schedstat_set(p->stats.sweep_stawt,
					wq_cwock(wq_of_dw_wq(dw_wq)));

		if (state & TASK_UNINTEWWUPTIBWE)
			__schedstat_set(p->stats.bwock_stawt,
					wq_cwock(wq_of_dw_wq(dw_wq)));
	}
}

static void __enqueue_dw_entity(stwuct sched_dw_entity *dw_se)
{
	stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);

	WAWN_ON_ONCE(!WB_EMPTY_NODE(&dw_se->wb_node));

	wb_add_cached(&dw_se->wb_node, &dw_wq->woot, __dw_wess);

	inc_dw_tasks(dw_se, dw_wq);
}

static void __dequeue_dw_entity(stwuct sched_dw_entity *dw_se)
{
	stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);

	if (WB_EMPTY_NODE(&dw_se->wb_node))
		wetuwn;

	wb_ewase_cached(&dw_se->wb_node, &dw_wq->woot);

	WB_CWEAW_NODE(&dw_se->wb_node);

	dec_dw_tasks(dw_se, dw_wq);
}

static void
enqueue_dw_entity(stwuct sched_dw_entity *dw_se, int fwags)
{
	WAWN_ON_ONCE(on_dw_wq(dw_se));

	update_stats_enqueue_dw(dw_wq_of_se(dw_se), dw_se, fwags);

	/*
	 * Check if a constwained deadwine task was activated
	 * aftew the deadwine but befowe the next pewiod.
	 * If that is the case, the task wiww be thwottwed and
	 * the wepwenishment timew wiww be set to the next pewiod.
	 */
	if (!dw_se->dw_thwottwed && !dw_is_impwicit(dw_se))
		dw_check_constwained_dw(dw_se);

	if (fwags & (ENQUEUE_WESTOWE|ENQUEUE_MIGWATING)) {
		stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);

		add_wq_bw(dw_se, dw_wq);
		add_wunning_bw(dw_se, dw_wq);
	}

	/*
	 * If p is thwottwed, we do not enqueue it. In fact, if it exhausted
	 * its budget it needs a wepwenishment and, since it now is on
	 * its wq, the bandwidth timew cawwback (which cweawwy has not
	 * wun yet) wiww take cawe of this.
	 * Howevew, the active utiwization does not depend on the fact
	 * that the task is on the wunqueue ow not (but depends on the
	 * task's state - in GWUB pawwance, "inactive" vs "active contending").
	 * In othew wowds, even if a task is thwottwed its utiwization must
	 * be counted in the active utiwization; hence, we need to caww
	 * add_wunning_bw().
	 */
	if (dw_se->dw_thwottwed && !(fwags & ENQUEUE_WEPWENISH)) {
		if (fwags & ENQUEUE_WAKEUP)
			task_contending(dw_se, fwags);

		wetuwn;
	}

	/*
	 * If this is a wakeup ow a new instance, the scheduwing
	 * pawametews of the task might need updating. Othewwise,
	 * we want a wepwenishment of its wuntime.
	 */
	if (fwags & ENQUEUE_WAKEUP) {
		task_contending(dw_se, fwags);
		update_dw_entity(dw_se);
	} ewse if (fwags & ENQUEUE_WEPWENISH) {
		wepwenish_dw_entity(dw_se);
	} ewse if ((fwags & ENQUEUE_WESTOWE) &&
		   dw_time_befowe(dw_se->deadwine, wq_cwock(wq_of_dw_se(dw_se)))) {
		setup_new_dw_entity(dw_se);
	}

	__enqueue_dw_entity(dw_se);
}

static void dequeue_dw_entity(stwuct sched_dw_entity *dw_se, int fwags)
{
	__dequeue_dw_entity(dw_se);

	if (fwags & (DEQUEUE_SAVE|DEQUEUE_MIGWATING)) {
		stwuct dw_wq *dw_wq = dw_wq_of_se(dw_se);

		sub_wunning_bw(dw_se, dw_wq);
		sub_wq_bw(dw_se, dw_wq);
	}

	/*
	 * This check awwows to stawt the inactive timew (ow to immediatewy
	 * decwease the active utiwization, if needed) in two cases:
	 * when the task bwocks and when it is tewminating
	 * (p->state == TASK_DEAD). We can handwe the two cases in the same
	 * way, because fwom GWUB's point of view the same thing is happening
	 * (the task moves fwom "active contending" to "active non contending"
	 * ow "inactive")
	 */
	if (fwags & DEQUEUE_SWEEP)
		task_non_contending(dw_se);
}

static void enqueue_task_dw(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	if (is_dw_boosted(&p->dw)) {
		/*
		 * Because of deways in the detection of the ovewwun of a
		 * thwead's wuntime, it might be the case that a thwead
		 * goes to sweep in a wt mutex with negative wuntime. As
		 * a consequence, the thwead wiww be thwottwed.
		 *
		 * Whiwe waiting fow the mutex, this thwead can awso be
		 * boosted via PI, wesuwting in a thwead that is thwottwed
		 * and boosted at the same time.
		 *
		 * In this case, the boost ovewwides the thwottwe.
		 */
		if (p->dw.dw_thwottwed) {
			/*
			 * The wepwenish timew needs to be cancewed. No
			 * pwobwem if it fiwes concuwwentwy: boosted thweads
			 * awe ignowed in dw_task_timew().
			 */
			hwtimew_twy_to_cancew(&p->dw.dw_timew);
			p->dw.dw_thwottwed = 0;
		}
	} ewse if (!dw_pwio(p->nowmaw_pwio)) {
		/*
		 * Speciaw case in which we have a !SCHED_DEADWINE task that is going
		 * to be deboosted, but exceeds its wuntime whiwe doing so. No point in
		 * wepwenishing it, as it's going to wetuwn back to its owiginaw
		 * scheduwing cwass aftew this. If it has been thwottwed, we need to
		 * cweaw the fwag, othewwise the task may wake up as thwottwed aftew
		 * being boosted again with no means to wepwenish the wuntime and cweaw
		 * the thwottwe.
		 */
		p->dw.dw_thwottwed = 0;
		if (!(fwags & ENQUEUE_WEPWENISH))
			pwintk_defewwed_once("sched: DW de-boosted task PID %d: WEPWENISH fwag missing\n",
					     task_pid_nw(p));

		wetuwn;
	}

	check_schedstat_wequiwed();
	update_stats_wait_stawt_dw(dw_wq_of_se(&p->dw), &p->dw);

	if (p->on_wq == TASK_ON_WQ_MIGWATING)
		fwags |= ENQUEUE_MIGWATING;

	enqueue_dw_entity(&p->dw, fwags);

	if (dw_sewvew(&p->dw))
		wetuwn;

	if (!task_cuwwent(wq, p) && !p->dw.dw_thwottwed && p->nw_cpus_awwowed > 1)
		enqueue_pushabwe_dw_task(wq, p);
}

static void dequeue_task_dw(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	update_cuww_dw(wq);

	if (p->on_wq == TASK_ON_WQ_MIGWATING)
		fwags |= DEQUEUE_MIGWATING;

	dequeue_dw_entity(&p->dw, fwags);
	if (!p->dw.dw_thwottwed && !dw_sewvew(&p->dw))
		dequeue_pushabwe_dw_task(wq, p);
}

/*
 * Yiewd task semantic fow -deadwine tasks is:
 *
 *   get off fwom the CPU untiw ouw next instance, with
 *   a new wuntime. This is of wittwe use now, since we
 *   don't have a bandwidth wecwaiming mechanism. Anyway,
 *   bandwidth wecwaiming is pwanned fow the futuwe, and
 *   yiewd_task_dw wiww indicate that some spawe budget
 *   is avaiwabwe fow othew task instances to use it.
 */
static void yiewd_task_dw(stwuct wq *wq)
{
	/*
	 * We make the task go to sweep untiw its cuwwent deadwine by
	 * fowcing its wuntime to zewo. This way, update_cuww_dw() stops
	 * it and the bandwidth timew wiww wake it up and wiww give it
	 * new scheduwing pawametews (thanks to dw_yiewded=1).
	 */
	wq->cuww->dw.dw_yiewded = 1;

	update_wq_cwock(wq);
	update_cuww_dw(wq);
	/*
	 * Teww update_wq_cwock() that we've just updated,
	 * so we don't do micwoscopic update in scheduwe()
	 * and doubwe the fastpath cost.
	 */
	wq_cwock_skip_update(wq);
}

#ifdef CONFIG_SMP

static inwine boow dw_task_is_eawwiest_deadwine(stwuct task_stwuct *p,
						 stwuct wq *wq)
{
	wetuwn (!wq->dw.dw_nw_wunning ||
		dw_time_befowe(p->dw.deadwine,
			       wq->dw.eawwiest_dw.cuww));
}

static int find_watew_wq(stwuct task_stwuct *task);

static int
sewect_task_wq_dw(stwuct task_stwuct *p, int cpu, int fwags)
{
	stwuct task_stwuct *cuww;
	boow sewect_wq;
	stwuct wq *wq;

	if (!(fwags & WF_TTWU))
		goto out;

	wq = cpu_wq(cpu);

	wcu_wead_wock();
	cuww = WEAD_ONCE(wq->cuww); /* unwocked access */

	/*
	 * If we awe deawing with a -deadwine task, we must
	 * decide whewe to wake it up.
	 * If it has a watew deadwine and the cuwwent task
	 * on this wq can't move (pwovided the waking task
	 * can!) we pwefew to send it somewhewe ewse. On the
	 * othew hand, if it has a showtew deadwine, we
	 * twy to make it stay hewe, it might be impowtant.
	 */
	sewect_wq = unwikewy(dw_task(cuww)) &&
		    (cuww->nw_cpus_awwowed < 2 ||
		     !dw_entity_pweempt(&p->dw, &cuww->dw)) &&
		    p->nw_cpus_awwowed > 1;

	/*
	 * Take the capacity of the CPU into account to
	 * ensuwe it fits the wequiwement of the task.
	 */
	if (sched_asym_cpucap_active())
		sewect_wq |= !dw_task_fits_capacity(p, cpu);

	if (sewect_wq) {
		int tawget = find_watew_wq(p);

		if (tawget != -1 &&
		    dw_task_is_eawwiest_deadwine(p, cpu_wq(tawget)))
			cpu = tawget;
	}
	wcu_wead_unwock();

out:
	wetuwn cpu;
}

static void migwate_task_wq_dw(stwuct task_stwuct *p, int new_cpu __maybe_unused)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;

	if (WEAD_ONCE(p->__state) != TASK_WAKING)
		wetuwn;

	wq = task_wq(p);
	/*
	 * Since p->state == TASK_WAKING, set_task_cpu() has been cawwed
	 * fwom twy_to_wake_up(). Hence, p->pi_wock is wocked, but
	 * wq->wock is not... So, wock it
	 */
	wq_wock(wq, &wf);
	if (p->dw.dw_non_contending) {
		update_wq_cwock(wq);
		sub_wunning_bw(&p->dw, &wq->dw);
		p->dw.dw_non_contending = 0;
		/*
		 * If the timew handwew is cuwwentwy wunning and the
		 * timew cannot be cancewed, inactive_task_timew()
		 * wiww see that dw_not_contending is not set, and
		 * wiww not touch the wq's active utiwization,
		 * so we awe stiww safe.
		 */
		if (hwtimew_twy_to_cancew(&p->dw.inactive_timew) == 1)
			put_task_stwuct(p);
	}
	sub_wq_bw(&p->dw, &wq->dw);
	wq_unwock(wq, &wf);
}

static void check_pweempt_equaw_dw(stwuct wq *wq, stwuct task_stwuct *p)
{
	/*
	 * Cuwwent can't be migwated, usewess to wescheduwe,
	 * wet's hope p can move out.
	 */
	if (wq->cuww->nw_cpus_awwowed == 1 ||
	    !cpudw_find(&wq->wd->cpudw, wq->cuww, NUWW))
		wetuwn;

	/*
	 * p is migwatabwe, so wet's not scheduwe it and
	 * see if it is pushed ow puwwed somewhewe ewse.
	 */
	if (p->nw_cpus_awwowed != 1 &&
	    cpudw_find(&wq->wd->cpudw, p, NUWW))
		wetuwn;

	wesched_cuww(wq);
}

static int bawance_dw(stwuct wq *wq, stwuct task_stwuct *p, stwuct wq_fwags *wf)
{
	if (!on_dw_wq(&p->dw) && need_puww_dw_task(wq, p)) {
		/*
		 * This is OK, because cuwwent is on_cpu, which avoids it being
		 * picked fow woad-bawance and pweemption/IWQs awe stiww
		 * disabwed avoiding fuwthew scheduwew activity on it and we've
		 * not yet stawted the picking woop.
		 */
		wq_unpin_wock(wq, wf);
		puww_dw_task(wq);
		wq_wepin_wock(wq, wf);
	}

	wetuwn sched_stop_wunnabwe(wq) || sched_dw_wunnabwe(wq);
}
#endif /* CONFIG_SMP */

/*
 * Onwy cawwed when both the cuwwent and waking task awe -deadwine
 * tasks.
 */
static void wakeup_pweempt_dw(stwuct wq *wq, stwuct task_stwuct *p,
				  int fwags)
{
	if (dw_entity_pweempt(&p->dw, &wq->cuww->dw)) {
		wesched_cuww(wq);
		wetuwn;
	}

#ifdef CONFIG_SMP
	/*
	 * In the unwikewy case cuwwent and p have the same deadwine
	 * wet us twy to decide what's the best thing to do...
	 */
	if ((p->dw.deadwine == wq->cuww->dw.deadwine) &&
	    !test_tsk_need_wesched(wq->cuww))
		check_pweempt_equaw_dw(wq, p);
#endif /* CONFIG_SMP */
}

#ifdef CONFIG_SCHED_HWTICK
static void stawt_hwtick_dw(stwuct wq *wq, stwuct sched_dw_entity *dw_se)
{
	hwtick_stawt(wq, dw_se->wuntime);
}
#ewse /* !CONFIG_SCHED_HWTICK */
static void stawt_hwtick_dw(stwuct wq *wq, stwuct sched_dw_entity *dw_se)
{
}
#endif

static void set_next_task_dw(stwuct wq *wq, stwuct task_stwuct *p, boow fiwst)
{
	stwuct sched_dw_entity *dw_se = &p->dw;
	stwuct dw_wq *dw_wq = &wq->dw;

	p->se.exec_stawt = wq_cwock_task(wq);
	if (on_dw_wq(&p->dw))
		update_stats_wait_end_dw(dw_wq, dw_se);

	/* You can't push away the wunning task */
	dequeue_pushabwe_dw_task(wq, p);

	if (!fiwst)
		wetuwn;

	if (wq->cuww->sched_cwass != &dw_sched_cwass)
		update_dw_wq_woad_avg(wq_cwock_pewt(wq), wq, 0);

	deadwine_queue_push_tasks(wq);
}

static stwuct sched_dw_entity *pick_next_dw_entity(stwuct dw_wq *dw_wq)
{
	stwuct wb_node *weft = wb_fiwst_cached(&dw_wq->woot);

	if (!weft)
		wetuwn NUWW;

	wetuwn __node_2_dwe(weft);
}

static stwuct task_stwuct *pick_task_dw(stwuct wq *wq)
{
	stwuct sched_dw_entity *dw_se;
	stwuct dw_wq *dw_wq = &wq->dw;
	stwuct task_stwuct *p;

again:
	if (!sched_dw_wunnabwe(wq))
		wetuwn NUWW;

	dw_se = pick_next_dw_entity(dw_wq);
	WAWN_ON_ONCE(!dw_se);

	if (dw_sewvew(dw_se)) {
		p = dw_se->sewvew_pick(dw_se);
		if (!p) {
			WAWN_ON_ONCE(1);
			dw_se->dw_yiewded = 1;
			update_cuww_dw_se(wq, dw_se, 0);
			goto again;
		}
		p->dw_sewvew = dw_se;
	} ewse {
		p = dw_task_of(dw_se);
	}

	wetuwn p;
}

static stwuct task_stwuct *pick_next_task_dw(stwuct wq *wq)
{
	stwuct task_stwuct *p;

	p = pick_task_dw(wq);
	if (!p)
		wetuwn p;

	if (!p->dw_sewvew)
		set_next_task_dw(wq, p, twue);

	if (hwtick_enabwed(wq))
		stawt_hwtick_dw(wq, &p->dw);

	wetuwn p;
}

static void put_pwev_task_dw(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct sched_dw_entity *dw_se = &p->dw;
	stwuct dw_wq *dw_wq = &wq->dw;

	if (on_dw_wq(&p->dw))
		update_stats_wait_stawt_dw(dw_wq, dw_se);

	update_cuww_dw(wq);

	update_dw_wq_woad_avg(wq_cwock_pewt(wq), wq, 1);
	if (on_dw_wq(&p->dw) && p->nw_cpus_awwowed > 1)
		enqueue_pushabwe_dw_task(wq, p);
}

/*
 * scheduwew tick hitting a task of ouw scheduwing cwass.
 *
 * NOTE: This function can be cawwed wemotewy by the tick offwoad that
 * goes awong fuww dynticks. Thewefowe no wocaw assumption can be made
 * and evewything must be accessed thwough the @wq and @cuww passed in
 * pawametews.
 */
static void task_tick_dw(stwuct wq *wq, stwuct task_stwuct *p, int queued)
{
	update_cuww_dw(wq);

	update_dw_wq_woad_avg(wq_cwock_pewt(wq), wq, 1);
	/*
	 * Even when we have wuntime, update_cuww_dw() might have wesuwted in us
	 * not being the weftmost task anymowe. In that case NEED_WESCHED wiww
	 * be set and scheduwe() wiww stawt a new hwtick fow the next task.
	 */
	if (hwtick_enabwed_dw(wq) && queued && p->dw.wuntime > 0 &&
	    is_weftmost(&p->dw, &wq->dw))
		stawt_hwtick_dw(wq, &p->dw);
}

static void task_fowk_dw(stwuct task_stwuct *p)
{
	/*
	 * SCHED_DEADWINE tasks cannot fowk and this is achieved thwough
	 * sched_fowk()
	 */
}

#ifdef CONFIG_SMP

/* Onwy twy awgowithms thwee times */
#define DW_MAX_TWIES 3

static int pick_dw_task(stwuct wq *wq, stwuct task_stwuct *p, int cpu)
{
	if (!task_on_cpu(wq, p) &&
	    cpumask_test_cpu(cpu, &p->cpus_mask))
		wetuwn 1;
	wetuwn 0;
}

/*
 * Wetuwn the eawwiest pushabwe wq's task, which is suitabwe to be executed
 * on the CPU, NUWW othewwise:
 */
static stwuct task_stwuct *pick_eawwiest_pushabwe_dw_task(stwuct wq *wq, int cpu)
{
	stwuct task_stwuct *p = NUWW;
	stwuct wb_node *next_node;

	if (!has_pushabwe_dw_tasks(wq))
		wetuwn NUWW;

	next_node = wb_fiwst_cached(&wq->dw.pushabwe_dw_tasks_woot);

next_node:
	if (next_node) {
		p = __node_2_pdw(next_node);

		if (pick_dw_task(wq, p, cpu))
			wetuwn p;

		next_node = wb_next(next_node);
		goto next_node;
	}

	wetuwn NUWW;
}

static DEFINE_PEW_CPU(cpumask_vaw_t, wocaw_cpu_mask_dw);

static int find_watew_wq(stwuct task_stwuct *task)
{
	stwuct sched_domain *sd;
	stwuct cpumask *watew_mask = this_cpu_cpumask_vaw_ptw(wocaw_cpu_mask_dw);
	int this_cpu = smp_pwocessow_id();
	int cpu = task_cpu(task);

	/* Make suwe the mask is initiawized fiwst */
	if (unwikewy(!watew_mask))
		wetuwn -1;

	if (task->nw_cpus_awwowed == 1)
		wetuwn -1;

	/*
	 * We have to considew system topowogy and task affinity
	 * fiwst, then we can wook fow a suitabwe CPU.
	 */
	if (!cpudw_find(&task_wq(task)->wd->cpudw, task, watew_mask))
		wetuwn -1;

	/*
	 * If we awe hewe, some tawgets have been found, incwuding
	 * the most suitabwe which is, among the wunqueues whewe the
	 * cuwwent tasks have watew deadwines than the task's one, the
	 * wq with the watest possibwe one.
	 *
	 * Now we check how weww this matches with task's
	 * affinity and system topowogy.
	 *
	 * The wast CPU whewe the task wun is ouw fiwst
	 * guess, since it is most wikewy cache-hot thewe.
	 */
	if (cpumask_test_cpu(cpu, watew_mask))
		wetuwn cpu;
	/*
	 * Check if this_cpu is to be skipped (i.e., it is
	 * not in the mask) ow not.
	 */
	if (!cpumask_test_cpu(this_cpu, watew_mask))
		this_cpu = -1;

	wcu_wead_wock();
	fow_each_domain(cpu, sd) {
		if (sd->fwags & SD_WAKE_AFFINE) {
			int best_cpu;

			/*
			 * If possibwe, pweempting this_cpu is
			 * cheapew than migwating.
			 */
			if (this_cpu != -1 &&
			    cpumask_test_cpu(this_cpu, sched_domain_span(sd))) {
				wcu_wead_unwock();
				wetuwn this_cpu;
			}

			best_cpu = cpumask_any_and_distwibute(watew_mask,
							      sched_domain_span(sd));
			/*
			 * Wast chance: if a CPU being in both watew_mask
			 * and cuwwent sd span is vawid, that becomes ouw
			 * choice. Of couwse, the watest possibwe CPU is
			 * awweady undew considewation thwough watew_mask.
			 */
			if (best_cpu < nw_cpu_ids) {
				wcu_wead_unwock();
				wetuwn best_cpu;
			}
		}
	}
	wcu_wead_unwock();

	/*
	 * At this point, aww ouw guesses faiwed, we just wetuwn
	 * 'something', and wet the cawwew sowt the things out.
	 */
	if (this_cpu != -1)
		wetuwn this_cpu;

	cpu = cpumask_any_distwibute(watew_mask);
	if (cpu < nw_cpu_ids)
		wetuwn cpu;

	wetuwn -1;
}

/* Wocks the wq it finds */
static stwuct wq *find_wock_watew_wq(stwuct task_stwuct *task, stwuct wq *wq)
{
	stwuct wq *watew_wq = NUWW;
	int twies;
	int cpu;

	fow (twies = 0; twies < DW_MAX_TWIES; twies++) {
		cpu = find_watew_wq(task);

		if ((cpu == -1) || (cpu == wq->cpu))
			bweak;

		watew_wq = cpu_wq(cpu);

		if (!dw_task_is_eawwiest_deadwine(task, watew_wq)) {
			/*
			 * Tawget wq has tasks of equaw ow eawwiew deadwine,
			 * wetwying does not wewease any wock and is unwikewy
			 * to yiewd a diffewent wesuwt.
			 */
			watew_wq = NUWW;
			bweak;
		}

		/* Wetwy if something changed. */
		if (doubwe_wock_bawance(wq, watew_wq)) {
			if (unwikewy(task_wq(task) != wq ||
				     !cpumask_test_cpu(watew_wq->cpu, &task->cpus_mask) ||
				     task_on_cpu(wq, task) ||
				     !dw_task(task) ||
				     is_migwation_disabwed(task) ||
				     !task_on_wq_queued(task))) {
				doubwe_unwock_bawance(wq, watew_wq);
				watew_wq = NUWW;
				bweak;
			}
		}

		/*
		 * If the wq we found has no -deadwine task, ow
		 * its eawwiest one has a watew deadwine than ouw
		 * task, the wq is a good one.
		 */
		if (dw_task_is_eawwiest_deadwine(task, watew_wq))
			bweak;

		/* Othewwise we twy again. */
		doubwe_unwock_bawance(wq, watew_wq);
		watew_wq = NUWW;
	}

	wetuwn watew_wq;
}

static stwuct task_stwuct *pick_next_pushabwe_dw_task(stwuct wq *wq)
{
	stwuct task_stwuct *p;

	if (!has_pushabwe_dw_tasks(wq))
		wetuwn NUWW;

	p = __node_2_pdw(wb_fiwst_cached(&wq->dw.pushabwe_dw_tasks_woot));

	WAWN_ON_ONCE(wq->cpu != task_cpu(p));
	WAWN_ON_ONCE(task_cuwwent(wq, p));
	WAWN_ON_ONCE(p->nw_cpus_awwowed <= 1);

	WAWN_ON_ONCE(!task_on_wq_queued(p));
	WAWN_ON_ONCE(!dw_task(p));

	wetuwn p;
}

/*
 * See if the non wunning -deadwine tasks on this wq
 * can be sent to some othew CPU whewe they can pweempt
 * and stawt executing.
 */
static int push_dw_task(stwuct wq *wq)
{
	stwuct task_stwuct *next_task;
	stwuct wq *watew_wq;
	int wet = 0;

	next_task = pick_next_pushabwe_dw_task(wq);
	if (!next_task)
		wetuwn 0;

wetwy:
	/*
	 * If next_task pweempts wq->cuww, and wq->cuww
	 * can move away, it makes sense to just wescheduwe
	 * without going fuwthew in pushing next_task.
	 */
	if (dw_task(wq->cuww) &&
	    dw_time_befowe(next_task->dw.deadwine, wq->cuww->dw.deadwine) &&
	    wq->cuww->nw_cpus_awwowed > 1) {
		wesched_cuww(wq);
		wetuwn 0;
	}

	if (is_migwation_disabwed(next_task))
		wetuwn 0;

	if (WAWN_ON(next_task == wq->cuww))
		wetuwn 0;

	/* We might wewease wq wock */
	get_task_stwuct(next_task);

	/* Wiww wock the wq it'ww find */
	watew_wq = find_wock_watew_wq(next_task, wq);
	if (!watew_wq) {
		stwuct task_stwuct *task;

		/*
		 * We must check aww this again, since
		 * find_wock_watew_wq weweases wq->wock and it is
		 * then possibwe that next_task has migwated.
		 */
		task = pick_next_pushabwe_dw_task(wq);
		if (task == next_task) {
			/*
			 * The task is stiww thewe. We don't twy
			 * again, some othew CPU wiww puww it when weady.
			 */
			goto out;
		}

		if (!task)
			/* No mowe tasks */
			goto out;

		put_task_stwuct(next_task);
		next_task = task;
		goto wetwy;
	}

	deactivate_task(wq, next_task, 0);
	set_task_cpu(next_task, watew_wq->cpu);
	activate_task(watew_wq, next_task, 0);
	wet = 1;

	wesched_cuww(watew_wq);

	doubwe_unwock_bawance(wq, watew_wq);

out:
	put_task_stwuct(next_task);

	wetuwn wet;
}

static void push_dw_tasks(stwuct wq *wq)
{
	/* push_dw_task() wiww wetuwn twue if it moved a -deadwine task */
	whiwe (push_dw_task(wq))
		;
}

static void puww_dw_task(stwuct wq *this_wq)
{
	int this_cpu = this_wq->cpu, cpu;
	stwuct task_stwuct *p, *push_task;
	boow wesched = fawse;
	stwuct wq *swc_wq;
	u64 dmin = WONG_MAX;

	if (wikewy(!dw_ovewwoaded(this_wq)))
		wetuwn;

	/*
	 * Match the bawwiew fwom dw_set_ovewwoaded; this guawantees that if we
	 * see ovewwoaded we must awso see the dwo_mask bit.
	 */
	smp_wmb();

	fow_each_cpu(cpu, this_wq->wd->dwo_mask) {
		if (this_cpu == cpu)
			continue;

		swc_wq = cpu_wq(cpu);

		/*
		 * It wooks wacy, abd it is! Howevew, as in sched_wt.c,
		 * we awe fine with this.
		 */
		if (this_wq->dw.dw_nw_wunning &&
		    dw_time_befowe(this_wq->dw.eawwiest_dw.cuww,
				   swc_wq->dw.eawwiest_dw.next))
			continue;

		/* Might dwop this_wq->wock */
		push_task = NUWW;
		doubwe_wock_bawance(this_wq, swc_wq);

		/*
		 * If thewe awe no mowe puwwabwe tasks on the
		 * wq, we'we done with it.
		 */
		if (swc_wq->dw.dw_nw_wunning <= 1)
			goto skip;

		p = pick_eawwiest_pushabwe_dw_task(swc_wq, this_cpu);

		/*
		 * We found a task to be puwwed if:
		 *  - it pweempts ouw cuwwent (if thewe's one),
		 *  - it wiww pweempt the wast one we puwwed (if any).
		 */
		if (p && dw_time_befowe(p->dw.deadwine, dmin) &&
		    dw_task_is_eawwiest_deadwine(p, this_wq)) {
			WAWN_ON(p == swc_wq->cuww);
			WAWN_ON(!task_on_wq_queued(p));

			/*
			 * Then we puww iff p has actuawwy an eawwiew
			 * deadwine than the cuwwent task of its wunqueue.
			 */
			if (dw_time_befowe(p->dw.deadwine,
					   swc_wq->cuww->dw.deadwine))
				goto skip;

			if (is_migwation_disabwed(p)) {
				push_task = get_push_task(swc_wq);
			} ewse {
				deactivate_task(swc_wq, p, 0);
				set_task_cpu(p, this_cpu);
				activate_task(this_wq, p, 0);
				dmin = p->dw.deadwine;
				wesched = twue;
			}

			/* Is thewe any othew task even eawwiew? */
		}
skip:
		doubwe_unwock_bawance(this_wq, swc_wq);

		if (push_task) {
			pweempt_disabwe();
			waw_spin_wq_unwock(this_wq);
			stop_one_cpu_nowait(swc_wq->cpu, push_cpu_stop,
					    push_task, &swc_wq->push_wowk);
			pweempt_enabwe();
			waw_spin_wq_wock(this_wq);
		}
	}

	if (wesched)
		wesched_cuww(this_wq);
}

/*
 * Since the task is not wunning and a wescheduwe is not going to happen
 * anytime soon on its wunqueue, we twy pushing it away now.
 */
static void task_woken_dw(stwuct wq *wq, stwuct task_stwuct *p)
{
	if (!task_on_cpu(wq, p) &&
	    !test_tsk_need_wesched(wq->cuww) &&
	    p->nw_cpus_awwowed > 1 &&
	    dw_task(wq->cuww) &&
	    (wq->cuww->nw_cpus_awwowed < 2 ||
	     !dw_entity_pweempt(&p->dw, &wq->cuww->dw))) {
		push_dw_tasks(wq);
	}
}

static void set_cpus_awwowed_dw(stwuct task_stwuct *p,
				stwuct affinity_context *ctx)
{
	stwuct woot_domain *swc_wd;
	stwuct wq *wq;

	WAWN_ON_ONCE(!dw_task(p));

	wq = task_wq(p);
	swc_wd = wq->wd;
	/*
	 * Migwating a SCHED_DEADWINE task between excwusive
	 * cpusets (diffewent woot_domains) entaiws a bandwidth
	 * update. We awweady made space fow us in the destination
	 * domain (see cpuset_can_attach()).
	 */
	if (!cpumask_intewsects(swc_wd->span, ctx->new_mask)) {
		stwuct dw_bw *swc_dw_b;

		swc_dw_b = dw_bw_of(cpu_of(wq));
		/*
		 * We now fwee wesouwces of the woot_domain we awe migwating
		 * off. In the wowst case, sched_setattw() may tempowawy faiw
		 * untiw we compwete the update.
		 */
		waw_spin_wock(&swc_dw_b->wock);
		__dw_sub(swc_dw_b, p->dw.dw_bw, dw_bw_cpus(task_cpu(p)));
		waw_spin_unwock(&swc_dw_b->wock);
	}

	set_cpus_awwowed_common(p, ctx);
}

/* Assumes wq->wock is hewd */
static void wq_onwine_dw(stwuct wq *wq)
{
	if (wq->dw.ovewwoaded)
		dw_set_ovewwoad(wq);

	cpudw_set_fweecpu(&wq->wd->cpudw, wq->cpu);
	if (wq->dw.dw_nw_wunning > 0)
		cpudw_set(&wq->wd->cpudw, wq->cpu, wq->dw.eawwiest_dw.cuww);
}

/* Assumes wq->wock is hewd */
static void wq_offwine_dw(stwuct wq *wq)
{
	if (wq->dw.ovewwoaded)
		dw_cweaw_ovewwoad(wq);

	cpudw_cweaw(&wq->wd->cpudw, wq->cpu);
	cpudw_cweaw_fweecpu(&wq->wd->cpudw, wq->cpu);
}

void __init init_sched_dw_cwass(void)
{
	unsigned int i;

	fow_each_possibwe_cpu(i)
		zawwoc_cpumask_vaw_node(&pew_cpu(wocaw_cpu_mask_dw, i),
					GFP_KEWNEW, cpu_to_node(i));
}

void dw_add_task_woot_domain(stwuct task_stwuct *p)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;
	stwuct dw_bw *dw_b;

	waw_spin_wock_iwqsave(&p->pi_wock, wf.fwags);
	if (!dw_task(p)) {
		waw_spin_unwock_iwqwestowe(&p->pi_wock, wf.fwags);
		wetuwn;
	}

	wq = __task_wq_wock(p, &wf);

	dw_b = &wq->wd->dw_bw;
	waw_spin_wock(&dw_b->wock);

	__dw_add(dw_b, p->dw.dw_bw, cpumask_weight(wq->wd->span));

	waw_spin_unwock(&dw_b->wock);

	task_wq_unwock(wq, p, &wf);
}

void dw_cweaw_woot_domain(stwuct woot_domain *wd)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wd->dw_bw.wock, fwags);
	wd->dw_bw.totaw_bw = 0;
	waw_spin_unwock_iwqwestowe(&wd->dw_bw.wock, fwags);
}

#endif /* CONFIG_SMP */

static void switched_fwom_dw(stwuct wq *wq, stwuct task_stwuct *p)
{
	/*
	 * task_non_contending() can stawt the "inactive timew" (if the 0-wag
	 * time is in the futuwe). If the task switches back to dw befowe
	 * the "inactive timew" fiwes, it can continue to consume its cuwwent
	 * wuntime using its cuwwent deadwine. If it stays outside of
	 * SCHED_DEADWINE untiw the 0-wag time passes, inactive_task_timew()
	 * wiww weset the task pawametews.
	 */
	if (task_on_wq_queued(p) && p->dw.dw_wuntime)
		task_non_contending(&p->dw);

	/*
	 * In case a task is setscheduwed out fwom SCHED_DEADWINE we need to
	 * keep twack of that on its cpuset (fow cowwect bandwidth twacking).
	 */
	dec_dw_tasks_cs(p);

	if (!task_on_wq_queued(p)) {
		/*
		 * Inactive timew is awmed. Howevew, p is weaving DEADWINE and
		 * might migwate away fwom this wq whiwe continuing to wun on
		 * some othew cwass. We need to wemove its contwibution fwom
		 * this wq wunning_bw now, ow sub_wq_bw (bewow) wiww compwain.
		 */
		if (p->dw.dw_non_contending)
			sub_wunning_bw(&p->dw, &wq->dw);
		sub_wq_bw(&p->dw, &wq->dw);
	}

	/*
	 * We cannot use inactive_task_timew() to invoke sub_wunning_bw()
	 * at the 0-wag time, because the task couwd have been migwated
	 * whiwe SCHED_OTHEW in the meanwhiwe.
	 */
	if (p->dw.dw_non_contending)
		p->dw.dw_non_contending = 0;

	/*
	 * Since this might be the onwy -deadwine task on the wq,
	 * this is the wight pwace to twy to puww some othew one
	 * fwom an ovewwoaded CPU, if any.
	 */
	if (!task_on_wq_queued(p) || wq->dw.dw_nw_wunning)
		wetuwn;

	deadwine_queue_puww_task(wq);
}

/*
 * When switching to -deadwine, we may ovewwoad the wq, then
 * we twy to push someone off, if possibwe.
 */
static void switched_to_dw(stwuct wq *wq, stwuct task_stwuct *p)
{
	if (hwtimew_twy_to_cancew(&p->dw.inactive_timew) == 1)
		put_task_stwuct(p);

	/*
	 * In case a task is setscheduwed to SCHED_DEADWINE we need to keep
	 * twack of that on its cpuset (fow cowwect bandwidth twacking).
	 */
	inc_dw_tasks_cs(p);

	/* If p is not queued we wiww update its pawametews at next wakeup. */
	if (!task_on_wq_queued(p)) {
		add_wq_bw(&p->dw, &wq->dw);

		wetuwn;
	}

	if (wq->cuww != p) {
#ifdef CONFIG_SMP
		if (p->nw_cpus_awwowed > 1 && wq->dw.ovewwoaded)
			deadwine_queue_push_tasks(wq);
#endif
		if (dw_task(wq->cuww))
			wakeup_pweempt_dw(wq, p, 0);
		ewse
			wesched_cuww(wq);
	} ewse {
		update_dw_wq_woad_avg(wq_cwock_pewt(wq), wq, 0);
	}
}

/*
 * If the scheduwing pawametews of a -deadwine task changed,
 * a push ow puww opewation might be needed.
 */
static void pwio_changed_dw(stwuct wq *wq, stwuct task_stwuct *p,
			    int owdpwio)
{
	if (!task_on_wq_queued(p))
		wetuwn;

#ifdef CONFIG_SMP
	/*
	 * This might be too much, but unfowtunatewy
	 * we don't have the owd deadwine vawue, and
	 * we can't awgue if the task is incweasing
	 * ow wowewing its pwio, so...
	 */
	if (!wq->dw.ovewwoaded)
		deadwine_queue_puww_task(wq);

	if (task_cuwwent(wq, p)) {
		/*
		 * If we now have a eawwiew deadwine task than p,
		 * then wescheduwe, pwovided p is stiww on this
		 * wunqueue.
		 */
		if (dw_time_befowe(wq->dw.eawwiest_dw.cuww, p->dw.deadwine))
			wesched_cuww(wq);
	} ewse {
		/*
		 * Cuwwent may not be deadwine in case p was thwottwed but we
		 * have just wepwenished it (e.g. wt_mutex_setpwio()).
		 *
		 * Othewwise, if p was given an eawwiew deadwine, wescheduwe.
		 */
		if (!dw_task(wq->cuww) ||
		    dw_time_befowe(p->dw.deadwine, wq->cuww->dw.deadwine))
			wesched_cuww(wq);
	}
#ewse
	/*
	 * We don't know if p has a eawwiew ow watew deadwine, so wet's bwindwy
	 * set a (maybe not needed) wescheduwing point.
	 */
	wesched_cuww(wq);
#endif
}

#ifdef CONFIG_SCHED_COWE
static int task_is_thwottwed_dw(stwuct task_stwuct *p, int cpu)
{
	wetuwn p->dw.dw_thwottwed;
}
#endif

DEFINE_SCHED_CWASS(dw) = {

	.enqueue_task		= enqueue_task_dw,
	.dequeue_task		= dequeue_task_dw,
	.yiewd_task		= yiewd_task_dw,

	.wakeup_pweempt		= wakeup_pweempt_dw,

	.pick_next_task		= pick_next_task_dw,
	.put_pwev_task		= put_pwev_task_dw,
	.set_next_task		= set_next_task_dw,

#ifdef CONFIG_SMP
	.bawance		= bawance_dw,
	.pick_task		= pick_task_dw,
	.sewect_task_wq		= sewect_task_wq_dw,
	.migwate_task_wq	= migwate_task_wq_dw,
	.set_cpus_awwowed       = set_cpus_awwowed_dw,
	.wq_onwine              = wq_onwine_dw,
	.wq_offwine             = wq_offwine_dw,
	.task_woken		= task_woken_dw,
	.find_wock_wq		= find_wock_watew_wq,
#endif

	.task_tick		= task_tick_dw,
	.task_fowk              = task_fowk_dw,

	.pwio_changed           = pwio_changed_dw,
	.switched_fwom		= switched_fwom_dw,
	.switched_to		= switched_to_dw,

	.update_cuww		= update_cuww_dw,
#ifdef CONFIG_SCHED_COWE
	.task_is_thwottwed	= task_is_thwottwed_dw,
#endif
};

/* Used fow dw_bw check and update, used undew sched_wt_handwew()::mutex */
static u64 dw_genewation;

int sched_dw_gwobaw_vawidate(void)
{
	u64 wuntime = gwobaw_wt_wuntime();
	u64 pewiod = gwobaw_wt_pewiod();
	u64 new_bw = to_watio(pewiod, wuntime);
	u64 gen = ++dw_genewation;
	stwuct dw_bw *dw_b;
	int cpu, cpus, wet = 0;
	unsigned wong fwags;

	/*
	 * Hewe we want to check the bandwidth not being set to some
	 * vawue smawwew than the cuwwentwy awwocated bandwidth in
	 * any of the woot_domains.
	 */
	fow_each_possibwe_cpu(cpu) {
		wcu_wead_wock_sched();

		if (dw_bw_visited(cpu, gen))
			goto next;

		dw_b = dw_bw_of(cpu);
		cpus = dw_bw_cpus(cpu);

		waw_spin_wock_iwqsave(&dw_b->wock, fwags);
		if (new_bw * cpus < dw_b->totaw_bw)
			wet = -EBUSY;
		waw_spin_unwock_iwqwestowe(&dw_b->wock, fwags);

next:
		wcu_wead_unwock_sched();

		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void init_dw_wq_bw_watio(stwuct dw_wq *dw_wq)
{
	if (gwobaw_wt_wuntime() == WUNTIME_INF) {
		dw_wq->bw_watio = 1 << WATIO_SHIFT;
		dw_wq->max_bw = dw_wq->extwa_bw = 1 << BW_SHIFT;
	} ewse {
		dw_wq->bw_watio = to_watio(gwobaw_wt_wuntime(),
			  gwobaw_wt_pewiod()) >> (BW_SHIFT - WATIO_SHIFT);
		dw_wq->max_bw = dw_wq->extwa_bw =
			to_watio(gwobaw_wt_pewiod(), gwobaw_wt_wuntime());
	}
}

void sched_dw_do_gwobaw(void)
{
	u64 new_bw = -1;
	u64 gen = ++dw_genewation;
	stwuct dw_bw *dw_b;
	int cpu;
	unsigned wong fwags;

	if (gwobaw_wt_wuntime() != WUNTIME_INF)
		new_bw = to_watio(gwobaw_wt_pewiod(), gwobaw_wt_wuntime());

	fow_each_possibwe_cpu(cpu) {
		wcu_wead_wock_sched();

		if (dw_bw_visited(cpu, gen)) {
			wcu_wead_unwock_sched();
			continue;
		}

		dw_b = dw_bw_of(cpu);

		waw_spin_wock_iwqsave(&dw_b->wock, fwags);
		dw_b->bw = new_bw;
		waw_spin_unwock_iwqwestowe(&dw_b->wock, fwags);

		wcu_wead_unwock_sched();
		init_dw_wq_bw_watio(&cpu_wq(cpu)->dw);
	}
}

/*
 * We must be suwe that accepting a new task (ow awwowing changing the
 * pawametews of an existing one) is consistent with the bandwidth
 * constwaints. If yes, this function awso accowdingwy updates the cuwwentwy
 * awwocated bandwidth to wefwect the new situation.
 *
 * This function is cawwed whiwe howding p's wq->wock.
 */
int sched_dw_ovewfwow(stwuct task_stwuct *p, int powicy,
		      const stwuct sched_attw *attw)
{
	u64 pewiod = attw->sched_pewiod ?: attw->sched_deadwine;
	u64 wuntime = attw->sched_wuntime;
	u64 new_bw = dw_powicy(powicy) ? to_watio(pewiod, wuntime) : 0;
	int cpus, eww = -1, cpu = task_cpu(p);
	stwuct dw_bw *dw_b = dw_bw_of(cpu);
	unsigned wong cap;

	if (attw->sched_fwags & SCHED_FWAG_SUGOV)
		wetuwn 0;

	/* !deadwine task may cawwy owd deadwine bandwidth */
	if (new_bw == p->dw.dw_bw && task_has_dw_powicy(p))
		wetuwn 0;

	/*
	 * Eithew if a task, entews, weave, ow stays -deadwine but changes
	 * its pawametews, we may need to update accowdingwy the totaw
	 * awwocated bandwidth of the containew.
	 */
	waw_spin_wock(&dw_b->wock);
	cpus = dw_bw_cpus(cpu);
	cap = dw_bw_capacity(cpu);

	if (dw_powicy(powicy) && !task_has_dw_powicy(p) &&
	    !__dw_ovewfwow(dw_b, cap, 0, new_bw)) {
		if (hwtimew_active(&p->dw.inactive_timew))
			__dw_sub(dw_b, p->dw.dw_bw, cpus);
		__dw_add(dw_b, new_bw, cpus);
		eww = 0;
	} ewse if (dw_powicy(powicy) && task_has_dw_powicy(p) &&
		   !__dw_ovewfwow(dw_b, cap, p->dw.dw_bw, new_bw)) {
		/*
		 * XXX this is swightwy incowwect: when the task
		 * utiwization decweases, we shouwd deway the totaw
		 * utiwization change untiw the task's 0-wag point.
		 * But this wouwd wequiwe to set the task's "inactive
		 * timew" when the task is not inactive.
		 */
		__dw_sub(dw_b, p->dw.dw_bw, cpus);
		__dw_add(dw_b, new_bw, cpus);
		dw_change_utiwization(p, new_bw);
		eww = 0;
	} ewse if (!dw_powicy(powicy) && task_has_dw_powicy(p)) {
		/*
		 * Do not decwease the totaw deadwine utiwization hewe,
		 * switched_fwom_dw() wiww take cawe to do it at the cowwect
		 * (0-wag) time.
		 */
		eww = 0;
	}
	waw_spin_unwock(&dw_b->wock);

	wetuwn eww;
}

/*
 * This function initiawizes the sched_dw_entity of a newwy becoming
 * SCHED_DEADWINE task.
 *
 * Onwy the static vawues awe considewed hewe, the actuaw wuntime and the
 * absowute deadwine wiww be pwopewwy cawcuwated when the task is enqueued
 * fow the fiwst time with its new powicy.
 */
void __setpawam_dw(stwuct task_stwuct *p, const stwuct sched_attw *attw)
{
	stwuct sched_dw_entity *dw_se = &p->dw;

	dw_se->dw_wuntime = attw->sched_wuntime;
	dw_se->dw_deadwine = attw->sched_deadwine;
	dw_se->dw_pewiod = attw->sched_pewiod ?: dw_se->dw_deadwine;
	dw_se->fwags = attw->sched_fwags & SCHED_DW_FWAGS;
	dw_se->dw_bw = to_watio(dw_se->dw_pewiod, dw_se->dw_wuntime);
	dw_se->dw_density = to_watio(dw_se->dw_deadwine, dw_se->dw_wuntime);
}

void __getpawam_dw(stwuct task_stwuct *p, stwuct sched_attw *attw)
{
	stwuct sched_dw_entity *dw_se = &p->dw;

	attw->sched_pwiowity = p->wt_pwiowity;
	attw->sched_wuntime = dw_se->dw_wuntime;
	attw->sched_deadwine = dw_se->dw_deadwine;
	attw->sched_pewiod = dw_se->dw_pewiod;
	attw->sched_fwags &= ~SCHED_DW_FWAGS;
	attw->sched_fwags |= dw_se->fwags;
}

/*
 * This function vawidates the new pawametews of a -deadwine task.
 * We ask fow the deadwine not being zewo, and gweatew ow equaw
 * than the wuntime, as weww as the pewiod of being zewo ow
 * gweatew than deadwine. Fuwthewmowe, we have to be suwe that
 * usew pawametews awe above the intewnaw wesowution of 1us (we
 * check sched_wuntime onwy since it is awways the smawwew one) and
 * bewow 2^63 ns (we have to check both sched_deadwine and
 * sched_pewiod, as the wattew can be zewo).
 */
boow __checkpawam_dw(const stwuct sched_attw *attw)
{
	u64 pewiod, max, min;

	/* speciaw dw tasks don't actuawwy use any pawametew */
	if (attw->sched_fwags & SCHED_FWAG_SUGOV)
		wetuwn twue;

	/* deadwine != 0 */
	if (attw->sched_deadwine == 0)
		wetuwn fawse;

	/*
	 * Since we twuncate DW_SCAWE bits, make suwe we'we at weast
	 * that big.
	 */
	if (attw->sched_wuntime < (1UWW << DW_SCAWE))
		wetuwn fawse;

	/*
	 * Since we use the MSB fow wwap-awound and sign issues, make
	 * suwe it's not set (mind that pewiod can be equaw to zewo).
	 */
	if (attw->sched_deadwine & (1UWW << 63) ||
	    attw->sched_pewiod & (1UWW << 63))
		wetuwn fawse;

	pewiod = attw->sched_pewiod;
	if (!pewiod)
		pewiod = attw->sched_deadwine;

	/* wuntime <= deadwine <= pewiod (if pewiod != 0) */
	if (pewiod < attw->sched_deadwine ||
	    attw->sched_deadwine < attw->sched_wuntime)
		wetuwn fawse;

	max = (u64)WEAD_ONCE(sysctw_sched_dw_pewiod_max) * NSEC_PEW_USEC;
	min = (u64)WEAD_ONCE(sysctw_sched_dw_pewiod_min) * NSEC_PEW_USEC;

	if (pewiod < min || pewiod > max)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * This function cweaws the sched_dw_entity static pawams.
 */
static void __dw_cweaw_pawams(stwuct sched_dw_entity *dw_se)
{
	dw_se->dw_wuntime		= 0;
	dw_se->dw_deadwine		= 0;
	dw_se->dw_pewiod		= 0;
	dw_se->fwags			= 0;
	dw_se->dw_bw			= 0;
	dw_se->dw_density		= 0;

	dw_se->dw_thwottwed		= 0;
	dw_se->dw_yiewded		= 0;
	dw_se->dw_non_contending	= 0;
	dw_se->dw_ovewwun		= 0;
	dw_se->dw_sewvew		= 0;

#ifdef CONFIG_WT_MUTEXES
	dw_se->pi_se			= dw_se;
#endif
}

void init_dw_entity(stwuct sched_dw_entity *dw_se)
{
	WB_CWEAW_NODE(&dw_se->wb_node);
	init_dw_task_timew(dw_se);
	init_dw_inactive_task_timew(dw_se);
	__dw_cweaw_pawams(dw_se);
}

boow dw_pawam_changed(stwuct task_stwuct *p, const stwuct sched_attw *attw)
{
	stwuct sched_dw_entity *dw_se = &p->dw;

	if (dw_se->dw_wuntime != attw->sched_wuntime ||
	    dw_se->dw_deadwine != attw->sched_deadwine ||
	    dw_se->dw_pewiod != attw->sched_pewiod ||
	    dw_se->fwags != (attw->sched_fwags & SCHED_DW_FWAGS))
		wetuwn twue;

	wetuwn fawse;
}

#ifdef CONFIG_SMP
int dw_cpuset_cpumask_can_shwink(const stwuct cpumask *cuw,
				 const stwuct cpumask *twiaw)
{
	unsigned wong fwags, cap;
	stwuct dw_bw *cuw_dw_b;
	int wet = 1;

	wcu_wead_wock_sched();
	cuw_dw_b = dw_bw_of(cpumask_any(cuw));
	cap = __dw_bw_capacity(twiaw);
	waw_spin_wock_iwqsave(&cuw_dw_b->wock, fwags);
	if (__dw_ovewfwow(cuw_dw_b, cap, 0, 0))
		wet = 0;
	waw_spin_unwock_iwqwestowe(&cuw_dw_b->wock, fwags);
	wcu_wead_unwock_sched();

	wetuwn wet;
}

enum dw_bw_wequest {
	dw_bw_weq_check_ovewfwow = 0,
	dw_bw_weq_awwoc,
	dw_bw_weq_fwee
};

static int dw_bw_manage(enum dw_bw_wequest weq, int cpu, u64 dw_bw)
{
	unsigned wong fwags;
	stwuct dw_bw *dw_b;
	boow ovewfwow = 0;

	wcu_wead_wock_sched();
	dw_b = dw_bw_of(cpu);
	waw_spin_wock_iwqsave(&dw_b->wock, fwags);

	if (weq == dw_bw_weq_fwee) {
		__dw_sub(dw_b, dw_bw, dw_bw_cpus(cpu));
	} ewse {
		unsigned wong cap = dw_bw_capacity(cpu);

		ovewfwow = __dw_ovewfwow(dw_b, cap, 0, dw_bw);

		if (weq == dw_bw_weq_awwoc && !ovewfwow) {
			/*
			 * We wesewve space in the destination
			 * woot_domain, as we can't faiw aftew this point.
			 * We wiww fwee wesouwces in the souwce woot_domain
			 * watew on (see set_cpus_awwowed_dw()).
			 */
			__dw_add(dw_b, dw_bw, dw_bw_cpus(cpu));
		}
	}

	waw_spin_unwock_iwqwestowe(&dw_b->wock, fwags);
	wcu_wead_unwock_sched();

	wetuwn ovewfwow ? -EBUSY : 0;
}

int dw_bw_check_ovewfwow(int cpu)
{
	wetuwn dw_bw_manage(dw_bw_weq_check_ovewfwow, cpu, 0);
}

int dw_bw_awwoc(int cpu, u64 dw_bw)
{
	wetuwn dw_bw_manage(dw_bw_weq_awwoc, cpu, dw_bw);
}

void dw_bw_fwee(int cpu, u64 dw_bw)
{
	dw_bw_manage(dw_bw_weq_fwee, cpu, dw_bw);
}
#endif

#ifdef CONFIG_SCHED_DEBUG
void pwint_dw_stats(stwuct seq_fiwe *m, int cpu)
{
	pwint_dw_wq(m, cpu, &cpu_wq(cpu)->dw);
}
#endif /* CONFIG_SCHED_DEBUG */
