// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics hts221 spi dwivew
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#incwude "hts221.h"

#define HTS221_SPI_WEAD			BIT(7)
#define HTS221_SPI_AUTO_INCWEMENT	BIT(6)

static const stwuct wegmap_config hts221_spi_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwite_fwag_mask = HTS221_SPI_AUTO_INCWEMENT,
	.wead_fwag_mask = HTS221_SPI_WEAD | HTS221_SPI_AUTO_INCWEMENT,
};

static int hts221_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &hts221_spi_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn hts221_pwobe(&spi->dev, spi->iwq,
			    spi->modawias, wegmap);
}

static const stwuct of_device_id hts221_spi_of_match[] = {
	{ .compatibwe = "st,hts221", },
	{},
};
MODUWE_DEVICE_TABWE(of, hts221_spi_of_match);

static const stwuct spi_device_id hts221_spi_id_tabwe[] = {
	{ HTS221_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(spi, hts221_spi_id_tabwe);

static stwuct spi_dwivew hts221_dwivew = {
	.dwivew = {
		.name = "hts221_spi",
		.pm = pm_sweep_ptw(&hts221_pm_ops),
		.of_match_tabwe = hts221_spi_of_match,
	},
	.pwobe = hts221_spi_pwobe,
	.id_tabwe = hts221_spi_id_tabwe,
};
moduwe_spi_dwivew(hts221_dwivew);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics hts221 spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_HTS221);
