// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019, 2022, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,dispcc-sc7180.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_DISP_CC_PWW0_OUT_EVEN,
	P_DISP_CC_PWW0_OUT_MAIN,
	P_DP_PHY_PWW_WINK_CWK,
	P_DP_PHY_PWW_VCO_DIV_CWK,
	P_DSI0_PHY_PWW_OUT_BYTECWK,
	P_DSI0_PHY_PWW_OUT_DSICWK,
	P_GPWW0_OUT_MAIN,
};

static const stwuct pww_vco fabia_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct cwk_awpha_pww disp_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_disp_cc_pww0_out_even[] = {
	{ 0x0, 1 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv disp_cc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_disp_cc_pww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_disp_cc_pww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&disp_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
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
	{ P_DISP_CC_PWW0_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &disp_cc_pww0.cwkw.hw },
	{ .fw_name = "gcc_disp_gpww0_cwk_swc" },
	{ .hw = &disp_cc_pww0_out_even.cwkw.hw },
};

static const stwuct pawent_map disp_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "gcc_disp_gpww0_cwk_swc" },
};

static const stwuct pawent_map disp_cc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "dsi0_phy_pww_out_dsicwk" },
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(75000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_ahb_cwk_swc = {
	.cmd_wcgw = 0x22bc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.fweq_tbw = ftbw_disp_cc_mdss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_ahb_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_byte0_cwk_swc = {
	.cmd_wcgw = 0x2110,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_byte0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_dp_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_aux_cwk_swc = {
	.cmd_wcgw = 0x21dc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_cwypto_cwk_swc = {
	.cmd_wcgw = 0x2194,
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
	.cmd_wcgw = 0x2178,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dp_pixew_cwk_swc = {
	.cmd_wcgw = 0x21ac,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_dp_pixew_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_esc0_cwk_swc = {
	.cmd_wcgw = 0x2148,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_esc0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_mdp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	F(345000000, P_DISP_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(460000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_mdp_cwk_swc = {
	.cmd_wcgw = 0x20c8,
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
	.cmd_wcgw = 0x2098,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_5,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_pcwk0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_wot_cwk_swc = {
	.cmd_wcgw = 0x20e0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_wot_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_vsync_cwk_swc = {
	.cmd_wcgw = 0x20f8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_vsync_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_bwanch disp_cc_mdss_ahb_cwk = {
	.hawt_weg = 0x2080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2080,
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

static stwuct cwk_wegmap_div disp_cc_mdss_byte0_div_cwk_swc = {
	.weg = 0x2128,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte0_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_dp_wink_div_cwk_swc = {
	.weg = 0x2190,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dp_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_dp_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

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

static stwuct cwk_bwanch disp_cc_mdss_dp_wink_intf_cwk = {
	.hawt_weg = 0x2044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
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
	.hawt_check = BWANCH_VOTED,
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

static stwuct cwk_bwanch disp_cc_mdss_wscc_vsync_cwk = {
	.hawt_weg = 0x4008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4008,
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
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0xf,
	.pd = {
		.name = "mdss_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW,
};

static stwuct gdsc *disp_cc_sc7180_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
};

static stwuct cwk_wegmap *disp_cc_sc7180_cwocks[] = {
	[DISP_CC_MDSS_AHB_CWK] = &disp_cc_mdss_ahb_cwk.cwkw,
	[DISP_CC_MDSS_AHB_CWK_SWC] = &disp_cc_mdss_ahb_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK] = &disp_cc_mdss_byte0_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK_SWC] = &disp_cc_mdss_byte0_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_DIV_CWK_SWC] = &disp_cc_mdss_byte0_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_INTF_CWK] = &disp_cc_mdss_byte0_intf_cwk.cwkw,
	[DISP_CC_MDSS_DP_AUX_CWK] = &disp_cc_mdss_dp_aux_cwk.cwkw,
	[DISP_CC_MDSS_DP_AUX_CWK_SWC] = &disp_cc_mdss_dp_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_CWYPTO_CWK] = &disp_cc_mdss_dp_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DP_CWYPTO_CWK_SWC] = &disp_cc_mdss_dp_cwypto_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_WINK_CWK] = &disp_cc_mdss_dp_wink_cwk.cwkw,
	[DISP_CC_MDSS_DP_WINK_CWK_SWC] = &disp_cc_mdss_dp_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DP_WINK_DIV_CWK_SWC] =
				&disp_cc_mdss_dp_wink_div_cwk_swc.cwkw,
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
	[DISP_CC_MDSS_WSCC_VSYNC_CWK] = &disp_cc_mdss_wscc_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK] = &disp_cc_mdss_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK_SWC] = &disp_cc_mdss_vsync_cwk_swc.cwkw,
	[DISP_CC_PWW0] = &disp_cc_pww0.cwkw,
	[DISP_CC_PWW0_OUT_EVEN] = &disp_cc_pww0_out_even.cwkw,
};

static const stwuct wegmap_config disp_cc_sc7180_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x10000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc disp_cc_sc7180_desc = {
	.config = &disp_cc_sc7180_wegmap_config,
	.cwks = disp_cc_sc7180_cwocks,
	.num_cwks = AWWAY_SIZE(disp_cc_sc7180_cwocks),
	.gdscs = disp_cc_sc7180_gdscs,
	.num_gdscs = AWWAY_SIZE(disp_cc_sc7180_gdscs),
};

static const stwuct of_device_id disp_cc_sc7180_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7180-dispcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, disp_cc_sc7180_match_tabwe);

static int disp_cc_sc7180_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	stwuct awpha_pww_config disp_cc_pww_config = {};

	wegmap = qcom_cc_map(pdev, &disp_cc_sc7180_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* 1380MHz configuwation */
	disp_cc_pww_config.w = 0x47;
	disp_cc_pww_config.awpha = 0xe000;
	disp_cc_pww_config.usew_ctw_vaw = 0x00000001;
	disp_cc_pww_config.usew_ctw_hi_vaw = 0x00004805;

	cwk_fabia_pww_configuwe(&disp_cc_pww0, wegmap, &disp_cc_pww_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &disp_cc_sc7180_desc, wegmap);
}

static stwuct pwatfowm_dwivew disp_cc_sc7180_dwivew = {
	.pwobe = disp_cc_sc7180_pwobe,
	.dwivew = {
		.name = "sc7180-dispcc",
		.of_match_tabwe = disp_cc_sc7180_match_tabwe,
	},
};

static int __init disp_cc_sc7180_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&disp_cc_sc7180_dwivew);
}
subsys_initcaww(disp_cc_sc7180_init);

static void __exit disp_cc_sc7180_exit(void)
{
	pwatfowm_dwivew_unwegistew(&disp_cc_sc7180_dwivew);
}
moduwe_exit(disp_cc_sc7180_exit);

MODUWE_DESCWIPTION("QTI DISP_CC SC7180 Dwivew");
MODUWE_WICENSE("GPW v2");
