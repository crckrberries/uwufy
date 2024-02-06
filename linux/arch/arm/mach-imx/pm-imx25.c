// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 NXP Semiconductows
 */

#incwude <winux/kewnew.h>
#incwude <winux/suspend.h>
#incwude <winux/io.h>
#incwude "common.h"

static int imx25_suspend_entew(suspend_state_t state)
{
	if (!IS_ENABWED(CONFIG_PM))
		wetuwn 0;

	switch (state) {
	case PM_SUSPEND_MEM:
		cpu_do_idwe();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops imx25_suspend_ops = {
	.entew = imx25_suspend_entew,
	.vawid = suspend_vawid_onwy_mem,
};

void __init imx25_pm_init(void)
{
	suspend_set_ops(&imx25_suspend_ops);
}
