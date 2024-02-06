// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gcc-sdm845.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-awpha-pww.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_AUD_WEF_CWK,
	P_GPWW0_OUT_EVEN,
	P_GPWW0_OUT_MAIN,
	P_GPWW4_OUT_MAIN,
	P_GPWW6_OUT_MAIN,
	P_SWEEP_CWK,
};

static stwuct cwk_awpha_pww gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
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
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
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
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww6",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_fabia_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_fabia_even[] = {
	{ 0x0, 1 },
	{ 0x1, 2 },
	{ 0x3, 4 },
	{ 0x7, 8 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_fabia_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_fabia_even),
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

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_SWEEP_CWK, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk", .name = "cowe_pi_sweep_cwk" },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .fw_name = "sweep_cwk", .name = "cowe_pi_sweep_cwk" },
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
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_AUD_WEF_CWK, 2 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "aud_wef_cwk", .name = "aud_wef_cwk" },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct cwk_pawent_data gcc_pawent_data_7_ao[] = {
	{ .fw_name = "bi_tcxo_ao", .name = "bi_tcxo_ao" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
	{ .fw_name = "cowe_bi_pww_test_se", .name = "cowe_bi_pww_test_se" },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "cowe_bi_pww_test_se", .name = "cowe_bi_pww_test_se" },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8_ao[] = {
	{ .fw_name = "bi_tcxo_ao", .name = "bi_tcxo_ao" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "cowe_bi_pww_test_se", .name = "cowe_bi_pww_test_se" },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW4_OUT_MAIN, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW6_OUT_MAIN, 2 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww6.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
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
		.pawent_data = gcc_pawent_data_7_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_cpuss_wbcpw_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_cpuss_wbcpw_cwk_swc = {
	.cmd_wcgw = 0x4815c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_wbcpw_cwk_swc",
		.pawent_data = gcc_pawent_data_8_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdm670_cpuss_wbcpw_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdm670_cpuss_wbcpw_cwk_swc = {
	.cmd_wcgw = 0x4815c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_sdm670_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_wbcpw_cwk_swc",
		.pawent_data = gcc_pawent_data_8_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x64004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x65004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x66004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_aux_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_aux_cwk_swc = {
	.cmd_wcgw = 0x6b028,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_0_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie_1_aux_cwk_swc = {
	.cmd_wcgw = 0x8d028,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_1_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_phy_wefgen_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_phy_wefgen_cwk_swc = {
	.cmd_wcgw = 0x6f014,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_phy_wefgen_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_phy_wefgen_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qspi_cowe_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(150000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_qspi_cowe_cwk_swc = {
	.cmd_wcgw = 0x4b008,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qspi_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qspi_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
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

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s0_cwk_swc[] = {
	F(7372800, P_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GPWW0_OUT_EVEN, 1, 4, 25),
	F(64000000, P_GPWW0_OUT_EVEN, 1, 16, 75),
	F(80000000, P_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	F(102400000, P_GPWW0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GPWW0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GPWW0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GPWW0_OUT_EVEN, 2.5, 0, 0),
	F(128000000, P_GPWW0_OUT_MAIN, 1, 16, 75),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s0_cwk_swc = {
	.cmd_wcgw = 0x17034,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s1_cwk_swc = {
	.cmd_wcgw = 0x17164,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s2_cwk_swc = {
	.cmd_wcgw = 0x17294,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s3_cwk_swc = {
	.cmd_wcgw = 0x173c4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s4_cwk_swc = {
	.cmd_wcgw = 0x174f4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s5_cwk_swc = {
	.cmd_wcgw = 0x17624,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s6_cwk_swc = {
	.cmd_wcgw = 0x17754,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s6_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s7_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s7_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s7_cwk_swc = {
	.cmd_wcgw = 0x17884,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s7_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s0_cwk_swc = {
	.cmd_wcgw = 0x18018,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s1_cwk_swc = {
	.cmd_wcgw = 0x18148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s2_cwk_swc = {
	.cmd_wcgw = 0x18278,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s3_cwk_swc = {
	.cmd_wcgw = 0x183a8,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s4_cwk_swc = {
	.cmd_wcgw = 0x184d8,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s5_cwk_swc = {
	.cmd_wcgw = 0x18608,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s6_cwk_swc = {
	.cmd_wcgw = 0x18738,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s6_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s7_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s7_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s7_cwk_swc = {
	.cmd_wcgw = 0x18868,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s7_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk_swc[] = {
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(20000000, P_GPWW0_OUT_EVEN, 5, 1, 3),
	F(25000000, P_GPWW0_OUT_EVEN, 6, 1, 2),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(192000000, P_GPWW6_OUT_MAIN, 2, 0, 0),
	F(384000000, P_GPWW6_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x26028,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_11,
	.fweq_tbw = ftbw_gcc_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_11,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_ice_cowe_cwk_swc[] = {
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x26010,
	.mnd_width = 8,
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
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(201500000, P_GPWW4_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x1400c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_10,
	.fweq_tbw = ftbw_gcc_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_10,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc4_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPWW0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc4_apps_cwk_swc = {
	.cmd_wcgw = 0x1600c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdcc4_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc4_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdm670_sdcc4_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(33333333, P_GPWW0_OUT_EVEN, 9, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdm670_sdcc4_apps_cwk_swc = {
	.cmd_wcgw = 0x1600c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdm670_sdcc4_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc4_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_tsif_wef_cwk_swc[] = {
	F(105495, P_BI_TCXO, 2, 1, 91),
	{ }
};

static stwuct cwk_wcg2 gcc_tsif_wef_cwk_swc = {
	.cmd_wcgw = 0x36010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_tsif_wef_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_tsif_wef_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_cawd_axi_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_cawd_axi_cwk_swc = {
	.cmd_wcgw = 0x7501c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_cawd_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_cawd_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_cawd_ice_cowe_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_cawd_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x7505c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_cawd_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_cawd_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_ufs_cawd_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x75090,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_cawd_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_cawd_unipwo_cowe_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(150000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_cawd_unipwo_cowe_cwk_swc = {
	.cmd_wcgw = 0x75074,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_cawd_unipwo_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_cawd_unipwo_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_axi_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_axi_cwk_swc = {
	.cmd_wcgw = 0x7701c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_ufs_phy_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x7705c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_cawd_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_ufs_phy_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x77090,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_ufs_phy_unipwo_cowe_cwk_swc = {
	.cmd_wcgw = 0x77074,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_cawd_unipwo_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_unipwo_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mastew_cwk_swc[] = {
	F(33333333, P_GPWW0_OUT_EVEN, 9, 0, 0),
	F(66666667, P_GPWW0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mastew_cwk_swc = {
	.cmd_wcgw = 0xf018,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GPWW0_OUT_EVEN, 15, 0, 0),
	F(40000000, P_GPWW0_OUT_EVEN, 7.5, 0, 0),
	F(60000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0xf030,
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

static stwuct cwk_wcg2 gcc_usb30_sec_mastew_cwk_swc = {
	.cmd_wcgw = 0x10018,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_sec_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb30_sec_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x10030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_sec_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0xf05c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb3_sec_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x1005c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_sec_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_vs_ctww_cwk_swc = {
	.cmd_wcgw = 0x7a030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_vs_ctww_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_vsensow_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	F(600000000, P_GPWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_vsensow_cwk_swc = {
	.cmd_wcgw = 0x7a018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_vsensow_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_vsensow_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_aggwe_noc_pcie_tbu_cwk = {
	.hawt_weg = 0x90014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x90014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_noc_pcie_tbu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_ufs_cawd_axi_cwk = {
	.hawt_weg = 0x82028,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x82028,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x82028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_ufs_cawd_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_cawd_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_ufs_phy_axi_cwk = {
	.hawt_weg = 0x82024,
	.hawt_check = BWANCH_HAWT,
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

static stwuct cwk_bwanch gcc_aggwe_usb3_sec_axi_cwk = {
	.hawt_weg = 0x82020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x82020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_usb3_sec_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_sec_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_apc_vs_cwk = {
	.hawt_weg = 0x7a050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_apc_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
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
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_ahb_cwk = {
	.hawt_weg = 0xb008,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_axi_cwk = {
	.hawt_weg = 0xb020,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_xo_cwk = {
	.hawt_weg = 0xb02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_xo_cwk",
			.fwags = CWK_IS_CWITICAW,
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
		.enabwe_weg = 0x52004,
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
		.enabwe_weg = 0x52004,
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
		.enabwe_weg = 0x52004,
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

static stwuct cwk_bwanch gcc_cfg_noc_usb3_sec_axi_cwk = {
	.hawt_weg = 0x5030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cfg_noc_usb3_sec_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_sec_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cpuss_ahb_cwk = {
	.hawt_weg = 0x48000,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_cpuss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_cpuss_wbcpw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/*
 * The souwce cwock fwequencies awe diffewent fow SDM670; define a chiwd cwock
 * pointing to the souwce cwock that uses SDM670 fwequencies.
 */
static stwuct cwk_bwanch gcc_sdm670_cpuss_wbcpw_cwk = {
	.hawt_weg = 0x48008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x48008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_wbcpw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdm670_cpuss_wbcpw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ddwss_gpu_axi_cwk = {
	.hawt_weg = 0x44038,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x44038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ddwss_gpu_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_ahb_cwk = {
	.hawt_weg = 0xb00c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb00c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_axi_cwk = {
	.hawt_weg = 0xb024,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52004,
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
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_xo_cwk = {
	.hawt_weg = 0xb030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_xo_cwk",
			.fwags = CWK_IS_CWITICAW,
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

static stwuct cwk_bwanch gcc_gpu_cfg_ahb_cwk = {
	.hawt_weg = 0x71004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x71004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x71004,
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
		.enabwe_weg = 0x52004,
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
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_iwef_cwk = {
	.hawt_weg = 0x8c010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_iwef_cwk",
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

static stwuct cwk_bwanch gcc_gpu_vs_cwk = {
	.hawt_weg = 0x7a04c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a04c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_axis2_cwk = {
	.hawt_weg = 0x8a008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8a008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_axis2_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_cfg_ahb_cwk = {
	.hawt_weg = 0x8a000,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x8a000,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x8a000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_gpww0_div_cwk_swc",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_mfab_axis_cwk = {
	.hawt_weg = 0x8a004,
	.hawt_check = BWANCH_VOTED,
	.hwcg_weg = 0x8a004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x8a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_mfab_axis_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_q6_memnoc_axi_cwk = {
	.hawt_weg = 0x8a154,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x8a154,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_q6_memnoc_axi_cwk",
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

static stwuct cwk_bwanch gcc_mss_vs_cwk = {
	.hawt_weg = 0x7a048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_aux_cwk = {
	.hawt_weg = 0x6b01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pcie_0_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cfg_ahb_cwk = {
	.hawt_weg = 0x6b018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x6b018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cwkwef_cwk = {
	.hawt_weg = 0x8c00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_mstw_axi_cwk = {
	.hawt_weg = 0x6b014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_pipe_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_pipe_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_0_pipe_cwk", .name = "pcie_0_pipe_cwk",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_axi_cwk = {
	.hawt_weg = 0x6b010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x6b010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_q2a_axi_cwk = {
	.hawt_weg = 0x6b00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_q2a_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_aux_cwk = {
	.hawt_weg = 0x8d01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(29),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pcie_1_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_cfg_ahb_cwk = {
	.hawt_weg = 0x8d018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8d018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_cwkwef_cwk = {
	.hawt_weg = 0x8c02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_mstw_axi_cwk = {
	.hawt_weg = 0x8d014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_pipe_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(30),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_pipe_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_1_pipe_cwk", .name = "pcie_1_pipe_cwk",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_swv_axi_cwk = {
	.hawt_weg = 0x8d010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8d010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_swv_q2a_axi_cwk = {
	.hawt_weg = 0x8d00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_q2a_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_phy_aux_cwk = {
	.hawt_weg = 0x6f004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6f004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pcie_0_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_phy_wefgen_cwk = {
	.hawt_weg = 0x6f02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6f02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_phy_wefgen_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_pcie_phy_wefgen_cwk_swc.cwkw.hw,
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
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwng_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_camewa_ahb_cwk = {
	.hawt_weg = 0xb014,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_disp_ahb_cwk = {
	.hawt_weg = 0xb018,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_disp_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_ahb_cwk = {
	.hawt_weg = 0xb010,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qspi_cnoc_pewiph_ahb_cwk = {
	.hawt_weg = 0x4b000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4b000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qspi_cnoc_pewiph_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qspi_cowe_cwk = {
	.hawt_weg = 0x4b004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4b004,
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

static stwuct cwk_bwanch gcc_qupv3_wwap0_s0_cwk = {
	.hawt_weg = 0x17030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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

static stwuct cwk_bwanch gcc_qupv3_wwap0_s6_cwk = {
	.hawt_weg = 0x17750,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s7_cwk = {
	.hawt_weg = 0x17880,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap0_s7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s0_cwk = {
	.hawt_weg = 0x18014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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

static stwuct cwk_bwanch gcc_qupv3_wwap1_s6_cwk = {
	.hawt_weg = 0x18734,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s7_cwk = {
	.hawt_weg = 0x18864,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(29),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_qupv3_wwap1_s7_cwk_swc.cwkw.hw,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
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
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x26008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x26008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x26004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x26004,
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
	.hawt_weg = 0x2600c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2600c,
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

static stwuct cwk_bwanch gcc_sdcc4_ahb_cwk = {
	.hawt_weg = 0x16008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_apps_cwk = {
	.hawt_weg = 0x16004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdcc4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/*
 * The souwce cwock fwequencies awe diffewent fow SDM670; define a chiwd cwock
 * pointing to the souwce cwock that uses SDM670 fwequencies.
 */
static stwuct cwk_bwanch gcc_sdm670_sdcc4_apps_cwk = {
	.hawt_weg = 0x16004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdm670_sdcc4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_cpuss_ahb_cwk = {
	.hawt_weg = 0x414c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_cpuss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_cpuss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsif_ahb_cwk = {
	.hawt_weg = 0x36004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_tsif_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsif_inactivity_timews_cwk = {
	.hawt_weg = 0x3600c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_tsif_inactivity_timews_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsif_wef_cwk = {
	.hawt_weg = 0x36008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_tsif_wef_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_tsif_wef_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_ahb_cwk = {
	.hawt_weg = 0x75010,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x75010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x75010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_axi_cwk = {
	.hawt_weg = 0x7500c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x7500c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7500c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_cawd_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_cwkwef_cwk = {
	.hawt_weg = 0x8c004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_ice_cowe_cwk = {
	.hawt_weg = 0x75058,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x75058,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x75058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_cawd_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_phy_aux_cwk = {
	.hawt_weg = 0x7508c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x7508c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7508c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_cawd_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_wx_symbow_0_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x75018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_wx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_wx_symbow_1_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x750a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_wx_symbow_1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_tx_symbow_0_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x75014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_tx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cawd_unipwo_cowe_cwk = {
	.hawt_weg = 0x75054,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x75054,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x75054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cawd_unipwo_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_ufs_cawd_unipwo_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
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
	.hawt_weg = 0x77010,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_axi_cwk = {
	.hawt_weg = 0x7700c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x7700c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7700c,
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
	.hawt_weg = 0x77058,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77058,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77058,
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
	.hawt_weg = 0x7708c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x7708c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7708c,
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
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x77018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_wx_symbow_1_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x770a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_tx_symbow_0_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x77014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_tx_symbow_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_unipwo_cowe_cwk = {
	.hawt_weg = 0x77054,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x77054,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77054,
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
	.hawt_weg = 0xf00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf00c,
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
	.hawt_weg = 0xf014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_pwim_sweep_cwk = {
	.hawt_weg = 0xf010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sec_mastew_cwk = {
	.hawt_weg = 0x1000c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1000c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sec_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_sec_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sec_mock_utmi_cwk = {
	.hawt_weg = 0x10014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sec_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_sec_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sec_sweep_cwk = {
	.hawt_weg = 0x10010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sec_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_cwkwef_cwk = {
	.hawt_weg = 0x8c008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_aux_cwk = {
	.hawt_weg = 0xf04c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf04c,
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
	.hawt_weg = 0xf050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf050,
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
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0xf054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_sec_cwkwef_cwk = {
	.hawt_weg = 0x8c028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8c028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_sec_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_sec_phy_aux_cwk = {
	.hawt_weg = 0x1004c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1004c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_sec_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb3_sec_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_sec_phy_com_aux_cwk = {
	.hawt_weg = 0x10050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_sec_phy_com_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb3_sec_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_sec_phy_pipe_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x10054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_sec_phy_pipe_cwk",
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

static stwuct cwk_bwanch gcc_vdda_vs_cwk = {
	.hawt_weg = 0x7a00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vdda_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vddcx_vs_cwk = {
	.hawt_weg = 0x7a004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vddcx_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vddmx_vs_cwk = {
	.hawt_weg = 0x7a008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vddmx_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_ahb_cwk = {
	.hawt_weg = 0xb004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xb004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xb004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_axi_cwk = {
	.hawt_weg = 0xb01c,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_xo_cwk = {
	.hawt_weg = 0xb028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_xo_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vs_ctww_ahb_cwk = {
	.hawt_weg = 0x7a014,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x7a014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7a014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vs_ctww_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vs_ctww_cwk = {
	.hawt_weg = 0x7a010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7a010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vs_ctww_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vs_ctww_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cpuss_dvm_bus_cwk = {
	.hawt_weg = 0x48190,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x48190,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_dvm_bus_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cpuss_gnoc_cwk = {
	.hawt_weg = 0x48004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x48004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(22),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_gnoc_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* TODO: Wemove aftew DTS updated to pwotect these */
#ifdef CONFIG_SDM_WPASSCC_845
static stwuct cwk_bwanch gcc_wpass_q6_axi_cwk = {
	.hawt_weg = 0x47000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x47000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wpass_q6_axi_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wpass_sway_cwk = {
	.hawt_weg = 0x47008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x47008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wpass_sway_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};
#endif

static stwuct gdsc pcie_0_gdsc = {
	.gdscw = 0x6b004,
	.pd = {
		.name = "pcie_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW,
};

static stwuct gdsc pcie_1_gdsc = {
	.gdscw = 0x8d004,
	.pd = {
		.name = "pcie_1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW,
};

static stwuct gdsc ufs_cawd_gdsc = {
	.gdscw = 0x75004,
	.pd = {
		.name = "ufs_cawd_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW,
};

static stwuct gdsc ufs_phy_gdsc = {
	.gdscw = 0x77004,
	.pd = {
		.name = "ufs_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW,
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0xf004,
	.pd = {
		.name = "usb30_pwim_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW,
};

static stwuct gdsc usb30_sec_gdsc = {
	.gdscw = 0x10004,
	.pd = {
		.name = "usb30_sec_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW,
};

static stwuct gdsc hwos1_vote_aggwe_noc_mmu_audio_tbu_gdsc = {
	.gdscw = 0x7d030,
	.pd = {
		.name = "hwos1_vote_aggwe_noc_mmu_audio_tbu_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_aggwe_noc_mmu_pcie_tbu_gdsc = {
	.gdscw = 0x7d03c,
	.pd = {
		.name = "hwos1_vote_aggwe_noc_mmu_pcie_tbu_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_aggwe_noc_mmu_tbu1_gdsc = {
	.gdscw = 0x7d034,
	.pd = {
		.name = "hwos1_vote_aggwe_noc_mmu_tbu1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_aggwe_noc_mmu_tbu2_gdsc = {
	.gdscw = 0x7d038,
	.pd = {
		.name = "hwos1_vote_aggwe_noc_mmu_tbu2_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc = {
	.gdscw = 0x7d040,
	.pd = {
		.name = "hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_mmnoc_mmu_tbu_hf1_gdsc = {
	.gdscw = 0x7d048,
	.pd = {
		.name = "hwos1_vote_mmnoc_mmu_tbu_hf1_gdsc",
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

static stwuct cwk_wegmap *gcc_sdm670_cwocks[] = {
	[GCC_AGGWE_UFS_PHY_AXI_CWK] = &gcc_aggwe_ufs_phy_axi_cwk.cwkw,
	[GCC_AGGWE_USB3_PWIM_AXI_CWK] = &gcc_aggwe_usb3_pwim_axi_cwk.cwkw,
	[GCC_APC_VS_CWK] = &gcc_apc_vs_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAMEWA_AHB_CWK] = &gcc_camewa_ahb_cwk.cwkw,
	[GCC_CAMEWA_AXI_CWK] = &gcc_camewa_axi_cwk.cwkw,
	[GCC_CAMEWA_XO_CWK] = &gcc_camewa_xo_cwk.cwkw,
	[GCC_CE1_AHB_CWK] = &gcc_ce1_ahb_cwk.cwkw,
	[GCC_CE1_AXI_CWK] = &gcc_ce1_axi_cwk.cwkw,
	[GCC_CE1_CWK] = &gcc_ce1_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK] = &gcc_cpuss_ahb_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK_SWC] = &gcc_cpuss_ahb_cwk_swc.cwkw,
	[GCC_CPUSS_WBCPW_CWK] = &gcc_sdm670_cpuss_wbcpw_cwk.cwkw,
	[GCC_CPUSS_WBCPW_CWK_SWC] = &gcc_sdm670_cpuss_wbcpw_cwk_swc.cwkw,
	[GCC_DDWSS_GPU_AXI_CWK] = &gcc_ddwss_gpu_axi_cwk.cwkw,
	[GCC_DISP_AHB_CWK] = &gcc_disp_ahb_cwk.cwkw,
	[GCC_DISP_AXI_CWK] = &gcc_disp_axi_cwk.cwkw,
	[GCC_DISP_GPWW0_CWK_SWC] = &gcc_disp_gpww0_cwk_swc.cwkw,
	[GCC_DISP_GPWW0_DIV_CWK_SWC] = &gcc_disp_gpww0_div_cwk_swc.cwkw,
	[GCC_DISP_XO_CWK] = &gcc_disp_xo_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPU_CFG_AHB_CWK] = &gcc_gpu_cfg_ahb_cwk.cwkw,
	[GCC_GPU_GPWW0_CWK_SWC] = &gcc_gpu_gpww0_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_DIV_CWK_SWC] = &gcc_gpu_gpww0_div_cwk_swc.cwkw,
	[GCC_GPU_IWEF_CWK] = &gcc_gpu_iwef_cwk.cwkw,
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_GPU_VS_CWK] = &gcc_gpu_vs_cwk.cwkw,
	[GCC_MSS_AXIS2_CWK] = &gcc_mss_axis2_cwk.cwkw,
	[GCC_MSS_CFG_AHB_CWK] = &gcc_mss_cfg_ahb_cwk.cwkw,
	[GCC_MSS_GPWW0_DIV_CWK_SWC] = &gcc_mss_gpww0_div_cwk_swc.cwkw,
	[GCC_MSS_MFAB_AXIS_CWK] = &gcc_mss_mfab_axis_cwk.cwkw,
	[GCC_MSS_Q6_MEMNOC_AXI_CWK] = &gcc_mss_q6_memnoc_axi_cwk.cwkw,
	[GCC_MSS_SNOC_AXI_CWK] = &gcc_mss_snoc_axi_cwk.cwkw,
	[GCC_MSS_VS_CWK] = &gcc_mss_vs_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_QMIP_CAMEWA_AHB_CWK] = &gcc_qmip_camewa_ahb_cwk.cwkw,
	[GCC_QMIP_DISP_AHB_CWK] = &gcc_qmip_disp_ahb_cwk.cwkw,
	[GCC_QMIP_VIDEO_AHB_CWK] = &gcc_qmip_video_ahb_cwk.cwkw,
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
	[GCC_QUPV3_WWAP0_S6_CWK] = &gcc_qupv3_wwap0_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S6_CWK_SWC] = &gcc_qupv3_wwap0_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S7_CWK] = &gcc_qupv3_wwap0_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S7_CWK_SWC] = &gcc_qupv3_wwap0_s7_cwk_swc.cwkw,
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
	[GCC_QUPV3_WWAP1_S6_CWK] = &gcc_qupv3_wwap1_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S6_CWK_SWC] = &gcc_qupv3_wwap1_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S7_CWK] = &gcc_qupv3_wwap1_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S7_CWK_SWC] = &gcc_qupv3_wwap1_s7_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP_0_M_AHB_CWK] = &gcc_qupv3_wwap_0_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_0_S_AHB_CWK] = &gcc_qupv3_wwap_0_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_M_AHB_CWK] = &gcc_qupv3_wwap_1_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_S_AHB_CWK] = &gcc_qupv3_wwap_1_s_ahb_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK_SWC] = &gcc_sdcc1_apps_cwk_swc.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK_SWC] = &gcc_sdcc1_ice_cowe_cwk_swc.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK] = &gcc_sdcc1_ice_cowe_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK_SWC] = &gcc_sdcc2_apps_cwk_swc.cwkw,
	[GCC_SDCC4_AHB_CWK] = &gcc_sdcc4_ahb_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK] = &gcc_sdm670_sdcc4_apps_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK_SWC] = &gcc_sdm670_sdcc4_apps_cwk_swc.cwkw,
	[GCC_SYS_NOC_CPUSS_AHB_CWK] = &gcc_sys_noc_cpuss_ahb_cwk.cwkw,
	[GCC_TSIF_AHB_CWK] = &gcc_tsif_ahb_cwk.cwkw,
	[GCC_TSIF_INACTIVITY_TIMEWS_CWK] =
					&gcc_tsif_inactivity_timews_cwk.cwkw,
	[GCC_TSIF_WEF_CWK] = &gcc_tsif_wef_cwk.cwkw,
	[GCC_TSIF_WEF_CWK_SWC] = &gcc_tsif_wef_cwk_swc.cwkw,
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
	[GCC_VDDA_VS_CWK] = &gcc_vdda_vs_cwk.cwkw,
	[GCC_VDDCX_VS_CWK] = &gcc_vddcx_vs_cwk.cwkw,
	[GCC_VDDMX_VS_CWK] = &gcc_vddmx_vs_cwk.cwkw,
	[GCC_VIDEO_AHB_CWK] = &gcc_video_ahb_cwk.cwkw,
	[GCC_VIDEO_AXI_CWK] = &gcc_video_axi_cwk.cwkw,
	[GCC_VIDEO_XO_CWK] = &gcc_video_xo_cwk.cwkw,
	[GCC_VS_CTWW_AHB_CWK] = &gcc_vs_ctww_ahb_cwk.cwkw,
	[GCC_VS_CTWW_CWK] = &gcc_vs_ctww_cwk.cwkw,
	[GCC_VS_CTWW_CWK_SWC] = &gcc_vs_ctww_cwk_swc.cwkw,
	[GCC_VSENSOW_CWK_SWC] = &gcc_vsensow_cwk_swc.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW0_OUT_EVEN] = &gpww0_out_even.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[GPWW6] = &gpww6.cwkw,
	[GCC_CPUSS_DVM_BUS_CWK] = &gcc_cpuss_dvm_bus_cwk.cwkw,
	[GCC_CPUSS_GNOC_CWK] = &gcc_cpuss_gnoc_cwk.cwkw,
	[GCC_QSPI_COWE_CWK_SWC] = &gcc_qspi_cowe_cwk_swc.cwkw,
	[GCC_QSPI_COWE_CWK] = &gcc_qspi_cowe_cwk.cwkw,
	[GCC_QSPI_CNOC_PEWIPH_AHB_CWK] = &gcc_qspi_cnoc_pewiph_ahb_cwk.cwkw,
};

static stwuct cwk_wegmap *gcc_sdm845_cwocks[] = {
	[GCC_AGGWE_NOC_PCIE_TBU_CWK] = &gcc_aggwe_noc_pcie_tbu_cwk.cwkw,
	[GCC_AGGWE_UFS_CAWD_AXI_CWK] = &gcc_aggwe_ufs_cawd_axi_cwk.cwkw,
	[GCC_AGGWE_UFS_PHY_AXI_CWK] = &gcc_aggwe_ufs_phy_axi_cwk.cwkw,
	[GCC_AGGWE_USB3_PWIM_AXI_CWK] = &gcc_aggwe_usb3_pwim_axi_cwk.cwkw,
	[GCC_AGGWE_USB3_SEC_AXI_CWK] = &gcc_aggwe_usb3_sec_axi_cwk.cwkw,
	[GCC_APC_VS_CWK] = &gcc_apc_vs_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAMEWA_AHB_CWK] = &gcc_camewa_ahb_cwk.cwkw,
	[GCC_CAMEWA_AXI_CWK] = &gcc_camewa_axi_cwk.cwkw,
	[GCC_CAMEWA_XO_CWK] = &gcc_camewa_xo_cwk.cwkw,
	[GCC_CE1_AHB_CWK] = &gcc_ce1_ahb_cwk.cwkw,
	[GCC_CE1_AXI_CWK] = &gcc_ce1_axi_cwk.cwkw,
	[GCC_CE1_CWK] = &gcc_ce1_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_CFG_NOC_USB3_SEC_AXI_CWK] = &gcc_cfg_noc_usb3_sec_axi_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK] = &gcc_cpuss_ahb_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK_SWC] = &gcc_cpuss_ahb_cwk_swc.cwkw,
	[GCC_CPUSS_WBCPW_CWK] = &gcc_cpuss_wbcpw_cwk.cwkw,
	[GCC_CPUSS_WBCPW_CWK_SWC] = &gcc_cpuss_wbcpw_cwk_swc.cwkw,
	[GCC_DDWSS_GPU_AXI_CWK] = &gcc_ddwss_gpu_axi_cwk.cwkw,
	[GCC_DISP_AHB_CWK] = &gcc_disp_ahb_cwk.cwkw,
	[GCC_DISP_AXI_CWK] = &gcc_disp_axi_cwk.cwkw,
	[GCC_DISP_GPWW0_CWK_SWC] = &gcc_disp_gpww0_cwk_swc.cwkw,
	[GCC_DISP_GPWW0_DIV_CWK_SWC] = &gcc_disp_gpww0_div_cwk_swc.cwkw,
	[GCC_DISP_XO_CWK] = &gcc_disp_xo_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPU_CFG_AHB_CWK] = &gcc_gpu_cfg_ahb_cwk.cwkw,
	[GCC_GPU_GPWW0_CWK_SWC] = &gcc_gpu_gpww0_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_DIV_CWK_SWC] = &gcc_gpu_gpww0_div_cwk_swc.cwkw,
	[GCC_GPU_IWEF_CWK] = &gcc_gpu_iwef_cwk.cwkw,
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_GPU_VS_CWK] = &gcc_gpu_vs_cwk.cwkw,
	[GCC_MSS_AXIS2_CWK] = &gcc_mss_axis2_cwk.cwkw,
	[GCC_MSS_CFG_AHB_CWK] = &gcc_mss_cfg_ahb_cwk.cwkw,
	[GCC_MSS_GPWW0_DIV_CWK_SWC] = &gcc_mss_gpww0_div_cwk_swc.cwkw,
	[GCC_MSS_MFAB_AXIS_CWK] = &gcc_mss_mfab_axis_cwk.cwkw,
	[GCC_MSS_Q6_MEMNOC_AXI_CWK] = &gcc_mss_q6_memnoc_axi_cwk.cwkw,
	[GCC_MSS_SNOC_AXI_CWK] = &gcc_mss_snoc_axi_cwk.cwkw,
	[GCC_MSS_VS_CWK] = &gcc_mss_vs_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK] = &gcc_pcie_0_aux_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK_SWC] = &gcc_pcie_0_aux_cwk_swc.cwkw,
	[GCC_PCIE_0_CFG_AHB_CWK] = &gcc_pcie_0_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_0_CWKWEF_CWK] = &gcc_pcie_0_cwkwef_cwk.cwkw,
	[GCC_PCIE_0_MSTW_AXI_CWK] = &gcc_pcie_0_mstw_axi_cwk.cwkw,
	[GCC_PCIE_0_PIPE_CWK] = &gcc_pcie_0_pipe_cwk.cwkw,
	[GCC_PCIE_0_SWV_AXI_CWK] = &gcc_pcie_0_swv_axi_cwk.cwkw,
	[GCC_PCIE_0_SWV_Q2A_AXI_CWK] = &gcc_pcie_0_swv_q2a_axi_cwk.cwkw,
	[GCC_PCIE_1_AUX_CWK] = &gcc_pcie_1_aux_cwk.cwkw,
	[GCC_PCIE_1_AUX_CWK_SWC] = &gcc_pcie_1_aux_cwk_swc.cwkw,
	[GCC_PCIE_1_CFG_AHB_CWK] = &gcc_pcie_1_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_1_CWKWEF_CWK] = &gcc_pcie_1_cwkwef_cwk.cwkw,
	[GCC_PCIE_1_MSTW_AXI_CWK] = &gcc_pcie_1_mstw_axi_cwk.cwkw,
	[GCC_PCIE_1_PIPE_CWK] = &gcc_pcie_1_pipe_cwk.cwkw,
	[GCC_PCIE_1_SWV_AXI_CWK] = &gcc_pcie_1_swv_axi_cwk.cwkw,
	[GCC_PCIE_1_SWV_Q2A_AXI_CWK] = &gcc_pcie_1_swv_q2a_axi_cwk.cwkw,
	[GCC_PCIE_PHY_AUX_CWK] = &gcc_pcie_phy_aux_cwk.cwkw,
	[GCC_PCIE_PHY_WEFGEN_CWK] = &gcc_pcie_phy_wefgen_cwk.cwkw,
	[GCC_PCIE_PHY_WEFGEN_CWK_SWC] = &gcc_pcie_phy_wefgen_cwk_swc.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_QMIP_CAMEWA_AHB_CWK] = &gcc_qmip_camewa_ahb_cwk.cwkw,
	[GCC_QMIP_DISP_AHB_CWK] = &gcc_qmip_disp_ahb_cwk.cwkw,
	[GCC_QMIP_VIDEO_AHB_CWK] = &gcc_qmip_video_ahb_cwk.cwkw,
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
	[GCC_QUPV3_WWAP0_S6_CWK] = &gcc_qupv3_wwap0_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S6_CWK_SWC] = &gcc_qupv3_wwap0_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S7_CWK] = &gcc_qupv3_wwap0_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S7_CWK_SWC] = &gcc_qupv3_wwap0_s7_cwk_swc.cwkw,
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
	[GCC_QUPV3_WWAP1_S6_CWK] = &gcc_qupv3_wwap1_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S6_CWK_SWC] = &gcc_qupv3_wwap1_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP1_S7_CWK] = &gcc_qupv3_wwap1_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S7_CWK_SWC] = &gcc_qupv3_wwap1_s7_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP_0_M_AHB_CWK] = &gcc_qupv3_wwap_0_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_0_S_AHB_CWK] = &gcc_qupv3_wwap_0_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_M_AHB_CWK] = &gcc_qupv3_wwap_1_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_S_AHB_CWK] = &gcc_qupv3_wwap_1_s_ahb_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK_SWC] = &gcc_sdcc2_apps_cwk_swc.cwkw,
	[GCC_SDCC4_AHB_CWK] = &gcc_sdcc4_ahb_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK] = &gcc_sdcc4_apps_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK_SWC] = &gcc_sdcc4_apps_cwk_swc.cwkw,
	[GCC_SYS_NOC_CPUSS_AHB_CWK] = &gcc_sys_noc_cpuss_ahb_cwk.cwkw,
	[GCC_TSIF_AHB_CWK] = &gcc_tsif_ahb_cwk.cwkw,
	[GCC_TSIF_INACTIVITY_TIMEWS_CWK] =
					&gcc_tsif_inactivity_timews_cwk.cwkw,
	[GCC_TSIF_WEF_CWK] = &gcc_tsif_wef_cwk.cwkw,
	[GCC_TSIF_WEF_CWK_SWC] = &gcc_tsif_wef_cwk_swc.cwkw,
	[GCC_UFS_CAWD_AHB_CWK] = &gcc_ufs_cawd_ahb_cwk.cwkw,
	[GCC_UFS_CAWD_AXI_CWK] = &gcc_ufs_cawd_axi_cwk.cwkw,
	[GCC_UFS_CAWD_AXI_CWK_SWC] = &gcc_ufs_cawd_axi_cwk_swc.cwkw,
	[GCC_UFS_CAWD_CWKWEF_CWK] = &gcc_ufs_cawd_cwkwef_cwk.cwkw,
	[GCC_UFS_CAWD_ICE_COWE_CWK] = &gcc_ufs_cawd_ice_cowe_cwk.cwkw,
	[GCC_UFS_CAWD_ICE_COWE_CWK_SWC] = &gcc_ufs_cawd_ice_cowe_cwk_swc.cwkw,
	[GCC_UFS_CAWD_PHY_AUX_CWK] = &gcc_ufs_cawd_phy_aux_cwk.cwkw,
	[GCC_UFS_CAWD_PHY_AUX_CWK_SWC] = &gcc_ufs_cawd_phy_aux_cwk_swc.cwkw,
	[GCC_UFS_CAWD_WX_SYMBOW_0_CWK] = &gcc_ufs_cawd_wx_symbow_0_cwk.cwkw,
	[GCC_UFS_CAWD_WX_SYMBOW_1_CWK] = &gcc_ufs_cawd_wx_symbow_1_cwk.cwkw,
	[GCC_UFS_CAWD_TX_SYMBOW_0_CWK] = &gcc_ufs_cawd_tx_symbow_0_cwk.cwkw,
	[GCC_UFS_CAWD_UNIPWO_COWE_CWK] = &gcc_ufs_cawd_unipwo_cowe_cwk.cwkw,
	[GCC_UFS_CAWD_UNIPWO_COWE_CWK_SWC] =
					&gcc_ufs_cawd_unipwo_cowe_cwk_swc.cwkw,
	[GCC_UFS_MEM_CWKWEF_CWK] = &gcc_ufs_mem_cwkwef_cwk.cwkw,
	[GCC_UFS_PHY_AHB_CWK] = &gcc_ufs_phy_ahb_cwk.cwkw,
	[GCC_UFS_PHY_AXI_CWK] = &gcc_ufs_phy_axi_cwk.cwkw,
	[GCC_UFS_PHY_AXI_CWK_SWC] = &gcc_ufs_phy_axi_cwk_swc.cwkw,
	[GCC_UFS_PHY_ICE_COWE_CWK] = &gcc_ufs_phy_ice_cowe_cwk.cwkw,
	[GCC_UFS_PHY_ICE_COWE_CWK_SWC] = &gcc_ufs_phy_ice_cowe_cwk_swc.cwkw,
	[GCC_UFS_PHY_PHY_AUX_CWK] = &gcc_ufs_phy_phy_aux_cwk.cwkw,
	[GCC_UFS_PHY_PHY_AUX_CWK_SWC] = &gcc_ufs_phy_phy_aux_cwk_swc.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_0_CWK] = &gcc_ufs_phy_wx_symbow_0_cwk.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_1_CWK] = &gcc_ufs_phy_wx_symbow_1_cwk.cwkw,
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
	[GCC_USB30_SEC_MASTEW_CWK] = &gcc_usb30_sec_mastew_cwk.cwkw,
	[GCC_USB30_SEC_MASTEW_CWK_SWC] = &gcc_usb30_sec_mastew_cwk_swc.cwkw,
	[GCC_USB30_SEC_MOCK_UTMI_CWK] = &gcc_usb30_sec_mock_utmi_cwk.cwkw,
	[GCC_USB30_SEC_MOCK_UTMI_CWK_SWC] =
					&gcc_usb30_sec_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_SEC_SWEEP_CWK] = &gcc_usb30_sec_sweep_cwk.cwkw,
	[GCC_USB3_PWIM_CWKWEF_CWK] = &gcc_usb3_pwim_cwkwef_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK] = &gcc_usb3_pwim_phy_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK_SWC] = &gcc_usb3_pwim_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PWIM_PHY_COM_AUX_CWK] = &gcc_usb3_pwim_phy_com_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK] = &gcc_usb3_pwim_phy_pipe_cwk.cwkw,
	[GCC_USB3_SEC_CWKWEF_CWK] = &gcc_usb3_sec_cwkwef_cwk.cwkw,
	[GCC_USB3_SEC_PHY_AUX_CWK] = &gcc_usb3_sec_phy_aux_cwk.cwkw,
	[GCC_USB3_SEC_PHY_AUX_CWK_SWC] = &gcc_usb3_sec_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_SEC_PHY_COM_AUX_CWK] = &gcc_usb3_sec_phy_com_aux_cwk.cwkw,
	[GCC_USB3_SEC_PHY_PIPE_CWK] = &gcc_usb3_sec_phy_pipe_cwk.cwkw,
	[GCC_USB_PHY_CFG_AHB2PHY_CWK] = &gcc_usb_phy_cfg_ahb2phy_cwk.cwkw,
	[GCC_VDDA_VS_CWK] = &gcc_vdda_vs_cwk.cwkw,
	[GCC_VDDCX_VS_CWK] = &gcc_vddcx_vs_cwk.cwkw,
	[GCC_VDDMX_VS_CWK] = &gcc_vddmx_vs_cwk.cwkw,
	[GCC_VIDEO_AHB_CWK] = &gcc_video_ahb_cwk.cwkw,
	[GCC_VIDEO_AXI_CWK] = &gcc_video_axi_cwk.cwkw,
	[GCC_VIDEO_XO_CWK] = &gcc_video_xo_cwk.cwkw,
	[GCC_VS_CTWW_AHB_CWK] = &gcc_vs_ctww_ahb_cwk.cwkw,
	[GCC_VS_CTWW_CWK] = &gcc_vs_ctww_cwk.cwkw,
	[GCC_VS_CTWW_CWK_SWC] = &gcc_vs_ctww_cwk_swc.cwkw,
	[GCC_VSENSOW_CWK_SWC] = &gcc_vsensow_cwk_swc.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW0_OUT_EVEN] = &gpww0_out_even.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[GCC_CPUSS_DVM_BUS_CWK] = &gcc_cpuss_dvm_bus_cwk.cwkw,
	[GCC_CPUSS_GNOC_CWK] = &gcc_cpuss_gnoc_cwk.cwkw,
	[GCC_QSPI_COWE_CWK_SWC] = &gcc_qspi_cowe_cwk_swc.cwkw,
	[GCC_QSPI_COWE_CWK] = &gcc_qspi_cowe_cwk.cwkw,
	[GCC_QSPI_CNOC_PEWIPH_AHB_CWK] = &gcc_qspi_cnoc_pewiph_ahb_cwk.cwkw,
#ifdef CONFIG_SDM_WPASSCC_845
	[GCC_WPASS_Q6_AXI_CWK] = &gcc_wpass_q6_axi_cwk.cwkw,
	[GCC_WPASS_SWAY_CWK] = &gcc_wpass_sway_cwk.cwkw,
#endif
};

static const stwuct qcom_weset_map gcc_sdm845_wesets[] = {
	[GCC_MMSS_BCW] = { 0xb000 },
	[GCC_PCIE_0_BCW] = { 0x6b000 },
	[GCC_PCIE_1_BCW] = { 0x8d000 },
	[GCC_PCIE_PHY_BCW] = { 0x6f000 },
	[GCC_PDM_BCW] = { 0x33000 },
	[GCC_PWNG_BCW] = { 0x34000 },
	[GCC_QUPV3_WWAPPEW_0_BCW] = { 0x17000 },
	[GCC_QUPV3_WWAPPEW_1_BCW] = { 0x18000 },
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x12000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x12004 },
	[GCC_SDCC2_BCW] = { 0x14000 },
	[GCC_SDCC4_BCW] = { 0x16000 },
	[GCC_TSIF_BCW] = { 0x36000 },
	[GCC_UFS_CAWD_BCW] = { 0x75000 },
	[GCC_UFS_PHY_BCW] = { 0x77000 },
	[GCC_USB30_PWIM_BCW] = { 0xf000 },
	[GCC_USB30_SEC_BCW] = { 0x10000 },
	[GCC_USB3_PHY_PWIM_BCW] = { 0x50000 },
	[GCC_USB3PHY_PHY_PWIM_BCW] = { 0x50004 },
	[GCC_USB3_DP_PHY_PWIM_BCW] = { 0x50008 },
	[GCC_USB3_PHY_SEC_BCW] = { 0x5000c },
	[GCC_USB3PHY_PHY_SEC_BCW] = { 0x50010 },
	[GCC_USB3_DP_PHY_SEC_BCW] = { 0x50014 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x6a000 },
	[GCC_PCIE_0_PHY_BCW] = { 0x6c01c },
	[GCC_PCIE_1_PHY_BCW] = { 0x8e01c },
};

static stwuct gdsc *gcc_sdm670_gdscs[] = {
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_AUDIO_TBU_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_audio_tbu_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_TBU1_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_tbu1_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_TBU2_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_tbu2_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_HF0_GDSC] =
			&hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_HF1_GDSC] =
			&hwos1_vote_mmnoc_mmu_tbu_hf1_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_SF_GDSC] = &hwos1_vote_mmnoc_mmu_tbu_sf_gdsc,
};

static stwuct gdsc *gcc_sdm845_gdscs[] = {
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_1_GDSC] = &pcie_1_gdsc,
	[UFS_CAWD_GDSC] = &ufs_cawd_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
	[USB30_SEC_GDSC] = &usb30_sec_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_AUDIO_TBU_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_audio_tbu_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_PCIE_TBU_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_pcie_tbu_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_TBU1_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_tbu1_gdsc,
	[HWOS1_VOTE_AGGWE_NOC_MMU_TBU2_GDSC] =
			&hwos1_vote_aggwe_noc_mmu_tbu2_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_HF0_GDSC] =
			&hwos1_vote_mmnoc_mmu_tbu_hf0_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_HF1_GDSC] =
			&hwos1_vote_mmnoc_mmu_tbu_hf1_gdsc,
	[HWOS1_VOTE_MMNOC_MMU_TBU_SF_GDSC] = &hwos1_vote_mmnoc_mmu_tbu_sf_gdsc,
};

static const stwuct wegmap_config gcc_sdm845_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x182090,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_sdm670_desc = {
	.config = &gcc_sdm845_wegmap_config,
	.cwks = gcc_sdm670_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sdm670_cwocks),
	/* Snapdwagon 670 can function without its own excwusive wesets. */
	.wesets = gcc_sdm845_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sdm845_wesets),
	.gdscs = gcc_sdm670_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sdm670_gdscs),
};

static const stwuct qcom_cc_desc gcc_sdm845_desc = {
	.config = &gcc_sdm845_wegmap_config,
	.cwks = gcc_sdm845_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sdm845_cwocks),
	.wesets = gcc_sdm845_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sdm845_wesets),
	.gdscs = gcc_sdm845_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sdm845_gdscs),
};

static const stwuct of_device_id gcc_sdm845_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-sdm670", .data = &gcc_sdm670_desc },
	{ .compatibwe = "qcom,gcc-sdm845", .data = &gcc_sdm845_desc },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sdm845_match_tabwe);

static const stwuct cwk_wcg_dfs_data gcc_dfs_cwocks[] = {
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s5_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s6_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap0_s7_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s5_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s6_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s7_cwk_swc),
};

static int gcc_sdm845_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *gcc_desc;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_sdm845_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Disabwe the GPWW0 active input to MMSS and GPU via MISC wegistews */
	wegmap_update_bits(wegmap, 0x09ffc, 0x3, 0x3);
	wegmap_update_bits(wegmap, 0x71028, 0x3, 0x3);

	wet = qcom_cc_wegistew_wcg_dfs(wegmap, gcc_dfs_cwocks,
					AWWAY_SIZE(gcc_dfs_cwocks));
	if (wet)
		wetuwn wet;

	gcc_desc = of_device_get_match_data(&pdev->dev);
	wetuwn qcom_cc_weawwy_pwobe(pdev, gcc_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sdm845_dwivew = {
	.pwobe		= gcc_sdm845_pwobe,
	.dwivew		= {
		.name	= "gcc-sdm845",
		.of_match_tabwe = gcc_sdm845_match_tabwe,
	},
};

static int __init gcc_sdm845_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sdm845_dwivew);
}
cowe_initcaww(gcc_sdm845_init);

static void __exit gcc_sdm845_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sdm845_dwivew);
}
moduwe_exit(gcc_sdm845_exit);

MODUWE_DESCWIPTION("QTI GCC SDM845 Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:gcc-sdm845");
