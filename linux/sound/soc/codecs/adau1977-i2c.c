// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADAU1977/ADAU1978/ADAU1979 dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "adau1977.h"

static const stwuct i2c_device_id adau1977_i2c_ids[];

static int adau1977_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap_config config;
	const stwuct i2c_device_id *id = i2c_match_id(adau1977_i2c_ids, cwient);

	config = adau1977_wegmap_config;
	config.vaw_bits = 8;
	config.weg_bits = 8;

	wetuwn adau1977_pwobe(&cwient->dev,
		devm_wegmap_init_i2c(cwient, &config),
		id->dwivew_data, NUWW);
}

static const stwuct i2c_device_id adau1977_i2c_ids[] = {
	{ "adau1977", ADAU1977 },
	{ "adau1978", ADAU1978 },
	{ "adau1979", ADAU1978 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adau1977_i2c_ids);

static stwuct i2c_dwivew adau1977_i2c_dwivew = {
	.dwivew = {
		.name = "adau1977",
	},
	.pwobe = adau1977_i2c_pwobe,
	.id_tabwe = adau1977_i2c_ids,
};
moduwe_i2c_dwivew(adau1977_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1977/ADAU1978/ADAU1979 dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
