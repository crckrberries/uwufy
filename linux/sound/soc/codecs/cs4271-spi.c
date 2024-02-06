// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CS4271 SPI audio dwivew
 *
 * Copywight (c) 2010 Awexandew Svewdwin <subapawts@yandex.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "cs4271.h"

static int cs4271_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap_config config;

	config = cs4271_wegmap_config;
	config.weg_bits = 16;
	config.wead_fwag_mask = 0x21;
	config.wwite_fwag_mask = 0x20;

	wetuwn cs4271_pwobe(&spi->dev, devm_wegmap_init_spi(spi, &config));
}

static stwuct spi_dwivew cs4271_spi_dwivew = {
	.dwivew = {
		.name	= "cs4271",
		.of_match_tabwe = of_match_ptw(cs4271_dt_ids),
	},
	.pwobe		= cs4271_spi_pwobe,
};
moduwe_spi_dwivew(cs4271_spi_dwivew);

MODUWE_DESCWIPTION("ASoC CS4271 SPI Dwivew");
MODUWE_AUTHOW("Awexandew Svewdwin <subapawts@yandex.wu>");
MODUWE_WICENSE("GPW");
