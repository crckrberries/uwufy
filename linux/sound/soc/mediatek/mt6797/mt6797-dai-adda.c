// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI ADDA Contwow
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude "mt6797-afe-common.h"
#incwude "mt6797-intewconnection.h"
#incwude "mt6797-weg.h"

enum {
	MTK_AFE_ADDA_DW_WATE_8K = 0,
	MTK_AFE_ADDA_DW_WATE_11K = 1,
	MTK_AFE_ADDA_DW_WATE_12K = 2,
	MTK_AFE_ADDA_DW_WATE_16K = 3,
	MTK_AFE_ADDA_DW_WATE_22K = 4,
	MTK_AFE_ADDA_DW_WATE_24K = 5,
	MTK_AFE_ADDA_DW_WATE_32K = 6,
	MTK_AFE_ADDA_DW_WATE_44K = 7,
	MTK_AFE_ADDA_DW_WATE_48K = 8,
	MTK_AFE_ADDA_DW_WATE_96K = 9,
	MTK_AFE_ADDA_DW_WATE_192K = 10,
};

enum {
	MTK_AFE_ADDA_UW_WATE_8K = 0,
	MTK_AFE_ADDA_UW_WATE_16K = 1,
	MTK_AFE_ADDA_UW_WATE_32K = 2,
	MTK_AFE_ADDA_UW_WATE_48K = 3,
	MTK_AFE_ADDA_UW_WATE_96K = 4,
	MTK_AFE_ADDA_UW_WATE_192K = 5,
	MTK_AFE_ADDA_UW_WATE_48K_HD = 6,
};

static unsigned int adda_dw_wate_twansfowm(stwuct mtk_base_afe *afe,
					   unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_ADDA_DW_WATE_8K;
	case 11025:
		wetuwn MTK_AFE_ADDA_DW_WATE_11K;
	case 12000:
		wetuwn MTK_AFE_ADDA_DW_WATE_12K;
	case 16000:
		wetuwn MTK_AFE_ADDA_DW_WATE_16K;
	case 22050:
		wetuwn MTK_AFE_ADDA_DW_WATE_22K;
	case 24000:
		wetuwn MTK_AFE_ADDA_DW_WATE_24K;
	case 32000:
		wetuwn MTK_AFE_ADDA_DW_WATE_32K;
	case 44100:
		wetuwn MTK_AFE_ADDA_DW_WATE_44K;
	case 48000:
		wetuwn MTK_AFE_ADDA_DW_WATE_48K;
	case 96000:
		wetuwn MTK_AFE_ADDA_DW_WATE_96K;
	case 192000:
		wetuwn MTK_AFE_ADDA_DW_WATE_192K;
	defauwt:
		dev_wawn(afe->dev, "%s(), wate %d invawid, use 48kHz!!!\n",
			 __func__, wate);
		wetuwn MTK_AFE_ADDA_DW_WATE_48K;
	}
}

static unsigned int adda_uw_wate_twansfowm(stwuct mtk_base_afe *afe,
					   unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_ADDA_UW_WATE_8K;
	case 16000:
		wetuwn MTK_AFE_ADDA_UW_WATE_16K;
	case 32000:
		wetuwn MTK_AFE_ADDA_UW_WATE_32K;
	case 48000:
		wetuwn MTK_AFE_ADDA_UW_WATE_48K;
	case 96000:
		wetuwn MTK_AFE_ADDA_UW_WATE_96K;
	case 192000:
		wetuwn MTK_AFE_ADDA_UW_WATE_192K;
	defauwt:
		dev_wawn(afe->dev, "%s(), wate %d invawid, use 48kHz!!!\n",
			 __func__, wate);
		wetuwn MTK_AFE_ADDA_UW_WATE_48K;
	}
}

/* dai component */
static const stwuct snd_kcontwow_new mtk_adda_dw_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN3, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN3, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN3, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN3,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN3,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN3,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN3,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_adda_dw_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN4, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN4, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN4, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN4, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN4, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN4, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN4,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN4,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN4,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN4,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN4,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN4,
				    I_PCM_2_CAP_CH2, 1, 0),
};

static int mtk_adda_uw_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

enum {
	SUPPWY_SEQ_AUD_TOP_PDN,
	SUPPWY_SEQ_ADDA_AFE_ON,
	SUPPWY_SEQ_ADDA_DW_ON,
	SUPPWY_SEQ_ADDA_UW_ON,
};

static const stwuct snd_soc_dapm_widget mtk_dai_adda_widgets[] = {
	/* adda */
	SND_SOC_DAPM_MIXEW("ADDA_DW_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dw_ch1_mix,
			   AWWAY_SIZE(mtk_adda_dw_ch1_mix)),
	SND_SOC_DAPM_MIXEW("ADDA_DW_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dw_ch2_mix,
			   AWWAY_SIZE(mtk_adda_dw_ch2_mix)),

	SND_SOC_DAPM_SUPPWY_S("ADDA Enabwe", SUPPWY_SEQ_ADDA_AFE_ON,
			      AFE_ADDA_UW_DW_CON0, ADDA_AFE_ON_SFT, 0,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("ADDA Pwayback Enabwe", SUPPWY_SEQ_ADDA_DW_ON,
			      AFE_ADDA_DW_SWC2_CON0,
			      DW_2_SWC_ON_TMP_CTW_PWE_SFT, 0,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("ADDA Captuwe Enabwe", SUPPWY_SEQ_ADDA_UW_ON,
			      AFE_ADDA_UW_SWC_CON0,
			      UW_SWC_ON_TMP_CTW_SFT, 0,
			      mtk_adda_uw_event,
			      SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("aud_dac_cwk", SUPPWY_SEQ_AUD_TOP_PDN,
			      AUDIO_TOP_CON0, PDN_DAC_SFT, 1,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("aud_dac_pwedis_cwk", SUPPWY_SEQ_AUD_TOP_PDN,
			      AUDIO_TOP_CON0, PDN_DAC_PWEDIS_SFT, 1,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("aud_adc_cwk", SUPPWY_SEQ_AUD_TOP_PDN,
			      AUDIO_TOP_CON0, PDN_ADC_SFT, 1,
			      NUWW, 0),

	SND_SOC_DAPM_CWOCK_SUPPWY("mtkaif_26m_cwk"),
};

static const stwuct snd_soc_dapm_woute mtk_dai_adda_woutes[] = {
	/* pwayback */
	{"ADDA_DW_CH1", "DW1_CH1", "DW1"},
	{"ADDA_DW_CH2", "DW1_CH1", "DW1"},
	{"ADDA_DW_CH2", "DW1_CH2", "DW1"},

	{"ADDA_DW_CH1", "DW2_CH1", "DW2"},
	{"ADDA_DW_CH2", "DW2_CH1", "DW2"},
	{"ADDA_DW_CH2", "DW2_CH2", "DW2"},

	{"ADDA_DW_CH1", "DW3_CH1", "DW3"},
	{"ADDA_DW_CH2", "DW3_CH1", "DW3"},
	{"ADDA_DW_CH2", "DW3_CH2", "DW3"},

	{"ADDA Pwayback", NUWW, "ADDA_DW_CH1"},
	{"ADDA Pwayback", NUWW, "ADDA_DW_CH2"},

	/* adda enabwe */
	{"ADDA Pwayback", NUWW, "ADDA Enabwe"},
	{"ADDA Pwayback", NUWW, "ADDA Pwayback Enabwe"},
	{"ADDA Captuwe", NUWW, "ADDA Enabwe"},
	{"ADDA Captuwe", NUWW, "ADDA Captuwe Enabwe"},

	/* cwk */
	{"ADDA Pwayback", NUWW, "mtkaif_26m_cwk"},
	{"ADDA Pwayback", NUWW, "aud_dac_cwk"},
	{"ADDA Pwayback", NUWW, "aud_dac_pwedis_cwk"},

	{"ADDA Captuwe", NUWW, "mtkaif_26m_cwk"},
	{"ADDA Captuwe", NUWW, "aud_adc_cwk"},
};

/* dai ops */
static int mtk_dai_adda_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);

	dev_dbg(afe->dev, "%s(), id %d, stweam %d, wate %d\n",
		__func__, dai->id, substweam->stweam, wate);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		unsigned int dw_swc2_con0 = 0;
		unsigned int dw_swc2_con1 = 0;

		/* cwean pwedistowtion */
		wegmap_wwite(afe->wegmap, AFE_ADDA_PWEDIS_CON0, 0);
		wegmap_wwite(afe->wegmap, AFE_ADDA_PWEDIS_CON1, 0);

		/* set input sampwing wate */
		dw_swc2_con0 = adda_dw_wate_twansfowm(afe, wate) << 28;

		/* set output mode */
		switch (wate) {
		case 192000:
			dw_swc2_con0 |= (0x1 << 24); /* UP_SAMPWING_WATE_X2 */
			dw_swc2_con0 |= 1 << 14;
			bweak;
		case 96000:
			dw_swc2_con0 |= (0x2 << 24); /* UP_SAMPWING_WATE_X4 */
			dw_swc2_con0 |= 1 << 14;
			bweak;
		defauwt:
			dw_swc2_con0 |= (0x3 << 24); /* UP_SAMPWING_WATE_X8 */
			bweak;
		}

		/* tuwn off mute function */
		dw_swc2_con0 |= (0x03 << 11);

		/* set voice input data if input sampwe wate is 8k ow 16k */
		if (wate == 8000 || wate == 16000)
			dw_swc2_con0 |= 0x01 << 5;

		if (wate < 96000) {
			/* SA suggest appwy -0.3db to audio/speech path */
			dw_swc2_con1 = 0xf74f0000;
		} ewse {
			/* SA suggest appwy -0.3db to audio/speech path
			 * with DW gain set to hawf,
			 * 0xFFFF = 0dB -> 0x8000 = 0dB when 96k, 192k
			 */
			dw_swc2_con1 = 0x7ba70000;
		}

		/* tuwn on down-wink gain */
		dw_swc2_con0 = dw_swc2_con0 | (0x01 << 1);

		wegmap_wwite(afe->wegmap, AFE_ADDA_DW_SWC2_CON0, dw_swc2_con0);
		wegmap_wwite(afe->wegmap, AFE_ADDA_DW_SWC2_CON1, dw_swc2_con1);
	} ewse {
		unsigned int voice_mode = 0;
		unsigned int uw_swc_con0 = 0;	/* defauwt vawue */

		/* Using Intewnaw ADC */
		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_TOP_CON0,
				   0x1 << 0,
				   0x0 << 0);

		voice_mode = adda_uw_wate_twansfowm(afe, wate);

		uw_swc_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* up8x txif sat on */
		wegmap_wwite(afe->wegmap, AFE_ADDA_NEWIF_CFG0, 0x03F87201);

		if (wate >= 96000) {	/* hiwes */
			/* use hiwes fowmat [1 0 23] */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_NEWIF_CFG0,
					   0x1 << 5,
					   0x1 << 5);

			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_NEWIF_CFG2,
					   0xf << 28,
					   voice_mode << 28);
		} ewse {	/* nowmaw 8~48k */
			/* use fixed 260k anc path */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_NEWIF_CFG2,
					   0xf << 28,
					   8 << 28);

			/* uw_use_cic_out */
			uw_swc_con0 |= 0x1 << 20;
		}

		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_NEWIF_CFG2,
				   0xf << 28,
				   8 << 28);

		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_UW_SWC_CON0,
				   0xfffffffe,
				   uw_swc_con0);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_adda_ops = {
	.hw_pawams = mtk_dai_adda_hw_pawams,
};

/* dai dwivew */
#define MTK_ADDA_PWAYBACK_WATES (SNDWV_PCM_WATE_8000_48000 |\
				 SNDWV_PCM_WATE_96000 |\
				 SNDWV_PCM_WATE_192000)

#define MTK_ADDA_CAPTUWE_WATES (SNDWV_PCM_WATE_8000 |\
				SNDWV_PCM_WATE_16000 |\
				SNDWV_PCM_WATE_32000 |\
				SNDWV_PCM_WATE_48000 |\
				SNDWV_PCM_WATE_96000 |\
				SNDWV_PCM_WATE_192000)

#define MTK_ADDA_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			  SNDWV_PCM_FMTBIT_S24_WE |\
			  SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_adda_dwivew[] = {
	{
		.name = "ADDA",
		.id = MT6797_DAI_ADDA,
		.pwayback = {
			.stweam_name = "ADDA Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_PWAYBACK_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "ADDA Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_CAPTUWE_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.ops = &mtk_dai_adda_ops,
	},
};

int mt6797_dai_adda_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_adda_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_adda_dwivew);

	dai->dapm_widgets = mtk_dai_adda_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_adda_widgets);
	dai->dapm_woutes = mtk_dai_adda_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_adda_woutes);
	wetuwn 0;
}
