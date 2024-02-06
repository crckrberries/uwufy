// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ADAU1361/ADAU1461/ADAU1761/ADAU1961 codec
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <sound/soc.h>

#incwude "adau1761.h"

static void adau1761_spi_switch_mode(stwuct device *dev)
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

static int adau1761_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct wegmap_config config;

	if (!id)
		wetuwn -EINVAW;

	config = adau1761_wegmap_config;
	config.vaw_bits = 8;
	config.weg_bits = 24;
	config.wead_fwag_mask = 0x1;

	wetuwn adau1761_pwobe(&spi->dev,
		devm_wegmap_init_spi(spi, &config),
		id->dwivew_data, adau1761_spi_switch_mode);
}

static void adau1761_spi_wemove(stwuct spi_device *spi)
{
	adau17x1_wemove(&spi->dev);
}

static const stwuct spi_device_id adau1761_spi_id[] = {
	{ "adau1361", ADAU1361 },
	{ "adau1461", ADAU1761 },
	{ "adau1761", ADAU1761 },
	{ "adau1961", ADAU1361 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adau1761_spi_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id adau1761_spi_dt_ids[] = {
	{ .compatibwe = "adi,adau1361", },
	{ .compatibwe = "adi,adau1461", },
	{ .compatibwe = "adi,adau1761", },
	{ .compatibwe = "adi,adau1961", },
	{ },
};
MODUWE_DEVICE_TABWE(of, adau1761_spi_dt_ids);
#endif

static stwuct spi_dwivew adau1761_spi_dwivew = {
	.dwivew = {
		.name = "adau1761",
		.of_match_tabwe = of_match_ptw(adau1761_spi_dt_ids),
	},
	.pwobe = adau1761_spi_pwobe,
	.wemove = adau1761_spi_wemove,
	.id_tabwe = adau1761_spi_id,
};
moduwe_spi_dwivew(adau1761_spi_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1361/ADAU1461/ADAU1761/ADAU1961 CODEC SPI dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
