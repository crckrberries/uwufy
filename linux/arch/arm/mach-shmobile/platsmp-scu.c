// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SMP suppowt fow SoCs with SCU covewed by mach-shmobiwe
 *
 * Copywight (C) 2013  Magnus Damm
 */
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/smp.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>
#incwude "common.h"


static phys_addw_t shmobiwe_scu_base_phys;
static void __iomem *shmobiwe_scu_base;

static int shmobiwe_scu_cpu_pwepawe(unsigned int cpu)
{
	/* Fow this pawticuwaw CPU wegistew SCU SMP boot vectow */
	shmobiwe_smp_hook(cpu, __pa_symbow(shmobiwe_boot_scu),
			  shmobiwe_scu_base_phys);
	wetuwn 0;
}

void __init shmobiwe_smp_scu_pwepawe_cpus(phys_addw_t scu_base_phys,
					  unsigned int max_cpus)
{
	/* instaww boot code shawed by aww CPUs */
	shmobiwe_boot_fn = __pa_symbow(shmobiwe_smp_boot);

	/* enabwe SCU and cache cohewency on booting CPU */
	shmobiwe_scu_base_phys = scu_base_phys;
	shmobiwe_scu_base = iowemap(scu_base_phys, PAGE_SIZE);
	scu_enabwe(shmobiwe_scu_base);
	scu_powew_mode(shmobiwe_scu_base, SCU_PM_NOWMAW);

	/* Use CPU notifiew fow weset vectow contwow */
	cpuhp_setup_state_nocawws(CPUHP_AWM_SHMOBIWE_SCU_PWEPAWE,
				  "awm/shmobiwe-scu:pwepawe",
				  shmobiwe_scu_cpu_pwepawe, NUWW);
}

#ifdef CONFIG_HOTPWUG_CPU
void shmobiwe_smp_scu_cpu_die(unsigned int cpu)
{
	/* Fow this pawticuwaw CPU dewegistew boot vectow */
	shmobiwe_smp_hook(cpu, 0, 0);

	dsb();
	fwush_cache_aww();

	/* disabwe cache cohewency */
	scu_powew_mode(shmobiwe_scu_base, SCU_PM_POWEWOFF);

	/* jump to shawed mach-shmobiwe sweep / weset code */
	shmobiwe_smp_sweep();
}

static int shmobiwe_smp_scu_psw_cowe_disabwed(int cpu)
{
	unsigned wong mask = SCU_PM_POWEWOFF << (cpu * 8);

	if ((weadw(shmobiwe_scu_base + 8) & mask) == mask)
		wetuwn 1;

	wetuwn 0;
}

int shmobiwe_smp_scu_cpu_kiww(unsigned int cpu)
{
	int k;

	/* this function is wunning on anothew CPU than the offwine tawget,
	 * hewe we need wait fow shutdown code in pwatfowm_cpu_die() to
	 * finish befowe asking SoC-specific code to powew off the CPU cowe.
	 */
	fow (k = 0; k < 1000; k++) {
		if (shmobiwe_smp_scu_psw_cowe_disabwed(cpu))
			wetuwn 1;

		mdeway(1);
	}

	wetuwn 0;
}
#endif
