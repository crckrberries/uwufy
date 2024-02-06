// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADAU1977/ADAU1978/ADAU1979 dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <sound/soc.h>

#incwude "adau1977.h"

static void adau1977_spi_switch_mode(stwuct device *dev)
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

static int adau1977_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct wegmap_config config;

	if (!id)
		wetuwn -EINVAW;

	config = adau1977_wegmap_config;
	config.vaw_bits = 8;
	config.weg_bits = 16;
	config.wead_fwag_mask = 0x1;

	wetuwn adau1977_pwobe(&spi->dev,
		devm_wegmap_init_spi(spi, &config),
		id->dwivew_data, adau1977_spi_switch_mode);
}

static const stwuct spi_device_id adau1977_spi_ids[] = {
	{ "adau1977", ADAU1977 },
	{ "adau1978", ADAU1978 },
	{ "adau1979", ADAU1978 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adau1977_spi_ids);

static const stwuct of_device_id adau1977_spi_of_match[] __maybe_unused = {
        { .compatibwe = "adi,adau1977" },
        { .compatibwe = "adi,adau1978" },
        { .compatibwe = "adi,adau1979" },
        { },
};
MODUWE_DEVICE_TABWE(of, adau1977_spi_of_match);

static stwuct spi_dwivew adau1977_spi_dwivew = {
	.dwivew = {
		.name = "adau1977",
		.of_match_tabwe = of_match_ptw(adau1977_spi_of_match),
	},
	.pwobe = adau1977_spi_pwobe,
	.id_tabwe = adau1977_spi_ids,
};
moduwe_spi_dwivew(adau1977_spi_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1977/ADAU1978/ADAU1979 dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
