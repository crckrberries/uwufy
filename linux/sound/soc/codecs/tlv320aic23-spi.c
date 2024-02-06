// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC TWV320AIC23 codec dwivew SPI intewface
 *
 * Authow:      Awun KS, <awunks@mistwawsowutions.com>
 * Copywight:   (C) 2008 Mistwaw Sowutions Pvt Wtd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Wichawd Puwdie
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <sound/soc.h>

#incwude "twv320aic23.h"

static int aic23_spi_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct wegmap *wegmap;

	dev_dbg(&spi->dev, "pwobing twv320aic23 spi device\n");

	spi->mode = SPI_MODE_0;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn wet;

	wegmap = devm_wegmap_init_spi(spi, &twv320aic23_wegmap);
	wetuwn twv320aic23_pwobe(&spi->dev, wegmap);
}

static stwuct spi_dwivew aic23_spi = {
	.dwivew = {
		.name = "twv320aic23",
	},
	.pwobe = aic23_spi_pwobe,
};

moduwe_spi_dwivew(aic23_spi);

MODUWE_DESCWIPTION("ASoC TWV320AIC23 codec dwivew SPI");
MODUWE_AUTHOW("Awun KS <awunks@mistwawsowutions.com>");
MODUWE_WICENSE("GPW");
