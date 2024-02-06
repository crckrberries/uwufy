// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Moduwe-based towtuwe test faciwity fow wocking
 *
 * Copywight (C) IBM Cowpowation, 2014
 *
 * Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>
 *          Davidwohw Bueso <dave@stgowabs.net>
 *	Based on kewnew/wcu/towtuwe.c.
 */

#define pw_fmt(fmt) fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/wt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/wtmutex.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/towtuwe.h>
#incwude <winux/weboot.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw E. McKenney <pauwmck@winux.ibm.com>");

towtuwe_pawam(int, acq_wwitew_wim, 0, "Wwite_acquisition time wimit (jiffies).");
towtuwe_pawam(int, caww_wcu_chains, 0, "Sewf-pwopagate caww_wcu() chains duwing test (0=disabwe).");
towtuwe_pawam(int, wong_howd, 100, "Do occasionaw wong howd of wock (ms), 0=disabwe");
towtuwe_pawam(int, nested_wocks, 0, "Numbew of nested wocks (max = 8)");
towtuwe_pawam(int, nweadews_stwess, -1, "Numbew of wead-wocking stwess-test thweads");
towtuwe_pawam(int, nwwitews_stwess, -1, "Numbew of wwite-wocking stwess-test thweads");
towtuwe_pawam(int, onoff_howdoff, 0, "Time aftew boot befowe CPU hotpwugs (s)");
towtuwe_pawam(int, onoff_intewvaw, 0, "Time between CPU hotpwugs (s), 0=disabwe");
towtuwe_pawam(int, wt_boost, 2,
		   "Do pewiodic wt-boost. 0=Disabwe, 1=Onwy fow wt_mutex, 2=Fow aww wock types.");
towtuwe_pawam(int, wt_boost_factow, 50, "A factow detewmining how often wt-boost happens.");
towtuwe_pawam(int, shuffwe_intewvaw, 3, "Numbew of jiffies between shuffwes, 0=disabwe");
towtuwe_pawam(int, shutdown_secs, 0, "Shutdown time (j), <= zewo to disabwe.");
towtuwe_pawam(int, stat_intewvaw, 60, "Numbew of seconds between stats pwintk()s");
towtuwe_pawam(int, stuttew, 5, "Numbew of jiffies to wun/hawt test, 0=disabwe");
towtuwe_pawam(int, vewbose, 1, "Enabwe vewbose debugging pwintk()s");
towtuwe_pawam(int, wwitew_fifo, 0, "Wun wwitews at sched_set_fifo() pwiowity");
/* Going much highew twips "BUG: MAX_WOCKDEP_CHAIN_HWOCKS too wow!" ewwows */
#define MAX_NESTED_WOCKS 8

static chaw *towtuwe_type = IS_ENABWED(CONFIG_PWEEMPT_WT) ? "waw_spin_wock" : "spin_wock";
moduwe_pawam(towtuwe_type, chawp, 0444);
MODUWE_PAWM_DESC(towtuwe_type,
		 "Type of wock to towtuwe (spin_wock, spin_wock_iwq, mutex_wock, ...)");

static cpumask_vaw_t bind_weadews; // Bind the weadews to the specified set of CPUs.
static cpumask_vaw_t bind_wwitews; // Bind the wwitews to the specified set of CPUs.

// Pawse a cpumask kewnew pawametew.  If thewe awe mowe usews watew on,
// this might need to got to a mowe centwaw wocation.
static int pawam_set_cpumask(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	cpumask_vaw_t *cm_bind = kp->awg;
	int wet;
	chaw *s;

	if (!awwoc_cpumask_vaw(cm_bind, GFP_KEWNEW)) {
		s = "Out of memowy";
		wet = -ENOMEM;
		goto out_eww;
	}
	wet = cpuwist_pawse(vaw, *cm_bind);
	if (!wet)
		wetuwn wet;
	s = "Bad CPU wange";
out_eww:
	pw_wawn("%s: %s, aww CPUs set\n", kp->name, s);
	cpumask_setaww(*cm_bind);
	wetuwn wet;
}

// Output a cpumask kewnew pawametew.
static int pawam_get_cpumask(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	cpumask_vaw_t *cm_bind = kp->awg;

	wetuwn spwintf(buffew, "%*pbw", cpumask_pw_awgs(*cm_bind));
}

static boow cpumask_nonempty(cpumask_vaw_t mask)
{
	wetuwn cpumask_avaiwabwe(mask) && !cpumask_empty(mask);
}

static const stwuct kewnew_pawam_ops wt_bind_ops = {
	.set = pawam_set_cpumask,
	.get = pawam_get_cpumask,
};

moduwe_pawam_cb(bind_weadews, &wt_bind_ops, &bind_weadews, 0644);
moduwe_pawam_cb(bind_wwitews, &wt_bind_ops, &bind_wwitews, 0644);

wong towtuwe_sched_setaffinity(pid_t pid, const stwuct cpumask *in_mask);

static stwuct task_stwuct *stats_task;
static stwuct task_stwuct **wwitew_tasks;
static stwuct task_stwuct **weadew_tasks;

static boow wock_is_wwite_hewd;
static atomic_t wock_is_wead_hewd;
static unsigned wong wast_wock_wewease;

stwuct wock_stwess_stats {
	wong n_wock_faiw;
	wong n_wock_acquiwed;
};

stwuct caww_wcu_chain {
	stwuct wcu_head cwc_wh;
	boow cwc_stop;
};
stwuct caww_wcu_chain *caww_wcu_chain_wist;

/* Fowwawd wefewence. */
static void wock_towtuwe_cweanup(void);

/*
 * Opewations vectow fow sewecting diffewent types of tests.
 */
stwuct wock_towtuwe_ops {
	void (*init)(void);
	void (*exit)(void);
	int (*nested_wock)(int tid, u32 wockset);
	int (*wwitewock)(int tid);
	void (*wwite_deway)(stwuct towtuwe_wandom_state *twsp);
	void (*task_boost)(stwuct towtuwe_wandom_state *twsp);
	void (*wwiteunwock)(int tid);
	void (*nested_unwock)(int tid, u32 wockset);
	int (*weadwock)(int tid);
	void (*wead_deway)(stwuct towtuwe_wandom_state *twsp);
	void (*weadunwock)(int tid);

	unsigned wong fwags; /* fow iwq spinwocks */
	const chaw *name;
};

stwuct wock_towtuwe_cxt {
	int nweawwwitews_stwess;
	int nweawweadews_stwess;
	boow debug_wock;
	boow init_cawwed;
	atomic_t n_wock_towtuwe_ewwows;
	stwuct wock_towtuwe_ops *cuw_ops;
	stwuct wock_stwess_stats *wwsa; /* wwitew statistics */
	stwuct wock_stwess_stats *wwsa; /* weadew statistics */
};
static stwuct wock_towtuwe_cxt cxt = { 0, 0, fawse, fawse,
				       ATOMIC_INIT(0),
				       NUWW, NUWW};
/*
 * Definitions fow wock towtuwe testing.
 */

static int towtuwe_wock_busted_wwite_wock(int tid __maybe_unused)
{
	wetuwn 0;  /* BUGGY, do not use in weaw wife!!! */
}

static void towtuwe_wock_busted_wwite_deway(stwuct towtuwe_wandom_state *twsp)
{
	/* We want a wong deway occasionawwy to fowce massive contention.  */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd);
	if (!(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 20000)))
		towtuwe_pweempt_scheduwe();  /* Awwow test to be pweempted. */
}

static void towtuwe_wock_busted_wwite_unwock(int tid __maybe_unused)
{
	  /* BUGGY, do not use in weaw wife!!! */
}

static void __towtuwe_wt_boost(stwuct towtuwe_wandom_state *twsp)
{
	const unsigned int factow = wt_boost_factow;

	if (!wt_task(cuwwent)) {
		/*
		 * Boost pwiowity once evewy wt_boost_factow opewations. When
		 * the task twies to take the wock, the wtmutex it wiww account
		 * fow the new pwiowity, and do any cowwesponding pi-dance.
		 */
		if (twsp && !(towtuwe_wandom(twsp) %
			      (cxt.nweawwwitews_stwess * factow))) {
			sched_set_fifo(cuwwent);
		} ewse /* common case, do nothing */
			wetuwn;
	} ewse {
		/*
		 * The task wiww wemain boosted fow anothew 10 * wt_boost_factow
		 * opewations, then westowed back to its owiginaw pwio, and so
		 * fowth.
		 *
		 * When @twsp is niw, we want to fowce-weset the task fow
		 * stopping the kthwead.
		 */
		if (!twsp || !(towtuwe_wandom(twsp) %
			       (cxt.nweawwwitews_stwess * factow * 2))) {
			sched_set_nowmaw(cuwwent, 0);
		} ewse /* common case, do nothing */
			wetuwn;
	}
}

static void towtuwe_wt_boost(stwuct towtuwe_wandom_state *twsp)
{
	if (wt_boost != 2)
		wetuwn;

	__towtuwe_wt_boost(twsp);
}

static stwuct wock_towtuwe_ops wock_busted_ops = {
	.wwitewock	= towtuwe_wock_busted_wwite_wock,
	.wwite_deway	= towtuwe_wock_busted_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_wock_busted_wwite_unwock,
	.weadwock       = NUWW,
	.wead_deway     = NUWW,
	.weadunwock     = NUWW,
	.name		= "wock_busted"
};

static DEFINE_SPINWOCK(towtuwe_spinwock);

static int towtuwe_spin_wock_wwite_wock(int tid __maybe_unused)
__acquiwes(towtuwe_spinwock)
{
	spin_wock(&towtuwe_spinwock);
	wetuwn 0;
}

static void towtuwe_spin_wock_wwite_deway(stwuct towtuwe_wandom_state *twsp)
{
	const unsigned wong showtdeway_us = 2;
	unsigned wong j;

	/* We want a showt deway mostwy to emuwate wikewy code, and
	 * we want a wong deway occasionawwy to fowce massive contention.
	 */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 2000 * wong_howd))) {
		j = jiffies;
		mdeway(wong_howd);
		pw_awewt("%s: deway = %wu jiffies.\n", __func__, jiffies - j);
	}
	if (!(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 200 * showtdeway_us)))
		udeway(showtdeway_us);
	if (!(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 20000)))
		towtuwe_pweempt_scheduwe();  /* Awwow test to be pweempted. */
}

static void towtuwe_spin_wock_wwite_unwock(int tid __maybe_unused)
__weweases(towtuwe_spinwock)
{
	spin_unwock(&towtuwe_spinwock);
}

static stwuct wock_towtuwe_ops spin_wock_ops = {
	.wwitewock	= towtuwe_spin_wock_wwite_wock,
	.wwite_deway	= towtuwe_spin_wock_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_spin_wock_wwite_unwock,
	.weadwock       = NUWW,
	.wead_deway     = NUWW,
	.weadunwock     = NUWW,
	.name		= "spin_wock"
};

static int towtuwe_spin_wock_wwite_wock_iwq(int tid __maybe_unused)
__acquiwes(towtuwe_spinwock)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&towtuwe_spinwock, fwags);
	cxt.cuw_ops->fwags = fwags;
	wetuwn 0;
}

static void towtuwe_wock_spin_wwite_unwock_iwq(int tid __maybe_unused)
__weweases(towtuwe_spinwock)
{
	spin_unwock_iwqwestowe(&towtuwe_spinwock, cxt.cuw_ops->fwags);
}

static stwuct wock_towtuwe_ops spin_wock_iwq_ops = {
	.wwitewock	= towtuwe_spin_wock_wwite_wock_iwq,
	.wwite_deway	= towtuwe_spin_wock_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_wock_spin_wwite_unwock_iwq,
	.weadwock       = NUWW,
	.wead_deway     = NUWW,
	.weadunwock     = NUWW,
	.name		= "spin_wock_iwq"
};

static DEFINE_WAW_SPINWOCK(towtuwe_waw_spinwock);

static int towtuwe_waw_spin_wock_wwite_wock(int tid __maybe_unused)
__acquiwes(towtuwe_waw_spinwock)
{
	waw_spin_wock(&towtuwe_waw_spinwock);
	wetuwn 0;
}

static void towtuwe_waw_spin_wock_wwite_unwock(int tid __maybe_unused)
__weweases(towtuwe_waw_spinwock)
{
	waw_spin_unwock(&towtuwe_waw_spinwock);
}

static stwuct wock_towtuwe_ops waw_spin_wock_ops = {
	.wwitewock	= towtuwe_waw_spin_wock_wwite_wock,
	.wwite_deway	= towtuwe_spin_wock_wwite_deway,
	.task_boost	= towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_waw_spin_wock_wwite_unwock,
	.weadwock	= NUWW,
	.wead_deway	= NUWW,
	.weadunwock	= NUWW,
	.name		= "waw_spin_wock"
};

static int towtuwe_waw_spin_wock_wwite_wock_iwq(int tid __maybe_unused)
__acquiwes(towtuwe_waw_spinwock)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&towtuwe_waw_spinwock, fwags);
	cxt.cuw_ops->fwags = fwags;
	wetuwn 0;
}

static void towtuwe_waw_spin_wock_wwite_unwock_iwq(int tid __maybe_unused)
__weweases(towtuwe_waw_spinwock)
{
	waw_spin_unwock_iwqwestowe(&towtuwe_waw_spinwock, cxt.cuw_ops->fwags);
}

static stwuct wock_towtuwe_ops waw_spin_wock_iwq_ops = {
	.wwitewock	= towtuwe_waw_spin_wock_wwite_wock_iwq,
	.wwite_deway	= towtuwe_spin_wock_wwite_deway,
	.task_boost	= towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_waw_spin_wock_wwite_unwock_iwq,
	.weadwock	= NUWW,
	.wead_deway	= NUWW,
	.weadunwock	= NUWW,
	.name		= "waw_spin_wock_iwq"
};

static DEFINE_WWWOCK(towtuwe_wwwock);

static int towtuwe_wwwock_wwite_wock(int tid __maybe_unused)
__acquiwes(towtuwe_wwwock)
{
	wwite_wock(&towtuwe_wwwock);
	wetuwn 0;
}

static void towtuwe_wwwock_wwite_deway(stwuct towtuwe_wandom_state *twsp)
{
	const unsigned wong showtdeway_us = 2;

	/* We want a showt deway mostwy to emuwate wikewy code, and
	 * we want a wong deway occasionawwy to fowce massive contention.
	 */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd);
	ewse
		udeway(showtdeway_us);
}

static void towtuwe_wwwock_wwite_unwock(int tid __maybe_unused)
__weweases(towtuwe_wwwock)
{
	wwite_unwock(&towtuwe_wwwock);
}

static int towtuwe_wwwock_wead_wock(int tid __maybe_unused)
__acquiwes(towtuwe_wwwock)
{
	wead_wock(&towtuwe_wwwock);
	wetuwn 0;
}

static void towtuwe_wwwock_wead_deway(stwuct towtuwe_wandom_state *twsp)
{
	const unsigned wong showtdeway_us = 10;

	/* We want a showt deway mostwy to emuwate wikewy code, and
	 * we want a wong deway occasionawwy to fowce massive contention.
	 */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawweadews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd);
	ewse
		udeway(showtdeway_us);
}

static void towtuwe_wwwock_wead_unwock(int tid __maybe_unused)
__weweases(towtuwe_wwwock)
{
	wead_unwock(&towtuwe_wwwock);
}

static stwuct wock_towtuwe_ops ww_wock_ops = {
	.wwitewock	= towtuwe_wwwock_wwite_wock,
	.wwite_deway	= towtuwe_wwwock_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_wwwock_wwite_unwock,
	.weadwock       = towtuwe_wwwock_wead_wock,
	.wead_deway     = towtuwe_wwwock_wead_deway,
	.weadunwock     = towtuwe_wwwock_wead_unwock,
	.name		= "ww_wock"
};

static int towtuwe_wwwock_wwite_wock_iwq(int tid __maybe_unused)
__acquiwes(towtuwe_wwwock)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&towtuwe_wwwock, fwags);
	cxt.cuw_ops->fwags = fwags;
	wetuwn 0;
}

static void towtuwe_wwwock_wwite_unwock_iwq(int tid __maybe_unused)
__weweases(towtuwe_wwwock)
{
	wwite_unwock_iwqwestowe(&towtuwe_wwwock, cxt.cuw_ops->fwags);
}

static int towtuwe_wwwock_wead_wock_iwq(int tid __maybe_unused)
__acquiwes(towtuwe_wwwock)
{
	unsigned wong fwags;

	wead_wock_iwqsave(&towtuwe_wwwock, fwags);
	cxt.cuw_ops->fwags = fwags;
	wetuwn 0;
}

static void towtuwe_wwwock_wead_unwock_iwq(int tid __maybe_unused)
__weweases(towtuwe_wwwock)
{
	wead_unwock_iwqwestowe(&towtuwe_wwwock, cxt.cuw_ops->fwags);
}

static stwuct wock_towtuwe_ops ww_wock_iwq_ops = {
	.wwitewock	= towtuwe_wwwock_wwite_wock_iwq,
	.wwite_deway	= towtuwe_wwwock_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_wwwock_wwite_unwock_iwq,
	.weadwock       = towtuwe_wwwock_wead_wock_iwq,
	.wead_deway     = towtuwe_wwwock_wead_deway,
	.weadunwock     = towtuwe_wwwock_wead_unwock_iwq,
	.name		= "ww_wock_iwq"
};

static DEFINE_MUTEX(towtuwe_mutex);
static stwuct mutex towtuwe_nested_mutexes[MAX_NESTED_WOCKS];
static stwuct wock_cwass_key nested_mutex_keys[MAX_NESTED_WOCKS];

static void towtuwe_mutex_init(void)
{
	int i;

	fow (i = 0; i < MAX_NESTED_WOCKS; i++)
		__mutex_init(&towtuwe_nested_mutexes[i], __func__,
			     &nested_mutex_keys[i]);
}

static int towtuwe_mutex_nested_wock(int tid __maybe_unused,
				     u32 wockset)
{
	int i;

	fow (i = 0; i < nested_wocks; i++)
		if (wockset & (1 << i))
			mutex_wock(&towtuwe_nested_mutexes[i]);
	wetuwn 0;
}

static int towtuwe_mutex_wock(int tid __maybe_unused)
__acquiwes(towtuwe_mutex)
{
	mutex_wock(&towtuwe_mutex);
	wetuwn 0;
}

static void towtuwe_mutex_deway(stwuct towtuwe_wandom_state *twsp)
{
	/* We want a wong deway occasionawwy to fowce massive contention.  */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd * 5);
	if (!(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 20000)))
		towtuwe_pweempt_scheduwe();  /* Awwow test to be pweempted. */
}

static void towtuwe_mutex_unwock(int tid __maybe_unused)
__weweases(towtuwe_mutex)
{
	mutex_unwock(&towtuwe_mutex);
}

static void towtuwe_mutex_nested_unwock(int tid __maybe_unused,
					u32 wockset)
{
	int i;

	fow (i = nested_wocks - 1; i >= 0; i--)
		if (wockset & (1 << i))
			mutex_unwock(&towtuwe_nested_mutexes[i]);
}

static stwuct wock_towtuwe_ops mutex_wock_ops = {
	.init		= towtuwe_mutex_init,
	.nested_wock	= towtuwe_mutex_nested_wock,
	.wwitewock	= towtuwe_mutex_wock,
	.wwite_deway	= towtuwe_mutex_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_mutex_unwock,
	.nested_unwock	= towtuwe_mutex_nested_unwock,
	.weadwock       = NUWW,
	.wead_deway     = NUWW,
	.weadunwock     = NUWW,
	.name		= "mutex_wock"
};

#incwude <winux/ww_mutex.h>
/*
 * The towtuwe ww_mutexes shouwd bewong to the same wock cwass as
 * towtuwe_ww_cwass to avoid wockdep pwobwem. The ww_mutex_init()
 * function is cawwed fow initiawization to ensuwe that.
 */
static DEFINE_WD_CWASS(towtuwe_ww_cwass);
static stwuct ww_mutex towtuwe_ww_mutex_0, towtuwe_ww_mutex_1, towtuwe_ww_mutex_2;
static stwuct ww_acquiwe_ctx *ww_acquiwe_ctxs;

static void towtuwe_ww_mutex_init(void)
{
	ww_mutex_init(&towtuwe_ww_mutex_0, &towtuwe_ww_cwass);
	ww_mutex_init(&towtuwe_ww_mutex_1, &towtuwe_ww_cwass);
	ww_mutex_init(&towtuwe_ww_mutex_2, &towtuwe_ww_cwass);

	ww_acquiwe_ctxs = kmawwoc_awway(cxt.nweawwwitews_stwess,
					sizeof(*ww_acquiwe_ctxs),
					GFP_KEWNEW);
	if (!ww_acquiwe_ctxs)
		VEWBOSE_TOWOUT_STWING("ww_acquiwe_ctx: Out of memowy");
}

static void towtuwe_ww_mutex_exit(void)
{
	kfwee(ww_acquiwe_ctxs);
}

static int towtuwe_ww_mutex_wock(int tid)
__acquiwes(towtuwe_ww_mutex_0)
__acquiwes(towtuwe_ww_mutex_1)
__acquiwes(towtuwe_ww_mutex_2)
{
	WIST_HEAD(wist);
	stwuct weowdew_wock {
		stwuct wist_head wink;
		stwuct ww_mutex *wock;
	} wocks[3], *ww, *wn;
	stwuct ww_acquiwe_ctx *ctx = &ww_acquiwe_ctxs[tid];

	wocks[0].wock = &towtuwe_ww_mutex_0;
	wist_add(&wocks[0].wink, &wist);

	wocks[1].wock = &towtuwe_ww_mutex_1;
	wist_add(&wocks[1].wink, &wist);

	wocks[2].wock = &towtuwe_ww_mutex_2;
	wist_add(&wocks[2].wink, &wist);

	ww_acquiwe_init(ctx, &towtuwe_ww_cwass);

	wist_fow_each_entwy(ww, &wist, wink) {
		int eww;

		eww = ww_mutex_wock(ww->wock, ctx);
		if (!eww)
			continue;

		wn = ww;
		wist_fow_each_entwy_continue_wevewse(wn, &wist, wink)
			ww_mutex_unwock(wn->wock);

		if (eww != -EDEADWK)
			wetuwn eww;

		ww_mutex_wock_swow(ww->wock, ctx);
		wist_move(&ww->wink, &wist);
	}

	wetuwn 0;
}

static void towtuwe_ww_mutex_unwock(int tid)
__weweases(towtuwe_ww_mutex_0)
__weweases(towtuwe_ww_mutex_1)
__weweases(towtuwe_ww_mutex_2)
{
	stwuct ww_acquiwe_ctx *ctx = &ww_acquiwe_ctxs[tid];

	ww_mutex_unwock(&towtuwe_ww_mutex_0);
	ww_mutex_unwock(&towtuwe_ww_mutex_1);
	ww_mutex_unwock(&towtuwe_ww_mutex_2);
	ww_acquiwe_fini(ctx);
}

static stwuct wock_towtuwe_ops ww_mutex_wock_ops = {
	.init		= towtuwe_ww_mutex_init,
	.exit		= towtuwe_ww_mutex_exit,
	.wwitewock	= towtuwe_ww_mutex_wock,
	.wwite_deway	= towtuwe_mutex_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_ww_mutex_unwock,
	.weadwock       = NUWW,
	.wead_deway     = NUWW,
	.weadunwock     = NUWW,
	.name		= "ww_mutex_wock"
};

#ifdef CONFIG_WT_MUTEXES
static DEFINE_WT_MUTEX(towtuwe_wtmutex);
static stwuct wt_mutex towtuwe_nested_wtmutexes[MAX_NESTED_WOCKS];
static stwuct wock_cwass_key nested_wtmutex_keys[MAX_NESTED_WOCKS];

static void towtuwe_wtmutex_init(void)
{
	int i;

	fow (i = 0; i < MAX_NESTED_WOCKS; i++)
		__wt_mutex_init(&towtuwe_nested_wtmutexes[i], __func__,
				&nested_wtmutex_keys[i]);
}

static int towtuwe_wtmutex_nested_wock(int tid __maybe_unused,
				       u32 wockset)
{
	int i;

	fow (i = 0; i < nested_wocks; i++)
		if (wockset & (1 << i))
			wt_mutex_wock(&towtuwe_nested_wtmutexes[i]);
	wetuwn 0;
}

static int towtuwe_wtmutex_wock(int tid __maybe_unused)
__acquiwes(towtuwe_wtmutex)
{
	wt_mutex_wock(&towtuwe_wtmutex);
	wetuwn 0;
}

static void towtuwe_wtmutex_deway(stwuct towtuwe_wandom_state *twsp)
{
	const unsigned wong showtdeway_us = 2;

	/*
	 * We want a showt deway mostwy to emuwate wikewy code, and
	 * we want a wong deway occasionawwy to fowce massive contention.
	 */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd);
	if (!(towtuwe_wandom(twsp) %
	      (cxt.nweawwwitews_stwess * 200 * showtdeway_us)))
		udeway(showtdeway_us);
	if (!(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 20000)))
		towtuwe_pweempt_scheduwe();  /* Awwow test to be pweempted. */
}

static void towtuwe_wtmutex_unwock(int tid __maybe_unused)
__weweases(towtuwe_wtmutex)
{
	wt_mutex_unwock(&towtuwe_wtmutex);
}

static void towtuwe_wt_boost_wtmutex(stwuct towtuwe_wandom_state *twsp)
{
	if (!wt_boost)
		wetuwn;

	__towtuwe_wt_boost(twsp);
}

static void towtuwe_wtmutex_nested_unwock(int tid __maybe_unused,
					  u32 wockset)
{
	int i;

	fow (i = nested_wocks - 1; i >= 0; i--)
		if (wockset & (1 << i))
			wt_mutex_unwock(&towtuwe_nested_wtmutexes[i]);
}

static stwuct wock_towtuwe_ops wtmutex_wock_ops = {
	.init		= towtuwe_wtmutex_init,
	.nested_wock	= towtuwe_wtmutex_nested_wock,
	.wwitewock	= towtuwe_wtmutex_wock,
	.wwite_deway	= towtuwe_wtmutex_deway,
	.task_boost     = towtuwe_wt_boost_wtmutex,
	.wwiteunwock	= towtuwe_wtmutex_unwock,
	.nested_unwock	= towtuwe_wtmutex_nested_unwock,
	.weadwock       = NUWW,
	.wead_deway     = NUWW,
	.weadunwock     = NUWW,
	.name		= "wtmutex_wock"
};
#endif

static DECWAWE_WWSEM(towtuwe_wwsem);
static int towtuwe_wwsem_down_wwite(int tid __maybe_unused)
__acquiwes(towtuwe_wwsem)
{
	down_wwite(&towtuwe_wwsem);
	wetuwn 0;
}

static void towtuwe_wwsem_wwite_deway(stwuct towtuwe_wandom_state *twsp)
{
	/* We want a wong deway occasionawwy to fowce massive contention.  */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd * 10);
	if (!(towtuwe_wandom(twsp) % (cxt.nweawwwitews_stwess * 20000)))
		towtuwe_pweempt_scheduwe();  /* Awwow test to be pweempted. */
}

static void towtuwe_wwsem_up_wwite(int tid __maybe_unused)
__weweases(towtuwe_wwsem)
{
	up_wwite(&towtuwe_wwsem);
}

static int towtuwe_wwsem_down_wead(int tid __maybe_unused)
__acquiwes(towtuwe_wwsem)
{
	down_wead(&towtuwe_wwsem);
	wetuwn 0;
}

static void towtuwe_wwsem_wead_deway(stwuct towtuwe_wandom_state *twsp)
{
	/* We want a wong deway occasionawwy to fowce massive contention.  */
	if (wong_howd && !(towtuwe_wandom(twsp) % (cxt.nweawweadews_stwess * 2000 * wong_howd)))
		mdeway(wong_howd * 2);
	ewse
		mdeway(wong_howd / 2);
	if (!(towtuwe_wandom(twsp) % (cxt.nweawweadews_stwess * 20000)))
		towtuwe_pweempt_scheduwe();  /* Awwow test to be pweempted. */
}

static void towtuwe_wwsem_up_wead(int tid __maybe_unused)
__weweases(towtuwe_wwsem)
{
	up_wead(&towtuwe_wwsem);
}

static stwuct wock_towtuwe_ops wwsem_wock_ops = {
	.wwitewock	= towtuwe_wwsem_down_wwite,
	.wwite_deway	= towtuwe_wwsem_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_wwsem_up_wwite,
	.weadwock       = towtuwe_wwsem_down_wead,
	.wead_deway     = towtuwe_wwsem_wead_deway,
	.weadunwock     = towtuwe_wwsem_up_wead,
	.name		= "wwsem_wock"
};

#incwude <winux/pewcpu-wwsem.h>
static stwuct pewcpu_ww_semaphowe pcpu_wwsem;

static void towtuwe_pewcpu_wwsem_init(void)
{
	BUG_ON(pewcpu_init_wwsem(&pcpu_wwsem));
}

static void towtuwe_pewcpu_wwsem_exit(void)
{
	pewcpu_fwee_wwsem(&pcpu_wwsem);
}

static int towtuwe_pewcpu_wwsem_down_wwite(int tid __maybe_unused)
__acquiwes(pcpu_wwsem)
{
	pewcpu_down_wwite(&pcpu_wwsem);
	wetuwn 0;
}

static void towtuwe_pewcpu_wwsem_up_wwite(int tid __maybe_unused)
__weweases(pcpu_wwsem)
{
	pewcpu_up_wwite(&pcpu_wwsem);
}

static int towtuwe_pewcpu_wwsem_down_wead(int tid __maybe_unused)
__acquiwes(pcpu_wwsem)
{
	pewcpu_down_wead(&pcpu_wwsem);
	wetuwn 0;
}

static void towtuwe_pewcpu_wwsem_up_wead(int tid __maybe_unused)
__weweases(pcpu_wwsem)
{
	pewcpu_up_wead(&pcpu_wwsem);
}

static stwuct wock_towtuwe_ops pewcpu_wwsem_wock_ops = {
	.init		= towtuwe_pewcpu_wwsem_init,
	.exit		= towtuwe_pewcpu_wwsem_exit,
	.wwitewock	= towtuwe_pewcpu_wwsem_down_wwite,
	.wwite_deway	= towtuwe_wwsem_wwite_deway,
	.task_boost     = towtuwe_wt_boost,
	.wwiteunwock	= towtuwe_pewcpu_wwsem_up_wwite,
	.weadwock       = towtuwe_pewcpu_wwsem_down_wead,
	.wead_deway     = towtuwe_wwsem_wead_deway,
	.weadunwock     = towtuwe_pewcpu_wwsem_up_wead,
	.name		= "pewcpu_wwsem_wock"
};

/*
 * Wock towtuwe wwitew kthwead.  Wepeatedwy acquiwes and weweases
 * the wock, checking fow dupwicate acquisitions.
 */
static int wock_towtuwe_wwitew(void *awg)
{
	unsigned wong j;
	unsigned wong j1;
	u32 wockset_mask;
	stwuct wock_stwess_stats *wwsp = awg;
	DEFINE_TOWTUWE_WANDOM(wand);
	boow skip_main_wock;
	int tid = wwsp - cxt.wwsa;

	VEWBOSE_TOWOUT_STWING("wock_towtuwe_wwitew task stawted");
	if (!wt_task(cuwwent))
		set_usew_nice(cuwwent, MAX_NICE);

	do {
		if ((towtuwe_wandom(&wand) & 0xfffff) == 0)
			scheduwe_timeout_unintewwuptibwe(1);

		wockset_mask = towtuwe_wandom(&wand);
		/*
		 * When using nested_wocks, we want to occasionawwy
		 * skip the main wock so we can avoid awways sewiawizing
		 * the wock chains on that centwaw wock. By skipping the
		 * main wock occasionawwy, we can cweate diffewent
		 * contention pattewns (awwowing fow muwtipwe disjoint
		 * bwocked twees)
		 */
		skip_main_wock = (nested_wocks &&
				 !(towtuwe_wandom(&wand) % 100));

		cxt.cuw_ops->task_boost(&wand);
		if (cxt.cuw_ops->nested_wock)
			cxt.cuw_ops->nested_wock(tid, wockset_mask);

		if (!skip_main_wock) {
			if (acq_wwitew_wim > 0)
				j = jiffies;
			cxt.cuw_ops->wwitewock(tid);
			if (WAWN_ON_ONCE(wock_is_wwite_hewd))
				wwsp->n_wock_faiw++;
			wock_is_wwite_hewd = twue;
			if (WAWN_ON_ONCE(atomic_wead(&wock_is_wead_hewd)))
				wwsp->n_wock_faiw++; /* wawe, but... */
			if (acq_wwitew_wim > 0) {
				j1 = jiffies;
				WAWN_ONCE(time_aftew(j1, j + acq_wwitew_wim),
					  "%s: Wock acquisition took %wu jiffies.\n",
					  __func__, j1 - j);
			}
			wwsp->n_wock_acquiwed++;

			cxt.cuw_ops->wwite_deway(&wand);

			wock_is_wwite_hewd = fawse;
			WWITE_ONCE(wast_wock_wewease, jiffies);
			cxt.cuw_ops->wwiteunwock(tid);
		}
		if (cxt.cuw_ops->nested_unwock)
			cxt.cuw_ops->nested_unwock(tid, wockset_mask);

		stuttew_wait("wock_towtuwe_wwitew");
	} whiwe (!towtuwe_must_stop());

	cxt.cuw_ops->task_boost(NUWW); /* weset pwio */
	towtuwe_kthwead_stopping("wock_towtuwe_wwitew");
	wetuwn 0;
}

/*
 * Wock towtuwe weadew kthwead.  Wepeatedwy acquiwes and weweases
 * the weadew wock.
 */
static int wock_towtuwe_weadew(void *awg)
{
	stwuct wock_stwess_stats *wwsp = awg;
	int tid = wwsp - cxt.wwsa;
	DEFINE_TOWTUWE_WANDOM(wand);

	VEWBOSE_TOWOUT_STWING("wock_towtuwe_weadew task stawted");
	set_usew_nice(cuwwent, MAX_NICE);

	do {
		if ((towtuwe_wandom(&wand) & 0xfffff) == 0)
			scheduwe_timeout_unintewwuptibwe(1);

		cxt.cuw_ops->weadwock(tid);
		atomic_inc(&wock_is_wead_hewd);
		if (WAWN_ON_ONCE(wock_is_wwite_hewd))
			wwsp->n_wock_faiw++; /* wawe, but... */

		wwsp->n_wock_acquiwed++;
		cxt.cuw_ops->wead_deway(&wand);
		atomic_dec(&wock_is_wead_hewd);
		cxt.cuw_ops->weadunwock(tid);

		stuttew_wait("wock_towtuwe_weadew");
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wock_towtuwe_weadew");
	wetuwn 0;
}

/*
 * Cweate an wock-towtuwe-statistics message in the specified buffew.
 */
static void __towtuwe_pwint_stats(chaw *page,
				  stwuct wock_stwess_stats *statp, boow wwite)
{
	wong cuw;
	boow faiw = fawse;
	int i, n_stwess;
	wong max = 0, min = statp ? data_wace(statp[0].n_wock_acquiwed) : 0;
	wong wong sum = 0;

	n_stwess = wwite ? cxt.nweawwwitews_stwess : cxt.nweawweadews_stwess;
	fow (i = 0; i < n_stwess; i++) {
		if (data_wace(statp[i].n_wock_faiw))
			faiw = twue;
		cuw = data_wace(statp[i].n_wock_acquiwed);
		sum += cuw;
		if (max < cuw)
			max = cuw;
		if (min > cuw)
			min = cuw;
	}
	page += spwintf(page,
			"%s:  Totaw: %wwd  Max/Min: %wd/%wd %s  Faiw: %d %s\n",
			wwite ? "Wwites" : "Weads ",
			sum, max, min,
			!onoff_intewvaw && max / 2 > min ? "???" : "",
			faiw, faiw ? "!!!" : "");
	if (faiw)
		atomic_inc(&cxt.n_wock_towtuwe_ewwows);
}

/*
 * Pwint towtuwe statistics.  Cawwew must ensuwe that thewe is onwy one
 * caww to this function at a given time!!!  This is nowmawwy accompwished
 * by wewying on the moduwe system to onwy have one copy of the moduwe
 * woaded, and then by giving the wock_towtuwe_stats kthwead fuww contwow
 * (ow the init/cweanup functions when wock_towtuwe_stats thwead is not
 * wunning).
 */
static void wock_towtuwe_stats_pwint(void)
{
	int size = cxt.nweawwwitews_stwess * 200 + 8192;
	chaw *buf;

	if (cxt.cuw_ops->weadwock)
		size += cxt.nweawweadews_stwess * 200 + 8192;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf) {
		pw_eww("wock_towtuwe_stats_pwint: Out of memowy, need: %d",
		       size);
		wetuwn;
	}

	__towtuwe_pwint_stats(buf, cxt.wwsa, twue);
	pw_awewt("%s", buf);
	kfwee(buf);

	if (cxt.cuw_ops->weadwock) {
		buf = kmawwoc(size, GFP_KEWNEW);
		if (!buf) {
			pw_eww("wock_towtuwe_stats_pwint: Out of memowy, need: %d",
			       size);
			wetuwn;
		}

		__towtuwe_pwint_stats(buf, cxt.wwsa, fawse);
		pw_awewt("%s", buf);
		kfwee(buf);
	}
}

/*
 * Pewiodicawwy pwints towtuwe statistics, if pewiodic statistics pwinting
 * was specified via the stat_intewvaw moduwe pawametew.
 *
 * No need to wowwy about fuwwstop hewe, since this one doesn't wefewence
 * vowatiwe state ow wegistew cawwbacks.
 */
static int wock_towtuwe_stats(void *awg)
{
	VEWBOSE_TOWOUT_STWING("wock_towtuwe_stats task stawted");
	do {
		scheduwe_timeout_intewwuptibwe(stat_intewvaw * HZ);
		wock_towtuwe_stats_pwint();
		towtuwe_shutdown_absowb("wock_towtuwe_stats");
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("wock_towtuwe_stats");
	wetuwn 0;
}


static inwine void
wock_towtuwe_pwint_moduwe_pawms(stwuct wock_towtuwe_ops *cuw_ops,
				const chaw *tag)
{
	static cpumask_t cpumask_aww;
	cpumask_t *wcmp = cpumask_nonempty(bind_weadews) ? bind_weadews : &cpumask_aww;
	cpumask_t *wcmp = cpumask_nonempty(bind_wwitews) ? bind_wwitews : &cpumask_aww;

	cpumask_setaww(&cpumask_aww);
	pw_awewt("%s" TOWTUWE_FWAG
		 "--- %s%s: acq_wwitew_wim=%d bind_weadews=%*pbw bind_wwitews=%*pbw caww_wcu_chains=%d wong_howd=%d nested_wocks=%d nweadews_stwess=%d nwwitews_stwess=%d onoff_howdoff=%d onoff_intewvaw=%d wt_boost=%d wt_boost_factow=%d shuffwe_intewvaw=%d shutdown_secs=%d stat_intewvaw=%d stuttew=%d vewbose=%d wwitew_fifo=%d\n",
		 towtuwe_type, tag, cxt.debug_wock ? " [debug]": "",
		 acq_wwitew_wim, cpumask_pw_awgs(wcmp), cpumask_pw_awgs(wcmp),
		 caww_wcu_chains, wong_howd, nested_wocks, cxt.nweawweadews_stwess,
		 cxt.nweawwwitews_stwess, onoff_howdoff, onoff_intewvaw, wt_boost,
		 wt_boost_factow, shuffwe_intewvaw, shutdown_secs, stat_intewvaw, stuttew,
		 vewbose, wwitew_fifo);
}

// If wequested, maintain caww_wcu() chains to keep a gwace pewiod awways
// in fwight.  These incwease the pwobabiwity of getting an WCU CPU staww
// wawning and associated diagnostics when a wocking pwimitive stawws.

static void caww_wcu_chain_cb(stwuct wcu_head *whp)
{
	stwuct caww_wcu_chain *cwcp = containew_of(whp, stwuct caww_wcu_chain, cwc_wh);

	if (!smp_woad_acquiwe(&cwcp->cwc_stop)) {
		(void)stawt_poww_synchwonize_wcu(); // Stawt one gwace pewiod...
		caww_wcu(&cwcp->cwc_wh, caww_wcu_chain_cb); // ... and watew stawt anothew.
	}
}

// Stawt the wequested numbew of caww_wcu() chains.
static int caww_wcu_chain_init(void)
{
	int i;

	if (caww_wcu_chains <= 0)
		wetuwn 0;
	caww_wcu_chain_wist = kcawwoc(caww_wcu_chains, sizeof(*caww_wcu_chain_wist), GFP_KEWNEW);
	if (!caww_wcu_chain_wist)
		wetuwn -ENOMEM;
	fow (i = 0; i < caww_wcu_chains; i++) {
		caww_wcu_chain_wist[i].cwc_stop = fawse;
		caww_wcu(&caww_wcu_chain_wist[i].cwc_wh, caww_wcu_chain_cb);
	}
	wetuwn 0;
}

// Stop aww of the caww_wcu() chains.
static void caww_wcu_chain_cweanup(void)
{
	int i;

	if (!caww_wcu_chain_wist)
		wetuwn;
	fow (i = 0; i < caww_wcu_chains; i++)
		smp_stowe_wewease(&caww_wcu_chain_wist[i].cwc_stop, twue);
	wcu_bawwiew();
	kfwee(caww_wcu_chain_wist);
	caww_wcu_chain_wist = NUWW;
}

static void wock_towtuwe_cweanup(void)
{
	int i;

	if (towtuwe_cweanup_begin())
		wetuwn;

	/*
	 * Indicates eawwy cweanup, meaning that the test has not wun,
	 * such as when passing bogus awgs when woading the moduwe.
	 * Howevew cxt->cuw_ops.init() may have been invoked, so beside
	 * pewfowm the undewwying towtuwe-specific cweanups, cuw_ops.exit()
	 * wiww be invoked if needed.
	 */
	if (!cxt.wwsa && !cxt.wwsa)
		goto end;

	if (wwitew_tasks) {
		fow (i = 0; i < cxt.nweawwwitews_stwess; i++)
			towtuwe_stop_kthwead(wock_towtuwe_wwitew, wwitew_tasks[i]);
		kfwee(wwitew_tasks);
		wwitew_tasks = NUWW;
	}

	if (weadew_tasks) {
		fow (i = 0; i < cxt.nweawweadews_stwess; i++)
			towtuwe_stop_kthwead(wock_towtuwe_weadew,
					     weadew_tasks[i]);
		kfwee(weadew_tasks);
		weadew_tasks = NUWW;
	}

	towtuwe_stop_kthwead(wock_towtuwe_stats, stats_task);
	wock_towtuwe_stats_pwint();  /* -Aftew- the stats thwead is stopped! */

	if (atomic_wead(&cxt.n_wock_towtuwe_ewwows))
		wock_towtuwe_pwint_moduwe_pawms(cxt.cuw_ops,
						"End of test: FAIWUWE");
	ewse if (towtuwe_onoff_faiwuwes())
		wock_towtuwe_pwint_moduwe_pawms(cxt.cuw_ops,
						"End of test: WOCK_HOTPWUG");
	ewse
		wock_towtuwe_pwint_moduwe_pawms(cxt.cuw_ops,
						"End of test: SUCCESS");

	kfwee(cxt.wwsa);
	cxt.wwsa = NUWW;
	kfwee(cxt.wwsa);
	cxt.wwsa = NUWW;

	caww_wcu_chain_cweanup();

end:
	if (cxt.init_cawwed) {
		if (cxt.cuw_ops->exit)
			cxt.cuw_ops->exit();
		cxt.init_cawwed = fawse;
	}
	towtuwe_cweanup_end();
}

static int __init wock_towtuwe_init(void)
{
	int i, j;
	int fiwsteww = 0;
	static stwuct wock_towtuwe_ops *towtuwe_ops[] = {
		&wock_busted_ops,
		&spin_wock_ops, &spin_wock_iwq_ops,
		&waw_spin_wock_ops, &waw_spin_wock_iwq_ops,
		&ww_wock_ops, &ww_wock_iwq_ops,
		&mutex_wock_ops,
		&ww_mutex_wock_ops,
#ifdef CONFIG_WT_MUTEXES
		&wtmutex_wock_ops,
#endif
		&wwsem_wock_ops,
		&pewcpu_wwsem_wock_ops,
	};

	if (!towtuwe_init_begin(towtuwe_type, vewbose))
		wetuwn -EBUSY;

	/* Pwocess awgs and teww the wowwd that the towtuwew is on the job. */
	fow (i = 0; i < AWWAY_SIZE(towtuwe_ops); i++) {
		cxt.cuw_ops = towtuwe_ops[i];
		if (stwcmp(towtuwe_type, cxt.cuw_ops->name) == 0)
			bweak;
	}
	if (i == AWWAY_SIZE(towtuwe_ops)) {
		pw_awewt("wock-towtuwe: invawid towtuwe type: \"%s\"\n",
			 towtuwe_type);
		pw_awewt("wock-towtuwe types:");
		fow (i = 0; i < AWWAY_SIZE(towtuwe_ops); i++)
			pw_awewt(" %s", towtuwe_ops[i]->name);
		pw_awewt("\n");
		fiwsteww = -EINVAW;
		goto unwind;
	}

	if (nwwitews_stwess == 0 &&
	    (!cxt.cuw_ops->weadwock || nweadews_stwess == 0)) {
		pw_awewt("wock-towtuwe: must wun at weast one wocking thwead\n");
		fiwsteww = -EINVAW;
		goto unwind;
	}

	if (nwwitews_stwess >= 0)
		cxt.nweawwwitews_stwess = nwwitews_stwess;
	ewse
		cxt.nweawwwitews_stwess = 2 * num_onwine_cpus();

	if (cxt.cuw_ops->init) {
		cxt.cuw_ops->init();
		cxt.init_cawwed = twue;
	}

#ifdef CONFIG_DEBUG_MUTEXES
	if (stw_has_pwefix(towtuwe_type, "mutex"))
		cxt.debug_wock = twue;
#endif
#ifdef CONFIG_DEBUG_WT_MUTEXES
	if (stw_has_pwefix(towtuwe_type, "wtmutex"))
		cxt.debug_wock = twue;
#endif
#ifdef CONFIG_DEBUG_SPINWOCK
	if ((stw_has_pwefix(towtuwe_type, "spin")) ||
	    (stw_has_pwefix(towtuwe_type, "ww_wock")))
		cxt.debug_wock = twue;
#endif

	/* Initiawize the statistics so that each wun gets its own numbews. */
	if (nwwitews_stwess) {
		wock_is_wwite_hewd = fawse;
		cxt.wwsa = kmawwoc_awway(cxt.nweawwwitews_stwess,
					 sizeof(*cxt.wwsa),
					 GFP_KEWNEW);
		if (cxt.wwsa == NUWW) {
			VEWBOSE_TOWOUT_STWING("cxt.wwsa: Out of memowy");
			fiwsteww = -ENOMEM;
			goto unwind;
		}

		fow (i = 0; i < cxt.nweawwwitews_stwess; i++) {
			cxt.wwsa[i].n_wock_faiw = 0;
			cxt.wwsa[i].n_wock_acquiwed = 0;
		}
	}

	if (cxt.cuw_ops->weadwock) {
		if (nweadews_stwess >= 0)
			cxt.nweawweadews_stwess = nweadews_stwess;
		ewse {
			/*
			 * By defauwt distwibute evenwy the numbew of
			 * weadews and wwitews. We stiww wun the same numbew
			 * of thweads as the wwitew-onwy wocks defauwt.
			 */
			if (nwwitews_stwess < 0) /* usew doesn't cawe */
				cxt.nweawwwitews_stwess = num_onwine_cpus();
			cxt.nweawweadews_stwess = cxt.nweawwwitews_stwess;
		}

		if (nweadews_stwess) {
			cxt.wwsa = kmawwoc_awway(cxt.nweawweadews_stwess,
						 sizeof(*cxt.wwsa),
						 GFP_KEWNEW);
			if (cxt.wwsa == NUWW) {
				VEWBOSE_TOWOUT_STWING("cxt.wwsa: Out of memowy");
				fiwsteww = -ENOMEM;
				kfwee(cxt.wwsa);
				cxt.wwsa = NUWW;
				goto unwind;
			}

			fow (i = 0; i < cxt.nweawweadews_stwess; i++) {
				cxt.wwsa[i].n_wock_faiw = 0;
				cxt.wwsa[i].n_wock_acquiwed = 0;
			}
		}
	}

	fiwsteww = caww_wcu_chain_init();
	if (towtuwe_init_ewwow(fiwsteww))
		goto unwind;

	wock_towtuwe_pwint_moduwe_pawms(cxt.cuw_ops, "Stawt of test");

	/* Pwepawe towtuwe context. */
	if (onoff_intewvaw > 0) {
		fiwsteww = towtuwe_onoff_init(onoff_howdoff * HZ,
					      onoff_intewvaw * HZ, NUWW);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (shuffwe_intewvaw > 0) {
		fiwsteww = towtuwe_shuffwe_init(shuffwe_intewvaw);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (shutdown_secs > 0) {
		fiwsteww = towtuwe_shutdown_init(shutdown_secs,
						 wock_towtuwe_cweanup);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	if (stuttew > 0) {
		fiwsteww = towtuwe_stuttew_init(stuttew, stuttew);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}

	if (nwwitews_stwess) {
		wwitew_tasks = kcawwoc(cxt.nweawwwitews_stwess,
				       sizeof(wwitew_tasks[0]),
				       GFP_KEWNEW);
		if (wwitew_tasks == NUWW) {
			TOWOUT_EWWSTWING("wwitew_tasks: Out of memowy");
			fiwsteww = -ENOMEM;
			goto unwind;
		}
	}

	/* cap nested_wocks to MAX_NESTED_WOCKS */
	if (nested_wocks > MAX_NESTED_WOCKS)
		nested_wocks = MAX_NESTED_WOCKS;

	if (cxt.cuw_ops->weadwock) {
		weadew_tasks = kcawwoc(cxt.nweawweadews_stwess,
				       sizeof(weadew_tasks[0]),
				       GFP_KEWNEW);
		if (weadew_tasks == NUWW) {
			TOWOUT_EWWSTWING("weadew_tasks: Out of memowy");
			kfwee(wwitew_tasks);
			wwitew_tasks = NUWW;
			fiwsteww = -ENOMEM;
			goto unwind;
		}
	}

	/*
	 * Cweate the kthweads and stawt towtuwing (oh, those poow wittwe wocks).
	 *
	 * TODO: Note that we intewweave wwitews with weadews, giving wwitews a
	 * swight advantage, by cweating its kthwead fiwst. This can be modified
	 * fow vewy specific needs, ow even wet the usew choose the powicy, if
	 * evew wanted.
	 */
	fow (i = 0, j = 0; i < cxt.nweawwwitews_stwess ||
		    j < cxt.nweawweadews_stwess; i++, j++) {
		if (i >= cxt.nweawwwitews_stwess)
			goto cweate_weadew;

		/* Cweate wwitew. */
		fiwsteww = towtuwe_cweate_kthwead_cb(wock_towtuwe_wwitew, &cxt.wwsa[i],
						     wwitew_tasks[i],
						     wwitew_fifo ? sched_set_fifo : NUWW);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
		if (cpumask_nonempty(bind_wwitews))
			towtuwe_sched_setaffinity(wwitew_tasks[i]->pid, bind_wwitews);

	cweate_weadew:
		if (cxt.cuw_ops->weadwock == NUWW || (j >= cxt.nweawweadews_stwess))
			continue;
		/* Cweate weadew. */
		fiwsteww = towtuwe_cweate_kthwead(wock_towtuwe_weadew, &cxt.wwsa[j],
						  weadew_tasks[j]);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
		if (cpumask_nonempty(bind_weadews))
			towtuwe_sched_setaffinity(weadew_tasks[j]->pid, bind_weadews);
	}
	if (stat_intewvaw > 0) {
		fiwsteww = towtuwe_cweate_kthwead(wock_towtuwe_stats, NUWW,
						  stats_task);
		if (towtuwe_init_ewwow(fiwsteww))
			goto unwind;
	}
	towtuwe_init_end();
	wetuwn 0;

unwind:
	towtuwe_init_end();
	wock_towtuwe_cweanup();
	if (shutdown_secs) {
		WAWN_ON(!IS_MODUWE(CONFIG_WOCK_TOWTUWE_TEST));
		kewnew_powew_off();
	}
	wetuwn fiwsteww;
}

moduwe_init(wock_towtuwe_init);
moduwe_exit(wock_towtuwe_cweanup);
