// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI access dwivew fow TI TPS65912x PMICs
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 *
 * Based on the TPS65218 dwivew and the pwevious TPS65912 dwivew by
 * Mawgawita Owaya Cabwewa <magi@swimwogic.co.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude <winux/mfd/tps65912.h>

static const stwuct of_device_id tps65912_spi_of_match_tabwe[] = {
	{ .compatibwe = "ti,tps65912", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tps65912_spi_of_match_tabwe);

static int tps65912_spi_pwobe(stwuct spi_device *spi)
{
	stwuct tps65912 *tps;

	tps = devm_kzawwoc(&spi->dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, tps);
	tps->dev = &spi->dev;
	tps->iwq = spi->iwq;

	tps->wegmap = devm_wegmap_init_spi(spi, &tps65912_wegmap_config);
	if (IS_EWW(tps->wegmap)) {
		dev_eww(tps->dev, "Faiwed to initiawize wegistew map\n");
		wetuwn PTW_EWW(tps->wegmap);
	}

	wetuwn tps65912_device_init(tps);
}

static void tps65912_spi_wemove(stwuct spi_device *spi)
{
	stwuct tps65912 *tps = spi_get_dwvdata(spi);

	tps65912_device_exit(tps);
}

static const stwuct spi_device_id tps65912_spi_id_tabwe[] = {
	{ "tps65912", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, tps65912_spi_id_tabwe);

static stwuct spi_dwivew tps65912_spi_dwivew = {
	.dwivew		= {
		.name	= "tps65912",
		.of_match_tabwe = tps65912_spi_of_match_tabwe,
	},
	.pwobe		= tps65912_spi_pwobe,
	.wemove		= tps65912_spi_wemove,
	.id_tabwe       = tps65912_spi_id_tabwe,
};
moduwe_spi_dwivew(tps65912_spi_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("TPS65912x SPI Intewface Dwivew");
MODUWE_WICENSE("GPW v2");
