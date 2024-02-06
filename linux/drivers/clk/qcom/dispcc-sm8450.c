// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm_wuntime.h>

#incwude <dt-bindings/cwock/qcom,sm8450-dispcc.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "weset.h"
#incwude "gdsc.h"

/* Need to match the owdew of cwocks in DT binding */
enum {
	DT_BI_TCXO,
	DT_BI_TCXO_AO,
	DT_AHB_CWK,
	DT_SWEEP_CWK,

	DT_DSI0_PHY_PWW_OUT_BYTECWK,
	DT_DSI0_PHY_PWW_OUT_DSICWK,
	DT_DSI1_PHY_PWW_OUT_BYTECWK,
	DT_DSI1_PHY_PWW_OUT_DSICWK,

	DT_DP0_PHY_PWW_WINK_CWK,
	DT_DP0_PHY_PWW_VCO_DIV_CWK,
	DT_DP1_PHY_PWW_WINK_CWK,
	DT_DP1_PHY_PWW_VCO_DIV_CWK,
	DT_DP2_PHY_PWW_WINK_CWK,
	DT_DP2_PHY_PWW_VCO_DIV_CWK,
	DT_DP3_PHY_PWW_WINK_CWK,
	DT_DP3_PHY_PWW_VCO_DIV_CWK,
};

#define DISP_CC_MISC_CMD	0xF000

enum {
	P_BI_TCXO,
	P_DISP_CC_PWW0_OUT_MAIN,
	P_DISP_CC_PWW1_OUT_EVEN,
	P_DISP_CC_PWW1_OUT_MAIN,
	P_DP0_PHY_PWW_WINK_CWK,
	P_DP0_PHY_PWW_VCO_DIV_CWK,
	P_DP1_PHY_PWW_WINK_CWK,
	P_DP1_PHY_PWW_VCO_DIV_CWK,
	P_DP2_PHY_PWW_WINK_CWK,
	P_DP2_PHY_PWW_VCO_DIV_CWK,
	P_DP3_PHY_PWW_WINK_CWK,
	P_DP3_PHY_PWW_VCO_DIV_CWK,
	P_DSI0_PHY_PWW_OUT_BYTECWK,
	P_DSI0_PHY_PWW_OUT_DSICWK,
	P_DSI1_PHY_PWW_OUT_BYTECWK,
	P_DSI1_PHY_PWW_OUT_DSICWK,
	P_SWEEP_CWK,
};

static stwuct pww_vco wucid_evo_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static const stwuct awpha_pww_config disp_cc_pww0_config = {
	.w = 0xD,
	.awpha = 0x6492,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32AA299C,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww disp_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_weset_wucid_evo_ops,
		},
	},
};

static const stwuct awpha_pww_config disp_cc_pww1_config = {
	.w = 0x1F,
	.awpha = 0x4000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32AA299C,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww disp_cc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_weset_wucid_evo_ops,
		},
	},
};

static const stwuct pawent_map disp_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_DP0_PHY_PWW_WINK_CWK, 1 },
	{ P_DP0_PHY_PWW_VCO_DIV_CWK, 2 },
	{ P_DP3_PHY_PWW_VCO_DIV_CWK, 3 },
	{ P_DP1_PHY_PWW_VCO_DIV_CWK, 4 },
	{ P_DP2_PHY_PWW_VCO_DIV_CWK, 6 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_DP0_PHY_PWW_WINK_CWK },
	{ .index = DT_DP0_PHY_PWW_VCO_DIV_CWK },
	{ .index = DT_DP3_PHY_PWW_VCO_DIV_CWK },
	{ .index = DT_DP1_PHY_PWW_VCO_DIV_CWK },
	{ .index = DT_DP2_PHY_PWW_VCO_DIV_CWK },
};

static const stwuct pawent_map disp_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_1_ao[] = {
	{ .index = DT_BI_TCXO_AO },
};

static const stwuct pawent_map disp_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 2 },
	{ P_DSI1_PHY_PWW_OUT_DSICWK, 3 },
	{ P_DSI1_PHY_PWW_OUT_BYTECWK, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_2[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_DSI0_PHY_PWW_OUT_DSICWK },
	{ .index = DT_DSI0_PHY_PWW_OUT_BYTECWK },
	{ .index = DT_DSI1_PHY_PWW_OUT_DSICWK },
	{ .index = DT_DSI1_PHY_PWW_OUT_BYTECWK },
};

static const stwuct pawent_map disp_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_DP0_PHY_PWW_WINK_CWK, 1 },
	{ P_DP1_PHY_PWW_WINK_CWK, 2 },
	{ P_DP2_PHY_PWW_WINK_CWK, 3 },
	{ P_DP3_PHY_PWW_WINK_CWK, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_3[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_DP0_PHY_PWW_WINK_CWK },
	{ .index = DT_DP1_PHY_PWW_WINK_CWK },
	{ .index = DT_DP2_PHY_PWW_WINK_CWK },
	{ .index = DT_DP3_PHY_PWW_WINK_CWK },
};

static const stwuct pawent_map disp_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 2 },
	{ P_DSI1_PHY_PWW_OUT_BYTECWK, 4 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_4[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_DSI0_PHY_PWW_OUT_BYTECWK },
	{ .index = DT_DSI1_PHY_PWW_OUT_BYTECWK },
};

static const stwuct pawent_map disp_cc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_DISP_CC_PWW0_OUT_MAIN, 1 },
	{ P_DISP_CC_PWW1_OUT_MAIN, 4 },
	{ P_DISP_CC_PWW1_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_5[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &disp_cc_pww0.cwkw.hw },
	{ .hw = &disp_cc_pww1.cwkw.hw },
	{ .hw = &disp_cc_pww1.cwkw.hw },
};

static const stwuct pawent_map disp_cc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_DISP_CC_PWW1_OUT_MAIN, 4 },
	{ P_DISP_CC_PWW1_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_6[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &disp_cc_pww1.cwkw.hw },
	{ .hw = &disp_cc_pww1.cwkw.hw },
};

static const stwuct pawent_map disp_cc_pawent_map_7[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data disp_cc_pawent_data_7[] = {
	{ .index = DT_SWEEP_CWK },
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_DISP_CC_PWW1_OUT_MAIN, 16, 0, 0),
	F(75000000, P_DISP_CC_PWW1_OUT_MAIN, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_ahb_cwk_swc = {
	.cmd_wcgw = 0x8324,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_6,
	.fweq_tbw = ftbw_disp_cc_mdss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_ahb_cwk_swc",
		.pawent_data = disp_cc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_6),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_byte0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_byte0_cwk_swc = {
	.cmd_wcgw = 0x8134,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_byte1_cwk_swc = {
	.cmd_wcgw = 0x8150,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx0_aux_cwk_swc = {
	.cmd_wcgw = 0x81ec,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx0_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_dptx0_wink_cwk_swc[] = {
	F(162000, P_DP0_PHY_PWW_WINK_CWK, 1, 0, 0),
	F(270000, P_DP0_PHY_PWW_WINK_CWK, 1, 0, 0),
	F(540000, P_DP0_PHY_PWW_WINK_CWK, 1, 0, 0),
	F(810000, P_DP0_PHY_PWW_WINK_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx0_wink_cwk_swc = {
	.cmd_wcgw = 0x819c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_dptx0_wink_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx0_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx0_pixew0_cwk_swc = {
	.cmd_wcgw = 0x81bc,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx0_pixew0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx0_pixew1_cwk_swc = {
	.cmd_wcgw = 0x81d4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx0_pixew1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx1_aux_cwk_swc = {
	.cmd_wcgw = 0x8254,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx1_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx1_wink_cwk_swc = {
	.cmd_wcgw = 0x8234,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_dptx0_wink_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx1_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx1_pixew0_cwk_swc = {
	.cmd_wcgw = 0x8204,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx1_pixew0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx1_pixew1_cwk_swc = {
	.cmd_wcgw = 0x821c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx1_pixew1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx2_aux_cwk_swc = {
	.cmd_wcgw = 0x82bc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx2_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx2_wink_cwk_swc = {
	.cmd_wcgw = 0x826c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_dptx0_wink_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx2_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx2_pixew0_cwk_swc = {
	.cmd_wcgw = 0x828c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx2_pixew0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx2_pixew1_cwk_swc = {
	.cmd_wcgw = 0x82a4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx2_pixew1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx3_aux_cwk_swc = {
	.cmd_wcgw = 0x8308,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx3_aux_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx3_wink_cwk_swc = {
	.cmd_wcgw = 0x82ec,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_3,
	.fweq_tbw = ftbw_disp_cc_mdss_dptx0_wink_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx3_wink_cwk_swc",
		.pawent_data = disp_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_dptx3_pixew0_cwk_swc = {
	.cmd_wcgw = 0x82d4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_0,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx3_pixew0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_dp_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_esc0_cwk_swc = {
	.cmd_wcgw = 0x816c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_esc0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_esc1_cwk_swc = {
	.cmd_wcgw = 0x8184,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_4,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_esc1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_mdp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(85714286, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(100000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(150000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(172000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(200000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(325000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(375000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(500000000, P_DISP_CC_PWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_mdp_cwk_swc = {
	.cmd_wcgw = 0x80ec,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_5,
	.fweq_tbw = ftbw_disp_cc_mdss_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_mdp_cwk_swc",
		.pawent_data = disp_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_pcwk0_cwk_swc = {
	.cmd_wcgw = 0x80bc,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_pcwk0_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_pcwk1_cwk_swc = {
	.cmd_wcgw = 0x80d4,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_2,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_pcwk1_cwk_swc",
		.pawent_data = disp_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_mdss_wot_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(150000000, P_DISP_CC_PWW1_OUT_MAIN, 4, 0, 0),
	F(200000000, P_DISP_CC_PWW1_OUT_MAIN, 3, 0, 0),
	F(300000000, P_DISP_CC_PWW1_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_mdss_wot_cwk_swc = {
	.cmd_wcgw = 0x8104,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_5,
	.fweq_tbw = ftbw_disp_cc_mdss_wot_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_wot_cwk_swc",
		.pawent_data = disp_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_mdss_vsync_cwk_swc = {
	.cmd_wcgw = 0x811c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_vsync_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_disp_cc_sweep_cwk_swc[] = {
	F(32000, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 disp_cc_sweep_cwk_swc = {
	.cmd_wcgw = 0xe060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_7,
	.fweq_tbw = ftbw_disp_cc_sweep_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_sweep_cwk_swc",
		.pawent_data = disp_cc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_7),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 disp_cc_xo_cwk_swc = {
	.cmd_wcgw = 0xe044,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = disp_cc_pawent_map_1,
	.fweq_tbw = ftbw_disp_cc_mdss_byte0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_xo_cwk_swc",
		.pawent_data = disp_cc_pawent_data_1_ao,
		.num_pawents = AWWAY_SIZE(disp_cc_pawent_data_1_ao),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_byte0_div_cwk_swc = {
	.weg = 0x814c,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte0_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_byte1_div_cwk_swc = {
	.weg = 0x8168,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_byte1_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_byte1_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_dptx0_wink_div_cwk_swc = {
	.weg = 0x81b4,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx0_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_dptx0_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_dptx1_wink_div_cwk_swc = {
	.weg = 0x824c,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx1_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_dptx1_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_dptx2_wink_div_cwk_swc = {
	.weg = 0x8284,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx2_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_dptx2_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div disp_cc_mdss_dptx3_wink_div_cwk_swc = {
	.weg = 0x8304,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "disp_cc_mdss_dptx3_wink_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&disp_cc_mdss_dptx3_wink_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch disp_cc_mdss_ahb1_cwk = {
	.hawt_weg = 0xa020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_ahb1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_ahb_cwk = {
	.hawt_weg = 0x80a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x80a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_byte0_cwk = {
	.hawt_weg = 0x8028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_byte0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_byte0_intf_cwk = {
	.hawt_weg = 0x802c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x802c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_byte0_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_byte0_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_byte1_cwk = {
	.hawt_weg = 0x8030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_byte1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_byte1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_byte1_intf_cwk = {
	.hawt_weg = 0x8034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_byte1_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_byte1_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_aux_cwk = {
	.hawt_weg = 0x8058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_cwypto_cwk = {
	.hawt_weg = 0x804c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x804c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_wink_cwk = {
	.hawt_weg = 0x8040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_wink_intf_cwk = {
	.hawt_weg = 0x8048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_pixew0_cwk = {
	.hawt_weg = 0x8050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_pixew0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_pixew0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_pixew1_cwk = {
	.hawt_weg = 0x8054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_pixew1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_pixew1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx0_usb_woutew_wink_intf_cwk = {
	.hawt_weg = 0x8044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx0_usb_woutew_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_aux_cwk = {
	.hawt_weg = 0x8074,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8074,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx1_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_cwypto_cwk = {
	.hawt_weg = 0x8070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8070,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx1_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_wink_cwk = {
	.hawt_weg = 0x8064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx1_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_wink_intf_cwk = {
	.hawt_weg = 0x806c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x806c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx1_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_pixew0_cwk = {
	.hawt_weg = 0x805c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x805c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_pixew0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx1_pixew0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_pixew1_cwk = {
	.hawt_weg = 0x8060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_pixew1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx1_pixew1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx1_usb_woutew_wink_intf_cwk = {
	.hawt_weg = 0x8068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx1_usb_woutew_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx0_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx2_aux_cwk = {
	.hawt_weg = 0x808c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x808c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx2_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx2_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx2_cwypto_cwk = {
	.hawt_weg = 0x8088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx2_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx2_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx2_wink_cwk = {
	.hawt_weg = 0x8080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx2_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx2_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx2_wink_intf_cwk = {
	.hawt_weg = 0x8084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx2_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx2_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx2_pixew0_cwk = {
	.hawt_weg = 0x8078,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx2_pixew0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx2_pixew0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx2_pixew1_cwk = {
	.hawt_weg = 0x807c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x807c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx2_pixew1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx2_pixew1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx3_aux_cwk = {
	.hawt_weg = 0x809c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x809c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx3_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx3_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx3_cwypto_cwk = {
	.hawt_weg = 0x80a0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x80a0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx3_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx3_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx3_wink_cwk = {
	.hawt_weg = 0x8094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx3_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx3_wink_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx3_wink_intf_cwk = {
	.hawt_weg = 0x8098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx3_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx3_wink_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_dptx3_pixew0_cwk = {
	.hawt_weg = 0x8090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_dptx3_pixew0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_dptx3_pixew0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_esc0_cwk = {
	.hawt_weg = 0x8038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_esc0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_esc0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_esc1_cwk = {
	.hawt_weg = 0x803c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x803c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_esc1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_esc1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_mdp1_cwk = {
	.hawt_weg = 0xa004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_mdp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_mdp_cwk = {
	.hawt_weg = 0x800c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x800c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_mdp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_mdp_wut1_cwk = {
	.hawt_weg = 0xa014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_mdp_wut1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_mdp_wut_cwk = {
	.hawt_weg = 0x801c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x801c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_mdp_wut_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_non_gdsc_ahb_cwk = {
	.hawt_weg = 0xc004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xc004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_non_gdsc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_pcwk0_cwk = {
	.hawt_weg = 0x8004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_pcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_pcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_pcwk1_cwk = {
	.hawt_weg = 0x8008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_pcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_pcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wot1_cwk = {
	.hawt_weg = 0xa00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_wot1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_wot_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wot_cwk = {
	.hawt_weg = 0x8014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
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

static stwuct cwk_bwanch disp_cc_mdss_wscc_ahb_cwk = {
	.hawt_weg = 0xc00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_wscc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_wscc_vsync_cwk = {
	.hawt_weg = 0xc008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_wscc_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_vsync1_cwk = {
	.hawt_weg = 0xa01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_vsync1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_mdss_vsync_cwk = {
	.hawt_weg = 0x8024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_mdss_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_mdss_vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch disp_cc_sweep_cwk = {
	.hawt_weg = 0xe078,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "disp_cc_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&disp_cc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc mdss_gdsc = {
	.gdscw = 0x9000,
	.pd = {
		.name = "mdss_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
};

static stwuct gdsc mdss_int2_gdsc = {
	.gdscw = 0xb000,
	.pd = {
		.name = "mdss_int2_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
};

static stwuct cwk_wegmap *disp_cc_sm8450_cwocks[] = {
	[DISP_CC_MDSS_AHB1_CWK] = &disp_cc_mdss_ahb1_cwk.cwkw,
	[DISP_CC_MDSS_AHB_CWK] = &disp_cc_mdss_ahb_cwk.cwkw,
	[DISP_CC_MDSS_AHB_CWK_SWC] = &disp_cc_mdss_ahb_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK] = &disp_cc_mdss_byte0_cwk.cwkw,
	[DISP_CC_MDSS_BYTE0_CWK_SWC] = &disp_cc_mdss_byte0_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_DIV_CWK_SWC] = &disp_cc_mdss_byte0_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE0_INTF_CWK] = &disp_cc_mdss_byte0_intf_cwk.cwkw,
	[DISP_CC_MDSS_BYTE1_CWK] = &disp_cc_mdss_byte1_cwk.cwkw,
	[DISP_CC_MDSS_BYTE1_CWK_SWC] = &disp_cc_mdss_byte1_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE1_DIV_CWK_SWC] = &disp_cc_mdss_byte1_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_BYTE1_INTF_CWK] = &disp_cc_mdss_byte1_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_AUX_CWK] = &disp_cc_mdss_dptx0_aux_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_AUX_CWK_SWC] = &disp_cc_mdss_dptx0_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX0_CWYPTO_CWK] = &disp_cc_mdss_dptx0_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_WINK_CWK] = &disp_cc_mdss_dptx0_wink_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_WINK_CWK_SWC] = &disp_cc_mdss_dptx0_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX0_WINK_DIV_CWK_SWC] = &disp_cc_mdss_dptx0_wink_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX0_WINK_INTF_CWK] = &disp_cc_mdss_dptx0_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_PIXEW0_CWK] = &disp_cc_mdss_dptx0_pixew0_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_PIXEW0_CWK_SWC] = &disp_cc_mdss_dptx0_pixew0_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX0_PIXEW1_CWK] = &disp_cc_mdss_dptx0_pixew1_cwk.cwkw,
	[DISP_CC_MDSS_DPTX0_PIXEW1_CWK_SWC] = &disp_cc_mdss_dptx0_pixew1_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX0_USB_WOUTEW_WINK_INTF_CWK] =
		&disp_cc_mdss_dptx0_usb_woutew_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_AUX_CWK] = &disp_cc_mdss_dptx1_aux_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_AUX_CWK_SWC] = &disp_cc_mdss_dptx1_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX1_CWYPTO_CWK] = &disp_cc_mdss_dptx1_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_WINK_CWK] = &disp_cc_mdss_dptx1_wink_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_WINK_CWK_SWC] = &disp_cc_mdss_dptx1_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX1_WINK_DIV_CWK_SWC] = &disp_cc_mdss_dptx1_wink_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX1_WINK_INTF_CWK] = &disp_cc_mdss_dptx1_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_PIXEW0_CWK] = &disp_cc_mdss_dptx1_pixew0_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_PIXEW0_CWK_SWC] = &disp_cc_mdss_dptx1_pixew0_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX1_PIXEW1_CWK] = &disp_cc_mdss_dptx1_pixew1_cwk.cwkw,
	[DISP_CC_MDSS_DPTX1_PIXEW1_CWK_SWC] = &disp_cc_mdss_dptx1_pixew1_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX1_USB_WOUTEW_WINK_INTF_CWK] =
		&disp_cc_mdss_dptx1_usb_woutew_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_AUX_CWK] = &disp_cc_mdss_dptx2_aux_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_AUX_CWK_SWC] = &disp_cc_mdss_dptx2_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX2_CWYPTO_CWK] = &disp_cc_mdss_dptx2_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_WINK_CWK] = &disp_cc_mdss_dptx2_wink_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_WINK_CWK_SWC] = &disp_cc_mdss_dptx2_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX2_WINK_DIV_CWK_SWC] = &disp_cc_mdss_dptx2_wink_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX2_WINK_INTF_CWK] = &disp_cc_mdss_dptx2_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_PIXEW0_CWK] = &disp_cc_mdss_dptx2_pixew0_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_PIXEW0_CWK_SWC] = &disp_cc_mdss_dptx2_pixew0_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX2_PIXEW1_CWK] = &disp_cc_mdss_dptx2_pixew1_cwk.cwkw,
	[DISP_CC_MDSS_DPTX2_PIXEW1_CWK_SWC] = &disp_cc_mdss_dptx2_pixew1_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX3_AUX_CWK] = &disp_cc_mdss_dptx3_aux_cwk.cwkw,
	[DISP_CC_MDSS_DPTX3_AUX_CWK_SWC] = &disp_cc_mdss_dptx3_aux_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX3_CWYPTO_CWK] = &disp_cc_mdss_dptx3_cwypto_cwk.cwkw,
	[DISP_CC_MDSS_DPTX3_WINK_CWK] = &disp_cc_mdss_dptx3_wink_cwk.cwkw,
	[DISP_CC_MDSS_DPTX3_WINK_CWK_SWC] = &disp_cc_mdss_dptx3_wink_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX3_WINK_DIV_CWK_SWC] = &disp_cc_mdss_dptx3_wink_div_cwk_swc.cwkw,
	[DISP_CC_MDSS_DPTX3_WINK_INTF_CWK] = &disp_cc_mdss_dptx3_wink_intf_cwk.cwkw,
	[DISP_CC_MDSS_DPTX3_PIXEW0_CWK] = &disp_cc_mdss_dptx3_pixew0_cwk.cwkw,
	[DISP_CC_MDSS_DPTX3_PIXEW0_CWK_SWC] = &disp_cc_mdss_dptx3_pixew0_cwk_swc.cwkw,
	[DISP_CC_MDSS_ESC0_CWK] = &disp_cc_mdss_esc0_cwk.cwkw,
	[DISP_CC_MDSS_ESC0_CWK_SWC] = &disp_cc_mdss_esc0_cwk_swc.cwkw,
	[DISP_CC_MDSS_ESC1_CWK] = &disp_cc_mdss_esc1_cwk.cwkw,
	[DISP_CC_MDSS_ESC1_CWK_SWC] = &disp_cc_mdss_esc1_cwk_swc.cwkw,
	[DISP_CC_MDSS_MDP1_CWK] = &disp_cc_mdss_mdp1_cwk.cwkw,
	[DISP_CC_MDSS_MDP_CWK] = &disp_cc_mdss_mdp_cwk.cwkw,
	[DISP_CC_MDSS_MDP_CWK_SWC] = &disp_cc_mdss_mdp_cwk_swc.cwkw,
	[DISP_CC_MDSS_MDP_WUT1_CWK] = &disp_cc_mdss_mdp_wut1_cwk.cwkw,
	[DISP_CC_MDSS_MDP_WUT_CWK] = &disp_cc_mdss_mdp_wut_cwk.cwkw,
	[DISP_CC_MDSS_NON_GDSC_AHB_CWK] = &disp_cc_mdss_non_gdsc_ahb_cwk.cwkw,
	[DISP_CC_MDSS_PCWK0_CWK] = &disp_cc_mdss_pcwk0_cwk.cwkw,
	[DISP_CC_MDSS_PCWK0_CWK_SWC] = &disp_cc_mdss_pcwk0_cwk_swc.cwkw,
	[DISP_CC_MDSS_PCWK1_CWK] = &disp_cc_mdss_pcwk1_cwk.cwkw,
	[DISP_CC_MDSS_PCWK1_CWK_SWC] = &disp_cc_mdss_pcwk1_cwk_swc.cwkw,
	[DISP_CC_MDSS_WOT1_CWK] = &disp_cc_mdss_wot1_cwk.cwkw,
	[DISP_CC_MDSS_WOT_CWK] = &disp_cc_mdss_wot_cwk.cwkw,
	[DISP_CC_MDSS_WOT_CWK_SWC] = &disp_cc_mdss_wot_cwk_swc.cwkw,
	[DISP_CC_MDSS_WSCC_AHB_CWK] = &disp_cc_mdss_wscc_ahb_cwk.cwkw,
	[DISP_CC_MDSS_WSCC_VSYNC_CWK] = &disp_cc_mdss_wscc_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC1_CWK] = &disp_cc_mdss_vsync1_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK] = &disp_cc_mdss_vsync_cwk.cwkw,
	[DISP_CC_MDSS_VSYNC_CWK_SWC] = &disp_cc_mdss_vsync_cwk_swc.cwkw,
	[DISP_CC_PWW0] = &disp_cc_pww0.cwkw,
	[DISP_CC_PWW1] = &disp_cc_pww1.cwkw,
	[DISP_CC_SWEEP_CWK] = &disp_cc_sweep_cwk.cwkw,
	[DISP_CC_SWEEP_CWK_SWC] = &disp_cc_sweep_cwk_swc.cwkw,
	[DISP_CC_XO_CWK_SWC] = &disp_cc_xo_cwk_swc.cwkw,
};

static const stwuct qcom_weset_map disp_cc_sm8450_wesets[] = {
	[DISP_CC_MDSS_COWE_BCW] = { 0x8000 },
	[DISP_CC_MDSS_COWE_INT2_BCW] = { 0xa000 },
	[DISP_CC_MDSS_WSCC_BCW] = { 0xc000 },
};

static stwuct gdsc *disp_cc_sm8450_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
	[MDSS_INT2_GDSC] = &mdss_int2_gdsc,
};

static const stwuct wegmap_config disp_cc_sm8450_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x11008,
	.fast_io = twue,
};

static stwuct qcom_cc_desc disp_cc_sm8450_desc = {
	.config = &disp_cc_sm8450_wegmap_config,
	.cwks = disp_cc_sm8450_cwocks,
	.num_cwks = AWWAY_SIZE(disp_cc_sm8450_cwocks),
	.wesets = disp_cc_sm8450_wesets,
	.num_wesets = AWWAY_SIZE(disp_cc_sm8450_wesets),
	.gdscs = disp_cc_sm8450_gdscs,
	.num_gdscs = AWWAY_SIZE(disp_cc_sm8450_gdscs),
};

static const stwuct of_device_id disp_cc_sm8450_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8450-dispcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, disp_cc_sm8450_match_tabwe);

static int disp_cc_sm8450_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wegmap = qcom_cc_map(pdev, &disp_cc_sm8450_desc);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto eww_put_wpm;
	}

	cwk_wucid_evo_pww_configuwe(&disp_cc_pww0, wegmap, &disp_cc_pww0_config);
	cwk_wucid_evo_pww_configuwe(&disp_cc_pww1, wegmap, &disp_cc_pww1_config);

	/* Enabwe cwock gating fow MDP cwocks */
	wegmap_update_bits(wegmap, DISP_CC_MISC_CMD, 0x10, 0x10);

	/*
	 * Keep cwocks awways enabwed:
	 *	disp_cc_xo_cwk
	 */
	wegmap_update_bits(wegmap, 0xe05c, BIT(0), BIT(0));

	wet = qcom_cc_weawwy_pwobe(pdev, &disp_cc_sm8450_desc, wegmap);
	if (wet)
		goto eww_put_wpm;

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

eww_put_wpm:
	pm_wuntime_put_sync(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew disp_cc_sm8450_dwivew = {
	.pwobe = disp_cc_sm8450_pwobe,
	.dwivew = {
		.name = "disp_cc-sm8450",
		.of_match_tabwe = disp_cc_sm8450_match_tabwe,
	},
};

static int __init disp_cc_sm8450_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&disp_cc_sm8450_dwivew);
}
subsys_initcaww(disp_cc_sm8450_init);

static void __exit disp_cc_sm8450_exit(void)
{
	pwatfowm_dwivew_unwegistew(&disp_cc_sm8450_dwivew);
}
moduwe_exit(disp_cc_sm8450_exit);

MODUWE_DESCWIPTION("QTI DISPCC SM8450 Dwivew");
MODUWE_WICENSE("GPW");
