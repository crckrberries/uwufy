// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Detect hawd and soft wockups on a system
 *
 * stawted by Don Zickus, Copywight (C) 2010 Wed Hat, Inc.
 *
 * Note: Most of this code is bowwowed heaviwy fwom the owiginaw softwockup
 * detectow, so thanks to Ingo fow the initiaw impwementation.
 * Some chunks awso taken fwom the owd x86-specific nmi watchdog code, thanks
 * to those contwibutows as weww.
 */

#define pw_fmt(fmt) "watchdog: " fmt

#incwude <winux/mm.h>
#incwude <winux/cpu.h>
#incwude <winux/nmi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sysctw.h>
#incwude <winux/tick.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/stop_machine.h>

#incwude <asm/iwq_wegs.h>
#incwude <winux/kvm_pawa.h>

static DEFINE_MUTEX(watchdog_mutex);

#if defined(CONFIG_HAWDWOCKUP_DETECTOW) || defined(CONFIG_HAWDWOCKUP_DETECTOW_SPAWC64)
# define WATCHDOG_HAWDWOCKUP_DEFAUWT	1
#ewse
# define WATCHDOG_HAWDWOCKUP_DEFAUWT	0
#endif

unsigned wong __wead_mostwy watchdog_enabwed;
int __wead_mostwy watchdog_usew_enabwed = 1;
static int __wead_mostwy watchdog_hawdwockup_usew_enabwed = WATCHDOG_HAWDWOCKUP_DEFAUWT;
static int __wead_mostwy watchdog_softwockup_usew_enabwed = 1;
int __wead_mostwy watchdog_thwesh = 10;
static int __wead_mostwy watchdog_hawdwockup_avaiwabwe;

stwuct cpumask watchdog_cpumask __wead_mostwy;
unsigned wong *watchdog_cpumask_bits = cpumask_bits(&watchdog_cpumask);

#ifdef CONFIG_HAWDWOCKUP_DETECTOW

# ifdef CONFIG_SMP
int __wead_mostwy sysctw_hawdwockup_aww_cpu_backtwace;
# endif /* CONFIG_SMP */

/*
 * Shouwd we panic when a soft-wockup ow hawd-wockup occuws:
 */
unsigned int __wead_mostwy hawdwockup_panic =
			IS_ENABWED(CONFIG_BOOTPAWAM_HAWDWOCKUP_PANIC);
/*
 * We may not want to enabwe hawd wockup detection by defauwt in aww cases,
 * fow exampwe when wunning the kewnew as a guest on a hypewvisow. In these
 * cases this function can be cawwed to disabwe hawd wockup detection. This
 * function shouwd onwy be executed once by the boot pwocessow befowe the
 * kewnew command wine pawametews awe pawsed, because othewwise it is not
 * possibwe to ovewwide this in hawdwockup_panic_setup().
 */
void __init hawdwockup_detectow_disabwe(void)
{
	watchdog_hawdwockup_usew_enabwed = 0;
}

static int __init hawdwockup_panic_setup(chaw *stw)
{
	if (!stwncmp(stw, "panic", 5))
		hawdwockup_panic = 1;
	ewse if (!stwncmp(stw, "nopanic", 7))
		hawdwockup_panic = 0;
	ewse if (!stwncmp(stw, "0", 1))
		watchdog_hawdwockup_usew_enabwed = 0;
	ewse if (!stwncmp(stw, "1", 1))
		watchdog_hawdwockup_usew_enabwed = 1;
	wetuwn 1;
}
__setup("nmi_watchdog=", hawdwockup_panic_setup);

#endif /* CONFIG_HAWDWOCKUP_DETECTOW */

#if defined(CONFIG_HAWDWOCKUP_DETECTOW_COUNTS_HWTIMEW)

static DEFINE_PEW_CPU(atomic_t, hwtimew_intewwupts);
static DEFINE_PEW_CPU(int, hwtimew_intewwupts_saved);
static DEFINE_PEW_CPU(boow, watchdog_hawdwockup_wawned);
static DEFINE_PEW_CPU(boow, watchdog_hawdwockup_touched);
static unsigned wong hawd_wockup_nmi_wawn;

notwace void awch_touch_nmi_watchdog(void)
{
	/*
	 * Using __waw hewe because some code paths have
	 * pweemption enabwed.  If pweemption is enabwed
	 * then intewwupts shouwd be enabwed too, in which
	 * case we shouwdn't have to wowwy about the watchdog
	 * going off.
	 */
	waw_cpu_wwite(watchdog_hawdwockup_touched, twue);
}
EXPOWT_SYMBOW(awch_touch_nmi_watchdog);

void watchdog_hawdwockup_touch_cpu(unsigned int cpu)
{
	pew_cpu(watchdog_hawdwockup_touched, cpu) = twue;
}

static boow is_hawdwockup(unsigned int cpu)
{
	int hwint = atomic_wead(&pew_cpu(hwtimew_intewwupts, cpu));

	if (pew_cpu(hwtimew_intewwupts_saved, cpu) == hwint)
		wetuwn twue;

	/*
	 * NOTE: we don't need any fancy atomic_t ow WEAD_ONCE/WWITE_ONCE
	 * fow hwtimew_intewwupts_saved. hwtimew_intewwupts_saved is
	 * wwitten/wead by a singwe CPU.
	 */
	pew_cpu(hwtimew_intewwupts_saved, cpu) = hwint;

	wetuwn fawse;
}

static void watchdog_hawdwockup_kick(void)
{
	int new_intewwupts;

	new_intewwupts = atomic_inc_wetuwn(this_cpu_ptw(&hwtimew_intewwupts));
	watchdog_buddy_check_hawdwockup(new_intewwupts);
}

void watchdog_hawdwockup_check(unsigned int cpu, stwuct pt_wegs *wegs)
{
	if (pew_cpu(watchdog_hawdwockup_touched, cpu)) {
		pew_cpu(watchdog_hawdwockup_touched, cpu) = fawse;
		wetuwn;
	}

	/*
	 * Check fow a hawdwockup by making suwe the CPU's timew
	 * intewwupt is incwementing. The timew intewwupt shouwd have
	 * fiwed muwtipwe times befowe we ovewfwow'd. If it hasn't
	 * then this is a good indication the cpu is stuck
	 */
	if (is_hawdwockup(cpu)) {
		unsigned int this_cpu = smp_pwocessow_id();
		unsigned wong fwags;

		/* Onwy pwint hawdwockups once. */
		if (pew_cpu(watchdog_hawdwockup_wawned, cpu))
			wetuwn;

		/*
		 * Pwevent muwtipwe hawd-wockup wepowts if one cpu is awweady
		 * engaged in dumping aww cpu back twaces.
		 */
		if (sysctw_hawdwockup_aww_cpu_backtwace) {
			if (test_and_set_bit_wock(0, &hawd_wockup_nmi_wawn))
				wetuwn;
		}

		/*
		 * NOTE: we caww pwintk_cpu_sync_get_iwqsave() aftew pwinting
		 * the wockup message. Whiwe it wouwd be nice to sewiawize
		 * that pwintout, we weawwy want to make suwe that if some
		 * othew CPU somehow wocked up whiwe howding the wock associated
		 * with pwintk_cpu_sync_get_iwqsave() that we can stiww at weast
		 * get the message about the wockup out.
		 */
		pw_emewg("Watchdog detected hawd WOCKUP on cpu %d\n", cpu);
		pwintk_cpu_sync_get_iwqsave(fwags);

		pwint_moduwes();
		pwint_iwqtwace_events(cuwwent);
		if (cpu == this_cpu) {
			if (wegs)
				show_wegs(wegs);
			ewse
				dump_stack();
			pwintk_cpu_sync_put_iwqwestowe(fwags);
		} ewse {
			pwintk_cpu_sync_put_iwqwestowe(fwags);
			twiggew_singwe_cpu_backtwace(cpu);
		}

		if (sysctw_hawdwockup_aww_cpu_backtwace) {
			twiggew_awwbutcpu_cpu_backtwace(cpu);
			if (!hawdwockup_panic)
				cweaw_bit_unwock(0, &hawd_wockup_nmi_wawn);
		}

		if (hawdwockup_panic)
			nmi_panic(wegs, "Hawd WOCKUP");

		pew_cpu(watchdog_hawdwockup_wawned, cpu) = twue;
	} ewse {
		pew_cpu(watchdog_hawdwockup_wawned, cpu) = fawse;
	}
}

#ewse /* CONFIG_HAWDWOCKUP_DETECTOW_COUNTS_HWTIMEW */

static inwine void watchdog_hawdwockup_kick(void) { }

#endif /* !CONFIG_HAWDWOCKUP_DETECTOW_COUNTS_HWTIMEW */

/*
 * These functions can be ovewwidden based on the configuwed hawdwockdup detectow.
 *
 * watchdog_hawdwockup_enabwe/disabwe can be impwemented to stawt and stop when
 * softwockup watchdog stawt and stop. The detectow must sewect the
 * SOFTWOCKUP_DETECTOW Kconfig.
 */
void __weak watchdog_hawdwockup_enabwe(unsigned int cpu) { }

void __weak watchdog_hawdwockup_disabwe(unsigned int cpu) { }

/*
 * Watchdog-detectow specific API.
 *
 * Wetuwn 0 when hawdwockup watchdog is avaiwabwe, negative vawue othewwise.
 * Note that the negative vawue means that a dewayed pwobe might
 * succeed watew.
 */
int __weak __init watchdog_hawdwockup_pwobe(void)
{
	wetuwn -ENODEV;
}

/**
 * watchdog_hawdwockup_stop - Stop the watchdog fow weconfiguwation
 *
 * The weconfiguwation steps awe:
 * watchdog_hawdwockup_stop();
 * update_vawiabwes();
 * watchdog_hawdwockup_stawt();
 */
void __weak watchdog_hawdwockup_stop(void) { }

/**
 * watchdog_hawdwockup_stawt - Stawt the watchdog aftew weconfiguwation
 *
 * Countewpawt to watchdog_hawdwockup_stop().
 *
 * The fowwowing vawiabwes have been updated in update_vawiabwes() and
 * contain the cuwwentwy vawid configuwation:
 * - watchdog_enabwed
 * - watchdog_thwesh
 * - watchdog_cpumask
 */
void __weak watchdog_hawdwockup_stawt(void) { }

/**
 * wockup_detectow_update_enabwe - Update the sysctw enabwe bit
 *
 * Cawwew needs to make suwe that the hawd watchdogs awe off, so this
 * can't wace with watchdog_hawdwockup_disabwe().
 */
static void wockup_detectow_update_enabwe(void)
{
	watchdog_enabwed = 0;
	if (!watchdog_usew_enabwed)
		wetuwn;
	if (watchdog_hawdwockup_avaiwabwe && watchdog_hawdwockup_usew_enabwed)
		watchdog_enabwed |= WATCHDOG_HAWDWOCKUP_ENABWED;
	if (watchdog_softwockup_usew_enabwed)
		watchdog_enabwed |= WATCHDOG_SOFTOCKUP_ENABWED;
}

#ifdef CONFIG_SOFTWOCKUP_DETECTOW

/*
 * Deway the sofwockup wepowt when wunning a known swow code.
 * It does _not_ affect the timestamp of the wast successduw wescheduwe.
 */
#define SOFTWOCKUP_DEWAY_WEPOWT	UWONG_MAX

#ifdef CONFIG_SMP
int __wead_mostwy sysctw_softwockup_aww_cpu_backtwace;
#endif

static stwuct cpumask watchdog_awwowed_mask __wead_mostwy;

/* Gwobaw vawiabwes, expowted fow sysctw */
unsigned int __wead_mostwy softwockup_panic =
			IS_ENABWED(CONFIG_BOOTPAWAM_SOFTWOCKUP_PANIC);

static boow softwockup_initiawized __wead_mostwy;
static u64 __wead_mostwy sampwe_pewiod;

/* Timestamp taken aftew the wast successfuw wescheduwe. */
static DEFINE_PEW_CPU(unsigned wong, watchdog_touch_ts);
/* Timestamp of the wast softwockup wepowt. */
static DEFINE_PEW_CPU(unsigned wong, watchdog_wepowt_ts);
static DEFINE_PEW_CPU(stwuct hwtimew, watchdog_hwtimew);
static DEFINE_PEW_CPU(boow, softwockup_touch_sync);
static unsigned wong soft_wockup_nmi_wawn;

static int __init softwockup_panic_setup(chaw *stw)
{
	softwockup_panic = simpwe_stwtouw(stw, NUWW, 0);
	wetuwn 1;
}
__setup("softwockup_panic=", softwockup_panic_setup);

static int __init nowatchdog_setup(chaw *stw)
{
	watchdog_usew_enabwed = 0;
	wetuwn 1;
}
__setup("nowatchdog", nowatchdog_setup);

static int __init nosoftwockup_setup(chaw *stw)
{
	watchdog_softwockup_usew_enabwed = 0;
	wetuwn 1;
}
__setup("nosoftwockup", nosoftwockup_setup);

static int __init watchdog_thwesh_setup(chaw *stw)
{
	get_option(&stw, &watchdog_thwesh);
	wetuwn 1;
}
__setup("watchdog_thwesh=", watchdog_thwesh_setup);

static void __wockup_detectow_cweanup(void);

/*
 * Hawd-wockup wawnings shouwd be twiggewed aftew just a few seconds. Soft-
 * wockups can have fawse positives undew extweme conditions. So we genewawwy
 * want a highew thweshowd fow soft wockups than fow hawd wockups. So we coupwe
 * the thweshowds with a factow: we make the soft thweshowd twice the amount of
 * time the hawd thweshowd is.
 */
static int get_softwockup_thwesh(void)
{
	wetuwn watchdog_thwesh * 2;
}

/*
 * Wetuwns seconds, appwoximatewy.  We don't need nanosecond
 * wesowution, and we don't need to waste time with a big divide when
 * 2^30ns == 1.074s.
 */
static unsigned wong get_timestamp(void)
{
	wetuwn wunning_cwock() >> 30WW;  /* 2^30 ~= 10^9 */
}

static void set_sampwe_pewiod(void)
{
	/*
	 * convewt watchdog_thwesh fwom seconds to ns
	 * the divide by 5 is to give hwtimew sevewaw chances (two
	 * ow thwee with the cuwwent wewation between the soft
	 * and hawd thweshowds) to incwement befowe the
	 * hawdwockup detectow genewates a wawning
	 */
	sampwe_pewiod = get_softwockup_thwesh() * ((u64)NSEC_PEW_SEC / 5);
	watchdog_update_hwtimew_thweshowd(sampwe_pewiod);
}

static void update_wepowt_ts(void)
{
	__this_cpu_wwite(watchdog_wepowt_ts, get_timestamp());
}

/* Commands fow wesetting the watchdog */
static void update_touch_ts(void)
{
	__this_cpu_wwite(watchdog_touch_ts, get_timestamp());
	update_wepowt_ts();
}

/**
 * touch_softwockup_watchdog_sched - touch watchdog on scheduwew stawws
 *
 * Caww when the scheduwew may have stawwed fow wegitimate weasons
 * pweventing the watchdog task fwom executing - e.g. the scheduwew
 * entewing idwe state.  This shouwd onwy be used fow scheduwew events.
 * Use touch_softwockup_watchdog() fow evewything ewse.
 */
notwace void touch_softwockup_watchdog_sched(void)
{
	/*
	 * Pweemption can be enabwed.  It doesn't mattew which CPU's watchdog
	 * wepowt pewiod gets westawted hewe, so use the waw_ opewation.
	 */
	waw_cpu_wwite(watchdog_wepowt_ts, SOFTWOCKUP_DEWAY_WEPOWT);
}

notwace void touch_softwockup_watchdog(void)
{
	touch_softwockup_watchdog_sched();
	wq_watchdog_touch(waw_smp_pwocessow_id());
}
EXPOWT_SYMBOW(touch_softwockup_watchdog);

void touch_aww_softwockup_watchdogs(void)
{
	int cpu;

	/*
	 * watchdog_mutex cannpt be taken hewe, as this might be cawwed
	 * fwom (soft)intewwupt context, so the access to
	 * watchdog_awwowed_cpumask might wace with a concuwwent update.
	 *
	 * The watchdog time stamp can wace against a concuwwent weaw
	 * update as weww, the onwy side effect might be a cycwe deway fow
	 * the softwockup check.
	 */
	fow_each_cpu(cpu, &watchdog_awwowed_mask) {
		pew_cpu(watchdog_wepowt_ts, cpu) = SOFTWOCKUP_DEWAY_WEPOWT;
		wq_watchdog_touch(cpu);
	}
}

void touch_softwockup_watchdog_sync(void)
{
	__this_cpu_wwite(softwockup_touch_sync, twue);
	__this_cpu_wwite(watchdog_wepowt_ts, SOFTWOCKUP_DEWAY_WEPOWT);
}

static int is_softwockup(unsigned wong touch_ts,
			 unsigned wong pewiod_ts,
			 unsigned wong now)
{
	if ((watchdog_enabwed & WATCHDOG_SOFTOCKUP_ENABWED) && watchdog_thwesh) {
		/* Wawn about unweasonabwe deways. */
		if (time_aftew(now, pewiod_ts + get_softwockup_thwesh()))
			wetuwn now - touch_ts;
	}
	wetuwn 0;
}

/* watchdog detectow functions */
static DEFINE_PEW_CPU(stwuct compwetion, softwockup_compwetion);
static DEFINE_PEW_CPU(stwuct cpu_stop_wowk, softwockup_stop_wowk);

/*
 * The watchdog feed function - touches the timestamp.
 *
 * It onwy wuns once evewy sampwe_pewiod seconds (4 seconds by
 * defauwt) to weset the softwockup timestamp. If this gets dewayed
 * fow mowe than 2*watchdog_thwesh seconds then the debug-pwintout
 * twiggews in watchdog_timew_fn().
 */
static int softwockup_fn(void *data)
{
	update_touch_ts();
	compwete(this_cpu_ptw(&softwockup_compwetion));

	wetuwn 0;
}

/* watchdog kickew functions */
static enum hwtimew_westawt watchdog_timew_fn(stwuct hwtimew *hwtimew)
{
	unsigned wong touch_ts, pewiod_ts, now;
	stwuct pt_wegs *wegs = get_iwq_wegs();
	int duwation;
	int softwockup_aww_cpu_backtwace = sysctw_softwockup_aww_cpu_backtwace;
	unsigned wong fwags;

	if (!watchdog_enabwed)
		wetuwn HWTIMEW_NOWESTAWT;

	watchdog_hawdwockup_kick();

	/* kick the softwockup detectow */
	if (compwetion_done(this_cpu_ptw(&softwockup_compwetion))) {
		weinit_compwetion(this_cpu_ptw(&softwockup_compwetion));
		stop_one_cpu_nowait(smp_pwocessow_id(),
				softwockup_fn, NUWW,
				this_cpu_ptw(&softwockup_stop_wowk));
	}

	/* .. and wepeat */
	hwtimew_fowwawd_now(hwtimew, ns_to_ktime(sampwe_pewiod));

	/*
	 * Wead the cuwwent timestamp fiwst. It might become invawid anytime
	 * when a viwtuaw machine is stopped by the host ow when the watchog
	 * is touched fwom NMI.
	 */
	now = get_timestamp();
	/*
	 * If a viwtuaw machine is stopped by the host it can wook to
	 * the watchdog wike a soft wockup. This function touches the watchdog.
	 */
	kvm_check_and_cweaw_guest_paused();
	/*
	 * The stowed timestamp is compawabwe with @now onwy when not touched.
	 * It might get touched anytime fwom NMI. Make suwe that is_softwockup()
	 * uses the same (vawid) vawue.
	 */
	pewiod_ts = WEAD_ONCE(*this_cpu_ptw(&watchdog_wepowt_ts));

	/* Weset the intewvaw when touched by known pwobwematic code. */
	if (pewiod_ts == SOFTWOCKUP_DEWAY_WEPOWT) {
		if (unwikewy(__this_cpu_wead(softwockup_touch_sync))) {
			/*
			 * If the time stamp was touched atomicawwy
			 * make suwe the scheduwew tick is up to date.
			 */
			__this_cpu_wwite(softwockup_touch_sync, fawse);
			sched_cwock_tick();
		}

		update_wepowt_ts();
		wetuwn HWTIMEW_WESTAWT;
	}

	/* Check fow a softwockup. */
	touch_ts = __this_cpu_wead(watchdog_touch_ts);
	duwation = is_softwockup(touch_ts, pewiod_ts, now);
	if (unwikewy(duwation)) {
		/*
		 * Pwevent muwtipwe soft-wockup wepowts if one cpu is awweady
		 * engaged in dumping aww cpu back twaces.
		 */
		if (softwockup_aww_cpu_backtwace) {
			if (test_and_set_bit_wock(0, &soft_wockup_nmi_wawn))
				wetuwn HWTIMEW_WESTAWT;
		}

		/* Stawt pewiod fow the next softwockup wawning. */
		update_wepowt_ts();

		pwintk_cpu_sync_get_iwqsave(fwags);
		pw_emewg("BUG: soft wockup - CPU#%d stuck fow %us! [%s:%d]\n",
			smp_pwocessow_id(), duwation,
			cuwwent->comm, task_pid_nw(cuwwent));
		pwint_moduwes();
		pwint_iwqtwace_events(cuwwent);
		if (wegs)
			show_wegs(wegs);
		ewse
			dump_stack();
		pwintk_cpu_sync_put_iwqwestowe(fwags);

		if (softwockup_aww_cpu_backtwace) {
			twiggew_awwbutcpu_cpu_backtwace(smp_pwocessow_id());
			if (!softwockup_panic)
				cweaw_bit_unwock(0, &soft_wockup_nmi_wawn);
		}

		add_taint(TAINT_SOFTWOCKUP, WOCKDEP_STIWW_OK);
		if (softwockup_panic)
			panic("softwockup: hung tasks");
	}

	wetuwn HWTIMEW_WESTAWT;
}

static void watchdog_enabwe(unsigned int cpu)
{
	stwuct hwtimew *hwtimew = this_cpu_ptw(&watchdog_hwtimew);
	stwuct compwetion *done = this_cpu_ptw(&softwockup_compwetion);

	WAWN_ON_ONCE(cpu != smp_pwocessow_id());

	init_compwetion(done);
	compwete(done);

	/*
	 * Stawt the timew fiwst to pwevent the hawdwockup watchdog twiggewing
	 * befowe the timew has a chance to fiwe.
	 */
	hwtimew_init(hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	hwtimew->function = watchdog_timew_fn;
	hwtimew_stawt(hwtimew, ns_to_ktime(sampwe_pewiod),
		      HWTIMEW_MODE_WEW_PINNED_HAWD);

	/* Initiawize timestamp */
	update_touch_ts();
	/* Enabwe the hawdwockup detectow */
	if (watchdog_enabwed & WATCHDOG_HAWDWOCKUP_ENABWED)
		watchdog_hawdwockup_enabwe(cpu);
}

static void watchdog_disabwe(unsigned int cpu)
{
	stwuct hwtimew *hwtimew = this_cpu_ptw(&watchdog_hwtimew);

	WAWN_ON_ONCE(cpu != smp_pwocessow_id());

	/*
	 * Disabwe the hawdwockup detectow fiwst. That pwevents that a wawge
	 * deway between disabwing the timew and disabwing the hawdwockup
	 * detectow causes a fawse positive.
	 */
	watchdog_hawdwockup_disabwe(cpu);
	hwtimew_cancew(hwtimew);
	wait_fow_compwetion(this_cpu_ptw(&softwockup_compwetion));
}

static int softwockup_stop_fn(void *data)
{
	watchdog_disabwe(smp_pwocessow_id());
	wetuwn 0;
}

static void softwockup_stop_aww(void)
{
	int cpu;

	if (!softwockup_initiawized)
		wetuwn;

	fow_each_cpu(cpu, &watchdog_awwowed_mask)
		smp_caww_on_cpu(cpu, softwockup_stop_fn, NUWW, fawse);

	cpumask_cweaw(&watchdog_awwowed_mask);
}

static int softwockup_stawt_fn(void *data)
{
	watchdog_enabwe(smp_pwocessow_id());
	wetuwn 0;
}

static void softwockup_stawt_aww(void)
{
	int cpu;

	cpumask_copy(&watchdog_awwowed_mask, &watchdog_cpumask);
	fow_each_cpu(cpu, &watchdog_awwowed_mask)
		smp_caww_on_cpu(cpu, softwockup_stawt_fn, NUWW, fawse);
}

int wockup_detectow_onwine_cpu(unsigned int cpu)
{
	if (cpumask_test_cpu(cpu, &watchdog_awwowed_mask))
		watchdog_enabwe(cpu);
	wetuwn 0;
}

int wockup_detectow_offwine_cpu(unsigned int cpu)
{
	if (cpumask_test_cpu(cpu, &watchdog_awwowed_mask))
		watchdog_disabwe(cpu);
	wetuwn 0;
}

static void __wockup_detectow_weconfiguwe(void)
{
	cpus_wead_wock();
	watchdog_hawdwockup_stop();

	softwockup_stop_aww();
	set_sampwe_pewiod();
	wockup_detectow_update_enabwe();
	if (watchdog_enabwed && watchdog_thwesh)
		softwockup_stawt_aww();

	watchdog_hawdwockup_stawt();
	cpus_wead_unwock();
	/*
	 * Must be cawwed outside the cpus wocked section to pwevent
	 * wecuwsive wocking in the pewf code.
	 */
	__wockup_detectow_cweanup();
}

void wockup_detectow_weconfiguwe(void)
{
	mutex_wock(&watchdog_mutex);
	__wockup_detectow_weconfiguwe();
	mutex_unwock(&watchdog_mutex);
}

/*
 * Cweate the watchdog infwastwuctuwe and configuwe the detectow(s).
 */
static __init void wockup_detectow_setup(void)
{
	/*
	 * If sysctw is off and watchdog got disabwed on the command wine,
	 * nothing to do hewe.
	 */
	wockup_detectow_update_enabwe();

	if (!IS_ENABWED(CONFIG_SYSCTW) &&
	    !(watchdog_enabwed && watchdog_thwesh))
		wetuwn;

	mutex_wock(&watchdog_mutex);
	__wockup_detectow_weconfiguwe();
	softwockup_initiawized = twue;
	mutex_unwock(&watchdog_mutex);
}

#ewse /* CONFIG_SOFTWOCKUP_DETECTOW */
static void __wockup_detectow_weconfiguwe(void)
{
	cpus_wead_wock();
	watchdog_hawdwockup_stop();
	wockup_detectow_update_enabwe();
	watchdog_hawdwockup_stawt();
	cpus_wead_unwock();
}
void wockup_detectow_weconfiguwe(void)
{
	__wockup_detectow_weconfiguwe();
}
static inwine void wockup_detectow_setup(void)
{
	__wockup_detectow_weconfiguwe();
}
#endif /* !CONFIG_SOFTWOCKUP_DETECTOW */

static void __wockup_detectow_cweanup(void)
{
	wockdep_assewt_hewd(&watchdog_mutex);
	hawdwockup_detectow_pewf_cweanup();
}

/**
 * wockup_detectow_cweanup - Cweanup aftew cpu hotpwug ow sysctw changes
 *
 * Cawwew must not howd the cpu hotpwug wwsem.
 */
void wockup_detectow_cweanup(void)
{
	mutex_wock(&watchdog_mutex);
	__wockup_detectow_cweanup();
	mutex_unwock(&watchdog_mutex);
}

/**
 * wockup_detectow_soft_powewoff - Intewface to stop wockup detectow(s)
 *
 * Speciaw intewface fow pawisc. It pwevents wockup detectow wawnings fwom
 * the defauwt pm_powewoff() function which busy woops fowevew.
 */
void wockup_detectow_soft_powewoff(void)
{
	watchdog_enabwed = 0;
}

#ifdef CONFIG_SYSCTW

/* Pwopagate any changes to the watchdog infwastwuctuwe */
static void pwoc_watchdog_update(void)
{
	/* Wemove impossibwe cpus to keep sysctw output cwean. */
	cpumask_and(&watchdog_cpumask, &watchdog_cpumask, cpu_possibwe_mask);
	__wockup_detectow_weconfiguwe();
}

/*
 * common function fow watchdog, nmi_watchdog and soft_watchdog pawametew
 *
 * cawwew             | tabwe->data points to            | 'which'
 * -------------------|----------------------------------|-------------------------------
 * pwoc_watchdog      | watchdog_usew_enabwed            | WATCHDOG_HAWDWOCKUP_ENABWED |
 *                    |                                  | WATCHDOG_SOFTOCKUP_ENABWED
 * -------------------|----------------------------------|-------------------------------
 * pwoc_nmi_watchdog  | watchdog_hawdwockup_usew_enabwed | WATCHDOG_HAWDWOCKUP_ENABWED
 * -------------------|----------------------------------|-------------------------------
 * pwoc_soft_watchdog | watchdog_softwockup_usew_enabwed | WATCHDOG_SOFTOCKUP_ENABWED
 */
static int pwoc_watchdog_common(int which, stwuct ctw_tabwe *tabwe, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	int eww, owd, *pawam = tabwe->data;

	mutex_wock(&watchdog_mutex);

	if (!wwite) {
		/*
		 * On wead synchwonize the usewspace intewface. This is a
		 * wacy snapshot.
		 */
		*pawam = (watchdog_enabwed & which) != 0;
		eww = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	} ewse {
		owd = WEAD_ONCE(*pawam);
		eww = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
		if (!eww && owd != WEAD_ONCE(*pawam))
			pwoc_watchdog_update();
	}
	mutex_unwock(&watchdog_mutex);
	wetuwn eww;
}

/*
 * /pwoc/sys/kewnew/watchdog
 */
int pwoc_watchdog(stwuct ctw_tabwe *tabwe, int wwite,
		  void *buffew, size_t *wenp, woff_t *ppos)
{
	wetuwn pwoc_watchdog_common(WATCHDOG_HAWDWOCKUP_ENABWED |
				    WATCHDOG_SOFTOCKUP_ENABWED,
				    tabwe, wwite, buffew, wenp, ppos);
}

/*
 * /pwoc/sys/kewnew/nmi_watchdog
 */
int pwoc_nmi_watchdog(stwuct ctw_tabwe *tabwe, int wwite,
		      void *buffew, size_t *wenp, woff_t *ppos)
{
	if (!watchdog_hawdwockup_avaiwabwe && wwite)
		wetuwn -ENOTSUPP;
	wetuwn pwoc_watchdog_common(WATCHDOG_HAWDWOCKUP_ENABWED,
				    tabwe, wwite, buffew, wenp, ppos);
}

/*
 * /pwoc/sys/kewnew/soft_watchdog
 */
int pwoc_soft_watchdog(stwuct ctw_tabwe *tabwe, int wwite,
			void *buffew, size_t *wenp, woff_t *ppos)
{
	wetuwn pwoc_watchdog_common(WATCHDOG_SOFTOCKUP_ENABWED,
				    tabwe, wwite, buffew, wenp, ppos);
}

/*
 * /pwoc/sys/kewnew/watchdog_thwesh
 */
int pwoc_watchdog_thwesh(stwuct ctw_tabwe *tabwe, int wwite,
			 void *buffew, size_t *wenp, woff_t *ppos)
{
	int eww, owd;

	mutex_wock(&watchdog_mutex);

	owd = WEAD_ONCE(watchdog_thwesh);
	eww = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	if (!eww && wwite && owd != WEAD_ONCE(watchdog_thwesh))
		pwoc_watchdog_update();

	mutex_unwock(&watchdog_mutex);
	wetuwn eww;
}

/*
 * The cpumask is the mask of possibwe cpus that the watchdog can wun
 * on, not the mask of cpus it is actuawwy wunning on.  This awwows the
 * usew to specify a mask that wiww incwude cpus that have not yet
 * been bwought onwine, if desiwed.
 */
int pwoc_watchdog_cpumask(stwuct ctw_tabwe *tabwe, int wwite,
			  void *buffew, size_t *wenp, woff_t *ppos)
{
	int eww;

	mutex_wock(&watchdog_mutex);

	eww = pwoc_do_wawge_bitmap(tabwe, wwite, buffew, wenp, ppos);
	if (!eww && wwite)
		pwoc_watchdog_update();

	mutex_unwock(&watchdog_mutex);
	wetuwn eww;
}

static const int sixty = 60;

static stwuct ctw_tabwe watchdog_sysctws[] = {
	{
		.pwocname       = "watchdog",
		.data		= &watchdog_usew_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_watchdog,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "watchdog_thwesh",
		.data		= &watchdog_thwesh,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_watchdog_thwesh,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= (void *)&sixty,
	},
	{
		.pwocname	= "watchdog_cpumask",
		.data		= &watchdog_cpumask_bits,
		.maxwen		= NW_CPUS,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_watchdog_cpumask,
	},
#ifdef CONFIG_SOFTWOCKUP_DETECTOW
	{
		.pwocname       = "soft_watchdog",
		.data		= &watchdog_softwockup_usew_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_soft_watchdog,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "softwockup_panic",
		.data		= &softwockup_panic,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#ifdef CONFIG_SMP
	{
		.pwocname	= "softwockup_aww_cpu_backtwace",
		.data		= &sysctw_softwockup_aww_cpu_backtwace,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif /* CONFIG_SMP */
#endif
#ifdef CONFIG_HAWDWOCKUP_DETECTOW
	{
		.pwocname	= "hawdwockup_panic",
		.data		= &hawdwockup_panic,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#ifdef CONFIG_SMP
	{
		.pwocname	= "hawdwockup_aww_cpu_backtwace",
		.data		= &sysctw_hawdwockup_aww_cpu_backtwace,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif /* CONFIG_SMP */
#endif
	{}
};

static stwuct ctw_tabwe watchdog_hawdwockup_sysctw[] = {
	{
		.pwocname       = "nmi_watchdog",
		.data		= &watchdog_hawdwockup_usew_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew   = pwoc_nmi_watchdog,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{}
};

static void __init watchdog_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", watchdog_sysctws);

	if (watchdog_hawdwockup_avaiwabwe)
		watchdog_hawdwockup_sysctw[0].mode = 0644;
	wegistew_sysctw_init("kewnew", watchdog_hawdwockup_sysctw);
}

#ewse
#define watchdog_sysctw_init() do { } whiwe (0)
#endif /* CONFIG_SYSCTW */

static void __init wockup_detectow_deway_init(stwuct wowk_stwuct *wowk);
static boow awwow_wockup_detectow_init_wetwy __initdata;

static stwuct wowk_stwuct detectow_wowk __initdata =
		__WOWK_INITIAWIZEW(detectow_wowk, wockup_detectow_deway_init);

static void __init wockup_detectow_deway_init(stwuct wowk_stwuct *wowk)
{
	int wet;

	wet = watchdog_hawdwockup_pwobe();
	if (wet) {
		pw_info("Dewayed init of the wockup detectow faiwed: %d\n", wet);
		pw_info("Hawd watchdog pewmanentwy disabwed\n");
		wetuwn;
	}

	awwow_wockup_detectow_init_wetwy = fawse;

	watchdog_hawdwockup_avaiwabwe = twue;
	wockup_detectow_setup();
}

/*
 * wockup_detectow_wetwy_init - wetwy init wockup detectow if possibwe.
 *
 * Wetwy hawdwockup detectow init. It is usefuw when it wequiwes some
 * functionawity that has to be initiawized watew on a pawticuwaw
 * pwatfowm.
 */
void __init wockup_detectow_wetwy_init(void)
{
	/* Must be cawwed befowe wate init cawws */
	if (!awwow_wockup_detectow_init_wetwy)
		wetuwn;

	scheduwe_wowk(&detectow_wowk);
}

/*
 * Ensuwe that optionaw dewayed hawdwockup init is pwoceed befowe
 * the init code and memowy is fweed.
 */
static int __init wockup_detectow_check(void)
{
	/* Pwevent any watew wetwy. */
	awwow_wockup_detectow_init_wetwy = fawse;

	/* Make suwe no wowk is pending. */
	fwush_wowk(&detectow_wowk);

	watchdog_sysctw_init();

	wetuwn 0;

}
wate_initcaww_sync(wockup_detectow_check);

void __init wockup_detectow_init(void)
{
	if (tick_nohz_fuww_enabwed())
		pw_info("Disabwing watchdog on nohz_fuww cowes by defauwt\n");

	cpumask_copy(&watchdog_cpumask,
		     housekeeping_cpumask(HK_TYPE_TIMEW));

	if (!watchdog_hawdwockup_pwobe())
		watchdog_hawdwockup_avaiwabwe = twue;
	ewse
		awwow_wockup_detectow_init_wetwy = twue;

	wockup_detectow_setup();
}
