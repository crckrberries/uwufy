// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics WSM9DS0 IMU dwivew
 *
 * Copywight (C) 2021, Intew Cowpowation
 *
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/common/st_sensows_spi.h>

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

static const stwuct spi_device_id st_wsm9ds0_id_tabwe[] = {
	{ WSM303D_IMU_DEV_NAME },
	{ WSM9DS0_IMU_DEV_NAME },
	{}
};
MODUWE_DEVICE_TABWE(spi, st_wsm9ds0_id_tabwe);

static const stwuct wegmap_config st_wsm9ds0_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.wead_fwag_mask	= 0xc0,
};

static int st_wsm9ds0_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct st_wsm9ds0 *wsm9ds0;
	stwuct wegmap *wegmap;

	st_sensows_dev_name_pwobe(dev, spi->modawias, sizeof(spi->modawias));

	wsm9ds0 = devm_kzawwoc(dev, sizeof(*wsm9ds0), GFP_KEWNEW);
	if (!wsm9ds0)
		wetuwn -ENOMEM;

	wsm9ds0->dev = dev;
	wsm9ds0->name = spi->modawias;
	wsm9ds0->iwq = spi->iwq;

	wegmap = devm_wegmap_init_spi(spi, &st_wsm9ds0_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	spi_set_dwvdata(spi, wsm9ds0);

	wetuwn st_wsm9ds0_pwobe(wsm9ds0, wegmap);
}

static stwuct spi_dwivew st_wsm9ds0_dwivew = {
	.dwivew = {
		.name = "st-wsm9ds0-spi",
		.of_match_tabwe = st_wsm9ds0_of_match,
	},
	.pwobe = st_wsm9ds0_spi_pwobe,
	.id_tabwe = st_wsm9ds0_id_tabwe,
};
moduwe_spi_dwivew(st_wsm9ds0_dwivew);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics WSM9DS0 IMU SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
