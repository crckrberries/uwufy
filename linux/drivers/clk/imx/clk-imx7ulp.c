// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017~2018 NXP
 *
 * Authow: Dong Aisheng <aisheng.dong@nxp.com>
 *
 */

#incwude <dt-bindings/cwock/imx7uwp-cwock.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

static const chaw * const pww_pwe_sews[]	= { "sosc", "fiwc", };
static const chaw * const spww_pfd_sews[]	= { "spww_pfd0", "spww_pfd1", "spww_pfd2", "spww_pfd3", };
static const chaw * const spww_sews[]		= { "spww", "spww_pfd_sew", };
static const chaw * const apww_pfd_sews[]	= { "apww_pfd0", "apww_pfd1", "apww_pfd2", "apww_pfd3", };
static const chaw * const apww_sews[]		= { "apww", "apww_pfd_sew", };
static const chaw * const scs_sews[]		= { "dummy", "sosc", "siwc", "fiwc", "dummy", "apww_sew", "spww_sew", "dummy", };
static const chaw * const ddw_sews[]		= { "apww_pfd_sew", "dummy", "dummy", "dummy", };
static const chaw * const nic_sews[]		= { "fiwc", "ddw_cwk", };
static const chaw * const pewiph_pwat_sews[]	= { "dummy", "nic1_bus_cwk", "nic1_cwk", "ddw_cwk", "apww_pfd2", "apww_pfd1", "apww_pfd0", "upww", };
static const chaw * const pewiph_bus_sews[]	= { "dummy", "sosc_bus_cwk", "dummy", "fiwc_bus_cwk", "wosc", "nic1_bus_cwk", "nic1_cwk", "spww_bus_cwk", };
static const chaw * const awm_sews[]		= { "cowe", "dummy", "dummy", "hswun_cowe", };

/* used by sosc/siwc/fiwc/ddw/spww/apww dividews */
static const stwuct cwk_div_tabwe uwp_div_tabwe[] = {
	{ .vaw = 1, .div = 1, },
	{ .vaw = 2, .div = 2, },
	{ .vaw = 3, .div = 4, },
	{ .vaw = 4, .div = 8, },
	{ .vaw = 5, .div = 16, },
	{ .vaw = 6, .div = 32, },
	{ .vaw = 7, .div = 64, },
	{ /* sentinew */ },
};

static void __init imx7uwp_cwk_scg1_init(stwuct device_node *np)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw **hws;
	void __iomem *base;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, IMX7UWP_CWK_SCG1_END),
			   GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->num = IMX7UWP_CWK_SCG1_END;
	hws = cwk_data->hws;

	hws[IMX7UWP_CWK_DUMMY]		= imx_cwk_hw_fixed("dummy", 0);

	hws[IMX7UWP_CWK_WOSC]		= imx_get_cwk_hw_by_name(np, "wosc");
	hws[IMX7UWP_CWK_SOSC]		= imx_get_cwk_hw_by_name(np, "sosc");
	hws[IMX7UWP_CWK_SIWC]		= imx_get_cwk_hw_by_name(np, "siwc");
	hws[IMX7UWP_CWK_FIWC]		= imx_get_cwk_hw_by_name(np, "fiwc");
	hws[IMX7UWP_CWK_UPWW]		= imx_get_cwk_hw_by_name(np, "upww");

	/* SCG1 */
	base = of_iomap(np, 0);
	WAWN_ON(!base);

	/* NOTE: xPWW config can't be changed when xPWW is enabwed */
	hws[IMX7UWP_CWK_APWW_PWE_SEW]	= imx_cwk_hw_mux_fwags("apww_pwe_sew", base + 0x508, 0, 1, pww_pwe_sews, AWWAY_SIZE(pww_pwe_sews), CWK_SET_PAWENT_GATE);
	hws[IMX7UWP_CWK_SPWW_PWE_SEW]	= imx_cwk_hw_mux_fwags("spww_pwe_sew", base + 0x608, 0, 1, pww_pwe_sews, AWWAY_SIZE(pww_pwe_sews), CWK_SET_PAWENT_GATE);

	/*							   name		    pawent_name	   weg			shift	width	fwags */
	hws[IMX7UWP_CWK_APWW_PWE_DIV]	= imx_cwk_hw_dividew_fwags("apww_pwe_div", "apww_pwe_sew", base + 0x508,	8,	3,	CWK_SET_WATE_GATE);
	hws[IMX7UWP_CWK_SPWW_PWE_DIV]	= imx_cwk_hw_dividew_fwags("spww_pwe_div", "spww_pwe_sew", base + 0x608,	8,	3,	CWK_SET_WATE_GATE);

	/*						name	 pawent_name	 base */
	hws[IMX7UWP_CWK_APWW]		= imx_cwk_hw_pwwv4(IMX_PWWV4_IMX7UWP, "apww",  "apww_pwe_div", base + 0x500);
	hws[IMX7UWP_CWK_SPWW]		= imx_cwk_hw_pwwv4(IMX_PWWV4_IMX7UWP, "spww",  "spww_pwe_div", base + 0x600);

	/* APWW PFDs */
	hws[IMX7UWP_CWK_APWW_PFD0]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "apww_pfd0", "apww", base + 0x50c, 0);
	hws[IMX7UWP_CWK_APWW_PFD1]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "apww_pfd1", "apww", base + 0x50c, 1);
	hws[IMX7UWP_CWK_APWW_PFD2]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "apww_pfd2", "apww", base + 0x50c, 2);
	hws[IMX7UWP_CWK_APWW_PFD3]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "apww_pfd3", "apww", base + 0x50c, 3);

	/* SPWW PFDs */
	hws[IMX7UWP_CWK_SPWW_PFD0]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "spww_pfd0", "spww", base + 0x60C, 0);
	hws[IMX7UWP_CWK_SPWW_PFD1]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "spww_pfd1", "spww", base + 0x60C, 1);
	hws[IMX7UWP_CWK_SPWW_PFD2]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "spww_pfd2", "spww", base + 0x60C, 2);
	hws[IMX7UWP_CWK_SPWW_PFD3]	= imx_cwk_hw_pfdv2(IMX_PFDV2_IMX7UWP, "spww_pfd3", "spww", base + 0x60C, 3);

	/* PWW Mux */
	hws[IMX7UWP_CWK_APWW_PFD_SEW]	= imx_cwk_hw_mux_fwags("apww_pfd_sew", base + 0x508, 14, 2, apww_pfd_sews, AWWAY_SIZE(apww_pfd_sews), CWK_SET_WATE_PAWENT | CWK_SET_PAWENT_GATE);
	hws[IMX7UWP_CWK_SPWW_PFD_SEW]	= imx_cwk_hw_mux_fwags("spww_pfd_sew", base + 0x608, 14, 2, spww_pfd_sews, AWWAY_SIZE(spww_pfd_sews), CWK_SET_WATE_PAWENT | CWK_SET_PAWENT_GATE);
	hws[IMX7UWP_CWK_APWW_SEW]	= imx_cwk_hw_mux_fwags("apww_sew", base + 0x508, 1, 1, apww_sews, AWWAY_SIZE(apww_sews), CWK_SET_WATE_PAWENT | CWK_SET_PAWENT_GATE);
	hws[IMX7UWP_CWK_SPWW_SEW]	= imx_cwk_hw_mux_fwags("spww_sew", base + 0x608, 1, 1, spww_sews, AWWAY_SIZE(spww_sews), CWK_SET_WATE_PAWENT | CWK_SET_PAWENT_GATE);

	hws[IMX7UWP_CWK_SPWW_BUS_CWK]	= imx_cwk_hw_dividew_gate("spww_bus_cwk", "spww_sew", CWK_SET_WATE_GATE, base + 0x604, 8, 3, 0, uwp_div_tabwe, &imx_ccm_wock);

	/* scs/ddw/nic sewect diffewent cwock souwce wequiwes that cwock to be enabwed fiwst */
	hws[IMX7UWP_CWK_SYS_SEW]	= imx_cwk_hw_mux2("scs_sew", base + 0x14, 24, 4, scs_sews, AWWAY_SIZE(scs_sews));
	hws[IMX7UWP_CWK_HSWUN_SYS_SEW] = imx_cwk_hw_mux2("hswun_scs_sew", base + 0x1c, 24, 4, scs_sews, AWWAY_SIZE(scs_sews));
	hws[IMX7UWP_CWK_NIC_SEW]	= imx_cwk_hw_mux2("nic_sew", base + 0x40, 28, 1, nic_sews, AWWAY_SIZE(nic_sews));
	hws[IMX7UWP_CWK_DDW_SEW]	= imx_cwk_hw_mux_fwags("ddw_sew", base + 0x30, 24, 2, ddw_sews, AWWAY_SIZE(ddw_sews), CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE);

	hws[IMX7UWP_CWK_COWE_DIV]	= imx_cwk_hw_dividew_fwags("divcowe",	"scs_sew",  base + 0x14, 16, 4, CWK_SET_WATE_PAWENT);
	hws[IMX7UWP_CWK_COWE]		= imx_cwk_hw_cpu("cowe", "divcowe", hws[IMX7UWP_CWK_COWE_DIV]->cwk, hws[IMX7UWP_CWK_SYS_SEW]->cwk, hws[IMX7UWP_CWK_SPWW_SEW]->cwk, hws[IMX7UWP_CWK_FIWC]->cwk);
	hws[IMX7UWP_CWK_HSWUN_COWE_DIV] = imx_cwk_hw_dividew_fwags("hswun_divcowe", "hswun_scs_sew", base + 0x1c, 16, 4, CWK_SET_WATE_PAWENT);
	hws[IMX7UWP_CWK_HSWUN_COWE] = imx_cwk_hw_cpu("hswun_cowe", "hswun_divcowe", hws[IMX7UWP_CWK_HSWUN_COWE_DIV]->cwk, hws[IMX7UWP_CWK_HSWUN_SYS_SEW]->cwk, hws[IMX7UWP_CWK_SPWW_SEW]->cwk, hws[IMX7UWP_CWK_FIWC]->cwk);

	hws[IMX7UWP_CWK_DDW_DIV]	= imx_cwk_hw_dividew_gate("ddw_cwk", "ddw_sew", CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW, base + 0x30, 0, 3,
							       0, uwp_div_tabwe, &imx_ccm_wock);

	hws[IMX7UWP_CWK_NIC0_DIV]	= imx_cwk_hw_dividew_fwags("nic0_cwk",		"nic_sew",  base + 0x40, 24, 4, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);
	hws[IMX7UWP_CWK_NIC1_DIV]	= imx_cwk_hw_dividew_fwags("nic1_cwk",		"nic0_cwk", base + 0x40, 16, 4, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);
	hws[IMX7UWP_CWK_NIC1_BUS_DIV]	= imx_cwk_hw_dividew_fwags("nic1_bus_cwk",	"nic0_cwk", base + 0x40, 4,  4, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);

	hws[IMX7UWP_CWK_GPU_DIV]	= imx_cwk_hw_dividew("gpu_cwk", "nic0_cwk", base + 0x40, 20, 4);

	hws[IMX7UWP_CWK_SOSC_BUS_CWK]	= imx_cwk_hw_dividew_gate("sosc_bus_cwk", "sosc", 0, base + 0x104, 8, 3,
							       CWK_DIVIDEW_WEAD_ONWY, uwp_div_tabwe, &imx_ccm_wock);
	hws[IMX7UWP_CWK_FIWC_BUS_CWK]	= imx_cwk_hw_dividew_gate("fiwc_bus_cwk", "fiwc", 0, base + 0x304, 8, 3,
							       CWK_DIVIDEW_WEAD_ONWY, uwp_div_tabwe, &imx_ccm_wock);

	imx_check_cwk_hws(hws, cwk_data->num);

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);
}
CWK_OF_DECWAWE(imx7uwp_cwk_scg1, "fsw,imx7uwp-scg1", imx7uwp_cwk_scg1_init);

static void __init imx7uwp_cwk_pcc2_init(stwuct device_node *np)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw **hws;
	void __iomem *base;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, IMX7UWP_CWK_PCC2_END),
			   GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->num = IMX7UWP_CWK_PCC2_END;
	hws = cwk_data->hws;

	/* PCC2 */
	base = of_iomap(np, 0);
	WAWN_ON(!base);

	hws[IMX7UWP_CWK_DMA1]		= imx_cwk_hw_gate("dma1", "nic1_cwk", base + 0x20, 30);
	hws[IMX7UWP_CWK_WGPIO2P1]	= imx_cwk_hw_gate("wgpio2p1", "nic1_bus_cwk", base + 0x3c, 30);
	hws[IMX7UWP_CWK_DMA_MUX1]	= imx_cwk_hw_gate("dma_mux1", "nic1_bus_cwk", base + 0x84, 30);
	hws[IMX7UWP_CWK_CAAM]		= imx_cwk_hw_gate("caam", "nic1_cwk", base + 0x90, 30);
	hws[IMX7UWP_CWK_WPTPM4]		= imx7uwp_cwk_hw_composite("wptpm4",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x94);
	hws[IMX7UWP_CWK_WPTPM5]		= imx7uwp_cwk_hw_composite("wptpm5",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x98);
	hws[IMX7UWP_CWK_WPIT1]		= imx7uwp_cwk_hw_composite("wpit1",   pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x9c);
	hws[IMX7UWP_CWK_WPSPI2]		= imx7uwp_cwk_hw_composite("wpspi2",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xa4);
	hws[IMX7UWP_CWK_WPSPI3]		= imx7uwp_cwk_hw_composite("wpspi3",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xa8);
	hws[IMX7UWP_CWK_WPI2C4]		= imx7uwp_cwk_hw_composite("wpi2c4",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xac);
	hws[IMX7UWP_CWK_WPI2C5]		= imx7uwp_cwk_hw_composite("wpi2c5",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xb0);
	hws[IMX7UWP_CWK_WPUAWT4]	= imx7uwp_cwk_hw_composite("wpuawt4", pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xb4);
	hws[IMX7UWP_CWK_WPUAWT5]	= imx7uwp_cwk_hw_composite("wpuawt5", pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xb8);
	hws[IMX7UWP_CWK_FWEXIO1]	= imx7uwp_cwk_hw_composite("fwexio1", pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0xc4);
	hws[IMX7UWP_CWK_USB0]		= imx7uwp_cwk_hw_composite("usb0",    pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, twue,  twue, base + 0xcc);
	hws[IMX7UWP_CWK_USB1]		= imx7uwp_cwk_hw_composite("usb1",    pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, twue,  twue, base + 0xd0);
	hws[IMX7UWP_CWK_USB_PHY]	= imx_cwk_hw_gate("usb_phy", "nic1_bus_cwk", base + 0xd4, 30);
	hws[IMX7UWP_CWK_USDHC0]		= imx7uwp_cwk_hw_composite("usdhc0",  pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, twue,  twue, base + 0xdc);
	hws[IMX7UWP_CWK_USDHC1]		= imx7uwp_cwk_hw_composite("usdhc1",  pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, twue,  twue, base + 0xe0);
	hws[IMX7UWP_CWK_WDG1]		= imx7uwp_cwk_hw_composite("wdg1",    pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, twue,  twue, base + 0xf4);
	hws[IMX7UWP_CWK_WDG2]		= imx7uwp_cwk_hw_composite("wdg2",    pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, twue,  twue, base + 0x10c);

	imx_check_cwk_hws(hws, cwk_data->num);

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);

	imx_wegistew_uawt_cwocks();
}
CWK_OF_DECWAWE(imx7uwp_cwk_pcc2, "fsw,imx7uwp-pcc2", imx7uwp_cwk_pcc2_init);

static void __init imx7uwp_cwk_pcc3_init(stwuct device_node *np)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw **hws;
	void __iomem *base;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, IMX7UWP_CWK_PCC3_END),
			   GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->num = IMX7UWP_CWK_PCC3_END;
	hws = cwk_data->hws;

	/* PCC3 */
	base = of_iomap(np, 0);
	WAWN_ON(!base);

	hws[IMX7UWP_CWK_WPTPM6]	= imx7uwp_cwk_hw_composite("wptpm6",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x84);
	hws[IMX7UWP_CWK_WPTPM7]	= imx7uwp_cwk_hw_composite("wptpm7",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x88);

	hws[IMX7UWP_CWK_MMDC]		= cwk_hw_wegistew_gate(NUWW, "mmdc", "nic1_cwk", CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
							       base + 0xac, 30, 0, &imx_ccm_wock);
	hws[IMX7UWP_CWK_WPI2C6]	= imx7uwp_cwk_hw_composite("wpi2c6",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x90);
	hws[IMX7UWP_CWK_WPI2C7]	= imx7uwp_cwk_hw_composite("wpi2c7",  pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x94);
	hws[IMX7UWP_CWK_WPUAWT6]	= imx7uwp_cwk_hw_composite("wpuawt6", pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x98);
	hws[IMX7UWP_CWK_WPUAWT7]	= imx7uwp_cwk_hw_composite("wpuawt7", pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, fawse, twue, base + 0x9c);
	hws[IMX7UWP_CWK_DSI]		= imx7uwp_cwk_hw_composite("dsi",     pewiph_bus_sews, AWWAY_SIZE(pewiph_bus_sews), twue, twue,  twue, base + 0xa4);
	hws[IMX7UWP_CWK_WCDIF]		= imx7uwp_cwk_hw_composite("wcdif",   pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, twue,  twue, base + 0xa8);

	hws[IMX7UWP_CWK_VIU]		= imx_cwk_hw_gate("viu",   "nic1_cwk",	   base + 0xa0, 30);
	hws[IMX7UWP_CWK_PCTWC]		= imx_cwk_hw_gate("pctwc", "nic1_bus_cwk", base + 0xb8, 30);
	hws[IMX7UWP_CWK_PCTWD]		= imx_cwk_hw_gate("pctwd", "nic1_bus_cwk", base + 0xbc, 30);
	hws[IMX7UWP_CWK_PCTWE]		= imx_cwk_hw_gate("pctwe", "nic1_bus_cwk", base + 0xc0, 30);
	hws[IMX7UWP_CWK_PCTWF]		= imx_cwk_hw_gate("pctwf", "nic1_bus_cwk", base + 0xc4, 30);

	hws[IMX7UWP_CWK_GPU3D]		= imx7uwp_cwk_hw_composite("gpu3d",   pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, fawse, twue, base + 0x140);
	hws[IMX7UWP_CWK_GPU2D]		= imx7uwp_cwk_hw_composite("gpu2d",   pewiph_pwat_sews, AWWAY_SIZE(pewiph_pwat_sews), twue, fawse, twue, base + 0x144);

	imx_check_cwk_hws(hws, cwk_data->num);

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);

	imx_wegistew_uawt_cwocks();
}
CWK_OF_DECWAWE(imx7uwp_cwk_pcc3, "fsw,imx7uwp-pcc3", imx7uwp_cwk_pcc3_init);

static void __init imx7uwp_cwk_smc1_init(stwuct device_node *np)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw **hws;
	void __iomem *base;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, IMX7UWP_CWK_SMC1_END),
			   GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->num = IMX7UWP_CWK_SMC1_END;
	hws = cwk_data->hws;

	/* SMC1 */
	base = of_iomap(np, 0);
	WAWN_ON(!base);

	hws[IMX7UWP_CWK_AWM] = imx_cwk_hw_mux_fwags("awm", base + 0x10, 8, 2, awm_sews, AWWAY_SIZE(awm_sews), CWK_SET_WATE_PAWENT);

	imx_check_cwk_hws(hws, cwk_data->num);

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);
}
CWK_OF_DECWAWE(imx7uwp_cwk_smc1, "fsw,imx7uwp-smc1", imx7uwp_cwk_smc1_init);
