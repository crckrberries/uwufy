// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022-2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,qdu1000-gcc.h>

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
	P_GCC_GPWW1_OUT_MAIN,
	P_GCC_GPWW2_OUT_MAIN,
	P_GCC_GPWW3_OUT_MAIN,
	P_GCC_GPWW4_OUT_MAIN,
	P_GCC_GPWW5_OUT_MAIN,
	P_GCC_GPWW6_OUT_MAIN,
	P_GCC_GPWW7_OUT_MAIN,
	P_GCC_GPWW8_OUT_MAIN,
	P_PCIE_0_PHY_AUX_CWK,
	P_PCIE_0_PIPE_CWK,
	P_SWEEP_CWK,
	P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK,
};

enum {
	DT_TCXO_IDX,
	DT_SWEEP_CWK_IDX,
	DT_PCIE_0_PIPE_CWK_IDX,
	DT_PCIE_0_PHY_AUX_CWK_IDX,
	DT_USB3_PHY_WWAPPEW_PIPE_CWK_IDX,
};

static stwuct cwk_awpha_pww gcc_gpww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww0",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gcc_gpww0_out_even[] = {
	{ 0x1, 2 }
};

static stwuct cwk_awpha_pww_postdiv gcc_gpww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_gcc_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gcc_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gpww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_gpww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static stwuct cwk_awpha_pww gcc_gpww1 = {
	.offset = 0x1000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(1),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww1",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gcc_gpww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_gcc_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gcc_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gpww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_gpww1.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static stwuct cwk_awpha_pww gcc_gpww2 = {
	.offset = 0x2000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(2),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww2",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gcc_gpww2_out_even = {
	.offset = 0x2000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_gcc_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gcc_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gpww2_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_gpww2.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static stwuct cwk_awpha_pww gcc_gpww3 = {
	.offset = 0x3000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(3),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww3",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww4 = {
	.offset = 0x4000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(4),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww4",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww5 = {
	.offset = 0x5000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(5),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww5",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gcc_gpww5_out_even = {
	.offset = 0x5000,
	.post_div_shift = 10,
	.post_div_tabwe = post_div_tabwe_gcc_gpww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gcc_gpww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gpww5_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_gpww5.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_evo_ops,
	},
};

static stwuct cwk_awpha_pww gcc_gpww6 = {
	.offset = 0x6000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(6),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww6",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww7 = {
	.offset = 0x7000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(7),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww7",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fixed_wucid_evo_ops,
		},
	},
};

static stwuct cwk_awpha_pww gcc_gpww8 = {
	.offset = 0x8000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_EVO],
	.cwkw = {
		.enabwe_weg = 0x62018,
		.enabwe_mask = BIT(8),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gpww8",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_TCXO_IDX,
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
	{ .index = DT_TCXO_IDX },
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
	{ .index = DT_TCXO_IDX },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .index = DT_SWEEP_CWK_IDX },
	{ .hw = &gcc_gpww0_out_even.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW5_OUT_MAIN, 3 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .index = DT_TCXO_IDX },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww5.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .index = DT_TCXO_IDX },
	{ .index = DT_SWEEP_CWK_IDX },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW2_OUT_MAIN, 2 },
	{ P_GCC_GPWW5_OUT_MAIN, 3 },
	{ P_GCC_GPWW1_OUT_MAIN, 4 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
	{ P_GCC_GPWW3_OUT_MAIN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .index = DT_TCXO_IDX },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww2.cwkw.hw },
	{ .hw = &gcc_gpww5.cwkw.hw },
	{ .hw = &gcc_gpww1.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
	{ .hw = &gcc_gpww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW2_OUT_MAIN, 2 },
	{ P_GCC_GPWW6_OUT_MAIN, 3 },
	{ P_GCC_GPWW1_OUT_MAIN, 4 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
	{ P_GCC_GPWW3_OUT_MAIN, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .index = DT_TCXO_IDX },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww2.cwkw.hw },
	{ .hw = &gcc_gpww6.cwkw.hw },
	{ .hw = &gcc_gpww1.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
	{ .hw = &gcc_gpww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_PCIE_0_PHY_AUX_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .index = DT_PCIE_0_PHY_AUX_CWK_IDX },
	{ .index = DT_TCXO_IDX },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW8_OUT_MAIN, 2 },
	{ P_GCC_GPWW5_OUT_MAIN, 3 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .index = DT_TCXO_IDX },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww8.cwkw.hw },
	{ .hw = &gcc_gpww5.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
	{ P_GCC_GPWW0_OUT_MAIN, 1 },
	{ P_GCC_GPWW2_OUT_MAIN, 2 },
	{ P_GCC_GPWW5_OUT_MAIN, 3 },
	{ P_GCC_GPWW7_OUT_MAIN, 4 },
	{ P_GCC_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .index = DT_TCXO_IDX },
	{ .hw = &gcc_gpww0.cwkw.hw },
	{ .hw = &gcc_gpww2.cwkw.hw },
	{ .hw = &gcc_gpww5.cwkw.hw },
	{ .hw = &gcc_gpww7.cwkw.hw },
	{ .hw = &gcc_gpww4.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_USB3_PHY_WWAPPEW_GCC_USB30_PIPE_CWK, 0 },
	{ P_BI_TCXO, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .index = DT_USB3_PHY_WWAPPEW_PIPE_CWK_IDX },
	{ .index = DT_TCXO_IDX },
};

static stwuct cwk_wegmap_mux gcc_pcie_0_phy_aux_cwk_swc = {
	.weg = 0x9d080,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_6,
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_phy_aux_cwk_swc",
			.pawent_data = gcc_pawent_data_6,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static stwuct cwk_wegmap_phy_mux gcc_pcie_0_pipe_cwk_swc = {
	.weg = 0x9d064,
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_pipe_cwk_swc",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_PCIE_0_PIPE_CWK_IDX,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_phy_mux_ops,
		},
	},
};

static stwuct cwk_wegmap_mux gcc_usb3_pwim_phy_pipe_cwk_swc = {
	.weg = 0x4906c,
	.shift = 0,
	.width = 2,
	.pawent_map = gcc_pawent_map_10,
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb3_pwim_phy_pipe_cwk_swc",
			.pawent_data = gcc_pawent_data_10,
			.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
			.ops = &cwk_wegmap_mux_cwosest_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_gcc_aggwe_noc_ecpwi_dma_cwk_swc[] = {
	F(466500000, P_GCC_GPWW5_OUT_MAIN, 2, 0, 0),
	F(500000000, P_GCC_GPWW2_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_aggwe_noc_ecpwi_dma_cwk_swc = {
	.cmd_wcgw = 0x92020,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_aggwe_noc_ecpwi_dma_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_aggwe_noc_ecpwi_dma_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_aggwe_noc_ecpwi_gsi_cwk_swc[] = {
	F(250000000, P_GCC_GPWW2_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GCC_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_aggwe_noc_ecpwi_gsi_cwk_swc = {
	.cmd_wcgw = 0x92038,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_aggwe_noc_ecpwi_gsi_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_aggwe_noc_ecpwi_gsi_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(200000000, P_GCC_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x74004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x75004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x76004,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_aux_cwk_swc = {
	.cmd_wcgw = 0x9d068,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie_0_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pcie_0_phy_wchng_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_pcie_0_phy_wchng_cwk_swc = {
	.cmd_wcgw = 0x9d04c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_phy_wchng_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pcie_0_phy_wchng_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
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
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_pdm2_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
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
	F(80000000, P_GCC_GPWW0_OUT_EVEN, 1, 4, 15),
	F(96000000, P_GCC_GPWW0_OUT_EVEN, 1, 8, 25),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s0_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s0_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s0_cwk_swc = {
	.cmd_wcgw = 0x27154,
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
	.cmd_wcgw = 0x27288,
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
	.cmd_wcgw = 0x273bc,
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
	.cmd_wcgw = 0x274f0,
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
	.cmd_wcgw = 0x27624,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s4_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s5_cwk_swc[] = {
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s5_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s5_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s5_cwk_swc = {
	.cmd_wcgw = 0x27758,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s5_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap0_s5_cwk_swc_init,
};

static stwuct cwk_init_data gcc_qupv3_wwap0_s6_cwk_swc_init = {
	.name = "gcc_qupv3_wwap0_s6_cwk_swc",
	.pawent_data = gcc_pawent_data_0,
	.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
	.ops = &cwk_wcg2_shawed_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap0_s6_cwk_swc = {
	.cmd_wcgw = 0x2788c,
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
	.cmd_wcgw = 0x279c0,
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
	.cmd_wcgw = 0x28154,
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
	.cmd_wcgw = 0x28288,
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
	.cmd_wcgw = 0x283bc,
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
	.cmd_wcgw = 0x284f0,
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
	.cmd_wcgw = 0x28624,
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
	.cmd_wcgw = 0x28758,
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
	.cmd_wcgw = 0x2888c,
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
	.cmd_wcgw = 0x289c0,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s7_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_sdcc5_apps_cwk_swc[] = {
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(20000000, P_GCC_GPWW0_OUT_MAIN, 10, 1, 3),
	F(25000000, P_GCC_GPWW0_OUT_MAIN, 12, 1, 2),
	F(50000000, P_GCC_GPWW0_OUT_MAIN, 12, 0, 0),
	F(100000000, P_GCC_GPWW0_OUT_MAIN, 6, 0, 0),
	F(192000000, P_GCC_GPWW8_OUT_MAIN, 4, 0, 0),
	F(300000000, P_GCC_GPWW0_OUT_MAIN, 2, 0, 0),
	F(384000000, P_GCC_GPWW8_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc5_apps_cwk_swc = {
	.cmd_wcgw = 0x3b034,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_sdcc5_apps_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_sdcc5_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc5_ice_cowe_cwk_swc[] = {
	F(300000000, P_GCC_GPWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc5_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x3b01c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_sdcc5_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_sdcc5_ice_cowe_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static stwuct cwk_wcg2 gcc_sm_bus_xo_cwk_swc = {
	.cmd_wcgw = 0x5b00c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_sm_bus_xo_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_tsc_cwk_swc[] = {
	F(500000000, P_GCC_GPWW7_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_tsc_cwk_swc = {
	.cmd_wcgw = 0x57010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_gcc_tsc_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_tsc_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mastew_cwk_swc[] = {
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
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb30_pwim_mastew_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x49044,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_0,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb30_pwim_mock_utmi_cwk_swc",
		.pawent_data = gcc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x49070,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_pcie_0_aux_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wegmap_div gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc = {
	.weg = 0x4905c,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "gcc_usb30_pwim_mock_utmi_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gcc_usb30_pwim_mock_utmi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch gcc_aggwe_noc_ecpwi_dma_cwk = {
	.hawt_weg = 0x92008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x92008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x92008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_aggwe_noc_ecpwi_dma_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_aggwe_noc_ecpwi_dma_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe_noc_ecpwi_gsi_cwk = {
	.hawt_weg = 0x9201c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9201c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x9201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_aggwe_noc_ecpwi_gsi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_aggwe_noc_ecpwi_gsi_cwk_swc.cwkw.hw,
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
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_ecpwi_cc_ahb_cwk = {
	.hawt_weg = 0x3e004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3e004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_cfg_noc_ecpwi_cc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x8401c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8401c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x8401c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_ddwss_ecpwi_dma_cwk = {
	.hawt_weg = 0x54030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x54030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x54030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ddwss_ecpwi_dma_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_aggwe_noc_ecpwi_dma_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ddwss_ecpwi_gsi_cwk = {
	.hawt_weg = 0x54298,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x54298,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x54298,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ddwss_ecpwi_gsi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_aggwe_noc_ecpwi_gsi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_ahb_cwk = {
	.hawt_weg = 0x3a008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3a008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3a008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_cc_gpww0_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_cc_gpww0_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_cc_gpww1_even_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(1),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_cc_gpww1_even_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww1_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_cc_gpww2_even_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(2),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_cc_gpww2_even_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww2_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_cc_gpww3_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(3),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_cc_gpww3_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww3.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_cc_gpww4_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(4),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_cc_gpww4_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww4.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_cc_gpww5_even_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x62010,
		.enabwe_mask = BIT(5),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_cc_gpww5_even_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_gpww5_out_even.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ecpwi_xo_cwk = {
	.hawt_weg = 0x3a004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_ecpwi_xo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_100g_c2c_hm_apb_cwk = {
	.hawt_weg = 0x39010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39010,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_eth_100g_c2c_hm_apb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_100g_fh_hm_apb_0_cwk = {
	.hawt_weg = 0x39004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_eth_100g_fh_hm_apb_0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_100g_fh_hm_apb_1_cwk = {
	.hawt_weg = 0x39008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_eth_100g_fh_hm_apb_1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_100g_fh_hm_apb_2_cwk = {
	.hawt_weg = 0x3900c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3900c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_eth_100g_fh_hm_apb_2_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_dbg_c2c_hm_apb_cwk = {
	.hawt_weg = 0x39014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x39014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_eth_dbg_c2c_hm_apb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_eth_dbg_snoc_axi_cwk = {
	.hawt_weg = 0x3901c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3901c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3901c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_eth_dbg_snoc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gemnoc_pcie_qx_cwk = {
	.hawt_weg = 0x5402c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x5402c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_gemnoc_pcie_qx_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x74000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x74000,
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
	.hawt_weg = 0x75000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x75000,
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

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0x76000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x76000,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_pcie_0_aux_cwk = {
	.hawt_weg = 0x9d030,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(29),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x9d02c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d02c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(28),
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_cwkwef_en",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_mstw_axi_cwk = {
	.hawt_weg = 0x9d024,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x9d024,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(27),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_phy_aux_cwk = {
	.hawt_weg = 0x9d038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d038,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(24),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_pcie_0_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_phy_wchng_cwk = {
	.hawt_weg = 0x9d048,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d048,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(23),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x9d040,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d040,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(30),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x9d01c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d01c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(26),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_q2a_axi_cwk = {
	.hawt_weg = 0x9d018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x9d018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(25),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pcie_0_swv_q2a_axi_cwk",
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
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_pdm_xo4_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_anoc_pcie_cwk = {
	.hawt_weg = 0x84044,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x84044,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x84044,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qmip_anoc_pcie_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_ecpwi_dma0_cwk = {
	.hawt_weg = 0x84038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x84038,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x84038,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qmip_ecpwi_dma0_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_ecpwi_dma1_cwk = {
	.hawt_weg = 0x8403c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x8403c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x8403c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qmip_ecpwi_dma1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qmip_ecpwi_gsi_cwk = {
	.hawt_weg = 0x84040,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x84040,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x84040,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qmip_ecpwi_gsi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_2x_cwk = {
	.hawt_weg = 0x27018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(9),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qupv3_wwap0_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_cowe_cwk = {
	.hawt_weg = 0x2700c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(8),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qupv3_wwap0_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap0_s0_cwk = {
	.hawt_weg = 0x2714c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(10),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x27280,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(11),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x273b4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(12),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x274e8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(13),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x2761c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(14),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x27750,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(15),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x27884,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(16),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x279b8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(17),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x28018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(18),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qupv3_wwap1_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_cwk = {
	.hawt_weg = 0x2800c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(19),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qupv3_wwap1_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_s0_cwk = {
	.hawt_weg = 0x2814c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(22),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x28280,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(23),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x283b4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(24),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x284e8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(25),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x2861c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(26),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x28750,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(27),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x28884,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(28),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x289b8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(29),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct cwk_bwanch gcc_qupv3_wwap_0_m_ahb_cwk = {
	.hawt_weg = 0x27004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x27004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62008,
		.enabwe_mask = BIT(6),
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_qupv3_wwap_1_s_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc5_ahb_cwk = {
	.hawt_weg = 0x3b00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3b00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sdcc5_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc5_apps_cwk = {
	.hawt_weg = 0x3b004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sdcc5_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc5_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc5_ice_cowe_cwk = {
	.hawt_weg = 0x3b010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3b010,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sdcc5_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sdcc5_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sm_bus_ahb_cwk = {
	.hawt_weg = 0x5b004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sm_bus_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sm_bus_xo_cwk = {
	.hawt_weg = 0x5b008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5b008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_sm_bus_xo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_sm_bus_xo_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_cnoc_gemnoc_pcie_qx_cwk = {
	.hawt_weg = 0x9200c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x9200c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(11),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_cnoc_gemnoc_pcie_qx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_cnoc_gemnoc_pcie_south_qx_cwk = {
	.hawt_weg = 0x92010,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x92010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(12),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_cnoc_gemnoc_pcie_south_qx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_cnoc_pcie_qx_cwk = {
	.hawt_weg = 0x84030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x84030,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_cnoc_pcie_qx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie_sf_centew_qx_cwk = {
	.hawt_weg = 0x92014,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x92014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(19),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie_sf_centew_qx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_snoc_pcie_sf_south_qx_cwk = {
	.hawt_weg = 0x92018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x92018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x62000,
		.enabwe_mask = BIT(22),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_snoc_pcie_sf_south_qx_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsc_cfg_ahb_cwk = {
	.hawt_weg = 0x5700c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5700c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_tsc_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsc_cntw_cwk = {
	.hawt_weg = 0x57004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x57004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_tsc_cntw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_tsc_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsc_etu_cwk = {
	.hawt_weg = 0x57008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x57008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_tsc_etu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gcc_tsc_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb2_cwkwef_en = {
	.hawt_weg = 0x9c008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9c008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb2_cwkwef_en",
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
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
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
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "gcc_usb30_pwim_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_pwim_phy_aux_cwk = {
	.hawt_weg = 0x49060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49060,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x49064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49064,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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
	.hawt_weg = 0x49068,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.hwcg_weg = 0x49068,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x49068,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
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

static stwuct gdsc pcie_0_gdsc = {
	.gdscw = 0x9d004,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0xf,
	.pd = {
		.name = "gcc_pcie_0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc pcie_0_phy_gdsc = {
	.gdscw = 0x7c004,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0x2,
	.pd = {
		.name = "gcc_pcie_0_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0x49004,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0xf,
	.pd = {
		.name = "gcc_usb30_pwim_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *gcc_qdu1000_cwocks[] = {
	[GCC_AGGWE_NOC_ECPWI_DMA_CWK] = &gcc_aggwe_noc_ecpwi_dma_cwk.cwkw,
	[GCC_AGGWE_NOC_ECPWI_DMA_CWK_SWC] = &gcc_aggwe_noc_ecpwi_dma_cwk_swc.cwkw,
	[GCC_AGGWE_NOC_ECPWI_GSI_CWK_SWC] = &gcc_aggwe_noc_ecpwi_gsi_cwk_swc.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CFG_NOC_ECPWI_CC_AHB_CWK] = &gcc_cfg_noc_ecpwi_cc_ahb_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_DDWSS_ECPWI_DMA_CWK] = &gcc_ddwss_ecpwi_dma_cwk.cwkw,
	[GCC_ECPWI_AHB_CWK] = &gcc_ecpwi_ahb_cwk.cwkw,
	[GCC_ECPWI_CC_GPWW0_CWK_SWC] = &gcc_ecpwi_cc_gpww0_cwk_swc.cwkw,
	[GCC_ECPWI_CC_GPWW1_EVEN_CWK_SWC] = &gcc_ecpwi_cc_gpww1_even_cwk_swc.cwkw,
	[GCC_ECPWI_CC_GPWW2_EVEN_CWK_SWC] = &gcc_ecpwi_cc_gpww2_even_cwk_swc.cwkw,
	[GCC_ECPWI_CC_GPWW3_CWK_SWC] = &gcc_ecpwi_cc_gpww3_cwk_swc.cwkw,
	[GCC_ECPWI_CC_GPWW4_CWK_SWC] = &gcc_ecpwi_cc_gpww4_cwk_swc.cwkw,
	[GCC_ECPWI_CC_GPWW5_EVEN_CWK_SWC] = &gcc_ecpwi_cc_gpww5_even_cwk_swc.cwkw,
	[GCC_ECPWI_XO_CWK] = &gcc_ecpwi_xo_cwk.cwkw,
	[GCC_ETH_DBG_SNOC_AXI_CWK] = &gcc_eth_dbg_snoc_axi_cwk.cwkw,
	[GCC_GEMNOC_PCIE_QX_CWK] = &gcc_gemnoc_pcie_qx_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP1_CWK_SWC] = &gcc_gp1_cwk_swc.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP2_CWK_SWC] = &gcc_gp2_cwk_swc.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_GP3_CWK_SWC] = &gcc_gp3_cwk_swc.cwkw,
	[GCC_GPWW0] = &gcc_gpww0.cwkw,
	[GCC_GPWW0_OUT_EVEN] = &gcc_gpww0_out_even.cwkw,
	[GCC_GPWW1] = &gcc_gpww1.cwkw,
	[GCC_GPWW2] = &gcc_gpww2.cwkw,
	[GCC_GPWW2_OUT_EVEN] = &gcc_gpww2_out_even.cwkw,
	[GCC_GPWW3] = &gcc_gpww3.cwkw,
	[GCC_GPWW4] = &gcc_gpww4.cwkw,
	[GCC_GPWW5] = &gcc_gpww5.cwkw,
	[GCC_GPWW5_OUT_EVEN] = &gcc_gpww5_out_even.cwkw,
	[GCC_GPWW6] = &gcc_gpww6.cwkw,
	[GCC_GPWW7] = &gcc_gpww7.cwkw,
	[GCC_GPWW8] = &gcc_gpww8.cwkw,
	[GCC_PCIE_0_AUX_CWK] = &gcc_pcie_0_aux_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK_SWC] = &gcc_pcie_0_aux_cwk_swc.cwkw,
	[GCC_PCIE_0_CFG_AHB_CWK] = &gcc_pcie_0_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_0_CWKWEF_EN] = &gcc_pcie_0_cwkwef_en.cwkw,
	[GCC_PCIE_0_MSTW_AXI_CWK] = &gcc_pcie_0_mstw_axi_cwk.cwkw,
	[GCC_PCIE_0_PHY_AUX_CWK] = &gcc_pcie_0_phy_aux_cwk.cwkw,
	[GCC_PCIE_0_PHY_WCHNG_CWK] = &gcc_pcie_0_phy_wchng_cwk.cwkw,
	[GCC_PCIE_0_PHY_WCHNG_CWK_SWC] = &gcc_pcie_0_phy_wchng_cwk_swc.cwkw,
	[GCC_PCIE_0_PIPE_CWK] = &gcc_pcie_0_pipe_cwk.cwkw,
	[GCC_PCIE_0_SWV_AXI_CWK] = &gcc_pcie_0_swv_axi_cwk.cwkw,
	[GCC_PCIE_0_SWV_Q2A_AXI_CWK] = &gcc_pcie_0_swv_q2a_axi_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM2_CWK_SWC] = &gcc_pdm2_cwk_swc.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM_XO4_CWK] = &gcc_pdm_xo4_cwk.cwkw,
	[GCC_QMIP_ANOC_PCIE_CWK] = &gcc_qmip_anoc_pcie_cwk.cwkw,
	[GCC_QMIP_ECPWI_DMA0_CWK] = &gcc_qmip_ecpwi_dma0_cwk.cwkw,
	[GCC_QMIP_ECPWI_DMA1_CWK] = &gcc_qmip_ecpwi_dma1_cwk.cwkw,
	[GCC_QMIP_ECPWI_GSI_CWK] = &gcc_qmip_ecpwi_gsi_cwk.cwkw,
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
	[GCC_QUPV3_WWAP1_S7_CWK] = &gcc_qupv3_wwap1_s7_cwk.cwkw,
	[GCC_QUPV3_WWAP1_S7_CWK_SWC] = &gcc_qupv3_wwap1_s7_cwk_swc.cwkw,
	[GCC_QUPV3_WWAP_0_M_AHB_CWK] = &gcc_qupv3_wwap_0_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_0_S_AHB_CWK] = &gcc_qupv3_wwap_0_s_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_M_AHB_CWK] = &gcc_qupv3_wwap_1_m_ahb_cwk.cwkw,
	[GCC_QUPV3_WWAP_1_S_AHB_CWK] = &gcc_qupv3_wwap_1_s_ahb_cwk.cwkw,
	[GCC_SDCC5_AHB_CWK] = &gcc_sdcc5_ahb_cwk.cwkw,
	[GCC_SDCC5_APPS_CWK] = &gcc_sdcc5_apps_cwk.cwkw,
	[GCC_SDCC5_APPS_CWK_SWC] = &gcc_sdcc5_apps_cwk_swc.cwkw,
	[GCC_SDCC5_ICE_COWE_CWK] = &gcc_sdcc5_ice_cowe_cwk.cwkw,
	[GCC_SDCC5_ICE_COWE_CWK_SWC] = &gcc_sdcc5_ice_cowe_cwk_swc.cwkw,
	[GCC_SM_BUS_AHB_CWK] = &gcc_sm_bus_ahb_cwk.cwkw,
	[GCC_SM_BUS_XO_CWK] = &gcc_sm_bus_xo_cwk.cwkw,
	[GCC_SM_BUS_XO_CWK_SWC] = &gcc_sm_bus_xo_cwk_swc.cwkw,
	[GCC_SNOC_CNOC_GEMNOC_PCIE_QX_CWK] = &gcc_snoc_cnoc_gemnoc_pcie_qx_cwk.cwkw,
	[GCC_SNOC_CNOC_GEMNOC_PCIE_SOUTH_QX_CWK] = &gcc_snoc_cnoc_gemnoc_pcie_south_qx_cwk.cwkw,
	[GCC_SNOC_CNOC_PCIE_QX_CWK] = &gcc_snoc_cnoc_pcie_qx_cwk.cwkw,
	[GCC_SNOC_PCIE_SF_CENTEW_QX_CWK] = &gcc_snoc_pcie_sf_centew_qx_cwk.cwkw,
	[GCC_SNOC_PCIE_SF_SOUTH_QX_CWK] = &gcc_snoc_pcie_sf_south_qx_cwk.cwkw,
	[GCC_TSC_CFG_AHB_CWK] = &gcc_tsc_cfg_ahb_cwk.cwkw,
	[GCC_TSC_CWK_SWC] = &gcc_tsc_cwk_swc.cwkw,
	[GCC_TSC_CNTW_CWK] = &gcc_tsc_cntw_cwk.cwkw,
	[GCC_TSC_ETU_CWK] = &gcc_tsc_etu_cwk.cwkw,
	[GCC_USB2_CWKWEF_EN] = &gcc_usb2_cwkwef_en.cwkw,
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
	[GCC_ETH_100G_C2C_HM_APB_CWK] = &gcc_eth_100g_c2c_hm_apb_cwk.cwkw,
	[GCC_ETH_100G_FH_HM_APB_0_CWK] = &gcc_eth_100g_fh_hm_apb_0_cwk.cwkw,
	[GCC_ETH_100G_FH_HM_APB_1_CWK] = &gcc_eth_100g_fh_hm_apb_1_cwk.cwkw,
	[GCC_ETH_100G_FH_HM_APB_2_CWK] = &gcc_eth_100g_fh_hm_apb_2_cwk.cwkw,
	[GCC_ETH_DBG_C2C_HM_APB_CWK] = &gcc_eth_dbg_c2c_hm_apb_cwk.cwkw,
	[GCC_AGGWE_NOC_ECPWI_GSI_CWK] = &gcc_aggwe_noc_ecpwi_gsi_cwk.cwkw,
	[GCC_PCIE_0_PHY_AUX_CWK_SWC] = &gcc_pcie_0_phy_aux_cwk_swc.cwkw,
	[GCC_PCIE_0_PIPE_CWK_SWC] = &gcc_pcie_0_pipe_cwk_swc.cwkw,
	[GCC_GPWW1_OUT_EVEN] = &gcc_gpww1_out_even.cwkw,
	[GCC_DDWSS_ECPWI_GSI_CWK] = &gcc_ddwss_ecpwi_gsi_cwk.cwkw,
};

static stwuct gdsc *gcc_qdu1000_gdscs[] = {
	[PCIE_0_GDSC] = &pcie_0_gdsc,
	[PCIE_0_PHY_GDSC] = &pcie_0_phy_gdsc,
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
};

static const stwuct qcom_weset_map gcc_qdu1000_wesets[] = {
	[GCC_ECPWI_CC_BCW] = { 0x3e000 },
	[GCC_ECPWI_SS_BCW] = { 0x3a000 },
	[GCC_ETH_WWAPPEW_BCW] = { 0x39000 },
	[GCC_PCIE_0_BCW] = { 0x9d000 },
	[GCC_PCIE_0_WINK_DOWN_BCW] = { 0x9e014 },
	[GCC_PCIE_0_NOCSW_COM_PHY_BCW] = { 0x9e020 },
	[GCC_PCIE_0_PHY_BCW] = { 0x7c000 },
	[GCC_PCIE_0_PHY_NOCSW_COM_PHY_BCW] = { 0x9e000 },
	[GCC_PCIE_PHY_CFG_AHB_BCW] = { 0x7f00c },
	[GCC_PCIE_PHY_COM_BCW] = { 0x7f010 },
	[GCC_PDM_BCW] = { 0x43000 },
	[GCC_QUPV3_WWAPPEW_0_BCW] = { 0x27000 },
	[GCC_QUPV3_WWAPPEW_1_BCW] = { 0x28000 },
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x22000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x22004 },
	[GCC_SDCC5_BCW] = { 0x3b000 },
	[GCC_TSC_BCW] = { 0x57000 },
	[GCC_USB30_PWIM_BCW] = { 0x49000 },
	[GCC_USB3_DP_PHY_PWIM_BCW] = { 0x60008 },
	[GCC_USB3_DP_PHY_SEC_BCW] = { 0x60014 },
	[GCC_USB3_PHY_PWIM_BCW] = { 0x60000 },
	[GCC_USB3_PHY_SEC_BCW] = { 0x6000c },
	[GCC_USB3PHY_PHY_PWIM_BCW] = { 0x60004 },
	[GCC_USB3PHY_PHY_SEC_BCW] = { 0x60010 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x7a000 },
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
	DEFINE_WCG_DFS(gcc_qupv3_wwap1_s7_cwk_swc),
};

static const stwuct wegmap_config gcc_qdu1000_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x1f41f0,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_qdu1000_desc = {
	.config = &gcc_qdu1000_wegmap_config,
	.cwks = gcc_qdu1000_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_qdu1000_cwocks),
	.wesets = gcc_qdu1000_wesets,
	.num_wesets = AWWAY_SIZE(gcc_qdu1000_wesets),
	.gdscs = gcc_qdu1000_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_qdu1000_gdscs),
};

static const stwuct of_device_id gcc_qdu1000_match_tabwe[] = {
	{ .compatibwe = "qcom,qdu1000-gcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_qdu1000_match_tabwe);

static int gcc_qdu1000_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_qdu1000_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Update FOWCE_MEM_COWE_ON fow gcc_pcie_0_mstw_axi_cwk */
	wegmap_update_bits(wegmap, 0x9d024, BIT(14), BIT(14));

	wet = qcom_cc_wegistew_wcg_dfs(wegmap, gcc_dfs_cwocks,
				       AWWAY_SIZE(gcc_dfs_cwocks));
	if (wet)
		wetuwn wet;

	wet = qcom_cc_weawwy_pwobe(pdev, &gcc_qdu1000_desc, wegmap);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wegistew GCC cwocks\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew gcc_qdu1000_dwivew = {
	.pwobe = gcc_qdu1000_pwobe,
	.dwivew = {
		.name = "gcc-qdu1000",
		.of_match_tabwe = gcc_qdu1000_match_tabwe,
	},
};

static int __init gcc_qdu1000_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_qdu1000_dwivew);
}
subsys_initcaww(gcc_qdu1000_init);

static void __exit gcc_qdu1000_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_qdu1000_dwivew);
}
moduwe_exit(gcc_qdu1000_exit);

MODUWE_DESCWIPTION("QTI GCC QDU1000 Dwivew");
MODUWE_WICENSE("GPW");
