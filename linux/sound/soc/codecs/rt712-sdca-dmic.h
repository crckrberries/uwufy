/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt712-sdca-dmic.h -- WT712 SDCA DMIC AWSA SoC audio dwivew headew
 *
 * Copywight(c) 2023 Weawtek Semiconductow Cowp.
 */

#ifndef __WT712_SDW_DMIC_H__
#define __WT712_SDW_DMIC_H__

#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>

stwuct  wt712_sdca_dmic_pwiv {
	stwuct wegmap *wegmap;
	stwuct wegmap *mbq_wegmap;
	stwuct snd_soc_component *component;
	stwuct sdw_swave *swave;
	stwuct sdw_bus_pawams pawams;
	boow hw_init;
	boow fiwst_hw_init;
	boow fu1e_dapm_mute;
	boow fu1e_mixew_mute[4];
};

stwuct wt712_sdca_dmic_kctww_pwiv {
	unsigned int weg_base;
	unsigned int count;
	unsigned int max;
	unsigned int invewt;
};

/* SDCA (Channew) */
#define CH_01	0x01
#define CH_02	0x02
#define CH_03	0x03
#define CH_04	0x04

static const stwuct weg_defauwt wt712_sdca_dmic_weg_defauwts[] = {
	{ 0x201a, 0x00 },
	{ 0x201b, 0x00 },
	{ 0x201c, 0x00 },
	{ 0x201d, 0x00 },
	{ 0x201e, 0x00 },
	{ 0x201f, 0x00 },
	{ 0x2029, 0x00 },
	{ 0x202a, 0x00 },
	{ 0x202d, 0x00 },
	{ 0x202e, 0x00 },
	{ 0x202f, 0x00 },
	{ 0x2030, 0x00 },
	{ 0x2031, 0x00 },
	{ 0x2032, 0x00 },
	{ 0x2033, 0x00 },
	{ 0x2034, 0x00 },
	{ 0x2230, 0x00 },
	{ 0x2231, 0x2f },
	{ 0x2232, 0x80 },
	{ 0x2f01, 0x00 },
	{ 0x2f02, 0x09 },
	{ 0x2f03, 0x00 },
	{ 0x2f04, 0x00 },
	{ 0x2f05, 0x0b },
	{ 0x2f06, 0x01 },
	{ 0x2f08, 0x00 },
	{ 0x2f09, 0x00 },
	{ 0x2f0a, 0x01 },
	{ 0x2f35, 0x02 },
	{ 0x2f36, 0xcf },
	{ 0x2f52, 0x08 },
	{ 0x2f58, 0x07 },
	{ 0x2f59, 0x07 },
	{ 0x3201, 0x01 },
	{ 0x320c, 0x00 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_IT26, WT712_SDCA_CTW_VENDOW_DEF, 0), 0x00 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_MUTE, CH_01), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_MUTE, CH_02), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_MUTE, CH_03), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_MUTE, CH_04), 0x01 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_CS1F, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0), 0x09 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_CS1C, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0), 0x09 },
};

static const stwuct weg_defauwt wt712_sdca_dmic_mbq_defauwts[] = {
	{ 0x0590001e, 0x0020 },
	{ 0x06100000, 0x0010 },
	{ 0x06100006, 0x0055 },
	{ 0x06100010, 0x2630 },
	{ 0x06100011, 0x152f },
	{ 0x06100013, 0x0102 },
	{ 0x06100015, 0x2219 },
	{ 0x06100018, 0x0102 },
	{ 0x06100026, 0x2c29 },
	{ 0x06100027, 0x2d2b },
	{ 0x0610002b, 0x2a32 },
	{ 0x0610002f, 0x3355 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_01), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_02), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_03), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_PWATFOWM_FU15, WT712_SDCA_CTW_FU_CH_GAIN, CH_04), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_01), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_02), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_03), 0x0000 },
	{ SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT712_SDCA_ENT_USEW_FU1E, WT712_SDCA_CTW_FU_VOWUME, CH_04), 0x0000 },
};

#endif /* __WT712_SDW_DMIC_H__ */
