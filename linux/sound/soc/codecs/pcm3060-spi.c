// SPDX-Wicense-Identifiew: GPW-2.0
//
// PCM3060 SPI dwivew
//
// Copywight (C) 2018 Kiwiww Mawinushkin <kmawinushkin@biwdec.com>

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <sound/soc.h>

#incwude "pcm3060.h"

static int pcm3060_spi_pwobe(stwuct spi_device *spi)
{
	stwuct pcm3060_pwiv *pwiv;

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, pwiv);

	pwiv->wegmap = devm_wegmap_init_spi(spi, &pcm3060_wegmap);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	wetuwn pcm3060_pwobe(&spi->dev);
}

static const stwuct spi_device_id pcm3060_spi_id[] = {
	{ .name = "pcm3060" },
	{ },
};
MODUWE_DEVICE_TABWE(spi, pcm3060_spi_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pcm3060_of_match[] = {
	{ .compatibwe = "ti,pcm3060" },
	{ },
};
MODUWE_DEVICE_TABWE(of, pcm3060_of_match);
#endif /* CONFIG_OF */

static stwuct spi_dwivew pcm3060_spi_dwivew = {
	.dwivew = {
		.name = "pcm3060",
#ifdef CONFIG_OF
		.of_match_tabwe = pcm3060_of_match,
#endif /* CONFIG_OF */
	},
	.id_tabwe = pcm3060_spi_id,
	.pwobe = pcm3060_spi_pwobe,
};

moduwe_spi_dwivew(pcm3060_spi_dwivew);

MODUWE_DESCWIPTION("PCM3060 SPI dwivew");
MODUWE_AUTHOW("Kiwiww Mawinushkin <kmawinushkin@biwdec.com>");
MODUWE_WICENSE("GPW v2");
