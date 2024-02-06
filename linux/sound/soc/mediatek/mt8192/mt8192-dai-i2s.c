// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio DAI I2S Contwow
//
// Copywight (c) 2020 MediaTek Inc.
// Authow: Shane Chien <shane.chien@mediatek.com>
//

#incwude <winux/bitops.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>

#incwude "mt8192-afe-cwk.h"
#incwude "mt8192-afe-common.h"
#incwude "mt8192-afe-gpio.h"
#incwude "mt8192-intewconnection.h"

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
#define MTK_AFE_I2S6_KCONTWOW_NAME "I2S6_HD_Mux"
#define MTK_AFE_I2S7_KCONTWOW_NAME "I2S7_HD_Mux"
#define MTK_AFE_I2S8_KCONTWOW_NAME "I2S8_HD_Mux"
#define MTK_AFE_I2S9_KCONTWOW_NAME "I2S9_HD_Mux"

#define I2S0_HD_EN_W_NAME "I2S0_HD_EN"
#define I2S1_HD_EN_W_NAME "I2S1_HD_EN"
#define I2S2_HD_EN_W_NAME "I2S2_HD_EN"
#define I2S3_HD_EN_W_NAME "I2S3_HD_EN"
#define I2S5_HD_EN_W_NAME "I2S5_HD_EN"
#define I2S6_HD_EN_W_NAME "I2S6_HD_EN"
#define I2S7_HD_EN_W_NAME "I2S7_HD_EN"
#define I2S8_HD_EN_W_NAME "I2S8_HD_EN"
#define I2S9_HD_EN_W_NAME "I2S9_HD_EN"

#define I2S0_MCWK_EN_W_NAME "I2S0_MCWK_EN"
#define I2S1_MCWK_EN_W_NAME "I2S1_MCWK_EN"
#define I2S2_MCWK_EN_W_NAME "I2S2_MCWK_EN"
#define I2S3_MCWK_EN_W_NAME "I2S3_MCWK_EN"
#define I2S5_MCWK_EN_W_NAME "I2S5_MCWK_EN"
#define I2S6_MCWK_EN_W_NAME "I2S6_MCWK_EN"
#define I2S7_MCWK_EN_W_NAME "I2S7_MCWK_EN"
#define I2S8_MCWK_EN_W_NAME "I2S8_MCWK_EN"
#define I2S9_MCWK_EN_W_NAME "I2S9_MCWK_EN"

static int get_i2s_id_by_name(stwuct mtk_base_afe *afe,
			      const chaw *name)
{
	if (stwncmp(name, "I2S0", 4) == 0)
		wetuwn MT8192_DAI_I2S_0;
	ewse if (stwncmp(name, "I2S1", 4) == 0)
		wetuwn MT8192_DAI_I2S_1;
	ewse if (stwncmp(name, "I2S2", 4) == 0)
		wetuwn MT8192_DAI_I2S_2;
	ewse if (stwncmp(name, "I2S3", 4) == 0)
		wetuwn MT8192_DAI_I2S_3;
	ewse if (stwncmp(name, "I2S5", 4) == 0)
		wetuwn MT8192_DAI_I2S_5;
	ewse if (stwncmp(name, "I2S6", 4) == 0)
		wetuwn MT8192_DAI_I2S_6;
	ewse if (stwncmp(name, "I2S7", 4) == 0)
		wetuwn MT8192_DAI_I2S_7;
	ewse if (stwncmp(name, "I2S8", 4) == 0)
		wetuwn MT8192_DAI_I2S_8;
	ewse if (stwncmp(name, "I2S9", 4) == 0)
		wetuwn MT8192_DAI_I2S_9;
	ewse
		wetuwn -EINVAW;
}

static stwuct mtk_afe_i2s_pwiv *get_i2s_pwiv_by_name(stwuct mtk_base_afe *afe,
						     const chaw *name)
{
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int dai_id = get_i2s_id_by_name(afe, name);

	if (dai_id < 0)
		wetuwn NUWW;

	wetuwn afe_pwiv->dai_pwiv[dai_id];
}

/* wow jittew contwow */
static const chaw * const mt8192_i2s_hd_stw[] = {
	"Nowmaw", "Wow_Jittew"
};

static SOC_ENUM_SINGWE_EXT_DECW(mt8192_i2s_enum, mt8192_i2s_hd_stw);

static int mt8192_i2s_hd_get(stwuct snd_kcontwow *kcontwow,
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

static int mt8192_i2s_hd_set(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv;
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	int hd_en;

	if (ucontwow->vawue.enumewated.item[0] >= e->items)
		wetuwn -EINVAW;

	hd_en = ucontwow->vawue.integew.vawue[0];

	dev_dbg(afe->dev, "%s(), kcontwow name %s, hd_en %d\n",
		__func__, kcontwow->id.name, hd_en);

	i2s_pwiv = get_i2s_pwiv_by_name(afe, kcontwow->id.name);

	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	i2s_pwiv->wow_jittew_en = hd_en;

	wetuwn 0;
}

static const stwuct snd_kcontwow_new mtk_dai_i2s_contwows[] = {
	SOC_ENUM_EXT(MTK_AFE_I2S0_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S1_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S2_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S3_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S5_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S6_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S7_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S8_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
	SOC_ENUM_EXT(MTK_AFE_I2S9_KCONTWOW_NAME, mt8192_i2s_enum,
		     mt8192_i2s_hd_get, mt8192_i2s_hd_set),
};

/* dai component */
/* i2s viwtuaw mux to output widget */
static const chaw * const i2s_mux_map[] = {
	"Nowmaw", "Dummy_Widget",
};

static int i2s_mux_map_vawue[] = {
	0, 1,
};

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(i2s_mux_map_enum,
					      SND_SOC_NOPM,
					      0,
					      1,
					      i2s_mux_map,
					      i2s_mux_map_vawue);

static const stwuct snd_kcontwow_new i2s0_in_mux_contwow =
	SOC_DAPM_ENUM("I2S0 In Sewect", i2s_mux_map_enum);

static const stwuct snd_kcontwow_new i2s8_in_mux_contwow =
	SOC_DAPM_ENUM("I2S8 In Sewect", i2s_mux_map_enum);

static const stwuct snd_kcontwow_new i2s1_out_mux_contwow =
	SOC_DAPM_ENUM("I2S1 Out Sewect", i2s_mux_map_enum);

static const stwuct snd_kcontwow_new i2s3_out_mux_contwow =
	SOC_DAPM_ENUM("I2S3 Out Sewect", i2s_mux_map_enum);

static const stwuct snd_kcontwow_new i2s5_out_mux_contwow =
	SOC_DAPM_ENUM("I2S5 Out Sewect", i2s_mux_map_enum);

static const stwuct snd_kcontwow_new i2s7_out_mux_contwow =
	SOC_DAPM_ENUM("I2S7 Out Sewect", i2s_mux_map_enum);

static const stwuct snd_kcontwow_new i2s9_out_mux_contwow =
	SOC_DAPM_ENUM("I2S9 Out Sewect", i2s_mux_map_enum);

/* Tinyconn Mux */
enum {
	TINYCONN_CH1_MUX_DW1 = 0x0,
	TINYCONN_CH2_MUX_DW1 = 0x1,
	TINYCONN_CH1_MUX_DW12 = 0x2,
	TINYCONN_CH2_MUX_DW12 = 0x3,
	TINYCONN_CH1_MUX_DW2 = 0x4,
	TINYCONN_CH2_MUX_DW2 = 0x5,
	TINYCONN_CH1_MUX_DW3 = 0x6,
	TINYCONN_CH2_MUX_DW3 = 0x7,
	TINYCONN_MUX_NONE = 0x1f,
};

static const chaw * const tinyconn_mux_map[] = {
	"NONE",
	"DW1_CH1",
	"DW1_CH2",
	"DW12_CH1",
	"DW12_CH2",
	"DW2_CH1",
	"DW2_CH2",
	"DW3_CH1",
	"DW3_CH2",
};

static int tinyconn_mux_map_vawue[] = {
	TINYCONN_MUX_NONE,
	TINYCONN_CH1_MUX_DW1,
	TINYCONN_CH2_MUX_DW1,
	TINYCONN_CH1_MUX_DW12,
	TINYCONN_CH2_MUX_DW12,
	TINYCONN_CH1_MUX_DW2,
	TINYCONN_CH2_MUX_DW2,
	TINYCONN_CH1_MUX_DW3,
	TINYCONN_CH2_MUX_DW3,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(i2s1_tinyconn_ch1_mux_map_enum,
				  AFE_TINY_CONN5,
				  O_20_CFG_SFT,
				  O_20_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_vawue);
static const stwuct snd_kcontwow_new i2s1_tinyconn_ch1_mux_contwow =
	SOC_DAPM_ENUM("i2s1 ch1 tinyconn Sewect",
		      i2s1_tinyconn_ch1_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(i2s1_tinyconn_ch2_mux_map_enum,
				  AFE_TINY_CONN5,
				  O_21_CFG_SFT,
				  O_21_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_vawue);
static const stwuct snd_kcontwow_new i2s1_tinyconn_ch2_mux_contwow =
	SOC_DAPM_ENUM("i2s1 ch2 tinyconn Sewect",
		      i2s1_tinyconn_ch2_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(i2s3_tinyconn_ch1_mux_map_enum,
				  AFE_TINY_CONN5,
				  O_22_CFG_SFT,
				  O_22_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_vawue);
static const stwuct snd_kcontwow_new i2s3_tinyconn_ch1_mux_contwow =
	SOC_DAPM_ENUM("i2s3 ch1 tinyconn Sewect",
		      i2s3_tinyconn_ch1_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(i2s3_tinyconn_ch2_mux_map_enum,
				  AFE_TINY_CONN5,
				  O_23_CFG_SFT,
				  O_23_CFG_MASK,
				  tinyconn_mux_map,
				  tinyconn_mux_map_vawue);
static const stwuct snd_kcontwow_new i2s3_tinyconn_ch2_mux_contwow =
	SOC_DAPM_ENUM("i2s3 ch2 tinyconn Sewect",
		      i2s3_tinyconn_ch2_mux_map_enum);

/* i2s in wpbk */
static const chaw * const i2s_wpbk_mux_map[] = {
	"Nowmaw", "Wpbk",
};

static int i2s_wpbk_mux_map_vawue[] = {
	0, 1,
};

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(i2s0_wpbk_mux_map_enum,
					      AFE_I2S_CON,
					      I2S_WOOPBACK_SFT,
					      1,
					      i2s_wpbk_mux_map,
					      i2s_wpbk_mux_map_vawue);

static const stwuct snd_kcontwow_new i2s0_wpbk_mux_contwow =
	SOC_DAPM_ENUM("I2S Wpbk Sewect", i2s0_wpbk_mux_map_enum);

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(i2s2_wpbk_mux_map_enum,
					      AFE_I2S_CON2,
					      I2S3_WOOPBACK_SFT,
					      1,
					      i2s_wpbk_mux_map,
					      i2s_wpbk_mux_map_vawue);

static const stwuct snd_kcontwow_new i2s2_wpbk_mux_contwow =
	SOC_DAPM_ENUM("I2S Wpbk Sewect", i2s2_wpbk_mux_map_enum);

/* intewconnection */
static const stwuct snd_kcontwow_new mtk_i2s3_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN0, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN0, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN0, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN0, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN0_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN0_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN0_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH1", AFE_CONN0_1, I_DW8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH1", AFE_CONN0_1, I_DW9_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN0,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN0,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN0,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN0,
				    I_ADDA_UW_CH3, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN0,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN0,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s3_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN1, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN1, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN1, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN1, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN1_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN1_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN1_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH2", AFE_CONN1_1, I_DW8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH2", AFE_CONN1_1, I_DW9_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN1,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN1,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN1,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH3", AFE_CONN1,
				    I_ADDA_UW_CH3, 1, 0),
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
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN28, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN28_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN28_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN28_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH1", AFE_CONN28_1, I_DW8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH1", AFE_CONN28_1, I_DW9_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN28,
				    I_GAIN1_OUT_CH1, 1, 0),
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
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN29, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN29_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN29_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN29_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH2", AFE_CONN29_1, I_DW8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH2", AFE_CONN29_1, I_DW9_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN29,
				    I_GAIN1_OUT_CH2, 1, 0),
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
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN30, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN30_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN30_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN30_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH1", AFE_CONN30_1, I_DW8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH1", AFE_CONN30_1, I_DW9_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN30,
				    I_GAIN1_OUT_CH1, 1, 0),
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
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN31, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN31_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN31_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN31_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH2", AFE_CONN31_1, I_DW8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH2", AFE_CONN31_1, I_DW9_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN31,
				    I_GAIN1_OUT_CH2, 1, 0),
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

static const stwuct snd_kcontwow_new mtk_i2s7_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN54, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN54, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN54, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN54, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN54_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN54_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN54_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH1", AFE_CONN54_1, I_DW9_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN54,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN54,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN54,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN54,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s7_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN55, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN55, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN55, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN55, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN55_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN55_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN55_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH2", AFE_CONN55_1, I_DW9_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN55,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN55,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN55,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN55,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN55,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN55,
				    I_PCM_2_CAP_CH2, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s9_ch1_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH1", AFE_CONN56, I_DW1_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH1", AFE_CONN56, I_DW2_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH1", AFE_CONN56, I_DW3_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH1", AFE_CONN56, I_DW12_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH1", AFE_CONN56_1, I_DW6_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH1", AFE_CONN56_1, I_DW4_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH1", AFE_CONN56_1, I_DW5_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH1", AFE_CONN56_1, I_DW8_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH1", AFE_CONN56_1, I_DW9_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH1", AFE_CONN56,
				    I_GAIN1_OUT_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH1", AFE_CONN56,
				    I_ADDA_UW_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN56,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN56,
				    I_PCM_2_CAP_CH1, 1, 0),
};

static const stwuct snd_kcontwow_new mtk_i2s9_ch2_mix[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("DW1_CH2", AFE_CONN57, I_DW1_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW2_CH2", AFE_CONN57, I_DW2_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW3_CH2", AFE_CONN57, I_DW3_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW12_CH2", AFE_CONN57, I_DW12_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW6_CH2", AFE_CONN57_1, I_DW6_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW4_CH2", AFE_CONN57_1, I_DW4_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW5_CH2", AFE_CONN57_1, I_DW5_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW8_CH2", AFE_CONN57_1, I_DW8_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("DW9_CH2", AFE_CONN57_1, I_DW9_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("GAIN1_OUT_CH2", AFE_CONN57,
				    I_GAIN1_OUT_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("ADDA_UW_CH2", AFE_CONN57,
				    I_ADDA_UW_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH1", AFE_CONN57,
				    I_PCM_1_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH1", AFE_CONN57,
				    I_PCM_2_CAP_CH1, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_1_CAP_CH2", AFE_CONN57,
				    I_PCM_1_CAP_CH2, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("PCM_2_CAP_CH2", AFE_CONN57,
				    I_PCM_2_CAP_CH2, 1, 0),
};

enum {
	SUPPWY_SEQ_APWW,
	SUPPWY_SEQ_I2S_MCWK_EN,
	SUPPWY_SEQ_I2S_HD_EN,
	SUPPWY_SEQ_I2S_EN,
};

static int mtk_i2s_en_event(stwuct snd_soc_dapm_widget *w,
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

	dev_dbg(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8192_afe_gpio_wequest(afe->dev, twue, i2s_pwiv->id, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		mt8192_afe_gpio_wequest(afe->dev, fawse, i2s_pwiv->id, 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mtk_apww_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow,
			  int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);

	dev_dbg(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (snd_soc_dapm_widget_name_cmp(w, APWW1_W_NAME) == 0)
			mt8192_apww1_enabwe(afe);
		ewse
			mt8192_apww2_enabwe(afe);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (snd_soc_dapm_widget_name_cmp(w, APWW1_W_NAME) == 0)
			mt8192_apww1_disabwe(afe);
		ewse
			mt8192_apww2_disabwe(afe);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int i2s_out_tinyconn_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow,
				  int event)
{
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt);
	unsigned int weg;
	unsigned int weg_shift;
	unsigned int weg_mask_shift;

	dev_dbg(afe->dev, "%s(), event 0x%x\n", __func__, event);

	if (stwstw(w->name, "I2S1")) {
		weg = AFE_I2S_CON1;
		weg_shift = I2S2_32BIT_EN_SFT;
		weg_mask_shift = I2S2_32BIT_EN_MASK_SFT;
	} ewse if (stwstw(w->name, "I2S3")) {
		weg = AFE_I2S_CON3;
		weg_shift = I2S4_32BIT_EN_SFT;
		weg_mask_shift = I2S4_32BIT_EN_MASK_SFT;
	} ewse if (stwstw(w->name, "I2S5")) {
		weg = AFE_I2S_CON4;
		weg_shift = I2S5_32BIT_EN_SFT;
		weg_mask_shift = I2S5_32BIT_EN_MASK_SFT;
	} ewse if (stwstw(w->name, "I2S7")) {
		weg = AFE_I2S_CON7;
		weg_shift = I2S7_32BIT_EN_SFT;
		weg_mask_shift = I2S7_32BIT_EN_MASK_SFT;
	} ewse if (stwstw(w->name, "I2S9")) {
		weg = AFE_I2S_CON9;
		weg_shift = I2S9_32BIT_EN_SFT;
		weg_mask_shift = I2S9_32BIT_EN_MASK_SFT;
	} ewse {
		weg = AFE_I2S_CON1;
		weg_shift = I2S2_32BIT_EN_SFT;
		weg_mask_shift = I2S2_32BIT_EN_MASK_SFT;
		dev_wawn(afe->dev, "%s(), ewwow widget name %s, use i2s1\n",
			 __func__, w->name);
	}

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wegmap_update_bits(afe->wegmap, weg, weg_mask_shift,
				   0x1 << weg_shift);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(afe->wegmap, weg, weg_mask_shift,
				   0x0 << weg_shift);
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

	dev_dbg(cmpnt->dev, "%s(), name %s, event 0x%x\n",
		__func__, w->name, event);

	i2s_pwiv = get_i2s_pwiv_by_name(afe, w->name);
	if (!i2s_pwiv) {
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);
		wetuwn -EINVAW;
	}

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		mt8192_mck_enabwe(afe, i2s_pwiv->mcwk_id, i2s_pwiv->mcwk_wate);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		i2s_pwiv->mcwk_wate = 0;
		mt8192_mck_disabwe(afe, i2s_pwiv->mcwk_id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget mtk_dai_i2s_widgets[] = {
	SND_SOC_DAPM_INPUT("CONNSYS"),

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

	SND_SOC_DAPM_MIXEW("I2S7_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s7_ch1_mix,
			   AWWAY_SIZE(mtk_i2s7_ch1_mix)),
	SND_SOC_DAPM_MIXEW("I2S7_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s7_ch2_mix,
			   AWWAY_SIZE(mtk_i2s7_ch2_mix)),

	SND_SOC_DAPM_MIXEW("I2S9_CH1", SND_SOC_NOPM, 0, 0,
			   mtk_i2s9_ch1_mix,
			   AWWAY_SIZE(mtk_i2s9_ch1_mix)),
	SND_SOC_DAPM_MIXEW("I2S9_CH2", SND_SOC_NOPM, 0, 0,
			   mtk_i2s9_ch2_mix,
			   AWWAY_SIZE(mtk_i2s9_ch2_mix)),

	SND_SOC_DAPM_MUX_E("I2S1_TINYCONN_CH1_MUX", SND_SOC_NOPM, 0, 0,
			   &i2s1_tinyconn_ch1_mux_contwow,
			   i2s_out_tinyconn_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX_E("I2S1_TINYCONN_CH2_MUX", SND_SOC_NOPM, 0, 0,
			   &i2s1_tinyconn_ch2_mux_contwow,
			   i2s_out_tinyconn_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX_E("I2S3_TINYCONN_CH1_MUX", SND_SOC_NOPM, 0, 0,
			   &i2s3_tinyconn_ch1_mux_contwow,
			   i2s_out_tinyconn_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX_E("I2S3_TINYCONN_CH2_MUX", SND_SOC_NOPM, 0, 0,
			   &i2s3_tinyconn_ch2_mux_contwow,
			   i2s_out_tinyconn_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),

	/* i2s en*/
	SND_SOC_DAPM_SUPPWY_S("I2S0_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON, I2S_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S1_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON1, I2S_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S2_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON2, I2S_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S3_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON3, I2S_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S5_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON4, I2S5_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S6_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON6, I2S6_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S7_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON7, I2S7_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S8_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON8, I2S8_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S("I2S9_EN", SUPPWY_SEQ_I2S_EN,
			      AFE_I2S_CON9, I2S9_EN_SFT, 0,
			      mtk_i2s_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	/* i2s hd en */
	SND_SOC_DAPM_SUPPWY_S(I2S0_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON, I2S1_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S1_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON1, I2S2_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S2_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON2, I2S3_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S3_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON3, I2S4_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S5_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON4, I2S5_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S6_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON6, I2S6_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S7_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON7, I2S7_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S8_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON8, I2S8_HD_EN_SFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S(I2S9_HD_EN_W_NAME, SUPPWY_SEQ_I2S_HD_EN,
			      AFE_I2S_CON9, I2S9_HD_EN_SFT, 0, NUWW, 0),

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
	SND_SOC_DAPM_SUPPWY_S(I2S6_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S7_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S8_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
			      SND_SOC_NOPM, 0, 0,
			      mtk_mcwk_en_event,
			      SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY_S(I2S9_MCWK_EN_W_NAME, SUPPWY_SEQ_I2S_MCWK_EN,
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

	/* awwow i2s on without codec on */
	SND_SOC_DAPM_OUTPUT("I2S_DUMMY_OUT"),
	SND_SOC_DAPM_MUX("I2S1_Out_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s1_out_mux_contwow),
	SND_SOC_DAPM_MUX("I2S3_Out_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s3_out_mux_contwow),
	SND_SOC_DAPM_MUX("I2S5_Out_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s5_out_mux_contwow),
	SND_SOC_DAPM_MUX("I2S7_Out_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s7_out_mux_contwow),
	SND_SOC_DAPM_MUX("I2S9_Out_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s9_out_mux_contwow),

	SND_SOC_DAPM_INPUT("I2S_DUMMY_IN"),
	SND_SOC_DAPM_MUX("I2S0_In_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s0_in_mux_contwow),
	SND_SOC_DAPM_MUX("I2S8_In_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s8_in_mux_contwow),

	/* i2s in wpbk */
	SND_SOC_DAPM_MUX("I2S0_Wpbk_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s0_wpbk_mux_contwow),
	SND_SOC_DAPM_MUX("I2S2_Wpbk_Mux",
			 SND_SOC_NOPM, 0, 0, &i2s2_wpbk_mux_contwow),
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
	cuw_apww = mt8192_get_apww_by_name(afe, souwce->name);

	/* choose APWW fwom i2s wate */
	i2s_need_apww = mt8192_get_apww_by_wate(afe, i2s_pwiv->wate);

	if (i2s_need_apww == cuw_apww)
		wetuwn 1;

	wetuwn 0;
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
	cuw_apww = mt8192_get_apww_by_name(afe, souwce->name);

	if (i2s_pwiv->mcwk_apww == cuw_apww)
		wetuwn 1;

	wetuwn 0;
}

static const stwuct snd_soc_dapm_woute mtk_dai_i2s_woutes[] = {
	{"Connsys I2S", NUWW, "CONNSYS"},

	/* i2s0 */
	{"I2S0", NUWW, "I2S0_EN"},
	{"I2S0", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S0", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S0", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S0", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S0_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S0_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S0", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S0", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S0_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S0_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s1 */
	{"I2S1_CH1", "DW1_CH1", "DW1"},
	{"I2S1_CH2", "DW1_CH2", "DW1"},
	{"I2S1_TINYCONN_CH1_MUX", "DW1_CH1", "DW1"},
	{"I2S1_TINYCONN_CH2_MUX", "DW1_CH2", "DW1"},

	{"I2S1_CH1", "DW2_CH1", "DW2"},
	{"I2S1_CH2", "DW2_CH2", "DW2"},
	{"I2S1_TINYCONN_CH1_MUX", "DW2_CH1", "DW2"},
	{"I2S1_TINYCONN_CH2_MUX", "DW2_CH2", "DW2"},

	{"I2S1_CH1", "DW3_CH1", "DW3"},
	{"I2S1_CH2", "DW3_CH2", "DW3"},
	{"I2S1_TINYCONN_CH1_MUX", "DW3_CH1", "DW3"},
	{"I2S1_TINYCONN_CH2_MUX", "DW3_CH2", "DW3"},

	{"I2S1_CH1", "DW12_CH1", "DW12"},
	{"I2S1_CH2", "DW12_CH2", "DW12"},
	{"I2S1_TINYCONN_CH1_MUX", "DW12_CH1", "DW12"},
	{"I2S1_TINYCONN_CH2_MUX", "DW12_CH2", "DW12"},

	{"I2S1_CH1", "DW4_CH1", "DW4"},
	{"I2S1_CH2", "DW4_CH2", "DW4"},

	{"I2S1_CH1", "DW5_CH1", "DW5"},
	{"I2S1_CH2", "DW5_CH2", "DW5"},

	{"I2S1_CH1", "DW6_CH1", "DW6"},
	{"I2S1_CH2", "DW6_CH2", "DW6"},

	{"I2S1_CH1", "DW8_CH1", "DW8"},
	{"I2S1_CH2", "DW8_CH2", "DW8"},

	{"I2S1", NUWW, "I2S1_CH1"},
	{"I2S1", NUWW, "I2S1_CH2"},
	{"I2S1", NUWW, "I2S3_TINYCONN_CH1_MUX"},
	{"I2S1", NUWW, "I2S3_TINYCONN_CH2_MUX"},

	{"I2S1", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S1_EN"},
	{"I2S1", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S1", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S1", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S1", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S1_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S1_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S1", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S1", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S1_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S1_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s2 */
	{"I2S2", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S2_EN"},
	{"I2S2", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S2", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S2", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S2", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S2_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S2_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S2", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S2", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S2_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S2_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s3 */
	{"I2S3_CH1", "DW1_CH1", "DW1"},
	{"I2S3_CH2", "DW1_CH2", "DW1"},
	{"I2S3_TINYCONN_CH1_MUX", "DW1_CH1", "DW1"},
	{"I2S3_TINYCONN_CH2_MUX", "DW1_CH2", "DW1"},

	{"I2S3_CH1", "DW2_CH1", "DW2"},
	{"I2S3_CH2", "DW2_CH2", "DW2"},
	{"I2S3_TINYCONN_CH1_MUX", "DW2_CH1", "DW2"},
	{"I2S3_TINYCONN_CH2_MUX", "DW2_CH2", "DW2"},

	{"I2S3_CH1", "DW3_CH1", "DW3"},
	{"I2S3_CH2", "DW3_CH2", "DW3"},
	{"I2S3_TINYCONN_CH1_MUX", "DW3_CH1", "DW3"},
	{"I2S3_TINYCONN_CH2_MUX", "DW3_CH2", "DW3"},

	{"I2S3_CH1", "DW12_CH1", "DW12"},
	{"I2S3_CH2", "DW12_CH2", "DW12"},
	{"I2S3_TINYCONN_CH1_MUX", "DW12_CH1", "DW12"},
	{"I2S3_TINYCONN_CH2_MUX", "DW12_CH2", "DW12"},

	{"I2S3_CH1", "DW4_CH1", "DW4"},
	{"I2S3_CH2", "DW4_CH2", "DW4"},

	{"I2S3_CH1", "DW5_CH1", "DW5"},
	{"I2S3_CH2", "DW5_CH2", "DW5"},

	{"I2S3_CH1", "DW6_CH1", "DW6"},
	{"I2S3_CH2", "DW6_CH2", "DW6"},

	{"I2S3_CH1", "DW8_CH1", "DW8"},
	{"I2S3_CH2", "DW8_CH2", "DW8"},

	{"I2S3", NUWW, "I2S3_CH1"},
	{"I2S3", NUWW, "I2S3_CH2"},
	{"I2S3", NUWW, "I2S3_TINYCONN_CH1_MUX"},
	{"I2S3", NUWW, "I2S3_TINYCONN_CH2_MUX"},

	{"I2S3", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S3_EN"},
	{"I2S3", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S3", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S3", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S3", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S3_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S3_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S3", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S3", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S3_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S3_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s5 */
	{"I2S5_CH1", "DW1_CH1", "DW1"},
	{"I2S5_CH2", "DW1_CH2", "DW1"},

	{"I2S5_CH1", "DW2_CH1", "DW2"},
	{"I2S5_CH2", "DW2_CH2", "DW2"},

	{"I2S5_CH1", "DW3_CH1", "DW3"},
	{"I2S5_CH2", "DW3_CH2", "DW3"},

	{"I2S5_CH1", "DW12_CH1", "DW12"},
	{"I2S5_CH2", "DW12_CH2", "DW12"},

	{"I2S5_CH1", "DW4_CH1", "DW4"},
	{"I2S5_CH2", "DW4_CH2", "DW4"},

	{"I2S5_CH1", "DW5_CH1", "DW5"},
	{"I2S5_CH2", "DW5_CH2", "DW5"},

	{"I2S5_CH1", "DW6_CH1", "DW6"},
	{"I2S5_CH2", "DW6_CH2", "DW6"},

	{"I2S5_CH1", "DW8_CH1", "DW8"},
	{"I2S5_CH2", "DW8_CH2", "DW8"},

	{"I2S5", NUWW, "I2S5_CH1"},
	{"I2S5", NUWW, "I2S5_CH2"},

	{"I2S5", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S5_EN"},
	{"I2S5", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S5", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S5", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S5", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S5_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S5_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S5", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S5", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S5_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S5_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s6 */
	{"I2S6", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S6_EN"},
	{"I2S6", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S6", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S6", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S6", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S6_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S6_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S6", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S6", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S6_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S6_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s7 */
	{"I2S7", NUWW, "I2S7_CH1"},
	{"I2S7", NUWW, "I2S7_CH2"},

	{"I2S7", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S7_EN"},
	{"I2S7", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S7", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S7", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S7", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S7_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S7_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S7", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S7", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S7_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S7_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s8 */
	{"I2S8", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S8", NUWW, "I2S8_EN"},
	{"I2S8", NUWW, "I2S9_EN", mtk_afe_i2s_shawe_connect},

	{"I2S8", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S8", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S8_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S8_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S8", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S8", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S8_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S8_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* i2s9 */
	{"I2S9_CH1", "DW1_CH1", "DW1"},
	{"I2S9_CH2", "DW1_CH2", "DW1"},

	{"I2S9_CH1", "DW2_CH1", "DW2"},
	{"I2S9_CH2", "DW2_CH2", "DW2"},

	{"I2S9_CH1", "DW3_CH1", "DW3"},
	{"I2S9_CH2", "DW3_CH2", "DW3"},

	{"I2S9_CH1", "DW12_CH1", "DW12"},
	{"I2S9_CH2", "DW12_CH2", "DW12"},

	{"I2S9_CH1", "DW4_CH1", "DW4"},
	{"I2S9_CH2", "DW4_CH2", "DW4"},

	{"I2S9_CH1", "DW5_CH1", "DW5"},
	{"I2S9_CH2", "DW5_CH2", "DW5"},

	{"I2S9_CH1", "DW6_CH1", "DW6"},
	{"I2S9_CH2", "DW6_CH2", "DW6"},

	{"I2S9_CH1", "DW8_CH1", "DW8"},
	{"I2S9_CH2", "DW8_CH2", "DW8"},

	{"I2S9_CH1", "DW9_CH1", "DW9"},
	{"I2S9_CH2", "DW9_CH2", "DW9"},

	{"I2S9", NUWW, "I2S9_CH1"},
	{"I2S9", NUWW, "I2S9_CH2"},

	{"I2S9", NUWW, "I2S0_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S1_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S2_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S3_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S5_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S6_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S7_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S8_EN", mtk_afe_i2s_shawe_connect},
	{"I2S9", NUWW, "I2S9_EN"},

	{"I2S9", NUWW, I2S0_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S1_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S2_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S3_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S5_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S6_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S7_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S8_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{"I2S9", NUWW, I2S9_HD_EN_W_NAME, mtk_afe_i2s_hd_connect},
	{I2S9_HD_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_i2s_apww_connect},
	{I2S9_HD_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_i2s_apww_connect},

	{"I2S9", NUWW, I2S0_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S1_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S2_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S3_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S5_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S6_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S7_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S8_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{"I2S9", NUWW, I2S9_MCWK_EN_W_NAME, mtk_afe_i2s_mcwk_connect},
	{I2S9_MCWK_EN_W_NAME, NUWW, APWW1_W_NAME, mtk_afe_mcwk_apww_connect},
	{I2S9_MCWK_EN_W_NAME, NUWW, APWW2_W_NAME, mtk_afe_mcwk_apww_connect},

	/* awwow i2s on without codec on */
	{"I2S0", NUWW, "I2S0_In_Mux"},
	{"I2S0_In_Mux", "Dummy_Widget", "I2S_DUMMY_IN"},

	{"I2S8", NUWW, "I2S8_In_Mux"},
	{"I2S8_In_Mux", "Dummy_Widget", "I2S_DUMMY_IN"},

	{"I2S1_Out_Mux", "Dummy_Widget", "I2S1"},
	{"I2S_DUMMY_OUT", NUWW, "I2S1_Out_Mux"},

	{"I2S3_Out_Mux", "Dummy_Widget", "I2S3"},
	{"I2S_DUMMY_OUT", NUWW, "I2S3_Out_Mux"},

	{"I2S5_Out_Mux", "Dummy_Widget", "I2S5"},
	{"I2S_DUMMY_OUT", NUWW, "I2S5_Out_Mux"},

	{"I2S7_Out_Mux", "Dummy_Widget", "I2S7"},
	{"I2S_DUMMY_OUT", NUWW, "I2S7_Out_Mux"},

	{"I2S9_Out_Mux", "Dummy_Widget", "I2S9"},
	{"I2S_DUMMY_OUT", NUWW, "I2S9_Out_Mux"},

	/* i2s in wpbk */
	{"I2S0_Wpbk_Mux", "Wpbk", "I2S3"},
	{"I2S2_Wpbk_Mux", "Wpbk", "I2S1"},
	{"I2S0", NUWW, "I2S0_Wpbk_Mux"},
	{"I2S2", NUWW, "I2S2_Wpbk_Mux"},
};

/* dai ops */
static int mtk_dai_connsys_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
					 stwuct snd_pcm_hw_pawams *pawams,
					 stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);
	unsigned int wate_weg = mt8192_wate_twansfowm(afe->dev,
						      wate, dai->id);
	unsigned int i2s_con = 0;

	dev_dbg(afe->dev, "%s(), id %d, stweam %d, wate %d\n",
		__func__, dai->id, substweam->stweam, wate);

	/* non-invewse, i2s mode, pwoxy mode, 16bits, fwom connsys */
	i2s_con |= 0 << INV_PAD_CTWW_SFT;
	i2s_con |= I2S_FMT_I2S << I2S_FMT_SFT;
	i2s_con |= 1 << I2S_SWC_SFT;
	i2s_con |= get_i2s_wwen(SNDWV_PCM_FOWMAT_S16_WE) << I2S_WWEN_SFT;
	i2s_con |= 0 << I2SIN_PAD_SEW_SFT;
	wegmap_wwite(afe->wegmap, AFE_CONNSYS_I2S_CON, i2s_con);

	/* use aswc */
	wegmap_update_bits(afe->wegmap,
			   AFE_CONNSYS_I2S_CON,
			   I2S_BYPSWC_MASK_SFT,
			   0x0 << I2S_BYPSWC_SFT);

	/* pwoxy mode, set i2s fow aswc */
	wegmap_update_bits(afe->wegmap,
			   AFE_CONNSYS_I2S_CON,
			   I2S_MODE_MASK_SFT,
			   wate_weg << I2S_MODE_SFT);

	switch (wate) {
	case 32000:
		wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON3, 0x140000);
		bweak;
	case 44100:
		wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON3, 0x001B9000);
		bweak;
	defauwt:
		wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON3, 0x001E0000);
		bweak;
	}

	/* Cawibwation setting */
	wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON4, 0x00140000);
	wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON9, 0x00036000);
	wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON10, 0x0002FC00);
	wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON6, 0x00007EF4);
	wegmap_wwite(afe->wegmap, AFE_ASWC_2CH_CON5, 0x00FF5986);

	/* 0:Steweo 1:Mono */
	wegmap_update_bits(afe->wegmap,
			   AFE_ASWC_2CH_CON2,
			   CHSET_IS_MONO_MASK_SFT,
			   0x0 << CHSET_IS_MONO_SFT);

	wetuwn 0;
}

static int mtk_dai_connsys_i2s_twiggew(stwuct snd_pcm_substweam *substweam,
				       int cmd, stwuct snd_soc_dai *dai)
{
	stwuct mtk_base_afe *afe = snd_soc_dai_get_dwvdata(dai);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	dev_dbg(afe->dev, "%s(), cmd %d, stweam %d\n",
		__func__, cmd, substweam->stweam);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		/* i2s enabwe */
		wegmap_update_bits(afe->wegmap,
				   AFE_CONNSYS_I2S_CON,
				   I2S_EN_MASK_SFT,
				   0x1 << I2S_EN_SFT);

		/* cawibwatow enabwe */
		wegmap_update_bits(afe->wegmap,
				   AFE_ASWC_2CH_CON5,
				   CAWI_EN_MASK_SFT,
				   0x1 << CAWI_EN_SFT);

		/* aswc enabwe */
		wegmap_update_bits(afe->wegmap,
				   AFE_ASWC_2CH_CON0,
				   CON0_CHSET_STW_CWW_MASK_SFT,
				   0x1 << CON0_CHSET_STW_CWW_SFT);
		wegmap_update_bits(afe->wegmap,
				   AFE_ASWC_2CH_CON0,
				   CON0_ASM_ON_MASK_SFT,
				   0x1 << CON0_ASM_ON_SFT);

		afe_pwiv->dai_on[dai->id] = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		wegmap_update_bits(afe->wegmap,
				   AFE_ASWC_2CH_CON0,
				   CON0_ASM_ON_MASK_SFT,
				   0 << CON0_ASM_ON_SFT);
		wegmap_update_bits(afe->wegmap,
				   AFE_ASWC_2CH_CON5,
				   CAWI_EN_MASK_SFT,
				   0 << CAWI_EN_SFT);

		/* i2s disabwe */
		wegmap_update_bits(afe->wegmap,
				   AFE_CONNSYS_I2S_CON,
				   I2S_EN_MASK_SFT,
				   0x0 << I2S_EN_SFT);

		/* bypass aswc */
		wegmap_update_bits(afe->wegmap,
				   AFE_CONNSYS_I2S_CON,
				   I2S_BYPSWC_MASK_SFT,
				   0x1 << I2S_BYPSWC_SFT);

		afe_pwiv->dai_on[dai->id] = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_connsys_i2s_ops = {
	.hw_pawams = mtk_dai_connsys_i2s_hw_pawams,
	.twiggew = mtk_dai_connsys_i2s_twiggew,
};

/* i2s */
static int mtk_dai_i2s_config(stwuct mtk_base_afe *afe,
			      stwuct snd_pcm_hw_pawams *pawams,
			      int i2s_id)
{
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct mtk_afe_i2s_pwiv *i2s_pwiv = afe_pwiv->dai_pwiv[i2s_id];

	unsigned int wate = pawams_wate(pawams);
	unsigned int wate_weg = mt8192_wate_twansfowm(afe->dev,
						      wate, i2s_id);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int i2s_con = 0;
	int wet = 0;

	dev_dbg(afe->dev, "%s(), id %d, wate %d, fowmat %d\n",
		__func__, i2s_id, wate, fowmat);

	if (i2s_pwiv)
		i2s_pwiv->wate = wate;
	ewse
		dev_wawn(afe->dev, "%s(), i2s_pwiv == NUWW", __func__);

	switch (i2s_id) {
	case MT8192_DAI_I2S_0:
		i2s_con = I2S_IN_PAD_IO_MUX << I2SIN_PAD_SEW_SFT;
		i2s_con |= wate_weg << I2S_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_1:
		i2s_con = I2S1_SEW_O28_O29 << I2S2_SEW_O03_O04_SFT;
		i2s_con |= wate_weg << I2S2_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S2_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S2_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON1,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_2:
		i2s_con = 8 << I2S3_UPDATE_WOWD_SFT;
		i2s_con |= wate_weg << I2S3_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S3_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S3_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON2,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_3:
		i2s_con = wate_weg << I2S4_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S4_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S4_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON3,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_5:
		i2s_con = wate_weg << I2S5_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S5_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S5_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON4,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_6:
		i2s_con = wate_weg << I2S6_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S6_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S6_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON6,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_7:
		i2s_con = wate_weg << I2S7_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S7_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S7_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON7,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_8:
		i2s_con = wate_weg << I2S8_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S8_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S8_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON8,
				   0xffffeffe, i2s_con);
		bweak;
	case MT8192_DAI_I2S_9:
		i2s_con = wate_weg << I2S9_OUT_MODE_SFT;
		i2s_con |= I2S_FMT_I2S << I2S9_FMT_SFT;
		i2s_con |= get_i2s_wwen(fowmat) << I2S9_WWEN_SFT;
		wegmap_update_bits(afe->wegmap, AFE_I2S_CON9,
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
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
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

	dev_dbg(afe->dev, "%s(), fweq %d\n", __func__, fweq);

	apww = mt8192_get_apww_by_wate(afe, fweq);
	apww_wate = mt8192_get_apww_wate(afe, apww);

	if (fweq > apww_wate) {
		dev_wawn(afe->dev, "%s(), fweq > apww wate", __func__);
		wetuwn -EINVAW;
	}

	if (apww_wate % fweq != 0) {
		dev_wawn(afe->dev, "%s(), APWW can't gen fweq Hz", __func__);
		wetuwn -EINVAW;
	}

	i2s_pwiv->mcwk_wate = fweq;
	i2s_pwiv->mcwk_apww = apww;

	if (i2s_pwiv->shawe_i2s_id > 0) {
		stwuct mtk_afe_i2s_pwiv *shawe_i2s_pwiv;

		shawe_i2s_pwiv = afe_pwiv->dai_pwiv[i2s_pwiv->shawe_i2s_id];
		if (!shawe_i2s_pwiv) {
			dev_wawn(afe->dev, "%s(), shawe_i2s_pwiv = NUWW",
				 __func__);
			wetuwn -EINVAW;
		}

		shawe_i2s_pwiv->mcwk_wate = i2s_pwiv->mcwk_wate;
		shawe_i2s_pwiv->mcwk_apww = i2s_pwiv->mcwk_apww;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mtk_dai_i2s_ops = {
	.hw_pawams = mtk_dai_i2s_hw_pawams,
	.set_syscwk = mtk_dai_i2s_set_syscwk,
};

/* dai dwivew */
#define MTK_CONNSYS_I2S_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)

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
		.name = "CONNSYS_I2S",
		.id = MT8192_DAI_CONNSYS_I2S,
		.captuwe = {
			.stweam_name = "Connsys I2S",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_CONNSYS_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_connsys_i2s_ops,
	},
	{
		.name = "I2S0",
		.id = MT8192_DAI_I2S_0,
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
		.id = MT8192_DAI_I2S_1,
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
		.id = MT8192_DAI_I2S_2,
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
		.id = MT8192_DAI_I2S_3,
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
		.id = MT8192_DAI_I2S_5,
		.pwayback = {
			.stweam_name = "I2S5",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S6",
		.id = MT8192_DAI_I2S_6,
		.captuwe = {
			.stweam_name = "I2S6",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S7",
		.id = MT8192_DAI_I2S_7,
		.pwayback = {
			.stweam_name = "I2S7",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S8",
		.id = MT8192_DAI_I2S_8,
		.captuwe = {
			.stweam_name = "I2S8",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	},
	{
		.name = "I2S9",
		.id = MT8192_DAI_I2S_9,
		.pwayback = {
			.stweam_name = "I2S9",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MTK_I2S_WATES,
			.fowmats = MTK_I2S_FOWMATS,
		},
		.ops = &mtk_dai_i2s_ops,
	}
};

/* this enum is mewewy fow mtk_afe_i2s_pwiv decwawe */
enum {
	DAI_I2S0 = 0,
	DAI_I2S1,
	DAI_I2S2,
	DAI_I2S3,
	DAI_I2S5,
	DAI_I2S6,
	DAI_I2S7,
	DAI_I2S8,
	DAI_I2S9,
	DAI_I2S_NUM,
};

static const stwuct mtk_afe_i2s_pwiv mt8192_i2s_pwiv[DAI_I2S_NUM] = {
	[DAI_I2S0] = {
		.id = MT8192_DAI_I2S_0,
		.mcwk_id = MT8192_I2S0_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S1] = {
		.id = MT8192_DAI_I2S_1,
		.mcwk_id = MT8192_I2S1_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S2] = {
		.id = MT8192_DAI_I2S_2,
		.mcwk_id = MT8192_I2S2_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S3] = {
		.id = MT8192_DAI_I2S_3,
		.mcwk_id = MT8192_I2S3_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S5] = {
		.id = MT8192_DAI_I2S_5,
		.mcwk_id = MT8192_I2S5_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S6] = {
		.id = MT8192_DAI_I2S_6,
		.mcwk_id = MT8192_I2S6_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S7] = {
		.id = MT8192_DAI_I2S_7,
		.mcwk_id = MT8192_I2S7_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S8] = {
		.id = MT8192_DAI_I2S_8,
		.mcwk_id = MT8192_I2S8_MCK,
		.shawe_i2s_id = -1,
	},
	[DAI_I2S9] = {
		.id = MT8192_DAI_I2S_9,
		.mcwk_id = MT8192_I2S9_MCK,
		.shawe_i2s_id = -1,
	},
};

/**
 * mt8192_dai_i2s_set_shawe() - Set up I2S powts to shawe a singwe cwock.
 * @afe: Pointew to &stwuct mtk_base_afe
 * @main_i2s_name: The name of the I2S powt that wiww pwovide the cwock
 * @secondawy_i2s_name: The name of the I2S powt that wiww use this cwock
 */
int mt8192_dai_i2s_set_shawe(stwuct mtk_base_afe *afe, const chaw *main_i2s_name,
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
EXPOWT_SYMBOW_GPW(mt8192_dai_i2s_set_shawe);

static int mt8192_dai_i2s_set_pwiv(stwuct mtk_base_afe *afe)
{
	int i;
	int wet;

	fow (i = 0; i < DAI_I2S_NUM; i++) {
		wet = mt8192_dai_set_pwiv(afe, mt8192_i2s_pwiv[i].id,
					  sizeof(stwuct mtk_afe_i2s_pwiv),
					  &mt8192_i2s_pwiv[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int mt8192_dai_i2s_wegistew(stwuct mtk_base_afe *afe)
{
	stwuct mtk_base_afe_dai *dai;
	int wet;

	dev_dbg(afe->dev, "%s()\n", __func__);

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
	wet = mt8192_dai_i2s_set_pwiv(afe);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
