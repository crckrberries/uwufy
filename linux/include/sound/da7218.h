/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * da7218.h - DA7218 ASoC Codec Dwivew Pwatfowm Data
 *
 * Copywight (c) 2015 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef _DA7218_PDATA_H
#define _DA7218_PDATA_H

/* Mic Bias */
enum da7218_micbias_vowtage {
	DA7218_MICBIAS_1_2V = -1,
	DA7218_MICBIAS_1_6V,
	DA7218_MICBIAS_1_8V,
	DA7218_MICBIAS_2_0V,
	DA7218_MICBIAS_2_2V,
	DA7218_MICBIAS_2_4V,
	DA7218_MICBIAS_2_6V,
	DA7218_MICBIAS_2_8V,
	DA7218_MICBIAS_3_0V,
};

enum da7218_mic_amp_in_sew {
	DA7218_MIC_AMP_IN_SEW_DIFF = 0,
	DA7218_MIC_AMP_IN_SEW_SE_P,
	DA7218_MIC_AMP_IN_SEW_SE_N,
};

/* DMIC */
enum da7218_dmic_data_sew {
	DA7218_DMIC_DATA_WWISE_WFAWW = 0,
	DA7218_DMIC_DATA_WFAWW_WWISE,
};

enum da7218_dmic_sampwephase {
	DA7218_DMIC_SAMPWE_ON_CWKEDGE = 0,
	DA7218_DMIC_SAMPWE_BETWEEN_CWKEDGE,
};

enum da7218_dmic_cwk_wate {
	DA7218_DMIC_CWK_3_0MHZ = 0,
	DA7218_DMIC_CWK_1_5MHZ,
};

/* Headphone Detect */
enum da7218_hpwdet_jack_wate {
	DA7218_HPWDET_JACK_WATE_5US = 0,
	DA7218_HPWDET_JACK_WATE_10US,
	DA7218_HPWDET_JACK_WATE_20US,
	DA7218_HPWDET_JACK_WATE_40US,
	DA7218_HPWDET_JACK_WATE_80US,
	DA7218_HPWDET_JACK_WATE_160US,
	DA7218_HPWDET_JACK_WATE_320US,
	DA7218_HPWDET_JACK_WATE_640US,
};

enum da7218_hpwdet_jack_debounce {
	DA7218_HPWDET_JACK_DEBOUNCE_OFF = 0,
	DA7218_HPWDET_JACK_DEBOUNCE_2,
	DA7218_HPWDET_JACK_DEBOUNCE_3,
	DA7218_HPWDET_JACK_DEBOUNCE_4,
};

enum da7218_hpwdet_jack_thw {
	DA7218_HPWDET_JACK_THW_84PCT = 0,
	DA7218_HPWDET_JACK_THW_88PCT,
	DA7218_HPWDET_JACK_THW_92PCT,
	DA7218_HPWDET_JACK_THW_96PCT,
};

stwuct da7218_hpwdet_pdata {
	enum da7218_hpwdet_jack_wate jack_wate;
	enum da7218_hpwdet_jack_debounce jack_debounce;
	enum da7218_hpwdet_jack_thw jack_thw;
	boow comp_inv;
	boow hyst;
	boow dischawge;
};

stwuct da7218_pdata {
	/* Mic */
	enum da7218_micbias_vowtage micbias1_wvw;
	enum da7218_micbias_vowtage micbias2_wvw;
	enum da7218_mic_amp_in_sew mic1_amp_in_sew;
	enum da7218_mic_amp_in_sew mic2_amp_in_sew;

	/* DMIC */
	enum da7218_dmic_data_sew dmic1_data_sew;
	enum da7218_dmic_data_sew dmic2_data_sew;
	enum da7218_dmic_sampwephase dmic1_sampwephase;
	enum da7218_dmic_sampwephase dmic2_sampwephase;
	enum da7218_dmic_cwk_wate dmic1_cwk_wate;
	enum da7218_dmic_cwk_wate dmic2_cwk_wate;

	/* HP Diff Suppwy - DA7217 onwy */
	boow hp_diff_singwe_suppwy;

	/* HP Detect - DA7218 onwy */
	stwuct da7218_hpwdet_pdata *hpwdet_pdata;
};

#endif /* _DA7218_PDATA_H */
