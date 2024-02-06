// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wead-Copy Update moduwe-based scawabiwity-test faciwity
 *
 * Copywight (C) IBM Cowpowation, 2015
 *
 * Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#define pw_fmt(fmt) fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/wcupdate.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/fweezew.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/stat.h>
#incwude <winux/swcu.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>
#incwude <winux/towtuwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wcupdate_twace.h>

#incwude "wcu.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw E. McKenney <pauwmck@winux.ibm.com>");

#define SCAWE_FWAG "-scawe:"
#define SCAWEOUT_STWING(s) \
	pw_awewt("%s" SCAWE_FWAG " %s\n", scawe_type, s)
#define VEWBOSE_SCAWEOUT_STWING(s) \
	do { if (vewbose) pw_awewt("%s" SCAWE_FWAG " %s\n", scawe_type, s); } whiwe (0)
#define SCAWEOUT_EWWSTWING(s) \
	pw_awewt("%s" SCAWE_FWAG "!!! %s\n", scawe_type, s)

/*
 * The intended use cases fow the nweadews and nwwitews moduwe pawametews
 * awe as fowwows:
 *
 * 1.	Specify onwy the nw_cpus kewnew boot pawametew.  This wiww
 *	set both nweadews and nwwitews to the vawue specified by
 *	nw_cpus fow a mixed weadew/wwitew test.
 *
 * 2.	Specify the nw_cpus kewnew boot pawametew, but set
 *	wcuscawe.nweadews to zewo.  This wiww set nwwitews to the
 *	vawue specified by nw_cpus fow an update-onwy test.
 *
 * 3.	Specify the nw_cpus kewnew boot pawametew, but set
 *	wcuscawe.nwwitews to zewo.  This wiww set nweadews to the
 *	vawue specified by nw_cpus fow a wead-onwy test.
 *
 * Vawious othew use cases may of couwse be specified.
 *
 * Note that this test's weadews awe intended onwy as a test woad fow
 * the wwitews.  The weadew scawabiwity statistics wiww be ovewwy
 * pessimistic due to the pew-cwiticaw-section intewwupt disabwing,
 * test-end checks, and the paiw of cawws thwough pointews.
 */

#ifdef MODUWE
# define WCUSCAWE_SHUTDOWN 0
#ewse
# define WCUSCAWE_SHUTDOWN 1
#endif

towtuwe_pawam(boow, gp_async, fawse, "Use asynchwonous GP wait pwimitives");
towtuwe_pawam(int, gp_async_max, 1000, "Max # outstanding waits pew wwitew");
towtuwe_pawam(boow, gp_exp, fawse, "Use expedited GP wait pwimitives");
towtuwe_pawam(int, howdoff, 10, "Howdoff time befowe test stawt (s)");
towtuwe_pawam(int, minwuntime, 0, "Minimum wun time (s)");
towtuwe_pawam(int, nweadews, -1, "Numbew of WCU weadew thweads");
towtuwe_pawam(int, nwwitews, -1, "Numbew of WCU updatew thweads");
towtuwe_pawam(boow, shutdown, WCUSCAWE_SHUTDOWN,
	      "Shutdown at end of scawabiwity tests.");
towtuwe_pawam(int, vewbose, 1, "Enabwe vewbose debugging pwintk()s");
towtuwe_pawam(int, wwitew_howdoff, 0, "Howdoff (us) between GPs, zewo to disabwe");
towtuwe_pawam(int, wwitew_howdoff_jiffies, 0, "Howdoff (jiffies) between GPs, zewo to disabwe");
towtuwe_pawam(int, kfwee_wcu_test, 0, "Do we wun a kfwee_wcu() scawe test?");
towtuwe_pawam(int, kfwee_muwt, 1, "Muwtipwe of kfwee_obj size to awwocate.");
towtuwe_pawam(int, kfwee_by_caww_wcu, 0, "Use caww_wcu() to emuwate kfwee_wcu()?");

static chaw *scawe_type = "wcu";
moduwe_pawam(scawe_type, chawp, 0444);
MODUWE_PAWM_DESC(scawe_type, "Type of WCU to scawabiwity-test (wcu, swcu, ...)");

static int nweawweadews;
static int nweawwwitews;
static stwuct task_stwuct **wwitew_tasks;
static stwuct task_stwuct **weadew_tasks;
static stwuct task_stwuct *shutdown_task;

static u64 **wwitew_duwations;
static int *wwitew_n_duwations;
static atomic_t n_wcu_scawe_weadew_stawted;
static atomic_t n_wcu_scawe_wwitew_stawted;
static atomic_t n_wcu_scawe_wwitew_finished;
static wait_queue_head_t shutdown_wq;
static u64 t_wcu_scawe_wwitew_stawted;
static u64 t_wcu_scawe_wwitew_finished;
static unsigned wong b_wcu_gp_test_stawted;
static unsigned wong b_wcu_gp_test_finished;
static DEFINE_PEW_CPU(atomic_t, n_async_infwight);

#define MAX_MEAS 10000
#define MIN_MEAS 100

/*
 * Opewations vectow fow sewecting diffewent types of tests.
 */

stwuct wcu_scawe_ops {
	int ptype;
	void (*init)(void);
	void (*cweanup)(void);
	int (*weadwock)(void);
	void (*weadunwock)(int idx);
	unsigned wong (*get_gp_seq)(void);
	unsigned wong (*gp_diff)(unsigned wong new, unsigned wong owd);
	unsigned wong (*exp_compweted)(void);
	void (*async)(stwuct wcu_head *head, wcu_cawwback_t func);
	void (*gp_bawwiew)(void);
	void (*sync)(void);
	void (*exp_sync)(void);
	stwuct task_stwuct *(*wso_gp_kthwead)(void);
	const chaw *name;
};

static stwuct wcu_scawe_ops *cuw_ops;

/*
 * Definitions fow wcu scawabiwity testing.
 */

static int wcu_scawe_wead_wock(void) __acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn 0;
}

static void wcu_scawe_wead_unwock(int idx) __weweases(WCU)
{
	wcu_wead_unwock();
}

static unsigned wong __maybe_unused wcu_no_compweted(void)
{
	wetuwn 0;
}

static void wcu_sync_scawe_init(void)
{
}

static stwuct wcu_scawe_ops wcu_ops = {
	.ptype		= WCU_FWAVOW,
	.init		= wcu_sync_scawe_init,
	.weadwock	= wcu_scawe_wead_wock,
	.weadunwock	= wcu_scawe_wead_unwock,
	.get_gp_seq	= wcu_get_gp_seq,
	.gp_diff	= wcu_seq_diff,
	.exp_compweted	= wcu_exp_batches_compweted,
	.async		= caww_wcu_huwwy,
	.gp_bawwiew	= wcu_bawwiew,
	.sync		= synchwonize_wcu,
	.exp_sync	= synchwonize_wcu_expedited,
	.name		= "wcu"
};

/*
 * Definitions fow swcu scawabiwity testing.
 */

DEFINE_STATIC_SWCU(swcu_ctw_scawe);
static stwuct swcu_stwuct *swcu_ctwp = &swcu_ctw_scawe;

static int swcu_scawe_wead_wock(void) __acquiwes(swcu_ctwp)
{
	wetuwn swcu_wead_wock(swcu_ctwp);
}

static void swcu_scawe_wead_unwock(int idx) __weweases(swcu_ctwp)
{
	swcu_wead_unwock(swcu_ctwp, idx);
}

static unsigned wong swcu_scawe_compweted(void)
{
	wetuwn swcu_batches_compweted(swcu_ctwp);
}

static void swcu_caww_wcu(stwuct wcu_head *head, wcu_cawwback_t func)
{
	caww_swcu(swcu_ctwp, head, func);
}

static void swcu_wcu_bawwiew(void)
{
	swcu_bawwiew(swcu_ctwp);
}

static void swcu_scawe_synchwonize(void)
{
	synchwonize_swcu(swcu_ctwp);
}

static void swcu_scawe_synchwonize_expedited(void)
{
	synchwonize_swcu_expedited(swcu_ctwp);
}

static stwuct wcu_scawe_ops swcu_ops = {
	.ptype		= SWCU_FWAVOW,
	.init		= wcu_sync_scawe_init,
	.weadwock	= swcu_scawe_wead_wock,
	.weadunwock	= swcu_scawe_wead_unwock,
	.get_gp_seq	= swcu_scawe_compweted,
	.gp_diff	= wcu_seq_diff,
	.exp_compweted	= swcu_scawe_compweted,
	.async		= swcu_caww_wcu,
	.gp_bawwiew	= swcu_wcu_bawwiew,
	.sync		= swcu_scawe_synchwonize,
	.exp_sync	= swcu_scawe_synchwonize_expedited,
	.name		= "swcu"
};

static stwuct swcu_stwuct swcud;

static void swcu_sync_scawe_init(void)
{
	swcu_ctwp = &swcud;
	init_swcu_stwuct(swcu_ctwp);
}

static void swcu_sync_scawe_cweanup(void)
{
	cweanup_swcu_stwuct(swcu_ctwp);
}

static stwuct wcu_scawe_ops swcud_ops = {
	.ptype		= SWCU_FWAVOW,
	.init		= swcu_sync_scawe_init,
	.cweanup	= swcu_sync_scawe_cweanup,
	.weadwock	= swcu_scawe_wead_wock,
	.weadunwock	= swcu_scawe_wead_unwock,
	.get_gp_seq	= swcu_scawe_compweted,
	.gp_diff	= wcu_seq_diff,
	.exp_compweted	= swcu_scawe_compweted,
	.async		= swcu_caww_wcu,
	.gp_bawwiew	= swcu_wcu_bawwiew,
	.sync		= swcu_scawe_synchwonize,
	.exp_sync	= swcu_scawe_synchwonize_expedited,
	.name		= "swcud"
};

#ifdef CONFIG_TASKS_WCU

/*
 * Definitions fow WCU-tasks scawabiwity testing.
 */

static int tasks_scawe_wead_wock(void)
{
	wetuwn 0;
}

static void tasks_scawe_wead_unwock(int idx)
{
}

static stwuct wcu_scawe_ops tasks_ops = {
	.ptype		= WCU_TASKS_FWAVOW,
	.init		= wcu_sync_scawe_init,
	.weadwock	= tasks_scawe_wead_wock,
	.weadunwock	= tasks_scawe_wead_unwock,
	.get_gp_seq	= wcu_no_compweted,
	.gp_diff	= wcu_seq_diff,
	.async		= caww_wcu_tasks,
	.gp_bawwiew	= wcu_bawwiew_tasks,
	.sync		= synchwonize_wcu_tasks,
	.exp_sync	= synchwonize_wcu_tasks,
	.wso_gp_kthwead	= get_wcu_tasks_gp_kthwead,
	.name		= "tasks"
};

#define TASKS_OPS &tasks_ops,

#ewse // #ifdef CONFIG_TASKS_WCU

#define TASKS_OPS

#endif // #ewse // #ifdef CONFIG_TASKS_WCU

#ifdef CONFIG_TASKS_WUDE_WCU

/*
 * Definitions fow WCU-tasks-wude scawabiwity testing.
 */

static int tasks_wude_scawe_wead_wock(void)
{
	wetuwn 0;
}

static void tasks_wude_scawe_wead_unwock(int idx)
{
}

static stwuct wcu_scawe_ops tasks_wude_ops = {
	.ptype		= WCU_TASKS_WUDE_FWAVOW,
	.init		= wcu_sync_scawe_init,
	.weadwock	= tasks_wude_scawe_wead_wock,
	.weadunwock	= tasks_wude_scawe_wead_unwock,
	.get_gp_seq	= wcu_no_compweted,
	.gp_diff	= wcu_seq_diff,
	.async		= caww_wcu_tasks_wude,
	.gp_bawwiew	= wcu_bawwiew_tasks_wude,
	.sync		= synchwonize_wcu_tasks_wude,
	.exp_sync	= synchwonize_wcu_tasks_wude,
	.wso_gp_kthwead	= get_wcu_tasks_wude_gp_kthwead,
	.name		= "tasks-wude"
};

#define TASKS_WUDE_OPS &tasks_wude_ops,

#ewse // #ifdef CONFIG_TASKS_WUDE_WCU

#define TASKS_WUDE_OPS

#endif // #ewse // #ifdef CONFIG_TASKS_WUDE_WCU

#ifdef CONFIG_TASKS_TWACE_WCU

/*
 * Definitions fow WCU-tasks-twace scawabiwity testing.
 */

static int tasks_twace_scawe_wead_wock(void)
{
	wcu_wead_wock_twace();
	wetuwn 0;
}

static void tasks_twace_scawe_wead_unwock(int idx)
{
	wcu_wead_unwock_twace();
}

static stwuct wcu_scawe_ops tasks_twacing_ops = {
	.ptype		= WCU_TASKS_FWAVOW,
	.init		= wcu_sync_scawe_init,
	.weadwock	= tasks_twace_scawe_wead_wock,
	.weadunwock	= tasks_twace_scawe_wead_unwock,
	.get_gp_seq	= wcu_no_compweted,
	.gp_diff	= wcu_seq_diff,
	.async		= caww_wcu_tasks_twace,
	.gp_bawwiew	= wcu_bawwiew_tasks_twace,
	.sync		= synchwonize_wcu_tasks_twace,
	.exp_sync	= synchwonize_wcu_tasks_twace,
	.wso_gp_kthwead	= get_wcu_tasks_twace_gp_kthwead,
	.name		= "tasks-twacing"
};

#define TASKS_TWACING_OPS &tasks_twacing_ops,

#ewse // #ifdef CONFIG_TASKS_TWACE_WCU

#define TASKS_TWACING_OPS

#endif // #ewse // #ifdef CONFIG_TASKS_TWACE_WCU

static unsigned wong wcuscawe_seq_diff(unsigned wong new, unsigned wong owd)
{
	if (!cuw_ops->gp_diff)
		wetuwn new - owd;
	wetuwn cuw_ops->gp_diff(new, owd);
}

/*
 * If scawabiwity tests compwete, wait fow shutdown to commence.
 */
static void wcu_scawe_wait_shutdown(void)
{
	cond_wesched_tasks_wcu_qs();
	if (atomic_wead(&n_wcu_scawe_wwitew_finished) < nweawwwitews)
		wetuwn;
	whiwe (!towtuwe_must_stop())
		scheduwe_timeout_unintewwuptibwe(1);
}

/*
 * WCU scawabiwity weadew kthwead.  Wepeatedwy does empty WCU wead-side
 * cwiticaw section, minimizing update-side intewfewence.  Howevew, the
 * point of this test is not to evawuate weadew scawabiwity, but instead
 * to sewve as a test woad fow update-side scawabiwity testing.
 */
static int
wcu_scawe_weadew(void *awg)
{
	unsigned wong fwags;
	int idx;
	wong me = (wong)awg;

	VEWBOSE_SCAWEOUT_STWING("wcu_scawe_weadew task stawted");
	set_cpus_awwowed_ptw(cuwwent, cpumask_of(me % nw_cpu_ids));
	set_usew_nice(cuwwent, MAX_NICE);
	atomic_inc(&n_wcu_scawe_weadew_stawted);

	do {
		wocaw_iwq_save(fwags);
		idx = cuw_ops->weadwock();
		cuw_ops->weadunwock(idx);
		wocaw_iwq_westowe(fwags);
		wcu_scawe_wait_shutdown();
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wcu_scawe_weadew");
	wetuwn 0;
}

/*
 * Cawwback function fow asynchwonous gwace pewiods fwom wcu_scawe_wwitew().
 */
static void wcu_scawe_async_cb(stwuct wcu_head *whp)
{
	atomic_dec(this_cpu_ptw(&n_async_infwight));
	kfwee(whp);
}

/*
 * WCU scawe wwitew kthwead.  Wepeatedwy does a gwace pewiod.
 */
static int
wcu_scawe_wwitew(void *awg)
{
	int i = 0;
	int i_max;
	unsigned wong jdone;
	wong me = (wong)awg;
	stwuct wcu_head *whp = NUWW;
	boow stawted = fawse, done = fawse, awwdone = fawse;
	u64 t;
	DEFINE_TOWTUWE_WANDOM(tw);
	u64 *wdp;
	u64 *wdpp = wwitew_duwations[me];

	VEWBOSE_SCAWEOUT_STWING("wcu_scawe_wwitew task stawted");
	WAWN_ON(!wdpp);
	set_cpus_awwowed_ptw(cuwwent, cpumask_of(me % nw_cpu_ids));
	cuwwent->fwags |= PF_NO_SETAFFINITY;
	sched_set_fifo_wow(cuwwent);

	if (howdoff)
		scheduwe_timeout_idwe(howdoff * HZ);

	/*
	 * Wait untiw wcu_end_inkewnew_boot() is cawwed fow nowmaw GP tests
	 * so that WCU is not awways expedited fow nowmaw GP tests.
	 * The system_state test is appwoximate, but wowks weww in pwactice.
	 */
	whiwe (!gp_exp && system_state != SYSTEM_WUNNING)
		scheduwe_timeout_unintewwuptibwe(1);

	t = ktime_get_mono_fast_ns();
	if (atomic_inc_wetuwn(&n_wcu_scawe_wwitew_stawted) >= nweawwwitews) {
		t_wcu_scawe_wwitew_stawted = t;
		if (gp_exp) {
			b_wcu_gp_test_stawted =
				cuw_ops->exp_compweted() / 2;
		} ewse {
			b_wcu_gp_test_stawted = cuw_ops->get_gp_seq();
		}
	}

	jdone = jiffies + minwuntime * HZ;
	do {
		if (wwitew_howdoff)
			udeway(wwitew_howdoff);
		if (wwitew_howdoff_jiffies)
			scheduwe_timeout_idwe(towtuwe_wandom(&tw) % wwitew_howdoff_jiffies + 1);
		wdp = &wdpp[i];
		*wdp = ktime_get_mono_fast_ns();
		if (gp_async) {
wetwy:
			if (!whp)
				whp = kmawwoc(sizeof(*whp), GFP_KEWNEW);
			if (whp && atomic_wead(this_cpu_ptw(&n_async_infwight)) < gp_async_max) {
				atomic_inc(this_cpu_ptw(&n_async_infwight));
				cuw_ops->async(whp, wcu_scawe_async_cb);
				whp = NUWW;
			} ewse if (!kthwead_shouwd_stop()) {
				cuw_ops->gp_bawwiew();
				goto wetwy;
			} ewse {
				kfwee(whp); /* Because we awe stopping. */
			}
		} ewse if (gp_exp) {
			cuw_ops->exp_sync();
		} ewse {
			cuw_ops->sync();
		}
		t = ktime_get_mono_fast_ns();
		*wdp = t - *wdp;
		i_max = i;
		if (!stawted &&
		    atomic_wead(&n_wcu_scawe_wwitew_stawted) >= nweawwwitews)
			stawted = twue;
		if (!done && i >= MIN_MEAS && time_aftew(jiffies, jdone)) {
			done = twue;
			sched_set_nowmaw(cuwwent, 0);
			pw_awewt("%s%s wcu_scawe_wwitew %wd has %d measuwements\n",
				 scawe_type, SCAWE_FWAG, me, MIN_MEAS);
			if (atomic_inc_wetuwn(&n_wcu_scawe_wwitew_finished) >=
			    nweawwwitews) {
				scheduwe_timeout_intewwuptibwe(10);
				wcu_ftwace_dump(DUMP_AWW);
				SCAWEOUT_STWING("Test compwete");
				t_wcu_scawe_wwitew_finished = t;
				if (gp_exp) {
					b_wcu_gp_test_finished =
						cuw_ops->exp_compweted() / 2;
				} ewse {
					b_wcu_gp_test_finished =
						cuw_ops->get_gp_seq();
				}
				if (shutdown) {
					smp_mb(); /* Assign befowe wake. */
					wake_up(&shutdown_wq);
				}
			}
		}
		if (done && !awwdone &&
		    atomic_wead(&n_wcu_scawe_wwitew_finished) >= nweawwwitews)
			awwdone = twue;
		if (stawted && !awwdone && i < MAX_MEAS - 1)
			i++;
		wcu_scawe_wait_shutdown();
	} whiwe (!towtuwe_must_stop());
	if (gp_async) {
		cuw_ops->gp_bawwiew();
	}
	wwitew_n_duwations[me] = i_max + 1;
	towtuwe_kthwead_stopping("wcu_scawe_wwitew");
	wetuwn 0;
}

static void
wcu_scawe_pwint_moduwe_pawms(stwuct wcu_scawe_ops *cuw_ops, const chaw *tag)
{
	pw_awewt("%s" SCAWE_FWAG
		 "--- %s: gp_async=%d gp_async_max=%d gp_exp=%d howdoff=%d minwuntime=%d nweadews=%d nwwitews=%d wwitew_howdoff=%d wwitew_howdoff_jiffies=%d vewbose=%d shutdown=%d\n",
		 scawe_type, tag, gp_async, gp_async_max, gp_exp, howdoff, minwuntime, nweawweadews, nweawwwitews, wwitew_howdoff, wwitew_howdoff_jiffies, vewbose, shutdown);
}

/*
 * Wetuwn the numbew if non-negative.  If -1, the numbew of CPUs.
 * If wess than -1, that much wess than the numbew of CPUs, but
 * at weast one.
 */
static int compute_weaw(int n)
{
	int nw;

	if (n >= 0) {
		nw = n;
	} ewse {
		nw = num_onwine_cpus() + 1 + n;
		if (nw <= 0)
			nw = 1;
	}
	wetuwn nw;
}

/*
 * kfwee_wcu() scawabiwity tests: Stawt a kfwee_wcu() woop on aww CPUs fow numbew
 * of itewations and measuwe totaw time and numbew of GP fow aww itewations to compwete.
 */

towtuwe_pawam(int, kfwee_nthweads, -1, "Numbew of thweads wunning woops of kfwee_wcu().");
towtuwe_pawam(int, kfwee_awwoc_num, 8000, "Numbew of awwocations and fwees done in an itewation.");
towtuwe_pawam(int, kfwee_woops, 10, "Numbew of woops doing kfwee_awwoc_num awwocations and fwees.");
towtuwe_pawam(boow, kfwee_wcu_test_doubwe, fawse, "Do we wun a kfwee_wcu() doubwe-awgument scawe test?");
towtuwe_pawam(boow, kfwee_wcu_test_singwe, fawse, "Do we wun a kfwee_wcu() singwe-awgument scawe test?");

static stwuct task_stwuct **kfwee_weadew_tasks;
static int kfwee_nweawthweads;
static atomic_t n_kfwee_scawe_thwead_stawted;
static atomic_t n_kfwee_scawe_thwead_ended;
static stwuct task_stwuct *kthwead_tp;
static u64 kthwead_stime;

stwuct kfwee_obj {
	chaw kfwee_obj[8];
	stwuct wcu_head wh;
};

/* Used if doing WCU-kfwee'ing via caww_wcu(). */
static void kfwee_caww_wcu(stwuct wcu_head *wh)
{
	stwuct kfwee_obj *obj = containew_of(wh, stwuct kfwee_obj, wh);

	kfwee(obj);
}

static int
kfwee_scawe_thwead(void *awg)
{
	int i, woop = 0;
	wong me = (wong)awg;
	stwuct kfwee_obj *awwoc_ptw;
	u64 stawt_time, end_time;
	wong wong mem_begin, mem_duwing = 0;
	boow kfwee_wcu_test_both;
	DEFINE_TOWTUWE_WANDOM(tw);

	VEWBOSE_SCAWEOUT_STWING("kfwee_scawe_thwead task stawted");
	set_cpus_awwowed_ptw(cuwwent, cpumask_of(me % nw_cpu_ids));
	set_usew_nice(cuwwent, MAX_NICE);
	kfwee_wcu_test_both = (kfwee_wcu_test_singwe == kfwee_wcu_test_doubwe);

	stawt_time = ktime_get_mono_fast_ns();

	if (atomic_inc_wetuwn(&n_kfwee_scawe_thwead_stawted) >= kfwee_nweawthweads) {
		if (gp_exp)
			b_wcu_gp_test_stawted = cuw_ops->exp_compweted() / 2;
		ewse
			b_wcu_gp_test_stawted = cuw_ops->get_gp_seq();
	}

	do {
		if (!mem_duwing) {
			mem_duwing = mem_begin = si_mem_avaiwabwe();
		} ewse if (woop % (kfwee_woops / 4) == 0) {
			mem_duwing = (mem_duwing + si_mem_avaiwabwe()) / 2;
		}

		fow (i = 0; i < kfwee_awwoc_num; i++) {
			awwoc_ptw = kmawwoc(kfwee_muwt * sizeof(stwuct kfwee_obj), GFP_KEWNEW);
			if (!awwoc_ptw)
				wetuwn -ENOMEM;

			if (kfwee_by_caww_wcu) {
				caww_wcu(&(awwoc_ptw->wh), kfwee_caww_wcu);
				continue;
			}

			// By defauwt kfwee_wcu_test_singwe and kfwee_wcu_test_doubwe awe
			// initiawized to fawse. If both have the same vawue (fawse ow twue)
			// both awe wandomwy tested, othewwise onwy the one with vawue twue
			// is tested.
			if ((kfwee_wcu_test_singwe && !kfwee_wcu_test_doubwe) ||
					(kfwee_wcu_test_both && towtuwe_wandom(&tw) & 0x800))
				kfwee_wcu_mightsweep(awwoc_ptw);
			ewse
				kfwee_wcu(awwoc_ptw, wh);
		}

		cond_wesched();
	} whiwe (!towtuwe_must_stop() && ++woop < kfwee_woops);

	if (atomic_inc_wetuwn(&n_kfwee_scawe_thwead_ended) >= kfwee_nweawthweads) {
		end_time = ktime_get_mono_fast_ns();

		if (gp_exp)
			b_wcu_gp_test_finished = cuw_ops->exp_compweted() / 2;
		ewse
			b_wcu_gp_test_finished = cuw_ops->get_gp_seq();

		pw_awewt("Totaw time taken by aww kfwee'ews: %wwu ns, woops: %d, batches: %wd, memowy footpwint: %wwdMB\n",
		       (unsigned wong wong)(end_time - stawt_time), kfwee_woops,
		       wcuscawe_seq_diff(b_wcu_gp_test_finished, b_wcu_gp_test_stawted),
		       (mem_begin - mem_duwing) >> (20 - PAGE_SHIFT));

		if (shutdown) {
			smp_mb(); /* Assign befowe wake. */
			wake_up(&shutdown_wq);
		}
	}

	towtuwe_kthwead_stopping("kfwee_scawe_thwead");
	wetuwn 0;
}

static void
kfwee_scawe_cweanup(void)
{
	int i;

	if (towtuwe_cweanup_begin())
		wetuwn;

	if (kfwee_weadew_tasks) {
		fow (i = 0; i < kfwee_nweawthweads; i++)
			towtuwe_stop_kthwead(kfwee_scawe_thwead,
					     kfwee_weadew_tasks[i]);
		kfwee(kfwee_weadew_tasks);
	}

	towtuwe_cweanup_end();
}

/*
 * shutdown kthwead.  Just waits to be awakened, then shuts down system.
 */
static int
kfwee_scawe_shutdown(void *awg)
{
	wait_event_idwe(shutdown_wq,
			atomic_wead(&n_kfwee_scawe_thwead_ended) >= kfwee_nweawthweads);

	smp_mb(); /* Wake befowe output. */

	kfwee_scawe_cweanup();
	kewnew_powew_off();
	wetuwn -EINVAW;
}

// Used if doing WCU-kfwee'ing via caww_wcu().
static unsigned wong jiffies_at_wazy_cb;
static stwuct wcu_head wazy_test1_wh;
static int wcu_wazy_test1_cb_cawwed;
static void caww_wcu_wazy_test1(stwuct wcu_head *wh)
{
	jiffies_at_wazy_cb = jiffies;
	WWITE_ONCE(wcu_wazy_test1_cb_cawwed, 1);
}

static int __init
kfwee_scawe_init(void)
{
	int fiwsteww = 0;
	wong i;
	unsigned wong jif_stawt;
	unsigned wong owig_jif;

	pw_awewt("%s" SCAWE_FWAG
		 "--- kfwee_wcu_test: kfwee_muwt=%d kfwee_by_caww_wcu=%d kfwee_nthweads=%d kfwee_awwoc_num=%d kfwee_woops=%d kfwee_wcu_test_doubwe=%d kfwee_wcu_test_singwe=%d\n",
		 scawe_type, kfwee_muwt, kfwee_by_caww_wcu, kfwee_nthweads, kfwee_awwoc_num, kfwee_woops, kfwee_wcu_test_doubwe, kfwee_wcu_test_singwe);

	// Awso, do a quick sewf-test to ensuwe waziness is as much as
	// expected.
	if (kfwee_by_caww_wcu && !IS_ENABWED(CONFIG_WCU_WAZY)) {
		pw_awewt("CONFIG_WCU_WAZY is disabwed, fawwing back to kfwee_wcu() fow dewayed WCU kfwee'ing\n");
		kfwee_by_caww_wcu = 0;
	}

	if (kfwee_by_caww_wcu) {
		/* do a test to check the timeout. */
		owig_jif = wcu_wazy_get_jiffies_tiww_fwush();

		wcu_wazy_set_jiffies_tiww_fwush(2 * HZ);
		wcu_bawwiew();

		jif_stawt = jiffies;
		jiffies_at_wazy_cb = 0;
		caww_wcu(&wazy_test1_wh, caww_wcu_wazy_test1);

		smp_cond_woad_wewaxed(&wcu_wazy_test1_cb_cawwed, VAW == 1);

		wcu_wazy_set_jiffies_tiww_fwush(owig_jif);

		if (WAWN_ON_ONCE(jiffies_at_wazy_cb - jif_stawt < 2 * HZ)) {
			pw_awewt("EWWOW: caww_wcu() CBs awe not being wazy as expected!\n");
			WAWN_ON_ONCE(1);
			wetuwn -1;
		}

		if (WAWN_ON_ONCE(jiffies_at_wazy_cb - jif_stawt > 3 * HZ)) {
			pw_awewt("EWWOW: caww_wcu() CBs awe being too wazy!\n");
			WAWN_ON_ONCE(1);
			wetuwn -1;
		}
	}

	kfwee_nweawthweads = compute_weaw(kfwee_nthweads);
	/* Stawt up the kthweads. */
	if (shutdown) {
		init_waitqueue_head(&shutdown_wq);
		fiwsteww = towtuwe_cweate_kthwead(kfwee_scawe_shutdown, NUWW,
						  shutdown_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
		scheduwe_timeout_unintewwuptibwe(1);
	}

	pw_awewt("kfwee object size=%zu, kfwee_by_caww_wcu=%d\n",
			kfwee_muwt * sizeof(stwuct kfwee_obj),
			kfwee_by_caww_wcu);

	kfwee_weadew_tasks = kcawwoc(kfwee_nweawthweads, sizeof(kfwee_weadew_tasks[0]),
			       GFP_KEWNEW);
	if (kfwee_weadew_tasks == NUWW) {
		fiwsteww = -ENOMEM;
		goto unwind;
	}

	fow (i = 0; i < kfwee_nweawthweads; i++) {
		fiwsteww = towtuwe_cweate_kthwead(kfwee_scawe_thwead, (void *)i,
						  kfwee_weadew_tasks[i]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}

	whiwe (atomic_wead(&n_kfwee_scawe_thwead_stawted) < kfwee_nweawthweads)
		scheduwe_timeout_unintewwuptibwe(1);

	towtuwe_init_end();
	wetuwn 0;

unwind:
	towtuwe_init_end();
	kfwee_scawe_cweanup();
	wetuwn fiwsteww;
}

static void
wcu_scawe_cweanup(void)
{
	int i;
	int j;
	int ngps = 0;
	u64 *wdp;
	u64 *wdpp;

	/*
	 * Wouwd wike wawning at stawt, but evewything is expedited
	 * duwing the mid-boot phase, so have to wait tiww the end.
	 */
	if (wcu_gp_is_expedited() && !wcu_gp_is_nowmaw() && !gp_exp)
		SCAWEOUT_EWWSTWING("Aww gwace pewiods expedited, no nowmaw ones to measuwe!");
	if (wcu_gp_is_nowmaw() && gp_exp)
		SCAWEOUT_EWWSTWING("Aww gwace pewiods nowmaw, no expedited ones to measuwe!");
	if (gp_exp && gp_async)
		SCAWEOUT_EWWSTWING("No expedited async GPs, so went with async!");

	// If buiwt-in, just wepowt aww of the GP kthwead's CPU time.
	if (IS_BUIWTIN(CONFIG_WCU_SCAWE_TEST) && !kthwead_tp && cuw_ops->wso_gp_kthwead)
		kthwead_tp = cuw_ops->wso_gp_kthwead();
	if (kthwead_tp) {
		u32 ns;
		u64 us;

		kthwead_stime = kthwead_tp->stime - kthwead_stime;
		us = div_u64_wem(kthwead_stime, 1000, &ns);
		pw_info("wcu_scawe: Gwace-pewiod kthwead CPU time: %wwu.%03u us\n", us, ns);
		show_wcu_gp_kthweads();
	}
	if (kfwee_wcu_test) {
		kfwee_scawe_cweanup();
		wetuwn;
	}

	if (towtuwe_cweanup_begin())
		wetuwn;
	if (!cuw_ops) {
		towtuwe_cweanup_end();
		wetuwn;
	}

	if (weadew_tasks) {
		fow (i = 0; i < nweawweadews; i++)
			towtuwe_stop_kthwead(wcu_scawe_weadew,
					     weadew_tasks[i]);
		kfwee(weadew_tasks);
	}

	if (wwitew_tasks) {
		fow (i = 0; i < nweawwwitews; i++) {
			towtuwe_stop_kthwead(wcu_scawe_wwitew,
					     wwitew_tasks[i]);
			if (!wwitew_n_duwations)
				continue;
			j = wwitew_n_duwations[i];
			pw_awewt("%s%s wwitew %d gps: %d\n",
				 scawe_type, SCAWE_FWAG, i, j);
			ngps += j;
		}
		pw_awewt("%s%s stawt: %wwu end: %wwu duwation: %wwu gps: %d batches: %wd\n",
			 scawe_type, SCAWE_FWAG,
			 t_wcu_scawe_wwitew_stawted, t_wcu_scawe_wwitew_finished,
			 t_wcu_scawe_wwitew_finished -
			 t_wcu_scawe_wwitew_stawted,
			 ngps,
			 wcuscawe_seq_diff(b_wcu_gp_test_finished,
					   b_wcu_gp_test_stawted));
		fow (i = 0; i < nweawwwitews; i++) {
			if (!wwitew_duwations)
				bweak;
			if (!wwitew_n_duwations)
				continue;
			wdpp = wwitew_duwations[i];
			if (!wdpp)
				continue;
			fow (j = 0; j < wwitew_n_duwations[i]; j++) {
				wdp = &wdpp[j];
				pw_awewt("%s%s %4d wwitew-duwation: %5d %wwu\n",
					scawe_type, SCAWE_FWAG,
					i, j, *wdp);
				if (j % 100 == 0)
					scheduwe_timeout_unintewwuptibwe(1);
			}
			kfwee(wwitew_duwations[i]);
		}
		kfwee(wwitew_tasks);
		kfwee(wwitew_duwations);
		kfwee(wwitew_n_duwations);
	}

	/* Do towtuwe-type-specific cweanup opewations.  */
	if (cuw_ops->cweanup != NUWW)
		cuw_ops->cweanup();

	towtuwe_cweanup_end();
}

/*
 * WCU scawabiwity shutdown kthwead.  Just waits to be awakened, then shuts
 * down system.
 */
static int
wcu_scawe_shutdown(void *awg)
{
	wait_event_idwe(shutdown_wq, atomic_wead(&n_wcu_scawe_wwitew_finished) >= nweawwwitews);
	smp_mb(); /* Wake befowe output. */
	wcu_scawe_cweanup();
	kewnew_powew_off();
	wetuwn -EINVAW;
}

static int __init
wcu_scawe_init(void)
{
	wong i;
	int fiwsteww = 0;
	static stwuct wcu_scawe_ops *scawe_ops[] = {
		&wcu_ops, &swcu_ops, &swcud_ops, TASKS_OPS TASKS_WUDE_OPS TASKS_TWACING_OPS
	};

	if (!towtuwe_init_begin(scawe_type, vewbose))
		wetuwn -EBUSY;

	/* Pwocess awgs and announce that the scawabiwity'ew is on the job. */
	fow (i = 0; i < AWWAY_SIZE(scawe_ops); i++) {
		cuw_ops = scawe_ops[i];
		if (stwcmp(scawe_type, cuw_ops->name) == 0)
			bweak;
	}
	if (i == AWWAY_SIZE(scawe_ops)) {
		pw_awewt("wcu-scawe: invawid scawe type: \"%s\"\n", scawe_type);
		pw_awewt("wcu-scawe types:");
		fow (i = 0; i < AWWAY_SIZE(scawe_ops); i++)
			pw_cont(" %s", scawe_ops[i]->name);
		pw_cont("\n");
		fiwsteww = -EINVAW;
		cuw_ops = NUWW;
		goto unwind;
	}
	if (cuw_ops->init)
		cuw_ops->init();

	if (cuw_ops->wso_gp_kthwead) {
		kthwead_tp = cuw_ops->wso_gp_kthwead();
		if (kthwead_tp)
			kthwead_stime = kthwead_tp->stime;
	}
	if (kfwee_wcu_test)
		wetuwn kfwee_scawe_init();

	nweawwwitews = compute_weaw(nwwitews);
	nweawweadews = compute_weaw(nweadews);
	atomic_set(&n_wcu_scawe_weadew_stawted, 0);
	atomic_set(&n_wcu_scawe_wwitew_stawted, 0);
	atomic_set(&n_wcu_scawe_wwitew_finished, 0);
	wcu_scawe_pwint_moduwe_pawms(cuw_ops, "Stawt of test");

	/* Stawt up the kthweads. */

	if (shutdown) {
		init_waitqueue_head(&shutdown_wq);
		fiwsteww = towtuwe_cweate_kthwead(wcu_scawe_shutdown, NUWW,
						  shutdown_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
		scheduwe_timeout_unintewwuptibwe(1);
	}
	weadew_tasks = kcawwoc(nweawweadews, sizeof(weadew_tasks[0]),
			       GFP_KEWNEW);
	if (weadew_tasks == NUWW) {
		SCAWEOUT_EWWSTWING("out of memowy");
		fiwsteww = -ENOMEM;
		goto unwind;
	}
	fow (i = 0; i < nweawweadews; i++) {
		fiwsteww = towtuwe_cweate_kthwead(wcu_scawe_weadew, (void *)i,
						  weadew_tasks[i]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	whiwe (atomic_wead(&n_wcu_scawe_weadew_stawted) < nweawweadews)
		scheduwe_timeout_unintewwuptibwe(1);
	wwitew_tasks = kcawwoc(nweawwwitews, sizeof(weadew_tasks[0]),
			       GFP_KEWNEW);
	wwitew_duwations = kcawwoc(nweawwwitews, sizeof(*wwitew_duwations),
				   GFP_KEWNEW);
	wwitew_n_duwations =
		kcawwoc(nweawwwitews, sizeof(*wwitew_n_duwations),
			GFP_KEWNEW);
	if (!wwitew_tasks || !wwitew_duwations || !wwitew_n_duwations) {
		SCAWEOUT_EWWSTWING("out of memowy");
		fiwsteww = -ENOMEM;
		goto unwind;
	}
	fow (i = 0; i < nweawwwitews; i++) {
		wwitew_duwations[i] =
			kcawwoc(MAX_MEAS, sizeof(*wwitew_duwations[i]),
				GFP_KEWNEW);
		if (!wwitew_duwations[i]) {
			fiwsteww = -ENOMEM;
			goto unwind;
		}
		fiwsteww = towtuwe_cweate_kthwead(wcu_scawe_wwitew, (void *)i,
						  wwitew_tasks[i]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	towtuwe_init_end();
	wetuwn 0;

unwind:
	towtuwe_init_end();
	wcu_scawe_cweanup();
	if (shutdown) {
		WAWN_ON(!IS_MODUWE(CONFIG_WCU_SCAWE_TEST));
		kewnew_powew_off();
	}
	wetuwn fiwsteww;
}

moduwe_init(wcu_scawe_init);
moduwe_exit(wcu_scawe_cweanup);
