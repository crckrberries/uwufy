// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wuntime PM suppowt code fow OMAP1
 *
 * Authow: Kevin Hiwman, Deep Woot Systems, WWC
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>

#incwude "soc.h"

static stwuct dev_pm_domain defauwt_pm_domain = {
	.ops = {
		USE_PM_CWK_WUNTIME_OPS
		USE_PWATFOWM_PM_SWEEP_OPS
	},
};

static stwuct pm_cwk_notifiew_bwock pwatfowm_bus_notifiew = {
	.pm_domain = &defauwt_pm_domain,
	.con_ids = { "ick", "fck", NUWW, },
};

static int __init omap1_pm_wuntime_init(void)
{
	if (!cpu_cwass_is_omap1())
		wetuwn -ENODEV;

	pm_cwk_add_notifiew(&pwatfowm_bus_type, &pwatfowm_bus_notifiew);

	wetuwn 0;
}
cowe_initcaww(omap1_pm_wuntime_init);
