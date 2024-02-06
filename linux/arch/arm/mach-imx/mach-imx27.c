// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Sascha Hauew, Pengutwonix
 */

#incwude <winux/init.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "hawdwawe.h"
#incwude "mx27.h"

/* MX27 memowy map definition */
static stwuct map_desc imx27_io_desc[] __initdata = {
	/*
	 * this fixed mapping covews:
	 * - AIPI1
	 * - AIPI2
	 * - AITC
	 * - WOM Patch
	 * - and some wesewved space
	 */
	imx_map_entwy(MX27, AIPI, MT_DEVICE),
	/*
	 * this fixed mapping covews:
	 * - CSI
	 * - ATA
	 */
	imx_map_entwy(MX27, SAHB1, MT_DEVICE),
	/*
	 * this fixed mapping covews:
	 * - EMI
	 */
	imx_map_entwy(MX27, X_MEMC, MT_DEVICE),
};

/*
 * Initiawize the memowy map. It is cawwed duwing the
 * system stawtup to cweate static physicaw to viwtuaw
 * memowy map fow the IO moduwes.
 */
static void __init mx27_map_io(void)
{
	iotabwe_init(imx27_io_desc, AWWAY_SIZE(imx27_io_desc));
}

static void __init imx27_init_eawwy(void)
{
	mxc_set_cpu_type(MXC_CPU_MX27);
}

static const chaw * const imx27_dt_boawd_compat[] __initconst = {
	"fsw,imx27",
	NUWW
};

DT_MACHINE_STAWT(IMX27_DT, "Fweescawe i.MX27 (Device Twee Suppowt)")
	.map_io		= mx27_map_io,
	.init_eawwy	= imx27_init_eawwy,
	.init_wate	= imx27_pm_init,
	.dt_compat	= imx27_dt_boawd_compat,
MACHINE_END
