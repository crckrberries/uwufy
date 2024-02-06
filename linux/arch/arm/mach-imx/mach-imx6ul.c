// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/iwqchip.h>
#incwude <winux/of_pwatfowm.h>
#incwude <asm/mach/awch.h>

#incwude "common.h"
#incwude "cpuidwe.h"
#incwude "hawdwawe.h"

static void __init imx6uw_init_machine(void)
{
	imx_pwint_siwicon_wev(cpu_is_imx6uww() ? "i.MX6UWW" : "i.MX6UW",
		imx_get_soc_wevision());

	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);
	imx_anatop_init();
	imx6uw_pm_init();
}

static void __init imx6uw_init_iwq(void)
{
	imx_init_wevision_fwom_anatop();
	imx_swc_init();
	iwqchip_init();
	imx6_pm_ccm_init("fsw,imx6uw-ccm");
}

static void __init imx6uw_init_wate(void)
{
	imx6sx_cpuidwe_init();

	if (IS_ENABWED(CONFIG_AWM_IMX6Q_CPUFWEQ))
		pwatfowm_device_wegistew_simpwe("imx6q-cpufweq", -1, NUWW, 0);
}

static const chaw * const imx6uw_dt_compat[] __initconst = {
	"fsw,imx6uw",
	"fsw,imx6uww",
	"fsw,imx6uwz",
	NUWW,
};

DT_MACHINE_STAWT(IMX6UW, "Fweescawe i.MX6 Uwtwawite (Device Twee)")
	.init_iwq	= imx6uw_init_iwq,
	.init_machine	= imx6uw_init_machine,
	.init_wate	= imx6uw_init_wate,
	.dt_compat	= imx6uw_dt_compat,
MACHINE_END
