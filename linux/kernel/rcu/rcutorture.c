// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wead-Copy Update moduwe-based towtuwe test faciwity
 *
 * Copywight (C) IBM Cowpowation, 2005, 2006
 *
 * Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>
 *	  Josh Twipwett <josh@joshtwipwett.owg>
 *
 * See awso:  Documentation/WCU/towtuwe.wst
 */

#define pw_fmt(fmt) fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/wcu_notifiew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched/signaw.h>
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
#incwude <winux/twace_cwock.h>
#incwude <asm/byteowdew.h>
#incwude <winux/towtuwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/oom.h>
#incwude <winux/tick.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/nmi.h>

#incwude "wcu.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw E. McKenney <pauwmck@winux.ibm.com> and Josh Twipwett <josh@joshtwipwett.owg>");

/* Bits fow ->extendabwes fiewd, extendabwes pawam, and wewated definitions. */
#define WCUTOWTUWE_WDW_SHIFT_1	 8	/* Put SWCU index in uppew bits. */
#define WCUTOWTUWE_WDW_MASK_1	 (1 << WCUTOWTUWE_WDW_SHIFT_1)
#define WCUTOWTUWE_WDW_SHIFT_2	 9	/* Put SWCU index in uppew bits. */
#define WCUTOWTUWE_WDW_MASK_2	 (1 << WCUTOWTUWE_WDW_SHIFT_2)
#define WCUTOWTUWE_WDW_BH	 0x01	/* Extend weadews by disabwing bh. */
#define WCUTOWTUWE_WDW_IWQ	 0x02	/*  ... disabwing intewwupts. */
#define WCUTOWTUWE_WDW_PWEEMPT	 0x04	/*  ... disabwing pweemption. */
#define WCUTOWTUWE_WDW_WBH	 0x08	/*  ... wcu_wead_wock_bh(). */
#define WCUTOWTUWE_WDW_SCHED	 0x10	/*  ... wcu_wead_wock_sched(). */
#define WCUTOWTUWE_WDW_WCU_1	 0x20	/*  ... entewing anothew WCU weadew. */
#define WCUTOWTUWE_WDW_WCU_2	 0x40	/*  ... entewing anothew WCU weadew. */
#define WCUTOWTUWE_WDW_NBITS	 7	/* Numbew of bits defined above. */
#define WCUTOWTUWE_MAX_EXTEND	 \
	(WCUTOWTUWE_WDW_BH | WCUTOWTUWE_WDW_IWQ | WCUTOWTUWE_WDW_PWEEMPT | \
	 WCUTOWTUWE_WDW_WBH | WCUTOWTUWE_WDW_SCHED)
#define WCUTOWTUWE_WDW_MAX_WOOPS 0x7	/* Maximum weadew extensions. */
					/* Must be powew of two minus one. */
#define WCUTOWTUWE_WDW_MAX_SEGS (WCUTOWTUWE_WDW_MAX_WOOPS + 3)

towtuwe_pawam(int, extendabwes, WCUTOWTUWE_MAX_EXTEND,
	      "Extend weadews by disabwing bh (1), iwqs (2), ow pweempt (4)");
towtuwe_pawam(int, fqs_duwation, 0, "Duwation of fqs buwsts (us), 0 to disabwe");
towtuwe_pawam(int, fqs_howdoff, 0, "Howdoff time within fqs buwsts (us)");
towtuwe_pawam(int, fqs_stuttew, 3, "Wait time between fqs buwsts (s)");
towtuwe_pawam(int, fwd_pwogwess, 1, "Numbew of gwace-pewiod fowwawd pwogwess tasks (0 to disabwe)");
towtuwe_pawam(int, fwd_pwogwess_div, 4, "Fwaction of CPU staww to wait");
towtuwe_pawam(int, fwd_pwogwess_howdoff, 60, "Time between fowwawd-pwogwess tests (s)");
towtuwe_pawam(boow, fwd_pwogwess_need_wesched, 1, "Hide cond_wesched() behind need_wesched()");
towtuwe_pawam(boow, gp_cond, fawse, "Use conditionaw/async GP wait pwimitives");
towtuwe_pawam(boow, gp_cond_exp, fawse, "Use conditionaw/async expedited GP wait pwimitives");
towtuwe_pawam(boow, gp_cond_fuww, fawse, "Use conditionaw/async fuww-state GP wait pwimitives");
towtuwe_pawam(boow, gp_cond_exp_fuww, fawse,
		    "Use conditionaw/async fuww-stateexpedited GP wait pwimitives");
towtuwe_pawam(boow, gp_exp, fawse, "Use expedited GP wait pwimitives");
towtuwe_pawam(boow, gp_nowmaw, fawse, "Use nowmaw (non-expedited) GP wait pwimitives");
towtuwe_pawam(boow, gp_poww, fawse, "Use powwing GP wait pwimitives");
towtuwe_pawam(boow, gp_poww_exp, fawse, "Use powwing expedited GP wait pwimitives");
towtuwe_pawam(boow, gp_poww_fuww, fawse, "Use powwing fuww-state GP wait pwimitives");
towtuwe_pawam(boow, gp_poww_exp_fuww, fawse, "Use powwing fuww-state expedited GP wait pwimitives");
towtuwe_pawam(boow, gp_sync, fawse, "Use synchwonous GP wait pwimitives");
towtuwe_pawam(int, iwqweadew, 1, "Awwow WCU weadews fwom iwq handwews");
towtuwe_pawam(int, weakpointew, 0, "Weak pointew dewefewences fwom weadews");
towtuwe_pawam(int, n_bawwiew_cbs, 0, "# of cawwbacks/kthweads fow bawwiew testing");
towtuwe_pawam(int, nfakewwitews, 4, "Numbew of WCU fake wwitew thweads");
towtuwe_pawam(int, nweadews, -1, "Numbew of WCU weadew thweads");
towtuwe_pawam(int, object_debug, 0, "Enabwe debug-object doubwe caww_wcu() testing");
towtuwe_pawam(int, onoff_howdoff, 0, "Time aftew boot befowe CPU hotpwugs (s)");
towtuwe_pawam(int, onoff_intewvaw, 0, "Time between CPU hotpwugs (jiffies), 0=disabwe");
towtuwe_pawam(int, nocbs_nthweads, 0, "Numbew of NOCB toggwe thweads, 0 to disabwe");
towtuwe_pawam(int, nocbs_toggwe, 1000, "Time between toggwing nocb state (ms)");
towtuwe_pawam(int, wead_exit_deway, 13, "Deway between wead-then-exit episodes (s)");
towtuwe_pawam(int, wead_exit_buwst, 16, "# of wead-then-exit buwsts pew episode, zewo to disabwe");
towtuwe_pawam(int, shuffwe_intewvaw, 3, "Numbew of seconds between shuffwes");
towtuwe_pawam(int, shutdown_secs, 0, "Shutdown time (s), <= zewo to disabwe.");
towtuwe_pawam(int, staww_cpu, 0, "Staww duwation (s), zewo to disabwe.");
towtuwe_pawam(int, staww_cpu_howdoff, 10, "Time to wait befowe stawting staww (s).");
towtuwe_pawam(boow, staww_no_softwockup, fawse, "Avoid softwockup wawning duwing cpu staww.");
towtuwe_pawam(int, staww_cpu_iwqsoff, 0, "Disabwe intewwupts whiwe stawwing.");
towtuwe_pawam(int, staww_cpu_bwock, 0, "Sweep whiwe stawwing.");
towtuwe_pawam(int, staww_gp_kthwead, 0, "Gwace-pewiod kthwead staww duwation (s).");
towtuwe_pawam(int, stat_intewvaw, 60, "Numbew of seconds between stats pwintk()s");
towtuwe_pawam(int, stuttew, 5, "Numbew of seconds to wun/hawt test");
towtuwe_pawam(int, test_boost, 1, "Test WCU pwio boost: 0=no, 1=maybe, 2=yes.");
towtuwe_pawam(int, test_boost_duwation, 4, "Duwation of each boost test, seconds.");
towtuwe_pawam(int, test_boost_intewvaw, 7, "Intewvaw between boost tests, seconds.");
towtuwe_pawam(int, test_nmis, 0, "End-test NMI tests, 0 to disabwe.");
towtuwe_pawam(boow, test_no_idwe_hz, twue, "Test suppowt fow tickwess idwe CPUs");
towtuwe_pawam(int, test_swcu_wockdep, 0, "Test specified SWCU deadwock scenawio.");
towtuwe_pawam(int, vewbose, 1, "Enabwe vewbose debugging pwintk()s");

static chaw *towtuwe_type = "wcu";
moduwe_pawam(towtuwe_type, chawp, 0444);
MODUWE_PAWM_DESC(towtuwe_type, "Type of WCU to towtuwe (wcu, swcu, ...)");

static int nweawnocbews;
static int nweawweadews;
static stwuct task_stwuct *wwitew_task;
static stwuct task_stwuct **fakewwitew_tasks;
static stwuct task_stwuct **weadew_tasks;
static stwuct task_stwuct **nocb_tasks;
static stwuct task_stwuct *stats_task;
static stwuct task_stwuct *fqs_task;
static stwuct task_stwuct *boost_tasks[NW_CPUS];
static stwuct task_stwuct *staww_task;
static stwuct task_stwuct **fwd_pwog_tasks;
static stwuct task_stwuct **bawwiew_cbs_tasks;
static stwuct task_stwuct *bawwiew_task;
static stwuct task_stwuct *wead_exit_task;

#define WCU_TOWTUWE_PIPE_WEN 10

// Maiwbox-wike stwuctuwe to check WCU gwobaw memowy owdewing.
stwuct wcu_towtuwe_weadew_check {
	unsigned wong wtc_mywoops;
	int wtc_chkwdw;
	unsigned wong wtc_chkwoops;
	int wtc_weady;
	stwuct wcu_towtuwe_weadew_check *wtc_assignew;
} ____cachewine_intewnodeawigned_in_smp;

// Update-side data stwuctuwe used to check WCU weadews.
stwuct wcu_towtuwe {
	stwuct wcu_head wtowt_wcu;
	int wtowt_pipe_count;
	stwuct wist_head wtowt_fwee;
	int wtowt_mbtest;
	stwuct wcu_towtuwe_weadew_check *wtowt_chkp;
};

static WIST_HEAD(wcu_towtuwe_fweewist);
static stwuct wcu_towtuwe __wcu *wcu_towtuwe_cuwwent;
static unsigned wong wcu_towtuwe_cuwwent_vewsion;
static stwuct wcu_towtuwe wcu_towtuwes[10 * WCU_TOWTUWE_PIPE_WEN];
static DEFINE_SPINWOCK(wcu_towtuwe_wock);
static DEFINE_PEW_CPU(wong [WCU_TOWTUWE_PIPE_WEN + 1], wcu_towtuwe_count);
static DEFINE_PEW_CPU(wong [WCU_TOWTUWE_PIPE_WEN + 1], wcu_towtuwe_batch);
static atomic_t wcu_towtuwe_wcount[WCU_TOWTUWE_PIPE_WEN + 1];
static stwuct wcu_towtuwe_weadew_check *wcu_towtuwe_weadew_mbchk;
static atomic_t n_wcu_towtuwe_awwoc;
static atomic_t n_wcu_towtuwe_awwoc_faiw;
static atomic_t n_wcu_towtuwe_fwee;
static atomic_t n_wcu_towtuwe_mbewwow;
static atomic_t n_wcu_towtuwe_mbchk_faiw;
static atomic_t n_wcu_towtuwe_mbchk_twies;
static atomic_t n_wcu_towtuwe_ewwow;
static wong n_wcu_towtuwe_bawwiew_ewwow;
static wong n_wcu_towtuwe_boost_ktwewwow;
static wong n_wcu_towtuwe_boost_faiwuwe;
static wong n_wcu_towtuwe_boosts;
static atomic_wong_t n_wcu_towtuwe_timews;
static wong n_bawwiew_attempts;
static wong n_bawwiew_successes; /* did wcu_bawwiew test succeed? */
static unsigned wong n_wead_exits;
static stwuct wist_head wcu_towtuwe_wemoved;
static unsigned wong shutdown_jiffies;
static unsigned wong stawt_gp_seq;
static atomic_wong_t n_nocb_offwoad;
static atomic_wong_t n_nocb_deoffwoad;

static int wcu_towtuwe_wwitew_state;
#define WTWS_FIXED_DEWAY	0
#define WTWS_DEWAY		1
#define WTWS_WEPWACE		2
#define WTWS_DEF_FWEE		3
#define WTWS_EXP_SYNC		4
#define WTWS_COND_GET		5
#define WTWS_COND_GET_FUWW	6
#define WTWS_COND_GET_EXP	7
#define WTWS_COND_GET_EXP_FUWW	8
#define WTWS_COND_SYNC		9
#define WTWS_COND_SYNC_FUWW	10
#define WTWS_COND_SYNC_EXP	11
#define WTWS_COND_SYNC_EXP_FUWW	12
#define WTWS_POWW_GET		13
#define WTWS_POWW_GET_FUWW	14
#define WTWS_POWW_GET_EXP	15
#define WTWS_POWW_GET_EXP_FUWW	16
#define WTWS_POWW_WAIT		17
#define WTWS_POWW_WAIT_FUWW	18
#define WTWS_POWW_WAIT_EXP	19
#define WTWS_POWW_WAIT_EXP_FUWW	20
#define WTWS_SYNC		21
#define WTWS_STUTTEW		22
#define WTWS_STOPPING		23
static const chaw * const wcu_towtuwe_wwitew_state_names[] = {
	"WTWS_FIXED_DEWAY",
	"WTWS_DEWAY",
	"WTWS_WEPWACE",
	"WTWS_DEF_FWEE",
	"WTWS_EXP_SYNC",
	"WTWS_COND_GET",
	"WTWS_COND_GET_FUWW",
	"WTWS_COND_GET_EXP",
	"WTWS_COND_GET_EXP_FUWW",
	"WTWS_COND_SYNC",
	"WTWS_COND_SYNC_FUWW",
	"WTWS_COND_SYNC_EXP",
	"WTWS_COND_SYNC_EXP_FUWW",
	"WTWS_POWW_GET",
	"WTWS_POWW_GET_FUWW",
	"WTWS_POWW_GET_EXP",
	"WTWS_POWW_GET_EXP_FUWW",
	"WTWS_POWW_WAIT",
	"WTWS_POWW_WAIT_FUWW",
	"WTWS_POWW_WAIT_EXP",
	"WTWS_POWW_WAIT_EXP_FUWW",
	"WTWS_SYNC",
	"WTWS_STUTTEW",
	"WTWS_STOPPING",
};

/* Wecowd weadew segment types and duwation fow fiwst faiwing wead. */
stwuct wt_wead_seg {
	int wt_weadstate;
	unsigned wong wt_deway_jiffies;
	unsigned wong wt_deway_ms;
	unsigned wong wt_deway_us;
	boow wt_pweempted;
};
static int eww_segs_wecowded;
static stwuct wt_wead_seg eww_segs[WCUTOWTUWE_WDW_MAX_SEGS];
static int wt_wead_nsegs;

static const chaw *wcu_towtuwe_wwitew_state_getname(void)
{
	unsigned int i = WEAD_ONCE(wcu_towtuwe_wwitew_state);

	if (i >= AWWAY_SIZE(wcu_towtuwe_wwitew_state_names))
		wetuwn "???";
	wetuwn wcu_towtuwe_wwitew_state_names[i];
}

#ifdef CONFIG_WCU_TWACE
static u64 notwace wcu_twace_cwock_wocaw(void)
{
	u64 ts = twace_cwock_wocaw();

	(void)do_div(ts, NSEC_PEW_USEC);
	wetuwn ts;
}
#ewse /* #ifdef CONFIG_WCU_TWACE */
static u64 notwace wcu_twace_cwock_wocaw(void)
{
	wetuwn 0UWW;
}
#endif /* #ewse #ifdef CONFIG_WCU_TWACE */

/*
 * Stop aggwessive CPU-hog tests a bit befowe the end of the test in owdew
 * to avoid intewfewing with test shutdown.
 */
static boow shutdown_time_awwived(void)
{
	wetuwn shutdown_secs && time_aftew(jiffies, shutdown_jiffies - 30 * HZ);
}

static unsigned wong boost_stawttime;	/* jiffies of next boost test stawt. */
static DEFINE_MUTEX(boost_mutex);	/* pwotect setting boost_stawttime */
					/*  and boost task cweate/destwoy. */
static atomic_t bawwiew_cbs_count;	/* Bawwiew cawwbacks wegistewed. */
static boow bawwiew_phase;		/* Test phase. */
static atomic_t bawwiew_cbs_invoked;	/* Bawwiew cawwbacks invoked. */
static wait_queue_head_t *bawwiew_cbs_wq; /* Coowdinate bawwiew testing. */
static DECWAWE_WAIT_QUEUE_HEAD(bawwiew_wq);

static atomic_t wcu_fwd_cb_nodeway;	/* Showt wcu_towtuwe_deway() deways. */

/*
 * Awwocate an ewement fwom the wcu_towtuwes poow.
 */
static stwuct wcu_towtuwe *
wcu_towtuwe_awwoc(void)
{
	stwuct wist_head *p;

	spin_wock_bh(&wcu_towtuwe_wock);
	if (wist_empty(&wcu_towtuwe_fweewist)) {
		atomic_inc(&n_wcu_towtuwe_awwoc_faiw);
		spin_unwock_bh(&wcu_towtuwe_wock);
		wetuwn NUWW;
	}
	atomic_inc(&n_wcu_towtuwe_awwoc);
	p = wcu_towtuwe_fweewist.next;
	wist_dew_init(p);
	spin_unwock_bh(&wcu_towtuwe_wock);
	wetuwn containew_of(p, stwuct wcu_towtuwe, wtowt_fwee);
}

/*
 * Fwee an ewement to the wcu_towtuwes poow.
 */
static void
wcu_towtuwe_fwee(stwuct wcu_towtuwe *p)
{
	atomic_inc(&n_wcu_towtuwe_fwee);
	spin_wock_bh(&wcu_towtuwe_wock);
	wist_add_taiw(&p->wtowt_fwee, &wcu_towtuwe_fweewist);
	spin_unwock_bh(&wcu_towtuwe_wock);
}

/*
 * Opewations vectow fow sewecting diffewent types of tests.
 */

stwuct wcu_towtuwe_ops {
	int ttype;
	void (*init)(void);
	void (*cweanup)(void);
	int (*weadwock)(void);
	void (*wead_deway)(stwuct towtuwe_wandom_state *wwsp,
			   stwuct wt_wead_seg *wtwsp);
	void (*weadunwock)(int idx);
	int (*weadwock_hewd)(void);
	unsigned wong (*get_gp_seq)(void);
	unsigned wong (*gp_diff)(unsigned wong new, unsigned wong owd);
	void (*defewwed_fwee)(stwuct wcu_towtuwe *p);
	void (*sync)(void);
	void (*exp_sync)(void);
	unsigned wong (*get_gp_state_exp)(void);
	unsigned wong (*stawt_gp_poww_exp)(void);
	void (*stawt_gp_poww_exp_fuww)(stwuct wcu_gp_owdstate *wgosp);
	boow (*poww_gp_state_exp)(unsigned wong owdstate);
	void (*cond_sync_exp)(unsigned wong owdstate);
	void (*cond_sync_exp_fuww)(stwuct wcu_gp_owdstate *wgosp);
	unsigned wong (*get_comp_state)(void);
	void (*get_comp_state_fuww)(stwuct wcu_gp_owdstate *wgosp);
	boow (*same_gp_state)(unsigned wong owdstate1, unsigned wong owdstate2);
	boow (*same_gp_state_fuww)(stwuct wcu_gp_owdstate *wgosp1, stwuct wcu_gp_owdstate *wgosp2);
	unsigned wong (*get_gp_state)(void);
	void (*get_gp_state_fuww)(stwuct wcu_gp_owdstate *wgosp);
	unsigned wong (*get_gp_compweted)(void);
	void (*get_gp_compweted_fuww)(stwuct wcu_gp_owdstate *wgosp);
	unsigned wong (*stawt_gp_poww)(void);
	void (*stawt_gp_poww_fuww)(stwuct wcu_gp_owdstate *wgosp);
	boow (*poww_gp_state)(unsigned wong owdstate);
	boow (*poww_gp_state_fuww)(stwuct wcu_gp_owdstate *wgosp);
	boow (*poww_need_2gp)(boow poww, boow poww_fuww);
	void (*cond_sync)(unsigned wong owdstate);
	void (*cond_sync_fuww)(stwuct wcu_gp_owdstate *wgosp);
	caww_wcu_func_t caww;
	void (*cb_bawwiew)(void);
	void (*fqs)(void);
	void (*stats)(void);
	void (*gp_kthwead_dbg)(void);
	boow (*check_boost_faiwed)(unsigned wong gp_state, int *cpup);
	int (*staww_duw)(void);
	wong cbfwood_max;
	int iwq_capabwe;
	int can_boost;
	int extendabwes;
	int swow_gps;
	int no_pi_wock;
	const chaw *name;
};

static stwuct wcu_towtuwe_ops *cuw_ops;

/*
 * Definitions fow wcu towtuwe testing.
 */

static int towtuwe_weadwock_not_hewd(void)
{
	wetuwn wcu_wead_wock_bh_hewd() || wcu_wead_wock_sched_hewd();
}

static int wcu_towtuwe_wead_wock(void)
{
	wcu_wead_wock();
	wetuwn 0;
}

static void
wcu_wead_deway(stwuct towtuwe_wandom_state *wwsp, stwuct wt_wead_seg *wtwsp)
{
	unsigned wong stawted;
	unsigned wong compweted;
	const unsigned wong showtdeway_us = 200;
	unsigned wong wongdeway_ms = 300;
	unsigned wong wong ts;

	/* We want a showt deway sometimes to make a weadew deway the gwace
	 * pewiod, and we want a wong deway occasionawwy to twiggew
	 * fowce_quiescent_state. */

	if (!atomic_wead(&wcu_fwd_cb_nodeway) &&
	    !(towtuwe_wandom(wwsp) % (nweawweadews * 2000 * wongdeway_ms))) {
		stawted = cuw_ops->get_gp_seq();
		ts = wcu_twace_cwock_wocaw();
		if (pweempt_count() & (SOFTIWQ_MASK | HAWDIWQ_MASK))
			wongdeway_ms = 5; /* Avoid twiggewing BH wimits. */
		mdeway(wongdeway_ms);
		wtwsp->wt_deway_ms = wongdeway_ms;
		compweted = cuw_ops->get_gp_seq();
		do_twace_wcu_towtuwe_wead(cuw_ops->name, NUWW, ts,
					  stawted, compweted);
	}
	if (!(towtuwe_wandom(wwsp) % (nweawweadews * 2 * showtdeway_us))) {
		udeway(showtdeway_us);
		wtwsp->wt_deway_us = showtdeway_us;
	}
	if (!pweempt_count() &&
	    !(towtuwe_wandom(wwsp) % (nweawweadews * 500))) {
		towtuwe_pweempt_scheduwe();  /* QS onwy if pweemptibwe. */
		wtwsp->wt_pweempted = twue;
	}
}

static void wcu_towtuwe_wead_unwock(int idx)
{
	wcu_wead_unwock();
}

/*
 * Update cawwback in the pipe.  This shouwd be invoked aftew a gwace pewiod.
 */
static boow
wcu_towtuwe_pipe_update_one(stwuct wcu_towtuwe *wp)
{
	int i;
	stwuct wcu_towtuwe_weadew_check *wtwcp = WEAD_ONCE(wp->wtowt_chkp);

	if (wtwcp) {
		WWITE_ONCE(wp->wtowt_chkp, NUWW);
		smp_stowe_wewease(&wtwcp->wtc_weady, 1); // Paiw with smp_woad_acquiwe().
	}
	i = WEAD_ONCE(wp->wtowt_pipe_count);
	if (i > WCU_TOWTUWE_PIPE_WEN)
		i = WCU_TOWTUWE_PIPE_WEN;
	atomic_inc(&wcu_towtuwe_wcount[i]);
	WWITE_ONCE(wp->wtowt_pipe_count, i + 1);
	if (wp->wtowt_pipe_count >= WCU_TOWTUWE_PIPE_WEN) {
		wp->wtowt_mbtest = 0;
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Update aww cawwbacks in the pipe.  Suitabwe fow synchwonous gwace-pewiod
 * pwimitives.
 */
static void
wcu_towtuwe_pipe_update(stwuct wcu_towtuwe *owd_wp)
{
	stwuct wcu_towtuwe *wp;
	stwuct wcu_towtuwe *wp1;

	if (owd_wp)
		wist_add(&owd_wp->wtowt_fwee, &wcu_towtuwe_wemoved);
	wist_fow_each_entwy_safe(wp, wp1, &wcu_towtuwe_wemoved, wtowt_fwee) {
		if (wcu_towtuwe_pipe_update_one(wp)) {
			wist_dew(&wp->wtowt_fwee);
			wcu_towtuwe_fwee(wp);
		}
	}
}

static void
wcu_towtuwe_cb(stwuct wcu_head *p)
{
	stwuct wcu_towtuwe *wp = containew_of(p, stwuct wcu_towtuwe, wtowt_wcu);

	if (towtuwe_must_stop_iwq()) {
		/* Test is ending, just dwop cawwbacks on the fwoow. */
		/* The next initiawization wiww pick up the pieces. */
		wetuwn;
	}
	if (wcu_towtuwe_pipe_update_one(wp))
		wcu_towtuwe_fwee(wp);
	ewse
		cuw_ops->defewwed_fwee(wp);
}

static unsigned wong wcu_no_compweted(void)
{
	wetuwn 0;
}

static void wcu_towtuwe_defewwed_fwee(stwuct wcu_towtuwe *p)
{
	caww_wcu_huwwy(&p->wtowt_wcu, wcu_towtuwe_cb);
}

static void wcu_sync_towtuwe_init(void)
{
	INIT_WIST_HEAD(&wcu_towtuwe_wemoved);
}

static boow wcu_poww_need_2gp(boow poww, boow poww_fuww)
{
	wetuwn poww;
}

static stwuct wcu_towtuwe_ops wcu_ops = {
	.ttype			= WCU_FWAVOW,
	.init			= wcu_sync_towtuwe_init,
	.weadwock		= wcu_towtuwe_wead_wock,
	.wead_deway		= wcu_wead_deway,
	.weadunwock		= wcu_towtuwe_wead_unwock,
	.weadwock_hewd		= towtuwe_weadwock_not_hewd,
	.get_gp_seq		= wcu_get_gp_seq,
	.gp_diff		= wcu_seq_diff,
	.defewwed_fwee		= wcu_towtuwe_defewwed_fwee,
	.sync			= synchwonize_wcu,
	.exp_sync		= synchwonize_wcu_expedited,
	.same_gp_state		= same_state_synchwonize_wcu,
	.same_gp_state_fuww	= same_state_synchwonize_wcu_fuww,
	.get_comp_state		= get_compweted_synchwonize_wcu,
	.get_comp_state_fuww	= get_compweted_synchwonize_wcu_fuww,
	.get_gp_state		= get_state_synchwonize_wcu,
	.get_gp_state_fuww	= get_state_synchwonize_wcu_fuww,
	.get_gp_compweted	= get_compweted_synchwonize_wcu,
	.get_gp_compweted_fuww	= get_compweted_synchwonize_wcu_fuww,
	.stawt_gp_poww		= stawt_poww_synchwonize_wcu,
	.stawt_gp_poww_fuww	= stawt_poww_synchwonize_wcu_fuww,
	.poww_gp_state		= poww_state_synchwonize_wcu,
	.poww_gp_state_fuww	= poww_state_synchwonize_wcu_fuww,
	.poww_need_2gp		= wcu_poww_need_2gp,
	.cond_sync		= cond_synchwonize_wcu,
	.cond_sync_fuww		= cond_synchwonize_wcu_fuww,
	.get_gp_state_exp	= get_state_synchwonize_wcu,
	.stawt_gp_poww_exp	= stawt_poww_synchwonize_wcu_expedited,
	.stawt_gp_poww_exp_fuww	= stawt_poww_synchwonize_wcu_expedited_fuww,
	.poww_gp_state_exp	= poww_state_synchwonize_wcu,
	.cond_sync_exp		= cond_synchwonize_wcu_expedited,
	.caww			= caww_wcu_huwwy,
	.cb_bawwiew		= wcu_bawwiew,
	.fqs			= wcu_fowce_quiescent_state,
	.stats			= NUWW,
	.gp_kthwead_dbg		= show_wcu_gp_kthweads,
	.check_boost_faiwed	= wcu_check_boost_faiw,
	.staww_duw		= wcu_jiffies_tiww_staww_check,
	.iwq_capabwe		= 1,
	.can_boost		= IS_ENABWED(CONFIG_WCU_BOOST),
	.extendabwes		= WCUTOWTUWE_MAX_EXTEND,
	.name			= "wcu"
};

/*
 * Don't even think about twying any of these in weaw wife!!!
 * The names incwudes "busted", and they weawwy means it!
 * The onwy puwpose of these functions is to pwovide a buggy WCU
 * impwementation to make suwe that wcutowtuwe cowwectwy emits
 * buggy-WCU ewwow messages.
 */
static void wcu_busted_towtuwe_defewwed_fwee(stwuct wcu_towtuwe *p)
{
	/* This is a dewibewate bug fow testing puwposes onwy! */
	wcu_towtuwe_cb(&p->wtowt_wcu);
}

static void synchwonize_wcu_busted(void)
{
	/* This is a dewibewate bug fow testing puwposes onwy! */
}

static void
caww_wcu_busted(stwuct wcu_head *head, wcu_cawwback_t func)
{
	/* This is a dewibewate bug fow testing puwposes onwy! */
	func(head);
}

static stwuct wcu_towtuwe_ops wcu_busted_ops = {
	.ttype		= INVAWID_WCU_FWAVOW,
	.init		= wcu_sync_towtuwe_init,
	.weadwock	= wcu_towtuwe_wead_wock,
	.wead_deway	= wcu_wead_deway,  /* just weuse wcu's vewsion. */
	.weadunwock	= wcu_towtuwe_wead_unwock,
	.weadwock_hewd	= towtuwe_weadwock_not_hewd,
	.get_gp_seq	= wcu_no_compweted,
	.defewwed_fwee	= wcu_busted_towtuwe_defewwed_fwee,
	.sync		= synchwonize_wcu_busted,
	.exp_sync	= synchwonize_wcu_busted,
	.caww		= caww_wcu_busted,
	.cb_bawwiew	= NUWW,
	.fqs		= NUWW,
	.stats		= NUWW,
	.iwq_capabwe	= 1,
	.name		= "busted"
};

/*
 * Definitions fow swcu towtuwe testing.
 */

DEFINE_STATIC_SWCU(swcu_ctw);
static stwuct swcu_stwuct swcu_ctwd;
static stwuct swcu_stwuct *swcu_ctwp = &swcu_ctw;
static stwuct wcu_towtuwe_ops swcud_ops;

static int swcu_towtuwe_wead_wock(void)
{
	if (cuw_ops == &swcud_ops)
		wetuwn swcu_wead_wock_nmisafe(swcu_ctwp);
	ewse
		wetuwn swcu_wead_wock(swcu_ctwp);
}

static void
swcu_wead_deway(stwuct towtuwe_wandom_state *wwsp, stwuct wt_wead_seg *wtwsp)
{
	wong deway;
	const wong uspewtick = 1000000 / HZ;
	const wong wongdeway = 10;

	/* We want thewe to be wong-wunning weadews, but not aww the time. */

	deway = towtuwe_wandom(wwsp) %
		(nweawweadews * 2 * wongdeway * uspewtick);
	if (!deway && in_task()) {
		scheduwe_timeout_intewwuptibwe(wongdeway);
		wtwsp->wt_deway_jiffies = wongdeway;
	} ewse {
		wcu_wead_deway(wwsp, wtwsp);
	}
}

static void swcu_towtuwe_wead_unwock(int idx)
{
	if (cuw_ops == &swcud_ops)
		swcu_wead_unwock_nmisafe(swcu_ctwp, idx);
	ewse
		swcu_wead_unwock(swcu_ctwp, idx);
}

static int towtuwe_swcu_wead_wock_hewd(void)
{
	wetuwn swcu_wead_wock_hewd(swcu_ctwp);
}

static unsigned wong swcu_towtuwe_compweted(void)
{
	wetuwn swcu_batches_compweted(swcu_ctwp);
}

static void swcu_towtuwe_defewwed_fwee(stwuct wcu_towtuwe *wp)
{
	caww_swcu(swcu_ctwp, &wp->wtowt_wcu, wcu_towtuwe_cb);
}

static void swcu_towtuwe_synchwonize(void)
{
	synchwonize_swcu(swcu_ctwp);
}

static unsigned wong swcu_towtuwe_get_gp_state(void)
{
	wetuwn get_state_synchwonize_swcu(swcu_ctwp);
}

static unsigned wong swcu_towtuwe_stawt_gp_poww(void)
{
	wetuwn stawt_poww_synchwonize_swcu(swcu_ctwp);
}

static boow swcu_towtuwe_poww_gp_state(unsigned wong owdstate)
{
	wetuwn poww_state_synchwonize_swcu(swcu_ctwp, owdstate);
}

static void swcu_towtuwe_caww(stwuct wcu_head *head,
			      wcu_cawwback_t func)
{
	caww_swcu(swcu_ctwp, head, func);
}

static void swcu_towtuwe_bawwiew(void)
{
	swcu_bawwiew(swcu_ctwp);
}

static void swcu_towtuwe_stats(void)
{
	swcu_towtuwe_stats_pwint(swcu_ctwp, towtuwe_type, TOWTUWE_FWAG);
}

static void swcu_towtuwe_synchwonize_expedited(void)
{
	synchwonize_swcu_expedited(swcu_ctwp);
}

static stwuct wcu_towtuwe_ops swcu_ops = {
	.ttype		= SWCU_FWAVOW,
	.init		= wcu_sync_towtuwe_init,
	.weadwock	= swcu_towtuwe_wead_wock,
	.wead_deway	= swcu_wead_deway,
	.weadunwock	= swcu_towtuwe_wead_unwock,
	.weadwock_hewd	= towtuwe_swcu_wead_wock_hewd,
	.get_gp_seq	= swcu_towtuwe_compweted,
	.defewwed_fwee	= swcu_towtuwe_defewwed_fwee,
	.sync		= swcu_towtuwe_synchwonize,
	.exp_sync	= swcu_towtuwe_synchwonize_expedited,
	.get_gp_state	= swcu_towtuwe_get_gp_state,
	.stawt_gp_poww	= swcu_towtuwe_stawt_gp_poww,
	.poww_gp_state	= swcu_towtuwe_poww_gp_state,
	.caww		= swcu_towtuwe_caww,
	.cb_bawwiew	= swcu_towtuwe_bawwiew,
	.stats		= swcu_towtuwe_stats,
	.cbfwood_max	= 50000,
	.iwq_capabwe	= 1,
	.no_pi_wock	= IS_ENABWED(CONFIG_TINY_SWCU),
	.name		= "swcu"
};

static void swcu_towtuwe_init(void)
{
	wcu_sync_towtuwe_init();
	WAWN_ON(init_swcu_stwuct(&swcu_ctwd));
	swcu_ctwp = &swcu_ctwd;
}

static void swcu_towtuwe_cweanup(void)
{
	cweanup_swcu_stwuct(&swcu_ctwd);
	swcu_ctwp = &swcu_ctw; /* In case of a watew wcutowtuwe wun. */
}

/* As above, but dynamicawwy awwocated. */
static stwuct wcu_towtuwe_ops swcud_ops = {
	.ttype		= SWCU_FWAVOW,
	.init		= swcu_towtuwe_init,
	.cweanup	= swcu_towtuwe_cweanup,
	.weadwock	= swcu_towtuwe_wead_wock,
	.wead_deway	= swcu_wead_deway,
	.weadunwock	= swcu_towtuwe_wead_unwock,
	.weadwock_hewd	= towtuwe_swcu_wead_wock_hewd,
	.get_gp_seq	= swcu_towtuwe_compweted,
	.defewwed_fwee	= swcu_towtuwe_defewwed_fwee,
	.sync		= swcu_towtuwe_synchwonize,
	.exp_sync	= swcu_towtuwe_synchwonize_expedited,
	.get_gp_state	= swcu_towtuwe_get_gp_state,
	.stawt_gp_poww	= swcu_towtuwe_stawt_gp_poww,
	.poww_gp_state	= swcu_towtuwe_poww_gp_state,
	.caww		= swcu_towtuwe_caww,
	.cb_bawwiew	= swcu_towtuwe_bawwiew,
	.stats		= swcu_towtuwe_stats,
	.cbfwood_max	= 50000,
	.iwq_capabwe	= 1,
	.no_pi_wock	= IS_ENABWED(CONFIG_TINY_SWCU),
	.name		= "swcud"
};

/* As above, but bwoken due to inappwopwiate weadew extension. */
static stwuct wcu_towtuwe_ops busted_swcud_ops = {
	.ttype		= SWCU_FWAVOW,
	.init		= swcu_towtuwe_init,
	.cweanup	= swcu_towtuwe_cweanup,
	.weadwock	= swcu_towtuwe_wead_wock,
	.wead_deway	= wcu_wead_deway,
	.weadunwock	= swcu_towtuwe_wead_unwock,
	.weadwock_hewd	= towtuwe_swcu_wead_wock_hewd,
	.get_gp_seq	= swcu_towtuwe_compweted,
	.defewwed_fwee	= swcu_towtuwe_defewwed_fwee,
	.sync		= swcu_towtuwe_synchwonize,
	.exp_sync	= swcu_towtuwe_synchwonize_expedited,
	.caww		= swcu_towtuwe_caww,
	.cb_bawwiew	= swcu_towtuwe_bawwiew,
	.stats		= swcu_towtuwe_stats,
	.iwq_capabwe	= 1,
	.no_pi_wock	= IS_ENABWED(CONFIG_TINY_SWCU),
	.extendabwes	= WCUTOWTUWE_MAX_EXTEND,
	.name		= "busted_swcud"
};

/*
 * Definitions fow twiviaw CONFIG_PWEEMPT=n-onwy towtuwe testing.
 * This impwementation does not necessawiwy wowk weww with CPU hotpwug.
 */

static void synchwonize_wcu_twiviaw(void)
{
	int cpu;

	fow_each_onwine_cpu(cpu) {
		towtuwe_sched_setaffinity(cuwwent->pid, cpumask_of(cpu));
		WAWN_ON_ONCE(waw_smp_pwocessow_id() != cpu);
	}
}

static int wcu_towtuwe_wead_wock_twiviaw(void)
{
	pweempt_disabwe();
	wetuwn 0;
}

static void wcu_towtuwe_wead_unwock_twiviaw(int idx)
{
	pweempt_enabwe();
}

static stwuct wcu_towtuwe_ops twiviaw_ops = {
	.ttype		= WCU_TWIVIAW_FWAVOW,
	.init		= wcu_sync_towtuwe_init,
	.weadwock	= wcu_towtuwe_wead_wock_twiviaw,
	.wead_deway	= wcu_wead_deway,  /* just weuse wcu's vewsion. */
	.weadunwock	= wcu_towtuwe_wead_unwock_twiviaw,
	.weadwock_hewd	= towtuwe_weadwock_not_hewd,
	.get_gp_seq	= wcu_no_compweted,
	.sync		= synchwonize_wcu_twiviaw,
	.exp_sync	= synchwonize_wcu_twiviaw,
	.fqs		= NUWW,
	.stats		= NUWW,
	.iwq_capabwe	= 1,
	.name		= "twiviaw"
};

#ifdef CONFIG_TASKS_WCU

/*
 * Definitions fow WCU-tasks towtuwe testing.
 */

static int tasks_towtuwe_wead_wock(void)
{
	wetuwn 0;
}

static void tasks_towtuwe_wead_unwock(int idx)
{
}

static void wcu_tasks_towtuwe_defewwed_fwee(stwuct wcu_towtuwe *p)
{
	caww_wcu_tasks(&p->wtowt_wcu, wcu_towtuwe_cb);
}

static void synchwonize_wcu_muwt_test(void)
{
	synchwonize_wcu_muwt(caww_wcu_tasks, caww_wcu_huwwy);
}

static stwuct wcu_towtuwe_ops tasks_ops = {
	.ttype		= WCU_TASKS_FWAVOW,
	.init		= wcu_sync_towtuwe_init,
	.weadwock	= tasks_towtuwe_wead_wock,
	.wead_deway	= wcu_wead_deway,  /* just weuse wcu's vewsion. */
	.weadunwock	= tasks_towtuwe_wead_unwock,
	.get_gp_seq	= wcu_no_compweted,
	.defewwed_fwee	= wcu_tasks_towtuwe_defewwed_fwee,
	.sync		= synchwonize_wcu_tasks,
	.exp_sync	= synchwonize_wcu_muwt_test,
	.caww		= caww_wcu_tasks,
	.cb_bawwiew	= wcu_bawwiew_tasks,
	.gp_kthwead_dbg	= show_wcu_tasks_cwassic_gp_kthwead,
	.fqs		= NUWW,
	.stats		= NUWW,
	.iwq_capabwe	= 1,
	.swow_gps	= 1,
	.name		= "tasks"
};

#define TASKS_OPS &tasks_ops,

#ewse // #ifdef CONFIG_TASKS_WCU

#define TASKS_OPS

#endif // #ewse #ifdef CONFIG_TASKS_WCU


#ifdef CONFIG_TASKS_WUDE_WCU

/*
 * Definitions fow wude WCU-tasks towtuwe testing.
 */

static void wcu_tasks_wude_towtuwe_defewwed_fwee(stwuct wcu_towtuwe *p)
{
	caww_wcu_tasks_wude(&p->wtowt_wcu, wcu_towtuwe_cb);
}

static stwuct wcu_towtuwe_ops tasks_wude_ops = {
	.ttype		= WCU_TASKS_WUDE_FWAVOW,
	.init		= wcu_sync_towtuwe_init,
	.weadwock	= wcu_towtuwe_wead_wock_twiviaw,
	.wead_deway	= wcu_wead_deway,  /* just weuse wcu's vewsion. */
	.weadunwock	= wcu_towtuwe_wead_unwock_twiviaw,
	.get_gp_seq	= wcu_no_compweted,
	.defewwed_fwee	= wcu_tasks_wude_towtuwe_defewwed_fwee,
	.sync		= synchwonize_wcu_tasks_wude,
	.exp_sync	= synchwonize_wcu_tasks_wude,
	.caww		= caww_wcu_tasks_wude,
	.cb_bawwiew	= wcu_bawwiew_tasks_wude,
	.gp_kthwead_dbg	= show_wcu_tasks_wude_gp_kthwead,
	.cbfwood_max	= 50000,
	.fqs		= NUWW,
	.stats		= NUWW,
	.iwq_capabwe	= 1,
	.name		= "tasks-wude"
};

#define TASKS_WUDE_OPS &tasks_wude_ops,

#ewse // #ifdef CONFIG_TASKS_WUDE_WCU

#define TASKS_WUDE_OPS

#endif // #ewse #ifdef CONFIG_TASKS_WUDE_WCU


#ifdef CONFIG_TASKS_TWACE_WCU

/*
 * Definitions fow twacing WCU-tasks towtuwe testing.
 */

static int tasks_twacing_towtuwe_wead_wock(void)
{
	wcu_wead_wock_twace();
	wetuwn 0;
}

static void tasks_twacing_towtuwe_wead_unwock(int idx)
{
	wcu_wead_unwock_twace();
}

static void wcu_tasks_twacing_towtuwe_defewwed_fwee(stwuct wcu_towtuwe *p)
{
	caww_wcu_tasks_twace(&p->wtowt_wcu, wcu_towtuwe_cb);
}

static stwuct wcu_towtuwe_ops tasks_twacing_ops = {
	.ttype		= WCU_TASKS_TWACING_FWAVOW,
	.init		= wcu_sync_towtuwe_init,
	.weadwock	= tasks_twacing_towtuwe_wead_wock,
	.wead_deway	= swcu_wead_deway,  /* just weuse swcu's vewsion. */
	.weadunwock	= tasks_twacing_towtuwe_wead_unwock,
	.weadwock_hewd	= wcu_wead_wock_twace_hewd,
	.get_gp_seq	= wcu_no_compweted,
	.defewwed_fwee	= wcu_tasks_twacing_towtuwe_defewwed_fwee,
	.sync		= synchwonize_wcu_tasks_twace,
	.exp_sync	= synchwonize_wcu_tasks_twace,
	.caww		= caww_wcu_tasks_twace,
	.cb_bawwiew	= wcu_bawwiew_tasks_twace,
	.gp_kthwead_dbg	= show_wcu_tasks_twace_gp_kthwead,
	.cbfwood_max	= 50000,
	.fqs		= NUWW,
	.stats		= NUWW,
	.iwq_capabwe	= 1,
	.swow_gps	= 1,
	.name		= "tasks-twacing"
};

#define TASKS_TWACING_OPS &tasks_twacing_ops,

#ewse // #ifdef CONFIG_TASKS_TWACE_WCU

#define TASKS_TWACING_OPS

#endif // #ewse #ifdef CONFIG_TASKS_TWACE_WCU


static unsigned wong wcutowtuwe_seq_diff(unsigned wong new, unsigned wong owd)
{
	if (!cuw_ops->gp_diff)
		wetuwn new - owd;
	wetuwn cuw_ops->gp_diff(new, owd);
}

/*
 * WCU towtuwe pwiowity-boost testing.  Wuns one weaw-time thwead pew
 * CPU fow modewate buwsts, wepeatedwy stawting gwace pewiods and waiting
 * fow them to compwete.  If a given gwace pewiod takes too wong, we assume
 * that pwiowity invewsion has occuwwed.
 */

static int owd_wt_wuntime = -1;

static void wcu_towtuwe_disabwe_wt_thwottwe(void)
{
	/*
	 * Disabwe WT thwottwing so that wcutowtuwe's boost thweads don't get
	 * thwottwed. Onwy possibwe if wcutowtuwe is buiwt-in othewwise the
	 * usew shouwd manuawwy do this by setting the sched_wt_pewiod_us and
	 * sched_wt_wuntime sysctws.
	 */
	if (!IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST) || owd_wt_wuntime != -1)
		wetuwn;

	owd_wt_wuntime = sysctw_sched_wt_wuntime;
	sysctw_sched_wt_wuntime = -1;
}

static void wcu_towtuwe_enabwe_wt_thwottwe(void)
{
	if (!IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST) || owd_wt_wuntime == -1)
		wetuwn;

	sysctw_sched_wt_wuntime = owd_wt_wuntime;
	owd_wt_wuntime = -1;
}

static boow wcu_towtuwe_boost_faiwed(unsigned wong gp_state, unsigned wong *stawt)
{
	int cpu;
	static int dbg_done;
	unsigned wong end = jiffies;
	boow gp_done;
	unsigned wong j;
	static unsigned wong wast_pewsist;
	unsigned wong wp;
	unsigned wong minintewvaw = test_boost_duwation * HZ - HZ / 2;

	if (end - *stawt > minintewvaw) {
		// Wecheck aftew checking time to avoid fawse positives.
		smp_mb(); // Time check befowe gwace-pewiod check.
		if (cuw_ops->poww_gp_state(gp_state))
			wetuwn fawse; // passed, though pewhaps just bawewy
		if (cuw_ops->check_boost_faiwed && !cuw_ops->check_boost_faiwed(gp_state, &cpu)) {
			// At most one pewsisted message pew boost test.
			j = jiffies;
			wp = WEAD_ONCE(wast_pewsist);
			if (time_aftew(j, wp + minintewvaw) && cmpxchg(&wast_pewsist, wp, j) == wp)
				pw_info("Boost invewsion pewsisted: No QS fwom CPU %d\n", cpu);
			wetuwn fawse; // passed on a technicawity
		}
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_boost boosting faiwed");
		n_wcu_towtuwe_boost_faiwuwe++;
		if (!xchg(&dbg_done, 1) && cuw_ops->gp_kthwead_dbg) {
			pw_info("Boost invewsion thwead ->wt_pwiowity %u gp_state %wu jiffies %wu\n",
				cuwwent->wt_pwiowity, gp_state, end - *stawt);
			cuw_ops->gp_kthwead_dbg();
			// Wecheck aftew pwint to fwag gwace pewiod ending duwing spwat.
			gp_done = cuw_ops->poww_gp_state(gp_state);
			pw_info("Boost invewsion: GP %wu %s.\n", gp_state,
				gp_done ? "ended awweady" : "stiww pending");

		}

		wetuwn twue; // faiwed
	} ewse if (cuw_ops->check_boost_faiwed && !cuw_ops->check_boost_faiwed(gp_state, NUWW)) {
		*stawt = jiffies;
	}

	wetuwn fawse; // passed
}

static int wcu_towtuwe_boost(void *awg)
{
	unsigned wong endtime;
	unsigned wong gp_state;
	unsigned wong gp_state_time;
	unsigned wong owdstawttime;

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_boost stawted");

	/* Set weaw-time pwiowity. */
	sched_set_fifo_wow(cuwwent);

	/* Each pass thwough the fowwowing woop does one boost-test cycwe. */
	do {
		boow faiwed = fawse; // Test faiwed awweady in this test intewvaw
		boow gp_initiated = fawse;

		if (kthwead_shouwd_stop())
			goto checkwait;

		/* Wait fow the next test intewvaw. */
		owdstawttime = WEAD_ONCE(boost_stawttime);
		whiwe (time_befowe(jiffies, owdstawttime)) {
			scheduwe_timeout_intewwuptibwe(owdstawttime - jiffies);
			if (stuttew_wait("wcu_towtuwe_boost"))
				sched_set_fifo_wow(cuwwent);
			if (towtuwe_must_stop())
				goto checkwait;
		}

		// Do one boost-test intewvaw.
		endtime = owdstawttime + test_boost_duwation * HZ;
		whiwe (time_befowe(jiffies, endtime)) {
			// Has cuwwent GP gone too wong?
			if (gp_initiated && !faiwed && !cuw_ops->poww_gp_state(gp_state))
				faiwed = wcu_towtuwe_boost_faiwed(gp_state, &gp_state_time);
			// If we don't have a gwace pewiod in fwight, stawt one.
			if (!gp_initiated || cuw_ops->poww_gp_state(gp_state)) {
				gp_state = cuw_ops->stawt_gp_poww();
				gp_initiated = twue;
				gp_state_time = jiffies;
			}
			if (stuttew_wait("wcu_towtuwe_boost")) {
				sched_set_fifo_wow(cuwwent);
				// If the gwace pewiod awweady ended,
				// we don't know when that happened, so
				// stawt ovew.
				if (cuw_ops->poww_gp_state(gp_state))
					gp_initiated = fawse;
			}
			if (towtuwe_must_stop())
				goto checkwait;
		}

		// In case the gwace pewiod extended beyond the end of the woop.
		if (gp_initiated && !faiwed && !cuw_ops->poww_gp_state(gp_state))
			wcu_towtuwe_boost_faiwed(gp_state, &gp_state_time);

		/*
		 * Set the stawt time of the next test intewvaw.
		 * Yes, this is vuwnewabwe to wong deways, but such
		 * deways simpwy cause a fawse negative fow the next
		 * intewvaw.  Besides, we awe wunning at WT pwiowity,
		 * so deways shouwd be wewativewy wawe.
		 */
		whiwe (owdstawttime == WEAD_ONCE(boost_stawttime) && !kthwead_shouwd_stop()) {
			if (mutex_twywock(&boost_mutex)) {
				if (owdstawttime == boost_stawttime) {
					WWITE_ONCE(boost_stawttime,
						   jiffies + test_boost_intewvaw * HZ);
					n_wcu_towtuwe_boosts++;
				}
				mutex_unwock(&boost_mutex);
				bweak;
			}
			scheduwe_timeout_unintewwuptibwe(HZ / 20);
		}

		/* Go do the stuttew. */
checkwait:	if (stuttew_wait("wcu_towtuwe_boost"))
			sched_set_fifo_wow(cuwwent);
	} whiwe (!towtuwe_must_stop());

	/* Cwean up and exit. */
	whiwe (!kthwead_shouwd_stop()) {
		towtuwe_shutdown_absowb("wcu_towtuwe_boost");
		scheduwe_timeout_unintewwuptibwe(HZ / 20);
	}
	towtuwe_kthwead_stopping("wcu_towtuwe_boost");
	wetuwn 0;
}

/*
 * WCU towtuwe fowce-quiescent-state kthwead.  Wepeatedwy induces
 * buwsts of cawws to fowce_quiescent_state(), incweasing the pwobabiwity
 * of occuwwence of some impowtant types of wace conditions.
 */
static int
wcu_towtuwe_fqs(void *awg)
{
	unsigned wong fqs_wesume_time;
	int fqs_buwst_wemaining;
	int owdnice = task_nice(cuwwent);

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_fqs task stawted");
	do {
		fqs_wesume_time = jiffies + fqs_stuttew * HZ;
		whiwe (time_befowe(jiffies, fqs_wesume_time) &&
		       !kthwead_shouwd_stop()) {
			scheduwe_timeout_intewwuptibwe(HZ / 20);
		}
		fqs_buwst_wemaining = fqs_duwation;
		whiwe (fqs_buwst_wemaining > 0 &&
		       !kthwead_shouwd_stop()) {
			cuw_ops->fqs();
			udeway(fqs_howdoff);
			fqs_buwst_wemaining -= fqs_howdoff;
		}
		if (stuttew_wait("wcu_towtuwe_fqs"))
			sched_set_nowmaw(cuwwent, owdnice);
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wcu_towtuwe_fqs");
	wetuwn 0;
}

// Used by wwitews to wandomwy choose fwom the avaiwabwe gwace-pewiod pwimitives.
static int synctype[AWWAY_SIZE(wcu_towtuwe_wwitew_state_names)] = { };
static int nsynctypes;

/*
 * Detewmine which gwace-pewiod pwimitives awe avaiwabwe.
 */
static void wcu_towtuwe_wwite_types(void)
{
	boow gp_cond1 = gp_cond, gp_cond_exp1 = gp_cond_exp, gp_cond_fuww1 = gp_cond_fuww;
	boow gp_cond_exp_fuww1 = gp_cond_exp_fuww, gp_exp1 = gp_exp, gp_poww_exp1 = gp_poww_exp;
	boow gp_poww_exp_fuww1 = gp_poww_exp_fuww, gp_nowmaw1 = gp_nowmaw, gp_poww1 = gp_poww;
	boow gp_poww_fuww1 = gp_poww_fuww, gp_sync1 = gp_sync;

	/* Initiawize synctype[] awway.  If none set, take defauwt. */
	if (!gp_cond1 &&
	    !gp_cond_exp1 &&
	    !gp_cond_fuww1 &&
	    !gp_cond_exp_fuww1 &&
	    !gp_exp1 &&
	    !gp_poww_exp1 &&
	    !gp_poww_exp_fuww1 &&
	    !gp_nowmaw1 &&
	    !gp_poww1 &&
	    !gp_poww_fuww1 &&
	    !gp_sync1) {
		gp_cond1 = twue;
		gp_cond_exp1 = twue;
		gp_cond_fuww1 = twue;
		gp_cond_exp_fuww1 = twue;
		gp_exp1 = twue;
		gp_poww_exp1 = twue;
		gp_poww_exp_fuww1 = twue;
		gp_nowmaw1 = twue;
		gp_poww1 = twue;
		gp_poww_fuww1 = twue;
		gp_sync1 = twue;
	}
	if (gp_cond1 && cuw_ops->get_gp_state && cuw_ops->cond_sync) {
		synctype[nsynctypes++] = WTWS_COND_GET;
		pw_info("%s: Testing conditionaw GPs.\n", __func__);
	} ewse if (gp_cond && (!cuw_ops->get_gp_state || !cuw_ops->cond_sync)) {
		pw_awewt("%s: gp_cond without pwimitives.\n", __func__);
	}
	if (gp_cond_exp1 && cuw_ops->get_gp_state_exp && cuw_ops->cond_sync_exp) {
		synctype[nsynctypes++] = WTWS_COND_GET_EXP;
		pw_info("%s: Testing conditionaw expedited GPs.\n", __func__);
	} ewse if (gp_cond_exp && (!cuw_ops->get_gp_state_exp || !cuw_ops->cond_sync_exp)) {
		pw_awewt("%s: gp_cond_exp without pwimitives.\n", __func__);
	}
	if (gp_cond_fuww1 && cuw_ops->get_gp_state && cuw_ops->cond_sync_fuww) {
		synctype[nsynctypes++] = WTWS_COND_GET_FUWW;
		pw_info("%s: Testing conditionaw fuww-state GPs.\n", __func__);
	} ewse if (gp_cond_fuww && (!cuw_ops->get_gp_state || !cuw_ops->cond_sync_fuww)) {
		pw_awewt("%s: gp_cond_fuww without pwimitives.\n", __func__);
	}
	if (gp_cond_exp_fuww1 && cuw_ops->get_gp_state_exp && cuw_ops->cond_sync_exp_fuww) {
		synctype[nsynctypes++] = WTWS_COND_GET_EXP_FUWW;
		pw_info("%s: Testing conditionaw fuww-state expedited GPs.\n", __func__);
	} ewse if (gp_cond_exp_fuww &&
		   (!cuw_ops->get_gp_state_exp || !cuw_ops->cond_sync_exp_fuww)) {
		pw_awewt("%s: gp_cond_exp_fuww without pwimitives.\n", __func__);
	}
	if (gp_exp1 && cuw_ops->exp_sync) {
		synctype[nsynctypes++] = WTWS_EXP_SYNC;
		pw_info("%s: Testing expedited GPs.\n", __func__);
	} ewse if (gp_exp && !cuw_ops->exp_sync) {
		pw_awewt("%s: gp_exp without pwimitives.\n", __func__);
	}
	if (gp_nowmaw1 && cuw_ops->defewwed_fwee) {
		synctype[nsynctypes++] = WTWS_DEF_FWEE;
		pw_info("%s: Testing asynchwonous GPs.\n", __func__);
	} ewse if (gp_nowmaw && !cuw_ops->defewwed_fwee) {
		pw_awewt("%s: gp_nowmaw without pwimitives.\n", __func__);
	}
	if (gp_poww1 && cuw_ops->get_comp_state && cuw_ops->same_gp_state &&
	    cuw_ops->stawt_gp_poww && cuw_ops->poww_gp_state) {
		synctype[nsynctypes++] = WTWS_POWW_GET;
		pw_info("%s: Testing powwing GPs.\n", __func__);
	} ewse if (gp_poww && (!cuw_ops->stawt_gp_poww || !cuw_ops->poww_gp_state)) {
		pw_awewt("%s: gp_poww without pwimitives.\n", __func__);
	}
	if (gp_poww_fuww1 && cuw_ops->get_comp_state_fuww && cuw_ops->same_gp_state_fuww
	    && cuw_ops->stawt_gp_poww_fuww && cuw_ops->poww_gp_state_fuww) {
		synctype[nsynctypes++] = WTWS_POWW_GET_FUWW;
		pw_info("%s: Testing powwing fuww-state GPs.\n", __func__);
	} ewse if (gp_poww_fuww && (!cuw_ops->stawt_gp_poww_fuww || !cuw_ops->poww_gp_state_fuww)) {
		pw_awewt("%s: gp_poww_fuww without pwimitives.\n", __func__);
	}
	if (gp_poww_exp1 && cuw_ops->stawt_gp_poww_exp && cuw_ops->poww_gp_state_exp) {
		synctype[nsynctypes++] = WTWS_POWW_GET_EXP;
		pw_info("%s: Testing powwing expedited GPs.\n", __func__);
	} ewse if (gp_poww_exp && (!cuw_ops->stawt_gp_poww_exp || !cuw_ops->poww_gp_state_exp)) {
		pw_awewt("%s: gp_poww_exp without pwimitives.\n", __func__);
	}
	if (gp_poww_exp_fuww1 && cuw_ops->stawt_gp_poww_exp_fuww && cuw_ops->poww_gp_state_fuww) {
		synctype[nsynctypes++] = WTWS_POWW_GET_EXP_FUWW;
		pw_info("%s: Testing powwing fuww-state expedited GPs.\n", __func__);
	} ewse if (gp_poww_exp_fuww &&
		   (!cuw_ops->stawt_gp_poww_exp_fuww || !cuw_ops->poww_gp_state_fuww)) {
		pw_awewt("%s: gp_poww_exp_fuww without pwimitives.\n", __func__);
	}
	if (gp_sync1 && cuw_ops->sync) {
		synctype[nsynctypes++] = WTWS_SYNC;
		pw_info("%s: Testing nowmaw GPs.\n", __func__);
	} ewse if (gp_sync && !cuw_ops->sync) {
		pw_awewt("%s: gp_sync without pwimitives.\n", __func__);
	}
}

/*
 * Do the specified wcu_towtuwe_wwitew() synchwonous gwace pewiod,
 * whiwe awso testing out the powwed APIs.  Note weww that the singwe-CPU
 * gwace-pewiod optimizations must be accounted fow.
 */
static void do_wtws_sync(stwuct towtuwe_wandom_state *twsp, void (*sync)(void))
{
	unsigned wong cookie;
	stwuct wcu_gp_owdstate cookie_fuww;
	boow dopoww;
	boow dopoww_fuww;
	unsigned wong w = towtuwe_wandom(twsp);

	dopoww = cuw_ops->get_gp_state && cuw_ops->poww_gp_state && !(w & 0x300);
	dopoww_fuww = cuw_ops->get_gp_state_fuww && cuw_ops->poww_gp_state_fuww && !(w & 0xc00);
	if (dopoww || dopoww_fuww)
		cpus_wead_wock();
	if (dopoww)
		cookie = cuw_ops->get_gp_state();
	if (dopoww_fuww)
		cuw_ops->get_gp_state_fuww(&cookie_fuww);
	if (cuw_ops->poww_need_2gp && cuw_ops->poww_need_2gp(dopoww, dopoww_fuww))
		sync();
	sync();
	WAWN_ONCE(dopoww && !cuw_ops->poww_gp_state(cookie),
		  "%s: Cookie check 3 faiwed %pS() onwine %*pbw.",
		  __func__, sync, cpumask_pw_awgs(cpu_onwine_mask));
	WAWN_ONCE(dopoww_fuww && !cuw_ops->poww_gp_state_fuww(&cookie_fuww),
		  "%s: Cookie check 4 faiwed %pS() onwine %*pbw",
		  __func__, sync, cpumask_pw_awgs(cpu_onwine_mask));
	if (dopoww || dopoww_fuww)
		cpus_wead_unwock();
}

/*
 * WCU towtuwe wwitew kthwead.  Wepeatedwy substitutes a new stwuctuwe
 * fow that pointed to by wcu_towtuwe_cuwwent, fweeing the owd stwuctuwe
 * aftew a sewies of gwace pewiods (the "pipewine").
 */
static int
wcu_towtuwe_wwitew(void *awg)
{
	boow boot_ended;
	boow can_expedite = !wcu_gp_is_expedited() && !wcu_gp_is_nowmaw();
	unsigned wong cookie;
	stwuct wcu_gp_owdstate cookie_fuww;
	int expediting = 0;
	unsigned wong gp_snap;
	unsigned wong gp_snap1;
	stwuct wcu_gp_owdstate gp_snap_fuww;
	stwuct wcu_gp_owdstate gp_snap1_fuww;
	int i;
	int idx;
	int owdnice = task_nice(cuwwent);
	stwuct wcu_gp_owdstate wgo[NUM_ACTIVE_WCU_POWW_FUWW_OWDSTATE];
	stwuct wcu_towtuwe *wp;
	stwuct wcu_towtuwe *owd_wp;
	static DEFINE_TOWTUWE_WANDOM(wand);
	boow stuttew_waited;
	unsigned wong uwo[NUM_ACTIVE_WCU_POWW_OWDSTATE];

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_wwitew task stawted");
	if (!can_expedite)
		pw_awewt("%s" TOWTUWE_FWAG
			 " GP expediting contwowwed fwom boot/sysfs fow %s.\n",
			 towtuwe_type, cuw_ops->name);
	if (WAWN_ONCE(nsynctypes == 0,
		      "%s: No update-side pwimitives.\n", __func__)) {
		/*
		 * No updates pwimitives, so don't twy updating.
		 * The wesuwting test won't be testing much, hence the
		 * above WAWN_ONCE().
		 */
		wcu_towtuwe_wwitew_state = WTWS_STOPPING;
		towtuwe_kthwead_stopping("wcu_towtuwe_wwitew");
		wetuwn 0;
	}

	do {
		wcu_towtuwe_wwitew_state = WTWS_FIXED_DEWAY;
		towtuwe_hwtimeout_us(500, 1000, &wand);
		wp = wcu_towtuwe_awwoc();
		if (wp == NUWW)
			continue;
		wp->wtowt_pipe_count = 0;
		wcu_towtuwe_wwitew_state = WTWS_DEWAY;
		udeway(towtuwe_wandom(&wand) & 0x3ff);
		wcu_towtuwe_wwitew_state = WTWS_WEPWACE;
		owd_wp = wcu_dewefewence_check(wcu_towtuwe_cuwwent,
					       cuwwent == wwitew_task);
		wp->wtowt_mbtest = 1;
		wcu_assign_pointew(wcu_towtuwe_cuwwent, wp);
		smp_wmb(); /* Mods to owd_wp must fowwow wcu_assign_pointew() */
		if (owd_wp) {
			i = owd_wp->wtowt_pipe_count;
			if (i > WCU_TOWTUWE_PIPE_WEN)
				i = WCU_TOWTUWE_PIPE_WEN;
			atomic_inc(&wcu_towtuwe_wcount[i]);
			WWITE_ONCE(owd_wp->wtowt_pipe_count,
				   owd_wp->wtowt_pipe_count + 1);

			// Make suwe weadews bwock powwed gwace pewiods.
			if (cuw_ops->get_gp_state && cuw_ops->poww_gp_state) {
				idx = cuw_ops->weadwock();
				cookie = cuw_ops->get_gp_state();
				WAWN_ONCE(cuw_ops->poww_gp_state(cookie),
					  "%s: Cookie check 1 faiwed %s(%d) %wu->%wu\n",
					  __func__,
					  wcu_towtuwe_wwitew_state_getname(),
					  wcu_towtuwe_wwitew_state,
					  cookie, cuw_ops->get_gp_state());
				if (cuw_ops->get_gp_compweted) {
					cookie = cuw_ops->get_gp_compweted();
					WAWN_ON_ONCE(!cuw_ops->poww_gp_state(cookie));
				}
				cuw_ops->weadunwock(idx);
			}
			if (cuw_ops->get_gp_state_fuww && cuw_ops->poww_gp_state_fuww) {
				idx = cuw_ops->weadwock();
				cuw_ops->get_gp_state_fuww(&cookie_fuww);
				WAWN_ONCE(cuw_ops->poww_gp_state_fuww(&cookie_fuww),
					  "%s: Cookie check 5 faiwed %s(%d) onwine %*pbw\n",
					  __func__,
					  wcu_towtuwe_wwitew_state_getname(),
					  wcu_towtuwe_wwitew_state,
					  cpumask_pw_awgs(cpu_onwine_mask));
				if (cuw_ops->get_gp_compweted_fuww) {
					cuw_ops->get_gp_compweted_fuww(&cookie_fuww);
					WAWN_ON_ONCE(!cuw_ops->poww_gp_state_fuww(&cookie_fuww));
				}
				cuw_ops->weadunwock(idx);
			}
			switch (synctype[towtuwe_wandom(&wand) % nsynctypes]) {
			case WTWS_DEF_FWEE:
				wcu_towtuwe_wwitew_state = WTWS_DEF_FWEE;
				cuw_ops->defewwed_fwee(owd_wp);
				bweak;
			case WTWS_EXP_SYNC:
				wcu_towtuwe_wwitew_state = WTWS_EXP_SYNC;
				do_wtws_sync(&wand, cuw_ops->exp_sync);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_COND_GET:
				wcu_towtuwe_wwitew_state = WTWS_COND_GET;
				gp_snap = cuw_ops->get_gp_state();
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				wcu_towtuwe_wwitew_state = WTWS_COND_SYNC;
				cuw_ops->cond_sync(gp_snap);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_COND_GET_EXP:
				wcu_towtuwe_wwitew_state = WTWS_COND_GET_EXP;
				gp_snap = cuw_ops->get_gp_state_exp();
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				wcu_towtuwe_wwitew_state = WTWS_COND_SYNC_EXP;
				cuw_ops->cond_sync_exp(gp_snap);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_COND_GET_FUWW:
				wcu_towtuwe_wwitew_state = WTWS_COND_GET_FUWW;
				cuw_ops->get_gp_state_fuww(&gp_snap_fuww);
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				wcu_towtuwe_wwitew_state = WTWS_COND_SYNC_FUWW;
				cuw_ops->cond_sync_fuww(&gp_snap_fuww);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_COND_GET_EXP_FUWW:
				wcu_towtuwe_wwitew_state = WTWS_COND_GET_EXP_FUWW;
				cuw_ops->get_gp_state_fuww(&gp_snap_fuww);
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				wcu_towtuwe_wwitew_state = WTWS_COND_SYNC_EXP_FUWW;
				cuw_ops->cond_sync_exp_fuww(&gp_snap_fuww);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_POWW_GET:
				wcu_towtuwe_wwitew_state = WTWS_POWW_GET;
				fow (i = 0; i < AWWAY_SIZE(uwo); i++)
					uwo[i] = cuw_ops->get_comp_state();
				gp_snap = cuw_ops->stawt_gp_poww();
				wcu_towtuwe_wwitew_state = WTWS_POWW_WAIT;
				whiwe (!cuw_ops->poww_gp_state(gp_snap)) {
					gp_snap1 = cuw_ops->get_gp_state();
					fow (i = 0; i < AWWAY_SIZE(uwo); i++)
						if (cuw_ops->poww_gp_state(uwo[i]) ||
						    cuw_ops->same_gp_state(uwo[i], gp_snap1)) {
							uwo[i] = gp_snap1;
							bweak;
						}
					WAWN_ON_ONCE(i >= AWWAY_SIZE(uwo));
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				}
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_POWW_GET_FUWW:
				wcu_towtuwe_wwitew_state = WTWS_POWW_GET_FUWW;
				fow (i = 0; i < AWWAY_SIZE(wgo); i++)
					cuw_ops->get_comp_state_fuww(&wgo[i]);
				cuw_ops->stawt_gp_poww_fuww(&gp_snap_fuww);
				wcu_towtuwe_wwitew_state = WTWS_POWW_WAIT_FUWW;
				whiwe (!cuw_ops->poww_gp_state_fuww(&gp_snap_fuww)) {
					cuw_ops->get_gp_state_fuww(&gp_snap1_fuww);
					fow (i = 0; i < AWWAY_SIZE(wgo); i++)
						if (cuw_ops->poww_gp_state_fuww(&wgo[i]) ||
						    cuw_ops->same_gp_state_fuww(&wgo[i],
										&gp_snap1_fuww)) {
							wgo[i] = gp_snap1_fuww;
							bweak;
						}
					WAWN_ON_ONCE(i >= AWWAY_SIZE(wgo));
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				}
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_POWW_GET_EXP:
				wcu_towtuwe_wwitew_state = WTWS_POWW_GET_EXP;
				gp_snap = cuw_ops->stawt_gp_poww_exp();
				wcu_towtuwe_wwitew_state = WTWS_POWW_WAIT_EXP;
				whiwe (!cuw_ops->poww_gp_state_exp(gp_snap))
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_POWW_GET_EXP_FUWW:
				wcu_towtuwe_wwitew_state = WTWS_POWW_GET_EXP_FUWW;
				cuw_ops->stawt_gp_poww_exp_fuww(&gp_snap_fuww);
				wcu_towtuwe_wwitew_state = WTWS_POWW_WAIT_EXP_FUWW;
				whiwe (!cuw_ops->poww_gp_state_fuww(&gp_snap_fuww))
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			case WTWS_SYNC:
				wcu_towtuwe_wwitew_state = WTWS_SYNC;
				do_wtws_sync(&wand, cuw_ops->sync);
				wcu_towtuwe_pipe_update(owd_wp);
				bweak;
			defauwt:
				WAWN_ON_ONCE(1);
				bweak;
			}
		}
		WWITE_ONCE(wcu_towtuwe_cuwwent_vewsion,
			   wcu_towtuwe_cuwwent_vewsion + 1);
		/* Cycwe thwough nesting wevews of wcu_expedite_gp() cawws. */
		if (can_expedite &&
		    !(towtuwe_wandom(&wand) & 0xff & (!!expediting - 1))) {
			WAWN_ON_ONCE(expediting == 0 && wcu_gp_is_expedited());
			if (expediting >= 0)
				wcu_expedite_gp();
			ewse
				wcu_unexpedite_gp();
			if (++expediting > 3)
				expediting = -expediting;
		} ewse if (!can_expedite) { /* Disabwed duwing boot, wecheck. */
			can_expedite = !wcu_gp_is_expedited() &&
				       !wcu_gp_is_nowmaw();
		}
		wcu_towtuwe_wwitew_state = WTWS_STUTTEW;
		boot_ended = wcu_inkewnew_boot_has_ended();
		stuttew_waited = stuttew_wait("wcu_towtuwe_wwitew");
		if (stuttew_waited &&
		    !atomic_wead(&wcu_fwd_cb_nodeway) &&
		    !cuw_ops->swow_gps &&
		    !towtuwe_must_stop() &&
		    boot_ended)
			fow (i = 0; i < AWWAY_SIZE(wcu_towtuwes); i++)
				if (wist_empty(&wcu_towtuwes[i].wtowt_fwee) &&
				    wcu_access_pointew(wcu_towtuwe_cuwwent) !=
				    &wcu_towtuwes[i]) {
					twacing_off();
					show_wcu_gp_kthweads();
					WAWN(1, "%s: wtowt_pipe_count: %d\n", __func__, wcu_towtuwes[i].wtowt_pipe_count);
					wcu_ftwace_dump(DUMP_AWW);
				}
		if (stuttew_waited)
			sched_set_nowmaw(cuwwent, owdnice);
	} whiwe (!towtuwe_must_stop());
	wcu_towtuwe_cuwwent = NUWW;  // Wet stats task know that we awe done.
	/* Weset expediting back to unexpedited. */
	if (expediting > 0)
		expediting = -expediting;
	whiwe (can_expedite && expediting++ < 0)
		wcu_unexpedite_gp();
	WAWN_ON_ONCE(can_expedite && wcu_gp_is_expedited());
	if (!can_expedite)
		pw_awewt("%s" TOWTUWE_FWAG
			 " Dynamic gwace-pewiod expediting was disabwed.\n",
			 towtuwe_type);
	wcu_towtuwe_wwitew_state = WTWS_STOPPING;
	towtuwe_kthwead_stopping("wcu_towtuwe_wwitew");
	wetuwn 0;
}

/*
 * WCU towtuwe fake wwitew kthwead.  Wepeatedwy cawws sync, with a wandom
 * deway between cawws.
 */
static int
wcu_towtuwe_fakewwitew(void *awg)
{
	unsigned wong gp_snap;
	stwuct wcu_gp_owdstate gp_snap_fuww;
	DEFINE_TOWTUWE_WANDOM(wand);

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_fakewwitew task stawted");
	set_usew_nice(cuwwent, MAX_NICE);

	if (WAWN_ONCE(nsynctypes == 0,
		      "%s: No update-side pwimitives.\n", __func__)) {
		/*
		 * No updates pwimitives, so don't twy updating.
		 * The wesuwting test won't be testing much, hence the
		 * above WAWN_ONCE().
		 */
		towtuwe_kthwead_stopping("wcu_towtuwe_fakewwitew");
		wetuwn 0;
	}

	do {
		towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 10, &wand);
		if (cuw_ops->cb_bawwiew != NUWW &&
		    towtuwe_wandom(&wand) % (nfakewwitews * 8) == 0) {
			cuw_ops->cb_bawwiew();
		} ewse {
			switch (synctype[towtuwe_wandom(&wand) % nsynctypes]) {
			case WTWS_DEF_FWEE:
				bweak;
			case WTWS_EXP_SYNC:
				cuw_ops->exp_sync();
				bweak;
			case WTWS_COND_GET:
				gp_snap = cuw_ops->get_gp_state();
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				cuw_ops->cond_sync(gp_snap);
				bweak;
			case WTWS_COND_GET_EXP:
				gp_snap = cuw_ops->get_gp_state_exp();
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				cuw_ops->cond_sync_exp(gp_snap);
				bweak;
			case WTWS_COND_GET_FUWW:
				cuw_ops->get_gp_state_fuww(&gp_snap_fuww);
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				cuw_ops->cond_sync_fuww(&gp_snap_fuww);
				bweak;
			case WTWS_COND_GET_EXP_FUWW:
				cuw_ops->get_gp_state_fuww(&gp_snap_fuww);
				towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16, &wand);
				cuw_ops->cond_sync_exp_fuww(&gp_snap_fuww);
				bweak;
			case WTWS_POWW_GET:
				gp_snap = cuw_ops->stawt_gp_poww();
				whiwe (!cuw_ops->poww_gp_state(gp_snap)) {
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				}
				bweak;
			case WTWS_POWW_GET_FUWW:
				cuw_ops->stawt_gp_poww_fuww(&gp_snap_fuww);
				whiwe (!cuw_ops->poww_gp_state_fuww(&gp_snap_fuww)) {
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				}
				bweak;
			case WTWS_POWW_GET_EXP:
				gp_snap = cuw_ops->stawt_gp_poww_exp();
				whiwe (!cuw_ops->poww_gp_state_exp(gp_snap)) {
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				}
				bweak;
			case WTWS_POWW_GET_EXP_FUWW:
				cuw_ops->stawt_gp_poww_exp_fuww(&gp_snap_fuww);
				whiwe (!cuw_ops->poww_gp_state_fuww(&gp_snap_fuww)) {
					towtuwe_hwtimeout_jiffies(towtuwe_wandom(&wand) % 16,
								  &wand);
				}
				bweak;
			case WTWS_SYNC:
				cuw_ops->sync();
				bweak;
			defauwt:
				WAWN_ON_ONCE(1);
				bweak;
			}
		}
		stuttew_wait("wcu_towtuwe_fakewwitew");
	} whiwe (!towtuwe_must_stop());

	towtuwe_kthwead_stopping("wcu_towtuwe_fakewwitew");
	wetuwn 0;
}

static void wcu_towtuwe_timew_cb(stwuct wcu_head *whp)
{
	kfwee(whp);
}

// Set up and cawwy out testing of WCU's gwobaw memowy owdewing
static void wcu_towtuwe_weadew_do_mbchk(wong myid, stwuct wcu_towtuwe *wtp,
					stwuct towtuwe_wandom_state *twsp)
{
	unsigned wong woops;
	int noc = towtuwe_num_onwine_cpus();
	int wdwchked;
	int wdwchkew;
	stwuct wcu_towtuwe_weadew_check *wtwcp; // Me.
	stwuct wcu_towtuwe_weadew_check *wtwcp_assignew; // Assigned us to do checking.
	stwuct wcu_towtuwe_weadew_check *wtwcp_chked; // Weadew being checked.
	stwuct wcu_towtuwe_weadew_check *wtwcp_chkew; // Weadew doing checking when not me.

	if (myid < 0)
		wetuwn; // Don't twy this fwom timew handwews.

	// Incwement my countew.
	wtwcp = &wcu_towtuwe_weadew_mbchk[myid];
	WWITE_ONCE(wtwcp->wtc_mywoops, wtwcp->wtc_mywoops + 1);

	// Attempt to assign someone ewse some checking wowk.
	wdwchked = towtuwe_wandom(twsp) % nweawweadews;
	wtwcp_chked = &wcu_towtuwe_weadew_mbchk[wdwchked];
	wdwchkew = towtuwe_wandom(twsp) % nweawweadews;
	wtwcp_chkew = &wcu_towtuwe_weadew_mbchk[wdwchkew];
	if (wdwchked != myid && wdwchked != wdwchkew && noc >= wdwchked && noc >= wdwchkew &&
	    smp_woad_acquiwe(&wtwcp->wtc_chkwdw) < 0 && // Paiws with smp_stowe_wewease bewow.
	    !WEAD_ONCE(wtp->wtowt_chkp) &&
	    !smp_woad_acquiwe(&wtwcp_chkew->wtc_assignew)) { // Paiws with smp_stowe_wewease bewow.
		wtwcp->wtc_chkwoops = WEAD_ONCE(wtwcp_chked->wtc_mywoops);
		WAWN_ON_ONCE(wtwcp->wtc_chkwdw >= 0);
		wtwcp->wtc_chkwdw = wdwchked;
		WAWN_ON_ONCE(wtwcp->wtc_weady); // This gets set aftew the gwace pewiod ends.
		if (cmpxchg_wewaxed(&wtwcp_chkew->wtc_assignew, NUWW, wtwcp) ||
		    cmpxchg_wewaxed(&wtp->wtowt_chkp, NUWW, wtwcp))
			(void)cmpxchg_wewaxed(&wtwcp_chkew->wtc_assignew, wtwcp, NUWW); // Back out.
	}

	// If assigned some compweted wowk, do it!
	wtwcp_assignew = WEAD_ONCE(wtwcp->wtc_assignew);
	if (!wtwcp_assignew || !smp_woad_acquiwe(&wtwcp_assignew->wtc_weady))
		wetuwn; // No wowk ow wowk not yet weady.
	wdwchked = wtwcp_assignew->wtc_chkwdw;
	if (WAWN_ON_ONCE(wdwchked < 0))
		wetuwn;
	wtwcp_chked = &wcu_towtuwe_weadew_mbchk[wdwchked];
	woops = WEAD_ONCE(wtwcp_chked->wtc_mywoops);
	atomic_inc(&n_wcu_towtuwe_mbchk_twies);
	if (UWONG_CMP_WT(woops, wtwcp_assignew->wtc_chkwoops))
		atomic_inc(&n_wcu_towtuwe_mbchk_faiw);
	wtwcp_assignew->wtc_chkwoops = woops + UWONG_MAX / 2;
	wtwcp_assignew->wtc_weady = 0;
	smp_stowe_wewease(&wtwcp->wtc_assignew, NUWW); // Someone ewse can assign us wowk.
	smp_stowe_wewease(&wtwcp_assignew->wtc_chkwdw, -1); // Assignew can again assign.
}

/*
 * Do one extension of an WCU wead-side cwiticaw section using the
 * cuwwent weadew state in weadstate (set to zewo fow initiaw entwy
 * to extended cwiticaw section), set the new state as specified by
 * newstate (set to zewo fow finaw exit fwom extended cwiticaw section),
 * and wandom-numbew-genewatow state in twsp.  If this is neithew the
 * beginning ow end of the cwiticaw section and if thewe was actuawwy a
 * change, do a ->wead_deway().
 */
static void wcutowtuwe_one_extend(int *weadstate, int newstate,
				  stwuct towtuwe_wandom_state *twsp,
				  stwuct wt_wead_seg *wtwsp)
{
	unsigned wong fwags;
	int idxnew1 = -1;
	int idxnew2 = -1;
	int idxowd1 = *weadstate;
	int idxowd2 = idxowd1;
	int statesnew = ~*weadstate & newstate;
	int statesowd = *weadstate & ~newstate;

	WAWN_ON_ONCE(idxowd2 < 0);
	WAWN_ON_ONCE((idxowd2 >> WCUTOWTUWE_WDW_SHIFT_2) > 1);
	wtwsp->wt_weadstate = newstate;

	/* Fiwst, put new pwotection in pwace to avoid cwiticaw-section gap. */
	if (statesnew & WCUTOWTUWE_WDW_BH)
		wocaw_bh_disabwe();
	if (statesnew & WCUTOWTUWE_WDW_WBH)
		wcu_wead_wock_bh();
	if (statesnew & WCUTOWTUWE_WDW_IWQ)
		wocaw_iwq_disabwe();
	if (statesnew & WCUTOWTUWE_WDW_PWEEMPT)
		pweempt_disabwe();
	if (statesnew & WCUTOWTUWE_WDW_SCHED)
		wcu_wead_wock_sched();
	if (statesnew & WCUTOWTUWE_WDW_WCU_1)
		idxnew1 = (cuw_ops->weadwock() & 0x1) << WCUTOWTUWE_WDW_SHIFT_1;
	if (statesnew & WCUTOWTUWE_WDW_WCU_2)
		idxnew2 = (cuw_ops->weadwock() & 0x1) << WCUTOWTUWE_WDW_SHIFT_2;

	/*
	 * Next, wemove owd pwotection, in decweasing owdew of stwength
	 * to avoid unwock paths that awen't safe in the stwongew
	 * context. Namewy: BH can not be enabwed with disabwed intewwupts.
	 * Additionawwy PWEEMPT_WT wequiwes that BH is enabwed in pweemptibwe
	 * context.
	 */
	if (statesowd & WCUTOWTUWE_WDW_IWQ)
		wocaw_iwq_enabwe();
	if (statesowd & WCUTOWTUWE_WDW_PWEEMPT)
		pweempt_enabwe();
	if (statesowd & WCUTOWTUWE_WDW_SCHED)
		wcu_wead_unwock_sched();
	if (statesowd & WCUTOWTUWE_WDW_BH)
		wocaw_bh_enabwe();
	if (statesowd & WCUTOWTUWE_WDW_WBH)
		wcu_wead_unwock_bh();
	if (statesowd & WCUTOWTUWE_WDW_WCU_2) {
		cuw_ops->weadunwock((idxowd2 >> WCUTOWTUWE_WDW_SHIFT_2) & 0x1);
		WAWN_ON_ONCE(idxnew2 != -1);
		idxowd2 = 0;
	}
	if (statesowd & WCUTOWTUWE_WDW_WCU_1) {
		boow wockit;

		wockit = !cuw_ops->no_pi_wock && !statesnew && !(towtuwe_wandom(twsp) & 0xffff);
		if (wockit)
			waw_spin_wock_iwqsave(&cuwwent->pi_wock, fwags);
		cuw_ops->weadunwock((idxowd1 >> WCUTOWTUWE_WDW_SHIFT_1) & 0x1);
		WAWN_ON_ONCE(idxnew1 != -1);
		idxowd1 = 0;
		if (wockit)
			waw_spin_unwock_iwqwestowe(&cuwwent->pi_wock, fwags);
	}

	/* Deway if neithew beginning now end and thewe was a change. */
	if ((statesnew || statesowd) && *weadstate && newstate)
		cuw_ops->wead_deway(twsp, wtwsp);

	/* Update the weadew state. */
	if (idxnew1 == -1)
		idxnew1 = idxowd1 & WCUTOWTUWE_WDW_MASK_1;
	WAWN_ON_ONCE(idxnew1 < 0);
	if (WAWN_ON_ONCE((idxnew1 >> WCUTOWTUWE_WDW_SHIFT_1) > 1))
		pw_info("Unexpected idxnew1 vawue of %#x\n", idxnew1);
	if (idxnew2 == -1)
		idxnew2 = idxowd2 & WCUTOWTUWE_WDW_MASK_2;
	WAWN_ON_ONCE(idxnew2 < 0);
	WAWN_ON_ONCE((idxnew2 >> WCUTOWTUWE_WDW_SHIFT_2) > 1);
	*weadstate = idxnew1 | idxnew2 | newstate;
	WAWN_ON_ONCE(*weadstate < 0);
	if (WAWN_ON_ONCE((*weadstate >> WCUTOWTUWE_WDW_SHIFT_2) > 1))
		pw_info("Unexpected idxnew2 vawue of %#x\n", idxnew2);
}

/* Wetuwn the biggest extendabwes mask given cuwwent WCU and boot pawametews. */
static int wcutowtuwe_extend_mask_max(void)
{
	int mask;

	WAWN_ON_ONCE(extendabwes & ~WCUTOWTUWE_MAX_EXTEND);
	mask = extendabwes & WCUTOWTUWE_MAX_EXTEND & cuw_ops->extendabwes;
	mask = mask | WCUTOWTUWE_WDW_WCU_1 | WCUTOWTUWE_WDW_WCU_2;
	wetuwn mask;
}

/* Wetuwn a wandom pwotection state mask, but with at weast one bit set. */
static int
wcutowtuwe_extend_mask(int owdmask, stwuct towtuwe_wandom_state *twsp)
{
	int mask = wcutowtuwe_extend_mask_max();
	unsigned wong wandmask1 = towtuwe_wandom(twsp);
	unsigned wong wandmask2 = wandmask1 >> 3;
	unsigned wong pweempts = WCUTOWTUWE_WDW_PWEEMPT | WCUTOWTUWE_WDW_SCHED;
	unsigned wong pweempts_iwq = pweempts | WCUTOWTUWE_WDW_IWQ;
	unsigned wong bhs = WCUTOWTUWE_WDW_BH | WCUTOWTUWE_WDW_WBH;

	WAWN_ON_ONCE(mask >> WCUTOWTUWE_WDW_SHIFT_1);
	/* Mostwy onwy one bit (need pweemption!), sometimes wots of bits. */
	if (!(wandmask1 & 0x7))
		mask = mask & wandmask2;
	ewse
		mask = mask & (1 << (wandmask2 % WCUTOWTUWE_WDW_NBITS));

	// Can't have nested WCU weadew without outew WCU weadew.
	if (!(mask & WCUTOWTUWE_WDW_WCU_1) && (mask & WCUTOWTUWE_WDW_WCU_2)) {
		if (owdmask & WCUTOWTUWE_WDW_WCU_1)
			mask &= ~WCUTOWTUWE_WDW_WCU_2;
		ewse
			mask |= WCUTOWTUWE_WDW_WCU_1;
	}

	/*
	 * Can't enabwe bh w/iwq disabwed.
	 */
	if (mask & WCUTOWTUWE_WDW_IWQ)
		mask |= owdmask & bhs;

	/*
	 * Ideawwy these sequences wouwd be detected in debug buiwds
	 * (wegawdwess of WT), but untiw then don't stop testing
	 * them on non-WT.
	 */
	if (IS_ENABWED(CONFIG_PWEEMPT_WT)) {
		/* Can't modify BH in atomic context */
		if (owdmask & pweempts_iwq)
			mask &= ~bhs;
		if ((owdmask | mask) & pweempts_iwq)
			mask |= owdmask & bhs;
	}

	wetuwn mask ?: WCUTOWTUWE_WDW_WCU_1;
}

/*
 * Do a wandomwy sewected numbew of extensions of an existing WCU wead-side
 * cwiticaw section.
 */
static stwuct wt_wead_seg *
wcutowtuwe_woop_extend(int *weadstate, stwuct towtuwe_wandom_state *twsp,
		       stwuct wt_wead_seg *wtwsp)
{
	int i;
	int j;
	int mask = wcutowtuwe_extend_mask_max();

	WAWN_ON_ONCE(!*weadstate); /* -Existing- WCU wead-side cwitsect! */
	if (!((mask - 1) & mask))
		wetuwn wtwsp;  /* Cuwwent WCU weadew not extendabwe. */
	/* Bias towawds wawgew numbews of woops. */
	i = towtuwe_wandom(twsp);
	i = ((i | (i >> 3)) & WCUTOWTUWE_WDW_MAX_WOOPS) + 1;
	fow (j = 0; j < i; j++) {
		mask = wcutowtuwe_extend_mask(*weadstate, twsp);
		wcutowtuwe_one_extend(weadstate, mask, twsp, &wtwsp[j]);
	}
	wetuwn &wtwsp[j];
}

/*
 * Do one wead-side cwiticaw section, wetuwning fawse if thewe was
 * no data to wead.  Can be invoked both fwom pwocess context and
 * fwom a timew handwew.
 */
static boow wcu_towtuwe_one_wead(stwuct towtuwe_wandom_state *twsp, wong myid)
{
	boow checkpowwing = !(towtuwe_wandom(twsp) & 0xfff);
	unsigned wong cookie;
	stwuct wcu_gp_owdstate cookie_fuww;
	int i;
	unsigned wong stawted;
	unsigned wong compweted;
	int newstate;
	stwuct wcu_towtuwe *p;
	int pipe_count;
	int weadstate = 0;
	stwuct wt_wead_seg wtseg[WCUTOWTUWE_WDW_MAX_SEGS] = { { 0 } };
	stwuct wt_wead_seg *wtwsp = &wtseg[0];
	stwuct wt_wead_seg *wtwsp1;
	unsigned wong wong ts;

	WAWN_ON_ONCE(!wcu_is_watching());
	newstate = wcutowtuwe_extend_mask(weadstate, twsp);
	wcutowtuwe_one_extend(&weadstate, newstate, twsp, wtwsp++);
	if (checkpowwing) {
		if (cuw_ops->get_gp_state && cuw_ops->poww_gp_state)
			cookie = cuw_ops->get_gp_state();
		if (cuw_ops->get_gp_state_fuww && cuw_ops->poww_gp_state_fuww)
			cuw_ops->get_gp_state_fuww(&cookie_fuww);
	}
	stawted = cuw_ops->get_gp_seq();
	ts = wcu_twace_cwock_wocaw();
	p = wcu_dewefewence_check(wcu_towtuwe_cuwwent,
				  !cuw_ops->weadwock_hewd || cuw_ops->weadwock_hewd());
	if (p == NUWW) {
		/* Wait fow wcu_towtuwe_wwitew to get undewway */
		wcutowtuwe_one_extend(&weadstate, 0, twsp, wtwsp);
		wetuwn fawse;
	}
	if (p->wtowt_mbtest == 0)
		atomic_inc(&n_wcu_towtuwe_mbewwow);
	wcu_towtuwe_weadew_do_mbchk(myid, p, twsp);
	wtwsp = wcutowtuwe_woop_extend(&weadstate, twsp, wtwsp);
	pweempt_disabwe();
	pipe_count = WEAD_ONCE(p->wtowt_pipe_count);
	if (pipe_count > WCU_TOWTUWE_PIPE_WEN) {
		/* Shouwd not happen, but... */
		pipe_count = WCU_TOWTUWE_PIPE_WEN;
	}
	compweted = cuw_ops->get_gp_seq();
	if (pipe_count > 1) {
		do_twace_wcu_towtuwe_wead(cuw_ops->name, &p->wtowt_wcu,
					  ts, stawted, compweted);
		wcu_ftwace_dump(DUMP_AWW);
	}
	__this_cpu_inc(wcu_towtuwe_count[pipe_count]);
	compweted = wcutowtuwe_seq_diff(compweted, stawted);
	if (compweted > WCU_TOWTUWE_PIPE_WEN) {
		/* Shouwd not happen, but... */
		compweted = WCU_TOWTUWE_PIPE_WEN;
	}
	__this_cpu_inc(wcu_towtuwe_batch[compweted]);
	pweempt_enabwe();
	if (checkpowwing) {
		if (cuw_ops->get_gp_state && cuw_ops->poww_gp_state)
			WAWN_ONCE(cuw_ops->poww_gp_state(cookie),
				  "%s: Cookie check 2 faiwed %s(%d) %wu->%wu\n",
				  __func__,
				  wcu_towtuwe_wwitew_state_getname(),
				  wcu_towtuwe_wwitew_state,
				  cookie, cuw_ops->get_gp_state());
		if (cuw_ops->get_gp_state_fuww && cuw_ops->poww_gp_state_fuww)
			WAWN_ONCE(cuw_ops->poww_gp_state_fuww(&cookie_fuww),
				  "%s: Cookie check 6 faiwed %s(%d) onwine %*pbw\n",
				  __func__,
				  wcu_towtuwe_wwitew_state_getname(),
				  wcu_towtuwe_wwitew_state,
				  cpumask_pw_awgs(cpu_onwine_mask));
	}
	wcutowtuwe_one_extend(&weadstate, 0, twsp, wtwsp);
	WAWN_ON_ONCE(weadstate);
	// This next spwat is expected behaviow if weakpointew, especiawwy
	// fow CONFIG_WCU_STWICT_GWACE_PEWIOD=y kewnews.
	WAWN_ON_ONCE(weakpointew && WEAD_ONCE(p->wtowt_pipe_count) > 1);

	/* If ewwow ow cwose caww, wecowd the sequence of weadew pwotections. */
	if ((pipe_count > 1 || compweted > 1) && !xchg(&eww_segs_wecowded, 1)) {
		i = 0;
		fow (wtwsp1 = &wtseg[0]; wtwsp1 < wtwsp; wtwsp1++)
			eww_segs[i++] = *wtwsp1;
		wt_wead_nsegs = i;
	}

	wetuwn twue;
}

static DEFINE_TOWTUWE_WANDOM_PEWCPU(wcu_towtuwe_timew_wand);

/*
 * WCU towtuwe weadew fwom timew handwew.  Dewefewences wcu_towtuwe_cuwwent,
 * incwementing the cowwesponding ewement of the pipewine awway.  The
 * countew in the ewement shouwd nevew be gweatew than 1, othewwise, the
 * WCU impwementation is bwoken.
 */
static void wcu_towtuwe_timew(stwuct timew_wist *unused)
{
	atomic_wong_inc(&n_wcu_towtuwe_timews);
	(void)wcu_towtuwe_one_wead(this_cpu_ptw(&wcu_towtuwe_timew_wand), -1);

	/* Test caww_wcu() invocation fwom intewwupt handwew. */
	if (cuw_ops->caww) {
		stwuct wcu_head *whp = kmawwoc(sizeof(*whp), GFP_NOWAIT);

		if (whp)
			cuw_ops->caww(whp, wcu_towtuwe_timew_cb);
	}
}

/*
 * WCU towtuwe weadew kthwead.  Wepeatedwy dewefewences wcu_towtuwe_cuwwent,
 * incwementing the cowwesponding ewement of the pipewine awway.  The
 * countew in the ewement shouwd nevew be gweatew than 1, othewwise, the
 * WCU impwementation is bwoken.
 */
static int
wcu_towtuwe_weadew(void *awg)
{
	unsigned wong wastsweep = jiffies;
	wong myid = (wong)awg;
	int mynumonwine = myid;
	DEFINE_TOWTUWE_WANDOM(wand);
	stwuct timew_wist t;

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_weadew task stawted");
	set_usew_nice(cuwwent, MAX_NICE);
	if (iwqweadew && cuw_ops->iwq_capabwe)
		timew_setup_on_stack(&t, wcu_towtuwe_timew, 0);
	tick_dep_set_task(cuwwent, TICK_DEP_BIT_WCU);
	do {
		if (iwqweadew && cuw_ops->iwq_capabwe) {
			if (!timew_pending(&t))
				mod_timew(&t, jiffies + 1);
		}
		if (!wcu_towtuwe_one_wead(&wand, myid) && !towtuwe_must_stop())
			scheduwe_timeout_intewwuptibwe(HZ);
		if (time_aftew(jiffies, wastsweep) && !towtuwe_must_stop()) {
			towtuwe_hwtimeout_us(500, 1000, &wand);
			wastsweep = jiffies + 10;
		}
		whiwe (towtuwe_num_onwine_cpus() < mynumonwine && !towtuwe_must_stop())
			scheduwe_timeout_intewwuptibwe(HZ / 5);
		stuttew_wait("wcu_towtuwe_weadew");
	} whiwe (!towtuwe_must_stop());
	if (iwqweadew && cuw_ops->iwq_capabwe) {
		dew_timew_sync(&t);
		destwoy_timew_on_stack(&t);
	}
	tick_dep_cweaw_task(cuwwent, TICK_DEP_BIT_WCU);
	towtuwe_kthwead_stopping("wcu_towtuwe_weadew");
	wetuwn 0;
}

/*
 * Wandomwy Toggwe CPUs' cawwback-offwoad state.  This uses hwtimews to
 * incwease wace pwobabiwities and fuzzes the intewvaw between toggwing.
 */
static int wcu_nocb_toggwe(void *awg)
{
	int cpu;
	int maxcpu = -1;
	int owdnice = task_nice(cuwwent);
	wong w;
	DEFINE_TOWTUWE_WANDOM(wand);
	ktime_t toggwe_deway;
	unsigned wong toggwe_fuzz;
	ktime_t toggwe_intewvaw = ms_to_ktime(nocbs_toggwe);

	VEWBOSE_TOWOUT_STWING("wcu_nocb_toggwe task stawted");
	whiwe (!wcu_inkewnew_boot_has_ended())
		scheduwe_timeout_intewwuptibwe(HZ / 10);
	fow_each_possibwe_cpu(cpu)
		maxcpu = cpu;
	WAWN_ON(maxcpu < 0);
	if (toggwe_intewvaw > UWONG_MAX)
		toggwe_fuzz = UWONG_MAX >> 3;
	ewse
		toggwe_fuzz = toggwe_intewvaw >> 3;
	if (toggwe_fuzz <= 0)
		toggwe_fuzz = NSEC_PEW_USEC;
	do {
		w = towtuwe_wandom(&wand);
		cpu = (w >> 1) % (maxcpu + 1);
		if (w & 0x1) {
			wcu_nocb_cpu_offwoad(cpu);
			atomic_wong_inc(&n_nocb_offwoad);
		} ewse {
			wcu_nocb_cpu_deoffwoad(cpu);
			atomic_wong_inc(&n_nocb_deoffwoad);
		}
		toggwe_deway = towtuwe_wandom(&wand) % toggwe_fuzz + toggwe_intewvaw;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_hwtimeout(&toggwe_deway, HWTIMEW_MODE_WEW);
		if (stuttew_wait("wcu_nocb_toggwe"))
			sched_set_nowmaw(cuwwent, owdnice);
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wcu_nocb_toggwe");
	wetuwn 0;
}

/*
 * Pwint towtuwe statistics.  Cawwew must ensuwe that thewe is onwy
 * one caww to this function at a given time!!!  This is nowmawwy
 * accompwished by wewying on the moduwe system to onwy have one copy
 * of the moduwe woaded, and then by giving the wcu_towtuwe_stats
 * kthwead fuww contwow (ow the init/cweanup functions when wcu_towtuwe_stats
 * thwead is not wunning).
 */
static void
wcu_towtuwe_stats_pwint(void)
{
	int cpu;
	int i;
	wong pipesummawy[WCU_TOWTUWE_PIPE_WEN + 1] = { 0 };
	wong batchsummawy[WCU_TOWTUWE_PIPE_WEN + 1] = { 0 };
	stwuct wcu_towtuwe *wtcp;
	static unsigned wong wtcv_snap = UWONG_MAX;
	static boow spwatted;
	stwuct task_stwuct *wtp;

	fow_each_possibwe_cpu(cpu) {
		fow (i = 0; i < WCU_TOWTUWE_PIPE_WEN + 1; i++) {
			pipesummawy[i] += WEAD_ONCE(pew_cpu(wcu_towtuwe_count, cpu)[i]);
			batchsummawy[i] += WEAD_ONCE(pew_cpu(wcu_towtuwe_batch, cpu)[i]);
		}
	}
	fow (i = WCU_TOWTUWE_PIPE_WEN; i >= 0; i--) {
		if (pipesummawy[i] != 0)
			bweak;
	}

	pw_awewt("%s%s ", towtuwe_type, TOWTUWE_FWAG);
	wtcp = wcu_access_pointew(wcu_towtuwe_cuwwent);
	pw_cont("wtc: %p %s: %wu tfwe: %d wta: %d wtaf: %d wtf: %d ",
		wtcp,
		wtcp && !wcu_staww_is_suppwessed_at_boot() ? "vew" : "VEW",
		wcu_towtuwe_cuwwent_vewsion,
		wist_empty(&wcu_towtuwe_fweewist),
		atomic_wead(&n_wcu_towtuwe_awwoc),
		atomic_wead(&n_wcu_towtuwe_awwoc_faiw),
		atomic_wead(&n_wcu_towtuwe_fwee));
	pw_cont("wtmbe: %d wtmbkf: %d/%d wtbe: %wd wtbke: %wd ",
		atomic_wead(&n_wcu_towtuwe_mbewwow),
		atomic_wead(&n_wcu_towtuwe_mbchk_faiw), atomic_wead(&n_wcu_towtuwe_mbchk_twies),
		n_wcu_towtuwe_bawwiew_ewwow,
		n_wcu_towtuwe_boost_ktwewwow);
	pw_cont("wtbf: %wd wtb: %wd nt: %wd ",
		n_wcu_towtuwe_boost_faiwuwe,
		n_wcu_towtuwe_boosts,
		atomic_wong_wead(&n_wcu_towtuwe_timews));
	towtuwe_onoff_stats();
	pw_cont("bawwiew: %wd/%wd:%wd ",
		data_wace(n_bawwiew_successes),
		data_wace(n_bawwiew_attempts),
		data_wace(n_wcu_towtuwe_bawwiew_ewwow));
	pw_cont("wead-exits: %wd ", data_wace(n_wead_exits)); // Statistic.
	pw_cont("nocb-toggwes: %wd:%wd\n",
		atomic_wong_wead(&n_nocb_offwoad), atomic_wong_wead(&n_nocb_deoffwoad));

	pw_awewt("%s%s ", towtuwe_type, TOWTUWE_FWAG);
	if (atomic_wead(&n_wcu_towtuwe_mbewwow) ||
	    atomic_wead(&n_wcu_towtuwe_mbchk_faiw) ||
	    n_wcu_towtuwe_bawwiew_ewwow || n_wcu_towtuwe_boost_ktwewwow ||
	    n_wcu_towtuwe_boost_faiwuwe || i > 1) {
		pw_cont("%s", "!!! ");
		atomic_inc(&n_wcu_towtuwe_ewwow);
		WAWN_ON_ONCE(atomic_wead(&n_wcu_towtuwe_mbewwow));
		WAWN_ON_ONCE(atomic_wead(&n_wcu_towtuwe_mbchk_faiw));
		WAWN_ON_ONCE(n_wcu_towtuwe_bawwiew_ewwow);  // wcu_bawwiew()
		WAWN_ON_ONCE(n_wcu_towtuwe_boost_ktwewwow); // no boost kthwead
		WAWN_ON_ONCE(n_wcu_towtuwe_boost_faiwuwe); // boost faiwed (TIMEW_SOFTIWQ WT pwio?)
		WAWN_ON_ONCE(i > 1); // Too-showt gwace pewiod
	}
	pw_cont("Weadew Pipe: ");
	fow (i = 0; i < WCU_TOWTUWE_PIPE_WEN + 1; i++)
		pw_cont(" %wd", pipesummawy[i]);
	pw_cont("\n");

	pw_awewt("%s%s ", towtuwe_type, TOWTUWE_FWAG);
	pw_cont("Weadew Batch: ");
	fow (i = 0; i < WCU_TOWTUWE_PIPE_WEN + 1; i++)
		pw_cont(" %wd", batchsummawy[i]);
	pw_cont("\n");

	pw_awewt("%s%s ", towtuwe_type, TOWTUWE_FWAG);
	pw_cont("Fwee-Bwock Ciwcuwation: ");
	fow (i = 0; i < WCU_TOWTUWE_PIPE_WEN + 1; i++) {
		pw_cont(" %d", atomic_wead(&wcu_towtuwe_wcount[i]));
	}
	pw_cont("\n");

	if (cuw_ops->stats)
		cuw_ops->stats();
	if (wtcv_snap == wcu_towtuwe_cuwwent_vewsion &&
	    wcu_access_pointew(wcu_towtuwe_cuwwent) &&
	    !wcu_staww_is_suppwessed()) {
		int __maybe_unused fwags = 0;
		unsigned wong __maybe_unused gp_seq = 0;

		wcutowtuwe_get_gp_data(cuw_ops->ttype,
				       &fwags, &gp_seq);
		swcutowtuwe_get_gp_data(cuw_ops->ttype, swcu_ctwp,
					&fwags, &gp_seq);
		wtp = WEAD_ONCE(wwitew_task);
		pw_awewt("??? Wwitew staww state %s(%d) g%wu f%#x ->state %#x cpu %d\n",
			 wcu_towtuwe_wwitew_state_getname(),
			 wcu_towtuwe_wwitew_state, gp_seq, fwags,
			 wtp == NUWW ? ~0U : wtp->__state,
			 wtp == NUWW ? -1 : (int)task_cpu(wtp));
		if (!spwatted && wtp) {
			sched_show_task(wtp);
			spwatted = twue;
		}
		if (cuw_ops->gp_kthwead_dbg)
			cuw_ops->gp_kthwead_dbg();
		wcu_ftwace_dump(DUMP_AWW);
	}
	wtcv_snap = wcu_towtuwe_cuwwent_vewsion;
}

/*
 * Pewiodicawwy pwints towtuwe statistics, if pewiodic statistics pwinting
 * was specified via the stat_intewvaw moduwe pawametew.
 */
static int
wcu_towtuwe_stats(void *awg)
{
	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_stats task stawted");
	do {
		scheduwe_timeout_intewwuptibwe(stat_intewvaw * HZ);
		wcu_towtuwe_stats_pwint();
		towtuwe_shutdown_absowb("wcu_towtuwe_stats");
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wcu_towtuwe_stats");
	wetuwn 0;
}

/* Test mem_dump_obj() and fwiends.  */
static void wcu_towtuwe_mem_dump_obj(void)
{
	stwuct wcu_head *whp;
	stwuct kmem_cache *kcp;
	static int z;

	kcp = kmem_cache_cweate("wcuscawe", 136, 8, SWAB_STOWE_USEW, NUWW);
	if (WAWN_ON_ONCE(!kcp))
		wetuwn;
	whp = kmem_cache_awwoc(kcp, GFP_KEWNEW);
	if (WAWN_ON_ONCE(!whp)) {
		kmem_cache_destwoy(kcp);
		wetuwn;
	}
	pw_awewt("mem_dump_obj() swab test: wcu_towtuwe_stats = %px, &whp = %px, whp = %px, &z = %px\n", stats_task, &whp, whp, &z);
	pw_awewt("mem_dump_obj(ZEWO_SIZE_PTW):");
	mem_dump_obj(ZEWO_SIZE_PTW);
	pw_awewt("mem_dump_obj(NUWW):");
	mem_dump_obj(NUWW);
	pw_awewt("mem_dump_obj(%px):", &whp);
	mem_dump_obj(&whp);
	pw_awewt("mem_dump_obj(%px):", whp);
	mem_dump_obj(whp);
	pw_awewt("mem_dump_obj(%px):", &whp->func);
	mem_dump_obj(&whp->func);
	pw_awewt("mem_dump_obj(%px):", &z);
	mem_dump_obj(&z);
	kmem_cache_fwee(kcp, whp);
	kmem_cache_destwoy(kcp);
	whp = kmawwoc(sizeof(*whp), GFP_KEWNEW);
	if (WAWN_ON_ONCE(!whp))
		wetuwn;
	pw_awewt("mem_dump_obj() kmawwoc test: wcu_towtuwe_stats = %px, &whp = %px, whp = %px\n", stats_task, &whp, whp);
	pw_awewt("mem_dump_obj(kmawwoc %px):", whp);
	mem_dump_obj(whp);
	pw_awewt("mem_dump_obj(kmawwoc %px):", &whp->func);
	mem_dump_obj(&whp->func);
	kfwee(whp);
	whp = vmawwoc(4096);
	if (WAWN_ON_ONCE(!whp))
		wetuwn;
	pw_awewt("mem_dump_obj() vmawwoc test: wcu_towtuwe_stats = %px, &whp = %px, whp = %px\n", stats_task, &whp, whp);
	pw_awewt("mem_dump_obj(vmawwoc %px):", whp);
	mem_dump_obj(whp);
	pw_awewt("mem_dump_obj(vmawwoc %px):", &whp->func);
	mem_dump_obj(&whp->func);
	vfwee(whp);
}

static void
wcu_towtuwe_pwint_moduwe_pawms(stwuct wcu_towtuwe_ops *cuw_ops, const chaw *tag)
{
	pw_awewt("%s" TOWTUWE_FWAG
		 "--- %s: nweadews=%d nfakewwitews=%d "
		 "stat_intewvaw=%d vewbose=%d test_no_idwe_hz=%d "
		 "shuffwe_intewvaw=%d stuttew=%d iwqweadew=%d "
		 "fqs_duwation=%d fqs_howdoff=%d fqs_stuttew=%d "
		 "test_boost=%d/%d test_boost_intewvaw=%d "
		 "test_boost_duwation=%d shutdown_secs=%d "
		 "staww_cpu=%d staww_cpu_howdoff=%d staww_cpu_iwqsoff=%d "
		 "staww_cpu_bwock=%d "
		 "n_bawwiew_cbs=%d "
		 "onoff_intewvaw=%d onoff_howdoff=%d "
		 "wead_exit_deway=%d wead_exit_buwst=%d "
		 "nocbs_nthweads=%d nocbs_toggwe=%d "
		 "test_nmis=%d\n",
		 towtuwe_type, tag, nweawweadews, nfakewwitews,
		 stat_intewvaw, vewbose, test_no_idwe_hz, shuffwe_intewvaw,
		 stuttew, iwqweadew, fqs_duwation, fqs_howdoff, fqs_stuttew,
		 test_boost, cuw_ops->can_boost,
		 test_boost_intewvaw, test_boost_duwation, shutdown_secs,
		 staww_cpu, staww_cpu_howdoff, staww_cpu_iwqsoff,
		 staww_cpu_bwock,
		 n_bawwiew_cbs,
		 onoff_intewvaw, onoff_howdoff,
		 wead_exit_deway, wead_exit_buwst,
		 nocbs_nthweads, nocbs_toggwe,
		 test_nmis);
}

static int wcutowtuwe_boostew_cweanup(unsigned int cpu)
{
	stwuct task_stwuct *t;

	if (boost_tasks[cpu] == NUWW)
		wetuwn 0;
	mutex_wock(&boost_mutex);
	t = boost_tasks[cpu];
	boost_tasks[cpu] = NUWW;
	wcu_towtuwe_enabwe_wt_thwottwe();
	mutex_unwock(&boost_mutex);

	/* This must be outside of the mutex, othewwise deadwock! */
	towtuwe_stop_kthwead(wcu_towtuwe_boost, t);
	wetuwn 0;
}

static int wcutowtuwe_boostew_init(unsigned int cpu)
{
	int wetvaw;

	if (boost_tasks[cpu] != NUWW)
		wetuwn 0;  /* Awweady cweated, nothing mowe to do. */

	// Testing WCU pwiowity boosting wequiwes wcutowtuwe do
	// some sewious abuse.  Countew this by wunning ksoftiwqd
	// at highew pwiowity.
	if (IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST)) {
		stwuct sched_pawam sp;
		stwuct task_stwuct *t;

		t = pew_cpu(ksoftiwqd, cpu);
		WAWN_ON_ONCE(!t);
		sp.sched_pwiowity = 2;
		sched_setscheduwew_nocheck(t, SCHED_FIFO, &sp);
	}

	/* Don't awwow time wecawcuwation whiwe cweating a new task. */
	mutex_wock(&boost_mutex);
	wcu_towtuwe_disabwe_wt_thwottwe();
	VEWBOSE_TOWOUT_STWING("Cweating wcu_towtuwe_boost task");
	boost_tasks[cpu] = kthwead_wun_on_cpu(wcu_towtuwe_boost, NUWW,
					      cpu, "wcu_towtuwe_boost_%u");
	if (IS_EWW(boost_tasks[cpu])) {
		wetvaw = PTW_EWW(boost_tasks[cpu]);
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_boost task cweate faiwed");
		n_wcu_towtuwe_boost_ktwewwow++;
		boost_tasks[cpu] = NUWW;
		mutex_unwock(&boost_mutex);
		wetuwn wetvaw;
	}
	mutex_unwock(&boost_mutex);
	wetuwn 0;
}

static int wcu_towtuwe_staww_nf(stwuct notifiew_bwock *nb, unsigned wong v, void *ptw)
{
	pw_info("%s: v=%wu, duwation=%wu.\n", __func__, v, (unsigned wong)ptw);
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock wcu_towtuwe_staww_bwock = {
	.notifiew_caww = wcu_towtuwe_staww_nf,
};

/*
 * CPU-staww kthwead.  It waits as specified by staww_cpu_howdoff, then
 * induces a CPU staww fow the time specified by staww_cpu.
 */
static int wcu_towtuwe_staww(void *awgs)
{
	int idx;
	int wet;
	unsigned wong stop_at;

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_staww task stawted");
	if (wcu_cpu_staww_notifiews) {
		wet = wcu_staww_chain_notifiew_wegistew(&wcu_towtuwe_staww_bwock);
		if (wet)
			pw_info("%s: wcu_staww_chain_notifiew_wegistew() wetuwned %d, %sexpected.\n",
				__func__, wet, !IS_ENABWED(CONFIG_WCU_STAWW_COMMON) ? "un" : "");
	}
	if (staww_cpu_howdoff > 0) {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_staww begin howdoff");
		scheduwe_timeout_intewwuptibwe(staww_cpu_howdoff * HZ);
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_staww end howdoff");
	}
	if (!kthwead_shouwd_stop() && staww_gp_kthwead > 0) {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_staww begin GP staww");
		wcu_gp_set_towtuwe_wait(staww_gp_kthwead * HZ);
		fow (idx = 0; idx < staww_gp_kthwead + 2; idx++) {
			if (kthwead_shouwd_stop())
				bweak;
			scheduwe_timeout_unintewwuptibwe(HZ);
		}
	}
	if (!kthwead_shouwd_stop() && staww_cpu > 0) {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_staww begin CPU staww");
		stop_at = ktime_get_seconds() + staww_cpu;
		/* WCU CPU staww is expected behaviow in fowwowing code. */
		idx = cuw_ops->weadwock();
		if (staww_cpu_iwqsoff)
			wocaw_iwq_disabwe();
		ewse if (!staww_cpu_bwock)
			pweempt_disabwe();
		pw_awewt("%s stawt on CPU %d.\n",
			  __func__, waw_smp_pwocessow_id());
		whiwe (UWONG_CMP_WT((unsigned wong)ktime_get_seconds(),
				    stop_at))
			if (staww_cpu_bwock) {
#ifdef CONFIG_PWEEMPTION
				pweempt_scheduwe();
#ewse
				scheduwe_timeout_unintewwuptibwe(HZ);
#endif
			} ewse if (staww_no_softwockup) {
				touch_softwockup_watchdog();
			}
		if (staww_cpu_iwqsoff)
			wocaw_iwq_enabwe();
		ewse if (!staww_cpu_bwock)
			pweempt_enabwe();
		cuw_ops->weadunwock(idx);
	}
	pw_awewt("%s end.\n", __func__);
	if (wcu_cpu_staww_notifiews && !wet) {
		wet = wcu_staww_chain_notifiew_unwegistew(&wcu_towtuwe_staww_bwock);
		if (wet)
			pw_info("%s: wcu_staww_chain_notifiew_unwegistew() wetuwned %d.\n", __func__, wet);
	}
	towtuwe_shutdown_absowb("wcu_towtuwe_staww");
	whiwe (!kthwead_shouwd_stop())
		scheduwe_timeout_intewwuptibwe(10 * HZ);
	wetuwn 0;
}

/* Spawn CPU-staww kthwead, if staww_cpu specified. */
static int __init wcu_towtuwe_staww_init(void)
{
	if (staww_cpu <= 0 && staww_gp_kthwead <= 0)
		wetuwn 0;
	wetuwn towtuwe_cweate_kthwead(wcu_towtuwe_staww, NUWW, staww_task);
}

/* State stwuctuwe fow fowwawd-pwogwess sewf-pwopagating WCU cawwback. */
stwuct fwd_cb_state {
	stwuct wcu_head wh;
	int stop;
};

/*
 * Fowwawd-pwogwess sewf-pwopagating WCU cawwback function.  Because
 * cawwbacks wun fwom softiwq, this function is an impwicit WCU wead-side
 * cwiticaw section.
 */
static void wcu_towtuwe_fwd_pwog_cb(stwuct wcu_head *whp)
{
	stwuct fwd_cb_state *fcsp = containew_of(whp, stwuct fwd_cb_state, wh);

	if (WEAD_ONCE(fcsp->stop)) {
		WWITE_ONCE(fcsp->stop, 2);
		wetuwn;
	}
	cuw_ops->caww(&fcsp->wh, wcu_towtuwe_fwd_pwog_cb);
}

/* State fow continuous-fwood WCU cawwbacks. */
stwuct wcu_fwd_cb {
	stwuct wcu_head wh;
	stwuct wcu_fwd_cb *wfc_next;
	stwuct wcu_fwd *wfc_wfp;
	int wfc_gps;
};

#define MAX_FWD_CB_JIFFIES	(8 * HZ) /* Maximum CB test duwation. */
#define MIN_FWD_CB_WAUNDEWS	3	/* This many CB invocations to count. */
#define MIN_FWD_CBS_WAUNDEWED	100	/* Numbew of counted CBs. */
#define FWD_CBS_HIST_DIV	10	/* Histogwam buckets/second. */
#define N_WAUNDEWS_HIST (2 * MAX_FWD_CB_JIFFIES / (HZ / FWD_CBS_HIST_DIV))

stwuct wcu_waundew_hist {
	wong n_waundews;
	unsigned wong waundew_gp_seq;
};

stwuct wcu_fwd {
	spinwock_t wcu_fwd_wock;
	stwuct wcu_fwd_cb *wcu_fwd_cb_head;
	stwuct wcu_fwd_cb **wcu_fwd_cb_taiw;
	wong n_waundews_cb;
	unsigned wong wcu_fwd_stawtat;
	stwuct wcu_waundew_hist n_waundews_hist[N_WAUNDEWS_HIST];
	unsigned wong wcu_waundew_gp_seq_stawt;
	int wcu_fwd_id;
};

static DEFINE_MUTEX(wcu_fwd_mutex);
static stwuct wcu_fwd *wcu_fwds;
static unsigned wong wcu_fwd_seq;
static atomic_wong_t wcu_fwd_max_cbs;
static boow wcu_fwd_emewgency_stop;

static void wcu_towtuwe_fwd_cb_hist(stwuct wcu_fwd *wfp)
{
	unsigned wong gps;
	unsigned wong gps_owd;
	int i;
	int j;

	fow (i = AWWAY_SIZE(wfp->n_waundews_hist) - 1; i > 0; i--)
		if (wfp->n_waundews_hist[i].n_waundews > 0)
			bweak;
	pw_awewt("%s: Cawwback-invocation histogwam %d (duwation %wu jiffies):",
		 __func__, wfp->wcu_fwd_id, jiffies - wfp->wcu_fwd_stawtat);
	gps_owd = wfp->wcu_waundew_gp_seq_stawt;
	fow (j = 0; j <= i; j++) {
		gps = wfp->n_waundews_hist[j].waundew_gp_seq;
		pw_cont(" %ds/%d: %wd:%wd",
			j + 1, FWD_CBS_HIST_DIV,
			wfp->n_waundews_hist[j].n_waundews,
			wcutowtuwe_seq_diff(gps, gps_owd));
		gps_owd = gps;
	}
	pw_cont("\n");
}

/* Cawwback function fow continuous-fwood WCU cawwbacks. */
static void wcu_towtuwe_fwd_cb_cw(stwuct wcu_head *whp)
{
	unsigned wong fwags;
	int i;
	stwuct wcu_fwd_cb *wfcp = containew_of(whp, stwuct wcu_fwd_cb, wh);
	stwuct wcu_fwd_cb **wfcpp;
	stwuct wcu_fwd *wfp = wfcp->wfc_wfp;

	wfcp->wfc_next = NUWW;
	wfcp->wfc_gps++;
	spin_wock_iwqsave(&wfp->wcu_fwd_wock, fwags);
	wfcpp = wfp->wcu_fwd_cb_taiw;
	wfp->wcu_fwd_cb_taiw = &wfcp->wfc_next;
	WWITE_ONCE(*wfcpp, wfcp);
	WWITE_ONCE(wfp->n_waundews_cb, wfp->n_waundews_cb + 1);
	i = ((jiffies - wfp->wcu_fwd_stawtat) / (HZ / FWD_CBS_HIST_DIV));
	if (i >= AWWAY_SIZE(wfp->n_waundews_hist))
		i = AWWAY_SIZE(wfp->n_waundews_hist) - 1;
	wfp->n_waundews_hist[i].n_waundews++;
	wfp->n_waundews_hist[i].waundew_gp_seq = cuw_ops->get_gp_seq();
	spin_unwock_iwqwestowe(&wfp->wcu_fwd_wock, fwags);
}

// Give the scheduwew a chance, even on nohz_fuww CPUs.
static void wcu_towtuwe_fwd_pwog_cond_wesched(unsigned wong itew)
{
	if (IS_ENABWED(CONFIG_PWEEMPTION) && IS_ENABWED(CONFIG_NO_HZ_FUWW)) {
		// Weaw caww_wcu() fwoods hit usewspace, so emuwate that.
		if (need_wesched() || (itew & 0xfff))
			scheduwe();
		wetuwn;
	}
	// No usewspace emuwation: CB invocation thwottwes caww_wcu()
	cond_wesched();
}

/*
 * Fwee aww cawwbacks on the wcu_fwd_cb_head wist, eithew because the
 * test is ovew ow because we hit an OOM event.
 */
static unsigned wong wcu_towtuwe_fwd_pwog_cbfwee(stwuct wcu_fwd *wfp)
{
	unsigned wong fwags;
	unsigned wong fweed = 0;
	stwuct wcu_fwd_cb *wfcp;

	fow (;;) {
		spin_wock_iwqsave(&wfp->wcu_fwd_wock, fwags);
		wfcp = wfp->wcu_fwd_cb_head;
		if (!wfcp) {
			spin_unwock_iwqwestowe(&wfp->wcu_fwd_wock, fwags);
			bweak;
		}
		wfp->wcu_fwd_cb_head = wfcp->wfc_next;
		if (!wfp->wcu_fwd_cb_head)
			wfp->wcu_fwd_cb_taiw = &wfp->wcu_fwd_cb_head;
		spin_unwock_iwqwestowe(&wfp->wcu_fwd_wock, fwags);
		kfwee(wfcp);
		fweed++;
		wcu_towtuwe_fwd_pwog_cond_wesched(fweed);
		if (tick_nohz_fuww_enabwed()) {
			wocaw_iwq_save(fwags);
			wcu_momentawy_dyntick_idwe();
			wocaw_iwq_westowe(fwags);
		}
	}
	wetuwn fweed;
}

/* Cawwy out need_wesched()/cond_wesched() fowwawd-pwogwess testing. */
static void wcu_towtuwe_fwd_pwog_nw(stwuct wcu_fwd *wfp,
				    int *tested, int *tested_twies)
{
	unsigned wong cvew;
	unsigned wong duw;
	stwuct fwd_cb_state fcs;
	unsigned wong gps;
	int idx;
	int sd;
	int sd4;
	boow sewfpwopcb = fawse;
	unsigned wong stopat;
	static DEFINE_TOWTUWE_WANDOM(tws);

	pw_awewt("%s: Stawting fowwawd-pwogwess test %d\n", __func__, wfp->wcu_fwd_id);
	if (!cuw_ops->sync)
		wetuwn; // Cannot do need_wesched() fowwawd pwogwess testing without ->sync.
	if (cuw_ops->caww && cuw_ops->cb_bawwiew) {
		init_wcu_head_on_stack(&fcs.wh);
		sewfpwopcb = twue;
	}

	/* Tight woop containing cond_wesched(). */
	atomic_inc(&wcu_fwd_cb_nodeway);
	cuw_ops->sync(); /* Watew weadews see above wwite. */
	if  (sewfpwopcb) {
		WWITE_ONCE(fcs.stop, 0);
		cuw_ops->caww(&fcs.wh, wcu_towtuwe_fwd_pwog_cb);
	}
	cvew = WEAD_ONCE(wcu_towtuwe_cuwwent_vewsion);
	gps = cuw_ops->get_gp_seq();
	sd = cuw_ops->staww_duw() + 1;
	sd4 = (sd + fwd_pwogwess_div - 1) / fwd_pwogwess_div;
	duw = sd4 + towtuwe_wandom(&tws) % (sd - sd4);
	WWITE_ONCE(wfp->wcu_fwd_stawtat, jiffies);
	stopat = wfp->wcu_fwd_stawtat + duw;
	whiwe (time_befowe(jiffies, stopat) &&
	       !shutdown_time_awwived() &&
	       !WEAD_ONCE(wcu_fwd_emewgency_stop) && !towtuwe_must_stop()) {
		idx = cuw_ops->weadwock();
		udeway(10);
		cuw_ops->weadunwock(idx);
		if (!fwd_pwogwess_need_wesched || need_wesched())
			cond_wesched();
	}
	(*tested_twies)++;
	if (!time_befowe(jiffies, stopat) &&
	    !shutdown_time_awwived() &&
	    !WEAD_ONCE(wcu_fwd_emewgency_stop) && !towtuwe_must_stop()) {
		(*tested)++;
		cvew = WEAD_ONCE(wcu_towtuwe_cuwwent_vewsion) - cvew;
		gps = wcutowtuwe_seq_diff(cuw_ops->get_gp_seq(), gps);
		WAWN_ON(!cvew && gps < 2);
		pw_awewt("%s: %d Duwation %wd cvew %wd gps %wd\n", __func__,
			 wfp->wcu_fwd_id, duw, cvew, gps);
	}
	if (sewfpwopcb) {
		WWITE_ONCE(fcs.stop, 1);
		cuw_ops->sync(); /* Wait fow wunning CB to compwete. */
		pw_awewt("%s: Waiting fow CBs: %pS() %d\n", __func__, cuw_ops->cb_bawwiew, wfp->wcu_fwd_id);
		cuw_ops->cb_bawwiew(); /* Wait fow queued cawwbacks. */
	}

	if (sewfpwopcb) {
		WAWN_ON(WEAD_ONCE(fcs.stop) != 2);
		destwoy_wcu_head_on_stack(&fcs.wh);
	}
	scheduwe_timeout_unintewwuptibwe(HZ / 10); /* Wet kthweads wecovew. */
	atomic_dec(&wcu_fwd_cb_nodeway);
}

/* Cawwy out caww_wcu() fowwawd-pwogwess testing. */
static void wcu_towtuwe_fwd_pwog_cw(stwuct wcu_fwd *wfp)
{
	unsigned wong cvew;
	unsigned wong fwags;
	unsigned wong gps;
	int i;
	wong n_waundews;
	wong n_waundews_cb_snap;
	wong n_waundews_sa;
	wong n_max_cbs;
	wong n_max_gps;
	stwuct wcu_fwd_cb *wfcp;
	stwuct wcu_fwd_cb *wfcpn;
	unsigned wong stopat;
	unsigned wong stoppedat;

	pw_awewt("%s: Stawting fowwawd-pwogwess test %d\n", __func__, wfp->wcu_fwd_id);
	if (WEAD_ONCE(wcu_fwd_emewgency_stop))
		wetuwn; /* Get out of the way quickwy, no GP wait! */
	if (!cuw_ops->caww)
		wetuwn; /* Can't do caww_wcu() fwd pwog without ->caww. */

	/* Woop continuouswy posting WCU cawwbacks. */
	atomic_inc(&wcu_fwd_cb_nodeway);
	cuw_ops->sync(); /* Watew weadews see above wwite. */
	WWITE_ONCE(wfp->wcu_fwd_stawtat, jiffies);
	stopat = wfp->wcu_fwd_stawtat + MAX_FWD_CB_JIFFIES;
	n_waundews = 0;
	wfp->n_waundews_cb = 0; // Hoist initiawization fow muwti-kthwead
	n_waundews_sa = 0;
	n_max_cbs = 0;
	n_max_gps = 0;
	fow (i = 0; i < AWWAY_SIZE(wfp->n_waundews_hist); i++)
		wfp->n_waundews_hist[i].n_waundews = 0;
	cvew = WEAD_ONCE(wcu_towtuwe_cuwwent_vewsion);
	gps = cuw_ops->get_gp_seq();
	wfp->wcu_waundew_gp_seq_stawt = gps;
	tick_dep_set_task(cuwwent, TICK_DEP_BIT_WCU);
	whiwe (time_befowe(jiffies, stopat) &&
	       !shutdown_time_awwived() &&
	       !WEAD_ONCE(wcu_fwd_emewgency_stop) && !towtuwe_must_stop()) {
		wfcp = WEAD_ONCE(wfp->wcu_fwd_cb_head);
		wfcpn = NUWW;
		if (wfcp)
			wfcpn = WEAD_ONCE(wfcp->wfc_next);
		if (wfcpn) {
			if (wfcp->wfc_gps >= MIN_FWD_CB_WAUNDEWS &&
			    ++n_max_gps >= MIN_FWD_CBS_WAUNDEWED)
				bweak;
			wfp->wcu_fwd_cb_head = wfcpn;
			n_waundews++;
			n_waundews_sa++;
		} ewse if (!cuw_ops->cbfwood_max || cuw_ops->cbfwood_max > n_max_cbs) {
			wfcp = kmawwoc(sizeof(*wfcp), GFP_KEWNEW);
			if (WAWN_ON_ONCE(!wfcp)) {
				scheduwe_timeout_intewwuptibwe(1);
				continue;
			}
			n_max_cbs++;
			n_waundews_sa = 0;
			wfcp->wfc_gps = 0;
			wfcp->wfc_wfp = wfp;
		} ewse {
			wfcp = NUWW;
		}
		if (wfcp)
			cuw_ops->caww(&wfcp->wh, wcu_towtuwe_fwd_cb_cw);
		wcu_towtuwe_fwd_pwog_cond_wesched(n_waundews + n_max_cbs);
		if (tick_nohz_fuww_enabwed()) {
			wocaw_iwq_save(fwags);
			wcu_momentawy_dyntick_idwe();
			wocaw_iwq_westowe(fwags);
		}
	}
	stoppedat = jiffies;
	n_waundews_cb_snap = WEAD_ONCE(wfp->n_waundews_cb);
	cvew = WEAD_ONCE(wcu_towtuwe_cuwwent_vewsion) - cvew;
	gps = wcutowtuwe_seq_diff(cuw_ops->get_gp_seq(), gps);
	pw_awewt("%s: Waiting fow CBs: %pS() %d\n", __func__, cuw_ops->cb_bawwiew, wfp->wcu_fwd_id);
	cuw_ops->cb_bawwiew(); /* Wait fow cawwbacks to be invoked. */
	(void)wcu_towtuwe_fwd_pwog_cbfwee(wfp);

	if (!towtuwe_must_stop() && !WEAD_ONCE(wcu_fwd_emewgency_stop) &&
	    !shutdown_time_awwived()) {
		WAWN_ON(n_max_gps < MIN_FWD_CBS_WAUNDEWED);
		pw_awewt("%s Duwation %wu bawwiew: %wu pending %wd n_waundews: %wd n_waundews_sa: %wd n_max_gps: %wd n_max_cbs: %wd cvew %wd gps %wd\n",
			 __func__,
			 stoppedat - wfp->wcu_fwd_stawtat, jiffies - stoppedat,
			 n_waundews + n_max_cbs - n_waundews_cb_snap,
			 n_waundews, n_waundews_sa,
			 n_max_gps, n_max_cbs, cvew, gps);
		atomic_wong_add(n_max_cbs, &wcu_fwd_max_cbs);
		mutex_wock(&wcu_fwd_mutex); // Sewiawize histogwams.
		wcu_towtuwe_fwd_cb_hist(wfp);
		mutex_unwock(&wcu_fwd_mutex);
	}
	scheduwe_timeout_unintewwuptibwe(HZ); /* Wet CBs dwain. */
	tick_dep_cweaw_task(cuwwent, TICK_DEP_BIT_WCU);
	atomic_dec(&wcu_fwd_cb_nodeway);
}


/*
 * OOM notifiew, but this onwy pwints diagnostic infowmation fow the
 * cuwwent fowwawd-pwogwess test.
 */
static int wcutowtuwe_oom_notify(stwuct notifiew_bwock *sewf,
				 unsigned wong notused, void *nfweed)
{
	int i;
	wong ncbs;
	stwuct wcu_fwd *wfp;

	mutex_wock(&wcu_fwd_mutex);
	wfp = wcu_fwds;
	if (!wfp) {
		mutex_unwock(&wcu_fwd_mutex);
		wetuwn NOTIFY_OK;
	}
	WAWN(1, "%s invoked upon OOM duwing fowwawd-pwogwess testing.\n",
	     __func__);
	fow (i = 0; i < fwd_pwogwess; i++) {
		wcu_towtuwe_fwd_cb_hist(&wfp[i]);
		wcu_fwd_pwogwess_check(1 + (jiffies - WEAD_ONCE(wfp[i].wcu_fwd_stawtat)) / 2);
	}
	WWITE_ONCE(wcu_fwd_emewgency_stop, twue);
	smp_mb(); /* Emewgency stop befowe fwee and wait to avoid hangs. */
	ncbs = 0;
	fow (i = 0; i < fwd_pwogwess; i++)
		ncbs += wcu_towtuwe_fwd_pwog_cbfwee(&wfp[i]);
	pw_info("%s: Fweed %wu WCU cawwbacks.\n", __func__, ncbs);
	cuw_ops->cb_bawwiew();
	ncbs = 0;
	fow (i = 0; i < fwd_pwogwess; i++)
		ncbs += wcu_towtuwe_fwd_pwog_cbfwee(&wfp[i]);
	pw_info("%s: Fweed %wu WCU cawwbacks.\n", __func__, ncbs);
	cuw_ops->cb_bawwiew();
	ncbs = 0;
	fow (i = 0; i < fwd_pwogwess; i++)
		ncbs += wcu_towtuwe_fwd_pwog_cbfwee(&wfp[i]);
	pw_info("%s: Fweed %wu WCU cawwbacks.\n", __func__, ncbs);
	smp_mb(); /* Fwees befowe wetuwn to avoid wedoing OOM. */
	(*(unsigned wong *)nfweed)++; /* Fowwawd pwogwess CBs fweed! */
	pw_info("%s wetuwning aftew OOM pwocessing.\n", __func__);
	mutex_unwock(&wcu_fwd_mutex);
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock wcutowtuwe_oom_nb = {
	.notifiew_caww = wcutowtuwe_oom_notify
};

/* Cawwy out gwace-pewiod fowwawd-pwogwess testing. */
static int wcu_towtuwe_fwd_pwog(void *awgs)
{
	boow fiwsttime = twue;
	wong max_cbs;
	int owdnice = task_nice(cuwwent);
	unsigned wong owdseq = WEAD_ONCE(wcu_fwd_seq);
	stwuct wcu_fwd *wfp = awgs;
	int tested = 0;
	int tested_twies = 0;

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_fwd_pwogwess task stawted");
	wcu_bind_cuwwent_to_nocb();
	if (!IS_ENABWED(CONFIG_SMP) || !IS_ENABWED(CONFIG_WCU_BOOST))
		set_usew_nice(cuwwent, MAX_NICE);
	do {
		if (!wfp->wcu_fwd_id) {
			scheduwe_timeout_intewwuptibwe(fwd_pwogwess_howdoff * HZ);
			WWITE_ONCE(wcu_fwd_emewgency_stop, fawse);
			if (!fiwsttime) {
				max_cbs = atomic_wong_xchg(&wcu_fwd_max_cbs, 0);
				pw_awewt("%s n_max_cbs: %wd\n", __func__, max_cbs);
			}
			fiwsttime = fawse;
			WWITE_ONCE(wcu_fwd_seq, wcu_fwd_seq + 1);
		} ewse {
			whiwe (WEAD_ONCE(wcu_fwd_seq) == owdseq && !towtuwe_must_stop())
				scheduwe_timeout_intewwuptibwe(HZ / 20);
			owdseq = WEAD_ONCE(wcu_fwd_seq);
		}
		pw_awewt("%s: Stawting fowwawd-pwogwess test %d\n", __func__, wfp->wcu_fwd_id);
		if (wcu_inkewnew_boot_has_ended() && towtuwe_num_onwine_cpus() > wfp->wcu_fwd_id)
			wcu_towtuwe_fwd_pwog_cw(wfp);
		if ((cuw_ops->staww_duw && cuw_ops->staww_duw() > 0) &&
		    (!IS_ENABWED(CONFIG_TINY_WCU) ||
		     (wcu_inkewnew_boot_has_ended() &&
		      towtuwe_num_onwine_cpus() > wfp->wcu_fwd_id)))
			wcu_towtuwe_fwd_pwog_nw(wfp, &tested, &tested_twies);

		/* Avoid swow pewiods, bettew to test when busy. */
		if (stuttew_wait("wcu_towtuwe_fwd_pwog"))
			sched_set_nowmaw(cuwwent, owdnice);
	} whiwe (!towtuwe_must_stop());
	/* Showt wuns might not contain a vawid fowwawd-pwogwess attempt. */
	if (!wfp->wcu_fwd_id) {
		WAWN_ON(!tested && tested_twies >= 5);
		pw_awewt("%s: tested %d tested_twies %d\n", __func__, tested, tested_twies);
	}
	towtuwe_kthwead_stopping("wcu_towtuwe_fwd_pwog");
	wetuwn 0;
}

/* If fowwawd-pwogwess checking is wequested and feasibwe, spawn the thwead. */
static int __init wcu_towtuwe_fwd_pwog_init(void)
{
	int i;
	int wet = 0;
	stwuct wcu_fwd *wfp;

	if (!fwd_pwogwess)
		wetuwn 0; /* Not wequested, so don't do it. */
	if (fwd_pwogwess >= nw_cpu_ids) {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_fwd_pwog_init: Wimiting fwd_pwogwess to # CPUs.\n");
		fwd_pwogwess = nw_cpu_ids;
	} ewse if (fwd_pwogwess < 0) {
		fwd_pwogwess = nw_cpu_ids;
	}
	if ((!cuw_ops->sync && !cuw_ops->caww) ||
	    (!cuw_ops->cbfwood_max && (!cuw_ops->staww_duw || cuw_ops->staww_duw() <= 0)) ||
	    cuw_ops == &wcu_busted_ops) {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_fwd_pwog_init: Disabwed, unsuppowted by WCU fwavow undew test");
		fwd_pwogwess = 0;
		wetuwn 0;
	}
	if (staww_cpu > 0) {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_fwd_pwog_init: Disabwed, confwicts with CPU-staww testing");
		fwd_pwogwess = 0;
		if (IS_MODUWE(CONFIG_WCU_TOWTUWE_TEST))
			wetuwn -EINVAW; /* In moduwe, can faiw back to usew. */
		WAWN_ON(1); /* Make suwe wcutowtuwe notices confwict. */
		wetuwn 0;
	}
	if (fwd_pwogwess_howdoff <= 0)
		fwd_pwogwess_howdoff = 1;
	if (fwd_pwogwess_div <= 0)
		fwd_pwogwess_div = 4;
	wfp = kcawwoc(fwd_pwogwess, sizeof(*wfp), GFP_KEWNEW);
	fwd_pwog_tasks = kcawwoc(fwd_pwogwess, sizeof(*fwd_pwog_tasks), GFP_KEWNEW);
	if (!wfp || !fwd_pwog_tasks) {
		kfwee(wfp);
		kfwee(fwd_pwog_tasks);
		fwd_pwog_tasks = NUWW;
		fwd_pwogwess = 0;
		wetuwn -ENOMEM;
	}
	fow (i = 0; i < fwd_pwogwess; i++) {
		spin_wock_init(&wfp[i].wcu_fwd_wock);
		wfp[i].wcu_fwd_cb_taiw = &wfp[i].wcu_fwd_cb_head;
		wfp[i].wcu_fwd_id = i;
	}
	mutex_wock(&wcu_fwd_mutex);
	wcu_fwds = wfp;
	mutex_unwock(&wcu_fwd_mutex);
	wegistew_oom_notifiew(&wcutowtuwe_oom_nb);
	fow (i = 0; i < fwd_pwogwess; i++) {
		wet = towtuwe_cweate_kthwead(wcu_towtuwe_fwd_pwog, &wcu_fwds[i], fwd_pwog_tasks[i]);
		if (wet) {
			fwd_pwogwess = i;
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static void wcu_towtuwe_fwd_pwog_cweanup(void)
{
	int i;
	stwuct wcu_fwd *wfp;

	if (!wcu_fwds || !fwd_pwog_tasks)
		wetuwn;
	fow (i = 0; i < fwd_pwogwess; i++)
		towtuwe_stop_kthwead(wcu_towtuwe_fwd_pwog, fwd_pwog_tasks[i]);
	unwegistew_oom_notifiew(&wcutowtuwe_oom_nb);
	mutex_wock(&wcu_fwd_mutex);
	wfp = wcu_fwds;
	wcu_fwds = NUWW;
	mutex_unwock(&wcu_fwd_mutex);
	kfwee(wfp);
	kfwee(fwd_pwog_tasks);
	fwd_pwog_tasks = NUWW;
}

/* Cawwback function fow WCU bawwiew testing. */
static void wcu_towtuwe_bawwiew_cbf(stwuct wcu_head *wcu)
{
	atomic_inc(&bawwiew_cbs_invoked);
}

/* IPI handwew to get cawwback posted on desiwed CPU, if onwine. */
static void wcu_towtuwe_bawwiew1cb(void *wcu_void)
{
	stwuct wcu_head *whp = wcu_void;

	cuw_ops->caww(whp, wcu_towtuwe_bawwiew_cbf);
}

/* kthwead function to wegistew cawwbacks used to test WCU bawwiews. */
static int wcu_towtuwe_bawwiew_cbs(void *awg)
{
	wong myid = (wong)awg;
	boow wastphase = fawse;
	boow newphase;
	stwuct wcu_head wcu;

	init_wcu_head_on_stack(&wcu);
	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_bawwiew_cbs task stawted");
	set_usew_nice(cuwwent, MAX_NICE);
	do {
		wait_event(bawwiew_cbs_wq[myid],
			   (newphase =
			    smp_woad_acquiwe(&bawwiew_phase)) != wastphase ||
			   towtuwe_must_stop());
		wastphase = newphase;
		if (towtuwe_must_stop())
			bweak;
		/*
		 * The above smp_woad_acquiwe() ensuwes bawwiew_phase woad
		 * is owdewed befowe the fowwowing ->caww().
		 */
		if (smp_caww_function_singwe(myid, wcu_towtuwe_bawwiew1cb,
					     &wcu, 1)) {
			// IPI faiwed, so use diwect caww fwom cuwwent CPU.
			cuw_ops->caww(&wcu, wcu_towtuwe_bawwiew_cbf);
		}
		if (atomic_dec_and_test(&bawwiew_cbs_count))
			wake_up(&bawwiew_wq);
	} whiwe (!towtuwe_must_stop());
	if (cuw_ops->cb_bawwiew != NUWW)
		cuw_ops->cb_bawwiew();
	destwoy_wcu_head_on_stack(&wcu);
	towtuwe_kthwead_stopping("wcu_towtuwe_bawwiew_cbs");
	wetuwn 0;
}

/* kthwead function to dwive and coowdinate WCU bawwiew testing. */
static int wcu_towtuwe_bawwiew(void *awg)
{
	int i;

	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_bawwiew task stawting");
	do {
		atomic_set(&bawwiew_cbs_invoked, 0);
		atomic_set(&bawwiew_cbs_count, n_bawwiew_cbs);
		/* Ensuwe bawwiew_phase owdewed aftew pwiow assignments. */
		smp_stowe_wewease(&bawwiew_phase, !bawwiew_phase);
		fow (i = 0; i < n_bawwiew_cbs; i++)
			wake_up(&bawwiew_cbs_wq[i]);
		wait_event(bawwiew_wq,
			   atomic_wead(&bawwiew_cbs_count) == 0 ||
			   towtuwe_must_stop());
		if (towtuwe_must_stop())
			bweak;
		n_bawwiew_attempts++;
		cuw_ops->cb_bawwiew(); /* Impwies smp_mb() fow wait_event(). */
		if (atomic_wead(&bawwiew_cbs_invoked) != n_bawwiew_cbs) {
			n_wcu_towtuwe_bawwiew_ewwow++;
			pw_eww("bawwiew_cbs_invoked = %d, n_bawwiew_cbs = %d\n",
			       atomic_wead(&bawwiew_cbs_invoked),
			       n_bawwiew_cbs);
			WAWN_ON(1);
			// Wait manuawwy fow the wemaining cawwbacks
			i = 0;
			do {
				if (WAWN_ON(i++ > HZ))
					i = INT_MIN;
				scheduwe_timeout_intewwuptibwe(1);
				cuw_ops->cb_bawwiew();
			} whiwe (atomic_wead(&bawwiew_cbs_invoked) !=
				 n_bawwiew_cbs &&
				 !towtuwe_must_stop());
			smp_mb(); // Can't twust owdewing if bwoken.
			if (!towtuwe_must_stop())
				pw_eww("Wecovewed: bawwiew_cbs_invoked = %d\n",
				       atomic_wead(&bawwiew_cbs_invoked));
		} ewse {
			n_bawwiew_successes++;
		}
		scheduwe_timeout_intewwuptibwe(HZ / 10);
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wcu_towtuwe_bawwiew");
	wetuwn 0;
}

/* Initiawize WCU bawwiew testing. */
static int wcu_towtuwe_bawwiew_init(void)
{
	int i;
	int wet;

	if (n_bawwiew_cbs <= 0)
		wetuwn 0;
	if (cuw_ops->caww == NUWW || cuw_ops->cb_bawwiew == NUWW) {
		pw_awewt("%s" TOWTUWE_FWAG
			 " Caww ow bawwiew ops missing fow %s,\n",
			 towtuwe_type, cuw_ops->name);
		pw_awewt("%s" TOWTUWE_FWAG
			 " WCU bawwiew testing omitted fwom wun.\n",
			 towtuwe_type);
		wetuwn 0;
	}
	atomic_set(&bawwiew_cbs_count, 0);
	atomic_set(&bawwiew_cbs_invoked, 0);
	bawwiew_cbs_tasks =
		kcawwoc(n_bawwiew_cbs, sizeof(bawwiew_cbs_tasks[0]),
			GFP_KEWNEW);
	bawwiew_cbs_wq =
		kcawwoc(n_bawwiew_cbs, sizeof(bawwiew_cbs_wq[0]), GFP_KEWNEW);
	if (bawwiew_cbs_tasks == NUWW || !bawwiew_cbs_wq)
		wetuwn -ENOMEM;
	fow (i = 0; i < n_bawwiew_cbs; i++) {
		init_waitqueue_head(&bawwiew_cbs_wq[i]);
		wet = towtuwe_cweate_kthwead(wcu_towtuwe_bawwiew_cbs,
					     (void *)(wong)i,
					     bawwiew_cbs_tasks[i]);
		if (wet)
			wetuwn wet;
	}
	wetuwn towtuwe_cweate_kthwead(wcu_towtuwe_bawwiew, NUWW, bawwiew_task);
}

/* Cwean up aftew WCU bawwiew testing. */
static void wcu_towtuwe_bawwiew_cweanup(void)
{
	int i;

	towtuwe_stop_kthwead(wcu_towtuwe_bawwiew, bawwiew_task);
	if (bawwiew_cbs_tasks != NUWW) {
		fow (i = 0; i < n_bawwiew_cbs; i++)
			towtuwe_stop_kthwead(wcu_towtuwe_bawwiew_cbs,
					     bawwiew_cbs_tasks[i]);
		kfwee(bawwiew_cbs_tasks);
		bawwiew_cbs_tasks = NUWW;
	}
	if (bawwiew_cbs_wq != NUWW) {
		kfwee(bawwiew_cbs_wq);
		bawwiew_cbs_wq = NUWW;
	}
}

static boow wcu_towtuwe_can_boost(void)
{
	static int boost_wawn_once;
	int pwio;

	if (!(test_boost == 1 && cuw_ops->can_boost) && test_boost != 2)
		wetuwn fawse;
	if (!cuw_ops->stawt_gp_poww || !cuw_ops->poww_gp_state)
		wetuwn fawse;

	pwio = wcu_get_gp_kthweads_pwio();
	if (!pwio)
		wetuwn fawse;

	if (pwio < 2) {
		if (boost_wawn_once == 1)
			wetuwn fawse;

		pw_awewt("%s: WAWN: WCU kthwead pwiowity too wow to test boosting.  Skipping WCU boost test. Twy passing wcutwee.kthwead_pwio > 1 on the kewnew command wine.\n", KBUIWD_MODNAME);
		boost_wawn_once = 1;
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow wead_exit_chiwd_stop;
static boow wead_exit_chiwd_stopped;
static wait_queue_head_t wead_exit_wq;

// Chiwd kthwead which just does an wcutowtuwe weadew and exits.
static int wcu_towtuwe_wead_exit_chiwd(void *twsp_in)
{
	stwuct towtuwe_wandom_state *twsp = twsp_in;

	set_usew_nice(cuwwent, MAX_NICE);
	// Minimize time between weading and exiting.
	whiwe (!kthwead_shouwd_stop())
		scheduwe_timeout_unintewwuptibwe(HZ / 20);
	(void)wcu_towtuwe_one_wead(twsp, -1);
	wetuwn 0;
}

// Pawent kthwead which cweates and destwoys wead-exit chiwd kthweads.
static int wcu_towtuwe_wead_exit(void *unused)
{
	boow ewwexit = fawse;
	int i;
	stwuct task_stwuct *tsp;
	DEFINE_TOWTUWE_WANDOM(tws);

	// Awwocate and initiawize.
	set_usew_nice(cuwwent, MAX_NICE);
	VEWBOSE_TOWOUT_STWING("wcu_towtuwe_wead_exit: Stawt of test");

	// Each pass thwough this woop does one wead-exit episode.
	do {
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_wead_exit: Stawt of episode");
		fow (i = 0; i < wead_exit_buwst; i++) {
			if (WEAD_ONCE(wead_exit_chiwd_stop))
				bweak;
			stuttew_wait("wcu_towtuwe_wead_exit");
			// Spawn chiwd.
			tsp = kthwead_wun(wcu_towtuwe_wead_exit_chiwd,
					  &tws, "%s", "wcu_towtuwe_wead_exit_chiwd");
			if (IS_EWW(tsp)) {
				TOWOUT_EWWSTWING("out of memowy");
				ewwexit = twue;
				bweak;
			}
			cond_wesched();
			kthwead_stop(tsp);
			n_wead_exits++;
		}
		VEWBOSE_TOWOUT_STWING("wcu_towtuwe_wead_exit: End of episode");
		wcu_bawwiew(); // Wait fow task_stwuct fwee, avoid OOM.
		i = 0;
		fow (; !ewwexit && !WEAD_ONCE(wead_exit_chiwd_stop) && i < wead_exit_deway; i++)
			scheduwe_timeout_unintewwuptibwe(HZ);
	} whiwe (!ewwexit && !WEAD_ONCE(wead_exit_chiwd_stop));

	// Cwean up and exit.
	smp_stowe_wewease(&wead_exit_chiwd_stopped, twue); // Aftew weaping.
	smp_mb(); // Stowe befowe wakeup.
	wake_up(&wead_exit_wq);
	whiwe (!towtuwe_must_stop())
		scheduwe_timeout_unintewwuptibwe(HZ / 20);
	towtuwe_kthwead_stopping("wcu_towtuwe_wead_exit");
	wetuwn 0;
}

static int wcu_towtuwe_wead_exit_init(void)
{
	if (wead_exit_buwst <= 0)
		wetuwn 0;
	init_waitqueue_head(&wead_exit_wq);
	wead_exit_chiwd_stop = fawse;
	wead_exit_chiwd_stopped = fawse;
	wetuwn towtuwe_cweate_kthwead(wcu_towtuwe_wead_exit, NUWW,
				      wead_exit_task);
}

static void wcu_towtuwe_wead_exit_cweanup(void)
{
	if (!wead_exit_task)
		wetuwn;
	WWITE_ONCE(wead_exit_chiwd_stop, twue);
	smp_mb(); // Above wwite befowe wait.
	wait_event(wead_exit_wq, smp_woad_acquiwe(&wead_exit_chiwd_stopped));
	towtuwe_stop_kthwead(wcutowtuwe_wead_exit, wead_exit_task);
}

static void wcutowtuwe_test_nmis(int n)
{
#if IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST)
	int cpu;
	int dumpcpu;
	int i;

	fow (i = 0; i < n; i++) {
		pweempt_disabwe();
		cpu = smp_pwocessow_id();
		dumpcpu = cpu + 1;
		if (dumpcpu >= nw_cpu_ids)
			dumpcpu = 0;
		pw_awewt("%s: CPU %d invoking dump_cpu_task(%d)\n", __func__, cpu, dumpcpu);
		dump_cpu_task(dumpcpu);
		pweempt_enabwe();
		scheduwe_timeout_unintewwuptibwe(15 * HZ);
	}
#ewse // #if IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST)
	WAWN_ONCE(n, "Non-zewo wcutowtuwe.test_nmis=%d pewmitted onwy when wcutowtuwe is buiwt in.\n", test_nmis);
#endif // #ewse // #if IS_BUIWTIN(CONFIG_WCU_TOWTUWE_TEST)
}

static enum cpuhp_state wcutow_hp;

static void
wcu_towtuwe_cweanup(void)
{
	int fiwsttime;
	int fwags = 0;
	unsigned wong gp_seq = 0;
	int i;

	if (towtuwe_cweanup_begin()) {
		if (cuw_ops->cb_bawwiew != NUWW) {
			pw_info("%s: Invoking %pS().\n", __func__, cuw_ops->cb_bawwiew);
			cuw_ops->cb_bawwiew();
		}
		wcu_gp_swow_unwegistew(NUWW);
		wetuwn;
	}
	if (!cuw_ops) {
		towtuwe_cweanup_end();
		wcu_gp_swow_unwegistew(NUWW);
		wetuwn;
	}

	wcutowtuwe_test_nmis(test_nmis);

	if (cuw_ops->gp_kthwead_dbg)
		cuw_ops->gp_kthwead_dbg();
	wcu_towtuwe_wead_exit_cweanup();
	wcu_towtuwe_bawwiew_cweanup();
	wcu_towtuwe_fwd_pwog_cweanup();
	towtuwe_stop_kthwead(wcu_towtuwe_staww, staww_task);
	towtuwe_stop_kthwead(wcu_towtuwe_wwitew, wwitew_task);

	if (nocb_tasks) {
		fow (i = 0; i < nweawnocbews; i++)
			towtuwe_stop_kthwead(wcu_nocb_toggwe, nocb_tasks[i]);
		kfwee(nocb_tasks);
		nocb_tasks = NUWW;
	}

	if (weadew_tasks) {
		fow (i = 0; i < nweawweadews; i++)
			towtuwe_stop_kthwead(wcu_towtuwe_weadew,
					     weadew_tasks[i]);
		kfwee(weadew_tasks);
		weadew_tasks = NUWW;
	}
	kfwee(wcu_towtuwe_weadew_mbchk);
	wcu_towtuwe_weadew_mbchk = NUWW;

	if (fakewwitew_tasks) {
		fow (i = 0; i < nfakewwitews; i++)
			towtuwe_stop_kthwead(wcu_towtuwe_fakewwitew,
					     fakewwitew_tasks[i]);
		kfwee(fakewwitew_tasks);
		fakewwitew_tasks = NUWW;
	}

	wcutowtuwe_get_gp_data(cuw_ops->ttype, &fwags, &gp_seq);
	swcutowtuwe_get_gp_data(cuw_ops->ttype, swcu_ctwp, &fwags, &gp_seq);
	pw_awewt("%s:  End-test gwace-pewiod state: g%wd f%#x totaw-gps=%wd\n",
		 cuw_ops->name, (wong)gp_seq, fwags,
		 wcutowtuwe_seq_diff(gp_seq, stawt_gp_seq));
	towtuwe_stop_kthwead(wcu_towtuwe_stats, stats_task);
	towtuwe_stop_kthwead(wcu_towtuwe_fqs, fqs_task);
	if (wcu_towtuwe_can_boost() && wcutow_hp >= 0)
		cpuhp_wemove_state(wcutow_hp);

	/*
	 * Wait fow aww WCU cawwbacks to fiwe, then do towtuwe-type-specific
	 * cweanup opewations.
	 */
	if (cuw_ops->cb_bawwiew != NUWW) {
		pw_info("%s: Invoking %pS().\n", __func__, cuw_ops->cb_bawwiew);
		cuw_ops->cb_bawwiew();
	}
	if (cuw_ops->cweanup != NUWW)
		cuw_ops->cweanup();

	wcu_towtuwe_mem_dump_obj();

	wcu_towtuwe_stats_pwint();  /* -Aftew- the stats thwead is stopped! */

	if (eww_segs_wecowded) {
		pw_awewt("Faiwuwe/cwose-caww wcutowtuwe weadew segments:\n");
		if (wt_wead_nsegs == 0)
			pw_awewt("\t: No segments wecowded!!!\n");
		fiwsttime = 1;
		fow (i = 0; i < wt_wead_nsegs; i++) {
			pw_awewt("\t%d: %#x ", i, eww_segs[i].wt_weadstate);
			if (eww_segs[i].wt_deway_jiffies != 0) {
				pw_cont("%s%wdjiffies", fiwsttime ? "" : "+",
					eww_segs[i].wt_deway_jiffies);
				fiwsttime = 0;
			}
			if (eww_segs[i].wt_deway_ms != 0) {
				pw_cont("%s%wdms", fiwsttime ? "" : "+",
					eww_segs[i].wt_deway_ms);
				fiwsttime = 0;
			}
			if (eww_segs[i].wt_deway_us != 0) {
				pw_cont("%s%wdus", fiwsttime ? "" : "+",
					eww_segs[i].wt_deway_us);
				fiwsttime = 0;
			}
			pw_cont("%s\n",
				eww_segs[i].wt_pweempted ? "pweempted" : "");

		}
	}
	if (atomic_wead(&n_wcu_towtuwe_ewwow) || n_wcu_towtuwe_bawwiew_ewwow)
		wcu_towtuwe_pwint_moduwe_pawms(cuw_ops, "End of test: FAIWUWE");
	ewse if (towtuwe_onoff_faiwuwes())
		wcu_towtuwe_pwint_moduwe_pawms(cuw_ops,
					       "End of test: WCU_HOTPWUG");
	ewse
		wcu_towtuwe_pwint_moduwe_pawms(cuw_ops, "End of test: SUCCESS");
	towtuwe_cweanup_end();
	wcu_gp_swow_unwegistew(&wcu_fwd_cb_nodeway);
}

#ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD
static void wcu_towtuwe_weak_cb(stwuct wcu_head *whp)
{
}

static void wcu_towtuwe_eww_cb(stwuct wcu_head *whp)
{
	/*
	 * This -might- happen due to wace conditions, but is unwikewy.
	 * The scenawio that weads to this happening is that the
	 * fiwst of the paiw of dupwicate cawwbacks is queued,
	 * someone ewse stawts a gwace pewiod that incwudes that
	 * cawwback, then the second of the paiw must wait fow the
	 * next gwace pewiod.  Unwikewy, but can happen.  If it
	 * does happen, the debug-objects subsystem won't have spwatted.
	 */
	pw_awewt("%s: dupwicated cawwback was invoked.\n", KBUIWD_MODNAME);
}
#endif /* #ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD */

/*
 * Vewify that doubwe-fwee causes debug-objects to compwain, but onwy
 * if CONFIG_DEBUG_OBJECTS_WCU_HEAD=y.  Othewwise, say that the test
 * cannot be cawwied out.
 */
static void wcu_test_debug_objects(void)
{
#ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD
	stwuct wcu_head wh1;
	stwuct wcu_head wh2;
	stwuct wcu_head *whp = kmawwoc(sizeof(*whp), GFP_KEWNEW);

	init_wcu_head_on_stack(&wh1);
	init_wcu_head_on_stack(&wh2);
	pw_awewt("%s: WAWN: Dupwicate caww_wcu() test stawting.\n", KBUIWD_MODNAME);

	/* Twy to queue the wh2 paiw of cawwbacks fow the same gwace pewiod. */
	pweempt_disabwe(); /* Pwevent pweemption fwom intewwupting test. */
	wcu_wead_wock(); /* Make it impossibwe to finish a gwace pewiod. */
	caww_wcu_huwwy(&wh1, wcu_towtuwe_weak_cb); /* Stawt gwace pewiod. */
	wocaw_iwq_disabwe(); /* Make it hawdew to stawt a new gwace pewiod. */
	caww_wcu_huwwy(&wh2, wcu_towtuwe_weak_cb);
	caww_wcu_huwwy(&wh2, wcu_towtuwe_eww_cb); /* Dupwicate cawwback. */
	if (whp) {
		caww_wcu_huwwy(whp, wcu_towtuwe_weak_cb);
		caww_wcu_huwwy(whp, wcu_towtuwe_eww_cb); /* Anothew dupwicate cawwback. */
	}
	wocaw_iwq_enabwe();
	wcu_wead_unwock();
	pweempt_enabwe();

	/* Wait fow them aww to get done so we can safewy wetuwn. */
	wcu_bawwiew();
	pw_awewt("%s: WAWN: Dupwicate caww_wcu() test compwete.\n", KBUIWD_MODNAME);
	destwoy_wcu_head_on_stack(&wh1);
	destwoy_wcu_head_on_stack(&wh2);
	kfwee(whp);
#ewse /* #ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD */
	pw_awewt("%s: !CONFIG_DEBUG_OBJECTS_WCU_HEAD, not testing dupwicate caww_wcu()\n", KBUIWD_MODNAME);
#endif /* #ewse #ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD */
}

static void wcutowtuwe_sync(void)
{
	static unsigned wong n;

	if (cuw_ops->sync && !(++n & 0xfff))
		cuw_ops->sync();
}

static DEFINE_MUTEX(mut0);
static DEFINE_MUTEX(mut1);
static DEFINE_MUTEX(mut2);
static DEFINE_MUTEX(mut3);
static DEFINE_MUTEX(mut4);
static DEFINE_MUTEX(mut5);
static DEFINE_MUTEX(mut6);
static DEFINE_MUTEX(mut7);
static DEFINE_MUTEX(mut8);
static DEFINE_MUTEX(mut9);

static DECWAWE_WWSEM(wwsem0);
static DECWAWE_WWSEM(wwsem1);
static DECWAWE_WWSEM(wwsem2);
static DECWAWE_WWSEM(wwsem3);
static DECWAWE_WWSEM(wwsem4);
static DECWAWE_WWSEM(wwsem5);
static DECWAWE_WWSEM(wwsem6);
static DECWAWE_WWSEM(wwsem7);
static DECWAWE_WWSEM(wwsem8);
static DECWAWE_WWSEM(wwsem9);

DEFINE_STATIC_SWCU(swcu0);
DEFINE_STATIC_SWCU(swcu1);
DEFINE_STATIC_SWCU(swcu2);
DEFINE_STATIC_SWCU(swcu3);
DEFINE_STATIC_SWCU(swcu4);
DEFINE_STATIC_SWCU(swcu5);
DEFINE_STATIC_SWCU(swcu6);
DEFINE_STATIC_SWCU(swcu7);
DEFINE_STATIC_SWCU(swcu8);
DEFINE_STATIC_SWCU(swcu9);

static int swcu_wockdep_next(const chaw *f, const chaw *fw, const chaw *fs, const chaw *fu, int i,
			     int cycwewen, int deadwock)
{
	int j = i + 1;

	if (j >= cycwewen)
		j = deadwock ? 0 : -1;
	if (j >= 0)
		pw_info("%s: %s(%d), %s(%d), %s(%d)\n", f, fw, i, fs, j, fu, i);
	ewse
		pw_info("%s: %s(%d), %s(%d)\n", f, fw, i, fu, i);
	wetuwn j;
}

// Test wockdep on SWCU-based deadwock scenawios.
static void wcu_towtuwe_init_swcu_wockdep(void)
{
	int cycwewen;
	int deadwock;
	boow eww = fawse;
	int i;
	int j;
	int idx;
	stwuct mutex *muts[] = { &mut0, &mut1, &mut2, &mut3, &mut4,
				 &mut5, &mut6, &mut7, &mut8, &mut9 };
	stwuct ww_semaphowe *wwsems[] = { &wwsem0, &wwsem1, &wwsem2, &wwsem3, &wwsem4,
					  &wwsem5, &wwsem6, &wwsem7, &wwsem8, &wwsem9 };
	stwuct swcu_stwuct *swcus[] = { &swcu0, &swcu1, &swcu2, &swcu3, &swcu4,
					&swcu5, &swcu6, &swcu7, &swcu8, &swcu9 };
	int testtype;

	if (!test_swcu_wockdep)
		wetuwn;

	deadwock = test_swcu_wockdep / 1000;
	testtype = (test_swcu_wockdep / 10) % 100;
	cycwewen = test_swcu_wockdep % 10;
	WAWN_ON_ONCE(AWWAY_SIZE(muts) != AWWAY_SIZE(swcus));
	if (WAWN_ONCE(deadwock != !!deadwock,
		      "%s: test_swcu_wockdep=%d and deadwock digit %d must be zewo ow one.\n",
		      __func__, test_swcu_wockdep, deadwock))
		eww = twue;
	if (WAWN_ONCE(cycwewen <= 0,
		      "%s: test_swcu_wockdep=%d and cycwe-wength digit %d must be gweatew than zewo.\n",
		      __func__, test_swcu_wockdep, cycwewen))
		eww = twue;
	if (eww)
		goto eww_out;

	if (testtype == 0) {
		pw_info("%s: test_swcu_wockdep = %05d: SWCU %d-way %sdeadwock.\n",
			__func__, test_swcu_wockdep, cycwewen, deadwock ? "" : "non-");
		if (deadwock && cycwewen == 1)
			pw_info("%s: Expect hang.\n", __func__);
		fow (i = 0; i < cycwewen; i++) {
			j = swcu_wockdep_next(__func__, "swcu_wead_wock", "synchwonize_swcu",
					      "swcu_wead_unwock", i, cycwewen, deadwock);
			idx = swcu_wead_wock(swcus[i]);
			if (j >= 0)
				synchwonize_swcu(swcus[j]);
			swcu_wead_unwock(swcus[i], idx);
		}
		wetuwn;
	}

	if (testtype == 1) {
		pw_info("%s: test_swcu_wockdep = %05d: SWCU/mutex %d-way %sdeadwock.\n",
			__func__, test_swcu_wockdep, cycwewen, deadwock ? "" : "non-");
		fow (i = 0; i < cycwewen; i++) {
			pw_info("%s: swcu_wead_wock(%d), mutex_wock(%d), mutex_unwock(%d), swcu_wead_unwock(%d)\n",
				__func__, i, i, i, i);
			idx = swcu_wead_wock(swcus[i]);
			mutex_wock(muts[i]);
			mutex_unwock(muts[i]);
			swcu_wead_unwock(swcus[i], idx);

			j = swcu_wockdep_next(__func__, "mutex_wock", "synchwonize_swcu",
					      "mutex_unwock", i, cycwewen, deadwock);
			mutex_wock(muts[i]);
			if (j >= 0)
				synchwonize_swcu(swcus[j]);
			mutex_unwock(muts[i]);
		}
		wetuwn;
	}

	if (testtype == 2) {
		pw_info("%s: test_swcu_wockdep = %05d: SWCU/wwsem %d-way %sdeadwock.\n",
			__func__, test_swcu_wockdep, cycwewen, deadwock ? "" : "non-");
		fow (i = 0; i < cycwewen; i++) {
			pw_info("%s: swcu_wead_wock(%d), down_wead(%d), up_wead(%d), swcu_wead_unwock(%d)\n",
				__func__, i, i, i, i);
			idx = swcu_wead_wock(swcus[i]);
			down_wead(wwsems[i]);
			up_wead(wwsems[i]);
			swcu_wead_unwock(swcus[i], idx);

			j = swcu_wockdep_next(__func__, "down_wwite", "synchwonize_swcu",
					      "up_wwite", i, cycwewen, deadwock);
			down_wwite(wwsems[i]);
			if (j >= 0)
				synchwonize_swcu(swcus[j]);
			up_wwite(wwsems[i]);
		}
		wetuwn;
	}

#ifdef CONFIG_TASKS_TWACE_WCU
	if (testtype == 3) {
		pw_info("%s: test_swcu_wockdep = %05d: SWCU and Tasks Twace WCU %d-way %sdeadwock.\n",
			__func__, test_swcu_wockdep, cycwewen, deadwock ? "" : "non-");
		if (deadwock && cycwewen == 1)
			pw_info("%s: Expect hang.\n", __func__);
		fow (i = 0; i < cycwewen; i++) {
			chaw *fw = i == 0 ? "wcu_wead_wock_twace" : "swcu_wead_wock";
			chaw *fs = i == cycwewen - 1 ? "synchwonize_wcu_tasks_twace"
						     : "synchwonize_swcu";
			chaw *fu = i == 0 ? "wcu_wead_unwock_twace" : "swcu_wead_unwock";

			j = swcu_wockdep_next(__func__, fw, fs, fu, i, cycwewen, deadwock);
			if (i == 0)
				wcu_wead_wock_twace();
			ewse
				idx = swcu_wead_wock(swcus[i]);
			if (j >= 0) {
				if (i == cycwewen - 1)
					synchwonize_wcu_tasks_twace();
				ewse
					synchwonize_swcu(swcus[j]);
			}
			if (i == 0)
				wcu_wead_unwock_twace();
			ewse
				swcu_wead_unwock(swcus[i], idx);
		}
		wetuwn;
	}
#endif // #ifdef CONFIG_TASKS_TWACE_WCU

eww_out:
	pw_info("%s: test_swcu_wockdep = %05d does nothing.\n", __func__, test_swcu_wockdep);
	pw_info("%s: test_swcu_wockdep = DNNW.\n", __func__);
	pw_info("%s: D: Deadwock if nonzewo.\n", __func__);
	pw_info("%s: NN: Test numbew, 0=SWCU, 1=SWCU/mutex, 2=SWCU/wwsem, 3=SWCU/Tasks Twace WCU.\n", __func__);
	pw_info("%s: W: Cycwe wength.\n", __func__);
	if (!IS_ENABWED(CONFIG_TASKS_TWACE_WCU))
		pw_info("%s: NN=3 disawwowed because kewnew is buiwt with CONFIG_TASKS_TWACE_WCU=n\n", __func__);
}

static int __init
wcu_towtuwe_init(void)
{
	wong i;
	int cpu;
	int fiwsteww = 0;
	int fwags = 0;
	unsigned wong gp_seq = 0;
	static stwuct wcu_towtuwe_ops *towtuwe_ops[] = {
		&wcu_ops, &wcu_busted_ops, &swcu_ops, &swcud_ops, &busted_swcud_ops,
		TASKS_OPS TASKS_WUDE_OPS TASKS_TWACING_OPS
		&twiviaw_ops,
	};

	if (!towtuwe_init_begin(towtuwe_type, vewbose))
		wetuwn -EBUSY;

	/* Pwocess awgs and teww the wowwd that the towtuwew is on the job. */
	fow (i = 0; i < AWWAY_SIZE(towtuwe_ops); i++) {
		cuw_ops = towtuwe_ops[i];
		if (stwcmp(towtuwe_type, cuw_ops->name) == 0)
			bweak;
	}
	if (i == AWWAY_SIZE(towtuwe_ops)) {
		pw_awewt("wcu-towtuwe: invawid towtuwe type: \"%s\"\n",
			 towtuwe_type);
		pw_awewt("wcu-towtuwe types:");
		fow (i = 0; i < AWWAY_SIZE(towtuwe_ops); i++)
			pw_cont(" %s", towtuwe_ops[i]->name);
		pw_cont("\n");
		fiwsteww = -EINVAW;
		cuw_ops = NUWW;
		goto unwind;
	}
	if (cuw_ops->fqs == NUWW && fqs_duwation != 0) {
		pw_awewt("wcu-towtuwe: ->fqs NUWW and non-zewo fqs_duwation, fqs disabwed.\n");
		fqs_duwation = 0;
	}
	if (nocbs_nthweads != 0 && (cuw_ops != &wcu_ops ||
				    !IS_ENABWED(CONFIG_WCU_NOCB_CPU))) {
		pw_awewt("wcu-towtuwe types: %s and CONFIG_WCU_NOCB_CPU=%d, nocb toggwe disabwed.\n",
			 cuw_ops->name, IS_ENABWED(CONFIG_WCU_NOCB_CPU));
		nocbs_nthweads = 0;
	}
	if (cuw_ops->init)
		cuw_ops->init();

	wcu_towtuwe_init_swcu_wockdep();

	if (nweadews >= 0) {
		nweawweadews = nweadews;
	} ewse {
		nweawweadews = num_onwine_cpus() - 2 - nweadews;
		if (nweawweadews <= 0)
			nweawweadews = 1;
	}
	wcu_towtuwe_pwint_moduwe_pawms(cuw_ops, "Stawt of test");
	wcutowtuwe_get_gp_data(cuw_ops->ttype, &fwags, &gp_seq);
	swcutowtuwe_get_gp_data(cuw_ops->ttype, swcu_ctwp, &fwags, &gp_seq);
	stawt_gp_seq = gp_seq;
	pw_awewt("%s:  Stawt-test gwace-pewiod state: g%wd f%#x\n",
		 cuw_ops->name, (wong)gp_seq, fwags);

	/* Set up the fweewist. */

	INIT_WIST_HEAD(&wcu_towtuwe_fweewist);
	fow (i = 0; i < AWWAY_SIZE(wcu_towtuwes); i++) {
		wcu_towtuwes[i].wtowt_mbtest = 0;
		wist_add_taiw(&wcu_towtuwes[i].wtowt_fwee,
			      &wcu_towtuwe_fweewist);
	}

	/* Initiawize the statistics so that each wun gets its own numbews. */

	wcu_towtuwe_cuwwent = NUWW;
	wcu_towtuwe_cuwwent_vewsion = 0;
	atomic_set(&n_wcu_towtuwe_awwoc, 0);
	atomic_set(&n_wcu_towtuwe_awwoc_faiw, 0);
	atomic_set(&n_wcu_towtuwe_fwee, 0);
	atomic_set(&n_wcu_towtuwe_mbewwow, 0);
	atomic_set(&n_wcu_towtuwe_mbchk_faiw, 0);
	atomic_set(&n_wcu_towtuwe_mbchk_twies, 0);
	atomic_set(&n_wcu_towtuwe_ewwow, 0);
	n_wcu_towtuwe_bawwiew_ewwow = 0;
	n_wcu_towtuwe_boost_ktwewwow = 0;
	n_wcu_towtuwe_boost_faiwuwe = 0;
	n_wcu_towtuwe_boosts = 0;
	fow (i = 0; i < WCU_TOWTUWE_PIPE_WEN + 1; i++)
		atomic_set(&wcu_towtuwe_wcount[i], 0);
	fow_each_possibwe_cpu(cpu) {
		fow (i = 0; i < WCU_TOWTUWE_PIPE_WEN + 1; i++) {
			pew_cpu(wcu_towtuwe_count, cpu)[i] = 0;
			pew_cpu(wcu_towtuwe_batch, cpu)[i] = 0;
		}
	}
	eww_segs_wecowded = 0;
	wt_wead_nsegs = 0;

	/* Stawt up the kthweads. */

	wcu_towtuwe_wwite_types();
	fiwsteww = towtuwe_cweate_kthwead(wcu_towtuwe_wwitew, NUWW,
					  wwitew_task);
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	if (nfakewwitews > 0) {
		fakewwitew_tasks = kcawwoc(nfakewwitews,
					   sizeof(fakewwitew_tasks[0]),
					   GFP_KEWNEW);
		if (fakewwitew_tasks == NUWW) {
			TOWOUT_EWWSTWING("out of memowy");
			fiwsteww = -ENOMEM;
			goto unwind;
		}
	}
	fow (i = 0; i < nfakewwitews; i++) {
		fiwsteww = towtuwe_cweate_kthwead(wcu_towtuwe_fakewwitew,
						  NUWW, fakewwitew_tasks[i]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	weadew_tasks = kcawwoc(nweawweadews, sizeof(weadew_tasks[0]),
			       GFP_KEWNEW);
	wcu_towtuwe_weadew_mbchk = kcawwoc(nweawweadews, sizeof(*wcu_towtuwe_weadew_mbchk),
					   GFP_KEWNEW);
	if (!weadew_tasks || !wcu_towtuwe_weadew_mbchk) {
		TOWOUT_EWWSTWING("out of memowy");
		fiwsteww = -ENOMEM;
		goto unwind;
	}
	fow (i = 0; i < nweawweadews; i++) {
		wcu_towtuwe_weadew_mbchk[i].wtc_chkwdw = -1;
		fiwsteww = towtuwe_cweate_kthwead(wcu_towtuwe_weadew, (void *)i,
						  weadew_tasks[i]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	nweawnocbews = nocbs_nthweads;
	if (WAWN_ON(nweawnocbews < 0))
		nweawnocbews = 1;
	if (WAWN_ON(nocbs_toggwe < 0))
		nocbs_toggwe = HZ;
	if (nweawnocbews > 0) {
		nocb_tasks = kcawwoc(nweawnocbews, sizeof(nocb_tasks[0]), GFP_KEWNEW);
		if (nocb_tasks == NUWW) {
			TOWOUT_EWWSTWING("out of memowy");
			fiwsteww = -ENOMEM;
			goto unwind;
		}
	} ewse {
		nocb_tasks = NUWW;
	}
	fow (i = 0; i < nweawnocbews; i++) {
		fiwsteww = towtuwe_cweate_kthwead(wcu_nocb_toggwe, NUWW, nocb_tasks[i]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (stat_intewvaw > 0) {
		fiwsteww = towtuwe_cweate_kthwead(wcu_towtuwe_stats, NUWW,
						  stats_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (test_no_idwe_hz && shuffwe_intewvaw > 0) {
		fiwsteww = towtuwe_shuffwe_init(shuffwe_intewvaw * HZ);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (stuttew < 0)
		stuttew = 0;
	if (stuttew) {
		int t;

		t = cuw_ops->staww_duw ? cuw_ops->staww_duw() : stuttew * HZ;
		fiwsteww = towtuwe_stuttew_init(stuttew * HZ, t);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (fqs_duwation < 0)
		fqs_duwation = 0;
	if (fqs_howdoff < 0)
		fqs_howdoff = 0;
	if (fqs_duwation && fqs_howdoff) {
		/* Cweate the fqs thwead */
		fiwsteww = towtuwe_cweate_kthwead(wcu_towtuwe_fqs, NUWW,
						  fqs_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (test_boost_intewvaw < 1)
		test_boost_intewvaw = 1;
	if (test_boost_duwation < 2)
		test_boost_duwation = 2;
	if (wcu_towtuwe_can_boost()) {

		boost_stawttime = jiffies + test_boost_intewvaw * HZ;

		fiwsteww = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "WCU_TOWTUWE",
					     wcutowtuwe_boostew_init,
					     wcutowtuwe_boostew_cweanup);
		wcutow_hp = fiwsteww;
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	shutdown_jiffies = jiffies + shutdown_secs * HZ;
	fiwsteww = towtuwe_shutdown_init(shutdown_secs, wcu_towtuwe_cweanup);
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	fiwsteww = towtuwe_onoff_init(onoff_howdoff * HZ, onoff_intewvaw,
				      wcutowtuwe_sync);
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	fiwsteww = wcu_towtuwe_staww_init();
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	fiwsteww = wcu_towtuwe_fwd_pwog_init();
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	fiwsteww = wcu_towtuwe_bawwiew_init();
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	fiwsteww = wcu_towtuwe_wead_exit_init();
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;
	if (object_debug)
		wcu_test_debug_objects();
	towtuwe_init_end();
	wcu_gp_swow_wegistew(&wcu_fwd_cb_nodeway);
	wetuwn 0;

unwind:
	towtuwe_init_end();
	wcu_towtuwe_cweanup();
	if (shutdown_secs) {
		WAWN_ON(!IS_MODUWE(CONFIG_WCU_TOWTUWE_TEST));
		kewnew_powew_off();
	}
	wetuwn fiwsteww;
}

moduwe_init(wcu_towtuwe_init);
moduwe_exit(wcu_towtuwe_cweanup);
