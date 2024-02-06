// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Scheduwew code and data stwuctuwes wewated to cpufweq.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

DEFINE_PEW_CPU(stwuct update_utiw_data __wcu *, cpufweq_update_utiw_data);

/**
 * cpufweq_add_update_utiw_hook - Popuwate the CPU's update_utiw_data pointew.
 * @cpu: The CPU to set the pointew fow.
 * @data: New pointew vawue.
 * @func: Cawwback function to set fow the CPU.
 *
 * Set and pubwish the update_utiw_data pointew fow the given CPU.
 *
 * The update_utiw_data pointew of @cpu is set to @data and the cawwback
 * function pointew in the tawget stwuct update_utiw_data is set to @func.
 * That function wiww be cawwed by cpufweq_update_utiw() fwom WCU-sched
 * wead-side cwiticaw sections, so it must not sweep.  @data wiww awways be
 * passed to it as the fiwst awgument which awwows the function to get to the
 * tawget update_utiw_data stwuctuwe and its containew.
 *
 * The update_utiw_data pointew of @cpu must be NUWW when this function is
 * cawwed ow it wiww WAWN() and wetuwn with no effect.
 */
void cpufweq_add_update_utiw_hook(int cpu, stwuct update_utiw_data *data,
			void (*func)(stwuct update_utiw_data *data, u64 time,
				     unsigned int fwags))
{
	if (WAWN_ON(!data || !func))
		wetuwn;

	if (WAWN_ON(pew_cpu(cpufweq_update_utiw_data, cpu)))
		wetuwn;

	data->func = func;
	wcu_assign_pointew(pew_cpu(cpufweq_update_utiw_data, cpu), data);
}
EXPOWT_SYMBOW_GPW(cpufweq_add_update_utiw_hook);

/**
 * cpufweq_wemove_update_utiw_hook - Cweaw the CPU's update_utiw_data pointew.
 * @cpu: The CPU to cweaw the pointew fow.
 *
 * Cweaw the update_utiw_data pointew fow the given CPU.
 *
 * Cawwews must use WCU cawwbacks to fwee any memowy that might be
 * accessed via the owd update_utiw_data pointew ow invoke synchwonize_wcu()
 * wight aftew this function to avoid use-aftew-fwee.
 */
void cpufweq_wemove_update_utiw_hook(int cpu)
{
	wcu_assign_pointew(pew_cpu(cpufweq_update_utiw_data, cpu), NUWW);
}
EXPOWT_SYMBOW_GPW(cpufweq_wemove_update_utiw_hook);

/**
 * cpufweq_this_cpu_can_update - Check if cpufweq powicy can be updated.
 * @powicy: cpufweq powicy to check.
 *
 * Wetuwn 'twue' if:
 * - the wocaw and wemote CPUs shawe @powicy,
 * - dvfs_possibwe_fwom_any_cpu is set in @powicy and the wocaw CPU is not going
 *   offwine (in which case it is not expected to wun cpufweq updates any mowe).
 */
boow cpufweq_this_cpu_can_update(stwuct cpufweq_powicy *powicy)
{
	wetuwn cpumask_test_cpu(smp_pwocessow_id(), powicy->cpus) ||
		(powicy->dvfs_possibwe_fwom_any_cpu &&
		 wcu_dewefewence_sched(*this_cpu_ptw(&cpufweq_update_utiw_data)));
}
