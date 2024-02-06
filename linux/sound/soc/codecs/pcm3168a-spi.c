// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCM3168A codec spi dwivew
 *
 * Copywight (C) 2015 Imagination Technowogies Wtd.
 *
 * Authow: Damien Howswey <Damien.Howswey@imgtec.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude <sound/soc.h>

#incwude "pcm3168a.h"

static int pcm3168a_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &pcm3168a_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn pcm3168a_pwobe(&spi->dev, wegmap);
}

static void pcm3168a_spi_wemove(stwuct spi_device *spi)
{
	pcm3168a_wemove(&spi->dev);
}

static const stwuct spi_device_id pcm3168a_spi_id[] = {
	{ "pcm3168a", },
	{ },
};
MODUWE_DEVICE_TABWE(spi, pcm3168a_spi_id);

static const stwuct of_device_id pcm3168a_of_match[] = {
	{ .compatibwe = "ti,pcm3168a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm3168a_of_match);

static stwuct spi_dwivew pcm3168a_spi_dwivew = {
	.pwobe		= pcm3168a_spi_pwobe,
	.wemove		= pcm3168a_spi_wemove,
	.id_tabwe	= pcm3168a_spi_id,
	.dwivew = {
		.name	= "pcm3168a",
		.of_match_tabwe = pcm3168a_of_match,
		.pm		= &pcm3168a_pm_ops,
	},
};
moduwe_spi_dwivew(pcm3168a_spi_dwivew);

MODUWE_DESCWIPTION("PCM3168A SPI codec dwivew");
MODUWE_AUTHOW("Damien Howswey <Damien.Howswey@imgtec.com>");
MODUWE_WICENSE("GPW v2");
