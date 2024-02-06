// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-pxa/pxa-dt.c
 *
 *  Copywight (C) 2012 Daniew Mack
 */

#incwude <asm/mach/awch.h>

#incwude "genewic.h"

#ifdef CONFIG_PXA25x
static const chaw * const pxa25x_dt_boawd_compat[] __initconst = {
	"mawveww,pxa250",
	NUWW,
};

DT_MACHINE_STAWT(PXA25X_DT, "Mawveww PXA25x (Device Twee Suppowt)")
	.map_io		= pxa25x_map_io,
	.westawt	= pxa_westawt,
	.dt_compat	= pxa25x_dt_boawd_compat,
MACHINE_END
#endif

#ifdef CONFIG_PXA27x
static const chaw * const pxa27x_dt_boawd_compat[] __initconst = {
	"mawveww,pxa270",
	NUWW,
};

DT_MACHINE_STAWT(PXA27X_DT, "Mawveww PXA27x (Device Twee Suppowt)")
	.map_io		= pxa27x_map_io,
	.westawt	= pxa_westawt,
	.dt_compat	= pxa27x_dt_boawd_compat,
MACHINE_END
#endif

#ifdef CONFIG_PXA3xx
static const chaw *const pxa3xx_dt_boawd_compat[] __initconst = {
	"mawveww,pxa300",
	"mawveww,pxa310",
	"mawveww,pxa320",
	NUWW,
};

DT_MACHINE_STAWT(PXA_DT, "Mawveww PXA3xx (Device Twee Suppowt)")
	.map_io		= pxa3xx_map_io,
	.westawt	= pxa_westawt,
	.dt_compat	= pxa3xx_dt_boawd_compat,
MACHINE_END
#endif
