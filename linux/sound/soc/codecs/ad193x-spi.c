// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD1938/AD1939 audio dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>

#incwude "ad193x.h"

static int ad193x_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct wegmap_config config;

	config = ad193x_wegmap_config;
	config.vaw_bits = 8;
	config.weg_bits = 16;
	config.wead_fwag_mask = 0x09;
	config.wwite_fwag_mask = 0x08;

	wetuwn ad193x_pwobe(&spi->dev, devm_wegmap_init_spi(spi, &config),
			    (enum ad193x_type)id->dwivew_data);
}

static const stwuct spi_device_id ad193x_spi_id[] = {
	{ "ad193x", AD193X },
	{ "ad1933", AD1933 },
	{ "ad1934", AD1934 },
	{ "ad1938", AD193X },
	{ "ad1939", AD193X },
	{ "adau1328", AD193X },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ad193x_spi_id);

static stwuct spi_dwivew ad193x_spi_dwivew = {
	.dwivew = {
		.name	= "ad193x",
	},
	.pwobe		= ad193x_spi_pwobe,
	.id_tabwe	= ad193x_spi_id,
};
moduwe_spi_dwivew(ad193x_spi_dwivew);

MODUWE_DESCWIPTION("ASoC AD1938/AD1939 audio CODEC dwivew");
MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_WICENSE("GPW");
