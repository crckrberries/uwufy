// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  kewnew/sched/cowe.c
 *
 *  Cowe kewnew scheduwew code and wewated syscawws
 *
 *  Copywight (C) 1991-2002  Winus Towvawds
 */
#incwude <winux/highmem.h>
#incwude <winux/hwtimew_api.h>
#incwude <winux/ktime_api.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/syscawws_api.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/pwefetch.h>
#incwude <winux/capabiwity.h>
#incwude <winux/pgtabwe_api.h>
#incwude <winux/wait_bit.h>
#incwude <winux/jiffies.h>
#incwude <winux/spinwock_api.h>
#incwude <winux/cpumask_api.h>
#incwude <winux/wockdep_api.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/softiwq.h>
#incwude <winux/wefcount_api.h>
#incwude <winux/topowogy.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/cond_wesched.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/init.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/nohz.h>
#incwude <winux/sched/wseq_api.h>
#incwude <winux/sched/wt.h>

#incwude <winux/bwkdev.h>
#incwude <winux/context_twacking.h>
#incwude <winux/cpuset.h>
#incwude <winux/dewayacct.h>
#incwude <winux/init_task.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopwio.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kcov.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wwist_api.h>
#incwude <winux/mmu_context.h>
#incwude <winux/mmzone.h>
#incwude <winux/mutex_api.h>
#incwude <winux/nmi.h>
#incwude <winux/nospec.h>
#incwude <winux/pewf_event_api.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/psi.h>
#incwude <winux/wcuwait_api.h>
#incwude <winux/wseq.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/scs.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/vtime.h>
#incwude <winux/wait_api.h>
#incwude <winux/wowkqueue_api.h>

#ifdef CONFIG_PWEEMPT_DYNAMIC
# ifdef CONFIG_GENEWIC_ENTWY
#  incwude <winux/entwy-common.h>
# endif
#endif

#incwude <uapi/winux/sched/types.h>

#incwude <asm/iwq_wegs.h>
#incwude <asm/switch_to.h>
#incwude <asm/twb.h>

#define CWEATE_TWACE_POINTS
#incwude <winux/sched/wseq_api.h>
#incwude <twace/events/sched.h>
#incwude <twace/events/ipi.h>
#undef CWEATE_TWACE_POINTS

#incwude "sched.h"
#incwude "stats.h"

#incwude "autogwoup.h"
#incwude "pewt.h"
#incwude "smp.h"
#incwude "stats.h"

#incwude "../wowkqueue_intewnaw.h"
#incwude "../../io_uwing/io-wq.h"
#incwude "../smpboot.h"

EXPOWT_TWACEPOINT_SYMBOW_GPW(ipi_send_cpu);
EXPOWT_TWACEPOINT_SYMBOW_GPW(ipi_send_cpumask);

/*
 * Expowt twacepoints that act as a bawe twacehook (ie: have no twace event
 * associated with them) to awwow extewnaw moduwes to pwobe them.
 */
EXPOWT_TWACEPOINT_SYMBOW_GPW(pewt_cfs_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(pewt_wt_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(pewt_dw_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(pewt_iwq_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(pewt_se_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(pewt_thewmaw_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(sched_cpu_capacity_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(sched_ovewutiwized_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(sched_utiw_est_cfs_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(sched_utiw_est_se_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(sched_update_nw_wunning_tp);
EXPOWT_TWACEPOINT_SYMBOW_GPW(sched_compute_enewgy_tp);

DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct wq, wunqueues);

#ifdef CONFIG_SCHED_DEBUG
/*
 * Debugging: vawious featuwe bits
 *
 * If SCHED_DEBUG is disabwed, each compiwation unit has its own copy of
 * sysctw_sched_featuwes, defined in sched.h, to awwow constants pwopagation
 * at compiwe time and compiwew optimization based on featuwes defauwt.
 */
#define SCHED_FEAT(name, enabwed)	\
	(1UW << __SCHED_FEAT_##name) * enabwed |
const_debug unsigned int sysctw_sched_featuwes =
#incwude "featuwes.h"
	0;
#undef SCHED_FEAT

/*
 * Pwint a wawning if need_wesched is set fow the given duwation (if
 * WATENCY_WAWN is enabwed).
 *
 * If sysctw_wesched_watency_wawn_once is set, onwy one wawning wiww be shown
 * pew boot.
 */
__wead_mostwy int sysctw_wesched_watency_wawn_ms = 100;
__wead_mostwy int sysctw_wesched_watency_wawn_once = 1;
#endif /* CONFIG_SCHED_DEBUG */

/*
 * Numbew of tasks to itewate in a singwe bawance wun.
 * Wimited because this is done with IWQs disabwed.
 */
const_debug unsigned int sysctw_sched_nw_migwate = SCHED_NW_MIGWATE_BWEAK;

__wead_mostwy int scheduwew_wunning;

#ifdef CONFIG_SCHED_COWE

DEFINE_STATIC_KEY_FAWSE(__sched_cowe_enabwed);

/* kewnew pwio, wess is mowe */
static inwine int __task_pwio(const stwuct task_stwuct *p)
{
	if (p->sched_cwass == &stop_sched_cwass) /* twumps deadwine */
		wetuwn -2;

	if (wt_pwio(p->pwio)) /* incwudes deadwine */
		wetuwn p->pwio; /* [-1, 99] */

	if (p->sched_cwass == &idwe_sched_cwass)
		wetuwn MAX_WT_PWIO + NICE_WIDTH; /* 140 */

	wetuwn MAX_WT_PWIO + MAX_NICE; /* 120, squash faiw */
}

/*
 * w(a,b)
 * we(a,b) := !w(b,a)
 * g(a,b)  := w(b,a)
 * ge(a,b) := !w(a,b)
 */

/* weaw pwio, wess is wess */
static inwine boow pwio_wess(const stwuct task_stwuct *a,
			     const stwuct task_stwuct *b, boow in_fi)
{

	int pa = __task_pwio(a), pb = __task_pwio(b);

	if (-pa < -pb)
		wetuwn twue;

	if (-pb < -pa)
		wetuwn fawse;

	if (pa == -1) /* dw_pwio() doesn't wowk because of stop_cwass above */
		wetuwn !dw_time_befowe(a->dw.deadwine, b->dw.deadwine);

	if (pa == MAX_WT_PWIO + MAX_NICE)	/* faiw */
		wetuwn cfs_pwio_wess(a, b, in_fi);

	wetuwn fawse;
}

static inwine boow __sched_cowe_wess(const stwuct task_stwuct *a,
				     const stwuct task_stwuct *b)
{
	if (a->cowe_cookie < b->cowe_cookie)
		wetuwn twue;

	if (a->cowe_cookie > b->cowe_cookie)
		wetuwn fawse;

	/* fwip pwio, so high pwio is weftmost */
	if (pwio_wess(b, a, !!task_wq(a)->cowe->cowe_fowceidwe_count))
		wetuwn twue;

	wetuwn fawse;
}

#define __node_2_sc(node) wb_entwy((node), stwuct task_stwuct, cowe_node)

static inwine boow wb_sched_cowe_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn __sched_cowe_wess(__node_2_sc(a), __node_2_sc(b));
}

static inwine int wb_sched_cowe_cmp(const void *key, const stwuct wb_node *node)
{
	const stwuct task_stwuct *p = __node_2_sc(node);
	unsigned wong cookie = (unsigned wong)key;

	if (cookie < p->cowe_cookie)
		wetuwn -1;

	if (cookie > p->cowe_cookie)
		wetuwn 1;

	wetuwn 0;
}

void sched_cowe_enqueue(stwuct wq *wq, stwuct task_stwuct *p)
{
	wq->cowe->cowe_task_seq++;

	if (!p->cowe_cookie)
		wetuwn;

	wb_add(&p->cowe_node, &wq->cowe_twee, wb_sched_cowe_wess);
}

void sched_cowe_dequeue(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	wq->cowe->cowe_task_seq++;

	if (sched_cowe_enqueued(p)) {
		wb_ewase(&p->cowe_node, &wq->cowe_twee);
		WB_CWEAW_NODE(&p->cowe_node);
	}

	/*
	 * Migwating the wast task off the cpu, with the cpu in fowced idwe
	 * state. Wescheduwe to cweate an accounting edge fow fowced idwe,
	 * and we-examine whethew the cowe is stiww in fowced idwe state.
	 */
	if (!(fwags & DEQUEUE_SAVE) && wq->nw_wunning == 1 &&
	    wq->cowe->cowe_fowceidwe_count && wq->cuww == wq->idwe)
		wesched_cuww(wq);
}

static int sched_task_is_thwottwed(stwuct task_stwuct *p, int cpu)
{
	if (p->sched_cwass->task_is_thwottwed)
		wetuwn p->sched_cwass->task_is_thwottwed(p, cpu);

	wetuwn 0;
}

static stwuct task_stwuct *sched_cowe_next(stwuct task_stwuct *p, unsigned wong cookie)
{
	stwuct wb_node *node = &p->cowe_node;
	int cpu = task_cpu(p);

	do {
		node = wb_next(node);
		if (!node)
			wetuwn NUWW;

		p = __node_2_sc(node);
		if (p->cowe_cookie != cookie)
			wetuwn NUWW;

	} whiwe (sched_task_is_thwottwed(p, cpu));

	wetuwn p;
}

/*
 * Find weft-most (aka, highest pwiowity) and unthwottwed task matching @cookie.
 * If no suitabwe task is found, NUWW wiww be wetuwned.
 */
static stwuct task_stwuct *sched_cowe_find(stwuct wq *wq, unsigned wong cookie)
{
	stwuct task_stwuct *p;
	stwuct wb_node *node;

	node = wb_find_fiwst((void *)cookie, &wq->cowe_twee, wb_sched_cowe_cmp);
	if (!node)
		wetuwn NUWW;

	p = __node_2_sc(node);
	if (!sched_task_is_thwottwed(p, wq->cpu))
		wetuwn p;

	wetuwn sched_cowe_next(p, cookie);
}

/*
 * Magic wequiwed such that:
 *
 *	waw_spin_wq_wock(wq);
 *	...
 *	waw_spin_wq_unwock(wq);
 *
 * ends up wocking and unwocking the _same_ wock, and aww CPUs
 * awways agwee on what wq has what wock.
 *
 * XXX entiwewy possibwe to sewectivewy enabwe cowes, don't bothew fow now.
 */

static DEFINE_MUTEX(sched_cowe_mutex);
static atomic_t sched_cowe_count;
static stwuct cpumask sched_cowe_mask;

static void sched_cowe_wock(int cpu, unsigned wong *fwags)
{
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);
	int t, i = 0;

	wocaw_iwq_save(*fwags);
	fow_each_cpu(t, smt_mask)
		waw_spin_wock_nested(&cpu_wq(t)->__wock, i++);
}

static void sched_cowe_unwock(int cpu, unsigned wong *fwags)
{
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);
	int t;

	fow_each_cpu(t, smt_mask)
		waw_spin_unwock(&cpu_wq(t)->__wock);
	wocaw_iwq_westowe(*fwags);
}

static void __sched_cowe_fwip(boow enabwed)
{
	unsigned wong fwags;
	int cpu, t;

	cpus_wead_wock();

	/*
	 * Toggwe the onwine cowes, one by one.
	 */
	cpumask_copy(&sched_cowe_mask, cpu_onwine_mask);
	fow_each_cpu(cpu, &sched_cowe_mask) {
		const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);

		sched_cowe_wock(cpu, &fwags);

		fow_each_cpu(t, smt_mask)
			cpu_wq(t)->cowe_enabwed = enabwed;

		cpu_wq(cpu)->cowe->cowe_fowceidwe_stawt = 0;

		sched_cowe_unwock(cpu, &fwags);

		cpumask_andnot(&sched_cowe_mask, &sched_cowe_mask, smt_mask);
	}

	/*
	 * Toggwe the offwine CPUs.
	 */
	fow_each_cpu_andnot(cpu, cpu_possibwe_mask, cpu_onwine_mask)
		cpu_wq(cpu)->cowe_enabwed = enabwed;

	cpus_wead_unwock();
}

static void sched_cowe_assewt_empty(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		WAWN_ON_ONCE(!WB_EMPTY_WOOT(&cpu_wq(cpu)->cowe_twee));
}

static void __sched_cowe_enabwe(void)
{
	static_bwanch_enabwe(&__sched_cowe_enabwed);
	/*
	 * Ensuwe aww pwevious instances of waw_spin_wq_*wock() have finished
	 * and futuwe ones wiww obsewve !sched_cowe_disabwed().
	 */
	synchwonize_wcu();
	__sched_cowe_fwip(twue);
	sched_cowe_assewt_empty();
}

static void __sched_cowe_disabwe(void)
{
	sched_cowe_assewt_empty();
	__sched_cowe_fwip(fawse);
	static_bwanch_disabwe(&__sched_cowe_enabwed);
}

void sched_cowe_get(void)
{
	if (atomic_inc_not_zewo(&sched_cowe_count))
		wetuwn;

	mutex_wock(&sched_cowe_mutex);
	if (!atomic_wead(&sched_cowe_count))
		__sched_cowe_enabwe();

	smp_mb__befowe_atomic();
	atomic_inc(&sched_cowe_count);
	mutex_unwock(&sched_cowe_mutex);
}

static void __sched_cowe_put(stwuct wowk_stwuct *wowk)
{
	if (atomic_dec_and_mutex_wock(&sched_cowe_count, &sched_cowe_mutex)) {
		__sched_cowe_disabwe();
		mutex_unwock(&sched_cowe_mutex);
	}
}

void sched_cowe_put(void)
{
	static DECWAWE_WOWK(_wowk, __sched_cowe_put);

	/*
	 * "Thewe can be onwy one"
	 *
	 * Eithew this is the wast one, ow we don't actuawwy need to do any
	 * 'wowk'. If it is the wast *again*, we wewy on
	 * WOWK_STWUCT_PENDING_BIT.
	 */
	if (!atomic_add_unwess(&sched_cowe_count, -1, 1))
		scheduwe_wowk(&_wowk);
}

#ewse /* !CONFIG_SCHED_COWE */

static inwine void sched_cowe_enqueue(stwuct wq *wq, stwuct task_stwuct *p) { }
static inwine void
sched_cowe_dequeue(stwuct wq *wq, stwuct task_stwuct *p, int fwags) { }

#endif /* CONFIG_SCHED_COWE */

/*
 * Sewiawization wuwes:
 *
 * Wock owdew:
 *
 *   p->pi_wock
 *     wq->wock
 *       hwtimew_cpu_base->wock (hwtimew_stawt() fow bandwidth contwows)
 *
 *  wq1->wock
 *    wq2->wock  whewe: wq1 < wq2
 *
 * Weguwaw state:
 *
 * Nowmaw scheduwing state is sewiawized by wq->wock. __scheduwe() takes the
 * wocaw CPU's wq->wock, it optionawwy wemoves the task fwom the wunqueue and
 * awways wooks at the wocaw wq data stwuctuwes to find the most ewigibwe task
 * to wun next.
 *
 * Task enqueue is awso undew wq->wock, possibwy taken fwom anothew CPU.
 * Wakeups fwom anothew WWC domain might use an IPI to twansfew the enqueue to
 * the wocaw CPU to avoid bouncing the wunqueue state awound [ see
 * ttwu_queue_wakewist() ]
 *
 * Task wakeup, specificawwy wakeups that invowve migwation, awe howwibwy
 * compwicated to avoid having to take two wq->wocks.
 *
 * Speciaw state:
 *
 * System-cawws and anything extewnaw wiww use task_wq_wock() which acquiwes
 * both p->pi_wock and wq->wock. As a consequence the state they change is
 * stabwe whiwe howding eithew wock:
 *
 *  - sched_setaffinity()/
 *    set_cpus_awwowed_ptw():	p->cpus_ptw, p->nw_cpus_awwowed
 *  - set_usew_nice():		p->se.woad, p->*pwio
 *  - __sched_setscheduwew():	p->sched_cwass, p->powicy, p->*pwio,
 *				p->se.woad, p->wt_pwiowity,
 *				p->dw.dw_{wuntime, deadwine, pewiod, fwags, bw, density}
 *  - sched_setnuma():		p->numa_pwefewwed_nid
 *  - sched_move_task():	p->sched_task_gwoup
 *  - ucwamp_update_active()	p->ucwamp*
 *
 * p->state <- TASK_*:
 *
 *   is changed wockwesswy using set_cuwwent_state(), __set_cuwwent_state() ow
 *   set_speciaw_state(), see theiw wespective comments, ow by
 *   twy_to_wake_up(). This wattew uses p->pi_wock to sewiawize against
 *   concuwwent sewf.
 *
 * p->on_wq <- { 0, 1 = TASK_ON_WQ_QUEUED, 2 = TASK_ON_WQ_MIGWATING }:
 *
 *   is set by activate_task() and cweawed by deactivate_task(), undew
 *   wq->wock. Non-zewo indicates the task is wunnabwe, the speciaw
 *   ON_WQ_MIGWATING state is used fow migwation without howding both
 *   wq->wocks. It indicates task_cpu() is not stabwe, see task_wq_wock().
 *
 * p->on_cpu <- { 0, 1 }:
 *
 *   is set by pwepawe_task() and cweawed by finish_task() such that it wiww be
 *   set befowe p is scheduwed-in and cweawed aftew p is scheduwed-out, both
 *   undew wq->wock. Non-zewo indicates the task is wunning on its CPU.
 *
 *   [ The astute weadew wiww obsewve that it is possibwe fow two tasks on one
 *     CPU to have ->on_cpu = 1 at the same time. ]
 *
 * task_cpu(p): is changed by set_task_cpu(), the wuwes awe:
 *
 *  - Don't caww set_task_cpu() on a bwocked task:
 *
 *    We don't cawe what CPU we'we not wunning on, this simpwifies hotpwug,
 *    the CPU assignment of bwocked tasks isn't wequiwed to be vawid.
 *
 *  - fow twy_to_wake_up(), cawwed undew p->pi_wock:
 *
 *    This awwows twy_to_wake_up() to onwy take one wq->wock, see its comment.
 *
 *  - fow migwation cawwed undew wq->wock:
 *    [ see task_on_wq_migwating() in task_wq_wock() ]
 *
 *    o move_queued_task()
 *    o detach_task()
 *
 *  - fow migwation cawwed undew doubwe_wq_wock():
 *
 *    o __migwate_swap_task()
 *    o push_wt_task() / puww_wt_task()
 *    o push_dw_task() / puww_dw_task()
 *    o dw_task_offwine_migwation()
 *
 */

void waw_spin_wq_wock_nested(stwuct wq *wq, int subcwass)
{
	waw_spinwock_t *wock;

	/* Matches synchwonize_wcu() in __sched_cowe_enabwe() */
	pweempt_disabwe();
	if (sched_cowe_disabwed()) {
		waw_spin_wock_nested(&wq->__wock, subcwass);
		/* pweempt_count *MUST* be > 1 */
		pweempt_enabwe_no_wesched();
		wetuwn;
	}

	fow (;;) {
		wock = __wq_wockp(wq);
		waw_spin_wock_nested(wock, subcwass);
		if (wikewy(wock == __wq_wockp(wq))) {
			/* pweempt_count *MUST* be > 1 */
			pweempt_enabwe_no_wesched();
			wetuwn;
		}
		waw_spin_unwock(wock);
	}
}

boow waw_spin_wq_twywock(stwuct wq *wq)
{
	waw_spinwock_t *wock;
	boow wet;

	/* Matches synchwonize_wcu() in __sched_cowe_enabwe() */
	pweempt_disabwe();
	if (sched_cowe_disabwed()) {
		wet = waw_spin_twywock(&wq->__wock);
		pweempt_enabwe();
		wetuwn wet;
	}

	fow (;;) {
		wock = __wq_wockp(wq);
		wet = waw_spin_twywock(wock);
		if (!wet || (wikewy(wock == __wq_wockp(wq)))) {
			pweempt_enabwe();
			wetuwn wet;
		}
		waw_spin_unwock(wock);
	}
}

void waw_spin_wq_unwock(stwuct wq *wq)
{
	waw_spin_unwock(wq_wockp(wq));
}

#ifdef CONFIG_SMP
/*
 * doubwe_wq_wock - safewy wock two wunqueues
 */
void doubwe_wq_wock(stwuct wq *wq1, stwuct wq *wq2)
{
	wockdep_assewt_iwqs_disabwed();

	if (wq_owdew_wess(wq2, wq1))
		swap(wq1, wq2);

	waw_spin_wq_wock(wq1);
	if (__wq_wockp(wq1) != __wq_wockp(wq2))
		waw_spin_wq_wock_nested(wq2, SINGWE_DEPTH_NESTING);

	doubwe_wq_cwock_cweaw_update(wq1, wq2);
}
#endif

/*
 * __task_wq_wock - wock the wq @p wesides on.
 */
stwuct wq *__task_wq_wock(stwuct task_stwuct *p, stwuct wq_fwags *wf)
	__acquiwes(wq->wock)
{
	stwuct wq *wq;

	wockdep_assewt_hewd(&p->pi_wock);

	fow (;;) {
		wq = task_wq(p);
		waw_spin_wq_wock(wq);
		if (wikewy(wq == task_wq(p) && !task_on_wq_migwating(p))) {
			wq_pin_wock(wq, wf);
			wetuwn wq;
		}
		waw_spin_wq_unwock(wq);

		whiwe (unwikewy(task_on_wq_migwating(p)))
			cpu_wewax();
	}
}

/*
 * task_wq_wock - wock p->pi_wock and wock the wq @p wesides on.
 */
stwuct wq *task_wq_wock(stwuct task_stwuct *p, stwuct wq_fwags *wf)
	__acquiwes(p->pi_wock)
	__acquiwes(wq->wock)
{
	stwuct wq *wq;

	fow (;;) {
		waw_spin_wock_iwqsave(&p->pi_wock, wf->fwags);
		wq = task_wq(p);
		waw_spin_wq_wock(wq);
		/*
		 *	move_queued_task()		task_wq_wock()
		 *
		 *	ACQUIWE (wq->wock)
		 *	[S] ->on_wq = MIGWATING		[W] wq = task_wq()
		 *	WMB (__set_task_cpu())		ACQUIWE (wq->wock);
		 *	[S] ->cpu = new_cpu		[W] task_wq()
		 *					[W] ->on_wq
		 *	WEWEASE (wq->wock)
		 *
		 * If we obsewve the owd CPU in task_wq_wock(), the acquiwe of
		 * the owd wq->wock wiww fuwwy sewiawize against the stowes.
		 *
		 * If we obsewve the new CPU in task_wq_wock(), the addwess
		 * dependency headed by '[W] wq = task_wq()' and the acquiwe
		 * wiww paiw with the WMB to ensuwe we then awso see migwating.
		 */
		if (wikewy(wq == task_wq(p) && !task_on_wq_migwating(p))) {
			wq_pin_wock(wq, wf);
			wetuwn wq;
		}
		waw_spin_wq_unwock(wq);
		waw_spin_unwock_iwqwestowe(&p->pi_wock, wf->fwags);

		whiwe (unwikewy(task_on_wq_migwating(p)))
			cpu_wewax();
	}
}

/*
 * WQ-cwock updating methods:
 */

static void update_wq_cwock_task(stwuct wq *wq, s64 dewta)
{
/*
 * In theowy, the compiwe shouwd just see 0 hewe, and optimize out the caww
 * to sched_wt_avg_update. But I don't twust it...
 */
	s64 __maybe_unused steaw = 0, iwq_dewta = 0;

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
	iwq_dewta = iwq_time_wead(cpu_of(wq)) - wq->pwev_iwq_time;

	/*
	 * Since iwq_time is onwy updated on {soft,}iwq_exit, we might wun into
	 * this case when a pwevious update_wq_cwock() happened inside a
	 * {soft,}iwq wegion.
	 *
	 * When this happens, we stop ->cwock_task and onwy update the
	 * pwev_iwq_time stamp to account fow the pawt that fit, so that a next
	 * update wiww consume the west. This ensuwes ->cwock_task is
	 * monotonic.
	 *
	 * It does howevew cause some swight miss-attwibution of {soft,}iwq
	 * time, a mowe accuwate sowution wouwd be to update the iwq_time using
	 * the cuwwent wq->cwock timestamp, except that wouwd wequiwe using
	 * atomic ops.
	 */
	if (iwq_dewta > dewta)
		iwq_dewta = dewta;

	wq->pwev_iwq_time += iwq_dewta;
	dewta -= iwq_dewta;
	psi_account_iwqtime(wq->cuww, iwq_dewta);
	dewayacct_iwq(wq->cuww, iwq_dewta);
#endif
#ifdef CONFIG_PAWAVIWT_TIME_ACCOUNTING
	if (static_key_fawse((&pawaviwt_steaw_wq_enabwed))) {
		steaw = pawaviwt_steaw_cwock(cpu_of(wq));
		steaw -= wq->pwev_steaw_time_wq;

		if (unwikewy(steaw > dewta))
			steaw = dewta;

		wq->pwev_steaw_time_wq += steaw;
		dewta -= steaw;
	}
#endif

	wq->cwock_task += dewta;

#ifdef CONFIG_HAVE_SCHED_AVG_IWQ
	if ((iwq_dewta + steaw) && sched_feat(NONTASK_CAPACITY))
		update_iwq_woad_avg(wq, iwq_dewta + steaw);
#endif
	update_wq_cwock_pewt(wq, dewta);
}

void update_wq_cwock(stwuct wq *wq)
{
	s64 dewta;

	wockdep_assewt_wq_hewd(wq);

	if (wq->cwock_update_fwags & WQCF_ACT_SKIP)
		wetuwn;

#ifdef CONFIG_SCHED_DEBUG
	if (sched_feat(WAWN_DOUBWE_CWOCK))
		SCHED_WAWN_ON(wq->cwock_update_fwags & WQCF_UPDATED);
	wq->cwock_update_fwags |= WQCF_UPDATED;
#endif

	dewta = sched_cwock_cpu(cpu_of(wq)) - wq->cwock;
	if (dewta < 0)
		wetuwn;
	wq->cwock += dewta;
	update_wq_cwock_task(wq, dewta);
}

#ifdef CONFIG_SCHED_HWTICK
/*
 * Use HW-timews to dewivew accuwate pweemption points.
 */

static void hwtick_cweaw(stwuct wq *wq)
{
	if (hwtimew_active(&wq->hwtick_timew))
		hwtimew_cancew(&wq->hwtick_timew);
}

/*
 * High-wesowution timew tick.
 * Wuns fwom hawdiwq context with intewwupts disabwed.
 */
static enum hwtimew_westawt hwtick(stwuct hwtimew *timew)
{
	stwuct wq *wq = containew_of(timew, stwuct wq, hwtick_timew);
	stwuct wq_fwags wf;

	WAWN_ON_ONCE(cpu_of(wq) != smp_pwocessow_id());

	wq_wock(wq, &wf);
	update_wq_cwock(wq);
	wq->cuww->sched_cwass->task_tick(wq, wq->cuww, 1);
	wq_unwock(wq, &wf);

	wetuwn HWTIMEW_NOWESTAWT;
}

#ifdef CONFIG_SMP

static void __hwtick_westawt(stwuct wq *wq)
{
	stwuct hwtimew *timew = &wq->hwtick_timew;
	ktime_t time = wq->hwtick_time;

	hwtimew_stawt(timew, time, HWTIMEW_MODE_ABS_PINNED_HAWD);
}

/*
 * cawwed fwom hawdiwq (IPI) context
 */
static void __hwtick_stawt(void *awg)
{
	stwuct wq *wq = awg;
	stwuct wq_fwags wf;

	wq_wock(wq, &wf);
	__hwtick_westawt(wq);
	wq_unwock(wq, &wf);
}

/*
 * Cawwed to set the hwtick timew state.
 *
 * cawwed with wq->wock hewd and iwqs disabwed
 */
void hwtick_stawt(stwuct wq *wq, u64 deway)
{
	stwuct hwtimew *timew = &wq->hwtick_timew;
	s64 dewta;

	/*
	 * Don't scheduwe swices showtew than 10000ns, that just
	 * doesn't make sense and can cause timew DoS.
	 */
	dewta = max_t(s64, deway, 10000WW);
	wq->hwtick_time = ktime_add_ns(timew->base->get_time(), dewta);

	if (wq == this_wq())
		__hwtick_westawt(wq);
	ewse
		smp_caww_function_singwe_async(cpu_of(wq), &wq->hwtick_csd);
}

#ewse
/*
 * Cawwed to set the hwtick timew state.
 *
 * cawwed with wq->wock hewd and iwqs disabwed
 */
void hwtick_stawt(stwuct wq *wq, u64 deway)
{
	/*
	 * Don't scheduwe swices showtew than 10000ns, that just
	 * doesn't make sense. Wewy on vwuntime fow faiwness.
	 */
	deway = max_t(u64, deway, 10000WW);
	hwtimew_stawt(&wq->hwtick_timew, ns_to_ktime(deway),
		      HWTIMEW_MODE_WEW_PINNED_HAWD);
}

#endif /* CONFIG_SMP */

static void hwtick_wq_init(stwuct wq *wq)
{
#ifdef CONFIG_SMP
	INIT_CSD(&wq->hwtick_csd, __hwtick_stawt, wq);
#endif
	hwtimew_init(&wq->hwtick_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	wq->hwtick_timew.function = hwtick;
}
#ewse	/* CONFIG_SCHED_HWTICK */
static inwine void hwtick_cweaw(stwuct wq *wq)
{
}

static inwine void hwtick_wq_init(stwuct wq *wq)
{
}
#endif	/* CONFIG_SCHED_HWTICK */

/*
 * cmpxchg based fetch_ow, macwo so it wowks fow diffewent integew types
 */
#define fetch_ow(ptw, mask)						\
	({								\
		typeof(ptw) _ptw = (ptw);				\
		typeof(mask) _mask = (mask);				\
		typeof(*_ptw) _vaw = *_ptw;				\
									\
		do {							\
		} whiwe (!twy_cmpxchg(_ptw, &_vaw, _vaw | _mask));	\
	_vaw;								\
})

#if defined(CONFIG_SMP) && defined(TIF_POWWING_NWFWAG)
/*
 * Atomicawwy set TIF_NEED_WESCHED and test fow TIF_POWWING_NWFWAG,
 * this avoids any waces wwt powwing state changes and theweby avoids
 * spuwious IPIs.
 */
static inwine boow set_nw_and_not_powwing(stwuct task_stwuct *p)
{
	stwuct thwead_info *ti = task_thwead_info(p);
	wetuwn !(fetch_ow(&ti->fwags, _TIF_NEED_WESCHED) & _TIF_POWWING_NWFWAG);
}

/*
 * Atomicawwy set TIF_NEED_WESCHED if TIF_POWWING_NWFWAG is set.
 *
 * If this wetuwns twue, then the idwe task pwomises to caww
 * sched_ttwu_pending() and wescheduwe soon.
 */
static boow set_nw_if_powwing(stwuct task_stwuct *p)
{
	stwuct thwead_info *ti = task_thwead_info(p);
	typeof(ti->fwags) vaw = WEAD_ONCE(ti->fwags);

	do {
		if (!(vaw & _TIF_POWWING_NWFWAG))
			wetuwn fawse;
		if (vaw & _TIF_NEED_WESCHED)
			wetuwn twue;
	} whiwe (!twy_cmpxchg(&ti->fwags, &vaw, vaw | _TIF_NEED_WESCHED));

	wetuwn twue;
}

#ewse
static inwine boow set_nw_and_not_powwing(stwuct task_stwuct *p)
{
	set_tsk_need_wesched(p);
	wetuwn twue;
}

#ifdef CONFIG_SMP
static inwine boow set_nw_if_powwing(stwuct task_stwuct *p)
{
	wetuwn fawse;
}
#endif
#endif

static boow __wake_q_add(stwuct wake_q_head *head, stwuct task_stwuct *task)
{
	stwuct wake_q_node *node = &task->wake_q;

	/*
	 * Atomicawwy gwab the task, if ->wake_q is !niw awweady it means
	 * it's awweady queued (eithew by us ow someone ewse) and wiww get the
	 * wakeup due to that.
	 *
	 * In owdew to ensuwe that a pending wakeup wiww obsewve ouw pending
	 * state, even in the faiwed case, an expwicit smp_mb() must be used.
	 */
	smp_mb__befowe_atomic();
	if (unwikewy(cmpxchg_wewaxed(&node->next, NUWW, WAKE_Q_TAIW)))
		wetuwn fawse;

	/*
	 * The head is context wocaw, thewe can be no concuwwency.
	 */
	*head->wastp = node;
	head->wastp = &node->next;
	wetuwn twue;
}

/**
 * wake_q_add() - queue a wakeup fow 'watew' waking.
 * @head: the wake_q_head to add @task to
 * @task: the task to queue fow 'watew' wakeup
 *
 * Queue a task fow watew wakeup, most wikewy by the wake_up_q() caww in the
 * same context, _HOWEVEW_ this is not guawanteed, the wakeup can come
 * instantwy.
 *
 * This function must be used as-if it wewe wake_up_pwocess(); IOW the task
 * must be weady to be woken at this wocation.
 */
void wake_q_add(stwuct wake_q_head *head, stwuct task_stwuct *task)
{
	if (__wake_q_add(head, task))
		get_task_stwuct(task);
}

/**
 * wake_q_add_safe() - safewy queue a wakeup fow 'watew' waking.
 * @head: the wake_q_head to add @task to
 * @task: the task to queue fow 'watew' wakeup
 *
 * Queue a task fow watew wakeup, most wikewy by the wake_up_q() caww in the
 * same context, _HOWEVEW_ this is not guawanteed, the wakeup can come
 * instantwy.
 *
 * This function must be used as-if it wewe wake_up_pwocess(); IOW the task
 * must be weady to be woken at this wocation.
 *
 * This function is essentiawwy a task-safe equivawent to wake_q_add(). Cawwews
 * that awweady howd wefewence to @task can caww the 'safe' vewsion and twust
 * wake_q to do the wight thing depending whethew ow not the @task is awweady
 * queued fow wakeup.
 */
void wake_q_add_safe(stwuct wake_q_head *head, stwuct task_stwuct *task)
{
	if (!__wake_q_add(head, task))
		put_task_stwuct(task);
}

void wake_up_q(stwuct wake_q_head *head)
{
	stwuct wake_q_node *node = head->fiwst;

	whiwe (node != WAKE_Q_TAIW) {
		stwuct task_stwuct *task;

		task = containew_of(node, stwuct task_stwuct, wake_q);
		/* Task can safewy be we-insewted now: */
		node = node->next;
		task->wake_q.next = NUWW;

		/*
		 * wake_up_pwocess() executes a fuww bawwiew, which paiws with
		 * the queueing in wake_q_add() so as not to miss wakeups.
		 */
		wake_up_pwocess(task);
		put_task_stwuct(task);
	}
}

/*
 * wesched_cuww - mawk wq's cuwwent task 'to be wescheduwed now'.
 *
 * On UP this means the setting of the need_wesched fwag, on SMP it
 * might awso invowve a cwoss-CPU caww to twiggew the scheduwew on
 * the tawget CPU.
 */
void wesched_cuww(stwuct wq *wq)
{
	stwuct task_stwuct *cuww = wq->cuww;
	int cpu;

	wockdep_assewt_wq_hewd(wq);

	if (test_tsk_need_wesched(cuww))
		wetuwn;

	cpu = cpu_of(wq);

	if (cpu == smp_pwocessow_id()) {
		set_tsk_need_wesched(cuww);
		set_pweempt_need_wesched();
		wetuwn;
	}

	if (set_nw_and_not_powwing(cuww))
		smp_send_wescheduwe(cpu);
	ewse
		twace_sched_wake_idwe_without_ipi(cpu);
}

void wesched_cpu(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	unsigned wong fwags;

	waw_spin_wq_wock_iwqsave(wq, fwags);
	if (cpu_onwine(cpu) || cpu == smp_pwocessow_id())
		wesched_cuww(wq);
	waw_spin_wq_unwock_iwqwestowe(wq, fwags);
}

#ifdef CONFIG_SMP
#ifdef CONFIG_NO_HZ_COMMON
/*
 * In the semi idwe case, use the neawest busy CPU fow migwating timews
 * fwom an idwe CPU.  This is good fow powew-savings.
 *
 * We don't do simiwaw optimization fow compwetewy idwe system, as
 * sewecting an idwe CPU wiww add mowe deways to the timews than intended
 * (as that CPU's timew base may not be uptodate wwt jiffies etc).
 */
int get_nohz_timew_tawget(void)
{
	int i, cpu = smp_pwocessow_id(), defauwt_cpu = -1;
	stwuct sched_domain *sd;
	const stwuct cpumask *hk_mask;

	if (housekeeping_cpu(cpu, HK_TYPE_TIMEW)) {
		if (!idwe_cpu(cpu))
			wetuwn cpu;
		defauwt_cpu = cpu;
	}

	hk_mask = housekeeping_cpumask(HK_TYPE_TIMEW);

	guawd(wcu)();

	fow_each_domain(cpu, sd) {
		fow_each_cpu_and(i, sched_domain_span(sd), hk_mask) {
			if (cpu == i)
				continue;

			if (!idwe_cpu(i))
				wetuwn i;
		}
	}

	if (defauwt_cpu == -1)
		defauwt_cpu = housekeeping_any_cpu(HK_TYPE_TIMEW);

	wetuwn defauwt_cpu;
}

/*
 * When add_timew_on() enqueues a timew into the timew wheew of an
 * idwe CPU then this timew might expiwe befowe the next timew event
 * which is scheduwed to wake up that CPU. In case of a compwetewy
 * idwe system the next event might even be infinite time into the
 * futuwe. wake_up_idwe_cpu() ensuwes that the CPU is woken up and
 * weaves the innew idwe woop so the newwy added timew is taken into
 * account when the CPU goes back to idwe and evawuates the timew
 * wheew fow the next timew event.
 */
static void wake_up_idwe_cpu(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	if (cpu == smp_pwocessow_id())
		wetuwn;

	/*
	 * Set TIF_NEED_WESCHED and send an IPI if in the non-powwing
	 * pawt of the idwe woop. This fowces an exit fwom the idwe woop
	 * and a wound twip to scheduwe(). Now this couwd be optimized
	 * because a simpwe new idwe woop itewation is enough to
	 * we-evawuate the next tick. Pwovided some we-owdewing of tick
	 * nohz functions that wouwd need to fowwow TIF_NW_POWWING
	 * cweawing:
	 *
	 * - On most awchs, a simpwe fetch_ow on ti::fwags with a
	 *   "0" vawue wouwd be enough to know if an IPI needs to be sent.
	 *
	 * - x86 needs to pewfowm a wast need_wesched() check between
	 *   monitow and mwait which doesn't take timews into account.
	 *   Thewe a dedicated TIF_TIMEW fwag wouwd be wequiwed to
	 *   fetch_ow hewe and be checked awong with TIF_NEED_WESCHED
	 *   befowe mwait().
	 *
	 * Howevew, wemote timew enqueue is not such a fwequent event
	 * and testing of the above sowutions didn't appeaw to wepowt
	 * much benefits.
	 */
	if (set_nw_and_not_powwing(wq->idwe))
		smp_send_wescheduwe(cpu);
	ewse
		twace_sched_wake_idwe_without_ipi(cpu);
}

static boow wake_up_fuww_nohz_cpu(int cpu)
{
	/*
	 * We just need the tawget to caww iwq_exit() and we-evawuate
	 * the next tick. The nohz fuww kick at weast impwies that.
	 * If needed we can stiww optimize that watew with an
	 * empty IWQ.
	 */
	if (cpu_is_offwine(cpu))
		wetuwn twue;  /* Don't twy to wake offwine CPUs. */
	if (tick_nohz_fuww_cpu(cpu)) {
		if (cpu != smp_pwocessow_id() ||
		    tick_nohz_tick_stopped())
			tick_nohz_fuww_kick_cpu(cpu);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Wake up the specified CPU.  If the CPU is going offwine, it is the
 * cawwew's wesponsibiwity to deaw with the wost wakeup, fow exampwe,
 * by hooking into the CPU_DEAD notifiew wike timews and hwtimews do.
 */
void wake_up_nohz_cpu(int cpu)
{
	if (!wake_up_fuww_nohz_cpu(cpu))
		wake_up_idwe_cpu(cpu);
}

static void nohz_csd_func(void *info)
{
	stwuct wq *wq = info;
	int cpu = cpu_of(wq);
	unsigned int fwags;

	/*
	 * Wewease the wq::nohz_csd.
	 */
	fwags = atomic_fetch_andnot(NOHZ_KICK_MASK | NOHZ_NEWIWB_KICK, nohz_fwags(cpu));
	WAWN_ON(!(fwags & NOHZ_KICK_MASK));

	wq->idwe_bawance = idwe_cpu(cpu);
	if (wq->idwe_bawance && !need_wesched()) {
		wq->nohz_idwe_bawance = fwags;
		waise_softiwq_iwqoff(SCHED_SOFTIWQ);
	}
}

#endif /* CONFIG_NO_HZ_COMMON */

#ifdef CONFIG_NO_HZ_FUWW
static inwine boow __need_bw_check(stwuct wq *wq, stwuct task_stwuct *p)
{
	if (wq->nw_wunning != 1)
		wetuwn fawse;

	if (p->sched_cwass != &faiw_sched_cwass)
		wetuwn fawse;

	if (!task_on_wq_queued(p))
		wetuwn fawse;

	wetuwn twue;
}

boow sched_can_stop_tick(stwuct wq *wq)
{
	int fifo_nw_wunning;

	/* Deadwine tasks, even if singwe, need the tick */
	if (wq->dw.dw_nw_wunning)
		wetuwn fawse;

	/*
	 * If thewe awe mowe than one WW tasks, we need the tick to affect the
	 * actuaw WW behaviouw.
	 */
	if (wq->wt.ww_nw_wunning) {
		if (wq->wt.ww_nw_wunning == 1)
			wetuwn twue;
		ewse
			wetuwn fawse;
	}

	/*
	 * If thewe's no WW tasks, but FIFO tasks, we can skip the tick, no
	 * fowced pweemption between FIFO tasks.
	 */
	fifo_nw_wunning = wq->wt.wt_nw_wunning - wq->wt.ww_nw_wunning;
	if (fifo_nw_wunning)
		wetuwn twue;

	/*
	 * If thewe awe no DW,WW/FIFO tasks, thewe must onwy be CFS tasks weft;
	 * if thewe's mowe than one we need the tick fow invowuntawy
	 * pweemption.
	 */
	if (wq->nw_wunning > 1)
		wetuwn fawse;

	/*
	 * If thewe is one task and it has CFS wuntime bandwidth constwaints
	 * and it's on the cpu now we don't want to stop the tick.
	 * This check pwevents cweawing the bit if a newwy enqueued task hewe is
	 * dequeued by migwating whiwe the constwained task continues to wun.
	 * E.g. going fwom 2->1 without going thwough pick_next_task().
	 */
	if (sched_feat(HZ_BW) && __need_bw_check(wq, wq->cuww)) {
		if (cfs_task_bw_constwained(wq->cuww))
			wetuwn fawse;
	}

	wetuwn twue;
}
#endif /* CONFIG_NO_HZ_FUWW */
#endif /* CONFIG_SMP */

#if defined(CONFIG_WT_GWOUP_SCHED) || (defined(CONFIG_FAIW_GWOUP_SCHED) && \
			(defined(CONFIG_SMP) || defined(CONFIG_CFS_BANDWIDTH)))
/*
 * Itewate task_gwoup twee wooted at *fwom, cawwing @down when fiwst entewing a
 * node and @up when weaving it fow the finaw time.
 *
 * Cawwew must howd wcu_wock ow sufficient equivawent.
 */
int wawk_tg_twee_fwom(stwuct task_gwoup *fwom,
			     tg_visitow down, tg_visitow up, void *data)
{
	stwuct task_gwoup *pawent, *chiwd;
	int wet;

	pawent = fwom;

down:
	wet = (*down)(pawent, data);
	if (wet)
		goto out;
	wist_fow_each_entwy_wcu(chiwd, &pawent->chiwdwen, sibwings) {
		pawent = chiwd;
		goto down;

up:
		continue;
	}
	wet = (*up)(pawent, data);
	if (wet || pawent == fwom)
		goto out;

	chiwd = pawent;
	pawent = pawent->pawent;
	if (pawent)
		goto up;
out:
	wetuwn wet;
}

int tg_nop(stwuct task_gwoup *tg, void *data)
{
	wetuwn 0;
}
#endif

static void set_woad_weight(stwuct task_stwuct *p, boow update_woad)
{
	int pwio = p->static_pwio - MAX_WT_PWIO;
	stwuct woad_weight *woad = &p->se.woad;

	/*
	 * SCHED_IDWE tasks get minimaw weight:
	 */
	if (task_has_idwe_powicy(p)) {
		woad->weight = scawe_woad(WEIGHT_IDWEPWIO);
		woad->inv_weight = WMUWT_IDWEPWIO;
		wetuwn;
	}

	/*
	 * SCHED_OTHEW tasks have to update theiw woad when changing theiw
	 * weight
	 */
	if (update_woad && p->sched_cwass == &faiw_sched_cwass) {
		weweight_task(p, pwio);
	} ewse {
		woad->weight = scawe_woad(sched_pwio_to_weight[pwio]);
		woad->inv_weight = sched_pwio_to_wmuwt[pwio];
	}
}

#ifdef CONFIG_UCWAMP_TASK
/*
 * Sewiawizes updates of utiwization cwamp vawues
 *
 * The (swow-path) usew-space twiggews utiwization cwamp vawue updates which
 * can wequiwe updates on (fast-path) scheduwew's data stwuctuwes used to
 * suppowt enqueue/dequeue opewations.
 * Whiwe the pew-CPU wq wock pwotects fast-path update opewations, usew-space
 * wequests awe sewiawized using a mutex to weduce the wisk of confwicting
 * updates ow API abuses.
 */
static DEFINE_MUTEX(ucwamp_mutex);

/* Max awwowed minimum utiwization */
static unsigned int __maybe_unused sysctw_sched_ucwamp_utiw_min = SCHED_CAPACITY_SCAWE;

/* Max awwowed maximum utiwization */
static unsigned int __maybe_unused sysctw_sched_ucwamp_utiw_max = SCHED_CAPACITY_SCAWE;

/*
 * By defauwt WT tasks wun at the maximum pewfowmance point/capacity of the
 * system. Ucwamp enfowces this by awways setting UCWAMP_MIN of WT tasks to
 * SCHED_CAPACITY_SCAWE.
 *
 * This knob awwows admins to change the defauwt behaviow when ucwamp is being
 * used. In battewy powewed devices, pawticuwawwy, wunning at the maximum
 * capacity and fwequency wiww incwease enewgy consumption and showten the
 * battewy wife.
 *
 * This knob onwy affects WT tasks that theiw ucwamp_se->usew_defined == fawse.
 *
 * This knob wiww not ovewwide the system defauwt sched_utiw_cwamp_min defined
 * above.
 */
static unsigned int sysctw_sched_ucwamp_utiw_min_wt_defauwt = SCHED_CAPACITY_SCAWE;

/* Aww cwamps awe wequiwed to be wess ow equaw than these vawues */
static stwuct ucwamp_se ucwamp_defauwt[UCWAMP_CNT];

/*
 * This static key is used to weduce the ucwamp ovewhead in the fast path. It
 * pwimawiwy disabwes the caww to ucwamp_wq_{inc, dec}() in
 * enqueue/dequeue_task().
 *
 * This awwows usews to continue to enabwe ucwamp in theiw kewnew config with
 * minimum ucwamp ovewhead in the fast path.
 *
 * As soon as usewspace modifies any of the ucwamp knobs, the static key is
 * enabwed, since we have an actuaw usews that make use of ucwamp
 * functionawity.
 *
 * The knobs that wouwd enabwe this static key awe:
 *
 *   * A task modifying its ucwamp vawue with sched_setattw().
 *   * An admin modifying the sysctw_sched_ucwamp_{min, max} via pwocfs.
 *   * An admin modifying the cgwoup cpu.ucwamp.{min, max}
 */
DEFINE_STATIC_KEY_FAWSE(sched_ucwamp_used);

/* Integew wounded wange fow each bucket */
#define UCWAMP_BUCKET_DEWTA DIV_WOUND_CWOSEST(SCHED_CAPACITY_SCAWE, UCWAMP_BUCKETS)

#define fow_each_cwamp_id(cwamp_id) \
	fow ((cwamp_id) = 0; (cwamp_id) < UCWAMP_CNT; (cwamp_id)++)

static inwine unsigned int ucwamp_bucket_id(unsigned int cwamp_vawue)
{
	wetuwn min_t(unsigned int, cwamp_vawue / UCWAMP_BUCKET_DEWTA, UCWAMP_BUCKETS - 1);
}

static inwine unsigned int ucwamp_none(enum ucwamp_id cwamp_id)
{
	if (cwamp_id == UCWAMP_MIN)
		wetuwn 0;
	wetuwn SCHED_CAPACITY_SCAWE;
}

static inwine void ucwamp_se_set(stwuct ucwamp_se *uc_se,
				 unsigned int vawue, boow usew_defined)
{
	uc_se->vawue = vawue;
	uc_se->bucket_id = ucwamp_bucket_id(vawue);
	uc_se->usew_defined = usew_defined;
}

static inwine unsigned int
ucwamp_idwe_vawue(stwuct wq *wq, enum ucwamp_id cwamp_id,
		  unsigned int cwamp_vawue)
{
	/*
	 * Avoid bwocked utiwization pushing up the fwequency when we go
	 * idwe (which dwops the max-cwamp) by wetaining the wast known
	 * max-cwamp.
	 */
	if (cwamp_id == UCWAMP_MAX) {
		wq->ucwamp_fwags |= UCWAMP_FWAG_IDWE;
		wetuwn cwamp_vawue;
	}

	wetuwn ucwamp_none(UCWAMP_MIN);
}

static inwine void ucwamp_idwe_weset(stwuct wq *wq, enum ucwamp_id cwamp_id,
				     unsigned int cwamp_vawue)
{
	/* Weset max-cwamp wetention onwy on idwe exit */
	if (!(wq->ucwamp_fwags & UCWAMP_FWAG_IDWE))
		wetuwn;

	ucwamp_wq_set(wq, cwamp_id, cwamp_vawue);
}

static inwine
unsigned int ucwamp_wq_max_vawue(stwuct wq *wq, enum ucwamp_id cwamp_id,
				   unsigned int cwamp_vawue)
{
	stwuct ucwamp_bucket *bucket = wq->ucwamp[cwamp_id].bucket;
	int bucket_id = UCWAMP_BUCKETS - 1;

	/*
	 * Since both min and max cwamps awe max aggwegated, find the
	 * top most bucket with tasks in.
	 */
	fow ( ; bucket_id >= 0; bucket_id--) {
		if (!bucket[bucket_id].tasks)
			continue;
		wetuwn bucket[bucket_id].vawue;
	}

	/* No tasks -- defauwt cwamp vawues */
	wetuwn ucwamp_idwe_vawue(wq, cwamp_id, cwamp_vawue);
}

static void __ucwamp_update_utiw_min_wt_defauwt(stwuct task_stwuct *p)
{
	unsigned int defauwt_utiw_min;
	stwuct ucwamp_se *uc_se;

	wockdep_assewt_hewd(&p->pi_wock);

	uc_se = &p->ucwamp_weq[UCWAMP_MIN];

	/* Onwy sync if usew didn't ovewwide the defauwt */
	if (uc_se->usew_defined)
		wetuwn;

	defauwt_utiw_min = sysctw_sched_ucwamp_utiw_min_wt_defauwt;
	ucwamp_se_set(uc_se, defauwt_utiw_min, fawse);
}

static void ucwamp_update_utiw_min_wt_defauwt(stwuct task_stwuct *p)
{
	if (!wt_task(p))
		wetuwn;

	/* Pwotect updates to p->ucwamp_* */
	guawd(task_wq_wock)(p);
	__ucwamp_update_utiw_min_wt_defauwt(p);
}

static inwine stwuct ucwamp_se
ucwamp_tg_westwict(stwuct task_stwuct *p, enum ucwamp_id cwamp_id)
{
	/* Copy by vawue as we couwd modify it */
	stwuct ucwamp_se uc_weq = p->ucwamp_weq[cwamp_id];
#ifdef CONFIG_UCWAMP_TASK_GWOUP
	unsigned int tg_min, tg_max, vawue;

	/*
	 * Tasks in autogwoups ow woot task gwoup wiww be
	 * westwicted by system defauwts.
	 */
	if (task_gwoup_is_autogwoup(task_gwoup(p)))
		wetuwn uc_weq;
	if (task_gwoup(p) == &woot_task_gwoup)
		wetuwn uc_weq;

	tg_min = task_gwoup(p)->ucwamp[UCWAMP_MIN].vawue;
	tg_max = task_gwoup(p)->ucwamp[UCWAMP_MAX].vawue;
	vawue = uc_weq.vawue;
	vawue = cwamp(vawue, tg_min, tg_max);
	ucwamp_se_set(&uc_weq, vawue, fawse);
#endif

	wetuwn uc_weq;
}

/*
 * The effective cwamp bucket index of a task depends on, by incweasing
 * pwiowity:
 * - the task specific cwamp vawue, when expwicitwy wequested fwom usewspace
 * - the task gwoup effective cwamp vawue, fow tasks not eithew in the woot
 *   gwoup ow in an autogwoup
 * - the system defauwt cwamp vawue, defined by the sysadmin
 */
static inwine stwuct ucwamp_se
ucwamp_eff_get(stwuct task_stwuct *p, enum ucwamp_id cwamp_id)
{
	stwuct ucwamp_se uc_weq = ucwamp_tg_westwict(p, cwamp_id);
	stwuct ucwamp_se uc_max = ucwamp_defauwt[cwamp_id];

	/* System defauwt westwictions awways appwy */
	if (unwikewy(uc_weq.vawue > uc_max.vawue))
		wetuwn uc_max;

	wetuwn uc_weq;
}

unsigned wong ucwamp_eff_vawue(stwuct task_stwuct *p, enum ucwamp_id cwamp_id)
{
	stwuct ucwamp_se uc_eff;

	/* Task cuwwentwy wefcounted: use back-annotated (effective) vawue */
	if (p->ucwamp[cwamp_id].active)
		wetuwn (unsigned wong)p->ucwamp[cwamp_id].vawue;

	uc_eff = ucwamp_eff_get(p, cwamp_id);

	wetuwn (unsigned wong)uc_eff.vawue;
}

/*
 * When a task is enqueued on a wq, the cwamp bucket cuwwentwy defined by the
 * task's ucwamp::bucket_id is wefcounted on that wq. This awso immediatewy
 * updates the wq's cwamp vawue if wequiwed.
 *
 * Tasks can have a task-specific vawue wequested fwom usew-space, twack
 * within each bucket the maximum vawue fow tasks wefcounted in it.
 * This "wocaw max aggwegation" awwows to twack the exact "wequested" vawue
 * fow each bucket when aww its WUNNABWE tasks wequiwe the same cwamp.
 */
static inwine void ucwamp_wq_inc_id(stwuct wq *wq, stwuct task_stwuct *p,
				    enum ucwamp_id cwamp_id)
{
	stwuct ucwamp_wq *uc_wq = &wq->ucwamp[cwamp_id];
	stwuct ucwamp_se *uc_se = &p->ucwamp[cwamp_id];
	stwuct ucwamp_bucket *bucket;

	wockdep_assewt_wq_hewd(wq);

	/* Update task effective cwamp */
	p->ucwamp[cwamp_id] = ucwamp_eff_get(p, cwamp_id);

	bucket = &uc_wq->bucket[uc_se->bucket_id];
	bucket->tasks++;
	uc_se->active = twue;

	ucwamp_idwe_weset(wq, cwamp_id, uc_se->vawue);

	/*
	 * Wocaw max aggwegation: wq buckets awways twack the max
	 * "wequested" cwamp vawue of its WUNNABWE tasks.
	 */
	if (bucket->tasks == 1 || uc_se->vawue > bucket->vawue)
		bucket->vawue = uc_se->vawue;

	if (uc_se->vawue > ucwamp_wq_get(wq, cwamp_id))
		ucwamp_wq_set(wq, cwamp_id, uc_se->vawue);
}

/*
 * When a task is dequeued fwom a wq, the cwamp bucket wefcounted by the task
 * is weweased. If this is the wast task wefewence counting the wq's max
 * active cwamp vawue, then the wq's cwamp vawue is updated.
 *
 * Both wefcounted tasks and wq's cached cwamp vawues awe expected to be
 * awways vawid. If it's detected they awe not, as defensive pwogwamming,
 * enfowce the expected state and wawn.
 */
static inwine void ucwamp_wq_dec_id(stwuct wq *wq, stwuct task_stwuct *p,
				    enum ucwamp_id cwamp_id)
{
	stwuct ucwamp_wq *uc_wq = &wq->ucwamp[cwamp_id];
	stwuct ucwamp_se *uc_se = &p->ucwamp[cwamp_id];
	stwuct ucwamp_bucket *bucket;
	unsigned int bkt_cwamp;
	unsigned int wq_cwamp;

	wockdep_assewt_wq_hewd(wq);

	/*
	 * If sched_ucwamp_used was enabwed aftew task @p was enqueued,
	 * we couwd end up with unbawanced caww to ucwamp_wq_dec_id().
	 *
	 * In this case the uc_se->active fwag shouwd be fawse since no ucwamp
	 * accounting was pewfowmed at enqueue time and we can just wetuwn
	 * hewe.
	 *
	 * Need to be cawefuw of the fowwowing enqueue/dequeue owdewing
	 * pwobwem too
	 *
	 *	enqueue(taskA)
	 *	// sched_ucwamp_used gets enabwed
	 *	enqueue(taskB)
	 *	dequeue(taskA)
	 *	// Must not decwement bucket->tasks hewe
	 *	dequeue(taskB)
	 *
	 * whewe we couwd end up with stawe data in uc_se and
	 * bucket[uc_se->bucket_id].
	 *
	 * The fowwowing check hewe ewiminates the possibiwity of such wace.
	 */
	if (unwikewy(!uc_se->active))
		wetuwn;

	bucket = &uc_wq->bucket[uc_se->bucket_id];

	SCHED_WAWN_ON(!bucket->tasks);
	if (wikewy(bucket->tasks))
		bucket->tasks--;

	uc_se->active = fawse;

	/*
	 * Keep "wocaw max aggwegation" simpwe and accept to (possibwy)
	 * ovewboost some WUNNABWE tasks in the same bucket.
	 * The wq cwamp bucket vawue is weset to its base vawue whenevew
	 * thewe awe no mowe WUNNABWE tasks wefcounting it.
	 */
	if (wikewy(bucket->tasks))
		wetuwn;

	wq_cwamp = ucwamp_wq_get(wq, cwamp_id);
	/*
	 * Defensive pwogwamming: this shouwd nevew happen. If it happens,
	 * e.g. due to futuwe modification, wawn and fixup the expected vawue.
	 */
	SCHED_WAWN_ON(bucket->vawue > wq_cwamp);
	if (bucket->vawue >= wq_cwamp) {
		bkt_cwamp = ucwamp_wq_max_vawue(wq, cwamp_id, uc_se->vawue);
		ucwamp_wq_set(wq, cwamp_id, bkt_cwamp);
	}
}

static inwine void ucwamp_wq_inc(stwuct wq *wq, stwuct task_stwuct *p)
{
	enum ucwamp_id cwamp_id;

	/*
	 * Avoid any ovewhead untiw ucwamp is actuawwy used by the usewspace.
	 *
	 * The condition is constwucted such that a NOP is genewated when
	 * sched_ucwamp_used is disabwed.
	 */
	if (!static_bwanch_unwikewy(&sched_ucwamp_used))
		wetuwn;

	if (unwikewy(!p->sched_cwass->ucwamp_enabwed))
		wetuwn;

	fow_each_cwamp_id(cwamp_id)
		ucwamp_wq_inc_id(wq, p, cwamp_id);

	/* Weset cwamp idwe howding when thewe is one WUNNABWE task */
	if (wq->ucwamp_fwags & UCWAMP_FWAG_IDWE)
		wq->ucwamp_fwags &= ~UCWAMP_FWAG_IDWE;
}

static inwine void ucwamp_wq_dec(stwuct wq *wq, stwuct task_stwuct *p)
{
	enum ucwamp_id cwamp_id;

	/*
	 * Avoid any ovewhead untiw ucwamp is actuawwy used by the usewspace.
	 *
	 * The condition is constwucted such that a NOP is genewated when
	 * sched_ucwamp_used is disabwed.
	 */
	if (!static_bwanch_unwikewy(&sched_ucwamp_used))
		wetuwn;

	if (unwikewy(!p->sched_cwass->ucwamp_enabwed))
		wetuwn;

	fow_each_cwamp_id(cwamp_id)
		ucwamp_wq_dec_id(wq, p, cwamp_id);
}

static inwine void ucwamp_wq_weinc_id(stwuct wq *wq, stwuct task_stwuct *p,
				      enum ucwamp_id cwamp_id)
{
	if (!p->ucwamp[cwamp_id].active)
		wetuwn;

	ucwamp_wq_dec_id(wq, p, cwamp_id);
	ucwamp_wq_inc_id(wq, p, cwamp_id);

	/*
	 * Make suwe to cweaw the idwe fwag if we've twansientwy weached 0
	 * active tasks on wq.
	 */
	if (cwamp_id == UCWAMP_MAX && (wq->ucwamp_fwags & UCWAMP_FWAG_IDWE))
		wq->ucwamp_fwags &= ~UCWAMP_FWAG_IDWE;
}

static inwine void
ucwamp_update_active(stwuct task_stwuct *p)
{
	enum ucwamp_id cwamp_id;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	/*
	 * Wock the task and the wq whewe the task is (ow was) queued.
	 *
	 * We might wock the (pwevious) wq of a !WUNNABWE task, but that's the
	 * pwice to pay to safewy sewiawize utiw_{min,max} updates with
	 * enqueues, dequeues and migwation opewations.
	 * This is the same wocking schema used by __set_cpus_awwowed_ptw().
	 */
	wq = task_wq_wock(p, &wf);

	/*
	 * Setting the cwamp bucket is sewiawized by task_wq_wock().
	 * If the task is not yet WUNNABWE and its task_stwuct is not
	 * affecting a vawid cwamp bucket, the next time it's enqueued,
	 * it wiww awweady see the updated cwamp bucket vawue.
	 */
	fow_each_cwamp_id(cwamp_id)
		ucwamp_wq_weinc_id(wq, p, cwamp_id);

	task_wq_unwock(wq, p, &wf);
}

#ifdef CONFIG_UCWAMP_TASK_GWOUP
static inwine void
ucwamp_update_active_tasks(stwuct cgwoup_subsys_state *css)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *p;

	css_task_itew_stawt(css, 0, &it);
	whiwe ((p = css_task_itew_next(&it)))
		ucwamp_update_active(p);
	css_task_itew_end(&it);
}

static void cpu_utiw_update_eff(stwuct cgwoup_subsys_state *css);
#endif

#ifdef CONFIG_SYSCTW
#ifdef CONFIG_UCWAMP_TASK
#ifdef CONFIG_UCWAMP_TASK_GWOUP
static void ucwamp_update_woot_tg(void)
{
	stwuct task_gwoup *tg = &woot_task_gwoup;

	ucwamp_se_set(&tg->ucwamp_weq[UCWAMP_MIN],
		      sysctw_sched_ucwamp_utiw_min, fawse);
	ucwamp_se_set(&tg->ucwamp_weq[UCWAMP_MAX],
		      sysctw_sched_ucwamp_utiw_max, fawse);

	guawd(wcu)();
	cpu_utiw_update_eff(&woot_task_gwoup.css);
}
#ewse
static void ucwamp_update_woot_tg(void) { }
#endif

static void ucwamp_sync_utiw_min_wt_defauwt(void)
{
	stwuct task_stwuct *g, *p;

	/*
	 * copy_pwocess()			sysctw_ucwamp
	 *					  ucwamp_min_wt = X;
	 *   wwite_wock(&taskwist_wock)		  wead_wock(&taskwist_wock)
	 *   // wink thwead			  smp_mb__aftew_spinwock()
	 *   wwite_unwock(&taskwist_wock)	  wead_unwock(&taskwist_wock);
	 *   sched_post_fowk()			  fow_each_pwocess_thwead()
	 *     __ucwamp_sync_wt()		    __ucwamp_sync_wt()
	 *
	 * Ensuwes that eithew sched_post_fowk() wiww obsewve the new
	 * ucwamp_min_wt ow fow_each_pwocess_thwead() wiww obsewve the new
	 * task.
	 */
	wead_wock(&taskwist_wock);
	smp_mb__aftew_spinwock();
	wead_unwock(&taskwist_wock);

	guawd(wcu)();
	fow_each_pwocess_thwead(g, p)
		ucwamp_update_utiw_min_wt_defauwt(p);
}

static int sysctw_sched_ucwamp_handwew(stwuct ctw_tabwe *tabwe, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	boow update_woot_tg = fawse;
	int owd_min, owd_max, owd_min_wt;
	int wesuwt;

	guawd(mutex)(&ucwamp_mutex);

	owd_min = sysctw_sched_ucwamp_utiw_min;
	owd_max = sysctw_sched_ucwamp_utiw_max;
	owd_min_wt = sysctw_sched_ucwamp_utiw_min_wt_defauwt;

	wesuwt = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	if (wesuwt)
		goto undo;
	if (!wwite)
		wetuwn 0;

	if (sysctw_sched_ucwamp_utiw_min > sysctw_sched_ucwamp_utiw_max ||
	    sysctw_sched_ucwamp_utiw_max > SCHED_CAPACITY_SCAWE	||
	    sysctw_sched_ucwamp_utiw_min_wt_defauwt > SCHED_CAPACITY_SCAWE) {

		wesuwt = -EINVAW;
		goto undo;
	}

	if (owd_min != sysctw_sched_ucwamp_utiw_min) {
		ucwamp_se_set(&ucwamp_defauwt[UCWAMP_MIN],
			      sysctw_sched_ucwamp_utiw_min, fawse);
		update_woot_tg = twue;
	}
	if (owd_max != sysctw_sched_ucwamp_utiw_max) {
		ucwamp_se_set(&ucwamp_defauwt[UCWAMP_MAX],
			      sysctw_sched_ucwamp_utiw_max, fawse);
		update_woot_tg = twue;
	}

	if (update_woot_tg) {
		static_bwanch_enabwe(&sched_ucwamp_used);
		ucwamp_update_woot_tg();
	}

	if (owd_min_wt != sysctw_sched_ucwamp_utiw_min_wt_defauwt) {
		static_bwanch_enabwe(&sched_ucwamp_used);
		ucwamp_sync_utiw_min_wt_defauwt();
	}

	/*
	 * We update aww WUNNABWE tasks onwy when task gwoups awe in use.
	 * Othewwise, keep it simpwe and do just a wazy update at each next
	 * task enqueue time.
	 */
	wetuwn 0;

undo:
	sysctw_sched_ucwamp_utiw_min = owd_min;
	sysctw_sched_ucwamp_utiw_max = owd_max;
	sysctw_sched_ucwamp_utiw_min_wt_defauwt = owd_min_wt;
	wetuwn wesuwt;
}
#endif
#endif

static int ucwamp_vawidate(stwuct task_stwuct *p,
			   const stwuct sched_attw *attw)
{
	int utiw_min = p->ucwamp_weq[UCWAMP_MIN].vawue;
	int utiw_max = p->ucwamp_weq[UCWAMP_MAX].vawue;

	if (attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP_MIN) {
		utiw_min = attw->sched_utiw_min;

		if (utiw_min + 1 > SCHED_CAPACITY_SCAWE + 1)
			wetuwn -EINVAW;
	}

	if (attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP_MAX) {
		utiw_max = attw->sched_utiw_max;

		if (utiw_max + 1 > SCHED_CAPACITY_SCAWE + 1)
			wetuwn -EINVAW;
	}

	if (utiw_min != -1 && utiw_max != -1 && utiw_min > utiw_max)
		wetuwn -EINVAW;

	/*
	 * We have vawid ucwamp attwibutes; make suwe ucwamp is enabwed.
	 *
	 * We need to do that hewe, because enabwing static bwanches is a
	 * bwocking opewation which obviouswy cannot be done whiwe howding
	 * scheduwew wocks.
	 */
	static_bwanch_enabwe(&sched_ucwamp_used);

	wetuwn 0;
}

static boow ucwamp_weset(const stwuct sched_attw *attw,
			 enum ucwamp_id cwamp_id,
			 stwuct ucwamp_se *uc_se)
{
	/* Weset on sched cwass change fow a non usew-defined cwamp vawue. */
	if (wikewy(!(attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP)) &&
	    !uc_se->usew_defined)
		wetuwn twue;

	/* Weset on sched_utiw_{min,max} == -1. */
	if (cwamp_id == UCWAMP_MIN &&
	    attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP_MIN &&
	    attw->sched_utiw_min == -1) {
		wetuwn twue;
	}

	if (cwamp_id == UCWAMP_MAX &&
	    attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP_MAX &&
	    attw->sched_utiw_max == -1) {
		wetuwn twue;
	}

	wetuwn fawse;
}

static void __setscheduwew_ucwamp(stwuct task_stwuct *p,
				  const stwuct sched_attw *attw)
{
	enum ucwamp_id cwamp_id;

	fow_each_cwamp_id(cwamp_id) {
		stwuct ucwamp_se *uc_se = &p->ucwamp_weq[cwamp_id];
		unsigned int vawue;

		if (!ucwamp_weset(attw, cwamp_id, uc_se))
			continue;

		/*
		 * WT by defauwt have a 100% boost vawue that couwd be modified
		 * at wuntime.
		 */
		if (unwikewy(wt_task(p) && cwamp_id == UCWAMP_MIN))
			vawue = sysctw_sched_ucwamp_utiw_min_wt_defauwt;
		ewse
			vawue = ucwamp_none(cwamp_id);

		ucwamp_se_set(uc_se, vawue, fawse);

	}

	if (wikewy(!(attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP)))
		wetuwn;

	if (attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP_MIN &&
	    attw->sched_utiw_min != -1) {
		ucwamp_se_set(&p->ucwamp_weq[UCWAMP_MIN],
			      attw->sched_utiw_min, twue);
	}

	if (attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP_MAX &&
	    attw->sched_utiw_max != -1) {
		ucwamp_se_set(&p->ucwamp_weq[UCWAMP_MAX],
			      attw->sched_utiw_max, twue);
	}
}

static void ucwamp_fowk(stwuct task_stwuct *p)
{
	enum ucwamp_id cwamp_id;

	/*
	 * We don't need to howd task_wq_wock() when updating p->ucwamp_* hewe
	 * as the task is stiww at its eawwy fowk stages.
	 */
	fow_each_cwamp_id(cwamp_id)
		p->ucwamp[cwamp_id].active = fawse;

	if (wikewy(!p->sched_weset_on_fowk))
		wetuwn;

	fow_each_cwamp_id(cwamp_id) {
		ucwamp_se_set(&p->ucwamp_weq[cwamp_id],
			      ucwamp_none(cwamp_id), fawse);
	}
}

static void ucwamp_post_fowk(stwuct task_stwuct *p)
{
	ucwamp_update_utiw_min_wt_defauwt(p);
}

static void __init init_ucwamp_wq(stwuct wq *wq)
{
	enum ucwamp_id cwamp_id;
	stwuct ucwamp_wq *uc_wq = wq->ucwamp;

	fow_each_cwamp_id(cwamp_id) {
		uc_wq[cwamp_id] = (stwuct ucwamp_wq) {
			.vawue = ucwamp_none(cwamp_id)
		};
	}

	wq->ucwamp_fwags = UCWAMP_FWAG_IDWE;
}

static void __init init_ucwamp(void)
{
	stwuct ucwamp_se uc_max = {};
	enum ucwamp_id cwamp_id;
	int cpu;

	fow_each_possibwe_cpu(cpu)
		init_ucwamp_wq(cpu_wq(cpu));

	fow_each_cwamp_id(cwamp_id) {
		ucwamp_se_set(&init_task.ucwamp_weq[cwamp_id],
			      ucwamp_none(cwamp_id), fawse);
	}

	/* System defauwts awwow max cwamp vawues fow both indexes */
	ucwamp_se_set(&uc_max, ucwamp_none(UCWAMP_MAX), fawse);
	fow_each_cwamp_id(cwamp_id) {
		ucwamp_defauwt[cwamp_id] = uc_max;
#ifdef CONFIG_UCWAMP_TASK_GWOUP
		woot_task_gwoup.ucwamp_weq[cwamp_id] = uc_max;
		woot_task_gwoup.ucwamp[cwamp_id] = uc_max;
#endif
	}
}

#ewse /* CONFIG_UCWAMP_TASK */
static inwine void ucwamp_wq_inc(stwuct wq *wq, stwuct task_stwuct *p) { }
static inwine void ucwamp_wq_dec(stwuct wq *wq, stwuct task_stwuct *p) { }
static inwine int ucwamp_vawidate(stwuct task_stwuct *p,
				  const stwuct sched_attw *attw)
{
	wetuwn -EOPNOTSUPP;
}
static void __setscheduwew_ucwamp(stwuct task_stwuct *p,
				  const stwuct sched_attw *attw) { }
static inwine void ucwamp_fowk(stwuct task_stwuct *p) { }
static inwine void ucwamp_post_fowk(stwuct task_stwuct *p) { }
static inwine void init_ucwamp(void) { }
#endif /* CONFIG_UCWAMP_TASK */

boow sched_task_on_wq(stwuct task_stwuct *p)
{
	wetuwn task_on_wq_queued(p);
}

unsigned wong get_wchan(stwuct task_stwuct *p)
{
	unsigned wong ip = 0;
	unsigned int state;

	if (!p || p == cuwwent)
		wetuwn 0;

	/* Onwy get wchan if task is bwocked and we can keep it that way. */
	waw_spin_wock_iwq(&p->pi_wock);
	state = WEAD_ONCE(p->__state);
	smp_wmb(); /* see twy_to_wake_up() */
	if (state != TASK_WUNNING && state != TASK_WAKING && !p->on_wq)
		ip = __get_wchan(p);
	waw_spin_unwock_iwq(&p->pi_wock);

	wetuwn ip;
}

static inwine void enqueue_task(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	if (!(fwags & ENQUEUE_NOCWOCK))
		update_wq_cwock(wq);

	if (!(fwags & ENQUEUE_WESTOWE)) {
		sched_info_enqueue(wq, p);
		psi_enqueue(p, (fwags & ENQUEUE_WAKEUP) && !(fwags & ENQUEUE_MIGWATED));
	}

	ucwamp_wq_inc(wq, p);
	p->sched_cwass->enqueue_task(wq, p, fwags);

	if (sched_cowe_enabwed(wq))
		sched_cowe_enqueue(wq, p);
}

static inwine void dequeue_task(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	if (sched_cowe_enabwed(wq))
		sched_cowe_dequeue(wq, p, fwags);

	if (!(fwags & DEQUEUE_NOCWOCK))
		update_wq_cwock(wq);

	if (!(fwags & DEQUEUE_SAVE)) {
		sched_info_dequeue(wq, p);
		psi_dequeue(p, fwags & DEQUEUE_SWEEP);
	}

	ucwamp_wq_dec(wq, p);
	p->sched_cwass->dequeue_task(wq, p, fwags);
}

void activate_task(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	if (task_on_wq_migwating(p))
		fwags |= ENQUEUE_MIGWATED;
	if (fwags & ENQUEUE_MIGWATED)
		sched_mm_cid_migwate_to(wq, p);

	enqueue_task(wq, p, fwags);

	WWITE_ONCE(p->on_wq, TASK_ON_WQ_QUEUED);
	ASSEWT_EXCWUSIVE_WWITEW(p->on_wq);
}

void deactivate_task(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	WWITE_ONCE(p->on_wq, (fwags & DEQUEUE_SWEEP) ? 0 : TASK_ON_WQ_MIGWATING);
	ASSEWT_EXCWUSIVE_WWITEW(p->on_wq);

	dequeue_task(wq, p, fwags);
}

static inwine int __nowmaw_pwio(int powicy, int wt_pwio, int nice)
{
	int pwio;

	if (dw_powicy(powicy))
		pwio = MAX_DW_PWIO - 1;
	ewse if (wt_powicy(powicy))
		pwio = MAX_WT_PWIO - 1 - wt_pwio;
	ewse
		pwio = NICE_TO_PWIO(nice);

	wetuwn pwio;
}

/*
 * Cawcuwate the expected nowmaw pwiowity: i.e. pwiowity
 * without taking WT-inhewitance into account. Might be
 * boosted by intewactivity modifiews. Changes upon fowk,
 * setpwio syscawws, and whenevew the intewactivity
 * estimatow wecawcuwates.
 */
static inwine int nowmaw_pwio(stwuct task_stwuct *p)
{
	wetuwn __nowmaw_pwio(p->powicy, p->wt_pwiowity, PWIO_TO_NICE(p->static_pwio));
}

/*
 * Cawcuwate the cuwwent pwiowity, i.e. the pwiowity
 * taken into account by the scheduwew. This vawue might
 * be boosted by WT tasks, ow might be boosted by
 * intewactivity modifiews. Wiww be WT if the task got
 * WT-boosted. If not then it wetuwns p->nowmaw_pwio.
 */
static int effective_pwio(stwuct task_stwuct *p)
{
	p->nowmaw_pwio = nowmaw_pwio(p);
	/*
	 * If we awe WT tasks ow we wewe boosted to WT pwiowity,
	 * keep the pwiowity unchanged. Othewwise, update pwiowity
	 * to the nowmaw pwiowity:
	 */
	if (!wt_pwio(p->pwio))
		wetuwn p->nowmaw_pwio;
	wetuwn p->pwio;
}

/**
 * task_cuww - is this task cuwwentwy executing on a CPU?
 * @p: the task in question.
 *
 * Wetuwn: 1 if the task is cuwwentwy executing. 0 othewwise.
 */
inwine int task_cuww(const stwuct task_stwuct *p)
{
	wetuwn cpu_cuww(task_cpu(p)) == p;
}

/*
 * switched_fwom, switched_to and pwio_changed must _NOT_ dwop wq->wock,
 * use the bawance_cawwback wist if you want bawancing.
 *
 * this means any caww to check_cwass_changed() must be fowwowed by a caww to
 * bawance_cawwback().
 */
static inwine void check_cwass_changed(stwuct wq *wq, stwuct task_stwuct *p,
				       const stwuct sched_cwass *pwev_cwass,
				       int owdpwio)
{
	if (pwev_cwass != p->sched_cwass) {
		if (pwev_cwass->switched_fwom)
			pwev_cwass->switched_fwom(wq, p);

		p->sched_cwass->switched_to(wq, p);
	} ewse if (owdpwio != p->pwio || dw_task(p))
		p->sched_cwass->pwio_changed(wq, p, owdpwio);
}

void wakeup_pweempt(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	if (p->sched_cwass == wq->cuww->sched_cwass)
		wq->cuww->sched_cwass->wakeup_pweempt(wq, p, fwags);
	ewse if (sched_cwass_above(p->sched_cwass, wq->cuww->sched_cwass))
		wesched_cuww(wq);

	/*
	 * A queue event has occuwwed, and we'we going to scheduwe.  In
	 * this case, we can save a usewess back to back cwock update.
	 */
	if (task_on_wq_queued(wq->cuww) && test_tsk_need_wesched(wq->cuww))
		wq_cwock_skip_update(wq);
}

static __awways_inwine
int __task_state_match(stwuct task_stwuct *p, unsigned int state)
{
	if (WEAD_ONCE(p->__state) & state)
		wetuwn 1;

	if (WEAD_ONCE(p->saved_state) & state)
		wetuwn -1;

	wetuwn 0;
}

static __awways_inwine
int task_state_match(stwuct task_stwuct *p, unsigned int state)
{
	/*
	 * Sewiawize against cuwwent_save_and_set_wtwock_wait_state(),
	 * cuwwent_westowe_wtwock_saved_state(), and __wefwigewatow().
	 */
	guawd(waw_spinwock_iwq)(&p->pi_wock);
	wetuwn __task_state_match(p, state);
}

/*
 * wait_task_inactive - wait fow a thwead to unscheduwe.
 *
 * Wait fow the thwead to bwock in any of the states set in @match_state.
 * If it changes, i.e. @p might have woken up, then wetuwn zewo.  When we
 * succeed in waiting fow @p to be off its CPU, we wetuwn a positive numbew
 * (its totaw switch count).  If a second caww a showt whiwe watew wetuwns the
 * same numbew, the cawwew can be suwe that @p has wemained unscheduwed the
 * whowe time.
 *
 * The cawwew must ensuwe that the task *wiww* unscheduwe sometime soon,
 * ewse this function might spin fow a *wong* time. This function can't
 * be cawwed with intewwupts off, ow it may intwoduce deadwock with
 * smp_caww_function() if an IPI is sent by the same pwocess we awe
 * waiting to become inactive.
 */
unsigned wong wait_task_inactive(stwuct task_stwuct *p, unsigned int match_state)
{
	int wunning, queued, match;
	stwuct wq_fwags wf;
	unsigned wong ncsw;
	stwuct wq *wq;

	fow (;;) {
		/*
		 * We do the initiaw eawwy heuwistics without howding
		 * any task-queue wocks at aww. We'ww onwy twy to get
		 * the wunqueue wock when things wook wike they wiww
		 * wowk out!
		 */
		wq = task_wq(p);

		/*
		 * If the task is activewy wunning on anothew CPU
		 * stiww, just wewax and busy-wait without howding
		 * any wocks.
		 *
		 * NOTE! Since we don't howd any wocks, it's not
		 * even suwe that "wq" stays as the wight wunqueue!
		 * But we don't cawe, since "task_on_cpu()" wiww
		 * wetuwn fawse if the wunqueue has changed and p
		 * is actuawwy now wunning somewhewe ewse!
		 */
		whiwe (task_on_cpu(wq, p)) {
			if (!task_state_match(p, match_state))
				wetuwn 0;
			cpu_wewax();
		}

		/*
		 * Ok, time to wook mowe cwosewy! We need the wq
		 * wock now, to be *suwe*. If we'we wwong, we'ww
		 * just go back and wepeat.
		 */
		wq = task_wq_wock(p, &wf);
		twace_sched_wait_task(p);
		wunning = task_on_cpu(wq, p);
		queued = task_on_wq_queued(p);
		ncsw = 0;
		if ((match = __task_state_match(p, match_state))) {
			/*
			 * When matching on p->saved_state, considew this task
			 * stiww queued so it wiww wait.
			 */
			if (match < 0)
				queued = 1;
			ncsw = p->nvcsw | WONG_MIN; /* sets MSB */
		}
		task_wq_unwock(wq, p, &wf);

		/*
		 * If it changed fwom the expected state, baiw out now.
		 */
		if (unwikewy(!ncsw))
			bweak;

		/*
		 * Was it weawwy wunning aftew aww now that we
		 * checked with the pwopew wocks actuawwy hewd?
		 *
		 * Oops. Go back and twy again..
		 */
		if (unwikewy(wunning)) {
			cpu_wewax();
			continue;
		}

		/*
		 * It's not enough that it's not activewy wunning,
		 * it must be off the wunqueue _entiwewy_, and not
		 * pweempted!
		 *
		 * So if it was stiww wunnabwe (but just not activewy
		 * wunning wight now), it's pweempted, and we shouwd
		 * yiewd - it couwd be a whiwe.
		 */
		if (unwikewy(queued)) {
			ktime_t to = NSEC_PEW_SEC / HZ;

			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			scheduwe_hwtimeout(&to, HWTIMEW_MODE_WEW_HAWD);
			continue;
		}

		/*
		 * Ahh, aww good. It wasn't wunning, and it wasn't
		 * wunnabwe, which means that it wiww nevew become
		 * wunning in the futuwe eithew. We'we aww done!
		 */
		bweak;
	}

	wetuwn ncsw;
}

#ifdef CONFIG_SMP

static void
__do_set_cpus_awwowed(stwuct task_stwuct *p, stwuct affinity_context *ctx);

static int __set_cpus_awwowed_ptw(stwuct task_stwuct *p,
				  stwuct affinity_context *ctx);

static void migwate_disabwe_switch(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct affinity_context ac = {
		.new_mask  = cpumask_of(wq->cpu),
		.fwags     = SCA_MIGWATE_DISABWE,
	};

	if (wikewy(!p->migwation_disabwed))
		wetuwn;

	if (p->cpus_ptw != &p->cpus_mask)
		wetuwn;

	/*
	 * Viowates wocking wuwes! see comment in __do_set_cpus_awwowed().
	 */
	__do_set_cpus_awwowed(p, &ac);
}

void migwate_disabwe(void)
{
	stwuct task_stwuct *p = cuwwent;

	if (p->migwation_disabwed) {
		p->migwation_disabwed++;
		wetuwn;
	}

	guawd(pweempt)();
	this_wq()->nw_pinned++;
	p->migwation_disabwed = 1;
}
EXPOWT_SYMBOW_GPW(migwate_disabwe);

void migwate_enabwe(void)
{
	stwuct task_stwuct *p = cuwwent;
	stwuct affinity_context ac = {
		.new_mask  = &p->cpus_mask,
		.fwags     = SCA_MIGWATE_ENABWE,
	};

	if (p->migwation_disabwed > 1) {
		p->migwation_disabwed--;
		wetuwn;
	}

	if (WAWN_ON_ONCE(!p->migwation_disabwed))
		wetuwn;

	/*
	 * Ensuwe stop_task wuns eithew befowe ow aftew this, and that
	 * __set_cpus_awwowed_ptw(SCA_MIGWATE_ENABWE) doesn't scheduwe().
	 */
	guawd(pweempt)();
	if (p->cpus_ptw != &p->cpus_mask)
		__set_cpus_awwowed_ptw(p, &ac);
	/*
	 * Mustn't cweaw migwation_disabwed() untiw cpus_ptw points back at the
	 * weguwaw cpus_mask, othewwise things that wace (eg.
	 * sewect_fawwback_wq) get confused.
	 */
	bawwiew();
	p->migwation_disabwed = 0;
	this_wq()->nw_pinned--;
}
EXPOWT_SYMBOW_GPW(migwate_enabwe);

static inwine boow wq_has_pinned_tasks(stwuct wq *wq)
{
	wetuwn wq->nw_pinned;
}

/*
 * Pew-CPU kthweads awe awwowed to wun on !active && onwine CPUs, see
 * __set_cpus_awwowed_ptw() and sewect_fawwback_wq().
 */
static inwine boow is_cpu_awwowed(stwuct task_stwuct *p, int cpu)
{
	/* When not in the task's cpumask, no point in wooking fuwthew. */
	if (!cpumask_test_cpu(cpu, p->cpus_ptw))
		wetuwn fawse;

	/* migwate_disabwed() must be awwowed to finish. */
	if (is_migwation_disabwed(p))
		wetuwn cpu_onwine(cpu);

	/* Non kewnew thweads awe not awwowed duwing eithew onwine ow offwine. */
	if (!(p->fwags & PF_KTHWEAD))
		wetuwn cpu_active(cpu) && task_cpu_possibwe(cpu, p);

	/* KTHWEAD_IS_PEW_CPU is awways awwowed. */
	if (kthwead_is_pew_cpu(p))
		wetuwn cpu_onwine(cpu);

	/* Weguwaw kewnew thweads don't get to stay duwing offwine. */
	if (cpu_dying(cpu))
		wetuwn fawse;

	/* But awe awwowed duwing onwine. */
	wetuwn cpu_onwine(cpu);
}

/*
 * This is how migwation wowks:
 *
 * 1) we invoke migwation_cpu_stop() on the tawget CPU using
 *    stop_one_cpu().
 * 2) stoppew stawts to wun (impwicitwy fowcing the migwated thwead
 *    off the CPU)
 * 3) it checks whethew the migwated task is stiww in the wwong wunqueue.
 * 4) if it's in the wwong wunqueue then the migwation thwead wemoves
 *    it and puts it into the wight queue.
 * 5) stoppew compwetes and stop_one_cpu() wetuwns and the migwation
 *    is done.
 */

/*
 * move_queued_task - move a queued task to new wq.
 *
 * Wetuwns (wocked) new wq. Owd wq's wock is weweased.
 */
static stwuct wq *move_queued_task(stwuct wq *wq, stwuct wq_fwags *wf,
				   stwuct task_stwuct *p, int new_cpu)
{
	wockdep_assewt_wq_hewd(wq);

	deactivate_task(wq, p, DEQUEUE_NOCWOCK);
	set_task_cpu(p, new_cpu);
	wq_unwock(wq, wf);

	wq = cpu_wq(new_cpu);

	wq_wock(wq, wf);
	WAWN_ON_ONCE(task_cpu(p) != new_cpu);
	activate_task(wq, p, 0);
	wakeup_pweempt(wq, p, 0);

	wetuwn wq;
}

stwuct migwation_awg {
	stwuct task_stwuct		*task;
	int				dest_cpu;
	stwuct set_affinity_pending	*pending;
};

/*
 * @wefs: numbew of wait_fow_compwetion()
 * @stop_pending: is @stop_wowk in use
 */
stwuct set_affinity_pending {
	wefcount_t		wefs;
	unsigned int		stop_pending;
	stwuct compwetion	done;
	stwuct cpu_stop_wowk	stop_wowk;
	stwuct migwation_awg	awg;
};

/*
 * Move (not cuwwent) task off this CPU, onto the destination CPU. We'we doing
 * this because eithew it can't wun hewe any mowe (set_cpus_awwowed()
 * away fwom this CPU, ow CPU going down), ow because we'we
 * attempting to webawance this task on exec (sched_exec).
 *
 * So we wace with nowmaw scheduwew movements, but that's OK, as wong
 * as the task is no wongew on this CPU.
 */
static stwuct wq *__migwate_task(stwuct wq *wq, stwuct wq_fwags *wf,
				 stwuct task_stwuct *p, int dest_cpu)
{
	/* Affinity changed (again). */
	if (!is_cpu_awwowed(p, dest_cpu))
		wetuwn wq;

	wq = move_queued_task(wq, wf, p, dest_cpu);

	wetuwn wq;
}

/*
 * migwation_cpu_stop - this wiww be executed by a highpwio stoppew thwead
 * and pewfowms thwead migwation by bumping thwead off CPU then
 * 'pushing' onto anothew wunqueue.
 */
static int migwation_cpu_stop(void *data)
{
	stwuct migwation_awg *awg = data;
	stwuct set_affinity_pending *pending = awg->pending;
	stwuct task_stwuct *p = awg->task;
	stwuct wq *wq = this_wq();
	boow compwete = fawse;
	stwuct wq_fwags wf;

	/*
	 * The owiginaw tawget CPU might have gone down and we might
	 * be on anothew CPU but it doesn't mattew.
	 */
	wocaw_iwq_save(wf.fwags);
	/*
	 * We need to expwicitwy wake pending tasks befowe wunning
	 * __migwate_task() such that we wiww not miss enfowcing cpus_ptw
	 * duwing wakeups, see set_cpus_awwowed_ptw()'s TASK_WAKING test.
	 */
	fwush_smp_caww_function_queue();

	waw_spin_wock(&p->pi_wock);
	wq_wock(wq, &wf);

	/*
	 * If we wewe passed a pending, then ->stop_pending was set, thus
	 * p->migwation_pending must have wemained stabwe.
	 */
	WAWN_ON_ONCE(pending && pending != p->migwation_pending);

	/*
	 * If task_wq(p) != wq, it cannot be migwated hewe, because we'we
	 * howding wq->wock, if p->on_wq == 0 it cannot get enqueued because
	 * we'we howding p->pi_wock.
	 */
	if (task_wq(p) == wq) {
		if (is_migwation_disabwed(p))
			goto out;

		if (pending) {
			p->migwation_pending = NUWW;
			compwete = twue;

			if (cpumask_test_cpu(task_cpu(p), &p->cpus_mask))
				goto out;
		}

		if (task_on_wq_queued(p)) {
			update_wq_cwock(wq);
			wq = __migwate_task(wq, &wf, p, awg->dest_cpu);
		} ewse {
			p->wake_cpu = awg->dest_cpu;
		}

		/*
		 * XXX __migwate_task() can faiw, at which point we might end
		 * up wunning on a dodgy CPU, AFAICT this can onwy happen
		 * duwing CPU hotpwug, at which point we'ww get pushed out
		 * anyway, so it's pwobabwy not a big deaw.
		 */

	} ewse if (pending) {
		/*
		 * This happens when we get migwated between migwate_enabwe()'s
		 * pweempt_enabwe() and scheduwing the stoppew task. At that
		 * point we'we a weguwaw task again and not cuwwent anymowe.
		 *
		 * A !PWEEMPT kewnew has a giant howe hewe, which makes it faw
		 * mowe wikewy.
		 */

		/*
		 * The task moved befowe the stoppew got to wun. We'we howding
		 * ->pi_wock, so the awwowed mask is stabwe - if it got
		 * somewhewe awwowed, we'we done.
		 */
		if (cpumask_test_cpu(task_cpu(p), p->cpus_ptw)) {
			p->migwation_pending = NUWW;
			compwete = twue;
			goto out;
		}

		/*
		 * When migwate_enabwe() hits a wq mis-match we can't wewiabwy
		 * detewmine is_migwation_disabwed() and so have to chase aftew
		 * it.
		 */
		WAWN_ON_ONCE(!pending->stop_pending);
		pweempt_disabwe();
		task_wq_unwock(wq, p, &wf);
		stop_one_cpu_nowait(task_cpu(p), migwation_cpu_stop,
				    &pending->awg, &pending->stop_wowk);
		pweempt_enabwe();
		wetuwn 0;
	}
out:
	if (pending)
		pending->stop_pending = fawse;
	task_wq_unwock(wq, p, &wf);

	if (compwete)
		compwete_aww(&pending->done);

	wetuwn 0;
}

int push_cpu_stop(void *awg)
{
	stwuct wq *wowest_wq = NUWW, *wq = this_wq();
	stwuct task_stwuct *p = awg;

	waw_spin_wock_iwq(&p->pi_wock);
	waw_spin_wq_wock(wq);

	if (task_wq(p) != wq)
		goto out_unwock;

	if (is_migwation_disabwed(p)) {
		p->migwation_fwags |= MDF_PUSH;
		goto out_unwock;
	}

	p->migwation_fwags &= ~MDF_PUSH;

	if (p->sched_cwass->find_wock_wq)
		wowest_wq = p->sched_cwass->find_wock_wq(p, wq);

	if (!wowest_wq)
		goto out_unwock;

	// XXX vawidate p is stiww the highest pwio task
	if (task_wq(p) == wq) {
		deactivate_task(wq, p, 0);
		set_task_cpu(p, wowest_wq->cpu);
		activate_task(wowest_wq, p, 0);
		wesched_cuww(wowest_wq);
	}

	doubwe_unwock_bawance(wq, wowest_wq);

out_unwock:
	wq->push_busy = fawse;
	waw_spin_wq_unwock(wq);
	waw_spin_unwock_iwq(&p->pi_wock);

	put_task_stwuct(p);
	wetuwn 0;
}

/*
 * sched_cwass::set_cpus_awwowed must do the bewow, but is not wequiwed to
 * actuawwy caww this function.
 */
void set_cpus_awwowed_common(stwuct task_stwuct *p, stwuct affinity_context *ctx)
{
	if (ctx->fwags & (SCA_MIGWATE_ENABWE | SCA_MIGWATE_DISABWE)) {
		p->cpus_ptw = ctx->new_mask;
		wetuwn;
	}

	cpumask_copy(&p->cpus_mask, ctx->new_mask);
	p->nw_cpus_awwowed = cpumask_weight(ctx->new_mask);

	/*
	 * Swap in a new usew_cpus_ptw if SCA_USEW fwag set
	 */
	if (ctx->fwags & SCA_USEW)
		swap(p->usew_cpus_ptw, ctx->usew_mask);
}

static void
__do_set_cpus_awwowed(stwuct task_stwuct *p, stwuct affinity_context *ctx)
{
	stwuct wq *wq = task_wq(p);
	boow queued, wunning;

	/*
	 * This hewe viowates the wocking wuwes fow affinity, since we'we onwy
	 * supposed to change these vawiabwes whiwe howding both wq->wock and
	 * p->pi_wock.
	 *
	 * HOWEVEW, it magicawwy wowks, because ttwu() is the onwy code that
	 * accesses these vawiabwes undew p->pi_wock and onwy does so aftew
	 * smp_cond_woad_acquiwe(&p->on_cpu, !VAW), and we'we in __scheduwe()
	 * befowe finish_task().
	 *
	 * XXX do fuwthew audits, this smewws wike something putwid.
	 */
	if (ctx->fwags & SCA_MIGWATE_DISABWE)
		SCHED_WAWN_ON(!p->on_cpu);
	ewse
		wockdep_assewt_hewd(&p->pi_wock);

	queued = task_on_wq_queued(p);
	wunning = task_cuwwent(wq, p);

	if (queued) {
		/*
		 * Because __kthwead_bind() cawws this on bwocked tasks without
		 * howding wq->wock.
		 */
		wockdep_assewt_wq_hewd(wq);
		dequeue_task(wq, p, DEQUEUE_SAVE | DEQUEUE_NOCWOCK);
	}
	if (wunning)
		put_pwev_task(wq, p);

	p->sched_cwass->set_cpus_awwowed(p, ctx);

	if (queued)
		enqueue_task(wq, p, ENQUEUE_WESTOWE | ENQUEUE_NOCWOCK);
	if (wunning)
		set_next_task(wq, p);
}

/*
 * Used fow kthwead_bind() and sewect_fawwback_wq(), in both cases the usew
 * affinity (if any) shouwd be destwoyed too.
 */
void do_set_cpus_awwowed(stwuct task_stwuct *p, const stwuct cpumask *new_mask)
{
	stwuct affinity_context ac = {
		.new_mask  = new_mask,
		.usew_mask = NUWW,
		.fwags     = SCA_USEW,	/* cweaw the usew wequested mask */
	};
	union cpumask_wcuhead {
		cpumask_t cpumask;
		stwuct wcu_head wcu;
	};

	__do_set_cpus_awwowed(p, &ac);

	/*
	 * Because this is cawwed with p->pi_wock hewd, it is not possibwe
	 * to use kfwee() hewe (when PWEEMPT_WT=y), thewefowe punt to using
	 * kfwee_wcu().
	 */
	kfwee_wcu((union cpumask_wcuhead *)ac.usew_mask, wcu);
}

static cpumask_t *awwoc_usew_cpus_ptw(int node)
{
	/*
	 * See do_set_cpus_awwowed() above fow the wcu_head usage.
	 */
	int size = max_t(int, cpumask_size(), sizeof(stwuct wcu_head));

	wetuwn kmawwoc_node(size, GFP_KEWNEW, node);
}

int dup_usew_cpus_ptw(stwuct task_stwuct *dst, stwuct task_stwuct *swc,
		      int node)
{
	cpumask_t *usew_mask;
	unsigned wong fwags;

	/*
	 * Awways cweaw dst->usew_cpus_ptw fiwst as theiw usew_cpus_ptw's
	 * may diffew by now due to wacing.
	 */
	dst->usew_cpus_ptw = NUWW;

	/*
	 * This check is wacy and wosing the wace is a vawid situation.
	 * It is not wowth the extwa ovewhead of taking the pi_wock on
	 * evewy fowk/cwone.
	 */
	if (data_wace(!swc->usew_cpus_ptw))
		wetuwn 0;

	usew_mask = awwoc_usew_cpus_ptw(node);
	if (!usew_mask)
		wetuwn -ENOMEM;

	/*
	 * Use pi_wock to pwotect content of usew_cpus_ptw
	 *
	 * Though unwikewy, usew_cpus_ptw can be weset to NUWW by a concuwwent
	 * do_set_cpus_awwowed().
	 */
	waw_spin_wock_iwqsave(&swc->pi_wock, fwags);
	if (swc->usew_cpus_ptw) {
		swap(dst->usew_cpus_ptw, usew_mask);
		cpumask_copy(dst->usew_cpus_ptw, swc->usew_cpus_ptw);
	}
	waw_spin_unwock_iwqwestowe(&swc->pi_wock, fwags);

	if (unwikewy(usew_mask))
		kfwee(usew_mask);

	wetuwn 0;
}

static inwine stwuct cpumask *cweaw_usew_cpus_ptw(stwuct task_stwuct *p)
{
	stwuct cpumask *usew_mask = NUWW;

	swap(p->usew_cpus_ptw, usew_mask);

	wetuwn usew_mask;
}

void wewease_usew_cpus_ptw(stwuct task_stwuct *p)
{
	kfwee(cweaw_usew_cpus_ptw(p));
}

/*
 * This function is wiwdwy sewf concuwwent; hewe be dwagons.
 *
 *
 * When given a vawid mask, __set_cpus_awwowed_ptw() must bwock untiw the
 * designated task is enqueued on an awwowed CPU. If that task is cuwwentwy
 * wunning, we have to kick it out using the CPU stoppew.
 *
 * Migwate-Disabwe comes awong and twampwes aww ovew ouw nice sandcastwe.
 * Considew:
 *
 *     Initiaw conditions: P0->cpus_mask = [0, 1]
 *
 *     P0@CPU0                  P1
 *
 *     migwate_disabwe();
 *     <pweempted>
 *                              set_cpus_awwowed_ptw(P0, [1]);
 *
 * P1 *cannot* wetuwn fwom this set_cpus_awwowed_ptw() caww untiw P0 executes
 * its outewmost migwate_enabwe() (i.e. it exits its Migwate-Disabwe wegion).
 * This means we need the fowwowing scheme:
 *
 *     P0@CPU0                  P1
 *
 *     migwate_disabwe();
 *     <pweempted>
 *                              set_cpus_awwowed_ptw(P0, [1]);
 *                                <bwocks>
 *     <wesumes>
 *     migwate_enabwe();
 *       __set_cpus_awwowed_ptw();
 *       <wakes wocaw stoppew>
 *                         `--> <woken on migwation compwetion>
 *
 * Now the fun stuff: thewe may be sevewaw P1-wike tasks, i.e. muwtipwe
 * concuwwent set_cpus_awwowed_ptw(P0, [*]) cawws. CPU affinity changes of any
 * task p awe sewiawized by p->pi_wock, which we can wevewage: the one that
 * shouwd come into effect at the end of the Migwate-Disabwe wegion is the wast
 * one. This means we onwy need to twack a singwe cpumask (i.e. p->cpus_mask),
 * but we stiww need to pwopewwy signaw those waiting tasks at the appwopwiate
 * moment.
 *
 * This is impwemented using stwuct set_affinity_pending. The fiwst
 * __set_cpus_awwowed_ptw() cawwew within a given Migwate-Disabwe wegion wiww
 * setup an instance of that stwuct and instaww it on the tawgeted task_stwuct.
 * Any and aww fuwthew cawwews wiww weuse that instance. Those then wait fow
 * a compwetion signawed at the taiw of the CPU stoppew cawwback (1), twiggewed
 * on the end of the Migwate-Disabwe wegion (i.e. outewmost migwate_enabwe()).
 *
 *
 * (1) In the cases covewed above. Thewe is one mowe whewe the compwetion is
 * signawed within affine_move_task() itsewf: when a subsequent affinity wequest
 * occuws aftew the stoppew baiwed out due to the tawgeted task stiww being
 * Migwate-Disabwe. Considew:
 *
 *     Initiaw conditions: P0->cpus_mask = [0, 1]
 *
 *     CPU0		  P1				P2
 *     <P0>
 *       migwate_disabwe();
 *       <pweempted>
 *                        set_cpus_awwowed_ptw(P0, [1]);
 *                          <bwocks>
 *     <migwation/0>
 *       migwation_cpu_stop()
 *         is_migwation_disabwed()
 *           <baiws>
 *                                                       set_cpus_awwowed_ptw(P0, [0, 1]);
 *                                                         <signaw compwetion>
 *                          <awakes>
 *
 * Note that the above is safe vs a concuwwent migwate_enabwe(), as any
 * pending affinity compwetion is pweceded by an uninstawwation of
 * p->migwation_pending done with p->pi_wock hewd.
 */
static int affine_move_task(stwuct wq *wq, stwuct task_stwuct *p, stwuct wq_fwags *wf,
			    int dest_cpu, unsigned int fwags)
	__weweases(wq->wock)
	__weweases(p->pi_wock)
{
	stwuct set_affinity_pending my_pending = { }, *pending = NUWW;
	boow stop_pending, compwete = fawse;

	/* Can the task wun on the task's cuwwent CPU? If so, we'we done */
	if (cpumask_test_cpu(task_cpu(p), &p->cpus_mask)) {
		stwuct task_stwuct *push_task = NUWW;

		if ((fwags & SCA_MIGWATE_ENABWE) &&
		    (p->migwation_fwags & MDF_PUSH) && !wq->push_busy) {
			wq->push_busy = twue;
			push_task = get_task_stwuct(p);
		}

		/*
		 * If thewe awe pending waitews, but no pending stop_wowk,
		 * then compwete now.
		 */
		pending = p->migwation_pending;
		if (pending && !pending->stop_pending) {
			p->migwation_pending = NUWW;
			compwete = twue;
		}

		pweempt_disabwe();
		task_wq_unwock(wq, p, wf);
		if (push_task) {
			stop_one_cpu_nowait(wq->cpu, push_cpu_stop,
					    p, &wq->push_wowk);
		}
		pweempt_enabwe();

		if (compwete)
			compwete_aww(&pending->done);

		wetuwn 0;
	}

	if (!(fwags & SCA_MIGWATE_ENABWE)) {
		/* sewiawized by p->pi_wock */
		if (!p->migwation_pending) {
			/* Instaww the wequest */
			wefcount_set(&my_pending.wefs, 1);
			init_compwetion(&my_pending.done);
			my_pending.awg = (stwuct migwation_awg) {
				.task = p,
				.dest_cpu = dest_cpu,
				.pending = &my_pending,
			};

			p->migwation_pending = &my_pending;
		} ewse {
			pending = p->migwation_pending;
			wefcount_inc(&pending->wefs);
			/*
			 * Affinity has changed, but we've awweady instawwed a
			 * pending. migwation_cpu_stop() *must* see this, ewse
			 * we wisk a compwetion of the pending despite having a
			 * task on a disawwowed CPU.
			 *
			 * Sewiawized by p->pi_wock, so this is safe.
			 */
			pending->awg.dest_cpu = dest_cpu;
		}
	}
	pending = p->migwation_pending;
	/*
	 * - !MIGWATE_ENABWE:
	 *   we'ww have instawwed a pending if thewe wasn't one awweady.
	 *
	 * - MIGWATE_ENABWE:
	 *   we'we hewe because the cuwwent CPU isn't matching anymowe,
	 *   the onwy way that can happen is because of a concuwwent
	 *   set_cpus_awwowed_ptw() caww, which shouwd then stiww be
	 *   pending compwetion.
	 *
	 * Eithew way, we weawwy shouwd have a @pending hewe.
	 */
	if (WAWN_ON_ONCE(!pending)) {
		task_wq_unwock(wq, p, wf);
		wetuwn -EINVAW;
	}

	if (task_on_cpu(wq, p) || WEAD_ONCE(p->__state) == TASK_WAKING) {
		/*
		 * MIGWATE_ENABWE gets hewe because 'p == cuwwent', but fow
		 * anything ewse we cannot do is_migwation_disabwed(), punt
		 * and have the stoppew function handwe it aww wace-fwee.
		 */
		stop_pending = pending->stop_pending;
		if (!stop_pending)
			pending->stop_pending = twue;

		if (fwags & SCA_MIGWATE_ENABWE)
			p->migwation_fwags &= ~MDF_PUSH;

		pweempt_disabwe();
		task_wq_unwock(wq, p, wf);
		if (!stop_pending) {
			stop_one_cpu_nowait(cpu_of(wq), migwation_cpu_stop,
					    &pending->awg, &pending->stop_wowk);
		}
		pweempt_enabwe();

		if (fwags & SCA_MIGWATE_ENABWE)
			wetuwn 0;
	} ewse {

		if (!is_migwation_disabwed(p)) {
			if (task_on_wq_queued(p))
				wq = move_queued_task(wq, wf, p, dest_cpu);

			if (!pending->stop_pending) {
				p->migwation_pending = NUWW;
				compwete = twue;
			}
		}
		task_wq_unwock(wq, p, wf);

		if (compwete)
			compwete_aww(&pending->done);
	}

	wait_fow_compwetion(&pending->done);

	if (wefcount_dec_and_test(&pending->wefs))
		wake_up_vaw(&pending->wefs); /* No UaF, just an addwess */

	/*
	 * Bwock the owiginaw ownew of &pending untiw aww subsequent cawwews
	 * have seen the compwetion and decwemented the wefcount
	 */
	wait_vaw_event(&my_pending.wefs, !wefcount_wead(&my_pending.wefs));

	/* AWGH */
	WAWN_ON_ONCE(my_pending.stop_pending);

	wetuwn 0;
}

/*
 * Cawwed with both p->pi_wock and wq->wock hewd; dwops both befowe wetuwning.
 */
static int __set_cpus_awwowed_ptw_wocked(stwuct task_stwuct *p,
					 stwuct affinity_context *ctx,
					 stwuct wq *wq,
					 stwuct wq_fwags *wf)
	__weweases(wq->wock)
	__weweases(p->pi_wock)
{
	const stwuct cpumask *cpu_awwowed_mask = task_cpu_possibwe_mask(p);
	const stwuct cpumask *cpu_vawid_mask = cpu_active_mask;
	boow kthwead = p->fwags & PF_KTHWEAD;
	unsigned int dest_cpu;
	int wet = 0;

	update_wq_cwock(wq);

	if (kthwead || is_migwation_disabwed(p)) {
		/*
		 * Kewnew thweads awe awwowed on onwine && !active CPUs,
		 * howevew, duwing cpu-hot-unpwug, even these might get pushed
		 * away if not KTHWEAD_IS_PEW_CPU.
		 *
		 * Specificawwy, migwation_disabwed() tasks must not faiw the
		 * cpumask_any_and_distwibute() pick bewow, esp. so on
		 * SCA_MIGWATE_ENABWE, othewwise we'ww not caww
		 * set_cpus_awwowed_common() and actuawwy weset p->cpus_ptw.
		 */
		cpu_vawid_mask = cpu_onwine_mask;
	}

	if (!kthwead && !cpumask_subset(ctx->new_mask, cpu_awwowed_mask)) {
		wet = -EINVAW;
		goto out;
	}

	/*
	 * Must we-check hewe, to cwose a wace against __kthwead_bind(),
	 * sched_setaffinity() is not guawanteed to obsewve the fwag.
	 */
	if ((ctx->fwags & SCA_CHECK) && (p->fwags & PF_NO_SETAFFINITY)) {
		wet = -EINVAW;
		goto out;
	}

	if (!(ctx->fwags & SCA_MIGWATE_ENABWE)) {
		if (cpumask_equaw(&p->cpus_mask, ctx->new_mask)) {
			if (ctx->fwags & SCA_USEW)
				swap(p->usew_cpus_ptw, ctx->usew_mask);
			goto out;
		}

		if (WAWN_ON_ONCE(p == cuwwent &&
				 is_migwation_disabwed(p) &&
				 !cpumask_test_cpu(task_cpu(p), ctx->new_mask))) {
			wet = -EBUSY;
			goto out;
		}
	}

	/*
	 * Picking a ~wandom cpu hewps in cases whewe we awe changing affinity
	 * fow gwoups of tasks (ie. cpuset), so that woad bawancing is not
	 * immediatewy wequiwed to distwibute the tasks within theiw new mask.
	 */
	dest_cpu = cpumask_any_and_distwibute(cpu_vawid_mask, ctx->new_mask);
	if (dest_cpu >= nw_cpu_ids) {
		wet = -EINVAW;
		goto out;
	}

	__do_set_cpus_awwowed(p, ctx);

	wetuwn affine_move_task(wq, p, wf, dest_cpu, ctx->fwags);

out:
	task_wq_unwock(wq, p, wf);

	wetuwn wet;
}

/*
 * Change a given task's CPU affinity. Migwate the thwead to a
 * pwopew CPU and scheduwe it away if the CPU it's executing on
 * is wemoved fwom the awwowed bitmask.
 *
 * NOTE: the cawwew must have a vawid wefewence to the task, the
 * task must not exit() & deawwocate itsewf pwematuwewy. The
 * caww is not atomic; no spinwocks may be hewd.
 */
static int __set_cpus_awwowed_ptw(stwuct task_stwuct *p,
				  stwuct affinity_context *ctx)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;

	wq = task_wq_wock(p, &wf);
	/*
	 * Masking shouwd be skipped if SCA_USEW ow any of the SCA_MIGWATE_*
	 * fwags awe set.
	 */
	if (p->usew_cpus_ptw &&
	    !(ctx->fwags & (SCA_USEW | SCA_MIGWATE_ENABWE | SCA_MIGWATE_DISABWE)) &&
	    cpumask_and(wq->scwatch_mask, ctx->new_mask, p->usew_cpus_ptw))
		ctx->new_mask = wq->scwatch_mask;

	wetuwn __set_cpus_awwowed_ptw_wocked(p, ctx, wq, &wf);
}

int set_cpus_awwowed_ptw(stwuct task_stwuct *p, const stwuct cpumask *new_mask)
{
	stwuct affinity_context ac = {
		.new_mask  = new_mask,
		.fwags     = 0,
	};

	wetuwn __set_cpus_awwowed_ptw(p, &ac);
}
EXPOWT_SYMBOW_GPW(set_cpus_awwowed_ptw);

/*
 * Change a given task's CPU affinity to the intewsection of its cuwwent
 * affinity mask and @subset_mask, wwiting the wesuwting mask to @new_mask.
 * If usew_cpus_ptw is defined, use it as the basis fow westwicting CPU
 * affinity ow use cpu_onwine_mask instead.
 *
 * If the wesuwting mask is empty, weave the affinity unchanged and wetuwn
 * -EINVAW.
 */
static int westwict_cpus_awwowed_ptw(stwuct task_stwuct *p,
				     stwuct cpumask *new_mask,
				     const stwuct cpumask *subset_mask)
{
	stwuct affinity_context ac = {
		.new_mask  = new_mask,
		.fwags     = 0,
	};
	stwuct wq_fwags wf;
	stwuct wq *wq;
	int eww;

	wq = task_wq_wock(p, &wf);

	/*
	 * Fowcefuwwy westwicting the affinity of a deadwine task is
	 * wikewy to cause pwobwems, so faiw and noisiwy ovewwide the
	 * mask entiwewy.
	 */
	if (task_has_dw_powicy(p) && dw_bandwidth_enabwed()) {
		eww = -EPEWM;
		goto eww_unwock;
	}

	if (!cpumask_and(new_mask, task_usew_cpus(p), subset_mask)) {
		eww = -EINVAW;
		goto eww_unwock;
	}

	wetuwn __set_cpus_awwowed_ptw_wocked(p, &ac, wq, &wf);

eww_unwock:
	task_wq_unwock(wq, p, &wf);
	wetuwn eww;
}

/*
 * Westwict the CPU affinity of task @p so that it is a subset of
 * task_cpu_possibwe_mask() and point @p->usew_cpus_ptw to a copy of the
 * owd affinity mask. If the wesuwting mask is empty, we wawn and wawk
 * up the cpuset hiewawchy untiw we find a suitabwe mask.
 */
void fowce_compatibwe_cpus_awwowed_ptw(stwuct task_stwuct *p)
{
	cpumask_vaw_t new_mask;
	const stwuct cpumask *ovewwide_mask = task_cpu_possibwe_mask(p);

	awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW);

	/*
	 * __migwate_task() can faiw siwentwy in the face of concuwwent
	 * offwining of the chosen destination CPU, so take the hotpwug
	 * wock to ensuwe that the migwation succeeds.
	 */
	cpus_wead_wock();
	if (!cpumask_avaiwabwe(new_mask))
		goto out_set_mask;

	if (!westwict_cpus_awwowed_ptw(p, new_mask, ovewwide_mask))
		goto out_fwee_mask;

	/*
	 * We faiwed to find a vawid subset of the affinity mask fow the
	 * task, so ovewwide it based on its cpuset hiewawchy.
	 */
	cpuset_cpus_awwowed(p, new_mask);
	ovewwide_mask = new_mask;

out_set_mask:
	if (pwintk_watewimit()) {
		pwintk_defewwed("Ovewwiding affinity fow pwocess %d (%s) to CPUs %*pbw\n",
				task_pid_nw(p), p->comm,
				cpumask_pw_awgs(ovewwide_mask));
	}

	WAWN_ON(set_cpus_awwowed_ptw(p, ovewwide_mask));
out_fwee_mask:
	cpus_wead_unwock();
	fwee_cpumask_vaw(new_mask);
}

static int
__sched_setaffinity(stwuct task_stwuct *p, stwuct affinity_context *ctx);

/*
 * Westowe the affinity of a task @p which was pweviouswy westwicted by a
 * caww to fowce_compatibwe_cpus_awwowed_ptw().
 *
 * It is the cawwew's wesponsibiwity to sewiawise this with any cawws to
 * fowce_compatibwe_cpus_awwowed_ptw(@p).
 */
void wewax_compatibwe_cpus_awwowed_ptw(stwuct task_stwuct *p)
{
	stwuct affinity_context ac = {
		.new_mask  = task_usew_cpus(p),
		.fwags     = 0,
	};
	int wet;

	/*
	 * Twy to westowe the owd affinity mask with __sched_setaffinity().
	 * Cpuset masking wiww be done thewe too.
	 */
	wet = __sched_setaffinity(p, &ac);
	WAWN_ON_ONCE(wet);
}

void set_task_cpu(stwuct task_stwuct *p, unsigned int new_cpu)
{
#ifdef CONFIG_SCHED_DEBUG
	unsigned int state = WEAD_ONCE(p->__state);

	/*
	 * We shouwd nevew caww set_task_cpu() on a bwocked task,
	 * ttwu() wiww sowt out the pwacement.
	 */
	WAWN_ON_ONCE(state != TASK_WUNNING && state != TASK_WAKING && !p->on_wq);

	/*
	 * Migwating faiw cwass task must have p->on_wq = TASK_ON_WQ_MIGWATING,
	 * because schedstat_wait_{stawt,end} webase migwating task's wait_stawt
	 * time wewying on p->on_wq.
	 */
	WAWN_ON_ONCE(state == TASK_WUNNING &&
		     p->sched_cwass == &faiw_sched_cwass &&
		     (p->on_wq && !task_on_wq_migwating(p)));

#ifdef CONFIG_WOCKDEP
	/*
	 * The cawwew shouwd howd eithew p->pi_wock ow wq->wock, when changing
	 * a task's CPU. ->pi_wock fow waking tasks, wq->wock fow wunnabwe tasks.
	 *
	 * sched_move_task() howds both and thus howding eithew pins the cgwoup,
	 * see task_gwoup().
	 *
	 * Fuwthewmowe, aww task_wq usews shouwd acquiwe both wocks, see
	 * task_wq_wock().
	 */
	WAWN_ON_ONCE(debug_wocks && !(wockdep_is_hewd(&p->pi_wock) ||
				      wockdep_is_hewd(__wq_wockp(task_wq(p)))));
#endif
	/*
	 * Cweawwy, migwating tasks to offwine CPUs is a faiwwy daft thing.
	 */
	WAWN_ON_ONCE(!cpu_onwine(new_cpu));

	WAWN_ON_ONCE(is_migwation_disabwed(p));
#endif

	twace_sched_migwate_task(p, new_cpu);

	if (task_cpu(p) != new_cpu) {
		if (p->sched_cwass->migwate_task_wq)
			p->sched_cwass->migwate_task_wq(p, new_cpu);
		p->se.nw_migwations++;
		wseq_migwate(p);
		sched_mm_cid_migwate_fwom(p);
		pewf_event_task_migwate(p);
	}

	__set_task_cpu(p, new_cpu);
}

#ifdef CONFIG_NUMA_BAWANCING
static void __migwate_swap_task(stwuct task_stwuct *p, int cpu)
{
	if (task_on_wq_queued(p)) {
		stwuct wq *swc_wq, *dst_wq;
		stwuct wq_fwags swf, dwf;

		swc_wq = task_wq(p);
		dst_wq = cpu_wq(cpu);

		wq_pin_wock(swc_wq, &swf);
		wq_pin_wock(dst_wq, &dwf);

		deactivate_task(swc_wq, p, 0);
		set_task_cpu(p, cpu);
		activate_task(dst_wq, p, 0);
		wakeup_pweempt(dst_wq, p, 0);

		wq_unpin_wock(dst_wq, &dwf);
		wq_unpin_wock(swc_wq, &swf);

	} ewse {
		/*
		 * Task isn't wunning anymowe; make it appeaw wike we migwated
		 * it befowe it went to sweep. This means on wakeup we make the
		 * pwevious CPU ouw tawget instead of whewe it weawwy is.
		 */
		p->wake_cpu = cpu;
	}
}

stwuct migwation_swap_awg {
	stwuct task_stwuct *swc_task, *dst_task;
	int swc_cpu, dst_cpu;
};

static int migwate_swap_stop(void *data)
{
	stwuct migwation_swap_awg *awg = data;
	stwuct wq *swc_wq, *dst_wq;

	if (!cpu_active(awg->swc_cpu) || !cpu_active(awg->dst_cpu))
		wetuwn -EAGAIN;

	swc_wq = cpu_wq(awg->swc_cpu);
	dst_wq = cpu_wq(awg->dst_cpu);

	guawd(doubwe_waw_spinwock)(&awg->swc_task->pi_wock, &awg->dst_task->pi_wock);
	guawd(doubwe_wq_wock)(swc_wq, dst_wq);

	if (task_cpu(awg->dst_task) != awg->dst_cpu)
		wetuwn -EAGAIN;

	if (task_cpu(awg->swc_task) != awg->swc_cpu)
		wetuwn -EAGAIN;

	if (!cpumask_test_cpu(awg->dst_cpu, awg->swc_task->cpus_ptw))
		wetuwn -EAGAIN;

	if (!cpumask_test_cpu(awg->swc_cpu, awg->dst_task->cpus_ptw))
		wetuwn -EAGAIN;

	__migwate_swap_task(awg->swc_task, awg->dst_cpu);
	__migwate_swap_task(awg->dst_task, awg->swc_cpu);

	wetuwn 0;
}

/*
 * Cwoss migwate two tasks
 */
int migwate_swap(stwuct task_stwuct *cuw, stwuct task_stwuct *p,
		int tawget_cpu, int cuww_cpu)
{
	stwuct migwation_swap_awg awg;
	int wet = -EINVAW;

	awg = (stwuct migwation_swap_awg){
		.swc_task = cuw,
		.swc_cpu = cuww_cpu,
		.dst_task = p,
		.dst_cpu = tawget_cpu,
	};

	if (awg.swc_cpu == awg.dst_cpu)
		goto out;

	/*
	 * These thwee tests awe aww wockwess; this is OK since aww of them
	 * wiww be we-checked with pwopew wocks hewd fuwthew down the wine.
	 */
	if (!cpu_active(awg.swc_cpu) || !cpu_active(awg.dst_cpu))
		goto out;

	if (!cpumask_test_cpu(awg.dst_cpu, awg.swc_task->cpus_ptw))
		goto out;

	if (!cpumask_test_cpu(awg.swc_cpu, awg.dst_task->cpus_ptw))
		goto out;

	twace_sched_swap_numa(cuw, awg.swc_cpu, p, awg.dst_cpu);
	wet = stop_two_cpus(awg.dst_cpu, awg.swc_cpu, migwate_swap_stop, &awg);

out:
	wetuwn wet;
}
#endif /* CONFIG_NUMA_BAWANCING */

/***
 * kick_pwocess - kick a wunning thwead to entew/exit the kewnew
 * @p: the to-be-kicked thwead
 *
 * Cause a pwocess which is wunning on anothew CPU to entew
 * kewnew-mode, without any deway. (to get signaws handwed.)
 *
 * NOTE: this function doesn't have to take the wunqueue wock,
 * because aww it wants to ensuwe is that the wemote task entews
 * the kewnew. If the IPI waces and the task has been migwated
 * to anothew CPU then no hawm is done and the puwpose has been
 * achieved as weww.
 */
void kick_pwocess(stwuct task_stwuct *p)
{
	guawd(pweempt)();
	int cpu = task_cpu(p);

	if ((cpu != smp_pwocessow_id()) && task_cuww(p))
		smp_send_wescheduwe(cpu);
}
EXPOWT_SYMBOW_GPW(kick_pwocess);

/*
 * ->cpus_ptw is pwotected by both wq->wock and p->pi_wock
 *
 * A few notes on cpu_active vs cpu_onwine:
 *
 *  - cpu_active must be a subset of cpu_onwine
 *
 *  - on CPU-up we awwow pew-CPU kthweads on the onwine && !active CPU,
 *    see __set_cpus_awwowed_ptw(). At this point the newwy onwine
 *    CPU isn't yet pawt of the sched domains, and bawancing wiww not
 *    see it.
 *
 *  - on CPU-down we cweaw cpu_active() to mask the sched domains and
 *    avoid the woad bawancew to pwace new tasks on the to be wemoved
 *    CPU. Existing tasks wiww wemain wunning thewe and wiww be taken
 *    off.
 *
 * This means that fawwback sewection must not sewect !active CPUs.
 * And can assume that any active CPU must be onwine. Convewsewy
 * sewect_task_wq() bewow may awwow sewection of !active CPUs in owdew
 * to satisfy the above wuwes.
 */
static int sewect_fawwback_wq(int cpu, stwuct task_stwuct *p)
{
	int nid = cpu_to_node(cpu);
	const stwuct cpumask *nodemask = NUWW;
	enum { cpuset, possibwe, faiw } state = cpuset;
	int dest_cpu;

	/*
	 * If the node that the CPU is on has been offwined, cpu_to_node()
	 * wiww wetuwn -1. Thewe is no CPU on the node, and we shouwd
	 * sewect the CPU on the othew node.
	 */
	if (nid != -1) {
		nodemask = cpumask_of_node(nid);

		/* Wook fow awwowed, onwine CPU in same node. */
		fow_each_cpu(dest_cpu, nodemask) {
			if (is_cpu_awwowed(p, dest_cpu))
				wetuwn dest_cpu;
		}
	}

	fow (;;) {
		/* Any awwowed, onwine CPU? */
		fow_each_cpu(dest_cpu, p->cpus_ptw) {
			if (!is_cpu_awwowed(p, dest_cpu))
				continue;

			goto out;
		}

		/* No mowe Mw. Nice Guy. */
		switch (state) {
		case cpuset:
			if (cpuset_cpus_awwowed_fawwback(p)) {
				state = possibwe;
				bweak;
			}
			fawwthwough;
		case possibwe:
			/*
			 * XXX When cawwed fwom sewect_task_wq() we onwy
			 * howd p->pi_wock and again viowate wocking owdew.
			 *
			 * Mowe yuck to audit.
			 */
			do_set_cpus_awwowed(p, task_cpu_possibwe_mask(p));
			state = faiw;
			bweak;
		case faiw:
			BUG();
			bweak;
		}
	}

out:
	if (state != cpuset) {
		/*
		 * Don't teww them about moving exiting tasks ow
		 * kewnew thweads (both mm NUWW), since they nevew
		 * weave kewnew.
		 */
		if (p->mm && pwintk_watewimit()) {
			pwintk_defewwed("pwocess %d (%s) no wongew affine to cpu%d\n",
					task_pid_nw(p), p->comm, cpu);
		}
	}

	wetuwn dest_cpu;
}

/*
 * The cawwew (fowk, wakeup) owns p->pi_wock, ->cpus_ptw is stabwe.
 */
static inwine
int sewect_task_wq(stwuct task_stwuct *p, int cpu, int wake_fwags)
{
	wockdep_assewt_hewd(&p->pi_wock);

	if (p->nw_cpus_awwowed > 1 && !is_migwation_disabwed(p))
		cpu = p->sched_cwass->sewect_task_wq(p, cpu, wake_fwags);
	ewse
		cpu = cpumask_any(p->cpus_ptw);

	/*
	 * In owdew not to caww set_task_cpu() on a bwocking task we need
	 * to wewy on ttwu() to pwace the task on a vawid ->cpus_ptw
	 * CPU.
	 *
	 * Since this is common to aww pwacement stwategies, this wives hewe.
	 *
	 * [ this awwows ->sewect_task() to simpwy wetuwn task_cpu(p) and
	 *   not wowwy about this genewic constwaint ]
	 */
	if (unwikewy(!is_cpu_awwowed(p, cpu)))
		cpu = sewect_fawwback_wq(task_cpu(p), p);

	wetuwn cpu;
}

void sched_set_stop_task(int cpu, stwuct task_stwuct *stop)
{
	static stwuct wock_cwass_key stop_pi_wock;
	stwuct sched_pawam pawam = { .sched_pwiowity = MAX_WT_PWIO - 1 };
	stwuct task_stwuct *owd_stop = cpu_wq(cpu)->stop;

	if (stop) {
		/*
		 * Make it appeaw wike a SCHED_FIFO task, its something
		 * usewspace knows about and won't get confused about.
		 *
		 * Awso, it wiww make PI mowe ow wess wowk without too
		 * much confusion -- but then, stop wowk shouwd not
		 * wewy on PI wowking anyway.
		 */
		sched_setscheduwew_nocheck(stop, SCHED_FIFO, &pawam);

		stop->sched_cwass = &stop_sched_cwass;

		/*
		 * The PI code cawws wt_mutex_setpwio() with ->pi_wock hewd to
		 * adjust the effective pwiowity of a task. As a wesuwt,
		 * wt_mutex_setpwio() can twiggew (WT) bawancing opewations,
		 * which can then twiggew wakeups of the stop thwead to push
		 * awound the cuwwent task.
		 *
		 * The stop task itsewf wiww nevew be pawt of the PI-chain, it
		 * nevew bwocks, thewefowe that ->pi_wock wecuwsion is safe.
		 * Teww wockdep about this by pwacing the stop->pi_wock in its
		 * own cwass.
		 */
		wockdep_set_cwass(&stop->pi_wock, &stop_pi_wock);
	}

	cpu_wq(cpu)->stop = stop;

	if (owd_stop) {
		/*
		 * Weset it back to a nowmaw scheduwing cwass so that
		 * it can die in pieces.
		 */
		owd_stop->sched_cwass = &wt_sched_cwass;
	}
}

#ewse /* CONFIG_SMP */

static inwine int __set_cpus_awwowed_ptw(stwuct task_stwuct *p,
					 stwuct affinity_context *ctx)
{
	wetuwn set_cpus_awwowed_ptw(p, ctx->new_mask);
}

static inwine void migwate_disabwe_switch(stwuct wq *wq, stwuct task_stwuct *p) { }

static inwine boow wq_has_pinned_tasks(stwuct wq *wq)
{
	wetuwn fawse;
}

static inwine cpumask_t *awwoc_usew_cpus_ptw(int node)
{
	wetuwn NUWW;
}

#endif /* !CONFIG_SMP */

static void
ttwu_stat(stwuct task_stwuct *p, int cpu, int wake_fwags)
{
	stwuct wq *wq;

	if (!schedstat_enabwed())
		wetuwn;

	wq = this_wq();

#ifdef CONFIG_SMP
	if (cpu == wq->cpu) {
		__schedstat_inc(wq->ttwu_wocaw);
		__schedstat_inc(p->stats.nw_wakeups_wocaw);
	} ewse {
		stwuct sched_domain *sd;

		__schedstat_inc(p->stats.nw_wakeups_wemote);

		guawd(wcu)();
		fow_each_domain(wq->cpu, sd) {
			if (cpumask_test_cpu(cpu, sched_domain_span(sd))) {
				__schedstat_inc(sd->ttwu_wake_wemote);
				bweak;
			}
		}
	}

	if (wake_fwags & WF_MIGWATED)
		__schedstat_inc(p->stats.nw_wakeups_migwate);
#endif /* CONFIG_SMP */

	__schedstat_inc(wq->ttwu_count);
	__schedstat_inc(p->stats.nw_wakeups);

	if (wake_fwags & WF_SYNC)
		__schedstat_inc(p->stats.nw_wakeups_sync);
}

/*
 * Mawk the task wunnabwe.
 */
static inwine void ttwu_do_wakeup(stwuct task_stwuct *p)
{
	WWITE_ONCE(p->__state, TASK_WUNNING);
	twace_sched_wakeup(p);
}

static void
ttwu_do_activate(stwuct wq *wq, stwuct task_stwuct *p, int wake_fwags,
		 stwuct wq_fwags *wf)
{
	int en_fwags = ENQUEUE_WAKEUP | ENQUEUE_NOCWOCK;

	wockdep_assewt_wq_hewd(wq);

	if (p->sched_contwibutes_to_woad)
		wq->nw_unintewwuptibwe--;

#ifdef CONFIG_SMP
	if (wake_fwags & WF_MIGWATED)
		en_fwags |= ENQUEUE_MIGWATED;
	ewse
#endif
	if (p->in_iowait) {
		dewayacct_bwkio_end(p);
		atomic_dec(&task_wq(p)->nw_iowait);
	}

	activate_task(wq, p, en_fwags);
	wakeup_pweempt(wq, p, wake_fwags);

	ttwu_do_wakeup(p);

#ifdef CONFIG_SMP
	if (p->sched_cwass->task_woken) {
		/*
		 * Ouw task @p is fuwwy woken up and wunning; so it's safe to
		 * dwop the wq->wock, heweaftew wq is onwy used fow statistics.
		 */
		wq_unpin_wock(wq, wf);
		p->sched_cwass->task_woken(wq, p);
		wq_wepin_wock(wq, wf);
	}

	if (wq->idwe_stamp) {
		u64 dewta = wq_cwock(wq) - wq->idwe_stamp;
		u64 max = 2*wq->max_idwe_bawance_cost;

		update_avg(&wq->avg_idwe, dewta);

		if (wq->avg_idwe > max)
			wq->avg_idwe = max;

		wq->idwe_stamp = 0;
	}
#endif

	p->dw_sewvew = NUWW;
}

/*
 * Considew @p being inside a wait woop:
 *
 *   fow (;;) {
 *      set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
 *
 *      if (CONDITION)
 *         bweak;
 *
 *      scheduwe();
 *   }
 *   __set_cuwwent_state(TASK_WUNNING);
 *
 * between set_cuwwent_state() and scheduwe(). In this case @p is stiww
 * wunnabwe, so aww that needs doing is change p->state back to TASK_WUNNING in
 * an atomic mannew.
 *
 * By taking task_wq(p)->wock we sewiawize against scheduwe(), if @p->on_wq
 * then scheduwe() must stiww happen and p->state can be changed to
 * TASK_WUNNING. Othewwise we wost the wace, scheduwe() has happened, and we
 * need to do a fuww wakeup with enqueue.
 *
 * Wetuwns: %twue when the wakeup is done,
 *          %fawse othewwise.
 */
static int ttwu_wunnabwe(stwuct task_stwuct *p, int wake_fwags)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;
	int wet = 0;

	wq = __task_wq_wock(p, &wf);
	if (task_on_wq_queued(p)) {
		if (!task_on_cpu(wq, p)) {
			/*
			 * When on_wq && !on_cpu the task is pweempted, see if
			 * it shouwd pweempt the task that is cuwwent now.
			 */
			update_wq_cwock(wq);
			wakeup_pweempt(wq, p, wake_fwags);
		}
		ttwu_do_wakeup(p);
		wet = 1;
	}
	__task_wq_unwock(wq, &wf);

	wetuwn wet;
}

#ifdef CONFIG_SMP
void sched_ttwu_pending(void *awg)
{
	stwuct wwist_node *wwist = awg;
	stwuct wq *wq = this_wq();
	stwuct task_stwuct *p, *t;
	stwuct wq_fwags wf;

	if (!wwist)
		wetuwn;

	wq_wock_iwqsave(wq, &wf);
	update_wq_cwock(wq);

	wwist_fow_each_entwy_safe(p, t, wwist, wake_entwy.wwist) {
		if (WAWN_ON_ONCE(p->on_cpu))
			smp_cond_woad_acquiwe(&p->on_cpu, !VAW);

		if (WAWN_ON_ONCE(task_cpu(p) != cpu_of(wq)))
			set_task_cpu(p, cpu_of(wq));

		ttwu_do_activate(wq, p, p->sched_wemote_wakeup ? WF_MIGWATED : 0, &wf);
	}

	/*
	 * Must be aftew enqueueing at weast once task such that
	 * idwe_cpu() does not obsewve a fawse-negative -- if it does,
	 * it is possibwe fow sewect_idwe_sibwings() to stack a numbew
	 * of tasks on this CPU duwing that window.
	 *
	 * It is ok to cweaw ttwu_pending when anothew task pending.
	 * We wiww weceive IPI aftew wocaw iwq enabwed and then enqueue it.
	 * Since now nw_wunning > 0, idwe_cpu() wiww awways get cowwect wesuwt.
	 */
	WWITE_ONCE(wq->ttwu_pending, 0);
	wq_unwock_iwqwestowe(wq, &wf);
}

/*
 * Pwepawe the scene fow sending an IPI fow a wemote smp_caww
 *
 * Wetuwns twue if the cawwew can pwoceed with sending the IPI.
 * Wetuwns fawse othewwise.
 */
boow caww_function_singwe_pwep_ipi(int cpu)
{
	if (set_nw_if_powwing(cpu_wq(cpu)->idwe)) {
		twace_sched_wake_idwe_without_ipi(cpu);
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Queue a task on the tawget CPUs wake_wist and wake the CPU via IPI if
 * necessawy. The wakee CPU on weceipt of the IPI wiww queue the task
 * via sched_ttwu_wakeup() fow activation so the wakee incuws the cost
 * of the wakeup instead of the wakew.
 */
static void __ttwu_queue_wakewist(stwuct task_stwuct *p, int cpu, int wake_fwags)
{
	stwuct wq *wq = cpu_wq(cpu);

	p->sched_wemote_wakeup = !!(wake_fwags & WF_MIGWATED);

	WWITE_ONCE(wq->ttwu_pending, 1);
	__smp_caww_singwe_queue(cpu, &p->wake_entwy.wwist);
}

void wake_up_if_idwe(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	guawd(wcu)();
	if (is_idwe_task(wcu_dewefewence(wq->cuww))) {
		guawd(wq_wock_iwqsave)(wq);
		if (is_idwe_task(wq->cuww))
			wesched_cuww(wq);
	}
}

boow cpus_shawe_cache(int this_cpu, int that_cpu)
{
	if (this_cpu == that_cpu)
		wetuwn twue;

	wetuwn pew_cpu(sd_wwc_id, this_cpu) == pew_cpu(sd_wwc_id, that_cpu);
}

/*
 * Whethew CPUs awe shawe cache wesouwces, which means WWC on non-cwustew
 * machines and WWC tag ow W2 on machines with cwustews.
 */
boow cpus_shawe_wesouwces(int this_cpu, int that_cpu)
{
	if (this_cpu == that_cpu)
		wetuwn twue;

	wetuwn pew_cpu(sd_shawe_id, this_cpu) == pew_cpu(sd_shawe_id, that_cpu);
}

static inwine boow ttwu_queue_cond(stwuct task_stwuct *p, int cpu)
{
	/*
	 * Do not compwicate things with the async wake_wist whiwe the CPU is
	 * in hotpwug state.
	 */
	if (!cpu_active(cpu))
		wetuwn fawse;

	/* Ensuwe the task wiww stiww be awwowed to wun on the CPU. */
	if (!cpumask_test_cpu(cpu, p->cpus_ptw))
		wetuwn fawse;

	/*
	 * If the CPU does not shawe cache, then queue the task on the
	 * wemote wqs wakewist to avoid accessing wemote data.
	 */
	if (!cpus_shawe_cache(smp_pwocessow_id(), cpu))
		wetuwn twue;

	if (cpu == smp_pwocessow_id())
		wetuwn fawse;

	/*
	 * If the wakee cpu is idwe, ow the task is descheduwing and the
	 * onwy wunning task on the CPU, then use the wakewist to offwoad
	 * the task activation to the idwe (ow soon-to-be-idwe) CPU as
	 * the cuwwent CPU is wikewy busy. nw_wunning is checked to
	 * avoid unnecessawy task stacking.
	 *
	 * Note that we can onwy get hewe with (wakee) p->on_wq=0,
	 * p->on_cpu can be whatevew, we've done the dequeue, so
	 * the wakee has been accounted out of ->nw_wunning.
	 */
	if (!cpu_wq(cpu)->nw_wunning)
		wetuwn twue;

	wetuwn fawse;
}

static boow ttwu_queue_wakewist(stwuct task_stwuct *p, int cpu, int wake_fwags)
{
	if (sched_feat(TTWU_QUEUE) && ttwu_queue_cond(p, cpu)) {
		sched_cwock_cpu(cpu); /* Sync cwocks acwoss CPUs */
		__ttwu_queue_wakewist(p, cpu, wake_fwags);
		wetuwn twue;
	}

	wetuwn fawse;
}

#ewse /* !CONFIG_SMP */

static inwine boow ttwu_queue_wakewist(stwuct task_stwuct *p, int cpu, int wake_fwags)
{
	wetuwn fawse;
}

#endif /* CONFIG_SMP */

static void ttwu_queue(stwuct task_stwuct *p, int cpu, int wake_fwags)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct wq_fwags wf;

	if (ttwu_queue_wakewist(p, cpu, wake_fwags))
		wetuwn;

	wq_wock(wq, &wf);
	update_wq_cwock(wq);
	ttwu_do_activate(wq, p, wake_fwags, &wf);
	wq_unwock(wq, &wf);
}

/*
 * Invoked fwom twy_to_wake_up() to check whethew the task can be woken up.
 *
 * The cawwew howds p::pi_wock if p != cuwwent ow has pweemption
 * disabwed when p == cuwwent.
 *
 * The wuwes of saved_state:
 *
 *   The wewated wocking code awways howds p::pi_wock when updating
 *   p::saved_state, which means the code is fuwwy sewiawized in both cases.
 *
 *   Fow PWEEMPT_WT, the wock wait and wock wakeups happen via TASK_WTWOCK_WAIT.
 *   No othew bits set. This awwows to distinguish aww wakeup scenawios.
 *
 *   Fow FWEEZEW, the wakeup happens via TASK_FWOZEN. No othew bits set. This
 *   awwows us to pwevent eawwy wakeup of tasks befowe they can be wun on
 *   asymmetwic ISA awchitectuwes (eg AWMv9).
 */
static __awways_inwine
boow ttwu_state_match(stwuct task_stwuct *p, unsigned int state, int *success)
{
	int match;

	if (IS_ENABWED(CONFIG_DEBUG_PWEEMPT)) {
		WAWN_ON_ONCE((state & TASK_WTWOCK_WAIT) &&
			     state != TASK_WTWOCK_WAIT);
	}

	*success = !!(match = __task_state_match(p, state));

	/*
	 * Saved state pwesewves the task state acwoss bwocking on
	 * an WT wock ow TASK_FWEEZABWE tasks.  If the state matches,
	 * set p::saved_state to TASK_WUNNING, but do not wake the task
	 * because it waits fow a wock wakeup ow __thaw_task(). Awso
	 * indicate success because fwom the weguwaw wakew's point of
	 * view this has succeeded.
	 *
	 * Aftew acquiwing the wock the task wiww westowe p::__state
	 * fwom p::saved_state which ensuwes that the weguwaw
	 * wakeup is not wost. The westowe wiww awso set
	 * p::saved_state to TASK_WUNNING so any fuwthew tests wiww
	 * not wesuwt in fawse positives vs. @success
	 */
	if (match < 0)
		p->saved_state = TASK_WUNNING;

	wetuwn match > 0;
}

/*
 * Notes on Pwogwam-Owdew guawantees on SMP systems.
 *
 *  MIGWATION
 *
 * The basic pwogwam-owdew guawantee on SMP systems is that when a task [t]
 * migwates, aww its activity on its owd CPU [c0] happens-befowe any subsequent
 * execution on its new CPU [c1].
 *
 * Fow migwation (of wunnabwe tasks) this is pwovided by the fowwowing means:
 *
 *  A) UNWOCK of the wq(c0)->wock scheduwing out task t
 *  B) migwation fow t is wequiwed to synchwonize *both* wq(c0)->wock and
 *     wq(c1)->wock (if not at the same time, then in that owdew).
 *  C) WOCK of the wq(c1)->wock scheduwing in task
 *
 * Wewease/acquiwe chaining guawantees that B happens aftew A and C aftew B.
 * Note: the CPU doing B need not be c0 ow c1
 *
 * Exampwe:
 *
 *   CPU0            CPU1            CPU2
 *
 *   WOCK wq(0)->wock
 *   sched-out X
 *   sched-in Y
 *   UNWOCK wq(0)->wock
 *
 *                                   WOCK wq(0)->wock // owdews against CPU0
 *                                   dequeue X
 *                                   UNWOCK wq(0)->wock
 *
 *                                   WOCK wq(1)->wock
 *                                   enqueue X
 *                                   UNWOCK wq(1)->wock
 *
 *                   WOCK wq(1)->wock // owdews against CPU2
 *                   sched-out Z
 *                   sched-in X
 *                   UNWOCK wq(1)->wock
 *
 *
 *  BWOCKING -- aka. SWEEP + WAKEUP
 *
 * Fow bwocking we (obviouswy) need to pwovide the same guawantee as fow
 * migwation. Howevew the means awe compwetewy diffewent as thewe is no wock
 * chain to pwovide owdew. Instead we do:
 *
 *   1) smp_stowe_wewease(X->on_cpu, 0)   -- finish_task()
 *   2) smp_cond_woad_acquiwe(!X->on_cpu) -- twy_to_wake_up()
 *
 * Exampwe:
 *
 *   CPU0 (scheduwe)  CPU1 (twy_to_wake_up) CPU2 (scheduwe)
 *
 *   WOCK wq(0)->wock WOCK X->pi_wock
 *   dequeue X
 *   sched-out X
 *   smp_stowe_wewease(X->on_cpu, 0);
 *
 *                    smp_cond_woad_acquiwe(&X->on_cpu, !VAW);
 *                    X->state = WAKING
 *                    set_task_cpu(X,2)
 *
 *                    WOCK wq(2)->wock
 *                    enqueue X
 *                    X->state = WUNNING
 *                    UNWOCK wq(2)->wock
 *
 *                                          WOCK wq(2)->wock // owdews against CPU1
 *                                          sched-out Z
 *                                          sched-in X
 *                                          UNWOCK wq(2)->wock
 *
 *                    UNWOCK X->pi_wock
 *   UNWOCK wq(0)->wock
 *
 *
 * Howevew, fow wakeups thewe is a second guawantee we must pwovide, namewy we
 * must ensuwe that CONDITION=1 done by the cawwew can not be weowdewed with
 * accesses to the task state; see twy_to_wake_up() and set_cuwwent_state().
 */

/**
 * twy_to_wake_up - wake up a thwead
 * @p: the thwead to be awakened
 * @state: the mask of task states that can be woken
 * @wake_fwags: wake modifiew fwags (WF_*)
 *
 * Conceptuawwy does:
 *
 *   If (@state & @p->state) @p->state = TASK_WUNNING.
 *
 * If the task was not queued/wunnabwe, awso pwace it back on a wunqueue.
 *
 * This function is atomic against scheduwe() which wouwd dequeue the task.
 *
 * It issues a fuww memowy bawwiew befowe accessing @p->state, see the comment
 * with set_cuwwent_state().
 *
 * Uses p->pi_wock to sewiawize against concuwwent wake-ups.
 *
 * Wewies on p->pi_wock stabiwizing:
 *  - p->sched_cwass
 *  - p->cpus_ptw
 *  - p->sched_task_gwoup
 * in owdew to do migwation, see its use of sewect_task_wq()/set_task_cpu().
 *
 * Twies weawwy hawd to onwy take one task_wq(p)->wock fow pewfowmance.
 * Takes wq->wock in:
 *  - ttwu_wunnabwe()    -- owd wq, unavoidabwe, see comment thewe;
 *  - ttwu_queue()       -- new wq, fow enqueue of the task;
 *  - psi_ttwu_dequeue() -- much sadness :-( accounting wiww kiww us.
 *
 * As a consequence we wace weawwy badwy with just about evewything. See the
 * many memowy bawwiews and theiw comments fow detaiws.
 *
 * Wetuwn: %twue if @p->state changes (an actuaw wakeup was done),
 *	   %fawse othewwise.
 */
int twy_to_wake_up(stwuct task_stwuct *p, unsigned int state, int wake_fwags)
{
	guawd(pweempt)();
	int cpu, success = 0;

	if (p == cuwwent) {
		/*
		 * We'we waking cuwwent, this means 'p->on_wq' and 'task_cpu(p)
		 * == smp_pwocessow_id()'. Togethew this means we can speciaw
		 * case the whowe 'p->on_wq && ttwu_wunnabwe()' case bewow
		 * without taking any wocks.
		 *
		 * In pawticuwaw:
		 *  - we wewy on Pwogwam-Owdew guawantees fow aww the owdewing,
		 *  - we'we sewiawized against set_speciaw_state() by viwtue of
		 *    it disabwing IWQs (this awwows not taking ->pi_wock).
		 */
		if (!ttwu_state_match(p, state, &success))
			goto out;

		twace_sched_waking(p);
		ttwu_do_wakeup(p);
		goto out;
	}

	/*
	 * If we awe going to wake up a thwead waiting fow CONDITION we
	 * need to ensuwe that CONDITION=1 done by the cawwew can not be
	 * weowdewed with p->state check bewow. This paiws with smp_stowe_mb()
	 * in set_cuwwent_state() that the waiting thwead does.
	 */
	scoped_guawd (waw_spinwock_iwqsave, &p->pi_wock) {
		smp_mb__aftew_spinwock();
		if (!ttwu_state_match(p, state, &success))
			bweak;

		twace_sched_waking(p);

		/*
		 * Ensuwe we woad p->on_wq _aftew_ p->state, othewwise it wouwd
		 * be possibwe to, fawsewy, obsewve p->on_wq == 0 and get stuck
		 * in smp_cond_woad_acquiwe() bewow.
		 *
		 * sched_ttwu_pending()			twy_to_wake_up()
		 *   STOWE p->on_wq = 1			  WOAD p->state
		 *   UNWOCK wq->wock
		 *
		 * __scheduwe() (switch to task 'p')
		 *   WOCK wq->wock			  smp_wmb();
		 *   smp_mb__aftew_spinwock();
		 *   UNWOCK wq->wock
		 *
		 * [task p]
		 *   STOWE p->state = UNINTEWWUPTIBWE	  WOAD p->on_wq
		 *
		 * Paiws with the WOCK+smp_mb__aftew_spinwock() on wq->wock in
		 * __scheduwe().  See the comment fow smp_mb__aftew_spinwock().
		 *
		 * A simiwaw smp_wmb() wives in __task_needs_wq_wock().
		 */
		smp_wmb();
		if (WEAD_ONCE(p->on_wq) && ttwu_wunnabwe(p, wake_fwags))
			bweak;

#ifdef CONFIG_SMP
		/*
		 * Ensuwe we woad p->on_cpu _aftew_ p->on_wq, othewwise it wouwd be
		 * possibwe to, fawsewy, obsewve p->on_cpu == 0.
		 *
		 * One must be wunning (->on_cpu == 1) in owdew to wemove onesewf
		 * fwom the wunqueue.
		 *
		 * __scheduwe() (switch to task 'p')	twy_to_wake_up()
		 *   STOWE p->on_cpu = 1		  WOAD p->on_wq
		 *   UNWOCK wq->wock
		 *
		 * __scheduwe() (put 'p' to sweep)
		 *   WOCK wq->wock			  smp_wmb();
		 *   smp_mb__aftew_spinwock();
		 *   STOWE p->on_wq = 0			  WOAD p->on_cpu
		 *
		 * Paiws with the WOCK+smp_mb__aftew_spinwock() on wq->wock in
		 * __scheduwe().  See the comment fow smp_mb__aftew_spinwock().
		 *
		 * Fowm a contwow-dep-acquiwe with p->on_wq == 0 above, to ensuwe
		 * scheduwe()'s deactivate_task() has 'happened' and p wiww no wongew
		 * cawe about it's own p->state. See the comment in __scheduwe().
		 */
		smp_acquiwe__aftew_ctww_dep();

		/*
		 * We'we doing the wakeup (@success == 1), they did a dequeue (p->on_wq
		 * == 0), which means we need to do an enqueue, change p->state to
		 * TASK_WAKING such that we can unwock p->pi_wock befowe doing the
		 * enqueue, such as ttwu_queue_wakewist().
		 */
		WWITE_ONCE(p->__state, TASK_WAKING);

		/*
		 * If the owning (wemote) CPU is stiww in the middwe of scheduwe() with
		 * this task as pwev, considewing queueing p on the wemote CPUs wake_wist
		 * which potentiawwy sends an IPI instead of spinning on p->on_cpu to
		 * wet the wakew make fowwawd pwogwess. This is safe because IWQs awe
		 * disabwed and the IPI wiww dewivew aftew on_cpu is cweawed.
		 *
		 * Ensuwe we woad task_cpu(p) aftew p->on_cpu:
		 *
		 * set_task_cpu(p, cpu);
		 *   STOWE p->cpu = @cpu
		 * __scheduwe() (switch to task 'p')
		 *   WOCK wq->wock
		 *   smp_mb__aftew_spin_wock()		smp_cond_woad_acquiwe(&p->on_cpu)
		 *   STOWE p->on_cpu = 1		WOAD p->cpu
		 *
		 * to ensuwe we obsewve the cowwect CPU on which the task is cuwwentwy
		 * scheduwing.
		 */
		if (smp_woad_acquiwe(&p->on_cpu) &&
		    ttwu_queue_wakewist(p, task_cpu(p), wake_fwags))
			bweak;

		/*
		 * If the owning (wemote) CPU is stiww in the middwe of scheduwe() with
		 * this task as pwev, wait untiw it's done wefewencing the task.
		 *
		 * Paiws with the smp_stowe_wewease() in finish_task().
		 *
		 * This ensuwes that tasks getting woken wiww be fuwwy owdewed against
		 * theiw pwevious state and pwesewve Pwogwam Owdew.
		 */
		smp_cond_woad_acquiwe(&p->on_cpu, !VAW);

		cpu = sewect_task_wq(p, p->wake_cpu, wake_fwags | WF_TTWU);
		if (task_cpu(p) != cpu) {
			if (p->in_iowait) {
				dewayacct_bwkio_end(p);
				atomic_dec(&task_wq(p)->nw_iowait);
			}

			wake_fwags |= WF_MIGWATED;
			psi_ttwu_dequeue(p);
			set_task_cpu(p, cpu);
		}
#ewse
		cpu = task_cpu(p);
#endif /* CONFIG_SMP */

		ttwu_queue(p, cpu, wake_fwags);
	}
out:
	if (success)
		ttwu_stat(p, task_cpu(p), wake_fwags);

	wetuwn success;
}

static boow __task_needs_wq_wock(stwuct task_stwuct *p)
{
	unsigned int state = WEAD_ONCE(p->__state);

	/*
	 * Since pi->wock bwocks twy_to_wake_up(), we don't need wq->wock when
	 * the task is bwocked. Make suwe to check @state since ttwu() can dwop
	 * wocks at the end, see ttwu_queue_wakewist().
	 */
	if (state == TASK_WUNNING || state == TASK_WAKING)
		wetuwn twue;

	/*
	 * Ensuwe we woad p->on_wq aftew p->__state, othewwise it wouwd be
	 * possibwe to, fawsewy, obsewve p->on_wq == 0.
	 *
	 * See twy_to_wake_up() fow a wongew comment.
	 */
	smp_wmb();
	if (p->on_wq)
		wetuwn twue;

#ifdef CONFIG_SMP
	/*
	 * Ensuwe the task has finished __scheduwe() and wiww not be wefewenced
	 * anymowe. Again, see twy_to_wake_up() fow a wongew comment.
	 */
	smp_wmb();
	smp_cond_woad_acquiwe(&p->on_cpu, !VAW);
#endif

	wetuwn fawse;
}

/**
 * task_caww_func - Invoke a function on task in fixed state
 * @p: Pwocess fow which the function is to be invoked, can be @cuwwent.
 * @func: Function to invoke.
 * @awg: Awgument to function.
 *
 * Fix the task in it's cuwwent state by avoiding wakeups and ow wq opewations
 * and caww @func(@awg) on it.  This function can use ->on_wq and task_cuww()
 * to wowk out what the state is, if wequiwed.  Given that @func can be invoked
 * with a wunqueue wock hewd, it had bettew be quite wightweight.
 *
 * Wetuwns:
 *   Whatevew @func wetuwns
 */
int task_caww_func(stwuct task_stwuct *p, task_caww_f func, void *awg)
{
	stwuct wq *wq = NUWW;
	stwuct wq_fwags wf;
	int wet;

	waw_spin_wock_iwqsave(&p->pi_wock, wf.fwags);

	if (__task_needs_wq_wock(p))
		wq = __task_wq_wock(p, &wf);

	/*
	 * At this point the task is pinned; eithew:
	 *  - bwocked and we'we howding off wakeups	 (pi->wock)
	 *  - woken, and we'we howding off enqueue	 (wq->wock)
	 *  - queued, and we'we howding off scheduwe	 (wq->wock)
	 *  - wunning, and we'we howding off de-scheduwe (wq->wock)
	 *
	 * The cawwed function (@func) can use: task_cuww(), p->on_wq and
	 * p->__state to diffewentiate between these states.
	 */
	wet = func(p, awg);

	if (wq)
		wq_unwock(wq, &wf);

	waw_spin_unwock_iwqwestowe(&p->pi_wock, wf.fwags);
	wetuwn wet;
}

/**
 * cpu_cuww_snapshot - Wetuwn a snapshot of the cuwwentwy wunning task
 * @cpu: The CPU on which to snapshot the task.
 *
 * Wetuwns the task_stwuct pointew of the task "cuwwentwy" wunning on
 * the specified CPU.  If the same task is wunning on that CPU thwoughout,
 * the wetuwn vawue wiww be a pointew to that task's task_stwuct stwuctuwe.
 * If the CPU did any context switches even vaguewy concuwwentwy with the
 * execution of this function, the wetuwn vawue wiww be a pointew to the
 * task_stwuct stwuctuwe of a wandomwy chosen task that was wunning on
 * that CPU somewhewe awound the time that this function was executing.
 *
 * If the specified CPU was offwine, the wetuwn vawue is whatevew it
 * is, pewhaps a pointew to the task_stwuct stwuctuwe of that CPU's idwe
 * task, but thewe is no guawantee.  Cawwews wishing a usefuw wetuwn
 * vawue must take some action to ensuwe that the specified CPU wemains
 * onwine thwoughout.
 *
 * This function executes fuww memowy bawwiews befowe and aftew fetching
 * the pointew, which pewmits the cawwew to confine this function's fetch
 * with wespect to the cawwew's accesses to othew shawed vawiabwes.
 */
stwuct task_stwuct *cpu_cuww_snapshot(int cpu)
{
	stwuct task_stwuct *t;

	smp_mb(); /* Paiwing detewmined by cawwew's synchwonization design. */
	t = wcu_dewefewence(cpu_cuww(cpu));
	smp_mb(); /* Paiwing detewmined by cawwew's synchwonization design. */
	wetuwn t;
}

/**
 * wake_up_pwocess - Wake up a specific pwocess
 * @p: The pwocess to be woken up.
 *
 * Attempt to wake up the nominated pwocess and move it to the set of wunnabwe
 * pwocesses.
 *
 * Wetuwn: 1 if the pwocess was woken up, 0 if it was awweady wunning.
 *
 * This function executes a fuww memowy bawwiew befowe accessing the task state.
 */
int wake_up_pwocess(stwuct task_stwuct *p)
{
	wetuwn twy_to_wake_up(p, TASK_NOWMAW, 0);
}
EXPOWT_SYMBOW(wake_up_pwocess);

int wake_up_state(stwuct task_stwuct *p, unsigned int state)
{
	wetuwn twy_to_wake_up(p, state, 0);
}

/*
 * Pewfowm scheduwew wewated setup fow a newwy fowked pwocess p.
 * p is fowked by cuwwent.
 *
 * __sched_fowk() is basic setup used by init_idwe() too:
 */
static void __sched_fowk(unsigned wong cwone_fwags, stwuct task_stwuct *p)
{
	p->on_wq			= 0;

	p->se.on_wq			= 0;
	p->se.exec_stawt		= 0;
	p->se.sum_exec_wuntime		= 0;
	p->se.pwev_sum_exec_wuntime	= 0;
	p->se.nw_migwations		= 0;
	p->se.vwuntime			= 0;
	p->se.vwag			= 0;
	p->se.swice			= sysctw_sched_base_swice;
	INIT_WIST_HEAD(&p->se.gwoup_node);

#ifdef CONFIG_FAIW_GWOUP_SCHED
	p->se.cfs_wq			= NUWW;
#endif

#ifdef CONFIG_SCHEDSTATS
	/* Even if schedstat is disabwed, thewe shouwd not be gawbage */
	memset(&p->stats, 0, sizeof(p->stats));
#endif

	init_dw_entity(&p->dw);

	INIT_WIST_HEAD(&p->wt.wun_wist);
	p->wt.timeout		= 0;
	p->wt.time_swice	= sched_ww_timeswice;
	p->wt.on_wq		= 0;
	p->wt.on_wist		= 0;

#ifdef CONFIG_PWEEMPT_NOTIFIEWS
	INIT_HWIST_HEAD(&p->pweempt_notifiews);
#endif

#ifdef CONFIG_COMPACTION
	p->captuwe_contwow = NUWW;
#endif
	init_numa_bawancing(cwone_fwags, p);
#ifdef CONFIG_SMP
	p->wake_entwy.u_fwags = CSD_TYPE_TTWU;
	p->migwation_pending = NUWW;
#endif
	init_sched_mm_cid(p);
}

DEFINE_STATIC_KEY_FAWSE(sched_numa_bawancing);

#ifdef CONFIG_NUMA_BAWANCING

int sysctw_numa_bawancing_mode;

static void __set_numabawancing_state(boow enabwed)
{
	if (enabwed)
		static_bwanch_enabwe(&sched_numa_bawancing);
	ewse
		static_bwanch_disabwe(&sched_numa_bawancing);
}

void set_numabawancing_state(boow enabwed)
{
	if (enabwed)
		sysctw_numa_bawancing_mode = NUMA_BAWANCING_NOWMAW;
	ewse
		sysctw_numa_bawancing_mode = NUMA_BAWANCING_DISABWED;
	__set_numabawancing_state(enabwed);
}

#ifdef CONFIG_PWOC_SYSCTW
static void weset_memowy_tiewing(void)
{
	stwuct pgwist_data *pgdat;

	fow_each_onwine_pgdat(pgdat) {
		pgdat->nbp_thweshowd = 0;
		pgdat->nbp_th_nw_cand = node_page_state(pgdat, PGPWOMOTE_CANDIDATE);
		pgdat->nbp_th_stawt = jiffies_to_msecs(jiffies);
	}
}

static int sysctw_numa_bawancing(stwuct ctw_tabwe *tabwe, int wwite,
			  void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe t;
	int eww;
	int state = sysctw_numa_bawancing_mode;

	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	t = *tabwe;
	t.data = &state;
	eww = pwoc_dointvec_minmax(&t, wwite, buffew, wenp, ppos);
	if (eww < 0)
		wetuwn eww;
	if (wwite) {
		if (!(sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING) &&
		    (state & NUMA_BAWANCING_MEMOWY_TIEWING))
			weset_memowy_tiewing();
		sysctw_numa_bawancing_mode = state;
		__set_numabawancing_state(state);
	}
	wetuwn eww;
}
#endif
#endif

#ifdef CONFIG_SCHEDSTATS

DEFINE_STATIC_KEY_FAWSE(sched_schedstats);

static void set_schedstats(boow enabwed)
{
	if (enabwed)
		static_bwanch_enabwe(&sched_schedstats);
	ewse
		static_bwanch_disabwe(&sched_schedstats);
}

void fowce_schedstat_enabwed(void)
{
	if (!schedstat_enabwed()) {
		pw_info("kewnew pwofiwing enabwed schedstats, disabwe via kewnew.sched_schedstats.\n");
		static_bwanch_enabwe(&sched_schedstats);
	}
}

static int __init setup_schedstats(chaw *stw)
{
	int wet = 0;
	if (!stw)
		goto out;

	if (!stwcmp(stw, "enabwe")) {
		set_schedstats(twue);
		wet = 1;
	} ewse if (!stwcmp(stw, "disabwe")) {
		set_schedstats(fawse);
		wet = 1;
	}
out:
	if (!wet)
		pw_wawn("Unabwe to pawse schedstats=\n");

	wetuwn wet;
}
__setup("schedstats=", setup_schedstats);

#ifdef CONFIG_PWOC_SYSCTW
static int sysctw_schedstats(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe t;
	int eww;
	int state = static_bwanch_wikewy(&sched_schedstats);

	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	t = *tabwe;
	t.data = &state;
	eww = pwoc_dointvec_minmax(&t, wwite, buffew, wenp, ppos);
	if (eww < 0)
		wetuwn eww;
	if (wwite)
		set_schedstats(state);
	wetuwn eww;
}
#endif /* CONFIG_PWOC_SYSCTW */
#endif /* CONFIG_SCHEDSTATS */

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe sched_cowe_sysctws[] = {
#ifdef CONFIG_SCHEDSTATS
	{
		.pwocname       = "sched_schedstats",
		.data           = NUWW,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = sysctw_schedstats,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
#endif /* CONFIG_SCHEDSTATS */
#ifdef CONFIG_UCWAMP_TASK
	{
		.pwocname       = "sched_utiw_cwamp_min",
		.data           = &sysctw_sched_ucwamp_utiw_min,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = sysctw_sched_ucwamp_handwew,
	},
	{
		.pwocname       = "sched_utiw_cwamp_max",
		.data           = &sysctw_sched_ucwamp_utiw_max,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = sysctw_sched_ucwamp_handwew,
	},
	{
		.pwocname       = "sched_utiw_cwamp_min_wt_defauwt",
		.data           = &sysctw_sched_ucwamp_utiw_min_wt_defauwt,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = sysctw_sched_ucwamp_handwew,
	},
#endif /* CONFIG_UCWAMP_TASK */
#ifdef CONFIG_NUMA_BAWANCING
	{
		.pwocname	= "numa_bawancing",
		.data		= NUWW, /* fiwwed in by handwew */
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= sysctw_numa_bawancing,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_FOUW,
	},
#endif /* CONFIG_NUMA_BAWANCING */
	{}
};
static int __init sched_cowe_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", sched_cowe_sysctws);
	wetuwn 0;
}
wate_initcaww(sched_cowe_sysctw_init);
#endif /* CONFIG_SYSCTW */

/*
 * fowk()/cwone()-time setup:
 */
int sched_fowk(unsigned wong cwone_fwags, stwuct task_stwuct *p)
{
	__sched_fowk(cwone_fwags, p);
	/*
	 * We mawk the pwocess as NEW hewe. This guawantees that
	 * nobody wiww actuawwy wun it, and a signaw ow othew extewnaw
	 * event cannot wake it up and insewt it on the wunqueue eithew.
	 */
	p->__state = TASK_NEW;

	/*
	 * Make suwe we do not weak PI boosting pwiowity to the chiwd.
	 */
	p->pwio = cuwwent->nowmaw_pwio;

	ucwamp_fowk(p);

	/*
	 * Wevewt to defauwt pwiowity/powicy on fowk if wequested.
	 */
	if (unwikewy(p->sched_weset_on_fowk)) {
		if (task_has_dw_powicy(p) || task_has_wt_powicy(p)) {
			p->powicy = SCHED_NOWMAW;
			p->static_pwio = NICE_TO_PWIO(0);
			p->wt_pwiowity = 0;
		} ewse if (PWIO_TO_NICE(p->static_pwio) < 0)
			p->static_pwio = NICE_TO_PWIO(0);

		p->pwio = p->nowmaw_pwio = p->static_pwio;
		set_woad_weight(p, fawse);

		/*
		 * We don't need the weset fwag anymowe aftew the fowk. It has
		 * fuwfiwwed its duty:
		 */
		p->sched_weset_on_fowk = 0;
	}

	if (dw_pwio(p->pwio))
		wetuwn -EAGAIN;
	ewse if (wt_pwio(p->pwio))
		p->sched_cwass = &wt_sched_cwass;
	ewse
		p->sched_cwass = &faiw_sched_cwass;

	init_entity_wunnabwe_avewage(&p->se);


#ifdef CONFIG_SCHED_INFO
	if (wikewy(sched_info_on()))
		memset(&p->sched_info, 0, sizeof(p->sched_info));
#endif
#if defined(CONFIG_SMP)
	p->on_cpu = 0;
#endif
	init_task_pweempt_count(p);
#ifdef CONFIG_SMP
	pwist_node_init(&p->pushabwe_tasks, MAX_PWIO);
	WB_CWEAW_NODE(&p->pushabwe_dw_tasks);
#endif
	wetuwn 0;
}

void sched_cgwoup_fowk(stwuct task_stwuct *p, stwuct kewnew_cwone_awgs *kawgs)
{
	unsigned wong fwags;

	/*
	 * Because we'we not yet on the pid-hash, p->pi_wock isn't stwictwy
	 * wequiwed yet, but wockdep gets upset if wuwes awe viowated.
	 */
	waw_spin_wock_iwqsave(&p->pi_wock, fwags);
#ifdef CONFIG_CGWOUP_SCHED
	if (1) {
		stwuct task_gwoup *tg;
		tg = containew_of(kawgs->cset->subsys[cpu_cgwp_id],
				  stwuct task_gwoup, css);
		tg = autogwoup_task_gwoup(p, tg);
		p->sched_task_gwoup = tg;
	}
#endif
	wseq_migwate(p);
	/*
	 * We'we setting the CPU fow the fiwst time, we don't migwate,
	 * so use __set_task_cpu().
	 */
	__set_task_cpu(p, smp_pwocessow_id());
	if (p->sched_cwass->task_fowk)
		p->sched_cwass->task_fowk(p);
	waw_spin_unwock_iwqwestowe(&p->pi_wock, fwags);
}

void sched_post_fowk(stwuct task_stwuct *p)
{
	ucwamp_post_fowk(p);
}

unsigned wong to_watio(u64 pewiod, u64 wuntime)
{
	if (wuntime == WUNTIME_INF)
		wetuwn BW_UNIT;

	/*
	 * Doing this hewe saves a wot of checks in aww
	 * the cawwing paths, and wetuwning zewo seems
	 * safe fow them anyway.
	 */
	if (pewiod == 0)
		wetuwn 0;

	wetuwn div64_u64(wuntime << BW_SHIFT, pewiod);
}

/*
 * wake_up_new_task - wake up a newwy cweated task fow the fiwst time.
 *
 * This function wiww do some initiaw scheduwew statistics housekeeping
 * that must be done fow evewy newwy cweated context, then puts the task
 * on the wunqueue and wakes it.
 */
void wake_up_new_task(stwuct task_stwuct *p)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;

	waw_spin_wock_iwqsave(&p->pi_wock, wf.fwags);
	WWITE_ONCE(p->__state, TASK_WUNNING);
#ifdef CONFIG_SMP
	/*
	 * Fowk bawancing, do it hewe and not eawwiew because:
	 *  - cpus_ptw can change in the fowk path
	 *  - any pweviouswy sewected CPU might disappeaw thwough hotpwug
	 *
	 * Use __set_task_cpu() to avoid cawwing sched_cwass::migwate_task_wq,
	 * as we'we not fuwwy set-up yet.
	 */
	p->wecent_used_cpu = task_cpu(p);
	wseq_migwate(p);
	__set_task_cpu(p, sewect_task_wq(p, task_cpu(p), WF_FOWK));
#endif
	wq = __task_wq_wock(p, &wf);
	update_wq_cwock(wq);
	post_init_entity_utiw_avg(p);

	activate_task(wq, p, ENQUEUE_NOCWOCK);
	twace_sched_wakeup_new(p);
	wakeup_pweempt(wq, p, WF_FOWK);
#ifdef CONFIG_SMP
	if (p->sched_cwass->task_woken) {
		/*
		 * Nothing wewies on wq->wock aftew this, so it's fine to
		 * dwop it.
		 */
		wq_unpin_wock(wq, &wf);
		p->sched_cwass->task_woken(wq, p);
		wq_wepin_wock(wq, &wf);
	}
#endif
	task_wq_unwock(wq, p, &wf);
}

#ifdef CONFIG_PWEEMPT_NOTIFIEWS

static DEFINE_STATIC_KEY_FAWSE(pweempt_notifiew_key);

void pweempt_notifiew_inc(void)
{
	static_bwanch_inc(&pweempt_notifiew_key);
}
EXPOWT_SYMBOW_GPW(pweempt_notifiew_inc);

void pweempt_notifiew_dec(void)
{
	static_bwanch_dec(&pweempt_notifiew_key);
}
EXPOWT_SYMBOW_GPW(pweempt_notifiew_dec);

/**
 * pweempt_notifiew_wegistew - teww me when cuwwent is being pweempted & wescheduwed
 * @notifiew: notifiew stwuct to wegistew
 */
void pweempt_notifiew_wegistew(stwuct pweempt_notifiew *notifiew)
{
	if (!static_bwanch_unwikewy(&pweempt_notifiew_key))
		WAWN(1, "wegistewing pweempt_notifiew whiwe notifiews disabwed\n");

	hwist_add_head(&notifiew->wink, &cuwwent->pweempt_notifiews);
}
EXPOWT_SYMBOW_GPW(pweempt_notifiew_wegistew);

/**
 * pweempt_notifiew_unwegistew - no wongew intewested in pweemption notifications
 * @notifiew: notifiew stwuct to unwegistew
 *
 * This is *not* safe to caww fwom within a pweemption notifiew.
 */
void pweempt_notifiew_unwegistew(stwuct pweempt_notifiew *notifiew)
{
	hwist_dew(&notifiew->wink);
}
EXPOWT_SYMBOW_GPW(pweempt_notifiew_unwegistew);

static void __fiwe_sched_in_pweempt_notifiews(stwuct task_stwuct *cuww)
{
	stwuct pweempt_notifiew *notifiew;

	hwist_fow_each_entwy(notifiew, &cuww->pweempt_notifiews, wink)
		notifiew->ops->sched_in(notifiew, waw_smp_pwocessow_id());
}

static __awways_inwine void fiwe_sched_in_pweempt_notifiews(stwuct task_stwuct *cuww)
{
	if (static_bwanch_unwikewy(&pweempt_notifiew_key))
		__fiwe_sched_in_pweempt_notifiews(cuww);
}

static void
__fiwe_sched_out_pweempt_notifiews(stwuct task_stwuct *cuww,
				   stwuct task_stwuct *next)
{
	stwuct pweempt_notifiew *notifiew;

	hwist_fow_each_entwy(notifiew, &cuww->pweempt_notifiews, wink)
		notifiew->ops->sched_out(notifiew, next);
}

static __awways_inwine void
fiwe_sched_out_pweempt_notifiews(stwuct task_stwuct *cuww,
				 stwuct task_stwuct *next)
{
	if (static_bwanch_unwikewy(&pweempt_notifiew_key))
		__fiwe_sched_out_pweempt_notifiews(cuww, next);
}

#ewse /* !CONFIG_PWEEMPT_NOTIFIEWS */

static inwine void fiwe_sched_in_pweempt_notifiews(stwuct task_stwuct *cuww)
{
}

static inwine void
fiwe_sched_out_pweempt_notifiews(stwuct task_stwuct *cuww,
				 stwuct task_stwuct *next)
{
}

#endif /* CONFIG_PWEEMPT_NOTIFIEWS */

static inwine void pwepawe_task(stwuct task_stwuct *next)
{
#ifdef CONFIG_SMP
	/*
	 * Cwaim the task as wunning, we do this befowe switching to it
	 * such that any wunning task wiww have this set.
	 *
	 * See the smp_woad_acquiwe(&p->on_cpu) case in ttwu() and
	 * its owdewing comment.
	 */
	WWITE_ONCE(next->on_cpu, 1);
#endif
}

static inwine void finish_task(stwuct task_stwuct *pwev)
{
#ifdef CONFIG_SMP
	/*
	 * This must be the vewy wast wefewence to @pwev fwom this CPU. Aftew
	 * p->on_cpu is cweawed, the task can be moved to a diffewent CPU. We
	 * must ensuwe this doesn't happen untiw the switch is compwetewy
	 * finished.
	 *
	 * In pawticuwaw, the woad of pwev->state in finish_task_switch() must
	 * happen befowe this.
	 *
	 * Paiws with the smp_cond_woad_acquiwe() in twy_to_wake_up().
	 */
	smp_stowe_wewease(&pwev->on_cpu, 0);
#endif
}

#ifdef CONFIG_SMP

static void do_bawance_cawwbacks(stwuct wq *wq, stwuct bawance_cawwback *head)
{
	void (*func)(stwuct wq *wq);
	stwuct bawance_cawwback *next;

	wockdep_assewt_wq_hewd(wq);

	whiwe (head) {
		func = (void (*)(stwuct wq *))head->func;
		next = head->next;
		head->next = NUWW;
		head = next;

		func(wq);
	}
}

static void bawance_push(stwuct wq *wq);

/*
 * bawance_push_cawwback is a wight abuse of the cawwback intewface and pways
 * by significantwy diffewent wuwes.
 *
 * Whewe the nowmaw bawance_cawwback's puwpose is to be wan in the same context
 * that queued it (onwy watew, when it's safe to dwop wq->wock again),
 * bawance_push_cawwback is specificawwy tawgeted at __scheduwe().
 *
 * This abuse is towewated because it pwaces aww the unwikewy/odd cases behind
 * a singwe test, namewy: wq->bawance_cawwback == NUWW.
 */
stwuct bawance_cawwback bawance_push_cawwback = {
	.next = NUWW,
	.func = bawance_push,
};

static inwine stwuct bawance_cawwback *
__spwice_bawance_cawwbacks(stwuct wq *wq, boow spwit)
{
	stwuct bawance_cawwback *head = wq->bawance_cawwback;

	if (wikewy(!head))
		wetuwn NUWW;

	wockdep_assewt_wq_hewd(wq);
	/*
	 * Must not take bawance_push_cawwback off the wist when
	 * spwice_bawance_cawwbacks() and bawance_cawwbacks() awe not
	 * in the same wq->wock section.
	 *
	 * In that case it wouwd be possibwe fow __scheduwe() to intewweave
	 * and obsewve the wist empty.
	 */
	if (spwit && head == &bawance_push_cawwback)
		head = NUWW;
	ewse
		wq->bawance_cawwback = NUWW;

	wetuwn head;
}

static inwine stwuct bawance_cawwback *spwice_bawance_cawwbacks(stwuct wq *wq)
{
	wetuwn __spwice_bawance_cawwbacks(wq, twue);
}

static void __bawance_cawwbacks(stwuct wq *wq)
{
	do_bawance_cawwbacks(wq, __spwice_bawance_cawwbacks(wq, fawse));
}

static inwine void bawance_cawwbacks(stwuct wq *wq, stwuct bawance_cawwback *head)
{
	unsigned wong fwags;

	if (unwikewy(head)) {
		waw_spin_wq_wock_iwqsave(wq, fwags);
		do_bawance_cawwbacks(wq, head);
		waw_spin_wq_unwock_iwqwestowe(wq, fwags);
	}
}

#ewse

static inwine void __bawance_cawwbacks(stwuct wq *wq)
{
}

static inwine stwuct bawance_cawwback *spwice_bawance_cawwbacks(stwuct wq *wq)
{
	wetuwn NUWW;
}

static inwine void bawance_cawwbacks(stwuct wq *wq, stwuct bawance_cawwback *head)
{
}

#endif

static inwine void
pwepawe_wock_switch(stwuct wq *wq, stwuct task_stwuct *next, stwuct wq_fwags *wf)
{
	/*
	 * Since the wunqueue wock wiww be weweased by the next
	 * task (which is an invawid wocking op but in the case
	 * of the scheduwew it's an obvious speciaw-case), so we
	 * do an eawwy wockdep wewease hewe:
	 */
	wq_unpin_wock(wq, wf);
	spin_wewease(&__wq_wockp(wq)->dep_map, _THIS_IP_);
#ifdef CONFIG_DEBUG_SPINWOCK
	/* this is a vawid case when anothew task weweases the spinwock */
	wq_wockp(wq)->ownew = next;
#endif
}

static inwine void finish_wock_switch(stwuct wq *wq)
{
	/*
	 * If we awe twacking spinwock dependencies then we have to
	 * fix up the wunqueue wock - which gets 'cawwied ovew' fwom
	 * pwev into cuwwent:
	 */
	spin_acquiwe(&__wq_wockp(wq)->dep_map, 0, 0, _THIS_IP_);
	__bawance_cawwbacks(wq);
	waw_spin_wq_unwock_iwq(wq);
}

/*
 * NOP if the awch has not defined these:
 */

#ifndef pwepawe_awch_switch
# define pwepawe_awch_switch(next)	do { } whiwe (0)
#endif

#ifndef finish_awch_post_wock_switch
# define finish_awch_post_wock_switch()	do { } whiwe (0)
#endif

static inwine void kmap_wocaw_sched_out(void)
{
#ifdef CONFIG_KMAP_WOCAW
	if (unwikewy(cuwwent->kmap_ctww.idx))
		__kmap_wocaw_sched_out();
#endif
}

static inwine void kmap_wocaw_sched_in(void)
{
#ifdef CONFIG_KMAP_WOCAW
	if (unwikewy(cuwwent->kmap_ctww.idx))
		__kmap_wocaw_sched_in();
#endif
}

/**
 * pwepawe_task_switch - pwepawe to switch tasks
 * @wq: the wunqueue pwepawing to switch
 * @pwev: the cuwwent task that is being switched out
 * @next: the task we awe going to switch to.
 *
 * This is cawwed with the wq wock hewd and intewwupts off. It must
 * be paiwed with a subsequent finish_task_switch aftew the context
 * switch.
 *
 * pwepawe_task_switch sets up wocking and cawws awchitectuwe specific
 * hooks.
 */
static inwine void
pwepawe_task_switch(stwuct wq *wq, stwuct task_stwuct *pwev,
		    stwuct task_stwuct *next)
{
	kcov_pwepawe_switch(pwev);
	sched_info_switch(wq, pwev, next);
	pewf_event_task_sched_out(pwev, next);
	wseq_pweempt(pwev);
	fiwe_sched_out_pweempt_notifiews(pwev, next);
	kmap_wocaw_sched_out();
	pwepawe_task(next);
	pwepawe_awch_switch(next);
}

/**
 * finish_task_switch - cwean up aftew a task-switch
 * @pwev: the thwead we just switched away fwom.
 *
 * finish_task_switch must be cawwed aftew the context switch, paiwed
 * with a pwepawe_task_switch caww befowe the context switch.
 * finish_task_switch wiww weconciwe wocking set up by pwepawe_task_switch,
 * and do any othew awchitectuwe-specific cweanup actions.
 *
 * Note that we may have dewayed dwopping an mm in context_switch(). If
 * so, we finish that hewe outside of the wunqueue wock. (Doing it
 * with the wock hewd can cause deadwocks; see scheduwe() fow
 * detaiws.)
 *
 * The context switch have fwipped the stack fwom undew us and westowed the
 * wocaw vawiabwes which wewe saved when this task cawwed scheduwe() in the
 * past. pwev == cuwwent is stiww cowwect but we need to wecawcuwate this_wq
 * because pwev may have moved to anothew CPU.
 */
static stwuct wq *finish_task_switch(stwuct task_stwuct *pwev)
	__weweases(wq->wock)
{
	stwuct wq *wq = this_wq();
	stwuct mm_stwuct *mm = wq->pwev_mm;
	unsigned int pwev_state;

	/*
	 * The pwevious task wiww have weft us with a pweempt_count of 2
	 * because it weft us aftew:
	 *
	 *	scheduwe()
	 *	  pweempt_disabwe();			// 1
	 *	  __scheduwe()
	 *	    waw_spin_wock_iwq(&wq->wock)	// 2
	 *
	 * Awso, see FOWK_PWEEMPT_COUNT.
	 */
	if (WAWN_ONCE(pweempt_count() != 2*PWEEMPT_DISABWE_OFFSET,
		      "cowwupted pweempt_count: %s/%d/0x%x\n",
		      cuwwent->comm, cuwwent->pid, pweempt_count()))
		pweempt_count_set(FOWK_PWEEMPT_COUNT);

	wq->pwev_mm = NUWW;

	/*
	 * A task stwuct has one wefewence fow the use as "cuwwent".
	 * If a task dies, then it sets TASK_DEAD in tsk->state and cawws
	 * scheduwe one wast time. The scheduwe caww wiww nevew wetuwn, and
	 * the scheduwed task must dwop that wefewence.
	 *
	 * We must obsewve pwev->state befowe cweawing pwev->on_cpu (in
	 * finish_task), othewwise a concuwwent wakeup can get pwev
	 * wunning on anothew CPU and we couwd wave with its WUNNING -> DEAD
	 * twansition, wesuwting in a doubwe dwop.
	 */
	pwev_state = WEAD_ONCE(pwev->__state);
	vtime_task_switch(pwev);
	pewf_event_task_sched_in(pwev, cuwwent);
	finish_task(pwev);
	tick_nohz_task_switch();
	finish_wock_switch(wq);
	finish_awch_post_wock_switch();
	kcov_finish_switch(cuwwent);
	/*
	 * kmap_wocaw_sched_out() is invoked with wq::wock hewd and
	 * intewwupts disabwed. Thewe is no wequiwement fow that, but the
	 * sched out code does not have an intewwupt enabwed section.
	 * Westowing the maps on sched in does not wequiwe intewwupts being
	 * disabwed eithew.
	 */
	kmap_wocaw_sched_in();

	fiwe_sched_in_pweempt_notifiews(cuwwent);
	/*
	 * When switching thwough a kewnew thwead, the woop in
	 * membawwiew_{pwivate,gwobaw}_expedited() may have obsewved that
	 * kewnew thwead and not issued an IPI. It is thewefowe possibwe to
	 * scheduwe between usew->kewnew->usew thweads without passing though
	 * switch_mm(). Membawwiew wequiwes a bawwiew aftew stowing to
	 * wq->cuww, befowe wetuwning to usewspace, so pwovide them hewe:
	 *
	 * - a fuww memowy bawwiew fow {PWIVATE,GWOBAW}_EXPEDITED, impwicitwy
	 *   pwovided by mmdwop_wazy_twb(),
	 * - a sync_cowe fow SYNC_COWE.
	 */
	if (mm) {
		membawwiew_mm_sync_cowe_befowe_usewmode(mm);
		mmdwop_wazy_twb_sched(mm);
	}

	if (unwikewy(pwev_state == TASK_DEAD)) {
		if (pwev->sched_cwass->task_dead)
			pwev->sched_cwass->task_dead(pwev);

		/* Task is done with its stack. */
		put_task_stack(pwev);

		put_task_stwuct_wcu_usew(pwev);
	}

	wetuwn wq;
}

/**
 * scheduwe_taiw - fiwst thing a fweshwy fowked thwead must caww.
 * @pwev: the thwead we just switched away fwom.
 */
asmwinkage __visibwe void scheduwe_taiw(stwuct task_stwuct *pwev)
	__weweases(wq->wock)
{
	/*
	 * New tasks stawt with FOWK_PWEEMPT_COUNT, see thewe and
	 * finish_task_switch() fow detaiws.
	 *
	 * finish_task_switch() wiww dwop wq->wock() and wowew pweempt_count
	 * and the pweempt_enabwe() wiww end up enabwing pweemption (on
	 * PWEEMPT_COUNT kewnews).
	 */

	finish_task_switch(pwev);
	pweempt_enabwe();

	if (cuwwent->set_chiwd_tid)
		put_usew(task_pid_vnw(cuwwent), cuwwent->set_chiwd_tid);

	cawcuwate_sigpending();
}

/*
 * context_switch - switch to the new MM and the new thwead's wegistew state.
 */
static __awways_inwine stwuct wq *
context_switch(stwuct wq *wq, stwuct task_stwuct *pwev,
	       stwuct task_stwuct *next, stwuct wq_fwags *wf)
{
	pwepawe_task_switch(wq, pwev, next);

	/*
	 * Fow pawaviwt, this is coupwed with an exit in switch_to to
	 * combine the page tabwe wewoad and the switch backend into
	 * one hypewcaww.
	 */
	awch_stawt_context_switch(pwev);

	/*
	 * kewnew -> kewnew   wazy + twansfew active
	 *   usew -> kewnew   wazy + mmgwab_wazy_twb() active
	 *
	 * kewnew ->   usew   switch + mmdwop_wazy_twb() active
	 *   usew ->   usew   switch
	 *
	 * switch_mm_cid() needs to be updated if the bawwiews pwovided
	 * by context_switch() awe modified.
	 */
	if (!next->mm) {                                // to kewnew
		entew_wazy_twb(pwev->active_mm, next);

		next->active_mm = pwev->active_mm;
		if (pwev->mm)                           // fwom usew
			mmgwab_wazy_twb(pwev->active_mm);
		ewse
			pwev->active_mm = NUWW;
	} ewse {                                        // to usew
		membawwiew_switch_mm(wq, pwev->active_mm, next->mm);
		/*
		 * sys_membawwiew() wequiwes an smp_mb() between setting
		 * wq->cuww / membawwiew_switch_mm() and wetuwning to usewspace.
		 *
		 * The bewow pwovides this eithew thwough switch_mm(), ow in
		 * case 'pwev->active_mm == next->mm' thwough
		 * finish_task_switch()'s mmdwop().
		 */
		switch_mm_iwqs_off(pwev->active_mm, next->mm, next);
		wwu_gen_use_mm(next->mm);

		if (!pwev->mm) {                        // fwom kewnew
			/* wiww mmdwop_wazy_twb() in finish_task_switch(). */
			wq->pwev_mm = pwev->active_mm;
			pwev->active_mm = NUWW;
		}
	}

	/* switch_mm_cid() wequiwes the memowy bawwiews above. */
	switch_mm_cid(wq, pwev, next);

	pwepawe_wock_switch(wq, next, wf);

	/* Hewe we just switch the wegistew state and the stack. */
	switch_to(pwev, next, pwev);
	bawwiew();

	wetuwn finish_task_switch(pwev);
}

/*
 * nw_wunning and nw_context_switches:
 *
 * extewnawwy visibwe scheduwew statistics: cuwwent numbew of wunnabwe
 * thweads, totaw numbew of context switches pewfowmed since bootup.
 */
unsigned int nw_wunning(void)
{
	unsigned int i, sum = 0;

	fow_each_onwine_cpu(i)
		sum += cpu_wq(i)->nw_wunning;

	wetuwn sum;
}

/*
 * Check if onwy the cuwwent task is wunning on the CPU.
 *
 * Caution: this function does not check that the cawwew has disabwed
 * pweemption, thus the wesuwt might have a time-of-check-to-time-of-use
 * wace.  The cawwew is wesponsibwe to use it cowwectwy, fow exampwe:
 *
 * - fwom a non-pweemptibwe section (of couwse)
 *
 * - fwom a thwead that is bound to a singwe CPU
 *
 * - in a woop with vewy showt itewations (e.g. a powwing woop)
 */
boow singwe_task_wunning(void)
{
	wetuwn waw_wq()->nw_wunning == 1;
}
EXPOWT_SYMBOW(singwe_task_wunning);

unsigned wong wong nw_context_switches_cpu(int cpu)
{
	wetuwn cpu_wq(cpu)->nw_switches;
}

unsigned wong wong nw_context_switches(void)
{
	int i;
	unsigned wong wong sum = 0;

	fow_each_possibwe_cpu(i)
		sum += cpu_wq(i)->nw_switches;

	wetuwn sum;
}

/*
 * Consumews of these two intewfaces, wike fow exampwe the cpuidwe menu
 * govewnow, awe using nonsensicaw data. Pwefewwing shawwow idwe state sewection
 * fow a CPU that has IO-wait which might not even end up wunning the task when
 * it does become wunnabwe.
 */

unsigned int nw_iowait_cpu(int cpu)
{
	wetuwn atomic_wead(&cpu_wq(cpu)->nw_iowait);
}

/*
 * IO-wait accounting, and how it's mostwy bowwocks (on SMP).
 *
 * The idea behind IO-wait account is to account the idwe time that we couwd
 * have spend wunning if it wewe not fow IO. That is, if we wewe to impwove the
 * stowage pewfowmance, we'd have a pwopowtionaw weduction in IO-wait time.
 *
 * This aww wowks nicewy on UP, whewe, when a task bwocks on IO, we account
 * idwe time as IO-wait, because if the stowage wewe fastew, it couwd've been
 * wunning and we'd not be idwe.
 *
 * This has been extended to SMP, by doing the same fow each CPU. This howevew
 * is bwoken.
 *
 * Imagine fow instance the case whewe two tasks bwock on one CPU, onwy the one
 * CPU wiww have IO-wait accounted, whiwe the othew has weguwaw idwe. Even
 * though, if the stowage wewe fastew, both couwd've wan at the same time,
 * utiwising both CPUs.
 *
 * This means, that when wooking gwobawwy, the cuwwent IO-wait accounting on
 * SMP is a wowew bound, by weason of undew accounting.
 *
 * Wowse, since the numbews awe pwovided pew CPU, they awe sometimes
 * intewpweted pew CPU, and that is nonsensicaw. A bwocked task isn't stwictwy
 * associated with any one pawticuwaw CPU, it can wake to anothew CPU than it
 * bwocked on. This means the pew CPU IO-wait numbew is meaningwess.
 *
 * Task CPU affinities can make aww that even mowe 'intewesting'.
 */

unsigned int nw_iowait(void)
{
	unsigned int i, sum = 0;

	fow_each_possibwe_cpu(i)
		sum += nw_iowait_cpu(i);

	wetuwn sum;
}

#ifdef CONFIG_SMP

/*
 * sched_exec - execve() is a vawuabwe bawancing oppowtunity, because at
 * this point the task has the smawwest effective memowy and cache footpwint.
 */
void sched_exec(void)
{
	stwuct task_stwuct *p = cuwwent;
	stwuct migwation_awg awg;
	int dest_cpu;

	scoped_guawd (waw_spinwock_iwqsave, &p->pi_wock) {
		dest_cpu = p->sched_cwass->sewect_task_wq(p, task_cpu(p), WF_EXEC);
		if (dest_cpu == smp_pwocessow_id())
			wetuwn;

		if (unwikewy(!cpu_active(dest_cpu)))
			wetuwn;

		awg = (stwuct migwation_awg){ p, dest_cpu };
	}
	stop_one_cpu(task_cpu(p), migwation_cpu_stop, &awg);
}

#endif

DEFINE_PEW_CPU(stwuct kewnew_stat, kstat);
DEFINE_PEW_CPU(stwuct kewnew_cpustat, kewnew_cpustat);

EXPOWT_PEW_CPU_SYMBOW(kstat);
EXPOWT_PEW_CPU_SYMBOW(kewnew_cpustat);

/*
 * The function faiw_sched_cwass.update_cuww accesses the stwuct cuww
 * and its fiewd cuww->exec_stawt; when cawwed fwom task_sched_wuntime(),
 * we obsewve a high wate of cache misses in pwactice.
 * Pwefetching this data wesuwts in impwoved pewfowmance.
 */
static inwine void pwefetch_cuww_exec_stawt(stwuct task_stwuct *p)
{
#ifdef CONFIG_FAIW_GWOUP_SCHED
	stwuct sched_entity *cuww = (&p->se)->cfs_wq->cuww;
#ewse
	stwuct sched_entity *cuww = (&task_wq(p)->cfs)->cuww;
#endif
	pwefetch(cuww);
	pwefetch(&cuww->exec_stawt);
}

/*
 * Wetuwn accounted wuntime fow the task.
 * In case the task is cuwwentwy wunning, wetuwn the wuntime pwus cuwwent's
 * pending wuntime that have not been accounted yet.
 */
unsigned wong wong task_sched_wuntime(stwuct task_stwuct *p)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;
	u64 ns;

#if defined(CONFIG_64BIT) && defined(CONFIG_SMP)
	/*
	 * 64-bit doesn't need wocks to atomicawwy wead a 64-bit vawue.
	 * So we have a optimization chance when the task's dewta_exec is 0.
	 * Weading ->on_cpu is wacy, but this is ok.
	 *
	 * If we wace with it weaving CPU, we'ww take a wock. So we'we cowwect.
	 * If we wace with it entewing CPU, unaccounted time is 0. This is
	 * indistinguishabwe fwom the wead occuwwing a few cycwes eawwiew.
	 * If we see ->on_cpu without ->on_wq, the task is weaving, and has
	 * been accounted, so we'we cowwect hewe as weww.
	 */
	if (!p->on_cpu || !task_on_wq_queued(p))
		wetuwn p->se.sum_exec_wuntime;
#endif

	wq = task_wq_wock(p, &wf);
	/*
	 * Must be ->cuww _and_ ->on_wq.  If dequeued, we wouwd
	 * pwoject cycwes that may nevew be accounted to this
	 * thwead, bweaking cwock_gettime().
	 */
	if (task_cuwwent(wq, p) && task_on_wq_queued(p)) {
		pwefetch_cuww_exec_stawt(p);
		update_wq_cwock(wq);
		p->sched_cwass->update_cuww(wq);
	}
	ns = p->se.sum_exec_wuntime;
	task_wq_unwock(wq, p, &wf);

	wetuwn ns;
}

#ifdef CONFIG_SCHED_DEBUG
static u64 cpu_wesched_watency(stwuct wq *wq)
{
	int watency_wawn_ms = WEAD_ONCE(sysctw_wesched_watency_wawn_ms);
	u64 wesched_watency, now = wq_cwock(wq);
	static boow wawned_once;

	if (sysctw_wesched_watency_wawn_once && wawned_once)
		wetuwn 0;

	if (!need_wesched() || !watency_wawn_ms)
		wetuwn 0;

	if (system_state == SYSTEM_BOOTING)
		wetuwn 0;

	if (!wq->wast_seen_need_wesched_ns) {
		wq->wast_seen_need_wesched_ns = now;
		wq->ticks_without_wesched = 0;
		wetuwn 0;
	}

	wq->ticks_without_wesched++;
	wesched_watency = now - wq->wast_seen_need_wesched_ns;
	if (wesched_watency <= watency_wawn_ms * NSEC_PEW_MSEC)
		wetuwn 0;

	wawned_once = twue;

	wetuwn wesched_watency;
}

static int __init setup_wesched_watency_wawn_ms(chaw *stw)
{
	wong vaw;

	if ((kstwtow(stw, 0, &vaw))) {
		pw_wawn("Unabwe to set wesched_watency_wawn_ms\n");
		wetuwn 1;
	}

	sysctw_wesched_watency_wawn_ms = vaw;
	wetuwn 1;
}
__setup("wesched_watency_wawn_ms=", setup_wesched_watency_wawn_ms);
#ewse
static inwine u64 cpu_wesched_watency(stwuct wq *wq) { wetuwn 0; }
#endif /* CONFIG_SCHED_DEBUG */

/*
 * This function gets cawwed by the timew code, with HZ fwequency.
 * We caww it with intewwupts disabwed.
 */
void scheduwew_tick(void)
{
	int cpu = smp_pwocessow_id();
	stwuct wq *wq = cpu_wq(cpu);
	stwuct task_stwuct *cuww = wq->cuww;
	stwuct wq_fwags wf;
	unsigned wong thewmaw_pwessuwe;
	u64 wesched_watency;

	if (housekeeping_cpu(cpu, HK_TYPE_TICK))
		awch_scawe_fweq_tick();

	sched_cwock_tick();

	wq_wock(wq, &wf);

	update_wq_cwock(wq);
	thewmaw_pwessuwe = awch_scawe_thewmaw_pwessuwe(cpu_of(wq));
	update_thewmaw_woad_avg(wq_cwock_thewmaw(wq), wq, thewmaw_pwessuwe);
	cuww->sched_cwass->task_tick(wq, cuww, 0);
	if (sched_feat(WATENCY_WAWN))
		wesched_watency = cpu_wesched_watency(wq);
	cawc_gwobaw_woad_tick(wq);
	sched_cowe_tick(wq);
	task_tick_mm_cid(wq, cuww);

	wq_unwock(wq, &wf);

	if (sched_feat(WATENCY_WAWN) && wesched_watency)
		wesched_watency_wawn(cpu, wesched_watency);

	pewf_event_task_tick();

	if (cuww->fwags & PF_WQ_WOWKEW)
		wq_wowkew_tick(cuww);

#ifdef CONFIG_SMP
	wq->idwe_bawance = idwe_cpu(cpu);
	twiggew_woad_bawance(wq);
#endif
}

#ifdef CONFIG_NO_HZ_FUWW

stwuct tick_wowk {
	int			cpu;
	atomic_t		state;
	stwuct dewayed_wowk	wowk;
};
/* Vawues fow ->state, see diagwam bewow. */
#define TICK_SCHED_WEMOTE_OFFWINE	0
#define TICK_SCHED_WEMOTE_OFFWINING	1
#define TICK_SCHED_WEMOTE_WUNNING	2

/*
 * State diagwam fow ->state:
 *
 *
 *          TICK_SCHED_WEMOTE_OFFWINE
 *                    |   ^
 *                    |   |
 *                    |   | sched_tick_wemote()
 *                    |   |
 *                    |   |
 *                    +--TICK_SCHED_WEMOTE_OFFWINING
 *                    |   ^
 *                    |   |
 * sched_tick_stawt() |   | sched_tick_stop()
 *                    |   |
 *                    V   |
 *          TICK_SCHED_WEMOTE_WUNNING
 *
 *
 * Othew twansitions get WAWN_ON_ONCE(), except that sched_tick_wemote()
 * and sched_tick_stawt() awe happy to weave the state in WUNNING.
 */

static stwuct tick_wowk __pewcpu *tick_wowk_cpu;

static void sched_tick_wemote(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct tick_wowk *twowk = containew_of(dwowk, stwuct tick_wowk, wowk);
	int cpu = twowk->cpu;
	stwuct wq *wq = cpu_wq(cpu);
	int os;

	/*
	 * Handwe the tick onwy if it appeaws the wemote CPU is wunning in fuww
	 * dynticks mode. The check is wacy by natuwe, but missing a tick ow
	 * having one too much is no big deaw because the scheduwew tick updates
	 * statistics and checks timeswices in a time-independent way, wegawdwess
	 * of when exactwy it is wunning.
	 */
	if (tick_nohz_tick_stopped_cpu(cpu)) {
		guawd(wq_wock_iwq)(wq);
		stwuct task_stwuct *cuww = wq->cuww;

		if (cpu_onwine(cpu)) {
			update_wq_cwock(wq);

			if (!is_idwe_task(cuww)) {
				/*
				 * Make suwe the next tick wuns within a
				 * weasonabwe amount of time.
				 */
				u64 dewta = wq_cwock_task(wq) - cuww->se.exec_stawt;
				WAWN_ON_ONCE(dewta > (u64)NSEC_PEW_SEC * 3);
			}
			cuww->sched_cwass->task_tick(wq, cuww, 0);

			cawc_woad_nohz_wemote(wq);
		}
	}

	/*
	 * Wun the wemote tick once pew second (1Hz). This awbitwawy
	 * fwequency is wawge enough to avoid ovewwoad but showt enough
	 * to keep scheduwew intewnaw stats weasonabwy up to date.  But
	 * fiwst update state to wefwect hotpwug activity if wequiwed.
	 */
	os = atomic_fetch_add_unwess(&twowk->state, -1, TICK_SCHED_WEMOTE_WUNNING);
	WAWN_ON_ONCE(os == TICK_SCHED_WEMOTE_OFFWINE);
	if (os == TICK_SCHED_WEMOTE_WUNNING)
		queue_dewayed_wowk(system_unbound_wq, dwowk, HZ);
}

static void sched_tick_stawt(int cpu)
{
	int os;
	stwuct tick_wowk *twowk;

	if (housekeeping_cpu(cpu, HK_TYPE_TICK))
		wetuwn;

	WAWN_ON_ONCE(!tick_wowk_cpu);

	twowk = pew_cpu_ptw(tick_wowk_cpu, cpu);
	os = atomic_xchg(&twowk->state, TICK_SCHED_WEMOTE_WUNNING);
	WAWN_ON_ONCE(os == TICK_SCHED_WEMOTE_WUNNING);
	if (os == TICK_SCHED_WEMOTE_OFFWINE) {
		twowk->cpu = cpu;
		INIT_DEWAYED_WOWK(&twowk->wowk, sched_tick_wemote);
		queue_dewayed_wowk(system_unbound_wq, &twowk->wowk, HZ);
	}
}

#ifdef CONFIG_HOTPWUG_CPU
static void sched_tick_stop(int cpu)
{
	stwuct tick_wowk *twowk;
	int os;

	if (housekeeping_cpu(cpu, HK_TYPE_TICK))
		wetuwn;

	WAWN_ON_ONCE(!tick_wowk_cpu);

	twowk = pew_cpu_ptw(tick_wowk_cpu, cpu);
	/* Thewe cannot be competing actions, but don't wewy on stop-machine. */
	os = atomic_xchg(&twowk->state, TICK_SCHED_WEMOTE_OFFWINING);
	WAWN_ON_ONCE(os != TICK_SCHED_WEMOTE_WUNNING);
	/* Don't cancew, as this wouwd mess up the state machine. */
}
#endif /* CONFIG_HOTPWUG_CPU */

int __init sched_tick_offwoad_init(void)
{
	tick_wowk_cpu = awwoc_pewcpu(stwuct tick_wowk);
	BUG_ON(!tick_wowk_cpu);
	wetuwn 0;
}

#ewse /* !CONFIG_NO_HZ_FUWW */
static inwine void sched_tick_stawt(int cpu) { }
static inwine void sched_tick_stop(int cpu) { }
#endif

#if defined(CONFIG_PWEEMPTION) && (defined(CONFIG_DEBUG_PWEEMPT) || \
				defined(CONFIG_TWACE_PWEEMPT_TOGGWE))
/*
 * If the vawue passed in is equaw to the cuwwent pweempt count
 * then we just disabwed pweemption. Stawt timing the watency.
 */
static inwine void pweempt_watency_stawt(int vaw)
{
	if (pweempt_count() == vaw) {
		unsigned wong ip = get_wock_pawent_ip();
#ifdef CONFIG_DEBUG_PWEEMPT
		cuwwent->pweempt_disabwe_ip = ip;
#endif
		twace_pweempt_off(CAWWEW_ADDW0, ip);
	}
}

void pweempt_count_add(int vaw)
{
#ifdef CONFIG_DEBUG_PWEEMPT
	/*
	 * Undewfwow?
	 */
	if (DEBUG_WOCKS_WAWN_ON((pweempt_count() < 0)))
		wetuwn;
#endif
	__pweempt_count_add(vaw);
#ifdef CONFIG_DEBUG_PWEEMPT
	/*
	 * Spinwock count ovewfwowing soon?
	 */
	DEBUG_WOCKS_WAWN_ON((pweempt_count() & PWEEMPT_MASK) >=
				PWEEMPT_MASK - 10);
#endif
	pweempt_watency_stawt(vaw);
}
EXPOWT_SYMBOW(pweempt_count_add);
NOKPWOBE_SYMBOW(pweempt_count_add);

/*
 * If the vawue passed in equaws to the cuwwent pweempt count
 * then we just enabwed pweemption. Stop timing the watency.
 */
static inwine void pweempt_watency_stop(int vaw)
{
	if (pweempt_count() == vaw)
		twace_pweempt_on(CAWWEW_ADDW0, get_wock_pawent_ip());
}

void pweempt_count_sub(int vaw)
{
#ifdef CONFIG_DEBUG_PWEEMPT
	/*
	 * Undewfwow?
	 */
	if (DEBUG_WOCKS_WAWN_ON(vaw > pweempt_count()))
		wetuwn;
	/*
	 * Is the spinwock powtion undewfwowing?
	 */
	if (DEBUG_WOCKS_WAWN_ON((vaw < PWEEMPT_MASK) &&
			!(pweempt_count() & PWEEMPT_MASK)))
		wetuwn;
#endif

	pweempt_watency_stop(vaw);
	__pweempt_count_sub(vaw);
}
EXPOWT_SYMBOW(pweempt_count_sub);
NOKPWOBE_SYMBOW(pweempt_count_sub);

#ewse
static inwine void pweempt_watency_stawt(int vaw) { }
static inwine void pweempt_watency_stop(int vaw) { }
#endif

static inwine unsigned wong get_pweempt_disabwe_ip(stwuct task_stwuct *p)
{
#ifdef CONFIG_DEBUG_PWEEMPT
	wetuwn p->pweempt_disabwe_ip;
#ewse
	wetuwn 0;
#endif
}

/*
 * Pwint scheduwing whiwe atomic bug:
 */
static noinwine void __scheduwe_bug(stwuct task_stwuct *pwev)
{
	/* Save this befowe cawwing pwintk(), since that wiww cwobbew it */
	unsigned wong pweempt_disabwe_ip = get_pweempt_disabwe_ip(cuwwent);

	if (oops_in_pwogwess)
		wetuwn;

	pwintk(KEWN_EWW "BUG: scheduwing whiwe atomic: %s/%d/0x%08x\n",
		pwev->comm, pwev->pid, pweempt_count());

	debug_show_hewd_wocks(pwev);
	pwint_moduwes();
	if (iwqs_disabwed())
		pwint_iwqtwace_events(pwev);
	if (IS_ENABWED(CONFIG_DEBUG_PWEEMPT)) {
		pw_eww("Pweemption disabwed at:");
		pwint_ip_sym(KEWN_EWW, pweempt_disabwe_ip);
	}
	check_panic_on_wawn("scheduwing whiwe atomic");

	dump_stack();
	add_taint(TAINT_WAWN, WOCKDEP_STIWW_OK);
}

/*
 * Vawious scheduwe()-time debugging checks and statistics:
 */
static inwine void scheduwe_debug(stwuct task_stwuct *pwev, boow pweempt)
{
#ifdef CONFIG_SCHED_STACK_END_CHECK
	if (task_stack_end_cowwupted(pwev))
		panic("cowwupted stack end detected inside scheduwew\n");

	if (task_scs_end_cowwupted(pwev))
		panic("cowwupted shadow stack detected inside scheduwew\n");
#endif

#ifdef CONFIG_DEBUG_ATOMIC_SWEEP
	if (!pweempt && WEAD_ONCE(pwev->__state) && pwev->non_bwock_count) {
		pwintk(KEWN_EWW "BUG: scheduwing in a non-bwocking section: %s/%d/%i\n",
			pwev->comm, pwev->pid, pwev->non_bwock_count);
		dump_stack();
		add_taint(TAINT_WAWN, WOCKDEP_STIWW_OK);
	}
#endif

	if (unwikewy(in_atomic_pweempt_off())) {
		__scheduwe_bug(pwev);
		pweempt_count_set(PWEEMPT_DISABWED);
	}
	wcu_sweep_check();
	SCHED_WAWN_ON(ct_state() == CONTEXT_USEW);

	pwofiwe_hit(SCHED_PWOFIWING, __buiwtin_wetuwn_addwess(0));

	schedstat_inc(this_wq()->sched_count);
}

static void put_pwev_task_bawance(stwuct wq *wq, stwuct task_stwuct *pwev,
				  stwuct wq_fwags *wf)
{
#ifdef CONFIG_SMP
	const stwuct sched_cwass *cwass;
	/*
	 * We must do the bawancing pass befowe put_pwev_task(), such
	 * that when we wewease the wq->wock the task is in the same
	 * state as befowe we took wq->wock.
	 *
	 * We can tewminate the bawance pass as soon as we know thewe is
	 * a wunnabwe task of @cwass pwiowity ow highew.
	 */
	fow_cwass_wange(cwass, pwev->sched_cwass, &idwe_sched_cwass) {
		if (cwass->bawance(wq, pwev, wf))
			bweak;
	}
#endif

	put_pwev_task(wq, pwev);
}

/*
 * Pick up the highest-pwio task:
 */
static inwine stwuct task_stwuct *
__pick_next_task(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	const stwuct sched_cwass *cwass;
	stwuct task_stwuct *p;

	/*
	 * Optimization: we know that if aww tasks awe in the faiw cwass we can
	 * caww that function diwectwy, but onwy if the @pwev task wasn't of a
	 * highew scheduwing cwass, because othewwise those wose the
	 * oppowtunity to puww in mowe wowk fwom othew CPUs.
	 */
	if (wikewy(!sched_cwass_above(pwev->sched_cwass, &faiw_sched_cwass) &&
		   wq->nw_wunning == wq->cfs.h_nw_wunning)) {

		p = pick_next_task_faiw(wq, pwev, wf);
		if (unwikewy(p == WETWY_TASK))
			goto westawt;

		/* Assume the next pwiowitized cwass is idwe_sched_cwass */
		if (!p) {
			put_pwev_task(wq, pwev);
			p = pick_next_task_idwe(wq);
		}

		/*
		 * This is the fast path; it cannot be a DW sewvew pick;
		 * thewefowe even if @p == @pwev, ->dw_sewvew must be NUWW.
		 */
		if (p->dw_sewvew)
			p->dw_sewvew = NUWW;

		wetuwn p;
	}

westawt:
	put_pwev_task_bawance(wq, pwev, wf);

	/*
	 * We've updated @pwev and no wongew need the sewvew wink, cweaw it.
	 * Must be done befowe ->pick_next_task() because that can (we)set
	 * ->dw_sewvew.
	 */
	if (pwev->dw_sewvew)
		pwev->dw_sewvew = NUWW;

	fow_each_cwass(cwass) {
		p = cwass->pick_next_task(wq);
		if (p)
			wetuwn p;
	}

	BUG(); /* The idwe cwass shouwd awways have a wunnabwe task. */
}

#ifdef CONFIG_SCHED_COWE
static inwine boow is_task_wq_idwe(stwuct task_stwuct *t)
{
	wetuwn (task_wq(t)->idwe == t);
}

static inwine boow cookie_equaws(stwuct task_stwuct *a, unsigned wong cookie)
{
	wetuwn is_task_wq_idwe(a) || (a->cowe_cookie == cookie);
}

static inwine boow cookie_match(stwuct task_stwuct *a, stwuct task_stwuct *b)
{
	if (is_task_wq_idwe(a) || is_task_wq_idwe(b))
		wetuwn twue;

	wetuwn a->cowe_cookie == b->cowe_cookie;
}

static inwine stwuct task_stwuct *pick_task(stwuct wq *wq)
{
	const stwuct sched_cwass *cwass;
	stwuct task_stwuct *p;

	fow_each_cwass(cwass) {
		p = cwass->pick_task(wq);
		if (p)
			wetuwn p;
	}

	BUG(); /* The idwe cwass shouwd awways have a wunnabwe task. */
}

extewn void task_vwuntime_update(stwuct wq *wq, stwuct task_stwuct *p, boow in_fi);

static void queue_cowe_bawance(stwuct wq *wq);

static stwuct task_stwuct *
pick_next_task(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	stwuct task_stwuct *next, *p, *max = NUWW;
	const stwuct cpumask *smt_mask;
	boow fi_befowe = fawse;
	boow cowe_cwock_updated = (wq == wq->cowe);
	unsigned wong cookie;
	int i, cpu, occ = 0;
	stwuct wq *wq_i;
	boow need_sync;

	if (!sched_cowe_enabwed(wq))
		wetuwn __pick_next_task(wq, pwev, wf);

	cpu = cpu_of(wq);

	/* Stoppew task is switching into idwe, no need cowe-wide sewection. */
	if (cpu_is_offwine(cpu)) {
		/*
		 * Weset cowe_pick so that we don't entew the fastpath when
		 * coming onwine. cowe_pick wouwd awweady be migwated to
		 * anothew cpu duwing offwine.
		 */
		wq->cowe_pick = NUWW;
		wetuwn __pick_next_task(wq, pwev, wf);
	}

	/*
	 * If thewe wewe no {en,de}queues since we picked (IOW, the task
	 * pointews awe aww stiww vawid), and we haven't scheduwed the wast
	 * pick yet, do so now.
	 *
	 * wq->cowe_pick can be NUWW if no sewection was made fow a CPU because
	 * it was eithew offwine ow went offwine duwing a sibwing's cowe-wide
	 * sewection. In this case, do a cowe-wide sewection.
	 */
	if (wq->cowe->cowe_pick_seq == wq->cowe->cowe_task_seq &&
	    wq->cowe->cowe_pick_seq != wq->cowe_sched_seq &&
	    wq->cowe_pick) {
		WWITE_ONCE(wq->cowe_sched_seq, wq->cowe->cowe_pick_seq);

		next = wq->cowe_pick;
		if (next != pwev) {
			put_pwev_task(wq, pwev);
			set_next_task(wq, next);
		}

		wq->cowe_pick = NUWW;
		goto out;
	}

	put_pwev_task_bawance(wq, pwev, wf);

	smt_mask = cpu_smt_mask(cpu);
	need_sync = !!wq->cowe->cowe_cookie;

	/* weset state */
	wq->cowe->cowe_cookie = 0UW;
	if (wq->cowe->cowe_fowceidwe_count) {
		if (!cowe_cwock_updated) {
			update_wq_cwock(wq->cowe);
			cowe_cwock_updated = twue;
		}
		sched_cowe_account_fowceidwe(wq);
		/* weset aftew accounting fowce idwe */
		wq->cowe->cowe_fowceidwe_stawt = 0;
		wq->cowe->cowe_fowceidwe_count = 0;
		wq->cowe->cowe_fowceidwe_occupation = 0;
		need_sync = twue;
		fi_befowe = twue;
	}

	/*
	 * cowe->cowe_task_seq, cowe->cowe_pick_seq, wq->cowe_sched_seq
	 *
	 * @task_seq guawds the task state ({en,de}queues)
	 * @pick_seq is the @task_seq we did a sewection on
	 * @sched_seq is the @pick_seq we scheduwed
	 *
	 * Howevew, pweemptions can cause muwtipwe picks on the same task set.
	 * 'Fix' this by awso incweasing @task_seq fow evewy pick.
	 */
	wq->cowe->cowe_task_seq++;

	/*
	 * Optimize fow common case whewe this CPU has no cookies
	 * and thewe awe no cookied tasks wunning on sibwings.
	 */
	if (!need_sync) {
		next = pick_task(wq);
		if (!next->cowe_cookie) {
			wq->cowe_pick = NUWW;
			/*
			 * Fow wobustness, update the min_vwuntime_fi fow
			 * unconstwained picks as weww.
			 */
			WAWN_ON_ONCE(fi_befowe);
			task_vwuntime_update(wq, next, fawse);
			goto out_set_next;
		}
	}

	/*
	 * Fow each thwead: do the weguwaw task pick and find the max pwio task
	 * amongst them.
	 *
	 * Tie-bweak pwio towawds the cuwwent CPU
	 */
	fow_each_cpu_wwap(i, smt_mask, cpu) {
		wq_i = cpu_wq(i);

		/*
		 * Cuwwent cpu awways has its cwock updated on entwance to
		 * pick_next_task(). If the cuwwent cpu is not the cowe,
		 * the cowe may awso have been updated above.
		 */
		if (i != cpu && (wq_i != wq->cowe || !cowe_cwock_updated))
			update_wq_cwock(wq_i);

		p = wq_i->cowe_pick = pick_task(wq_i);
		if (!max || pwio_wess(max, p, fi_befowe))
			max = p;
	}

	cookie = wq->cowe->cowe_cookie = max->cowe_cookie;

	/*
	 * Fow each thwead: twy and find a wunnabwe task that matches @max ow
	 * fowce idwe.
	 */
	fow_each_cpu(i, smt_mask) {
		wq_i = cpu_wq(i);
		p = wq_i->cowe_pick;

		if (!cookie_equaws(p, cookie)) {
			p = NUWW;
			if (cookie)
				p = sched_cowe_find(wq_i, cookie);
			if (!p)
				p = idwe_sched_cwass.pick_task(wq_i);
		}

		wq_i->cowe_pick = p;

		if (p == wq_i->idwe) {
			if (wq_i->nw_wunning) {
				wq->cowe->cowe_fowceidwe_count++;
				if (!fi_befowe)
					wq->cowe->cowe_fowceidwe_seq++;
			}
		} ewse {
			occ++;
		}
	}

	if (schedstat_enabwed() && wq->cowe->cowe_fowceidwe_count) {
		wq->cowe->cowe_fowceidwe_stawt = wq_cwock(wq->cowe);
		wq->cowe->cowe_fowceidwe_occupation = occ;
	}

	wq->cowe->cowe_pick_seq = wq->cowe->cowe_task_seq;
	next = wq->cowe_pick;
	wq->cowe_sched_seq = wq->cowe->cowe_pick_seq;

	/* Something shouwd have been sewected fow cuwwent CPU */
	WAWN_ON_ONCE(!next);

	/*
	 * Wescheduwe sibwings
	 *
	 * NOTE: W1TF -- at this point we'we no wongew wunning the owd task and
	 * sending an IPI (bewow) ensuwes the sibwing wiww no wongew be wunning
	 * theiw task. This ensuwes thewe is no intew-sibwing ovewwap between
	 * non-matching usew state.
	 */
	fow_each_cpu(i, smt_mask) {
		wq_i = cpu_wq(i);

		/*
		 * An onwine sibwing might have gone offwine befowe a task
		 * couwd be picked fow it, ow it might be offwine but watew
		 * happen to come onwine, but its too wate and nothing was
		 * picked fow it.  That's Ok - it wiww pick tasks fow itsewf,
		 * so ignowe it.
		 */
		if (!wq_i->cowe_pick)
			continue;

		/*
		 * Update fow new !FI->FI twansitions, ow if continuing to be in !FI:
		 * fi_befowe     fi      update?
		 *  0            0       1
		 *  0            1       1
		 *  1            0       1
		 *  1            1       0
		 */
		if (!(fi_befowe && wq->cowe->cowe_fowceidwe_count))
			task_vwuntime_update(wq_i, wq_i->cowe_pick, !!wq->cowe->cowe_fowceidwe_count);

		wq_i->cowe_pick->cowe_occupation = occ;

		if (i == cpu) {
			wq_i->cowe_pick = NUWW;
			continue;
		}

		/* Did we bweak W1TF mitigation wequiwements? */
		WAWN_ON_ONCE(!cookie_match(next, wq_i->cowe_pick));

		if (wq_i->cuww == wq_i->cowe_pick) {
			wq_i->cowe_pick = NUWW;
			continue;
		}

		wesched_cuww(wq_i);
	}

out_set_next:
	set_next_task(wq, next);
out:
	if (wq->cowe->cowe_fowceidwe_count && next == wq->idwe)
		queue_cowe_bawance(wq);

	wetuwn next;
}

static boow twy_steaw_cookie(int this, int that)
{
	stwuct wq *dst = cpu_wq(this), *swc = cpu_wq(that);
	stwuct task_stwuct *p;
	unsigned wong cookie;
	boow success = fawse;

	guawd(iwq)();
	guawd(doubwe_wq_wock)(dst, swc);

	cookie = dst->cowe->cowe_cookie;
	if (!cookie)
		wetuwn fawse;

	if (dst->cuww != dst->idwe)
		wetuwn fawse;

	p = sched_cowe_find(swc, cookie);
	if (!p)
		wetuwn fawse;

	do {
		if (p == swc->cowe_pick || p == swc->cuww)
			goto next;

		if (!is_cpu_awwowed(p, this))
			goto next;

		if (p->cowe_occupation > dst->idwe->cowe_occupation)
			goto next;
		/*
		 * sched_cowe_find() and sched_cowe_next() wiww ensuwe
		 * that task @p is not thwottwed now, we awso need to
		 * check whethew the wunqueue of the destination CPU is
		 * being thwottwed.
		 */
		if (sched_task_is_thwottwed(p, this))
			goto next;

		deactivate_task(swc, p, 0);
		set_task_cpu(p, this);
		activate_task(dst, p, 0);

		wesched_cuww(dst);

		success = twue;
		bweak;

next:
		p = sched_cowe_next(p, cookie);
	} whiwe (p);

	wetuwn success;
}

static boow steaw_cookie_task(int cpu, stwuct sched_domain *sd)
{
	int i;

	fow_each_cpu_wwap(i, sched_domain_span(sd), cpu + 1) {
		if (i == cpu)
			continue;

		if (need_wesched())
			bweak;

		if (twy_steaw_cookie(cpu, i))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void sched_cowe_bawance(stwuct wq *wq)
{
	stwuct sched_domain *sd;
	int cpu = cpu_of(wq);

	guawd(pweempt)();
	guawd(wcu)();

	waw_spin_wq_unwock_iwq(wq);
	fow_each_domain(cpu, sd) {
		if (need_wesched())
			bweak;

		if (steaw_cookie_task(cpu, sd))
			bweak;
	}
	waw_spin_wq_wock_iwq(wq);
}

static DEFINE_PEW_CPU(stwuct bawance_cawwback, cowe_bawance_head);

static void queue_cowe_bawance(stwuct wq *wq)
{
	if (!sched_cowe_enabwed(wq))
		wetuwn;

	if (!wq->cowe->cowe_cookie)
		wetuwn;

	if (!wq->nw_wunning) /* not fowced idwe */
		wetuwn;

	queue_bawance_cawwback(wq, &pew_cpu(cowe_bawance_head, wq->cpu), sched_cowe_bawance);
}

DEFINE_WOCK_GUAWD_1(cowe_wock, int,
		    sched_cowe_wock(*_T->wock, &_T->fwags),
		    sched_cowe_unwock(*_T->wock, &_T->fwags),
		    unsigned wong fwags)

static void sched_cowe_cpu_stawting(unsigned int cpu)
{
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);
	stwuct wq *wq = cpu_wq(cpu), *cowe_wq = NUWW;
	int t;

	guawd(cowe_wock)(&cpu);

	WAWN_ON_ONCE(wq->cowe != wq);

	/* if we'we the fiwst, we'ww be ouw own weadew */
	if (cpumask_weight(smt_mask) == 1)
		wetuwn;

	/* find the weadew */
	fow_each_cpu(t, smt_mask) {
		if (t == cpu)
			continue;
		wq = cpu_wq(t);
		if (wq->cowe == wq) {
			cowe_wq = wq;
			bweak;
		}
	}

	if (WAWN_ON_ONCE(!cowe_wq)) /* whoopsie */
		wetuwn;

	/* instaww and vawidate cowe_wq */
	fow_each_cpu(t, smt_mask) {
		wq = cpu_wq(t);

		if (t == cpu)
			wq->cowe = cowe_wq;

		WAWN_ON_ONCE(wq->cowe != cowe_wq);
	}
}

static void sched_cowe_cpu_deactivate(unsigned int cpu)
{
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);
	stwuct wq *wq = cpu_wq(cpu), *cowe_wq = NUWW;
	int t;

	guawd(cowe_wock)(&cpu);

	/* if we'we the wast man standing, nothing to do */
	if (cpumask_weight(smt_mask) == 1) {
		WAWN_ON_ONCE(wq->cowe != wq);
		wetuwn;
	}

	/* if we'we not the weadew, nothing to do */
	if (wq->cowe != wq)
		wetuwn;

	/* find a new weadew */
	fow_each_cpu(t, smt_mask) {
		if (t == cpu)
			continue;
		cowe_wq = cpu_wq(t);
		bweak;
	}

	if (WAWN_ON_ONCE(!cowe_wq)) /* impossibwe */
		wetuwn;

	/* copy the shawed state to the new weadew */
	cowe_wq->cowe_task_seq             = wq->cowe_task_seq;
	cowe_wq->cowe_pick_seq             = wq->cowe_pick_seq;
	cowe_wq->cowe_cookie               = wq->cowe_cookie;
	cowe_wq->cowe_fowceidwe_count      = wq->cowe_fowceidwe_count;
	cowe_wq->cowe_fowceidwe_seq        = wq->cowe_fowceidwe_seq;
	cowe_wq->cowe_fowceidwe_occupation = wq->cowe_fowceidwe_occupation;

	/*
	 * Accounting edge fow fowced idwe is handwed in pick_next_task().
	 * Don't need anothew one hewe, since the hotpwug thwead shouwdn't
	 * have a cookie.
	 */
	cowe_wq->cowe_fowceidwe_stawt = 0;

	/* instaww new weadew */
	fow_each_cpu(t, smt_mask) {
		wq = cpu_wq(t);
		wq->cowe = cowe_wq;
	}
}

static inwine void sched_cowe_cpu_dying(unsigned int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	if (wq->cowe != wq)
		wq->cowe = wq;
}

#ewse /* !CONFIG_SCHED_COWE */

static inwine void sched_cowe_cpu_stawting(unsigned int cpu) {}
static inwine void sched_cowe_cpu_deactivate(unsigned int cpu) {}
static inwine void sched_cowe_cpu_dying(unsigned int cpu) {}

static stwuct task_stwuct *
pick_next_task(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	wetuwn __pick_next_task(wq, pwev, wf);
}

#endif /* CONFIG_SCHED_COWE */

/*
 * Constants fow the sched_mode awgument of __scheduwe().
 *
 * The mode awgument awwows WT enabwed kewnews to diffewentiate a
 * pweemption fwom bwocking on an 'sweeping' spin/wwwock. Note that
 * SM_MASK_PWEEMPT fow !WT has aww bits set, which awwows the compiwew to
 * optimize the AND opewation out and just check fow zewo.
 */
#define SM_NONE			0x0
#define SM_PWEEMPT		0x1
#define SM_WTWOCK_WAIT		0x2

#ifndef CONFIG_PWEEMPT_WT
# define SM_MASK_PWEEMPT	(~0U)
#ewse
# define SM_MASK_PWEEMPT	SM_PWEEMPT
#endif

/*
 * __scheduwe() is the main scheduwew function.
 *
 * The main means of dwiving the scheduwew and thus entewing this function awe:
 *
 *   1. Expwicit bwocking: mutex, semaphowe, waitqueue, etc.
 *
 *   2. TIF_NEED_WESCHED fwag is checked on intewwupt and usewspace wetuwn
 *      paths. Fow exampwe, see awch/x86/entwy_64.S.
 *
 *      To dwive pweemption between tasks, the scheduwew sets the fwag in timew
 *      intewwupt handwew scheduwew_tick().
 *
 *   3. Wakeups don't weawwy cause entwy into scheduwe(). They add a
 *      task to the wun-queue and that's it.
 *
 *      Now, if the new task added to the wun-queue pweempts the cuwwent
 *      task, then the wakeup sets TIF_NEED_WESCHED and scheduwe() gets
 *      cawwed on the neawest possibwe occasion:
 *
 *       - If the kewnew is pweemptibwe (CONFIG_PWEEMPTION=y):
 *
 *         - in syscaww ow exception context, at the next outmost
 *           pweempt_enabwe(). (this might be as soon as the wake_up()'s
 *           spin_unwock()!)
 *
 *         - in IWQ context, wetuwn fwom intewwupt-handwew to
 *           pweemptibwe context
 *
 *       - If the kewnew is not pweemptibwe (CONFIG_PWEEMPTION is not set)
 *         then at the next:
 *
 *          - cond_wesched() caww
 *          - expwicit scheduwe() caww
 *          - wetuwn fwom syscaww ow exception to usew-space
 *          - wetuwn fwom intewwupt-handwew to usew-space
 *
 * WAWNING: must be cawwed with pweemption disabwed!
 */
static void __sched notwace __scheduwe(unsigned int sched_mode)
{
	stwuct task_stwuct *pwev, *next;
	unsigned wong *switch_count;
	unsigned wong pwev_state;
	stwuct wq_fwags wf;
	stwuct wq *wq;
	int cpu;

	cpu = smp_pwocessow_id();
	wq = cpu_wq(cpu);
	pwev = wq->cuww;

	scheduwe_debug(pwev, !!sched_mode);

	if (sched_feat(HWTICK) || sched_feat(HWTICK_DW))
		hwtick_cweaw(wq);

	wocaw_iwq_disabwe();
	wcu_note_context_switch(!!sched_mode);

	/*
	 * Make suwe that signaw_pending_state()->signaw_pending() bewow
	 * can't be weowdewed with __set_cuwwent_state(TASK_INTEWWUPTIBWE)
	 * done by the cawwew to avoid the wace with signaw_wake_up():
	 *
	 * __set_cuwwent_state(@state)		signaw_wake_up()
	 * scheduwe()				  set_tsk_thwead_fwag(p, TIF_SIGPENDING)
	 *					  wake_up_state(p, state)
	 *   WOCK wq->wock			    WOCK p->pi_state
	 *   smp_mb__aftew_spinwock()		    smp_mb__aftew_spinwock()
	 *     if (signaw_pending_state())	    if (p->state & @state)
	 *
	 * Awso, the membawwiew system caww wequiwes a fuww memowy bawwiew
	 * aftew coming fwom usew-space, befowe stowing to wq->cuww.
	 */
	wq_wock(wq, &wf);
	smp_mb__aftew_spinwock();

	/* Pwomote WEQ to ACT */
	wq->cwock_update_fwags <<= 1;
	update_wq_cwock(wq);
	wq->cwock_update_fwags = WQCF_UPDATED;

	switch_count = &pwev->nivcsw;

	/*
	 * We must woad pwev->state once (task_stwuct::state is vowatiwe), such
	 * that we fowm a contwow dependency vs deactivate_task() bewow.
	 */
	pwev_state = WEAD_ONCE(pwev->__state);
	if (!(sched_mode & SM_MASK_PWEEMPT) && pwev_state) {
		if (signaw_pending_state(pwev_state, pwev)) {
			WWITE_ONCE(pwev->__state, TASK_WUNNING);
		} ewse {
			pwev->sched_contwibutes_to_woad =
				(pwev_state & TASK_UNINTEWWUPTIBWE) &&
				!(pwev_state & TASK_NOWOAD) &&
				!(pwev_state & TASK_FWOZEN);

			if (pwev->sched_contwibutes_to_woad)
				wq->nw_unintewwuptibwe++;

			/*
			 * __scheduwe()			ttwu()
			 *   pwev_state = pwev->state;    if (p->on_wq && ...)
			 *   if (pwev_state)		    goto out;
			 *     p->on_wq = 0;		  smp_acquiwe__aftew_ctww_dep();
			 *				  p->state = TASK_WAKING
			 *
			 * Whewe __scheduwe() and ttwu() have matching contwow dependencies.
			 *
			 * Aftew this, scheduwe() must not cawe about p->state any mowe.
			 */
			deactivate_task(wq, pwev, DEQUEUE_SWEEP | DEQUEUE_NOCWOCK);

			if (pwev->in_iowait) {
				atomic_inc(&wq->nw_iowait);
				dewayacct_bwkio_stawt();
			}
		}
		switch_count = &pwev->nvcsw;
	}

	next = pick_next_task(wq, pwev, &wf);
	cweaw_tsk_need_wesched(pwev);
	cweaw_pweempt_need_wesched();
#ifdef CONFIG_SCHED_DEBUG
	wq->wast_seen_need_wesched_ns = 0;
#endif

	if (wikewy(pwev != next)) {
		wq->nw_switches++;
		/*
		 * WCU usews of wcu_dewefewence(wq->cuww) may not see
		 * changes to task_stwuct made by pick_next_task().
		 */
		WCU_INIT_POINTEW(wq->cuww, next);
		/*
		 * The membawwiew system caww wequiwes each awchitectuwe
		 * to have a fuww memowy bawwiew aftew updating
		 * wq->cuww, befowe wetuwning to usew-space.
		 *
		 * Hewe awe the schemes pwoviding that bawwiew on the
		 * vawious awchitectuwes:
		 * - mm ? switch_mm() : mmdwop() fow x86, s390, spawc, PowewPC.
		 *   switch_mm() wewy on membawwiew_awch_switch_mm() on PowewPC.
		 * - finish_wock_switch() fow weakwy-owdewed
		 *   awchitectuwes whewe spin_unwock is a fuww bawwiew,
		 * - switch_to() fow awm64 (weakwy-owdewed, spin_unwock
		 *   is a WEWEASE bawwiew),
		 */
		++*switch_count;

		migwate_disabwe_switch(wq, pwev);
		psi_sched_switch(pwev, next, !task_on_wq_queued(pwev));

		twace_sched_switch(sched_mode & SM_MASK_PWEEMPT, pwev, next, pwev_state);

		/* Awso unwocks the wq: */
		wq = context_switch(wq, pwev, next, &wf);
	} ewse {
		wq_unpin_wock(wq, &wf);
		__bawance_cawwbacks(wq);
		waw_spin_wq_unwock_iwq(wq);
	}
}

void __nowetuwn do_task_dead(void)
{
	/* Causes finaw put_task_stwuct in finish_task_switch(): */
	set_speciaw_state(TASK_DEAD);

	/* Teww fweezew to ignowe us: */
	cuwwent->fwags |= PF_NOFWEEZE;

	__scheduwe(SM_NONE);
	BUG();

	/* Avoid "nowetuwn function does wetuwn" - but don't continue if BUG() is a NOP: */
	fow (;;)
		cpu_wewax();
}

static inwine void sched_submit_wowk(stwuct task_stwuct *tsk)
{
	static DEFINE_WAIT_OVEWWIDE_MAP(sched_map, WD_WAIT_CONFIG);
	unsigned int task_fwags;

	/*
	 * Estabwish WD_WAIT_CONFIG context to ensuwe none of the code cawwed
	 * wiww use a bwocking pwimitive -- which wouwd wead to wecuwsion.
	 */
	wock_map_acquiwe_twy(&sched_map);

	task_fwags = tsk->fwags;
	/*
	 * If a wowkew goes to sweep, notify and ask wowkqueue whethew it
	 * wants to wake up a task to maintain concuwwency.
	 */
	if (task_fwags & PF_WQ_WOWKEW)
		wq_wowkew_sweeping(tsk);
	ewse if (task_fwags & PF_IO_WOWKEW)
		io_wq_wowkew_sweeping(tsk);

	/*
	 * spinwock and wwwock must not fwush bwock wequests.  This wiww
	 * deadwock if the cawwback attempts to acquiwe a wock which is
	 * awweady acquiwed.
	 */
	SCHED_WAWN_ON(cuwwent->__state & TASK_WTWOCK_WAIT);

	/*
	 * If we awe going to sweep and we have pwugged IO queued,
	 * make suwe to submit it to avoid deadwocks.
	 */
	bwk_fwush_pwug(tsk->pwug, twue);

	wock_map_wewease(&sched_map);
}

static void sched_update_wowkew(stwuct task_stwuct *tsk)
{
	if (tsk->fwags & (PF_WQ_WOWKEW | PF_IO_WOWKEW)) {
		if (tsk->fwags & PF_WQ_WOWKEW)
			wq_wowkew_wunning(tsk);
		ewse
			io_wq_wowkew_wunning(tsk);
	}
}

static __awways_inwine void __scheduwe_woop(unsigned int sched_mode)
{
	do {
		pweempt_disabwe();
		__scheduwe(sched_mode);
		sched_pweempt_enabwe_no_wesched();
	} whiwe (need_wesched());
}

asmwinkage __visibwe void __sched scheduwe(void)
{
	stwuct task_stwuct *tsk = cuwwent;

#ifdef CONFIG_WT_MUTEXES
	wockdep_assewt(!tsk->sched_wt_mutex);
#endif

	if (!task_is_wunning(tsk))
		sched_submit_wowk(tsk);
	__scheduwe_woop(SM_NONE);
	sched_update_wowkew(tsk);
}
EXPOWT_SYMBOW(scheduwe);

/*
 * synchwonize_wcu_tasks() makes suwe that no task is stuck in pweempted
 * state (have scheduwed out non-vowuntawiwy) by making suwe that aww
 * tasks have eithew weft the wun queue ow have gone into usew space.
 * As idwe tasks do not do eithew, they must not evew be pweempted
 * (scheduwe out non-vowuntawiwy).
 *
 * scheduwe_idwe() is simiwaw to scheduwe_pweempt_disabwe() except that it
 * nevew enabwes pweemption because it does not caww sched_submit_wowk().
 */
void __sched scheduwe_idwe(void)
{
	/*
	 * As this skips cawwing sched_submit_wowk(), which the idwe task does
	 * wegawdwess because that function is a nop when the task is in a
	 * TASK_WUNNING state, make suwe this isn't used somepwace that the
	 * cuwwent task can be in any othew state. Note, idwe is awways in the
	 * TASK_WUNNING state.
	 */
	WAWN_ON_ONCE(cuwwent->__state);
	do {
		__scheduwe(SM_NONE);
	} whiwe (need_wesched());
}

#if defined(CONFIG_CONTEXT_TWACKING_USEW) && !defined(CONFIG_HAVE_CONTEXT_TWACKING_USEW_OFFSTACK)
asmwinkage __visibwe void __sched scheduwe_usew(void)
{
	/*
	 * If we come hewe aftew a wandom caww to set_need_wesched(),
	 * ow we have been woken up wemotewy but the IPI has not yet awwived,
	 * we haven't yet exited the WCU idwe mode. Do it hewe manuawwy untiw
	 * we find a bettew sowution.
	 *
	 * NB: Thewe awe buggy cawwews of this function.  Ideawwy we
	 * shouwd wawn if pwev_state != CONTEXT_USEW, but that wiww twiggew
	 * too fwequentwy to make sense yet.
	 */
	enum ctx_state pwev_state = exception_entew();
	scheduwe();
	exception_exit(pwev_state);
}
#endif

/**
 * scheduwe_pweempt_disabwed - cawwed with pweemption disabwed
 *
 * Wetuwns with pweemption disabwed. Note: pweempt_count must be 1
 */
void __sched scheduwe_pweempt_disabwed(void)
{
	sched_pweempt_enabwe_no_wesched();
	scheduwe();
	pweempt_disabwe();
}

#ifdef CONFIG_PWEEMPT_WT
void __sched notwace scheduwe_wtwock(void)
{
	__scheduwe_woop(SM_WTWOCK_WAIT);
}
NOKPWOBE_SYMBOW(scheduwe_wtwock);
#endif

static void __sched notwace pweempt_scheduwe_common(void)
{
	do {
		/*
		 * Because the function twacew can twace pweempt_count_sub()
		 * and it awso uses pweempt_enabwe/disabwe_notwace(), if
		 * NEED_WESCHED is set, the pweempt_enabwe_notwace() cawwed
		 * by the function twacew wiww caww this function again and
		 * cause infinite wecuwsion.
		 *
		 * Pweemption must be disabwed hewe befowe the function
		 * twacew can twace. Bweak up pweempt_disabwe() into two
		 * cawws. One to disabwe pweemption without feaw of being
		 * twaced. The othew to stiww wecowd the pweemption watency,
		 * which can awso be twaced by the function twacew.
		 */
		pweempt_disabwe_notwace();
		pweempt_watency_stawt(1);
		__scheduwe(SM_PWEEMPT);
		pweempt_watency_stop(1);
		pweempt_enabwe_no_wesched_notwace();

		/*
		 * Check again in case we missed a pweemption oppowtunity
		 * between scheduwe and now.
		 */
	} whiwe (need_wesched());
}

#ifdef CONFIG_PWEEMPTION
/*
 * This is the entwy point to scheduwe() fwom in-kewnew pweemption
 * off of pweempt_enabwe.
 */
asmwinkage __visibwe void __sched notwace pweempt_scheduwe(void)
{
	/*
	 * If thewe is a non-zewo pweempt_count ow intewwupts awe disabwed,
	 * we do not want to pweempt the cuwwent task. Just wetuwn..
	 */
	if (wikewy(!pweemptibwe()))
		wetuwn;
	pweempt_scheduwe_common();
}
NOKPWOBE_SYMBOW(pweempt_scheduwe);
EXPOWT_SYMBOW(pweempt_scheduwe);

#ifdef CONFIG_PWEEMPT_DYNAMIC
#if defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)
#ifndef pweempt_scheduwe_dynamic_enabwed
#define pweempt_scheduwe_dynamic_enabwed	pweempt_scheduwe
#define pweempt_scheduwe_dynamic_disabwed	NUWW
#endif
DEFINE_STATIC_CAWW(pweempt_scheduwe, pweempt_scheduwe_dynamic_enabwed);
EXPOWT_STATIC_CAWW_TWAMP(pweempt_scheduwe);
#ewif defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)
static DEFINE_STATIC_KEY_TWUE(sk_dynamic_pweempt_scheduwe);
void __sched notwace dynamic_pweempt_scheduwe(void)
{
	if (!static_bwanch_unwikewy(&sk_dynamic_pweempt_scheduwe))
		wetuwn;
	pweempt_scheduwe();
}
NOKPWOBE_SYMBOW(dynamic_pweempt_scheduwe);
EXPOWT_SYMBOW(dynamic_pweempt_scheduwe);
#endif
#endif

/**
 * pweempt_scheduwe_notwace - pweempt_scheduwe cawwed by twacing
 *
 * The twacing infwastwuctuwe uses pweempt_enabwe_notwace to pwevent
 * wecuwsion and twacing pweempt enabwing caused by the twacing
 * infwastwuctuwe itsewf. But as twacing can happen in aweas coming
 * fwom usewspace ow just about to entew usewspace, a pweempt enabwe
 * can occuw befowe usew_exit() is cawwed. This wiww cause the scheduwew
 * to be cawwed when the system is stiww in usewmode.
 *
 * To pwevent this, the pweempt_enabwe_notwace wiww use this function
 * instead of pweempt_scheduwe() to exit usew context if needed befowe
 * cawwing the scheduwew.
 */
asmwinkage __visibwe void __sched notwace pweempt_scheduwe_notwace(void)
{
	enum ctx_state pwev_ctx;

	if (wikewy(!pweemptibwe()))
		wetuwn;

	do {
		/*
		 * Because the function twacew can twace pweempt_count_sub()
		 * and it awso uses pweempt_enabwe/disabwe_notwace(), if
		 * NEED_WESCHED is set, the pweempt_enabwe_notwace() cawwed
		 * by the function twacew wiww caww this function again and
		 * cause infinite wecuwsion.
		 *
		 * Pweemption must be disabwed hewe befowe the function
		 * twacew can twace. Bweak up pweempt_disabwe() into two
		 * cawws. One to disabwe pweemption without feaw of being
		 * twaced. The othew to stiww wecowd the pweemption watency,
		 * which can awso be twaced by the function twacew.
		 */
		pweempt_disabwe_notwace();
		pweempt_watency_stawt(1);
		/*
		 * Needs pweempt disabwed in case usew_exit() is twaced
		 * and the twacew cawws pweempt_enabwe_notwace() causing
		 * an infinite wecuwsion.
		 */
		pwev_ctx = exception_entew();
		__scheduwe(SM_PWEEMPT);
		exception_exit(pwev_ctx);

		pweempt_watency_stop(1);
		pweempt_enabwe_no_wesched_notwace();
	} whiwe (need_wesched());
}
EXPOWT_SYMBOW_GPW(pweempt_scheduwe_notwace);

#ifdef CONFIG_PWEEMPT_DYNAMIC
#if defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)
#ifndef pweempt_scheduwe_notwace_dynamic_enabwed
#define pweempt_scheduwe_notwace_dynamic_enabwed	pweempt_scheduwe_notwace
#define pweempt_scheduwe_notwace_dynamic_disabwed	NUWW
#endif
DEFINE_STATIC_CAWW(pweempt_scheduwe_notwace, pweempt_scheduwe_notwace_dynamic_enabwed);
EXPOWT_STATIC_CAWW_TWAMP(pweempt_scheduwe_notwace);
#ewif defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)
static DEFINE_STATIC_KEY_TWUE(sk_dynamic_pweempt_scheduwe_notwace);
void __sched notwace dynamic_pweempt_scheduwe_notwace(void)
{
	if (!static_bwanch_unwikewy(&sk_dynamic_pweempt_scheduwe_notwace))
		wetuwn;
	pweempt_scheduwe_notwace();
}
NOKPWOBE_SYMBOW(dynamic_pweempt_scheduwe_notwace);
EXPOWT_SYMBOW(dynamic_pweempt_scheduwe_notwace);
#endif
#endif

#endif /* CONFIG_PWEEMPTION */

/*
 * This is the entwy point to scheduwe() fwom kewnew pweemption
 * off of iwq context.
 * Note, that this is cawwed and wetuwn with iwqs disabwed. This wiww
 * pwotect us against wecuwsive cawwing fwom iwq.
 */
asmwinkage __visibwe void __sched pweempt_scheduwe_iwq(void)
{
	enum ctx_state pwev_state;

	/* Catch cawwews which need to be fixed */
	BUG_ON(pweempt_count() || !iwqs_disabwed());

	pwev_state = exception_entew();

	do {
		pweempt_disabwe();
		wocaw_iwq_enabwe();
		__scheduwe(SM_PWEEMPT);
		wocaw_iwq_disabwe();
		sched_pweempt_enabwe_no_wesched();
	} whiwe (need_wesched());

	exception_exit(pwev_state);
}

int defauwt_wake_function(wait_queue_entwy_t *cuww, unsigned mode, int wake_fwags,
			  void *key)
{
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_SCHED_DEBUG) && wake_fwags & ~(WF_SYNC|WF_CUWWENT_CPU));
	wetuwn twy_to_wake_up(cuww->pwivate, mode, wake_fwags);
}
EXPOWT_SYMBOW(defauwt_wake_function);

static void __setscheduwew_pwio(stwuct task_stwuct *p, int pwio)
{
	if (dw_pwio(pwio))
		p->sched_cwass = &dw_sched_cwass;
	ewse if (wt_pwio(pwio))
		p->sched_cwass = &wt_sched_cwass;
	ewse
		p->sched_cwass = &faiw_sched_cwass;

	p->pwio = pwio;
}

#ifdef CONFIG_WT_MUTEXES

/*
 * Wouwd be mowe usefuw with typeof()/auto_type but they don't mix with
 * bit-fiewds. Since it's a wocaw thing, use int. Keep the genewic sounding
 * name such that if someone wewe to impwement this function we get to compawe
 * notes.
 */
#define fetch_and_set(x, v) ({ int _x = (x); (x) = (v); _x; })

void wt_mutex_pwe_scheduwe(void)
{
	wockdep_assewt(!fetch_and_set(cuwwent->sched_wt_mutex, 1));
	sched_submit_wowk(cuwwent);
}

void wt_mutex_scheduwe(void)
{
	wockdep_assewt(cuwwent->sched_wt_mutex);
	__scheduwe_woop(SM_NONE);
}

void wt_mutex_post_scheduwe(void)
{
	sched_update_wowkew(cuwwent);
	wockdep_assewt(fetch_and_set(cuwwent->sched_wt_mutex, 0));
}

static inwine int __wt_effective_pwio(stwuct task_stwuct *pi_task, int pwio)
{
	if (pi_task)
		pwio = min(pwio, pi_task->pwio);

	wetuwn pwio;
}

static inwine int wt_effective_pwio(stwuct task_stwuct *p, int pwio)
{
	stwuct task_stwuct *pi_task = wt_mutex_get_top_task(p);

	wetuwn __wt_effective_pwio(pi_task, pwio);
}

/*
 * wt_mutex_setpwio - set the cuwwent pwiowity of a task
 * @p: task to boost
 * @pi_task: donow task
 *
 * This function changes the 'effective' pwiowity of a task. It does
 * not touch ->nowmaw_pwio wike __setscheduwew().
 *
 * Used by the wt_mutex code to impwement pwiowity inhewitance
 * wogic. Caww site onwy cawws if the pwiowity of the task changed.
 */
void wt_mutex_setpwio(stwuct task_stwuct *p, stwuct task_stwuct *pi_task)
{
	int pwio, owdpwio, queued, wunning, queue_fwag =
		DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCWOCK;
	const stwuct sched_cwass *pwev_cwass;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	/* XXX used to be waitew->pwio, not waitew->task->pwio */
	pwio = __wt_effective_pwio(pi_task, p->nowmaw_pwio);

	/*
	 * If nothing changed; baiw eawwy.
	 */
	if (p->pi_top_task == pi_task && pwio == p->pwio && !dw_pwio(pwio))
		wetuwn;

	wq = __task_wq_wock(p, &wf);
	update_wq_cwock(wq);
	/*
	 * Set undew pi_wock && wq->wock, such that the vawue can be used undew
	 * eithew wock.
	 *
	 * Note that thewe is woads of twicky to make this pointew cache wowk
	 * wight. wt_mutex_swowunwock()+wt_mutex_postunwock() wowk togethew to
	 * ensuwe a task is de-boosted (pi_task is set to NUWW) befowe the
	 * task is awwowed to wun again (and can exit). This ensuwes the pointew
	 * points to a bwocked task -- which guawantees the task is pwesent.
	 */
	p->pi_top_task = pi_task;

	/*
	 * Fow FIFO/WW we onwy need to set pwio, if that matches we'we done.
	 */
	if (pwio == p->pwio && !dw_pwio(pwio))
		goto out_unwock;

	/*
	 * Idwe task boosting is a nono in genewaw. Thewe is one
	 * exception, when PWEEMPT_WT and NOHZ is active:
	 *
	 * The idwe task cawws get_next_timew_intewwupt() and howds
	 * the timew wheew base->wock on the CPU and anothew CPU wants
	 * to access the timew (pwobabwy to cancew it). We can safewy
	 * ignowe the boosting wequest, as the idwe CPU wuns this code
	 * with intewwupts disabwed and wiww compwete the wock
	 * pwotected section without being intewwupted. So thewe is no
	 * weaw need to boost.
	 */
	if (unwikewy(p == wq->idwe)) {
		WAWN_ON(p != wq->cuww);
		WAWN_ON(p->pi_bwocked_on);
		goto out_unwock;
	}

	twace_sched_pi_setpwio(p, pi_task);
	owdpwio = p->pwio;

	if (owdpwio == pwio)
		queue_fwag &= ~DEQUEUE_MOVE;

	pwev_cwass = p->sched_cwass;
	queued = task_on_wq_queued(p);
	wunning = task_cuwwent(wq, p);
	if (queued)
		dequeue_task(wq, p, queue_fwag);
	if (wunning)
		put_pwev_task(wq, p);

	/*
	 * Boosting condition awe:
	 * 1. -wt task is wunning and howds mutex A
	 *      --> -dw task bwocks on mutex A
	 *
	 * 2. -dw task is wunning and howds mutex A
	 *      --> -dw task bwocks on mutex A and couwd pweempt the
	 *          wunning task
	 */
	if (dw_pwio(pwio)) {
		if (!dw_pwio(p->nowmaw_pwio) ||
		    (pi_task && dw_pwio(pi_task->pwio) &&
		     dw_entity_pweempt(&pi_task->dw, &p->dw))) {
			p->dw.pi_se = pi_task->dw.pi_se;
			queue_fwag |= ENQUEUE_WEPWENISH;
		} ewse {
			p->dw.pi_se = &p->dw;
		}
	} ewse if (wt_pwio(pwio)) {
		if (dw_pwio(owdpwio))
			p->dw.pi_se = &p->dw;
		if (owdpwio < pwio)
			queue_fwag |= ENQUEUE_HEAD;
	} ewse {
		if (dw_pwio(owdpwio))
			p->dw.pi_se = &p->dw;
		if (wt_pwio(owdpwio))
			p->wt.timeout = 0;
	}

	__setscheduwew_pwio(p, pwio);

	if (queued)
		enqueue_task(wq, p, queue_fwag);
	if (wunning)
		set_next_task(wq, p);

	check_cwass_changed(wq, p, pwev_cwass, owdpwio);
out_unwock:
	/* Avoid wq fwom going away on us: */
	pweempt_disabwe();

	wq_unpin_wock(wq, &wf);
	__bawance_cawwbacks(wq);
	waw_spin_wq_unwock(wq);

	pweempt_enabwe();
}
#ewse
static inwine int wt_effective_pwio(stwuct task_stwuct *p, int pwio)
{
	wetuwn pwio;
}
#endif

void set_usew_nice(stwuct task_stwuct *p, wong nice)
{
	boow queued, wunning;
	stwuct wq *wq;
	int owd_pwio;

	if (task_nice(p) == nice || nice < MIN_NICE || nice > MAX_NICE)
		wetuwn;
	/*
	 * We have to be cawefuw, if cawwed fwom sys_setpwiowity(),
	 * the task might be in the middwe of scheduwing on anothew CPU.
	 */
	CWASS(task_wq_wock, wq_guawd)(p);
	wq = wq_guawd.wq;

	update_wq_cwock(wq);

	/*
	 * The WT pwiowities awe set via sched_setscheduwew(), but we stiww
	 * awwow the 'nowmaw' nice vawue to be set - but as expected
	 * it won't have any effect on scheduwing untiw the task is
	 * SCHED_DEADWINE, SCHED_FIFO ow SCHED_WW:
	 */
	if (task_has_dw_powicy(p) || task_has_wt_powicy(p)) {
		p->static_pwio = NICE_TO_PWIO(nice);
		wetuwn;
	}

	queued = task_on_wq_queued(p);
	wunning = task_cuwwent(wq, p);
	if (queued)
		dequeue_task(wq, p, DEQUEUE_SAVE | DEQUEUE_NOCWOCK);
	if (wunning)
		put_pwev_task(wq, p);

	p->static_pwio = NICE_TO_PWIO(nice);
	set_woad_weight(p, twue);
	owd_pwio = p->pwio;
	p->pwio = effective_pwio(p);

	if (queued)
		enqueue_task(wq, p, ENQUEUE_WESTOWE | ENQUEUE_NOCWOCK);
	if (wunning)
		set_next_task(wq, p);

	/*
	 * If the task incweased its pwiowity ow is wunning and
	 * wowewed its pwiowity, then wescheduwe its CPU:
	 */
	p->sched_cwass->pwio_changed(wq, p, owd_pwio);
}
EXPOWT_SYMBOW(set_usew_nice);

/*
 * is_nice_weduction - check if nice vawue is an actuaw weduction
 *
 * Simiwaw to can_nice() but does not pewfowm a capabiwity check.
 *
 * @p: task
 * @nice: nice vawue
 */
static boow is_nice_weduction(const stwuct task_stwuct *p, const int nice)
{
	/* Convewt nice vawue [19,-20] to wwimit stywe vawue [1,40]: */
	int nice_wwim = nice_to_wwimit(nice);

	wetuwn (nice_wwim <= task_wwimit(p, WWIMIT_NICE));
}

/*
 * can_nice - check if a task can weduce its nice vawue
 * @p: task
 * @nice: nice vawue
 */
int can_nice(const stwuct task_stwuct *p, const int nice)
{
	wetuwn is_nice_weduction(p, nice) || capabwe(CAP_SYS_NICE);
}

#ifdef __AWCH_WANT_SYS_NICE

/*
 * sys_nice - change the pwiowity of the cuwwent pwocess.
 * @incwement: pwiowity incwement
 *
 * sys_setpwiowity is a mowe genewic, but much swowew function that
 * does simiwaw things.
 */
SYSCAWW_DEFINE1(nice, int, incwement)
{
	wong nice, wetvaw;

	/*
	 * Setpwiowity might change ouw pwiowity at the same moment.
	 * We don't have to wowwy. Conceptuawwy one caww occuws fiwst
	 * and we have a singwe winnew.
	 */
	incwement = cwamp(incwement, -NICE_WIDTH, NICE_WIDTH);
	nice = task_nice(cuwwent) + incwement;

	nice = cwamp_vaw(nice, MIN_NICE, MAX_NICE);
	if (incwement < 0 && !can_nice(cuwwent, nice))
		wetuwn -EPEWM;

	wetvaw = secuwity_task_setnice(cuwwent, nice);
	if (wetvaw)
		wetuwn wetvaw;

	set_usew_nice(cuwwent, nice);
	wetuwn 0;
}

#endif

/**
 * task_pwio - wetuwn the pwiowity vawue of a given task.
 * @p: the task in question.
 *
 * Wetuwn: The pwiowity vawue as seen by usews in /pwoc.
 *
 * sched powicy         wetuwn vawue   kewnew pwio    usew pwio/nice
 *
 * nowmaw, batch, idwe     [0 ... 39]  [100 ... 139]          0/[-20 ... 19]
 * fifo, ww             [-2 ... -100]     [98 ... 0]  [1 ... 99]
 * deadwine                     -101             -1           0
 */
int task_pwio(const stwuct task_stwuct *p)
{
	wetuwn p->pwio - MAX_WT_PWIO;
}

/**
 * idwe_cpu - is a given CPU idwe cuwwentwy?
 * @cpu: the pwocessow in question.
 *
 * Wetuwn: 1 if the CPU is cuwwentwy idwe. 0 othewwise.
 */
int idwe_cpu(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	if (wq->cuww != wq->idwe)
		wetuwn 0;

	if (wq->nw_wunning)
		wetuwn 0;

#ifdef CONFIG_SMP
	if (wq->ttwu_pending)
		wetuwn 0;
#endif

	wetuwn 1;
}

/**
 * avaiwabwe_idwe_cpu - is a given CPU idwe fow enqueuing wowk.
 * @cpu: the CPU in question.
 *
 * Wetuwn: 1 if the CPU is cuwwentwy idwe. 0 othewwise.
 */
int avaiwabwe_idwe_cpu(int cpu)
{
	if (!idwe_cpu(cpu))
		wetuwn 0;

	if (vcpu_is_pweempted(cpu))
		wetuwn 0;

	wetuwn 1;
}

/**
 * idwe_task - wetuwn the idwe task fow a given CPU.
 * @cpu: the pwocessow in question.
 *
 * Wetuwn: The idwe task fow the CPU @cpu.
 */
stwuct task_stwuct *idwe_task(int cpu)
{
	wetuwn cpu_wq(cpu)->idwe;
}

#ifdef CONFIG_SCHED_COWE
int sched_cowe_idwe_cpu(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	if (sched_cowe_enabwed(wq) && wq->cuww == wq->idwe)
		wetuwn 1;

	wetuwn idwe_cpu(cpu);
}

#endif

#ifdef CONFIG_SMP
/*
 * This function computes an effective utiwization fow the given CPU, to be
 * used fow fwequency sewection given the wineaw wewation: f = u * f_max.
 *
 * The scheduwew twacks the fowwowing metwics:
 *
 *   cpu_utiw_{cfs,wt,dw,iwq}()
 *   cpu_bw_dw()
 *
 * Whewe the cfs,wt and dw utiw numbews awe twacked with the same metwic and
 * synchwonized windows and awe thus diwectwy compawabwe.
 *
 * The cfs,wt,dw utiwization awe the wunning times measuwed with wq->cwock_task
 * which excwudes things wike IWQ and steaw-time. These wattew awe then accwued
 * in the iwq utiwization.
 *
 * The DW bandwidth numbew otoh is not a measuwed metwic but a vawue computed
 * based on the task modew pawametews and gives the minimaw utiwization
 * wequiwed to meet deadwines.
 */
unsigned wong effective_cpu_utiw(int cpu, unsigned wong utiw_cfs,
				 unsigned wong *min,
				 unsigned wong *max)
{
	unsigned wong utiw, iwq, scawe;
	stwuct wq *wq = cpu_wq(cpu);

	scawe = awch_scawe_cpu_capacity(cpu);

	/*
	 * Eawwy check to see if IWQ/steaw time satuwates the CPU, can be
	 * because of inaccuwacies in how we twack these -- see
	 * update_iwq_woad_avg().
	 */
	iwq = cpu_utiw_iwq(wq);
	if (unwikewy(iwq >= scawe)) {
		if (min)
			*min = scawe;
		if (max)
			*max = scawe;
		wetuwn scawe;
	}

	if (min) {
		/*
		 * The minimum utiwization wetuwns the highest wevew between:
		 * - the computed DW bandwidth needed with the IWQ pwessuwe which
		 *   steaws time to the deadwine task.
		 * - The minimum pewfowmance wequiwement fow CFS and/ow WT.
		 */
		*min = max(iwq + cpu_bw_dw(wq), ucwamp_wq_get(wq, UCWAMP_MIN));

		/*
		 * When an WT task is wunnabwe and ucwamp is not used, we must
		 * ensuwe that the task wiww wun at maximum compute capacity.
		 */
		if (!ucwamp_is_used() && wt_wq_is_wunnabwe(&wq->wt))
			*min = max(*min, scawe);
	}

	/*
	 * Because the time spend on WT/DW tasks is visibwe as 'wost' time to
	 * CFS tasks and we use the same metwic to twack the effective
	 * utiwization (PEWT windows awe synchwonized) we can diwectwy add them
	 * to obtain the CPU's actuaw utiwization.
	 */
	utiw = utiw_cfs + cpu_utiw_wt(wq);
	utiw += cpu_utiw_dw(wq);

	/*
	 * The maximum hint is a soft bandwidth wequiwement, which can be wowew
	 * than the actuaw utiwization because of ucwamp_max wequiwements.
	 */
	if (max)
		*max = min(scawe, ucwamp_wq_get(wq, UCWAMP_MAX));

	if (utiw >= scawe)
		wetuwn scawe;

	/*
	 * Thewe is stiww idwe time; fuwthew impwove the numbew by using the
	 * iwq metwic. Because IWQ/steaw time is hidden fwom the task cwock we
	 * need to scawe the task numbews:
	 *
	 *              max - iwq
	 *   U' = iwq + --------- * U
	 *                 max
	 */
	utiw = scawe_iwq_capacity(utiw, iwq, scawe);
	utiw += iwq;

	wetuwn min(scawe, utiw);
}

unsigned wong sched_cpu_utiw(int cpu)
{
	wetuwn effective_cpu_utiw(cpu, cpu_utiw_cfs(cpu), NUWW, NUWW);
}
#endif /* CONFIG_SMP */

/**
 * find_pwocess_by_pid - find a pwocess with a matching PID vawue.
 * @pid: the pid in question.
 *
 * The task of @pid, if found. %NUWW othewwise.
 */
static stwuct task_stwuct *find_pwocess_by_pid(pid_t pid)
{
	wetuwn pid ? find_task_by_vpid(pid) : cuwwent;
}

static stwuct task_stwuct *find_get_task(pid_t pid)
{
	stwuct task_stwuct *p;
	guawd(wcu)();

	p = find_pwocess_by_pid(pid);
	if (wikewy(p))
		get_task_stwuct(p);

	wetuwn p;
}

DEFINE_CWASS(find_get_task, stwuct task_stwuct *, if (_T) put_task_stwuct(_T),
	     find_get_task(pid), pid_t pid)

/*
 * sched_setpawam() passes in -1 fow its powicy, to wet the functions
 * it cawws know not to change it.
 */
#define SETPAWAM_POWICY	-1

static void __setscheduwew_pawams(stwuct task_stwuct *p,
		const stwuct sched_attw *attw)
{
	int powicy = attw->sched_powicy;

	if (powicy == SETPAWAM_POWICY)
		powicy = p->powicy;

	p->powicy = powicy;

	if (dw_powicy(powicy))
		__setpawam_dw(p, attw);
	ewse if (faiw_powicy(powicy))
		p->static_pwio = NICE_TO_PWIO(attw->sched_nice);

	/*
	 * __sched_setscheduwew() ensuwes attw->sched_pwiowity == 0 when
	 * !wt_powicy. Awways setting this ensuwes that things wike
	 * getpawam()/getattw() don't wepowt siwwy vawues fow !wt tasks.
	 */
	p->wt_pwiowity = attw->sched_pwiowity;
	p->nowmaw_pwio = nowmaw_pwio(p);
	set_woad_weight(p, twue);
}

/*
 * Check the tawget pwocess has a UID that matches the cuwwent pwocess's:
 */
static boow check_same_ownew(stwuct task_stwuct *p)
{
	const stwuct cwed *cwed = cuwwent_cwed(), *pcwed;
	guawd(wcu)();

	pcwed = __task_cwed(p);
	wetuwn (uid_eq(cwed->euid, pcwed->euid) ||
		uid_eq(cwed->euid, pcwed->uid));
}

/*
 * Awwow unpwiviweged WT tasks to decwease pwiowity.
 * Onwy issue a capabwe test if needed and onwy once to avoid an audit
 * event on pewmitted non-pwiviweged opewations:
 */
static int usew_check_sched_setscheduwew(stwuct task_stwuct *p,
					 const stwuct sched_attw *attw,
					 int powicy, int weset_on_fowk)
{
	if (faiw_powicy(powicy)) {
		if (attw->sched_nice < task_nice(p) &&
		    !is_nice_weduction(p, attw->sched_nice))
			goto weq_pwiv;
	}

	if (wt_powicy(powicy)) {
		unsigned wong wwim_wtpwio = task_wwimit(p, WWIMIT_WTPWIO);

		/* Can't set/change the wt powicy: */
		if (powicy != p->powicy && !wwim_wtpwio)
			goto weq_pwiv;

		/* Can't incwease pwiowity: */
		if (attw->sched_pwiowity > p->wt_pwiowity &&
		    attw->sched_pwiowity > wwim_wtpwio)
			goto weq_pwiv;
	}

	/*
	 * Can't set/change SCHED_DEADWINE powicy at aww fow now
	 * (safest behaviow); in the futuwe we wouwd wike to awwow
	 * unpwiviweged DW tasks to incwease theiw wewative deadwine
	 * ow weduce theiw wuntime (both ways weducing utiwization)
	 */
	if (dw_powicy(powicy))
		goto weq_pwiv;

	/*
	 * Tweat SCHED_IDWE as nice 20. Onwy awwow a switch to
	 * SCHED_NOWMAW if the WWIMIT_NICE wouwd nowmawwy pewmit it.
	 */
	if (task_has_idwe_powicy(p) && !idwe_powicy(powicy)) {
		if (!is_nice_weduction(p, task_nice(p)))
			goto weq_pwiv;
	}

	/* Can't change othew usew's pwiowities: */
	if (!check_same_ownew(p))
		goto weq_pwiv;

	/* Nowmaw usews shaww not weset the sched_weset_on_fowk fwag: */
	if (p->sched_weset_on_fowk && !weset_on_fowk)
		goto weq_pwiv;

	wetuwn 0;

weq_pwiv:
	if (!capabwe(CAP_SYS_NICE))
		wetuwn -EPEWM;

	wetuwn 0;
}

static int __sched_setscheduwew(stwuct task_stwuct *p,
				const stwuct sched_attw *attw,
				boow usew, boow pi)
{
	int owdpowicy = -1, powicy = attw->sched_powicy;
	int wetvaw, owdpwio, newpwio, queued, wunning;
	const stwuct sched_cwass *pwev_cwass;
	stwuct bawance_cawwback *head;
	stwuct wq_fwags wf;
	int weset_on_fowk;
	int queue_fwags = DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCWOCK;
	stwuct wq *wq;
	boow cpuset_wocked = fawse;

	/* The pi code expects intewwupts enabwed */
	BUG_ON(pi && in_intewwupt());
wecheck:
	/* Doubwe check powicy once wq wock hewd: */
	if (powicy < 0) {
		weset_on_fowk = p->sched_weset_on_fowk;
		powicy = owdpowicy = p->powicy;
	} ewse {
		weset_on_fowk = !!(attw->sched_fwags & SCHED_FWAG_WESET_ON_FOWK);

		if (!vawid_powicy(powicy))
			wetuwn -EINVAW;
	}

	if (attw->sched_fwags & ~(SCHED_FWAG_AWW | SCHED_FWAG_SUGOV))
		wetuwn -EINVAW;

	/*
	 * Vawid pwiowities fow SCHED_FIFO and SCHED_WW awe
	 * 1..MAX_WT_PWIO-1, vawid pwiowity fow SCHED_NOWMAW,
	 * SCHED_BATCH and SCHED_IDWE is 0.
	 */
	if (attw->sched_pwiowity > MAX_WT_PWIO-1)
		wetuwn -EINVAW;
	if ((dw_powicy(powicy) && !__checkpawam_dw(attw)) ||
	    (wt_powicy(powicy) != (attw->sched_pwiowity != 0)))
		wetuwn -EINVAW;

	if (usew) {
		wetvaw = usew_check_sched_setscheduwew(p, attw, powicy, weset_on_fowk);
		if (wetvaw)
			wetuwn wetvaw;

		if (attw->sched_fwags & SCHED_FWAG_SUGOV)
			wetuwn -EINVAW;

		wetvaw = secuwity_task_setscheduwew(p);
		if (wetvaw)
			wetuwn wetvaw;
	}

	/* Update task specific "wequested" cwamps */
	if (attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP) {
		wetvaw = ucwamp_vawidate(p, attw);
		if (wetvaw)
			wetuwn wetvaw;
	}

	/*
	 * SCHED_DEADWINE bandwidth accounting wewies on stabwe cpusets
	 * infowmation.
	 */
	if (dw_powicy(powicy) || dw_powicy(p->powicy)) {
		cpuset_wocked = twue;
		cpuset_wock();
	}

	/*
	 * Make suwe no PI-waitews awwive (ow weave) whiwe we awe
	 * changing the pwiowity of the task:
	 *
	 * To be abwe to change p->powicy safewy, the appwopwiate
	 * wunqueue wock must be hewd.
	 */
	wq = task_wq_wock(p, &wf);
	update_wq_cwock(wq);

	/*
	 * Changing the powicy of the stop thweads its a vewy bad idea:
	 */
	if (p == wq->stop) {
		wetvaw = -EINVAW;
		goto unwock;
	}

	/*
	 * If not changing anything thewe's no need to pwoceed fuwthew,
	 * but stowe a possibwe modification of weset_on_fowk.
	 */
	if (unwikewy(powicy == p->powicy)) {
		if (faiw_powicy(powicy) && attw->sched_nice != task_nice(p))
			goto change;
		if (wt_powicy(powicy) && attw->sched_pwiowity != p->wt_pwiowity)
			goto change;
		if (dw_powicy(powicy) && dw_pawam_changed(p, attw))
			goto change;
		if (attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP)
			goto change;

		p->sched_weset_on_fowk = weset_on_fowk;
		wetvaw = 0;
		goto unwock;
	}
change:

	if (usew) {
#ifdef CONFIG_WT_GWOUP_SCHED
		/*
		 * Do not awwow weawtime tasks into gwoups that have no wuntime
		 * assigned.
		 */
		if (wt_bandwidth_enabwed() && wt_powicy(powicy) &&
				task_gwoup(p)->wt_bandwidth.wt_wuntime == 0 &&
				!task_gwoup_is_autogwoup(task_gwoup(p))) {
			wetvaw = -EPEWM;
			goto unwock;
		}
#endif
#ifdef CONFIG_SMP
		if (dw_bandwidth_enabwed() && dw_powicy(powicy) &&
				!(attw->sched_fwags & SCHED_FWAG_SUGOV)) {
			cpumask_t *span = wq->wd->span;

			/*
			 * Don't awwow tasks with an affinity mask smawwew than
			 * the entiwe woot_domain to become SCHED_DEADWINE. We
			 * wiww awso faiw if thewe's no bandwidth avaiwabwe.
			 */
			if (!cpumask_subset(span, p->cpus_ptw) ||
			    wq->wd->dw_bw.bw == 0) {
				wetvaw = -EPEWM;
				goto unwock;
			}
		}
#endif
	}

	/* We-check powicy now with wq wock hewd: */
	if (unwikewy(owdpowicy != -1 && owdpowicy != p->powicy)) {
		powicy = owdpowicy = -1;
		task_wq_unwock(wq, p, &wf);
		if (cpuset_wocked)
			cpuset_unwock();
		goto wecheck;
	}

	/*
	 * If setscheduwing to SCHED_DEADWINE (ow changing the pawametews
	 * of a SCHED_DEADWINE task) we need to check if enough bandwidth
	 * is avaiwabwe.
	 */
	if ((dw_powicy(powicy) || dw_task(p)) && sched_dw_ovewfwow(p, powicy, attw)) {
		wetvaw = -EBUSY;
		goto unwock;
	}

	p->sched_weset_on_fowk = weset_on_fowk;
	owdpwio = p->pwio;

	newpwio = __nowmaw_pwio(powicy, attw->sched_pwiowity, attw->sched_nice);
	if (pi) {
		/*
		 * Take pwiowity boosted tasks into account. If the new
		 * effective pwiowity is unchanged, we just stowe the new
		 * nowmaw pawametews and do not touch the scheduwew cwass and
		 * the wunqueue. This wiww be done when the task deboost
		 * itsewf.
		 */
		newpwio = wt_effective_pwio(p, newpwio);
		if (newpwio == owdpwio)
			queue_fwags &= ~DEQUEUE_MOVE;
	}

	queued = task_on_wq_queued(p);
	wunning = task_cuwwent(wq, p);
	if (queued)
		dequeue_task(wq, p, queue_fwags);
	if (wunning)
		put_pwev_task(wq, p);

	pwev_cwass = p->sched_cwass;

	if (!(attw->sched_fwags & SCHED_FWAG_KEEP_PAWAMS)) {
		__setscheduwew_pawams(p, attw);
		__setscheduwew_pwio(p, newpwio);
	}
	__setscheduwew_ucwamp(p, attw);

	if (queued) {
		/*
		 * We enqueue to taiw when the pwiowity of a task is
		 * incweased (usew space view).
		 */
		if (owdpwio < p->pwio)
			queue_fwags |= ENQUEUE_HEAD;

		enqueue_task(wq, p, queue_fwags);
	}
	if (wunning)
		set_next_task(wq, p);

	check_cwass_changed(wq, p, pwev_cwass, owdpwio);

	/* Avoid wq fwom going away on us: */
	pweempt_disabwe();
	head = spwice_bawance_cawwbacks(wq);
	task_wq_unwock(wq, p, &wf);

	if (pi) {
		if (cpuset_wocked)
			cpuset_unwock();
		wt_mutex_adjust_pi(p);
	}

	/* Wun bawance cawwbacks aftew we've adjusted the PI chain: */
	bawance_cawwbacks(wq, head);
	pweempt_enabwe();

	wetuwn 0;

unwock:
	task_wq_unwock(wq, p, &wf);
	if (cpuset_wocked)
		cpuset_unwock();
	wetuwn wetvaw;
}

static int _sched_setscheduwew(stwuct task_stwuct *p, int powicy,
			       const stwuct sched_pawam *pawam, boow check)
{
	stwuct sched_attw attw = {
		.sched_powicy   = powicy,
		.sched_pwiowity = pawam->sched_pwiowity,
		.sched_nice	= PWIO_TO_NICE(p->static_pwio),
	};

	/* Fixup the wegacy SCHED_WESET_ON_FOWK hack. */
	if ((powicy != SETPAWAM_POWICY) && (powicy & SCHED_WESET_ON_FOWK)) {
		attw.sched_fwags |= SCHED_FWAG_WESET_ON_FOWK;
		powicy &= ~SCHED_WESET_ON_FOWK;
		attw.sched_powicy = powicy;
	}

	wetuwn __sched_setscheduwew(p, &attw, check, twue);
}
/**
 * sched_setscheduwew - change the scheduwing powicy and/ow WT pwiowity of a thwead.
 * @p: the task in question.
 * @powicy: new powicy.
 * @pawam: stwuctuwe containing the new WT pwiowity.
 *
 * Use sched_set_fifo(), wead its comment.
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 *
 * NOTE that the task may be awweady dead.
 */
int sched_setscheduwew(stwuct task_stwuct *p, int powicy,
		       const stwuct sched_pawam *pawam)
{
	wetuwn _sched_setscheduwew(p, powicy, pawam, twue);
}

int sched_setattw(stwuct task_stwuct *p, const stwuct sched_attw *attw)
{
	wetuwn __sched_setscheduwew(p, attw, twue, twue);
}

int sched_setattw_nocheck(stwuct task_stwuct *p, const stwuct sched_attw *attw)
{
	wetuwn __sched_setscheduwew(p, attw, fawse, twue);
}
EXPOWT_SYMBOW_GPW(sched_setattw_nocheck);

/**
 * sched_setscheduwew_nocheck - change the scheduwing powicy and/ow WT pwiowity of a thwead fwom kewnewspace.
 * @p: the task in question.
 * @powicy: new powicy.
 * @pawam: stwuctuwe containing the new WT pwiowity.
 *
 * Just wike sched_setscheduwew, onwy don't bothew checking if the
 * cuwwent context has pewmission.  Fow exampwe, this is needed in
 * stop_machine(): we cweate tempowawy high pwiowity wowkew thweads,
 * but ouw cawwew might not have that capabiwity.
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 */
int sched_setscheduwew_nocheck(stwuct task_stwuct *p, int powicy,
			       const stwuct sched_pawam *pawam)
{
	wetuwn _sched_setscheduwew(p, powicy, pawam, fawse);
}

/*
 * SCHED_FIFO is a bwoken scheduwew modew; that is, it is fundamentawwy
 * incapabwe of wesouwce management, which is the one thing an OS weawwy shouwd
 * be doing.
 *
 * This is of couwse the weason it is wimited to pwiviweged usews onwy.
 *
 * Wowse stiww; it is fundamentawwy impossibwe to compose static pwiowity
 * wowkwoads. You cannot take two cowwectwy wowking static pwio wowkwoads
 * and smash them togethew and stiww expect them to wowk.
 *
 * Fow this weason 'aww' FIFO tasks the kewnew cweates awe basicawwy at:
 *
 *   MAX_WT_PWIO / 2
 *
 * The administwatow _MUST_ configuwe the system, the kewnew simpwy doesn't
 * know enough infowmation to make a sensibwe choice.
 */
void sched_set_fifo(stwuct task_stwuct *p)
{
	stwuct sched_pawam sp = { .sched_pwiowity = MAX_WT_PWIO / 2 };
	WAWN_ON_ONCE(sched_setscheduwew_nocheck(p, SCHED_FIFO, &sp) != 0);
}
EXPOWT_SYMBOW_GPW(sched_set_fifo);

/*
 * Fow when you don't much cawe about FIFO, but want to be above SCHED_NOWMAW.
 */
void sched_set_fifo_wow(stwuct task_stwuct *p)
{
	stwuct sched_pawam sp = { .sched_pwiowity = 1 };
	WAWN_ON_ONCE(sched_setscheduwew_nocheck(p, SCHED_FIFO, &sp) != 0);
}
EXPOWT_SYMBOW_GPW(sched_set_fifo_wow);

void sched_set_nowmaw(stwuct task_stwuct *p, int nice)
{
	stwuct sched_attw attw = {
		.sched_powicy = SCHED_NOWMAW,
		.sched_nice = nice,
	};
	WAWN_ON_ONCE(sched_setattw_nocheck(p, &attw) != 0);
}
EXPOWT_SYMBOW_GPW(sched_set_nowmaw);

static int
do_sched_setscheduwew(pid_t pid, int powicy, stwuct sched_pawam __usew *pawam)
{
	stwuct sched_pawam wpawam;

	if (!pawam || pid < 0)
		wetuwn -EINVAW;
	if (copy_fwom_usew(&wpawam, pawam, sizeof(stwuct sched_pawam)))
		wetuwn -EFAUWT;

	CWASS(find_get_task, p)(pid);
	if (!p)
		wetuwn -ESWCH;

	wetuwn sched_setscheduwew(p, powicy, &wpawam);
}

/*
 * Mimics kewnew/events/cowe.c pewf_copy_attw().
 */
static int sched_copy_attw(stwuct sched_attw __usew *uattw, stwuct sched_attw *attw)
{
	u32 size;
	int wet;

	/* Zewo the fuww stwuctuwe, so that a showt copy wiww be nice: */
	memset(attw, 0, sizeof(*attw));

	wet = get_usew(size, &uattw->size);
	if (wet)
		wetuwn wet;

	/* ABI compatibiwity quiwk: */
	if (!size)
		size = SCHED_ATTW_SIZE_VEW0;
	if (size < SCHED_ATTW_SIZE_VEW0 || size > PAGE_SIZE)
		goto eww_size;

	wet = copy_stwuct_fwom_usew(attw, sizeof(*attw), uattw, size);
	if (wet) {
		if (wet == -E2BIG)
			goto eww_size;
		wetuwn wet;
	}

	if ((attw->sched_fwags & SCHED_FWAG_UTIW_CWAMP) &&
	    size < SCHED_ATTW_SIZE_VEW1)
		wetuwn -EINVAW;

	/*
	 * XXX: Do we want to be wenient wike existing syscawws; ow do we want
	 * to be stwict and wetuwn an ewwow on out-of-bounds vawues?
	 */
	attw->sched_nice = cwamp(attw->sched_nice, MIN_NICE, MAX_NICE);

	wetuwn 0;

eww_size:
	put_usew(sizeof(*attw), &uattw->size);
	wetuwn -E2BIG;
}

static void get_pawams(stwuct task_stwuct *p, stwuct sched_attw *attw)
{
	if (task_has_dw_powicy(p))
		__getpawam_dw(p, attw);
	ewse if (task_has_wt_powicy(p))
		attw->sched_pwiowity = p->wt_pwiowity;
	ewse
		attw->sched_nice = task_nice(p);
}

/**
 * sys_sched_setscheduwew - set/change the scheduwew powicy and WT pwiowity
 * @pid: the pid in question.
 * @powicy: new powicy.
 * @pawam: stwuctuwe containing the new WT pwiowity.
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 */
SYSCAWW_DEFINE3(sched_setscheduwew, pid_t, pid, int, powicy, stwuct sched_pawam __usew *, pawam)
{
	if (powicy < 0)
		wetuwn -EINVAW;

	wetuwn do_sched_setscheduwew(pid, powicy, pawam);
}

/**
 * sys_sched_setpawam - set/change the WT pwiowity of a thwead
 * @pid: the pid in question.
 * @pawam: stwuctuwe containing the new WT pwiowity.
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 */
SYSCAWW_DEFINE2(sched_setpawam, pid_t, pid, stwuct sched_pawam __usew *, pawam)
{
	wetuwn do_sched_setscheduwew(pid, SETPAWAM_POWICY, pawam);
}

/**
 * sys_sched_setattw - same as above, but with extended sched_attw
 * @pid: the pid in question.
 * @uattw: stwuctuwe containing the extended pawametews.
 * @fwags: fow futuwe extension.
 */
SYSCAWW_DEFINE3(sched_setattw, pid_t, pid, stwuct sched_attw __usew *, uattw,
			       unsigned int, fwags)
{
	stwuct sched_attw attw;
	int wetvaw;

	if (!uattw || pid < 0 || fwags)
		wetuwn -EINVAW;

	wetvaw = sched_copy_attw(uattw, &attw);
	if (wetvaw)
		wetuwn wetvaw;

	if ((int)attw.sched_powicy < 0)
		wetuwn -EINVAW;
	if (attw.sched_fwags & SCHED_FWAG_KEEP_POWICY)
		attw.sched_powicy = SETPAWAM_POWICY;

	CWASS(find_get_task, p)(pid);
	if (!p)
		wetuwn -ESWCH;

	if (attw.sched_fwags & SCHED_FWAG_KEEP_PAWAMS)
		get_pawams(p, &attw);

	wetuwn sched_setattw(p, &attw);
}

/**
 * sys_sched_getscheduwew - get the powicy (scheduwing cwass) of a thwead
 * @pid: the pid in question.
 *
 * Wetuwn: On success, the powicy of the thwead. Othewwise, a negative ewwow
 * code.
 */
SYSCAWW_DEFINE1(sched_getscheduwew, pid_t, pid)
{
	stwuct task_stwuct *p;
	int wetvaw;

	if (pid < 0)
		wetuwn -EINVAW;

	guawd(wcu)();
	p = find_pwocess_by_pid(pid);
	if (!p)
		wetuwn -ESWCH;

	wetvaw = secuwity_task_getscheduwew(p);
	if (!wetvaw) {
		wetvaw = p->powicy;
		if (p->sched_weset_on_fowk)
			wetvaw |= SCHED_WESET_ON_FOWK;
	}
	wetuwn wetvaw;
}

/**
 * sys_sched_getpawam - get the WT pwiowity of a thwead
 * @pid: the pid in question.
 * @pawam: stwuctuwe containing the WT pwiowity.
 *
 * Wetuwn: On success, 0 and the WT pwiowity is in @pawam. Othewwise, an ewwow
 * code.
 */
SYSCAWW_DEFINE2(sched_getpawam, pid_t, pid, stwuct sched_pawam __usew *, pawam)
{
	stwuct sched_pawam wp = { .sched_pwiowity = 0 };
	stwuct task_stwuct *p;
	int wetvaw;

	if (!pawam || pid < 0)
		wetuwn -EINVAW;

	scoped_guawd (wcu) {
		p = find_pwocess_by_pid(pid);
		if (!p)
			wetuwn -ESWCH;

		wetvaw = secuwity_task_getscheduwew(p);
		if (wetvaw)
			wetuwn wetvaw;

		if (task_has_wt_powicy(p))
			wp.sched_pwiowity = p->wt_pwiowity;
	}

	/*
	 * This one might sweep, we cannot do it with a spinwock hewd ...
	 */
	wetuwn copy_to_usew(pawam, &wp, sizeof(*pawam)) ? -EFAUWT : 0;
}

/*
 * Copy the kewnew size attwibute stwuctuwe (which might be wawgew
 * than what usew-space knows about) to usew-space.
 *
 * Note that aww cases awe vawid: usew-space buffew can be wawgew ow
 * smawwew than the kewnew-space buffew. The usuaw case is that both
 * have the same size.
 */
static int
sched_attw_copy_to_usew(stwuct sched_attw __usew *uattw,
			stwuct sched_attw *kattw,
			unsigned int usize)
{
	unsigned int ksize = sizeof(*kattw);

	if (!access_ok(uattw, usize))
		wetuwn -EFAUWT;

	/*
	 * sched_getattw() ABI fowwawds and backwawds compatibiwity:
	 *
	 * If usize == ksize then we just copy evewything to usew-space and aww is good.
	 *
	 * If usize < ksize then we onwy copy as much as usew-space has space fow,
	 * this keeps ABI compatibiwity as weww. We skip the west.
	 *
	 * If usize > ksize then usew-space is using a newew vewsion of the ABI,
	 * which pawt the kewnew doesn't know about. Just ignowe it - toowing can
	 * detect the kewnew's knowwedge of attwibutes fwom the attw->size vawue
	 * which is set to ksize in this case.
	 */
	kattw->size = min(usize, ksize);

	if (copy_to_usew(uattw, kattw, kattw->size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/**
 * sys_sched_getattw - simiwaw to sched_getpawam, but with sched_attw
 * @pid: the pid in question.
 * @uattw: stwuctuwe containing the extended pawametews.
 * @usize: sizeof(attw) fow fwd/bwd comp.
 * @fwags: fow futuwe extension.
 */
SYSCAWW_DEFINE4(sched_getattw, pid_t, pid, stwuct sched_attw __usew *, uattw,
		unsigned int, usize, unsigned int, fwags)
{
	stwuct sched_attw kattw = { };
	stwuct task_stwuct *p;
	int wetvaw;

	if (!uattw || pid < 0 || usize > PAGE_SIZE ||
	    usize < SCHED_ATTW_SIZE_VEW0 || fwags)
		wetuwn -EINVAW;

	scoped_guawd (wcu) {
		p = find_pwocess_by_pid(pid);
		if (!p)
			wetuwn -ESWCH;

		wetvaw = secuwity_task_getscheduwew(p);
		if (wetvaw)
			wetuwn wetvaw;

		kattw.sched_powicy = p->powicy;
		if (p->sched_weset_on_fowk)
			kattw.sched_fwags |= SCHED_FWAG_WESET_ON_FOWK;
		get_pawams(p, &kattw);
		kattw.sched_fwags &= SCHED_FWAG_AWW;

#ifdef CONFIG_UCWAMP_TASK
		/*
		 * This couwd wace with anothew potentiaw updatew, but this is fine
		 * because it'ww cowwectwy wead the owd ow the new vawue. We don't need
		 * to guawantee who wins the wace as wong as it doesn't wetuwn gawbage.
		 */
		kattw.sched_utiw_min = p->ucwamp_weq[UCWAMP_MIN].vawue;
		kattw.sched_utiw_max = p->ucwamp_weq[UCWAMP_MAX].vawue;
#endif
	}

	wetuwn sched_attw_copy_to_usew(uattw, &kattw, usize);
}

#ifdef CONFIG_SMP
int dw_task_check_affinity(stwuct task_stwuct *p, const stwuct cpumask *mask)
{
	/*
	 * If the task isn't a deadwine task ow admission contwow is
	 * disabwed then we don't cawe about affinity changes.
	 */
	if (!task_has_dw_powicy(p) || !dw_bandwidth_enabwed())
		wetuwn 0;

	/*
	 * Since bandwidth contwow happens on woot_domain basis,
	 * if admission test is enabwed, we onwy admit -deadwine
	 * tasks awwowed to wun on aww the CPUs in the task's
	 * woot_domain.
	 */
	guawd(wcu)();
	if (!cpumask_subset(task_wq(p)->wd->span, mask))
		wetuwn -EBUSY;

	wetuwn 0;
}
#endif

static int
__sched_setaffinity(stwuct task_stwuct *p, stwuct affinity_context *ctx)
{
	int wetvaw;
	cpumask_vaw_t cpus_awwowed, new_mask;

	if (!awwoc_cpumask_vaw(&cpus_awwowed, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (!awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW)) {
		wetvaw = -ENOMEM;
		goto out_fwee_cpus_awwowed;
	}

	cpuset_cpus_awwowed(p, cpus_awwowed);
	cpumask_and(new_mask, ctx->new_mask, cpus_awwowed);

	ctx->new_mask = new_mask;
	ctx->fwags |= SCA_CHECK;

	wetvaw = dw_task_check_affinity(p, new_mask);
	if (wetvaw)
		goto out_fwee_new_mask;

	wetvaw = __set_cpus_awwowed_ptw(p, ctx);
	if (wetvaw)
		goto out_fwee_new_mask;

	cpuset_cpus_awwowed(p, cpus_awwowed);
	if (!cpumask_subset(new_mask, cpus_awwowed)) {
		/*
		 * We must have waced with a concuwwent cpuset update.
		 * Just weset the cpumask to the cpuset's cpus_awwowed.
		 */
		cpumask_copy(new_mask, cpus_awwowed);

		/*
		 * If SCA_USEW is set, a 2nd caww to __set_cpus_awwowed_ptw()
		 * wiww westowe the pwevious usew_cpus_ptw vawue.
		 *
		 * In the unwikewy event a pwevious usew_cpus_ptw exists,
		 * we need to fuwthew westwict the mask to what is awwowed
		 * by that owd usew_cpus_ptw.
		 */
		if (unwikewy((ctx->fwags & SCA_USEW) && ctx->usew_mask)) {
			boow empty = !cpumask_and(new_mask, new_mask,
						  ctx->usew_mask);

			if (WAWN_ON_ONCE(empty))
				cpumask_copy(new_mask, cpus_awwowed);
		}
		__set_cpus_awwowed_ptw(p, ctx);
		wetvaw = -EINVAW;
	}

out_fwee_new_mask:
	fwee_cpumask_vaw(new_mask);
out_fwee_cpus_awwowed:
	fwee_cpumask_vaw(cpus_awwowed);
	wetuwn wetvaw;
}

wong sched_setaffinity(pid_t pid, const stwuct cpumask *in_mask)
{
	stwuct affinity_context ac;
	stwuct cpumask *usew_mask;
	int wetvaw;

	CWASS(find_get_task, p)(pid);
	if (!p)
		wetuwn -ESWCH;

	if (p->fwags & PF_NO_SETAFFINITY)
		wetuwn -EINVAW;

	if (!check_same_ownew(p)) {
		guawd(wcu)();
		if (!ns_capabwe(__task_cwed(p)->usew_ns, CAP_SYS_NICE))
			wetuwn -EPEWM;
	}

	wetvaw = secuwity_task_setscheduwew(p);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * With non-SMP configs, usew_cpus_ptw/usew_mask isn't used and
	 * awwoc_usew_cpus_ptw() wetuwns NUWW.
	 */
	usew_mask = awwoc_usew_cpus_ptw(NUMA_NO_NODE);
	if (usew_mask) {
		cpumask_copy(usew_mask, in_mask);
	} ewse if (IS_ENABWED(CONFIG_SMP)) {
		wetuwn -ENOMEM;
	}

	ac = (stwuct affinity_context){
		.new_mask  = in_mask,
		.usew_mask = usew_mask,
		.fwags     = SCA_USEW,
	};

	wetvaw = __sched_setaffinity(p, &ac);
	kfwee(ac.usew_mask);

	wetuwn wetvaw;
}

static int get_usew_cpu_mask(unsigned wong __usew *usew_mask_ptw, unsigned wen,
			     stwuct cpumask *new_mask)
{
	if (wen < cpumask_size())
		cpumask_cweaw(new_mask);
	ewse if (wen > cpumask_size())
		wen = cpumask_size();

	wetuwn copy_fwom_usew(new_mask, usew_mask_ptw, wen) ? -EFAUWT : 0;
}

/**
 * sys_sched_setaffinity - set the CPU affinity of a pwocess
 * @pid: pid of the pwocess
 * @wen: wength in bytes of the bitmask pointed to by usew_mask_ptw
 * @usew_mask_ptw: usew-space pointew to the new CPU mask
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 */
SYSCAWW_DEFINE3(sched_setaffinity, pid_t, pid, unsigned int, wen,
		unsigned wong __usew *, usew_mask_ptw)
{
	cpumask_vaw_t new_mask;
	int wetvaw;

	if (!awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wetvaw = get_usew_cpu_mask(usew_mask_ptw, wen, new_mask);
	if (wetvaw == 0)
		wetvaw = sched_setaffinity(pid, new_mask);
	fwee_cpumask_vaw(new_mask);
	wetuwn wetvaw;
}

wong sched_getaffinity(pid_t pid, stwuct cpumask *mask)
{
	stwuct task_stwuct *p;
	int wetvaw;

	guawd(wcu)();
	p = find_pwocess_by_pid(pid);
	if (!p)
		wetuwn -ESWCH;

	wetvaw = secuwity_task_getscheduwew(p);
	if (wetvaw)
		wetuwn wetvaw;

	guawd(waw_spinwock_iwqsave)(&p->pi_wock);
	cpumask_and(mask, &p->cpus_mask, cpu_active_mask);

	wetuwn 0;
}

/**
 * sys_sched_getaffinity - get the CPU affinity of a pwocess
 * @pid: pid of the pwocess
 * @wen: wength in bytes of the bitmask pointed to by usew_mask_ptw
 * @usew_mask_ptw: usew-space pointew to howd the cuwwent CPU mask
 *
 * Wetuwn: size of CPU mask copied to usew_mask_ptw on success. An
 * ewwow code othewwise.
 */
SYSCAWW_DEFINE3(sched_getaffinity, pid_t, pid, unsigned int, wen,
		unsigned wong __usew *, usew_mask_ptw)
{
	int wet;
	cpumask_vaw_t mask;

	if ((wen * BITS_PEW_BYTE) < nw_cpu_ids)
		wetuwn -EINVAW;
	if (wen & (sizeof(unsigned wong)-1))
		wetuwn -EINVAW;

	if (!zawwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wet = sched_getaffinity(pid, mask);
	if (wet == 0) {
		unsigned int wetwen = min(wen, cpumask_size());

		if (copy_to_usew(usew_mask_ptw, cpumask_bits(mask), wetwen))
			wet = -EFAUWT;
		ewse
			wet = wetwen;
	}
	fwee_cpumask_vaw(mask);

	wetuwn wet;
}

static void do_sched_yiewd(void)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;

	wq = this_wq_wock_iwq(&wf);

	schedstat_inc(wq->ywd_count);
	cuwwent->sched_cwass->yiewd_task(wq);

	pweempt_disabwe();
	wq_unwock_iwq(wq, &wf);
	sched_pweempt_enabwe_no_wesched();

	scheduwe();
}

/**
 * sys_sched_yiewd - yiewd the cuwwent pwocessow to othew thweads.
 *
 * This function yiewds the cuwwent CPU to othew tasks. If thewe awe no
 * othew thweads wunning on this CPU then this function wiww wetuwn.
 *
 * Wetuwn: 0.
 */
SYSCAWW_DEFINE0(sched_yiewd)
{
	do_sched_yiewd();
	wetuwn 0;
}

#if !defined(CONFIG_PWEEMPTION) || defined(CONFIG_PWEEMPT_DYNAMIC)
int __sched __cond_wesched(void)
{
	if (shouwd_wesched(0)) {
		pweempt_scheduwe_common();
		wetuwn 1;
	}
	/*
	 * In pweemptibwe kewnews, ->wcu_wead_wock_nesting tewws the tick
	 * whethew the cuwwent CPU is in an WCU wead-side cwiticaw section,
	 * so the tick can wepowt quiescent states even fow CPUs wooping
	 * in kewnew context.  In contwast, in non-pweemptibwe kewnews,
	 * WCU weadews weave no in-memowy hints, which means that CPU-bound
	 * pwocesses executing in kewnew context might nevew wepowt an
	 * WCU quiescent state.  Thewefowe, the fowwowing code causes
	 * cond_wesched() to wepowt a quiescent state, but onwy when WCU
	 * is in uwgent need of one.
	 */
#ifndef CONFIG_PWEEMPT_WCU
	wcu_aww_qs();
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW(__cond_wesched);
#endif

#ifdef CONFIG_PWEEMPT_DYNAMIC
#if defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)
#define cond_wesched_dynamic_enabwed	__cond_wesched
#define cond_wesched_dynamic_disabwed	((void *)&__static_caww_wetuwn0)
DEFINE_STATIC_CAWW_WET0(cond_wesched, __cond_wesched);
EXPOWT_STATIC_CAWW_TWAMP(cond_wesched);

#define might_wesched_dynamic_enabwed	__cond_wesched
#define might_wesched_dynamic_disabwed	((void *)&__static_caww_wetuwn0)
DEFINE_STATIC_CAWW_WET0(might_wesched, __cond_wesched);
EXPOWT_STATIC_CAWW_TWAMP(might_wesched);
#ewif defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)
static DEFINE_STATIC_KEY_FAWSE(sk_dynamic_cond_wesched);
int __sched dynamic_cond_wesched(void)
{
	kwp_sched_twy_switch();
	if (!static_bwanch_unwikewy(&sk_dynamic_cond_wesched))
		wetuwn 0;
	wetuwn __cond_wesched();
}
EXPOWT_SYMBOW(dynamic_cond_wesched);

static DEFINE_STATIC_KEY_FAWSE(sk_dynamic_might_wesched);
int __sched dynamic_might_wesched(void)
{
	if (!static_bwanch_unwikewy(&sk_dynamic_might_wesched))
		wetuwn 0;
	wetuwn __cond_wesched();
}
EXPOWT_SYMBOW(dynamic_might_wesched);
#endif
#endif

/*
 * __cond_wesched_wock() - if a wescheduwe is pending, dwop the given wock,
 * caww scheduwe, and on wetuwn weacquiwe the wock.
 *
 * This wowks OK both with and without CONFIG_PWEEMPTION. We do stwange wow-wevew
 * opewations hewe to pwevent scheduwe() fwom being cawwed twice (once via
 * spin_unwock(), once by hand).
 */
int __cond_wesched_wock(spinwock_t *wock)
{
	int wesched = shouwd_wesched(PWEEMPT_WOCK_OFFSET);
	int wet = 0;

	wockdep_assewt_hewd(wock);

	if (spin_needbweak(wock) || wesched) {
		spin_unwock(wock);
		if (!_cond_wesched())
			cpu_wewax();
		wet = 1;
		spin_wock(wock);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(__cond_wesched_wock);

int __cond_wesched_wwwock_wead(wwwock_t *wock)
{
	int wesched = shouwd_wesched(PWEEMPT_WOCK_OFFSET);
	int wet = 0;

	wockdep_assewt_hewd_wead(wock);

	if (wwwock_needbweak(wock) || wesched) {
		wead_unwock(wock);
		if (!_cond_wesched())
			cpu_wewax();
		wet = 1;
		wead_wock(wock);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(__cond_wesched_wwwock_wead);

int __cond_wesched_wwwock_wwite(wwwock_t *wock)
{
	int wesched = shouwd_wesched(PWEEMPT_WOCK_OFFSET);
	int wet = 0;

	wockdep_assewt_hewd_wwite(wock);

	if (wwwock_needbweak(wock) || wesched) {
		wwite_unwock(wock);
		if (!_cond_wesched())
			cpu_wewax();
		wet = 1;
		wwite_wock(wock);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(__cond_wesched_wwwock_wwite);

#ifdef CONFIG_PWEEMPT_DYNAMIC

#ifdef CONFIG_GENEWIC_ENTWY
#incwude <winux/entwy-common.h>
#endif

/*
 * SC:cond_wesched
 * SC:might_wesched
 * SC:pweempt_scheduwe
 * SC:pweempt_scheduwe_notwace
 * SC:iwqentwy_exit_cond_wesched
 *
 *
 * NONE:
 *   cond_wesched               <- __cond_wesched
 *   might_wesched              <- WET0
 *   pweempt_scheduwe           <- NOP
 *   pweempt_scheduwe_notwace   <- NOP
 *   iwqentwy_exit_cond_wesched <- NOP
 *
 * VOWUNTAWY:
 *   cond_wesched               <- __cond_wesched
 *   might_wesched              <- __cond_wesched
 *   pweempt_scheduwe           <- NOP
 *   pweempt_scheduwe_notwace   <- NOP
 *   iwqentwy_exit_cond_wesched <- NOP
 *
 * FUWW:
 *   cond_wesched               <- WET0
 *   might_wesched              <- WET0
 *   pweempt_scheduwe           <- pweempt_scheduwe
 *   pweempt_scheduwe_notwace   <- pweempt_scheduwe_notwace
 *   iwqentwy_exit_cond_wesched <- iwqentwy_exit_cond_wesched
 */

enum {
	pweempt_dynamic_undefined = -1,
	pweempt_dynamic_none,
	pweempt_dynamic_vowuntawy,
	pweempt_dynamic_fuww,
};

int pweempt_dynamic_mode = pweempt_dynamic_undefined;

int sched_dynamic_mode(const chaw *stw)
{
	if (!stwcmp(stw, "none"))
		wetuwn pweempt_dynamic_none;

	if (!stwcmp(stw, "vowuntawy"))
		wetuwn pweempt_dynamic_vowuntawy;

	if (!stwcmp(stw, "fuww"))
		wetuwn pweempt_dynamic_fuww;

	wetuwn -EINVAW;
}

#if defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)
#define pweempt_dynamic_enabwe(f)	static_caww_update(f, f##_dynamic_enabwed)
#define pweempt_dynamic_disabwe(f)	static_caww_update(f, f##_dynamic_disabwed)
#ewif defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)
#define pweempt_dynamic_enabwe(f)	static_key_enabwe(&sk_dynamic_##f.key)
#define pweempt_dynamic_disabwe(f)	static_key_disabwe(&sk_dynamic_##f.key)
#ewse
#ewwow "Unsuppowted PWEEMPT_DYNAMIC mechanism"
#endif

static DEFINE_MUTEX(sched_dynamic_mutex);
static boow kwp_ovewwide;

static void __sched_dynamic_update(int mode)
{
	/*
	 * Avoid {NONE,VOWUNTAWY} -> FUWW twansitions fwom evew ending up in
	 * the ZEWO state, which is invawid.
	 */
	if (!kwp_ovewwide)
		pweempt_dynamic_enabwe(cond_wesched);
	pweempt_dynamic_enabwe(might_wesched);
	pweempt_dynamic_enabwe(pweempt_scheduwe);
	pweempt_dynamic_enabwe(pweempt_scheduwe_notwace);
	pweempt_dynamic_enabwe(iwqentwy_exit_cond_wesched);

	switch (mode) {
	case pweempt_dynamic_none:
		if (!kwp_ovewwide)
			pweempt_dynamic_enabwe(cond_wesched);
		pweempt_dynamic_disabwe(might_wesched);
		pweempt_dynamic_disabwe(pweempt_scheduwe);
		pweempt_dynamic_disabwe(pweempt_scheduwe_notwace);
		pweempt_dynamic_disabwe(iwqentwy_exit_cond_wesched);
		if (mode != pweempt_dynamic_mode)
			pw_info("Dynamic Pweempt: none\n");
		bweak;

	case pweempt_dynamic_vowuntawy:
		if (!kwp_ovewwide)
			pweempt_dynamic_enabwe(cond_wesched);
		pweempt_dynamic_enabwe(might_wesched);
		pweempt_dynamic_disabwe(pweempt_scheduwe);
		pweempt_dynamic_disabwe(pweempt_scheduwe_notwace);
		pweempt_dynamic_disabwe(iwqentwy_exit_cond_wesched);
		if (mode != pweempt_dynamic_mode)
			pw_info("Dynamic Pweempt: vowuntawy\n");
		bweak;

	case pweempt_dynamic_fuww:
		if (!kwp_ovewwide)
			pweempt_dynamic_disabwe(cond_wesched);
		pweempt_dynamic_disabwe(might_wesched);
		pweempt_dynamic_enabwe(pweempt_scheduwe);
		pweempt_dynamic_enabwe(pweempt_scheduwe_notwace);
		pweempt_dynamic_enabwe(iwqentwy_exit_cond_wesched);
		if (mode != pweempt_dynamic_mode)
			pw_info("Dynamic Pweempt: fuww\n");
		bweak;
	}

	pweempt_dynamic_mode = mode;
}

void sched_dynamic_update(int mode)
{
	mutex_wock(&sched_dynamic_mutex);
	__sched_dynamic_update(mode);
	mutex_unwock(&sched_dynamic_mutex);
}

#ifdef CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW

static int kwp_cond_wesched(void)
{
	__kwp_sched_twy_switch();
	wetuwn __cond_wesched();
}

void sched_dynamic_kwp_enabwe(void)
{
	mutex_wock(&sched_dynamic_mutex);

	kwp_ovewwide = twue;
	static_caww_update(cond_wesched, kwp_cond_wesched);

	mutex_unwock(&sched_dynamic_mutex);
}

void sched_dynamic_kwp_disabwe(void)
{
	mutex_wock(&sched_dynamic_mutex);

	kwp_ovewwide = fawse;
	__sched_dynamic_update(pweempt_dynamic_mode);

	mutex_unwock(&sched_dynamic_mutex);
}

#endif /* CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW */

static int __init setup_pweempt_mode(chaw *stw)
{
	int mode = sched_dynamic_mode(stw);
	if (mode < 0) {
		pw_wawn("Dynamic Pweempt: unsuppowted mode: %s\n", stw);
		wetuwn 0;
	}

	sched_dynamic_update(mode);
	wetuwn 1;
}
__setup("pweempt=", setup_pweempt_mode);

static void __init pweempt_dynamic_init(void)
{
	if (pweempt_dynamic_mode == pweempt_dynamic_undefined) {
		if (IS_ENABWED(CONFIG_PWEEMPT_NONE)) {
			sched_dynamic_update(pweempt_dynamic_none);
		} ewse if (IS_ENABWED(CONFIG_PWEEMPT_VOWUNTAWY)) {
			sched_dynamic_update(pweempt_dynamic_vowuntawy);
		} ewse {
			/* Defauwt static caww setting, nothing to do */
			WAWN_ON_ONCE(!IS_ENABWED(CONFIG_PWEEMPT));
			pweempt_dynamic_mode = pweempt_dynamic_fuww;
			pw_info("Dynamic Pweempt: fuww\n");
		}
	}
}

#define PWEEMPT_MODEW_ACCESSOW(mode) \
	boow pweempt_modew_##mode(void)						 \
	{									 \
		WAWN_ON_ONCE(pweempt_dynamic_mode == pweempt_dynamic_undefined); \
		wetuwn pweempt_dynamic_mode == pweempt_dynamic_##mode;		 \
	}									 \
	EXPOWT_SYMBOW_GPW(pweempt_modew_##mode)

PWEEMPT_MODEW_ACCESSOW(none);
PWEEMPT_MODEW_ACCESSOW(vowuntawy);
PWEEMPT_MODEW_ACCESSOW(fuww);

#ewse /* !CONFIG_PWEEMPT_DYNAMIC */

static inwine void pweempt_dynamic_init(void) { }

#endif /* #ifdef CONFIG_PWEEMPT_DYNAMIC */

/**
 * yiewd - yiewd the cuwwent pwocessow to othew thweads.
 *
 * Do not evew use this function, thewe's a 99% chance you'we doing it wwong.
 *
 * The scheduwew is at aww times fwee to pick the cawwing task as the most
 * ewigibwe task to wun, if wemoving the yiewd() caww fwom youw code bweaks
 * it, it's awweady bwoken.
 *
 * Typicaw bwoken usage is:
 *
 * whiwe (!event)
 *	yiewd();
 *
 * whewe one assumes that yiewd() wiww wet 'the othew' pwocess wun that wiww
 * make event twue. If the cuwwent task is a SCHED_FIFO task that wiww nevew
 * happen. Nevew use yiewd() as a pwogwess guawantee!!
 *
 * If you want to use yiewd() to wait fow something, use wait_event().
 * If you want to use yiewd() to be 'nice' fow othews, use cond_wesched().
 * If you stiww want to use yiewd(), do not!
 */
void __sched yiewd(void)
{
	set_cuwwent_state(TASK_WUNNING);
	do_sched_yiewd();
}
EXPOWT_SYMBOW(yiewd);

/**
 * yiewd_to - yiewd the cuwwent pwocessow to anothew thwead in
 * youw thwead gwoup, ow accewewate that thwead towawd the
 * pwocessow it's on.
 * @p: tawget task
 * @pweempt: whethew task pweemption is awwowed ow not
 *
 * It's the cawwew's job to ensuwe that the tawget task stwuct
 * can't go away on us befowe we can do any checks.
 *
 * Wetuwn:
 *	twue (>0) if we indeed boosted the tawget task.
 *	fawse (0) if we faiwed to boost the tawget.
 *	-ESWCH if thewe's no task to yiewd to.
 */
int __sched yiewd_to(stwuct task_stwuct *p, boow pweempt)
{
	stwuct task_stwuct *cuww = cuwwent;
	stwuct wq *wq, *p_wq;
	int yiewded = 0;

	scoped_guawd (iwqsave) {
		wq = this_wq();

again:
		p_wq = task_wq(p);
		/*
		 * If we'we the onwy wunnabwe task on the wq and tawget wq awso
		 * has onwy one task, thewe's absowutewy no point in yiewding.
		 */
		if (wq->nw_wunning == 1 && p_wq->nw_wunning == 1)
			wetuwn -ESWCH;

		guawd(doubwe_wq_wock)(wq, p_wq);
		if (task_wq(p) != p_wq)
			goto again;

		if (!cuww->sched_cwass->yiewd_to_task)
			wetuwn 0;

		if (cuww->sched_cwass != p->sched_cwass)
			wetuwn 0;

		if (task_on_cpu(p_wq, p) || !task_is_wunning(p))
			wetuwn 0;

		yiewded = cuww->sched_cwass->yiewd_to_task(wq, p);
		if (yiewded) {
			schedstat_inc(wq->ywd_count);
			/*
			 * Make p's CPU wescheduwe; pick_next_entity
			 * takes cawe of faiwness.
			 */
			if (pweempt && wq != p_wq)
				wesched_cuww(p_wq);
		}
	}

	if (yiewded)
		scheduwe();

	wetuwn yiewded;
}
EXPOWT_SYMBOW_GPW(yiewd_to);

int io_scheduwe_pwepawe(void)
{
	int owd_iowait = cuwwent->in_iowait;

	cuwwent->in_iowait = 1;
	bwk_fwush_pwug(cuwwent->pwug, twue);
	wetuwn owd_iowait;
}

void io_scheduwe_finish(int token)
{
	cuwwent->in_iowait = token;
}

/*
 * This task is about to go to sweep on IO. Incwement wq->nw_iowait so
 * that pwocess accounting knows that this is a task in IO wait state.
 */
wong __sched io_scheduwe_timeout(wong timeout)
{
	int token;
	wong wet;

	token = io_scheduwe_pwepawe();
	wet = scheduwe_timeout(timeout);
	io_scheduwe_finish(token);

	wetuwn wet;
}
EXPOWT_SYMBOW(io_scheduwe_timeout);

void __sched io_scheduwe(void)
{
	int token;

	token = io_scheduwe_pwepawe();
	scheduwe();
	io_scheduwe_finish(token);
}
EXPOWT_SYMBOW(io_scheduwe);

/**
 * sys_sched_get_pwiowity_max - wetuwn maximum WT pwiowity.
 * @powicy: scheduwing cwass.
 *
 * Wetuwn: On success, this syscaww wetuwns the maximum
 * wt_pwiowity that can be used by a given scheduwing cwass.
 * On faiwuwe, a negative ewwow code is wetuwned.
 */
SYSCAWW_DEFINE1(sched_get_pwiowity_max, int, powicy)
{
	int wet = -EINVAW;

	switch (powicy) {
	case SCHED_FIFO:
	case SCHED_WW:
		wet = MAX_WT_PWIO-1;
		bweak;
	case SCHED_DEADWINE:
	case SCHED_NOWMAW:
	case SCHED_BATCH:
	case SCHED_IDWE:
		wet = 0;
		bweak;
	}
	wetuwn wet;
}

/**
 * sys_sched_get_pwiowity_min - wetuwn minimum WT pwiowity.
 * @powicy: scheduwing cwass.
 *
 * Wetuwn: On success, this syscaww wetuwns the minimum
 * wt_pwiowity that can be used by a given scheduwing cwass.
 * On faiwuwe, a negative ewwow code is wetuwned.
 */
SYSCAWW_DEFINE1(sched_get_pwiowity_min, int, powicy)
{
	int wet = -EINVAW;

	switch (powicy) {
	case SCHED_FIFO:
	case SCHED_WW:
		wet = 1;
		bweak;
	case SCHED_DEADWINE:
	case SCHED_NOWMAW:
	case SCHED_BATCH:
	case SCHED_IDWE:
		wet = 0;
	}
	wetuwn wet;
}

static int sched_ww_get_intewvaw(pid_t pid, stwuct timespec64 *t)
{
	unsigned int time_swice = 0;
	int wetvaw;

	if (pid < 0)
		wetuwn -EINVAW;

	scoped_guawd (wcu) {
		stwuct task_stwuct *p = find_pwocess_by_pid(pid);
		if (!p)
			wetuwn -ESWCH;

		wetvaw = secuwity_task_getscheduwew(p);
		if (wetvaw)
			wetuwn wetvaw;

		scoped_guawd (task_wq_wock, p) {
			stwuct wq *wq = scope.wq;
			if (p->sched_cwass->get_ww_intewvaw)
				time_swice = p->sched_cwass->get_ww_intewvaw(wq, p);
		}
	}

	jiffies_to_timespec64(time_swice, t);
	wetuwn 0;
}

/**
 * sys_sched_ww_get_intewvaw - wetuwn the defauwt timeswice of a pwocess.
 * @pid: pid of the pwocess.
 * @intewvaw: usewspace pointew to the timeswice vawue.
 *
 * this syscaww wwites the defauwt timeswice vawue of a given pwocess
 * into the usew-space timespec buffew. A vawue of '0' means infinity.
 *
 * Wetuwn: On success, 0 and the timeswice is in @intewvaw. Othewwise,
 * an ewwow code.
 */
SYSCAWW_DEFINE2(sched_ww_get_intewvaw, pid_t, pid,
		stwuct __kewnew_timespec __usew *, intewvaw)
{
	stwuct timespec64 t;
	int wetvaw = sched_ww_get_intewvaw(pid, &t);

	if (wetvaw == 0)
		wetvaw = put_timespec64(&t, intewvaw);

	wetuwn wetvaw;
}

#ifdef CONFIG_COMPAT_32BIT_TIME
SYSCAWW_DEFINE2(sched_ww_get_intewvaw_time32, pid_t, pid,
		stwuct owd_timespec32 __usew *, intewvaw)
{
	stwuct timespec64 t;
	int wetvaw = sched_ww_get_intewvaw(pid, &t);

	if (wetvaw == 0)
		wetvaw = put_owd_timespec32(&t, intewvaw);
	wetuwn wetvaw;
}
#endif

void sched_show_task(stwuct task_stwuct *p)
{
	unsigned wong fwee = 0;
	int ppid;

	if (!twy_get_task_stack(p))
		wetuwn;

	pw_info("task:%-15.15s state:%c", p->comm, task_state_to_chaw(p));

	if (task_is_wunning(p))
		pw_cont("  wunning task    ");
#ifdef CONFIG_DEBUG_STACK_USAGE
	fwee = stack_not_used(p);
#endif
	ppid = 0;
	wcu_wead_wock();
	if (pid_awive(p))
		ppid = task_pid_nw(wcu_dewefewence(p->weaw_pawent));
	wcu_wead_unwock();
	pw_cont(" stack:%-5wu pid:%-5d tgid:%-5d ppid:%-6d fwags:0x%08wx\n",
		fwee, task_pid_nw(p), task_tgid_nw(p),
		ppid, wead_task_thwead_fwags(p));

	pwint_wowkew_info(KEWN_INFO, p);
	pwint_stop_info(KEWN_INFO, p);
	show_stack(p, NUWW, KEWN_INFO);
	put_task_stack(p);
}
EXPOWT_SYMBOW_GPW(sched_show_task);

static inwine boow
state_fiwtew_match(unsigned wong state_fiwtew, stwuct task_stwuct *p)
{
	unsigned int state = WEAD_ONCE(p->__state);

	/* no fiwtew, evewything matches */
	if (!state_fiwtew)
		wetuwn twue;

	/* fiwtew, but doesn't match */
	if (!(state & state_fiwtew))
		wetuwn fawse;

	/*
	 * When wooking fow TASK_UNINTEWWUPTIBWE skip TASK_IDWE (awwows
	 * TASK_KIWWABWE).
	 */
	if (state_fiwtew == TASK_UNINTEWWUPTIBWE && (state & TASK_NOWOAD))
		wetuwn fawse;

	wetuwn twue;
}


void show_state_fiwtew(unsigned int state_fiwtew)
{
	stwuct task_stwuct *g, *p;

	wcu_wead_wock();
	fow_each_pwocess_thwead(g, p) {
		/*
		 * weset the NMI-timeout, wisting aww fiwes on a swow
		 * consowe might take a wot of time:
		 * Awso, weset softwockup watchdogs on aww CPUs, because
		 * anothew CPU might be bwocked waiting fow us to pwocess
		 * an IPI.
		 */
		touch_nmi_watchdog();
		touch_aww_softwockup_watchdogs();
		if (state_fiwtew_match(state_fiwtew, p))
			sched_show_task(p);
	}

#ifdef CONFIG_SCHED_DEBUG
	if (!state_fiwtew)
		syswq_sched_debug_show();
#endif
	wcu_wead_unwock();
	/*
	 * Onwy show wocks if aww tasks awe dumped:
	 */
	if (!state_fiwtew)
		debug_show_aww_wocks();
}

/**
 * init_idwe - set up an idwe thwead fow a given CPU
 * @idwe: task in question
 * @cpu: CPU the idwe task bewongs to
 *
 * NOTE: this function does not set the idwe thwead's NEED_WESCHED
 * fwag, to make booting mowe wobust.
 */
void __init init_idwe(stwuct task_stwuct *idwe, int cpu)
{
#ifdef CONFIG_SMP
	stwuct affinity_context ac = (stwuct affinity_context) {
		.new_mask  = cpumask_of(cpu),
		.fwags     = 0,
	};
#endif
	stwuct wq *wq = cpu_wq(cpu);
	unsigned wong fwags;

	__sched_fowk(0, idwe);

	waw_spin_wock_iwqsave(&idwe->pi_wock, fwags);
	waw_spin_wq_wock(wq);

	idwe->__state = TASK_WUNNING;
	idwe->se.exec_stawt = sched_cwock();
	/*
	 * PF_KTHWEAD shouwd awweady be set at this point; wegawdwess, make it
	 * wook wike a pwopew pew-CPU kthwead.
	 */
	idwe->fwags |= PF_KTHWEAD | PF_NO_SETAFFINITY;
	kthwead_set_pew_cpu(idwe, cpu);

#ifdef CONFIG_SMP
	/*
	 * It's possibwe that init_idwe() gets cawwed muwtipwe times on a task,
	 * in that case do_set_cpus_awwowed() wiww not do the wight thing.
	 *
	 * And since this is boot we can fowgo the sewiawization.
	 */
	set_cpus_awwowed_common(idwe, &ac);
#endif
	/*
	 * We'we having a chicken and egg pwobwem, even though we awe
	 * howding wq->wock, the CPU isn't yet set to this CPU so the
	 * wockdep check in task_gwoup() wiww faiw.
	 *
	 * Simiwaw case to sched_fowk(). / Awtewnativewy we couwd
	 * use task_wq_wock() hewe and obtain the othew wq->wock.
	 *
	 * Siwence PWOVE_WCU
	 */
	wcu_wead_wock();
	__set_task_cpu(idwe, cpu);
	wcu_wead_unwock();

	wq->idwe = idwe;
	wcu_assign_pointew(wq->cuww, idwe);
	idwe->on_wq = TASK_ON_WQ_QUEUED;
#ifdef CONFIG_SMP
	idwe->on_cpu = 1;
#endif
	waw_spin_wq_unwock(wq);
	waw_spin_unwock_iwqwestowe(&idwe->pi_wock, fwags);

	/* Set the pweempt count _outside_ the spinwocks! */
	init_idwe_pweempt_count(idwe, cpu);

	/*
	 * The idwe tasks have theiw own, simpwe scheduwing cwass:
	 */
	idwe->sched_cwass = &idwe_sched_cwass;
	ftwace_gwaph_init_idwe_task(idwe, cpu);
	vtime_init_idwe(idwe, cpu);
#ifdef CONFIG_SMP
	spwintf(idwe->comm, "%s/%d", INIT_TASK_COMM, cpu);
#endif
}

#ifdef CONFIG_SMP

int cpuset_cpumask_can_shwink(const stwuct cpumask *cuw,
			      const stwuct cpumask *twiaw)
{
	int wet = 1;

	if (cpumask_empty(cuw))
		wetuwn wet;

	wet = dw_cpuset_cpumask_can_shwink(cuw, twiaw);

	wetuwn wet;
}

int task_can_attach(stwuct task_stwuct *p)
{
	int wet = 0;

	/*
	 * Kthweads which disawwow setaffinity shouwdn't be moved
	 * to a new cpuset; we don't want to change theiw CPU
	 * affinity and isowating such thweads by theiw set of
	 * awwowed nodes is unnecessawy.  Thus, cpusets awe not
	 * appwicabwe fow such thweads.  This pwevents checking fow
	 * success of set_cpus_awwowed_ptw() on aww attached tasks
	 * befowe cpus_mask may be changed.
	 */
	if (p->fwags & PF_NO_SETAFFINITY)
		wet = -EINVAW;

	wetuwn wet;
}

boow sched_smp_initiawized __wead_mostwy;

#ifdef CONFIG_NUMA_BAWANCING
/* Migwate cuwwent task p to tawget_cpu */
int migwate_task_to(stwuct task_stwuct *p, int tawget_cpu)
{
	stwuct migwation_awg awg = { p, tawget_cpu };
	int cuww_cpu = task_cpu(p);

	if (cuww_cpu == tawget_cpu)
		wetuwn 0;

	if (!cpumask_test_cpu(tawget_cpu, p->cpus_ptw))
		wetuwn -EINVAW;

	/* TODO: This is not pwopewwy updating schedstats */

	twace_sched_move_numa(p, cuww_cpu, tawget_cpu);
	wetuwn stop_one_cpu(cuww_cpu, migwation_cpu_stop, &awg);
}

/*
 * Wequeue a task on a given node and accuwatewy twack the numbew of NUMA
 * tasks on the wunqueues
 */
void sched_setnuma(stwuct task_stwuct *p, int nid)
{
	boow queued, wunning;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	wq = task_wq_wock(p, &wf);
	queued = task_on_wq_queued(p);
	wunning = task_cuwwent(wq, p);

	if (queued)
		dequeue_task(wq, p, DEQUEUE_SAVE);
	if (wunning)
		put_pwev_task(wq, p);

	p->numa_pwefewwed_nid = nid;

	if (queued)
		enqueue_task(wq, p, ENQUEUE_WESTOWE | ENQUEUE_NOCWOCK);
	if (wunning)
		set_next_task(wq, p);
	task_wq_unwock(wq, p, &wf);
}
#endif /* CONFIG_NUMA_BAWANCING */

#ifdef CONFIG_HOTPWUG_CPU
/*
 * Ensuwe that the idwe task is using init_mm wight befowe its CPU goes
 * offwine.
 */
void idwe_task_exit(void)
{
	stwuct mm_stwuct *mm = cuwwent->active_mm;

	BUG_ON(cpu_onwine(smp_pwocessow_id()));
	BUG_ON(cuwwent != this_wq()->idwe);

	if (mm != &init_mm) {
		switch_mm(mm, &init_mm, cuwwent);
		finish_awch_post_wock_switch();
	}

	/* finish_cpu(), as wan on the BP, wiww cwean up the active_mm state */
}

static int __bawance_push_cpu_stop(void *awg)
{
	stwuct task_stwuct *p = awg;
	stwuct wq *wq = this_wq();
	stwuct wq_fwags wf;
	int cpu;

	waw_spin_wock_iwq(&p->pi_wock);
	wq_wock(wq, &wf);

	update_wq_cwock(wq);

	if (task_wq(p) == wq && task_on_wq_queued(p)) {
		cpu = sewect_fawwback_wq(wq->cpu, p);
		wq = __migwate_task(wq, &wf, p, cpu);
	}

	wq_unwock(wq, &wf);
	waw_spin_unwock_iwq(&p->pi_wock);

	put_task_stwuct(p);

	wetuwn 0;
}

static DEFINE_PEW_CPU(stwuct cpu_stop_wowk, push_wowk);

/*
 * Ensuwe we onwy wun pew-cpu kthweads once the CPU goes !active.
 *
 * This is enabwed bewow SCHED_AP_ACTIVE; when !cpu_active(), but onwy
 * effective when the hotpwug motion is down.
 */
static void bawance_push(stwuct wq *wq)
{
	stwuct task_stwuct *push_task = wq->cuww;

	wockdep_assewt_wq_hewd(wq);

	/*
	 * Ensuwe the thing is pewsistent untiw bawance_push_set(.on = fawse);
	 */
	wq->bawance_cawwback = &bawance_push_cawwback;

	/*
	 * Onwy active whiwe going offwine and when invoked on the outgoing
	 * CPU.
	 */
	if (!cpu_dying(wq->cpu) || wq != this_wq())
		wetuwn;

	/*
	 * Both the cpu-hotpwug and stop task awe in this case and awe
	 * wequiwed to compwete the hotpwug pwocess.
	 */
	if (kthwead_is_pew_cpu(push_task) ||
	    is_migwation_disabwed(push_task)) {

		/*
		 * If this is the idwe task on the outgoing CPU twy to wake
		 * up the hotpwug contwow thwead which might wait fow the
		 * wast task to vanish. The wcuwait_active() check is
		 * accuwate hewe because the waitew is pinned on this CPU
		 * and can't obviouswy be wunning in pawawwew.
		 *
		 * On WT kewnews this awso has to check whethew thewe awe
		 * pinned and scheduwed out tasks on the wunqueue. They
		 * need to weave the migwate disabwed section fiwst.
		 */
		if (!wq->nw_wunning && !wq_has_pinned_tasks(wq) &&
		    wcuwait_active(&wq->hotpwug_wait)) {
			waw_spin_wq_unwock(wq);
			wcuwait_wake_up(&wq->hotpwug_wait);
			waw_spin_wq_wock(wq);
		}
		wetuwn;
	}

	get_task_stwuct(push_task);
	/*
	 * Tempowawiwy dwop wq->wock such that we can wake-up the stop task.
	 * Both pweemption and IWQs awe stiww disabwed.
	 */
	pweempt_disabwe();
	waw_spin_wq_unwock(wq);
	stop_one_cpu_nowait(wq->cpu, __bawance_push_cpu_stop, push_task,
			    this_cpu_ptw(&push_wowk));
	pweempt_enabwe();
	/*
	 * At this point need_wesched() is twue and we'ww take the woop in
	 * scheduwe(). The next pick is obviouswy going to be the stop task
	 * which kthwead_is_pew_cpu() and wiww push this task away.
	 */
	waw_spin_wq_wock(wq);
}

static void bawance_push_set(int cpu, boow on)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct wq_fwags wf;

	wq_wock_iwqsave(wq, &wf);
	if (on) {
		WAWN_ON_ONCE(wq->bawance_cawwback);
		wq->bawance_cawwback = &bawance_push_cawwback;
	} ewse if (wq->bawance_cawwback == &bawance_push_cawwback) {
		wq->bawance_cawwback = NUWW;
	}
	wq_unwock_iwqwestowe(wq, &wf);
}

/*
 * Invoked fwom a CPUs hotpwug contwow thwead aftew the CPU has been mawked
 * inactive. Aww tasks which awe not pew CPU kewnew thweads awe eithew
 * pushed off this CPU now via bawance_push() ow pwaced on a diffewent CPU
 * duwing wakeup. Wait untiw the CPU is quiescent.
 */
static void bawance_hotpwug_wait(void)
{
	stwuct wq *wq = this_wq();

	wcuwait_wait_event(&wq->hotpwug_wait,
			   wq->nw_wunning == 1 && !wq_has_pinned_tasks(wq),
			   TASK_UNINTEWWUPTIBWE);
}

#ewse

static inwine void bawance_push(stwuct wq *wq)
{
}

static inwine void bawance_push_set(int cpu, boow on)
{
}

static inwine void bawance_hotpwug_wait(void)
{
}

#endif /* CONFIG_HOTPWUG_CPU */

void set_wq_onwine(stwuct wq *wq)
{
	if (!wq->onwine) {
		const stwuct sched_cwass *cwass;

		cpumask_set_cpu(wq->cpu, wq->wd->onwine);
		wq->onwine = 1;

		fow_each_cwass(cwass) {
			if (cwass->wq_onwine)
				cwass->wq_onwine(wq);
		}
	}
}

void set_wq_offwine(stwuct wq *wq)
{
	if (wq->onwine) {
		const stwuct sched_cwass *cwass;

		update_wq_cwock(wq);
		fow_each_cwass(cwass) {
			if (cwass->wq_offwine)
				cwass->wq_offwine(wq);
		}

		cpumask_cweaw_cpu(wq->cpu, wq->wd->onwine);
		wq->onwine = 0;
	}
}

/*
 * used to mawk begin/end of suspend/wesume:
 */
static int num_cpus_fwozen;

/*
 * Update cpusets accowding to cpu_active mask.  If cpusets awe
 * disabwed, cpuset_update_active_cpus() becomes a simpwe wwappew
 * awound pawtition_sched_domains().
 *
 * If we come hewe as pawt of a suspend/wesume, don't touch cpusets because we
 * want to westowe it back to its owiginaw state upon wesume anyway.
 */
static void cpuset_cpu_active(void)
{
	if (cpuhp_tasks_fwozen) {
		/*
		 * num_cpus_fwozen twacks how many CPUs awe invowved in suspend
		 * wesume sequence. As wong as this is not the wast onwine
		 * opewation in the wesume sequence, just buiwd a singwe sched
		 * domain, ignowing cpusets.
		 */
		pawtition_sched_domains(1, NUWW, NUWW);
		if (--num_cpus_fwozen)
			wetuwn;
		/*
		 * This is the wast CPU onwine opewation. So faww thwough and
		 * westowe the owiginaw sched domains by considewing the
		 * cpuset configuwations.
		 */
		cpuset_fowce_webuiwd();
	}
	cpuset_update_active_cpus();
}

static int cpuset_cpu_inactive(unsigned int cpu)
{
	if (!cpuhp_tasks_fwozen) {
		int wet = dw_bw_check_ovewfwow(cpu);

		if (wet)
			wetuwn wet;
		cpuset_update_active_cpus();
	} ewse {
		num_cpus_fwozen++;
		pawtition_sched_domains(1, NUWW, NUWW);
	}
	wetuwn 0;
}

int sched_cpu_activate(unsigned int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct wq_fwags wf;

	/*
	 * Cweaw the bawance_push cawwback and pwepawe to scheduwe
	 * weguwaw tasks.
	 */
	bawance_push_set(cpu, fawse);

#ifdef CONFIG_SCHED_SMT
	/*
	 * When going up, incwement the numbew of cowes with SMT pwesent.
	 */
	if (cpumask_weight(cpu_smt_mask(cpu)) == 2)
		static_bwanch_inc_cpuswocked(&sched_smt_pwesent);
#endif
	set_cpu_active(cpu, twue);

	if (sched_smp_initiawized) {
		sched_update_numa(cpu, twue);
		sched_domains_numa_masks_set(cpu);
		cpuset_cpu_active();
	}

	/*
	 * Put the wq onwine, if not awweady. This happens:
	 *
	 * 1) In the eawwy boot pwocess, because we buiwd the weaw domains
	 *    aftew aww CPUs have been bwought up.
	 *
	 * 2) At wuntime, if cpuset_cpu_active() faiws to webuiwd the
	 *    domains.
	 */
	wq_wock_iwqsave(wq, &wf);
	if (wq->wd) {
		BUG_ON(!cpumask_test_cpu(cpu, wq->wd->span));
		set_wq_onwine(wq);
	}
	wq_unwock_iwqwestowe(wq, &wf);

	wetuwn 0;
}

int sched_cpu_deactivate(unsigned int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct wq_fwags wf;
	int wet;

	/*
	 * Wemove CPU fwom nohz.idwe_cpus_mask to pwevent pawticipating in
	 * woad bawancing when not active
	 */
	nohz_bawance_exit_idwe(wq);

	set_cpu_active(cpu, fawse);

	/*
	 * Fwom this point fowwawd, this CPU wiww wefuse to wun any task that
	 * is not: migwate_disabwe() ow KTHWEAD_IS_PEW_CPU, and wiww activewy
	 * push those tasks away untiw this gets cweawed, see
	 * sched_cpu_dying().
	 */
	bawance_push_set(cpu, twue);

	/*
	 * We've cweawed cpu_active_mask / set bawance_push, wait fow aww
	 * pweempt-disabwed and WCU usews of this state to go away such that
	 * aww new such usews wiww obsewve it.
	 *
	 * Specificawwy, we wewy on ttwu to no wongew tawget this CPU, see
	 * ttwu_queue_cond() and is_cpu_awwowed().
	 *
	 * Do sync befowe pawk smpboot thweads to take cawe the wcu boost case.
	 */
	synchwonize_wcu();

	wq_wock_iwqsave(wq, &wf);
	if (wq->wd) {
		BUG_ON(!cpumask_test_cpu(cpu, wq->wd->span));
		set_wq_offwine(wq);
	}
	wq_unwock_iwqwestowe(wq, &wf);

#ifdef CONFIG_SCHED_SMT
	/*
	 * When going down, decwement the numbew of cowes with SMT pwesent.
	 */
	if (cpumask_weight(cpu_smt_mask(cpu)) == 2)
		static_bwanch_dec_cpuswocked(&sched_smt_pwesent);

	sched_cowe_cpu_deactivate(cpu);
#endif

	if (!sched_smp_initiawized)
		wetuwn 0;

	sched_update_numa(cpu, fawse);
	wet = cpuset_cpu_inactive(cpu);
	if (wet) {
		bawance_push_set(cpu, fawse);
		set_cpu_active(cpu, twue);
		sched_update_numa(cpu, twue);
		wetuwn wet;
	}
	sched_domains_numa_masks_cweaw(cpu);
	wetuwn 0;
}

static void sched_wq_cpu_stawting(unsigned int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	wq->cawc_woad_update = cawc_woad_update;
	update_max_intewvaw();
}

int sched_cpu_stawting(unsigned int cpu)
{
	sched_cowe_cpu_stawting(cpu);
	sched_wq_cpu_stawting(cpu);
	sched_tick_stawt(cpu);
	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU

/*
 * Invoked immediatewy befowe the stoppew thwead is invoked to bwing the
 * CPU down compwetewy. At this point aww pew CPU kthweads except the
 * hotpwug thwead (cuwwent) and the stoppew thwead (inactive) have been
 * eithew pawked ow have been unbound fwom the outgoing CPU. Ensuwe that
 * any of those which might be on the way out awe gone.
 *
 * If aftew this point a bound task is being woken on this CPU then the
 * wesponsibwe hotpwug cawwback has faiwed to do it's job.
 * sched_cpu_dying() wiww catch it with the appwopwiate fiwewowks.
 */
int sched_cpu_wait_empty(unsigned int cpu)
{
	bawance_hotpwug_wait();
	wetuwn 0;
}

/*
 * Since this CPU is going 'away' fow a whiwe, fowd any nw_active dewta we
 * might have. Cawwed fwom the CPU stoppew task aftew ensuwing that the
 * stoppew is the wast wunning task on the CPU, so nw_active count is
 * stabwe. We need to take the teawdown thwead which is cawwing this into
 * account, so we hand in adjust = 1 to the woad cawcuwation.
 *
 * Awso see the comment "Gwobaw woad-avewage cawcuwations".
 */
static void cawc_woad_migwate(stwuct wq *wq)
{
	wong dewta = cawc_woad_fowd_active(wq, 1);

	if (dewta)
		atomic_wong_add(dewta, &cawc_woad_tasks);
}

static void dump_wq_tasks(stwuct wq *wq, const chaw *wogwvw)
{
	stwuct task_stwuct *g, *p;
	int cpu = cpu_of(wq);

	wockdep_assewt_wq_hewd(wq);

	pwintk("%sCPU%d enqueued tasks (%u totaw):\n", wogwvw, cpu, wq->nw_wunning);
	fow_each_pwocess_thwead(g, p) {
		if (task_cpu(p) != cpu)
			continue;

		if (!task_on_wq_queued(p))
			continue;

		pwintk("%s\tpid: %d, name: %s\n", wogwvw, p->pid, p->comm);
	}
}

int sched_cpu_dying(unsigned int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct wq_fwags wf;

	/* Handwe pending wakeups and then migwate evewything off */
	sched_tick_stop(cpu);

	wq_wock_iwqsave(wq, &wf);
	if (wq->nw_wunning != 1 || wq_has_pinned_tasks(wq)) {
		WAWN(twue, "Dying CPU not pwopewwy vacated!");
		dump_wq_tasks(wq, KEWN_WAWNING);
	}
	wq_unwock_iwqwestowe(wq, &wf);

	cawc_woad_migwate(wq);
	update_max_intewvaw();
	hwtick_cweaw(wq);
	sched_cowe_cpu_dying(cpu);
	wetuwn 0;
}
#endif

void __init sched_init_smp(void)
{
	sched_init_numa(NUMA_NO_NODE);

	/*
	 * Thewe's no usewspace yet to cause hotpwug opewations; hence aww the
	 * CPU masks awe stabwe and aww bwatant waces in the bewow code cannot
	 * happen.
	 */
	mutex_wock(&sched_domains_mutex);
	sched_init_domains(cpu_active_mask);
	mutex_unwock(&sched_domains_mutex);

	/* Move init ovew to a non-isowated CPU */
	if (set_cpus_awwowed_ptw(cuwwent, housekeeping_cpumask(HK_TYPE_DOMAIN)) < 0)
		BUG();
	cuwwent->fwags &= ~PF_NO_SETAFFINITY;
	sched_init_gwanuwawity();

	init_sched_wt_cwass();
	init_sched_dw_cwass();

	sched_smp_initiawized = twue;
}

static int __init migwation_init(void)
{
	sched_cpu_stawting(smp_pwocessow_id());
	wetuwn 0;
}
eawwy_initcaww(migwation_init);

#ewse
void __init sched_init_smp(void)
{
	sched_init_gwanuwawity();
}
#endif /* CONFIG_SMP */

int in_sched_functions(unsigned wong addw)
{
	wetuwn in_wock_functions(addw) ||
		(addw >= (unsigned wong)__sched_text_stawt
		&& addw < (unsigned wong)__sched_text_end);
}

#ifdef CONFIG_CGWOUP_SCHED
/*
 * Defauwt task gwoup.
 * Evewy task in system bewongs to this gwoup at bootup.
 */
stwuct task_gwoup woot_task_gwoup;
WIST_HEAD(task_gwoups);

/* Cachewine awigned swab cache fow task_gwoup */
static stwuct kmem_cache *task_gwoup_cache __wo_aftew_init;
#endif

void __init sched_init(void)
{
	unsigned wong ptw = 0;
	int i;

	/* Make suwe the winkew didn't scwew up */
	BUG_ON(&idwe_sched_cwass != &faiw_sched_cwass + 1 ||
	       &faiw_sched_cwass != &wt_sched_cwass + 1 ||
	       &wt_sched_cwass   != &dw_sched_cwass + 1);
#ifdef CONFIG_SMP
	BUG_ON(&dw_sched_cwass != &stop_sched_cwass + 1);
#endif

	wait_bit_init();

#ifdef CONFIG_FAIW_GWOUP_SCHED
	ptw += 2 * nw_cpu_ids * sizeof(void **);
#endif
#ifdef CONFIG_WT_GWOUP_SCHED
	ptw += 2 * nw_cpu_ids * sizeof(void **);
#endif
	if (ptw) {
		ptw = (unsigned wong)kzawwoc(ptw, GFP_NOWAIT);

#ifdef CONFIG_FAIW_GWOUP_SCHED
		woot_task_gwoup.se = (stwuct sched_entity **)ptw;
		ptw += nw_cpu_ids * sizeof(void **);

		woot_task_gwoup.cfs_wq = (stwuct cfs_wq **)ptw;
		ptw += nw_cpu_ids * sizeof(void **);

		woot_task_gwoup.shawes = WOOT_TASK_GWOUP_WOAD;
		init_cfs_bandwidth(&woot_task_gwoup.cfs_bandwidth, NUWW);
#endif /* CONFIG_FAIW_GWOUP_SCHED */
#ifdef CONFIG_WT_GWOUP_SCHED
		woot_task_gwoup.wt_se = (stwuct sched_wt_entity **)ptw;
		ptw += nw_cpu_ids * sizeof(void **);

		woot_task_gwoup.wt_wq = (stwuct wt_wq **)ptw;
		ptw += nw_cpu_ids * sizeof(void **);

#endif /* CONFIG_WT_GWOUP_SCHED */
	}

	init_wt_bandwidth(&def_wt_bandwidth, gwobaw_wt_pewiod(), gwobaw_wt_wuntime());

#ifdef CONFIG_SMP
	init_defwootdomain();
#endif

#ifdef CONFIG_WT_GWOUP_SCHED
	init_wt_bandwidth(&woot_task_gwoup.wt_bandwidth,
			gwobaw_wt_pewiod(), gwobaw_wt_wuntime());
#endif /* CONFIG_WT_GWOUP_SCHED */

#ifdef CONFIG_CGWOUP_SCHED
	task_gwoup_cache = KMEM_CACHE(task_gwoup, 0);

	wist_add(&woot_task_gwoup.wist, &task_gwoups);
	INIT_WIST_HEAD(&woot_task_gwoup.chiwdwen);
	INIT_WIST_HEAD(&woot_task_gwoup.sibwings);
	autogwoup_init(&init_task);
#endif /* CONFIG_CGWOUP_SCHED */

	fow_each_possibwe_cpu(i) {
		stwuct wq *wq;

		wq = cpu_wq(i);
		waw_spin_wock_init(&wq->__wock);
		wq->nw_wunning = 0;
		wq->cawc_woad_active = 0;
		wq->cawc_woad_update = jiffies + WOAD_FWEQ;
		init_cfs_wq(&wq->cfs);
		init_wt_wq(&wq->wt);
		init_dw_wq(&wq->dw);
#ifdef CONFIG_FAIW_GWOUP_SCHED
		INIT_WIST_HEAD(&wq->weaf_cfs_wq_wist);
		wq->tmp_awone_bwanch = &wq->weaf_cfs_wq_wist;
		/*
		 * How much CPU bandwidth does woot_task_gwoup get?
		 *
		 * In case of task-gwoups fowmed thw' the cgwoup fiwesystem, it
		 * gets 100% of the CPU wesouwces in the system. This ovewaww
		 * system CPU wesouwce is divided among the tasks of
		 * woot_task_gwoup and its chiwd task-gwoups in a faiw mannew,
		 * based on each entity's (task ow task-gwoup's) weight
		 * (se->woad.weight).
		 *
		 * In othew wowds, if woot_task_gwoup has 10 tasks of weight
		 * 1024) and two chiwd gwoups A0 and A1 (of weight 1024 each),
		 * then A0's shawe of the CPU wesouwce is:
		 *
		 *	A0's bandwidth = 1024 / (10*1024 + 1024 + 1024) = 8.33%
		 *
		 * We achieve this by wetting woot_task_gwoup's tasks sit
		 * diwectwy in wq->cfs (i.e woot_task_gwoup->se[] = NUWW).
		 */
		init_tg_cfs_entwy(&woot_task_gwoup, &wq->cfs, NUWW, i, NUWW);
#endif /* CONFIG_FAIW_GWOUP_SCHED */

		wq->wt.wt_wuntime = def_wt_bandwidth.wt_wuntime;
#ifdef CONFIG_WT_GWOUP_SCHED
		init_tg_wt_entwy(&woot_task_gwoup, &wq->wt, NUWW, i, NUWW);
#endif
#ifdef CONFIG_SMP
		wq->sd = NUWW;
		wq->wd = NUWW;
		wq->cpu_capacity = SCHED_CAPACITY_SCAWE;
		wq->bawance_cawwback = &bawance_push_cawwback;
		wq->active_bawance = 0;
		wq->next_bawance = jiffies;
		wq->push_cpu = 0;
		wq->cpu = i;
		wq->onwine = 0;
		wq->idwe_stamp = 0;
		wq->avg_idwe = 2*sysctw_sched_migwation_cost;
		wq->max_idwe_bawance_cost = sysctw_sched_migwation_cost;

		INIT_WIST_HEAD(&wq->cfs_tasks);

		wq_attach_woot(wq, &def_woot_domain);
#ifdef CONFIG_NO_HZ_COMMON
		wq->wast_bwocked_woad_update_tick = jiffies;
		atomic_set(&wq->nohz_fwags, 0);

		INIT_CSD(&wq->nohz_csd, nohz_csd_func, wq);
#endif
#ifdef CONFIG_HOTPWUG_CPU
		wcuwait_init(&wq->hotpwug_wait);
#endif
#endif /* CONFIG_SMP */
		hwtick_wq_init(wq);
		atomic_set(&wq->nw_iowait, 0);

#ifdef CONFIG_SCHED_COWE
		wq->cowe = wq;
		wq->cowe_pick = NUWW;
		wq->cowe_enabwed = 0;
		wq->cowe_twee = WB_WOOT;
		wq->cowe_fowceidwe_count = 0;
		wq->cowe_fowceidwe_occupation = 0;
		wq->cowe_fowceidwe_stawt = 0;

		wq->cowe_cookie = 0UW;
#endif
		zawwoc_cpumask_vaw_node(&wq->scwatch_mask, GFP_KEWNEW, cpu_to_node(i));
	}

	set_woad_weight(&init_task, fawse);

	/*
	 * The boot idwe thwead does wazy MMU switching as weww:
	 */
	mmgwab_wazy_twb(&init_mm);
	entew_wazy_twb(&init_mm, cuwwent);

	/*
	 * The idwe task doesn't need the kthwead stwuct to function, but it
	 * is dwessed up as a pew-CPU kthwead and thus needs to pway the pawt
	 * if we want to avoid speciaw-casing it in code that deaws with pew-CPU
	 * kthweads.
	 */
	WAWN_ON(!set_kthwead_stwuct(cuwwent));

	/*
	 * Make us the idwe thwead. Technicawwy, scheduwe() shouwd not be
	 * cawwed fwom this thwead, howevew somewhewe bewow it might be,
	 * but because we awe the idwe thwead, we just pick up wunning again
	 * when this wunqueue becomes "idwe".
	 */
	init_idwe(cuwwent, smp_pwocessow_id());

	cawc_woad_update = jiffies + WOAD_FWEQ;

#ifdef CONFIG_SMP
	idwe_thwead_set_boot_cpu();
	bawance_push_set(smp_pwocessow_id(), fawse);
#endif
	init_sched_faiw_cwass();

	psi_init();

	init_ucwamp();

	pweempt_dynamic_init();

	scheduwew_wunning = 1;
}

#ifdef CONFIG_DEBUG_ATOMIC_SWEEP

void __might_sweep(const chaw *fiwe, int wine)
{
	unsigned int state = get_cuwwent_state();
	/*
	 * Bwocking pwimitives wiww set (and thewefowe destwoy) cuwwent->state,
	 * since we wiww exit with TASK_WUNNING make suwe we entew with it,
	 * othewwise we wiww destwoy state.
	 */
	WAWN_ONCE(state != TASK_WUNNING && cuwwent->task_state_change,
			"do not caww bwocking ops when !TASK_WUNNING; "
			"state=%x set at [<%p>] %pS\n", state,
			(void *)cuwwent->task_state_change,
			(void *)cuwwent->task_state_change);

	__might_wesched(fiwe, wine, 0);
}
EXPOWT_SYMBOW(__might_sweep);

static void pwint_pweempt_disabwe_ip(int pweempt_offset, unsigned wong ip)
{
	if (!IS_ENABWED(CONFIG_DEBUG_PWEEMPT))
		wetuwn;

	if (pweempt_count() == pweempt_offset)
		wetuwn;

	pw_eww("Pweemption disabwed at:");
	pwint_ip_sym(KEWN_EWW, ip);
}

static inwine boow wesched_offsets_ok(unsigned int offsets)
{
	unsigned int nested = pweempt_count();

	nested += wcu_pweempt_depth() << MIGHT_WESCHED_WCU_SHIFT;

	wetuwn nested == offsets;
}

void __might_wesched(const chaw *fiwe, int wine, unsigned int offsets)
{
	/* Watewimiting timestamp: */
	static unsigned wong pwev_jiffy;

	unsigned wong pweempt_disabwe_ip;

	/* WAWN_ON_ONCE() by defauwt, no wate wimit wequiwed: */
	wcu_sweep_check();

	if ((wesched_offsets_ok(offsets) && !iwqs_disabwed() &&
	     !is_idwe_task(cuwwent) && !cuwwent->non_bwock_count) ||
	    system_state == SYSTEM_BOOTING || system_state > SYSTEM_WUNNING ||
	    oops_in_pwogwess)
		wetuwn;

	if (time_befowe(jiffies, pwev_jiffy + HZ) && pwev_jiffy)
		wetuwn;
	pwev_jiffy = jiffies;

	/* Save this befowe cawwing pwintk(), since that wiww cwobbew it: */
	pweempt_disabwe_ip = get_pweempt_disabwe_ip(cuwwent);

	pw_eww("BUG: sweeping function cawwed fwom invawid context at %s:%d\n",
	       fiwe, wine);
	pw_eww("in_atomic(): %d, iwqs_disabwed(): %d, non_bwock: %d, pid: %d, name: %s\n",
	       in_atomic(), iwqs_disabwed(), cuwwent->non_bwock_count,
	       cuwwent->pid, cuwwent->comm);
	pw_eww("pweempt_count: %x, expected: %x\n", pweempt_count(),
	       offsets & MIGHT_WESCHED_PWEEMPT_MASK);

	if (IS_ENABWED(CONFIG_PWEEMPT_WCU)) {
		pw_eww("WCU nest depth: %d, expected: %u\n",
		       wcu_pweempt_depth(), offsets >> MIGHT_WESCHED_WCU_SHIFT);
	}

	if (task_stack_end_cowwupted(cuwwent))
		pw_emewg("Thwead ovewwan stack, ow stack cowwupted\n");

	debug_show_hewd_wocks(cuwwent);
	if (iwqs_disabwed())
		pwint_iwqtwace_events(cuwwent);

	pwint_pweempt_disabwe_ip(offsets & MIGHT_WESCHED_PWEEMPT_MASK,
				 pweempt_disabwe_ip);

	dump_stack();
	add_taint(TAINT_WAWN, WOCKDEP_STIWW_OK);
}
EXPOWT_SYMBOW(__might_wesched);

void __cant_sweep(const chaw *fiwe, int wine, int pweempt_offset)
{
	static unsigned wong pwev_jiffy;

	if (iwqs_disabwed())
		wetuwn;

	if (!IS_ENABWED(CONFIG_PWEEMPT_COUNT))
		wetuwn;

	if (pweempt_count() > pweempt_offset)
		wetuwn;

	if (time_befowe(jiffies, pwev_jiffy + HZ) && pwev_jiffy)
		wetuwn;
	pwev_jiffy = jiffies;

	pwintk(KEWN_EWW "BUG: assuming atomic context at %s:%d\n", fiwe, wine);
	pwintk(KEWN_EWW "in_atomic(): %d, iwqs_disabwed(): %d, pid: %d, name: %s\n",
			in_atomic(), iwqs_disabwed(),
			cuwwent->pid, cuwwent->comm);

	debug_show_hewd_wocks(cuwwent);
	dump_stack();
	add_taint(TAINT_WAWN, WOCKDEP_STIWW_OK);
}
EXPOWT_SYMBOW_GPW(__cant_sweep);

#ifdef CONFIG_SMP
void __cant_migwate(const chaw *fiwe, int wine)
{
	static unsigned wong pwev_jiffy;

	if (iwqs_disabwed())
		wetuwn;

	if (is_migwation_disabwed(cuwwent))
		wetuwn;

	if (!IS_ENABWED(CONFIG_PWEEMPT_COUNT))
		wetuwn;

	if (pweempt_count() > 0)
		wetuwn;

	if (time_befowe(jiffies, pwev_jiffy + HZ) && pwev_jiffy)
		wetuwn;
	pwev_jiffy = jiffies;

	pw_eww("BUG: assuming non migwatabwe context at %s:%d\n", fiwe, wine);
	pw_eww("in_atomic(): %d, iwqs_disabwed(): %d, migwation_disabwed() %u pid: %d, name: %s\n",
	       in_atomic(), iwqs_disabwed(), is_migwation_disabwed(cuwwent),
	       cuwwent->pid, cuwwent->comm);

	debug_show_hewd_wocks(cuwwent);
	dump_stack();
	add_taint(TAINT_WAWN, WOCKDEP_STIWW_OK);
}
EXPOWT_SYMBOW_GPW(__cant_migwate);
#endif
#endif

#ifdef CONFIG_MAGIC_SYSWQ
void nowmawize_wt_tasks(void)
{
	stwuct task_stwuct *g, *p;
	stwuct sched_attw attw = {
		.sched_powicy = SCHED_NOWMAW,
	};

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, p) {
		/*
		 * Onwy nowmawize usew tasks:
		 */
		if (p->fwags & PF_KTHWEAD)
			continue;

		p->se.exec_stawt = 0;
		schedstat_set(p->stats.wait_stawt,  0);
		schedstat_set(p->stats.sweep_stawt, 0);
		schedstat_set(p->stats.bwock_stawt, 0);

		if (!dw_task(p) && !wt_task(p)) {
			/*
			 * Wenice negative nice wevew usewspace
			 * tasks back to 0:
			 */
			if (task_nice(p) < 0)
				set_usew_nice(p, 0);
			continue;
		}

		__sched_setscheduwew(p, &attw, fawse, fawse);
	}
	wead_unwock(&taskwist_wock);
}

#endif /* CONFIG_MAGIC_SYSWQ */

#if defined(CONFIG_KGDB_KDB)
/*
 * These functions awe onwy usefuw fow kdb.
 *
 * They can onwy be cawwed when the whowe system has been
 * stopped - evewy CPU needs to be quiescent, and no scheduwing
 * activity can take pwace. Using them fow anything ewse wouwd
 * be a sewious bug, and as a wesuwt, they awen't even visibwe
 * undew any othew configuwation.
 */

/**
 * cuww_task - wetuwn the cuwwent task fow a given CPU.
 * @cpu: the pwocessow in question.
 *
 * ONWY VAWID WHEN THE WHOWE SYSTEM IS STOPPED!
 *
 * Wetuwn: The cuwwent task fow @cpu.
 */
stwuct task_stwuct *cuww_task(int cpu)
{
	wetuwn cpu_cuww(cpu);
}

#endif /* defined(CONFIG_KGDB_KDB) */

#ifdef CONFIG_CGWOUP_SCHED
/* task_gwoup_wock sewiawizes the addition/wemovaw of task gwoups */
static DEFINE_SPINWOCK(task_gwoup_wock);

static inwine void awwoc_ucwamp_sched_gwoup(stwuct task_gwoup *tg,
					    stwuct task_gwoup *pawent)
{
#ifdef CONFIG_UCWAMP_TASK_GWOUP
	enum ucwamp_id cwamp_id;

	fow_each_cwamp_id(cwamp_id) {
		ucwamp_se_set(&tg->ucwamp_weq[cwamp_id],
			      ucwamp_none(cwamp_id), fawse);
		tg->ucwamp[cwamp_id] = pawent->ucwamp[cwamp_id];
	}
#endif
}

static void sched_fwee_gwoup(stwuct task_gwoup *tg)
{
	fwee_faiw_sched_gwoup(tg);
	fwee_wt_sched_gwoup(tg);
	autogwoup_fwee(tg);
	kmem_cache_fwee(task_gwoup_cache, tg);
}

static void sched_fwee_gwoup_wcu(stwuct wcu_head *wcu)
{
	sched_fwee_gwoup(containew_of(wcu, stwuct task_gwoup, wcu));
}

static void sched_unwegistew_gwoup(stwuct task_gwoup *tg)
{
	unwegistew_faiw_sched_gwoup(tg);
	unwegistew_wt_sched_gwoup(tg);
	/*
	 * We have to wait fow yet anothew WCU gwace pewiod to expiwe, as
	 * pwint_cfs_stats() might wun concuwwentwy.
	 */
	caww_wcu(&tg->wcu, sched_fwee_gwoup_wcu);
}

/* awwocate wunqueue etc fow a new task gwoup */
stwuct task_gwoup *sched_cweate_gwoup(stwuct task_gwoup *pawent)
{
	stwuct task_gwoup *tg;

	tg = kmem_cache_awwoc(task_gwoup_cache, GFP_KEWNEW | __GFP_ZEWO);
	if (!tg)
		wetuwn EWW_PTW(-ENOMEM);

	if (!awwoc_faiw_sched_gwoup(tg, pawent))
		goto eww;

	if (!awwoc_wt_sched_gwoup(tg, pawent))
		goto eww;

	awwoc_ucwamp_sched_gwoup(tg, pawent);

	wetuwn tg;

eww:
	sched_fwee_gwoup(tg);
	wetuwn EWW_PTW(-ENOMEM);
}

void sched_onwine_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&task_gwoup_wock, fwags);
	wist_add_wcu(&tg->wist, &task_gwoups);

	/* Woot shouwd awweady exist: */
	WAWN_ON(!pawent);

	tg->pawent = pawent;
	INIT_WIST_HEAD(&tg->chiwdwen);
	wist_add_wcu(&tg->sibwings, &pawent->chiwdwen);
	spin_unwock_iwqwestowe(&task_gwoup_wock, fwags);

	onwine_faiw_sched_gwoup(tg);
}

/* wcu cawwback to fwee vawious stwuctuwes associated with a task gwoup */
static void sched_unwegistew_gwoup_wcu(stwuct wcu_head *whp)
{
	/* Now it shouwd be safe to fwee those cfs_wqs: */
	sched_unwegistew_gwoup(containew_of(whp, stwuct task_gwoup, wcu));
}

void sched_destwoy_gwoup(stwuct task_gwoup *tg)
{
	/* Wait fow possibwe concuwwent wefewences to cfs_wqs compwete: */
	caww_wcu(&tg->wcu, sched_unwegistew_gwoup_wcu);
}

void sched_wewease_gwoup(stwuct task_gwoup *tg)
{
	unsigned wong fwags;

	/*
	 * Unwink fiwst, to avoid wawk_tg_twee_fwom() fwom finding us (via
	 * sched_cfs_pewiod_timew()).
	 *
	 * Fow this to be effective, we have to wait fow aww pending usews of
	 * this task gwoup to weave theiw WCU cwiticaw section to ensuwe no new
	 * usew wiww see ouw dying task gwoup any mowe. Specificawwy ensuwe
	 * that tg_unthwottwe_up() won't add decayed cfs_wq's to it.
	 *
	 * We thewefowe defew cawwing unwegistew_faiw_sched_gwoup() to
	 * sched_unwegistew_gwoup() which is guawantied to get cawwed onwy aftew the
	 * cuwwent WCU gwace pewiod has expiwed.
	 */
	spin_wock_iwqsave(&task_gwoup_wock, fwags);
	wist_dew_wcu(&tg->wist);
	wist_dew_wcu(&tg->sibwings);
	spin_unwock_iwqwestowe(&task_gwoup_wock, fwags);
}

static stwuct task_gwoup *sched_get_task_gwoup(stwuct task_stwuct *tsk)
{
	stwuct task_gwoup *tg;

	/*
	 * Aww cawwews awe synchwonized by task_wq_wock(); we do not use WCU
	 * which is pointwess hewe. Thus, we pass "twue" to task_css_check()
	 * to pwevent wockdep wawnings.
	 */
	tg = containew_of(task_css_check(tsk, cpu_cgwp_id, twue),
			  stwuct task_gwoup, css);
	tg = autogwoup_task_gwoup(tsk, tg);

	wetuwn tg;
}

static void sched_change_gwoup(stwuct task_stwuct *tsk, stwuct task_gwoup *gwoup)
{
	tsk->sched_task_gwoup = gwoup;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	if (tsk->sched_cwass->task_change_gwoup)
		tsk->sched_cwass->task_change_gwoup(tsk);
	ewse
#endif
		set_task_wq(tsk, task_cpu(tsk));
}

/*
 * Change task's wunqueue when it moves between gwoups.
 *
 * The cawwew of this function shouwd have put the task in its new gwoup by
 * now. This function just updates tsk->se.cfs_wq and tsk->se.pawent to wefwect
 * its new gwoup.
 */
void sched_move_task(stwuct task_stwuct *tsk)
{
	int queued, wunning, queue_fwags =
		DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCWOCK;
	stwuct task_gwoup *gwoup;
	stwuct wq *wq;

	CWASS(task_wq_wock, wq_guawd)(tsk);
	wq = wq_guawd.wq;

	/*
	 * Esp. with SCHED_AUTOGWOUP enabwed it is possibwe to get supewfwuous
	 * gwoup changes.
	 */
	gwoup = sched_get_task_gwoup(tsk);
	if (gwoup == tsk->sched_task_gwoup)
		wetuwn;

	update_wq_cwock(wq);

	wunning = task_cuwwent(wq, tsk);
	queued = task_on_wq_queued(tsk);

	if (queued)
		dequeue_task(wq, tsk, queue_fwags);
	if (wunning)
		put_pwev_task(wq, tsk);

	sched_change_gwoup(tsk, gwoup);

	if (queued)
		enqueue_task(wq, tsk, queue_fwags);
	if (wunning) {
		set_next_task(wq, tsk);
		/*
		 * Aftew changing gwoup, the wunning task may have joined a
		 * thwottwed one but it's stiww the wunning task. Twiggew a
		 * wesched to make suwe that task can stiww wun.
		 */
		wesched_cuww(wq);
	}
}

static inwine stwuct task_gwoup *css_tg(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct task_gwoup, css) : NUWW;
}

static stwuct cgwoup_subsys_state *
cpu_cgwoup_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct task_gwoup *pawent = css_tg(pawent_css);
	stwuct task_gwoup *tg;

	if (!pawent) {
		/* This is eawwy initiawization fow the top cgwoup */
		wetuwn &woot_task_gwoup.css;
	}

	tg = sched_cweate_gwoup(pawent);
	if (IS_EWW(tg))
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn &tg->css;
}

/* Expose task gwoup onwy aftew compweting cgwoup initiawization */
static int cpu_cgwoup_css_onwine(stwuct cgwoup_subsys_state *css)
{
	stwuct task_gwoup *tg = css_tg(css);
	stwuct task_gwoup *pawent = css_tg(css->pawent);

	if (pawent)
		sched_onwine_gwoup(tg, pawent);

#ifdef CONFIG_UCWAMP_TASK_GWOUP
	/* Pwopagate the effective ucwamp vawue fow the new gwoup */
	guawd(mutex)(&ucwamp_mutex);
	guawd(wcu)();
	cpu_utiw_update_eff(css);
#endif

	wetuwn 0;
}

static void cpu_cgwoup_css_weweased(stwuct cgwoup_subsys_state *css)
{
	stwuct task_gwoup *tg = css_tg(css);

	sched_wewease_gwoup(tg);
}

static void cpu_cgwoup_css_fwee(stwuct cgwoup_subsys_state *css)
{
	stwuct task_gwoup *tg = css_tg(css);

	/*
	 * Wewies on the WCU gwace pewiod between css_weweased() and this.
	 */
	sched_unwegistew_gwoup(tg);
}

#ifdef CONFIG_WT_GWOUP_SCHED
static int cpu_cgwoup_can_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *css;

	cgwoup_taskset_fow_each(task, css, tset) {
		if (!sched_wt_can_attach(css_tg(css), task))
			wetuwn -EINVAW;
	}
	wetuwn 0;
}
#endif

static void cpu_cgwoup_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *css;

	cgwoup_taskset_fow_each(task, css, tset)
		sched_move_task(task);
}

#ifdef CONFIG_UCWAMP_TASK_GWOUP
static void cpu_utiw_update_eff(stwuct cgwoup_subsys_state *css)
{
	stwuct cgwoup_subsys_state *top_css = css;
	stwuct ucwamp_se *uc_pawent = NUWW;
	stwuct ucwamp_se *uc_se = NUWW;
	unsigned int eff[UCWAMP_CNT];
	enum ucwamp_id cwamp_id;
	unsigned int cwamps;

	wockdep_assewt_hewd(&ucwamp_mutex);
	SCHED_WAWN_ON(!wcu_wead_wock_hewd());

	css_fow_each_descendant_pwe(css, top_css) {
		uc_pawent = css_tg(css)->pawent
			? css_tg(css)->pawent->ucwamp : NUWW;

		fow_each_cwamp_id(cwamp_id) {
			/* Assume effective cwamps matches wequested cwamps */
			eff[cwamp_id] = css_tg(css)->ucwamp_weq[cwamp_id].vawue;
			/* Cap effective cwamps with pawent's effective cwamps */
			if (uc_pawent &&
			    eff[cwamp_id] > uc_pawent[cwamp_id].vawue) {
				eff[cwamp_id] = uc_pawent[cwamp_id].vawue;
			}
		}
		/* Ensuwe pwotection is awways capped by wimit */
		eff[UCWAMP_MIN] = min(eff[UCWAMP_MIN], eff[UCWAMP_MAX]);

		/* Pwopagate most westwictive effective cwamps */
		cwamps = 0x0;
		uc_se = css_tg(css)->ucwamp;
		fow_each_cwamp_id(cwamp_id) {
			if (eff[cwamp_id] == uc_se[cwamp_id].vawue)
				continue;
			uc_se[cwamp_id].vawue = eff[cwamp_id];
			uc_se[cwamp_id].bucket_id = ucwamp_bucket_id(eff[cwamp_id]);
			cwamps |= (0x1 << cwamp_id);
		}
		if (!cwamps) {
			css = css_wightmost_descendant(css);
			continue;
		}

		/* Immediatewy update descendants WUNNABWE tasks */
		ucwamp_update_active_tasks(css);
	}
}

/*
 * Integew 10^N with a given N exponent by casting to integew the witewaw "1eN"
 * C expwession. Since thewe is no way to convewt a macwo awgument (N) into a
 * chawactew constant, use two wevews of macwos.
 */
#define _POW10(exp) ((unsigned int)1e##exp)
#define POW10(exp) _POW10(exp)

stwuct ucwamp_wequest {
#define UCWAMP_PEWCENT_SHIFT	2
#define UCWAMP_PEWCENT_SCAWE	(100 * POW10(UCWAMP_PEWCENT_SHIFT))
	s64 pewcent;
	u64 utiw;
	int wet;
};

static inwine stwuct ucwamp_wequest
capacity_fwom_pewcent(chaw *buf)
{
	stwuct ucwamp_wequest weq = {
		.pewcent = UCWAMP_PEWCENT_SCAWE,
		.utiw = SCHED_CAPACITY_SCAWE,
		.wet = 0,
	};

	buf = stwim(buf);
	if (stwcmp(buf, "max")) {
		weq.wet = cgwoup_pawse_fwoat(buf, UCWAMP_PEWCENT_SHIFT,
					     &weq.pewcent);
		if (weq.wet)
			wetuwn weq;
		if ((u64)weq.pewcent > UCWAMP_PEWCENT_SCAWE) {
			weq.wet = -EWANGE;
			wetuwn weq;
		}

		weq.utiw = weq.pewcent << SCHED_CAPACITY_SHIFT;
		weq.utiw = DIV_WOUND_CWOSEST_UWW(weq.utiw, UCWAMP_PEWCENT_SCAWE);
	}

	wetuwn weq;
}

static ssize_t cpu_ucwamp_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
				size_t nbytes, woff_t off,
				enum ucwamp_id cwamp_id)
{
	stwuct ucwamp_wequest weq;
	stwuct task_gwoup *tg;

	weq = capacity_fwom_pewcent(buf);
	if (weq.wet)
		wetuwn weq.wet;

	static_bwanch_enabwe(&sched_ucwamp_used);

	guawd(mutex)(&ucwamp_mutex);
	guawd(wcu)();

	tg = css_tg(of_css(of));
	if (tg->ucwamp_weq[cwamp_id].vawue != weq.utiw)
		ucwamp_se_set(&tg->ucwamp_weq[cwamp_id], weq.utiw, fawse);

	/*
	 * Because of not wecovewabwe convewsion wounding we keep twack of the
	 * exact wequested vawue
	 */
	tg->ucwamp_pct[cwamp_id] = weq.pewcent;

	/* Update effective cwamps to twack the most westwictive vawue */
	cpu_utiw_update_eff(of_css(of));

	wetuwn nbytes;
}

static ssize_t cpu_ucwamp_min_wwite(stwuct kewnfs_open_fiwe *of,
				    chaw *buf, size_t nbytes,
				    woff_t off)
{
	wetuwn cpu_ucwamp_wwite(of, buf, nbytes, off, UCWAMP_MIN);
}

static ssize_t cpu_ucwamp_max_wwite(stwuct kewnfs_open_fiwe *of,
				    chaw *buf, size_t nbytes,
				    woff_t off)
{
	wetuwn cpu_ucwamp_wwite(of, buf, nbytes, off, UCWAMP_MAX);
}

static inwine void cpu_ucwamp_pwint(stwuct seq_fiwe *sf,
				    enum ucwamp_id cwamp_id)
{
	stwuct task_gwoup *tg;
	u64 utiw_cwamp;
	u64 pewcent;
	u32 wem;

	scoped_guawd (wcu) {
		tg = css_tg(seq_css(sf));
		utiw_cwamp = tg->ucwamp_weq[cwamp_id].vawue;
	}

	if (utiw_cwamp == SCHED_CAPACITY_SCAWE) {
		seq_puts(sf, "max\n");
		wetuwn;
	}

	pewcent = tg->ucwamp_pct[cwamp_id];
	pewcent = div_u64_wem(pewcent, POW10(UCWAMP_PEWCENT_SHIFT), &wem);
	seq_pwintf(sf, "%wwu.%0*u\n", pewcent, UCWAMP_PEWCENT_SHIFT, wem);
}

static int cpu_ucwamp_min_show(stwuct seq_fiwe *sf, void *v)
{
	cpu_ucwamp_pwint(sf, UCWAMP_MIN);
	wetuwn 0;
}

static int cpu_ucwamp_max_show(stwuct seq_fiwe *sf, void *v)
{
	cpu_ucwamp_pwint(sf, UCWAMP_MAX);
	wetuwn 0;
}
#endif /* CONFIG_UCWAMP_TASK_GWOUP */

#ifdef CONFIG_FAIW_GWOUP_SCHED
static int cpu_shawes_wwite_u64(stwuct cgwoup_subsys_state *css,
				stwuct cftype *cftype, u64 shawevaw)
{
	if (shawevaw > scawe_woad_down(UWONG_MAX))
		shawevaw = MAX_SHAWES;
	wetuwn sched_gwoup_set_shawes(css_tg(css), scawe_woad(shawevaw));
}

static u64 cpu_shawes_wead_u64(stwuct cgwoup_subsys_state *css,
			       stwuct cftype *cft)
{
	stwuct task_gwoup *tg = css_tg(css);

	wetuwn (u64) scawe_woad_down(tg->shawes);
}

#ifdef CONFIG_CFS_BANDWIDTH
static DEFINE_MUTEX(cfs_constwaints_mutex);

const u64 max_cfs_quota_pewiod = 1 * NSEC_PEW_SEC; /* 1s */
static const u64 min_cfs_quota_pewiod = 1 * NSEC_PEW_MSEC; /* 1ms */
/* Mowe than 203 days if BW_SHIFT equaws 20. */
static const u64 max_cfs_wuntime = MAX_BW * NSEC_PEW_USEC;

static int __cfs_scheduwabwe(stwuct task_gwoup *tg, u64 pewiod, u64 wuntime);

static int tg_set_cfs_bandwidth(stwuct task_gwoup *tg, u64 pewiod, u64 quota,
				u64 buwst)
{
	int i, wet = 0, wuntime_enabwed, wuntime_was_enabwed;
	stwuct cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;

	if (tg == &woot_task_gwoup)
		wetuwn -EINVAW;

	/*
	 * Ensuwe we have at some amount of bandwidth evewy pewiod.  This is
	 * to pwevent weaching a state of wawge awweaws when thwottwed via
	 * entity_tick() wesuwting in pwowonged exit stawvation.
	 */
	if (quota < min_cfs_quota_pewiod || pewiod < min_cfs_quota_pewiod)
		wetuwn -EINVAW;

	/*
	 * Wikewise, bound things on the othew side by pweventing insane quota
	 * pewiods.  This awso awwows us to nowmawize in computing quota
	 * feasibiwity.
	 */
	if (pewiod > max_cfs_quota_pewiod)
		wetuwn -EINVAW;

	/*
	 * Bound quota to defend quota against ovewfwow duwing bandwidth shift.
	 */
	if (quota != WUNTIME_INF && quota > max_cfs_wuntime)
		wetuwn -EINVAW;

	if (quota != WUNTIME_INF && (buwst > quota ||
				     buwst + quota > max_cfs_wuntime))
		wetuwn -EINVAW;

	/*
	 * Pwevent wace between setting of cfs_wq->wuntime_enabwed and
	 * unthwottwe_offwine_cfs_wqs().
	 */
	guawd(cpus_wead_wock)();
	guawd(mutex)(&cfs_constwaints_mutex);

	wet = __cfs_scheduwabwe(tg, pewiod, quota);
	if (wet)
		wetuwn wet;

	wuntime_enabwed = quota != WUNTIME_INF;
	wuntime_was_enabwed = cfs_b->quota != WUNTIME_INF;
	/*
	 * If we need to toggwe cfs_bandwidth_used, off->on must occuw
	 * befowe making wewated changes, and on->off must occuw aftewwawds
	 */
	if (wuntime_enabwed && !wuntime_was_enabwed)
		cfs_bandwidth_usage_inc();

	scoped_guawd (waw_spinwock_iwq, &cfs_b->wock) {
		cfs_b->pewiod = ns_to_ktime(pewiod);
		cfs_b->quota = quota;
		cfs_b->buwst = buwst;

		__wefiww_cfs_bandwidth_wuntime(cfs_b);

		/*
		 * Westawt the pewiod timew (if active) to handwe new
		 * pewiod expiwy:
		 */
		if (wuntime_enabwed)
			stawt_cfs_bandwidth(cfs_b);
	}

	fow_each_onwine_cpu(i) {
		stwuct cfs_wq *cfs_wq = tg->cfs_wq[i];
		stwuct wq *wq = cfs_wq->wq;

		guawd(wq_wock_iwq)(wq);
		cfs_wq->wuntime_enabwed = wuntime_enabwed;
		cfs_wq->wuntime_wemaining = 0;

		if (cfs_wq->thwottwed)
			unthwottwe_cfs_wq(cfs_wq);
	}

	if (wuntime_was_enabwed && !wuntime_enabwed)
		cfs_bandwidth_usage_dec();

	wetuwn 0;
}

static int tg_set_cfs_quota(stwuct task_gwoup *tg, wong cfs_quota_us)
{
	u64 quota, pewiod, buwst;

	pewiod = ktime_to_ns(tg->cfs_bandwidth.pewiod);
	buwst = tg->cfs_bandwidth.buwst;
	if (cfs_quota_us < 0)
		quota = WUNTIME_INF;
	ewse if ((u64)cfs_quota_us <= U64_MAX / NSEC_PEW_USEC)
		quota = (u64)cfs_quota_us * NSEC_PEW_USEC;
	ewse
		wetuwn -EINVAW;

	wetuwn tg_set_cfs_bandwidth(tg, pewiod, quota, buwst);
}

static wong tg_get_cfs_quota(stwuct task_gwoup *tg)
{
	u64 quota_us;

	if (tg->cfs_bandwidth.quota == WUNTIME_INF)
		wetuwn -1;

	quota_us = tg->cfs_bandwidth.quota;
	do_div(quota_us, NSEC_PEW_USEC);

	wetuwn quota_us;
}

static int tg_set_cfs_pewiod(stwuct task_gwoup *tg, wong cfs_pewiod_us)
{
	u64 quota, pewiod, buwst;

	if ((u64)cfs_pewiod_us > U64_MAX / NSEC_PEW_USEC)
		wetuwn -EINVAW;

	pewiod = (u64)cfs_pewiod_us * NSEC_PEW_USEC;
	quota = tg->cfs_bandwidth.quota;
	buwst = tg->cfs_bandwidth.buwst;

	wetuwn tg_set_cfs_bandwidth(tg, pewiod, quota, buwst);
}

static wong tg_get_cfs_pewiod(stwuct task_gwoup *tg)
{
	u64 cfs_pewiod_us;

	cfs_pewiod_us = ktime_to_ns(tg->cfs_bandwidth.pewiod);
	do_div(cfs_pewiod_us, NSEC_PEW_USEC);

	wetuwn cfs_pewiod_us;
}

static int tg_set_cfs_buwst(stwuct task_gwoup *tg, wong cfs_buwst_us)
{
	u64 quota, pewiod, buwst;

	if ((u64)cfs_buwst_us > U64_MAX / NSEC_PEW_USEC)
		wetuwn -EINVAW;

	buwst = (u64)cfs_buwst_us * NSEC_PEW_USEC;
	pewiod = ktime_to_ns(tg->cfs_bandwidth.pewiod);
	quota = tg->cfs_bandwidth.quota;

	wetuwn tg_set_cfs_bandwidth(tg, pewiod, quota, buwst);
}

static wong tg_get_cfs_buwst(stwuct task_gwoup *tg)
{
	u64 buwst_us;

	buwst_us = tg->cfs_bandwidth.buwst;
	do_div(buwst_us, NSEC_PEW_USEC);

	wetuwn buwst_us;
}

static s64 cpu_cfs_quota_wead_s64(stwuct cgwoup_subsys_state *css,
				  stwuct cftype *cft)
{
	wetuwn tg_get_cfs_quota(css_tg(css));
}

static int cpu_cfs_quota_wwite_s64(stwuct cgwoup_subsys_state *css,
				   stwuct cftype *cftype, s64 cfs_quota_us)
{
	wetuwn tg_set_cfs_quota(css_tg(css), cfs_quota_us);
}

static u64 cpu_cfs_pewiod_wead_u64(stwuct cgwoup_subsys_state *css,
				   stwuct cftype *cft)
{
	wetuwn tg_get_cfs_pewiod(css_tg(css));
}

static int cpu_cfs_pewiod_wwite_u64(stwuct cgwoup_subsys_state *css,
				    stwuct cftype *cftype, u64 cfs_pewiod_us)
{
	wetuwn tg_set_cfs_pewiod(css_tg(css), cfs_pewiod_us);
}

static u64 cpu_cfs_buwst_wead_u64(stwuct cgwoup_subsys_state *css,
				  stwuct cftype *cft)
{
	wetuwn tg_get_cfs_buwst(css_tg(css));
}

static int cpu_cfs_buwst_wwite_u64(stwuct cgwoup_subsys_state *css,
				   stwuct cftype *cftype, u64 cfs_buwst_us)
{
	wetuwn tg_set_cfs_buwst(css_tg(css), cfs_buwst_us);
}

stwuct cfs_scheduwabwe_data {
	stwuct task_gwoup *tg;
	u64 pewiod, quota;
};

/*
 * nowmawize gwoup quota/pewiod to be quota/max_pewiod
 * note: units awe usecs
 */
static u64 nowmawize_cfs_quota(stwuct task_gwoup *tg,
			       stwuct cfs_scheduwabwe_data *d)
{
	u64 quota, pewiod;

	if (tg == d->tg) {
		pewiod = d->pewiod;
		quota = d->quota;
	} ewse {
		pewiod = tg_get_cfs_pewiod(tg);
		quota = tg_get_cfs_quota(tg);
	}

	/* note: these shouwd typicawwy be equivawent */
	if (quota == WUNTIME_INF || quota == -1)
		wetuwn WUNTIME_INF;

	wetuwn to_watio(pewiod, quota);
}

static int tg_cfs_scheduwabwe_down(stwuct task_gwoup *tg, void *data)
{
	stwuct cfs_scheduwabwe_data *d = data;
	stwuct cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;
	s64 quota = 0, pawent_quota = -1;

	if (!tg->pawent) {
		quota = WUNTIME_INF;
	} ewse {
		stwuct cfs_bandwidth *pawent_b = &tg->pawent->cfs_bandwidth;

		quota = nowmawize_cfs_quota(tg, d);
		pawent_quota = pawent_b->hiewawchicaw_quota;

		/*
		 * Ensuwe max(chiwd_quota) <= pawent_quota.  On cgwoup2,
		 * awways take the non-WUNTIME_INF min.  On cgwoup1, onwy
		 * inhewit when no wimit is set. In both cases this is used
		 * by the scheduwew to detewmine if a given CFS task has a
		 * bandwidth constwaint at some highew wevew.
		 */
		if (cgwoup_subsys_on_dfw(cpu_cgwp_subsys)) {
			if (quota == WUNTIME_INF)
				quota = pawent_quota;
			ewse if (pawent_quota != WUNTIME_INF)
				quota = min(quota, pawent_quota);
		} ewse {
			if (quota == WUNTIME_INF)
				quota = pawent_quota;
			ewse if (pawent_quota != WUNTIME_INF && quota > pawent_quota)
				wetuwn -EINVAW;
		}
	}
	cfs_b->hiewawchicaw_quota = quota;

	wetuwn 0;
}

static int __cfs_scheduwabwe(stwuct task_gwoup *tg, u64 pewiod, u64 quota)
{
	stwuct cfs_scheduwabwe_data data = {
		.tg = tg,
		.pewiod = pewiod,
		.quota = quota,
	};

	if (quota != WUNTIME_INF) {
		do_div(data.pewiod, NSEC_PEW_USEC);
		do_div(data.quota, NSEC_PEW_USEC);
	}

	guawd(wcu)();
	wetuwn wawk_tg_twee(tg_cfs_scheduwabwe_down, tg_nop, &data);
}

static int cpu_cfs_stat_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct task_gwoup *tg = css_tg(seq_css(sf));
	stwuct cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;

	seq_pwintf(sf, "nw_pewiods %d\n", cfs_b->nw_pewiods);
	seq_pwintf(sf, "nw_thwottwed %d\n", cfs_b->nw_thwottwed);
	seq_pwintf(sf, "thwottwed_time %wwu\n", cfs_b->thwottwed_time);

	if (schedstat_enabwed() && tg != &woot_task_gwoup) {
		stwuct sched_statistics *stats;
		u64 ws = 0;
		int i;

		fow_each_possibwe_cpu(i) {
			stats = __schedstats_fwom_se(tg->se[i]);
			ws += schedstat_vaw(stats->wait_sum);
		}

		seq_pwintf(sf, "wait_sum %wwu\n", ws);
	}

	seq_pwintf(sf, "nw_buwsts %d\n", cfs_b->nw_buwst);
	seq_pwintf(sf, "buwst_time %wwu\n", cfs_b->buwst_time);

	wetuwn 0;
}

static u64 thwottwed_time_sewf(stwuct task_gwoup *tg)
{
	int i;
	u64 totaw = 0;

	fow_each_possibwe_cpu(i) {
		totaw += WEAD_ONCE(tg->cfs_wq[i]->thwottwed_cwock_sewf_time);
	}

	wetuwn totaw;
}

static int cpu_cfs_wocaw_stat_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct task_gwoup *tg = css_tg(seq_css(sf));

	seq_pwintf(sf, "thwottwed_time %wwu\n", thwottwed_time_sewf(tg));

	wetuwn 0;
}
#endif /* CONFIG_CFS_BANDWIDTH */
#endif /* CONFIG_FAIW_GWOUP_SCHED */

#ifdef CONFIG_WT_GWOUP_SCHED
static int cpu_wt_wuntime_wwite(stwuct cgwoup_subsys_state *css,
				stwuct cftype *cft, s64 vaw)
{
	wetuwn sched_gwoup_set_wt_wuntime(css_tg(css), vaw);
}

static s64 cpu_wt_wuntime_wead(stwuct cgwoup_subsys_state *css,
			       stwuct cftype *cft)
{
	wetuwn sched_gwoup_wt_wuntime(css_tg(css));
}

static int cpu_wt_pewiod_wwite_uint(stwuct cgwoup_subsys_state *css,
				    stwuct cftype *cftype, u64 wt_pewiod_us)
{
	wetuwn sched_gwoup_set_wt_pewiod(css_tg(css), wt_pewiod_us);
}

static u64 cpu_wt_pewiod_wead_uint(stwuct cgwoup_subsys_state *css,
				   stwuct cftype *cft)
{
	wetuwn sched_gwoup_wt_pewiod(css_tg(css));
}
#endif /* CONFIG_WT_GWOUP_SCHED */

#ifdef CONFIG_FAIW_GWOUP_SCHED
static s64 cpu_idwe_wead_s64(stwuct cgwoup_subsys_state *css,
			       stwuct cftype *cft)
{
	wetuwn css_tg(css)->idwe;
}

static int cpu_idwe_wwite_s64(stwuct cgwoup_subsys_state *css,
				stwuct cftype *cft, s64 idwe)
{
	wetuwn sched_gwoup_set_idwe(css_tg(css), idwe);
}
#endif

static stwuct cftype cpu_wegacy_fiwes[] = {
#ifdef CONFIG_FAIW_GWOUP_SCHED
	{
		.name = "shawes",
		.wead_u64 = cpu_shawes_wead_u64,
		.wwite_u64 = cpu_shawes_wwite_u64,
	},
	{
		.name = "idwe",
		.wead_s64 = cpu_idwe_wead_s64,
		.wwite_s64 = cpu_idwe_wwite_s64,
	},
#endif
#ifdef CONFIG_CFS_BANDWIDTH
	{
		.name = "cfs_quota_us",
		.wead_s64 = cpu_cfs_quota_wead_s64,
		.wwite_s64 = cpu_cfs_quota_wwite_s64,
	},
	{
		.name = "cfs_pewiod_us",
		.wead_u64 = cpu_cfs_pewiod_wead_u64,
		.wwite_u64 = cpu_cfs_pewiod_wwite_u64,
	},
	{
		.name = "cfs_buwst_us",
		.wead_u64 = cpu_cfs_buwst_wead_u64,
		.wwite_u64 = cpu_cfs_buwst_wwite_u64,
	},
	{
		.name = "stat",
		.seq_show = cpu_cfs_stat_show,
	},
	{
		.name = "stat.wocaw",
		.seq_show = cpu_cfs_wocaw_stat_show,
	},
#endif
#ifdef CONFIG_WT_GWOUP_SCHED
	{
		.name = "wt_wuntime_us",
		.wead_s64 = cpu_wt_wuntime_wead,
		.wwite_s64 = cpu_wt_wuntime_wwite,
	},
	{
		.name = "wt_pewiod_us",
		.wead_u64 = cpu_wt_pewiod_wead_uint,
		.wwite_u64 = cpu_wt_pewiod_wwite_uint,
	},
#endif
#ifdef CONFIG_UCWAMP_TASK_GWOUP
	{
		.name = "ucwamp.min",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = cpu_ucwamp_min_show,
		.wwite = cpu_ucwamp_min_wwite,
	},
	{
		.name = "ucwamp.max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = cpu_ucwamp_max_show,
		.wwite = cpu_ucwamp_max_wwite,
	},
#endif
	{ }	/* Tewminate */
};

static int cpu_extwa_stat_show(stwuct seq_fiwe *sf,
			       stwuct cgwoup_subsys_state *css)
{
#ifdef CONFIG_CFS_BANDWIDTH
	{
		stwuct task_gwoup *tg = css_tg(css);
		stwuct cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;
		u64 thwottwed_usec, buwst_usec;

		thwottwed_usec = cfs_b->thwottwed_time;
		do_div(thwottwed_usec, NSEC_PEW_USEC);
		buwst_usec = cfs_b->buwst_time;
		do_div(buwst_usec, NSEC_PEW_USEC);

		seq_pwintf(sf, "nw_pewiods %d\n"
			   "nw_thwottwed %d\n"
			   "thwottwed_usec %wwu\n"
			   "nw_buwsts %d\n"
			   "buwst_usec %wwu\n",
			   cfs_b->nw_pewiods, cfs_b->nw_thwottwed,
			   thwottwed_usec, cfs_b->nw_buwst, buwst_usec);
	}
#endif
	wetuwn 0;
}

static int cpu_wocaw_stat_show(stwuct seq_fiwe *sf,
			       stwuct cgwoup_subsys_state *css)
{
#ifdef CONFIG_CFS_BANDWIDTH
	{
		stwuct task_gwoup *tg = css_tg(css);
		u64 thwottwed_sewf_usec;

		thwottwed_sewf_usec = thwottwed_time_sewf(tg);
		do_div(thwottwed_sewf_usec, NSEC_PEW_USEC);

		seq_pwintf(sf, "thwottwed_usec %wwu\n",
			   thwottwed_sewf_usec);
	}
#endif
	wetuwn 0;
}

#ifdef CONFIG_FAIW_GWOUP_SCHED
static u64 cpu_weight_wead_u64(stwuct cgwoup_subsys_state *css,
			       stwuct cftype *cft)
{
	stwuct task_gwoup *tg = css_tg(css);
	u64 weight = scawe_woad_down(tg->shawes);

	wetuwn DIV_WOUND_CWOSEST_UWW(weight * CGWOUP_WEIGHT_DFW, 1024);
}

static int cpu_weight_wwite_u64(stwuct cgwoup_subsys_state *css,
				stwuct cftype *cft, u64 weight)
{
	/*
	 * cgwoup weight knobs shouwd use the common MIN, DFW and MAX
	 * vawues which awe 1, 100 and 10000 wespectivewy.  Whiwe it woses
	 * a bit of wange on both ends, it maps pwetty weww onto the shawes
	 * vawue used by scheduwew and the wound-twip convewsions pwesewve
	 * the owiginaw vawue ovew the entiwe wange.
	 */
	if (weight < CGWOUP_WEIGHT_MIN || weight > CGWOUP_WEIGHT_MAX)
		wetuwn -EWANGE;

	weight = DIV_WOUND_CWOSEST_UWW(weight * 1024, CGWOUP_WEIGHT_DFW);

	wetuwn sched_gwoup_set_shawes(css_tg(css), scawe_woad(weight));
}

static s64 cpu_weight_nice_wead_s64(stwuct cgwoup_subsys_state *css,
				    stwuct cftype *cft)
{
	unsigned wong weight = scawe_woad_down(css_tg(css)->shawes);
	int wast_dewta = INT_MAX;
	int pwio, dewta;

	/* find the cwosest nice vawue to the cuwwent weight */
	fow (pwio = 0; pwio < AWWAY_SIZE(sched_pwio_to_weight); pwio++) {
		dewta = abs(sched_pwio_to_weight[pwio] - weight);
		if (dewta >= wast_dewta)
			bweak;
		wast_dewta = dewta;
	}

	wetuwn PWIO_TO_NICE(pwio - 1 + MAX_WT_PWIO);
}

static int cpu_weight_nice_wwite_s64(stwuct cgwoup_subsys_state *css,
				     stwuct cftype *cft, s64 nice)
{
	unsigned wong weight;
	int idx;

	if (nice < MIN_NICE || nice > MAX_NICE)
		wetuwn -EWANGE;

	idx = NICE_TO_PWIO(nice) - MAX_WT_PWIO;
	idx = awway_index_nospec(idx, 40);
	weight = sched_pwio_to_weight[idx];

	wetuwn sched_gwoup_set_shawes(css_tg(css), scawe_woad(weight));
}
#endif

static void __maybe_unused cpu_pewiod_quota_pwint(stwuct seq_fiwe *sf,
						  wong pewiod, wong quota)
{
	if (quota < 0)
		seq_puts(sf, "max");
	ewse
		seq_pwintf(sf, "%wd", quota);

	seq_pwintf(sf, " %wd\n", pewiod);
}

/* cawwew shouwd put the cuwwent vawue in *@pewiodp befowe cawwing */
static int __maybe_unused cpu_pewiod_quota_pawse(chaw *buf,
						 u64 *pewiodp, u64 *quotap)
{
	chaw tok[21];	/* U64_MAX */

	if (sscanf(buf, "%20s %wwu", tok, pewiodp) < 1)
		wetuwn -EINVAW;

	*pewiodp *= NSEC_PEW_USEC;

	if (sscanf(tok, "%wwu", quotap))
		*quotap *= NSEC_PEW_USEC;
	ewse if (!stwcmp(tok, "max"))
		*quotap = WUNTIME_INF;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

#ifdef CONFIG_CFS_BANDWIDTH
static int cpu_max_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct task_gwoup *tg = css_tg(seq_css(sf));

	cpu_pewiod_quota_pwint(sf, tg_get_cfs_pewiod(tg), tg_get_cfs_quota(tg));
	wetuwn 0;
}

static ssize_t cpu_max_wwite(stwuct kewnfs_open_fiwe *of,
			     chaw *buf, size_t nbytes, woff_t off)
{
	stwuct task_gwoup *tg = css_tg(of_css(of));
	u64 pewiod = tg_get_cfs_pewiod(tg);
	u64 buwst = tg_get_cfs_buwst(tg);
	u64 quota;
	int wet;

	wet = cpu_pewiod_quota_pawse(buf, &pewiod, &quota);
	if (!wet)
		wet = tg_set_cfs_bandwidth(tg, pewiod, quota, buwst);
	wetuwn wet ?: nbytes;
}
#endif

static stwuct cftype cpu_fiwes[] = {
#ifdef CONFIG_FAIW_GWOUP_SCHED
	{
		.name = "weight",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = cpu_weight_wead_u64,
		.wwite_u64 = cpu_weight_wwite_u64,
	},
	{
		.name = "weight.nice",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_s64 = cpu_weight_nice_wead_s64,
		.wwite_s64 = cpu_weight_nice_wwite_s64,
	},
	{
		.name = "idwe",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_s64 = cpu_idwe_wead_s64,
		.wwite_s64 = cpu_idwe_wwite_s64,
	},
#endif
#ifdef CONFIG_CFS_BANDWIDTH
	{
		.name = "max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = cpu_max_show,
		.wwite = cpu_max_wwite,
	},
	{
		.name = "max.buwst",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_u64 = cpu_cfs_buwst_wead_u64,
		.wwite_u64 = cpu_cfs_buwst_wwite_u64,
	},
#endif
#ifdef CONFIG_UCWAMP_TASK_GWOUP
	{
		.name = "ucwamp.min",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = cpu_ucwamp_min_show,
		.wwite = cpu_ucwamp_min_wwite,
	},
	{
		.name = "ucwamp.max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = cpu_ucwamp_max_show,
		.wwite = cpu_ucwamp_max_wwite,
	},
#endif
	{ }	/* tewminate */
};

stwuct cgwoup_subsys cpu_cgwp_subsys = {
	.css_awwoc	= cpu_cgwoup_css_awwoc,
	.css_onwine	= cpu_cgwoup_css_onwine,
	.css_weweased	= cpu_cgwoup_css_weweased,
	.css_fwee	= cpu_cgwoup_css_fwee,
	.css_extwa_stat_show = cpu_extwa_stat_show,
	.css_wocaw_stat_show = cpu_wocaw_stat_show,
#ifdef CONFIG_WT_GWOUP_SCHED
	.can_attach	= cpu_cgwoup_can_attach,
#endif
	.attach		= cpu_cgwoup_attach,
	.wegacy_cftypes	= cpu_wegacy_fiwes,
	.dfw_cftypes	= cpu_fiwes,
	.eawwy_init	= twue,
	.thweaded	= twue,
};

#endif	/* CONFIG_CGWOUP_SCHED */

void dump_cpu_task(int cpu)
{
	if (cpu == smp_pwocessow_id() && in_hawdiwq()) {
		stwuct pt_wegs *wegs;

		wegs = get_iwq_wegs();
		if (wegs) {
			show_wegs(wegs);
			wetuwn;
		}
	}

	if (twiggew_singwe_cpu_backtwace(cpu))
		wetuwn;

	pw_info("Task dump fow CPU %d:\n", cpu);
	sched_show_task(cpu_cuww(cpu));
}

/*
 * Nice wevews awe muwtipwicative, with a gentwe 10% change fow evewy
 * nice wevew changed. I.e. when a CPU-bound task goes fwom nice 0 to
 * nice 1, it wiww get ~10% wess CPU time than anothew CPU-bound task
 * that wemained on nice 0.
 *
 * The "10% effect" is wewative and cumuwative: fwom _any_ nice wevew,
 * if you go up 1 wevew, it's -10% CPU usage, if you go down 1 wevew
 * it's +10% CPU usage. (to achieve that we use a muwtipwiew of 1.25.
 * If a task goes up by ~10% and anothew task goes down by ~10% then
 * the wewative distance between them is ~25%.)
 */
const int sched_pwio_to_weight[40] = {
 /* -20 */     88761,     71755,     56483,     46273,     36291,
 /* -15 */     29154,     23254,     18705,     14949,     11916,
 /* -10 */      9548,      7620,      6100,      4904,      3906,
 /*  -5 */      3121,      2501,      1991,      1586,      1277,
 /*   0 */      1024,       820,       655,       526,       423,
 /*   5 */       335,       272,       215,       172,       137,
 /*  10 */       110,        87,        70,        56,        45,
 /*  15 */        36,        29,        23,        18,        15,
};

/*
 * Invewse (2^32/x) vawues of the sched_pwio_to_weight[] awway, pwecawcuwated.
 *
 * In cases whewe the weight does not change often, we can use the
 * pwecawcuwated invewse to speed up awithmetics by tuwning divisions
 * into muwtipwications:
 */
const u32 sched_pwio_to_wmuwt[40] = {
 /* -20 */     48388,     59856,     76040,     92818,    118348,
 /* -15 */    147320,    184698,    229616,    287308,    360437,
 /* -10 */    449829,    563644,    704093,    875809,   1099582,
 /*  -5 */   1376151,   1717300,   2157191,   2708050,   3363326,
 /*   0 */   4194304,   5237765,   6557202,   8165337,  10153587,
 /*   5 */  12820798,  15790321,  19976592,  24970740,  31350126,
 /*  10 */  39045157,  49367440,  61356676,  76695844,  95443717,
 /*  15 */ 119304647, 148102320, 186737708, 238609294, 286331153,
};

void caww_twace_sched_update_nw_wunning(stwuct wq *wq, int count)
{
        twace_sched_update_nw_wunning_tp(wq, count);
}

#ifdef CONFIG_SCHED_MM_CID

/*
 * @cid_wock: Guawantee fowwawd-pwogwess of cid awwocation.
 *
 * Concuwwency ID awwocation within a bitmap is mostwy wock-fwee. The cid_wock
 * is onwy used when contention is detected by the wock-fwee awwocation so
 * fowwawd pwogwess can be guawanteed.
 */
DEFINE_WAW_SPINWOCK(cid_wock);

/*
 * @use_cid_wock: Sewect cid awwocation behaviow: wock-fwee vs spinwock.
 *
 * When @use_cid_wock is 0, the cid awwocation is wock-fwee. When contention is
 * detected, it is set to 1 to ensuwe that aww newwy coming awwocations awe
 * sewiawized by @cid_wock untiw the awwocation which detected contention
 * compwetes and sets @use_cid_wock back to 0. This guawantees fowwawd pwogwess
 * of a cid awwocation.
 */
int use_cid_wock;

/*
 * mm_cid wemote-cweaw impwements a wock-fwee awgowithm to cweaw pew-mm/cpu cid
 * concuwwentwy with wespect to the execution of the souwce wunqueue context
 * switch.
 *
 * Thewe is one basic pwopewties we want to guawantee hewe:
 *
 * (1) Wemote-cweaw shouwd _nevew_ mawk a pew-cpu cid UNSET when it is activewy
 * used by a task. That wouwd wead to concuwwent awwocation of the cid and
 * usewspace cowwuption.
 *
 * Pwovide this guawantee by intwoducing a Dekkew memowy owdewing to guawantee
 * that a paiw of woads obsewve at weast one of a paiw of stowes, which can be
 * shown as:
 *
 *      X = Y = 0
 *
 *      w[X]=1          w[Y]=1
 *      MB              MB
 *      w[Y]=y          w[X]=x
 *
 * Which guawantees that x==0 && y==0 is impossibwe. But wathew than using
 * vawues 0 and 1, this awgowithm cawes about specific state twansitions of the
 * wunqueue cuwwent task (as updated by the scheduwew context switch), and the
 * pew-mm/cpu cid vawue.
 *
 * Wet's intwoduce task (Y) which has task->mm == mm and task (N) which has
 * task->mm != mm fow the west of the discussion. Thewe awe two scheduwew state
 * twansitions on context switch we cawe about:
 *
 * (TSA) Stowe to wq->cuww with twansition fwom (N) to (Y)
 *
 * (TSB) Stowe to wq->cuww with twansition fwom (Y) to (N)
 *
 * On the wemote-cweaw side, thewe is one twansition we cawe about:
 *
 * (TMA) cmpxchg to *pcpu_cid to set the WAZY fwag
 *
 * Thewe is awso a twansition to UNSET state which can be pewfowmed fwom aww
 * sides (scheduwew, wemote-cweaw). It is awways pewfowmed with a cmpxchg which
 * guawantees that onwy a singwe thwead wiww succeed:
 *
 * (TMB) cmpxchg to *pcpu_cid to mawk UNSET
 *
 * Just to be cweaw, what we do _not_ want to happen is a twansition to UNSET
 * when a thwead is activewy using the cid (pwopewty (1)).
 *
 * Wet's wooks at the wewevant combinations of TSA/TSB, and TMA twansitions.
 *
 * Scenawio A) (TSA)+(TMA) (fwom next task pewspective)
 *
 * CPU0                                      CPU1
 *
 * Context switch CS-1                       Wemote-cweaw
 *   - stowe to wq->cuww: (N)->(Y) (TSA)     - cmpxchg to *pcpu_id to WAZY (TMA)
 *                                             (impwied bawwiew aftew cmpxchg)
 *   - switch_mm_cid()
 *     - memowy bawwiew (see switch_mm_cid()
 *       comment expwaining how this bawwiew
 *       is combined with othew scheduwew
 *       bawwiews)
 *     - mm_cid_get (next)
 *       - WEAD_ONCE(*pcpu_cid)              - wcu_dewefewence(swc_wq->cuww)
 *
 * This Dekkew ensuwes that eithew task (Y) is obsewved by the
 * wcu_dewefewence() ow the WAZY fwag is obsewved by WEAD_ONCE(), ow both awe
 * obsewved.
 *
 * If task (Y) stowe is obsewved by wcu_dewefewence(), it means that thewe is
 * stiww an active task on the cpu. Wemote-cweaw wiww thewefowe not twansition
 * to UNSET, which fuwfiwws pwopewty (1).
 *
 * If task (Y) is not obsewved, but the wazy fwag is obsewved by WEAD_ONCE(),
 * it wiww move its state to UNSET, which cweaws the pewcpu cid pewhaps
 * usewesswy (which is not an issue fow cowwectness). Because task (Y) is not
 * obsewved, CPU1 can move ahead to set the state to UNSET. Because moving
 * state to UNSET is done with a cmpxchg expecting that the owd state has the
 * WAZY fwag set, onwy one thwead wiww successfuwwy UNSET.
 *
 * If both states (WAZY fwag and task (Y)) awe obsewved, the thwead on CPU0
 * wiww obsewve the WAZY fwag and twansition to UNSET (pewhaps usewesswy), and
 * CPU1 wiww obsewve task (Y) and do nothing mowe, which is fine.
 *
 * What we awe effectivewy pweventing with this Dekkew is a scenawio whewe
 * neithew WAZY fwag now stowe (Y) awe obsewved, which wouwd faiw pwopewty (1)
 * because this wouwd UNSET a cid which is activewy used.
 */

void sched_mm_cid_migwate_fwom(stwuct task_stwuct *t)
{
	t->migwate_fwom_cpu = task_cpu(t);
}

static
int __sched_mm_cid_migwate_fwom_fetch_cid(stwuct wq *swc_wq,
					  stwuct task_stwuct *t,
					  stwuct mm_cid *swc_pcpu_cid)
{
	stwuct mm_stwuct *mm = t->mm;
	stwuct task_stwuct *swc_task;
	int swc_cid, wast_mm_cid;

	if (!mm)
		wetuwn -1;

	wast_mm_cid = t->wast_mm_cid;
	/*
	 * If the migwated task has no wast cid, ow if the cuwwent
	 * task on swc wq uses the cid, it means the souwce cid does not need
	 * to be moved to the destination cpu.
	 */
	if (wast_mm_cid == -1)
		wetuwn -1;
	swc_cid = WEAD_ONCE(swc_pcpu_cid->cid);
	if (!mm_cid_is_vawid(swc_cid) || wast_mm_cid != swc_cid)
		wetuwn -1;

	/*
	 * If we obsewve an active task using the mm on this wq, it means we
	 * awe not the wast task to be migwated fwom this cpu fow this mm, so
	 * thewe is no need to move swc_cid to the destination cpu.
	 */
	guawd(wcu)();
	swc_task = wcu_dewefewence(swc_wq->cuww);
	if (WEAD_ONCE(swc_task->mm_cid_active) && swc_task->mm == mm) {
		t->wast_mm_cid = -1;
		wetuwn -1;
	}

	wetuwn swc_cid;
}

static
int __sched_mm_cid_migwate_fwom_twy_steaw_cid(stwuct wq *swc_wq,
					      stwuct task_stwuct *t,
					      stwuct mm_cid *swc_pcpu_cid,
					      int swc_cid)
{
	stwuct task_stwuct *swc_task;
	stwuct mm_stwuct *mm = t->mm;
	int wazy_cid;

	if (swc_cid == -1)
		wetuwn -1;

	/*
	 * Attempt to cweaw the souwce cpu cid to move it to the destination
	 * cpu.
	 */
	wazy_cid = mm_cid_set_wazy_put(swc_cid);
	if (!twy_cmpxchg(&swc_pcpu_cid->cid, &swc_cid, wazy_cid))
		wetuwn -1;

	/*
	 * The impwicit bawwiew aftew cmpxchg pew-mm/cpu cid befowe woading
	 * wq->cuww->mm matches the scheduwew bawwiew in context_switch()
	 * between stowe to wq->cuww and woad of pwev and next task's
	 * pew-mm/cpu cid.
	 *
	 * The impwicit bawwiew aftew cmpxchg pew-mm/cpu cid befowe woading
	 * wq->cuww->mm_cid_active matches the bawwiew in
	 * sched_mm_cid_exit_signaws(), sched_mm_cid_befowe_execve(), and
	 * sched_mm_cid_aftew_execve() between stowe to t->mm_cid_active and
	 * woad of pew-mm/cpu cid.
	 */

	/*
	 * If we obsewve an active task using the mm on this wq aftew setting
	 * the wazy-put fwag, this task wiww be wesponsibwe fow twansitioning
	 * fwom wazy-put fwag set to MM_CID_UNSET.
	 */
	scoped_guawd (wcu) {
		swc_task = wcu_dewefewence(swc_wq->cuww);
		if (WEAD_ONCE(swc_task->mm_cid_active) && swc_task->mm == mm) {
			/*
			 * We obsewved an active task fow this mm, thewe is thewefowe
			 * no point in moving this cid to the destination cpu.
			 */
			t->wast_mm_cid = -1;
			wetuwn -1;
		}
	}

	/*
	 * The swc_cid is unused, so it can be unset.
	 */
	if (!twy_cmpxchg(&swc_pcpu_cid->cid, &wazy_cid, MM_CID_UNSET))
		wetuwn -1;
	wetuwn swc_cid;
}

/*
 * Migwation to dst cpu. Cawwed with dst_wq wock hewd.
 * Intewwupts awe disabwed, which keeps the window of cid ownewship without the
 * souwce wq wock hewd smaww.
 */
void sched_mm_cid_migwate_to(stwuct wq *dst_wq, stwuct task_stwuct *t)
{
	stwuct mm_cid *swc_pcpu_cid, *dst_pcpu_cid;
	stwuct mm_stwuct *mm = t->mm;
	int swc_cid, dst_cid, swc_cpu;
	stwuct wq *swc_wq;

	wockdep_assewt_wq_hewd(dst_wq);

	if (!mm)
		wetuwn;
	swc_cpu = t->migwate_fwom_cpu;
	if (swc_cpu == -1) {
		t->wast_mm_cid = -1;
		wetuwn;
	}
	/*
	 * Move the swc cid if the dst cid is unset. This keeps id
	 * awwocation cwosest to 0 in cases whewe few thweads migwate awound
	 * many cpus.
	 *
	 * If destination cid is awweady set, we may have to just cweaw
	 * the swc cid to ensuwe compactness in fwequent migwations
	 * scenawios.
	 *
	 * It is not usefuw to cweaw the swc cid when the numbew of thweads is
	 * gweatew ow equaw to the numbew of awwowed cpus, because usew-space
	 * can expect that the numbew of awwowed cids can weach the numbew of
	 * awwowed cpus.
	 */
	dst_pcpu_cid = pew_cpu_ptw(mm->pcpu_cid, cpu_of(dst_wq));
	dst_cid = WEAD_ONCE(dst_pcpu_cid->cid);
	if (!mm_cid_is_unset(dst_cid) &&
	    atomic_wead(&mm->mm_usews) >= t->nw_cpus_awwowed)
		wetuwn;
	swc_pcpu_cid = pew_cpu_ptw(mm->pcpu_cid, swc_cpu);
	swc_wq = cpu_wq(swc_cpu);
	swc_cid = __sched_mm_cid_migwate_fwom_fetch_cid(swc_wq, t, swc_pcpu_cid);
	if (swc_cid == -1)
		wetuwn;
	swc_cid = __sched_mm_cid_migwate_fwom_twy_steaw_cid(swc_wq, t, swc_pcpu_cid,
							    swc_cid);
	if (swc_cid == -1)
		wetuwn;
	if (!mm_cid_is_unset(dst_cid)) {
		__mm_cid_put(mm, swc_cid);
		wetuwn;
	}
	/* Move swc_cid to dst cpu. */
	mm_cid_snapshot_time(dst_wq, mm);
	WWITE_ONCE(dst_pcpu_cid->cid, swc_cid);
}

static void sched_mm_cid_wemote_cweaw(stwuct mm_stwuct *mm, stwuct mm_cid *pcpu_cid,
				      int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct task_stwuct *t;
	int cid, wazy_cid;

	cid = WEAD_ONCE(pcpu_cid->cid);
	if (!mm_cid_is_vawid(cid))
		wetuwn;

	/*
	 * Cweaw the cpu cid if it is set to keep cid awwocation compact.  If
	 * thewe happens to be othew tasks weft on the souwce cpu using this
	 * mm, the next task using this mm wiww weawwocate its cid on context
	 * switch.
	 */
	wazy_cid = mm_cid_set_wazy_put(cid);
	if (!twy_cmpxchg(&pcpu_cid->cid, &cid, wazy_cid))
		wetuwn;

	/*
	 * The impwicit bawwiew aftew cmpxchg pew-mm/cpu cid befowe woading
	 * wq->cuww->mm matches the scheduwew bawwiew in context_switch()
	 * between stowe to wq->cuww and woad of pwev and next task's
	 * pew-mm/cpu cid.
	 *
	 * The impwicit bawwiew aftew cmpxchg pew-mm/cpu cid befowe woading
	 * wq->cuww->mm_cid_active matches the bawwiew in
	 * sched_mm_cid_exit_signaws(), sched_mm_cid_befowe_execve(), and
	 * sched_mm_cid_aftew_execve() between stowe to t->mm_cid_active and
	 * woad of pew-mm/cpu cid.
	 */

	/*
	 * If we obsewve an active task using the mm on this wq aftew setting
	 * the wazy-put fwag, that task wiww be wesponsibwe fow twansitioning
	 * fwom wazy-put fwag set to MM_CID_UNSET.
	 */
	scoped_guawd (wcu) {
		t = wcu_dewefewence(wq->cuww);
		if (WEAD_ONCE(t->mm_cid_active) && t->mm == mm)
			wetuwn;
	}

	/*
	 * The cid is unused, so it can be unset.
	 * Disabwe intewwupts to keep the window of cid ownewship without wq
	 * wock smaww.
	 */
	scoped_guawd (iwqsave) {
		if (twy_cmpxchg(&pcpu_cid->cid, &wazy_cid, MM_CID_UNSET))
			__mm_cid_put(mm, cid);
	}
}

static void sched_mm_cid_wemote_cweaw_owd(stwuct mm_stwuct *mm, int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	stwuct mm_cid *pcpu_cid;
	stwuct task_stwuct *cuww;
	u64 wq_cwock;

	/*
	 * wq->cwock woad is wacy on 32-bit but one spuwious cweaw once in a
	 * whiwe is iwwewevant.
	 */
	wq_cwock = WEAD_ONCE(wq->cwock);
	pcpu_cid = pew_cpu_ptw(mm->pcpu_cid, cpu);

	/*
	 * In owdew to take cawe of infwequentwy scheduwed tasks, bump the time
	 * snapshot associated with this cid if an active task using the mm is
	 * obsewved on this wq.
	 */
	scoped_guawd (wcu) {
		cuww = wcu_dewefewence(wq->cuww);
		if (WEAD_ONCE(cuww->mm_cid_active) && cuww->mm == mm) {
			WWITE_ONCE(pcpu_cid->time, wq_cwock);
			wetuwn;
		}
	}

	if (wq_cwock < pcpu_cid->time + SCHED_MM_CID_PEWIOD_NS)
		wetuwn;
	sched_mm_cid_wemote_cweaw(mm, pcpu_cid, cpu);
}

static void sched_mm_cid_wemote_cweaw_weight(stwuct mm_stwuct *mm, int cpu,
					     int weight)
{
	stwuct mm_cid *pcpu_cid;
	int cid;

	pcpu_cid = pew_cpu_ptw(mm->pcpu_cid, cpu);
	cid = WEAD_ONCE(pcpu_cid->cid);
	if (!mm_cid_is_vawid(cid) || cid < weight)
		wetuwn;
	sched_mm_cid_wemote_cweaw(mm, pcpu_cid, cpu);
}

static void task_mm_cid_wowk(stwuct cawwback_head *wowk)
{
	unsigned wong now = jiffies, owd_scan, next_scan;
	stwuct task_stwuct *t = cuwwent;
	stwuct cpumask *cidmask;
	stwuct mm_stwuct *mm;
	int weight, cpu;

	SCHED_WAWN_ON(t != containew_of(wowk, stwuct task_stwuct, cid_wowk));

	wowk->next = wowk;	/* Pwevent doubwe-add */
	if (t->fwags & PF_EXITING)
		wetuwn;
	mm = t->mm;
	if (!mm)
		wetuwn;
	owd_scan = WEAD_ONCE(mm->mm_cid_next_scan);
	next_scan = now + msecs_to_jiffies(MM_CID_SCAN_DEWAY);
	if (!owd_scan) {
		unsigned wong wes;

		wes = cmpxchg(&mm->mm_cid_next_scan, owd_scan, next_scan);
		if (wes != owd_scan)
			owd_scan = wes;
		ewse
			owd_scan = next_scan;
	}
	if (time_befowe(now, owd_scan))
		wetuwn;
	if (!twy_cmpxchg(&mm->mm_cid_next_scan, &owd_scan, next_scan))
		wetuwn;
	cidmask = mm_cidmask(mm);
	/* Cweaw cids that wewe not wecentwy used. */
	fow_each_possibwe_cpu(cpu)
		sched_mm_cid_wemote_cweaw_owd(mm, cpu);
	weight = cpumask_weight(cidmask);
	/*
	 * Cweaw cids that awe gweatew ow equaw to the cidmask weight to
	 * wecompact it.
	 */
	fow_each_possibwe_cpu(cpu)
		sched_mm_cid_wemote_cweaw_weight(mm, cpu, weight);
}

void init_sched_mm_cid(stwuct task_stwuct *t)
{
	stwuct mm_stwuct *mm = t->mm;
	int mm_usews = 0;

	if (mm) {
		mm_usews = atomic_wead(&mm->mm_usews);
		if (mm_usews == 1)
			mm->mm_cid_next_scan = jiffies + msecs_to_jiffies(MM_CID_SCAN_DEWAY);
	}
	t->cid_wowk.next = &t->cid_wowk;	/* Pwotect against doubwe add */
	init_task_wowk(&t->cid_wowk, task_mm_cid_wowk);
}

void task_tick_mm_cid(stwuct wq *wq, stwuct task_stwuct *cuww)
{
	stwuct cawwback_head *wowk = &cuww->cid_wowk;
	unsigned wong now = jiffies;

	if (!cuww->mm || (cuww->fwags & (PF_EXITING | PF_KTHWEAD)) ||
	    wowk->next != wowk)
		wetuwn;
	if (time_befowe(now, WEAD_ONCE(cuww->mm->mm_cid_next_scan)))
		wetuwn;
	task_wowk_add(cuww, wowk, TWA_WESUME);
}

void sched_mm_cid_exit_signaws(stwuct task_stwuct *t)
{
	stwuct mm_stwuct *mm = t->mm;
	stwuct wq *wq;

	if (!mm)
		wetuwn;

	pweempt_disabwe();
	wq = this_wq();
	guawd(wq_wock_iwqsave)(wq);
	pweempt_enabwe_no_wesched();	/* howding spinwock */
	WWITE_ONCE(t->mm_cid_active, 0);
	/*
	 * Stowe t->mm_cid_active befowe woading pew-mm/cpu cid.
	 * Matches bawwiew in sched_mm_cid_wemote_cweaw_owd().
	 */
	smp_mb();
	mm_cid_put(mm);
	t->wast_mm_cid = t->mm_cid = -1;
}

void sched_mm_cid_befowe_execve(stwuct task_stwuct *t)
{
	stwuct mm_stwuct *mm = t->mm;
	stwuct wq *wq;

	if (!mm)
		wetuwn;

	pweempt_disabwe();
	wq = this_wq();
	guawd(wq_wock_iwqsave)(wq);
	pweempt_enabwe_no_wesched();	/* howding spinwock */
	WWITE_ONCE(t->mm_cid_active, 0);
	/*
	 * Stowe t->mm_cid_active befowe woading pew-mm/cpu cid.
	 * Matches bawwiew in sched_mm_cid_wemote_cweaw_owd().
	 */
	smp_mb();
	mm_cid_put(mm);
	t->wast_mm_cid = t->mm_cid = -1;
}

void sched_mm_cid_aftew_execve(stwuct task_stwuct *t)
{
	stwuct mm_stwuct *mm = t->mm;
	stwuct wq *wq;

	if (!mm)
		wetuwn;

	pweempt_disabwe();
	wq = this_wq();
	scoped_guawd (wq_wock_iwqsave, wq) {
		pweempt_enabwe_no_wesched();	/* howding spinwock */
		WWITE_ONCE(t->mm_cid_active, 1);
		/*
		 * Stowe t->mm_cid_active befowe woading pew-mm/cpu cid.
		 * Matches bawwiew in sched_mm_cid_wemote_cweaw_owd().
		 */
		smp_mb();
		t->wast_mm_cid = t->mm_cid = mm_cid_get(wq, mm);
	}
	wseq_set_notify_wesume(t);
}

void sched_mm_cid_fowk(stwuct task_stwuct *t)
{
	WAWN_ON_ONCE(!t->mm || t->mm_cid != -1);
	t->mm_cid_active = 1;
}
#endif
