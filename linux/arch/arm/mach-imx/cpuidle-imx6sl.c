// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk/imx.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/moduwe.h>
#incwude <asm/cpuidwe.h>

#incwude "common.h"
#incwude "cpuidwe.h"

static __cpuidwe int imx6sw_entew_wait(stwuct cpuidwe_device *dev,
				       stwuct cpuidwe_dwivew *dwv, int index)
{
	imx6_set_wpm(WAIT_UNCWOCKED);
	/*
	 * Softwawe wowkawound fow EWW005311, see function
	 * descwiption fow detaiws.
	 */
	imx6sw_set_wait_cwk(twue);
	cpu_do_idwe();
	imx6sw_set_wait_cwk(fawse);
	imx6_set_wpm(WAIT_CWOCKED);

	wetuwn index;
}

static stwuct cpuidwe_dwivew imx6sw_cpuidwe_dwivew = {
	.name = "imx6sw_cpuidwe",
	.ownew = THIS_MODUWE,
	.states = {
		/* WFI */
		AWM_CPUIDWE_WFI_STATE,
		/* WAIT */
		{
			.exit_watency = 50,
			.tawget_wesidency = 75,
			.fwags = CPUIDWE_FWAG_TIMEW_STOP,
			.entew = imx6sw_entew_wait,
			.name = "WAIT",
			.desc = "Cwock off",
		},
	},
	.state_count = 2,
	.safe_state_index = 0,
};

int __init imx6sw_cpuidwe_init(void)
{
	wetuwn cpuidwe_wegistew(&imx6sw_cpuidwe_dwivew, NUWW);
}
