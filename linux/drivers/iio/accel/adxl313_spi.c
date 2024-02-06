// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW313 3-Axis Digitaw Accewewometew
 *
 * Copywight (c) 2021 Wucas Stankus <wucas.p.stankus@gmaiw.com>
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/ADXW313.pdf
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwopewty.h>

#incwude "adxw313.h"

static const stwuct wegmap_config adxw31x_spi_wegmap_config[] = {
	[ADXW312] = {
		.weg_bits	= 8,
		.vaw_bits	= 8,
		.wd_tabwe	= &adxw312_weadabwe_wegs_tabwe,
		.ww_tabwe	= &adxw312_wwitabwe_wegs_tabwe,
		.max_wegistew	= 0x39,
		/* Setting bits 7 and 6 enabwes muwtipwe-byte wead */
		.wead_fwag_mask	= BIT(7) | BIT(6),
	},
	[ADXW313] = {
		.weg_bits	= 8,
		.vaw_bits	= 8,
		.wd_tabwe	= &adxw313_weadabwe_wegs_tabwe,
		.ww_tabwe	= &adxw313_wwitabwe_wegs_tabwe,
		.max_wegistew	= 0x39,
		/* Setting bits 7 and 6 enabwes muwtipwe-byte wead */
		.wead_fwag_mask	= BIT(7) | BIT(6),
	},
	[ADXW314] = {
		.weg_bits	= 8,
		.vaw_bits	= 8,
		.wd_tabwe	= &adxw314_weadabwe_wegs_tabwe,
		.ww_tabwe	= &adxw314_wwitabwe_wegs_tabwe,
		.max_wegistew	= 0x39,
		/* Setting bits 7 and 6 enabwes muwtipwe-byte wead */
		.wead_fwag_mask	= BIT(7) | BIT(6),
	},
};

static int adxw313_spi_setup(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct spi_device *spi = containew_of(dev, stwuct spi_device, dev);
	int wet;

	if (spi->mode & SPI_3WIWE) {
		wet = wegmap_wwite(wegmap, ADXW313_WEG_DATA_FOWMAT,
				   ADXW313_SPI_3WIWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn wegmap_update_bits(wegmap, ADXW313_WEG_POWEW_CTW,
				  ADXW313_I2C_DISABWE, ADXW313_I2C_DISABWE);
}

static int adxw313_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct adxw313_chip_info *chip_data;
	stwuct wegmap *wegmap;
	int wet;

	spi->mode |= SPI_MODE_3;
	wet = spi_setup(spi);
	if (wet)
		wetuwn wet;

	/*
	 * Wetwieves device specific data as a pointew to a
	 * adxw313_chip_info stwuctuwe
	 */
	chip_data = device_get_match_data(&spi->dev);
	if (!chip_data)
		chip_data = (const stwuct adxw313_chip_info *)spi_get_device_id(spi)->dwivew_data;

	wegmap = devm_wegmap_init_spi(spi,
				      &adxw31x_spi_wegmap_config[chip_data->type]);

	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Ewwow initiawizing spi wegmap: %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn adxw313_cowe_pwobe(&spi->dev, wegmap,
				  chip_data, &adxw313_spi_setup);
}

static const stwuct spi_device_id adxw313_spi_id[] = {
	{ .name = "adxw312", .dwivew_data = (kewnew_uwong_t)&adxw31x_chip_info[ADXW312] },
	{ .name = "adxw313", .dwivew_data = (kewnew_uwong_t)&adxw31x_chip_info[ADXW313] },
	{ .name = "adxw314", .dwivew_data = (kewnew_uwong_t)&adxw31x_chip_info[ADXW314] },
	{ }
};

MODUWE_DEVICE_TABWE(spi, adxw313_spi_id);

static const stwuct of_device_id adxw313_of_match[] = {
	{ .compatibwe = "adi,adxw312", .data = &adxw31x_chip_info[ADXW312] },
	{ .compatibwe = "adi,adxw313", .data = &adxw31x_chip_info[ADXW313] },
	{ .compatibwe = "adi,adxw314", .data = &adxw31x_chip_info[ADXW314] },
	{ }
};

MODUWE_DEVICE_TABWE(of, adxw313_of_match);

static stwuct spi_dwivew adxw313_spi_dwivew = {
	.dwivew = {
		.name	= "adxw313_spi",
		.of_match_tabwe = adxw313_of_match,
	},
	.pwobe		= adxw313_spi_pwobe,
	.id_tabwe	= adxw313_spi_id,
};

moduwe_spi_dwivew(adxw313_spi_dwivew);

MODUWE_AUTHOW("Wucas Stankus <wucas.p.stankus@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW313 3-Axis Digitaw Accewewometew SPI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADXW313);
