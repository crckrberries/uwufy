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

#incwude <dt-bindings/cwock/qcom,wcc-msm8960.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"

static stwuct cwk_pawent_data pxo_pawent_data = {
	.fw_name = "pxo", .name = "pxo_boawd",
};

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
		.pawent_data = &pxo_pawent_data,
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

enum {
	P_PXO,
	P_PWW4,
};

static const stwuct pawent_map wcc_pxo_pww4_map[] = {
	{ P_PXO, 0 },
	{ P_PWW4, 2 }
};

static stwuct cwk_pawent_data wcc_pxo_pww4[] = {
	{ .fw_name = "pxo", .name = "pxo_boawd" },
	{ .fw_name = "pww4_vote", .name = "pww4_vote" },
};

static stwuct fweq_tbw cwk_tbw_aif_osw_492[] = {
	{   512000, P_PWW4, 4, 1, 240 },
	{   768000, P_PWW4, 4, 1, 160 },
	{  1024000, P_PWW4, 4, 1, 120 },
	{  1536000, P_PWW4, 4, 1,  80 },
	{  2048000, P_PWW4, 4, 1,  60 },
	{  3072000, P_PWW4, 4, 1,  40 },
	{  4096000, P_PWW4, 4, 1,  30 },
	{  6144000, P_PWW4, 4, 1,  20 },
	{  8192000, P_PWW4, 4, 1,  15 },
	{ 12288000, P_PWW4, 4, 1,  10 },
	{ 24576000, P_PWW4, 4, 1,   5 },
	{ 27000000, P_PXO,  1, 0,   0 },
	{ }
};

static stwuct fweq_tbw cwk_tbw_aif_osw_393[] = {
	{   512000, P_PWW4, 4, 1, 192 },
	{   768000, P_PWW4, 4, 1, 128 },
	{  1024000, P_PWW4, 4, 1,  96 },
	{  1536000, P_PWW4, 4, 1,  64 },
	{  2048000, P_PWW4, 4, 1,  48 },
	{  3072000, P_PWW4, 4, 1,  32 },
	{  4096000, P_PWW4, 4, 1,  24 },
	{  6144000, P_PWW4, 4, 1,  16 },
	{  8192000, P_PWW4, 4, 1,  12 },
	{ 12288000, P_PWW4, 4, 1,   8 },
	{ 24576000, P_PWW4, 4, 1,   4 },
	{ 27000000, P_PXO,  1, 0,   0 },
	{ }
};

#define CWK_AIF_OSW_SWC(pwefix, _ns, _md)			\
static stwuct cwk_wcg pwefix##_osw_swc = {			\
	.ns_weg = _ns,						\
	.md_weg = _md,						\
	.mn = {							\
		.mnctw_en_bit = 8,				\
		.mnctw_weset_bit = 7,				\
		.mnctw_mode_shift = 5,				\
		.n_vaw_shift = 24,				\
		.m_vaw_shift = 8,				\
		.width = 8,					\
	},							\
	.p = {							\
		.pwe_div_shift = 3,				\
		.pwe_div_width = 2,				\
	},							\
	.s = {							\
		.swc_sew_shift = 0,				\
		.pawent_map = wcc_pxo_pww4_map,			\
	},							\
	.fweq_tbw = cwk_tbw_aif_osw_393,			\
	.cwkw = {						\
		.enabwe_weg = _ns,				\
		.enabwe_mask = BIT(9),				\
		.hw.init = &(stwuct cwk_init_data){		\
			.name = #pwefix "_osw_swc",		\
			.pawent_data = wcc_pxo_pww4,		\
			.num_pawents = AWWAY_SIZE(wcc_pxo_pww4), \
			.ops = &cwk_wcg_ops,			\
			.fwags = CWK_SET_WATE_GATE,		\
		},						\
	},							\
};								\

#define CWK_AIF_OSW_CWK(pwefix, _ns, hw, en_bit)		\
static stwuct cwk_bwanch pwefix##_osw_cwk = {			\
	.hawt_weg = hw,						\
	.hawt_bit = 1,						\
	.hawt_check = BWANCH_HAWT_ENABWE,			\
	.cwkw = {						\
		.enabwe_weg = _ns,				\
		.enabwe_mask = BIT(en_bit),			\
		.hw.init = &(stwuct cwk_init_data){		\
			.name = #pwefix "_osw_cwk",		\
			.pawent_hws = (const stwuct cwk_hw*[]){	\
				&pwefix##_osw_swc.cwkw.hw,	\
			},					\
			.num_pawents = 1,			\
			.ops = &cwk_bwanch_ops,			\
			.fwags = CWK_SET_WATE_PAWENT,		\
		},						\
	},							\
};								\

#define CWK_AIF_OSW_DIV_CWK(pwefix, _ns, _width)		\
static stwuct cwk_wegmap_div pwefix##_div_cwk = {		\
	.weg = _ns,						\
	.shift = 10,						\
	.width = _width,					\
	.cwkw = {						\
		.hw.init = &(stwuct cwk_init_data){		\
			.name = #pwefix "_div_cwk",		\
			.pawent_hws = (const stwuct cwk_hw*[]){	\
				&pwefix##_osw_swc.cwkw.hw,	\
			},					\
			.num_pawents = 1,			\
			.ops = &cwk_wegmap_div_ops,		\
		},						\
	},							\
};								\

#define CWK_AIF_OSW_BIT_DIV_CWK(pwefix, _ns, hw, en_bit)	\
static stwuct cwk_bwanch pwefix##_bit_div_cwk = {		\
	.hawt_weg = hw,						\
	.hawt_bit = 0,						\
	.hawt_check = BWANCH_HAWT_ENABWE,			\
	.cwkw = {						\
		.enabwe_weg = _ns,				\
		.enabwe_mask = BIT(en_bit),			\
		.hw.init = &(stwuct cwk_init_data){		\
			.name = #pwefix "_bit_div_cwk",		\
			.pawent_hws = (const stwuct cwk_hw*[]){	\
				&pwefix##_div_cwk.cwkw.hw,	\
			},					\
			.num_pawents = 1,			\
			.ops = &cwk_bwanch_ops,			\
			.fwags = CWK_SET_WATE_PAWENT,		\
		},						\
	},							\
};								\

#define CWK_AIF_OSW_BIT_CWK(pwefix, _ns, _shift)		\
static stwuct cwk_wegmap_mux pwefix##_bit_cwk = {		\
	.weg = _ns,						\
	.shift = _shift,					\
	.width = 1,						\
	.cwkw = {						\
		.hw.init = &(stwuct cwk_init_data){		\
			.name = #pwefix "_bit_cwk",		\
			.pawent_data = (const stwuct cwk_pawent_data[]){ \
				{ .hw = &pwefix##_bit_div_cwk.cwkw.hw, }, \
				{ .fw_name = #pwefix "_codec_cwk", \
				  .name = #pwefix "_codec_cwk", }, \
			},					\
			.num_pawents = 2,			\
			.ops = &cwk_wegmap_mux_cwosest_ops,	\
			.fwags = CWK_SET_WATE_PAWENT,		\
		},						\
	},							\
};

CWK_AIF_OSW_SWC(mi2s, 0x48, 0x4c)
CWK_AIF_OSW_CWK(mi2s, 0x48, 0x50, 17)
CWK_AIF_OSW_DIV_CWK(mi2s, 0x48, 4)
CWK_AIF_OSW_BIT_DIV_CWK(mi2s, 0x48, 0x50, 15)
CWK_AIF_OSW_BIT_CWK(mi2s, 0x48, 14)

#define CWK_AIF_OSW_DIV(pwefix, _ns, _md, hw)			\
	CWK_AIF_OSW_SWC(pwefix, _ns, _md)			\
	CWK_AIF_OSW_CWK(pwefix, _ns, hw, 21)			\
	CWK_AIF_OSW_DIV_CWK(pwefix, _ns, 8)			\
	CWK_AIF_OSW_BIT_DIV_CWK(pwefix, _ns, hw, 19)		\
	CWK_AIF_OSW_BIT_CWK(pwefix, _ns, 18)

CWK_AIF_OSW_DIV(codec_i2s_mic, 0x60, 0x64, 0x68);
CWK_AIF_OSW_DIV(spawe_i2s_mic, 0x78, 0x7c, 0x80);
CWK_AIF_OSW_DIV(codec_i2s_spkw, 0x6c, 0x70, 0x74);
CWK_AIF_OSW_DIV(spawe_i2s_spkw, 0x84, 0x88, 0x8c);

static stwuct fweq_tbw cwk_tbw_pcm_492[] = {
	{   256000, P_PWW4, 4, 1, 480 },
	{   512000, P_PWW4, 4, 1, 240 },
	{   768000, P_PWW4, 4, 1, 160 },
	{  1024000, P_PWW4, 4, 1, 120 },
	{  1536000, P_PWW4, 4, 1,  80 },
	{  2048000, P_PWW4, 4, 1,  60 },
	{  3072000, P_PWW4, 4, 1,  40 },
	{  4096000, P_PWW4, 4, 1,  30 },
	{  6144000, P_PWW4, 4, 1,  20 },
	{  8192000, P_PWW4, 4, 1,  15 },
	{ 12288000, P_PWW4, 4, 1,  10 },
	{ 24576000, P_PWW4, 4, 1,   5 },
	{ 27000000, P_PXO,  1, 0,   0 },
	{ }
};

static stwuct fweq_tbw cwk_tbw_pcm_393[] = {
	{   256000, P_PWW4, 4, 1, 384 },
	{   512000, P_PWW4, 4, 1, 192 },
	{   768000, P_PWW4, 4, 1, 128 },
	{  1024000, P_PWW4, 4, 1,  96 },
	{  1536000, P_PWW4, 4, 1,  64 },
	{  2048000, P_PWW4, 4, 1,  48 },
	{  3072000, P_PWW4, 4, 1,  32 },
	{  4096000, P_PWW4, 4, 1,  24 },
	{  6144000, P_PWW4, 4, 1,  16 },
	{  8192000, P_PWW4, 4, 1,  12 },
	{ 12288000, P_PWW4, 4, 1,   8 },
	{ 24576000, P_PWW4, 4, 1,   4 },
	{ 27000000, P_PXO,  1, 0,   0 },
	{ }
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
	.fweq_tbw = cwk_tbw_pcm_393,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcm_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wegmap_mux pcm_cwk = {
	.weg = 0x54,
	.shift = 10,
	.width = 1,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcm_cwk",
			.pawent_data = (const stwuct cwk_pawent_data[]){
				{ .hw = &pcm_cwk_out.cwkw.hw },
				{ .fw_name = "pcm_codec_cwk", .name = "pcm_codec_cwk" },
			},
			.num_pawents = 2,
			.ops = &cwk_wegmap_mux_cwosest_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg swimbus_swc = {
	.ns_weg = 0xcc,
	.md_weg = 0xd0,
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
	.fweq_tbw = cwk_tbw_aif_osw_393,
	.cwkw = {
		.enabwe_weg = 0xcc,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "swimbus_swc",
			.pawent_data = wcc_pxo_pww4,
			.num_pawents = AWWAY_SIZE(wcc_pxo_pww4),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch audio_swimbus_cwk = {
	.hawt_weg = 0xd4,
	.hawt_bit = 0,
	.hawt_check = BWANCH_HAWT_ENABWE,
	.cwkw = {
		.enabwe_weg = 0xcc,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "audio_swimbus_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&swimbus_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch sps_swimbus_cwk = {
	.hawt_weg = 0xd4,
	.hawt_bit = 1,
	.hawt_check = BWANCH_HAWT_ENABWE,
	.cwkw = {
		.enabwe_weg = 0xcc,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sps_swimbus_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&swimbus_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wegmap *wcc_msm8960_cwks[] = {
	[PWW4] = &pww4.cwkw,
	[MI2S_OSW_SWC] = &mi2s_osw_swc.cwkw,
	[MI2S_OSW_CWK] = &mi2s_osw_cwk.cwkw,
	[MI2S_DIV_CWK] = &mi2s_div_cwk.cwkw,
	[MI2S_BIT_DIV_CWK] = &mi2s_bit_div_cwk.cwkw,
	[MI2S_BIT_CWK] = &mi2s_bit_cwk.cwkw,
	[PCM_SWC] = &pcm_swc.cwkw,
	[PCM_CWK_OUT] = &pcm_cwk_out.cwkw,
	[PCM_CWK] = &pcm_cwk.cwkw,
	[SWIMBUS_SWC] = &swimbus_swc.cwkw,
	[AUDIO_SWIMBUS_CWK] = &audio_swimbus_cwk.cwkw,
	[SPS_SWIMBUS_CWK] = &sps_swimbus_cwk.cwkw,
	[CODEC_I2S_MIC_OSW_SWC] = &codec_i2s_mic_osw_swc.cwkw,
	[CODEC_I2S_MIC_OSW_CWK] = &codec_i2s_mic_osw_cwk.cwkw,
	[CODEC_I2S_MIC_DIV_CWK] = &codec_i2s_mic_div_cwk.cwkw,
	[CODEC_I2S_MIC_BIT_DIV_CWK] = &codec_i2s_mic_bit_div_cwk.cwkw,
	[CODEC_I2S_MIC_BIT_CWK] = &codec_i2s_mic_bit_cwk.cwkw,
	[SPAWE_I2S_MIC_OSW_SWC] = &spawe_i2s_mic_osw_swc.cwkw,
	[SPAWE_I2S_MIC_OSW_CWK] = &spawe_i2s_mic_osw_cwk.cwkw,
	[SPAWE_I2S_MIC_DIV_CWK] = &spawe_i2s_mic_div_cwk.cwkw,
	[SPAWE_I2S_MIC_BIT_DIV_CWK] = &spawe_i2s_mic_bit_div_cwk.cwkw,
	[SPAWE_I2S_MIC_BIT_CWK] = &spawe_i2s_mic_bit_cwk.cwkw,
	[CODEC_I2S_SPKW_OSW_SWC] = &codec_i2s_spkw_osw_swc.cwkw,
	[CODEC_I2S_SPKW_OSW_CWK] = &codec_i2s_spkw_osw_cwk.cwkw,
	[CODEC_I2S_SPKW_DIV_CWK] = &codec_i2s_spkw_div_cwk.cwkw,
	[CODEC_I2S_SPKW_BIT_DIV_CWK] = &codec_i2s_spkw_bit_div_cwk.cwkw,
	[CODEC_I2S_SPKW_BIT_CWK] = &codec_i2s_spkw_bit_cwk.cwkw,
	[SPAWE_I2S_SPKW_OSW_SWC] = &spawe_i2s_spkw_osw_swc.cwkw,
	[SPAWE_I2S_SPKW_OSW_CWK] = &spawe_i2s_spkw_osw_cwk.cwkw,
	[SPAWE_I2S_SPKW_DIV_CWK] = &spawe_i2s_spkw_div_cwk.cwkw,
	[SPAWE_I2S_SPKW_BIT_DIV_CWK] = &spawe_i2s_spkw_bit_div_cwk.cwkw,
	[SPAWE_I2S_SPKW_BIT_CWK] = &spawe_i2s_spkw_bit_cwk.cwkw,
};

static const stwuct wegmap_config wcc_msm8960_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0xfc,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc wcc_msm8960_desc = {
	.config = &wcc_msm8960_wegmap_config,
	.cwks = wcc_msm8960_cwks,
	.num_cwks = AWWAY_SIZE(wcc_msm8960_cwks),
};

static const stwuct of_device_id wcc_msm8960_match_tabwe[] = {
	{ .compatibwe = "qcom,wcc-msm8960" },
	{ .compatibwe = "qcom,wcc-apq8064" },
	{ .compatibwe = "qcom,wcc-mdm9615" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcc_msm8960_match_tabwe);

static int wcc_msm8960_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 vaw;
	stwuct wegmap *wegmap;

	/* patch fow the cxo <-> pxo diffewence */
	if (of_device_is_compatibwe(pdev->dev.of_node, "qcom,wcc-mdm9615")) {
		pxo_pawent_data.fw_name = "cxo";
		pxo_pawent_data.name = "cxo_boawd";
		wcc_pxo_pww4[0].fw_name = "cxo";
		wcc_pxo_pww4[0].name = "cxo_boawd";
	}

	wegmap = qcom_cc_map(pdev, &wcc_msm8960_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Use the cowwect fwequency pwan depending on speed of PWW4 */
	wegmap_wead(wegmap, 0x4, &vaw);
	if (vaw == 0x12) {
		swimbus_swc.fweq_tbw = cwk_tbw_aif_osw_492;
		mi2s_osw_swc.fweq_tbw = cwk_tbw_aif_osw_492;
		codec_i2s_mic_osw_swc.fweq_tbw = cwk_tbw_aif_osw_492;
		spawe_i2s_mic_osw_swc.fweq_tbw = cwk_tbw_aif_osw_492;
		codec_i2s_spkw_osw_swc.fweq_tbw = cwk_tbw_aif_osw_492;
		spawe_i2s_spkw_osw_swc.fweq_tbw = cwk_tbw_aif_osw_492;
		pcm_swc.fweq_tbw = cwk_tbw_pcm_492;
	}
	/* Enabwe PWW4 souwce on the WPASS Pwimawy PWW Mux */
	wegmap_wwite(wegmap, 0xc4, 0x1);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &wcc_msm8960_desc, wegmap);
}

static stwuct pwatfowm_dwivew wcc_msm8960_dwivew = {
	.pwobe		= wcc_msm8960_pwobe,
	.dwivew		= {
		.name	= "wcc-msm8960",
		.of_match_tabwe = wcc_msm8960_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(wcc_msm8960_dwivew);

MODUWE_DESCWIPTION("QCOM WCC MSM8960 Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wcc-msm8960");
