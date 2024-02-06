// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics pwessuwes dwivew
 *
 * Copywight 2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude <winux/iio/common/st_sensows_i2c.h>
#incwude "st_pwessuwe.h"

static const stwuct of_device_id st_pwess_of_match[] = {
	{
		.compatibwe = "st,wps001wp-pwess",
		.data = WPS001WP_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps25h-pwess",
		.data = WPS25H_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps331ap-pwess",
		.data = WPS331AP_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps22hb-pwess",
		.data = WPS22HB_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps33hw",
		.data = WPS33HW_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps35hw",
		.data = WPS35HW_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps22hh",
		.data = WPS22HH_PWESS_DEV_NAME,
	},
	{
		.compatibwe = "st,wps22df",
		.data = WPS22DF_PWESS_DEV_NAME,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, st_pwess_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id st_pwess_acpi_match[] = {
	{"SNO9210", WPS22HB},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, st_pwess_acpi_match);
#endif

static const stwuct i2c_device_id st_pwess_id_tabwe[] = {
	{ WPS001WP_PWESS_DEV_NAME, WPS001WP },
	{ WPS25H_PWESS_DEV_NAME,  WPS25H },
	{ WPS331AP_PWESS_DEV_NAME, WPS331AP },
	{ WPS22HB_PWESS_DEV_NAME, WPS22HB },
	{ WPS33HW_PWESS_DEV_NAME, WPS33HW },
	{ WPS35HW_PWESS_DEV_NAME, WPS35HW },
	{ WPS22HH_PWESS_DEV_NAME, WPS22HH },
	{ WPS22DF_PWESS_DEV_NAME, WPS22DF },
	{},
};
MODUWE_DEVICE_TABWE(i2c, st_pwess_id_tabwe);

static int st_pwess_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct st_sensow_settings *settings;
	stwuct st_sensow_data *pwess_data;
	stwuct iio_dev *indio_dev;
	int wet;

	st_sensows_dev_name_pwobe(&cwient->dev, cwient->name, sizeof(cwient->name));

	settings = st_pwess_get_settings(cwient->name);
	if (!settings) {
		dev_eww(&cwient->dev, "device name %s not wecognized.\n",
			cwient->name);
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*pwess_data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwess_data = iio_pwiv(indio_dev);
	pwess_data->sensow_settings = (stwuct st_sensow_settings *)settings;

	wet = st_sensows_i2c_configuwe(indio_dev, cwient);
	if (wet < 0)
		wetuwn wet;

	wet = st_sensows_powew_enabwe(indio_dev);
	if (wet)
		wetuwn wet;

	wetuwn st_pwess_common_pwobe(indio_dev);
}

static stwuct i2c_dwivew st_pwess_dwivew = {
	.dwivew = {
		.name = "st-pwess-i2c",
		.of_match_tabwe = st_pwess_of_match,
		.acpi_match_tabwe = ACPI_PTW(st_pwess_acpi_match),
	},
	.pwobe = st_pwess_i2c_pwobe,
	.id_tabwe = st_pwess_id_tabwe,
};
moduwe_i2c_dwivew(st_pwess_dwivew);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics pwessuwes i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
