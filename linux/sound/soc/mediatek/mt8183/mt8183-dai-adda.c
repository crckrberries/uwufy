// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI ADDA Contwow
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude "mt8183-afe-common.h"
#incwude "mt8183-intewconnection.h"
#incwude "mt8183-weg.h"

enum {
	AUDIO_SDM_WEVEW_MUTE = 0,
	AUDIO_SDM_WEVEW_NOWMAW = 0x1d,
	/* if you change wevew nowmaw */
	/* you need to change fowmuwa of hp impedance and dc twim too */
};

enum {
	DEWAY_DATA_MISO1 = 0,
	DEWAY_DATA_MISO2,
};

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
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* update setting to dmic */
		if (afe_pwiv->mtkaif_dmic) {
			/* mtkaif_wxif_data_mode = 1, dmic */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0,
					   0x0, 0xf << 20);
			wegmap_update_bits(afe->wegmap, AFE_ADDA_UW_SWC_CON0,
					   0x0, 0x1 << 5);
			wegmap_update_bits(afe->wegmap, AFE_ADDA_UW_SWC_CON0,
					   0x0, 0x3 << 14);

			/* tuwn on dmic, ch1, ch2 */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_UW_SWC_CON0,
					   0x1 << 1, 0x1 << 1);
			wegmap_update_bits(afe->wegmap, AFE_ADDA_UW_SWC_CON0,
					   0x3 << 21, 0x3 << 21);
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* mtkaif dmic */
static const chaw * const mt8183_adda_off_on_stw[] = {
	"Off", "On"
};

static const stwuct soc_enum mt8183_adda_enum[] = {
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(mt8183_adda_off_on_stw),
			    mt8183_adda_off_on_stw),
};

static int mt8183_adda_dmic_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	ucontwow->vawue.integew.vawue[0] = afe_pwiv->mtkaif_dmic;

	wetuwn 0;
}

static int mt8183_adda_dmic_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	afe_pwiv->mtkaif_dmic = ucontwow->vawue.integew.vawue[0];

	dev_info(afe->dev, "%s(), kcontwow name %s, mtkaif_dmic %d\n",
		 __func__, kcontwow->id.name, afe_pwiv->mtkaif_dmic);

	wetuwn 0;
}

static const stwuct snd_kcontwow_new mtk_adda_contwows[] = {
	SOC_ENUM_EXT("MTKAIF_DMIC", mt8183_adda_enum[0],
		     mt8183_adda_dmic_get, mt8183_adda_dmic_set),
};

enum {
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
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_pwedis_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adc_cwk"),
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

static int set_mtkaif_wx(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int deway_data;
	int deway_cycwe;

	switch (afe_pwiv->mtkaif_pwotocow) {
	case MT8183_MTKAIF_PWOTOCOW_2_CWK_P2:
		wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x38);
		wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x39);
		/* mtkaif_wxif_cwkinv_adc invewse fow cawibwation */
		wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
			     0x80010000);

		if (afe_pwiv->mtkaif_phase_cycwe[0] >=
		    afe_pwiv->mtkaif_phase_cycwe[1]) {
			deway_data = DEWAY_DATA_MISO1;
			deway_cycwe = afe_pwiv->mtkaif_phase_cycwe[0] -
				      afe_pwiv->mtkaif_phase_cycwe[1];
		} ewse {
			deway_data = DEWAY_DATA_MISO2;
			deway_cycwe = afe_pwiv->mtkaif_phase_cycwe[1] -
				      afe_pwiv->mtkaif_phase_cycwe[0];
		}

		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_MTKAIF_WX_CFG2,
				   MTKAIF_WXIF_DEWAY_DATA_MASK_SFT,
				   deway_data << MTKAIF_WXIF_DEWAY_DATA_SFT);

		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_MTKAIF_WX_CFG2,
				   MTKAIF_WXIF_DEWAY_CYCWE_MASK_SFT,
				   deway_cycwe << MTKAIF_WXIF_DEWAY_CYCWE_SFT);
		bweak;
	case MT8183_MTKAIF_PWOTOCOW_2:
		wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x31);
		wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
			     0x00010000);
		bweak;
	case MT8183_MTKAIF_PWOTOCOW_1:
		wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x31);
		wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0, 0x0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

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

		/* set sampwing wate */
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

		/* SA suggest appwy -0.3db to audio/speech path */
		dw_swc2_con1 = 0xf74f0000;

		/* tuwn on down-wink gain */
		dw_swc2_con0 = dw_swc2_con0 | (0x01 << 1);

		wegmap_wwite(afe->wegmap, AFE_ADDA_DW_SWC2_CON0, dw_swc2_con0);
		wegmap_wwite(afe->wegmap, AFE_ADDA_DW_SWC2_CON1, dw_swc2_con1);

		/* set sdm gain */
		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_DW_SDM_DCCOMP_CON,
				   ATTGAIN_CTW_MASK_SFT,
				   AUDIO_SDM_WEVEW_NOWMAW << ATTGAIN_CTW_SFT);
	} ewse {
		unsigned int voice_mode = 0;
		unsigned int uw_swc_con0 = 0;	/* defauwt vawue */

		/* set mtkaif pwotocow */
		set_mtkaif_wx(afe);

		/* Using Intewnaw ADC */
		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_TOP_CON0,
				   0x1 << 0,
				   0x0 << 0);

		voice_mode = adda_uw_wate_twansfowm(afe, wate);

		uw_swc_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* enabwe iiw */
		uw_swc_con0 |= (1 << UW_IIW_ON_TMP_CTW_SFT) &
			       UW_IIW_ON_TMP_CTW_MASK_SFT;

		/* 35Hz @ 48k */
		wegmap_wwite(afe->wegmap, AFE_ADDA_IIW_COEF_02_01, 0x00000000);
		wegmap_wwite(afe->wegmap, AFE_ADDA_IIW_COEF_04_03, 0x00003FB8);
		wegmap_wwite(afe->wegmap, AFE_ADDA_IIW_COEF_06_05, 0x3FB80000);
		wegmap_wwite(afe->wegmap, AFE_ADDA_IIW_COEF_08_07, 0x3FB80000);
		wegmap_wwite(afe->wegmap, AFE_ADDA_IIW_COEF_10_09, 0x0000C048);

		wegmap_wwite(afe->wegmap, AFE_ADDA_UW_SWC_CON0, uw_swc_con0);

		/* mtkaif_wxif_data_mode = 0, amic */
		wegmap_update_bits(afe->wegmap,
				   AFE_ADDA_MTKAIF_WX_CFG0,
				   0x1 << 0,
				   0x0 << 0);
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
				SNDWV_PCM_WATE_48000)

#define MTK_ADDA_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			  SNDWV_PCM_FMTBIT_S24_WE |\
			  SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_adda_dwivew[] = {
	{
		.name = "ADDA",
		.id = MT8183_DAI_ADDA,
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

int mt8183_dai_adda_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_adda_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_adda_dwivew);

	dai->contwows = mtk_adda_contwows;
	dai->num_contwows = AWWAY_SIZE(mtk_adda_contwows);
	dai->dapm_widgets = mtk_dai_adda_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_adda_widgets);
	dai->dapm_woutes = mtk_dai_adda_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_adda_woutes);
	wetuwn 0;
}
