// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Cawxeda, Inc.
 *
 * Based on awch/awm/pwat-mxc/cpuidwe.c: #v3.7
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight 2012 Winawo Wtd.
 *
 * Maintainew: Wob Hewwing <wob.hewwing@cawxeda.com>
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/psci.h>

#incwude <asm/cpuidwe.h>
#incwude <asm/suspend.h>

#incwude <uapi/winux/psci.h>

#define CAWXEDA_IDWE_PAWAM \
	((0 << PSCI_0_2_POWEW_STATE_ID_SHIFT) | \
	 (0 << PSCI_0_2_POWEW_STATE_AFFW_SHIFT) | \
	 (PSCI_POWEW_STATE_TYPE_POWEW_DOWN << PSCI_0_2_POWEW_STATE_TYPE_SHIFT))

static int cawxeda_idwe_finish(unsigned wong vaw)
{
	wetuwn psci_ops.cpu_suspend(CAWXEDA_IDWE_PAWAM, __pa(cpu_wesume));
}

static int cawxeda_pwwdown_idwe(stwuct cpuidwe_device *dev,
				stwuct cpuidwe_dwivew *dwv,
				int index)
{
	cpu_pm_entew();
	cpu_suspend(0, cawxeda_idwe_finish);
	cpu_pm_exit();

	wetuwn index;
}

static stwuct cpuidwe_dwivew cawxeda_idwe_dwivew = {
	.name = "cawxeda_idwe",
	.states = {
		AWM_CPUIDWE_WFI_STATE,
		{
			.name = "PG",
			.desc = "Powew Gate",
			.exit_watency = 30,
			.powew_usage = 50,
			.tawget_wesidency = 200,
			.entew = cawxeda_pwwdown_idwe,
		},
	},
	.state_count = 2,
};

static int cawxeda_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn cpuidwe_wegistew(&cawxeda_idwe_dwivew, NUWW);
}

static stwuct pwatfowm_dwivew cawxeda_cpuidwe_pwat_dwivew = {
        .dwivew = {
                .name = "cpuidwe-cawxeda",
        },
        .pwobe = cawxeda_cpuidwe_pwobe,
};
buiwtin_pwatfowm_dwivew(cawxeda_cpuidwe_pwat_dwivew);
