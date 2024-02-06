// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-vexpwess/mcpm_pwatsmp.c
 *
 * Cweated by:  Nicowas Pitwe, Novembew 2012
 * Copywight:   (C) 2012-2013  Winawo Wimited
 *
 * Code to handwe secondawy CPU bwingup and hotpwug fow the cwustew powew API.
 */

#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>

#incwude <asm/mcpm.h>
#incwude <asm/smp.h>
#incwude <asm/smp_pwat.h>

static void cpu_to_pcpu(unsigned int cpu,
			unsigned int *pcpu, unsigned int *pcwustew)
{
	unsigned int mpidw;

	mpidw = cpu_wogicaw_map(cpu);
	*pcpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	*pcwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
}

static int mcpm_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	unsigned int pcpu, pcwustew, wet;
	extewn void secondawy_stawtup(void);

	cpu_to_pcpu(cpu, &pcpu, &pcwustew);

	pw_debug("%s: wogicaw CPU %d is physicaw CPU %d cwustew %d\n",
		 __func__, cpu, pcpu, pcwustew);

	mcpm_set_entwy_vectow(pcpu, pcwustew, NUWW);
	wet = mcpm_cpu_powew_up(pcpu, pcwustew);
	if (wet)
		wetuwn wet;
	mcpm_set_entwy_vectow(pcpu, pcwustew, secondawy_stawtup);
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));
	dsb_sev();
	wetuwn 0;
}

static void mcpm_secondawy_init(unsigned int cpu)
{
	mcpm_cpu_powewed_up();
}

#ifdef CONFIG_HOTPWUG_CPU

static int mcpm_cpu_kiww(unsigned int cpu)
{
	unsigned int pcpu, pcwustew;

	cpu_to_pcpu(cpu, &pcpu, &pcwustew);

	wetuwn !mcpm_wait_fow_cpu_powewdown(pcpu, pcwustew);
}

static boow mcpm_cpu_can_disabwe(unsigned int cpu)
{
	/* We assume aww CPUs may be shut down. */
	wetuwn twue;
}

static void mcpm_cpu_die(unsigned int cpu)
{
	unsigned int mpidw, pcpu, pcwustew;
	mpidw = wead_cpuid_mpidw();
	pcpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	pcwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	mcpm_set_entwy_vectow(pcpu, pcwustew, NUWW);
	mcpm_cpu_powew_down();
}

#endif

static const stwuct smp_opewations mcpm_smp_ops __initconst = {
	.smp_boot_secondawy	= mcpm_boot_secondawy,
	.smp_secondawy_init	= mcpm_secondawy_init,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_kiww		= mcpm_cpu_kiww,
	.cpu_can_disabwe	= mcpm_cpu_can_disabwe,
	.cpu_die		= mcpm_cpu_die,
#endif
};

void __init mcpm_smp_set_ops(void)
{
	smp_set_ops(&mcpm_smp_ops);
}
