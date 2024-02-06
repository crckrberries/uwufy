// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gcc-sm8450.h>

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
	P_BI_TCXO,
	P_GCC_GPWW0_OUT_EVEN,
	P_GCC_GPWW0_OUT_MAIN,
	P_GCC_GPWW4_OUT_MAIN,
	P_GCC_GPWW9_OUT_MAIN,
	P_PCIE_1_PHY_AUX_CWK,
	P_SWEEP_CWK,
	P_UFS_PHY_WX_SYMBOW_0_CWK,
	P_UFS_PHY_WX_SYMBOW_1_CWK,
	P_UFS_PHY_TX_SYMBOW_0_CWK,
	P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK,
};

static stwuct cwk_awpha_pww gcc_gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gcc_gpww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gcc_gpww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_gcc_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gcc_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static stwuct cwk_awpha_pww gcc_gpww4 = {
	.offset = 0x4000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww9 = {
	.offset = 0x9000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww9",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_SWEEP_CWK, 5 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk" },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_PCIE_1_PHY_AUX_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .fw_name = "pcie_1_phy_aux_cwk" },
	{ .fw_name = "bi_tcxo" },
};

static const stwuct pawent_map gcc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW9_OUT_MAIN, 2 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_7[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww9.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_UFS_PHY_WX_SYMBOW_0_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .fw_name = "ufs_phy_wx_symbow_0_cwk" },
	{ .fw_name = "bi_tcxo" },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_UFS_PHY_WX_SYMBOW_1_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .fw_name = "ufs_phy_wx_symbow_1_cwk" },
	{ .fw_name = "bi_tcxo" },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_UFS_PHY_TX_SYMBOW_0_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .fw_name = "ufs_phy_tx_symbow_0_cwk" },
	{ .fw_name = "bi_tcxo" },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .fw_name = "usb3_phy_wwappew_gcc_usb30_pipe_cwk" },
	{ .fw_name = "bi_tcxo" },
};

static stwuct cwk_wegmap_phy_mux gcc_pcie_0_pipe_cwk_swc = {
	.weg = 0x7b060,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_0_pipe_cwk",
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_pcie_1_phy_aux_cwk_swc = {
	.weg = 0x9d080,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_5,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_phy_aux_cwk_swc",
			.pawent_data = gcc_pawent_data_5,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_phy_mux gcc_pcie_1_pipe_cwk_swc = {
	.weg = 0x9d064,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_1_pipe_cwk",
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_ufs_phy_wx_symbow_0_cwk_swc = {
	.weg = 0x87060,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_8,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_0_cwk_swc",
			.pawent_data = gcc_pawent_data_8,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_ufs_phy_wx_symbow_1_cwk_swc = {
	.weg = 0x870d0,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_9,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_1_cwk_swc",
			.pawent_data = gcc_pawent_data_9,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_ufs_phy_tx_symbow_0_cwk_swc = {
	.weg = 0x87050,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_10,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_tx_symbow_0_cwk_swc",
			.pawent_data = gcc_pawent_data_10,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_usb3_pwim_phy_pipe_cwk_swc = {
	.weg = 0x49068,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_11,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk_swc",
			.pawent_data = gcc_pawent_data_11,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(50000000, P_GCC_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	F(200000000, P_GCC_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x74004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x75004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x76004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_aux_cwk_swc = {
	.cmd_wcgw = 0x7b064,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_0_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_phy_wchng_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_phy_wchng_cwk_swc = {
	.cmd_wcgw = 0x7b048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_phy_wchng_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_0_phy_wchng_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie_1_aux_cwk_swc = {
	.cmd_wcgw = 0x9d068,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_1_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie_1_phy_wchng_cwk_swc = {
	.cmd_wcgw = 0x9d04c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_phy_wchng_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_1_phy_wchng_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(60000000, P_GCC_GPWW0_OUT_MAIN, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pdm2_cwk_swc = {
	.cmd_wcgw = 0x43010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pdm2_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pdm2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s0_cwk_swc[] = {
	F(7372800, P_GCC_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 25),
	F(64000000, P_GCC_GPWW0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s0_cwk_swc = {
	.cmd_wcgw = 0x27014,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s1_cwk_swc = {
	.cmd_wcgw = 0x27148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s2_cwk_swc = {
	.cmd_wcgw = 0x2727c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s3_cwk_swc = {
	.cmd_wcgw = 0x273b0,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s4_cwk_swc = {
	.cmd_wcgw = 0x274e4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s4_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s5_cwk_swc[] = {
	F(7372800, P_GCC_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 75),
	F(37500000, P_GCC_GPWW0_OUT_EVEN, 8, 0, 0),
	F(48000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 25),
	F(50000000, P_GCC_GPWW0_OUT_MAIN, 12, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s5_cwk_swc = {
	.cmd_wcgw = 0x27618,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s5_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s6_cwk_swc = {
	.cmd_wcgw = 0x2774c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s6_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s7_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s7_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s7_cwk_swc = {
	.cmd_wcgw = 0x27880,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s7_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap1_s0_cwk_swc[] = {
	F(7372800, P_GCC_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 25),
	F(64000000, P_GCC_GPWW0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	F(102400000, P_GCC_GPWW0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GCC_GPWW0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GCC_GPWW0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GCC_GPWW0_OUT_MAIN, 5, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s0_cwk_swc = {
	.cmd_wcgw = 0x28014,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s1_cwk_swc = {
	.cmd_wcgw = 0x28148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s2_cwk_swc = {
	.cmd_wcgw = 0x2827c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s3_cwk_swc = {
	.cmd_wcgw = 0x283b0,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s4_cwk_swc = {
	.cmd_wcgw = 0x284e4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s5_cwk_swc = {
	.cmd_wcgw = 0x28618,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s6_cwk_swc = {
	.cmd_wcgw = 0x2874c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s6_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s0_cwk_swc = {
	.cmd_wcgw = 0x2e014,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s1_cwk_swc = {
	.cmd_wcgw = 0x2e148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s2_cwk_swc = {
	.cmd_wcgw = 0x2e27c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s3_cwk_swc = {
	.cmd_wcgw = 0x2e3b0,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s4_cwk_swc = {
	.cmd_wcgw = 0x2e4e4,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s5_cwk_swc = {
	.cmd_wcgw = 0x2e618,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s6_cwk_swc = {
	.cmd_wcgw = 0x2e74c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s6_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_sdcc2_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(25000000, P_GCC_GPWW0_OUT_EVEN, 12, 0, 0),
	F(50000000, P_GCC_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_EVEN, 3, 0, 0),
	F(202000000, P_GCC_GPWW9_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x24014,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_sdcc2_apps_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc4_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(25000000, P_GCC_GPWW0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc4_apps_cwk_swc = {
	.cmd_wcgw = 0x26014,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdcc4_apps_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc4_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_axi_cwk_swc[] = {
	F(25000000, P_GCC_GPWW0_OUT_EVEN, 12, 0, 0),
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GCC_GPWW0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GCC_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_axi_cwk_swc = {
	.cmd_wcgw = 0x8702c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_axi_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_ice_cowe_cwk_swc[] = {
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GCC_GPWW0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GCC_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x87074,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_ice_cowe_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_phy_aux_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x870a8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_ufs_phy_phy_aux_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_ufs_phy_unipwo_cowe_cwk_swc = {
	.cmd_wcgw = 0x8708c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_ice_cowe_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_unipwo_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mastew_cwk_swc[] = {
	F(66666667, P_GCC_GPWW0_OUT_EVEN, 4.5, 0, 0),
	F(133333333, P_GCC_GPWW0_OUT_MAIN, 4.5, 0, 0),
	F(200000000, P_GCC_GPWW0_OUT_MAIN, 3, 0, 0),
	F(240000000, P_GCC_GPWW0_OUT_MAIN, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mastew_cwk_swc = {
	.cmd_wcgw = 0x49028,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mastew_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x49040,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x4906c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.hw_cwk_ctww = twue,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc = {
	.weg = 0x49058,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch gcc_aggwe_noc_pcie_0_axi_cwk = {
	.hawt_weg = 0x7b08c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x7b08c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_noc_pcie_0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_noc_pcie_1_axi_cwk = {
	.hawt_weg = 0x9d098,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x9d098,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_noc_pcie_1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_ufs_phy_axi_cwk = {
	.hawt_weg = 0x870d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x870d4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x870d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_ufs_phy_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_ufs_phy_axi_hw_ctw_cwk = {
	.hawt_weg = 0x870d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x870d4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x870d4,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_ufs_phy_axi_hw_ctw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x49088,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x49088,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x49088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_usb3_pwim_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x48004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x48004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_hf_axi_cwk = {
	.hawt_weg = 0x36010,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x36010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x36010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_sf_axi_cwk = {
	.hawt_weg = 0x36018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x36018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x36018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_sf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_pcie_anoc_ahb_cwk = {
	.hawt_weg = 0x20030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x20030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cfg_noc_pcie_anoc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x49084,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x49084,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x49084,
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

static stwuct cwk_bwanch gcc_ddwss_gpu_axi_cwk = {
	.hawt_weg = 0x81154,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x81154,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x81154,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ddwss_gpu_axi_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ddwss_pcie_sf_tbu_cwk = {
	.hawt_weg = 0x9d094,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x9d094,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ddwss_pcie_sf_tbu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_hf_axi_cwk = {
	.hawt_weg = 0x3700c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x3700c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3700c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_sf_axi_cwk = {
	.hawt_weg = 0x37014,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x37014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x37014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_sf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eusb3_0_cwkwef_en = {
	.hawt_weg = 0x9c00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9c00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_eusb3_0_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x74000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x74000,
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
	.hawt_weg = 0x75000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x75000,
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
	.hawt_weg = 0x76000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x76000,
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

static stwuct cwk_bwanch gcc_gpu_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww0.cwkw.hw,
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
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww0_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_memnoc_gfx_cwk = {
	.hawt_weg = 0x81010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x81010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x81010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_memnoc_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_snoc_dvm_gfx_cwk = {
	.hawt_weg = 0x81018,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x81018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_snoc_dvm_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_aux_cwk = {
	.hawt_weg = 0x7b034,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_0_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cfg_ahb_cwk = {
	.hawt_weg = 0x7b030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x7b030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cwkwef_en = {
	.hawt_weg = 0x9c004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_mstw_axi_cwk = {
	.hawt_weg = 0x7b028,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_phy_wchng_cwk = {
	.hawt_weg = 0x7b044,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(22),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_phy_wchng_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_0_phy_wchng_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_pipe_cwk = {
	.hawt_weg = 0x7b03c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_0_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_axi_cwk = {
	.hawt_weg = 0x7b020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x7b020,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_q2a_axi_cwk = {
	.hawt_weg = 0x7b01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_q2a_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_aux_cwk = {
	.hawt_weg = 0x9d030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(29),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_1_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_cfg_ahb_cwk = {
	.hawt_weg = 0x9d02c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d02c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_cwkwef_en = {
	.hawt_weg = 0x9c008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9c008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_mstw_axi_cwk = {
	.hawt_weg = 0x9d024,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_phy_aux_cwk = {
	.hawt_weg = 0x9d038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(24),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_1_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_phy_wchng_cwk = {
	.hawt_weg = 0x9d048,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(23),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_phy_wchng_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_1_phy_wchng_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_pipe_cwk = {
	.hawt_weg = 0x9d040,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(30),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_1_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_swv_axi_cwk = {
	.hawt_weg = 0x9d01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d01c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_swv_q2a_axi_cwk = {
	.hawt_weg = 0x9d018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_q2a_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x4300c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4300c,
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
	.hawt_weg = 0x43004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x43004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x43004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_xo4_cwk = {
	.hawt_weg = 0x43008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x43008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_xo4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_camewa_nwt_ahb_cwk = {
	.hawt_weg = 0x36008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x36008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x36008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_nwt_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_camewa_wt_ahb_cwk = {
	.hawt_weg = 0x3600c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3600c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_wt_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_disp_ahb_cwk = {
	.hawt_weg = 0x37008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x37008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x37008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_disp_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_gpu_ahb_cwk = {
	.hawt_weg = 0x81008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x81008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x81008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_gpu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_pcie_ahb_cwk = {
	.hawt_weg = 0x7b018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x7b018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7b018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_pcie_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_cv_cpu_ahb_cwk = {
	.hawt_weg = 0x42014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x42014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x42014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_cv_cpu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_cvp_ahb_cwk = {
	.hawt_weg = 0x42008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x42008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x42008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_cvp_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_v_cpu_ahb_cwk = {
	.hawt_weg = 0x42010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x42010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x42010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_v_cpu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_vcodec_ahb_cwk = {
	.hawt_weg = 0x4200c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x4200c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x4200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_vcodec_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_2x_cwk = {
	.hawt_weg = 0x3300c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_cwk = {
	.hawt_weg = 0x33000,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s0_cwk = {
	.hawt_weg = 0x2700c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
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
	.hawt_weg = 0x27140,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
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
	.hawt_weg = 0x27274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
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
	.hawt_weg = 0x273a8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
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
	.hawt_weg = 0x274dc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
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
	.hawt_weg = 0x27610,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
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

static stwuct cwk_bwanch gcc_qupv3_wwap0_s6_cwk = {
	.hawt_weg = 0x27744,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s7_cwk = {
	.hawt_weg = 0x27878,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap0_s7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap0_s7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_2x_cwk = {
	.hawt_weg = 0x3314c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(18),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_cwk = {
	.hawt_weg = 0x33140,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s0_cwk = {
	.hawt_weg = 0x2800c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(22),
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
	.hawt_weg = 0x28140,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(23),
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
	.hawt_weg = 0x28274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(24),
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
	.hawt_weg = 0x283a8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(25),
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
	.hawt_weg = 0x284dc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(26),
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
	.hawt_weg = 0x28610,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(27),
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

static stwuct cwk_bwanch gcc_qupv3_wwap1_s6_cwk = {
	.hawt_weg = 0x28744,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_cowe_2x_cwk = {
	.hawt_weg = 0x3328c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_cowe_cwk = {
	.hawt_weg = 0x33280,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s0_cwk = {
	.hawt_weg = 0x2e00c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s1_cwk = {
	.hawt_weg = 0x2e140,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s2_cwk = {
	.hawt_weg = 0x2e274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s3_cwk = {
	.hawt_weg = 0x2e3a8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s4_cwk = {
	.hawt_weg = 0x2e4dc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s5_cwk = {
	.hawt_weg = 0x2e610,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s6_cwk = {
	.hawt_weg = 0x2e744,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_0_m_ahb_cwk = {
	.hawt_weg = 0x27004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x27004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_0_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_0_s_ahb_cwk = {
	.hawt_weg = 0x27008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x27008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_0_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_m_ahb_cwk = {
	.hawt_weg = 0x28004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x28004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_s_ahb_cwk = {
	.hawt_weg = 0x28008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x28008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(21),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_2_m_ahb_cwk = {
	.hawt_weg = 0x2e004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2e004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_2_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_2_s_ahb_cwk = {
	.hawt_weg = 0x2e008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2e008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_2_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x2400c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2400c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_apps_cwk = {
	.hawt_weg = 0x24004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x24004,
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

static stwuct cwk_bwanch gcc_sdcc2_at_cwk = {
	.hawt_weg = 0x24010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x24010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x24010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_at_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_ahb_cwk = {
	.hawt_weg = 0x2600c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_apps_cwk = {
	.hawt_weg = 0x26004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x26004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_at_cwk = {
	.hawt_weg = 0x26010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x26010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x26010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_at_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_0_cwkwef_en = {
	.hawt_weg = 0x9c000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9c000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_0_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_ahb_cwk = {
	.hawt_weg = 0x87020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x87020,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x87020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_axi_cwk = {
	.hawt_weg = 0x87018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x87018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x87018,
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

static stwuct cwk_bwanch gcc_ufs_phy_axi_hw_ctw_cwk = {
	.hawt_weg = 0x87018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x87018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x87018,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_axi_hw_ctw_cwk",
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
	.hawt_weg = 0x8706c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8706c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x8706c,
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

static stwuct cwk_bwanch gcc_ufs_phy_ice_cowe_hw_ctw_cwk = {
	.hawt_weg = 0x8706c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8706c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x8706c,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ice_cowe_hw_ctw_cwk",
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
	.hawt_weg = 0x870a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x870a4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x870a4,
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

static stwuct cwk_bwanch gcc_ufs_phy_phy_aux_hw_ctw_cwk = {
	.hawt_weg = 0x870a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x870a4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x870a4,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_phy_aux_hw_ctw_cwk",
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
	.hawt_weg = 0x87028,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x87028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_wx_symbow_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_wx_symbow_1_cwk = {
	.hawt_weg = 0x870c0,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x870c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_wx_symbow_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_tx_symbow_0_cwk = {
	.hawt_weg = 0x87024,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x87024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_tx_symbow_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_ufs_phy_tx_symbow_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_unipwo_cowe_cwk = {
	.hawt_weg = 0x87064,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x87064,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x87064,
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

static stwuct cwk_bwanch gcc_ufs_phy_unipwo_cowe_hw_ctw_cwk = {
	.hawt_weg = 0x87064,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x87064,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x87064,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_unipwo_cowe_hw_ctw_cwk",
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
	.hawt_weg = 0x49018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49018,
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
	.hawt_weg = 0x49024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49024,
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
	.hawt_weg = 0x49020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_0_cwkwef_en = {
	.hawt_weg = 0x9c010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9c010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_0_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_aux_cwk = {
	.hawt_weg = 0x4905c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4905c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb3_pwim_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_com_aux_cwk = {
	.hawt_weg = 0x49060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49060,
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
	.hawt_weg = 0x49064,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x49064,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x49064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_usb3_pwim_phy_pipe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_axi0_cwk = {
	.hawt_weg = 0x42018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x42018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x42018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_axi1_cwk = {
	.hawt_weg = 0x42020,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x42020,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x42020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc pcie_0_gdsc = {
	.gdscw = 0x7b004,
	.pd = {
		.name = "pcie_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc pcie_1_gdsc = {
	.gdscw = 0x9d004,
	.pd = {
		.name = "pcie_1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ufs_phy_gdsc = {
	.gdscw = 0x87004,
	.pd = {
		.name = "ufs_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0x49004,
	.pd = {
		.name = "usb30_pwim_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *gcc_sm8450_cwocks[] = {
	[GCC_AGGWE_NOC_PCIE_0_AXI_CWK] = &gcc_aggwe_noc_pcie_0_axi_cwk.cwkw,
	[GCC_AGGWE_NOC_PCIE_1_AXI_CWK] = &gcc_aggwe_noc_pcie_1_axi_cwk.cwkw,
	[GCC_AGGWE_UFS_PHY_AXI_CWK] = &gcc_aggwe_ufs_phy_axi_cwk.cwkw,
	[GCC_AGGWE_UFS_PHY_AXI_HW_CTW_CWK] = &gcc_aggwe_ufs_phy_axi_hw_ctw_cwk.cwkw,
	[GCC_AGGWE_USB3_PWIM_AXI_CWK] = &gcc_aggwe_usb3_pwim_axi_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAMEWA_HF_AXI_CWK] = &gcc_camewa_hf_axi_cwk.cwkw,
	[GCC_CAMEWA_SF_AXI_CWK] = &gcc_camewa_sf_axi_cwk.cwkw,
	[GCC_CFG_NOC_PCIE_ANOC_AHB_CWK] = &gcc_cfg_noc_pcie_anoc_ahb_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_DDWSS_GPU_AXI_CWK] = &gcc_ddwss_gpu_axi_cwk.cwkw,
	[GCC_DDWSS_PCIE_SF_TBU_CWK] = &gcc_ddwss_pcie_sf_tbu_cwk.cwkw,
	[GCC_DISP_HF_AXI_CWK] = &gcc_disp_hf_axi_cwk.cwkw,
	[GCC_DISP_SF_AXI_CWK] = &gcc_disp_sf_axi_cwk.cwkw,
	[GCC_EUSB3_0_CWKWEF_EN] = &gcc_eusb3_0_cwkwef_en.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPWW0] = &gcc_gpww0.cwkw,
	[GCC_GPWW0_OUT_EVEN] = &gcc_gpww0_out_even.cwkw,
	[GCC_GPWW4] = &gcc_gpww4.cwkw,
	[GCC_GPWW9] = &gcc_gpww9.cwkw,
	[GCC_GPU_GPWW0_CWK_SWC] = &gcc_gpu_gpww0_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_DIV_CWK_SWC] = &gcc_gpu_gpww0_div_cwk_swc.cwkw,
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK] = &gcc_pcie_0_aux_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK_SWC] = &gcc_pcie_0_aux_cwk_swc.cwkw,
	[GCC_PCIE_0_CFG_AHB_CWK] = &gcc_pcie_0_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_0_CWKWEF_EN] = &gcc_pcie_0_cwkwef_en.cwkw,
	[GCC_PCIE_0_MSTW_AXI_CWK] = &gcc_pcie_0_mstw_axi_cwk.cwkw,
	[GCC_PCIE_0_PHY_WCHNG_CWK] = &gcc_pcie_0_phy_wchng_cwk.cwkw,
	[GCC_PCIE_0_PHY_WCHNG_CWK_SWC] = &gcc_pcie_0_phy_wchng_cwk_swc.cwkw,
	[GCC_PCIE_0_PIPE_CWK] = &gcc_pcie_0_pipe_cwk.cwkw,
	[GCC_PCIE_0_PIPE_CWK_SWC] = &gcc_pcie_0_pipe_cwk_swc.cwkw,
	[GCC_PCIE_0_SWV_AXI_CWK] = &gcc_pcie_0_swv_axi_cwk.cwkw,
	[GCC_PCIE_0_SWV_Q2A_AXI_CWK] = &gcc_pcie_0_swv_q2a_axi_cwk.cwkw,
	[GCC_PCIE_1_AUX_CWK] = &gcc_pcie_1_aux_cwk.cwkw,
	[GCC_PCIE_1_AUX_CWK_SWC] = &gcc_pcie_1_aux_cwk_swc.cwkw,
	[GCC_PCIE_1_CFG_AHB_CWK] = &gcc_pcie_1_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_1_CWKWEF_EN] = &gcc_pcie_1_cwkwef_en.cwkw,
	[GCC_PCIE_1_MSTW_AXI_CWK] = &gcc_pcie_1_mstw_axi_cwk.cwkw,
	[GCC_PCIE_1_PHY_AUX_CWK] = &gcc_pcie_1_phy_aux_cwk.cwkw,
	[GCC_PCIE_1_PHY_AUX_CWK_SWC] = &gcc_pcie_1_phy_aux_cwk_swc.cwkw,
	[GCC_PCIE_1_PHY_WCHNG_CWK] = &gcc_pcie_1_phy_wchng_cwk.cwkw,
	[GCC_PCIE_1_PHY_WCHNG_CWK_SWC] = &gcc_pcie_1_phy_wchng_cwk_swc.cwkw,
	[GCC_PCIE_1_PIPE_CWK] = &gcc_pcie_1_pipe_cwk.cwkw,
	[GCC_PCIE_1_PIPE_CWK_SWC] = &gcc_pcie_1_pipe_cwk_swc.cwkw,
	[GCC_PCIE_1_SWV_AXI_CWK] = &gcc_pcie_1_swv_axi_cwk.cwkw,
	[GCC_PCIE_1_SWV_Q2A_AXI_CWK] = &gcc_pcie_1_swv_q2a_axi_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_QMIP_CAMEWA_NWT_AHB_CWK] = &gcc_qmip_camewa_nwt_ahb_cwk.cwkw,
	[GCC_QMIP_CAMEWA_WT_AHB_CWK] = &gcc_qmip_camewa_wt_ahb_cwk.cwkw,
	[GCC_QMIP_DISP_AHB_CWK] = &gcc_qmip_disp_ahb_cwk.cwkw,
	[GCC_QMIP_GPU_AHB_CWK] = &gcc_qmip_gpu_ahb_cwk.cwkw,
	[GCC_QMIP_PCIE_AHB_CWK] = &gcc_qmip_pcie_ahb_cwk.cwkw,
	[GCC_QMIP_VIDEO_CV_CPU_AHB_CWK] = &gcc_qmip_video_cv_cpu_ahb_cwk.cwkw,
	[GCC_QMIP_VIDEO_CVP_AHB_CWK] = &gcc_qmip_video_cvp_ahb_cwk.cwkw,
	[GCC_QMIP_VIDEO_V_CPU_AHB_CWK] = &gcc_qmip_video_v_cpu_ahb_cwk.cwkw,
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
	[GCC_QUPV3_WWAP0_S6_CWK] = &gcc_qupv3_wwap0_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S6_CWK_SWC] = &gcc_qupv3_wwap0_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP0_S7_CWK] = &gcc_qupv3_wwap0_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP0_S7_CWK_SWC] = &gcc_qupv3_wwap0_s7_cwk_swc.cwkw,
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
	[GCC_QUPV3_WWAP1_S6_CWK] = &gcc_qupv3_wwap1_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S6_CWK_SWC] = &gcc_qupv3_wwap1_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_COWE_2X_CWK] = &gcc_qupv3_wwap2_cowe_2x_cwk.cwkw,
	[GCC_QUPV3_WWAP2_COWE_CWK] = &gcc_qupv3_wwap2_cowe_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S0_CWK] = &gcc_qupv3_wwap2_s0_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S0_CWK_SWC] = &gcc_qupv3_wwap2_s0_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_S1_CWK] = &gcc_qupv3_wwap2_s1_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S1_CWK_SWC] = &gcc_qupv3_wwap2_s1_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_S2_CWK] = &gcc_qupv3_wwap2_s2_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S2_CWK_SWC] = &gcc_qupv3_wwap2_s2_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_S3_CWK] = &gcc_qupv3_wwap2_s3_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S3_CWK_SWC] = &gcc_qupv3_wwap2_s3_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_S4_CWK] = &gcc_qupv3_wwap2_s4_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S4_CWK_SWC] = &gcc_qupv3_wwap2_s4_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_S5_CWK] = &gcc_qupv3_wwap2_s5_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S5_CWK_SWC] = &gcc_qupv3_wwap2_s5_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP2_S6_CWK] = &gcc_qupv3_wwap2_s6_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S6_CWK_SWC] = &gcc_qupv3_wwap2_s6_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP_0_M_AHB_CWK] = &gcc_qupv3_wwap_0_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_0_S_AHB_CWK] = &gcc_qupv3_wwap_0_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_M_AHB_CWK] = &gcc_qupv3_wwap_1_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_S_AHB_CWK] = &gcc_qupv3_wwap_1_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_2_M_AHB_CWK] = &gcc_qupv3_wwap_2_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_2_S_AHB_CWK] = &gcc_qupv3_wwap_2_s_ahb_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK_SWC] = &gcc_sdcc2_apps_cwk_swc.cwkw,
	[GCC_SDCC2_AT_CWK] = &gcc_sdcc2_at_cwk.cwkw,
	[GCC_SDCC4_AHB_CWK] = &gcc_sdcc4_ahb_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK] = &gcc_sdcc4_apps_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK_SWC] = &gcc_sdcc4_apps_cwk_swc.cwkw,
	[GCC_SDCC4_AT_CWK] = &gcc_sdcc4_at_cwk.cwkw,
	[GCC_UFS_0_CWKWEF_EN] = &gcc_ufs_0_cwkwef_en.cwkw,
	[GCC_UFS_PHY_AHB_CWK] = &gcc_ufs_phy_ahb_cwk.cwkw,
	[GCC_UFS_PHY_AXI_CWK] = &gcc_ufs_phy_axi_cwk.cwkw,
	[GCC_UFS_PHY_AXI_CWK_SWC] = &gcc_ufs_phy_axi_cwk_swc.cwkw,
	[GCC_UFS_PHY_AXI_HW_CTW_CWK] = &gcc_ufs_phy_axi_hw_ctw_cwk.cwkw,
	[GCC_UFS_PHY_ICE_COWE_CWK] = &gcc_ufs_phy_ice_cowe_cwk.cwkw,
	[GCC_UFS_PHY_ICE_COWE_CWK_SWC] = &gcc_ufs_phy_ice_cowe_cwk_swc.cwkw,
	[GCC_UFS_PHY_ICE_COWE_HW_CTW_CWK] = &gcc_ufs_phy_ice_cowe_hw_ctw_cwk.cwkw,
	[GCC_UFS_PHY_PHY_AUX_CWK] = &gcc_ufs_phy_phy_aux_cwk.cwkw,
	[GCC_UFS_PHY_PHY_AUX_CWK_SWC] = &gcc_ufs_phy_phy_aux_cwk_swc.cwkw,
	[GCC_UFS_PHY_PHY_AUX_HW_CTW_CWK] = &gcc_ufs_phy_phy_aux_hw_ctw_cwk.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_0_CWK] = &gcc_ufs_phy_wx_symbow_0_cwk.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_0_CWK_SWC] = &gcc_ufs_phy_wx_symbow_0_cwk_swc.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_1_CWK] = &gcc_ufs_phy_wx_symbow_1_cwk.cwkw,
	[GCC_UFS_PHY_WX_SYMBOW_1_CWK_SWC] = &gcc_ufs_phy_wx_symbow_1_cwk_swc.cwkw,
	[GCC_UFS_PHY_TX_SYMBOW_0_CWK] = &gcc_ufs_phy_tx_symbow_0_cwk.cwkw,
	[GCC_UFS_PHY_TX_SYMBOW_0_CWK_SWC] = &gcc_ufs_phy_tx_symbow_0_cwk_swc.cwkw,
	[GCC_UFS_PHY_UNIPWO_COWE_CWK] = &gcc_ufs_phy_unipwo_cowe_cwk.cwkw,
	[GCC_UFS_PHY_UNIPWO_COWE_CWK_SWC] = &gcc_ufs_phy_unipwo_cowe_cwk_swc.cwkw,
	[GCC_UFS_PHY_UNIPWO_COWE_HW_CTW_CWK] = &gcc_ufs_phy_unipwo_cowe_hw_ctw_cwk.cwkw,
	[GCC_USB30_PWIM_MASTEW_CWK] = &gcc_usb30_pwim_mastew_cwk.cwkw,
	[GCC_USB30_PWIM_MASTEW_CWK_SWC] = &gcc_usb30_pwim_mastew_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_CWK] = &gcc_usb30_pwim_mock_utmi_cwk.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_CWK_SWC] = &gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw,
	[GCC_USB30_PWIM_MOCK_UTMI_POSTDIV_CWK_SWC] = &gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc.cwkw,
	[GCC_USB30_PWIM_SWEEP_CWK] = &gcc_usb30_pwim_sweep_cwk.cwkw,
	[GCC_USB3_0_CWKWEF_EN] = &gcc_usb3_0_cwkwef_en.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK] = &gcc_usb3_pwim_phy_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK_SWC] = &gcc_usb3_pwim_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PWIM_PHY_COM_AUX_CWK] = &gcc_usb3_pwim_phy_com_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK] = &gcc_usb3_pwim_phy_pipe_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK_SWC] = &gcc_usb3_pwim_phy_pipe_cwk_swc.cwkw,
	[GCC_VIDEO_AXI0_CWK] = &gcc_video_axi0_cwk.cwkw,
	[GCC_VIDEO_AXI1_CWK] = &gcc_video_axi1_cwk.cwkw,
};

static const stwuct qcom_weset_map gcc_sm8450_wesets[] = {
	[GCC_CAMEWA_BCW] = { 0x36000 },
	[GCC_DISPWAY_BCW] = { 0x37000 },
	[GCC_GPU_BCW] = { 0x81000 },
	[GCC_PCIE_0_BCW] = { 0x7b000 },
	[GCC_PCIE_0_WINK_DOWN_BCW] = { 0x7c014 },
	[GCC_PCIE_0_NOCSW_COM_PHY_BCW] = { 0x7c020 },
	[GCC_PCIE_0_PHY_BCW] = { 0x7c01c },
	[GCC_PCIE_0_PHY_NOCSW_COM_PHY_BCW] = { 0x7c028 },
	[GCC_PCIE_1_BCW] = { 0x9d000 },
	[GCC_PCIE_1_WINK_DOWN_BCW] = { 0x9e014 },
	[GCC_PCIE_1_NOCSW_COM_PHY_BCW] = { 0x9e020 },
	[GCC_PCIE_1_PHY_BCW] = { 0x9e01c },
	[GCC_PCIE_1_PHY_NOCSW_COM_PHY_BCW] = { 0x9e000 },
	[GCC_PCIE_PHY_BCW] = { 0x7f000 },
	[GCC_PCIE_PHY_CFG_AHB_BCW] = { 0x7f00c },
	[GCC_PCIE_PHY_COM_BCW] = { 0x7f010 },
	[GCC_PDM_BCW] = { 0x43000 },
	[GCC_QUPV3_WWAPPEW_0_BCW] = { 0x27000 },
	[GCC_QUPV3_WWAPPEW_1_BCW] = { 0x28000 },
	[GCC_QUPV3_WWAPPEW_2_BCW] = { 0x2e000 },
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x22000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x22004 },
	[GCC_SDCC2_BCW] = { 0x24000 },
	[GCC_SDCC4_BCW] = { 0x26000 },
	[GCC_UFS_PHY_BCW] = { 0x87000 },
	[GCC_USB30_PWIM_BCW] = { 0x49000 },
	[GCC_USB3_DP_PHY_PWIM_BCW] = { 0x60008 },
	[GCC_USB3_DP_PHY_SEC_BCW] = { 0x60014 },
	[GCC_USB3_PHY_PWIM_BCW] = { 0x60000 },
	[GCC_USB3_PHY_SEC_BCW] = { 0x6000c },
	[GCC_USB3PHY_PHY_PWIM_BCW] = { 0x60004 },
	[GCC_USB3PHY_PHY_SEC_BCW] = { 0x60010 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x7a000 },
	[GCC_VIDEO_AXI0_CWK_AWES] = { 0x42018, 2 },
	[GCC_VIDEO_AXI1_CWK_AWES] = { 0x42020, 2 },
	[GCC_VIDEO_BCW] = { 0x42000 },
};

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
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s5_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s6_cwk_swc),
};

static stwuct gdsc *gcc_sm8450_gdscs[] = {
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_1_GDSC] = &pcie_1_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
};

static const stwuct wegmap_config gcc_sm8450_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x1f1030,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_sm8450_desc = {
	.config = &gcc_sm8450_wegmap_config,
	.cwks = gcc_sm8450_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sm8450_cwocks),
	.wesets = gcc_sm8450_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sm8450_wesets),
	.gdscs = gcc_sm8450_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sm8450_gdscs),
};

static const stwuct of_device_id gcc_sm8450_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-sm8450" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sm8450_match_tabwe);

static int gcc_sm8450_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_sm8450_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = qcom_cc_wegistew_wcg_dfs(wegmap, gcc_dfs_cwocks,
				       AWWAY_SIZE(gcc_dfs_cwocks));
	if (wet)
		wetuwn wet;

	/* FOWCE_MEM_COWE_ON fow ufs phy ice cowe cwocks */
	wegmap_update_bits(wegmap, gcc_ufs_phy_ice_cowe_cwk.hawt_weg, BIT(14), BIT(14));

	/*
	 * Keep the cwiticaw cwock awways-On
	 * gcc_camewa_ahb_cwk, gcc_camewa_xo_cwk, gcc_disp_ahb_cwk,
	 * gcc_disp_xo_cwk, gcc_gpu_cfg_ahb_cwk, gcc_video_ahb_cwk,
	 * gcc_video_xo_cwk
	 */
	wegmap_update_bits(wegmap, 0x36004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x36020, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x37004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x3701c, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x81004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x42004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x42028, BIT(0), BIT(0));

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sm8450_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sm8450_dwivew = {
	.pwobe = gcc_sm8450_pwobe,
	.dwivew = {
		.name = "gcc-sm8450",
		.of_match_tabwe = gcc_sm8450_match_tabwe,
	},
};

static int __init gcc_sm8450_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sm8450_dwivew);
}
subsys_initcaww(gcc_sm8450_init);

static void __exit gcc_sm8450_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sm8450_dwivew);
}
moduwe_exit(gcc_sm8450_exit);

MODUWE_DESCWIPTION("QTI GCC SM8450 Dwivew");
MODUWE_WICENSE("GPW v2");
