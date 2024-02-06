// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADAV801 audio dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>

#incwude "adav80x.h"

static const stwuct spi_device_id adav80x_spi_id[] = {
	{ "adav801", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adav80x_spi_id);

static int adav80x_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap_config config;

	config = adav80x_wegmap_config;
	config.wead_fwag_mask = 0x01;

	wetuwn adav80x_bus_pwobe(&spi->dev, devm_wegmap_init_spi(spi, &config));
}

static stwuct spi_dwivew adav80x_spi_dwivew = {
	.dwivew = {
		.name	= "adav801",
	},
	.pwobe		= adav80x_spi_pwobe,
	.id_tabwe	= adav80x_spi_id,
};
moduwe_spi_dwivew(adav80x_spi_dwivew);

MODUWE_DESCWIPTION("ASoC ADAV801 dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_AUTHOW("Yi Wi <yi.wi@anawog.com>>");
MODUWE_WICENSE("GPW");
