// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI I2S Contwow
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude "mt8183-afe-cwk.h"
#incwude "mt8183-afe-common.h"
#incwude "mt8183-intewconnection.h"
#incwude "mt8183-weg.h"

enum {
	I2S_FMT_EIAJ = 0,
	I2S_FMT_I2S = 1,
};

enum {
	I2S_WWEN_16_BIT = 0,
	I2S_WWEN_32_BIT = 1,
};

enum {
	I2S_HD_NOWMAW = 0,
	I2S_HD_WOW_JITTEW = 1,
};

enum {
	I2S1_SEW_O28_O29 = 0,
	I2S1_SEW_O03_O04 = 1,
};

enum {
	I2S_IN_PAD_CONNSYS = 0,
	I2S_IN_PAD_IO_MUX = 1,
};

stwuct mtk_afe_i2s_pwiv {
	int id;
	int wate; /* fow detewmine which apww to use */
	int wow_jittew_en;

	int shawe_i2s_id;

	int mcwk_id;
	int mcwk_wate;
	int mcwk_apww;

	int use_eiaj;
};

static unsigned int get_i2s_wwen(snd_pcm_fowmat_t fowmat)
{
	wetuwn snd_pcm_fowmat_physicaw_width(fowmat) <= 16 ?
	       I2S_WWEN_16_BIT : I2S_WWEN_32_BIT;
}

#define MTK_AFE_I2S0_KCONTWOW_NAME "I2S0_HD_Mux"
#define MTK_AFE_I2S1_KCONTWOW_NAME "I2S1_HD_Mux"
#define MTK_AFE_I2S2_KCONTWOW_NAME "I2S2_HD_Mux"
#define MTK_AFE_I2S3_KCONTWOW_NAME "I2S3_HD_Mux"
#define MTK_AFE_I2S5_KCONTWOW_NAME "I2S5_HD_Mux"

#define I2S0_HD_EN_W_NAME "I2S0_HD_EN"
#define I2S1_HD_EN_W_NAME "I2S1_HD_EN"
#define I2S2_HD_EN_W_NAME "I2S2_HD_EN"
#define I2S3_HD_EN_W_NAME "I2S3_HD_EN"
#define I2S5_HD_EN_W_NAME "I2S5_HD_EN"

#define I2S0_MCWK_EN_W_NAME "I2S0_MCWK_EN"
#define I2S1_MCWK_EN_W_NAME "I2S1_MCWK_EN"
#define I2S2_MCWK_EN_W_NAME "I2S2_MCWK_EN"
#define I2S3_MCWK_EN_W_NAME "I2S3_MCWK_EN"
#define I2S5_MCWK_EN_W_NAME "I2S5_MCWK_EN"

static int get_i2s_id_by_name(stwuct mtk_base_afe *afe,
			      const chaw *name)
{
	if (stwncmp(name, "I2S0", 4) == 0)
		wetuwn MT8183_DAI_I2S_0;
	ewse if (stwncmp(name, "I2S1", 4) == 0)
		wetuwn MT8183_DAI_I2S_1;
	ewse if (stwncmp(name, "I2S2", 4) == 0)
		wetuwn MT8183_DAI_I2S_2;
	ewse if (stwncmp(name, "I2S3", 4) == 0)
		wetuwn MT8183_DAI_I2S_3;
	ewse if (stwncmp(name, "I2S5", 4) == 0)
		wetuwn MT8183_DAI_I2S_5;
	ewse
		wetuwn -EINVAW;
}

static stwuct mtk_afe_i2s_pwiv *get_i2s_pwiv_by_name(stwuct mtk_base_afe *afe,
						     const chaw *name)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_i2s_id_by_name(afe, name);

	if (dai_id < 0)
		wetuwn NUWW;

	wetuwn afe_pwiv->dai_pwiv[dai_id];
}

/* wow jittew contwow */
static const chaw * const mt8183_i2s_hd_stw[] = {
	"Nowmaw", "Wow_Jittew"
};

static const stwuct soc_enum mt8183_i2s_enum[] = {
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(mt8183_i2s_hd_stw),
			    mt8183_i2s_hd_stw),
};

static int mt8183_i2s_hd_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, kcontwow->id.name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	ucontwow->vawue.integew.vawue[0] = i2s_pwiv->wow_jittew_en;

	wetuwn 0;
}

static int mt8183_i2s_hd_set(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	int hd_en, change;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	hd_en = ucontwow->vawue.integew.vawue[0];

	i2s_pwiv = get_i2s_pwiv_by_name(afe, kcontwow->id.name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	change = i2s_pwiv->wow_jittew_en != hd_en;
	i2s_pwiv->wow_jittew_en = hd_en;

	wetuwn change;
}

static const stwuct snd_kcontwow_new mtk_dai_i2s_contwows[] = {
	SOC_ENUM_EXT(MTK_AFE_I2S0_KCONTWOW_NAME, mt8183_i2s_enum[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S1_KCONTWOW_NAME, mt8183_i2s_enum[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S2_KCONTWOW_NAME, mt8183_i2s_enum[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S3_KCONTWOW_NAME, mt8183_i2s_enum[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S5_KCONTWOW_NAME, mt8183_i2s_enum[0],
		     mt8183_i2s_hd_get, mt8183_i2s_hd_set),
};

/* dai component */
/* intewconnection */
static const stwuct snd_kcontwow_new mtk_i2s3_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN0, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN0, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN0, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN0,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN0,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN0,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s3_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN1, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN1, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN1, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN1,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN1,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN1,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN1,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN1,
				    I_PCM_2_CAP_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s1_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN28, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN28, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN28, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN28,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN28,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN28,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s1_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN29, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN29, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN29, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN29,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN29,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN29,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN29,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN29,
				    I_PCM_2_CAP_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s5_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN30, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN30, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN30, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN30,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN30,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN30,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s5_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN31, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN31, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN31, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN31,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN31,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN31,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN31,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN31,
				    I_PCM_2_CAP_CH2, 1, 0),
};

enum {
	SUPPWY_SEQ_APWW,
	SUPPWY_SEQ_I2S_MCWK_EN,
	SUPPWY_SEQ_I2S_HD_EN,
	SUPPWY_SEQ_I2S_EN,
};

static int mtk_apww_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow,
			  int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (snd_soc_dapm_widget_name_cmp(w, APWW1_W_NAME) == 0)
			mt8183_apww1_enabwe(afe);
		ewse
			mt8183_apww2_enabwe(afe);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (snd_soc_dapm_widget_name_cmp(w, APWW1_W_NAME) == 0)
			mt8183_apww1_disabwe(afe);
		ewse
			mt8183_apww2_disabwe(afe);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_mcwk_en_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow,
			     int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, w->name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8183_mck_enabwe(afe, i2s_pwiv->mcwk_id, i2s_pwiv->mcwk_wate);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		i2s_pwiv->mcwk_wate = 0;
		mt8183_mck_disabwe(afe, i2s_pwiv->mcwk_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget mtk_dai_i2s_widgets[] = {
	SND_SOC_DAPM_MIXEW("I2S1_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s1_ch1_mix,
			   AWWAY_SIZE(mtk_i2s1_ch1_mix)),
	SND_SOC_DAPM_MIXEW("I2S1_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s1_ch2_mix,
			   AWWAY_SIZE(mtk_i2s1_ch2_mix)),

	SND_SOC_DAPM_MIXEW("I2S3_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s3_ch1_mix,
			   AWWAY_SIZE(mtk_i2s3_ch1_mix)),
	SND_SOC_DAPM_MIXEW("I2S3_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s3_ch2_mix,
			   AWWAY_SIZE(mtk_i2s3_ch2_mix)),

	SND_SOC_DAPM_MIXEW("I2S5_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s5_ch1_mix,
			   AWWAY_SIZE(mtk_i2s5_ch1_mix)),
	SND_SOC_DAPM_MIXEW("I2S5_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s5_ch2_mix,
			   AWWAY_SIZE(mtk_i2s5_ch2_mix)),

	/* i2s en*/
	SND_SOC_DAPM_SUPPWY_S("I2S0_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON, I2S_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("I2S1_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON1, I2S_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("I2S2_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON2, I2S_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("I2S3_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON3, I2S_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("I2S5_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON4, I2S5_EN_SFT, 0,
			      NUWW, 0),
	/* i2s hd en */
	SND_SOC_DAPM_SUPPWY_S(I2S0_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON, I2S1_HD_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S1_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON1, I2S2_HD_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S2_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON2, I2S3_HD_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S3_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON3, I2S4_HD_EN_SFT, 0,
			      NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S5_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON4, I2S5_HD_EN_SFT, 0,
			      NUWW, 0),

	/* i2s mcwk en */
	SND_SOC_DAPM_SUPPWY_S(I2S0_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S1_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S2_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S3_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S5_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	/* apww */
	SND_SOC_DAPM_SUPPWY_S(APWW1_W_NAME, SUPPWY_SEQ_APWW,
			      SND_SOC_NOPM, 0, 0,
			      mtk_apww_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(APWW2_W_NAME, SUPPWY_SEQ_APWW,
			      SND_SOC_NOPM, 0, 0,
			      mtk_apww_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static int mtk_afe_i2s_shawe_connect(stwuct snd_soc_dapm_widget *souwce,
				     stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, sink->name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	if (i2s_pwiv->shawe_i2s_id < 0)
		wetuwn 0;

	wetuwn i2s_pwiv->shawe_i2s_id == get_i2s_id_by_name(afe, souwce->name);
}

static int mtk_afe_i2s_hd_connect(stwuct snd_soc_dapm_widget *souwce,
				  stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, sink->name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	if (get_i2s_id_by_name(afe, sink->name) ==
	    get_i2s_id_by_name(afe, souwce->name))
		wetuwn i2s_pwiv->wow_jittew_en;

	/* check if shawe i2s need hd en */
	if (i2s_pwiv->shawe_i2s_id < 0)
		wetuwn 0;

	if (i2s_pwiv->shawe_i2s_id == get_i2s_id_by_name(afe, souwce->name))
		wetuwn i2s_pwiv->wow_jittew_en;

	wetuwn 0;
}

static int mtk_afe_i2s_apww_connect(stwuct snd_soc_dapm_widget *souwce,
				    stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;
	int cuw_apww;
	int i2s_need_apww;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, w->name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	/* which apww */
	cuw_apww = mt8183_get_apww_by_name(afe, souwce->name);

	/* choose APWW fwom i2s wate */
	i2s_need_apww = mt8183_get_apww_by_wate(afe, i2s_pwiv->wate);

	wetuwn (i2s_need_apww == cuw_apww) ? 1 : 0;
}

static int mtk_afe_i2s_mcwk_connect(stwuct snd_soc_dapm_widget *souwce,
				    stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, sink->name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	if (get_i2s_id_by_name(afe, sink->name) ==
	    get_i2s_id_by_name(afe, souwce->name))
		wetuwn (i2s_pwiv->mcwk_wate > 0) ? 1 : 0;

	/* check if shawe i2s need mcwk */
	if (i2s_pwiv->shawe_i2s_id < 0)
		wetuwn 0;

	if (i2s_pwiv->shawe_i2s_id == get_i2s_id_by_name(afe, souwce->name))
		wetuwn (i2s_pwiv->mcwk_wate > 0) ? 1 : 0;

	wetuwn 0;
}

static int mtk_afe_mcwk_apww_connect(stwuct snd_soc_dapm_widget *souwce,
				     stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_dapm_widget *w = sink;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;
	int cuw_apww;

	i2s_pwiv = get_i2s_pwiv_by_name(afe, w->name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn 0;
	}

	/* which apww */
	cuw_apww = mt8183_get_apww_by_name(afe, souwce->name);

	wetuwn (i2s_pwiv->mcwk_apww == cuw_apww) ? 1 : 0;
}

static const stwuct snd_soc_dapm_woute mtk_dai_i2s_woutes[] = {
	/* i2s0 */
	{"I2S0", NUWW, "I2S0_EN"},
	{"I2S0", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},

	{"I2S0", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S0_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S0_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S0", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S0_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S0_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s1 */
	{"I2S1_CH1", "DW1_CH1", "DW1"},
	{"I2S1_CH2", "DW1_CH2", "DW1"},

	{"I2S1_CH1", "DW2_CH1", "DW2"},
	{"I2S1_CH2", "DW2_CH2", "DW2"},

	{"I2S1_CH1", "DW3_CH1", "DW3"},
	{"I2S1_CH2", "DW3_CH2", "DW3"},

	{"I2S1", NUWW, "I2S1_CH1"},
	{"I2S1", NUWW, "I2S1_CH2"},

	{"I2S1", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S1_EN"},
	{"I2S1", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},

	{"I2S1", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S1_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S1_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S1", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S1_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S1_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s2 */
	{"I2S2", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S2_EN"},
	{"I2S2", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},

	{"I2S2", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S2_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S2_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S2", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S2_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S2_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s3 */
	{"I2S3_CH1", "DW1_CH1", "DW1"},
	{"I2S3_CH2", "DW1_CH2", "DW1"},

	{"I2S3_CH1", "DW2_CH1", "DW2"},
	{"I2S3_CH2", "DW2_CH2", "DW2"},

	{"I2S3_CH1", "DW3_CH1", "DW3"},
	{"I2S3_CH2", "DW3_CH2", "DW3"},

	{"I2S3", NUWW, "I2S3_CH1"},
	{"I2S3", NUWW, "I2S3_CH2"},

	{"I2S3", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S3_EN"},
	{"I2S3", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},

	{"I2S3", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S3_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S3_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S3", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S3_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S3_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s5 */
	{"I2S5_CH1", "DW1_CH1", "DW1"},
	{"I2S5_CH2", "DW1_CH2", "DW1"},

	{"I2S5_CH1", "DW2_CH1", "DW2"},
	{"I2S5_CH2", "DW2_CH2", "DW2"},

	{"I2S5_CH1", "DW3_CH1", "DW3"},
	{"I2S5_CH2", "DW3_CH2", "DW3"},

	{"I2S5", NUWW, "I2S5_CH1"},
	{"I2S5", NUWW, "I2S5_CH2"},

	{"I2S5", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S5_EN"},

	{"I2S5", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S5_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S5_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S5", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S5_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S5_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},
};

/* dai ops */
static int mtk_dai_i2s_config(stwuct mtk_base_afe *afe,
			      stwuct snd_pcm_hw_pawams *pawams,
			      int i2s_id)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv = afe_pwiv->dai_pwiv[i2s_id];

	unsigned int wate = pawams_wate(pawams);
	unsigned int wate_weg = mt8183_wate_twansfowm(afe->dev,
						      wate, i2s_id);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int i2s_con = 0, fmt_con = I2S_FMT_I2S << I2S_FMT_SFT;
	int wet = 0;

	if (i2s_pwiv) {
		i2s_pwiv->wate = wate;

		if (i2s_pwiv->use_eiaj)
			fmt_con = I2S_FMT_EIAJ << I2S_FMT_SFT;
	} ewse {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
	}

	switch (i2s_id) {
	case MT8183_DAI_I2S_0:
		wegmap_update_bits(afe->wegmap, AFE_DAC_CON1,
				   I2S_MODE_MASK_SFT, wate_weg << I2S_MODE_SFT);
		i2s_con = I2S_IN_PAD_IO_MUX << I2SIN_PAD_SEW_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wwen(fowmat) << I2S_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8183_DAI_I2S_1:
		i2s_con = I2S1_SEW_O28_O29 << I2S2_SEW_O03_O04_SFT;
		i2s_con |= wate_weg << I2S2_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wwen(fowmat) << I2S2_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON1,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8183_DAI_I2S_2:
		i2s_con = 8 << I2S3_UPDATE_WOWD_SFT;
		i2s_con |= wate_weg << I2S3_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wwen(fowmat) << I2S3_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON2,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8183_DAI_I2S_3:
		i2s_con = wate_weg << I2S4_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wwen(fowmat) << I2S4_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON3,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8183_DAI_I2S_5:
		i2s_con = wate_weg << I2S5_OUT_MODE_SFT;
		i2s_con |= fmt_con;
		i2s_con |= get_i2s_wwen(fowmat) << I2S5_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON4,
				   0xffffeffe, i2s_con);
		bweak;
	defauwt:
		dev_wawn(afe->dev, "%s(), id %d not suppowt\n",
			 __func__, i2s_id);
		wetuwn -EINVAW;
	}

	/* set shawe i2s */
	if (i2s_pwiv && i2s_pwiv->shawe_i2s_id >= 0)
		wet = mtk_dai_i2s_config(afe, pawams, i2s_pwiv->shawe_i2s_id);

	wetuwn wet;
}

static int mtk_dai_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);

	wetuwn mtk_dai_i2s_config(afe, pawams, dai->id);
}

static int mtk_dai_i2s_set_syscwk(stwuct snd_soc_dai *dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct mtk_base_afe *afe = dev_get_dwvdata(dai->dev);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv = afe_pwiv->dai_pwiv[dai->id];
	int apww;
	int apww_wate;

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	if (diw != SND_SOC_CWOCK_OUT) {
		dev_wawn(afe->dev, "%s(), diw != SND_SOC_CWOCK_OUT", __func__);
		wetuwn -EINVAW;
	}

	apww = mt8183_get_apww_by_wate(afe, fweq);
	apww_wate = mt8183_get_apww_wate(afe, apww);

	if (fweq > apww_wate) {
		dev_wawn(afe->dev, "%s(), fweq > apww wate", __func__);
		wetuwn -EINVAW;
	}

	if (apww_wate % fweq != 0) {
		dev_wawn(afe->dev, "%s(), APWW cannot genewate fweq Hz",
			 __func__);
		wetuwn -EINVAW;
	}

	i2s_pwiv->mcwk_wate = fweq;
	i2s_pwiv->mcwk_apww = apww;

	if (i2s_pwiv->shawe_i2s_id > 0) {
		stwuct mtk_afe_i2s_pwiv *shawe_i2s_pwiv;

		shawe_i2s_pwiv = afe_pwiv->dai_pwiv[i2s_pwiv->shawe_i2s_id];
		if (!shawe_i2s_pwiv) {
			dev_wawn(afe->dev, "%s(), shawe_i2s_pwiv == NUWW",
				 __func__);
			wetuwn -EINVAW;
		}

		shawe_i2s_pwiv->mcwk_wate = i2s_pwiv->mcwk_wate;
		shawe_i2s_pwiv->mcwk_apww = i2s_pwiv->mcwk_apww;
	}

	wetuwn 0;
}

static int mtk_dai_i2s_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;

	switch (dai->id) {
	case MT8183_DAI_I2S_0:
	case MT8183_DAI_I2S_1:
	case MT8183_DAI_I2S_2:
	case MT8183_DAI_I2S_3:
	case MT8183_DAI_I2S_5:
		bweak;
	defauwt:
		dev_wawn(afe->dev, "%s(), id %d not suppowt\n",
			 __func__, dai->id);
		wetuwn -EINVAW;
	}
	i2s_pwiv = afe_pwiv->dai_pwiv[dai->id];

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WEFT_J:
		i2s_pwiv->use_eiaj = 1;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		i2s_pwiv->use_eiaj = 0;
		bweak;
	defauwt:
		dev_wawn(afe->dev, "%s(), DAI fowmat %d not suppowt\n",
			 __func__, fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_i2s_ops = {
	.hw_pawams = mtk_dai_i2s_hw_pawams,
	.set_syscwk = mtk_dai_i2s_set_syscwk,
	.set_fmt = mtk_dai_i2s_set_fmt,
};

/* dai dwivew */
#define MTK_I2S_WATES (SNDWV_PCM_WATE_8000_48000 |\
		       SNDWV_PCM_WATE_88200 |\
		       SNDWV_PCM_WATE_96000 |\
		       SNDWV_PCM_WATE_176400 |\
		       SNDWV_PCM_WATE_192000)

#define MTK_I2S_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew mtk_dai_i2s_dwivew[] = {
	{
		.name = "I2S0",
		.id = MT8183_DAI_I2S_0,
		.captuwe = {
			.stweam_name = "I2S0",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S1",
		.id = MT8183_DAI_I2S_1,
		.pwayback = {
			.stweam_name = "I2S1",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S2",
		.id = MT8183_DAI_I2S_2,
		.captuwe = {
			.stweam_name = "I2S2",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S3",
		.id = MT8183_DAI_I2S_3,
		.pwayback = {
			.stweam_name = "I2S3",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S5",
		.id = MT8183_DAI_I2S_5,
		.pwayback = {
			.stweam_name = "I2S5",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
};

/* this enum is mewewy fow mtk_afe_i2s_pwiv decwawe */
enum {
	DAI_I2S0 = 0,
	DAI_I2S1,
	DAI_I2S2,
	DAI_I2S3,
	DAI_I2S5,
	DAI_I2S_NUM,
};

static const stwuct mtk_afe_i2s_pwiv mt8183_i2s_pwiv[DAI_I2S_NUM] = {
	[DAI_I2S0] = {
		.id = MT8183_DAI_I2S_0,
		.mcwk_id = MT8183_I2S0_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S1] = {
		.id = MT8183_DAI_I2S_1,
		.mcwk_id = MT8183_I2S1_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S2] = {
		.id = MT8183_DAI_I2S_2,
		.mcwk_id = MT8183_I2S2_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S3] = {
		.id = MT8183_DAI_I2S_3,
		.mcwk_id = MT8183_I2S3_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S5] = {
		.id = MT8183_DAI_I2S_5,
		.mcwk_id = MT8183_I2S5_MCK,
		.shawe_i2s_id = -1,
	},
};

/**
 * mt8183_dai_i2s_set_shawe() - Set up I2S powts to shawe a singwe cwock.
 * @afe: Pointew to &stwuct mtk_base_afe
 * @main_i2s_name: The name of the I2S powt that wiww pwovide the cwock
 * @secondawy_i2s_name: The name of the I2S powt that wiww use this cwock
 */
int mt8183_dai_i2s_set_shawe(stwuct mtk_base_afe *afe, const chaw *main_i2s_name,
			     const chaw *secondawy_i2s_name)
{
	stwuct mtk_afe_i2s_pwiv *secondawy_i2s_pwiv;
	int main_i2s_id;

	secondawy_i2s_pwiv = get_i2s_pwiv_by_name(afe, secondawy_i2s_name);
	if (!secondawy_i2s_pwiv)
		wetuwn -EINVAW;

	main_i2s_id = get_i2s_id_by_name(afe, main_i2s_name);
	if (main_i2s_id < 0)
		wetuwn main_i2s_id;

	secondawy_i2s_pwiv->shawe_i2s_id = main_i2s_id;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt8183_dai_i2s_set_shawe);

static int mt8183_dai_i2s_set_pwiv(stwuct mtk_base_afe *afe)
{
	stwuct mt8183_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;
	int i;

	fow (i = 0; i < DAI_I2S_NUM; i++) {
		i2s_pwiv = devm_kzawwoc(afe->dev,
					sizeof(stwuct mtk_afe_i2s_pwiv),
					GFP_KEWNEW);
		if (!i2s_pwiv)
			wetuwn -ENOMEM;

		memcpy(i2s_pwiv, &mt8183_i2s_pwiv[i],
		       sizeof(stwuct mtk_afe_i2s_pwiv));

		afe_pwiv->dai_pwiv[mt8183_i2s_pwiv[i].id] = i2s_pwiv;
	}

	wetuwn 0;
}

int mt8183_dai_i2s_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;
	int wet;

	dai = devm_kzawwoc(afe->dev, sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	wist_add(&dai->wist, &afe->sub_dais);

	dai->dai_dwivews = mtk_dai_i2s_dwivew;
	dai->num_dai_dwivews = AWWAY_SIZE(mtk_dai_i2s_dwivew);

	dai->contwows = mtk_dai_i2s_contwows;
	dai->num_contwows = AWWAY_SIZE(mtk_dai_i2s_contwows);
	dai->dapm_widgets = mtk_dai_i2s_widgets;
	dai->num_dapm_widgets = AWWAY_SIZE(mtk_dai_i2s_widgets);
	dai->dapm_woutes = mtk_dai_i2s_woutes;
	dai->num_dapm_woutes = AWWAY_SIZE(mtk_dai_i2s_woutes);

	/* set aww dai i2s pwivate data */
	wet = mt8183_dai_i2s_set_pwiv(afe);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
