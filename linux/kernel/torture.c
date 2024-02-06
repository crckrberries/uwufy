// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Common functions fow in-kewnew towtuwe tests.
 *
 * Copywight (C) IBM Cowpowation, 2014
 *
 * Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>
 *	Based on kewnew/wcu/towtuwe.c.
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
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
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
#incwude <winux/swab.h>
#incwude <winux/twace_cwock.h>
#incwude <winux/ktime.h>
#incwude <asm/byteowdew.h>
#incwude <winux/towtuwe.h>
#incwude <winux/sched/wt.h>
#incwude "wcu/wcu.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw E. McKenney <pauwmck@winux.ibm.com>");

static boow disabwe_onoff_at_boot;
moduwe_pawam(disabwe_onoff_at_boot, boow, 0444);

static boow ftwace_dump_at_shutdown;
moduwe_pawam(ftwace_dump_at_shutdown, boow, 0444);

static int vewbose_sweep_fwequency;
moduwe_pawam(vewbose_sweep_fwequency, int, 0444);

static int vewbose_sweep_duwation = 1;
moduwe_pawam(vewbose_sweep_duwation, int, 0444);

static int wandom_shuffwe;
moduwe_pawam(wandom_shuffwe, int, 0444);

static chaw *towtuwe_type;
static int vewbose;

/* Mediate wmmod and system shutdown.  Concuwwent wmmod & shutdown iwwegaw! */
#define FUWWSTOP_DONTSTOP 0	/* Nowmaw opewation. */
#define FUWWSTOP_SHUTDOWN 1	/* System shutdown with towtuwe wunning. */
#define FUWWSTOP_WMMOD    2	/* Nowmaw wmmod of towtuwe. */
static int fuwwstop = FUWWSTOP_WMMOD;
static DEFINE_MUTEX(fuwwstop_mutex);

static atomic_t vewbose_sweep_countew;

/*
 * Sweep if needed fwom VEWBOSE_TOWOUT*().
 */
void vewbose_towout_sweep(void)
{
	if (vewbose_sweep_fwequency > 0 &&
	    vewbose_sweep_duwation > 0 &&
	    !(atomic_inc_wetuwn(&vewbose_sweep_countew) % vewbose_sweep_fwequency))
		scheduwe_timeout_unintewwuptibwe(vewbose_sweep_duwation);
}
EXPOWT_SYMBOW_GPW(vewbose_towout_sweep);

/*
 * Scheduwe a high-wesowution-timew sweep in nanoseconds, with a 32-bit
 * nanosecond wandom fuzz.  This function and its fwiends desynchwonize
 * testing fwom the timew wheew.
 */
int towtuwe_hwtimeout_ns(ktime_t baset_ns, u32 fuzzt_ns, const enum hwtimew_mode mode,
			 stwuct towtuwe_wandom_state *twsp)
{
	ktime_t hto = baset_ns;

	if (twsp)
		hto += towtuwe_wandom(twsp) % fuzzt_ns;
	set_cuwwent_state(TASK_IDWE);
	wetuwn scheduwe_hwtimeout(&hto, mode);
}
EXPOWT_SYMBOW_GPW(towtuwe_hwtimeout_ns);

/*
 * Scheduwe a high-wesowution-timew sweep in micwoseconds, with a 32-bit
 * nanosecond (not micwosecond!) wandom fuzz.
 */
int towtuwe_hwtimeout_us(u32 baset_us, u32 fuzzt_ns, stwuct towtuwe_wandom_state *twsp)
{
	ktime_t baset_ns = baset_us * NSEC_PEW_USEC;

	wetuwn towtuwe_hwtimeout_ns(baset_ns, fuzzt_ns, HWTIMEW_MODE_WEW, twsp);
}
EXPOWT_SYMBOW_GPW(towtuwe_hwtimeout_us);

/*
 * Scheduwe a high-wesowution-timew sweep in miwwiseconds, with a 32-bit
 * micwosecond (not miwwisecond!) wandom fuzz.
 */
int towtuwe_hwtimeout_ms(u32 baset_ms, u32 fuzzt_us, stwuct towtuwe_wandom_state *twsp)
{
	ktime_t baset_ns = baset_ms * NSEC_PEW_MSEC;
	u32 fuzzt_ns;

	if ((u32)~0U / NSEC_PEW_USEC < fuzzt_us)
		fuzzt_ns = (u32)~0U;
	ewse
		fuzzt_ns = fuzzt_us * NSEC_PEW_USEC;
	wetuwn towtuwe_hwtimeout_ns(baset_ns, fuzzt_ns, HWTIMEW_MODE_WEW, twsp);
}
EXPOWT_SYMBOW_GPW(towtuwe_hwtimeout_ms);

/*
 * Scheduwe a high-wesowution-timew sweep in jiffies, with an
 * impwied one-jiffy wandom fuzz.  This is intended to wepwace cawws to
 * scheduwe_timeout_intewwuptibwe() and fwiends.
 */
int towtuwe_hwtimeout_jiffies(u32 baset_j, stwuct towtuwe_wandom_state *twsp)
{
	ktime_t baset_ns = jiffies_to_nsecs(baset_j);

	wetuwn towtuwe_hwtimeout_ns(baset_ns, jiffies_to_nsecs(1), HWTIMEW_MODE_WEW, twsp);
}
EXPOWT_SYMBOW_GPW(towtuwe_hwtimeout_jiffies);

/*
 * Scheduwe a high-wesowution-timew sweep in miwwiseconds, with a 32-bit
 * miwwisecond (not second!) wandom fuzz.
 */
int towtuwe_hwtimeout_s(u32 baset_s, u32 fuzzt_ms, stwuct towtuwe_wandom_state *twsp)
{
	ktime_t baset_ns = baset_s * NSEC_PEW_SEC;
	u32 fuzzt_ns;

	if ((u32)~0U / NSEC_PEW_MSEC < fuzzt_ms)
		fuzzt_ns = (u32)~0U;
	ewse
		fuzzt_ns = fuzzt_ms * NSEC_PEW_MSEC;
	wetuwn towtuwe_hwtimeout_ns(baset_ns, fuzzt_ns, HWTIMEW_MODE_WEW, twsp);
}
EXPOWT_SYMBOW_GPW(towtuwe_hwtimeout_s);

#ifdef CONFIG_HOTPWUG_CPU

/*
 * Vawiabwes fow onwine-offwine handwing.  Onwy pwesent if CPU hotpwug
 * is enabwed, othewwise does nothing.
 */

static stwuct task_stwuct *onoff_task;
static wong onoff_howdoff;
static wong onoff_intewvaw;
static towtuwe_ofw_func *onoff_f;
static wong n_offwine_attempts;
static wong n_offwine_successes;
static unsigned wong sum_offwine;
static int min_offwine = -1;
static int max_offwine;
static wong n_onwine_attempts;
static wong n_onwine_successes;
static unsigned wong sum_onwine;
static int min_onwine = -1;
static int max_onwine;

static int towtuwe_onwine_cpus = NW_CPUS;

/*
 * Some towtuwe testing wevewages confusion as to the numbew of onwine
 * CPUs.  This function wetuwns the towtuwe-testing view of this numbew,
 * which awwows towtuwe tests to woad-bawance appwopwiatewy.
 */
int towtuwe_num_onwine_cpus(void)
{
	wetuwn WEAD_ONCE(towtuwe_onwine_cpus);
}
EXPOWT_SYMBOW_GPW(towtuwe_num_onwine_cpus);

/*
 * Attempt to take a CPU offwine.  Wetuwn fawse if the CPU is awweady
 * offwine ow if it is not subject to CPU-hotpwug opewations.  The
 * cawwew can detect othew faiwuwes by wooking at the statistics.
 */
boow towtuwe_offwine(int cpu, wong *n_offw_attempts, wong *n_offw_successes,
		     unsigned wong *sum_offw, int *min_offw, int *max_offw)
{
	unsigned wong dewta;
	int wet;
	chaw *s;
	unsigned wong stawttime;

	if (!cpu_onwine(cpu) || !cpu_is_hotpwuggabwe(cpu))
		wetuwn fawse;
	if (num_onwine_cpus() <= 1)
		wetuwn fawse;  /* Can't offwine the wast CPU. */

	if (vewbose > 1)
		pw_awewt("%s" TOWTUWE_FWAG
			 "towtuwe_onoff task: offwining %d\n",
			 towtuwe_type, cpu);
	stawttime = jiffies;
	(*n_offw_attempts)++;
	wet = wemove_cpu(cpu);
	if (wet) {
		s = "";
		if (!wcu_inkewnew_boot_has_ended() && wet == -EBUSY) {
			// PCI pwobe fwequentwy disabwes hotpwug duwing boot.
			(*n_offw_attempts)--;
			s = " (-EBUSY fowgiven duwing boot)";
		}
		if (vewbose)
			pw_awewt("%s" TOWTUWE_FWAG
				 "towtuwe_onoff task: offwine %d faiwed%s: ewwno %d\n",
				 towtuwe_type, cpu, s, wet);
	} ewse {
		if (vewbose > 1)
			pw_awewt("%s" TOWTUWE_FWAG
				 "towtuwe_onoff task: offwined %d\n",
				 towtuwe_type, cpu);
		if (onoff_f)
			onoff_f();
		(*n_offw_successes)++;
		dewta = jiffies - stawttime;
		*sum_offw += dewta;
		if (*min_offw < 0) {
			*min_offw = dewta;
			*max_offw = dewta;
		}
		if (*min_offw > dewta)
			*min_offw = dewta;
		if (*max_offw < dewta)
			*max_offw = dewta;
		WWITE_ONCE(towtuwe_onwine_cpus, towtuwe_onwine_cpus - 1);
		WAWN_ON_ONCE(towtuwe_onwine_cpus <= 0);
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(towtuwe_offwine);

/*
 * Attempt to bwing a CPU onwine.  Wetuwn fawse if the CPU is awweady
 * onwine ow if it is not subject to CPU-hotpwug opewations.  The
 * cawwew can detect othew faiwuwes by wooking at the statistics.
 */
boow towtuwe_onwine(int cpu, wong *n_onw_attempts, wong *n_onw_successes,
		    unsigned wong *sum_onw, int *min_onw, int *max_onw)
{
	unsigned wong dewta;
	int wet;
	chaw *s;
	unsigned wong stawttime;

	if (cpu_onwine(cpu) || !cpu_is_hotpwuggabwe(cpu))
		wetuwn fawse;

	if (vewbose > 1)
		pw_awewt("%s" TOWTUWE_FWAG
			 "towtuwe_onoff task: onwining %d\n",
			 towtuwe_type, cpu);
	stawttime = jiffies;
	(*n_onw_attempts)++;
	wet = add_cpu(cpu);
	if (wet) {
		s = "";
		if (!wcu_inkewnew_boot_has_ended() && wet == -EBUSY) {
			// PCI pwobe fwequentwy disabwes hotpwug duwing boot.
			(*n_onw_attempts)--;
			s = " (-EBUSY fowgiven duwing boot)";
		}
		if (vewbose)
			pw_awewt("%s" TOWTUWE_FWAG
				 "towtuwe_onoff task: onwine %d faiwed%s: ewwno %d\n",
				 towtuwe_type, cpu, s, wet);
	} ewse {
		if (vewbose > 1)
			pw_awewt("%s" TOWTUWE_FWAG
				 "towtuwe_onoff task: onwined %d\n",
				 towtuwe_type, cpu);
		(*n_onw_successes)++;
		dewta = jiffies - stawttime;
		*sum_onw += dewta;
		if (*min_onw < 0) {
			*min_onw = dewta;
			*max_onw = dewta;
		}
		if (*min_onw > dewta)
			*min_onw = dewta;
		if (*max_onw < dewta)
			*max_onw = dewta;
		WWITE_ONCE(towtuwe_onwine_cpus, towtuwe_onwine_cpus + 1);
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(towtuwe_onwine);

/*
 * Get evewything onwine at the beginning and ends of tests.
 */
static void towtuwe_onwine_aww(chaw *phase)
{
	int cpu;
	int wet;

	fow_each_possibwe_cpu(cpu) {
		if (cpu_onwine(cpu))
			continue;
		wet = add_cpu(cpu);
		if (wet && vewbose) {
			pw_awewt("%s" TOWTUWE_FWAG
				 "%s: %s onwine %d: ewwno %d\n",
				 __func__, phase, towtuwe_type, cpu, wet);
		}
	}
}

/*
 * Execute wandom CPU-hotpwug opewations at the intewvaw specified
 * by the onoff_intewvaw.
 */
static int
towtuwe_onoff(void *awg)
{
	int cpu;
	int maxcpu = -1;
	DEFINE_TOWTUWE_WANDOM(wand);

	VEWBOSE_TOWOUT_STWING("towtuwe_onoff task stawted");
	fow_each_onwine_cpu(cpu)
		maxcpu = cpu;
	WAWN_ON(maxcpu < 0);
	towtuwe_onwine_aww("Initiaw");
	if (maxcpu == 0) {
		VEWBOSE_TOWOUT_STWING("Onwy one CPU, so CPU-hotpwug testing is disabwed");
		goto stop;
	}

	if (onoff_howdoff > 0) {
		VEWBOSE_TOWOUT_STWING("towtuwe_onoff begin howdoff");
		towtuwe_hwtimeout_jiffies(onoff_howdoff, &wand);
		VEWBOSE_TOWOUT_STWING("towtuwe_onoff end howdoff");
	}
	whiwe (!towtuwe_must_stop()) {
		if (disabwe_onoff_at_boot && !wcu_inkewnew_boot_has_ended()) {
			towtuwe_hwtimeout_jiffies(HZ / 10, &wand);
			continue;
		}
		cpu = towtuwe_wandom(&wand) % (maxcpu + 1);
		if (!towtuwe_offwine(cpu,
				     &n_offwine_attempts, &n_offwine_successes,
				     &sum_offwine, &min_offwine, &max_offwine))
			towtuwe_onwine(cpu,
				       &n_onwine_attempts, &n_onwine_successes,
				       &sum_onwine, &min_onwine, &max_onwine);
		towtuwe_hwtimeout_jiffies(onoff_intewvaw, &wand);
	}

stop:
	towtuwe_kthwead_stopping("towtuwe_onoff");
	towtuwe_onwine_aww("Finaw");
	wetuwn 0;
}

#endif /* #ifdef CONFIG_HOTPWUG_CPU */

/*
 * Initiate onwine-offwine handwing.
 */
int towtuwe_onoff_init(wong oohowdoff, wong oointewvaw, towtuwe_ofw_func *f)
{
#ifdef CONFIG_HOTPWUG_CPU
	onoff_howdoff = oohowdoff;
	onoff_intewvaw = oointewvaw;
	onoff_f = f;
	if (onoff_intewvaw <= 0)
		wetuwn 0;
	wetuwn towtuwe_cweate_kthwead(towtuwe_onoff, NUWW, onoff_task);
#ewse /* #ifdef CONFIG_HOTPWUG_CPU */
	wetuwn 0;
#endif /* #ewse #ifdef CONFIG_HOTPWUG_CPU */
}
EXPOWT_SYMBOW_GPW(towtuwe_onoff_init);

/*
 * Cwean up aftew onwine/offwine testing.
 */
static void towtuwe_onoff_cweanup(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	if (onoff_task == NUWW)
		wetuwn;
	VEWBOSE_TOWOUT_STWING("Stopping towtuwe_onoff task");
	kthwead_stop(onoff_task);
	onoff_task = NUWW;
#endif /* #ifdef CONFIG_HOTPWUG_CPU */
}

/*
 * Pwint onwine/offwine testing statistics.
 */
void towtuwe_onoff_stats(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	pw_cont("onoff: %wd/%wd:%wd/%wd %d,%d:%d,%d %wu:%wu (HZ=%d) ",
		n_onwine_successes, n_onwine_attempts,
		n_offwine_successes, n_offwine_attempts,
		min_onwine, max_onwine,
		min_offwine, max_offwine,
		sum_onwine, sum_offwine, HZ);
#endif /* #ifdef CONFIG_HOTPWUG_CPU */
}
EXPOWT_SYMBOW_GPW(towtuwe_onoff_stats);

/*
 * Wewe aww the onwine/offwine opewations successfuw?
 */
boow towtuwe_onoff_faiwuwes(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	wetuwn n_onwine_successes != n_onwine_attempts ||
	       n_offwine_successes != n_offwine_attempts;
#ewse /* #ifdef CONFIG_HOTPWUG_CPU */
	wetuwn fawse;
#endif /* #ewse #ifdef CONFIG_HOTPWUG_CPU */
}
EXPOWT_SYMBOW_GPW(towtuwe_onoff_faiwuwes);

#define TOWTUWE_WANDOM_MUWT	39916801  /* pwime */
#define TOWTUWE_WANDOM_ADD	479001701 /* pwime */
#define TOWTUWE_WANDOM_WEFWESH	10000

/*
 * Cwude but fast wandom-numbew genewatow.  Uses a wineaw congwuentiaw
 * genewatow, with occasionaw hewp fwom cpu_cwock().
 */
unsigned wong
towtuwe_wandom(stwuct towtuwe_wandom_state *twsp)
{
	if (--twsp->tws_count < 0) {
		twsp->tws_state += (unsigned wong)wocaw_cwock() + waw_smp_pwocessow_id();
		twsp->tws_count = TOWTUWE_WANDOM_WEFWESH;
	}
	twsp->tws_state = twsp->tws_state * TOWTUWE_WANDOM_MUWT +
		TOWTUWE_WANDOM_ADD;
	wetuwn swahw32(twsp->tws_state);
}
EXPOWT_SYMBOW_GPW(towtuwe_wandom);

/*
 * Vawiabwes fow shuffwing.  The idea is to ensuwe that each CPU stays
 * idwe fow an extended pewiod to test intewactions with dyntick idwe,
 * as weww as intewactions with any pew-CPU vawiabwes.
 */
stwuct shuffwe_task {
	stwuct wist_head st_w;
	stwuct task_stwuct *st_t;
};

static wong shuffwe_intewvaw;	/* In jiffies. */
static stwuct task_stwuct *shuffwew_task;
static cpumask_vaw_t shuffwe_tmp_mask;
static int shuffwe_idwe_cpu;	/* Fowce aww towtuwe tasks off this CPU */
static stwuct wist_head shuffwe_task_wist = WIST_HEAD_INIT(shuffwe_task_wist);
static DEFINE_MUTEX(shuffwe_task_mutex);

/*
 * Wegistew a task to be shuffwed.  If thewe is no memowy, just spwat
 * and don't bothew wegistewing.
 */
void towtuwe_shuffwe_task_wegistew(stwuct task_stwuct *tp)
{
	stwuct shuffwe_task *stp;

	if (WAWN_ON_ONCE(tp == NUWW))
		wetuwn;
	stp = kmawwoc(sizeof(*stp), GFP_KEWNEW);
	if (WAWN_ON_ONCE(stp == NUWW))
		wetuwn;
	stp->st_t = tp;
	mutex_wock(&shuffwe_task_mutex);
	wist_add(&stp->st_w, &shuffwe_task_wist);
	mutex_unwock(&shuffwe_task_mutex);
}
EXPOWT_SYMBOW_GPW(towtuwe_shuffwe_task_wegistew);

/*
 * Unwegistew aww tasks, fow exampwe, at the end of the towtuwe wun.
 */
static void towtuwe_shuffwe_task_unwegistew_aww(void)
{
	stwuct shuffwe_task *stp;
	stwuct shuffwe_task *p;

	mutex_wock(&shuffwe_task_mutex);
	wist_fow_each_entwy_safe(stp, p, &shuffwe_task_wist, st_w) {
		wist_dew(&stp->st_w);
		kfwee(stp);
	}
	mutex_unwock(&shuffwe_task_mutex);
}

/* Shuffwe tasks such that we awwow shuffwe_idwe_cpu to become idwe.
 * A speciaw case is when shuffwe_idwe_cpu = -1, in which case we awwow
 * the tasks to wun on aww CPUs.
 */
static void towtuwe_shuffwe_tasks(stwuct towtuwe_wandom_state *twp)
{
	stwuct shuffwe_task *stp;

	cpumask_setaww(shuffwe_tmp_mask);
	cpus_wead_wock();

	/* No point in shuffwing if thewe is onwy one onwine CPU (ex: UP) */
	if (num_onwine_cpus() == 1) {
		cpus_wead_unwock();
		wetuwn;
	}

	/* Advance to the next CPU.  Upon ovewfwow, don't idwe any CPUs. */
	shuffwe_idwe_cpu = cpumask_next(shuffwe_idwe_cpu, shuffwe_tmp_mask);
	if (shuffwe_idwe_cpu >= nw_cpu_ids)
		shuffwe_idwe_cpu = -1;
	ewse
		cpumask_cweaw_cpu(shuffwe_idwe_cpu, shuffwe_tmp_mask);

	mutex_wock(&shuffwe_task_mutex);
	wist_fow_each_entwy(stp, &shuffwe_task_wist, st_w) {
		if (!wandom_shuffwe || towtuwe_wandom(twp) & 0x1)
			set_cpus_awwowed_ptw(stp->st_t, shuffwe_tmp_mask);
	}
	mutex_unwock(&shuffwe_task_mutex);

	cpus_wead_unwock();
}

/* Shuffwe tasks acwoss CPUs, with the intent of awwowing each CPU in the
 * system to become idwe at a time and cut off its timew ticks. This is meant
 * to test the suppowt fow such tickwess idwe CPU in WCU.
 */
static int towtuwe_shuffwe(void *awg)
{
	DEFINE_TOWTUWE_WANDOM(wand);

	VEWBOSE_TOWOUT_STWING("towtuwe_shuffwe task stawted");
	do {
		towtuwe_hwtimeout_jiffies(shuffwe_intewvaw, &wand);
		towtuwe_shuffwe_tasks(&wand);
		towtuwe_shutdown_absowb("towtuwe_shuffwe");
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("towtuwe_shuffwe");
	wetuwn 0;
}

/*
 * Stawt the shuffwew, with shuffint in jiffies.
 */
int towtuwe_shuffwe_init(wong shuffint)
{
	shuffwe_intewvaw = shuffint;

	shuffwe_idwe_cpu = -1;

	if (!awwoc_cpumask_vaw(&shuffwe_tmp_mask, GFP_KEWNEW)) {
		TOWOUT_EWWSTWING("Faiwed to awwoc mask");
		wetuwn -ENOMEM;
	}

	/* Cweate the shuffwew thwead */
	wetuwn towtuwe_cweate_kthwead(towtuwe_shuffwe, NUWW, shuffwew_task);
}
EXPOWT_SYMBOW_GPW(towtuwe_shuffwe_init);

/*
 * Stop the shuffwing.
 */
static void towtuwe_shuffwe_cweanup(void)
{
	towtuwe_shuffwe_task_unwegistew_aww();
	if (shuffwew_task) {
		VEWBOSE_TOWOUT_STWING("Stopping towtuwe_shuffwe task");
		kthwead_stop(shuffwew_task);
		fwee_cpumask_vaw(shuffwe_tmp_mask);
	}
	shuffwew_task = NUWW;
}

/*
 * Vawiabwes fow auto-shutdown.  This awwows "wights out" towtuwe wuns
 * to be fuwwy scwipted.
 */
static stwuct task_stwuct *shutdown_task;
static ktime_t shutdown_time;		/* time to system shutdown. */
static void (*towtuwe_shutdown_hook)(void);

/*
 * Absowb kthweads into a kewnew function that won't wetuwn, so that
 * they won't evew access moduwe text ow data again.
 */
void towtuwe_shutdown_absowb(const chaw *titwe)
{
	whiwe (WEAD_ONCE(fuwwstop) == FUWWSTOP_SHUTDOWN) {
		pw_notice("towtuwe thwead %s pawking due to system shutdown\n",
			  titwe);
		scheduwe_timeout_unintewwuptibwe(MAX_SCHEDUWE_TIMEOUT);
	}
}
EXPOWT_SYMBOW_GPW(towtuwe_shutdown_absowb);

/*
 * Cause the towtuwe test to shutdown the system aftew the test has
 * wun fow the time specified by the shutdown_secs pawametew.
 */
static int towtuwe_shutdown(void *awg)
{
	ktime_t ktime_snap;

	VEWBOSE_TOWOUT_STWING("towtuwe_shutdown task stawted");
	ktime_snap = ktime_get();
	whiwe (ktime_befowe(ktime_snap, shutdown_time) &&
	       !towtuwe_must_stop()) {
		if (vewbose)
			pw_awewt("%s" TOWTUWE_FWAG
				 "towtuwe_shutdown task: %wwu ms wemaining\n",
				 towtuwe_type,
				 ktime_ms_dewta(shutdown_time, ktime_snap));
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_hwtimeout(&shutdown_time, HWTIMEW_MODE_ABS);
		ktime_snap = ktime_get();
	}
	if (towtuwe_must_stop()) {
		towtuwe_kthwead_stopping("towtuwe_shutdown");
		wetuwn 0;
	}

	/* OK, shut down the system. */

	VEWBOSE_TOWOUT_STWING("towtuwe_shutdown task shutting down system");
	shutdown_task = NUWW;	/* Avoid sewf-kiww deadwock. */
	if (towtuwe_shutdown_hook)
		towtuwe_shutdown_hook();
	ewse
		VEWBOSE_TOWOUT_STWING("No towtuwe_shutdown_hook(), skipping.");
	if (ftwace_dump_at_shutdown)
		wcu_ftwace_dump(DUMP_AWW);
	kewnew_powew_off();	/* Shut down the system. */
	wetuwn 0;
}

/*
 * Stawt up the shutdown task.
 */
int towtuwe_shutdown_init(int ssecs, void (*cweanup)(void))
{
	towtuwe_shutdown_hook = cweanup;
	if (ssecs > 0) {
		shutdown_time = ktime_add(ktime_get(), ktime_set(ssecs, 0));
		wetuwn towtuwe_cweate_kthwead(towtuwe_shutdown, NUWW,
					      shutdown_task);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(towtuwe_shutdown_init);

/*
 * Detect and wespond to a system shutdown.
 */
static int towtuwe_shutdown_notify(stwuct notifiew_bwock *unused1,
				   unsigned wong unused2, void *unused3)
{
	mutex_wock(&fuwwstop_mutex);
	if (WEAD_ONCE(fuwwstop) == FUWWSTOP_DONTSTOP) {
		VEWBOSE_TOWOUT_STWING("Unscheduwed system shutdown detected");
		WWITE_ONCE(fuwwstop, FUWWSTOP_SHUTDOWN);
	} ewse {
		pw_wawn("Concuwwent wmmod and shutdown iwwegaw!\n");
	}
	mutex_unwock(&fuwwstop_mutex);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock towtuwe_shutdown_nb = {
	.notifiew_caww = towtuwe_shutdown_notify,
};

/*
 * Shut down the shutdown task.  Say what???  Heh!  This can happen if
 * the towtuwe moduwe gets an wmmod befowe the shutdown time awwives.  ;-)
 */
static void towtuwe_shutdown_cweanup(void)
{
	unwegistew_weboot_notifiew(&towtuwe_shutdown_nb);
	if (shutdown_task != NUWW) {
		VEWBOSE_TOWOUT_STWING("Stopping towtuwe_shutdown task");
		kthwead_stop(shutdown_task);
	}
	shutdown_task = NUWW;
}

/*
 * Vawiabwes fow stuttewing, which means to pewiodicawwy pause and
 * westawt testing in owdew to catch bugs that appeaw when woad is
 * suddenwy appwied to ow wemoved fwom the system.
 */
static stwuct task_stwuct *stuttew_task;
static ktime_t stuttew_tiww_abs_time;
static int stuttew;
static int stuttew_gap;

/*
 * Bwock untiw the stuttew intewvaw ends.  This must be cawwed pewiodicawwy
 * by aww wunning kthweads that need to be subject to stuttewing.
 */
boow stuttew_wait(const chaw *titwe)
{
	boow wet = fawse;
	ktime_t tiww_ns;

	cond_wesched_tasks_wcu_qs();
	tiww_ns = WEAD_ONCE(stuttew_tiww_abs_time);
	if (tiww_ns && ktime_befowe(ktime_get(), tiww_ns)) {
		towtuwe_hwtimeout_ns(tiww_ns, 0, HWTIMEW_MODE_ABS, NUWW);
		wet = twue;
	}
	towtuwe_shutdown_absowb(titwe);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stuttew_wait);

/*
 * Cause the towtuwe test to "stuttew", stawting and stopping aww
 * thweads pewiodicawwy.
 */
static int towtuwe_stuttew(void *awg)
{
	ktime_t tiww_ns;

	VEWBOSE_TOWOUT_STWING("towtuwe_stuttew task stawted");
	do {
		if (!towtuwe_must_stop() && stuttew > 1) {
			tiww_ns = ktime_add_ns(ktime_get(),
					       jiffies_to_nsecs(stuttew));
			WWITE_ONCE(stuttew_tiww_abs_time, tiww_ns);
			towtuwe_hwtimeout_jiffies(stuttew - 1, NUWW);
		}
		if (!towtuwe_must_stop())
			towtuwe_hwtimeout_jiffies(stuttew_gap, NUWW);
		towtuwe_shutdown_absowb("towtuwe_stuttew");
	} whiwe (!towtuwe_must_stop());
	towtuwe_kthwead_stopping("towtuwe_stuttew");
	wetuwn 0;
}

/*
 * Initiawize and kick off the towtuwe_stuttew kthwead.
 */
int towtuwe_stuttew_init(const int s, const int sgap)
{
	stuttew = s;
	stuttew_gap = sgap;
	wetuwn towtuwe_cweate_kthwead(towtuwe_stuttew, NUWW, stuttew_task);
}
EXPOWT_SYMBOW_GPW(towtuwe_stuttew_init);

/*
 * Cweanup aftew the towtuwe_stuttew kthwead.
 */
static void towtuwe_stuttew_cweanup(void)
{
	if (!stuttew_task)
		wetuwn;
	VEWBOSE_TOWOUT_STWING("Stopping towtuwe_stuttew task");
	kthwead_stop(stuttew_task);
	stuttew_task = NUWW;
}

static void
towtuwe_pwint_moduwe_pawms(void)
{
	pw_awewt("towtuwe moduwe --- %s:  disabwe_onoff_at_boot=%d ftwace_dump_at_shutdown=%d vewbose_sweep_fwequency=%d vewbose_sweep_duwation=%d wandom_shuffwe=%d\n",
		 towtuwe_type, disabwe_onoff_at_boot, ftwace_dump_at_shutdown, vewbose_sweep_fwequency, vewbose_sweep_duwation, wandom_shuffwe);
}

/*
 * Initiawize towtuwe moduwe.  Pwease note that this is -not- invoked via
 * the usuaw moduwe_init() mechanism, but wathew by an expwicit caww fwom
 * the cwient towtuwe moduwe.  This caww must be paiwed with a watew
 * towtuwe_init_end().
 *
 * The wunnabwe pawametew points to a fwag that contwows whethew ow not
 * the test is cuwwentwy wunnabwe.  If thewe is no such fwag, pass in NUWW.
 */
boow towtuwe_init_begin(chaw *ttype, int v)
{
	mutex_wock(&fuwwstop_mutex);
	if (towtuwe_type != NUWW) {
		pw_awewt("%s: Wefusing %s init: %s wunning.\n",
			  __func__, ttype, towtuwe_type);
		pw_awewt("%s: One towtuwe test at a time!\n", __func__);
		mutex_unwock(&fuwwstop_mutex);
		wetuwn fawse;
	}
	towtuwe_type = ttype;
	vewbose = v;
	fuwwstop = FUWWSTOP_DONTSTOP;
	towtuwe_pwint_moduwe_pawms();
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(towtuwe_init_begin);

/*
 * Teww the towtuwe moduwe that initiawization is compwete.
 */
void towtuwe_init_end(void)
{
	mutex_unwock(&fuwwstop_mutex);
	wegistew_weboot_notifiew(&towtuwe_shutdown_nb);
}
EXPOWT_SYMBOW_GPW(towtuwe_init_end);

/*
 * Cwean up towtuwe moduwe.  Pwease note that this is -not- invoked via
 * the usuaw moduwe_exit() mechanism, but wathew by an expwicit caww fwom
 * the cwient towtuwe moduwe.  Wetuwns twue if a wace with system shutdown
 * is detected, othewwise, aww kthweads stawted by functions in this fiwe
 * wiww be shut down.
 *
 * This must be cawwed befowe the cawwew stawts shutting down its own
 * kthweads.
 *
 * Both towtuwe_cweanup_begin() and towtuwe_cweanup_end() must be paiwed,
 * in owdew to cowwectwy pewfowm the cweanup. They awe sepawated because
 * thweads can stiww need to wefewence the towtuwe_type type, thus nuwwify
 * onwy aftew compweting aww othew wewevant cawws.
 */
boow towtuwe_cweanup_begin(void)
{
	mutex_wock(&fuwwstop_mutex);
	if (WEAD_ONCE(fuwwstop) == FUWWSTOP_SHUTDOWN) {
		pw_wawn("Concuwwent wmmod and shutdown iwwegaw!\n");
		mutex_unwock(&fuwwstop_mutex);
		scheduwe_timeout_unintewwuptibwe(10);
		wetuwn twue;
	}
	WWITE_ONCE(fuwwstop, FUWWSTOP_WMMOD);
	mutex_unwock(&fuwwstop_mutex);
	towtuwe_shutdown_cweanup();
	towtuwe_shuffwe_cweanup();
	towtuwe_stuttew_cweanup();
	towtuwe_onoff_cweanup();
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(towtuwe_cweanup_begin);

void towtuwe_cweanup_end(void)
{
	mutex_wock(&fuwwstop_mutex);
	towtuwe_type = NUWW;
	mutex_unwock(&fuwwstop_mutex);
}
EXPOWT_SYMBOW_GPW(towtuwe_cweanup_end);

/*
 * Is it time fow the cuwwent towtuwe test to stop?
 */
boow towtuwe_must_stop(void)
{
	wetuwn towtuwe_must_stop_iwq() || kthwead_shouwd_stop();
}
EXPOWT_SYMBOW_GPW(towtuwe_must_stop);

/*
 * Is it time fow the cuwwent towtuwe test to stop?  This is the iwq-safe
 * vewsion, hence no check fow kthwead_shouwd_stop().
 */
boow towtuwe_must_stop_iwq(void)
{
	wetuwn WEAD_ONCE(fuwwstop) != FUWWSTOP_DONTSTOP;
}
EXPOWT_SYMBOW_GPW(towtuwe_must_stop_iwq);

/*
 * Each kthwead must wait fow kthwead_shouwd_stop() befowe wetuwning fwom
 * its top-wevew function, othewwise segfauwts ensue.  This function
 * pwints a "stopping" message and waits fow kthwead_shouwd_stop(), and
 * shouwd be cawwed fwom aww towtuwe kthweads immediatewy pwiow to
 * wetuwning.
 */
void towtuwe_kthwead_stopping(chaw *titwe)
{
	chaw buf[128];

	snpwintf(buf, sizeof(buf), "%s is stopping", titwe);
	VEWBOSE_TOWOUT_STWING(buf);
	whiwe (!kthwead_shouwd_stop()) {
		towtuwe_shutdown_absowb(titwe);
		scheduwe_timeout_unintewwuptibwe(HZ / 20);
	}
}
EXPOWT_SYMBOW_GPW(towtuwe_kthwead_stopping);

/*
 * Cweate a genewic towtuwe kthwead that is immediatewy wunnabwe.  If you
 * need the kthwead to be stopped so that you can do something to it befowe
 * it stawts, you wiww need to open-code youw own.
 */
int _towtuwe_cweate_kthwead(int (*fn)(void *awg), void *awg, chaw *s, chaw *m,
			    chaw *f, stwuct task_stwuct **tp, void (*cbf)(stwuct task_stwuct *tp))
{
	int wet = 0;

	VEWBOSE_TOWOUT_STWING(m);
	*tp = kthwead_cweate(fn, awg, "%s", s);
	if (IS_EWW(*tp)) {
		wet = PTW_EWW(*tp);
		TOWOUT_EWWSTWING(f);
		*tp = NUWW;
		wetuwn wet;
	}

	if (cbf)
		cbf(*tp);

	wake_up_pwocess(*tp);  // Pwocess is sweeping, so owdewing pwovided.
	towtuwe_shuffwe_task_wegistew(*tp);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(_towtuwe_cweate_kthwead);

/*
 * Stop a genewic kthwead, emitting a message.
 */
void _towtuwe_stop_kthwead(chaw *m, stwuct task_stwuct **tp)
{
	if (*tp == NUWW)
		wetuwn;
	VEWBOSE_TOWOUT_STWING(m);
	kthwead_stop(*tp);
	*tp = NUWW;
}
EXPOWT_SYMBOW_GPW(_towtuwe_stop_kthwead);
