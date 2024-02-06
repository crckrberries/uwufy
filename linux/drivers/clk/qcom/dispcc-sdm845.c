// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,dispcc-sdm845.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_DISP_CC_PWW0_OUT_MAIN,
	P_DSI0_PHY_PWW_OUT_BYTECWK,
	P_DSI0_PHY_PWW_OUT_DSICWK,
	P_DSI1_PHY_PWW_OUT_BYTECWK,
	P_DSI1_PHY_PWW_OUT_DSICWK,
	P_GPWW0_OUT_MAIN,
	P_GPWW0_OUT_MAIN_DIV,
	P_DP_PHY_PWW_WINK_CWK,
	P_DP_PHY_PWW_VCO_DIV_CWK,
};

static stwuct cwk_awpha_pww disp_cc_pww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct pawent_map disp_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 1 },
	{ P_DSI1_PHY_PWW_OUT_BYTECWK, 2 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .fw_name = "dsi0_phy_pww_out_bytecwk", .name = "dsi0_phy_pww_out_bytecwk" },
	{ .fw_name = "dsi1_phy_pww_out_bytecwk", .name = "dsi1_phy_pww_out_bytecwk" },
};

static const stwuct pawent_map disp_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_DP_PHY_PWW_WINK_CWK, 1 },
	{ P_DP_PHY_PWW_VCO_DIV_CWK, 2 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .fw_name = "dp_wink_cwk_divsew_ten", .name = "dp_wink_cwk_divsew_ten" },
	{ .fw_name = "dp_vco_divided_cwk_swc_mux", .name = "dp_vco_divided_cwk_swc_mux" },
};

static const stwuct pawent_map disp_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
};

static const stwuct pawent_map disp_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_DISP_CC_PWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_MAIN, 4 },
	{ P_GPWW0_OUT_MAIN_DIV, 5 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &disp_cc_pww0.cwkw.hw },
	{ .fw_name = "gcc_disp_gpww0_cwk_swc", .name = "gcc_disp_gpww0_cwk_swc" },
	{ .fw_name = "gcc_disp_gpww0_div_cwk_swc", .name = "gcc_disp_gpww0_div_cwk_swc" },
};

static const stwuct pawent_map disp_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
	{ P_DSI1_PHY_PWW_OUT_DSICWK, 2 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .fw_name = "dsi0_phy_pww_out_dsicwk", .name = "dsi0_phy_pww_out_dsicwk" },
	{ .fw_name = "dsi1_phy_pww_out_dsicwk", .name = "dsi1_phy_pww_out_dsicwk" },
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_wcg2 disp_cc_mdss_byte0_cwk_swc = {
	.cmd_wcgw = 0x20d0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_byte0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_wcg2 disp_cc_mdss_byte1_cwk_swc = {
	.cmd_wcgw = 0x20ec,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_byte1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_dp_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_aux_cwk_swc = {
	.cmd_wcgw = 0x219c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_cwypto_cwk_swc = {
	.cmd_wcgw = 0x2154,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_cwypto_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_wink_cwk_swc = {
	.cmd_wcgw = 0x2138,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_pixew1_cwk_swc = {
	.cmd_wcgw = 0x2184,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_pixew1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_pixew_cwk_swc = {
	.cmd_wcgw = 0x216c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_pixew_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_esc0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_esc0_cwk_swc = {
	.cmd_wcgw = 0x2108,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_esc0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_esc1_cwk_swc = {
	.cmd_wcgw = 0x2120,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_esc1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_mdp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(85714286, P_GPWW0_OUT_MAIN, 7, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(150000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(171428571, P_GPWW0_OUT_MAIN, 3.5, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	F(344000000, P_DISP_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(430000000, P_DISP_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_mdp_cwk_swc = {
	.cmd_wcgw = 0x2088,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_mdp_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_wcg2 disp_cc_mdss_pcwk0_cwk_swc = {
	.cmd_wcgw = 0x2058,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_pcwk0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_wcg2 disp_cc_mdss_pcwk1_cwk_swc = {
	.cmd_wcgw = 0x2070,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_pcwk1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_wot_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(171428571, P_GPWW0_OUT_MAIN, 3.5, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	F(344000000, P_DISP_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(430000000, P_DISP_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_wot_cwk_swc = {
	.cmd_wcgw = 0x20a0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_wot_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_wot_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_vsync_cwk_swc = {
	.cmd_wcgw = 0x20b8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_vsync_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch disp_cc_mdss_ahb_cwk = {
	.hawt_weg = 0x4004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_axi_cwk = {
	.hawt_weg = 0x4008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_bwanch disp_cc_mdss_byte0_cwk = {
	.hawt_weg = 0x2028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_wegmap_div disp_cc_mdss_byte0_div_cwk_swc = {
	.weg = 0x20e8,
	.shift = 0,
	.width = 2,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_div_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_bwanch disp_cc_mdss_byte0_intf_cwk = {
	.hawt_weg = 0x202c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x202c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte0_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte0_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_bwanch disp_cc_mdss_byte1_cwk = {
	.hawt_weg = 0x2030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_wegmap_div disp_cc_mdss_byte1_div_cwk_swc = {
	.weg = 0x2104,
	.shift = 0,
	.width = 2,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte1_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_div_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_bwanch disp_cc_mdss_byte1_intf_cwk = {
	.hawt_weg = 0x2034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte1_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte1_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_aux_cwk = {
	.hawt_weg = 0x2054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_cwypto_cwk = {
	.hawt_weg = 0x2048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_cwypto_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_wink_cwk = {
	.hawt_weg = 0x2040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* weset state of disp_cc_mdss_dp_wink_div_cwk_swc dividew is 0x3 (div 4) */
static stwuct cwk_bwanch disp_cc_mdss_dp_wink_intf_cwk = {
	.hawt_weg = 0x2044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_pixew1_cwk = {
	.hawt_weg = 0x2050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_pixew1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_pixew1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_pixew_cwk = {
	.hawt_weg = 0x204c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x204c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_pixew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_pixew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_esc0_cwk = {
	.hawt_weg = 0x2038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_esc0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_esc0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_esc1_cwk = {
	.hawt_weg = 0x203c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_esc1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_esc1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_mdp_cwk = {
	.hawt_weg = 0x200c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_mdp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_mdp_wut_cwk = {
	.hawt_weg = 0x201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_mdp_wut_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_bwanch disp_cc_mdss_pcwk0_cwk = {
	.hawt_weg = 0x2004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_pcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_pcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Wetuwn the HW wecawc wate fow idwe use case */
static stwuct cwk_bwanch disp_cc_mdss_pcwk1_cwk = {
	.hawt_weg = 0x2008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_pcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_pcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wot_cwk = {
	.hawt_weg = 0x2014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_wot_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_wot_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wscc_ahb_cwk = {
	.hawt_weg = 0x5004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_wscc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wscc_vsync_cwk = {
	.hawt_weg = 0x5008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_wscc_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_vsync_cwk = {
	.hawt_weg = 0x2024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc mdss_gdsc = {
	.gdscw = 0x3000,
	.pd = {
		.name = "mdss_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
};

static stwuct cwk_wegmap *disp_cc_sdm845_cwocks[] = {
	[DISP_CC_MDSS_AHB_CWK] = &disp_cc_mdss_ahb_cwk.cwkw,
	[DISP_CC_MDSS_AXI_CWK] = &disp_cc_mdss_axi_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK] = &disp_cc_mdss_byte0_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK_SWC] = &disp_cc_mdss_byte0_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_INTF_CWK] = &disp_cc_mdss_byte0_intf_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_DIV_CWK_SWC] =
					&disp_cc_mdss_byte0_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE1_CWK] = &disp_cc_mdss_byte1_cwk.cwkw,
	[DISP_CC_MDSS_BYTE1_CWK_SWC] = &disp_cc_mdss_byte1_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE1_INTF_CWK] = &disp_cc_mdss_byte1_intf_cwk.cwkw,
	[DISP_CC_MDSS_BYTE1_DIV_CWK_SWC] =
					&disp_cc_mdss_byte1_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_AUX_CWK] = &disp_cc_mdss_dp_aux_cwk.cwkw,
	[DISP_CC_MDSS_DP_AUX_CWK_SWC] = &disp_cc_mdss_dp_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_CWYPTO_CWK] = &disp_cc_mdss_dp_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DP_CWYPTO_CWK_SWC] =
					&disp_cc_mdss_dp_cwypto_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_WINK_CWK] = &disp_cc_mdss_dp_wink_cwk.cwkw,
	[DISP_CC_MDSS_DP_WINK_CWK_SWC] = &disp_cc_mdss_dp_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_WINK_INTF_CWK] = &disp_cc_mdss_dp_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DP_PIXEW1_CWK] = &disp_cc_mdss_dp_pixew1_cwk.cwkw,
	[DISP_CC_MDSS_DP_PIXEW1_CWK_SWC] =
					&disp_cc_mdss_dp_pixew1_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_PIXEW_CWK] = &disp_cc_mdss_dp_pixew_cwk.cwkw,
	[DISP_CC_MDSS_DP_PIXEW_CWK_SWC] = &disp_cc_mdss_dp_pixew_cwk_swc.cwkw,
	[DISP_CC_MDSS_ESC0_CWK] = &disp_cc_mdss_esc0_cwk.cwkw,
	[DISP_CC_MDSS_ESC0_CWK_SWC] = &disp_cc_mdss_esc0_cwk_swc.cwkw,
	[DISP_CC_MDSS_ESC1_CWK] = &disp_cc_mdss_esc1_cwk.cwkw,
	[DISP_CC_MDSS_ESC1_CWK_SWC] = &disp_cc_mdss_esc1_cwk_swc.cwkw,
	[DISP_CC_MDSS_MDP_CWK] = &disp_cc_mdss_mdp_cwk.cwkw,
	[DISP_CC_MDSS_MDP_CWK_SWC] = &disp_cc_mdss_mdp_cwk_swc.cwkw,
	[DISP_CC_MDSS_MDP_WUT_CWK] = &disp_cc_mdss_mdp_wut_cwk.cwkw,
	[DISP_CC_MDSS_PCWK0_CWK] = &disp_cc_mdss_pcwk0_cwk.cwkw,
	[DISP_CC_MDSS_PCWK0_CWK_SWC] = &disp_cc_mdss_pcwk0_cwk_swc.cwkw,
	[DISP_CC_MDSS_PCWK1_CWK] = &disp_cc_mdss_pcwk1_cwk.cwkw,
	[DISP_CC_MDSS_PCWK1_CWK_SWC] = &disp_cc_mdss_pcwk1_cwk_swc.cwkw,
	[DISP_CC_MDSS_WOT_CWK] = &disp_cc_mdss_wot_cwk.cwkw,
	[DISP_CC_MDSS_WOT_CWK_SWC] = &disp_cc_mdss_wot_cwk_swc.cwkw,
	[DISP_CC_MDSS_WSCC_AHB_CWK] = &disp_cc_mdss_wscc_ahb_cwk.cwkw,
	[DISP_CC_MDSS_WSCC_VSYNC_CWK] = &disp_cc_mdss_wscc_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK] = &disp_cc_mdss_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK_SWC] = &disp_cc_mdss_vsync_cwk_swc.cwkw,
	[DISP_CC_PWW0] = &disp_cc_pww0.cwkw,
};

static const stwuct qcom_weset_map disp_cc_sdm845_wesets[] = {
	[DISP_CC_MDSS_WSCC_BCW] = { 0x5000 },
};

static stwuct gdsc *disp_cc_sdm845_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
};

static const stwuct wegmap_config disp_cc_sdm845_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x10000,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc disp_cc_sdm845_desc = {
	.config = &disp_cc_sdm845_wegmap_config,
	.cwks = disp_cc_sdm845_cwocks,
	.num_cwks = AWWAY_SIZE(disp_cc_sdm845_cwocks),
	.wesets = disp_cc_sdm845_wesets,
	.num_wesets = AWWAY_SIZE(disp_cc_sdm845_wesets),
	.gdscs = disp_cc_sdm845_gdscs,
	.num_gdscs = AWWAY_SIZE(disp_cc_sdm845_gdscs),
};

static const stwuct of_device_id disp_cc_sdm845_match_tabwe[] = {
	{ .compatibwe = "qcom,sdm845-dispcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, disp_cc_sdm845_match_tabwe);

static int disp_cc_sdm845_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	stwuct awpha_pww_config disp_cc_pww0_config = {};

	wegmap = qcom_cc_map(pdev, &disp_cc_sdm845_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	disp_cc_pww0_config.w = 0x2c;
	disp_cc_pww0_config.awpha = 0xcaaa;

	cwk_fabia_pww_configuwe(&disp_cc_pww0, wegmap, &disp_cc_pww0_config);

	/* Enabwe hawdwawe cwock gating fow DSI and MDP cwocks */
	wegmap_update_bits(wegmap, 0x8000, 0x7f0, 0x7f0);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &disp_cc_sdm845_desc, wegmap);
}

static stwuct pwatfowm_dwivew disp_cc_sdm845_dwivew = {
	.pwobe		= disp_cc_sdm845_pwobe,
	.dwivew		= {
		.name	= "disp_cc-sdm845",
		.of_match_tabwe = disp_cc_sdm845_match_tabwe,
	},
};

static int __init disp_cc_sdm845_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&disp_cc_sdm845_dwivew);
}
subsys_initcaww(disp_cc_sdm845_init);

static void __exit disp_cc_sdm845_exit(void)
{
	pwatfowm_dwivew_unwegistew(&disp_cc_sdm845_dwivew);
}
moduwe_exit(disp_cc_sdm845_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QTI DISPCC SDM845 Dwivew");
