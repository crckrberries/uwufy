// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on dispcc-qcm2290.c
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021, Winawo Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm6115-dispcc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	DT_BI_TCXO,
	DT_SWEEP_CWK,
	DT_DSI0_PHY_PWW_OUT_BYTECWK,
	DT_DSI0_PHY_PWW_OUT_DSICWK,
	DT_GPWW0_DISP_DIV,
};

enum {
	P_BI_TCXO,
	P_DISP_CC_PWW0_OUT_MAIN,
	P_DSI0_PHY_PWW_OUT_BYTECWK,
	P_DSI0_PHY_PWW_OUT_DSICWK,
	P_GPWW0_OUT_MAIN,
	P_SWEEP_CWK,
};

static const stwuct cwk_pawent_data pawent_data_tcxo = { .index = DT_BI_TCXO };

static const stwuct pww_vco spawk_vco[] = {
	{ 500000000, 1000000000, 2 },
};

/* 768MHz configuwation */
static const stwuct awpha_pww_config disp_cc_pww0_config = {
	.w = 0x28,
	.awpha = 0x0,
	.awpha_en_mask = BIT(24),
	.vco_vaw = 0x2 << 20,
	.vco_mask = GENMASK(21, 20),
	.main_output_mask = BIT(0),
	.config_ctw_vaw = 0x4001055B,
};

static stwuct cwk_awpha_pww disp_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = spawk_vco,
	.num_vco = AWWAY_SIZE(spawk_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_pww0",
			.pawent_data = &pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_disp_cc_pww0_out_main[] = {
	{ 0x0, 1 },
	{ }
};
static stwuct cwk_awpha_pww_postdiv disp_cc_pww0_out_main = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_disp_cc_pww0_out_main,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_disp_cc_pww0_out_main),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_pww0_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&disp_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_ops,
	},
};

static const stwuct pawent_map disp_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 1 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_DSI0_PHY_PWW_OUT_BYTECWK },
};

static const stwuct pawent_map disp_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
};

static const stwuct pawent_map disp_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_2[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_GPWW0_DISP_DIV },
};

static const stwuct pawent_map disp_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_DISP_CC_PWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_3[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &disp_cc_pww0_out_main.cwkw.hw },
};

static const stwuct pawent_map disp_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_4[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_DSI0_PHY_PWW_OUT_DSICWK },
};

static const stwuct pawent_map disp_cc_pawent_map_5[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_5[] = {
	{ .index = DT_SWEEP_CWK, },
};

static stwuct cwk_wcg2 disp_cc_mdss_byte0_cwk_swc = {
	.cmd_wcgw = 0x20bc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_byte0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		/* Fow set_wate and set_pawent to succeed, pawent(s) must be enabwed */
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE | CWK_GET_WATE_NOCACHE,
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_byte0_div_cwk_swc = {
	.weg = 0x20d4,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte0_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_ahb_cwk_swc = {
	.cmd_wcgw = 0x2154,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_ahb_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_esc0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_esc0_cwk_swc = {
	.cmd_wcgw = 0x20d8,
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

static const stwuct fweq_tbw ftbw_disp_cc_mdss_mdp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(192000000, P_DISP_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(256000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(307200000, P_DISP_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(384000000, P_DISP_CC_PWW0_OUT_MAIN, 2, 0, 0),
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
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_pcwk0_cwk_swc = {
	.cmd_wcgw = 0x205c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_pcwk0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		/* Fow set_wate and set_pawent to succeed, pawent(s) must be enabwed */
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE | CWK_GET_WATE_NOCACHE,
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
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_mdss_vsync_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_sweep_cwk_swc[] = {
	F(32764, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_sweep_cwk_swc = {
	.cmd_wcgw = 0x6050,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_5,
	.fweq_tbw = ftbw_disp_cc_sweep_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "disp_cc_sweep_cwk_swc",
		.pawent_data = disp_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_5),
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
				&disp_cc_mdss_byte0_div_cwk_swc.cwkw.hw,
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
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2018,
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
	.hawt_weg = 0x4004,
	.hawt_check = BWANCH_HAWT_VOTED,
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
			.pawent_hws = (const stwuct cwk_hw*[]) {
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

static stwuct cwk_bwanch disp_cc_sweep_cwk = {
	.hawt_weg = 0x6068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "disp_cc_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&disp_cc_sweep_cwk_swc.cwkw.hw,
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
	.fwags = HW_CTWW,
};

static stwuct gdsc *disp_cc_sm6115_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
};

static stwuct cwk_wegmap *disp_cc_sm6115_cwocks[] = {
	[DISP_CC_PWW0] = &disp_cc_pww0.cwkw,
	[DISP_CC_PWW0_OUT_MAIN] = &disp_cc_pww0_out_main.cwkw,
	[DISP_CC_MDSS_AHB_CWK] = &disp_cc_mdss_ahb_cwk.cwkw,
	[DISP_CC_MDSS_AHB_CWK_SWC] = &disp_cc_mdss_ahb_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK] = &disp_cc_mdss_byte0_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK_SWC] = &disp_cc_mdss_byte0_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_DIV_CWK_SWC] = &disp_cc_mdss_byte0_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_INTF_CWK] = &disp_cc_mdss_byte0_intf_cwk.cwkw,
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
	[DISP_CC_SWEEP_CWK] = &disp_cc_sweep_cwk.cwkw,
	[DISP_CC_SWEEP_CWK_SWC] = &disp_cc_sweep_cwk_swc.cwkw,
};

static const stwuct wegmap_config disp_cc_sm6115_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x10000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc disp_cc_sm6115_desc = {
	.config = &disp_cc_sm6115_wegmap_config,
	.cwks = disp_cc_sm6115_cwocks,
	.num_cwks = AWWAY_SIZE(disp_cc_sm6115_cwocks),
	.gdscs = disp_cc_sm6115_gdscs,
	.num_gdscs = AWWAY_SIZE(disp_cc_sm6115_gdscs),
};

static const stwuct of_device_id disp_cc_sm6115_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6115-dispcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, disp_cc_sm6115_match_tabwe);

static int disp_cc_sm6115_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &disp_cc_sm6115_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_awpha_pww_configuwe(&disp_cc_pww0, wegmap, &disp_cc_pww0_config);

	/* Keep DISP_CC_XO_CWK awways-ON */
	wegmap_update_bits(wegmap, 0x604c, BIT(0), BIT(0));

	wet = qcom_cc_weawwy_pwobe(pdev, &disp_cc_sm6115_desc, wegmap);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew DISP CC cwocks\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew disp_cc_sm6115_dwivew = {
	.pwobe = disp_cc_sm6115_pwobe,
	.dwivew = {
		.name = "dispcc-sm6115",
		.of_match_tabwe = disp_cc_sm6115_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(disp_cc_sm6115_dwivew);
MODUWE_DESCWIPTION("Quawcomm SM6115 Dispway Cwock contwowwew");
MODUWE_WICENSE("GPW");
