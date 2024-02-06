// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI TDM Contwow
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude "mt8183-afe-cwk.h"
#incwude "mt8183-afe-common.h"
#incwude "mt8183-intewconnection.h"
#incwude "mt8183-weg.h"

stwuct mtk_afe_tdm_pwiv {
	int bck_id;
	int bck_wate;
	int tdm_out_mode;
	int bck_invewt;
	int wck_invewt;
	int mcwk_id;
	int mcwk_muwtipwe; /* accowding to sampwe wate */
	int mcwk_wate;
	int mcwk_apww;
};

enum {
	TDM_OUT_I2S = 0,
	TDM_OUT_TDM = 1,
};

enum {
	TDM_BCK_NON_INV = 0,
	TDM_BCK_INV = 1,
};

enum {
	TDM_WCK_NON_INV = 0,
	TDM_WCK_INV = 1,
};

enum {
	TDM_WWEN_16_BIT = 1,
	TDM_WWEN_32_BIT = 2,
};

enum {
	TDM_CHANNEW_BCK_16 = 0,
	TDM_CHANNEW_BCK_24 = 1,
	TDM_CHANNEW_BCK_32 = 2,
};

enum {
	TDM_CHANNEW_NUM_2 = 0,
	TDM_CHANNEW_NUM_4 = 1,
	TDM_CHANNEW_NUM_8 = 2,
};

enum  {
	TDM_CH_STAWT_O30_O31 = 0,
	TDM_CH_STAWT_O32_O33,
	TDM_CH_STAWT_O34_O35,
	TDM_CH_STAWT_O36_O37,
	TDM_CH_ZEWO,
};

enum {
	HDMI_BIT_WIDTH_16_BIT = 0,
	HDMI_BIT_WIDTH_32_BIT = 1,
};

static unsigned int get_hdmi_wwen(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) <= 16 ?
	       HDMI_BIT_WIDTH_16_BIT : HDMI_BIT_WIDTH_32_BIT;
}

static unsigned int get_tdm_wwen(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) <= 16 ?
	       TDM_WWEN_16_BIT : TDM_WWEN_32_BIT;
}

static unsigned int get_tdm_channew_bck(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) <= 16 ?
	       TDM_CHANNEW_BCK_16 : TDM_CHANNEW_BCK_32;
}

static unsigned int get_tdm_wwck_width(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) - 1;
}

static unsigned int get_tdm_ch(unsigned int ch)
{
	switch (ch) {
	case 1:
	case 2:
		wetuwn TDM_CHANNEW_NUM_2;
	case 3:
	case 4:
		wetuwn TDM_CHANNEW_NUM_4;
	case 5:
	case 6:
	case 7:
	case 8:
	defauwt:
		wetuwn TDM_CHANNEW_NUM_8;
	}
}

static unsigned int get_tdm_ch_fixup(unsigned int channews)
{
	if (channews > 4)
		wetuwn 8;
	ewse if (channews > 2)
		wetuwn 4;
	ewse
		wetuwn 2;
}

static unsigned int get_tdm_ch_pew_sdata(unsigned int mode,
					 unsigned int channews)
{
	if (mode == TDM_OUT_TDM)
		wetuwn get_tdm_ch_fixup(channews);
	ewse
		wetuwn 2;
}

/* intewconnection */
enum {
	HDMI_CONN_CH0 = 0,
	HDMI_CONN_CH1,
	HDMI_CONN_CH2,
	HDMI_CONN_CH3,
	HDMI_CONN_CH4,
	HDMI_CONN_CH5,
	HDMI_CONN_CH6,
	HDMI_CONN_CH7,
};

static const chaw *const hdmi_conn_mux_map[] = {
	"CH0", "CH1", "CH2", "CH3",
	"CH4", "CH5", "CH6", "CH7",
};

static int hdmi_conn_mux_map_vawue[] = {
	HDMI_CONN_CH0,
	HDMI_CONN_CH1,
	HDMI_CONN_CH2,
	HDMI_CONN_CH3,
	HDMI_CONN_CH4,
	HDMI_CONN_CH5,
	HDMI_CONN_CH6,
	HDMI_CONN_CH7,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch0_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_0_SFT,
				  HDMI_O_0_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch0_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH0_MUX", hdmi_ch0_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch1_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_1_SFT,
				  HDMI_O_1_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch1_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH1_MUX", hdmi_ch1_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch2_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_2_SFT,
				  HDMI_O_2_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch2_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH2_MUX", hdmi_ch2_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch3_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_3_SFT,
				  HDMI_O_3_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch3_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH3_MUX", hdmi_ch3_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch4_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_4_SFT,
				  HDMI_O_4_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch4_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH4_MUX", hdmi_ch4_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch5_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_5_SFT,
				  HDMI_O_5_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch5_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH5_MUX", hdmi_ch5_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch6_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_6_SFT,
				  HDMI_O_6_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch6_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH6_MUX", hdmi_ch6_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(hdmi_ch7_mux_map_enum,
				  AFE_HDMI_CONN0,
				  HDMI_O_7_SFT,
				  HDMI_O_7_MASK,
				  hdmi_conn_mux_map,
				  hdmi_conn_mux_map_vawue);

static const stwuct snd_kcontwow_new hdmi_ch7_mux_contwow =
	SOC_DAPM_ENUM("HDMI_CH7_MUX", hdmi_ch7_mux_map_enum);

enum {
	SUPPWY_SEQ_APWW,
	SUPPWY_SEQ_TDM_MCK_EN,
	SUPPWY_SEQ_TDM_BCK_EN,
};

static int mtk_tdm_bck_en_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow,
				int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[MT8183_DAI_TDM];

	dev_info(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8183_mck_enabwe(afe, tdm_pwiv->bck_id, tdm_pwiv->bck_wate);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		mt8183_mck_disabwe(afe, tdm_pwiv->bck_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_tdm_mck_en_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow,
				int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[MT8183_DAI_TDM];

	dev_info(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		 __func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8183_mck_enabwe(afe, tdm_pwiv->mcwk_id, tdm_pwiv->mcwk_wate);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		tdm_pwiv->mcwk_wate = 0;
		mt8183_mck_disabwe(afe, tdm_pwiv->mcwk_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget mtk_dai_tdm_widgets[] = {
	SND_SOC_DAPM_MUX("HDMI_CH0_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch0_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH1_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch1_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH2_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch2_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH3_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch3_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH4_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch4_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH5_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch5_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH6_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch6_mux_contwow),
	SND_SOC_DAPM_MUX("HDMI_CH7_MUX", SND_SOC_NOPM, 0, 0,
			 &hdmi_ch7_mux_contwow),

	SND_SOC_DAPM_CWOCK_SUPPWY("aud_tdm_cwk"),

	SND_SOC_DAPM_SUPPWY_S("TDM_BCK", SUPPWY_SEQ_TDM_BCK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_tdm_bck_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("TDM_MCK", SUPPWY_SEQ_TDM_MCK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_tdm_mck_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static int mtk_afe_tdm_apww_connect(stwuct snd_soc_dapm_widget *souwce,
				    stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[MT8183_DAI_TDM];
	int cuw_apww;

	/* which apww */
	cuw_apww = mt8183_get_apww_by_name(afe, souwce->name);

	wetuwn (tdm_pwiv->mcwk_apww == cuw_apww) ? 1 : 0;
}

static const stwuct snd_soc_dapm_woute mtk_dai_tdm_woutes[] = {
	{"HDMI_CH0_MUX", "CH0", "HDMI"},
	{"HDMI_CH0_MUX", "CH1", "HDMI"},
	{"HDMI_CH0_MUX", "CH2", "HDMI"},
	{"HDMI_CH0_MUX", "CH3", "HDMI"},
	{"HDMI_CH0_MUX", "CH4", "HDMI"},
	{"HDMI_CH0_MUX", "CH5", "HDMI"},
	{"HDMI_CH0_MUX", "CH6", "HDMI"},
	{"HDMI_CH0_MUX", "CH7", "HDMI"},

	{"HDMI_CH1_MUX", "CH0", "HDMI"},
	{"HDMI_CH1_MUX", "CH1", "HDMI"},
	{"HDMI_CH1_MUX", "CH2", "HDMI"},
	{"HDMI_CH1_MUX", "CH3", "HDMI"},
	{"HDMI_CH1_MUX", "CH4", "HDMI"},
	{"HDMI_CH1_MUX", "CH5", "HDMI"},
	{"HDMI_CH1_MUX", "CH6", "HDMI"},
	{"HDMI_CH1_MUX", "CH7", "HDMI"},

	{"HDMI_CH2_MUX", "CH0", "HDMI"},
	{"HDMI_CH2_MUX", "CH1", "HDMI"},
	{"HDMI_CH2_MUX", "CH2", "HDMI"},
	{"HDMI_CH2_MUX", "CH3", "HDMI"},
	{"HDMI_CH2_MUX", "CH4", "HDMI"},
	{"HDMI_CH2_MUX", "CH5", "HDMI"},
	{"HDMI_CH2_MUX", "CH6", "HDMI"},
	{"HDMI_CH2_MUX", "CH7", "HDMI"},

	{"HDMI_CH3_MUX", "CH0", "HDMI"},
	{"HDMI_CH3_MUX", "CH1", "HDMI"},
	{"HDMI_CH3_MUX", "CH2", "HDMI"},
	{"HDMI_CH3_MUX", "CH3", "HDMI"},
	{"HDMI_CH3_MUX", "CH4", "HDMI"},
	{"HDMI_CH3_MUX", "CH5", "HDMI"},
	{"HDMI_CH3_MUX", "CH6", "HDMI"},
	{"HDMI_CH3_MUX", "CH7", "HDMI"},

	{"HDMI_CH4_MUX", "CH0", "HDMI"},
	{"HDMI_CH4_MUX", "CH1", "HDMI"},
	{"HDMI_CH4_MUX", "CH2", "HDMI"},
	{"HDMI_CH4_MUX", "CH3", "HDMI"},
	{"HDMI_CH4_MUX", "CH4", "HDMI"},
	{"HDMI_CH4_MUX", "CH5", "HDMI"},
	{"HDMI_CH4_MUX", "CH6", "HDMI"},
	{"HDMI_CH4_MUX", "CH7", "HDMI"},

	{"HDMI_CH5_MUX", "CH0", "HDMI"},
	{"HDMI_CH5_MUX", "CH1", "HDMI"},
	{"HDMI_CH5_MUX", "CH2", "HDMI"},
	{"HDMI_CH5_MUX", "CH3", "HDMI"},
	{"HDMI_CH5_MUX", "CH4", "HDMI"},
	{"HDMI_CH5_MUX", "CH5", "HDMI"},
	{"HDMI_CH5_MUX", "CH6", "HDMI"},
	{"HDMI_CH5_MUX", "CH7", "HDMI"},

	{"HDMI_CH6_MUX", "CH0", "HDMI"},
	{"HDMI_CH6_MUX", "CH1", "HDMI"},
	{"HDMI_CH6_MUX", "CH2", "HDMI"},
	{"HDMI_CH6_MUX", "CH3", "HDMI"},
	{"HDMI_CH6_MUX", "CH4", "HDMI"},
	{"HDMI_CH6_MUX", "CH5", "HDMI"},
	{"HDMI_CH6_MUX", "CH6", "HDMI"},
	{"HDMI_CH6_MUX", "CH7", "HDMI"},

	{"HDMI_CH7_MUX", "CH0", "HDMI"},
	{"HDMI_CH7_MUX", "CH1", "HDMI"},
	{"HDMI_CH7_MUX", "CH2", "HDMI"},
	{"HDMI_CH7_MUX", "CH3", "HDMI"},
	{"HDMI_CH7_MUX", "CH4", "HDMI"},
	{"HDMI_CH7_MUX", "CH5", "HDMI"},
	{"HDMI_CH7_MUX", "CH6", "HDMI"},
	{"HDMI_CH7_MUX", "CH7", "HDMI"},

	{"TDM", NUWW, "HDMI_CH0_MUX"},
	{"TDM", NUWW, "HDMI_CH1_MUX"},
	{"TDM", NUWW, "HDMI_CH2_MUX"},
	{"TDM", NUWW, "HDMI_CH3_MUX"},
	{"TDM", NUWW, "HDMI_CH4_MUX"},
	{"TDM", NUWW, "HDMI_CH5_MUX"},
	{"TDM", NUWW, "HDMI_CH6_MUX"},
	{"TDM", NUWW, "HDMI_CH7_MUX"},

	{"TDM", NUWW, "aud_tdm_cwk"},
	{"TDM", NUWW, "TDM_BCK"},
	{"TDM_BCK", NUWW, "TDM_MCK"},
	{"TDM_MCK", NUWW, APWW1_W_NAME, mtk_afe_tdm_apww_connect},
	{"TDM_MCK", NUWW, APWW2_W_NAME, mtk_afe_tdm_apww_connect},
};

/* dai ops */
static int mtk_dai_tdm_caw_mcwk(stwuct mtk_base_afe *afe,
				stwuct mtk_afe_tdm_pwiv *tdm_pwiv,
				int fweq)
{
	int apww;
	int apww_wate;

	apww = mt8183_get_apww_by_wate(afe, fweq);
	apww_wate = mt8183_get_apww_wate(afe, apww);

	if (!fweq || fweq > apww_wate) {
		dev_wawn(afe->dev,
			 "%s(), fweq(%d Hz) invawid\n", __func__, fweq);
		wetuwn -EINVAW;
	}

	if (apww_wate % fweq != 0) {
		dev_wawn(afe->dev,
			 "%s(), APWW cannot genewate %d Hz", __func__, fweq);
		wetuwn -EINVAW;
	}

	tdm_pwiv->mcwk_wate = fweq;
	tdm_pwiv->mcwk_apww = apww;

	wetuwn 0;
}

static int mtk_dai_tdm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int tdm_id = dai->id;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[tdm_id];
	unsigned int tdm_out_mode = tdm_pwiv->tdm_out_mode;
	unsigned int wate = pawams_wate(pawams);
	unsigned int channews = pawams_channews(pawams);
	unsigned int out_channews_pew_sdata =
		get_tdm_ch_pew_sdata(tdm_out_mode, channews);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int tdm_con = 0;

	/* cawcuwate mcwk_wate, if not set expwicitwy */
	if (!tdm_pwiv->mcwk_wate) {
		tdm_pwiv->mcwk_wate = wate * tdm_pwiv->mcwk_muwtipwe;
		mtk_dai_tdm_caw_mcwk(afe,
				     tdm_pwiv,
				     tdm_pwiv->mcwk_wate);
	}

	/* cawcuwate bck */
	tdm_pwiv->bck_wate = wate *
			     out_channews_pew_sdata *
			     snd_pcm_fowmat_physicaw_width(fowmat);

	if (tdm_pwiv->bck_wate > tdm_pwiv->mcwk_wate)
		dev_wawn(afe->dev, "%s(), bck_wate > mcwk_wate wate", __func__);

	if (tdm_pwiv->mcwk_wate % tdm_pwiv->bck_wate != 0)
		dev_wawn(afe->dev, "%s(), bck cannot genewate", __func__);

	dev_info(afe->dev, "%s(), id %d, wate %d, channews %d, fowmat %d, mcwk_wate %d, bck_wate %d\n",
		 __func__,
		 tdm_id, wate, channews, fowmat,
		 tdm_pwiv->mcwk_wate, tdm_pwiv->bck_wate);
	dev_info(afe->dev, "%s(), out_channews_pew_sdata = %d\n",
		 __func__, out_channews_pew_sdata);

	/* set tdm */
	if (tdm_pwiv->bck_invewt)
		wegmap_update_bits(afe->wegmap, AUDIO_TOP_CON3,
				   BCK_INVEWSE_MASK_SFT,
				   0x1 << BCK_INVEWSE_SFT);

	if (tdm_pwiv->wck_invewt)
		tdm_con |= 1 << WWCK_INVEWSE_SFT;

	if (tdm_pwiv->tdm_out_mode == TDM_OUT_I2S) {
		tdm_con |= 1 << DEWAY_DATA_SFT;
		tdm_con |= get_tdm_wwck_width(fowmat) << WWCK_TDM_WIDTH_SFT;
	} ewse if (tdm_pwiv->tdm_out_mode == TDM_OUT_TDM) {
		tdm_con |= 0 << DEWAY_DATA_SFT;
		tdm_con |= 0 << WWCK_TDM_WIDTH_SFT;
	}

	tdm_con |= 1 << WEFT_AWIGN_SFT;
	tdm_con |= get_tdm_wwen(fowmat) << WWEN_SFT;
	tdm_con |= get_tdm_ch(out_channews_pew_sdata) << CHANNEW_NUM_SFT;
	tdm_con |= get_tdm_channew_bck(fowmat) << CHANNEW_BCK_CYCWES_SFT;
	wegmap_wwite(afe->wegmap, AFE_TDM_CON1, tdm_con);

	if (out_channews_pew_sdata == 2) {
		switch (channews) {
		case 1:
		case 2:
			tdm_con = TDM_CH_STAWT_O30_O31 << ST_CH_PAIW_SOUT0_SFT;
			tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT1_SFT;
			tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT2_SFT;
			tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT3_SFT;
			bweak;
		case 3:
		case 4:
			tdm_con = TDM_CH_STAWT_O30_O31 << ST_CH_PAIW_SOUT0_SFT;
			tdm_con |= TDM_CH_STAWT_O32_O33 << ST_CH_PAIW_SOUT1_SFT;
			tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT2_SFT;
			tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT3_SFT;
			bweak;
		case 5:
		case 6:
			tdm_con = TDM_CH_STAWT_O30_O31 << ST_CH_PAIW_SOUT0_SFT;
			tdm_con |= TDM_CH_STAWT_O32_O33 << ST_CH_PAIW_SOUT1_SFT;
			tdm_con |= TDM_CH_STAWT_O34_O35 << ST_CH_PAIW_SOUT2_SFT;
			tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT3_SFT;
			bweak;
		case 7:
		case 8:
			tdm_con = TDM_CH_STAWT_O30_O31 << ST_CH_PAIW_SOUT0_SFT;
			tdm_con |= TDM_CH_STAWT_O32_O33 << ST_CH_PAIW_SOUT1_SFT;
			tdm_con |= TDM_CH_STAWT_O34_O35 << ST_CH_PAIW_SOUT2_SFT;
			tdm_con |= TDM_CH_STAWT_O36_O37 << ST_CH_PAIW_SOUT3_SFT;
			bweak;
		defauwt:
			tdm_con = 0;
		}
	} ewse {
		tdm_con = TDM_CH_STAWT_O30_O31 << ST_CH_PAIW_SOUT0_SFT;
		tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT1_SFT;
		tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT2_SFT;
		tdm_con |= TDM_CH_ZEWO << ST_CH_PAIW_SOUT3_SFT;
	}

	wegmap_wwite(afe->wegmap, AFE_TDM_CON2, tdm_con);

	wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0,
			   AFE_HDMI_OUT_CH_NUM_MASK_SFT,
			   channews << AFE_HDMI_OUT_CH_NUM_SFT);

	wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0,
			   AFE_HDMI_OUT_BIT_WIDTH_MASK_SFT,
			   get_hdmi_wwen(fowmat) << AFE_HDMI_OUT_BIT_WIDTH_SFT);
	wetuwn 0;
}

static int mtk_dai_tdm_twiggew(stwuct snd_pcm_substweam *substweam,
			       int cmd,
			       stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		/* enabwe Out contwow */
		wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0,
				   AFE_HDMI_OUT_ON_MASK_SFT,
				   0x1 << AFE_HDMI_OUT_ON_SFT);
		/* enabwe tdm */
		wegmap_update_bits(afe->wegmap, AFE_TDM_CON1,
				   TDM_EN_MASK_SFT, 0x1 << TDM_EN_SFT);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		/* disabwe tdm */
		wegmap_update_bits(afe->wegmap, AFE_TDM_CON1,
				   TDM_EN_MASK_SFT, 0);
		/* disabwe Out contwow */
		wegmap_update_bits(afe->wegmap, AFE_HDMI_OUT_CON0,
				   AFE_HDMI_OUT_ON_MASK_SFT,
				   0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtk_dai_tdm_set_syscwk(stwuct snd_soc_dai *dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dai->dev);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai->id];

	if (!tdm_pwiv) {
		dev_wawn(afe->dev, "%s(), tdm_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	if (diw != SND_SOC_CWOCK_OUT) {
		dev_wawn(afe->dev, "%s(), diw != SND_SOC_CWOCK_OUT", __func__);
		wetuwn -EINVAW;
	}

	dev_info(afe->dev, "%s(), fweq %d\n", __func__, fweq);

	wetuwn mtk_dai_tdm_caw_mcwk(afe, tdm_pwiv, fweq);
}

static int mtk_dai_tdm_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dai->dev);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai->id];

	if (!tdm_pwiv) {
		dev_wawn(afe->dev, "%s(), tdm_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	/* DAI mode*/
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		tdm_pwiv->tdm_out_mode = TDM_OUT_I2S;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		tdm_pwiv->tdm_out_mode = TDM_OUT_TDM;
		bweak;
	defauwt:
		tdm_pwiv->tdm_out_mode = TDM_OUT_I2S;
	}

	/* DAI cwock invewsion*/
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		tdm_pwiv->bck_invewt = TDM_BCK_NON_INV;
		tdm_pwiv->wck_invewt = TDM_WCK_NON_INV;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		tdm_pwiv->bck_invewt = TDM_BCK_NON_INV;
		tdm_pwiv->wck_invewt = TDM_WCK_INV;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		tdm_pwiv->bck_invewt = TDM_BCK_INV;
		tdm_pwiv->wck_invewt = TDM_WCK_NON_INV;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
	defauwt:
		tdm_pwiv->bck_invewt = TDM_BCK_INV;
		tdm_pwiv->wck_invewt = TDM_WCK_INV;
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_tdm_ops = {
	.hw_pawams = mtk_dai_tdm_hw_pawams,
	.twiggew = mtk_dai_tdm_twiggew,
	.set_syscwk = mtk_dai_tdm_set_syscwk,
	.set_fmt = mtk_dai_tdm_set_fmt,
};

/* dai dwivew */
#define MTK_TDM_WATES (SNDWV_PCM_WATE_8000_48000 |\
		       SNDWV_PCM_WATE_88200 |\
		       SNDWV_PCM_WATE_96000 |\
		       SNDWV_PCM_WATE_176400 |\
		       SNDWV_PCM_WATE_192000)

#define MTK_TDM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_tdm_dwivew[] = {
	{
		.name = "TDM",
		.id = MT8183_DAI_TDM,
		.pwayback = {
			.stweam_name = "TDM",
			.channews_min = 2,
			.channews_max = 8,
			.wates = MTK_TDM_WATES,
			.fowmats = MTK_TDM_FOWMATS,
		},
		.ops = &mtk_dai_tdm_ops,
	},
};

int mt8183_dai_tdm_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv;
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_tdm_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_tdm_dwivew);

	dai->dapm_widgets = mtk_dai_tdm_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_tdm_widgets);
	dai->dapm_woutes = mtk_dai_tdm_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_tdm_woutes);

	tdm_pwiv = devm_kzawwoc(afe->dev, sizeof(stwuct mtk_afe_tdm_pwiv),
				GFP_KEWNEW);
	if (!tdm_pwiv)
		wetuwn -ENOMEM;

	tdm_pwiv->mcwk_muwtipwe = 128;
	tdm_pwiv->bck_id = MT8183_I2S4_BCK;
	tdm_pwiv->mcwk_id = MT8183_I2S4_MCK;

	afe_pwiv->dai_pwiv[MT8183_DAI_TDM] = tdm_pwiv;
	wetuwn 0;
}
