// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm8450-camcc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	DT_IFACE,
	DT_BI_TCXO,
	DT_BI_TCXO_AO,
	DT_SWEEP_CWK
};

enum {
	P_BI_TCXO,
	P_CAM_CC_PWW0_OUT_EVEN,
	P_CAM_CC_PWW0_OUT_MAIN,
	P_CAM_CC_PWW0_OUT_ODD,
	P_CAM_CC_PWW1_OUT_EVEN,
	P_CAM_CC_PWW2_OUT_EVEN,
	P_CAM_CC_PWW2_OUT_MAIN,
	P_CAM_CC_PWW3_OUT_EVEN,
	P_CAM_CC_PWW4_OUT_EVEN,
	P_CAM_CC_PWW5_OUT_EVEN,
	P_CAM_CC_PWW6_OUT_EVEN,
	P_CAM_CC_PWW7_OUT_EVEN,
	P_CAM_CC_PWW8_OUT_EVEN,
	P_SWEEP_CWK,
};

static const stwuct pww_vco wucid_evo_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static const stwuct pww_vco wivian_evo_vco[] = {
	{ 864000000, 1056000000, 0 },
};

static const stwuct cwk_pawent_data pww_pawent_data_tcxo = { .index = DT_BI_TCXO };

static const stwuct awpha_pww_config cam_cc_pww0_config = {
	.w = 0x3e,
	.awpha = 0x8000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00008400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww0",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww0_out_odd[] = {
	{ 0x2, 3 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_odd = {
	.offset = 0x0,
	.post_div_shift = 14,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww0_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww0_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww0_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww1_config = {
	.w = 0x25,
	.awpha = 0xeaaa,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww1",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww1_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww1_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww1_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww2_config = {
	.w = 0x32,
	.awpha = 0x0,
	.config_ctw_vaw = 0x90008820,
	.config_ctw_hi_vaw = 0x00890263,
	.config_ctw_hi1_vaw = 0x00000217,
};

static stwuct cwk_awpha_pww cam_cc_pww2 = {
	.offset = 0x2000,
	.vco_tabwe = wivian_evo_vco,
	.num_vco = AWWAY_SIZE(wivian_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WIVIAN_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww2",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wivian_evo_ops,
		},
	},
};

static const stwuct awpha_pww_config cam_cc_pww3_config = {
	.w = 0x2d,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww3 = {
	.offset = 0x3000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww3",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww3_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww3_out_even = {
	.offset = 0x3000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww3_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww3_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww3_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww3.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww4_config = {
	.w = 0x2d,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww4 = {
	.offset = 0x4000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww4",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww4_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww4_out_even = {
	.offset = 0x4000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww4_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww4_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww4_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww4.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww5_config = {
	.w = 0x2d,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww5 = {
	.offset = 0x5000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww5",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww5_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww5_out_even = {
	.offset = 0x5000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww5_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww5_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww5_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww5.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww6_config = {
	.w = 0x2d,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww6 = {
	.offset = 0x6000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww6",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww6_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww6_out_even = {
	.offset = 0x6000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww6_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww6_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww6_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww6.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww7_config = {
	.w = 0x2d,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww7 = {
	.offset = 0x7000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww7",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww7_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww7_out_even = {
	.offset = 0x7000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww7_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww7_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww7_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww7.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww8_config = {
	.w = 0x32,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x32aa299c,
	.usew_ctw_vaw = 0x00000400,
	.usew_ctw_hi_vaw = 0x00000805,
};

static stwuct cwk_awpha_pww cam_cc_pww8 = {
	.offset = 0x8000,
	.vco_tabwe = wucid_evo_vco,
	.num_vco = AWWAY_SIZE(wucid_evo_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_pww8",
			.pawent_data = &pww_pawent_data_tcxo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww8_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww8_out_even = {
	.offset = 0x8000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww8_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww8_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_pww8_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww8.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct pawent_map cam_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW0_OUT_MAIN, 1 },
	{ P_CAM_CC_PWW0_OUT_EVEN, 2 },
	{ P_CAM_CC_PWW0_OUT_ODD, 3 },
	{ P_CAM_CC_PWW8_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww0.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_odd.cwkw.hw },
	{ .hw = &cam_cc_pww8_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW2_OUT_EVEN, 3 },
	{ P_CAM_CC_PWW2_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww2.cwkw.hw },
	{ .hw = &cam_cc_pww2.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_2[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww3_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW4_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_3[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww4_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW5_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_4[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww5_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW1_OUT_EVEN, 4 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_5[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww1_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW6_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_6[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww6_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW7_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_7[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &cam_cc_pww7_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_8[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_8[] = {
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map cam_cc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_9_ao[] = {
	{ .index = DT_BI_TCXO_AO, .name = "bi_tcxo_ao" },
};

static const stwuct fweq_tbw ftbw_cam_cc_bps_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_ODD, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW8_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_bps_cwk_swc = {
	.cmd_wcgw = 0x10050,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_bps_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_camnoc_axi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_camnoc_axi_cwk_swc = {
	.cmd_wcgw = 0x13194,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_camnoc_axi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_camnoc_axi_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cci_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_CAM_CC_PWW0_OUT_EVEN, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cci_0_cwk_swc = {
	.cmd_wcgw = 0x1312c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_cci_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_cci_1_cwk_swc = {
	.cmd_wcgw = 0x13148,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_cci_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cphy_wx_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(480000000, P_CAM_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0x1104c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_cphy_wx_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_csi0phytimew_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x150e0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csi0phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0x15104,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csi1phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0x15124,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csi2phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi3phytimew_cwk_swc = {
	.cmd_wcgw = 0x1514c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csi3phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi4phytimew_cwk_swc = {
	.cmd_wcgw = 0x1516c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csi4phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi5phytimew_cwk_swc = {
	.cmd_wcgw = 0x1518c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csi5phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_csid_cwk_swc[] = {
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(480000000, P_CAM_CC_PWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_csid_cwk_swc = {
	.cmd_wcgw = 0x13174,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csid_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_fast_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_fast_ahb_cwk_swc = {
	.cmd_wcgw = 0x10018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fast_ahb_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_fast_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_icp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW8_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_icp_cwk_swc = {
	.cmd_wcgw = 0x13108,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_icp_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_icp_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(432000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(594000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(675000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(727000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_cwk_swc = {
	.cmd_wcgw = 0x11018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_ife_0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_ife_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(432000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(594000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(675000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(727000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_1_cwk_swc = {
	.cmd_wcgw = 0x12018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_3,
	.fweq_tbw = ftbw_cam_cc_ife_1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_ife_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_2_cwk_swc[] = {
	F(432000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	F(594000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	F(675000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	F(727000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_2_cwk_swc = {
	.cmd_wcgw = 0x12064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_4,
	.fweq_tbw = ftbw_cam_cc_ife_2_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_ife_2_cwk_swc",
		.pawent_data = cam_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_wite_cwk_swc[] = {
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW8_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_wite_cwk_swc = {
	.cmd_wcgw = 0x13000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_wite_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_ife_wite_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_csid_cwk_swc = {
	.cmd_wcgw = 0x13024,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_wite_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_ife_wite_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ipe_nps_cwk_swc[] = {
	F(364000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(500000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(700000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ipe_nps_cwk_swc = {
	.cmd_wcgw = 0x1008c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_5,
	.fweq_tbw = ftbw_cam_cc_ipe_nps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_ipe_nps_cwk_swc",
		.pawent_data = cam_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_jpeg_cwk_swc = {
	.cmd_wcgw = 0x130dc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_jpeg_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_mcwk0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_CAM_CC_PWW2_OUT_MAIN, 10, 1, 4),
	F(68571429, P_CAM_CC_PWW2_OUT_MAIN, 14, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x15000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x1501c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x15038,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk2_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x15054,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk3_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk4_cwk_swc = {
	.cmd_wcgw = 0x15070,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk4_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk5_cwk_swc = {
	.cmd_wcgw = 0x1508c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk5_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk6_cwk_swc = {
	.cmd_wcgw = 0x150a8,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk6_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk7_cwk_swc = {
	.cmd_wcgw = 0x150c4,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_mcwk7_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_qdss_debug_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_CAM_CC_PWW0_OUT_EVEN, 8, 0, 0),
	F(150000000, P_CAM_CC_PWW0_OUT_EVEN, 4, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_qdss_debug_cwk_swc = {
	.cmd_wcgw = 0x131bc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_qdss_debug_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_qdss_debug_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_sfe_0_cwk_swc[] = {
	F(432000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	F(594000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	F(675000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	F(727000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_sfe_0_cwk_swc = {
	.cmd_wcgw = 0x13064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_6,
	.fweq_tbw = ftbw_cam_cc_sfe_0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_sfe_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_6),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_sfe_1_cwk_swc[] = {
	F(432000000, P_CAM_CC_PWW7_OUT_EVEN, 1, 0, 0),
	F(594000000, P_CAM_CC_PWW7_OUT_EVEN, 1, 0, 0),
	F(675000000, P_CAM_CC_PWW7_OUT_EVEN, 1, 0, 0),
	F(727000000, P_CAM_CC_PWW7_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_sfe_1_cwk_swc = {
	.cmd_wcgw = 0x130ac,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_7,
	.fweq_tbw = ftbw_cam_cc_sfe_1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_sfe_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_7),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_sweep_cwk_swc[] = {
	F(32000, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_sweep_cwk_swc = {
	.cmd_wcgw = 0x13210,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_8,
	.fweq_tbw = ftbw_cam_cc_sweep_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_sweep_cwk_swc",
		.pawent_data = cam_cc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_8),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_swow_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(80000000, P_CAM_CC_PWW0_OUT_EVEN, 7.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_swow_ahb_cwk_swc = {
	.cmd_wcgw = 0x10034,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_swow_ahb_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_swow_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_xo_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_xo_cwk_swc = {
	.cmd_wcgw = 0x131f4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_9,
	.fweq_tbw = ftbw_cam_cc_xo_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "cam_cc_xo_cwk_swc",
		.pawent_data = cam_cc_pawent_data_9_ao,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_9_ao),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch cam_cc_gdsc_cwk = {
	.hawt_weg = 0x1320c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1320c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_gdsc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_ahb_cwk = {
	.hawt_weg = 0x1004c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1004c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_bps_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_cwk = {
	.hawt_weg = 0x10068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_bps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_bps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_fast_ahb_cwk = {
	.hawt_weg = 0x10030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_bps_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_camnoc_axi_cwk = {
	.hawt_weg = 0x131ac,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x131ac,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_camnoc_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_camnoc_dcd_xo_cwk = {
	.hawt_weg = 0x131b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x131b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_camnoc_dcd_xo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cci_0_cwk = {
	.hawt_weg = 0x13144,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13144,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cci_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cci_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cci_1_cwk = {
	.hawt_weg = 0x13160,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13160,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cci_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cci_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cowe_ahb_cwk = {
	.hawt_weg = 0x131f0,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x131f0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cowe_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ahb_cwk = {
	.hawt_weg = 0x13164,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13164,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_bps_cwk = {
	.hawt_weg = 0x10070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10070,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_bps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_bps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_fast_ahb_cwk = {
	.hawt_weg = 0x1316c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1316c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ife_0_cwk = {
	.hawt_weg = 0x11038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ife_1_cwk = {
	.hawt_weg = 0x12038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ife_2_cwk = {
	.hawt_weg = 0x12084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12084,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_ife_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ife_wite_cwk = {
	.hawt_weg = 0x13020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_ife_wite_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ipe_nps_cwk = {
	.hawt_weg = 0x100ac,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100ac,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_ipe_nps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ipe_nps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_sbi_cwk = {
	.hawt_weg = 0x100ec,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100ec,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_sbi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_sfe_0_cwk = {
	.hawt_weg = 0x13084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13084,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_sfe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_sfe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_sfe_1_cwk = {
	.hawt_weg = 0x130cc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x130cc,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_cpas_sfe_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_sfe_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi0phytimew_cwk = {
	.hawt_weg = 0x150f8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x150f8,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csi0phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi1phytimew_cwk = {
	.hawt_weg = 0x1511c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1511c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csi1phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi2phytimew_cwk = {
	.hawt_weg = 0x1513c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1513c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csi2phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi3phytimew_cwk = {
	.hawt_weg = 0x15164,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15164,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csi3phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csi3phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi4phytimew_cwk = {
	.hawt_weg = 0x15184,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15184,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csi4phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csi4phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi5phytimew_cwk = {
	.hawt_weg = 0x151a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x151a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csi5phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csi5phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csid_cwk = {
	.hawt_weg = 0x1318c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1318c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csid_csiphy_wx_cwk = {
	.hawt_weg = 0x15100,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15100,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csid_csiphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy0_cwk = {
	.hawt_weg = 0x150fc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x150fc,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy1_cwk = {
	.hawt_weg = 0x15120,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15120,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy2_cwk = {
	.hawt_weg = 0x15140,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15140,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy3_cwk = {
	.hawt_weg = 0x15168,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15168,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csiphy3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy4_cwk = {
	.hawt_weg = 0x15188,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15188,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csiphy4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy5_cwk = {
	.hawt_weg = 0x151a8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x151a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_csiphy5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_ahb_cwk = {
	.hawt_weg = 0x13128,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13128,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_icp_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_cwk = {
	.hawt_weg = 0x13120,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13120,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_icp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_icp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_cwk = {
	.hawt_weg = 0x11030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_dsp_cwk = {
	.hawt_weg = 0x1103c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1103c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_0_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_fast_ahb_cwk = {
	.hawt_weg = 0x11048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_0_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_cwk = {
	.hawt_weg = 0x12030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_dsp_cwk = {
	.hawt_weg = 0x1203c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_1_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_fast_ahb_cwk = {
	.hawt_weg = 0x12048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_1_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_2_cwk = {
	.hawt_weg = 0x1207c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1207c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_2_dsp_cwk = {
	.hawt_weg = 0x12088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12088,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_2_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_2_fast_ahb_cwk = {
	.hawt_weg = 0x12094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12094,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_2_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_ahb_cwk = {
	.hawt_weg = 0x13048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_wite_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_cwk = {
	.hawt_weg = 0x13018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_wite_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_cphy_wx_cwk = {
	.hawt_weg = 0x13044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13044,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_wite_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_csid_cwk = {
	.hawt_weg = 0x1303c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1303c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ife_wite_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_nps_ahb_cwk = {
	.hawt_weg = 0x100c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ipe_nps_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_nps_cwk = {
	.hawt_weg = 0x100a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ipe_nps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ipe_nps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_nps_fast_ahb_cwk = {
	.hawt_weg = 0x100c4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100c4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ipe_nps_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_pps_cwk = {
	.hawt_weg = 0x100b0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100b0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ipe_pps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ipe_nps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_pps_fast_ahb_cwk = {
	.hawt_weg = 0x100c8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100c8,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_ipe_pps_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_jpeg_cwk = {
	.hawt_weg = 0x130f4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x130f4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_jpeg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_jpeg_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk0_cwk = {
	.hawt_weg = 0x15018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk1_cwk = {
	.hawt_weg = 0x15034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15034,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk2_cwk = {
	.hawt_weg = 0x15050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15050,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk3_cwk = {
	.hawt_weg = 0x1506c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1506c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk4_cwk = {
	.hawt_weg = 0x15088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15088,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk5_cwk = {
	.hawt_weg = 0x150a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x150a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk6_cwk = {
	.hawt_weg = 0x150c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x150c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk7_cwk = {
	.hawt_weg = 0x150dc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x150dc,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_mcwk7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_mcwk7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_qdss_debug_cwk = {
	.hawt_weg = 0x131d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x131d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_qdss_debug_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_qdss_debug_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_qdss_debug_xo_cwk = {
	.hawt_weg = 0x131d8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x131d8,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_qdss_debug_xo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_ahb_cwk = {
	.hawt_weg = 0x100f0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100f0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sbi_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_cwk = {
	.hawt_weg = 0x100e4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x100e4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sbi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sfe_0_cwk = {
	.hawt_weg = 0x1307c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1307c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sfe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_sfe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sfe_0_fast_ahb_cwk = {
	.hawt_weg = 0x13090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13090,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sfe_0_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sfe_1_cwk = {
	.hawt_weg = 0x130c4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x130c4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sfe_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_sfe_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sfe_1_fast_ahb_cwk = {
	.hawt_weg = 0x130d8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x130d8,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sfe_1_fast_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sweep_cwk = {
	.hawt_weg = 0x13228,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13228,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "cam_cc_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap *cam_cc_sm8450_cwocks[] = {
	[CAM_CC_BPS_AHB_CWK] = &cam_cc_bps_ahb_cwk.cwkw,
	[CAM_CC_BPS_CWK] = &cam_cc_bps_cwk.cwkw,
	[CAM_CC_BPS_CWK_SWC] = &cam_cc_bps_cwk_swc.cwkw,
	[CAM_CC_BPS_FAST_AHB_CWK] = &cam_cc_bps_fast_ahb_cwk.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK] = &cam_cc_camnoc_axi_cwk.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK_SWC] = &cam_cc_camnoc_axi_cwk_swc.cwkw,
	[CAM_CC_CAMNOC_DCD_XO_CWK] = &cam_cc_camnoc_dcd_xo_cwk.cwkw,
	[CAM_CC_CCI_0_CWK] = &cam_cc_cci_0_cwk.cwkw,
	[CAM_CC_CCI_0_CWK_SWC] = &cam_cc_cci_0_cwk_swc.cwkw,
	[CAM_CC_CCI_1_CWK] = &cam_cc_cci_1_cwk.cwkw,
	[CAM_CC_CCI_1_CWK_SWC] = &cam_cc_cci_1_cwk_swc.cwkw,
	[CAM_CC_COWE_AHB_CWK] = &cam_cc_cowe_ahb_cwk.cwkw,
	[CAM_CC_CPAS_AHB_CWK] = &cam_cc_cpas_ahb_cwk.cwkw,
	[CAM_CC_CPAS_BPS_CWK] = &cam_cc_cpas_bps_cwk.cwkw,
	[CAM_CC_CPAS_FAST_AHB_CWK] = &cam_cc_cpas_fast_ahb_cwk.cwkw,
	[CAM_CC_CPAS_IFE_0_CWK] = &cam_cc_cpas_ife_0_cwk.cwkw,
	[CAM_CC_CPAS_IFE_1_CWK] = &cam_cc_cpas_ife_1_cwk.cwkw,
	[CAM_CC_CPAS_IFE_2_CWK] = &cam_cc_cpas_ife_2_cwk.cwkw,
	[CAM_CC_CPAS_IFE_WITE_CWK] = &cam_cc_cpas_ife_wite_cwk.cwkw,
	[CAM_CC_CPAS_IPE_NPS_CWK] = &cam_cc_cpas_ipe_nps_cwk.cwkw,
	[CAM_CC_CPAS_SBI_CWK] = &cam_cc_cpas_sbi_cwk.cwkw,
	[CAM_CC_CPAS_SFE_0_CWK] = &cam_cc_cpas_sfe_0_cwk.cwkw,
	[CAM_CC_CPAS_SFE_1_CWK] = &cam_cc_cpas_sfe_1_cwk.cwkw,
	[CAM_CC_CPHY_WX_CWK_SWC] = &cam_cc_cphy_wx_cwk_swc.cwkw,
	[CAM_CC_CSI0PHYTIMEW_CWK] = &cam_cc_csi0phytimew_cwk.cwkw,
	[CAM_CC_CSI0PHYTIMEW_CWK_SWC] = &cam_cc_csi0phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI1PHYTIMEW_CWK] = &cam_cc_csi1phytimew_cwk.cwkw,
	[CAM_CC_CSI1PHYTIMEW_CWK_SWC] = &cam_cc_csi1phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI2PHYTIMEW_CWK] = &cam_cc_csi2phytimew_cwk.cwkw,
	[CAM_CC_CSI2PHYTIMEW_CWK_SWC] = &cam_cc_csi2phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI3PHYTIMEW_CWK] = &cam_cc_csi3phytimew_cwk.cwkw,
	[CAM_CC_CSI3PHYTIMEW_CWK_SWC] = &cam_cc_csi3phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI4PHYTIMEW_CWK] = &cam_cc_csi4phytimew_cwk.cwkw,
	[CAM_CC_CSI4PHYTIMEW_CWK_SWC] = &cam_cc_csi4phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI5PHYTIMEW_CWK] = &cam_cc_csi5phytimew_cwk.cwkw,
	[CAM_CC_CSI5PHYTIMEW_CWK_SWC] = &cam_cc_csi5phytimew_cwk_swc.cwkw,
	[CAM_CC_CSID_CWK] = &cam_cc_csid_cwk.cwkw,
	[CAM_CC_CSID_CWK_SWC] = &cam_cc_csid_cwk_swc.cwkw,
	[CAM_CC_CSID_CSIPHY_WX_CWK] = &cam_cc_csid_csiphy_wx_cwk.cwkw,
	[CAM_CC_CSIPHY0_CWK] = &cam_cc_csiphy0_cwk.cwkw,
	[CAM_CC_CSIPHY1_CWK] = &cam_cc_csiphy1_cwk.cwkw,
	[CAM_CC_CSIPHY2_CWK] = &cam_cc_csiphy2_cwk.cwkw,
	[CAM_CC_CSIPHY3_CWK] = &cam_cc_csiphy3_cwk.cwkw,
	[CAM_CC_CSIPHY4_CWK] = &cam_cc_csiphy4_cwk.cwkw,
	[CAM_CC_CSIPHY5_CWK] = &cam_cc_csiphy5_cwk.cwkw,
	[CAM_CC_FAST_AHB_CWK_SWC] = &cam_cc_fast_ahb_cwk_swc.cwkw,
	[CAM_CC_GDSC_CWK] = &cam_cc_gdsc_cwk.cwkw,
	[CAM_CC_ICP_AHB_CWK] = &cam_cc_icp_ahb_cwk.cwkw,
	[CAM_CC_ICP_CWK] = &cam_cc_icp_cwk.cwkw,
	[CAM_CC_ICP_CWK_SWC] = &cam_cc_icp_cwk_swc.cwkw,
	[CAM_CC_IFE_0_CWK] = &cam_cc_ife_0_cwk.cwkw,
	[CAM_CC_IFE_0_CWK_SWC] = &cam_cc_ife_0_cwk_swc.cwkw,
	[CAM_CC_IFE_0_DSP_CWK] = &cam_cc_ife_0_dsp_cwk.cwkw,
	[CAM_CC_IFE_0_FAST_AHB_CWK] = &cam_cc_ife_0_fast_ahb_cwk.cwkw,
	[CAM_CC_IFE_1_CWK] = &cam_cc_ife_1_cwk.cwkw,
	[CAM_CC_IFE_1_CWK_SWC] = &cam_cc_ife_1_cwk_swc.cwkw,
	[CAM_CC_IFE_1_DSP_CWK] = &cam_cc_ife_1_dsp_cwk.cwkw,
	[CAM_CC_IFE_1_FAST_AHB_CWK] = &cam_cc_ife_1_fast_ahb_cwk.cwkw,
	[CAM_CC_IFE_2_CWK] = &cam_cc_ife_2_cwk.cwkw,
	[CAM_CC_IFE_2_CWK_SWC] = &cam_cc_ife_2_cwk_swc.cwkw,
	[CAM_CC_IFE_2_DSP_CWK] = &cam_cc_ife_2_dsp_cwk.cwkw,
	[CAM_CC_IFE_2_FAST_AHB_CWK] = &cam_cc_ife_2_fast_ahb_cwk.cwkw,
	[CAM_CC_IFE_WITE_AHB_CWK] = &cam_cc_ife_wite_ahb_cwk.cwkw,
	[CAM_CC_IFE_WITE_CWK] = &cam_cc_ife_wite_cwk.cwkw,
	[CAM_CC_IFE_WITE_CWK_SWC] = &cam_cc_ife_wite_cwk_swc.cwkw,
	[CAM_CC_IFE_WITE_CPHY_WX_CWK] = &cam_cc_ife_wite_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_WITE_CSID_CWK] = &cam_cc_ife_wite_csid_cwk.cwkw,
	[CAM_CC_IFE_WITE_CSID_CWK_SWC] = &cam_cc_ife_wite_csid_cwk_swc.cwkw,
	[CAM_CC_IPE_NPS_AHB_CWK] = &cam_cc_ipe_nps_ahb_cwk.cwkw,
	[CAM_CC_IPE_NPS_CWK] = &cam_cc_ipe_nps_cwk.cwkw,
	[CAM_CC_IPE_NPS_CWK_SWC] = &cam_cc_ipe_nps_cwk_swc.cwkw,
	[CAM_CC_IPE_NPS_FAST_AHB_CWK] = &cam_cc_ipe_nps_fast_ahb_cwk.cwkw,
	[CAM_CC_IPE_PPS_CWK] = &cam_cc_ipe_pps_cwk.cwkw,
	[CAM_CC_IPE_PPS_FAST_AHB_CWK] = &cam_cc_ipe_pps_fast_ahb_cwk.cwkw,
	[CAM_CC_JPEG_CWK] = &cam_cc_jpeg_cwk.cwkw,
	[CAM_CC_JPEG_CWK_SWC] = &cam_cc_jpeg_cwk_swc.cwkw,
	[CAM_CC_MCWK0_CWK] = &cam_cc_mcwk0_cwk.cwkw,
	[CAM_CC_MCWK0_CWK_SWC] = &cam_cc_mcwk0_cwk_swc.cwkw,
	[CAM_CC_MCWK1_CWK] = &cam_cc_mcwk1_cwk.cwkw,
	[CAM_CC_MCWK1_CWK_SWC] = &cam_cc_mcwk1_cwk_swc.cwkw,
	[CAM_CC_MCWK2_CWK] = &cam_cc_mcwk2_cwk.cwkw,
	[CAM_CC_MCWK2_CWK_SWC] = &cam_cc_mcwk2_cwk_swc.cwkw,
	[CAM_CC_MCWK3_CWK] = &cam_cc_mcwk3_cwk.cwkw,
	[CAM_CC_MCWK3_CWK_SWC] = &cam_cc_mcwk3_cwk_swc.cwkw,
	[CAM_CC_MCWK4_CWK] = &cam_cc_mcwk4_cwk.cwkw,
	[CAM_CC_MCWK4_CWK_SWC] = &cam_cc_mcwk4_cwk_swc.cwkw,
	[CAM_CC_MCWK5_CWK] = &cam_cc_mcwk5_cwk.cwkw,
	[CAM_CC_MCWK5_CWK_SWC] = &cam_cc_mcwk5_cwk_swc.cwkw,
	[CAM_CC_MCWK6_CWK] = &cam_cc_mcwk6_cwk.cwkw,
	[CAM_CC_MCWK6_CWK_SWC] = &cam_cc_mcwk6_cwk_swc.cwkw,
	[CAM_CC_MCWK7_CWK] = &cam_cc_mcwk7_cwk.cwkw,
	[CAM_CC_MCWK7_CWK_SWC] = &cam_cc_mcwk7_cwk_swc.cwkw,
	[CAM_CC_PWW0] = &cam_cc_pww0.cwkw,
	[CAM_CC_PWW0_OUT_EVEN] = &cam_cc_pww0_out_even.cwkw,
	[CAM_CC_PWW0_OUT_ODD] = &cam_cc_pww0_out_odd.cwkw,
	[CAM_CC_PWW1] = &cam_cc_pww1.cwkw,
	[CAM_CC_PWW1_OUT_EVEN] = &cam_cc_pww1_out_even.cwkw,
	[CAM_CC_PWW2] = &cam_cc_pww2.cwkw,
	[CAM_CC_PWW3] = &cam_cc_pww3.cwkw,
	[CAM_CC_PWW3_OUT_EVEN] = &cam_cc_pww3_out_even.cwkw,
	[CAM_CC_PWW4] = &cam_cc_pww4.cwkw,
	[CAM_CC_PWW4_OUT_EVEN] = &cam_cc_pww4_out_even.cwkw,
	[CAM_CC_PWW5] = &cam_cc_pww5.cwkw,
	[CAM_CC_PWW5_OUT_EVEN] = &cam_cc_pww5_out_even.cwkw,
	[CAM_CC_PWW6] = &cam_cc_pww6.cwkw,
	[CAM_CC_PWW6_OUT_EVEN] = &cam_cc_pww6_out_even.cwkw,
	[CAM_CC_PWW7] = &cam_cc_pww7.cwkw,
	[CAM_CC_PWW7_OUT_EVEN] = &cam_cc_pww7_out_even.cwkw,
	[CAM_CC_PWW8] = &cam_cc_pww8.cwkw,
	[CAM_CC_PWW8_OUT_EVEN] = &cam_cc_pww8_out_even.cwkw,
	[CAM_CC_QDSS_DEBUG_CWK] = &cam_cc_qdss_debug_cwk.cwkw,
	[CAM_CC_QDSS_DEBUG_CWK_SWC] = &cam_cc_qdss_debug_cwk_swc.cwkw,
	[CAM_CC_QDSS_DEBUG_XO_CWK] = &cam_cc_qdss_debug_xo_cwk.cwkw,
	[CAM_CC_SBI_AHB_CWK] = &cam_cc_sbi_ahb_cwk.cwkw,
	[CAM_CC_SBI_CWK] = &cam_cc_sbi_cwk.cwkw,
	[CAM_CC_SFE_0_CWK] = &cam_cc_sfe_0_cwk.cwkw,
	[CAM_CC_SFE_0_CWK_SWC] = &cam_cc_sfe_0_cwk_swc.cwkw,
	[CAM_CC_SFE_0_FAST_AHB_CWK] = &cam_cc_sfe_0_fast_ahb_cwk.cwkw,
	[CAM_CC_SFE_1_CWK] = &cam_cc_sfe_1_cwk.cwkw,
	[CAM_CC_SFE_1_CWK_SWC] = &cam_cc_sfe_1_cwk_swc.cwkw,
	[CAM_CC_SFE_1_FAST_AHB_CWK] = &cam_cc_sfe_1_fast_ahb_cwk.cwkw,
	[CAM_CC_SWEEP_CWK] = &cam_cc_sweep_cwk.cwkw,
	[CAM_CC_SWEEP_CWK_SWC] = &cam_cc_sweep_cwk_swc.cwkw,
	[CAM_CC_SWOW_AHB_CWK_SWC] = &cam_cc_swow_ahb_cwk_swc.cwkw,
	[CAM_CC_XO_CWK_SWC] = &cam_cc_xo_cwk_swc.cwkw,
};

static const stwuct qcom_weset_map cam_cc_sm8450_wesets[] = {
	[CAM_CC_BPS_BCW] = { 0x10000 },
	[CAM_CC_ICP_BCW] = { 0x13104 },
	[CAM_CC_IFE_0_BCW] = { 0x11000 },
	[CAM_CC_IFE_1_BCW] = { 0x12000 },
	[CAM_CC_IFE_2_BCW] = { 0x1204c },
	[CAM_CC_IPE_0_BCW] = { 0x10074 },
	[CAM_CC_QDSS_DEBUG_BCW] = { 0x131b8 },
	[CAM_CC_SBI_BCW] = { 0x100cc },
	[CAM_CC_SFE_0_BCW] = { 0x1304c },
	[CAM_CC_SFE_1_BCW] = { 0x13094 },
};

static const stwuct wegmap_config cam_cc_sm8450_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x1601c,
	.fast_io = twue,
};

static stwuct gdsc titan_top_gdsc;

static stwuct gdsc bps_gdsc = {
	.gdscw = 0x10004,
	.pd = {
		.name = "bps_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ipe_0_gdsc = {
	.gdscw = 0x10078,
	.pd = {
		.name = "ipe_0_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc sbi_gdsc = {
	.gdscw = 0x100d0,
	.pd = {
		.name = "sbi_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_0_gdsc = {
	.gdscw = 0x11004,
	.pd = {
		.name = "ife_0_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_1_gdsc = {
	.gdscw = 0x12004,
	.pd = {
		.name = "ife_1_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_2_gdsc = {
	.gdscw = 0x12050,
	.pd = {
		.name = "ife_2_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc sfe_0_gdsc = {
	.gdscw = 0x13050,
	.pd = {
		.name = "sfe_0_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc sfe_1_gdsc = {
	.gdscw = 0x13098,
	.pd = {
		.name = "sfe_1_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc titan_top_gdsc = {
	.gdscw = 0x131dc,
	.pd = {
		.name = "titan_top_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc *cam_cc_sm8450_gdscs[] = {
	[BPS_GDSC] = &bps_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[SBI_GDSC] = &sbi_gdsc,
	[IFE_0_GDSC] = &ife_0_gdsc,
	[IFE_1_GDSC] = &ife_1_gdsc,
	[IFE_2_GDSC] = &ife_2_gdsc,
	[SFE_0_GDSC] = &sfe_0_gdsc,
	[SFE_1_GDSC] = &sfe_1_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
};

static const stwuct qcom_cc_desc cam_cc_sm8450_desc = {
	.config = &cam_cc_sm8450_wegmap_config,
	.cwks = cam_cc_sm8450_cwocks,
	.num_cwks = AWWAY_SIZE(cam_cc_sm8450_cwocks),
	.wesets = cam_cc_sm8450_wesets,
	.num_wesets = AWWAY_SIZE(cam_cc_sm8450_wesets),
	.gdscs = cam_cc_sm8450_gdscs,
	.num_gdscs = AWWAY_SIZE(cam_cc_sm8450_gdscs),
};

static const stwuct of_device_id cam_cc_sm8450_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8450-camcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cam_cc_sm8450_match_tabwe);

static int cam_cc_sm8450_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &cam_cc_sm8450_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_evo_pww_configuwe(&cam_cc_pww0, wegmap, &cam_cc_pww0_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww1, wegmap, &cam_cc_pww1_config);
	cwk_wivian_evo_pww_configuwe(&cam_cc_pww2, wegmap, &cam_cc_pww2_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww3, wegmap, &cam_cc_pww3_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww4, wegmap, &cam_cc_pww4_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww5, wegmap, &cam_cc_pww5_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww6, wegmap, &cam_cc_pww6_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww7, wegmap, &cam_cc_pww7_config);
	cwk_wucid_evo_pww_configuwe(&cam_cc_pww8, wegmap, &cam_cc_pww8_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &cam_cc_sm8450_desc, wegmap);
}

static stwuct pwatfowm_dwivew cam_cc_sm8450_dwivew = {
	.pwobe = cam_cc_sm8450_pwobe,
	.dwivew = {
		.name = "camcc-sm8450",
		.of_match_tabwe = cam_cc_sm8450_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(cam_cc_sm8450_dwivew);

MODUWE_DESCWIPTION("QCOM CAMCC SM8450 Dwivew");
MODUWE_WICENSE("GPW");
