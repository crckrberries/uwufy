// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gcc-qcs404.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	DT_XO,
	DT_SWEEP_CWK,
	DT_PCIE_0_PIPE_CWK,
	DT_DSI0_PHY_PWW_OUT_DSICWK,
	DT_DSI0_PHY_PWW_OUT_BYTECWK,
	DT_HDMI_PHY_PWW_CWK,
};

enum {
	P_DSI0_PHY_PWW_OUT_BYTECWK,
	P_DSI0_PHY_PWW_OUT_DSICWK,
	P_GPWW0_OUT_MAIN,
	P_GPWW1_OUT_MAIN,
	P_GPWW3_OUT_MAIN,
	P_GPWW4_OUT_MAIN,
	P_GPWW6_OUT_AUX,
	P_HDMI_PHY_PWW_CWK,
	P_PCIE_0_PIPE_CWK,
	P_SWEEP_CWK,
	P_XO,
};

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_XO, 0 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
};

static stwuct cwk_fixed_factow cxo = {
	.muwt = 1,
	.div = 1,
	.hw.init = &(stwuct cwk_init_data){
		.name = "cxo",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww0_sweep_cwk_swc = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x45008,
		.enabwe_mask = BIT(23),
		.enabwe_is_invewted = twue,
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0_sweep_cwk_swc",
			.pawent_data = gcc_pawent_data_1,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww0_out_main = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.fwags = SUPPOWTS_FSM_MODE,
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0_out_main",
			.pawent_data = gcc_pawent_data_1,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww0_ao_out_main = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.fwags = SUPPOWTS_FSM_MODE,
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0_ao_out_main",
			.pawent_data = gcc_pawent_data_1,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_awpha_pww_fixed_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww1_out_main = {
	.offset = 0x20000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww1_out_main",
			.pawent_data = gcc_pawent_data_1,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

/* 930MHz configuwation */
static const stwuct awpha_pww_config gpww3_config = {
	.w = 48,
	.awpha = 0x0,
	.awpha_en_mask = BIT(24),
	.post_div_mask = 0xf << 8,
	.post_div_vaw = 0x1 << 8,
	.vco_mask = 0x3 << 20,
	.main_output_mask = 0x1,
	.config_ctw_vaw = 0x4001055b,
};

static const stwuct pww_vco gpww3_vco[] = {
	{ 700000000, 1400000000, 0 },
};

static stwuct cwk_awpha_pww gpww3_out_main = {
	.offset = 0x22000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.vco_tabwe = gpww3_vco,
	.num_vco = AWWAY_SIZE(gpww3_vco),
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww3_out_main",
			.pawent_data = gcc_pawent_data_1,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww4_out_main = {
	.offset = 0x24000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4_out_main",
			.pawent_data = gcc_pawent_data_1,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_pww gpww6 = {
	.w_weg = 0x37004,
	.m_weg = 0x37008,
	.n_weg = 0x3700C,
	.config_weg = 0x37014,
	.mode_weg = 0x37000,
	.status_weg = 0x3701C,
	.status_bit = 17,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww6",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_wegmap gpww6_out_aux = {
	.enabwe_weg = 0x45000,
	.enabwe_mask = BIT(7),
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww6_out_aux",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gpww6.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
};

static const stwuct cwk_pawent_data gcc_pawent_data_ao_0[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_ao_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW6_OUT_AUX, 2 },
	{ P_SWEEP_CWK, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
	{ .hw = &gpww6_out_aux.hw },
	{ .index = DT_SWEEP_CWK, .name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW6_OUT_AUX, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
	{ .hw = &gpww6_out_aux.hw },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_XO, 0 },
	{ P_GPWW1_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww1_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_XO, 0 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .index = DT_DSI0_PHY_PWW_OUT_BYTECWK, .name = "dsi0pwwbyte" },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_XO, 0 },
	{ P_DSI0_PHY_PWW_OUT_BYTECWK, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .index = DT_DSI0_PHY_PWW_OUT_BYTECWK, .name = "dsi0pwwbyte" },
};

static const stwuct pawent_map gcc_pawent_map_7[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW3_OUT_MAIN, 2 },
	{ P_GPWW6_OUT_AUX, 3 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_7[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
	{ .hw = &gpww3_out_main.cwkw.hw },
	{ .hw = &gpww6_out_aux.hw },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_XO, 0 },
	{ P_HDMI_PHY_PWW_CWK, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .index = DT_HDMI_PHY_PWW_CWK, .name = "hdmi_pww" },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 2 },
	{ P_GPWW6_OUT_AUX, 3 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
	{ .index = DT_DSI0_PHY_PWW_OUT_DSICWK, .name = "dsi0pww" },
	{ .hw = &gpww6_out_aux.hw },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_XO, 0 },
	{ P_SWEEP_CWK, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .index = DT_SWEEP_CWK, .name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_XO, 0 },
	{ P_PCIE_0_PIPE_CWK, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .fw_name = "pcie_0_pipe_cwk", .name = "pcie_0_pipe_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_12[] = {
	{ P_XO, 0 },
	{ P_DSI0_PHY_PWW_OUT_DSICWK, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_12[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .index = DT_DSI0_PHY_PWW_OUT_DSICWK, .name = "dsi0pww" },
};

static const stwuct pawent_map gcc_pawent_map_13[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW4_OUT_MAIN, 2 },
	{ P_GPWW6_OUT_AUX, 3 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_13[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
	{ .hw = &gpww4_out_main.cwkw.hw },
	{ .hw = &gpww6_out_aux.hw },
};

static const stwuct pawent_map gcc_pawent_map_14[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_14[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_15[] = {
	{ P_XO, 0 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_15[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
};

static const stwuct pawent_map gcc_pawent_map_16[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_16[] = {
	{ .index = DT_XO, .name = "xo-boawd" },
	{ .hw = &gpww0_out_main.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_apss_ahb_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 apss_ahb_cwk_swc = {
	.cmd_wcgw = 0x46000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_apss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "apss_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_ao_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_ao_0),
		.fwags = CWK_IS_CWITICAW,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_qup0_i2c_apps_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup0_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x602c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup0_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_qup0_spi_apps_cwk_swc[] = {
	F(960000, P_XO, 10, 1, 2),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(16000000, P_GPWW0_OUT_MAIN, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup0_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x6034,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup0_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x200c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_qup1_spi_apps_cwk_swc[] = {
	F(960000,   P_XO, 10, 1, 2),
	F(4800000,  P_XO, 4, 0, 0),
	F(9600000,  P_XO, 2, 0, 0),
	F(10480000, P_GPWW0_OUT_MAIN, 1, 3, 229),
	F(16000000, P_GPWW0_OUT_MAIN, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(20961000, P_GPWW0_OUT_MAIN, 1, 6, 229),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x3000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_qup2_spi_apps_cwk_swc[] = {
	F(960000,   P_XO, 10, 1, 2),
	F(4800000,  P_XO, 4, 0, 0),
	F(9600000,  P_XO, 2, 0, 0),
	F(15000000, P_GPWW0_OUT_MAIN, 1,  3, 160),
	F(16000000, P_GPWW0_OUT_MAIN, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(30000000, P_GPWW0_OUT_MAIN, 1,  3, 80),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x3014,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup2_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup3_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x4000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup3_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x4024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup4_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x5000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup4_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup4_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x5024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup4_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_uawt0_apps_cwk_swc[] = {
	F(3686400, P_GPWW0_OUT_MAIN, 1, 72, 15625),
	F(7372800, P_GPWW0_OUT_MAIN, 1, 144, 15625),
	F(14745600, P_GPWW0_OUT_MAIN, 1, 288, 15625),
	F(16000000, P_GPWW0_OUT_MAIN, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPWW0_OUT_MAIN, 1, 3, 100),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(32000000, P_GPWW0_OUT_MAIN, 1, 1, 25),
	F(40000000, P_GPWW0_OUT_MAIN, 1, 1, 20),
	F(46400000, P_GPWW0_OUT_MAIN, 1, 29, 500),
	F(48000000, P_GPWW0_OUT_MAIN, 1, 3, 50),
	F(51200000, P_GPWW0_OUT_MAIN, 1, 8, 125),
	F(56000000, P_GPWW0_OUT_MAIN, 1, 7, 100),
	F(58982400, P_GPWW0_OUT_MAIN, 1, 1152, 15625),
	F(60000000, P_GPWW0_OUT_MAIN, 1, 3, 40),
	F(64000000, P_GPWW0_OUT_MAIN, 1, 2, 25),
	{ }
};

static stwuct cwk_wcg2 bwsp1_uawt0_apps_cwk_swc = {
	.cmd_wcgw = 0x600c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_uawt0_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt0_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x2044,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_uawt0_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x3034,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_uawt0_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt3_apps_cwk_swc = {
	.cmd_wcgw = 0x4014,
	.mnd_width = 16,
	.hid_width = 5,
	.cfg_off = 0x20,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_uawt0_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt3_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup0_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0xc00c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup0_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup0_spi_apps_cwk_swc = {
	.cmd_wcgw = 0xc024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_qup0_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup0_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt0_apps_cwk_swc = {
	.cmd_wcgw = 0xc044,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_bwsp1_uawt0_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt0_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 byte0_cwk_swc = {
	.cmd_wcgw = 0x4d044,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "byte0_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_byte2_ops,
	},
};

static const stwuct fweq_tbw ftbw_emac_cwk_swc[] = {
	F(5000000,   P_GPWW1_OUT_MAIN, 2, 1, 50),
	F(50000000,  P_GPWW1_OUT_MAIN, 10, 0, 0),
	F(125000000, P_GPWW1_OUT_MAIN, 4, 0, 0),
	F(250000000, P_GPWW1_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 emac_cwk_swc = {
	.cmd_wcgw = 0x4e01c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_emac_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "emac_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_emac_ptp_cwk_swc[] = {
	F(50000000,  P_GPWW1_OUT_MAIN, 10, 0, 0),
	F(125000000, P_GPWW1_OUT_MAIN, 4, 0, 0),
	F(250000000, P_GPWW1_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 emac_ptp_cwk_swc = {
	.cmd_wcgw = 0x4e014,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_emac_ptp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "emac_ptp_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_esc0_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 esc0_cwk_swc = {
	.cmd_wcgw = 0x4d05c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "esc0_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gfx3d_cwk_swc[] = {
	F(19200000,  P_XO, 1, 0, 0),
	F(50000000,  P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(80000000,  P_GPWW0_OUT_MAIN, 10, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(160000000, P_GPWW0_OUT_MAIN, 5, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(228571429, P_GPWW0_OUT_MAIN, 3.5, 0, 0),
	F(240000000, P_GPWW6_OUT_AUX,  4.5, 0, 0),
	F(266666667, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(270000000, P_GPWW6_OUT_AUX,  4, 0, 0),
	F(320000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	F(400000000, P_GPWW0_OUT_MAIN, 2, 0, 0),
	F(484800000, P_GPWW3_OUT_MAIN, 1, 0, 0),
	F(523200000, P_GPWW3_OUT_MAIN, 1, 0, 0),
	F(550000000, P_GPWW3_OUT_MAIN, 1, 0, 0),
	F(598000000, P_GPWW3_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gfx3d_cwk_swc = {
	.cmd_wcgw = 0x59000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gfx3d_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gfx3d_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gp1_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gp1_cwk_swc = {
	.cmd_wcgw = 0x8004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gp2_cwk_swc = {
	.cmd_wcgw = 0x9004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gp3_cwk_swc = {
	.cmd_wcgw = 0xa004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 hdmi_app_cwk_swc = {
	.cmd_wcgw = 0x4d0e4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_app_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 hdmi_pcwk_cwk_swc = {
	.cmd_wcgw = 0x4d0dc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pcwk_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_mdp_cwk_swc[] = {
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(80000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(145454545, P_GPWW0_OUT_MAIN, 5.5, 0, 0),
	F(160000000, P_GPWW0_OUT_MAIN, 5, 0, 0),
	F(177777778, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(266666667, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(320000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 mdp_cwk_swc = {
	.cmd_wcgw = 0x4d014,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "mdp_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_pcie_0_aux_cwk_swc[] = {
	F(1200000, P_XO, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 pcie_0_aux_cwk_swc = {
	.cmd_wcgw = 0x3e024,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_10,
	.fweq_tbw = ftbw_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pcie_0_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_10,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_pcie_0_pipe_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(125000000, P_PCIE_0_PIPE_CWK, 2, 0, 0),
	F(250000000, P_PCIE_0_PIPE_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 pcie_0_pipe_cwk_swc = {
	.cmd_wcgw = 0x3e01c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_11,
	.fweq_tbw = ftbw_pcie_0_pipe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pcie_0_pipe_cwk_swc",
		.pawent_data = gcc_pawent_data_11,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 pcwk0_cwk_swc = {
	.cmd_wcgw = 0x4d000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_12,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pcwk0_cwk_swc",
		.pawent_data = gcc_pawent_data_12,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_12),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_pixew_ops,
	},
};

static const stwuct fweq_tbw ftbw_pdm2_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(64000000, P_GPWW0_OUT_MAIN, 12.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 pdm2_cwk_swc = {
	.cmd_wcgw = 0x44010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_pdm2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pdm2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_sdcc1_apps_cwk_swc[] = {
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPWW0_OUT_MAIN, 10, 1, 4),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(177777778, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(192000000, P_GPWW4_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(384000000, P_GPWW4_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x42004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_13,
	.fweq_tbw = ftbw_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_13,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_13),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_sdcc1_ice_cowe_cwk_swc[] = {
	F(160000000, P_GPWW0_OUT_MAIN, 5, 0, 0),
	F(266666667, P_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc1_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x5d000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_sdcc1_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc1_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_sdcc2_apps_cwk_swc[] = {
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPWW0_OUT_MAIN, 10, 1, 4),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(177777778, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x43004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_14,
	.fweq_tbw = ftbw_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_14,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_14),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static stwuct cwk_wcg2 usb20_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x41048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb20_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_usb30_mastew_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(266666667, P_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb30_mastew_cwk_swc = {
	.cmd_wcgw = 0x39028,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_usb30_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb30_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 usb30_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x3901c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb30_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 usb3_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x3903c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb3_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_usb_hs_system_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(80000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(177777778, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb_hs_system_cwk_swc = {
	.cmd_wcgw = 0x41010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_usb_hs_system_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb_hs_system_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 vsync_cwk_swc = {
	.cmd_wcgw = 0x4d02c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_15,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "vsync_cwk_swc",
		.pawent_data = gcc_pawent_data_15,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_15),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cdsp_bimc_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(266666667, P_GPWW0_OUT_MAIN, 3, 0, 0),
	F(320000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cdsp_bimc_cwk_swc = {
	.cmd_wcgw = 0x5e010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_16,
	.fweq_tbw = ftbw_cdsp_bimc_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "cdsp_bimc_cwk_swc",
		.pawent_data = gcc_pawent_data_16,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_16),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_apss_ahb_cwk = {
	.hawt_weg = 0x4601c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_apss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&apss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_apss_tcu_cwk = {
	.hawt_weg = 0x5b004,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_apss_tcu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bimc_gfx_cwk = {
	.hawt_weg = 0x59034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bimc_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_apss_tcu_cwk.cwkw.hw,
			},

		},
	},
};

static stwuct cwk_bwanch gcc_bimc_gpu_cwk = {
	.hawt_weg = 0x59030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bimc_gpu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bimc_cdsp_cwk = {
	.hawt_weg = 0x31030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bimc_cdsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cdsp_bimc_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bimc_mdss_cwk = {
	.hawt_weg = 0x31038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bimc_mdss_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x1008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_dcc_cwk = {
	.hawt_weg = 0x77004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x77004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_dcc_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_dcc_xo_cwk = {
	.hawt_weg = 0x77008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x77008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_dcc_xo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup0_i2c_apps_cwk = {
	.hawt_weg = 0x6028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup0_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup0_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup0_spi_apps_cwk = {
	.hawt_weg = 0x6024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup0_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup0_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x2008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup1_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x2004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x3010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup2_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x300c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_i2c_apps_cwk = {
	.hawt_weg = 0x4020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup3_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_spi_apps_cwk = {
	.hawt_weg = 0x401c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x401c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup3_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_i2c_apps_cwk = {
	.hawt_weg = 0x5020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup4_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_spi_apps_cwk = {
	.hawt_weg = 0x501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup4_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt0_apps_cwk = {
	.hawt_weg = 0x6004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt0_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_uawt0_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x203c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_uawt1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt2_apps_cwk = {
	.hawt_weg = 0x302c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x302c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_uawt2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt3_apps_cwk = {
	.hawt_weg = 0x400c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x400c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt3_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_uawt3_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_ahb_cwk = {
	.hawt_weg = 0xb008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup0_i2c_apps_cwk = {
	.hawt_weg = 0xc008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup0_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp2_qup0_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup0_spi_apps_cwk = {
	.hawt_weg = 0xc004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup0_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp2_qup0_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt0_apps_cwk = {
	.hawt_weg = 0xc03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt0_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp2_uawt0_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x1300c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cwypto_ahb_cwk = {
	.hawt_weg = 0x16024,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cwypto_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cwypto_axi_cwk = {
	.hawt_weg = 0x16020,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cwypto_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cwypto_cwk = {
	.hawt_weg = 0x1601c,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cwypto_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_axi_cwk = {
	.hawt_weg = 0x4e010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_ptp_cwk = {
	.hawt_weg = 0x4e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_ptp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&emac_ptp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_wgmii_cwk = {
	.hawt_weg = 0x4e008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_wgmii_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&emac_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_swave_ahb_cwk = {
	.hawt_weg = 0x4e00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_swave_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_geni_iw_s_cwk = {
	.hawt_weg = 0xf008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_geni_iw_s_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_geni_iw_h_cwk = {
	.hawt_weg = 0xf004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_geni_iw_h_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gfx_tcu_cwk = {
	.hawt_weg = 0x12020,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500C,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gfx_tcu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gfx_tbu_cwk = {
	.hawt_weg = 0x12010,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500C,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gfx_tbu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cdsp_tbu_cwk = {
	.hawt_weg = 0x1203c,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x13020,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_cdsp_tbu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cdsp_bimc_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x8000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x9000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gp2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0xa000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gp3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gtcu_ahb_cwk = {
	.hawt_weg = 0x12044,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gtcu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdp_tbu_cwk = {
	.hawt_weg = 0x1201c,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdp_tbu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_ahb_cwk = {
	.hawt_weg = 0x4d07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_axi_cwk = {
	.hawt_weg = 0x4d080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_byte0_cwk = {
	.hawt_weg = 0x4d094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_byte0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_esc0_cwk = {
	.hawt_weg = 0x4d098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_esc0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&esc0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_hdmi_app_cwk = {
	.hawt_weg = 0x4d0d8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d0d8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_hdmi_app_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&hdmi_app_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_hdmi_pcwk_cwk = {
	.hawt_weg = 0x4d0d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d0d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_hdmi_pcwk_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&hdmi_pcwk_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_mdp_cwk = {
	.hawt_weg = 0x4d088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_mdp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_pcwk0_cwk = {
	.hawt_weg = 0x4d084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_pcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdss_vsync_cwk = {
	.hawt_weg = 0x4d090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mdss_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_oxiwi_ahb_cwk = {
	.hawt_weg = 0x59028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_oxiwi_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_oxiwi_gfx3d_cwk = {
	.hawt_weg = 0x59020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_oxiwi_gfx3d_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_aux_cwk = {
	.hawt_weg = 0x3e014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcie_0_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cfg_ahb_cwk = {
	.hawt_weg = 0x3e008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_mstw_axi_cwk = {
	.hawt_weg = 0x3e018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(18),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_pipe_cwk = {
	.hawt_weg = 0x3e00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcie_0_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_axi_cwk = {
	.hawt_weg = 0x3e010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(22),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcnoc_usb2_cwk = {
	.hawt_weg = 0x27008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x27008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcnoc_usb2_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcnoc_usb3_cwk = {
	.hawt_weg = 0x2700c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2700c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcnoc_usb3_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x4400c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4400c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pdm2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_ahb_cwk = {
	.hawt_weg = 0x44004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x44004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x13004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwng_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* PWM cwks do not have XO as pawent as swc cwk is a bawance woot */
static stwuct cwk_bwanch gcc_pwm0_xo512_cwk = {
	.hawt_weg = 0x44018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x44018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwm0_xo512_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwm1_xo512_cwk = {
	.hawt_weg = 0x49004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwm1_xo512_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwm2_xo512_cwk = {
	.hawt_weg = 0x4a004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwm2_xo512_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qdss_dap_cwk = {
	.hawt_weg = 0x29084,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qdss_dap_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x4201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x42018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&sdcc1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ice_cowe_cwk = {
	.hawt_weg = 0x5d014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5d014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&sdcc1_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cdsp_cfg_ahb_cwk = {
	.hawt_weg = 0x5e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_cdsp_cfg_ahb_cbcw",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x4301c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4301c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_apps_cwk = {
	.hawt_weg = 0x43018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x43018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_smmu_cfg_cwk = {
	.hawt_weg = 0x12038,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x3600C,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_smmu_cfg_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_usb3_cwk = {
	.hawt_weg = 0x26014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x26014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_usb3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_hs_inactivity_timews_cwk = {
	.hawt_weg = 0x4100C,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4100C,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_hs_inactivity_timews_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb20_mock_utmi_cwk = {
	.hawt_weg = 0x41044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x41044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb20_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb20_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb2a_phy_sweep_cwk = {
	.hawt_weg = 0x4102c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4102c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb2a_phy_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mastew_cwk = {
	.hawt_weg = 0x3900c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3900c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mock_utmi_cwk = {
	.hawt_weg = 0x39014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb30_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sweep_cwk = {
	.hawt_weg = 0x39010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_aux_cwk = {
	.hawt_weg = 0x39044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb3_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_pipe_cwk = {
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x39018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_hs_phy_cfg_ahb_cwk = {
	.hawt_weg = 0x41030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x41030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_hs_phy_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_hs_system_cwk = {
	.hawt_weg = 0x41004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x41004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_hs_system_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb_hs_system_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wdsp_q6ss_ahbs_cwk = {
	.hawt_weg = 0x1e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wdsp_q6ss_ahbs_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wdsp_q6ss_axim_cwk = {
	.hawt_weg = 0x1e008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wdsp_q6ss_axim_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc mdss_gdsc = {
	.gdscw = 0x4d078,
	.pd = {
		.name = "mdss",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc oxiwi_gdsc = {
	.gdscw = 0x5901c,
	.pd = {
		.name = "oxiwi",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_hw *gcc_qcs404_hws[] = {
	&cxo.hw,
};

static stwuct cwk_wegmap *gcc_qcs404_cwocks[] = {
	[GCC_APSS_AHB_CWK_SWC] = &apss_ahb_cwk_swc.cwkw,
	[GCC_BWSP1_QUP0_I2C_APPS_CWK_SWC] = &bwsp1_qup0_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP0_SPI_APPS_CWK_SWC] = &bwsp1_qup0_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK_SWC] = &bwsp1_qup1_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK_SWC] = &bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK_SWC] = &bwsp1_qup2_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK_SWC] = &bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK_SWC] = &bwsp1_qup3_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK_SWC] = &bwsp1_qup3_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK_SWC] = &bwsp1_qup4_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK_SWC] = &bwsp1_qup4_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT0_APPS_CWK_SWC] = &bwsp1_uawt0_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK_SWC] = &bwsp1_uawt1_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK_SWC] = &bwsp1_uawt2_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK_SWC] = &bwsp1_uawt3_apps_cwk_swc.cwkw,
	[GCC_BWSP2_QUP0_I2C_APPS_CWK_SWC] = &bwsp2_qup0_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP2_QUP0_SPI_APPS_CWK_SWC] = &bwsp2_qup0_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP2_UAWT0_APPS_CWK_SWC] = &bwsp2_uawt0_apps_cwk_swc.cwkw,
	[GCC_BYTE0_CWK_SWC] = &byte0_cwk_swc.cwkw,
	[GCC_EMAC_CWK_SWC] = &emac_cwk_swc.cwkw,
	[GCC_EMAC_PTP_CWK_SWC] = &emac_ptp_cwk_swc.cwkw,
	[GCC_ESC0_CWK_SWC] = &esc0_cwk_swc.cwkw,
	[GCC_APSS_AHB_CWK] = &gcc_apss_ahb_cwk.cwkw,
	[GCC_BIMC_GFX_CWK] = &gcc_bimc_gfx_cwk.cwkw,
	[GCC_BIMC_CDSP_CWK] = &gcc_bimc_cdsp_cwk.cwkw,
	[GCC_BIMC_MDSS_CWK] = &gcc_bimc_mdss_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_QUP0_I2C_APPS_CWK] = &gcc_bwsp1_qup0_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP0_SPI_APPS_CWK] = &gcc_bwsp1_qup0_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK] = &gcc_bwsp1_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK] = &gcc_bwsp1_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK] = &gcc_bwsp1_qup4_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK] = &gcc_bwsp1_qup4_spi_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT0_APPS_CWK] = &gcc_bwsp1_uawt0_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK] = &gcc_bwsp1_uawt3_apps_cwk.cwkw,
	[GCC_BWSP2_AHB_CWK] = &gcc_bwsp2_ahb_cwk.cwkw,
	[GCC_BWSP2_QUP0_I2C_APPS_CWK] = &gcc_bwsp2_qup0_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_QUP0_SPI_APPS_CWK] = &gcc_bwsp2_qup0_spi_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT0_APPS_CWK] = &gcc_bwsp2_uawt0_apps_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_ETH_AXI_CWK] = &gcc_eth_axi_cwk.cwkw,
	[GCC_ETH_PTP_CWK] = &gcc_eth_ptp_cwk.cwkw,
	[GCC_ETH_WGMII_CWK] = &gcc_eth_wgmii_cwk.cwkw,
	[GCC_ETH_SWAVE_AHB_CWK] = &gcc_eth_swave_ahb_cwk.cwkw,
	[GCC_GENI_IW_S_CWK] = &gcc_geni_iw_s_cwk.cwkw,
	[GCC_GENI_IW_H_CWK] = &gcc_geni_iw_h_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_MDSS_AHB_CWK] = &gcc_mdss_ahb_cwk.cwkw,
	[GCC_MDSS_AXI_CWK] = &gcc_mdss_axi_cwk.cwkw,
	[GCC_MDSS_BYTE0_CWK] = &gcc_mdss_byte0_cwk.cwkw,
	[GCC_MDSS_ESC0_CWK] = &gcc_mdss_esc0_cwk.cwkw,
	[GCC_MDSS_HDMI_APP_CWK] = &gcc_mdss_hdmi_app_cwk.cwkw,
	[GCC_MDSS_HDMI_PCWK_CWK] = &gcc_mdss_hdmi_pcwk_cwk.cwkw,
	[GCC_MDSS_MDP_CWK] = &gcc_mdss_mdp_cwk.cwkw,
	[GCC_MDSS_PCWK0_CWK] = &gcc_mdss_pcwk0_cwk.cwkw,
	[GCC_MDSS_VSYNC_CWK] = &gcc_mdss_vsync_cwk.cwkw,
	[GCC_OXIWI_AHB_CWK] = &gcc_oxiwi_ahb_cwk.cwkw,
	[GCC_OXIWI_GFX3D_CWK] = &gcc_oxiwi_gfx3d_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK] = &gcc_pcie_0_aux_cwk.cwkw,
	[GCC_PCIE_0_CFG_AHB_CWK] = &gcc_pcie_0_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_0_MSTW_AXI_CWK] = &gcc_pcie_0_mstw_axi_cwk.cwkw,
	[GCC_PCIE_0_PIPE_CWK] = &gcc_pcie_0_pipe_cwk.cwkw,
	[GCC_PCIE_0_SWV_AXI_CWK] = &gcc_pcie_0_swv_axi_cwk.cwkw,
	[GCC_PCNOC_USB2_CWK] = &gcc_pcnoc_usb2_cwk.cwkw,
	[GCC_PCNOC_USB3_CWK] = &gcc_pcnoc_usb3_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_PWM0_XO512_CWK] = &gcc_pwm0_xo512_cwk.cwkw,
	[GCC_PWM1_XO512_CWK] = &gcc_pwm1_xo512_cwk.cwkw,
	[GCC_PWM2_XO512_CWK] = &gcc_pwm2_xo512_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK] = &gcc_sdcc1_ice_cowe_cwk.cwkw,
	[GCC_CDSP_CFG_AHB_CWK] = &gcc_cdsp_cfg_ahb_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SYS_NOC_USB3_CWK] = &gcc_sys_noc_usb3_cwk.cwkw,
	[GCC_USB20_MOCK_UTMI_CWK] = &gcc_usb20_mock_utmi_cwk.cwkw,
	[GCC_USB2A_PHY_SWEEP_CWK] = &gcc_usb2a_phy_sweep_cwk.cwkw,
	[GCC_USB30_MASTEW_CWK] = &gcc_usb30_mastew_cwk.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK] = &gcc_usb30_mock_utmi_cwk.cwkw,
	[GCC_USB30_SWEEP_CWK] = &gcc_usb30_sweep_cwk.cwkw,
	[GCC_USB3_PHY_AUX_CWK] = &gcc_usb3_phy_aux_cwk.cwkw,
	[GCC_USB3_PHY_PIPE_CWK] = &gcc_usb3_phy_pipe_cwk.cwkw,
	[GCC_USB_HS_PHY_CFG_AHB_CWK] = &gcc_usb_hs_phy_cfg_ahb_cwk.cwkw,
	[GCC_USB_HS_SYSTEM_CWK] = &gcc_usb_hs_system_cwk.cwkw,
	[GCC_GFX3D_CWK_SWC] = &gfx3d_cwk_swc.cwkw,
	[GCC_GP1_CWK_SWC] = &gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK_SWC] = &gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK_SWC] = &gp3_cwk_swc.cwkw,
	[GCC_GPWW0_OUT_MAIN] = &gpww0_out_main.cwkw,
	[GCC_GPWW0_AO_OUT_MAIN] = &gpww0_ao_out_main.cwkw,
	[GCC_GPWW0_SWEEP_CWK_SWC] = &gpww0_sweep_cwk_swc.cwkw,
	[GCC_GPWW1_OUT_MAIN] = &gpww1_out_main.cwkw,
	[GCC_GPWW3_OUT_MAIN] = &gpww3_out_main.cwkw,
	[GCC_GPWW4_OUT_MAIN] = &gpww4_out_main.cwkw,
	[GCC_GPWW6] = &gpww6.cwkw,
	[GCC_GPWW6_OUT_AUX] = &gpww6_out_aux,
	[GCC_HDMI_APP_CWK_SWC] = &hdmi_app_cwk_swc.cwkw,
	[GCC_HDMI_PCWK_CWK_SWC] = &hdmi_pcwk_cwk_swc.cwkw,
	[GCC_MDP_CWK_SWC] = &mdp_cwk_swc.cwkw,
	[GCC_PCIE_0_AUX_CWK_SWC] = &pcie_0_aux_cwk_swc.cwkw,
	[GCC_PCIE_0_PIPE_CWK_SWC] = &pcie_0_pipe_cwk_swc.cwkw,
	[GCC_PCWK0_CWK_SWC] = &pcwk0_cwk_swc.cwkw,
	[GCC_PDM2_CWK_SWC] = &pdm2_cwk_swc.cwkw,
	[GCC_SDCC1_APPS_CWK_SWC] = &sdcc1_apps_cwk_swc.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK_SWC] = &sdcc1_ice_cowe_cwk_swc.cwkw,
	[GCC_SDCC2_APPS_CWK_SWC] = &sdcc2_apps_cwk_swc.cwkw,
	[GCC_USB20_MOCK_UTMI_CWK_SWC] = &usb20_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_MASTEW_CWK_SWC] = &usb30_mastew_cwk_swc.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK_SWC] = &usb30_mock_utmi_cwk_swc.cwkw,
	[GCC_USB3_PHY_AUX_CWK_SWC] = &usb3_phy_aux_cwk_swc.cwkw,
	[GCC_USB_HS_SYSTEM_CWK_SWC] = &usb_hs_system_cwk_swc.cwkw,
	[GCC_VSYNC_CWK_SWC] = &vsync_cwk_swc.cwkw,
	[GCC_CDSP_BIMC_CWK_SWC] = &cdsp_bimc_cwk_swc.cwkw,
	[GCC_USB_HS_INACTIVITY_TIMEWS_CWK] =
			&gcc_usb_hs_inactivity_timews_cwk.cwkw,
	[GCC_BIMC_GPU_CWK] = &gcc_bimc_gpu_cwk.cwkw,
	[GCC_GTCU_AHB_CWK] = &gcc_gtcu_ahb_cwk.cwkw,
	[GCC_GFX_TCU_CWK] = &gcc_gfx_tcu_cwk.cwkw,
	[GCC_GFX_TBU_CWK] = &gcc_gfx_tbu_cwk.cwkw,
	[GCC_SMMU_CFG_CWK] = &gcc_smmu_cfg_cwk.cwkw,
	[GCC_APSS_TCU_CWK] = &gcc_apss_tcu_cwk.cwkw,
	[GCC_CDSP_TBU_CWK] = &gcc_cdsp_tbu_cwk.cwkw,
	[GCC_CWYPTO_AHB_CWK] = &gcc_cwypto_ahb_cwk.cwkw,
	[GCC_CWYPTO_AXI_CWK] = &gcc_cwypto_axi_cwk.cwkw,
	[GCC_CWYPTO_CWK] = &gcc_cwypto_cwk.cwkw,
	[GCC_MDP_TBU_CWK] = &gcc_mdp_tbu_cwk.cwkw,
	[GCC_QDSS_DAP_CWK] = &gcc_qdss_dap_cwk.cwkw,
	[GCC_DCC_CWK] = &gcc_dcc_cwk.cwkw,
	[GCC_DCC_XO_CWK] = &gcc_dcc_xo_cwk.cwkw,
	[GCC_WCSS_Q6_AHB_CWK] = &gcc_wdsp_q6ss_ahbs_cwk.cwkw,
	[GCC_WCSS_Q6_AXIM_CWK] =  &gcc_wdsp_q6ss_axim_cwk.cwkw,

};

static stwuct gdsc *gcc_qcs404_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
	[OXIWI_GDSC] = &oxiwi_gdsc,
};

static const stwuct qcom_weset_map gcc_qcs404_wesets[] = {
	[GCC_GENI_IW_BCW] = { 0x0F000 },
	[GCC_CDSP_WESTAWT] = { 0x18000 },
	[GCC_USB_HS_BCW] = { 0x41000 },
	[GCC_USB2_HS_PHY_ONWY_BCW] = { 0x41034 },
	[GCC_QUSB2_PHY_BCW] = { 0x4103c },
	[GCC_USB_HS_PHY_CFG_AHB_BCW] = { 0x0000c, 1 },
	[GCC_USB2A_PHY_BCW] = { 0x0000c, 0 },
	[GCC_USB3_PHY_BCW] = { 0x39004 },
	[GCC_USB_30_BCW] = { 0x39000 },
	[GCC_USB3PHY_PHY_BCW] = { 0x39008 },
	[GCC_PCIE_0_BCW] = { 0x3e000 },
	[GCC_PCIE_0_PHY_BCW] = { 0x3e004 },
	[GCC_PCIE_0_WINK_DOWN_BCW] = { 0x3e038 },
	[GCC_PCIEPHY_0_PHY_BCW] = { 0x3e03c },
	[GCC_PCIE_0_AXI_MASTEW_STICKY_AWES] = { 0x3e040, 6},
	[GCC_PCIE_0_AHB_AWES] = { 0x3e040, 5 },
	[GCC_PCIE_0_AXI_SWAVE_AWES] = { 0x3e040, 4 },
	[GCC_PCIE_0_AXI_MASTEW_AWES] = { 0x3e040, 3 },
	[GCC_PCIE_0_COWE_STICKY_AWES] = { 0x3e040, 2 },
	[GCC_PCIE_0_SWEEP_AWES] = { 0x3e040, 1 },
	[GCC_PCIE_0_PIPE_AWES] = { 0x3e040, 0 },
	[GCC_EMAC_BCW] = { 0x4e000 },
	[GCC_WDSP_WESTAWT] = {0x19000},
};

static const stwuct wegmap_config gcc_qcs404_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x7f000,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_qcs404_desc = {
	.config = &gcc_qcs404_wegmap_config,
	.cwks = gcc_qcs404_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_qcs404_cwocks),
	.wesets = gcc_qcs404_wesets,
	.num_wesets = AWWAY_SIZE(gcc_qcs404_wesets),
	.cwk_hws = gcc_qcs404_hws,
	.num_cwk_hws = AWWAY_SIZE(gcc_qcs404_hws),
	.gdscs = gcc_qcs404_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_qcs404_gdscs),
};

static const stwuct of_device_id gcc_qcs404_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-qcs404" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_qcs404_match_tabwe);

static int gcc_qcs404_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gcc_qcs404_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_awpha_pww_configuwe(&gpww3_out_main, wegmap, &gpww3_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_qcs404_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_qcs404_dwivew = {
	.pwobe = gcc_qcs404_pwobe,
	.dwivew = {
		.name = "gcc-qcs404",
		.of_match_tabwe = gcc_qcs404_match_tabwe,
	},
};

static int __init gcc_qcs404_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_qcs404_dwivew);
}
cowe_initcaww(gcc_qcs404_init);

static void __exit gcc_qcs404_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_qcs404_dwivew);
}
moduwe_exit(gcc_qcs404_exit);

MODUWE_DESCWIPTION("Quawcomm GCC QCS404 Dwivew");
MODUWE_WICENSE("GPW v2");
