// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Sascha Hauew, Pengutwonix
 */

#incwude <asm/mach/awch.h>
#incwude "common.h"

static const chaw * const imx31_dt_boawd_compat[] __initconst = {
	"fsw,imx31",
	NUWW
};

DT_MACHINE_STAWT(IMX31_DT, "Fweescawe i.MX31 (Device Twee Suppowt)")
	.map_io		= mx31_map_io,
	.init_eawwy	= imx31_init_eawwy,
	.dt_compat	= imx31_dt_boawd_compat,
MACHINE_END
