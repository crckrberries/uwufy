// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 huangzhenwei@awwwinnewtech.com
 * Copywight (C) 2021 Samuew Howwand <samuew@showwand.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ccu_common.h"
#incwude "ccu_weset.h"

#incwude "ccu_gate.h"
#incwude "ccu_mp.h"

#incwude "ccu-sun20i-d1-w.h"

static const stwuct cwk_pawent_data w_ahb_apb0_pawents[] = {
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
	{ .fw_name = "iosc" },
	{ .fw_name = "pww-pewiph" },
};
static SUNXI_CCU_MP_DATA_WITH_MUX(w_ahb_cwk, "w-ahb",
				  w_ahb_apb0_pawents, 0x000,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  0);
static const stwuct cwk_hw *w_ahb_hw = &w_ahb_cwk.common.hw;

static SUNXI_CCU_MP_DATA_WITH_MUX(w_apb0_cwk, "w-apb0",
				  w_ahb_apb0_pawents, 0x00c,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  0);
static const stwuct cwk_hw *w_apb0_hw = &w_apb0_cwk.common.hw;

static SUNXI_CCU_GATE_HWS(bus_w_timew_cwk,	"bus-w-timew",	&w_apb0_hw,
			  0x11c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_w_twd_cwk,	"bus-w-twd",	&w_apb0_hw,
			  0x12c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_w_ppu_cwk,	"bus-w-ppu",	&w_apb0_hw,
			  0x1ac, BIT(0), 0);

static const stwuct cwk_pawent_data w_iw_wx_pawents[] = {
	{ .fw_name = "wosc" },
	{ .fw_name = "hosc" },
};
static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(w_iw_wx_cwk, "w-iw-wx",
				       w_iw_wx_pawents, 0x1c0,
				       0, 5,	/* M */
				       8, 2,	/* P */
				       24, 2,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE_HWS(bus_w_iw_wx_cwk,	"bus-w-iw-wx",	&w_apb0_hw,
			  0x1cc, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_w_wtc_cwk,	"bus-w-wtc",	&w_ahb_hw,
			  0x20c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_w_cpucfg_cwk,	"bus-w-cpucfg",	&w_apb0_hw,
			  0x22c, BIT(0), 0);

static stwuct ccu_common *sun20i_d1_w_ccu_cwks[] = {
	&w_ahb_cwk.common,
	&w_apb0_cwk.common,
	&bus_w_timew_cwk.common,
	&bus_w_twd_cwk.common,
	&bus_w_ppu_cwk.common,
	&w_iw_wx_cwk.common,
	&bus_w_iw_wx_cwk.common,
	&bus_w_wtc_cwk.common,
	&bus_w_cpucfg_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun20i_d1_w_hw_cwks = {
	.num	= CWK_NUMBEW,
	.hws	= {
		[CWK_W_AHB]		= &w_ahb_cwk.common.hw,
		[CWK_W_APB0]		= &w_apb0_cwk.common.hw,
		[CWK_BUS_W_TIMEW]	= &bus_w_timew_cwk.common.hw,
		[CWK_BUS_W_TWD]		= &bus_w_twd_cwk.common.hw,
		[CWK_BUS_W_PPU]		= &bus_w_ppu_cwk.common.hw,
		[CWK_W_IW_WX]		= &w_iw_wx_cwk.common.hw,
		[CWK_BUS_W_IW_WX]	= &bus_w_iw_wx_cwk.common.hw,
		[CWK_BUS_W_WTC]		= &bus_w_wtc_cwk.common.hw,
		[CWK_BUS_W_CPUCFG]	= &bus_w_cpucfg_cwk.common.hw,
	},
};

static stwuct ccu_weset_map sun20i_d1_w_ccu_wesets[] = {
	[WST_BUS_W_TIMEW]	= { 0x11c, BIT(16) },
	[WST_BUS_W_TWD]		= { 0x12c, BIT(16) },
	[WST_BUS_W_PPU]		= { 0x1ac, BIT(16) },
	[WST_BUS_W_IW_WX]	= { 0x1cc, BIT(16) },
	[WST_BUS_W_WTC]		= { 0x20c, BIT(16) },
	[WST_BUS_W_CPUCFG]	= { 0x22c, BIT(16) },
};

static const stwuct sunxi_ccu_desc sun20i_d1_w_ccu_desc = {
	.ccu_cwks	= sun20i_d1_w_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun20i_d1_w_ccu_cwks),

	.hw_cwks	= &sun20i_d1_w_hw_cwks,

	.wesets		= sun20i_d1_w_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun20i_d1_w_ccu_wesets),
};

static int sun20i_d1_w_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	wetuwn devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun20i_d1_w_ccu_desc);
}

static const stwuct of_device_id sun20i_d1_w_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun20i-d1-w-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun20i_d1_w_ccu_dwivew = {
	.pwobe	= sun20i_d1_w_ccu_pwobe,
	.dwivew	= {
		.name			= "sun20i-d1-w-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= sun20i_d1_w_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun20i_d1_w_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
