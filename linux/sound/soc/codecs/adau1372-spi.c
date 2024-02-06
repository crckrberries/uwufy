// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ADAU1372 codec
 *
 * Copywight 2016 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <sound/soc.h>

#incwude "adau1372.h"

static void adau1372_spi_switch_mode(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	/*
	 * To get the device into SPI mode CWATCH has to be puwwed wow thwee
	 * times.  Do this by issuing thwee dummy weads.
	 */
	spi_w8w8(spi, 0x00);
	spi_w8w8(spi, 0x00);
	spi_w8w8(spi, 0x00);
}

static int adau1372_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap_config config;

	config = adau1372_wegmap_config;
	config.wead_fwag_mask = 0x1;

	wetuwn adau1372_pwobe(&spi->dev,
		devm_wegmap_init_spi(spi, &config), adau1372_spi_switch_mode);
}

static const stwuct spi_device_id adau1372_spi_id[] = {
	{ "adau1372", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adau1372_spi_id);

static stwuct spi_dwivew adau1372_spi_dwivew = {
	.dwivew = {
		.name = "adau1372",
	},
	.pwobe = adau1372_spi_pwobe,
	.id_tabwe = adau1372_spi_id,
};
moduwe_spi_dwivew(adau1372_spi_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1372 CODEC SPI dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW v2");
