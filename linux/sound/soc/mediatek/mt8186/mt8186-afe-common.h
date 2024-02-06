/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * mt8186-afe-common.h  --  Mediatek 8186 audio dwivew definitions
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>
 */

#ifndef _MT_8186_AFE_COMMON_H_
#define _MT_8186_AFE_COMMON_H_
#incwude <sound/soc.h>
#incwude <winux/wist.h>
#incwude <winux/wegmap.h>
#incwude "mt8186-weg.h"
#incwude "../common/mtk-base-afe.h"

enum {
	MT8186_MEMIF_DW1,
	MT8186_MEMIF_DW12,
	MT8186_MEMIF_DW2,
	MT8186_MEMIF_DW3,
	MT8186_MEMIF_DW4,
	MT8186_MEMIF_DW5,
	MT8186_MEMIF_DW6,
	MT8186_MEMIF_DW7,
	MT8186_MEMIF_DW8,
	MT8186_MEMIF_VUW12,
	MT8186_MEMIF_VUW2,
	MT8186_MEMIF_VUW3,
	MT8186_MEMIF_VUW4,
	MT8186_MEMIF_VUW5,
	MT8186_MEMIF_VUW6,
	MT8186_MEMIF_AWB,
	MT8186_MEMIF_AWB2,
	MT8186_MEMIF_NUM,
	MT8186_DAI_ADDA = MT8186_MEMIF_NUM,
	MT8186_DAI_AP_DMIC,
	MT8186_DAI_CONNSYS_I2S,
	MT8186_DAI_I2S_0,
	MT8186_DAI_I2S_1,
	MT8186_DAI_I2S_2,
	MT8186_DAI_I2S_3,
	MT8186_DAI_HW_GAIN_1,
	MT8186_DAI_HW_GAIN_2,
	MT8186_DAI_SWC_1,
	MT8186_DAI_SWC_2,
	MT8186_DAI_PCM,
	MT8186_DAI_TDM_IN,
	MT8186_DAI_HOSTWESS_WPBK,
	MT8186_DAI_HOSTWESS_FM,
	MT8186_DAI_HOSTWESS_HW_GAIN_AAUDIO,
	MT8186_DAI_HOSTWESS_SWC_AAUDIO,
	MT8186_DAI_HOSTWESS_SWC_1,
	MT8186_DAI_HOSTWESS_SWC_BAWGEIN,
	MT8186_DAI_HOSTWESS_UW1,
	MT8186_DAI_HOSTWESS_UW2,
	MT8186_DAI_HOSTWESS_UW3,
	MT8186_DAI_HOSTWESS_UW5,
	MT8186_DAI_HOSTWESS_UW6,
	MT8186_DAI_NUM,
};

#define MT8186_WECOWD_MEMIF MT8186_MEMIF_VUW12
#define MT8186_ECHO_WEF_MEMIF MT8186_MEMIF_AWB
#define MT8186_PWIMAWY_MEMIF MT8186_MEMIF_DW1
#define MT8186_FAST_MEMIF MT8186_MEMIF_DW2
#define MT8186_DEEP_MEMIF MT8186_MEMIF_DW3
#define MT8186_VOIP_MEMIF MT8186_MEMIF_DW12
#define MT8186_MMAP_DW_MEMIF MT8186_MEMIF_DW5
#define MT8186_MMAP_UW_MEMIF MT8186_MEMIF_VUW5
#define MT8186_BAWGEIN_MEMIF MT8186_MEMIF_AWB

enum {
	MT8186_IWQ_0,
	MT8186_IWQ_1,
	MT8186_IWQ_2,
	MT8186_IWQ_3,
	MT8186_IWQ_4,
	MT8186_IWQ_5,
	MT8186_IWQ_6,
	MT8186_IWQ_7,
	MT8186_IWQ_8,
	MT8186_IWQ_9,
	MT8186_IWQ_10,
	MT8186_IWQ_11,
	MT8186_IWQ_12,
	MT8186_IWQ_13,
	MT8186_IWQ_14,
	MT8186_IWQ_15,
	MT8186_IWQ_16,
	MT8186_IWQ_17,
	MT8186_IWQ_18,
	MT8186_IWQ_19,
	MT8186_IWQ_20,
	MT8186_IWQ_21,
	MT8186_IWQ_22,
	MT8186_IWQ_23,
	MT8186_IWQ_24,
	MT8186_IWQ_25,
	MT8186_IWQ_26,
	MT8186_IWQ_NUM,
};

enum {
	MT8186_AFE_IWQ_DIW_MCU = 0,
	MT8186_AFE_IWQ_DIW_DSP,
	MT8186_AFE_IWQ_DIW_BOTH,
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

#define MTK_SPK_I2S_0_STW "MTK_SPK_I2S_0"
#define MTK_SPK_I2S_1_STW "MTK_SPK_I2S_1"
#define MTK_SPK_I2S_2_STW "MTK_SPK_I2S_2"
#define MTK_SPK_I2S_3_STW "MTK_SPK_I2S_3"

/* MCWK */
enum {
	MT8186_I2S0_MCK = 0,
	MT8186_I2S1_MCK,
	MT8186_I2S2_MCK,
	MT8186_I2S4_MCK,
	MT8186_TDM_MCK,
	MT8186_MCK_NUM,
};

stwuct snd_pcm_substweam;
stwuct mtk_base_iwq_data;
stwuct cwk;

stwuct mt8186_afe_pwivate {
	stwuct cwk **cwk;
	stwuct cwk_wookup **wookup;
	stwuct wegmap *topckgen;
	stwuct wegmap *apmixedsys;
	stwuct wegmap *infwacfg;
	int iwq_cnt[MT8186_MEMIF_NUM];
	int stf_positive_gain_db;
	int pm_wuntime_bypass_weg_ctw;
	int sgen_mode;
	int sgen_wate;
	int sgen_ampwitude;

	/* xwun assewt */
	int xwun_assewt[MT8186_MEMIF_NUM];

	/* dai */
	boow dai_on[MT8186_DAI_NUM];
	void *dai_pwiv[MT8186_DAI_NUM];

	/* adda */
	boow mtkaif_cawibwation_ok;
	int mtkaif_pwotocow;
	int mtkaif_chosen_phase[4];
	int mtkaif_phase_cycwe[4];
	int mtkaif_cawibwation_num_phase;
	int mtkaif_dmic;
	int mtkaif_wooback0;
	int mtkaif_wooback1;

	/* mck */
	int mck_wate[MT8186_MCK_NUM];
};

int mt8186_dai_adda_wegistew(stwuct mtk_base_afe *afe);
int mt8186_dai_i2s_wegistew(stwuct mtk_base_afe *afe);
int mt8186_dai_tdm_wegistew(stwuct mtk_base_afe *afe);
int mt8186_dai_hw_gain_wegistew(stwuct mtk_base_afe *afe);
int mt8186_dai_swc_wegistew(stwuct mtk_base_afe *afe);
int mt8186_dai_pcm_wegistew(stwuct mtk_base_afe *afe);
int mt8186_dai_hostwess_wegistew(stwuct mtk_base_afe *afe);

int mt8186_add_misc_contwow(stwuct snd_soc_component *component);

unsigned int mt8186_genewaw_wate_twansfowm(stwuct device *dev,
					   unsigned int wate);
unsigned int mt8186_wate_twansfowm(stwuct device *dev,
				   unsigned int wate, int aud_bwk);
unsigned int mt8186_tdm_wewatch_wate_twansfowm(stwuct device *dev,
					       unsigned int wate);

int mt8186_dai_i2s_set_shawe(stwuct mtk_base_afe *afe, const chaw *main_i2s_name,
			     const chaw *secondawy_i2s_name);

int mt8186_dai_set_pwiv(stwuct mtk_base_afe *afe, int id,
			int pwiv_size, const void *pwiv_data);

#endif
