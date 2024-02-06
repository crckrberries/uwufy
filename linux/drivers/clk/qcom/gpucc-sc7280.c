// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gpucc-sc7280.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_GCC_GPU_GPWW0_CWK_SWC,
	P_GCC_GPU_GPWW0_DIV_CWK_SWC,
	P_GPU_CC_PWW0_OUT_MAIN,
	P_GPU_CC_PWW1_OUT_MAIN,
};

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct cwk_awpha_pww gpu_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

/* 500MHz Configuwation */
static const stwuct awpha_pww_config gpu_cc_pww1_config = {
	.w = 0x1A,
	.awpha = 0xAAA,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww gpu_cc_pww1 = {
	.offset = 0x100,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct pawent_map gpu_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW0_OUT_MAIN, 1 },
	{ P_GPU_CC_PWW1_OUT_MAIN, 3 },
	{ P_GCC_GPU_GPWW0_CWK_SWC, 5 },
	{ P_GCC_GPU_GPWW0_DIV_CWK_SWC, 6 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &gpu_cc_pww0.cwkw.hw },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .fw_name = "gcc_gpu_gpww0_cwk_swc" },
	{ .fw_name = "gcc_gpu_gpww0_div_cwk_swc" },
};

static const stwuct pawent_map gpu_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW1_OUT_MAIN, 3 },
	{ P_GCC_GPU_GPWW0_CWK_SWC, 5 },
	{ P_GCC_GPU_GPWW0_DIV_CWK_SWC, 6 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo", },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .fw_name = "gcc_gpu_gpww0_cwk_swc", },
	{ .fw_name = "gcc_gpu_gpww0_div_cwk_swc", },
};

static const stwuct fweq_tbw ftbw_gpu_cc_gmu_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GCC_GPU_GPWW0_DIV_CWK_SWC, 1.5, 0, 0),
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
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gpu_cc_hub_cwk_swc[] = {
	F(150000000, P_GCC_GPU_GPWW0_DIV_CWK_SWC, 2, 0, 0),
	F(240000000, P_GCC_GPU_GPWW0_CWK_SWC, 2.5, 0, 0),
	F(300000000, P_GCC_GPU_GPWW0_CWK_SWC, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gpu_cc_hub_cwk_swc = {
	.cmd_wcgw = 0x117c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gpu_cc_pawent_map_1,
	.fweq_tbw = ftbw_gpu_cc_hub_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpu_cc_hub_cwk_swc",
		.pawent_data = gpu_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gpu_cc_pawent_data_1),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wegmap_div gpu_cc_hub_ahb_div_cwk_swc = {
	.weg = 0x11c0,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpu_cc_hub_ahb_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpu_cc_hub_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div gpu_cc_hub_cx_int_div_cwk_swc = {
	.weg = 0x11bc,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpu_cc_hub_cx_int_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpu_cc_hub_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_hub_ahb_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cwc_ahb_cwk = {
	.hawt_weg = 0x107c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x107c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cwc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_hub_ahb_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
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
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_snoc_dvm_cwk = {
	.hawt_weg = 0x108c,
	.hawt_check = BWANCH_HAWT_VOTED,
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
	.hawt_check = BWANCH_HAWT_VOTED,
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
			.ops = &cwk_bwanch2_aon_ops,
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

static stwuct cwk_bwanch gpu_cc_hwos1_vote_gpu_smmu_cwk = {
	.hawt_weg = 0x5000,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_hwos1_vote_gpu_smmu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_hub_aon_cwk = {
	.hawt_weg = 0x1178,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1178,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_hub_aon_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_hub_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_hub_cx_int_cwk = {
	.hawt_weg = 0x1204,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1204,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_hub_cx_int_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_hub_cx_int_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_mnd1x_0_gfx3d_cwk = {
	.hawt_weg = 0x802c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x802c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_mnd1x_0_gfx3d_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_mnd1x_1_gfx3d_cwk = {
	.hawt_weg = 0x8030,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x8030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_mnd1x_1_gfx3d_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_sweep_cwk = {
	.hawt_weg = 0x1090,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x1090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc cx_gdsc = {
	.gdscw = 0x106c,
	.gds_hw_ctww = 0x1540,
	.pd = {
		.name = "cx_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE | WETAIN_FF_ENABWE,
};

static stwuct gdsc gx_gdsc = {
	.gdscw = 0x100c,
	.cwamp_io_ctww = 0x1508,
	.pd = {
		.name = "gx_gdsc",
		.powew_on = gdsc_gx_do_nothing_enabwe,
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = CWAMP_IO | WETAIN_FF_ENABWE,
};

static stwuct gdsc *gpu_cc_sc7180_gdscs[] = {
	[GPU_CC_CX_GDSC] = &cx_gdsc,
	[GPU_CC_GX_GDSC] = &gx_gdsc,
};

static stwuct cwk_wegmap *gpu_cc_sc7280_cwocks[] = {
	[GPU_CC_AHB_CWK] = &gpu_cc_ahb_cwk.cwkw,
	[GPU_CC_CWC_AHB_CWK] = &gpu_cc_cwc_ahb_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpu_cc_cx_gmu_cwk.cwkw,
	[GPU_CC_CX_SNOC_DVM_CWK] = &gpu_cc_cx_snoc_dvm_cwk.cwkw,
	[GPU_CC_CXO_AON_CWK] = &gpu_cc_cxo_aon_cwk.cwkw,
	[GPU_CC_CXO_CWK] = &gpu_cc_cxo_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpu_cc_gmu_cwk_swc.cwkw,
	[GPU_CC_GX_GMU_CWK] = &gpu_cc_gx_gmu_cwk.cwkw,
	[GPU_CC_HWOS1_VOTE_GPU_SMMU_CWK] = &gpu_cc_hwos1_vote_gpu_smmu_cwk.cwkw,
	[GPU_CC_HUB_AHB_DIV_CWK_SWC] = &gpu_cc_hub_ahb_div_cwk_swc.cwkw,
	[GPU_CC_HUB_AON_CWK] = &gpu_cc_hub_aon_cwk.cwkw,
	[GPU_CC_HUB_CWK_SWC] = &gpu_cc_hub_cwk_swc.cwkw,
	[GPU_CC_HUB_CX_INT_CWK] = &gpu_cc_hub_cx_int_cwk.cwkw,
	[GPU_CC_HUB_CX_INT_DIV_CWK_SWC] = &gpu_cc_hub_cx_int_div_cwk_swc.cwkw,
	[GPU_CC_MND1X_0_GFX3D_CWK] = &gpu_cc_mnd1x_0_gfx3d_cwk.cwkw,
	[GPU_CC_MND1X_1_GFX3D_CWK] = &gpu_cc_mnd1x_1_gfx3d_cwk.cwkw,
	[GPU_CC_PWW0] = &gpu_cc_pww0.cwkw,
	[GPU_CC_PWW1] = &gpu_cc_pww1.cwkw,
	[GPU_CC_SWEEP_CWK] = &gpu_cc_sweep_cwk.cwkw,
};

static const stwuct wegmap_config gpu_cc_sc7280_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x8030,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gpu_cc_sc7280_desc = {
	.config = &gpu_cc_sc7280_wegmap_config,
	.cwks = gpu_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(gpu_cc_sc7280_cwocks),
	.gdscs = gpu_cc_sc7180_gdscs,
	.num_gdscs = AWWAY_SIZE(gpu_cc_sc7180_gdscs),
};

static const stwuct of_device_id gpu_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpu_cc_sc7280_match_tabwe);

static int gpu_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gpu_cc_sc7280_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_pww_configuwe(&gpu_cc_pww1, wegmap, &gpu_cc_pww1_config);

	/*
	 * Keep the cwocks awways-ON
	 * GPU_CC_CB_CWK, GPUCC_CX_GMU_CWK
	 */
	wegmap_update_bits(wegmap, 0x1170, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x1098, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x1098, BIT(13), BIT(13));

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpu_cc_sc7280_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpu_cc_sc7280_dwivew = {
	.pwobe = gpu_cc_sc7280_pwobe,
	.dwivew = {
		.name = "gpu_cc-sc7280",
		.of_match_tabwe = gpu_cc_sc7280_match_tabwe,
	},
};

static int __init gpu_cc_sc7280_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpu_cc_sc7280_dwivew);
}
subsys_initcaww(gpu_cc_sc7280_init);

static void __exit gpu_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpu_cc_sc7280_dwivew);
}
moduwe_exit(gpu_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI GPU_CC SC7280 Dwivew");
MODUWE_WICENSE("GPW v2");
