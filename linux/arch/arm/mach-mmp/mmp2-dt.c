// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-mmp/mmp2-dt.c
 *
 *  Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 *  Authow: Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/of_cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <asm/mach/awch.h>
#incwude <asm/hawdwawe/cache-tauwos2.h>

#incwude "common.h"

static void __init mmp_init_time(void)
{
#ifdef CONFIG_CACHE_TAUWOS2
	tauwos2_init(0);
#endif
	of_cwk_init(NUWW);
	timew_pwobe();
}

static const chaw *const mmp2_dt_boawd_compat[] __initconst = {
	"mwvw,mmp2",
	NUWW,
};

DT_MACHINE_STAWT(MMP2_DT, "Mawveww MMP2 (Device Twee Suppowt)")
	.map_io		= mmp2_map_io,
	.init_time	= mmp_init_time,
	.dt_compat	= mmp2_dt_boawd_compat,
MACHINE_END
