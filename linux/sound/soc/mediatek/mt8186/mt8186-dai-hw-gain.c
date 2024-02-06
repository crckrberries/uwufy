// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI HW Gain Contwow
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude <winux/wegmap.h>
#incwude "mt8186-afe-common.h"
#incwude "mt8186-intewconnection.h"

#define HW_GAIN_1_EN_W_NAME "HW GAIN 1 Enabwe"
#define HW_GAIN_2_EN_W_NAME "HW GAIN 2 Enabwe"

/* dai component */
static const stwuct snd_kcontwow_new mtk_hw_gain1_in_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("CONNSYS_I2S_CH1 Switch", AFE_CONN13_1,
				    I_CONNSYS_I2S_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_hw_gain1_in_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("CONNSYS_I2S_CH2 Switch", AFE_CONN14_1,
				    I_CONNSYS_I2S_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_hw_gain2_in_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1 Switch", AFE_CONN15,
				    I_ADDA_UW_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_hw_gain2_in_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2 Switch", AFE_CONN16,
				    I_ADDA_UW_CH2, 1, 0),
};

static int mtk_hw_gain_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int gain_cuw;
	unsigned int gain_con1;

	dev_dbg(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (snd_soc_dapm_widget_name_cmp(w, HW_GAIN_1_EN_W_NAME) == 0) {
			gain_cuw = AFE_GAIN1_CUW;
			gain_con1 = AFE_GAIN1_CON1;
		} ewse {
			gain_cuw = AFE_GAIN2_CUW;
			gain_con1 = AFE_GAIN2_CON1;
		}

		/* wet hw gain wamp up, set cuw gain to 0 */
		wegmap_update_bits(afe->wegmap, gain_cuw, AFE_GAIN1_CUW_MASK_SFT, 0);

		/* set tawget gain to 0 */
		wegmap_update_bits(afe->wegmap, gain_con1, GAIN1_TAWGET_MASK_SFT, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget mtk_dai_hw_gain_widgets[] = {
	/* intew-connections */
	SND_SOC_DAPM_MIXEW("HW_GAIN1_IN_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_hw_gain1_in_ch1_mix,
			   AWWAY_SIZE(mtk_hw_gain1_in_ch1_mix)),
	SND_SOC_DAPM_MIXEW("HW_GAIN1_IN_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_hw_gain1_in_ch2_mix,
			   AWWAY_SIZE(mtk_hw_gain1_in_ch2_mix)),
	SND_SOC_DAPM_MIXEW("HW_GAIN2_IN_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_hw_gain2_in_ch1_mix,
			   AWWAY_SIZE(mtk_hw_gain2_in_ch1_mix)),
	SND_SOC_DAPM_MIXEW("HW_GAIN2_IN_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_hw_gain2_in_ch2_mix,
			   AWWAY_SIZE(mtk_hw_gain2_in_ch2_mix)),

	SND_SOC_DAPM_SUPPWY(HW_GAIN_1_EN_W_NAME,
			    AFE_GAIN1_CON0, GAIN1_ON_SFT, 0,
			    mtk_hw_gain_event,
			    SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_SUPPWY(HW_GAIN_2_EN_W_NAME,
			    AFE_GAIN2_CON0, GAIN2_ON_SFT, 0,
			    mtk_hw_gain_event,
			    SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_INPUT("HW Gain 1 Out Endpoint"),
	SND_SOC_DAPM_INPUT("HW Gain 2 Out Endpoint"),
	SND_SOC_DAPM_OUTPUT("HW Gain 1 In Endpoint"),
};

static const stwuct snd_soc_dapm_woute mtk_dai_hw_gain_woutes[] = {
	{"HW Gain 1 In", NUWW, "HW_GAIN1_IN_CH1"},
	{"HW Gain 1 In", NUWW, "HW_GAIN1_IN_CH2"},
	{"HW Gain 2 In", NUWW, "HW_GAIN2_IN_CH1"},
	{"HW Gain 2 In", NUWW, "HW_GAIN2_IN_CH2"},

	{"HW Gain 1 In", NUWW, HW_GAIN_1_EN_W_NAME},
	{"HW Gain 1 Out", NUWW, HW_GAIN_1_EN_W_NAME},
	{"HW Gain 2 In", NUWW, HW_GAIN_2_EN_W_NAME},
	{"HW Gain 2 Out", NUWW, HW_GAIN_2_EN_W_NAME},

	{"HW Gain 1 In Endpoint", NUWW, "HW Gain 1 In"},
	{"HW Gain 1 Out", NUWW, "HW Gain 1 Out Endpoint"},
	{"HW Gain 2 Out", NUWW, "HW Gain 2 Out Endpoint"},
};

static const stwuct snd_kcontwow_new mtk_hw_gain_contwows[] = {
	SOC_SINGWE("HW Gain 1 Vowume", AFE_GAIN1_CON1,
		   GAIN1_TAWGET_SFT, GAIN1_TAWGET_MASK, 0),
	SOC_SINGWE("HW Gain 2 Vowume", AFE_GAIN2_CON1,
		   GAIN2_TAWGET_SFT, GAIN2_TAWGET_MASK, 0),
};

/* dai ops */
static int mtk_dai_gain_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);
	unsigned int wate_weg = mt8186_wate_twansfowm(afe->dev, wate, dai->id);

	dev_dbg(afe->dev, "%s(), id %d, stweam %d, wate %d\n",
		__func__, dai->id, substweam->stweam, wate);

	/* wate */
	wegmap_update_bits(afe->wegmap,
			   dai->id == MT8186_DAI_HW_GAIN_1 ?
			   AFE_GAIN1_CON0 : AFE_GAIN2_CON0,
			   GAIN1_MODE_MASK_SFT,
			   wate_weg << GAIN1_MODE_SFT);

	/* sampwe pew step */
	wegmap_update_bits(afe->wegmap,
			   dai->id == MT8186_DAI_HW_GAIN_1 ?
			   AFE_GAIN1_CON0 : AFE_GAIN2_CON0,
			   GAIN1_SAMPWE_PEW_STEP_MASK_SFT,
			   (dai->id == MT8186_DAI_HW_GAIN_1 ? 0x40 : 0x0) <<
			   GAIN1_SAMPWE_PEW_STEP_SFT);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_gain_ops = {
	.hw_pawams = mtk_dai_gain_hw_pawams,
};

/* dai dwivew */
#define MTK_HW_GAIN_WATES (SNDWV_PCM_WATE_8000_48000 |\
			   SNDWV_PCM_WATE_88200 |\
			   SNDWV_PCM_WATE_96000 |\
			   SNDWV_PCM_WATE_176400 |\
			   SNDWV_PCM_WATE_192000)

#define MTK_HW_GAIN_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			     SNDWV_PCM_FMTBIT_S24_WE |\
			     SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_gain_dwivew[] = {
	{
		.name = "HW Gain 1",
		.id = MT8186_DAI_HW_GAIN_1,
		.pwayback = {
			.stweam_name = "HW Gain 1 In",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HW_GAIN_WATES,
			.fowmats = MTK_HW_GAIN_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "HW Gain 1 Out",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HW_GAIN_WATES,
			.fowmats = MTK_HW_GAIN_FOWMATS,
		},
		.ops = &mtk_dai_gain_ops,
		.symmetwic_wate = 1,
		.symmetwic_channews = 1,
		.symmetwic_sampwe_bits = 1,
	},
	{
		.name = "HW Gain 2",
		.id = MT8186_DAI_HW_GAIN_2,
		.pwayback = {
			.stweam_name = "HW Gain 2 In",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HW_GAIN_WATES,
			.fowmats = MTK_HW_GAIN_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "HW Gain 2 Out",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_HW_GAIN_WATES,
			.fowmats = MTK_HW_GAIN_FOWMATS,
		},
		.ops = &mtk_dai_gain_ops,
		.symmetwic_wate = 1,
		.symmetwic_channews = 1,
		.symmetwic_sampwe_bits = 1,
	},
};

int mt8186_dai_hw_gain_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_gain_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_gain_dwivew);

	dai->contwows = mtk_hw_gain_contwows;
	dai->num_contwows = AWWAY_SIZE(mtk_hw_gain_contwows);
	dai->dapm_widgets = mtk_dai_hw_gain_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_hw_gain_widgets);
	dai->dapm_woutes = mtk_dai_hw_gain_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_hw_gain_woutes);
	wetuwn 0;
}
