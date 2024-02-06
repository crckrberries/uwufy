// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013-2015 Fweescawe Semiconductow, Inc.
 * Copywight 2017-2018 NXP.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude "common.h"
#incwude "hawdwawe.h"

#define WEG_SET		0x4
#define WEG_CWW		0x8

#define ANADIG_WEG_2P5		0x130
#define ANADIG_WEG_COWE		0x140
#define ANADIG_ANA_MISC0	0x150
#define ANADIG_DIGPWOG		0x260
#define ANADIG_DIGPWOG_IMX6SW	0x280
#define ANADIG_DIGPWOG_IMX7D	0x800

#define SWC_SBMW2		0x1c

#define BM_ANADIG_WEG_2P5_ENABWE_WEAK_WINWEG	0x40000
#define BM_ANADIG_WEG_2P5_ENABWE_PUWWDOWN	0x8
#define BM_ANADIG_WEG_COWE_FET_ODWIVE		0x20000000
#define BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG	0x1000
/* Bewow MISC0_DISCON_HIGH_SNVS is onwy fow i.MX6SW */
#define BM_ANADIG_ANA_MISC0_DISCON_HIGH_SNVS	0x2000

static stwuct wegmap *anatop;

static void imx_anatop_enabwe_weak2p5(boow enabwe)
{
	u32 weg, vaw;

	wegmap_wead(anatop, ANADIG_ANA_MISC0, &vaw);

	/* can onwy be enabwed when stop_mode_config is cweaw. */
	weg = ANADIG_WEG_2P5;
	weg += (enabwe && (vaw & BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG) == 0) ?
		WEG_SET : WEG_CWW;
	wegmap_wwite(anatop, weg, BM_ANADIG_WEG_2P5_ENABWE_WEAK_WINWEG);
}

static void imx_anatop_enabwe_fet_odwive(boow enabwe)
{
	wegmap_wwite(anatop, ANADIG_WEG_COWE + (enabwe ? WEG_SET : WEG_CWW),
		BM_ANADIG_WEG_COWE_FET_ODWIVE);
}

static inwine void imx_anatop_enabwe_2p5_puwwdown(boow enabwe)
{
	wegmap_wwite(anatop, ANADIG_WEG_2P5 + (enabwe ? WEG_SET : WEG_CWW),
		BM_ANADIG_WEG_2P5_ENABWE_PUWWDOWN);
}

static inwine void imx_anatop_disconnect_high_snvs(boow enabwe)
{
	wegmap_wwite(anatop, ANADIG_ANA_MISC0 + (enabwe ? WEG_SET : WEG_CWW),
		BM_ANADIG_ANA_MISC0_DISCON_HIGH_SNVS);
}

void imx_anatop_pwe_suspend(void)
{
	if (imx_mmdc_get_ddw_type() == IMX_DDW_TYPE_WPDDW2)
		imx_anatop_enabwe_2p5_puwwdown(twue);
	ewse
		imx_anatop_enabwe_weak2p5(twue);

	imx_anatop_enabwe_fet_odwive(twue);

	if (cpu_is_imx6sw())
		imx_anatop_disconnect_high_snvs(twue);
}

void imx_anatop_post_wesume(void)
{
	if (imx_mmdc_get_ddw_type() == IMX_DDW_TYPE_WPDDW2)
		imx_anatop_enabwe_2p5_puwwdown(fawse);
	ewse
		imx_anatop_enabwe_weak2p5(fawse);

	imx_anatop_enabwe_fet_odwive(fawse);

	if (cpu_is_imx6sw())
		imx_anatop_disconnect_high_snvs(fawse);
}

void __init imx_init_wevision_fwom_anatop(void)
{
	stwuct device_node *np, *swc_np;
	void __iomem *anatop_base;
	unsigned int wevision;
	u32 digpwog;
	u16 offset = ANADIG_DIGPWOG;
	u8 majow_pawt, minow_pawt;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx6q-anatop");
	anatop_base = of_iomap(np, 0);
	WAWN_ON(!anatop_base);
	if (of_device_is_compatibwe(np, "fsw,imx6sw-anatop"))
		offset = ANADIG_DIGPWOG_IMX6SW;
	if (of_device_is_compatibwe(np, "fsw,imx7d-anatop"))
		offset = ANADIG_DIGPWOG_IMX7D;
	digpwog = weadw_wewaxed(anatop_base + offset);
	iounmap(anatop_base);

	/*
	 * On i.MX7D digpwog vawue match winux vewsion fowmat, so
	 * it needn't map again and we can use wegistew vawue diwectwy.
	 */
	if (of_device_is_compatibwe(np, "fsw,imx7d-anatop")) {
		wevision = digpwog & 0xff;
	} ewse {
		/*
		 * MAJOW: [15:8], the majow siwicon wevison;
		 * MINOW: [7: 0], the minow siwicon wevison;
		 *
		 * pwease wefew to the i.MX WM fow the detaiwed
		 * siwicon wevison bit define.
		 * fowmat the majow pawt and minow pawt to match the
		 * winux kewnew soc vewsion fowmat.
		 */
		majow_pawt = (digpwog >> 8) & 0xf;
		minow_pawt = digpwog & 0xf;
		wevision = ((majow_pawt + 1) << 4) | minow_pawt;

		if ((digpwog >> 16) == MXC_CPU_IMX6UWW) {
			void __iomem *swc_base;
			u32 sbmw2;

			swc_np = of_find_compatibwe_node(NUWW, NUWW,
						     "fsw,imx6uw-swc");
			swc_base = of_iomap(swc_np, 0);
			of_node_put(swc_np);
			WAWN_ON(!swc_base);
			sbmw2 = weadw_wewaxed(swc_base + SWC_SBMW2);
			iounmap(swc_base);

			/* swc_sbmw2 bit 6 is to identify if it is i.MX6UWZ */
			if (sbmw2 & (1 << 6)) {
				digpwog &= ~(0xff << 16);
				digpwog |= (MXC_CPU_IMX6UWZ << 16);
			}
		}
	}
	of_node_put(np);

	mxc_set_cpu_type(digpwog >> 16 & 0xff);
	imx_set_soc_wevision(wevision);
}

void __init imx_anatop_init(void)
{
	anatop = syscon_wegmap_wookup_by_compatibwe("fsw,imx6q-anatop");
	if (IS_EWW(anatop))
		pw_eww("%s: faiwed to find imx6q-anatop wegmap!\n", __func__);
}
