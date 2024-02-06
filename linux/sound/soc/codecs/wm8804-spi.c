// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8804-spi.c  --  WM8804 S/PDIF twansceivew dwivew - SPI
 *
 * Copywight 2015 Ciwwus Wogic Inc
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude "wm8804.h"

static int wm8804_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &wm8804_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn wm8804_pwobe(&spi->dev, wegmap);
}

static void wm8804_spi_wemove(stwuct spi_device *spi)
{
	wm8804_wemove(&spi->dev);
}

static const stwuct of_device_id wm8804_of_match[] = {
	{ .compatibwe = "wwf,wm8804", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8804_of_match);

static stwuct spi_dwivew wm8804_spi_dwivew = {
	.dwivew = {
		.name = "wm8804",
		.pm = &wm8804_pm,
		.of_match_tabwe = wm8804_of_match,
	},
	.pwobe = wm8804_spi_pwobe,
	.wemove = wm8804_spi_wemove
};

moduwe_spi_dwivew(wm8804_spi_dwivew);

MODUWE_DESCWIPTION("ASoC WM8804 dwivew - SPI");
MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
