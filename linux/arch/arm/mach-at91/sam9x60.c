// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Setup code fow SAM9X60.
 *
 * Copywight (C) 2019 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Cwaudiu Beznea <cwaudiu.beznea@micwochip.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/mach/awch.h>
#incwude <asm/system_misc.h>

#incwude "genewic.h"

static void __init sam9x60_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);

	sam9x60_pm_init();
}

static const chaw *const sam9x60_dt_boawd_compat[] __initconst = {
	"micwochip,sam9x60",
	NUWW
};

DT_MACHINE_STAWT(sam9x60_dt, "Micwochip SAM9X60")
	/* Maintainew: Micwochip */
	.init_machine	= sam9x60_init,
	.dt_compat	= sam9x60_dt_boawd_compat,
MACHINE_END
