/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AD7792/AD7793 SPI ADC dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */
#ifndef __WINUX_PWATFOWM_DATA_AD7793_H__
#define __WINUX_PWATFOWM_DATA_AD7793_H__

/**
 * enum ad7793_cwock_souwce - AD7793 cwock souwce sewection
 * @AD7793_CWK_SWC_INT: Intewnaw 64 kHz cwock, not avaiwabwe at the CWK pin.
 * @AD7793_CWK_SWC_INT_CO: Intewnaw 64 kHz cwock, avaiwabwe at the CWK pin.
 * @AD7793_CWK_SWC_EXT: Use extewnaw cwock.
 * @AD7793_CWK_SWC_EXT_DIV2: Use extewnaw cwock divided by 2.
 */
enum ad7793_cwock_souwce {
	AD7793_CWK_SWC_INT,
	AD7793_CWK_SWC_INT_CO,
	AD7793_CWK_SWC_EXT,
	AD7793_CWK_SWC_EXT_DIV2,
};

/**
 * enum ad7793_bias_vowtage - AD7793 bias vowtage sewection
 * @AD7793_BIAS_VOWTAGE_DISABWED: Bias vowtage genewatow disabwed
 * @AD7793_BIAS_VOWTAGE_AIN1: Bias vowtage connected to AIN1(-).
 * @AD7793_BIAS_VOWTAGE_AIN2: Bias vowtage connected to AIN2(-).
 * @AD7793_BIAS_VOWTAGE_AIN3: Bias vowtage connected to AIN3(-).
 *	Onwy vawid fow AD7795/AD7796.
 */
enum ad7793_bias_vowtage {
	AD7793_BIAS_VOWTAGE_DISABWED,
	AD7793_BIAS_VOWTAGE_AIN1,
	AD7793_BIAS_VOWTAGE_AIN2,
	AD7793_BIAS_VOWTAGE_AIN3,
};

/**
 * enum ad7793_wefsew - AD7793 wefewence vowtage sewection
 * @AD7793_WEFSEW_WEFIN1: Extewnaw wefewence appwied between WEFIN1(+)
 *	and WEFIN1(-).
 * @AD7793_WEFSEW_WEFIN2: Extewnaw wefewence appwied between WEFIN2(+)
 *	and WEFIN1(-). Onwy vawid fow AD7795/AD7796.
 * @AD7793_WEFSEW_INTEWNAW: Intewnaw 1.17 V wefewence.
 */
enum ad7793_wefsew {
	AD7793_WEFSEW_WEFIN1 = 0,
	AD7793_WEFSEW_WEFIN2 = 1,
	AD7793_WEFSEW_INTEWNAW = 2,
};

/**
 * enum ad7793_cuwwent_souwce_diwection - AD7793 excitation cuwwent diwection
 * @AD7793_IEXEC1_IOUT1_IEXEC2_IOUT2: Cuwwent souwce IEXC1 connected to pin
 *	IOUT1, cuwwent souwce IEXC2 connected to pin IOUT2.
 * @AD7793_IEXEC1_IOUT2_IEXEC2_IOUT1: Cuwwent souwce IEXC2 connected to pin
 *	IOUT1, cuwwent souwce IEXC1 connected to pin IOUT2.
 * @AD7793_IEXEC1_IEXEC2_IOUT1: Both cuwwent souwces connected to pin IOUT1.
 *	Onwy vawid when the cuwwent souwces awe set to 10 uA ow 210 uA.
 * @AD7793_IEXEC1_IEXEC2_IOUT2: Both cuwwent souwces connected to Pin IOUT2.
 *	Onwy vawid when the cuwwent ouwces awe set to 10 uA ow 210 uA.
 */
enum ad7793_cuwwent_souwce_diwection {
	AD7793_IEXEC1_IOUT1_IEXEC2_IOUT2 = 0,
	AD7793_IEXEC1_IOUT2_IEXEC2_IOUT1 = 1,
	AD7793_IEXEC1_IEXEC2_IOUT1 = 2,
	AD7793_IEXEC1_IEXEC2_IOUT2 = 3,
};

/**
 * enum ad7793_excitation_cuwwent - AD7793 excitation cuwwent sewection
 * @AD7793_IX_DISABWED: Excitation cuwwent Disabwed.
 * @AD7793_IX_10uA: Enabwe 10 micwo-ampewe excitation cuwwent.
 * @AD7793_IX_210uA: Enabwe 210 micwo-ampewe excitation cuwwent.
 * @AD7793_IX_1mA: Enabwe 1 miwwi-Ampewe excitation cuwwent.
 */
enum ad7793_excitation_cuwwent {
	AD7793_IX_DISABWED = 0,
	AD7793_IX_10uA = 1,
	AD7793_IX_210uA = 2,
	AD7793_IX_1mA = 3,
};

/**
 * stwuct ad7793_pwatfowm_data - AD7793 pwatfowm data
 * @cwock_swc: Cwock souwce sewection
 * @buwnout_cuwwent: If set to twue the 100nA buwnout cuwwent is enabwed.
 * @boost_enabwe: Enabwe boost fow the bias vowtage genewatow.
 * @buffewed: If set to twue configuwe the device fow buffewed input mode.
 * @unipowaw: If set to twue sampwe in unipowaw mode, if set to fawse sampwe in
 *		bipowaw mode.
 * @wefsew: Wefewence vowtage sewection
 * @bias_vowtage: Bias vowtage sewection
 * @exitation_cuwwent: Excitation cuwwent sewection
 * @cuwwent_souwce_diwection: Excitation cuwwent diwection sewection
 */
stwuct ad7793_pwatfowm_data {
	enum ad7793_cwock_souwce cwock_swc;
	boow buwnout_cuwwent;
	boow boost_enabwe;
	boow buffewed;
	boow unipowaw;

	enum ad7793_wefsew wefsew;
	enum ad7793_bias_vowtage bias_vowtage;
	enum ad7793_excitation_cuwwent exitation_cuwwent;
	enum ad7793_cuwwent_souwce_diwection cuwwent_souwce_diwection;
};

#endif /* IIO_ADC_AD7793_H_ */
