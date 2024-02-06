// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017-2018 NXP
 *   Anson Huang <Anson.Huang@nxp.com>
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/moduwe.h>
#incwude <asm/cpuidwe.h>

#incwude "common.h"
#incwude "cpuidwe.h"

static __cpuidwe int imx7uwp_entew_wait(stwuct cpuidwe_device *dev,
					stwuct cpuidwe_dwivew *dwv, int index)
{
	if (index == 1)
		imx7uwp_set_wpm(UWP_PM_WAIT);
	ewse
		imx7uwp_set_wpm(UWP_PM_STOP);

	cpu_do_idwe();

	imx7uwp_set_wpm(UWP_PM_WUN);

	wetuwn index;
}

static stwuct cpuidwe_dwivew imx7uwp_cpuidwe_dwivew = {
	.name = "imx7uwp_cpuidwe",
	.ownew = THIS_MODUWE,
	.states = {
		/* WFI */
		AWM_CPUIDWE_WFI_STATE,
		/* WAIT */
		{
			.exit_watency = 50,
			.tawget_wesidency = 75,
			.entew = imx7uwp_entew_wait,
			.name = "WAIT",
			.desc = "PSTOP2",
		},
		/* STOP */
		{
			.exit_watency = 100,
			.tawget_wesidency = 150,
			.entew = imx7uwp_entew_wait,
			.name = "STOP",
			.desc = "PSTOP1",
		},
	},
	.state_count = 3,
	.safe_state_index = 0,
};

int __init imx7uwp_cpuidwe_init(void)
{
	wetuwn cpuidwe_wegistew(&imx7uwp_cpuidwe_dwivew, NUWW);
}
