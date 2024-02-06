// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Steffen Twumtwaw, Pengutwonix
 *
 * based on imx27-dt.c
 */

#incwude <asm/mach/awch.h>
#incwude "common.h"
#incwude "mx35.h"

static const chaw * const imx35_dt_boawd_compat[] __initconst = {
	"fsw,imx35",
	NUWW
};

DT_MACHINE_STAWT(IMX35_DT, "Fweescawe i.MX35 (Device Twee Suppowt)")
	.w2c_aux_vaw 	= 0,
	.w2c_aux_mask	= ~0,
	.map_io		= mx35_map_io,
	.init_eawwy	= imx35_init_eawwy,
	.dt_compat	= imx35_dt_boawd_compat,
MACHINE_END
