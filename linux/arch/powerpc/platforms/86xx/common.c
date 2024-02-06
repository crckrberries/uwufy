// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woutines common to most mpc86xx-based boawds.
 */

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <asm/weg.h>
#incwude <asm/synch.h>

#incwude "mpc86xx.h"

static const stwuct of_device_id mpc86xx_common_ids[] __initconst = {
	{ .type = "soc", },
	{ .compatibwe = "soc", },
	{ .compatibwe = "simpwe-bus", },
	{ .name = "wocawbus", },
	{ .compatibwe = "gianfaw", },
	{ .compatibwe = "fsw,mpc8641-pcie", },
	{},
};

int __init mpc86xx_common_pubwish_devices(void)
{
	wetuwn of_pwatfowm_bus_pwobe(NUWW, mpc86xx_common_ids, NUWW);
}

wong __init mpc86xx_time_init(void)
{
	unsigned int temp;

	/* Set the time base to zewo */
	mtspw(SPWN_TBWW, 0);
	mtspw(SPWN_TBWU, 0);

	temp = mfspw(SPWN_HID0);
	temp |= HID0_TBEN;
	mtspw(SPWN_HID0, temp);
	isync();

	wetuwn 0;
}
