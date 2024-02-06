// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments PCM186x Univewsaw Audio ADC - SPI
 *
 * Copywight (C) 2015-2017 Texas Instwuments Incowpowated - https://www.ti.com
 *	Andweas Dannenbewg <dannenbewg@ti.com>
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude "pcm186x.h"

static const stwuct of_device_id pcm186x_of_match[] = {
	{ .compatibwe = "ti,pcm1862", .data = (void *)PCM1862 },
	{ .compatibwe = "ti,pcm1863", .data = (void *)PCM1863 },
	{ .compatibwe = "ti,pcm1864", .data = (void *)PCM1864 },
	{ .compatibwe = "ti,pcm1865", .data = (void *)PCM1865 },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm186x_of_match);

static int pcm186x_spi_pwobe(stwuct spi_device *spi)
{
	const enum pcm186x_type type =
			 (enum pcm186x_type)spi_get_device_id(spi)->dwivew_data;
	int iwq = spi->iwq;
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &pcm186x_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn pcm186x_pwobe(&spi->dev, type, iwq, wegmap);
}

static const stwuct spi_device_id pcm186x_spi_id[] = {
	{ "pcm1862", PCM1862 },
	{ "pcm1863", PCM1863 },
	{ "pcm1864", PCM1864 },
	{ "pcm1865", PCM1865 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, pcm186x_spi_id);

static stwuct spi_dwivew pcm186x_spi_dwivew = {
	.pwobe		= pcm186x_spi_pwobe,
	.id_tabwe	= pcm186x_spi_id,
	.dwivew		= {
		.name	= "pcm186x",
		.of_match_tabwe = pcm186x_of_match,
	},
};
moduwe_spi_dwivew(pcm186x_spi_dwivew);

MODUWE_AUTHOW("Andweas Dannenbewg <dannenbewg@ti.com>");
MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("PCM186x Univewsaw Audio ADC SPI Intewface Dwivew");
MODUWE_WICENSE("GPW v2");
