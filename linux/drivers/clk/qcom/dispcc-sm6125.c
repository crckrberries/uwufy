// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,dispcc-sm6125.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_DISP_CC_PWW0_OUT_MAIN,
	P_DP_PHY_PWW_WINK_CWK,
	P_DP_PHY_PWW_VCO_DIV_CWK,
	P_DSI0_PHY_PWW_OUT_BYTECWK,
	P_DSI0_PHY_PWW_OUT_DSICWK,
	P_DSI1_PHY_PWW_OUT_DSICWK,
	P_GPWW0_OUT_MAIN,
};

static stwuct pww_vco disp_cc_pww_vco[] = {
	{ 500000000, 1000000000, 2 },
};

static stwuct cwk_awpha_pww disp_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = disp_cc_pww_vco,
	.num_vco = AWWAY_SIZE(disp_cc_pww_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

/* 768MHz configuwation */
static const stwuct awpha_pww_config disp_cc_pww0_config = {
	.w = 0x28,
	.vco_vaw = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.main_output_mask = BIT(0),
	.config_ctw_vaw = 0x4001055b,
};

static const stwuct pawent_map disp_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
};

static const stwuct pawent_map disp_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_DP_PHY_PWW_WINK_CWK, 1 },
	{ P_DP_PHY_PWW_VCO_DIV_CWK, 2 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "dp_phy_pww_wink_cwk" },
	{ .fw_name = "dp_phy_pww_vco_div_cwk" },
};

static const stwuct pawent_map disp_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 1 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "dsi0_phy_pww_out_bytecwk" },
};

static const stwuct pawent_map disp_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_DISP_CC_PWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &disp_cc_pww0.cwkw.hw },
	{ .fw_name = "gcc_disp_gpww0_div_cwk_swc" },
};

static const stwuct pawent_map disp_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "gcc_disp_gpww0_div_cwk_swc" },
};

static const stwuct pawent_map disp_cc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
	{ P_DSI1_PHY_PWW_OUT_DSICWK, 2 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "dsi0_phy_pww_out_dsicwk" },
	{ .fw_name = "dsi1_phy_pww_out_dsicwk" },
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(75000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_ahb_cwk_swc = {
	.cmd_wcgw = 0x2154,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.fweq_tbw = ftbw_disp_cc_mdss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_ahb_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_byte0_cwk_swc = {
	.cmd_wcgw = 0x20bc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_byte0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
		.ops = &cwk_byte2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_dp_aux1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_aux_cwk_swc = {
	.cmd_wcgw = 0x213c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_dp_cwypto_cwk_swc[] = {
	F( 180000, P_DP_PHY_PWW_WINK_CWK,   1.5,   0,   0),
	F( 360000, P_DP_PHY_PWW_WINK_CWK,   1.5,   0,   0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_cwypto_cwk_swc = {
	.cmd_wcgw = 0x210c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_cwypto_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_cwypto_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_GET_WATE_NOCACHE,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_dp_wink_cwk_swc[] = {
	F( 162000, P_DP_PHY_PWW_WINK_CWK,   1,   0,   0),
	F( 270000, P_DP_PHY_PWW_WINK_CWK,   1,   0,   0),
	F( 540000, P_DP_PHY_PWW_WINK_CWK,   1,   0,   0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_wink_cwk_swc = {
	.cmd_wcgw = 0x20f0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_wink_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_pixew_cwk_swc = {
	.cmd_wcgw = 0x2124,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_pixew_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_esc0_cwk_swc = {
	.cmd_wcgw = 0x20d8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_esc0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_mdp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(192000000, P_DISP_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(256000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(307200000, P_DISP_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(384000000, P_DISP_CC_PWW0_OUT_MAIN, 2, 0, 0),
	F(400000000, P_GPWW0_OUT_MAIN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_mdp_cwk_swc = {
	.cmd_wcgw = 0x2074,
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

static stwuct cwk_wcg2 disp_cc_mdss_pcwk0_cwk_swc = {
	.cmd_wcgw = 0x205c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_5,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_pcwk0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
		.ops = &cwk_pixew_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_wot_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(192000000, P_DISP_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(256000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(307200000, P_DISP_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_wot_cwk_swc = {
	.cmd_wcgw = 0x208c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_wot_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_wot_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_vsync_cwk_swc = {
	.cmd_wcgw = 0x20a4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_vsync_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch disp_cc_mdss_ahb_cwk = {
	.hawt_weg = 0x2044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_byte0_cwk = {
	.hawt_weg = 0x2024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_byte0_intf_cwk = {
	.hawt_weg = 0x2028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_byte0_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_aux_cwk = {
	.hawt_weg = 0x2040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2040,
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
	.hawt_weg = 0x2038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_cwypto_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_wink_cwk = {
	.hawt_weg = 0x2030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_wink_intf_cwk = {
	.hawt_weg = 0x2034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_pixew_cwk = {
	.hawt_weg = 0x203c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_pixew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_pixew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_esc0_cwk = {
	.hawt_weg = 0x202c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x202c,
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

static stwuct cwk_bwanch disp_cc_mdss_mdp_cwk = {
	.hawt_weg = 0x2008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2008,
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
	.hawt_weg = 0x2018,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2018,
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

static stwuct cwk_bwanch disp_cc_mdss_non_gdsc_ahb_cwk = {
	.hawt_weg = 0x4004,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_non_gdsc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

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
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wot_cwk = {
	.hawt_weg = 0x2010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2010,
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

static stwuct cwk_bwanch disp_cc_mdss_vsync_cwk = {
	.hawt_weg = 0x2020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2020,
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

static stwuct cwk_bwanch disp_cc_xo_cwk = {
	.hawt_weg = 0x604c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x604c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_xo_cwk",
			.fwags = CWK_IS_CWITICAW,
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
	.fwags = HW_CTWW,
};

static stwuct cwk_wegmap *disp_cc_sm6125_cwocks[] = {
	[DISP_CC_MDSS_AHB_CWK] = &disp_cc_mdss_ahb_cwk.cwkw,
	[DISP_CC_MDSS_AHB_CWK_SWC] = &disp_cc_mdss_ahb_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK] = &disp_cc_mdss_byte0_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK_SWC] = &disp_cc_mdss_byte0_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_INTF_CWK] = &disp_cc_mdss_byte0_intf_cwk.cwkw,
	[DISP_CC_MDSS_DP_AUX_CWK] = &disp_cc_mdss_dp_aux_cwk.cwkw,
	[DISP_CC_MDSS_DP_AUX_CWK_SWC] = &disp_cc_mdss_dp_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_CWYPTO_CWK] = &disp_cc_mdss_dp_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DP_CWYPTO_CWK_SWC] = &disp_cc_mdss_dp_cwypto_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_WINK_CWK] = &disp_cc_mdss_dp_wink_cwk.cwkw,
	[DISP_CC_MDSS_DP_WINK_CWK_SWC] = &disp_cc_mdss_dp_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_WINK_INTF_CWK] = &disp_cc_mdss_dp_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DP_PIXEW_CWK] = &disp_cc_mdss_dp_pixew_cwk.cwkw,
	[DISP_CC_MDSS_DP_PIXEW_CWK_SWC] = &disp_cc_mdss_dp_pixew_cwk_swc.cwkw,
	[DISP_CC_MDSS_ESC0_CWK] = &disp_cc_mdss_esc0_cwk.cwkw,
	[DISP_CC_MDSS_ESC0_CWK_SWC] = &disp_cc_mdss_esc0_cwk_swc.cwkw,
	[DISP_CC_MDSS_MDP_CWK] = &disp_cc_mdss_mdp_cwk.cwkw,
	[DISP_CC_MDSS_MDP_CWK_SWC] = &disp_cc_mdss_mdp_cwk_swc.cwkw,
	[DISP_CC_MDSS_MDP_WUT_CWK] = &disp_cc_mdss_mdp_wut_cwk.cwkw,
	[DISP_CC_MDSS_NON_GDSC_AHB_CWK] = &disp_cc_mdss_non_gdsc_ahb_cwk.cwkw,
	[DISP_CC_MDSS_PCWK0_CWK] = &disp_cc_mdss_pcwk0_cwk.cwkw,
	[DISP_CC_MDSS_PCWK0_CWK_SWC] = &disp_cc_mdss_pcwk0_cwk_swc.cwkw,
	[DISP_CC_MDSS_WOT_CWK] = &disp_cc_mdss_wot_cwk.cwkw,
	[DISP_CC_MDSS_WOT_CWK_SWC] = &disp_cc_mdss_wot_cwk_swc.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK] = &disp_cc_mdss_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK_SWC] = &disp_cc_mdss_vsync_cwk_swc.cwkw,
	[DISP_CC_PWW0] = &disp_cc_pww0.cwkw,
	[DISP_CC_XO_CWK] = &disp_cc_xo_cwk.cwkw,
};

static stwuct gdsc *disp_cc_sm6125_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
};

static const stwuct wegmap_config disp_cc_sm6125_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x10000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc disp_cc_sm6125_desc = {
	.config = &disp_cc_sm6125_wegmap_config,
	.cwks = disp_cc_sm6125_cwocks,
	.num_cwks = AWWAY_SIZE(disp_cc_sm6125_cwocks),
	.gdscs = disp_cc_sm6125_gdscs,
	.num_gdscs = AWWAY_SIZE(disp_cc_sm6125_gdscs),
};

static const stwuct of_device_id disp_cc_sm6125_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6125-dispcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, disp_cc_sm6125_match_tabwe);

static int disp_cc_sm6125_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &disp_cc_sm6125_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_awpha_pww_configuwe(&disp_cc_pww0, wegmap, &disp_cc_pww0_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &disp_cc_sm6125_desc, wegmap);
}

static stwuct pwatfowm_dwivew disp_cc_sm6125_dwivew = {
	.pwobe = disp_cc_sm6125_pwobe,
	.dwivew = {
		.name = "disp_cc-sm6125",
		.of_match_tabwe = disp_cc_sm6125_match_tabwe,
	},
};

static int __init disp_cc_sm6125_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&disp_cc_sm6125_dwivew);
}
subsys_initcaww(disp_cc_sm6125_init);

static void __exit disp_cc_sm6125_exit(void)
{
	pwatfowm_dwivew_unwegistew(&disp_cc_sm6125_dwivew);
}
moduwe_exit(disp_cc_sm6125_exit);

MODUWE_DESCWIPTION("QTI DISPCC SM6125 Dwivew");
MODUWE_WICENSE("GPW v2");
