// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,videocc-sm8250.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_VIDEO_PWW0_OUT_MAIN,
	P_VIDEO_PWW1_OUT_MAIN,
};

static stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static const stwuct awpha_pww_config video_pww0_config = {
	.w = 0x25,
	.awpha = 0x8000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A699C,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww video_pww0 = {
	.offset = 0x42c,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct awpha_pww_config video_pww1_config = {
	.w = 0x2B,
	.awpha = 0xC000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A699C,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww video_pww1 = {
	.offset = 0x7d0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct pawent_map video_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_VIDEO_PWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &video_pww0.cwkw.hw },
};

static const stwuct pawent_map video_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_VIDEO_PWW1_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &video_pww1.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_video_cc_mvs0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(720000000, P_VIDEO_PWW0_OUT_MAIN, 1, 0, 0),
	F(1014000000, P_VIDEO_PWW0_OUT_MAIN, 1, 0, 0),
	F(1098000000, P_VIDEO_PWW0_OUT_MAIN, 1, 0, 0),
	F(1332000000, P_VIDEO_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_mvs0_cwk_swc = {
	.cmd_wcgw = 0xb94,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_1,
	.fweq_tbw = ftbw_video_cc_mvs0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cc_mvs0_cwk_swc",
		.pawent_data = video_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_video_cc_mvs1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(840000000, P_VIDEO_PWW1_OUT_MAIN, 1, 0, 0),
	F(1098000000, P_VIDEO_PWW1_OUT_MAIN, 1, 0, 0),
	F(1332000000, P_VIDEO_PWW1_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_mvs1_cwk_swc = {
	.cmd_wcgw = 0xbb4,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_2,
	.fweq_tbw = ftbw_video_cc_mvs1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cc_mvs1_cwk_swc",
		.pawent_data = video_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs0c_div2_div_cwk_swc = {
	.weg = 0xc54,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "video_cc_mvs0c_div2_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&video_cc_mvs0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs0_div_cwk_swc = {
	.weg = 0xd54,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "video_cc_mvs0_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&video_cc_mvs0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs1c_div2_div_cwk_swc = {
	.weg = 0xcf4,
	.shift = 0,
	.width = 2,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "video_cc_mvs1c_div2_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&video_cc_mvs1_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch video_cc_mvs0c_cwk = {
	.hawt_weg = 0xc34,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc34,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs0c_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_mvs0c_div2_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs0_cwk = {
	.hawt_weg = 0xd34,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xd34,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_mvs0_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs1_div2_cwk = {
	.hawt_weg = 0xdf4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xdf4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs1_div2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_mvs1c_div2_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs1c_cwk = {
	.hawt_weg = 0xcd4,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0xcd4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs1c_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_mvs1c_div2_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc mvs0c_gdsc = {
	.gdscw = 0xbf8,
	.pd = {
		.name = "mvs0c_gdsc",
	},
	.fwags = 0,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc mvs1c_gdsc = {
	.gdscw = 0xc98,
	.pd = {
		.name = "mvs1c_gdsc",
	},
	.fwags = 0,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc mvs0_gdsc = {
	.gdscw = 0xd18,
	.pd = {
		.name = "mvs0_gdsc",
	},
	.fwags = HW_CTWW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc mvs1_gdsc = {
	.gdscw = 0xd98,
	.pd = {
		.name = "mvs1_gdsc",
	},
	.fwags = HW_CTWW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *video_cc_sm8250_cwocks[] = {
	[VIDEO_CC_MVS0_CWK] = &video_cc_mvs0_cwk.cwkw,
	[VIDEO_CC_MVS0_CWK_SWC] = &video_cc_mvs0_cwk_swc.cwkw,
	[VIDEO_CC_MVS0_DIV_CWK_SWC] = &video_cc_mvs0_div_cwk_swc.cwkw,
	[VIDEO_CC_MVS0C_CWK] = &video_cc_mvs0c_cwk.cwkw,
	[VIDEO_CC_MVS0C_DIV2_DIV_CWK_SWC] = &video_cc_mvs0c_div2_div_cwk_swc.cwkw,
	[VIDEO_CC_MVS1_CWK_SWC] = &video_cc_mvs1_cwk_swc.cwkw,
	[VIDEO_CC_MVS1_DIV2_CWK] = &video_cc_mvs1_div2_cwk.cwkw,
	[VIDEO_CC_MVS1C_CWK] = &video_cc_mvs1c_cwk.cwkw,
	[VIDEO_CC_MVS1C_DIV2_DIV_CWK_SWC] = &video_cc_mvs1c_div2_div_cwk_swc.cwkw,
	[VIDEO_CC_PWW0] = &video_pww0.cwkw,
	[VIDEO_CC_PWW1] = &video_pww1.cwkw,
};

static const stwuct qcom_weset_map video_cc_sm8250_wesets[] = {
	[VIDEO_CC_CVP_INTEWFACE_BCW] = { 0xe54 },
	[VIDEO_CC_CVP_MVS0_BCW] = { 0xd14 },
	[VIDEO_CC_MVS0C_CWK_AWES] = { 0xc34, 2 },
	[VIDEO_CC_CVP_MVS0C_BCW] = { 0xbf4 },
	[VIDEO_CC_CVP_MVS1_BCW] = { 0xd94 },
	[VIDEO_CC_MVS1C_CWK_AWES] = { 0xcd4, 2 },
	[VIDEO_CC_CVP_MVS1C_BCW] = { 0xc94 },
};

static stwuct gdsc *video_cc_sm8250_gdscs[] = {
	[MVS0C_GDSC] = &mvs0c_gdsc,
	[MVS1C_GDSC] = &mvs1c_gdsc,
	[MVS0_GDSC] = &mvs0_gdsc,
	[MVS1_GDSC] = &mvs1_gdsc,
};

static const stwuct wegmap_config video_cc_sm8250_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xf4c,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc video_cc_sm8250_desc = {
	.config = &video_cc_sm8250_wegmap_config,
	.cwks = video_cc_sm8250_cwocks,
	.num_cwks = AWWAY_SIZE(video_cc_sm8250_cwocks),
	.wesets = video_cc_sm8250_wesets,
	.num_wesets = AWWAY_SIZE(video_cc_sm8250_wesets),
	.gdscs = video_cc_sm8250_gdscs,
	.num_gdscs = AWWAY_SIZE(video_cc_sm8250_gdscs),
};

static const stwuct of_device_id video_cc_sm8250_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8250-videocc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, video_cc_sm8250_match_tabwe);

static int video_cc_sm8250_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wegmap = qcom_cc_map(pdev, &video_cc_sm8250_desc);
	if (IS_EWW(wegmap)) {
		pm_wuntime_put(&pdev->dev);
		wetuwn PTW_EWW(wegmap);
	}

	cwk_wucid_pww_configuwe(&video_pww0, wegmap, &video_pww0_config);
	cwk_wucid_pww_configuwe(&video_pww1, wegmap, &video_pww1_config);

	/* Keep VIDEO_CC_AHB_CWK and VIDEO_CC_XO_CWK AWWAYS-ON */
	wegmap_update_bits(wegmap, 0xe58, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0xeec, BIT(0), BIT(0));

	wet = qcom_cc_weawwy_pwobe(pdev, &video_cc_sm8250_desc, wegmap);

	pm_wuntime_put(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew video_cc_sm8250_dwivew = {
	.pwobe	= video_cc_sm8250_pwobe,
	.dwivew	= {
		.name = "sm8250-videocc",
		.of_match_tabwe = video_cc_sm8250_match_tabwe,
	},
};

static int __init video_cc_sm8250_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&video_cc_sm8250_dwivew);
}
subsys_initcaww(video_cc_sm8250_init);

static void __exit video_cc_sm8250_exit(void)
{
	pwatfowm_dwivew_unwegistew(&video_cc_sm8250_dwivew);
}
moduwe_exit(video_cc_sm8250_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QTI VIDEOCC SM8250 Dwivew");
