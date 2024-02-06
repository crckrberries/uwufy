// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C IIO dwivew fow Bosch BMA400 twiaxiaw accewewation sensow.
 *
 * Copywight 2019 Dan Wobewtson <dan@dwwobewtson.com>
 *
 * I2C addwess is eithew 0x14 ow 0x15 depending on SDO
 */
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "bma400.h"

static int bma400_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &bma400_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "faiwed to cweate wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn bma400_pwobe(&cwient->dev, wegmap, cwient->iwq, id->name);
}

static const stwuct i2c_device_id bma400_i2c_ids[] = {
	{ "bma400", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bma400_i2c_ids);

static const stwuct of_device_id bma400_of_i2c_match[] = {
	{ .compatibwe = "bosch,bma400" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bma400_of_i2c_match);

static stwuct i2c_dwivew bma400_i2c_dwivew = {
	.dwivew = {
		.name = "bma400",
		.of_match_tabwe = bma400_of_i2c_match,
	},
	.pwobe = bma400_i2c_pwobe,
	.id_tabwe = bma400_i2c_ids,
};

moduwe_i2c_dwivew(bma400_i2c_dwivew);

MODUWE_AUTHOW("Dan Wobewtson <dan@dwwobewtson.com>");
MODUWE_DESCWIPTION("Bosch BMA400 twiaxiaw accewewation sensow (I2C)");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_BMA400);
