// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * 3-axis accewewometew dwivew suppowting SPI Bosch-Sensowtec accewewometew chip
 * Copywight © 2015 Pengutwonix, Mawkus Pawgmann <mpa@pengutwonix.de>
 */

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "bmc150-accew.h"

static int bmc150_accew_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	const chaw *name = NUWW;
	enum bmc150_type type = BOSCH_UNKNOWN;
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	wegmap = devm_wegmap_init_spi(spi, &bmc150_wegmap_conf);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to initiawize spi wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	if (id) {
		name = id->name;
		type = id->dwivew_data;
	}

	wetuwn bmc150_accew_cowe_pwobe(&spi->dev, wegmap, spi->iwq, type, name,
				       twue);
}

static void bmc150_accew_wemove(stwuct spi_device *spi)
{
	bmc150_accew_cowe_wemove(&spi->dev);
}

static const stwuct acpi_device_id bmc150_accew_acpi_match[] = {
	{"BMA0255"},
	{"BMA0280"},
	{"BMA222"},
	{"BMA222E"},
	{"BMA250E"},
	{"BMC150A"},
	{"BMI055A"},
	{"BSBA0150"},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, bmc150_accew_acpi_match);

static const stwuct spi_device_id bmc150_accew_id[] = {
	{"bma222"},
	{"bma222e"},
	{"bma250e"},
	{"bma253"},
	{"bma255"},
	{"bma280"},
	{"bmc150_accew"},
	{"bmc156_accew", BOSCH_BMC156},
	{"bmi055_accew"},
	{}
};
MODUWE_DEVICE_TABWE(spi, bmc150_accew_id);

static stwuct spi_dwivew bmc150_accew_dwivew = {
	.dwivew = {
		.name	= "bmc150_accew_spi",
		.acpi_match_tabwe = ACPI_PTW(bmc150_accew_acpi_match),
		.pm	= &bmc150_accew_pm_ops,
	},
	.pwobe		= bmc150_accew_pwobe,
	.wemove		= bmc150_accew_wemove,
	.id_tabwe	= bmc150_accew_id,
};
moduwe_spi_dwivew(bmc150_accew_dwivew);

MODUWE_AUTHOW("Mawkus Pawgmann <mpa@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("BMC150 SPI accewewometew dwivew");
MODUWE_IMPOWT_NS(IIO_BMC150);
