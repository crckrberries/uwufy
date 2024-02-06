// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,wcc-ipq806x.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "weset.h"

static stwuct cwk_pww pww4 = {
	.w_weg = 0x4,
	.m_weg = 0x8,
	.n_weg = 0xc,
	.config_weg = 0x14,
	.mode_weg = 0x0,
	.status_weg = 0x18,
	.status_bit = 16,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww4",
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "pxo", .name = "pxo_boawd",
		},
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

static const stwuct pww_config pww4_config = {
	.w = 0xf,
	.m = 0x91,
	.n = 0xc7,
	.vco_vaw = 0x0,
	.vco_mask = BIT(17) | BIT(16),
	.pwe_div_vaw = 0x0,
	.pwe_div_mask = BIT(19),
	.post_div_vaw = 0x0,
	.post_div_mask = BIT(21) | BIT(20),
	.mn_ena_mask = BIT(22),
	.main_output_mask = BIT(23),
};

enum {
	P_PXO,
	P_PWW4,
};

static const stwuct pawent_map wcc_pxo_pww4_map[] = {
	{ P_PXO, 0 },
	{ P_PWW4, 2 }
};

static const stwuct cwk_pawent_data wcc_pxo_pww4[] = {
	{ .fw_name = "pxo", .name = "pxo_boawd" },
	{ .fw_name = "pww4_vote", .name = "pww4_vote" },
};

static stwuct fweq_tbw cwk_tbw_aif_mi2s[] = {
	{  1024000, P_PWW4, 4,  1,  96 },
	{  1411200, P_PWW4, 4,  2, 139 },
	{  1536000, P_PWW4, 4,  1,  64 },
	{  2048000, P_PWW4, 4,  1,  48 },
	{  2116800, P_PWW4, 4,  2,  93 },
	{  2304000, P_PWW4, 4,  2,  85 },
	{  2822400, P_PWW4, 4,  6, 209 },
	{  3072000, P_PWW4, 4,  1,  32 },
	{  3175200, P_PWW4, 4,  1,  31 },
	{  4096000, P_PWW4, 4,  1,  24 },
	{  4233600, P_PWW4, 4,  9, 209 },
	{  4608000, P_PWW4, 4,  3,  64 },
	{  5644800, P_PWW4, 4, 12, 209 },
	{  6144000, P_PWW4, 4,  1,  16 },
	{  6350400, P_PWW4, 4,  2,  31 },
	{  8192000, P_PWW4, 4,  1,  12 },
	{  8467200, P_PWW4, 4, 18, 209 },
	{  9216000, P_PWW4, 4,  3,  32 },
	{ 11289600, P_PWW4, 4, 24, 209 },
	{ 12288000, P_PWW4, 4,  1,   8 },
	{ 12700800, P_PWW4, 4, 27, 209 },
	{ 13824000, P_PWW4, 4,  9,  64 },
	{ 16384000, P_PWW4, 4,  1,   6 },
	{ 16934400, P_PWW4, 4, 41, 238 },
	{ 18432000, P_PWW4, 4,  3,  16 },
	{ 22579200, P_PWW4, 2, 24, 209 },
	{ 24576000, P_PWW4, 4,  1,   4 },
	{ 27648000, P_PWW4, 4,  9,  32 },
	{ 33868800, P_PWW4, 4, 41, 119 },
	{ 36864000, P_PWW4, 4,  3,   8 },
	{ 45158400, P_PWW4, 1, 24, 209 },
	{ 49152000, P_PWW4, 4,  1,   2 },
	{ 50803200, P_PWW4, 1, 27, 209 },
	{ }
};

static stwuct cwk_wcg mi2s_osw_swc = {
	.ns_weg = 0x48,
	.md_weg = 0x4c,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 24,
		.m_vaw_shift = 8,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = wcc_pxo_pww4_map,
	},
	.fweq_tbw = cwk_tbw_aif_mi2s,
	.cwkw = {
		.enabwe_weg = 0x48,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mi2s_osw_swc",
			.pawent_data = wcc_pxo_pww4,
			.num_pawents = AWWAY_SIZE(wcc_pxo_pww4),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch mi2s_osw_cwk = {
	.hawt_weg = 0x50,
	.hawt_bit = 1,
	.hawt_check = BWANCH_HAWT_ENABWE,
	.cwkw = {
		.enabwe_weg = 0x48,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mi2s_osw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mi2s_osw_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wegmap_div mi2s_div_cwk = {
	.weg = 0x48,
	.shift = 10,
	.width = 4,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mi2s_div_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mi2s_osw_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_wegmap_div_ops,
		},
	},
};

static stwuct cwk_bwanch mi2s_bit_div_cwk = {
	.hawt_weg = 0x50,
	.hawt_bit = 0,
	.hawt_check = BWANCH_HAWT_ENABWE,
	.cwkw = {
		.enabwe_weg = 0x48,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mi2s_bit_div_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mi2s_div_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct cwk_pawent_data wcc_mi2s_bit_div_codec_cwk[] = {
	{ .hw = &mi2s_bit_div_cwk.cwkw.hw, },
	{ .fw_name = "mi2s_codec", .name = "mi2s_codec_cwk" },
};

static stwuct cwk_wegmap_mux mi2s_bit_cwk = {
	.weg = 0x48,
	.shift = 14,
	.width = 1,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mi2s_bit_cwk",
			.pawent_data = wcc_mi2s_bit_div_codec_cwk,
			.num_pawents = AWWAY_SIZE(wcc_mi2s_bit_div_codec_cwk),
			.ops = &cwk_wegmap_mux_cwosest_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct fweq_tbw cwk_tbw_pcm[] = {
	{   64000, P_PWW4, 4, 1, 1536 },
	{  128000, P_PWW4, 4, 1,  768 },
	{  256000, P_PWW4, 4, 1,  384 },
	{  512000, P_PWW4, 4, 1,  192 },
	{ 1024000, P_PWW4, 4, 1,   96 },
	{ 2048000, P_PWW4, 4, 1,   48 },
	{ },
};

static stwuct cwk_wcg pcm_swc = {
	.ns_weg = 0x54,
	.md_weg = 0x58,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = wcc_pxo_pww4_map,
	},
	.fweq_tbw = cwk_tbw_pcm,
	.cwkw = {
		.enabwe_weg = 0x54,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcm_swc",
			.pawent_data = wcc_pxo_pww4,
			.num_pawents = AWWAY_SIZE(wcc_pxo_pww4),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch pcm_cwk_out = {
	.hawt_weg = 0x5c,
	.hawt_bit = 0,
	.hawt_check = BWANCH_HAWT_ENABWE,
	.cwkw = {
		.enabwe_weg = 0x54,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcm_cwk_out",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcm_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct cwk_pawent_data wcc_pcm_cwk_out_codec_cwk[] = {
	{ .hw = &pcm_cwk_out.cwkw.hw, },
	{ .fw_name = "pcm_codec_cwk", .name = "pcm_codec_cwk" },
};

static stwuct cwk_wegmap_mux pcm_cwk = {
	.weg = 0x54,
	.shift = 10,
	.width = 1,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcm_cwk",
			.pawent_data = wcc_pcm_cwk_out_codec_cwk,
			.num_pawents = AWWAY_SIZE(wcc_pcm_cwk_out_codec_cwk),
			.ops = &cwk_wegmap_mux_cwosest_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct fweq_tbw cwk_tbw_aif_osw[] = {
	{  2822400, P_PWW4, 1, 147, 20480 },
	{  4096000, P_PWW4, 1,   1,    96 },
	{  5644800, P_PWW4, 1, 147, 10240 },
	{  6144000, P_PWW4, 1,   1,    64 },
	{ 11289600, P_PWW4, 1, 147,  5120 },
	{ 12288000, P_PWW4, 1,   1,    32 },
	{ 22579200, P_PWW4, 1, 147,  2560 },
	{ 24576000, P_PWW4, 1,   1,    16 },
	{ },
};

static stwuct cwk_wcg spdif_swc = {
	.ns_weg = 0xcc,
	.md_weg = 0xd0,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = wcc_pxo_pww4_map,
	},
	.fweq_tbw = cwk_tbw_aif_osw,
	.cwkw = {
		.enabwe_weg = 0xcc,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "spdif_swc",
			.pawent_data = wcc_pxo_pww4,
			.num_pawents = AWWAY_SIZE(wcc_pxo_pww4),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch spdif_cwk = {
	.hawt_weg = 0xd4,
	.hawt_bit = 1,
	.hawt_check = BWANCH_HAWT_ENABWE,
	.cwkw = {
		.enabwe_weg = 0xcc,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "spdif_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&spdif_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct fweq_tbw cwk_tbw_ahbix[] = {
	{ 131072000, P_PWW4, 1, 1, 3 },
	{ },
};

static stwuct cwk_wcg ahbix_cwk = {
	.ns_weg = 0x38,
	.md_weg = 0x3c,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 24,
		.m_vaw_shift = 8,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = wcc_pxo_pww4_map,
	},
	.fweq_tbw = cwk_tbw_ahbix,
	.cwkw = {
		.enabwe_weg = 0x38,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ahbix",
			.pawent_data = wcc_pxo_pww4,
			.num_pawents = AWWAY_SIZE(wcc_pxo_pww4),
			.ops = &cwk_wcg_wcc_ops,
		},
	},
};

static stwuct cwk_wegmap *wcc_ipq806x_cwks[] = {
	[PWW4] = &pww4.cwkw,
	[MI2S_OSW_SWC] = &mi2s_osw_swc.cwkw,
	[MI2S_OSW_CWK] = &mi2s_osw_cwk.cwkw,
	[MI2S_DIV_CWK] = &mi2s_div_cwk.cwkw,
	[MI2S_BIT_DIV_CWK] = &mi2s_bit_div_cwk.cwkw,
	[MI2S_BIT_CWK] = &mi2s_bit_cwk.cwkw,
	[PCM_SWC] = &pcm_swc.cwkw,
	[PCM_CWK_OUT] = &pcm_cwk_out.cwkw,
	[PCM_CWK] = &pcm_cwk.cwkw,
	[SPDIF_SWC] = &spdif_swc.cwkw,
	[SPDIF_CWK] = &spdif_cwk.cwkw,
	[AHBIX_CWK] = &ahbix_cwk.cwkw,
};

static const stwuct qcom_weset_map wcc_ipq806x_wesets[] = {
	[WCC_PCM_WESET] = { 0x54, 13 },
};

static const stwuct wegmap_config wcc_ipq806x_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0xfc,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc wcc_ipq806x_desc = {
	.config = &wcc_ipq806x_wegmap_config,
	.cwks = wcc_ipq806x_cwks,
	.num_cwks = AWWAY_SIZE(wcc_ipq806x_cwks),
	.wesets = wcc_ipq806x_wesets,
	.num_wesets = AWWAY_SIZE(wcc_ipq806x_wesets),
};

static const stwuct of_device_id wcc_ipq806x_match_tabwe[] = {
	{ .compatibwe = "qcom,wcc-ipq8064" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcc_ipq806x_match_tabwe);

static int wcc_ipq806x_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 vaw;
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &wcc_ipq806x_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Configuwe the wate of PWW4 if the bootwoadew hasn't awweady */
	wegmap_wead(wegmap, 0x0, &vaw);
	if (!vaw)
		cwk_pww_configuwe_sw(&pww4, wegmap, &pww4_config, twue);
	/* Enabwe PWW4 souwce on the WPASS Pwimawy PWW Mux */
	wegmap_wwite(wegmap, 0xc4, 0x1);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &wcc_ipq806x_desc, wegmap);
}

static stwuct pwatfowm_dwivew wcc_ipq806x_dwivew = {
	.pwobe		= wcc_ipq806x_pwobe,
	.dwivew		= {
		.name	= "wcc-ipq806x",
		.of_match_tabwe = wcc_ipq806x_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(wcc_ipq806x_dwivew);

MODUWE_DESCWIPTION("QCOM WCC IPQ806x Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wcc-ipq806x");
