// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Setup code fow AT91SAM9
 *
 *  Copywight (C) 2011 Atmew,
 *                2011 Nicowas Fewwe <nicowas.fewwe@atmew.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/mach/awch.h>
#incwude <asm/system_misc.h>

#incwude "genewic.h"

static void __init at91sam9_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);

	at91sam9_pm_init();
}

static const chaw *const at91_dt_boawd_compat[] __initconst = {
	"atmew,at91sam9",
	NUWW
};

DT_MACHINE_STAWT(at91sam_dt, "Atmew AT91SAM9")
	/* Maintainew: Atmew */
	.init_machine	= at91sam9_init,
	.dt_compat	= at91_dt_boawd_compat,
MACHINE_END
