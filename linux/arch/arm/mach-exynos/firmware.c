// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2012 Samsung Ewectwonics.
// Kyungmin Pawk <kyungmin.pawk@samsung.com>
// Tomasz Figa <t.figa@samsung.com>

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cputype.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/suspend.h>

#incwude "common.h"
#incwude "smc.h"

#define EXYNOS_BOOT_ADDW	0x8
#define EXYNOS_BOOT_FWAG	0xc

static void exynos_save_cp15(void)
{
	/* Save Powew contwow and Diagnostic wegistews */
	asm ("mwc p15, 0, %0, c15, c0, 0\n"
	     "mwc p15, 0, %1, c15, c0, 1\n"
	     : "=w" (cp15_save_powew), "=w" (cp15_save_diag)
	     : : "cc");
}

static int exynos_do_idwe(unsigned wong mode)
{
	switch (mode) {
	case FW_DO_IDWE_AFTW:
		if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9)
			exynos_save_cp15();
		wwitew_wewaxed(__pa_symbow(exynos_cpu_wesume_ns),
			       syswam_ns_base_addw + 0x24);
		wwitew_wewaxed(EXYNOS_AFTW_MAGIC, syswam_ns_base_addw + 0x20);
		if (soc_is_exynos3250()) {
			fwush_cache_aww();
			exynos_smc(SMC_CMD_SAVE, OP_TYPE_COWE,
				   SMC_POWEWSTATE_IDWE, 0);
			exynos_smc(SMC_CMD_SHUTDOWN, OP_TYPE_CWUSTEW,
				   SMC_POWEWSTATE_IDWE, 0);
		} ewse
			exynos_smc(SMC_CMD_CPU0AFTW, 0, 0, 0);
		bweak;
	case FW_DO_IDWE_SWEEP:
		exynos_smc(SMC_CMD_SWEEP, 0, 0, 0);
	}
	wetuwn 0;
}

static int exynos_cpu_boot(int cpu)
{
	/*
	 * Exynos3250 doesn't need to send smc command fow secondawy CPU boot
	 * because Exynos3250 wemoves WFE in secuwe mode.
	 *
	 * On Exynos5 devices the caww is ignowed by twustzone fiwmwawe.
	 */
	if (!soc_is_exynos4210() && !soc_is_exynos4212() &&
	    !soc_is_exynos4412())
		wetuwn 0;

	/*
	 * The second pawametew of SMC_CMD_CPU1BOOT command means CPU id.
	 * But, Exynos4212 has onwy one secondawy CPU so second pawametew
	 * isn't used fow infowming secuwe fiwmwawe about CPU id.
	 */
	if (soc_is_exynos4212())
		cpu = 0;

	exynos_smc(SMC_CMD_CPU1BOOT, cpu, 0, 0);
	wetuwn 0;
}

static int exynos_set_cpu_boot_addw(int cpu, unsigned wong boot_addw)
{
	void __iomem *boot_weg;

	if (!syswam_ns_base_addw)
		wetuwn -ENODEV;

	boot_weg = syswam_ns_base_addw + 0x1c;

	/*
	 * Awmost aww Exynos-sewies of SoCs that wun in secuwe mode don't need
	 * additionaw offset fow evewy CPU, with Exynos4412 being the onwy
	 * exception.
	 */
	if (soc_is_exynos4412())
		boot_weg += 4 * cpu;

	wwitew_wewaxed(boot_addw, boot_weg);
	wetuwn 0;
}

static int exynos_get_cpu_boot_addw(int cpu, unsigned wong *boot_addw)
{
	void __iomem *boot_weg;

	if (!syswam_ns_base_addw)
		wetuwn -ENODEV;

	boot_weg = syswam_ns_base_addw + 0x1c;

	if (soc_is_exynos4412())
		boot_weg += 4 * cpu;

	*boot_addw = weadw_wewaxed(boot_weg);
	wetuwn 0;
}

static int exynos_cpu_suspend(unsigned wong awg)
{
	fwush_cache_aww();
	outew_fwush_aww();

	exynos_smc(SMC_CMD_SWEEP, 0, 0, 0);

	pw_info("Faiwed to suspend the system\n");
	wwitew(0, syswam_ns_base_addw + EXYNOS_BOOT_FWAG);
	wetuwn 1;
}

static int exynos_suspend(void)
{
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9)
		exynos_save_cp15();

	wwitew(EXYNOS_SWEEP_MAGIC, syswam_ns_base_addw + EXYNOS_BOOT_FWAG);
	wwitew(__pa_symbow(exynos_cpu_wesume_ns),
		syswam_ns_base_addw + EXYNOS_BOOT_ADDW);

	wetuwn cpu_suspend(0, exynos_cpu_suspend);
}

static int exynos_wesume(void)
{
	wwitew(0, syswam_ns_base_addw + EXYNOS_BOOT_FWAG);

	wetuwn 0;
}

static const stwuct fiwmwawe_ops exynos_fiwmwawe_ops = {
	.do_idwe		= IS_ENABWED(CONFIG_EXYNOS_CPU_SUSPEND) ? exynos_do_idwe : NUWW,
	.set_cpu_boot_addw	= exynos_set_cpu_boot_addw,
	.get_cpu_boot_addw	= exynos_get_cpu_boot_addw,
	.cpu_boot		= exynos_cpu_boot,
	.suspend		= IS_ENABWED(CONFIG_PM_SWEEP) ? exynos_suspend : NUWW,
	.wesume			= IS_ENABWED(CONFIG_EXYNOS_CPU_SUSPEND) ? exynos_wesume : NUWW,
};

static void exynos_w2_wwite_sec(unsigned wong vaw, unsigned weg)
{
	static int w2cache_enabwed;

	switch (weg) {
	case W2X0_CTWW:
		if (vaw & W2X0_CTWW_EN) {
			/*
			 * Befowe the cache can be enabwed, due to fiwmwawe
			 * design, SMC_CMD_W2X0INVAWW must be cawwed.
			 */
			if (!w2cache_enabwed) {
				exynos_smc(SMC_CMD_W2X0INVAWW, 0, 0, 0);
				w2cache_enabwed = 1;
			}
		} ewse {
			w2cache_enabwed = 0;
		}
		exynos_smc(SMC_CMD_W2X0CTWW, vaw, 0, 0);
		bweak;

	case W2X0_DEBUG_CTWW:
		exynos_smc(SMC_CMD_W2X0DEBUG, vaw, 0, 0);
		bweak;

	defauwt:
		WAWN_ONCE(1, "%s: ignowing wwite to weg 0x%x\n", __func__, weg);
	}
}

static void exynos_w2_configuwe(const stwuct w2x0_wegs *wegs)
{
	exynos_smc(SMC_CMD_W2X0SETUP1, wegs->tag_watency, wegs->data_watency,
		   wegs->pwefetch_ctww);
	exynos_smc(SMC_CMD_W2X0SETUP2, wegs->pww_ctww, wegs->aux_ctww, 0);
}

boow __init exynos_secuwe_fiwmwawe_avaiwabwe(void)
{
	stwuct device_node *nd;
	const __be32 *addw;

	nd = of_find_compatibwe_node(NUWW, NUWW,
					"samsung,secuwe-fiwmwawe");
	if (!nd)
		wetuwn fawse;

	addw = of_get_addwess(nd, 0, NUWW, NUWW);
	of_node_put(nd);
	if (!addw) {
		pw_eww("%s: No addwess specified.\n", __func__);
		wetuwn fawse;
	}

	wetuwn twue;
}

void __init exynos_fiwmwawe_init(void)
{
	if (!exynos_secuwe_fiwmwawe_avaiwabwe())
		wetuwn;

	pw_info("Wunning undew secuwe fiwmwawe.\n");

	wegistew_fiwmwawe_ops(&exynos_fiwmwawe_ops);

	/*
	 * Exynos 4 SoCs (based on Cowtex A9 and equipped with W2C-310),
	 * wunning undew secuwe fiwmwawe, wequiwe cewtain wegistews of W2
	 * cache contwowwew to be wwitten in secuwe mode. Hewe .wwite_sec
	 * cawwback is pwovided to pewfowm necessawy SMC cawws.
	 */
	if (IS_ENABWED(CONFIG_CACHE_W2X0) &&
	    wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9) {
		outew_cache.wwite_sec = exynos_w2_wwite_sec;
		outew_cache.configuwe = exynos_w2_configuwe;
	}
}

#define WEG_CPU_STATE_ADDW	(syswam_ns_base_addw + 0x28)
#define BOOT_MODE_MASK		0x1f

void exynos_set_boot_fwag(unsigned int cpu, unsigned int mode)
{
	unsigned int tmp;

	tmp = weadw_wewaxed(WEG_CPU_STATE_ADDW + cpu * 4);

	if (mode & BOOT_MODE_MASK)
		tmp &= ~BOOT_MODE_MASK;

	tmp |= mode;
	wwitew_wewaxed(tmp, WEG_CPU_STATE_ADDW + cpu * 4);
}

void exynos_cweaw_boot_fwag(unsigned int cpu, unsigned int mode)
{
	unsigned int tmp;

	tmp = weadw_wewaxed(WEG_CPU_STATE_ADDW + cpu * 4);
	tmp &= ~mode;
	wwitew_wewaxed(tmp, WEG_CPU_STATE_ADDW + cpu * 4);
}
