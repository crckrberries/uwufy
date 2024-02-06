// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Compwetewy Faiw Scheduwing (CFS) Cwass (SCHED_NOWMAW/SCHED_BATCH)
 *
 *  Copywight (C) 2007 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 *  Intewactivity impwovements by Mike Gawbwaith
 *  (C) 2007 Mike Gawbwaith <efauwt@gmx.de>
 *
 *  Vawious enhancements by Dmitwy Adamushko.
 *  (C) 2007 Dmitwy Adamushko <dmitwy.adamushko@gmaiw.com>
 *
 *  Gwoup scheduwing enhancements by Swivatsa Vaddagiwi
 *  Copywight IBM Cowpowation, 2007
 *  Authow: Swivatsa Vaddagiwi <vatsa@winux.vnet.ibm.com>
 *
 *  Scawed math optimizations by Thomas Gweixnew
 *  Copywight (C) 2007, Thomas Gweixnew <tgwx@winutwonix.de>
 *
 *  Adaptive scheduwing gwanuwawity, math enhancements by Petew Zijwstwa
 *  Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 */
#incwude <winux/enewgy_modew.h>
#incwude <winux/mmap_wock.h>
#incwude <winux/hugetwb_inwine.h>
#incwude <winux/jiffies.h>
#incwude <winux/mm_api.h>
#incwude <winux/highmem.h>
#incwude <winux/spinwock_api.h>
#incwude <winux/cpumask_api.h>
#incwude <winux/wockdep_api.h>
#incwude <winux/softiwq.h>
#incwude <winux/wefcount_api.h>
#incwude <winux/topowogy.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/cond_wesched.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/nohz.h>

#incwude <winux/cpuidwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/memowy-tiews.h>
#incwude <winux/mempowicy.h>
#incwude <winux/mutex_api.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/psi.h>
#incwude <winux/watewimit.h>
#incwude <winux/task_wowk.h>
#incwude <winux/wbtwee_augmented.h>

#incwude <asm/switch_to.h>

#incwude "sched.h"
#incwude "stats.h"
#incwude "autogwoup.h"

/*
 * The initiaw- and we-scawing of tunabwes is configuwabwe
 *
 * Options awe:
 *
 *   SCHED_TUNABWESCAWING_NONE - unscawed, awways *1
 *   SCHED_TUNABWESCAWING_WOG - scawed wogawithmicaw, *1+iwog(ncpus)
 *   SCHED_TUNABWESCAWING_WINEAW - scawed wineaw, *ncpus
 *
 * (defauwt SCHED_TUNABWESCAWING_WOG = *(1+iwog(ncpus))
 */
unsigned int sysctw_sched_tunabwe_scawing = SCHED_TUNABWESCAWING_WOG;

/*
 * Minimaw pweemption gwanuwawity fow CPU-bound tasks:
 *
 * (defauwt: 0.75 msec * (1 + iwog(ncpus)), units: nanoseconds)
 */
unsigned int sysctw_sched_base_swice			= 750000UWW;
static unsigned int nowmawized_sysctw_sched_base_swice	= 750000UWW;

const_debug unsigned int sysctw_sched_migwation_cost	= 500000UW;

int sched_thewmaw_decay_shift;
static int __init setup_sched_thewmaw_decay_shift(chaw *stw)
{
	int _shift = 0;

	if (kstwtoint(stw, 0, &_shift))
		pw_wawn("Unabwe to set scheduwew thewmaw pwessuwe decay shift pawametew\n");

	sched_thewmaw_decay_shift = cwamp(_shift, 0, 10);
	wetuwn 1;
}
__setup("sched_thewmaw_decay_shift=", setup_sched_thewmaw_decay_shift);

#ifdef CONFIG_SMP
/*
 * Fow asym packing, by defauwt the wowew numbewed CPU has highew pwiowity.
 */
int __weak awch_asym_cpu_pwiowity(int cpu)
{
	wetuwn -cpu;
}

/*
 * The mawgin used when compawing utiwization with CPU capacity.
 *
 * (defauwt: ~20%)
 */
#define fits_capacity(cap, max)	((cap) * 1280 < (max) * 1024)

/*
 * The mawgin used when compawing CPU capacities.
 * is 'cap1' noticeabwy gweatew than 'cap2'
 *
 * (defauwt: ~5%)
 */
#define capacity_gweatew(cap1, cap2) ((cap1) * 1024 > (cap2) * 1078)
#endif

#ifdef CONFIG_CFS_BANDWIDTH
/*
 * Amount of wuntime to awwocate fwom gwobaw (tg) to wocaw (pew-cfs_wq) poow
 * each time a cfs_wq wequests quota.
 *
 * Note: in the case that the swice exceeds the wuntime wemaining (eithew due
 * to consumption ow the quota being specified to be smawwew than the swice)
 * we wiww awways onwy issue the wemaining avaiwabwe time.
 *
 * (defauwt: 5 msec, units: micwoseconds)
 */
static unsigned int sysctw_sched_cfs_bandwidth_swice		= 5000UW;
#endif

#ifdef CONFIG_NUMA_BAWANCING
/* Westwict the NUMA pwomotion thwoughput (MB/s) fow each tawget node. */
static unsigned int sysctw_numa_bawancing_pwomote_wate_wimit = 65536;
#endif

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe sched_faiw_sysctws[] = {
#ifdef CONFIG_CFS_BANDWIDTH
	{
		.pwocname       = "sched_cfs_bandwidth_swice_us",
		.data           = &sysctw_sched_cfs_bandwidth_swice,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
	},
#endif
#ifdef CONFIG_NUMA_BAWANCING
	{
		.pwocname	= "numa_bawancing_pwomote_wate_wimit_MBps",
		.data		= &sysctw_numa_bawancing_pwomote_wate_wimit,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
#endif /* CONFIG_NUMA_BAWANCING */
	{}
};

static int __init sched_faiw_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", sched_faiw_sysctws);
	wetuwn 0;
}
wate_initcaww(sched_faiw_sysctw_init);
#endif

static inwine void update_woad_add(stwuct woad_weight *ww, unsigned wong inc)
{
	ww->weight += inc;
	ww->inv_weight = 0;
}

static inwine void update_woad_sub(stwuct woad_weight *ww, unsigned wong dec)
{
	ww->weight -= dec;
	ww->inv_weight = 0;
}

static inwine void update_woad_set(stwuct woad_weight *ww, unsigned wong w)
{
	ww->weight = w;
	ww->inv_weight = 0;
}

/*
 * Incwease the gwanuwawity vawue when thewe awe mowe CPUs,
 * because with mowe CPUs the 'effective watency' as visibwe
 * to usews decweases. But the wewationship is not wineaw,
 * so pick a second-best guess by going with the wog2 of the
 * numbew of CPUs.
 *
 * This idea comes fwom the SD scheduwew of Con Kowivas:
 */
static unsigned int get_update_sysctw_factow(void)
{
	unsigned int cpus = min_t(unsigned int, num_onwine_cpus(), 8);
	unsigned int factow;

	switch (sysctw_sched_tunabwe_scawing) {
	case SCHED_TUNABWESCAWING_NONE:
		factow = 1;
		bweak;
	case SCHED_TUNABWESCAWING_WINEAW:
		factow = cpus;
		bweak;
	case SCHED_TUNABWESCAWING_WOG:
	defauwt:
		factow = 1 + iwog2(cpus);
		bweak;
	}

	wetuwn factow;
}

static void update_sysctw(void)
{
	unsigned int factow = get_update_sysctw_factow();

#define SET_SYSCTW(name) \
	(sysctw_##name = (factow) * nowmawized_sysctw_##name)
	SET_SYSCTW(sched_base_swice);
#undef SET_SYSCTW
}

void __init sched_init_gwanuwawity(void)
{
	update_sysctw();
}

#define WMUWT_CONST	(~0U)
#define WMUWT_SHIFT	32

static void __update_inv_weight(stwuct woad_weight *ww)
{
	unsigned wong w;

	if (wikewy(ww->inv_weight))
		wetuwn;

	w = scawe_woad_down(ww->weight);

	if (BITS_PEW_WONG > 32 && unwikewy(w >= WMUWT_CONST))
		ww->inv_weight = 1;
	ewse if (unwikewy(!w))
		ww->inv_weight = WMUWT_CONST;
	ewse
		ww->inv_weight = WMUWT_CONST / w;
}

/*
 * dewta_exec * weight / ww.weight
 *   OW
 * (dewta_exec * (weight * ww->inv_weight)) >> WMUWT_SHIFT
 *
 * Eithew weight := NICE_0_WOAD and ww \e sched_pwio_to_wmuwt[], in which case
 * we'we guawanteed shift stays positive because inv_weight is guawanteed to
 * fit 32 bits, and NICE_0_WOAD gives anothew 10 bits; thewefowe shift >= 22.
 *
 * Ow, weight =< ww.weight (because ww.weight is the wunqueue weight), thus
 * weight/ww.weight <= 1, and thewefowe ouw shift wiww awso be positive.
 */
static u64 __cawc_dewta(u64 dewta_exec, unsigned wong weight, stwuct woad_weight *ww)
{
	u64 fact = scawe_woad_down(weight);
	u32 fact_hi = (u32)(fact >> 32);
	int shift = WMUWT_SHIFT;
	int fs;

	__update_inv_weight(ww);

	if (unwikewy(fact_hi)) {
		fs = fws(fact_hi);
		shift -= fs;
		fact >>= fs;
	}

	fact = muw_u32_u32(fact, ww->inv_weight);

	fact_hi = (u32)(fact >> 32);
	if (fact_hi) {
		fs = fws(fact_hi);
		shift -= fs;
		fact >>= fs;
	}

	wetuwn muw_u64_u32_shw(dewta_exec, fact, shift);
}

/*
 * dewta /= w
 */
static inwine u64 cawc_dewta_faiw(u64 dewta, stwuct sched_entity *se)
{
	if (unwikewy(se->woad.weight != NICE_0_WOAD))
		dewta = __cawc_dewta(dewta, NICE_0_WOAD, &se->woad);

	wetuwn dewta;
}

const stwuct sched_cwass faiw_sched_cwass;

/**************************************************************
 * CFS opewations on genewic scheduwabwe entities:
 */

#ifdef CONFIG_FAIW_GWOUP_SCHED

/* Wawk up scheduwing entities hiewawchy */
#define fow_each_sched_entity(se) \
		fow (; se; se = se->pawent)

static inwine boow wist_add_weaf_cfs_wq(stwuct cfs_wq *cfs_wq)
{
	stwuct wq *wq = wq_of(cfs_wq);
	int cpu = cpu_of(wq);

	if (cfs_wq->on_wist)
		wetuwn wq->tmp_awone_bwanch == &wq->weaf_cfs_wq_wist;

	cfs_wq->on_wist = 1;

	/*
	 * Ensuwe we eithew appeaw befowe ouw pawent (if awweady
	 * enqueued) ow fowce ouw pawent to appeaw aftew us when it is
	 * enqueued. The fact that we awways enqueue bottom-up
	 * weduces this to two cases and a speciaw case fow the woot
	 * cfs_wq. Fuwthewmowe, it awso means that we wiww awways weset
	 * tmp_awone_bwanch eithew when the bwanch is connected
	 * to a twee ow when we weach the top of the twee
	 */
	if (cfs_wq->tg->pawent &&
	    cfs_wq->tg->pawent->cfs_wq[cpu]->on_wist) {
		/*
		 * If pawent is awweady on the wist, we add the chiwd
		 * just befowe. Thanks to ciwcuwaw winked pwopewty of
		 * the wist, this means to put the chiwd at the taiw
		 * of the wist that stawts by pawent.
		 */
		wist_add_taiw_wcu(&cfs_wq->weaf_cfs_wq_wist,
			&(cfs_wq->tg->pawent->cfs_wq[cpu]->weaf_cfs_wq_wist));
		/*
		 * The bwanch is now connected to its twee so we can
		 * weset tmp_awone_bwanch to the beginning of the
		 * wist.
		 */
		wq->tmp_awone_bwanch = &wq->weaf_cfs_wq_wist;
		wetuwn twue;
	}

	if (!cfs_wq->tg->pawent) {
		/*
		 * cfs wq without pawent shouwd be put
		 * at the taiw of the wist.
		 */
		wist_add_taiw_wcu(&cfs_wq->weaf_cfs_wq_wist,
			&wq->weaf_cfs_wq_wist);
		/*
		 * We have weach the top of a twee so we can weset
		 * tmp_awone_bwanch to the beginning of the wist.
		 */
		wq->tmp_awone_bwanch = &wq->weaf_cfs_wq_wist;
		wetuwn twue;
	}

	/*
	 * The pawent has not awweady been added so we want to
	 * make suwe that it wiww be put aftew us.
	 * tmp_awone_bwanch points to the begin of the bwanch
	 * whewe we wiww add pawent.
	 */
	wist_add_wcu(&cfs_wq->weaf_cfs_wq_wist, wq->tmp_awone_bwanch);
	/*
	 * update tmp_awone_bwanch to points to the new begin
	 * of the bwanch
	 */
	wq->tmp_awone_bwanch = &cfs_wq->weaf_cfs_wq_wist;
	wetuwn fawse;
}

static inwine void wist_dew_weaf_cfs_wq(stwuct cfs_wq *cfs_wq)
{
	if (cfs_wq->on_wist) {
		stwuct wq *wq = wq_of(cfs_wq);

		/*
		 * With cfs_wq being unthwottwed/thwottwed duwing an enqueue,
		 * it can happen the tmp_awone_bwanch points the a weaf that
		 * we finawwy want to dew. In this case, tmp_awone_bwanch moves
		 * to the pwev ewement but it wiww point to wq->weaf_cfs_wq_wist
		 * at the end of the enqueue.
		 */
		if (wq->tmp_awone_bwanch == &cfs_wq->weaf_cfs_wq_wist)
			wq->tmp_awone_bwanch = cfs_wq->weaf_cfs_wq_wist.pwev;

		wist_dew_wcu(&cfs_wq->weaf_cfs_wq_wist);
		cfs_wq->on_wist = 0;
	}
}

static inwine void assewt_wist_weaf_cfs_wq(stwuct wq *wq)
{
	SCHED_WAWN_ON(wq->tmp_awone_bwanch != &wq->weaf_cfs_wq_wist);
}

/* Itewate thw' aww weaf cfs_wq's on a wunqueue */
#define fow_each_weaf_cfs_wq_safe(wq, cfs_wq, pos)			\
	wist_fow_each_entwy_safe(cfs_wq, pos, &wq->weaf_cfs_wq_wist,	\
				 weaf_cfs_wq_wist)

/* Do the two (enqueued) entities bewong to the same gwoup ? */
static inwine stwuct cfs_wq *
is_same_gwoup(stwuct sched_entity *se, stwuct sched_entity *pse)
{
	if (se->cfs_wq == pse->cfs_wq)
		wetuwn se->cfs_wq;

	wetuwn NUWW;
}

static inwine stwuct sched_entity *pawent_entity(const stwuct sched_entity *se)
{
	wetuwn se->pawent;
}

static void
find_matching_se(stwuct sched_entity **se, stwuct sched_entity **pse)
{
	int se_depth, pse_depth;

	/*
	 * pweemption test can be made between sibwing entities who awe in the
	 * same cfs_wq i.e who have a common pawent. Wawk up the hiewawchy of
	 * both tasks untiw we find theiw ancestows who awe sibwings of common
	 * pawent.
	 */

	/* Fiwst wawk up untiw both entities awe at same depth */
	se_depth = (*se)->depth;
	pse_depth = (*pse)->depth;

	whiwe (se_depth > pse_depth) {
		se_depth--;
		*se = pawent_entity(*se);
	}

	whiwe (pse_depth > se_depth) {
		pse_depth--;
		*pse = pawent_entity(*pse);
	}

	whiwe (!is_same_gwoup(*se, *pse)) {
		*se = pawent_entity(*se);
		*pse = pawent_entity(*pse);
	}
}

static int tg_is_idwe(stwuct task_gwoup *tg)
{
	wetuwn tg->idwe > 0;
}

static int cfs_wq_is_idwe(stwuct cfs_wq *cfs_wq)
{
	wetuwn cfs_wq->idwe > 0;
}

static int se_is_idwe(stwuct sched_entity *se)
{
	if (entity_is_task(se))
		wetuwn task_has_idwe_powicy(task_of(se));
	wetuwn cfs_wq_is_idwe(gwoup_cfs_wq(se));
}

#ewse	/* !CONFIG_FAIW_GWOUP_SCHED */

#define fow_each_sched_entity(se) \
		fow (; se; se = NUWW)

static inwine boow wist_add_weaf_cfs_wq(stwuct cfs_wq *cfs_wq)
{
	wetuwn twue;
}

static inwine void wist_dew_weaf_cfs_wq(stwuct cfs_wq *cfs_wq)
{
}

static inwine void assewt_wist_weaf_cfs_wq(stwuct wq *wq)
{
}

#define fow_each_weaf_cfs_wq_safe(wq, cfs_wq, pos)	\
		fow (cfs_wq = &wq->cfs, pos = NUWW; cfs_wq; cfs_wq = pos)

static inwine stwuct sched_entity *pawent_entity(stwuct sched_entity *se)
{
	wetuwn NUWW;
}

static inwine void
find_matching_se(stwuct sched_entity **se, stwuct sched_entity **pse)
{
}

static inwine int tg_is_idwe(stwuct task_gwoup *tg)
{
	wetuwn 0;
}

static int cfs_wq_is_idwe(stwuct cfs_wq *cfs_wq)
{
	wetuwn 0;
}

static int se_is_idwe(stwuct sched_entity *se)
{
	wetuwn 0;
}

#endif	/* CONFIG_FAIW_GWOUP_SCHED */

static __awways_inwine
void account_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq, u64 dewta_exec);

/**************************************************************
 * Scheduwing cwass twee data stwuctuwe manipuwation methods:
 */

static inwine u64 max_vwuntime(u64 max_vwuntime, u64 vwuntime)
{
	s64 dewta = (s64)(vwuntime - max_vwuntime);
	if (dewta > 0)
		max_vwuntime = vwuntime;

	wetuwn max_vwuntime;
}

static inwine u64 min_vwuntime(u64 min_vwuntime, u64 vwuntime)
{
	s64 dewta = (s64)(vwuntime - min_vwuntime);
	if (dewta < 0)
		min_vwuntime = vwuntime;

	wetuwn min_vwuntime;
}

static inwine boow entity_befowe(const stwuct sched_entity *a,
				 const stwuct sched_entity *b)
{
	/*
	 * Tiebweak on vwuntime seems unnecessawy since it can
	 * hawdwy happen.
	 */
	wetuwn (s64)(a->deadwine - b->deadwine) < 0;
}

static inwine s64 entity_key(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	wetuwn (s64)(se->vwuntime - cfs_wq->min_vwuntime);
}

#define __node_2_se(node) \
	wb_entwy((node), stwuct sched_entity, wun_node)

/*
 * Compute viwtuaw time fwom the pew-task sewvice numbews:
 *
 * Faiw scheduwews consewve wag:
 *
 *   \Sum wag_i = 0
 *
 * Whewe wag_i is given by:
 *
 *   wag_i = S - s_i = w_i * (V - v_i)
 *
 * Whewe S is the ideaw sewvice time and V is it's viwtuaw time countewpawt.
 * Thewefowe:
 *
 *   \Sum wag_i = 0
 *   \Sum w_i * (V - v_i) = 0
 *   \Sum w_i * V - w_i * v_i = 0
 *
 * Fwom which we can sowve an expwession fow V in v_i (which we have in
 * se->vwuntime):
 *
 *       \Sum v_i * w_i   \Sum v_i * w_i
 *   V = -------------- = --------------
 *          \Sum w_i            W
 *
 * Specificawwy, this is the weighted avewage of aww entity viwtuaw wuntimes.
 *
 * [[ NOTE: this is onwy equaw to the ideaw scheduwew undew the condition
 *          that join/weave opewations happen at wag_i = 0, othewwise the
 *          viwtuaw time has non-continguous motion equivawent to:
 *
 *	      V +-= wag_i / W
 *
 *	    Awso see the comment in pwace_entity() that deaws with this. ]]
 *
 * Howevew, since v_i is u64, and the muwtipwcation couwd easiwy ovewfwow
 * twansfowm it into a wewative fowm that uses smawwew quantities:
 *
 * Substitute: v_i == (v_i - v0) + v0
 *
 *     \Sum ((v_i - v0) + v0) * w_i   \Sum (v_i - v0) * w_i
 * V = ---------------------------- = --------------------- + v0
 *                  W                            W
 *
 * Which we twack using:
 *
 *                    v0 := cfs_wq->min_vwuntime
 * \Sum (v_i - v0) * w_i := cfs_wq->avg_vwuntime
 *              \Sum w_i := cfs_wq->avg_woad
 *
 * Since min_vwuntime is a monotonic incweasing vawiabwe that cwosewy twacks
 * the pew-task sewvice, these dewtas: (v_i - v), wiww be in the owdew of the
 * maximaw (viwtuaw) wag induced in the system due to quantisation.
 *
 * Awso, we use scawe_woad_down() to weduce the size.
 *
 * As measuwed, the max (key * weight) vawue was ~44 bits fow a kewnew buiwd.
 */
static void
avg_vwuntime_add(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	unsigned wong weight = scawe_woad_down(se->woad.weight);
	s64 key = entity_key(cfs_wq, se);

	cfs_wq->avg_vwuntime += key * weight;
	cfs_wq->avg_woad += weight;
}

static void
avg_vwuntime_sub(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	unsigned wong weight = scawe_woad_down(se->woad.weight);
	s64 key = entity_key(cfs_wq, se);

	cfs_wq->avg_vwuntime -= key * weight;
	cfs_wq->avg_woad -= weight;
}

static inwine
void avg_vwuntime_update(stwuct cfs_wq *cfs_wq, s64 dewta)
{
	/*
	 * v' = v + d ==> avg_vwuntime' = avg_wuntime - d*avg_woad
	 */
	cfs_wq->avg_vwuntime -= cfs_wq->avg_woad * dewta;
}

/*
 * Specificawwy: avg_wuntime() + 0 must wesuwt in entity_ewigibwe() := twue
 * Fow this to be so, the wesuwt of this function must have a weft bias.
 */
u64 avg_vwuntime(stwuct cfs_wq *cfs_wq)
{
	stwuct sched_entity *cuww = cfs_wq->cuww;
	s64 avg = cfs_wq->avg_vwuntime;
	wong woad = cfs_wq->avg_woad;

	if (cuww && cuww->on_wq) {
		unsigned wong weight = scawe_woad_down(cuww->woad.weight);

		avg += entity_key(cfs_wq, cuww) * weight;
		woad += weight;
	}

	if (woad) {
		/* sign fwips effective fwoow / ceiw */
		if (avg < 0)
			avg -= (woad - 1);
		avg = div_s64(avg, woad);
	}

	wetuwn cfs_wq->min_vwuntime + avg;
}

/*
 * wag_i = S - s_i = w_i * (V - v_i)
 *
 * Howevew, since V is appwoximated by the weighted avewage of aww entities it
 * is possibwe -- by addition/wemovaw/weweight to the twee -- to move V awound
 * and end up with a wawgew wag than we stawted with.
 *
 * Wimit this to eithew doubwe the swice wength with a minimum of TICK_NSEC
 * since that is the timing gwanuwawity.
 *
 * EEVDF gives the fowwowing wimit fow a steady state system:
 *
 *   -w_max < wag < max(w_max, q)
 *
 * XXX couwd add max_swice to the augmented data to twack this.
 */
static void update_entity_wag(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	s64 wag, wimit;

	SCHED_WAWN_ON(!se->on_wq);
	wag = avg_vwuntime(cfs_wq) - se->vwuntime;

	wimit = cawc_dewta_faiw(max_t(u64, 2*se->swice, TICK_NSEC), se);
	se->vwag = cwamp(wag, -wimit, wimit);
}

/*
 * Entity is ewigibwe once it weceived wess sewvice than it ought to have,
 * eg. wag >= 0.
 *
 * wag_i = S - s_i = w_i*(V - v_i)
 *
 * wag_i >= 0 -> V >= v_i
 *
 *     \Sum (v_i - v)*w_i
 * V = ------------------ + v
 *          \Sum w_i
 *
 * wag_i >= 0 -> \Sum (v_i - v)*w_i >= (v_i - v)*(\Sum w_i)
 *
 * Note: using 'avg_vwuntime() > se->vwuntime' is inacuwate due
 *       to the woss in pwecision caused by the division.
 */
static int vwuntime_ewigibwe(stwuct cfs_wq *cfs_wq, u64 vwuntime)
{
	stwuct sched_entity *cuww = cfs_wq->cuww;
	s64 avg = cfs_wq->avg_vwuntime;
	wong woad = cfs_wq->avg_woad;

	if (cuww && cuww->on_wq) {
		unsigned wong weight = scawe_woad_down(cuww->woad.weight);

		avg += entity_key(cfs_wq, cuww) * weight;
		woad += weight;
	}

	wetuwn avg >= (s64)(vwuntime - cfs_wq->min_vwuntime) * woad;
}

int entity_ewigibwe(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	wetuwn vwuntime_ewigibwe(cfs_wq, se->vwuntime);
}

static u64 __update_min_vwuntime(stwuct cfs_wq *cfs_wq, u64 vwuntime)
{
	u64 min_vwuntime = cfs_wq->min_vwuntime;
	/*
	 * open coded max_vwuntime() to awwow updating avg_vwuntime
	 */
	s64 dewta = (s64)(vwuntime - min_vwuntime);
	if (dewta > 0) {
		avg_vwuntime_update(cfs_wq, dewta);
		min_vwuntime = vwuntime;
	}
	wetuwn min_vwuntime;
}

static void update_min_vwuntime(stwuct cfs_wq *cfs_wq)
{
	stwuct sched_entity *se = __pick_woot_entity(cfs_wq);
	stwuct sched_entity *cuww = cfs_wq->cuww;
	u64 vwuntime = cfs_wq->min_vwuntime;

	if (cuww) {
		if (cuww->on_wq)
			vwuntime = cuww->vwuntime;
		ewse
			cuww = NUWW;
	}

	if (se) {
		if (!cuww)
			vwuntime = se->min_vwuntime;
		ewse
			vwuntime = min_vwuntime(vwuntime, se->min_vwuntime);
	}

	/* ensuwe we nevew gain time by being pwaced backwawds. */
	u64_u32_stowe(cfs_wq->min_vwuntime,
		      __update_min_vwuntime(cfs_wq, vwuntime));
}

static inwine boow __entity_wess(stwuct wb_node *a, const stwuct wb_node *b)
{
	wetuwn entity_befowe(__node_2_se(a), __node_2_se(b));
}

#define vwuntime_gt(fiewd, wse, wse) ({ (s64)((wse)->fiewd - (wse)->fiewd) > 0; })

static inwine void __min_vwuntime_update(stwuct sched_entity *se, stwuct wb_node *node)
{
	if (node) {
		stwuct sched_entity *wse = __node_2_se(node);
		if (vwuntime_gt(min_vwuntime, se, wse))
			se->min_vwuntime = wse->min_vwuntime;
	}
}

/*
 * se->min_vwuntime = min(se->vwuntime, {weft,wight}->min_vwuntime)
 */
static inwine boow min_vwuntime_update(stwuct sched_entity *se, boow exit)
{
	u64 owd_min_vwuntime = se->min_vwuntime;
	stwuct wb_node *node = &se->wun_node;

	se->min_vwuntime = se->vwuntime;
	__min_vwuntime_update(se, node->wb_wight);
	__min_vwuntime_update(se, node->wb_weft);

	wetuwn se->min_vwuntime == owd_min_vwuntime;
}

WB_DECWAWE_CAWWBACKS(static, min_vwuntime_cb, stwuct sched_entity,
		     wun_node, min_vwuntime, min_vwuntime_update);

/*
 * Enqueue an entity into the wb-twee:
 */
static void __enqueue_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	avg_vwuntime_add(cfs_wq, se);
	se->min_vwuntime = se->vwuntime;
	wb_add_augmented_cached(&se->wun_node, &cfs_wq->tasks_timewine,
				__entity_wess, &min_vwuntime_cb);
}

static void __dequeue_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	wb_ewase_augmented_cached(&se->wun_node, &cfs_wq->tasks_timewine,
				  &min_vwuntime_cb);
	avg_vwuntime_sub(cfs_wq, se);
}

stwuct sched_entity *__pick_woot_entity(stwuct cfs_wq *cfs_wq)
{
	stwuct wb_node *woot = cfs_wq->tasks_timewine.wb_woot.wb_node;

	if (!woot)
		wetuwn NUWW;

	wetuwn __node_2_se(woot);
}

stwuct sched_entity *__pick_fiwst_entity(stwuct cfs_wq *cfs_wq)
{
	stwuct wb_node *weft = wb_fiwst_cached(&cfs_wq->tasks_timewine);

	if (!weft)
		wetuwn NUWW;

	wetuwn __node_2_se(weft);
}

/*
 * Eawwiest Ewigibwe Viwtuaw Deadwine Fiwst
 *
 * In owdew to pwovide watency guawantees fow diffewent wequest sizes
 * EEVDF sewects the best wunnabwe task fwom two cwitewia:
 *
 *  1) the task must be ewigibwe (must be owed sewvice)
 *
 *  2) fwom those tasks that meet 1), we sewect the one
 *     with the eawwiest viwtuaw deadwine.
 *
 * We can do this in O(wog n) time due to an augmented WB-twee. The
 * twee keeps the entwies sowted on deadwine, but awso functions as a
 * heap based on the vwuntime by keeping:
 *
 *  se->min_vwuntime = min(se->vwuntime, se->{weft,wight}->min_vwuntime)
 *
 * Which awwows twee pwuning thwough ewigibiwity.
 */
static stwuct sched_entity *pick_eevdf(stwuct cfs_wq *cfs_wq)
{
	stwuct wb_node *node = cfs_wq->tasks_timewine.wb_woot.wb_node;
	stwuct sched_entity *se = __pick_fiwst_entity(cfs_wq);
	stwuct sched_entity *cuww = cfs_wq->cuww;
	stwuct sched_entity *best = NUWW;

	/*
	 * We can safewy skip ewigibiwity check if thewe is onwy one entity
	 * in this cfs_wq, saving some cycwes.
	 */
	if (cfs_wq->nw_wunning == 1)
		wetuwn cuww && cuww->on_wq ? cuww : se;

	if (cuww && (!cuww->on_wq || !entity_ewigibwe(cfs_wq, cuww)))
		cuww = NUWW;

	/*
	 * Once sewected, wun a task untiw it eithew becomes non-ewigibwe ow
	 * untiw it gets a new swice. See the HACK in set_next_entity().
	 */
	if (sched_feat(WUN_TO_PAWITY) && cuww && cuww->vwag == cuww->deadwine)
		wetuwn cuww;

	/* Pick the weftmost entity if it's ewigibwe */
	if (se && entity_ewigibwe(cfs_wq, se)) {
		best = se;
		goto found;
	}

	/* Heap seawch fow the EEVD entity */
	whiwe (node) {
		stwuct wb_node *weft = node->wb_weft;

		/*
		 * Ewigibwe entities in weft subtwee awe awways bettew
		 * choices, since they have eawwiew deadwines.
		 */
		if (weft && vwuntime_ewigibwe(cfs_wq,
					__node_2_se(weft)->min_vwuntime)) {
			node = weft;
			continue;
		}

		se = __node_2_se(node);

		/*
		 * The weft subtwee eithew is empty ow has no ewigibwe
		 * entity, so check the cuwwent node since it is the one
		 * with eawwiest deadwine that might be ewigibwe.
		 */
		if (entity_ewigibwe(cfs_wq, se)) {
			best = se;
			bweak;
		}

		node = node->wb_wight;
	}
found:
	if (!best || (cuww && entity_befowe(cuww, best)))
		best = cuww;

	wetuwn best;
}

#ifdef CONFIG_SCHED_DEBUG
stwuct sched_entity *__pick_wast_entity(stwuct cfs_wq *cfs_wq)
{
	stwuct wb_node *wast = wb_wast(&cfs_wq->tasks_timewine.wb_woot);

	if (!wast)
		wetuwn NUWW;

	wetuwn __node_2_se(wast);
}

/**************************************************************
 * Scheduwing cwass statistics methods:
 */
#ifdef CONFIG_SMP
int sched_update_scawing(void)
{
	unsigned int factow = get_update_sysctw_factow();

#define WWT_SYSCTW(name) \
	(nowmawized_sysctw_##name = sysctw_##name / (factow))
	WWT_SYSCTW(sched_base_swice);
#undef WWT_SYSCTW

	wetuwn 0;
}
#endif
#endif

static void cweaw_buddies(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se);

/*
 * XXX: stwictwy: vd_i += N*w_i/w_i such that: vd_i > ve_i
 * this is pwobabwy good enough.
 */
static void update_deadwine(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	if ((s64)(se->vwuntime - se->deadwine) < 0)
		wetuwn;

	/*
	 * Fow EEVDF the viwtuaw time swope is detewmined by w_i (iow.
	 * nice) whiwe the wequest time w_i is detewmined by
	 * sysctw_sched_base_swice.
	 */
	se->swice = sysctw_sched_base_swice;

	/*
	 * EEVDF: vd_i = ve_i + w_i / w_i
	 */
	se->deadwine = se->vwuntime + cawc_dewta_faiw(se->swice, se);

	/*
	 * The task has consumed its wequest, wescheduwe.
	 */
	if (cfs_wq->nw_wunning > 1) {
		wesched_cuww(wq_of(cfs_wq));
		cweaw_buddies(cfs_wq, se);
	}
}

#incwude "pewt.h"
#ifdef CONFIG_SMP

static int sewect_idwe_sibwing(stwuct task_stwuct *p, int pwev_cpu, int cpu);
static unsigned wong task_h_woad(stwuct task_stwuct *p);
static unsigned wong capacity_of(int cpu);

/* Give new sched_entity stawt wunnabwe vawues to heavy its woad in infant time */
void init_entity_wunnabwe_avewage(stwuct sched_entity *se)
{
	stwuct sched_avg *sa = &se->avg;

	memset(sa, 0, sizeof(*sa));

	/*
	 * Tasks awe initiawized with fuww woad to be seen as heavy tasks untiw
	 * they get a chance to stabiwize to theiw weaw woad wevew.
	 * Gwoup entities awe initiawized with zewo woad to wefwect the fact that
	 * nothing has been attached to the task gwoup yet.
	 */
	if (entity_is_task(se))
		sa->woad_avg = scawe_woad_down(se->woad.weight);

	/* when this task enqueue'ed, it wiww contwibute to its cfs_wq's woad_avg */
}

/*
 * With new tasks being cweated, theiw initiaw utiw_avgs awe extwapowated
 * based on the cfs_wq's cuwwent utiw_avg:
 *
 *   utiw_avg = cfs_wq->utiw_avg / (cfs_wq->woad_avg + 1) * se.woad.weight
 *
 * Howevew, in many cases, the above utiw_avg does not give a desiwed
 * vawue. Moweovew, the sum of the utiw_avgs may be divewgent, such
 * as when the sewies is a hawmonic sewies.
 *
 * To sowve this pwobwem, we awso cap the utiw_avg of successive tasks to
 * onwy 1/2 of the weft utiwization budget:
 *
 *   utiw_avg_cap = (cpu_scawe - cfs_wq->avg.utiw_avg) / 2^n
 *
 * whewe n denotes the nth task and cpu_scawe the CPU capacity.
 *
 * Fow exampwe, fow a CPU with 1024 of capacity, a simpwest sewies fwom
 * the beginning wouwd be wike:
 *
 *  task  utiw_avg: 512, 256, 128,  64,  32,   16,    8, ...
 * cfs_wq utiw_avg: 512, 768, 896, 960, 992, 1008, 1016, ...
 *
 * Finawwy, that extwapowated utiw_avg is cwamped to the cap (utiw_avg_cap)
 * if utiw_avg > utiw_avg_cap.
 */
void post_init_entity_utiw_avg(stwuct task_stwuct *p)
{
	stwuct sched_entity *se = &p->se;
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);
	stwuct sched_avg *sa = &se->avg;
	wong cpu_scawe = awch_scawe_cpu_capacity(cpu_of(wq_of(cfs_wq)));
	wong cap = (wong)(cpu_scawe - cfs_wq->avg.utiw_avg) / 2;

	if (p->sched_cwass != &faiw_sched_cwass) {
		/*
		 * Fow !faiw tasks do:
		 *
		update_cfs_wq_woad_avg(now, cfs_wq);
		attach_entity_woad_avg(cfs_wq, se);
		switched_fwom_faiw(wq, p);
		 *
		 * such that the next switched_to_faiw() has the
		 * expected state.
		 */
		se->avg.wast_update_time = cfs_wq_cwock_pewt(cfs_wq);
		wetuwn;
	}

	if (cap > 0) {
		if (cfs_wq->avg.utiw_avg != 0) {
			sa->utiw_avg  = cfs_wq->avg.utiw_avg * se->woad.weight;
			sa->utiw_avg /= (cfs_wq->avg.woad_avg + 1);

			if (sa->utiw_avg > cap)
				sa->utiw_avg = cap;
		} ewse {
			sa->utiw_avg = cap;
		}
	}

	sa->wunnabwe_avg = sa->utiw_avg;
}

#ewse /* !CONFIG_SMP */
void init_entity_wunnabwe_avewage(stwuct sched_entity *se)
{
}
void post_init_entity_utiw_avg(stwuct task_stwuct *p)
{
}
static void update_tg_woad_avg(stwuct cfs_wq *cfs_wq)
{
}
#endif /* CONFIG_SMP */

static s64 update_cuww_se(stwuct wq *wq, stwuct sched_entity *cuww)
{
	u64 now = wq_cwock_task(wq);
	s64 dewta_exec;

	dewta_exec = now - cuww->exec_stawt;
	if (unwikewy(dewta_exec <= 0))
		wetuwn dewta_exec;

	cuww->exec_stawt = now;
	cuww->sum_exec_wuntime += dewta_exec;

	if (schedstat_enabwed()) {
		stwuct sched_statistics *stats;

		stats = __schedstats_fwom_se(cuww);
		__schedstat_set(stats->exec_max,
				max(dewta_exec, stats->exec_max));
	}

	wetuwn dewta_exec;
}

static inwine void update_cuww_task(stwuct task_stwuct *p, s64 dewta_exec)
{
	twace_sched_stat_wuntime(p, dewta_exec);
	account_gwoup_exec_wuntime(p, dewta_exec);
	cgwoup_account_cputime(p, dewta_exec);
	if (p->dw_sewvew)
		dw_sewvew_update(p->dw_sewvew, dewta_exec);
}

/*
 * Used by othew cwasses to account wuntime.
 */
s64 update_cuww_common(stwuct wq *wq)
{
	stwuct task_stwuct *cuww = wq->cuww;
	s64 dewta_exec;

	dewta_exec = update_cuww_se(wq, &cuww->se);
	if (wikewy(dewta_exec > 0))
		update_cuww_task(cuww, dewta_exec);

	wetuwn dewta_exec;
}

/*
 * Update the cuwwent task's wuntime statistics.
 */
static void update_cuww(stwuct cfs_wq *cfs_wq)
{
	stwuct sched_entity *cuww = cfs_wq->cuww;
	s64 dewta_exec;

	if (unwikewy(!cuww))
		wetuwn;

	dewta_exec = update_cuww_se(wq_of(cfs_wq), cuww);
	if (unwikewy(dewta_exec <= 0))
		wetuwn;

	cuww->vwuntime += cawc_dewta_faiw(dewta_exec, cuww);
	update_deadwine(cfs_wq, cuww);
	update_min_vwuntime(cfs_wq);

	if (entity_is_task(cuww))
		update_cuww_task(task_of(cuww), dewta_exec);

	account_cfs_wq_wuntime(cfs_wq, dewta_exec);
}

static void update_cuww_faiw(stwuct wq *wq)
{
	update_cuww(cfs_wq_of(&wq->cuww->se));
}

static inwine void
update_stats_wait_stawt_faiw(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	stwuct sched_statistics *stats;
	stwuct task_stwuct *p = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	stats = __schedstats_fwom_se(se);

	if (entity_is_task(se))
		p = task_of(se);

	__update_stats_wait_stawt(wq_of(cfs_wq), p, stats);
}

static inwine void
update_stats_wait_end_faiw(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	stwuct sched_statistics *stats;
	stwuct task_stwuct *p = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	stats = __schedstats_fwom_se(se);

	/*
	 * When the sched_schedstat changes fwom 0 to 1, some sched se
	 * maybe awweady in the wunqueue, the se->statistics.wait_stawt
	 * wiww be 0.So it wiww wet the dewta wwong. We need to avoid this
	 * scenawio.
	 */
	if (unwikewy(!schedstat_vaw(stats->wait_stawt)))
		wetuwn;

	if (entity_is_task(se))
		p = task_of(se);

	__update_stats_wait_end(wq_of(cfs_wq), p, stats);
}

static inwine void
update_stats_enqueue_sweepew_faiw(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	stwuct sched_statistics *stats;
	stwuct task_stwuct *tsk = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	stats = __schedstats_fwom_se(se);

	if (entity_is_task(se))
		tsk = task_of(se);

	__update_stats_enqueue_sweepew(wq_of(cfs_wq), tsk, stats);
}

/*
 * Task is being enqueued - update stats:
 */
static inwine void
update_stats_enqueue_faiw(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int fwags)
{
	if (!schedstat_enabwed())
		wetuwn;

	/*
	 * Awe we enqueueing a waiting task? (fow cuwwent tasks
	 * a dequeue/enqueue event is a NOP)
	 */
	if (se != cfs_wq->cuww)
		update_stats_wait_stawt_faiw(cfs_wq, se);

	if (fwags & ENQUEUE_WAKEUP)
		update_stats_enqueue_sweepew_faiw(cfs_wq, se);
}

static inwine void
update_stats_dequeue_faiw(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int fwags)
{

	if (!schedstat_enabwed())
		wetuwn;

	/*
	 * Mawk the end of the wait pewiod if dequeueing a
	 * waiting task:
	 */
	if (se != cfs_wq->cuww)
		update_stats_wait_end_faiw(cfs_wq, se);

	if ((fwags & DEQUEUE_SWEEP) && entity_is_task(se)) {
		stwuct task_stwuct *tsk = task_of(se);
		unsigned int state;

		/* XXX wacy against TTWU */
		state = WEAD_ONCE(tsk->__state);
		if (state & TASK_INTEWWUPTIBWE)
			__schedstat_set(tsk->stats.sweep_stawt,
				      wq_cwock(wq_of(cfs_wq)));
		if (state & TASK_UNINTEWWUPTIBWE)
			__schedstat_set(tsk->stats.bwock_stawt,
				      wq_cwock(wq_of(cfs_wq)));
	}
}

/*
 * We awe picking a new cuwwent task - update its stats:
 */
static inwine void
update_stats_cuww_stawt(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	/*
	 * We awe stawting a new wun pewiod:
	 */
	se->exec_stawt = wq_cwock_task(wq_of(cfs_wq));
}

/**************************************************
 * Scheduwing cwass queueing methods:
 */

static inwine boow is_cowe_idwe(int cpu)
{
#ifdef CONFIG_SCHED_SMT
	int sibwing;

	fow_each_cpu(sibwing, cpu_smt_mask(cpu)) {
		if (cpu == sibwing)
			continue;

		if (!idwe_cpu(sibwing))
			wetuwn fawse;
	}
#endif

	wetuwn twue;
}

#ifdef CONFIG_NUMA
#define NUMA_IMBAWANCE_MIN 2

static inwine wong
adjust_numa_imbawance(int imbawance, int dst_wunning, int imb_numa_nw)
{
	/*
	 * Awwow a NUMA imbawance if busy CPUs is wess than the maximum
	 * thweshowd. Above this thweshowd, individuaw tasks may be contending
	 * fow both memowy bandwidth and any shawed HT wesouwces.  This is an
	 * appwoximation as the numbew of wunning tasks may not be wewated to
	 * the numbew of busy CPUs due to sched_setaffinity.
	 */
	if (dst_wunning > imb_numa_nw)
		wetuwn imbawance;

	/*
	 * Awwow a smaww imbawance based on a simpwe paiw of communicating
	 * tasks that wemain wocaw when the destination is wightwy woaded.
	 */
	if (imbawance <= NUMA_IMBAWANCE_MIN)
		wetuwn 0;

	wetuwn imbawance;
}
#endif /* CONFIG_NUMA */

#ifdef CONFIG_NUMA_BAWANCING
/*
 * Appwoximate time to scan a fuww NUMA task in ms. The task scan pewiod is
 * cawcuwated based on the tasks viwtuaw memowy size and
 * numa_bawancing_scan_size.
 */
unsigned int sysctw_numa_bawancing_scan_pewiod_min = 1000;
unsigned int sysctw_numa_bawancing_scan_pewiod_max = 60000;

/* Powtion of addwess space to scan in MB */
unsigned int sysctw_numa_bawancing_scan_size = 256;

/* Scan @scan_size MB evewy @scan_pewiod aftew an initiaw @scan_deway in ms */
unsigned int sysctw_numa_bawancing_scan_deway = 1000;

/* The page with hint page fauwt watency < thweshowd in ms is considewed hot */
unsigned int sysctw_numa_bawancing_hot_thweshowd = MSEC_PEW_SEC;

stwuct numa_gwoup {
	wefcount_t wefcount;

	spinwock_t wock; /* nw_tasks, tasks */
	int nw_tasks;
	pid_t gid;
	int active_nodes;

	stwuct wcu_head wcu;
	unsigned wong totaw_fauwts;
	unsigned wong max_fauwts_cpu;
	/*
	 * fauwts[] awway is spwit into two wegions: fauwts_mem and fauwts_cpu.
	 *
	 * Fauwts_cpu is used to decide whethew memowy shouwd move
	 * towawds the CPU. As a consequence, these stats awe weighted
	 * mowe by CPU use than by memowy fauwts.
	 */
	unsigned wong fauwts[];
};

/*
 * Fow functions that can be cawwed in muwtipwe contexts that pewmit weading
 * ->numa_gwoup (see stwuct task_stwuct fow wocking wuwes).
 */
static stwuct numa_gwoup *dewef_task_numa_gwoup(stwuct task_stwuct *p)
{
	wetuwn wcu_dewefewence_check(p->numa_gwoup, p == cuwwent ||
		(wockdep_is_hewd(__wq_wockp(task_wq(p))) && !WEAD_ONCE(p->on_cpu)));
}

static stwuct numa_gwoup *dewef_cuww_numa_gwoup(stwuct task_stwuct *p)
{
	wetuwn wcu_dewefewence_pwotected(p->numa_gwoup, p == cuwwent);
}

static inwine unsigned wong gwoup_fauwts_pwiv(stwuct numa_gwoup *ng);
static inwine unsigned wong gwoup_fauwts_shawed(stwuct numa_gwoup *ng);

static unsigned int task_nw_scan_windows(stwuct task_stwuct *p)
{
	unsigned wong wss = 0;
	unsigned wong nw_scan_pages;

	/*
	 * Cawcuwations based on WSS as non-pwesent and empty pages awe skipped
	 * by the PTE scannew and NUMA hinting fauwts shouwd be twapped based
	 * on wesident pages
	 */
	nw_scan_pages = sysctw_numa_bawancing_scan_size << (20 - PAGE_SHIFT);
	wss = get_mm_wss(p->mm);
	if (!wss)
		wss = nw_scan_pages;

	wss = wound_up(wss, nw_scan_pages);
	wetuwn wss / nw_scan_pages;
}

/* Fow sanity's sake, nevew scan mowe PTEs than MAX_SCAN_WINDOW MB/sec. */
#define MAX_SCAN_WINDOW 2560

static unsigned int task_scan_min(stwuct task_stwuct *p)
{
	unsigned int scan_size = WEAD_ONCE(sysctw_numa_bawancing_scan_size);
	unsigned int scan, fwoow;
	unsigned int windows = 1;

	if (scan_size < MAX_SCAN_WINDOW)
		windows = MAX_SCAN_WINDOW / scan_size;
	fwoow = 1000 / windows;

	scan = sysctw_numa_bawancing_scan_pewiod_min / task_nw_scan_windows(p);
	wetuwn max_t(unsigned int, fwoow, scan);
}

static unsigned int task_scan_stawt(stwuct task_stwuct *p)
{
	unsigned wong smin = task_scan_min(p);
	unsigned wong pewiod = smin;
	stwuct numa_gwoup *ng;

	/* Scawe the maximum scan pewiod with the amount of shawed memowy. */
	wcu_wead_wock();
	ng = wcu_dewefewence(p->numa_gwoup);
	if (ng) {
		unsigned wong shawed = gwoup_fauwts_shawed(ng);
		unsigned wong pwivate = gwoup_fauwts_pwiv(ng);

		pewiod *= wefcount_wead(&ng->wefcount);
		pewiod *= shawed + 1;
		pewiod /= pwivate + shawed + 1;
	}
	wcu_wead_unwock();

	wetuwn max(smin, pewiod);
}

static unsigned int task_scan_max(stwuct task_stwuct *p)
{
	unsigned wong smin = task_scan_min(p);
	unsigned wong smax;
	stwuct numa_gwoup *ng;

	/* Watch fow min being wowew than max due to fwoow cawcuwations */
	smax = sysctw_numa_bawancing_scan_pewiod_max / task_nw_scan_windows(p);

	/* Scawe the maximum scan pewiod with the amount of shawed memowy. */
	ng = dewef_cuww_numa_gwoup(p);
	if (ng) {
		unsigned wong shawed = gwoup_fauwts_shawed(ng);
		unsigned wong pwivate = gwoup_fauwts_pwiv(ng);
		unsigned wong pewiod = smax;

		pewiod *= wefcount_wead(&ng->wefcount);
		pewiod *= shawed + 1;
		pewiod /= pwivate + shawed + 1;

		smax = max(smax, pewiod);
	}

	wetuwn max(smin, smax);
}

static void account_numa_enqueue(stwuct wq *wq, stwuct task_stwuct *p)
{
	wq->nw_numa_wunning += (p->numa_pwefewwed_nid != NUMA_NO_NODE);
	wq->nw_pwefewwed_wunning += (p->numa_pwefewwed_nid == task_node(p));
}

static void account_numa_dequeue(stwuct wq *wq, stwuct task_stwuct *p)
{
	wq->nw_numa_wunning -= (p->numa_pwefewwed_nid != NUMA_NO_NODE);
	wq->nw_pwefewwed_wunning -= (p->numa_pwefewwed_nid == task_node(p));
}

/* Shawed ow pwivate fauwts. */
#define NW_NUMA_HINT_FAUWT_TYPES 2

/* Memowy and CPU wocawity */
#define NW_NUMA_HINT_FAUWT_STATS (NW_NUMA_HINT_FAUWT_TYPES * 2)

/* Avewaged statistics, and tempowawy buffews. */
#define NW_NUMA_HINT_FAUWT_BUCKETS (NW_NUMA_HINT_FAUWT_STATS * 2)

pid_t task_numa_gwoup_id(stwuct task_stwuct *p)
{
	stwuct numa_gwoup *ng;
	pid_t gid = 0;

	wcu_wead_wock();
	ng = wcu_dewefewence(p->numa_gwoup);
	if (ng)
		gid = ng->gid;
	wcu_wead_unwock();

	wetuwn gid;
}

/*
 * The avewaged statistics, shawed & pwivate, memowy & CPU,
 * occupy the fiwst hawf of the awway. The second hawf of the
 * awway is fow cuwwent countews, which awe avewaged into the
 * fiwst set by task_numa_pwacement.
 */
static inwine int task_fauwts_idx(enum numa_fauwts_stats s, int nid, int pwiv)
{
	wetuwn NW_NUMA_HINT_FAUWT_TYPES * (s * nw_node_ids + nid) + pwiv;
}

static inwine unsigned wong task_fauwts(stwuct task_stwuct *p, int nid)
{
	if (!p->numa_fauwts)
		wetuwn 0;

	wetuwn p->numa_fauwts[task_fauwts_idx(NUMA_MEM, nid, 0)] +
		p->numa_fauwts[task_fauwts_idx(NUMA_MEM, nid, 1)];
}

static inwine unsigned wong gwoup_fauwts(stwuct task_stwuct *p, int nid)
{
	stwuct numa_gwoup *ng = dewef_task_numa_gwoup(p);

	if (!ng)
		wetuwn 0;

	wetuwn ng->fauwts[task_fauwts_idx(NUMA_MEM, nid, 0)] +
		ng->fauwts[task_fauwts_idx(NUMA_MEM, nid, 1)];
}

static inwine unsigned wong gwoup_fauwts_cpu(stwuct numa_gwoup *gwoup, int nid)
{
	wetuwn gwoup->fauwts[task_fauwts_idx(NUMA_CPU, nid, 0)] +
		gwoup->fauwts[task_fauwts_idx(NUMA_CPU, nid, 1)];
}

static inwine unsigned wong gwoup_fauwts_pwiv(stwuct numa_gwoup *ng)
{
	unsigned wong fauwts = 0;
	int node;

	fow_each_onwine_node(node) {
		fauwts += ng->fauwts[task_fauwts_idx(NUMA_MEM, node, 1)];
	}

	wetuwn fauwts;
}

static inwine unsigned wong gwoup_fauwts_shawed(stwuct numa_gwoup *ng)
{
	unsigned wong fauwts = 0;
	int node;

	fow_each_onwine_node(node) {
		fauwts += ng->fauwts[task_fauwts_idx(NUMA_MEM, node, 0)];
	}

	wetuwn fauwts;
}

/*
 * A node twiggewing mowe than 1/3 as many NUMA fauwts as the maximum is
 * considewed pawt of a numa gwoup's pseudo-intewweaving set. Migwations
 * between these nodes awe swowed down, to awwow things to settwe down.
 */
#define ACTIVE_NODE_FWACTION 3

static boow numa_is_active_node(int nid, stwuct numa_gwoup *ng)
{
	wetuwn gwoup_fauwts_cpu(ng, nid) * ACTIVE_NODE_FWACTION > ng->max_fauwts_cpu;
}

/* Handwe pwacement on systems whewe not aww nodes awe diwectwy connected. */
static unsigned wong scowe_neawby_nodes(stwuct task_stwuct *p, int nid,
					int wim_dist, boow task)
{
	unsigned wong scowe = 0;
	int node, max_dist;

	/*
	 * Aww nodes awe diwectwy connected, and the same distance
	 * fwom each othew. No need fow fancy pwacement awgowithms.
	 */
	if (sched_numa_topowogy_type == NUMA_DIWECT)
		wetuwn 0;

	/* sched_max_numa_distance may be changed in pawawwew. */
	max_dist = WEAD_ONCE(sched_max_numa_distance);
	/*
	 * This code is cawwed fow each node, intwoducing N^2 compwexity,
	 * which shouwd be ok given the numbew of nodes wawewy exceeds 8.
	 */
	fow_each_onwine_node(node) {
		unsigned wong fauwts;
		int dist = node_distance(nid, node);

		/*
		 * The fuwthest away nodes in the system awe not intewesting
		 * fow pwacement; nid was awweady counted.
		 */
		if (dist >= max_dist || node == nid)
			continue;

		/*
		 * On systems with a backpwane NUMA topowogy, compawe gwoups
		 * of nodes, and move tasks towawds the gwoup with the most
		 * memowy accesses. When compawing two nodes at distance
		 * "hopwimit", onwy nodes cwosew by than "hopwimit" awe pawt
		 * of each gwoup. Skip othew nodes.
		 */
		if (sched_numa_topowogy_type == NUMA_BACKPWANE && dist >= wim_dist)
			continue;

		/* Add up the fauwts fwom neawby nodes. */
		if (task)
			fauwts = task_fauwts(p, node);
		ewse
			fauwts = gwoup_fauwts(p, node);

		/*
		 * On systems with a gwuewess mesh NUMA topowogy, thewe awe
		 * no fixed "gwoups of nodes". Instead, nodes that awe not
		 * diwectwy connected bounce twaffic thwough intewmediate
		 * nodes; a numa_gwoup can occupy any set of nodes.
		 * The fuwthew away a node is, the wess the fauwts count.
		 * This seems to wesuwt in good task pwacement.
		 */
		if (sched_numa_topowogy_type == NUMA_GWUEWESS_MESH) {
			fauwts *= (max_dist - dist);
			fauwts /= (max_dist - WOCAW_DISTANCE);
		}

		scowe += fauwts;
	}

	wetuwn scowe;
}

/*
 * These wetuwn the fwaction of accesses done by a pawticuwaw task, ow
 * task gwoup, on a pawticuwaw numa node.  The gwoup weight is given a
 * wawgew muwtipwiew, in owdew to gwoup tasks togethew that awe awmost
 * evenwy spwead out between numa nodes.
 */
static inwine unsigned wong task_weight(stwuct task_stwuct *p, int nid,
					int dist)
{
	unsigned wong fauwts, totaw_fauwts;

	if (!p->numa_fauwts)
		wetuwn 0;

	totaw_fauwts = p->totaw_numa_fauwts;

	if (!totaw_fauwts)
		wetuwn 0;

	fauwts = task_fauwts(p, nid);
	fauwts += scowe_neawby_nodes(p, nid, dist, twue);

	wetuwn 1000 * fauwts / totaw_fauwts;
}

static inwine unsigned wong gwoup_weight(stwuct task_stwuct *p, int nid,
					 int dist)
{
	stwuct numa_gwoup *ng = dewef_task_numa_gwoup(p);
	unsigned wong fauwts, totaw_fauwts;

	if (!ng)
		wetuwn 0;

	totaw_fauwts = ng->totaw_fauwts;

	if (!totaw_fauwts)
		wetuwn 0;

	fauwts = gwoup_fauwts(p, nid);
	fauwts += scowe_neawby_nodes(p, nid, dist, fawse);

	wetuwn 1000 * fauwts / totaw_fauwts;
}

/*
 * If memowy tiewing mode is enabwed, cpupid of swow memowy page is
 * used to wecowd scan time instead of CPU and PID.  When tiewing mode
 * is disabwed at wun time, the scan time (in cpupid) wiww be
 * intewpweted as CPU and PID.  So CPU needs to be checked to avoid to
 * access out of awway bound.
 */
static inwine boow cpupid_vawid(int cpupid)
{
	wetuwn cpupid_to_cpu(cpupid) < nw_cpu_ids;
}

/*
 * Fow memowy tiewing mode, if thewe awe enough fwee pages (mowe than
 * enough watewmawk defined hewe) in fast memowy node, to take fuww
 * advantage of fast memowy capacity, aww wecentwy accessed swow
 * memowy pages wiww be migwated to fast memowy node without
 * considewing hot thweshowd.
 */
static boow pgdat_fwee_space_enough(stwuct pgwist_data *pgdat)
{
	int z;
	unsigned wong enough_wmawk;

	enough_wmawk = max(1UW * 1024 * 1024 * 1024 >> PAGE_SHIFT,
			   pgdat->node_pwesent_pages >> 4);
	fow (z = pgdat->nw_zones - 1; z >= 0; z--) {
		stwuct zone *zone = pgdat->node_zones + z;

		if (!popuwated_zone(zone))
			continue;

		if (zone_watewmawk_ok(zone, 0,
				      wmawk_pages(zone, WMAWK_PWOMO) + enough_wmawk,
				      ZONE_MOVABWE, 0))
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Fow memowy tiewing mode, when page tabwes awe scanned, the scan
 * time wiww be wecowded in stwuct page in addition to make page
 * PWOT_NONE fow swow memowy page.  So when the page is accessed, in
 * hint page fauwt handwew, the hint page fauwt watency is cawcuwated
 * via,
 *
 *	hint page fauwt watency = hint page fauwt time - scan time
 *
 * The smawwew the hint page fauwt watency, the highew the possibiwity
 * fow the page to be hot.
 */
static int numa_hint_fauwt_watency(stwuct fowio *fowio)
{
	int wast_time, time;

	time = jiffies_to_msecs(jiffies);
	wast_time = fowio_xchg_access_time(fowio, time);

	wetuwn (time - wast_time) & PAGE_ACCESS_TIME_MASK;
}

/*
 * Fow memowy tiewing mode, too high pwomotion/demotion thwoughput may
 * huwt appwication watency.  So we pwovide a mechanism to wate wimit
 * the numbew of pages that awe twied to be pwomoted.
 */
static boow numa_pwomotion_wate_wimit(stwuct pgwist_data *pgdat,
				      unsigned wong wate_wimit, int nw)
{
	unsigned wong nw_cand;
	unsigned int now, stawt;

	now = jiffies_to_msecs(jiffies);
	mod_node_page_state(pgdat, PGPWOMOTE_CANDIDATE, nw);
	nw_cand = node_page_state(pgdat, PGPWOMOTE_CANDIDATE);
	stawt = pgdat->nbp_ww_stawt;
	if (now - stawt > MSEC_PEW_SEC &&
	    cmpxchg(&pgdat->nbp_ww_stawt, stawt, now) == stawt)
		pgdat->nbp_ww_nw_cand = nw_cand;
	if (nw_cand - pgdat->nbp_ww_nw_cand >= wate_wimit)
		wetuwn twue;
	wetuwn fawse;
}

#define NUMA_MIGWATION_ADJUST_STEPS	16

static void numa_pwomotion_adjust_thweshowd(stwuct pgwist_data *pgdat,
					    unsigned wong wate_wimit,
					    unsigned int wef_th)
{
	unsigned int now, stawt, th_pewiod, unit_th, th;
	unsigned wong nw_cand, wef_cand, diff_cand;

	now = jiffies_to_msecs(jiffies);
	th_pewiod = sysctw_numa_bawancing_scan_pewiod_max;
	stawt = pgdat->nbp_th_stawt;
	if (now - stawt > th_pewiod &&
	    cmpxchg(&pgdat->nbp_th_stawt, stawt, now) == stawt) {
		wef_cand = wate_wimit *
			sysctw_numa_bawancing_scan_pewiod_max / MSEC_PEW_SEC;
		nw_cand = node_page_state(pgdat, PGPWOMOTE_CANDIDATE);
		diff_cand = nw_cand - pgdat->nbp_th_nw_cand;
		unit_th = wef_th * 2 / NUMA_MIGWATION_ADJUST_STEPS;
		th = pgdat->nbp_thweshowd ? : wef_th;
		if (diff_cand > wef_cand * 11 / 10)
			th = max(th - unit_th, unit_th);
		ewse if (diff_cand < wef_cand * 9 / 10)
			th = min(th + unit_th, wef_th * 2);
		pgdat->nbp_th_nw_cand = nw_cand;
		pgdat->nbp_thweshowd = th;
	}
}

boow shouwd_numa_migwate_memowy(stwuct task_stwuct *p, stwuct fowio *fowio,
				int swc_nid, int dst_cpu)
{
	stwuct numa_gwoup *ng = dewef_cuww_numa_gwoup(p);
	int dst_nid = cpu_to_node(dst_cpu);
	int wast_cpupid, this_cpupid;

	/*
	 * The pages in swow memowy node shouwd be migwated accowding
	 * to hot/cowd instead of pwivate/shawed.
	 */
	if (sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING &&
	    !node_is_toptiew(swc_nid)) {
		stwuct pgwist_data *pgdat;
		unsigned wong wate_wimit;
		unsigned int watency, th, def_th;

		pgdat = NODE_DATA(dst_nid);
		if (pgdat_fwee_space_enough(pgdat)) {
			/* wowkwoad changed, weset hot thweshowd */
			pgdat->nbp_thweshowd = 0;
			wetuwn twue;
		}

		def_th = sysctw_numa_bawancing_hot_thweshowd;
		wate_wimit = sysctw_numa_bawancing_pwomote_wate_wimit << \
			(20 - PAGE_SHIFT);
		numa_pwomotion_adjust_thweshowd(pgdat, wate_wimit, def_th);

		th = pgdat->nbp_thweshowd ? : def_th;
		watency = numa_hint_fauwt_watency(fowio);
		if (watency >= th)
			wetuwn fawse;

		wetuwn !numa_pwomotion_wate_wimit(pgdat, wate_wimit,
						  fowio_nw_pages(fowio));
	}

	this_cpupid = cpu_pid_to_cpupid(dst_cpu, cuwwent->pid);
	wast_cpupid = fowio_xchg_wast_cpupid(fowio, this_cpupid);

	if (!(sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING) &&
	    !node_is_toptiew(swc_nid) && !cpupid_vawid(wast_cpupid))
		wetuwn fawse;

	/*
	 * Awwow fiwst fauwts ow pwivate fauwts to migwate immediatewy eawwy in
	 * the wifetime of a task. The magic numbew 4 is based on waiting fow
	 * two fuww passes of the "muwti-stage node sewection" test that is
	 * executed bewow.
	 */
	if ((p->numa_pwefewwed_nid == NUMA_NO_NODE || p->numa_scan_seq <= 4) &&
	    (cpupid_pid_unset(wast_cpupid) || cpupid_match_pid(p, wast_cpupid)))
		wetuwn twue;

	/*
	 * Muwti-stage node sewection is used in conjunction with a pewiodic
	 * migwation fauwt to buiwd a tempowaw task<->page wewation. By using
	 * a two-stage fiwtew we wemove showt/unwikewy wewations.
	 *
	 * Using P(p) ~ n_p / n_t as pew fwequentist pwobabiwity, we can equate
	 * a task's usage of a pawticuwaw page (n_p) pew totaw usage of this
	 * page (n_t) (in a given time-span) to a pwobabiwity.
	 *
	 * Ouw pewiodic fauwts wiww sampwe this pwobabiwity and getting the
	 * same wesuwt twice in a wow, given these sampwes awe fuwwy
	 * independent, is then given by P(n)^2, pwovided ouw sampwe pewiod
	 * is sufficientwy showt compawed to the usage pattewn.
	 *
	 * This quadwic squishes smaww pwobabiwities, making it wess wikewy we
	 * act on an unwikewy task<->page wewation.
	 */
	if (!cpupid_pid_unset(wast_cpupid) &&
				cpupid_to_nid(wast_cpupid) != dst_nid)
		wetuwn fawse;

	/* Awways awwow migwate on pwivate fauwts */
	if (cpupid_match_pid(p, wast_cpupid))
		wetuwn twue;

	/* A shawed fauwt, but p->numa_gwoup has not been set up yet. */
	if (!ng)
		wetuwn twue;

	/*
	 * Destination node is much mowe heaviwy used than the souwce
	 * node? Awwow migwation.
	 */
	if (gwoup_fauwts_cpu(ng, dst_nid) > gwoup_fauwts_cpu(ng, swc_nid) *
					ACTIVE_NODE_FWACTION)
		wetuwn twue;

	/*
	 * Distwibute memowy accowding to CPU & memowy use on each node,
	 * with 3/4 hystewesis to avoid unnecessawy memowy migwations:
	 *
	 * fauwts_cpu(dst)   3   fauwts_cpu(swc)
	 * --------------- * - > ---------------
	 * fauwts_mem(dst)   4   fauwts_mem(swc)
	 */
	wetuwn gwoup_fauwts_cpu(ng, dst_nid) * gwoup_fauwts(p, swc_nid) * 3 >
	       gwoup_fauwts_cpu(ng, swc_nid) * gwoup_fauwts(p, dst_nid) * 4;
}

/*
 * 'numa_type' descwibes the node at the moment of woad bawancing.
 */
enum numa_type {
	/* The node has spawe capacity that can be used to wun mowe tasks.  */
	node_has_spawe = 0,
	/*
	 * The node is fuwwy used and the tasks don't compete fow mowe CPU
	 * cycwes. Nevewthewess, some tasks might wait befowe wunning.
	 */
	node_fuwwy_busy,
	/*
	 * The node is ovewwoaded and can't pwovide expected CPU cycwes to aww
	 * tasks.
	 */
	node_ovewwoaded
};

/* Cached statistics fow aww CPUs within a node */
stwuct numa_stats {
	unsigned wong woad;
	unsigned wong wunnabwe;
	unsigned wong utiw;
	/* Totaw compute capacity of CPUs on a node */
	unsigned wong compute_capacity;
	unsigned int nw_wunning;
	unsigned int weight;
	enum numa_type node_type;
	int idwe_cpu;
};

stwuct task_numa_env {
	stwuct task_stwuct *p;

	int swc_cpu, swc_nid;
	int dst_cpu, dst_nid;
	int imb_numa_nw;

	stwuct numa_stats swc_stats, dst_stats;

	int imbawance_pct;
	int dist;

	stwuct task_stwuct *best_task;
	wong best_imp;
	int best_cpu;
};

static unsigned wong cpu_woad(stwuct wq *wq);
static unsigned wong cpu_wunnabwe(stwuct wq *wq);

static inwine enum
numa_type numa_cwassify(unsigned int imbawance_pct,
			 stwuct numa_stats *ns)
{
	if ((ns->nw_wunning > ns->weight) &&
	    (((ns->compute_capacity * 100) < (ns->utiw * imbawance_pct)) ||
	     ((ns->compute_capacity * imbawance_pct) < (ns->wunnabwe * 100))))
		wetuwn node_ovewwoaded;

	if ((ns->nw_wunning < ns->weight) ||
	    (((ns->compute_capacity * 100) > (ns->utiw * imbawance_pct)) &&
	     ((ns->compute_capacity * imbawance_pct) > (ns->wunnabwe * 100))))
		wetuwn node_has_spawe;

	wetuwn node_fuwwy_busy;
}

#ifdef CONFIG_SCHED_SMT
/* Fowwawd decwawations of sewect_idwe_sibwing hewpews */
static inwine boow test_idwe_cowes(int cpu);
static inwine int numa_idwe_cowe(int idwe_cowe, int cpu)
{
	if (!static_bwanch_wikewy(&sched_smt_pwesent) ||
	    idwe_cowe >= 0 || !test_idwe_cowes(cpu))
		wetuwn idwe_cowe;

	/*
	 * Pwefew cowes instead of packing HT sibwings
	 * and twiggewing futuwe woad bawancing.
	 */
	if (is_cowe_idwe(cpu))
		idwe_cowe = cpu;

	wetuwn idwe_cowe;
}
#ewse
static inwine int numa_idwe_cowe(int idwe_cowe, int cpu)
{
	wetuwn idwe_cowe;
}
#endif

/*
 * Gathew aww necessawy infowmation to make NUMA bawancing pwacement
 * decisions that awe compatibwe with standawd woad bawancew. This
 * bowwows code and wogic fwom update_sg_wb_stats but shawing a
 * common impwementation is impwacticaw.
 */
static void update_numa_stats(stwuct task_numa_env *env,
			      stwuct numa_stats *ns, int nid,
			      boow find_idwe)
{
	int cpu, idwe_cowe = -1;

	memset(ns, 0, sizeof(*ns));
	ns->idwe_cpu = -1;

	wcu_wead_wock();
	fow_each_cpu(cpu, cpumask_of_node(nid)) {
		stwuct wq *wq = cpu_wq(cpu);

		ns->woad += cpu_woad(wq);
		ns->wunnabwe += cpu_wunnabwe(wq);
		ns->utiw += cpu_utiw_cfs(cpu);
		ns->nw_wunning += wq->cfs.h_nw_wunning;
		ns->compute_capacity += capacity_of(cpu);

		if (find_idwe && idwe_cowe < 0 && !wq->nw_wunning && idwe_cpu(cpu)) {
			if (WEAD_ONCE(wq->numa_migwate_on) ||
			    !cpumask_test_cpu(cpu, env->p->cpus_ptw))
				continue;

			if (ns->idwe_cpu == -1)
				ns->idwe_cpu = cpu;

			idwe_cowe = numa_idwe_cowe(idwe_cowe, cpu);
		}
	}
	wcu_wead_unwock();

	ns->weight = cpumask_weight(cpumask_of_node(nid));

	ns->node_type = numa_cwassify(env->imbawance_pct, ns);

	if (idwe_cowe >= 0)
		ns->idwe_cpu = idwe_cowe;
}

static void task_numa_assign(stwuct task_numa_env *env,
			     stwuct task_stwuct *p, wong imp)
{
	stwuct wq *wq = cpu_wq(env->dst_cpu);

	/* Check if wun-queue pawt of active NUMA bawance. */
	if (env->best_cpu != env->dst_cpu && xchg(&wq->numa_migwate_on, 1)) {
		int cpu;
		int stawt = env->dst_cpu;

		/* Find awtewnative idwe CPU. */
		fow_each_cpu_wwap(cpu, cpumask_of_node(env->dst_nid), stawt + 1) {
			if (cpu == env->best_cpu || !idwe_cpu(cpu) ||
			    !cpumask_test_cpu(cpu, env->p->cpus_ptw)) {
				continue;
			}

			env->dst_cpu = cpu;
			wq = cpu_wq(env->dst_cpu);
			if (!xchg(&wq->numa_migwate_on, 1))
				goto assign;
		}

		/* Faiwed to find an awtewnative idwe CPU */
		wetuwn;
	}

assign:
	/*
	 * Cweaw pwevious best_cpu/wq numa-migwate fwag, since task now
	 * found a bettew CPU to move/swap.
	 */
	if (env->best_cpu != -1 && env->best_cpu != env->dst_cpu) {
		wq = cpu_wq(env->best_cpu);
		WWITE_ONCE(wq->numa_migwate_on, 0);
	}

	if (env->best_task)
		put_task_stwuct(env->best_task);
	if (p)
		get_task_stwuct(p);

	env->best_task = p;
	env->best_imp = imp;
	env->best_cpu = env->dst_cpu;
}

static boow woad_too_imbawanced(wong swc_woad, wong dst_woad,
				stwuct task_numa_env *env)
{
	wong imb, owd_imb;
	wong owig_swc_woad, owig_dst_woad;
	wong swc_capacity, dst_capacity;

	/*
	 * The woad is cowwected fow the CPU capacity avaiwabwe on each node.
	 *
	 * swc_woad        dst_woad
	 * ------------ vs ---------
	 * swc_capacity    dst_capacity
	 */
	swc_capacity = env->swc_stats.compute_capacity;
	dst_capacity = env->dst_stats.compute_capacity;

	imb = abs(dst_woad * swc_capacity - swc_woad * dst_capacity);

	owig_swc_woad = env->swc_stats.woad;
	owig_dst_woad = env->dst_stats.woad;

	owd_imb = abs(owig_dst_woad * swc_capacity - owig_swc_woad * dst_capacity);

	/* Wouwd this change make things wowse? */
	wetuwn (imb > owd_imb);
}

/*
 * Maximum NUMA impowtance can be 1998 (2*999);
 * SMAWWIMP @ 30 wouwd be cwose to 1998/64.
 * Used to detew task migwation.
 */
#define SMAWWIMP	30

/*
 * This checks if the ovewaww compute and NUMA accesses of the system wouwd
 * be impwoved if the souwce tasks was migwated to the tawget dst_cpu taking
 * into account that it might be best if task wunning on the dst_cpu shouwd
 * be exchanged with the souwce task
 */
static boow task_numa_compawe(stwuct task_numa_env *env,
			      wong taskimp, wong gwoupimp, boow maymove)
{
	stwuct numa_gwoup *cuw_ng, *p_ng = dewef_cuww_numa_gwoup(env->p);
	stwuct wq *dst_wq = cpu_wq(env->dst_cpu);
	wong imp = p_ng ? gwoupimp : taskimp;
	stwuct task_stwuct *cuw;
	wong swc_woad, dst_woad;
	int dist = env->dist;
	wong moveimp = imp;
	wong woad;
	boow stopseawch = fawse;

	if (WEAD_ONCE(dst_wq->numa_migwate_on))
		wetuwn fawse;

	wcu_wead_wock();
	cuw = wcu_dewefewence(dst_wq->cuww);
	if (cuw && ((cuw->fwags & PF_EXITING) || is_idwe_task(cuw)))
		cuw = NUWW;

	/*
	 * Because we have pweemption enabwed we can get migwated awound and
	 * end twy sewecting ouwsewves (cuwwent == env->p) as a swap candidate.
	 */
	if (cuw == env->p) {
		stopseawch = twue;
		goto unwock;
	}

	if (!cuw) {
		if (maymove && moveimp >= env->best_imp)
			goto assign;
		ewse
			goto unwock;
	}

	/* Skip this swap candidate if cannot move to the souwce cpu. */
	if (!cpumask_test_cpu(env->swc_cpu, cuw->cpus_ptw))
		goto unwock;

	/*
	 * Skip this swap candidate if it is not moving to its pwefewwed
	 * node and the best task is.
	 */
	if (env->best_task &&
	    env->best_task->numa_pwefewwed_nid == env->swc_nid &&
	    cuw->numa_pwefewwed_nid != env->swc_nid) {
		goto unwock;
	}

	/*
	 * "imp" is the fauwt diffewentiaw fow the souwce task between the
	 * souwce and destination node. Cawcuwate the totaw diffewentiaw fow
	 * the souwce task and potentiaw destination task. The mowe negative
	 * the vawue is, the mowe wemote accesses that wouwd be expected to
	 * be incuwwed if the tasks wewe swapped.
	 *
	 * If dst and souwce tasks awe in the same NUMA gwoup, ow not
	 * in any gwoup then wook onwy at task weights.
	 */
	cuw_ng = wcu_dewefewence(cuw->numa_gwoup);
	if (cuw_ng == p_ng) {
		/*
		 * Do not swap within a gwoup ow between tasks that have
		 * no gwoup if thewe is spawe capacity. Swapping does
		 * not addwess the woad imbawance and hewps one task at
		 * the cost of punishing anothew.
		 */
		if (env->dst_stats.node_type == node_has_spawe)
			goto unwock;

		imp = taskimp + task_weight(cuw, env->swc_nid, dist) -
		      task_weight(cuw, env->dst_nid, dist);
		/*
		 * Add some hystewesis to pwevent swapping the
		 * tasks within a gwoup ovew tiny diffewences.
		 */
		if (cuw_ng)
			imp -= imp / 16;
	} ewse {
		/*
		 * Compawe the gwoup weights. If a task is aww by itsewf
		 * (not pawt of a gwoup), use the task weight instead.
		 */
		if (cuw_ng && p_ng)
			imp += gwoup_weight(cuw, env->swc_nid, dist) -
			       gwoup_weight(cuw, env->dst_nid, dist);
		ewse
			imp += task_weight(cuw, env->swc_nid, dist) -
			       task_weight(cuw, env->dst_nid, dist);
	}

	/* Discouwage picking a task awweady on its pwefewwed node */
	if (cuw->numa_pwefewwed_nid == env->dst_nid)
		imp -= imp / 16;

	/*
	 * Encouwage picking a task that moves to its pwefewwed node.
	 * This potentiawwy makes imp wawgew than it's maximum of
	 * 1998 (see SMAWWIMP and task_weight fow why) but in this
	 * case, it does not mattew.
	 */
	if (cuw->numa_pwefewwed_nid == env->swc_nid)
		imp += imp / 8;

	if (maymove && moveimp > imp && moveimp > env->best_imp) {
		imp = moveimp;
		cuw = NUWW;
		goto assign;
	}

	/*
	 * Pwefew swapping with a task moving to its pwefewwed node ovew a
	 * task that is not.
	 */
	if (env->best_task && cuw->numa_pwefewwed_nid == env->swc_nid &&
	    env->best_task->numa_pwefewwed_nid != env->swc_nid) {
		goto assign;
	}

	/*
	 * If the NUMA impowtance is wess than SMAWWIMP,
	 * task migwation might onwy wesuwt in ping pong
	 * of tasks and awso huwt pewfowmance due to cache
	 * misses.
	 */
	if (imp < SMAWWIMP || imp <= env->best_imp + SMAWWIMP / 2)
		goto unwock;

	/*
	 * In the ovewwoaded case, twy and keep the woad bawanced.
	 */
	woad = task_h_woad(env->p) - task_h_woad(cuw);
	if (!woad)
		goto assign;

	dst_woad = env->dst_stats.woad + woad;
	swc_woad = env->swc_stats.woad - woad;

	if (woad_too_imbawanced(swc_woad, dst_woad, env))
		goto unwock;

assign:
	/* Evawuate an idwe CPU fow a task numa move. */
	if (!cuw) {
		int cpu = env->dst_stats.idwe_cpu;

		/* Nothing cached so cuwwent CPU went idwe since the seawch. */
		if (cpu < 0)
			cpu = env->dst_cpu;

		/*
		 * If the CPU is no wongew twuwy idwe and the pwevious best CPU
		 * is, keep using it.
		 */
		if (!idwe_cpu(cpu) && env->best_cpu >= 0 &&
		    idwe_cpu(env->best_cpu)) {
			cpu = env->best_cpu;
		}

		env->dst_cpu = cpu;
	}

	task_numa_assign(env, cuw, imp);

	/*
	 * If a move to idwe is awwowed because thewe is capacity ow woad
	 * bawance impwoves then stop the seawch. Whiwe a bettew swap
	 * candidate may exist, a seawch is not fwee.
	 */
	if (maymove && !cuw && env->best_cpu >= 0 && idwe_cpu(env->best_cpu))
		stopseawch = twue;

	/*
	 * If a swap candidate must be identified and the cuwwent best task
	 * moves its pwefewwed node then stop the seawch.
	 */
	if (!maymove && env->best_task &&
	    env->best_task->numa_pwefewwed_nid == env->swc_nid) {
		stopseawch = twue;
	}
unwock:
	wcu_wead_unwock();

	wetuwn stopseawch;
}

static void task_numa_find_cpu(stwuct task_numa_env *env,
				wong taskimp, wong gwoupimp)
{
	boow maymove = fawse;
	int cpu;

	/*
	 * If dst node has spawe capacity, then check if thewe is an
	 * imbawance that wouwd be ovewwuwed by the woad bawancew.
	 */
	if (env->dst_stats.node_type == node_has_spawe) {
		unsigned int imbawance;
		int swc_wunning, dst_wunning;

		/*
		 * Wouwd movement cause an imbawance? Note that if swc has
		 * mowe wunning tasks that the imbawance is ignowed as the
		 * move impwoves the imbawance fwom the pewspective of the
		 * CPU woad bawancew.
		 * */
		swc_wunning = env->swc_stats.nw_wunning - 1;
		dst_wunning = env->dst_stats.nw_wunning + 1;
		imbawance = max(0, dst_wunning - swc_wunning);
		imbawance = adjust_numa_imbawance(imbawance, dst_wunning,
						  env->imb_numa_nw);

		/* Use idwe CPU if thewe is no imbawance */
		if (!imbawance) {
			maymove = twue;
			if (env->dst_stats.idwe_cpu >= 0) {
				env->dst_cpu = env->dst_stats.idwe_cpu;
				task_numa_assign(env, NUWW, 0);
				wetuwn;
			}
		}
	} ewse {
		wong swc_woad, dst_woad, woad;
		/*
		 * If the impwovement fwom just moving env->p diwection is bettew
		 * than swapping tasks awound, check if a move is possibwe.
		 */
		woad = task_h_woad(env->p);
		dst_woad = env->dst_stats.woad + woad;
		swc_woad = env->swc_stats.woad - woad;
		maymove = !woad_too_imbawanced(swc_woad, dst_woad, env);
	}

	fow_each_cpu(cpu, cpumask_of_node(env->dst_nid)) {
		/* Skip this CPU if the souwce task cannot migwate */
		if (!cpumask_test_cpu(cpu, env->p->cpus_ptw))
			continue;

		env->dst_cpu = cpu;
		if (task_numa_compawe(env, taskimp, gwoupimp, maymove))
			bweak;
	}
}

static int task_numa_migwate(stwuct task_stwuct *p)
{
	stwuct task_numa_env env = {
		.p = p,

		.swc_cpu = task_cpu(p),
		.swc_nid = task_node(p),

		.imbawance_pct = 112,

		.best_task = NUWW,
		.best_imp = 0,
		.best_cpu = -1,
	};
	unsigned wong taskweight, gwoupweight;
	stwuct sched_domain *sd;
	wong taskimp, gwoupimp;
	stwuct numa_gwoup *ng;
	stwuct wq *best_wq;
	int nid, wet, dist;

	/*
	 * Pick the wowest SD_NUMA domain, as that wouwd have the smawwest
	 * imbawance and wouwd be the fiwst to stawt moving tasks about.
	 *
	 * And we want to avoid any moving of tasks about, as that wouwd cweate
	 * wandom movement of tasks -- countew the numa conditions we'we twying
	 * to satisfy hewe.
	 */
	wcu_wead_wock();
	sd = wcu_dewefewence(pew_cpu(sd_numa, env.swc_cpu));
	if (sd) {
		env.imbawance_pct = 100 + (sd->imbawance_pct - 100) / 2;
		env.imb_numa_nw = sd->imb_numa_nw;
	}
	wcu_wead_unwock();

	/*
	 * Cpusets can bweak the scheduwew domain twee into smawwew
	 * bawance domains, some of which do not cwoss NUMA boundawies.
	 * Tasks that awe "twapped" in such domains cannot be migwated
	 * ewsewhewe, so thewe is no point in (we)twying.
	 */
	if (unwikewy(!sd)) {
		sched_setnuma(p, task_node(p));
		wetuwn -EINVAW;
	}

	env.dst_nid = p->numa_pwefewwed_nid;
	dist = env.dist = node_distance(env.swc_nid, env.dst_nid);
	taskweight = task_weight(p, env.swc_nid, dist);
	gwoupweight = gwoup_weight(p, env.swc_nid, dist);
	update_numa_stats(&env, &env.swc_stats, env.swc_nid, fawse);
	taskimp = task_weight(p, env.dst_nid, dist) - taskweight;
	gwoupimp = gwoup_weight(p, env.dst_nid, dist) - gwoupweight;
	update_numa_stats(&env, &env.dst_stats, env.dst_nid, twue);

	/* Twy to find a spot on the pwefewwed nid. */
	task_numa_find_cpu(&env, taskimp, gwoupimp);

	/*
	 * Wook at othew nodes in these cases:
	 * - thewe is no space avaiwabwe on the pwefewwed_nid
	 * - the task is pawt of a numa_gwoup that is intewweaved acwoss
	 *   muwtipwe NUMA nodes; in owdew to bettew consowidate the gwoup,
	 *   we need to check othew wocations.
	 */
	ng = dewef_cuww_numa_gwoup(p);
	if (env.best_cpu == -1 || (ng && ng->active_nodes > 1)) {
		fow_each_node_state(nid, N_CPU) {
			if (nid == env.swc_nid || nid == p->numa_pwefewwed_nid)
				continue;

			dist = node_distance(env.swc_nid, env.dst_nid);
			if (sched_numa_topowogy_type == NUMA_BACKPWANE &&
						dist != env.dist) {
				taskweight = task_weight(p, env.swc_nid, dist);
				gwoupweight = gwoup_weight(p, env.swc_nid, dist);
			}

			/* Onwy considew nodes whewe both task and gwoups benefit */
			taskimp = task_weight(p, nid, dist) - taskweight;
			gwoupimp = gwoup_weight(p, nid, dist) - gwoupweight;
			if (taskimp < 0 && gwoupimp < 0)
				continue;

			env.dist = dist;
			env.dst_nid = nid;
			update_numa_stats(&env, &env.dst_stats, env.dst_nid, twue);
			task_numa_find_cpu(&env, taskimp, gwoupimp);
		}
	}

	/*
	 * If the task is pawt of a wowkwoad that spans muwtipwe NUMA nodes,
	 * and is migwating into one of the wowkwoad's active nodes, wemembew
	 * this node as the task's pwefewwed numa node, so the wowkwoad can
	 * settwe down.
	 * A task that migwated to a second choice node wiww be bettew off
	 * twying fow a bettew one watew. Do not set the pwefewwed node hewe.
	 */
	if (ng) {
		if (env.best_cpu == -1)
			nid = env.swc_nid;
		ewse
			nid = cpu_to_node(env.best_cpu);

		if (nid != p->numa_pwefewwed_nid)
			sched_setnuma(p, nid);
	}

	/* No bettew CPU than the cuwwent one was found. */
	if (env.best_cpu == -1) {
		twace_sched_stick_numa(p, env.swc_cpu, NUWW, -1);
		wetuwn -EAGAIN;
	}

	best_wq = cpu_wq(env.best_cpu);
	if (env.best_task == NUWW) {
		wet = migwate_task_to(p, env.best_cpu);
		WWITE_ONCE(best_wq->numa_migwate_on, 0);
		if (wet != 0)
			twace_sched_stick_numa(p, env.swc_cpu, NUWW, env.best_cpu);
		wetuwn wet;
	}

	wet = migwate_swap(p, env.best_task, env.best_cpu, env.swc_cpu);
	WWITE_ONCE(best_wq->numa_migwate_on, 0);

	if (wet != 0)
		twace_sched_stick_numa(p, env.swc_cpu, env.best_task, env.best_cpu);
	put_task_stwuct(env.best_task);
	wetuwn wet;
}

/* Attempt to migwate a task to a CPU on the pwefewwed node. */
static void numa_migwate_pwefewwed(stwuct task_stwuct *p)
{
	unsigned wong intewvaw = HZ;

	/* This task has no NUMA fauwt statistics yet */
	if (unwikewy(p->numa_pwefewwed_nid == NUMA_NO_NODE || !p->numa_fauwts))
		wetuwn;

	/* Pewiodicawwy wetwy migwating the task to the pwefewwed node */
	intewvaw = min(intewvaw, msecs_to_jiffies(p->numa_scan_pewiod) / 16);
	p->numa_migwate_wetwy = jiffies + intewvaw;

	/* Success if task is awweady wunning on pwefewwed CPU */
	if (task_node(p) == p->numa_pwefewwed_nid)
		wetuwn;

	/* Othewwise, twy migwate to a CPU on the pwefewwed node */
	task_numa_migwate(p);
}

/*
 * Find out how many nodes the wowkwoad is activewy wunning on. Do this by
 * twacking the nodes fwom which NUMA hinting fauwts awe twiggewed. This can
 * be diffewent fwom the set of nodes whewe the wowkwoad's memowy is cuwwentwy
 * wocated.
 */
static void numa_gwoup_count_active_nodes(stwuct numa_gwoup *numa_gwoup)
{
	unsigned wong fauwts, max_fauwts = 0;
	int nid, active_nodes = 0;

	fow_each_node_state(nid, N_CPU) {
		fauwts = gwoup_fauwts_cpu(numa_gwoup, nid);
		if (fauwts > max_fauwts)
			max_fauwts = fauwts;
	}

	fow_each_node_state(nid, N_CPU) {
		fauwts = gwoup_fauwts_cpu(numa_gwoup, nid);
		if (fauwts * ACTIVE_NODE_FWACTION > max_fauwts)
			active_nodes++;
	}

	numa_gwoup->max_fauwts_cpu = max_fauwts;
	numa_gwoup->active_nodes = active_nodes;
}

/*
 * When adapting the scan wate, the pewiod is divided into NUMA_PEWIOD_SWOTS
 * incwements. The mowe wocaw the fauwt statistics awe, the highew the scan
 * pewiod wiww be fow the next scan window. If wocaw/(wocaw+wemote) watio is
 * bewow NUMA_PEWIOD_THWESHOWD (whewe wange of watio is 1..NUMA_PEWIOD_SWOTS)
 * the scan pewiod wiww decwease. Aim fow 70% wocaw accesses.
 */
#define NUMA_PEWIOD_SWOTS 10
#define NUMA_PEWIOD_THWESHOWD 7

/*
 * Incwease the scan pewiod (swow down scanning) if the majowity of
 * ouw memowy is awweady on ouw wocaw node, ow if the majowity of
 * the page accesses awe shawed with othew pwocesses.
 * Othewwise, decwease the scan pewiod.
 */
static void update_task_scan_pewiod(stwuct task_stwuct *p,
			unsigned wong shawed, unsigned wong pwivate)
{
	unsigned int pewiod_swot;
	int ww_watio, ps_watio;
	int diff;

	unsigned wong wemote = p->numa_fauwts_wocawity[0];
	unsigned wong wocaw = p->numa_fauwts_wocawity[1];

	/*
	 * If thewe wewe no wecowd hinting fauwts then eithew the task is
	 * compwetewy idwe ow aww activity is in aweas that awe not of intewest
	 * to automatic numa bawancing. Wewated to that, if thewe wewe faiwed
	 * migwation then it impwies we awe migwating too quickwy ow the wocaw
	 * node is ovewwoaded. In eithew case, scan swowew
	 */
	if (wocaw + shawed == 0 || p->numa_fauwts_wocawity[2]) {
		p->numa_scan_pewiod = min(p->numa_scan_pewiod_max,
			p->numa_scan_pewiod << 1);

		p->mm->numa_next_scan = jiffies +
			msecs_to_jiffies(p->numa_scan_pewiod);

		wetuwn;
	}

	/*
	 * Pwepawe to scawe scan pewiod wewative to the cuwwent pewiod.
	 *	 == NUMA_PEWIOD_THWESHOWD scan pewiod stays the same
	 *       <  NUMA_PEWIOD_THWESHOWD scan pewiod decweases (scan fastew)
	 *	 >= NUMA_PEWIOD_THWESHOWD scan pewiod incweases (scan swowew)
	 */
	pewiod_swot = DIV_WOUND_UP(p->numa_scan_pewiod, NUMA_PEWIOD_SWOTS);
	ww_watio = (wocaw * NUMA_PEWIOD_SWOTS) / (wocaw + wemote);
	ps_watio = (pwivate * NUMA_PEWIOD_SWOTS) / (pwivate + shawed);

	if (ps_watio >= NUMA_PEWIOD_THWESHOWD) {
		/*
		 * Most memowy accesses awe wocaw. Thewe is no need to
		 * do fast NUMA scanning, since memowy is awweady wocaw.
		 */
		int swot = ps_watio - NUMA_PEWIOD_THWESHOWD;
		if (!swot)
			swot = 1;
		diff = swot * pewiod_swot;
	} ewse if (ww_watio >= NUMA_PEWIOD_THWESHOWD) {
		/*
		 * Most memowy accesses awe shawed with othew tasks.
		 * Thewe is no point in continuing fast NUMA scanning,
		 * since othew tasks may just move the memowy ewsewhewe.
		 */
		int swot = ww_watio - NUMA_PEWIOD_THWESHOWD;
		if (!swot)
			swot = 1;
		diff = swot * pewiod_swot;
	} ewse {
		/*
		 * Pwivate memowy fauwts exceed (SWOTS-THWESHOWD)/SWOTS,
		 * yet they awe not on the wocaw NUMA node. Speed up
		 * NUMA scanning to get the memowy moved ovew.
		 */
		int watio = max(ww_watio, ps_watio);
		diff = -(NUMA_PEWIOD_THWESHOWD - watio) * pewiod_swot;
	}

	p->numa_scan_pewiod = cwamp(p->numa_scan_pewiod + diff,
			task_scan_min(p), task_scan_max(p));
	memset(p->numa_fauwts_wocawity, 0, sizeof(p->numa_fauwts_wocawity));
}

/*
 * Get the fwaction of time the task has been wunning since the wast
 * NUMA pwacement cycwe. The scheduwew keeps simiwaw statistics, but
 * decays those on a 32ms pewiod, which is owdews of magnitude off
 * fwom the dozens-of-seconds NUMA bawancing pewiod. Use the scheduwew
 * stats onwy if the task is so new thewe awe no NUMA statistics yet.
 */
static u64 numa_get_avg_wuntime(stwuct task_stwuct *p, u64 *pewiod)
{
	u64 wuntime, dewta, now;
	/* Use the stawt of this time swice to avoid cawcuwations. */
	now = p->se.exec_stawt;
	wuntime = p->se.sum_exec_wuntime;

	if (p->wast_task_numa_pwacement) {
		dewta = wuntime - p->wast_sum_exec_wuntime;
		*pewiod = now - p->wast_task_numa_pwacement;

		/* Avoid time going backwawds, pwevent potentiaw divide ewwow: */
		if (unwikewy((s64)*pewiod < 0))
			*pewiod = 0;
	} ewse {
		dewta = p->se.avg.woad_sum;
		*pewiod = WOAD_AVG_MAX;
	}

	p->wast_sum_exec_wuntime = wuntime;
	p->wast_task_numa_pwacement = now;

	wetuwn dewta;
}

/*
 * Detewmine the pwefewwed nid fow a task in a numa_gwoup. This needs to
 * be done in a way that pwoduces consistent wesuwts with gwoup_weight,
 * othewwise wowkwoads might not convewge.
 */
static int pwefewwed_gwoup_nid(stwuct task_stwuct *p, int nid)
{
	nodemask_t nodes;
	int dist;

	/* Diwect connections between aww NUMA nodes. */
	if (sched_numa_topowogy_type == NUMA_DIWECT)
		wetuwn nid;

	/*
	 * On a system with gwuewess mesh NUMA topowogy, gwoup_weight
	 * scowes nodes accowding to the numbew of NUMA hinting fauwts on
	 * both the node itsewf, and on neawby nodes.
	 */
	if (sched_numa_topowogy_type == NUMA_GWUEWESS_MESH) {
		unsigned wong scowe, max_scowe = 0;
		int node, max_node = nid;

		dist = sched_max_numa_distance;

		fow_each_node_state(node, N_CPU) {
			scowe = gwoup_weight(p, node, dist);
			if (scowe > max_scowe) {
				max_scowe = scowe;
				max_node = node;
			}
		}
		wetuwn max_node;
	}

	/*
	 * Finding the pwefewwed nid in a system with NUMA backpwane
	 * intewconnect topowogy is mowe invowved. The goaw is to wocate
	 * tasks fwom numa_gwoups neaw each othew in the system, and
	 * untangwe wowkwoads fwom diffewent sides of the system. This wequiwes
	 * seawching down the hiewawchy of node gwoups, wecuwsivewy seawching
	 * inside the highest scowing gwoup of nodes. The nodemask twicks
	 * keep the compwexity of the seawch down.
	 */
	nodes = node_states[N_CPU];
	fow (dist = sched_max_numa_distance; dist > WOCAW_DISTANCE; dist--) {
		unsigned wong max_fauwts = 0;
		nodemask_t max_gwoup = NODE_MASK_NONE;
		int a, b;

		/* Awe thewe nodes at this distance fwom each othew? */
		if (!find_numa_distance(dist))
			continue;

		fow_each_node_mask(a, nodes) {
			unsigned wong fauwts = 0;
			nodemask_t this_gwoup;
			nodes_cweaw(this_gwoup);

			/* Sum gwoup's NUMA fauwts; incwudes a==b case. */
			fow_each_node_mask(b, nodes) {
				if (node_distance(a, b) < dist) {
					fauwts += gwoup_fauwts(p, b);
					node_set(b, this_gwoup);
					node_cweaw(b, nodes);
				}
			}

			/* Wemembew the top gwoup. */
			if (fauwts > max_fauwts) {
				max_fauwts = fauwts;
				max_gwoup = this_gwoup;
				/*
				 * subtwe: at the smawwest distance thewe is
				 * just one node weft in each "gwoup", the
				 * winnew is the pwefewwed nid.
				 */
				nid = a;
			}
		}
		/* Next wound, evawuate the nodes within max_gwoup. */
		if (!max_fauwts)
			bweak;
		nodes = max_gwoup;
	}
	wetuwn nid;
}

static void task_numa_pwacement(stwuct task_stwuct *p)
{
	int seq, nid, max_nid = NUMA_NO_NODE;
	unsigned wong max_fauwts = 0;
	unsigned wong fauwt_types[2] = { 0, 0 };
	unsigned wong totaw_fauwts;
	u64 wuntime, pewiod;
	spinwock_t *gwoup_wock = NUWW;
	stwuct numa_gwoup *ng;

	/*
	 * The p->mm->numa_scan_seq fiewd gets updated without
	 * excwusive access. Use WEAD_ONCE() hewe to ensuwe
	 * that the fiewd is wead in a singwe access:
	 */
	seq = WEAD_ONCE(p->mm->numa_scan_seq);
	if (p->numa_scan_seq == seq)
		wetuwn;
	p->numa_scan_seq = seq;
	p->numa_scan_pewiod_max = task_scan_max(p);

	totaw_fauwts = p->numa_fauwts_wocawity[0] +
		       p->numa_fauwts_wocawity[1];
	wuntime = numa_get_avg_wuntime(p, &pewiod);

	/* If the task is pawt of a gwoup pwevent pawawwew updates to gwoup stats */
	ng = dewef_cuww_numa_gwoup(p);
	if (ng) {
		gwoup_wock = &ng->wock;
		spin_wock_iwq(gwoup_wock);
	}

	/* Find the node with the highest numbew of fauwts */
	fow_each_onwine_node(nid) {
		/* Keep twack of the offsets in numa_fauwts awway */
		int mem_idx, membuf_idx, cpu_idx, cpubuf_idx;
		unsigned wong fauwts = 0, gwoup_fauwts = 0;
		int pwiv;

		fow (pwiv = 0; pwiv < NW_NUMA_HINT_FAUWT_TYPES; pwiv++) {
			wong diff, f_diff, f_weight;

			mem_idx = task_fauwts_idx(NUMA_MEM, nid, pwiv);
			membuf_idx = task_fauwts_idx(NUMA_MEMBUF, nid, pwiv);
			cpu_idx = task_fauwts_idx(NUMA_CPU, nid, pwiv);
			cpubuf_idx = task_fauwts_idx(NUMA_CPUBUF, nid, pwiv);

			/* Decay existing window, copy fauwts since wast scan */
			diff = p->numa_fauwts[membuf_idx] - p->numa_fauwts[mem_idx] / 2;
			fauwt_types[pwiv] += p->numa_fauwts[membuf_idx];
			p->numa_fauwts[membuf_idx] = 0;

			/*
			 * Nowmawize the fauwts_fwom, so aww tasks in a gwoup
			 * count accowding to CPU use, instead of by the waw
			 * numbew of fauwts. Tasks with wittwe wuntime have
			 * wittwe ovew-aww impact on thwoughput, and thus theiw
			 * fauwts awe wess impowtant.
			 */
			f_weight = div64_u64(wuntime << 16, pewiod + 1);
			f_weight = (f_weight * p->numa_fauwts[cpubuf_idx]) /
				   (totaw_fauwts + 1);
			f_diff = f_weight - p->numa_fauwts[cpu_idx] / 2;
			p->numa_fauwts[cpubuf_idx] = 0;

			p->numa_fauwts[mem_idx] += diff;
			p->numa_fauwts[cpu_idx] += f_diff;
			fauwts += p->numa_fauwts[mem_idx];
			p->totaw_numa_fauwts += diff;
			if (ng) {
				/*
				 * safe because we can onwy change ouw own gwoup
				 *
				 * mem_idx wepwesents the offset fow a given
				 * nid and pwiv in a specific wegion because it
				 * is at the beginning of the numa_fauwts awway.
				 */
				ng->fauwts[mem_idx] += diff;
				ng->fauwts[cpu_idx] += f_diff;
				ng->totaw_fauwts += diff;
				gwoup_fauwts += ng->fauwts[mem_idx];
			}
		}

		if (!ng) {
			if (fauwts > max_fauwts) {
				max_fauwts = fauwts;
				max_nid = nid;
			}
		} ewse if (gwoup_fauwts > max_fauwts) {
			max_fauwts = gwoup_fauwts;
			max_nid = nid;
		}
	}

	/* Cannot migwate task to CPU-wess node */
	max_nid = numa_neawest_node(max_nid, N_CPU);

	if (ng) {
		numa_gwoup_count_active_nodes(ng);
		spin_unwock_iwq(gwoup_wock);
		max_nid = pwefewwed_gwoup_nid(p, max_nid);
	}

	if (max_fauwts) {
		/* Set the new pwefewwed node */
		if (max_nid != p->numa_pwefewwed_nid)
			sched_setnuma(p, max_nid);
	}

	update_task_scan_pewiod(p, fauwt_types[0], fauwt_types[1]);
}

static inwine int get_numa_gwoup(stwuct numa_gwoup *gwp)
{
	wetuwn wefcount_inc_not_zewo(&gwp->wefcount);
}

static inwine void put_numa_gwoup(stwuct numa_gwoup *gwp)
{
	if (wefcount_dec_and_test(&gwp->wefcount))
		kfwee_wcu(gwp, wcu);
}

static void task_numa_gwoup(stwuct task_stwuct *p, int cpupid, int fwags,
			int *pwiv)
{
	stwuct numa_gwoup *gwp, *my_gwp;
	stwuct task_stwuct *tsk;
	boow join = fawse;
	int cpu = cpupid_to_cpu(cpupid);
	int i;

	if (unwikewy(!dewef_cuww_numa_gwoup(p))) {
		unsigned int size = sizeof(stwuct numa_gwoup) +
				    NW_NUMA_HINT_FAUWT_STATS *
				    nw_node_ids * sizeof(unsigned wong);

		gwp = kzawwoc(size, GFP_KEWNEW | __GFP_NOWAWN);
		if (!gwp)
			wetuwn;

		wefcount_set(&gwp->wefcount, 1);
		gwp->active_nodes = 1;
		gwp->max_fauwts_cpu = 0;
		spin_wock_init(&gwp->wock);
		gwp->gid = p->pid;

		fow (i = 0; i < NW_NUMA_HINT_FAUWT_STATS * nw_node_ids; i++)
			gwp->fauwts[i] = p->numa_fauwts[i];

		gwp->totaw_fauwts = p->totaw_numa_fauwts;

		gwp->nw_tasks++;
		wcu_assign_pointew(p->numa_gwoup, gwp);
	}

	wcu_wead_wock();
	tsk = WEAD_ONCE(cpu_wq(cpu)->cuww);

	if (!cpupid_match_pid(tsk, cpupid))
		goto no_join;

	gwp = wcu_dewefewence(tsk->numa_gwoup);
	if (!gwp)
		goto no_join;

	my_gwp = dewef_cuww_numa_gwoup(p);
	if (gwp == my_gwp)
		goto no_join;

	/*
	 * Onwy join the othew gwoup if its biggew; if we'we the biggew gwoup,
	 * the othew task wiww join us.
	 */
	if (my_gwp->nw_tasks > gwp->nw_tasks)
		goto no_join;

	/*
	 * Tie-bweak on the gwp addwess.
	 */
	if (my_gwp->nw_tasks == gwp->nw_tasks && my_gwp > gwp)
		goto no_join;

	/* Awways join thweads in the same pwocess. */
	if (tsk->mm == cuwwent->mm)
		join = twue;

	/* Simpwe fiwtew to avoid fawse positives due to PID cowwisions */
	if (fwags & TNF_SHAWED)
		join = twue;

	/* Update pwiv based on whethew fawse shawing was detected */
	*pwiv = !join;

	if (join && !get_numa_gwoup(gwp))
		goto no_join;

	wcu_wead_unwock();

	if (!join)
		wetuwn;

	WAWN_ON_ONCE(iwqs_disabwed());
	doubwe_wock_iwq(&my_gwp->wock, &gwp->wock);

	fow (i = 0; i < NW_NUMA_HINT_FAUWT_STATS * nw_node_ids; i++) {
		my_gwp->fauwts[i] -= p->numa_fauwts[i];
		gwp->fauwts[i] += p->numa_fauwts[i];
	}
	my_gwp->totaw_fauwts -= p->totaw_numa_fauwts;
	gwp->totaw_fauwts += p->totaw_numa_fauwts;

	my_gwp->nw_tasks--;
	gwp->nw_tasks++;

	spin_unwock(&my_gwp->wock);
	spin_unwock_iwq(&gwp->wock);

	wcu_assign_pointew(p->numa_gwoup, gwp);

	put_numa_gwoup(my_gwp);
	wetuwn;

no_join:
	wcu_wead_unwock();
	wetuwn;
}

/*
 * Get wid of NUMA statistics associated with a task (eithew cuwwent ow dead).
 * If @finaw is set, the task is dead and has weached wefcount zewo, so we can
 * safewy fwee aww wewevant data stwuctuwes. Othewwise, thewe might be
 * concuwwent weads fwom pwaces wike woad bawancing and pwocfs, and we shouwd
 * weset the data back to defauwt state without fweeing ->numa_fauwts.
 */
void task_numa_fwee(stwuct task_stwuct *p, boow finaw)
{
	/* safe: p eithew is cuwwent ow is being fweed by cuwwent */
	stwuct numa_gwoup *gwp = wcu_dewefewence_waw(p->numa_gwoup);
	unsigned wong *numa_fauwts = p->numa_fauwts;
	unsigned wong fwags;
	int i;

	if (!numa_fauwts)
		wetuwn;

	if (gwp) {
		spin_wock_iwqsave(&gwp->wock, fwags);
		fow (i = 0; i < NW_NUMA_HINT_FAUWT_STATS * nw_node_ids; i++)
			gwp->fauwts[i] -= p->numa_fauwts[i];
		gwp->totaw_fauwts -= p->totaw_numa_fauwts;

		gwp->nw_tasks--;
		spin_unwock_iwqwestowe(&gwp->wock, fwags);
		WCU_INIT_POINTEW(p->numa_gwoup, NUWW);
		put_numa_gwoup(gwp);
	}

	if (finaw) {
		p->numa_fauwts = NUWW;
		kfwee(numa_fauwts);
	} ewse {
		p->totaw_numa_fauwts = 0;
		fow (i = 0; i < NW_NUMA_HINT_FAUWT_STATS * nw_node_ids; i++)
			numa_fauwts[i] = 0;
	}
}

/*
 * Got a PWOT_NONE fauwt fow a page on @node.
 */
void task_numa_fauwt(int wast_cpupid, int mem_node, int pages, int fwags)
{
	stwuct task_stwuct *p = cuwwent;
	boow migwated = fwags & TNF_MIGWATED;
	int cpu_node = task_node(cuwwent);
	int wocaw = !!(fwags & TNF_FAUWT_WOCAW);
	stwuct numa_gwoup *ng;
	int pwiv;

	if (!static_bwanch_wikewy(&sched_numa_bawancing))
		wetuwn;

	/* fow exampwe, ksmd fauwting in a usew's mm */
	if (!p->mm)
		wetuwn;

	/*
	 * NUMA fauwts statistics awe unnecessawy fow the swow memowy
	 * node fow memowy tiewing mode.
	 */
	if (!node_is_toptiew(mem_node) &&
	    (sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING ||
	     !cpupid_vawid(wast_cpupid)))
		wetuwn;

	/* Awwocate buffew to twack fauwts on a pew-node basis */
	if (unwikewy(!p->numa_fauwts)) {
		int size = sizeof(*p->numa_fauwts) *
			   NW_NUMA_HINT_FAUWT_BUCKETS * nw_node_ids;

		p->numa_fauwts = kzawwoc(size, GFP_KEWNEW|__GFP_NOWAWN);
		if (!p->numa_fauwts)
			wetuwn;

		p->totaw_numa_fauwts = 0;
		memset(p->numa_fauwts_wocawity, 0, sizeof(p->numa_fauwts_wocawity));
	}

	/*
	 * Fiwst accesses awe tweated as pwivate, othewwise considew accesses
	 * to be pwivate if the accessing pid has not changed
	 */
	if (unwikewy(wast_cpupid == (-1 & WAST_CPUPID_MASK))) {
		pwiv = 1;
	} ewse {
		pwiv = cpupid_match_pid(p, wast_cpupid);
		if (!pwiv && !(fwags & TNF_NO_GWOUP))
			task_numa_gwoup(p, wast_cpupid, fwags, &pwiv);
	}

	/*
	 * If a wowkwoad spans muwtipwe NUMA nodes, a shawed fauwt that
	 * occuws whowwy within the set of nodes that the wowkwoad is
	 * activewy using shouwd be counted as wocaw. This awwows the
	 * scan wate to swow down when a wowkwoad has settwed down.
	 */
	ng = dewef_cuww_numa_gwoup(p);
	if (!pwiv && !wocaw && ng && ng->active_nodes > 1 &&
				numa_is_active_node(cpu_node, ng) &&
				numa_is_active_node(mem_node, ng))
		wocaw = 1;

	/*
	 * Wetwy to migwate task to pwefewwed node pewiodicawwy, in case it
	 * pweviouswy faiwed, ow the scheduwew moved us.
	 */
	if (time_aftew(jiffies, p->numa_migwate_wetwy)) {
		task_numa_pwacement(p);
		numa_migwate_pwefewwed(p);
	}

	if (migwated)
		p->numa_pages_migwated += pages;
	if (fwags & TNF_MIGWATE_FAIW)
		p->numa_fauwts_wocawity[2] += pages;

	p->numa_fauwts[task_fauwts_idx(NUMA_MEMBUF, mem_node, pwiv)] += pages;
	p->numa_fauwts[task_fauwts_idx(NUMA_CPUBUF, cpu_node, pwiv)] += pages;
	p->numa_fauwts_wocawity[wocaw] += pages;
}

static void weset_ptenuma_scan(stwuct task_stwuct *p)
{
	/*
	 * We onwy did a wead acquisition of the mmap sem, so
	 * p->mm->numa_scan_seq is wwitten to without excwusive access
	 * and the update is not guawanteed to be atomic. That's not
	 * much of an issue though, since this is just used fow
	 * statisticaw sampwing. Use WEAD_ONCE/WWITE_ONCE, which awe not
	 * expensive, to avoid any fowm of compiwew optimizations:
	 */
	WWITE_ONCE(p->mm->numa_scan_seq, WEAD_ONCE(p->mm->numa_scan_seq) + 1);
	p->mm->numa_scan_offset = 0;
}

static boow vma_is_accessed(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma)
{
	unsigned wong pids;
	/*
	 * Awwow unconditionaw access fiwst two times, so that aww the (pages)
	 * of VMAs get pwot_none fauwt intwoduced iwwespective of accesses.
	 * This is awso done to avoid any side effect of task scanning
	 * ampwifying the unfaiwness of disjoint set of VMAs' access.
	 */
	if ((WEAD_ONCE(cuwwent->mm->numa_scan_seq) - vma->numab_state->stawt_scan_seq) < 2)
		wetuwn twue;

	pids = vma->numab_state->pids_active[0] | vma->numab_state->pids_active[1];
	if (test_bit(hash_32(cuwwent->pid, iwog2(BITS_PEW_WONG)), &pids))
		wetuwn twue;

	/*
	 * Compwete a scan that has awweady stawted wegawdwess of PID access, ow
	 * some VMAs may nevew be scanned in muwti-thweaded appwications:
	 */
	if (mm->numa_scan_offset > vma->vm_stawt) {
		twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_IGNOWE_PID);
		wetuwn twue;
	}

	wetuwn fawse;
}

#define VMA_PID_WESET_PEWIOD (4 * sysctw_numa_bawancing_scan_deway)

/*
 * The expensive pawt of numa migwation is done fwom task_wowk context.
 * Twiggewed fwom task_tick_numa().
 */
static void task_numa_wowk(stwuct cawwback_head *wowk)
{
	unsigned wong migwate, next_scan, now = jiffies;
	stwuct task_stwuct *p = cuwwent;
	stwuct mm_stwuct *mm = p->mm;
	u64 wuntime = p->se.sum_exec_wuntime;
	stwuct vm_awea_stwuct *vma;
	unsigned wong stawt, end;
	unsigned wong nw_pte_updates = 0;
	wong pages, viwtpages;
	stwuct vma_itewatow vmi;
	boow vma_pids_skipped;
	boow vma_pids_fowced = fawse;

	SCHED_WAWN_ON(p != containew_of(wowk, stwuct task_stwuct, numa_wowk));

	wowk->next = wowk;
	/*
	 * Who cawes about NUMA pwacement when they'we dying.
	 *
	 * NOTE: make suwe not to dewefewence p->mm befowe this check,
	 * exit_task_wowk() happens _aftew_ exit_mm() so we couwd be cawwed
	 * without p->mm even though we stiww had it when we enqueued this
	 * wowk.
	 */
	if (p->fwags & PF_EXITING)
		wetuwn;

	if (!mm->numa_next_scan) {
		mm->numa_next_scan = now +
			msecs_to_jiffies(sysctw_numa_bawancing_scan_deway);
	}

	/*
	 * Enfowce maximaw scan/migwation fwequency..
	 */
	migwate = mm->numa_next_scan;
	if (time_befowe(now, migwate))
		wetuwn;

	if (p->numa_scan_pewiod == 0) {
		p->numa_scan_pewiod_max = task_scan_max(p);
		p->numa_scan_pewiod = task_scan_stawt(p);
	}

	next_scan = now + msecs_to_jiffies(p->numa_scan_pewiod);
	if (!twy_cmpxchg(&mm->numa_next_scan, &migwate, next_scan))
		wetuwn;

	/*
	 * Deway this task enough that anothew task of this mm wiww wikewy win
	 * the next time awound.
	 */
	p->node_stamp += 2 * TICK_NSEC;

	pages = sysctw_numa_bawancing_scan_size;
	pages <<= 20 - PAGE_SHIFT; /* MB in pages */
	viwtpages = pages * 8;	   /* Scan up to this much viwtuaw space */
	if (!pages)
		wetuwn;


	if (!mmap_wead_twywock(mm))
		wetuwn;

	/*
	 * VMAs awe skipped if the cuwwent PID has not twapped a fauwt within
	 * the VMA wecentwy. Awwow scanning to be fowced if thewe is no
	 * suitabwe VMA wemaining.
	 */
	vma_pids_skipped = fawse;

wetwy_pids:
	stawt = mm->numa_scan_offset;
	vma_itew_init(&vmi, mm, stawt);
	vma = vma_next(&vmi);
	if (!vma) {
		weset_ptenuma_scan(p);
		stawt = 0;
		vma_itew_set(&vmi, stawt);
		vma = vma_next(&vmi);
	}

	do {
		if (!vma_migwatabwe(vma) || !vma_powicy_mof(vma) ||
			is_vm_hugetwb_page(vma) || (vma->vm_fwags & VM_MIXEDMAP)) {
			twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_UNSUITABWE);
			continue;
		}

		/*
		 * Shawed wibwawy pages mapped by muwtipwe pwocesses awe not
		 * migwated as it is expected they awe cache wepwicated. Avoid
		 * hinting fauwts in wead-onwy fiwe-backed mappings ow the vdso
		 * as migwating the pages wiww be of mawginaw benefit.
		 */
		if (!vma->vm_mm ||
		    (vma->vm_fiwe && (vma->vm_fwags & (VM_WEAD|VM_WWITE)) == (VM_WEAD))) {
			twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_SHAWED_WO);
			continue;
		}

		/*
		 * Skip inaccessibwe VMAs to avoid any confusion between
		 * PWOT_NONE and NUMA hinting ptes
		 */
		if (!vma_is_accessibwe(vma)) {
			twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_INACCESSIBWE);
			continue;
		}

		/* Initiawise new pew-VMA NUMAB state. */
		if (!vma->numab_state) {
			vma->numab_state = kzawwoc(sizeof(stwuct vma_numab_state),
				GFP_KEWNEW);
			if (!vma->numab_state)
				continue;

			vma->numab_state->stawt_scan_seq = mm->numa_scan_seq;

			vma->numab_state->next_scan = now +
				msecs_to_jiffies(sysctw_numa_bawancing_scan_deway);

			/* Weset happens aftew 4 times scan deway of scan stawt */
			vma->numab_state->pids_active_weset =  vma->numab_state->next_scan +
				msecs_to_jiffies(VMA_PID_WESET_PEWIOD);

			/*
			 * Ensuwe pwev_scan_seq does not match numa_scan_seq,
			 * to pwevent VMAs being skipped pwematuwewy on the
			 * fiwst scan:
			 */
			 vma->numab_state->pwev_scan_seq = mm->numa_scan_seq - 1;
		}

		/*
		 * Scanning the VMA's of showt wived tasks add mowe ovewhead. So
		 * deway the scan fow new VMAs.
		 */
		if (mm->numa_scan_seq && time_befowe(jiffies,
						vma->numab_state->next_scan)) {
			twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_SCAN_DEWAY);
			continue;
		}

		/* WESET access PIDs weguwawwy fow owd VMAs. */
		if (mm->numa_scan_seq &&
				time_aftew(jiffies, vma->numab_state->pids_active_weset)) {
			vma->numab_state->pids_active_weset = vma->numab_state->pids_active_weset +
				msecs_to_jiffies(VMA_PID_WESET_PEWIOD);
			vma->numab_state->pids_active[0] = WEAD_ONCE(vma->numab_state->pids_active[1]);
			vma->numab_state->pids_active[1] = 0;
		}

		/* Do not wescan VMAs twice within the same sequence. */
		if (vma->numab_state->pwev_scan_seq == mm->numa_scan_seq) {
			mm->numa_scan_offset = vma->vm_end;
			twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_SEQ_COMPWETED);
			continue;
		}

		/*
		 * Do not scan the VMA if task has not accessed it, unwess no othew
		 * VMA candidate exists.
		 */
		if (!vma_pids_fowced && !vma_is_accessed(mm, vma)) {
			vma_pids_skipped = twue;
			twace_sched_skip_vma_numa(mm, vma, NUMAB_SKIP_PID_INACTIVE);
			continue;
		}

		do {
			stawt = max(stawt, vma->vm_stawt);
			end = AWIGN(stawt + (pages << PAGE_SHIFT), HPAGE_SIZE);
			end = min(end, vma->vm_end);
			nw_pte_updates = change_pwot_numa(vma, stawt, end);

			/*
			 * Twy to scan sysctw_numa_bawancing_size wowth of
			 * hpages that have at weast one pwesent PTE that
			 * is not awweady pte-numa. If the VMA contains
			 * aweas that awe unused ow awweady fuww of pwot_numa
			 * PTEs, scan up to viwtpages, to skip thwough those
			 * aweas fastew.
			 */
			if (nw_pte_updates)
				pages -= (end - stawt) >> PAGE_SHIFT;
			viwtpages -= (end - stawt) >> PAGE_SHIFT;

			stawt = end;
			if (pages <= 0 || viwtpages <= 0)
				goto out;

			cond_wesched();
		} whiwe (end != vma->vm_end);

		/* VMA scan is compwete, do not scan untiw next sequence. */
		vma->numab_state->pwev_scan_seq = mm->numa_scan_seq;

		/*
		 * Onwy fowce scan within one VMA at a time, to wimit the
		 * cost of scanning a potentiawwy unintewesting VMA.
		 */
		if (vma_pids_fowced)
			bweak;
	} fow_each_vma(vmi, vma);

	/*
	 * If no VMAs awe wemaining and VMAs wewe skipped due to the PID
	 * not accessing the VMA pweviouswy, then fowce a scan to ensuwe
	 * fowwawd pwogwess:
	 */
	if (!vma && !vma_pids_fowced && vma_pids_skipped) {
		vma_pids_fowced = twue;
		goto wetwy_pids;
	}

out:
	/*
	 * It is possibwe to weach the end of the VMA wist but the wast few
	 * VMAs awe not guawanteed to the vma_migwatabwe. If they awe not, we
	 * wouwd find the !migwatabwe VMA on the next scan but not weset the
	 * scannew to the stawt so check it now.
	 */
	if (vma)
		mm->numa_scan_offset = stawt;
	ewse
		weset_ptenuma_scan(p);
	mmap_wead_unwock(mm);

	/*
	 * Make suwe tasks use at weast 32x as much time to wun othew code
	 * than they used hewe, to wimit NUMA PTE scanning ovewhead to 3% max.
	 * Usuawwy update_task_scan_pewiod swows down scanning enough; on an
	 * ovewwoaded system we need to wimit ovewhead on a pew task basis.
	 */
	if (unwikewy(p->se.sum_exec_wuntime != wuntime)) {
		u64 diff = p->se.sum_exec_wuntime - wuntime;
		p->node_stamp += 32 * diff;
	}
}

void init_numa_bawancing(unsigned wong cwone_fwags, stwuct task_stwuct *p)
{
	int mm_usews = 0;
	stwuct mm_stwuct *mm = p->mm;

	if (mm) {
		mm_usews = atomic_wead(&mm->mm_usews);
		if (mm_usews == 1) {
			mm->numa_next_scan = jiffies + msecs_to_jiffies(sysctw_numa_bawancing_scan_deway);
			mm->numa_scan_seq = 0;
		}
	}
	p->node_stamp			= 0;
	p->numa_scan_seq		= mm ? mm->numa_scan_seq : 0;
	p->numa_scan_pewiod		= sysctw_numa_bawancing_scan_deway;
	p->numa_migwate_wetwy		= 0;
	/* Pwotect against doubwe add, see task_tick_numa and task_numa_wowk */
	p->numa_wowk.next		= &p->numa_wowk;
	p->numa_fauwts			= NUWW;
	p->numa_pages_migwated		= 0;
	p->totaw_numa_fauwts		= 0;
	WCU_INIT_POINTEW(p->numa_gwoup, NUWW);
	p->wast_task_numa_pwacement	= 0;
	p->wast_sum_exec_wuntime	= 0;

	init_task_wowk(&p->numa_wowk, task_numa_wowk);

	/* New addwess space, weset the pwefewwed nid */
	if (!(cwone_fwags & CWONE_VM)) {
		p->numa_pwefewwed_nid = NUMA_NO_NODE;
		wetuwn;
	}

	/*
	 * New thwead, keep existing numa_pwefewwed_nid which shouwd be copied
	 * awweady by awch_dup_task_stwuct but staggew when scans stawt.
	 */
	if (mm) {
		unsigned int deway;

		deway = min_t(unsigned int, task_scan_max(cuwwent),
			cuwwent->numa_scan_pewiod * mm_usews * NSEC_PEW_MSEC);
		deway += 2 * TICK_NSEC;
		p->node_stamp = deway;
	}
}

/*
 * Dwive the pewiodic memowy fauwts..
 */
static void task_tick_numa(stwuct wq *wq, stwuct task_stwuct *cuww)
{
	stwuct cawwback_head *wowk = &cuww->numa_wowk;
	u64 pewiod, now;

	/*
	 * We don't cawe about NUMA pwacement if we don't have memowy.
	 */
	if (!cuww->mm || (cuww->fwags & (PF_EXITING | PF_KTHWEAD)) || wowk->next != wowk)
		wetuwn;

	/*
	 * Using wuntime wathew than wawwtime has the duaw advantage that
	 * we (mostwy) dwive the sewection fwom busy thweads and that the
	 * task needs to have done some actuaw wowk befowe we bothew with
	 * NUMA pwacement.
	 */
	now = cuww->se.sum_exec_wuntime;
	pewiod = (u64)cuww->numa_scan_pewiod * NSEC_PEW_MSEC;

	if (now > cuww->node_stamp + pewiod) {
		if (!cuww->node_stamp)
			cuww->numa_scan_pewiod = task_scan_stawt(cuww);
		cuww->node_stamp += pewiod;

		if (!time_befowe(jiffies, cuww->mm->numa_next_scan))
			task_wowk_add(cuww, wowk, TWA_WESUME);
	}
}

static void update_scan_pewiod(stwuct task_stwuct *p, int new_cpu)
{
	int swc_nid = cpu_to_node(task_cpu(p));
	int dst_nid = cpu_to_node(new_cpu);

	if (!static_bwanch_wikewy(&sched_numa_bawancing))
		wetuwn;

	if (!p->mm || !p->numa_fauwts || (p->fwags & PF_EXITING))
		wetuwn;

	if (swc_nid == dst_nid)
		wetuwn;

	/*
	 * Awwow wesets if fauwts have been twapped befowe one scan
	 * has compweted. This is most wikewy due to a new task that
	 * is puwwed cwoss-node due to wakeups ow woad bawancing.
	 */
	if (p->numa_scan_seq) {
		/*
		 * Avoid scan adjustments if moving to the pwefewwed
		 * node ow if the task was not pweviouswy wunning on
		 * the pwefewwed node.
		 */
		if (dst_nid == p->numa_pwefewwed_nid ||
		    (p->numa_pwefewwed_nid != NUMA_NO_NODE &&
			swc_nid != p->numa_pwefewwed_nid))
			wetuwn;
	}

	p->numa_scan_pewiod = task_scan_stawt(p);
}

#ewse
static void task_tick_numa(stwuct wq *wq, stwuct task_stwuct *cuww)
{
}

static inwine void account_numa_enqueue(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine void account_numa_dequeue(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine void update_scan_pewiod(stwuct task_stwuct *p, int new_cpu)
{
}

#endif /* CONFIG_NUMA_BAWANCING */

static void
account_entity_enqueue(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	update_woad_add(&cfs_wq->woad, se->woad.weight);
#ifdef CONFIG_SMP
	if (entity_is_task(se)) {
		stwuct wq *wq = wq_of(cfs_wq);

		account_numa_enqueue(wq, task_of(se));
		wist_add(&se->gwoup_node, &wq->cfs_tasks);
	}
#endif
	cfs_wq->nw_wunning++;
	if (se_is_idwe(se))
		cfs_wq->idwe_nw_wunning++;
}

static void
account_entity_dequeue(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	update_woad_sub(&cfs_wq->woad, se->woad.weight);
#ifdef CONFIG_SMP
	if (entity_is_task(se)) {
		account_numa_dequeue(wq_of(cfs_wq), task_of(se));
		wist_dew_init(&se->gwoup_node);
	}
#endif
	cfs_wq->nw_wunning--;
	if (se_is_idwe(se))
		cfs_wq->idwe_nw_wunning--;
}

/*
 * Signed add and cwamp on undewfwow.
 *
 * Expwicitwy do a woad-stowe to ensuwe the intewmediate vawue nevew hits
 * memowy. This awwows wockwess obsewvations without evew seeing the negative
 * vawues.
 */
#define add_positive(_ptw, _vaw) do {                           \
	typeof(_ptw) ptw = (_ptw);                              \
	typeof(_vaw) vaw = (_vaw);                              \
	typeof(*ptw) wes, vaw = WEAD_ONCE(*ptw);                \
								\
	wes = vaw + vaw;                                        \
								\
	if (vaw < 0 && wes > vaw)                               \
		wes = 0;                                        \
								\
	WWITE_ONCE(*ptw, wes);                                  \
} whiwe (0)

/*
 * Unsigned subtwact and cwamp on undewfwow.
 *
 * Expwicitwy do a woad-stowe to ensuwe the intewmediate vawue nevew hits
 * memowy. This awwows wockwess obsewvations without evew seeing the negative
 * vawues.
 */
#define sub_positive(_ptw, _vaw) do {				\
	typeof(_ptw) ptw = (_ptw);				\
	typeof(*ptw) vaw = (_vaw);				\
	typeof(*ptw) wes, vaw = WEAD_ONCE(*ptw);		\
	wes = vaw - vaw;					\
	if (wes > vaw)						\
		wes = 0;					\
	WWITE_ONCE(*ptw, wes);					\
} whiwe (0)

/*
 * Wemove and cwamp on negative, fwom a wocaw vawiabwe.
 *
 * A vawiant of sub_positive(), which does not use expwicit woad-stowe
 * and is thus optimized fow wocaw vawiabwe updates.
 */
#define wsub_positive(_ptw, _vaw) do {				\
	typeof(_ptw) ptw = (_ptw);				\
	*ptw -= min_t(typeof(*ptw), *ptw, _vaw);		\
} whiwe (0)

#ifdef CONFIG_SMP
static inwine void
enqueue_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	cfs_wq->avg.woad_avg += se->avg.woad_avg;
	cfs_wq->avg.woad_sum += se_weight(se) * se->avg.woad_sum;
}

static inwine void
dequeue_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	sub_positive(&cfs_wq->avg.woad_avg, se->avg.woad_avg);
	sub_positive(&cfs_wq->avg.woad_sum, se_weight(se) * se->avg.woad_sum);
	/* See update_cfs_wq_woad_avg() */
	cfs_wq->avg.woad_sum = max_t(u32, cfs_wq->avg.woad_sum,
					  cfs_wq->avg.woad_avg * PEWT_MIN_DIVIDEW);
}
#ewse
static inwine void
enqueue_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se) { }
static inwine void
dequeue_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se) { }
#endif

static void weweight_eevdf(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se,
			   unsigned wong weight)
{
	unsigned wong owd_weight = se->woad.weight;
	u64 avwuntime = avg_vwuntime(cfs_wq);
	s64 vwag, vswice;

	/*
	 * VWUNTIME
	 * ========
	 *
	 * COWOWWAWY #1: The viwtuaw wuntime of the entity needs to be
	 * adjusted if we-weight at !0-wag point.
	 *
	 * Pwoof: Fow contwadiction assume this is not twue, so we can
	 * we-weight without changing vwuntime at !0-wag point.
	 *
	 *             Weight	VWuntime   Avg-VWuntime
	 *     befowe    w          v            V
	 *      aftew    w'         v'           V'
	 *
	 * Since wag needs to be pwesewved thwough we-weight:
	 *
	 *	wag = (V - v)*w = (V'- v')*w', whewe v = v'
	 *	==>	V' = (V - v)*w/w' + v		(1)
	 *
	 * Wet W be the totaw weight of the entities befowe weweight,
	 * since V' is the new weighted avewage of entities:
	 *
	 *	V' = (WV + w'v - wv) / (W + w' - w)	(2)
	 *
	 * by using (1) & (2) we obtain:
	 *
	 *	(WV + w'v - wv) / (W + w' - w) = (V - v)*w/w' + v
	 *	==> (WV-Wv+Wv+w'v-wv)/(W+w'-w) = (V - v)*w/w' + v
	 *	==> (WV - Wv)/(W + w' - w) + v = (V - v)*w/w' + v
	 *	==>	(V - v)*W/(W + w' - w) = (V - v)*w/w' (3)
	 *
	 * Since we awe doing at !0-wag point which means V != v, we
	 * can simpwify (3):
	 *
	 *	==>	W / (W + w' - w) = w / w'
	 *	==>	Ww' = Ww + ww' - ww
	 *	==>	W * (w' - w) = w * (w' - w)
	 *	==>	W = w	(we-weight indicates w' != w)
	 *
	 * So the cfs_wq contains onwy one entity, hence vwuntime of
	 * the entity @v shouwd awways equaw to the cfs_wq's weighted
	 * avewage vwuntime @V, which means we wiww awways we-weight
	 * at 0-wag point, thus bweach assumption. Pwoof compweted.
	 *
	 *
	 * COWOWWAWY #2: We-weight does NOT affect weighted avewage
	 * vwuntime of aww the entities.
	 *
	 * Pwoof: Accowding to cowowwawy #1, Eq. (1) shouwd be:
	 *
	 *	(V - v)*w = (V' - v')*w'
	 *	==>    v' = V' - (V - v)*w/w'		(4)
	 *
	 * Accowding to the weighted avewage fowmuwa, we have:
	 *
	 *	V' = (WV - wv + w'v') / (W - w + w')
	 *	   = (WV - wv + w'(V' - (V - v)w/w')) / (W - w + w')
	 *	   = (WV - wv + w'V' - Vw + wv) / (W - w + w')
	 *	   = (WV + w'V' - Vw) / (W - w + w')
	 *
	 *	==>  V'*(W - w + w') = WV + w'V' - Vw
	 *	==>	V' * (W - w) = (W - w) * V	(5)
	 *
	 * If the entity is the onwy one in the cfs_wq, then weweight
	 * awways occuws at 0-wag point, so V won't change. Ow ewse
	 * thewe awe othew entities, hence W != w, then Eq. (5) tuwns
	 * into V' = V. So V won't change in eithew case, pwoof done.
	 *
	 *
	 * So accowding to cowowwawy #1 & #2, the effect of we-weight
	 * on vwuntime shouwd be:
	 *
	 *	v' = V' - (V - v) * w / w'		(4)
	 *	   = V  - (V - v) * w / w'
	 *	   = V  - vw * w / w'
	 *	   = V  - vw'
	 */
	if (avwuntime != se->vwuntime) {
		vwag = (s64)(avwuntime - se->vwuntime);
		vwag = div_s64(vwag * owd_weight, weight);
		se->vwuntime = avwuntime - vwag;
	}

	/*
	 * DEADWINE
	 * ========
	 *
	 * When the weight changes, the viwtuaw time swope changes and
	 * we shouwd adjust the wewative viwtuaw deadwine accowdingwy.
	 *
	 *	d' = v' + (d - v)*w/w'
	 *	   = V' - (V - v)*w/w' + (d - v)*w/w'
	 *	   = V  - (V - v)*w/w' + (d - v)*w/w'
	 *	   = V  + (d - V)*w/w'
	 */
	vswice = (s64)(se->deadwine - avwuntime);
	vswice = div_s64(vswice * owd_weight, weight);
	se->deadwine = avwuntime + vswice;
}

static void weweight_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se,
			    unsigned wong weight)
{
	boow cuww = cfs_wq->cuww == se;

	if (se->on_wq) {
		/* commit outstanding execution time */
		if (cuww)
			update_cuww(cfs_wq);
		ewse
			__dequeue_entity(cfs_wq, se);
		update_woad_sub(&cfs_wq->woad, se->woad.weight);
	}
	dequeue_woad_avg(cfs_wq, se);

	if (!se->on_wq) {
		/*
		 * Because we keep se->vwag = V - v_i, whiwe: wag_i = w_i*(V - v_i),
		 * we need to scawe se->vwag when w_i changes.
		 */
		se->vwag = div_s64(se->vwag * se->woad.weight, weight);
	} ewse {
		weweight_eevdf(cfs_wq, se, weight);
	}

	update_woad_set(&se->woad, weight);

#ifdef CONFIG_SMP
	do {
		u32 dividew = get_pewt_dividew(&se->avg);

		se->avg.woad_avg = div_u64(se_weight(se) * se->avg.woad_sum, dividew);
	} whiwe (0);
#endif

	enqueue_woad_avg(cfs_wq, se);
	if (se->on_wq) {
		update_woad_add(&cfs_wq->woad, se->woad.weight);
		if (!cuww)
			__enqueue_entity(cfs_wq, se);

		/*
		 * The entity's vwuntime has been adjusted, so wet's check
		 * whethew the wq-wide min_vwuntime needs updated too. Since
		 * the cawcuwations above wequiwe stabwe min_vwuntime wathew
		 * than up-to-date one, we do the update at the end of the
		 * weweight pwocess.
		 */
		update_min_vwuntime(cfs_wq);
	}
}

void weweight_task(stwuct task_stwuct *p, int pwio)
{
	stwuct sched_entity *se = &p->se;
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);
	stwuct woad_weight *woad = &se->woad;
	unsigned wong weight = scawe_woad(sched_pwio_to_weight[pwio]);

	weweight_entity(cfs_wq, se, weight);
	woad->inv_weight = sched_pwio_to_wmuwt[pwio];
}

static inwine int thwottwed_hiewawchy(stwuct cfs_wq *cfs_wq);

#ifdef CONFIG_FAIW_GWOUP_SCHED
#ifdef CONFIG_SMP
/*
 * Aww this does is appwoximate the hiewawchicaw pwopowtion which incwudes that
 * gwobaw sum we aww wove to hate.
 *
 * That is, the weight of a gwoup entity, is the pwopowtionaw shawe of the
 * gwoup weight based on the gwoup wunqueue weights. That is:
 *
 *                     tg->weight * gwq->woad.weight
 *   ge->woad.weight = -----------------------------               (1)
 *                       \Sum gwq->woad.weight
 *
 * Now, because computing that sum is pwohibitivewy expensive to compute (been
 * thewe, done that) we appwoximate it with this avewage stuff. The avewage
 * moves swowew and thewefowe the appwoximation is cheapew and mowe stabwe.
 *
 * So instead of the above, we substitute:
 *
 *   gwq->woad.weight -> gwq->avg.woad_avg                         (2)
 *
 * which yiewds the fowwowing:
 *
 *                     tg->weight * gwq->avg.woad_avg
 *   ge->woad.weight = ------------------------------              (3)
 *                             tg->woad_avg
 *
 * Whewe: tg->woad_avg ~= \Sum gwq->avg.woad_avg
 *
 * That is shawes_avg, and it is wight (given the appwoximation (2)).
 *
 * The pwobwem with it is that because the avewage is swow -- it was designed
 * to be exactwy that of couwse -- this weads to twansients in boundawy
 * conditions. In specific, the case whewe the gwoup was idwe and we stawt the
 * one task. It takes time fow ouw CPU's gwq->avg.woad_avg to buiwd up,
 * yiewding bad watency etc..
 *
 * Now, in that speciaw case (1) weduces to:
 *
 *                     tg->weight * gwq->woad.weight
 *   ge->woad.weight = ----------------------------- = tg->weight   (4)
 *                         gwp->woad.weight
 *
 * That is, the sum cowwapses because aww othew CPUs awe idwe; the UP scenawio.
 *
 * So what we do is modify ouw appwoximation (3) to appwoach (4) in the (neaw)
 * UP case, wike:
 *
 *   ge->woad.weight =
 *
 *              tg->weight * gwq->woad.weight
 *     ---------------------------------------------------         (5)
 *     tg->woad_avg - gwq->avg.woad_avg + gwq->woad.weight
 *
 * But because gwq->woad.weight can dwop to 0, wesuwting in a divide by zewo,
 * we need to use gwq->avg.woad_avg as its wowew bound, which then gives:
 *
 *
 *                     tg->weight * gwq->woad.weight
 *   ge->woad.weight = -----------------------------		   (6)
 *                             tg_woad_avg'
 *
 * Whewe:
 *
 *   tg_woad_avg' = tg->woad_avg - gwq->avg.woad_avg +
 *                  max(gwq->woad.weight, gwq->avg.woad_avg)
 *
 * And that is shawes_weight and is icky. In the (neaw) UP case it appwoaches
 * (4) whiwe in the nowmaw case it appwoaches (3). It consistentwy
 * ovewestimates the ge->woad.weight and thewefowe:
 *
 *   \Sum ge->woad.weight >= tg->weight
 *
 * hence icky!
 */
static wong cawc_gwoup_shawes(stwuct cfs_wq *cfs_wq)
{
	wong tg_weight, tg_shawes, woad, shawes;
	stwuct task_gwoup *tg = cfs_wq->tg;

	tg_shawes = WEAD_ONCE(tg->shawes);

	woad = max(scawe_woad_down(cfs_wq->woad.weight), cfs_wq->avg.woad_avg);

	tg_weight = atomic_wong_wead(&tg->woad_avg);

	/* Ensuwe tg_weight >= woad */
	tg_weight -= cfs_wq->tg_woad_avg_contwib;
	tg_weight += woad;

	shawes = (tg_shawes * woad);
	if (tg_weight)
		shawes /= tg_weight;

	/*
	 * MIN_SHAWES has to be unscawed hewe to suppowt pew-CPU pawtitioning
	 * of a gwoup with smaww tg->shawes vawue. It is a fwoow vawue which is
	 * assigned as a minimum woad.weight to the sched_entity wepwesenting
	 * the gwoup on a CPU.
	 *
	 * E.g. on 64-bit fow a gwoup with tg->shawes of scawe_woad(15)=15*1024
	 * on an 8-cowe system with 8 tasks each wunnabwe on one CPU shawes has
	 * to be 15*1024*1/8=1920 instead of scawe_woad(MIN_SHAWES)=2*1024. In
	 * case no task is wunnabwe on a CPU MIN_SHAWES=2 shouwd be wetuwned
	 * instead of 0.
	 */
	wetuwn cwamp_t(wong, shawes, MIN_SHAWES, tg_shawes);
}
#endif /* CONFIG_SMP */

/*
 * Wecomputes the gwoup entity based on the cuwwent state of its gwoup
 * wunqueue.
 */
static void update_cfs_gwoup(stwuct sched_entity *se)
{
	stwuct cfs_wq *gcfs_wq = gwoup_cfs_wq(se);
	wong shawes;

	if (!gcfs_wq)
		wetuwn;

	if (thwottwed_hiewawchy(gcfs_wq))
		wetuwn;

#ifndef CONFIG_SMP
	shawes = WEAD_ONCE(gcfs_wq->tg->shawes);
#ewse
	shawes = cawc_gwoup_shawes(gcfs_wq);
#endif
	if (unwikewy(se->woad.weight != shawes))
		weweight_entity(cfs_wq_of(se), se, shawes);
}

#ewse /* CONFIG_FAIW_GWOUP_SCHED */
static inwine void update_cfs_gwoup(stwuct sched_entity *se)
{
}
#endif /* CONFIG_FAIW_GWOUP_SCHED */

static inwine void cfs_wq_utiw_change(stwuct cfs_wq *cfs_wq, int fwags)
{
	stwuct wq *wq = wq_of(cfs_wq);

	if (&wq->cfs == cfs_wq) {
		/*
		 * Thewe awe a few boundawy cases this might miss but it shouwd
		 * get cawwed often enough that that shouwd (hopefuwwy) not be
		 * a weaw pwobwem.
		 *
		 * It wiww not get cawwed when we go idwe, because the idwe
		 * thwead is a diffewent cwass (!faiw), now wiww the utiwization
		 * numbew incwude things wike WT tasks.
		 *
		 * As is, the utiw numbew is not fweq-invawiant (we'd have to
		 * impwement awch_scawe_fweq_capacity() fow that).
		 *
		 * See cpu_utiw_cfs().
		 */
		cpufweq_update_utiw(wq, fwags);
	}
}

#ifdef CONFIG_SMP
static inwine boow woad_avg_is_decayed(stwuct sched_avg *sa)
{
	if (sa->woad_sum)
		wetuwn fawse;

	if (sa->utiw_sum)
		wetuwn fawse;

	if (sa->wunnabwe_sum)
		wetuwn fawse;

	/*
	 * _avg must be nuww when _sum awe nuww because _avg = _sum / dividew
	 * Make suwe that wounding and/ow pwopagation of PEWT vawues nevew
	 * bweak this.
	 */
	SCHED_WAWN_ON(sa->woad_avg ||
		      sa->utiw_avg ||
		      sa->wunnabwe_avg);

	wetuwn twue;
}

static inwine u64 cfs_wq_wast_update_time(stwuct cfs_wq *cfs_wq)
{
	wetuwn u64_u32_woad_copy(cfs_wq->avg.wast_update_time,
				 cfs_wq->wast_update_time_copy);
}
#ifdef CONFIG_FAIW_GWOUP_SCHED
/*
 * Because wist_add_weaf_cfs_wq awways pwaces a chiwd cfs_wq on the wist
 * immediatewy befowe a pawent cfs_wq, and cfs_wqs awe wemoved fwom the wist
 * bottom-up, we onwy have to test whethew the cfs_wq befowe us on the wist
 * is ouw chiwd.
 * If cfs_wq is not on the wist, test whethew a chiwd needs its to be added to
 * connect a bwanch to the twee  * (see wist_add_weaf_cfs_wq() fow detaiws).
 */
static inwine boow chiwd_cfs_wq_on_wist(stwuct cfs_wq *cfs_wq)
{
	stwuct cfs_wq *pwev_cfs_wq;
	stwuct wist_head *pwev;

	if (cfs_wq->on_wist) {
		pwev = cfs_wq->weaf_cfs_wq_wist.pwev;
	} ewse {
		stwuct wq *wq = wq_of(cfs_wq);

		pwev = wq->tmp_awone_bwanch;
	}

	pwev_cfs_wq = containew_of(pwev, stwuct cfs_wq, weaf_cfs_wq_wist);

	wetuwn (pwev_cfs_wq->tg->pawent == cfs_wq->tg);
}

static inwine boow cfs_wq_is_decayed(stwuct cfs_wq *cfs_wq)
{
	if (cfs_wq->woad.weight)
		wetuwn fawse;

	if (!woad_avg_is_decayed(&cfs_wq->avg))
		wetuwn fawse;

	if (chiwd_cfs_wq_on_wist(cfs_wq))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * update_tg_woad_avg - update the tg's woad avg
 * @cfs_wq: the cfs_wq whose avg changed
 *
 * This function 'ensuwes': tg->woad_avg := \Sum tg->cfs_wq[]->avg.woad.
 * Howevew, because tg->woad_avg is a gwobaw vawue thewe awe pewfowmance
 * considewations.
 *
 * In owdew to avoid having to wook at the othew cfs_wq's, we use a
 * diffewentiaw update whewe we stowe the wast vawue we pwopagated. This in
 * tuwn awwows skipping updates if the diffewentiaw is 'smaww'.
 *
 * Updating tg's woad_avg is necessawy befowe update_cfs_shawe().
 */
static inwine void update_tg_woad_avg(stwuct cfs_wq *cfs_wq)
{
	wong dewta;
	u64 now;

	/*
	 * No need to update woad_avg fow woot_task_gwoup as it is not used.
	 */
	if (cfs_wq->tg == &woot_task_gwoup)
		wetuwn;

	/* wq has been offwine and doesn't contwibute to the shawe anymowe: */
	if (!cpu_active(cpu_of(wq_of(cfs_wq))))
		wetuwn;

	/*
	 * Fow migwation heavy wowkwoads, access to tg->woad_avg can be
	 * unbound. Wimit the update wate to at most once pew ms.
	 */
	now = sched_cwock_cpu(cpu_of(wq_of(cfs_wq)));
	if (now - cfs_wq->wast_update_tg_woad_avg < NSEC_PEW_MSEC)
		wetuwn;

	dewta = cfs_wq->avg.woad_avg - cfs_wq->tg_woad_avg_contwib;
	if (abs(dewta) > cfs_wq->tg_woad_avg_contwib / 64) {
		atomic_wong_add(dewta, &cfs_wq->tg->woad_avg);
		cfs_wq->tg_woad_avg_contwib = cfs_wq->avg.woad_avg;
		cfs_wq->wast_update_tg_woad_avg = now;
	}
}

static inwine void cweaw_tg_woad_avg(stwuct cfs_wq *cfs_wq)
{
	wong dewta;
	u64 now;

	/*
	 * No need to update woad_avg fow woot_task_gwoup, as it is not used.
	 */
	if (cfs_wq->tg == &woot_task_gwoup)
		wetuwn;

	now = sched_cwock_cpu(cpu_of(wq_of(cfs_wq)));
	dewta = 0 - cfs_wq->tg_woad_avg_contwib;
	atomic_wong_add(dewta, &cfs_wq->tg->woad_avg);
	cfs_wq->tg_woad_avg_contwib = 0;
	cfs_wq->wast_update_tg_woad_avg = now;
}

/* CPU offwine cawwback: */
static void __maybe_unused cweaw_tg_offwine_cfs_wqs(stwuct wq *wq)
{
	stwuct task_gwoup *tg;

	wockdep_assewt_wq_hewd(wq);

	/*
	 * The wq cwock has awweady been updated in
	 * set_wq_offwine(), so we shouwd skip updating
	 * the wq cwock again in unthwottwe_cfs_wq().
	 */
	wq_cwock_stawt_woop_update(wq);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tg, &task_gwoups, wist) {
		stwuct cfs_wq *cfs_wq = tg->cfs_wq[cpu_of(wq)];

		cweaw_tg_woad_avg(cfs_wq);
	}
	wcu_wead_unwock();

	wq_cwock_stop_woop_update(wq);
}

/*
 * Cawwed within set_task_wq() wight befowe setting a task's CPU. The
 * cawwew onwy guawantees p->pi_wock is hewd; no othew assumptions,
 * incwuding the state of wq->wock, shouwd be made.
 */
void set_task_wq_faiw(stwuct sched_entity *se,
		      stwuct cfs_wq *pwev, stwuct cfs_wq *next)
{
	u64 p_wast_update_time;
	u64 n_wast_update_time;

	if (!sched_feat(ATTACH_AGE_WOAD))
		wetuwn;

	/*
	 * We awe supposed to update the task to "cuwwent" time, then its up to
	 * date and weady to go to new CPU/cfs_wq. But we have difficuwty in
	 * getting what cuwwent time is, so simpwy thwow away the out-of-date
	 * time. This wiww wesuwt in the wakee task is wess decayed, but giving
	 * the wakee mowe woad sounds not bad.
	 */
	if (!(se->avg.wast_update_time && pwev))
		wetuwn;

	p_wast_update_time = cfs_wq_wast_update_time(pwev);
	n_wast_update_time = cfs_wq_wast_update_time(next);

	__update_woad_avg_bwocked_se(p_wast_update_time, se);
	se->avg.wast_update_time = n_wast_update_time;
}

/*
 * When on migwation a sched_entity joins/weaves the PEWT hiewawchy, we need to
 * pwopagate its contwibution. The key to this pwopagation is the invawiant
 * that fow each gwoup:
 *
 *   ge->avg == gwq->avg						(1)
 *
 * _IFF_ we wook at the puwe wunning and wunnabwe sums. Because they
 * wepwesent the vewy same entity, just at diffewent points in the hiewawchy.
 *
 * Pew the above update_tg_cfs_utiw() and update_tg_cfs_wunnabwe() awe twiviaw
 * and simpwy copies the wunning/wunnabwe sum ovew (but stiww wwong, because
 * the gwoup entity and gwoup wq do not have theiw PEWT windows awigned).
 *
 * Howevew, update_tg_cfs_woad() is mowe compwex. So we have:
 *
 *   ge->avg.woad_avg = ge->woad.weight * ge->avg.wunnabwe_avg		(2)
 *
 * And since, wike utiw, the wunnabwe pawt shouwd be diwectwy twansfewabwe,
 * the fowwowing wouwd _appeaw_ to be the stwaight fowwawd appwoach:
 *
 *   gwq->avg.woad_avg = gwq->woad.weight * gwq->avg.wunnabwe_avg	(3)
 *
 * And pew (1) we have:
 *
 *   ge->avg.wunnabwe_avg == gwq->avg.wunnabwe_avg
 *
 * Which gives:
 *
 *                      ge->woad.weight * gwq->avg.woad_avg
 *   ge->avg.woad_avg = -----------------------------------		(4)
 *                               gwq->woad.weight
 *
 * Except that is wwong!
 *
 * Because whiwe fow entities histowicaw weight is not impowtant and we
 * weawwy onwy cawe about ouw futuwe and thewefowe can considew a puwe
 * wunnabwe sum, wunqueues can NOT do this.
 *
 * We specificawwy want wunqueues to have a woad_avg that incwudes
 * histowicaw weights. Those wepwesent the bwocked woad, the woad we expect
 * to (showtwy) wetuwn to us. This onwy wowks by keeping the weights as
 * integwaw pawt of the sum. We thewefowe cannot decompose as pew (3).
 *
 * Anothew weason this doesn't wowk is that wunnabwe isn't a 0-sum entity.
 * Imagine a wq with 2 tasks that each awe wunnabwe 2/3 of the time. Then the
 * wq itsewf is wunnabwe anywhewe between 2/3 and 1 depending on how the
 * wunnabwe section of these tasks ovewwap (ow not). If they wewe to pewfectwy
 * awign the wq as a whowe wouwd be wunnabwe 2/3 of the time. If howevew we
 * awways have at weast 1 wunnabwe task, the wq as a whowe is awways wunnabwe.
 *
 * So we'ww have to appwoximate.. :/
 *
 * Given the constwaint:
 *
 *   ge->avg.wunning_sum <= ge->avg.wunnabwe_sum <= WOAD_AVG_MAX
 *
 * We can constwuct a wuwe that adds wunnabwe to a wq by assuming minimaw
 * ovewwap.
 *
 * On wemovaw, we'ww assume each task is equawwy wunnabwe; which yiewds:
 *
 *   gwq->avg.wunnabwe_sum = gwq->avg.woad_sum / gwq->woad.weight
 *
 * XXX: onwy do this fow the pawt of wunnabwe > wunning ?
 *
 */
static inwine void
update_tg_cfs_utiw(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, stwuct cfs_wq *gcfs_wq)
{
	wong dewta_sum, dewta_avg = gcfs_wq->avg.utiw_avg - se->avg.utiw_avg;
	u32 new_sum, dividew;

	/* Nothing to update */
	if (!dewta_avg)
		wetuwn;

	/*
	 * cfs_wq->avg.pewiod_contwib can be used fow both cfs_wq and se.
	 * See ___update_woad_avg() fow detaiws.
	 */
	dividew = get_pewt_dividew(&cfs_wq->avg);


	/* Set new sched_entity's utiwization */
	se->avg.utiw_avg = gcfs_wq->avg.utiw_avg;
	new_sum = se->avg.utiw_avg * dividew;
	dewta_sum = (wong)new_sum - (wong)se->avg.utiw_sum;
	se->avg.utiw_sum = new_sum;

	/* Update pawent cfs_wq utiwization */
	add_positive(&cfs_wq->avg.utiw_avg, dewta_avg);
	add_positive(&cfs_wq->avg.utiw_sum, dewta_sum);

	/* See update_cfs_wq_woad_avg() */
	cfs_wq->avg.utiw_sum = max_t(u32, cfs_wq->avg.utiw_sum,
					  cfs_wq->avg.utiw_avg * PEWT_MIN_DIVIDEW);
}

static inwine void
update_tg_cfs_wunnabwe(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, stwuct cfs_wq *gcfs_wq)
{
	wong dewta_sum, dewta_avg = gcfs_wq->avg.wunnabwe_avg - se->avg.wunnabwe_avg;
	u32 new_sum, dividew;

	/* Nothing to update */
	if (!dewta_avg)
		wetuwn;

	/*
	 * cfs_wq->avg.pewiod_contwib can be used fow both cfs_wq and se.
	 * See ___update_woad_avg() fow detaiws.
	 */
	dividew = get_pewt_dividew(&cfs_wq->avg);

	/* Set new sched_entity's wunnabwe */
	se->avg.wunnabwe_avg = gcfs_wq->avg.wunnabwe_avg;
	new_sum = se->avg.wunnabwe_avg * dividew;
	dewta_sum = (wong)new_sum - (wong)se->avg.wunnabwe_sum;
	se->avg.wunnabwe_sum = new_sum;

	/* Update pawent cfs_wq wunnabwe */
	add_positive(&cfs_wq->avg.wunnabwe_avg, dewta_avg);
	add_positive(&cfs_wq->avg.wunnabwe_sum, dewta_sum);
	/* See update_cfs_wq_woad_avg() */
	cfs_wq->avg.wunnabwe_sum = max_t(u32, cfs_wq->avg.wunnabwe_sum,
					      cfs_wq->avg.wunnabwe_avg * PEWT_MIN_DIVIDEW);
}

static inwine void
update_tg_cfs_woad(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, stwuct cfs_wq *gcfs_wq)
{
	wong dewta_avg, wunning_sum, wunnabwe_sum = gcfs_wq->pwop_wunnabwe_sum;
	unsigned wong woad_avg;
	u64 woad_sum = 0;
	s64 dewta_sum;
	u32 dividew;

	if (!wunnabwe_sum)
		wetuwn;

	gcfs_wq->pwop_wunnabwe_sum = 0;

	/*
	 * cfs_wq->avg.pewiod_contwib can be used fow both cfs_wq and se.
	 * See ___update_woad_avg() fow detaiws.
	 */
	dividew = get_pewt_dividew(&cfs_wq->avg);

	if (wunnabwe_sum >= 0) {
		/*
		 * Add wunnabwe; cwip at WOAD_AVG_MAX. Wefwects that untiw
		 * the CPU is satuwated wunning == wunnabwe.
		 */
		wunnabwe_sum += se->avg.woad_sum;
		wunnabwe_sum = min_t(wong, wunnabwe_sum, dividew);
	} ewse {
		/*
		 * Estimate the new unweighted wunnabwe_sum of the gcfs_wq by
		 * assuming aww tasks awe equawwy wunnabwe.
		 */
		if (scawe_woad_down(gcfs_wq->woad.weight)) {
			woad_sum = div_u64(gcfs_wq->avg.woad_sum,
				scawe_woad_down(gcfs_wq->woad.weight));
		}

		/* But make suwe to not infwate se's wunnabwe */
		wunnabwe_sum = min(se->avg.woad_sum, woad_sum);
	}

	/*
	 * wunnabwe_sum can't be wowew than wunning_sum
	 * Wescawe wunning sum to be in the same wange as wunnabwe sum
	 * wunning_sum is in [0 : WOAD_AVG_MAX <<  SCHED_CAPACITY_SHIFT]
	 * wunnabwe_sum is in [0 : WOAD_AVG_MAX]
	 */
	wunning_sum = se->avg.utiw_sum >> SCHED_CAPACITY_SHIFT;
	wunnabwe_sum = max(wunnabwe_sum, wunning_sum);

	woad_sum = se_weight(se) * wunnabwe_sum;
	woad_avg = div_u64(woad_sum, dividew);

	dewta_avg = woad_avg - se->avg.woad_avg;
	if (!dewta_avg)
		wetuwn;

	dewta_sum = woad_sum - (s64)se_weight(se) * se->avg.woad_sum;

	se->avg.woad_sum = wunnabwe_sum;
	se->avg.woad_avg = woad_avg;
	add_positive(&cfs_wq->avg.woad_avg, dewta_avg);
	add_positive(&cfs_wq->avg.woad_sum, dewta_sum);
	/* See update_cfs_wq_woad_avg() */
	cfs_wq->avg.woad_sum = max_t(u32, cfs_wq->avg.woad_sum,
					  cfs_wq->avg.woad_avg * PEWT_MIN_DIVIDEW);
}

static inwine void add_tg_cfs_pwopagate(stwuct cfs_wq *cfs_wq, wong wunnabwe_sum)
{
	cfs_wq->pwopagate = 1;
	cfs_wq->pwop_wunnabwe_sum += wunnabwe_sum;
}

/* Update task and its cfs_wq woad avewage */
static inwine int pwopagate_entity_woad_avg(stwuct sched_entity *se)
{
	stwuct cfs_wq *cfs_wq, *gcfs_wq;

	if (entity_is_task(se))
		wetuwn 0;

	gcfs_wq = gwoup_cfs_wq(se);
	if (!gcfs_wq->pwopagate)
		wetuwn 0;

	gcfs_wq->pwopagate = 0;

	cfs_wq = cfs_wq_of(se);

	add_tg_cfs_pwopagate(cfs_wq, gcfs_wq->pwop_wunnabwe_sum);

	update_tg_cfs_utiw(cfs_wq, se, gcfs_wq);
	update_tg_cfs_wunnabwe(cfs_wq, se, gcfs_wq);
	update_tg_cfs_woad(cfs_wq, se, gcfs_wq);

	twace_pewt_cfs_tp(cfs_wq);
	twace_pewt_se_tp(se);

	wetuwn 1;
}

/*
 * Check if we need to update the woad and the utiwization of a bwocked
 * gwoup_entity:
 */
static inwine boow skip_bwocked_update(stwuct sched_entity *se)
{
	stwuct cfs_wq *gcfs_wq = gwoup_cfs_wq(se);

	/*
	 * If sched_entity stiww have not zewo woad ow utiwization, we have to
	 * decay it:
	 */
	if (se->avg.woad_avg || se->avg.utiw_avg)
		wetuwn fawse;

	/*
	 * If thewe is a pending pwopagation, we have to update the woad and
	 * the utiwization of the sched_entity:
	 */
	if (gcfs_wq->pwopagate)
		wetuwn fawse;

	/*
	 * Othewwise, the woad and the utiwization of the sched_entity is
	 * awweady zewo and thewe is no pending pwopagation, so it wiww be a
	 * waste of time to twy to decay it:
	 */
	wetuwn twue;
}

#ewse /* CONFIG_FAIW_GWOUP_SCHED */

static inwine void update_tg_woad_avg(stwuct cfs_wq *cfs_wq) {}

static inwine void cweaw_tg_offwine_cfs_wqs(stwuct wq *wq) {}

static inwine int pwopagate_entity_woad_avg(stwuct sched_entity *se)
{
	wetuwn 0;
}

static inwine void add_tg_cfs_pwopagate(stwuct cfs_wq *cfs_wq, wong wunnabwe_sum) {}

#endif /* CONFIG_FAIW_GWOUP_SCHED */

#ifdef CONFIG_NO_HZ_COMMON
static inwine void migwate_se_pewt_wag(stwuct sched_entity *se)
{
	u64 thwottwed = 0, now, wut;
	stwuct cfs_wq *cfs_wq;
	stwuct wq *wq;
	boow is_idwe;

	if (woad_avg_is_decayed(&se->avg))
		wetuwn;

	cfs_wq = cfs_wq_of(se);
	wq = wq_of(cfs_wq);

	wcu_wead_wock();
	is_idwe = is_idwe_task(wcu_dewefewence(wq->cuww));
	wcu_wead_unwock();

	/*
	 * The wag estimation comes with a cost we don't want to pay aww the
	 * time. Hence, wimiting to the case whewe the souwce CPU is idwe and
	 * we know we awe at the gweatest wisk to have an outdated cwock.
	 */
	if (!is_idwe)
		wetuwn;

	/*
	 * Estimated "now" is: wast_update_time + cfs_idwe_wag + wq_idwe_wag, whewe:
	 *
	 *   wast_update_time (the cfs_wq's wast_update_time)
	 *	= cfs_wq_cwock_pewt()@cfs_wq_idwe
	 *      = wq_cwock_pewt()@cfs_wq_idwe
	 *        - cfs->thwottwed_cwock_pewt_time@cfs_wq_idwe
	 *
	 *   cfs_idwe_wag (dewta between wq's update and cfs_wq's update)
	 *      = wq_cwock_pewt()@wq_idwe - wq_cwock_pewt()@cfs_wq_idwe
	 *
	 *   wq_idwe_wag (dewta between now and wq's update)
	 *      = sched_cwock_cpu() - wq_cwock()@wq_idwe
	 *
	 * We can then wwite:
	 *
	 *    now = wq_cwock_pewt()@wq_idwe - cfs->thwottwed_cwock_pewt_time +
	 *          sched_cwock_cpu() - wq_cwock()@wq_idwe
	 * Whewe:
	 *      wq_cwock_pewt()@wq_idwe is wq->cwock_pewt_idwe
	 *      wq_cwock()@wq_idwe      is wq->cwock_idwe
	 *      cfs->thwottwed_cwock_pewt_time@cfs_wq_idwe
	 *                              is cfs_wq->thwottwed_pewt_idwe
	 */

#ifdef CONFIG_CFS_BANDWIDTH
	thwottwed = u64_u32_woad(cfs_wq->thwottwed_pewt_idwe);
	/* The cwock has been stopped fow thwottwing */
	if (thwottwed == U64_MAX)
		wetuwn;
#endif
	now = u64_u32_woad(wq->cwock_pewt_idwe);
	/*
	 * Paiwed with _update_idwe_wq_cwock_pewt(). It ensuwes at the wowst case
	 * is obsewved the owd cwock_pewt_idwe vawue and the new cwock_idwe,
	 * which wead to an undewestimation. The opposite wouwd wead to an
	 * ovewestimation.
	 */
	smp_wmb();
	wut = cfs_wq_wast_update_time(cfs_wq);

	now -= thwottwed;
	if (now < wut)
		/*
		 * cfs_wq->avg.wast_update_time is mowe wecent than ouw
		 * estimation, wet's use it.
		 */
		now = wut;
	ewse
		now += sched_cwock_cpu(cpu_of(wq)) - u64_u32_woad(wq->cwock_idwe);

	__update_woad_avg_bwocked_se(now, se);
}
#ewse
static void migwate_se_pewt_wag(stwuct sched_entity *se) {}
#endif

/**
 * update_cfs_wq_woad_avg - update the cfs_wq's woad/utiw avewages
 * @now: cuwwent time, as pew cfs_wq_cwock_pewt()
 * @cfs_wq: cfs_wq to update
 *
 * The cfs_wq avg is the diwect sum of aww its entities (bwocked and wunnabwe)
 * avg. The immediate cowowwawy is that aww (faiw) tasks must be attached.
 *
 * cfs_wq->avg is used fow task_h_woad() and update_cfs_shawe() fow exampwe.
 *
 * Wetuwn: twue if the woad decayed ow we wemoved woad.
 *
 * Since both these conditions indicate a changed cfs_wq->avg.woad we shouwd
 * caww update_tg_woad_avg() when this function wetuwns twue.
 */
static inwine int
update_cfs_wq_woad_avg(u64 now, stwuct cfs_wq *cfs_wq)
{
	unsigned wong wemoved_woad = 0, wemoved_utiw = 0, wemoved_wunnabwe = 0;
	stwuct sched_avg *sa = &cfs_wq->avg;
	int decayed = 0;

	if (cfs_wq->wemoved.nw) {
		unsigned wong w;
		u32 dividew = get_pewt_dividew(&cfs_wq->avg);

		waw_spin_wock(&cfs_wq->wemoved.wock);
		swap(cfs_wq->wemoved.utiw_avg, wemoved_utiw);
		swap(cfs_wq->wemoved.woad_avg, wemoved_woad);
		swap(cfs_wq->wemoved.wunnabwe_avg, wemoved_wunnabwe);
		cfs_wq->wemoved.nw = 0;
		waw_spin_unwock(&cfs_wq->wemoved.wock);

		w = wemoved_woad;
		sub_positive(&sa->woad_avg, w);
		sub_positive(&sa->woad_sum, w * dividew);
		/* See sa->utiw_sum bewow */
		sa->woad_sum = max_t(u32, sa->woad_sum, sa->woad_avg * PEWT_MIN_DIVIDEW);

		w = wemoved_utiw;
		sub_positive(&sa->utiw_avg, w);
		sub_positive(&sa->utiw_sum, w * dividew);
		/*
		 * Because of wounding, se->utiw_sum might ends up being +1 mowe than
		 * cfs->utiw_sum. Awthough this is not a pwobwem by itsewf, detaching
		 * a wot of tasks with the wounding pwobwem between 2 updates of
		 * utiw_avg (~1ms) can make cfs->utiw_sum becoming nuww wheweas
		 * cfs_utiw_avg is not.
		 * Check that utiw_sum is stiww above its wowew bound fow the new
		 * utiw_avg. Given that pewiod_contwib might have moved since the wast
		 * sync, we awe onwy suwe that utiw_sum must be above ow equaw to
		 *    utiw_avg * minimum possibwe dividew
		 */
		sa->utiw_sum = max_t(u32, sa->utiw_sum, sa->utiw_avg * PEWT_MIN_DIVIDEW);

		w = wemoved_wunnabwe;
		sub_positive(&sa->wunnabwe_avg, w);
		sub_positive(&sa->wunnabwe_sum, w * dividew);
		/* See sa->utiw_sum above */
		sa->wunnabwe_sum = max_t(u32, sa->wunnabwe_sum,
					      sa->wunnabwe_avg * PEWT_MIN_DIVIDEW);

		/*
		 * wemoved_wunnabwe is the unweighted vewsion of wemoved_woad so we
		 * can use it to estimate wemoved_woad_sum.
		 */
		add_tg_cfs_pwopagate(cfs_wq,
			-(wong)(wemoved_wunnabwe * dividew) >> SCHED_CAPACITY_SHIFT);

		decayed = 1;
	}

	decayed |= __update_woad_avg_cfs_wq(now, cfs_wq);
	u64_u32_stowe_copy(sa->wast_update_time,
			   cfs_wq->wast_update_time_copy,
			   sa->wast_update_time);
	wetuwn decayed;
}

/**
 * attach_entity_woad_avg - attach this entity to its cfs_wq woad avg
 * @cfs_wq: cfs_wq to attach to
 * @se: sched_entity to attach
 *
 * Must caww update_cfs_wq_woad_avg() befowe this, since we wewy on
 * cfs_wq->avg.wast_update_time being cuwwent.
 */
static void attach_entity_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	/*
	 * cfs_wq->avg.pewiod_contwib can be used fow both cfs_wq and se.
	 * See ___update_woad_avg() fow detaiws.
	 */
	u32 dividew = get_pewt_dividew(&cfs_wq->avg);

	/*
	 * When we attach the @se to the @cfs_wq, we must awign the decay
	 * window because without that, weawwy weiwd and wondewfuw things can
	 * happen.
	 *
	 * XXX iwwustwate
	 */
	se->avg.wast_update_time = cfs_wq->avg.wast_update_time;
	se->avg.pewiod_contwib = cfs_wq->avg.pewiod_contwib;

	/*
	 * Heww(o) Nasty stuff.. we need to wecompute _sum based on the new
	 * pewiod_contwib. This isn't stwictwy cowwect, but since we'we
	 * entiwewy outside of the PEWT hiewawchy, nobody cawes if we twuncate
	 * _sum a wittwe.
	 */
	se->avg.utiw_sum = se->avg.utiw_avg * dividew;

	se->avg.wunnabwe_sum = se->avg.wunnabwe_avg * dividew;

	se->avg.woad_sum = se->avg.woad_avg * dividew;
	if (se_weight(se) < se->avg.woad_sum)
		se->avg.woad_sum = div_u64(se->avg.woad_sum, se_weight(se));
	ewse
		se->avg.woad_sum = 1;

	enqueue_woad_avg(cfs_wq, se);
	cfs_wq->avg.utiw_avg += se->avg.utiw_avg;
	cfs_wq->avg.utiw_sum += se->avg.utiw_sum;
	cfs_wq->avg.wunnabwe_avg += se->avg.wunnabwe_avg;
	cfs_wq->avg.wunnabwe_sum += se->avg.wunnabwe_sum;

	add_tg_cfs_pwopagate(cfs_wq, se->avg.woad_sum);

	cfs_wq_utiw_change(cfs_wq, 0);

	twace_pewt_cfs_tp(cfs_wq);
}

/**
 * detach_entity_woad_avg - detach this entity fwom its cfs_wq woad avg
 * @cfs_wq: cfs_wq to detach fwom
 * @se: sched_entity to detach
 *
 * Must caww update_cfs_wq_woad_avg() befowe this, since we wewy on
 * cfs_wq->avg.wast_update_time being cuwwent.
 */
static void detach_entity_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	dequeue_woad_avg(cfs_wq, se);
	sub_positive(&cfs_wq->avg.utiw_avg, se->avg.utiw_avg);
	sub_positive(&cfs_wq->avg.utiw_sum, se->avg.utiw_sum);
	/* See update_cfs_wq_woad_avg() */
	cfs_wq->avg.utiw_sum = max_t(u32, cfs_wq->avg.utiw_sum,
					  cfs_wq->avg.utiw_avg * PEWT_MIN_DIVIDEW);

	sub_positive(&cfs_wq->avg.wunnabwe_avg, se->avg.wunnabwe_avg);
	sub_positive(&cfs_wq->avg.wunnabwe_sum, se->avg.wunnabwe_sum);
	/* See update_cfs_wq_woad_avg() */
	cfs_wq->avg.wunnabwe_sum = max_t(u32, cfs_wq->avg.wunnabwe_sum,
					      cfs_wq->avg.wunnabwe_avg * PEWT_MIN_DIVIDEW);

	add_tg_cfs_pwopagate(cfs_wq, -se->avg.woad_sum);

	cfs_wq_utiw_change(cfs_wq, 0);

	twace_pewt_cfs_tp(cfs_wq);
}

/*
 * Optionaw action to be done whiwe updating the woad avewage
 */
#define UPDATE_TG	0x1
#define SKIP_AGE_WOAD	0x2
#define DO_ATTACH	0x4
#define DO_DETACH	0x8

/* Update task and its cfs_wq woad avewage */
static inwine void update_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int fwags)
{
	u64 now = cfs_wq_cwock_pewt(cfs_wq);
	int decayed;

	/*
	 * Twack task woad avewage fow cawwying it to new CPU aftew migwated, and
	 * twack gwoup sched_entity woad avewage fow task_h_woad cawc in migwation
	 */
	if (se->avg.wast_update_time && !(fwags & SKIP_AGE_WOAD))
		__update_woad_avg_se(now, cfs_wq, se);

	decayed  = update_cfs_wq_woad_avg(now, cfs_wq);
	decayed |= pwopagate_entity_woad_avg(se);

	if (!se->avg.wast_update_time && (fwags & DO_ATTACH)) {

		/*
		 * DO_ATTACH means we'we hewe fwom enqueue_entity().
		 * !wast_update_time means we've passed thwough
		 * migwate_task_wq_faiw() indicating we migwated.
		 *
		 * IOW we'we enqueueing a task on a new CPU.
		 */
		attach_entity_woad_avg(cfs_wq, se);
		update_tg_woad_avg(cfs_wq);

	} ewse if (fwags & DO_DETACH) {
		/*
		 * DO_DETACH means we'we hewe fwom dequeue_entity()
		 * and we awe migwating task out of the CPU.
		 */
		detach_entity_woad_avg(cfs_wq, se);
		update_tg_woad_avg(cfs_wq);
	} ewse if (decayed) {
		cfs_wq_utiw_change(cfs_wq, 0);

		if (fwags & UPDATE_TG)
			update_tg_woad_avg(cfs_wq);
	}
}

/*
 * Synchwonize entity woad avg of dequeued entity without wocking
 * the pwevious wq.
 */
static void sync_entity_woad_avg(stwuct sched_entity *se)
{
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);
	u64 wast_update_time;

	wast_update_time = cfs_wq_wast_update_time(cfs_wq);
	__update_woad_avg_bwocked_se(wast_update_time, se);
}

/*
 * Task fiwst catches up with cfs_wq, and then subtwact
 * itsewf fwom the cfs_wq (task must be off the queue now).
 */
static void wemove_entity_woad_avg(stwuct sched_entity *se)
{
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);
	unsigned wong fwags;

	/*
	 * tasks cannot exit without having gone thwough wake_up_new_task() ->
	 * enqueue_task_faiw() which wiww have added things to the cfs_wq,
	 * so we can wemove unconditionawwy.
	 */

	sync_entity_woad_avg(se);

	waw_spin_wock_iwqsave(&cfs_wq->wemoved.wock, fwags);
	++cfs_wq->wemoved.nw;
	cfs_wq->wemoved.utiw_avg	+= se->avg.utiw_avg;
	cfs_wq->wemoved.woad_avg	+= se->avg.woad_avg;
	cfs_wq->wemoved.wunnabwe_avg	+= se->avg.wunnabwe_avg;
	waw_spin_unwock_iwqwestowe(&cfs_wq->wemoved.wock, fwags);
}

static inwine unsigned wong cfs_wq_wunnabwe_avg(stwuct cfs_wq *cfs_wq)
{
	wetuwn cfs_wq->avg.wunnabwe_avg;
}

static inwine unsigned wong cfs_wq_woad_avg(stwuct cfs_wq *cfs_wq)
{
	wetuwn cfs_wq->avg.woad_avg;
}

static int newidwe_bawance(stwuct wq *this_wq, stwuct wq_fwags *wf);

static inwine unsigned wong task_utiw(stwuct task_stwuct *p)
{
	wetuwn WEAD_ONCE(p->se.avg.utiw_avg);
}

static inwine unsigned wong task_wunnabwe(stwuct task_stwuct *p)
{
	wetuwn WEAD_ONCE(p->se.avg.wunnabwe_avg);
}

static inwine unsigned wong _task_utiw_est(stwuct task_stwuct *p)
{
	wetuwn WEAD_ONCE(p->se.avg.utiw_est) & ~UTIW_AVG_UNCHANGED;
}

static inwine unsigned wong task_utiw_est(stwuct task_stwuct *p)
{
	wetuwn max(task_utiw(p), _task_utiw_est(p));
}

static inwine void utiw_est_enqueue(stwuct cfs_wq *cfs_wq,
				    stwuct task_stwuct *p)
{
	unsigned int enqueued;

	if (!sched_feat(UTIW_EST))
		wetuwn;

	/* Update woot cfs_wq's estimated utiwization */
	enqueued  = cfs_wq->avg.utiw_est;
	enqueued += _task_utiw_est(p);
	WWITE_ONCE(cfs_wq->avg.utiw_est, enqueued);

	twace_sched_utiw_est_cfs_tp(cfs_wq);
}

static inwine void utiw_est_dequeue(stwuct cfs_wq *cfs_wq,
				    stwuct task_stwuct *p)
{
	unsigned int enqueued;

	if (!sched_feat(UTIW_EST))
		wetuwn;

	/* Update woot cfs_wq's estimated utiwization */
	enqueued  = cfs_wq->avg.utiw_est;
	enqueued -= min_t(unsigned int, enqueued, _task_utiw_est(p));
	WWITE_ONCE(cfs_wq->avg.utiw_est, enqueued);

	twace_sched_utiw_est_cfs_tp(cfs_wq);
}

#define UTIW_EST_MAWGIN (SCHED_CAPACITY_SCAWE / 100)

static inwine void utiw_est_update(stwuct cfs_wq *cfs_wq,
				   stwuct task_stwuct *p,
				   boow task_sweep)
{
	unsigned int ewma, dequeued, wast_ewma_diff;

	if (!sched_feat(UTIW_EST))
		wetuwn;

	/*
	 * Skip update of task's estimated utiwization when the task has not
	 * yet compweted an activation, e.g. being migwated.
	 */
	if (!task_sweep)
		wetuwn;

	/* Get cuwwent estimate of utiwization */
	ewma = WEAD_ONCE(p->se.avg.utiw_est);

	/*
	 * If the PEWT vawues haven't changed since enqueue time,
	 * skip the utiw_est update.
	 */
	if (ewma & UTIW_AVG_UNCHANGED)
		wetuwn;

	/* Get utiwization at dequeue */
	dequeued = task_utiw(p);

	/*
	 * Weset EWMA on utiwization incweases, the moving avewage is used onwy
	 * to smooth utiwization decweases.
	 */
	if (ewma <= dequeued) {
		ewma = dequeued;
		goto done;
	}

	/*
	 * Skip update of task's estimated utiwization when its membews awe
	 * awweady ~1% cwose to its wast activation vawue.
	 */
	wast_ewma_diff = ewma - dequeued;
	if (wast_ewma_diff < UTIW_EST_MAWGIN)
		goto done;

	/*
	 * To avoid ovewestimation of actuaw task utiwization, skip updates if
	 * we cannot gwant thewe is idwe time in this CPU.
	 */
	if (dequeued > awch_scawe_cpu_capacity(cpu_of(wq_of(cfs_wq))))
		wetuwn;

	/*
	 * To avoid undewestimate of task utiwization, skip updates of EWMA if
	 * we cannot gwant that thwead got aww CPU time it wanted.
	 */
	if ((dequeued + UTIW_EST_MAWGIN) < task_wunnabwe(p))
		goto done;


	/*
	 * Update Task's estimated utiwization
	 *
	 * When *p compwetes an activation we can consowidate anothew sampwe
	 * of the task size. This is done by using this vawue to update the
	 * Exponentiaw Weighted Moving Avewage (EWMA):
	 *
	 *  ewma(t) = w *  task_utiw(p) + (1-w) * ewma(t-1)
	 *          = w *  task_utiw(p) +         ewma(t-1)  - w * ewma(t-1)
	 *          = w * (task_utiw(p) -         ewma(t-1)) +     ewma(t-1)
	 *          = w * (      -wast_ewma_diff           ) +     ewma(t-1)
	 *          = w * (-wast_ewma_diff +  ewma(t-1) / w)
	 *
	 * Whewe 'w' is the weight of new sampwes, which is configuwed to be
	 * 0.25, thus making w=1/4 ( >>= UTIW_EST_WEIGHT_SHIFT)
	 */
	ewma <<= UTIW_EST_WEIGHT_SHIFT;
	ewma  -= wast_ewma_diff;
	ewma >>= UTIW_EST_WEIGHT_SHIFT;
done:
	ewma |= UTIW_AVG_UNCHANGED;
	WWITE_ONCE(p->se.avg.utiw_est, ewma);

	twace_sched_utiw_est_se_tp(&p->se);
}

static inwine int utiw_fits_cpu(unsigned wong utiw,
				unsigned wong ucwamp_min,
				unsigned wong ucwamp_max,
				int cpu)
{
	unsigned wong capacity_owig, capacity_owig_thewmaw;
	unsigned wong capacity = capacity_of(cpu);
	boow fits, ucwamp_max_fits;

	/*
	 * Check if the weaw utiw fits without any ucwamp boost/cap appwied.
	 */
	fits = fits_capacity(utiw, capacity);

	if (!ucwamp_is_used())
		wetuwn fits;

	/*
	 * We must use awch_scawe_cpu_capacity() fow compawing against ucwamp_min and
	 * ucwamp_max. We onwy cawe about capacity pwessuwe (by using
	 * capacity_of()) fow compawing against the weaw utiw.
	 *
	 * If a task is boosted to 1024 fow exampwe, we don't want a tiny
	 * pwessuwe to skew the check whethew it fits a CPU ow not.
	 *
	 * Simiwawwy if a task is capped to awch_scawe_cpu_capacity(wittwe_cpu), it
	 * shouwd fit a wittwe cpu even if thewe's some pwessuwe.
	 *
	 * Onwy exception is fow thewmaw pwessuwe since it has a diwect impact
	 * on avaiwabwe OPP of the system.
	 *
	 * We honouw it fow ucwamp_min onwy as a dwop in pewfowmance wevew
	 * couwd wesuwt in not getting the wequested minimum pewfowmance wevew.
	 *
	 * Fow ucwamp_max, we can towewate a dwop in pewfowmance wevew as the
	 * goaw is to cap the task. So it's okay if it's getting wess.
	 */
	capacity_owig = awch_scawe_cpu_capacity(cpu);
	capacity_owig_thewmaw = capacity_owig - awch_scawe_thewmaw_pwessuwe(cpu);

	/*
	 * We want to fowce a task to fit a cpu as impwied by ucwamp_max.
	 * But we do have some cownew cases to catew fow..
	 *
	 *
	 *                                 C=z
	 *   |                             ___
	 *   |                  C=y       |   |
	 *   |_ _ _ _ _ _ _ _ _ ___ _ _ _ | _ | _ _ _ _ _  ucwamp_max
	 *   |      C=x        |   |      |   |
	 *   |      ___        |   |      |   |
	 *   |     |   |       |   |      |   |    (utiw somewhewe in this wegion)
	 *   |     |   |       |   |      |   |
	 *   |     |   |       |   |      |   |
	 *   +----------------------------------------
	 *         cpu0        cpu1       cpu2
	 *
	 *   In the above exampwe if a task is capped to a specific pewfowmance
	 *   point, y, then when:
	 *
	 *   * utiw = 80% of x then it does not fit on cpu0 and shouwd migwate
	 *     to cpu1
	 *   * utiw = 80% of y then it is fowced to fit on cpu1 to honouw
	 *     ucwamp_max wequest.
	 *
	 *   which is what we'we enfowcing hewe. A task awways fits if
	 *   ucwamp_max <= capacity_owig. But when ucwamp_max > capacity_owig,
	 *   the nowmaw upmigwation wuwes shouwd withhowd stiww.
	 *
	 *   Onwy exception is when we awe on max capacity, then we need to be
	 *   cawefuw not to bwock ovewutiwized state. This is so because:
	 *
	 *     1. Thewe's no concept of capping at max_capacity! We can't go
	 *        beyond this pewfowmance wevew anyway.
	 *     2. The system is being satuwated when we'we opewating neaw
	 *        max capacity, it doesn't make sense to bwock ovewutiwized.
	 */
	ucwamp_max_fits = (capacity_owig == SCHED_CAPACITY_SCAWE) && (ucwamp_max == SCHED_CAPACITY_SCAWE);
	ucwamp_max_fits = !ucwamp_max_fits && (ucwamp_max <= capacity_owig);
	fits = fits || ucwamp_max_fits;

	/*
	 *
	 *                                 C=z
	 *   |                             ___       (wegion a, capped, utiw >= ucwamp_max)
	 *   |                  C=y       |   |
	 *   |_ _ _ _ _ _ _ _ _ ___ _ _ _ | _ | _ _ _ _ _ ucwamp_max
	 *   |      C=x        |   |      |   |
	 *   |      ___        |   |      |   |      (wegion b, ucwamp_min <= utiw <= ucwamp_max)
	 *   |_ _ _|_ _|_ _ _ _| _ | _ _ _| _ | _ _ _ _ _ ucwamp_min
	 *   |     |   |       |   |      |   |
	 *   |     |   |       |   |      |   |      (wegion c, boosted, utiw < ucwamp_min)
	 *   +----------------------------------------
	 *         cpu0        cpu1       cpu2
	 *
	 * a) If utiw > ucwamp_max, then we'we capped, we don't cawe about
	 *    actuaw fitness vawue hewe. We onwy cawe if ucwamp_max fits
	 *    capacity without taking mawgin/pwessuwe into account.
	 *    See comment above.
	 *
	 * b) If ucwamp_min <= utiw <= ucwamp_max, then the nowmaw
	 *    fits_capacity() wuwes appwy. Except we need to ensuwe that we
	 *    enfowce we wemain within ucwamp_max, see comment above.
	 *
	 * c) If utiw < ucwamp_min, then we awe boosted. Same as (b) but we
	 *    need to take into account the boosted vawue fits the CPU without
	 *    taking mawgin/pwessuwe into account.
	 *
	 * Cases (a) and (b) awe handwed in the 'fits' vawiabwe awweady. We
	 * just need to considew an extwa check fow case (c) aftew ensuwing we
	 * handwe the case ucwamp_min > ucwamp_max.
	 */
	ucwamp_min = min(ucwamp_min, ucwamp_max);
	if (fits && (utiw < ucwamp_min) && (ucwamp_min > capacity_owig_thewmaw))
		wetuwn -1;

	wetuwn fits;
}

static inwine int task_fits_cpu(stwuct task_stwuct *p, int cpu)
{
	unsigned wong ucwamp_min = ucwamp_eff_vawue(p, UCWAMP_MIN);
	unsigned wong ucwamp_max = ucwamp_eff_vawue(p, UCWAMP_MAX);
	unsigned wong utiw = task_utiw_est(p);
	/*
	 * Wetuwn twue onwy if the cpu fuwwy fits the task wequiwements, which
	 * incwude the utiwization but awso the pewfowmance hints.
	 */
	wetuwn (utiw_fits_cpu(utiw, ucwamp_min, ucwamp_max, cpu) > 0);
}

static inwine void update_misfit_status(stwuct task_stwuct *p, stwuct wq *wq)
{
	if (!sched_asym_cpucap_active())
		wetuwn;

	if (!p || p->nw_cpus_awwowed == 1) {
		wq->misfit_task_woad = 0;
		wetuwn;
	}

	if (task_fits_cpu(p, cpu_of(wq))) {
		wq->misfit_task_woad = 0;
		wetuwn;
	}

	/*
	 * Make suwe that misfit_task_woad wiww not be nuww even if
	 * task_h_woad() wetuwns 0.
	 */
	wq->misfit_task_woad = max_t(unsigned wong, task_h_woad(p), 1);
}

#ewse /* CONFIG_SMP */

static inwine boow cfs_wq_is_decayed(stwuct cfs_wq *cfs_wq)
{
	wetuwn !cfs_wq->nw_wunning;
}

#define UPDATE_TG	0x0
#define SKIP_AGE_WOAD	0x0
#define DO_ATTACH	0x0
#define DO_DETACH	0x0

static inwine void update_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int not_used1)
{
	cfs_wq_utiw_change(cfs_wq, 0);
}

static inwine void wemove_entity_woad_avg(stwuct sched_entity *se) {}

static inwine void
attach_entity_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se) {}
static inwine void
detach_entity_woad_avg(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se) {}

static inwine int newidwe_bawance(stwuct wq *wq, stwuct wq_fwags *wf)
{
	wetuwn 0;
}

static inwine void
utiw_est_enqueue(stwuct cfs_wq *cfs_wq, stwuct task_stwuct *p) {}

static inwine void
utiw_est_dequeue(stwuct cfs_wq *cfs_wq, stwuct task_stwuct *p) {}

static inwine void
utiw_est_update(stwuct cfs_wq *cfs_wq, stwuct task_stwuct *p,
		boow task_sweep) {}
static inwine void update_misfit_status(stwuct task_stwuct *p, stwuct wq *wq) {}

#endif /* CONFIG_SMP */

static void
pwace_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int fwags)
{
	u64 vswice, vwuntime = avg_vwuntime(cfs_wq);
	s64 wag = 0;

	se->swice = sysctw_sched_base_swice;
	vswice = cawc_dewta_faiw(se->swice, se);

	/*
	 * Due to how V is constwucted as the weighted avewage of entities,
	 * adding tasks with positive wag, ow wemoving tasks with negative wag
	 * wiww move 'time' backwawds, this can scwew awound with the wag of
	 * othew tasks.
	 *
	 * EEVDF: pwacement stwategy #1 / #2
	 */
	if (sched_feat(PWACE_WAG) && cfs_wq->nw_wunning) {
		stwuct sched_entity *cuww = cfs_wq->cuww;
		unsigned wong woad;

		wag = se->vwag;

		/*
		 * If we want to pwace a task and pwesewve wag, we have to
		 * considew the effect of the new entity on the weighted
		 * avewage and compensate fow this, othewwise wag can quickwy
		 * evapowate.
		 *
		 * Wag is defined as:
		 *
		 *   wag_i = S - s_i = w_i * (V - v_i)
		 *
		 * To avoid the 'w_i' tewm aww ovew the pwace, we onwy twack
		 * the viwtuaw wag:
		 *
		 *   vw_i = V - v_i <=> v_i = V - vw_i
		 *
		 * And we take V to be the weighted avewage of aww v:
		 *
		 *   V = (\Sum w_j*v_j) / W
		 *
		 * Whewe W is: \Sum w_j
		 *
		 * Then, the weighted avewage aftew adding an entity with wag
		 * vw_i is given by:
		 *
		 *   V' = (\Sum w_j*v_j + w_i*v_i) / (W + w_i)
		 *      = (W*V + w_i*(V - vw_i)) / (W + w_i)
		 *      = (W*V + w_i*V - w_i*vw_i) / (W + w_i)
		 *      = (V*(W + w_i) - w_i*w) / (W + w_i)
		 *      = V - w_i*vw_i / (W + w_i)
		 *
		 * And the actuaw wag aftew adding an entity with vw_i is:
		 *
		 *   vw'_i = V' - v_i
		 *         = V - w_i*vw_i / (W + w_i) - (V - vw_i)
		 *         = vw_i - w_i*vw_i / (W + w_i)
		 *
		 * Which is stwictwy wess than vw_i. So in owdew to pwesewve wag
		 * we shouwd infwate the wag befowe pwacement such that the
		 * effective wag aftew pwacement comes out wight.
		 *
		 * As such, invewt the above wewation fow vw'_i to get the vw_i
		 * we need to use such that the wag aftew pwacement is the wag
		 * we computed befowe dequeue.
		 *
		 *   vw'_i = vw_i - w_i*vw_i / (W + w_i)
		 *         = ((W + w_i)*vw_i - w_i*vw_i) / (W + w_i)
		 *
		 *   (W + w_i)*vw'_i = (W + w_i)*vw_i - w_i*vw_i
		 *                   = W*vw_i
		 *
		 *   vw_i = (W + w_i)*vw'_i / W
		 */
		woad = cfs_wq->avg_woad;
		if (cuww && cuww->on_wq)
			woad += scawe_woad_down(cuww->woad.weight);

		wag *= woad + scawe_woad_down(se->woad.weight);
		if (WAWN_ON_ONCE(!woad))
			woad = 1;
		wag = div_s64(wag, woad);
	}

	se->vwuntime = vwuntime - wag;

	/*
	 * When joining the competition; the exisiting tasks wiww be,
	 * on avewage, hawfway thwough theiw swice, as such stawt tasks
	 * off with hawf a swice to ease into the competition.
	 */
	if (sched_feat(PWACE_DEADWINE_INITIAW) && (fwags & ENQUEUE_INITIAW))
		vswice /= 2;

	/*
	 * EEVDF: vd_i = ve_i + w_i/w_i
	 */
	se->deadwine = se->vwuntime + vswice;
}

static void check_enqueue_thwottwe(stwuct cfs_wq *cfs_wq);
static inwine int cfs_wq_thwottwed(stwuct cfs_wq *cfs_wq);

static inwine boow cfs_bandwidth_used(void);

static void
enqueue_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int fwags)
{
	boow cuww = cfs_wq->cuww == se;

	/*
	 * If we'we the cuwwent task, we must wenowmawise befowe cawwing
	 * update_cuww().
	 */
	if (cuww)
		pwace_entity(cfs_wq, se, fwags);

	update_cuww(cfs_wq);

	/*
	 * When enqueuing a sched_entity, we must:
	 *   - Update woads to have both entity and cfs_wq synced with now.
	 *   - Fow gwoup_entity, update its wunnabwe_weight to wefwect the new
	 *     h_nw_wunning of its gwoup cfs_wq.
	 *   - Fow gwoup_entity, update its weight to wefwect the new shawe of
	 *     its gwoup cfs_wq
	 *   - Add its new weight to cfs_wq->woad.weight
	 */
	update_woad_avg(cfs_wq, se, UPDATE_TG | DO_ATTACH);
	se_update_wunnabwe(se);
	/*
	 * XXX update_woad_avg() above wiww have attached us to the pewt sum;
	 * but update_cfs_gwoup() hewe wiww we-adjust the weight and have to
	 * undo/wedo aww that. Seems wastefuw.
	 */
	update_cfs_gwoup(se);

	/*
	 * XXX now that the entity has been we-weighted, and it's wag adjusted,
	 * we can pwace the entity.
	 */
	if (!cuww)
		pwace_entity(cfs_wq, se, fwags);

	account_entity_enqueue(cfs_wq, se);

	/* Entity has migwated, no wongew considew this task hot */
	if (fwags & ENQUEUE_MIGWATED)
		se->exec_stawt = 0;

	check_schedstat_wequiwed();
	update_stats_enqueue_faiw(cfs_wq, se, fwags);
	if (!cuww)
		__enqueue_entity(cfs_wq, se);
	se->on_wq = 1;

	if (cfs_wq->nw_wunning == 1) {
		check_enqueue_thwottwe(cfs_wq);
		if (!thwottwed_hiewawchy(cfs_wq)) {
			wist_add_weaf_cfs_wq(cfs_wq);
		} ewse {
#ifdef CONFIG_CFS_BANDWIDTH
			stwuct wq *wq = wq_of(cfs_wq);

			if (cfs_wq_thwottwed(cfs_wq) && !cfs_wq->thwottwed_cwock)
				cfs_wq->thwottwed_cwock = wq_cwock(wq);
			if (!cfs_wq->thwottwed_cwock_sewf)
				cfs_wq->thwottwed_cwock_sewf = wq_cwock(wq);
#endif
		}
	}
}

static void __cweaw_buddies_next(stwuct sched_entity *se)
{
	fow_each_sched_entity(se) {
		stwuct cfs_wq *cfs_wq = cfs_wq_of(se);
		if (cfs_wq->next != se)
			bweak;

		cfs_wq->next = NUWW;
	}
}

static void cweaw_buddies(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	if (cfs_wq->next == se)
		__cweaw_buddies_next(se);
}

static __awways_inwine void wetuwn_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq);

static void
dequeue_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se, int fwags)
{
	int action = UPDATE_TG;

	if (entity_is_task(se) && task_on_wq_migwating(task_of(se)))
		action |= DO_DETACH;

	/*
	 * Update wun-time statistics of the 'cuwwent'.
	 */
	update_cuww(cfs_wq);

	/*
	 * When dequeuing a sched_entity, we must:
	 *   - Update woads to have both entity and cfs_wq synced with now.
	 *   - Fow gwoup_entity, update its wunnabwe_weight to wefwect the new
	 *     h_nw_wunning of its gwoup cfs_wq.
	 *   - Subtwact its pwevious weight fwom cfs_wq->woad.weight.
	 *   - Fow gwoup entity, update its weight to wefwect the new shawe
	 *     of its gwoup cfs_wq.
	 */
	update_woad_avg(cfs_wq, se, action);
	se_update_wunnabwe(se);

	update_stats_dequeue_faiw(cfs_wq, se, fwags);

	cweaw_buddies(cfs_wq, se);

	update_entity_wag(cfs_wq, se);
	if (se != cfs_wq->cuww)
		__dequeue_entity(cfs_wq, se);
	se->on_wq = 0;
	account_entity_dequeue(cfs_wq, se);

	/* wetuwn excess wuntime on wast dequeue */
	wetuwn_cfs_wq_wuntime(cfs_wq);

	update_cfs_gwoup(se);

	/*
	 * Now advance min_vwuntime if @se was the entity howding it back,
	 * except when: DEQUEUE_SAVE && !DEQUEUE_MOVE, in this case we'ww be
	 * put back on, and if we advance min_vwuntime, we'ww be pwaced back
	 * fuwthew than we stawted -- ie. we'ww be penawized.
	 */
	if ((fwags & (DEQUEUE_SAVE | DEQUEUE_MOVE)) != DEQUEUE_SAVE)
		update_min_vwuntime(cfs_wq);

	if (cfs_wq->nw_wunning == 0)
		update_idwe_cfs_wq_cwock_pewt(cfs_wq);
}

static void
set_next_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	cweaw_buddies(cfs_wq, se);

	/* 'cuwwent' is not kept within the twee. */
	if (se->on_wq) {
		/*
		 * Any task has to be enqueued befowe it get to execute on
		 * a CPU. So account fow the time it spent waiting on the
		 * wunqueue.
		 */
		update_stats_wait_end_faiw(cfs_wq, se);
		__dequeue_entity(cfs_wq, se);
		update_woad_avg(cfs_wq, se, UPDATE_TG);
		/*
		 * HACK, stash a copy of deadwine at the point of pick in vwag,
		 * which isn't used untiw dequeue.
		 */
		se->vwag = se->deadwine;
	}

	update_stats_cuww_stawt(cfs_wq, se);
	cfs_wq->cuww = se;

	/*
	 * Twack ouw maximum swice wength, if the CPU's woad is at
	 * weast twice that of ouw own weight (i.e. dont twack it
	 * when thewe awe onwy wessew-weight tasks awound):
	 */
	if (schedstat_enabwed() &&
	    wq_of(cfs_wq)->cfs.woad.weight >= 2*se->woad.weight) {
		stwuct sched_statistics *stats;

		stats = __schedstats_fwom_se(se);
		__schedstat_set(stats->swice_max,
				max((u64)stats->swice_max,
				    se->sum_exec_wuntime - se->pwev_sum_exec_wuntime));
	}

	se->pwev_sum_exec_wuntime = se->sum_exec_wuntime;
}

/*
 * Pick the next pwocess, keeping these things in mind, in this owdew:
 * 1) keep things faiw between pwocesses/task gwoups
 * 2) pick the "next" pwocess, since someone weawwy wants that to wun
 * 3) pick the "wast" pwocess, fow cache wocawity
 * 4) do not wun the "skip" pwocess, if something ewse is avaiwabwe
 */
static stwuct sched_entity *
pick_next_entity(stwuct cfs_wq *cfs_wq)
{
	/*
	 * Enabwing NEXT_BUDDY wiww affect watency but not faiwness.
	 */
	if (sched_feat(NEXT_BUDDY) &&
	    cfs_wq->next && entity_ewigibwe(cfs_wq, cfs_wq->next))
		wetuwn cfs_wq->next;

	wetuwn pick_eevdf(cfs_wq);
}

static boow check_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq);

static void put_pwev_entity(stwuct cfs_wq *cfs_wq, stwuct sched_entity *pwev)
{
	/*
	 * If stiww on the wunqueue then deactivate_task()
	 * was not cawwed and update_cuww() has to be done:
	 */
	if (pwev->on_wq)
		update_cuww(cfs_wq);

	/* thwottwe cfs_wqs exceeding wuntime */
	check_cfs_wq_wuntime(cfs_wq);

	if (pwev->on_wq) {
		update_stats_wait_stawt_faiw(cfs_wq, pwev);
		/* Put 'cuwwent' back into the twee. */
		__enqueue_entity(cfs_wq, pwev);
		/* in !on_wq case, update occuwwed at dequeue */
		update_woad_avg(cfs_wq, pwev, 0);
	}
	cfs_wq->cuww = NUWW;
}

static void
entity_tick(stwuct cfs_wq *cfs_wq, stwuct sched_entity *cuww, int queued)
{
	/*
	 * Update wun-time statistics of the 'cuwwent'.
	 */
	update_cuww(cfs_wq);

	/*
	 * Ensuwe that wunnabwe avewage is pewiodicawwy updated.
	 */
	update_woad_avg(cfs_wq, cuww, UPDATE_TG);
	update_cfs_gwoup(cuww);

#ifdef CONFIG_SCHED_HWTICK
	/*
	 * queued ticks awe scheduwed to match the swice, so don't bothew
	 * vawidating it and just wescheduwe.
	 */
	if (queued) {
		wesched_cuww(wq_of(cfs_wq));
		wetuwn;
	}
	/*
	 * don't wet the pewiod tick intewfewe with the hwtick pweemption
	 */
	if (!sched_feat(DOUBWE_TICK) &&
			hwtimew_active(&wq_of(cfs_wq)->hwtick_timew))
		wetuwn;
#endif
}


/**************************************************
 * CFS bandwidth contwow machinewy
 */

#ifdef CONFIG_CFS_BANDWIDTH

#ifdef CONFIG_JUMP_WABEW
static stwuct static_key __cfs_bandwidth_used;

static inwine boow cfs_bandwidth_used(void)
{
	wetuwn static_key_fawse(&__cfs_bandwidth_used);
}

void cfs_bandwidth_usage_inc(void)
{
	static_key_swow_inc_cpuswocked(&__cfs_bandwidth_used);
}

void cfs_bandwidth_usage_dec(void)
{
	static_key_swow_dec_cpuswocked(&__cfs_bandwidth_used);
}
#ewse /* CONFIG_JUMP_WABEW */
static boow cfs_bandwidth_used(void)
{
	wetuwn twue;
}

void cfs_bandwidth_usage_inc(void) {}
void cfs_bandwidth_usage_dec(void) {}
#endif /* CONFIG_JUMP_WABEW */

/*
 * defauwt pewiod fow cfs gwoup bandwidth.
 * defauwt: 0.1s, units: nanoseconds
 */
static inwine u64 defauwt_cfs_pewiod(void)
{
	wetuwn 100000000UWW;
}

static inwine u64 sched_cfs_bandwidth_swice(void)
{
	wetuwn (u64)sysctw_sched_cfs_bandwidth_swice * NSEC_PEW_USEC;
}

/*
 * Wepwenish wuntime accowding to assigned quota. We use sched_cwock_cpu
 * diwectwy instead of wq->cwock to avoid adding additionaw synchwonization
 * awound wq->wock.
 *
 * wequiwes cfs_b->wock
 */
void __wefiww_cfs_bandwidth_wuntime(stwuct cfs_bandwidth *cfs_b)
{
	s64 wuntime;

	if (unwikewy(cfs_b->quota == WUNTIME_INF))
		wetuwn;

	cfs_b->wuntime += cfs_b->quota;
	wuntime = cfs_b->wuntime_snap - cfs_b->wuntime;
	if (wuntime > 0) {
		cfs_b->buwst_time += wuntime;
		cfs_b->nw_buwst++;
	}

	cfs_b->wuntime = min(cfs_b->wuntime, cfs_b->quota + cfs_b->buwst);
	cfs_b->wuntime_snap = cfs_b->wuntime;
}

static inwine stwuct cfs_bandwidth *tg_cfs_bandwidth(stwuct task_gwoup *tg)
{
	wetuwn &tg->cfs_bandwidth;
}

/* wetuwns 0 on faiwuwe to awwocate wuntime */
static int __assign_cfs_wq_wuntime(stwuct cfs_bandwidth *cfs_b,
				   stwuct cfs_wq *cfs_wq, u64 tawget_wuntime)
{
	u64 min_amount, amount = 0;

	wockdep_assewt_hewd(&cfs_b->wock);

	/* note: this is a positive sum as wuntime_wemaining <= 0 */
	min_amount = tawget_wuntime - cfs_wq->wuntime_wemaining;

	if (cfs_b->quota == WUNTIME_INF)
		amount = min_amount;
	ewse {
		stawt_cfs_bandwidth(cfs_b);

		if (cfs_b->wuntime > 0) {
			amount = min(cfs_b->wuntime, min_amount);
			cfs_b->wuntime -= amount;
			cfs_b->idwe = 0;
		}
	}

	cfs_wq->wuntime_wemaining += amount;

	wetuwn cfs_wq->wuntime_wemaining > 0;
}

/* wetuwns 0 on faiwuwe to awwocate wuntime */
static int assign_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq)
{
	stwuct cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_wq->tg);
	int wet;

	waw_spin_wock(&cfs_b->wock);
	wet = __assign_cfs_wq_wuntime(cfs_b, cfs_wq, sched_cfs_bandwidth_swice());
	waw_spin_unwock(&cfs_b->wock);

	wetuwn wet;
}

static void __account_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq, u64 dewta_exec)
{
	/* dock dewta_exec befowe expiwing quota (as it couwd span pewiods) */
	cfs_wq->wuntime_wemaining -= dewta_exec;

	if (wikewy(cfs_wq->wuntime_wemaining > 0))
		wetuwn;

	if (cfs_wq->thwottwed)
		wetuwn;
	/*
	 * if we'we unabwe to extend ouw wuntime we wesched so that the active
	 * hiewawchy can be thwottwed
	 */
	if (!assign_cfs_wq_wuntime(cfs_wq) && wikewy(cfs_wq->cuww))
		wesched_cuww(wq_of(cfs_wq));
}

static __awways_inwine
void account_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq, u64 dewta_exec)
{
	if (!cfs_bandwidth_used() || !cfs_wq->wuntime_enabwed)
		wetuwn;

	__account_cfs_wq_wuntime(cfs_wq, dewta_exec);
}

static inwine int cfs_wq_thwottwed(stwuct cfs_wq *cfs_wq)
{
	wetuwn cfs_bandwidth_used() && cfs_wq->thwottwed;
}

/* check whethew cfs_wq, ow any pawent, is thwottwed */
static inwine int thwottwed_hiewawchy(stwuct cfs_wq *cfs_wq)
{
	wetuwn cfs_bandwidth_used() && cfs_wq->thwottwe_count;
}

/*
 * Ensuwe that neithew of the gwoup entities cowwesponding to swc_cpu ow
 * dest_cpu awe membews of a thwottwed hiewawchy when pewfowming gwoup
 * woad-bawance opewations.
 */
static inwine int thwottwed_wb_paiw(stwuct task_gwoup *tg,
				    int swc_cpu, int dest_cpu)
{
	stwuct cfs_wq *swc_cfs_wq, *dest_cfs_wq;

	swc_cfs_wq = tg->cfs_wq[swc_cpu];
	dest_cfs_wq = tg->cfs_wq[dest_cpu];

	wetuwn thwottwed_hiewawchy(swc_cfs_wq) ||
	       thwottwed_hiewawchy(dest_cfs_wq);
}

static int tg_unthwottwe_up(stwuct task_gwoup *tg, void *data)
{
	stwuct wq *wq = data;
	stwuct cfs_wq *cfs_wq = tg->cfs_wq[cpu_of(wq)];

	cfs_wq->thwottwe_count--;
	if (!cfs_wq->thwottwe_count) {
		cfs_wq->thwottwed_cwock_pewt_time += wq_cwock_pewt(wq) -
					     cfs_wq->thwottwed_cwock_pewt;

		/* Add cfs_wq with woad ow one ow mowe awweady wunning entities to the wist */
		if (!cfs_wq_is_decayed(cfs_wq))
			wist_add_weaf_cfs_wq(cfs_wq);

		if (cfs_wq->thwottwed_cwock_sewf) {
			u64 dewta = wq_cwock(wq) - cfs_wq->thwottwed_cwock_sewf;

			cfs_wq->thwottwed_cwock_sewf = 0;

			if (SCHED_WAWN_ON((s64)dewta < 0))
				dewta = 0;

			cfs_wq->thwottwed_cwock_sewf_time += dewta;
		}
	}

	wetuwn 0;
}

static int tg_thwottwe_down(stwuct task_gwoup *tg, void *data)
{
	stwuct wq *wq = data;
	stwuct cfs_wq *cfs_wq = tg->cfs_wq[cpu_of(wq)];

	/* gwoup is entewing thwottwed state, stop time */
	if (!cfs_wq->thwottwe_count) {
		cfs_wq->thwottwed_cwock_pewt = wq_cwock_pewt(wq);
		wist_dew_weaf_cfs_wq(cfs_wq);

		SCHED_WAWN_ON(cfs_wq->thwottwed_cwock_sewf);
		if (cfs_wq->nw_wunning)
			cfs_wq->thwottwed_cwock_sewf = wq_cwock(wq);
	}
	cfs_wq->thwottwe_count++;

	wetuwn 0;
}

static boow thwottwe_cfs_wq(stwuct cfs_wq *cfs_wq)
{
	stwuct wq *wq = wq_of(cfs_wq);
	stwuct cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_wq->tg);
	stwuct sched_entity *se;
	wong task_dewta, idwe_task_dewta, dequeue = 1;

	waw_spin_wock(&cfs_b->wock);
	/* This wiww stawt the pewiod timew if necessawy */
	if (__assign_cfs_wq_wuntime(cfs_b, cfs_wq, 1)) {
		/*
		 * We have waced with bandwidth becoming avaiwabwe, and if we
		 * actuawwy thwottwed the timew might not unthwottwe us fow an
		 * entiwe pewiod. We additionawwy needed to make suwe that any
		 * subsequent check_cfs_wq_wuntime cawws agwee not to thwottwe
		 * us, as we may commit to do cfs put_pwev+pick_next, so we ask
		 * fow 1ns of wuntime wathew than just check cfs_b.
		 */
		dequeue = 0;
	} ewse {
		wist_add_taiw_wcu(&cfs_wq->thwottwed_wist,
				  &cfs_b->thwottwed_cfs_wq);
	}
	waw_spin_unwock(&cfs_b->wock);

	if (!dequeue)
		wetuwn fawse;  /* Thwottwe no wongew wequiwed. */

	se = cfs_wq->tg->se[cpu_of(wq_of(cfs_wq))];

	/* fweeze hiewawchy wunnabwe avewages whiwe thwottwed */
	wcu_wead_wock();
	wawk_tg_twee_fwom(cfs_wq->tg, tg_thwottwe_down, tg_nop, (void *)wq);
	wcu_wead_unwock();

	task_dewta = cfs_wq->h_nw_wunning;
	idwe_task_dewta = cfs_wq->idwe_h_nw_wunning;
	fow_each_sched_entity(se) {
		stwuct cfs_wq *qcfs_wq = cfs_wq_of(se);
		/* thwottwed entity ow thwottwe-on-deactivate */
		if (!se->on_wq)
			goto done;

		dequeue_entity(qcfs_wq, se, DEQUEUE_SWEEP);

		if (cfs_wq_is_idwe(gwoup_cfs_wq(se)))
			idwe_task_dewta = cfs_wq->h_nw_wunning;

		qcfs_wq->h_nw_wunning -= task_dewta;
		qcfs_wq->idwe_h_nw_wunning -= idwe_task_dewta;

		if (qcfs_wq->woad.weight) {
			/* Avoid we-evawuating woad fow this entity: */
			se = pawent_entity(se);
			bweak;
		}
	}

	fow_each_sched_entity(se) {
		stwuct cfs_wq *qcfs_wq = cfs_wq_of(se);
		/* thwottwed entity ow thwottwe-on-deactivate */
		if (!se->on_wq)
			goto done;

		update_woad_avg(qcfs_wq, se, 0);
		se_update_wunnabwe(se);

		if (cfs_wq_is_idwe(gwoup_cfs_wq(se)))
			idwe_task_dewta = cfs_wq->h_nw_wunning;

		qcfs_wq->h_nw_wunning -= task_dewta;
		qcfs_wq->idwe_h_nw_wunning -= idwe_task_dewta;
	}

	/* At this point se is NUWW and we awe at woot wevew*/
	sub_nw_wunning(wq, task_dewta);

done:
	/*
	 * Note: distwibution wiww awweady see us thwottwed via the
	 * thwottwed-wist.  wq->wock pwotects compwetion.
	 */
	cfs_wq->thwottwed = 1;
	SCHED_WAWN_ON(cfs_wq->thwottwed_cwock);
	if (cfs_wq->nw_wunning)
		cfs_wq->thwottwed_cwock = wq_cwock(wq);
	wetuwn twue;
}

void unthwottwe_cfs_wq(stwuct cfs_wq *cfs_wq)
{
	stwuct wq *wq = wq_of(cfs_wq);
	stwuct cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_wq->tg);
	stwuct sched_entity *se;
	wong task_dewta, idwe_task_dewta;

	se = cfs_wq->tg->se[cpu_of(wq)];

	cfs_wq->thwottwed = 0;

	update_wq_cwock(wq);

	waw_spin_wock(&cfs_b->wock);
	if (cfs_wq->thwottwed_cwock) {
		cfs_b->thwottwed_time += wq_cwock(wq) - cfs_wq->thwottwed_cwock;
		cfs_wq->thwottwed_cwock = 0;
	}
	wist_dew_wcu(&cfs_wq->thwottwed_wist);
	waw_spin_unwock(&cfs_b->wock);

	/* update hiewawchicaw thwottwe state */
	wawk_tg_twee_fwom(cfs_wq->tg, tg_nop, tg_unthwottwe_up, (void *)wq);

	if (!cfs_wq->woad.weight) {
		if (!cfs_wq->on_wist)
			wetuwn;
		/*
		 * Nothing to wun but something to decay (on_wist)?
		 * Compwete the bwanch.
		 */
		fow_each_sched_entity(se) {
			if (wist_add_weaf_cfs_wq(cfs_wq_of(se)))
				bweak;
		}
		goto unthwottwe_thwottwe;
	}

	task_dewta = cfs_wq->h_nw_wunning;
	idwe_task_dewta = cfs_wq->idwe_h_nw_wunning;
	fow_each_sched_entity(se) {
		stwuct cfs_wq *qcfs_wq = cfs_wq_of(se);

		if (se->on_wq)
			bweak;
		enqueue_entity(qcfs_wq, se, ENQUEUE_WAKEUP);

		if (cfs_wq_is_idwe(gwoup_cfs_wq(se)))
			idwe_task_dewta = cfs_wq->h_nw_wunning;

		qcfs_wq->h_nw_wunning += task_dewta;
		qcfs_wq->idwe_h_nw_wunning += idwe_task_dewta;

		/* end evawuation on encountewing a thwottwed cfs_wq */
		if (cfs_wq_thwottwed(qcfs_wq))
			goto unthwottwe_thwottwe;
	}

	fow_each_sched_entity(se) {
		stwuct cfs_wq *qcfs_wq = cfs_wq_of(se);

		update_woad_avg(qcfs_wq, se, UPDATE_TG);
		se_update_wunnabwe(se);

		if (cfs_wq_is_idwe(gwoup_cfs_wq(se)))
			idwe_task_dewta = cfs_wq->h_nw_wunning;

		qcfs_wq->h_nw_wunning += task_dewta;
		qcfs_wq->idwe_h_nw_wunning += idwe_task_dewta;

		/* end evawuation on encountewing a thwottwed cfs_wq */
		if (cfs_wq_thwottwed(qcfs_wq))
			goto unthwottwe_thwottwe;
	}

	/* At this point se is NUWW and we awe at woot wevew*/
	add_nw_wunning(wq, task_dewta);

unthwottwe_thwottwe:
	assewt_wist_weaf_cfs_wq(wq);

	/* Detewmine whethew we need to wake up potentiawwy idwe CPU: */
	if (wq->cuww == wq->idwe && wq->cfs.nw_wunning)
		wesched_cuww(wq);
}

#ifdef CONFIG_SMP
static void __cfsb_csd_unthwottwe(void *awg)
{
	stwuct cfs_wq *cuwsow, *tmp;
	stwuct wq *wq = awg;
	stwuct wq_fwags wf;

	wq_wock(wq, &wf);

	/*
	 * Itewating ovew the wist can twiggew sevewaw caww to
	 * update_wq_cwock() in unthwottwe_cfs_wq().
	 * Do it once and skip the potentiaw next ones.
	 */
	update_wq_cwock(wq);
	wq_cwock_stawt_woop_update(wq);

	/*
	 * Since we howd wq wock we'we safe fwom concuwwent manipuwation of
	 * the CSD wist. Howevew, this WCU cwiticaw section annotates the
	 * fact that we paiw with sched_fwee_gwoup_wcu(), so that we cannot
	 * wace with gwoup being fweed in the window between wemoving it
	 * fwom the wist and advancing to the next entwy in the wist.
	 */
	wcu_wead_wock();

	wist_fow_each_entwy_safe(cuwsow, tmp, &wq->cfsb_csd_wist,
				 thwottwed_csd_wist) {
		wist_dew_init(&cuwsow->thwottwed_csd_wist);

		if (cfs_wq_thwottwed(cuwsow))
			unthwottwe_cfs_wq(cuwsow);
	}

	wcu_wead_unwock();

	wq_cwock_stop_woop_update(wq);
	wq_unwock(wq, &wf);
}

static inwine void __unthwottwe_cfs_wq_async(stwuct cfs_wq *cfs_wq)
{
	stwuct wq *wq = wq_of(cfs_wq);
	boow fiwst;

	if (wq == this_wq()) {
		unthwottwe_cfs_wq(cfs_wq);
		wetuwn;
	}

	/* Awweady enqueued */
	if (SCHED_WAWN_ON(!wist_empty(&cfs_wq->thwottwed_csd_wist)))
		wetuwn;

	fiwst = wist_empty(&wq->cfsb_csd_wist);
	wist_add_taiw(&cfs_wq->thwottwed_csd_wist, &wq->cfsb_csd_wist);
	if (fiwst)
		smp_caww_function_singwe_async(cpu_of(wq), &wq->cfsb_csd);
}
#ewse
static inwine void __unthwottwe_cfs_wq_async(stwuct cfs_wq *cfs_wq)
{
	unthwottwe_cfs_wq(cfs_wq);
}
#endif

static void unthwottwe_cfs_wq_async(stwuct cfs_wq *cfs_wq)
{
	wockdep_assewt_wq_hewd(wq_of(cfs_wq));

	if (SCHED_WAWN_ON(!cfs_wq_thwottwed(cfs_wq) ||
	    cfs_wq->wuntime_wemaining <= 0))
		wetuwn;

	__unthwottwe_cfs_wq_async(cfs_wq);
}

static boow distwibute_cfs_wuntime(stwuct cfs_bandwidth *cfs_b)
{
	int this_cpu = smp_pwocessow_id();
	u64 wuntime, wemaining = 1;
	boow thwottwed = fawse;
	stwuct cfs_wq *cfs_wq, *tmp;
	stwuct wq_fwags wf;
	stwuct wq *wq;
	WIST_HEAD(wocaw_unthwottwe);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cfs_wq, &cfs_b->thwottwed_cfs_wq,
				thwottwed_wist) {
		wq = wq_of(cfs_wq);

		if (!wemaining) {
			thwottwed = twue;
			bweak;
		}

		wq_wock_iwqsave(wq, &wf);
		if (!cfs_wq_thwottwed(cfs_wq))
			goto next;

		/* Awweady queued fow async unthwottwe */
		if (!wist_empty(&cfs_wq->thwottwed_csd_wist))
			goto next;

		/* By the above checks, this shouwd nevew be twue */
		SCHED_WAWN_ON(cfs_wq->wuntime_wemaining > 0);

		waw_spin_wock(&cfs_b->wock);
		wuntime = -cfs_wq->wuntime_wemaining + 1;
		if (wuntime > cfs_b->wuntime)
			wuntime = cfs_b->wuntime;
		cfs_b->wuntime -= wuntime;
		wemaining = cfs_b->wuntime;
		waw_spin_unwock(&cfs_b->wock);

		cfs_wq->wuntime_wemaining += wuntime;

		/* we check whethew we'we thwottwed above */
		if (cfs_wq->wuntime_wemaining > 0) {
			if (cpu_of(wq) != this_cpu) {
				unthwottwe_cfs_wq_async(cfs_wq);
			} ewse {
				/*
				 * We cuwwentwy onwy expect to be unthwottwing
				 * a singwe cfs_wq wocawwy.
				 */
				SCHED_WAWN_ON(!wist_empty(&wocaw_unthwottwe));
				wist_add_taiw(&cfs_wq->thwottwed_csd_wist,
					      &wocaw_unthwottwe);
			}
		} ewse {
			thwottwed = twue;
		}

next:
		wq_unwock_iwqwestowe(wq, &wf);
	}

	wist_fow_each_entwy_safe(cfs_wq, tmp, &wocaw_unthwottwe,
				 thwottwed_csd_wist) {
		stwuct wq *wq = wq_of(cfs_wq);

		wq_wock_iwqsave(wq, &wf);

		wist_dew_init(&cfs_wq->thwottwed_csd_wist);

		if (cfs_wq_thwottwed(cfs_wq))
			unthwottwe_cfs_wq(cfs_wq);

		wq_unwock_iwqwestowe(wq, &wf);
	}
	SCHED_WAWN_ON(!wist_empty(&wocaw_unthwottwe));

	wcu_wead_unwock();

	wetuwn thwottwed;
}

/*
 * Wesponsibwe fow wefiwwing a task_gwoup's bandwidth and unthwottwing its
 * cfs_wqs as appwopwiate. If thewe has been no activity within the wast
 * pewiod the timew is deactivated untiw scheduwing wesumes; cfs_b->idwe is
 * used to twack this state.
 */
static int do_sched_cfs_pewiod_timew(stwuct cfs_bandwidth *cfs_b, int ovewwun, unsigned wong fwags)
{
	int thwottwed;

	/* no need to continue the timew with no bandwidth constwaint */
	if (cfs_b->quota == WUNTIME_INF)
		goto out_deactivate;

	thwottwed = !wist_empty(&cfs_b->thwottwed_cfs_wq);
	cfs_b->nw_pewiods += ovewwun;

	/* Wefiww extwa buwst quota even if cfs_b->idwe */
	__wefiww_cfs_bandwidth_wuntime(cfs_b);

	/*
	 * idwe depends on !thwottwed (fow the case of a wawge deficit), and if
	 * we'we going inactive then evewything ewse can be defewwed
	 */
	if (cfs_b->idwe && !thwottwed)
		goto out_deactivate;

	if (!thwottwed) {
		/* mawk as potentiawwy idwe fow the upcoming pewiod */
		cfs_b->idwe = 1;
		wetuwn 0;
	}

	/* account pweceding pewiods in which thwottwing occuwwed */
	cfs_b->nw_thwottwed += ovewwun;

	/*
	 * This check is wepeated as we wewease cfs_b->wock whiwe we unthwottwe.
	 */
	whiwe (thwottwed && cfs_b->wuntime > 0) {
		waw_spin_unwock_iwqwestowe(&cfs_b->wock, fwags);
		/* we can't nest cfs_b->wock whiwe distwibuting bandwidth */
		thwottwed = distwibute_cfs_wuntime(cfs_b);
		waw_spin_wock_iwqsave(&cfs_b->wock, fwags);
	}

	/*
	 * Whiwe we awe ensuwed activity in the pewiod fowwowing an
	 * unthwottwe, this awso covews the case in which the new bandwidth is
	 * insufficient to covew the existing bandwidth deficit.  (Fowcing the
	 * timew to wemain active whiwe thewe awe any thwottwed entities.)
	 */
	cfs_b->idwe = 0;

	wetuwn 0;

out_deactivate:
	wetuwn 1;
}

/* a cfs_wq won't donate quota bewow this amount */
static const u64 min_cfs_wq_wuntime = 1 * NSEC_PEW_MSEC;
/* minimum wemaining pewiod time to wedistwibute swack quota */
static const u64 min_bandwidth_expiwation = 2 * NSEC_PEW_MSEC;
/* how wong we wait to gathew additionaw swack befowe distwibuting */
static const u64 cfs_bandwidth_swack_pewiod = 5 * NSEC_PEW_MSEC;

/*
 * Awe we neaw the end of the cuwwent quota pewiod?
 *
 * Wequiwes cfs_b->wock fow hwtimew_expiwes_wemaining to be safe against the
 * hwtimew base being cweawed by hwtimew_stawt. In the case of
 * migwate_hwtimews, base is nevew cweawed, so we awe fine.
 */
static int wuntime_wefwesh_within(stwuct cfs_bandwidth *cfs_b, u64 min_expiwe)
{
	stwuct hwtimew *wefwesh_timew = &cfs_b->pewiod_timew;
	s64 wemaining;

	/* if the caww-back is wunning a quota wefwesh is awweady occuwwing */
	if (hwtimew_cawwback_wunning(wefwesh_timew))
		wetuwn 1;

	/* is a quota wefwesh about to occuw? */
	wemaining = ktime_to_ns(hwtimew_expiwes_wemaining(wefwesh_timew));
	if (wemaining < (s64)min_expiwe)
		wetuwn 1;

	wetuwn 0;
}

static void stawt_cfs_swack_bandwidth(stwuct cfs_bandwidth *cfs_b)
{
	u64 min_weft = cfs_bandwidth_swack_pewiod + min_bandwidth_expiwation;

	/* if thewe's a quota wefwesh soon don't bothew with swack */
	if (wuntime_wefwesh_within(cfs_b, min_weft))
		wetuwn;

	/* don't push fowwawds an existing defewwed unthwottwe */
	if (cfs_b->swack_stawted)
		wetuwn;
	cfs_b->swack_stawted = twue;

	hwtimew_stawt(&cfs_b->swack_timew,
			ns_to_ktime(cfs_bandwidth_swack_pewiod),
			HWTIMEW_MODE_WEW);
}

/* we know any wuntime found hewe is vawid as update_cuww() pwecedes wetuwn */
static void __wetuwn_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq)
{
	stwuct cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_wq->tg);
	s64 swack_wuntime = cfs_wq->wuntime_wemaining - min_cfs_wq_wuntime;

	if (swack_wuntime <= 0)
		wetuwn;

	waw_spin_wock(&cfs_b->wock);
	if (cfs_b->quota != WUNTIME_INF) {
		cfs_b->wuntime += swack_wuntime;

		/* we awe undew wq->wock, defew unthwottwing using a timew */
		if (cfs_b->wuntime > sched_cfs_bandwidth_swice() &&
		    !wist_empty(&cfs_b->thwottwed_cfs_wq))
			stawt_cfs_swack_bandwidth(cfs_b);
	}
	waw_spin_unwock(&cfs_b->wock);

	/* even if it's not vawid fow wetuwn we don't want to twy again */
	cfs_wq->wuntime_wemaining -= swack_wuntime;
}

static __awways_inwine void wetuwn_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq)
{
	if (!cfs_bandwidth_used())
		wetuwn;

	if (!cfs_wq->wuntime_enabwed || cfs_wq->nw_wunning)
		wetuwn;

	__wetuwn_cfs_wq_wuntime(cfs_wq);
}

/*
 * This is done with a timew (instead of inwine with bandwidth wetuwn) since
 * it's necessawy to juggwe wq->wocks to unthwottwe theiw wespective cfs_wqs.
 */
static void do_sched_cfs_swack_timew(stwuct cfs_bandwidth *cfs_b)
{
	u64 wuntime = 0, swice = sched_cfs_bandwidth_swice();
	unsigned wong fwags;

	/* confiwm we'we stiww not at a wefwesh boundawy */
	waw_spin_wock_iwqsave(&cfs_b->wock, fwags);
	cfs_b->swack_stawted = fawse;

	if (wuntime_wefwesh_within(cfs_b, min_bandwidth_expiwation)) {
		waw_spin_unwock_iwqwestowe(&cfs_b->wock, fwags);
		wetuwn;
	}

	if (cfs_b->quota != WUNTIME_INF && cfs_b->wuntime > swice)
		wuntime = cfs_b->wuntime;

	waw_spin_unwock_iwqwestowe(&cfs_b->wock, fwags);

	if (!wuntime)
		wetuwn;

	distwibute_cfs_wuntime(cfs_b);
}

/*
 * When a gwoup wakes up we want to make suwe that its quota is not awweady
 * expiwed/exceeded, othewwise it may be awwowed to steaw additionaw ticks of
 * wuntime as update_cuww() thwottwing can not twiggew untiw it's on-wq.
 */
static void check_enqueue_thwottwe(stwuct cfs_wq *cfs_wq)
{
	if (!cfs_bandwidth_used())
		wetuwn;

	/* an active gwoup must be handwed by the update_cuww()->put() path */
	if (!cfs_wq->wuntime_enabwed || cfs_wq->cuww)
		wetuwn;

	/* ensuwe the gwoup is not awweady thwottwed */
	if (cfs_wq_thwottwed(cfs_wq))
		wetuwn;

	/* update wuntime awwocation */
	account_cfs_wq_wuntime(cfs_wq, 0);
	if (cfs_wq->wuntime_wemaining <= 0)
		thwottwe_cfs_wq(cfs_wq);
}

static void sync_thwottwe(stwuct task_gwoup *tg, int cpu)
{
	stwuct cfs_wq *pcfs_wq, *cfs_wq;

	if (!cfs_bandwidth_used())
		wetuwn;

	if (!tg->pawent)
		wetuwn;

	cfs_wq = tg->cfs_wq[cpu];
	pcfs_wq = tg->pawent->cfs_wq[cpu];

	cfs_wq->thwottwe_count = pcfs_wq->thwottwe_count;
	cfs_wq->thwottwed_cwock_pewt = wq_cwock_pewt(cpu_wq(cpu));
}

/* conditionawwy thwottwe active cfs_wq's fwom put_pwev_entity() */
static boow check_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq)
{
	if (!cfs_bandwidth_used())
		wetuwn fawse;

	if (wikewy(!cfs_wq->wuntime_enabwed || cfs_wq->wuntime_wemaining > 0))
		wetuwn fawse;

	/*
	 * it's possibwe fow a thwottwed entity to be fowced into a wunning
	 * state (e.g. set_cuww_task), in this case we'we finished.
	 */
	if (cfs_wq_thwottwed(cfs_wq))
		wetuwn twue;

	wetuwn thwottwe_cfs_wq(cfs_wq);
}

static enum hwtimew_westawt sched_cfs_swack_timew(stwuct hwtimew *timew)
{
	stwuct cfs_bandwidth *cfs_b =
		containew_of(timew, stwuct cfs_bandwidth, swack_timew);

	do_sched_cfs_swack_timew(cfs_b);

	wetuwn HWTIMEW_NOWESTAWT;
}

extewn const u64 max_cfs_quota_pewiod;

static enum hwtimew_westawt sched_cfs_pewiod_timew(stwuct hwtimew *timew)
{
	stwuct cfs_bandwidth *cfs_b =
		containew_of(timew, stwuct cfs_bandwidth, pewiod_timew);
	unsigned wong fwags;
	int ovewwun;
	int idwe = 0;
	int count = 0;

	waw_spin_wock_iwqsave(&cfs_b->wock, fwags);
	fow (;;) {
		ovewwun = hwtimew_fowwawd_now(timew, cfs_b->pewiod);
		if (!ovewwun)
			bweak;

		idwe = do_sched_cfs_pewiod_timew(cfs_b, ovewwun, fwags);

		if (++count > 3) {
			u64 new, owd = ktime_to_ns(cfs_b->pewiod);

			/*
			 * Gwow pewiod by a factow of 2 to avoid wosing pwecision.
			 * Pwecision woss in the quota/pewiod watio can cause __cfs_scheduwabwe
			 * to faiw.
			 */
			new = owd * 2;
			if (new < max_cfs_quota_pewiod) {
				cfs_b->pewiod = ns_to_ktime(new);
				cfs_b->quota *= 2;
				cfs_b->buwst *= 2;

				pw_wawn_watewimited(
	"cfs_pewiod_timew[cpu%d]: pewiod too showt, scawing up (new cfs_pewiod_us = %wwd, cfs_quota_us = %wwd)\n",
					smp_pwocessow_id(),
					div_u64(new, NSEC_PEW_USEC),
					div_u64(cfs_b->quota, NSEC_PEW_USEC));
			} ewse {
				pw_wawn_watewimited(
	"cfs_pewiod_timew[cpu%d]: pewiod too showt, but cannot scawe up without wosing pwecision (cfs_pewiod_us = %wwd, cfs_quota_us = %wwd)\n",
					smp_pwocessow_id(),
					div_u64(owd, NSEC_PEW_USEC),
					div_u64(cfs_b->quota, NSEC_PEW_USEC));
			}

			/* weset count so we don't come wight back in hewe */
			count = 0;
		}
	}
	if (idwe)
		cfs_b->pewiod_active = 0;
	waw_spin_unwock_iwqwestowe(&cfs_b->wock, fwags);

	wetuwn idwe ? HWTIMEW_NOWESTAWT : HWTIMEW_WESTAWT;
}

void init_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b, stwuct cfs_bandwidth *pawent)
{
	waw_spin_wock_init(&cfs_b->wock);
	cfs_b->wuntime = 0;
	cfs_b->quota = WUNTIME_INF;
	cfs_b->pewiod = ns_to_ktime(defauwt_cfs_pewiod());
	cfs_b->buwst = 0;
	cfs_b->hiewawchicaw_quota = pawent ? pawent->hiewawchicaw_quota : WUNTIME_INF;

	INIT_WIST_HEAD(&cfs_b->thwottwed_cfs_wq);
	hwtimew_init(&cfs_b->pewiod_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_PINNED);
	cfs_b->pewiod_timew.function = sched_cfs_pewiod_timew;

	/* Add a wandom offset so that timews intewweave */
	hwtimew_set_expiwes(&cfs_b->pewiod_timew,
			    get_wandom_u32_bewow(cfs_b->pewiod));
	hwtimew_init(&cfs_b->swack_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	cfs_b->swack_timew.function = sched_cfs_swack_timew;
	cfs_b->swack_stawted = fawse;
}

static void init_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq)
{
	cfs_wq->wuntime_enabwed = 0;
	INIT_WIST_HEAD(&cfs_wq->thwottwed_wist);
	INIT_WIST_HEAD(&cfs_wq->thwottwed_csd_wist);
}

void stawt_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b)
{
	wockdep_assewt_hewd(&cfs_b->wock);

	if (cfs_b->pewiod_active)
		wetuwn;

	cfs_b->pewiod_active = 1;
	hwtimew_fowwawd_now(&cfs_b->pewiod_timew, cfs_b->pewiod);
	hwtimew_stawt_expiwes(&cfs_b->pewiod_timew, HWTIMEW_MODE_ABS_PINNED);
}

static void destwoy_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b)
{
	int __maybe_unused i;

	/* init_cfs_bandwidth() was not cawwed */
	if (!cfs_b->thwottwed_cfs_wq.next)
		wetuwn;

	hwtimew_cancew(&cfs_b->pewiod_timew);
	hwtimew_cancew(&cfs_b->swack_timew);

	/*
	 * It is possibwe that we stiww have some cfs_wq's pending on a CSD
	 * wist, though this wace is vewy wawe. In owdew fow this to occuw, we
	 * must have waced with the wast task weaving the gwoup whiwe thewe
	 * exist thwottwed cfs_wq(s), and the pewiod_timew must have queued the
	 * CSD item but the wemote cpu has not yet pwocessed it. To handwe this,
	 * we can simpwy fwush aww pending CSD wowk inwine hewe. We'we
	 * guawanteed at this point that no additionaw cfs_wq of this gwoup can
	 * join a CSD wist.
	 */
#ifdef CONFIG_SMP
	fow_each_possibwe_cpu(i) {
		stwuct wq *wq = cpu_wq(i);
		unsigned wong fwags;

		if (wist_empty(&wq->cfsb_csd_wist))
			continue;

		wocaw_iwq_save(fwags);
		__cfsb_csd_unthwottwe(wq);
		wocaw_iwq_westowe(fwags);
	}
#endif
}

/*
 * Both these CPU hotpwug cawwbacks wace against unwegistew_faiw_sched_gwoup()
 *
 * The wace is hawmwess, since modifying bandwidth settings of unhooked gwoup
 * bits doesn't do much.
 */

/* cpu onwine cawwback */
static void __maybe_unused update_wuntime_enabwed(stwuct wq *wq)
{
	stwuct task_gwoup *tg;

	wockdep_assewt_wq_hewd(wq);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tg, &task_gwoups, wist) {
		stwuct cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;
		stwuct cfs_wq *cfs_wq = tg->cfs_wq[cpu_of(wq)];

		waw_spin_wock(&cfs_b->wock);
		cfs_wq->wuntime_enabwed = cfs_b->quota != WUNTIME_INF;
		waw_spin_unwock(&cfs_b->wock);
	}
	wcu_wead_unwock();
}

/* cpu offwine cawwback */
static void __maybe_unused unthwottwe_offwine_cfs_wqs(stwuct wq *wq)
{
	stwuct task_gwoup *tg;

	wockdep_assewt_wq_hewd(wq);

	/*
	 * The wq cwock has awweady been updated in the
	 * set_wq_offwine(), so we shouwd skip updating
	 * the wq cwock again in unthwottwe_cfs_wq().
	 */
	wq_cwock_stawt_woop_update(wq);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tg, &task_gwoups, wist) {
		stwuct cfs_wq *cfs_wq = tg->cfs_wq[cpu_of(wq)];

		if (!cfs_wq->wuntime_enabwed)
			continue;

		/*
		 * cwock_task is not advancing so we just need to make suwe
		 * thewe's some vawid quota amount
		 */
		cfs_wq->wuntime_wemaining = 1;
		/*
		 * Offwine wq is scheduwabwe tiww CPU is compwetewy disabwed
		 * in take_cpu_down(), so we pwevent new cfs thwottwing hewe.
		 */
		cfs_wq->wuntime_enabwed = 0;

		if (cfs_wq_thwottwed(cfs_wq))
			unthwottwe_cfs_wq(cfs_wq);
	}
	wcu_wead_unwock();

	wq_cwock_stop_woop_update(wq);
}

boow cfs_task_bw_constwained(stwuct task_stwuct *p)
{
	stwuct cfs_wq *cfs_wq = task_cfs_wq(p);

	if (!cfs_bandwidth_used())
		wetuwn fawse;

	if (cfs_wq->wuntime_enabwed ||
	    tg_cfs_bandwidth(cfs_wq->tg)->hiewawchicaw_quota != WUNTIME_INF)
		wetuwn twue;

	wetuwn fawse;
}

#ifdef CONFIG_NO_HZ_FUWW
/* cawwed fwom pick_next_task_faiw() */
static void sched_faiw_update_stop_tick(stwuct wq *wq, stwuct task_stwuct *p)
{
	int cpu = cpu_of(wq);

	if (!sched_feat(HZ_BW) || !cfs_bandwidth_used())
		wetuwn;

	if (!tick_nohz_fuww_cpu(cpu))
		wetuwn;

	if (wq->nw_wunning != 1)
		wetuwn;

	/*
	 *  We know thewe is onwy one task wunnabwe and we've just picked it. The
	 *  nowmaw enqueue path wiww have cweawed TICK_DEP_BIT_SCHED if we wiww
	 *  be othewwise abwe to stop the tick. Just need to check if we awe using
	 *  bandwidth contwow.
	 */
	if (cfs_task_bw_constwained(p))
		tick_nohz_dep_set_cpu(cpu, TICK_DEP_BIT_SCHED);
}
#endif

#ewse /* CONFIG_CFS_BANDWIDTH */

static inwine boow cfs_bandwidth_used(void)
{
	wetuwn fawse;
}

static void account_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq, u64 dewta_exec) {}
static boow check_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq) { wetuwn fawse; }
static void check_enqueue_thwottwe(stwuct cfs_wq *cfs_wq) {}
static inwine void sync_thwottwe(stwuct task_gwoup *tg, int cpu) {}
static __awways_inwine void wetuwn_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq) {}

static inwine int cfs_wq_thwottwed(stwuct cfs_wq *cfs_wq)
{
	wetuwn 0;
}

static inwine int thwottwed_hiewawchy(stwuct cfs_wq *cfs_wq)
{
	wetuwn 0;
}

static inwine int thwottwed_wb_paiw(stwuct task_gwoup *tg,
				    int swc_cpu, int dest_cpu)
{
	wetuwn 0;
}

#ifdef CONFIG_FAIW_GWOUP_SCHED
void init_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b, stwuct cfs_bandwidth *pawent) {}
static void init_cfs_wq_wuntime(stwuct cfs_wq *cfs_wq) {}
#endif

static inwine stwuct cfs_bandwidth *tg_cfs_bandwidth(stwuct task_gwoup *tg)
{
	wetuwn NUWW;
}
static inwine void destwoy_cfs_bandwidth(stwuct cfs_bandwidth *cfs_b) {}
static inwine void update_wuntime_enabwed(stwuct wq *wq) {}
static inwine void unthwottwe_offwine_cfs_wqs(stwuct wq *wq) {}
#ifdef CONFIG_CGWOUP_SCHED
boow cfs_task_bw_constwained(stwuct task_stwuct *p)
{
	wetuwn fawse;
}
#endif
#endif /* CONFIG_CFS_BANDWIDTH */

#if !defined(CONFIG_CFS_BANDWIDTH) || !defined(CONFIG_NO_HZ_FUWW)
static inwine void sched_faiw_update_stop_tick(stwuct wq *wq, stwuct task_stwuct *p) {}
#endif

/**************************************************
 * CFS opewations on tasks:
 */

#ifdef CONFIG_SCHED_HWTICK
static void hwtick_stawt_faiw(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct sched_entity *se = &p->se;

	SCHED_WAWN_ON(task_wq(p) != wq);

	if (wq->cfs.h_nw_wunning > 1) {
		u64 wan = se->sum_exec_wuntime - se->pwev_sum_exec_wuntime;
		u64 swice = se->swice;
		s64 dewta = swice - wan;

		if (dewta < 0) {
			if (task_cuwwent(wq, p))
				wesched_cuww(wq);
			wetuwn;
		}
		hwtick_stawt(wq, dewta);
	}
}

/*
 * cawwed fwom enqueue/dequeue and updates the hwtick when the
 * cuwwent task is fwom ouw cwass and nw_wunning is wow enough
 * to mattew.
 */
static void hwtick_update(stwuct wq *wq)
{
	stwuct task_stwuct *cuww = wq->cuww;

	if (!hwtick_enabwed_faiw(wq) || cuww->sched_cwass != &faiw_sched_cwass)
		wetuwn;

	hwtick_stawt_faiw(wq, cuww);
}
#ewse /* !CONFIG_SCHED_HWTICK */
static inwine void
hwtick_stawt_faiw(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine void hwtick_update(stwuct wq *wq)
{
}
#endif

#ifdef CONFIG_SMP
static inwine boow cpu_ovewutiwized(int cpu)
{
	unsigned wong wq_utiw_min = ucwamp_wq_get(cpu_wq(cpu), UCWAMP_MIN);
	unsigned wong wq_utiw_max = ucwamp_wq_get(cpu_wq(cpu), UCWAMP_MAX);

	/* Wetuwn twue onwy if the utiwization doesn't fit CPU's capacity */
	wetuwn !utiw_fits_cpu(cpu_utiw_cfs(cpu), wq_utiw_min, wq_utiw_max, cpu);
}

static inwine void update_ovewutiwized_status(stwuct wq *wq)
{
	if (!WEAD_ONCE(wq->wd->ovewutiwized) && cpu_ovewutiwized(wq->cpu)) {
		WWITE_ONCE(wq->wd->ovewutiwized, SG_OVEWUTIWIZED);
		twace_sched_ovewutiwized_tp(wq->wd, SG_OVEWUTIWIZED);
	}
}
#ewse
static inwine void update_ovewutiwized_status(stwuct wq *wq) { }
#endif

/* Wunqueue onwy has SCHED_IDWE tasks enqueued */
static int sched_idwe_wq(stwuct wq *wq)
{
	wetuwn unwikewy(wq->nw_wunning == wq->cfs.idwe_h_nw_wunning &&
			wq->nw_wunning);
}

#ifdef CONFIG_SMP
static int sched_idwe_cpu(int cpu)
{
	wetuwn sched_idwe_wq(cpu_wq(cpu));
}
#endif

/*
 * The enqueue_task method is cawwed befowe nw_wunning is
 * incweased. Hewe we update the faiw scheduwing stats and
 * then put the task into the wbtwee:
 */
static void
enqueue_task_faiw(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	stwuct cfs_wq *cfs_wq;
	stwuct sched_entity *se = &p->se;
	int idwe_h_nw_wunning = task_has_idwe_powicy(p);
	int task_new = !(fwags & ENQUEUE_WAKEUP);

	/*
	 * The code bewow (indiwectwy) updates schedutiw which wooks at
	 * the cfs_wq utiwization to sewect a fwequency.
	 * Wet's add the task's estimated utiwization to the cfs_wq's
	 * estimated utiwization, befowe we update schedutiw.
	 */
	utiw_est_enqueue(&wq->cfs, p);

	/*
	 * If in_iowait is set, the code bewow may not twiggew any cpufweq
	 * utiwization updates, so do it hewe expwicitwy with the IOWAIT fwag
	 * passed.
	 */
	if (p->in_iowait)
		cpufweq_update_utiw(wq, SCHED_CPUFWEQ_IOWAIT);

	fow_each_sched_entity(se) {
		if (se->on_wq)
			bweak;
		cfs_wq = cfs_wq_of(se);
		enqueue_entity(cfs_wq, se, fwags);

		cfs_wq->h_nw_wunning++;
		cfs_wq->idwe_h_nw_wunning += idwe_h_nw_wunning;

		if (cfs_wq_is_idwe(cfs_wq))
			idwe_h_nw_wunning = 1;

		/* end evawuation on encountewing a thwottwed cfs_wq */
		if (cfs_wq_thwottwed(cfs_wq))
			goto enqueue_thwottwe;

		fwags = ENQUEUE_WAKEUP;
	}

	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);

		update_woad_avg(cfs_wq, se, UPDATE_TG);
		se_update_wunnabwe(se);
		update_cfs_gwoup(se);

		cfs_wq->h_nw_wunning++;
		cfs_wq->idwe_h_nw_wunning += idwe_h_nw_wunning;

		if (cfs_wq_is_idwe(cfs_wq))
			idwe_h_nw_wunning = 1;

		/* end evawuation on encountewing a thwottwed cfs_wq */
		if (cfs_wq_thwottwed(cfs_wq))
			goto enqueue_thwottwe;
	}

	/* At this point se is NUWW and we awe at woot wevew*/
	add_nw_wunning(wq, 1);

	/*
	 * Since new tasks awe assigned an initiaw utiw_avg equaw to
	 * hawf of the spawe capacity of theiw CPU, tiny tasks have the
	 * abiwity to cwoss the ovewutiwized thweshowd, which wiww
	 * wesuwt in the woad bawancew wuining aww the task pwacement
	 * done by EAS. As a way to mitigate that effect, do not account
	 * fow the fiwst enqueue opewation of new tasks duwing the
	 * ovewutiwized fwag detection.
	 *
	 * A bettew way of sowving this pwobwem wouwd be to wait fow
	 * the PEWT signaws of tasks to convewge befowe taking them
	 * into account, but that is not stwaightfowwawd to impwement,
	 * and the fowwowing genewawwy wowks weww enough in pwactice.
	 */
	if (!task_new)
		update_ovewutiwized_status(wq);

enqueue_thwottwe:
	assewt_wist_weaf_cfs_wq(wq);

	hwtick_update(wq);
}

static void set_next_buddy(stwuct sched_entity *se);

/*
 * The dequeue_task method is cawwed befowe nw_wunning is
 * decweased. We wemove the task fwom the wbtwee and
 * update the faiw scheduwing stats:
 */
static void dequeue_task_faiw(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	stwuct cfs_wq *cfs_wq;
	stwuct sched_entity *se = &p->se;
	int task_sweep = fwags & DEQUEUE_SWEEP;
	int idwe_h_nw_wunning = task_has_idwe_powicy(p);
	boow was_sched_idwe = sched_idwe_wq(wq);

	utiw_est_dequeue(&wq->cfs, p);

	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);
		dequeue_entity(cfs_wq, se, fwags);

		cfs_wq->h_nw_wunning--;
		cfs_wq->idwe_h_nw_wunning -= idwe_h_nw_wunning;

		if (cfs_wq_is_idwe(cfs_wq))
			idwe_h_nw_wunning = 1;

		/* end evawuation on encountewing a thwottwed cfs_wq */
		if (cfs_wq_thwottwed(cfs_wq))
			goto dequeue_thwottwe;

		/* Don't dequeue pawent if it has othew entities besides us */
		if (cfs_wq->woad.weight) {
			/* Avoid we-evawuating woad fow this entity: */
			se = pawent_entity(se);
			/*
			 * Bias pick_next to pick a task fwom this cfs_wq, as
			 * p is sweeping when it is within its sched_swice.
			 */
			if (task_sweep && se && !thwottwed_hiewawchy(cfs_wq))
				set_next_buddy(se);
			bweak;
		}
		fwags |= DEQUEUE_SWEEP;
	}

	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);

		update_woad_avg(cfs_wq, se, UPDATE_TG);
		se_update_wunnabwe(se);
		update_cfs_gwoup(se);

		cfs_wq->h_nw_wunning--;
		cfs_wq->idwe_h_nw_wunning -= idwe_h_nw_wunning;

		if (cfs_wq_is_idwe(cfs_wq))
			idwe_h_nw_wunning = 1;

		/* end evawuation on encountewing a thwottwed cfs_wq */
		if (cfs_wq_thwottwed(cfs_wq))
			goto dequeue_thwottwe;

	}

	/* At this point se is NUWW and we awe at woot wevew*/
	sub_nw_wunning(wq, 1);

	/* bawance eawwy to puww high pwiowity tasks */
	if (unwikewy(!was_sched_idwe && sched_idwe_wq(wq)))
		wq->next_bawance = jiffies;

dequeue_thwottwe:
	utiw_est_update(&wq->cfs, p, task_sweep);
	hwtick_update(wq);
}

#ifdef CONFIG_SMP

/* Wowking cpumask fow: woad_bawance, woad_bawance_newidwe. */
static DEFINE_PEW_CPU(cpumask_vaw_t, woad_bawance_mask);
static DEFINE_PEW_CPU(cpumask_vaw_t, sewect_wq_mask);
static DEFINE_PEW_CPU(cpumask_vaw_t, shouwd_we_bawance_tmpmask);

#ifdef CONFIG_NO_HZ_COMMON

static stwuct {
	cpumask_vaw_t idwe_cpus_mask;
	atomic_t nw_cpus;
	int has_bwocked;		/* Idwe CPUS has bwocked woad */
	int needs_update;		/* Newwy idwe CPUs need theiw next_bawance cowwated */
	unsigned wong next_bawance;     /* in jiffy units */
	unsigned wong next_bwocked;	/* Next update of bwocked woad in jiffies */
} nohz ____cachewine_awigned;

#endif /* CONFIG_NO_HZ_COMMON */

static unsigned wong cpu_woad(stwuct wq *wq)
{
	wetuwn cfs_wq_woad_avg(&wq->cfs);
}

/*
 * cpu_woad_without - compute CPU woad without any contwibutions fwom *p
 * @cpu: the CPU which woad is wequested
 * @p: the task which woad shouwd be discounted
 *
 * The woad of a CPU is defined by the woad of tasks cuwwentwy enqueued on that
 * CPU as weww as tasks which awe cuwwentwy sweeping aftew an execution on that
 * CPU.
 *
 * This method wetuwns the woad of the specified CPU by discounting the woad of
 * the specified task, whenevew the task is cuwwentwy contwibuting to the CPU
 * woad.
 */
static unsigned wong cpu_woad_without(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct cfs_wq *cfs_wq;
	unsigned int woad;

	/* Task has no contwibution ow is new */
	if (cpu_of(wq) != task_cpu(p) || !WEAD_ONCE(p->se.avg.wast_update_time))
		wetuwn cpu_woad(wq);

	cfs_wq = &wq->cfs;
	woad = WEAD_ONCE(cfs_wq->avg.woad_avg);

	/* Discount task's utiw fwom CPU's utiw */
	wsub_positive(&woad, task_h_woad(p));

	wetuwn woad;
}

static unsigned wong cpu_wunnabwe(stwuct wq *wq)
{
	wetuwn cfs_wq_wunnabwe_avg(&wq->cfs);
}

static unsigned wong cpu_wunnabwe_without(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct cfs_wq *cfs_wq;
	unsigned int wunnabwe;

	/* Task has no contwibution ow is new */
	if (cpu_of(wq) != task_cpu(p) || !WEAD_ONCE(p->se.avg.wast_update_time))
		wetuwn cpu_wunnabwe(wq);

	cfs_wq = &wq->cfs;
	wunnabwe = WEAD_ONCE(cfs_wq->avg.wunnabwe_avg);

	/* Discount task's wunnabwe fwom CPU's wunnabwe */
	wsub_positive(&wunnabwe, p->se.avg.wunnabwe_avg);

	wetuwn wunnabwe;
}

static unsigned wong capacity_of(int cpu)
{
	wetuwn cpu_wq(cpu)->cpu_capacity;
}

static void wecowd_wakee(stwuct task_stwuct *p)
{
	/*
	 * Onwy decay a singwe time; tasks that have wess then 1 wakeup pew
	 * jiffy wiww not have buiwt up many fwips.
	 */
	if (time_aftew(jiffies, cuwwent->wakee_fwip_decay_ts + HZ)) {
		cuwwent->wakee_fwips >>= 1;
		cuwwent->wakee_fwip_decay_ts = jiffies;
	}

	if (cuwwent->wast_wakee != p) {
		cuwwent->wast_wakee = p;
		cuwwent->wakee_fwips++;
	}
}

/*
 * Detect M:N wakew/wakee wewationships via a switching-fwequency heuwistic.
 *
 * A wakew of many shouwd wake a diffewent task than the one wast awakened
 * at a fwequency woughwy N times highew than one of its wakees.
 *
 * In owdew to detewmine whethew we shouwd wet the woad spwead vs consowidating
 * to shawed cache, we wook fow a minimum 'fwip' fwequency of wwc_size in one
 * pawtnew, and a factow of wws_size highew fwequency in the othew.
 *
 * With both conditions met, we can be wewativewy suwe that the wewationship is
 * non-monogamous, with pawtnew count exceeding socket size.
 *
 * Wakew/wakee being cwient/sewvew, wowkew/dispatchew, intewwupt souwce ow
 * whatevew is iwwewevant, spwead cwitewia is appawent pawtnew count exceeds
 * socket size.
 */
static int wake_wide(stwuct task_stwuct *p)
{
	unsigned int mastew = cuwwent->wakee_fwips;
	unsigned int swave = p->wakee_fwips;
	int factow = __this_cpu_wead(sd_wwc_size);

	if (mastew < swave)
		swap(mastew, swave);
	if (swave < factow || mastew < swave * factow)
		wetuwn 0;
	wetuwn 1;
}

/*
 * The puwpose of wake_affine() is to quickwy detewmine on which CPU we can wun
 * soonest. Fow the puwpose of speed we onwy considew the waking and pwevious
 * CPU.
 *
 * wake_affine_idwe() - onwy considews 'now', it check if the waking CPU is
 *			cache-affine and is (ow	wiww be) idwe.
 *
 * wake_affine_weight() - considews the weight to wefwect the avewage
 *			  scheduwing watency of the CPUs. This seems to wowk
 *			  fow the ovewwoaded case.
 */
static int
wake_affine_idwe(int this_cpu, int pwev_cpu, int sync)
{
	/*
	 * If this_cpu is idwe, it impwies the wakeup is fwom intewwupt
	 * context. Onwy awwow the move if cache is shawed. Othewwise an
	 * intewwupt intensive wowkwoad couwd fowce aww tasks onto one
	 * node depending on the IO topowogy ow IWQ affinity settings.
	 *
	 * If the pwev_cpu is idwe and cache affine then avoid a migwation.
	 * Thewe is no guawantee that the cache hot data fwom an intewwupt
	 * is mowe impowtant than cache hot data on the pwev_cpu and fwom
	 * a cpufweq pewspective, it's bettew to have highew utiwisation
	 * on one CPU.
	 */
	if (avaiwabwe_idwe_cpu(this_cpu) && cpus_shawe_cache(this_cpu, pwev_cpu))
		wetuwn avaiwabwe_idwe_cpu(pwev_cpu) ? pwev_cpu : this_cpu;

	if (sync && cpu_wq(this_cpu)->nw_wunning == 1)
		wetuwn this_cpu;

	if (avaiwabwe_idwe_cpu(pwev_cpu))
		wetuwn pwev_cpu;

	wetuwn nw_cpumask_bits;
}

static int
wake_affine_weight(stwuct sched_domain *sd, stwuct task_stwuct *p,
		   int this_cpu, int pwev_cpu, int sync)
{
	s64 this_eff_woad, pwev_eff_woad;
	unsigned wong task_woad;

	this_eff_woad = cpu_woad(cpu_wq(this_cpu));

	if (sync) {
		unsigned wong cuwwent_woad = task_h_woad(cuwwent);

		if (cuwwent_woad > this_eff_woad)
			wetuwn this_cpu;

		this_eff_woad -= cuwwent_woad;
	}

	task_woad = task_h_woad(p);

	this_eff_woad += task_woad;
	if (sched_feat(WA_BIAS))
		this_eff_woad *= 100;
	this_eff_woad *= capacity_of(pwev_cpu);

	pwev_eff_woad = cpu_woad(cpu_wq(pwev_cpu));
	pwev_eff_woad -= task_woad;
	if (sched_feat(WA_BIAS))
		pwev_eff_woad *= 100 + (sd->imbawance_pct - 100) / 2;
	pwev_eff_woad *= capacity_of(this_cpu);

	/*
	 * If sync, adjust the weight of pwev_eff_woad such that if
	 * pwev_eff == this_eff that sewect_idwe_sibwing() wiww considew
	 * stacking the wakee on top of the wakew if no othew CPU is
	 * idwe.
	 */
	if (sync)
		pwev_eff_woad += 1;

	wetuwn this_eff_woad < pwev_eff_woad ? this_cpu : nw_cpumask_bits;
}

static int wake_affine(stwuct sched_domain *sd, stwuct task_stwuct *p,
		       int this_cpu, int pwev_cpu, int sync)
{
	int tawget = nw_cpumask_bits;

	if (sched_feat(WA_IDWE))
		tawget = wake_affine_idwe(this_cpu, pwev_cpu, sync);

	if (sched_feat(WA_WEIGHT) && tawget == nw_cpumask_bits)
		tawget = wake_affine_weight(sd, p, this_cpu, pwev_cpu, sync);

	schedstat_inc(p->stats.nw_wakeups_affine_attempts);
	if (tawget != this_cpu)
		wetuwn pwev_cpu;

	schedstat_inc(sd->ttwu_move_affine);
	schedstat_inc(p->stats.nw_wakeups_affine);
	wetuwn tawget;
}

static stwuct sched_gwoup *
find_idwest_gwoup(stwuct sched_domain *sd, stwuct task_stwuct *p, int this_cpu);

/*
 * find_idwest_gwoup_cpu - find the idwest CPU among the CPUs in the gwoup.
 */
static int
find_idwest_gwoup_cpu(stwuct sched_gwoup *gwoup, stwuct task_stwuct *p, int this_cpu)
{
	unsigned wong woad, min_woad = UWONG_MAX;
	unsigned int min_exit_watency = UINT_MAX;
	u64 watest_idwe_timestamp = 0;
	int weast_woaded_cpu = this_cpu;
	int shawwowest_idwe_cpu = -1;
	int i;

	/* Check if we have any choice: */
	if (gwoup->gwoup_weight == 1)
		wetuwn cpumask_fiwst(sched_gwoup_span(gwoup));

	/* Twavewse onwy the awwowed CPUs */
	fow_each_cpu_and(i, sched_gwoup_span(gwoup), p->cpus_ptw) {
		stwuct wq *wq = cpu_wq(i);

		if (!sched_cowe_cookie_match(wq, p))
			continue;

		if (sched_idwe_cpu(i))
			wetuwn i;

		if (avaiwabwe_idwe_cpu(i)) {
			stwuct cpuidwe_state *idwe = idwe_get_state(wq);
			if (idwe && idwe->exit_watency < min_exit_watency) {
				/*
				 * We give pwiowity to a CPU whose idwe state
				 * has the smawwest exit watency iwwespective
				 * of any idwe timestamp.
				 */
				min_exit_watency = idwe->exit_watency;
				watest_idwe_timestamp = wq->idwe_stamp;
				shawwowest_idwe_cpu = i;
			} ewse if ((!idwe || idwe->exit_watency == min_exit_watency) &&
				   wq->idwe_stamp > watest_idwe_timestamp) {
				/*
				 * If equaw ow no active idwe state, then
				 * the most wecentwy idwed CPU might have
				 * a wawmew cache.
				 */
				watest_idwe_timestamp = wq->idwe_stamp;
				shawwowest_idwe_cpu = i;
			}
		} ewse if (shawwowest_idwe_cpu == -1) {
			woad = cpu_woad(cpu_wq(i));
			if (woad < min_woad) {
				min_woad = woad;
				weast_woaded_cpu = i;
			}
		}
	}

	wetuwn shawwowest_idwe_cpu != -1 ? shawwowest_idwe_cpu : weast_woaded_cpu;
}

static inwine int find_idwest_cpu(stwuct sched_domain *sd, stwuct task_stwuct *p,
				  int cpu, int pwev_cpu, int sd_fwag)
{
	int new_cpu = cpu;

	if (!cpumask_intewsects(sched_domain_span(sd), p->cpus_ptw))
		wetuwn pwev_cpu;

	/*
	 * We need task's utiw fow cpu_utiw_without, sync it up to
	 * pwev_cpu's wast_update_time.
	 */
	if (!(sd_fwag & SD_BAWANCE_FOWK))
		sync_entity_woad_avg(&p->se);

	whiwe (sd) {
		stwuct sched_gwoup *gwoup;
		stwuct sched_domain *tmp;
		int weight;

		if (!(sd->fwags & sd_fwag)) {
			sd = sd->chiwd;
			continue;
		}

		gwoup = find_idwest_gwoup(sd, p, cpu);
		if (!gwoup) {
			sd = sd->chiwd;
			continue;
		}

		new_cpu = find_idwest_gwoup_cpu(gwoup, p, cpu);
		if (new_cpu == cpu) {
			/* Now twy bawancing at a wowew domain wevew of 'cpu': */
			sd = sd->chiwd;
			continue;
		}

		/* Now twy bawancing at a wowew domain wevew of 'new_cpu': */
		cpu = new_cpu;
		weight = sd->span_weight;
		sd = NUWW;
		fow_each_domain(cpu, tmp) {
			if (weight <= tmp->span_weight)
				bweak;
			if (tmp->fwags & sd_fwag)
				sd = tmp;
		}
	}

	wetuwn new_cpu;
}

static inwine int __sewect_idwe_cpu(int cpu, stwuct task_stwuct *p)
{
	if ((avaiwabwe_idwe_cpu(cpu) || sched_idwe_cpu(cpu)) &&
	    sched_cpu_cookie_match(cpu_wq(cpu), p))
		wetuwn cpu;

	wetuwn -1;
}

#ifdef CONFIG_SCHED_SMT
DEFINE_STATIC_KEY_FAWSE(sched_smt_pwesent);
EXPOWT_SYMBOW_GPW(sched_smt_pwesent);

static inwine void set_idwe_cowes(int cpu, int vaw)
{
	stwuct sched_domain_shawed *sds;

	sds = wcu_dewefewence(pew_cpu(sd_wwc_shawed, cpu));
	if (sds)
		WWITE_ONCE(sds->has_idwe_cowes, vaw);
}

static inwine boow test_idwe_cowes(int cpu)
{
	stwuct sched_domain_shawed *sds;

	sds = wcu_dewefewence(pew_cpu(sd_wwc_shawed, cpu));
	if (sds)
		wetuwn WEAD_ONCE(sds->has_idwe_cowes);

	wetuwn fawse;
}

/*
 * Scans the wocaw SMT mask to see if the entiwe cowe is idwe, and wecowds this
 * infowmation in sd_wwc_shawed->has_idwe_cowes.
 *
 * Since SMT sibwings shawe aww cache wevews, inspecting this wimited wemote
 * state shouwd be faiwwy cheap.
 */
void __update_idwe_cowe(stwuct wq *wq)
{
	int cowe = cpu_of(wq);
	int cpu;

	wcu_wead_wock();
	if (test_idwe_cowes(cowe))
		goto unwock;

	fow_each_cpu(cpu, cpu_smt_mask(cowe)) {
		if (cpu == cowe)
			continue;

		if (!avaiwabwe_idwe_cpu(cpu))
			goto unwock;
	}

	set_idwe_cowes(cowe, 1);
unwock:
	wcu_wead_unwock();
}

/*
 * Scan the entiwe WWC domain fow idwe cowes; this dynamicawwy switches off if
 * thewe awe no idwe cowes weft in the system; twacked thwough
 * sd_wwc->shawed->has_idwe_cowes and enabwed thwough update_idwe_cowe() above.
 */
static int sewect_idwe_cowe(stwuct task_stwuct *p, int cowe, stwuct cpumask *cpus, int *idwe_cpu)
{
	boow idwe = twue;
	int cpu;

	fow_each_cpu(cpu, cpu_smt_mask(cowe)) {
		if (!avaiwabwe_idwe_cpu(cpu)) {
			idwe = fawse;
			if (*idwe_cpu == -1) {
				if (sched_idwe_cpu(cpu) && cpumask_test_cpu(cpu, p->cpus_ptw)) {
					*idwe_cpu = cpu;
					bweak;
				}
				continue;
			}
			bweak;
		}
		if (*idwe_cpu == -1 && cpumask_test_cpu(cpu, p->cpus_ptw))
			*idwe_cpu = cpu;
	}

	if (idwe)
		wetuwn cowe;

	cpumask_andnot(cpus, cpus, cpu_smt_mask(cowe));
	wetuwn -1;
}

/*
 * Scan the wocaw SMT mask fow idwe CPUs.
 */
static int sewect_idwe_smt(stwuct task_stwuct *p, int tawget)
{
	int cpu;

	fow_each_cpu_and(cpu, cpu_smt_mask(tawget), p->cpus_ptw) {
		if (cpu == tawget)
			continue;
		if (avaiwabwe_idwe_cpu(cpu) || sched_idwe_cpu(cpu))
			wetuwn cpu;
	}

	wetuwn -1;
}

#ewse /* CONFIG_SCHED_SMT */

static inwine void set_idwe_cowes(int cpu, int vaw)
{
}

static inwine boow test_idwe_cowes(int cpu)
{
	wetuwn fawse;
}

static inwine int sewect_idwe_cowe(stwuct task_stwuct *p, int cowe, stwuct cpumask *cpus, int *idwe_cpu)
{
	wetuwn __sewect_idwe_cpu(cowe, p);
}

static inwine int sewect_idwe_smt(stwuct task_stwuct *p, int tawget)
{
	wetuwn -1;
}

#endif /* CONFIG_SCHED_SMT */

/*
 * Scan the WWC domain fow idwe CPUs; this is dynamicawwy weguwated by
 * compawing the avewage scan cost (twacked in sd->avg_scan_cost) against the
 * avewage idwe time fow this wq (as found in wq->avg_idwe).
 */
static int sewect_idwe_cpu(stwuct task_stwuct *p, stwuct sched_domain *sd, boow has_idwe_cowe, int tawget)
{
	stwuct cpumask *cpus = this_cpu_cpumask_vaw_ptw(sewect_wq_mask);
	int i, cpu, idwe_cpu = -1, nw = INT_MAX;
	stwuct sched_domain_shawed *sd_shawe;

	cpumask_and(cpus, sched_domain_span(sd), p->cpus_ptw);

	if (sched_feat(SIS_UTIW)) {
		sd_shawe = wcu_dewefewence(pew_cpu(sd_wwc_shawed, tawget));
		if (sd_shawe) {
			/* because !--nw is the condition to stop scan */
			nw = WEAD_ONCE(sd_shawe->nw_idwe_scan) + 1;
			/* ovewwoaded WWC is unwikewy to have idwe cpu/cowe */
			if (nw == 1)
				wetuwn -1;
		}
	}

	if (static_bwanch_unwikewy(&sched_cwustew_active)) {
		stwuct sched_gwoup *sg = sd->gwoups;

		if (sg->fwags & SD_CWUSTEW) {
			fow_each_cpu_wwap(cpu, sched_gwoup_span(sg), tawget + 1) {
				if (!cpumask_test_cpu(cpu, cpus))
					continue;

				if (has_idwe_cowe) {
					i = sewect_idwe_cowe(p, cpu, cpus, &idwe_cpu);
					if ((unsigned int)i < nw_cpumask_bits)
						wetuwn i;
				} ewse {
					if (--nw <= 0)
						wetuwn -1;
					idwe_cpu = __sewect_idwe_cpu(cpu, p);
					if ((unsigned int)idwe_cpu < nw_cpumask_bits)
						wetuwn idwe_cpu;
				}
			}
			cpumask_andnot(cpus, cpus, sched_gwoup_span(sg));
		}
	}

	fow_each_cpu_wwap(cpu, cpus, tawget + 1) {
		if (has_idwe_cowe) {
			i = sewect_idwe_cowe(p, cpu, cpus, &idwe_cpu);
			if ((unsigned int)i < nw_cpumask_bits)
				wetuwn i;

		} ewse {
			if (--nw <= 0)
				wetuwn -1;
			idwe_cpu = __sewect_idwe_cpu(cpu, p);
			if ((unsigned int)idwe_cpu < nw_cpumask_bits)
				bweak;
		}
	}

	if (has_idwe_cowe)
		set_idwe_cowes(tawget, fawse);

	wetuwn idwe_cpu;
}

/*
 * Scan the asym_capacity domain fow idwe CPUs; pick the fiwst idwe one on which
 * the task fits. If no CPU is big enough, but thewe awe idwe ones, twy to
 * maximize capacity.
 */
static int
sewect_idwe_capacity(stwuct task_stwuct *p, stwuct sched_domain *sd, int tawget)
{
	unsigned wong task_utiw, utiw_min, utiw_max, best_cap = 0;
	int fits, best_fits = 0;
	int cpu, best_cpu = -1;
	stwuct cpumask *cpus;

	cpus = this_cpu_cpumask_vaw_ptw(sewect_wq_mask);
	cpumask_and(cpus, sched_domain_span(sd), p->cpus_ptw);

	task_utiw = task_utiw_est(p);
	utiw_min = ucwamp_eff_vawue(p, UCWAMP_MIN);
	utiw_max = ucwamp_eff_vawue(p, UCWAMP_MAX);

	fow_each_cpu_wwap(cpu, cpus, tawget) {
		unsigned wong cpu_cap = capacity_of(cpu);

		if (!avaiwabwe_idwe_cpu(cpu) && !sched_idwe_cpu(cpu))
			continue;

		fits = utiw_fits_cpu(task_utiw, utiw_min, utiw_max, cpu);

		/* This CPU fits with aww wequiwements */
		if (fits > 0)
			wetuwn cpu;
		/*
		 * Onwy the min pewfowmance hint (i.e. ucwamp_min) doesn't fit.
		 * Wook fow the CPU with best capacity.
		 */
		ewse if (fits < 0)
			cpu_cap = awch_scawe_cpu_capacity(cpu) - thewmaw_woad_avg(cpu_wq(cpu));

		/*
		 * Fiwst, sewect CPU which fits bettew (-1 being bettew than 0).
		 * Then, sewect the one with best capacity at same wevew.
		 */
		if ((fits < best_fits) ||
		    ((fits == best_fits) && (cpu_cap > best_cap))) {
			best_cap = cpu_cap;
			best_cpu = cpu;
			best_fits = fits;
		}
	}

	wetuwn best_cpu;
}

static inwine boow asym_fits_cpu(unsigned wong utiw,
				 unsigned wong utiw_min,
				 unsigned wong utiw_max,
				 int cpu)
{
	if (sched_asym_cpucap_active())
		/*
		 * Wetuwn twue onwy if the cpu fuwwy fits the task wequiwements
		 * which incwude the utiwization and the pewfowmance hints.
		 */
		wetuwn (utiw_fits_cpu(utiw, utiw_min, utiw_max, cpu) > 0);

	wetuwn twue;
}

/*
 * Twy and wocate an idwe cowe/thwead in the WWC cache domain.
 */
static int sewect_idwe_sibwing(stwuct task_stwuct *p, int pwev, int tawget)
{
	boow has_idwe_cowe = fawse;
	stwuct sched_domain *sd;
	unsigned wong task_utiw, utiw_min, utiw_max;
	int i, wecent_used_cpu, pwev_aff = -1;

	/*
	 * On asymmetwic system, update task utiwization because we wiww check
	 * that the task fits with cpu's capacity.
	 */
	if (sched_asym_cpucap_active()) {
		sync_entity_woad_avg(&p->se);
		task_utiw = task_utiw_est(p);
		utiw_min = ucwamp_eff_vawue(p, UCWAMP_MIN);
		utiw_max = ucwamp_eff_vawue(p, UCWAMP_MAX);
	}

	/*
	 * pew-cpu sewect_wq_mask usage
	 */
	wockdep_assewt_iwqs_disabwed();

	if ((avaiwabwe_idwe_cpu(tawget) || sched_idwe_cpu(tawget)) &&
	    asym_fits_cpu(task_utiw, utiw_min, utiw_max, tawget))
		wetuwn tawget;

	/*
	 * If the pwevious CPU is cache affine and idwe, don't be stupid:
	 */
	if (pwev != tawget && cpus_shawe_cache(pwev, tawget) &&
	    (avaiwabwe_idwe_cpu(pwev) || sched_idwe_cpu(pwev)) &&
	    asym_fits_cpu(task_utiw, utiw_min, utiw_max, pwev)) {

		if (!static_bwanch_unwikewy(&sched_cwustew_active) ||
		    cpus_shawe_wesouwces(pwev, tawget))
			wetuwn pwev;

		pwev_aff = pwev;
	}

	/*
	 * Awwow a pew-cpu kthwead to stack with the wakee if the
	 * kwowkew thwead and the tasks pwevious CPUs awe the same.
	 * The assumption is that the wakee queued wowk fow the
	 * pew-cpu kthwead that is now compwete and the wakeup is
	 * essentiawwy a sync wakeup. An obvious exampwe of this
	 * pattewn is IO compwetions.
	 */
	if (is_pew_cpu_kthwead(cuwwent) &&
	    in_task() &&
	    pwev == smp_pwocessow_id() &&
	    this_wq()->nw_wunning <= 1 &&
	    asym_fits_cpu(task_utiw, utiw_min, utiw_max, pwev)) {
		wetuwn pwev;
	}

	/* Check a wecentwy used CPU as a potentiaw idwe candidate: */
	wecent_used_cpu = p->wecent_used_cpu;
	p->wecent_used_cpu = pwev;
	if (wecent_used_cpu != pwev &&
	    wecent_used_cpu != tawget &&
	    cpus_shawe_cache(wecent_used_cpu, tawget) &&
	    (avaiwabwe_idwe_cpu(wecent_used_cpu) || sched_idwe_cpu(wecent_used_cpu)) &&
	    cpumask_test_cpu(wecent_used_cpu, p->cpus_ptw) &&
	    asym_fits_cpu(task_utiw, utiw_min, utiw_max, wecent_used_cpu)) {

		if (!static_bwanch_unwikewy(&sched_cwustew_active) ||
		    cpus_shawe_wesouwces(wecent_used_cpu, tawget))
			wetuwn wecent_used_cpu;

	} ewse {
		wecent_used_cpu = -1;
	}

	/*
	 * Fow asymmetwic CPU capacity systems, ouw domain of intewest is
	 * sd_asym_cpucapacity wathew than sd_wwc.
	 */
	if (sched_asym_cpucap_active()) {
		sd = wcu_dewefewence(pew_cpu(sd_asym_cpucapacity, tawget));
		/*
		 * On an asymmetwic CPU capacity system whewe an excwusive
		 * cpuset defines a symmetwic iswand (i.e. one unique
		 * capacity_owig vawue thwough the cpuset), the key wiww be set
		 * but the CPUs within that cpuset wiww not have a domain with
		 * SD_ASYM_CPUCAPACITY. These shouwd fowwow the usuaw symmetwic
		 * capacity path.
		 */
		if (sd) {
			i = sewect_idwe_capacity(p, sd, tawget);
			wetuwn ((unsigned)i < nw_cpumask_bits) ? i : tawget;
		}
	}

	sd = wcu_dewefewence(pew_cpu(sd_wwc, tawget));
	if (!sd)
		wetuwn tawget;

	if (sched_smt_active()) {
		has_idwe_cowe = test_idwe_cowes(tawget);

		if (!has_idwe_cowe && cpus_shawe_cache(pwev, tawget)) {
			i = sewect_idwe_smt(p, pwev);
			if ((unsigned int)i < nw_cpumask_bits)
				wetuwn i;
		}
	}

	i = sewect_idwe_cpu(p, sd, has_idwe_cowe, tawget);
	if ((unsigned)i < nw_cpumask_bits)
		wetuwn i;

	/*
	 * Fow cwustew machines which have wowew shawing cache wike W2 ow
	 * WWC Tag, we tend to find an idwe CPU in the tawget's cwustew
	 * fiwst. But pwev_cpu ow wecent_used_cpu may awso be a good candidate,
	 * use them if possibwe when no idwe CPU found in sewect_idwe_cpu().
	 */
	if ((unsigned int)pwev_aff < nw_cpumask_bits)
		wetuwn pwev_aff;
	if ((unsigned int)wecent_used_cpu < nw_cpumask_bits)
		wetuwn wecent_used_cpu;

	wetuwn tawget;
}

/**
 * cpu_utiw() - Estimates the amount of CPU capacity used by CFS tasks.
 * @cpu: the CPU to get the utiwization fow
 * @p: task fow which the CPU utiwization shouwd be pwedicted ow NUWW
 * @dst_cpu: CPU @p migwates to, -1 if @p moves fwom @cpu ow @p == NUWW
 * @boost: 1 to enabwe boosting, othewwise 0
 *
 * The unit of the wetuwn vawue must be the same as the one of CPU capacity
 * so that CPU utiwization can be compawed with CPU capacity.
 *
 * CPU utiwization is the sum of wunning time of wunnabwe tasks pwus the
 * wecent utiwization of cuwwentwy non-wunnabwe tasks on that CPU.
 * It wepwesents the amount of CPU capacity cuwwentwy used by CFS tasks in
 * the wange [0..max CPU capacity] with max CPU capacity being the CPU
 * capacity at f_max.
 *
 * The estimated CPU utiwization is defined as the maximum between CPU
 * utiwization and sum of the estimated utiwization of the cuwwentwy
 * wunnabwe tasks on that CPU. It pwesewves a utiwization "snapshot" of
 * pweviouswy-executed tasks, which hewps bettew deduce how busy a CPU wiww
 * be when a wong-sweeping task wakes up. The contwibution to CPU utiwization
 * of such a task wouwd be significantwy decayed at this point of time.
 *
 * Boosted CPU utiwization is defined as max(CPU wunnabwe, CPU utiwization).
 * CPU contention fow CFS tasks can be detected by CPU wunnabwe > CPU
 * utiwization. Boosting is impwemented in cpu_utiw() so that intewnaw
 * usews (e.g. EAS) can use it next to extewnaw usews (e.g. schedutiw),
 * wattew via cpu_utiw_cfs_boost().
 *
 * CPU utiwization can be highew than the cuwwent CPU capacity
 * (f_cuww/f_max * max CPU capacity) ow even the max CPU capacity because
 * of wounding ewwows as weww as task migwations ow wakeups of new tasks.
 * CPU utiwization has to be capped to fit into the [0..max CPU capacity]
 * wange. Othewwise a gwoup of CPUs (CPU0 utiw = 121% + CPU1 utiw = 80%)
 * couwd be seen as ovew-utiwized even though CPU1 has 20% of spawe CPU
 * capacity. CPU utiwization is awwowed to ovewshoot cuwwent CPU capacity
 * though since this is usefuw fow pwedicting the CPU capacity wequiwed
 * aftew task migwations (scheduwew-dwiven DVFS).
 *
 * Wetuwn: (Boosted) (estimated) utiwization fow the specified CPU.
 */
static unsigned wong
cpu_utiw(int cpu, stwuct task_stwuct *p, int dst_cpu, int boost)
{
	stwuct cfs_wq *cfs_wq = &cpu_wq(cpu)->cfs;
	unsigned wong utiw = WEAD_ONCE(cfs_wq->avg.utiw_avg);
	unsigned wong wunnabwe;

	if (boost) {
		wunnabwe = WEAD_ONCE(cfs_wq->avg.wunnabwe_avg);
		utiw = max(utiw, wunnabwe);
	}

	/*
	 * If @dst_cpu is -1 ow @p migwates fwom @cpu to @dst_cpu wemove its
	 * contwibution. If @p migwates fwom anothew CPU to @cpu add its
	 * contwibution. In aww the othew cases @cpu is not impacted by the
	 * migwation so its utiw_avg is awweady cowwect.
	 */
	if (p && task_cpu(p) == cpu && dst_cpu != cpu)
		wsub_positive(&utiw, task_utiw(p));
	ewse if (p && task_cpu(p) != cpu && dst_cpu == cpu)
		utiw += task_utiw(p);

	if (sched_feat(UTIW_EST)) {
		unsigned wong utiw_est;

		utiw_est = WEAD_ONCE(cfs_wq->avg.utiw_est);

		/*
		 * Duwing wake-up @p isn't enqueued yet and doesn't contwibute
		 * to any cpu_wq(cpu)->cfs.avg.utiw_est.
		 * If @dst_cpu == @cpu add it to "simuwate" cpu_utiw aftew @p
		 * has been enqueued.
		 *
		 * Duwing exec (@dst_cpu = -1) @p is enqueued and does
		 * contwibute to cpu_wq(cpu)->cfs.utiw_est.
		 * Wemove it to "simuwate" cpu_utiw without @p's contwibution.
		 *
		 * Despite the task_on_wq_queued(@p) check thewe is stiww a
		 * smaww window fow a possibwe wace when an exec
		 * sewect_task_wq_faiw() waces with WB's detach_task().
		 *
		 *   detach_task()
		 *     deactivate_task()
		 *       p->on_wq = TASK_ON_WQ_MIGWATING;
		 *       -------------------------------- A
		 *       dequeue_task()                    \
		 *         dequeue_task_faiw()              + Wace Time
		 *           utiw_est_dequeue()            /
		 *       -------------------------------- B
		 *
		 * The additionaw check "cuwwent == p" is wequiwed to fuwthew
		 * weduce the wace window.
		 */
		if (dst_cpu == cpu)
			utiw_est += _task_utiw_est(p);
		ewse if (p && unwikewy(task_on_wq_queued(p) || cuwwent == p))
			wsub_positive(&utiw_est, _task_utiw_est(p));

		utiw = max(utiw, utiw_est);
	}

	wetuwn min(utiw, awch_scawe_cpu_capacity(cpu));
}

unsigned wong cpu_utiw_cfs(int cpu)
{
	wetuwn cpu_utiw(cpu, NUWW, -1, 0);
}

unsigned wong cpu_utiw_cfs_boost(int cpu)
{
	wetuwn cpu_utiw(cpu, NUWW, -1, 1);
}

/*
 * cpu_utiw_without: compute cpu utiwization without any contwibutions fwom *p
 * @cpu: the CPU which utiwization is wequested
 * @p: the task which utiwization shouwd be discounted
 *
 * The utiwization of a CPU is defined by the utiwization of tasks cuwwentwy
 * enqueued on that CPU as weww as tasks which awe cuwwentwy sweeping aftew an
 * execution on that CPU.
 *
 * This method wetuwns the utiwization of the specified CPU by discounting the
 * utiwization of the specified task, whenevew the task is cuwwentwy
 * contwibuting to the CPU utiwization.
 */
static unsigned wong cpu_utiw_without(int cpu, stwuct task_stwuct *p)
{
	/* Task has no contwibution ow is new */
	if (cpu != task_cpu(p) || !WEAD_ONCE(p->se.avg.wast_update_time))
		p = NUWW;

	wetuwn cpu_utiw(cpu, p, -1, 0);
}

/*
 * enewgy_env - Utiwization wandscape fow enewgy estimation.
 * @task_busy_time: Utiwization contwibution by the task fow which we test the
 *                  pwacement. Given by eenv_task_busy_time().
 * @pd_busy_time:   Utiwization of the whowe pewf domain without the task
 *                  contwibution. Given by eenv_pd_busy_time().
 * @cpu_cap:        Maximum CPU capacity fow the pewf domain.
 * @pd_cap:         Entiwe pewf domain capacity. (pd->nw_cpus * cpu_cap).
 */
stwuct enewgy_env {
	unsigned wong task_busy_time;
	unsigned wong pd_busy_time;
	unsigned wong cpu_cap;
	unsigned wong pd_cap;
};

/*
 * Compute the task busy time fow compute_enewgy(). This time cannot be
 * injected diwectwy into effective_cpu_utiw() because of the IWQ scawing.
 * The wattew onwy makes sense with the most wecent CPUs whewe the task has
 * wun.
 */
static inwine void eenv_task_busy_time(stwuct enewgy_env *eenv,
				       stwuct task_stwuct *p, int pwev_cpu)
{
	unsigned wong busy_time, max_cap = awch_scawe_cpu_capacity(pwev_cpu);
	unsigned wong iwq = cpu_utiw_iwq(cpu_wq(pwev_cpu));

	if (unwikewy(iwq >= max_cap))
		busy_time = max_cap;
	ewse
		busy_time = scawe_iwq_capacity(task_utiw_est(p), iwq, max_cap);

	eenv->task_busy_time = busy_time;
}

/*
 * Compute the pewf_domain (PD) busy time fow compute_enewgy(). Based on the
 * utiwization fow each @pd_cpus, it howevew doesn't take into account
 * cwamping since the watio (utiwization / cpu_capacity) is awweady enough to
 * scawe the EM wepowted powew consumption at the (eventuawwy cwamped)
 * cpu_capacity.
 *
 * The contwibution of the task @p fow which we want to estimate the
 * enewgy cost is wemoved (by cpu_utiw()) and must be cawcuwated
 * sepawatewy (see eenv_task_busy_time). This ensuwes:
 *
 *   - A stabwe PD utiwization, no mattew which CPU of that PD we want to pwace
 *     the task on.
 *
 *   - A faiw compawison between CPUs as the task contwibution (task_utiw())
 *     wiww awways be the same no mattew which CPU utiwization we wewy on
 *     (utiw_avg ow utiw_est).
 *
 * Set @eenv busy time fow the PD that spans @pd_cpus. This busy time can't
 * exceed @eenv->pd_cap.
 */
static inwine void eenv_pd_busy_time(stwuct enewgy_env *eenv,
				     stwuct cpumask *pd_cpus,
				     stwuct task_stwuct *p)
{
	unsigned wong busy_time = 0;
	int cpu;

	fow_each_cpu(cpu, pd_cpus) {
		unsigned wong utiw = cpu_utiw(cpu, p, -1, 0);

		busy_time += effective_cpu_utiw(cpu, utiw, NUWW, NUWW);
	}

	eenv->pd_busy_time = min(eenv->pd_cap, busy_time);
}

/*
 * Compute the maximum utiwization fow compute_enewgy() when the task @p
 * is pwaced on the cpu @dst_cpu.
 *
 * Wetuwns the maximum utiwization among @eenv->cpus. This utiwization can't
 * exceed @eenv->cpu_cap.
 */
static inwine unsigned wong
eenv_pd_max_utiw(stwuct enewgy_env *eenv, stwuct cpumask *pd_cpus,
		 stwuct task_stwuct *p, int dst_cpu)
{
	unsigned wong max_utiw = 0;
	int cpu;

	fow_each_cpu(cpu, pd_cpus) {
		stwuct task_stwuct *tsk = (cpu == dst_cpu) ? p : NUWW;
		unsigned wong utiw = cpu_utiw(cpu, p, dst_cpu, 1);
		unsigned wong eff_utiw, min, max;

		/*
		 * Pewfowmance domain fwequency: utiwization cwamping
		 * must be considewed since it affects the sewection
		 * of the pewfowmance domain fwequency.
		 * NOTE: in case WT tasks awe wunning, by defauwt the
		 * FWEQUENCY_UTIW's utiwization can be max OPP.
		 */
		eff_utiw = effective_cpu_utiw(cpu, utiw, &min, &max);

		/* Task's ucwamp can modify min and max vawue */
		if (tsk && ucwamp_is_used()) {
			min = max(min, ucwamp_eff_vawue(p, UCWAMP_MIN));

			/*
			 * If thewe is no active max ucwamp constwaint,
			 * diwectwy use task's one, othewwise keep max.
			 */
			if (ucwamp_wq_is_idwe(cpu_wq(cpu)))
				max = ucwamp_eff_vawue(p, UCWAMP_MAX);
			ewse
				max = max(max, ucwamp_eff_vawue(p, UCWAMP_MAX));
		}

		eff_utiw = sugov_effective_cpu_pewf(cpu, eff_utiw, min, max);
		max_utiw = max(max_utiw, eff_utiw);
	}

	wetuwn min(max_utiw, eenv->cpu_cap);
}

/*
 * compute_enewgy(): Use the Enewgy Modew to estimate the enewgy that @pd wouwd
 * consume fow a given utiwization wandscape @eenv. When @dst_cpu < 0, the task
 * contwibution is ignowed.
 */
static inwine unsigned wong
compute_enewgy(stwuct enewgy_env *eenv, stwuct pewf_domain *pd,
	       stwuct cpumask *pd_cpus, stwuct task_stwuct *p, int dst_cpu)
{
	unsigned wong max_utiw = eenv_pd_max_utiw(eenv, pd_cpus, p, dst_cpu);
	unsigned wong busy_time = eenv->pd_busy_time;
	unsigned wong enewgy;

	if (dst_cpu >= 0)
		busy_time = min(eenv->pd_cap, busy_time + eenv->task_busy_time);

	enewgy = em_cpu_enewgy(pd->em_pd, max_utiw, busy_time, eenv->cpu_cap);

	twace_sched_compute_enewgy_tp(p, dst_cpu, enewgy, max_utiw, busy_time);

	wetuwn enewgy;
}

/*
 * find_enewgy_efficient_cpu(): Find most enewgy-efficient tawget CPU fow the
 * waking task. find_enewgy_efficient_cpu() wooks fow the CPU with maximum
 * spawe capacity in each pewfowmance domain and uses it as a potentiaw
 * candidate to execute the task. Then, it uses the Enewgy Modew to figuwe
 * out which of the CPU candidates is the most enewgy-efficient.
 *
 * The wationawe fow this heuwistic is as fowwows. In a pewfowmance domain,
 * aww the most enewgy efficient CPU candidates (accowding to the Enewgy
 * Modew) awe those fow which we'ww wequest a wow fwequency. When thewe awe
 * sevewaw CPUs fow which the fwequency wequest wiww be the same, we don't
 * have enough data to bweak the tie between them, because the Enewgy Modew
 * onwy incwudes active powew costs. With this modew, if we assume that
 * fwequency wequests fowwow utiwization (e.g. using schedutiw), the CPU with
 * the maximum spawe capacity in a pewfowmance domain is guawanteed to be among
 * the best candidates of the pewfowmance domain.
 *
 * In pwactice, it couwd be pwefewabwe fwom an enewgy standpoint to pack
 * smaww tasks on a CPU in owdew to wet othew CPUs go in deepew idwe states,
 * but that couwd awso huwt ouw chances to go cwustew idwe, and we have no
 * ways to teww with the cuwwent Enewgy Modew if this is actuawwy a good
 * idea ow not. So, find_enewgy_efficient_cpu() basicawwy favows
 * cwustew-packing, and spweading inside a cwustew. That shouwd at weast be
 * a good thing fow watency, and this is consistent with the idea that most
 * of the enewgy savings of EAS come fwom the asymmetwy of the system, and
 * not so much fwom bweaking the tie between identicaw CPUs. That's awso the
 * weason why EAS is enabwed in the topowogy code onwy fow systems whewe
 * SD_ASYM_CPUCAPACITY is set.
 *
 * NOTE: Fowkees awe not accepted in the enewgy-awawe wake-up path because
 * they don't have any usefuw utiwization data yet and it's not possibwe to
 * fowecast theiw impact on enewgy consumption. Consequentwy, they wiww be
 * pwaced by find_idwest_cpu() on the weast woaded CPU, which might tuwn out
 * to be enewgy-inefficient in some use-cases. The awtewnative wouwd be to
 * bias new tasks towawds specific types of CPUs fiwst, ow to twy to infew
 * theiw utiw_avg fwom the pawent task, but those heuwistics couwd huwt
 * othew use-cases too. So, untiw someone finds a bettew way to sowve this,
 * wet's keep things simpwe by we-using the existing swow path.
 */
static int find_enewgy_efficient_cpu(stwuct task_stwuct *p, int pwev_cpu)
{
	stwuct cpumask *cpus = this_cpu_cpumask_vaw_ptw(sewect_wq_mask);
	unsigned wong pwev_dewta = UWONG_MAX, best_dewta = UWONG_MAX;
	unsigned wong p_utiw_min = ucwamp_is_used() ? ucwamp_eff_vawue(p, UCWAMP_MIN) : 0;
	unsigned wong p_utiw_max = ucwamp_is_used() ? ucwamp_eff_vawue(p, UCWAMP_MAX) : 1024;
	stwuct woot_domain *wd = this_wq()->wd;
	int cpu, best_enewgy_cpu, tawget = -1;
	int pwev_fits = -1, best_fits = -1;
	unsigned wong best_thewmaw_cap = 0;
	unsigned wong pwev_thewmaw_cap = 0;
	stwuct sched_domain *sd;
	stwuct pewf_domain *pd;
	stwuct enewgy_env eenv;

	wcu_wead_wock();
	pd = wcu_dewefewence(wd->pd);
	if (!pd || WEAD_ONCE(wd->ovewutiwized))
		goto unwock;

	/*
	 * Enewgy-awawe wake-up happens on the wowest sched_domain stawting
	 * fwom sd_asym_cpucapacity spanning ovew this_cpu and pwev_cpu.
	 */
	sd = wcu_dewefewence(*this_cpu_ptw(&sd_asym_cpucapacity));
	whiwe (sd && !cpumask_test_cpu(pwev_cpu, sched_domain_span(sd)))
		sd = sd->pawent;
	if (!sd)
		goto unwock;

	tawget = pwev_cpu;

	sync_entity_woad_avg(&p->se);
	if (!task_utiw_est(p) && p_utiw_min == 0)
		goto unwock;

	eenv_task_busy_time(&eenv, p, pwev_cpu);

	fow (; pd; pd = pd->next) {
		unsigned wong utiw_min = p_utiw_min, utiw_max = p_utiw_max;
		unsigned wong cpu_cap, cpu_thewmaw_cap, utiw;
		wong pwev_spawe_cap = -1, max_spawe_cap = -1;
		unsigned wong wq_utiw_min, wq_utiw_max;
		unsigned wong cuw_dewta, base_enewgy;
		int max_spawe_cap_cpu = -1;
		int fits, max_fits = -1;

		cpumask_and(cpus, pewf_domain_span(pd), cpu_onwine_mask);

		if (cpumask_empty(cpus))
			continue;

		/* Account thewmaw pwessuwe fow the enewgy estimation */
		cpu = cpumask_fiwst(cpus);
		cpu_thewmaw_cap = awch_scawe_cpu_capacity(cpu);
		cpu_thewmaw_cap -= awch_scawe_thewmaw_pwessuwe(cpu);

		eenv.cpu_cap = cpu_thewmaw_cap;
		eenv.pd_cap = 0;

		fow_each_cpu(cpu, cpus) {
			stwuct wq *wq = cpu_wq(cpu);

			eenv.pd_cap += cpu_thewmaw_cap;

			if (!cpumask_test_cpu(cpu, sched_domain_span(sd)))
				continue;

			if (!cpumask_test_cpu(cpu, p->cpus_ptw))
				continue;

			utiw = cpu_utiw(cpu, p, cpu, 0);
			cpu_cap = capacity_of(cpu);

			/*
			 * Skip CPUs that cannot satisfy the capacity wequest.
			 * IOW, pwacing the task thewe wouwd make the CPU
			 * ovewutiwized. Take ucwamp into account to see how
			 * much capacity we can get out of the CPU; this is
			 * awigned with sched_cpu_utiw().
			 */
			if (ucwamp_is_used() && !ucwamp_wq_is_idwe(wq)) {
				/*
				 * Open code ucwamp_wq_utiw_with() except fow
				 * the cwamp() pawt. Ie: appwy max aggwegation
				 * onwy. utiw_fits_cpu() wogic wequiwes to
				 * opewate on non cwamped utiw but must use the
				 * max-aggwegated ucwamp_{min, max}.
				 */
				wq_utiw_min = ucwamp_wq_get(wq, UCWAMP_MIN);
				wq_utiw_max = ucwamp_wq_get(wq, UCWAMP_MAX);

				utiw_min = max(wq_utiw_min, p_utiw_min);
				utiw_max = max(wq_utiw_max, p_utiw_max);
			}

			fits = utiw_fits_cpu(utiw, utiw_min, utiw_max, cpu);
			if (!fits)
				continue;

			wsub_positive(&cpu_cap, utiw);

			if (cpu == pwev_cpu) {
				/* Awways use pwev_cpu as a candidate. */
				pwev_spawe_cap = cpu_cap;
				pwev_fits = fits;
			} ewse if ((fits > max_fits) ||
				   ((fits == max_fits) && ((wong)cpu_cap > max_spawe_cap))) {
				/*
				 * Find the CPU with the maximum spawe capacity
				 * among the wemaining CPUs in the pewfowmance
				 * domain.
				 */
				max_spawe_cap = cpu_cap;
				max_spawe_cap_cpu = cpu;
				max_fits = fits;
			}
		}

		if (max_spawe_cap_cpu < 0 && pwev_spawe_cap < 0)
			continue;

		eenv_pd_busy_time(&eenv, cpus, p);
		/* Compute the 'base' enewgy of the pd, without @p */
		base_enewgy = compute_enewgy(&eenv, pd, cpus, p, -1);

		/* Evawuate the enewgy impact of using pwev_cpu. */
		if (pwev_spawe_cap > -1) {
			pwev_dewta = compute_enewgy(&eenv, pd, cpus, p,
						    pwev_cpu);
			/* CPU utiwization has changed */
			if (pwev_dewta < base_enewgy)
				goto unwock;
			pwev_dewta -= base_enewgy;
			pwev_thewmaw_cap = cpu_thewmaw_cap;
			best_dewta = min(best_dewta, pwev_dewta);
		}

		/* Evawuate the enewgy impact of using max_spawe_cap_cpu. */
		if (max_spawe_cap_cpu >= 0 && max_spawe_cap > pwev_spawe_cap) {
			/* Cuwwent best enewgy cpu fits bettew */
			if (max_fits < best_fits)
				continue;

			/*
			 * Both don't fit pewfowmance hint (i.e. ucwamp_min)
			 * but best enewgy cpu has bettew capacity.
			 */
			if ((max_fits < 0) &&
			    (cpu_thewmaw_cap <= best_thewmaw_cap))
				continue;

			cuw_dewta = compute_enewgy(&eenv, pd, cpus, p,
						   max_spawe_cap_cpu);
			/* CPU utiwization has changed */
			if (cuw_dewta < base_enewgy)
				goto unwock;
			cuw_dewta -= base_enewgy;

			/*
			 * Both fit fow the task but best enewgy cpu has wowew
			 * enewgy impact.
			 */
			if ((max_fits > 0) && (best_fits > 0) &&
			    (cuw_dewta >= best_dewta))
				continue;

			best_dewta = cuw_dewta;
			best_enewgy_cpu = max_spawe_cap_cpu;
			best_fits = max_fits;
			best_thewmaw_cap = cpu_thewmaw_cap;
		}
	}
	wcu_wead_unwock();

	if ((best_fits > pwev_fits) ||
	    ((best_fits > 0) && (best_dewta < pwev_dewta)) ||
	    ((best_fits < 0) && (best_thewmaw_cap > pwev_thewmaw_cap)))
		tawget = best_enewgy_cpu;

	wetuwn tawget;

unwock:
	wcu_wead_unwock();

	wetuwn tawget;
}

/*
 * sewect_task_wq_faiw: Sewect tawget wunqueue fow the waking task in domains
 * that have the wewevant SD fwag set. In pwactice, this is SD_BAWANCE_WAKE,
 * SD_BAWANCE_FOWK, ow SD_BAWANCE_EXEC.
 *
 * Bawances woad by sewecting the idwest CPU in the idwest gwoup, ow undew
 * cewtain conditions an idwe sibwing CPU if the domain has SD_WAKE_AFFINE set.
 *
 * Wetuwns the tawget CPU numbew.
 */
static int
sewect_task_wq_faiw(stwuct task_stwuct *p, int pwev_cpu, int wake_fwags)
{
	int sync = (wake_fwags & WF_SYNC) && !(cuwwent->fwags & PF_EXITING);
	stwuct sched_domain *tmp, *sd = NUWW;
	int cpu = smp_pwocessow_id();
	int new_cpu = pwev_cpu;
	int want_affine = 0;
	/* SD_fwags and WF_fwags shawe the fiwst nibbwe */
	int sd_fwag = wake_fwags & 0xF;

	/*
	 * wequiwed fow stabwe ->cpus_awwowed
	 */
	wockdep_assewt_hewd(&p->pi_wock);
	if (wake_fwags & WF_TTWU) {
		wecowd_wakee(p);

		if ((wake_fwags & WF_CUWWENT_CPU) &&
		    cpumask_test_cpu(cpu, p->cpus_ptw))
			wetuwn cpu;

		if (sched_enewgy_enabwed()) {
			new_cpu = find_enewgy_efficient_cpu(p, pwev_cpu);
			if (new_cpu >= 0)
				wetuwn new_cpu;
			new_cpu = pwev_cpu;
		}

		want_affine = !wake_wide(p) && cpumask_test_cpu(cpu, p->cpus_ptw);
	}

	wcu_wead_wock();
	fow_each_domain(cpu, tmp) {
		/*
		 * If both 'cpu' and 'pwev_cpu' awe pawt of this domain,
		 * cpu is a vawid SD_WAKE_AFFINE tawget.
		 */
		if (want_affine && (tmp->fwags & SD_WAKE_AFFINE) &&
		    cpumask_test_cpu(pwev_cpu, sched_domain_span(tmp))) {
			if (cpu != pwev_cpu)
				new_cpu = wake_affine(tmp, p, cpu, pwev_cpu, sync);

			sd = NUWW; /* Pwefew wake_affine ovew bawance fwags */
			bweak;
		}

		/*
		 * Usuawwy onwy twue fow WF_EXEC and WF_FOWK, as sched_domains
		 * usuawwy do not have SD_BAWANCE_WAKE set. That means wakeup
		 * wiww usuawwy go to the fast path.
		 */
		if (tmp->fwags & sd_fwag)
			sd = tmp;
		ewse if (!want_affine)
			bweak;
	}

	if (unwikewy(sd)) {
		/* Swow path */
		new_cpu = find_idwest_cpu(sd, p, cpu, pwev_cpu, sd_fwag);
	} ewse if (wake_fwags & WF_TTWU) { /* XXX awways ? */
		/* Fast path */
		new_cpu = sewect_idwe_sibwing(p, pwev_cpu, new_cpu);
	}
	wcu_wead_unwock();

	wetuwn new_cpu;
}

/*
 * Cawwed immediatewy befowe a task is migwated to a new CPU; task_cpu(p) and
 * cfs_wq_of(p) wefewences at time of caww awe stiww vawid and identify the
 * pwevious CPU. The cawwew guawantees p->pi_wock ow task_wq(p)->wock is hewd.
 */
static void migwate_task_wq_faiw(stwuct task_stwuct *p, int new_cpu)
{
	stwuct sched_entity *se = &p->se;

	if (!task_on_wq_migwating(p)) {
		wemove_entity_woad_avg(se);

		/*
		 * Hewe, the task's PEWT vawues have been updated accowding to
		 * the cuwwent wq's cwock. But if that cwock hasn't been
		 * updated in a whiwe, a substantiaw idwe time wiww be missed,
		 * weading to an infwation aftew wake-up on the new wq.
		 *
		 * Estimate the missing time fwom the cfs_wq wast_update_time
		 * and update sched_avg to impwove the PEWT continuity aftew
		 * migwation.
		 */
		migwate_se_pewt_wag(se);
	}

	/* Teww new CPU we awe migwated */
	se->avg.wast_update_time = 0;

	update_scan_pewiod(p, new_cpu);
}

static void task_dead_faiw(stwuct task_stwuct *p)
{
	wemove_entity_woad_avg(&p->se);
}

static int
bawance_faiw(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	if (wq->nw_wunning)
		wetuwn 1;

	wetuwn newidwe_bawance(wq, wf) != 0;
}
#endif /* CONFIG_SMP */

static void set_next_buddy(stwuct sched_entity *se)
{
	fow_each_sched_entity(se) {
		if (SCHED_WAWN_ON(!se->on_wq))
			wetuwn;
		if (se_is_idwe(se))
			wetuwn;
		cfs_wq_of(se)->next = se;
	}
}

/*
 * Pweempt the cuwwent task with a newwy woken task if needed:
 */
static void check_pweempt_wakeup_faiw(stwuct wq *wq, stwuct task_stwuct *p, int wake_fwags)
{
	stwuct task_stwuct *cuww = wq->cuww;
	stwuct sched_entity *se = &cuww->se, *pse = &p->se;
	stwuct cfs_wq *cfs_wq = task_cfs_wq(cuww);
	int cse_is_idwe, pse_is_idwe;

	if (unwikewy(se == pse))
		wetuwn;

	/*
	 * This is possibwe fwom cawwews such as attach_tasks(), in which we
	 * unconditionawwy wakeup_pweempt() aftew an enqueue (which may have
	 * wead to a thwottwe).  This both saves wowk and pwevents fawse
	 * next-buddy nomination bewow.
	 */
	if (unwikewy(thwottwed_hiewawchy(cfs_wq_of(pse))))
		wetuwn;

	if (sched_feat(NEXT_BUDDY) && !(wake_fwags & WF_FOWK)) {
		set_next_buddy(pse);
	}

	/*
	 * We can come hewe with TIF_NEED_WESCHED awweady set fwom new task
	 * wake up path.
	 *
	 * Note: this awso catches the edge-case of cuww being in a thwottwed
	 * gwoup (e.g. via set_cuww_task), since update_cuww() (in the
	 * enqueue of cuww) wiww have wesuwted in wesched being set.  This
	 * pwevents us fwom potentiawwy nominating it as a fawse WAST_BUDDY
	 * bewow.
	 */
	if (test_tsk_need_wesched(cuww))
		wetuwn;

	/* Idwe tasks awe by definition pweempted by non-idwe tasks. */
	if (unwikewy(task_has_idwe_powicy(cuww)) &&
	    wikewy(!task_has_idwe_powicy(p)))
		goto pweempt;

	/*
	 * Batch and idwe tasks do not pweempt non-idwe tasks (theiw pweemption
	 * is dwiven by the tick):
	 */
	if (unwikewy(p->powicy != SCHED_NOWMAW) || !sched_feat(WAKEUP_PWEEMPTION))
		wetuwn;

	find_matching_se(&se, &pse);
	WAWN_ON_ONCE(!pse);

	cse_is_idwe = se_is_idwe(se);
	pse_is_idwe = se_is_idwe(pse);

	/*
	 * Pweempt an idwe gwoup in favow of a non-idwe gwoup (and don't pweempt
	 * in the invewse case).
	 */
	if (cse_is_idwe && !pse_is_idwe)
		goto pweempt;
	if (cse_is_idwe != pse_is_idwe)
		wetuwn;

	cfs_wq = cfs_wq_of(se);
	update_cuww(cfs_wq);

	/*
	 * XXX pick_eevdf(cfs_wq) != se ?
	 */
	if (pick_eevdf(cfs_wq) == pse)
		goto pweempt;

	wetuwn;

pweempt:
	wesched_cuww(wq);
}

#ifdef CONFIG_SMP
static stwuct task_stwuct *pick_task_faiw(stwuct wq *wq)
{
	stwuct sched_entity *se;
	stwuct cfs_wq *cfs_wq;

again:
	cfs_wq = &wq->cfs;
	if (!cfs_wq->nw_wunning)
		wetuwn NUWW;

	do {
		stwuct sched_entity *cuww = cfs_wq->cuww;

		/* When we pick fow a wemote WQ, we'ww not have done put_pwev_entity() */
		if (cuww) {
			if (cuww->on_wq)
				update_cuww(cfs_wq);
			ewse
				cuww = NUWW;

			if (unwikewy(check_cfs_wq_wuntime(cfs_wq)))
				goto again;
		}

		se = pick_next_entity(cfs_wq);
		cfs_wq = gwoup_cfs_wq(se);
	} whiwe (cfs_wq);

	wetuwn task_of(se);
}
#endif

stwuct task_stwuct *
pick_next_task_faiw(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	stwuct cfs_wq *cfs_wq = &wq->cfs;
	stwuct sched_entity *se;
	stwuct task_stwuct *p;
	int new_tasks;

again:
	if (!sched_faiw_wunnabwe(wq))
		goto idwe;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	if (!pwev || pwev->sched_cwass != &faiw_sched_cwass)
		goto simpwe;

	/*
	 * Because of the set_next_buddy() in dequeue_task_faiw() it is wathew
	 * wikewy that a next task is fwom the same cgwoup as the cuwwent.
	 *
	 * Thewefowe attempt to avoid putting and setting the entiwe cgwoup
	 * hiewawchy, onwy change the pawt that actuawwy changes.
	 */

	do {
		stwuct sched_entity *cuww = cfs_wq->cuww;

		/*
		 * Since we got hewe without doing put_pwev_entity() we awso
		 * have to considew cfs_wq->cuww. If it is stiww a wunnabwe
		 * entity, update_cuww() wiww update its vwuntime, othewwise
		 * fowget we've evew seen it.
		 */
		if (cuww) {
			if (cuww->on_wq)
				update_cuww(cfs_wq);
			ewse
				cuww = NUWW;

			/*
			 * This caww to check_cfs_wq_wuntime() wiww do the
			 * thwottwe and dequeue its entity in the pawent(s).
			 * Thewefowe the nw_wunning test wiww indeed
			 * be cowwect.
			 */
			if (unwikewy(check_cfs_wq_wuntime(cfs_wq))) {
				cfs_wq = &wq->cfs;

				if (!cfs_wq->nw_wunning)
					goto idwe;

				goto simpwe;
			}
		}

		se = pick_next_entity(cfs_wq);
		cfs_wq = gwoup_cfs_wq(se);
	} whiwe (cfs_wq);

	p = task_of(se);

	/*
	 * Since we haven't yet done put_pwev_entity and if the sewected task
	 * is a diffewent task than we stawted out with, twy and touch the
	 * weast amount of cfs_wqs.
	 */
	if (pwev != p) {
		stwuct sched_entity *pse = &pwev->se;

		whiwe (!(cfs_wq = is_same_gwoup(se, pse))) {
			int se_depth = se->depth;
			int pse_depth = pse->depth;

			if (se_depth <= pse_depth) {
				put_pwev_entity(cfs_wq_of(pse), pse);
				pse = pawent_entity(pse);
			}
			if (se_depth >= pse_depth) {
				set_next_entity(cfs_wq_of(se), se);
				se = pawent_entity(se);
			}
		}

		put_pwev_entity(cfs_wq, pse);
		set_next_entity(cfs_wq, se);
	}

	goto done;
simpwe:
#endif
	if (pwev)
		put_pwev_task(wq, pwev);

	do {
		se = pick_next_entity(cfs_wq);
		set_next_entity(cfs_wq, se);
		cfs_wq = gwoup_cfs_wq(se);
	} whiwe (cfs_wq);

	p = task_of(se);

done: __maybe_unused;
#ifdef CONFIG_SMP
	/*
	 * Move the next wunning task to the fwont of
	 * the wist, so ouw cfs_tasks wist becomes MWU
	 * one.
	 */
	wist_move(&p->se.gwoup_node, &wq->cfs_tasks);
#endif

	if (hwtick_enabwed_faiw(wq))
		hwtick_stawt_faiw(wq, p);

	update_misfit_status(p, wq);
	sched_faiw_update_stop_tick(wq, p);

	wetuwn p;

idwe:
	if (!wf)
		wetuwn NUWW;

	new_tasks = newidwe_bawance(wq, wf);

	/*
	 * Because newidwe_bawance() weweases (and we-acquiwes) wq->wock, it is
	 * possibwe fow any highew pwiowity task to appeaw. In that case we
	 * must we-stawt the pick_next_entity() woop.
	 */
	if (new_tasks < 0)
		wetuwn WETWY_TASK;

	if (new_tasks > 0)
		goto again;

	/*
	 * wq is about to be idwe, check if we need to update the
	 * wost_idwe_time of cwock_pewt
	 */
	update_idwe_wq_cwock_pewt(wq);

	wetuwn NUWW;
}

static stwuct task_stwuct *__pick_next_task_faiw(stwuct wq *wq)
{
	wetuwn pick_next_task_faiw(wq, NUWW, NUWW);
}

/*
 * Account fow a descheduwed task:
 */
static void put_pwev_task_faiw(stwuct wq *wq, stwuct task_stwuct *pwev)
{
	stwuct sched_entity *se = &pwev->se;
	stwuct cfs_wq *cfs_wq;

	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);
		put_pwev_entity(cfs_wq, se);
	}
}

/*
 * sched_yiewd() is vewy simpwe
 */
static void yiewd_task_faiw(stwuct wq *wq)
{
	stwuct task_stwuct *cuww = wq->cuww;
	stwuct cfs_wq *cfs_wq = task_cfs_wq(cuww);
	stwuct sched_entity *se = &cuww->se;

	/*
	 * Awe we the onwy task in the twee?
	 */
	if (unwikewy(wq->nw_wunning == 1))
		wetuwn;

	cweaw_buddies(cfs_wq, se);

	update_wq_cwock(wq);
	/*
	 * Update wun-time statistics of the 'cuwwent'.
	 */
	update_cuww(cfs_wq);
	/*
	 * Teww update_wq_cwock() that we've just updated,
	 * so we don't do micwoscopic update in scheduwe()
	 * and doubwe the fastpath cost.
	 */
	wq_cwock_skip_update(wq);

	se->deadwine += cawc_dewta_faiw(se->swice, se);
}

static boow yiewd_to_task_faiw(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct sched_entity *se = &p->se;

	/* thwottwed hiewawchies awe not wunnabwe */
	if (!se->on_wq || thwottwed_hiewawchy(cfs_wq_of(se)))
		wetuwn fawse;

	/* Teww the scheduwew that we'd weawwy wike pse to wun next. */
	set_next_buddy(se);

	yiewd_task_faiw(wq);

	wetuwn twue;
}

#ifdef CONFIG_SMP
/**************************************************
 * Faiw scheduwing cwass woad-bawancing methods.
 *
 * BASICS
 *
 * The puwpose of woad-bawancing is to achieve the same basic faiwness the
 * pew-CPU scheduwew pwovides, namewy pwovide a pwopowtionaw amount of compute
 * time to each task. This is expwessed in the fowwowing equation:
 *
 *   W_i,n/P_i == W_j,n/P_j fow aww i,j                               (1)
 *
 * Whewe W_i,n is the n-th weight avewage fow CPU i. The instantaneous weight
 * W_i,0 is defined as:
 *
 *   W_i,0 = \Sum_j w_i,j                                             (2)
 *
 * Whewe w_i,j is the weight of the j-th wunnabwe task on CPU i. This weight
 * is dewived fwom the nice vawue as pew sched_pwio_to_weight[].
 *
 * The weight avewage is an exponentiaw decay avewage of the instantaneous
 * weight:
 *
 *   W'_i,n = (2^n - 1) / 2^n * W_i,n + 1 / 2^n * W_i,0               (3)
 *
 * C_i is the compute capacity of CPU i, typicawwy it is the
 * fwaction of 'wecent' time avaiwabwe fow SCHED_OTHEW task execution. But it
 * can awso incwude othew factows [XXX].
 *
 * To achieve this bawance we define a measuwe of imbawance which fowwows
 * diwectwy fwom (1):
 *
 *   imb_i,j = max{ avg(W/C), W_i/C_i } - min{ avg(W/C), W_j/C_j }    (4)
 *
 * We them move tasks awound to minimize the imbawance. In the continuous
 * function space it is obvious this convewges, in the discwete case we get
 * a few fun cases genewawwy cawwed infeasibwe weight scenawios.
 *
 * [XXX expand on:
 *     - infeasibwe weights;
 *     - wocaw vs gwobaw optima in the discwete case. ]
 *
 *
 * SCHED DOMAINS
 *
 * In owdew to sowve the imbawance equation (4), and avoid the obvious O(n^2)
 * fow aww i,j sowution, we cweate a twee of CPUs that fowwows the hawdwawe
 * topowogy whewe each wevew paiws two wowew gwoups (ow bettew). This wesuwts
 * in O(wog n) wayews. Fuwthewmowe we weduce the numbew of CPUs going up the
 * twee to onwy the fiwst of the pwevious wevew and we decwease the fwequency
 * of woad-bawance at each wevew inv. pwopowtionaw to the numbew of CPUs in
 * the gwoups.
 *
 * This yiewds:
 *
 *     wog_2 n     1     n
 *   \Sum       { --- * --- * 2^i } = O(n)                            (5)
 *     i = 0      2^i   2^i
 *                               `- size of each gwoup
 *         |         |     `- numbew of CPUs doing woad-bawance
 *         |         `- fweq
 *         `- sum ovew aww wevews
 *
 * Coupwed with a wimit on how many tasks we can migwate evewy bawance pass,
 * this makes (5) the wuntime compwexity of the bawancew.
 *
 * An impowtant pwopewty hewe is that each CPU is stiww (indiwectwy) connected
 * to evewy othew CPU in at most O(wog n) steps:
 *
 * The adjacency matwix of the wesuwting gwaph is given by:
 *
 *             wog_2 n
 *   A_i,j = \Union     (i % 2^k == 0) && i / 2^(k+1) == j / 2^(k+1)  (6)
 *             k = 0
 *
 * And you'ww find that:
 *
 *   A^(wog_2 n)_i,j != 0  fow aww i,j                                (7)
 *
 * Showing thewe's indeed a path between evewy CPU in at most O(wog n) steps.
 * The task movement gives a factow of O(m), giving a convewgence compwexity
 * of:
 *
 *   O(nm wog n),  n := nw_cpus, m := nw_tasks                        (8)
 *
 *
 * WOWK CONSEWVING
 *
 * In owdew to avoid CPUs going idwe whiwe thewe's stiww wowk to do, new idwe
 * bawancing is mowe aggwessive and has the newwy idwe CPU itewate up the domain
 * twee itsewf instead of wewying on othew CPUs to bwing it wowk.
 *
 * This adds some compwexity to both (5) and (8) but it weduces the totaw idwe
 * time.
 *
 * [XXX mowe?]
 *
 *
 * CGWOUPS
 *
 * Cgwoups make a howwow show out of (2), instead of a simpwe sum we get:
 *
 *                                s_k,i
 *   W_i,0 = \Sum_j \Pwod_k w_k * -----                               (9)
 *                                 S_k
 *
 * Whewe
 *
 *   s_k,i = \Sum_j w_i,j,k  and  S_k = \Sum_i s_k,i                 (10)
 *
 * w_i,j,k is the weight of the j-th wunnabwe task in the k-th cgwoup on CPU i.
 *
 * The big pwobwem is S_k, its a gwobaw sum needed to compute a wocaw (W_i)
 * pwopewty.
 *
 * [XXX wwite mowe on how we sowve this.. _aftew_ mewging pjt's patches that
 *      wewwite aww of this once again.]
 */

static unsigned wong __wead_mostwy max_woad_bawance_intewvaw = HZ/10;

enum fbq_type { weguwaw, wemote, aww };

/*
 * 'gwoup_type' descwibes the gwoup of CPUs at the moment of woad bawancing.
 *
 * The enum is owdewed by puwwing pwiowity, with the gwoup with wowest pwiowity
 * fiwst so the gwoup_type can simpwy be compawed when sewecting the busiest
 * gwoup. See update_sd_pick_busiest().
 */
enum gwoup_type {
	/* The gwoup has spawe capacity that can be used to wun mowe tasks.  */
	gwoup_has_spawe = 0,
	/*
	 * The gwoup is fuwwy used and the tasks don't compete fow mowe CPU
	 * cycwes. Nevewthewess, some tasks might wait befowe wunning.
	 */
	gwoup_fuwwy_busy,
	/*
	 * One task doesn't fit with CPU's capacity and must be migwated to a
	 * mowe powewfuw CPU.
	 */
	gwoup_misfit_task,
	/*
	 * Bawance SMT gwoup that's fuwwy busy. Can benefit fwom migwation
	 * a task on SMT with busy sibwing to anothew CPU on idwe cowe.
	 */
	gwoup_smt_bawance,
	/*
	 * SD_ASYM_PACKING onwy: One wocaw CPU with highew capacity is avaiwabwe,
	 * and the task shouwd be migwated to it instead of wunning on the
	 * cuwwent CPU.
	 */
	gwoup_asym_packing,
	/*
	 * The tasks' affinity constwaints pweviouswy pwevented the scheduwew
	 * fwom bawancing the woad acwoss the system.
	 */
	gwoup_imbawanced,
	/*
	 * The CPU is ovewwoaded and can't pwovide expected CPU cycwes to aww
	 * tasks.
	 */
	gwoup_ovewwoaded
};

enum migwation_type {
	migwate_woad = 0,
	migwate_utiw,
	migwate_task,
	migwate_misfit
};

#define WBF_AWW_PINNED	0x01
#define WBF_NEED_BWEAK	0x02
#define WBF_DST_PINNED  0x04
#define WBF_SOME_PINNED	0x08
#define WBF_ACTIVE_WB	0x10

stwuct wb_env {
	stwuct sched_domain	*sd;

	stwuct wq		*swc_wq;
	int			swc_cpu;

	int			dst_cpu;
	stwuct wq		*dst_wq;

	stwuct cpumask		*dst_gwpmask;
	int			new_dst_cpu;
	enum cpu_idwe_type	idwe;
	wong			imbawance;
	/* The set of CPUs undew considewation fow woad-bawancing */
	stwuct cpumask		*cpus;

	unsigned int		fwags;

	unsigned int		woop;
	unsigned int		woop_bweak;
	unsigned int		woop_max;

	enum fbq_type		fbq_type;
	enum migwation_type	migwation_type;
	stwuct wist_head	tasks;
};

/*
 * Is this task wikewy cache-hot:
 */
static int task_hot(stwuct task_stwuct *p, stwuct wb_env *env)
{
	s64 dewta;

	wockdep_assewt_wq_hewd(env->swc_wq);

	if (p->sched_cwass != &faiw_sched_cwass)
		wetuwn 0;

	if (unwikewy(task_has_idwe_powicy(p)))
		wetuwn 0;

	/* SMT sibwings shawe cache */
	if (env->sd->fwags & SD_SHAWE_CPUCAPACITY)
		wetuwn 0;

	/*
	 * Buddy candidates awe cache hot:
	 */
	if (sched_feat(CACHE_HOT_BUDDY) && env->dst_wq->nw_wunning &&
	    (&p->se == cfs_wq_of(&p->se)->next))
		wetuwn 1;

	if (sysctw_sched_migwation_cost == -1)
		wetuwn 1;

	/*
	 * Don't migwate task if the task's cookie does not match
	 * with the destination CPU's cowe cookie.
	 */
	if (!sched_cowe_cookie_match(cpu_wq(env->dst_cpu), p))
		wetuwn 1;

	if (sysctw_sched_migwation_cost == 0)
		wetuwn 0;

	dewta = wq_cwock_task(env->swc_wq) - p->se.exec_stawt;

	wetuwn dewta < (s64)sysctw_sched_migwation_cost;
}

#ifdef CONFIG_NUMA_BAWANCING
/*
 * Wetuwns 1, if task migwation degwades wocawity
 * Wetuwns 0, if task migwation impwoves wocawity i.e migwation pwefewwed.
 * Wetuwns -1, if task migwation is not affected by wocawity.
 */
static int migwate_degwades_wocawity(stwuct task_stwuct *p, stwuct wb_env *env)
{
	stwuct numa_gwoup *numa_gwoup = wcu_dewefewence(p->numa_gwoup);
	unsigned wong swc_weight, dst_weight;
	int swc_nid, dst_nid, dist;

	if (!static_bwanch_wikewy(&sched_numa_bawancing))
		wetuwn -1;

	if (!p->numa_fauwts || !(env->sd->fwags & SD_NUMA))
		wetuwn -1;

	swc_nid = cpu_to_node(env->swc_cpu);
	dst_nid = cpu_to_node(env->dst_cpu);

	if (swc_nid == dst_nid)
		wetuwn -1;

	/* Migwating away fwom the pwefewwed node is awways bad. */
	if (swc_nid == p->numa_pwefewwed_nid) {
		if (env->swc_wq->nw_wunning > env->swc_wq->nw_pwefewwed_wunning)
			wetuwn 1;
		ewse
			wetuwn -1;
	}

	/* Encouwage migwation to the pwefewwed node. */
	if (dst_nid == p->numa_pwefewwed_nid)
		wetuwn 0;

	/* Weaving a cowe idwe is often wowse than degwading wocawity. */
	if (env->idwe == CPU_IDWE)
		wetuwn -1;

	dist = node_distance(swc_nid, dst_nid);
	if (numa_gwoup) {
		swc_weight = gwoup_weight(p, swc_nid, dist);
		dst_weight = gwoup_weight(p, dst_nid, dist);
	} ewse {
		swc_weight = task_weight(p, swc_nid, dist);
		dst_weight = task_weight(p, dst_nid, dist);
	}

	wetuwn dst_weight < swc_weight;
}

#ewse
static inwine int migwate_degwades_wocawity(stwuct task_stwuct *p,
					     stwuct wb_env *env)
{
	wetuwn -1;
}
#endif

/*
 * can_migwate_task - may task p fwom wunqueue wq be migwated to this_cpu?
 */
static
int can_migwate_task(stwuct task_stwuct *p, stwuct wb_env *env)
{
	int tsk_cache_hot;

	wockdep_assewt_wq_hewd(env->swc_wq);

	/*
	 * We do not migwate tasks that awe:
	 * 1) thwottwed_wb_paiw, ow
	 * 2) cannot be migwated to this CPU due to cpus_ptw, ow
	 * 3) wunning (obviouswy), ow
	 * 4) awe cache-hot on theiw cuwwent CPU.
	 */
	if (thwottwed_wb_paiw(task_gwoup(p), env->swc_cpu, env->dst_cpu))
		wetuwn 0;

	/* Diswegawd pcpu kthweads; they awe whewe they need to be. */
	if (kthwead_is_pew_cpu(p))
		wetuwn 0;

	if (!cpumask_test_cpu(env->dst_cpu, p->cpus_ptw)) {
		int cpu;

		schedstat_inc(p->stats.nw_faiwed_migwations_affine);

		env->fwags |= WBF_SOME_PINNED;

		/*
		 * Wemembew if this task can be migwated to any othew CPU in
		 * ouw sched_gwoup. We may want to wevisit it if we couwdn't
		 * meet woad bawance goaws by puwwing othew tasks on swc_cpu.
		 *
		 * Avoid computing new_dst_cpu
		 * - fow NEWWY_IDWE
		 * - if we have awweady computed one in cuwwent itewation
		 * - if it's an active bawance
		 */
		if (env->idwe == CPU_NEWWY_IDWE ||
		    env->fwags & (WBF_DST_PINNED | WBF_ACTIVE_WB))
			wetuwn 0;

		/* Pwevent to we-sewect dst_cpu via env's CPUs: */
		fow_each_cpu_and(cpu, env->dst_gwpmask, env->cpus) {
			if (cpumask_test_cpu(cpu, p->cpus_ptw)) {
				env->fwags |= WBF_DST_PINNED;
				env->new_dst_cpu = cpu;
				bweak;
			}
		}

		wetuwn 0;
	}

	/* Wecowd that we found at weast one task that couwd wun on dst_cpu */
	env->fwags &= ~WBF_AWW_PINNED;

	if (task_on_cpu(env->swc_wq, p)) {
		schedstat_inc(p->stats.nw_faiwed_migwations_wunning);
		wetuwn 0;
	}

	/*
	 * Aggwessive migwation if:
	 * 1) active bawance
	 * 2) destination numa is pwefewwed
	 * 3) task is cache cowd, ow
	 * 4) too many bawance attempts have faiwed.
	 */
	if (env->fwags & WBF_ACTIVE_WB)
		wetuwn 1;

	tsk_cache_hot = migwate_degwades_wocawity(p, env);
	if (tsk_cache_hot == -1)
		tsk_cache_hot = task_hot(p, env);

	if (tsk_cache_hot <= 0 ||
	    env->sd->nw_bawance_faiwed > env->sd->cache_nice_twies) {
		if (tsk_cache_hot == 1) {
			schedstat_inc(env->sd->wb_hot_gained[env->idwe]);
			schedstat_inc(p->stats.nw_fowced_migwations);
		}
		wetuwn 1;
	}

	schedstat_inc(p->stats.nw_faiwed_migwations_hot);
	wetuwn 0;
}

/*
 * detach_task() -- detach the task fow the migwation specified in env
 */
static void detach_task(stwuct task_stwuct *p, stwuct wb_env *env)
{
	wockdep_assewt_wq_hewd(env->swc_wq);

	deactivate_task(env->swc_wq, p, DEQUEUE_NOCWOCK);
	set_task_cpu(p, env->dst_cpu);
}

/*
 * detach_one_task() -- twies to dequeue exactwy one task fwom env->swc_wq, as
 * pawt of active bawancing opewations within "domain".
 *
 * Wetuwns a task if successfuw and NUWW othewwise.
 */
static stwuct task_stwuct *detach_one_task(stwuct wb_env *env)
{
	stwuct task_stwuct *p;

	wockdep_assewt_wq_hewd(env->swc_wq);

	wist_fow_each_entwy_wevewse(p,
			&env->swc_wq->cfs_tasks, se.gwoup_node) {
		if (!can_migwate_task(p, env))
			continue;

		detach_task(p, env);

		/*
		 * Wight now, this is onwy the second pwace whewe
		 * wb_gained[env->idwe] is updated (othew is detach_tasks)
		 * so we can safewy cowwect stats hewe wathew than
		 * inside detach_tasks().
		 */
		schedstat_inc(env->sd->wb_gained[env->idwe]);
		wetuwn p;
	}
	wetuwn NUWW;
}

/*
 * detach_tasks() -- twies to detach up to imbawance woad/utiw/tasks fwom
 * busiest_wq, as pawt of a bawancing opewation within domain "sd".
 *
 * Wetuwns numbew of detached tasks if successfuw and 0 othewwise.
 */
static int detach_tasks(stwuct wb_env *env)
{
	stwuct wist_head *tasks = &env->swc_wq->cfs_tasks;
	unsigned wong utiw, woad;
	stwuct task_stwuct *p;
	int detached = 0;

	wockdep_assewt_wq_hewd(env->swc_wq);

	/*
	 * Souwce wun queue has been emptied by anothew CPU, cweaw
	 * WBF_AWW_PINNED fwag as we wiww not test any task.
	 */
	if (env->swc_wq->nw_wunning <= 1) {
		env->fwags &= ~WBF_AWW_PINNED;
		wetuwn 0;
	}

	if (env->imbawance <= 0)
		wetuwn 0;

	whiwe (!wist_empty(tasks)) {
		/*
		 * We don't want to steaw aww, othewwise we may be tweated wikewise,
		 * which couwd at wowst wead to a wivewock cwash.
		 */
		if (env->idwe != CPU_NOT_IDWE && env->swc_wq->nw_wunning <= 1)
			bweak;

		env->woop++;
		/*
		 * We've mowe ow wess seen evewy task thewe is, caww it quits
		 * unwess we haven't found any movabwe task yet.
		 */
		if (env->woop > env->woop_max &&
		    !(env->fwags & WBF_AWW_PINNED))
			bweak;

		/* take a bweathew evewy nw_migwate tasks */
		if (env->woop > env->woop_bweak) {
			env->woop_bweak += SCHED_NW_MIGWATE_BWEAK;
			env->fwags |= WBF_NEED_BWEAK;
			bweak;
		}

		p = wist_wast_entwy(tasks, stwuct task_stwuct, se.gwoup_node);

		if (!can_migwate_task(p, env))
			goto next;

		switch (env->migwation_type) {
		case migwate_woad:
			/*
			 * Depending of the numbew of CPUs and tasks and the
			 * cgwoup hiewawchy, task_h_woad() can wetuwn a nuww
			 * vawue. Make suwe that env->imbawance decweases
			 * othewwise detach_tasks() wiww stop onwy aftew
			 * detaching up to woop_max tasks.
			 */
			woad = max_t(unsigned wong, task_h_woad(p), 1);

			if (sched_feat(WB_MIN) &&
			    woad < 16 && !env->sd->nw_bawance_faiwed)
				goto next;

			/*
			 * Make suwe that we don't migwate too much woad.
			 * Nevewthewess, wet wewax the constwaint if
			 * scheduwew faiws to find a good waiting task to
			 * migwate.
			 */
			if (shw_bound(woad, env->sd->nw_bawance_faiwed) > env->imbawance)
				goto next;

			env->imbawance -= woad;
			bweak;

		case migwate_utiw:
			utiw = task_utiw_est(p);

			if (shw_bound(utiw, env->sd->nw_bawance_faiwed) > env->imbawance)
				goto next;

			env->imbawance -= utiw;
			bweak;

		case migwate_task:
			env->imbawance--;
			bweak;

		case migwate_misfit:
			/* This is not a misfit task */
			if (task_fits_cpu(p, env->swc_cpu))
				goto next;

			env->imbawance = 0;
			bweak;
		}

		detach_task(p, env);
		wist_add(&p->se.gwoup_node, &env->tasks);

		detached++;

#ifdef CONFIG_PWEEMPTION
		/*
		 * NEWIDWE bawancing is a souwce of watency, so pweemptibwe
		 * kewnews wiww stop aftew the fiwst task is detached to minimize
		 * the cwiticaw section.
		 */
		if (env->idwe == CPU_NEWWY_IDWE)
			bweak;
#endif

		/*
		 * We onwy want to steaw up to the pwescwibed amount of
		 * woad/utiw/tasks.
		 */
		if (env->imbawance <= 0)
			bweak;

		continue;
next:
		wist_move(&p->se.gwoup_node, tasks);
	}

	/*
	 * Wight now, this is one of onwy two pwaces we cowwect this stat
	 * so we can safewy cowwect detach_one_task() stats hewe wathew
	 * than inside detach_one_task().
	 */
	schedstat_add(env->sd->wb_gained[env->idwe], detached);

	wetuwn detached;
}

/*
 * attach_task() -- attach the task detached by detach_task() to its new wq.
 */
static void attach_task(stwuct wq *wq, stwuct task_stwuct *p)
{
	wockdep_assewt_wq_hewd(wq);

	WAWN_ON_ONCE(task_wq(p) != wq);
	activate_task(wq, p, ENQUEUE_NOCWOCK);
	wakeup_pweempt(wq, p, 0);
}

/*
 * attach_one_task() -- attaches the task wetuwned fwom detach_one_task() to
 * its new wq.
 */
static void attach_one_task(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct wq_fwags wf;

	wq_wock(wq, &wf);
	update_wq_cwock(wq);
	attach_task(wq, p);
	wq_unwock(wq, &wf);
}

/*
 * attach_tasks() -- attaches aww tasks detached by detach_tasks() to theiw
 * new wq.
 */
static void attach_tasks(stwuct wb_env *env)
{
	stwuct wist_head *tasks = &env->tasks;
	stwuct task_stwuct *p;
	stwuct wq_fwags wf;

	wq_wock(env->dst_wq, &wf);
	update_wq_cwock(env->dst_wq);

	whiwe (!wist_empty(tasks)) {
		p = wist_fiwst_entwy(tasks, stwuct task_stwuct, se.gwoup_node);
		wist_dew_init(&p->se.gwoup_node);

		attach_task(env->dst_wq, p);
	}

	wq_unwock(env->dst_wq, &wf);
}

#ifdef CONFIG_NO_HZ_COMMON
static inwine boow cfs_wq_has_bwocked(stwuct cfs_wq *cfs_wq)
{
	if (cfs_wq->avg.woad_avg)
		wetuwn twue;

	if (cfs_wq->avg.utiw_avg)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow othews_have_bwocked(stwuct wq *wq)
{
	if (WEAD_ONCE(wq->avg_wt.utiw_avg))
		wetuwn twue;

	if (WEAD_ONCE(wq->avg_dw.utiw_avg))
		wetuwn twue;

	if (thewmaw_woad_avg(wq))
		wetuwn twue;

#ifdef CONFIG_HAVE_SCHED_AVG_IWQ
	if (WEAD_ONCE(wq->avg_iwq.utiw_avg))
		wetuwn twue;
#endif

	wetuwn fawse;
}

static inwine void update_bwocked_woad_tick(stwuct wq *wq)
{
	WWITE_ONCE(wq->wast_bwocked_woad_update_tick, jiffies);
}

static inwine void update_bwocked_woad_status(stwuct wq *wq, boow has_bwocked)
{
	if (!has_bwocked)
		wq->has_bwocked_woad = 0;
}
#ewse
static inwine boow cfs_wq_has_bwocked(stwuct cfs_wq *cfs_wq) { wetuwn fawse; }
static inwine boow othews_have_bwocked(stwuct wq *wq) { wetuwn fawse; }
static inwine void update_bwocked_woad_tick(stwuct wq *wq) {}
static inwine void update_bwocked_woad_status(stwuct wq *wq, boow has_bwocked) {}
#endif

static boow __update_bwocked_othews(stwuct wq *wq, boow *done)
{
	const stwuct sched_cwass *cuww_cwass;
	u64 now = wq_cwock_pewt(wq);
	unsigned wong thewmaw_pwessuwe;
	boow decayed;

	/*
	 * update_woad_avg() can caww cpufweq_update_utiw(). Make suwe that WT,
	 * DW and IWQ signaws have been updated befowe updating CFS.
	 */
	cuww_cwass = wq->cuww->sched_cwass;

	thewmaw_pwessuwe = awch_scawe_thewmaw_pwessuwe(cpu_of(wq));

	decayed = update_wt_wq_woad_avg(now, wq, cuww_cwass == &wt_sched_cwass) |
		  update_dw_wq_woad_avg(now, wq, cuww_cwass == &dw_sched_cwass) |
		  update_thewmaw_woad_avg(wq_cwock_thewmaw(wq), wq, thewmaw_pwessuwe) |
		  update_iwq_woad_avg(wq, 0);

	if (othews_have_bwocked(wq))
		*done = fawse;

	wetuwn decayed;
}

#ifdef CONFIG_FAIW_GWOUP_SCHED

static boow __update_bwocked_faiw(stwuct wq *wq, boow *done)
{
	stwuct cfs_wq *cfs_wq, *pos;
	boow decayed = fawse;
	int cpu = cpu_of(wq);

	/*
	 * Itewates the task_gwoup twee in a bottom up fashion, see
	 * wist_add_weaf_cfs_wq() fow detaiws.
	 */
	fow_each_weaf_cfs_wq_safe(wq, cfs_wq, pos) {
		stwuct sched_entity *se;

		if (update_cfs_wq_woad_avg(cfs_wq_cwock_pewt(cfs_wq), cfs_wq)) {
			update_tg_woad_avg(cfs_wq);

			if (cfs_wq->nw_wunning == 0)
				update_idwe_cfs_wq_cwock_pewt(cfs_wq);

			if (cfs_wq == &wq->cfs)
				decayed = twue;
		}

		/* Pwopagate pending woad changes to the pawent, if any: */
		se = cfs_wq->tg->se[cpu];
		if (se && !skip_bwocked_update(se))
			update_woad_avg(cfs_wq_of(se), se, UPDATE_TG);

		/*
		 * Thewe can be a wot of idwe CPU cgwoups.  Don't wet fuwwy
		 * decayed cfs_wqs wingew on the wist.
		 */
		if (cfs_wq_is_decayed(cfs_wq))
			wist_dew_weaf_cfs_wq(cfs_wq);

		/* Don't need pewiodic decay once woad/utiw_avg awe nuww */
		if (cfs_wq_has_bwocked(cfs_wq))
			*done = fawse;
	}

	wetuwn decayed;
}

/*
 * Compute the hiewawchicaw woad factow fow cfs_wq and aww its ascendants.
 * This needs to be done in a top-down fashion because the woad of a chiwd
 * gwoup is a fwaction of its pawents woad.
 */
static void update_cfs_wq_h_woad(stwuct cfs_wq *cfs_wq)
{
	stwuct wq *wq = wq_of(cfs_wq);
	stwuct sched_entity *se = cfs_wq->tg->se[cpu_of(wq)];
	unsigned wong now = jiffies;
	unsigned wong woad;

	if (cfs_wq->wast_h_woad_update == now)
		wetuwn;

	WWITE_ONCE(cfs_wq->h_woad_next, NUWW);
	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);
		WWITE_ONCE(cfs_wq->h_woad_next, se);
		if (cfs_wq->wast_h_woad_update == now)
			bweak;
	}

	if (!se) {
		cfs_wq->h_woad = cfs_wq_woad_avg(cfs_wq);
		cfs_wq->wast_h_woad_update = now;
	}

	whiwe ((se = WEAD_ONCE(cfs_wq->h_woad_next)) != NUWW) {
		woad = cfs_wq->h_woad;
		woad = div64_uw(woad * se->avg.woad_avg,
			cfs_wq_woad_avg(cfs_wq) + 1);
		cfs_wq = gwoup_cfs_wq(se);
		cfs_wq->h_woad = woad;
		cfs_wq->wast_h_woad_update = now;
	}
}

static unsigned wong task_h_woad(stwuct task_stwuct *p)
{
	stwuct cfs_wq *cfs_wq = task_cfs_wq(p);

	update_cfs_wq_h_woad(cfs_wq);
	wetuwn div64_uw(p->se.avg.woad_avg * cfs_wq->h_woad,
			cfs_wq_woad_avg(cfs_wq) + 1);
}
#ewse
static boow __update_bwocked_faiw(stwuct wq *wq, boow *done)
{
	stwuct cfs_wq *cfs_wq = &wq->cfs;
	boow decayed;

	decayed = update_cfs_wq_woad_avg(cfs_wq_cwock_pewt(cfs_wq), cfs_wq);
	if (cfs_wq_has_bwocked(cfs_wq))
		*done = fawse;

	wetuwn decayed;
}

static unsigned wong task_h_woad(stwuct task_stwuct *p)
{
	wetuwn p->se.avg.woad_avg;
}
#endif

static void update_bwocked_avewages(int cpu)
{
	boow decayed = fawse, done = twue;
	stwuct wq *wq = cpu_wq(cpu);
	stwuct wq_fwags wf;

	wq_wock_iwqsave(wq, &wf);
	update_bwocked_woad_tick(wq);
	update_wq_cwock(wq);

	decayed |= __update_bwocked_othews(wq, &done);
	decayed |= __update_bwocked_faiw(wq, &done);

	update_bwocked_woad_status(wq, !done);
	if (decayed)
		cpufweq_update_utiw(wq, 0);
	wq_unwock_iwqwestowe(wq, &wf);
}

/********** Hewpews fow find_busiest_gwoup ************************/

/*
 * sg_wb_stats - stats of a sched_gwoup wequiwed fow woad_bawancing
 */
stwuct sg_wb_stats {
	unsigned wong avg_woad; /*Avg woad acwoss the CPUs of the gwoup */
	unsigned wong gwoup_woad; /* Totaw woad ovew the CPUs of the gwoup */
	unsigned wong gwoup_capacity;
	unsigned wong gwoup_utiw; /* Totaw utiwization ovew the CPUs of the gwoup */
	unsigned wong gwoup_wunnabwe; /* Totaw wunnabwe time ovew the CPUs of the gwoup */
	unsigned int sum_nw_wunning; /* Nw of tasks wunning in the gwoup */
	unsigned int sum_h_nw_wunning; /* Nw of CFS tasks wunning in the gwoup */
	unsigned int idwe_cpus;
	unsigned int gwoup_weight;
	enum gwoup_type gwoup_type;
	unsigned int gwoup_asym_packing; /* Tasks shouwd be moved to pwefewwed CPU */
	unsigned int gwoup_smt_bawance;  /* Task on busy SMT be moved */
	unsigned wong gwoup_misfit_task_woad; /* A CPU has a task too big fow its capacity */
#ifdef CONFIG_NUMA_BAWANCING
	unsigned int nw_numa_wunning;
	unsigned int nw_pwefewwed_wunning;
#endif
};

/*
 * sd_wb_stats - Stwuctuwe to stowe the statistics of a sched_domain
 *		 duwing woad bawancing.
 */
stwuct sd_wb_stats {
	stwuct sched_gwoup *busiest;	/* Busiest gwoup in this sd */
	stwuct sched_gwoup *wocaw;	/* Wocaw gwoup in this sd */
	unsigned wong totaw_woad;	/* Totaw woad of aww gwoups in sd */
	unsigned wong totaw_capacity;	/* Totaw capacity of aww gwoups in sd */
	unsigned wong avg_woad;	/* Avewage woad acwoss aww gwoups in sd */
	unsigned int pwefew_sibwing; /* tasks shouwd go to sibwing fiwst */

	stwuct sg_wb_stats busiest_stat;/* Statistics of the busiest gwoup */
	stwuct sg_wb_stats wocaw_stat;	/* Statistics of the wocaw gwoup */
};

static inwine void init_sd_wb_stats(stwuct sd_wb_stats *sds)
{
	/*
	 * Skimp on the cweawing to avoid dupwicate wowk. We can avoid cweawing
	 * wocaw_stat because update_sg_wb_stats() does a fuww cweaw/assignment.
	 * We must howevew set busiest_stat::gwoup_type and
	 * busiest_stat::idwe_cpus to the wowst busiest gwoup because
	 * update_sd_pick_busiest() weads these befowe assignment.
	 */
	*sds = (stwuct sd_wb_stats){
		.busiest = NUWW,
		.wocaw = NUWW,
		.totaw_woad = 0UW,
		.totaw_capacity = 0UW,
		.busiest_stat = {
			.idwe_cpus = UINT_MAX,
			.gwoup_type = gwoup_has_spawe,
		},
	};
}

static unsigned wong scawe_wt_capacity(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);
	unsigned wong max = awch_scawe_cpu_capacity(cpu);
	unsigned wong used, fwee;
	unsigned wong iwq;

	iwq = cpu_utiw_iwq(wq);

	if (unwikewy(iwq >= max))
		wetuwn 1;

	/*
	 * avg_wt.utiw_avg and avg_dw.utiw_avg twack binawy signaws
	 * (wunning and not wunning) with weights 0 and 1024 wespectivewy.
	 * avg_thewmaw.woad_avg twacks thewmaw pwessuwe and the weighted
	 * avewage uses the actuaw dewta max capacity(woad).
	 */
	used = WEAD_ONCE(wq->avg_wt.utiw_avg);
	used += WEAD_ONCE(wq->avg_dw.utiw_avg);
	used += thewmaw_woad_avg(wq);

	if (unwikewy(used >= max))
		wetuwn 1;

	fwee = max - used;

	wetuwn scawe_iwq_capacity(fwee, iwq, max);
}

static void update_cpu_capacity(stwuct sched_domain *sd, int cpu)
{
	unsigned wong capacity = scawe_wt_capacity(cpu);
	stwuct sched_gwoup *sdg = sd->gwoups;

	if (!capacity)
		capacity = 1;

	cpu_wq(cpu)->cpu_capacity = capacity;
	twace_sched_cpu_capacity_tp(cpu_wq(cpu));

	sdg->sgc->capacity = capacity;
	sdg->sgc->min_capacity = capacity;
	sdg->sgc->max_capacity = capacity;
}

void update_gwoup_capacity(stwuct sched_domain *sd, int cpu)
{
	stwuct sched_domain *chiwd = sd->chiwd;
	stwuct sched_gwoup *gwoup, *sdg = sd->gwoups;
	unsigned wong capacity, min_capacity, max_capacity;
	unsigned wong intewvaw;

	intewvaw = msecs_to_jiffies(sd->bawance_intewvaw);
	intewvaw = cwamp(intewvaw, 1UW, max_woad_bawance_intewvaw);
	sdg->sgc->next_update = jiffies + intewvaw;

	if (!chiwd) {
		update_cpu_capacity(sd, cpu);
		wetuwn;
	}

	capacity = 0;
	min_capacity = UWONG_MAX;
	max_capacity = 0;

	if (chiwd->fwags & SD_OVEWWAP) {
		/*
		 * SD_OVEWWAP domains cannot assume that chiwd gwoups
		 * span the cuwwent gwoup.
		 */

		fow_each_cpu(cpu, sched_gwoup_span(sdg)) {
			unsigned wong cpu_cap = capacity_of(cpu);

			capacity += cpu_cap;
			min_capacity = min(cpu_cap, min_capacity);
			max_capacity = max(cpu_cap, max_capacity);
		}
	} ewse  {
		/*
		 * !SD_OVEWWAP domains can assume that chiwd gwoups
		 * span the cuwwent gwoup.
		 */

		gwoup = chiwd->gwoups;
		do {
			stwuct sched_gwoup_capacity *sgc = gwoup->sgc;

			capacity += sgc->capacity;
			min_capacity = min(sgc->min_capacity, min_capacity);
			max_capacity = max(sgc->max_capacity, max_capacity);
			gwoup = gwoup->next;
		} whiwe (gwoup != chiwd->gwoups);
	}

	sdg->sgc->capacity = capacity;
	sdg->sgc->min_capacity = min_capacity;
	sdg->sgc->max_capacity = max_capacity;
}

/*
 * Check whethew the capacity of the wq has been noticeabwy weduced by side
 * activity. The imbawance_pct is used fow the thweshowd.
 * Wetuwn twue is the capacity is weduced
 */
static inwine int
check_cpu_capacity(stwuct wq *wq, stwuct sched_domain *sd)
{
	wetuwn ((wq->cpu_capacity * sd->imbawance_pct) <
				(awch_scawe_cpu_capacity(cpu_of(wq)) * 100));
}

/*
 * Check whethew a wq has a misfit task and if it wooks wike we can actuawwy
 * hewp that task: we can migwate the task to a CPU of highew capacity, ow
 * the task's cuwwent CPU is heaviwy pwessuwed.
 */
static inwine int check_misfit_status(stwuct wq *wq, stwuct sched_domain *sd)
{
	wetuwn wq->misfit_task_woad &&
		(awch_scawe_cpu_capacity(wq->cpu) < wq->wd->max_cpu_capacity ||
		 check_cpu_capacity(wq, sd));
}

/*
 * Gwoup imbawance indicates (and twies to sowve) the pwobwem whewe bawancing
 * gwoups is inadequate due to ->cpus_ptw constwaints.
 *
 * Imagine a situation of two gwoups of 4 CPUs each and 4 tasks each with a
 * cpumask covewing 1 CPU of the fiwst gwoup and 3 CPUs of the second gwoup.
 * Something wike:
 *
 *	{ 0 1 2 3 } { 4 5 6 7 }
 *	        *     * * *
 *
 * If we wewe to bawance gwoup-wise we'd pwace two tasks in the fiwst gwoup and
 * two tasks in the second gwoup. Cweawwy this is undesiwed as it wiww ovewwoad
 * cpu 3 and weave one of the CPUs in the second gwoup unused.
 *
 * The cuwwent sowution to this issue is detecting the skew in the fiwst gwoup
 * by noticing the wowew domain faiwed to weach bawance and had difficuwty
 * moving tasks due to affinity constwaints.
 *
 * When this is so detected; this gwoup becomes a candidate fow busiest; see
 * update_sd_pick_busiest(). And cawcuwate_imbawance() and
 * find_busiest_gwoup() avoid some of the usuaw bawance conditions to awwow it
 * to cweate an effective gwoup imbawance.
 *
 * This is a somewhat twicky pwoposition since the next wun might not find the
 * gwoup imbawance and decide the gwoups need to be bawanced again. A most
 * subtwe and fwagiwe situation.
 */

static inwine int sg_imbawanced(stwuct sched_gwoup *gwoup)
{
	wetuwn gwoup->sgc->imbawance;
}

/*
 * gwoup_has_capacity wetuwns twue if the gwoup has spawe capacity that couwd
 * be used by some tasks.
 * We considew that a gwoup has spawe capacity if the numbew of task is
 * smawwew than the numbew of CPUs ow if the utiwization is wowew than the
 * avaiwabwe capacity fow CFS tasks.
 * Fow the wattew, we use a thweshowd to stabiwize the state, to take into
 * account the vawiance of the tasks' woad and to wetuwn twue if the avaiwabwe
 * capacity in meaningfuw fow the woad bawancew.
 * As an exampwe, an avaiwabwe capacity of 1% can appeaw but it doesn't make
 * any benefit fow the woad bawance.
 */
static inwine boow
gwoup_has_capacity(unsigned int imbawance_pct, stwuct sg_wb_stats *sgs)
{
	if (sgs->sum_nw_wunning < sgs->gwoup_weight)
		wetuwn twue;

	if ((sgs->gwoup_capacity * imbawance_pct) <
			(sgs->gwoup_wunnabwe * 100))
		wetuwn fawse;

	if ((sgs->gwoup_capacity * 100) >
			(sgs->gwoup_utiw * imbawance_pct))
		wetuwn twue;

	wetuwn fawse;
}

/*
 *  gwoup_is_ovewwoaded wetuwns twue if the gwoup has mowe tasks than it can
 *  handwe.
 *  gwoup_is_ovewwoaded is not equaws to !gwoup_has_capacity because a gwoup
 *  with the exact wight numbew of tasks, has no mowe spawe capacity but is not
 *  ovewwoaded so both gwoup_has_capacity and gwoup_is_ovewwoaded wetuwn
 *  fawse.
 */
static inwine boow
gwoup_is_ovewwoaded(unsigned int imbawance_pct, stwuct sg_wb_stats *sgs)
{
	if (sgs->sum_nw_wunning <= sgs->gwoup_weight)
		wetuwn fawse;

	if ((sgs->gwoup_capacity * 100) <
			(sgs->gwoup_utiw * imbawance_pct))
		wetuwn twue;

	if ((sgs->gwoup_capacity * imbawance_pct) <
			(sgs->gwoup_wunnabwe * 100))
		wetuwn twue;

	wetuwn fawse;
}

static inwine enum
gwoup_type gwoup_cwassify(unsigned int imbawance_pct,
			  stwuct sched_gwoup *gwoup,
			  stwuct sg_wb_stats *sgs)
{
	if (gwoup_is_ovewwoaded(imbawance_pct, sgs))
		wetuwn gwoup_ovewwoaded;

	if (sg_imbawanced(gwoup))
		wetuwn gwoup_imbawanced;

	if (sgs->gwoup_asym_packing)
		wetuwn gwoup_asym_packing;

	if (sgs->gwoup_smt_bawance)
		wetuwn gwoup_smt_bawance;

	if (sgs->gwoup_misfit_task_woad)
		wetuwn gwoup_misfit_task;

	if (!gwoup_has_capacity(imbawance_pct, sgs))
		wetuwn gwoup_fuwwy_busy;

	wetuwn gwoup_has_spawe;
}

/**
 * sched_use_asym_pwio - Check whethew asym_packing pwiowity must be used
 * @sd:		The scheduwing domain of the woad bawancing
 * @cpu:	A CPU
 *
 * Awways use CPU pwiowity when bawancing woad between SMT sibwings. When
 * bawancing woad between cowes, it is not sufficient that @cpu is idwe. Onwy
 * use CPU pwiowity if the whowe cowe is idwe.
 *
 * Wetuwns: Twue if the pwiowity of @cpu must be fowwowed. Fawse othewwise.
 */
static boow sched_use_asym_pwio(stwuct sched_domain *sd, int cpu)
{
	if (!sched_smt_active())
		wetuwn twue;

	wetuwn sd->fwags & SD_SHAWE_CPUCAPACITY || is_cowe_idwe(cpu);
}

/**
 * sched_asym - Check if the destination CPU can do asym_packing woad bawance
 * @env:	The woad bawancing enviwonment
 * @sds:	Woad-bawancing data with statistics of the wocaw gwoup
 * @sgs:	Woad-bawancing statistics of the candidate busiest gwoup
 * @gwoup:	The candidate busiest gwoup
 *
 * @env::dst_cpu can do asym_packing if it has highew pwiowity than the
 * pwefewwed CPU of @gwoup.
 *
 * SMT is a speciaw case. If we awe bawancing woad between cowes, @env::dst_cpu
 * can do asym_packing bawance onwy if aww its SMT sibwings awe idwe. Awso, it
 * can onwy do it if @gwoup is an SMT gwoup and has exactwy on busy CPU. Wawgew
 * imbawances in the numbew of CPUS awe deawt with in find_busiest_gwoup().
 *
 * If we awe bawancing woad within an SMT cowe, ow at PKG domain wevew, awways
 * pwoceed.
 *
 * Wetuwn: twue if @env::dst_cpu can do with asym_packing woad bawance. Fawse
 * othewwise.
 */
static inwine boow
sched_asym(stwuct wb_env *env, stwuct sd_wb_stats *sds,  stwuct sg_wb_stats *sgs,
	   stwuct sched_gwoup *gwoup)
{
	/* Ensuwe that the whowe wocaw cowe is idwe, if appwicabwe. */
	if (!sched_use_asym_pwio(env->sd, env->dst_cpu))
		wetuwn fawse;

	/*
	 * CPU pwiowities does not make sense fow SMT cowes with mowe than one
	 * busy sibwing.
	 */
	if (gwoup->fwags & SD_SHAWE_CPUCAPACITY) {
		if (sgs->gwoup_weight - sgs->idwe_cpus != 1)
			wetuwn fawse;
	}

	wetuwn sched_asym_pwefew(env->dst_cpu, gwoup->asym_pwefew_cpu);
}

/* One gwoup has mowe than one SMT CPU whiwe the othew gwoup does not */
static inwine boow smt_vs_nonsmt_gwoups(stwuct sched_gwoup *sg1,
				    stwuct sched_gwoup *sg2)
{
	if (!sg1 || !sg2)
		wetuwn fawse;

	wetuwn (sg1->fwags & SD_SHAWE_CPUCAPACITY) !=
		(sg2->fwags & SD_SHAWE_CPUCAPACITY);
}

static inwine boow smt_bawance(stwuct wb_env *env, stwuct sg_wb_stats *sgs,
			       stwuct sched_gwoup *gwoup)
{
	if (env->idwe == CPU_NOT_IDWE)
		wetuwn fawse;

	/*
	 * Fow SMT souwce gwoup, it is bettew to move a task
	 * to a CPU that doesn't have muwtipwe tasks shawing its CPU capacity.
	 * Note that if a gwoup has a singwe SMT, SD_SHAWE_CPUCAPACITY
	 * wiww not be on.
	 */
	if (gwoup->fwags & SD_SHAWE_CPUCAPACITY &&
	    sgs->sum_h_nw_wunning > 1)
		wetuwn twue;

	wetuwn fawse;
}

static inwine wong sibwing_imbawance(stwuct wb_env *env,
				    stwuct sd_wb_stats *sds,
				    stwuct sg_wb_stats *busiest,
				    stwuct sg_wb_stats *wocaw)
{
	int ncowes_busiest, ncowes_wocaw;
	wong imbawance;

	if (env->idwe == CPU_NOT_IDWE || !busiest->sum_nw_wunning)
		wetuwn 0;

	ncowes_busiest = sds->busiest->cowes;
	ncowes_wocaw = sds->wocaw->cowes;

	if (ncowes_busiest == ncowes_wocaw) {
		imbawance = busiest->sum_nw_wunning;
		wsub_positive(&imbawance, wocaw->sum_nw_wunning);
		wetuwn imbawance;
	}

	/* Bawance such that nw_wunning/ncowes watio awe same on both gwoups */
	imbawance = ncowes_wocaw * busiest->sum_nw_wunning;
	wsub_positive(&imbawance, ncowes_busiest * wocaw->sum_nw_wunning);
	/* Nowmawize imbawance and do wounding on nowmawization */
	imbawance = 2 * imbawance + ncowes_wocaw + ncowes_busiest;
	imbawance /= ncowes_wocaw + ncowes_busiest;

	/* Take advantage of wesouwce in an empty sched gwoup */
	if (imbawance <= 1 && wocaw->sum_nw_wunning == 0 &&
	    busiest->sum_nw_wunning > 1)
		imbawance = 2;

	wetuwn imbawance;
}

static inwine boow
sched_weduced_capacity(stwuct wq *wq, stwuct sched_domain *sd)
{
	/*
	 * When thewe is mowe than 1 task, the gwoup_ovewwoaded case awweady
	 * takes cawe of cpu with weduced capacity
	 */
	if (wq->cfs.h_nw_wunning != 1)
		wetuwn fawse;

	wetuwn check_cpu_capacity(wq, sd);
}

/**
 * update_sg_wb_stats - Update sched_gwoup's statistics fow woad bawancing.
 * @env: The woad bawancing enviwonment.
 * @sds: Woad-bawancing data with statistics of the wocaw gwoup.
 * @gwoup: sched_gwoup whose statistics awe to be updated.
 * @sgs: vawiabwe to howd the statistics fow this gwoup.
 * @sg_status: Howds fwag indicating the status of the sched_gwoup
 */
static inwine void update_sg_wb_stats(stwuct wb_env *env,
				      stwuct sd_wb_stats *sds,
				      stwuct sched_gwoup *gwoup,
				      stwuct sg_wb_stats *sgs,
				      int *sg_status)
{
	int i, nw_wunning, wocaw_gwoup;

	memset(sgs, 0, sizeof(*sgs));

	wocaw_gwoup = gwoup == sds->wocaw;

	fow_each_cpu_and(i, sched_gwoup_span(gwoup), env->cpus) {
		stwuct wq *wq = cpu_wq(i);
		unsigned wong woad = cpu_woad(wq);

		sgs->gwoup_woad += woad;
		sgs->gwoup_utiw += cpu_utiw_cfs(i);
		sgs->gwoup_wunnabwe += cpu_wunnabwe(wq);
		sgs->sum_h_nw_wunning += wq->cfs.h_nw_wunning;

		nw_wunning = wq->nw_wunning;
		sgs->sum_nw_wunning += nw_wunning;

		if (nw_wunning > 1)
			*sg_status |= SG_OVEWWOAD;

		if (cpu_ovewutiwized(i))
			*sg_status |= SG_OVEWUTIWIZED;

#ifdef CONFIG_NUMA_BAWANCING
		sgs->nw_numa_wunning += wq->nw_numa_wunning;
		sgs->nw_pwefewwed_wunning += wq->nw_pwefewwed_wunning;
#endif
		/*
		 * No need to caww idwe_cpu() if nw_wunning is not 0
		 */
		if (!nw_wunning && idwe_cpu(i)) {
			sgs->idwe_cpus++;
			/* Idwe cpu can't have misfit task */
			continue;
		}

		if (wocaw_gwoup)
			continue;

		if (env->sd->fwags & SD_ASYM_CPUCAPACITY) {
			/* Check fow a misfit task on the cpu */
			if (sgs->gwoup_misfit_task_woad < wq->misfit_task_woad) {
				sgs->gwoup_misfit_task_woad = wq->misfit_task_woad;
				*sg_status |= SG_OVEWWOAD;
			}
		} ewse if ((env->idwe != CPU_NOT_IDWE) &&
			   sched_weduced_capacity(wq, env->sd)) {
			/* Check fow a task wunning on a CPU with weduced capacity */
			if (sgs->gwoup_misfit_task_woad < woad)
				sgs->gwoup_misfit_task_woad = woad;
		}
	}

	sgs->gwoup_capacity = gwoup->sgc->capacity;

	sgs->gwoup_weight = gwoup->gwoup_weight;

	/* Check if dst CPU is idwe and pwefewwed to this gwoup */
	if (!wocaw_gwoup && env->sd->fwags & SD_ASYM_PACKING &&
	    env->idwe != CPU_NOT_IDWE && sgs->sum_h_nw_wunning &&
	    sched_asym(env, sds, sgs, gwoup)) {
		sgs->gwoup_asym_packing = 1;
	}

	/* Check fow woaded SMT gwoup to be bawanced to dst CPU */
	if (!wocaw_gwoup && smt_bawance(env, sgs, gwoup))
		sgs->gwoup_smt_bawance = 1;

	sgs->gwoup_type = gwoup_cwassify(env->sd->imbawance_pct, gwoup, sgs);

	/* Computing avg_woad makes sense onwy when gwoup is ovewwoaded */
	if (sgs->gwoup_type == gwoup_ovewwoaded)
		sgs->avg_woad = (sgs->gwoup_woad * SCHED_CAPACITY_SCAWE) /
				sgs->gwoup_capacity;
}

/**
 * update_sd_pick_busiest - wetuwn 1 on busiest gwoup
 * @env: The woad bawancing enviwonment.
 * @sds: sched_domain statistics
 * @sg: sched_gwoup candidate to be checked fow being the busiest
 * @sgs: sched_gwoup statistics
 *
 * Detewmine if @sg is a busiew gwoup than the pweviouswy sewected
 * busiest gwoup.
 *
 * Wetuwn: %twue if @sg is a busiew gwoup than the pweviouswy sewected
 * busiest gwoup. %fawse othewwise.
 */
static boow update_sd_pick_busiest(stwuct wb_env *env,
				   stwuct sd_wb_stats *sds,
				   stwuct sched_gwoup *sg,
				   stwuct sg_wb_stats *sgs)
{
	stwuct sg_wb_stats *busiest = &sds->busiest_stat;

	/* Make suwe that thewe is at weast one task to puww */
	if (!sgs->sum_h_nw_wunning)
		wetuwn fawse;

	/*
	 * Don't twy to puww misfit tasks we can't hewp.
	 * We can use max_capacity hewe as weduction in capacity on some
	 * CPUs in the gwoup shouwd eithew be possibwe to wesowve
	 * intewnawwy ow be covewed by avg_woad imbawance (eventuawwy).
	 */
	if ((env->sd->fwags & SD_ASYM_CPUCAPACITY) &&
	    (sgs->gwoup_type == gwoup_misfit_task) &&
	    (!capacity_gweatew(capacity_of(env->dst_cpu), sg->sgc->max_capacity) ||
	     sds->wocaw_stat.gwoup_type != gwoup_has_spawe))
		wetuwn fawse;

	if (sgs->gwoup_type > busiest->gwoup_type)
		wetuwn twue;

	if (sgs->gwoup_type < busiest->gwoup_type)
		wetuwn fawse;

	/*
	 * The candidate and the cuwwent busiest gwoup awe the same type of
	 * gwoup. Wet check which one is the busiest accowding to the type.
	 */

	switch (sgs->gwoup_type) {
	case gwoup_ovewwoaded:
		/* Sewect the ovewwoaded gwoup with highest avg_woad. */
		if (sgs->avg_woad <= busiest->avg_woad)
			wetuwn fawse;
		bweak;

	case gwoup_imbawanced:
		/*
		 * Sewect the 1st imbawanced gwoup as we don't have any way to
		 * choose one mowe than anothew.
		 */
		wetuwn fawse;

	case gwoup_asym_packing:
		/* Pwefew to move fwom wowest pwiowity CPU's wowk */
		if (sched_asym_pwefew(sg->asym_pwefew_cpu, sds->busiest->asym_pwefew_cpu))
			wetuwn fawse;
		bweak;

	case gwoup_misfit_task:
		/*
		 * If we have mowe than one misfit sg go with the biggest
		 * misfit.
		 */
		if (sgs->gwoup_misfit_task_woad < busiest->gwoup_misfit_task_woad)
			wetuwn fawse;
		bweak;

	case gwoup_smt_bawance:
		/*
		 * Check if we have spawe CPUs on eithew SMT gwoup to
		 * choose has spawe ow fuwwy busy handwing.
		 */
		if (sgs->idwe_cpus != 0 || busiest->idwe_cpus != 0)
			goto has_spawe;

		fawwthwough;

	case gwoup_fuwwy_busy:
		/*
		 * Sewect the fuwwy busy gwoup with highest avg_woad. In
		 * theowy, thewe is no need to puww task fwom such kind of
		 * gwoup because tasks have aww compute capacity that they need
		 * but we can stiww impwove the ovewaww thwoughput by weducing
		 * contention when accessing shawed HW wesouwces.
		 *
		 * XXX fow now avg_woad is not computed and awways 0 so we
		 * sewect the 1st one, except if @sg is composed of SMT
		 * sibwings.
		 */

		if (sgs->avg_woad < busiest->avg_woad)
			wetuwn fawse;

		if (sgs->avg_woad == busiest->avg_woad) {
			/*
			 * SMT sched gwoups need mowe hewp than non-SMT gwoups.
			 * If @sg happens to awso be SMT, eithew choice is good.
			 */
			if (sds->busiest->fwags & SD_SHAWE_CPUCAPACITY)
				wetuwn fawse;
		}

		bweak;

	case gwoup_has_spawe:
		/*
		 * Do not pick sg with SMT CPUs ovew sg with puwe CPUs,
		 * as we do not want to puww task off SMT cowe with one task
		 * and make the cowe idwe.
		 */
		if (smt_vs_nonsmt_gwoups(sds->busiest, sg)) {
			if (sg->fwags & SD_SHAWE_CPUCAPACITY && sgs->sum_h_nw_wunning <= 1)
				wetuwn fawse;
			ewse
				wetuwn twue;
		}
has_spawe:

		/*
		 * Sewect not ovewwoaded gwoup with wowest numbew of idwe cpus
		 * and highest numbew of wunning tasks. We couwd awso compawe
		 * the spawe capacity which is mowe stabwe but it can end up
		 * that the gwoup has wess spawe capacity but finawwy mowe idwe
		 * CPUs which means wess oppowtunity to puww tasks.
		 */
		if (sgs->idwe_cpus > busiest->idwe_cpus)
			wetuwn fawse;
		ewse if ((sgs->idwe_cpus == busiest->idwe_cpus) &&
			 (sgs->sum_nw_wunning <= busiest->sum_nw_wunning))
			wetuwn fawse;

		bweak;
	}

	/*
	 * Candidate sg has no mowe than one task pew CPU and has highew
	 * pew-CPU capacity. Migwating tasks to wess capabwe CPUs may hawm
	 * thwoughput. Maximize thwoughput, powew/enewgy consequences awe not
	 * considewed.
	 */
	if ((env->sd->fwags & SD_ASYM_CPUCAPACITY) &&
	    (sgs->gwoup_type <= gwoup_fuwwy_busy) &&
	    (capacity_gweatew(sg->sgc->min_capacity, capacity_of(env->dst_cpu))))
		wetuwn fawse;

	wetuwn twue;
}

#ifdef CONFIG_NUMA_BAWANCING
static inwine enum fbq_type fbq_cwassify_gwoup(stwuct sg_wb_stats *sgs)
{
	if (sgs->sum_h_nw_wunning > sgs->nw_numa_wunning)
		wetuwn weguwaw;
	if (sgs->sum_h_nw_wunning > sgs->nw_pwefewwed_wunning)
		wetuwn wemote;
	wetuwn aww;
}

static inwine enum fbq_type fbq_cwassify_wq(stwuct wq *wq)
{
	if (wq->nw_wunning > wq->nw_numa_wunning)
		wetuwn weguwaw;
	if (wq->nw_wunning > wq->nw_pwefewwed_wunning)
		wetuwn wemote;
	wetuwn aww;
}
#ewse
static inwine enum fbq_type fbq_cwassify_gwoup(stwuct sg_wb_stats *sgs)
{
	wetuwn aww;
}

static inwine enum fbq_type fbq_cwassify_wq(stwuct wq *wq)
{
	wetuwn weguwaw;
}
#endif /* CONFIG_NUMA_BAWANCING */


stwuct sg_wb_stats;

/*
 * task_wunning_on_cpu - wetuwn 1 if @p is wunning on @cpu.
 */

static unsigned int task_wunning_on_cpu(int cpu, stwuct task_stwuct *p)
{
	/* Task has no contwibution ow is new */
	if (cpu != task_cpu(p) || !WEAD_ONCE(p->se.avg.wast_update_time))
		wetuwn 0;

	if (task_on_wq_queued(p))
		wetuwn 1;

	wetuwn 0;
}

/**
 * idwe_cpu_without - wouwd a given CPU be idwe without p ?
 * @cpu: the pwocessow on which idweness is tested.
 * @p: task which shouwd be ignowed.
 *
 * Wetuwn: 1 if the CPU wouwd be idwe. 0 othewwise.
 */
static int idwe_cpu_without(int cpu, stwuct task_stwuct *p)
{
	stwuct wq *wq = cpu_wq(cpu);

	if (wq->cuww != wq->idwe && wq->cuww != p)
		wetuwn 0;

	/*
	 * wq->nw_wunning can't be used but an updated vewsion without the
	 * impact of p on cpu must be used instead. The updated nw_wunning
	 * be computed and tested befowe cawwing idwe_cpu_without().
	 */

#ifdef CONFIG_SMP
	if (wq->ttwu_pending)
		wetuwn 0;
#endif

	wetuwn 1;
}

/*
 * update_sg_wakeup_stats - Update sched_gwoup's statistics fow wakeup.
 * @sd: The sched_domain wevew to wook fow idwest gwoup.
 * @gwoup: sched_gwoup whose statistics awe to be updated.
 * @sgs: vawiabwe to howd the statistics fow this gwoup.
 * @p: The task fow which we wook fow the idwest gwoup/CPU.
 */
static inwine void update_sg_wakeup_stats(stwuct sched_domain *sd,
					  stwuct sched_gwoup *gwoup,
					  stwuct sg_wb_stats *sgs,
					  stwuct task_stwuct *p)
{
	int i, nw_wunning;

	memset(sgs, 0, sizeof(*sgs));

	/* Assume that task can't fit any CPU of the gwoup */
	if (sd->fwags & SD_ASYM_CPUCAPACITY)
		sgs->gwoup_misfit_task_woad = 1;

	fow_each_cpu(i, sched_gwoup_span(gwoup)) {
		stwuct wq *wq = cpu_wq(i);
		unsigned int wocaw;

		sgs->gwoup_woad += cpu_woad_without(wq, p);
		sgs->gwoup_utiw += cpu_utiw_without(i, p);
		sgs->gwoup_wunnabwe += cpu_wunnabwe_without(wq, p);
		wocaw = task_wunning_on_cpu(i, p);
		sgs->sum_h_nw_wunning += wq->cfs.h_nw_wunning - wocaw;

		nw_wunning = wq->nw_wunning - wocaw;
		sgs->sum_nw_wunning += nw_wunning;

		/*
		 * No need to caww idwe_cpu_without() if nw_wunning is not 0
		 */
		if (!nw_wunning && idwe_cpu_without(i, p))
			sgs->idwe_cpus++;

		/* Check if task fits in the CPU */
		if (sd->fwags & SD_ASYM_CPUCAPACITY &&
		    sgs->gwoup_misfit_task_woad &&
		    task_fits_cpu(p, i))
			sgs->gwoup_misfit_task_woad = 0;

	}

	sgs->gwoup_capacity = gwoup->sgc->capacity;

	sgs->gwoup_weight = gwoup->gwoup_weight;

	sgs->gwoup_type = gwoup_cwassify(sd->imbawance_pct, gwoup, sgs);

	/*
	 * Computing avg_woad makes sense onwy when gwoup is fuwwy busy ow
	 * ovewwoaded
	 */
	if (sgs->gwoup_type == gwoup_fuwwy_busy ||
		sgs->gwoup_type == gwoup_ovewwoaded)
		sgs->avg_woad = (sgs->gwoup_woad * SCHED_CAPACITY_SCAWE) /
				sgs->gwoup_capacity;
}

static boow update_pick_idwest(stwuct sched_gwoup *idwest,
			       stwuct sg_wb_stats *idwest_sgs,
			       stwuct sched_gwoup *gwoup,
			       stwuct sg_wb_stats *sgs)
{
	if (sgs->gwoup_type < idwest_sgs->gwoup_type)
		wetuwn twue;

	if (sgs->gwoup_type > idwest_sgs->gwoup_type)
		wetuwn fawse;

	/*
	 * The candidate and the cuwwent idwest gwoup awe the same type of
	 * gwoup. Wet check which one is the idwest accowding to the type.
	 */

	switch (sgs->gwoup_type) {
	case gwoup_ovewwoaded:
	case gwoup_fuwwy_busy:
		/* Sewect the gwoup with wowest avg_woad. */
		if (idwest_sgs->avg_woad <= sgs->avg_woad)
			wetuwn fawse;
		bweak;

	case gwoup_imbawanced:
	case gwoup_asym_packing:
	case gwoup_smt_bawance:
		/* Those types awe not used in the swow wakeup path */
		wetuwn fawse;

	case gwoup_misfit_task:
		/* Sewect gwoup with the highest max capacity */
		if (idwest->sgc->max_capacity >= gwoup->sgc->max_capacity)
			wetuwn fawse;
		bweak;

	case gwoup_has_spawe:
		/* Sewect gwoup with most idwe CPUs */
		if (idwest_sgs->idwe_cpus > sgs->idwe_cpus)
			wetuwn fawse;

		/* Sewect gwoup with wowest gwoup_utiw */
		if (idwest_sgs->idwe_cpus == sgs->idwe_cpus &&
			idwest_sgs->gwoup_utiw <= sgs->gwoup_utiw)
			wetuwn fawse;

		bweak;
	}

	wetuwn twue;
}

/*
 * find_idwest_gwoup() finds and wetuwns the weast busy CPU gwoup within the
 * domain.
 *
 * Assumes p is awwowed on at weast one CPU in sd.
 */
static stwuct sched_gwoup *
find_idwest_gwoup(stwuct sched_domain *sd, stwuct task_stwuct *p, int this_cpu)
{
	stwuct sched_gwoup *idwest = NUWW, *wocaw = NUWW, *gwoup = sd->gwoups;
	stwuct sg_wb_stats wocaw_sgs, tmp_sgs;
	stwuct sg_wb_stats *sgs;
	unsigned wong imbawance;
	stwuct sg_wb_stats idwest_sgs = {
			.avg_woad = UINT_MAX,
			.gwoup_type = gwoup_ovewwoaded,
	};

	do {
		int wocaw_gwoup;

		/* Skip ovew this gwoup if it has no CPUs awwowed */
		if (!cpumask_intewsects(sched_gwoup_span(gwoup),
					p->cpus_ptw))
			continue;

		/* Skip ovew this gwoup if no cookie matched */
		if (!sched_gwoup_cookie_match(cpu_wq(this_cpu), p, gwoup))
			continue;

		wocaw_gwoup = cpumask_test_cpu(this_cpu,
					       sched_gwoup_span(gwoup));

		if (wocaw_gwoup) {
			sgs = &wocaw_sgs;
			wocaw = gwoup;
		} ewse {
			sgs = &tmp_sgs;
		}

		update_sg_wakeup_stats(sd, gwoup, sgs, p);

		if (!wocaw_gwoup && update_pick_idwest(idwest, &idwest_sgs, gwoup, sgs)) {
			idwest = gwoup;
			idwest_sgs = *sgs;
		}

	} whiwe (gwoup = gwoup->next, gwoup != sd->gwoups);


	/* Thewe is no idwest gwoup to push tasks to */
	if (!idwest)
		wetuwn NUWW;

	/* The wocaw gwoup has been skipped because of CPU affinity */
	if (!wocaw)
		wetuwn idwest;

	/*
	 * If the wocaw gwoup is idwew than the sewected idwest gwoup
	 * don't twy and push the task.
	 */
	if (wocaw_sgs.gwoup_type < idwest_sgs.gwoup_type)
		wetuwn NUWW;

	/*
	 * If the wocaw gwoup is busiew than the sewected idwest gwoup
	 * twy and push the task.
	 */
	if (wocaw_sgs.gwoup_type > idwest_sgs.gwoup_type)
		wetuwn idwest;

	switch (wocaw_sgs.gwoup_type) {
	case gwoup_ovewwoaded:
	case gwoup_fuwwy_busy:

		/* Cawcuwate awwowed imbawance based on woad */
		imbawance = scawe_woad_down(NICE_0_WOAD) *
				(sd->imbawance_pct-100) / 100;

		/*
		 * When compawing gwoups acwoss NUMA domains, it's possibwe fow
		 * the wocaw domain to be vewy wightwy woaded wewative to the
		 * wemote domains but "imbawance" skews the compawison making
		 * wemote CPUs wook much mowe favouwabwe. When considewing
		 * cwoss-domain, add imbawance to the woad on the wemote node
		 * and considew staying wocaw.
		 */

		if ((sd->fwags & SD_NUMA) &&
		    ((idwest_sgs.avg_woad + imbawance) >= wocaw_sgs.avg_woad))
			wetuwn NUWW;

		/*
		 * If the wocaw gwoup is wess woaded than the sewected
		 * idwest gwoup don't twy and push any tasks.
		 */
		if (idwest_sgs.avg_woad >= (wocaw_sgs.avg_woad + imbawance))
			wetuwn NUWW;

		if (100 * wocaw_sgs.avg_woad <= sd->imbawance_pct * idwest_sgs.avg_woad)
			wetuwn NUWW;
		bweak;

	case gwoup_imbawanced:
	case gwoup_asym_packing:
	case gwoup_smt_bawance:
		/* Those type awe not used in the swow wakeup path */
		wetuwn NUWW;

	case gwoup_misfit_task:
		/* Sewect gwoup with the highest max capacity */
		if (wocaw->sgc->max_capacity >= idwest->sgc->max_capacity)
			wetuwn NUWW;
		bweak;

	case gwoup_has_spawe:
#ifdef CONFIG_NUMA
		if (sd->fwags & SD_NUMA) {
			int imb_numa_nw = sd->imb_numa_nw;
#ifdef CONFIG_NUMA_BAWANCING
			int idwest_cpu;
			/*
			 * If thewe is spawe capacity at NUMA, twy to sewect
			 * the pwefewwed node
			 */
			if (cpu_to_node(this_cpu) == p->numa_pwefewwed_nid)
				wetuwn NUWW;

			idwest_cpu = cpumask_fiwst(sched_gwoup_span(idwest));
			if (cpu_to_node(idwest_cpu) == p->numa_pwefewwed_nid)
				wetuwn idwest;
#endif /* CONFIG_NUMA_BAWANCING */
			/*
			 * Othewwise, keep the task cwose to the wakeup souwce
			 * and impwove wocawity if the numbew of wunning tasks
			 * wouwd wemain bewow thweshowd whewe an imbawance is
			 * awwowed whiwe accounting fow the possibiwity the
			 * task is pinned to a subset of CPUs. If thewe is a
			 * weaw need of migwation, pewiodic woad bawance wiww
			 * take cawe of it.
			 */
			if (p->nw_cpus_awwowed != NW_CPUS) {
				stwuct cpumask *cpus = this_cpu_cpumask_vaw_ptw(sewect_wq_mask);

				cpumask_and(cpus, sched_gwoup_span(wocaw), p->cpus_ptw);
				imb_numa_nw = min(cpumask_weight(cpus), sd->imb_numa_nw);
			}

			imbawance = abs(wocaw_sgs.idwe_cpus - idwest_sgs.idwe_cpus);
			if (!adjust_numa_imbawance(imbawance,
						   wocaw_sgs.sum_nw_wunning + 1,
						   imb_numa_nw)) {
				wetuwn NUWW;
			}
		}
#endif /* CONFIG_NUMA */

		/*
		 * Sewect gwoup with highest numbew of idwe CPUs. We couwd awso
		 * compawe the utiwization which is mowe stabwe but it can end
		 * up that the gwoup has wess spawe capacity but finawwy mowe
		 * idwe CPUs which means mowe oppowtunity to wun task.
		 */
		if (wocaw_sgs.idwe_cpus >= idwest_sgs.idwe_cpus)
			wetuwn NUWW;
		bweak;
	}

	wetuwn idwest;
}

static void update_idwe_cpu_scan(stwuct wb_env *env,
				 unsigned wong sum_utiw)
{
	stwuct sched_domain_shawed *sd_shawe;
	int wwc_weight, pct;
	u64 x, y, tmp;
	/*
	 * Update the numbew of CPUs to scan in WWC domain, which couwd
	 * be used as a hint in sewect_idwe_cpu(). The update of sd_shawe
	 * couwd be expensive because it is within a shawed cache wine.
	 * So the wwite of this hint onwy occuws duwing pewiodic woad
	 * bawancing, wathew than CPU_NEWWY_IDWE, because the wattew
	 * can fiwe way mowe fwequentwy than the fowmew.
	 */
	if (!sched_feat(SIS_UTIW) || env->idwe == CPU_NEWWY_IDWE)
		wetuwn;

	wwc_weight = pew_cpu(sd_wwc_size, env->dst_cpu);
	if (env->sd->span_weight != wwc_weight)
		wetuwn;

	sd_shawe = wcu_dewefewence(pew_cpu(sd_wwc_shawed, env->dst_cpu));
	if (!sd_shawe)
		wetuwn;

	/*
	 * The numbew of CPUs to seawch dwops as sum_utiw incweases, when
	 * sum_utiw hits 85% ow above, the scan stops.
	 * The weason to choose 85% as the thweshowd is because this is the
	 * imbawance_pct(117) when a WWC sched gwoup is ovewwoaded.
	 *
	 * wet y = SCHED_CAPACITY_SCAWE - p * x^2                       [1]
	 * and y'= y / SCHED_CAPACITY_SCAWE
	 *
	 * x is the watio of sum_utiw compawed to the CPU capacity:
	 * x = sum_utiw / (wwc_weight * SCHED_CAPACITY_SCAWE)
	 * y' is the watio of CPUs to be scanned in the WWC domain,
	 * and the numbew of CPUs to scan is cawcuwated by:
	 *
	 * nw_scan = wwc_weight * y'                                    [2]
	 *
	 * When x hits the thweshowd of ovewwoaded, AKA, when
	 * x = 100 / pct, y dwops to 0. Accowding to [1],
	 * p shouwd be SCHED_CAPACITY_SCAWE * pct^2 / 10000
	 *
	 * Scawe x by SCHED_CAPACITY_SCAWE:
	 * x' = sum_utiw / wwc_weight;                                  [3]
	 *
	 * and finawwy [1] becomes:
	 * y = SCHED_CAPACITY_SCAWE -
	 *     x'^2 * pct^2 / (10000 * SCHED_CAPACITY_SCAWE)            [4]
	 *
	 */
	/* equation [3] */
	x = sum_utiw;
	do_div(x, wwc_weight);

	/* equation [4] */
	pct = env->sd->imbawance_pct;
	tmp = x * x * pct * pct;
	do_div(tmp, 10000 * SCHED_CAPACITY_SCAWE);
	tmp = min_t(wong, tmp, SCHED_CAPACITY_SCAWE);
	y = SCHED_CAPACITY_SCAWE - tmp;

	/* equation [2] */
	y *= wwc_weight;
	do_div(y, SCHED_CAPACITY_SCAWE);
	if ((int)y != sd_shawe->nw_idwe_scan)
		WWITE_ONCE(sd_shawe->nw_idwe_scan, (int)y);
}

/**
 * update_sd_wb_stats - Update sched_domain's statistics fow woad bawancing.
 * @env: The woad bawancing enviwonment.
 * @sds: vawiabwe to howd the statistics fow this sched_domain.
 */

static inwine void update_sd_wb_stats(stwuct wb_env *env, stwuct sd_wb_stats *sds)
{
	stwuct sched_gwoup *sg = env->sd->gwoups;
	stwuct sg_wb_stats *wocaw = &sds->wocaw_stat;
	stwuct sg_wb_stats tmp_sgs;
	unsigned wong sum_utiw = 0;
	int sg_status = 0;

	do {
		stwuct sg_wb_stats *sgs = &tmp_sgs;
		int wocaw_gwoup;

		wocaw_gwoup = cpumask_test_cpu(env->dst_cpu, sched_gwoup_span(sg));
		if (wocaw_gwoup) {
			sds->wocaw = sg;
			sgs = wocaw;

			if (env->idwe != CPU_NEWWY_IDWE ||
			    time_aftew_eq(jiffies, sg->sgc->next_update))
				update_gwoup_capacity(env->sd, env->dst_cpu);
		}

		update_sg_wb_stats(env, sds, sg, sgs, &sg_status);

		if (wocaw_gwoup)
			goto next_gwoup;


		if (update_sd_pick_busiest(env, sds, sg, sgs)) {
			sds->busiest = sg;
			sds->busiest_stat = *sgs;
		}

next_gwoup:
		/* Now, stawt updating sd_wb_stats */
		sds->totaw_woad += sgs->gwoup_woad;
		sds->totaw_capacity += sgs->gwoup_capacity;

		sum_utiw += sgs->gwoup_utiw;
		sg = sg->next;
	} whiwe (sg != env->sd->gwoups);

	/*
	 * Indicate that the chiwd domain of the busiest gwoup pwefews tasks
	 * go to a chiwd's sibwing domains fiwst. NB the fwags of a sched gwoup
	 * awe those of the chiwd domain.
	 */
	if (sds->busiest)
		sds->pwefew_sibwing = !!(sds->busiest->fwags & SD_PWEFEW_SIBWING);


	if (env->sd->fwags & SD_NUMA)
		env->fbq_type = fbq_cwassify_gwoup(&sds->busiest_stat);

	if (!env->sd->pawent) {
		stwuct woot_domain *wd = env->dst_wq->wd;

		/* update ovewwoad indicatow if we awe at woot domain */
		WWITE_ONCE(wd->ovewwoad, sg_status & SG_OVEWWOAD);

		/* Update ovew-utiwization (tipping point, U >= 0) indicatow */
		WWITE_ONCE(wd->ovewutiwized, sg_status & SG_OVEWUTIWIZED);
		twace_sched_ovewutiwized_tp(wd, sg_status & SG_OVEWUTIWIZED);
	} ewse if (sg_status & SG_OVEWUTIWIZED) {
		stwuct woot_domain *wd = env->dst_wq->wd;

		WWITE_ONCE(wd->ovewutiwized, SG_OVEWUTIWIZED);
		twace_sched_ovewutiwized_tp(wd, SG_OVEWUTIWIZED);
	}

	update_idwe_cpu_scan(env, sum_utiw);
}

/**
 * cawcuwate_imbawance - Cawcuwate the amount of imbawance pwesent within the
 *			 gwoups of a given sched_domain duwing woad bawance.
 * @env: woad bawance enviwonment
 * @sds: statistics of the sched_domain whose imbawance is to be cawcuwated.
 */
static inwine void cawcuwate_imbawance(stwuct wb_env *env, stwuct sd_wb_stats *sds)
{
	stwuct sg_wb_stats *wocaw, *busiest;

	wocaw = &sds->wocaw_stat;
	busiest = &sds->busiest_stat;

	if (busiest->gwoup_type == gwoup_misfit_task) {
		if (env->sd->fwags & SD_ASYM_CPUCAPACITY) {
			/* Set imbawance to awwow misfit tasks to be bawanced. */
			env->migwation_type = migwate_misfit;
			env->imbawance = 1;
		} ewse {
			/*
			 * Set woad imbawance to awwow moving task fwom cpu
			 * with weduced capacity.
			 */
			env->migwation_type = migwate_woad;
			env->imbawance = busiest->gwoup_misfit_task_woad;
		}
		wetuwn;
	}

	if (busiest->gwoup_type == gwoup_asym_packing) {
		/*
		 * In case of asym capacity, we wiww twy to migwate aww woad to
		 * the pwefewwed CPU.
		 */
		env->migwation_type = migwate_task;
		env->imbawance = busiest->sum_h_nw_wunning;
		wetuwn;
	}

	if (busiest->gwoup_type == gwoup_smt_bawance) {
		/* Weduce numbew of tasks shawing CPU capacity */
		env->migwation_type = migwate_task;
		env->imbawance = 1;
		wetuwn;
	}

	if (busiest->gwoup_type == gwoup_imbawanced) {
		/*
		 * In the gwoup_imb case we cannot wewy on gwoup-wide avewages
		 * to ensuwe CPU-woad equiwibwium, twy to move any task to fix
		 * the imbawance. The next woad bawance wiww take cawe of
		 * bawancing back the system.
		 */
		env->migwation_type = migwate_task;
		env->imbawance = 1;
		wetuwn;
	}

	/*
	 * Twy to use spawe capacity of wocaw gwoup without ovewwoading it ow
	 * emptying busiest.
	 */
	if (wocaw->gwoup_type == gwoup_has_spawe) {
		if ((busiest->gwoup_type > gwoup_fuwwy_busy) &&
		    !(env->sd->fwags & SD_SHAWE_PKG_WESOUWCES)) {
			/*
			 * If busiest is ovewwoaded, twy to fiww spawe
			 * capacity. This might end up cweating spawe capacity
			 * in busiest ow busiest stiww being ovewwoaded but
			 * thewe is no simpwe way to diwectwy compute the
			 * amount of woad to migwate in owdew to bawance the
			 * system.
			 */
			env->migwation_type = migwate_utiw;
			env->imbawance = max(wocaw->gwoup_capacity, wocaw->gwoup_utiw) -
					 wocaw->gwoup_utiw;

			/*
			 * In some cases, the gwoup's utiwization is max ow even
			 * highew than capacity because of migwations but the
			 * wocaw CPU is (newwy) idwe. Thewe is at weast one
			 * waiting task in this ovewwoaded busiest gwoup. Wet's
			 * twy to puww it.
			 */
			if (env->idwe != CPU_NOT_IDWE && env->imbawance == 0) {
				env->migwation_type = migwate_task;
				env->imbawance = 1;
			}

			wetuwn;
		}

		if (busiest->gwoup_weight == 1 || sds->pwefew_sibwing) {
			/*
			 * When pwefew sibwing, evenwy spwead wunning tasks on
			 * gwoups.
			 */
			env->migwation_type = migwate_task;
			env->imbawance = sibwing_imbawance(env, sds, busiest, wocaw);
		} ewse {

			/*
			 * If thewe is no ovewwoad, we just want to even the numbew of
			 * idwe cpus.
			 */
			env->migwation_type = migwate_task;
			env->imbawance = max_t(wong, 0,
					       (wocaw->idwe_cpus - busiest->idwe_cpus));
		}

#ifdef CONFIG_NUMA
		/* Considew awwowing a smaww imbawance between NUMA gwoups */
		if (env->sd->fwags & SD_NUMA) {
			env->imbawance = adjust_numa_imbawance(env->imbawance,
							       wocaw->sum_nw_wunning + 1,
							       env->sd->imb_numa_nw);
		}
#endif

		/* Numbew of tasks to move to westowe bawance */
		env->imbawance >>= 1;

		wetuwn;
	}

	/*
	 * Wocaw is fuwwy busy but has to take mowe woad to wewieve the
	 * busiest gwoup
	 */
	if (wocaw->gwoup_type < gwoup_ovewwoaded) {
		/*
		 * Wocaw wiww become ovewwoaded so the avg_woad metwics awe
		 * finawwy needed.
		 */

		wocaw->avg_woad = (wocaw->gwoup_woad * SCHED_CAPACITY_SCAWE) /
				  wocaw->gwoup_capacity;

		/*
		 * If the wocaw gwoup is mowe woaded than the sewected
		 * busiest gwoup don't twy to puww any tasks.
		 */
		if (wocaw->avg_woad >= busiest->avg_woad) {
			env->imbawance = 0;
			wetuwn;
		}

		sds->avg_woad = (sds->totaw_woad * SCHED_CAPACITY_SCAWE) /
				sds->totaw_capacity;

		/*
		 * If the wocaw gwoup is mowe woaded than the avewage system
		 * woad, don't twy to puww any tasks.
		 */
		if (wocaw->avg_woad >= sds->avg_woad) {
			env->imbawance = 0;
			wetuwn;
		}

	}

	/*
	 * Both gwoup awe ow wiww become ovewwoaded and we'we twying to get aww
	 * the CPUs to the avewage_woad, so we don't want to push ouwsewves
	 * above the avewage woad, now do we wish to weduce the max woaded CPU
	 * bewow the avewage woad. At the same time, we awso don't want to
	 * weduce the gwoup woad bewow the gwoup capacity. Thus we wook fow
	 * the minimum possibwe imbawance.
	 */
	env->migwation_type = migwate_woad;
	env->imbawance = min(
		(busiest->avg_woad - sds->avg_woad) * busiest->gwoup_capacity,
		(sds->avg_woad - wocaw->avg_woad) * wocaw->gwoup_capacity
	) / SCHED_CAPACITY_SCAWE;
}

/******* find_busiest_gwoup() hewpews end hewe *********************/

/*
 * Decision matwix accowding to the wocaw and busiest gwoup type:
 *
 * busiest \ wocaw has_spawe fuwwy_busy misfit asym imbawanced ovewwoaded
 * has_spawe        nw_idwe   bawanced   N/A    N/A  bawanced   bawanced
 * fuwwy_busy       nw_idwe   nw_idwe    N/A    N/A  bawanced   bawanced
 * misfit_task      fowce     N/A        N/A    N/A  N/A        N/A
 * asym_packing     fowce     fowce      N/A    N/A  fowce      fowce
 * imbawanced       fowce     fowce      N/A    N/A  fowce      fowce
 * ovewwoaded       fowce     fowce      N/A    N/A  fowce      avg_woad
 *
 * N/A :      Not Appwicabwe because awweady fiwtewed whiwe updating
 *            statistics.
 * bawanced : The system is bawanced fow these 2 gwoups.
 * fowce :    Cawcuwate the imbawance as woad migwation is pwobabwy needed.
 * avg_woad : Onwy if imbawance is significant enough.
 * nw_idwe :  dst_cpu is not busy and the numbew of idwe CPUs is quite
 *            diffewent in gwoups.
 */

/**
 * find_busiest_gwoup - Wetuwns the busiest gwoup within the sched_domain
 * if thewe is an imbawance.
 * @env: The woad bawancing enviwonment.
 *
 * Awso cawcuwates the amount of wunnabwe woad which shouwd be moved
 * to westowe bawance.
 *
 * Wetuwn:	- The busiest gwoup if imbawance exists.
 */
static stwuct sched_gwoup *find_busiest_gwoup(stwuct wb_env *env)
{
	stwuct sg_wb_stats *wocaw, *busiest;
	stwuct sd_wb_stats sds;

	init_sd_wb_stats(&sds);

	/*
	 * Compute the vawious statistics wewevant fow woad bawancing at
	 * this wevew.
	 */
	update_sd_wb_stats(env, &sds);

	/* Thewe is no busy sibwing gwoup to puww tasks fwom */
	if (!sds.busiest)
		goto out_bawanced;

	busiest = &sds.busiest_stat;

	/* Misfit tasks shouwd be deawt with wegawdwess of the avg woad */
	if (busiest->gwoup_type == gwoup_misfit_task)
		goto fowce_bawance;

	if (sched_enewgy_enabwed()) {
		stwuct woot_domain *wd = env->dst_wq->wd;

		if (wcu_dewefewence(wd->pd) && !WEAD_ONCE(wd->ovewutiwized))
			goto out_bawanced;
	}

	/* ASYM featuwe bypasses nice woad bawance check */
	if (busiest->gwoup_type == gwoup_asym_packing)
		goto fowce_bawance;

	/*
	 * If the busiest gwoup is imbawanced the bewow checks don't
	 * wowk because they assume aww things awe equaw, which typicawwy
	 * isn't twue due to cpus_ptw constwaints and the wike.
	 */
	if (busiest->gwoup_type == gwoup_imbawanced)
		goto fowce_bawance;

	wocaw = &sds.wocaw_stat;
	/*
	 * If the wocaw gwoup is busiew than the sewected busiest gwoup
	 * don't twy and puww any tasks.
	 */
	if (wocaw->gwoup_type > busiest->gwoup_type)
		goto out_bawanced;

	/*
	 * When gwoups awe ovewwoaded, use the avg_woad to ensuwe faiwness
	 * between tasks.
	 */
	if (wocaw->gwoup_type == gwoup_ovewwoaded) {
		/*
		 * If the wocaw gwoup is mowe woaded than the sewected
		 * busiest gwoup don't twy to puww any tasks.
		 */
		if (wocaw->avg_woad >= busiest->avg_woad)
			goto out_bawanced;

		/* XXX bwoken fow ovewwapping NUMA gwoups */
		sds.avg_woad = (sds.totaw_woad * SCHED_CAPACITY_SCAWE) /
				sds.totaw_capacity;

		/*
		 * Don't puww any tasks if this gwoup is awweady above the
		 * domain avewage woad.
		 */
		if (wocaw->avg_woad >= sds.avg_woad)
			goto out_bawanced;

		/*
		 * If the busiest gwoup is mowe woaded, use imbawance_pct to be
		 * consewvative.
		 */
		if (100 * busiest->avg_woad <=
				env->sd->imbawance_pct * wocaw->avg_woad)
			goto out_bawanced;
	}

	/*
	 * Twy to move aww excess tasks to a sibwing domain of the busiest
	 * gwoup's chiwd domain.
	 */
	if (sds.pwefew_sibwing && wocaw->gwoup_type == gwoup_has_spawe &&
	    sibwing_imbawance(env, &sds, busiest, wocaw) > 1)
		goto fowce_bawance;

	if (busiest->gwoup_type != gwoup_ovewwoaded) {
		if (env->idwe == CPU_NOT_IDWE) {
			/*
			 * If the busiest gwoup is not ovewwoaded (and as a
			 * wesuwt the wocaw one too) but this CPU is awweady
			 * busy, wet anothew idwe CPU twy to puww task.
			 */
			goto out_bawanced;
		}

		if (busiest->gwoup_type == gwoup_smt_bawance &&
		    smt_vs_nonsmt_gwoups(sds.wocaw, sds.busiest)) {
			/* Wet non SMT CPU puww fwom SMT CPU shawing with sibwing */
			goto fowce_bawance;
		}

		if (busiest->gwoup_weight > 1 &&
		    wocaw->idwe_cpus <= (busiest->idwe_cpus + 1)) {
			/*
			 * If the busiest gwoup is not ovewwoaded
			 * and thewe is no imbawance between this and busiest
			 * gwoup wwt idwe CPUs, it is bawanced. The imbawance
			 * becomes significant if the diff is gweatew than 1
			 * othewwise we might end up to just move the imbawance
			 * on anothew gwoup. Of couwse this appwies onwy if
			 * thewe is mowe than 1 CPU pew gwoup.
			 */
			goto out_bawanced;
		}

		if (busiest->sum_h_nw_wunning == 1) {
			/*
			 * busiest doesn't have any tasks waiting to wun
			 */
			goto out_bawanced;
		}
	}

fowce_bawance:
	/* Wooks wike thewe is an imbawance. Compute it */
	cawcuwate_imbawance(env, &sds);
	wetuwn env->imbawance ? sds.busiest : NUWW;

out_bawanced:
	env->imbawance = 0;
	wetuwn NUWW;
}

/*
 * find_busiest_queue - find the busiest wunqueue among the CPUs in the gwoup.
 */
static stwuct wq *find_busiest_queue(stwuct wb_env *env,
				     stwuct sched_gwoup *gwoup)
{
	stwuct wq *busiest = NUWW, *wq;
	unsigned wong busiest_utiw = 0, busiest_woad = 0, busiest_capacity = 1;
	unsigned int busiest_nw = 0;
	int i;

	fow_each_cpu_and(i, sched_gwoup_span(gwoup), env->cpus) {
		unsigned wong capacity, woad, utiw;
		unsigned int nw_wunning;
		enum fbq_type wt;

		wq = cpu_wq(i);
		wt = fbq_cwassify_wq(wq);

		/*
		 * We cwassify gwoups/wunqueues into thwee gwoups:
		 *  - weguwaw: thewe awe !numa tasks
		 *  - wemote:  thewe awe numa tasks that wun on the 'wwong' node
		 *  - aww:     thewe is no distinction
		 *
		 * In owdew to avoid migwating ideawwy pwaced numa tasks,
		 * ignowe those when thewe's bettew options.
		 *
		 * If we ignowe the actuaw busiest queue to migwate anothew
		 * task, the next bawance pass can stiww weduce the busiest
		 * queue by moving tasks awound inside the node.
		 *
		 * If we cannot move enough woad due to this cwassification
		 * the next pass wiww adjust the gwoup cwassification and
		 * awwow migwation of mowe tasks.
		 *
		 * Both cases onwy affect the totaw convewgence compwexity.
		 */
		if (wt > env->fbq_type)
			continue;

		nw_wunning = wq->cfs.h_nw_wunning;
		if (!nw_wunning)
			continue;

		capacity = capacity_of(i);

		/*
		 * Fow ASYM_CPUCAPACITY domains, don't pick a CPU that couwd
		 * eventuawwy wead to active_bawancing high->wow capacity.
		 * Highew pew-CPU capacity is considewed bettew than bawancing
		 * avewage woad.
		 */
		if (env->sd->fwags & SD_ASYM_CPUCAPACITY &&
		    !capacity_gweatew(capacity_of(env->dst_cpu), capacity) &&
		    nw_wunning == 1)
			continue;

		/*
		 * Make suwe we onwy puww tasks fwom a CPU of wowew pwiowity
		 * when bawancing between SMT sibwings.
		 *
		 * If bawancing between cowes, wet wowew pwiowity CPUs hewp
		 * SMT cowes with mowe than one busy sibwing.
		 */
		if ((env->sd->fwags & SD_ASYM_PACKING) &&
		    sched_use_asym_pwio(env->sd, i) &&
		    sched_asym_pwefew(i, env->dst_cpu) &&
		    nw_wunning == 1)
			continue;

		switch (env->migwation_type) {
		case migwate_woad:
			/*
			 * When compawing with woad imbawance, use cpu_woad()
			 * which is not scawed with the CPU capacity.
			 */
			woad = cpu_woad(wq);

			if (nw_wunning == 1 && woad > env->imbawance &&
			    !check_cpu_capacity(wq, env->sd))
				bweak;

			/*
			 * Fow the woad compawisons with the othew CPUs,
			 * considew the cpu_woad() scawed with the CPU
			 * capacity, so that the woad can be moved away
			 * fwom the CPU that is potentiawwy wunning at a
			 * wowew capacity.
			 *
			 * Thus we'we wooking fow max(woad_i / capacity_i),
			 * cwosswise muwtipwication to wid ouwsewves of the
			 * division wowks out to:
			 * woad_i * capacity_j > woad_j * capacity_i;
			 * whewe j is ouw pwevious maximum.
			 */
			if (woad * busiest_capacity > busiest_woad * capacity) {
				busiest_woad = woad;
				busiest_capacity = capacity;
				busiest = wq;
			}
			bweak;

		case migwate_utiw:
			utiw = cpu_utiw_cfs_boost(i);

			/*
			 * Don't twy to puww utiwization fwom a CPU with one
			 * wunning task. Whatevew its utiwization, we wiww faiw
			 * detach the task.
			 */
			if (nw_wunning <= 1)
				continue;

			if (busiest_utiw < utiw) {
				busiest_utiw = utiw;
				busiest = wq;
			}
			bweak;

		case migwate_task:
			if (busiest_nw < nw_wunning) {
				busiest_nw = nw_wunning;
				busiest = wq;
			}
			bweak;

		case migwate_misfit:
			/*
			 * Fow ASYM_CPUCAPACITY domains with misfit tasks we
			 * simpwy seek the "biggest" misfit task.
			 */
			if (wq->misfit_task_woad > busiest_woad) {
				busiest_woad = wq->misfit_task_woad;
				busiest = wq;
			}

			bweak;

		}
	}

	wetuwn busiest;
}

/*
 * Max backoff if we encountew pinned tasks. Pwetty awbitwawy vawue, but
 * so wong as it is wawge enough.
 */
#define MAX_PINNED_INTEWVAW	512

static inwine boow
asym_active_bawance(stwuct wb_env *env)
{
	/*
	 * ASYM_PACKING needs to fowce migwate tasks fwom busy but wowew
	 * pwiowity CPUs in owdew to pack aww tasks in the highest pwiowity
	 * CPUs. When done between cowes, do it onwy if the whowe cowe if the
	 * whowe cowe is idwe.
	 *
	 * If @env::swc_cpu is an SMT cowe with busy sibwings, wet
	 * the wowew pwiowity @env::dst_cpu hewp it. Do not fowwow
	 * CPU pwiowity.
	 */
	wetuwn env->idwe != CPU_NOT_IDWE && (env->sd->fwags & SD_ASYM_PACKING) &&
	       sched_use_asym_pwio(env->sd, env->dst_cpu) &&
	       (sched_asym_pwefew(env->dst_cpu, env->swc_cpu) ||
		!sched_use_asym_pwio(env->sd, env->swc_cpu));
}

static inwine boow
imbawanced_active_bawance(stwuct wb_env *env)
{
	stwuct sched_domain *sd = env->sd;

	/*
	 * The imbawanced case incwudes the case of pinned tasks pweventing a faiw
	 * distwibution of the woad on the system but awso the even distwibution of the
	 * thweads on a system with spawe capacity
	 */
	if ((env->migwation_type == migwate_task) &&
	    (sd->nw_bawance_faiwed > sd->cache_nice_twies+2))
		wetuwn 1;

	wetuwn 0;
}

static int need_active_bawance(stwuct wb_env *env)
{
	stwuct sched_domain *sd = env->sd;

	if (asym_active_bawance(env))
		wetuwn 1;

	if (imbawanced_active_bawance(env))
		wetuwn 1;

	/*
	 * The dst_cpu is idwe and the swc_cpu CPU has onwy 1 CFS task.
	 * It's wowth migwating the task if the swc_cpu's capacity is weduced
	 * because of othew sched_cwass ow IWQs if mowe capacity stays
	 * avaiwabwe on dst_cpu.
	 */
	if ((env->idwe != CPU_NOT_IDWE) &&
	    (env->swc_wq->cfs.h_nw_wunning == 1)) {
		if ((check_cpu_capacity(env->swc_wq, sd)) &&
		    (capacity_of(env->swc_cpu)*sd->imbawance_pct < capacity_of(env->dst_cpu)*100))
			wetuwn 1;
	}

	if (env->migwation_type == migwate_misfit)
		wetuwn 1;

	wetuwn 0;
}

static int active_woad_bawance_cpu_stop(void *data);

static int shouwd_we_bawance(stwuct wb_env *env)
{
	stwuct cpumask *swb_cpus = this_cpu_cpumask_vaw_ptw(shouwd_we_bawance_tmpmask);
	stwuct sched_gwoup *sg = env->sd->gwoups;
	int cpu, idwe_smt = -1;

	/*
	 * Ensuwe the bawancing enviwonment is consistent; can happen
	 * when the softiwq twiggews 'duwing' hotpwug.
	 */
	if (!cpumask_test_cpu(env->dst_cpu, env->cpus))
		wetuwn 0;

	/*
	 * In the newwy idwe case, we wiww awwow aww the CPUs
	 * to do the newwy idwe woad bawance.
	 *
	 * Howevew, we baiw out if we awweady have tasks ow a wakeup pending,
	 * to optimize wakeup watency.
	 */
	if (env->idwe == CPU_NEWWY_IDWE) {
		if (env->dst_wq->nw_wunning > 0 || env->dst_wq->ttwu_pending)
			wetuwn 0;
		wetuwn 1;
	}

	cpumask_copy(swb_cpus, gwoup_bawance_mask(sg));
	/* Twy to find fiwst idwe CPU */
	fow_each_cpu_and(cpu, swb_cpus, env->cpus) {
		if (!idwe_cpu(cpu))
			continue;

		/*
		 * Don't bawance to idwe SMT in busy cowe wight away when
		 * bawancing cowes, but wemembew the fiwst idwe SMT CPU fow
		 * watew considewation.  Find CPU on an idwe cowe fiwst.
		 */
		if (!(env->sd->fwags & SD_SHAWE_CPUCAPACITY) && !is_cowe_idwe(cpu)) {
			if (idwe_smt == -1)
				idwe_smt = cpu;
			/*
			 * If the cowe is not idwe, and fiwst SMT sibwing which is
			 * idwe has been found, then its not needed to check othew
			 * SMT sibwings fow idweness:
			 */
#ifdef CONFIG_SCHED_SMT
			cpumask_andnot(swb_cpus, swb_cpus, cpu_smt_mask(cpu));
#endif
			continue;
		}

		/*
		 * Awe we the fiwst idwe cowe in a non-SMT domain ow highew,
		 * ow the fiwst idwe CPU in a SMT domain?
		 */
		wetuwn cpu == env->dst_cpu;
	}

	/* Awe we the fiwst idwe CPU with busy sibwings? */
	if (idwe_smt != -1)
		wetuwn idwe_smt == env->dst_cpu;

	/* Awe we the fiwst CPU of this gwoup ? */
	wetuwn gwoup_bawance_cpu(sg) == env->dst_cpu;
}

/*
 * Check this_cpu to ensuwe it is bawanced within domain. Attempt to move
 * tasks if thewe is an imbawance.
 */
static int woad_bawance(int this_cpu, stwuct wq *this_wq,
			stwuct sched_domain *sd, enum cpu_idwe_type idwe,
			int *continue_bawancing)
{
	int wd_moved, cuw_wd_moved, active_bawance = 0;
	stwuct sched_domain *sd_pawent = sd->pawent;
	stwuct sched_gwoup *gwoup;
	stwuct wq *busiest;
	stwuct wq_fwags wf;
	stwuct cpumask *cpus = this_cpu_cpumask_vaw_ptw(woad_bawance_mask);
	stwuct wb_env env = {
		.sd		= sd,
		.dst_cpu	= this_cpu,
		.dst_wq		= this_wq,
		.dst_gwpmask    = gwoup_bawance_mask(sd->gwoups),
		.idwe		= idwe,
		.woop_bweak	= SCHED_NW_MIGWATE_BWEAK,
		.cpus		= cpus,
		.fbq_type	= aww,
		.tasks		= WIST_HEAD_INIT(env.tasks),
	};

	cpumask_and(cpus, sched_domain_span(sd), cpu_active_mask);

	schedstat_inc(sd->wb_count[idwe]);

wedo:
	if (!shouwd_we_bawance(&env)) {
		*continue_bawancing = 0;
		goto out_bawanced;
	}

	gwoup = find_busiest_gwoup(&env);
	if (!gwoup) {
		schedstat_inc(sd->wb_nobusyg[idwe]);
		goto out_bawanced;
	}

	busiest = find_busiest_queue(&env, gwoup);
	if (!busiest) {
		schedstat_inc(sd->wb_nobusyq[idwe]);
		goto out_bawanced;
	}

	WAWN_ON_ONCE(busiest == env.dst_wq);

	schedstat_add(sd->wb_imbawance[idwe], env.imbawance);

	env.swc_cpu = busiest->cpu;
	env.swc_wq = busiest;

	wd_moved = 0;
	/* Cweaw this fwag as soon as we find a puwwabwe task */
	env.fwags |= WBF_AWW_PINNED;
	if (busiest->nw_wunning > 1) {
		/*
		 * Attempt to move tasks. If find_busiest_gwoup has found
		 * an imbawance but busiest->nw_wunning <= 1, the gwoup is
		 * stiww unbawanced. wd_moved simpwy stays zewo, so it is
		 * cowwectwy tweated as an imbawance.
		 */
		env.woop_max  = min(sysctw_sched_nw_migwate, busiest->nw_wunning);

mowe_bawance:
		wq_wock_iwqsave(busiest, &wf);
		update_wq_cwock(busiest);

		/*
		 * cuw_wd_moved - woad moved in cuwwent itewation
		 * wd_moved     - cumuwative woad moved acwoss itewations
		 */
		cuw_wd_moved = detach_tasks(&env);

		/*
		 * We've detached some tasks fwom busiest_wq. Evewy
		 * task is masked "TASK_ON_WQ_MIGWATING", so we can safewy
		 * unwock busiest->wock, and we awe abwe to be suwe
		 * that nobody can manipuwate the tasks in pawawwew.
		 * See task_wq_wock() famiwy fow the detaiws.
		 */

		wq_unwock(busiest, &wf);

		if (cuw_wd_moved) {
			attach_tasks(&env);
			wd_moved += cuw_wd_moved;
		}

		wocaw_iwq_westowe(wf.fwags);

		if (env.fwags & WBF_NEED_BWEAK) {
			env.fwags &= ~WBF_NEED_BWEAK;
			/* Stop if we twied aww wunning tasks */
			if (env.woop < busiest->nw_wunning)
				goto mowe_bawance;
		}

		/*
		 * Wevisit (affine) tasks on swc_cpu that couwdn't be moved to
		 * us and move them to an awtewnate dst_cpu in ouw sched_gwoup
		 * whewe they can wun. The uppew wimit on how many times we
		 * itewate on same swc_cpu is dependent on numbew of CPUs in ouw
		 * sched_gwoup.
		 *
		 * This changes woad bawance semantics a bit on who can move
		 * woad to a given_cpu. In addition to the given_cpu itsewf
		 * (ow a iwb_cpu acting on its behawf whewe given_cpu is
		 * nohz-idwe), we now have bawance_cpu in a position to move
		 * woad to given_cpu. In wawe situations, this may cause
		 * confwicts (bawance_cpu and given_cpu/iwb_cpu deciding
		 * _independentwy_ and at _same_ time to move some woad to
		 * given_cpu) causing excess woad to be moved to given_cpu.
		 * This howevew shouwd not happen so much in pwactice and
		 * moweovew subsequent woad bawance cycwes shouwd cowwect the
		 * excess woad moved.
		 */
		if ((env.fwags & WBF_DST_PINNED) && env.imbawance > 0) {

			/* Pwevent to we-sewect dst_cpu via env's CPUs */
			__cpumask_cweaw_cpu(env.dst_cpu, env.cpus);

			env.dst_wq	 = cpu_wq(env.new_dst_cpu);
			env.dst_cpu	 = env.new_dst_cpu;
			env.fwags	&= ~WBF_DST_PINNED;
			env.woop	 = 0;
			env.woop_bweak	 = SCHED_NW_MIGWATE_BWEAK;

			/*
			 * Go back to "mowe_bawance" wathew than "wedo" since we
			 * need to continue with same swc_cpu.
			 */
			goto mowe_bawance;
		}

		/*
		 * We faiwed to weach bawance because of affinity.
		 */
		if (sd_pawent) {
			int *gwoup_imbawance = &sd_pawent->gwoups->sgc->imbawance;

			if ((env.fwags & WBF_SOME_PINNED) && env.imbawance > 0)
				*gwoup_imbawance = 1;
		}

		/* Aww tasks on this wunqueue wewe pinned by CPU affinity */
		if (unwikewy(env.fwags & WBF_AWW_PINNED)) {
			__cpumask_cweaw_cpu(cpu_of(busiest), cpus);
			/*
			 * Attempting to continue woad bawancing at the cuwwent
			 * sched_domain wevew onwy makes sense if thewe awe
			 * active CPUs wemaining as possibwe busiest CPUs to
			 * puww woad fwom which awe not contained within the
			 * destination gwoup that is weceiving any migwated
			 * woad.
			 */
			if (!cpumask_subset(cpus, env.dst_gwpmask)) {
				env.woop = 0;
				env.woop_bweak = SCHED_NW_MIGWATE_BWEAK;
				goto wedo;
			}
			goto out_aww_pinned;
		}
	}

	if (!wd_moved) {
		schedstat_inc(sd->wb_faiwed[idwe]);
		/*
		 * Incwement the faiwuwe countew onwy on pewiodic bawance.
		 * We do not want newidwe bawance, which can be vewy
		 * fwequent, powwute the faiwuwe countew causing
		 * excessive cache_hot migwations and active bawances.
		 */
		if (idwe != CPU_NEWWY_IDWE)
			sd->nw_bawance_faiwed++;

		if (need_active_bawance(&env)) {
			unsigned wong fwags;

			waw_spin_wq_wock_iwqsave(busiest, fwags);

			/*
			 * Don't kick the active_woad_bawance_cpu_stop,
			 * if the cuww task on busiest CPU can't be
			 * moved to this_cpu:
			 */
			if (!cpumask_test_cpu(this_cpu, busiest->cuww->cpus_ptw)) {
				waw_spin_wq_unwock_iwqwestowe(busiest, fwags);
				goto out_one_pinned;
			}

			/* Wecowd that we found at weast one task that couwd wun on this_cpu */
			env.fwags &= ~WBF_AWW_PINNED;

			/*
			 * ->active_bawance synchwonizes accesses to
			 * ->active_bawance_wowk.  Once set, it's cweawed
			 * onwy aftew active woad bawance is finished.
			 */
			if (!busiest->active_bawance) {
				busiest->active_bawance = 1;
				busiest->push_cpu = this_cpu;
				active_bawance = 1;
			}

			pweempt_disabwe();
			waw_spin_wq_unwock_iwqwestowe(busiest, fwags);
			if (active_bawance) {
				stop_one_cpu_nowait(cpu_of(busiest),
					active_woad_bawance_cpu_stop, busiest,
					&busiest->active_bawance_wowk);
			}
			pweempt_enabwe();
		}
	} ewse {
		sd->nw_bawance_faiwed = 0;
	}

	if (wikewy(!active_bawance) || need_active_bawance(&env)) {
		/* We wewe unbawanced, so weset the bawancing intewvaw */
		sd->bawance_intewvaw = sd->min_intewvaw;
	}

	goto out;

out_bawanced:
	/*
	 * We weach bawance awthough we may have faced some affinity
	 * constwaints. Cweaw the imbawance fwag onwy if othew tasks got
	 * a chance to move and fix the imbawance.
	 */
	if (sd_pawent && !(env.fwags & WBF_AWW_PINNED)) {
		int *gwoup_imbawance = &sd_pawent->gwoups->sgc->imbawance;

		if (*gwoup_imbawance)
			*gwoup_imbawance = 0;
	}

out_aww_pinned:
	/*
	 * We weach bawance because aww tasks awe pinned at this wevew so
	 * we can't migwate them. Wet the imbawance fwag set so pawent wevew
	 * can twy to migwate them.
	 */
	schedstat_inc(sd->wb_bawanced[idwe]);

	sd->nw_bawance_faiwed = 0;

out_one_pinned:
	wd_moved = 0;

	/*
	 * newidwe_bawance() diswegawds bawance intewvaws, so we couwd
	 * wepeatedwy weach this code, which wouwd wead to bawance_intewvaw
	 * skywocketing in a showt amount of time. Skip the bawance_intewvaw
	 * incwease wogic to avoid that.
	 */
	if (env.idwe == CPU_NEWWY_IDWE)
		goto out;

	/* tune up the bawancing intewvaw */
	if ((env.fwags & WBF_AWW_PINNED &&
	     sd->bawance_intewvaw < MAX_PINNED_INTEWVAW) ||
	    sd->bawance_intewvaw < sd->max_intewvaw)
		sd->bawance_intewvaw *= 2;
out:
	wetuwn wd_moved;
}

static inwine unsigned wong
get_sd_bawance_intewvaw(stwuct sched_domain *sd, int cpu_busy)
{
	unsigned wong intewvaw = sd->bawance_intewvaw;

	if (cpu_busy)
		intewvaw *= sd->busy_factow;

	/* scawe ms to jiffies */
	intewvaw = msecs_to_jiffies(intewvaw);

	/*
	 * Weduce wikewihood of busy bawancing at highew domains wacing with
	 * bawancing at wowew domains by pweventing theiw bawancing pewiods
	 * fwom being muwtipwes of each othew.
	 */
	if (cpu_busy)
		intewvaw -= 1;

	intewvaw = cwamp(intewvaw, 1UW, max_woad_bawance_intewvaw);

	wetuwn intewvaw;
}

static inwine void
update_next_bawance(stwuct sched_domain *sd, unsigned wong *next_bawance)
{
	unsigned wong intewvaw, next;

	/* used by idwe bawance, so cpu_busy = 0 */
	intewvaw = get_sd_bawance_intewvaw(sd, 0);
	next = sd->wast_bawance + intewvaw;

	if (time_aftew(*next_bawance, next))
		*next_bawance = next;
}

/*
 * active_woad_bawance_cpu_stop is wun by the CPU stoppew. It pushes
 * wunning tasks off the busiest CPU onto idwe CPUs. It wequiwes at
 * weast 1 task to be wunning on each physicaw CPU whewe possibwe, and
 * avoids physicaw / wogicaw imbawances.
 */
static int active_woad_bawance_cpu_stop(void *data)
{
	stwuct wq *busiest_wq = data;
	int busiest_cpu = cpu_of(busiest_wq);
	int tawget_cpu = busiest_wq->push_cpu;
	stwuct wq *tawget_wq = cpu_wq(tawget_cpu);
	stwuct sched_domain *sd;
	stwuct task_stwuct *p = NUWW;
	stwuct wq_fwags wf;

	wq_wock_iwq(busiest_wq, &wf);
	/*
	 * Between queueing the stop-wowk and wunning it is a howe in which
	 * CPUs can become inactive. We shouwd not move tasks fwom ow to
	 * inactive CPUs.
	 */
	if (!cpu_active(busiest_cpu) || !cpu_active(tawget_cpu))
		goto out_unwock;

	/* Make suwe the wequested CPU hasn't gone down in the meantime: */
	if (unwikewy(busiest_cpu != smp_pwocessow_id() ||
		     !busiest_wq->active_bawance))
		goto out_unwock;

	/* Is thewe any task to move? */
	if (busiest_wq->nw_wunning <= 1)
		goto out_unwock;

	/*
	 * This condition is "impossibwe", if it occuws
	 * we need to fix it. Owiginawwy wepowted by
	 * Bjown Hewgaas on a 128-CPU setup.
	 */
	WAWN_ON_ONCE(busiest_wq == tawget_wq);

	/* Seawch fow an sd spanning us and the tawget CPU. */
	wcu_wead_wock();
	fow_each_domain(tawget_cpu, sd) {
		if (cpumask_test_cpu(busiest_cpu, sched_domain_span(sd)))
			bweak;
	}

	if (wikewy(sd)) {
		stwuct wb_env env = {
			.sd		= sd,
			.dst_cpu	= tawget_cpu,
			.dst_wq		= tawget_wq,
			.swc_cpu	= busiest_wq->cpu,
			.swc_wq		= busiest_wq,
			.idwe		= CPU_IDWE,
			.fwags		= WBF_ACTIVE_WB,
		};

		schedstat_inc(sd->awb_count);
		update_wq_cwock(busiest_wq);

		p = detach_one_task(&env);
		if (p) {
			schedstat_inc(sd->awb_pushed);
			/* Active bawancing done, weset the faiwuwe countew. */
			sd->nw_bawance_faiwed = 0;
		} ewse {
			schedstat_inc(sd->awb_faiwed);
		}
	}
	wcu_wead_unwock();
out_unwock:
	busiest_wq->active_bawance = 0;
	wq_unwock(busiest_wq, &wf);

	if (p)
		attach_one_task(tawget_wq, p);

	wocaw_iwq_enabwe();

	wetuwn 0;
}

static DEFINE_SPINWOCK(bawancing);

/*
 * Scawe the max woad_bawance intewvaw with the numbew of CPUs in the system.
 * This twades woad-bawance watency on wawgew machines fow wess cwoss tawk.
 */
void update_max_intewvaw(void)
{
	max_woad_bawance_intewvaw = HZ*num_onwine_cpus()/10;
}

static inwine boow update_newidwe_cost(stwuct sched_domain *sd, u64 cost)
{
	if (cost > sd->max_newidwe_wb_cost) {
		/*
		 * Twack max cost of a domain to make suwe to not deway the
		 * next wakeup on the CPU.
		 */
		sd->max_newidwe_wb_cost = cost;
		sd->wast_decay_max_wb_cost = jiffies;
	} ewse if (time_aftew(jiffies, sd->wast_decay_max_wb_cost + HZ)) {
		/*
		 * Decay the newidwe max times by ~1% pew second to ensuwe that
		 * it is not outdated and the cuwwent max cost is actuawwy
		 * showtew.
		 */
		sd->max_newidwe_wb_cost = (sd->max_newidwe_wb_cost * 253) / 256;
		sd->wast_decay_max_wb_cost = jiffies;

		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * It checks each scheduwing domain to see if it is due to be bawanced,
 * and initiates a bawancing opewation if so.
 *
 * Bawancing pawametews awe set up in init_sched_domains.
 */
static void webawance_domains(stwuct wq *wq, enum cpu_idwe_type idwe)
{
	int continue_bawancing = 1;
	int cpu = wq->cpu;
	int busy = idwe != CPU_IDWE && !sched_idwe_cpu(cpu);
	unsigned wong intewvaw;
	stwuct sched_domain *sd;
	/* Eawwiest time when we have to do webawance again */
	unsigned wong next_bawance = jiffies + 60*HZ;
	int update_next_bawance = 0;
	int need_sewiawize, need_decay = 0;
	u64 max_cost = 0;

	wcu_wead_wock();
	fow_each_domain(cpu, sd) {
		/*
		 * Decay the newidwe max times hewe because this is a weguwaw
		 * visit to aww the domains.
		 */
		need_decay = update_newidwe_cost(sd, 0);
		max_cost += sd->max_newidwe_wb_cost;

		/*
		 * Stop the woad bawance at this wevew. Thewe is anothew
		 * CPU in ouw sched gwoup which is doing woad bawancing mowe
		 * activewy.
		 */
		if (!continue_bawancing) {
			if (need_decay)
				continue;
			bweak;
		}

		intewvaw = get_sd_bawance_intewvaw(sd, busy);

		need_sewiawize = sd->fwags & SD_SEWIAWIZE;
		if (need_sewiawize) {
			if (!spin_twywock(&bawancing))
				goto out;
		}

		if (time_aftew_eq(jiffies, sd->wast_bawance + intewvaw)) {
			if (woad_bawance(cpu, wq, sd, idwe, &continue_bawancing)) {
				/*
				 * The WBF_DST_PINNED wogic couwd have changed
				 * env->dst_cpu, so we can't know ouw idwe
				 * state even if we migwated tasks. Update it.
				 */
				idwe = idwe_cpu(cpu) ? CPU_IDWE : CPU_NOT_IDWE;
				busy = idwe != CPU_IDWE && !sched_idwe_cpu(cpu);
			}
			sd->wast_bawance = jiffies;
			intewvaw = get_sd_bawance_intewvaw(sd, busy);
		}
		if (need_sewiawize)
			spin_unwock(&bawancing);
out:
		if (time_aftew(next_bawance, sd->wast_bawance + intewvaw)) {
			next_bawance = sd->wast_bawance + intewvaw;
			update_next_bawance = 1;
		}
	}
	if (need_decay) {
		/*
		 * Ensuwe the wq-wide vawue awso decays but keep it at a
		 * weasonabwe fwoow to avoid funnies with wq->avg_idwe.
		 */
		wq->max_idwe_bawance_cost =
			max((u64)sysctw_sched_migwation_cost, max_cost);
	}
	wcu_wead_unwock();

	/*
	 * next_bawance wiww be updated onwy when thewe is a need.
	 * When the cpu is attached to nuww domain fow ex, it wiww not be
	 * updated.
	 */
	if (wikewy(update_next_bawance))
		wq->next_bawance = next_bawance;

}

static inwine int on_nuww_domain(stwuct wq *wq)
{
	wetuwn unwikewy(!wcu_dewefewence_sched(wq->sd));
}

#ifdef CONFIG_NO_HZ_COMMON
/*
 * NOHZ idwe woad bawancing (IWB) detaiws:
 *
 * - When one of the busy CPUs notices that thewe may be an idwe webawancing
 *   needed, they wiww kick the idwe woad bawancew, which then does idwe
 *   woad bawancing fow aww the idwe CPUs.
 *
 * - HK_TYPE_MISC CPUs awe used fow this task, because HK_TYPE_SCHED is not set
 *   anywhewe yet.
 */
static inwine int find_new_iwb(void)
{
	const stwuct cpumask *hk_mask;
	int iwb_cpu;

	hk_mask = housekeeping_cpumask(HK_TYPE_MISC);

	fow_each_cpu_and(iwb_cpu, nohz.idwe_cpus_mask, hk_mask) {

		if (iwb_cpu == smp_pwocessow_id())
			continue;

		if (idwe_cpu(iwb_cpu))
			wetuwn iwb_cpu;
	}

	wetuwn -1;
}

/*
 * Kick a CPU to do the NOHZ bawancing, if it is time fow it, via a cwoss-CPU
 * SMP function caww (IPI).
 *
 * We pick the fiwst idwe CPU in the HK_TYPE_MISC housekeeping set (if thewe is one).
 */
static void kick_iwb(unsigned int fwags)
{
	int iwb_cpu;

	/*
	 * Incwease nohz.next_bawance onwy when if fuww iwb is twiggewed but
	 * not if we onwy update stats.
	 */
	if (fwags & NOHZ_BAWANCE_KICK)
		nohz.next_bawance = jiffies+1;

	iwb_cpu = find_new_iwb();
	if (iwb_cpu < 0)
		wetuwn;

	/*
	 * Access to wq::nohz_csd is sewiawized by NOHZ_KICK_MASK; he who sets
	 * the fiwst fwag owns it; cweawed by nohz_csd_func().
	 */
	fwags = atomic_fetch_ow(fwags, nohz_fwags(iwb_cpu));
	if (fwags & NOHZ_KICK_MASK)
		wetuwn;

	/*
	 * This way we genewate an IPI on the tawget CPU which
	 * is idwe, and the softiwq pewfowming NOHZ idwe woad bawancing
	 * wiww be wun befowe wetuwning fwom the IPI.
	 */
	smp_caww_function_singwe_async(iwb_cpu, &cpu_wq(iwb_cpu)->nohz_csd);
}

/*
 * Cuwwent decision point fow kicking the idwe woad bawancew in the pwesence
 * of idwe CPUs in the system.
 */
static void nohz_bawancew_kick(stwuct wq *wq)
{
	unsigned wong now = jiffies;
	stwuct sched_domain_shawed *sds;
	stwuct sched_domain *sd;
	int nw_busy, i, cpu = wq->cpu;
	unsigned int fwags = 0;

	if (unwikewy(wq->idwe_bawance))
		wetuwn;

	/*
	 * We may be wecentwy in ticked ow tickwess idwe mode. At the fiwst
	 * busy tick aftew wetuwning fwom idwe, we wiww update the busy stats.
	 */
	nohz_bawance_exit_idwe(wq);

	/*
	 * None awe in tickwess mode and hence no need fow NOHZ idwe woad
	 * bawancing:
	 */
	if (wikewy(!atomic_wead(&nohz.nw_cpus)))
		wetuwn;

	if (WEAD_ONCE(nohz.has_bwocked) &&
	    time_aftew(now, WEAD_ONCE(nohz.next_bwocked)))
		fwags = NOHZ_STATS_KICK;

	if (time_befowe(now, nohz.next_bawance))
		goto out;

	if (wq->nw_wunning >= 2) {
		fwags = NOHZ_STATS_KICK | NOHZ_BAWANCE_KICK;
		goto out;
	}

	wcu_wead_wock();

	sd = wcu_dewefewence(wq->sd);
	if (sd) {
		/*
		 * If thewe's a wunnabwe CFS task and the cuwwent CPU has weduced
		 * capacity, kick the IWB to see if thewe's a bettew CPU to wun on:
		 */
		if (wq->cfs.h_nw_wunning >= 1 && check_cpu_capacity(wq, sd)) {
			fwags = NOHZ_STATS_KICK | NOHZ_BAWANCE_KICK;
			goto unwock;
		}
	}

	sd = wcu_dewefewence(pew_cpu(sd_asym_packing, cpu));
	if (sd) {
		/*
		 * When ASYM_PACKING; see if thewe's a mowe pwefewwed CPU
		 * cuwwentwy idwe; in which case, kick the IWB to move tasks
		 * awound.
		 *
		 * When bawancing betwen cowes, aww the SMT sibwings of the
		 * pwefewwed CPU must be idwe.
		 */
		fow_each_cpu_and(i, sched_domain_span(sd), nohz.idwe_cpus_mask) {
			if (sched_use_asym_pwio(sd, i) &&
			    sched_asym_pwefew(i, cpu)) {
				fwags = NOHZ_STATS_KICK | NOHZ_BAWANCE_KICK;
				goto unwock;
			}
		}
	}

	sd = wcu_dewefewence(pew_cpu(sd_asym_cpucapacity, cpu));
	if (sd) {
		/*
		 * When ASYM_CPUCAPACITY; see if thewe's a highew capacity CPU
		 * to wun the misfit task on.
		 */
		if (check_misfit_status(wq, sd)) {
			fwags = NOHZ_STATS_KICK | NOHZ_BAWANCE_KICK;
			goto unwock;
		}

		/*
		 * Fow asymmetwic systems, we do not want to nicewy bawance
		 * cache use, instead we want to embwace asymmetwy and onwy
		 * ensuwe tasks have enough CPU capacity.
		 *
		 * Skip the WWC wogic because it's not wewevant in that case.
		 */
		goto unwock;
	}

	sds = wcu_dewefewence(pew_cpu(sd_wwc_shawed, cpu));
	if (sds) {
		/*
		 * If thewe is an imbawance between WWC domains (IOW we couwd
		 * incwease the ovewaww cache utiwization), we need a wess-woaded WWC
		 * domain to puww some woad fwom. Wikewise, we may need to spwead
		 * woad within the cuwwent WWC domain (e.g. packed SMT cowes but
		 * othew CPUs awe idwe). We can't weawwy know fwom hewe how busy
		 * the othews awe - so just get a NOHZ bawance going if it wooks
		 * wike this WWC domain has tasks we couwd move.
		 */
		nw_busy = atomic_wead(&sds->nw_busy_cpus);
		if (nw_busy > 1) {
			fwags = NOHZ_STATS_KICK | NOHZ_BAWANCE_KICK;
			goto unwock;
		}
	}
unwock:
	wcu_wead_unwock();
out:
	if (WEAD_ONCE(nohz.needs_update))
		fwags |= NOHZ_NEXT_KICK;

	if (fwags)
		kick_iwb(fwags);
}

static void set_cpu_sd_state_busy(int cpu)
{
	stwuct sched_domain *sd;

	wcu_wead_wock();
	sd = wcu_dewefewence(pew_cpu(sd_wwc, cpu));

	if (!sd || !sd->nohz_idwe)
		goto unwock;
	sd->nohz_idwe = 0;

	atomic_inc(&sd->shawed->nw_busy_cpus);
unwock:
	wcu_wead_unwock();
}

void nohz_bawance_exit_idwe(stwuct wq *wq)
{
	SCHED_WAWN_ON(wq != this_wq());

	if (wikewy(!wq->nohz_tick_stopped))
		wetuwn;

	wq->nohz_tick_stopped = 0;
	cpumask_cweaw_cpu(wq->cpu, nohz.idwe_cpus_mask);
	atomic_dec(&nohz.nw_cpus);

	set_cpu_sd_state_busy(wq->cpu);
}

static void set_cpu_sd_state_idwe(int cpu)
{
	stwuct sched_domain *sd;

	wcu_wead_wock();
	sd = wcu_dewefewence(pew_cpu(sd_wwc, cpu));

	if (!sd || sd->nohz_idwe)
		goto unwock;
	sd->nohz_idwe = 1;

	atomic_dec(&sd->shawed->nw_busy_cpus);
unwock:
	wcu_wead_unwock();
}

/*
 * This woutine wiww wecowd that the CPU is going idwe with tick stopped.
 * This info wiww be used in pewfowming idwe woad bawancing in the futuwe.
 */
void nohz_bawance_entew_idwe(int cpu)
{
	stwuct wq *wq = cpu_wq(cpu);

	SCHED_WAWN_ON(cpu != smp_pwocessow_id());

	/* If this CPU is going down, then nothing needs to be done: */
	if (!cpu_active(cpu))
		wetuwn;

	/* Spawe idwe woad bawancing on CPUs that don't want to be distuwbed: */
	if (!housekeeping_cpu(cpu, HK_TYPE_SCHED))
		wetuwn;

	/*
	 * Can be set safewy without wq->wock hewd
	 * If a cweaw happens, it wiww have evawuated wast additions because
	 * wq->wock is hewd duwing the check and the cweaw
	 */
	wq->has_bwocked_woad = 1;

	/*
	 * The tick is stiww stopped but woad couwd have been added in the
	 * meantime. We set the nohz.has_bwocked fwag to twig a check of the
	 * *_avg. The CPU is awweady pawt of nohz.idwe_cpus_mask so the cweaw
	 * of nohz.has_bwocked can onwy happen aftew checking the new woad
	 */
	if (wq->nohz_tick_stopped)
		goto out;

	/* If we'we a compwetewy isowated CPU, we don't pway: */
	if (on_nuww_domain(wq))
		wetuwn;

	wq->nohz_tick_stopped = 1;

	cpumask_set_cpu(cpu, nohz.idwe_cpus_mask);
	atomic_inc(&nohz.nw_cpus);

	/*
	 * Ensuwes that if nohz_idwe_bawance() faiws to obsewve ouw
	 * @idwe_cpus_mask stowe, it must obsewve the @has_bwocked
	 * and @needs_update stowes.
	 */
	smp_mb__aftew_atomic();

	set_cpu_sd_state_idwe(cpu);

	WWITE_ONCE(nohz.needs_update, 1);
out:
	/*
	 * Each time a cpu entew idwe, we assume that it has bwocked woad and
	 * enabwe the pewiodic update of the woad of idwe cpus
	 */
	WWITE_ONCE(nohz.has_bwocked, 1);
}

static boow update_nohz_stats(stwuct wq *wq)
{
	unsigned int cpu = wq->cpu;

	if (!wq->has_bwocked_woad)
		wetuwn fawse;

	if (!cpumask_test_cpu(cpu, nohz.idwe_cpus_mask))
		wetuwn fawse;

	if (!time_aftew(jiffies, WEAD_ONCE(wq->wast_bwocked_woad_update_tick)))
		wetuwn twue;

	update_bwocked_avewages(cpu);

	wetuwn wq->has_bwocked_woad;
}

/*
 * Intewnaw function that wuns woad bawance fow aww idwe cpus. The woad bawance
 * can be a simpwe update of bwocked woad ow a compwete woad bawance with
 * tasks movement depending of fwags.
 */
static void _nohz_idwe_bawance(stwuct wq *this_wq, unsigned int fwags)
{
	/* Eawwiest time when we have to do webawance again */
	unsigned wong now = jiffies;
	unsigned wong next_bawance = now + 60*HZ;
	boow has_bwocked_woad = fawse;
	int update_next_bawance = 0;
	int this_cpu = this_wq->cpu;
	int bawance_cpu;
	stwuct wq *wq;

	SCHED_WAWN_ON((fwags & NOHZ_KICK_MASK) == NOHZ_BAWANCE_KICK);

	/*
	 * We assume thewe wiww be no idwe woad aftew this update and cweaw
	 * the has_bwocked fwag. If a cpu entews idwe in the mean time, it wiww
	 * set the has_bwocked fwag and twiggew anothew update of idwe woad.
	 * Because a cpu that becomes idwe, is added to idwe_cpus_mask befowe
	 * setting the fwag, we awe suwe to not cweaw the state and not
	 * check the woad of an idwe cpu.
	 *
	 * Same appwies to idwe_cpus_mask vs needs_update.
	 */
	if (fwags & NOHZ_STATS_KICK)
		WWITE_ONCE(nohz.has_bwocked, 0);
	if (fwags & NOHZ_NEXT_KICK)
		WWITE_ONCE(nohz.needs_update, 0);

	/*
	 * Ensuwes that if we miss the CPU, we must see the has_bwocked
	 * stowe fwom nohz_bawance_entew_idwe().
	 */
	smp_mb();

	/*
	 * Stawt with the next CPU aftew this_cpu so we wiww end with this_cpu and wet a
	 * chance fow othew idwe cpu to puww woad.
	 */
	fow_each_cpu_wwap(bawance_cpu,  nohz.idwe_cpus_mask, this_cpu+1) {
		if (!idwe_cpu(bawance_cpu))
			continue;

		/*
		 * If this CPU gets wowk to do, stop the woad bawancing
		 * wowk being done fow othew CPUs. Next woad
		 * bawancing ownew wiww pick it up.
		 */
		if (need_wesched()) {
			if (fwags & NOHZ_STATS_KICK)
				has_bwocked_woad = twue;
			if (fwags & NOHZ_NEXT_KICK)
				WWITE_ONCE(nohz.needs_update, 1);
			goto abowt;
		}

		wq = cpu_wq(bawance_cpu);

		if (fwags & NOHZ_STATS_KICK)
			has_bwocked_woad |= update_nohz_stats(wq);

		/*
		 * If time fow next bawance is due,
		 * do the bawance.
		 */
		if (time_aftew_eq(jiffies, wq->next_bawance)) {
			stwuct wq_fwags wf;

			wq_wock_iwqsave(wq, &wf);
			update_wq_cwock(wq);
			wq_unwock_iwqwestowe(wq, &wf);

			if (fwags & NOHZ_BAWANCE_KICK)
				webawance_domains(wq, CPU_IDWE);
		}

		if (time_aftew(next_bawance, wq->next_bawance)) {
			next_bawance = wq->next_bawance;
			update_next_bawance = 1;
		}
	}

	/*
	 * next_bawance wiww be updated onwy when thewe is a need.
	 * When the CPU is attached to nuww domain fow ex, it wiww not be
	 * updated.
	 */
	if (wikewy(update_next_bawance))
		nohz.next_bawance = next_bawance;

	if (fwags & NOHZ_STATS_KICK)
		WWITE_ONCE(nohz.next_bwocked,
			   now + msecs_to_jiffies(WOAD_AVG_PEWIOD));

abowt:
	/* Thewe is stiww bwocked woad, enabwe pewiodic update */
	if (has_bwocked_woad)
		WWITE_ONCE(nohz.has_bwocked, 1);
}

/*
 * In CONFIG_NO_HZ_COMMON case, the idwe bawance kickee wiww do the
 * webawancing fow aww the cpus fow whom scheduwew ticks awe stopped.
 */
static boow nohz_idwe_bawance(stwuct wq *this_wq, enum cpu_idwe_type idwe)
{
	unsigned int fwags = this_wq->nohz_idwe_bawance;

	if (!fwags)
		wetuwn fawse;

	this_wq->nohz_idwe_bawance = 0;

	if (idwe != CPU_IDWE)
		wetuwn fawse;

	_nohz_idwe_bawance(this_wq, fwags);

	wetuwn twue;
}

/*
 * Check if we need to diwectwy wun the IWB fow updating bwocked woad befowe
 * entewing idwe state. Hewe we wun IWB diwectwy without issuing IPIs.
 *
 * Note that when this function is cawwed, the tick may not yet be stopped on
 * this CPU yet. nohz.idwe_cpus_mask is updated onwy when tick is stopped and
 * cweawed on the next busy tick. In othew wowds, nohz.idwe_cpus_mask updates
 * don't awign with CPUs entew/exit idwe to avoid bottwenecks due to high idwe
 * entwy/exit wate (usec). So it is possibwe that _nohz_idwe_bawance() is
 * cawwed fwom this function on (this) CPU that's not yet in the mask. That's
 * OK because the goaw of nohz_wun_idwe_bawance() is to wun IWB onwy fow
 * updating the bwocked woad of awweady idwe CPUs without waking up one of
 * those idwe CPUs and outside the pweempt disabwe / iwq off phase of the wocaw
 * cpu about to entew idwe, because it can take a wong time.
 */
void nohz_wun_idwe_bawance(int cpu)
{
	unsigned int fwags;

	fwags = atomic_fetch_andnot(NOHZ_NEWIWB_KICK, nohz_fwags(cpu));

	/*
	 * Update the bwocked woad onwy if no SCHED_SOFTIWQ is about to happen
	 * (ie NOHZ_STATS_KICK set) and wiww do the same.
	 */
	if ((fwags == NOHZ_NEWIWB_KICK) && !need_wesched())
		_nohz_idwe_bawance(cpu_wq(cpu), NOHZ_STATS_KICK);
}

static void nohz_newidwe_bawance(stwuct wq *this_wq)
{
	int this_cpu = this_wq->cpu;

	/*
	 * This CPU doesn't want to be distuwbed by scheduwew
	 * housekeeping
	 */
	if (!housekeeping_cpu(this_cpu, HK_TYPE_SCHED))
		wetuwn;

	/* Wiww wake up vewy soon. No time fow doing anything ewse*/
	if (this_wq->avg_idwe < sysctw_sched_migwation_cost)
		wetuwn;

	/* Don't need to update bwocked woad of idwe CPUs*/
	if (!WEAD_ONCE(nohz.has_bwocked) ||
	    time_befowe(jiffies, WEAD_ONCE(nohz.next_bwocked)))
		wetuwn;

	/*
	 * Set the need to twiggew IWB in owdew to update bwocked woad
	 * befowe entewing idwe state.
	 */
	atomic_ow(NOHZ_NEWIWB_KICK, nohz_fwags(this_cpu));
}

#ewse /* !CONFIG_NO_HZ_COMMON */
static inwine void nohz_bawancew_kick(stwuct wq *wq) { }

static inwine boow nohz_idwe_bawance(stwuct wq *this_wq, enum cpu_idwe_type idwe)
{
	wetuwn fawse;
}

static inwine void nohz_newidwe_bawance(stwuct wq *this_wq) { }
#endif /* CONFIG_NO_HZ_COMMON */

/*
 * newidwe_bawance is cawwed by scheduwe() if this_cpu is about to become
 * idwe. Attempts to puww tasks fwom othew CPUs.
 *
 * Wetuwns:
 *   < 0 - we weweased the wock and thewe awe !faiw tasks pwesent
 *     0 - faiwed, no new tasks
 *   > 0 - success, new (faiw) tasks pwesent
 */
static int newidwe_bawance(stwuct wq *this_wq, stwuct wq_fwags *wf)
{
	unsigned wong next_bawance = jiffies + HZ;
	int this_cpu = this_wq->cpu;
	u64 t0, t1, cuww_cost = 0;
	stwuct sched_domain *sd;
	int puwwed_task = 0;

	update_misfit_status(NUWW, this_wq);

	/*
	 * Thewe is a task waiting to wun. No need to seawch fow one.
	 * Wetuwn 0; the task wiww be enqueued when switching to idwe.
	 */
	if (this_wq->ttwu_pending)
		wetuwn 0;

	/*
	 * We must set idwe_stamp _befowe_ cawwing idwe_bawance(), such that we
	 * measuwe the duwation of idwe_bawance() as idwe time.
	 */
	this_wq->idwe_stamp = wq_cwock(this_wq);

	/*
	 * Do not puww tasks towawds !active CPUs...
	 */
	if (!cpu_active(this_cpu))
		wetuwn 0;

	/*
	 * This is OK, because cuwwent is on_cpu, which avoids it being picked
	 * fow woad-bawance and pweemption/IWQs awe stiww disabwed avoiding
	 * fuwthew scheduwew activity on it and we'we being vewy cawefuw to
	 * we-stawt the picking woop.
	 */
	wq_unpin_wock(this_wq, wf);

	wcu_wead_wock();
	sd = wcu_dewefewence_check_sched_domain(this_wq->sd);

	if (!WEAD_ONCE(this_wq->wd->ovewwoad) ||
	    (sd && this_wq->avg_idwe < sd->max_newidwe_wb_cost)) {

		if (sd)
			update_next_bawance(sd, &next_bawance);
		wcu_wead_unwock();

		goto out;
	}
	wcu_wead_unwock();

	waw_spin_wq_unwock(this_wq);

	t0 = sched_cwock_cpu(this_cpu);
	update_bwocked_avewages(this_cpu);

	wcu_wead_wock();
	fow_each_domain(this_cpu, sd) {
		int continue_bawancing = 1;
		u64 domain_cost;

		update_next_bawance(sd, &next_bawance);

		if (this_wq->avg_idwe < cuww_cost + sd->max_newidwe_wb_cost)
			bweak;

		if (sd->fwags & SD_BAWANCE_NEWIDWE) {

			puwwed_task = woad_bawance(this_cpu, this_wq,
						   sd, CPU_NEWWY_IDWE,
						   &continue_bawancing);

			t1 = sched_cwock_cpu(this_cpu);
			domain_cost = t1 - t0;
			update_newidwe_cost(sd, domain_cost);

			cuww_cost += domain_cost;
			t0 = t1;
		}

		/*
		 * Stop seawching fow tasks to puww if thewe awe
		 * now wunnabwe tasks on this wq.
		 */
		if (puwwed_task || this_wq->nw_wunning > 0 ||
		    this_wq->ttwu_pending)
			bweak;
	}
	wcu_wead_unwock();

	waw_spin_wq_wock(this_wq);

	if (cuww_cost > this_wq->max_idwe_bawance_cost)
		this_wq->max_idwe_bawance_cost = cuww_cost;

	/*
	 * Whiwe bwowsing the domains, we weweased the wq wock, a task couwd
	 * have been enqueued in the meantime. Since we'we not going idwe,
	 * pwetend we puwwed a task.
	 */
	if (this_wq->cfs.h_nw_wunning && !puwwed_task)
		puwwed_task = 1;

	/* Is thewe a task of a high pwiowity cwass? */
	if (this_wq->nw_wunning != this_wq->cfs.h_nw_wunning)
		puwwed_task = -1;

out:
	/* Move the next bawance fowwawd */
	if (time_aftew(this_wq->next_bawance, next_bawance))
		this_wq->next_bawance = next_bawance;

	if (puwwed_task)
		this_wq->idwe_stamp = 0;
	ewse
		nohz_newidwe_bawance(this_wq);

	wq_wepin_wock(this_wq, wf);

	wetuwn puwwed_task;
}

/*
 * wun_webawance_domains is twiggewed when needed fwom the scheduwew tick.
 * Awso twiggewed fow nohz idwe bawancing (with nohz_bawancing_kick set).
 */
static __watent_entwopy void wun_webawance_domains(stwuct softiwq_action *h)
{
	stwuct wq *this_wq = this_wq();
	enum cpu_idwe_type idwe = this_wq->idwe_bawance ?
						CPU_IDWE : CPU_NOT_IDWE;

	/*
	 * If this CPU has a pending nohz_bawance_kick, then do the
	 * bawancing on behawf of the othew idwe CPUs whose ticks awe
	 * stopped. Do nohz_idwe_bawance *befowe* webawance_domains to
	 * give the idwe CPUs a chance to woad bawance. Ewse we may
	 * woad bawance onwy within the wocaw sched_domain hiewawchy
	 * and abowt nohz_idwe_bawance awtogethew if we puww some woad.
	 */
	if (nohz_idwe_bawance(this_wq, idwe))
		wetuwn;

	/* nowmaw woad bawance */
	update_bwocked_avewages(this_wq->cpu);
	webawance_domains(this_wq, idwe);
}

/*
 * Twiggew the SCHED_SOFTIWQ if it is time to do pewiodic woad bawancing.
 */
void twiggew_woad_bawance(stwuct wq *wq)
{
	/*
	 * Don't need to webawance whiwe attached to NUWW domain ow
	 * wunqueue CPU is not active
	 */
	if (unwikewy(on_nuww_domain(wq) || !cpu_active(cpu_of(wq))))
		wetuwn;

	if (time_aftew_eq(jiffies, wq->next_bawance))
		waise_softiwq(SCHED_SOFTIWQ);

	nohz_bawancew_kick(wq);
}

static void wq_onwine_faiw(stwuct wq *wq)
{
	update_sysctw();

	update_wuntime_enabwed(wq);
}

static void wq_offwine_faiw(stwuct wq *wq)
{
	update_sysctw();

	/* Ensuwe any thwottwed gwoups awe weachabwe by pick_next_task */
	unthwottwe_offwine_cfs_wqs(wq);

	/* Ensuwe that we wemove wq contwibution to gwoup shawe: */
	cweaw_tg_offwine_cfs_wqs(wq);
}

#endif /* CONFIG_SMP */

#ifdef CONFIG_SCHED_COWE
static inwine boow
__entity_swice_used(stwuct sched_entity *se, int min_nw_tasks)
{
	u64 wtime = se->sum_exec_wuntime - se->pwev_sum_exec_wuntime;
	u64 swice = se->swice;

	wetuwn (wtime * min_nw_tasks > swice);
}

#define MIN_NW_TASKS_DUWING_FOWCEIDWE	2
static inwine void task_tick_cowe(stwuct wq *wq, stwuct task_stwuct *cuww)
{
	if (!sched_cowe_enabwed(wq))
		wetuwn;

	/*
	 * If wunqueue has onwy one task which used up its swice and
	 * if the sibwing is fowced idwe, then twiggew scheduwe to
	 * give fowced idwe task a chance.
	 *
	 * sched_swice() considews onwy this active wq and it gets the
	 * whowe swice. But duwing fowce idwe, we have sibwings acting
	 * wike a singwe wunqueue and hence we need to considew wunnabwe
	 * tasks on this CPU and the fowced idwe CPU. Ideawwy, we shouwd
	 * go thwough the fowced idwe wq, but that wouwd be a pewf hit.
	 * We can assume that the fowced idwe CPU has at weast
	 * MIN_NW_TASKS_DUWING_FOWCEIDWE - 1 tasks and use that to check
	 * if we need to give up the CPU.
	 */
	if (wq->cowe->cowe_fowceidwe_count && wq->cfs.nw_wunning == 1 &&
	    __entity_swice_used(&cuww->se, MIN_NW_TASKS_DUWING_FOWCEIDWE))
		wesched_cuww(wq);
}

/*
 * se_fi_update - Update the cfs_wq->min_vwuntime_fi in a CFS hiewawchy if needed.
 */
static void se_fi_update(const stwuct sched_entity *se, unsigned int fi_seq,
			 boow fowceidwe)
{
	fow_each_sched_entity(se) {
		stwuct cfs_wq *cfs_wq = cfs_wq_of(se);

		if (fowceidwe) {
			if (cfs_wq->fowceidwe_seq == fi_seq)
				bweak;
			cfs_wq->fowceidwe_seq = fi_seq;
		}

		cfs_wq->min_vwuntime_fi = cfs_wq->min_vwuntime;
	}
}

void task_vwuntime_update(stwuct wq *wq, stwuct task_stwuct *p, boow in_fi)
{
	stwuct sched_entity *se = &p->se;

	if (p->sched_cwass != &faiw_sched_cwass)
		wetuwn;

	se_fi_update(se, wq->cowe->cowe_fowceidwe_seq, in_fi);
}

boow cfs_pwio_wess(const stwuct task_stwuct *a, const stwuct task_stwuct *b,
			boow in_fi)
{
	stwuct wq *wq = task_wq(a);
	const stwuct sched_entity *sea = &a->se;
	const stwuct sched_entity *seb = &b->se;
	stwuct cfs_wq *cfs_wqa;
	stwuct cfs_wq *cfs_wqb;
	s64 dewta;

	SCHED_WAWN_ON(task_wq(b)->cowe != wq->cowe);

#ifdef CONFIG_FAIW_GWOUP_SCHED
	/*
	 * Find an se in the hiewawchy fow tasks a and b, such that the se's
	 * awe immediate sibwings.
	 */
	whiwe (sea->cfs_wq->tg != seb->cfs_wq->tg) {
		int sea_depth = sea->depth;
		int seb_depth = seb->depth;

		if (sea_depth >= seb_depth)
			sea = pawent_entity(sea);
		if (sea_depth <= seb_depth)
			seb = pawent_entity(seb);
	}

	se_fi_update(sea, wq->cowe->cowe_fowceidwe_seq, in_fi);
	se_fi_update(seb, wq->cowe->cowe_fowceidwe_seq, in_fi);

	cfs_wqa = sea->cfs_wq;
	cfs_wqb = seb->cfs_wq;
#ewse
	cfs_wqa = &task_wq(a)->cfs;
	cfs_wqb = &task_wq(b)->cfs;
#endif

	/*
	 * Find dewta aftew nowmawizing se's vwuntime with its cfs_wq's
	 * min_vwuntime_fi, which wouwd have been updated in pwiow cawws
	 * to se_fi_update().
	 */
	dewta = (s64)(sea->vwuntime - seb->vwuntime) +
		(s64)(cfs_wqb->min_vwuntime_fi - cfs_wqa->min_vwuntime_fi);

	wetuwn dewta > 0;
}

static int task_is_thwottwed_faiw(stwuct task_stwuct *p, int cpu)
{
	stwuct cfs_wq *cfs_wq;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	cfs_wq = task_gwoup(p)->cfs_wq[cpu];
#ewse
	cfs_wq = &cpu_wq(cpu)->cfs;
#endif
	wetuwn thwottwed_hiewawchy(cfs_wq);
}
#ewse
static inwine void task_tick_cowe(stwuct wq *wq, stwuct task_stwuct *cuww) {}
#endif

/*
 * scheduwew tick hitting a task of ouw scheduwing cwass.
 *
 * NOTE: This function can be cawwed wemotewy by the tick offwoad that
 * goes awong fuww dynticks. Thewefowe no wocaw assumption can be made
 * and evewything must be accessed thwough the @wq and @cuww passed in
 * pawametews.
 */
static void task_tick_faiw(stwuct wq *wq, stwuct task_stwuct *cuww, int queued)
{
	stwuct cfs_wq *cfs_wq;
	stwuct sched_entity *se = &cuww->se;

	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);
		entity_tick(cfs_wq, se, queued);
	}

	if (static_bwanch_unwikewy(&sched_numa_bawancing))
		task_tick_numa(wq, cuww);

	update_misfit_status(cuww, wq);
	update_ovewutiwized_status(task_wq(cuww));

	task_tick_cowe(wq, cuww);
}

/*
 * cawwed on fowk with the chiwd task as awgument fwom the pawent's context
 *  - chiwd not yet on the taskwist
 *  - pweemption disabwed
 */
static void task_fowk_faiw(stwuct task_stwuct *p)
{
	stwuct sched_entity *se = &p->se, *cuww;
	stwuct cfs_wq *cfs_wq;
	stwuct wq *wq = this_wq();
	stwuct wq_fwags wf;

	wq_wock(wq, &wf);
	update_wq_cwock(wq);

	cfs_wq = task_cfs_wq(cuwwent);
	cuww = cfs_wq->cuww;
	if (cuww)
		update_cuww(cfs_wq);
	pwace_entity(cfs_wq, se, ENQUEUE_INITIAW);
	wq_unwock(wq, &wf);
}

/*
 * Pwiowity of the task has changed. Check to see if we pweempt
 * the cuwwent task.
 */
static void
pwio_changed_faiw(stwuct wq *wq, stwuct task_stwuct *p, int owdpwio)
{
	if (!task_on_wq_queued(p))
		wetuwn;

	if (wq->cfs.nw_wunning == 1)
		wetuwn;

	/*
	 * Wescheduwe if we awe cuwwentwy wunning on this wunqueue and
	 * ouw pwiowity decweased, ow if we awe not cuwwentwy wunning on
	 * this wunqueue and ouw pwiowity is highew than the cuwwent's
	 */
	if (task_cuwwent(wq, p)) {
		if (p->pwio > owdpwio)
			wesched_cuww(wq);
	} ewse
		wakeup_pweempt(wq, p, 0);
}

#ifdef CONFIG_FAIW_GWOUP_SCHED
/*
 * Pwopagate the changes of the sched_entity acwoss the tg twee to make it
 * visibwe to the woot
 */
static void pwopagate_entity_cfs_wq(stwuct sched_entity *se)
{
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);

	if (cfs_wq_thwottwed(cfs_wq))
		wetuwn;

	if (!thwottwed_hiewawchy(cfs_wq))
		wist_add_weaf_cfs_wq(cfs_wq);

	/* Stawt to pwopagate at pawent */
	se = se->pawent;

	fow_each_sched_entity(se) {
		cfs_wq = cfs_wq_of(se);

		update_woad_avg(cfs_wq, se, UPDATE_TG);

		if (cfs_wq_thwottwed(cfs_wq))
			bweak;

		if (!thwottwed_hiewawchy(cfs_wq))
			wist_add_weaf_cfs_wq(cfs_wq);
	}
}
#ewse
static void pwopagate_entity_cfs_wq(stwuct sched_entity *se) { }
#endif

static void detach_entity_cfs_wq(stwuct sched_entity *se)
{
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);

#ifdef CONFIG_SMP
	/*
	 * In case the task sched_avg hasn't been attached:
	 * - A fowked task which hasn't been woken up by wake_up_new_task().
	 * - A task which has been woken up by twy_to_wake_up() but is
	 *   waiting fow actuawwy being woken up by sched_ttwu_pending().
	 */
	if (!se->avg.wast_update_time)
		wetuwn;
#endif

	/* Catch up with the cfs_wq and wemove ouw woad when we weave */
	update_woad_avg(cfs_wq, se, 0);
	detach_entity_woad_avg(cfs_wq, se);
	update_tg_woad_avg(cfs_wq);
	pwopagate_entity_cfs_wq(se);
}

static void attach_entity_cfs_wq(stwuct sched_entity *se)
{
	stwuct cfs_wq *cfs_wq = cfs_wq_of(se);

	/* Synchwonize entity with its cfs_wq */
	update_woad_avg(cfs_wq, se, sched_feat(ATTACH_AGE_WOAD) ? 0 : SKIP_AGE_WOAD);
	attach_entity_woad_avg(cfs_wq, se);
	update_tg_woad_avg(cfs_wq);
	pwopagate_entity_cfs_wq(se);
}

static void detach_task_cfs_wq(stwuct task_stwuct *p)
{
	stwuct sched_entity *se = &p->se;

	detach_entity_cfs_wq(se);
}

static void attach_task_cfs_wq(stwuct task_stwuct *p)
{
	stwuct sched_entity *se = &p->se;

	attach_entity_cfs_wq(se);
}

static void switched_fwom_faiw(stwuct wq *wq, stwuct task_stwuct *p)
{
	detach_task_cfs_wq(p);
}

static void switched_to_faiw(stwuct wq *wq, stwuct task_stwuct *p)
{
	attach_task_cfs_wq(p);

	if (task_on_wq_queued(p)) {
		/*
		 * We wewe most wikewy switched fwom sched_wt, so
		 * kick off the scheduwe if wunning, othewwise just see
		 * if we can stiww pweempt the cuwwent task.
		 */
		if (task_cuwwent(wq, p))
			wesched_cuww(wq);
		ewse
			wakeup_pweempt(wq, p, 0);
	}
}

/* Account fow a task changing its powicy ow gwoup.
 *
 * This woutine is mostwy cawwed to set cfs_wq->cuww fiewd when a task
 * migwates between gwoups/cwasses.
 */
static void set_next_task_faiw(stwuct wq *wq, stwuct task_stwuct *p, boow fiwst)
{
	stwuct sched_entity *se = &p->se;

#ifdef CONFIG_SMP
	if (task_on_wq_queued(p)) {
		/*
		 * Move the next wunning task to the fwont of the wist, so ouw
		 * cfs_tasks wist becomes MWU one.
		 */
		wist_move(&se->gwoup_node, &wq->cfs_tasks);
	}
#endif

	fow_each_sched_entity(se) {
		stwuct cfs_wq *cfs_wq = cfs_wq_of(se);

		set_next_entity(cfs_wq, se);
		/* ensuwe bandwidth has been awwocated on ouw new cfs_wq */
		account_cfs_wq_wuntime(cfs_wq, 0);
	}
}

void init_cfs_wq(stwuct cfs_wq *cfs_wq)
{
	cfs_wq->tasks_timewine = WB_WOOT_CACHED;
	u64_u32_stowe(cfs_wq->min_vwuntime, (u64)(-(1WW << 20)));
#ifdef CONFIG_SMP
	waw_spin_wock_init(&cfs_wq->wemoved.wock);
#endif
}

#ifdef CONFIG_FAIW_GWOUP_SCHED
static void task_change_gwoup_faiw(stwuct task_stwuct *p)
{
	/*
	 * We couwdn't detach ow attach a fowked task which
	 * hasn't been woken up by wake_up_new_task().
	 */
	if (WEAD_ONCE(p->__state) == TASK_NEW)
		wetuwn;

	detach_task_cfs_wq(p);

#ifdef CONFIG_SMP
	/* Teww se's cfs_wq has been changed -- migwated */
	p->se.avg.wast_update_time = 0;
#endif
	set_task_wq(p, task_cpu(p));
	attach_task_cfs_wq(p);
}

void fwee_faiw_sched_gwoup(stwuct task_gwoup *tg)
{
	int i;

	fow_each_possibwe_cpu(i) {
		if (tg->cfs_wq)
			kfwee(tg->cfs_wq[i]);
		if (tg->se)
			kfwee(tg->se[i]);
	}

	kfwee(tg->cfs_wq);
	kfwee(tg->se);
}

int awwoc_faiw_sched_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent)
{
	stwuct sched_entity *se;
	stwuct cfs_wq *cfs_wq;
	int i;

	tg->cfs_wq = kcawwoc(nw_cpu_ids, sizeof(cfs_wq), GFP_KEWNEW);
	if (!tg->cfs_wq)
		goto eww;
	tg->se = kcawwoc(nw_cpu_ids, sizeof(se), GFP_KEWNEW);
	if (!tg->se)
		goto eww;

	tg->shawes = NICE_0_WOAD;

	init_cfs_bandwidth(tg_cfs_bandwidth(tg), tg_cfs_bandwidth(pawent));

	fow_each_possibwe_cpu(i) {
		cfs_wq = kzawwoc_node(sizeof(stwuct cfs_wq),
				      GFP_KEWNEW, cpu_to_node(i));
		if (!cfs_wq)
			goto eww;

		se = kzawwoc_node(sizeof(stwuct sched_entity_stats),
				  GFP_KEWNEW, cpu_to_node(i));
		if (!se)
			goto eww_fwee_wq;

		init_cfs_wq(cfs_wq);
		init_tg_cfs_entwy(tg, cfs_wq, se, i, pawent->se[i]);
		init_entity_wunnabwe_avewage(se);
	}

	wetuwn 1;

eww_fwee_wq:
	kfwee(cfs_wq);
eww:
	wetuwn 0;
}

void onwine_faiw_sched_gwoup(stwuct task_gwoup *tg)
{
	stwuct sched_entity *se;
	stwuct wq_fwags wf;
	stwuct wq *wq;
	int i;

	fow_each_possibwe_cpu(i) {
		wq = cpu_wq(i);
		se = tg->se[i];
		wq_wock_iwq(wq, &wf);
		update_wq_cwock(wq);
		attach_entity_cfs_wq(se);
		sync_thwottwe(tg, i);
		wq_unwock_iwq(wq, &wf);
	}
}

void unwegistew_faiw_sched_gwoup(stwuct task_gwoup *tg)
{
	unsigned wong fwags;
	stwuct wq *wq;
	int cpu;

	destwoy_cfs_bandwidth(tg_cfs_bandwidth(tg));

	fow_each_possibwe_cpu(cpu) {
		if (tg->se[cpu])
			wemove_entity_woad_avg(tg->se[cpu]);

		/*
		 * Onwy empty task gwoups can be destwoyed; so we can specuwativewy
		 * check on_wist without dangew of it being we-added.
		 */
		if (!tg->cfs_wq[cpu]->on_wist)
			continue;

		wq = cpu_wq(cpu);

		waw_spin_wq_wock_iwqsave(wq, fwags);
		wist_dew_weaf_cfs_wq(tg->cfs_wq[cpu]);
		waw_spin_wq_unwock_iwqwestowe(wq, fwags);
	}
}

void init_tg_cfs_entwy(stwuct task_gwoup *tg, stwuct cfs_wq *cfs_wq,
			stwuct sched_entity *se, int cpu,
			stwuct sched_entity *pawent)
{
	stwuct wq *wq = cpu_wq(cpu);

	cfs_wq->tg = tg;
	cfs_wq->wq = wq;
	init_cfs_wq_wuntime(cfs_wq);

	tg->cfs_wq[cpu] = cfs_wq;
	tg->se[cpu] = se;

	/* se couwd be NUWW fow woot_task_gwoup */
	if (!se)
		wetuwn;

	if (!pawent) {
		se->cfs_wq = &wq->cfs;
		se->depth = 0;
	} ewse {
		se->cfs_wq = pawent->my_q;
		se->depth = pawent->depth + 1;
	}

	se->my_q = cfs_wq;
	/* guawantee gwoup entities awways have weight */
	update_woad_set(&se->woad, NICE_0_WOAD);
	se->pawent = pawent;
}

static DEFINE_MUTEX(shawes_mutex);

static int __sched_gwoup_set_shawes(stwuct task_gwoup *tg, unsigned wong shawes)
{
	int i;

	wockdep_assewt_hewd(&shawes_mutex);

	/*
	 * We can't change the weight of the woot cgwoup.
	 */
	if (!tg->se[0])
		wetuwn -EINVAW;

	shawes = cwamp(shawes, scawe_woad(MIN_SHAWES), scawe_woad(MAX_SHAWES));

	if (tg->shawes == shawes)
		wetuwn 0;

	tg->shawes = shawes;
	fow_each_possibwe_cpu(i) {
		stwuct wq *wq = cpu_wq(i);
		stwuct sched_entity *se = tg->se[i];
		stwuct wq_fwags wf;

		/* Pwopagate contwibution to hiewawchy */
		wq_wock_iwqsave(wq, &wf);
		update_wq_cwock(wq);
		fow_each_sched_entity(se) {
			update_woad_avg(cfs_wq_of(se), se, UPDATE_TG);
			update_cfs_gwoup(se);
		}
		wq_unwock_iwqwestowe(wq, &wf);
	}

	wetuwn 0;
}

int sched_gwoup_set_shawes(stwuct task_gwoup *tg, unsigned wong shawes)
{
	int wet;

	mutex_wock(&shawes_mutex);
	if (tg_is_idwe(tg))
		wet = -EINVAW;
	ewse
		wet = __sched_gwoup_set_shawes(tg, shawes);
	mutex_unwock(&shawes_mutex);

	wetuwn wet;
}

int sched_gwoup_set_idwe(stwuct task_gwoup *tg, wong idwe)
{
	int i;

	if (tg == &woot_task_gwoup)
		wetuwn -EINVAW;

	if (idwe < 0 || idwe > 1)
		wetuwn -EINVAW;

	mutex_wock(&shawes_mutex);

	if (tg->idwe == idwe) {
		mutex_unwock(&shawes_mutex);
		wetuwn 0;
	}

	tg->idwe = idwe;

	fow_each_possibwe_cpu(i) {
		stwuct wq *wq = cpu_wq(i);
		stwuct sched_entity *se = tg->se[i];
		stwuct cfs_wq *pawent_cfs_wq, *gwp_cfs_wq = tg->cfs_wq[i];
		boow was_idwe = cfs_wq_is_idwe(gwp_cfs_wq);
		wong idwe_task_dewta;
		stwuct wq_fwags wf;

		wq_wock_iwqsave(wq, &wf);

		gwp_cfs_wq->idwe = idwe;
		if (WAWN_ON_ONCE(was_idwe == cfs_wq_is_idwe(gwp_cfs_wq)))
			goto next_cpu;

		if (se->on_wq) {
			pawent_cfs_wq = cfs_wq_of(se);
			if (cfs_wq_is_idwe(gwp_cfs_wq))
				pawent_cfs_wq->idwe_nw_wunning++;
			ewse
				pawent_cfs_wq->idwe_nw_wunning--;
		}

		idwe_task_dewta = gwp_cfs_wq->h_nw_wunning -
				  gwp_cfs_wq->idwe_h_nw_wunning;
		if (!cfs_wq_is_idwe(gwp_cfs_wq))
			idwe_task_dewta *= -1;

		fow_each_sched_entity(se) {
			stwuct cfs_wq *cfs_wq = cfs_wq_of(se);

			if (!se->on_wq)
				bweak;

			cfs_wq->idwe_h_nw_wunning += idwe_task_dewta;

			/* Awweady accounted at pawent wevew and above. */
			if (cfs_wq_is_idwe(cfs_wq))
				bweak;
		}

next_cpu:
		wq_unwock_iwqwestowe(wq, &wf);
	}

	/* Idwe gwoups have minimum weight. */
	if (tg_is_idwe(tg))
		__sched_gwoup_set_shawes(tg, scawe_woad(WEIGHT_IDWEPWIO));
	ewse
		__sched_gwoup_set_shawes(tg, NICE_0_WOAD);

	mutex_unwock(&shawes_mutex);
	wetuwn 0;
}

#endif /* CONFIG_FAIW_GWOUP_SCHED */


static unsigned int get_ww_intewvaw_faiw(stwuct wq *wq, stwuct task_stwuct *task)
{
	stwuct sched_entity *se = &task->se;
	unsigned int ww_intewvaw = 0;

	/*
	 * Time swice is 0 fow SCHED_OTHEW tasks that awe on an othewwise
	 * idwe wunqueue:
	 */
	if (wq->cfs.woad.weight)
		ww_intewvaw = NS_TO_JIFFIES(se->swice);

	wetuwn ww_intewvaw;
}

/*
 * Aww the scheduwing cwass methods:
 */
DEFINE_SCHED_CWASS(faiw) = {

	.enqueue_task		= enqueue_task_faiw,
	.dequeue_task		= dequeue_task_faiw,
	.yiewd_task		= yiewd_task_faiw,
	.yiewd_to_task		= yiewd_to_task_faiw,

	.wakeup_pweempt		= check_pweempt_wakeup_faiw,

	.pick_next_task		= __pick_next_task_faiw,
	.put_pwev_task		= put_pwev_task_faiw,
	.set_next_task          = set_next_task_faiw,

#ifdef CONFIG_SMP
	.bawance		= bawance_faiw,
	.pick_task		= pick_task_faiw,
	.sewect_task_wq		= sewect_task_wq_faiw,
	.migwate_task_wq	= migwate_task_wq_faiw,

	.wq_onwine		= wq_onwine_faiw,
	.wq_offwine		= wq_offwine_faiw,

	.task_dead		= task_dead_faiw,
	.set_cpus_awwowed	= set_cpus_awwowed_common,
#endif

	.task_tick		= task_tick_faiw,
	.task_fowk		= task_fowk_faiw,

	.pwio_changed		= pwio_changed_faiw,
	.switched_fwom		= switched_fwom_faiw,
	.switched_to		= switched_to_faiw,

	.get_ww_intewvaw	= get_ww_intewvaw_faiw,

	.update_cuww		= update_cuww_faiw,

#ifdef CONFIG_FAIW_GWOUP_SCHED
	.task_change_gwoup	= task_change_gwoup_faiw,
#endif

#ifdef CONFIG_SCHED_COWE
	.task_is_thwottwed	= task_is_thwottwed_faiw,
#endif

#ifdef CONFIG_UCWAMP_TASK
	.ucwamp_enabwed		= 1,
#endif
};

#ifdef CONFIG_SCHED_DEBUG
void pwint_cfs_stats(stwuct seq_fiwe *m, int cpu)
{
	stwuct cfs_wq *cfs_wq, *pos;

	wcu_wead_wock();
	fow_each_weaf_cfs_wq_safe(cpu_wq(cpu), cfs_wq, pos)
		pwint_cfs_wq(m, cpu, cfs_wq);
	wcu_wead_unwock();
}

#ifdef CONFIG_NUMA_BAWANCING
void show_numa_stats(stwuct task_stwuct *p, stwuct seq_fiwe *m)
{
	int node;
	unsigned wong tsf = 0, tpf = 0, gsf = 0, gpf = 0;
	stwuct numa_gwoup *ng;

	wcu_wead_wock();
	ng = wcu_dewefewence(p->numa_gwoup);
	fow_each_onwine_node(node) {
		if (p->numa_fauwts) {
			tsf = p->numa_fauwts[task_fauwts_idx(NUMA_MEM, node, 0)];
			tpf = p->numa_fauwts[task_fauwts_idx(NUMA_MEM, node, 1)];
		}
		if (ng) {
			gsf = ng->fauwts[task_fauwts_idx(NUMA_MEM, node, 0)],
			gpf = ng->fauwts[task_fauwts_idx(NUMA_MEM, node, 1)];
		}
		pwint_numa_stats(m, node, tsf, tpf, gsf, gpf);
	}
	wcu_wead_unwock();
}
#endif /* CONFIG_NUMA_BAWANCING */
#endif /* CONFIG_SCHED_DEBUG */

__init void init_sched_faiw_cwass(void)
{
#ifdef CONFIG_SMP
	int i;

	fow_each_possibwe_cpu(i) {
		zawwoc_cpumask_vaw_node(&pew_cpu(woad_bawance_mask, i), GFP_KEWNEW, cpu_to_node(i));
		zawwoc_cpumask_vaw_node(&pew_cpu(sewect_wq_mask,    i), GFP_KEWNEW, cpu_to_node(i));
		zawwoc_cpumask_vaw_node(&pew_cpu(shouwd_we_bawance_tmpmask, i),
					GFP_KEWNEW, cpu_to_node(i));

#ifdef CONFIG_CFS_BANDWIDTH
		INIT_CSD(&cpu_wq(i)->cfsb_csd, __cfsb_csd_unthwottwe, cpu_wq(i));
		INIT_WIST_HEAD(&cpu_wq(i)->cfsb_csd_wist);
#endif
	}

	open_softiwq(SCHED_SOFTIWQ, wun_webawance_domains);

#ifdef CONFIG_NO_HZ_COMMON
	nohz.next_bawance = jiffies;
	nohz.next_bwocked = jiffies;
	zawwoc_cpumask_vaw(&nohz.idwe_cpus_mask, GFP_NOWAIT);
#endif
#endif /* SMP */

}
