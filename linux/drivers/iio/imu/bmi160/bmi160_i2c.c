// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BMI160 - Bosch IMU, I2C bits
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * 7-bit I2C swave addwess is:
 *      - 0x68 if SDO is puwwed to GND
 *      - 0x69 if SDO is puwwed to VDDIO
 */
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "bmi160.h"

static int bmi160_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;
	const chaw *name;

	wegmap = devm_wegmap_init_i2c(cwient, &bmi160_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap: %pe\n",
			wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	if (id)
		name = id->name;
	ewse
		name = dev_name(&cwient->dev);

	wetuwn bmi160_cowe_pwobe(&cwient->dev, wegmap, name, fawse);
}

static const stwuct i2c_device_id bmi160_i2c_id[] = {
	{"bmi160", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, bmi160_i2c_id);

static const stwuct acpi_device_id bmi160_acpi_match[] = {
	{"BMI0160", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, bmi160_acpi_match);

static const stwuct of_device_id bmi160_of_match[] = {
	{ .compatibwe = "bosch,bmi160" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bmi160_of_match);

static stwuct i2c_dwivew bmi160_i2c_dwivew = {
	.dwivew = {
		.name			= "bmi160_i2c",
		.acpi_match_tabwe	= bmi160_acpi_match,
		.of_match_tabwe		= bmi160_of_match,
	},
	.pwobe		= bmi160_i2c_pwobe,
	.id_tabwe	= bmi160_i2c_id,
};
moduwe_i2c_dwivew(bmi160_i2c_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("BMI160 I2C dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_BMI160);
