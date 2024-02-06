// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm6350-camcc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	DT_BI_TCXO,
};

enum {
	P_BI_TCXO,
	P_CAMCC_PWW0_OUT_EVEN,
	P_CAMCC_PWW0_OUT_MAIN,
	P_CAMCC_PWW1_OUT_EVEN,
	P_CAMCC_PWW1_OUT_MAIN,
	P_CAMCC_PWW2_OUT_EAWWY,
	P_CAMCC_PWW2_OUT_MAIN,
	P_CAMCC_PWW3_OUT_MAIN,
};

static stwuct pww_vco fabia_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 600MHz configuwation */
static const stwuct awpha_pww_config camcc_pww0_config = {
	.w = 0x1f,
	.awpha = 0x4000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002067,
	.test_ctw_vaw = 0x40000000,
	.test_ctw_hi_vaw = 0x00000002,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00004805,
};

static stwuct cwk_awpha_pww camcc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv camcc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

/* 808MHz configuwation */
static const stwuct awpha_pww_config camcc_pww1_config = {
	.w = 0x2a,
	.awpha = 0x1555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002067,
	.test_ctw_vaw = 0x40000000,
	.test_ctw_hi_vaw = 0x00000000,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00004805,
};

static stwuct cwk_awpha_pww camcc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww1_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv camcc_pww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww1_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww1_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

/* 1920MHz configuwation */
static const stwuct awpha_pww_config camcc_pww2_config = {
	.w = 0x64,
	.awpha = 0x0,
	.post_div_vaw = 0x3 << 8,
	.post_div_mask = 0x3 << 8,
	.aux_output_mask = BIT(1),
	.main_output_mask = BIT(0),
	.eawwy_output_mask = BIT(3),
	.config_ctw_vaw = 0x20000800,
	.config_ctw_hi_vaw = 0x400003d2,
	.test_ctw_vaw = 0x04000400,
	.test_ctw_hi_vaw = 0x00004000,
};

static stwuct cwk_awpha_pww camcc_pww2 = {
	.offset = 0x2000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_AGEWA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww2",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_agewa_ops,
		},
	},
};

static stwuct cwk_fixed_factow camcc_pww2_out_eawwy = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww2_out_eawwy",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww2.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_camcc_pww2_out_main[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv camcc_pww2_out_main = {
	.offset = 0x2000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_camcc_pww2_out_main,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_camcc_pww2_out_main),
	.width = 2,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_AGEWA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_pww2_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&camcc_pww2.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_ops,
	},
};

/* 384MHz configuwation */
static const stwuct awpha_pww_config camcc_pww3_config = {
	.w = 0x14,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002067,
	.test_ctw_vaw = 0x40000000,
	.test_ctw_hi_vaw = 0x00000002,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00014805,
};

static stwuct cwk_awpha_pww camcc_pww3 = {
	.offset = 0x3000,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_pww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct pawent_map camcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW1_OUT_EVEN, 3 },
	{ P_CAMCC_PWW2_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww1_out_even.cwkw.hw },
	{ .hw = &camcc_pww2_out_main.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW3_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww3.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW2_OUT_EAWWY, 3 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww2_out_eawwy.hw },
};

static const stwuct pawent_map camcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW1_OUT_EVEN, 3 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww1_out_even.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW1_OUT_EVEN, 3 },
	{ P_CAMCC_PWW3_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww1_out_even.cwkw.hw },
	{ .hw = &camcc_pww3.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW2_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww2_out_main.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW1_OUT_MAIN, 2 },
	{ P_CAMCC_PWW2_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_7[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww1.cwkw.hw },
	{ .hw = &camcc_pww2_out_main.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_8[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW0_OUT_MAIN, 1 },
	{ P_CAMCC_PWW1_OUT_MAIN, 2 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_8[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww0.cwkw.hw },
	{ .hw = &camcc_pww1.cwkw.hw },
};

static const stwuct pawent_map camcc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAMCC_PWW2_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data camcc_pawent_data_9[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &camcc_pww2_out_main.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_camcc_bps_cwk_swc[] = {
	F(200000000, P_CAMCC_PWW0_OUT_MAIN, 3, 0, 0),
	F(320000000, P_CAMCC_PWW2_OUT_MAIN, 1.5, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(480000000, P_CAMCC_PWW2_OUT_MAIN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_bps_cwk_swc = {
	.cmd_wcgw = 0x6010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_bps_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_cci_0_cwk_swc[] = {
	F(37500000, P_CAMCC_PWW0_OUT_EVEN, 8, 0, 0),
	F(50000000, P_CAMCC_PWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_CAMCC_PWW0_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_cci_0_cwk_swc = {
	.cmd_wcgw = 0xf004,
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
	.cmd_wcgw = 0x10004,
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

static const stwuct fweq_tbw ftbw_camcc_cphy_wx_cwk_swc[] = {
	F(150000000, P_CAMCC_PWW0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
	F(384000000, P_CAMCC_PWW3_OUT_MAIN, 1, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_MAIN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0x9064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_cphy_wx_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_csi0phytimew_cwk_swc[] = {
	F(300000000, P_CAMCC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x5004,
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
	.cmd_wcgw = 0x5028,
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
	.cmd_wcgw = 0x504c,
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
	.cmd_wcgw = 0x5070,
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
	F(100000000, P_CAMCC_PWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_CAMCC_PWW0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_CAMCC_PWW0_OUT_MAIN, 2, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_fast_ahb_cwk_swc = {
	.cmd_wcgw = 0x603c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_4,
	.fweq_tbw = ftbw_camcc_fast_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_fast_ahb_cwk_swc",
		.pawent_data = camcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_icp_cwk_swc[] = {
	F(240000000, P_CAMCC_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(384000000, P_CAMCC_PWW3_OUT_MAIN, 1, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_icp_cwk_swc = {
	.cmd_wcgw = 0xe014,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_5,
	.fweq_tbw = ftbw_camcc_icp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_icp_cwk_swc",
		.pawent_data = camcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_5),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_0_cwk_swc[] = {
	F(240000000, P_CAMCC_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(320000000, P_CAMCC_PWW2_OUT_MAIN, 1.5, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(480000000, P_CAMCC_PWW2_OUT_MAIN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_ife_0_cwk_swc = {
	.cmd_wcgw = 0x9010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_0_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_0_csid_cwk_swc = {
	.cmd_wcgw = 0x903c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_0_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_1_cwk_swc = {
	.cmd_wcgw = 0xa010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_1_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_1_csid_cwk_swc = {
	.cmd_wcgw = 0xa034,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_1_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_2_cwk_swc = {
	.cmd_wcgw = 0xb00c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_2_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_2_csid_cwk_swc = {
	.cmd_wcgw = 0xb030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_2_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ife_wite_cwk_swc[] = {
	F(320000000, P_CAMCC_PWW2_OUT_MAIN, 1.5, 0, 0),
	F(400000000, P_CAMCC_PWW0_OUT_MAIN, 1.5, 0, 0),
	F(480000000, P_CAMCC_PWW2_OUT_MAIN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_ife_wite_cwk_swc = {
	.cmd_wcgw = 0xc004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_6,
	.fweq_tbw = ftbw_camcc_ife_wite_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_cwk_swc",
		.pawent_data = camcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_ife_wite_csid_cwk_swc = {
	.cmd_wcgw = 0xc024,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_2,
	.fweq_tbw = ftbw_camcc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ife_wite_csid_cwk_swc",
		.pawent_data = camcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_ipe_0_cwk_swc[] = {
	F(240000000, P_CAMCC_PWW2_OUT_MAIN, 2, 0, 0),
	F(320000000, P_CAMCC_PWW2_OUT_MAIN, 1.5, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_MAIN, 2, 0, 0),
	F(538666667, P_CAMCC_PWW1_OUT_MAIN, 1.5, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_ipe_0_cwk_swc = {
	.cmd_wcgw = 0x7010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_7,
	.fweq_tbw = ftbw_camcc_ipe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_ipe_0_cwk_swc",
		.pawent_data = camcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_7),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_jpeg_cwk_swc[] = {
	F(66666667, P_CAMCC_PWW0_OUT_MAIN, 9, 0, 0),
	F(133333333, P_CAMCC_PWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_CAMCC_PWW0_OUT_MAIN, 3, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_EVEN, 1, 0, 0),
	F(480000000, P_CAMCC_PWW2_OUT_MAIN, 1, 0, 0),
	F(600000000, P_CAMCC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_jpeg_cwk_swc = {
	.cmd_wcgw = 0xd004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_1,
	.fweq_tbw = ftbw_camcc_jpeg_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_jpeg_cwk_swc",
		.pawent_data = camcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_wwme_cwk_swc[] = {
	F(200000000, P_CAMCC_PWW0_OUT_MAIN, 3, 0, 0),
	F(269333333, P_CAMCC_PWW1_OUT_MAIN, 3, 0, 0),
	F(323200000, P_CAMCC_PWW1_OUT_MAIN, 2.5, 0, 0),
	F(404000000, P_CAMCC_PWW1_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_wwme_cwk_swc = {
	.cmd_wcgw = 0x11004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_8,
	.fweq_tbw = ftbw_camcc_wwme_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_wwme_cwk_swc",
		.pawent_data = camcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_8),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_mcwk0_cwk_swc[] = {
	F(19200000, P_CAMCC_PWW2_OUT_EAWWY, 1, 1, 50),
	F(24000000, P_CAMCC_PWW2_OUT_EAWWY, 10, 1, 4),
	F(64000000, P_CAMCC_PWW2_OUT_EAWWY, 15, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x4004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_3,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk0_cwk_swc",
		.pawent_data = camcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x4024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_3,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk1_cwk_swc",
		.pawent_data = camcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x4044,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_3,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk2_cwk_swc",
		.pawent_data = camcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x4064,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_3,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk3_cwk_swc",
		.pawent_data = camcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camcc_mcwk4_cwk_swc = {
	.cmd_wcgw = 0x4084,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_3,
	.fweq_tbw = ftbw_camcc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_mcwk4_cwk_swc",
		.pawent_data = camcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_camcc_swow_ahb_cwk_swc[] = {
	F(80000000, P_CAMCC_PWW2_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camcc_swow_ahb_cwk_swc = {
	.cmd_wcgw = 0x6058,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = camcc_pawent_map_9,
	.fweq_tbw = ftbw_camcc_swow_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camcc_swow_ahb_cwk_swc",
		.pawent_data = camcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(camcc_pawent_data_9),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch camcc_bps_ahb_cwk = {
	.hawt_weg = 0x6070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6070,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_bps_aweg_cwk = {
	.hawt_weg = 0x6054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_fast_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_bps_axi_cwk = {
	.hawt_weg = 0x6038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_bps_cwk = {
	.hawt_weg = 0x6028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_bps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_bps_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_camnoc_axi_cwk = {
	.hawt_weg = 0x13004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_camnoc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cci_0_cwk = {
	.hawt_weg = 0xf01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cci_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cci_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cci_1_cwk = {
	.hawt_weg = 0x1001c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1001c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cci_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cci_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cowe_ahb_cwk = {
	.hawt_weg = 0x14010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x14010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cowe_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_cpas_ahb_cwk = {
	.hawt_weg = 0x12004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_cpas_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi0phytimew_cwk = {
	.hawt_weg = 0x501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi0phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi1phytimew_cwk = {
	.hawt_weg = 0x5040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi1phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi2phytimew_cwk = {
	.hawt_weg = 0x5064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi2phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csi3phytimew_cwk = {
	.hawt_weg = 0x5088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csi3phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_csi3phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy0_cwk = {
	.hawt_weg = 0x5020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy1_cwk = {
	.hawt_weg = 0x5044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy2_cwk = {
	.hawt_weg = 0x5068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_csiphy3_cwk = {
	.hawt_weg = 0x508c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x508c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_csiphy3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_icp_cwk = {
	.hawt_weg = 0xe02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_icp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_icp_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_icp_ts_cwk = {
	.hawt_weg = 0xe00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_icp_ts_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_axi_cwk = {
	.hawt_weg = 0x9080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_cwk = {
	.hawt_weg = 0x9028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_cphy_wx_cwk = {
	.hawt_weg = 0x907c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x907c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_csid_cwk = {
	.hawt_weg = 0x9054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_0_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_0_dsp_cwk = {
	.hawt_weg = 0x9038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_0_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_axi_cwk = {
	.hawt_weg = 0xa058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_cwk = {
	.hawt_weg = 0xa028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_cphy_wx_cwk = {
	.hawt_weg = 0xa054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_csid_cwk = {
	.hawt_weg = 0xa04c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa04c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_1_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_1_dsp_cwk = {
	.hawt_weg = 0xa030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_1_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_axi_cwk = {
	.hawt_weg = 0xb054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_cwk = {
	.hawt_weg = 0xb024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_2_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_cphy_wx_cwk = {
	.hawt_weg = 0xb050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_csid_cwk = {
	.hawt_weg = 0xb048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_2_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_2_dsp_cwk = {
	.hawt_weg = 0xb02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_2_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_2_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_cwk = {
	.hawt_weg = 0xc01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_cphy_wx_cwk = {
	.hawt_weg = 0xc044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ife_wite_csid_cwk = {
	.hawt_weg = 0xc03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ife_wite_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ife_wite_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_ahb_cwk = {
	.hawt_weg = 0x7040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_aweg_cwk = {
	.hawt_weg = 0x703c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x703c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_fast_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_axi_cwk = {
	.hawt_weg = 0x7038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_ipe_0_cwk = {
	.hawt_weg = 0x7028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_ipe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_ipe_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_jpeg_cwk = {
	.hawt_weg = 0xd01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xd01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_jpeg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_jpeg_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_wwme_cwk = {
	.hawt_weg = 0x1101c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1101c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_wwme_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_wwme_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk0_cwk = {
	.hawt_weg = 0x401c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x401c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk1_cwk = {
	.hawt_weg = 0x403c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x403c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk2_cwk = {
	.hawt_weg = 0x405c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x405c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk2_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk3_cwk = {
	.hawt_weg = 0x407c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x407c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk3_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_mcwk4_cwk = {
	.hawt_weg = 0x409c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x409c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_mcwk4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&camcc_mcwk4_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_soc_ahb_cwk = {
	.hawt_weg = 0x1400c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1400c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_soc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camcc_sys_tmw_cwk = {
	.hawt_weg = 0xe034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camcc_sys_tmw_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc bps_gdsc = {
	.gdscw = 0x6004,
	.pd = {
		.name = "bps_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc ipe_0_gdsc = {
	.gdscw = 0x7004,
	.pd = {
		.name = "ipe_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc ife_0_gdsc = {
	.gdscw = 0x9004,
	.pd = {
		.name = "ife_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_1_gdsc = {
	.gdscw = 0xa004,
	.pd = {
		.name = "ife_1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_2_gdsc = {
	.gdscw = 0xb004,
	.pd = {
		.name = "ife_2_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc titan_top_gdsc = {
	.gdscw = 0x14004,
	.pd = {
		.name = "titan_top_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_hw *camcc_sm6350_hws[] = {
	[CAMCC_PWW2_OUT_EAWWY] = &camcc_pww2_out_eawwy.hw,
};

static stwuct cwk_wegmap *camcc_sm6350_cwocks[] = {
	[CAMCC_BPS_AHB_CWK] = &camcc_bps_ahb_cwk.cwkw,
	[CAMCC_BPS_AWEG_CWK] = &camcc_bps_aweg_cwk.cwkw,
	[CAMCC_BPS_AXI_CWK] = &camcc_bps_axi_cwk.cwkw,
	[CAMCC_BPS_CWK] = &camcc_bps_cwk.cwkw,
	[CAMCC_BPS_CWK_SWC] = &camcc_bps_cwk_swc.cwkw,
	[CAMCC_CAMNOC_AXI_CWK] = &camcc_camnoc_axi_cwk.cwkw,
	[CAMCC_CCI_0_CWK] = &camcc_cci_0_cwk.cwkw,
	[CAMCC_CCI_0_CWK_SWC] = &camcc_cci_0_cwk_swc.cwkw,
	[CAMCC_CCI_1_CWK] = &camcc_cci_1_cwk.cwkw,
	[CAMCC_CCI_1_CWK_SWC] = &camcc_cci_1_cwk_swc.cwkw,
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
	[CAMCC_ICP_CWK] = &camcc_icp_cwk.cwkw,
	[CAMCC_ICP_CWK_SWC] = &camcc_icp_cwk_swc.cwkw,
	[CAMCC_ICP_TS_CWK] = &camcc_icp_ts_cwk.cwkw,
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
	[CAMCC_IFE_WITE_CWK] = &camcc_ife_wite_cwk.cwkw,
	[CAMCC_IFE_WITE_CWK_SWC] = &camcc_ife_wite_cwk_swc.cwkw,
	[CAMCC_IFE_WITE_CPHY_WX_CWK] = &camcc_ife_wite_cphy_wx_cwk.cwkw,
	[CAMCC_IFE_WITE_CSID_CWK] = &camcc_ife_wite_csid_cwk.cwkw,
	[CAMCC_IFE_WITE_CSID_CWK_SWC] = &camcc_ife_wite_csid_cwk_swc.cwkw,
	[CAMCC_IPE_0_AHB_CWK] = &camcc_ipe_0_ahb_cwk.cwkw,
	[CAMCC_IPE_0_AWEG_CWK] = &camcc_ipe_0_aweg_cwk.cwkw,
	[CAMCC_IPE_0_AXI_CWK] = &camcc_ipe_0_axi_cwk.cwkw,
	[CAMCC_IPE_0_CWK] = &camcc_ipe_0_cwk.cwkw,
	[CAMCC_IPE_0_CWK_SWC] = &camcc_ipe_0_cwk_swc.cwkw,
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
	[CAMCC_PWW0] = &camcc_pww0.cwkw,
	[CAMCC_PWW0_OUT_EVEN] = &camcc_pww0_out_even.cwkw,
	[CAMCC_PWW1] = &camcc_pww1.cwkw,
	[CAMCC_PWW1_OUT_EVEN] = &camcc_pww1_out_even.cwkw,
	[CAMCC_PWW2] = &camcc_pww2.cwkw,
	[CAMCC_PWW2_OUT_MAIN] = &camcc_pww2_out_main.cwkw,
	[CAMCC_PWW3] = &camcc_pww3.cwkw,
	[CAMCC_SWOW_AHB_CWK_SWC] = &camcc_swow_ahb_cwk_swc.cwkw,
	[CAMCC_SOC_AHB_CWK] = &camcc_soc_ahb_cwk.cwkw,
	[CAMCC_SYS_TMW_CWK] = &camcc_sys_tmw_cwk.cwkw,
};

static stwuct gdsc *camcc_sm6350_gdscs[] = {
	[BPS_GDSC] = &bps_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[IFE_0_GDSC] = &ife_0_gdsc,
	[IFE_1_GDSC] = &ife_1_gdsc,
	[IFE_2_GDSC] = &ife_2_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
};

static const stwuct wegmap_config camcc_sm6350_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x16000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc camcc_sm6350_desc = {
	.config = &camcc_sm6350_wegmap_config,
	.cwk_hws = camcc_sm6350_hws,
	.num_cwk_hws = AWWAY_SIZE(camcc_sm6350_hws),
	.cwks = camcc_sm6350_cwocks,
	.num_cwks = AWWAY_SIZE(camcc_sm6350_cwocks),
	.gdscs = camcc_sm6350_gdscs,
	.num_gdscs = AWWAY_SIZE(camcc_sm6350_gdscs),
};

static const stwuct of_device_id camcc_sm6350_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6350-camcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, camcc_sm6350_match_tabwe);

static int camcc_sm6350_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &camcc_sm6350_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_fabia_pww_configuwe(&camcc_pww0, wegmap, &camcc_pww0_config);
	cwk_fabia_pww_configuwe(&camcc_pww1, wegmap, &camcc_pww1_config);
	cwk_agewa_pww_configuwe(&camcc_pww2, wegmap, &camcc_pww2_config);
	cwk_fabia_pww_configuwe(&camcc_pww3, wegmap, &camcc_pww3_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &camcc_sm6350_desc, wegmap);
}

static stwuct pwatfowm_dwivew camcc_sm6350_dwivew = {
	.pwobe = camcc_sm6350_pwobe,
	.dwivew = {
		.name = "sm6350-camcc",
		.of_match_tabwe = camcc_sm6350_match_tabwe,
	},
};

static int __init camcc_sm6350_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&camcc_sm6350_dwivew);
}
subsys_initcaww(camcc_sm6350_init);

static void __exit camcc_sm6350_exit(void)
{
	pwatfowm_dwivew_unwegistew(&camcc_sm6350_dwivew);
}
moduwe_exit(camcc_sm6350_exit);

MODUWE_DESCWIPTION("QTI CAMCC SM6350 Dwivew");
MODUWE_WICENSE("GPW");
