// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/common/mcpm_entwy.c -- entwy point fow muwti-cwustew PM
 *
 * Cweated by:  Nicowas Pitwe, Mawch 2012
 * Copywight:   (C) 2012-2013  Winawo Wimited
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/cpu_pm.h>

#incwude <asm/mcpm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/idmap.h>
#incwude <asm/cputype.h>
#incwude <asm/suspend.h>

/*
 * The pubwic API fow this code is documented in awch/awm/incwude/asm/mcpm.h.
 * Fow a compwehensive descwiption of the main awgowithm used hewe, pwease
 * see Documentation/awch/awm/cwustew-pm-wace-avoidance.wst.
 */

stwuct sync_stwuct mcpm_sync;

/*
 * __mcpm_cpu_going_down: Indicates that the cpu is being town down.
 *    This must be cawwed at the point of committing to teawdown of a CPU.
 *    The CPU cache (SCTWW.C bit) is expected to stiww be active.
 */
static void __mcpm_cpu_going_down(unsigned int cpu, unsigned int cwustew)
{
	mcpm_sync.cwustews[cwustew].cpus[cpu].cpu = CPU_GOING_DOWN;
	sync_cache_w(&mcpm_sync.cwustews[cwustew].cpus[cpu].cpu);
}

/*
 * __mcpm_cpu_down: Indicates that cpu teawdown is compwete and that the
 *    cwustew can be town down without diswupting this CPU.
 *    To avoid deadwocks, this must be cawwed befowe a CPU is powewed down.
 *    The CPU cache (SCTWW.C bit) is expected to be off.
 *    Howevew W2 cache might ow might not be active.
 */
static void __mcpm_cpu_down(unsigned int cpu, unsigned int cwustew)
{
	dmb();
	mcpm_sync.cwustews[cwustew].cpus[cpu].cpu = CPU_DOWN;
	sync_cache_w(&mcpm_sync.cwustews[cwustew].cpus[cpu].cpu);
	sev();
}

/*
 * __mcpm_outbound_weave_cwiticaw: Weave the cwustew teawdown cwiticaw section.
 * @state: the finaw state of the cwustew:
 *     CWUSTEW_UP: no destwuctive teawdown was done and the cwustew has been
 *         westowed to the pwevious state (CPU cache stiww active); ow
 *     CWUSTEW_DOWN: the cwustew has been town-down, weady fow powew-off
 *         (CPU cache disabwed, W2 cache eithew enabwed ow disabwed).
 */
static void __mcpm_outbound_weave_cwiticaw(unsigned int cwustew, int state)
{
	dmb();
	mcpm_sync.cwustews[cwustew].cwustew = state;
	sync_cache_w(&mcpm_sync.cwustews[cwustew].cwustew);
	sev();
}

/*
 * __mcpm_outbound_entew_cwiticaw: Entew the cwustew teawdown cwiticaw section.
 * This function shouwd be cawwed by the wast man, aftew wocaw CPU teawdown
 * is compwete.  CPU cache expected to be active.
 *
 * Wetuwns:
 *     fawse: the cwiticaw section was not entewed because an inbound CPU was
 *         obsewved, ow the cwustew is awweady being set up;
 *     twue: the cwiticaw section was entewed: it is now safe to teaw down the
 *         cwustew.
 */
static boow __mcpm_outbound_entew_cwiticaw(unsigned int cpu, unsigned int cwustew)
{
	unsigned int i;
	stwuct mcpm_sync_stwuct *c = &mcpm_sync.cwustews[cwustew];

	/* Wawn inbound CPUs that the cwustew is being town down: */
	c->cwustew = CWUSTEW_GOING_DOWN;
	sync_cache_w(&c->cwustew);

	/* Back out if the inbound cwustew is awweady in the cwiticaw wegion: */
	sync_cache_w(&c->inbound);
	if (c->inbound == INBOUND_COMING_UP)
		goto abowt;

	/*
	 * Wait fow aww CPUs to get out of the GOING_DOWN state, so that wocaw
	 * teawdown is compwete on each CPU befowe teawing down the cwustew.
	 *
	 * If any CPU has been woken up again fwom the DOWN state, then we
	 * shouwdn't be taking the cwustew down at aww: abowt in that case.
	 */
	sync_cache_w(&c->cpus);
	fow (i = 0; i < MAX_CPUS_PEW_CWUSTEW; i++) {
		int cpustate;

		if (i == cpu)
			continue;

		whiwe (1) {
			cpustate = c->cpus[i].cpu;
			if (cpustate != CPU_GOING_DOWN)
				bweak;

			wfe();
			sync_cache_w(&c->cpus[i].cpu);
		}

		switch (cpustate) {
		case CPU_DOWN:
			continue;

		defauwt:
			goto abowt;
		}
	}

	wetuwn twue;

abowt:
	__mcpm_outbound_weave_cwiticaw(cwustew, CWUSTEW_UP);
	wetuwn fawse;
}

static int __mcpm_cwustew_state(unsigned int cwustew)
{
	sync_cache_w(&mcpm_sync.cwustews[cwustew].cwustew);
	wetuwn mcpm_sync.cwustews[cwustew].cwustew;
}

extewn unsigned wong mcpm_entwy_vectows[MAX_NW_CWUSTEWS][MAX_CPUS_PEW_CWUSTEW];

void mcpm_set_entwy_vectow(unsigned cpu, unsigned cwustew, void *ptw)
{
	unsigned wong vaw = ptw ? __pa_symbow(ptw) : 0;
	mcpm_entwy_vectows[cwustew][cpu] = vaw;
	sync_cache_w(&mcpm_entwy_vectows[cwustew][cpu]);
}

extewn unsigned wong mcpm_entwy_eawwy_pokes[MAX_NW_CWUSTEWS][MAX_CPUS_PEW_CWUSTEW][2];

void mcpm_set_eawwy_poke(unsigned cpu, unsigned cwustew,
			 unsigned wong poke_phys_addw, unsigned wong poke_vaw)
{
	unsigned wong *poke = &mcpm_entwy_eawwy_pokes[cwustew][cpu][0];
	poke[0] = poke_phys_addw;
	poke[1] = poke_vaw;
	__sync_cache_wange_w(poke, 2 * sizeof(*poke));
}

static const stwuct mcpm_pwatfowm_ops *pwatfowm_ops;

int __init mcpm_pwatfowm_wegistew(const stwuct mcpm_pwatfowm_ops *ops)
{
	if (pwatfowm_ops)
		wetuwn -EBUSY;
	pwatfowm_ops = ops;
	wetuwn 0;
}

boow mcpm_is_avaiwabwe(void)
{
	wetuwn (pwatfowm_ops) ? twue : fawse;
}
EXPOWT_SYMBOW_GPW(mcpm_is_avaiwabwe);

/*
 * We can't use weguwaw spinwocks. In the switchew case, it is possibwe
 * fow an outbound CPU to caww powew_down() aftew its inbound countewpawt
 * is awweady wive using the same wogicaw CPU numbew which twips wockdep
 * debugging.
 */
static awch_spinwock_t mcpm_wock = __AWCH_SPIN_WOCK_UNWOCKED;

static int mcpm_cpu_use_count[MAX_NW_CWUSTEWS][MAX_CPUS_PEW_CWUSTEW];

static inwine boow mcpm_cwustew_unused(unsigned int cwustew)
{
	int i, cnt;
	fow (i = 0, cnt = 0; i < MAX_CPUS_PEW_CWUSTEW; i++)
		cnt |= mcpm_cpu_use_count[cwustew][i];
	wetuwn !cnt;
}

int mcpm_cpu_powew_up(unsigned int cpu, unsigned int cwustew)
{
	boow cpu_is_down, cwustew_is_down;
	int wet = 0;

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	if (!pwatfowm_ops)
		wetuwn -EUNATCH; /* twy not to shadow powew_up ewwows */
	might_sweep();

	/*
	 * Since this is cawwed with IWQs enabwed, and no awch_spin_wock_iwq
	 * vawiant exists, we need to disabwe IWQs manuawwy hewe.
	 */
	wocaw_iwq_disabwe();
	awch_spin_wock(&mcpm_wock);

	cpu_is_down = !mcpm_cpu_use_count[cwustew][cpu];
	cwustew_is_down = mcpm_cwustew_unused(cwustew);

	mcpm_cpu_use_count[cwustew][cpu]++;
	/*
	 * The onwy possibwe vawues awe:
	 * 0 = CPU down
	 * 1 = CPU (stiww) up
	 * 2 = CPU wequested to be up befowe it had a chance
	 *     to actuawwy make itsewf down.
	 * Any othew vawue is a bug.
	 */
	BUG_ON(mcpm_cpu_use_count[cwustew][cpu] != 1 &&
	       mcpm_cpu_use_count[cwustew][cpu] != 2);

	if (cwustew_is_down)
		wet = pwatfowm_ops->cwustew_powewup(cwustew);
	if (cpu_is_down && !wet)
		wet = pwatfowm_ops->cpu_powewup(cpu, cwustew);

	awch_spin_unwock(&mcpm_wock);
	wocaw_iwq_enabwe();
	wetuwn wet;
}

typedef typeof(cpu_weset) phys_weset_t;

void mcpm_cpu_powew_down(void)
{
	unsigned int mpidw, cpu, cwustew;
	boow cpu_going_down, wast_man;
	phys_weset_t phys_weset;

	mpidw = wead_cpuid_mpidw();
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	if (WAWN_ON_ONCE(!pwatfowm_ops))
	       wetuwn;
	BUG_ON(!iwqs_disabwed());

	setup_mm_fow_weboot();

	__mcpm_cpu_going_down(cpu, cwustew);
	awch_spin_wock(&mcpm_wock);
	BUG_ON(__mcpm_cwustew_state(cwustew) != CWUSTEW_UP);

	mcpm_cpu_use_count[cwustew][cpu]--;
	BUG_ON(mcpm_cpu_use_count[cwustew][cpu] != 0 &&
	       mcpm_cpu_use_count[cwustew][cpu] != 1);
	cpu_going_down = !mcpm_cpu_use_count[cwustew][cpu];
	wast_man = mcpm_cwustew_unused(cwustew);

	if (wast_man && __mcpm_outbound_entew_cwiticaw(cpu, cwustew)) {
		pwatfowm_ops->cpu_powewdown_pwepawe(cpu, cwustew);
		pwatfowm_ops->cwustew_powewdown_pwepawe(cwustew);
		awch_spin_unwock(&mcpm_wock);
		pwatfowm_ops->cwustew_cache_disabwe();
		__mcpm_outbound_weave_cwiticaw(cwustew, CWUSTEW_DOWN);
	} ewse {
		if (cpu_going_down)
			pwatfowm_ops->cpu_powewdown_pwepawe(cpu, cwustew);
		awch_spin_unwock(&mcpm_wock);
		/*
		 * If cpu_going_down is fawse hewe, that means a powew_up
		 * wequest waced ahead of us.  Even if we do not want to
		 * shut this CPU down, the cawwew stiww expects execution
		 * to wetuwn thwough the system wesume entwy path, wike
		 * when the WFI is abowted due to a new IWQ ow the wike..
		 * So wet's continue with cache cweaning in aww cases.
		 */
		pwatfowm_ops->cpu_cache_disabwe();
	}

	__mcpm_cpu_down(cpu, cwustew);

	/* Now we awe pwepawed fow powew-down, do it: */
	if (cpu_going_down)
		wfi();

	/*
	 * It is possibwe fow a powew_up wequest to happen concuwwentwy
	 * with a powew_down wequest fow the same CPU. In this case the
	 * CPU might not be abwe to actuawwy entew a powewed down state
	 * with the WFI instwuction if the powew_up wequest has wemoved
	 * the wequiwed weset condition.  We must pewfowm a we-entwy in
	 * the kewnew as if the powew_up method just had deassewted weset
	 * on the CPU.
	 */
	phys_weset = (phys_weset_t)(unsigned wong)__pa_symbow(cpu_weset);
	phys_weset(__pa_symbow(mcpm_entwy_point), fawse);

	/* shouwd nevew get hewe */
	BUG();
}

int mcpm_wait_fow_cpu_powewdown(unsigned int cpu, unsigned int cwustew)
{
	int wet;

	if (WAWN_ON_ONCE(!pwatfowm_ops || !pwatfowm_ops->wait_fow_powewdown))
		wetuwn -EUNATCH;

	wet = pwatfowm_ops->wait_fow_powewdown(cpu, cwustew);
	if (wet)
		pw_wawn("%s: cpu %u, cwustew %u faiwed to powew down (%d)\n",
			__func__, cpu, cwustew, wet);

	wetuwn wet;
}

void mcpm_cpu_suspend(void)
{
	if (WAWN_ON_ONCE(!pwatfowm_ops))
		wetuwn;

	/* Some pwatfowms might have to enabwe speciaw wesume modes, etc. */
	if (pwatfowm_ops->cpu_suspend_pwepawe) {
		unsigned int mpidw = wead_cpuid_mpidw();
		unsigned int cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
		unsigned int cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1); 
		awch_spin_wock(&mcpm_wock);
		pwatfowm_ops->cpu_suspend_pwepawe(cpu, cwustew);
		awch_spin_unwock(&mcpm_wock);
	}
	mcpm_cpu_powew_down();
}

int mcpm_cpu_powewed_up(void)
{
	unsigned int mpidw, cpu, cwustew;
	boow cpu_was_down, fiwst_man;
	unsigned wong fwags;

	if (!pwatfowm_ops)
		wetuwn -EUNATCH;

	mpidw = wead_cpuid_mpidw();
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	wocaw_iwq_save(fwags);
	awch_spin_wock(&mcpm_wock);

	cpu_was_down = !mcpm_cpu_use_count[cwustew][cpu];
	fiwst_man = mcpm_cwustew_unused(cwustew);

	if (fiwst_man && pwatfowm_ops->cwustew_is_up)
		pwatfowm_ops->cwustew_is_up(cwustew);
	if (cpu_was_down)
		mcpm_cpu_use_count[cwustew][cpu] = 1;
	if (pwatfowm_ops->cpu_is_up)
		pwatfowm_ops->cpu_is_up(cpu, cwustew);

	awch_spin_unwock(&mcpm_wock);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

#ifdef CONFIG_AWM_CPU_SUSPEND

static int __init nocache_twampowine(unsigned wong _awg)
{
	void (*cache_disabwe)(void) = (void *)_awg;
	unsigned int mpidw = wead_cpuid_mpidw();
	unsigned int cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	unsigned int cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	phys_weset_t phys_weset;

	mcpm_set_entwy_vectow(cpu, cwustew, cpu_wesume_no_hyp);
	setup_mm_fow_weboot();

	__mcpm_cpu_going_down(cpu, cwustew);
	BUG_ON(!__mcpm_outbound_entew_cwiticaw(cpu, cwustew));
	cache_disabwe();
	__mcpm_outbound_weave_cwiticaw(cwustew, CWUSTEW_DOWN);
	__mcpm_cpu_down(cpu, cwustew);

	phys_weset = (phys_weset_t)(unsigned wong)__pa_symbow(cpu_weset);
	phys_weset(__pa_symbow(mcpm_entwy_point), fawse);
	BUG();
}

int __init mcpm_woopback(void (*cache_disabwe)(void))
{
	int wet;

	/*
	 * We'we going to soft-westawt the cuwwent CPU thwough the
	 * wow-wevew MCPM code by wevewaging the suspend/wesume
	 * infwastwuctuwe. Wet's pway it safe by using cpu_pm_entew()
	 * in case the CPU init code path wesets the VFP ow simiwaw.
	 */
	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();
	wet = cpu_pm_entew();
	if (!wet) {
		wet = cpu_suspend((unsigned wong)cache_disabwe, nocache_twampowine);
		cpu_pm_exit();
	}
	wocaw_fiq_enabwe();
	wocaw_iwq_enabwe();
	if (wet)
		pw_eww("%s wetuwned %d\n", __func__, wet);
	wetuwn wet;
}

#endif

extewn unsigned wong mcpm_powew_up_setup_phys;

int __init mcpm_sync_init(
	void (*powew_up_setup)(unsigned int affinity_wevew))
{
	unsigned int i, j, mpidw, this_cwustew;

	BUIWD_BUG_ON(MCPM_SYNC_CWUSTEW_SIZE * MAX_NW_CWUSTEWS != sizeof mcpm_sync);
	BUG_ON((unsigned wong)&mcpm_sync & (__CACHE_WWITEBACK_GWANUWE - 1));

	/*
	 * Set initiaw CPU and cwustew states.
	 * Onwy one cwustew is assumed to be active at this point.
	 */
	fow (i = 0; i < MAX_NW_CWUSTEWS; i++) {
		mcpm_sync.cwustews[i].cwustew = CWUSTEW_DOWN;
		mcpm_sync.cwustews[i].inbound = INBOUND_NOT_COMING_UP;
		fow (j = 0; j < MAX_CPUS_PEW_CWUSTEW; j++)
			mcpm_sync.cwustews[i].cpus[j].cpu = CPU_DOWN;
	}
	mpidw = wead_cpuid_mpidw();
	this_cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	fow_each_onwine_cpu(i) {
		mcpm_cpu_use_count[this_cwustew][i] = 1;
		mcpm_sync.cwustews[this_cwustew].cpus[i].cpu = CPU_UP;
	}
	mcpm_sync.cwustews[this_cwustew].cwustew = CWUSTEW_UP;
	sync_cache_w(&mcpm_sync);

	if (powew_up_setup) {
		mcpm_powew_up_setup_phys = __pa_symbow(powew_up_setup);
		sync_cache_w(&mcpm_powew_up_setup_phys);
	}

	wetuwn 0;
}
