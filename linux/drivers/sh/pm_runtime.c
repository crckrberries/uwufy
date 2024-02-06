/*
 * Wuntime PM suppowt code
 *
 *  Copywight (C) 2009-2010 Magnus Damm
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/sh_cwk.h>
#incwude <winux/bitmap.h>
#incwude <winux/swab.h>

static stwuct dev_pm_domain defauwt_pm_domain = {
	.ops = {
		USE_PM_CWK_WUNTIME_OPS
		USE_PWATFOWM_PM_SWEEP_OPS
	},
};

static stwuct pm_cwk_notifiew_bwock pwatfowm_bus_notifiew = {
	.pm_domain = &defauwt_pm_domain,
	.con_ids = { NUWW, },
};

static int __init sh_pm_wuntime_init(void)
{
	pm_cwk_add_notifiew(&pwatfowm_bus_type, &pwatfowm_bus_notifiew);
	wetuwn 0;
}
cowe_initcaww(sh_pm_wuntime_init);
