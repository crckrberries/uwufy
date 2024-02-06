// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2020, Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gcc-sdx55.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_EVEN,
	P_GPWW0_OUT_MAIN,
	P_GPWW4_OUT_EVEN,
	P_GPWW5_OUT_MAIN,
	P_SWEEP_CWK,
};

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct cwk_awpha_pww gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.cwkw = {
		.enabwe_weg = 0x6d000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_wucid_even[] = {
	{ 0x0, 1 },
	{ 0x1, 2 },
	{ 0x3, 4 },
	{ 0x7, 8 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpww0_out_even = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_wucid_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_wucid_even),
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct cwk_awpha_pww gpww4 = {
	.offset = 0x76000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.cwkw = {
		.enabwe_weg = 0x6d000,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gpww4_out_even = {
	.offset = 0x76000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_wucid_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_wucid_even),
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww4_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww4.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct cwk_awpha_pww gpww5 = {
	.offset = 0x74000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.cwkw = {
		.enabwe_weg = 0x6d000,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww5",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_ops,
		},
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawents_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct cwk_pawent_data gcc_pawents_0_ao[] = {
	{ .fw_name = "bi_tcxo_ao" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW4_OUT_EVEN, 2 },
	{ P_GPWW5_OUT_MAIN, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawents_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4_out_even.cwkw.hw },
	{ .hw = &gpww5.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_SWEEP_CWK, 5 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawents_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawents_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW4_OUT_EVEN, 2 },
	{ P_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawents_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4_out_even.cwkw.hw },
	{ .hw = &gpww0_out_even.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_bwsp1_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x11024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
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
	.cmd_wcgw = 0x1100c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x13024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1300c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup3_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x15024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup3_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1500c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup4_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x17024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup4_i2c_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup4_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1700c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_qup4_spi_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
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
	.cmd_wcgw = 0x1200c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x1400c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt3_apps_cwk_swc = {
	.cmd_wcgw = 0x1600c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt3_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt4_apps_cwk_swc = {
	.cmd_wcgw = 0x1800c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_bwsp1_uawt4_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
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
	.cmd_wcgw = 0x24010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_cpuss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_ahb_cwk_swc",
		.pawent_data = gcc_pawents_0_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_cpuss_wbcpw_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_cpuss_wbcpw_cwk_swc = {
	.cmd_wcgw = 0x2402c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_cpuss_wbcpw_cwk_swc",
		.pawent_data = gcc_pawents_0_ao,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0_ao),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_emac_cwk_swc[] = {
	F(2500000, P_BI_TCXO, 1, 25, 192),
	F(5000000, P_BI_TCXO, 1, 25, 96),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(250000000, P_GPWW4_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_emac_cwk_swc = {
	.cmd_wcgw = 0x47020,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_emac_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_emac_cwk_swc",
		.pawent_data = gcc_pawents_5,
		.num_pawents = AWWAY_SIZE(gcc_pawents_5),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_emac_ptp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_EVEN, 6, 0, 0),
	F(230400000, P_GPWW5_OUT_MAIN, 3.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_emac_ptp_cwk_swc = {
	.cmd_wcgw = 0x47038,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_emac_ptp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_emac_ptp_cwk_swc",
		.pawent_data = gcc_pawents_2,
		.num_pawents = AWWAY_SIZE(gcc_pawents_2),
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
	.cmd_wcgw = 0x2b004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawents_3,
		.num_pawents = AWWAY_SIZE(gcc_pawents_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x2c004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawents_3,
		.num_pawents = AWWAY_SIZE(gcc_pawents_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x2d004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawents_3,
		.num_pawents = AWWAY_SIZE(gcc_pawents_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie_aux_phy_cwk_swc = {
	.cmd_wcgw = 0x37034,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_cpuss_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_aux_phy_cwk_swc",
		.pawent_data = gcc_pawents_4,
		.num_pawents = AWWAY_SIZE(gcc_pawents_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_wchng_phy_cwk_swc[] = {
	F(100000000, P_GPWW0_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_wchng_phy_cwk_swc = {
	.cmd_wcgw = 0x37050,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_pcie_wchng_phy_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_wchng_phy_cwk_swc",
		.pawent_data = gcc_pawents_3,
		.num_pawents = AWWAY_SIZE(gcc_pawents_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPWW0_OUT_MAIN, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pdm2_cwk_swc = {
	.cmd_wcgw = 0x19010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pdm2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pdm2_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0xf00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_mastew_cwk_swc[] = {
	F(200000000, P_GPWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_mastew_cwk_swc = {
	.cmd_wcgw = 0xb024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_mastew_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_mock_utmi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0xb03c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawents_0,
		.num_pawents = AWWAY_SIZE(gcc_pawents_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb3_phy_aux_cwk_swc[] = {
	F(1000000, P_BI_TCXO, 1, 5, 96),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb3_phy_aux_cwk_swc = {
	.cmd_wcgw = 0xb064,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_usb3_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_phy_aux_cwk_swc",
		.pawent_data = gcc_pawents_4,
		.num_pawents = AWWAY_SIZE(gcc_pawents_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_ahb_pcie_wink_cwk = {
	.hawt_weg = 0x22004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x22004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ahb_pcie_wink_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x10004,
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
	.hawt_weg = 0x11008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup1_i2c_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x11004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x13008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup2_i2c_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x13004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_i2c_apps_cwk = {
	.hawt_weg = 0x15008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup3_i2c_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_spi_apps_cwk = {
	.hawt_weg = 0x15004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x15004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup3_spi_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_i2c_apps_cwk = {
	.hawt_weg = 0x17008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup4_i2c_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_spi_apps_cwk = {
	.hawt_weg = 0x17004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_qup4_spi_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x12004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_uawt1_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt2_apps_cwk = {
	.hawt_weg = 0x14004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x14004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_uawt2_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt3_apps_cwk = {
	.hawt_weg = 0x16004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt3_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_uawt3_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt4_apps_cwk = {
	.hawt_weg = 0x18004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x18004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_bwsp1_uawt4_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x1c004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1c004,
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

static stwuct cwk_bwanch gcc_ce1_ahb_cwk = {
	.hawt_weg = 0x2100c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2100c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_axi_cwk = {
	.hawt_weg = 0x21008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_cwk = {
	.hawt_weg = 0x21004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cpuss_wbcpw_cwk = {
	.hawt_weg = 0x24008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x24008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_wbcpw_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_cpuss_wbcpw_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_axi_cwk = {
	.hawt_weg = 0x4701c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4701c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_ptp_cwk = {
	.hawt_weg = 0x47018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x47018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_ptp_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_emac_ptp_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_wgmii_cwk = {
	.hawt_weg = 0x47010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x47010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_wgmii_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_emac_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_swave_ahb_cwk = {
	.hawt_weg = 0x47014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x47014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eth_swave_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x2b000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2b000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_gp1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x2c000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2c000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_gp2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0x2d000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2d000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_gp3_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cwkwef_cwk = {
	.hawt_weg = 0x88004,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x88004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_aux_cwk = {
	.hawt_weg = 0x37024,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_aux_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_cfg_ahb_cwk = {
	.hawt_weg = 0x3701c,
	.hawt_check = BWANCH_HAWT_VOTED,
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
	.hawt_weg = 0x37018,
	.hawt_check = BWANCH_HAWT_VOTED,
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
	.hawt_weg = 0x3702c,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_wchng_phy_cwk = {
	.hawt_weg = 0x37020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_wchng_phy_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_pcie_wchng_phy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_sweep_cwk = {
	.hawt_weg = 0x37028,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_pcie_aux_phy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_swv_axi_cwk = {
	.hawt_weg = 0x37014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x37014,
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
	.hawt_weg = 0x37010,
	.hawt_check = BWANCH_HAWT_VOTED,
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
	.hawt_weg = 0x1900c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1900c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_pdm2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_ahb_cwk = {
	.hawt_weg = 0x19004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x19004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x19004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_xo4_cwk = {
	.hawt_weg = 0x19008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x19008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_xo4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0xf008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0xf004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xf004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_sdcc1_apps_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mastew_cwk = {
	.hawt_weg = 0xb010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_usb30_mastew_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mock_utmi_cwk = {
	.hawt_weg = 0xb020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_usb30_mock_utmi_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mstw_axi_cwk = {
	.hawt_weg = 0xb014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sweep_cwk = {
	.hawt_weg = 0xb01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_swv_ahb_cwk = {
	.hawt_weg = 0xb018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_swv_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_aux_cwk = {
	.hawt_weg = 0xb058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&gcc_usb3_phy_aux_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_pipe_cwk = {
	.hawt_weg = 0xb05c,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0xb05c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_cwkwef_cwk = {
	.hawt_weg = 0x88000,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x88000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_cwkwef_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_phy_cfg_ahb2phy_cwk = {
	.hawt_weg = 0xe004,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0xe004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xe004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_phy_cfg_ahb2phy_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_xo_pcie_wink_cwk = {
	.hawt_weg = 0x22008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x22008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_xo_pcie_wink_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc usb30_gdsc = {
	.gdscw = 0x0b004,
	.pd = {
		.name = "usb30_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc pcie_gdsc = {
	.gdscw = 0x37004,
	.pd = {
		.name = "pcie_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc emac_gdsc = {
	.gdscw = 0x47004,
	.pd = {
		.name = "emac_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *gcc_sdx55_cwocks[] = {
	[GCC_AHB_PCIE_WINK_CWK] = &gcc_ahb_pcie_wink_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK_SWC] =
		&gcc_bwsp1_qup1_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK_SWC] =
		&gcc_bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK_SWC] =
		&gcc_bwsp1_qup2_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK_SWC] =
		&gcc_bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK] = &gcc_bwsp1_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK_SWC] =
		&gcc_bwsp1_qup3_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK] = &gcc_bwsp1_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK_SWC] =
		&gcc_bwsp1_qup3_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK] = &gcc_bwsp1_qup4_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK_SWC] =
		&gcc_bwsp1_qup4_i2c_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK] = &gcc_bwsp1_qup4_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK_SWC] =
		&gcc_bwsp1_qup4_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK_SWC] = &gcc_bwsp1_uawt1_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK_SWC] = &gcc_bwsp1_uawt2_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK] = &gcc_bwsp1_uawt3_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK_SWC] = &gcc_bwsp1_uawt3_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT4_APPS_CWK] = &gcc_bwsp1_uawt4_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT4_APPS_CWK_SWC] = &gcc_bwsp1_uawt4_apps_cwk_swc.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CE1_AHB_CWK] = &gcc_ce1_ahb_cwk.cwkw,
	[GCC_CE1_AXI_CWK] = &gcc_ce1_axi_cwk.cwkw,
	[GCC_CE1_CWK] = &gcc_ce1_cwk.cwkw,
	[GCC_CPUSS_AHB_CWK_SWC] = &gcc_cpuss_ahb_cwk_swc.cwkw,
	[GCC_CPUSS_WBCPW_CWK] = &gcc_cpuss_wbcpw_cwk.cwkw,
	[GCC_CPUSS_WBCPW_CWK_SWC] = &gcc_cpuss_wbcpw_cwk_swc.cwkw,
	[GCC_EMAC_CWK_SWC] = &gcc_emac_cwk_swc.cwkw,
	[GCC_EMAC_PTP_CWK_SWC] = &gcc_emac_ptp_cwk_swc.cwkw,
	[GCC_ETH_AXI_CWK] = &gcc_eth_axi_cwk.cwkw,
	[GCC_ETH_PTP_CWK] = &gcc_eth_ptp_cwk.cwkw,
	[GCC_ETH_WGMII_CWK] = &gcc_eth_wgmii_cwk.cwkw,
	[GCC_ETH_SWAVE_AHB_CWK] = &gcc_eth_swave_ahb_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_PCIE_0_CWKWEF_CWK] = &gcc_pcie_0_cwkwef_cwk.cwkw,
	[GCC_PCIE_AUX_CWK] = &gcc_pcie_aux_cwk.cwkw,
	[GCC_PCIE_AUX_PHY_CWK_SWC] = &gcc_pcie_aux_phy_cwk_swc.cwkw,
	[GCC_PCIE_CFG_AHB_CWK] = &gcc_pcie_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_MSTW_AXI_CWK] = &gcc_pcie_mstw_axi_cwk.cwkw,
	[GCC_PCIE_PIPE_CWK] = &gcc_pcie_pipe_cwk.cwkw,
	[GCC_PCIE_WCHNG_PHY_CWK] = &gcc_pcie_wchng_phy_cwk.cwkw,
	[GCC_PCIE_WCHNG_PHY_CWK_SWC] = &gcc_pcie_wchng_phy_cwk_swc.cwkw,
	[GCC_PCIE_SWEEP_CWK] = &gcc_pcie_sweep_cwk.cwkw,
	[GCC_PCIE_SWV_AXI_CWK] = &gcc_pcie_swv_axi_cwk.cwkw,
	[GCC_PCIE_SWV_Q2A_AXI_CWK] = &gcc_pcie_swv_q2a_axi_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK_SWC] = &gcc_sdcc1_apps_cwk_swc.cwkw,
	[GCC_USB30_MASTEW_CWK] = &gcc_usb30_mastew_cwk.cwkw,
	[GCC_USB30_MASTEW_CWK_SWC] = &gcc_usb30_mastew_cwk_swc.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK] = &gcc_usb30_mock_utmi_cwk.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK_SWC] = &gcc_usb30_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_MSTW_AXI_CWK] = &gcc_usb30_mstw_axi_cwk.cwkw,
	[GCC_USB30_SWEEP_CWK] = &gcc_usb30_sweep_cwk.cwkw,
	[GCC_USB30_SWV_AHB_CWK] = &gcc_usb30_swv_ahb_cwk.cwkw,
	[GCC_USB3_PHY_AUX_CWK] = &gcc_usb3_phy_aux_cwk.cwkw,
	[GCC_USB3_PHY_AUX_CWK_SWC] = &gcc_usb3_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PHY_PIPE_CWK] = &gcc_usb3_phy_pipe_cwk.cwkw,
	[GCC_USB3_PWIM_CWKWEF_CWK] = &gcc_usb3_pwim_cwkwef_cwk.cwkw,
	[GCC_USB_PHY_CFG_AHB2PHY_CWK] = &gcc_usb_phy_cfg_ahb2phy_cwk.cwkw,
	[GCC_XO_PCIE_WINK_CWK] = &gcc_xo_pcie_wink_cwk.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW0_OUT_EVEN] = &gpww0_out_even.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[GPWW4_OUT_EVEN] = &gpww4_out_even.cwkw,
	[GPWW5] = &gpww5.cwkw,
};

static const stwuct qcom_weset_map gcc_sdx55_wesets[] = {
	[GCC_EMAC_BCW] = { 0x47000 },
	[GCC_PCIE_BCW] = { 0x37000 },
	[GCC_PCIE_WINK_DOWN_BCW] = { 0x77000 },
	[GCC_PCIE_PHY_BCW] = { 0x39000 },
	[GCC_PCIE_PHY_COM_BCW] = { 0x78004 },
	[GCC_QUSB2PHY_BCW] = { 0xd000 },
	[GCC_USB30_BCW] = { 0xb000 },
	[GCC_USB3_PHY_BCW] = { 0xc000 },
	[GCC_USB3PHY_PHY_BCW] = { 0xc004 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0xe000 },
};

static stwuct gdsc *gcc_sdx55_gdscs[] = {
	[USB30_GDSC] = &usb30_gdsc,
	[PCIE_GDSC] = &pcie_gdsc,
	[EMAC_GDSC] = &emac_gdsc,
};

static const stwuct wegmap_config gcc_sdx55_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x9b040,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_sdx55_desc = {
	.config = &gcc_sdx55_wegmap_config,
	.cwks = gcc_sdx55_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sdx55_cwocks),
	.wesets = gcc_sdx55_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sdx55_wesets),
	.gdscs = gcc_sdx55_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sdx55_gdscs),
};

static const stwuct of_device_id gcc_sdx55_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-sdx55" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sdx55_match_tabwe);

static int gcc_sdx55_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gcc_sdx55_desc);
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

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sdx55_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sdx55_dwivew = {
	.pwobe = gcc_sdx55_pwobe,
	.dwivew = {
		.name = "gcc-sdx55",
		.of_match_tabwe = gcc_sdx55_match_tabwe,
	},
};

static int __init gcc_sdx55_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sdx55_dwivew);
}
subsys_initcaww(gcc_sdx55_init);

static void __exit gcc_sdx55_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sdx55_dwivew);
}
moduwe_exit(gcc_sdx55_exit);

MODUWE_DESCWIPTION("QTI GCC SDX55 Dwivew");
MODUWE_WICENSE("GPW v2");
