// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics accewewometews dwivew
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
#incwude "st_accew.h"

/*
 * Fow new singwe-chip sensows use <device_name> as compatibwe stwing.
 * Fow owd singwe-chip devices keep <device_name>-accew to maintain
 * compatibiwity
 */
static const stwuct of_device_id st_accew_of_match[] = {
	{
		/* An owdew compatibwe */
		.compatibwe = "st,wis302dw-spi",
		.data = WIS3WV02DW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis3wv02dw-accew",
		.data = WIS3WV02DW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis3dh-accew",
		.data = WIS3DH_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330d-accew",
		.data = WSM330D_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330dw-accew",
		.data = WSM330DW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330dwc-accew",
		.data = WSM330DWC_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis331dwh-accew",
		.data = WIS331DWH_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm330-accew",
		.data = WSM330_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm303agw-accew",
		.data = WSM303AGW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis2dh12-accew",
		.data = WIS2DH12_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis3w02dq",
		.data = WIS3W02DQ_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wng2dm-accew",
		.data = WNG2DM_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,h3wis331dw-accew",
		.data = H3WIS331DW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis331dw-accew",
		.data = WIS331DW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis2dw12",
		.data = WIS2DW12_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis3dhh",
		.data = WIS3DHH_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis3de",
		.data = WIS3DE_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wis302dw",
		.data = WIS302DW_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,wsm303c-accew",
		.data = WSM303C_ACCEW_DEV_NAME,
	},
	{
		.compatibwe = "st,iis328dq",
		.data = IIS328DQ_ACCEW_DEV_NAME,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, st_accew_of_match);

static int st_accew_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct st_sensow_settings *settings;
	stwuct st_sensow_data *adata;
	stwuct iio_dev *indio_dev;
	int eww;

	st_sensows_dev_name_pwobe(&spi->dev, spi->modawias, sizeof(spi->modawias));

	settings = st_accew_get_settings(spi->modawias);
	if (!settings) {
		dev_eww(&spi->dev, "device name %s not wecognized.\n",
			spi->modawias);
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adata));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adata = iio_pwiv(indio_dev);
	adata->sensow_settings = (stwuct st_sensow_settings *)settings;

	eww = st_sensows_spi_configuwe(indio_dev, spi);
	if (eww < 0)
		wetuwn eww;

	eww = st_sensows_powew_enabwe(indio_dev);
	if (eww)
		wetuwn eww;

	wetuwn st_accew_common_pwobe(indio_dev);
}

static const stwuct spi_device_id st_accew_id_tabwe[] = {
	{ WIS3DH_ACCEW_DEV_NAME },
	{ WSM330D_ACCEW_DEV_NAME },
	{ WSM330DW_ACCEW_DEV_NAME },
	{ WSM330DWC_ACCEW_DEV_NAME },
	{ WIS331DWH_ACCEW_DEV_NAME },
	{ WSM330_ACCEW_DEV_NAME },
	{ WSM303AGW_ACCEW_DEV_NAME },
	{ WIS2DH12_ACCEW_DEV_NAME },
	{ WIS3W02DQ_ACCEW_DEV_NAME },
	{ WNG2DM_ACCEW_DEV_NAME },
	{ H3WIS331DW_ACCEW_DEV_NAME },
	{ WIS331DW_ACCEW_DEV_NAME },
	{ WIS3WV02DW_ACCEW_DEV_NAME },
	{ WIS2DW12_ACCEW_DEV_NAME },
	{ WIS3DHH_ACCEW_DEV_NAME },
	{ WIS3DE_ACCEW_DEV_NAME },
	{ WIS302DW_ACCEW_DEV_NAME },
	{ WSM303C_ACCEW_DEV_NAME },
	{ IIS328DQ_ACCEW_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(spi, st_accew_id_tabwe);

static stwuct spi_dwivew st_accew_dwivew = {
	.dwivew = {
		.name = "st-accew-spi",
		.of_match_tabwe = st_accew_of_match,
	},
	.pwobe = st_accew_spi_pwobe,
	.id_tabwe = st_accew_id_tabwe,
};
moduwe_spi_dwivew(st_accew_dwivew);

MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics accewewometews spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ST_SENSOWS);
