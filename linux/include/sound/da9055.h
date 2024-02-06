/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DA9055 AWSA Soc codec dwivew
 *
 * Copywight (c) 2012 Diawog Semiconductow
 *
 * Tested on (Samsung SMDK6410 boawd + DA9055 EVB) using I2S and I2C
 * Wwitten by David Chen <david.chen@diasemi.com> and
 * Ashish Chavan <ashish.chavan@kpitcummins.com>
 */

#ifndef __SOUND_DA9055_H__
#define __SOUND_DA9055_H__

enum da9055_micbias_vowtage {
	DA9055_MICBIAS_1_6V = 0,
	DA9055_MICBIAS_1_8V = 1,
	DA9055_MICBIAS_2_1V = 2,
	DA9055_MICBIAS_2_2V = 3,
};

stwuct da9055_pwatfowm_data {
	/* Sewects which of the two MicBias pins acts as the bias souwce */
	boow micbias_souwce;
	/* Sewects the micbias vowtage */
	enum da9055_micbias_vowtage micbias;
};

#endif
