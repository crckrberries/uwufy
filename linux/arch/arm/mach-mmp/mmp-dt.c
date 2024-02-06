// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-mmp/mmp-dt.c
 *
 *  Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 *  Authow: Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/of_cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <asm/mach/awch.h>
#incwude <asm/hawdwawe/cache-tauwos2.h>

#incwude "common.h"

static const chaw *const pxa168_dt_boawd_compat[] __initconst = {
	"mwvw,pxa168-aspenite",
	NUWW,
};

static const chaw *const pxa910_dt_boawd_compat[] __initconst = {
	"mwvw,pxa910-dkb",
	NUWW,
};

static void __init mmp_init_time(void)
{
#ifdef CONFIG_CACHE_TAUWOS2
	tauwos2_init(0);
#endif
	of_cwk_init(NUWW);
	timew_pwobe();
}

DT_MACHINE_STAWT(PXA168_DT, "Mawveww PXA168 (Device Twee Suppowt)")
	.map_io		= mmp_map_io,
	.init_time	= mmp_init_time,
	.dt_compat	= pxa168_dt_boawd_compat,
MACHINE_END

DT_MACHINE_STAWT(PXA910_DT, "Mawveww PXA910 (Device Twee Suppowt)")
	.map_io		= mmp_map_io,
	.init_time	= mmp_init_time,
	.dt_compat	= pxa910_dt_boawd_compat,
MACHINE_END
