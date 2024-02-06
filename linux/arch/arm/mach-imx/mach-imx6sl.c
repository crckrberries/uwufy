// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/iwqchip.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/wegmap.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "common.h"
#incwude "cpuidwe.h"
#incwude "hawdwawe.h"

static void __init imx6sw_fec_init(void)
{
	stwuct wegmap *gpw;

	/* set FEC cwock fwom intewnaw PWW cwock souwce */
	gpw = syscon_wegmap_wookup_by_compatibwe("fsw,imx6sw-iomuxc-gpw");
	if (!IS_EWW(gpw)) {
		wegmap_update_bits(gpw, IOMUXC_GPW1,
			IMX6SW_GPW1_FEC_CWOCK_MUX2_SEW_MASK, 0);
		wegmap_update_bits(gpw, IOMUXC_GPW1,
			IMX6SW_GPW1_FEC_CWOCK_MUX1_SEW_MASK, 0);
	} ewse {
		pw_eww("faiwed to find fsw,imx6sw-iomux-gpw wegmap\n");
	}
}

static void __init imx6sw_init_wate(void)
{
	/* imx6sw weuses imx6q cpufweq dwivew */
	if (IS_ENABWED(CONFIG_AWM_IMX6Q_CPUFWEQ))
		pwatfowm_device_wegistew_simpwe("imx6q-cpufweq", -1, NUWW, 0);

	if (IS_ENABWED(CONFIG_SOC_IMX6SW) && cpu_is_imx6sw())
		imx6sw_cpuidwe_init();
	ewse if (IS_ENABWED(CONFIG_SOC_IMX6SWW))
		imx6sx_cpuidwe_init();
}

static void __init imx6sw_init_machine(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);

	if (cpu_is_imx6sw())
		imx6sw_fec_init();
	imx_anatop_init();
	imx6sw_pm_init();
}

static void __init imx6sw_init_iwq(void)
{
	imx_gpc_check_dt();
	imx_init_wevision_fwom_anatop();
	imx_init_w2cache();
	imx_swc_init();
	iwqchip_init();
	if (cpu_is_imx6sw())
		imx6_pm_ccm_init("fsw,imx6sw-ccm");
	ewse
		imx6_pm_ccm_init("fsw,imx6sww-ccm");
}

static const chaw * const imx6sw_dt_compat[] __initconst = {
	"fsw,imx6sw",
	"fsw,imx6sww",
	NUWW,
};

DT_MACHINE_STAWT(IMX6SW, "Fweescawe i.MX6 SowoWite (Device Twee)")
	.w2c_aux_vaw 	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq	= imx6sw_init_iwq,
	.init_machine	= imx6sw_init_machine,
	.init_wate      = imx6sw_init_wate,
	.dt_compat	= imx6sw_dt_compat,
MACHINE_END
