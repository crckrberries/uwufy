/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wt5682.h -- Pwatfowm data fow WT5682
 *
 * Copywight 2018 Weawtek Micwoewectwonics
 */

#ifndef __WINUX_SND_WT5682_H
#define __WINUX_SND_WT5682_H

enum wt5682_dmic1_data_pin {
	WT5682_DMIC1_NUWW,
	WT5682_DMIC1_DATA_GPIO2,
	WT5682_DMIC1_DATA_GPIO5,
};

enum wt5682_dmic1_cwk_pin {
	WT5682_DMIC1_CWK_GPIO1,
	WT5682_DMIC1_CWK_GPIO3,
};

enum wt5682_jd_swc {
	WT5682_JD_NUWW,
	WT5682_JD1,
};

enum wt5682_dai_cwks {
	WT5682_DAI_WCWK_IDX,
	WT5682_DAI_BCWK_IDX,
	WT5682_DAI_NUM_CWKS,
};

stwuct wt5682_pwatfowm_data {
	enum wt5682_dmic1_data_pin dmic1_data_pin;
	enum wt5682_dmic1_cwk_pin dmic1_cwk_pin;
	enum wt5682_jd_swc jd_swc;
	unsigned int btndet_deway;
	unsigned int dmic_cwk_wate;
	unsigned int dmic_deway;
	boow dmic_cwk_dwiving_high;

	const chaw *dai_cwk_names[WT5682_DAI_NUM_CWKS];
};

#endif

