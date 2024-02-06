// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,camcc-sc7280.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_CAM_CC_PWW0_OUT_EVEN,
	P_CAM_CC_PWW0_OUT_MAIN,
	P_CAM_CC_PWW0_OUT_ODD,
	P_CAM_CC_PWW1_OUT_EVEN,
	P_CAM_CC_PWW2_OUT_AUX2,
	P_CAM_CC_PWW2_OUT_EAWWY,
	P_CAM_CC_PWW3_OUT_EVEN,
	P_CAM_CC_PWW4_OUT_EVEN,
	P_CAM_CC_PWW5_OUT_EVEN,
	P_CAM_CC_PWW6_OUT_EVEN,
	P_CAM_CC_PWW6_OUT_MAIN,
	P_CAM_CC_PWW6_OUT_ODD,
	P_SWEEP_CWK,
};

static stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct pww_vco zonda_vco[] = {
	{ 595200000UW, 3600000000UW, 0 },
};

/* 1200MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww0_config = {
	.w = 0x3E,
	.awpha = 0x8000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00003101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww0_out_odd[] = {
	{ 0x3, 3 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_odd = {
	.offset = 0x0,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww0_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww0_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww0_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

/* 600MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww1_config = {
	.w = 0x1F,
	.awpha = 0x4000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww1_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww1_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww1_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

/* 1440MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww2_config = {
	.w = 0x4B,
	.awpha = 0x0,
	.config_ctw_vaw = 0x08200800,
	.config_ctw_hi_vaw = 0x05022011,
	.config_ctw_hi1_vaw = 0x08000000,
	.usew_ctw_vaw = 0x00000301,
};

static stwuct cwk_awpha_pww cam_cc_pww2 = {
	.offset = 0x2000,
	.vco_tabwe = zonda_vco,
	.num_vco = AWWAY_SIZE(zonda_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww2",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_zonda_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww2_out_aux[] = {
	{ 0x3, 4 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww2_out_aux = {
	.offset = 0x2000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww2_out_aux,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww2_out_aux),
	.width = 2,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww2_out_aux",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww2.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_zonda_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww2_out_aux2[] = {
	{ 0x3, 4 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww2_out_aux2 = {
	.offset = 0x2000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww2_out_aux2,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww2_out_aux2),
	.width = 2,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww2_out_aux2",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww2.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_zonda_ops,
	},
};

/* 760MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww3_config = {
	.w = 0x27,
	.awpha = 0x9555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww3 = {
	.offset = 0x3000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww3_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww3_out_even = {
	.offset = 0x3000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww3_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww3_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww3_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww3.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

/* 760MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww4_config = {
	.w = 0x27,
	.awpha = 0x9555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww4 = {
	.offset = 0x4000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww4_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww4_out_even = {
	.offset = 0x4000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww4_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww4_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww4_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww4.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

/* 760MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww5_config = {
	.w = 0x27,
	.awpha = 0x9555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww5 = {
	.offset = 0x5000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww5",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww5_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww5_out_even = {
	.offset = 0x5000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww5_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww5_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww5_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww5.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

/* 960MHz Configuwation */
static const stwuct awpha_pww_config cam_cc_pww6_config = {
	.w = 0x32,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00003101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww6 = {
	.offset = 0x6000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww6",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww6_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww6_out_even = {
	.offset = 0x6000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww6_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww6_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww6_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww6.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww6_out_odd[] = {
	{ 0x3, 3 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww6_out_odd = {
	.offset = 0x6000,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww6_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww6_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww6_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&cam_cc_pww6.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct pawent_map cam_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW0_OUT_MAIN, 1 },
	{ P_CAM_CC_PWW0_OUT_EVEN, 2 },
	{ P_CAM_CC_PWW0_OUT_ODD, 3 },
	{ P_CAM_CC_PWW6_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww0.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_odd.cwkw.hw },
	{ .hw = &cam_cc_pww6_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW0_OUT_MAIN, 1 },
	{ P_CAM_CC_PWW0_OUT_EVEN, 2 },
	{ P_CAM_CC_PWW0_OUT_ODD, 3 },
	{ P_CAM_CC_PWW6_OUT_MAIN, 4 },
	{ P_CAM_CC_PWW6_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww0.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_odd.cwkw.hw },
	{ .hw = &cam_cc_pww6.cwkw.hw },
	{ .hw = &cam_cc_pww6_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW2_OUT_AUX2, 3 },
	{ P_CAM_CC_PWW2_OUT_EAWWY, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww2_out_aux2.cwkw.hw },
	{ .hw = &cam_cc_pww2.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW0_OUT_MAIN, 1 },
	{ P_CAM_CC_PWW0_OUT_EVEN, 2 },
	{ P_CAM_CC_PWW0_OUT_ODD, 3 },
	{ P_CAM_CC_PWW6_OUT_EVEN, 5 },
	{ P_CAM_CC_PWW6_OUT_ODD, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww0.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_odd.cwkw.hw },
	{ .hw = &cam_cc_pww6_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww6_out_odd.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww3_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW4_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww4_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW5_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww5_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW1_OUT_EVEN, 4 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_7[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww1_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_8[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_8[] = {
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map cam_cc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_9_ao[] = {
	{ .fw_name = "bi_tcxo_ao" },
};

static const stwuct fweq_tbw ftbw_cam_cc_bps_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_ODD, 4, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_ODD, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_bps_cwk_swc = {
	.cmd_wcgw = 0x7010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_bps_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_camnoc_axi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(150000000, P_CAM_CC_PWW0_OUT_EVEN, 4, 0, 0),
	F(240000000, P_CAM_CC_PWW6_OUT_EVEN, 2, 0, 0),
	F(320000000, P_CAM_CC_PWW6_OUT_ODD, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	F(480000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_camnoc_axi_cwk_swc = {
	.cmd_wcgw = 0xc124,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_3,
	.fweq_tbw = ftbw_cam_cc_camnoc_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_camnoc_axi_cwk_swc",
		.pawent_data = cam_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cci_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_CAM_CC_PWW0_OUT_EVEN, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cci_0_cwk_swc = {
	.cmd_wcgw = 0xc0e0,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cci_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_cci_1_cwk_swc = {
	.cmd_wcgw = 0xc0fc,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cci_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cphy_wx_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0xa064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cphy_wx_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_csi0phytimew_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0xe0ac,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi0phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0xe0d0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi1phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0xe0f4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi2phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi3phytimew_cwk_swc = {
	.cmd_wcgw = 0xe11c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi3phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
		},
};

static stwuct cwk_wcg2 cam_cc_csi4phytimew_cwk_swc = {
	.cmd_wcgw = 0xe140,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi4phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_fast_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_CAM_CC_PWW0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_fast_ahb_cwk_swc = {
	.cmd_wcgw = 0x703c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fast_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_fast_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_icp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_icp_cwk_swc = {
	.cmd_wcgw = 0xc0b8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_icp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_icp_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(380000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(510000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_cwk_swc = {
	.cmd_wcgw = 0xa010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_4,
	.fweq_tbw = ftbw_cam_cc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(380000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(510000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_1_cwk_swc = {
	.cmd_wcgw = 0xb010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_5,
	.fweq_tbw = ftbw_cam_cc_ife_1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_csid_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_CAM_CC_PWW0_OUT_EVEN, 8, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_csid_cwk_swc = {
	.cmd_wcgw = 0xa03c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_0_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_1_csid_cwk_swc = {
	.cmd_wcgw = 0xb03c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_1_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_2_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(380000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	F(510000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAM_CC_PWW5_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_2_cwk_swc = {
	.cmd_wcgw = 0xb07c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_6,
	.fweq_tbw = ftbw_cam_cc_ife_2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_2_cwk_swc",
		.pawent_data = cam_cc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_6),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_2_csid_cwk_swc = {
	.cmd_wcgw = 0xb0a8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_2_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_wite_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(320000000, P_CAM_CC_PWW6_OUT_ODD, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW6_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_wite_0_cwk_swc = {
	.cmd_wcgw = 0xc004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_3,
	.fweq_tbw = ftbw_cam_cc_ife_wite_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_0_csid_cwk_swc = {
	.cmd_wcgw = 0xc020,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_0_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_1_cwk_swc = {
	.cmd_wcgw = 0xc048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_3,
	.fweq_tbw = ftbw_cam_cc_ife_wite_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_1_csid_cwk_swc = {
	.cmd_wcgw = 0xc064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_1_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ipe_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(430000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(520000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ipe_0_cwk_swc = {
	.cmd_wcgw = 0x8010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_7,
	.fweq_tbw = ftbw_cam_cc_ipe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ipe_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_7),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_jpeg_cwk_swc = {
	.cmd_wcgw = 0xc08c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_jpeg_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_wwme_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(240000000, P_CAM_CC_PWW6_OUT_EVEN, 2, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(320000000, P_CAM_CC_PWW6_OUT_ODD, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_wwme_cwk_swc = {
	.cmd_wcgw = 0xc150,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_3,
	.fweq_tbw = ftbw_cam_cc_wwme_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_wwme_cwk_swc",
		.pawent_data = cam_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_mcwk0_cwk_swc[] = {
	F(19200000, P_CAM_CC_PWW2_OUT_EAWWY, 1, 1, 75),
	F(24000000, P_CAM_CC_PWW2_OUT_EAWWY, 10, 1, 6),
	F(34285714, P_CAM_CC_PWW2_OUT_EAWWY, 2, 1, 21),
	{ }
};

static stwuct cwk_wcg2 cam_cc_mcwk0_cwk_swc = {
	.cmd_wcgw = 0xe000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk1_cwk_swc = {
	.cmd_wcgw = 0xe01c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk2_cwk_swc = {
	.cmd_wcgw = 0xe038,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk2_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk3_cwk_swc = {
	.cmd_wcgw = 0xe054,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk3_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk4_cwk_swc = {
	.cmd_wcgw = 0xe070,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk4_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk5_cwk_swc = {
	.cmd_wcgw = 0xe08c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk5_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
		},
};

static const stwuct fweq_tbw ftbw_cam_cc_sweep_cwk_swc[] = {
	F(32000, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_sweep_cwk_swc = {
	.cmd_wcgw = 0xc1c0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_8,
	.fweq_tbw = ftbw_cam_cc_sweep_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_sweep_cwk_swc",
		.pawent_data = cam_cc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_8),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_swow_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(80000000, P_CAM_CC_PWW0_OUT_EVEN, 7.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_swow_ahb_cwk_swc = {
	.cmd_wcgw = 0x7058,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_swow_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_swow_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_xo_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_xo_cwk_swc = {
	.cmd_wcgw = 0xc1a4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_9,
	.fweq_tbw = ftbw_cam_cc_xo_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_xo_cwk_swc",
		.pawent_data = cam_cc_pawent_data_9_ao,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_9_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch cam_cc_bps_ahb_cwk = {
	.hawt_weg = 0x7070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7070,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_bps_aweg_cwk = {
	.hawt_weg = 0x7054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_axi_cwk = {
	.hawt_weg = 0x7038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_cwk = {
	.hawt_weg = 0x7028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_camnoc_axi_cwk = {
	.hawt_weg = 0xc140,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc140,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xc148,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc148,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xc0f8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0f8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xc114,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc114,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xc1a0,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0xc1a0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xc11c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc11c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_csi0phytimew_cwk = {
	.hawt_weg = 0xe0c4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe0c4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe0e8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe0e8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe10c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe10c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe134,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe134,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe158,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe158,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_csiphy0_cwk = {
	.hawt_weg = 0xe0c8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe0c8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe0ec,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe0ec,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe110,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe110,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe138,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe138,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe15c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe15c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_gdsc_cwk = {
	.hawt_weg = 0xc1bc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc1bc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_icp_ahb_cwk = {
	.hawt_weg = 0xc0d8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0d8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xc0d0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_0_axi_cwk = {
	.hawt_weg = 0xa080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_cwk = {
	.hawt_weg = 0xa028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_0_cphy_wx_cwk = {
	.hawt_weg = 0xa07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_csid_cwk = {
	.hawt_weg = 0xa054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_0_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_dsp_cwk = {
	.hawt_weg = 0xa038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_1_axi_cwk = {
	.hawt_weg = 0xb068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_cwk = {
	.hawt_weg = 0xb028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_1_cphy_wx_cwk = {
	.hawt_weg = 0xb064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_csid_cwk = {
	.hawt_weg = 0xb054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_1_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_dsp_cwk = {
	.hawt_weg = 0xb038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_2_axi_cwk = {
	.hawt_weg = 0xb0d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_2_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_2_cwk = {
	.hawt_weg = 0xb094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_2_cphy_wx_cwk = {
	.hawt_weg = 0xb0d0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_2_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_2_csid_cwk = {
	.hawt_weg = 0xb0c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_2_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_2_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_2_dsp_cwk = {
	.hawt_weg = 0xb0a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_ife_wite_0_cwk = {
	.hawt_weg = 0xc01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_0_cphy_wx_cwk = {
	.hawt_weg = 0xc040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_0_csid_cwk = {
	.hawt_weg = 0xc038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_0_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_1_cwk = {
	.hawt_weg = 0xc060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_1_cphy_wx_cwk = {
	.hawt_weg = 0xc084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_1_csid_cwk = {
	.hawt_weg = 0xc07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ife_wite_1_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_ahb_cwk = {
	.hawt_weg = 0x8040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_aweg_cwk = {
	.hawt_weg = 0x803c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x803c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_axi_cwk = {
	.hawt_weg = 0x8038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_cwk = {
	.hawt_weg = 0x8028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_ipe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_jpeg_cwk = {
	.hawt_weg = 0xc0a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_wwme_cwk = {
	.hawt_weg = 0xc168,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc168,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_wwme_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cam_cc_wwme_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk0_cwk = {
	.hawt_weg = 0xe018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe06c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe06c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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
	.hawt_weg = 0xe0a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe0a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct cwk_bwanch cam_cc_sweep_cwk = {
	.hawt_weg = 0xc1d8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc1d8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
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

static stwuct gdsc cam_cc_titan_top_gdsc = {
	.gdscw = 0xc194,
	.pd = {
		.name = "cam_cc_titan_top_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct gdsc cam_cc_bps_gdsc = {
	.gdscw = 0x7004,
	.pd = {
		.name = "cam_cc_bps_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
};

static stwuct gdsc cam_cc_ife_0_gdsc = {
	.gdscw = 0xa004,
	.pd = {
		.name = "cam_cc_ife_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct gdsc cam_cc_ife_1_gdsc = {
	.gdscw = 0xb004,
	.pd = {
		.name = "cam_cc_ife_1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct gdsc cam_cc_ife_2_gdsc = {
	.gdscw = 0xb070,
	.pd = {
		.name = "cam_cc_ife_2_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct gdsc cam_cc_ipe_0_gdsc = {
	.gdscw = 0x8004,
	.pd = {
		.name = "cam_cc_ipe_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
};

static stwuct cwk_wegmap *cam_cc_sc7280_cwocks[] = {
	[CAM_CC_BPS_AHB_CWK] = &cam_cc_bps_ahb_cwk.cwkw,
	[CAM_CC_BPS_AWEG_CWK] = &cam_cc_bps_aweg_cwk.cwkw,
	[CAM_CC_BPS_AXI_CWK] = &cam_cc_bps_axi_cwk.cwkw,
	[CAM_CC_BPS_CWK] = &cam_cc_bps_cwk.cwkw,
	[CAM_CC_BPS_CWK_SWC] = &cam_cc_bps_cwk_swc.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK] = &cam_cc_camnoc_axi_cwk.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK_SWC] = &cam_cc_camnoc_axi_cwk_swc.cwkw,
	[CAM_CC_CAMNOC_DCD_XO_CWK] = &cam_cc_camnoc_dcd_xo_cwk.cwkw,
	[CAM_CC_CCI_0_CWK] = &cam_cc_cci_0_cwk.cwkw,
	[CAM_CC_CCI_0_CWK_SWC] = &cam_cc_cci_0_cwk_swc.cwkw,
	[CAM_CC_CCI_1_CWK] = &cam_cc_cci_1_cwk.cwkw,
	[CAM_CC_CCI_1_CWK_SWC] = &cam_cc_cci_1_cwk_swc.cwkw,
	[CAM_CC_COWE_AHB_CWK] = &cam_cc_cowe_ahb_cwk.cwkw,
	[CAM_CC_CPAS_AHB_CWK] = &cam_cc_cpas_ahb_cwk.cwkw,
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
	[CAM_CC_CSIPHY0_CWK] = &cam_cc_csiphy0_cwk.cwkw,
	[CAM_CC_CSIPHY1_CWK] = &cam_cc_csiphy1_cwk.cwkw,
	[CAM_CC_CSIPHY2_CWK] = &cam_cc_csiphy2_cwk.cwkw,
	[CAM_CC_CSIPHY3_CWK] = &cam_cc_csiphy3_cwk.cwkw,
	[CAM_CC_CSIPHY4_CWK] = &cam_cc_csiphy4_cwk.cwkw,
	[CAM_CC_FAST_AHB_CWK_SWC] = &cam_cc_fast_ahb_cwk_swc.cwkw,
	[CAM_CC_GDSC_CWK] = &cam_cc_gdsc_cwk.cwkw,
	[CAM_CC_ICP_AHB_CWK] = &cam_cc_icp_ahb_cwk.cwkw,
	[CAM_CC_ICP_CWK] = &cam_cc_icp_cwk.cwkw,
	[CAM_CC_ICP_CWK_SWC] = &cam_cc_icp_cwk_swc.cwkw,
	[CAM_CC_IFE_0_AXI_CWK] = &cam_cc_ife_0_axi_cwk.cwkw,
	[CAM_CC_IFE_0_CWK] = &cam_cc_ife_0_cwk.cwkw,
	[CAM_CC_IFE_0_CWK_SWC] = &cam_cc_ife_0_cwk_swc.cwkw,
	[CAM_CC_IFE_0_CPHY_WX_CWK] = &cam_cc_ife_0_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_0_CSID_CWK] = &cam_cc_ife_0_csid_cwk.cwkw,
	[CAM_CC_IFE_0_CSID_CWK_SWC] = &cam_cc_ife_0_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_0_DSP_CWK] = &cam_cc_ife_0_dsp_cwk.cwkw,
	[CAM_CC_IFE_1_AXI_CWK] = &cam_cc_ife_1_axi_cwk.cwkw,
	[CAM_CC_IFE_1_CWK] = &cam_cc_ife_1_cwk.cwkw,
	[CAM_CC_IFE_1_CWK_SWC] = &cam_cc_ife_1_cwk_swc.cwkw,
	[CAM_CC_IFE_1_CPHY_WX_CWK] = &cam_cc_ife_1_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_1_CSID_CWK] = &cam_cc_ife_1_csid_cwk.cwkw,
	[CAM_CC_IFE_1_CSID_CWK_SWC] = &cam_cc_ife_1_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_1_DSP_CWK] = &cam_cc_ife_1_dsp_cwk.cwkw,
	[CAM_CC_IFE_2_AXI_CWK] = &cam_cc_ife_2_axi_cwk.cwkw,
	[CAM_CC_IFE_2_CWK] = &cam_cc_ife_2_cwk.cwkw,
	[CAM_CC_IFE_2_CWK_SWC] = &cam_cc_ife_2_cwk_swc.cwkw,
	[CAM_CC_IFE_2_CPHY_WX_CWK] = &cam_cc_ife_2_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_2_CSID_CWK] = &cam_cc_ife_2_csid_cwk.cwkw,
	[CAM_CC_IFE_2_CSID_CWK_SWC] = &cam_cc_ife_2_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_2_DSP_CWK] = &cam_cc_ife_2_dsp_cwk.cwkw,
	[CAM_CC_IFE_WITE_0_CWK] = &cam_cc_ife_wite_0_cwk.cwkw,
	[CAM_CC_IFE_WITE_0_CWK_SWC] = &cam_cc_ife_wite_0_cwk_swc.cwkw,
	[CAM_CC_IFE_WITE_0_CPHY_WX_CWK] = &cam_cc_ife_wite_0_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_WITE_0_CSID_CWK] = &cam_cc_ife_wite_0_csid_cwk.cwkw,
	[CAM_CC_IFE_WITE_0_CSID_CWK_SWC] = &cam_cc_ife_wite_0_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_WITE_1_CWK] = &cam_cc_ife_wite_1_cwk.cwkw,
	[CAM_CC_IFE_WITE_1_CWK_SWC] = &cam_cc_ife_wite_1_cwk_swc.cwkw,
	[CAM_CC_IFE_WITE_1_CPHY_WX_CWK] = &cam_cc_ife_wite_1_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_WITE_1_CSID_CWK] = &cam_cc_ife_wite_1_csid_cwk.cwkw,
	[CAM_CC_IFE_WITE_1_CSID_CWK_SWC] = &cam_cc_ife_wite_1_csid_cwk_swc.cwkw,
	[CAM_CC_IPE_0_AHB_CWK] = &cam_cc_ipe_0_ahb_cwk.cwkw,
	[CAM_CC_IPE_0_AWEG_CWK] = &cam_cc_ipe_0_aweg_cwk.cwkw,
	[CAM_CC_IPE_0_AXI_CWK] = &cam_cc_ipe_0_axi_cwk.cwkw,
	[CAM_CC_IPE_0_CWK] = &cam_cc_ipe_0_cwk.cwkw,
	[CAM_CC_IPE_0_CWK_SWC] = &cam_cc_ipe_0_cwk_swc.cwkw,
	[CAM_CC_JPEG_CWK] = &cam_cc_jpeg_cwk.cwkw,
	[CAM_CC_JPEG_CWK_SWC] = &cam_cc_jpeg_cwk_swc.cwkw,
	[CAM_CC_WWME_CWK] = &cam_cc_wwme_cwk.cwkw,
	[CAM_CC_WWME_CWK_SWC] = &cam_cc_wwme_cwk_swc.cwkw,
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
	[CAM_CC_PWW0] = &cam_cc_pww0.cwkw,
	[CAM_CC_PWW0_OUT_EVEN] = &cam_cc_pww0_out_even.cwkw,
	[CAM_CC_PWW0_OUT_ODD] = &cam_cc_pww0_out_odd.cwkw,
	[CAM_CC_PWW1] = &cam_cc_pww1.cwkw,
	[CAM_CC_PWW1_OUT_EVEN] = &cam_cc_pww1_out_even.cwkw,
	[CAM_CC_PWW2] = &cam_cc_pww2.cwkw,
	[CAM_CC_PWW2_OUT_AUX] = &cam_cc_pww2_out_aux.cwkw,
	[CAM_CC_PWW2_OUT_AUX2] = &cam_cc_pww2_out_aux2.cwkw,
	[CAM_CC_PWW3] = &cam_cc_pww3.cwkw,
	[CAM_CC_PWW3_OUT_EVEN] = &cam_cc_pww3_out_even.cwkw,
	[CAM_CC_PWW4] = &cam_cc_pww4.cwkw,
	[CAM_CC_PWW4_OUT_EVEN] = &cam_cc_pww4_out_even.cwkw,
	[CAM_CC_PWW5] = &cam_cc_pww5.cwkw,
	[CAM_CC_PWW5_OUT_EVEN] = &cam_cc_pww5_out_even.cwkw,
	[CAM_CC_PWW6] = &cam_cc_pww6.cwkw,
	[CAM_CC_PWW6_OUT_EVEN] = &cam_cc_pww6_out_even.cwkw,
	[CAM_CC_PWW6_OUT_ODD] = &cam_cc_pww6_out_odd.cwkw,
	[CAM_CC_SWEEP_CWK] = &cam_cc_sweep_cwk.cwkw,
	[CAM_CC_SWEEP_CWK_SWC] = &cam_cc_sweep_cwk_swc.cwkw,
	[CAM_CC_SWOW_AHB_CWK_SWC] = &cam_cc_swow_ahb_cwk_swc.cwkw,
	[CAM_CC_XO_CWK_SWC] = &cam_cc_xo_cwk_swc.cwkw,
};

static stwuct gdsc *cam_cc_sc7280_gdscs[] = {
	[CAM_CC_TITAN_TOP_GDSC] = &cam_cc_titan_top_gdsc,
	[CAM_CC_BPS_GDSC] = &cam_cc_bps_gdsc,
	[CAM_CC_IFE_0_GDSC] = &cam_cc_ife_0_gdsc,
	[CAM_CC_IFE_1_GDSC] = &cam_cc_ife_1_gdsc,
	[CAM_CC_IFE_2_GDSC] = &cam_cc_ife_2_gdsc,
	[CAM_CC_IPE_0_GDSC] = &cam_cc_ipe_0_gdsc,
};

static const stwuct wegmap_config cam_cc_sc7280_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xf00c,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc cam_cc_sc7280_desc = {
	.config = &cam_cc_sc7280_wegmap_config,
	.cwks = cam_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(cam_cc_sc7280_cwocks),
	.gdscs = cam_cc_sc7280_gdscs,
	.num_gdscs = AWWAY_SIZE(cam_cc_sc7280_gdscs),
};

static const stwuct of_device_id cam_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-camcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cam_cc_sc7280_match_tabwe);

static int cam_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &cam_cc_sc7280_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_pww_configuwe(&cam_cc_pww0, wegmap, &cam_cc_pww0_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww1, wegmap, &cam_cc_pww1_config);
	cwk_zonda_pww_configuwe(&cam_cc_pww2, wegmap, &cam_cc_pww2_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww3, wegmap, &cam_cc_pww3_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww4, wegmap, &cam_cc_pww4_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww5, wegmap, &cam_cc_pww5_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww6, wegmap, &cam_cc_pww6_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &cam_cc_sc7280_desc, wegmap);
}

static stwuct pwatfowm_dwivew cam_cc_sc7280_dwivew = {
	.pwobe = cam_cc_sc7280_pwobe,
	.dwivew = {
		.name = "cam_cc-sc7280",
		.of_match_tabwe = cam_cc_sc7280_match_tabwe,
	},
};

static int __init cam_cc_sc7280_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cam_cc_sc7280_dwivew);
}
subsys_initcaww(cam_cc_sc7280_init);

static void __exit cam_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cam_cc_sc7280_dwivew);
}
moduwe_exit(cam_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI CAM_CC SC7280 Dwivew");
MODUWE_WICENSE("GPW v2");
