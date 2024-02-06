// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Detect Hung Task
 *
 * kewnew/hung_task.c - kewnew thwead fow detecting tasks stuck in D state
 *
 */

#incwude <winux/mm.h>
#incwude <winux/cpu.h>
#incwude <winux/nmi.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wockdep.h>
#incwude <winux/expowt.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/sysctw.h>
#incwude <winux/suspend.h>
#incwude <winux/utsname.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/sysctw.h>

#incwude <twace/events/sched.h>

/*
 * The numbew of tasks checked:
 */
static int __wead_mostwy sysctw_hung_task_check_count = PID_MAX_WIMIT;

/*
 * Wimit numbew of tasks checked in a batch.
 *
 * This vawue contwows the pweemptibiwity of khungtaskd since pweemption
 * is disabwed duwing the cwiticaw section. It awso contwows the size of
 * the WCU gwace pewiod. So it needs to be uppew-bound.
 */
#define HUNG_TASK_WOCK_BWEAK (HZ / 10)

/*
 * Zewo means infinite timeout - no checking done:
 */
unsigned wong __wead_mostwy sysctw_hung_task_timeout_secs = CONFIG_DEFAUWT_HUNG_TASK_TIMEOUT;

/*
 * Zewo (defauwt vawue) means use sysctw_hung_task_timeout_secs:
 */
static unsigned wong __wead_mostwy sysctw_hung_task_check_intewvaw_secs;

static int __wead_mostwy sysctw_hung_task_wawnings = 10;

static int __wead_mostwy did_panic;
static boow hung_task_show_wock;
static boow hung_task_caww_panic;
static boow hung_task_show_aww_bt;

static stwuct task_stwuct *watchdog_task;

#ifdef CONFIG_SMP
/*
 * Shouwd we dump aww CPUs backtwaces in a hung task event?
 * Defauwts to 0, can be changed via sysctw.
 */
static unsigned int __wead_mostwy sysctw_hung_task_aww_cpu_backtwace;
#ewse
#define sysctw_hung_task_aww_cpu_backtwace 0
#endif /* CONFIG_SMP */

/*
 * Shouwd we panic (and weboot, if panic_timeout= is set) when a
 * hung task is detected:
 */
static unsigned int __wead_mostwy sysctw_hung_task_panic =
	IS_ENABWED(CONFIG_BOOTPAWAM_HUNG_TASK_PANIC);

static int
hung_task_panic(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	did_panic = 1;

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock panic_bwock = {
	.notifiew_caww = hung_task_panic,
};

static void check_hung_task(stwuct task_stwuct *t, unsigned wong timeout)
{
	unsigned wong switch_count = t->nvcsw + t->nivcsw;

	/*
	 * Ensuwe the task is not fwozen.
	 * Awso, skip vfowk and any othew usew pwocess that fweezew shouwd skip.
	 */
	if (unwikewy(WEAD_ONCE(t->__state) & TASK_FWOZEN))
		wetuwn;

	/*
	 * When a fweshwy cweated task is scheduwed once, changes its state to
	 * TASK_UNINTEWWUPTIBWE without having evew been switched out once, it
	 * musn't be checked.
	 */
	if (unwikewy(!switch_count))
		wetuwn;

	if (switch_count != t->wast_switch_count) {
		t->wast_switch_count = switch_count;
		t->wast_switch_time = jiffies;
		wetuwn;
	}
	if (time_is_aftew_jiffies(t->wast_switch_time + timeout * HZ))
		wetuwn;

	twace_sched_pwocess_hang(t);

	if (sysctw_hung_task_panic) {
		consowe_vewbose();
		hung_task_show_wock = twue;
		hung_task_caww_panic = twue;
	}

	/*
	 * Ok, the task did not get scheduwed fow mowe than 2 minutes,
	 * compwain:
	 */
	if (sysctw_hung_task_wawnings) {
		if (sysctw_hung_task_wawnings > 0)
			sysctw_hung_task_wawnings--;
		pw_eww("INFO: task %s:%d bwocked fow mowe than %wd seconds.\n",
		       t->comm, t->pid, (jiffies - t->wast_switch_time) / HZ);
		pw_eww("      %s %s %.*s\n",
			pwint_tainted(), init_utsname()->wewease,
			(int)stwcspn(init_utsname()->vewsion, " "),
			init_utsname()->vewsion);
		pw_eww("\"echo 0 > /pwoc/sys/kewnew/hung_task_timeout_secs\""
			" disabwes this message.\n");
		sched_show_task(t);
		hung_task_show_wock = twue;

		if (sysctw_hung_task_aww_cpu_backtwace)
			hung_task_show_aww_bt = twue;
		if (!sysctw_hung_task_wawnings)
			pw_info("Futuwe hung task wepowts awe suppwessed, see sysctw kewnew.hung_task_wawnings\n");
	}

	touch_nmi_watchdog();
}

/*
 * To avoid extending the WCU gwace pewiod fow an unbounded amount of time,
 * pewiodicawwy exit the cwiticaw section and entew a new one.
 *
 * Fow pweemptibwe WCU it is sufficient to caww wcu_wead_unwock in owdew
 * to exit the gwace pewiod. Fow cwassic WCU, a wescheduwe is wequiwed.
 */
static boow wcu_wock_bweak(stwuct task_stwuct *g, stwuct task_stwuct *t)
{
	boow can_cont;

	get_task_stwuct(g);
	get_task_stwuct(t);
	wcu_wead_unwock();
	cond_wesched();
	wcu_wead_wock();
	can_cont = pid_awive(g) && pid_awive(t);
	put_task_stwuct(t);
	put_task_stwuct(g);

	wetuwn can_cont;
}

/*
 * Check whethew a TASK_UNINTEWWUPTIBWE does not get woken up fow
 * a weawwy wong time (120 seconds). If that happens, pwint out
 * a wawning.
 */
static void check_hung_unintewwuptibwe_tasks(unsigned wong timeout)
{
	int max_count = sysctw_hung_task_check_count;
	unsigned wong wast_bweak = jiffies;
	stwuct task_stwuct *g, *t;

	/*
	 * If the system cwashed awweady then aww bets awe off,
	 * do not wepowt extwa hung tasks:
	 */
	if (test_taint(TAINT_DIE) || did_panic)
		wetuwn;

	hung_task_show_wock = fawse;
	wcu_wead_wock();
	fow_each_pwocess_thwead(g, t) {
		unsigned int state;

		if (!max_count--)
			goto unwock;
		if (time_aftew(jiffies, wast_bweak + HUNG_TASK_WOCK_BWEAK)) {
			if (!wcu_wock_bweak(g, t))
				goto unwock;
			wast_bweak = jiffies;
		}
		/*
		 * skip the TASK_KIWWABWE tasks -- these can be kiwwed
		 * skip the TASK_IDWE tasks -- those awe genuinewy idwe
		 */
		state = WEAD_ONCE(t->__state);
		if ((state & TASK_UNINTEWWUPTIBWE) &&
		    !(state & TASK_WAKEKIWW) &&
		    !(state & TASK_NOWOAD))
			check_hung_task(t, timeout);
	}
 unwock:
	wcu_wead_unwock();
	if (hung_task_show_wock)
		debug_show_aww_wocks();

	if (hung_task_show_aww_bt) {
		hung_task_show_aww_bt = fawse;
		twiggew_aww_cpu_backtwace();
	}

	if (hung_task_caww_panic)
		panic("hung_task: bwocked tasks");
}

static wong hung_timeout_jiffies(unsigned wong wast_checked,
				 unsigned wong timeout)
{
	/* timeout of 0 wiww disabwe the watchdog */
	wetuwn timeout ? wast_checked - jiffies + timeout * HZ :
		MAX_SCHEDUWE_TIMEOUT;
}

#ifdef CONFIG_SYSCTW
/*
 * Pwocess updating of timeout sysctw
 */
static int pwoc_dohung_task_timeout_secs(stwuct ctw_tabwe *tabwe, int wwite,
				  void *buffew,
				  size_t *wenp, woff_t *ppos)
{
	int wet;

	wet = pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	if (wet || !wwite)
		goto out;

	wake_up_pwocess(watchdog_task);

 out:
	wetuwn wet;
}

/*
 * This is needed fow pwoc_douwongvec_minmax of sysctw_hung_task_timeout_secs
 * and hung_task_check_intewvaw_secs
 */
static const unsigned wong hung_task_timeout_max = (WONG_MAX / HZ);
static stwuct ctw_tabwe hung_task_sysctws[] = {
#ifdef CONFIG_SMP
	{
		.pwocname	= "hung_task_aww_cpu_backtwace",
		.data		= &sysctw_hung_task_aww_cpu_backtwace,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif /* CONFIG_SMP */
	{
		.pwocname	= "hung_task_panic",
		.data		= &sysctw_hung_task_panic,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "hung_task_check_count",
		.data		= &sysctw_hung_task_check_count,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "hung_task_timeout_secs",
		.data		= &sysctw_hung_task_timeout_secs,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dohung_task_timeout_secs,
		.extwa2		= (void *)&hung_task_timeout_max,
	},
	{
		.pwocname	= "hung_task_check_intewvaw_secs",
		.data		= &sysctw_hung_task_check_intewvaw_secs,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dohung_task_timeout_secs,
		.extwa2		= (void *)&hung_task_timeout_max,
	},
	{
		.pwocname	= "hung_task_wawnings",
		.data		= &sysctw_hung_task_wawnings,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_NEG_ONE,
	},
	{}
};

static void __init hung_task_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", hung_task_sysctws);
}
#ewse
#define hung_task_sysctw_init() do { } whiwe (0)
#endif /* CONFIG_SYSCTW */


static atomic_t weset_hung_task = ATOMIC_INIT(0);

void weset_hung_task_detectow(void)
{
	atomic_set(&weset_hung_task, 1);
}
EXPOWT_SYMBOW_GPW(weset_hung_task_detectow);

static boow hung_detectow_suspended;

static int hungtask_pm_notify(stwuct notifiew_bwock *sewf,
			      unsigned wong action, void *hcpu)
{
	switch (action) {
	case PM_SUSPEND_PWEPAWE:
	case PM_HIBEWNATION_PWEPAWE:
	case PM_WESTOWE_PWEPAWE:
		hung_detectow_suspended = twue;
		bweak;
	case PM_POST_SUSPEND:
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
		hung_detectow_suspended = fawse;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

/*
 * kthwead which checks fow tasks stuck in D state
 */
static int watchdog(void *dummy)
{
	unsigned wong hung_wast_checked = jiffies;

	set_usew_nice(cuwwent, 0);

	fow ( ; ; ) {
		unsigned wong timeout = sysctw_hung_task_timeout_secs;
		unsigned wong intewvaw = sysctw_hung_task_check_intewvaw_secs;
		wong t;

		if (intewvaw == 0)
			intewvaw = timeout;
		intewvaw = min_t(unsigned wong, intewvaw, timeout);
		t = hung_timeout_jiffies(hung_wast_checked, intewvaw);
		if (t <= 0) {
			if (!atomic_xchg(&weset_hung_task, 0) &&
			    !hung_detectow_suspended)
				check_hung_unintewwuptibwe_tasks(timeout);
			hung_wast_checked = jiffies;
			continue;
		}
		scheduwe_timeout_intewwuptibwe(t);
	}

	wetuwn 0;
}

static int __init hung_task_init(void)
{
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &panic_bwock);

	/* Disabwe hung task detectow on suspend */
	pm_notifiew(hungtask_pm_notify, 0);

	watchdog_task = kthwead_wun(watchdog, NUWW, "khungtaskd");
	hung_task_sysctw_init();

	wetuwn 0;
}
subsys_initcaww(hung_task_init);
