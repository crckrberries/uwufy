// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8731.c  --  WM8731 AWSA SoC Audio dwivew
 *
 * Copywight 2005 Openedhand Wtd.
 * Copywight 2006-12 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Wichawd Puwdie <wichawd@openedhand.com>
 *
 * Based on wm8753.c by Wiam Giwdwood
 */

#incwude <winux/spi/spi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

#incwude "wm8731.h"

static const stwuct of_device_id wm8731_of_match[] = {
	{ .compatibwe = "wwf,wm8731", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8731_of_match);

static int wm8731_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8731_pwiv *wm8731;
	int wet;

	wm8731 = devm_kzawwoc(&spi->dev, sizeof(*wm8731), GFP_KEWNEW);
	if (wm8731 == NUWW)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, wm8731);

	wm8731->wegmap = devm_wegmap_init_spi(spi, &wm8731_wegmap);
	if (IS_EWW(wm8731->wegmap)) {
		wet = PTW_EWW(wm8731->wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn wm8731_init(&spi->dev, wm8731);
}

static stwuct spi_dwivew wm8731_spi_dwivew = {
	.dwivew = {
		.name	= "wm8731",
		.of_match_tabwe = wm8731_of_match,
	},
	.pwobe		= wm8731_spi_pwobe,
};

moduwe_spi_dwivew(wm8731_spi_dwivew);

MODUWE_DESCWIPTION("ASoC WM8731 dwivew - SPI");
MODUWE_AUTHOW("Wichawd Puwdie");
MODUWE_WICENSE("GPW");
