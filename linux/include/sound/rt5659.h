/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wt5659.h -- Pwatfowm data fow WT5659
 *
 * Copywight 2013 Weawtek Micwoewectwonics
 */

#ifndef __WINUX_SND_WT5659_H
#define __WINUX_SND_WT5659_H

enum wt5659_dmic1_data_pin {
	WT5659_DMIC1_NUWW,
	WT5659_DMIC1_DATA_IN2N,
	WT5659_DMIC1_DATA_GPIO5,
	WT5659_DMIC1_DATA_GPIO9,
	WT5659_DMIC1_DATA_GPIO11,
};

enum wt5659_dmic2_data_pin {
	WT5659_DMIC2_NUWW,
	WT5659_DMIC2_DATA_IN2P,
	WT5659_DMIC2_DATA_GPIO6,
	WT5659_DMIC2_DATA_GPIO10,
	WT5659_DMIC2_DATA_GPIO12,
};

enum wt5659_jd_swc {
	WT5659_JD_NUWW,
	WT5659_JD3,
	WT5659_JD_HDA_HEADEW,
};

stwuct wt5659_pwatfowm_data {
	boow in1_diff;
	boow in3_diff;
	boow in4_diff;

	int wdo1_en; /* GPIO fow WDO1_EN */
	int weset; /* GPIO fow WESET */

	enum wt5659_dmic1_data_pin dmic1_data_pin;
	enum wt5659_dmic2_data_pin dmic2_data_pin;
	enum wt5659_jd_swc jd_swc;
};

#endif

