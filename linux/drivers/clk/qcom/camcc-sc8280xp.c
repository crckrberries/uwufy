// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sc8280xp-camcc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	DT_IFACE,
	DT_BI_TCXO,
	DT_BI_TCXO_AO,
	DT_SWEEP_CWK,
};

enum {
	P_BI_TCXO,
	P_CAMCC_PWW0_OUT_EVEN,
	P_CAMCC_PWW0_OUT_MAIN,
	P_CAMCC_PWW0_OUT_ODD,
	P_CAMCC_PWW1_OUT_EVEN,
	P_CAMCC_PWW2_OUT_AUX,
	P_CAMCC_PWW2_OUT_EAWWY,
	P_CAMCC_PWW3_OUT_EVEN,
	P_CAMCC_PWW4_OUT_EVEN,
	P_CAMCC_PWW5_OUT_EVEN,
	P_CAMCC_PWW6_OUT_EVEN,
	P_CAMCC_PWW7_OUT_EVEN,
	P_CAMCC_PWW7_OUT_ODD,
	P_SWEEP_CWK,
};

static stwuct pww_vco wucid_vco[] = {
	{ 249600000, 1800000000, 0 },
};

static stwuct pww_vco zonda_vco[] = {
	{ 595200000, 3600000000, 0 },
};

static stwuct awpha_pww_config camcc_pww0_config = {
	.w = 0x3e,
	.awpha = 0x8000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00003100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww0_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww0_out_odd[] = {
	{ 0x3, 3 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww0_out_odd = {
	.offset = 0x0,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_camcc_pww0_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww0_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww0_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct awpha_pww_config camcc_pww1_config = {
	.w = 0x21,
	.awpha = 0x5555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww1_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww1_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww1_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct awpha_pww_config camcc_pww2_config = {
	.w = 0x32,
	.awpha = 0x0,
	.config_ctw_vaw = 0x08200800,
	.config_ctw_hi_vaw = 0x05028011,
	.config_ctw_hi1_vaw = 0x08000000,
};

static stwuct cwk_awpha_pww camcc_pww2 = {
	.offset = 0x2000,
	.vco_tabwe = zonda_vco,
	.num_vco = AWWAY_SIZE(zonda_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww2",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_zonda_ops,
		},
	},
};

static stwuct awpha_pww_config camcc_pww3_config = {
	.w = 0x29,
	.awpha = 0xaaaa,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww3 = {
	.offset = 0x3000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww3_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww3_out_even = {
	.offset = 0x3000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww3_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww3_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww3_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww3.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct awpha_pww_config camcc_pww4_config = {
	.w = 0x29,
	.awpha = 0xaaaa,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww4 = {
	.offset = 0x4000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww4_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww4_out_even = {
	.offset = 0x4000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww4_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww4_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww4_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww4.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct awpha_pww_config camcc_pww5_config = {
	.w = 0x29,
	.awpha = 0xaaaa,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww5 = {
	.offset = 0x10000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww5",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww5_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww5_out_even = {
	.offset = 0x10000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww5_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww5_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww5_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww5.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct awpha_pww_config camcc_pww6_config = {
	.w = 0x29,
	.awpha = 0xaaaa,
	.config_ctw_vaw = 0x20486699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww6 = {
	.offset = 0x11000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww6",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww6_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww6_out_even = {
	.offset = 0x11000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww6_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww6_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww6_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww6.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct awpha_pww_config camcc_pww7_config = {
	.w = 0x32,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x2a9a699c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x01800000,
	.usew_ctw_vaw = 0x00003100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww camcc_pww7 = {
	.offset = 0x12000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww7",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_5wpe_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww7_out_even[] = {
	{ 0x1, 2 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww7_out_even = {
	.offset = 0x12000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww7_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww7_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww7_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww7.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww7_out_odd[] = {
	{ 0x3, 3 },
};

static stwuct cwk_awpha_pww_postdiv camcc_pww7_out_odd = {
	.offset = 0x12000,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_camcc_pww7_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww7_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww7_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww7.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct pawent_map camcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW0_OUT_EVEN, 2 },
	{ P_CAMCC_PWW0_OUT_ODD, 3 },
	{ P_CAMCC_PWW7_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww0_out_even.cwkw.hw },
	{ .hw = &camcc_pww0_out_odd.cwkw.hw },
	{ .hw = &camcc_pww7_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW2_OUT_AUX, 2 },
	{ P_CAMCC_PWW2_OUT_EAWWY, 5 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww2.cwkw.hw },
	{ .hw = &camcc_pww2.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW0_OUT_EVEN, 2 },
	{ P_CAMCC_PWW0_OUT_ODD, 3 },
	{ P_CAMCC_PWW7_OUT_ODD, 4 },
	{ P_CAMCC_PWW7_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_2[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww0_out_even.cwkw.hw },
	{ .hw = &camcc_pww0_out_odd.cwkw.hw },
	{ .hw = &camcc_pww7_out_odd.cwkw.hw },
	{ .hw = &camcc_pww7_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW0_OUT_EVEN, 2 },
	{ P_CAMCC_PWW0_OUT_ODD, 3 },
	{ P_CAMCC_PWW7_OUT_EVEN, 5 },
	{ P_CAMCC_PWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_3[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww0_out_even.cwkw.hw },
	{ .hw = &camcc_pww0_out_odd.cwkw.hw },
	{ .hw = &camcc_pww7_out_even.cwkw.hw },
	{ .hw = &camcc_pww3_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_4[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww3_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW4_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_5[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww4_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW5_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_6[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww5_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW6_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_7[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww6_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_8[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW1_OUT_EVEN, 4 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_8[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &camcc_pww1_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_9[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_9[] = {
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map camcc_pawent_map_10[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_10_ao[] = {
	{ .fw_name = "bi_tcxo_ao" },
};

static const stwuct fweq_tbw ftbw_camcc_bps_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_CAMCC_PWW0_OUT_ODD, 2, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAMCC_PWW7_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
	F(760000000, P_CAMCC_PWW3_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_bps_cwk_swc = {
	.cmd_wcgw = 0x7010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_3,
	.fweq_tbw = ftbw_camcc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_bps_cwk_swc",
		.pawent_data = camcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_camnoc_axi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(150000000, P_CAMCC_PWW0_OUT_EVEN, 4, 0, 0),
	F(266666667, P_CAMCC_PWW0_OUT_ODD, 1.5, 0, 0),
	F(320000000, P_CAMCC_PWW7_OUT_ODD, 1, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAMCC_PWW7_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_camnoc_axi_cwk_swc = {
	.cmd_wcgw = 0xc170,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_camnoc_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_camnoc_axi_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_cci_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_CAMCC_PWW0_OUT_EVEN, 16, 0, 0),
};

static stwuct cwk_wcg2 camcc_cci_0_cwk_swc = {
	.cmd_wcgw = 0xc108,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_cci_0_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_cci_1_cwk_swc = {
	.cmd_wcgw = 0xc124,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_cci_1_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_cci_2_cwk_swc = {
	.cmd_wcgw = 0xc204,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_cci_2_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_cci_3_cwk_swc = {
	.cmd_wcgw = 0xc220,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_cci_3_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_cphy_wx_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(240000000, P_CAMCC_PWW0_OUT_EVEN, 2.5, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0xa064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_cphy_wx_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_csi0phytimew_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAMCC_PWW0_OUT_EVEN, 2, 0, 0),
};

static stwuct cwk_wcg2 camcc_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x6004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_csi0phytimew_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0x6028,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_csi1phytimew_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0x604c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_csi2phytimew_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_csi3phytimew_cwk_swc = {
	.cmd_wcgw = 0x6074,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_csi3phytimew_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_fast_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAMCC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAMCC_PWW0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAMCC_PWW0_OUT_MAIN, 4, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_MAIN, 3, 0, 0),
};

static stwuct cwk_wcg2 camcc_fast_ahb_cwk_swc = {
	.cmd_wcgw = 0x703c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_fast_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_fast_ahb_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_icp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
};

static stwuct cwk_wcg2 camcc_icp_cwk_swc = {
	.cmd_wcgw = 0xc0b8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_icp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_icp_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAMCC_PWW3_OUT_EVEN, 1, 0, 0),
	F(558000000, P_CAMCC_PWW3_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAMCC_PWW3_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAMCC_PWW3_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_0_cwk_swc = {
	.cmd_wcgw = 0xa010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_4,
	.fweq_tbw = ftbw_camcc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_0_cwk_swc",
		.pawent_data = camcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_0_csid_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_CAMCC_PWW0_OUT_EVEN, 8, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAMCC_PWW7_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_0_csid_cwk_swc = {
	.cmd_wcgw = 0xa03c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_0_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAMCC_PWW4_OUT_EVEN, 1, 0, 0),
	F(558000000, P_CAMCC_PWW4_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAMCC_PWW4_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAMCC_PWW4_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_1_cwk_swc = {
	.cmd_wcgw = 0xb010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_5,
	.fweq_tbw = ftbw_camcc_ife_1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_1_cwk_swc",
		.pawent_data = camcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_1_csid_cwk_swc = {
	.cmd_wcgw = 0xb03c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_1_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_2_cwk_swc[] = {
	F(400000000, P_CAMCC_PWW5_OUT_EVEN, 1, 0, 0),
	F(558000000, P_CAMCC_PWW5_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAMCC_PWW5_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAMCC_PWW5_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_2_cwk_swc = {
	.cmd_wcgw = 0xf010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_6,
	.fweq_tbw = ftbw_camcc_ife_2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_2_cwk_swc",
		.pawent_data = camcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_6),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_2_csid_cwk_swc[] = {
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAMCC_PWW7_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_2_csid_cwk_swc = {
	.cmd_wcgw = 0xf03c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_2_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_2_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_3_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAMCC_PWW6_OUT_EVEN, 1, 0, 0),
	F(558000000, P_CAMCC_PWW6_OUT_EVEN, 1, 0, 0),
	F(637000000, P_CAMCC_PWW6_OUT_EVEN, 1, 0, 0),
	F(760000000, P_CAMCC_PWW6_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_3_cwk_swc = {
	.cmd_wcgw = 0xf07c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_7,
	.fweq_tbw = ftbw_camcc_ife_3_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_3_cwk_swc",
		.pawent_data = camcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_7),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_3_csid_cwk_swc = {
	.cmd_wcgw = 0xf0a8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_2_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_3_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_wite_0_cwk_swc[] = {
	F(320000000, P_CAMCC_PWW7_OUT_ODD, 1, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAMCC_PWW7_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
};

static stwuct cwk_wcg2 camcc_ife_wite_0_cwk_swc = {
	.cmd_wcgw = 0xc004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_ife_wite_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_0_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_0_csid_cwk_swc = {
	.cmd_wcgw = 0xc020,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_2_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_0_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_1_cwk_swc = {
	.cmd_wcgw = 0xc048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_ife_wite_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_1_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_1_csid_cwk_swc = {
	.cmd_wcgw = 0xc064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_2_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_1_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_2_cwk_swc = {
	.cmd_wcgw = 0xc240,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_ife_wite_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_2_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_2_csid_cwk_swc = {
	.cmd_wcgw = 0xc25c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_2_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_2_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_3_cwk_swc = {
	.cmd_wcgw = 0xc284,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_ife_wite_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_3_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_3_csid_cwk_swc = {
	.cmd_wcgw = 0xc2a0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_ife_2_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_3_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ipe_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(320000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(475000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(520000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_ipe_0_cwk_swc = {
	.cmd_wcgw = 0x8010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_8,
	.fweq_tbw = ftbw_camcc_ipe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ipe_0_cwk_swc",
		.pawent_data = camcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_8),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_jpeg_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_CAMCC_PWW0_OUT_ODD, 2, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAMCC_PWW7_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
};

static stwuct cwk_wcg2 camcc_jpeg_cwk_swc = {
	.cmd_wcgw = 0xc08c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_jpeg_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_jpeg_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_wwme_cwk_swc[] = {
	F(240000000, P_CAMCC_PWW7_OUT_EVEN, 2, 0, 0),
	F(300000000, P_CAMCC_PWW0_OUT_EVEN, 2, 0, 0),
	F(320000000, P_CAMCC_PWW7_OUT_ODD, 1, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_MAIN, 3, 0, 0),
};

static stwuct cwk_wcg2 camcc_wwme_cwk_swc = {
	.cmd_wcgw = 0xc144,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_wwme_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_wwme_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_mcwk0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_CAMCC_PWW2_OUT_EAWWY, 10, 1, 4),
	F(64000000, P_CAMCC_PWW2_OUT_EAWWY, 15, 0, 0),
};

static stwuct cwk_wcg2 camcc_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x5004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk0_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x5024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk1_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x5044,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk2_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x5064,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk3_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk4_cwk_swc = {
	.cmd_wcgw = 0x5084,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk4_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk5_cwk_swc = {
	.cmd_wcgw = 0x50a4,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk5_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk6_cwk_swc = {
	.cmd_wcgw = 0x50c4,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk6_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk7_cwk_swc = {
	.cmd_wcgw = 0x50e4,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk7_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_sweep_cwk_swc[] = {
	F(32000, P_SWEEP_CWK, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_sweep_cwk_swc = {
	.cmd_wcgw = 0xc1e8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_9,
	.fweq_tbw = ftbw_camcc_sweep_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_sweep_cwk_swc",
		.pawent_data = camcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_9),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_swow_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(80000000, P_CAMCC_PWW7_OUT_EVEN, 6, 0, 0),
};

static stwuct cwk_wcg2 camcc_swow_ahb_cwk_swc = {
	.cmd_wcgw = 0x7058,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_0,
	.fweq_tbw = ftbw_camcc_swow_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_swow_ahb_cwk_swc",
		.pawent_data = camcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_xo_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
};

static stwuct cwk_wcg2 camcc_xo_cwk_swc = {
	.cmd_wcgw = 0xc1cc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_10,
	.fweq_tbw = ftbw_camcc_xo_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_xo_cwk_swc",
		.pawent_data = camcc_pawent_data_10_ao,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_10_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch camcc_bps_ahb_cwk = {
	.hawt_weg = 0x7070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7070,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_bps_aweg_cwk = {
	.hawt_weg = 0x7054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_bps_axi_cwk = {
	.hawt_weg = 0x7038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_bps_cwk = {
	.hawt_weg = 0x7028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_bps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_camnoc_axi_cwk = {
	.hawt_weg = 0xc18c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc18c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_camnoc_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_camnoc_dcd_xo_cwk = {
	.hawt_weg = 0xc194,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc194,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_camnoc_dcd_xo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cci_0_cwk = {
	.hawt_weg = 0xc120,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc120,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cci_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cci_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cci_1_cwk = {
	.hawt_weg = 0xc13c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc13c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cci_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cci_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cci_2_cwk = {
	.hawt_weg = 0xc21c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc21c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cci_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cci_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cci_3_cwk = {
	.hawt_weg = 0xc238,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc238,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cci_3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cci_3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cowe_ahb_cwk = {
	.hawt_weg = 0xc1c8,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0xc1c8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cowe_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cpas_ahb_cwk = {
	.hawt_weg = 0xc168,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc168,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cpas_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi0phytimew_cwk = {
	.hawt_weg = 0x601c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x601c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi0phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi1phytimew_cwk = {
	.hawt_weg = 0x6040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi1phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi2phytimew_cwk = {
	.hawt_weg = 0x6064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi2phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi3phytimew_cwk = {
	.hawt_weg = 0x608c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x608c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi3phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi3phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy0_cwk = {
	.hawt_weg = 0x6020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy1_cwk = {
	.hawt_weg = 0x6044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy2_cwk = {
	.hawt_weg = 0x6068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy3_cwk = {
	.hawt_weg = 0x6090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_gdsc_cwk = {
	.hawt_weg = 0xc1e4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc1e4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_gdsc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_icp_ahb_cwk = {
	.hawt_weg = 0xc0d8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0d8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_icp_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_icp_cwk = {
	.hawt_weg = 0xc0d0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_icp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_icp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_axi_cwk = {
	.hawt_weg = 0xa080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_cwk = {
	.hawt_weg = 0xa028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_cphy_wx_cwk = {
	.hawt_weg = 0xa07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_csid_cwk = {
	.hawt_weg = 0xa054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_0_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_dsp_cwk = {
	.hawt_weg = 0xa038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_axi_cwk = {
	.hawt_weg = 0xb068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_cwk = {
	.hawt_weg = 0xb028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_cphy_wx_cwk = {
	.hawt_weg = 0xb064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_csid_cwk = {
	.hawt_weg = 0xb054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_1_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_dsp_cwk = {
	.hawt_weg = 0xb038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_axi_cwk = {
	.hawt_weg = 0xf068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_cwk = {
	.hawt_weg = 0xf028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_cphy_wx_cwk = {
	.hawt_weg = 0xf064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_csid_cwk = {
	.hawt_weg = 0xf054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_2_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_dsp_cwk = {
	.hawt_weg = 0xf038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_3_axi_cwk = {
	.hawt_weg = 0xf0d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf0d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_3_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_3_cwk = {
	.hawt_weg = 0xf094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_3_cphy_wx_cwk = {
	.hawt_weg = 0xf0d0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf0d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_3_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_3_csid_cwk = {
	.hawt_weg = 0xf0c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf0c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_3_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_3_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_3_dsp_cwk = {
	.hawt_weg = 0xf0a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf0a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_3_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_0_cwk = {
	.hawt_weg = 0xc01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_0_cphy_wx_cwk = {
	.hawt_weg = 0xc040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_0_csid_cwk = {
	.hawt_weg = 0xc038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_0_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_1_cwk = {
	.hawt_weg = 0xc060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_1_cphy_wx_cwk = {
	.hawt_weg = 0xc084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_1_csid_cwk = {
	.hawt_weg = 0xc07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_1_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_2_cwk = {
	.hawt_weg = 0xc258,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc258,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_2_cphy_wx_cwk = {
	.hawt_weg = 0xc27c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc27c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_2_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_2_csid_cwk = {
	.hawt_weg = 0xc274,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc274,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_2_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_2_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_3_cwk = {
	.hawt_weg = 0xc29c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc29c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_3_cphy_wx_cwk = {
	.hawt_weg = 0xc2c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc2c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_3_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_3_csid_cwk = {
	.hawt_weg = 0xc2b8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc2b8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_3_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_3_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_ahb_cwk = {
	.hawt_weg = 0x8040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_aweg_cwk = {
	.hawt_weg = 0x803c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x803c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_axi_cwk = {
	.hawt_weg = 0x8038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_cwk = {
	.hawt_weg = 0x8028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ipe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_1_ahb_cwk = {
	.hawt_weg = 0x9028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_1_aweg_cwk = {
	.hawt_weg = 0x9024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_1_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_1_axi_cwk = {
	.hawt_weg = 0x9020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_1_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_camnoc_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_1_cwk = {
	.hawt_weg = 0x9010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ipe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_jpeg_cwk = {
	.hawt_weg = 0xc0a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_jpeg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_jpeg_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_wwme_cwk = {
	.hawt_weg = 0xc15c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc15c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_wwme_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_wwme_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk0_cwk = {
	.hawt_weg = 0x501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk1_cwk = {
	.hawt_weg = 0x503c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x503c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk2_cwk = {
	.hawt_weg = 0x505c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x505c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk3_cwk = {
	.hawt_weg = 0x507c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x507c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk4_cwk = {
	.hawt_weg = 0x509c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x509c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk5_cwk = {
	.hawt_weg = 0x50bc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50bc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk6_cwk = {
	.hawt_weg = 0x50dc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50dc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk7_cwk = {
	.hawt_weg = 0x50fc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50fc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_sweep_cwk = {
	.hawt_weg = 0xc200,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc200,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc titan_top_gdsc;

static stwuct gdsc bps_gdsc = {
	.gdscw = 0x7004,
	.pd = {
		.name = "bps_gdsc",
	},
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_0_gdsc = {
	.gdscw = 0xa004,
	.pd = {
		.name = "ife_0_gdsc",
	},
	.fwags = WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_1_gdsc = {
	.gdscw = 0xb004,
	.pd = {
		.name = "ife_1_gdsc",
	},
	.fwags = WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_2_gdsc = {
	.gdscw = 0xf004,
	.pd = {
		.name = "ife_2_gdsc",
	},
	.fwags = WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_3_gdsc = {
	.gdscw = 0xf070,
	.pd = {
		.name = "ife_3_gdsc",
	},
	.fwags = WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ipe_0_gdsc = {
	.gdscw = 0x8004,
	.pd = {
		.name = "ipe_0_gdsc",
	},
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ipe_1_gdsc = {
	.gdscw = 0x9004,
	.pd = {
		.name = "ipe_1_gdsc",
	},
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc titan_top_gdsc = {
	.gdscw = 0xc1bc,
	.pd = {
		.name = "titan_top_gdsc",
	},
	.fwags = WETAIN_FF_ENABWE,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *camcc_sc8280xp_cwocks[] = {
	[CAMCC_BPS_AHB_CWK] = &camcc_bps_ahb_cwk.cwkw,
	[CAMCC_BPS_AWEG_CWK] = &camcc_bps_aweg_cwk.cwkw,
	[CAMCC_BPS_AXI_CWK] = &camcc_bps_axi_cwk.cwkw,
	[CAMCC_BPS_CWK] = &camcc_bps_cwk.cwkw,
	[CAMCC_BPS_CWK_SWC] = &camcc_bps_cwk_swc.cwkw,
	[CAMCC_CAMNOC_AXI_CWK] = &camcc_camnoc_axi_cwk.cwkw,
	[CAMCC_CAMNOC_AXI_CWK_SWC] = &camcc_camnoc_axi_cwk_swc.cwkw,
	[CAMCC_CAMNOC_DCD_XO_CWK] = &camcc_camnoc_dcd_xo_cwk.cwkw,
	[CAMCC_CCI_0_CWK] = &camcc_cci_0_cwk.cwkw,
	[CAMCC_CCI_0_CWK_SWC] = &camcc_cci_0_cwk_swc.cwkw,
	[CAMCC_CCI_1_CWK] = &camcc_cci_1_cwk.cwkw,
	[CAMCC_CCI_1_CWK_SWC] = &camcc_cci_1_cwk_swc.cwkw,
	[CAMCC_CCI_2_CWK] = &camcc_cci_2_cwk.cwkw,
	[CAMCC_CCI_2_CWK_SWC] = &camcc_cci_2_cwk_swc.cwkw,
	[CAMCC_CCI_3_CWK] = &camcc_cci_3_cwk.cwkw,
	[CAMCC_CCI_3_CWK_SWC] = &camcc_cci_3_cwk_swc.cwkw,
	[CAMCC_COWE_AHB_CWK] = &camcc_cowe_ahb_cwk.cwkw,
	[CAMCC_CPAS_AHB_CWK] = &camcc_cpas_ahb_cwk.cwkw,
	[CAMCC_CPHY_WX_CWK_SWC] = &camcc_cphy_wx_cwk_swc.cwkw,
	[CAMCC_CSI0PHYTIMEW_CWK] = &camcc_csi0phytimew_cwk.cwkw,
	[CAMCC_CSI0PHYTIMEW_CWK_SWC] = &camcc_csi0phytimew_cwk_swc.cwkw,
	[CAMCC_CSI1PHYTIMEW_CWK] = &camcc_csi1phytimew_cwk.cwkw,
	[CAMCC_CSI1PHYTIMEW_CWK_SWC] = &camcc_csi1phytimew_cwk_swc.cwkw,
	[CAMCC_CSI2PHYTIMEW_CWK] = &camcc_csi2phytimew_cwk.cwkw,
	[CAMCC_CSI2PHYTIMEW_CWK_SWC] = &camcc_csi2phytimew_cwk_swc.cwkw,
	[CAMCC_CSI3PHYTIMEW_CWK] = &camcc_csi3phytimew_cwk.cwkw,
	[CAMCC_CSI3PHYTIMEW_CWK_SWC] = &camcc_csi3phytimew_cwk_swc.cwkw,
	[CAMCC_CSIPHY0_CWK] = &camcc_csiphy0_cwk.cwkw,
	[CAMCC_CSIPHY1_CWK] = &camcc_csiphy1_cwk.cwkw,
	[CAMCC_CSIPHY2_CWK] = &camcc_csiphy2_cwk.cwkw,
	[CAMCC_CSIPHY3_CWK] = &camcc_csiphy3_cwk.cwkw,
	[CAMCC_FAST_AHB_CWK_SWC] = &camcc_fast_ahb_cwk_swc.cwkw,
	[CAMCC_GDSC_CWK] = &camcc_gdsc_cwk.cwkw,
	[CAMCC_ICP_AHB_CWK] = &camcc_icp_ahb_cwk.cwkw,
	[CAMCC_ICP_CWK] = &camcc_icp_cwk.cwkw,
	[CAMCC_ICP_CWK_SWC] = &camcc_icp_cwk_swc.cwkw,
	[CAMCC_IFE_0_AXI_CWK] = &camcc_ife_0_axi_cwk.cwkw,
	[CAMCC_IFE_0_CWK] = &camcc_ife_0_cwk.cwkw,
	[CAMCC_IFE_0_CWK_SWC] = &camcc_ife_0_cwk_swc.cwkw,
	[CAMCC_IFE_0_CPHY_WX_CWK] = &camcc_ife_0_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_0_CSID_CWK] = &camcc_ife_0_csid_cwk.cwkw,
	[CAMCC_IFE_0_CSID_CWK_SWC] = &camcc_ife_0_csid_cwk_swc.cwkw,
	[CAMCC_IFE_0_DSP_CWK] = &camcc_ife_0_dsp_cwk.cwkw,
	[CAMCC_IFE_1_AXI_CWK] = &camcc_ife_1_axi_cwk.cwkw,
	[CAMCC_IFE_1_CWK] = &camcc_ife_1_cwk.cwkw,
	[CAMCC_IFE_1_CWK_SWC] = &camcc_ife_1_cwk_swc.cwkw,
	[CAMCC_IFE_1_CPHY_WX_CWK] = &camcc_ife_1_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_1_CSID_CWK] = &camcc_ife_1_csid_cwk.cwkw,
	[CAMCC_IFE_1_CSID_CWK_SWC] = &camcc_ife_1_csid_cwk_swc.cwkw,
	[CAMCC_IFE_1_DSP_CWK] = &camcc_ife_1_dsp_cwk.cwkw,
	[CAMCC_IFE_2_AXI_CWK] = &camcc_ife_2_axi_cwk.cwkw,
	[CAMCC_IFE_2_CWK] = &camcc_ife_2_cwk.cwkw,
	[CAMCC_IFE_2_CWK_SWC] = &camcc_ife_2_cwk_swc.cwkw,
	[CAMCC_IFE_2_CPHY_WX_CWK] = &camcc_ife_2_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_2_CSID_CWK] = &camcc_ife_2_csid_cwk.cwkw,
	[CAMCC_IFE_2_CSID_CWK_SWC] = &camcc_ife_2_csid_cwk_swc.cwkw,
	[CAMCC_IFE_2_DSP_CWK] = &camcc_ife_2_dsp_cwk.cwkw,
	[CAMCC_IFE_3_AXI_CWK] = &camcc_ife_3_axi_cwk.cwkw,
	[CAMCC_IFE_3_CWK] = &camcc_ife_3_cwk.cwkw,
	[CAMCC_IFE_3_CWK_SWC] = &camcc_ife_3_cwk_swc.cwkw,
	[CAMCC_IFE_3_CPHY_WX_CWK] = &camcc_ife_3_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_3_CSID_CWK] = &camcc_ife_3_csid_cwk.cwkw,
	[CAMCC_IFE_3_CSID_CWK_SWC] = &camcc_ife_3_csid_cwk_swc.cwkw,
	[CAMCC_IFE_3_DSP_CWK] = &camcc_ife_3_dsp_cwk.cwkw,
	[CAMCC_IFE_WITE_0_CWK] = &camcc_ife_wite_0_cwk.cwkw,
	[CAMCC_IFE_WITE_0_CWK_SWC] = &camcc_ife_wite_0_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_0_CPHY_WX_CWK] = &camcc_ife_wite_0_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_WITE_0_CSID_CWK] = &camcc_ife_wite_0_csid_cwk.cwkw,
	[CAMCC_IFE_WITE_0_CSID_CWK_SWC] = &camcc_ife_wite_0_csid_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_1_CWK] = &camcc_ife_wite_1_cwk.cwkw,
	[CAMCC_IFE_WITE_1_CWK_SWC] = &camcc_ife_wite_1_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_1_CPHY_WX_CWK] = &camcc_ife_wite_1_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_WITE_1_CSID_CWK] = &camcc_ife_wite_1_csid_cwk.cwkw,
	[CAMCC_IFE_WITE_1_CSID_CWK_SWC] = &camcc_ife_wite_1_csid_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_2_CWK] = &camcc_ife_wite_2_cwk.cwkw,
	[CAMCC_IFE_WITE_2_CWK_SWC] = &camcc_ife_wite_2_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_2_CPHY_WX_CWK] = &camcc_ife_wite_2_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_WITE_2_CSID_CWK] = &camcc_ife_wite_2_csid_cwk.cwkw,
	[CAMCC_IFE_WITE_2_CSID_CWK_SWC] = &camcc_ife_wite_2_csid_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_3_CWK] = &camcc_ife_wite_3_cwk.cwkw,
	[CAMCC_IFE_WITE_3_CWK_SWC] = &camcc_ife_wite_3_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_3_CPHY_WX_CWK] = &camcc_ife_wite_3_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_WITE_3_CSID_CWK] = &camcc_ife_wite_3_csid_cwk.cwkw,
	[CAMCC_IFE_WITE_3_CSID_CWK_SWC] = &camcc_ife_wite_3_csid_cwk_swc.cwkw,
	[CAMCC_IPE_0_AHB_CWK] = &camcc_ipe_0_ahb_cwk.cwkw,
	[CAMCC_IPE_0_AWEG_CWK] = &camcc_ipe_0_aweg_cwk.cwkw,
	[CAMCC_IPE_0_AXI_CWK] = &camcc_ipe_0_axi_cwk.cwkw,
	[CAMCC_IPE_0_CWK] = &camcc_ipe_0_cwk.cwkw,
	[CAMCC_IPE_0_CWK_SWC] = &camcc_ipe_0_cwk_swc.cwkw,
	[CAMCC_IPE_1_AHB_CWK] = &camcc_ipe_1_ahb_cwk.cwkw,
	[CAMCC_IPE_1_AWEG_CWK] = &camcc_ipe_1_aweg_cwk.cwkw,
	[CAMCC_IPE_1_AXI_CWK] = &camcc_ipe_1_axi_cwk.cwkw,
	[CAMCC_IPE_1_CWK] = &camcc_ipe_1_cwk.cwkw,
	[CAMCC_JPEG_CWK] = &camcc_jpeg_cwk.cwkw,
	[CAMCC_JPEG_CWK_SWC] = &camcc_jpeg_cwk_swc.cwkw,
	[CAMCC_WWME_CWK] = &camcc_wwme_cwk.cwkw,
	[CAMCC_WWME_CWK_SWC] = &camcc_wwme_cwk_swc.cwkw,
	[CAMCC_MCWK0_CWK] = &camcc_mcwk0_cwk.cwkw,
	[CAMCC_MCWK0_CWK_SWC] = &camcc_mcwk0_cwk_swc.cwkw,
	[CAMCC_MCWK1_CWK] = &camcc_mcwk1_cwk.cwkw,
	[CAMCC_MCWK1_CWK_SWC] = &camcc_mcwk1_cwk_swc.cwkw,
	[CAMCC_MCWK2_CWK] = &camcc_mcwk2_cwk.cwkw,
	[CAMCC_MCWK2_CWK_SWC] = &camcc_mcwk2_cwk_swc.cwkw,
	[CAMCC_MCWK3_CWK] = &camcc_mcwk3_cwk.cwkw,
	[CAMCC_MCWK3_CWK_SWC] = &camcc_mcwk3_cwk_swc.cwkw,
	[CAMCC_MCWK4_CWK] = &camcc_mcwk4_cwk.cwkw,
	[CAMCC_MCWK4_CWK_SWC] = &camcc_mcwk4_cwk_swc.cwkw,
	[CAMCC_MCWK5_CWK] = &camcc_mcwk5_cwk.cwkw,
	[CAMCC_MCWK5_CWK_SWC] = &camcc_mcwk5_cwk_swc.cwkw,
	[CAMCC_MCWK6_CWK] = &camcc_mcwk6_cwk.cwkw,
	[CAMCC_MCWK6_CWK_SWC] = &camcc_mcwk6_cwk_swc.cwkw,
	[CAMCC_MCWK7_CWK] = &camcc_mcwk7_cwk.cwkw,
	[CAMCC_MCWK7_CWK_SWC] = &camcc_mcwk7_cwk_swc.cwkw,
	[CAMCC_PWW0] = &camcc_pww0.cwkw,
	[CAMCC_PWW0_OUT_EVEN] = &camcc_pww0_out_even.cwkw,
	[CAMCC_PWW0_OUT_ODD] = &camcc_pww0_out_odd.cwkw,
	[CAMCC_PWW1] = &camcc_pww1.cwkw,
	[CAMCC_PWW1_OUT_EVEN] = &camcc_pww1_out_even.cwkw,
	[CAMCC_PWW2] = &camcc_pww2.cwkw,
	[CAMCC_PWW3] = &camcc_pww3.cwkw,
	[CAMCC_PWW3_OUT_EVEN] = &camcc_pww3_out_even.cwkw,
	[CAMCC_PWW4] = &camcc_pww4.cwkw,
	[CAMCC_PWW4_OUT_EVEN] = &camcc_pww4_out_even.cwkw,
	[CAMCC_PWW5] = &camcc_pww5.cwkw,
	[CAMCC_PWW5_OUT_EVEN] = &camcc_pww5_out_even.cwkw,
	[CAMCC_PWW6] = &camcc_pww6.cwkw,
	[CAMCC_PWW6_OUT_EVEN] = &camcc_pww6_out_even.cwkw,
	[CAMCC_PWW7] = &camcc_pww7.cwkw,
	[CAMCC_PWW7_OUT_EVEN] = &camcc_pww7_out_even.cwkw,
	[CAMCC_PWW7_OUT_ODD] = &camcc_pww7_out_odd.cwkw,
	[CAMCC_SWEEP_CWK] = &camcc_sweep_cwk.cwkw,
	[CAMCC_SWEEP_CWK_SWC] = &camcc_sweep_cwk_swc.cwkw,
	[CAMCC_SWOW_AHB_CWK_SWC] = &camcc_swow_ahb_cwk_swc.cwkw,
	[CAMCC_XO_CWK_SWC] = &camcc_xo_cwk_swc.cwkw,
};

static stwuct gdsc *camcc_sc8280xp_gdscs[] = {
	[BPS_GDSC] = &bps_gdsc,
	[IFE_0_GDSC] = &ife_0_gdsc,
	[IFE_1_GDSC] = &ife_1_gdsc,
	[IFE_2_GDSC] = &ife_2_gdsc,
	[IFE_3_GDSC] = &ife_3_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[IPE_1_GDSC] = &ipe_1_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
};

static const stwuct qcom_weset_map camcc_sc8280xp_wesets[] = {
	[CAMCC_BPS_BCW] = { 0x7000 },
	[CAMCC_CAMNOC_BCW] = { 0xc16c },
	[CAMCC_CCI_BCW] = { 0xc104 },
	[CAMCC_CPAS_BCW] = { 0xc164 },
	[CAMCC_CSI0PHY_BCW] = { 0x6000 },
	[CAMCC_CSI1PHY_BCW] = { 0x6024 },
	[CAMCC_CSI2PHY_BCW] = { 0x6048 },
	[CAMCC_CSI3PHY_BCW] = { 0x6070 },
	[CAMCC_ICP_BCW] = { 0xc0b4 },
	[CAMCC_IFE_0_BCW] = { 0xa000 },
	[CAMCC_IFE_1_BCW] = { 0xb000 },
	[CAMCC_IFE_2_BCW] = { 0xf000 },
	[CAMCC_IFE_3_BCW] = { 0xf06c },
	[CAMCC_IFE_WITE_0_BCW] = { 0xc000 },
	[CAMCC_IFE_WITE_1_BCW] = { 0xc044 },
	[CAMCC_IFE_WITE_2_BCW] = { 0xc23c },
	[CAMCC_IFE_WITE_3_BCW] = { 0xc280 },
	[CAMCC_IPE_0_BCW] = { 0x8000 },
	[CAMCC_IPE_1_BCW] = { 0x9000 },
	[CAMCC_JPEG_BCW] = { 0xc088 },
	[CAMCC_WWME_BCW] = { 0xc140 },
};

static const stwuct wegmap_config camcc_sc8280xp_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x13020,
	.fast_io = twue,
};

static stwuct qcom_cc_desc camcc_sc8280xp_desc = {
	.config = &camcc_sc8280xp_wegmap_config,
	.cwks = camcc_sc8280xp_cwocks,
	.num_cwks = AWWAY_SIZE(camcc_sc8280xp_cwocks),
	.wesets = camcc_sc8280xp_wesets,
	.num_wesets = AWWAY_SIZE(camcc_sc8280xp_wesets),
	.gdscs = camcc_sc8280xp_gdscs,
	.num_gdscs = AWWAY_SIZE(camcc_sc8280xp_gdscs),
};

static const stwuct of_device_id camcc_sc8280xp_match_tabwe[] = {
	{ .compatibwe = "qcom,sc8280xp-camcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, camcc_sc8280xp_match_tabwe);

static int camcc_sc8280xp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wegmap = qcom_cc_map(pdev, &camcc_sc8280xp_desc);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto eww_put_wpm;
	}

	cwk_wucid_pww_configuwe(&camcc_pww0, wegmap, &camcc_pww0_config);
	cwk_wucid_pww_configuwe(&camcc_pww1, wegmap, &camcc_pww1_config);
	cwk_zonda_pww_configuwe(&camcc_pww2, wegmap, &camcc_pww2_config);
	cwk_wucid_pww_configuwe(&camcc_pww3, wegmap, &camcc_pww3_config);
	cwk_wucid_pww_configuwe(&camcc_pww4, wegmap, &camcc_pww4_config);
	cwk_wucid_pww_configuwe(&camcc_pww5, wegmap, &camcc_pww5_config);
	cwk_wucid_pww_configuwe(&camcc_pww6, wegmap, &camcc_pww6_config);
	cwk_wucid_pww_configuwe(&camcc_pww7, wegmap, &camcc_pww7_config);

	/*
	 * Keep camcc_gdsc_cwk awways enabwed:
	 */
	wegmap_update_bits(wegmap, 0xc1e4, BIT(0), 1);

	wet = qcom_cc_weawwy_pwobe(pdev, &camcc_sc8280xp_desc, wegmap);
	if (wet)
		goto eww_disabwe;

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

eww_disabwe:
	wegmap_update_bits(wegmap, 0xc1e4, BIT(0), 0);
eww_put_wpm:
	pm_wuntime_put_sync(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew camcc_sc8280xp_dwivew = {
	.pwobe = camcc_sc8280xp_pwobe,
	.dwivew = {
		.name = "camcc-sc8280xp",
		.of_match_tabwe = camcc_sc8280xp_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(camcc_sc8280xp_dwivew);

MODUWE_DESCWIPTION("QCOM CAMCC SC8280XP Dwivew");
MODUWE_WICENSE("GPW");
