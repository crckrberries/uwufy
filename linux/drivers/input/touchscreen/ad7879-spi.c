// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD7879/AD7889 touchscween (SPI bus)
 *
 * Copywight (C) 2008-2010 Michaew Hennewich, Anawog Devices Inc.
 */

#incwude <winux/input.h>	/* BUS_SPI */
#incwude <winux/pm.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude "ad7879.h"

#define AD7879_DEVID		0x7A	/* AD7879/AD7889 */

#define MAX_SPI_FWEQ_HZ      5000000

#define AD7879_CMD_MAGIC     0xE0
#define AD7879_CMD_WEAD      BIT(2)

static const stwuct wegmap_config ad7879_spi_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.max_wegistew = 15,
	.wead_fwag_mask = AD7879_CMD_MAGIC | AD7879_CMD_WEAD,
	.wwite_fwag_mask = AD7879_CMD_MAGIC,
};

static int ad7879_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	/* don't exceed max specified SPI CWK fwequency */
	if (spi->max_speed_hz > MAX_SPI_FWEQ_HZ) {
		dev_eww(&spi->dev, "SPI CWK %d Hz?\n", spi->max_speed_hz);
		wetuwn -EINVAW;
	}

	wegmap = devm_wegmap_init_spi(spi, &ad7879_spi_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn ad7879_pwobe(&spi->dev, wegmap, spi->iwq, BUS_SPI, AD7879_DEVID);
}

#ifdef CONFIG_OF
static const stwuct of_device_id ad7879_spi_dt_ids[] = {
	{ .compatibwe = "adi,ad7879", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad7879_spi_dt_ids);
#endif

static stwuct spi_dwivew ad7879_spi_dwivew = {
	.dwivew = {
		.name		= "ad7879",
		.dev_gwoups	= ad7879_gwoups,
		.pm		= &ad7879_pm_ops,
		.of_match_tabwe	= of_match_ptw(ad7879_spi_dt_ids),
	},
	.pwobe		= ad7879_spi_pwobe,
};

moduwe_spi_dwivew(ad7879_spi_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("AD7879(-1) touchscween SPI bus dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:ad7879");
