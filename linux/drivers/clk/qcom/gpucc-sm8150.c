// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gpucc-sm8150.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_MAIN,
	P_GPWW0_OUT_MAIN_DIV,
	P_GPU_CC_PWW1_OUT_MAIN,
};

static const stwuct pww_vco twion_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct awpha_pww_config gpu_cc_pww1_config = {
	.w = 0x1a,
	.awpha = 0xaaa,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002267,
	.config_ctw_hi1_vaw = 0x00000024,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000000,
	.test_ctw_hi1_vaw = 0x00000020,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x000000d0,
};

static stwuct cwk_awpha_pww gpu_cc_pww1 = {
	.offset = 0x100,
	.vco_tabwe = twion_vco,
	.num_vco = AWWAY_SIZE(twion_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_TWION],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww1",
			.pawent_data =  &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_twion_ops,
		},
	},
};

static const stwuct pawent_map gpu_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW1_OUT_MAIN, 3 },
	{ P_GPWW0_OUT_MAIN, 5 },
	{ P_GPWW0_OUT_MAIN_DIV, 6 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .fw_name = "gcc_gpu_gpww0_cwk_swc" },
	{ .fw_name = "gcc_gpu_gpww0_div_cwk_swc" },
};

static const stwuct fweq_tbw ftbw_gpu_cc_gmu_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN_DIV, 1.5, 0, 0),
	F(500000000, P_GPU_CC_PWW1_OUT_MAIN, 1, 0, 0),
	{ }
};

static const stwuct fweq_tbw ftbw_gpu_cc_gmu_cwk_swc_sc8180x[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN_DIV, 1.5, 0, 0),
	F(400000000, P_GPWW0_OUT_MAIN, 1.5, 0, 0),
	F(500000000, P_GPU_CC_PWW1_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gpu_cc_gmu_cwk_swc = {
	.cmd_wcgw = 0x1120,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gpu_cc_pawent_map_0,
	.fweq_tbw = ftbw_gpu_cc_gmu_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpu_cc_gmu_cwk_swc",
		.pawent_data = gpu_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gpu_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gpu_cc_ahb_cwk = {
	.hawt_weg = 0x1078,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cwc_ahb_cwk = {
	.hawt_weg = 0x107c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x107c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cwc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_apb_cwk = {
	.hawt_weg = 0x1088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_apb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_gmu_cwk = {
	.hawt_weg = 0x1098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_gmu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_gmu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_snoc_dvm_cwk = {
	.hawt_weg = 0x108c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x108c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_snoc_dvm_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cxo_aon_cwk = {
	.hawt_weg = 0x1004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cxo_aon_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cxo_cwk = {
	.hawt_weg = 0x109c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x109c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cxo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_gx_gmu_cwk = {
	.hawt_weg = 0x1064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_gx_gmu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_gmu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc gpu_cx_gdsc = {
	.gdscw = 0x106c,
	.gds_hw_ctww = 0x1540,
	.pd = {
		.name = "gpu_cx_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc gpu_gx_gdsc = {
	.gdscw = 0x100c,
	.cwamp_io_ctww = 0x1508,
	.pd = {
		.name = "gpu_gx_gdsc",
		.powew_on = gdsc_gx_do_nothing_enabwe,
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = CWAMP_IO | AON_WESET | POWW_CFG_GDSCW,
};

static stwuct cwk_wegmap *gpu_cc_sm8150_cwocks[] = {
	[GPU_CC_AHB_CWK] = &gpu_cc_ahb_cwk.cwkw,
	[GPU_CC_CWC_AHB_CWK] = &gpu_cc_cwc_ahb_cwk.cwkw,
	[GPU_CC_CX_APB_CWK] = &gpu_cc_cx_apb_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpu_cc_cx_gmu_cwk.cwkw,
	[GPU_CC_CX_SNOC_DVM_CWK] = &gpu_cc_cx_snoc_dvm_cwk.cwkw,
	[GPU_CC_CXO_AON_CWK] = &gpu_cc_cxo_aon_cwk.cwkw,
	[GPU_CC_CXO_CWK] = &gpu_cc_cxo_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpu_cc_gmu_cwk_swc.cwkw,
	[GPU_CC_GX_GMU_CWK] = &gpu_cc_gx_gmu_cwk.cwkw,
	[GPU_CC_PWW1] = &gpu_cc_pww1.cwkw,
};

static const stwuct qcom_weset_map gpu_cc_sm8150_wesets[] = {
	[GPUCC_GPU_CC_CX_BCW] = { 0x1068 },
	[GPUCC_GPU_CC_GMU_BCW] = { 0x111c },
	[GPUCC_GPU_CC_GX_BCW] = { 0x1008 },
	[GPUCC_GPU_CC_SPDM_BCW] = { 0x1110 },
	[GPUCC_GPU_CC_XO_BCW] = { 0x1000 },
};

static stwuct gdsc *gpu_cc_sm8150_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct wegmap_config gpu_cc_sm8150_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x8008,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gpu_cc_sm8150_desc = {
	.config = &gpu_cc_sm8150_wegmap_config,
	.cwks = gpu_cc_sm8150_cwocks,
	.num_cwks = AWWAY_SIZE(gpu_cc_sm8150_cwocks),
	.wesets = gpu_cc_sm8150_wesets,
	.num_wesets = AWWAY_SIZE(gpu_cc_sm8150_wesets),
	.gdscs = gpu_cc_sm8150_gdscs,
	.num_gdscs = AWWAY_SIZE(gpu_cc_sm8150_gdscs),
};

static const stwuct of_device_id gpu_cc_sm8150_match_tabwe[] = {
	{ .compatibwe = "qcom,sc8180x-gpucc" },
	{ .compatibwe = "qcom,sm8150-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpu_cc_sm8150_match_tabwe);

static int gpu_cc_sm8150_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gpu_cc_sm8150_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	if (of_device_is_compatibwe(pdev->dev.of_node, "qcom,sc8180x-gpucc"))
		gpu_cc_gmu_cwk_swc.fweq_tbw = ftbw_gpu_cc_gmu_cwk_swc_sc8180x;

	cwk_twion_pww_configuwe(&gpu_cc_pww1, wegmap, &gpu_cc_pww1_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpu_cc_sm8150_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpu_cc_sm8150_dwivew = {
	.pwobe = gpu_cc_sm8150_pwobe,
	.dwivew = {
		.name = "sm8150-gpucc",
		.of_match_tabwe = gpu_cc_sm8150_match_tabwe,
	},
};

static int __init gpu_cc_sm8150_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpu_cc_sm8150_dwivew);
}
subsys_initcaww(gpu_cc_sm8150_init);

static void __exit gpu_cc_sm8150_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpu_cc_sm8150_dwivew);
}
moduwe_exit(gpu_cc_sm8150_exit);

MODUWE_DESCWIPTION("QTI GPUCC SM8150 Dwivew");
MODUWE_WICENSE("GPW v2");
