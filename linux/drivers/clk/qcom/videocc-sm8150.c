// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,videocc-sm8150.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_VIDEO_PWW0_OUT_MAIN,
};

static stwuct pww_vco twion_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct awpha_pww_config video_pww0_config = {
	.w = 0x14,
	.awpha = 0xD555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002267,
	.config_ctw_hi1_vaw = 0x00000024,
	.test_ctw_hi1_vaw = 0x00000020,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x000000D0,
};

static stwuct cwk_awpha_pww video_pww0 = {
	.offset = 0x42c,
	.vco_tabwe = twion_vco,
	.num_vco = AWWAY_SIZE(twion_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_TWION],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_twion_ops,
		},
	},
};

static const stwuct pawent_map video_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_VIDEO_PWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &video_pww0.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_video_cc_iwis_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(240000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(338000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(365000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(444000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(533000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_iwis_cwk_swc = {
	.cmd_wcgw = 0x7f0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_0,
	.fweq_tbw = ftbw_video_cc_iwis_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cc_iwis_cwk_swc",
		.pawent_data = video_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_bwanch video_cc_iwis_ahb_cwk = {
	.hawt_weg = 0x8f4,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x8f4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_iwis_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs0_cowe_cwk = {
	.hawt_weg = 0x890,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x890,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs0_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs1_cowe_cwk = {
	.hawt_weg = 0x8d0,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x8d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs1_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvsc_cowe_cwk = {
	.hawt_weg = 0x850,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x850,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvsc_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc venus_gdsc = {
	.gdscw = 0x814,
	.pd = {
		.name = "venus_gdsc",
	},
	.fwags = 0,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc vcodec0_gdsc = {
	.gdscw = 0x874,
	.pd = {
		.name = "vcodec0_gdsc",
	},
	.fwags = HW_CTWW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc vcodec1_gdsc = {
	.gdscw = 0x8b4,
	.pd = {
		.name = "vcodec1_gdsc",
	},
	.fwags = HW_CTWW,
	.pwwsts = PWWSTS_OFF_ON,
};
static stwuct cwk_wegmap *video_cc_sm8150_cwocks[] = {
	[VIDEO_CC_IWIS_AHB_CWK] = &video_cc_iwis_ahb_cwk.cwkw,
	[VIDEO_CC_IWIS_CWK_SWC] = &video_cc_iwis_cwk_swc.cwkw,
	[VIDEO_CC_MVS0_COWE_CWK] = &video_cc_mvs0_cowe_cwk.cwkw,
	[VIDEO_CC_MVS1_COWE_CWK] = &video_cc_mvs1_cowe_cwk.cwkw,
	[VIDEO_CC_MVSC_COWE_CWK] = &video_cc_mvsc_cowe_cwk.cwkw,
	[VIDEO_CC_PWW0] = &video_pww0.cwkw,
};

static stwuct gdsc *video_cc_sm8150_gdscs[] = {
	[VENUS_GDSC] = &venus_gdsc,
	[VCODEC0_GDSC] = &vcodec0_gdsc,
	[VCODEC1_GDSC] = &vcodec1_gdsc,
};

static const stwuct wegmap_config video_cc_sm8150_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0xb94,
	.fast_io	= twue,
};

static const stwuct qcom_weset_map video_cc_sm8150_wesets[] = {
	[VIDEO_CC_MVSC_COWE_CWK_BCW] = { 0x850, 2 },
	[VIDEO_CC_INTEWFACE_BCW] = { 0x8f0 },
	[VIDEO_CC_MVS0_BCW] = { 0x870 },
	[VIDEO_CC_MVS1_BCW] = { 0x8b0 },
	[VIDEO_CC_MVSC_BCW] = { 0x810 },
};

static const stwuct qcom_cc_desc video_cc_sm8150_desc = {
	.config = &video_cc_sm8150_wegmap_config,
	.cwks = video_cc_sm8150_cwocks,
	.num_cwks = AWWAY_SIZE(video_cc_sm8150_cwocks),
	.wesets = video_cc_sm8150_wesets,
	.num_wesets = AWWAY_SIZE(video_cc_sm8150_wesets),
	.gdscs = video_cc_sm8150_gdscs,
	.num_gdscs = AWWAY_SIZE(video_cc_sm8150_gdscs),
};

static const stwuct of_device_id video_cc_sm8150_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8150-videocc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, video_cc_sm8150_match_tabwe);

static int video_cc_sm8150_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wegmap = qcom_cc_map(pdev, &video_cc_sm8150_desc);
	if (IS_EWW(wegmap)) {
		pm_wuntime_put_sync(&pdev->dev);
		wetuwn PTW_EWW(wegmap);
	}

	cwk_twion_pww_configuwe(&video_pww0, wegmap, &video_pww0_config);

	/* Keep VIDEO_CC_XO_CWK AWWAYS-ON */
	wegmap_update_bits(wegmap, 0x984, 0x1, 0x1);

	wet = qcom_cc_weawwy_pwobe(pdev, &video_cc_sm8150_desc, wegmap);

	pm_wuntime_put_sync(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew video_cc_sm8150_dwivew = {
	.pwobe = video_cc_sm8150_pwobe,
	.dwivew = {
		.name	= "video_cc-sm8150",
		.of_match_tabwe = video_cc_sm8150_match_tabwe,
	},
};

static int __init video_cc_sm8150_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&video_cc_sm8150_dwivew);
}
subsys_initcaww(video_cc_sm8150_init);

static void __exit video_cc_sm8150_exit(void)
{
	pwatfowm_dwivew_unwegistew(&video_cc_sm8150_dwivew);
}
moduwe_exit(video_cc_sm8150_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QTI VIDEOCC SM8150 Dwivew");
