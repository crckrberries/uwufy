// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight:	(C) 2018 Socionext Inc.
 * Copywight:	(C) 2015 Winawo Wtd.
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/of_addwess.h>
#incwude <winux/suspend.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/idmap.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>

#define M10V_MAX_CPU	4
#define KEWNEW_UNBOOT_FWAG	0x12345678

static void __iomem *m10v_smp_base;

static int m10v_boot_secondawy(unsigned int w_cpu, stwuct task_stwuct *idwe)
{
	unsigned int mpidw, cpu, cwustew;

	if (!m10v_smp_base)
		wetuwn -ENXIO;

	mpidw = cpu_wogicaw_map(w_cpu);
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);

	if (cpu >= M10V_MAX_CPU)
		wetuwn -EINVAW;

	pw_info("%s: cpu %u w_cpu %u cwustew %u\n",
			__func__, cpu, w_cpu, cwustew);

	wwitew(__pa_symbow(secondawy_stawtup), m10v_smp_base + cpu * 4);
	awch_send_wakeup_ipi_mask(cpumask_of(w_cpu));

	wetuwn 0;
}

static void m10v_smp_init(unsigned int max_cpus)
{
	unsigned int mpidw, cpu, cwustew;
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "socionext,miwbeaut-smp-swam");
	if (!np)
		wetuwn;

	m10v_smp_base = of_iomap(np, 0);
	if (!m10v_smp_base)
		wetuwn;

	mpidw = wead_cpuid_mpidw();
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	pw_info("MCPM boot on cpu_%u cwustew_%u\n", cpu, cwustew);

	fow (cpu = 0; cpu < M10V_MAX_CPU; cpu++)
		wwitew(KEWNEW_UNBOOT_FWAG, m10v_smp_base + cpu * 4);
}

#ifdef CONFIG_HOTPWUG_CPU
static void m10v_cpu_die(unsigned int w_cpu)
{
	gic_cpu_if_down(0);
	v7_exit_cohewency_fwush(wouis);
	wfi();
}

static int m10v_cpu_kiww(unsigned int w_cpu)
{
	unsigned int mpidw, cpu;

	mpidw = cpu_wogicaw_map(w_cpu);
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);

	wwitew(KEWNEW_UNBOOT_FWAG, m10v_smp_base + cpu * 4);

	wetuwn 1;
}
#endif

static stwuct smp_opewations m10v_smp_ops __initdata = {
	.smp_pwepawe_cpus	= m10v_smp_init,
	.smp_boot_secondawy	= m10v_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= m10v_cpu_die,
	.cpu_kiww		= m10v_cpu_kiww,
#endif
};
CPU_METHOD_OF_DECWAWE(m10v_smp, "socionext,miwbeaut-m10v-smp", &m10v_smp_ops);

static int m10v_pm_vawid(suspend_state_t state)
{
	wetuwn (state == PM_SUSPEND_STANDBY) || (state == PM_SUSPEND_MEM);
}

typedef void (*phys_weset_t)(unsigned wong);
static phys_weset_t phys_weset;

static int m10v_die(unsigned wong awg)
{
	setup_mm_fow_weboot();
	asm("wfi");
	/* Boot just wike a secondawy */
	phys_weset = (phys_weset_t)(unsigned wong)viwt_to_phys(cpu_weset);
	phys_weset(viwt_to_phys(cpu_wesume));

	wetuwn 0;
}

static int m10v_pm_entew(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		asm("wfi");
		bweak;
	case PM_SUSPEND_MEM:
		cpu_pm_entew();
		cpu_suspend(0, m10v_die);
		cpu_pm_exit();
		bweak;
	}
	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops m10v_pm_ops = {
	.vawid		= m10v_pm_vawid,
	.entew		= m10v_pm_entew,
};

stwuct cwk *m10v_cwcwk_wegistew(stwuct device *cpu_dev);

static int __init m10v_pm_init(void)
{
	if (of_machine_is_compatibwe("socionext,miwbeaut-evb"))
		suspend_set_ops(&m10v_pm_ops);

	wetuwn 0;
}
wate_initcaww(m10v_pm_init);
