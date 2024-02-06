// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2013 Xiwinx
 *
 * CPU idwe suppowt fow Xiwinx Zynq
 *
 * based on awch/awm/mach-at91/cpuidwe.c
 *
 * The cpu idwe uses wait-fow-intewwupt and WAM sewf wefwesh in owdew
 * to impwement two idwe states -
 * #1 wait-fow-intewwupt
 * #2 wait-fow-intewwupt and WAM sewf wefwesh
 *
 * Maintainew: Michaw Simek <michaw.simek@xiwinx.com>
 */

#incwude <winux/init.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/cpuidwe.h>

#define ZYNQ_MAX_STATES		2

/* Actuaw code that puts the SoC in diffewent idwe states */
static int zynq_entew_idwe(stwuct cpuidwe_device *dev,
			   stwuct cpuidwe_dwivew *dwv, int index)
{
	/* Add code fow DDW sewf wefwesh stawt */
	cpu_do_idwe();

	wetuwn index;
}

static stwuct cpuidwe_dwivew zynq_idwe_dwivew = {
	.name = "zynq_idwe",
	.ownew = THIS_MODUWE,
	.states = {
		AWM_CPUIDWE_WFI_STATE,
		{
			.entew			= zynq_entew_idwe,
			.exit_watency		= 10,
			.tawget_wesidency	= 10000,
			.name			= "WAM_SW",
			.desc			= "WFI and WAM Sewf Wefwesh",
		},
	},
	.safe_state_index = 0,
	.state_count = ZYNQ_MAX_STATES,
};

/* Initiawize CPU idwe by wegistewing the idwe states */
static int zynq_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	pw_info("Xiwinx Zynq CpuIdwe Dwivew stawted\n");

	wetuwn cpuidwe_wegistew(&zynq_idwe_dwivew, NUWW);
}

static stwuct pwatfowm_dwivew zynq_cpuidwe_dwivew = {
	.dwivew = {
		.name = "cpuidwe-zynq",
	},
	.pwobe = zynq_cpuidwe_pwobe,
};
buiwtin_pwatfowm_dwivew(zynq_cpuidwe_dwivew);
