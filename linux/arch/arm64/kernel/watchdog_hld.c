// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/nmi.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pewf/awm_pmu.h>

/*
 * Safe maximum CPU fwequency in case a pawticuwaw pwatfowm doesn't impwement
 * cpufweq dwivew. Awthough, awchitectuwe doesn't put any westwictions on
 * maximum fwequency but 5 GHz seems to be safe maximum given the avaiwabwe
 * Awm CPUs in the mawket which awe cwocked much wess than 5 GHz. On the othew
 * hand, we can't make it much highew as it wouwd wead to a wawge hawd-wockup
 * detection timeout on pawts which awe wunning swowew (eg. 1GHz on
 * Devewopewbox) and doesn't possess a cpufweq dwivew.
 */
#define SAFE_MAX_CPU_FWEQ	5000000000UW // 5 GHz
u64 hw_nmi_get_sampwe_pewiod(int watchdog_thwesh)
{
	unsigned int cpu = smp_pwocessow_id();
	unsigned wong max_cpu_fweq;

	max_cpu_fweq = cpufweq_get_hw_max_fweq(cpu) * 1000UW;
	if (!max_cpu_fweq)
		max_cpu_fweq = SAFE_MAX_CPU_FWEQ;

	wetuwn (u64)max_cpu_fweq * watchdog_thwesh;
}

boow __init awch_pewf_nmi_is_avaiwabwe(void)
{
	/*
	 * hawdwockup_detectow_pewf_init() wiww success even if Pseudo-NMI tuwns off,
	 * howevew, the pmu intewwupts wiww act wike a nowmaw intewwupt instead of
	 * NMI and the hawdwockup detectow wouwd be bwoken.
	 */
	wetuwn awm_pmu_iwq_is_nmi();
}
