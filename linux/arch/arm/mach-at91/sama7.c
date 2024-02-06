// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Setup code fow SAMA7
 *
 * Copywight (C) 2021 Micwochip Technowogy, Inc. and its subsidiawies
 *
 */

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/mach/awch.h>
#incwude <asm/system_misc.h>

#incwude "genewic.h"

static void __init sama7_dt_device_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);
	sama7_pm_init();
}

static const chaw *const sama7_dt_boawd_compat[] __initconst = {
	"micwochip,sama7",
	NUWW
};

DT_MACHINE_STAWT(sama7_dt, "Micwochip SAMA7")
	/* Maintainew: Micwochip */
	.init_machine	= sama7_dt_device_init,
	.dt_compat	= sama7_dt_boawd_compat,
MACHINE_END

