// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm8550-gcc.h>

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
	DT_SWEEP_CWK,
	DT_PCIE_0_PIPE,
	DT_PCIE_1_PIPE,
	DT_PCIE_1_PHY_AUX,
	DT_UFS_PHY_WX_SYMBOW_0,
	DT_UFS_PHY_WX_SYMBOW_1,
	DT_UFS_PHY_TX_SYMBOW_0,
	DT_USB3_PHY_WWAPPEW_GCC_USB30_PIPE,
};

enum {
	P_BI_TCXO,
	P_GCC_GPWW0_OUT_EVEN,
	P_GCC_GPWW0_OUT_MAIN,
	P_GCC_GPWW4_OUT_MAIN,
	P_GCC_GPWW7_OUT_MAIN,
	P_GCC_GPWW9_OUT_MAIN,
	P_PCIE_0_PIPE_CWK,
	P_PCIE_1_PHY_AUX_CWK,
	P_PCIE_1_PIPE_CWK,
	P_SWEEP_CWK,
	P_UFS_PHY_WX_SYMBOW_0_CWK,
	P_UFS_PHY_WX_SYMBOW_1_CWK,
	P_UFS_PHY_TX_SYMBOW_0_CWK,
	P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK,
};

static stwuct cwk_awpha_pww gcc_gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw = {
		.enabwe_weg = 0x52018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_owe_ops,
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
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_owe_ops,
	},
};

static stwuct cwk_awpha_pww gcc_gpww4 = {
	.offset = 0x4000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw = {
		.enabwe_weg = 0x52018,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_owe_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww7 = {
	.offset = 0x7000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw = {
		.enabwe_weg = 0x52018,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww7",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_owe_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww9 = {
	.offset = 0x9000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw = {
		.enabwe_weg = 0x52018,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpww9",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_owe_ops,
		},
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
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
	{ .index = DT_BI_TCXO },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .index = DT_SWEEP_CWK },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_SWEEP_CWK },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .index = DT_BI_TCXO },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_PCIE_1_PHY_AUX_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .index = DT_PCIE_1_PHY_AUX },
	{ .index = DT_BI_TCXO },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW7_OUT_MAIN, 2 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww7.cwkw.hw },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW9_OUT_MAIN, 2 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
	{ P_GCC_GPWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww9.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_UFS_PHY_WX_SYMBOW_0_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .index = DT_UFS_PHY_WX_SYMBOW_0 },
	{ .index = DT_BI_TCXO },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_UFS_PHY_WX_SYMBOW_1_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .index = DT_UFS_PHY_WX_SYMBOW_1 },
	{ .index = DT_BI_TCXO },
};

static const stwuct pawent_map gcc_pawent_map_12[] = {
	{ P_UFS_PHY_TX_SYMBOW_0_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_12[] = {
	{ .index = DT_UFS_PHY_TX_SYMBOW_0 },
	{ .index = DT_BI_TCXO },
};

static const stwuct pawent_map gcc_pawent_map_13[] = {
	{ P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_13[] = {
	{ .index = DT_USB3_PHY_WWAPPEW_GCC_USB30_PIPE },
	{ .index = DT_BI_TCXO },
};

static stwuct cwk_wegmap_phy_mux gcc_pcie_0_pipe_cwk_swc = {
	.weg = 0x6b070,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_PCIE_0_PIPE,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_pcie_1_phy_aux_cwk_swc = {
	.weg = 0x8d094,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_6,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_phy_aux_cwk_swc",
			.pawent_data = gcc_pawent_data_6,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_phy_mux gcc_pcie_1_pipe_cwk_swc = {
	.weg = 0x8d078,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_PCIE_1_PIPE,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_ufs_phy_wx_symbow_0_cwk_swc = {
	.weg = 0x77064,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_10,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_0_cwk_swc",
			.pawent_data = gcc_pawent_data_10,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_ufs_phy_wx_symbow_1_cwk_swc = {
	.weg = 0x770e0,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_11,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_wx_symbow_1_cwk_swc",
			.pawent_data = gcc_pawent_data_11,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_ufs_phy_tx_symbow_0_cwk_swc = {
	.weg = 0x77054,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_12,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_tx_symbow_0_cwk_swc",
			.pawent_data = gcc_pawent_data_12,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_12),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_usb3_pwim_phy_pipe_cwk_swc = {
	.weg = 0x3906c,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_13,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk_swc",
			.pawent_data = gcc_pawent_data_13,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_13),
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
	.cmd_wcgw = 0x64004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x65004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x66004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_aux_cwk_swc = {
	.cmd_wcgw = 0x6b074,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_0_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_phy_wchng_cwk_swc[] = {
	F(100000000, P_GCC_GPWW0_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_phy_wchng_cwk_swc = {
	.cmd_wcgw = 0x6b058,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_phy_wchng_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_0_phy_wchng_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie_1_aux_cwk_swc = {
	.cmd_wcgw = 0x8d07c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_1_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_pcie_1_phy_wchng_cwk_swc = {
	.cmd_wcgw = 0x8d060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_phy_wchng_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_pcie_1_phy_wchng_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(60000000, P_GCC_GPWW0_OUT_MAIN, 10, 0, 0),
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
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s0_cwk_swc = {
	.cmd_wcgw = 0x17008,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s0_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s1_cwk_swc = {
	.cmd_wcgw = 0x17024,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s1_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s2_cwk_swc = {
	.cmd_wcgw = 0x17040,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s3_cwk_swc = {
	.cmd_wcgw = 0x1705c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s3_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s4_cwk_swc = {
	.cmd_wcgw = 0x17078,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s4_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s5_cwk_swc = {
	.cmd_wcgw = 0x17094,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s5_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s6_cwk_swc = {
	.cmd_wcgw = 0x170b0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s6_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s7_cwk_swc = {
	.cmd_wcgw = 0x170cc,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s7_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s8_cwk_swc = {
	.cmd_wcgw = 0x170e8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s8_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_qupv3_i2c_s9_cwk_swc = {
	.cmd_wcgw = 0x17104,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_qupv3_i2c_s9_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap1_s0_cwk_swc[] = {
	F(7372800, P_GCC_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 25),
	F(51200000, P_GCC_GPWW0_OUT_EVEN, 1, 64, 375),
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
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s0_cwk_swc = {
	.cmd_wcgw = 0x18010,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s1_cwk_swc = {
	.cmd_wcgw = 0x18148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s1_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap1_s2_cwk_swc[] = {
	F(7372800, P_GCC_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 25),
	F(51200000, P_GCC_GPWW0_OUT_EVEN, 1, 64, 375),
	F(64000000, P_GCC_GPWW0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s2_cwk_swc = {
	.cmd_wcgw = 0x18280,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s3_cwk_swc = {
	.cmd_wcgw = 0x183b8,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s4_cwk_swc = {
	.cmd_wcgw = 0x184f0,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s5_cwk_swc = {
	.cmd_wcgw = 0x18628,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s6_cwk_swc = {
	.cmd_wcgw = 0x18760,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s6_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap1_s7_cwk_swc_init = {
	.name = "gcc_qupv3_wwap1_s7_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s7_cwk_swc = {
	.cmd_wcgw = 0x18898,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s7_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s0_cwk_swc = {
	.cmd_wcgw = 0x1e010,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s0_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s1_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s1_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s1_cwk_swc = {
	.cmd_wcgw = 0x1e148,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s1_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s2_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s2_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s2_cwk_swc = {
	.cmd_wcgw = 0x1e280,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s2_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s3_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s3_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s3_cwk_swc = {
	.cmd_wcgw = 0x1e3b8,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s3_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s4_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s4_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s4_cwk_swc = {
	.cmd_wcgw = 0x1e4f0,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s4_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s5_cwk_swc = {
	.cmd_wcgw = 0x1e628,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s5_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap2_s6_cwk_swc[] = {
	F(7372800, P_GCC_GPWW0_OUT_EVEN, 1, 384, 15625),
	F(14745600, P_GCC_GPWW0_OUT_EVEN, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GCC_GPWW0_OUT_EVEN, 1, 1536, 15625),
	F(32000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 75),
	F(48000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 25),
	F(51200000, P_GCC_GPWW0_OUT_EVEN, 1, 64, 375),
	F(64000000, P_GCC_GPWW0_OUT_EVEN, 1, 16, 75),
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(80000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	F(102400000, P_GCC_GPWW0_OUT_EVEN, 1, 128, 375),
	F(112000000, P_GCC_GPWW0_OUT_EVEN, 1, 28, 75),
	F(117964800, P_GCC_GPWW0_OUT_EVEN, 1, 6144, 15625),
	F(120000000, P_GCC_GPWW0_OUT_MAIN, 5, 0, 0),
	F(125000000, P_GCC_GPWW0_OUT_MAIN, 1, 5, 24),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_8,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s6_cwk_swc = {
	.cmd_wcgw = 0x1e760,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_qupv3_wwap2_s6_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s6_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap2_s7_cwk_swc_init = {
	.name = "gcc_qupv3_wwap2_s7_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.fwags = CWK_SET_WATE_PAWENT,
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap2_s7_cwk_swc = {
	.cmd_wcgw = 0x1e898,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap1_s2_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap2_s7_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_sdcc2_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(25000000, P_GCC_GPWW0_OUT_EVEN, 12, 0, 0),
	F(37500000, P_GCC_GPWW0_OUT_EVEN, 8, 0, 0),
	F(50000000, P_GCC_GPWW0_OUT_EVEN, 6, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_EVEN, 3, 0, 0),
	F(202000000, P_GCC_GPWW9_OUT_MAIN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x14018,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_gcc_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc4_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(25000000, P_GCC_GPWW0_OUT_EVEN, 12, 0, 0),
	F(37500000, P_GCC_GPWW0_OUT_EVEN, 8, 0, 0),
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc4_apps_cwk_swc = {
	.cmd_wcgw = 0x16018,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_sdcc4_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc4_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
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
	.cmd_wcgw = 0x77030,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_axi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_ice_cowe_cwk_swc[] = {
	F(100000000, P_GCC_GPWW0_OUT_EVEN, 3, 0, 0),
	F(201500000, P_GCC_GPWW4_OUT_MAIN, 4, 0, 0),
	F(403000000, P_GCC_GPWW4_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x77080,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_ufs_phy_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_phy_aux_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x770b4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_ufs_phy_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc[] = {
	F(75000000, P_GCC_GPWW0_OUT_EVEN, 4, 0, 0),
	F(150000000, P_GCC_GPWW0_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GCC_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_unipwo_cowe_cwk_swc = {
	.cmd_wcgw = 0x77098,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_ufs_phy_unipwo_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
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
	.cmd_wcgw = 0x3902c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_usb30_pwim_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x39044,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb30_pwim_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x39070,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wegmap_div gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc = {
	.weg = 0x3905c,
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

static stwuct cwk_bwanch gcc_aggwe_noc_pcie_axi_cwk = {
	.hawt_weg = 0x1003c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x1003c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe_noc_pcie_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_ufs_phy_axi_cwk = {
	.hawt_weg = 0x770e4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x770e4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x770e4,
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
	.hawt_weg = 0x770e4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x770e4,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x770e4,
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
	.hawt_weg = 0x3908c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3908c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3908c,
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
	.hawt_weg = 0x26010,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x26010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x26010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camewa_sf_axi_cwk = {
	.hawt_weg = 0x2601c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x2601c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x2601c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_sf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_pcie_anoc_ahb_cwk = {
	.hawt_weg = 0x10028,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x10028,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cfg_noc_pcie_anoc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x39088,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x39088,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x39088,
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

static stwuct cwk_bwanch gcc_cnoc_pcie_sf_axi_cwk = {
	.hawt_weg = 0x10030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x10030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cnoc_pcie_sf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ddwss_gpu_axi_cwk = {
	.hawt_weg = 0x71154,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x71154,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x71154,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ddwss_gpu_axi_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ddwss_pcie_sf_qtb_cwk = {
	.hawt_weg = 0x1004c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x1004c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(19),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ddwss_pcie_sf_qtb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_hf_axi_cwk = {
	.hawt_weg = 0x2700c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x2700c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x2700c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_hf_axi_cwk",
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
	.hawt_weg = 0x65000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x65000,
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
	.hawt_weg = 0x66000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x66000,
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
		.enabwe_weg = 0x52000,
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
		.enabwe_weg = 0x52000,
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
	.hawt_weg = 0x71010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x71010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x71010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_memnoc_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_snoc_dvm_gfx_cwk = {
	.hawt_weg = 0x71018,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x71018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_snoc_dvm_gfx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_aux_cwk = {
	.hawt_weg = 0x6b03c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x6b038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x6b038,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_mstw_axi_cwk = {
	.hawt_weg = 0x6b02c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x6b02c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_phy_wchng_cwk = {
	.hawt_weg = 0x6b054,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
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
	.hawt_weg = 0x6b048,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x6b020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x6b020,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_q2a_axi_cwk = {
	.hawt_weg = 0x6b01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_q2a_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_aux_cwk = {
	.hawt_weg = 0x8d038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
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
	.hawt_weg = 0x8d034,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8d034,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_mstw_axi_cwk = {
	.hawt_weg = 0x8d028,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x8d028,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_phy_aux_cwk = {
	.hawt_weg = 0x8d044,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
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
	.hawt_weg = 0x8d05c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
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
	.hawt_weg = 0x8d050,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x52000,
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
	.hawt_weg = 0x8d01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8d01c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_swv_q2a_axi_cwk = {
	.hawt_weg = 0x8d018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(25),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_q2a_axi_cwk",
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
	.hawt_weg = 0x33004,
	.hawt_check = BWANCH_HAWT_VOTED,
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

static stwuct cwk_bwanch gcc_qmip_camewa_nwt_ahb_cwk = {
	.hawt_weg = 0x26008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x26008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x26008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_nwt_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_camewa_wt_ahb_cwk = {
	.hawt_weg = 0x2600c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2600c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x2600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_camewa_wt_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_disp_ahb_cwk = {
	.hawt_weg = 0x27008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x27008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x27008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_disp_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_gpu_ahb_cwk = {
	.hawt_weg = 0x71008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x71008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x71008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_gpu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_pcie_ahb_cwk = {
	.hawt_weg = 0x6b018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x6b018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_pcie_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_cv_cpu_ahb_cwk = {
	.hawt_weg = 0x32014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x32014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x32014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_cv_cpu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_cvp_ahb_cwk = {
	.hawt_weg = 0x32008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x32008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x32008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_cvp_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_v_cpu_ahb_cwk = {
	.hawt_weg = 0x32010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x32010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x32010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_v_cpu_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_video_vcodec_ahb_cwk = {
	.hawt_weg = 0x3200c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3200c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qmip_video_vcodec_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_cowe_cwk = {
	.hawt_weg = 0x23144,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s0_cwk = {
	.hawt_weg = 0x17004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s1_cwk = {
	.hawt_weg = 0x17020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s2_cwk = {
	.hawt_weg = 0x1703c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s3_cwk = {
	.hawt_weg = 0x17058,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s4_cwk = {
	.hawt_weg = 0x17074,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s4_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s5_cwk = {
	.hawt_weg = 0x17090,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s5_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s6_cwk = {
	.hawt_weg = 0x170ac,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s6_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s7_cwk = {
	.hawt_weg = 0x170c8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s8_cwk = {
	.hawt_weg = 0x170e4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s8_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s8_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s9_cwk = {
	.hawt_weg = 0x17100,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s9_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_i2c_s9_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_i2c_s_ahb_cwk = {
	.hawt_weg = 0x23140,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x23140,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52008,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_i2c_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_2x_cwk = {
	.hawt_weg = 0x23294,
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
	.hawt_weg = 0x23284,
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
	.hawt_weg = 0x18004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x1813c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x18274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x183ac,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x184e4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x1861c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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
	.hawt_weg = 0x18754,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52008,
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

static stwuct cwk_bwanch gcc_qupv3_wwap1_s7_cwk = {
	.hawt_weg = 0x1888c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_s7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap1_s7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_cowe_2x_cwk = {
	.hawt_weg = 0x23004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_cowe_cwk = {
	.hawt_weg = 0x233d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap2_s0_cwk = {
	.hawt_weg = 0x1e004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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
	.hawt_weg = 0x1e13c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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
	.hawt_weg = 0x1e274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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
	.hawt_weg = 0x1e3ac,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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
	.hawt_weg = 0x1e4e4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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
	.hawt_weg = 0x1e61c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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
	.hawt_weg = 0x1e754,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
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

static stwuct cwk_bwanch gcc_qupv3_wwap2_s7_cwk = {
	.hawt_weg = 0x1e88c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap2_s7_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_qupv3_wwap2_s7_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_m_ahb_cwk = {
	.hawt_weg = 0x2327c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2327c,
	.hwcg_bit = 1,
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
	.hawt_weg = 0x23280,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x23280,
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

static stwuct cwk_bwanch gcc_qupv3_wwap_2_m_ahb_cwk = {
	.hawt_weg = 0x233cc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x233cc,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_2_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_2_s_ahb_cwk = {
	.hawt_weg = 0x233d0,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x233d0,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x52010,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_2_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x14010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x14010,
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
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_ahb_cwk = {
	.hawt_weg = 0x16010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x16010,
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
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_ahb_cwk = {
	.hawt_weg = 0x77024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77024,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_phy_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_phy_axi_cwk = {
	.hawt_weg = 0x77018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77018,
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
	.hawt_weg = 0x77018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77018,
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
	.hawt_weg = 0x77074,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77074,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77074,
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
	.hawt_weg = 0x77074,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77074,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77074,
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
	.hawt_weg = 0x770b0,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x770b0,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x770b0,
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
	.hawt_weg = 0x770b0,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x770b0,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x770b0,
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
	.hawt_weg = 0x7702c,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x7702c,
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
	.hawt_weg = 0x770cc,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x770cc,
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
	.hawt_weg = 0x77028,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x77028,
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
	.hawt_weg = 0x77068,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77068,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77068,
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
	.hawt_weg = 0x77068,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x77068,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x77068,
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
	.hawt_weg = 0x39018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39018,
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
	.hawt_weg = 0x39028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39028,
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
	.hawt_weg = 0x39024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_pwim_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_aux_cwk = {
	.hawt_weg = 0x39060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39060,
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
	.hawt_weg = 0x39064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39064,
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
	.hawt_weg = 0x39068,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x39068,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x39068,
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
	.hawt_weg = 0x32018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x32018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x32018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_video_axi1_cwk = {
	.hawt_weg = 0x32024,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x32024,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x32024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_axi1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc pcie_0_gdsc = {
	.gdscw = 0x6b004,
	.cowwapse_ctww = 0x52020,
	.cowwapse_mask = BIT(0),
	.pd = {
		.name = "pcie_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE | POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc pcie_0_phy_gdsc = {
	.gdscw = 0x6c000,
	.cowwapse_ctww = 0x52020,
	.cowwapse_mask = BIT(3),
	.pd = {
		.name = "pcie_0_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE | POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc pcie_1_gdsc = {
	.gdscw = 0x8d004,
	.cowwapse_ctww = 0x52020,
	.cowwapse_mask = BIT(1),
	.pd = {
		.name = "pcie_1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE | POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc pcie_1_phy_gdsc = {
	.gdscw = 0x8e000,
	.cowwapse_ctww = 0x52020,
	.cowwapse_mask = BIT(4),
	.pd = {
		.name = "pcie_1_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE | POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc ufs_phy_gdsc = {
	.gdscw = 0x77004,
	.pd = {
		.name = "ufs_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc ufs_mem_phy_gdsc = {
	.gdscw = 0x9e000,
	.pd = {
		.name = "ufs_mem_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0x39004,
	.pd = {
		.name = "usb30_pwim_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc usb3_phy_gdsc = {
	.gdscw = 0x50018,
	.pd = {
		.name = "usb3_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct cwk_wegmap *gcc_sm8550_cwocks[] = {
	[GCC_AGGWE_NOC_PCIE_AXI_CWK] = &gcc_aggwe_noc_pcie_axi_cwk.cwkw,
	[GCC_AGGWE_UFS_PHY_AXI_CWK] = &gcc_aggwe_ufs_phy_axi_cwk.cwkw,
	[GCC_AGGWE_UFS_PHY_AXI_HW_CTW_CWK] = &gcc_aggwe_ufs_phy_axi_hw_ctw_cwk.cwkw,
	[GCC_AGGWE_USB3_PWIM_AXI_CWK] = &gcc_aggwe_usb3_pwim_axi_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAMEWA_HF_AXI_CWK] = &gcc_camewa_hf_axi_cwk.cwkw,
	[GCC_CAMEWA_SF_AXI_CWK] = &gcc_camewa_sf_axi_cwk.cwkw,
	[GCC_CFG_NOC_PCIE_ANOC_AHB_CWK] = &gcc_cfg_noc_pcie_anoc_ahb_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_CNOC_PCIE_SF_AXI_CWK] = &gcc_cnoc_pcie_sf_axi_cwk.cwkw,
	[GCC_DDWSS_GPU_AXI_CWK] = &gcc_ddwss_gpu_axi_cwk.cwkw,
	[GCC_DDWSS_PCIE_SF_QTB_CWK] = &gcc_ddwss_pcie_sf_qtb_cwk.cwkw,
	[GCC_DISP_HF_AXI_CWK] = &gcc_disp_hf_axi_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPWW0] = &gcc_gpww0.cwkw,
	[GCC_GPWW0_OUT_EVEN] = &gcc_gpww0_out_even.cwkw,
	[GCC_GPWW4] = &gcc_gpww4.cwkw,
	[GCC_GPWW7] = &gcc_gpww7.cwkw,
	[GCC_GPWW9] = &gcc_gpww9.cwkw,
	[GCC_GPU_GPWW0_CWK_SWC] = &gcc_gpu_gpww0_cwk_swc.cwkw,
	[GCC_GPU_GPWW0_DIV_CWK_SWC] = &gcc_gpu_gpww0_div_cwk_swc.cwkw,
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK] = &gcc_pcie_0_aux_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK_SWC] = &gcc_pcie_0_aux_cwk_swc.cwkw,
	[GCC_PCIE_0_CFG_AHB_CWK] = &gcc_pcie_0_cfg_ahb_cwk.cwkw,
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
	[GCC_QUPV3_I2C_COWE_CWK] = &gcc_qupv3_i2c_cowe_cwk.cwkw,
	[GCC_QUPV3_I2C_S0_CWK] = &gcc_qupv3_i2c_s0_cwk.cwkw,
	[GCC_QUPV3_I2C_S0_CWK_SWC] = &gcc_qupv3_i2c_s0_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S1_CWK] = &gcc_qupv3_i2c_s1_cwk.cwkw,
	[GCC_QUPV3_I2C_S1_CWK_SWC] = &gcc_qupv3_i2c_s1_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S2_CWK] = &gcc_qupv3_i2c_s2_cwk.cwkw,
	[GCC_QUPV3_I2C_S2_CWK_SWC] = &gcc_qupv3_i2c_s2_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S3_CWK] = &gcc_qupv3_i2c_s3_cwk.cwkw,
	[GCC_QUPV3_I2C_S3_CWK_SWC] = &gcc_qupv3_i2c_s3_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S4_CWK] = &gcc_qupv3_i2c_s4_cwk.cwkw,
	[GCC_QUPV3_I2C_S4_CWK_SWC] = &gcc_qupv3_i2c_s4_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S5_CWK] = &gcc_qupv3_i2c_s5_cwk.cwkw,
	[GCC_QUPV3_I2C_S5_CWK_SWC] = &gcc_qupv3_i2c_s5_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S6_CWK] = &gcc_qupv3_i2c_s6_cwk.cwkw,
	[GCC_QUPV3_I2C_S6_CWK_SWC] = &gcc_qupv3_i2c_s6_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S7_CWK] = &gcc_qupv3_i2c_s7_cwk.cwkw,
	[GCC_QUPV3_I2C_S7_CWK_SWC] = &gcc_qupv3_i2c_s7_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S8_CWK] = &gcc_qupv3_i2c_s8_cwk.cwkw,
	[GCC_QUPV3_I2C_S8_CWK_SWC] = &gcc_qupv3_i2c_s8_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S9_CWK] = &gcc_qupv3_i2c_s9_cwk.cwkw,
	[GCC_QUPV3_I2C_S9_CWK_SWC] = &gcc_qupv3_i2c_s9_cwk_swc.cwkw,
	[GCC_QUPV3_I2C_S_AHB_CWK] = &gcc_qupv3_i2c_s_ahb_cwk.cwkw,
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
	[GCC_QUPV3_WWAP1_S7_CWK] = &gcc_qupv3_wwap1_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S7_CWK_SWC] = &gcc_qupv3_wwap1_s7_cwk_swc.cwkw,
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
	[GCC_QUPV3_WWAP2_S7_CWK] = &gcc_qupv3_wwap2_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP2_S7_CWK_SWC] = &gcc_qupv3_wwap2_s7_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP_1_M_AHB_CWK] = &gcc_qupv3_wwap_1_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_S_AHB_CWK] = &gcc_qupv3_wwap_1_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_2_M_AHB_CWK] = &gcc_qupv3_wwap_2_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_2_S_AHB_CWK] = &gcc_qupv3_wwap_2_s_ahb_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK_SWC] = &gcc_sdcc2_apps_cwk_swc.cwkw,
	[GCC_SDCC4_AHB_CWK] = &gcc_sdcc4_ahb_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK] = &gcc_sdcc4_apps_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK_SWC] = &gcc_sdcc4_apps_cwk_swc.cwkw,
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
	[GCC_USB3_PWIM_PHY_AUX_CWK] = &gcc_usb3_pwim_phy_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_AUX_CWK_SWC] = &gcc_usb3_pwim_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PWIM_PHY_COM_AUX_CWK] = &gcc_usb3_pwim_phy_com_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK] = &gcc_usb3_pwim_phy_pipe_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK_SWC] = &gcc_usb3_pwim_phy_pipe_cwk_swc.cwkw,
	[GCC_VIDEO_AXI0_CWK] = &gcc_video_axi0_cwk.cwkw,
	[GCC_VIDEO_AXI1_CWK] = &gcc_video_axi1_cwk.cwkw,
};

static const stwuct qcom_weset_map gcc_sm8550_wesets[] = {
	[GCC_CAMEWA_BCW] = { 0x26000 },
	[GCC_DISPWAY_BCW] = { 0x27000 },
	[GCC_GPU_BCW] = { 0x71000 },
	[GCC_PCIE_0_BCW] = { 0x6b000 },
	[GCC_PCIE_0_WINK_DOWN_BCW] = { 0x6c014 },
	[GCC_PCIE_0_NOCSW_COM_PHY_BCW] = { 0x6c020 },
	[GCC_PCIE_0_PHY_BCW] = { 0x6c01c },
	[GCC_PCIE_0_PHY_NOCSW_COM_PHY_BCW] = { 0x6c028 },
	[GCC_PCIE_1_BCW] = { 0x8d000 },
	[GCC_PCIE_1_WINK_DOWN_BCW] = { 0x8e014 },
	[GCC_PCIE_1_NOCSW_COM_PHY_BCW] = { 0x8e020 },
	[GCC_PCIE_1_PHY_BCW] = { 0x8e01c },
	[GCC_PCIE_1_PHY_NOCSW_COM_PHY_BCW] = { 0x8e024 },
	[GCC_PCIE_PHY_BCW] = { 0x6f000 },
	[GCC_PCIE_PHY_CFG_AHB_BCW] = { 0x6f00c },
	[GCC_PCIE_PHY_COM_BCW] = { 0x6f010 },
	[GCC_PDM_BCW] = { 0x33000 },
	[GCC_QUPV3_WWAPPEW_1_BCW] = { 0x18000 },
	[GCC_QUPV3_WWAPPEW_2_BCW] = { 0x1e000 },
	[GCC_QUPV3_WWAPPEW_I2C_BCW] = { 0x17000 },
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x12000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x12004 },
	[GCC_SDCC2_BCW] = { 0x14000 },
	[GCC_SDCC4_BCW] = { 0x16000 },
	[GCC_UFS_PHY_BCW] = { 0x77000 },
	[GCC_USB30_PWIM_BCW] = { 0x39000 },
	[GCC_USB3_DP_PHY_PWIM_BCW] = { 0x50008 },
	[GCC_USB3_DP_PHY_SEC_BCW] = { 0x50014 },
	[GCC_USB3_PHY_PWIM_BCW] = { 0x50000 },
	[GCC_USB3_PHY_SEC_BCW] = { 0x5000c },
	[GCC_USB3PHY_PHY_PWIM_BCW] = { 0x50004 },
	[GCC_USB3PHY_PHY_SEC_BCW] = { 0x50010 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x6a000 },
	[GCC_VIDEO_AXI0_CWK_AWES] = { 0x32018, 2 },
	[GCC_VIDEO_AXI1_CWK_AWES] = { 0x32024, 2 },
	[GCC_VIDEO_BCW] = { 0x32000 },
};

static const stwuct cwk_wcg_dfs_data gcc_dfs_cwocks[] = {
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s5_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s6_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s7_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s0_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s1_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s2_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s3_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s4_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s5_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s6_cwk_swc),
	DEFINE_WCG_DFS(gcc_qupv3_wwap2_s7_cwk_swc),
};

static stwuct gdsc *gcc_sm8550_gdscs[] = {
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_0_PHY_GDSC] = &pcie_0_phy_gdsc,
	[PCIE_1_GDSC] = &pcie_1_gdsc,
	[PCIE_1_PHY_GDSC] = &pcie_1_phy_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[UFS_MEM_PHY_GDSC] = &ufs_mem_phy_gdsc,
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
	[USB3_PHY_GDSC] = &usb3_phy_gdsc,
};

static const stwuct wegmap_config gcc_sm8550_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x1f41f0,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_sm8550_desc = {
	.config = &gcc_sm8550_wegmap_config,
	.cwks = gcc_sm8550_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sm8550_cwocks),
	.wesets = gcc_sm8550_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sm8550_wesets),
	.gdscs = gcc_sm8550_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sm8550_gdscs),
};

static const stwuct of_device_id gcc_sm8550_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8550-gcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sm8550_match_tabwe);

static int gcc_sm8550_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_sm8550_desc);
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
	wegmap_update_bits(wegmap, 0x26004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x26028, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x27004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x27018, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x71004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x32004, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x32030, BIT(0), BIT(0));

	/* Cweaw GDSC_SWEEP_ENA_VOTE to stop votes being auto-wemoved in sweep. */
	wegmap_wwite(wegmap, 0x52024, 0x0);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sm8550_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sm8550_dwivew = {
	.pwobe = gcc_sm8550_pwobe,
	.dwivew = {
		.name = "gcc-sm8550",
		.of_match_tabwe = gcc_sm8550_match_tabwe,
	},
};

static int __init gcc_sm8550_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sm8550_dwivew);
}
subsys_initcaww(gcc_sm8550_init);

static void __exit gcc_sm8550_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sm8550_dwivew);
}
moduwe_exit(gcc_sm8550_exit);

MODUWE_DESCWIPTION("QTI GCC SM8550 Dwivew");
MODUWE_WICENSE("GPW");
