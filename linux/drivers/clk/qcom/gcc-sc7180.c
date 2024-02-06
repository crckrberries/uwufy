// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gcc-sc7180.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_EVEN,
	P_GPWW0_OUT_MAIN,
	P_GPWW1_OUT_MAIN,
	P_GPWW4_OUT_MAIN,
	P_GPWW6_OUT_MAIN,
	P_GPWW7_OUT_MAIN,
	P_SWEEP_CWK,
};

static stwuct cwk_awpha_pww gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_fabia_ops,
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
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static stwuct cwk_fixed_factow gcc_pww0_main_div_cdiv = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pww0_main_div_cdiv",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww1 = {
	.offset = 0x01000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_fabia_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww4 = {
	.offset = 0x76000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_fabia_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww6 = {
	.offset = 0x13000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww6",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_fabia_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww7 = {
	.offset = 0x27000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww7",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
				.name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_fabia_ops,
		},
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0_ao[] = {
	{ .fw_name = "bi_tcxo_ao", .name = "bi_tcxo_ao" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW6_OUT_MAIN, 2 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww6.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW1_OUT_MAIN, 4 },
	{ P_GPWW4_OUT_MAIN, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww1.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_SWEEP_CWK, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW7_OUT_MAIN, 3 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww7.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" },
};

static const stwuct fweq_tbw ftbw_gcc_cpuss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_cpuss_ahb_cwk_swc = {
	.cmd_wcgw = 0x48014,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_cpuss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_0_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0_ao),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
		},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(200000000, P_GPWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x64004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x65004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x66004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPWW0_OUT_EVEN, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pdm2_cwk_swc = {
	.cmd_wcgw = 0x33010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pdm2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pdm2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qspi_cowe_cwk_swc[] = {
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	F(300000000, P_GPWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_qspi_cowe_cwk_swc = {
	.cmd_wcgw = 0x4b00c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_qspi_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qspi_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s0_cwk_swc[] = {
	F(7372800, P_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GPWW0_OUT_EVEN, 1, 4, 25),
	F(51200000, P_GPWW6_OUT_MAIN, 7.5, 0, 0),
	F(64000000, P_GPWW0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(102400000, P_GPWW0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GPWW0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GPWW0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GPWW0_OUT_EVEN, 2.5, 0, 0),
	F(128000000, P_GPWW6_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_1,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s0_cwk_swc = {
	.cmd_wcgw = 0x17034,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s1_cwk_swc = {
	.cmd_wcgw = 0x17164,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s2_cwk_swc = {
	.cmd_wcgw = 0x17294,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s3_cwk_swc = {
	.cmd_wcgw = 0x173c4,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s4_cwk_swc = {
	.cmd_wcgw = 0x174f4,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s5_cwk_swc = {
	.cmd_wcgw = 0x17624,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s0_cwk_swc = {
	.cmd_wcgw = 0x18018,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s1_cwk_swc = {
	.cmd_wcgw = 0x18148,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s2_cwk_swc = {
	.cmd_wcgw = 0x18278,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s3_cwk_swc = {
	.cmd_wcgw = 0x183a8,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s4_cwk_swc = {
	.cmd_wcgw = 0x184d8,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s5_cwk_swc = {
	.cmd_wcgw = 0x18608,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s5_cwk_swc_init,
};


static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk_swc[] = {
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPWW0_OUT_EVEN, 5, 1, 3),
	F(25000000, P_GPWW0_OUT_EVEN, 6, 1, 2),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(192000000, P_GPWW6_OUT_MAIN, 2, 0, 0),
	F(384000000, P_GPWW6_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x12028,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_ice_cowe_cwk_swc[] = {
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x12010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdcc1_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc2_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(202000000, P_GPWW7_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x1400c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.fwags = CWK_OPS_PAWENT_ENABWE,
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_axi_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_axi_cwk_swc = {
	.cmd_wcgw = 0x77020,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
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
	.cmd_wcgw = 0x77048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_phy_aux_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x77098,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_ufs_phy_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_unipwo_cowe_cwk_swc = {
	.cmd_wcgw = 0x77060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_unipwo_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mastew_cwk_swc[] = {
	F(66666667, P_GPWW0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mastew_cwk_swc = {
	.cmd_wcgw = 0xf01c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPWW0_OUT_EVEN, 15, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0xf034,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb3_pwim_phy_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0xf060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_usb3_pwim_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sec_ctww_cwk_swc[] = {
	F(4800000, P_BI_TCXO, 4, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sec_ctww_cwk_swc = {
	.cmd_wcgw = 0x3d030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_sec_ctww_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sec_ctww_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_aggwe_ufs_phy_axi_cwk = {
	.hawt_weg = 0x82024,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x82024,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x82024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_ufs_phy_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_phy_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x8201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_usb3_pwim_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x38004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x38004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_hf_axi_cwk = {
	.hawt_weg = 0xb020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_thwottwe_hf_axi_cwk = {
	.hawt_weg = 0xb080,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb080,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_thwottwe_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_ahb_cwk = {
	.hawt_weg = 0x4100c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x4100c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_axi_cwk = {
	.hawt_weg = 0x41008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_cwk = {
	.hawt_weg = 0x41004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x502c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x502c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cfg_noc_usb3_pwim_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Fow CPUSS functionawity the AHB cwock needs to be weft enabwed */
static stwuct cwk_bwanch gcc_cpuss_ahb_cwk = {
	.hawt_weg = 0x48000,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_cpuss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cpuss_wbcpw_cwk = {
	.hawt_weg = 0x48008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x48008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_wbcpw_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ddwss_gpu_axi_cwk = {
	.hawt_weg = 0x4452c,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4452c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ddwss_gpu_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(18),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_gpww0_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pww0_main_div_cdiv.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_hf_axi_cwk = {
	.hawt_weg = 0xb024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_thwottwe_hf_axi_cwk = {
	.hawt_weg = 0xb084,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb084,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_thwottwe_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x64000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x64000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x65000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x65000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_gp2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0x66000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x66000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_gp3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pww0_main_div_cdiv.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_memnoc_gfx_cwk = {
	.hawt_weg = 0x7100c,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7100c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_memnoc_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_snoc_dvm_gfx_cwk = {
	.hawt_weg = 0x71018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x71018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_snoc_dvm_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_axi_cwk = {
	.hawt_weg = 0x4d008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_bwmon_axi_cwk = {
	.hawt_weg = 0x73008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x73008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_bwmon_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_bwmon_dma_cfg_ahb_cwk = {
	.hawt_weg = 0x73018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x73018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_bwmon_dma_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_bwmon_dsp_cfg_ahb_cwk = {
	.hawt_weg = 0x7301c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7301c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_bwmon_dsp_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_cfg_ahb_cwk = {
	.hawt_weg = 0x4d004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x4d004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x4d004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_dma_cwk = {
	.hawt_weg = 0x4d1a0,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x4d1a0,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x4d1a0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_dma_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_gpww0_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_npu_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_npu_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pww0_main_div_cdiv.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x3300c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pdm2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_ahb_cwk = {
	.hawt_weg = 0x33004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x33004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x33004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_xo4_cwk = {
	.hawt_weg = 0x33008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x33008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_xo4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x34004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x34004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwng_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qspi_cnoc_pewiph_ahb_cwk = {
	.hawt_weg = 0x4b004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x4b004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x4b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qspi_cnoc_pewiph_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qspi_cowe_cwk = {
	.hawt_weg = 0x4b008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4b008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qspi_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qspi_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_2x_cwk = {
	.hawt_weg = 0x17014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_cwk = {
	.hawt_weg = 0x1700c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s0_cwk = {
	.hawt_weg = 0x17030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s1_cwk = {
	.hawt_weg = 0x17160,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s2_cwk = {
	.hawt_weg = 0x17290,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s3_cwk = {
	.hawt_weg = 0x173c0,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s4_cwk = {
	.hawt_weg = 0x174f0,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s5_cwk = {
	.hawt_weg = 0x17620,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_2x_cwk = {
	.hawt_weg = 0x18004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(18),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_cwk = {
	.hawt_weg = 0x18008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s0_cwk = {
	.hawt_weg = 0x18014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(22),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s1_cwk = {
	.hawt_weg = 0x18144,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(23),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s2_cwk = {
	.hawt_weg = 0x18274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(24),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s3_cwk = {
	.hawt_weg = 0x183a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s4_cwk = {
	.hawt_weg = 0x184d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s5_cwk = {
	.hawt_weg = 0x18604,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_0_m_ahb_cwk = {
	.hawt_weg = 0x17004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_0_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_0_s_ahb_cwk = {
	.hawt_weg = 0x17008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x17008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_0_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_m_ahb_cwk = {
	.hawt_weg = 0x1800c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_s_ahb_cwk = {
	.hawt_weg = 0x18010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x18010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x12008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x1200c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdcc1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ice_cowe_cwk = {
	.hawt_weg = 0x12040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdcc1_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x14008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x14008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_apps_cwk = {
	.hawt_weg = 0x14004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x14004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Fow CPUSS functionawity the SYS NOC cwock needs to be weft enabwed */
static stwuct cwk_bwanch gcc_sys_noc_cpuss_ahb_cwk = {
	.hawt_weg = 0x4144,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_cpuss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_cpuss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT,
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

static stwuct cwk_bwanch gcc_ufs_phy_ahb_cwk = {
	.hawt_weg = 0x77014,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_axi_cwk = {
	.hawt_weg = 0x77038,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77038,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_phy_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_ice_cowe_cwk = {
	.hawt_weg = 0x77090,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77090,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_phy_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_phy_aux_cwk = {
	.hawt_weg = 0x77094,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77094,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_phy_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_wx_symbow_0_cwk = {
	.hawt_weg = 0x7701c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x7701c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_tx_symbow_0_cwk = {
	.hawt_weg = 0x77018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x77018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_tx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_unipwo_cowe_cwk = {
	.hawt_weg = 0x7708c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x7708c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7708c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_unipwo_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_phy_unipwo_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_mastew_cwk = {
	.hawt_weg = 0xf010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_mock_utmi_cwk = {
	.hawt_weg = 0xf018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_sweep_cwk = {
	.hawt_weg = 0xf014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_sweep_cwk",
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

static stwuct cwk_bwanch gcc_usb3_pwim_phy_aux_cwk = {
	.hawt_weg = 0xf050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb3_pwim_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_com_aux_cwk = {
	.hawt_weg = 0xf054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_com_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb3_pwim_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_pipe_cwk = {
	.hawt_weg = 0xf058,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0xf058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_phy_cfg_ahb2phy_cwk = {
	.hawt_weg = 0x6a004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x6a004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_phy_cfg_ahb2phy_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_axi_cwk = {
	.hawt_weg = 0xb01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pww0_main_div_cdiv.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_thwottwe_axi_cwk = {
	.hawt_weg = 0xb07c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb07c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_thwottwe_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_cfg_ahb_cwk = {
	.hawt_weg = 0x8a000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8a000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_mfab_axis_cwk = {
	.hawt_weg = 0x8a004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x8a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_mfab_axis_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_nav_axi_cwk = {
	.hawt_weg = 0x8a00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x8a00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_nav_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_snoc_axi_cwk = {
	.hawt_weg = 0x8a150,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8a150,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_snoc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_q6_memnoc_axi_cwk = {
	.hawt_weg = 0x8a154,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8a154,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_q6_memnoc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wpass_cfg_noc_sway_cwk = {
	.hawt_weg = 0x47018,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x47018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wpass_cfg_noc_sway_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc ufs_phy_gdsc = {
	.gdscw = 0x77004,
	.pd = {
		.name = "ufs_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0x0f004,
	.pd = {
		.name = "usb30_pwim_gdsc",
	},
	.pwwsts = PWWSTS_WET_ON,
};

static stwuct gdsc hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc = {
	.gdscw = 0x7d040,
	.pd = {
		.name = "hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_mmnoc_mmu_tbu_sf_gdsc = {
	.gdscw = 0x7d044,
	.pd = {
		.name = "hwos1_vote_mmnoc_mmu_tbu_sf_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc *gcc_sc7180_gdscs[] = {
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_HF0_GDSC] =
					&hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_SF_GDSC] =
					&hwos1_vote_mmnoc_mmu_tbu_sf_gdsc,
};


static stwuct cwk_hw *gcc_sc7180_hws[] = {
	[GCC_GPWW0_MAIN_DIV_CDIV] = &gcc_pww0_main_div_cdiv.hw,
};

static stwuct cwk_wegmap *gcc_sc7180_cwocks[] = {
	[GCC_AGGWE_UFS_PHY_AXI_CWK] = &gcc_aggwe_ufs_phy_axi_cwk.cwkw,
	[GCC_AGGWE_USB3_PWIM_AXI_CWK] = &gcc_aggwe_usb3_pwim_axi_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAMEWA_HF_AXI_CWK] = &gcc_camewa_hf_axi_cwk.cwkw,
	[GCC_CAMEWA_THWOTTWE_HF_AXI_CWK] = &gcc_camewa_thwottwe_hf_axi_cwk.cwkw,
	[GCC_CE1_AHB_CWK] = &gcc_ce1_ahb_cwk.cwkw,
	[GCC_CE1_AXI_CWK] = &gcc_ce1_axi_cwk.cwkw,
	[GCC_CE1_CWK] = &gcc_ce1_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK] = &gcc_cpuss_ahb_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK_SWC] = &gcc_cpuss_ahb_cwk_swc.cwkw,
	[GCC_CPUSS_WBCPW_CWK] = &gcc_cpuss_wbcpw_cwk.cwkw,
	[GCC_DDWSS_GPU_AXI_CWK] = &gcc_ddwss_gpu_axi_cwk.cwkw,
	[GCC_DISP_GPWW0_CWK_SWC] = &gcc_disp_gpww0_cwk_swc.cwkw,
	[GCC_DISP_GPWW0_DIV_CWK_SWC] = &gcc_disp_gpww0_div_cwk_swc.cwkw,
	[GCC_DISP_HF_AXI_CWK] = &gcc_disp_hf_axi_cwk.cwkw,
	[GCC_DISP_THWOTTWE_HF_AXI_CWK] = &gcc_disp_thwottwe_hf_axi_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_CWK_SWC] = &gcc_gpu_gpww0_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_DIV_CWK_SWC] = &gcc_gpu_gpww0_div_cwk_swc.cwkw,
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_NPU_AXI_CWK] = &gcc_npu_axi_cwk.cwkw,
	[GCC_NPU_BWMON_AXI_CWK] = &gcc_npu_bwmon_axi_cwk.cwkw,
	[GCC_NPU_BWMON_DMA_CFG_AHB_CWK] = &gcc_npu_bwmon_dma_cfg_ahb_cwk.cwkw,
	[GCC_NPU_BWMON_DSP_CFG_AHB_CWK] = &gcc_npu_bwmon_dsp_cfg_ahb_cwk.cwkw,
	[GCC_NPU_CFG_AHB_CWK] = &gcc_npu_cfg_ahb_cwk.cwkw,
	[GCC_NPU_DMA_CWK] = &gcc_npu_dma_cwk.cwkw,
	[GCC_NPU_GPWW0_CWK_SWC] = &gcc_npu_gpww0_cwk_swc.cwkw,
	[GCC_NPU_GPWW0_DIV_CWK_SWC] = &gcc_npu_gpww0_div_cwk_swc.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_QSPI_CNOC_PEWIPH_AHB_CWK] = &gcc_qspi_cnoc_pewiph_ahb_cwk.cwkw,
	[GCC_QSPI_COWE_CWK] = &gcc_qspi_cowe_cwk.cwkw,
	[GCC_QSPI_COWE_CWK_SWC] = &gcc_qspi_cowe_cwk_swc.cwkw,
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
	[GCC_UFS_MEM_CWKWEF_CWK] = &gcc_ufs_mem_cwkwef_cwk.cwkw,
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
	[GCC_UFS_PHY_UNIPWO_COWE_CWK_SWC] =
		&gcc_ufs_phy_unipwo_cowe_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MASTEW_CWK] = &gcc_usb30_pwim_mastew_cwk.cwkw,
	[GCC_USB30_PWIM_MASTEW_CWK_SWC] = &gcc_usb30_pwim_mastew_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_CWK] = &gcc_usb30_pwim_mock_utmi_cwk.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_CWK_SWC] =
		&gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_PWIM_SWEEP_CWK] = &gcc_usb30_pwim_sweep_cwk.cwkw,
	[GCC_USB3_PWIM_CWKWEF_CWK] = &gcc_usb3_pwim_cwkwef_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK] = &gcc_usb3_pwim_phy_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK_SWC] = &gcc_usb3_pwim_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PWIM_PHY_COM_AUX_CWK] = &gcc_usb3_pwim_phy_com_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK] = &gcc_usb3_pwim_phy_pipe_cwk.cwkw,
	[GCC_USB_PHY_CFG_AHB2PHY_CWK] = &gcc_usb_phy_cfg_ahb2phy_cwk.cwkw,
	[GCC_VIDEO_AXI_CWK] = &gcc_video_axi_cwk.cwkw,
	[GCC_VIDEO_GPWW0_DIV_CWK_SWC] = &gcc_video_gpww0_div_cwk_swc.cwkw,
	[GCC_VIDEO_THWOTTWE_AXI_CWK] = &gcc_video_thwottwe_axi_cwk.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW0_OUT_EVEN] = &gpww0_out_even.cwkw,
	[GPWW6] = &gpww6.cwkw,
	[GPWW7] = &gpww7.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[GPWW1] = &gpww1.cwkw,
	[GCC_MSS_CFG_AHB_CWK] = &gcc_mss_cfg_ahb_cwk.cwkw,
	[GCC_MSS_MFAB_AXIS_CWK] = &gcc_mss_mfab_axis_cwk.cwkw,
	[GCC_MSS_NAV_AXI_CWK] = &gcc_mss_nav_axi_cwk.cwkw,
	[GCC_MSS_Q6_MEMNOC_AXI_CWK] = &gcc_mss_q6_memnoc_axi_cwk.cwkw,
	[GCC_MSS_SNOC_AXI_CWK] = &gcc_mss_snoc_axi_cwk.cwkw,
	[GCC_SEC_CTWW_CWK_SWC] = &gcc_sec_ctww_cwk_swc.cwkw,
	[GCC_WPASS_CFG_NOC_SWAY_CWK] = &gcc_wpass_cfg_noc_sway_cwk.cwkw,
};

static const stwuct qcom_weset_map gcc_sc7180_wesets[] = {
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x26000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x26004 },
	[GCC_UFS_PHY_BCW] = { 0x77000 },
	[GCC_USB30_PWIM_BCW] = { 0xf000 },
	[GCC_USB3_PHY_PWIM_BCW] = { 0x50000 },
	[GCC_USB3PHY_PHY_PWIM_BCW] = { 0x50004 },
	[GCC_USB3_PHY_SEC_BCW] = { 0x5000c },
	[GCC_USB3_DP_PHY_PWIM_BCW] = { 0x50008 },
	[GCC_USB3PHY_PHY_SEC_BCW] = { 0x50010 },
	[GCC_USB3_DP_PHY_SEC_BCW] = { 0x50014 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x6a000 },
};

static stwuct cwk_wcg_dfs_data gcc_dfs_cwocks[] = {
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

static const stwuct wegmap_config gcc_sc7180_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x18208c,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_sc7180_desc = {
	.config = &gcc_sc7180_wegmap_config,
	.cwk_hws = gcc_sc7180_hws,
	.num_cwk_hws = AWWAY_SIZE(gcc_sc7180_hws),
	.cwks = gcc_sc7180_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sc7180_cwocks),
	.wesets = gcc_sc7180_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sc7180_wesets),
	.gdscs = gcc_sc7180_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sc7180_gdscs),
};

static const stwuct of_device_id gcc_sc7180_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-sc7180" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sc7180_match_tabwe);

static int gcc_sc7180_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_sc7180_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/*
	 * Disabwe the GPWW0 active input to MM bwocks, NPU
	 * and GPU via MISC wegistews.
	 */
	wegmap_update_bits(wegmap, 0x09ffc, 0x3, 0x3);
	wegmap_update_bits(wegmap, 0x4d110, 0x3, 0x3);
	wegmap_update_bits(wegmap, 0x71028, 0x3, 0x3);

	/*
	 * Keep the cwocks awways-ON
	 * GCC_CPUSS_GNOC_CWK, GCC_VIDEO_AHB_CWK, GCC_CAMEWA_AHB_CWK,
	 * GCC_DISP_AHB_CWK, GCC_GPU_CFG_AHB_CWK
	 */
	wegmap_update_bits(wegmap, 0x48004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x0b004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x0b008, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x0b00c, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x0b02c, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x0b028, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x0b030, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x71004, BIT(0), BIT(0));

	wet = qcom_cc_wegistew_wcg_dfs(wegmap, gcc_dfs_cwocks,
					AWWAY_SIZE(gcc_dfs_cwocks));
	if (wet)
		wetuwn wet;

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sc7180_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sc7180_dwivew = {
	.pwobe = gcc_sc7180_pwobe,
	.dwivew = {
		.name = "gcc-sc7180",
		.of_match_tabwe = gcc_sc7180_match_tabwe,
	},
};

static int __init gcc_sc7180_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sc7180_dwivew);
}
cowe_initcaww(gcc_sc7180_init);

static void __exit gcc_sc7180_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sc7180_dwivew);
}
moduwe_exit(gcc_sc7180_exit);

MODUWE_DESCWIPTION("QTI GCC SC7180 Dwivew");
MODUWE_WICENSE("GPW v2");
