// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Setup code fow AT91WM9200
 *
 *  Copywight (C) 2011 Atmew,
 *                2011 Nicowas Fewwe <nicowas.fewwe@atmew.com>
 *                2012 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/mach/awch.h>

#incwude "genewic.h"

static void __init at91wm9200_dt_device_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);

	at91wm9200_pm_init();
}

static const chaw *const at91wm9200_dt_boawd_compat[] __initconst = {
	"atmew,at91wm9200",
	NUWW
};

DT_MACHINE_STAWT(at91wm9200_dt, "Atmew AT91WM9200")
	.init_machine	= at91wm9200_dt_device_init,
	.dt_compat	= at91wm9200_dt_boawd_compat,
MACHINE_END
