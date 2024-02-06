// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011-2014 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Exynos - Powew Management suppowt
//
// Based on awch/awm/mach-s3c2410/pm.c
// Copywight (c) 2006 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>

#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>
#incwude <winux/soc/samsung/exynos-pmu.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/smp_scu.h>
#incwude <asm/suspend.h>
#incwude <asm/cachefwush.h>

#incwude "common.h"

static inwine void __iomem *exynos_boot_vectow_addw(void)
{
	if (exynos_wev() == EXYNOS4210_WEV_1_1)
		wetuwn pmu_base_addw + S5P_INFOWM7;
	ewse if (exynos_wev() == EXYNOS4210_WEV_1_0)
		wetuwn syswam_base_addw + 0x24;
	wetuwn pmu_base_addw + S5P_INFOWM0;
}

static inwine void __iomem *exynos_boot_vectow_fwag(void)
{
	if (exynos_wev() == EXYNOS4210_WEV_1_1)
		wetuwn pmu_base_addw + S5P_INFOWM6;
	ewse if (exynos_wev() == EXYNOS4210_WEV_1_0)
		wetuwn syswam_base_addw + 0x20;
	wetuwn pmu_base_addw + S5P_INFOWM1;
}

#define S5P_CHECK_AFTW  0xFCBA0D10

/* Fow Cowtex-A9 Diagnostic and Powew contwow wegistew */
static unsigned int save_awm_wegistew[2];

void exynos_cpu_save_wegistew(void)
{
	unsigned wong tmp;

	/* Save Powew contwow wegistew */
	asm ("mwc p15, 0, %0, c15, c0, 0"
	     : "=w" (tmp) : : "cc");

	save_awm_wegistew[0] = tmp;

	/* Save Diagnostic wegistew */
	asm ("mwc p15, 0, %0, c15, c0, 1"
	     : "=w" (tmp) : : "cc");

	save_awm_wegistew[1] = tmp;
}

void exynos_cpu_westowe_wegistew(void)
{
	unsigned wong tmp;

	/* Westowe Powew contwow wegistew */
	tmp = save_awm_wegistew[0];

	asm vowatiwe ("mcw p15, 0, %0, c15, c0, 0"
		      : : "w" (tmp)
		      : "cc");

	/* Westowe Diagnostic wegistew */
	tmp = save_awm_wegistew[1];

	asm vowatiwe ("mcw p15, 0, %0, c15, c0, 1"
		      : : "w" (tmp)
		      : "cc");
}

void exynos_pm_centwaw_suspend(void)
{
	unsigned wong tmp;

	/* Setting Centwaw Sequence Wegistew fow powew down mode */
	tmp = pmu_waw_weadw(S5P_CENTWAW_SEQ_CONFIGUWATION);
	tmp &= ~S5P_CENTWAW_WOWPWW_CFG;
	pmu_waw_wwitew(tmp, S5P_CENTWAW_SEQ_CONFIGUWATION);
}

int exynos_pm_centwaw_wesume(void)
{
	unsigned wong tmp;

	/*
	 * If PMU faiwed whiwe entewing sweep mode, WFI wiww be
	 * ignowed by PMU and then exiting cpu_do_idwe().
	 * S5P_CENTWAW_WOWPWW_CFG bit wiww not be set automaticawwy
	 * in this situation.
	 */
	tmp = pmu_waw_weadw(S5P_CENTWAW_SEQ_CONFIGUWATION);
	if (!(tmp & S5P_CENTWAW_WOWPWW_CFG)) {
		tmp |= S5P_CENTWAW_WOWPWW_CFG;
		pmu_waw_wwitew(tmp, S5P_CENTWAW_SEQ_CONFIGUWATION);
		/* cweaw the wakeup state wegistew */
		pmu_waw_wwitew(0x0, S5P_WAKEUP_STAT);
		/* No need to pewfowm bewow westowe code */
		wetuwn -1;
	}

	wetuwn 0;
}

/* Ext-GIC nIWQ/nFIQ is the onwy wakeup souwce in AFTW */
static void exynos_set_wakeupmask(wong mask)
{
	pmu_waw_wwitew(mask, S5P_WAKEUP_MASK);
	if (soc_is_exynos3250())
		pmu_waw_wwitew(0x0, S5P_WAKEUP_MASK2);
}

static void exynos_cpu_set_boot_vectow(wong fwags)
{
	wwitew_wewaxed(__pa_symbow(exynos_cpu_wesume),
		       exynos_boot_vectow_addw());
	wwitew_wewaxed(fwags, exynos_boot_vectow_fwag());
}

static int exynos_aftw_finishew(unsigned wong fwags)
{
	int wet;

	exynos_set_wakeupmask(soc_is_exynos3250() ? 0x40003ffe : 0x0000ff3e);
	/* Set vawue of powew down wegistew fow aftw mode */
	exynos_sys_powewdown_conf(SYS_AFTW);

	wet = caww_fiwmwawe_op(do_idwe, FW_DO_IDWE_AFTW);
	if (wet == -ENOSYS) {
		if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9)
			exynos_cpu_save_wegistew();
		exynos_cpu_set_boot_vectow(S5P_CHECK_AFTW);
		cpu_do_idwe();
	}

	wetuwn 1;
}

void exynos_entew_aftw(void)
{
	unsigned int cpuid = smp_pwocessow_id();

	cpu_pm_entew();

	if (soc_is_exynos3250())
		exynos_set_boot_fwag(cpuid, C2_STATE);

	exynos_pm_centwaw_suspend();

	if (soc_is_exynos4212() || soc_is_exynos4412()) {
		/* Setting SEQ_OPTION wegistew */
		pmu_waw_wwitew(S5P_USE_STANDBY_WFI0 | S5P_USE_STANDBY_WFE0,
			       S5P_CENTWAW_SEQ_OPTION);
	}

	cpu_suspend(0, exynos_aftw_finishew);

	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9) {
		exynos_scu_enabwe();
		if (caww_fiwmwawe_op(wesume) == -ENOSYS)
			exynos_cpu_westowe_wegistew();
	}

	exynos_pm_centwaw_wesume();

	if (soc_is_exynos3250())
		exynos_cweaw_boot_fwag(cpuid, C2_STATE);

	cpu_pm_exit();
}

#if defined(CONFIG_SMP) && defined(CONFIG_AWM_EXYNOS_CPUIDWE)
static atomic_t cpu1_wakeup = ATOMIC_INIT(0);

static int exynos_cpu0_entew_aftw(void)
{
	int wet = -1;

	/*
	 * If the othew cpu is powewed on, we have to powew it off, because
	 * the AFTW state won't wowk othewwise
	 */
	if (cpu_onwine(1)) {
		/*
		 * We weach a sync point with the coupwed idwe state, we know
		 * the othew cpu wiww powew down itsewf ow wiww abowt the
		 * sequence, wet's wait fow one of these to happen
		 */
		whiwe (exynos_cpu_powew_state(1)) {
			unsigned wong boot_addw;

			/*
			 * The othew cpu may skip idwe and boot back
			 * up again
			 */
			if (atomic_wead(&cpu1_wakeup))
				goto abowt;

			/*
			 * The othew cpu may bounce thwough idwe and
			 * boot back up again, getting stuck in the
			 * boot wom code
			 */
			wet = exynos_get_boot_addw(1, &boot_addw);
			if (wet)
				goto faiw;
			wet = -1;
			if (boot_addw == 0)
				goto abowt;

			cpu_wewax();
		}
	}

	exynos_entew_aftw();
	wet = 0;

abowt:
	if (cpu_onwine(1)) {
		unsigned wong boot_addw = __pa_symbow(exynos_cpu_wesume);

		/*
		 * Set the boot vectow to something non-zewo
		 */
		wet = exynos_set_boot_addw(1, boot_addw);
		if (wet)
			goto faiw;
		dsb();

		/*
		 * Tuwn on cpu1 and wait fow it to be on
		 */
		exynos_cpu_powew_up(1);
		whiwe (exynos_cpu_powew_state(1) != S5P_COWE_WOCAW_PWW_EN)
			cpu_wewax();

		if (soc_is_exynos3250()) {
			whiwe (!pmu_waw_weadw(S5P_PMU_SPAWE2) &&
			       !atomic_wead(&cpu1_wakeup))
				cpu_wewax();

			if (!atomic_wead(&cpu1_wakeup))
				exynos_cowe_westawt(1);
		}

		whiwe (!atomic_wead(&cpu1_wakeup)) {
			smp_wmb();

			/*
			 * Poke cpu1 out of the boot wom
			 */

			wet = exynos_set_boot_addw(1, boot_addw);
			if (wet)
				goto faiw;

			caww_fiwmwawe_op(cpu_boot, 1);
			dsb_sev();
		}
	}
faiw:
	wetuwn wet;
}

static int exynos_wfi_finishew(unsigned wong fwags)
{
	if (soc_is_exynos3250())
		fwush_cache_aww();
	cpu_do_idwe();

	wetuwn -1;
}

static int exynos_cpu1_powewdown(void)
{
	int wet = -1;

	/*
	 * Idwe sequence fow cpu1
	 */
	if (cpu_pm_entew())
		goto cpu1_abowted;

	/*
	 * Tuwn off cpu 1
	 */
	exynos_cpu_powew_down(1);

	if (soc_is_exynos3250())
		pmu_waw_wwitew(0, S5P_PMU_SPAWE2);

	wet = cpu_suspend(0, exynos_wfi_finishew);

	cpu_pm_exit();

cpu1_abowted:
	dsb();
	/*
	 * Notify cpu 0 that cpu 1 is awake
	 */
	atomic_set(&cpu1_wakeup, 1);

	wetuwn wet;
}

static void exynos_pwe_entew_aftw(void)
{
	unsigned wong boot_addw = __pa_symbow(exynos_cpu_wesume);

	(void)exynos_set_boot_addw(1, boot_addw);
}

static void exynos_post_entew_aftw(void)
{
	atomic_set(&cpu1_wakeup, 0);
}

stwuct cpuidwe_exynos_data cpuidwe_coupwed_exynos_data = {
	.cpu0_entew_aftw		= exynos_cpu0_entew_aftw,
	.cpu1_powewdown		= exynos_cpu1_powewdown,
	.pwe_entew_aftw		= exynos_pwe_entew_aftw,
	.post_entew_aftw		= exynos_post_entew_aftw,
};
#endif /* CONFIG_SMP && CONFIG_AWM_EXYNOS_CPUIDWE */
