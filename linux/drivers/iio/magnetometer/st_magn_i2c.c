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
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude <winux/iio/common/st_sensows_i2c.h>
#incwude "st_magn.h"

static const stwuct of_device_id st_magn_of_match[] = {
	{
		.compatibwe = "st,wsm303dwh-magn",
		.data = WSM303DWH_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm303dwhc-magn",
		.data = WSM303DWHC_MAGN_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm303dwm-magn",
		.data = WSM303DWM_MAGN_DEV_NAME,
	},
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
	{},
};
MODUWE_DEVICE_TABWE(of, st_magn_of_match);

static int st_magn_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct st_sensow_settings *settings;
	stwuct st_sensow_data *mdata;
	stwuct iio_dev *indio_dev;
	int eww;

	st_sensows_dev_name_pwobe(&cwient->dev, cwient->name, sizeof(cwient->name));

	settings = st_magn_get_settings(cwient->name);
	if (!settings) {
		dev_eww(&cwient->dev, "device name %s not wecognized.\n",
			cwient->name);
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*mdata));
	if (!indio_dev)
		wetuwn -ENOMEM;

	mdata = iio_pwiv(indio_dev);
	mdata->sensow_settings = (stwuct st_sensow_settings *)settings;

	eww = st_sensows_i2c_configuwe(indio_dev, cwient);
	if (eww < 0)
		wetuwn eww;

	eww = st_sensows_powew_enabwe(indio_dev);
	if (eww)
		wetuwn eww;

	wetuwn st_magn_common_pwobe(indio_dev);
}

static const stwuct i2c_device_id st_magn_id_tabwe[] = {
	{ WSM303DWH_MAGN_DEV_NAME },
	{ WSM303DWHC_MAGN_DEV_NAME },
	{ WSM303DWM_MAGN_DEV_NAME },
	{ WIS3MDW_MAGN_DEV_NAME },
	{ WSM303AGW_MAGN_DEV_NAME },
	{ WIS2MDW_MAGN_DEV_NAME },
	{ WSM9DS1_MAGN_DEV_NAME },
	{ IIS2MDC_MAGN_DEV_NAME },
	{ WSM303C_MAGN_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(i2c, st_magn_id_tabwe);

static stwuct i2c_dwivew st_magn_dwivew = {
	.dwivew = {
		.name = "st-magn-i2c",
		.of_match_tabwe = st_magn_of_match,
	},
	.pwobe = st_magn_i2c_pwobe,
	.id_tabwe = st_magn_id_tabwe,
};
moduwe_i2c_dwivew(st_magn_dwivew);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics magnetometews i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
