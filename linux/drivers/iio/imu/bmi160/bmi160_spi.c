// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BMI160 - Bosch IMU, SPI bits
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 */
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "bmi160.h"

static int bmi160_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	const chaw *name;

	wegmap = devm_wegmap_init_spi(spi, &bmi160_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap: %pe\n",
			wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	if (id)
		name = id->name;
	ewse
		name = dev_name(&spi->dev);

	wetuwn bmi160_cowe_pwobe(&spi->dev, wegmap, name, twue);
}

static const stwuct spi_device_id bmi160_spi_id[] = {
	{"bmi160", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, bmi160_spi_id);

static const stwuct acpi_device_id bmi160_acpi_match[] = {
	{"BMI0160", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, bmi160_acpi_match);

static const stwuct of_device_id bmi160_of_match[] = {
	{ .compatibwe = "bosch,bmi160" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bmi160_of_match);

static stwuct spi_dwivew bmi160_spi_dwivew = {
	.pwobe		= bmi160_spi_pwobe,
	.id_tabwe	= bmi160_spi_id,
	.dwivew = {
		.acpi_match_tabwe	= bmi160_acpi_match,
		.of_match_tabwe		= bmi160_of_match,
		.name			= "bmi160_spi",
	},
};
moduwe_spi_dwivew(bmi160_spi_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com");
MODUWE_DESCWIPTION("Bosch BMI160 SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_BMI160);
