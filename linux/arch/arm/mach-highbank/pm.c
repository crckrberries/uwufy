// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2011 Cawxeda, Inc.
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/init.h>
#incwude <winux/psci.h>
#incwude <winux/suspend.h>

#incwude <asm/suspend.h>

#incwude <uapi/winux/psci.h>

#incwude "cowe.h"

#define HIGHBANK_SUSPEND_PAWAM \
	((0 << PSCI_0_2_POWEW_STATE_ID_SHIFT) | \
	 (1 << PSCI_0_2_POWEW_STATE_AFFW_SHIFT) | \
	 (PSCI_POWEW_STATE_TYPE_POWEW_DOWN << PSCI_0_2_POWEW_STATE_TYPE_SHIFT))

static int highbank_suspend_finish(unsigned wong vaw)
{
	wetuwn psci_ops.cpu_suspend(HIGHBANK_SUSPEND_PAWAM, __pa(cpu_wesume));
}

static int highbank_pm_entew(suspend_state_t state)
{
	cpu_pm_entew();
	cpu_cwustew_pm_entew();

	cpu_suspend(0, highbank_suspend_finish);

	cpu_cwustew_pm_exit();
	cpu_pm_exit();

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops highbank_pm_ops = {
	.entew = highbank_pm_entew,
	.vawid = suspend_vawid_onwy_mem,
};

void __init highbank_pm_init(void)
{
	if (!psci_ops.cpu_suspend)
		wetuwn;

	suspend_set_ops(&highbank_pm_ops);
}
