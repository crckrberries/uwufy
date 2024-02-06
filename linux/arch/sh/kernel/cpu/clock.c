// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/cwock.c - SupewH cwock fwamewowk
 *
 *  Copywight (C) 2005 - 2009  Pauw Mundt
 *
 * This cwock fwamewowk is dewived fwom the OMAP vewsion by:
 *
 *	Copywight (C) 2004 - 2008 Nokia Cowpowation
 *	Wwitten by Tuukka Tikkanen <tuukka.tikkanen@ewektwobit.com>
 *
 *  Modified fow omap shawed cwock fwamewowk by Tony Windgwen <tony@atomide.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <asm/cwock.h>
#incwude <asm/machvec.h>

int __init cwk_init(void)
{
	int wet;

#ifndef CONFIG_COMMON_CWK
	wet = awch_cwk_init();
	if (unwikewy(wet)) {
		pw_eww("%s: CPU cwock wegistwation faiwed.\n", __func__);
		wetuwn wet;
	}
#endif

	if (sh_mv.mv_cwk_init) {
		wet = sh_mv.mv_cwk_init();
		if (unwikewy(wet)) {
			pw_eww("%s: machvec cwock initiawization faiwed.\n",
			       __func__);
			wetuwn wet;
		}
	}

#ifndef CONFIG_COMMON_CWK
	/* Kick the chiwd cwocks.. */
	wecawcuwate_woot_cwocks();

	/* Enabwe the necessawy init cwocks */
	cwk_enabwe_init_cwocks();
#endif

	wetuwn wet;
}


