// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Konwad Dybcio <konwad.dybcio@somainwine.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gcc-sm6125.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_AUX2,
	P_GPWW0_OUT_EAWWY,
	P_GPWW3_OUT_EAWWY,
	P_GPWW4_OUT_MAIN,
	P_GPWW5_OUT_MAIN,
	P_GPWW6_OUT_EAWWY,
	P_GPWW6_OUT_MAIN,
	P_GPWW7_OUT_MAIN,
	P_GPWW8_OUT_EAWWY,
	P_GPWW8_OUT_MAIN,
	P_GPWW9_OUT_MAIN,
	P_SWEEP_CWK,
};

static stwuct cwk_awpha_pww gpww0_out_eawwy = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0_out_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww0_out_aux2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_aux2",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0_out_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_fixed_factow gpww0_out_main = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0_out_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww3_out_eawwy = {
	.offset = 0x3000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww3_out_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww4_out_main = {
	.offset = 0x4000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4_out_main",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww5_out_main = {
	.offset = 0x5000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww5_out_main",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpww6_out_eawwy = {
	.offset = 0x6000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww6_out_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww6_out_main = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww6_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww6_out_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww7_out_eawwy = {
	.offset = 0x7000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww7_out_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww7_out_main = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww7_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww7_out_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww8_out_eawwy = {
	.offset = 0x8000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww8_out_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww8_out_main = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww8_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww8_out_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww9_out_eawwy = {
	.offset = 0x9000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x79000,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww9_out_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww9_out_main = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww9_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww9_out_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static const stwuct pawent_map gcc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW0_OUT_AUX2, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww0_out_aux2.hw },
};

static const stwuct pawent_map gcc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW0_OUT_AUX2, 2 },
	{ P_GPWW6_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww0_out_aux2.hw },
	{ .hw = &gpww6_out_main.hw },
};

static const stwuct pawent_map gcc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW0_OUT_AUX2, 2 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww0_out_aux2.hw },
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW5_OUT_MAIN, 3 },
	{ P_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww5_out_main.cwkw.hw },
	{ .hw = &gpww4_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW9_OUT_MAIN, 2 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww9_out_main.hw },
};

static const stwuct pawent_map gcc_pawent_map_5[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_5[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww4_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_7[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_7[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map gcc_pawent_map_8[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW9_OUT_MAIN, 2 },
	{ P_GPWW6_OUT_EAWWY, 3 },
	{ P_GPWW8_OUT_MAIN, 4 },
	{ P_GPWW4_OUT_MAIN, 5 },
	{ P_GPWW3_OUT_EAWWY, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_8[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww9_out_main.hw },
	{ .hw = &gpww6_out_eawwy.cwkw.hw },
	{ .hw = &gpww8_out_main.hw },
	{ .hw = &gpww4_out_main.cwkw.hw },
	{ .hw = &gpww3_out_eawwy.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_9[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW8_OUT_MAIN, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_9[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww8_out_main.hw },
};

static const stwuct pawent_map gcc_pawent_map_10[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW9_OUT_MAIN, 2 },
	{ P_GPWW6_OUT_EAWWY, 3 },
	{ P_GPWW8_OUT_MAIN, 4 },
	{ P_GPWW3_OUT_EAWWY, 6 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_10[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww9_out_main.hw },
	{ .hw = &gpww6_out_eawwy.cwkw.hw },
	{ .hw = &gpww8_out_main.hw },
	{ .hw = &gpww3_out_eawwy.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_11[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW8_OUT_EAWWY, 4 },
	{ P_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_11[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww8_out_eawwy.cwkw.hw },
	{ .hw = &gpww4_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_12[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW6_OUT_EAWWY, 3 },
	{ P_GPWW8_OUT_EAWWY, 4 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_12[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww6_out_eawwy.cwkw.hw },
	{ .hw = &gpww8_out_eawwy.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_13[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_EAWWY, 1 },
	{ P_GPWW0_OUT_AUX2, 2 },
	{ P_GPWW7_OUT_MAIN, 3 },
	{ P_GPWW4_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_13[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpww0_out_eawwy.cwkw.hw },
	{ .hw = &gpww0_out_aux2.hw },
	{ .hw = &gpww7_out_main.hw },
	{ .hw = &gpww4_out_main.cwkw.hw },
};

static const stwuct pawent_map gcc_pawent_map_14[] = {
	{ P_BI_TCXO, 0 },
	{ P_SWEEP_CWK, 5 },
};

static const stwuct cwk_pawent_data gcc_pawent_data_14[] = {
	{ .fw_name = "bi_tcxo" },
	{ .fw_name = "sweep_cwk" },
};

static const stwuct fweq_tbw ftbw_gcc_camss_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(40000000, P_GPWW8_OUT_MAIN, 12, 0, 0),
	F(80000000, P_GPWW8_OUT_MAIN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_ahb_cwk_swc = {
	.cmd_wcgw = 0x56088,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_9,
	.fweq_tbw = ftbw_gcc_camss_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_ahb_cwk_swc",
		.pawent_data = gcc_pawent_data_9,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_9),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_cci_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_EAWWY, 16, 0, 0),
	F(50000000, P_GPWW0_OUT_EAWWY, 12, 0, 0),
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_cci_cwk_swc = {
	.cmd_wcgw = 0x52004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_camss_cci_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_cci_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_cpp_cwk_swc[] = {
	F(120000000, P_GPWW8_OUT_MAIN, 4, 0, 0),
	F(240000000, P_GPWW8_OUT_MAIN, 2, 0, 0),
	F(320000000, P_GPWW8_OUT_MAIN, 1.5, 0, 0),
	F(480000000, P_GPWW8_OUT_MAIN, 1, 0, 0),
	F(576000000, P_GPWW9_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_cpp_cwk_swc = {
	.cmd_wcgw = 0x560c8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_10,
	.fweq_tbw = ftbw_gcc_camss_cpp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_cpp_cwk_swc",
		.pawent_data = gcc_pawent_data_10,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_10),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_csi0_cwk_swc[] = {
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	F(311000000, P_GPWW5_OUT_MAIN, 3, 0, 0),
	F(403200000, P_GPWW4_OUT_MAIN, 2, 0, 0),
	F(466500000, P_GPWW5_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_csi0_cwk_swc = {
	.cmd_wcgw = 0x55030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi0_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_csi0phytimew_cwk_swc[] = {
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	F(268800000, P_GPWW4_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x53004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi0phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi1_cwk_swc = {
	.cmd_wcgw = 0x5506c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi1_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0x53024,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi1phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi2_cwk_swc = {
	.cmd_wcgw = 0x550a4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi2_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0x53044,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_6,
	.fweq_tbw = ftbw_gcc_camss_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi2phytimew_cwk_swc",
		.pawent_data = gcc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_6),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_csi3_cwk_swc = {
	.cmd_wcgw = 0x550e0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_3,
	.fweq_tbw = ftbw_gcc_camss_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csi3_cwk_swc",
		.pawent_data = gcc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_3),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_csiphy_cwk_swc[] = {
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	F(268800000, P_GPWW4_OUT_MAIN, 3, 0, 0),
	F(320000000, P_GPWW8_OUT_EAWWY, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_csiphy_cwk_swc = {
	.cmd_wcgw = 0x55000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_11,
	.fweq_tbw = ftbw_gcc_camss_csiphy_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_csiphy_cwk_swc",
		.pawent_data = gcc_pawent_data_11,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_11),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_gp0_cwk_swc[] = {
	F(50000000, P_GPWW0_OUT_EAWWY, 12, 0, 0),
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_gp0_cwk_swc = {
	.cmd_wcgw = 0x50000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_camss_gp0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_gp0_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_gp1_cwk_swc = {
	.cmd_wcgw = 0x5001c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_7,
	.fweq_tbw = ftbw_gcc_camss_gp0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_7,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_7),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_jpeg_cwk_swc[] = {
	F(66666667, P_GPWW0_OUT_EAWWY, 9, 0, 0),
	F(133333333, P_GPWW0_OUT_EAWWY, 4.5, 0, 0),
	F(219428571, P_GPWW6_OUT_EAWWY, 3.5, 0, 0),
	F(320000000, P_GPWW8_OUT_EAWWY, 3, 0, 0),
	F(480000000, P_GPWW8_OUT_EAWWY, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_jpeg_cwk_swc = {
	.cmd_wcgw = 0x52028,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_12,
	.fweq_tbw = ftbw_gcc_camss_jpeg_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_jpeg_cwk_swc",
		.pawent_data = gcc_pawent_data_12,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_12),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_mcwk0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_GPWW9_OUT_MAIN, 1, 1, 24),
	F(64000000, P_GPWW9_OUT_MAIN, 1, 1, 9),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x51000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk0_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x5101c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk1_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x51038,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk2_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x51054,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_4,
	.fweq_tbw = ftbw_gcc_camss_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_mcwk3_cwk_swc",
		.pawent_data = gcc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_4),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_camss_vfe0_cwk_swc[] = {
	F(120000000, P_GPWW8_OUT_MAIN, 4, 0, 0),
	F(256000000, P_GPWW6_OUT_EAWWY, 3, 0, 0),
	F(403200000, P_GPWW4_OUT_MAIN, 2, 0, 0),
	F(480000000, P_GPWW8_OUT_MAIN, 1, 0, 0),
	F(533000000, P_GPWW3_OUT_EAWWY, 2, 0, 0),
	F(576000000, P_GPWW9_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_camss_vfe0_cwk_swc = {
	.cmd_wcgw = 0x54010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_camss_vfe0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_vfe0_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_camss_vfe1_cwk_swc = {
	.cmd_wcgw = 0x54048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_8,
	.fweq_tbw = ftbw_gcc_camss_vfe0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_camss_vfe1_cwk_swc",
		.pawent_data = gcc_pawent_data_8,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_8),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_gp1_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_AUX2, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_AUX2, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_gp1_cwk_swc = {
	.cmd_wcgw = 0x4d004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp1_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp2_cwk_swc = {
	.cmd_wcgw = 0x4e004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp2_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_gp3_cwk_swc = {
	.cmd_wcgw = 0x4f004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_2,
	.fweq_tbw = ftbw_gcc_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_gp3_cwk_swc",
		.pawent_data = gcc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_2),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_pdm2_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_GPWW0_OUT_EAWWY, 10, 0, 0),
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
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_qupv3_wwap0_s0_cwk_swc[] = {
	F(7372800, P_GPWW0_OUT_AUX2, 1, 384, 15625),
	F(14745600, P_GPWW0_OUT_AUX2, 1, 768, 15625),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(29491200, P_GPWW0_OUT_AUX2, 1, 1536, 15625),
	F(32000000, P_GPWW0_OUT_AUX2, 1, 8, 75),
	F(48000000, P_GPWW0_OUT_AUX2, 1, 4, 25),
	F(64000000, P_GPWW0_OUT_AUX2, 1, 16, 75),
	F(75000000, P_GPWW0_OUT_AUX2, 4, 0, 0),
	F(80000000, P_GPWW0_OUT_AUX2, 1, 4, 15),
	F(96000000, P_GPWW0_OUT_AUX2, 1, 8, 25),
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(102400000, P_GPWW0_OUT_AUX2, 1, 128, 375),
	F(112000000, P_GPWW0_OUT_AUX2, 1, 28, 75),
	F(117964800, P_GPWW0_OUT_AUX2, 1, 6144, 15625),
	F(120000000, P_GPWW0_OUT_AUX2, 2.5, 0, 0),
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
	.ops = &cwk_wcg2_ops,
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
	.ops = &cwk_wcg2_ops,
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
	.ops = &cwk_wcg2_ops,
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
	.ops = &cwk_wcg2_ops,
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
	.ops = &cwk_wcg2_ops,
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
	.ops = &cwk_wcg2_ops,
};

static stwuct cwk_wcg2 gcc_qupv3_wwap1_s0_cwk_swc = {
	.cmd_wcgw = 0x39148,
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
	.cmd_wcgw = 0x39278,
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
	.cmd_wcgw = 0x393a8,
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
	.cmd_wcgw = 0x394d8,
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
	.cmd_wcgw = 0x39608,
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
	.cmd_wcgw = 0x39738,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_1,
	.fweq_tbw = ftbw_gcc_qupv3_wwap0_s0_cwk_swc,
	.cwkw.hw.init = &gcc_qupv3_wwap1_s5_cwk_swc_init,
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_apps_cwk_swc[] = {
	F(144000, P_BI_TCXO, 16, 3, 25),
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(20000000, P_GPWW0_OUT_AUX2, 5, 1, 3),
	F(25000000, P_GPWW0_OUT_AUX2, 6, 1, 2),
	F(50000000, P_GPWW0_OUT_AUX2, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_AUX2, 3, 0, 0),
	F(192000000, P_GPWW6_OUT_MAIN, 2, 0, 0),
	F(384000000, P_GPWW6_OUT_MAIN, 1, 0, 0),
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
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_ice_cowe_cwk_swc[] = {
	F(75000000, P_GPWW0_OUT_AUX2, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_EAWWY, 4, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	F(300000000, P_GPWW0_OUT_EAWWY, 2, 0, 0),
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
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_sdcc2_apps_cwk_swc[] = {
	F(400000, P_BI_TCXO, 12, 1, 4),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(25000000, P_GPWW0_OUT_AUX2, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_AUX2, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_AUX2, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x1e00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_13,
	.fweq_tbw = ftbw_gcc_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sdcc2_apps_cwk_swc",
		.pawent_data = gcc_pawent_data_13,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_13),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_axi_cwk_swc[] = {
	F(25000000, P_GPWW0_OUT_AUX2, 12, 0, 0),
	F(50000000, P_GPWW0_OUT_AUX2, 6, 0, 0),
	F(100000000, P_GPWW0_OUT_EAWWY, 6, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_EAWWY, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_ufs_phy_axi_cwk_swc = {
	.cmd_wcgw = 0x45020,
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
	F(37500000, P_GPWW0_OUT_AUX2, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_AUX2, 4, 0, 0),
	F(150000000, P_GPWW0_OUT_EAWWY, 4, 0, 0),
	F(300000000, P_GPWW0_OUT_EAWWY, 2, 0, 0),
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
		.ops = &cwk_wcg2_ops,
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
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_ufs_phy_unipwo_cowe_cwk_swc[] = {
	F(37500000, P_GPWW0_OUT_AUX2, 8, 0, 0),
	F(75000000, P_GPWW0_OUT_EAWWY, 8, 0, 0),
	F(150000000, P_GPWW0_OUT_EAWWY, 4, 0, 0),
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
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb30_pwim_mastew_cwk_swc[] = {
	F(66666667, P_GPWW0_OUT_AUX2, 4.5, 0, 0),
	F(133333333, P_GPWW0_OUT_EAWWY, 4.5, 0, 0),
	F(200000000, P_GPWW0_OUT_EAWWY, 3, 0, 0),
	F(240000000, P_GPWW0_OUT_EAWWY, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb30_pwim_mastew_cwk_swc = {
	.cmd_wcgw = 0x1a01c,
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
	F(20000000, P_GPWW0_OUT_AUX2, 15, 0, 0),
	F(40000000, P_GPWW0_OUT_AUX2, 7.5, 0, 0),
	F(60000000, P_GPWW0_OUT_EAWWY, 10, 0, 0),
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
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb3_pwim_phy_aux_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_usb3_pwim_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x1a060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_14,
	.fweq_tbw = ftbw_gcc_usb3_pwim_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_usb3_pwim_phy_aux_cwk_swc",
		.pawent_data = gcc_pawent_data_14,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_14),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_vs_ctww_cwk_swc = {
	.cmd_wcgw = 0x42030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_usb3_pwim_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_vs_ctww_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_vsensow_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_GPWW0_OUT_EAWWY, 1.5, 0, 0),
	F(600000000, P_GPWW0_OUT_EAWWY, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gcc_vsensow_cwk_swc = {
	.cmd_wcgw = 0x42018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gcc_pawent_map_5,
	.fweq_tbw = ftbw_gcc_vsensow_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_vsensow_cwk_swc",
		.pawent_data = gcc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(gcc_pawent_data_5),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_ahb2phy_csi_cwk = {
	.hawt_weg = 0x1d004,
	.hawt_check = BWANCH_HAWT,
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
	.hawt_check = BWANCH_HAWT,
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

static stwuct cwk_bwanch gcc_apc_vs_cwk = {
	.hawt_weg = 0x4204c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4204c,
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

static stwuct cwk_bwanch gcc_bimc_gpu_axi_cwk = {
	.hawt_weg = 0x71154,
	.hawt_check = BWANCH_HAWT_DEWAY,
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

static stwuct cwk_bwanch gcc_camewa_xo_cwk = {
	.hawt_weg = 0x17028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camewa_xo_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cci_ahb_cwk = {
	.hawt_weg = 0x52020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cci_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cci_cwk = {
	.hawt_weg = 0x5201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cci_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_cci_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_csid0_cwk = {
	.hawt_weg = 0x5504c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5504c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_csid0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_csid1_cwk = {
	.hawt_weg = 0x55088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_csid1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_csid2_cwk = {
	.hawt_weg = 0x550c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_csid2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cphy_csid3_cwk = {
	.hawt_weg = 0x550fc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550fc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cphy_csid3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cpp_ahb_cwk = {
	.hawt_weg = 0x560e8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x560e8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cpp_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cpp_axi_cwk = {
	.hawt_weg = 0x560f4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x560f4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cpp_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cpp_cwk = {
	.hawt_weg = 0x560e0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x560e0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cpp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_cpp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_cpp_vbif_ahb_cwk = {
	.hawt_weg = 0x560f0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x560f0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_cpp_vbif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi0_ahb_cwk = {
	.hawt_weg = 0x55050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi0_cwk = {
	.hawt_weg = 0x55048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi0phytimew_cwk = {
	.hawt_weg = 0x5301c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5301c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi0phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi0pix_cwk = {
	.hawt_weg = 0x55060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi0pix_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi0wdi_cwk = {
	.hawt_weg = 0x55058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi0wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi1_ahb_cwk = {
	.hawt_weg = 0x5508c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5508c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi1_cwk = {
	.hawt_weg = 0x55084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi1phytimew_cwk = {
	.hawt_weg = 0x5303c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5303c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi1phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi1pix_cwk = {
	.hawt_weg = 0x5509c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5509c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi1pix_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi1wdi_cwk = {
	.hawt_weg = 0x55094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi1wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi2_ahb_cwk = {
	.hawt_weg = 0x550c4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550c4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi2_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi2_cwk = {
	.hawt_weg = 0x550bc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550bc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi2phytimew_cwk = {
	.hawt_weg = 0x5305c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5305c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi2phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi2pix_cwk = {
	.hawt_weg = 0x550d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi2pix_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi2wdi_cwk = {
	.hawt_weg = 0x550cc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550cc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi2wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi3_ahb_cwk = {
	.hawt_weg = 0x55100,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55100,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi3_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi3_cwk = {
	.hawt_weg = 0x550f8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x550f8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi3pix_cwk = {
	.hawt_weg = 0x55110,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55110,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi3pix_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi3wdi_cwk = {
	.hawt_weg = 0x55108,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55108,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi3wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csi3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi_vfe0_cwk = {
	.hawt_weg = 0x54074,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54074,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi_vfe0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_vfe0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csi_vfe1_cwk = {
	.hawt_weg = 0x54080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csi_vfe1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_vfe1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csiphy0_cwk = {
	.hawt_weg = 0x55018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csiphy1_cwk = {
	.hawt_weg = 0x5501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_csiphy2_cwk = {
	.hawt_weg = 0x55020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_csiphy_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_gp0_cwk = {
	.hawt_weg = 0x50018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_gp0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_gp0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_gp1_cwk = {
	.hawt_weg = 0x50034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_ispif_ahb_cwk = {
	.hawt_weg = 0x540a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x540a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_ispif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_jpeg_ahb_cwk = {
	.hawt_weg = 0x52048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_jpeg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_jpeg_axi_cwk = {
	.hawt_weg = 0x5204c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5204c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_jpeg_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_jpeg_cwk = {
	.hawt_weg = 0x52040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_jpeg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_jpeg_cwk_swc.cwkw.hw,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
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
			.pawent_hws = (const stwuct cwk_hw*[]){
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
			.pawent_hws = (const stwuct cwk_hw*[]){
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_mcwk3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_micwo_ahb_cwk = {
	.hawt_weg = 0x560b0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x560b0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_micwo_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_thwottwe_nwt_axi_cwk = {
	.hawt_weg = 0x560a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(27),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_thwottwe_nwt_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_thwottwe_wt_axi_cwk = {
	.hawt_weg = 0x560a8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(26),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_thwottwe_wt_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_top_ahb_cwk = {
	.hawt_weg = 0x560a0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x560a0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_top_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe0_ahb_cwk = {
	.hawt_weg = 0x54034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe0_cwk = {
	.hawt_weg = 0x54028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_vfe0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe0_stweam_cwk = {
	.hawt_weg = 0x54030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe0_stweam_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_vfe0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe1_ahb_cwk = {
	.hawt_weg = 0x5406c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5406c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe1_cwk = {
	.hawt_weg = 0x54060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_vfe1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe1_stweam_cwk = {
	.hawt_weg = 0x54068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe1_stweam_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_vfe1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe_tsctw_cwk = {
	.hawt_weg = 0x5409c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5409c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe_tsctw_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe_vbif_ahb_cwk = {
	.hawt_weg = 0x5408c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5408c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe_vbif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_camss_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_camss_vfe_vbif_axi_cwk = {
	.hawt_weg = 0x54090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_camss_vfe_vbif_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_ahb_cwk = {
	.hawt_weg = 0x2700c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2700c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_axi_cwk = {
	.hawt_weg = 0x27008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ce1_cwk = {
	.hawt_weg = 0x27004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ce1_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_cfg_noc_usb3_pwim_axi_cwk = {
	.hawt_weg = 0x1a084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a084,
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

static stwuct cwk_bwanch gcc_cpuss_gnoc_cwk = {
	.hawt_weg = 0x2b004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x2b004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(22),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_cpuss_gnoc_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_ahb_cwk = {
	.hawt_weg = 0x1700c,
	.hawt_check = BWANCH_HAWT,
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

static stwuct cwk_bwanch gcc_disp_gpww0_div_cwk_swc = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_gpww0_div_cwk_swc",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0_out_eawwy.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_hf_axi_cwk = {
	.hawt_weg = 0x17020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x17020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_hf_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_thwottwe_cowe_cwk = {
	.hawt_weg = 0x17064,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_thwottwe_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_disp_xo_cwk = {
	.hawt_weg = 0x1702c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1702c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_disp_xo_cwk",
			.fwags = CWK_IS_CWITICAW,
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
	.hawt_weg = 0x4e000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e000,
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
	.hawt_weg = 0x4f000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f000,
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
	.hawt_weg = 0x36004,
	.hawt_check = BWANCH_HAWT,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0_out_eawwy.cwkw.hw,
			},
			.num_pawents = 1,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0_out_aux2.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_memnoc_gfx_cwk = {
	.hawt_weg = 0x3600c,
	.hawt_check = BWANCH_VOTED,
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
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(31),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_thwottwe_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gpu_thwottwe_xo_cwk = {
	.hawt_weg = 0x36044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gpu_thwottwe_xo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_vs_cwk = {
	.hawt_weg = 0x42048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42048,
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

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x2000c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2000c,
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
	.hawt_weg = 0x20004,
	.hawt_check = BWANCH_HAWT,
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
	.hawt_check = BWANCH_HAWT,
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
	.hawt_check = BWANCH_HAWT,
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
	.hawt_check = BWANCH_HAWT,
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
	.hawt_weg = 0x1f274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x1f3a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x1f4d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x1f604,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x1f734,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x39014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(18),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap1_cowe_2x_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap1_cowe_cwk = {
	.hawt_weg = 0x3900c,
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
	.hawt_weg = 0x39144,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x39274,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x393a4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x394d4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x39604,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x39734,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
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
	.hawt_weg = 0x1f004,
	.hawt_check = BWANCH_HAWT_VOTED,
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
	.hawt_weg = 0x39004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(20),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qupv3_wwap_1_m_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qupv3_wwap_1_s_ahb_cwk = {
	.hawt_weg = 0x39008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x39008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x7900c,
		.enabwe_mask = BIT(21),
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
	.hawt_weg = 0x3800c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3800c,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_compute_sf_axi_cwk = {
	.hawt_weg = 0x1050c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1050c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_compute_sf_axi_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_cpuss_ahb_cwk = {
	.hawt_weg = 0x2b06c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_cpuss_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
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
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_usb3_pwim_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_usb30_pwim_mastew_cwk_swc.cwkw.hw,
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
	.hawt_weg = 0x45014,
	.hawt_check = BWANCH_HAWT,
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
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x45010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45010,
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
	.hawt_weg = 0x45044,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x45044,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45044,
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
	.hawt_weg = 0x45078,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x45078,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45078,
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
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x45040,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x45040,
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
	.hawt_weg = 0x1a010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a010,
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
	.hawt_weg = 0x1a018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1a018,
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

static stwuct cwk_bwanch gcc_usb3_pwim_cwkwef_cwk = {
	.hawt_weg = 0x80278,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x80278,
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
		.enabwe_weg = 0x1a058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_pwim_phy_pipe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vdda_vs_cwk = {
	.hawt_weg = 0x4200c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4200c,
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
	.hawt_weg = 0x42004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42004,
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
	.hawt_weg = 0x42008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42008,
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
	.hawt_weg = 0x17004,
	.hawt_check = BWANCH_HAWT,
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
	.hawt_check = BWANCH_HAWT,
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
	.cwkw = {
		.enabwe_weg = 0x79004,
		.enabwe_mask = BIT(28),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_video_thwottwe_cowe_cwk",
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
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vs_ctww_ahb_cwk = {
	.hawt_weg = 0x42014,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x42014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x42014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_vs_ctww_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_vs_ctww_cwk = {
	.hawt_weg = 0x42010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42010,
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

static stwuct cwk_bwanch gcc_wcss_vs_cwk = {
	.hawt_weg = 0x42050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wcss_vs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_vsensow_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc usb30_pwim_gdsc = {
	.gdscw = 0x1a004,
	.pd = {
		.name = "usb30_pwim_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ufs_phy_gdsc = {
	.gdscw = 0x45004,
	.pd = {
		.name = "ufs_phy_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_vfe0_gdsc = {
	.gdscw = 0x54004,
	.pd = {
		.name = "camss_vfe0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_vfe1_gdsc = {
	.gdscw = 0x5403c,
	.pd = {
		.name = "camss_vfe1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_top_gdsc = {
	.gdscw = 0x5607c,
	.pd = {
		.name = "camss_top_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc cam_cpp_gdsc = {
	.gdscw = 0x560bc,
	.pd = {
		.name = "cam_cpp_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc hwos1_vote_tuwing_mmu_tbu1_gdsc = {
	.gdscw = 0x7d060,
	.pd = {
		.name = "hwos1_vote_tuwing_mmu_tbu1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_mm_snoc_mmu_tbu_wt_gdsc = {
	.gdscw = 0x80074,
	.pd = {
		.name = "hwos1_vote_mm_snoc_mmu_tbu_wt_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_mm_snoc_mmu_tbu_nwt_gdsc = {
	.gdscw = 0x80084,
	.pd = {
		.name = "hwos1_vote_mm_snoc_mmu_tbu_nwt_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};


static stwuct gdsc hwos1_vote_tuwing_mmu_tbu0_gdsc = {
	.gdscw = 0x80094,
	.pd = {
		.name = "hwos1_vote_tuwing_mmu_tbu0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc *gcc_sm6125_gdscs[] = {
	[USB30_PWIM_GDSC] = &usb30_pwim_gdsc,
	[UFS_PHY_GDSC] = &ufs_phy_gdsc,
	[CAMSS_VFE0_GDSC] = &camss_vfe0_gdsc,
	[CAMSS_VFE1_GDSC] = &camss_vfe1_gdsc,
	[CAMSS_TOP_GDSC] = &camss_top_gdsc,
	[CAM_CPP_GDSC] = &cam_cpp_gdsc,
	[HWOS1_VOTE_TUWING_MMU_TBU1_GDSC] = &hwos1_vote_tuwing_mmu_tbu1_gdsc,
	[HWOS1_VOTE_MM_SNOC_MMU_TBU_WT_GDSC] = &hwos1_vote_mm_snoc_mmu_tbu_wt_gdsc,
	[HWOS1_VOTE_MM_SNOC_MMU_TBU_NWT_GDSC] = &hwos1_vote_mm_snoc_mmu_tbu_nwt_gdsc,
	[HWOS1_VOTE_TUWING_MMU_TBU0_GDSC] = &hwos1_vote_tuwing_mmu_tbu0_gdsc,
};

static stwuct cwk_hw *gcc_sm6125_hws[] = {
	[GPWW0_OUT_AUX2] = &gpww0_out_aux2.hw,
	[GPWW0_OUT_MAIN] = &gpww0_out_main.hw,
	[GPWW6_OUT_MAIN] = &gpww6_out_main.hw,
	[GPWW7_OUT_MAIN] = &gpww7_out_main.hw,
	[GPWW8_OUT_MAIN] = &gpww8_out_main.hw,
	[GPWW9_OUT_MAIN] = &gpww9_out_main.hw,
};

static stwuct cwk_wegmap *gcc_sm6125_cwocks[] = {
	[GCC_AHB2PHY_CSI_CWK] = &gcc_ahb2phy_csi_cwk.cwkw,
	[GCC_AHB2PHY_USB_CWK] = &gcc_ahb2phy_usb_cwk.cwkw,
	[GCC_APC_VS_CWK] = &gcc_apc_vs_cwk.cwkw,
	[GCC_BIMC_GPU_AXI_CWK] = &gcc_bimc_gpu_axi_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CAMEWA_AHB_CWK] = &gcc_camewa_ahb_cwk.cwkw,
	[GCC_CAMEWA_XO_CWK] = &gcc_camewa_xo_cwk.cwkw,
	[GCC_CAMSS_AHB_CWK_SWC] = &gcc_camss_ahb_cwk_swc.cwkw,
	[GCC_CAMSS_CCI_AHB_CWK] = &gcc_camss_cci_ahb_cwk.cwkw,
	[GCC_CAMSS_CCI_CWK] = &gcc_camss_cci_cwk.cwkw,
	[GCC_CAMSS_CCI_CWK_SWC] = &gcc_camss_cci_cwk_swc.cwkw,
	[GCC_CAMSS_CPHY_CSID0_CWK] = &gcc_camss_cphy_csid0_cwk.cwkw,
	[GCC_CAMSS_CPHY_CSID1_CWK] = &gcc_camss_cphy_csid1_cwk.cwkw,
	[GCC_CAMSS_CPHY_CSID2_CWK] = &gcc_camss_cphy_csid2_cwk.cwkw,
	[GCC_CAMSS_CPHY_CSID3_CWK] = &gcc_camss_cphy_csid3_cwk.cwkw,
	[GCC_CAMSS_CPP_AHB_CWK] = &gcc_camss_cpp_ahb_cwk.cwkw,
	[GCC_CAMSS_CPP_AXI_CWK] = &gcc_camss_cpp_axi_cwk.cwkw,
	[GCC_CAMSS_CPP_CWK] = &gcc_camss_cpp_cwk.cwkw,
	[GCC_CAMSS_CPP_CWK_SWC] = &gcc_camss_cpp_cwk_swc.cwkw,
	[GCC_CAMSS_CPP_VBIF_AHB_CWK] = &gcc_camss_cpp_vbif_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI0_AHB_CWK] = &gcc_camss_csi0_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI0_CWK] = &gcc_camss_csi0_cwk.cwkw,
	[GCC_CAMSS_CSI0_CWK_SWC] = &gcc_camss_csi0_cwk_swc.cwkw,
	[GCC_CAMSS_CSI0PHYTIMEW_CWK] = &gcc_camss_csi0phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI0PHYTIMEW_CWK_SWC] = &gcc_camss_csi0phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_CSI0PIX_CWK] = &gcc_camss_csi0pix_cwk.cwkw,
	[GCC_CAMSS_CSI0WDI_CWK] = &gcc_camss_csi0wdi_cwk.cwkw,
	[GCC_CAMSS_CSI1_AHB_CWK] = &gcc_camss_csi1_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI1_CWK] = &gcc_camss_csi1_cwk.cwkw,
	[GCC_CAMSS_CSI1_CWK_SWC] = &gcc_camss_csi1_cwk_swc.cwkw,
	[GCC_CAMSS_CSI1PHYTIMEW_CWK] = &gcc_camss_csi1phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI1PHYTIMEW_CWK_SWC] = &gcc_camss_csi1phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_CSI1PIX_CWK] = &gcc_camss_csi1pix_cwk.cwkw,
	[GCC_CAMSS_CSI1WDI_CWK] = &gcc_camss_csi1wdi_cwk.cwkw,
	[GCC_CAMSS_CSI2_AHB_CWK] = &gcc_camss_csi2_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI2_CWK] = &gcc_camss_csi2_cwk.cwkw,
	[GCC_CAMSS_CSI2_CWK_SWC] = &gcc_camss_csi2_cwk_swc.cwkw,
	[GCC_CAMSS_CSI2PHYTIMEW_CWK] = &gcc_camss_csi2phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI2PHYTIMEW_CWK_SWC] = &gcc_camss_csi2phytimew_cwk_swc.cwkw,
	[GCC_CAMSS_CSI2PIX_CWK] = &gcc_camss_csi2pix_cwk.cwkw,
	[GCC_CAMSS_CSI2WDI_CWK] = &gcc_camss_csi2wdi_cwk.cwkw,
	[GCC_CAMSS_CSI3_AHB_CWK] = &gcc_camss_csi3_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI3_CWK] = &gcc_camss_csi3_cwk.cwkw,
	[GCC_CAMSS_CSI3_CWK_SWC] = &gcc_camss_csi3_cwk_swc.cwkw,
	[GCC_CAMSS_CSI3PIX_CWK] = &gcc_camss_csi3pix_cwk.cwkw,
	[GCC_CAMSS_CSI3WDI_CWK] = &gcc_camss_csi3wdi_cwk.cwkw,
	[GCC_CAMSS_CSI_VFE0_CWK] = &gcc_camss_csi_vfe0_cwk.cwkw,
	[GCC_CAMSS_CSI_VFE1_CWK] = &gcc_camss_csi_vfe1_cwk.cwkw,
	[GCC_CAMSS_CSIPHY0_CWK] = &gcc_camss_csiphy0_cwk.cwkw,
	[GCC_CAMSS_CSIPHY1_CWK] = &gcc_camss_csiphy1_cwk.cwkw,
	[GCC_CAMSS_CSIPHY2_CWK] = &gcc_camss_csiphy2_cwk.cwkw,
	[GCC_CAMSS_CSIPHY_CWK_SWC] = &gcc_camss_csiphy_cwk_swc.cwkw,
	[GCC_CAMSS_GP0_CWK] = &gcc_camss_gp0_cwk.cwkw,
	[GCC_CAMSS_GP0_CWK_SWC] = &gcc_camss_gp0_cwk_swc.cwkw,
	[GCC_CAMSS_GP1_CWK] = &gcc_camss_gp1_cwk.cwkw,
	[GCC_CAMSS_GP1_CWK_SWC] = &gcc_camss_gp1_cwk_swc.cwkw,
	[GCC_CAMSS_ISPIF_AHB_CWK] = &gcc_camss_ispif_ahb_cwk.cwkw,
	[GCC_CAMSS_JPEG_AHB_CWK] = &gcc_camss_jpeg_ahb_cwk.cwkw,
	[GCC_CAMSS_JPEG_AXI_CWK] = &gcc_camss_jpeg_axi_cwk.cwkw,
	[GCC_CAMSS_JPEG_CWK] = &gcc_camss_jpeg_cwk.cwkw,
	[GCC_CAMSS_JPEG_CWK_SWC] = &gcc_camss_jpeg_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK0_CWK] = &gcc_camss_mcwk0_cwk.cwkw,
	[GCC_CAMSS_MCWK0_CWK_SWC] = &gcc_camss_mcwk0_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK1_CWK] = &gcc_camss_mcwk1_cwk.cwkw,
	[GCC_CAMSS_MCWK1_CWK_SWC] = &gcc_camss_mcwk1_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK2_CWK] = &gcc_camss_mcwk2_cwk.cwkw,
	[GCC_CAMSS_MCWK2_CWK_SWC] = &gcc_camss_mcwk2_cwk_swc.cwkw,
	[GCC_CAMSS_MCWK3_CWK] = &gcc_camss_mcwk3_cwk.cwkw,
	[GCC_CAMSS_MCWK3_CWK_SWC] = &gcc_camss_mcwk3_cwk_swc.cwkw,
	[GCC_CAMSS_MICWO_AHB_CWK] = &gcc_camss_micwo_ahb_cwk.cwkw,
	[GCC_CAMSS_THWOTTWE_NWT_AXI_CWK] = &gcc_camss_thwottwe_nwt_axi_cwk.cwkw,
	[GCC_CAMSS_THWOTTWE_WT_AXI_CWK] = &gcc_camss_thwottwe_wt_axi_cwk.cwkw,
	[GCC_CAMSS_TOP_AHB_CWK] = &gcc_camss_top_ahb_cwk.cwkw,
	[GCC_CAMSS_VFE0_AHB_CWK] = &gcc_camss_vfe0_ahb_cwk.cwkw,
	[GCC_CAMSS_VFE0_CWK] = &gcc_camss_vfe0_cwk.cwkw,
	[GCC_CAMSS_VFE0_CWK_SWC] = &gcc_camss_vfe0_cwk_swc.cwkw,
	[GCC_CAMSS_VFE0_STWEAM_CWK] = &gcc_camss_vfe0_stweam_cwk.cwkw,
	[GCC_CAMSS_VFE1_AHB_CWK] = &gcc_camss_vfe1_ahb_cwk.cwkw,
	[GCC_CAMSS_VFE1_CWK] = &gcc_camss_vfe1_cwk.cwkw,
	[GCC_CAMSS_VFE1_CWK_SWC] = &gcc_camss_vfe1_cwk_swc.cwkw,
	[GCC_CAMSS_VFE1_STWEAM_CWK] = &gcc_camss_vfe1_stweam_cwk.cwkw,
	[GCC_CAMSS_VFE_TSCTW_CWK] = &gcc_camss_vfe_tsctw_cwk.cwkw,
	[GCC_CAMSS_VFE_VBIF_AHB_CWK] = &gcc_camss_vfe_vbif_ahb_cwk.cwkw,
	[GCC_CAMSS_VFE_VBIF_AXI_CWK] = &gcc_camss_vfe_vbif_axi_cwk.cwkw,
	[GCC_CE1_AHB_CWK] = &gcc_ce1_ahb_cwk.cwkw,
	[GCC_CE1_AXI_CWK] = &gcc_ce1_axi_cwk.cwkw,
	[GCC_CE1_CWK] = &gcc_ce1_cwk.cwkw,
	[GCC_CFG_NOC_USB3_PWIM_AXI_CWK] = &gcc_cfg_noc_usb3_pwim_axi_cwk.cwkw,
	[GCC_CPUSS_GNOC_CWK] = &gcc_cpuss_gnoc_cwk.cwkw,
	[GCC_DISP_AHB_CWK] = &gcc_disp_ahb_cwk.cwkw,
	[GCC_DISP_GPWW0_DIV_CWK_SWC] = &gcc_disp_gpww0_div_cwk_swc.cwkw,
	[GCC_DISP_HF_AXI_CWK] = &gcc_disp_hf_axi_cwk.cwkw,
	[GCC_DISP_THWOTTWE_COWE_CWK] = &gcc_disp_thwottwe_cowe_cwk.cwkw,
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
	[GCC_GPU_MEMNOC_GFX_CWK] = &gcc_gpu_memnoc_gfx_cwk.cwkw,
	[GCC_GPU_SNOC_DVM_GFX_CWK] = &gcc_gpu_snoc_dvm_gfx_cwk.cwkw,
	[GCC_GPU_THWOTTWE_COWE_CWK] = &gcc_gpu_thwottwe_cowe_cwk.cwkw,
	[GCC_GPU_THWOTTWE_XO_CWK] = &gcc_gpu_thwottwe_xo_cwk.cwkw,
	[GCC_MSS_VS_CWK] = &gcc_mss_vs_cwk.cwkw,
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
	[GCC_SYS_NOC_COMPUTE_SF_AXI_CWK] = &gcc_sys_noc_compute_sf_axi_cwk.cwkw,
	[GCC_SYS_NOC_CPUSS_AHB_CWK] = &gcc_sys_noc_cpuss_ahb_cwk.cwkw,
	[GCC_SYS_NOC_UFS_PHY_AXI_CWK] = &gcc_sys_noc_ufs_phy_axi_cwk.cwkw,
	[GCC_SYS_NOC_USB3_PWIM_AXI_CWK] = &gcc_sys_noc_usb3_pwim_axi_cwk.cwkw,
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
	[GCC_USB3_PWIM_PHY_AUX_CWK_SWC] = &gcc_usb3_pwim_phy_aux_cwk_swc.cwkw,
	[GCC_USB3_PWIM_PHY_COM_AUX_CWK] = &gcc_usb3_pwim_phy_com_aux_cwk.cwkw,
	[GCC_USB3_PWIM_PHY_PIPE_CWK] = &gcc_usb3_pwim_phy_pipe_cwk.cwkw,
	[GCC_VDDA_VS_CWK] = &gcc_vdda_vs_cwk.cwkw,
	[GCC_VDDCX_VS_CWK] = &gcc_vddcx_vs_cwk.cwkw,
	[GCC_VDDMX_VS_CWK] = &gcc_vddmx_vs_cwk.cwkw,
	[GCC_VIDEO_AHB_CWK] = &gcc_video_ahb_cwk.cwkw,
	[GCC_VIDEO_AXI0_CWK] = &gcc_video_axi0_cwk.cwkw,
	[GCC_VIDEO_THWOTTWE_COWE_CWK] = &gcc_video_thwottwe_cowe_cwk.cwkw,
	[GCC_VIDEO_XO_CWK] = &gcc_video_xo_cwk.cwkw,
	[GCC_VS_CTWW_AHB_CWK] = &gcc_vs_ctww_ahb_cwk.cwkw,
	[GCC_VS_CTWW_CWK] = &gcc_vs_ctww_cwk.cwkw,
	[GCC_VS_CTWW_CWK_SWC] = &gcc_vs_ctww_cwk_swc.cwkw,
	[GCC_VSENSOW_CWK_SWC] = &gcc_vsensow_cwk_swc.cwkw,
	[GCC_WCSS_VS_CWK] = &gcc_wcss_vs_cwk.cwkw,
	[GPWW0_OUT_EAWWY] = &gpww0_out_eawwy.cwkw,
	[GPWW3_OUT_EAWWY] = &gpww3_out_eawwy.cwkw,
	[GPWW4_OUT_MAIN] = &gpww4_out_main.cwkw,
	[GPWW5_OUT_MAIN] = &gpww5_out_main.cwkw,
	[GPWW6_OUT_EAWWY] = &gpww6_out_eawwy.cwkw,
	[GPWW7_OUT_EAWWY] = &gpww7_out_eawwy.cwkw,
	[GPWW8_OUT_EAWWY] = &gpww8_out_eawwy.cwkw,
	[GPWW9_OUT_EAWWY] = &gpww9_out_eawwy.cwkw,
	[GCC_USB3_PWIM_CWKWEF_CWK] = &gcc_usb3_pwim_cwkwef_cwk.cwkw,
};

static const stwuct qcom_weset_map gcc_sm6125_wesets[] = {
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x1c000 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x1c004 },
	[GCC_UFS_PHY_BCW] = { 0x45000 },
	[GCC_USB30_PWIM_BCW] = { 0x1a000 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x1d000 },
	[GCC_USB3PHY_PHY_PWIM_SP0_BCW] = { 0x1b008 },
	[GCC_USB3_PHY_PWIM_SP0_BCW] = { 0x1b000 },
	[GCC_CAMSS_MICWO_BCW] = { 0x560ac },
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

static const stwuct wegmap_config gcc_sm6125_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xc7000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gcc_sm6125_desc = {
	.config = &gcc_sm6125_wegmap_config,
	.cwks = gcc_sm6125_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_sm6125_cwocks),
	.cwk_hws = gcc_sm6125_hws,
	.num_cwk_hws = AWWAY_SIZE(gcc_sm6125_hws),
	.wesets = gcc_sm6125_wesets,
	.num_wesets = AWWAY_SIZE(gcc_sm6125_wesets),
	.gdscs = gcc_sm6125_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_sm6125_gdscs),
};

static const stwuct of_device_id gcc_sm6125_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-sm6125" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_sm6125_match_tabwe);

static int gcc_sm6125_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = qcom_cc_map(pdev, &gcc_sm6125_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/*
	 * Disabwe the GPWW0 active input to video bwock via
	 * MISC wegistews.
	 */
	wegmap_update_bits(wegmap, 0x80258, 0x1, 0x1);

	/*
	 * Enabwe DUAW_EDGE mode fow MCWK WCGs
	 * This is wequiwed to enabwe MND dividew mode
	 */
	wegmap_update_bits(wegmap, 0x51004, 0x3000, 0x2000);
	wegmap_update_bits(wegmap, 0x51020, 0x3000, 0x2000);
	wegmap_update_bits(wegmap, 0x5103c, 0x3000, 0x2000);
	wegmap_update_bits(wegmap, 0x51058, 0x3000, 0x2000);

	wet = qcom_cc_wegistew_wcg_dfs(wegmap, gcc_dfs_cwocks,
						AWWAY_SIZE(gcc_dfs_cwocks));
	if (wet)
		wetuwn wet;

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_sm6125_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_sm6125_dwivew = {
	.pwobe = gcc_sm6125_pwobe,
	.dwivew = {
		.name = "gcc-sm6125",
		.of_match_tabwe = gcc_sm6125_match_tabwe,
	},
};

static int __init gcc_sm6125_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_sm6125_dwivew);
}
subsys_initcaww(gcc_sm6125_init);

static void __exit gcc_sm6125_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_sm6125_dwivew);
}
moduwe_exit(gcc_sm6125_exit);

MODUWE_DESCWIPTION("QTI GCC SM6125 Dwivew");
MODUWE_WICENSE("GPW v2");
