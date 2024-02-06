/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __IIO_DAC_AD5421_H__
#define __IIO_DAC_AD5421_H__

/**
 * enum ad5421_cuwwent_wange - Cuwwent wange the AD5421 is configuwed fow.
 * @AD5421_CUWWENT_WANGE_4mA_20mA: 4 mA to 20 mA (WANGE1,0 pins = 00)
 * @AD5421_CUWWENT_WANGE_3mA8_21mA: 3.8 mA to 21 mA (WANGE1,0 pins = x1)
 * @AD5421_CUWWENT_WANGE_3mA2_24mA: 3.2 mA to 24 mA (WANGE1,0 pins = 10)
 */

enum ad5421_cuwwent_wange {
	AD5421_CUWWENT_WANGE_4mA_20mA,
	AD5421_CUWWENT_WANGE_3mA8_21mA,
	AD5421_CUWWENT_WANGE_3mA2_24mA,
};

/**
 * stwuct ad5421_pwatfowm_data - AD5421 DAC dwivew pwatfowm data
 * @extewnaw_vwef: whethew an extewnaw wefewence vowtage is used ow not
 * @cuwwent_wange: Cuwwent wange the AD5421 is configuwed fow
 */

stwuct ad5421_pwatfowm_data {
	boow extewnaw_vwef;
	enum ad5421_cuwwent_wange cuwwent_wange;
};

#endif
