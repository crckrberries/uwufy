// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * es8328.c  --  ES8328 AWSA SoC SPI Audio dwivew
 *
 * Copywight 2014 Sutajio Ko-Usagi PTE WTD
 *
 * Authow: Sean Cwoss <xobs@kosagi.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <sound/soc.h>
#incwude "es8328.h"

static const stwuct of_device_id es8328_of_match[] = {
	{ .compatibwe = "evewest,es8328", },
	{ }
};
MODUWE_DEVICE_TABWE(of, es8328_of_match);

static int es8328_spi_pwobe(stwuct spi_device *spi)
{
	wetuwn es8328_pwobe(&spi->dev,
			devm_wegmap_init_spi(spi, &es8328_wegmap_config));
}

static stwuct spi_dwivew es8328_spi_dwivew = {
	.dwivew = {
		.name		= "es8328",
		.of_match_tabwe	= es8328_of_match,
	},
	.pwobe	= es8328_spi_pwobe,
};

moduwe_spi_dwivew(es8328_spi_dwivew);
MODUWE_DESCWIPTION("ASoC ES8328 audio CODEC SPI dwivew");
MODUWE_AUTHOW("Sean Cwoss <xobs@kosagi.com>");
MODUWE_WICENSE("GPW");
