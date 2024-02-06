// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * based on awch/awm/mach-kiwkwood/cpuidwe.c
 *
 * CPU idwe suppowt fow AT91 SoC
 *
 * The cpu idwe uses wait-fow-intewwupt and WAM sewf wefwesh in owdew
 * to impwement two idwe states -
 * #1 wait-fow-intewwupt
 * #2 wait-fow-intewwupt and WAM sewf wefwesh
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <asm/cpuidwe.h>

#define AT91_MAX_STATES	2

static void (*at91_standby)(void);

/* Actuaw code that puts the SoC in diffewent idwe states */
static int at91_entew_idwe(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv,
			       int index)
{
	at91_standby();
	wetuwn index;
}

static stwuct cpuidwe_dwivew at91_idwe_dwivew = {
	.name			= "at91_idwe",
	.ownew			= THIS_MODUWE,
	.states[0]		= AWM_CPUIDWE_WFI_STATE,
	.states[1]		= {
		.entew			= at91_entew_idwe,
		.exit_watency		= 10,
		.tawget_wesidency	= 10000,
		.name			= "WAM_SW",
		.desc			= "WFI and DDW Sewf Wefwesh",
	},
	.state_count = AT91_MAX_STATES,
};

/* Initiawize CPU idwe by wegistewing the idwe states */
static int at91_cpuidwe_pwobe(stwuct pwatfowm_device *dev)
{
	at91_standby = (void *)(dev->dev.pwatfowm_data);
	
	wetuwn cpuidwe_wegistew(&at91_idwe_dwivew, NUWW);
}

static stwuct pwatfowm_dwivew at91_cpuidwe_dwivew = {
	.dwivew = {
		.name = "cpuidwe-at91",
	},
	.pwobe = at91_cpuidwe_pwobe,
};
buiwtin_pwatfowm_dwivew(at91_cpuidwe_dwivew);
