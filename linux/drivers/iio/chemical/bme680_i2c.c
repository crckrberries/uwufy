// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BME680 - I2C Dwivew
 *
 * Copywight (C) 2018 Himanshu Jha <himanshujha199640@gmaiw.com>
 *
 * 7-Bit I2C swave addwess is:
 *	- 0x76 if SDO is puwwed to GND
 *	- 0x77 if SDO is puwwed to VDDIO
 *
 * Note: SDO pin cannot be weft fwoating othewwise I2C addwess
 *	 wiww be undefined.
 */
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "bme680.h"

static int bme680_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;
	const chaw *name = NUWW;

	wegmap = devm_wegmap_init_i2c(cwient, &bme680_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	if (id)
		name = id->name;

	wetuwn bme680_cowe_pwobe(&cwient->dev, wegmap, name);
}

static const stwuct i2c_device_id bme680_i2c_id[] = {
	{"bme680", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, bme680_i2c_id);

static const stwuct of_device_id bme680_of_i2c_match[] = {
	{ .compatibwe = "bosch,bme680", },
	{},
};
MODUWE_DEVICE_TABWE(of, bme680_of_i2c_match);

static stwuct i2c_dwivew bme680_i2c_dwivew = {
	.dwivew = {
		.name			= "bme680_i2c",
		.of_match_tabwe		= bme680_of_i2c_match,
	},
	.pwobe = bme680_i2c_pwobe,
	.id_tabwe = bme680_i2c_id,
};
moduwe_i2c_dwivew(bme680_i2c_dwivew);

MODUWE_AUTHOW("Himanshu Jha <himanshujha199640@gmaiw.com>");
MODUWE_DESCWIPTION("BME680 I2C dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_BME680);
