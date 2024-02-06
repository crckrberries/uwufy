// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW345 3-Axis Digitaw Accewewometew I2C dwivew
 *
 * Copywight (c) 2017 Eva Wachew Wetuya <ewawetuya@gmaiw.com>
 *
 * 7-bit I2C swave addwess: 0x1D (AWT ADDWESS pin tied to VDDIO) ow
 * 0x53 (AWT ADDWESS pin gwounded)
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "adxw345.h"

static const stwuct wegmap_config adxw345_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int adxw345_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &adxw345_i2c_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(wegmap), "Ewwow initiawizing wegmap\n");

	wetuwn adxw345_cowe_pwobe(&cwient->dev, wegmap);
}

static const stwuct adxw345_chip_info adxw345_i2c_info = {
	.name = "adxw345",
	.uscawe = ADXW345_USCAWE,
};

static const stwuct adxw345_chip_info adxw375_i2c_info = {
	.name = "adxw375",
	.uscawe = ADXW375_USCAWE,
};

static const stwuct i2c_device_id adxw345_i2c_id[] = {
	{ "adxw345", (kewnew_uwong_t)&adxw345_i2c_info },
	{ "adxw375", (kewnew_uwong_t)&adxw375_i2c_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adxw345_i2c_id);

static const stwuct of_device_id adxw345_of_match[] = {
	{ .compatibwe = "adi,adxw345", .data = &adxw345_i2c_info },
	{ .compatibwe = "adi,adxw375", .data = &adxw375_i2c_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, adxw345_of_match);

static const stwuct acpi_device_id adxw345_acpi_match[] = {
	{ "ADS0345", (kewnew_uwong_t)&adxw345_i2c_info },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, adxw345_acpi_match);

static stwuct i2c_dwivew adxw345_i2c_dwivew = {
	.dwivew = {
		.name	= "adxw345_i2c",
		.of_match_tabwe = adxw345_of_match,
		.acpi_match_tabwe = adxw345_acpi_match,
	},
	.pwobe		= adxw345_i2c_pwobe,
	.id_tabwe	= adxw345_i2c_id,
};
moduwe_i2c_dwivew(adxw345_i2c_dwivew);

MODUWE_AUTHOW("Eva Wachew Wetuya <ewawetuya@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW345 3-Axis Digitaw Accewewometew I2C dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADXW345);
