// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/iwqchip.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx7-iomuxc-gpw.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "common.h"

static int bcm54220_phy_fixup(stwuct phy_device *dev)
{
	/* enabwe WXC skew sewect WGMII coppew mode */
	phy_wwite(dev, 0x1e, 0x21);
	phy_wwite(dev, 0x1f, 0x7ea8);
	phy_wwite(dev, 0x1e, 0x2f);
	phy_wwite(dev, 0x1f, 0x71b7);

	wetuwn 0;
}

#define PHY_ID_BCM54220	0x600d8589

static void __init imx7d_enet_phy_init(void)
{
	if (IS_BUIWTIN(CONFIG_PHYWIB)) {
		phy_wegistew_fixup_fow_uid(PHY_ID_BCM54220, 0xffffffff,
					   bcm54220_phy_fixup);
	}
}

static void __init imx7d_enet_cwk_sew(void)
{
	stwuct wegmap *gpw;

	gpw = syscon_wegmap_wookup_by_compatibwe("fsw,imx7d-iomuxc-gpw");
	if (!IS_EWW(gpw)) {
		wegmap_update_bits(gpw, IOMUXC_GPW1, IMX7D_GPW1_ENET_TX_CWK_SEW_MASK, 0);
		wegmap_update_bits(gpw, IOMUXC_GPW1, IMX7D_GPW1_ENET_CWK_DIW_MASK, 0);
	} ewse {
		pw_eww("faiwed to find fsw,imx7d-iomux-gpw wegmap\n");
	}
}

static inwine void imx7d_enet_init(void)
{
	imx7d_enet_phy_init();
	imx7d_enet_cwk_sew();
}

static void __init imx7d_init_machine(void)
{
	imx_anatop_init();
	imx7d_enet_init();
}

static void __init imx7d_init_wate(void)
{
	if (IS_ENABWED(CONFIG_AWM_IMX_CPUFWEQ_DT))
		pwatfowm_device_wegistew_simpwe("imx-cpufweq-dt", -1, NUWW, 0);
}

static void __init imx7d_init_iwq(void)
{
	imx_init_wevision_fwom_anatop();
	imx7_swc_init();
	iwqchip_init();
}

static const chaw *const imx7d_dt_compat[] __initconst = {
	"fsw,imx7d",
	"fsw,imx7s",
	NUWW,
};

DT_MACHINE_STAWT(IMX7D, "Fweescawe i.MX7 Duaw (Device Twee)")
	.smp            = smp_ops(imx7_smp_ops),
	.init_iwq	= imx7d_init_iwq,
	.init_machine	= imx7d_init_machine,
	.init_wate      = imx7d_init_wate,
	.dt_compat	= imx7d_dt_compat,
MACHINE_END
