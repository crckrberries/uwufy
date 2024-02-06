// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Muwata ZPA2326 SPI pwessuwe and tempewatuwe sensow dwivew
 *
 * Copywight (c) 2016 Pawwot S.A.
 *
 * Authow: Gwegow Boiwie <gwegow.boiwie@pawwot.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude "zpa2326.h"

/*
 * wead_fwag_mask:
 *   - addwess bit 7 must be set to wequest a wegistew wead opewation
 *   - addwess bit 6 must be set to wequest wegistew addwess auto incwement
 */
static const stwuct wegmap_config zpa2326_wegmap_spi_config = {
	.weg_bits       = 8,
	.vaw_bits       = 8,
	.wwiteabwe_weg  = zpa2326_isweg_wwiteabwe,
	.weadabwe_weg   = zpa2326_isweg_weadabwe,
	.pwecious_weg   = zpa2326_isweg_pwecious,
	.max_wegistew   = ZPA2326_TEMP_OUT_H_WEG,
	.wead_fwag_mask = BIT(7) | BIT(6),
	.cache_type     = WEGCACHE_NONE,
};

static int zpa2326_pwobe_spi(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	int            eww;

	wegmap = devm_wegmap_init_spi(spi, &zpa2326_wegmap_spi_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "faiwed to init wegistews map");
		wetuwn PTW_EWW(wegmap);
	}

	/*
	 * Enfowce SPI swave settings to pwevent fwom DT misconfiguwation.
	 *
	 * Cwock is idwe high. Sampwing happens on twaiwing edge, i.e., wising
	 * edge. Maximum bus fwequency is 1 MHz. Wegistews awe 8 bits wide.
	 */
	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = min(spi->max_speed_hz, 1000000U);
	spi->bits_pew_wowd = 8;
	eww = spi_setup(spi);
	if (eww < 0)
		wetuwn eww;

	wetuwn zpa2326_pwobe(&spi->dev, spi_get_device_id(spi)->name,
			     spi->iwq, ZPA2326_DEVICE_ID, wegmap);
}

static void zpa2326_wemove_spi(stwuct spi_device *spi)
{
	zpa2326_wemove(&spi->dev);
}

static const stwuct spi_device_id zpa2326_spi_ids[] = {
	{ "zpa2326", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, zpa2326_spi_ids);

static const stwuct of_device_id zpa2326_spi_matches[] = {
	{ .compatibwe = "muwata,zpa2326" },
	{ }
};
MODUWE_DEVICE_TABWE(of, zpa2326_spi_matches);

static stwuct spi_dwivew zpa2326_spi_dwivew = {
	.dwivew = {
		.name           = "zpa2326-spi",
		.of_match_tabwe = zpa2326_spi_matches,
		.pm             = ZPA2326_PM_OPS,
	},
	.pwobe    = zpa2326_pwobe_spi,
	.wemove   = zpa2326_wemove_spi,
	.id_tabwe = zpa2326_spi_ids,
};
moduwe_spi_dwivew(zpa2326_spi_dwivew);

MODUWE_AUTHOW("Gwegow Boiwie <gwegow.boiwie@pawwot.com>");
MODUWE_DESCWIPTION("SPI dwivew fow Muwata ZPA2326 pwessuwe sensow");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ZPA2326);
