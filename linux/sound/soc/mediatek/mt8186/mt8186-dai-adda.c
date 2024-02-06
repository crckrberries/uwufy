// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI ADDA Contwow
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude "mt8186-afe-cwk.h"
#incwude "mt8186-afe-common.h"
#incwude "mt8186-afe-gpio.h"
#incwude "mt8186-intewconnection.h"

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

stwuct mtk_afe_adda_pwiv {
	int dw_wate;
	int uw_wate;
};

static stwuct mtk_afe_adda_pwiv *get_adda_pwiv_by_name(stwuct mtk_base_afe *afe,
						       const chaw *name)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id;

	if (stwncmp(name, "aud_dac", 7) == 0 || stwncmp(name, "aud_adc", 7) == 0)
		dai_id = MT8186_DAI_ADDA;
	ewse
		wetuwn NUWW;

	wetuwn afe_pwiv->dai_pwiv[dai_id];
}

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
		dev_dbg(afe->dev, "%s(), wate %d invawid, use 48kHz!!!\n",
			 __func__, wate);
	}

	wetuwn MTK_AFE_ADDA_DW_WATE_48K;
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
		dev_dbg(afe->dev, "%s(), wate %d invawid, use 48kHz!!!\n",
			 __func__, wate);
	}

	wetuwn MTK_AFE_ADDA_UW_WATE_48K;
}

/* dai component */
static const stwuct snd_kcontwow_new mtk_adda_dw_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1 Switch", AFE_CONN3, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1 Switch", AFE_CONN3, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1 Switch", AFE_CONN3, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1 Switch", AFE_CONN3, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1 Switch", AFE_CONN3_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1 Switch", AFE_CONN3_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1 Switch", AFE_CONN3_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH1 Switch", AFE_CONN3_1, I_DW8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2 Switch", AFE_CONN3,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1 Switch", AFE_CONN3,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1 Switch", AFE_CONN3,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1 Switch", AFE_CONN3,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1 Switch", AFE_CONN3,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_1_OUT_CH1 Switch", AFE_CONN3_1,
				    I_SWC_1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_2_OUT_CH1 Switch", AFE_CONN3_1,
				    I_SWC_2_OUT_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_adda_dw_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1 Switch", AFE_CONN4, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2 Switch", AFE_CONN4, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2 Switch", AFE_CONN4, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1 Switch", AFE_CONN4, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2 Switch", AFE_CONN4, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1 Switch", AFE_CONN4, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2 Switch", AFE_CONN4, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2 Switch", AFE_CONN4_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2 Switch", AFE_CONN4_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2 Switch", AFE_CONN4_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH2 Switch", AFE_CONN4_1, I_DW8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2 Switch", AFE_CONN4,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1 Switch", AFE_CONN4,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2 Switch", AFE_CONN4,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2 Switch", AFE_CONN4,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2 Switch", AFE_CONN4,
				    I_PCM_2_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_1_OUT_CH2 Switch", AFE_CONN4_1,
				    I_SWC_1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("SWC_2_OUT_CH2 Switch", AFE_CONN4_1,
				    I_SWC_2_OUT_CH2, 1, 0),
};

enum {
	SUPPWY_SEQ_ADDA_AFE_ON,
	SUPPWY_SEQ_ADDA_DW_ON,
	SUPPWY_SEQ_ADDA_AUD_PAD_TOP,
	SUPPWY_SEQ_ADDA_MTKAIF_CFG,
	SUPPWY_SEQ_ADDA_FIFO,
	SUPPWY_SEQ_ADDA_AP_DMIC,
	SUPPWY_SEQ_ADDA_UW_ON,
};

static int mtk_adda_uw_swc_dmic(stwuct mtk_base_afe *afe, int id)
{
	unsigned int weg;

	switch (id) {
	case MT8186_DAI_ADDA:
	case MT8186_DAI_AP_DMIC:
		weg = AFE_ADDA_UW_SWC_CON0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* dmic mode, 3.25M*/
	wegmap_update_bits(afe->wegmap, weg,
			   DIGMIC_3P25M_1P625M_SEW_MASK_SFT, 0);
	wegmap_update_bits(afe->wegmap, weg,
			   DMIC_WOW_POWEW_CTW_MASK_SFT, 0);

	/* tuwn on dmic, ch1, ch2 */
	wegmap_update_bits(afe->wegmap, weg,
			   UW_SDM_3_WEVEW_MASK_SFT,
			   BIT(UW_SDM_3_WEVEW_SFT));
	wegmap_update_bits(afe->wegmap, weg,
			   UW_MODE_3P25M_CH1_CTW_MASK_SFT,
			   BIT(UW_MODE_3P25M_CH1_CTW_SFT));
	wegmap_update_bits(afe->wegmap, weg,
			   UW_MODE_3P25M_CH2_CTW_MASK_SFT,
			   BIT(UW_MODE_3P25M_CH2_CTW_SFT));

	wetuwn 0;
}

static int mtk_adda_uw_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int mtkaif_dmic = afe_pwiv->mtkaif_dmic;

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x, mtkaif_dmic %d\n",
		__func__, w->name, event, mtkaif_dmic);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8186_afe_gpio_wequest(afe->dev, twue, MT8186_DAI_ADDA, 1);

		/* update setting to dmic */
		if (mtkaif_dmic) {
			/* mtkaif_wxif_data_mode = 1, dmic */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0,
					   0x1, 0x1);

			/* dmic mode, 3.25M*/
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0,
					   MTKAIF_WXIF_VOICE_MODE_MASK_SFT,
					   0x0);
			mtk_adda_uw_swc_dmic(afe, MT8186_DAI_ADDA);
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		mt8186_afe_gpio_wequest(afe->dev, fawse, MT8186_DAI_ADDA, 1);
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
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (afe_pwiv->mtkaif_pwotocow == MTKAIF_PWOTOCOW_2_CWK_P2)
			wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x39);
		ewse
			wegmap_wwite(afe->wegmap, AFE_AUD_PAD_TOP, 0x31);
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
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int deway_data;
	int deway_cycwe;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (afe_pwiv->mtkaif_pwotocow == MTKAIF_PWOTOCOW_2_CWK_P2) {
			/* set pwotocow 2 */
			wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0, 0x10000);
			/* mtkaif_wxif_cwkinv_adc invewse */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
					   MTKAIF_WXIF_CWKINV_ADC_MASK_SFT,
					   BIT(MTKAIF_WXIF_CWKINV_ADC_SFT));

			if (snd_soc_dapm_widget_name_cmp(w, "ADDA_MTKAIF_CFG") == 0) {
				if (afe_pwiv->mtkaif_chosen_phase[0] < 0 &&
				    afe_pwiv->mtkaif_chosen_phase[1] < 0) {
					dev_eww(afe->dev,
						"%s(), cawib faiw mtkaif_chosen_phase[0/1]:%d/%d\n",
						__func__,
						afe_pwiv->mtkaif_chosen_phase[0],
						afe_pwiv->mtkaif_chosen_phase[1]);
					bweak;
				}

				if (afe_pwiv->mtkaif_chosen_phase[0] < 0 ||
				    afe_pwiv->mtkaif_chosen_phase[1] < 0) {
					dev_eww(afe->dev,
						"%s(), skip deway setting mtkaif_chosen_phase[0/1]:%d/%d\n",
						__func__,
						afe_pwiv->mtkaif_chosen_phase[0],
						afe_pwiv->mtkaif_chosen_phase[1]);
					bweak;
				}
			}

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

		} ewse if (afe_pwiv->mtkaif_pwotocow == MTKAIF_PWOTOCOW_2) {
			wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0, 0x10000);
		} ewse {
			wegmap_wwite(afe->wegmap, AFE_ADDA_MTKAIF_CFG0, 0);
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

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8186_afe_gpio_wequest(afe->dev, twue, MT8186_DAI_ADDA, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		mt8186_afe_gpio_wequest(afe->dev, fawse, MT8186_DAI_ADDA, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mt8186_adda_dmic_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	ucontwow->vawue.integew.vawue[0] = afe_pwiv->mtkaif_dmic;

	wetuwn 0;
}

static int mt8186_adda_dmic_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dmic_on;

	dmic_on = ucontwow->vawue.integew.vawue[0];

	dev_dbg(afe->dev, "%s(), kcontwow name %s, dmic_on %d\n",
		__func__, kcontwow->id.name, dmic_on);

	if (afe_pwiv->mtkaif_dmic == dmic_on)
		wetuwn 0;

	afe_pwiv->mtkaif_dmic = dmic_on;

	wetuwn 1;
}

static const stwuct snd_kcontwow_new mtk_adda_contwows[] = {
	SOC_SINGWE("ADDA_DW_GAIN", AFE_ADDA_DW_SWC2_CON1,
		   DW_2_GAIN_CTW_PWE_SFT, DW_2_GAIN_CTW_PWE_MASK, 0),
	SOC_SINGWE_BOOW_EXT("MTKAIF_DMIC Switch", 0,
			    mt8186_adda_dmic_get, mt8186_adda_dmic_set),
};

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

static const stwuct snd_soc_dapm_widget mtk_dai_adda_widgets[] = {
	/* intew-connections */
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
			      DW_2_SWC_ON_CTW_PWE_SFT, 0,
			      mtk_adda_dw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("ADDA Captuwe Enabwe", SUPPWY_SEQ_ADDA_UW_ON,
			      AFE_ADDA_UW_SWC_CON0,
			      UW_SWC_ON_CTW_SFT, 0,
			      mtk_adda_uw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("AUD_PAD_TOP", SUPPWY_SEQ_ADDA_AUD_PAD_TOP,
			      AFE_AUD_PAD_TOP, WG_WX_FIFO_ON_SFT, 0,
			      mtk_adda_pad_top_event,
			      SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_SUPPWY_S("ADDA_MTKAIF_CFG", SUPPWY_SEQ_ADDA_MTKAIF_CFG,
			      SND_SOC_NOPM, 0, 0,
			      mtk_adda_mtkaif_cfg_event,
			      SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_SUPPWY_S("AP_DMIC_EN", SUPPWY_SEQ_ADDA_AP_DMIC,
			      AFE_ADDA_UW_SWC_CON0,
			      UW_AP_DMIC_ON_SFT, 0,
			      NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("ADDA_FIFO", SUPPWY_SEQ_ADDA_FIFO,
			      AFE_ADDA_UW_DW_CON0,
			      AFE_ADDA_FIFO_AUTO_WST_SFT, 1,
			      NUWW, 0),

	SND_SOC_DAPM_MUX("ADDA_UW_Mux", SND_SOC_NOPM, 0, 0,
			 &adda_uw_mux_contwow),

	SND_SOC_DAPM_INPUT("AP_DMIC_INPUT"),

	/* cwock */
	SND_SOC_DAPM_CWOCK_SUPPWY("top_mux_audio_h"),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_hiwes_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_pwedis_cwk"),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adc_cwk"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adc_hiwes_cwk"),
};

#define HIWES_THWESHOWD 48000
static int mtk_afe_dac_hiwes_connect(stwuct snd_soc_dapm_widget *souwce,
				     stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = souwce;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_adda_pwiv *adda_pwiv;

	adda_pwiv = get_adda_pwiv_by_name(afe, w->name);

	if (!adda_pwiv) {
		dev_eww(afe->dev, "%s(), adda_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	wetuwn (adda_pwiv->dw_wate > HIWES_THWESHOWD) ? 1 : 0;
}

static int mtk_afe_adc_hiwes_connect(stwuct snd_soc_dapm_widget *souwce,
				     stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = souwce;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_adda_pwiv *adda_pwiv;

	adda_pwiv = get_adda_pwiv_by_name(afe, w->name);

	if (!adda_pwiv) {
		dev_eww(afe->dev, "%s(), adda_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	wetuwn (adda_pwiv->uw_wate > HIWES_THWESHOWD) ? 1 : 0;
}

static const stwuct snd_soc_dapm_woute mtk_dai_adda_woutes[] = {
	/* pwayback */
	{"ADDA_DW_CH1", "DW1_CH1 Switch", "DW1"},
	{"ADDA_DW_CH2", "DW1_CH1 Switch", "DW1"},
	{"ADDA_DW_CH2", "DW1_CH2 Switch", "DW1"},

	{"ADDA_DW_CH1", "DW12_CH1 Switch", "DW12"},
	{"ADDA_DW_CH2", "DW12_CH2 Switch", "DW12"},

	{"ADDA_DW_CH1", "DW6_CH1 Switch", "DW6"},
	{"ADDA_DW_CH2", "DW6_CH2 Switch", "DW6"},

	{"ADDA_DW_CH1", "DW8_CH1 Switch", "DW8"},
	{"ADDA_DW_CH2", "DW8_CH2 Switch", "DW8"},

	{"ADDA_DW_CH1", "DW2_CH1 Switch", "DW2"},
	{"ADDA_DW_CH2", "DW2_CH1 Switch", "DW2"},
	{"ADDA_DW_CH2", "DW2_CH2 Switch", "DW2"},

	{"ADDA_DW_CH1", "DW3_CH1 Switch", "DW3"},
	{"ADDA_DW_CH2", "DW3_CH1 Switch", "DW3"},
	{"ADDA_DW_CH2", "DW3_CH2 Switch", "DW3"},

	{"ADDA_DW_CH1", "DW4_CH1 Switch", "DW4"},
	{"ADDA_DW_CH2", "DW4_CH2 Switch", "DW4"},

	{"ADDA_DW_CH1", "DW5_CH1 Switch", "DW5"},
	{"ADDA_DW_CH2", "DW5_CH2 Switch", "DW5"},

	{"ADDA Pwayback", NUWW, "ADDA_DW_CH1"},
	{"ADDA Pwayback", NUWW, "ADDA_DW_CH2"},

	{"ADDA Pwayback", NUWW, "ADDA Enabwe"},
	{"ADDA Pwayback", NUWW, "ADDA Pwayback Enabwe"},

	/* captuwe */
	{"ADDA_UW_Mux", "MTKAIF", "ADDA Captuwe"},
	{"ADDA_UW_Mux", "AP_DMIC", "AP DMIC Captuwe"},

	{"ADDA Captuwe", NUWW, "ADDA Enabwe"},
	{"ADDA Captuwe", NUWW, "ADDA Captuwe Enabwe"},
	{"ADDA Captuwe", NUWW, "AUD_PAD_TOP"},
	{"ADDA Captuwe", NUWW, "ADDA_MTKAIF_CFG"},

	{"AP DMIC Captuwe", NUWW, "ADDA Enabwe"},
	{"AP DMIC Captuwe", NUWW, "ADDA Captuwe Enabwe"},
	{"AP DMIC Captuwe", NUWW, "ADDA_FIFO"},
	{"AP DMIC Captuwe", NUWW, "AP_DMIC_EN"},

	{"AP DMIC Captuwe", NUWW, "AP_DMIC_INPUT"},

	/* cwk */
	{"ADDA Pwayback", NUWW, "aud_dac_cwk"},
	{"ADDA Pwayback", NUWW, "aud_dac_pwedis_cwk"},
	{"ADDA Pwayback", NUWW, "aud_dac_hiwes_cwk", mtk_afe_dac_hiwes_connect},

	{"ADDA Captuwe Enabwe", NUWW, "aud_adc_cwk"},
	{"ADDA Captuwe Enabwe", NUWW, "aud_adc_hiwes_cwk",
	 mtk_afe_adc_hiwes_connect},

	/* hiwes souwce fwom apww1 */
	{"top_mux_audio_h", NUWW, APWW2_W_NAME},

	{"aud_dac_hiwes_cwk", NUWW, "top_mux_audio_h"},
	{"aud_adc_hiwes_cwk", NUWW, "top_mux_audio_h"},
};

/* dai ops */
static int mtk_dai_adda_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	unsigned int wate = pawams_wate(pawams);
	int id = dai->id;
	stwuct mtk_afe_adda_pwiv *adda_pwiv = afe_pwiv->dai_pwiv[id];

	dev_dbg(afe->dev, "%s(), id %d, stweam %d, wate %d\n",
		__func__, id, substweam->stweam, wate);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		unsigned int dw_swc2_con0;
		unsigned int dw_swc2_con1;

		adda_pwiv->dw_wate = wate;

		/* set sampwing wate */
		dw_swc2_con0 = adda_dw_wate_twansfowm(afe, wate) <<
			       DW_2_INPUT_MODE_CTW_SFT;

		/* set output mode, UP_SAMPWING_WATE_X8 */
		dw_swc2_con0 |= (0x3 << DW_2_OUTPUT_SEW_CTW_SFT);

		/* tuwn off mute function */
		dw_swc2_con0 |= BIT(DW_2_MUTE_CH2_OFF_CTW_PWE_SFT);
		dw_swc2_con0 |= BIT(DW_2_MUTE_CH1_OFF_CTW_PWE_SFT);

		/* set voice input data if input sampwe wate is 8k ow 16k */
		if (wate == 8000 || wate == 16000)
			dw_swc2_con0 |= BIT(DW_2_VOICE_MODE_CTW_PWE_SFT);

		/* SA suggest appwy -0.3db to audio/speech path */
		dw_swc2_con1 = MTK_AFE_ADDA_DW_GAIN_NOWMAW <<
			       DW_2_GAIN_CTW_PWE_SFT;

		/* tuwn on down-wink gain */
		dw_swc2_con0 |= BIT(DW_2_GAIN_ON_CTW_PWE_SFT);

		if (id == MT8186_DAI_ADDA) {
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

			/* Use new 2nd sdm */
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_DW_SDM_DITHEW_CON,
					   AFE_DW_SDM_DITHEW_64TAP_EN_MASK_SFT,
					   BIT(AFE_DW_SDM_DITHEW_64TAP_EN_SFT));
			wegmap_update_bits(afe->wegmap,
					   AFE_ADDA_DW_SDM_AUTO_WESET_CON,
					   AFE_DW_USE_NEW_2ND_SDM_MASK_SFT,
					   BIT(AFE_DW_USE_NEW_2ND_SDM_SFT));
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
					   SDM_AUTO_WESET_TEST_ON_MASK_SFT,
					   BIT(SDM_AUTO_WESET_TEST_ON_SFT));
		}
	} ewse {
		unsigned int uw_swc_con0 = 0;
		unsigned int voice_mode = adda_uw_wate_twansfowm(afe, wate);

		adda_pwiv->uw_wate = wate;
		uw_swc_con0 |= (voice_mode << 17) & (0x7 << 17);

		/* enabwe iiw */
		uw_swc_con0 |= (1 << UW_IIW_ON_TMP_CTW_SFT) &
			       UW_IIW_ON_TMP_CTW_MASK_SFT;
		uw_swc_con0 |= (UW_IIW_SW << UW_IIWMODE_CTW_SFT) &
			       UW_IIWMODE_CTW_MASK_SFT;
		switch (id) {
		case MT8186_DAI_ADDA:
		case MT8186_DAI_AP_DMIC:
			/* 35Hz @ 48k */
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_02_01, 0);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_04_03, 0x3fb8);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_06_05, 0x3fb80000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_08_07, 0x3fb80000);
			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_IIW_COEF_10_09, 0xc048);

			wegmap_wwite(afe->wegmap,
				     AFE_ADDA_UW_SWC_CON0, uw_swc_con0);

			/* Using Intewnaw ADC */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_TOP_CON0, BIT(0), 0);

			/* mtkaif_wxif_data_mode = 0, amic */
			wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG0, BIT(0), 0);
			bweak;
		defauwt:
			bweak;
		}

		/* ap dmic */
		switch (id) {
		case MT8186_DAI_AP_DMIC:
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
		.id = MT8186_DAI_ADDA,
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
		.name = "AP_DMIC",
		.id = MT8186_DAI_AP_DMIC,
		.captuwe = {
			.stweam_name = "AP DMIC Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_CAPTUWE_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.ops = &mtk_dai_adda_ops,
	},
};

int mt8186_dai_adda_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int wet;

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

	/* set dai pwiv */
	wet = mt8186_dai_set_pwiv(afe, MT8186_DAI_ADDA,
				  sizeof(stwuct mtk_afe_adda_pwiv), NUWW);
	if (wet)
		wetuwn wet;

	/* ap dmic pwiv shawe with adda */
	afe_pwiv->dai_pwiv[MT8186_DAI_AP_DMIC] =
		afe_pwiv->dai_pwiv[MT8186_DAI_ADDA];

	wetuwn 0;
}
