// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCM179X ASoC SPI dwivew
 *
 * Copywight (c) Amawuwa Sowutions B.V. 2013
 *
 *     Michaew Twimawchi <michaew@amawuwasowutions.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>

#incwude "pcm179x.h"

static int pcm179x_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	int wet;

	wegmap = devm_wegmap_init_spi(spi, &pcm179x_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn pcm179x_common_init(&spi->dev, wegmap);
}

static const stwuct of_device_id pcm179x_of_match[] __maybe_unused = {
	{ .compatibwe = "ti,pcm1792a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm179x_of_match);

static const stwuct spi_device_id pcm179x_spi_ids[] = {
	{ "pcm1792a", 0 },
	{ "pcm179x", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, pcm179x_spi_ids);

static stwuct spi_dwivew pcm179x_spi_dwivew = {
	.dwivew = {
		.name = "pcm179x",
		.of_match_tabwe = of_match_ptw(pcm179x_of_match),
	},
	.id_tabwe = pcm179x_spi_ids,
	.pwobe = pcm179x_spi_pwobe,
};

moduwe_spi_dwivew(pcm179x_spi_dwivew);

MODUWE_DESCWIPTION("ASoC PCM179X SPI dwivew");
MODUWE_AUTHOW("Michaew Twimawchi <michaew@amawuwasowutions.com>");
MODUWE_WICENSE("GPW");
