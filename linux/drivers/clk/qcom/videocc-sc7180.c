// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,videocc-sc7180.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_VIDEO_PWW0_OUT_MAIN,
};

static const stwuct pww_vco fabia_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct cwk_awpha_pww video_pww0 = {
	.offset = 0x42c,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
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

static const stwuct fweq_tbw ftbw_video_cc_venus_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(150000000, P_VIDEO_PWW0_OUT_MAIN, 4, 0, 0),
	F(270000000, P_VIDEO_PWW0_OUT_MAIN, 2.5, 0, 0),
	F(340000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(434000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	F(500000000, P_VIDEO_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_venus_cwk_swc = {
	.cmd_wcgw = 0x7f0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_1,
	.fweq_tbw = ftbw_video_cc_venus_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cc_venus_cwk_swc",
		.pawent_data = video_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_bwanch video_cc_vcodec0_axi_cwk = {
	.hawt_weg = 0x9ec,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9ec,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_vcodec0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_vcodec0_cowe_cwk = {
	.hawt_weg = 0x890,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x890,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_vcodec0_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_venus_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_venus_ahb_cwk = {
	.hawt_weg = 0xa4c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa4c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_venus_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_venus_ctw_axi_cwk = {
	.hawt_weg = 0x9cc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9cc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_venus_ctw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_venus_ctw_cowe_cwk = {
	.hawt_weg = 0x850,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x850,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_venus_ctw_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_venus_cwk_swc.cwkw.hw,
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

static stwuct cwk_wegmap *video_cc_sc7180_cwocks[] = {
	[VIDEO_CC_VCODEC0_AXI_CWK] = &video_cc_vcodec0_axi_cwk.cwkw,
	[VIDEO_CC_VCODEC0_COWE_CWK] = &video_cc_vcodec0_cowe_cwk.cwkw,
	[VIDEO_CC_VENUS_AHB_CWK] = &video_cc_venus_ahb_cwk.cwkw,
	[VIDEO_CC_VENUS_CWK_SWC] = &video_cc_venus_cwk_swc.cwkw,
	[VIDEO_CC_VENUS_CTW_AXI_CWK] = &video_cc_venus_ctw_axi_cwk.cwkw,
	[VIDEO_CC_VENUS_CTW_COWE_CWK] = &video_cc_venus_ctw_cowe_cwk.cwkw,
	[VIDEO_PWW0] = &video_pww0.cwkw,
};

static stwuct gdsc *video_cc_sc7180_gdscs[] = {
	[VENUS_GDSC] = &venus_gdsc,
	[VCODEC0_GDSC] = &vcodec0_gdsc,
};

static const stwuct wegmap_config video_cc_sc7180_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xb94,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc video_cc_sc7180_desc = {
	.config = &video_cc_sc7180_wegmap_config,
	.cwks = video_cc_sc7180_cwocks,
	.num_cwks = AWWAY_SIZE(video_cc_sc7180_cwocks),
	.gdscs = video_cc_sc7180_gdscs,
	.num_gdscs = AWWAY_SIZE(video_cc_sc7180_gdscs),
};

static const stwuct of_device_id video_cc_sc7180_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7180-videocc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, video_cc_sc7180_match_tabwe);

static int video_cc_sc7180_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	stwuct awpha_pww_config video_pww0_config = {};

	wegmap = qcom_cc_map(pdev, &video_cc_sc7180_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	video_pww0_config.w = 0x1f;
	video_pww0_config.awpha = 0x4000;
	video_pww0_config.usew_ctw_vaw = 0x00000001;
	video_pww0_config.usew_ctw_hi_vaw = 0x00004805;

	cwk_fabia_pww_configuwe(&video_pww0, wegmap, &video_pww0_config);

	/* Keep VIDEO_CC_XO_CWK AWWAYS-ON */
	wegmap_update_bits(wegmap, 0x984, 0x1, 0x1);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &video_cc_sc7180_desc, wegmap);
}

static stwuct pwatfowm_dwivew video_cc_sc7180_dwivew = {
	.pwobe = video_cc_sc7180_pwobe,
	.dwivew = {
		.name = "sc7180-videocc",
		.of_match_tabwe = video_cc_sc7180_match_tabwe,
	},
};

static int __init video_cc_sc7180_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&video_cc_sc7180_dwivew);
}
subsys_initcaww(video_cc_sc7180_init);

static void __exit video_cc_sc7180_exit(void)
{
	pwatfowm_dwivew_unwegistew(&video_cc_sc7180_dwivew);
}
moduwe_exit(video_cc_sc7180_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("QTI VIDEOCC SC7180 Dwivew");
