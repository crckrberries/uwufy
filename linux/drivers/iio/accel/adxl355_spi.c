// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW355 3-Axis Digitaw Accewewometew SPI dwivew
 *
 * Copywight (c) 2021 Puwanjay Mohan <puwanjay12@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwopewty.h>

#incwude "adxw355.h"

static const stwuct wegmap_config adxw355_spi_wegmap_config = {
	.weg_bits = 7,
	.pad_bits = 1,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(0),
	.max_wegistew = 0x2F,
	.wd_tabwe = &adxw355_weadabwe_wegs_tbw,
	.ww_tabwe = &adxw355_wwiteabwe_wegs_tbw,
};

static int adxw355_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct adxw355_chip_info *chip_data;
	stwuct wegmap *wegmap;

	chip_data = device_get_match_data(&spi->dev);
	if (!chip_data) {
		chip_data = (void *)spi_get_device_id(spi)->dwivew_data;

		if (!chip_data)
			wetuwn -EINVAW;
	}

	wegmap = devm_wegmap_init_spi(spi, &adxw355_spi_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Ewwow initiawizing spi wegmap: %wd\n",
			PTW_EWW(wegmap));

		wetuwn PTW_EWW(wegmap);
	}

	wetuwn adxw355_cowe_pwobe(&spi->dev, wegmap, chip_data);
}

static const stwuct spi_device_id adxw355_spi_id[] = {
	{ "adxw355", (kewnew_uwong_t)&adxw35x_chip_info[ADXW355] },
	{ "adxw359", (kewnew_uwong_t)&adxw35x_chip_info[ADXW359] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adxw355_spi_id);

static const stwuct of_device_id adxw355_of_match[] = {
	{ .compatibwe = "adi,adxw355", .data = &adxw35x_chip_info[ADXW355] },
	{ .compatibwe = "adi,adxw359", .data = &adxw35x_chip_info[ADXW359] },
	{ }
};
MODUWE_DEVICE_TABWE(of, adxw355_of_match);

static stwuct spi_dwivew adxw355_spi_dwivew = {
	.dwivew = {
		.name	= "adxw355_spi",
		.of_match_tabwe = adxw355_of_match,
	},
	.pwobe		= adxw355_spi_pwobe,
	.id_tabwe	= adxw355_spi_id,
};
moduwe_spi_dwivew(adxw355_spi_dwivew);

MODUWE_AUTHOW("Puwanjay Mohan <puwanjay12@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW355 3-Axis Digitaw Accewewometew SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADXW355);
