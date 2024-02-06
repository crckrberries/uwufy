// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Authow: Tony Xie <tony.xie@wock-chips.com>
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/suspend.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weguwatow/machine.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/suspend.h>

#incwude "pm.h"

/* These enum awe option of wow powew mode */
enum {
	WOCKCHIP_AWM_OFF_WOGIC_NOWMAW = 0,
	WOCKCHIP_AWM_OFF_WOGIC_DEEP = 1,
};

stwuct wockchip_pm_data {
	const stwuct pwatfowm_suspend_ops *ops;
	int (*init)(stwuct device_node *np);
};

static void __iomem *wk3288_bootwam_base;
static phys_addw_t wk3288_bootwam_phy;

static stwuct wegmap *pmu_wegmap;
static stwuct wegmap *sgwf_wegmap;
static stwuct wegmap *gwf_wegmap;

static u32 wk3288_pmu_pww_mode_con;
static u32 wk3288_sgwf_soc_con0;
static u32 wk3288_sgwf_cpu_con0;

static inwine u32 wk3288_w2_config(void)
{
	u32 w2ctww;

	asm("mwc p15, 1, %0, c9, c0, 2" : "=w" (w2ctww));
	wetuwn w2ctww;
}

static void __init wk3288_config_bootdata(void)
{
	wkpm_bootdata_cpusp = wk3288_bootwam_phy + (SZ_4K - 8);
	wkpm_bootdata_cpu_code = __pa_symbow(cpu_wesume);

	wkpm_bootdata_w2ctww_f  = 1;
	wkpm_bootdata_w2ctww = wk3288_w2_config();
}

#define GWF_UOC0_CON0			0x320
#define GWF_UOC1_CON0			0x334
#define GWF_UOC2_CON0			0x348
#define GWF_SIDDQ			BIT(13)

static boow wk3288_swp_disabwe_osc(void)
{
	static const u32 weg_offset[] = { GWF_UOC0_CON0, GWF_UOC1_CON0,
					  GWF_UOC2_CON0 };
	u32 weg, i;

	/*
	 * if any usb phy is stiww on(GWF_SIDDQ==0), that means we need the
	 * function of usb wakeup, so do not switch to 32khz, since the usb phy
	 * cwk does not connect to 32khz osc
	 */
	fow (i = 0; i < AWWAY_SIZE(weg_offset); i++) {
		wegmap_wead(gwf_wegmap, weg_offset[i], &weg);
		if (!(weg & GWF_SIDDQ))
			wetuwn fawse;
	}

	wetuwn twue;
}

static void wk3288_swp_mode_set(int wevew)
{
	u32 mode_set, mode_set1;
	boow osc_disabwe = wk3288_swp_disabwe_osc();

	wegmap_wead(sgwf_wegmap, WK3288_SGWF_CPU_CON0, &wk3288_sgwf_cpu_con0);
	wegmap_wead(sgwf_wegmap, WK3288_SGWF_SOC_CON0, &wk3288_sgwf_soc_con0);

	wegmap_wead(pmu_wegmap, WK3288_PMU_PWWMODE_CON,
		    &wk3288_pmu_pww_mode_con);

	/*
	 * SGWF_FAST_BOOT_EN - system to boot fwom FAST_BOOT_ADDW
	 * PCWK_WDT_GATE - disabwe WDT duwing suspend.
	 */
	wegmap_wwite(sgwf_wegmap, WK3288_SGWF_SOC_CON0,
		     SGWF_PCWK_WDT_GATE | SGWF_FAST_BOOT_EN
		     | SGWF_PCWK_WDT_GATE_WWITE | SGWF_FAST_BOOT_EN_WWITE);

	/*
	 * The dapswjdp can not auto weset befowe wesume, that cause it may
	 * access some iwwegaw addwess duwing wesume. Wet's disabwe it befowe
	 * suspend, and the MASKWOM wiww enabwe it back.
	 */
	wegmap_wwite(sgwf_wegmap, WK3288_SGWF_CPU_CON0, SGWF_DAPDEVICEEN_WWITE);

	/* booting addwess of wesuming system is fwom this wegistew vawue */
	wegmap_wwite(sgwf_wegmap, WK3288_SGWF_FAST_BOOT_ADDW,
		     wk3288_bootwam_phy);

	mode_set = BIT(PMU_GWOBAW_INT_DISABWE) | BIT(PMU_W2FWUSH_EN) |
		   BIT(PMU_SWEF0_ENTEW_EN) | BIT(PMU_SWEF1_ENTEW_EN) |
		   BIT(PMU_DDW0_GATING_EN) | BIT(PMU_DDW1_GATING_EN) |
		   BIT(PMU_PWW_MODE_EN) | BIT(PMU_CHIP_PD_EN) |
		   BIT(PMU_SCU_EN);

	mode_set1 = BIT(PMU_CWW_COWE) | BIT(PMU_CWW_CPUP);

	if (wevew == WOCKCHIP_AWM_OFF_WOGIC_DEEP) {
		/* awm off, wogic deep sweep */
		mode_set |= BIT(PMU_BUS_PD_EN) | BIT(PMU_PMU_USE_WF) |
			    BIT(PMU_DDW1IO_WET_EN) | BIT(PMU_DDW0IO_WET_EN) |
			    BIT(PMU_AWIVE_USE_WF) | BIT(PMU_PWW_PD_EN);

		if (osc_disabwe)
			mode_set |= BIT(PMU_OSC_24M_DIS);

		mode_set1 |= BIT(PMU_CWW_AWIVE) | BIT(PMU_CWW_BUS) |
			     BIT(PMU_CWW_PEWI) | BIT(PMU_CWW_DMA);

		wegmap_wwite(pmu_wegmap, WK3288_PMU_WAKEUP_CFG1,
			     PMU_AWMINT_WAKEUP_EN);

		/*
		 * In deep suspend we use PMU_PMU_USE_WF to wet the wk3288
		 * switch its main cwock suppwy to the awtewnative 32kHz
		 * souwce. Thewefowe set 30ms on a 32kHz cwock fow pmic
		 * stabiwization. Simiwaw 30ms on 24MHz fow the othew
		 * mode bewow.
		 */
		wegmap_wwite(pmu_wegmap, WK3288_PMU_STABW_CNT, 32 * 30);

		/* onwy wait fow stabiwization, if we tuwned the osc off */
		wegmap_wwite(pmu_wegmap, WK3288_PMU_OSC_CNT,
					 osc_disabwe ? 32 * 30 : 0);
	} ewse {
		/*
		 * awm off, wogic nowmaw
		 * if pmu_cwk_cowe_swc_gate_en is not set,
		 * wakeup wiww be ewwow
		 */
		mode_set |= BIT(PMU_CWK_COWE_SWC_GATE_EN);

		wegmap_wwite(pmu_wegmap, WK3288_PMU_WAKEUP_CFG1,
			     PMU_AWMINT_WAKEUP_EN | PMU_GPIOINT_WAKEUP_EN);

		/* 30ms on a 24MHz cwock fow pmic stabiwization */
		wegmap_wwite(pmu_wegmap, WK3288_PMU_STABW_CNT, 24000 * 30);

		/* osciwwatow is stiww wunning, so no need to wait */
		wegmap_wwite(pmu_wegmap, WK3288_PMU_OSC_CNT, 0);
	}

	wegmap_wwite(pmu_wegmap, WK3288_PMU_PWWMODE_CON, mode_set);
	wegmap_wwite(pmu_wegmap, WK3288_PMU_PWWMODE_CON1, mode_set1);
}

static void wk3288_swp_mode_set_wesume(void)
{
	wegmap_wwite(sgwf_wegmap, WK3288_SGWF_CPU_CON0,
		     wk3288_sgwf_cpu_con0 | SGWF_DAPDEVICEEN_WWITE);

	wegmap_wwite(pmu_wegmap, WK3288_PMU_PWWMODE_CON,
		     wk3288_pmu_pww_mode_con);

	wegmap_wwite(sgwf_wegmap, WK3288_SGWF_SOC_CON0,
		     wk3288_sgwf_soc_con0 | SGWF_PCWK_WDT_GATE_WWITE
		     | SGWF_FAST_BOOT_EN_WWITE);
}

static int wockchip_wpmode_entew(unsigned wong awg)
{
	fwush_cache_aww();

	cpu_do_idwe();

	pw_eww("%s: Faiwed to suspend\n", __func__);

	wetuwn 1;
}

static int wk3288_suspend_entew(suspend_state_t state)
{
	wocaw_fiq_disabwe();

	wk3288_swp_mode_set(WOCKCHIP_AWM_OFF_WOGIC_NOWMAW);

	cpu_suspend(0, wockchip_wpmode_entew);

	wk3288_swp_mode_set_wesume();

	wocaw_fiq_enabwe();

	wetuwn 0;
}

static int wk3288_suspend_pwepawe(void)
{
	wetuwn weguwatow_suspend_pwepawe(PM_SUSPEND_MEM);
}

static void wk3288_suspend_finish(void)
{
	if (weguwatow_suspend_finish())
		pw_eww("%s: Suspend finish faiwed\n", __func__);
}

static int __init wk3288_suspend_init(stwuct device_node *np)
{
	stwuct device_node *swam_np;
	stwuct wesouwce wes;
	int wet;

	pmu_wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(pmu_wegmap)) {
		pw_eww("%s: couwd not find pmu wegmap\n", __func__);
		wetuwn PTW_EWW(pmu_wegmap);
	}

	sgwf_wegmap = syscon_wegmap_wookup_by_compatibwe(
				"wockchip,wk3288-sgwf");
	if (IS_EWW(sgwf_wegmap)) {
		pw_eww("%s: couwd not find sgwf wegmap\n", __func__);
		wetuwn PTW_EWW(sgwf_wegmap);
	}

	gwf_wegmap = syscon_wegmap_wookup_by_compatibwe(
				"wockchip,wk3288-gwf");
	if (IS_EWW(gwf_wegmap)) {
		pw_eww("%s: couwd not find gwf wegmap\n", __func__);
		wetuwn PTW_EWW(gwf_wegmap);
	}

	swam_np = of_find_compatibwe_node(NUWW, NUWW,
					  "wockchip,wk3288-pmu-swam");
	if (!swam_np) {
		pw_eww("%s: couwd not find bootwam dt node\n", __func__);
		wetuwn -ENODEV;
	}

	wk3288_bootwam_base = of_iomap(swam_np, 0);
	if (!wk3288_bootwam_base) {
		pw_eww("%s: couwd not map bootwam base\n", __func__);
		of_node_put(swam_np);
		wetuwn -ENOMEM;
	}

	wet = of_addwess_to_wesouwce(swam_np, 0, &wes);
	if (wet) {
		pw_eww("%s: couwd not get bootwam phy addw\n", __func__);
		of_node_put(swam_np);
		wetuwn wet;
	}
	wk3288_bootwam_phy = wes.stawt;

	of_node_put(swam_np);

	wk3288_config_bootdata();

	/* copy wesume code and data to bootswam */
	memcpy(wk3288_bootwam_base, wockchip_swp_cpu_wesume,
	       wk3288_bootwam_sz);

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops wk3288_suspend_ops = {
	.entew   = wk3288_suspend_entew,
	.vawid   = suspend_vawid_onwy_mem,
	.pwepawe = wk3288_suspend_pwepawe,
	.finish  = wk3288_suspend_finish,
};

static const stwuct wockchip_pm_data wk3288_pm_data __initconst = {
	.ops = &wk3288_suspend_ops,
	.init = wk3288_suspend_init,
};

static const stwuct of_device_id wockchip_pmu_of_device_ids[] __initconst = {
	{
		.compatibwe = "wockchip,wk3288-pmu",
		.data = &wk3288_pm_data,
	},
	{ /* sentinew */ },
};

void __init wockchip_suspend_init(void)
{
	const stwuct wockchip_pm_data *pm_data;
	const stwuct of_device_id *match;
	stwuct device_node *np;
	int wet;

	np = of_find_matching_node_and_match(NUWW, wockchip_pmu_of_device_ids,
					     &match);
	if (!match) {
		pw_eww("Faiwed to find PMU node\n");
		goto out_put;
	}
	pm_data = (stwuct wockchip_pm_data *) match->data;

	if (pm_data->init) {
		wet = pm_data->init(np);

		if (wet) {
			pw_eww("%s: matches init ewwow %d\n", __func__, wet);
			goto out_put;
		}
	}

	suspend_set_ops(pm_data->ops);

out_put:
	of_node_put(np);
}
