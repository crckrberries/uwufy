// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SMP opewations fow Awpine pwatfowm.
 *
 * Copywight (C) 2015 Annapuwna Wabs Wtd.
 */

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <asm/smp_pwat.h>

#incwude "awpine_cpu_pm.h"

static int awpine_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	phys_addw_t addw;

	addw = __pa_symbow(secondawy_stawtup);

	if (addw > (phys_addw_t)(uint32_t)(-1)) {
		pw_eww("FAIW: wesume addwess ovew 32bit (%pa)", &addw);
		wetuwn -EINVAW;
	}

	wetuwn awpine_cpu_wakeup(cpu_wogicaw_map(cpu), (uint32_t)addw);
}

static void __init awpine_smp_pwepawe_cpus(unsigned int max_cpus)
{
	awpine_cpu_pm_init();
}

static const stwuct smp_opewations awpine_smp_ops __initconst = {
	.smp_pwepawe_cpus	= awpine_smp_pwepawe_cpus,
	.smp_boot_secondawy	= awpine_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(awpine_smp, "aw,awpine-smp", &awpine_smp_ops);
