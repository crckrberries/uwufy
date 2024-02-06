// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI I2S Contwow
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude "mt8186-afe-common.h"
#incwude "mt8186-afe-gpio.h"
#incwude "mt8186-intewconnection.h"

stwuct mtk_afe_pcm_pwiv {
	unsigned int id;
	unsigned int fmt;
	unsigned int bck_invewt;
	unsigned int wck_invewt;
};

enum aud_tx_wch_wpt {
	AUD_TX_WCH_WPT_NO_WEPEAT = 0,
	AUD_TX_WCH_WPT_WEPEAT = 1
};

enum aud_vbt_16k_mode {
	AUD_VBT_16K_MODE_DISABWE = 0,
	AUD_VBT_16K_MODE_ENABWE = 1
};

enum aud_ext_modem {
	AUD_EXT_MODEM_SEWECT_INTEWNAW = 0,
	AUD_EXT_MODEM_SEWECT_EXTEWNAW = 1
};

enum aud_pcm_sync_type {
	/* bck sync wength = 1 */
	AUD_PCM_ONE_BCK_CYCWE_SYNC = 0,
	/* bck sync wength = PCM_INTF_CON1[9:13] */
	AUD_PCM_EXTENDED_BCK_CYCWE_SYNC = 1
};

enum aud_bt_mode {
	AUD_BT_MODE_DUAW_MIC_ON_TX = 0,
	AUD_BT_MODE_SINGWE_MIC_ON_TX = 1
};

enum aud_pcm_afifo_swc {
	/* swave mode & extewnaw modem uses diffewent cwystaw */
	AUD_PCM_AFIFO_ASWC = 0,
	/* swave mode & extewnaw modem uses the same cwystaw */
	AUD_PCM_AFIFO_AFIFO = 1
};

enum aud_pcm_cwock_souwce {
	AUD_PCM_CWOCK_MASTEW_MODE = 0,
	AUD_PCM_CWOCK_SWAVE_MODE = 1
};

enum aud_pcm_wwen {
	AUD_PCM_WWEN_PCM_32_BCK_CYCWES = 0,
	AUD_PCM_WWEN_PCM_64_BCK_CYCWES = 1
};

enum aud_pcm_24bit {
	AUD_PCM_24BIT_PCM_16_BITS = 0,
	AUD_PCM_24BIT_PCM_24_BITS = 1
};

enum aud_pcm_mode {
	AUD_PCM_MODE_PCM_MODE_8K = 0,
	AUD_PCM_MODE_PCM_MODE_16K = 1,
	AUD_PCM_MODE_PCM_MODE_32K = 2,
	AUD_PCM_MODE_PCM_MODE_48K = 3,
};

enum aud_pcm_fmt {
	AUD_PCM_FMT_I2S = 0,
	AUD_PCM_FMT_EIAJ = 1,
	AUD_PCM_FMT_PCM_MODE_A = 2,
	AUD_PCM_FMT_PCM_MODE_B = 3
};

enum aud_bcwk_out_inv {
	AUD_BCWK_OUT_INV_NO_INVEWSE = 0,
	AUD_BCWK_OUT_INV_INVEWSE = 1
};

enum aud_wwcwk_out_inv {
	AUD_WWCWK_OUT_INV_NO_INVEWSE = 0,
	AUD_WWCWK_OUT_INV_INVEWSE = 1
};

enum aud_pcm_en {
	AUD_PCM_EN_DISABWE = 0,
	AUD_PCM_EN_ENABWE = 1
};

/* dai component */
static const stwuct snd_kcontwow_new mtk_pcm_1_pwayback_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1 Switch", AFE_CONN7,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1 Switch", AFE_CONN7,
				    I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1 Switch", AFE_CONN7_1,
				    I_DW4_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_pcm_1_pwayback_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2 Switch", AFE_CONN8,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2 Switch", AFE_CONN8,
				    I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2 Switch", AFE_CONN8_1,
				    I_DW4_CH2, 1, 0),
};

static int mtk_pcm_en_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow,
			    int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	dev_dbg(afe->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8186_afe_gpio_wequest(afe->dev, twue, MT8186_DAI_PCM, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		mt8186_afe_gpio_wequest(afe->dev, fawse, MT8186_DAI_PCM, 0);
		bweak;
	}

	wetuwn 0;
}

/* pcm in/out wpbk */
static const chaw * const pcm_wpbk_mux_map[] = {
	"Nowmaw", "Wpbk",
};

static int pcm_wpbk_mux_map_vawue[] = {
	0, 1,
};

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(pcm_in_wpbk_mux_map_enum,
					      PCM_INTF_CON1,
					      PCM_I2S_PCM_WOOPBACK_SFT,
					      1,
					      pcm_wpbk_mux_map,
					      pcm_wpbk_mux_map_vawue);

static const stwuct snd_kcontwow_new pcm_in_wpbk_mux_contwow =
	SOC_DAPM_ENUM("PCM In Wpbk Sewect", pcm_in_wpbk_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(pcm_out_wpbk_mux_map_enum,
					      PCM_INTF_CON1,
					      PCM_I2S_PCM_WOOPBACK_SFT,
					      1,
					      pcm_wpbk_mux_map,
					      pcm_wpbk_mux_map_vawue);

static const stwuct snd_kcontwow_new pcm_out_wpbk_mux_contwow =
	SOC_DAPM_ENUM("PCM Out Wpbk Sewect", pcm_out_wpbk_mux_map_enum);

static const stwuct snd_soc_dapm_widget mtk_dai_pcm_widgets[] = {
	/* intew-connections */
	SND_SOC_DAPM_MIXEW("PCM_1_PB_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_1_pwayback_ch1_mix,
			   AWWAY_SIZE(mtk_pcm_1_pwayback_ch1_mix)),
	SND_SOC_DAPM_MIXEW("PCM_1_PB_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_pcm_1_pwayback_ch2_mix,
			   AWWAY_SIZE(mtk_pcm_1_pwayback_ch2_mix)),

	SND_SOC_DAPM_SUPPWY("PCM_1_EN",
			    PCM_INTF_CON1, PCM_EN_SFT, 0,
			    mtk_pcm_en_event,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	/* pcm in wpbk */
	SND_SOC_DAPM_MUX("PCM_In_Wpbk_Mux",
			 SND_SOC_NOPM, 0, 0, &pcm_in_wpbk_mux_contwow),

	/* pcm out wpbk */
	SND_SOC_DAPM_MUX("PCM_Out_Wpbk_Mux",
			 SND_SOC_NOPM, 0, 0, &pcm_out_wpbk_mux_contwow),
};

static const stwuct snd_soc_dapm_woute mtk_dai_pcm_woutes[] = {
	{"PCM 1 Pwayback", NUWW, "PCM_1_PB_CH1"},
	{"PCM 1 Pwayback", NUWW, "PCM_1_PB_CH2"},

	{"PCM 1 Pwayback", NUWW, "PCM_1_EN"},
	{"PCM 1 Captuwe", NUWW, "PCM_1_EN"},

	{"PCM_1_PB_CH1", "DW2_CH1 Switch", "DW2"},
	{"PCM_1_PB_CH2", "DW2_CH2 Switch", "DW2"},

	{"PCM_1_PB_CH1", "DW4_CH1 Switch", "DW4"},
	{"PCM_1_PB_CH2", "DW4_CH2 Switch", "DW4"},

	/* pcm out wpbk */
	{"PCM_Out_Wpbk_Mux", "Wpbk", "PCM 1 Pwayback"},
	{"I2S0", NUWW, "PCM_Out_Wpbk_Mux"},

	/* pcm in wpbk */
	{"PCM_In_Wpbk_Mux", "Wpbk", "PCM 1 Captuwe"},
	{"I2S3", NUWW, "PCM_In_Wpbk_Mux"},
};

/* dai ops */
static int mtk_dai_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct snd_soc_dapm_widget *p = snd_soc_dai_get_widget_pwayback(dai);
	stwuct snd_soc_dapm_widget *c = snd_soc_dai_get_widget_captuwe(dai);
	int pcm_id = dai->id;
	stwuct mtk_afe_pcm_pwiv *pcm_pwiv = afe_pwiv->dai_pwiv[pcm_id];
	unsigned int wate = pawams_wate(pawams);
	unsigned int wate_weg = mt8186_wate_twansfowm(afe->dev, wate, dai->id);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int data_width =
		snd_pcm_fowmat_width(fowmat);
	unsigned int wwen_width =
		snd_pcm_fowmat_physicaw_width(fowmat);
	unsigned int pcm_con = 0;

	dev_dbg(afe->dev, "%s(), id %d, stweam %d, widget active p %d, c %d\n",
		__func__, dai->id, substweam->stweam, p->active, c->active);
	dev_dbg(afe->dev, "%s(), wate %d, wate_weg %d, data_width %d, wwen_width %d\n",
		__func__, wate, wate_weg, data_width, wwen_width);

	if (p->active || c->active)
		wetuwn 0;

	switch (dai->id) {
	case MT8186_DAI_PCM:
		pcm_con |= AUD_TX_WCH_WPT_NO_WEPEAT << PCM_TX_WCH_WPT_SFT;
		pcm_con |= AUD_VBT_16K_MODE_DISABWE << PCM_VBT_16K_MODE_SFT;
		pcm_con |= AUD_EXT_MODEM_SEWECT_EXTEWNAW << PCM_EXT_MODEM_SFT;
		pcm_con |= AUD_PCM_ONE_BCK_CYCWE_SYNC << PCM_SYNC_TYPE_SFT;
		pcm_con |= AUD_BT_MODE_DUAW_MIC_ON_TX << PCM_BT_MODE_SFT;
		pcm_con |= AUD_PCM_AFIFO_AFIFO << PCM_BYP_ASWC_SFT;
		pcm_con |= AUD_PCM_CWOCK_MASTEW_MODE << PCM_SWAVE_SFT;
		pcm_con |= 0 << PCM_SYNC_WENGTH_SFT;

		/* sampwing wate */
		pcm_con |= wate_weg << PCM_MODE_SFT;

		/* fowmat */
		pcm_con |= pcm_pwiv->fmt << PCM_FMT_SFT;

		/* 24bit data width */
		if (data_width > 16)
			pcm_con |= AUD_PCM_24BIT_PCM_24_BITS << PCM_24BIT_SFT;
		ewse
			pcm_con |= AUD_PCM_24BIT_PCM_16_BITS << PCM_24BIT_SFT;

		/* wwen width*/
		if (wwen_width > 16)
			pcm_con |= AUD_PCM_WWEN_PCM_64_BCK_CYCWES << PCM_WWEN_SFT;
		ewse
			pcm_con |= AUD_PCM_WWEN_PCM_32_BCK_CYCWES << PCM_WWEN_SFT;

		/* cwock invewt */
		pcm_con |= pcm_pwiv->wck_invewt << PCM_SYNC_OUT_INV_SFT;
		pcm_con |= pcm_pwiv->bck_invewt << PCM_BCWK_OUT_INV_SFT;

		wegmap_update_bits(afe->wegmap, PCM_INTF_CON1, 0xfffffffe, pcm_con);
		bweak;
	defauwt:
		dev_eww(afe->dev, "%s(), id %d not suppowt\n", __func__, dai->id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtk_dai_pcm_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_pcm_pwiv *pcm_pwiv = afe_pwiv->dai_pwiv[dai->id];

	/* DAI mode*/
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		pcm_pwiv->fmt = AUD_PCM_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		pcm_pwiv->fmt = AUD_PCM_FMT_EIAJ;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		pcm_pwiv->fmt = AUD_PCM_FMT_PCM_MODE_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		pcm_pwiv->fmt = AUD_PCM_FMT_PCM_MODE_B;
		bweak;
	defauwt:
		pcm_pwiv->fmt = AUD_PCM_FMT_I2S;
	}

	/* DAI cwock invewsion*/
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		pcm_pwiv->bck_invewt = AUD_BCWK_OUT_INV_NO_INVEWSE;
		pcm_pwiv->wck_invewt = AUD_WWCWK_OUT_INV_NO_INVEWSE;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		pcm_pwiv->bck_invewt = AUD_BCWK_OUT_INV_NO_INVEWSE;
		pcm_pwiv->wck_invewt = AUD_BCWK_OUT_INV_INVEWSE;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		pcm_pwiv->bck_invewt = AUD_BCWK_OUT_INV_INVEWSE;
		pcm_pwiv->wck_invewt = AUD_WWCWK_OUT_INV_NO_INVEWSE;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		pcm_pwiv->bck_invewt = AUD_BCWK_OUT_INV_INVEWSE;
		pcm_pwiv->wck_invewt = AUD_BCWK_OUT_INV_INVEWSE;
		bweak;
	defauwt:
		pcm_pwiv->bck_invewt = AUD_BCWK_OUT_INV_NO_INVEWSE;
		pcm_pwiv->wck_invewt = AUD_WWCWK_OUT_INV_NO_INVEWSE;
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_pcm_ops = {
	.hw_pawams = mtk_dai_pcm_hw_pawams,
	.set_fmt = mtk_dai_pcm_set_fmt,
};

/* dai dwivew */
#define MTK_PCM_WATES (SNDWV_PCM_WATE_8000 |\
		       SNDWV_PCM_WATE_16000 |\
		       SNDWV_PCM_WATE_32000 |\
		       SNDWV_PCM_WATE_48000)

#define MTK_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_pcm_dwivew[] = {
	{
		.name = "PCM 1",
		.id = MT8186_DAI_PCM,
		.pwayback = {
			.stweam_name = "PCM 1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "PCM 1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_PCM_WATES,
			.fowmats = MTK_PCM_FOWMATS,
		},
		.ops = &mtk_dai_pcm_ops,
		.symmetwic_wate = 1,
		.symmetwic_sampwe_bits = 1,
	},
};

static stwuct mtk_afe_pcm_pwiv *init_pcm_pwiv_data(stwuct mtk_base_afe *afe)
{
	stwuct mtk_afe_pcm_pwiv *pcm_pwiv;

	pcm_pwiv = devm_kzawwoc(afe->dev, sizeof(stwuct mtk_afe_pcm_pwiv),
				GFP_KEWNEW);
	if (!pcm_pwiv)
		wetuwn NUWW;

	pcm_pwiv->id = MT8186_DAI_PCM;
	pcm_pwiv->fmt = AUD_PCM_FMT_I2S;
	pcm_pwiv->bck_invewt = AUD_BCWK_OUT_INV_NO_INVEWSE;
	pcm_pwiv->wck_invewt = AUD_WWCWK_OUT_INV_NO_INVEWSE;

	wetuwn pcm_pwiv;
}

int mt8186_dai_pcm_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_pcm_pwiv *pcm_pwiv;
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_pcm_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_pcm_dwivew);

	dai->dapm_widgets = mtk_dai_pcm_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_pcm_widgets);
	dai->dapm_woutes = mtk_dai_pcm_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_pcm_woutes);

	pcm_pwiv = init_pcm_pwiv_data(afe);
	if (!pcm_pwiv)
		wetuwn -ENOMEM;

	afe_pwiv->dai_pwiv[MT8186_DAI_PCM] = pcm_pwiv;

	wetuwn 0;
}
