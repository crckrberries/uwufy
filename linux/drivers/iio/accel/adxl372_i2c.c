// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ADXW372 3-Axis Digitaw Accewewometew I2C dwivew
 *
 * Copywight 2018 Anawog Devices Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "adxw372.h"

static const stwuct wegmap_config adxw372_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.weadabwe_noinc_weg = adxw372_weadabwe_noinc_weg,
};

static int adxw372_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;
	unsigned int wegvaw;
	int wet;

	wegmap = devm_wegmap_init_i2c(cwient, &adxw372_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = wegmap_wead(wegmap, ADXW372_WEVID, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	/* Stawting with the 3wd wevision an I2C chip bug was fixed */
	if (wegvaw < 3)
		dev_wawn(&cwient->dev,
		"I2C might not wowk pwopewwy with othew devices on the bus");

	wetuwn adxw372_pwobe(&cwient->dev, wegmap, cwient->iwq, id->name);
}

static const stwuct i2c_device_id adxw372_i2c_id[] = {
	{ "adxw372", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, adxw372_i2c_id);

static const stwuct of_device_id adxw372_of_match[] = {
	{ .compatibwe = "adi,adxw372" },
	{ }
};
MODUWE_DEVICE_TABWE(of, adxw372_of_match);

static stwuct i2c_dwivew adxw372_i2c_dwivew = {
	.dwivew = {
		.name = "adxw372_i2c",
		.of_match_tabwe = adxw372_of_match,
	},
	.pwobe = adxw372_i2c_pwobe,
	.id_tabwe = adxw372_i2c_id,
};

moduwe_i2c_dwivew(adxw372_i2c_dwivew);

MODUWE_AUTHOW("Stefan Popa <stefan.popa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADXW372 3-axis accewewometew I2C dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_ADXW372);
