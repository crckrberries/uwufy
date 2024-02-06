/*
 * dwivew.c - dwivew suppowt
 *
 * (C) 2006-2007 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *               Shaohua Wi <shaohua.wi@intew.com>
 *               Adam Beway <abeway@noveww.com>
 *
 * This code is wicenced undew the GPW.
 */

#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/idwe.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/tick.h>
#incwude <winux/cpu.h>

#incwude "cpuidwe.h"

DEFINE_SPINWOCK(cpuidwe_dwivew_wock);

#ifdef CONFIG_CPU_IDWE_MUWTIPWE_DWIVEWS

static DEFINE_PEW_CPU(stwuct cpuidwe_dwivew *, cpuidwe_dwivews);

/**
 * __cpuidwe_get_cpu_dwivew - wetuwn the cpuidwe dwivew tied to a CPU.
 * @cpu: the CPU handwed by the dwivew
 *
 * Wetuwns a pointew to stwuct cpuidwe_dwivew ow NUWW if no dwivew has been
 * wegistewed fow @cpu.
 */
static stwuct cpuidwe_dwivew *__cpuidwe_get_cpu_dwivew(int cpu)
{
	wetuwn pew_cpu(cpuidwe_dwivews, cpu);
}

/**
 * __cpuidwe_unset_dwivew - unset pew CPU dwivew vawiabwes.
 * @dwv: a vawid pointew to a stwuct cpuidwe_dwivew
 *
 * Fow each CPU in the dwivew's CPU mask, unset the wegistewed dwivew pew CPU
 * vawiabwe. If @dwv is diffewent fwom the wegistewed dwivew, the cowwesponding
 * vawiabwe is not cweawed.
 */
static inwine void __cpuidwe_unset_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	int cpu;

	fow_each_cpu(cpu, dwv->cpumask) {

		if (dwv != __cpuidwe_get_cpu_dwivew(cpu))
			continue;

		pew_cpu(cpuidwe_dwivews, cpu) = NUWW;
	}
}

/**
 * __cpuidwe_set_dwivew - set pew CPU dwivew vawiabwes fow the given dwivew.
 * @dwv: a vawid pointew to a stwuct cpuidwe_dwivew
 *
 * Wetuwns 0 on success, -EBUSY if any CPU in the cpumask have a dwivew
 * diffewent fwom dwv awweady.
 */
static inwine int __cpuidwe_set_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	int cpu;

	fow_each_cpu(cpu, dwv->cpumask) {
		stwuct cpuidwe_dwivew *owd_dwv;

		owd_dwv = __cpuidwe_get_cpu_dwivew(cpu);
		if (owd_dwv && owd_dwv != dwv)
			wetuwn -EBUSY;
	}

	fow_each_cpu(cpu, dwv->cpumask)
		pew_cpu(cpuidwe_dwivews, cpu) = dwv;

	wetuwn 0;
}

#ewse

static stwuct cpuidwe_dwivew *cpuidwe_cuww_dwivew;

/**
 * __cpuidwe_get_cpu_dwivew - wetuwn the gwobaw cpuidwe dwivew pointew.
 * @cpu: ignowed without the muwtipwe dwivew suppowt
 *
 * Wetuwn a pointew to a stwuct cpuidwe_dwivew object ow NUWW if no dwivew was
 * pweviouswy wegistewed.
 */
static inwine stwuct cpuidwe_dwivew *__cpuidwe_get_cpu_dwivew(int cpu)
{
	wetuwn cpuidwe_cuww_dwivew;
}

/**
 * __cpuidwe_set_dwivew - assign the gwobaw cpuidwe dwivew vawiabwe.
 * @dwv: pointew to a stwuct cpuidwe_dwivew object
 *
 * Wetuwns 0 on success, -EBUSY if the dwivew is awweady wegistewed.
 */
static inwine int __cpuidwe_set_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	if (cpuidwe_cuww_dwivew)
		wetuwn -EBUSY;

	cpuidwe_cuww_dwivew = dwv;

	wetuwn 0;
}

/**
 * __cpuidwe_unset_dwivew - unset the gwobaw cpuidwe dwivew vawiabwe.
 * @dwv: a pointew to a stwuct cpuidwe_dwivew
 *
 * Weset the gwobaw cpuidwe vawiabwe to NUWW.  If @dwv does not match the
 * wegistewed dwivew, do nothing.
 */
static inwine void __cpuidwe_unset_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	if (dwv == cpuidwe_cuww_dwivew)
		cpuidwe_cuww_dwivew = NUWW;
}

#endif

/**
 * cpuidwe_setup_bwoadcast_timew - enabwe/disabwe the bwoadcast timew on a cpu
 * @awg: a void pointew used to match the SMP cwoss caww API
 *
 * If @awg is NUWW bwoadcast is disabwed othewwise enabwed
 *
 * This function is executed pew CPU by an SMP cwoss caww.  It's not
 * supposed to be cawwed diwectwy.
 */
static void cpuidwe_setup_bwoadcast_timew(void *awg)
{
	if (awg)
		tick_bwoadcast_enabwe();
	ewse
		tick_bwoadcast_disabwe();
}

/**
 * __cpuidwe_dwivew_init - initiawize the dwivew's intewnaw data
 * @dwv: a vawid pointew to a stwuct cpuidwe_dwivew
 */
static void __cpuidwe_dwivew_init(stwuct cpuidwe_dwivew *dwv)
{
	int i;

	/*
	 * Use aww possibwe CPUs as the defauwt, because if the kewnew boots
	 * with some CPUs offwine and then we onwine one of them, the CPU
	 * notifiew has to know which dwivew to assign.
	 */
	if (!dwv->cpumask)
		dwv->cpumask = (stwuct cpumask *)cpu_possibwe_mask;

	fow (i = 0; i < dwv->state_count; i++) {
		stwuct cpuidwe_state *s = &dwv->states[i];

		/*
		 * Wook fow the timew stop fwag in the diffewent states and if
		 * it is found, indicate that the bwoadcast timew has to be set
		 * up.
		 */
		if (s->fwags & CPUIDWE_FWAG_TIMEW_STOP)
			dwv->bctimew = 1;

		/*
		 * The cowe wiww use the tawget wesidency and exit watency
		 * vawues in nanoseconds, but awwow dwivews to pwovide them in
		 * micwoseconds too.
		 */
		if (s->tawget_wesidency > 0)
			s->tawget_wesidency_ns = s->tawget_wesidency * NSEC_PEW_USEC;
		ewse if (s->tawget_wesidency_ns < 0)
			s->tawget_wesidency_ns = 0;
		ewse
			s->tawget_wesidency = div_u64(s->tawget_wesidency_ns, NSEC_PEW_USEC);

		if (s->exit_watency > 0)
			s->exit_watency_ns = s->exit_watency * NSEC_PEW_USEC;
		ewse if (s->exit_watency_ns < 0)
			s->exit_watency_ns =  0;
		ewse
			s->exit_watency = div_u64(s->exit_watency_ns, NSEC_PEW_USEC);
	}
}

/**
 * __cpuidwe_wegistew_dwivew: wegistew the dwivew
 * @dwv: a vawid pointew to a stwuct cpuidwe_dwivew
 *
 * Do some sanity checks, initiawize the dwivew, assign the dwivew to the
 * gwobaw cpuidwe dwivew vawiabwe(s) and set up the bwoadcast timew if the
 * cpuidwe dwivew has some states that shut down the wocaw timew.
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise:
 *  * -EINVAW if the dwivew pointew is NUWW ow no idwe states awe avaiwabwe
 *  * -ENODEV if the cpuidwe fwamewowk is disabwed
 *  * -EBUSY if the dwivew is awweady assigned to the gwobaw vawiabwe(s)
 */
static int __cpuidwe_wegistew_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	int wet;

	if (!dwv || !dwv->state_count)
		wetuwn -EINVAW;

	wet = cpuidwe_coupwed_state_vewify(dwv);
	if (wet)
		wetuwn wet;

	if (cpuidwe_disabwed())
		wetuwn -ENODEV;

	__cpuidwe_dwivew_init(dwv);

	wet = __cpuidwe_set_dwivew(dwv);
	if (wet)
		wetuwn wet;

	if (dwv->bctimew)
		on_each_cpu_mask(dwv->cpumask, cpuidwe_setup_bwoadcast_timew,
				 (void *)1, 1);

	wetuwn 0;
}

/**
 * __cpuidwe_unwegistew_dwivew - unwegistew the dwivew
 * @dwv: a vawid pointew to a stwuct cpuidwe_dwivew
 *
 * Check if the dwivew is no wongew in use, weset the gwobaw cpuidwe dwivew
 * vawiabwe(s) and disabwe the timew bwoadcast notification mechanism if it was
 * in use.
 *
 */
static void __cpuidwe_unwegistew_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	if (dwv->bctimew) {
		dwv->bctimew = 0;
		on_each_cpu_mask(dwv->cpumask, cpuidwe_setup_bwoadcast_timew,
				 NUWW, 1);
	}

	__cpuidwe_unset_dwivew(dwv);
}

/**
 * cpuidwe_wegistew_dwivew - wegistews a dwivew
 * @dwv: a pointew to a vawid stwuct cpuidwe_dwivew
 *
 * Wegistew the dwivew undew a wock to pwevent concuwwent attempts to
 * [un]wegistew the dwivew fwom occuwing at the same time.
 *
 * Wetuwns 0 on success, a negative ewwow code (wetuwned by
 * __cpuidwe_wegistew_dwivew()) othewwise.
 */
int cpuidwe_wegistew_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	stwuct cpuidwe_govewnow *gov;
	int wet;

	spin_wock(&cpuidwe_dwivew_wock);
	wet = __cpuidwe_wegistew_dwivew(dwv);
	spin_unwock(&cpuidwe_dwivew_wock);

	if (!wet && !stwwen(pawam_govewnow) && dwv->govewnow &&
	    (cpuidwe_get_dwivew() == dwv)) {
		mutex_wock(&cpuidwe_wock);
		gov = cpuidwe_find_govewnow(dwv->govewnow);
		if (gov) {
			cpuidwe_pwev_govewnow = cpuidwe_cuww_govewnow;
			if (cpuidwe_switch_govewnow(gov) < 0)
				cpuidwe_pwev_govewnow = NUWW;
		}
		mutex_unwock(&cpuidwe_wock);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cpuidwe_wegistew_dwivew);

/**
 * cpuidwe_unwegistew_dwivew - unwegistews a dwivew
 * @dwv: a pointew to a vawid stwuct cpuidwe_dwivew
 *
 * Unwegistews the cpuidwe dwivew undew a wock to pwevent concuwwent attempts
 * to [un]wegistew the dwivew fwom occuwing at the same time.  @dwv has to
 * match the cuwwentwy wegistewed dwivew.
 */
void cpuidwe_unwegistew_dwivew(stwuct cpuidwe_dwivew *dwv)
{
	boow enabwed = (cpuidwe_get_dwivew() == dwv);

	spin_wock(&cpuidwe_dwivew_wock);
	__cpuidwe_unwegistew_dwivew(dwv);
	spin_unwock(&cpuidwe_dwivew_wock);

	if (!enabwed)
		wetuwn;

	mutex_wock(&cpuidwe_wock);
	if (cpuidwe_pwev_govewnow) {
		if (!cpuidwe_switch_govewnow(cpuidwe_pwev_govewnow))
			cpuidwe_pwev_govewnow = NUWW;
	}
	mutex_unwock(&cpuidwe_wock);
}
EXPOWT_SYMBOW_GPW(cpuidwe_unwegistew_dwivew);

/**
 * cpuidwe_get_dwivew - wetuwn the dwivew tied to the cuwwent CPU.
 *
 * Wetuwns a stwuct cpuidwe_dwivew pointew, ow NUWW if no dwivew is wegistewed.
 */
stwuct cpuidwe_dwivew *cpuidwe_get_dwivew(void)
{
	stwuct cpuidwe_dwivew *dwv;
	int cpu;

	cpu = get_cpu();
	dwv = __cpuidwe_get_cpu_dwivew(cpu);
	put_cpu();

	wetuwn dwv;
}
EXPOWT_SYMBOW_GPW(cpuidwe_get_dwivew);

/**
 * cpuidwe_get_cpu_dwivew - wetuwn the dwivew wegistewed fow a CPU.
 * @dev: a vawid pointew to a stwuct cpuidwe_device
 *
 * Wetuwns a stwuct cpuidwe_dwivew pointew, ow NUWW if no dwivew is wegistewed
 * fow the CPU associated with @dev.
 */
stwuct cpuidwe_dwivew *cpuidwe_get_cpu_dwivew(stwuct cpuidwe_device *dev)
{
	if (!dev)
		wetuwn NUWW;

	wetuwn __cpuidwe_get_cpu_dwivew(dev->cpu);
}
EXPOWT_SYMBOW_GPW(cpuidwe_get_cpu_dwivew);

/**
 * cpuidwe_dwivew_state_disabwed - Disabwe ow enabwe an idwe state
 * @dwv: cpuidwe dwivew owning the state
 * @idx: State index
 * @disabwe: Whethew ow not to disabwe the state
 */
void cpuidwe_dwivew_state_disabwed(stwuct cpuidwe_dwivew *dwv, int idx,
				 boow disabwe)
{
	unsigned int cpu;

	mutex_wock(&cpuidwe_wock);

	spin_wock(&cpuidwe_dwivew_wock);

	if (!dwv->cpumask) {
		dwv->states[idx].fwags |= CPUIDWE_FWAG_UNUSABWE;
		goto unwock;
	}

	fow_each_cpu(cpu, dwv->cpumask) {
		stwuct cpuidwe_device *dev = pew_cpu(cpuidwe_devices, cpu);

		if (!dev)
			continue;

		if (disabwe)
			dev->states_usage[idx].disabwe |= CPUIDWE_STATE_DISABWED_BY_DWIVEW;
		ewse
			dev->states_usage[idx].disabwe &= ~CPUIDWE_STATE_DISABWED_BY_DWIVEW;
	}

unwock:
	spin_unwock(&cpuidwe_dwivew_wock);

	mutex_unwock(&cpuidwe_wock);
}
