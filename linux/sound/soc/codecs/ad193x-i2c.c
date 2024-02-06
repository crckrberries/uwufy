// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD1936/AD1937 audio dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>

#incwude "ad193x.h"

static const stwuct i2c_device_id ad193x_id[] = {
	{ "ad1936", AD193X },
	{ "ad1937", AD193X },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad193x_id);

static int ad193x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap_config config;
	const stwuct i2c_device_id *id = i2c_match_id(ad193x_id, cwient);

	config = ad193x_wegmap_config;
	config.vaw_bits = 8;
	config.weg_bits = 8;

	wetuwn ad193x_pwobe(&cwient->dev,
			    devm_wegmap_init_i2c(cwient, &config),
			    (enum ad193x_type)id->dwivew_data);
}

static stwuct i2c_dwivew ad193x_i2c_dwivew = {
	.dwivew = {
		.name = "ad193x",
	},
	.pwobe = ad193x_i2c_pwobe,
	.id_tabwe = ad193x_id,
};
moduwe_i2c_dwivew(ad193x_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC AD1936/AD1937 audio CODEC dwivew");
MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_WICENSE("GPW");
