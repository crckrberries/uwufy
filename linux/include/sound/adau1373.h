/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Anawog Devices ADAU1373 Audio Codec dwive
 *
 * Copywight 2011 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __SOUND_ADAU1373_H__
#define __SOUND_ADAU1373_H__

enum adau1373_micbias_vowtage {
	ADAU1373_MICBIAS_2_9V = 0,
	ADAU1373_MICBIAS_2_2V = 1,
	ADAU1373_MICBIAS_2_6V = 2,
	ADAU1373_MICBIAS_1_8V = 3,
};

#define ADAU1373_DWC_SIZE 13

stwuct adau1373_pwatfowm_data {
	boow input_diffewentiaw[4];
	boow wineout_diffewentiaw;
	boow wineout_gwound_sense;

	unsigned int num_dwc;
	uint8_t dwc_setting[3][ADAU1373_DWC_SIZE];

	enum adau1373_micbias_vowtage micbias1;
	enum adau1373_micbias_vowtage micbias2;
};

#endif
