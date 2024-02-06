// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021-2022, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,dispcc-sc7280.h>

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
	P_EDP_PHY_PWW_WINK_CWK,
	P_EDP_PHY_PWW_VCO_DIV_CWK,
	P_GCC_DISP_GPWW0_CWK,
};

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 1520MHz Configuwation*/
static const stwuct awpha_pww_config disp_cc_pww0_config = {
	.w = 0x4F,
	.awpha = 0x2AAA,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww disp_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
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
	{ P_EDP_PHY_PWW_WINK_CWK, 1 },
	{ P_EDP_PHY_PWW_VCO_DIV_CWK, 2 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "edp_phy_pww_wink_cwk" },
	{ .fw_name = "edp_phy_pww_vco_div_cwk" },
};

static const stwuct pawent_map disp_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_DISP_CC_PWW0_OUT_MAIN, 1 },
	{ P_GCC_DISP_GPWW0_CWK, 4 },
	{ P_DISP_CC_PWW0_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &disp_cc_pww0.cwkw.hw },
	{ .fw_name = "gcc_disp_gpww0_cwk" },
	{ .hw = &disp_cc_pww0.cwkw.hw },
};

static const stwuct pawent_map disp_cc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_DISP_GPWW0_CWK, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "gcc_disp_gpww0_cwk" },
};

static const stwuct pawent_map disp_cc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "dsi0_phy_pww_out_dsicwk" },
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GCC_DISP_GPWW0_CWK, 16, 0, 0),
	F(75000000, P_GCC_DISP_GPWW0_CWK, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_ahb_cwk_swc = {
	.cmd_wcgw = 0x1170,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_5,
	.fweq_tbw = ftbw_disp_cc_mdss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_ahb_cwk_swc",
		.pawent_data = disp_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_5),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_byte0_cwk_swc = {
	.cmd_wcgw = 0x10d8,
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
	.cmd_wcgw = 0x1158,
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
	.cmd_wcgw = 0x1128,
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
	.cmd_wcgw = 0x110c,
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
	.cmd_wcgw = 0x1140,
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

static stwuct cwk_wcg2 disp_cc_mdss_edp_aux_cwk_swc = {
	.cmd_wcgw = 0x11d0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_edp_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_edp_wink_cwk_swc = {
	.cmd_wcgw = 0x11a0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_edp_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_edp_pixew_cwk_swc = {
	.cmd_wcgw = 0x1188,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_edp_pixew_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_esc0_cwk_swc = {
	.cmd_wcgw = 0x10f4,
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
	F(200000000, P_GCC_DISP_GPWW0_CWK, 3, 0, 0),
	F(300000000, P_GCC_DISP_GPWW0_CWK, 2, 0, 0),
	F(380000000, P_DISP_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(506666667, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(608000000, P_DISP_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_mdp_cwk_swc = {
	.cmd_wcgw = 0x1090,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.fweq_tbw = ftbw_disp_cc_mdss_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_mdp_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_pcwk0_cwk_swc = {
	.cmd_wcgw = 0x1078,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_6,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_pcwk0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_6),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_wot_cwk_swc = {
	.cmd_wcgw = 0x10a8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.fweq_tbw = ftbw_disp_cc_mdss_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_wot_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_vsync_cwk_swc = {
	.cmd_wcgw = 0x10c0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_vsync_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_byte0_div_cwk_swc = {
	.weg = 0x10f0,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte0_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_dp_wink_div_cwk_swc = {
	.weg = 0x1124,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dp_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&disp_cc_mdss_dp_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_edp_wink_div_cwk_swc = {
	.weg = 0x11b8,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_edp_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&disp_cc_mdss_edp_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch disp_cc_mdss_ahb_cwk = {
	.hawt_weg = 0x1050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1050,
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
	.hawt_weg = 0x1030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1030,
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

static stwuct cwk_bwanch disp_cc_mdss_byte0_intf_cwk = {
	.hawt_weg = 0x1034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1034,
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
	.hawt_weg = 0x104c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x104c,
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
	.hawt_weg = 0x1044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1044,
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
	.hawt_weg = 0x103c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x103c,
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
	.hawt_weg = 0x1040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_dp_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_dp_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dp_pixew_cwk = {
	.hawt_weg = 0x1048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1048,
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

static stwuct cwk_bwanch disp_cc_mdss_edp_aux_cwk = {
	.hawt_weg = 0x1060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_edp_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_edp_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_edp_wink_cwk = {
	.hawt_weg = 0x1058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_edp_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_edp_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_edp_wink_intf_cwk = {
	.hawt_weg = 0x105c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x105c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_edp_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_edp_wink_div_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_edp_pixew_cwk = {
	.hawt_weg = 0x1054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_edp_pixew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_edp_pixew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_esc0_cwk = {
	.hawt_weg = 0x1038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1038,
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
	.hawt_weg = 0x1014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1014,
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
	.hawt_weg = 0x1024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x1024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_mdp_wut_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_non_gdsc_ahb_cwk = {
	.hawt_weg = 0x2004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2004,
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
	.hawt_weg = 0x1010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1010,
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
	.hawt_weg = 0x101c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x101c,
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
	.hawt_weg = 0x200c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_mdss_wscc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wscc_vsync_cwk = {
	.hawt_weg = 0x2008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2008,
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
	.hawt_weg = 0x102c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x102c,
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

static stwuct cwk_bwanch disp_cc_sweep_cwk = {
	.hawt_weg = 0x5004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc disp_cc_mdss_cowe_gdsc = {
	.gdscw = 0x1004,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0xf,
	.pd = {
		.name = "disp_cc_mdss_cowe_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
};

static stwuct cwk_wegmap *disp_cc_sc7280_cwocks[] = {
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
	[DISP_CC_MDSS_EDP_AUX_CWK] = &disp_cc_mdss_edp_aux_cwk.cwkw,
	[DISP_CC_MDSS_EDP_AUX_CWK_SWC] = &disp_cc_mdss_edp_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_EDP_WINK_CWK] = &disp_cc_mdss_edp_wink_cwk.cwkw,
	[DISP_CC_MDSS_EDP_WINK_CWK_SWC] = &disp_cc_mdss_edp_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_EDP_WINK_DIV_CWK_SWC] =
		&disp_cc_mdss_edp_wink_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_EDP_WINK_INTF_CWK] = &disp_cc_mdss_edp_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_EDP_PIXEW_CWK] = &disp_cc_mdss_edp_pixew_cwk.cwkw,
	[DISP_CC_MDSS_EDP_PIXEW_CWK_SWC] = &disp_cc_mdss_edp_pixew_cwk_swc.cwkw,
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
	[DISP_CC_MDSS_WSCC_AHB_CWK] = &disp_cc_mdss_wscc_ahb_cwk.cwkw,
	[DISP_CC_MDSS_WSCC_VSYNC_CWK] = &disp_cc_mdss_wscc_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK] = &disp_cc_mdss_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK_SWC] = &disp_cc_mdss_vsync_cwk_swc.cwkw,
	[DISP_CC_PWW0] = &disp_cc_pww0.cwkw,
	[DISP_CC_SWEEP_CWK] = &disp_cc_sweep_cwk.cwkw,
};

static stwuct gdsc *disp_cc_sc7280_gdscs[] = {
	[DISP_CC_MDSS_COWE_GDSC] = &disp_cc_mdss_cowe_gdsc,
};

static const stwuct wegmap_config disp_cc_sc7280_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x10000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc disp_cc_sc7280_desc = {
	.config = &disp_cc_sc7280_wegmap_config,
	.cwks = disp_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(disp_cc_sc7280_cwocks),
	.gdscs = disp_cc_sc7280_gdscs,
	.num_gdscs = AWWAY_SIZE(disp_cc_sc7280_gdscs),
};

static const stwuct of_device_id disp_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-dispcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, disp_cc_sc7280_match_tabwe);

static int disp_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &disp_cc_sc7280_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_pww_configuwe(&disp_cc_pww0, wegmap, &disp_cc_pww0_config);

	/*
	 * Keep the cwocks awways-ON
	 * DISP_CC_XO_CWK
	 */
	wegmap_update_bits(wegmap, 0x5008, BIT(0), BIT(0));

	wetuwn qcom_cc_weawwy_pwobe(pdev, &disp_cc_sc7280_desc, wegmap);
}

static stwuct pwatfowm_dwivew disp_cc_sc7280_dwivew = {
	.pwobe = disp_cc_sc7280_pwobe,
	.dwivew = {
		.name = "disp_cc-sc7280",
		.of_match_tabwe = disp_cc_sc7280_match_tabwe,
	},
};

static int __init disp_cc_sc7280_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&disp_cc_sc7280_dwivew);
}
subsys_initcaww(disp_cc_sc7280_init);

static void __exit disp_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&disp_cc_sc7280_dwivew);
}
moduwe_exit(disp_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI DISP_CC sc7280 Dwivew");
MODUWE_WICENSE("GPW v2");
