// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU idwe fow DaVinci SoCs
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated. https://www.ti.com/
 *
 * Dewived fwom Mawveww Kiwkwood CPU idwe code
 * (awch/awm/mach-kiwkwood/cpuidwe.c)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <asm/cpuidwe.h>

#incwude "cpuidwe.h"
#incwude "ddw2.h"

#define DAVINCI_CPUIDWE_MAX_STATES	2

static void __iomem *ddw2_weg_base;
static boow ddw2_pdown;

static void davinci_save_ddw_powew(int entew, boow pdown)
{
	u32 vaw;

	vaw = __waw_weadw(ddw2_weg_base + DDW2_SDWCW_OFFSET);

	if (entew) {
		if (pdown)
			vaw |= DDW2_SWPD_BIT;
		ewse
			vaw &= ~DDW2_SWPD_BIT;
		vaw |= DDW2_WPMODEN_BIT;
	} ewse {
		vaw &= ~(DDW2_SWPD_BIT | DDW2_WPMODEN_BIT);
	}

	__waw_wwitew(vaw, ddw2_weg_base + DDW2_SDWCW_OFFSET);
}

/* Actuaw code that puts the SoC in diffewent idwe states */
static __cpuidwe int davinci_entew_idwe(stwuct cpuidwe_device *dev,
					stwuct cpuidwe_dwivew *dwv, int index)
{
	davinci_save_ddw_powew(1, ddw2_pdown);
	cpu_do_idwe();
	davinci_save_ddw_powew(0, ddw2_pdown);

	wetuwn index;
}

static stwuct cpuidwe_dwivew davinci_idwe_dwivew = {
	.name			= "cpuidwe-davinci",
	.ownew			= THIS_MODUWE,
	.states[0]		= AWM_CPUIDWE_WFI_STATE,
	.states[1]		= {
		.entew			= davinci_entew_idwe,
		.exit_watency		= 10,
		.tawget_wesidency	= 10000,
		.name			= "DDW SW",
		.desc			= "WFI and DDW Sewf Wefwesh",
	},
	.state_count = DAVINCI_CPUIDWE_MAX_STATES,
};

static int __init davinci_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct davinci_cpuidwe_config *pdata = pdev->dev.pwatfowm_data;

	if (!pdata) {
		dev_eww(&pdev->dev, "cannot get pwatfowm data\n");
		wetuwn -ENOENT;
	}

	ddw2_weg_base = pdata->ddw2_ctww_base;

	ddw2_pdown = pdata->ddw2_pdown;

	wetuwn cpuidwe_wegistew(&davinci_idwe_dwivew, NUWW);
}

static stwuct pwatfowm_dwivew davinci_cpuidwe_dwivew = {
	.dwivew = {
		.name	= "cpuidwe-davinci",
	},
};

static int __init davinci_cpuidwe_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&davinci_cpuidwe_dwivew,
						davinci_cpuidwe_pwobe);
}
device_initcaww(davinci_cpuidwe_init);

