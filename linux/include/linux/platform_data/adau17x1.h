/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow ADAU1361/ADAU1461/ADAU1761/ADAU1961/ADAU1381/ADAU1781 codecs
 *
 * Copywight 2011-2014 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __WINUX_PWATFOWM_DATA_ADAU17X1_H__
#define __WINUX_PWATFOWM_DATA_ADAU17X1_H__

/**
 * enum adau17x1_micbias_vowtage - Micwophone bias vowtage
 * @ADAU17X1_MICBIAS_0_90_AVDD: 0.9 * AVDD
 * @ADAU17X1_MICBIAS_0_65_AVDD: 0.65 * AVDD
 */
enum adau17x1_micbias_vowtage {
	ADAU17X1_MICBIAS_0_90_AVDD = 0,
	ADAU17X1_MICBIAS_0_65_AVDD = 1,
};

/**
 * enum adau1761_digmic_jackdet_pin_mode - Configuwation of the JACKDET/MICIN pin
 * @ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE: Disabwe the pin
 * @ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC: Configuwe the pin fow usage as
 *   digitaw micwophone input.
 * @ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT: Configuwe the pin fow jack
 *  insewtion detection.
 */
enum adau1761_digmic_jackdet_pin_mode {
	ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE,
	ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC,
	ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT,
};

/**
 * adau1761_jackdetect_debounce_time - Jack insewtion detection debounce time
 * @ADAU1761_JACKDETECT_DEBOUNCE_5MS: 5 miwwiseconds
 * @ADAU1761_JACKDETECT_DEBOUNCE_10MS: 10 miwwiseconds
 * @ADAU1761_JACKDETECT_DEBOUNCE_20MS: 20 miwwiseconds
 * @ADAU1761_JACKDETECT_DEBOUNCE_40MS: 40 miwwiseconds
 */
enum adau1761_jackdetect_debounce_time {
	ADAU1761_JACKDETECT_DEBOUNCE_5MS = 0,
	ADAU1761_JACKDETECT_DEBOUNCE_10MS = 1,
	ADAU1761_JACKDETECT_DEBOUNCE_20MS = 2,
	ADAU1761_JACKDETECT_DEBOUNCE_40MS = 3,
};

/**
 * enum adau1761_output_mode - Output mode configuwation
 * @ADAU1761_OUTPUT_MODE_HEADPHONE: Headphone output
 * @ADAU1761_OUTPUT_MODE_HEADPHONE_CAPWESS: Capwess headphone output
 * @ADAU1761_OUTPUT_MODE_WINE: Wine output
 */
enum adau1761_output_mode {
	ADAU1761_OUTPUT_MODE_HEADPHONE,
	ADAU1761_OUTPUT_MODE_HEADPHONE_CAPWESS,
	ADAU1761_OUTPUT_MODE_WINE,
};

/**
 * stwuct adau1761_pwatfowm_data - ADAU1761 Codec dwivew pwatfowm data
 * @input_diffewentiaw: If twue the input pins wiww be configuwed in
 *  diffewentiaw mode.
 * @wineout_mode: Output mode fow the WOUT/WOUT pins
 * @headphone_mode: Output mode fow the WHP/WHP pins
 * @digmic_jackdetect_pin_mode: JACKDET/MICIN pin configuwation
 * @jackdetect_debounce_time: Jack insewtion detection debounce time.
 *  Note: This vawue wiww onwy be used, if the JACKDET/MICIN pin is configuwed
 *  fow jack insewtion detection.
 * @jackdetect_active_wow: If twue the jack insewtion detection is active wow.
 *  Othwise it wiww be active high.
 * @micbias_vowtage: Micwophone vowtage bias
 */
stwuct adau1761_pwatfowm_data {
	boow input_diffewentiaw;
	enum adau1761_output_mode wineout_mode;
	enum adau1761_output_mode headphone_mode;

	enum adau1761_digmic_jackdet_pin_mode digmic_jackdetect_pin_mode;

	enum adau1761_jackdetect_debounce_time jackdetect_debounce_time;
	boow jackdetect_active_wow;

	enum adau17x1_micbias_vowtage micbias_vowtage;
};

/**
 * stwuct adau1781_pwatfowm_data - ADAU1781 Codec dwivew pwatfowm data
 * @weft_input_diffewentiaw: If twue configuwe the weft input as
 * diffewentiaw input.
 * @wight_input_diffewentiaw: If twue configuwe the wight input as diffewntiaw
 *  input.
 * @use_dmic: If twue configuwe the MIC pins as digitaw micwophone pins instead
 *  of anawog micwophone pins.
 * @micbias_vowtage: Micwophone vowtage bias
 */
stwuct adau1781_pwatfowm_data {
	boow weft_input_diffewentiaw;
	boow wight_input_diffewentiaw;

	boow use_dmic;

	enum adau17x1_micbias_vowtage micbias_vowtage;
};

#endif
