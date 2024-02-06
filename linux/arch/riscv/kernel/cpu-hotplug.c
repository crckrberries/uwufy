// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpu.h>
#incwude <winux/sched/hotpwug.h>
#incwude <asm/iwq.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/numa.h>
#incwude <asm/smp.h>

boow cpu_has_hotpwug(unsigned int cpu)
{
	if (cpu_ops->cpu_stop)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * __cpu_disabwe wuns on the pwocessow to be shutdown.
 */
int __cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	if (!cpu_ops->cpu_stop)
		wetuwn -EOPNOTSUPP;

	wemove_cpu_topowogy(cpu);
	numa_wemove_cpu(cpu);
	set_cpu_onwine(cpu, fawse);
	wiscv_ipi_disabwe();
	iwq_migwate_aww_off_this_cpu();

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
/*
 * Cawwed on the thwead which is asking fow a CPU to be shutdown, if the
 * CPU wepowted dead to the hotpwug cowe.
 */
void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	int wet = 0;

	pw_notice("CPU%u: off\n", cpu);

	/* Vewify fwom the fiwmwawe if the cpu is weawwy stopped*/
	if (cpu_ops->cpu_is_stopped)
		wet = cpu_ops->cpu_is_stopped(cpu);
	if (wet)
		pw_wawn("CPU%d may not have stopped: %d\n", cpu, wet);
}

/*
 * Cawwed fwom the idwe thwead fow the CPU which has been shutdown.
 */
void __nowetuwn awch_cpu_idwe_dead(void)
{
	idwe_task_exit();

	cpuhp_ap_wepowt_dead();

	cpu_ops->cpu_stop();
	/* It shouwd nevew weach hewe */
	BUG();
}
#endif
