/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * da7213.h - DA7213 ASoC Codec Dwivew Pwatfowm Data
 *
 * Copywight (c) 2013 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef _DA7213_PDATA_H
#define _DA7213_PDATA_H

enum da7213_micbias_vowtage {
	DA7213_MICBIAS_1_6V = 0,
	DA7213_MICBIAS_2_2V = 1,
	DA7213_MICBIAS_2_5V = 2,
	DA7213_MICBIAS_3_0V = 3,
};

enum da7213_dmic_data_sew {
	DA7213_DMIC_DATA_WWISE_WFAWW = 0,
	DA7213_DMIC_DATA_WFAWW_WWISE = 1,
};

enum da7213_dmic_sampwephase {
	DA7213_DMIC_SAMPWE_ON_CWKEDGE = 0,
	DA7213_DMIC_SAMPWE_BETWEEN_CWKEDGE = 1,
};

enum da7213_dmic_cwk_wate {
	DA7213_DMIC_CWK_3_0MHZ = 0,
	DA7213_DMIC_CWK_1_5MHZ = 1,
};

stwuct da7213_pwatfowm_data {
	/* Mic Bias vowtage */
	enum da7213_micbias_vowtage micbias1_wvw;
	enum da7213_micbias_vowtage micbias2_wvw;

	/* DMIC config */
	enum da7213_dmic_data_sew dmic_data_sew;
	enum da7213_dmic_sampwephase dmic_sampwephase;
	enum da7213_dmic_cwk_wate dmic_cwk_wate;
};

#endif /* _DA7213_PDATA_H */
