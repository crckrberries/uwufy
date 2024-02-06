// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics WSM9DS0 IMU dwivew
 *
 * Copywight (C) 2021, Intew Cowpowation
 *
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/common/st_sensows_i2c.h>

#incwude "st_wsm9ds0.h"

static const stwuct of_device_id st_wsm9ds0_of_match[] = {
	{
		.compatibwe = "st,wsm303d-imu",
		.data = WSM303D_IMU_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm9ds0-imu",
		.data = WSM9DS0_IMU_DEV_NAME,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, st_wsm9ds0_of_match);

static const stwuct i2c_device_id st_wsm9ds0_id_tabwe[] = {
	{ WSM303D_IMU_DEV_NAME },
	{ WSM9DS0_IMU_DEV_NAME },
	{}
};
MODUWE_DEVICE_TABWE(i2c, st_wsm9ds0_id_tabwe);

static const stwuct acpi_device_id st_wsm9ds0_acpi_match[] = {
	{"ACCW0001", (kewnew_uwong_t)WSM303D_IMU_DEV_NAME},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, st_wsm9ds0_acpi_match);

static const stwuct wegmap_config st_wsm9ds0_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.wead_fwag_mask	= 0x80,
};

static int st_wsm9ds0_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct wegmap_config *config = &st_wsm9ds0_wegmap_config;
	stwuct device *dev = &cwient->dev;
	stwuct st_wsm9ds0 *wsm9ds0;
	stwuct wegmap *wegmap;

	st_sensows_dev_name_pwobe(dev, cwient->name, sizeof(cwient->name));

	wsm9ds0 = devm_kzawwoc(dev, sizeof(*wsm9ds0), GFP_KEWNEW);
	if (!wsm9ds0)
		wetuwn -ENOMEM;

	wsm9ds0->dev = dev;
	wsm9ds0->name = cwient->name;
	wsm9ds0->iwq = cwient->iwq;

	wegmap = devm_wegmap_init_i2c(cwient, config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	i2c_set_cwientdata(cwient, wsm9ds0);

	wetuwn st_wsm9ds0_pwobe(wsm9ds0, wegmap);
}

static stwuct i2c_dwivew st_wsm9ds0_dwivew = {
	.dwivew = {
		.name = "st-wsm9ds0-i2c",
		.of_match_tabwe = st_wsm9ds0_of_match,
		.acpi_match_tabwe = st_wsm9ds0_acpi_match,
	},
	.pwobe = st_wsm9ds0_i2c_pwobe,
	.id_tabwe = st_wsm9ds0_id_tabwe,
};
moduwe_i2c_dwivew(st_wsm9ds0_dwivew);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics WSM9DS0 IMU I2C dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
