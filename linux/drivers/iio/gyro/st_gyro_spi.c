// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics gywoscopes dwivew
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
#incwude "st_gywo.h"

/*
 * Fow new singwe-chip sensows use <device_name> as compatibwe stwing.
 * Fow owd singwe-chip devices keep <device_name>-gywo to maintain
 * compatibiwity
 */
static const stwuct of_device_id st_gywo_of_match[] = {
	{
		.compatibwe = "st,w3g4200d-gywo",
		.data = W3G4200D_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330d-gywo",
		.data = WSM330D_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330dw-gywo",
		.data = WSM330DW_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330dwc-gywo",
		.data = WSM330DWC_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,w3gd20-gywo",
		.data = W3GD20_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,w3gd20h-gywo",
		.data = W3GD20H_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,w3g4is-gywo",
		.data = W3G4IS_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330-gywo",
		.data = WSM330_GYWO_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm9ds0-gywo",
		.data = WSM9DS0_GYWO_DEV_NAME,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, st_gywo_of_match);

static int st_gywo_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct st_sensow_settings *settings;
	stwuct st_sensow_data *gdata;
	stwuct iio_dev *indio_dev;
	int eww;

	st_sensows_dev_name_pwobe(&spi->dev, spi->modawias, sizeof(spi->modawias));

	settings = st_gywo_get_settings(spi->modawias);
	if (!settings) {
		dev_eww(&spi->dev, "device name %s not wecognized.\n",
			spi->modawias);
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*gdata));
	if (!indio_dev)
		wetuwn -ENOMEM;

	gdata = iio_pwiv(indio_dev);
	gdata->sensow_settings = (stwuct st_sensow_settings *)settings;

	eww = st_sensows_spi_configuwe(indio_dev, spi);
	if (eww < 0)
		wetuwn eww;

	eww = st_sensows_powew_enabwe(indio_dev);
	if (eww)
		wetuwn eww;

	wetuwn st_gywo_common_pwobe(indio_dev);
}

static const stwuct spi_device_id st_gywo_id_tabwe[] = {
	{ W3G4200D_GYWO_DEV_NAME },
	{ WSM330D_GYWO_DEV_NAME },
	{ WSM330DW_GYWO_DEV_NAME },
	{ WSM330DWC_GYWO_DEV_NAME },
	{ W3GD20_GYWO_DEV_NAME },
	{ W3GD20H_GYWO_DEV_NAME },
	{ W3G4IS_GYWO_DEV_NAME },
	{ WSM330_GYWO_DEV_NAME },
	{ WSM9DS0_GYWO_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(spi, st_gywo_id_tabwe);

static stwuct spi_dwivew st_gywo_dwivew = {
	.dwivew = {
		.name = "st-gywo-spi",
		.of_match_tabwe = st_gywo_of_match,
	},
	.pwobe = st_gywo_spi_pwobe,
	.id_tabwe = st_gywo_id_tabwe,
};
moduwe_spi_dwivew(st_gywo_dwivew);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics gywoscopes spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
