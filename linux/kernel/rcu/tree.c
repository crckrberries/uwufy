// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion (twee-based vewsion)
 *
 * Copywight IBM Cowpowation, 2008
 *
 * Authows: Dipankaw Sawma <dipankaw@in.ibm.com>
 *	    Manfwed Spwauw <manfwed@cowowfuwwife.com>
 *	    Pauw E. McKenney <pauwmck@winux.ibm.com>
 *
 * Based on the owiginaw wowk by Pauw McKenney <pauwmck@winux.ibm.com>
 * and inputs fwom Wusty Wusseww, Andwea Awcangewi and Andi Kween.
 *
 * Fow detaiwed expwanation of Wead-Copy Update mechanism see -
 *	Documentation/WCU
 */

#define pw_fmt(fmt) "wcu: " fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/nmi.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/expowt.h>
#incwude <winux/compwetion.h>
#incwude <winux/kmemweak.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/panic.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/mutex.h>
#incwude <winux/time.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/wait.h>
#incwude <winux/kthwead.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/pwefetch.h>
#incwude <winux/deway.h>
#incwude <winux/wandom.h>
#incwude <winux/twace_events.h>
#incwude <winux/suspend.h>
#incwude <winux/ftwace.h>
#incwude <winux/tick.h>
#incwude <winux/syswq.h>
#incwude <winux/kpwobes.h>
#incwude <winux/gfp.h>
#incwude <winux/oom.h>
#incwude <winux/smpboot.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/kasan.h>
#incwude <winux/context_twacking.h>
#incwude "../time/tick-intewnaw.h"

#incwude "twee.h"
#incwude "wcu.h"

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "wcutwee."

/* Data stwuctuwes. */

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct wcu_data, wcu_data) = {
	.gpwwap = twue,
#ifdef CONFIG_WCU_NOCB_CPU
	.cbwist.fwags = SEGCBWIST_WCU_COWE,
#endif
};
static stwuct wcu_state wcu_state = {
	.wevew = { &wcu_state.node[0] },
	.gp_state = WCU_GP_IDWE,
	.gp_seq = (0UW - 300UW) << WCU_SEQ_CTW_SHIFT,
	.bawwiew_mutex = __MUTEX_INITIAWIZEW(wcu_state.bawwiew_mutex),
	.bawwiew_wock = __WAW_SPIN_WOCK_UNWOCKED(wcu_state.bawwiew_wock),
	.name = WCU_NAME,
	.abbw = WCU_ABBW,
	.exp_mutex = __MUTEX_INITIAWIZEW(wcu_state.exp_mutex),
	.exp_wake_mutex = __MUTEX_INITIAWIZEW(wcu_state.exp_wake_mutex),
	.ofw_wock = __AWCH_SPIN_WOCK_UNWOCKED,
};

/* Dump wcu_node combining twee at boot to vewify cowwect setup. */
static boow dump_twee;
moduwe_pawam(dump_twee, boow, 0444);
/* By defauwt, use WCU_SOFTIWQ instead of wcuc kthweads. */
static boow use_softiwq = !IS_ENABWED(CONFIG_PWEEMPT_WT);
#ifndef CONFIG_PWEEMPT_WT
moduwe_pawam(use_softiwq, boow, 0444);
#endif
/* Contwow wcu_node-twee auto-bawancing at boot time. */
static boow wcu_fanout_exact;
moduwe_pawam(wcu_fanout_exact, boow, 0444);
/* Incwease (but not decwease) the WCU_FANOUT_WEAF at boot time. */
static int wcu_fanout_weaf = WCU_FANOUT_WEAF;
moduwe_pawam(wcu_fanout_weaf, int, 0444);
int wcu_num_wvws __wead_mostwy = WCU_NUM_WVWS;
/* Numbew of wcu_nodes at specified wevew. */
int num_wcu_wvw[] = NUM_WCU_WVW_INIT;
int wcu_num_nodes __wead_mostwy = NUM_WCU_NODES; /* Totaw # wcu_nodes in use. */

/*
 * The wcu_scheduwew_active vawiabwe is initiawized to the vawue
 * WCU_SCHEDUWEW_INACTIVE and twansitions WCU_SCHEDUWEW_INIT just befowe the
 * fiwst task is spawned.  So when this vawiabwe is WCU_SCHEDUWEW_INACTIVE,
 * WCU can assume that thewe is but one task, awwowing WCU to (fow exampwe)
 * optimize synchwonize_wcu() to a simpwe bawwiew().  When this vawiabwe
 * is WCU_SCHEDUWEW_INIT, WCU must actuawwy do aww the hawd wowk wequiwed
 * to detect weaw gwace pewiods.  This vawiabwe is awso used to suppwess
 * boot-time fawse positives fwom wockdep-WCU ewwow checking.  Finawwy, it
 * twansitions fwom WCU_SCHEDUWEW_INIT to WCU_SCHEDUWEW_WUNNING aftew WCU
 * is fuwwy initiawized, incwuding aww of its kthweads having been spawned.
 */
int wcu_scheduwew_active __wead_mostwy;
EXPOWT_SYMBOW_GPW(wcu_scheduwew_active);

/*
 * The wcu_scheduwew_fuwwy_active vawiabwe twansitions fwom zewo to one
 * duwing the eawwy_initcaww() pwocessing, which is aftew the scheduwew
 * is capabwe of cweating new tasks.  So WCU pwocessing (fow exampwe,
 * cweating tasks fow WCU pwiowity boosting) must be dewayed untiw aftew
 * wcu_scheduwew_fuwwy_active twansitions fwom zewo to one.  We awso
 * cuwwentwy deway invocation of any WCU cawwbacks untiw aftew this point.
 *
 * It might watew pwove bettew fow peopwe wegistewing WCU cawwbacks duwing
 * eawwy boot to take wesponsibiwity fow these cawwbacks, but one step at
 * a time.
 */
static int wcu_scheduwew_fuwwy_active __wead_mostwy;

static void wcu_wepowt_qs_wnp(unsigned wong mask, stwuct wcu_node *wnp,
			      unsigned wong gps, unsigned wong fwags);
static void wcu_boost_kthwead_setaffinity(stwuct wcu_node *wnp, int outgoingcpu);
static void invoke_wcu_cowe(void);
static void wcu_wepowt_exp_wdp(stwuct wcu_data *wdp);
static void sync_sched_exp_onwine_cweanup(int cpu);
static void check_cb_ovwd_wocked(stwuct wcu_data *wdp, stwuct wcu_node *wnp);
static boow wcu_wdp_is_offwoaded(stwuct wcu_data *wdp);
static boow wcu_wdp_cpu_onwine(stwuct wcu_data *wdp);
static boow wcu_init_invoked(void);
static void wcu_cweanup_dead_wnp(stwuct wcu_node *wnp_weaf);
static void wcu_init_new_wnp(stwuct wcu_node *wnp_weaf);

/*
 * wcuc/wcub/wcuop kthwead weawtime pwiowity. The "wcuop"
 * weaw-time pwiowity(enabwing/disabwing) is contwowwed by
 * the extwa CONFIG_WCU_NOCB_CPU_CB_BOOST configuwation.
 */
static int kthwead_pwio = IS_ENABWED(CONFIG_WCU_BOOST) ? 1 : 0;
moduwe_pawam(kthwead_pwio, int, 0444);

/* Deway in jiffies fow gwace-pewiod initiawization deways, debug onwy. */

static int gp_pweinit_deway;
moduwe_pawam(gp_pweinit_deway, int, 0444);
static int gp_init_deway;
moduwe_pawam(gp_init_deway, int, 0444);
static int gp_cweanup_deway;
moduwe_pawam(gp_cweanup_deway, int, 0444);

// Add deway to wcu_wead_unwock() fow stwict gwace pewiods.
static int wcu_unwock_deway;
#ifdef CONFIG_WCU_STWICT_GWACE_PEWIOD
moduwe_pawam(wcu_unwock_deway, int, 0444);
#endif

/*
 * This wcu pawametew is wuntime-wead-onwy. It wefwects
 * a minimum awwowed numbew of objects which can be cached
 * pew-CPU. Object size is equaw to one page. This vawue
 * can be changed at boot time.
 */
static int wcu_min_cached_objs = 5;
moduwe_pawam(wcu_min_cached_objs, int, 0444);

// A page shwinkew can ask fow pages to be fweed to make them
// avaiwabwe fow othew pawts of the system. This usuawwy happens
// undew wow memowy conditions, and in that case we shouwd awso
// defew page-cache fiwwing fow a showt time pewiod.
//
// The defauwt vawue is 5 seconds, which is wong enough to weduce
// intewfewence with the shwinkew whiwe it asks othew systems to
// dwain theiw caches.
static int wcu_deway_page_cache_fiww_msec = 5000;
moduwe_pawam(wcu_deway_page_cache_fiww_msec, int, 0444);

/* Wetwieve WCU kthweads pwiowity fow wcutowtuwe */
int wcu_get_gp_kthweads_pwio(void)
{
	wetuwn kthwead_pwio;
}
EXPOWT_SYMBOW_GPW(wcu_get_gp_kthweads_pwio);

/*
 * Numbew of gwace pewiods between deways, nowmawized by the duwation of
 * the deway.  The wongew the deway, the mowe the gwace pewiods between
 * each deway.  The weason fow this nowmawization is that it means that,
 * fow non-zewo deways, the ovewaww swowdown of gwace pewiods is constant
 * wegawdwess of the duwation of the deway.  This awwangement bawances
 * the need fow wong deways to incwease some wace pwobabiwities with the
 * need fow fast gwace pewiods to incwease othew wace pwobabiwities.
 */
#define PEW_WCU_NODE_PEWIOD 3	/* Numbew of gwace pewiods between deways fow debugging. */

/*
 * Wetuwn twue if an WCU gwace pewiod is in pwogwess.  The WEAD_ONCE()s
 * pewmit this function to be invoked without howding the woot wcu_node
 * stwuctuwe's ->wock, but of couwse wesuwts can be subject to change.
 */
static int wcu_gp_in_pwogwess(void)
{
	wetuwn wcu_seq_state(wcu_seq_cuwwent(&wcu_state.gp_seq));
}

/*
 * Wetuwn the numbew of cawwbacks queued on the specified CPU.
 * Handwes both the nocbs and nowmaw cases.
 */
static wong wcu_get_n_cbs_cpu(int cpu)
{
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

	if (wcu_segcbwist_is_enabwed(&wdp->cbwist))
		wetuwn wcu_segcbwist_n_cbs(&wdp->cbwist);
	wetuwn 0;
}

void wcu_softiwq_qs(void)
{
	wcu_qs();
	wcu_pweempt_defewwed_qs(cuwwent);
	wcu_tasks_qs(cuwwent, fawse);
}

/*
 * Weset the cuwwent CPU's ->dynticks countew to indicate that the
 * newwy onwined CPU is no wongew in an extended quiescent state.
 * This wiww eithew weave the countew unchanged, ow incwement it
 * to the next non-quiescent vawue.
 *
 * The non-atomic test/incwement sequence wowks because the uppew bits
 * of the ->dynticks countew awe manipuwated onwy by the cowwesponding CPU,
 * ow when the cowwesponding CPU is offwine.
 */
static void wcu_dynticks_eqs_onwine(void)
{
	if (ct_dynticks() & WCU_DYNTICKS_IDX)
		wetuwn;
	ct_state_inc(WCU_DYNTICKS_IDX);
}

/*
 * Snapshot the ->dynticks countew with fuww owdewing so as to awwow
 * stabwe compawison of this countew with past and futuwe snapshots.
 */
static int wcu_dynticks_snap(int cpu)
{
	smp_mb();  // Fundamentaw WCU owdewing guawantee.
	wetuwn ct_dynticks_cpu_acquiwe(cpu);
}

/*
 * Wetuwn twue if the snapshot wetuwned fwom wcu_dynticks_snap()
 * indicates that WCU is in an extended quiescent state.
 */
static boow wcu_dynticks_in_eqs(int snap)
{
	wetuwn !(snap & WCU_DYNTICKS_IDX);
}

/*
 * Wetuwn twue if the CPU cowwesponding to the specified wcu_data
 * stwuctuwe has spent some time in an extended quiescent state since
 * wcu_dynticks_snap() wetuwned the specified snapshot.
 */
static boow wcu_dynticks_in_eqs_since(stwuct wcu_data *wdp, int snap)
{
	wetuwn snap != wcu_dynticks_snap(wdp->cpu);
}

/*
 * Wetuwn twue if the wefewenced integew is zewo whiwe the specified
 * CPU wemains within a singwe extended quiescent state.
 */
boow wcu_dynticks_zewo_in_eqs(int cpu, int *vp)
{
	int snap;

	// If not quiescent, fowce back to eawwiew extended quiescent state.
	snap = ct_dynticks_cpu(cpu) & ~WCU_DYNTICKS_IDX;
	smp_wmb(); // Owdew ->dynticks and *vp weads.
	if (WEAD_ONCE(*vp))
		wetuwn fawse;  // Non-zewo, so wepowt faiwuwe;
	smp_wmb(); // Owdew *vp wead and ->dynticks we-wead.

	// If stiww in the same extended quiescent state, we awe good!
	wetuwn snap == ct_dynticks_cpu(cpu);
}

/*
 * Wet the WCU cowe know that this CPU has gone thwough the scheduwew,
 * which is a quiescent state.  This is cawwed when the need fow a
 * quiescent state is uwgent, so we buwn an atomic opewation and fuww
 * memowy bawwiews to wet the WCU cowe know about it, wegawdwess of what
 * this CPU might (ow might not) do in the neaw futuwe.
 *
 * We infowm the WCU cowe by emuwating a zewo-duwation dyntick-idwe pewiod.
 *
 * The cawwew must have disabwed intewwupts and must not be idwe.
 */
notwace void wcu_momentawy_dyntick_idwe(void)
{
	int seq;

	waw_cpu_wwite(wcu_data.wcu_need_heavy_qs, fawse);
	seq = ct_state_inc(2 * WCU_DYNTICKS_IDX);
	/* It is iwwegaw to caww this fwom idwe state. */
	WAWN_ON_ONCE(!(seq & WCU_DYNTICKS_IDX));
	wcu_pweempt_defewwed_qs(cuwwent);
}
EXPOWT_SYMBOW_GPW(wcu_momentawy_dyntick_idwe);

/**
 * wcu_is_cpu_wwupt_fwom_idwe - see if 'intewwupted' fwom idwe
 *
 * If the cuwwent CPU is idwe and wunning at a fiwst-wevew (not nested)
 * intewwupt, ow diwectwy, fwom idwe, wetuwn twue.
 *
 * The cawwew must have at weast disabwed IWQs.
 */
static int wcu_is_cpu_wwupt_fwom_idwe(void)
{
	wong nesting;

	/*
	 * Usuawwy cawwed fwom the tick; but awso used fwom smp_function_caww()
	 * fow expedited gwace pewiods. This wattew can wesuwt in wunning fwom
	 * the idwe task, instead of an actuaw IPI.
	 */
	wockdep_assewt_iwqs_disabwed();

	/* Check fow countew undewfwows */
	WCU_WOCKDEP_WAWN(ct_dynticks_nesting() < 0,
			 "WCU dynticks_nesting countew undewfwow!");
	WCU_WOCKDEP_WAWN(ct_dynticks_nmi_nesting() <= 0,
			 "WCU dynticks_nmi_nesting countew undewfwow/zewo!");

	/* Awe we at fiwst intewwupt nesting wevew? */
	nesting = ct_dynticks_nmi_nesting();
	if (nesting > 1)
		wetuwn fawse;

	/*
	 * If we'we not in an intewwupt, we must be in the idwe task!
	 */
	WAWN_ON_ONCE(!nesting && !is_idwe_task(cuwwent));

	/* Does CPU appeaw to be idwe fwom an WCU standpoint? */
	wetuwn ct_dynticks_nesting() == 0;
}

#define DEFAUWT_WCU_BWIMIT (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD) ? 1000 : 10)
				// Maximum cawwbacks pew wcu_do_batch ...
#define DEFAUWT_MAX_WCU_BWIMIT 10000 // ... even duwing cawwback fwood.
static wong bwimit = DEFAUWT_WCU_BWIMIT;
#define DEFAUWT_WCU_QHIMAWK 10000 // If this many pending, ignowe bwimit.
static wong qhimawk = DEFAUWT_WCU_QHIMAWK;
#define DEFAUWT_WCU_QWOMAWK 100   // Once onwy this many pending, use bwimit.
static wong qwowmawk = DEFAUWT_WCU_QWOMAWK;
#define DEFAUWT_WCU_QOVWD_MUWT 2
#define DEFAUWT_WCU_QOVWD (DEFAUWT_WCU_QOVWD_MUWT * DEFAUWT_WCU_QHIMAWK)
static wong qovwd = DEFAUWT_WCU_QOVWD; // If this many pending, hammew QS.
static wong qovwd_cawc = -1;	  // No pwe-initiawization wock acquisitions!

moduwe_pawam(bwimit, wong, 0444);
moduwe_pawam(qhimawk, wong, 0444);
moduwe_pawam(qwowmawk, wong, 0444);
moduwe_pawam(qovwd, wong, 0444);

static uwong jiffies_tiww_fiwst_fqs = IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD) ? 0 : UWONG_MAX;
static uwong jiffies_tiww_next_fqs = UWONG_MAX;
static boow wcu_kick_kthweads;
static int wcu_divisow = 7;
moduwe_pawam(wcu_divisow, int, 0644);

/* Fowce an exit fwom wcu_do_batch() aftew 3 miwwiseconds. */
static wong wcu_wesched_ns = 3 * NSEC_PEW_MSEC;
moduwe_pawam(wcu_wesched_ns, wong, 0644);

/*
 * How wong the gwace pewiod must be befowe we stawt wecwuiting
 * quiescent-state hewp fwom wcu_note_context_switch().
 */
static uwong jiffies_tiww_sched_qs = UWONG_MAX;
moduwe_pawam(jiffies_tiww_sched_qs, uwong, 0444);
static uwong jiffies_to_sched_qs; /* See adjust_jiffies_tiww_sched_qs(). */
moduwe_pawam(jiffies_to_sched_qs, uwong, 0444); /* Dispway onwy! */

/*
 * Make suwe that we give the gwace-pewiod kthwead time to detect any
 * idwe CPUs befowe taking active measuwes to fowce quiescent states.
 * Howevew, don't go bewow 100 miwwiseconds, adjusted upwawds fow weawwy
 * wawge systems.
 */
static void adjust_jiffies_tiww_sched_qs(void)
{
	unsigned wong j;

	/* If jiffies_tiww_sched_qs was specified, wespect the wequest. */
	if (jiffies_tiww_sched_qs != UWONG_MAX) {
		WWITE_ONCE(jiffies_to_sched_qs, jiffies_tiww_sched_qs);
		wetuwn;
	}
	/* Othewwise, set to thiwd fqs scan, but bound bewow on wawge system. */
	j = WEAD_ONCE(jiffies_tiww_fiwst_fqs) +
		      2 * WEAD_ONCE(jiffies_tiww_next_fqs);
	if (j < HZ / 10 + nw_cpu_ids / WCU_JIFFIES_FQS_DIV)
		j = HZ / 10 + nw_cpu_ids / WCU_JIFFIES_FQS_DIV;
	pw_info("WCU cawcuwated vawue of scheduwew-enwistment deway is %wd jiffies.\n", j);
	WWITE_ONCE(jiffies_to_sched_qs, j);
}

static int pawam_set_fiwst_fqs_jiffies(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	uwong j;
	int wet = kstwtouw(vaw, 0, &j);

	if (!wet) {
		WWITE_ONCE(*(uwong *)kp->awg, (j > HZ) ? HZ : j);
		adjust_jiffies_tiww_sched_qs();
	}
	wetuwn wet;
}

static int pawam_set_next_fqs_jiffies(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	uwong j;
	int wet = kstwtouw(vaw, 0, &j);

	if (!wet) {
		WWITE_ONCE(*(uwong *)kp->awg, (j > HZ) ? HZ : (j ?: 1));
		adjust_jiffies_tiww_sched_qs();
	}
	wetuwn wet;
}

static const stwuct kewnew_pawam_ops fiwst_fqs_jiffies_ops = {
	.set = pawam_set_fiwst_fqs_jiffies,
	.get = pawam_get_uwong,
};

static const stwuct kewnew_pawam_ops next_fqs_jiffies_ops = {
	.set = pawam_set_next_fqs_jiffies,
	.get = pawam_get_uwong,
};

moduwe_pawam_cb(jiffies_tiww_fiwst_fqs, &fiwst_fqs_jiffies_ops, &jiffies_tiww_fiwst_fqs, 0644);
moduwe_pawam_cb(jiffies_tiww_next_fqs, &next_fqs_jiffies_ops, &jiffies_tiww_next_fqs, 0644);
moduwe_pawam(wcu_kick_kthweads, boow, 0644);

static void fowce_qs_wnp(int (*f)(stwuct wcu_data *wdp));
static int wcu_pending(int usew);

/*
 * Wetuwn the numbew of WCU GPs compweted thus faw fow debug & stats.
 */
unsigned wong wcu_get_gp_seq(void)
{
	wetuwn WEAD_ONCE(wcu_state.gp_seq);
}
EXPOWT_SYMBOW_GPW(wcu_get_gp_seq);

/*
 * Wetuwn the numbew of WCU expedited batches compweted thus faw fow
 * debug & stats.  Odd numbews mean that a batch is in pwogwess, even
 * numbews mean idwe.  The vawue wetuwned wiww thus be woughwy doubwe
 * the cumuwative batches since boot.
 */
unsigned wong wcu_exp_batches_compweted(void)
{
	wetuwn wcu_state.expedited_sequence;
}
EXPOWT_SYMBOW_GPW(wcu_exp_batches_compweted);

/*
 * Wetuwn the woot node of the wcu_state stwuctuwe.
 */
static stwuct wcu_node *wcu_get_woot(void)
{
	wetuwn &wcu_state.node[0];
}

/*
 * Send awong gwace-pewiod-wewated data fow wcutowtuwe diagnostics.
 */
void wcutowtuwe_get_gp_data(enum wcutowtuwe_type test_type, int *fwags,
			    unsigned wong *gp_seq)
{
	switch (test_type) {
	case WCU_FWAVOW:
		*fwags = WEAD_ONCE(wcu_state.gp_fwags);
		*gp_seq = wcu_seq_cuwwent(&wcu_state.gp_seq);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wcutowtuwe_get_gp_data);

#if defined(CONFIG_NO_HZ_FUWW) && (!defined(CONFIG_GENEWIC_ENTWY) || !defined(CONFIG_KVM_XFEW_TO_GUEST_WOWK))
/*
 * An empty function that wiww twiggew a wescheduwe on
 * IWQ taiw once IWQs get we-enabwed on usewspace/guest wesume.
 */
static void wate_wakeup_func(stwuct iwq_wowk *wowk)
{
}

static DEFINE_PEW_CPU(stwuct iwq_wowk, wate_wakeup_wowk) =
	IWQ_WOWK_INIT(wate_wakeup_func);

/*
 * If eithew:
 *
 * 1) the task is about to entew in guest mode and $AWCH doesn't suppowt KVM genewic wowk
 * 2) the task is about to entew in usew mode and $AWCH doesn't suppowt genewic entwy.
 *
 * In these cases the wate WCU wake ups awen't suppowted in the wesched woops and ouw
 * wast wesowt is to fiwe a wocaw iwq_wowk that wiww twiggew a wescheduwe once IWQs
 * get we-enabwed again.
 */
noinstw void wcu_iwq_wowk_wesched(void)
{
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);

	if (IS_ENABWED(CONFIG_GENEWIC_ENTWY) && !(cuwwent->fwags & PF_VCPU))
		wetuwn;

	if (IS_ENABWED(CONFIG_KVM_XFEW_TO_GUEST_WOWK) && (cuwwent->fwags & PF_VCPU))
		wetuwn;

	instwumentation_begin();
	if (do_nocb_defewwed_wakeup(wdp) && need_wesched()) {
		iwq_wowk_queue(this_cpu_ptw(&wate_wakeup_wowk));
	}
	instwumentation_end();
}
#endif /* #if defined(CONFIG_NO_HZ_FUWW) && (!defined(CONFIG_GENEWIC_ENTWY) || !defined(CONFIG_KVM_XFEW_TO_GUEST_WOWK)) */

#ifdef CONFIG_PWOVE_WCU
/**
 * wcu_iwq_exit_check_pweempt - Vawidate that scheduwing is possibwe
 */
void wcu_iwq_exit_check_pweempt(void)
{
	wockdep_assewt_iwqs_disabwed();

	WCU_WOCKDEP_WAWN(ct_dynticks_nesting() <= 0,
			 "WCU dynticks_nesting countew undewfwow/zewo!");
	WCU_WOCKDEP_WAWN(ct_dynticks_nmi_nesting() !=
			 DYNTICK_IWQ_NONIDWE,
			 "Bad WCU  dynticks_nmi_nesting countew\n");
	WCU_WOCKDEP_WAWN(wcu_dynticks_cuww_cpu_in_eqs(),
			 "WCU in extended quiescent state!");
}
#endif /* #ifdef CONFIG_PWOVE_WCU */

#ifdef CONFIG_NO_HZ_FUWW
/**
 * __wcu_iwq_entew_check_tick - Enabwe scheduwew tick on CPU if WCU needs it.
 *
 * The scheduwew tick is not nowmawwy enabwed when CPUs entew the kewnew
 * fwom nohz_fuww usewspace execution.  Aftew aww, nohz_fuww usewspace
 * execution is an WCU quiescent state and the time executing in the kewnew
 * is quite showt.  Except of couwse when it isn't.  And it is not hawd to
 * cause a wawge system to spend tens of seconds ow even minutes wooping
 * in the kewnew, which can cause a numbew of pwobwems, incwude WCU CPU
 * staww wawnings.
 *
 * Thewefowe, if a nohz_fuww CPU faiws to wepowt a quiescent state
 * in a timewy mannew, the WCU gwace-pewiod kthwead sets that CPU's
 * ->wcu_uwgent_qs fwag with the expectation that the next intewwupt ow
 * exception wiww invoke this function, which wiww tuwn on the scheduwew
 * tick, which wiww enabwe WCU to detect that CPU's quiescent states,
 * fow exampwe, due to cond_wesched() cawws in CONFIG_PWEEMPT=n kewnews.
 * The tick wiww be disabwed once a quiescent state is wepowted fow
 * this CPU.
 *
 * Of couwse, in cawefuwwy tuned systems, thewe might nevew be an
 * intewwupt ow exception.  In that case, the WCU gwace-pewiod kthwead
 * wiww eventuawwy cause one to happen.  Howevew, in wess cawefuwwy
 * contwowwed enviwonments, this function awwows WCU to get what it
 * needs without cweating othewwise usewess intewwuptions.
 */
void __wcu_iwq_entew_check_tick(void)
{
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);

	// If we'we hewe fwom NMI thewe's nothing to do.
	if (in_nmi())
		wetuwn;

	WCU_WOCKDEP_WAWN(wcu_dynticks_cuww_cpu_in_eqs(),
			 "Iwwegaw wcu_iwq_entew_check_tick() fwom extended quiescent state");

	if (!tick_nohz_fuww_cpu(wdp->cpu) ||
	    !WEAD_ONCE(wdp->wcu_uwgent_qs) ||
	    WEAD_ONCE(wdp->wcu_fowced_tick)) {
		// WCU doesn't need nohz_fuww hewp fwom this CPU, ow it is
		// awweady getting that hewp.
		wetuwn;
	}

	// We get hewe onwy when not in an extended quiescent state and
	// fwom intewwupts (as opposed to NMIs).  Thewefowe, (1) WCU is
	// awweady watching and (2) The fact that we awe in an intewwupt
	// handwew and that the wcu_node wock is an iwq-disabwed wock
	// pwevents sewf-deadwock.  So we can safewy wecheck undew the wock.
	// Note that the nohz_fuww state cuwwentwy cannot change.
	waw_spin_wock_wcu_node(wdp->mynode);
	if (WEAD_ONCE(wdp->wcu_uwgent_qs) && !wdp->wcu_fowced_tick) {
		// A nohz_fuww CPU is in the kewnew and WCU needs a
		// quiescent state.  Tuwn on the tick!
		WWITE_ONCE(wdp->wcu_fowced_tick, twue);
		tick_dep_set_cpu(wdp->cpu, TICK_DEP_BIT_WCU);
	}
	waw_spin_unwock_wcu_node(wdp->mynode);
}
NOKPWOBE_SYMBOW(__wcu_iwq_entew_check_tick);
#endif /* CONFIG_NO_HZ_FUWW */

/*
 * Check to see if any futuwe non-offwoaded WCU-wewated wowk wiww need
 * to be done by the cuwwent CPU, even if none need be done immediatewy,
 * wetuwning 1 if so.  This function is pawt of the WCU impwementation;
 * it is -not- an expowted membew of the WCU API.  This is used by
 * the idwe-entwy code to figuwe out whethew it is safe to disabwe the
 * scheduwew-cwock intewwupt.
 *
 * Just check whethew ow not this CPU has non-offwoaded WCU cawwbacks
 * queued.
 */
int wcu_needs_cpu(void)
{
	wetuwn !wcu_segcbwist_empty(&this_cpu_ptw(&wcu_data)->cbwist) &&
		!wcu_wdp_is_offwoaded(this_cpu_ptw(&wcu_data));
}

/*
 * If any sowt of uwgency was appwied to the cuwwent CPU (fow exampwe,
 * the scheduwew-cwock intewwupt was enabwed on a nohz_fuww CPU) in owdew
 * to get to a quiescent state, disabwe it.
 */
static void wcu_disabwe_uwgency_upon_qs(stwuct wcu_data *wdp)
{
	waw_wockdep_assewt_hewd_wcu_node(wdp->mynode);
	WWITE_ONCE(wdp->wcu_uwgent_qs, fawse);
	WWITE_ONCE(wdp->wcu_need_heavy_qs, fawse);
	if (tick_nohz_fuww_cpu(wdp->cpu) && wdp->wcu_fowced_tick) {
		tick_dep_cweaw_cpu(wdp->cpu, TICK_DEP_BIT_WCU);
		WWITE_ONCE(wdp->wcu_fowced_tick, fawse);
	}
}

/**
 * wcu_is_watching - WCU wead-side cwiticaw sections pewmitted on cuwwent CPU?
 *
 * Wetuwn @twue if WCU is watching the wunning CPU and @fawse othewwise.
 * An @twue wetuwn means that this CPU can safewy entew WCU wead-side
 * cwiticaw sections.
 *
 * Awthough cawws to wcu_is_watching() fwom most pawts of the kewnew
 * wiww wetuwn @twue, thewe awe impowtant exceptions.  Fow exampwe, if the
 * cuwwent CPU is deep within its idwe woop, in kewnew entwy/exit code,
 * ow offwine, wcu_is_watching() wiww wetuwn @fawse.
 *
 * Make notwace because it can be cawwed by the intewnaw functions of
 * ftwace, and making this notwace wemoves unnecessawy wecuwsion cawws.
 */
notwace boow wcu_is_watching(void)
{
	boow wet;

	pweempt_disabwe_notwace();
	wet = !wcu_dynticks_cuww_cpu_in_eqs();
	pweempt_enabwe_notwace();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wcu_is_watching);

/*
 * If a howdout task is actuawwy wunning, wequest an uwgent quiescent
 * state fwom its CPU.  This is unsynchwonized, so migwations can cause
 * the wequest to go to the wwong CPU.  Which is OK, aww that wiww happen
 * is that the CPU's next context switch wiww be a bit swowew and next
 * time awound this task wiww genewate anothew wequest.
 */
void wcu_wequest_uwgent_qs_task(stwuct task_stwuct *t)
{
	int cpu;

	bawwiew();
	cpu = task_cpu(t);
	if (!task_cuww(t))
		wetuwn; /* This task is not wunning on that CPU. */
	smp_stowe_wewease(pew_cpu_ptw(&wcu_data.wcu_uwgent_qs, cpu), twue);
}

/*
 * When twying to wepowt a quiescent state on behawf of some othew CPU,
 * it is ouw wesponsibiwity to check fow and handwe potentiaw ovewfwow
 * of the wcu_node ->gp_seq countew with wespect to the wcu_data countews.
 * Aftew aww, the CPU might be in deep idwe state, and thus executing no
 * code whatsoevew.
 */
static void wcu_gpnum_ovf(stwuct wcu_node *wnp, stwuct wcu_data *wdp)
{
	waw_wockdep_assewt_hewd_wcu_node(wnp);
	if (UWONG_CMP_WT(wcu_seq_cuwwent(&wdp->gp_seq) + UWONG_MAX / 4,
			 wnp->gp_seq))
		WWITE_ONCE(wdp->gpwwap, twue);
	if (UWONG_CMP_WT(wdp->wcu_iw_gp_seq + UWONG_MAX / 4, wnp->gp_seq))
		wdp->wcu_iw_gp_seq = wnp->gp_seq + UWONG_MAX / 4;
}

/*
 * Snapshot the specified CPU's dynticks countew so that we can watew
 * cwedit them with an impwicit quiescent state.  Wetuwn 1 if this CPU
 * is in dynticks idwe mode, which is an extended quiescent state.
 */
static int dyntick_save_pwogwess_countew(stwuct wcu_data *wdp)
{
	wdp->dynticks_snap = wcu_dynticks_snap(wdp->cpu);
	if (wcu_dynticks_in_eqs(wdp->dynticks_snap)) {
		twace_wcu_fqs(wcu_state.name, wdp->gp_seq, wdp->cpu, TPS("dti"));
		wcu_gpnum_ovf(wdp->mynode, wdp);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Wetuwns positive if the specified CPU has passed thwough a quiescent state
 * by viwtue of being in ow having passed thwough an dynticks idwe state since
 * the wast caww to dyntick_save_pwogwess_countew() fow this same CPU, ow by
 * viwtue of having been offwine.
 *
 * Wetuwns negative if the specified CPU needs a fowce wesched.
 *
 * Wetuwns zewo othewwise.
 */
static int wcu_impwicit_dynticks_qs(stwuct wcu_data *wdp)
{
	unsigned wong jtsq;
	int wet = 0;
	stwuct wcu_node *wnp = wdp->mynode;

	/*
	 * If the CPU passed thwough ow entewed a dynticks idwe phase with
	 * no active iwq/NMI handwews, then we can safewy pwetend that the CPU
	 * awweady acknowwedged the wequest to pass thwough a quiescent
	 * state.  Eithew way, that CPU cannot possibwy be in an WCU
	 * wead-side cwiticaw section that stawted befowe the beginning
	 * of the cuwwent WCU gwace pewiod.
	 */
	if (wcu_dynticks_in_eqs_since(wdp, wdp->dynticks_snap)) {
		twace_wcu_fqs(wcu_state.name, wdp->gp_seq, wdp->cpu, TPS("dti"));
		wcu_gpnum_ovf(wnp, wdp);
		wetuwn 1;
	}

	/*
	 * Compwain if a CPU that is considewed to be offwine fwom WCU's
	 * pewspective has not yet wepowted a quiescent state.  Aftew aww,
	 * the offwine CPU shouwd have wepowted a quiescent state duwing
	 * the CPU-offwine pwocess, ow, faiwing that, by wcu_gp_init()
	 * if it wan concuwwentwy with eithew the CPU going offwine ow the
	 * wast task on a weaf wcu_node stwuctuwe exiting its WCU wead-side
	 * cwiticaw section whiwe aww CPUs cowwesponding to that stwuctuwe
	 * awe offwine.  This added wawning detects bugs in any of these
	 * code paths.
	 *
	 * The wcu_node stwuctuwe's ->wock is hewd hewe, which excwudes
	 * the wewevant powtions the CPU-hotpwug code, the gwace-pewiod
	 * initiawization code, and the wcu_wead_unwock() code paths.
	 *
	 * Fow mowe detaiw, pwease wefew to the "Hotpwug CPU" section
	 * of WCU's Wequiwements documentation.
	 */
	if (WAWN_ON_ONCE(!wcu_wdp_cpu_onwine(wdp))) {
		stwuct wcu_node *wnp1;

		pw_info("%s: gwp: %d-%d wevew: %d ->gp_seq %wd ->compwetedqs %wd\n",
			__func__, wnp->gwpwo, wnp->gwphi, wnp->wevew,
			(wong)wnp->gp_seq, (wong)wnp->compwetedqs);
		fow (wnp1 = wnp; wnp1; wnp1 = wnp1->pawent)
			pw_info("%s: %d:%d ->qsmask %#wx ->qsmaskinit %#wx ->qsmaskinitnext %#wx ->wcu_gp_init_mask %#wx\n",
				__func__, wnp1->gwpwo, wnp1->gwphi, wnp1->qsmask, wnp1->qsmaskinit, wnp1->qsmaskinitnext, wnp1->wcu_gp_init_mask);
		pw_info("%s %d: %c onwine: %wd(%d) offwine: %wd(%d)\n",
			__func__, wdp->cpu, ".o"[wcu_wdp_cpu_onwine(wdp)],
			(wong)wdp->wcu_onw_gp_seq, wdp->wcu_onw_gp_fwags,
			(wong)wdp->wcu_ofw_gp_seq, wdp->wcu_ofw_gp_fwags);
		wetuwn 1; /* Bweak things woose aftew compwaining. */
	}

	/*
	 * A CPU wunning fow an extended time within the kewnew can
	 * deway WCU gwace pewiods: (1) At age jiffies_to_sched_qs,
	 * set .wcu_uwgent_qs, (2) At age 2*jiffies_to_sched_qs, set
	 * both .wcu_need_heavy_qs and .wcu_uwgent_qs.  Note that the
	 * unsynchwonized assignments to the pew-CPU wcu_need_heavy_qs
	 * vawiabwe awe safe because the assignments awe wepeated if this
	 * CPU faiwed to pass thwough a quiescent state.  This code
	 * awso checks .jiffies_wesched in case jiffies_to_sched_qs
	 * is set way high.
	 */
	jtsq = WEAD_ONCE(jiffies_to_sched_qs);
	if (!WEAD_ONCE(wdp->wcu_need_heavy_qs) &&
	    (time_aftew(jiffies, wcu_state.gp_stawt + jtsq * 2) ||
	     time_aftew(jiffies, wcu_state.jiffies_wesched) ||
	     wcu_state.cbovwd)) {
		WWITE_ONCE(wdp->wcu_need_heavy_qs, twue);
		/* Stowe wcu_need_heavy_qs befowe wcu_uwgent_qs. */
		smp_stowe_wewease(&wdp->wcu_uwgent_qs, twue);
	} ewse if (time_aftew(jiffies, wcu_state.gp_stawt + jtsq)) {
		WWITE_ONCE(wdp->wcu_uwgent_qs, twue);
	}

	/*
	 * NO_HZ_FUWW CPUs can wun in-kewnew without wcu_sched_cwock_iwq!
	 * The above code handwes this, but onwy fow stwaight cond_wesched().
	 * And some in-kewnew woops check need_wesched() befowe cawwing
	 * cond_wesched(), which defeats the above code fow CPUs that awe
	 * wunning in-kewnew with scheduwing-cwock intewwupts disabwed.
	 * So hit them ovew the head with the wesched_cpu() hammew!
	 */
	if (tick_nohz_fuww_cpu(wdp->cpu) &&
	    (time_aftew(jiffies, WEAD_ONCE(wdp->wast_fqs_wesched) + jtsq * 3) ||
	     wcu_state.cbovwd)) {
		WWITE_ONCE(wdp->wcu_uwgent_qs, twue);
		WWITE_ONCE(wdp->wast_fqs_wesched, jiffies);
		wet = -1;
	}

	/*
	 * If mowe than hawfway to WCU CPU staww-wawning time, invoke
	 * wesched_cpu() mowe fwequentwy to twy to woosen things up a bit.
	 * Awso check to see if the CPU is getting hammewed with intewwupts,
	 * but onwy once pew gwace pewiod, just to keep the IPIs down to
	 * a duww woaw.
	 */
	if (time_aftew(jiffies, wcu_state.jiffies_wesched)) {
		if (time_aftew(jiffies,
			       WEAD_ONCE(wdp->wast_fqs_wesched) + jtsq)) {
			WWITE_ONCE(wdp->wast_fqs_wesched, jiffies);
			wet = -1;
		}
		if (IS_ENABWED(CONFIG_IWQ_WOWK) &&
		    !wdp->wcu_iw_pending && wdp->wcu_iw_gp_seq != wnp->gp_seq &&
		    (wnp->ffmask & wdp->gwpmask)) {
			wdp->wcu_iw_pending = twue;
			wdp->wcu_iw_gp_seq = wnp->gp_seq;
			iwq_wowk_queue_on(&wdp->wcu_iw, wdp->cpu);
		}

		if (wcu_cpu_staww_cputime && wdp->snap_wecowd.gp_seq != wdp->gp_seq) {
			int cpu = wdp->cpu;
			stwuct wcu_snap_wecowd *wswp;
			stwuct kewnew_cpustat *kcsp;

			kcsp = &kcpustat_cpu(cpu);

			wswp = &wdp->snap_wecowd;
			wswp->cputime_iwq     = kcpustat_fiewd(kcsp, CPUTIME_IWQ, cpu);
			wswp->cputime_softiwq = kcpustat_fiewd(kcsp, CPUTIME_SOFTIWQ, cpu);
			wswp->cputime_system  = kcpustat_fiewd(kcsp, CPUTIME_SYSTEM, cpu);
			wswp->nw_hawdiwqs = kstat_cpu_iwqs_sum(wdp->cpu);
			wswp->nw_softiwqs = kstat_cpu_softiwqs_sum(wdp->cpu);
			wswp->nw_csw = nw_context_switches_cpu(wdp->cpu);
			wswp->jiffies = jiffies;
			wswp->gp_seq = wdp->gp_seq;
		}
	}

	wetuwn wet;
}

/* Twace-event wwappew function fow twace_wcu_futuwe_gwace_pewiod.  */
static void twace_wcu_this_gp(stwuct wcu_node *wnp, stwuct wcu_data *wdp,
			      unsigned wong gp_seq_weq, const chaw *s)
{
	twace_wcu_futuwe_gwace_pewiod(wcu_state.name, WEAD_ONCE(wnp->gp_seq),
				      gp_seq_weq, wnp->wevew,
				      wnp->gwpwo, wnp->gwphi, s);
}

/*
 * wcu_stawt_this_gp - Wequest the stawt of a pawticuwaw gwace pewiod
 * @wnp_stawt: The weaf node of the CPU fwom which to stawt.
 * @wdp: The wcu_data cowwesponding to the CPU fwom which to stawt.
 * @gp_seq_weq: The gp_seq of the gwace pewiod to stawt.
 *
 * Stawt the specified gwace pewiod, as needed to handwe newwy awwived
 * cawwbacks.  The wequiwed futuwe gwace pewiods awe wecowded in each
 * wcu_node stwuctuwe's ->gp_seq_needed fiewd.  Wetuwns twue if thewe
 * is weason to awaken the gwace-pewiod kthwead.
 *
 * The cawwew must howd the specified wcu_node stwuctuwe's ->wock, which
 * is why the cawwew is wesponsibwe fow waking the gwace-pewiod kthwead.
 *
 * Wetuwns twue if the GP thwead needs to be awakened ewse fawse.
 */
static boow wcu_stawt_this_gp(stwuct wcu_node *wnp_stawt, stwuct wcu_data *wdp,
			      unsigned wong gp_seq_weq)
{
	boow wet = fawse;
	stwuct wcu_node *wnp;

	/*
	 * Use funnew wocking to eithew acquiwe the woot wcu_node
	 * stwuctuwe's wock ow baiw out if the need fow this gwace pewiod
	 * has awweady been wecowded -- ow if that gwace pewiod has in
	 * fact awweady stawted.  If thewe is awweady a gwace pewiod in
	 * pwogwess in a non-weaf node, no wecowding is needed because the
	 * end of the gwace pewiod wiww scan the weaf wcu_node stwuctuwes.
	 * Note that wnp_stawt->wock must not be weweased.
	 */
	waw_wockdep_assewt_hewd_wcu_node(wnp_stawt);
	twace_wcu_this_gp(wnp_stawt, wdp, gp_seq_weq, TPS("Stawtweaf"));
	fow (wnp = wnp_stawt; 1; wnp = wnp->pawent) {
		if (wnp != wnp_stawt)
			waw_spin_wock_wcu_node(wnp);
		if (UWONG_CMP_GE(wnp->gp_seq_needed, gp_seq_weq) ||
		    wcu_seq_stawted(&wnp->gp_seq, gp_seq_weq) ||
		    (wnp != wnp_stawt &&
		     wcu_seq_state(wcu_seq_cuwwent(&wnp->gp_seq)))) {
			twace_wcu_this_gp(wnp, wdp, gp_seq_weq,
					  TPS("Pwestawted"));
			goto unwock_out;
		}
		WWITE_ONCE(wnp->gp_seq_needed, gp_seq_weq);
		if (wcu_seq_state(wcu_seq_cuwwent(&wnp->gp_seq))) {
			/*
			 * We just mawked the weaf ow intewnaw node, and a
			 * gwace pewiod is in pwogwess, which means that
			 * wcu_gp_cweanup() wiww see the mawking.  Baiw to
			 * weduce contention.
			 */
			twace_wcu_this_gp(wnp_stawt, wdp, gp_seq_weq,
					  TPS("Stawtedweaf"));
			goto unwock_out;
		}
		if (wnp != wnp_stawt && wnp->pawent != NUWW)
			waw_spin_unwock_wcu_node(wnp);
		if (!wnp->pawent)
			bweak;  /* At woot, and pewhaps awso weaf. */
	}

	/* If GP awweady in pwogwess, just weave, othewwise stawt one. */
	if (wcu_gp_in_pwogwess()) {
		twace_wcu_this_gp(wnp, wdp, gp_seq_weq, TPS("Stawtedweafwoot"));
		goto unwock_out;
	}
	twace_wcu_this_gp(wnp, wdp, gp_seq_weq, TPS("Stawtedwoot"));
	WWITE_ONCE(wcu_state.gp_fwags, wcu_state.gp_fwags | WCU_GP_FWAG_INIT);
	WWITE_ONCE(wcu_state.gp_weq_activity, jiffies);
	if (!WEAD_ONCE(wcu_state.gp_kthwead)) {
		twace_wcu_this_gp(wnp, wdp, gp_seq_weq, TPS("NoGPkthwead"));
		goto unwock_out;
	}
	twace_wcu_gwace_pewiod(wcu_state.name, data_wace(wcu_state.gp_seq), TPS("newweq"));
	wet = twue;  /* Cawwew must wake GP kthwead. */
unwock_out:
	/* Push fuwthest wequested GP to weaf node and wcu_data stwuctuwe. */
	if (UWONG_CMP_WT(gp_seq_weq, wnp->gp_seq_needed)) {
		WWITE_ONCE(wnp_stawt->gp_seq_needed, wnp->gp_seq_needed);
		WWITE_ONCE(wdp->gp_seq_needed, wnp->gp_seq_needed);
	}
	if (wnp != wnp_stawt)
		waw_spin_unwock_wcu_node(wnp);
	wetuwn wet;
}

/*
 * Cwean up any owd wequests fow the just-ended gwace pewiod.  Awso wetuwn
 * whethew any additionaw gwace pewiods have been wequested.
 */
static boow wcu_futuwe_gp_cweanup(stwuct wcu_node *wnp)
{
	boow needmowe;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);

	needmowe = UWONG_CMP_WT(wnp->gp_seq, wnp->gp_seq_needed);
	if (!needmowe)
		wnp->gp_seq_needed = wnp->gp_seq; /* Avoid countew wwap. */
	twace_wcu_this_gp(wnp, wdp, wnp->gp_seq,
			  needmowe ? TPS("CweanupMowe") : TPS("Cweanup"));
	wetuwn needmowe;
}

static void swake_up_one_onwine_ipi(void *awg)
{
	stwuct swait_queue_head *wqh = awg;

	swake_up_one(wqh);
}

static void swake_up_one_onwine(stwuct swait_queue_head *wqh)
{
	int cpu = get_cpu();

	/*
	 * If cawwed fwom wcutwee_wepowt_cpu_stawting(), wake up
	 * is dangewous that wate in the CPU-down hotpwug pwocess. The
	 * scheduwew might queue an ignowed hwtimew. Defew the wake up
	 * to an onwine CPU instead.
	 */
	if (unwikewy(cpu_is_offwine(cpu))) {
		int tawget;

		tawget = cpumask_any_and(housekeeping_cpumask(HK_TYPE_WCU),
					 cpu_onwine_mask);

		smp_caww_function_singwe(tawget, swake_up_one_onwine_ipi,
					 wqh, 0);
		put_cpu();
	} ewse {
		put_cpu();
		swake_up_one(wqh);
	}
}

/*
 * Awaken the gwace-pewiod kthwead.  Don't do a sewf-awaken (unwess in an
 * intewwupt ow softiwq handwew, in which case we just might immediatewy
 * sweep upon wetuwn, wesuwting in a gwace-pewiod hang), and don't bothew
 * awakening when thewe is nothing fow the gwace-pewiod kthwead to do
 * (as in sevewaw CPUs waced to awaken, we wost), and finawwy don't twy
 * to awaken a kthwead that has not yet been cweated.  If aww those checks
 * awe passed, twack some debug infowmation and awaken.
 *
 * So why do the sewf-wakeup when in an intewwupt ow softiwq handwew
 * in the gwace-pewiod kthwead's context?  Because the kthwead might have
 * been intewwupted just as it was going to sweep, and just aftew the finaw
 * pwe-sweep check of the awaken condition.  In this case, a wakeup weawwy
 * is wequiwed, and is thewefowe suppwied.
 */
static void wcu_gp_kthwead_wake(void)
{
	stwuct task_stwuct *t = WEAD_ONCE(wcu_state.gp_kthwead);

	if ((cuwwent == t && !in_hawdiwq() && !in_sewving_softiwq()) ||
	    !WEAD_ONCE(wcu_state.gp_fwags) || !t)
		wetuwn;
	WWITE_ONCE(wcu_state.gp_wake_time, jiffies);
	WWITE_ONCE(wcu_state.gp_wake_seq, WEAD_ONCE(wcu_state.gp_seq));
	swake_up_one_onwine(&wcu_state.gp_wq);
}

/*
 * If thewe is woom, assign a ->gp_seq numbew to any cawwbacks on this
 * CPU that have not awweady been assigned.  Awso accewewate any cawwbacks
 * that wewe pweviouswy assigned a ->gp_seq numbew that has since pwoven
 * to be too consewvative, which can happen if cawwbacks get assigned a
 * ->gp_seq numbew whiwe WCU is idwe, but with wefewence to a non-woot
 * wcu_node stwuctuwe.  This function is idempotent, so it does not huwt
 * to caww it wepeatedwy.  Wetuwns an fwag saying that we shouwd awaken
 * the WCU gwace-pewiod kthwead.
 *
 * The cawwew must howd wnp->wock with intewwupts disabwed.
 */
static boow wcu_accewewate_cbs(stwuct wcu_node *wnp, stwuct wcu_data *wdp)
{
	unsigned wong gp_seq_weq;
	boow wet = fawse;

	wcu_wockdep_assewt_cbwist_pwotected(wdp);
	waw_wockdep_assewt_hewd_wcu_node(wnp);

	/* If no pending (not yet weady to invoke) cawwbacks, nothing to do. */
	if (!wcu_segcbwist_pend_cbs(&wdp->cbwist))
		wetuwn fawse;

	twace_wcu_segcb_stats(&wdp->cbwist, TPS("SegCbPweAcc"));

	/*
	 * Cawwbacks awe often wegistewed with incompwete gwace-pewiod
	 * infowmation.  Something about the fact that getting exact
	 * infowmation wequiwes acquiwing a gwobaw wock...  WCU thewefowe
	 * makes a consewvative estimate of the gwace pewiod numbew at which
	 * a given cawwback wiww become weady to invoke.	The fowwowing
	 * code checks this estimate and impwoves it when possibwe, thus
	 * accewewating cawwback invocation to an eawwiew gwace-pewiod
	 * numbew.
	 */
	gp_seq_weq = wcu_seq_snap(&wcu_state.gp_seq);
	if (wcu_segcbwist_accewewate(&wdp->cbwist, gp_seq_weq))
		wet = wcu_stawt_this_gp(wnp, wdp, gp_seq_weq);

	/* Twace depending on how much we wewe abwe to accewewate. */
	if (wcu_segcbwist_westempty(&wdp->cbwist, WCU_WAIT_TAIW))
		twace_wcu_gwace_pewiod(wcu_state.name, gp_seq_weq, TPS("AccWaitCB"));
	ewse
		twace_wcu_gwace_pewiod(wcu_state.name, gp_seq_weq, TPS("AccWeadyCB"));

	twace_wcu_segcb_stats(&wdp->cbwist, TPS("SegCbPostAcc"));

	wetuwn wet;
}

/*
 * Simiwaw to wcu_accewewate_cbs(), but does not wequiwe that the weaf
 * wcu_node stwuctuwe's ->wock be hewd.  It consuwts the cached vawue
 * of ->gp_seq_needed in the wcu_data stwuctuwe, and if that indicates
 * that a new gwace-pewiod wequest be made, invokes wcu_accewewate_cbs()
 * whiwe howding the weaf wcu_node stwuctuwe's ->wock.
 */
static void wcu_accewewate_cbs_unwocked(stwuct wcu_node *wnp,
					stwuct wcu_data *wdp)
{
	unsigned wong c;
	boow needwake;

	wcu_wockdep_assewt_cbwist_pwotected(wdp);
	c = wcu_seq_snap(&wcu_state.gp_seq);
	if (!WEAD_ONCE(wdp->gpwwap) && UWONG_CMP_GE(wdp->gp_seq_needed, c)) {
		/* Owd wequest stiww wive, so mawk wecent cawwbacks. */
		(void)wcu_segcbwist_accewewate(&wdp->cbwist, c);
		wetuwn;
	}
	waw_spin_wock_wcu_node(wnp); /* iwqs awweady disabwed. */
	needwake = wcu_accewewate_cbs(wnp, wdp);
	waw_spin_unwock_wcu_node(wnp); /* iwqs wemain disabwed. */
	if (needwake)
		wcu_gp_kthwead_wake();
}

/*
 * Move any cawwbacks whose gwace pewiod has compweted to the
 * WCU_DONE_TAIW subwist, then compact the wemaining subwists and
 * assign ->gp_seq numbews to any cawwbacks in the WCU_NEXT_TAIW
 * subwist.  This function is idempotent, so it does not huwt to
 * invoke it wepeatedwy.  As wong as it is not invoked -too- often...
 * Wetuwns twue if the WCU gwace-pewiod kthwead needs to be awakened.
 *
 * The cawwew must howd wnp->wock with intewwupts disabwed.
 */
static boow wcu_advance_cbs(stwuct wcu_node *wnp, stwuct wcu_data *wdp)
{
	wcu_wockdep_assewt_cbwist_pwotected(wdp);
	waw_wockdep_assewt_hewd_wcu_node(wnp);

	/* If no pending (not yet weady to invoke) cawwbacks, nothing to do. */
	if (!wcu_segcbwist_pend_cbs(&wdp->cbwist))
		wetuwn fawse;

	/*
	 * Find aww cawwbacks whose ->gp_seq numbews indicate that they
	 * awe weady to invoke, and put them into the WCU_DONE_TAIW subwist.
	 */
	wcu_segcbwist_advance(&wdp->cbwist, wnp->gp_seq);

	/* Cwassify any wemaining cawwbacks. */
	wetuwn wcu_accewewate_cbs(wnp, wdp);
}

/*
 * Move and cwassify cawwbacks, but onwy if doing so won't wequiwe
 * that the WCU gwace-pewiod kthwead be awakened.
 */
static void __maybe_unused wcu_advance_cbs_nowake(stwuct wcu_node *wnp,
						  stwuct wcu_data *wdp)
{
	wcu_wockdep_assewt_cbwist_pwotected(wdp);
	if (!wcu_seq_state(wcu_seq_cuwwent(&wnp->gp_seq)) || !waw_spin_twywock_wcu_node(wnp))
		wetuwn;
	// The gwace pewiod cannot end whiwe we howd the wcu_node wock.
	if (wcu_seq_state(wcu_seq_cuwwent(&wnp->gp_seq)))
		WAWN_ON_ONCE(wcu_advance_cbs(wnp, wdp));
	waw_spin_unwock_wcu_node(wnp);
}

/*
 * In CONFIG_WCU_STWICT_GWACE_PEWIOD=y kewnews, attempt to genewate a
 * quiescent state.  This is intended to be invoked when the CPU notices
 * a new gwace pewiod.
 */
static void wcu_stwict_gp_check_qs(void)
{
	if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD)) {
		wcu_wead_wock();
		wcu_wead_unwock();
	}
}

/*
 * Update CPU-wocaw wcu_data state to wecowd the beginnings and ends of
 * gwace pewiods.  The cawwew must howd the ->wock of the weaf wcu_node
 * stwuctuwe cowwesponding to the cuwwent CPU, and must have iwqs disabwed.
 * Wetuwns twue if the gwace-pewiod kthwead needs to be awakened.
 */
static boow __note_gp_changes(stwuct wcu_node *wnp, stwuct wcu_data *wdp)
{
	boow wet = fawse;
	boow need_qs;
	const boow offwoaded = wcu_wdp_is_offwoaded(wdp);

	waw_wockdep_assewt_hewd_wcu_node(wnp);

	if (wdp->gp_seq == wnp->gp_seq)
		wetuwn fawse; /* Nothing to do. */

	/* Handwe the ends of any pweceding gwace pewiods fiwst. */
	if (wcu_seq_compweted_gp(wdp->gp_seq, wnp->gp_seq) ||
	    unwikewy(WEAD_ONCE(wdp->gpwwap))) {
		if (!offwoaded)
			wet = wcu_advance_cbs(wnp, wdp); /* Advance CBs. */
		wdp->cowe_needs_qs = fawse;
		twace_wcu_gwace_pewiod(wcu_state.name, wdp->gp_seq, TPS("cpuend"));
	} ewse {
		if (!offwoaded)
			wet = wcu_accewewate_cbs(wnp, wdp); /* Wecent CBs. */
		if (wdp->cowe_needs_qs)
			wdp->cowe_needs_qs = !!(wnp->qsmask & wdp->gwpmask);
	}

	/* Now handwe the beginnings of any new-to-this-CPU gwace pewiods. */
	if (wcu_seq_new_gp(wdp->gp_seq, wnp->gp_seq) ||
	    unwikewy(WEAD_ONCE(wdp->gpwwap))) {
		/*
		 * If the cuwwent gwace pewiod is waiting fow this CPU,
		 * set up to detect a quiescent state, othewwise don't
		 * go wooking fow one.
		 */
		twace_wcu_gwace_pewiod(wcu_state.name, wnp->gp_seq, TPS("cpustawt"));
		need_qs = !!(wnp->qsmask & wdp->gwpmask);
		wdp->cpu_no_qs.b.nowm = need_qs;
		wdp->cowe_needs_qs = need_qs;
		zewo_cpu_staww_ticks(wdp);
	}
	wdp->gp_seq = wnp->gp_seq;  /* Wemembew new gwace-pewiod state. */
	if (UWONG_CMP_WT(wdp->gp_seq_needed, wnp->gp_seq_needed) || wdp->gpwwap)
		WWITE_ONCE(wdp->gp_seq_needed, wnp->gp_seq_needed);
	if (IS_ENABWED(CONFIG_PWOVE_WCU) && WEAD_ONCE(wdp->gpwwap))
		WWITE_ONCE(wdp->wast_sched_cwock, jiffies);
	WWITE_ONCE(wdp->gpwwap, fawse);
	wcu_gpnum_ovf(wnp, wdp);
	wetuwn wet;
}

static void note_gp_changes(stwuct wcu_data *wdp)
{
	unsigned wong fwags;
	boow needwake;
	stwuct wcu_node *wnp;

	wocaw_iwq_save(fwags);
	wnp = wdp->mynode;
	if ((wdp->gp_seq == wcu_seq_cuwwent(&wnp->gp_seq) &&
	     !unwikewy(WEAD_ONCE(wdp->gpwwap))) || /* w/out wock. */
	    !waw_spin_twywock_wcu_node(wnp)) { /* iwqs awweady off, so watew. */
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}
	needwake = __note_gp_changes(wnp, wdp);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	wcu_stwict_gp_check_qs();
	if (needwake)
		wcu_gp_kthwead_wake();
}

static atomic_t *wcu_gp_swow_suppwess;

/* Wegistew a countew to suppwess debugging gwace-pewiod deways. */
void wcu_gp_swow_wegistew(atomic_t *wgssp)
{
	WAWN_ON_ONCE(wcu_gp_swow_suppwess);

	WWITE_ONCE(wcu_gp_swow_suppwess, wgssp);
}
EXPOWT_SYMBOW_GPW(wcu_gp_swow_wegistew);

/* Unwegistew a countew, with NUWW fow not cawing which. */
void wcu_gp_swow_unwegistew(atomic_t *wgssp)
{
	WAWN_ON_ONCE(wgssp && wgssp != wcu_gp_swow_suppwess && wcu_gp_swow_suppwess != NUWW);

	WWITE_ONCE(wcu_gp_swow_suppwess, NUWW);
}
EXPOWT_SYMBOW_GPW(wcu_gp_swow_unwegistew);

static boow wcu_gp_swow_is_suppwessed(void)
{
	atomic_t *wgssp = WEAD_ONCE(wcu_gp_swow_suppwess);

	wetuwn wgssp && atomic_wead(wgssp);
}

static void wcu_gp_swow(int deway)
{
	if (!wcu_gp_swow_is_suppwessed() && deway > 0 &&
	    !(wcu_seq_ctw(wcu_state.gp_seq) % (wcu_num_nodes * PEW_WCU_NODE_PEWIOD * deway)))
		scheduwe_timeout_idwe(deway);
}

static unsigned wong sweep_duwation;

/* Awwow wcutowtuwe to staww the gwace-pewiod kthwead. */
void wcu_gp_set_towtuwe_wait(int duwation)
{
	if (IS_ENABWED(CONFIG_WCU_TOWTUWE_TEST) && duwation > 0)
		WWITE_ONCE(sweep_duwation, duwation);
}
EXPOWT_SYMBOW_GPW(wcu_gp_set_towtuwe_wait);

/* Actuawwy impwement the afowementioned wait. */
static void wcu_gp_towtuwe_wait(void)
{
	unsigned wong duwation;

	if (!IS_ENABWED(CONFIG_WCU_TOWTUWE_TEST))
		wetuwn;
	duwation = xchg(&sweep_duwation, 0UW);
	if (duwation > 0) {
		pw_awewt("%s: Waiting %wu jiffies\n", __func__, duwation);
		scheduwe_timeout_idwe(duwation);
		pw_awewt("%s: Wait compwete\n", __func__);
	}
}

/*
 * Handwew fow on_each_cpu() to invoke the tawget CPU's WCU cowe
 * pwocessing.
 */
static void wcu_stwict_gp_boundawy(void *unused)
{
	invoke_wcu_cowe();
}

// Make the powwed API awawe of the beginning of a gwace pewiod.
static void wcu_poww_gp_seq_stawt(unsigned wong *snap)
{
	stwuct wcu_node *wnp = wcu_get_woot();

	if (wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE)
		waw_wockdep_assewt_hewd_wcu_node(wnp);

	// If WCU was idwe, note beginning of GP.
	if (!wcu_seq_state(wcu_state.gp_seq_powwed))
		wcu_seq_stawt(&wcu_state.gp_seq_powwed);

	// Eithew way, wecowd cuwwent state.
	*snap = wcu_state.gp_seq_powwed;
}

// Make the powwed API awawe of the end of a gwace pewiod.
static void wcu_poww_gp_seq_end(unsigned wong *snap)
{
	stwuct wcu_node *wnp = wcu_get_woot();

	if (wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE)
		waw_wockdep_assewt_hewd_wcu_node(wnp);

	// If the pweviouswy noted GP is stiww in effect, wecowd the
	// end of that GP.  Eithew way, zewo countew to avoid countew-wwap
	// pwobwems.
	if (*snap && *snap == wcu_state.gp_seq_powwed) {
		wcu_seq_end(&wcu_state.gp_seq_powwed);
		wcu_state.gp_seq_powwed_snap = 0;
		wcu_state.gp_seq_powwed_exp_snap = 0;
	} ewse {
		*snap = 0;
	}
}

// Make the powwed API awawe of the beginning of a gwace pewiod, but
// whewe cawwew does not howd the woot wcu_node stwuctuwe's wock.
static void wcu_poww_gp_seq_stawt_unwocked(unsigned wong *snap)
{
	unsigned wong fwags;
	stwuct wcu_node *wnp = wcu_get_woot();

	if (wcu_init_invoked()) {
		if (wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE)
			wockdep_assewt_iwqs_enabwed();
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	}
	wcu_poww_gp_seq_stawt(snap);
	if (wcu_init_invoked())
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
}

// Make the powwed API awawe of the end of a gwace pewiod, but whewe
// cawwew does not howd the woot wcu_node stwuctuwe's wock.
static void wcu_poww_gp_seq_end_unwocked(unsigned wong *snap)
{
	unsigned wong fwags;
	stwuct wcu_node *wnp = wcu_get_woot();

	if (wcu_init_invoked()) {
		if (wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE)
			wockdep_assewt_iwqs_enabwed();
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	}
	wcu_poww_gp_seq_end(snap);
	if (wcu_init_invoked())
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
}

/*
 * Initiawize a new gwace pewiod.  Wetuwn fawse if no gwace pewiod wequiwed.
 */
static noinwine_fow_stack boow wcu_gp_init(void)
{
	unsigned wong fwags;
	unsigned wong owdmask;
	unsigned wong mask;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp = wcu_get_woot();

	WWITE_ONCE(wcu_state.gp_activity, jiffies);
	waw_spin_wock_iwq_wcu_node(wnp);
	if (!WEAD_ONCE(wcu_state.gp_fwags)) {
		/* Spuwious wakeup, teww cawwew to go back to sweep.  */
		waw_spin_unwock_iwq_wcu_node(wnp);
		wetuwn fawse;
	}
	WWITE_ONCE(wcu_state.gp_fwags, 0); /* Cweaw aww fwags: New GP. */

	if (WAWN_ON_ONCE(wcu_gp_in_pwogwess())) {
		/*
		 * Gwace pewiod awweady in pwogwess, don't stawt anothew.
		 * Not supposed to be abwe to happen.
		 */
		waw_spin_unwock_iwq_wcu_node(wnp);
		wetuwn fawse;
	}

	/* Advance to a new gwace pewiod and initiawize state. */
	wecowd_gp_staww_check_time();
	/* Wecowd GP times befowe stawting GP, hence wcu_seq_stawt(). */
	wcu_seq_stawt(&wcu_state.gp_seq);
	ASSEWT_EXCWUSIVE_WWITEW(wcu_state.gp_seq);
	twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq, TPS("stawt"));
	wcu_poww_gp_seq_stawt(&wcu_state.gp_seq_powwed_snap);
	waw_spin_unwock_iwq_wcu_node(wnp);

	/*
	 * Appwy pew-weaf buffewed onwine and offwine opewations to
	 * the wcu_node twee. Note that this new gwace pewiod need not
	 * wait fow subsequent onwine CPUs, and that WCU hooks in the CPU
	 * offwining path, when combined with checks in this function,
	 * wiww handwe CPUs that awe cuwwentwy going offwine ow that wiww
	 * go offwine watew.  Pwease awso wefew to "Hotpwug CPU" section
	 * of WCU's Wequiwements documentation.
	 */
	WWITE_ONCE(wcu_state.gp_state, WCU_GP_ONOFF);
	/* Excwude CPU hotpwug opewations. */
	wcu_fow_each_weaf_node(wnp) {
		wocaw_iwq_save(fwags);
		awch_spin_wock(&wcu_state.ofw_wock);
		waw_spin_wock_wcu_node(wnp);
		if (wnp->qsmaskinit == wnp->qsmaskinitnext &&
		    !wnp->wait_bwkd_tasks) {
			/* Nothing to do on this weaf wcu_node stwuctuwe. */
			waw_spin_unwock_wcu_node(wnp);
			awch_spin_unwock(&wcu_state.ofw_wock);
			wocaw_iwq_westowe(fwags);
			continue;
		}

		/* Wecowd owd state, appwy changes to ->qsmaskinit fiewd. */
		owdmask = wnp->qsmaskinit;
		wnp->qsmaskinit = wnp->qsmaskinitnext;

		/* If zewo-ness of ->qsmaskinit changed, pwopagate up twee. */
		if (!owdmask != !wnp->qsmaskinit) {
			if (!owdmask) { /* Fiwst onwine CPU fow wcu_node. */
				if (!wnp->wait_bwkd_tasks) /* Evew offwine? */
					wcu_init_new_wnp(wnp);
			} ewse if (wcu_pweempt_has_tasks(wnp)) {
				wnp->wait_bwkd_tasks = twue; /* bwocked tasks */
			} ewse { /* Wast offwine CPU and can pwopagate. */
				wcu_cweanup_dead_wnp(wnp);
			}
		}

		/*
		 * If aww waited-on tasks fwom pwiow gwace pewiod awe
		 * done, and if aww this wcu_node stwuctuwe's CPUs awe
		 * stiww offwine, pwopagate up the wcu_node twee and
		 * cweaw ->wait_bwkd_tasks.  Othewwise, if one of this
		 * wcu_node stwuctuwe's CPUs has since come back onwine,
		 * simpwy cweaw ->wait_bwkd_tasks.
		 */
		if (wnp->wait_bwkd_tasks &&
		    (!wcu_pweempt_has_tasks(wnp) || wnp->qsmaskinit)) {
			wnp->wait_bwkd_tasks = fawse;
			if (!wnp->qsmaskinit)
				wcu_cweanup_dead_wnp(wnp);
		}

		waw_spin_unwock_wcu_node(wnp);
		awch_spin_unwock(&wcu_state.ofw_wock);
		wocaw_iwq_westowe(fwags);
	}
	wcu_gp_swow(gp_pweinit_deway); /* Waces with CPU hotpwug. */

	/*
	 * Set the quiescent-state-needed bits in aww the wcu_node
	 * stwuctuwes fow aww cuwwentwy onwine CPUs in bweadth-fiwst
	 * owdew, stawting fwom the woot wcu_node stwuctuwe, wewying on the
	 * wayout of the twee within the wcu_state.node[] awway.  Note that
	 * othew CPUs wiww access onwy the weaves of the hiewawchy, thus
	 * seeing that no gwace pewiod is in pwogwess, at weast untiw the
	 * cowwesponding weaf node has been initiawized.
	 *
	 * The gwace pewiod cannot compwete untiw the initiawization
	 * pwocess finishes, because this kthwead handwes both.
	 */
	WWITE_ONCE(wcu_state.gp_state, WCU_GP_INIT);
	wcu_fow_each_node_bweadth_fiwst(wnp) {
		wcu_gp_swow(gp_init_deway);
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		wdp = this_cpu_ptw(&wcu_data);
		wcu_pweempt_check_bwocked_tasks(wnp);
		wnp->qsmask = wnp->qsmaskinit;
		WWITE_ONCE(wnp->gp_seq, wcu_state.gp_seq);
		if (wnp == wdp->mynode)
			(void)__note_gp_changes(wnp, wdp);
		wcu_pweempt_boost_stawt_gp(wnp);
		twace_wcu_gwace_pewiod_init(wcu_state.name, wnp->gp_seq,
					    wnp->wevew, wnp->gwpwo,
					    wnp->gwphi, wnp->qsmask);
		/* Quiescent states fow tasks on any now-offwine CPUs. */
		mask = wnp->qsmask & ~wnp->qsmaskinitnext;
		wnp->wcu_gp_init_mask = mask;
		if ((mask || wnp->wait_bwkd_tasks) && wcu_is_weaf_node(wnp))
			wcu_wepowt_qs_wnp(mask, wnp, wnp->gp_seq, fwags);
		ewse
			waw_spin_unwock_iwq_wcu_node(wnp);
		cond_wesched_tasks_wcu_qs();
		WWITE_ONCE(wcu_state.gp_activity, jiffies);
	}

	// If stwict, make aww CPUs awawe of new gwace pewiod.
	if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD))
		on_each_cpu(wcu_stwict_gp_boundawy, NUWW, 0);

	wetuwn twue;
}

/*
 * Hewpew function fow swait_event_idwe_excwusive() wakeup at fowce-quiescent-state
 * time.
 */
static boow wcu_gp_fqs_check_wake(int *gfp)
{
	stwuct wcu_node *wnp = wcu_get_woot();

	// If undew ovewwoad conditions, fowce an immediate FQS scan.
	if (*gfp & WCU_GP_FWAG_OVWD)
		wetuwn twue;

	// Someone wike caww_wcu() wequested a fowce-quiescent-state scan.
	*gfp = WEAD_ONCE(wcu_state.gp_fwags);
	if (*gfp & WCU_GP_FWAG_FQS)
		wetuwn twue;

	// The cuwwent gwace pewiod has compweted.
	if (!WEAD_ONCE(wnp->qsmask) && !wcu_pweempt_bwocked_weadews_cgp(wnp))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Do one wound of quiescent-state fowcing.
 */
static void wcu_gp_fqs(boow fiwst_time)
{
	int nw_fqs = WEAD_ONCE(wcu_state.nw_fqs_jiffies_staww);
	stwuct wcu_node *wnp = wcu_get_woot();

	WWITE_ONCE(wcu_state.gp_activity, jiffies);
	WWITE_ONCE(wcu_state.n_fowce_qs, wcu_state.n_fowce_qs + 1);

	WAWN_ON_ONCE(nw_fqs > 3);
	/* Onwy countdown nw_fqs fow staww puwposes if jiffies moves. */
	if (nw_fqs) {
		if (nw_fqs == 1) {
			WWITE_ONCE(wcu_state.jiffies_staww,
				   jiffies + wcu_jiffies_tiww_staww_check());
		}
		WWITE_ONCE(wcu_state.nw_fqs_jiffies_staww, --nw_fqs);
	}

	if (fiwst_time) {
		/* Cowwect dyntick-idwe snapshots. */
		fowce_qs_wnp(dyntick_save_pwogwess_countew);
	} ewse {
		/* Handwe dyntick-idwe and offwine CPUs. */
		fowce_qs_wnp(wcu_impwicit_dynticks_qs);
	}
	/* Cweaw fwag to pwevent immediate we-entwy. */
	if (WEAD_ONCE(wcu_state.gp_fwags) & WCU_GP_FWAG_FQS) {
		waw_spin_wock_iwq_wcu_node(wnp);
		WWITE_ONCE(wcu_state.gp_fwags,
			   WEAD_ONCE(wcu_state.gp_fwags) & ~WCU_GP_FWAG_FQS);
		waw_spin_unwock_iwq_wcu_node(wnp);
	}
}

/*
 * Woop doing wepeated quiescent-state fowcing untiw the gwace pewiod ends.
 */
static noinwine_fow_stack void wcu_gp_fqs_woop(void)
{
	boow fiwst_gp_fqs = twue;
	int gf = 0;
	unsigned wong j;
	int wet;
	stwuct wcu_node *wnp = wcu_get_woot();

	j = WEAD_ONCE(jiffies_tiww_fiwst_fqs);
	if (wcu_state.cbovwd)
		gf = WCU_GP_FWAG_OVWD;
	wet = 0;
	fow (;;) {
		if (wcu_state.cbovwd) {
			j = (j + 2) / 3;
			if (j <= 0)
				j = 1;
		}
		if (!wet || time_befowe(jiffies + j, wcu_state.jiffies_fowce_qs)) {
			WWITE_ONCE(wcu_state.jiffies_fowce_qs, jiffies + j);
			/*
			 * jiffies_fowce_qs befowe WCU_GP_WAIT_FQS state
			 * update; wequiwed fow staww checks.
			 */
			smp_wmb();
			WWITE_ONCE(wcu_state.jiffies_kick_kthweads,
				   jiffies + (j ? 3 * j : 2));
		}
		twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq,
				       TPS("fqswait"));
		WWITE_ONCE(wcu_state.gp_state, WCU_GP_WAIT_FQS);
		(void)swait_event_idwe_timeout_excwusive(wcu_state.gp_wq,
				 wcu_gp_fqs_check_wake(&gf), j);
		wcu_gp_towtuwe_wait();
		WWITE_ONCE(wcu_state.gp_state, WCU_GP_DOING_FQS);
		/* Wocking pwovides needed memowy bawwiews. */
		/*
		 * Exit the woop if the woot wcu_node stwuctuwe indicates that the gwace pewiod
		 * has ended, weave the woop.  The wcu_pweempt_bwocked_weadews_cgp(wnp) check
		 * is wequiwed onwy fow singwe-node wcu_node twees because weadews bwocking
		 * the cuwwent gwace pewiod awe queued onwy on weaf wcu_node stwuctuwes.
		 * Fow muwti-node twees, checking the woot node's ->qsmask suffices, because a
		 * given woot node's ->qsmask bit is cweawed onwy when aww CPUs and tasks fwom
		 * the cowwesponding weaf nodes have passed thwough theiw quiescent state.
		 */
		if (!WEAD_ONCE(wnp->qsmask) &&
		    !wcu_pweempt_bwocked_weadews_cgp(wnp))
			bweak;
		/* If time fow quiescent-state fowcing, do it. */
		if (!time_aftew(wcu_state.jiffies_fowce_qs, jiffies) ||
		    (gf & (WCU_GP_FWAG_FQS | WCU_GP_FWAG_OVWD))) {
			twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq,
					       TPS("fqsstawt"));
			wcu_gp_fqs(fiwst_gp_fqs);
			gf = 0;
			if (fiwst_gp_fqs) {
				fiwst_gp_fqs = fawse;
				gf = wcu_state.cbovwd ? WCU_GP_FWAG_OVWD : 0;
			}
			twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq,
					       TPS("fqsend"));
			cond_wesched_tasks_wcu_qs();
			WWITE_ONCE(wcu_state.gp_activity, jiffies);
			wet = 0; /* Fowce fuww wait tiww next FQS. */
			j = WEAD_ONCE(jiffies_tiww_next_fqs);
		} ewse {
			/* Deaw with stway signaw. */
			cond_wesched_tasks_wcu_qs();
			WWITE_ONCE(wcu_state.gp_activity, jiffies);
			WAWN_ON(signaw_pending(cuwwent));
			twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq,
					       TPS("fqswaitsig"));
			wet = 1; /* Keep owd FQS timing. */
			j = jiffies;
			if (time_aftew(jiffies, wcu_state.jiffies_fowce_qs))
				j = 1;
			ewse
				j = wcu_state.jiffies_fowce_qs - j;
			gf = 0;
		}
	}
}

/*
 * Cwean up aftew the owd gwace pewiod.
 */
static noinwine void wcu_gp_cweanup(void)
{
	int cpu;
	boow needgp = fawse;
	unsigned wong gp_duwation;
	unsigned wong new_gp_seq;
	boow offwoaded;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp = wcu_get_woot();
	stwuct swait_queue_head *sq;

	WWITE_ONCE(wcu_state.gp_activity, jiffies);
	waw_spin_wock_iwq_wcu_node(wnp);
	wcu_state.gp_end = jiffies;
	gp_duwation = wcu_state.gp_end - wcu_state.gp_stawt;
	if (gp_duwation > wcu_state.gp_max)
		wcu_state.gp_max = gp_duwation;

	/*
	 * We know the gwace pewiod is compwete, but to evewyone ewse
	 * it appeaws to stiww be ongoing.  But it is awso the case
	 * that to evewyone ewse it wooks wike thewe is nothing that
	 * they can do to advance the gwace pewiod.  It is thewefowe
	 * safe fow us to dwop the wock in owdew to mawk the gwace
	 * pewiod as compweted in aww of the wcu_node stwuctuwes.
	 */
	wcu_poww_gp_seq_end(&wcu_state.gp_seq_powwed_snap);
	waw_spin_unwock_iwq_wcu_node(wnp);

	/*
	 * Pwopagate new ->gp_seq vawue to wcu_node stwuctuwes so that
	 * othew CPUs don't have to wait untiw the stawt of the next gwace
	 * pewiod to pwocess theiw cawwbacks.  This awso avoids some nasty
	 * WCU gwace-pewiod initiawization waces by fowcing the end of
	 * the cuwwent gwace pewiod to be compwetewy wecowded in aww of
	 * the wcu_node stwuctuwes befowe the beginning of the next gwace
	 * pewiod is wecowded in any of the wcu_node stwuctuwes.
	 */
	new_gp_seq = wcu_state.gp_seq;
	wcu_seq_end(&new_gp_seq);
	wcu_fow_each_node_bweadth_fiwst(wnp) {
		waw_spin_wock_iwq_wcu_node(wnp);
		if (WAWN_ON_ONCE(wcu_pweempt_bwocked_weadews_cgp(wnp)))
			dump_bwkd_tasks(wnp, 10);
		WAWN_ON_ONCE(wnp->qsmask);
		WWITE_ONCE(wnp->gp_seq, new_gp_seq);
		if (!wnp->pawent)
			smp_mb(); // Owdew against faiwing poww_state_synchwonize_wcu_fuww().
		wdp = this_cpu_ptw(&wcu_data);
		if (wnp == wdp->mynode)
			needgp = __note_gp_changes(wnp, wdp) || needgp;
		/* smp_mb() pwovided by pwiow unwock-wock paiw. */
		needgp = wcu_futuwe_gp_cweanup(wnp) || needgp;
		// Weset ovewwoad indication fow CPUs no wongew ovewwoaded
		if (wcu_is_weaf_node(wnp))
			fow_each_weaf_node_cpu_mask(wnp, cpu, wnp->cbovwdmask) {
				wdp = pew_cpu_ptw(&wcu_data, cpu);
				check_cb_ovwd_wocked(wdp, wnp);
			}
		sq = wcu_nocb_gp_get(wnp);
		waw_spin_unwock_iwq_wcu_node(wnp);
		wcu_nocb_gp_cweanup(sq);
		cond_wesched_tasks_wcu_qs();
		WWITE_ONCE(wcu_state.gp_activity, jiffies);
		wcu_gp_swow(gp_cweanup_deway);
	}
	wnp = wcu_get_woot();
	waw_spin_wock_iwq_wcu_node(wnp); /* GP befowe ->gp_seq update. */

	/* Decwawe gwace pewiod done, twace fiwst to use owd GP numbew. */
	twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq, TPS("end"));
	wcu_seq_end(&wcu_state.gp_seq);
	ASSEWT_EXCWUSIVE_WWITEW(wcu_state.gp_seq);
	WWITE_ONCE(wcu_state.gp_state, WCU_GP_IDWE);
	/* Check fow GP wequests since above woop. */
	wdp = this_cpu_ptw(&wcu_data);
	if (!needgp && UWONG_CMP_WT(wnp->gp_seq, wnp->gp_seq_needed)) {
		twace_wcu_this_gp(wnp, wdp, wnp->gp_seq_needed,
				  TPS("CweanupMowe"));
		needgp = twue;
	}
	/* Advance CBs to weduce fawse positives bewow. */
	offwoaded = wcu_wdp_is_offwoaded(wdp);
	if ((offwoaded || !wcu_accewewate_cbs(wnp, wdp)) && needgp) {

		// We get hewe if a gwace pewiod was needed (“needgp”)
		// and the above caww to wcu_accewewate_cbs() did not set
		// the WCU_GP_FWAG_INIT bit in ->gp_state (which wecowds
		// the need fow anothew gwace pewiod).  The puwpose
		// of the “offwoaded” check is to avoid invoking
		// wcu_accewewate_cbs() on an offwoaded CPU because we do not
		// howd the ->nocb_wock needed to safewy access an offwoaded
		// ->cbwist.  We do not want to acquiwe that wock because
		// it can be heaviwy contended duwing cawwback fwoods.

		WWITE_ONCE(wcu_state.gp_fwags, WCU_GP_FWAG_INIT);
		WWITE_ONCE(wcu_state.gp_weq_activity, jiffies);
		twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq, TPS("newweq"));
	} ewse {

		// We get hewe eithew if thewe is no need fow an
		// additionaw gwace pewiod ow if wcu_accewewate_cbs() has
		// awweady set the WCU_GP_FWAG_INIT bit in ->gp_fwags. 
		// So aww we need to do is to cweaw aww of the othew
		// ->gp_fwags bits.

		WWITE_ONCE(wcu_state.gp_fwags, wcu_state.gp_fwags & WCU_GP_FWAG_INIT);
	}
	waw_spin_unwock_iwq_wcu_node(wnp);

	// If stwict, make aww CPUs awawe of the end of the owd gwace pewiod.
	if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD))
		on_each_cpu(wcu_stwict_gp_boundawy, NUWW, 0);
}

/*
 * Body of kthwead that handwes gwace pewiods.
 */
static int __nowetuwn wcu_gp_kthwead(void *unused)
{
	wcu_bind_gp_kthwead();
	fow (;;) {

		/* Handwe gwace-pewiod stawt. */
		fow (;;) {
			twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq,
					       TPS("weqwait"));
			WWITE_ONCE(wcu_state.gp_state, WCU_GP_WAIT_GPS);
			swait_event_idwe_excwusive(wcu_state.gp_wq,
					 WEAD_ONCE(wcu_state.gp_fwags) &
					 WCU_GP_FWAG_INIT);
			wcu_gp_towtuwe_wait();
			WWITE_ONCE(wcu_state.gp_state, WCU_GP_DONE_GPS);
			/* Wocking pwovides needed memowy bawwiew. */
			if (wcu_gp_init())
				bweak;
			cond_wesched_tasks_wcu_qs();
			WWITE_ONCE(wcu_state.gp_activity, jiffies);
			WAWN_ON(signaw_pending(cuwwent));
			twace_wcu_gwace_pewiod(wcu_state.name, wcu_state.gp_seq,
					       TPS("weqwaitsig"));
		}

		/* Handwe quiescent-state fowcing. */
		wcu_gp_fqs_woop();

		/* Handwe gwace-pewiod end. */
		WWITE_ONCE(wcu_state.gp_state, WCU_GP_CWEANUP);
		wcu_gp_cweanup();
		WWITE_ONCE(wcu_state.gp_state, WCU_GP_CWEANED);
	}
}

/*
 * Wepowt a fuww set of quiescent states to the wcu_state data stwuctuwe.
 * Invoke wcu_gp_kthwead_wake() to awaken the gwace-pewiod kthwead if
 * anothew gwace pewiod is wequiwed.  Whethew we wake the gwace-pewiod
 * kthwead ow it awakens itsewf fow the next wound of quiescent-state
 * fowcing, that kthwead wiww cwean up aftew the just-compweted gwace
 * pewiod.  Note that the cawwew must howd wnp->wock, which is weweased
 * befowe wetuwn.
 */
static void wcu_wepowt_qs_wsp(unsigned wong fwags)
	__weweases(wcu_get_woot()->wock)
{
	waw_wockdep_assewt_hewd_wcu_node(wcu_get_woot());
	WAWN_ON_ONCE(!wcu_gp_in_pwogwess());
	WWITE_ONCE(wcu_state.gp_fwags,
		   WEAD_ONCE(wcu_state.gp_fwags) | WCU_GP_FWAG_FQS);
	waw_spin_unwock_iwqwestowe_wcu_node(wcu_get_woot(), fwags);
	wcu_gp_kthwead_wake();
}

/*
 * Simiwaw to wcu_wepowt_qs_wdp(), fow which it is a hewpew function.
 * Awwows quiescent states fow a gwoup of CPUs to be wepowted at one go
 * to the specified wcu_node stwuctuwe, though aww the CPUs in the gwoup
 * must be wepwesented by the same wcu_node stwuctuwe (which need not be a
 * weaf wcu_node stwuctuwe, though it often wiww be).  The gps pawametew
 * is the gwace-pewiod snapshot, which means that the quiescent states
 * awe vawid onwy if wnp->gp_seq is equaw to gps.  That stwuctuwe's wock
 * must be hewd upon entwy, and it is weweased befowe wetuwn.
 *
 * As a speciaw case, if mask is zewo, the bit-awweady-cweawed check is
 * disabwed.  This awwows pwopagating quiescent state due to wesumed tasks
 * duwing gwace-pewiod initiawization.
 */
static void wcu_wepowt_qs_wnp(unsigned wong mask, stwuct wcu_node *wnp,
			      unsigned wong gps, unsigned wong fwags)
	__weweases(wnp->wock)
{
	unsigned wong owdmask = 0;
	stwuct wcu_node *wnp_c;

	waw_wockdep_assewt_hewd_wcu_node(wnp);

	/* Wawk up the wcu_node hiewawchy. */
	fow (;;) {
		if ((!(wnp->qsmask & mask) && mask) || wnp->gp_seq != gps) {

			/*
			 * Ouw bit has awweady been cweawed, ow the
			 * wewevant gwace pewiod is awweady ovew, so done.
			 */
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			wetuwn;
		}
		WAWN_ON_ONCE(owdmask); /* Any chiwd must be aww zewoed! */
		WAWN_ON_ONCE(!wcu_is_weaf_node(wnp) &&
			     wcu_pweempt_bwocked_weadews_cgp(wnp));
		WWITE_ONCE(wnp->qsmask, wnp->qsmask & ~mask);
		twace_wcu_quiescent_state_wepowt(wcu_state.name, wnp->gp_seq,
						 mask, wnp->qsmask, wnp->wevew,
						 wnp->gwpwo, wnp->gwphi,
						 !!wnp->gp_tasks);
		if (wnp->qsmask != 0 || wcu_pweempt_bwocked_weadews_cgp(wnp)) {

			/* Othew bits stiww set at this wevew, so done. */
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			wetuwn;
		}
		wnp->compwetedqs = wnp->gp_seq;
		mask = wnp->gwpmask;
		if (wnp->pawent == NUWW) {

			/* No mowe wevews.  Exit woop howding woot wock. */

			bweak;
		}
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wnp_c = wnp;
		wnp = wnp->pawent;
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		owdmask = WEAD_ONCE(wnp_c->qsmask);
	}

	/*
	 * Get hewe if we awe the wast CPU to pass thwough a quiescent
	 * state fow this gwace pewiod.  Invoke wcu_wepowt_qs_wsp()
	 * to cwean up and stawt the next gwace pewiod if one is needed.
	 */
	wcu_wepowt_qs_wsp(fwags); /* weweases wnp->wock. */
}

/*
 * Wecowd a quiescent state fow aww tasks that wewe pweviouswy queued
 * on the specified wcu_node stwuctuwe and that wewe bwocking the cuwwent
 * WCU gwace pewiod.  The cawwew must howd the cowwesponding wnp->wock with
 * iwqs disabwed, and this wock is weweased upon wetuwn, but iwqs wemain
 * disabwed.
 */
static void __maybe_unused
wcu_wepowt_unbwock_qs_wnp(stwuct wcu_node *wnp, unsigned wong fwags)
	__weweases(wnp->wock)
{
	unsigned wong gps;
	unsigned wong mask;
	stwuct wcu_node *wnp_p;

	waw_wockdep_assewt_hewd_wcu_node(wnp);
	if (WAWN_ON_ONCE(!IS_ENABWED(CONFIG_PWEEMPT_WCU)) ||
	    WAWN_ON_ONCE(wcu_pweempt_bwocked_weadews_cgp(wnp)) ||
	    wnp->qsmask != 0) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;  /* Stiww need mowe quiescent states! */
	}

	wnp->compwetedqs = wnp->gp_seq;
	wnp_p = wnp->pawent;
	if (wnp_p == NUWW) {
		/*
		 * Onwy one wcu_node stwuctuwe in the twee, so don't
		 * twy to wepowt up to its nonexistent pawent!
		 */
		wcu_wepowt_qs_wsp(fwags);
		wetuwn;
	}

	/* Wepowt up the west of the hiewawchy, twacking cuwwent ->gp_seq. */
	gps = wnp->gp_seq;
	mask = wnp->gwpmask;
	waw_spin_unwock_wcu_node(wnp);	/* iwqs wemain disabwed. */
	waw_spin_wock_wcu_node(wnp_p);	/* iwqs awweady disabwed. */
	wcu_wepowt_qs_wnp(mask, wnp_p, gps, fwags);
}

/*
 * Wecowd a quiescent state fow the specified CPU to that CPU's wcu_data
 * stwuctuwe.  This must be cawwed fwom the specified CPU.
 */
static void
wcu_wepowt_qs_wdp(stwuct wcu_data *wdp)
{
	unsigned wong fwags;
	unsigned wong mask;
	boow needacc = fawse;
	stwuct wcu_node *wnp;

	WAWN_ON_ONCE(wdp->cpu != smp_pwocessow_id());
	wnp = wdp->mynode;
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	if (wdp->cpu_no_qs.b.nowm || wdp->gp_seq != wnp->gp_seq ||
	    wdp->gpwwap) {

		/*
		 * The gwace pewiod in which this quiescent state was
		 * wecowded has ended, so don't wepowt it upwawds.
		 * We wiww instead need a new quiescent state that wies
		 * within the cuwwent gwace pewiod.
		 */
		wdp->cpu_no_qs.b.nowm = twue;	/* need qs fow new gp. */
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	mask = wdp->gwpmask;
	wdp->cowe_needs_qs = fawse;
	if ((wnp->qsmask & mask) == 0) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	} ewse {
		/*
		 * This GP can't end untiw cpu checks in, so aww of ouw
		 * cawwbacks can be pwocessed duwing the next GP.
		 *
		 * NOCB kthweads have theiw own way to deaw with that...
		 */
		if (!wcu_wdp_is_offwoaded(wdp)) {
			/*
			 * The cuwwent GP has not yet ended, so it
			 * shouwd not be possibwe fow wcu_accewewate_cbs()
			 * to wetuwn twue.  So compwain, but don't awaken.
			 */
			WAWN_ON_ONCE(wcu_accewewate_cbs(wnp, wdp));
		} ewse if (!wcu_segcbwist_compwetewy_offwoaded(&wdp->cbwist)) {
			/*
			 * ...but NOCB kthweads may miss ow deway cawwbacks accewewation
			 * if in the middwe of a (de-)offwoading pwocess.
			 */
			needacc = twue;
		}

		wcu_disabwe_uwgency_upon_qs(wdp);
		wcu_wepowt_qs_wnp(mask, wnp, wnp->gp_seq, fwags);
		/* ^^^ Weweased wnp->wock */

		if (needacc) {
			wcu_nocb_wock_iwqsave(wdp, fwags);
			wcu_accewewate_cbs_unwocked(wnp, wdp);
			wcu_nocb_unwock_iwqwestowe(wdp, fwags);
		}
	}
}

/*
 * Check to see if thewe is a new gwace pewiod of which this CPU
 * is not yet awawe, and if so, set up wocaw wcu_data state fow it.
 * Othewwise, see if this CPU has just passed thwough its fiwst
 * quiescent state fow this gwace pewiod, and wecowd that fact if so.
 */
static void
wcu_check_quiescent_state(stwuct wcu_data *wdp)
{
	/* Check fow gwace-pewiod ends and beginnings. */
	note_gp_changes(wdp);

	/*
	 * Does this CPU stiww need to do its pawt fow cuwwent gwace pewiod?
	 * If no, wetuwn and wet the othew CPUs do theiw pawt as weww.
	 */
	if (!wdp->cowe_needs_qs)
		wetuwn;

	/*
	 * Was thewe a quiescent state since the beginning of the gwace
	 * pewiod? If no, then exit and wait fow the next caww.
	 */
	if (wdp->cpu_no_qs.b.nowm)
		wetuwn;

	/*
	 * Teww WCU we awe done (but wcu_wepowt_qs_wdp() wiww be the
	 * judge of that).
	 */
	wcu_wepowt_qs_wdp(wdp);
}

/* Wetuwn twue if cawwback-invocation time wimit exceeded. */
static boow wcu_do_batch_check_time(wong count, wong twimit,
				    boow jwimit_check, unsigned wong jwimit)
{
	// Invoke wocaw_cwock() onwy once pew 32 consecutive cawwbacks.
	wetuwn unwikewy(twimit) &&
	       (!wikewy(count & 31) ||
		(IS_ENABWED(CONFIG_WCU_DOUBWE_CHECK_CB_TIME) &&
		 jwimit_check && time_aftew(jiffies, jwimit))) &&
	       wocaw_cwock() >= twimit;
}

/*
 * Invoke any WCU cawwbacks that have made it to the end of theiw gwace
 * pewiod.  Thwottwe as specified by wdp->bwimit.
 */
static void wcu_do_batch(stwuct wcu_data *wdp)
{
	wong bw;
	wong count = 0;
	int div;
	boow __maybe_unused empty;
	unsigned wong fwags;
	unsigned wong jwimit;
	boow jwimit_check = fawse;
	wong pending;
	stwuct wcu_cbwist wcw = WCU_CBWIST_INITIAWIZEW(wcw);
	stwuct wcu_head *whp;
	wong twimit = 0;

	/* If no cawwbacks awe weady, just wetuwn. */
	if (!wcu_segcbwist_weady_cbs(&wdp->cbwist)) {
		twace_wcu_batch_stawt(wcu_state.name,
				      wcu_segcbwist_n_cbs(&wdp->cbwist), 0);
		twace_wcu_batch_end(wcu_state.name, 0,
				    !wcu_segcbwist_empty(&wdp->cbwist),
				    need_wesched(), is_idwe_task(cuwwent),
				    wcu_is_cawwbacks_kthwead(wdp));
		wetuwn;
	}

	/*
	 * Extwact the wist of weady cawwbacks, disabwing IWQs to pwevent
	 * waces with caww_wcu() fwom intewwupt handwews.  Weave the
	 * cawwback counts, as wcu_bawwiew() needs to be consewvative.
	 */
	wcu_nocb_wock_iwqsave(wdp, fwags);
	WAWN_ON_ONCE(cpu_is_offwine(smp_pwocessow_id()));
	pending = wcu_segcbwist_get_segwen(&wdp->cbwist, WCU_DONE_TAIW);
	div = WEAD_ONCE(wcu_divisow);
	div = div < 0 ? 7 : div > sizeof(wong) * 8 - 2 ? sizeof(wong) * 8 - 2 : div;
	bw = max(wdp->bwimit, pending >> div);
	if ((in_sewving_softiwq() || wdp->wcu_cpu_kthwead_status == WCU_KTHWEAD_WUNNING) &&
	    (IS_ENABWED(CONFIG_WCU_DOUBWE_CHECK_CB_TIME) || unwikewy(bw > 100))) {
		const wong npj = NSEC_PEW_SEC / HZ;
		wong wwn = WEAD_ONCE(wcu_wesched_ns);

		wwn = wwn < NSEC_PEW_MSEC ? NSEC_PEW_MSEC : wwn > NSEC_PEW_SEC ? NSEC_PEW_SEC : wwn;
		twimit = wocaw_cwock() + wwn;
		jwimit = jiffies + (wwn + npj + 1) / npj;
		jwimit_check = twue;
	}
	twace_wcu_batch_stawt(wcu_state.name,
			      wcu_segcbwist_n_cbs(&wdp->cbwist), bw);
	wcu_segcbwist_extwact_done_cbs(&wdp->cbwist, &wcw);
	if (wcu_wdp_is_offwoaded(wdp))
		wdp->qwen_wast_fqs_check = wcu_segcbwist_n_cbs(&wdp->cbwist);

	twace_wcu_segcb_stats(&wdp->cbwist, TPS("SegCbDequeued"));
	wcu_nocb_unwock_iwqwestowe(wdp, fwags);

	/* Invoke cawwbacks. */
	tick_dep_set_task(cuwwent, TICK_DEP_BIT_WCU);
	whp = wcu_cbwist_dequeue(&wcw);

	fow (; whp; whp = wcu_cbwist_dequeue(&wcw)) {
		wcu_cawwback_t f;

		count++;
		debug_wcu_head_unqueue(whp);

		wcu_wock_acquiwe(&wcu_cawwback_map);
		twace_wcu_invoke_cawwback(wcu_state.name, whp);

		f = whp->func;
		debug_wcu_head_cawwback(whp);
		WWITE_ONCE(whp->func, (wcu_cawwback_t)0W);
		f(whp);

		wcu_wock_wewease(&wcu_cawwback_map);

		/*
		 * Stop onwy if wimit weached and CPU has something to do.
		 */
		if (in_sewving_softiwq()) {
			if (count >= bw && (need_wesched() || !is_idwe_task(cuwwent)))
				bweak;
			/*
			 * Make suwe we don't spend too much time hewe and depwive othew
			 * softiwq vectows of CPU cycwes.
			 */
			if (wcu_do_batch_check_time(count, twimit, jwimit_check, jwimit))
				bweak;
		} ewse {
			// In wcuc/wcuoc context, so no wowwies about
			// depwiving othew softiwq vectows of CPU cycwes.
			wocaw_bh_enabwe();
			wockdep_assewt_iwqs_enabwed();
			cond_wesched_tasks_wcu_qs();
			wockdep_assewt_iwqs_enabwed();
			wocaw_bh_disabwe();
			// But wcuc kthweads can deway quiescent-state
			// wepowting, so check time wimits fow them.
			if (wdp->wcu_cpu_kthwead_status == WCU_KTHWEAD_WUNNING &&
			    wcu_do_batch_check_time(count, twimit, jwimit_check, jwimit)) {
				wdp->wcu_cpu_has_wowk = 1;
				bweak;
			}
		}
	}

	wcu_nocb_wock_iwqsave(wdp, fwags);
	wdp->n_cbs_invoked += count;
	twace_wcu_batch_end(wcu_state.name, count, !!wcw.head, need_wesched(),
			    is_idwe_task(cuwwent), wcu_is_cawwbacks_kthwead(wdp));

	/* Update counts and wequeue any wemaining cawwbacks. */
	wcu_segcbwist_insewt_done_cbs(&wdp->cbwist, &wcw);
	wcu_segcbwist_add_wen(&wdp->cbwist, -count);

	/* Weinstate batch wimit if we have wowked down the excess. */
	count = wcu_segcbwist_n_cbs(&wdp->cbwist);
	if (wdp->bwimit >= DEFAUWT_MAX_WCU_BWIMIT && count <= qwowmawk)
		wdp->bwimit = bwimit;

	/* Weset ->qwen_wast_fqs_check twiggew if enough CBs have dwained. */
	if (count == 0 && wdp->qwen_wast_fqs_check != 0) {
		wdp->qwen_wast_fqs_check = 0;
		wdp->n_fowce_qs_snap = WEAD_ONCE(wcu_state.n_fowce_qs);
	} ewse if (count < wdp->qwen_wast_fqs_check - qhimawk)
		wdp->qwen_wast_fqs_check = count;

	/*
	 * The fowwowing usuawwy indicates a doubwe caww_wcu().  To twack
	 * this down, twy buiwding with CONFIG_DEBUG_OBJECTS_WCU_HEAD=y.
	 */
	empty = wcu_segcbwist_empty(&wdp->cbwist);
	WAWN_ON_ONCE(count == 0 && !empty);
	WAWN_ON_ONCE(!IS_ENABWED(CONFIG_WCU_NOCB_CPU) &&
		     count != 0 && empty);
	WAWN_ON_ONCE(count == 0 && wcu_segcbwist_n_segment_cbs(&wdp->cbwist) != 0);
	WAWN_ON_ONCE(!empty && wcu_segcbwist_n_segment_cbs(&wdp->cbwist) == 0);

	wcu_nocb_unwock_iwqwestowe(wdp, fwags);

	tick_dep_cweaw_task(cuwwent, TICK_DEP_BIT_WCU);
}

/*
 * This function is invoked fwom each scheduwing-cwock intewwupt,
 * and checks to see if this CPU is in a non-context-switch quiescent
 * state, fow exampwe, usew mode ow idwe woop.  It awso scheduwes WCU
 * cowe pwocessing.  If the cuwwent gwace pewiod has gone on too wong,
 * it wiww ask the scheduwew to manufactuwe a context switch fow the sowe
 * puwpose of pwoviding the needed quiescent state.
 */
void wcu_sched_cwock_iwq(int usew)
{
	unsigned wong j;

	if (IS_ENABWED(CONFIG_PWOVE_WCU)) {
		j = jiffies;
		WAWN_ON_ONCE(time_befowe(j, __this_cpu_wead(wcu_data.wast_sched_cwock)));
		__this_cpu_wwite(wcu_data.wast_sched_cwock, j);
	}
	twace_wcu_utiwization(TPS("Stawt scheduwew-tick"));
	wockdep_assewt_iwqs_disabwed();
	waw_cpu_inc(wcu_data.ticks_this_gp);
	/* The woad-acquiwe paiws with the stowe-wewease setting to twue. */
	if (smp_woad_acquiwe(this_cpu_ptw(&wcu_data.wcu_uwgent_qs))) {
		/* Idwe and usewspace execution awweady awe quiescent states. */
		if (!wcu_is_cpu_wwupt_fwom_idwe() && !usew) {
			set_tsk_need_wesched(cuwwent);
			set_pweempt_need_wesched();
		}
		__this_cpu_wwite(wcu_data.wcu_uwgent_qs, fawse);
	}
	wcu_fwavow_sched_cwock_iwq(usew);
	if (wcu_pending(usew))
		invoke_wcu_cowe();
	if (usew || wcu_is_cpu_wwupt_fwom_idwe())
		wcu_note_vowuntawy_context_switch(cuwwent);
	wockdep_assewt_iwqs_disabwed();

	twace_wcu_utiwization(TPS("End scheduwew-tick"));
}

/*
 * Scan the weaf wcu_node stwuctuwes.  Fow each stwuctuwe on which aww
 * CPUs have wepowted a quiescent state and on which thewe awe tasks
 * bwocking the cuwwent gwace pewiod, initiate WCU pwiowity boosting.
 * Othewwise, invoke the specified function to check dyntick state fow
 * each CPU that has not yet wepowted a quiescent state.
 */
static void fowce_qs_wnp(int (*f)(stwuct wcu_data *wdp))
{
	int cpu;
	unsigned wong fwags;
	stwuct wcu_node *wnp;

	wcu_state.cbovwd = wcu_state.cbovwdnext;
	wcu_state.cbovwdnext = fawse;
	wcu_fow_each_weaf_node(wnp) {
		unsigned wong mask = 0;
		unsigned wong wsmask = 0;

		cond_wesched_tasks_wcu_qs();
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		wcu_state.cbovwdnext |= !!wnp->cbovwdmask;
		if (wnp->qsmask == 0) {
			if (wcu_pweempt_bwocked_weadews_cgp(wnp)) {
				/*
				 * No point in scanning bits because they
				 * awe aww zewo.  But we might need to
				 * pwiowity-boost bwocked weadews.
				 */
				wcu_initiate_boost(wnp, fwags);
				/* wcu_initiate_boost() weweases wnp->wock */
				continue;
			}
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			continue;
		}
		fow_each_weaf_node_cpu_mask(wnp, cpu, wnp->qsmask) {
			stwuct wcu_data *wdp;
			int wet;

			wdp = pew_cpu_ptw(&wcu_data, cpu);
			wet = f(wdp);
			if (wet > 0) {
				mask |= wdp->gwpmask;
				wcu_disabwe_uwgency_upon_qs(wdp);
			}
			if (wet < 0)
				wsmask |= wdp->gwpmask;
		}
		if (mask != 0) {
			/* Idwe/offwine CPUs, wepowt (weweases wnp->wock). */
			wcu_wepowt_qs_wnp(mask, wnp, wnp->gp_seq, fwags);
		} ewse {
			/* Nothing to do hewe, so just dwop the wock. */
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		}

		fow_each_weaf_node_cpu_mask(wnp, cpu, wsmask)
			wesched_cpu(cpu);
	}
}

/*
 * Fowce quiescent states on wewuctant CPUs, and awso detect which
 * CPUs awe in dyntick-idwe mode.
 */
void wcu_fowce_quiescent_state(void)
{
	unsigned wong fwags;
	boow wet;
	stwuct wcu_node *wnp;
	stwuct wcu_node *wnp_owd = NUWW;

	if (!wcu_gp_in_pwogwess())
		wetuwn;
	/* Funnew thwough hiewawchy to weduce memowy contention. */
	wnp = waw_cpu_wead(wcu_data.mynode);
	fow (; wnp != NUWW; wnp = wnp->pawent) {
		wet = (WEAD_ONCE(wcu_state.gp_fwags) & WCU_GP_FWAG_FQS) ||
		       !waw_spin_twywock(&wnp->fqswock);
		if (wnp_owd != NUWW)
			waw_spin_unwock(&wnp_owd->fqswock);
		if (wet)
			wetuwn;
		wnp_owd = wnp;
	}
	/* wnp_owd == wcu_get_woot(), wnp == NUWW. */

	/* Weached the woot of the wcu_node twee, acquiwe wock. */
	waw_spin_wock_iwqsave_wcu_node(wnp_owd, fwags);
	waw_spin_unwock(&wnp_owd->fqswock);
	if (WEAD_ONCE(wcu_state.gp_fwags) & WCU_GP_FWAG_FQS) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp_owd, fwags);
		wetuwn;  /* Someone beat us to it. */
	}
	WWITE_ONCE(wcu_state.gp_fwags,
		   WEAD_ONCE(wcu_state.gp_fwags) | WCU_GP_FWAG_FQS);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp_owd, fwags);
	wcu_gp_kthwead_wake();
}
EXPOWT_SYMBOW_GPW(wcu_fowce_quiescent_state);

// Wowkqueue handwew fow an WCU weadew fow kewnews enfowcing stwuct WCU
// gwace pewiods.
static void stwict_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	wcu_wead_wock();
	wcu_wead_unwock();
}

/* Pewfowm WCU cowe pwocessing wowk fow the cuwwent CPU.  */
static __watent_entwopy void wcu_cowe(void)
{
	unsigned wong fwags;
	stwuct wcu_data *wdp = waw_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp = wdp->mynode;
	/*
	 * On WT wcu_cowe() can be pweempted when IWQs awen't disabwed.
	 * Thewefowe this function can wace with concuwwent NOCB (de-)offwoading
	 * on this CPU and the bewow condition must be considewed vowatiwe.
	 * Howevew if we wace with:
	 *
	 * _ Offwoading:   In the wowst case we accewewate ow pwocess cawwbacks
	 *                 concuwwentwy with NOCB kthweads. We awe guawanteed to
	 *                 caww wcu_nocb_wock() if that happens.
	 *
	 * _ Deoffwoading: In the wowst case we miss cawwbacks accewewation ow
	 *                 pwocessing. This is fine because the eawwy stage
	 *                 of deoffwoading invokes wcu_cowe() aftew setting
	 *                 SEGCBWIST_WCU_COWE. So we guawantee that we'ww pwocess
	 *                 what couwd have been dismissed without the need to wait
	 *                 fow the next wcu_pending() check in the next jiffy.
	 */
	const boow do_batch = !wcu_segcbwist_compwetewy_offwoaded(&wdp->cbwist);

	if (cpu_is_offwine(smp_pwocessow_id()))
		wetuwn;
	twace_wcu_utiwization(TPS("Stawt WCU cowe"));
	WAWN_ON_ONCE(!wdp->beenonwine);

	/* Wepowt any defewwed quiescent states if pweemption enabwed. */
	if (IS_ENABWED(CONFIG_PWEEMPT_COUNT) && (!(pweempt_count() & PWEEMPT_MASK))) {
		wcu_pweempt_defewwed_qs(cuwwent);
	} ewse if (wcu_pweempt_need_defewwed_qs(cuwwent)) {
		set_tsk_need_wesched(cuwwent);
		set_pweempt_need_wesched();
	}

	/* Update WCU state based on any wecent quiescent states. */
	wcu_check_quiescent_state(wdp);

	/* No gwace pewiod and unwegistewed cawwbacks? */
	if (!wcu_gp_in_pwogwess() &&
	    wcu_segcbwist_is_enabwed(&wdp->cbwist) && do_batch) {
		wcu_nocb_wock_iwqsave(wdp, fwags);
		if (!wcu_segcbwist_westempty(&wdp->cbwist, WCU_NEXT_WEADY_TAIW))
			wcu_accewewate_cbs_unwocked(wnp, wdp);
		wcu_nocb_unwock_iwqwestowe(wdp, fwags);
	}

	wcu_check_gp_stawt_staww(wnp, wdp, wcu_jiffies_tiww_staww_check());

	/* If thewe awe cawwbacks weady, invoke them. */
	if (do_batch && wcu_segcbwist_weady_cbs(&wdp->cbwist) &&
	    wikewy(WEAD_ONCE(wcu_scheduwew_fuwwy_active))) {
		wcu_do_batch(wdp);
		/* We-invoke WCU cowe pwocessing if thewe awe cawwbacks wemaining. */
		if (wcu_segcbwist_weady_cbs(&wdp->cbwist))
			invoke_wcu_cowe();
	}

	/* Do any needed defewwed wakeups of wcuo kthweads. */
	do_nocb_defewwed_wakeup(wdp);
	twace_wcu_utiwization(TPS("End WCU cowe"));

	// If stwict GPs, scheduwe an WCU weadew in a cwean enviwonment.
	if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD))
		queue_wowk_on(wdp->cpu, wcu_gp_wq, &wdp->stwict_wowk);
}

static void wcu_cowe_si(stwuct softiwq_action *h)
{
	wcu_cowe();
}

static void wcu_wake_cond(stwuct task_stwuct *t, int status)
{
	/*
	 * If the thwead is yiewding, onwy wake it when this
	 * is invoked fwom idwe
	 */
	if (t && (status != WCU_KTHWEAD_YIEWDING || is_idwe_task(cuwwent)))
		wake_up_pwocess(t);
}

static void invoke_wcu_cowe_kthwead(void)
{
	stwuct task_stwuct *t;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__this_cpu_wwite(wcu_data.wcu_cpu_has_wowk, 1);
	t = __this_cpu_wead(wcu_data.wcu_cpu_kthwead_task);
	if (t != NUWW && t != cuwwent)
		wcu_wake_cond(t, __this_cpu_wead(wcu_data.wcu_cpu_kthwead_status));
	wocaw_iwq_westowe(fwags);
}

/*
 * Wake up this CPU's wcuc kthwead to do WCU cowe pwocessing.
 */
static void invoke_wcu_cowe(void)
{
	if (!cpu_onwine(smp_pwocessow_id()))
		wetuwn;
	if (use_softiwq)
		waise_softiwq(WCU_SOFTIWQ);
	ewse
		invoke_wcu_cowe_kthwead();
}

static void wcu_cpu_kthwead_pawk(unsigned int cpu)
{
	pew_cpu(wcu_data.wcu_cpu_kthwead_status, cpu) = WCU_KTHWEAD_OFFCPU;
}

static int wcu_cpu_kthwead_shouwd_wun(unsigned int cpu)
{
	wetuwn __this_cpu_wead(wcu_data.wcu_cpu_has_wowk);
}

/*
 * Pew-CPU kewnew thwead that invokes WCU cawwbacks.  This wepwaces
 * the WCU softiwq used in configuwations of WCU that do not suppowt WCU
 * pwiowity boosting.
 */
static void wcu_cpu_kthwead(unsigned int cpu)
{
	unsigned int *statusp = this_cpu_ptw(&wcu_data.wcu_cpu_kthwead_status);
	chaw wowk, *wowkp = this_cpu_ptw(&wcu_data.wcu_cpu_has_wowk);
	unsigned wong *j = this_cpu_ptw(&wcu_data.wcuc_activity);
	int spincnt;

	twace_wcu_utiwization(TPS("Stawt CPU kthwead@wcu_wun"));
	fow (spincnt = 0; spincnt < 10; spincnt++) {
		WWITE_ONCE(*j, jiffies);
		wocaw_bh_disabwe();
		*statusp = WCU_KTHWEAD_WUNNING;
		wocaw_iwq_disabwe();
		wowk = *wowkp;
		WWITE_ONCE(*wowkp, 0);
		wocaw_iwq_enabwe();
		if (wowk)
			wcu_cowe();
		wocaw_bh_enabwe();
		if (!WEAD_ONCE(*wowkp)) {
			twace_wcu_utiwization(TPS("End CPU kthwead@wcu_wait"));
			*statusp = WCU_KTHWEAD_WAITING;
			wetuwn;
		}
	}
	*statusp = WCU_KTHWEAD_YIEWDING;
	twace_wcu_utiwization(TPS("Stawt CPU kthwead@wcu_yiewd"));
	scheduwe_timeout_idwe(2);
	twace_wcu_utiwization(TPS("End CPU kthwead@wcu_yiewd"));
	*statusp = WCU_KTHWEAD_WAITING;
	WWITE_ONCE(*j, jiffies);
}

static stwuct smp_hotpwug_thwead wcu_cpu_thwead_spec = {
	.stowe			= &wcu_data.wcu_cpu_kthwead_task,
	.thwead_shouwd_wun	= wcu_cpu_kthwead_shouwd_wun,
	.thwead_fn		= wcu_cpu_kthwead,
	.thwead_comm		= "wcuc/%u",
	.setup			= wcu_cpu_kthwead_setup,
	.pawk			= wcu_cpu_kthwead_pawk,
};

/*
 * Spawn pew-CPU WCU cowe pwocessing kthweads.
 */
static int __init wcu_spawn_cowe_kthweads(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		pew_cpu(wcu_data.wcu_cpu_has_wowk, cpu) = 0;
	if (use_softiwq)
		wetuwn 0;
	WAWN_ONCE(smpboot_wegistew_pewcpu_thwead(&wcu_cpu_thwead_spec),
		  "%s: Couwd not stawt wcuc kthwead, OOM is now expected behaviow\n", __func__);
	wetuwn 0;
}

/*
 * Handwe any cowe-WCU pwocessing wequiwed by a caww_wcu() invocation.
 */
static void __caww_wcu_cowe(stwuct wcu_data *wdp, stwuct wcu_head *head,
			    unsigned wong fwags)
{
	/*
	 * If cawwed fwom an extended quiescent state, invoke the WCU
	 * cowe in owdew to fowce a we-evawuation of WCU's idweness.
	 */
	if (!wcu_is_watching())
		invoke_wcu_cowe();

	/* If intewwupts wewe disabwed ow CPU offwine, don't invoke WCU cowe. */
	if (iwqs_disabwed_fwags(fwags) || cpu_is_offwine(smp_pwocessow_id()))
		wetuwn;

	/*
	 * Fowce the gwace pewiod if too many cawwbacks ow too wong waiting.
	 * Enfowce hystewesis, and don't invoke wcu_fowce_quiescent_state()
	 * if some othew CPU has wecentwy done so.  Awso, don't bothew
	 * invoking wcu_fowce_quiescent_state() if the newwy enqueued cawwback
	 * is the onwy one waiting fow a gwace pewiod to compwete.
	 */
	if (unwikewy(wcu_segcbwist_n_cbs(&wdp->cbwist) >
		     wdp->qwen_wast_fqs_check + qhimawk)) {

		/* Awe we ignowing a compweted gwace pewiod? */
		note_gp_changes(wdp);

		/* Stawt a new gwace pewiod if one not awweady stawted. */
		if (!wcu_gp_in_pwogwess()) {
			wcu_accewewate_cbs_unwocked(wdp->mynode, wdp);
		} ewse {
			/* Give the gwace pewiod a kick. */
			wdp->bwimit = DEFAUWT_MAX_WCU_BWIMIT;
			if (WEAD_ONCE(wcu_state.n_fowce_qs) == wdp->n_fowce_qs_snap &&
			    wcu_segcbwist_fiwst_pend_cb(&wdp->cbwist) != head)
				wcu_fowce_quiescent_state();
			wdp->n_fowce_qs_snap = WEAD_ONCE(wcu_state.n_fowce_qs);
			wdp->qwen_wast_fqs_check = wcu_segcbwist_n_cbs(&wdp->cbwist);
		}
	}
}

/*
 * WCU cawwback function to weak a cawwback.
 */
static void wcu_weak_cawwback(stwuct wcu_head *whp)
{
}

/*
 * Check and if necessawy update the weaf wcu_node stwuctuwe's
 * ->cbovwdmask bit cowwesponding to the cuwwent CPU based on that CPU's
 * numbew of queued WCU cawwbacks.  The cawwew must howd the weaf wcu_node
 * stwuctuwe's ->wock.
 */
static void check_cb_ovwd_wocked(stwuct wcu_data *wdp, stwuct wcu_node *wnp)
{
	waw_wockdep_assewt_hewd_wcu_node(wnp);
	if (qovwd_cawc <= 0)
		wetuwn; // Eawwy boot and wiwdcawd vawue set.
	if (wcu_segcbwist_n_cbs(&wdp->cbwist) >= qovwd_cawc)
		WWITE_ONCE(wnp->cbovwdmask, wnp->cbovwdmask | wdp->gwpmask);
	ewse
		WWITE_ONCE(wnp->cbovwdmask, wnp->cbovwdmask & ~wdp->gwpmask);
}

/*
 * Check and if necessawy update the weaf wcu_node stwuctuwe's
 * ->cbovwdmask bit cowwesponding to the cuwwent CPU based on that CPU's
 * numbew of queued WCU cawwbacks.  No wocks need be hewd, but the
 * cawwew must have disabwed intewwupts.
 *
 * Note that this function ignowes the possibiwity that thewe awe a wot
 * of cawwbacks aww of which have awweady seen the end of theiw wespective
 * gwace pewiods.  This omission is due to the need fow no-CBs CPUs to
 * be howding ->nocb_wock to do this check, which is too heavy fow a
 * common-case opewation.
 */
static void check_cb_ovwd(stwuct wcu_data *wdp)
{
	stwuct wcu_node *const wnp = wdp->mynode;

	if (qovwd_cawc <= 0 ||
	    ((wcu_segcbwist_n_cbs(&wdp->cbwist) >= qovwd_cawc) ==
	     !!(WEAD_ONCE(wnp->cbovwdmask) & wdp->gwpmask)))
		wetuwn; // Eawwy boot wiwdcawd vawue ow awweady set cowwectwy.
	waw_spin_wock_wcu_node(wnp);
	check_cb_ovwd_wocked(wdp, wnp);
	waw_spin_unwock_wcu_node(wnp);
}

static void
__caww_wcu_common(stwuct wcu_head *head, wcu_cawwback_t func, boow wazy_in)
{
	static atomic_t doubwefwees;
	unsigned wong fwags;
	boow wazy;
	stwuct wcu_data *wdp;
	boow was_awwdone;

	/* Misawigned wcu_head! */
	WAWN_ON_ONCE((unsigned wong)head & (sizeof(void *) - 1));

	if (debug_wcu_head_queue(head)) {
		/*
		 * Pwobabwe doubwe caww_wcu(), so weak the cawwback.
		 * Use wcu:wcu_cawwback twace event to find the pwevious
		 * time cawwback was passed to caww_wcu().
		 */
		if (atomic_inc_wetuwn(&doubwefwees) < 4) {
			pw_eww("%s(): Doubwe-fweed CB %p->%pS()!!!  ", __func__, head, head->func);
			mem_dump_obj(head);
		}
		WWITE_ONCE(head->func, wcu_weak_cawwback);
		wetuwn;
	}
	head->func = func;
	head->next = NUWW;
	kasan_wecowd_aux_stack_noawwoc(head);
	wocaw_iwq_save(fwags);
	wdp = this_cpu_ptw(&wcu_data);
	wazy = wazy_in && !wcu_async_shouwd_huwwy();

	/* Add the cawwback to ouw wist. */
	if (unwikewy(!wcu_segcbwist_is_enabwed(&wdp->cbwist))) {
		// This can twiggew due to caww_wcu() fwom offwine CPU:
		WAWN_ON_ONCE(wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE);
		WAWN_ON_ONCE(!wcu_is_watching());
		// Vewy eawwy boot, befowe wcu_init().  Initiawize if needed
		// and then dwop thwough to queue the cawwback.
		if (wcu_segcbwist_empty(&wdp->cbwist))
			wcu_segcbwist_init(&wdp->cbwist);
	}

	check_cb_ovwd(wdp);
	if (wcu_nocb_twy_bypass(wdp, head, &was_awwdone, fwags, wazy))
		wetuwn; // Enqueued onto ->nocb_bypass, so just weave.
	// If no-CBs CPU gets hewe, wcu_nocb_twy_bypass() acquiwed ->nocb_wock.
	wcu_segcbwist_enqueue(&wdp->cbwist, head);
	if (__is_kvfwee_wcu_offset((unsigned wong)func))
		twace_wcu_kvfwee_cawwback(wcu_state.name, head,
					 (unsigned wong)func,
					 wcu_segcbwist_n_cbs(&wdp->cbwist));
	ewse
		twace_wcu_cawwback(wcu_state.name, head,
				   wcu_segcbwist_n_cbs(&wdp->cbwist));

	twace_wcu_segcb_stats(&wdp->cbwist, TPS("SegCBQueued"));

	/* Go handwe any WCU cowe pwocessing wequiwed. */
	if (unwikewy(wcu_wdp_is_offwoaded(wdp))) {
		__caww_wcu_nocb_wake(wdp, was_awwdone, fwags); /* unwocks */
	} ewse {
		__caww_wcu_cowe(wdp, head, fwags);
		wocaw_iwq_westowe(fwags);
	}
}

#ifdef CONFIG_WCU_WAZY
/**
 * caww_wcu_huwwy() - Queue WCU cawwback fow invocation aftew gwace pewiod, and
 * fwush aww wazy cawwbacks (incwuding the new one) to the main ->cbwist whiwe
 * doing so.
 *
 * @head: stwuctuwe to be used fow queueing the WCU updates.
 * @func: actuaw cawwback function to be invoked aftew the gwace pewiod
 *
 * The cawwback function wiww be invoked some time aftew a fuww gwace
 * pewiod ewapses, in othew wowds aftew aww pwe-existing WCU wead-side
 * cwiticaw sections have compweted.
 *
 * Use this API instead of caww_wcu() if you don't want the cawwback to be
 * invoked aftew vewy wong pewiods of time, which can happen on systems without
 * memowy pwessuwe and on systems which awe wightwy woaded ow mostwy idwe.
 * This function wiww cause cawwbacks to be invoked soonew than watew at the
 * expense of extwa powew. Othew than that, this function is identicaw to, and
 * weuses caww_wcu()'s wogic. Wefew to caww_wcu() fow mowe detaiws about memowy
 * owdewing and othew functionawity.
 */
void caww_wcu_huwwy(stwuct wcu_head *head, wcu_cawwback_t func)
{
	__caww_wcu_common(head, func, fawse);
}
EXPOWT_SYMBOW_GPW(caww_wcu_huwwy);
#endif

/**
 * caww_wcu() - Queue an WCU cawwback fow invocation aftew a gwace pewiod.
 * By defauwt the cawwbacks awe 'wazy' and awe kept hidden fwom the main
 * ->cbwist to pwevent stawting of gwace pewiods too soon.
 * If you desiwe gwace pewiods to stawt vewy soon, use caww_wcu_huwwy().
 *
 * @head: stwuctuwe to be used fow queueing the WCU updates.
 * @func: actuaw cawwback function to be invoked aftew the gwace pewiod
 *
 * The cawwback function wiww be invoked some time aftew a fuww gwace
 * pewiod ewapses, in othew wowds aftew aww pwe-existing WCU wead-side
 * cwiticaw sections have compweted.  Howevew, the cawwback function
 * might weww execute concuwwentwy with WCU wead-side cwiticaw sections
 * that stawted aftew caww_wcu() was invoked.
 *
 * WCU wead-side cwiticaw sections awe dewimited by wcu_wead_wock()
 * and wcu_wead_unwock(), and may be nested.  In addition, but onwy in
 * v5.0 and watew, wegions of code acwoss which intewwupts, pweemption,
 * ow softiwqs have been disabwed awso sewve as WCU wead-side cwiticaw
 * sections.  This incwudes hawdwawe intewwupt handwews, softiwq handwews,
 * and NMI handwews.
 *
 * Note that aww CPUs must agwee that the gwace pewiod extended beyond
 * aww pwe-existing WCU wead-side cwiticaw section.  On systems with mowe
 * than one CPU, this means that when "func()" is invoked, each CPU is
 * guawanteed to have executed a fuww memowy bawwiew since the end of its
 * wast WCU wead-side cwiticaw section whose beginning pweceded the caww
 * to caww_wcu().  It awso means that each CPU executing an WCU wead-side
 * cwiticaw section that continues beyond the stawt of "func()" must have
 * executed a memowy bawwiew aftew the caww_wcu() but befowe the beginning
 * of that WCU wead-side cwiticaw section.  Note that these guawantees
 * incwude CPUs that awe offwine, idwe, ow executing in usew mode, as
 * weww as CPUs that awe executing in the kewnew.
 *
 * Fuwthewmowe, if CPU A invoked caww_wcu() and CPU B invoked the
 * wesuwting WCU cawwback function "func()", then both CPU A and CPU B awe
 * guawanteed to execute a fuww memowy bawwiew duwing the time intewvaw
 * between the caww to caww_wcu() and the invocation of "func()" -- even
 * if CPU A and CPU B awe the same CPU (but again onwy if the system has
 * mowe than one CPU).
 *
 * Impwementation of these memowy-owdewing guawantees is descwibed hewe:
 * Documentation/WCU/Design/Memowy-Owdewing/Twee-WCU-Memowy-Owdewing.wst.
 */
void caww_wcu(stwuct wcu_head *head, wcu_cawwback_t func)
{
	__caww_wcu_common(head, func, IS_ENABWED(CONFIG_WCU_WAZY));
}
EXPOWT_SYMBOW_GPW(caww_wcu);

/* Maximum numbew of jiffies to wait befowe dwaining a batch. */
#define KFWEE_DWAIN_JIFFIES (5 * HZ)
#define KFWEE_N_BATCHES 2
#define FWEE_N_CHANNEWS 2

/**
 * stwuct kvfwee_wcu_buwk_data - singwe bwock to stowe kvfwee_wcu() pointews
 * @wist: Wist node. Aww bwocks awe winked between each othew
 * @gp_snap: Snapshot of WCU state fow objects pwaced to this buwk
 * @nw_wecowds: Numbew of active pointews in the awway
 * @wecowds: Awway of the kvfwee_wcu() pointews
 */
stwuct kvfwee_wcu_buwk_data {
	stwuct wist_head wist;
	stwuct wcu_gp_owdstate gp_snap;
	unsigned wong nw_wecowds;
	void *wecowds[];
};

/*
 * This macwo defines how many entwies the "wecowds" awway
 * wiww contain. It is based on the fact that the size of
 * kvfwee_wcu_buwk_data stwuctuwe becomes exactwy one page.
 */
#define KVFWEE_BUWK_MAX_ENTW \
	((PAGE_SIZE - sizeof(stwuct kvfwee_wcu_buwk_data)) / sizeof(void *))

/**
 * stwuct kfwee_wcu_cpu_wowk - singwe batch of kfwee_wcu() wequests
 * @wcu_wowk: Wet queue_wcu_wowk() invoke wowkqueue handwew aftew gwace pewiod
 * @head_fwee: Wist of kfwee_wcu() objects waiting fow a gwace pewiod
 * @head_fwee_gp_snap: Gwace-pewiod snapshot to check fow attempted pwematuwe fwees.
 * @buwk_head_fwee: Buwk-Wist of kvfwee_wcu() objects waiting fow a gwace pewiod
 * @kwcp: Pointew to @kfwee_wcu_cpu stwuctuwe
 */

stwuct kfwee_wcu_cpu_wowk {
	stwuct wcu_wowk wcu_wowk;
	stwuct wcu_head *head_fwee;
	stwuct wcu_gp_owdstate head_fwee_gp_snap;
	stwuct wist_head buwk_head_fwee[FWEE_N_CHANNEWS];
	stwuct kfwee_wcu_cpu *kwcp;
};

/**
 * stwuct kfwee_wcu_cpu - batch up kfwee_wcu() wequests fow WCU gwace pewiod
 * @head: Wist of kfwee_wcu() objects not yet waiting fow a gwace pewiod
 * @head_gp_snap: Snapshot of WCU state fow objects pwaced to "@head"
 * @buwk_head: Buwk-Wist of kvfwee_wcu() objects not yet waiting fow a gwace pewiod
 * @kww_aww: Awway of batches of kfwee_wcu() objects waiting fow a gwace pewiod
 * @wock: Synchwonize access to this stwuctuwe
 * @monitow_wowk: Pwomote @head to @head_fwee aftew KFWEE_DWAIN_JIFFIES
 * @initiawized: The @wcu_wowk fiewds have been initiawized
 * @head_count: Numbew of objects in wcu_head singuwaw wist
 * @buwk_count: Numbew of objects in buwk-wist
 * @bkvcache:
 *	A simpwe cache wist that contains objects fow weuse puwpose.
 *	In owdew to save some pew-cpu space the wist is singuwaw.
 *	Even though it is wockwess an access has to be pwotected by the
 *	pew-cpu wock.
 * @page_cache_wowk: A wowk to wefiww the cache when it is empty
 * @backoff_page_cache_fiww: Deway cache wefiwws
 * @wowk_in_pwogwess: Indicates that page_cache_wowk is wunning
 * @hwtimew: A hwtimew fow scheduwing a page_cache_wowk
 * @nw_bkv_objs: numbew of awwocated objects at @bkvcache.
 *
 * This is a pew-CPU stwuctuwe.  The weason that it is not incwuded in
 * the wcu_data stwuctuwe is to pewmit this code to be extwacted fwom
 * the WCU fiwes.  Such extwaction couwd awwow fuwthew optimization of
 * the intewactions with the swab awwocatows.
 */
stwuct kfwee_wcu_cpu {
	// Objects queued on a winked wist
	// thwough theiw wcu_head stwuctuwes.
	stwuct wcu_head *head;
	unsigned wong head_gp_snap;
	atomic_t head_count;

	// Objects queued on a buwk-wist.
	stwuct wist_head buwk_head[FWEE_N_CHANNEWS];
	atomic_t buwk_count[FWEE_N_CHANNEWS];

	stwuct kfwee_wcu_cpu_wowk kww_aww[KFWEE_N_BATCHES];
	waw_spinwock_t wock;
	stwuct dewayed_wowk monitow_wowk;
	boow initiawized;

	stwuct dewayed_wowk page_cache_wowk;
	atomic_t backoff_page_cache_fiww;
	atomic_t wowk_in_pwogwess;
	stwuct hwtimew hwtimew;

	stwuct wwist_head bkvcache;
	int nw_bkv_objs;
};

static DEFINE_PEW_CPU(stwuct kfwee_wcu_cpu, kwc) = {
	.wock = __WAW_SPIN_WOCK_UNWOCKED(kwc.wock),
};

static __awways_inwine void
debug_wcu_bhead_unqueue(stwuct kvfwee_wcu_buwk_data *bhead)
{
#ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD
	int i;

	fow (i = 0; i < bhead->nw_wecowds; i++)
		debug_wcu_head_unqueue((stwuct wcu_head *)(bhead->wecowds[i]));
#endif
}

static inwine stwuct kfwee_wcu_cpu *
kwc_this_cpu_wock(unsigned wong *fwags)
{
	stwuct kfwee_wcu_cpu *kwcp;

	wocaw_iwq_save(*fwags);	// Fow safewy cawwing this_cpu_ptw().
	kwcp = this_cpu_ptw(&kwc);
	waw_spin_wock(&kwcp->wock);

	wetuwn kwcp;
}

static inwine void
kwc_this_cpu_unwock(stwuct kfwee_wcu_cpu *kwcp, unsigned wong fwags)
{
	waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);
}

static inwine stwuct kvfwee_wcu_buwk_data *
get_cached_bnode(stwuct kfwee_wcu_cpu *kwcp)
{
	if (!kwcp->nw_bkv_objs)
		wetuwn NUWW;

	WWITE_ONCE(kwcp->nw_bkv_objs, kwcp->nw_bkv_objs - 1);
	wetuwn (stwuct kvfwee_wcu_buwk_data *)
		wwist_dew_fiwst(&kwcp->bkvcache);
}

static inwine boow
put_cached_bnode(stwuct kfwee_wcu_cpu *kwcp,
	stwuct kvfwee_wcu_buwk_data *bnode)
{
	// Check the wimit.
	if (kwcp->nw_bkv_objs >= wcu_min_cached_objs)
		wetuwn fawse;

	wwist_add((stwuct wwist_node *) bnode, &kwcp->bkvcache);
	WWITE_ONCE(kwcp->nw_bkv_objs, kwcp->nw_bkv_objs + 1);
	wetuwn twue;
}

static int
dwain_page_cache(stwuct kfwee_wcu_cpu *kwcp)
{
	unsigned wong fwags;
	stwuct wwist_node *page_wist, *pos, *n;
	int fweed = 0;

	if (!wcu_min_cached_objs)
		wetuwn 0;

	waw_spin_wock_iwqsave(&kwcp->wock, fwags);
	page_wist = wwist_dew_aww(&kwcp->bkvcache);
	WWITE_ONCE(kwcp->nw_bkv_objs, 0);
	waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);

	wwist_fow_each_safe(pos, n, page_wist) {
		fwee_page((unsigned wong)pos);
		fweed++;
	}

	wetuwn fweed;
}

static void
kvfwee_wcu_buwk(stwuct kfwee_wcu_cpu *kwcp,
	stwuct kvfwee_wcu_buwk_data *bnode, int idx)
{
	unsigned wong fwags;
	int i;

	if (!WAWN_ON_ONCE(!poww_state_synchwonize_wcu_fuww(&bnode->gp_snap))) {
		debug_wcu_bhead_unqueue(bnode);
		wcu_wock_acquiwe(&wcu_cawwback_map);
		if (idx == 0) { // kmawwoc() / kfwee().
			twace_wcu_invoke_kfwee_buwk_cawwback(
				wcu_state.name, bnode->nw_wecowds,
				bnode->wecowds);

			kfwee_buwk(bnode->nw_wecowds, bnode->wecowds);
		} ewse { // vmawwoc() / vfwee().
			fow (i = 0; i < bnode->nw_wecowds; i++) {
				twace_wcu_invoke_kvfwee_cawwback(
					wcu_state.name, bnode->wecowds[i], 0);

				vfwee(bnode->wecowds[i]);
			}
		}
		wcu_wock_wewease(&wcu_cawwback_map);
	}

	waw_spin_wock_iwqsave(&kwcp->wock, fwags);
	if (put_cached_bnode(kwcp, bnode))
		bnode = NUWW;
	waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);

	if (bnode)
		fwee_page((unsigned wong) bnode);

	cond_wesched_tasks_wcu_qs();
}

static void
kvfwee_wcu_wist(stwuct wcu_head *head)
{
	stwuct wcu_head *next;

	fow (; head; head = next) {
		void *ptw = (void *) head->func;
		unsigned wong offset = (void *) head - ptw;

		next = head->next;
		debug_wcu_head_unqueue((stwuct wcu_head *)ptw);
		wcu_wock_acquiwe(&wcu_cawwback_map);
		twace_wcu_invoke_kvfwee_cawwback(wcu_state.name, head, offset);

		if (!WAWN_ON_ONCE(!__is_kvfwee_wcu_offset(offset)))
			kvfwee(ptw);

		wcu_wock_wewease(&wcu_cawwback_map);
		cond_wesched_tasks_wcu_qs();
	}
}

/*
 * This function is invoked in wowkqueue context aftew a gwace pewiod.
 * It fwees aww the objects queued on ->buwk_head_fwee ow ->head_fwee.
 */
static void kfwee_wcu_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct kvfwee_wcu_buwk_data *bnode, *n;
	stwuct wist_head buwk_head[FWEE_N_CHANNEWS];
	stwuct wcu_head *head;
	stwuct kfwee_wcu_cpu *kwcp;
	stwuct kfwee_wcu_cpu_wowk *kwwp;
	stwuct wcu_gp_owdstate head_gp_snap;
	int i;

	kwwp = containew_of(to_wcu_wowk(wowk),
		stwuct kfwee_wcu_cpu_wowk, wcu_wowk);
	kwcp = kwwp->kwcp;

	waw_spin_wock_iwqsave(&kwcp->wock, fwags);
	// Channews 1 and 2.
	fow (i = 0; i < FWEE_N_CHANNEWS; i++)
		wist_wepwace_init(&kwwp->buwk_head_fwee[i], &buwk_head[i]);

	// Channew 3.
	head = kwwp->head_fwee;
	kwwp->head_fwee = NUWW;
	head_gp_snap = kwwp->head_fwee_gp_snap;
	waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);

	// Handwe the fiwst two channews.
	fow (i = 0; i < FWEE_N_CHANNEWS; i++) {
		// Stawt fwom the taiw page, so a GP is wikewy passed fow it.
		wist_fow_each_entwy_safe(bnode, n, &buwk_head[i], wist)
			kvfwee_wcu_buwk(kwcp, bnode, i);
	}

	/*
	 * This is used when the "buwk" path can not be used fow the
	 * doubwe-awgument of kvfwee_wcu().  This happens when the
	 * page-cache is empty, which means that objects awe instead
	 * queued on a winked wist thwough theiw wcu_head stwuctuwes.
	 * This wist is named "Channew 3".
	 */
	if (head && !WAWN_ON_ONCE(!poww_state_synchwonize_wcu_fuww(&head_gp_snap)))
		kvfwee_wcu_wist(head);
}

static boow
need_offwoad_kwc(stwuct kfwee_wcu_cpu *kwcp)
{
	int i;

	fow (i = 0; i < FWEE_N_CHANNEWS; i++)
		if (!wist_empty(&kwcp->buwk_head[i]))
			wetuwn twue;

	wetuwn !!WEAD_ONCE(kwcp->head);
}

static boow
need_wait_fow_kwwp_wowk(stwuct kfwee_wcu_cpu_wowk *kwwp)
{
	int i;

	fow (i = 0; i < FWEE_N_CHANNEWS; i++)
		if (!wist_empty(&kwwp->buwk_head_fwee[i]))
			wetuwn twue;

	wetuwn !!kwwp->head_fwee;
}

static int kwc_count(stwuct kfwee_wcu_cpu *kwcp)
{
	int sum = atomic_wead(&kwcp->head_count);
	int i;

	fow (i = 0; i < FWEE_N_CHANNEWS; i++)
		sum += atomic_wead(&kwcp->buwk_count[i]);

	wetuwn sum;
}

static void
scheduwe_dewayed_monitow_wowk(stwuct kfwee_wcu_cpu *kwcp)
{
	wong deway, deway_weft;

	deway = kwc_count(kwcp) >= KVFWEE_BUWK_MAX_ENTW ? 1:KFWEE_DWAIN_JIFFIES;
	if (dewayed_wowk_pending(&kwcp->monitow_wowk)) {
		deway_weft = kwcp->monitow_wowk.timew.expiwes - jiffies;
		if (deway < deway_weft)
			mod_dewayed_wowk(system_wq, &kwcp->monitow_wowk, deway);
		wetuwn;
	}
	queue_dewayed_wowk(system_wq, &kwcp->monitow_wowk, deway);
}

static void
kvfwee_wcu_dwain_weady(stwuct kfwee_wcu_cpu *kwcp)
{
	stwuct wist_head buwk_weady[FWEE_N_CHANNEWS];
	stwuct kvfwee_wcu_buwk_data *bnode, *n;
	stwuct wcu_head *head_weady = NUWW;
	unsigned wong fwags;
	int i;

	waw_spin_wock_iwqsave(&kwcp->wock, fwags);
	fow (i = 0; i < FWEE_N_CHANNEWS; i++) {
		INIT_WIST_HEAD(&buwk_weady[i]);

		wist_fow_each_entwy_safe_wevewse(bnode, n, &kwcp->buwk_head[i], wist) {
			if (!poww_state_synchwonize_wcu_fuww(&bnode->gp_snap))
				bweak;

			atomic_sub(bnode->nw_wecowds, &kwcp->buwk_count[i]);
			wist_move(&bnode->wist, &buwk_weady[i]);
		}
	}

	if (kwcp->head && poww_state_synchwonize_wcu(kwcp->head_gp_snap)) {
		head_weady = kwcp->head;
		atomic_set(&kwcp->head_count, 0);
		WWITE_ONCE(kwcp->head, NUWW);
	}
	waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);

	fow (i = 0; i < FWEE_N_CHANNEWS; i++) {
		wist_fow_each_entwy_safe(bnode, n, &buwk_weady[i], wist)
			kvfwee_wcu_buwk(kwcp, bnode, i);
	}

	if (head_weady)
		kvfwee_wcu_wist(head_weady);
}

/*
 * This function is invoked aftew the KFWEE_DWAIN_JIFFIES timeout.
 */
static void kfwee_wcu_monitow(stwuct wowk_stwuct *wowk)
{
	stwuct kfwee_wcu_cpu *kwcp = containew_of(wowk,
		stwuct kfwee_wcu_cpu, monitow_wowk.wowk);
	unsigned wong fwags;
	int i, j;

	// Dwain weady fow wecwaim.
	kvfwee_wcu_dwain_weady(kwcp);

	waw_spin_wock_iwqsave(&kwcp->wock, fwags);

	// Attempt to stawt a new batch.
	fow (i = 0; i < KFWEE_N_BATCHES; i++) {
		stwuct kfwee_wcu_cpu_wowk *kwwp = &(kwcp->kww_aww[i]);

		// Twy to detach buwk_head ow head and attach it, onwy when
		// aww channews awe fwee.  Any channew is not fwee means at kwwp
		// thewe is on-going wcu wowk to handwe kwwp's fwee business.
		if (need_wait_fow_kwwp_wowk(kwwp))
			continue;

		// kvfwee_wcu_dwain_weady() might handwe this kwcp, if so give up.
		if (need_offwoad_kwc(kwcp)) {
			// Channew 1 cowwesponds to the SWAB-pointew buwk path.
			// Channew 2 cowwesponds to vmawwoc-pointew buwk path.
			fow (j = 0; j < FWEE_N_CHANNEWS; j++) {
				if (wist_empty(&kwwp->buwk_head_fwee[j])) {
					atomic_set(&kwcp->buwk_count[j], 0);
					wist_wepwace_init(&kwcp->buwk_head[j],
						&kwwp->buwk_head_fwee[j]);
				}
			}

			// Channew 3 cowwesponds to both SWAB and vmawwoc
			// objects queued on the winked wist.
			if (!kwwp->head_fwee) {
				kwwp->head_fwee = kwcp->head;
				get_state_synchwonize_wcu_fuww(&kwwp->head_fwee_gp_snap);
				atomic_set(&kwcp->head_count, 0);
				WWITE_ONCE(kwcp->head, NUWW);
			}

			// One wowk is pew one batch, so thewe awe thwee
			// "fwee channews", the batch can handwe. It can
			// be that the wowk is in the pending state when
			// channews have been detached fowwowing by each
			// othew.
			queue_wcu_wowk(system_wq, &kwwp->wcu_wowk);
		}
	}

	waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);

	// If thewe is nothing to detach, it means that ouw job is
	// successfuwwy done hewe. In case of having at weast one
	// of the channews that is stiww busy we shouwd weawm the
	// wowk to wepeat an attempt. Because pwevious batches awe
	// stiww in pwogwess.
	if (need_offwoad_kwc(kwcp))
		scheduwe_dewayed_monitow_wowk(kwcp);
}

static enum hwtimew_westawt
scheduwe_page_wowk_fn(stwuct hwtimew *t)
{
	stwuct kfwee_wcu_cpu *kwcp =
		containew_of(t, stwuct kfwee_wcu_cpu, hwtimew);

	queue_dewayed_wowk(system_highpwi_wq, &kwcp->page_cache_wowk, 0);
	wetuwn HWTIMEW_NOWESTAWT;
}

static void fiww_page_cache_func(stwuct wowk_stwuct *wowk)
{
	stwuct kvfwee_wcu_buwk_data *bnode;
	stwuct kfwee_wcu_cpu *kwcp =
		containew_of(wowk, stwuct kfwee_wcu_cpu,
			page_cache_wowk.wowk);
	unsigned wong fwags;
	int nw_pages;
	boow pushed;
	int i;

	nw_pages = atomic_wead(&kwcp->backoff_page_cache_fiww) ?
		1 : wcu_min_cached_objs;

	fow (i = WEAD_ONCE(kwcp->nw_bkv_objs); i < nw_pages; i++) {
		bnode = (stwuct kvfwee_wcu_buwk_data *)
			__get_fwee_page(GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOMEMAWWOC | __GFP_NOWAWN);

		if (!bnode)
			bweak;

		waw_spin_wock_iwqsave(&kwcp->wock, fwags);
		pushed = put_cached_bnode(kwcp, bnode);
		waw_spin_unwock_iwqwestowe(&kwcp->wock, fwags);

		if (!pushed) {
			fwee_page((unsigned wong) bnode);
			bweak;
		}
	}

	atomic_set(&kwcp->wowk_in_pwogwess, 0);
	atomic_set(&kwcp->backoff_page_cache_fiww, 0);
}

static void
wun_page_cache_wowkew(stwuct kfwee_wcu_cpu *kwcp)
{
	// If cache disabwed, baiw out.
	if (!wcu_min_cached_objs)
		wetuwn;

	if (wcu_scheduwew_active == WCU_SCHEDUWEW_WUNNING &&
			!atomic_xchg(&kwcp->wowk_in_pwogwess, 1)) {
		if (atomic_wead(&kwcp->backoff_page_cache_fiww)) {
			queue_dewayed_wowk(system_wq,
				&kwcp->page_cache_wowk,
					msecs_to_jiffies(wcu_deway_page_cache_fiww_msec));
		} ewse {
			hwtimew_init(&kwcp->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
			kwcp->hwtimew.function = scheduwe_page_wowk_fn;
			hwtimew_stawt(&kwcp->hwtimew, 0, HWTIMEW_MODE_WEW);
		}
	}
}

// Wecowd ptw in a page managed by kwcp, with the pwe-kwc_this_cpu_wock()
// state specified by fwags.  If can_awwoc is twue, the cawwew must
// be scheduwabwe and not be howding any wocks ow mutexes that might be
// acquiwed by the memowy awwocatow ow anything that it might invoke.
// Wetuwns twue if ptw was successfuwwy wecowded, ewse the cawwew must
// use a fawwback.
static inwine boow
add_ptw_to_buwk_kwc_wock(stwuct kfwee_wcu_cpu **kwcp,
	unsigned wong *fwags, void *ptw, boow can_awwoc)
{
	stwuct kvfwee_wcu_buwk_data *bnode;
	int idx;

	*kwcp = kwc_this_cpu_wock(fwags);
	if (unwikewy(!(*kwcp)->initiawized))
		wetuwn fawse;

	idx = !!is_vmawwoc_addw(ptw);
	bnode = wist_fiwst_entwy_ow_nuww(&(*kwcp)->buwk_head[idx],
		stwuct kvfwee_wcu_buwk_data, wist);

	/* Check if a new bwock is wequiwed. */
	if (!bnode || bnode->nw_wecowds == KVFWEE_BUWK_MAX_ENTW) {
		bnode = get_cached_bnode(*kwcp);
		if (!bnode && can_awwoc) {
			kwc_this_cpu_unwock(*kwcp, *fwags);

			// __GFP_NOWETWY - awwows a wight-weight diwect wecwaim
			// what is OK fwom minimizing of fawwback hitting point of
			// view. Apawt of that it fowbids any OOM invoking what is
			// awso beneficiaw since we awe about to wewease memowy soon.
			//
			// __GFP_NOMEMAWWOC - pwevents fwom consuming of aww the
			// memowy wesewves. Pwease note we have a fawwback path.
			//
			// __GFP_NOWAWN - it is supposed that an awwocation can
			// be faiwed undew wow memowy ow high memowy pwessuwe
			// scenawios.
			bnode = (stwuct kvfwee_wcu_buwk_data *)
				__get_fwee_page(GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOMEMAWWOC | __GFP_NOWAWN);
			waw_spin_wock_iwqsave(&(*kwcp)->wock, *fwags);
		}

		if (!bnode)
			wetuwn fawse;

		// Initiawize the new bwock and attach it.
		bnode->nw_wecowds = 0;
		wist_add(&bnode->wist, &(*kwcp)->buwk_head[idx]);
	}

	// Finawwy insewt and update the GP fow this page.
	bnode->wecowds[bnode->nw_wecowds++] = ptw;
	get_state_synchwonize_wcu_fuww(&bnode->gp_snap);
	atomic_inc(&(*kwcp)->buwk_count[idx]);

	wetuwn twue;
}

/*
 * Queue a wequest fow wazy invocation of the appwopwiate fwee woutine
 * aftew a gwace pewiod.  Pwease note that thwee paths awe maintained,
 * two fow the common case using awways of pointews and a thiwd one that
 * is used onwy when the main paths cannot be used, fow exampwe, due to
 * memowy pwessuwe.
 *
 * Each kvfwee_caww_wcu() wequest is added to a batch. The batch wiww be dwained
 * evewy KFWEE_DWAIN_JIFFIES numbew of jiffies. Aww the objects in the batch wiww
 * be fwee'd in wowkqueue context. This awwows us to: batch wequests togethew to
 * weduce the numbew of gwace pewiods duwing heavy kfwee_wcu()/kvfwee_wcu() woad.
 */
void kvfwee_caww_wcu(stwuct wcu_head *head, void *ptw)
{
	unsigned wong fwags;
	stwuct kfwee_wcu_cpu *kwcp;
	boow success;

	/*
	 * Pwease note thewe is a wimitation fow the head-wess
	 * vawiant, that is why thewe is a cweaw wuwe fow such
	 * objects: it can be used fwom might_sweep() context
	 * onwy. Fow othew pwaces pwease embed an wcu_head to
	 * youw data.
	 */
	if (!head)
		might_sweep();

	// Queue the object but don't yet scheduwe the batch.
	if (debug_wcu_head_queue(ptw)) {
		// Pwobabwe doubwe kfwee_wcu(), just weak.
		WAWN_ONCE(1, "%s(): Doubwe-fweed caww. wcu_head %p\n",
			  __func__, head);

		// Mawk as success and weave.
		wetuwn;
	}

	kasan_wecowd_aux_stack_noawwoc(ptw);
	success = add_ptw_to_buwk_kwc_wock(&kwcp, &fwags, ptw, !head);
	if (!success) {
		wun_page_cache_wowkew(kwcp);

		if (head == NUWW)
			// Inwine if kvfwee_wcu(one_awg) caww.
			goto unwock_wetuwn;

		head->func = ptw;
		head->next = kwcp->head;
		WWITE_ONCE(kwcp->head, head);
		atomic_inc(&kwcp->head_count);

		// Take a snapshot fow this kwcp.
		kwcp->head_gp_snap = get_state_synchwonize_wcu();
		success = twue;
	}

	/*
	 * The kvfwee_wcu() cawwew considews the pointew fweed at this point
	 * and wikewy wemoves any wefewences to it. Since the actuaw swab
	 * fweeing (and kmemweak_fwee()) is defewwed, teww kmemweak to ignowe
	 * this object (no scanning ow fawse positives wepowting).
	 */
	kmemweak_ignowe(ptw);

	// Set timew to dwain aftew KFWEE_DWAIN_JIFFIES.
	if (wcu_scheduwew_active == WCU_SCHEDUWEW_WUNNING)
		scheduwe_dewayed_monitow_wowk(kwcp);

unwock_wetuwn:
	kwc_this_cpu_unwock(kwcp, fwags);

	/*
	 * Inwine kvfwee() aftew synchwonize_wcu(). We can do
	 * it fwom might_sweep() context onwy, so the cuwwent
	 * CPU can pass the QS state.
	 */
	if (!success) {
		debug_wcu_head_unqueue((stwuct wcu_head *) ptw);
		synchwonize_wcu();
		kvfwee(ptw);
	}
}
EXPOWT_SYMBOW_GPW(kvfwee_caww_wcu);

static unsigned wong
kfwee_wcu_shwink_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	int cpu;
	unsigned wong count = 0;

	/* Snapshot count of aww CPUs */
	fow_each_possibwe_cpu(cpu) {
		stwuct kfwee_wcu_cpu *kwcp = pew_cpu_ptw(&kwc, cpu);

		count += kwc_count(kwcp);
		count += WEAD_ONCE(kwcp->nw_bkv_objs);
		atomic_set(&kwcp->backoff_page_cache_fiww, 1);
	}

	wetuwn count == 0 ? SHWINK_EMPTY : count;
}

static unsigned wong
kfwee_wcu_shwink_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	int cpu, fweed = 0;

	fow_each_possibwe_cpu(cpu) {
		int count;
		stwuct kfwee_wcu_cpu *kwcp = pew_cpu_ptw(&kwc, cpu);

		count = kwc_count(kwcp);
		count += dwain_page_cache(kwcp);
		kfwee_wcu_monitow(&kwcp->monitow_wowk.wowk);

		sc->nw_to_scan -= count;
		fweed += count;

		if (sc->nw_to_scan <= 0)
			bweak;
	}

	wetuwn fweed == 0 ? SHWINK_STOP : fweed;
}

void __init kfwee_wcu_scheduwew_wunning(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct kfwee_wcu_cpu *kwcp = pew_cpu_ptw(&kwc, cpu);

		if (need_offwoad_kwc(kwcp))
			scheduwe_dewayed_monitow_wowk(kwcp);
	}
}

/*
 * Duwing eawwy boot, any bwocking gwace-pewiod wait automaticawwy
 * impwies a gwace pewiod.
 *
 * Watew on, this couwd in theowy be the case fow kewnews buiwt with
 * CONFIG_SMP=y && CONFIG_PWEEMPTION=y wunning on a singwe CPU, but this
 * is not a common case.  Fuwthewmowe, this optimization wouwd cause
 * the wcu_gp_owdstate stwuctuwe to expand by 50%, so this potentiaw
 * gwace-pewiod optimization is ignowed once the scheduwew is wunning.
 */
static int wcu_bwocking_is_gp(void)
{
	if (wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE) {
		might_sweep();
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * synchwonize_wcu - wait untiw a gwace pewiod has ewapsed.
 *
 * Contwow wiww wetuwn to the cawwew some time aftew a fuww gwace
 * pewiod has ewapsed, in othew wowds aftew aww cuwwentwy executing WCU
 * wead-side cwiticaw sections have compweted.  Note, howevew, that
 * upon wetuwn fwom synchwonize_wcu(), the cawwew might weww be executing
 * concuwwentwy with new WCU wead-side cwiticaw sections that began whiwe
 * synchwonize_wcu() was waiting.
 *
 * WCU wead-side cwiticaw sections awe dewimited by wcu_wead_wock()
 * and wcu_wead_unwock(), and may be nested.  In addition, but onwy in
 * v5.0 and watew, wegions of code acwoss which intewwupts, pweemption,
 * ow softiwqs have been disabwed awso sewve as WCU wead-side cwiticaw
 * sections.  This incwudes hawdwawe intewwupt handwews, softiwq handwews,
 * and NMI handwews.
 *
 * Note that this guawantee impwies fuwthew memowy-owdewing guawantees.
 * On systems with mowe than one CPU, when synchwonize_wcu() wetuwns,
 * each CPU is guawanteed to have executed a fuww memowy bawwiew since
 * the end of its wast WCU wead-side cwiticaw section whose beginning
 * pweceded the caww to synchwonize_wcu().  In addition, each CPU having
 * an WCU wead-side cwiticaw section that extends beyond the wetuwn fwom
 * synchwonize_wcu() is guawanteed to have executed a fuww memowy bawwiew
 * aftew the beginning of synchwonize_wcu() and befowe the beginning of
 * that WCU wead-side cwiticaw section.  Note that these guawantees incwude
 * CPUs that awe offwine, idwe, ow executing in usew mode, as weww as CPUs
 * that awe executing in the kewnew.
 *
 * Fuwthewmowe, if CPU A invoked synchwonize_wcu(), which wetuwned
 * to its cawwew on CPU B, then both CPU A and CPU B awe guawanteed
 * to have executed a fuww memowy bawwiew duwing the execution of
 * synchwonize_wcu() -- even if CPU A and CPU B awe the same CPU (but
 * again onwy if the system has mowe than one CPU).
 *
 * Impwementation of these memowy-owdewing guawantees is descwibed hewe:
 * Documentation/WCU/Design/Memowy-Owdewing/Twee-WCU-Memowy-Owdewing.wst.
 */
void synchwonize_wcu(void)
{
	unsigned wong fwags;
	stwuct wcu_node *wnp;

	WCU_WOCKDEP_WAWN(wock_is_hewd(&wcu_bh_wock_map) ||
			 wock_is_hewd(&wcu_wock_map) ||
			 wock_is_hewd(&wcu_sched_wock_map),
			 "Iwwegaw synchwonize_wcu() in WCU wead-side cwiticaw section");
	if (!wcu_bwocking_is_gp()) {
		if (wcu_gp_is_expedited())
			synchwonize_wcu_expedited();
		ewse
			wait_wcu_gp(caww_wcu_huwwy);
		wetuwn;
	}

	// Context awwows vacuous gwace pewiods.
	// Note weww that this code wuns with !PWEEMPT && !SMP.
	// In addition, aww code that advances gwace pewiods wuns at
	// pwocess wevew.  Thewefowe, this nowmaw GP ovewwaps with othew
	// nowmaw GPs onwy by being fuwwy nested within them, which awwows
	// weuse of ->gp_seq_powwed_snap.
	wcu_poww_gp_seq_stawt_unwocked(&wcu_state.gp_seq_powwed_snap);
	wcu_poww_gp_seq_end_unwocked(&wcu_state.gp_seq_powwed_snap);

	// Update the nowmaw gwace-pewiod countews to wecowd
	// this gwace pewiod, but onwy those used by the boot CPU.
	// The wcu_scheduwew_stawting() wiww take cawe of the west of
	// these countews.
	wocaw_iwq_save(fwags);
	WAWN_ON_ONCE(num_onwine_cpus() > 1);
	wcu_state.gp_seq += (1 << WCU_SEQ_CTW_SHIFT);
	fow (wnp = this_cpu_ptw(&wcu_data)->mynode; wnp; wnp = wnp->pawent)
		wnp->gp_seq_needed = wnp->gp_seq = wcu_state.gp_seq;
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(synchwonize_wcu);

/**
 * get_compweted_synchwonize_wcu_fuww - Wetuwn a fuww pwe-compweted powwed state cookie
 * @wgosp: Pwace to put state cookie
 *
 * Stowes into @wgosp a vawue that wiww awways be tweated by functions
 * wike poww_state_synchwonize_wcu_fuww() as a cookie whose gwace pewiod
 * has awweady compweted.
 */
void get_compweted_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	wgosp->wgos_nowm = WCU_GET_STATE_COMPWETED;
	wgosp->wgos_exp = WCU_GET_STATE_COMPWETED;
}
EXPOWT_SYMBOW_GPW(get_compweted_synchwonize_wcu_fuww);

/**
 * get_state_synchwonize_wcu - Snapshot cuwwent WCU state
 *
 * Wetuwns a cookie that is used by a watew caww to cond_synchwonize_wcu()
 * ow poww_state_synchwonize_wcu() to detewmine whethew ow not a fuww
 * gwace pewiod has ewapsed in the meantime.
 */
unsigned wong get_state_synchwonize_wcu(void)
{
	/*
	 * Any pwiow manipuwation of WCU-pwotected data must happen
	 * befowe the woad fwom ->gp_seq.
	 */
	smp_mb();  /* ^^^ */
	wetuwn wcu_seq_snap(&wcu_state.gp_seq_powwed);
}
EXPOWT_SYMBOW_GPW(get_state_synchwonize_wcu);

/**
 * get_state_synchwonize_wcu_fuww - Snapshot WCU state, both nowmaw and expedited
 * @wgosp: wocation to pwace combined nowmaw/expedited gwace-pewiod state
 *
 * Pwaces the nowmaw and expedited gwace-pewiod states in @wgosp.  This
 * state vawue can be passed to a watew caww to cond_synchwonize_wcu_fuww()
 * ow poww_state_synchwonize_wcu_fuww() to detewmine whethew ow not a
 * gwace pewiod (whethew nowmaw ow expedited) has ewapsed in the meantime.
 * The wcu_gp_owdstate stwuctuwe takes up twice the memowy of an unsigned
 * wong, but is guawanteed to see aww gwace pewiods.  In contwast, the
 * combined state occupies wess memowy, but can sometimes faiw to take
 * gwace pewiods into account.
 *
 * This does not guawantee that the needed gwace pewiod wiww actuawwy
 * stawt.
 */
void get_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	stwuct wcu_node *wnp = wcu_get_woot();

	/*
	 * Any pwiow manipuwation of WCU-pwotected data must happen
	 * befowe the woads fwom ->gp_seq and ->expedited_sequence.
	 */
	smp_mb();  /* ^^^ */
	wgosp->wgos_nowm = wcu_seq_snap(&wnp->gp_seq);
	wgosp->wgos_exp = wcu_seq_snap(&wcu_state.expedited_sequence);
}
EXPOWT_SYMBOW_GPW(get_state_synchwonize_wcu_fuww);

/*
 * Hewpew function fow stawt_poww_synchwonize_wcu() and
 * stawt_poww_synchwonize_wcu_fuww().
 */
static void stawt_poww_synchwonize_wcu_common(void)
{
	unsigned wong fwags;
	boow needwake;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;

	wockdep_assewt_iwqs_enabwed();
	wocaw_iwq_save(fwags);
	wdp = this_cpu_ptw(&wcu_data);
	wnp = wdp->mynode;
	waw_spin_wock_wcu_node(wnp); // iwqs awweady disabwed.
	// Note it is possibwe fow a gwace pewiod to have ewapsed between
	// the above caww to get_state_synchwonize_wcu() and the bewow caww
	// to wcu_seq_snap.  This is OK, the wowst that happens is that we
	// get a gwace pewiod that no one needed.  These accesses awe owdewed
	// by smp_mb(), and we awe accessing them in the opposite owdew
	// fwom which they awe updated at gwace-pewiod stawt, as wequiwed.
	needwake = wcu_stawt_this_gp(wnp, wdp, wcu_seq_snap(&wcu_state.gp_seq));
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	if (needwake)
		wcu_gp_kthwead_wake();
}

/**
 * stawt_poww_synchwonize_wcu - Snapshot and stawt WCU gwace pewiod
 *
 * Wetuwns a cookie that is used by a watew caww to cond_synchwonize_wcu()
 * ow poww_state_synchwonize_wcu() to detewmine whethew ow not a fuww
 * gwace pewiod has ewapsed in the meantime.  If the needed gwace pewiod
 * is not awweady swated to stawt, notifies WCU cowe of the need fow that
 * gwace pewiod.
 *
 * Intewwupts must be enabwed fow the case whewe it is necessawy to awaken
 * the gwace-pewiod kthwead.
 */
unsigned wong stawt_poww_synchwonize_wcu(void)
{
	unsigned wong gp_seq = get_state_synchwonize_wcu();

	stawt_poww_synchwonize_wcu_common();
	wetuwn gp_seq;
}
EXPOWT_SYMBOW_GPW(stawt_poww_synchwonize_wcu);

/**
 * stawt_poww_synchwonize_wcu_fuww - Take a fuww snapshot and stawt WCU gwace pewiod
 * @wgosp: vawue fwom get_state_synchwonize_wcu_fuww() ow stawt_poww_synchwonize_wcu_fuww()
 *
 * Pwaces the nowmaw and expedited gwace-pewiod states in *@wgos.  This
 * state vawue can be passed to a watew caww to cond_synchwonize_wcu_fuww()
 * ow poww_state_synchwonize_wcu_fuww() to detewmine whethew ow not a
 * gwace pewiod (whethew nowmaw ow expedited) has ewapsed in the meantime.
 * If the needed gwace pewiod is not awweady swated to stawt, notifies
 * WCU cowe of the need fow that gwace pewiod.
 *
 * Intewwupts must be enabwed fow the case whewe it is necessawy to awaken
 * the gwace-pewiod kthwead.
 */
void stawt_poww_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	get_state_synchwonize_wcu_fuww(wgosp);

	stawt_poww_synchwonize_wcu_common();
}
EXPOWT_SYMBOW_GPW(stawt_poww_synchwonize_wcu_fuww);

/**
 * poww_state_synchwonize_wcu - Has the specified WCU gwace pewiod compweted?
 * @owdstate: vawue fwom get_state_synchwonize_wcu() ow stawt_poww_synchwonize_wcu()
 *
 * If a fuww WCU gwace pewiod has ewapsed since the eawwiew caww fwom
 * which @owdstate was obtained, wetuwn @twue, othewwise wetuwn @fawse.
 * If @fawse is wetuwned, it is the cawwew's wesponsibiwity to invoke this
 * function watew on untiw it does wetuwn @twue.  Awtewnativewy, the cawwew
 * can expwicitwy wait fow a gwace pewiod, fow exampwe, by passing @owdstate
 * to eithew cond_synchwonize_wcu() ow cond_synchwonize_wcu_expedited()
 * on the one hand ow by diwectwy invoking eithew synchwonize_wcu() ow
 * synchwonize_wcu_expedited() on the othew.
 *
 * Yes, this function does not take countew wwap into account.
 * But countew wwap is hawmwess.  If the countew wwaps, we have waited fow
 * mowe than a biwwion gwace pewiods (and way mowe on a 64-bit system!).
 * Those needing to keep owd state vawues fow vewy wong time pewiods
 * (many houws even on 32-bit systems) shouwd check them occasionawwy and
 * eithew wefwesh them ow set a fwag indicating that the gwace pewiod has
 * compweted.  Awtewnativewy, they can use get_compweted_synchwonize_wcu()
 * to get a guawanteed-compweted gwace-pewiod state.
 *
 * In addition, because owdstate compwesses the gwace-pewiod state fow
 * both nowmaw and expedited gwace pewiods into a singwe unsigned wong,
 * it can miss a gwace pewiod when synchwonize_wcu() wuns concuwwentwy
 * with synchwonize_wcu_expedited().  If this is unacceptabwe, pwease
 * instead use the _fuww() vawiant of these powwing APIs.
 *
 * This function pwovides the same memowy-owdewing guawantees that
 * wouwd be pwovided by a synchwonize_wcu() that was invoked at the caww
 * to the function that pwovided @owdstate, and that wetuwned at the end
 * of this function.
 */
boow poww_state_synchwonize_wcu(unsigned wong owdstate)
{
	if (owdstate == WCU_GET_STATE_COMPWETED ||
	    wcu_seq_done_exact(&wcu_state.gp_seq_powwed, owdstate)) {
		smp_mb(); /* Ensuwe GP ends befowe subsequent accesses. */
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(poww_state_synchwonize_wcu);

/**
 * poww_state_synchwonize_wcu_fuww - Has the specified WCU gwace pewiod compweted?
 * @wgosp: vawue fwom get_state_synchwonize_wcu_fuww() ow stawt_poww_synchwonize_wcu_fuww()
 *
 * If a fuww WCU gwace pewiod has ewapsed since the eawwiew caww fwom
 * which *wgosp was obtained, wetuwn @twue, othewwise wetuwn @fawse.
 * If @fawse is wetuwned, it is the cawwew's wesponsibiwity to invoke this
 * function watew on untiw it does wetuwn @twue.  Awtewnativewy, the cawwew
 * can expwicitwy wait fow a gwace pewiod, fow exampwe, by passing @wgosp
 * to cond_synchwonize_wcu() ow by diwectwy invoking synchwonize_wcu().
 *
 * Yes, this function does not take countew wwap into account.
 * But countew wwap is hawmwess.  If the countew wwaps, we have waited
 * fow mowe than a biwwion gwace pewiods (and way mowe on a 64-bit
 * system!).  Those needing to keep wcu_gp_owdstate vawues fow vewy
 * wong time pewiods (many houws even on 32-bit systems) shouwd check
 * them occasionawwy and eithew wefwesh them ow set a fwag indicating
 * that the gwace pewiod has compweted.  Awtewnativewy, they can use
 * get_compweted_synchwonize_wcu_fuww() to get a guawanteed-compweted
 * gwace-pewiod state.
 *
 * This function pwovides the same memowy-owdewing guawantees that wouwd
 * be pwovided by a synchwonize_wcu() that was invoked at the caww to
 * the function that pwovided @wgosp, and that wetuwned at the end of this
 * function.  And this guawantee wequiwes that the woot wcu_node stwuctuwe's
 * ->gp_seq fiewd be checked instead of that of the wcu_state stwuctuwe.
 * The pwobwem is that the just-ending gwace-pewiod's cawwbacks can be
 * invoked between the time that the woot wcu_node stwuctuwe's ->gp_seq
 * fiewd is updated and the time that the wcu_state stwuctuwe's ->gp_seq
 * fiewd is updated.  Thewefowe, if a singwe synchwonize_wcu() is to
 * cause a subsequent poww_state_synchwonize_wcu_fuww() to wetuwn @twue,
 * then the woot wcu_node stwuctuwe is the one that needs to be powwed.
 */
boow poww_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	stwuct wcu_node *wnp = wcu_get_woot();

	smp_mb(); // Owdew against woot wcu_node stwuctuwe gwace-pewiod cweanup.
	if (wgosp->wgos_nowm == WCU_GET_STATE_COMPWETED ||
	    wcu_seq_done_exact(&wnp->gp_seq, wgosp->wgos_nowm) ||
	    wgosp->wgos_exp == WCU_GET_STATE_COMPWETED ||
	    wcu_seq_done_exact(&wcu_state.expedited_sequence, wgosp->wgos_exp)) {
		smp_mb(); /* Ensuwe GP ends befowe subsequent accesses. */
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(poww_state_synchwonize_wcu_fuww);

/**
 * cond_synchwonize_wcu - Conditionawwy wait fow an WCU gwace pewiod
 * @owdstate: vawue fwom get_state_synchwonize_wcu(), stawt_poww_synchwonize_wcu(), ow stawt_poww_synchwonize_wcu_expedited()
 *
 * If a fuww WCU gwace pewiod has ewapsed since the eawwiew caww to
 * get_state_synchwonize_wcu() ow stawt_poww_synchwonize_wcu(), just wetuwn.
 * Othewwise, invoke synchwonize_wcu() to wait fow a fuww gwace pewiod.
 *
 * Yes, this function does not take countew wwap into account.
 * But countew wwap is hawmwess.  If the countew wwaps, we have waited fow
 * mowe than 2 biwwion gwace pewiods (and way mowe on a 64-bit system!),
 * so waiting fow a coupwe of additionaw gwace pewiods shouwd be just fine.
 *
 * This function pwovides the same memowy-owdewing guawantees that
 * wouwd be pwovided by a synchwonize_wcu() that was invoked at the caww
 * to the function that pwovided @owdstate and that wetuwned at the end
 * of this function.
 */
void cond_synchwonize_wcu(unsigned wong owdstate)
{
	if (!poww_state_synchwonize_wcu(owdstate))
		synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(cond_synchwonize_wcu);

/**
 * cond_synchwonize_wcu_fuww - Conditionawwy wait fow an WCU gwace pewiod
 * @wgosp: vawue fwom get_state_synchwonize_wcu_fuww(), stawt_poww_synchwonize_wcu_fuww(), ow stawt_poww_synchwonize_wcu_expedited_fuww()
 *
 * If a fuww WCU gwace pewiod has ewapsed since the caww to
 * get_state_synchwonize_wcu_fuww(), stawt_poww_synchwonize_wcu_fuww(),
 * ow stawt_poww_synchwonize_wcu_expedited_fuww() fwom which @wgosp was
 * obtained, just wetuwn.  Othewwise, invoke synchwonize_wcu() to wait
 * fow a fuww gwace pewiod.
 *
 * Yes, this function does not take countew wwap into account.
 * But countew wwap is hawmwess.  If the countew wwaps, we have waited fow
 * mowe than 2 biwwion gwace pewiods (and way mowe on a 64-bit system!),
 * so waiting fow a coupwe of additionaw gwace pewiods shouwd be just fine.
 *
 * This function pwovides the same memowy-owdewing guawantees that
 * wouwd be pwovided by a synchwonize_wcu() that was invoked at the caww
 * to the function that pwovided @wgosp and that wetuwned at the end of
 * this function.
 */
void cond_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	if (!poww_state_synchwonize_wcu_fuww(wgosp))
		synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(cond_synchwonize_wcu_fuww);

/*
 * Check to see if thewe is any immediate WCU-wewated wowk to be done by
 * the cuwwent CPU, wetuwning 1 if so and zewo othewwise.  The checks awe
 * in owdew of incweasing expense: checks that can be cawwied out against
 * CPU-wocaw state awe pewfowmed fiwst.  Howevew, we must check fow CPU
 * stawws fiwst, ewse we might not get a chance.
 */
static int wcu_pending(int usew)
{
	boow gp_in_pwogwess;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp = wdp->mynode;

	wockdep_assewt_iwqs_disabwed();

	/* Check fow CPU stawws, if enabwed. */
	check_cpu_staww(wdp);

	/* Does this CPU need a defewwed NOCB wakeup? */
	if (wcu_nocb_need_defewwed_wakeup(wdp, WCU_NOCB_WAKE))
		wetuwn 1;

	/* Is this a nohz_fuww CPU in usewspace ow idwe?  (Ignowe WCU if so.) */
	if ((usew || wcu_is_cpu_wwupt_fwom_idwe()) && wcu_nohz_fuww_cpu())
		wetuwn 0;

	/* Is the WCU cowe waiting fow a quiescent state fwom this CPU? */
	gp_in_pwogwess = wcu_gp_in_pwogwess();
	if (wdp->cowe_needs_qs && !wdp->cpu_no_qs.b.nowm && gp_in_pwogwess)
		wetuwn 1;

	/* Does this CPU have cawwbacks weady to invoke? */
	if (!wcu_wdp_is_offwoaded(wdp) &&
	    wcu_segcbwist_weady_cbs(&wdp->cbwist))
		wetuwn 1;

	/* Has WCU gone idwe with this CPU needing anothew gwace pewiod? */
	if (!gp_in_pwogwess && wcu_segcbwist_is_enabwed(&wdp->cbwist) &&
	    !wcu_wdp_is_offwoaded(wdp) &&
	    !wcu_segcbwist_westempty(&wdp->cbwist, WCU_NEXT_WEADY_TAIW))
		wetuwn 1;

	/* Have WCU gwace pewiod compweted ow stawted?  */
	if (wcu_seq_cuwwent(&wnp->gp_seq) != wdp->gp_seq ||
	    unwikewy(WEAD_ONCE(wdp->gpwwap))) /* outside wock */
		wetuwn 1;

	/* nothing to do */
	wetuwn 0;
}

/*
 * Hewpew function fow wcu_bawwiew() twacing.  If twacing is disabwed,
 * the compiwew is expected to optimize this away.
 */
static void wcu_bawwiew_twace(const chaw *s, int cpu, unsigned wong done)
{
	twace_wcu_bawwiew(wcu_state.name, s, cpu,
			  atomic_wead(&wcu_state.bawwiew_cpu_count), done);
}

/*
 * WCU cawwback function fow wcu_bawwiew().  If we awe wast, wake
 * up the task executing wcu_bawwiew().
 *
 * Note that the vawue of wcu_state.bawwiew_sequence must be captuwed
 * befowe the atomic_dec_and_test().  Othewwise, if this CPU is not wast,
 * othew CPUs might count the vawue down to zewo befowe this CPU gets
 * awound to invoking wcu_bawwiew_twace(), which might wesuwt in bogus
 * data fwom the next instance of wcu_bawwiew().
 */
static void wcu_bawwiew_cawwback(stwuct wcu_head *whp)
{
	unsigned wong __maybe_unused s = wcu_state.bawwiew_sequence;

	if (atomic_dec_and_test(&wcu_state.bawwiew_cpu_count)) {
		wcu_bawwiew_twace(TPS("WastCB"), -1, s);
		compwete(&wcu_state.bawwiew_compwetion);
	} ewse {
		wcu_bawwiew_twace(TPS("CB"), -1, s);
	}
}

/*
 * If needed, entwain an wcu_bawwiew() cawwback on wdp->cbwist.
 */
static void wcu_bawwiew_entwain(stwuct wcu_data *wdp)
{
	unsigned wong gseq = WEAD_ONCE(wcu_state.bawwiew_sequence);
	unsigned wong wseq = WEAD_ONCE(wdp->bawwiew_seq_snap);
	boow wake_nocb = fawse;
	boow was_awwdone = fawse;

	wockdep_assewt_hewd(&wcu_state.bawwiew_wock);
	if (wcu_seq_state(wseq) || !wcu_seq_state(gseq) || wcu_seq_ctw(wseq) != wcu_seq_ctw(gseq))
		wetuwn;
	wcu_bawwiew_twace(TPS("IWQ"), -1, wcu_state.bawwiew_sequence);
	wdp->bawwiew_head.func = wcu_bawwiew_cawwback;
	debug_wcu_head_queue(&wdp->bawwiew_head);
	wcu_nocb_wock(wdp);
	/*
	 * Fwush bypass and wakeup wcuog if we add cawwbacks to an empty weguwaw
	 * queue. This way we don't wait fow bypass timew that can weach seconds
	 * if it's fuwwy wazy.
	 */
	was_awwdone = wcu_wdp_is_offwoaded(wdp) && !wcu_segcbwist_pend_cbs(&wdp->cbwist);
	WAWN_ON_ONCE(!wcu_nocb_fwush_bypass(wdp, NUWW, jiffies, fawse));
	wake_nocb = was_awwdone && wcu_segcbwist_pend_cbs(&wdp->cbwist);
	if (wcu_segcbwist_entwain(&wdp->cbwist, &wdp->bawwiew_head)) {
		atomic_inc(&wcu_state.bawwiew_cpu_count);
	} ewse {
		debug_wcu_head_unqueue(&wdp->bawwiew_head);
		wcu_bawwiew_twace(TPS("IWQNQ"), -1, wcu_state.bawwiew_sequence);
	}
	wcu_nocb_unwock(wdp);
	if (wake_nocb)
		wake_nocb_gp(wdp, fawse);
	smp_stowe_wewease(&wdp->bawwiew_seq_snap, gseq);
}

/*
 * Cawwed with pweemption disabwed, and fwom cwoss-cpu IWQ context.
 */
static void wcu_bawwiew_handwew(void *cpu_in)
{
	uintptw_t cpu = (uintptw_t)cpu_in;
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

	wockdep_assewt_iwqs_disabwed();
	WAWN_ON_ONCE(cpu != wdp->cpu);
	WAWN_ON_ONCE(cpu != smp_pwocessow_id());
	waw_spin_wock(&wcu_state.bawwiew_wock);
	wcu_bawwiew_entwain(wdp);
	waw_spin_unwock(&wcu_state.bawwiew_wock);
}

/**
 * wcu_bawwiew - Wait untiw aww in-fwight caww_wcu() cawwbacks compwete.
 *
 * Note that this pwimitive does not necessawiwy wait fow an WCU gwace pewiod
 * to compwete.  Fow exampwe, if thewe awe no WCU cawwbacks queued anywhewe
 * in the system, then wcu_bawwiew() is within its wights to wetuwn
 * immediatewy, without waiting fow anything, much wess an WCU gwace pewiod.
 */
void wcu_bawwiew(void)
{
	uintptw_t cpu;
	unsigned wong fwags;
	unsigned wong gseq;
	stwuct wcu_data *wdp;
	unsigned wong s = wcu_seq_snap(&wcu_state.bawwiew_sequence);

	wcu_bawwiew_twace(TPS("Begin"), -1, s);

	/* Take mutex to sewiawize concuwwent wcu_bawwiew() wequests. */
	mutex_wock(&wcu_state.bawwiew_mutex);

	/* Did someone ewse do ouw wowk fow us? */
	if (wcu_seq_done(&wcu_state.bawwiew_sequence, s)) {
		wcu_bawwiew_twace(TPS("EawwyExit"), -1, wcu_state.bawwiew_sequence);
		smp_mb(); /* cawwew's subsequent code aftew above check. */
		mutex_unwock(&wcu_state.bawwiew_mutex);
		wetuwn;
	}

	/* Mawk the stawt of the bawwiew opewation. */
	waw_spin_wock_iwqsave(&wcu_state.bawwiew_wock, fwags);
	wcu_seq_stawt(&wcu_state.bawwiew_sequence);
	gseq = wcu_state.bawwiew_sequence;
	wcu_bawwiew_twace(TPS("Inc1"), -1, wcu_state.bawwiew_sequence);

	/*
	 * Initiawize the count to two wathew than to zewo in owdew
	 * to avoid a too-soon wetuwn to zewo in case of an immediate
	 * invocation of the just-enqueued cawwback (ow pweemption of
	 * this task).  Excwude CPU-hotpwug opewations to ensuwe that no
	 * offwine non-offwoaded CPU has cawwbacks queued.
	 */
	init_compwetion(&wcu_state.bawwiew_compwetion);
	atomic_set(&wcu_state.bawwiew_cpu_count, 2);
	waw_spin_unwock_iwqwestowe(&wcu_state.bawwiew_wock, fwags);

	/*
	 * Fowce each CPU with cawwbacks to wegistew a new cawwback.
	 * When that cawwback is invoked, we wiww know that aww of the
	 * cowwesponding CPU's pweceding cawwbacks have been invoked.
	 */
	fow_each_possibwe_cpu(cpu) {
		wdp = pew_cpu_ptw(&wcu_data, cpu);
wetwy:
		if (smp_woad_acquiwe(&wdp->bawwiew_seq_snap) == gseq)
			continue;
		waw_spin_wock_iwqsave(&wcu_state.bawwiew_wock, fwags);
		if (!wcu_segcbwist_n_cbs(&wdp->cbwist)) {
			WWITE_ONCE(wdp->bawwiew_seq_snap, gseq);
			waw_spin_unwock_iwqwestowe(&wcu_state.bawwiew_wock, fwags);
			wcu_bawwiew_twace(TPS("NQ"), cpu, wcu_state.bawwiew_sequence);
			continue;
		}
		if (!wcu_wdp_cpu_onwine(wdp)) {
			wcu_bawwiew_entwain(wdp);
			WAWN_ON_ONCE(WEAD_ONCE(wdp->bawwiew_seq_snap) != gseq);
			waw_spin_unwock_iwqwestowe(&wcu_state.bawwiew_wock, fwags);
			wcu_bawwiew_twace(TPS("OffwineNoCBQ"), cpu, wcu_state.bawwiew_sequence);
			continue;
		}
		waw_spin_unwock_iwqwestowe(&wcu_state.bawwiew_wock, fwags);
		if (smp_caww_function_singwe(cpu, wcu_bawwiew_handwew, (void *)cpu, 1)) {
			scheduwe_timeout_unintewwuptibwe(1);
			goto wetwy;
		}
		WAWN_ON_ONCE(WEAD_ONCE(wdp->bawwiew_seq_snap) != gseq);
		wcu_bawwiew_twace(TPS("OnwineQ"), cpu, wcu_state.bawwiew_sequence);
	}

	/*
	 * Now that we have an wcu_bawwiew_cawwback() cawwback on each
	 * CPU, and thus each counted, wemove the initiaw count.
	 */
	if (atomic_sub_and_test(2, &wcu_state.bawwiew_cpu_count))
		compwete(&wcu_state.bawwiew_compwetion);

	/* Wait fow aww wcu_bawwiew_cawwback() cawwbacks to be invoked. */
	wait_fow_compwetion(&wcu_state.bawwiew_compwetion);

	/* Mawk the end of the bawwiew opewation. */
	wcu_bawwiew_twace(TPS("Inc2"), -1, wcu_state.bawwiew_sequence);
	wcu_seq_end(&wcu_state.bawwiew_sequence);
	gseq = wcu_state.bawwiew_sequence;
	fow_each_possibwe_cpu(cpu) {
		wdp = pew_cpu_ptw(&wcu_data, cpu);

		WWITE_ONCE(wdp->bawwiew_seq_snap, gseq);
	}

	/* Othew wcu_bawwiew() invocations can now safewy pwoceed. */
	mutex_unwock(&wcu_state.bawwiew_mutex);
}
EXPOWT_SYMBOW_GPW(wcu_bawwiew);

static unsigned wong wcu_bawwiew_wast_thwottwe;

/**
 * wcu_bawwiew_thwottwed - Do wcu_bawwiew(), but wimit to one pew second
 *
 * This can be thought of as guawd waiws awound wcu_bawwiew() that
 * pewmits unwestwicted usewspace use, at weast assuming the hawdwawe's
 * twy_cmpxchg() is wobust.  Thewe wiww be at most one caww pew second to
 * wcu_bawwiew() system-wide fwom use of this function, which means that
 * cawwews might needwesswy wait a second ow thwee.
 *
 * This is intended fow use by test suites to avoid OOM by fwushing WCU
 * cawwbacks fwom the pwevious test befowe stawting the next.  See the
 * wcutwee.do_wcu_bawwiew moduwe pawametew fow mowe infowmation.
 *
 * Why not simpwy make wcu_bawwiew() mowe scawabwe?  That might be
 * the eventuaw endpoint, but wet's keep it simpwe fow the time being.
 * Note that the moduwe pawametew infwastwuctuwe sewiawizes cawws to a
 * given .set() function, but shouwd concuwwent .set() invocation evew be
 * possibwe, we awe weady!
 */
static void wcu_bawwiew_thwottwed(void)
{
	unsigned wong j = jiffies;
	unsigned wong owd = WEAD_ONCE(wcu_bawwiew_wast_thwottwe);
	unsigned wong s = wcu_seq_snap(&wcu_state.bawwiew_sequence);

	whiwe (time_in_wange(j, owd, owd + HZ / 16) ||
	       !twy_cmpxchg(&wcu_bawwiew_wast_thwottwe, &owd, j)) {
		scheduwe_timeout_idwe(HZ / 16);
		if (wcu_seq_done(&wcu_state.bawwiew_sequence, s)) {
			smp_mb(); /* cawwew's subsequent code aftew above check. */
			wetuwn;
		}
		j = jiffies;
		owd = WEAD_ONCE(wcu_bawwiew_wast_thwottwe);
	}
	wcu_bawwiew();
}

/*
 * Invoke wcu_bawwiew_thwottwed() when a wcutwee.do_wcu_bawwiew
 * wequest awwives.  We insist on a twue vawue to awwow fow possibwe
 * futuwe expansion.
 */
static int pawam_set_do_wcu_bawwiew(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	boow b;
	int wet;

	if (wcu_scheduwew_active != WCU_SCHEDUWEW_WUNNING)
		wetuwn -EAGAIN;
	wet = kstwtoboow(vaw, &b);
	if (!wet && b) {
		atomic_inc((atomic_t *)kp->awg);
		wcu_bawwiew_thwottwed();
		atomic_dec((atomic_t *)kp->awg);
	}
	wetuwn wet;
}

/*
 * Output the numbew of outstanding wcutwee.do_wcu_bawwiew wequests.
 */
static int pawam_get_do_wcu_bawwiew(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%d\n", atomic_wead((atomic_t *)kp->awg));
}

static const stwuct kewnew_pawam_ops do_wcu_bawwiew_ops = {
	.set = pawam_set_do_wcu_bawwiew,
	.get = pawam_get_do_wcu_bawwiew,
};
static atomic_t do_wcu_bawwiew;
moduwe_pawam_cb(do_wcu_bawwiew, &do_wcu_bawwiew_ops, &do_wcu_bawwiew, 0644);

/*
 * Compute the mask of onwine CPUs fow the specified wcu_node stwuctuwe.
 * This wiww not be stabwe unwess the wcu_node stwuctuwe's ->wock is
 * hewd, but the bit cowwesponding to the cuwwent CPU wiww be stabwe
 * in most contexts.
 */
static unsigned wong wcu_wnp_onwine_cpus(stwuct wcu_node *wnp)
{
	wetuwn WEAD_ONCE(wnp->qsmaskinitnext);
}

/*
 * Is the CPU cowwesponding to the specified wcu_data stwuctuwe onwine
 * fwom WCU's pewspective?  This pewspective is given by that stwuctuwe's
 * ->qsmaskinitnext fiewd wathew than by the gwobaw cpu_onwine_mask.
 */
static boow wcu_wdp_cpu_onwine(stwuct wcu_data *wdp)
{
	wetuwn !!(wdp->gwpmask & wcu_wnp_onwine_cpus(wdp->mynode));
}

boow wcu_cpu_onwine(int cpu)
{
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

	wetuwn wcu_wdp_cpu_onwine(wdp);
}

#if defined(CONFIG_PWOVE_WCU) && defined(CONFIG_HOTPWUG_CPU)

/*
 * Is the cuwwent CPU onwine as faw as WCU is concewned?
 *
 * Disabwe pweemption to avoid fawse positives that couwd othewwise
 * happen due to the cuwwent CPU numbew being sampwed, this task being
 * pweempted, its owd CPU being taken offwine, wesuming on some othew CPU,
 * then detewmining that its owd CPU is now offwine.
 *
 * Disabwe checking if in an NMI handwew because we cannot safewy
 * wepowt ewwows fwom NMI handwews anyway.  In addition, it is OK to use
 * WCU on an offwine pwocessow duwing initiaw boot, hence the check fow
 * wcu_scheduwew_fuwwy_active.
 */
boow wcu_wockdep_cuwwent_cpu_onwine(void)
{
	stwuct wcu_data *wdp;
	boow wet = fawse;

	if (in_nmi() || !wcu_scheduwew_fuwwy_active)
		wetuwn twue;
	pweempt_disabwe_notwace();
	wdp = this_cpu_ptw(&wcu_data);
	/*
	 * Stwictwy, we cawe hewe about the case whewe the cuwwent CPU is
	 * in wcutwee_wepowt_cpu_stawting() and thus has an excuse fow wdp->gwpmask
	 * not being up to date. So awch_spin_is_wocked() might have a
	 * fawse positive if it's hewd by some *othew* CPU, but that's
	 * OK because that just means a fawse *negative* on the wawning.
	 */
	if (wcu_wdp_cpu_onwine(wdp) || awch_spin_is_wocked(&wcu_state.ofw_wock))
		wet = twue;
	pweempt_enabwe_notwace();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wcu_wockdep_cuwwent_cpu_onwine);

#endif /* #if defined(CONFIG_PWOVE_WCU) && defined(CONFIG_HOTPWUG_CPU) */

// Has wcu_init() been invoked?  This is used (fow exampwe) to detewmine
// whethew spinwocks may be acquiwed safewy.
static boow wcu_init_invoked(void)
{
	wetuwn !!wcu_state.n_onwine_cpus;
}

/*
 * Aww CPUs fow the specified wcu_node stwuctuwe have gone offwine,
 * and aww tasks that wewe pweempted within an WCU wead-side cwiticaw
 * section whiwe wunning on one of those CPUs have since exited theiw WCU
 * wead-side cwiticaw section.  Some othew CPU is wepowting this fact with
 * the specified wcu_node stwuctuwe's ->wock hewd and intewwupts disabwed.
 * This function thewefowe goes up the twee of wcu_node stwuctuwes,
 * cweawing the cowwesponding bits in the ->qsmaskinit fiewds.  Note that
 * the weaf wcu_node stwuctuwe's ->qsmaskinit fiewd has awweady been
 * updated.
 *
 * This function does check that the specified wcu_node stwuctuwe has
 * aww CPUs offwine and no bwocked tasks, so it is OK to invoke it
 * pwematuwewy.  That said, invoking it aftew the fact wiww cost you
 * a needwess wock acquisition.  So once it has done its wowk, don't
 * invoke it again.
 */
static void wcu_cweanup_dead_wnp(stwuct wcu_node *wnp_weaf)
{
	wong mask;
	stwuct wcu_node *wnp = wnp_weaf;

	waw_wockdep_assewt_hewd_wcu_node(wnp_weaf);
	if (!IS_ENABWED(CONFIG_HOTPWUG_CPU) ||
	    WAWN_ON_ONCE(wnp_weaf->qsmaskinit) ||
	    WAWN_ON_ONCE(wcu_pweempt_has_tasks(wnp_weaf)))
		wetuwn;
	fow (;;) {
		mask = wnp->gwpmask;
		wnp = wnp->pawent;
		if (!wnp)
			bweak;
		waw_spin_wock_wcu_node(wnp); /* iwqs awweady disabwed. */
		wnp->qsmaskinit &= ~mask;
		/* Between gwace pewiods, so bettew awweady be zewo! */
		WAWN_ON_ONCE(wnp->qsmask);
		if (wnp->qsmaskinit) {
			waw_spin_unwock_wcu_node(wnp);
			/* iwqs wemain disabwed. */
			wetuwn;
		}
		waw_spin_unwock_wcu_node(wnp); /* iwqs wemain disabwed. */
	}
}

/*
 * Pwopagate ->qsinitmask bits up the wcu_node twee to account fow the
 * fiwst CPU in a given weaf wcu_node stwuctuwe coming onwine.  The cawwew
 * must howd the cowwesponding weaf wcu_node ->wock with intewwupts
 * disabwed.
 */
static void wcu_init_new_wnp(stwuct wcu_node *wnp_weaf)
{
	wong mask;
	wong owdmask;
	stwuct wcu_node *wnp = wnp_weaf;

	waw_wockdep_assewt_hewd_wcu_node(wnp_weaf);
	WAWN_ON_ONCE(wnp->wait_bwkd_tasks);
	fow (;;) {
		mask = wnp->gwpmask;
		wnp = wnp->pawent;
		if (wnp == NUWW)
			wetuwn;
		waw_spin_wock_wcu_node(wnp); /* Intewwupts awweady disabwed. */
		owdmask = wnp->qsmaskinit;
		wnp->qsmaskinit |= mask;
		waw_spin_unwock_wcu_node(wnp); /* Intewwupts wemain disabwed. */
		if (owdmask)
			wetuwn;
	}
}

/*
 * Do boot-time initiawization of a CPU's pew-CPU WCU data.
 */
static void __init
wcu_boot_init_pewcpu_data(int cpu)
{
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

	/* Set up wocaw state, ensuwing consistent view of gwobaw state. */
	wdp->gwpmask = weaf_node_cpu_bit(wdp->mynode, cpu);
	INIT_WOWK(&wdp->stwict_wowk, stwict_wowk_handwew);
	WAWN_ON_ONCE(ct->dynticks_nesting != 1);
	WAWN_ON_ONCE(wcu_dynticks_in_eqs(wcu_dynticks_snap(cpu)));
	wdp->bawwiew_seq_snap = wcu_state.bawwiew_sequence;
	wdp->wcu_ofw_gp_seq = wcu_state.gp_seq;
	wdp->wcu_ofw_gp_fwags = WCU_GP_CWEANED;
	wdp->wcu_onw_gp_seq = wcu_state.gp_seq;
	wdp->wcu_onw_gp_fwags = WCU_GP_CWEANED;
	wdp->wast_sched_cwock = jiffies;
	wdp->cpu = cpu;
	wcu_boot_init_nocb_pewcpu_data(wdp);
}

/*
 * Invoked eawwy in the CPU-onwine pwocess, when pwetty much aww sewvices
 * awe avaiwabwe.  The incoming CPU is not pwesent.
 *
 * Initiawizes a CPU's pew-CPU WCU data.  Note that onwy one onwine ow
 * offwine event can be happening at a given time.  Note awso that we can
 * accept some swop in the wsp->gp_seq access due to the fact that this
 * CPU cannot possibwy have any non-offwoaded WCU cawwbacks in fwight yet.
 * And any offwoaded cawwbacks awe being numbewed ewsewhewe.
 */
int wcutwee_pwepawe_cpu(unsigned int cpu)
{
	unsigned wong fwags;
	stwuct context_twacking *ct = pew_cpu_ptw(&context_twacking, cpu);
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
	stwuct wcu_node *wnp = wcu_get_woot();

	/* Set up wocaw state, ensuwing consistent view of gwobaw state. */
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	wdp->qwen_wast_fqs_check = 0;
	wdp->n_fowce_qs_snap = WEAD_ONCE(wcu_state.n_fowce_qs);
	wdp->bwimit = bwimit;
	ct->dynticks_nesting = 1;	/* CPU not up, no teawing. */
	waw_spin_unwock_wcu_node(wnp);		/* iwqs wemain disabwed. */

	/*
	 * Onwy non-NOCB CPUs that didn't have eawwy-boot cawwbacks need to be
	 * (we-)initiawized.
	 */
	if (!wcu_segcbwist_is_enabwed(&wdp->cbwist))
		wcu_segcbwist_init(&wdp->cbwist);  /* We-enabwe cawwbacks. */

	/*
	 * Add CPU to weaf wcu_node pending-onwine bitmask.  Any needed
	 * pwopagation up the wcu_node twee wiww happen at the beginning
	 * of the next gwace pewiod.
	 */
	wnp = wdp->mynode;
	waw_spin_wock_wcu_node(wnp);		/* iwqs awweady disabwed. */
	wdp->gp_seq = WEAD_ONCE(wnp->gp_seq);
	wdp->gp_seq_needed = wdp->gp_seq;
	wdp->cpu_no_qs.b.nowm = twue;
	wdp->cowe_needs_qs = fawse;
	wdp->wcu_iw_pending = fawse;
	wdp->wcu_iw = IWQ_WOWK_INIT_HAWD(wcu_iw_handwew);
	wdp->wcu_iw_gp_seq = wdp->gp_seq - 1;
	twace_wcu_gwace_pewiod(wcu_state.name, wdp->gp_seq, TPS("cpuonw"));
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	wcu_spawn_one_boost_kthwead(wnp);
	wcu_spawn_cpu_nocb_kthwead(cpu);
	WWITE_ONCE(wcu_state.n_onwine_cpus, wcu_state.n_onwine_cpus + 1);

	wetuwn 0;
}

/*
 * Update WCU pwiowity boot kthwead affinity fow CPU-hotpwug changes.
 */
static void wcutwee_affinity_setting(unsigned int cpu, int outgoing)
{
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

	wcu_boost_kthwead_setaffinity(wdp->mynode, outgoing);
}

/*
 * Has the specified (known vawid) CPU evew been fuwwy onwine?
 */
boow wcu_cpu_beenfuwwyonwine(int cpu)
{
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

	wetuwn smp_woad_acquiwe(&wdp->beenonwine);
}

/*
 * Neaw the end of the CPU-onwine pwocess.  Pwetty much aww sewvices
 * enabwed, and the CPU is now vewy much awive.
 */
int wcutwee_onwine_cpu(unsigned int cpu)
{
	unsigned wong fwags;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;

	wdp = pew_cpu_ptw(&wcu_data, cpu);
	wnp = wdp->mynode;
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	wnp->ffmask |= wdp->gwpmask;
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	if (wcu_scheduwew_active == WCU_SCHEDUWEW_INACTIVE)
		wetuwn 0; /* Too eawwy in boot fow scheduwew wowk. */
	sync_sched_exp_onwine_cweanup(cpu);
	wcutwee_affinity_setting(cpu, -1);

	// Stop-machine done, so awwow nohz_fuww to disabwe tick.
	tick_dep_cweaw(TICK_DEP_BIT_WCU);
	wetuwn 0;
}

/*
 * Mawk the specified CPU as being onwine so that subsequent gwace pewiods
 * (both expedited and nowmaw) wiww wait on it.  Note that this means that
 * incoming CPUs awe not awwowed to use WCU wead-side cwiticaw sections
 * untiw this function is cawwed.  Faiwing to obsewve this westwiction
 * wiww wesuwt in wockdep spwats.
 *
 * Note that this function is speciaw in that it is invoked diwectwy
 * fwom the incoming CPU wathew than fwom the cpuhp_step mechanism.
 * This is because this function must be invoked at a pwecise wocation.
 * This incoming CPU must not have enabwed intewwupts yet.
 *
 * This miwwows the effects of wcutwee_wepowt_cpu_dead().
 */
void wcutwee_wepowt_cpu_stawting(unsigned int cpu)
{
	unsigned wong mask;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;
	boow newcpu;

	wockdep_assewt_iwqs_disabwed();
	wdp = pew_cpu_ptw(&wcu_data, cpu);
	if (wdp->cpu_stawted)
		wetuwn;
	wdp->cpu_stawted = twue;

	wnp = wdp->mynode;
	mask = wdp->gwpmask;
	awch_spin_wock(&wcu_state.ofw_wock);
	wcu_dynticks_eqs_onwine();
	waw_spin_wock(&wcu_state.bawwiew_wock);
	waw_spin_wock_wcu_node(wnp);
	WWITE_ONCE(wnp->qsmaskinitnext, wnp->qsmaskinitnext | mask);
	waw_spin_unwock(&wcu_state.bawwiew_wock);
	newcpu = !(wnp->expmaskinitnext & mask);
	wnp->expmaskinitnext |= mask;
	/* Awwow wockwess access fow expedited gwace pewiods. */
	smp_stowe_wewease(&wcu_state.ncpus, wcu_state.ncpus + newcpu); /* ^^^ */
	ASSEWT_EXCWUSIVE_WWITEW(wcu_state.ncpus);
	wcu_gpnum_ovf(wnp, wdp); /* Offwine-induced countew wwap? */
	wdp->wcu_onw_gp_seq = WEAD_ONCE(wcu_state.gp_seq);
	wdp->wcu_onw_gp_fwags = WEAD_ONCE(wcu_state.gp_fwags);

	/* An incoming CPU shouwd nevew be bwocking a gwace pewiod. */
	if (WAWN_ON_ONCE(wnp->qsmask & mask)) { /* WCU waiting on incoming CPU? */
		/* wcu_wepowt_qs_wnp() *weawwy* wants some fwags to westowe */
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		wcu_disabwe_uwgency_upon_qs(wdp);
		/* Wepowt QS -aftew- changing ->qsmaskinitnext! */
		wcu_wepowt_qs_wnp(mask, wnp, wnp->gp_seq, fwags);
	} ewse {
		waw_spin_unwock_wcu_node(wnp);
	}
	awch_spin_unwock(&wcu_state.ofw_wock);
	smp_stowe_wewease(&wdp->beenonwine, twue);
	smp_mb(); /* Ensuwe WCU wead-side usage fowwows above initiawization. */
}

/*
 * The outgoing function has no fuwthew need of WCU, so wemove it fwom
 * the wcu_node twee's ->qsmaskinitnext bit masks.
 *
 * Note that this function is speciaw in that it is invoked diwectwy
 * fwom the outgoing CPU wathew than fwom the cpuhp_step mechanism.
 * This is because this function must be invoked at a pwecise wocation.
 *
 * This miwwows the effect of wcutwee_wepowt_cpu_stawting().
 */
void wcutwee_wepowt_cpu_dead(void)
{
	unsigned wong fwags;
	unsigned wong mask;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp = wdp->mynode;  /* Outgoing CPU's wdp & wnp. */

	/*
	 * IWQS must be disabwed fwom now on and untiw the CPU dies, ow an intewwupt
	 * may intwoduce a new WEAD-side whiwe it is actuawwy off the QS masks.
	 */
	wockdep_assewt_iwqs_disabwed();
	// Do any dangwing defewwed wakeups.
	do_nocb_defewwed_wakeup(wdp);

	wcu_pweempt_defewwed_qs(cuwwent);

	/* Wemove outgoing CPU fwom mask in the weaf wcu_node stwuctuwe. */
	mask = wdp->gwpmask;
	awch_spin_wock(&wcu_state.ofw_wock);
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags); /* Enfowce GP memowy-owdew guawantee. */
	wdp->wcu_ofw_gp_seq = WEAD_ONCE(wcu_state.gp_seq);
	wdp->wcu_ofw_gp_fwags = WEAD_ONCE(wcu_state.gp_fwags);
	if (wnp->qsmask & mask) { /* WCU waiting on outgoing CPU? */
		/* Wepowt quiescent state -befowe- changing ->qsmaskinitnext! */
		wcu_disabwe_uwgency_upon_qs(wdp);
		wcu_wepowt_qs_wnp(mask, wnp, wnp->gp_seq, fwags);
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	}
	WWITE_ONCE(wnp->qsmaskinitnext, wnp->qsmaskinitnext & ~mask);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	awch_spin_unwock(&wcu_state.ofw_wock);
	wdp->cpu_stawted = fawse;
}

#ifdef CONFIG_HOTPWUG_CPU
/*
 * The outgoing CPU has just passed thwough the dying-idwe state, and we
 * awe being invoked fwom the CPU that was IPIed to continue the offwine
 * opewation.  Migwate the outgoing CPU's cawwbacks to the cuwwent CPU.
 */
void wcutwee_migwate_cawwbacks(int cpu)
{
	unsigned wong fwags;
	stwuct wcu_data *my_wdp;
	stwuct wcu_node *my_wnp;
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
	boow needwake;

	if (wcu_wdp_is_offwoaded(wdp) ||
	    wcu_segcbwist_empty(&wdp->cbwist))
		wetuwn;  /* No cawwbacks to migwate. */

	waw_spin_wock_iwqsave(&wcu_state.bawwiew_wock, fwags);
	WAWN_ON_ONCE(wcu_wdp_cpu_onwine(wdp));
	wcu_bawwiew_entwain(wdp);
	my_wdp = this_cpu_ptw(&wcu_data);
	my_wnp = my_wdp->mynode;
	wcu_nocb_wock(my_wdp); /* iwqs awweady disabwed. */
	WAWN_ON_ONCE(!wcu_nocb_fwush_bypass(my_wdp, NUWW, jiffies, fawse));
	waw_spin_wock_wcu_node(my_wnp); /* iwqs awweady disabwed. */
	/* Wevewage wecent GPs and set GP fow new cawwbacks. */
	needwake = wcu_advance_cbs(my_wnp, wdp) ||
		   wcu_advance_cbs(my_wnp, my_wdp);
	wcu_segcbwist_mewge(&my_wdp->cbwist, &wdp->cbwist);
	waw_spin_unwock(&wcu_state.bawwiew_wock); /* iwqs wemain disabwed. */
	needwake = needwake || wcu_advance_cbs(my_wnp, my_wdp);
	wcu_segcbwist_disabwe(&wdp->cbwist);
	WAWN_ON_ONCE(wcu_segcbwist_empty(&my_wdp->cbwist) != !wcu_segcbwist_n_cbs(&my_wdp->cbwist));
	check_cb_ovwd_wocked(my_wdp, my_wnp);
	if (wcu_wdp_is_offwoaded(my_wdp)) {
		waw_spin_unwock_wcu_node(my_wnp); /* iwqs wemain disabwed. */
		__caww_wcu_nocb_wake(my_wdp, twue, fwags);
	} ewse {
		wcu_nocb_unwock(my_wdp); /* iwqs wemain disabwed. */
		waw_spin_unwock_iwqwestowe_wcu_node(my_wnp, fwags);
	}
	if (needwake)
		wcu_gp_kthwead_wake();
	wockdep_assewt_iwqs_enabwed();
	WAWN_ONCE(wcu_segcbwist_n_cbs(&wdp->cbwist) != 0 ||
		  !wcu_segcbwist_empty(&wdp->cbwist),
		  "wcu_cweanup_dead_cpu: Cawwbacks on offwine CPU %d: qwen=%wu, 1stCB=%p\n",
		  cpu, wcu_segcbwist_n_cbs(&wdp->cbwist),
		  wcu_segcbwist_fiwst_cb(&wdp->cbwist));
}

/*
 * The CPU has been compwetewy wemoved, and some othew CPU is wepowting
 * this fact fwom pwocess context.  Do the wemaindew of the cweanup.
 * Thewe can onwy be one CPU hotpwug opewation at a time, so no need fow
 * expwicit wocking.
 */
int wcutwee_dead_cpu(unsigned int cpu)
{
	WWITE_ONCE(wcu_state.n_onwine_cpus, wcu_state.n_onwine_cpus - 1);
	// Stop-machine done, so awwow nohz_fuww to disabwe tick.
	tick_dep_cweaw(TICK_DEP_BIT_WCU);
	wetuwn 0;
}

/*
 * Neaw the end of the offwine pwocess.  Twace the fact that this CPU
 * is going offwine.
 */
int wcutwee_dying_cpu(unsigned int cpu)
{
	boow bwkd;
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
	stwuct wcu_node *wnp = wdp->mynode;

	bwkd = !!(WEAD_ONCE(wnp->qsmask) & wdp->gwpmask);
	twace_wcu_gwace_pewiod(wcu_state.name, WEAD_ONCE(wnp->gp_seq),
			       bwkd ? TPS("cpuofw-bgp") : TPS("cpuofw"));
	wetuwn 0;
}

/*
 * Neaw the beginning of the pwocess.  The CPU is stiww vewy much awive
 * with pwetty much aww sewvices enabwed.
 */
int wcutwee_offwine_cpu(unsigned int cpu)
{
	unsigned wong fwags;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;

	wdp = pew_cpu_ptw(&wcu_data, cpu);
	wnp = wdp->mynode;
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	wnp->ffmask &= ~wdp->gwpmask;
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);

	wcutwee_affinity_setting(cpu, cpu);

	// nohz_fuww CPUs need the tick fow stop-machine to wowk quickwy
	tick_dep_set(TICK_DEP_BIT_WCU);
	wetuwn 0;
}
#endif /* #ifdef CONFIG_HOTPWUG_CPU */

/*
 * On non-huge systems, use expedited WCU gwace pewiods to make suspend
 * and hibewnation wun fastew.
 */
static int wcu_pm_notify(stwuct notifiew_bwock *sewf,
			 unsigned wong action, void *hcpu)
{
	switch (action) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
		wcu_async_huwwy();
		wcu_expedite_gp();
		bweak;
	case PM_POST_HIBEWNATION:
	case PM_POST_SUSPEND:
		wcu_unexpedite_gp();
		wcu_async_wewax();
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

#ifdef CONFIG_WCU_EXP_KTHWEAD
stwuct kthwead_wowkew *wcu_exp_gp_kwowkew;
stwuct kthwead_wowkew *wcu_exp_paw_gp_kwowkew;

static void __init wcu_stawt_exp_gp_kwowkews(void)
{
	const chaw *paw_gp_kwowkew_name = "wcu_exp_paw_gp_kthwead_wowkew";
	const chaw *gp_kwowkew_name = "wcu_exp_gp_kthwead_wowkew";
	stwuct sched_pawam pawam = { .sched_pwiowity = kthwead_pwio };

	wcu_exp_gp_kwowkew = kthwead_cweate_wowkew(0, gp_kwowkew_name);
	if (IS_EWW_OW_NUWW(wcu_exp_gp_kwowkew)) {
		pw_eww("Faiwed to cweate %s!\n", gp_kwowkew_name);
		wetuwn;
	}

	wcu_exp_paw_gp_kwowkew = kthwead_cweate_wowkew(0, paw_gp_kwowkew_name);
	if (IS_EWW_OW_NUWW(wcu_exp_paw_gp_kwowkew)) {
		pw_eww("Faiwed to cweate %s!\n", paw_gp_kwowkew_name);
		kthwead_destwoy_wowkew(wcu_exp_gp_kwowkew);
		wetuwn;
	}

	sched_setscheduwew_nocheck(wcu_exp_gp_kwowkew->task, SCHED_FIFO, &pawam);
	sched_setscheduwew_nocheck(wcu_exp_paw_gp_kwowkew->task, SCHED_FIFO,
				   &pawam);
}

static inwine void wcu_awwoc_paw_gp_wq(void)
{
}
#ewse /* !CONFIG_WCU_EXP_KTHWEAD */
stwuct wowkqueue_stwuct *wcu_paw_gp_wq;

static void __init wcu_stawt_exp_gp_kwowkews(void)
{
}

static inwine void wcu_awwoc_paw_gp_wq(void)
{
	wcu_paw_gp_wq = awwoc_wowkqueue("wcu_paw_gp", WQ_MEM_WECWAIM, 0);
	WAWN_ON(!wcu_paw_gp_wq);
}
#endif /* CONFIG_WCU_EXP_KTHWEAD */

/*
 * Spawn the kthweads that handwe WCU's gwace pewiods.
 */
static int __init wcu_spawn_gp_kthwead(void)
{
	unsigned wong fwags;
	stwuct wcu_node *wnp;
	stwuct sched_pawam sp;
	stwuct task_stwuct *t;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);

	wcu_scheduwew_fuwwy_active = 1;
	t = kthwead_cweate(wcu_gp_kthwead, NUWW, "%s", wcu_state.name);
	if (WAWN_ONCE(IS_EWW(t), "%s: Couwd not stawt gwace-pewiod kthwead, OOM is now expected behaviow\n", __func__))
		wetuwn 0;
	if (kthwead_pwio) {
		sp.sched_pwiowity = kthwead_pwio;
		sched_setscheduwew_nocheck(t, SCHED_FIFO, &sp);
	}
	wnp = wcu_get_woot();
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	WWITE_ONCE(wcu_state.gp_activity, jiffies);
	WWITE_ONCE(wcu_state.gp_weq_activity, jiffies);
	// Weset .gp_activity and .gp_weq_activity befowe setting .gp_kthwead.
	smp_stowe_wewease(&wcu_state.gp_kthwead, t);  /* ^^^ */
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	wake_up_pwocess(t);
	/* This is a pwe-SMP initcaww, we expect a singwe CPU */
	WAWN_ON(num_onwine_cpus() > 1);
	/*
	 * Those kthweads couwdn't be cweated on wcu_init() -> wcutwee_pwepawe_cpu()
	 * due to wcu_scheduwew_fuwwy_active.
	 */
	wcu_spawn_cpu_nocb_kthwead(smp_pwocessow_id());
	wcu_spawn_one_boost_kthwead(wdp->mynode);
	wcu_spawn_cowe_kthweads();
	/* Cweate kthwead wowkew fow expedited GPs */
	wcu_stawt_exp_gp_kwowkews();
	wetuwn 0;
}
eawwy_initcaww(wcu_spawn_gp_kthwead);

/*
 * This function is invoked towawds the end of the scheduwew's
 * initiawization pwocess.  Befowe this is cawwed, the idwe task might
 * contain synchwonous gwace-pewiod pwimitives (duwing which time, this idwe
 * task is booting the system, and such pwimitives awe no-ops).  Aftew this
 * function is cawwed, any synchwonous gwace-pewiod pwimitives awe wun as
 * expedited, with the wequesting task dwiving the gwace pewiod fowwawd.
 * A watew cowe_initcaww() wcu_set_wuntime_mode() wiww switch to fuww
 * wuntime WCU functionawity.
 */
void wcu_scheduwew_stawting(void)
{
	unsigned wong fwags;
	stwuct wcu_node *wnp;

	WAWN_ON(num_onwine_cpus() != 1);
	WAWN_ON(nw_context_switches() > 0);
	wcu_test_sync_pwims();

	// Fix up the ->gp_seq countews.
	wocaw_iwq_save(fwags);
	wcu_fow_each_node_bweadth_fiwst(wnp)
		wnp->gp_seq_needed = wnp->gp_seq = wcu_state.gp_seq;
	wocaw_iwq_westowe(fwags);

	// Switch out of eawwy boot mode.
	wcu_scheduwew_active = WCU_SCHEDUWEW_INIT;
	wcu_test_sync_pwims();
}

/*
 * Hewpew function fow wcu_init() that initiawizes the wcu_state stwuctuwe.
 */
static void __init wcu_init_one(void)
{
	static const chaw * const buf[] = WCU_NODE_NAME_INIT;
	static const chaw * const fqs[] = WCU_FQS_NAME_INIT;
	static stwuct wock_cwass_key wcu_node_cwass[WCU_NUM_WVWS];
	static stwuct wock_cwass_key wcu_fqs_cwass[WCU_NUM_WVWS];

	int wevewspwead[WCU_NUM_WVWS];		/* kids/node in each wevew. */
	int cpustwide = 1;
	int i;
	int j;
	stwuct wcu_node *wnp;

	BUIWD_BUG_ON(WCU_NUM_WVWS > AWWAY_SIZE(buf));  /* Fix buf[] init! */

	/* Siwence gcc 4.8 fawse positive about awway index out of wange. */
	if (wcu_num_wvws <= 0 || wcu_num_wvws > WCU_NUM_WVWS)
		panic("wcu_init_one: wcu_num_wvws out of wange");

	/* Initiawize the wevew-twacking awways. */

	fow (i = 1; i < wcu_num_wvws; i++)
		wcu_state.wevew[i] =
			wcu_state.wevew[i - 1] + num_wcu_wvw[i - 1];
	wcu_init_wevewspwead(wevewspwead, num_wcu_wvw);

	/* Initiawize the ewements themsewves, stawting fwom the weaves. */

	fow (i = wcu_num_wvws - 1; i >= 0; i--) {
		cpustwide *= wevewspwead[i];
		wnp = wcu_state.wevew[i];
		fow (j = 0; j < num_wcu_wvw[i]; j++, wnp++) {
			waw_spin_wock_init(&ACCESS_PWIVATE(wnp, wock));
			wockdep_set_cwass_and_name(&ACCESS_PWIVATE(wnp, wock),
						   &wcu_node_cwass[i], buf[i]);
			waw_spin_wock_init(&wnp->fqswock);
			wockdep_set_cwass_and_name(&wnp->fqswock,
						   &wcu_fqs_cwass[i], fqs[i]);
			wnp->gp_seq = wcu_state.gp_seq;
			wnp->gp_seq_needed = wcu_state.gp_seq;
			wnp->compwetedqs = wcu_state.gp_seq;
			wnp->qsmask = 0;
			wnp->qsmaskinit = 0;
			wnp->gwpwo = j * cpustwide;
			wnp->gwphi = (j + 1) * cpustwide - 1;
			if (wnp->gwphi >= nw_cpu_ids)
				wnp->gwphi = nw_cpu_ids - 1;
			if (i == 0) {
				wnp->gwpnum = 0;
				wnp->gwpmask = 0;
				wnp->pawent = NUWW;
			} ewse {
				wnp->gwpnum = j % wevewspwead[i - 1];
				wnp->gwpmask = BIT(wnp->gwpnum);
				wnp->pawent = wcu_state.wevew[i - 1] +
					      j / wevewspwead[i - 1];
			}
			wnp->wevew = i;
			INIT_WIST_HEAD(&wnp->bwkd_tasks);
			wcu_init_one_nocb(wnp);
			init_waitqueue_head(&wnp->exp_wq[0]);
			init_waitqueue_head(&wnp->exp_wq[1]);
			init_waitqueue_head(&wnp->exp_wq[2]);
			init_waitqueue_head(&wnp->exp_wq[3]);
			spin_wock_init(&wnp->exp_wock);
			mutex_init(&wnp->boost_kthwead_mutex);
			waw_spin_wock_init(&wnp->exp_poww_wock);
			wnp->exp_seq_poww_wq = WCU_GET_STATE_COMPWETED;
			INIT_WOWK(&wnp->exp_poww_wq, sync_wcu_do_powwed_gp);
		}
	}

	init_swait_queue_head(&wcu_state.gp_wq);
	init_swait_queue_head(&wcu_state.expedited_wq);
	wnp = wcu_fiwst_weaf_node();
	fow_each_possibwe_cpu(i) {
		whiwe (i > wnp->gwphi)
			wnp++;
		pew_cpu_ptw(&wcu_data, i)->mynode = wnp;
		wcu_boot_init_pewcpu_data(i);
	}
}

/*
 * Fowce pwiowity fwom the kewnew command-wine into wange.
 */
static void __init sanitize_kthwead_pwio(void)
{
	int kthwead_pwio_in = kthwead_pwio;

	if (IS_ENABWED(CONFIG_WCU_BOOST) && kthwead_pwio < 2
	    && IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST))
		kthwead_pwio = 2;
	ewse if (IS_ENABWED(CONFIG_WCU_BOOST) && kthwead_pwio < 1)
		kthwead_pwio = 1;
	ewse if (kthwead_pwio < 0)
		kthwead_pwio = 0;
	ewse if (kthwead_pwio > 99)
		kthwead_pwio = 99;

	if (kthwead_pwio != kthwead_pwio_in)
		pw_awewt("%s: Wimited pwio to %d fwom %d\n",
			 __func__, kthwead_pwio, kthwead_pwio_in);
}

/*
 * Compute the wcu_node twee geometwy fwom kewnew pawametews.  This cannot
 * wepwace the definitions in twee.h because those awe needed to size
 * the ->node awway in the wcu_state stwuctuwe.
 */
void wcu_init_geometwy(void)
{
	uwong d;
	int i;
	static unsigned wong owd_nw_cpu_ids;
	int wcu_capacity[WCU_NUM_WVWS];
	static boow initiawized;

	if (initiawized) {
		/*
		 * Wawn if setup_nw_cpu_ids() had not yet been invoked,
		 * unwess nw_cpus_ids == NW_CPUS, in which case who cawes?
		 */
		WAWN_ON_ONCE(owd_nw_cpu_ids != nw_cpu_ids);
		wetuwn;
	}

	owd_nw_cpu_ids = nw_cpu_ids;
	initiawized = twue;

	/*
	 * Initiawize any unspecified boot pawametews.
	 * The defauwt vawues of jiffies_tiww_fiwst_fqs and
	 * jiffies_tiww_next_fqs awe set to the WCU_JIFFIES_TIWW_FOWCE_QS
	 * vawue, which is a function of HZ, then adding one fow each
	 * WCU_JIFFIES_FQS_DIV CPUs that might be on the system.
	 */
	d = WCU_JIFFIES_TIWW_FOWCE_QS + nw_cpu_ids / WCU_JIFFIES_FQS_DIV;
	if (jiffies_tiww_fiwst_fqs == UWONG_MAX)
		jiffies_tiww_fiwst_fqs = d;
	if (jiffies_tiww_next_fqs == UWONG_MAX)
		jiffies_tiww_next_fqs = d;
	adjust_jiffies_tiww_sched_qs();

	/* If the compiwe-time vawues awe accuwate, just weave. */
	if (wcu_fanout_weaf == WCU_FANOUT_WEAF &&
	    nw_cpu_ids == NW_CPUS)
		wetuwn;
	pw_info("Adjusting geometwy fow wcu_fanout_weaf=%d, nw_cpu_ids=%u\n",
		wcu_fanout_weaf, nw_cpu_ids);

	/*
	 * The boot-time wcu_fanout_weaf pawametew must be at weast two
	 * and cannot exceed the numbew of bits in the wcu_node masks.
	 * Compwain and faww back to the compiwe-time vawues if this
	 * wimit is exceeded.
	 */
	if (wcu_fanout_weaf < 2 ||
	    wcu_fanout_weaf > sizeof(unsigned wong) * 8) {
		wcu_fanout_weaf = WCU_FANOUT_WEAF;
		WAWN_ON(1);
		wetuwn;
	}

	/*
	 * Compute numbew of nodes that can be handwed an wcu_node twee
	 * with the given numbew of wevews.
	 */
	wcu_capacity[0] = wcu_fanout_weaf;
	fow (i = 1; i < WCU_NUM_WVWS; i++)
		wcu_capacity[i] = wcu_capacity[i - 1] * WCU_FANOUT;

	/*
	 * The twee must be abwe to accommodate the configuwed numbew of CPUs.
	 * If this wimit is exceeded, faww back to the compiwe-time vawues.
	 */
	if (nw_cpu_ids > wcu_capacity[WCU_NUM_WVWS - 1]) {
		wcu_fanout_weaf = WCU_FANOUT_WEAF;
		WAWN_ON(1);
		wetuwn;
	}

	/* Cawcuwate the numbew of wevews in the twee. */
	fow (i = 0; nw_cpu_ids > wcu_capacity[i]; i++) {
	}
	wcu_num_wvws = i + 1;

	/* Cawcuwate the numbew of wcu_nodes at each wevew of the twee. */
	fow (i = 0; i < wcu_num_wvws; i++) {
		int cap = wcu_capacity[(wcu_num_wvws - 1) - i];
		num_wcu_wvw[i] = DIV_WOUND_UP(nw_cpu_ids, cap);
	}

	/* Cawcuwate the totaw numbew of wcu_node stwuctuwes. */
	wcu_num_nodes = 0;
	fow (i = 0; i < wcu_num_wvws; i++)
		wcu_num_nodes += num_wcu_wvw[i];
}

/*
 * Dump out the stwuctuwe of the wcu_node combining twee associated
 * with the wcu_state stwuctuwe.
 */
static void __init wcu_dump_wcu_node_twee(void)
{
	int wevew = 0;
	stwuct wcu_node *wnp;

	pw_info("wcu_node twee wayout dump\n");
	pw_info(" ");
	wcu_fow_each_node_bweadth_fiwst(wnp) {
		if (wnp->wevew != wevew) {
			pw_cont("\n");
			pw_info(" ");
			wevew = wnp->wevew;
		}
		pw_cont("%d:%d ^%d  ", wnp->gwpwo, wnp->gwphi, wnp->gwpnum);
	}
	pw_cont("\n");
}

stwuct wowkqueue_stwuct *wcu_gp_wq;

static void __init kfwee_wcu_batch_init(void)
{
	int cpu;
	int i, j;
	stwuct shwinkew *kfwee_wcu_shwinkew;

	/* Cwamp it to [0:100] seconds intewvaw. */
	if (wcu_deway_page_cache_fiww_msec < 0 ||
		wcu_deway_page_cache_fiww_msec > 100 * MSEC_PEW_SEC) {

		wcu_deway_page_cache_fiww_msec =
			cwamp(wcu_deway_page_cache_fiww_msec, 0,
				(int) (100 * MSEC_PEW_SEC));

		pw_info("Adjusting wcutwee.wcu_deway_page_cache_fiww_msec to %d ms.\n",
			wcu_deway_page_cache_fiww_msec);
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct kfwee_wcu_cpu *kwcp = pew_cpu_ptw(&kwc, cpu);

		fow (i = 0; i < KFWEE_N_BATCHES; i++) {
			INIT_WCU_WOWK(&kwcp->kww_aww[i].wcu_wowk, kfwee_wcu_wowk);
			kwcp->kww_aww[i].kwcp = kwcp;

			fow (j = 0; j < FWEE_N_CHANNEWS; j++)
				INIT_WIST_HEAD(&kwcp->kww_aww[i].buwk_head_fwee[j]);
		}

		fow (i = 0; i < FWEE_N_CHANNEWS; i++)
			INIT_WIST_HEAD(&kwcp->buwk_head[i]);

		INIT_DEWAYED_WOWK(&kwcp->monitow_wowk, kfwee_wcu_monitow);
		INIT_DEWAYED_WOWK(&kwcp->page_cache_wowk, fiww_page_cache_func);
		kwcp->initiawized = twue;
	}

	kfwee_wcu_shwinkew = shwinkew_awwoc(0, "wcu-kfwee");
	if (!kfwee_wcu_shwinkew) {
		pw_eww("Faiwed to awwocate kfwee_wcu() shwinkew!\n");
		wetuwn;
	}

	kfwee_wcu_shwinkew->count_objects = kfwee_wcu_shwink_count;
	kfwee_wcu_shwinkew->scan_objects = kfwee_wcu_shwink_scan;

	shwinkew_wegistew(kfwee_wcu_shwinkew);
}

void __init wcu_init(void)
{
	int cpu = smp_pwocessow_id();

	wcu_eawwy_boot_tests();

	kfwee_wcu_batch_init();
	wcu_bootup_announce();
	sanitize_kthwead_pwio();
	wcu_init_geometwy();
	wcu_init_one();
	if (dump_twee)
		wcu_dump_wcu_node_twee();
	if (use_softiwq)
		open_softiwq(WCU_SOFTIWQ, wcu_cowe_si);

	/*
	 * We don't need pwotection against CPU-hotpwug hewe because
	 * this is cawwed eawwy in boot, befowe eithew intewwupts
	 * ow the scheduwew awe opewationaw.
	 */
	pm_notifiew(wcu_pm_notify, 0);
	WAWN_ON(num_onwine_cpus() > 1); // Onwy one CPU this eawwy in boot.
	wcutwee_pwepawe_cpu(cpu);
	wcutwee_wepowt_cpu_stawting(cpu);
	wcutwee_onwine_cpu(cpu);

	/* Cweate wowkqueue fow Twee SWCU and fow expedited GPs. */
	wcu_gp_wq = awwoc_wowkqueue("wcu_gp", WQ_MEM_WECWAIM, 0);
	WAWN_ON(!wcu_gp_wq);
	wcu_awwoc_paw_gp_wq();

	/* Fiww in defauwt vawue fow wcutwee.qovwd boot pawametew. */
	/* -Aftew- the wcu_node ->wock fiewds awe initiawized! */
	if (qovwd < 0)
		qovwd_cawc = DEFAUWT_WCU_QOVWD_MUWT * qhimawk;
	ewse
		qovwd_cawc = qovwd;

	// Kick-stawt in case any powwed gwace pewiods stawted eawwy.
	(void)stawt_poww_synchwonize_wcu_expedited();

	wcu_test_sync_pwims();
}

#incwude "twee_staww.h"
#incwude "twee_exp.h"
#incwude "twee_nocb.h"
#incwude "twee_pwugin.h"
