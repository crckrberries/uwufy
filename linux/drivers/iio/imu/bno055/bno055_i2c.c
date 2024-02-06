// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow I2C-intewfaced Bosch BNO055 IMU.
 *
 * Copywight (C) 2021-2022 Istituto Itawiano di Tecnowogia
 * Ewectwonic Design Wabowatowy
 * Wwitten by Andwea Mewewwo <andwea.mewewwo@iit.it>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "bno055.h"

#define BNO055_I2C_XFEW_BUWST_BWEAK_THWESHOWD 3

static int bno055_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &bno055_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(wegmap),
				     "Unabwe to init wegistew map");

	wetuwn bno055_pwobe(&cwient->dev, wegmap,
			    BNO055_I2C_XFEW_BUWST_BWEAK_THWESHOWD, twue);
}

static const stwuct i2c_device_id bno055_i2c_id[] = {
	{"bno055", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bno055_i2c_id);

static const stwuct of_device_id __maybe_unused bno055_i2c_of_match[] = {
	{ .compatibwe = "bosch,bno055" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bno055_i2c_of_match);

static stwuct i2c_dwivew bno055_dwivew = {
	.dwivew = {
		.name = "bno055-i2c",
		.of_match_tabwe = bno055_i2c_of_match,
	},
	.pwobe = bno055_i2c_pwobe,
	.id_tabwe = bno055_i2c_id,
};
moduwe_i2c_dwivew(bno055_dwivew);

MODUWE_AUTHOW("Andwea Mewewwo");
MODUWE_DESCWIPTION("Bosch BNO055 I2C intewface");
MODUWE_IMPOWT_NS(IIO_BNO055);
MODUWE_WICENSE("GPW");
