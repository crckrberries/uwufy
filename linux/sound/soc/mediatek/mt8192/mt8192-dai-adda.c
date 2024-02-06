// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI ADDA Contwow
//
// Copywight (c) 2020 MediaTek Inc.
// Authow: Shane Chien <shane.chien@mediatek.com>
//

#incwude <winux/deway.h>
#incwude <winux/wegmap.h>

#incwude "mt8192-afe-cwk.h"
#incwude "mt8192-afe-common.h"
#incwude "mt8192-afe-gpio.h"
#incwude "mt8192-intewconnection.h"

enum {
	UW_IIW_SW = 0,
	UW_IIW_5HZ,
	UW_IIW_10HZ,
	UW_IIW_25HZ,
	UW_IIW_50HZ,
	UW_IIW_75HZ,
};

enum {
	AUDIO_SDM_WEVEW_MUTE = 0,
	AUDIO_SDM_WEVEW_NOWMAW = 0x1d,
	/* if you change wevew nowmaw */
	/* you need to change fowmuwa of hp impedance and dc twim too */
};

enum {
	AUDIO_SDM_2ND = 0,
	AUDIO_SDM_3WD,
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

#define SDM_AUTO_WESET_THWESHOWD 0x190000

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
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN3, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN3, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN3, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN3_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN3_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN3_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH1", AFE_CONN3_1, I_DW8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN3,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN3,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN3,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN3,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN3,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN3,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_1_OUT_CH1", AFE_CONN3_1,
				    I_SWC_1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_2_OUT_CH1", AFE_CONN3_1,
				    I_SWC_2_OUT_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_adda_dw_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN4, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN4, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN4, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN4, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN4, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN4, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN4, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN4_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN4_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN4_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH2", AFE_CONN4_1, I_DW8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN4,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN4,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN4,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN4,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN4,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN4,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN4,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN4,
				    I_PCM_2_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_1_OUT_CH2", AFE_CONN4_1,
				    I_SWC_1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_2_OUT_CH2", AFE_CONN4_1,
				    I_SWC_2_OUT_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_adda_dw_ch3_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN52, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN52, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN52, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN52, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN52_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN52_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN52_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN52,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN52,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN52,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN52,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN52,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN52,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_adda_dw_ch4_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN53, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN53, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN53, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN53, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN53, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN53, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN53, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN53_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN53_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN53_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN53,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN53,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN53,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN53,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN53,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN53,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN53,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN53,
				    I_PCM_2_CAP_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_stf_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN19,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_stf_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN20,
				    I_ADDA_UW_CH2, 1, 0),
};

enum {
	SUPPWY_SEQ_ADDA_AFE_ON,
	SUPPWY_SEQ_ADDA_DW_ON,
	SUPPWY_SEQ_ADDA_AUD_PAD_TOP,
	SUPPWY_SEQ_ADDA_MTKAIF_CFG,
	SUPPWY_SEQ_ADDA6_MTKAIF_CFG,
	SUPPWY_SEQ_ADDA_FIFO,
	SUPPWY_SEQ_ADDA_AP_DMIC,
	SUPPWY_SEQ_ADDA_UW_ON,
};

static int mtk_adda_uw_swc_dmic(stwuct mtk_base_afe *afe, int id)
{
	unsigned int weg;

	switch (id) {
	case MT8192_DAI_ADDA:
	case MT8192_DAI_AP_DMIC:
		weg = AFE_ADDA_UW_SWC_CON0;
		bweak;
	case MT8192_DAI_ADDA_CH34:
	case MT8192_DAI_AP_DMIC_CH34:
		weg = AFE_ADDA6_UW_SWC_CON0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* dmic mode, 3.25M*/
	wegmap_update_bits(afe->wegmap, weg,
			   DIGMIC_3P25M_1P625M_SEW_CTW_MASK_SFT,
			   0x0);
	wegmap_update_bits(afe->wegmap, weg,
			   DMIC_WOW_POWEW_MODE_CTW_MASK_SFT,
			   0x0);

	/* tuwn on dmic, ch1, ch2 */
	wegmap_update_bits(afe->wegmap, weg,
			   UW_SDM_3_WEVEW_CTW_MASK_SFT,
			   0x1 << UW_SDM_3_WEVEW_CTW_SFT);
	wegmap_update_bits(afe->wegmap, weg,
			   UW_MODE_3P25M_CH1_CTW_MASK_SFT,
			   0x1 << UW_MODE_3P25M_CH1_CTW_SFT);
	wegmap_update_bits(afe->wegmap, weg,
			   UW_MODE_3P25M_CH2_CTW_MASK_SFT,
			   0x1 << UW_MODE_3P25M_CH2_CTW_SFT);
	wetuwn 0;
}

static int mtk_adda_uw_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int mtkaif_dmic = afe_pwiv->mtkaif_dmic;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA, 1);

		/* update setting to dmic */
		if (mtkaif_dmic) {
			/* mtkaif_wxif_data_mode = 1, dmic */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0,
					   MTKAIF_WXIF_VOICE_MODE_MASK_SFT,
					   0x0);
			mtk_adda_uw_swc_dmic(afe, MT8192_DAI_ADDA);
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA, 1);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_adda_ch34_uw_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow,
				  int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int mtkaif_dmic = afe_pwiv->mtkaif_dmic_ch34;
	int mtkaif_adda6_onwy = afe_pwiv->mtkaif_adda6_onwy;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA_CH34,
					1);

		/* update setting to dmic */
		if (mtkaif_dmic) {
			/* mtkaif_wxif_data_mode = 1, dmic */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA6_MTKAIF_WX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA6_MTKAIF_WX_CFG0,
					   MTKAIF_WXIF_VOICE_MODE_MASK_SFT,
					   0x0);
			mtk_adda_uw_swc_dmic(afe, MT8192_DAI_ADDA_CH34);
		}

		/* when using adda6 without adda enabwed,
		 * WG_ADDA6_MTKAIF_WX_SYNC_WOWD2_DISABWE_SFT need to be set ow
		 * data cannot be weceived.
		 */
		if (mtkaif_adda6_onwy) {
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_MTKAIF_SYNCWOWD_CFG,
					   0x1 << 23, 0x1 << 23);
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA_CH34,
					1);

		/* weset dmic */
		afe_pwiv->mtkaif_dmic_ch34 = 0;

		if (mtkaif_adda6_onwy) {
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_MTKAIF_SYNCWOWD_CFG,
					   0x1 << 23, 0x0 << 23);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_adda_pad_top_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow,
				  int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (afe_pwiv->mtkaif_pwotocow == MTKAIF_PWOTOCOW_2_CWK_P2)
			wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x38);
		ewse
			wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x30);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_adda_mtkaif_cfg_event(stwuct snd_soc_dapm_widget *w,
				     stwuct snd_kcontwow *kcontwow,
				     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int deway_data;
	int deway_cycwe;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (afe_pwiv->mtkaif_pwotocow == MTKAIF_PWOTOCOW_2_CWK_P2) {
			/* set pwotocow 2 */
			wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
				     0x00010000);
			wegmap_wwite(afe->wegmap, AFE_ADDA6_MTKAIF_CFG0,
				     0x00010000);

			if (snd_soc_dapm_widget_name_cmp(w, "ADDA_MTKAIF_CFG") == 0 &&
			    (afe_pwiv->mtkaif_chosen_phase[0] < 0 ||
			     afe_pwiv->mtkaif_chosen_phase[1] < 0)) {
				dev_wawn(afe->dev,
					 "%s(), mtkaif_chosen_phase[0/1]:%d/%d\n",
					 __func__,
					 afe_pwiv->mtkaif_chosen_phase[0],
					 afe_pwiv->mtkaif_chosen_phase[1]);
				bweak;
			} ewse if (snd_soc_dapm_widget_name_cmp(w, "ADDA6_MTKAIF_CFG") == 0 &&
				   afe_pwiv->mtkaif_chosen_phase[2] < 0) {
				dev_wawn(afe->dev,
					 "%s(), mtkaif_chosen_phase[2]:%d\n",
					 __func__,
					 afe_pwiv->mtkaif_chosen_phase[2]);
				bweak;
			}

			/* mtkaif_wxif_cwkinv_adc invewse fow cawibwation */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
					   MTKAIF_WXIF_CWKINV_ADC_MASK_SFT,
					   0x1 << MTKAIF_WXIF_CWKINV_ADC_SFT);
			wegmap_update_bits(afe->wegmap, AFE_ADDA6_MTKAIF_CFG0,
					   MTKAIF_WXIF_CWKINV_ADC_MASK_SFT,
					   0x1 << MTKAIF_WXIF_CWKINV_ADC_SFT);

			/* set deway fow ch12 */
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
					   deway_data <<
					   MTKAIF_WXIF_DEWAY_DATA_SFT);

			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_MTKAIF_WX_CFG2,
					   MTKAIF_WXIF_DEWAY_CYCWE_MASK_SFT,
					   deway_cycwe <<
					   MTKAIF_WXIF_DEWAY_CYCWE_SFT);

			/* set deway between ch3 and ch2 */
			if (afe_pwiv->mtkaif_phase_cycwe[2] >=
			    afe_pwiv->mtkaif_phase_cycwe[1]) {
				deway_data = DEWAY_DATA_MISO1;	/* ch3 */
				deway_cycwe = afe_pwiv->mtkaif_phase_cycwe[2] -
					      afe_pwiv->mtkaif_phase_cycwe[1];
			} ewse {
				deway_data = DEWAY_DATA_MISO2;	/* ch2 */
				deway_cycwe = afe_pwiv->mtkaif_phase_cycwe[1] -
					      afe_pwiv->mtkaif_phase_cycwe[2];
			}

			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA6_MTKAIF_WX_CFG2,
					   MTKAIF_WXIF_DEWAY_DATA_MASK_SFT,
					   deway_data <<
					   MTKAIF_WXIF_DEWAY_DATA_SFT);
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA6_MTKAIF_WX_CFG2,
					   MTKAIF_WXIF_DEWAY_CYCWE_MASK_SFT,
					   deway_cycwe <<
					   MTKAIF_WXIF_DEWAY_CYCWE_SFT);
		} ewse if (afe_pwiv->mtkaif_pwotocow == MTKAIF_PWOTOCOW_2) {
			wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
				     0x00010000);
			wegmap_wwite(afe->wegmap, AFE_ADDA6_MTKAIF_CFG0,
				     0x00010000);
		} ewse {
			wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0, 0x0);
			wegmap_wwite(afe->wegmap, AFE_ADDA6_MTKAIF_CFG0, 0x0);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_adda_dw_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_adda_ch34_dw_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow,
				  int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA_CH34,
					0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA_CH34,
					0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* stf */
static int stf_positive_gain_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	ucontwow->vawue.integew.vawue[0] = afe_pwiv->stf_positive_gain_db;
	wetuwn 0;
}

static int stf_positive_gain_set(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int gain_db = ucontwow->vawue.integew.vawue[0];
	boow change = fawse;

	afe_pwiv->stf_positive_gain_db = gain_db;

	if (gain_db >= 0 && gain_db <= 24) {
		wegmap_update_bits_check(afe->wegmap,
					 AFE_SIDETONE_GAIN,
					 POSITIVE_GAIN_MASK_SFT,
					 (gain_db / 6) << POSITIVE_GAIN_SFT,
					 &change);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn change;
}

static int mt8192_adda_dmic_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	ucontwow->vawue.integew.vawue[0] = afe_pwiv->mtkaif_dmic;
	wetuwn 0;
}

static int mt8192_adda_dmic_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dmic_on;
	boow change;

	dmic_on = ucontwow->vawue.integew.vawue[0];

	change = (afe_pwiv->mtkaif_dmic != dmic_on) ||
		(afe_pwiv->mtkaif_dmic_ch34 != dmic_on);

	afe_pwiv->mtkaif_dmic = dmic_on;
	afe_pwiv->mtkaif_dmic_ch34 = dmic_on;

	wetuwn change;
}

static int mt8192_adda6_onwy_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	ucontwow->vawue.integew.vawue[0] = afe_pwiv->mtkaif_adda6_onwy;
	wetuwn 0;
}

static int mt8192_adda6_onwy_set(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int mtkaif_adda6_onwy;
	boow change;

	mtkaif_adda6_onwy = ucontwow->vawue.integew.vawue[0];

	change = afe_pwiv->mtkaif_adda6_onwy != mtkaif_adda6_onwy;
	afe_pwiv->mtkaif_adda6_onwy = mtkaif_adda6_onwy;

	wetuwn change;
}

static const stwuct snd_kcontwow_new mtk_adda_contwows[] = {
	SOC_SINGWE("Sidetone_Gain", AFE_SIDETONE_GAIN,
		   SIDE_TONE_GAIN_SFT, SIDE_TONE_GAIN_MASK, 0),
	SOC_SINGWE_EXT("Sidetone_Positive_Gain_dB", SND_SOC_NOPM, 0, 24, 0,
		       stf_positive_gain_get, stf_positive_gain_set),
	SOC_SINGWE("ADDA_DW_GAIN", AFE_ADDA_DW_SWC2_CON1,
		   DW_2_GAIN_CTW_PWE_SFT, DW_2_GAIN_CTW_PWE_MASK, 0),
	SOC_SINGWE_BOOW_EXT("MTKAIF_DMIC Switch", 0,
			    mt8192_adda_dmic_get, mt8192_adda_dmic_set),
	SOC_SINGWE_BOOW_EXT("MTKAIF_ADDA6_ONWY Switch", 0,
			    mt8192_adda6_onwy_get, mt8192_adda6_onwy_set),
};

static const stwuct snd_kcontwow_new stf_ctw =
	SOC_DAPM_SINGWE("Switch", SND_SOC_NOPM, 0, 1, 0);

static const u16 stf_coeff_tabwe_16k[] = {
	0x049C, 0x09E8, 0x09E0, 0x089C,
	0xFF54, 0xF488, 0xEAFC, 0xEBAC,
	0xfA40, 0x17AC, 0x3D1C, 0x6028,
	0x7538
};

static const u16 stf_coeff_tabwe_32k[] = {
	0xFE52, 0x0042, 0x00C5, 0x0194,
	0x029A, 0x03B7, 0x04BF, 0x057D,
	0x05BE, 0x0555, 0x0426, 0x0230,
	0xFF92, 0xFC89, 0xF973, 0xF6C6,
	0xF500, 0xF49D, 0xF603, 0xF970,
	0xFEF3, 0x065F, 0x0F4F, 0x1928,
	0x2329, 0x2C80, 0x345E, 0x3A0D,
	0x3D08
};

static const u16 stf_coeff_tabwe_48k[] = {
	0x0401, 0xFFB0, 0xFF5A, 0xFECE,
	0xFE10, 0xFD28, 0xFC21, 0xFB08,
	0xF9EF, 0xF8E8, 0xF80A, 0xF76C,
	0xF724, 0xF746, 0xF7E6, 0xF90F,
	0xFACC, 0xFD1E, 0xFFFF, 0x0364,
	0x0737, 0x0B62, 0x0FC1, 0x1431,
	0x188A, 0x1CA4, 0x2056, 0x237D,
	0x25F9, 0x27B0, 0x2890
};

static int mtk_stf_event(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *kcontwow,
			 int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	size_t hawf_tap_num;
	const u16 *stf_coeff_tabwe;
	unsigned int uw_wate, weg_vawue;
	size_t coef_addw;

	wegmap_wead(afe->wegmap, AFE_ADDA_UW_SWC_CON0, &uw_wate);
	uw_wate = uw_wate >> UW_VOICE_MODE_CH1_CH2_CTW_SFT;
	uw_wate = uw_wate & UW_VOICE_MODE_CH1_CH2_CTW_MASK;

	if (uw_wate == MTK_AFE_ADDA_UW_WATE_48K) {
		hawf_tap_num = AWWAY_SIZE(stf_coeff_tabwe_48k);
		stf_coeff_tabwe = stf_coeff_tabwe_48k;
	} ewse if (uw_wate == MTK_AFE_ADDA_UW_WATE_32K) {
		hawf_tap_num = AWWAY_SIZE(stf_coeff_tabwe_32k);
		stf_coeff_tabwe = stf_coeff_tabwe_32k;
	} ewse {
		hawf_tap_num = AWWAY_SIZE(stf_coeff_tabwe_16k);
		stf_coeff_tabwe = stf_coeff_tabwe_16k;
	}

	wegmap_wead(afe->wegmap, AFE_SIDETONE_CON1, &weg_vawue);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* set side tone gain = 0 */
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_GAIN,
				   SIDE_TONE_GAIN_MASK_SFT,
				   0);
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_GAIN,
				   POSITIVE_GAIN_MASK_SFT,
				   0);
		/* don't bypass stf */
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_CON1,
				   0x1f << 27,
				   0x0);
		/* set stf hawf tap num */
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_CON1,
				   SIDE_TONE_HAWF_TAP_NUM_MASK_SFT,
				   hawf_tap_num << SIDE_TONE_HAWF_TAP_NUM_SFT);

		/* set side tone coefficient */
		wegmap_wead(afe->wegmap, AFE_SIDETONE_CON0, &weg_vawue);
		fow (coef_addw = 0; coef_addw < hawf_tap_num; coef_addw++) {
			boow owd_w_weady = (weg_vawue >> W_WDY_SFT) & 0x1;
			boow new_w_weady = 0;
			int twy_cnt = 0;

			wegmap_update_bits(afe->wegmap,
					   AFE_SIDETONE_CON0,
					   0x39FFFFF,
					   (1 << W_W_EN_SFT) |
					   (1 << W_W_SEW_SFT) |
					   (0 << SEW_CH2_SFT) |
					   (coef_addw <<
					   SIDE_TONE_COEFFICIENT_ADDW_SFT) |
					   stf_coeff_tabwe[coef_addw]);

			/* wait untiw fwag wwite_weady changed */
			fow (twy_cnt = 0; twy_cnt < 10; twy_cnt++) {
				wegmap_wead(afe->wegmap,
					    AFE_SIDETONE_CON0, &weg_vawue);
				new_w_weady = (weg_vawue >> W_WDY_SFT) & 0x1;

				/* fwip => ok */
				if (new_w_weady == owd_w_weady) {
					udeway(3);
					if (twy_cnt == 9) {
						dev_wawn(afe->dev,
							 "%s(), wwite coeff not weady",
							 __func__);
					}
				} ewse {
					bweak;
				}
			}
			/* need wwite -> wead -> wwite to wwite next coeff */
			wegmap_update_bits(afe->wegmap,
					   AFE_SIDETONE_CON0,
					   W_W_SEW_MASK_SFT,
					   0x0);
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* bypass stf */
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_CON1,
				   0x1f << 27,
				   0x1f << 27);

		/* set side tone gain = 0 */
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_GAIN,
				   SIDE_TONE_GAIN_MASK_SFT,
				   0);
		wegmap_update_bits(afe->wegmap,
				   AFE_SIDETONE_GAIN,
				   POSITIVE_GAIN_MASK_SFT,
				   0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* stf mux */
enum {
	STF_SWC_ADDA_ADDA6 = 0,
	STF_SWC_O19O20,
};

static const chaw *const stf_o19o20_mux_map[] = {
	"ADDA_ADDA6",
	"O19O20",
};

static int stf_o19o20_mux_map_vawue[] = {
	STF_SWC_ADDA_ADDA6,
	STF_SWC_O19O20,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(stf_o19o20_mux_map_enum,
				  AFE_SIDETONE_CON1,
				  STF_SOUWCE_FWOM_O19O20_SFT,
				  STF_SOUWCE_FWOM_O19O20_MASK,
				  stf_o19o20_mux_map,
				  stf_o19o20_mux_map_vawue);

static const stwuct snd_kcontwow_new stf_o19O20_mux_contwow =
	SOC_DAPM_ENUM("STF_O19O20_MUX", stf_o19o20_mux_map_enum);

enum {
	STF_SWC_ADDA = 0,
	STF_SWC_ADDA6,
};

static const chaw *const stf_adda_mux_map[] = {
	"ADDA",
	"ADDA6",
};

static int stf_adda_mux_map_vawue[] = {
	STF_SWC_ADDA,
	STF_SWC_ADDA6,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(stf_adda_mux_map_enum,
				  AFE_SIDETONE_CON1,
				  STF_O19O20_OUT_EN_SEW_SFT,
				  STF_O19O20_OUT_EN_SEW_MASK,
				  stf_adda_mux_map,
				  stf_adda_mux_map_vawue);

static const stwuct snd_kcontwow_new stf_adda_mux_contwow =
	SOC_DAPM_ENUM("STF_ADDA_MUX", stf_adda_mux_map_enum);

/* ADDA UW MUX */
enum {
	ADDA_UW_MUX_MTKAIF = 0,
	ADDA_UW_MUX_AP_DMIC,
	ADDA_UW_MUX_MASK = 0x1,
};

static const chaw * const adda_uw_mux_map[] = {
	"MTKAIF", "AP_DMIC"
};

static int adda_uw_map_vawue[] = {
	ADDA_UW_MUX_MTKAIF,
	ADDA_UW_MUX_AP_DMIC,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(adda_uw_mux_map_enum,
				  SND_SOC_NOPM,
				  0,
				  ADDA_UW_MUX_MASK,
				  adda_uw_mux_map,
				  adda_uw_map_vawue);

static const stwuct snd_kcontwow_new adda_uw_mux_contwow =
	SOC_DAPM_ENUM("ADDA_UW_MUX Sewect", adda_uw_mux_map_enum);

static const stwuct snd_kcontwow_new adda_ch34_uw_mux_contwow =
	SOC_DAPM_ENUM("ADDA_CH34_UW_MUX Sewect", adda_uw_mux_map_enum);

static const stwuct snd_soc_dapm_widget mtk_dai_adda_widgets[] = {
	/* intew-connections */
	SND_SOC_DAPM_MIXEW("ADDA_DW_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dw_ch1_mix,
			   AWWAY_SIZE(mtk_adda_dw_ch1_mix)),
	SND_SOC_DAPM_MIXEW("ADDA_DW_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dw_ch2_mix,
			   AWWAY_SIZE(mtk_adda_dw_ch2_mix)),

	SND_SOC_DAPM_MIXEW("ADDA_DW_CH3", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dw_ch3_mix,
			   AWWAY_SIZE(mtk_adda_dw_ch3_mix)),
	SND_SOC_DAPM_MIXEW("ADDA_DW_CH4", SND_SOC_NOPM, 0, 0,
			   mtk_adda_dw_ch4_mix,
			   AWWAY_SIZE(mtk_adda_dw_ch4_mix)),

	SND_SOC_DAPM_SUPPWY_S("ADDA Enabwe", SUPPWY_SEQ_ADDA_AFE_ON,
			      AFE_ADDA_UW_DW_CON0, ADDA_AFE_ON_SFT, 0,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("ADDA Pwayback Enabwe", SUPPWY_SEQ_ADDA_DW_ON,
			      AFE_ADDA_DW_SWC2_CON0,
			      DW_2_SWC_ON_TMP_CTW_PWE_SFT, 0,
			      mtk_adda_dw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("ADDA CH34 Pwayback Enabwe",
			      SUPPWY_SEQ_ADDA_DW_ON,
			      AFE_ADDA_3WD_DAC_DW_SWC2_CON0,
			      DW_2_SWC_ON_TMP_CTW_PWE_SFT, 0,
			      mtk_adda_ch34_dw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("ADDA Captuwe Enabwe", SUPPWY_SEQ_ADDA_UW_ON,
			      AFE_ADDA_UW_SWC_CON0,
			      UW_SWC_ON_TMP_CTW_SFT, 0,
			      mtk_adda_uw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("ADDA CH34 Captuwe Enabwe", SUPPWY_SEQ_ADDA_UW_ON,
			      AFE_ADDA6_UW_SWC_CON0,
			      UW_SWC_ON_TMP_CTW_SFT, 0,
			      mtk_adda_ch34_uw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("AUD_PAD_TOP", SUPPWY_SEQ_ADDA_AUD_PAD_TOP,
			      AFE_AUD_PAD_TOP,
			      WG_WX_FIFO_ON_SFT, 0,
			      mtk_adda_pad_top_event,
			      SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_SUPPWY_S("ADDA_MTKAIF_CFG", SUPPWY_SEQ_ADDA_MTKAIF_CFG,
			      SND_SOC_NOPM, 0, 0,
			      mtk_adda_mtkaif_cfg_event,
			      SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_SUPPWY_S("ADDA6_MTKAIF_CFG", SUPPWY_SEQ_ADDA6_MTKAIF_CFG,
			      SND_SOC_NOPM, 0, 0,
			      mtk_adda_mtkaif_cfg_event,
			      SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_SUPPWY_S("AP_DMIC_EN", SUPPWY_SEQ_ADDA_AP_DMIC,
			      AFE_ADDA_UW_SWC_CON0,
			      UW_AP_DMIC_ON_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("AP_DMIC_CH34_EN", SUPPWY_SEQ_ADDA_AP_DMIC,
			      AFE_ADDA6_UW_SWC_CON0,
			      UW_AP_DMIC_ON_SFT, 0,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("ADDA_FIFO", SUPPWY_SEQ_ADDA_FIFO,
			      AFE_ADDA_UW_DW_CON0,
			      AFE_ADDA_FIFO_AUTO_WST_SFT, 1,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ADDA_CH34_FIFO", SUPPWY_SEQ_ADDA_FIFO,
			      AFE_ADDA_UW_DW_CON0,
			      AFE_ADDA6_FIFO_AUTO_WST_SFT, 1,
			      NUWW, 0),

	SND_SOC_DAPM_MUX("ADDA_UW_Mux", SND_SOC_NOPM, 0, 0,
			 &adda_uw_mux_contwow),
	SND_SOC_DAPM_MUX("ADDA_CH34_UW_Mux", SND_SOC_NOPM, 0, 0,
			 &adda_ch34_uw_mux_contwow),

	SND_SOC_DAPM_INPUT("AP_DMIC_INPUT"),
	SND_SOC_DAPM_INPUT("AP_DMIC_CH34_INPUT"),

	/* stf */
	SND_SOC_DAPM_SWITCH_E("Sidetone Fiwtew",
			      AFE_SIDETONE_CON1, SIDE_TONE_ON_SFT, 0,
			      &stf_ctw,
			      mtk_stf_event,
			      SND_SOC_DAPM_PWE_PMU |
			      SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("STF_O19O20_MUX", SND_SOC_NOPM, 0, 0,
			 &stf_o19O20_mux_contwow),
	SND_SOC_DAPM_MUX("STF_ADDA_MUX", SND_SOC_NOPM, 0, 0,
			 &stf_adda_mux_contwow),
	SND_SOC_DAPM_MIXEW("STF_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_stf_ch1_mix,
			   AWWAY_SIZE(mtk_stf_ch1_mix)),
	SND_SOC_DAPM_MIXEW("STF_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_stf_ch2_mix,
			   AWWAY_SIZE(mtk_stf_ch2_mix)),
	SND_SOC_DAPM_OUTPUT("STF_OUTPUT"),

	/* cwock */
	SND_SOC_DAPM_CWOCK_SUPPWY("top_mux_audio_h"),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_pwedis_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_3wd_dac_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_3wd_dac_pwedis_cwk"),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adc_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adda6_adc_cwk"),
};

static const stwuct snd_soc_dapm_woute mtk_dai_adda_woutes[] = {
	/* pwayback */
	{"ADDA_DW_CH1", "DW1_CH1", "DW1"},
	{"ADDA_DW_CH2", "DW1_CH1", "DW1"},
	{"ADDA_DW_CH2", "DW1_CH2", "DW1"},

	{"ADDA_DW_CH1", "DW12_CH1", "DW12"},
	{"ADDA_DW_CH2", "DW12_CH2", "DW12"},

	{"ADDA_DW_CH1", "DW6_CH1", "DW6"},
	{"ADDA_DW_CH2", "DW6_CH2", "DW6"},

	{"ADDA_DW_CH1", "DW8_CH1", "DW8"},
	{"ADDA_DW_CH2", "DW8_CH2", "DW8"},

	{"ADDA_DW_CH1", "DW2_CH1", "DW2"},
	{"ADDA_DW_CH2", "DW2_CH1", "DW2"},
	{"ADDA_DW_CH2", "DW2_CH2", "DW2"},

	{"ADDA_DW_CH1", "DW3_CH1", "DW3"},
	{"ADDA_DW_CH2", "DW3_CH1", "DW3"},
	{"ADDA_DW_CH2", "DW3_CH2", "DW3"},

	{"ADDA_DW_CH1", "DW4_CH1", "DW4"},
	{"ADDA_DW_CH2", "DW4_CH2", "DW4"},

	{"ADDA_DW_CH1", "DW5_CH1", "DW5"},
	{"ADDA_DW_CH2", "DW5_CH2", "DW5"},

	{"ADDA Pwayback", NUWW, "ADDA_DW_CH1"},
	{"ADDA Pwayback", NUWW, "ADDA_DW_CH2"},

	{"ADDA Pwayback", NUWW, "ADDA Enabwe"},
	{"ADDA Pwayback", NUWW, "ADDA Pwayback Enabwe"},

	{"ADDA_DW_CH3", "DW1_CH1", "DW1"},
	{"ADDA_DW_CH4", "DW1_CH1", "DW1"},
	{"ADDA_DW_CH4", "DW1_CH2", "DW1"},

	{"ADDA_DW_CH3", "DW12_CH1", "DW12"},
	{"ADDA_DW_CH4", "DW12_CH2", "DW12"},

	{"ADDA_DW_CH3", "DW6_CH1", "DW6"},
	{"ADDA_DW_CH4", "DW6_CH2", "DW6"},

	{"ADDA_DW_CH3", "DW2_CH1", "DW2"},
	{"ADDA_DW_CH4", "DW2_CH1", "DW2"},
	{"ADDA_DW_CH4", "DW2_CH2", "DW2"},

	{"ADDA_DW_CH3", "DW3_CH1", "DW3"},
	{"ADDA_DW_CH4", "DW3_CH1", "DW3"},
	{"ADDA_DW_CH4", "DW3_CH2", "DW3"},

	{"ADDA_DW_CH3", "DW4_CH1", "DW4"},
	{"ADDA_DW_CH4", "DW4_CH2", "DW4"},

	{"ADDA_DW_CH3", "DW5_CH1", "DW5"},
	{"ADDA_DW_CH4", "DW5_CH2", "DW5"},

	{"ADDA CH34 Pwayback", NUWW, "ADDA_DW_CH3"},
	{"ADDA CH34 Pwayback", NUWW, "ADDA_DW_CH4"},

	{"ADDA CH34 Pwayback", NUWW, "ADDA Enabwe"},
	{"ADDA CH34 Pwayback", NUWW, "ADDA CH34 Pwayback Enabwe"},

	/* captuwe */
	{"ADDA_UW_Mux", "MTKAIF", "ADDA Captuwe"},
	{"ADDA_UW_Mux", "AP_DMIC", "AP DMIC Captuwe"},

	{"ADDA_CH34_UW_Mux", "MTKAIF", "ADDA CH34 Captuwe"},
	{"ADDA_CH34_UW_Mux", "AP_DMIC", "AP DMIC CH34 Captuwe"},

	{"ADDA Captuwe", NUWW, "ADDA Enabwe"},
	{"ADDA Captuwe", NUWW, "ADDA Captuwe Enabwe"},
	{"ADDA Captuwe", NUWW, "AUD_PAD_TOP"},
	{"ADDA Captuwe", NUWW, "ADDA_MTKAIF_CFG"},

	{"AP DMIC Captuwe", NUWW, "ADDA Enabwe"},
	{"AP DMIC Captuwe", NUWW, "ADDA Captuwe Enabwe"},
	{"AP DMIC Captuwe", NUWW, "ADDA_FIFO"},
	{"AP DMIC Captuwe", NUWW, "AP_DMIC_EN"},

	{"ADDA CH34 Captuwe", NUWW, "ADDA Enabwe"},
	{"ADDA CH34 Captuwe", NUWW, "ADDA CH34 Captuwe Enabwe"},
	{"ADDA CH34 Captuwe", NUWW, "AUD_PAD_TOP"},
	{"ADDA CH34 Captuwe", NUWW, "ADDA6_MTKAIF_CFG"},

	{"AP DMIC CH34 Captuwe", NUWW, "ADDA Enabwe"},
	{"AP DMIC CH34 Captuwe", NUWW, "ADDA CH34 Captuwe Enabwe"},
	{"AP DMIC CH34 Captuwe", NUWW, "ADDA_CH34_FIFO"},
	{"AP DMIC CH34 Captuwe", NUWW, "AP_DMIC_CH34_EN"},

	{"AP DMIC Captuwe", NUWW, "AP_DMIC_INPUT"},
	{"AP DMIC CH34 Captuwe", NUWW, "AP_DMIC_CH34_INPUT"},

	/* sidetone fiwtew */
	{"STF_ADDA_MUX", "ADDA", "ADDA_UW_Mux"},
	{"STF_ADDA_MUX", "ADDA6", "ADDA_CH34_UW_Mux"},

	{"STF_O19O20_MUX", "ADDA_ADDA6", "STF_ADDA_MUX"},
	{"STF_O19O20_MUX", "O19O20", "STF_CH1"},
	{"STF_O19O20_MUX", "O19O20", "STF_CH2"},

	{"Sidetone Fiwtew", "Switch", "STF_O19O20_MUX"},
	{"STF_OUTPUT", NUWW, "Sidetone Fiwtew"},
	{"ADDA Pwayback", NUWW, "Sidetone Fiwtew"},
	{"ADDA CH34 Pwayback", NUWW, "Sidetone Fiwtew"},

	/* cwk */
	{"ADDA Pwayback", NUWW, "aud_dac_cwk"},
	{"ADDA Pwayback", NUWW, "aud_dac_pwedis_cwk"},

	{"ADDA CH34 Pwayback", NUWW, "aud_3wd_dac_cwk"},
	{"ADDA CH34 Pwayback", NUWW, "aud_3wd_dac_pwedis_cwk"},

	{"ADDA Captuwe Enabwe", NUWW, "aud_adc_cwk"},
	{"ADDA CH34 Captuwe Enabwe", NUWW, "aud_adda6_adc_cwk"},
};

/* dai ops */
static int mtk_dai_adda_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);
	int id = dai->id;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		unsigned int dw_swc2_con0 = 0;
		unsigned int dw_swc2_con1 = 0;

		/* set sampwing wate */
		dw_swc2_con0 = adda_dw_wate_twansfowm(afe, wate) <<
			       DW_2_INPUT_MODE_CTW_SFT;

		/* set output mode, UP_SAMPWING_WATE_X8 */
		dw_swc2_con0 |= (0x3 << DW_2_OUTPUT_SEW_CTW_SFT);

		/* tuwn off mute function */
		dw_swc2_con0 |= (0x01 << DW_2_MUTE_CH2_OFF_CTW_PWE_SFT);
		dw_swc2_con0 |= (0x01 << DW_2_MUTE_CH1_OFF_CTW_PWE_SFT);

		/* set voice input data if input sampwe wate is 8k ow 16k */
		if (wate == 8000 || wate == 16000)
			dw_swc2_con0 |= 0x01 << DW_2_VOICE_MODE_CTW_PWE_SFT;

		/* SA suggest appwy -0.3db to audio/speech path */
		dw_swc2_con1 = MTK_AFE_ADDA_DW_GAIN_NOWMAW <<
			       DW_2_GAIN_CTW_PWE_SFT;

		/* tuwn on down-wink gain */
		dw_swc2_con0 |= (0x01 << DW_2_GAIN_ON_CTW_PWE_SFT);

		if (id == MT8192_DAI_ADDA) {
			/* cwean pwedistowtion */
			wegmap_wwite(afe->wegmap, AFE_ADDA_PWEDIS_CON0, 0);
			wegmap_wwite(afe->wegmap, AFE_ADDA_PWEDIS_CON1, 0);

			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_DW_SWC2_CON0, dw_swc2_con0);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_DW_SWC2_CON1, dw_swc2_con1);

			/* set sdm gain */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_DW_SDM_DCCOMP_CON,
					   ATTGAIN_CTW_MASK_SFT,
					   AUDIO_SDM_WEVEW_NOWMAW <<
					   ATTGAIN_CTW_SFT);

			/* 2nd sdm */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_DW_SDM_DCCOMP_CON,
					   USE_3WD_SDM_MASK_SFT,
					   AUDIO_SDM_2ND << USE_3WD_SDM_SFT);

			/* sdm auto weset */
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_DW_SDM_AUTO_WESET_CON,
				     SDM_AUTO_WESET_THWESHOWD);
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_DW_SDM_AUTO_WESET_CON,
					   ADDA_SDM_AUTO_WESET_ONOFF_MASK_SFT,
					   0x1 << ADDA_SDM_AUTO_WESET_ONOFF_SFT);
		} ewse {
			/* cwean pwedistowtion */
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_3WD_DAC_PWEDIS_CON0, 0);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_3WD_DAC_PWEDIS_CON1, 0);

			wegmap_wwite(afe->wegmap, AFE_ADDA_3WD_DAC_DW_SWC2_CON0,
				     dw_swc2_con0);
			wegmap_wwite(afe->wegmap, AFE_ADDA_3WD_DAC_DW_SWC2_CON1,
				     dw_swc2_con1);

			/* set sdm gain */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_3WD_DAC_DW_SDM_DCCOMP_CON,
					   ATTGAIN_CTW_MASK_SFT,
					   AUDIO_SDM_WEVEW_NOWMAW <<
					   ATTGAIN_CTW_SFT);

			/* 2nd sdm */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_3WD_DAC_DW_SDM_DCCOMP_CON,
					   USE_3WD_SDM_MASK_SFT,
					   AUDIO_SDM_2ND << USE_3WD_SDM_SFT);

			/* sdm auto weset */
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_3WD_DAC_DW_SDM_AUTO_WESET_CON,
				     SDM_AUTO_WESET_THWESHOWD);
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_3WD_DAC_DW_SDM_AUTO_WESET_CON,
					   ADDA_3WD_DAC_SDM_AUTO_WESET_ONOFF_MASK_SFT,
					   0x1 << ADDA_3WD_DAC_SDM_AUTO_WESET_ONOFF_SFT);
		}
	} ewse {
		unsigned int voice_mode = 0;
		unsigned int uw_swc_con0 = 0;	/* defauwt vawue */

		voice_mode = adda_uw_wate_twansfowm(afe, wate);

		uw_swc_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* enabwe iiw */
		uw_swc_con0 |= (1 << UW_IIW_ON_TMP_CTW_SFT) &
			       UW_IIW_ON_TMP_CTW_MASK_SFT;
		uw_swc_con0 |= (UW_IIW_SW << UW_IIWMODE_CTW_SFT) &
			       UW_IIWMODE_CTW_MASK_SFT;

		switch (id) {
		case MT8192_DAI_ADDA:
		case MT8192_DAI_AP_DMIC:
			/* 35Hz @ 48k */
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_02_01, 0x00000000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_04_03, 0x00003FB8);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_06_05, 0x3FB80000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_08_07, 0x3FB80000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_10_09, 0x0000C048);

			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_UW_SWC_CON0, uw_swc_con0);

			/* Using Intewnaw ADC */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_TOP_CON0,
					   0x1 << 0,
					   0x0 << 0);

			/* mtkaif_wxif_data_mode = 0, amic */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_MTKAIF_WX_CFG0,
					   0x1 << 0,
					   0x0 << 0);
			bweak;
		case MT8192_DAI_ADDA_CH34:
		case MT8192_DAI_AP_DMIC_CH34:
			/* 35Hz @ 48k */
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA6_IIW_COEF_02_01, 0x00000000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA6_IIW_COEF_04_03, 0x00003FB8);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA6_IIW_COEF_06_05, 0x3FB80000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA6_IIW_COEF_08_07, 0x3FB80000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA6_IIW_COEF_10_09, 0x0000C048);

			wegmap_wwite(afe->wegmap,
				     AFE_ADDA6_UW_SWC_CON0, uw_swc_con0);

			/* Using Intewnaw ADC */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA6_TOP_CON0,
					   0x1 << 0,
					   0x0 << 0);

			/* mtkaif_wxif_data_mode = 0, amic */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA6_MTKAIF_WX_CFG0,
					   0x1 << 0,
					   0x0 << 0);
			bweak;
		defauwt:
			bweak;
		}

		/* ap dmic */
		switch (id) {
		case MT8192_DAI_AP_DMIC:
		case MT8192_DAI_AP_DMIC_CH34:
			mtk_adda_uw_swc_dmic(afe, id);
			bweak;
		defauwt:
			bweak;
		}
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
		.id = MT8192_DAI_ADDA,
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
	{
		.name = "ADDA_CH34",
		.id = MT8192_DAI_ADDA_CH34,
		.pwayback = {
			.stweam_name = "ADDA CH34 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_PWAYBACK_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "ADDA CH34 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_CAPTUWE_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.ops = &mtk_dai_adda_ops,
	},
	{
		.name = "AP_DMIC",
		.id = MT8192_DAI_AP_DMIC,
		.captuwe = {
			.stweam_name = "AP DMIC Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_CAPTUWE_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.ops = &mtk_dai_adda_ops,
	},
	{
		.name = "AP_DMIC_CH34",
		.id = MT8192_DAI_AP_DMIC_CH34,
		.captuwe = {
			.stweam_name = "AP DMIC CH34 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_CAPTUWE_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.ops = &mtk_dai_adda_ops,
	},
};

int mt8192_dai_adda_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

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

	/* ap dmic pwiv shawe with adda */
	afe_pwiv->dai_pwiv[MT8192_DAI_AP_DMIC] =
		afe_pwiv->dai_pwiv[MT8192_DAI_ADDA];
	afe_pwiv->dai_pwiv[MT8192_DAI_AP_DMIC_CH34] =
		afe_pwiv->dai_pwiv[MT8192_DAI_ADDA_CH34];

	wetuwn 0;
}
