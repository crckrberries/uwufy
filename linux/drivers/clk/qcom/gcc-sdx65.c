// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gcc-sdx65.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_EVEN,
	P_GPWW0_OUT_MAIN,
	P_PCIE_PIPE_CWK,
	P_SWEEP_CWK,
	P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK,
};

static stwuct cwk_awpha_pww gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x6d000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw *[]){ &gpww0.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0_ao[] = {
	{ .fw_name = "bi_tcxo_ao" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_SWEEP_CWK, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk" },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 2 },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_PCIE_PIPE_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .fw_name = "pcie_pipe_cwk"},
	{ .fw_name = "bi_tcxo"},
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .fw_name = "usb3_phy_wwappew_gcc_usb30_pipe_cwk"},
	{ .fw_name = "bi_tcxo"},
};

static stwuct cwk_wegmap_mux gcc_pcie_aux_cwk_swc = {
	.weg = 0x43060,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_4,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_aux_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_pcie_pipe_cwk_swc = {
	.weg = 0x43044,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_5,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_pipe_cwk_swc",
			.pawent_data = gcc_pawent_data_5,
			.num_pawents = 2,
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_usb3_phy_pipe_cwk_swc = {
	.weg = 0x1706c,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_6,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_pipe_cwk_swc",
			.pawent_data = gcc_pawent_data_6,
			.num_pawents = 2,
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_bwsp1_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x1c024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc[] = {
	F(960000, P_BI_TCXO, 10, 1, 2),
	F(4800000, P_BI_TCXO, 4, 0, 0),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(15000000, P_GPWW0_OUT_EVEN, 5, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_GPWW0_OUT_MAIN, 12.5, 1, 2),
	F(25000000, P_GPWW0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GPWW0_OUT_MAIN, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_bwsp1_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1c00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x1e024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1e00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup3_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x20024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup3_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2000c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup4_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x22024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup4_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup4_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2200c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup4_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_uawt1_apps_cwk_swc[] = {
	F(3686400, P_GPWW0_OUT_EVEN, 1, 192, 15625),
	F(7372800, P_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(14745600, P_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(16000000, P_GPWW0_OUT_EVEN, 1, 4, 75),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(19354839, P_GPWW0_OUT_MAIN, 15.5, 1, 2),
	F(20000000, P_GPWW0_OUT_MAIN, 15, 1, 2),
	F(20689655, P_GPWW0_OUT_MAIN, 14.5, 1, 2),
	F(21428571, P_GPWW0_OUT_MAIN, 14, 1, 2),
	F(22222222, P_GPWW0_OUT_MAIN, 13.5, 1, 2),
	F(23076923, P_GPWW0_OUT_MAIN, 13, 1, 2),
	F(24000000, P_GPWW0_OUT_MAIN, 5, 1, 5),
	F(25000000, P_GPWW0_OUT_MAIN, 12, 1, 2),
	F(26086957, P_GPWW0_OUT_MAIN, 11.5, 1, 2),
	F(27272727, P_GPWW0_OUT_MAIN, 11, 1, 2),
	F(28571429, P_GPWW0_OUT_MAIN, 10.5, 1, 2),
	F(32000000, P_GPWW0_OUT_MAIN, 1, 4, 75),
	F(40000000, P_GPWW0_OUT_MAIN, 15, 0, 0),
	F(46400000, P_GPWW0_OUT_MAIN, 1, 29, 375),
	F(48000000, P_GPWW0_OUT_MAIN, 12.5, 0, 0),
	F(51200000, P_GPWW0_OUT_MAIN, 1, 32, 375),
	F(56000000, P_GPWW0_OUT_MAIN, 1, 7, 75),
	F(58982400, P_GPWW0_OUT_MAIN, 1, 1536, 15625),
	F(60000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
	F(63157895, P_GPWW0_OUT_MAIN, 9.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x1d00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x1f00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt3_apps_cwk_swc = {
	.cmd_wcgw = 0x2100c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt3_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt4_apps_cwk_swc = {
	.cmd_wcgw = 0x2300c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt4_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_cpuss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_cpuss_ahb_cwk_swc = {
	.cmd_wcgw = 0x3000c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_cpuss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_0_ao,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x37004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x38004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x39004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_aux_phy_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_aux_phy_cwk_swc = {
	.cmd_wcgw = 0x43048,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_pcie_aux_phy_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_aux_phy_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_wchng_phy_cwk_swc[] = {
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_wchng_phy_cwk_swc = {
	.cmd_wcgw = 0x43064,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_wchng_phy_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_wchng_phy_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pdm2_cwk_swc = {
	.cmd_wcgw = 0x24010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pdm2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pdm2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x1a010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_mastew_cwk_swc[] = {
	F(200000000, P_GPWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_mastew_cwk_swc = {
	.cmd_wcgw = 0x17030,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb30_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x17048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_aux_phy_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = 3,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb3_phy_aux_cwk_swc[] = {
	F(1000000, P_BI_TCXO, 1, 5, 96),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb3_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x17070,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_usb3_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div gcc_cpuss_ahb_postdiv_cwk_swc = {
	.weg = 0x30024,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_cpuss_ahb_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_cpuss_ahb_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div gcc_usb30_mock_utmi_postdiv_cwk_swc = {
	.weg = 0x17060,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_usb30_mock_utmi_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_usb30_mock_utmi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch gcc_ahb_pcie_wink_cwk = {
	.hawt_weg = 0x2e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ahb_pcie_wink_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x1b004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x1c008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1c008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup1_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x1c004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x1e008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup2_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x1e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_i2c_apps_cwk = {
	.hawt_weg = 0x20008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x20008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup3_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_spi_apps_cwk = {
	.hawt_weg = 0x20004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x20004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup3_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_i2c_apps_cwk = {
	.hawt_weg = 0x22008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x22008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup4_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_spi_apps_cwk = {
	.hawt_weg = 0x22004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x22004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup4_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_sweep_cwk = {
	.hawt_weg = 0x1b00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x1d004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1d004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_uawt1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt2_apps_cwk = {
	.hawt_weg = 0x1f004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1f004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_uawt2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt3_apps_cwk = {
	.hawt_weg = 0x21004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x21004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt3_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_uawt3_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt4_apps_cwk = {
	.hawt_weg = 0x23004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x23004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_uawt4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x27004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x27004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x37000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x37000,
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
	.hawt_weg = 0x38000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x38000,
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
	.hawt_weg = 0x39000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39000,
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

static stwuct cwk_bwanch gcc_pcie_0_cwkwef_en = {
	.hawt_weg = 0x88004,
	/*
	 * The cwock contwowwew does not handwe the status bit fow
	 * the cwocks with gdscs(powewdomains) in hw contwowwed mode
	 * and hence avoid checking fow the status bit of those cwocks
	 * by setting the BWANCH_HAWT_DEWAY fwag
	 */
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x88004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_aux_cwk = {
	.hawt_weg = 0x43034,
	/*
	 * The cwock contwowwew does not handwe the status bit fow
	 * the cwocks with gdscs(powewdomains) in hw contwowwed mode
	 * and hence avoid checking fow the status bit of those cwocks
	 * by setting the BWANCH_HAWT_DEWAY fwag
	 */
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x43034,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_cfg_ahb_cwk = {
	.hawt_weg = 0x4302c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x4302c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_mstw_axi_cwk = {
	.hawt_weg = 0x43024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x43024,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_pipe_cwk = {
	.hawt_weg = 0x4303c,
	/*
	 * The cwock contwowwew does not handwe the status bit fow
	 * the cwocks with gdscs(powewdomains) in hw contwowwed mode
	 * and hence avoid checking fow the status bit of those cwocks
	 * by setting the BWANCH_HAWT_DEWAY fwag
	 */
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x4303c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_wchng_phy_cwk = {
	.hawt_weg = 0x43030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x43030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_wchng_phy_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_wchng_phy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_sweep_cwk = {
	.hawt_weg = 0x43038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x43038,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_aux_phy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_swv_axi_cwk = {
	.hawt_weg = 0x4301c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x4301c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_swv_q2a_axi_cwk = {
	.hawt_weg = 0x43018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x43018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_swv_q2a_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x2400c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2400c,
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
	.hawt_weg = 0x24004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x24004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x24004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_xo4_cwk = {
	.hawt_weg = 0x24008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x24008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_xo4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wx1_usb2_cwkwef_en = {
	.hawt_weg = 0x88008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x88008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wx1_usb2_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x1a00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x1a004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a004,
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

static stwuct cwk_bwanch gcc_usb30_mastew_cwk = {
	.hawt_weg = 0x17018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mock_utmi_cwk = {
	.hawt_weg = 0x1702c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1702c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_mock_utmi_postdiv_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mstw_axi_cwk = {
	.hawt_weg = 0x17020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sweep_cwk = {
	.hawt_weg = 0x17028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_swv_ahb_cwk = {
	.hawt_weg = 0x17024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_swv_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_aux_cwk = {
	.hawt_weg = 0x17064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb3_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc usb30_gdsc = {
	.gdscw = 0x17004,
	.pd = {
		.name = "usb30_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc pcie_gdsc = {
	.gdscw = 0x43004,
	.pd = {
		.name = "pcie_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_bwanch gcc_usb3_phy_pipe_cwk = {
	.hawt_weg = 0x17068,
	/*
	 * The cwock contwowwew does not handwe the status bit fow
	 * the cwocks with gdscs(powewdomains) in hw contwowwed mode
	 * and hence avoid checking fow the status bit of those cwocks
	 * by setting the BWANCH_HAWT_DEWAY fwag
	 */
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x17068,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x17068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb3_phy_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_cwkwef_en = {
	.hawt_weg = 0x88000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x88000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_phy_cfg_ahb2phy_cwk = {
	.hawt_weg = 0x19008,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x19008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x19008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_phy_cfg_ahb2phy_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_xo_div4_cwk = {
	.hawt_weg = 0x2e010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_xo_div4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_xo_pcie_wink_cwk = {
	.hawt_weg = 0x2e008,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x2e008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x2e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_xo_pcie_wink_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap *gcc_sdx65_cwocks[] = {
	[GCC_AHB_PCIE_WINK_CWK] = &gcc_ahb_pcie_wink_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK_SWC] = &gcc_bwsp1_qup1_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK_SWC] = &gcc_bwsp1_qup2_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK] = &gcc_bwsp1_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK_SWC] = &gcc_bwsp1_qup3_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK] = &gcc_bwsp1_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup3_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK] = &gcc_bwsp1_qup4_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK_SWC] = &gcc_bwsp1_qup4_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK] = &gcc_bwsp1_qup4_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup4_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_SWEEP_CWK] = &gcc_bwsp1_sweep_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK_SWC] = &gcc_bwsp1_uawt1_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK_SWC] = &gcc_bwsp1_uawt2_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK] = &gcc_bwsp1_uawt3_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK_SWC] = &gcc_bwsp1_uawt3_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT4_APPS_CWK] = &gcc_bwsp1_uawt4_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT4_APPS_CWK_SWC] = &gcc_bwsp1_uawt4_apps_cwk_swc.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK_SWC] = &gcc_cpuss_ahb_cwk_swc.cwkw,
	[GCC_CPUSS_AHB_POSTDIV_CWK_SWC] = &gcc_cpuss_ahb_postdiv_cwk_swc.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_PCIE_0_CWKWEF_EN] = &gcc_pcie_0_cwkwef_en.cwkw,
	[GCC_PCIE_AUX_CWK] = &gcc_pcie_aux_cwk.cwkw,
	[GCC_PCIE_AUX_CWK_SWC] = &gcc_pcie_aux_cwk_swc.cwkw,
	[GCC_PCIE_AUX_PHY_CWK_SWC] = &gcc_pcie_aux_phy_cwk_swc.cwkw,
	[GCC_PCIE_CFG_AHB_CWK] = &gcc_pcie_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_MSTW_AXI_CWK] = &gcc_pcie_mstw_axi_cwk.cwkw,
	[GCC_PCIE_PIPE_CWK] = &gcc_pcie_pipe_cwk.cwkw,
	[GCC_PCIE_PIPE_CWK_SWC] = &gcc_pcie_pipe_cwk_swc.cwkw,
	[GCC_PCIE_WCHNG_PHY_CWK] = &gcc_pcie_wchng_phy_cwk.cwkw,
	[GCC_PCIE_WCHNG_PHY_CWK_SWC] = &gcc_pcie_wchng_phy_cwk_swc.cwkw,
	[GCC_PCIE_SWEEP_CWK] = &gcc_pcie_sweep_cwk.cwkw,
	[GCC_PCIE_SWV_AXI_CWK] = &gcc_pcie_swv_axi_cwk.cwkw,
	[GCC_PCIE_SWV_Q2A_AXI_CWK] = &gcc_pcie_swv_q2a_axi_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_WX1_USB2_CWKWEF_EN] = &gcc_wx1_usb2_cwkwef_en.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK_SWC] = &gcc_sdcc1_apps_cwk_swc.cwkw,
	[GCC_USB30_MASTEW_CWK] = &gcc_usb30_mastew_cwk.cwkw,
	[GCC_USB30_MASTEW_CWK_SWC] = &gcc_usb30_mastew_cwk_swc.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK] = &gcc_usb30_mock_utmi_cwk.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK_SWC] = &gcc_usb30_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_MOCK_UTMI_POSTDIV_CWK_SWC] =	&gcc_usb30_mock_utmi_postdiv_cwk_swc.cwkw,
	[GCC_USB30_MSTW_AXI_CWK] = &gcc_usb30_mstw_axi_cwk.cwkw,
	[GCC_USB30_SWEEP_CWK] = &gcc_usb30_sweep_cwk.cwkw,
	[GCC_USB30_SWV_AHB_CWK] = &gcc_usb30_swv_ahb_cwk.cwkw,
	[GCC_USB3_PHY_AUX_CWK] = &gcc_usb3_phy_aux_cwk.cwkw,
	[GCC_USB3_PHY_AUX_CWK_SWC] = &gcc_usb3_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PHY_PIPE_CWK] = &gcc_usb3_phy_pipe_cwk.cwkw,
	[GCC_USB3_PHY_PIPE_CWK_SWC] = &gcc_usb3_phy_pipe_cwk_swc.cwkw,
	[GCC_USB3_PWIM_CWKWEF_EN] = &gcc_usb3_pwim_cwkwef_en.cwkw,
	[GCC_USB_PHY_CFG_AHB2PHY_CWK] = &gcc_usb_phy_cfg_ahb2phy_cwk.cwkw,
	[GCC_XO_DIV4_CWK] = &gcc_xo_div4_cwk.cwkw,
	[GCC_XO_PCIE_WINK_CWK] = &gcc_xo_pcie_wink_cwk.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW0_OUT_EVEN] = &gpww0_out_even.cwkw,
};

static const stwuct qcom_weset_map gcc_sdx65_wesets[] = {
	[GCC_BWSP1_QUP1_BCW] = { 0x1c000 },
	[GCC_BWSP1_QUP2_BCW] = { 0x1e000 },
	[GCC_BWSP1_QUP3_BCW] = { 0x20000 },
	[GCC_BWSP1_QUP4_BCW] = { 0x22000 },
	[GCC_BWSP1_UAWT1_BCW] = { 0x1d000 },
	[GCC_BWSP1_UAWT2_BCW] = { 0x1f000 },
	[GCC_BWSP1_UAWT3_BCW] = { 0x21000 },
	[GCC_BWSP1_UAWT4_BCW] = { 0x23000 },
	[GCC_PCIE_BCW] = { 0x43000 },
	[GCC_PCIE_WINK_DOWN_BCW] = { 0x77000 },
	[GCC_PCIE_NOCSW_COM_PHY_BCW] = { 0x78008 },
	[GCC_PCIE_PHY_BCW] = { 0x44000 },
	[GCC_PCIE_PHY_CFG_AHB_BCW] = { 0x78000 },
	[GCC_PCIE_PHY_COM_BCW] = { 0x78004 },
	[GCC_PCIE_PHY_NOCSW_COM_PHY_BCW] = { 0x7800c },
	[GCC_PDM_BCW] = { 0x24000 },
	[GCC_QUSB2PHY_BCW] = { 0x19000 },
	[GCC_SDCC1_BCW] = { 0x1a000 },
	[GCC_TCSW_PCIE_BCW] = { 0x57000 },
	[GCC_USB30_BCW] = { 0x17000 },
	[GCC_USB3_PHY_BCW] = { 0x18000 },
	[GCC_USB3PHY_PHY_BCW] = { 0x18004 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x19004 },
};

static stwuct gdsc *gcc_sdx65_gdscs[] = {
	[USB30_GDSC] = &usb30_gdsc,
	[PCIE_GDSC] = &pcie_gdsc,
};

static const stwuct wegmap_config gcc_sdx65_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x1f101c,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_sdx65_desc = {
	.config = &gcc_sdx65_wegmap_config,
	.cwks = gcc_sdx65_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sdx65_cwocks),
	.wesets = gcc_sdx65_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sdx65_wesets),
	.gdscs = gcc_sdx65_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sdx65_gdscs),
};

static const stwuct of_device_id gcc_sdx65_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-sdx65" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sdx65_match_tabwe);

static int gcc_sdx65_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gcc_sdx65_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);
	/*
	 * Keep the cwocks awways-ON as they awe cwiticaw to the functioning
	 * of the system:
	 * GCC_SYS_NOC_CPUSS_AHB_CWK, GCC_CPUSS_AHB_CWK, GCC_CPUSS_GNOC_CWK
	 */
	wegmap_update_bits(wegmap, 0x6d008, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x6d008, BIT(21), BIT(21));
	wegmap_update_bits(wegmap, 0x6d008, BIT(22), BIT(22));

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sdx65_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sdx65_dwivew = {
	.pwobe = gcc_sdx65_pwobe,
	.dwivew = {
		.name = "gcc-sdx65",
		.of_match_tabwe = gcc_sdx65_match_tabwe,
	},
};

static int __init gcc_sdx65_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sdx65_dwivew);
}
subsys_initcaww(gcc_sdx65_init);

static void __exit gcc_sdx65_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sdx65_dwivew);
}
moduwe_exit(gcc_sdx65_exit);

MODUWE_DESCWIPTION("QTI GCC SDX65 Dwivew");
MODUWE_WICENSE("GPW v2");
