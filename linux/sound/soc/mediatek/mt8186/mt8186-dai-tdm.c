// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI TDM Contwow
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>

#incwude "mt8186-afe-cwk.h"
#incwude "mt8186-afe-common.h"
#incwude "mt8186-afe-gpio.h"
#incwude "mt8186-intewconnection.h"

#define TDM_HD_EN_W_NAME "TDM_HD_EN"
#define TDM_MCWK_EN_W_NAME "TDM_MCWK_EN"
#define MTK_AFE_TDM_KCONTWOW_NAME "TDM_HD_Mux"

stwuct mtk_afe_tdm_pwiv {
	unsigned int id;
	unsigned int wate; /* fow detewmine which apww to use */
	unsigned int bck_invewt;
	unsigned int wck_invewt;
	unsigned int wwck_width;
	unsigned int mcwk_id;
	unsigned int mcwk_muwtipwe; /* accowding to sampwe wate */
	unsigned int mcwk_wate;
	unsigned int mcwk_apww;
	unsigned int tdm_mode;
	unsigned int data_mode;
	unsigned int swave_mode;
	unsigned int wow_jittew_en;
};

enum {
	TDM_IN_I2S = 0,
	TDM_IN_WJ = 1,
	TDM_IN_WJ = 2,
	TDM_IN_DSP_A = 4,
	TDM_IN_DSP_B = 5,
};

enum {
	TDM_DATA_ONE_PIN = 0,
	TDM_DATA_MUWTI_PIN,
};

enum {
	TDM_BCK_NON_INV = 0,
	TDM_BCK_INV = 1,
};

enum {
	TDM_WCK_NON_INV = 0,
	TDM_WCK_INV = 1,
};

static unsigned int get_tdm_wwck_width(snd_pcm_fowmat_t fowmat,
				       unsigned int mode)
{
	if (mode == TDM_IN_DSP_A || mode == TDM_IN_DSP_B)
		wetuwn 0;

	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) - 1;
}

static unsigned int get_tdm_ch_fixup(unsigned int channews)
{
	if (channews > 4)
		wetuwn 8;
	ewse if (channews > 2)
		wetuwn 4;

	wetuwn 2;
}

static unsigned int get_tdm_ch_pew_sdata(unsigned int mode,
					 unsigned int channews)
{
	if (mode == TDM_IN_DSP_A || mode == TDM_IN_DSP_B)
		wetuwn get_tdm_ch_fixup(channews);

	wetuwn 2;
}

enum {
	SUPPWY_SEQ_APWW,
	SUPPWY_SEQ_TDM_MCK_EN,
	SUPPWY_SEQ_TDM_HD_EN,
	SUPPWY_SEQ_TDM_EN,
};

static int get_tdm_id_by_name(const chaw *name)
{
	wetuwn MT8186_DAI_TDM_IN;
}

static int mtk_tdm_en_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow,
			    int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(w->name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];

	dev_dbg(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8186_afe_gpio_wequest(afe->dev, twue, tdm_pwiv->id, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		mt8186_afe_gpio_wequest(afe->dev, fawse, tdm_pwiv->id, 0);
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
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(w->name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];

	dev_dbg(cmpnt->dev, "%s(), name %s, event 0x%x, dai_id %d\n",
		__func__, w->name, event, dai_id);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8186_mck_enabwe(afe, tdm_pwiv->mcwk_id, tdm_pwiv->mcwk_wate);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		tdm_pwiv->mcwk_wate = 0;
		mt8186_mck_disabwe(afe, tdm_pwiv->mcwk_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* dai component */
/* tdm viwtuaw mux to output widget */
static const chaw * const tdm_mux_map[] = {
	"Nowmaw", "Dummy_Widget",
};

static int tdm_mux_map_vawue[] = {
	0, 1,
};

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(tdm_mux_map_enum,
					      SND_SOC_NOPM,
					      0,
					      1,
					      tdm_mux_map,
					      tdm_mux_map_vawue);

static const stwuct snd_kcontwow_new tdm_in_mux_contwow =
	SOC_DAPM_ENUM("TDM In Sewect", tdm_mux_map_enum);

static const stwuct snd_soc_dapm_widget mtk_dai_tdm_widgets[] = {
	SND_SOC_DAPM_CWOCK_SUPPWY("aud_tdm_cwk"),

	SND_SOC_DAPM_SUPPWY_S("TDM_EN", SUPPWY_SEQ_TDM_EN,
			      ETDM_IN1_CON0, ETDM_IN1_CON0_WEG_ETDM_IN_EN_SFT,
			      0, mtk_tdm_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	/* tdm hd en */
	SND_SOC_DAPM_SUPPWY_S(TDM_HD_EN_W_NAME, SUPPWY_SEQ_TDM_HD_EN,
			      ETDM_IN1_CON2, ETDM_IN1_CON2_WEG_CWOCK_SOUWCE_SEW_SFT,
			      0, NUWW,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S(TDM_MCWK_EN_W_NAME, SUPPWY_SEQ_TDM_MCK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_tdm_mck_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("TDM_DUMMY_IN"),

	SND_SOC_DAPM_MUX("TDM_In_Mux",
			 SND_SOC_NOPM, 0, 0, &tdm_in_mux_contwow),
};

static int mtk_afe_tdm_mcwk_connect(stwuct snd_soc_dapm_widget *souwce,
				    stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(w->name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];

	wetuwn (tdm_pwiv->mcwk_wate > 0) ? 1 : 0;
}

static int mtk_afe_tdm_mcwk_apww_connect(stwuct snd_soc_dapm_widget *souwce,
					 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(w->name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];
	int cuw_apww;

	/* which apww */
	cuw_apww = mt8186_get_apww_by_name(afe, souwce->name);

	wetuwn (tdm_pwiv->mcwk_apww == cuw_apww) ? 1 : 0;
}

static int mtk_afe_tdm_hd_connect(stwuct snd_soc_dapm_widget *souwce,
				  stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(w->name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];

	wetuwn tdm_pwiv->wow_jittew_en;
}

static int mtk_afe_tdm_apww_connect(stwuct snd_soc_dapm_widget *souwce,
				    stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(w->name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];
	int cuw_apww;
	int tdm_need_apww;

	/* which apww */
	cuw_apww = mt8186_get_apww_by_name(afe, souwce->name);

	/* choose APWW fwom tdm wate */
	tdm_need_apww = mt8186_get_apww_by_wate(afe, tdm_pwiv->wate);

	wetuwn (tdm_need_apww == cuw_apww) ? 1 : 0;
}

/* wow jittew contwow */
static const chaw * const mt8186_tdm_hd_stw[] = {
	"Nowmaw", "Wow_Jittew"
};

static const stwuct soc_enum mt8186_tdm_enum[] = {
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(mt8186_tdm_hd_stw),
			    mt8186_tdm_hd_stw),
};

static int mt8186_tdm_hd_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(kcontwow->id.name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];

	ucontwow->vawue.integew.vawue[0] = tdm_pwiv->wow_jittew_en;

	wetuwn 0;
}

static int mt8186_tdm_hd_set(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_tdm_id_by_name(kcontwow->id.name);
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai_id];
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	int hd_en;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	hd_en = ucontwow->vawue.integew.vawue[0];

	dev_dbg(afe->dev, "%s(), kcontwow name %s, hd_en %d\n",
		__func__, kcontwow->id.name, hd_en);

	if (tdm_pwiv->wow_jittew_en == hd_en)
		wetuwn 0;

	tdm_pwiv->wow_jittew_en = hd_en;

	wetuwn 1;
}

static const stwuct snd_kcontwow_new mtk_dai_tdm_contwows[] = {
	SOC_ENUM_EXT(MTK_AFE_TDM_KCONTWOW_NAME, mt8186_tdm_enum[0],
		     mt8186_tdm_hd_get, mt8186_tdm_hd_set),
};

static const stwuct snd_soc_dapm_woute mtk_dai_tdm_woutes[] = {
	{"TDM IN", NUWW, "aud_tdm_cwk"},
	{"TDM IN", NUWW, "TDM_EN"},
	{"TDM IN", NUWW, TDM_HD_EN_W_NAME, mtk_afe_tdm_hd_connect},
	{TDM_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_tdm_apww_connect},
	{TDM_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_tdm_apww_connect},

	{"TDM IN", NUWW, TDM_MCWK_EN_W_NAME, mtk_afe_tdm_mcwk_connect},
	{TDM_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_tdm_mcwk_apww_connect},
	{TDM_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_tdm_mcwk_apww_connect},

	/* awwow tdm on without codec on */
	{"TDM IN", NUWW, "TDM_In_Mux"},
	{"TDM_In_Mux", "Dummy_Widget", "TDM_DUMMY_IN"},
};

/* dai ops */
static int mtk_dai_tdm_caw_mcwk(stwuct mtk_base_afe *afe,
				stwuct mtk_afe_tdm_pwiv *tdm_pwiv,
				int fweq)
{
	int apww;
	int apww_wate;

	apww = mt8186_get_apww_by_wate(afe, fweq);
	apww_wate = mt8186_get_apww_wate(afe, apww);

	if (!fweq || fweq > apww_wate) {
		dev_eww(afe->dev,
			"%s(), fweq(%d Hz) invawid\n", __func__, fweq);
		wetuwn -EINVAW;
	}

	if (apww_wate % fweq != 0) {
		dev_eww(afe->dev,
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
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int tdm_id = dai->id;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[tdm_id];
	unsigned int tdm_mode = tdm_pwiv->tdm_mode;
	unsigned int data_mode = tdm_pwiv->data_mode;
	unsigned int wate = pawams_wate(pawams);
	unsigned int channews = pawams_channews(pawams);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int bit_width =
		snd_pcm_fowmat_physicaw_width(fowmat);
	unsigned int tdm_channews = (data_mode == TDM_DATA_ONE_PIN) ?
		get_tdm_ch_pew_sdata(tdm_mode, channews) : 2;
	unsigned int wwck_width =
		get_tdm_wwck_width(fowmat, tdm_mode);
	unsigned int tdm_con = 0;
	boow swave_mode = tdm_pwiv->swave_mode;
	boow wwck_inv = tdm_pwiv->wck_invewt;
	boow bck_inv = tdm_pwiv->bck_invewt;
	unsigned int twan_wate;
	unsigned int twan_wewatch_wate;

	tdm_pwiv->wate = wate;
	twan_wate = mt8186_wate_twansfowm(afe->dev, wate, dai->id);
	twan_wewatch_wate = mt8186_tdm_wewatch_wate_twansfowm(afe->dev, wate);

	/* cawcuwate mcwk_wate, if not set expwicitwy */
	if (!tdm_pwiv->mcwk_wate) {
		tdm_pwiv->mcwk_wate = wate * tdm_pwiv->mcwk_muwtipwe;
		mtk_dai_tdm_caw_mcwk(afe, tdm_pwiv, tdm_pwiv->mcwk_wate);
	}

	/* ETDM_IN1_CON0 */
	tdm_con |= swave_mode << ETDM_IN1_CON0_WEG_SWAVE_MODE_SFT;
	tdm_con |= tdm_mode << ETDM_IN1_CON0_WEG_FMT_SFT;
	tdm_con |= (bit_width - 1) << ETDM_IN1_CON0_WEG_BIT_WENGTH_SFT;
	tdm_con |= (bit_width - 1) << ETDM_IN1_CON0_WEG_WOWD_WENGTH_SFT;
	tdm_con |= (tdm_channews - 1) << ETDM_IN1_CON0_WEG_CH_NUM_SFT;
	/* need to disabwe sync mode othewwise this may cause watch data ewwow */
	tdm_con |= 0 << ETDM_IN1_CON0_WEG_SYNC_MODE_SFT;
	/* wewatch 1x en cwock fix to h26m */
	tdm_con |= 0 << ETDM_IN1_CON0_WEG_WEWATCH_1X_EN_SEW_DOMAIN_SFT;
	wegmap_update_bits(afe->wegmap, ETDM_IN1_CON0, ETDM_IN_CON0_CTWW_MASK, tdm_con);

	/* ETDM_IN1_CON1 */
	tdm_con = 0;
	tdm_con |= 0 << ETDM_IN1_CON1_WEG_WWCK_AUTO_MODE_SFT;
	tdm_con |= 1 << ETDM_IN1_CON1_PINMUX_MCWK_CTWW_OE_SFT;
	tdm_con |= (wwck_width - 1) << ETDM_IN1_CON1_WEG_WWCK_WIDTH_SFT;
	wegmap_update_bits(afe->wegmap, ETDM_IN1_CON1, ETDM_IN_CON1_CTWW_MASK, tdm_con);

	/* ETDM_IN1_CON3 */
	tdm_con = ETDM_IN_CON3_FS(twan_wate);
	wegmap_update_bits(afe->wegmap, ETDM_IN1_CON3, ETDM_IN_CON3_CTWW_MASK, tdm_con);

	/* ETDM_IN1_CON4 */
	tdm_con = ETDM_IN_CON4_FS(twan_wewatch_wate);
	if (swave_mode) {
		if (wwck_inv)
			tdm_con |= ETDM_IN_CON4_CON0_SWAVE_WWCK_INV;
		if (bck_inv)
			tdm_con |= ETDM_IN_CON4_CON0_SWAVE_BCK_INV;
	} ewse {
		if (wwck_inv)
			tdm_con |= ETDM_IN_CON4_CON0_MASTEW_WWCK_INV;
		if (bck_inv)
			tdm_con |= ETDM_IN_CON4_CON0_MASTEW_BCK_INV;
	}
	wegmap_update_bits(afe->wegmap, ETDM_IN1_CON4, ETDM_IN_CON4_CTWW_MASK, tdm_con);

	/* ETDM_IN1_CON2 */
	tdm_con = 0;
	if (data_mode == TDM_DATA_MUWTI_PIN) {
		tdm_con |= ETDM_IN_CON2_MUWTI_IP_2CH_MODE;
		tdm_con |= ETDM_IN_CON2_MUWTI_IP_CH(channews);
	}
	wegmap_update_bits(afe->wegmap, ETDM_IN1_CON2, ETDM_IN_CON2_CTWW_MASK, tdm_con);

	/* ETDM_IN1_CON8 */
	tdm_con = 0;
	if (swave_mode) {
		tdm_con |= 1 << ETDM_IN1_CON8_WEG_ETDM_USE_AFIFO_SFT;
		tdm_con |= 0 << ETDM_IN1_CON8_WEG_AFIFO_CWOCK_DOMAIN_SEW_SFT;
		tdm_con |= ETDM_IN_CON8_FS(twan_wewatch_wate);
	} ewse {
		tdm_con |= 0 << ETDM_IN1_CON8_WEG_ETDM_USE_AFIFO_SFT;
	}
	wegmap_update_bits(afe->wegmap, ETDM_IN1_CON8, ETDM_IN_CON8_CTWW_MASK, tdm_con);

	wetuwn 0;
}

static int mtk_dai_tdm_set_syscwk(stwuct snd_soc_dai *dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dai->dev);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai->id];

	if (diw != SND_SOC_CWOCK_IN) {
		dev_eww(afe->dev, "%s(), diw != SND_SOC_CWOCK_OUT", __func__);
		wetuwn -EINVAW;
	}

	dev_dbg(afe->dev, "%s(), fweq %d\n", __func__, fweq);

	wetuwn mtk_dai_tdm_caw_mcwk(afe, tdm_pwiv, fweq);
}

static int mtk_dai_tdm_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dai->dev);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai->id];

	/* DAI mode*/
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		tdm_pwiv->tdm_mode = TDM_IN_I2S;
		tdm_pwiv->data_mode = TDM_DATA_MUWTI_PIN;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		tdm_pwiv->tdm_mode = TDM_IN_WJ;
		tdm_pwiv->data_mode = TDM_DATA_MUWTI_PIN;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		tdm_pwiv->tdm_mode = TDM_IN_WJ;
		tdm_pwiv->data_mode = TDM_DATA_MUWTI_PIN;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		tdm_pwiv->tdm_mode = TDM_IN_DSP_A;
		tdm_pwiv->data_mode = TDM_DATA_ONE_PIN;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		tdm_pwiv->tdm_mode = TDM_IN_DSP_B;
		tdm_pwiv->data_mode = TDM_DATA_ONE_PIN;
		bweak;
	defauwt:
		dev_eww(afe->dev, "%s(), invawid DAIFMT_FOWMAT_MASK", __func__);
		wetuwn -EINVAW;
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
		tdm_pwiv->bck_invewt = TDM_BCK_INV;
		tdm_pwiv->wck_invewt = TDM_WCK_INV;
		bweak;
	defauwt:
		dev_eww(afe->dev, "%s(), invawid DAIFMT_INV_MASK", __func__);
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		tdm_pwiv->swave_mode = fawse;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		tdm_pwiv->swave_mode = twue;
		bweak;
	defauwt:
		dev_eww(afe->dev, "%s(), invawid DAIFMT_CWOCK_PWOVIDEW_MASK",
			__func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtk_dai_tdm_set_tdm_swot(stwuct snd_soc_dai *dai,
				    unsigned int tx_mask,
				    unsigned int wx_mask,
				    int swots,
				    int swot_width)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dai->dev);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv = afe_pwiv->dai_pwiv[dai->id];

	dev_dbg(dai->dev, "%s %d swot_width %d\n", __func__, dai->id, swot_width);

	tdm_pwiv->wwck_width = swot_width;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_tdm_ops = {
	.hw_pawams = mtk_dai_tdm_hw_pawams,
	.set_syscwk = mtk_dai_tdm_set_syscwk,
	.set_fmt = mtk_dai_tdm_set_fmt,
	.set_tdm_swot = mtk_dai_tdm_set_tdm_swot,
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
		.name = "TDM IN",
		.id = MT8186_DAI_TDM_IN,
		.captuwe = {
			.stweam_name = "TDM IN",
			.channews_min = 2,
			.channews_max = 8,
			.wates = MTK_TDM_WATES,
			.fowmats = MTK_TDM_FOWMATS,
		},
		.ops = &mtk_dai_tdm_ops,
	},
};

static stwuct mtk_afe_tdm_pwiv *init_tdm_pwiv_data(stwuct mtk_base_afe *afe)
{
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv;

	tdm_pwiv = devm_kzawwoc(afe->dev, sizeof(stwuct mtk_afe_tdm_pwiv),
				GFP_KEWNEW);
	if (!tdm_pwiv)
		wetuwn NUWW;

	tdm_pwiv->mcwk_muwtipwe = 512;
	tdm_pwiv->mcwk_id = MT8186_TDM_MCK;
	tdm_pwiv->id = MT8186_DAI_TDM_IN;

	wetuwn tdm_pwiv;
}

int mt8186_dai_tdm_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_tdm_pwiv *tdm_pwiv;
	stwuct mtk_base_afe_dai *dai;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_tdm_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_tdm_dwivew);

	dai->contwows = mtk_dai_tdm_contwows;
	dai->num_contwows = AWWAY_SIZE(mtk_dai_tdm_contwows);
	dai->dapm_widgets = mtk_dai_tdm_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_tdm_widgets);
	dai->dapm_woutes = mtk_dai_tdm_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_tdm_woutes);

	tdm_pwiv = init_tdm_pwiv_data(afe);
	if (!tdm_pwiv)
		wetuwn -ENOMEM;

	afe_pwiv->dai_pwiv[MT8186_DAI_TDM_IN] = tdm_pwiv;

	wetuwn 0;
}
