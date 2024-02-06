// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Konwad Dybcio <konwad.dybcio@somainwine.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm6375-gcc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "cwk-wegmap-phy-mux.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	DT_BI_TCXO,
	DT_BI_TCXO_AO,
	DT_SWEEP_CWK
};

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_EVEN,
	P_GPWW0_OUT_MAIN,
	P_GPWW0_OUT_ODD,
	P_GPWW10_OUT_EVEN,
	P_GPWW11_OUT_EVEN,
	P_GPWW11_OUT_ODD,
	P_GPWW3_OUT_EVEN,
	P_GPWW3_OUT_MAIN,
	P_GPWW4_OUT_EVEN,
	P_GPWW5_OUT_EVEN,
	P_GPWW6_OUT_EVEN,
	P_GPWW6_OUT_MAIN,
	P_GPWW7_OUT_EVEN,
	P_GPWW8_OUT_EVEN,
	P_GPWW8_OUT_MAIN,
	P_GPWW9_OUT_EAWWY,
	P_GPWW9_OUT_MAIN,
	P_SWEEP_CWK,
};

static stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct pww_vco zonda_vco[] = {
	{ 595200000, 3600000000UW, 0 },
};

static stwuct cwk_awpha_pww gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww0_out_odd[] = {
	{ 0x3, 3 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww0_out_odd = {
	.offset = 0x0,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_gpww0_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww0_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct cwk_awpha_pww gpww1 = {
	.offset = 0x1000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

/* 1152MHz Configuwation */
static const stwuct awpha_pww_config gpww10_config = {
	.w = 0x3c,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329a299c,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww gpww10 = {
	.offset = 0xa000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.fwags = SUPPOWTS_FSM_WEGACY_MODE,
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww10",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

/* 532MHz Configuwation */
static const stwuct awpha_pww_config gpww11_config = {
	.w = 0x1b,
	.awpha = 0xb555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329a299c,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww gpww11 = {
	.offset = 0xb000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.fwags = SUPPOWTS_FSM_WEGACY_MODE,
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww11",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww3 = {
	.offset = 0x3000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww3_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww3_out_even = {
	.offset = 0x3000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_gpww3_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww3_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww3_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww3.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct cwk_awpha_pww gpww4 = {
	.offset = 0x4000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww5 = {
	.offset = 0x5000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww5",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww6 = {
	.offset = 0x6000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww6",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww6_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww6_out_even = {
	.offset = 0x6000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_gpww6_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww6_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww6_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww6.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct cwk_awpha_pww gpww7 = {
	.offset = 0x7000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww7",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

/* 400MHz Configuwation */
static const stwuct awpha_pww_config gpww8_config = {
	.w = 0x14,
	.awpha = 0xd555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329a299c,
	.usew_ctw_vaw = 0x00000101,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww gpww8 = {
	.offset = 0x8000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.fwags = SUPPOWTS_FSM_WEGACY_MODE,
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww8",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww8_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww8_out_even = {
	.offset = 0x8000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_gpww8_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww8_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww8_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww8.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

/* 1440MHz Configuwation */
static const stwuct awpha_pww_config gpww9_config = {
	.w = 0x4b,
	.awpha = 0x0,
	.config_ctw_vaw = 0x08200800,
	.config_ctw_hi_vaw = 0x05022011,
	.config_ctw_hi1_vaw = 0x08000000,
	.usew_ctw_vaw = 0x00000301,
};

static stwuct cwk_awpha_pww gpww9 = {
	.offset = 0x9000,
	.vco_tabwe = zonda_vco,
	.num_vco = AWWAY_SIZE(zonda_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww9",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_zonda_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww9_out_main[] = {
	{ 0x3, 4 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww9_out_main = {
	.offset = 0x9000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_gpww9_out_main,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww9_out_main),
	.width = 2,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww9_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww9.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_zonda_ops,
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW6_OUT_EVEN, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww6_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW0_OUT_ODD, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww0_out_odd.cwkw.hw },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2_ao[] = {
	{ .index = DT_BI_TCXO_AO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww0_out_odd.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW9_OUT_EAWWY, 2 },
	{ P_GPWW10_OUT_EVEN, 3 },
	{ P_GPWW9_OUT_MAIN, 4 },
	{ P_GPWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww9.cwkw.hw },
	{ .hw = &gpww10.cwkw.hw },
	{ .hw = &gpww9_out_main.cwkw.hw },
	{ .hw = &gpww3_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW0_OUT_ODD, 4 },
	{ P_GPWW4_OUT_EVEN, 5 },
	{ P_GPWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww0_out_odd.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww3_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW8_OUT_MAIN, 2 },
	{ P_GPWW10_OUT_EVEN, 3 },
	{ P_GPWW9_OUT_MAIN, 4 },
	{ P_GPWW8_OUT_EVEN, 5 },
	{ P_GPWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww8.cwkw.hw },
	{ .hw = &gpww10.cwkw.hw },
	{ .hw = &gpww9_out_main.cwkw.hw },
	{ .hw = &gpww8_out_even.cwkw.hw },
	{ .hw = &gpww3_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW8_OUT_MAIN, 2 },
	{ P_GPWW5_OUT_EVEN, 3 },
	{ P_GPWW9_OUT_MAIN, 4 },
	{ P_GPWW8_OUT_EVEN, 5 },
	{ P_GPWW3_OUT_MAIN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww8.cwkw.hw },
	{ .hw = &gpww5.cwkw.hw },
	{ .hw = &gpww9_out_main.cwkw.hw },
	{ .hw = &gpww8_out_even.cwkw.hw },
	{ .hw = &gpww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW0_OUT_ODD, 4 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_7[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww0_out_odd.cwkw.hw },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW10_OUT_EVEN, 3 },
	{ P_GPWW4_OUT_EVEN, 5 },
	{ P_GPWW3_OUT_MAIN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww10.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW10_OUT_EVEN, 3 },
	{ P_GPWW9_OUT_MAIN, 4 },
	{ P_GPWW8_OUT_EVEN, 5 },
	{ P_GPWW3_OUT_MAIN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww10.cwkw.hw },
	{ .hw = &gpww9_out_main.cwkw.hw },
	{ .hw = &gpww8_out_even.cwkw.hw },
	{ .hw = &gpww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW8_OUT_MAIN, 2 },
	{ P_GPWW10_OUT_EVEN, 3 },
	{ P_GPWW9_OUT_MAIN, 4 },
	{ P_GPWW8_OUT_EVEN, 5 },
	{ P_GPWW3_OUT_MAIN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww8.cwkw.hw },
	{ .hw = &gpww10.cwkw.hw },
	{ .hw = &gpww9_out_main.cwkw.hw },
	{ .hw = &gpww8_out_even.cwkw.hw },
	{ .hw = &gpww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW8_OUT_MAIN, 2 },
	{ P_GPWW10_OUT_EVEN, 3 },
	{ P_GPWW6_OUT_MAIN, 4 },
	{ P_GPWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww8.cwkw.hw },
	{ .hw = &gpww10.cwkw.hw },
	{ .hw = &gpww6.cwkw.hw },
	{ .hw = &gpww3_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_12[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 2 },
	{ P_GPWW7_OUT_EVEN, 3 },
	{ P_GPWW4_OUT_EVEN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_12[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .hw = &gpww7.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_13[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_13[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_14[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW11_OUT_ODD, 2 },
	{ P_GPWW11_OUT_EVEN, 3 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_14[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpww11.cwkw.hw },
	{ .hw = &gpww11.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_camss_axi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	F(300000000, P_GPWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_axi_cwk_swc = {
	.cmd_wcgw = 0x5802c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_camss_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_cci_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_GPWW0_OUT_EVEN, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_cci_0_cwk_swc = {
	.cmd_wcgw = 0x56000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_gcc_camss_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_cci_0_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_cci_1_cwk_swc = {
	.cmd_wcgw = 0x5c000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_gcc_camss_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_cci_1_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_csi0phytimew_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_ODD, 2, 0, 0),
	F(300000000, P_GPWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x59000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi0phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0x5901c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi1phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0x59038,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi2phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi3phytimew_cwk_swc = {
	.cmd_wcgw = 0x59054,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi3phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_mcwk0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_GPWW9_OUT_MAIN, 1, 1, 15),
	F(65454545, P_GPWW9_OUT_EAWWY, 11, 1, 2),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x51000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk0_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x5101c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk1_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x51038,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk2_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x51054,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk3_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk4_cwk_swc = {
	.cmd_wcgw = 0x51070,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk4_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_ope_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(171428571, P_GPWW0_OUT_MAIN, 3.5, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_ope_ahb_cwk_swc = {
	.cmd_wcgw = 0x55024,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_10,
	.fweq_tbw = ftbw_gcc_camss_ope_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_ope_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_10,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_ope_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPWW8_OUT_EVEN, 1, 0, 0),
	F(266600000, P_GPWW8_OUT_EVEN, 1, 0, 0),
	F(480000000, P_GPWW8_OUT_EVEN, 1, 0, 0),
	F(580000000, P_GPWW8_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_ope_cwk_swc = {
	.cmd_wcgw = 0x55004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_10,
	.fweq_tbw = ftbw_gcc_camss_ope_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_ope_cwk_swc",
		.pawent_data = gcc_pawent_data_10,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_tfe_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(120000000, P_GPWW0_OUT_MAIN, 5, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(144000000, P_GPWW9_OUT_MAIN, 2.5, 0, 0),
	F(150000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(171428571, P_GPWW0_OUT_MAIN, 3.5, 0, 0),
	F(180000000, P_GPWW9_OUT_MAIN, 2, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	F(329142857, P_GPWW10_OUT_EVEN, 3.5, 0, 0),
	F(384000000, P_GPWW10_OUT_EVEN, 3, 0, 0),
	F(460800000, P_GPWW10_OUT_EVEN, 2.5, 0, 0),
	F(576000000, P_GPWW10_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_tfe_0_cwk_swc = {
	.cmd_wcgw = 0x52004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_camss_tfe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_0_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_tfe_0_csid_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(120000000, P_GPWW0_OUT_MAIN, 5, 0, 0),
	F(266571429, P_GPWW5_OUT_EVEN, 3.5, 0, 0),
	F(426400000, P_GPWW3_OUT_MAIN, 2.5, 0, 0),
	F(466500000, P_GPWW5_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_tfe_0_csid_cwk_swc = {
	.cmd_wcgw = 0x52094,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_camss_tfe_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_0_csid_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_tfe_1_cwk_swc = {
	.cmd_wcgw = 0x52024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_camss_tfe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_1_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_tfe_1_csid_cwk_swc = {
	.cmd_wcgw = 0x520b4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_camss_tfe_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_1_csid_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_tfe_2_cwk_swc = {
	.cmd_wcgw = 0x52044,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_camss_tfe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_2_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_tfe_2_csid_cwk_swc = {
	.cmd_wcgw = 0x520d4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_camss_tfe_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_2_csid_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_tfe_cphy_wx_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(256000000, P_GPWW6_OUT_MAIN, 3, 0, 0),
	F(384000000, P_GPWW6_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_tfe_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0x52064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_11,
	.fweq_tbw = ftbw_gcc_camss_tfe_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_tfe_cphy_wx_cwk_swc",
		.pawent_data = gcc_pawent_data_11,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_top_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(40000000, P_GPWW0_OUT_EVEN, 7.5, 0, 0),
	F(80000000, P_GPWW0_OUT_MAIN, 7.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_top_ahb_cwk_swc = {
	.cmd_wcgw = 0x58010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_camss_top_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_top_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_cpuss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_ODD, 4, 0, 0),
	F(100000000, P_GPWW0_OUT_ODD, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_cpuss_ahb_cwk_swc = {
	.cmd_wcgw = 0x2b13c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_cpuss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_2_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2_ao),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_ODD, 4, 0, 0),
	F(100000000, P_GPWW0_OUT_ODD, 2, 0, 0),
	F(200000000, P_GPWW0_OUT_ODD, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x4d004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x4e004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x4f004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPWW0_OUT_EVEN, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pdm2_cwk_swc = {
	.cmd_wcgw = 0x20010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pdm2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pdm2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s0_cwk_swc[] = {
	F(7372800, P_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GPWW0_OUT_EVEN, 1, 4, 25),
	F(64000000, P_GPWW0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(102400000, P_GPWW0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GPWW0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GPWW0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GPWW0_OUT_EVEN, 2.5, 0, 0),
	F(128000000, P_GPWW6_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s0_cwk_swc = {
	.cmd_wcgw = 0x1f148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s1_cwk_swc = {
	.cmd_wcgw = 0x1f278,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s2_cwk_swc = {
	.cmd_wcgw = 0x1f3a8,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s3_cwk_swc = {
	.cmd_wcgw = 0x1f4d8,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s4_cwk_swc = {
	.cmd_wcgw = 0x1f608,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s5_cwk_swc = {
	.cmd_wcgw = 0x1f738,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s0_cwk_swc = {
	.cmd_wcgw = 0x5301c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s1_cwk_swc = {
	.cmd_wcgw = 0x5314c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s2_cwk_swc = {
	.cmd_wcgw = 0x5327c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s3_cwk_swc = {
	.cmd_wcgw = 0x533ac,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s4_cwk_swc = {
	.cmd_wcgw = 0x534dc,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s5_cwk_swc = {
	.cmd_wcgw = 0x5360c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s5_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk_swc[] = {
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(20000000, P_GPWW0_OUT_EVEN, 5, 1, 3),
	F(25000000, P_GPWW0_OUT_EVEN, 6, 1, 2),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(192000000, P_GPWW6_OUT_EVEN, 2, 0, 0),
	F(384000000, P_GPWW6_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x38028,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_ice_cowe_cwk_swc[] = {
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x38010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdcc1_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc2_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(202000000, P_GPWW7_OUT_EVEN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x1e00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_12,
	.fweq_tbw = ftbw_gcc_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_12,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_12),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_axi_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_ODD, 4, 0, 0),
	F(100000000, P_GPWW0_OUT_ODD, 2, 0, 0),
	F(200000000, P_GPWW0_OUT_ODD, 1, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_axi_cwk_swc = {
	.cmd_wcgw = 0x45020,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_ufs_phy_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_ice_cowe_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GPWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x45048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_phy_aux_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x4507c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_unipwo_cowe_cwk_swc = {
	.cmd_wcgw = 0x45060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_unipwo_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mastew_cwk_swc[] = {
	F(66666667, P_GPWW0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPWW0_OUT_ODD, 1, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mastew_cwk_swc = {
	.cmd_wcgw = 0x1a01c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x1a034,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x1a060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_13,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_13,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_13),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_video_venus_cwk_swc[] = {
	F(133000000, P_GPWW11_OUT_EVEN, 4, 0, 0),
	F(240000000, P_GPWW11_OUT_EVEN, 2.5, 0, 0),
	F(300000000, P_GPWW11_OUT_EVEN, 2, 0, 0),
	F(384000000, P_GPWW11_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_video_venus_cwk_swc = {
	.cmd_wcgw = 0x58060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_14,
	.fweq_tbw = ftbw_gcc_video_venus_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_video_venus_cwk_swc",
		.pawent_data = gcc_pawent_data_14,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_14),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wegmap_div gcc_cpuss_ahb_postdiv_cwk_swc = {
	.weg = 0x2b154,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_cpuss_ahb_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gcc_cpuss_ahb_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc = {
	.weg = 0x1a04c,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch gcc_ahb2phy_csi_cwk = {
	.hawt_weg = 0x1d004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1d004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1d004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ahb2phy_csi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ahb2phy_usb_cwk = {
	.hawt_weg = 0x1d008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1d008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1d008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ahb2phy_usb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bimc_gpu_axi_cwk = {
	.hawt_weg = 0x71154,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x71154,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x71154,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bimc_gpu_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x23004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x23004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cam_thwottwe_nwt_cwk = {
	.hawt_weg = 0x17070,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17070,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cam_thwottwe_nwt_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cam_thwottwe_wt_cwk = {
	.hawt_weg = 0x1706c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1706c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cam_thwottwe_wt_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_ahb_cwk = {
	.hawt_weg = 0x17008,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x17008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x17008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_axi_cwk = {
	.hawt_weg = 0x58044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cci_0_cwk = {
	.hawt_weg = 0x56018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x56018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cci_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_cci_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cci_1_cwk = {
	.hawt_weg = 0x5c018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5c018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cci_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_cci_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_0_cwk = {
	.hawt_weg = 0x52088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_1_cwk = {
	.hawt_weg = 0x5208c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5208c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_2_cwk = {
	.hawt_weg = 0x52090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_3_cwk = {
	.hawt_weg = 0x520f8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x520f8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi0phytimew_cwk = {
	.hawt_weg = 0x59018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_csi0phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi1phytimew_cwk = {
	.hawt_weg = 0x59034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_csi1phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi2phytimew_cwk = {
	.hawt_weg = 0x59050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_csi2phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi3phytimew_cwk = {
	.hawt_weg = 0x5906c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5906c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi3phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_csi3phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_mcwk0_cwk = {
	.hawt_weg = 0x51018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x51018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_mcwk1_cwk = {
	.hawt_weg = 0x51034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x51034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_mcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_mcwk2_cwk = {
	.hawt_weg = 0x51050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x51050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_mcwk2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_mcwk3_cwk = {
	.hawt_weg = 0x5106c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5106c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_mcwk3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_mcwk4_cwk = {
	.hawt_weg = 0x51088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x51088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_mcwk4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_mcwk4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_nwt_axi_cwk = {
	.hawt_weg = 0x58054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_nwt_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_ope_ahb_cwk = {
	.hawt_weg = 0x5503c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5503c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_ope_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_ope_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_ope_cwk = {
	.hawt_weg = 0x5501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_ope_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_ope_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_wt_axi_cwk = {
	.hawt_weg = 0x5805c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5805c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_wt_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_0_cwk = {
	.hawt_weg = 0x5201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_0_cphy_wx_cwk = {
	.hawt_weg = 0x5207c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5207c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_0_csid_cwk = {
	.hawt_weg = 0x520ac,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x520ac,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_0_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_1_cwk = {
	.hawt_weg = 0x5203c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_1_cphy_wx_cwk = {
	.hawt_weg = 0x52080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_1_csid_cwk = {
	.hawt_weg = 0x520cc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x520cc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_1_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_2_cwk = {
	.hawt_weg = 0x5205c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5205c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_2_cphy_wx_cwk = {
	.hawt_weg = 0x52084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_2_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_tfe_2_csid_cwk = {
	.hawt_weg = 0x520ec,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x520ec,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_tfe_2_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_tfe_2_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_top_ahb_cwk = {
	.hawt_weg = 0x58028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_top_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_camss_top_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x1a084,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1a084,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1a084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cfg_noc_usb3_pwim_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_ahb_cwk = {
	.hawt_weg = 0x1700c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1700c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1700c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap_div gcc_disp_gpww0_cwk_swc = {
	.weg = 0x17058,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_disp_gpww0_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_ops,
	},
};

static stwuct cwk_bwanch gcc_disp_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_disp_gpww0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_hf_axi_cwk = {
	.hawt_weg = 0x17020,
	.hawt_check = BWANCH_VOTED,
	.hwcg_weg = 0x17020,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x17020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_sweep_cwk = {
	.hawt_weg = 0x17074,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17074,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x17074,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_thwottwe_cowe_cwk = {
	.hawt_weg = 0x17064,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17064,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_thwottwe_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x4d000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x4e000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gp2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0x4f000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gp3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_cfg_ahb_cwk = {
	.hawt_weg = 0x36004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x36004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x36004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_cfg_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpww0_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_memnoc_gfx_cwk = {
	.hawt_weg = 0x3600c,
	.hawt_check = BWANCH_VOTED,
	.hwcg_weg = 0x3600c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_memnoc_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_snoc_dvm_gfx_cwk = {
	.hawt_weg = 0x36018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_snoc_dvm_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_thwottwe_cowe_cwk = {
	.hawt_weg = 0x36048,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x36048,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(31),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_thwottwe_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x2000c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2000c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pdm2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_ahb_cwk = {
	.hawt_weg = 0x20004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x20004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x20004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_xo4_cwk = {
	.hawt_weg = 0x20008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x20008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_xo4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x21004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x21004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwng_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_camewa_nwt_ahb_cwk = {
	.hawt_weg = 0x17014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_nwt_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_camewa_wt_ahb_cwk = {
	.hawt_weg = 0x17060,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17060,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_wt_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_disp_ahb_cwk = {
	.hawt_weg = 0x17018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_disp_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_gpu_cfg_ahb_cwk = {
	.hawt_weg = 0x36040,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x36040,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_gpu_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_vcodec_ahb_cwk = {
	.hawt_weg = 0x17010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_vcodec_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_2x_cwk = {
	.hawt_weg = 0x1f014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_cwk = {
	.hawt_weg = 0x1f00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s0_cwk = {
	.hawt_weg = 0x1f144,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s1_cwk = {
	.hawt_weg = 0x1f274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s2_cwk = {
	.hawt_weg = 0x1f3a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s3_cwk = {
	.hawt_weg = 0x1f4d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s4_cwk = {
	.hawt_weg = 0x1f604,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s5_cwk = {
	.hawt_weg = 0x1f734,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_2x_cwk = {
	.hawt_weg = 0x53014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_cwk = {
	.hawt_weg = 0x5300c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s0_cwk = {
	.hawt_weg = 0x53018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s1_cwk = {
	.hawt_weg = 0x53148,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(22),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s2_cwk = {
	.hawt_weg = 0x53278,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(23),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s3_cwk = {
	.hawt_weg = 0x533a8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(24),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s4_cwk = {
	.hawt_weg = 0x534d8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s5_cwk = {
	.hawt_weg = 0x53608,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_0_m_ahb_cwk = {
	.hawt_weg = 0x1f004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1f004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_0_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_0_s_ahb_cwk = {
	.hawt_weg = 0x1f008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1f008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_0_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_m_ahb_cwk = {
	.hawt_weg = 0x53004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x53004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_s_ahb_cwk = {
	.hawt_weg = 0x53008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x53008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(18),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x38008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x38008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x38004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x38004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ice_cowe_cwk = {
	.hawt_weg = 0x3800c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3800c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3800c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc1_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x1e008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_apps_cwk = {
	.hawt_weg = 0x1e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_cpuss_ahb_cwk = {
	.hawt_weg = 0x2b06c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2b06c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_cpuss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_cpuss_ahb_postdiv_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_ufs_phy_axi_cwk = {
	.hawt_weg = 0x45098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x45098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_ufs_phy_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x1a080,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1a080,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1a080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_usb3_pwim_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_ahb_cwk = {
	.hawt_weg = 0x45014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x45014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_axi_cwk = {
	.hawt_weg = 0x45010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x45010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_ice_cowe_cwk = {
	.hawt_weg = 0x45044,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x45044,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_phy_aux_cwk = {
	.hawt_weg = 0x45078,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x45078,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_wx_symbow_0_cwk = {
	.hawt_weg = 0x4501c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x4501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_tx_symbow_0_cwk = {
	.hawt_weg = 0x45018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x45018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_tx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_unipwo_cowe_cwk = {
	.hawt_weg = 0x45040,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x45040,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_unipwo_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_unipwo_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_mastew_cwk = {
	.hawt_weg = 0x1a010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_mock_utmi_cwk = {
	.hawt_weg = 0x1a018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_sweep_cwk = {
	.hawt_weg = 0x1a014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_mem_cwkwef_cwk = {
	.hawt_weg = 0x8c000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_mem_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wx5_pcie_cwkwef_en_cwk = {
	.hawt_weg = 0x8c00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wx5_pcie_cwkwef_en_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_cwkwef_cwk = {
	.hawt_weg = 0x8c010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_com_aux_cwk = {
	.hawt_weg = 0x1a054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_com_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb3_pwim_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_pipe_cwk = {
	.hawt_weg = 0x1a058,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x1a058,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1a058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vcodec0_axi_cwk = {
	.hawt_weg = 0x6e008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vcodec0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_venus_ahb_cwk = {
	.hawt_weg = 0x6e010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6e010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_venus_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_venus_ctw_axi_cwk = {
	.hawt_weg = 0x6e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_venus_ctw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_ahb_cwk = {
	.hawt_weg = 0x17004,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x17004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x17004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_axi0_cwk = {
	.hawt_weg = 0x1701c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1701c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1701c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_thwottwe_cowe_cwk = {
	.hawt_weg = 0x17068,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17068,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_thwottwe_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_vcodec0_sys_cwk = {
	.hawt_weg = 0x580a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x580a4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x580a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_vcodec0_sys_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_video_venus_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_venus_ctw_cwk = {
	.hawt_weg = 0x5808c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5808c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_venus_ctw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_video_venus_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_xo_cwk = {
	.hawt_weg = 0x17024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_xo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0x1a004,
	.pd = {
		.name = "usb30_pwim_gdsc",
	},
	/* TODO: Change to OFF_ON when USB dwivews get pwopew suspend suppowt */
	.pwwsts = PWWSTS_WET_ON,
};

static stwuct gdsc ufs_phy_gdsc = {
	.gdscw = 0x45004,
	.pd = {
		.name = "ufs_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_top_gdsc = {
	.gdscw = 0x58004,
	.pd = {
		.name = "camss_top_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc venus_gdsc = {
	.gdscw = 0x5807c,
	.pd = {
		.name = "venus_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc vcodec0_gdsc = {
	.gdscw = 0x58098,
	.pd = {
		.name = "vcodec0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW,
};

static stwuct gdsc hwos1_vote_mm_snoc_mmu_tbu_wt_gdsc = {
	.gdscw = 0x7d074,
	.pd = {
		.name = "hwos1_vote_mm_snoc_mmu_tbu_wt_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_mm_snoc_mmu_tbu_nwt_gdsc = {
	.gdscw = 0x7d078,
	.pd = {
		.name = "hwos1_vote_mm_snoc_mmu_tbu_nwt_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_tuwing_mmu_tbu1_gdsc = {
	.gdscw = 0x7d060,
	.pd = {
		.name = "hwos1_vote_tuwing_mmu_tbu1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_tuwing_mmu_tbu0_gdsc = {
	.gdscw = 0x7d07c,
	.pd = {
		.name = "hwos1_vote_tuwing_mmu_tbu0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct cwk_wegmap *gcc_sm6375_cwocks[] = {
	[GCC_AHB2PHY_CSI_CWK] = &gcc_ahb2phy_csi_cwk.cwkw,
	[GCC_AHB2PHY_USB_CWK] = &gcc_ahb2phy_usb_cwk.cwkw,
	[GCC_BIMC_GPU_AXI_CWK] = &gcc_bimc_gpu_axi_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAM_THWOTTWE_NWT_CWK] = &gcc_cam_thwottwe_nwt_cwk.cwkw,
	[GCC_CAM_THWOTTWE_WT_CWK] = &gcc_cam_thwottwe_wt_cwk.cwkw,
	[GCC_CAMEWA_AHB_CWK] = &gcc_camewa_ahb_cwk.cwkw,
	[GCC_CAMSS_AXI_CWK] = &gcc_camss_axi_cwk.cwkw,
	[GCC_CAMSS_AXI_CWK_SWC] = &gcc_camss_axi_cwk_swc.cwkw,
	[GCC_CAMSS_CCI_0_CWK] = &gcc_camss_cci_0_cwk.cwkw,
	[GCC_CAMSS_CCI_0_CWK_SWC] = &gcc_camss_cci_0_cwk_swc.cwkw,
	[GCC_CAMSS_CCI_1_CWK] = &gcc_camss_cci_1_cwk.cwkw,
	[GCC_CAMSS_CCI_1_CWK_SWC] = &gcc_camss_cci_1_cwk_swc.cwkw,
	[GCC_CAMSS_CPHY_0_CWK] = &gcc_camss_cphy_0_cwk.cwkw,
	[GCC_CAMSS_CPHY_1_CWK] = &gcc_camss_cphy_1_cwk.cwkw,
	[GCC_CAMSS_CPHY_2_CWK] = &gcc_camss_cphy_2_cwk.cwkw,
	[GCC_CAMSS_CPHY_3_CWK] = &gcc_camss_cphy_3_cwk.cwkw,
	[GCC_CAMSS_CSI0PHYTIMEW_CWK] = &gcc_camss_csi0phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI0PHYTIMEW_CWK_SWC] = &gcc_camss_csi0phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_CSI1PHYTIMEW_CWK] = &gcc_camss_csi1phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI1PHYTIMEW_CWK_SWC] = &gcc_camss_csi1phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_CSI2PHYTIMEW_CWK] = &gcc_camss_csi2phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI2PHYTIMEW_CWK_SWC] = &gcc_camss_csi2phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_CSI3PHYTIMEW_CWK] = &gcc_camss_csi3phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI3PHYTIMEW_CWK_SWC] = &gcc_camss_csi3phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK0_CWK] = &gcc_camss_mcwk0_cwk.cwkw,
	[GCC_CAMSS_MCWK0_CWK_SWC] = &gcc_camss_mcwk0_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK1_CWK] = &gcc_camss_mcwk1_cwk.cwkw,
	[GCC_CAMSS_MCWK1_CWK_SWC] = &gcc_camss_mcwk1_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK2_CWK] = &gcc_camss_mcwk2_cwk.cwkw,
	[GCC_CAMSS_MCWK2_CWK_SWC] = &gcc_camss_mcwk2_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK3_CWK] = &gcc_camss_mcwk3_cwk.cwkw,
	[GCC_CAMSS_MCWK3_CWK_SWC] = &gcc_camss_mcwk3_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK4_CWK] = &gcc_camss_mcwk4_cwk.cwkw,
	[GCC_CAMSS_MCWK4_CWK_SWC] = &gcc_camss_mcwk4_cwk_swc.cwkw,
	[GCC_CAMSS_NWT_AXI_CWK] = &gcc_camss_nwt_axi_cwk.cwkw,
	[GCC_CAMSS_OPE_AHB_CWK] = &gcc_camss_ope_ahb_cwk.cwkw,
	[GCC_CAMSS_OPE_AHB_CWK_SWC] = &gcc_camss_ope_ahb_cwk_swc.cwkw,
	[GCC_CAMSS_OPE_CWK] = &gcc_camss_ope_cwk.cwkw,
	[GCC_CAMSS_OPE_CWK_SWC] = &gcc_camss_ope_cwk_swc.cwkw,
	[GCC_CAMSS_WT_AXI_CWK] = &gcc_camss_wt_axi_cwk.cwkw,
	[GCC_CAMSS_TFE_0_CWK] = &gcc_camss_tfe_0_cwk.cwkw,
	[GCC_CAMSS_TFE_0_CWK_SWC] = &gcc_camss_tfe_0_cwk_swc.cwkw,
	[GCC_CAMSS_TFE_0_CPHY_WX_CWK] = &gcc_camss_tfe_0_cphy_wx_cwk.cwkw,
	[GCC_CAMSS_TFE_0_CSID_CWK] = &gcc_camss_tfe_0_csid_cwk.cwkw,
	[GCC_CAMSS_TFE_0_CSID_CWK_SWC] = &gcc_camss_tfe_0_csid_cwk_swc.cwkw,
	[GCC_CAMSS_TFE_1_CWK] = &gcc_camss_tfe_1_cwk.cwkw,
	[GCC_CAMSS_TFE_1_CWK_SWC] = &gcc_camss_tfe_1_cwk_swc.cwkw,
	[GCC_CAMSS_TFE_1_CPHY_WX_CWK] = &gcc_camss_tfe_1_cphy_wx_cwk.cwkw,
	[GCC_CAMSS_TFE_1_CSID_CWK] = &gcc_camss_tfe_1_csid_cwk.cwkw,
	[GCC_CAMSS_TFE_1_CSID_CWK_SWC] = &gcc_camss_tfe_1_csid_cwk_swc.cwkw,
	[GCC_CAMSS_TFE_2_CWK] = &gcc_camss_tfe_2_cwk.cwkw,
	[GCC_CAMSS_TFE_2_CWK_SWC] = &gcc_camss_tfe_2_cwk_swc.cwkw,
	[GCC_CAMSS_TFE_2_CPHY_WX_CWK] = &gcc_camss_tfe_2_cphy_wx_cwk.cwkw,
	[GCC_CAMSS_TFE_2_CSID_CWK] = &gcc_camss_tfe_2_csid_cwk.cwkw,
	[GCC_CAMSS_TFE_2_CSID_CWK_SWC] = &gcc_camss_tfe_2_csid_cwk_swc.cwkw,
	[GCC_CAMSS_TFE_CPHY_WX_CWK_SWC] = &gcc_camss_tfe_cphy_wx_cwk_swc.cwkw,
	[GCC_CAMSS_TOP_AHB_CWK] = &gcc_camss_top_ahb_cwk.cwkw,
	[GCC_CAMSS_TOP_AHB_CWK_SWC] = &gcc_camss_top_ahb_cwk_swc.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK_SWC] = &gcc_cpuss_ahb_cwk_swc.cwkw,
	[GCC_CPUSS_AHB_POSTDIV_CWK_SWC] = &gcc_cpuss_ahb_postdiv_cwk_swc.cwkw,
	[GCC_DISP_AHB_CWK] = &gcc_disp_ahb_cwk.cwkw,
	[GCC_DISP_GPWW0_CWK_SWC] = &gcc_disp_gpww0_cwk_swc.cwkw,
	[GCC_DISP_GPWW0_DIV_CWK_SWC] = &gcc_disp_gpww0_div_cwk_swc.cwkw,
	[GCC_DISP_HF_AXI_CWK] = &gcc_disp_hf_axi_cwk.cwkw,
	[GCC_DISP_SWEEP_CWK] = &gcc_disp_sweep_cwk.cwkw,
	[GCC_DISP_THWOTTWE_COWE_CWK] = &gcc_disp_thwottwe_cowe_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPU_CFG_AHB_CWK] = &gcc_gpu_cfg_ahb_cwk.cwkw,
	[GCC_GPU_GPWW0_CWK_SWC] = &gcc_gpu_gpww0_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_DIV_CWK_SWC] = &gcc_gpu_gpww0_div_cwk_swc.cwkw,
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_GPU_THWOTTWE_COWE_CWK] = &gcc_gpu_thwottwe_cowe_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_QMIP_CAMEWA_NWT_AHB_CWK] = &gcc_qmip_camewa_nwt_ahb_cwk.cwkw,
	[GCC_QMIP_CAMEWA_WT_AHB_CWK] = &gcc_qmip_camewa_wt_ahb_cwk.cwkw,
	[GCC_QMIP_DISP_AHB_CWK] = &gcc_qmip_disp_ahb_cwk.cwkw,
	[GCC_QMIP_GPU_CFG_AHB_CWK] = &gcc_qmip_gpu_cfg_ahb_cwk.cwkw,
	[GCC_QMIP_VIDEO_VCODEC_AHB_CWK] = &gcc_qmip_video_vcodec_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP0_COWE_2X_CWK] = &gcc_qupv3_wwap0_cowe_2x_cwk.cwkw,
	[GCC_QUPV3_WWAP0_COWE_CWK] = &gcc_qupv3_wwap0_cowe_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S0_CWK] = &gcc_qupv3_wwap0_s0_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S0_CWK_SWC] = &gcc_qupv3_wwap0_s0_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S1_CWK] = &gcc_qupv3_wwap0_s1_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S1_CWK_SWC] = &gcc_qupv3_wwap0_s1_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S2_CWK] = &gcc_qupv3_wwap0_s2_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S2_CWK_SWC] = &gcc_qupv3_wwap0_s2_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S3_CWK] = &gcc_qupv3_wwap0_s3_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S3_CWK_SWC] = &gcc_qupv3_wwap0_s3_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S4_CWK] = &gcc_qupv3_wwap0_s4_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S4_CWK_SWC] = &gcc_qupv3_wwap0_s4_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S5_CWK] = &gcc_qupv3_wwap0_s5_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S5_CWK_SWC] = &gcc_qupv3_wwap0_s5_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_COWE_2X_CWK] = &gcc_qupv3_wwap1_cowe_2x_cwk.cwkw,
	[GCC_QUPV3_WWAP1_COWE_CWK] = &gcc_qupv3_wwap1_cowe_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S0_CWK] = &gcc_qupv3_wwap1_s0_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S0_CWK_SWC] = &gcc_qupv3_wwap1_s0_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S1_CWK] = &gcc_qupv3_wwap1_s1_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S1_CWK_SWC] = &gcc_qupv3_wwap1_s1_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S2_CWK] = &gcc_qupv3_wwap1_s2_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S2_CWK_SWC] = &gcc_qupv3_wwap1_s2_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S3_CWK] = &gcc_qupv3_wwap1_s3_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S3_CWK_SWC] = &gcc_qupv3_wwap1_s3_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S4_CWK] = &gcc_qupv3_wwap1_s4_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S4_CWK_SWC] = &gcc_qupv3_wwap1_s4_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S5_CWK] = &gcc_qupv3_wwap1_s5_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S5_CWK_SWC] = &gcc_qupv3_wwap1_s5_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP_0_M_AHB_CWK] = &gcc_qupv3_wwap_0_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_0_S_AHB_CWK] = &gcc_qupv3_wwap_0_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_M_AHB_CWK] = &gcc_qupv3_wwap_1_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_S_AHB_CWK] = &gcc_qupv3_wwap_1_s_ahb_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK_SWC] = &gcc_sdcc1_apps_cwk_swc.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK] = &gcc_sdcc1_ice_cowe_cwk.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK_SWC] = &gcc_sdcc1_ice_cowe_cwk_swc.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK_SWC] = &gcc_sdcc2_apps_cwk_swc.cwkw,
	[GCC_SYS_NOC_CPUSS_AHB_CWK] = &gcc_sys_noc_cpuss_ahb_cwk.cwkw,
	[GCC_SYS_NOC_UFS_PHY_AXI_CWK] = &gcc_sys_noc_ufs_phy_axi_cwk.cwkw,
	[GCC_SYS_NOC_USB3_PWIM_AXI_CWK] = &gcc_sys_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_UFS_PHY_AHB_CWK] = &gcc_ufs_phy_ahb_cwk.cwkw,
	[GCC_UFS_PHY_AXI_CWK] = &gcc_ufs_phy_axi_cwk.cwkw,
	[GCC_UFS_PHY_AXI_CWK_SWC] = &gcc_ufs_phy_axi_cwk_swc.cwkw,
	[GCC_UFS_PHY_ICE_COWE_CWK] = &gcc_ufs_phy_ice_cowe_cwk.cwkw,
	[GCC_UFS_PHY_ICE_COWE_CWK_SWC] = &gcc_ufs_phy_ice_cowe_cwk_swc.cwkw,
	[GCC_UFS_PHY_PHY_AUX_CWK] = &gcc_ufs_phy_phy_aux_cwk.cwkw,
	[GCC_UFS_PHY_PHY_AUX_CWK_SWC] = &gcc_ufs_phy_phy_aux_cwk_swc.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_0_CWK] = &gcc_ufs_phy_wx_symbow_0_cwk.cwkw,
	[GCC_UFS_PHY_TX_SYMBOW_0_CWK] = &gcc_ufs_phy_tx_symbow_0_cwk.cwkw,
	[GCC_UFS_PHY_UNIPWO_COWE_CWK] = &gcc_ufs_phy_unipwo_cowe_cwk.cwkw,
	[GCC_UFS_PHY_UNIPWO_COWE_CWK_SWC] = &gcc_ufs_phy_unipwo_cowe_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MASTEW_CWK] = &gcc_usb30_pwim_mastew_cwk.cwkw,
	[GCC_USB30_PWIM_MASTEW_CWK_SWC] = &gcc_usb30_pwim_mastew_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_CWK] = &gcc_usb30_pwim_mock_utmi_cwk.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_CWK_SWC] = &gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_POSTDIV_CWK_SWC] = &gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc.cwkw,
	[GCC_USB30_PWIM_SWEEP_CWK] = &gcc_usb30_pwim_sweep_cwk.cwkw,
	[GCC_USB3_PWIM_CWKWEF_CWK] = &gcc_usb3_pwim_cwkwef_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK_SWC] = &gcc_usb3_pwim_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PWIM_PHY_COM_AUX_CWK] = &gcc_usb3_pwim_phy_com_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK] = &gcc_usb3_pwim_phy_pipe_cwk.cwkw,
	[GCC_VCODEC0_AXI_CWK] = &gcc_vcodec0_axi_cwk.cwkw,
	[GCC_VENUS_AHB_CWK] = &gcc_venus_ahb_cwk.cwkw,
	[GCC_VENUS_CTW_AXI_CWK] = &gcc_venus_ctw_axi_cwk.cwkw,
	[GCC_VIDEO_AHB_CWK] = &gcc_video_ahb_cwk.cwkw,
	[GCC_VIDEO_AXI0_CWK] = &gcc_video_axi0_cwk.cwkw,
	[GCC_VIDEO_THWOTTWE_COWE_CWK] = &gcc_video_thwottwe_cowe_cwk.cwkw,
	[GCC_VIDEO_VCODEC0_SYS_CWK] = &gcc_video_vcodec0_sys_cwk.cwkw,
	[GCC_VIDEO_VENUS_CWK_SWC] = &gcc_video_venus_cwk_swc.cwkw,
	[GCC_VIDEO_VENUS_CTW_CWK] = &gcc_video_venus_ctw_cwk.cwkw,
	[GCC_VIDEO_XO_CWK] = &gcc_video_xo_cwk.cwkw,
	[GCC_UFS_MEM_CWKWEF_CWK] = &gcc_ufs_mem_cwkwef_cwk.cwkw,
	[GCC_WX5_PCIE_CWKWEF_EN_CWK] = &gcc_wx5_pcie_cwkwef_en_cwk.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW0_OUT_EVEN] = &gpww0_out_even.cwkw,
	[GPWW0_OUT_ODD] = &gpww0_out_odd.cwkw,
	[GPWW1] = &gpww1.cwkw,
	[GPWW10] = &gpww10.cwkw,
	[GPWW11] = &gpww11.cwkw,
	[GPWW3] = &gpww3.cwkw,
	[GPWW3_OUT_EVEN] = &gpww3_out_even.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[GPWW5] = &gpww5.cwkw,
	[GPWW6] = &gpww6.cwkw,
	[GPWW6_OUT_EVEN] = &gpww6_out_even.cwkw,
	[GPWW7] = &gpww7.cwkw,
	[GPWW8] = &gpww8.cwkw,
	[GPWW8_OUT_EVEN] = &gpww8_out_even.cwkw,
	[GPWW9] = &gpww9.cwkw,
	[GPWW9_OUT_MAIN] = &gpww9_out_main.cwkw,
};

static const stwuct qcom_weset_map gcc_sm6375_wesets[] = {
	[GCC_MMSS_BCW] = { 0x17000 },
	[GCC_USB30_PWIM_BCW] = { 0x1a000 },
	[GCC_USB3_PHY_PWIM_SP0_BCW] = { 0x1b000 },
	[GCC_USB3_DP_PHY_PWIM_BCW] = { 0x1b020 },
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x1c000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x1c004 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x1d000 },
	[GCC_SDCC2_BCW] = { 0x1e000 },
	[GCC_QUPV3_WWAPPEW_0_BCW] = { 0x1f000 },
	[GCC_PDM_BCW] = { 0x20000 },
	[GCC_GPU_BCW] = { 0x36000 },
	[GCC_SDCC1_BCW] = { 0x38000 },
	[GCC_UFS_PHY_BCW] = { 0x45000 },
	[GCC_CAMSS_TFE_BCW] = { 0x52000 },
	[GCC_QUPV3_WWAPPEW_1_BCW] = { 0x53000 },
	[GCC_CAMSS_OPE_BCW] = { 0x55000 },
	[GCC_CAMSS_TOP_BCW] = { 0x58000 },
	[GCC_VENUS_BCW] = { 0x58078 },
	[GCC_VCODEC0_BCW] = { 0x58094 },
	[GCC_VIDEO_INTEWFACE_BCW] = { 0x6e000 },
};


static const stwuct cwk_wcg_dfs_data gcc_dfs_cwocks[] = {
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s5_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s5_cwk_swc),
};

static stwuct gdsc *gcc_sm6375_gdscs[] = {
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[CAMSS_TOP_GDSC] = &camss_top_gdsc,
	[VENUS_GDSC] = &venus_gdsc,
	[VCODEC0_GDSC] = &vcodec0_gdsc,
	[HWOS1_VOTE_MM_SNOC_MMU_TBU_NWT_GDSC] = &hwos1_vote_mm_snoc_mmu_tbu_nwt_gdsc,
	[HWOS1_VOTE_MM_SNOC_MMU_TBU_WT_GDSC] = &hwos1_vote_mm_snoc_mmu_tbu_wt_gdsc,
	[HWOS1_VOTE_TUWING_MMU_TBU0_GDSC] = &hwos1_vote_tuwing_mmu_tbu0_gdsc,
	[HWOS1_VOTE_TUWING_MMU_TBU1_GDSC] = &hwos1_vote_tuwing_mmu_tbu1_gdsc,
};

static const stwuct wegmap_config gcc_sm6375_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xc7000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_sm6375_desc = {
	.config = &gcc_sm6375_wegmap_config,
	.cwks = gcc_sm6375_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sm6375_cwocks),
	.wesets = gcc_sm6375_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sm6375_wesets),
	.gdscs = gcc_sm6375_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sm6375_gdscs),
};

static const stwuct of_device_id gcc_sm6375_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6375-gcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sm6375_match_tabwe);

static int gcc_sm6375_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_sm6375_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = qcom_cc_wegistew_wcg_dfs(wegmap, gcc_dfs_cwocks, AWWAY_SIZE(gcc_dfs_cwocks));
	if (wet)
		wetuwn wet;

	/*
	 * Keep the fowwowing cwocks awways on:
	 * GCC_CAMEWA_XO_CWK, GCC_CPUSS_GNOC_CWK, GCC_DISP_XO_CWK
	 */
	wegmap_update_bits(wegmap, 0x17028, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x2b004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x1702c, BIT(0), BIT(0));

	cwk_wucid_pww_configuwe(&gpww10, wegmap, &gpww10_config);
	cwk_wucid_pww_configuwe(&gpww11, wegmap, &gpww11_config);
	cwk_wucid_pww_configuwe(&gpww8, wegmap, &gpww8_config);
	cwk_zonda_pww_configuwe(&gpww9, wegmap, &gpww9_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sm6375_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sm6375_dwivew = {
	.pwobe = gcc_sm6375_pwobe,
	.dwivew = {
		.name = "gcc-sm6375",
		.of_match_tabwe = gcc_sm6375_match_tabwe,
	},
};

static int __init gcc_sm6375_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sm6375_dwivew);
}
subsys_initcaww(gcc_sm6375_init);

static void __exit gcc_sm6375_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sm6375_dwivew);
}
moduwe_exit(gcc_sm6375_exit);

MODUWE_DESCWIPTION("QTI GCC SM6375 Dwivew");
MODUWE_WICENSE("GPW");
