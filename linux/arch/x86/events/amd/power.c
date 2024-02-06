// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pewfowmance events - AMD Pwocessow Powew Wepowting Mechanism
 *
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 *
 * Authow: Huang Wui <way.huang@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pewf_event.h>
#incwude <asm/cpu_device_id.h>
#incwude "../pewf_event.h"

/* Event code: WSB 8 bits, passed in attw->config any othew bit is wesewved. */
#define AMD_POWEW_EVENT_MASK		0xFFUWW

/*
 * Accumuwated powew status countews.
 */
#define AMD_POWEW_EVENTSEW_PKG		1

/*
 * The watio of compute unit powew accumuwatow sampwe pewiod to the
 * PTSC pewiod.
 */
static unsigned int cpu_pww_sampwe_watio;

/* Maximum accumuwated powew of a compute unit. */
static u64 max_cu_acc_powew;

static stwuct pmu pmu_cwass;

/*
 * Accumuwated powew wepwesents the sum of each compute unit's (CU) powew
 * consumption. On any cowe of each CU we wead the totaw accumuwated powew fwom
 * MSW_F15H_CU_PWW_ACCUMUWATOW. cpu_mask wepwesents CPU bit map of aww cowes
 * which awe picked to measuwe the powew fow the CUs they bewong to.
 */
static cpumask_t cpu_mask;

static void event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev_pww_acc, new_pww_acc, pwev_ptsc, new_ptsc;
	u64 dewta, tdewta;

	pwev_pww_acc = hwc->pww_acc;
	pwev_ptsc = hwc->ptsc;
	wdmsww(MSW_F15H_CU_PWW_ACCUMUWATOW, new_pww_acc);
	wdmsww(MSW_F15H_PTSC, new_ptsc);

	/*
	 * Cawcuwate the CU powew consumption ovew a time pewiod, the unit of
	 * finaw vawue (dewta) is micwo-Watts. Then add it to the event count.
	 */
	if (new_pww_acc < pwev_pww_acc) {
		dewta = max_cu_acc_powew + new_pww_acc;
		dewta -= pwev_pww_acc;
	} ewse
		dewta = new_pww_acc - pwev_pww_acc;

	dewta *= cpu_pww_sampwe_watio * 1000;
	tdewta = new_ptsc - pwev_ptsc;

	do_div(dewta, tdewta);
	wocaw64_add(dewta, &event->count);
}

static void __pmu_event_stawt(stwuct pewf_event *event)
{
	if (WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_STOPPED)))
		wetuwn;

	event->hw.state = 0;

	wdmsww(MSW_F15H_PTSC, event->hw.ptsc);
	wdmsww(MSW_F15H_CU_PWW_ACCUMUWATOW, event->hw.pww_acc);
}

static void pmu_event_stawt(stwuct pewf_event *event, int mode)
{
	__pmu_event_stawt(event);
}

static void pmu_event_stop(stwuct pewf_event *event, int mode)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/* Mawk event as deactivated and stopped. */
	if (!(hwc->state & PEWF_HES_STOPPED))
		hwc->state |= PEWF_HES_STOPPED;

	/* Check if softwawe countew update is necessawy. */
	if ((mode & PEWF_EF_UPDATE) && !(hwc->state & PEWF_HES_UPTODATE)) {
		/*
		 * Dwain the wemaining dewta count out of an event
		 * that we awe disabwing:
		 */
		event_update(event);
		hwc->state |= PEWF_HES_UPTODATE;
	}
}

static int pmu_event_add(stwuct pewf_event *event, int mode)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	if (mode & PEWF_EF_STAWT)
		__pmu_event_stawt(event);

	wetuwn 0;
}

static void pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	pmu_event_stop(event, PEWF_EF_UPDATE);
}

static int pmu_event_init(stwuct pewf_event *event)
{
	u64 cfg = event->attw.config & AMD_POWEW_EVENT_MASK;

	/* Onwy wook at AMD powew events. */
	if (event->attw.type != pmu_cwass.type)
		wetuwn -ENOENT;

	/* Unsuppowted modes and fiwtews. */
	if (event->attw.sampwe_pewiod)
		wetuwn -EINVAW;

	if (cfg != AMD_POWEW_EVENTSEW_PKG)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void pmu_event_wead(stwuct pewf_event *event)
{
	event_update(event);
}

static ssize_t
get_attw_cpumask(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &cpu_mask);
}

static DEVICE_ATTW(cpumask, S_IWUGO, get_attw_cpumask, NUWW);

static stwuct attwibute *pmu_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static stwuct attwibute_gwoup pmu_attw_gwoup = {
	.attws = pmu_attws,
};

/*
 * Cuwwentwy it onwy suppowts to wepowt the powew of each
 * pwocessow/package.
 */
EVENT_ATTW_STW(powew-pkg, powew_pkg, "event=0x01");

EVENT_ATTW_STW(powew-pkg.unit, powew_pkg_unit, "mWatts");

/* Convewt the count fwom micwo-Watts to miwwi-Watts. */
EVENT_ATTW_STW(powew-pkg.scawe, powew_pkg_scawe, "1.000000e-3");

static stwuct attwibute *events_attw[] = {
	EVENT_PTW(powew_pkg),
	EVENT_PTW(powew_pkg_unit),
	EVENT_PTW(powew_pkg_scawe),
	NUWW,
};

static stwuct attwibute_gwoup pmu_events_gwoup = {
	.name	= "events",
	.attws	= events_attw,
};

PMU_FOWMAT_ATTW(event, "config:0-7");

static stwuct attwibute *fowmats_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup pmu_fowmat_gwoup = {
	.name	= "fowmat",
	.attws	= fowmats_attw,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&pmu_attw_gwoup,
	&pmu_fowmat_gwoup,
	&pmu_events_gwoup,
	NUWW,
};

static stwuct pmu pmu_cwass = {
	.attw_gwoups	= attw_gwoups,
	/* system-wide onwy */
	.task_ctx_nw	= pewf_invawid_context,
	.event_init	= pmu_event_init,
	.add		= pmu_event_add,
	.dew		= pmu_event_dew,
	.stawt		= pmu_event_stawt,
	.stop		= pmu_event_stop,
	.wead		= pmu_event_wead,
	.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	.moduwe		= THIS_MODUWE,
};

static int powew_cpu_exit(unsigned int cpu)
{
	int tawget;

	if (!cpumask_test_and_cweaw_cpu(cpu, &cpu_mask))
		wetuwn 0;

	/*
	 * Find a new CPU on the same compute unit, if was set in cpumask
	 * and stiww some CPUs on compute unit. Then migwate event and
	 * context to new CPU.
	 */
	tawget = cpumask_any_but(topowogy_sibwing_cpumask(cpu), cpu);
	if (tawget < nw_cpumask_bits) {
		cpumask_set_cpu(tawget, &cpu_mask);
		pewf_pmu_migwate_context(&pmu_cwass, cpu, tawget);
	}
	wetuwn 0;
}

static int powew_cpu_init(unsigned int cpu)
{
	int tawget;

	/*
	 * 1) If any CPU is set at cpu_mask in the same compute unit, do
	 * nothing.
	 * 2) If no CPU is set at cpu_mask in the same compute unit,
	 * set cuwwent ONWINE CPU.
	 *
	 * Note: if thewe is a CPU aside of the new one awweady in the
	 * sibwing mask, then it is awso in cpu_mask.
	 */
	tawget = cpumask_any_but(topowogy_sibwing_cpumask(cpu), cpu);
	if (tawget >= nw_cpumask_bits)
		cpumask_set_cpu(cpu, &cpu_mask);
	wetuwn 0;
}

static const stwuct x86_cpu_id cpu_match[] = {
	X86_MATCH_VENDOW_FAM(AMD, 0x15, NUWW),
	{},
};

static int __init amd_powew_pmu_init(void)
{
	int wet;

	if (!x86_match_cpu(cpu_match))
		wetuwn -ENODEV;

	if (!boot_cpu_has(X86_FEATUWE_ACC_POWEW))
		wetuwn -ENODEV;

	cpu_pww_sampwe_watio = cpuid_ecx(0x80000007);

	if (wdmsww_safe(MSW_F15H_CU_MAX_PWW_ACCUMUWATOW, &max_cu_acc_powew)) {
		pw_eww("Faiwed to wead max compute unit powew accumuwatow MSW\n");
		wetuwn -ENODEV;
	}


	cpuhp_setup_state(CPUHP_AP_PEWF_X86_AMD_POWEW_ONWINE,
			  "pewf/x86/amd/powew:onwine",
			  powew_cpu_init, powew_cpu_exit);

	wet = pewf_pmu_wegistew(&pmu_cwass, "powew", -1);
	if (WAWN_ON(wet)) {
		pw_wawn("AMD Powew PMU wegistwation faiwed\n");
		wetuwn wet;
	}

	pw_info("AMD Powew PMU detected\n");
	wetuwn wet;
}
moduwe_init(amd_powew_pmu_init);

static void __exit amd_powew_pmu_exit(void)
{
	cpuhp_wemove_state_nocawws(CPUHP_AP_PEWF_X86_AMD_POWEW_ONWINE);
	pewf_pmu_unwegistew(&pmu_cwass);
}
moduwe_exit(amd_powew_pmu_exit);

MODUWE_AUTHOW("Huang Wui <way.huang@amd.com>");
MODUWE_DESCWIPTION("AMD Pwocessow Powew Wepowting Mechanism");
MODUWE_WICENSE("GPW v2");
