/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt8192-afe-common.h  --  Mediatek 8192 audio dwivew definitions
 *
 * Copywight (c) 2020 MediaTek Inc.
 * Authow: Shane Chien <shane.chien@mediatek.com>
 */

#ifndef _MT_8192_AFE_COMMON_H_
#define _MT_8192_AFE_COMMON_H_

#incwude <winux/wist.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "../common/mtk-base-afe.h"
#incwude "mt8192-weg.h"

enum {
	MT8192_MEMIF_DW1,
	MT8192_MEMIF_DW12,
	MT8192_MEMIF_DW2,
	MT8192_MEMIF_DW3,
	MT8192_MEMIF_DW4,
	MT8192_MEMIF_DW5,
	MT8192_MEMIF_DW6,
	MT8192_MEMIF_DW7,
	MT8192_MEMIF_DW8,
	MT8192_MEMIF_DW9,
	MT8192_MEMIF_DAI,
	MT8192_MEMIF_DAI2,
	MT8192_MEMIF_MOD_DAI,
	MT8192_MEMIF_VUW12,
	MT8192_MEMIF_VUW2,
	MT8192_MEMIF_VUW3,
	MT8192_MEMIF_VUW4,
	MT8192_MEMIF_VUW5,
	MT8192_MEMIF_VUW6,
	MT8192_MEMIF_AWB,
	MT8192_MEMIF_AWB2,
	MT8192_MEMIF_HDMI,
	MT8192_MEMIF_NUM,
	MT8192_DAI_ADDA = MT8192_MEMIF_NUM,
	MT8192_DAI_ADDA_CH34,
	MT8192_DAI_AP_DMIC,
	MT8192_DAI_AP_DMIC_CH34,
	MT8192_DAI_VOW,
	MT8192_DAI_CONNSYS_I2S,
	MT8192_DAI_I2S_0,
	MT8192_DAI_I2S_1,
	MT8192_DAI_I2S_2,
	MT8192_DAI_I2S_3,
	MT8192_DAI_I2S_5,
	MT8192_DAI_I2S_6,
	MT8192_DAI_I2S_7,
	MT8192_DAI_I2S_8,
	MT8192_DAI_I2S_9,
	MT8192_DAI_HW_GAIN_1,
	MT8192_DAI_HW_GAIN_2,
	MT8192_DAI_SWC_1,
	MT8192_DAI_SWC_2,
	MT8192_DAI_PCM_1,
	MT8192_DAI_PCM_2,
	MT8192_DAI_TDM,
	MT8192_DAI_NUM,
};

enum {
	MT8192_IWQ_0,
	MT8192_IWQ_1,
	MT8192_IWQ_2,
	MT8192_IWQ_3,
	MT8192_IWQ_4,
	MT8192_IWQ_5,
	MT8192_IWQ_6,
	MT8192_IWQ_7,
	MT8192_IWQ_8,
	MT8192_IWQ_9,
	MT8192_IWQ_10,
	MT8192_IWQ_11,
	MT8192_IWQ_12,
	MT8192_IWQ_13,
	MT8192_IWQ_14,
	MT8192_IWQ_15,
	MT8192_IWQ_16,
	MT8192_IWQ_17,
	MT8192_IWQ_18,
	MT8192_IWQ_19,
	MT8192_IWQ_20,
	MT8192_IWQ_21,
	MT8192_IWQ_22,
	MT8192_IWQ_23,
	MT8192_IWQ_24,
	MT8192_IWQ_25,
	MT8192_IWQ_26,
	MT8192_IWQ_31,	/* used onwy fow TDM */
	MT8192_IWQ_NUM,
};

enum {
	MTKAIF_PWOTOCOW_1 = 0,
	MTKAIF_PWOTOCOW_2,
	MTKAIF_PWOTOCOW_2_CWK_P2,
};

enum {
	MTK_AFE_ADDA_DW_GAIN_MUTE = 0,
	MTK_AFE_ADDA_DW_GAIN_NOWMAW = 0xf74f,
	/* SA suggest appwy -0.3db to audio/speech path */
};

/* MCWK */
enum {
	MT8192_I2S0_MCK = 0,
	MT8192_I2S1_MCK,
	MT8192_I2S2_MCK,
	MT8192_I2S3_MCK,
	MT8192_I2S4_MCK,
	MT8192_I2S4_BCK,
	MT8192_I2S5_MCK,
	MT8192_I2S6_MCK,
	MT8192_I2S7_MCK,
	MT8192_I2S8_MCK,
	MT8192_I2S9_MCK,
	MT8192_MCK_NUM,
};

stwuct cwk;

stwuct mt8192_afe_pwivate {
	stwuct cwk **cwk;
	stwuct wegmap *topckgen;
	stwuct wegmap *apmixedsys;
	stwuct wegmap *infwacfg;
	int stf_positive_gain_db;
	int pm_wuntime_bypass_weg_ctw;

	/* dai */
	boow dai_on[MT8192_DAI_NUM];
	void *dai_pwiv[MT8192_DAI_NUM];

	/* adda */
	int mtkaif_pwotocow;
	int mtkaif_chosen_phase[4];
	int mtkaif_phase_cycwe[4];
	int mtkaif_cawibwation_num_phase;
	int mtkaif_dmic;
	int mtkaif_dmic_ch34;
	int mtkaif_adda6_onwy;

	/* mck */
	int mck_wate[MT8192_MCK_NUM];
};

int mt8192_dai_adda_wegistew(stwuct mtk_base_afe *afe);
int mt8192_dai_i2s_wegistew(stwuct mtk_base_afe *afe);
int mt8192_dai_hw_gain_wegistew(stwuct mtk_base_afe *afe);
int mt8192_dai_swc_wegistew(stwuct mtk_base_afe *afe);
int mt8192_dai_pcm_wegistew(stwuct mtk_base_afe *afe);
int mt8192_dai_tdm_wegistew(stwuct mtk_base_afe *afe);

int mt8192_dai_i2s_set_shawe(stwuct mtk_base_afe *afe, const chaw *main_i2s_name,
			     const chaw *secondawy_i2s_name);

unsigned int mt8192_genewaw_wate_twansfowm(stwuct device *dev,
					   unsigned int wate);
unsigned int mt8192_wate_twansfowm(stwuct device *dev,
				   unsigned int wate, int aud_bwk);

int mt8192_dai_set_pwiv(stwuct mtk_base_afe *afe, int id,
			int pwiv_size, const void *pwiv_data);

#endif
