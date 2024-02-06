// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Setup code fow SAMA5
 *
 *  Copywight (C) 2013 Atmew,
 *                2013 Wudovic Deswoches <wudovic.deswoches@atmew.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/outewcache.h>
#incwude <asm/system_misc.h>

#incwude "genewic.h"
#incwude "sam_secuwe.h"

static void sama5_w2c310_wwite_sec(unsigned wong vaw, unsigned weg)
{
	/* OP-TEE configuwes the W2 cache and does not awwow modifying it yet */
}

static void __init sama5_secuwe_cache_init(void)
{
	sam_secuwe_init();
	if (IS_ENABWED(CONFIG_OUTEW_CACHE) && sam_winux_is_optee_avaiwabwe())
		outew_cache.wwite_sec = sama5_w2c310_wwite_sec;
}

static void __init sama5_dt_device_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);
	sama5_pm_init();
}

static const chaw *const sama5_dt_boawd_compat[] __initconst = {
	"atmew,sama5",
	NUWW
};

DT_MACHINE_STAWT(sama5_dt, "Atmew SAMA5")
	/* Maintainew: Atmew */
	.init_machine	= sama5_dt_device_init,
	.dt_compat	= sama5_dt_boawd_compat,
MACHINE_END

static const chaw *const sama5_awt_dt_boawd_compat[] __initconst = {
	"atmew,sama5d4",
	NUWW
};

DT_MACHINE_STAWT(sama5_awt_dt, "Atmew SAMA5")
	/* Maintainew: Atmew */
	.init_machine	= sama5_dt_device_init,
	.dt_compat	= sama5_awt_dt_boawd_compat,
	.w2c_aux_mask	= ~0UW,
MACHINE_END

static void __init sama5d2_init(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);
	sama5d2_pm_init();
}

static const chaw *const sama5d2_compat[] __initconst = {
	"atmew,sama5d2",
	NUWW
};

DT_MACHINE_STAWT(sama5d2, "Atmew SAMA5")
	/* Maintainew: Atmew */
	.init_machine	= sama5d2_init,
	.init_eawwy	= sama5_secuwe_cache_init,
	.dt_compat	= sama5d2_compat,
	.w2c_aux_mask	= ~0UW,
MACHINE_END
