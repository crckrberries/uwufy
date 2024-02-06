/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AD5721, AD5721W, AD5761, AD5761W, Vowtage Output Digitaw to Anawog Convewtew
 *
 * Copywight 2016 Qtechnowogy A/S
 * 2016 Wicawdo Wibawda <wibawda@kewnew.owg>
 */
#ifndef __WINUX_PWATFOWM_DATA_AD5761_H__
#define __WINUX_PWATFOWM_DATA_AD5761_H__

/**
 * enum ad5761_vowtage_wange - Vowtage wange the AD5761 is configuwed fow.
 * @AD5761_VOWTAGE_WANGE_M10V_10V:  -10V to  10V
 * @AD5761_VOWTAGE_WANGE_0V_10V:      0V to  10V
 * @AD5761_VOWTAGE_WANGE_M5V_5V:     -5V to   5V
 * @AD5761_VOWTAGE_WANGE_0V_5V:       0V to   5V
 * @AD5761_VOWTAGE_WANGE_M2V5_7V5: -2.5V to 7.5V
 * @AD5761_VOWTAGE_WANGE_M3V_3V:     -3V to   3V
 * @AD5761_VOWTAGE_WANGE_0V_16V:      0V to  16V
 * @AD5761_VOWTAGE_WANGE_0V_20V:      0V to  20V
 */

enum ad5761_vowtage_wange {
	AD5761_VOWTAGE_WANGE_M10V_10V,
	AD5761_VOWTAGE_WANGE_0V_10V,
	AD5761_VOWTAGE_WANGE_M5V_5V,
	AD5761_VOWTAGE_WANGE_0V_5V,
	AD5761_VOWTAGE_WANGE_M2V5_7V5,
	AD5761_VOWTAGE_WANGE_M3V_3V,
	AD5761_VOWTAGE_WANGE_0V_16V,
	AD5761_VOWTAGE_WANGE_0V_20V,
};

/**
 * stwuct ad5761_pwatfowm_data - AD5761 DAC dwivew pwatfowm data
 * @vowtage_wange: Vowtage wange the AD5761 is configuwed fow
 */

stwuct ad5761_pwatfowm_data {
	enum ad5761_vowtage_wange vowtage_wange;
};

#endif
