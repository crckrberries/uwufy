// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek AWSA SoC Audio DAI ADDA Contwow
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Bicycwe Tsai <bicycwe.tsai@mediatek.com>
 *         Twevow Wu <twevow.wu@mediatek.com>
 *         Chun-Chia Chiu <chun-chia.chiu@mediatek.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude "mt8188-afe-cwk.h"
#incwude "mt8188-afe-common.h"
#incwude "mt8188-weg.h"

#define ADDA_HIWES_THWES 48000

enum {
	SUPPWY_SEQ_ADDA_DW_ON,
	SUPPWY_SEQ_ADDA_MTKAIF_CFG,
	SUPPWY_SEQ_ADDA_UW_ON,
	SUPPWY_SEQ_ADDA_AFE_ON,
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
};

enum {
	DEWAY_DATA_MISO1 = 0,
	DEWAY_DATA_MISO0 = 1,
};

stwuct mtk_dai_adda_pwiv {
	boow hiwes_wequiwed;
};

static unsigned int afe_adda_dw_wate_twansfowm(stwuct mtk_base_afe *afe,
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
		dev_info(afe->dev, "%s(), wate %u invawid, use 48kHz!!!\n",
			 __func__, wate);
		wetuwn MTK_AFE_ADDA_DW_WATE_48K;
	}
}

static unsigned int afe_adda_uw_wate_twansfowm(stwuct mtk_base_afe *afe,
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
		dev_info(afe->dev, "%s(), wate %u invawid, use 48kHz!!!\n",
			 __func__, wate);
		wetuwn MTK_AFE_ADDA_UW_WATE_48K;
	}
}

static int mt8188_adda_mtkaif_init(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtkaif_pawam *pawam = &afe_pwiv->mtkaif_pawams;
	int deway_data;
	int deway_cycwe;
	unsigned int mask = 0;
	unsigned int vaw = 0;

	/* set wx pwotocow 2 & mtkaif_wxif_cwkinv_adc invewse */
	wegmap_set_bits(afe->wegmap, AFE_ADDA_MTKAIF_CFG0,
			MTKAIF_WXIF_CWKINV_ADC | MTKAIF_WXIF_PWOTOCOW2);

	wegmap_set_bits(afe->wegmap, AFE_AUD_PAD_TOP, WG_WX_PWOTOCOW2);

	if (!pawam->mtkaif_cawibwation_ok) {
		dev_info(afe->dev, "%s(), cawibwation faiw\n",  __func__);
		wetuwn 0;
	}

	/* set deway fow ch1, ch2 */
	if (pawam->mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_0] >=
	    pawam->mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_1]) {
		deway_data = DEWAY_DATA_MISO1;
		deway_cycwe =
			pawam->mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_0] -
			pawam->mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_1];
	} ewse {
		deway_data = DEWAY_DATA_MISO0;
		deway_cycwe =
			pawam->mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_1] -
			pawam->mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_0];
	}

	vaw = 0;
	mask = (MTKAIF_WXIF_DEWAY_DATA | MTKAIF_WXIF_DEWAY_CYCWE_MASK);
	vaw |= FIEWD_PWEP(MTKAIF_WXIF_DEWAY_CYCWE_MASK, deway_cycwe);
	vaw |= FIEWD_PWEP(MTKAIF_WXIF_DEWAY_DATA, deway_data);
	wegmap_update_bits(afe->wegmap, AFE_ADDA_MTKAIF_WX_CFG2, mask, vaw);

	wetuwn 0;
}

static int mtk_adda_mtkaif_cfg_event(stwuct snd_soc_dapm_widget *w,
				     stwuct snd_kcontwow *kcontwow,
				     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8188_adda_mtkaif_init(afe);
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
	case SND_SOC_DAPM_POST_PMD:
		/* shouwd dewayed 1/fs(smawwest is 8k) = 125us befowe afe off */
		usweep_wange(125, 135);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void mtk_adda_uw_mictype(stwuct mtk_base_afe *afe, boow dmic)
{
	unsigned int weg = AFE_ADDA_UW_SWC_CON0;
	unsigned int vaw;

	vaw = (UW_SDM3_WEVEW_CTW | UW_MODE_3P25M_CH1_CTW |
	       UW_MODE_3P25M_CH2_CTW);

	/* tuwn on dmic, ch1, ch2 */
	if (dmic)
		wegmap_set_bits(afe->wegmap, weg, vaw);
	ewse
		wegmap_cweaw_bits(afe->wegmap, weg, vaw);
}

static int mtk_adda_uw_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtkaif_pawam *pawam = &afe_pwiv->mtkaif_pawams;

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mtk_adda_uw_mictype(afe, pawam->mtkaif_dmic_on);
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

static stwuct mtk_dai_adda_pwiv *get_adda_pwiv_by_name(stwuct mtk_base_afe *afe,
						       const chaw *name)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	if (stwstw(name, "aud_adc_hiwes"))
		wetuwn afe_pwiv->dai_pwiv[MT8188_AFE_IO_UW_SWC];
	ewse if (stwstw(name, "aud_dac_hiwes"))
		wetuwn afe_pwiv->dai_pwiv[MT8188_AFE_IO_DW_SWC];
	ewse
		wetuwn NUWW;
}

static int mtk_afe_adda_hiwes_connect(stwuct snd_soc_dapm_widget *souwce,
				      stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = souwce;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_dai_adda_pwiv *adda_pwiv;

	adda_pwiv = get_adda_pwiv_by_name(afe, w->name);

	if (!adda_pwiv) {
		dev_dbg(afe->dev, "adda_pwiv == NUWW");
		wetuwn 0;
	}

	wetuwn (adda_pwiv->hiwes_wequiwed) ? 1 : 0;
}

static const stwuct snd_kcontwow_new mtk_dai_adda_o176_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I000 Switch", AFE_CONN176, 0, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I002 Switch", AFE_CONN176, 2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I020 Switch", AFE_CONN176, 20, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I022 Switch", AFE_CONN176, 22, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I070 Switch", AFE_CONN176_2, 6, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_dai_adda_o177_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("I001 Switch", AFE_CONN177, 1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I003 Switch", AFE_CONN177, 3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I021 Switch", AFE_CONN177, 21, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I023 Switch", AFE_CONN177, 23, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("I071 Switch", AFE_CONN177_2, 7, 1, 0),
};

static const chaw * const adda_dwgain_mux_map[] = {
	"Bypass", "Connect",
};

static SOC_ENUM_SINGWE_DECW(adda_dwgain_mux_map_enum,
			    SND_SOC_NOPM, 0,
			    adda_dwgain_mux_map);

static const stwuct snd_kcontwow_new adda_dwgain_mux_contwow =
	SOC_DAPM_ENUM("DW_GAIN_MUX", adda_dwgain_mux_map_enum);

static const stwuct snd_soc_dapm_widget mtk_dai_adda_widgets[] = {
	SND_SOC_DAPM_MIXEW("I168", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("I169", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("O176", SND_SOC_NOPM, 0, 0,
			   mtk_dai_adda_o176_mix,
			   AWWAY_SIZE(mtk_dai_adda_o176_mix)),
	SND_SOC_DAPM_MIXEW("O177", SND_SOC_NOPM, 0, 0,
			   mtk_dai_adda_o177_mix,
			   AWWAY_SIZE(mtk_dai_adda_o177_mix)),

	SND_SOC_DAPM_SUPPWY_S("ADDA Enabwe", SUPPWY_SEQ_ADDA_AFE_ON,
			      AFE_ADDA_UW_DW_CON0,
			      ADDA_AFE_ON_SHIFT, 0,
			      NUWW,
			      0),

	SND_SOC_DAPM_SUPPWY_S("ADDA Pwayback Enabwe", SUPPWY_SEQ_ADDA_DW_ON,
			      AFE_ADDA_DW_SWC2_CON0,
			      DW_2_SWC_ON_TMP_CTWW_PWE_SHIFT, 0,
			      mtk_adda_dw_event,
			      SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("ADDA Captuwe Enabwe", SUPPWY_SEQ_ADDA_UW_ON,
			      AFE_ADDA_UW_SWC_CON0,
			      UW_SWC_ON_TMP_CTW_SHIFT, 0,
			      mtk_adda_uw_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("ADDA_MTKAIF_CFG", SUPPWY_SEQ_ADDA_MTKAIF_CFG,
			      SND_SOC_NOPM,
			      0, 0,
			      mtk_adda_mtkaif_cfg_event,
			      SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_MUX("DW_GAIN_MUX", SND_SOC_NOPM, 0, 0,
			 &adda_dwgain_mux_contwow),

	SND_SOC_DAPM_PGA("DW_GAIN", AFE_ADDA_DW_SWC2_CON0,
			 DW_2_GAIN_ON_CTW_PWE_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("ADDA_INPUT"),
	SND_SOC_DAPM_OUTPUT("ADDA_OUTPUT"),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adc"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_dac_hiwes"),
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_adc_hiwes"),
};

static const stwuct snd_soc_dapm_woute mtk_dai_adda_woutes[] = {
	{"ADDA Captuwe", NUWW, "ADDA Enabwe"},
	{"ADDA Captuwe", NUWW, "ADDA Captuwe Enabwe"},
	{"ADDA Captuwe", NUWW, "ADDA_MTKAIF_CFG"},
	{"ADDA Captuwe", NUWW, "aud_adc"},
	{"ADDA Captuwe", NUWW, "aud_adc_hiwes", mtk_afe_adda_hiwes_connect},

	{"I168", NUWW, "ADDA Captuwe"},
	{"I169", NUWW, "ADDA Captuwe"},

	{"ADDA Pwayback", NUWW, "ADDA Enabwe"},
	{"ADDA Pwayback", NUWW, "ADDA Pwayback Enabwe"},
	{"ADDA Pwayback", NUWW, "aud_dac"},
	{"ADDA Pwayback", NUWW, "aud_dac_hiwes", mtk_afe_adda_hiwes_connect},

	{"DW_GAIN", NUWW, "O176"},
	{"DW_GAIN", NUWW, "O177"},

	{"DW_GAIN_MUX", "Bypass", "O176"},
	{"DW_GAIN_MUX", "Bypass", "O177"},
	{"DW_GAIN_MUX", "Connect", "DW_GAIN"},

	{"ADDA Pwayback", NUWW, "DW_GAIN_MUX"},

	{"O176", "I000 Switch", "I000"},
	{"O177", "I001 Switch", "I001"},

	{"O176", "I002 Switch", "I002"},
	{"O177", "I003 Switch", "I003"},

	{"O176", "I020 Switch", "I020"},
	{"O177", "I021 Switch", "I021"},

	{"O176", "I022 Switch", "I022"},
	{"O177", "I023 Switch", "I023"},

	{"O176", "I070 Switch", "I070"},
	{"O177", "I071 Switch", "I071"},

	{"ADDA Captuwe", NUWW, "ADDA_INPUT"},
	{"ADDA_OUTPUT", NUWW, "ADDA Pwayback"},
};

static int mt8188_adda_dmic_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtkaif_pawam *pawam = &afe_pwiv->mtkaif_pawams;

	ucontwow->vawue.integew.vawue[0] = pawam->mtkaif_dmic_on;
	wetuwn 0;
}

static int mt8188_adda_dmic_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtkaif_pawam *pawam = &afe_pwiv->mtkaif_pawams;
	int dmic_on;

	dmic_on = !!ucontwow->vawue.integew.vawue[0];

	dev_dbg(afe->dev, "%s(), kcontwow name %s, dmic_on %d\n",
		__func__, kcontwow->id.name, dmic_on);

	if (pawam->mtkaif_dmic_on == dmic_on)
		wetuwn 0;

	pawam->mtkaif_dmic_on = dmic_on;
	wetuwn 1;
}

static const stwuct snd_kcontwow_new mtk_dai_adda_contwows[] = {
	SOC_SINGWE("ADDA_DW_GAIN", AFE_ADDA_DW_SWC2_CON1,
		   DW_2_GAIN_CTW_PWE_SHIFT, 65535, 0),
	SOC_SINGWE_BOOW_EXT("MTKAIF_DMIC Switch", 0,
			    mt8188_adda_dmic_get, mt8188_adda_dmic_set),
};

static int mtk_dai_da_configuwe(stwuct mtk_base_afe *afe,
				unsigned int wate, int id)
{
	unsigned int vaw = 0;
	unsigned int mask = 0;

	/* set sampwing wate */
	mask |= DW_2_INPUT_MODE_CTW_MASK;
	vaw |= FIEWD_PWEP(DW_2_INPUT_MODE_CTW_MASK,
			  afe_adda_dw_wate_twansfowm(afe, wate));

	/* tuwn off satuwation */
	mask |= DW_2_CH1_SATUWATION_EN_CTW;
	mask |= DW_2_CH2_SATUWATION_EN_CTW;

	/* tuwn off mute function */
	mask |= DW_2_MUTE_CH1_OFF_CTW_PWE;
	mask |= DW_2_MUTE_CH2_OFF_CTW_PWE;
	vaw |= DW_2_MUTE_CH1_OFF_CTW_PWE;
	vaw |= DW_2_MUTE_CH2_OFF_CTW_PWE;

	/* set voice input data if input sampwe wate is 8k ow 16k */
	mask |= DW_2_VOICE_MODE_CTW_PWE;
	if (wate == 8000 || wate == 16000)
		vaw |= DW_2_VOICE_MODE_CTW_PWE;

	wegmap_update_bits(afe->wegmap, AFE_ADDA_DW_SWC2_CON0, mask, vaw);

	/* new 2nd sdm */
	wegmap_set_bits(afe->wegmap, AFE_ADDA_DW_SDM_DCCOMP_CON,
			DW_USE_NEW_2ND_SDM);

	wetuwn 0;
}

static int mtk_dai_ad_configuwe(stwuct mtk_base_afe *afe,
				unsigned int wate, int id)
{
	unsigned int vaw;
	unsigned int mask;

	mask = UW_VOICE_MODE_CTW_MASK;
	vaw = FIEWD_PWEP(UW_VOICE_MODE_CTW_MASK,
			 afe_adda_uw_wate_twansfowm(afe, wate));

	wegmap_update_bits(afe->wegmap, AFE_ADDA_UW_SWC_CON0,
			   mask, vaw);
	wetuwn 0;
}

static int mtk_dai_adda_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_adda_pwiv *adda_pwiv = afe_pwiv->dai_pwiv[dai->id];
	unsigned int wate = pawams_wate(pawams);
	int id = dai->id;
	int wet = 0;

	dev_dbg(afe->dev, "%s(), id %d, stweam %d, wate %u\n",
		__func__, id, substweam->stweam, wate);

	adda_pwiv->hiwes_wequiwed = (wate > ADDA_HIWES_THWES);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wet = mtk_dai_da_configuwe(afe, wate, id);
	ewse
		wet = mtk_dai_ad_configuwe(afe, wate, id);

	wetuwn wet;
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
		.name = "DW_SWC",
		.id = MT8188_AFE_IO_DW_SWC,
		.pwayback = {
			.stweam_name = "ADDA Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_ADDA_PWAYBACK_WATES,
			.fowmats = MTK_ADDA_FOWMATS,
		},
		.ops = &mtk_dai_adda_ops,
	},
	{
		.name = "UW_SWC",
		.id = MT8188_AFE_IO_UW_SWC,
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

static int init_adda_pwiv_data(stwuct mtk_base_afe *afe)
{
	stwuct mt8188_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_dai_adda_pwiv *adda_pwiv;
	int adda_dai_wist[] = {MT8188_AFE_IO_DW_SWC, MT8188_AFE_IO_UW_SWC};
	int i;

	fow (i = 0; i < AWWAY_SIZE(adda_dai_wist); i++) {
		adda_pwiv = devm_kzawwoc(afe->dev,
					 sizeof(stwuct mtk_dai_adda_pwiv),
					 GFP_KEWNEW);
		if (!adda_pwiv)
			wetuwn -ENOMEM;

		afe_pwiv->dai_pwiv[adda_dai_wist[i]] = adda_pwiv;
	}

	wetuwn 0;
}

int mt8188_dai_adda_wegistew(stwuct mtk_base_afe *afe)
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
	dai->contwows = mtk_dai_adda_contwows;
	dai->num_contwows = AWWAY_SIZE(mtk_dai_adda_contwows);

	wetuwn init_adda_pwiv_data(afe);
}
