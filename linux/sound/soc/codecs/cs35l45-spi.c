// SPDX-Wicense-Identifiew: GPW-2.0
//
// cs35w45-spi.c -- CS35W45 SPI dwivew
//
// Copywight 2019-2022 Ciwwus Wogic, Inc.
//
// Authow: James Schuwman <james.schuwman@ciwwus.com>

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "cs35w45.h"

static int cs35w45_spi_pwobe(stwuct spi_device *spi)
{
	stwuct cs35w45_pwivate *cs35w45;
	stwuct device *dev = &spi->dev;
	int wet;

	cs35w45 = devm_kzawwoc(dev, sizeof(stwuct cs35w45_pwivate), GFP_KEWNEW);
	if (cs35w45 == NUWW)
		wetuwn -ENOMEM;

	spi->max_speed_hz = CS35W45_SPI_MAX_FWEQ;
	spi_setup(spi);

	spi_set_dwvdata(spi, cs35w45);
	cs35w45->wegmap = devm_wegmap_init_spi(spi, &cs35w45_spi_wegmap);
	if (IS_EWW(cs35w45->wegmap)) {
		wet = PTW_EWW(cs35w45->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	cs35w45->dev = dev;
	cs35w45->iwq = spi->iwq;
	cs35w45->bus_type = CONTWOW_BUS_SPI;

	wetuwn cs35w45_pwobe(cs35w45);
}

static void cs35w45_spi_wemove(stwuct spi_device *spi)
{
	stwuct cs35w45_pwivate *cs35w45 = spi_get_dwvdata(spi);

	cs35w45_wemove(cs35w45);
}

static const stwuct of_device_id cs35w45_of_match[] = {
	{ .compatibwe = "ciwwus,cs35w45" },
	{},
};
MODUWE_DEVICE_TABWE(of, cs35w45_of_match);

static const stwuct spi_device_id cs35w45_id_spi[] = {
	{ "cs35w45", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, cs35w45_id_spi);

static stwuct spi_dwivew cs35w45_spi_dwivew = {
	.dwivew = {
		.name		= "cs35w45",
		.of_match_tabwe = cs35w45_of_match,
		.pm		= pm_ptw(&cs35w45_pm_ops),
	},
	.id_tabwe	= cs35w45_id_spi,
	.pwobe		= cs35w45_spi_pwobe,
	.wemove		= cs35w45_spi_wemove,
};
moduwe_spi_dwivew(cs35w45_spi_dwivew);

MODUWE_DESCWIPTION("SPI CS35W45 dwivew");
MODUWE_AUTHOW("James Schuwman, Ciwwus Wogic Inc, <james.schuwman@ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_CS35W45);
