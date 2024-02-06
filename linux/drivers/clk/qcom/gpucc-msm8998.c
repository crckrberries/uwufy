// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, Jeffwey Hugo
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gpucc-msm8998.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_XO,
	P_GPWW0,
	P_GPUPWW0_OUT_EVEN,
};

/* Instead of going diwectwy to the bwock, XO is wouted thwough this bwanch */
static stwuct cwk_bwanch gpucc_cxo_cwk = {
	.hawt_weg = 0x1020,
	.cwkw = {
		.enabwe_weg = 0x1020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cxo_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo"
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_IS_CWITICAW,
		},
	},
};

static stwuct pww_vco fabia_vco[] = {
	{ 249600000, 2000000000, 0 },
	{ 125000000, 1000000000, 1 },
};

static const stwuct cwk_div_tabwe post_div_tabwe_fabia_even[] = {
	{ 0x0, 1 },
	{ 0x1, 2 },
	{ 0x3, 4 },
	{ 0x7, 8 },
	{ }
};

static stwuct cwk_awpha_pww gpupww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpupww0",
		.pawent_hws = (const stwuct cwk_hw *[]){ &gpucc_cxo_cwk.cwkw.hw },
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_fabia_ops,
	},
};

static stwuct cwk_awpha_pww_postdiv gpupww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_fabia_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_fabia_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpupww0_out_even",
		.pawent_hws = (const stwuct cwk_hw *[]){ &gpupww0.cwkw.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static const stwuct pawent_map gpu_xo_gpww0_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 5 },
};

static const stwuct cwk_pawent_data gpu_xo_gpww0[] = {
	{ .hw = &gpucc_cxo_cwk.cwkw.hw },
	{ .fw_name = "gpww0", .name = "gcc_gpu_gpww0_cwk" },
};

static const stwuct pawent_map gpu_xo_gpupww0_map[] = {
	{ P_XO, 0 },
	{ P_GPUPWW0_OUT_EVEN, 1 },
};

static const stwuct cwk_hw *gpu_xo_gpupww0[] = {
	&gpucc_cxo_cwk.cwkw.hw,
	&gpupww0_out_even.cwkw.hw,
};

static const stwuct fweq_tbw ftbw_wbcpw_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wbcpw_cwk_swc = {
	.cmd_wcgw = 0x1030,
	.hid_width = 5,
	.pawent_map = gpu_xo_gpww0_map,
	.fweq_tbw = ftbw_wbcpw_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wbcpw_cwk_swc",
		.pawent_data = gpu_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gpu_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gfx3d_cwk_swc[] = {
	{ .swc = P_GPUPWW0_OUT_EVEN, .pwe_div = 3 },
	{ }
};

static stwuct cwk_wcg2 gfx3d_cwk_swc = {
	.cmd_wcgw = 0x1070,
	.hid_width = 5,
	.pawent_map = gpu_xo_gpupww0_map,
	.fweq_tbw = ftbw_gfx3d_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gfx3d_cwk_swc",
		.pawent_hws = gpu_xo_gpupww0,
		.num_pawents = AWWAY_SIZE(gpu_xo_gpupww0),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
	},
};

static const stwuct fweq_tbw ftbw_wbbmtimew_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wbbmtimew_cwk_swc = {
	.cmd_wcgw = 0x10b0,
	.hid_width = 5,
	.pawent_map = gpu_xo_gpww0_map,
	.fweq_tbw = ftbw_wbbmtimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wbbmtimew_cwk_swc",
		.pawent_data = gpu_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gpu_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gfx3d_isense_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPWW0, 15, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gfx3d_isense_cwk_swc = {
	.cmd_wcgw = 0x1100,
	.hid_width = 5,
	.pawent_map = gpu_xo_gpww0_map,
	.fweq_tbw = ftbw_gfx3d_isense_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gfx3d_isense_cwk_swc",
		.pawent_data = gpu_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gpu_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch wbcpw_cwk = {
	.hawt_weg = 0x1054,
	.cwkw = {
		.enabwe_weg = 0x1054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wbcpw_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &wbcpw_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gfx3d_cwk = {
	.hawt_weg = 0x1098,
	.cwkw = {
		.enabwe_weg = 0x1098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gfx3d_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &gfx3d_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch wbbmtimew_cwk = {
	.hawt_weg = 0x10d0,
	.cwkw = {
		.enabwe_weg = 0x10d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wbbmtimew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &wbbmtimew_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gfx3d_isense_cwk = {
	.hawt_weg = 0x1124,
	.cwkw = {
		.enabwe_weg = 0x1124,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gfx3d_isense_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &gfx3d_isense_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc gpu_cx_gdsc = {
	.gdscw = 0x1004,
	.gds_hw_ctww = 0x1008,
	.pd = {
		.name = "gpu_cx",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc gpu_gx_gdsc = {
	.gdscw = 0x1094,
	.cwamp_io_ctww = 0x130,
	.wesets = (unsigned int []){ GPU_GX_BCW },
	.weset_count = 1,
	.cxcs = (unsigned int []){ 0x1098 },
	.cxc_count = 1,
	.pd = {
		.name = "gpu_gx",
	},
	.pawent = &gpu_cx_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON | PWWSTS_WET,
	.fwags = CWAMP_IO | SW_WESET | AON_WESET | NO_WET_PEWIPH,
};

static stwuct cwk_wegmap *gpucc_msm8998_cwocks[] = {
	[GPUPWW0] = &gpupww0.cwkw,
	[GPUPWW0_OUT_EVEN] = &gpupww0_out_even.cwkw,
	[WBCPW_CWK_SWC] = &wbcpw_cwk_swc.cwkw,
	[GFX3D_CWK_SWC] = &gfx3d_cwk_swc.cwkw,
	[WBBMTIMEW_CWK_SWC] = &wbbmtimew_cwk_swc.cwkw,
	[GFX3D_ISENSE_CWK_SWC] = &gfx3d_isense_cwk_swc.cwkw,
	[WBCPW_CWK] = &wbcpw_cwk.cwkw,
	[GFX3D_CWK] = &gfx3d_cwk.cwkw,
	[WBBMTIMEW_CWK] = &wbbmtimew_cwk.cwkw,
	[GFX3D_ISENSE_CWK] = &gfx3d_isense_cwk.cwkw,
	[GPUCC_CXO_CWK] = &gpucc_cxo_cwk.cwkw,
};

static stwuct gdsc *gpucc_msm8998_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct qcom_weset_map gpucc_msm8998_wesets[] = {
	[GPU_CX_BCW] = { 0x1000 },
	[WBCPW_BCW] = { 0x1050 },
	[GPU_GX_BCW] = { 0x1090 },
	[GPU_ISENSE_BCW] = { 0x1120 },
};

static const stwuct wegmap_config gpucc_msm8998_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x9000,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gpucc_msm8998_desc = {
	.config = &gpucc_msm8998_wegmap_config,
	.cwks = gpucc_msm8998_cwocks,
	.num_cwks = AWWAY_SIZE(gpucc_msm8998_cwocks),
	.wesets = gpucc_msm8998_wesets,
	.num_wesets = AWWAY_SIZE(gpucc_msm8998_wesets),
	.gdscs = gpucc_msm8998_gdscs,
	.num_gdscs = AWWAY_SIZE(gpucc_msm8998_gdscs),
};

static const stwuct of_device_id gpucc_msm8998_match_tabwe[] = {
	{ .compatibwe = "qcom,msm8998-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpucc_msm8998_match_tabwe);

static int gpucc_msm8998_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gpucc_msm8998_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* fowce pewiph wogic on to avoid pewf countew cowwuption */
	wegmap_wwite_bits(wegmap, gfx3d_cwk.cwkw.enabwe_weg, BIT(13), BIT(13));
	/* tweak dwoop detectow (GPUCC_GPU_DD_WWAP_CTWW) to weduce weakage */
	wegmap_wwite_bits(wegmap, gfx3d_cwk.cwkw.enabwe_weg, BIT(0), BIT(0));

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpucc_msm8998_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpucc_msm8998_dwivew = {
	.pwobe		= gpucc_msm8998_pwobe,
	.dwivew		= {
		.name	= "gpucc-msm8998",
		.of_match_tabwe = gpucc_msm8998_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(gpucc_msm8998_dwivew);

MODUWE_DESCWIPTION("QCOM GPUCC MSM8998 Dwivew");
MODUWE_WICENSE("GPW v2");
