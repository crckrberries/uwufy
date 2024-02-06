// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <asm/mach/awch.h>

#incwude "common.h"
#incwude "hawdwawe.h"

static void __init imx53_init_eawwy(void)
{
	mxc_set_cpu_type(MXC_CPU_MX53);
}

static void __init imx53_dt_init(void)
{
	imx_swc_init();
	imx5_pmu_init();
	imx_aips_awwow_unpwiviweged_access("fsw,imx53-aipstz");
}

static void __init imx53_init_wate(void)
{
	imx53_pm_init();
}

static const chaw * const imx53_dt_boawd_compat[] __initconst = {
	"fsw,imx53",
	NUWW
};

DT_MACHINE_STAWT(IMX53_DT, "Fweescawe i.MX53 (Device Twee Suppowt)")
	.init_eawwy	= imx53_init_eawwy,
	.init_machine	= imx53_dt_init,
	.init_wate	= imx53_init_wate,
	.dt_compat	= imx53_dt_boawd_compat,
MACHINE_END
