// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,ipq5332-gcc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "cwk-wegmap-phy-mux.h"
#incwude "weset.h"

enum {
	DT_XO,
	DT_SWEEP_CWK,
	DT_PCIE_2WANE_PHY_PIPE_CWK,
	DT_PCIE_2WANE_PHY_PIPE_CWK_X1,
	DT_USB_PCIE_WWAPPEW_PIPE_CWK,
};

enum {
	P_PCIE3X2_PIPE,
	P_PCIE3X1_0_PIPE,
	P_PCIE3X1_1_PIPE,
	P_USB3PHY_0_PIPE,
	P_COWE_BI_PWW_TEST_SE,
	P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC,
	P_GPWW0_OUT_AUX,
	P_GPWW0_OUT_MAIN,
	P_GPWW2_OUT_AUX,
	P_GPWW2_OUT_MAIN,
	P_GPWW4_OUT_AUX,
	P_GPWW4_OUT_MAIN,
	P_SWEEP_CWK,
	P_XO,
};

static const stwuct cwk_pawent_data gcc_pawent_data_xo = { .index = DT_XO };

static stwuct cwk_awpha_pww gpww0_main = {
	.offset = 0x20000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.cwkw = {
		.enabwe_weg = 0xb000,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gpww0_main",
			.pawent_data = &gcc_pawent_data_xo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_stwomew_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww0_div2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww0_div2",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gpww0_main.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww_postdiv gpww0 = {
	.offset = 0x20000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww0",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gpww0_main.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wo_ops,
	},
};

static stwuct cwk_awpha_pww gpww2_main = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.cwkw = {
		.enabwe_weg = 0xb000,
		.enabwe_mask = BIT(1),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gpww2",
			.pawent_data = &gcc_pawent_data_xo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_stwomew_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gpww2 = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww2_main",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gpww2_main.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wo_ops,
	},
};

static stwuct cwk_awpha_pww gpww4_main = {
	.offset = 0x22000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.cwkw = {
		.enabwe_weg = 0xb000,
		.enabwe_mask = BIT(2),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gpww4_main",
			.pawent_data = &gcc_pawent_data_xo,
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_stwomew_ops,
			/*
			 * Thewe awe no consumews fow this GPWW in kewnew yet,
			 * (wiww be added soon), so the cwock fwamewowk
			 * disabwes this souwce. But some of the cwocks
			 * initiawized by boot woadews uses this souwce. So we
			 * need to keep this cwock ON. Add the
			 * CWK_IGNOWE_UNUSED fwag so the cwock wiww not be
			 * disabwed. Once the consumew in kewnew is added, we
			 * can get wid of this fwag.
			 */
			.fwags = CWK_IGNOWE_UNUSED,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gpww4 = {
	.offset = 0x22000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww4",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gpww4_main.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wo_ops,
	},
};

static const stwuct pawent_map gcc_pawent_map_xo[] = {
	{ P_XO, 0 },
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_div2.hw },
};

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW4_OUT_MAIN, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 4 },
	{ P_SWEEP_CWK, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_div2.hw },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_XO, 0 },
	{ P_GPWW4_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_AUX, 2 },
	{ P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .index = DT_XO },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_div2.hw },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW0_OUT_AUX, 2 },
	{ P_SWEEP_CWK, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0.cwkw.hw },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW2_OUT_AUX, 2 },
	{ P_GPWW4_OUT_AUX, 3 },
	{ P_SWEEP_CWK, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww2.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_7[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW2_OUT_AUX, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_7[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww2.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW2_OUT_MAIN, 2 },
	{ P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww2.cwkw.hw },
	{ .hw = &gpww0_div2.hw },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_SWEEP_CWK, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_MAIN, 1 },
	{ P_GPWW4_OUT_MAIN, 2 },
	{ P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 3 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww0_div2.hw },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_XO, 0 },
	{ P_GPWW0_OUT_AUX, 2 },
	{ P_SWEEP_CWK, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_12[] = {
	{ P_XO, 0 },
	{ P_GPWW4_OUT_AUX, 1 },
	{ P_GPWW0_OUT_MAIN, 3 },
	{ P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_12[] = {
	{ .index = DT_XO },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_div2.hw },
};

static const stwuct fweq_tbw ftbw_gcc_adss_pwm_cwk_swc[] = {
	F(24000000, P_XO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_adss_pwm_cwk_swc = {
	.cmd_wcgw = 0x1c004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_adss_pwm_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_adss_pwm_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_apss_axi_cwk_swc[] = {
	F(480000000, P_GPWW4_OUT_AUX, 2.5, 0, 0),
	F(533333333, P_GPWW0_OUT_MAIN, 1.5, 0, 0),
	{ }
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc[] = {
	F(960000, P_XO, 1, 1, 25),
	F(4800000, P_XO, 5, 0, 0),
	F(9600000, P_XO, 2.5, 0, 0),
	F(16000000, P_GPWW0_OUT_MAIN, 10, 1, 5),
	F(24000000, P_XO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_bwsp1_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x3004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x4004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_bwsp1_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_bwsp1_uawt1_apps_cwk_swc[] = {
	F(3686400, P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 1, 144, 15625),
	F(7372800, P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 1, 288, 15625),
	F(14745600, P_GCC_GPWW0_OUT_MAIN_DIV_CWK_SWC, 1, 576, 15625),
	F(24000000, P_XO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	F(32000000, P_GPWW0_OUT_MAIN, 1, 1, 25),
	F(40000000, P_GPWW0_OUT_MAIN, 1, 1, 20),
	F(46400000, P_GPWW0_OUT_MAIN, 1, 29, 500),
	F(48000000, P_GPWW0_OUT_MAIN, 1, 3, 50),
	F(51200000, P_GPWW0_OUT_MAIN, 1, 8, 125),
	F(56000000, P_GPWW0_OUT_MAIN, 1, 7, 100),
	F(58982400, P_GPWW0_OUT_MAIN, 1, 1152, 15625),
	F(60000000, P_GPWW0_OUT_MAIN, 1, 3, 40),
	F(64000000, P_GPWW0_OUT_MAIN, 12.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x202c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x302c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_bwsp1_uawt3_apps_cwk_swc = {
	.cmd_wcgw = 0x402c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_bwsp1_uawt3_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(24000000, P_XO, 1, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x8004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x9004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_wpass_sway_cwk_swc[] = {
	F(133333333, P_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_wpass_sway_cwk_swc = {
	.cmd_wcgw = 0x27004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_wpass_sway_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_wpass_sway_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_nss_ts_cwk_swc[] = {
	F(24000000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_nss_ts_cwk_swc = {
	.cmd_wcgw = 0x17088,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_xo,
	.fweq_tbw = ftbw_gcc_nss_ts_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_nss_ts_cwk_swc",
		.pawent_data = &gcc_pawent_data_xo,
		.num_pawents = 1,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie3x1_0_axi_cwk_swc[] = {
	F(240000000, P_GPWW4_OUT_MAIN, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie3x1_0_axi_cwk_swc = {
	.cmd_wcgw = 0x29018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie3x1_0_axi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x1_0_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie3x1_0_wchg_cwk_swc = {
	.cmd_wcgw = 0x2907c,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_adss_pwm_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x1_0_wchg_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_wchg_cwk = {
	.hawt_weg = 0x2907c,
	.cwkw = {
		.enabwe_weg = 0x2907c,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_wchg_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]) {
					&gcc_pcie3x1_0_wchg_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wcg2 gcc_pcie3x1_1_axi_cwk_swc = {
	.cmd_wcgw = 0x2a004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie3x1_0_axi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x1_1_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie3x1_1_wchg_cwk_swc = {
	.cmd_wcgw = 0x2a078,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_adss_pwm_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x1_1_wchg_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_wchg_cwk = {
	.hawt_weg = 0x2a078,
	.cwkw = {
		.enabwe_weg = 0x2a078,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_wchg_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]) {
					&gcc_pcie3x1_1_wchg_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie3x2_axi_m_cwk_swc[] = {
	F(266666667, P_GPWW4_OUT_MAIN, 4.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie3x2_axi_m_cwk_swc = {
	.cmd_wcgw = 0x28018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie3x2_axi_m_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x2_axi_m_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie3x2_axi_s_cwk_swc = {
	.cmd_wcgw = 0x28084,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie3x1_0_axi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x2_axi_s_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie3x2_wchg_cwk_swc = {
	.cmd_wcgw = 0x28078,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_adss_pwm_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie3x2_wchg_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_wchg_cwk = {
	.hawt_weg = 0x28078,
	.cwkw = {
		.enabwe_weg = 0x28078,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_wchg_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]) {
					&gcc_pcie3x2_wchg_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_aux_cwk_swc[] = {
	F(2000000, P_XO, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_aux_cwk_swc = {
	.cmd_wcgw = 0x28004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_pcie_aux_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_phy_mux gcc_pcie3x2_pipe_cwk_swc = {
	.weg = 0x28064,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_PCIE_2WANE_PHY_PIPE_CWK,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_phy_mux gcc_pcie3x1_0_pipe_cwk_swc = {
	.weg = 0x29064,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_USB_PCIE_WWAPPEW_PIPE_CWK,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_phy_mux gcc_pcie3x1_1_pipe_cwk_swc = {
	.weg = 0x2a064,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_PCIE_2WANE_PHY_PIPE_CWK_X1,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcnoc_bfdcd_cwk_swc[] = {
	F(24000000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0_OUT_MAIN, 16, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcnoc_bfdcd_cwk_swc = {
	.cmd_wcgw = 0x31004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcnoc_bfdcd_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcnoc_bfdcd_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_q6_axim_cwk_swc = {
	.cmd_wcgw = 0x25004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_apss_axi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_q6_axim_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qdss_at_cwk_swc[] = {
	F(240000000, P_GPWW4_OUT_MAIN, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_qdss_at_cwk_swc = {
	.cmd_wcgw = 0x2d004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_qdss_at_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_qdss_at_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qdss_tsctw_cwk_swc[] = {
	F(600000000, P_GPWW4_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_qdss_tsctw_cwk_swc = {
	.cmd_wcgw = 0x2d01c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_qdss_tsctw_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_qdss_tsctw_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_fixed_factow gcc_qdss_tsctw_div2_cwk_swc = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_qdss_tsctw_div2_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_qdss_tsctw_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_fixed_factow gcc_qdss_tsctw_div3_cwk_swc = {
	.muwt = 1,
	.div = 3,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_qdss_tsctw_div3_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_qdss_tsctw_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_fixed_factow gcc_qdss_tsctw_div4_cwk_swc = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_qdss_tsctw_div4_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_qdss_tsctw_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_fixed_factow gcc_qdss_tsctw_div8_cwk_swc = {
	.muwt = 1,
	.div = 8,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_qdss_tsctw_div8_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_qdss_tsctw_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_fixed_factow gcc_qdss_tsctw_div16_cwk_swc = {
	.muwt = 1,
	.div = 16,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_qdss_tsctw_div16_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_qdss_tsctw_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qpic_io_macwo_cwk_swc[] = {
	F(24000000, P_XO, 1, 0, 0),
	F(100000000, P_GPWW0_OUT_MAIN, 8, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(320000000, P_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_qpic_io_macwo_cwk_swc = {
	.cmd_wcgw = 0x32004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_qpic_io_macwo_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_qpic_io_macwo_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk_swc[] = {
	F(143713, P_XO, 1, 1, 167),
	F(400000, P_XO, 1, 1, 60),
	F(24000000, P_XO, 1, 0, 0),
	F(48000000, P_GPWW2_OUT_MAIN, 12, 1, 2),
	F(96000000, P_GPWW2_OUT_MAIN, 12, 0, 0),
	F(177777778, P_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(192000000, P_GPWW2_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x33004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_sdcc1_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sweep_cwk_swc[] = {
	F(32000, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sweep_cwk_swc = {
	.cmd_wcgw = 0x3400c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_gcc_sweep_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_sweep_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_system_noc_bfdcd_cwk_swc[] = {
	F(24000000, P_XO, 1, 0, 0),
	F(133333333, P_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN, 4, 0, 0),
	F(266666667, P_GPWW4_OUT_MAIN, 4.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_system_noc_bfdcd_cwk_swc = {
	.cmd_wcgw = 0x2e004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_10,
	.fweq_tbw = ftbw_gcc_system_noc_bfdcd_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_system_noc_bfdcd_cwk_swc",
		.pawent_data = gcc_pawent_data_10,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_fixed_factow gcc_system_noc_bfdcd_div2_cwk_swc = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_system_noc_bfdcd_div2_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wcg2 gcc_uniphy_sys_cwk_swc = {
	.cmd_wcgw = 0x16004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_xo,
	.fweq_tbw = ftbw_gcc_nss_ts_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_uniphy_sys_cwk_swc",
		.pawent_data = &gcc_pawent_data_xo,
		.num_pawents = 1,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb0_aux_cwk_swc = {
	.cmd_wcgw = 0x2c018,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_11,
	.fweq_tbw = ftbw_gcc_pcie_aux_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb0_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_11,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb0_wfps_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_MAIN, 16, 1, 2),
	{ }
};

static stwuct cwk_wcg2 gcc_usb0_wfps_cwk_swc = {
	.cmd_wcgw = 0x2c07c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_usb0_wfps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb0_wfps_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb0_mastew_cwk_swc = {
	.cmd_wcgw = 0x2c004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb0_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb0_mock_utmi_cwk_swc[] = {
	F(60000000, P_GPWW4_OUT_AUX, 10, 1, 2),
	{ }
};

static stwuct cwk_wcg2 gcc_usb0_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x2c02c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_12,
	.fweq_tbw = ftbw_gcc_usb0_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb0_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_12,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_12),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_phy_mux gcc_usb0_pipe_cwk_swc = {
	.weg = 0x2c074,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_usb0_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_USB_PCIE_WWAPPEW_PIPE_CWK,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wcg2 gcc_wcss_ahb_cwk_swc = {
	.cmd_wcgw = 0x25030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_wpass_sway_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_wcss_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_xo_cwk_swc = {
	.cmd_wcgw = 0x34004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_xo,
	.fweq_tbw = ftbw_gcc_nss_ts_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_xo_cwk_swc",
		.pawent_data = &gcc_pawent_data_xo,
		.num_pawents = 1,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_fixed_factow gcc_xo_div4_cwk_swc = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_xo_div4_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_xo_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap_div gcc_qdss_dap_div_cwk_swc = {
	.weg = 0x2d028,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_qdss_dap_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_qdss_tsctw_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div gcc_usb0_mock_utmi_div_cwk_swc = {
	.weg = 0x2c040,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb0_mock_utmi_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_usb0_mock_utmi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch gcc_adss_pwm_cwk = {
	.hawt_weg = 0x1c00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1c00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_adss_pwm_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_adss_pwm_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ahb_cwk = {
	.hawt_weg = 0x34024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x34024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x1008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb004,
		.enabwe_mask = BIT(4),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_bwsp1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x2024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x2020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x3024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x3020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x4024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_bwsp1_qup3_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_spi_apps_cwk = {
	.hawt_weg = 0x4020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_bwsp1_sweep_cwk = {
	.hawt_weg = 0x1010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb004,
		.enabwe_mask = BIT(5),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_bwsp1_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x2040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2040,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x3040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3040,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x4054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4054,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_ce_ahb_cwk = {
	.hawt_weg = 0x25074,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25074,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ce_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_div2_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce_axi_cwk = {
	.hawt_weg = 0x25068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ce_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce_pcnoc_ahb_cwk = {
	.hawt_weg = 0x25070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25070,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ce_pcnoc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cmn_12gpww_ahb_cwk = {
	.hawt_weg = 0x3a004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_cmn_12gpww_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cmn_12gpww_apu_cwk = {
	.hawt_weg = 0x3a00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3a00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_cmn_12gpww_apu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cmn_12gpww_sys_cwk = {
	.hawt_weg = 0x3a008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3a008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_cmn_12gpww_sys_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_uniphy_sys_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x8018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x9018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_wpass_cowe_axim_cwk = {
	.hawt_weg = 0x27018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x27018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wpass_cowe_axim_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wpass_sway_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wpass_sway_cwk = {
	.hawt_weg = 0x27014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x27014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wpass_sway_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wpass_sway_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdio_ahb_cwk = {
	.hawt_weg = 0x12004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x12004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_mdio_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mdio_swave_ahb_cwk = {
	.hawt_weg = 0x1200c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_mdio_swave_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nss_ts_cwk = {
	.hawt_weg = 0x17018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x17018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nss_ts_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_nss_ts_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nsscc_cwk = {
	.hawt_weg = 0x17034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17034,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nsscc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nsscfg_cwk = {
	.hawt_weg = 0x1702c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1702c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nsscfg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_atb_cwk = {
	.hawt_weg = 0x17014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_atb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_nsscc_cwk = {
	.hawt_weg = 0x17030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_nsscc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_qosgen_wef_cwk = {
	.hawt_weg = 0x1701c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1701c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_qosgen_wef_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_xo_div4_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_snoc_1_cwk = {
	.hawt_weg = 0x1707c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1707c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_snoc_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_snoc_cwk = {
	.hawt_weg = 0x17028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17028,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_snoc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_timeout_wef_cwk = {
	.hawt_weg = 0x17020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_timeout_wef_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_xo_div4_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_xo_dcd_cwk = {
	.hawt_weg = 0x17074,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17074,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_xo_dcd_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_ahb_cwk = {
	.hawt_weg = 0x29030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x29030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_aux_cwk = {
	.hawt_weg = 0x29070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x29070,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_axi_m_cwk = {
	.hawt_weg = 0x29038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x29038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_axi_m_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_0_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_axi_s_bwidge_cwk = {
	.hawt_weg = 0x29048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x29048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_axi_s_bwidge_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_0_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_axi_s_cwk = {
	.hawt_weg = 0x29040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x29040,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_axi_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_0_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_0_pipe_cwk = {
	.hawt_weg = 0x29068,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x29068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_0_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_0_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_ahb_cwk = {
	.hawt_weg = 0x2a00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2a00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_aux_cwk = {
	.hawt_weg = 0x2a070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2a070,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_axi_m_cwk = {
	.hawt_weg = 0x2a014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2a014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_axi_m_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_1_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_axi_s_bwidge_cwk = {
	.hawt_weg = 0x2a024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2a024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_axi_s_bwidge_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_1_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_axi_s_cwk = {
	.hawt_weg = 0x2a01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2a01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_axi_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_1_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_1_pipe_cwk = {
	.hawt_weg = 0x2a068,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x2a068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_1_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_1_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x1_phy_ahb_cwk = {
	.hawt_weg = 0x29078,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x29078,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x1_phy_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_ahb_cwk = {
	.hawt_weg = 0x28030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x28030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_aux_cwk = {
	.hawt_weg = 0x28070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x28070,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_axi_m_cwk = {
	.hawt_weg = 0x28038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x28038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_axi_m_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x2_axi_m_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_axi_s_bwidge_cwk = {
	.hawt_weg = 0x28048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x28048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_axi_s_bwidge_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x2_axi_s_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_axi_s_cwk = {
	.hawt_weg = 0x28040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x28040,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_axi_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x2_axi_s_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_phy_ahb_cwk = {
	.hawt_weg = 0x28080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x28080,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_phy_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie3x2_pipe_cwk = {
	.hawt_weg = 0x28068,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x28068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie3x2_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x2_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcnoc_at_cwk = {
	.hawt_weg = 0x31024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x31024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcnoc_at_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcnoc_wpass_cwk = {
	.hawt_weg = 0x31020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcnoc_wpass_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wpass_sway_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x13024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb004,
		.enabwe_mask = BIT(10),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pwng_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6_ahb_cwk = {
	.hawt_weg = 0x25014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x25014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wcss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6_ahb_s_cwk = {
	.hawt_weg = 0x25018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x25018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6_ahb_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wcss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6_axim_cwk = {
	.hawt_weg = 0x2500c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2500c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6_axim_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_q6_axim_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6_axis_cwk = {
	.hawt_weg = 0x25010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x25010,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6_axis_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6_tsctw_1to2_cwk = {
	.hawt_weg = 0x25020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x25020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6_tsctw_1to2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_tsctw_div2_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6ss_atbm_cwk = {
	.hawt_weg = 0x2501c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6ss_atbm_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6ss_pcwkdbg_cwk = {
	.hawt_weg = 0x25024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x25024,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6ss_pcwkdbg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_dap_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_q6ss_twig_cwk = {
	.hawt_weg = 0x250a0,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x250a0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_q6ss_twig_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_dap_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qdss_at_cwk = {
	.hawt_weg = 0x2d038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2d038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qdss_at_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qdss_cfg_ahb_cwk = {
	.hawt_weg = 0x2d06c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2d06c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qdss_cfg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qdss_dap_ahb_cwk = {
	.hawt_weg = 0x2d068,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2d068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qdss_dap_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qdss_dap_cwk = {
	.hawt_weg = 0x2d05c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xb004,
		.enabwe_mask = BIT(2),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qdss_dap_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_dap_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qdss_etw_usb_cwk = {
	.hawt_weg = 0x2d064,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2d064,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qdss_etw_usb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_fixed_factow gcc_eud_at_div_cwk_swc = {
	.muwt = 1,
	.div = 6,
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_eud_at_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw *[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_bwanch gcc_qdss_eud_at_cwk = {
	.hawt_weg = 0x2d070,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2d070,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qdss_eud_at_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_eud_at_div_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qpic_ahb_cwk = {
	.hawt_weg = 0x32010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x32010,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qpic_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qpic_cwk = {
	.hawt_weg = 0x32014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x32014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qpic_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qpic_io_macwo_cwk = {
	.hawt_weg = 0x3200c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qpic_io_macwo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qpic_io_macwo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qpic_sweep_cwk = {
	.hawt_weg = 0x3201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qpic_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x33034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x33034,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sdcc1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x3302c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3302c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_snoc_wpass_cfg_cwk = {
	.hawt_weg = 0x2e028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e028,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_wpass_cfg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wpass_sway_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_nssnoc_1_cwk = {
	.hawt_weg = 0x17090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17090,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_nssnoc_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_nssnoc_cwk = {
	.hawt_weg = 0x17084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17084,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_nssnoc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie3_1wane_1_m_cwk = {
	.hawt_weg = 0x2e050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e050,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie3_1wane_1_m_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_1_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie3_1wane_1_s_cwk = {
	.hawt_weg = 0x2e0ac,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e0ac,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie3_1wane_1_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_1_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie3_1wane_m_cwk = {
	.hawt_weg = 0x2e080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e080,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie3_1wane_m_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_0_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie3_1wane_s_cwk = {
	.hawt_weg = 0x2e04c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e04c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie3_1wane_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x1_0_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie3_2wane_m_cwk = {
	.hawt_weg = 0x2e07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie3_2wane_m_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x2_axi_m_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie3_2wane_s_cwk = {
	.hawt_weg = 0x2e048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie3_2wane_s_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie3x2_axi_s_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_usb_cwk = {
	.hawt_weg = 0x2e058,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2e058,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_usb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb0_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_at_cwk = {
	.hawt_weg = 0x2e038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2e038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sys_noc_at_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_wcss_ahb_cwk = {
	.hawt_weg = 0x2e030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sys_noc_wcss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wcss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_uniphy0_ahb_cwk = {
	.hawt_weg = 0x16010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16010,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_uniphy0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_uniphy0_sys_cwk = {
	.hawt_weg = 0x1600c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_uniphy0_sys_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_uniphy_sys_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_uniphy1_ahb_cwk = {
	.hawt_weg = 0x1601c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1601c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_uniphy1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_uniphy1_sys_cwk = {
	.hawt_weg = 0x16018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_uniphy1_sys_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_uniphy_sys_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_aux_cwk = {
	.hawt_weg = 0x2c050,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2c050,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb0_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_eud_at_cwk = {
	.hawt_weg = 0x30004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x30004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_eud_at_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_eud_at_div_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_wfps_cwk = {
	.hawt_weg = 0x2c090,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2c090,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_wfps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb0_wfps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_mastew_cwk = {
	.hawt_weg = 0x2c048,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2c048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb0_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_mock_utmi_cwk = {
	.hawt_weg = 0x2c054,
	.cwkw = {
		.enabwe_weg = 0x2c054,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb0_mock_utmi_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_phy_cfg_ahb_cwk = {
	.hawt_weg = 0x2c05c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2c05c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_phy_cfg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_pipe_cwk = {
	.hawt_weg = 0x2c078,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x2c078,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb0_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb0_sweep_cwk = {
	.hawt_weg = 0x2c058,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x2c058,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb0_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_axim_cwk = {
	.hawt_weg = 0x2505c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2505c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_axim_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_axis_cwk = {
	.hawt_weg = 0x25060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25060,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_axis_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_dbg_ifc_apb_bdg_cwk = {
	.hawt_weg = 0x25048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25048,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_dbg_ifc_apb_bdg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_dap_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_dbg_ifc_apb_cwk = {
	.hawt_weg = 0x25038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_dbg_ifc_apb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_dap_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_dbg_ifc_atb_bdg_cwk = {
	.hawt_weg = 0x2504c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2504c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_dbg_ifc_atb_bdg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_dbg_ifc_atb_cwk = {
	.hawt_weg = 0x2503c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2503c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_dbg_ifc_atb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_at_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_dbg_ifc_nts_bdg_cwk = {
	.hawt_weg = 0x25050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25050,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_dbg_ifc_nts_bdg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_tsctw_div2_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_dbg_ifc_nts_cwk = {
	.hawt_weg = 0x25040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25040,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_dbg_ifc_nts_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qdss_tsctw_div2_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_ecahb_cwk = {
	.hawt_weg = 0x25058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x25058,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_ecahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_wcss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_mst_async_bdg_cwk = {
	.hawt_weg = 0x2e0b0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e0b0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_mst_async_bdg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wcss_swv_async_bdg_cwk = {
	.hawt_weg = 0x2e0b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2e0b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_wcss_swv_async_bdg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_xo_cwk = {
	.hawt_weg = 0x34018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x34018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_xo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_xo_div4_cwk = {
	.hawt_weg = 0x3401c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3401c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_xo_div4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_xo_div4_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_im_sweep_cwk = {
	.hawt_weg = 0x34020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x34020,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_im_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_nssnoc_pcnoc_1_cwk = {
	.hawt_weg = 0x17080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17080,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_nssnoc_pcnoc_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap_div gcc_snoc_qosgen_extwef_div_cwk_swc = {
	.weg = 0x2e010,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_snoc_qosgen_extwef_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_xo_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap *gcc_ipq5332_cwocks[] = {
	[GPWW0_MAIN] = &gpww0_main.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW2_MAIN] = &gpww2_main.cwkw,
	[GPWW2] = &gpww2.cwkw,
	[GPWW4_MAIN] = &gpww4_main.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[GCC_ADSS_PWM_CWK] = &gcc_adss_pwm_cwk.cwkw,
	[GCC_ADSS_PWM_CWK_SWC] = &gcc_adss_pwm_cwk_swc.cwkw,
	[GCC_AHB_CWK] = &gcc_ahb_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK] = &gcc_bwsp1_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK] = &gcc_bwsp1_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK_SWC] = &gcc_bwsp1_qup3_spi_apps_cwk_swc.cwkw,
	[GCC_BWSP1_SWEEP_CWK] = &gcc_bwsp1_sweep_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK_SWC] = &gcc_bwsp1_uawt1_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK_SWC] = &gcc_bwsp1_uawt2_apps_cwk_swc.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK] = &gcc_bwsp1_uawt3_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK_SWC] = &gcc_bwsp1_uawt3_apps_cwk_swc.cwkw,
	[GCC_CE_AHB_CWK] = &gcc_ce_ahb_cwk.cwkw,
	[GCC_CE_AXI_CWK] = &gcc_ce_axi_cwk.cwkw,
	[GCC_CE_PCNOC_AHB_CWK] = &gcc_ce_pcnoc_ahb_cwk.cwkw,
	[GCC_CMN_12GPWW_AHB_CWK] = &gcc_cmn_12gpww_ahb_cwk.cwkw,
	[GCC_CMN_12GPWW_APU_CWK] = &gcc_cmn_12gpww_apu_cwk.cwkw,
	[GCC_CMN_12GPWW_SYS_CWK] = &gcc_cmn_12gpww_sys_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_WPASS_COWE_AXIM_CWK] = &gcc_wpass_cowe_axim_cwk.cwkw,
	[GCC_WPASS_SWAY_CWK] = &gcc_wpass_sway_cwk.cwkw,
	[GCC_WPASS_SWAY_CWK_SWC] = &gcc_wpass_sway_cwk_swc.cwkw,
	[GCC_MDIO_AHB_CWK] = &gcc_mdio_ahb_cwk.cwkw,
	[GCC_MDIO_SWAVE_AHB_CWK] = &gcc_mdio_swave_ahb_cwk.cwkw,
	[GCC_NSS_TS_CWK] = &gcc_nss_ts_cwk.cwkw,
	[GCC_NSS_TS_CWK_SWC] = &gcc_nss_ts_cwk_swc.cwkw,
	[GCC_NSSCC_CWK] = &gcc_nsscc_cwk.cwkw,
	[GCC_NSSCFG_CWK] = &gcc_nsscfg_cwk.cwkw,
	[GCC_NSSNOC_ATB_CWK] = &gcc_nssnoc_atb_cwk.cwkw,
	[GCC_NSSNOC_NSSCC_CWK] = &gcc_nssnoc_nsscc_cwk.cwkw,
	[GCC_NSSNOC_QOSGEN_WEF_CWK] = &gcc_nssnoc_qosgen_wef_cwk.cwkw,
	[GCC_NSSNOC_SNOC_1_CWK] = &gcc_nssnoc_snoc_1_cwk.cwkw,
	[GCC_NSSNOC_SNOC_CWK] = &gcc_nssnoc_snoc_cwk.cwkw,
	[GCC_NSSNOC_TIMEOUT_WEF_CWK] = &gcc_nssnoc_timeout_wef_cwk.cwkw,
	[GCC_NSSNOC_XO_DCD_CWK] = &gcc_nssnoc_xo_dcd_cwk.cwkw,
	[GCC_PCIE3X1_0_AHB_CWK] = &gcc_pcie3x1_0_ahb_cwk.cwkw,
	[GCC_PCIE3X1_0_AUX_CWK] = &gcc_pcie3x1_0_aux_cwk.cwkw,
	[GCC_PCIE3X1_0_AXI_CWK_SWC] = &gcc_pcie3x1_0_axi_cwk_swc.cwkw,
	[GCC_PCIE3X1_0_AXI_M_CWK] = &gcc_pcie3x1_0_axi_m_cwk.cwkw,
	[GCC_PCIE3X1_0_AXI_S_BWIDGE_CWK] = &gcc_pcie3x1_0_axi_s_bwidge_cwk.cwkw,
	[GCC_PCIE3X1_0_AXI_S_CWK] = &gcc_pcie3x1_0_axi_s_cwk.cwkw,
	[GCC_PCIE3X1_0_PIPE_CWK] = &gcc_pcie3x1_0_pipe_cwk.cwkw,
	[GCC_PCIE3X1_0_WCHG_CWK] = &gcc_pcie3x1_0_wchg_cwk.cwkw,
	[GCC_PCIE3X1_0_WCHG_CWK_SWC] = &gcc_pcie3x1_0_wchg_cwk_swc.cwkw,
	[GCC_PCIE3X1_1_AHB_CWK] = &gcc_pcie3x1_1_ahb_cwk.cwkw,
	[GCC_PCIE3X1_1_AUX_CWK] = &gcc_pcie3x1_1_aux_cwk.cwkw,
	[GCC_PCIE3X1_1_AXI_CWK_SWC] = &gcc_pcie3x1_1_axi_cwk_swc.cwkw,
	[GCC_PCIE3X1_1_AXI_M_CWK] = &gcc_pcie3x1_1_axi_m_cwk.cwkw,
	[GCC_PCIE3X1_1_AXI_S_BWIDGE_CWK] = &gcc_pcie3x1_1_axi_s_bwidge_cwk.cwkw,
	[GCC_PCIE3X1_1_AXI_S_CWK] = &gcc_pcie3x1_1_axi_s_cwk.cwkw,
	[GCC_PCIE3X1_1_PIPE_CWK] = &gcc_pcie3x1_1_pipe_cwk.cwkw,
	[GCC_PCIE3X1_1_WCHG_CWK] = &gcc_pcie3x1_1_wchg_cwk.cwkw,
	[GCC_PCIE3X1_1_WCHG_CWK_SWC] = &gcc_pcie3x1_1_wchg_cwk_swc.cwkw,
	[GCC_PCIE3X1_PHY_AHB_CWK] = &gcc_pcie3x1_phy_ahb_cwk.cwkw,
	[GCC_PCIE3X2_AHB_CWK] = &gcc_pcie3x2_ahb_cwk.cwkw,
	[GCC_PCIE3X2_AUX_CWK] = &gcc_pcie3x2_aux_cwk.cwkw,
	[GCC_PCIE3X2_AXI_M_CWK] = &gcc_pcie3x2_axi_m_cwk.cwkw,
	[GCC_PCIE3X2_AXI_M_CWK_SWC] = &gcc_pcie3x2_axi_m_cwk_swc.cwkw,
	[GCC_PCIE3X2_AXI_S_BWIDGE_CWK] = &gcc_pcie3x2_axi_s_bwidge_cwk.cwkw,
	[GCC_PCIE3X2_AXI_S_CWK] = &gcc_pcie3x2_axi_s_cwk.cwkw,
	[GCC_PCIE3X2_AXI_S_CWK_SWC] = &gcc_pcie3x2_axi_s_cwk_swc.cwkw,
	[GCC_PCIE3X2_PHY_AHB_CWK] = &gcc_pcie3x2_phy_ahb_cwk.cwkw,
	[GCC_PCIE3X2_PIPE_CWK] = &gcc_pcie3x2_pipe_cwk.cwkw,
	[GCC_PCIE3X2_WCHG_CWK] = &gcc_pcie3x2_wchg_cwk.cwkw,
	[GCC_PCIE3X2_WCHG_CWK_SWC] = &gcc_pcie3x2_wchg_cwk_swc.cwkw,
	[GCC_PCIE_AUX_CWK_SWC] = &gcc_pcie_aux_cwk_swc.cwkw,
	[GCC_PCNOC_AT_CWK] = &gcc_pcnoc_at_cwk.cwkw,
	[GCC_PCNOC_BFDCD_CWK_SWC] = &gcc_pcnoc_bfdcd_cwk_swc.cwkw,
	[GCC_PCNOC_WPASS_CWK] = &gcc_pcnoc_wpass_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_Q6_AHB_CWK] = &gcc_q6_ahb_cwk.cwkw,
	[GCC_Q6_AHB_S_CWK] = &gcc_q6_ahb_s_cwk.cwkw,
	[GCC_Q6_AXIM_CWK] = &gcc_q6_axim_cwk.cwkw,
	[GCC_Q6_AXIM_CWK_SWC] = &gcc_q6_axim_cwk_swc.cwkw,
	[GCC_Q6_AXIS_CWK] = &gcc_q6_axis_cwk.cwkw,
	[GCC_Q6_TSCTW_1TO2_CWK] = &gcc_q6_tsctw_1to2_cwk.cwkw,
	[GCC_Q6SS_ATBM_CWK] = &gcc_q6ss_atbm_cwk.cwkw,
	[GCC_Q6SS_PCWKDBG_CWK] = &gcc_q6ss_pcwkdbg_cwk.cwkw,
	[GCC_Q6SS_TWIG_CWK] = &gcc_q6ss_twig_cwk.cwkw,
	[GCC_QDSS_AT_CWK] = &gcc_qdss_at_cwk.cwkw,
	[GCC_QDSS_AT_CWK_SWC] = &gcc_qdss_at_cwk_swc.cwkw,
	[GCC_QDSS_CFG_AHB_CWK] = &gcc_qdss_cfg_ahb_cwk.cwkw,
	[GCC_QDSS_DAP_AHB_CWK] = &gcc_qdss_dap_ahb_cwk.cwkw,
	[GCC_QDSS_DAP_CWK] = &gcc_qdss_dap_cwk.cwkw,
	[GCC_QDSS_DAP_DIV_CWK_SWC] = &gcc_qdss_dap_div_cwk_swc.cwkw,
	[GCC_QDSS_ETW_USB_CWK] = &gcc_qdss_etw_usb_cwk.cwkw,
	[GCC_QDSS_EUD_AT_CWK] = &gcc_qdss_eud_at_cwk.cwkw,
	[GCC_QPIC_AHB_CWK] = &gcc_qpic_ahb_cwk.cwkw,
	[GCC_QPIC_CWK] = &gcc_qpic_cwk.cwkw,
	[GCC_QPIC_IO_MACWO_CWK] = &gcc_qpic_io_macwo_cwk.cwkw,
	[GCC_QPIC_IO_MACWO_CWK_SWC] = &gcc_qpic_io_macwo_cwk_swc.cwkw,
	[GCC_QPIC_SWEEP_CWK] = &gcc_qpic_sweep_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK_SWC] = &gcc_sdcc1_apps_cwk_swc.cwkw,
	[GCC_SWEEP_CWK_SWC] = &gcc_sweep_cwk_swc.cwkw,
	[GCC_SNOC_WPASS_CFG_CWK] = &gcc_snoc_wpass_cfg_cwk.cwkw,
	[GCC_SNOC_NSSNOC_1_CWK] = &gcc_snoc_nssnoc_1_cwk.cwkw,
	[GCC_SNOC_NSSNOC_CWK] = &gcc_snoc_nssnoc_cwk.cwkw,
	[GCC_SNOC_PCIE3_1WANE_1_M_CWK] = &gcc_snoc_pcie3_1wane_1_m_cwk.cwkw,
	[GCC_SNOC_PCIE3_1WANE_1_S_CWK] = &gcc_snoc_pcie3_1wane_1_s_cwk.cwkw,
	[GCC_SNOC_PCIE3_1WANE_M_CWK] = &gcc_snoc_pcie3_1wane_m_cwk.cwkw,
	[GCC_SNOC_PCIE3_1WANE_S_CWK] = &gcc_snoc_pcie3_1wane_s_cwk.cwkw,
	[GCC_SNOC_PCIE3_2WANE_M_CWK] = &gcc_snoc_pcie3_2wane_m_cwk.cwkw,
	[GCC_SNOC_PCIE3_2WANE_S_CWK] = &gcc_snoc_pcie3_2wane_s_cwk.cwkw,
	[GCC_SNOC_USB_CWK] = &gcc_snoc_usb_cwk.cwkw,
	[GCC_SYS_NOC_AT_CWK] = &gcc_sys_noc_at_cwk.cwkw,
	[GCC_SYS_NOC_WCSS_AHB_CWK] = &gcc_sys_noc_wcss_ahb_cwk.cwkw,
	[GCC_SYSTEM_NOC_BFDCD_CWK_SWC] = &gcc_system_noc_bfdcd_cwk_swc.cwkw,
	[GCC_UNIPHY0_AHB_CWK] = &gcc_uniphy0_ahb_cwk.cwkw,
	[GCC_UNIPHY0_SYS_CWK] = &gcc_uniphy0_sys_cwk.cwkw,
	[GCC_UNIPHY1_AHB_CWK] = &gcc_uniphy1_ahb_cwk.cwkw,
	[GCC_UNIPHY1_SYS_CWK] = &gcc_uniphy1_sys_cwk.cwkw,
	[GCC_UNIPHY_SYS_CWK_SWC] = &gcc_uniphy_sys_cwk_swc.cwkw,
	[GCC_USB0_AUX_CWK] = &gcc_usb0_aux_cwk.cwkw,
	[GCC_USB0_AUX_CWK_SWC] = &gcc_usb0_aux_cwk_swc.cwkw,
	[GCC_USB0_EUD_AT_CWK] = &gcc_usb0_eud_at_cwk.cwkw,
	[GCC_USB0_WFPS_CWK] = &gcc_usb0_wfps_cwk.cwkw,
	[GCC_USB0_WFPS_CWK_SWC] = &gcc_usb0_wfps_cwk_swc.cwkw,
	[GCC_USB0_MASTEW_CWK] = &gcc_usb0_mastew_cwk.cwkw,
	[GCC_USB0_MASTEW_CWK_SWC] = &gcc_usb0_mastew_cwk_swc.cwkw,
	[GCC_USB0_MOCK_UTMI_CWK] = &gcc_usb0_mock_utmi_cwk.cwkw,
	[GCC_USB0_MOCK_UTMI_CWK_SWC] = &gcc_usb0_mock_utmi_cwk_swc.cwkw,
	[GCC_USB0_MOCK_UTMI_DIV_CWK_SWC] = &gcc_usb0_mock_utmi_div_cwk_swc.cwkw,
	[GCC_USB0_PHY_CFG_AHB_CWK] = &gcc_usb0_phy_cfg_ahb_cwk.cwkw,
	[GCC_USB0_PIPE_CWK] = &gcc_usb0_pipe_cwk.cwkw,
	[GCC_USB0_SWEEP_CWK] = &gcc_usb0_sweep_cwk.cwkw,
	[GCC_WCSS_AHB_CWK_SWC] = &gcc_wcss_ahb_cwk_swc.cwkw,
	[GCC_WCSS_AXIM_CWK] = &gcc_wcss_axim_cwk.cwkw,
	[GCC_WCSS_AXIS_CWK] = &gcc_wcss_axis_cwk.cwkw,
	[GCC_WCSS_DBG_IFC_APB_BDG_CWK] = &gcc_wcss_dbg_ifc_apb_bdg_cwk.cwkw,
	[GCC_WCSS_DBG_IFC_APB_CWK] = &gcc_wcss_dbg_ifc_apb_cwk.cwkw,
	[GCC_WCSS_DBG_IFC_ATB_BDG_CWK] = &gcc_wcss_dbg_ifc_atb_bdg_cwk.cwkw,
	[GCC_WCSS_DBG_IFC_ATB_CWK] = &gcc_wcss_dbg_ifc_atb_cwk.cwkw,
	[GCC_WCSS_DBG_IFC_NTS_BDG_CWK] = &gcc_wcss_dbg_ifc_nts_bdg_cwk.cwkw,
	[GCC_WCSS_DBG_IFC_NTS_CWK] = &gcc_wcss_dbg_ifc_nts_cwk.cwkw,
	[GCC_WCSS_ECAHB_CWK] = &gcc_wcss_ecahb_cwk.cwkw,
	[GCC_WCSS_MST_ASYNC_BDG_CWK] = &gcc_wcss_mst_async_bdg_cwk.cwkw,
	[GCC_WCSS_SWV_ASYNC_BDG_CWK] = &gcc_wcss_swv_async_bdg_cwk.cwkw,
	[GCC_XO_CWK] = &gcc_xo_cwk.cwkw,
	[GCC_XO_CWK_SWC] = &gcc_xo_cwk_swc.cwkw,
	[GCC_XO_DIV4_CWK] = &gcc_xo_div4_cwk.cwkw,
	[GCC_IM_SWEEP_CWK] = &gcc_im_sweep_cwk.cwkw,
	[GCC_NSSNOC_PCNOC_1_CWK] = &gcc_nssnoc_pcnoc_1_cwk.cwkw,
	[GCC_SNOC_QOSGEN_EXTWEF_DIV_CWK_SWC] = &gcc_snoc_qosgen_extwef_div_cwk_swc.cwkw,
	[GCC_PCIE3X2_PIPE_CWK_SWC] = &gcc_pcie3x2_pipe_cwk_swc.cwkw,
	[GCC_PCIE3X1_0_PIPE_CWK_SWC] = &gcc_pcie3x1_0_pipe_cwk_swc.cwkw,
	[GCC_PCIE3X1_1_PIPE_CWK_SWC] = &gcc_pcie3x1_1_pipe_cwk_swc.cwkw,
	[GCC_USB0_PIPE_CWK_SWC] = &gcc_usb0_pipe_cwk_swc.cwkw,
};

static const stwuct qcom_weset_map gcc_ipq5332_wesets[] = {
	[GCC_ADSS_BCW] = { 0x1c000 },
	[GCC_ADSS_PWM_CWK_AWES] = { 0x1c00c, 2 },
	[GCC_AHB_CWK_AWES] = { 0x34024, 2 },
	[GCC_APC0_VOWTAGE_DWOOP_DETECTOW_BCW] = { 0x38000 },
	[GCC_APC0_VOWTAGE_DWOOP_DETECTOW_GPWW0_CWK_AWES] = { 0x3800c, 2 },
	[GCC_APSS_AHB_CWK_AWES] = { 0x24018, 2 },
	[GCC_APSS_AXI_CWK_AWES] = { 0x2401c, 2 },
	[GCC_BWSP1_AHB_CWK_AWES] = { 0x1008, 2 },
	[GCC_BWSP1_BCW] = { 0x1000 },
	[GCC_BWSP1_QUP1_BCW] = { 0x2000 },
	[GCC_BWSP1_QUP1_I2C_APPS_CWK_AWES] = { 0x2024, 2 },
	[GCC_BWSP1_QUP1_SPI_APPS_CWK_AWES] = { 0x2020, 2 },
	[GCC_BWSP1_QUP2_BCW] = { 0x3000 },
	[GCC_BWSP1_QUP2_I2C_APPS_CWK_AWES] = { 0x3024, 2 },
	[GCC_BWSP1_QUP2_SPI_APPS_CWK_AWES] = { 0x3020, 2 },
	[GCC_BWSP1_QUP3_BCW] = { 0x4000 },
	[GCC_BWSP1_QUP3_I2C_APPS_CWK_AWES] = { 0x4024, 2 },
	[GCC_BWSP1_QUP3_SPI_APPS_CWK_AWES] = { 0x4020, 2 },
	[GCC_BWSP1_SWEEP_CWK_AWES] = { 0x1010, 2 },
	[GCC_BWSP1_UAWT1_APPS_CWK_AWES] = { 0x2040, 2 },
	[GCC_BWSP1_UAWT1_BCW] = { 0x2028 },
	[GCC_BWSP1_UAWT2_APPS_CWK_AWES] = { 0x3040, 2 },
	[GCC_BWSP1_UAWT2_BCW] = { 0x3028 },
	[GCC_BWSP1_UAWT3_APPS_CWK_AWES] = { 0x4054, 2 },
	[GCC_BWSP1_UAWT3_BCW] = { 0x4028 },
	[GCC_CE_BCW] = { 0x18008 },
	[GCC_CMN_BWK_BCW] = { 0x3a000 },
	[GCC_CMN_WDO0_BCW] = { 0x1d000 },
	[GCC_CMN_WDO1_BCW] = { 0x1d008 },
	[GCC_DCC_BCW] = { 0x35000 },
	[GCC_GP1_CWK_AWES] = { 0x8018, 2 },
	[GCC_GP2_CWK_AWES] = { 0x9018, 2 },
	[GCC_WPASS_BCW] = { 0x27000 },
	[GCC_WPASS_COWE_AXIM_CWK_AWES] = { 0x27018, 2 },
	[GCC_WPASS_SWAY_CWK_AWES] = { 0x27014, 2 },
	[GCC_MDIOM_BCW] = { 0x12000 },
	[GCC_MDIOS_BCW] = { 0x12008 },
	[GCC_NSS_BCW] = { 0x17000 },
	[GCC_NSS_TS_CWK_AWES] = { 0x17018, 2 },
	[GCC_NSSCC_CWK_AWES] = { 0x17034, 2 },
	[GCC_NSSCFG_CWK_AWES] = { 0x1702c, 2 },
	[GCC_NSSNOC_ATB_CWK_AWES] = { 0x17014, 2 },
	[GCC_NSSNOC_NSSCC_CWK_AWES] = { 0x17030, 2 },
	[GCC_NSSNOC_QOSGEN_WEF_CWK_AWES] = { 0x1701c, 2 },
	[GCC_NSSNOC_SNOC_1_CWK_AWES] = { 0x1707c, 2 },
	[GCC_NSSNOC_SNOC_CWK_AWES] = { 0x17028, 2 },
	[GCC_NSSNOC_TIMEOUT_WEF_CWK_AWES] = { 0x17020, 2 },
	[GCC_NSSNOC_XO_DCD_CWK_AWES] = { 0x17074, 2 },
	[GCC_PCIE3X1_0_AHB_CWK_AWES] = { 0x29030, 2 },
	[GCC_PCIE3X1_0_AUX_CWK_AWES] = { 0x29070, 2 },
	[GCC_PCIE3X1_0_AXI_M_CWK_AWES] = { 0x29038, 2 },
	[GCC_PCIE3X1_0_AXI_S_BWIDGE_CWK_AWES] = { 0x29048, 2 },
	[GCC_PCIE3X1_0_AXI_S_CWK_AWES] = { 0x29040, 2 },
	[GCC_PCIE3X1_0_BCW] = { 0x29000 },
	[GCC_PCIE3X1_0_WINK_DOWN_BCW] = { 0x29054 },
	[GCC_PCIE3X1_0_PHY_BCW] = { 0x29060 },
	[GCC_PCIE3X1_0_PHY_PHY_BCW] = { 0x2905c },
	[GCC_PCIE3X1_1_AHB_CWK_AWES] = { 0x2a00c, 2 },
	[GCC_PCIE3X1_1_AUX_CWK_AWES] = { 0x2a070, 2 },
	[GCC_PCIE3X1_1_AXI_M_CWK_AWES] = { 0x2a014, 2 },
	[GCC_PCIE3X1_1_AXI_S_BWIDGE_CWK_AWES] = { 0x2a024, 2 },
	[GCC_PCIE3X1_1_AXI_S_CWK_AWES] = { 0x2a01c, 2 },
	[GCC_PCIE3X1_1_BCW] = { 0x2a000 },
	[GCC_PCIE3X1_1_WINK_DOWN_BCW] = { 0x2a028 },
	[GCC_PCIE3X1_1_PHY_BCW] = { 0x2a030 },
	[GCC_PCIE3X1_1_PHY_PHY_BCW] = { 0x2a02c },
	[GCC_PCIE3X1_PHY_AHB_CWK_AWES] = { 0x29078, 2 },
	[GCC_PCIE3X2_AHB_CWK_AWES] = { 0x28030, 2 },
	[GCC_PCIE3X2_AUX_CWK_AWES] = { 0x28070, 2 },
	[GCC_PCIE3X2_AXI_M_CWK_AWES] = { 0x28038, 2 },
	[GCC_PCIE3X2_AXI_S_BWIDGE_CWK_AWES] = { 0x28048, 2 },
	[GCC_PCIE3X2_AXI_S_CWK_AWES] = { 0x28040, 2 },
	[GCC_PCIE3X2_BCW] = { 0x28000 },
	[GCC_PCIE3X2_WINK_DOWN_BCW] = { 0x28054 },
	[GCC_PCIE3X2_PHY_AHB_CWK_AWES] = { 0x28080, 2 },
	[GCC_PCIE3X2_PHY_BCW] = { 0x28060 },
	[GCC_PCIE3X2PHY_PHY_BCW] = { 0x2805c },
	[GCC_PCNOC_BCW] = { 0x31000 },
	[GCC_PCNOC_WPASS_CWK_AWES] = { 0x31020, 2 },
	[GCC_PWNG_AHB_CWK_AWES] = { 0x13024, 2 },
	[GCC_PWNG_BCW] = { 0x13020 },
	[GCC_Q6_AHB_CWK_AWES] = { 0x25014, 2 },
	[GCC_Q6_AHB_S_CWK_AWES] = { 0x25018, 2 },
	[GCC_Q6_AXIM_CWK_AWES] = { 0x2500c, 2 },
	[GCC_Q6_AXIS_CWK_AWES] = { 0x25010, 2 },
	[GCC_Q6_TSCTW_1TO2_CWK_AWES] = { 0x25020, 2 },
	[GCC_Q6SS_ATBM_CWK_AWES] = { 0x2501c, 2 },
	[GCC_Q6SS_PCWKDBG_CWK_AWES] = { 0x25024, 2 },
	[GCC_Q6SS_TWIG_CWK_AWES] = { 0x250a0, 2 },
	[GCC_QDSS_APB2JTAG_CWK_AWES] = { 0x2d060, 2 },
	[GCC_QDSS_AT_CWK_AWES] = { 0x2d038, 2 },
	[GCC_QDSS_BCW] = { 0x2d000 },
	[GCC_QDSS_CFG_AHB_CWK_AWES] = { 0x2d06c, 2 },
	[GCC_QDSS_DAP_AHB_CWK_AWES] = { 0x2d068, 2 },
	[GCC_QDSS_DAP_CWK_AWES] = { 0x2d05c, 2 },
	[GCC_QDSS_ETW_USB_CWK_AWES] = { 0x2d064, 2 },
	[GCC_QDSS_EUD_AT_CWK_AWES] = { 0x2d070, 2 },
	[GCC_QDSS_STM_CWK_AWES] = { 0x2d040, 2 },
	[GCC_QDSS_TWACECWKIN_CWK_AWES] = { 0x2d044, 2 },
	[GCC_QDSS_TS_CWK_AWES] = { 0x2d078, 2 },
	[GCC_QDSS_TSCTW_DIV16_CWK_AWES] = { 0x2d058, 2 },
	[GCC_QDSS_TSCTW_DIV2_CWK_AWES] = { 0x2d048, 2 },
	[GCC_QDSS_TSCTW_DIV3_CWK_AWES] = { 0x2d04c, 2 },
	[GCC_QDSS_TSCTW_DIV4_CWK_AWES] = { 0x2d050, 2 },
	[GCC_QDSS_TSCTW_DIV8_CWK_AWES] = { 0x2d054, 2 },
	[GCC_QPIC_AHB_CWK_AWES] = { 0x32010, 2 },
	[GCC_QPIC_CWK_AWES] = { 0x32014, 2 },
	[GCC_QPIC_BCW] = { 0x32000 },
	[GCC_QPIC_IO_MACWO_CWK_AWES] = { 0x3200c, 2 },
	[GCC_QPIC_SWEEP_CWK_AWES] = { 0x3201c, 2 },
	[GCC_QUSB2_0_PHY_BCW] = { 0x2c068 },
	[GCC_SDCC1_AHB_CWK_AWES] = { 0x33034, 2 },
	[GCC_SDCC1_APPS_CWK_AWES] = { 0x3302c, 2 },
	[GCC_SDCC_BCW] = { 0x33000 },
	[GCC_SNOC_BCW] = { 0x2e000 },
	[GCC_SNOC_WPASS_CFG_CWK_AWES] = { 0x2e028, 2 },
	[GCC_SNOC_NSSNOC_1_CWK_AWES] = { 0x17090, 2 },
	[GCC_SNOC_NSSNOC_CWK_AWES] = { 0x17084, 2 },
	[GCC_SYS_NOC_QDSS_STM_AXI_CWK_AWES] = { 0x2e034, 2 },
	[GCC_SYS_NOC_WCSS_AHB_CWK_AWES] = { 0x2e030, 2 },
	[GCC_UNIPHY0_AHB_CWK_AWES] = { 0x16010, 2 },
	[GCC_UNIPHY0_BCW] = { 0x16000 },
	[GCC_UNIPHY0_SYS_CWK_AWES] = { 0x1600c, 2 },
	[GCC_UNIPHY1_AHB_CWK_AWES] = { 0x1601c, 2 },
	[GCC_UNIPHY1_BCW] = { 0x16014 },
	[GCC_UNIPHY1_SYS_CWK_AWES] = { 0x16018, 2 },
	[GCC_USB0_AUX_CWK_AWES] = { 0x2c050, 2 },
	[GCC_USB0_EUD_AT_CWK_AWES] = { 0x30004, 2 },
	[GCC_USB0_WFPS_CWK_AWES] = { 0x2c090, 2 },
	[GCC_USB0_MASTEW_CWK_AWES] = { 0x2c048, 2 },
	[GCC_USB0_MOCK_UTMI_CWK_AWES] = { 0x2c054, 2 },
	[GCC_USB0_PHY_BCW] = { 0x2c06c },
	[GCC_USB0_PHY_CFG_AHB_CWK_AWES] = { 0x2c05c, 2 },
	[GCC_USB0_SWEEP_CWK_AWES] = { 0x2c058, 2 },
	[GCC_USB3PHY_0_PHY_BCW] = { 0x2c070 },
	[GCC_USB_BCW] = { 0x2c000 },
	[GCC_WCSS_AXIM_CWK_AWES] = { 0x2505c, 2 },
	[GCC_WCSS_AXIS_CWK_AWES] = { 0x25060, 2 },
	[GCC_WCSS_BCW] = { 0x18004 },
	[GCC_WCSS_DBG_IFC_APB_BDG_CWK_AWES] = { 0x25048, 2 },
	[GCC_WCSS_DBG_IFC_APB_CWK_AWES] = { 0x25038, 2 },
	[GCC_WCSS_DBG_IFC_ATB_BDG_CWK_AWES] = { 0x2504c, 2 },
	[GCC_WCSS_DBG_IFC_ATB_CWK_AWES] = { 0x2503c, 2 },
	[GCC_WCSS_DBG_IFC_NTS_BDG_CWK_AWES] = { 0x25050, 2 },
	[GCC_WCSS_DBG_IFC_NTS_CWK_AWES] = { 0x25040, 2 },
	[GCC_WCSS_ECAHB_CWK_AWES] = { 0x25058, 2 },
	[GCC_WCSS_MST_ASYNC_BDG_CWK_AWES] = { 0x2e0b0, 2 },
	[GCC_WCSS_Q6_BCW] = { 0x18000 },
	[GCC_WCSS_SWV_ASYNC_BDG_CWK_AWES] = { 0x2e0b4, 2 },
	[GCC_XO_CWK_AWES] = { 0x34018, 2 },
	[GCC_XO_DIV4_CWK_AWES] = { 0x3401c, 2 },
	[GCC_Q6SS_DBG_AWES] = { 0x25094 },
	[GCC_WCSS_DBG_BDG_AWES] = { 0x25098, 0 },
	[GCC_WCSS_DBG_AWES] = { 0x25098, 1 },
	[GCC_WCSS_AXI_S_AWES] = { 0x25098, 2 },
	[GCC_WCSS_AXI_M_AWES] = { 0x25098, 3 },
	[GCC_WCSSAON_AWES] = { 0x2509C },
	[GCC_PCIE3X2_PIPE_AWES] = { 0x28058, 0 },
	[GCC_PCIE3X2_COWE_STICKY_AWES] = { 0x28058, 1 },
	[GCC_PCIE3X2_AXI_S_STICKY_AWES] = { 0x28058, 2 },
	[GCC_PCIE3X2_AXI_M_STICKY_AWES] = { 0x28058, 3 },
	[GCC_PCIE3X1_0_PIPE_AWES] = { 0x29058, 0 },
	[GCC_PCIE3X1_0_COWE_STICKY_AWES] = { 0x29058, 1 },
	[GCC_PCIE3X1_0_AXI_S_STICKY_AWES] = { 0x29058, 2 },
	[GCC_PCIE3X1_0_AXI_M_STICKY_AWES] = { 0x29058, 3 },
	[GCC_PCIE3X1_1_PIPE_AWES] = { 0x2a058, 0 },
	[GCC_PCIE3X1_1_COWE_STICKY_AWES] = { 0x2a058, 1 },
	[GCC_PCIE3X1_1_AXI_S_STICKY_AWES] = { 0x2a058, 2 },
	[GCC_PCIE3X1_1_AXI_M_STICKY_AWES] = { 0x2a058, 3 },
	[GCC_IM_SWEEP_CWK_AWES] = { 0x34020, 2 },
	[GCC_NSSNOC_PCNOC_1_CWK_AWES] = { 0x17080, 2 },
	[GCC_UNIPHY0_XPCS_AWES] = { 0x16050 },
	[GCC_UNIPHY1_XPCS_AWES] = { 0x16060 },
};

static const stwuct wegmap_config gcc_ipq5332_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x3f024,
	.fast_io = twue,
};

static stwuct cwk_hw *gcc_ipq5332_hws[] = {
	&gpww0_div2.hw,
	&gcc_xo_div4_cwk_swc.hw,
	&gcc_system_noc_bfdcd_div2_cwk_swc.hw,
	&gcc_qdss_tsctw_div2_cwk_swc.hw,
	&gcc_qdss_tsctw_div3_cwk_swc.hw,
	&gcc_qdss_tsctw_div4_cwk_swc.hw,
	&gcc_qdss_tsctw_div8_cwk_swc.hw,
	&gcc_qdss_tsctw_div16_cwk_swc.hw,
	&gcc_eud_at_div_cwk_swc.hw,
};

static const stwuct qcom_cc_desc gcc_ipq5332_desc = {
	.config = &gcc_ipq5332_wegmap_config,
	.cwks = gcc_ipq5332_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_ipq5332_cwocks),
	.wesets = gcc_ipq5332_wesets,
	.num_wesets = AWWAY_SIZE(gcc_ipq5332_wesets),
	.cwk_hws = gcc_ipq5332_hws,
	.num_cwk_hws = AWWAY_SIZE(gcc_ipq5332_hws),
};

static int gcc_ipq5332_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn qcom_cc_pwobe(pdev, &gcc_ipq5332_desc);
}

static const stwuct of_device_id gcc_ipq5332_match_tabwe[] = {
	{ .compatibwe = "qcom,ipq5332-gcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_ipq5332_match_tabwe);

static stwuct pwatfowm_dwivew gcc_ipq5332_dwivew = {
	.pwobe = gcc_ipq5332_pwobe,
	.dwivew = {
		.name = "gcc-ipq5332",
		.of_match_tabwe = gcc_ipq5332_match_tabwe,
	},
};

static int __init gcc_ipq5332_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_ipq5332_dwivew);
}
cowe_initcaww(gcc_ipq5332_init);

static void __exit gcc_ipq5332_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_ipq5332_dwivew);
}
moduwe_exit(gcc_ipq5332_exit);

MODUWE_DESCWIPTION("QTI GCC IPQ5332 Dwivew");
MODUWE_WICENSE("GPW");
