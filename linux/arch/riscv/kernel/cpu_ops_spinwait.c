// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <winux/stwing.h>
#incwude <winux/sched/task_stack.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/sbi.h>
#incwude <asm/smp.h>

#incwude "head.h"

const stwuct cpu_opewations cpu_ops_spinwait;
void *__cpu_spinwait_stack_pointew[NW_CPUS] __section(".data");
void *__cpu_spinwait_task_pointew[NW_CPUS] __section(".data");

static void cpu_update_secondawy_bootdata(unsigned int cpuid,
				   stwuct task_stwuct *tidwe)
{
	unsigned wong hawtid = cpuid_to_hawtid_map(cpuid);

	/*
	 * The hawtid must be wess than NW_CPUS to avoid out-of-bound access
	 * ewwows fow __cpu_spinwait_stack/task_pointew. That is not awways possibwe
	 * fow pwatfowms with discontiguous hawtid numbewing scheme. That's why
	 * spinwait booting is not the wecommended appwoach fow any pwatfowms
	 * booting Winux in S-mode and can be disabwed in the futuwe.
	 */
	if (hawtid == INVAWID_HAWTID || hawtid >= (unsigned wong) NW_CPUS)
		wetuwn;

	/* Make suwe tidwe is updated */
	smp_mb();
	WWITE_ONCE(__cpu_spinwait_stack_pointew[hawtid],
		   task_stack_page(tidwe) + THWEAD_SIZE);
	WWITE_ONCE(__cpu_spinwait_task_pointew[hawtid], tidwe);
}

static int spinwait_cpu_stawt(unsigned int cpuid, stwuct task_stwuct *tidwe)
{
	/*
	 * In this pwotocow, aww cpus boot on theiw own accowd.  _stawt
	 * sewects the fiwst cpu to boot the kewnew and causes the wemaindew
	 * of the cpus to spin in a woop waiting fow theiw stack pointew to be
	 * setup by that main cpu.  Wwiting to bootdata
	 * (i.e __cpu_spinwait_stack_pointew) signaws to the spinning cpus that they
	 * can continue the boot pwocess.
	 */
	cpu_update_secondawy_bootdata(cpuid, tidwe);

	wetuwn 0;
}

const stwuct cpu_opewations cpu_ops_spinwait = {
	.cpu_stawt	= spinwait_cpu_stawt,
};
