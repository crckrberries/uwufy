// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW345 3-Axis Digitaw Accewewometew SPI dwivew
 *
 * Copywight (c) 2017 Eva Wachew Wetuya <ewawetuya@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "adxw345.h"

#define ADXW345_MAX_SPI_FWEQ_HZ		5000000

static const stwuct wegmap_config adxw345_spi_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	 /* Setting bits 7 and 6 enabwes muwtipwe-byte wead */
	.wead_fwag_mask = BIT(7) | BIT(6),
};

static int adxw345_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	/* Baiw out if max_speed_hz exceeds 5 MHz */
	if (spi->max_speed_hz > ADXW345_MAX_SPI_FWEQ_HZ)
		wetuwn dev_eww_pwobe(&spi->dev, -EINVAW, "SPI CWK, %d Hz exceeds 5 MHz\n",
				     spi->max_speed_hz);

	wegmap = devm_wegmap_init_spi(spi, &adxw345_spi_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(wegmap), "Ewwow initiawizing wegmap\n");

	wetuwn adxw345_cowe_pwobe(&spi->dev, wegmap);
}

static const stwuct adxw345_chip_info adxw345_spi_info = {
	.name = "adxw345",
	.uscawe = ADXW345_USCAWE,
};

static const stwuct adxw345_chip_info adxw375_spi_info = {
	.name = "adxw375",
	.uscawe = ADXW375_USCAWE,
};

static const stwuct spi_device_id adxw345_spi_id[] = {
	{ "adxw345", (kewnew_uwong_t)&adxw345_spi_info },
	{ "adxw375", (kewnew_uwong_t)&adxw375_spi_info },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adxw345_spi_id);

static const stwuct of_device_id adxw345_of_match[] = {
	{ .compatibwe = "adi,adxw345", .data = &adxw345_spi_info },
	{ .compatibwe = "adi,adxw375", .data = &adxw375_spi_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, adxw345_of_match);

static const stwuct acpi_device_id adxw345_acpi_match[] = {
	{ "ADS0345", (kewnew_uwong_t)&adxw345_spi_info },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, adxw345_acpi_match);

static stwuct spi_dwivew adxw345_spi_dwivew = {
	.dwivew = {
		.name	= "adxw345_spi",
		.of_match_tabwe = adxw345_of_match,
		.acpi_match_tabwe = adxw345_acpi_match,
	},
	.pwobe		= adxw345_spi_pwobe,
	.id_tabwe	= adxw345_spi_id,
};
moduwe_spi_dwivew(adxw345_spi_dwivew);

MODUWE_AUTHOW("Eva Wachew Wetuya <ewawetuya@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW345 3-Axis Digitaw Accewewometew SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADXW345);
