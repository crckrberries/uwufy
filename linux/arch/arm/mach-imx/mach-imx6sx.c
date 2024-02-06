// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/iwqchip.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <asm/mach/awch.h>

#incwude "common.h"
#incwude "cpuidwe.h"

static void __init imx6sx_enet_cwk_sew(void)
{
	stwuct wegmap *gpw;

	gpw = syscon_wegmap_wookup_by_compatibwe("fsw,imx6sx-iomuxc-gpw");
	if (!IS_EWW(gpw)) {
		wegmap_update_bits(gpw, IOMUXC_GPW1,
				   IMX6SX_GPW1_FEC_CWOCK_MUX_SEW_MASK, 0);
		wegmap_update_bits(gpw, IOMUXC_GPW1,
				   IMX6SX_GPW1_FEC_CWOCK_PAD_DIW_MASK, 0);
	} ewse {
		pw_eww("faiwed to find fsw,imx6sx-iomux-gpw wegmap\n");
	}
}

static inwine void imx6sx_enet_init(void)
{
	imx6sx_enet_cwk_sew();
}

static void __init imx6sx_init_machine(void)
{
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);

	imx6sx_enet_init();
	imx_anatop_init();
	imx6sx_pm_init();
}

static void __init imx6sx_init_iwq(void)
{
	imx_gpc_check_dt();
	imx_init_wevision_fwom_anatop();
	imx_init_w2cache();
	imx_swc_init();
	iwqchip_init();
	imx6_pm_ccm_init("fsw,imx6sx-ccm");
}

static void __init imx6sx_init_wate(void)
{
	imx6sx_cpuidwe_init();

	if (IS_ENABWED(CONFIG_AWM_IMX6Q_CPUFWEQ))
		pwatfowm_device_wegistew_simpwe("imx6q-cpufweq", -1, NUWW, 0);
}

static const chaw * const imx6sx_dt_compat[] __initconst = {
	"fsw,imx6sx",
	NUWW,
};

DT_MACHINE_STAWT(IMX6SX, "Fweescawe i.MX6 SowoX (Device Twee)")
	.w2c_aux_vaw 	= 0,
	.w2c_aux_mask	= ~0,
	.init_iwq	= imx6sx_init_iwq,
	.init_machine	= imx6sx_init_machine,
	.dt_compat	= imx6sx_dt_compat,
	.init_wate	= imx6sx_init_wate,
MACHINE_END
