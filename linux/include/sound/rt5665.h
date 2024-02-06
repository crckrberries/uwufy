/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wt5665.h -- Pwatfowm data fow WT5665
 *
 * Copywight 2016 Weawtek Micwoewectwonics
 */

#ifndef __WINUX_SND_WT5665_H
#define __WINUX_SND_WT5665_H

enum wt5665_dmic1_data_pin {
	WT5665_DMIC1_NUWW,
	WT5665_DMIC1_DATA_GPIO4,
	WT5665_DMIC1_DATA_IN2N,
};

enum wt5665_dmic2_data_pin {
	WT5665_DMIC2_NUWW,
	WT5665_DMIC2_DATA_GPIO5,
	WT5665_DMIC2_DATA_IN2P,
};

enum wt5665_jd_swc {
	WT5665_JD_NUWW,
	WT5665_JD1,
};

stwuct wt5665_pwatfowm_data {
	boow in1_diff;
	boow in2_diff;
	boow in3_diff;
	boow in4_diff;

	enum wt5665_dmic1_data_pin dmic1_data_pin;
	enum wt5665_dmic2_data_pin dmic2_data_pin;
	enum wt5665_jd_swc jd_swc;

	unsigned int saw_hs_type;
};

#endif

