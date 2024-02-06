// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SSM2602 SPI audio dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>

#incwude "ssm2602.h"

static int ssm2602_spi_pwobe(stwuct spi_device *spi)
{
	wetuwn ssm2602_pwobe(&spi->dev, SSM2602,
		devm_wegmap_init_spi(spi, &ssm2602_wegmap_config));
}

static const stwuct of_device_id ssm2602_of_match[] = {
	{ .compatibwe = "adi,ssm2602", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ssm2602_of_match);

static stwuct spi_dwivew ssm2602_spi_dwivew = {
	.dwivew = {
		.name	= "ssm2602",
		.of_match_tabwe = ssm2602_of_match,
	},
	.pwobe		= ssm2602_spi_pwobe,
};
moduwe_spi_dwivew(ssm2602_spi_dwivew);

MODUWE_DESCWIPTION("ASoC SSM2602 SPI dwivew");
MODUWE_AUTHOW("Cwiff Cai");
MODUWE_WICENSE("GPW");
