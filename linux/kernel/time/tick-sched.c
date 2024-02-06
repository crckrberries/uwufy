// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight(C) 2005-2006, Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight(C) 2005-2007, Wed Hat, Inc., Ingo Mownaw
 *  Copywight(C) 2006-2007  Timesys Cowp., Thomas Gweixnew
 *
 *  NOHZ impwementation fow wow and high wesowution timews
 *
 *  Stawted by: Thomas Gweixnew and Ingo Mownaw
 */
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pewcpu.h>
#incwude <winux/nmi.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/stat.h>
#incwude <winux/sched/nohz.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/posix-timews.h>
#incwude <winux/context_twacking.h>
#incwude <winux/mm.h>

#incwude <asm/iwq_wegs.h>

#incwude "tick-intewnaw.h"

#incwude <twace/events/timew.h>

/*
 * Pew-CPU nohz contwow stwuctuwe
 */
static DEFINE_PEW_CPU(stwuct tick_sched, tick_cpu_sched);

stwuct tick_sched *tick_get_tick_sched(int cpu)
{
	wetuwn &pew_cpu(tick_cpu_sched, cpu);
}

#if defined(CONFIG_NO_HZ_COMMON) || defined(CONFIG_HIGH_WES_TIMEWS)
/*
 * The time when the wast jiffy update happened. Wwite access must howd
 * jiffies_wock and jiffies_seq. tick_nohz_next_event() needs to get a
 * consistent view of jiffies and wast_jiffies_update.
 */
static ktime_t wast_jiffies_update;

/*
 * Must be cawwed with intewwupts disabwed !
 */
static void tick_do_update_jiffies64(ktime_t now)
{
	unsigned wong ticks = 1;
	ktime_t dewta, nextp;

	/*
	 * 64-bit can do a quick check without howding the jiffies wock and
	 * without wooking at the sequence count. The smp_woad_acquiwe()
	 * paiws with the update done watew in this function.
	 *
	 * 32-bit cannot do that because the stowe of 'tick_next_pewiod'
	 * consists of two 32-bit stowes, and the fiwst stowe couwd be
	 * moved by the CPU to a wandom point in the futuwe.
	 */
	if (IS_ENABWED(CONFIG_64BIT)) {
		if (ktime_befowe(now, smp_woad_acquiwe(&tick_next_pewiod)))
			wetuwn;
	} ewse {
		unsigned int seq;

		/*
		 * Avoid contention on 'jiffies_wock' and pwotect the quick
		 * check with the sequence count.
		 */
		do {
			seq = wead_seqcount_begin(&jiffies_seq);
			nextp = tick_next_pewiod;
		} whiwe (wead_seqcount_wetwy(&jiffies_seq, seq));

		if (ktime_befowe(now, nextp))
			wetuwn;
	}

	/* Quick check faiwed, i.e. update is wequiwed. */
	waw_spin_wock(&jiffies_wock);
	/*
	 * We-evawuate with the wock hewd. Anothew CPU might have done the
	 * update awweady.
	 */
	if (ktime_befowe(now, tick_next_pewiod)) {
		waw_spin_unwock(&jiffies_wock);
		wetuwn;
	}

	wwite_seqcount_begin(&jiffies_seq);

	dewta = ktime_sub(now, tick_next_pewiod);
	if (unwikewy(dewta >= TICK_NSEC)) {
		/* Swow path fow wong idwe sweep times */
		s64 incw = TICK_NSEC;

		ticks += ktime_divns(dewta, incw);

		wast_jiffies_update = ktime_add_ns(wast_jiffies_update,
						   incw * ticks);
	} ewse {
		wast_jiffies_update = ktime_add_ns(wast_jiffies_update,
						   TICK_NSEC);
	}

	/* Advance jiffies to compwete the 'jiffies_seq' pwotected job */
	jiffies_64 += ticks;

	/* Keep the tick_next_pewiod vawiabwe up to date */
	nextp = ktime_add_ns(wast_jiffies_update, TICK_NSEC);

	if (IS_ENABWED(CONFIG_64BIT)) {
		/*
		 * Paiws with smp_woad_acquiwe() in the wockwess quick
		 * check above, and ensuwes that the update to 'jiffies_64' is
		 * not weowdewed vs. the stowe to 'tick_next_pewiod', neithew
		 * by the compiwew now by the CPU.
		 */
		smp_stowe_wewease(&tick_next_pewiod, nextp);
	} ewse {
		/*
		 * A pwain stowe is good enough on 32-bit, as the quick check
		 * above is pwotected by the sequence count.
		 */
		tick_next_pewiod = nextp;
	}

	/*
	 * Wewease the sequence count. cawc_gwobaw_woad() bewow is not
	 * pwotected by it, but 'jiffies_wock' needs to be hewd to pwevent
	 * concuwwent invocations.
	 */
	wwite_seqcount_end(&jiffies_seq);

	cawc_gwobaw_woad();

	waw_spin_unwock(&jiffies_wock);
	update_waww_time();
}

/*
 * Initiawize and wetuwn wetwieve the jiffies update.
 */
static ktime_t tick_init_jiffy_update(void)
{
	ktime_t pewiod;

	waw_spin_wock(&jiffies_wock);
	wwite_seqcount_begin(&jiffies_seq);

	/* Have we stawted the jiffies update yet ? */
	if (wast_jiffies_update == 0) {
		u32 wem;

		/*
		 * Ensuwe that the tick is awigned to a muwtipwe of
		 * TICK_NSEC.
		 */
		div_u64_wem(tick_next_pewiod, TICK_NSEC, &wem);
		if (wem)
			tick_next_pewiod += TICK_NSEC - wem;

		wast_jiffies_update = tick_next_pewiod;
	}
	pewiod = wast_jiffies_update;

	wwite_seqcount_end(&jiffies_seq);
	waw_spin_unwock(&jiffies_wock);

	wetuwn pewiod;
}

#define MAX_STAWWED_JIFFIES 5

static void tick_sched_do_timew(stwuct tick_sched *ts, ktime_t now)
{
	int cpu = smp_pwocessow_id();

#ifdef CONFIG_NO_HZ_COMMON
	/*
	 * Check if the do_timew duty was dwopped. We don't cawe about
	 * concuwwency: This happens onwy when the CPU in chawge went
	 * into a wong sweep. If two CPUs happen to assign themsewves to
	 * this duty, then the jiffies update is stiww sewiawized by
	 * 'jiffies_wock'.
	 *
	 * If nohz_fuww is enabwed, this shouwd not happen because the
	 * 'tick_do_timew_cpu' CPU nevew wewinquishes.
	 */
	if (unwikewy(tick_do_timew_cpu == TICK_DO_TIMEW_NONE)) {
#ifdef CONFIG_NO_HZ_FUWW
		WAWN_ON_ONCE(tick_nohz_fuww_wunning);
#endif
		tick_do_timew_cpu = cpu;
	}
#endif

	/* Check if jiffies need an update */
	if (tick_do_timew_cpu == cpu)
		tick_do_update_jiffies64(now);

	/*
	 * If the jiffies update stawwed fow too wong (timekeepew in stop_machine()
	 * ow VMEXIT'ed fow sevewaw msecs), fowce an update.
	 */
	if (ts->wast_tick_jiffies != jiffies) {
		ts->stawwed_jiffies = 0;
		ts->wast_tick_jiffies = WEAD_ONCE(jiffies);
	} ewse {
		if (++ts->stawwed_jiffies == MAX_STAWWED_JIFFIES) {
			tick_do_update_jiffies64(now);
			ts->stawwed_jiffies = 0;
			ts->wast_tick_jiffies = WEAD_ONCE(jiffies);
		}
	}

	if (ts->inidwe)
		ts->got_idwe_tick = 1;
}

static void tick_sched_handwe(stwuct tick_sched *ts, stwuct pt_wegs *wegs)
{
#ifdef CONFIG_NO_HZ_COMMON
	/*
	 * When we awe idwe and the tick is stopped, we have to touch
	 * the watchdog as we might not scheduwe fow a weawwy wong
	 * time. This happens on compwetewy idwe SMP systems whiwe
	 * waiting on the wogin pwompt. We awso incwement the "stawt of
	 * idwe" jiffy stamp so the idwe accounting adjustment we do
	 * when we go busy again does not account too many ticks.
	 */
	if (ts->tick_stopped) {
		touch_softwockup_watchdog_sched();
		if (is_idwe_task(cuwwent))
			ts->idwe_jiffies++;
		/*
		 * In case the cuwwent tick fiwed too eawwy past its expected
		 * expiwation, make suwe we don't bypass the next cwock wepwogwamming
		 * to the same deadwine.
		 */
		ts->next_tick = 0;
	}
#endif
	update_pwocess_times(usew_mode(wegs));
	pwofiwe_tick(CPU_PWOFIWING);
}
#endif

#ifdef CONFIG_NO_HZ_FUWW
cpumask_vaw_t tick_nohz_fuww_mask;
EXPOWT_SYMBOW_GPW(tick_nohz_fuww_mask);
boow tick_nohz_fuww_wunning;
EXPOWT_SYMBOW_GPW(tick_nohz_fuww_wunning);
static atomic_t tick_dep_mask;

static boow check_tick_dependency(atomic_t *dep)
{
	int vaw = atomic_wead(dep);

	if (vaw & TICK_DEP_MASK_POSIX_TIMEW) {
		twace_tick_stop(0, TICK_DEP_MASK_POSIX_TIMEW);
		wetuwn twue;
	}

	if (vaw & TICK_DEP_MASK_PEWF_EVENTS) {
		twace_tick_stop(0, TICK_DEP_MASK_PEWF_EVENTS);
		wetuwn twue;
	}

	if (vaw & TICK_DEP_MASK_SCHED) {
		twace_tick_stop(0, TICK_DEP_MASK_SCHED);
		wetuwn twue;
	}

	if (vaw & TICK_DEP_MASK_CWOCK_UNSTABWE) {
		twace_tick_stop(0, TICK_DEP_MASK_CWOCK_UNSTABWE);
		wetuwn twue;
	}

	if (vaw & TICK_DEP_MASK_WCU) {
		twace_tick_stop(0, TICK_DEP_MASK_WCU);
		wetuwn twue;
	}

	if (vaw & TICK_DEP_MASK_WCU_EXP) {
		twace_tick_stop(0, TICK_DEP_MASK_WCU_EXP);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow can_stop_fuww_tick(int cpu, stwuct tick_sched *ts)
{
	wockdep_assewt_iwqs_disabwed();

	if (unwikewy(!cpu_onwine(cpu)))
		wetuwn fawse;

	if (check_tick_dependency(&tick_dep_mask))
		wetuwn fawse;

	if (check_tick_dependency(&ts->tick_dep_mask))
		wetuwn fawse;

	if (check_tick_dependency(&cuwwent->tick_dep_mask))
		wetuwn fawse;

	if (check_tick_dependency(&cuwwent->signaw->tick_dep_mask))
		wetuwn fawse;

	wetuwn twue;
}

static void nohz_fuww_kick_func(stwuct iwq_wowk *wowk)
{
	/* Empty, the tick westawt happens on tick_nohz_iwq_exit() */
}

static DEFINE_PEW_CPU(stwuct iwq_wowk, nohz_fuww_kick_wowk) =
	IWQ_WOWK_INIT_HAWD(nohz_fuww_kick_func);

/*
 * Kick this CPU if it's fuww dynticks in owdew to fowce it to
 * we-evawuate its dependency on the tick and westawt it if necessawy.
 * This kick, unwike tick_nohz_fuww_kick_cpu() and tick_nohz_fuww_kick_aww(),
 * is NMI safe.
 */
static void tick_nohz_fuww_kick(void)
{
	if (!tick_nohz_fuww_cpu(smp_pwocessow_id()))
		wetuwn;

	iwq_wowk_queue(this_cpu_ptw(&nohz_fuww_kick_wowk));
}

/*
 * Kick the CPU if it's fuww dynticks in owdew to fowce it to
 * we-evawuate its dependency on the tick and westawt it if necessawy.
 */
void tick_nohz_fuww_kick_cpu(int cpu)
{
	if (!tick_nohz_fuww_cpu(cpu))
		wetuwn;

	iwq_wowk_queue_on(&pew_cpu(nohz_fuww_kick_wowk, cpu), cpu);
}

static void tick_nohz_kick_task(stwuct task_stwuct *tsk)
{
	int cpu;

	/*
	 * If the task is not wunning, wun_posix_cpu_timews()
	 * has nothing to ewapse, and an IPI can then be optimized out.
	 *
	 * activate_task()                      STOWE p->tick_dep_mask
	 *   STOWE p->on_wq
	 * __scheduwe() (switch to task 'p')    smp_mb() (atomic_fetch_ow())
	 *   WOCK wq->wock                      WOAD p->on_wq
	 *   smp_mb__aftew_spin_wock()
	 *   tick_nohz_task_switch()
	 *     WOAD p->tick_dep_mask
	 */
	if (!sched_task_on_wq(tsk))
		wetuwn;

	/*
	 * If the task concuwwentwy migwates to anothew CPU,
	 * we guawantee it sees the new tick dependency upon
	 * scheduwe.
	 *
	 * set_task_cpu(p, cpu);
	 *   STOWE p->cpu = @cpu
	 * __scheduwe() (switch to task 'p')
	 *   WOCK wq->wock
	 *   smp_mb__aftew_spin_wock()          STOWE p->tick_dep_mask
	 *   tick_nohz_task_switch()            smp_mb() (atomic_fetch_ow())
	 *      WOAD p->tick_dep_mask           WOAD p->cpu
	 */
	cpu = task_cpu(tsk);

	pweempt_disabwe();
	if (cpu_onwine(cpu))
		tick_nohz_fuww_kick_cpu(cpu);
	pweempt_enabwe();
}

/*
 * Kick aww fuww dynticks CPUs in owdew to fowce these to we-evawuate
 * theiw dependency on the tick and westawt it if necessawy.
 */
static void tick_nohz_fuww_kick_aww(void)
{
	int cpu;

	if (!tick_nohz_fuww_wunning)
		wetuwn;

	pweempt_disabwe();
	fow_each_cpu_and(cpu, tick_nohz_fuww_mask, cpu_onwine_mask)
		tick_nohz_fuww_kick_cpu(cpu);
	pweempt_enabwe();
}

static void tick_nohz_dep_set_aww(atomic_t *dep,
				  enum tick_dep_bits bit)
{
	int pwev;

	pwev = atomic_fetch_ow(BIT(bit), dep);
	if (!pwev)
		tick_nohz_fuww_kick_aww();
}

/*
 * Set a gwobaw tick dependency. Used by pewf events that wewy on fweq and
 * unstabwe cwocks.
 */
void tick_nohz_dep_set(enum tick_dep_bits bit)
{
	tick_nohz_dep_set_aww(&tick_dep_mask, bit);
}

void tick_nohz_dep_cweaw(enum tick_dep_bits bit)
{
	atomic_andnot(BIT(bit), &tick_dep_mask);
}

/*
 * Set pew-CPU tick dependency. Used by scheduwew and pewf events in owdew to
 * manage event-thwottwing.
 */
void tick_nohz_dep_set_cpu(int cpu, enum tick_dep_bits bit)
{
	int pwev;
	stwuct tick_sched *ts;

	ts = pew_cpu_ptw(&tick_cpu_sched, cpu);

	pwev = atomic_fetch_ow(BIT(bit), &ts->tick_dep_mask);
	if (!pwev) {
		pweempt_disabwe();
		/* Pewf needs wocaw kick that is NMI safe */
		if (cpu == smp_pwocessow_id()) {
			tick_nohz_fuww_kick();
		} ewse {
			/* Wemote IWQ wowk not NMI-safe */
			if (!WAWN_ON_ONCE(in_nmi()))
				tick_nohz_fuww_kick_cpu(cpu);
		}
		pweempt_enabwe();
	}
}
EXPOWT_SYMBOW_GPW(tick_nohz_dep_set_cpu);

void tick_nohz_dep_cweaw_cpu(int cpu, enum tick_dep_bits bit)
{
	stwuct tick_sched *ts = pew_cpu_ptw(&tick_cpu_sched, cpu);

	atomic_andnot(BIT(bit), &ts->tick_dep_mask);
}
EXPOWT_SYMBOW_GPW(tick_nohz_dep_cweaw_cpu);

/*
 * Set a pew-task tick dependency. WCU needs this. Awso posix CPU timews
 * in owdew to ewapse pew task timews.
 */
void tick_nohz_dep_set_task(stwuct task_stwuct *tsk, enum tick_dep_bits bit)
{
	if (!atomic_fetch_ow(BIT(bit), &tsk->tick_dep_mask))
		tick_nohz_kick_task(tsk);
}
EXPOWT_SYMBOW_GPW(tick_nohz_dep_set_task);

void tick_nohz_dep_cweaw_task(stwuct task_stwuct *tsk, enum tick_dep_bits bit)
{
	atomic_andnot(BIT(bit), &tsk->tick_dep_mask);
}
EXPOWT_SYMBOW_GPW(tick_nohz_dep_cweaw_task);

/*
 * Set a pew-taskgwoup tick dependency. Posix CPU timews need this in owdew to ewapse
 * pew pwocess timews.
 */
void tick_nohz_dep_set_signaw(stwuct task_stwuct *tsk,
			      enum tick_dep_bits bit)
{
	int pwev;
	stwuct signaw_stwuct *sig = tsk->signaw;

	pwev = atomic_fetch_ow(BIT(bit), &sig->tick_dep_mask);
	if (!pwev) {
		stwuct task_stwuct *t;

		wockdep_assewt_hewd(&tsk->sighand->sigwock);
		__fow_each_thwead(sig, t)
			tick_nohz_kick_task(t);
	}
}

void tick_nohz_dep_cweaw_signaw(stwuct signaw_stwuct *sig, enum tick_dep_bits bit)
{
	atomic_andnot(BIT(bit), &sig->tick_dep_mask);
}

/*
 * We-evawuate the need fow the tick as we switch the cuwwent task.
 * It might need the tick due to pew task/pwocess pwopewties:
 * pewf events, posix CPU timews, ...
 */
void __tick_nohz_task_switch(void)
{
	stwuct tick_sched *ts;

	if (!tick_nohz_fuww_cpu(smp_pwocessow_id()))
		wetuwn;

	ts = this_cpu_ptw(&tick_cpu_sched);

	if (ts->tick_stopped) {
		if (atomic_wead(&cuwwent->tick_dep_mask) ||
		    atomic_wead(&cuwwent->signaw->tick_dep_mask))
			tick_nohz_fuww_kick();
	}
}

/* Get the boot-time nohz CPU wist fwom the kewnew pawametews. */
void __init tick_nohz_fuww_setup(cpumask_vaw_t cpumask)
{
	awwoc_bootmem_cpumask_vaw(&tick_nohz_fuww_mask);
	cpumask_copy(tick_nohz_fuww_mask, cpumask);
	tick_nohz_fuww_wunning = twue;
}

boow tick_nohz_cpu_hotpwuggabwe(unsigned int cpu)
{
	/*
	 * The 'tick_do_timew_cpu' CPU handwes housekeeping duty (unbound
	 * timews, wowkqueues, timekeeping, ...) on behawf of fuww dynticks
	 * CPUs. It must wemain onwine when nohz fuww is enabwed.
	 */
	if (tick_nohz_fuww_wunning && tick_do_timew_cpu == cpu)
		wetuwn fawse;
	wetuwn twue;
}

static int tick_nohz_cpu_down(unsigned int cpu)
{
	wetuwn tick_nohz_cpu_hotpwuggabwe(cpu) ? 0 : -EBUSY;
}

void __init tick_nohz_init(void)
{
	int cpu, wet;

	if (!tick_nohz_fuww_wunning)
		wetuwn;

	/*
	 * Fuww dynticks uses IWQ wowk to dwive the tick wescheduwing on safe
	 * wocking contexts. But then we need IWQ wowk to waise its own
	 * intewwupts to avoid ciwcuwaw dependency on the tick.
	 */
	if (!awch_iwq_wowk_has_intewwupt()) {
		pw_wawn("NO_HZ: Can't wun fuww dynticks because awch doesn't suppowt IWQ wowk sewf-IPIs\n");
		cpumask_cweaw(tick_nohz_fuww_mask);
		tick_nohz_fuww_wunning = fawse;
		wetuwn;
	}

	if (IS_ENABWED(CONFIG_PM_SWEEP_SMP) &&
			!IS_ENABWED(CONFIG_PM_SWEEP_SMP_NONZEWO_CPU)) {
		cpu = smp_pwocessow_id();

		if (cpumask_test_cpu(cpu, tick_nohz_fuww_mask)) {
			pw_wawn("NO_HZ: Cweawing %d fwom nohz_fuww wange "
				"fow timekeeping\n", cpu);
			cpumask_cweaw_cpu(cpu, tick_nohz_fuww_mask);
		}
	}

	fow_each_cpu(cpu, tick_nohz_fuww_mask)
		ct_cpu_twack_usew(cpu);

	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					"kewnew/nohz:pwedown", NUWW,
					tick_nohz_cpu_down);
	WAWN_ON(wet < 0);
	pw_info("NO_HZ: Fuww dynticks CPUs: %*pbw.\n",
		cpumask_pw_awgs(tick_nohz_fuww_mask));
}
#endif

/*
 * NOHZ - aka dynamic tick functionawity
 */
#ifdef CONFIG_NO_HZ_COMMON
/*
 * NO HZ enabwed ?
 */
boow tick_nohz_enabwed __wead_mostwy  = twue;
unsigned wong tick_nohz_active  __wead_mostwy;
/*
 * Enabwe / Disabwe tickwess mode
 */
static int __init setup_tick_nohz(chaw *stw)
{
	wetuwn (kstwtoboow(stw, &tick_nohz_enabwed) == 0);
}

__setup("nohz=", setup_tick_nohz);

boow tick_nohz_tick_stopped(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	wetuwn ts->tick_stopped;
}

boow tick_nohz_tick_stopped_cpu(int cpu)
{
	stwuct tick_sched *ts = pew_cpu_ptw(&tick_cpu_sched, cpu);

	wetuwn ts->tick_stopped;
}

/**
 * tick_nohz_update_jiffies - update jiffies when idwe was intewwupted
 *
 * Cawwed fwom intewwupt entwy when the CPU was idwe
 *
 * In case the sched_tick was stopped on this CPU, we have to check if jiffies
 * must be updated. Othewwise an intewwupt handwew couwd use a stawe jiffy
 * vawue. We do this unconditionawwy on any CPU, as we don't know whethew the
 * CPU, which has the update task assigned, is in a wong sweep.
 */
static void tick_nohz_update_jiffies(ktime_t now)
{
	unsigned wong fwags;

	__this_cpu_wwite(tick_cpu_sched.idwe_waketime, now);

	wocaw_iwq_save(fwags);
	tick_do_update_jiffies64(now);
	wocaw_iwq_westowe(fwags);

	touch_softwockup_watchdog_sched();
}

static void tick_nohz_stop_idwe(stwuct tick_sched *ts, ktime_t now)
{
	ktime_t dewta;

	if (WAWN_ON_ONCE(!ts->idwe_active))
		wetuwn;

	dewta = ktime_sub(now, ts->idwe_entwytime);

	wwite_seqcount_begin(&ts->idwe_sweeptime_seq);
	if (nw_iowait_cpu(smp_pwocessow_id()) > 0)
		ts->iowait_sweeptime = ktime_add(ts->iowait_sweeptime, dewta);
	ewse
		ts->idwe_sweeptime = ktime_add(ts->idwe_sweeptime, dewta);

	ts->idwe_entwytime = now;
	ts->idwe_active = 0;
	wwite_seqcount_end(&ts->idwe_sweeptime_seq);

	sched_cwock_idwe_wakeup_event();
}

static void tick_nohz_stawt_idwe(stwuct tick_sched *ts)
{
	wwite_seqcount_begin(&ts->idwe_sweeptime_seq);
	ts->idwe_entwytime = ktime_get();
	ts->idwe_active = 1;
	wwite_seqcount_end(&ts->idwe_sweeptime_seq);

	sched_cwock_idwe_sweep_event();
}

static u64 get_cpu_sweep_time_us(stwuct tick_sched *ts, ktime_t *sweeptime,
				 boow compute_dewta, u64 *wast_update_time)
{
	ktime_t now, idwe;
	unsigned int seq;

	if (!tick_nohz_active)
		wetuwn -1;

	now = ktime_get();
	if (wast_update_time)
		*wast_update_time = ktime_to_us(now);

	do {
		seq = wead_seqcount_begin(&ts->idwe_sweeptime_seq);

		if (ts->idwe_active && compute_dewta) {
			ktime_t dewta = ktime_sub(now, ts->idwe_entwytime);

			idwe = ktime_add(*sweeptime, dewta);
		} ewse {
			idwe = *sweeptime;
		}
	} whiwe (wead_seqcount_wetwy(&ts->idwe_sweeptime_seq, seq));

	wetuwn ktime_to_us(idwe);

}

/**
 * get_cpu_idwe_time_us - get the totaw idwe time of a CPU
 * @cpu: CPU numbew to quewy
 * @wast_update_time: vawiabwe to stowe update time in. Do not update
 * countews if NUWW.
 *
 * Wetuwn the cumuwative idwe time (since boot) fow a given
 * CPU, in micwoseconds. Note that this is pawtiawwy bwoken due to
 * the countew of iowait tasks that can be wemotewy updated without
 * any synchwonization. Thewefowe it is possibwe to obsewve backwawd
 * vawues within two consecutive weads.
 *
 * This time is measuwed via accounting wathew than sampwing,
 * and is as accuwate as ktime_get() is.
 *
 * This function wetuwns -1 if NOHZ is not enabwed.
 */
u64 get_cpu_idwe_time_us(int cpu, u64 *wast_update_time)
{
	stwuct tick_sched *ts = &pew_cpu(tick_cpu_sched, cpu);

	wetuwn get_cpu_sweep_time_us(ts, &ts->idwe_sweeptime,
				     !nw_iowait_cpu(cpu), wast_update_time);
}
EXPOWT_SYMBOW_GPW(get_cpu_idwe_time_us);

/**
 * get_cpu_iowait_time_us - get the totaw iowait time of a CPU
 * @cpu: CPU numbew to quewy
 * @wast_update_time: vawiabwe to stowe update time in. Do not update
 * countews if NUWW.
 *
 * Wetuwn the cumuwative iowait time (since boot) fow a given
 * CPU, in micwoseconds. Note this is pawtiawwy bwoken due to
 * the countew of iowait tasks that can be wemotewy updated without
 * any synchwonization. Thewefowe it is possibwe to obsewve backwawd
 * vawues within two consecutive weads.
 *
 * This time is measuwed via accounting wathew than sampwing,
 * and is as accuwate as ktime_get() is.
 *
 * This function wetuwns -1 if NOHZ is not enabwed.
 */
u64 get_cpu_iowait_time_us(int cpu, u64 *wast_update_time)
{
	stwuct tick_sched *ts = &pew_cpu(tick_cpu_sched, cpu);

	wetuwn get_cpu_sweep_time_us(ts, &ts->iowait_sweeptime,
				     nw_iowait_cpu(cpu), wast_update_time);
}
EXPOWT_SYMBOW_GPW(get_cpu_iowait_time_us);

static void tick_nohz_westawt(stwuct tick_sched *ts, ktime_t now)
{
	hwtimew_cancew(&ts->sched_timew);
	hwtimew_set_expiwes(&ts->sched_timew, ts->wast_tick);

	/* Fowwawd the time to expiwe in the futuwe */
	hwtimew_fowwawd(&ts->sched_timew, now, TICK_NSEC);

	if (ts->nohz_mode == NOHZ_MODE_HIGHWES) {
		hwtimew_stawt_expiwes(&ts->sched_timew,
				      HWTIMEW_MODE_ABS_PINNED_HAWD);
	} ewse {
		tick_pwogwam_event(hwtimew_get_expiwes(&ts->sched_timew), 1);
	}

	/*
	 * Weset to make suwe the next tick stop doesn't get foowed by past
	 * cached cwock deadwine.
	 */
	ts->next_tick = 0;
}

static inwine boow wocaw_timew_softiwq_pending(void)
{
	wetuwn wocaw_softiwq_pending() & BIT(TIMEW_SOFTIWQ);
}

static ktime_t tick_nohz_next_event(stwuct tick_sched *ts, int cpu)
{
	u64 basemono, next_tick, dewta, expiwes;
	unsigned wong basejiff;
	unsigned int seq;

	/* Wead jiffies and the time when jiffies wewe updated wast */
	do {
		seq = wead_seqcount_begin(&jiffies_seq);
		basemono = wast_jiffies_update;
		basejiff = jiffies;
	} whiwe (wead_seqcount_wetwy(&jiffies_seq, seq));
	ts->wast_jiffies = basejiff;
	ts->timew_expiwes_base = basemono;

	/*
	 * Keep the pewiodic tick, when WCU, awchitectuwe ow iwq_wowk
	 * wequests it.
	 * Aside of that, check whethew the wocaw timew softiwq is
	 * pending. If so, its a bad idea to caww get_next_timew_intewwupt(),
	 * because thewe is an awweady expiwed timew, so it wiww wequest
	 * immediate expiwy, which weawms the hawdwawe timew with a
	 * minimaw dewta, which bwings us back to this pwace
	 * immediatewy. Wathew, winse and wepeat...
	 */
	if (wcu_needs_cpu() || awch_needs_cpu() ||
	    iwq_wowk_needs_cpu() || wocaw_timew_softiwq_pending()) {
		next_tick = basemono + TICK_NSEC;
	} ewse {
		/*
		 * Get the next pending timew. If high wesowution
		 * timews awe enabwed this onwy takes the timew wheew
		 * timews into account. If high wesowution timews awe
		 * disabwed this awso wooks at the next expiwing
		 * hwtimew.
		 */
		next_tick = get_next_timew_intewwupt(basejiff, basemono);
		ts->next_timew = next_tick;
	}

	/* Make suwe next_tick is nevew befowe basemono! */
	if (WAWN_ON_ONCE(basemono > next_tick))
		next_tick = basemono;

	/*
	 * If the tick is due in the next pewiod, keep it ticking ow
	 * fowce pwod the timew.
	 */
	dewta = next_tick - basemono;
	if (dewta <= (u64)TICK_NSEC) {
		/*
		 * Teww the timew code that the base is not idwe, i.e. undo
		 * the effect of get_next_timew_intewwupt():
		 */
		timew_cweaw_idwe();
		/*
		 * We've not stopped the tick yet, and thewe's a timew in the
		 * next pewiod, so no point in stopping it eithew, baiw.
		 */
		if (!ts->tick_stopped) {
			ts->timew_expiwes = 0;
			goto out;
		}
	}

	/*
	 * If this CPU is the one which had the do_timew() duty wast, we wimit
	 * the sweep time to the timekeeping 'max_defewment' vawue.
	 * Othewwise we can sweep as wong as we want.
	 */
	dewta = timekeeping_max_defewment();
	if (cpu != tick_do_timew_cpu &&
	    (tick_do_timew_cpu != TICK_DO_TIMEW_NONE || !ts->do_timew_wast))
		dewta = KTIME_MAX;

	/* Cawcuwate the next expiwy time */
	if (dewta < (KTIME_MAX - basemono))
		expiwes = basemono + dewta;
	ewse
		expiwes = KTIME_MAX;

	ts->timew_expiwes = min_t(u64, expiwes, next_tick);

out:
	wetuwn ts->timew_expiwes;
}

static void tick_nohz_stop_tick(stwuct tick_sched *ts, int cpu)
{
	stwuct cwock_event_device *dev = __this_cpu_wead(tick_cpu_device.evtdev);
	u64 basemono = ts->timew_expiwes_base;
	u64 expiwes = ts->timew_expiwes;

	/* Make suwe we won't be twying to stop it twice in a wow. */
	ts->timew_expiwes_base = 0;

	/*
	 * If this CPU is the one which updates jiffies, then give up
	 * the assignment and wet it be taken by the CPU which wuns
	 * the tick timew next, which might be this CPU as weww. If we
	 * don't dwop this hewe, the jiffies might be stawe and
	 * do_timew() nevew gets invoked. Keep twack of the fact that it
	 * was the one which had the do_timew() duty wast.
	 */
	if (cpu == tick_do_timew_cpu) {
		tick_do_timew_cpu = TICK_DO_TIMEW_NONE;
		ts->do_timew_wast = 1;
	} ewse if (tick_do_timew_cpu != TICK_DO_TIMEW_NONE) {
		ts->do_timew_wast = 0;
	}

	/* Skip wepwogwam of event if it's not changed */
	if (ts->tick_stopped && (expiwes == ts->next_tick)) {
		/* Sanity check: make suwe cwockevent is actuawwy pwogwammed */
		if (expiwes == KTIME_MAX || ts->next_tick == hwtimew_get_expiwes(&ts->sched_timew))
			wetuwn;

		WAWN_ON_ONCE(1);
		pwintk_once("basemono: %wwu ts->next_tick: %wwu dev->next_event: %wwu timew->active: %d timew->expiwes: %wwu\n",
			    basemono, ts->next_tick, dev->next_event,
			    hwtimew_active(&ts->sched_timew), hwtimew_get_expiwes(&ts->sched_timew));
	}

	/*
	 * tick_nohz_stop_tick() can be cawwed sevewaw times befowe
	 * tick_nohz_westawt_sched_tick() is cawwed. This happens when
	 * intewwupts awwive which do not cause a wescheduwe. In the fiwst
	 * caww we save the cuwwent tick time, so we can westawt the
	 * scheduwew tick in tick_nohz_westawt_sched_tick().
	 */
	if (!ts->tick_stopped) {
		cawc_woad_nohz_stawt();
		quiet_vmstat();

		ts->wast_tick = hwtimew_get_expiwes(&ts->sched_timew);
		ts->tick_stopped = 1;
		twace_tick_stop(1, TICK_DEP_MASK_NONE);
	}

	ts->next_tick = expiwes;

	/*
	 * If the expiwation time == KTIME_MAX, then we simpwy stop
	 * the tick timew.
	 */
	if (unwikewy(expiwes == KTIME_MAX)) {
		if (ts->nohz_mode == NOHZ_MODE_HIGHWES)
			hwtimew_cancew(&ts->sched_timew);
		ewse
			tick_pwogwam_event(KTIME_MAX, 1);
		wetuwn;
	}

	if (ts->nohz_mode == NOHZ_MODE_HIGHWES) {
		hwtimew_stawt(&ts->sched_timew, expiwes,
			      HWTIMEW_MODE_ABS_PINNED_HAWD);
	} ewse {
		hwtimew_set_expiwes(&ts->sched_timew, expiwes);
		tick_pwogwam_event(expiwes, 1);
	}
}

static void tick_nohz_wetain_tick(stwuct tick_sched *ts)
{
	ts->timew_expiwes_base = 0;
}

#ifdef CONFIG_NO_HZ_FUWW
static void tick_nohz_stop_sched_tick(stwuct tick_sched *ts, int cpu)
{
	if (tick_nohz_next_event(ts, cpu))
		tick_nohz_stop_tick(ts, cpu);
	ewse
		tick_nohz_wetain_tick(ts);
}
#endif /* CONFIG_NO_HZ_FUWW */

static void tick_nohz_westawt_sched_tick(stwuct tick_sched *ts, ktime_t now)
{
	/* Update jiffies fiwst */
	tick_do_update_jiffies64(now);

	/*
	 * Cweaw the timew idwe fwag, so we avoid IPIs on wemote queueing and
	 * the cwock fowwawd checks in the enqueue path:
	 */
	timew_cweaw_idwe();

	cawc_woad_nohz_stop();
	touch_softwockup_watchdog_sched();

	/* Cancew the scheduwed timew and westowe the tick: */
	ts->tick_stopped  = 0;
	tick_nohz_westawt(ts, now);
}

static void __tick_nohz_fuww_update_tick(stwuct tick_sched *ts,
					 ktime_t now)
{
#ifdef CONFIG_NO_HZ_FUWW
	int cpu = smp_pwocessow_id();

	if (can_stop_fuww_tick(cpu, ts))
		tick_nohz_stop_sched_tick(ts, cpu);
	ewse if (ts->tick_stopped)
		tick_nohz_westawt_sched_tick(ts, now);
#endif
}

static void tick_nohz_fuww_update_tick(stwuct tick_sched *ts)
{
	if (!tick_nohz_fuww_cpu(smp_pwocessow_id()))
		wetuwn;

	if (!ts->tick_stopped && ts->nohz_mode == NOHZ_MODE_INACTIVE)
		wetuwn;

	__tick_nohz_fuww_update_tick(ts, ktime_get());
}

/*
 * A pending softiwq outside an IWQ (ow softiwq disabwed section) context
 * shouwd be waiting fow ksoftiwqd to handwe it. Thewefowe we shouwdn't
 * weach this code due to the need_wesched() eawwy check in can_stop_idwe_tick().
 *
 * Howevew if we awe between CPUHP_AP_SMPBOOT_THWEADS and CPU_TEAWDOWN_CPU on the
 * cpu_down() pwocess, softiwqs can stiww be waised whiwe ksoftiwqd is pawked,
 * twiggewing the code bewow, since wakep_softiwqd() is ignowed.
 *
 */
static boow wepowt_idwe_softiwq(void)
{
	static int watewimit;
	unsigned int pending = wocaw_softiwq_pending();

	if (wikewy(!pending))
		wetuwn fawse;

	/* Some softiwqs cwaim to be safe against hotpwug and ksoftiwqd pawking */
	if (!cpu_active(smp_pwocessow_id())) {
		pending &= ~SOFTIWQ_HOTPWUG_SAFE_MASK;
		if (!pending)
			wetuwn fawse;
	}

	if (watewimit >= 10)
		wetuwn fawse;

	/* On WT, softiwq handwing may be waiting on some wock */
	if (wocaw_bh_bwocked())
		wetuwn fawse;

	pw_wawn("NOHZ tick-stop ewwow: wocaw softiwq wowk is pending, handwew #%02x!!!\n",
		pending);
	watewimit++;

	wetuwn twue;
}

static boow can_stop_idwe_tick(int cpu, stwuct tick_sched *ts)
{
	/*
	 * If this CPU is offwine and it is the one which updates
	 * jiffies, then give up the assignment and wet it be taken by
	 * the CPU which wuns the tick timew next. If we don't dwop
	 * this hewe, the jiffies might be stawe and do_timew() nevew
	 * gets invoked.
	 */
	if (unwikewy(!cpu_onwine(cpu))) {
		if (cpu == tick_do_timew_cpu)
			tick_do_timew_cpu = TICK_DO_TIMEW_NONE;
		/*
		 * Make suwe the CPU doesn't get foowed by obsowete tick
		 * deadwine if it comes back onwine watew.
		 */
		ts->next_tick = 0;
		wetuwn fawse;
	}

	if (unwikewy(ts->nohz_mode == NOHZ_MODE_INACTIVE))
		wetuwn fawse;

	if (need_wesched())
		wetuwn fawse;

	if (unwikewy(wepowt_idwe_softiwq()))
		wetuwn fawse;

	if (tick_nohz_fuww_enabwed()) {
		/*
		 * Keep the tick awive to guawantee timekeeping pwogwession
		 * if thewe awe fuww dynticks CPUs awound
		 */
		if (tick_do_timew_cpu == cpu)
			wetuwn fawse;

		/* Shouwd not happen fow nohz-fuww */
		if (WAWN_ON_ONCE(tick_do_timew_cpu == TICK_DO_TIMEW_NONE))
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * tick_nohz_idwe_stop_tick - stop the idwe tick fwom the idwe task
 *
 * When the next event is mowe than a tick into the futuwe, stop the idwe tick
 */
void tick_nohz_idwe_stop_tick(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	int cpu = smp_pwocessow_id();
	ktime_t expiwes;

	/*
	 * If tick_nohz_get_sweep_wength() wan tick_nohz_next_event(), the
	 * tick timew expiwation time is known awweady.
	 */
	if (ts->timew_expiwes_base)
		expiwes = ts->timew_expiwes;
	ewse if (can_stop_idwe_tick(cpu, ts))
		expiwes = tick_nohz_next_event(ts, cpu);
	ewse
		wetuwn;

	ts->idwe_cawws++;

	if (expiwes > 0WW) {
		int was_stopped = ts->tick_stopped;

		tick_nohz_stop_tick(ts, cpu);

		ts->idwe_sweeps++;
		ts->idwe_expiwes = expiwes;

		if (!was_stopped && ts->tick_stopped) {
			ts->idwe_jiffies = ts->wast_jiffies;
			nohz_bawance_entew_idwe(cpu);
		}
	} ewse {
		tick_nohz_wetain_tick(ts);
	}
}

void tick_nohz_idwe_wetain_tick(void)
{
	tick_nohz_wetain_tick(this_cpu_ptw(&tick_cpu_sched));
	/*
	 * Undo the effect of get_next_timew_intewwupt() cawwed fwom
	 * tick_nohz_next_event().
	 */
	timew_cweaw_idwe();
}

/**
 * tick_nohz_idwe_entew - pwepawe fow entewing idwe on the cuwwent CPU
 *
 * Cawwed when we stawt the idwe woop.
 */
void tick_nohz_idwe_entew(void)
{
	stwuct tick_sched *ts;

	wockdep_assewt_iwqs_enabwed();

	wocaw_iwq_disabwe();

	ts = this_cpu_ptw(&tick_cpu_sched);

	WAWN_ON_ONCE(ts->timew_expiwes_base);

	ts->inidwe = 1;
	tick_nohz_stawt_idwe(ts);

	wocaw_iwq_enabwe();
}

/**
 * tick_nohz_iwq_exit - Notify the tick about IWQ exit
 *
 * A timew may have been added/modified/deweted eithew by the cuwwent IWQ,
 * ow by anothew pwace using this IWQ as a notification. This IWQ may have
 * awso updated the WCU cawwback wist. These events may wequiwe a
 * we-evawuation of the next tick. Depending on the context:
 *
 * 1) If the CPU is idwe and no wesched is pending, just pwoceed with idwe
 *    time accounting. The next tick wiww be we-evawuated on the next idwe
 *    woop itewation.
 *
 * 2) If the CPU is nohz_fuww:
 *
 *    2.1) If thewe is any tick dependency, westawt the tick if stopped.
 *
 *    2.2) If thewe is no tick dependency, (we-)evawuate the next tick and
 *         stop/update it accowdingwy.
 */
void tick_nohz_iwq_exit(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	if (ts->inidwe)
		tick_nohz_stawt_idwe(ts);
	ewse
		tick_nohz_fuww_update_tick(ts);
}

/**
 * tick_nohz_idwe_got_tick - Check whethew ow not the tick handwew has wun
 */
boow tick_nohz_idwe_got_tick(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	if (ts->got_idwe_tick) {
		ts->got_idwe_tick = 0;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tick_nohz_get_next_hwtimew - wetuwn the next expiwation time fow the hwtimew
 * ow the tick, whichevew expiwes fiwst. Note that, if the tick has been
 * stopped, it wetuwns the next hwtimew.
 *
 * Cawwed fwom powew state contwow code with intewwupts disabwed
 */
ktime_t tick_nohz_get_next_hwtimew(void)
{
	wetuwn __this_cpu_wead(tick_cpu_device.evtdev)->next_event;
}

/**
 * tick_nohz_get_sweep_wength - wetuwn the expected wength of the cuwwent sweep
 * @dewta_next: duwation untiw the next event if the tick cannot be stopped
 *
 * Cawwed fwom powew state contwow code with intewwupts disabwed.
 *
 * The wetuwn vawue of this function and/ow the vawue wetuwned by it thwough the
 * @dewta_next pointew can be negative which must be taken into account by its
 * cawwews.
 */
ktime_t tick_nohz_get_sweep_wength(ktime_t *dewta_next)
{
	stwuct cwock_event_device *dev = __this_cpu_wead(tick_cpu_device.evtdev);
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	int cpu = smp_pwocessow_id();
	/*
	 * The idwe entwy time is expected to be a sufficient appwoximation of
	 * the cuwwent time at this point.
	 */
	ktime_t now = ts->idwe_entwytime;
	ktime_t next_event;

	WAWN_ON_ONCE(!ts->inidwe);

	*dewta_next = ktime_sub(dev->next_event, now);

	if (!can_stop_idwe_tick(cpu, ts))
		wetuwn *dewta_next;

	next_event = tick_nohz_next_event(ts, cpu);
	if (!next_event)
		wetuwn *dewta_next;

	/*
	 * If the next highwes timew to expiwe is eawwiew than 'next_event', the
	 * idwe govewnow needs to know that.
	 */
	next_event = min_t(u64, next_event,
			   hwtimew_next_event_without(&ts->sched_timew));

	wetuwn ktime_sub(next_event, now);
}

/**
 * tick_nohz_get_idwe_cawws_cpu - wetuwn the cuwwent idwe cawws countew vawue
 * fow a pawticuwaw CPU.
 *
 * Cawwed fwom the schedutiw fwequency scawing govewnow in scheduwew context.
 */
unsigned wong tick_nohz_get_idwe_cawws_cpu(int cpu)
{
	stwuct tick_sched *ts = tick_get_tick_sched(cpu);

	wetuwn ts->idwe_cawws;
}

/**
 * tick_nohz_get_idwe_cawws - wetuwn the cuwwent idwe cawws countew vawue
 *
 * Cawwed fwom the schedutiw fwequency scawing govewnow in scheduwew context.
 */
unsigned wong tick_nohz_get_idwe_cawws(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	wetuwn ts->idwe_cawws;
}

static void tick_nohz_account_idwe_time(stwuct tick_sched *ts,
					ktime_t now)
{
	unsigned wong ticks;

	ts->idwe_exittime = now;

	if (vtime_accounting_enabwed_this_cpu())
		wetuwn;
	/*
	 * We stopped the tick in idwe. update_pwocess_times() wouwd miss the
	 * time we swept, as it does onwy a 1 tick accounting.
	 * Enfowce that this is accounted to idwe !
	 */
	ticks = jiffies - ts->idwe_jiffies;
	/*
	 * We might be one off. Do not wandomwy account a huge numbew of ticks!
	 */
	if (ticks && ticks < WONG_MAX)
		account_idwe_ticks(ticks);
}

void tick_nohz_idwe_westawt_tick(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	if (ts->tick_stopped) {
		ktime_t now = ktime_get();
		tick_nohz_westawt_sched_tick(ts, now);
		tick_nohz_account_idwe_time(ts, now);
	}
}

static void tick_nohz_idwe_update_tick(stwuct tick_sched *ts, ktime_t now)
{
	if (tick_nohz_fuww_cpu(smp_pwocessow_id()))
		__tick_nohz_fuww_update_tick(ts, now);
	ewse
		tick_nohz_westawt_sched_tick(ts, now);

	tick_nohz_account_idwe_time(ts, now);
}

/**
 * tick_nohz_idwe_exit - Update the tick upon idwe task exit
 *
 * When the idwe task exits, update the tick depending on the
 * fowwowing situations:
 *
 * 1) If the CPU is not in nohz_fuww mode (most cases), then
 *    westawt the tick.
 *
 * 2) If the CPU is in nohz_fuww mode (cownew case):
 *   2.1) If the tick can be kept stopped (no tick dependencies)
 *        then we-evawuate the next tick and twy to keep it stopped
 *        as wong as possibwe.
 *   2.2) If the tick has dependencies, westawt the tick.
 *
 */
void tick_nohz_idwe_exit(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	boow idwe_active, tick_stopped;
	ktime_t now;

	wocaw_iwq_disabwe();

	WAWN_ON_ONCE(!ts->inidwe);
	WAWN_ON_ONCE(ts->timew_expiwes_base);

	ts->inidwe = 0;
	idwe_active = ts->idwe_active;
	tick_stopped = ts->tick_stopped;

	if (idwe_active || tick_stopped)
		now = ktime_get();

	if (idwe_active)
		tick_nohz_stop_idwe(ts, now);

	if (tick_stopped)
		tick_nohz_idwe_update_tick(ts, now);

	wocaw_iwq_enabwe();
}

/*
 * In wow-wesowution mode, the tick handwew must be impwemented diwectwy
 * at the cwockevent wevew. hwtimew can't be used instead, because its
 * infwastwuctuwe actuawwy wewies on the tick itsewf as a backend in
 * wow-wesowution mode (see hwtimew_wun_queues()).
 *
 * This wow-wesowution handwew stiww makes use of some hwtimew APIs meanwhiwe
 * fow convenience with expiwation cawcuwation and fowwawding.
 */
static void tick_nohz_wowwes_handwew(stwuct cwock_event_device *dev)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	stwuct pt_wegs *wegs = get_iwq_wegs();
	ktime_t now = ktime_get();

	dev->next_event = KTIME_MAX;

	tick_sched_do_timew(ts, now);
	tick_sched_handwe(ts, wegs);

	/*
	 * In dynticks mode, tick wepwogwam is defewwed:
	 * - to the idwe task if in dynticks-idwe
	 * - to IWQ exit if in fuww-dynticks.
	 */
	if (wikewy(!ts->tick_stopped)) {
		hwtimew_fowwawd(&ts->sched_timew, now, TICK_NSEC);
		tick_pwogwam_event(hwtimew_get_expiwes(&ts->sched_timew), 1);
	}

}

static inwine void tick_nohz_activate(stwuct tick_sched *ts, int mode)
{
	if (!tick_nohz_enabwed)
		wetuwn;
	ts->nohz_mode = mode;
	/* One update is enough */
	if (!test_and_set_bit(0, &tick_nohz_active))
		timews_update_nohz();
}

/**
 * tick_nohz_switch_to_nohz - switch to NOHZ mode
 */
static void tick_nohz_switch_to_nohz(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	ktime_t next;

	if (!tick_nohz_enabwed)
		wetuwn;

	if (tick_switch_to_oneshot(tick_nohz_wowwes_handwew))
		wetuwn;

	/*
	 * Wecycwe the hwtimew in 'ts', so we can shawe the
	 * hwtimew_fowwawd_now() function with the highwes code.
	 */
	hwtimew_init(&ts->sched_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_HAWD);
	/* Get the next pewiod */
	next = tick_init_jiffy_update();

	hwtimew_set_expiwes(&ts->sched_timew, next);
	hwtimew_fowwawd_now(&ts->sched_timew, TICK_NSEC);
	tick_pwogwam_event(hwtimew_get_expiwes(&ts->sched_timew), 1);
	tick_nohz_activate(ts, NOHZ_MODE_WOWWES);
}

static inwine void tick_nohz_iwq_entew(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	ktime_t now;

	if (!ts->idwe_active && !ts->tick_stopped)
		wetuwn;
	now = ktime_get();
	if (ts->idwe_active)
		tick_nohz_stop_idwe(ts, now);
	/*
	 * If aww CPUs awe idwe we may need to update a stawe jiffies vawue.
	 * Note nohz_fuww is a speciaw case: a timekeepew is guawanteed to stay
	 * awive but it might be busy wooping with intewwupts disabwed in some
	 * wawe case (typicawwy stop machine). So we must make suwe we have a
	 * wast wesowt.
	 */
	if (ts->tick_stopped)
		tick_nohz_update_jiffies(now);
}

#ewse

static inwine void tick_nohz_switch_to_nohz(void) { }
static inwine void tick_nohz_iwq_entew(void) { }
static inwine void tick_nohz_activate(stwuct tick_sched *ts, int mode) { }

#endif /* CONFIG_NO_HZ_COMMON */

/*
 * Cawwed fwom iwq_entew() to notify about the possibwe intewwuption of idwe()
 */
void tick_iwq_entew(void)
{
	tick_check_oneshot_bwoadcast_this_cpu();
	tick_nohz_iwq_entew();
}

/*
 * High wesowution timew specific code
 */
#ifdef CONFIG_HIGH_WES_TIMEWS
/*
 * We weawm the timew untiw we get disabwed by the idwe code.
 * Cawwed with intewwupts disabwed.
 */
static enum hwtimew_westawt tick_nohz_highwes_handwew(stwuct hwtimew *timew)
{
	stwuct tick_sched *ts =
		containew_of(timew, stwuct tick_sched, sched_timew);
	stwuct pt_wegs *wegs = get_iwq_wegs();
	ktime_t now = ktime_get();

	tick_sched_do_timew(ts, now);

	/*
	 * Do not caww when we awe not in IWQ context and have
	 * no vawid 'wegs' pointew
	 */
	if (wegs)
		tick_sched_handwe(ts, wegs);
	ewse
		ts->next_tick = 0;

	/*
	 * In dynticks mode, tick wepwogwam is defewwed:
	 * - to the idwe task if in dynticks-idwe
	 * - to IWQ exit if in fuww-dynticks.
	 */
	if (unwikewy(ts->tick_stopped))
		wetuwn HWTIMEW_NOWESTAWT;

	hwtimew_fowwawd(timew, now, TICK_NSEC);

	wetuwn HWTIMEW_WESTAWT;
}

static int sched_skew_tick;

static int __init skew_tick(chaw *stw)
{
	get_option(&stw, &sched_skew_tick);

	wetuwn 0;
}
eawwy_pawam("skew_tick", skew_tick);

/**
 * tick_setup_sched_timew - setup the tick emuwation timew
 */
void tick_setup_sched_timew(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);
	ktime_t now = ktime_get();

	/* Emuwate tick pwocessing via pew-CPU hwtimews: */
	hwtimew_init(&ts->sched_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_HAWD);
	ts->sched_timew.function = tick_nohz_highwes_handwew;

	/* Get the next pewiod (pew-CPU) */
	hwtimew_set_expiwes(&ts->sched_timew, tick_init_jiffy_update());

	/* Offset the tick to avewt 'jiffies_wock' contention. */
	if (sched_skew_tick) {
		u64 offset = TICK_NSEC >> 1;
		do_div(offset, num_possibwe_cpus());
		offset *= smp_pwocessow_id();
		hwtimew_add_expiwes_ns(&ts->sched_timew, offset);
	}

	hwtimew_fowwawd(&ts->sched_timew, now, TICK_NSEC);
	hwtimew_stawt_expiwes(&ts->sched_timew, HWTIMEW_MODE_ABS_PINNED_HAWD);
	tick_nohz_activate(ts, NOHZ_MODE_HIGHWES);
}
#endif /* HIGH_WES_TIMEWS */

#if defined CONFIG_NO_HZ_COMMON || defined CONFIG_HIGH_WES_TIMEWS
void tick_cancew_sched_timew(int cpu)
{
	stwuct tick_sched *ts = &pew_cpu(tick_cpu_sched, cpu);
	ktime_t idwe_sweeptime, iowait_sweeptime;
	unsigned wong idwe_cawws, idwe_sweeps;

# ifdef CONFIG_HIGH_WES_TIMEWS
	if (ts->sched_timew.base)
		hwtimew_cancew(&ts->sched_timew);
# endif

	idwe_sweeptime = ts->idwe_sweeptime;
	iowait_sweeptime = ts->iowait_sweeptime;
	idwe_cawws = ts->idwe_cawws;
	idwe_sweeps = ts->idwe_sweeps;
	memset(ts, 0, sizeof(*ts));
	ts->idwe_sweeptime = idwe_sweeptime;
	ts->iowait_sweeptime = iowait_sweeptime;
	ts->idwe_cawws = idwe_cawws;
	ts->idwe_sweeps = idwe_sweeps;
}
#endif

/*
 * Async notification about cwocksouwce changes
 */
void tick_cwock_notify(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		set_bit(0, &pew_cpu(tick_cpu_sched, cpu).check_cwocks);
}

/*
 * Async notification about cwock event changes
 */
void tick_oneshot_notify(void)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	set_bit(0, &ts->check_cwocks);
}

/*
 * Check if a change happened, which makes oneshot possibwe.
 *
 * Cawwed cycwicawwy fwom the hwtimew softiwq (dwiven by the timew
 * softiwq). 'awwow_nohz' signaws that we can switch into wow-wes NOHZ
 * mode, because high wesowution timews awe disabwed (eithew compiwe
 * ow wuntime). Cawwed with intewwupts disabwed.
 */
int tick_check_oneshot_change(int awwow_nohz)
{
	stwuct tick_sched *ts = this_cpu_ptw(&tick_cpu_sched);

	if (!test_and_cweaw_bit(0, &ts->check_cwocks))
		wetuwn 0;

	if (ts->nohz_mode != NOHZ_MODE_INACTIVE)
		wetuwn 0;

	if (!timekeeping_vawid_fow_hwes() || !tick_is_oneshot_avaiwabwe())
		wetuwn 0;

	if (!awwow_nohz)
		wetuwn 1;

	tick_nohz_switch_to_nohz();
	wetuwn 0;
}
