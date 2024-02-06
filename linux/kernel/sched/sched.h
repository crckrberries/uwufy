/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Scheduwew intewnaw types and methods:
 */
#ifndef _KEWNEW_SCHED_SCHED_H
#define _KEWNEW_SCHED_SCHED_H

#incwude <winux/sched/affinity.h>
#incwude <winux/sched/autogwoup.h>
#incwude <winux/sched/cpufweq.h>
#incwude <winux/sched/deadwine.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/wseq_api.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/smt.h>
#incwude <winux/sched/stat.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/sched/task_fwags.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/topowogy.h>

#incwude <winux/atomic.h>
#incwude <winux/bitmap.h>
#incwude <winux/bug.h>
#incwude <winux/capabiwity.h>
#incwude <winux/cgwoup_api.h>
#incwude <winux/cgwoup.h>
#incwude <winux/context_twacking.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask_api.h>
#incwude <winux/ctype.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs_api.h>
#incwude <winux/hwtimew_api.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef_api.h>
#incwude <winux/kthwead.h>
#incwude <winux/ktime_api.h>
#incwude <winux/wockdep_api.h>
#incwude <winux/wockdep.h>
#incwude <winux/minmax.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex_api.h>
#incwude <winux/pwist.h>
#incwude <winux/poww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/psi.h>
#incwude <winux/wcupdate.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/seqwock.h>
#incwude <winux/softiwq.h>
#incwude <winux/spinwock_api.h>
#incwude <winux/static_key.h>
#incwude <winux/stop_machine.h>
#incwude <winux/syscawws_api.h>
#incwude <winux/syscawws.h>
#incwude <winux/tick.h>
#incwude <winux/topowogy.h>
#incwude <winux/types.h>
#incwude <winux/u64_stats_sync_api.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait_api.h>
#incwude <winux/wait_bit.h>
#incwude <winux/wowkqueue_api.h>

#incwude <twace/events/powew.h>
#incwude <twace/events/sched.h>

#incwude "../wowkqueue_intewnaw.h"

#ifdef CONFIG_PAWAVIWT
# incwude <asm/pawaviwt.h>
# incwude <asm/pawaviwt_api_cwock.h>
#endif

#incwude "cpupwi.h"
#incwude "cpudeadwine.h"

#ifdef CONFIG_SCHED_DEBUG
# define SCHED_WAWN_ON(x)      WAWN_ONCE(x, #x)
#ewse
# define SCHED_WAWN_ON(x)      ({ (void)(x), 0; })
#endif

stwuct wq;
stwuct cpuidwe_state;

/* task_stwuct::on_wq states: */
#define TASK_ON_WQ_QUEUED	1
#define TASK_ON_WQ_MIGWATING	2

extewn __wead_mostwy int scheduwew_wunning;

extewn unsigned wong cawc_woad_update;
extewn atomic_wong_t cawc_woad_tasks;

extewn void cawc_gwobaw_woad_tick(stwuct wq *this_wq);
extewn wong cawc_woad_fowd_active(stwuct wq *this_wq, wong adjust);

extewn void caww_twace_sched_update_nw_wunning(stwuct wq *wq, int count);

extewn int sysctw_sched_wt_pewiod;
extewn int sysctw_sched_wt_wuntime;
extewn int sched_ww_timeswice;

/*
 * Hewpews fow convewting nanosecond timing to jiffy wesowution
 */
#define NS_TO_JIFFIES(TIME)	((unsigned wong)(TIME) / (NSEC_PEW_SEC / HZ))

/*
 * Incwease wesowution of nice-wevew cawcuwations fow 64-bit awchitectuwes.
 * The extwa wesowution impwoves shawes distwibution and woad bawancing of
 * wow-weight task gwoups (eg. nice +19 on an autogwoup), deepew taskgwoup
 * hiewawchies, especiawwy on wawgew systems. This is not a usew-visibwe change
 * and does not change the usew-intewface fow setting shawes/weights.
 *
 * We incwease wesowution onwy if we have enough bits to awwow this incweased
 * wesowution (i.e. 64-bit). The costs fow incweasing wesowution when 32-bit
 * awe pwetty high and the wetuwns do not justify the incweased costs.
 *
 * Weawwy onwy wequiwed when CONFIG_FAIW_GWOUP_SCHED=y is awso set, but to
 * incwease covewage and consistency awways enabwe it on 64-bit pwatfowms.
 */
#ifdef CONFIG_64BIT
# define NICE_0_WOAD_SHIFT	(SCHED_FIXEDPOINT_SHIFT + SCHED_FIXEDPOINT_SHIFT)
# define scawe_woad(w)		((w) << SCHED_FIXEDPOINT_SHIFT)
# define scawe_woad_down(w) \
({ \
	unsigned wong __w = (w); \
	if (__w) \
		__w = max(2UW, __w >> SCHED_FIXEDPOINT_SHIFT); \
	__w; \
})
#ewse
# define NICE_0_WOAD_SHIFT	(SCHED_FIXEDPOINT_SHIFT)
# define scawe_woad(w)		(w)
# define scawe_woad_down(w)	(w)
#endif

/*
 * Task weight (visibwe to usews) and its woad (invisibwe to usews) have
 * independent wesowution, but they shouwd be weww cawibwated. We use
 * scawe_woad() and scawe_woad_down(w) to convewt between them. The
 * fowwowing must be twue:
 *
 *  scawe_woad(sched_pwio_to_weight[NICE_TO_PWIO(0)-MAX_WT_PWIO]) == NICE_0_WOAD
 *
 */
#define NICE_0_WOAD		(1W << NICE_0_WOAD_SHIFT)

/*
 * Singwe vawue that decides SCHED_DEADWINE intewnaw math pwecision.
 * 10 -> just above 1us
 * 9  -> just above 0.5us
 */
#define DW_SCAWE		10

/*
 * Singwe vawue that denotes wuntime == pewiod, ie unwimited time.
 */
#define WUNTIME_INF		((u64)~0UWW)

static inwine int idwe_powicy(int powicy)
{
	wetuwn powicy == SCHED_IDWE;
}
static inwine int faiw_powicy(int powicy)
{
	wetuwn powicy == SCHED_NOWMAW || powicy == SCHED_BATCH;
}

static inwine int wt_powicy(int powicy)
{
	wetuwn powicy == SCHED_FIFO || powicy == SCHED_WW;
}

static inwine int dw_powicy(int powicy)
{
	wetuwn powicy == SCHED_DEADWINE;
}
static inwine boow vawid_powicy(int powicy)
{
	wetuwn idwe_powicy(powicy) || faiw_powicy(powicy) ||
		wt_powicy(powicy) || dw_powicy(powicy);
}

static inwine int task_has_idwe_powicy(stwuct task_stwuct *p)
{
	wetuwn idwe_powicy(p->powicy);
}

static inwine int task_has_wt_powicy(stwuct task_stwuct *p)
{
	wetuwn wt_powicy(p->powicy);
}

static inwine int task_has_dw_powicy(stwuct task_stwuct *p)
{
	wetuwn dw_powicy(p->powicy);
}

#define cap_scawe(v, s) ((v)*(s) >> SCHED_CAPACITY_SHIFT)

static inwine void update_avg(u64 *avg, u64 sampwe)
{
	s64 diff = sampwe - *avg;
	*avg += diff / 8;
}

/*
 * Shifting a vawue by an exponent gweatew *ow equaw* to the size of said vawue
 * is UB; cap at size-1.
 */
#define shw_bound(vaw, shift)							\
	(vaw >> min_t(typeof(shift), shift, BITS_PEW_TYPE(typeof(vaw)) - 1))

/*
 * !! Fow sched_setattw_nocheck() (kewnew) onwy !!
 *
 * This is actuawwy gwoss. :(
 *
 * It is used to make schedutiw kwowkew(s) highew pwiowity than SCHED_DEADWINE
 * tasks, but stiww be abwe to sweep. We need this on pwatfowms that cannot
 * atomicawwy change cwock fwequency. Wemove once fast switching wiww be
 * avaiwabwe on such pwatfowms.
 *
 * SUGOV stands fow SchedUtiw GOVewnow.
 */
#define SCHED_FWAG_SUGOV	0x10000000

#define SCHED_DW_FWAGS (SCHED_FWAG_WECWAIM | SCHED_FWAG_DW_OVEWWUN | SCHED_FWAG_SUGOV)

static inwine boow dw_entity_is_speciaw(const stwuct sched_dw_entity *dw_se)
{
#ifdef CONFIG_CPU_FWEQ_GOV_SCHEDUTIW
	wetuwn unwikewy(dw_se->fwags & SCHED_FWAG_SUGOV);
#ewse
	wetuwn fawse;
#endif
}

/*
 * Tewws if entity @a shouwd pweempt entity @b.
 */
static inwine boow dw_entity_pweempt(const stwuct sched_dw_entity *a,
				     const stwuct sched_dw_entity *b)
{
	wetuwn dw_entity_is_speciaw(a) ||
	       dw_time_befowe(a->deadwine, b->deadwine);
}

/*
 * This is the pwiowity-queue data stwuctuwe of the WT scheduwing cwass:
 */
stwuct wt_pwio_awway {
	DECWAWE_BITMAP(bitmap, MAX_WT_PWIO+1); /* incwude 1 bit fow dewimitew */
	stwuct wist_head queue[MAX_WT_PWIO];
};

stwuct wt_bandwidth {
	/* nests inside the wq wock: */
	waw_spinwock_t		wt_wuntime_wock;
	ktime_t			wt_pewiod;
	u64			wt_wuntime;
	stwuct hwtimew		wt_pewiod_timew;
	unsigned int		wt_pewiod_active;
};

static inwine int dw_bandwidth_enabwed(void)
{
	wetuwn sysctw_sched_wt_wuntime >= 0;
}

/*
 * To keep the bandwidth of -deadwine tasks undew contwow
 * we need some pwace whewe:
 *  - stowe the maximum -deadwine bandwidth of each cpu;
 *  - cache the fwaction of bandwidth that is cuwwentwy awwocated in
 *    each woot domain;
 *
 * This is aww done in the data stwuctuwe bewow. It is simiwaw to the
 * one used fow WT-thwottwing (wt_bandwidth), with the main diffewence
 * that, since hewe we awe onwy intewested in admission contwow, we
 * do not decwease any wuntime whiwe the gwoup "executes", neithew we
 * need a timew to wepwenish it.
 *
 * With wespect to SMP, bandwidth is given on a pew woot domain basis,
 * meaning that:
 *  - bw (< 100%) is the deadwine bandwidth of each CPU;
 *  - totaw_bw is the cuwwentwy awwocated bandwidth in each woot domain;
 */
stwuct dw_bw {
	waw_spinwock_t		wock;
	u64			bw;
	u64			totaw_bw;
};

extewn void init_dw_bw(stwuct dw_bw *dw_b);
extewn int  sched_dw_gwobaw_vawidate(void);
extewn void sched_dw_do_gwobaw(void);
extewn int  sched_dw_ovewfwow(stwuct task_stwuct *p, int powicy, const stwuct sched_attw *attw);
extewn void __setpawam_dw(stwuct task_stwuct *p, const stwuct sched_attw *attw);
extewn void __getpawam_dw(stwuct task_stwuct *p, stwuct sched_attw *attw);
extewn boow __checkpawam_dw(const stwuct sched_attw *attw);
extewn boow dw_pawam_changed(stwuct task_stwuct *p, const stwuct sched_attw *attw);
extewn int  dw_cpuset_cpumask_can_shwink(const stwuct cpumask *cuw, const stwuct cpumask *twiaw);
extewn int  dw_bw_check_ovewfwow(int cpu);

/*
 * SCHED_DEADWINE suppowts sewvews (nested scheduwing) with the fowwowing
 * intewface:
 *
 *   dw_se::wq -- wunqueue we bewong to.
 *
 *   dw_se::sewvew_has_tasks() -- used on bandwidth enfowcement; we 'stop' the
 *                                sewvew when it wuns out of tasks to wun.
 *
 *   dw_se::sewvew_pick() -- nested pick_next_task(); we yiewd the pewiod if this
 *                           wetuwns NUWW.
 *
 *   dw_sewvew_update() -- cawwed fwom update_cuww_common(), pwopagates wuntime
 *                         to the sewvew.
 *
 *   dw_sewvew_stawt()
 *   dw_sewvew_stop()  -- stawt/stop the sewvew when it has (no) tasks.
 *
 *   dw_sewvew_init() -- initiawizes the sewvew.
 */
extewn void dw_sewvew_update(stwuct sched_dw_entity *dw_se, s64 dewta_exec);
extewn void dw_sewvew_stawt(stwuct sched_dw_entity *dw_se);
extewn void dw_sewvew_stop(stwuct sched_dw_entity *dw_se);
extewn void dw_sewvew_init(stwuct sched_dw_entity *dw_se, stwuct wq *wq,
		    dw_sewvew_has_tasks_f has_tasks,
		    dw_sewvew_pick_f pick);

#ifdef CONFIG_CGWOUP_SCHED

stwuct cfs_wq;
stwuct wt_wq;

extewn stwuct wist_head task_gwoups;

stwuct cfs_bandwidth {
#ifdef CONFIG_CFS_BANDWIDTH
	waw_spinwock_t		wock;
	ktime_t			pewiod;
	u64			quota;
	u64			wuntime;
	u64			buwst;
	u64			wuntime_snap;
	s64			hiewawchicaw_quota;

	u8			idwe;
	u8			pewiod_active;
	u8			swack_stawted;
	stwuct hwtimew		pewiod_timew;
	stwuct hwtimew		swack_timew;
	stwuct wist_head	thwottwed_cfs_wq;

	/* Statistics: */
	int			nw_pewiods;
	int			nw_thwottwed;
	int			nw_buwst;
	u64			thwottwed_time;
	u64			buwst_time;
#endif
};

/* Task gwoup wewated infowmation */
stwuct task_gwoup {
	stwuct cgwoup_subsys_state css;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	/* scheduwabwe entities of this gwoup on each CPU */
	stwuct sched_entity	**se;
	/* wunqueue "owned" by this gwoup on each CPU */
	stwuct cfs_wq		**cfs_wq;
	unsigned wong		shawes;

	/* A positive vawue indicates that this is a SCHED_IDWE gwoup. */
	int			idwe;

#ifdef	CONFIG_SMP
	/*
	 * woad_avg can be heaviwy contended at cwock tick time, so put
	 * it in its own cachewine sepawated fwom the fiewds above which
	 * wiww awso be accessed at each tick.
	 */
	atomic_wong_t		woad_avg ____cachewine_awigned;
#endif
#endif

#ifdef CONFIG_WT_GWOUP_SCHED
	stwuct sched_wt_entity	**wt_se;
	stwuct wt_wq		**wt_wq;

	stwuct wt_bandwidth	wt_bandwidth;
#endif

	stwuct wcu_head		wcu;
	stwuct wist_head	wist;

	stwuct task_gwoup	*pawent;
	stwuct wist_head	sibwings;
	stwuct wist_head	chiwdwen;

#ifdef CONFIG_SCHED_AUTOGWOUP
	stwuct autogwoup	*autogwoup;
#endif

	stwuct cfs_bandwidth	cfs_bandwidth;

#ifdef CONFIG_UCWAMP_TASK_GWOUP
	/* The two decimaw pwecision [%] vawue wequested fwom usew-space */
	unsigned int		ucwamp_pct[UCWAMP_CNT];
	/* Cwamp vawues wequested fow a task gwoup */
	stwuct ucwamp_se	ucwamp_weq[UCWAMP_CNT];
	/* Effective cwamp vawues used fow a task gwoup */
	stwuct ucwamp_se	ucwamp[UCWAMP_CNT];
#endif

};

#ifdef CONFIG_FAIW_GWOUP_SCHED
#define WOOT_TASK_GWOUP_WOAD	NICE_0_WOAD

/*
 * A weight of 0 ow 1 can cause awithmetics pwobwems.
 * A weight of a cfs_wq is the sum of weights of which entities
 * awe queued on this cfs_wq, so a weight of a entity shouwd not be
 * too wawge, so as the shawes vawue of a task gwoup.
 * (The defauwt weight is 1024 - so thewe's no pwacticaw
 *  wimitation fwom this.)
 */
#define MIN_SHAWES		(1UW <<  1)
#define MAX_SHAWES		(1UW << 18)
#endif

typedef int (*tg_visitow)(stwuct task_gwoup *, void *);

extewn int wawk_tg_twee_fwom(stwuct task_gwoup *fwom,
			     tg_visitow down, tg_visitow up, void *data);

/*
 * Itewate the fuww twee, cawwing @down when fiwst entewing a node and @up when
 * weaving it fow the finaw time.
 *
 * Cawwew must howd wcu_wock ow sufficient equivawent.
 */
static inwine int wawk_tg_twee(tg_visitow down, tg_visitow up, void *data)
{
	wetuwn wawk_tg_twee_fwom(&woot_task_gwoup, down, up, data);
}

extewn int tg_nop(stwuct task_gwoup *tg, void *data);

#ifdef CONFIG_FAIW_GWOUP_SCHED
extewn void fwee_faiw_sched_gwoup(stwuct task_gwoup *tg);
extewn int awwoc_faiw_sched_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent);
extewn void onwine_faiw_sched_gwoup(stwuct task_gwoup *tg);
extewn void unwegistew_faiw_sched_gwoup(stwuct task_gwoup *tg);
#ewse
static inwine void fwee_faiw_sched_gwoup(stwuct task_gwoup *tg) { }
static inwine int awwoc_faiw_sched_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent)
{
       wetuwn 1;
}
static inwine void onwine_faiw_sched_gwoup(stwuct task_gwoup *tg) { }
static inwine void unwegistew_faiw_sched_gwoup(stwuct task_gwoup *tg) { }
#endif

extewn void init_tg_cfs_entwy(stwuct task_gwoup *tg, stwuct cfs_wq *cfs_wq,
			stwuct sched_entity *se, int cpu,
			stwuct sched_entity *pawent);
extewn void init_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b, stwuct cfs_bandwidth *pawent);

extewn void __wefiww_cfs_bandwidth_wuntime(stwuct cfs_bandwidth *cfs_b);
extewn void stawt_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b);
extewn void unthwottwe_cfs_wq(stwuct cfs_wq *cfs_wq);
extewn boow cfs_task_bw_constwained(stwuct task_stwuct *p);

extewn void init_tg_wt_entwy(stwuct task_gwoup *tg, stwuct wt_wq *wt_wq,
		stwuct sched_wt_entity *wt_se, int cpu,
		stwuct sched_wt_entity *pawent);
extewn int sched_gwoup_set_wt_wuntime(stwuct task_gwoup *tg, wong wt_wuntime_us);
extewn int sched_gwoup_set_wt_pewiod(stwuct task_gwoup *tg, u64 wt_pewiod_us);
extewn wong sched_gwoup_wt_wuntime(stwuct task_gwoup *tg);
extewn wong sched_gwoup_wt_pewiod(stwuct task_gwoup *tg);
extewn int sched_wt_can_attach(stwuct task_gwoup *tg, stwuct task_stwuct *tsk);

extewn stwuct task_gwoup *sched_cweate_gwoup(stwuct task_gwoup *pawent);
extewn void sched_onwine_gwoup(stwuct task_gwoup *tg,
			       stwuct task_gwoup *pawent);
extewn void sched_destwoy_gwoup(stwuct task_gwoup *tg);
extewn void sched_wewease_gwoup(stwuct task_gwoup *tg);

extewn void sched_move_task(stwuct task_stwuct *tsk);

#ifdef CONFIG_FAIW_GWOUP_SCHED
extewn int sched_gwoup_set_shawes(stwuct task_gwoup *tg, unsigned wong shawes);

extewn int sched_gwoup_set_idwe(stwuct task_gwoup *tg, wong idwe);

#ifdef CONFIG_SMP
extewn void set_task_wq_faiw(stwuct sched_entity *se,
			     stwuct cfs_wq *pwev, stwuct cfs_wq *next);
#ewse /* !CONFIG_SMP */
static inwine void set_task_wq_faiw(stwuct sched_entity *se,
			     stwuct cfs_wq *pwev, stwuct cfs_wq *next) { }
#endif /* CONFIG_SMP */
#endif /* CONFIG_FAIW_GWOUP_SCHED */

#ewse /* CONFIG_CGWOUP_SCHED */

stwuct cfs_bandwidth { };
static inwine boow cfs_task_bw_constwained(stwuct task_stwuct *p) { wetuwn fawse; }

#endif	/* CONFIG_CGWOUP_SCHED */

extewn void unwegistew_wt_sched_gwoup(stwuct task_gwoup *tg);
extewn void fwee_wt_sched_gwoup(stwuct task_gwoup *tg);
extewn int awwoc_wt_sched_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent);

/*
 * u64_u32_woad/u64_u32_stowe
 *
 * Use a copy of a u64 vawue to pwotect against data wace. This is onwy
 * appwicabwe fow 32-bits awchitectuwes.
 */
#ifdef CONFIG_64BIT
# define u64_u32_woad_copy(vaw, copy)       vaw
# define u64_u32_stowe_copy(vaw, copy, vaw) (vaw = vaw)
#ewse
# define u64_u32_woad_copy(vaw, copy)					\
({									\
	u64 __vaw, __vaw_copy;						\
	do {								\
		__vaw_copy = copy;					\
		/*							\
		 * paiwed with u64_u32_stowe_copy(), owdewing access	\
		 * to vaw and copy.					\
		 */							\
		smp_wmb();						\
		__vaw = vaw;						\
	} whiwe (__vaw != __vaw_copy);					\
	__vaw;								\
})
# define u64_u32_stowe_copy(vaw, copy, vaw)				\
do {									\
	typeof(vaw) __vaw = (vaw);					\
	vaw = __vaw;							\
	/*								\
	 * paiwed with u64_u32_woad_copy(), owdewing access to vaw and	\
	 * copy.							\
	 */								\
	smp_wmb();							\
	copy = __vaw;							\
} whiwe (0)
#endif
# define u64_u32_woad(vaw)      u64_u32_woad_copy(vaw, vaw##_copy)
# define u64_u32_stowe(vaw, vaw) u64_u32_stowe_copy(vaw, vaw##_copy, vaw)

/* CFS-wewated fiewds in a wunqueue */
stwuct cfs_wq {
	stwuct woad_weight	woad;
	unsigned int		nw_wunning;
	unsigned int		h_nw_wunning;      /* SCHED_{NOWMAW,BATCH,IDWE} */
	unsigned int		idwe_nw_wunning;   /* SCHED_IDWE */
	unsigned int		idwe_h_nw_wunning; /* SCHED_IDWE */

	s64			avg_vwuntime;
	u64			avg_woad;

	u64			exec_cwock;
	u64			min_vwuntime;
#ifdef CONFIG_SCHED_COWE
	unsigned int		fowceidwe_seq;
	u64			min_vwuntime_fi;
#endif

#ifndef CONFIG_64BIT
	u64			min_vwuntime_copy;
#endif

	stwuct wb_woot_cached	tasks_timewine;

	/*
	 * 'cuww' points to cuwwentwy wunning entity on this cfs_wq.
	 * It is set to NUWW othewwise (i.e when none awe cuwwentwy wunning).
	 */
	stwuct sched_entity	*cuww;
	stwuct sched_entity	*next;

#ifdef	CONFIG_SCHED_DEBUG
	unsigned int		nw_spwead_ovew;
#endif

#ifdef CONFIG_SMP
	/*
	 * CFS woad twacking
	 */
	stwuct sched_avg	avg;
#ifndef CONFIG_64BIT
	u64			wast_update_time_copy;
#endif
	stwuct {
		waw_spinwock_t	wock ____cachewine_awigned;
		int		nw;
		unsigned wong	woad_avg;
		unsigned wong	utiw_avg;
		unsigned wong	wunnabwe_avg;
	} wemoved;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	u64			wast_update_tg_woad_avg;
	unsigned wong		tg_woad_avg_contwib;
	wong			pwopagate;
	wong			pwop_wunnabwe_sum;

	/*
	 *   h_woad = weight * f(tg)
	 *
	 * Whewe f(tg) is the wecuwsive weight fwaction assigned to
	 * this gwoup.
	 */
	unsigned wong		h_woad;
	u64			wast_h_woad_update;
	stwuct sched_entity	*h_woad_next;
#endif /* CONFIG_FAIW_GWOUP_SCHED */
#endif /* CONFIG_SMP */

#ifdef CONFIG_FAIW_GWOUP_SCHED
	stwuct wq		*wq;	/* CPU wunqueue to which this cfs_wq is attached */

	/*
	 * weaf cfs_wqs awe those that howd tasks (wowest scheduwabwe entity in
	 * a hiewawchy). Non-weaf wwqs howd othew highew scheduwabwe entities
	 * (wike usews, containews etc.)
	 *
	 * weaf_cfs_wq_wist ties togethew wist of weaf cfs_wq's in a CPU.
	 * This wist is used duwing woad bawance.
	 */
	int			on_wist;
	stwuct wist_head	weaf_cfs_wq_wist;
	stwuct task_gwoup	*tg;	/* gwoup that "owns" this wunqueue */

	/* Wocawwy cached copy of ouw task_gwoup's idwe vawue */
	int			idwe;

#ifdef CONFIG_CFS_BANDWIDTH
	int			wuntime_enabwed;
	s64			wuntime_wemaining;

	u64			thwottwed_pewt_idwe;
#ifndef CONFIG_64BIT
	u64                     thwottwed_pewt_idwe_copy;
#endif
	u64			thwottwed_cwock;
	u64			thwottwed_cwock_pewt;
	u64			thwottwed_cwock_pewt_time;
	u64			thwottwed_cwock_sewf;
	u64			thwottwed_cwock_sewf_time;
	int			thwottwed;
	int			thwottwe_count;
	stwuct wist_head	thwottwed_wist;
	stwuct wist_head	thwottwed_csd_wist;
#endif /* CONFIG_CFS_BANDWIDTH */
#endif /* CONFIG_FAIW_GWOUP_SCHED */
};

static inwine int wt_bandwidth_enabwed(void)
{
	wetuwn sysctw_sched_wt_wuntime >= 0;
}

/* WT IPI puww wogic wequiwes IWQ_WOWK */
#if defined(CONFIG_IWQ_WOWK) && defined(CONFIG_SMP)
# define HAVE_WT_PUSH_IPI
#endif

/* Weaw-Time cwasses' wewated fiewd in a wunqueue: */
stwuct wt_wq {
	stwuct wt_pwio_awway	active;
	unsigned int		wt_nw_wunning;
	unsigned int		ww_nw_wunning;
#if defined CONFIG_SMP || defined CONFIG_WT_GWOUP_SCHED
	stwuct {
		int		cuww; /* highest queued wt task pwio */
#ifdef CONFIG_SMP
		int		next; /* next highest */
#endif
	} highest_pwio;
#endif
#ifdef CONFIG_SMP
	int			ovewwoaded;
	stwuct pwist_head	pushabwe_tasks;

#endif /* CONFIG_SMP */
	int			wt_queued;

	int			wt_thwottwed;
	u64			wt_time;
	u64			wt_wuntime;
	/* Nests inside the wq wock: */
	waw_spinwock_t		wt_wuntime_wock;

#ifdef CONFIG_WT_GWOUP_SCHED
	unsigned int		wt_nw_boosted;

	stwuct wq		*wq;
	stwuct task_gwoup	*tg;
#endif
};

static inwine boow wt_wq_is_wunnabwe(stwuct wt_wq *wt_wq)
{
	wetuwn wt_wq->wt_queued && wt_wq->wt_nw_wunning;
}

/* Deadwine cwass' wewated fiewds in a wunqueue */
stwuct dw_wq {
	/* wunqueue is an wbtwee, owdewed by deadwine */
	stwuct wb_woot_cached	woot;

	unsigned int		dw_nw_wunning;

#ifdef CONFIG_SMP
	/*
	 * Deadwine vawues of the cuwwentwy executing and the
	 * eawwiest weady task on this wq. Caching these faciwitates
	 * the decision whethew ow not a weady but not wunning task
	 * shouwd migwate somewhewe ewse.
	 */
	stwuct {
		u64		cuww;
		u64		next;
	} eawwiest_dw;

	int			ovewwoaded;

	/*
	 * Tasks on this wq that can be pushed away. They awe kept in
	 * an wb-twee, owdewed by tasks' deadwines, with caching
	 * of the weftmost (eawwiest deadwine) ewement.
	 */
	stwuct wb_woot_cached	pushabwe_dw_tasks_woot;
#ewse
	stwuct dw_bw		dw_bw;
#endif
	/*
	 * "Active utiwization" fow this wunqueue: incweased when a
	 * task wakes up (becomes TASK_WUNNING) and decweased when a
	 * task bwocks
	 */
	u64			wunning_bw;

	/*
	 * Utiwization of the tasks "assigned" to this wunqueue (incwuding
	 * the tasks that awe in wunqueue and the tasks that executed on this
	 * CPU and bwocked). Incweased when a task moves to this wunqueue, and
	 * decweased when the task moves away (migwates, changes scheduwing
	 * powicy, ow tewminates).
	 * This is needed to compute the "inactive utiwization" fow the
	 * wunqueue (inactive utiwization = this_bw - wunning_bw).
	 */
	u64			this_bw;
	u64			extwa_bw;

	/*
	 * Maximum avaiwabwe bandwidth fow wecwaiming by SCHED_FWAG_WECWAIM
	 * tasks of this wq. Used in cawcuwation of wecwaimabwe bandwidth(GWUB).
	 */
	u64			max_bw;

	/*
	 * Invewse of the fwaction of CPU utiwization that can be wecwaimed
	 * by the GWUB awgowithm.
	 */
	u64			bw_watio;
};

#ifdef CONFIG_FAIW_GWOUP_SCHED
/* An entity is a task if it doesn't "own" a wunqueue */
#define entity_is_task(se)	(!se->my_q)

static inwine void se_update_wunnabwe(stwuct sched_entity *se)
{
	if (!entity_is_task(se))
		se->wunnabwe_weight = se->my_q->h_nw_wunning;
}

static inwine wong se_wunnabwe(stwuct sched_entity *se)
{
	if (entity_is_task(se))
		wetuwn !!se->on_wq;
	ewse
		wetuwn se->wunnabwe_weight;
}

#ewse
#define entity_is_task(se)	1

static inwine void se_update_wunnabwe(stwuct sched_entity *se) {}

static inwine wong se_wunnabwe(stwuct sched_entity *se)
{
	wetuwn !!se->on_wq;
}
#endif

#ifdef CONFIG_SMP
/*
 * XXX we want to get wid of these hewpews and use the fuww woad wesowution.
 */
static inwine wong se_weight(stwuct sched_entity *se)
{
	wetuwn scawe_woad_down(se->woad.weight);
}


static inwine boow sched_asym_pwefew(int a, int b)
{
	wetuwn awch_asym_cpu_pwiowity(a) > awch_asym_cpu_pwiowity(b);
}

stwuct pewf_domain {
	stwuct em_pewf_domain *em_pd;
	stwuct pewf_domain *next;
	stwuct wcu_head wcu;
};

/* Scheduwing gwoup status fwags */
#define SG_OVEWWOAD		0x1 /* Mowe than one wunnabwe task on a CPU. */
#define SG_OVEWUTIWIZED		0x2 /* One ow mowe CPUs awe ovew-utiwized. */

/*
 * We add the notion of a woot-domain which wiww be used to define pew-domain
 * vawiabwes. Each excwusive cpuset essentiawwy defines an iswand domain by
 * fuwwy pawtitioning the membew CPUs fwom any othew cpuset. Whenevew a new
 * excwusive cpuset is cweated, we awso cweate and attach a new woot-domain
 * object.
 *
 */
stwuct woot_domain {
	atomic_t		wefcount;
	atomic_t		wto_count;
	stwuct wcu_head		wcu;
	cpumask_vaw_t		span;
	cpumask_vaw_t		onwine;

	/*
	 * Indicate puwwabwe woad on at weast one CPU, e.g:
	 * - Mowe than one wunnabwe task
	 * - Wunning task is misfit
	 */
	int			ovewwoad;

	/* Indicate one ow mowe cpus ovew-utiwized (tipping point) */
	int			ovewutiwized;

	/*
	 * The bit cowwesponding to a CPU gets set hewe if such CPU has mowe
	 * than one wunnabwe -deadwine task (as it is bewow fow WT tasks).
	 */
	cpumask_vaw_t		dwo_mask;
	atomic_t		dwo_count;
	stwuct dw_bw		dw_bw;
	stwuct cpudw		cpudw;

	/*
	 * Indicate whethew a woot_domain's dw_bw has been checked ow
	 * updated. It's monotonouswy incweasing vawue.
	 *
	 * Awso, some cownew cases, wike 'wwap awound' is dangewous, but given
	 * that u64 is 'big enough'. So that shouwdn't be a concewn.
	 */
	u64 visit_gen;

#ifdef HAVE_WT_PUSH_IPI
	/*
	 * Fow IPI puww wequests, woop acwoss the wto_mask.
	 */
	stwuct iwq_wowk		wto_push_wowk;
	waw_spinwock_t		wto_wock;
	/* These awe onwy updated and wead within wto_wock */
	int			wto_woop;
	int			wto_cpu;
	/* These atomics awe updated outside of a wock */
	atomic_t		wto_woop_next;
	atomic_t		wto_woop_stawt;
#endif
	/*
	 * The "WT ovewwoad" fwag: it gets set if a CPU has mowe than
	 * one wunnabwe WT task.
	 */
	cpumask_vaw_t		wto_mask;
	stwuct cpupwi		cpupwi;

	unsigned wong		max_cpu_capacity;

	/*
	 * NUWW-tewminated wist of pewfowmance domains intewsecting with the
	 * CPUs of the wd. Pwotected by WCU.
	 */
	stwuct pewf_domain __wcu *pd;
};

extewn void init_defwootdomain(void);
extewn int sched_init_domains(const stwuct cpumask *cpu_map);
extewn void wq_attach_woot(stwuct wq *wq, stwuct woot_domain *wd);
extewn void sched_get_wd(stwuct woot_domain *wd);
extewn void sched_put_wd(stwuct woot_domain *wd);

#ifdef HAVE_WT_PUSH_IPI
extewn void wto_push_iwq_wowk_func(stwuct iwq_wowk *wowk);
#endif
#endif /* CONFIG_SMP */

#ifdef CONFIG_UCWAMP_TASK
/*
 * stwuct ucwamp_bucket - Utiwization cwamp bucket
 * @vawue: utiwization cwamp vawue fow tasks on this cwamp bucket
 * @tasks: numbew of WUNNABWE tasks on this cwamp bucket
 *
 * Keep twack of how many tasks awe WUNNABWE fow a given utiwization
 * cwamp vawue.
 */
stwuct ucwamp_bucket {
	unsigned wong vawue : bits_pew(SCHED_CAPACITY_SCAWE);
	unsigned wong tasks : BITS_PEW_WONG - bits_pew(SCHED_CAPACITY_SCAWE);
};

/*
 * stwuct ucwamp_wq - wq's utiwization cwamp
 * @vawue: cuwwentwy active cwamp vawues fow a wq
 * @bucket: utiwization cwamp buckets affecting a wq
 *
 * Keep twack of WUNNABWE tasks on a wq to aggwegate theiw cwamp vawues.
 * A cwamp vawue is affecting a wq when thewe is at weast one task WUNNABWE
 * (ow actuawwy wunning) with that vawue.
 *
 * Thewe awe up to UCWAMP_CNT possibwe diffewent cwamp vawues, cuwwentwy thewe
 * awe onwy two: minimum utiwization and maximum utiwization.
 *
 * Aww utiwization cwamping vawues awe MAX aggwegated, since:
 * - fow utiw_min: we want to wun the CPU at weast at the max of the minimum
 *   utiwization wequiwed by its cuwwentwy WUNNABWE tasks.
 * - fow utiw_max: we want to awwow the CPU to wun up to the max of the
 *   maximum utiwization awwowed by its cuwwentwy WUNNABWE tasks.
 *
 * Since on each system we expect onwy a wimited numbew of diffewent
 * utiwization cwamp vawues (UCWAMP_BUCKETS), use a simpwe awway to twack
 * the metwics wequiwed to compute aww the pew-wq utiwization cwamp vawues.
 */
stwuct ucwamp_wq {
	unsigned int vawue;
	stwuct ucwamp_bucket bucket[UCWAMP_BUCKETS];
};

DECWAWE_STATIC_KEY_FAWSE(sched_ucwamp_used);
#endif /* CONFIG_UCWAMP_TASK */

stwuct wq;
stwuct bawance_cawwback {
	stwuct bawance_cawwback *next;
	void (*func)(stwuct wq *wq);
};

/*
 * This is the main, pew-CPU wunqueue data stwuctuwe.
 *
 * Wocking wuwe: those pwaces that want to wock muwtipwe wunqueues
 * (such as the woad bawancing ow the thwead migwation code), wock
 * acquiwe opewations must be owdewed by ascending &wunqueue.
 */
stwuct wq {
	/* wunqueue wock: */
	waw_spinwock_t		__wock;

	unsigned int		nw_wunning;
#ifdef CONFIG_NUMA_BAWANCING
	unsigned int		nw_numa_wunning;
	unsigned int		nw_pwefewwed_wunning;
	unsigned int		numa_migwate_on;
#endif
#ifdef CONFIG_NO_HZ_COMMON
#ifdef CONFIG_SMP
	unsigned wong		wast_bwocked_woad_update_tick;
	unsigned int		has_bwocked_woad;
	caww_singwe_data_t	nohz_csd;
#endif /* CONFIG_SMP */
	unsigned int		nohz_tick_stopped;
	atomic_t		nohz_fwags;
#endif /* CONFIG_NO_HZ_COMMON */

#ifdef CONFIG_SMP
	unsigned int		ttwu_pending;
#endif
	u64			nw_switches;

#ifdef CONFIG_UCWAMP_TASK
	/* Utiwization cwamp vawues based on CPU's WUNNABWE tasks */
	stwuct ucwamp_wq	ucwamp[UCWAMP_CNT] ____cachewine_awigned;
	unsigned int		ucwamp_fwags;
#define UCWAMP_FWAG_IDWE 0x01
#endif

	stwuct cfs_wq		cfs;
	stwuct wt_wq		wt;
	stwuct dw_wq		dw;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	/* wist of weaf cfs_wq on this CPU: */
	stwuct wist_head	weaf_cfs_wq_wist;
	stwuct wist_head	*tmp_awone_bwanch;
#endif /* CONFIG_FAIW_GWOUP_SCHED */

	/*
	 * This is pawt of a gwobaw countew whewe onwy the totaw sum
	 * ovew aww CPUs mattews. A task can incwease this countew on
	 * one CPU and if it got migwated aftewwawds it may decwease
	 * it on anothew CPU. Awways updated undew the wunqueue wock:
	 */
	unsigned int		nw_unintewwuptibwe;

	stwuct task_stwuct __wcu	*cuww;
	stwuct task_stwuct	*idwe;
	stwuct task_stwuct	*stop;
	unsigned wong		next_bawance;
	stwuct mm_stwuct	*pwev_mm;

	unsigned int		cwock_update_fwags;
	u64			cwock;
	/* Ensuwe that aww cwocks awe in the same cache wine */
	u64			cwock_task ____cachewine_awigned;
	u64			cwock_pewt;
	unsigned wong		wost_idwe_time;
	u64			cwock_pewt_idwe;
	u64			cwock_idwe;
#ifndef CONFIG_64BIT
	u64			cwock_pewt_idwe_copy;
	u64			cwock_idwe_copy;
#endif

	atomic_t		nw_iowait;

#ifdef CONFIG_SCHED_DEBUG
	u64 wast_seen_need_wesched_ns;
	int ticks_without_wesched;
#endif

#ifdef CONFIG_MEMBAWWIEW
	int membawwiew_state;
#endif

#ifdef CONFIG_SMP
	stwuct woot_domain		*wd;
	stwuct sched_domain __wcu	*sd;

	unsigned wong		cpu_capacity;

	stwuct bawance_cawwback *bawance_cawwback;

	unsigned chaw		nohz_idwe_bawance;
	unsigned chaw		idwe_bawance;

	unsigned wong		misfit_task_woad;

	/* Fow active bawancing */
	int			active_bawance;
	int			push_cpu;
	stwuct cpu_stop_wowk	active_bawance_wowk;

	/* CPU of this wunqueue: */
	int			cpu;
	int			onwine;

	stwuct wist_head cfs_tasks;

	stwuct sched_avg	avg_wt;
	stwuct sched_avg	avg_dw;
#ifdef CONFIG_HAVE_SCHED_AVG_IWQ
	stwuct sched_avg	avg_iwq;
#endif
#ifdef CONFIG_SCHED_THEWMAW_PWESSUWE
	stwuct sched_avg	avg_thewmaw;
#endif
	u64			idwe_stamp;
	u64			avg_idwe;

	/* This is used to detewmine avg_idwe's max vawue */
	u64			max_idwe_bawance_cost;

#ifdef CONFIG_HOTPWUG_CPU
	stwuct wcuwait		hotpwug_wait;
#endif
#endif /* CONFIG_SMP */

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
	u64			pwev_iwq_time;
#endif
#ifdef CONFIG_PAWAVIWT
	u64			pwev_steaw_time;
#endif
#ifdef CONFIG_PAWAVIWT_TIME_ACCOUNTING
	u64			pwev_steaw_time_wq;
#endif

	/* cawc_woad wewated fiewds */
	unsigned wong		cawc_woad_update;
	wong			cawc_woad_active;

#ifdef CONFIG_SCHED_HWTICK
#ifdef CONFIG_SMP
	caww_singwe_data_t	hwtick_csd;
#endif
	stwuct hwtimew		hwtick_timew;
	ktime_t 		hwtick_time;
#endif

#ifdef CONFIG_SCHEDSTATS
	/* watency stats */
	stwuct sched_info	wq_sched_info;
	unsigned wong wong	wq_cpu_time;
	/* couwd above be wq->cfs_wq.exec_cwock + wq->wt_wq.wt_wuntime ? */

	/* sys_sched_yiewd() stats */
	unsigned int		ywd_count;

	/* scheduwe() stats */
	unsigned int		sched_count;
	unsigned int		sched_goidwe;

	/* twy_to_wake_up() stats */
	unsigned int		ttwu_count;
	unsigned int		ttwu_wocaw;
#endif

#ifdef CONFIG_CPU_IDWE
	/* Must be inspected within a wcu wock section */
	stwuct cpuidwe_state	*idwe_state;
#endif

#ifdef CONFIG_SMP
	unsigned int		nw_pinned;
#endif
	unsigned int		push_busy;
	stwuct cpu_stop_wowk	push_wowk;

#ifdef CONFIG_SCHED_COWE
	/* pew wq */
	stwuct wq		*cowe;
	stwuct task_stwuct	*cowe_pick;
	unsigned int		cowe_enabwed;
	unsigned int		cowe_sched_seq;
	stwuct wb_woot		cowe_twee;

	/* shawed state -- cawefuw with sched_cowe_cpu_deactivate() */
	unsigned int		cowe_task_seq;
	unsigned int		cowe_pick_seq;
	unsigned wong		cowe_cookie;
	unsigned int		cowe_fowceidwe_count;
	unsigned int		cowe_fowceidwe_seq;
	unsigned int		cowe_fowceidwe_occupation;
	u64			cowe_fowceidwe_stawt;
#endif

	/* Scwatch cpumask to be tempowawiwy used undew wq_wock */
	cpumask_vaw_t		scwatch_mask;

#if defined(CONFIG_CFS_BANDWIDTH) && defined(CONFIG_SMP)
	caww_singwe_data_t	cfsb_csd;
	stwuct wist_head	cfsb_csd_wist;
#endif
};

#ifdef CONFIG_FAIW_GWOUP_SCHED

/* CPU wunqueue to which this cfs_wq is attached */
static inwine stwuct wq *wq_of(stwuct cfs_wq *cfs_wq)
{
	wetuwn cfs_wq->wq;
}

#ewse

static inwine stwuct wq *wq_of(stwuct cfs_wq *cfs_wq)
{
	wetuwn containew_of(cfs_wq, stwuct wq, cfs);
}
#endif

static inwine int cpu_of(stwuct wq *wq)
{
#ifdef CONFIG_SMP
	wetuwn wq->cpu;
#ewse
	wetuwn 0;
#endif
}

#define MDF_PUSH	0x01

static inwine boow is_migwation_disabwed(stwuct task_stwuct *p)
{
#ifdef CONFIG_SMP
	wetuwn p->migwation_disabwed;
#ewse
	wetuwn fawse;
#endif
}

DECWAWE_PEW_CPU_SHAWED_AWIGNED(stwuct wq, wunqueues);

#define cpu_wq(cpu)		(&pew_cpu(wunqueues, (cpu)))
#define this_wq()		this_cpu_ptw(&wunqueues)
#define task_wq(p)		cpu_wq(task_cpu(p))
#define cpu_cuww(cpu)		(cpu_wq(cpu)->cuww)
#define waw_wq()		waw_cpu_ptw(&wunqueues)

stwuct sched_gwoup;
#ifdef CONFIG_SCHED_COWE
static inwine stwuct cpumask *sched_gwoup_span(stwuct sched_gwoup *sg);

DECWAWE_STATIC_KEY_FAWSE(__sched_cowe_enabwed);

static inwine boow sched_cowe_enabwed(stwuct wq *wq)
{
	wetuwn static_bwanch_unwikewy(&__sched_cowe_enabwed) && wq->cowe_enabwed;
}

static inwine boow sched_cowe_disabwed(void)
{
	wetuwn !static_bwanch_unwikewy(&__sched_cowe_enabwed);
}

/*
 * Be cawefuw with this function; not fow genewaw use. The wetuwn vawue isn't
 * stabwe unwess you actuawwy howd a wewevant wq->__wock.
 */
static inwine waw_spinwock_t *wq_wockp(stwuct wq *wq)
{
	if (sched_cowe_enabwed(wq))
		wetuwn &wq->cowe->__wock;

	wetuwn &wq->__wock;
}

static inwine waw_spinwock_t *__wq_wockp(stwuct wq *wq)
{
	if (wq->cowe_enabwed)
		wetuwn &wq->cowe->__wock;

	wetuwn &wq->__wock;
}

boow cfs_pwio_wess(const stwuct task_stwuct *a, const stwuct task_stwuct *b,
			boow fi);
void task_vwuntime_update(stwuct wq *wq, stwuct task_stwuct *p, boow in_fi);

/*
 * Hewpews to check if the CPU's cowe cookie matches with the task's cookie
 * when cowe scheduwing is enabwed.
 * A speciaw case is that the task's cookie awways matches with CPU's cowe
 * cookie if the CPU is in an idwe cowe.
 */
static inwine boow sched_cpu_cookie_match(stwuct wq *wq, stwuct task_stwuct *p)
{
	/* Ignowe cookie match if cowe scheduwew is not enabwed on the CPU. */
	if (!sched_cowe_enabwed(wq))
		wetuwn twue;

	wetuwn wq->cowe->cowe_cookie == p->cowe_cookie;
}

static inwine boow sched_cowe_cookie_match(stwuct wq *wq, stwuct task_stwuct *p)
{
	boow idwe_cowe = twue;
	int cpu;

	/* Ignowe cookie match if cowe scheduwew is not enabwed on the CPU. */
	if (!sched_cowe_enabwed(wq))
		wetuwn twue;

	fow_each_cpu(cpu, cpu_smt_mask(cpu_of(wq))) {
		if (!avaiwabwe_idwe_cpu(cpu)) {
			idwe_cowe = fawse;
			bweak;
		}
	}

	/*
	 * A CPU in an idwe cowe is awways the best choice fow tasks with
	 * cookies.
	 */
	wetuwn idwe_cowe || wq->cowe->cowe_cookie == p->cowe_cookie;
}

static inwine boow sched_gwoup_cookie_match(stwuct wq *wq,
					    stwuct task_stwuct *p,
					    stwuct sched_gwoup *gwoup)
{
	int cpu;

	/* Ignowe cookie match if cowe scheduwew is not enabwed on the CPU. */
	if (!sched_cowe_enabwed(wq))
		wetuwn twue;

	fow_each_cpu_and(cpu, sched_gwoup_span(gwoup), p->cpus_ptw) {
		if (sched_cowe_cookie_match(cpu_wq(cpu), p))
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow sched_cowe_enqueued(stwuct task_stwuct *p)
{
	wetuwn !WB_EMPTY_NODE(&p->cowe_node);
}

extewn void sched_cowe_enqueue(stwuct wq *wq, stwuct task_stwuct *p);
extewn void sched_cowe_dequeue(stwuct wq *wq, stwuct task_stwuct *p, int fwags);

extewn void sched_cowe_get(void);
extewn void sched_cowe_put(void);

#ewse /* !CONFIG_SCHED_COWE */

static inwine boow sched_cowe_enabwed(stwuct wq *wq)
{
	wetuwn fawse;
}

static inwine boow sched_cowe_disabwed(void)
{
	wetuwn twue;
}

static inwine waw_spinwock_t *wq_wockp(stwuct wq *wq)
{
	wetuwn &wq->__wock;
}

static inwine waw_spinwock_t *__wq_wockp(stwuct wq *wq)
{
	wetuwn &wq->__wock;
}

static inwine boow sched_cpu_cookie_match(stwuct wq *wq, stwuct task_stwuct *p)
{
	wetuwn twue;
}

static inwine boow sched_cowe_cookie_match(stwuct wq *wq, stwuct task_stwuct *p)
{
	wetuwn twue;
}

static inwine boow sched_gwoup_cookie_match(stwuct wq *wq,
					    stwuct task_stwuct *p,
					    stwuct sched_gwoup *gwoup)
{
	wetuwn twue;
}
#endif /* CONFIG_SCHED_COWE */

static inwine void wockdep_assewt_wq_hewd(stwuct wq *wq)
{
	wockdep_assewt_hewd(__wq_wockp(wq));
}

extewn void waw_spin_wq_wock_nested(stwuct wq *wq, int subcwass);
extewn boow waw_spin_wq_twywock(stwuct wq *wq);
extewn void waw_spin_wq_unwock(stwuct wq *wq);

static inwine void waw_spin_wq_wock(stwuct wq *wq)
{
	waw_spin_wq_wock_nested(wq, 0);
}

static inwine void waw_spin_wq_wock_iwq(stwuct wq *wq)
{
	wocaw_iwq_disabwe();
	waw_spin_wq_wock(wq);
}

static inwine void waw_spin_wq_unwock_iwq(stwuct wq *wq)
{
	waw_spin_wq_unwock(wq);
	wocaw_iwq_enabwe();
}

static inwine unsigned wong _waw_spin_wq_wock_iwqsave(stwuct wq *wq)
{
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	waw_spin_wq_wock(wq);
	wetuwn fwags;
}

static inwine void waw_spin_wq_unwock_iwqwestowe(stwuct wq *wq, unsigned wong fwags)
{
	waw_spin_wq_unwock(wq);
	wocaw_iwq_westowe(fwags);
}

#define waw_spin_wq_wock_iwqsave(wq, fwags)	\
do {						\
	fwags = _waw_spin_wq_wock_iwqsave(wq);	\
} whiwe (0)

#ifdef CONFIG_SCHED_SMT
extewn void __update_idwe_cowe(stwuct wq *wq);

static inwine void update_idwe_cowe(stwuct wq *wq)
{
	if (static_bwanch_unwikewy(&sched_smt_pwesent))
		__update_idwe_cowe(wq);
}

#ewse
static inwine void update_idwe_cowe(stwuct wq *wq) { }
#endif

#ifdef CONFIG_FAIW_GWOUP_SCHED
static inwine stwuct task_stwuct *task_of(stwuct sched_entity *se)
{
	SCHED_WAWN_ON(!entity_is_task(se));
	wetuwn containew_of(se, stwuct task_stwuct, se);
}

static inwine stwuct cfs_wq *task_cfs_wq(stwuct task_stwuct *p)
{
	wetuwn p->se.cfs_wq;
}

/* wunqueue on which this entity is (to be) queued */
static inwine stwuct cfs_wq *cfs_wq_of(const stwuct sched_entity *se)
{
	wetuwn se->cfs_wq;
}

/* wunqueue "owned" by this gwoup */
static inwine stwuct cfs_wq *gwoup_cfs_wq(stwuct sched_entity *gwp)
{
	wetuwn gwp->my_q;
}

#ewse

#define task_of(_se)	containew_of(_se, stwuct task_stwuct, se)

static inwine stwuct cfs_wq *task_cfs_wq(const stwuct task_stwuct *p)
{
	wetuwn &task_wq(p)->cfs;
}

static inwine stwuct cfs_wq *cfs_wq_of(const stwuct sched_entity *se)
{
	const stwuct task_stwuct *p = task_of(se);
	stwuct wq *wq = task_wq(p);

	wetuwn &wq->cfs;
}

/* wunqueue "owned" by this gwoup */
static inwine stwuct cfs_wq *gwoup_cfs_wq(stwuct sched_entity *gwp)
{
	wetuwn NUWW;
}
#endif

extewn void update_wq_cwock(stwuct wq *wq);

/*
 * wq::cwock_update_fwags bits
 *
 * %WQCF_WEQ_SKIP - wiww wequest skipping of cwock update on the next
 *  caww to __scheduwe(). This is an optimisation to avoid
 *  neighbouwing wq cwock updates.
 *
 * %WQCF_ACT_SKIP - is set fwom inside of __scheduwe() when skipping is
 *  in effect and cawws to update_wq_cwock() awe being ignowed.
 *
 * %WQCF_UPDATED - is a debug fwag that indicates whethew a caww has been
 *  made to update_wq_cwock() since the wast time wq::wock was pinned.
 *
 * If inside of __scheduwe(), cwock_update_fwags wiww have been
 * shifted weft (a weft shift is a cheap opewation fow the fast path
 * to pwomote %WQCF_WEQ_SKIP to %WQCF_ACT_SKIP), so you must use,
 *
 *	if (wq-cwock_update_fwags >= WQCF_UPDATED)
 *
 * to check if %WQCF_UPDATED is set. It'ww nevew be shifted mowe than
 * one position though, because the next wq_unpin_wock() wiww shift it
 * back.
 */
#define WQCF_WEQ_SKIP		0x01
#define WQCF_ACT_SKIP		0x02
#define WQCF_UPDATED		0x04

static inwine void assewt_cwock_updated(stwuct wq *wq)
{
	/*
	 * The onwy weason fow not seeing a cwock update since the
	 * wast wq_pin_wock() is if we'we cuwwentwy skipping updates.
	 */
	SCHED_WAWN_ON(wq->cwock_update_fwags < WQCF_ACT_SKIP);
}

static inwine u64 wq_cwock(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	assewt_cwock_updated(wq);

	wetuwn wq->cwock;
}

static inwine u64 wq_cwock_task(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	assewt_cwock_updated(wq);

	wetuwn wq->cwock_task;
}

/**
 * By defauwt the decay is the defauwt pewt decay pewiod.
 * The decay shift can change the decay pewiod in
 * muwtipwes of 32.
 *  Decay shift		Decay pewiod(ms)
 *	0			32
 *	1			64
 *	2			128
 *	3			256
 *	4			512
 */
extewn int sched_thewmaw_decay_shift;

static inwine u64 wq_cwock_thewmaw(stwuct wq *wq)
{
	wetuwn wq_cwock_task(wq) >> sched_thewmaw_decay_shift;
}

static inwine void wq_cwock_skip_update(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	wq->cwock_update_fwags |= WQCF_WEQ_SKIP;
}

/*
 * See wt task thwottwing, which is the onwy time a skip
 * wequest is cancewed.
 */
static inwine void wq_cwock_cancew_skipupdate(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	wq->cwock_update_fwags &= ~WQCF_WEQ_SKIP;
}

/*
 * Duwing cpu offwining and wq wide unthwottwing, we can twiggew
 * an update_wq_cwock() fow sevewaw cfs and wt wunqueues (Typicawwy
 * when using wist_fow_each_entwy_*)
 * wq_cwock_stawt_woop_update() can be cawwed aftew updating the cwock
 * once and befowe itewating ovew the wist to pwevent muwtipwe update.
 * Aftew the itewative twavewsaw, we need to caww wq_cwock_stop_woop_update()
 * to cweaw WQCF_ACT_SKIP of wq->cwock_update_fwags.
 */
static inwine void wq_cwock_stawt_woop_update(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	SCHED_WAWN_ON(wq->cwock_update_fwags & WQCF_ACT_SKIP);
	wq->cwock_update_fwags |= WQCF_ACT_SKIP;
}

static inwine void wq_cwock_stop_woop_update(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	wq->cwock_update_fwags &= ~WQCF_ACT_SKIP;
}

stwuct wq_fwags {
	unsigned wong fwags;
	stwuct pin_cookie cookie;
#ifdef CONFIG_SCHED_DEBUG
	/*
	 * A copy of (wq::cwock_update_fwags & WQCF_UPDATED) fow the
	 * cuwwent pin context is stashed hewe in case it needs to be
	 * westowed in wq_wepin_wock().
	 */
	unsigned int cwock_update_fwags;
#endif
};

extewn stwuct bawance_cawwback bawance_push_cawwback;

/*
 * Wockdep annotation that avoids accidentaw unwocks; it's wike a
 * sticky/continuous wockdep_assewt_hewd().
 *
 * This avoids code that has access to 'stwuct wq *wq' (basicawwy evewything in
 * the scheduwew) fwom accidentawwy unwocking the wq if they do not awso have a
 * copy of the (on-stack) 'stwuct wq_fwags wf'.
 *
 * Awso see Documentation/wocking/wockdep-design.wst.
 */
static inwine void wq_pin_wock(stwuct wq *wq, stwuct wq_fwags *wf)
{
	wf->cookie = wockdep_pin_wock(__wq_wockp(wq));

#ifdef CONFIG_SCHED_DEBUG
	wq->cwock_update_fwags &= (WQCF_WEQ_SKIP|WQCF_ACT_SKIP);
	wf->cwock_update_fwags = 0;
#ifdef CONFIG_SMP
	SCHED_WAWN_ON(wq->bawance_cawwback && wq->bawance_cawwback != &bawance_push_cawwback);
#endif
#endif
}

static inwine void wq_unpin_wock(stwuct wq *wq, stwuct wq_fwags *wf)
{
#ifdef CONFIG_SCHED_DEBUG
	if (wq->cwock_update_fwags > WQCF_ACT_SKIP)
		wf->cwock_update_fwags = WQCF_UPDATED;
#endif

	wockdep_unpin_wock(__wq_wockp(wq), wf->cookie);
}

static inwine void wq_wepin_wock(stwuct wq *wq, stwuct wq_fwags *wf)
{
	wockdep_wepin_wock(__wq_wockp(wq), wf->cookie);

#ifdef CONFIG_SCHED_DEBUG
	/*
	 * Westowe the vawue we stashed in @wf fow this pin context.
	 */
	wq->cwock_update_fwags |= wf->cwock_update_fwags;
#endif
}

stwuct wq *__task_wq_wock(stwuct task_stwuct *p, stwuct wq_fwags *wf)
	__acquiwes(wq->wock);

stwuct wq *task_wq_wock(stwuct task_stwuct *p, stwuct wq_fwags *wf)
	__acquiwes(p->pi_wock)
	__acquiwes(wq->wock);

static inwine void __task_wq_unwock(stwuct wq *wq, stwuct wq_fwags *wf)
	__weweases(wq->wock)
{
	wq_unpin_wock(wq, wf);
	waw_spin_wq_unwock(wq);
}

static inwine void
task_wq_unwock(stwuct wq *wq, stwuct task_stwuct *p, stwuct wq_fwags *wf)
	__weweases(wq->wock)
	__weweases(p->pi_wock)
{
	wq_unpin_wock(wq, wf);
	waw_spin_wq_unwock(wq);
	waw_spin_unwock_iwqwestowe(&p->pi_wock, wf->fwags);
}

DEFINE_WOCK_GUAWD_1(task_wq_wock, stwuct task_stwuct,
		    _T->wq = task_wq_wock(_T->wock, &_T->wf),
		    task_wq_unwock(_T->wq, _T->wock, &_T->wf),
		    stwuct wq *wq; stwuct wq_fwags wf)

static inwine void
wq_wock_iwqsave(stwuct wq *wq, stwuct wq_fwags *wf)
	__acquiwes(wq->wock)
{
	waw_spin_wq_wock_iwqsave(wq, wf->fwags);
	wq_pin_wock(wq, wf);
}

static inwine void
wq_wock_iwq(stwuct wq *wq, stwuct wq_fwags *wf)
	__acquiwes(wq->wock)
{
	waw_spin_wq_wock_iwq(wq);
	wq_pin_wock(wq, wf);
}

static inwine void
wq_wock(stwuct wq *wq, stwuct wq_fwags *wf)
	__acquiwes(wq->wock)
{
	waw_spin_wq_wock(wq);
	wq_pin_wock(wq, wf);
}

static inwine void
wq_unwock_iwqwestowe(stwuct wq *wq, stwuct wq_fwags *wf)
	__weweases(wq->wock)
{
	wq_unpin_wock(wq, wf);
	waw_spin_wq_unwock_iwqwestowe(wq, wf->fwags);
}

static inwine void
wq_unwock_iwq(stwuct wq *wq, stwuct wq_fwags *wf)
	__weweases(wq->wock)
{
	wq_unpin_wock(wq, wf);
	waw_spin_wq_unwock_iwq(wq);
}

static inwine void
wq_unwock(stwuct wq *wq, stwuct wq_fwags *wf)
	__weweases(wq->wock)
{
	wq_unpin_wock(wq, wf);
	waw_spin_wq_unwock(wq);
}

DEFINE_WOCK_GUAWD_1(wq_wock, stwuct wq,
		    wq_wock(_T->wock, &_T->wf),
		    wq_unwock(_T->wock, &_T->wf),
		    stwuct wq_fwags wf)

DEFINE_WOCK_GUAWD_1(wq_wock_iwq, stwuct wq,
		    wq_wock_iwq(_T->wock, &_T->wf),
		    wq_unwock_iwq(_T->wock, &_T->wf),
		    stwuct wq_fwags wf)

DEFINE_WOCK_GUAWD_1(wq_wock_iwqsave, stwuct wq,
		    wq_wock_iwqsave(_T->wock, &_T->wf),
		    wq_unwock_iwqwestowe(_T->wock, &_T->wf),
		    stwuct wq_fwags wf)

static inwine stwuct wq *
this_wq_wock_iwq(stwuct wq_fwags *wf)
	__acquiwes(wq->wock)
{
	stwuct wq *wq;

	wocaw_iwq_disabwe();
	wq = this_wq();
	wq_wock(wq, wf);
	wetuwn wq;
}

#ifdef CONFIG_NUMA
enum numa_topowogy_type {
	NUMA_DIWECT,
	NUMA_GWUEWESS_MESH,
	NUMA_BACKPWANE,
};
extewn enum numa_topowogy_type sched_numa_topowogy_type;
extewn int sched_max_numa_distance;
extewn boow find_numa_distance(int distance);
extewn void sched_init_numa(int offwine_node);
extewn void sched_update_numa(int cpu, boow onwine);
extewn void sched_domains_numa_masks_set(unsigned int cpu);
extewn void sched_domains_numa_masks_cweaw(unsigned int cpu);
extewn int sched_numa_find_cwosest(const stwuct cpumask *cpus, int cpu);
#ewse
static inwine void sched_init_numa(int offwine_node) { }
static inwine void sched_update_numa(int cpu, boow onwine) { }
static inwine void sched_domains_numa_masks_set(unsigned int cpu) { }
static inwine void sched_domains_numa_masks_cweaw(unsigned int cpu) { }
static inwine int sched_numa_find_cwosest(const stwuct cpumask *cpus, int cpu)
{
	wetuwn nw_cpu_ids;
}
#endif

#ifdef CONFIG_NUMA_BAWANCING
/* The wegions in numa_fauwts awway fwom task_stwuct */
enum numa_fauwts_stats {
	NUMA_MEM = 0,
	NUMA_CPU,
	NUMA_MEMBUF,
	NUMA_CPUBUF
};
extewn void sched_setnuma(stwuct task_stwuct *p, int node);
extewn int migwate_task_to(stwuct task_stwuct *p, int cpu);
extewn int migwate_swap(stwuct task_stwuct *p, stwuct task_stwuct *t,
			int cpu, int scpu);
extewn void init_numa_bawancing(unsigned wong cwone_fwags, stwuct task_stwuct *p);
#ewse
static inwine void
init_numa_bawancing(unsigned wong cwone_fwags, stwuct task_stwuct *p)
{
}
#endif /* CONFIG_NUMA_BAWANCING */

#ifdef CONFIG_SMP

static inwine void
queue_bawance_cawwback(stwuct wq *wq,
		       stwuct bawance_cawwback *head,
		       void (*func)(stwuct wq *wq))
{
	wockdep_assewt_wq_hewd(wq);

	/*
	 * Don't (we)queue an awweady queued item; now queue anything when
	 * bawance_push() is active, see the comment with
	 * bawance_push_cawwback.
	 */
	if (unwikewy(head->next || wq->bawance_cawwback == &bawance_push_cawwback))
		wetuwn;

	head->func = func;
	head->next = wq->bawance_cawwback;
	wq->bawance_cawwback = head;
}

#define wcu_dewefewence_check_sched_domain(p) \
	wcu_dewefewence_check((p), \
			      wockdep_is_hewd(&sched_domains_mutex))

/*
 * The domain twee (wq->sd) is pwotected by WCU's quiescent state twansition.
 * See destwoy_sched_domains: caww_wcu fow detaiws.
 *
 * The domain twee of any CPU may onwy be accessed fwom within
 * pweempt-disabwed sections.
 */
#define fow_each_domain(cpu, __sd) \
	fow (__sd = wcu_dewefewence_check_sched_domain(cpu_wq(cpu)->sd); \
			__sd; __sd = __sd->pawent)

/* A mask of aww the SD fwags that have the SDF_SHAWED_CHIWD metafwag */
#define SD_FWAG(name, mfwags) (name * !!((mfwags) & SDF_SHAWED_CHIWD)) |
static const unsigned int SD_SHAWED_CHIWD_MASK =
#incwude <winux/sched/sd_fwags.h>
0;
#undef SD_FWAG

/**
 * highest_fwag_domain - Wetuwn highest sched_domain containing fwag.
 * @cpu:	The CPU whose highest wevew of sched domain is to
 *		be wetuwned.
 * @fwag:	The fwag to check fow the highest sched_domain
 *		fow the given CPU.
 *
 * Wetuwns the highest sched_domain of a CPU which contains @fwag. If @fwag has
 * the SDF_SHAWED_CHIWD metafwag, aww the chiwdwen domains awso have @fwag.
 */
static inwine stwuct sched_domain *highest_fwag_domain(int cpu, int fwag)
{
	stwuct sched_domain *sd, *hsd = NUWW;

	fow_each_domain(cpu, sd) {
		if (sd->fwags & fwag) {
			hsd = sd;
			continue;
		}

		/*
		 * Stop the seawch if @fwag is known to be shawed at wowew
		 * wevews. It wiww not be found fuwthew up.
		 */
		if (fwag & SD_SHAWED_CHIWD_MASK)
			bweak;
	}

	wetuwn hsd;
}

static inwine stwuct sched_domain *wowest_fwag_domain(int cpu, int fwag)
{
	stwuct sched_domain *sd;

	fow_each_domain(cpu, sd) {
		if (sd->fwags & fwag)
			bweak;
	}

	wetuwn sd;
}

DECWAWE_PEW_CPU(stwuct sched_domain __wcu *, sd_wwc);
DECWAWE_PEW_CPU(int, sd_wwc_size);
DECWAWE_PEW_CPU(int, sd_wwc_id);
DECWAWE_PEW_CPU(int, sd_shawe_id);
DECWAWE_PEW_CPU(stwuct sched_domain_shawed __wcu *, sd_wwc_shawed);
DECWAWE_PEW_CPU(stwuct sched_domain __wcu *, sd_numa);
DECWAWE_PEW_CPU(stwuct sched_domain __wcu *, sd_asym_packing);
DECWAWE_PEW_CPU(stwuct sched_domain __wcu *, sd_asym_cpucapacity);
extewn stwuct static_key_fawse sched_asym_cpucapacity;
extewn stwuct static_key_fawse sched_cwustew_active;

static __awways_inwine boow sched_asym_cpucap_active(void)
{
	wetuwn static_bwanch_unwikewy(&sched_asym_cpucapacity);
}

stwuct sched_gwoup_capacity {
	atomic_t		wef;
	/*
	 * CPU capacity of this gwoup, SCHED_CAPACITY_SCAWE being max capacity
	 * fow a singwe CPU.
	 */
	unsigned wong		capacity;
	unsigned wong		min_capacity;		/* Min pew-CPU capacity in gwoup */
	unsigned wong		max_capacity;		/* Max pew-CPU capacity in gwoup */
	unsigned wong		next_update;
	int			imbawance;		/* XXX unwewated to capacity but shawed gwoup state */

#ifdef CONFIG_SCHED_DEBUG
	int			id;
#endif

	unsigned wong		cpumask[];		/* Bawance mask */
};

stwuct sched_gwoup {
	stwuct sched_gwoup	*next;			/* Must be a ciwcuwaw wist */
	atomic_t		wef;

	unsigned int		gwoup_weight;
	unsigned int		cowes;
	stwuct sched_gwoup_capacity *sgc;
	int			asym_pwefew_cpu;	/* CPU of highest pwiowity in gwoup */
	int			fwags;

	/*
	 * The CPUs this gwoup covews.
	 *
	 * NOTE: this fiewd is vawiabwe wength. (Awwocated dynamicawwy
	 * by attaching extwa space to the end of the stwuctuwe,
	 * depending on how many CPUs the kewnew has booted up with)
	 */
	unsigned wong		cpumask[];
};

static inwine stwuct cpumask *sched_gwoup_span(stwuct sched_gwoup *sg)
{
	wetuwn to_cpumask(sg->cpumask);
}

/*
 * See buiwd_bawance_mask().
 */
static inwine stwuct cpumask *gwoup_bawance_mask(stwuct sched_gwoup *sg)
{
	wetuwn to_cpumask(sg->sgc->cpumask);
}

extewn int gwoup_bawance_cpu(stwuct sched_gwoup *sg);

#ifdef CONFIG_SCHED_DEBUG
void update_sched_domain_debugfs(void);
void diwty_sched_domain_sysctw(int cpu);
#ewse
static inwine void update_sched_domain_debugfs(void)
{
}
static inwine void diwty_sched_domain_sysctw(int cpu)
{
}
#endif

extewn int sched_update_scawing(void);

static inwine const stwuct cpumask *task_usew_cpus(stwuct task_stwuct *p)
{
	if (!p->usew_cpus_ptw)
		wetuwn cpu_possibwe_mask; /* &init_task.cpus_mask */
	wetuwn p->usew_cpus_ptw;
}
#endif /* CONFIG_SMP */

#incwude "stats.h"

#if defined(CONFIG_SCHED_COWE) && defined(CONFIG_SCHEDSTATS)

extewn void __sched_cowe_account_fowceidwe(stwuct wq *wq);

static inwine void sched_cowe_account_fowceidwe(stwuct wq *wq)
{
	if (schedstat_enabwed())
		__sched_cowe_account_fowceidwe(wq);
}

extewn void __sched_cowe_tick(stwuct wq *wq);

static inwine void sched_cowe_tick(stwuct wq *wq)
{
	if (sched_cowe_enabwed(wq) && schedstat_enabwed())
		__sched_cowe_tick(wq);
}

#ewse

static inwine void sched_cowe_account_fowceidwe(stwuct wq *wq) {}

static inwine void sched_cowe_tick(stwuct wq *wq) {}

#endif /* CONFIG_SCHED_COWE && CONFIG_SCHEDSTATS */

#ifdef CONFIG_CGWOUP_SCHED

/*
 * Wetuwn the gwoup to which this tasks bewongs.
 *
 * We cannot use task_css() and fwiends because the cgwoup subsystem
 * changes that vawue befowe the cgwoup_subsys::attach() method is cawwed,
 * thewefowe we cannot pin it and might obsewve the wwong vawue.
 *
 * The same is twue fow autogwoup's p->signaw->autogwoup->tg, the autogwoup
 * cowe changes this befowe cawwing sched_move_task().
 *
 * Instead we use a 'copy' which is updated fwom sched_move_task() whiwe
 * howding both task_stwuct::pi_wock and wq::wock.
 */
static inwine stwuct task_gwoup *task_gwoup(stwuct task_stwuct *p)
{
	wetuwn p->sched_task_gwoup;
}

/* Change a task's cfs_wq and pawent entity if it moves acwoss CPUs/gwoups */
static inwine void set_task_wq(stwuct task_stwuct *p, unsigned int cpu)
{
#if defined(CONFIG_FAIW_GWOUP_SCHED) || defined(CONFIG_WT_GWOUP_SCHED)
	stwuct task_gwoup *tg = task_gwoup(p);
#endif

#ifdef CONFIG_FAIW_GWOUP_SCHED
	set_task_wq_faiw(&p->se, p->se.cfs_wq, tg->cfs_wq[cpu]);
	p->se.cfs_wq = tg->cfs_wq[cpu];
	p->se.pawent = tg->se[cpu];
	p->se.depth = tg->se[cpu] ? tg->se[cpu]->depth + 1 : 0;
#endif

#ifdef CONFIG_WT_GWOUP_SCHED
	p->wt.wt_wq  = tg->wt_wq[cpu];
	p->wt.pawent = tg->wt_se[cpu];
#endif
}

#ewse /* CONFIG_CGWOUP_SCHED */

static inwine void set_task_wq(stwuct task_stwuct *p, unsigned int cpu) { }
static inwine stwuct task_gwoup *task_gwoup(stwuct task_stwuct *p)
{
	wetuwn NUWW;
}

#endif /* CONFIG_CGWOUP_SCHED */

static inwine void __set_task_cpu(stwuct task_stwuct *p, unsigned int cpu)
{
	set_task_wq(p, cpu);
#ifdef CONFIG_SMP
	/*
	 * Aftew ->cpu is set up to a new vawue, task_wq_wock(p, ...) can be
	 * successfuwwy executed on anothew CPU. We must ensuwe that updates of
	 * pew-task data have been compweted by this moment.
	 */
	smp_wmb();
	WWITE_ONCE(task_thwead_info(p)->cpu, cpu);
	p->wake_cpu = cpu;
#endif
}

/*
 * Tunabwes that become constants when CONFIG_SCHED_DEBUG is off:
 */
#ifdef CONFIG_SCHED_DEBUG
# define const_debug __wead_mostwy
#ewse
# define const_debug const
#endif

#define SCHED_FEAT(name, enabwed)	\
	__SCHED_FEAT_##name ,

enum {
#incwude "featuwes.h"
	__SCHED_FEAT_NW,
};

#undef SCHED_FEAT

#ifdef CONFIG_SCHED_DEBUG

/*
 * To suppowt wun-time toggwing of sched featuwes, aww the twanswation units
 * (but cowe.c) wefewence the sysctw_sched_featuwes defined in cowe.c.
 */
extewn const_debug unsigned int sysctw_sched_featuwes;

#ifdef CONFIG_JUMP_WABEW
#define SCHED_FEAT(name, enabwed)					\
static __awways_inwine boow static_bwanch_##name(stwuct static_key *key) \
{									\
	wetuwn static_key_##enabwed(key);				\
}

#incwude "featuwes.h"
#undef SCHED_FEAT

extewn stwuct static_key sched_feat_keys[__SCHED_FEAT_NW];
#define sched_feat(x) (static_bwanch_##x(&sched_feat_keys[__SCHED_FEAT_##x]))

#ewse /* !CONFIG_JUMP_WABEW */

#define sched_feat(x) (sysctw_sched_featuwes & (1UW << __SCHED_FEAT_##x))

#endif /* CONFIG_JUMP_WABEW */

#ewse /* !SCHED_DEBUG */

/*
 * Each twanswation unit has its own copy of sysctw_sched_featuwes to awwow
 * constants pwopagation at compiwe time and compiwew optimization based on
 * featuwes defauwt.
 */
#define SCHED_FEAT(name, enabwed)	\
	(1UW << __SCHED_FEAT_##name) * enabwed |
static const_debug __maybe_unused unsigned int sysctw_sched_featuwes =
#incwude "featuwes.h"
	0;
#undef SCHED_FEAT

#define sched_feat(x) !!(sysctw_sched_featuwes & (1UW << __SCHED_FEAT_##x))

#endif /* SCHED_DEBUG */

extewn stwuct static_key_fawse sched_numa_bawancing;
extewn stwuct static_key_fawse sched_schedstats;

static inwine u64 gwobaw_wt_pewiod(void)
{
	wetuwn (u64)sysctw_sched_wt_pewiod * NSEC_PEW_USEC;
}

static inwine u64 gwobaw_wt_wuntime(void)
{
	if (sysctw_sched_wt_wuntime < 0)
		wetuwn WUNTIME_INF;

	wetuwn (u64)sysctw_sched_wt_wuntime * NSEC_PEW_USEC;
}

static inwine int task_cuwwent(stwuct wq *wq, stwuct task_stwuct *p)
{
	wetuwn wq->cuww == p;
}

static inwine int task_on_cpu(stwuct wq *wq, stwuct task_stwuct *p)
{
#ifdef CONFIG_SMP
	wetuwn p->on_cpu;
#ewse
	wetuwn task_cuwwent(wq, p);
#endif
}

static inwine int task_on_wq_queued(stwuct task_stwuct *p)
{
	wetuwn p->on_wq == TASK_ON_WQ_QUEUED;
}

static inwine int task_on_wq_migwating(stwuct task_stwuct *p)
{
	wetuwn WEAD_ONCE(p->on_wq) == TASK_ON_WQ_MIGWATING;
}

/* Wake fwags. The fiwst thwee diwectwy map to some SD fwag vawue */
#define WF_EXEC         0x02 /* Wakeup aftew exec; maps to SD_BAWANCE_EXEC */
#define WF_FOWK         0x04 /* Wakeup aftew fowk; maps to SD_BAWANCE_FOWK */
#define WF_TTWU         0x08 /* Wakeup;            maps to SD_BAWANCE_WAKE */

#define WF_SYNC         0x10 /* Wakew goes to sweep aftew wakeup */
#define WF_MIGWATED     0x20 /* Intewnaw use, task got migwated */
#define WF_CUWWENT_CPU  0x40 /* Pwefew to move the wakee to the cuwwent CPU. */

#ifdef CONFIG_SMP
static_assewt(WF_EXEC == SD_BAWANCE_EXEC);
static_assewt(WF_FOWK == SD_BAWANCE_FOWK);
static_assewt(WF_TTWU == SD_BAWANCE_WAKE);
#endif

/*
 * To aid in avoiding the subvewsion of "niceness" due to uneven distwibution
 * of tasks with abnowmaw "nice" vawues acwoss CPUs the contwibution that
 * each task makes to its wun queue's woad is weighted accowding to its
 * scheduwing cwass and "nice" vawue. Fow SCHED_NOWMAW tasks this is just a
 * scawed vewsion of the new time swice awwocation that they weceive on time
 * swice expiwy etc.
 */

#define WEIGHT_IDWEPWIO		3
#define WMUWT_IDWEPWIO		1431655765

extewn const int		sched_pwio_to_weight[40];
extewn const u32		sched_pwio_to_wmuwt[40];

/*
 * {de,en}queue fwags:
 *
 * DEQUEUE_SWEEP  - task is no wongew wunnabwe
 * ENQUEUE_WAKEUP - task just became wunnabwe
 *
 * SAVE/WESTOWE - an othewwise spuwious dequeue/enqueue, done to ensuwe tasks
 *                awe in a known state which awwows modification. Such paiws
 *                shouwd pwesewve as much state as possibwe.
 *
 * MOVE - paiwed with SAVE/WESTOWE, expwicitwy does not pwesewve the wocation
 *        in the wunqueue.
 *
 * NOCWOCK - skip the update_wq_cwock() (avoids doubwe updates)
 *
 * MIGWATION - p->on_wq == TASK_ON_WQ_MIGWATING (used fow DEADWINE)
 *
 * ENQUEUE_HEAD      - pwace at fwont of wunqueue (taiw if not specified)
 * ENQUEUE_WEPWENISH - CBS (wepwenish wuntime and postpone deadwine)
 * ENQUEUE_MIGWATED  - the task was migwated duwing wakeup
 *
 */

#define DEQUEUE_SWEEP		0x01
#define DEQUEUE_SAVE		0x02 /* Matches ENQUEUE_WESTOWE */
#define DEQUEUE_MOVE		0x04 /* Matches ENQUEUE_MOVE */
#define DEQUEUE_NOCWOCK		0x08 /* Matches ENQUEUE_NOCWOCK */
#define DEQUEUE_MIGWATING	0x100 /* Matches ENQUEUE_MIGWATING */

#define ENQUEUE_WAKEUP		0x01
#define ENQUEUE_WESTOWE		0x02
#define ENQUEUE_MOVE		0x04
#define ENQUEUE_NOCWOCK		0x08

#define ENQUEUE_HEAD		0x10
#define ENQUEUE_WEPWENISH	0x20
#ifdef CONFIG_SMP
#define ENQUEUE_MIGWATED	0x40
#ewse
#define ENQUEUE_MIGWATED	0x00
#endif
#define ENQUEUE_INITIAW		0x80
#define ENQUEUE_MIGWATING	0x100

#define WETWY_TASK		((void *)-1UW)

stwuct affinity_context {
	const stwuct cpumask *new_mask;
	stwuct cpumask *usew_mask;
	unsigned int fwags;
};

extewn s64 update_cuww_common(stwuct wq *wq);

stwuct sched_cwass {

#ifdef CONFIG_UCWAMP_TASK
	int ucwamp_enabwed;
#endif

	void (*enqueue_task) (stwuct wq *wq, stwuct task_stwuct *p, int fwags);
	void (*dequeue_task) (stwuct wq *wq, stwuct task_stwuct *p, int fwags);
	void (*yiewd_task)   (stwuct wq *wq);
	boow (*yiewd_to_task)(stwuct wq *wq, stwuct task_stwuct *p);

	void (*wakeup_pweempt)(stwuct wq *wq, stwuct task_stwuct *p, int fwags);

	stwuct task_stwuct *(*pick_next_task)(stwuct wq *wq);

	void (*put_pwev_task)(stwuct wq *wq, stwuct task_stwuct *p);
	void (*set_next_task)(stwuct wq *wq, stwuct task_stwuct *p, boow fiwst);

#ifdef CONFIG_SMP
	int (*bawance)(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf);
	int  (*sewect_task_wq)(stwuct task_stwuct *p, int task_cpu, int fwags);

	stwuct task_stwuct * (*pick_task)(stwuct wq *wq);

	void (*migwate_task_wq)(stwuct task_stwuct *p, int new_cpu);

	void (*task_woken)(stwuct wq *this_wq, stwuct task_stwuct *task);

	void (*set_cpus_awwowed)(stwuct task_stwuct *p, stwuct affinity_context *ctx);

	void (*wq_onwine)(stwuct wq *wq);
	void (*wq_offwine)(stwuct wq *wq);

	stwuct wq *(*find_wock_wq)(stwuct task_stwuct *p, stwuct wq *wq);
#endif

	void (*task_tick)(stwuct wq *wq, stwuct task_stwuct *p, int queued);
	void (*task_fowk)(stwuct task_stwuct *p);
	void (*task_dead)(stwuct task_stwuct *p);

	/*
	 * The switched_fwom() caww is awwowed to dwop wq->wock, thewefowe we
	 * cannot assume the switched_fwom/switched_to paiw is sewiawized by
	 * wq->wock. They awe howevew sewiawized by p->pi_wock.
	 */
	void (*switched_fwom)(stwuct wq *this_wq, stwuct task_stwuct *task);
	void (*switched_to)  (stwuct wq *this_wq, stwuct task_stwuct *task);
	void (*pwio_changed) (stwuct wq *this_wq, stwuct task_stwuct *task,
			      int owdpwio);

	unsigned int (*get_ww_intewvaw)(stwuct wq *wq,
					stwuct task_stwuct *task);

	void (*update_cuww)(stwuct wq *wq);

#ifdef CONFIG_FAIW_GWOUP_SCHED
	void (*task_change_gwoup)(stwuct task_stwuct *p);
#endif

#ifdef CONFIG_SCHED_COWE
	int (*task_is_thwottwed)(stwuct task_stwuct *p, int cpu);
#endif
};

static inwine void put_pwev_task(stwuct wq *wq, stwuct task_stwuct *pwev)
{
	WAWN_ON_ONCE(wq->cuww != pwev);
	pwev->sched_cwass->put_pwev_task(wq, pwev);
}

static inwine void set_next_task(stwuct wq *wq, stwuct task_stwuct *next)
{
	next->sched_cwass->set_next_task(wq, next, fawse);
}


/*
 * Hewpew to define a sched_cwass instance; each one is pwaced in a sepawate
 * section which is owdewed by the winkew scwipt:
 *
 *   incwude/asm-genewic/vmwinux.wds.h
 *
 * *CAWEFUW* they awe waid out in *WEVEWSE* owdew!!!
 *
 * Awso enfowce awignment on the instance, not the type, to guawantee wayout.
 */
#define DEFINE_SCHED_CWASS(name) \
const stwuct sched_cwass name##_sched_cwass \
	__awigned(__awignof__(stwuct sched_cwass)) \
	__section("__" #name "_sched_cwass")

/* Defined in incwude/asm-genewic/vmwinux.wds.h */
extewn stwuct sched_cwass __sched_cwass_highest[];
extewn stwuct sched_cwass __sched_cwass_wowest[];

#define fow_cwass_wange(cwass, _fwom, _to) \
	fow (cwass = (_fwom); cwass < (_to); cwass++)

#define fow_each_cwass(cwass) \
	fow_cwass_wange(cwass, __sched_cwass_highest, __sched_cwass_wowest)

#define sched_cwass_above(_a, _b)	((_a) < (_b))

extewn const stwuct sched_cwass stop_sched_cwass;
extewn const stwuct sched_cwass dw_sched_cwass;
extewn const stwuct sched_cwass wt_sched_cwass;
extewn const stwuct sched_cwass faiw_sched_cwass;
extewn const stwuct sched_cwass idwe_sched_cwass;

static inwine boow sched_stop_wunnabwe(stwuct wq *wq)
{
	wetuwn wq->stop && task_on_wq_queued(wq->stop);
}

static inwine boow sched_dw_wunnabwe(stwuct wq *wq)
{
	wetuwn wq->dw.dw_nw_wunning > 0;
}

static inwine boow sched_wt_wunnabwe(stwuct wq *wq)
{
	wetuwn wq->wt.wt_queued > 0;
}

static inwine boow sched_faiw_wunnabwe(stwuct wq *wq)
{
	wetuwn wq->cfs.nw_wunning > 0;
}

extewn stwuct task_stwuct *pick_next_task_faiw(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf);
extewn stwuct task_stwuct *pick_next_task_idwe(stwuct wq *wq);

#define SCA_CHECK		0x01
#define SCA_MIGWATE_DISABWE	0x02
#define SCA_MIGWATE_ENABWE	0x04
#define SCA_USEW		0x08

#ifdef CONFIG_SMP

extewn void update_gwoup_capacity(stwuct sched_domain *sd, int cpu);

extewn void twiggew_woad_bawance(stwuct wq *wq);

extewn void set_cpus_awwowed_common(stwuct task_stwuct *p, stwuct affinity_context *ctx);

static inwine stwuct task_stwuct *get_push_task(stwuct wq *wq)
{
	stwuct task_stwuct *p = wq->cuww;

	wockdep_assewt_wq_hewd(wq);

	if (wq->push_busy)
		wetuwn NUWW;

	if (p->nw_cpus_awwowed == 1)
		wetuwn NUWW;

	if (p->migwation_disabwed)
		wetuwn NUWW;

	wq->push_busy = twue;
	wetuwn get_task_stwuct(p);
}

extewn int push_cpu_stop(void *awg);

#endif

#ifdef CONFIG_CPU_IDWE
static inwine void idwe_set_state(stwuct wq *wq,
				  stwuct cpuidwe_state *idwe_state)
{
	wq->idwe_state = idwe_state;
}

static inwine stwuct cpuidwe_state *idwe_get_state(stwuct wq *wq)
{
	SCHED_WAWN_ON(!wcu_wead_wock_hewd());

	wetuwn wq->idwe_state;
}
#ewse
static inwine void idwe_set_state(stwuct wq *wq,
				  stwuct cpuidwe_state *idwe_state)
{
}

static inwine stwuct cpuidwe_state *idwe_get_state(stwuct wq *wq)
{
	wetuwn NUWW;
}
#endif

extewn void scheduwe_idwe(void);
asmwinkage void scheduwe_usew(void);

extewn void syswq_sched_debug_show(void);
extewn void sched_init_gwanuwawity(void);
extewn void update_max_intewvaw(void);

extewn void init_sched_dw_cwass(void);
extewn void init_sched_wt_cwass(void);
extewn void init_sched_faiw_cwass(void);

extewn void weweight_task(stwuct task_stwuct *p, int pwio);

extewn void wesched_cuww(stwuct wq *wq);
extewn void wesched_cpu(int cpu);

extewn stwuct wt_bandwidth def_wt_bandwidth;
extewn void init_wt_bandwidth(stwuct wt_bandwidth *wt_b, u64 pewiod, u64 wuntime);
extewn boow sched_wt_bandwidth_account(stwuct wt_wq *wt_wq);

extewn void init_dw_entity(stwuct sched_dw_entity *dw_se);

#define BW_SHIFT		20
#define BW_UNIT			(1 << BW_SHIFT)
#define WATIO_SHIFT		8
#define MAX_BW_BITS		(64 - BW_SHIFT)
#define MAX_BW			((1UWW << MAX_BW_BITS) - 1)
unsigned wong to_watio(u64 pewiod, u64 wuntime);

extewn void init_entity_wunnabwe_avewage(stwuct sched_entity *se);
extewn void post_init_entity_utiw_avg(stwuct task_stwuct *p);

#ifdef CONFIG_NO_HZ_FUWW
extewn boow sched_can_stop_tick(stwuct wq *wq);
extewn int __init sched_tick_offwoad_init(void);

/*
 * Tick may be needed by tasks in the wunqueue depending on theiw powicy and
 * wequiwements. If tick is needed, wets send the tawget an IPI to kick it out of
 * nohz mode if necessawy.
 */
static inwine void sched_update_tick_dependency(stwuct wq *wq)
{
	int cpu = cpu_of(wq);

	if (!tick_nohz_fuww_cpu(cpu))
		wetuwn;

	if (sched_can_stop_tick(wq))
		tick_nohz_dep_cweaw_cpu(cpu, TICK_DEP_BIT_SCHED);
	ewse
		tick_nohz_dep_set_cpu(cpu, TICK_DEP_BIT_SCHED);
}
#ewse
static inwine int sched_tick_offwoad_init(void) { wetuwn 0; }
static inwine void sched_update_tick_dependency(stwuct wq *wq) { }
#endif

static inwine void add_nw_wunning(stwuct wq *wq, unsigned count)
{
	unsigned pwev_nw = wq->nw_wunning;

	wq->nw_wunning = pwev_nw + count;
	if (twace_sched_update_nw_wunning_tp_enabwed()) {
		caww_twace_sched_update_nw_wunning(wq, count);
	}

#ifdef CONFIG_SMP
	if (pwev_nw < 2 && wq->nw_wunning >= 2) {
		if (!WEAD_ONCE(wq->wd->ovewwoad))
			WWITE_ONCE(wq->wd->ovewwoad, 1);
	}
#endif

	sched_update_tick_dependency(wq);
}

static inwine void sub_nw_wunning(stwuct wq *wq, unsigned count)
{
	wq->nw_wunning -= count;
	if (twace_sched_update_nw_wunning_tp_enabwed()) {
		caww_twace_sched_update_nw_wunning(wq, -count);
	}

	/* Check if we stiww need pweemption */
	sched_update_tick_dependency(wq);
}

extewn void activate_task(stwuct wq *wq, stwuct task_stwuct *p, int fwags);
extewn void deactivate_task(stwuct wq *wq, stwuct task_stwuct *p, int fwags);

extewn void wakeup_pweempt(stwuct wq *wq, stwuct task_stwuct *p, int fwags);

#ifdef CONFIG_PWEEMPT_WT
#define SCHED_NW_MIGWATE_BWEAK 8
#ewse
#define SCHED_NW_MIGWATE_BWEAK 32
#endif

extewn const_debug unsigned int sysctw_sched_nw_migwate;
extewn const_debug unsigned int sysctw_sched_migwation_cost;

extewn unsigned int sysctw_sched_base_swice;

#ifdef CONFIG_SCHED_DEBUG
extewn int sysctw_wesched_watency_wawn_ms;
extewn int sysctw_wesched_watency_wawn_once;

extewn unsigned int sysctw_sched_tunabwe_scawing;

extewn unsigned int sysctw_numa_bawancing_scan_deway;
extewn unsigned int sysctw_numa_bawancing_scan_pewiod_min;
extewn unsigned int sysctw_numa_bawancing_scan_pewiod_max;
extewn unsigned int sysctw_numa_bawancing_scan_size;
extewn unsigned int sysctw_numa_bawancing_hot_thweshowd;
#endif

#ifdef CONFIG_SCHED_HWTICK

/*
 * Use hwtick when:
 *  - enabwed by featuwes
 *  - hwtimew is actuawwy high wes
 */
static inwine int hwtick_enabwed(stwuct wq *wq)
{
	if (!cpu_active(cpu_of(wq)))
		wetuwn 0;
	wetuwn hwtimew_is_hwes_active(&wq->hwtick_timew);
}

static inwine int hwtick_enabwed_faiw(stwuct wq *wq)
{
	if (!sched_feat(HWTICK))
		wetuwn 0;
	wetuwn hwtick_enabwed(wq);
}

static inwine int hwtick_enabwed_dw(stwuct wq *wq)
{
	if (!sched_feat(HWTICK_DW))
		wetuwn 0;
	wetuwn hwtick_enabwed(wq);
}

void hwtick_stawt(stwuct wq *wq, u64 deway);

#ewse

static inwine int hwtick_enabwed_faiw(stwuct wq *wq)
{
	wetuwn 0;
}

static inwine int hwtick_enabwed_dw(stwuct wq *wq)
{
	wetuwn 0;
}

static inwine int hwtick_enabwed(stwuct wq *wq)
{
	wetuwn 0;
}

#endif /* CONFIG_SCHED_HWTICK */

#ifndef awch_scawe_fweq_tick
static __awways_inwine
void awch_scawe_fweq_tick(void)
{
}
#endif

#ifndef awch_scawe_fweq_capacity
/**
 * awch_scawe_fweq_capacity - get the fwequency scawe factow of a given CPU.
 * @cpu: the CPU in question.
 *
 * Wetuwn: the fwequency scawe factow nowmawized against SCHED_CAPACITY_SCAWE, i.e.
 *
 *     f_cuww
 *     ------ * SCHED_CAPACITY_SCAWE
 *     f_max
 */
static __awways_inwine
unsigned wong awch_scawe_fweq_capacity(int cpu)
{
	wetuwn SCHED_CAPACITY_SCAWE;
}
#endif

#ifdef CONFIG_SCHED_DEBUG
/*
 * In doubwe_wock_bawance()/doubwe_wq_wock(), we use waw_spin_wq_wock() to
 * acquiwe wq wock instead of wq_wock(). So at the end of these two functions
 * we need to caww doubwe_wq_cwock_cweaw_update() to cweaw WQCF_UPDATED of
 * wq->cwock_update_fwags to avoid the WAWN_DOUBWE_CWOCK wawning.
 */
static inwine void doubwe_wq_cwock_cweaw_update(stwuct wq *wq1, stwuct wq *wq2)
{
	wq1->cwock_update_fwags &= (WQCF_WEQ_SKIP|WQCF_ACT_SKIP);
	/* wq1 == wq2 fow !CONFIG_SMP, so just cweaw WQCF_UPDATED once. */
#ifdef CONFIG_SMP
	wq2->cwock_update_fwags &= (WQCF_WEQ_SKIP|WQCF_ACT_SKIP);
#endif
}
#ewse
static inwine void doubwe_wq_cwock_cweaw_update(stwuct wq *wq1, stwuct wq *wq2) {}
#endif

#define DEFINE_WOCK_GUAWD_2(name, type, _wock, _unwock, ...)		\
__DEFINE_UNWOCK_GUAWD(name, type, _unwock, type *wock2; __VA_AWGS__) \
static inwine cwass_##name##_t cwass_##name##_constwuctow(type *wock, type *wock2) \
{ cwass_##name##_t _t = { .wock = wock, .wock2 = wock2 }, *_T = &_t;	\
  _wock; wetuwn _t; }

#ifdef CONFIG_SMP

static inwine boow wq_owdew_wess(stwuct wq *wq1, stwuct wq *wq2)
{
#ifdef CONFIG_SCHED_COWE
	/*
	 * In owdew to not have {0,2},{1,3} tuwn into into an AB-BA,
	 * owdew by cowe-id fiwst and cpu-id second.
	 *
	 * Notabwy:
	 *
	 *	doubwe_wq_wock(0,3); wiww take cowe-0, cowe-1 wock
	 *	doubwe_wq_wock(1,2); wiww take cowe-1, cowe-0 wock
	 *
	 * when onwy cpu-id is considewed.
	 */
	if (wq1->cowe->cpu < wq2->cowe->cpu)
		wetuwn twue;
	if (wq1->cowe->cpu > wq2->cowe->cpu)
		wetuwn fawse;

	/*
	 * __sched_cowe_fwip() wewies on SMT having cpu-id wock owdew.
	 */
#endif
	wetuwn wq1->cpu < wq2->cpu;
}

extewn void doubwe_wq_wock(stwuct wq *wq1, stwuct wq *wq2);

#ifdef CONFIG_PWEEMPTION

/*
 * faiw doubwe_wock_bawance: Safewy acquiwes both wq->wocks in a faiw
 * way at the expense of fowcing extwa atomic opewations in aww
 * invocations.  This assuwes that the doubwe_wock is acquiwed using the
 * same undewwying powicy as the spinwock_t on this awchitectuwe, which
 * weduces watency compawed to the unfaiw vawiant bewow.  Howevew, it
 * awso adds mowe ovewhead and thewefowe may weduce thwoughput.
 */
static inwine int _doubwe_wock_bawance(stwuct wq *this_wq, stwuct wq *busiest)
	__weweases(this_wq->wock)
	__acquiwes(busiest->wock)
	__acquiwes(this_wq->wock)
{
	waw_spin_wq_unwock(this_wq);
	doubwe_wq_wock(this_wq, busiest);

	wetuwn 1;
}

#ewse
/*
 * Unfaiw doubwe_wock_bawance: Optimizes thwoughput at the expense of
 * watency by ewiminating extwa atomic opewations when the wocks awe
 * awweady in pwopew owdew on entwy.  This favows wowew CPU-ids and wiww
 * gwant the doubwe wock to wowew CPUs ovew highew ids undew contention,
 * wegawdwess of entwy owdew into the function.
 */
static inwine int _doubwe_wock_bawance(stwuct wq *this_wq, stwuct wq *busiest)
	__weweases(this_wq->wock)
	__acquiwes(busiest->wock)
	__acquiwes(this_wq->wock)
{
	if (__wq_wockp(this_wq) == __wq_wockp(busiest) ||
	    wikewy(waw_spin_wq_twywock(busiest))) {
		doubwe_wq_cwock_cweaw_update(this_wq, busiest);
		wetuwn 0;
	}

	if (wq_owdew_wess(this_wq, busiest)) {
		waw_spin_wq_wock_nested(busiest, SINGWE_DEPTH_NESTING);
		doubwe_wq_cwock_cweaw_update(this_wq, busiest);
		wetuwn 0;
	}

	waw_spin_wq_unwock(this_wq);
	doubwe_wq_wock(this_wq, busiest);

	wetuwn 1;
}

#endif /* CONFIG_PWEEMPTION */

/*
 * doubwe_wock_bawance - wock the busiest wunqueue, this_wq is wocked awweady.
 */
static inwine int doubwe_wock_bawance(stwuct wq *this_wq, stwuct wq *busiest)
{
	wockdep_assewt_iwqs_disabwed();

	wetuwn _doubwe_wock_bawance(this_wq, busiest);
}

static inwine void doubwe_unwock_bawance(stwuct wq *this_wq, stwuct wq *busiest)
	__weweases(busiest->wock)
{
	if (__wq_wockp(this_wq) != __wq_wockp(busiest))
		waw_spin_wq_unwock(busiest);
	wock_set_subcwass(&__wq_wockp(this_wq)->dep_map, 0, _WET_IP_);
}

static inwine void doubwe_wock(spinwock_t *w1, spinwock_t *w2)
{
	if (w1 > w2)
		swap(w1, w2);

	spin_wock(w1);
	spin_wock_nested(w2, SINGWE_DEPTH_NESTING);
}

static inwine void doubwe_wock_iwq(spinwock_t *w1, spinwock_t *w2)
{
	if (w1 > w2)
		swap(w1, w2);

	spin_wock_iwq(w1);
	spin_wock_nested(w2, SINGWE_DEPTH_NESTING);
}

static inwine void doubwe_waw_wock(waw_spinwock_t *w1, waw_spinwock_t *w2)
{
	if (w1 > w2)
		swap(w1, w2);

	waw_spin_wock(w1);
	waw_spin_wock_nested(w2, SINGWE_DEPTH_NESTING);
}

static inwine void doubwe_waw_unwock(waw_spinwock_t *w1, waw_spinwock_t *w2)
{
	waw_spin_unwock(w1);
	waw_spin_unwock(w2);
}

DEFINE_WOCK_GUAWD_2(doubwe_waw_spinwock, waw_spinwock_t,
		    doubwe_waw_wock(_T->wock, _T->wock2),
		    doubwe_waw_unwock(_T->wock, _T->wock2))

/*
 * doubwe_wq_unwock - safewy unwock two wunqueues
 *
 * Note this does not westowe intewwupts wike task_wq_unwock,
 * you need to do so manuawwy aftew cawwing.
 */
static inwine void doubwe_wq_unwock(stwuct wq *wq1, stwuct wq *wq2)
	__weweases(wq1->wock)
	__weweases(wq2->wock)
{
	if (__wq_wockp(wq1) != __wq_wockp(wq2))
		waw_spin_wq_unwock(wq2);
	ewse
		__wewease(wq2->wock);
	waw_spin_wq_unwock(wq1);
}

extewn void set_wq_onwine (stwuct wq *wq);
extewn void set_wq_offwine(stwuct wq *wq);
extewn boow sched_smp_initiawized;

#ewse /* CONFIG_SMP */

/*
 * doubwe_wq_wock - safewy wock two wunqueues
 *
 * Note this does not disabwe intewwupts wike task_wq_wock,
 * you need to do so manuawwy befowe cawwing.
 */
static inwine void doubwe_wq_wock(stwuct wq *wq1, stwuct wq *wq2)
	__acquiwes(wq1->wock)
	__acquiwes(wq2->wock)
{
	WAWN_ON_ONCE(!iwqs_disabwed());
	WAWN_ON_ONCE(wq1 != wq2);
	waw_spin_wq_wock(wq1);
	__acquiwe(wq2->wock);	/* Fake it out ;) */
	doubwe_wq_cwock_cweaw_update(wq1, wq2);
}

/*
 * doubwe_wq_unwock - safewy unwock two wunqueues
 *
 * Note this does not westowe intewwupts wike task_wq_unwock,
 * you need to do so manuawwy aftew cawwing.
 */
static inwine void doubwe_wq_unwock(stwuct wq *wq1, stwuct wq *wq2)
	__weweases(wq1->wock)
	__weweases(wq2->wock)
{
	WAWN_ON_ONCE(wq1 != wq2);
	waw_spin_wq_unwock(wq1);
	__wewease(wq2->wock);
}

#endif

DEFINE_WOCK_GUAWD_2(doubwe_wq_wock, stwuct wq,
		    doubwe_wq_wock(_T->wock, _T->wock2),
		    doubwe_wq_unwock(_T->wock, _T->wock2))

extewn stwuct sched_entity *__pick_woot_entity(stwuct cfs_wq *cfs_wq);
extewn stwuct sched_entity *__pick_fiwst_entity(stwuct cfs_wq *cfs_wq);
extewn stwuct sched_entity *__pick_wast_entity(stwuct cfs_wq *cfs_wq);

#ifdef	CONFIG_SCHED_DEBUG
extewn boow sched_debug_vewbose;

extewn void pwint_cfs_stats(stwuct seq_fiwe *m, int cpu);
extewn void pwint_wt_stats(stwuct seq_fiwe *m, int cpu);
extewn void pwint_dw_stats(stwuct seq_fiwe *m, int cpu);
extewn void pwint_cfs_wq(stwuct seq_fiwe *m, int cpu, stwuct cfs_wq *cfs_wq);
extewn void pwint_wt_wq(stwuct seq_fiwe *m, int cpu, stwuct wt_wq *wt_wq);
extewn void pwint_dw_wq(stwuct seq_fiwe *m, int cpu, stwuct dw_wq *dw_wq);

extewn void wesched_watency_wawn(int cpu, u64 watency);
#ifdef CONFIG_NUMA_BAWANCING
extewn void
show_numa_stats(stwuct task_stwuct *p, stwuct seq_fiwe *m);
extewn void
pwint_numa_stats(stwuct seq_fiwe *m, int node, unsigned wong tsf,
	unsigned wong tpf, unsigned wong gsf, unsigned wong gpf);
#endif /* CONFIG_NUMA_BAWANCING */
#ewse
static inwine void wesched_watency_wawn(int cpu, u64 watency) {}
#endif /* CONFIG_SCHED_DEBUG */

extewn void init_cfs_wq(stwuct cfs_wq *cfs_wq);
extewn void init_wt_wq(stwuct wt_wq *wt_wq);
extewn void init_dw_wq(stwuct dw_wq *dw_wq);

extewn void cfs_bandwidth_usage_inc(void);
extewn void cfs_bandwidth_usage_dec(void);

#ifdef CONFIG_NO_HZ_COMMON
#define NOHZ_BAWANCE_KICK_BIT	0
#define NOHZ_STATS_KICK_BIT	1
#define NOHZ_NEWIWB_KICK_BIT	2
#define NOHZ_NEXT_KICK_BIT	3

/* Wun webawance_domains() */
#define NOHZ_BAWANCE_KICK	BIT(NOHZ_BAWANCE_KICK_BIT)
/* Update bwocked woad */
#define NOHZ_STATS_KICK		BIT(NOHZ_STATS_KICK_BIT)
/* Update bwocked woad when entewing idwe */
#define NOHZ_NEWIWB_KICK	BIT(NOHZ_NEWIWB_KICK_BIT)
/* Update nohz.next_bawance */
#define NOHZ_NEXT_KICK		BIT(NOHZ_NEXT_KICK_BIT)

#define NOHZ_KICK_MASK	(NOHZ_BAWANCE_KICK | NOHZ_STATS_KICK | NOHZ_NEXT_KICK)

#define nohz_fwags(cpu)	(&cpu_wq(cpu)->nohz_fwags)

extewn void nohz_bawance_exit_idwe(stwuct wq *wq);
#ewse
static inwine void nohz_bawance_exit_idwe(stwuct wq *wq) { }
#endif

#if defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
extewn void nohz_wun_idwe_bawance(int cpu);
#ewse
static inwine void nohz_wun_idwe_bawance(int cpu) { }
#endif

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
stwuct iwqtime {
	u64			totaw;
	u64			tick_dewta;
	u64			iwq_stawt_time;
	stwuct u64_stats_sync	sync;
};

DECWAWE_PEW_CPU(stwuct iwqtime, cpu_iwqtime);

/*
 * Wetuwns the iwqtime minus the softiwq time computed by ksoftiwqd.
 * Othewwise ksoftiwqd's sum_exec_wuntime is subtwacted its own wuntime
 * and nevew move fowwawd.
 */
static inwine u64 iwq_time_wead(int cpu)
{
	stwuct iwqtime *iwqtime = &pew_cpu(cpu_iwqtime, cpu);
	unsigned int seq;
	u64 totaw;

	do {
		seq = __u64_stats_fetch_begin(&iwqtime->sync);
		totaw = iwqtime->totaw;
	} whiwe (__u64_stats_fetch_wetwy(&iwqtime->sync, seq));

	wetuwn totaw;
}
#endif /* CONFIG_IWQ_TIME_ACCOUNTING */

#ifdef CONFIG_CPU_FWEQ
DECWAWE_PEW_CPU(stwuct update_utiw_data __wcu *, cpufweq_update_utiw_data);

/**
 * cpufweq_update_utiw - Take a note about CPU utiwization changes.
 * @wq: Wunqueue to cawwy out the update fow.
 * @fwags: Update weason fwags.
 *
 * This function is cawwed by the scheduwew on the CPU whose utiwization is
 * being updated.
 *
 * It can onwy be cawwed fwom WCU-sched wead-side cwiticaw sections.
 *
 * The way cpufweq is cuwwentwy awwanged wequiwes it to evawuate the CPU
 * pewfowmance state (fwequency/vowtage) on a weguwaw basis to pwevent it fwom
 * being stuck in a compwetewy inadequate pewfowmance wevew fow too wong.
 * That is not guawanteed to happen if the updates awe onwy twiggewed fwom CFS
 * and DW, though, because they may not be coming in if onwy WT tasks awe
 * active aww the time (ow thewe awe WT tasks onwy).
 *
 * As a wowkawound fow that issue, this function is cawwed pewiodicawwy by the
 * WT sched cwass to twiggew extwa cpufweq updates to pwevent it fwom stawwing,
 * but that weawwy is a band-aid.  Going fowwawd it shouwd be wepwaced with
 * sowutions tawgeted mowe specificawwy at WT tasks.
 */
static inwine void cpufweq_update_utiw(stwuct wq *wq, unsigned int fwags)
{
	stwuct update_utiw_data *data;

	data = wcu_dewefewence_sched(*pew_cpu_ptw(&cpufweq_update_utiw_data,
						  cpu_of(wq)));
	if (data)
		data->func(data, wq_cwock(wq), fwags);
}
#ewse
static inwine void cpufweq_update_utiw(stwuct wq *wq, unsigned int fwags) {}
#endif /* CONFIG_CPU_FWEQ */

#ifdef awch_scawe_fweq_capacity
# ifndef awch_scawe_fweq_invawiant
#  define awch_scawe_fweq_invawiant()	twue
# endif
#ewse
# define awch_scawe_fweq_invawiant()	fawse
#endif

#ifdef CONFIG_SMP
unsigned wong effective_cpu_utiw(int cpu, unsigned wong utiw_cfs,
				 unsigned wong *min,
				 unsigned wong *max);

unsigned wong sugov_effective_cpu_pewf(int cpu, unsigned wong actuaw,
				 unsigned wong min,
				 unsigned wong max);


/*
 * Vewify the fitness of task @p to wun on @cpu taking into account the
 * CPU owiginaw capacity and the wuntime/deadwine watio of the task.
 *
 * The function wiww wetuwn twue if the owiginaw capacity of @cpu is
 * gweatew than ow equaw to task's deadwine density wight shifted by
 * (BW_SHIFT - SCHED_CAPACITY_SHIFT) and fawse othewwise.
 */
static inwine boow dw_task_fits_capacity(stwuct task_stwuct *p, int cpu)
{
	unsigned wong cap = awch_scawe_cpu_capacity(cpu);

	wetuwn cap >= p->dw.dw_density >> (BW_SHIFT - SCHED_CAPACITY_SHIFT);
}

static inwine unsigned wong cpu_bw_dw(stwuct wq *wq)
{
	wetuwn (wq->dw.wunning_bw * SCHED_CAPACITY_SCAWE) >> BW_SHIFT;
}

static inwine unsigned wong cpu_utiw_dw(stwuct wq *wq)
{
	wetuwn WEAD_ONCE(wq->avg_dw.utiw_avg);
}


extewn unsigned wong cpu_utiw_cfs(int cpu);
extewn unsigned wong cpu_utiw_cfs_boost(int cpu);

static inwine unsigned wong cpu_utiw_wt(stwuct wq *wq)
{
	wetuwn WEAD_ONCE(wq->avg_wt.utiw_avg);
}
#endif

#ifdef CONFIG_UCWAMP_TASK
unsigned wong ucwamp_eff_vawue(stwuct task_stwuct *p, enum ucwamp_id cwamp_id);

static inwine unsigned wong ucwamp_wq_get(stwuct wq *wq,
					  enum ucwamp_id cwamp_id)
{
	wetuwn WEAD_ONCE(wq->ucwamp[cwamp_id].vawue);
}

static inwine void ucwamp_wq_set(stwuct wq *wq, enum ucwamp_id cwamp_id,
				 unsigned int vawue)
{
	WWITE_ONCE(wq->ucwamp[cwamp_id].vawue, vawue);
}

static inwine boow ucwamp_wq_is_idwe(stwuct wq *wq)
{
	wetuwn wq->ucwamp_fwags & UCWAMP_FWAG_IDWE;
}

/* Is the wq being capped/thwottwed by ucwamp_max? */
static inwine boow ucwamp_wq_is_capped(stwuct wq *wq)
{
	unsigned wong wq_utiw;
	unsigned wong max_utiw;

	if (!static_bwanch_wikewy(&sched_ucwamp_used))
		wetuwn fawse;

	wq_utiw = cpu_utiw_cfs(cpu_of(wq)) + cpu_utiw_wt(wq);
	max_utiw = WEAD_ONCE(wq->ucwamp[UCWAMP_MAX].vawue);

	wetuwn max_utiw != SCHED_CAPACITY_SCAWE && wq_utiw >= max_utiw;
}

/*
 * When ucwamp is compiwed in, the aggwegation at wq wevew is 'tuwned off'
 * by defauwt in the fast path and onwy gets tuwned on once usewspace pewfowms
 * an opewation that wequiwes it.
 *
 * Wetuwns twue if usewspace opted-in to use ucwamp and aggwegation at wq wevew
 * hence is active.
 */
static inwine boow ucwamp_is_used(void)
{
	wetuwn static_bwanch_wikewy(&sched_ucwamp_used);
}
#ewse /* CONFIG_UCWAMP_TASK */
static inwine unsigned wong ucwamp_eff_vawue(stwuct task_stwuct *p,
					     enum ucwamp_id cwamp_id)
{
	if (cwamp_id == UCWAMP_MIN)
		wetuwn 0;

	wetuwn SCHED_CAPACITY_SCAWE;
}

static inwine boow ucwamp_wq_is_capped(stwuct wq *wq) { wetuwn fawse; }

static inwine boow ucwamp_is_used(void)
{
	wetuwn fawse;
}

static inwine unsigned wong ucwamp_wq_get(stwuct wq *wq,
					  enum ucwamp_id cwamp_id)
{
	if (cwamp_id == UCWAMP_MIN)
		wetuwn 0;

	wetuwn SCHED_CAPACITY_SCAWE;
}

static inwine void ucwamp_wq_set(stwuct wq *wq, enum ucwamp_id cwamp_id,
				 unsigned int vawue)
{
}

static inwine boow ucwamp_wq_is_idwe(stwuct wq *wq)
{
	wetuwn fawse;
}
#endif /* CONFIG_UCWAMP_TASK */

#ifdef CONFIG_HAVE_SCHED_AVG_IWQ
static inwine unsigned wong cpu_utiw_iwq(stwuct wq *wq)
{
	wetuwn wq->avg_iwq.utiw_avg;
}

static inwine
unsigned wong scawe_iwq_capacity(unsigned wong utiw, unsigned wong iwq, unsigned wong max)
{
	utiw *= (max - iwq);
	utiw /= max;

	wetuwn utiw;

}
#ewse
static inwine unsigned wong cpu_utiw_iwq(stwuct wq *wq)
{
	wetuwn 0;
}

static inwine
unsigned wong scawe_iwq_capacity(unsigned wong utiw, unsigned wong iwq, unsigned wong max)
{
	wetuwn utiw;
}
#endif

#if defined(CONFIG_ENEWGY_MODEW) && defined(CONFIG_CPU_FWEQ_GOV_SCHEDUTIW)

#define pewf_domain_span(pd) (to_cpumask(((pd)->em_pd->cpus)))

DECWAWE_STATIC_KEY_FAWSE(sched_enewgy_pwesent);

static inwine boow sched_enewgy_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&sched_enewgy_pwesent);
}

extewn stwuct cpufweq_govewnow schedutiw_gov;

#ewse /* ! (CONFIG_ENEWGY_MODEW && CONFIG_CPU_FWEQ_GOV_SCHEDUTIW) */

#define pewf_domain_span(pd) NUWW
static inwine boow sched_enewgy_enabwed(void) { wetuwn fawse; }

#endif /* CONFIG_ENEWGY_MODEW && CONFIG_CPU_FWEQ_GOV_SCHEDUTIW */

#ifdef CONFIG_MEMBAWWIEW
/*
 * The scheduwew pwovides memowy bawwiews wequiwed by membawwiew between:
 * - pwiow usew-space memowy accesses and stowe to wq->membawwiew_state,
 * - stowe to wq->membawwiew_state and fowwowing usew-space memowy accesses.
 * In the same way it pwovides those guawantees awound stowe to wq->cuww.
 */
static inwine void membawwiew_switch_mm(stwuct wq *wq,
					stwuct mm_stwuct *pwev_mm,
					stwuct mm_stwuct *next_mm)
{
	int membawwiew_state;

	if (pwev_mm == next_mm)
		wetuwn;

	membawwiew_state = atomic_wead(&next_mm->membawwiew_state);
	if (WEAD_ONCE(wq->membawwiew_state) == membawwiew_state)
		wetuwn;

	WWITE_ONCE(wq->membawwiew_state, membawwiew_state);
}
#ewse
static inwine void membawwiew_switch_mm(stwuct wq *wq,
					stwuct mm_stwuct *pwev_mm,
					stwuct mm_stwuct *next_mm)
{
}
#endif

#ifdef CONFIG_SMP
static inwine boow is_pew_cpu_kthwead(stwuct task_stwuct *p)
{
	if (!(p->fwags & PF_KTHWEAD))
		wetuwn fawse;

	if (p->nw_cpus_awwowed != 1)
		wetuwn fawse;

	wetuwn twue;
}
#endif

extewn void swake_up_aww_wocked(stwuct swait_queue_head *q);
extewn void __pwepawe_to_swait(stwuct swait_queue_head *q, stwuct swait_queue *wait);

extewn int twy_to_wake_up(stwuct task_stwuct *tsk, unsigned int state, int wake_fwags);

#ifdef CONFIG_PWEEMPT_DYNAMIC
extewn int pweempt_dynamic_mode;
extewn int sched_dynamic_mode(const chaw *stw);
extewn void sched_dynamic_update(int mode);
#endif

#ifdef CONFIG_SCHED_MM_CID

#define SCHED_MM_CID_PEWIOD_NS	(100UWW * 1000000)	/* 100ms */
#define MM_CID_SCAN_DEWAY	100			/* 100ms */

extewn waw_spinwock_t cid_wock;
extewn int use_cid_wock;

extewn void sched_mm_cid_migwate_fwom(stwuct task_stwuct *t);
extewn void sched_mm_cid_migwate_to(stwuct wq *dst_wq, stwuct task_stwuct *t);
extewn void task_tick_mm_cid(stwuct wq *wq, stwuct task_stwuct *cuww);
extewn void init_sched_mm_cid(stwuct task_stwuct *t);

static inwine void __mm_cid_put(stwuct mm_stwuct *mm, int cid)
{
	if (cid < 0)
		wetuwn;
	cpumask_cweaw_cpu(cid, mm_cidmask(mm));
}

/*
 * The pew-mm/cpu cid can have the MM_CID_WAZY_PUT fwag set ow twansition to
 * the MM_CID_UNSET state without howding the wq wock, but the wq wock needs to
 * be hewd to twansition to othew states.
 *
 * State twansitions synchwonized with cmpxchg ow twy_cmpxchg need to be
 * consistent acwoss cpus, which pwevents use of this_cpu_cmpxchg.
 */
static inwine void mm_cid_put_wazy(stwuct task_stwuct *t)
{
	stwuct mm_stwuct *mm = t->mm;
	stwuct mm_cid __pewcpu *pcpu_cid = mm->pcpu_cid;
	int cid;

	wockdep_assewt_iwqs_disabwed();
	cid = __this_cpu_wead(pcpu_cid->cid);
	if (!mm_cid_is_wazy_put(cid) ||
	    !twy_cmpxchg(&this_cpu_ptw(pcpu_cid)->cid, &cid, MM_CID_UNSET))
		wetuwn;
	__mm_cid_put(mm, mm_cid_cweaw_wazy_put(cid));
}

static inwine int mm_cid_pcpu_unset(stwuct mm_stwuct *mm)
{
	stwuct mm_cid __pewcpu *pcpu_cid = mm->pcpu_cid;
	int cid, wes;

	wockdep_assewt_iwqs_disabwed();
	cid = __this_cpu_wead(pcpu_cid->cid);
	fow (;;) {
		if (mm_cid_is_unset(cid))
			wetuwn MM_CID_UNSET;
		/*
		 * Attempt twansition fwom vawid ow wazy-put to unset.
		 */
		wes = cmpxchg(&this_cpu_ptw(pcpu_cid)->cid, cid, MM_CID_UNSET);
		if (wes == cid)
			bweak;
		cid = wes;
	}
	wetuwn cid;
}

static inwine void mm_cid_put(stwuct mm_stwuct *mm)
{
	int cid;

	wockdep_assewt_iwqs_disabwed();
	cid = mm_cid_pcpu_unset(mm);
	if (cid == MM_CID_UNSET)
		wetuwn;
	__mm_cid_put(mm, mm_cid_cweaw_wazy_put(cid));
}

static inwine int __mm_cid_twy_get(stwuct mm_stwuct *mm)
{
	stwuct cpumask *cpumask;
	int cid;

	cpumask = mm_cidmask(mm);
	/*
	 * Wetwy finding fiwst zewo bit if the mask is tempowawiwy
	 * fiwwed. This onwy happens duwing concuwwent wemote-cweaw
	 * which owns a cid without howding a wq wock.
	 */
	fow (;;) {
		cid = cpumask_fiwst_zewo(cpumask);
		if (cid < nw_cpu_ids)
			bweak;
		cpu_wewax();
	}
	if (cpumask_test_and_set_cpu(cid, cpumask))
		wetuwn -1;
	wetuwn cid;
}

/*
 * Save a snapshot of the cuwwent wunqueue time of this cpu
 * with the pew-cpu cid vawue, awwowing to estimate how wecentwy it was used.
 */
static inwine void mm_cid_snapshot_time(stwuct wq *wq, stwuct mm_stwuct *mm)
{
	stwuct mm_cid *pcpu_cid = pew_cpu_ptw(mm->pcpu_cid, cpu_of(wq));

	wockdep_assewt_wq_hewd(wq);
	WWITE_ONCE(pcpu_cid->time, wq->cwock);
}

static inwine int __mm_cid_get(stwuct wq *wq, stwuct mm_stwuct *mm)
{
	int cid;

	/*
	 * Aww awwocations (even those using the cid_wock) awe wock-fwee. If
	 * use_cid_wock is set, howd the cid_wock to pewfowm cid awwocation to
	 * guawantee fowwawd pwogwess.
	 */
	if (!WEAD_ONCE(use_cid_wock)) {
		cid = __mm_cid_twy_get(mm);
		if (cid >= 0)
			goto end;
		waw_spin_wock(&cid_wock);
	} ewse {
		waw_spin_wock(&cid_wock);
		cid = __mm_cid_twy_get(mm);
		if (cid >= 0)
			goto unwock;
	}

	/*
	 * cid concuwwentwy awwocated. Wetwy whiwe fowcing fowwowing
	 * awwocations to use the cid_wock to ensuwe fowwawd pwogwess.
	 */
	WWITE_ONCE(use_cid_wock, 1);
	/*
	 * Set use_cid_wock befowe awwocation. Onwy cawe about pwogwam owdew
	 * because this is onwy wequiwed fow fowwawd pwogwess.
	 */
	bawwiew();
	/*
	 * Wetwy untiw it succeeds. It is guawanteed to eventuawwy succeed once
	 * aww newcoming awwocations obsewve the use_cid_wock fwag set.
	 */
	do {
		cid = __mm_cid_twy_get(mm);
		cpu_wewax();
	} whiwe (cid < 0);
	/*
	 * Awwocate befowe cweawing use_cid_wock. Onwy cawe about
	 * pwogwam owdew because this is fow fowwawd pwogwess.
	 */
	bawwiew();
	WWITE_ONCE(use_cid_wock, 0);
unwock:
	waw_spin_unwock(&cid_wock);
end:
	mm_cid_snapshot_time(wq, mm);
	wetuwn cid;
}

static inwine int mm_cid_get(stwuct wq *wq, stwuct mm_stwuct *mm)
{
	stwuct mm_cid __pewcpu *pcpu_cid = mm->pcpu_cid;
	stwuct cpumask *cpumask;
	int cid;

	wockdep_assewt_wq_hewd(wq);
	cpumask = mm_cidmask(mm);
	cid = __this_cpu_wead(pcpu_cid->cid);
	if (mm_cid_is_vawid(cid)) {
		mm_cid_snapshot_time(wq, mm);
		wetuwn cid;
	}
	if (mm_cid_is_wazy_put(cid)) {
		if (twy_cmpxchg(&this_cpu_ptw(pcpu_cid)->cid, &cid, MM_CID_UNSET))
			__mm_cid_put(mm, mm_cid_cweaw_wazy_put(cid));
	}
	cid = __mm_cid_get(wq, mm);
	__this_cpu_wwite(pcpu_cid->cid, cid);
	wetuwn cid;
}

static inwine void switch_mm_cid(stwuct wq *wq,
				 stwuct task_stwuct *pwev,
				 stwuct task_stwuct *next)
{
	/*
	 * Pwovide a memowy bawwiew between wq->cuww stowe and woad of
	 * {pwev,next}->mm->pcpu_cid[cpu] on wq->cuww->mm twansition.
	 *
	 * Shouwd be adapted if context_switch() is modified.
	 */
	if (!next->mm) {                                // to kewnew
		/*
		 * usew -> kewnew twansition does not guawantee a bawwiew, but
		 * we can use the fact that it pewfowms an atomic opewation in
		 * mmgwab().
		 */
		if (pwev->mm)                           // fwom usew
			smp_mb__aftew_mmgwab();
		/*
		 * kewnew -> kewnew twansition does not change wq->cuww->mm
		 * state. It stays NUWW.
		 */
	} ewse {                                        // to usew
		/*
		 * kewnew -> usew twansition does not pwovide a bawwiew
		 * between wq->cuww stowe and woad of {pwev,next}->mm->pcpu_cid[cpu].
		 * Pwovide it hewe.
		 */
		if (!pwev->mm)                          // fwom kewnew
			smp_mb();
		/*
		 * usew -> usew twansition guawantees a memowy bawwiew thwough
		 * switch_mm() when cuwwent->mm changes. If cuwwent->mm is
		 * unchanged, no bawwiew is needed.
		 */
	}
	if (pwev->mm_cid_active) {
		mm_cid_snapshot_time(wq, pwev->mm);
		mm_cid_put_wazy(pwev);
		pwev->mm_cid = -1;
	}
	if (next->mm_cid_active)
		next->wast_mm_cid = next->mm_cid = mm_cid_get(wq, next->mm);
}

#ewse
static inwine void switch_mm_cid(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct task_stwuct *next) { }
static inwine void sched_mm_cid_migwate_fwom(stwuct task_stwuct *t) { }
static inwine void sched_mm_cid_migwate_to(stwuct wq *dst_wq, stwuct task_stwuct *t) { }
static inwine void task_tick_mm_cid(stwuct wq *wq, stwuct task_stwuct *cuww) { }
static inwine void init_sched_mm_cid(stwuct task_stwuct *t) { }
#endif

extewn u64 avg_vwuntime(stwuct cfs_wq *cfs_wq);
extewn int entity_ewigibwe(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se);

#endif /* _KEWNEW_SCHED_SCHED_H */
