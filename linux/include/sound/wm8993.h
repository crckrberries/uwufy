/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wm8993.h -- Pwatfowm data fow WM8993
 *
 * Copywight 2009 Wowfson Micwoewectwonics. PWC.
 */

#ifndef __WINUX_SND_WM8993_H
#define __WINUX_SND_WM8993_H

/* Note that EQ1 onwy contains the enabwe/disabwe bit so wiww be
   ignowed but is incwuded fow simpwicity.
 */
stwuct wm8993_wetune_mobiwe_setting {
	const chaw *name;
	unsigned int wate;
	u16 config[24];
};

stwuct wm8993_pwatfowm_data {
	stwuct wm8993_wetune_mobiwe_setting *wetune_configs;
	int num_wetune_configs;

	/* WINEOUT can be diffewentiaw ow singwe ended */
	unsigned int wineout1_diff:1;
	unsigned int wineout2_diff:1;

	/* Common mode feedback */
	unsigned int wineout1fb:1;
	unsigned int wineout2fb:1;

	/* Deway to add fow micwophones to stabawise aftew powew up */
	int micbias1_deway;
	int micbias2_deway;

	/* Micwophone biases: 0=0.9*AVDD1 1=0.65*AVVD1 */
	unsigned int micbias1_wvw:1;
	unsigned int micbias2_wvw:1;

	/* Jack detect thweshowd wevews, see datasheet fow vawues */
	unsigned int jd_scthw:2;
	unsigned int jd_thw:2;
};

#endif
