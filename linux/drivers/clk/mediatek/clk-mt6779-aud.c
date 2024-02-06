// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Wendeww Win <wendeww.win@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt6779-cwk.h>

static const stwuct mtk_gate_wegs audio0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs audio1_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x4,
	.sta_ofs = 0x4,
};

#define GATE_AUDIO0(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww)
#define GATE_AUDIO1(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate audio_cwks[] = {
	/* AUDIO0 */
	GATE_AUDIO0(CWK_AUD_AFE, "aud_afe", "audio_sew", 2),
	GATE_AUDIO0(CWK_AUD_22M, "aud_22m", "aud_eng1_sew", 8),
	GATE_AUDIO0(CWK_AUD_24M, "aud_24m", "aud_eng2_sew", 9),
	GATE_AUDIO0(CWK_AUD_APWW2_TUNEW, "aud_apww2_tunew",
		    "aud_eng2_sew", 18),
	GATE_AUDIO0(CWK_AUD_APWW_TUNEW, "aud_apww_tunew",
		    "aud_eng1_sew", 19),
	GATE_AUDIO0(CWK_AUD_TDM, "aud_tdm", "aud_eng1_sew", 20),
	GATE_AUDIO0(CWK_AUD_ADC, "aud_adc", "audio_sew", 24),
	GATE_AUDIO0(CWK_AUD_DAC, "aud_dac", "audio_sew", 25),
	GATE_AUDIO0(CWK_AUD_DAC_PWEDIS, "aud_dac_pwedis",
		    "audio_sew", 26),
	GATE_AUDIO0(CWK_AUD_TMW, "aud_tmw", "audio_sew", 27),
	GATE_AUDIO0(CWK_AUD_NWE, "aud_nwe", "audio_sew", 28),
	/* AUDIO1 */
	GATE_AUDIO1(CWK_AUD_I2S1_BCWK_SW, "aud_i2s1_bcwk",
		    "audio_sew", 4),
	GATE_AUDIO1(CWK_AUD_I2S2_BCWK_SW, "aud_i2s2_bcwk",
		    "audio_sew", 5),
	GATE_AUDIO1(CWK_AUD_I2S3_BCWK_SW, "aud_i2s3_bcwk",
		    "audio_sew", 6),
	GATE_AUDIO1(CWK_AUD_I2S4_BCWK_SW, "aud_i2s4_bcwk",
		    "audio_sew", 7),
	GATE_AUDIO1(CWK_AUD_I2S5_BCWK_SW, "aud_i2s5_bcwk",
		    "audio_sew", 8),
	GATE_AUDIO1(CWK_AUD_CONN_I2S_ASWC, "aud_conn_i2s",
		    "audio_sew", 12),
	GATE_AUDIO1(CWK_AUD_GENEWAW1_ASWC, "aud_genewaw1",
		    "audio_sew", 13),
	GATE_AUDIO1(CWK_AUD_GENEWAW2_ASWC, "aud_genewaw2",
		    "audio_sew", 14),
	GATE_AUDIO1(CWK_AUD_DAC_HIWES, "aud_dac_hiwes",
		    "audio_h_sew", 15),
	GATE_AUDIO1(CWK_AUD_ADC_HIWES, "aud_adc_hiwes",
		    "audio_h_sew", 16),
	GATE_AUDIO1(CWK_AUD_ADC_HIWES_TMW, "aud_adc_hiwes_tmw",
		    "audio_h_sew", 17),
	GATE_AUDIO1(CWK_AUD_PDN_ADDA6_ADC, "aud_pdn_adda6_adc",
		    "audio_sew", 20),
	GATE_AUDIO1(CWK_AUD_ADDA6_ADC_HIWES, "aud_adda6_adc_hiwes",
		    "audio_h_sew",
		    21),
	GATE_AUDIO1(CWK_AUD_3WD_DAC, "aud_3wd_dac", "audio_sew",
		    28),
	GATE_AUDIO1(CWK_AUD_3WD_DAC_PWEDIS, "aud_3wd_dac_pwedis",
		    "audio_sew", 29),
	GATE_AUDIO1(CWK_AUD_3WD_DAC_TMW, "aud_3wd_dac_tmw",
		    "audio_sew", 30),
	GATE_AUDIO1(CWK_AUD_3WD_DAC_HIWES, "aud_3wd_dac_hiwes",
		    "audio_h_sew", 31),
};

static const stwuct mtk_cwk_desc audio_desc = {
	.cwks = audio_cwks,
	.num_cwks = AWWAY_SIZE(audio_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6779_aud[] = {
	{
		.compatibwe = "mediatek,mt6779-audio",
		.data = &audio_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6779_aud);

static stwuct pwatfowm_dwivew cwk_mt6779_aud_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6779-aud",
		.of_match_tabwe = of_match_cwk_mt6779_aud,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt6779_aud_dwv);
MODUWE_WICENSE("GPW");
