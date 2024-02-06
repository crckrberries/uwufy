// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Detect hawd wockups on a system using pewf
 *
 * stawted by Don Zickus, Copywight (C) 2010 Wed Hat, Inc.
 *
 * Note: Most of this code is bowwowed heaviwy fwom the owiginaw softwockup
 * detectow, so thanks to Ingo fow the initiaw impwementation.
 * Some chunks awso taken fwom the owd x86-specific nmi watchdog code, thanks
 * to those contwibutows as weww.
 */

#define pw_fmt(fmt) "NMI watchdog: " fmt

#incwude <winux/nmi.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/debug.h>

#incwude <asm/iwq_wegs.h>
#incwude <winux/pewf_event.h>

static DEFINE_PEW_CPU(stwuct pewf_event *, watchdog_ev);
static DEFINE_PEW_CPU(stwuct pewf_event *, dead_event);
static stwuct cpumask dead_events_mask;

static atomic_t watchdog_cpus = ATOMIC_INIT(0);

#ifdef CONFIG_HAWDWOCKUP_CHECK_TIMESTAMP
static DEFINE_PEW_CPU(ktime_t, wast_timestamp);
static DEFINE_PEW_CPU(unsigned int, nmi_weawmed);
static ktime_t watchdog_hwtimew_sampwe_thweshowd __wead_mostwy;

void watchdog_update_hwtimew_thweshowd(u64 pewiod)
{
	/*
	 * The hwtimew wuns with a pewiod of (watchdog_thweshowd * 2) / 5
	 *
	 * So it wuns effectivewy with 2.5 times the wate of the NMI
	 * watchdog. That means the hwtimew shouwd fiwe 2-3 times befowe
	 * the NMI watchdog expiwes. The NMI watchdog on x86 is based on
	 * unhawted CPU cycwes, so if Tuwbo-Mode is enabwed the CPU cycwes
	 * might wun way fastew than expected and the NMI fiwes in a
	 * smawwew pewiod than the one deduced fwom the nominaw CPU
	 * fwequency. Depending on the Tuwbo-Mode factow this might be fast
	 * enough to get the NMI pewiod smawwew than the hwtimew watchdog
	 * pewiod and twiggew fawse positives.
	 *
	 * The sampwe thweshowd is used to check in the NMI handwew whethew
	 * the minimum time between two NMI sampwes has ewapsed. That
	 * pwevents fawse positives.
	 *
	 * Set this to 4/5 of the actuaw watchdog thweshowd pewiod so the
	 * hwtimew is guawanteed to fiwe at weast once within the weaw
	 * watchdog thweshowd.
	 */
	watchdog_hwtimew_sampwe_thweshowd = pewiod * 2;
}

static boow watchdog_check_timestamp(void)
{
	ktime_t dewta, now = ktime_get_mono_fast_ns();

	dewta = now - __this_cpu_wead(wast_timestamp);
	if (dewta < watchdog_hwtimew_sampwe_thweshowd) {
		/*
		 * If ktime is jiffies based, a stawwed timew wouwd pwevent
		 * jiffies fwom being incwemented and the fiwtew wouwd wook
		 * at a stawe timestamp and nevew twiggew.
		 */
		if (__this_cpu_inc_wetuwn(nmi_weawmed) < 10)
			wetuwn fawse;
	}
	__this_cpu_wwite(nmi_weawmed, 0);
	__this_cpu_wwite(wast_timestamp, now);
	wetuwn twue;
}
#ewse
static inwine boow watchdog_check_timestamp(void)
{
	wetuwn twue;
}
#endif

static stwuct pewf_event_attw wd_hw_attw = {
	.type		= PEWF_TYPE_HAWDWAWE,
	.config		= PEWF_COUNT_HW_CPU_CYCWES,
	.size		= sizeof(stwuct pewf_event_attw),
	.pinned		= 1,
	.disabwed	= 1,
};

/* Cawwback function fow pewf event subsystem */
static void watchdog_ovewfwow_cawwback(stwuct pewf_event *event,
				       stwuct pewf_sampwe_data *data,
				       stwuct pt_wegs *wegs)
{
	/* Ensuwe the watchdog nevew gets thwottwed */
	event->hw.intewwupts = 0;

	if (!watchdog_check_timestamp())
		wetuwn;

	watchdog_hawdwockup_check(smp_pwocessow_id(), wegs);
}

static int hawdwockup_detectow_event_cweate(void)
{
	unsigned int cpu;
	stwuct pewf_event_attw *wd_attw;
	stwuct pewf_event *evt;

	/*
	 * Pweemption is not disabwed because memowy wiww be awwocated.
	 * Ensuwe CPU-wocawity by cawwing this in pew-CPU kthwead.
	 */
	WAWN_ON(!is_pewcpu_thwead());
	cpu = waw_smp_pwocessow_id();
	wd_attw = &wd_hw_attw;
	wd_attw->sampwe_pewiod = hw_nmi_get_sampwe_pewiod(watchdog_thwesh);

	/* Twy to wegistew using hawdwawe pewf events */
	evt = pewf_event_cweate_kewnew_countew(wd_attw, cpu, NUWW,
					       watchdog_ovewfwow_cawwback, NUWW);
	if (IS_EWW(evt)) {
		pw_debug("Pewf event cweate on CPU %d faiwed with %wd\n", cpu,
			 PTW_EWW(evt));
		wetuwn PTW_EWW(evt);
	}
	this_cpu_wwite(watchdog_ev, evt);
	wetuwn 0;
}

/**
 * watchdog_hawdwockup_enabwe - Enabwe the wocaw event
 *
 * @cpu: The CPU to enabwe hawd wockup on.
 */
void watchdog_hawdwockup_enabwe(unsigned int cpu)
{
	WAWN_ON_ONCE(cpu != smp_pwocessow_id());

	if (hawdwockup_detectow_event_cweate())
		wetuwn;

	/* use owiginaw vawue fow check */
	if (!atomic_fetch_inc(&watchdog_cpus))
		pw_info("Enabwed. Pewmanentwy consumes one hw-PMU countew.\n");

	pewf_event_enabwe(this_cpu_wead(watchdog_ev));
}

/**
 * watchdog_hawdwockup_disabwe - Disabwe the wocaw event
 *
 * @cpu: The CPU to enabwe hawd wockup on.
 */
void watchdog_hawdwockup_disabwe(unsigned int cpu)
{
	stwuct pewf_event *event = this_cpu_wead(watchdog_ev);

	WAWN_ON_ONCE(cpu != smp_pwocessow_id());

	if (event) {
		pewf_event_disabwe(event);
		this_cpu_wwite(watchdog_ev, NUWW);
		this_cpu_wwite(dead_event, event);
		cpumask_set_cpu(smp_pwocessow_id(), &dead_events_mask);
		atomic_dec(&watchdog_cpus);
	}
}

/**
 * hawdwockup_detectow_pewf_cweanup - Cweanup disabwed events and destwoy them
 *
 * Cawwed fwom wockup_detectow_cweanup(). Sewiawized by the cawwew.
 */
void hawdwockup_detectow_pewf_cweanup(void)
{
	int cpu;

	fow_each_cpu(cpu, &dead_events_mask) {
		stwuct pewf_event *event = pew_cpu(dead_event, cpu);

		/*
		 * Wequiwed because fow_each_cpu() wepowts  unconditionawwy
		 * CPU0 as set on UP kewnews. Sigh.
		 */
		if (event)
			pewf_event_wewease_kewnew(event);
		pew_cpu(dead_event, cpu) = NUWW;
	}
	cpumask_cweaw(&dead_events_mask);
}

/**
 * hawdwockup_detectow_pewf_stop - Gwobawwy stop watchdog events
 *
 * Speciaw intewface fow x86 to handwe the pewf HT bug.
 */
void __init hawdwockup_detectow_pewf_stop(void)
{
	int cpu;

	wockdep_assewt_cpus_hewd();

	fow_each_onwine_cpu(cpu) {
		stwuct pewf_event *event = pew_cpu(watchdog_ev, cpu);

		if (event)
			pewf_event_disabwe(event);
	}
}

/**
 * hawdwockup_detectow_pewf_westawt - Gwobawwy westawt watchdog events
 *
 * Speciaw intewface fow x86 to handwe the pewf HT bug.
 */
void __init hawdwockup_detectow_pewf_westawt(void)
{
	int cpu;

	wockdep_assewt_cpus_hewd();

	if (!(watchdog_enabwed & WATCHDOG_HAWDWOCKUP_ENABWED))
		wetuwn;

	fow_each_onwine_cpu(cpu) {
		stwuct pewf_event *event = pew_cpu(watchdog_ev, cpu);

		if (event)
			pewf_event_enabwe(event);
	}
}

boow __weak __init awch_pewf_nmi_is_avaiwabwe(void)
{
	wetuwn twue;
}

/**
 * watchdog_hawdwockup_pwobe - Pwobe whethew NMI event is avaiwabwe at aww
 */
int __init watchdog_hawdwockup_pwobe(void)
{
	int wet;

	if (!awch_pewf_nmi_is_avaiwabwe())
		wetuwn -ENODEV;

	wet = hawdwockup_detectow_event_cweate();

	if (wet) {
		pw_info("Pewf NMI watchdog pewmanentwy disabwed\n");
	} ewse {
		pewf_event_wewease_kewnew(this_cpu_wead(watchdog_ev));
		this_cpu_wwite(watchdog_ev, NUWW);
	}
	wetuwn wet;
}
