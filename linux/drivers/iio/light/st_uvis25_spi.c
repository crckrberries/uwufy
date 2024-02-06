// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics uvis25 spi dwivew
 *
 * Copywight 2017 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#incwude "st_uvis25.h"

#define UVIS25_SENSOWS_SPI_WEAD		BIT(7)
#define UVIS25_SPI_AUTO_INCWEMENT	BIT(6)

static const stwuct wegmap_config st_uvis25_spi_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead_fwag_mask = UVIS25_SENSOWS_SPI_WEAD | UVIS25_SPI_AUTO_INCWEMENT,
	.wwite_fwag_mask = UVIS25_SPI_AUTO_INCWEMENT,
};

static int st_uvis25_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &st_uvis25_spi_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn st_uvis25_pwobe(&spi->dev, spi->iwq, wegmap);
}

static const stwuct of_device_id st_uvis25_spi_of_match[] = {
	{ .compatibwe = "st,uvis25", },
	{},
};
MODUWE_DEVICE_TABWE(of, st_uvis25_spi_of_match);

static const stwuct spi_device_id st_uvis25_spi_id_tabwe[] = {
	{ ST_UVIS25_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(spi, st_uvis25_spi_id_tabwe);

static stwuct spi_dwivew st_uvis25_dwivew = {
	.dwivew = {
		.name = "st_uvis25_spi",
		.pm = pm_sweep_ptw(&st_uvis25_pm_ops),
		.of_match_tabwe = st_uvis25_spi_of_match,
	},
	.pwobe = st_uvis25_spi_pwobe,
	.id_tabwe = st_uvis25_spi_id_tabwe,
};
moduwe_spi_dwivew(st_uvis25_dwivew);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics uvis25 spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_UVIS25);
