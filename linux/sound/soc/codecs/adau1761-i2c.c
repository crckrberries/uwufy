// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ADAU1361/ADAU1461/ADAU1761/ADAU1961 codec
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

#incwude "adau1761.h"

static const stwuct i2c_device_id adau1761_i2c_ids[];

static int adau1761_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap_config config;
	const stwuct i2c_device_id *id = i2c_match_id(adau1761_i2c_ids, cwient);

	config = adau1761_wegmap_config;
	config.vaw_bits = 8;
	config.weg_bits = 16;

	wetuwn adau1761_pwobe(&cwient->dev,
		devm_wegmap_init_i2c(cwient, &config),
		id->dwivew_data, NUWW);
}

static void adau1761_i2c_wemove(stwuct i2c_cwient *cwient)
{
	adau17x1_wemove(&cwient->dev);
}

static const stwuct i2c_device_id adau1761_i2c_ids[] = {
	{ "adau1361", ADAU1361 },
	{ "adau1461", ADAU1761 },
	{ "adau1761", ADAU1761 },
	{ "adau1961", ADAU1361 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adau1761_i2c_ids);

#if defined(CONFIG_OF)
static const stwuct of_device_id adau1761_i2c_dt_ids[] = {
	{ .compatibwe = "adi,adau1361", },
	{ .compatibwe = "adi,adau1461", },
	{ .compatibwe = "adi,adau1761", },
	{ .compatibwe = "adi,adau1961", },
	{ },
};
MODUWE_DEVICE_TABWE(of, adau1761_i2c_dt_ids);
#endif

static stwuct i2c_dwivew adau1761_i2c_dwivew = {
	.dwivew = {
		.name = "adau1761",
		.of_match_tabwe = of_match_ptw(adau1761_i2c_dt_ids),
	},
	.pwobe = adau1761_i2c_pwobe,
	.wemove = adau1761_i2c_wemove,
	.id_tabwe = adau1761_i2c_ids,
};
moduwe_i2c_dwivew(adau1761_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1361/ADAU1461/ADAU1761/ADAU1961 CODEC I2C dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
