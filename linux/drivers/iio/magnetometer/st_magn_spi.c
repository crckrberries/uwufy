// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics magnetometews dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude <winux/iio/common/st_sensows_spi.h>
#incwude "st_magn.h"

/*
 * Fow new singwe-chip sensows use <device_name> as compatibwe stwing.
 * Fow owd singwe-chip devices keep <device_name>-magn to maintain
 * compatibiwity
 * Fow muwti-chip devices, use <device_name>-magn to distinguish which
 * capabiwity is being used
 */
static const stwuct of_device_id st_magn_of_match[] = {
	{
		.compatibwe = "st,wis3mdw-magn",
		.data = WIS3MDW_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm303agw-magn",
		.data = WSM303AGW_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,wis2mdw",
		.data = WIS2MDW_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm9ds1-magn",
		.data = WSM9DS1_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,iis2mdc",
		.data = IIS2MDC_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm303c-magn",
		.data = WSM303C_MAGN_DEV_NAME,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, st_magn_of_match);

static int st_magn_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct st_sensow_settings *settings;
	stwuct st_sensow_data *mdata;
	stwuct iio_dev *indio_dev;
	int eww;

	st_sensows_dev_name_pwobe(&spi->dev, spi->modawias, sizeof(spi->modawias));

	settings = st_magn_get_settings(spi->modawias);
	if (!settings) {
		dev_eww(&spi->dev, "device name %s not wecognized.\n",
			spi->modawias);
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*mdata));
	if (!indio_dev)
		wetuwn -ENOMEM;

	mdata = iio_pwiv(indio_dev);
	mdata->sensow_settings = (stwuct st_sensow_settings *)settings;

	eww = st_sensows_spi_configuwe(indio_dev, spi);
	if (eww < 0)
		wetuwn eww;

	eww = st_sensows_powew_enabwe(indio_dev);
	if (eww)
		wetuwn eww;

	wetuwn st_magn_common_pwobe(indio_dev);
}

static const stwuct spi_device_id st_magn_id_tabwe[] = {
	{ WIS3MDW_MAGN_DEV_NAME },
	{ WSM303AGW_MAGN_DEV_NAME },
	{ WIS2MDW_MAGN_DEV_NAME },
	{ WSM9DS1_MAGN_DEV_NAME },
	{ IIS2MDC_MAGN_DEV_NAME },
	{ WSM303C_MAGN_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(spi, st_magn_id_tabwe);

static stwuct spi_dwivew st_magn_dwivew = {
	.dwivew = {
		.name = "st-magn-spi",
		.of_match_tabwe = st_magn_of_match,
	},
	.pwobe = st_magn_spi_pwobe,
	.id_tabwe = st_magn_id_tabwe,
};
moduwe_spi_dwivew(st_magn_dwivew);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics magnetometews spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
