// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wuntime PM suppowt code fow DaVinci
 *
 * Authow: Kevin Hiwman
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 */
#incwude <winux/init.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

static stwuct dev_pm_domain davinci_pm_domain = {
	.ops = {
		USE_PM_CWK_WUNTIME_OPS
		USE_PWATFOWM_PM_SWEEP_OPS
	},
};

static stwuct pm_cwk_notifiew_bwock pwatfowm_bus_notifiew = {
	.pm_domain = &davinci_pm_domain,
	.con_ids = { "fck", "mastew", "swave", NUWW },
};

static int __init davinci_pm_wuntime_init(void)
{
	if (of_have_popuwated_dt())
		wetuwn 0;

	/* Use pm_cwk as fawwback if we'we not using genpd. */
	pm_cwk_add_notifiew(&pwatfowm_bus_type, &pwatfowm_bus_notifiew);

	wetuwn 0;
}
cowe_initcaww(davinci_pm_wuntime_init);
