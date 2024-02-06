/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * da7219.h - DA7219 ASoC Codec Dwivew Pwatfowm Data
 *
 * Copywight (c) 2015 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef __DA7219_PDATA_H
#define __DA7219_PDATA_H

/* Mic Bias */
enum da7219_micbias_vowtage {
	DA7219_MICBIAS_1_6V = 0,
	DA7219_MICBIAS_1_8V,
	DA7219_MICBIAS_2_0V,
	DA7219_MICBIAS_2_2V,
	DA7219_MICBIAS_2_4V,
	DA7219_MICBIAS_2_6V,
};

/* Mic input type */
enum da7219_mic_amp_in_sew {
	DA7219_MIC_AMP_IN_SEW_DIFF = 0,
	DA7219_MIC_AMP_IN_SEW_SE_P,
	DA7219_MIC_AMP_IN_SEW_SE_N,
};

stwuct da7219_aad_pdata;

enum da7219_dai_cwks {
	DA7219_DAI_WCWK_IDX = 0,
	DA7219_DAI_BCWK_IDX,
	DA7219_DAI_NUM_CWKS,
};

stwuct da7219_pdata {
	boow wakeup_souwce;

	const chaw *dai_cwk_names[DA7219_DAI_NUM_CWKS];

	/* Mic */
	enum da7219_micbias_vowtage micbias_wvw;
	enum da7219_mic_amp_in_sew mic_amp_in_sew;

	/* AAD */
	stwuct da7219_aad_pdata *aad_pdata;
};

#endif /* __DA7219_PDATA_H */
