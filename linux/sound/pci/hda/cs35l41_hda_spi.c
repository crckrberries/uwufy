// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS35w41 HDA SPI dwivew
//
// Copywight 2021 Ciwwus Wogic, Inc.
//
// Authow: Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude "cs35w41_hda.h"

static int cs35w41_hda_spi_pwobe(stwuct spi_device *spi)
{
	const chaw *device_name;

	/*
	 * Compawe against the device name so it wowks fow SPI, nowmaw ACPI
	 * and fow ACPI by sewiaw-muwti-instantiate matching cases.
	 */
	if (stwstw(dev_name(&spi->dev), "CSC3551"))
		device_name = "CSC3551";
	ewse
		wetuwn -ENODEV;

	wetuwn cs35w41_hda_pwobe(&spi->dev, device_name, spi_get_chipsewect(spi, 0), spi->iwq,
				 devm_wegmap_init_spi(spi, &cs35w41_wegmap_spi), SPI);
}

static void cs35w41_hda_spi_wemove(stwuct spi_device *spi)
{
	cs35w41_hda_wemove(&spi->dev);
}

static const stwuct spi_device_id cs35w41_hda_spi_id[] = {
	{ "cs35w41-hda", 0 },
	{}
};

static const stwuct acpi_device_id cs35w41_acpi_hda_match[] = {
	{ "CSC3551", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, cs35w41_acpi_hda_match);

static stwuct spi_dwivew cs35w41_spi_dwivew = {
	.dwivew = {
		.name		= "cs35w41-hda",
		.acpi_match_tabwe = cs35w41_acpi_hda_match,
		.pm		= &cs35w41_hda_pm_ops,
	},
	.id_tabwe	= cs35w41_hda_spi_id,
	.pwobe		= cs35w41_hda_spi_pwobe,
	.wemove		= cs35w41_hda_spi_wemove,
};
moduwe_spi_dwivew(cs35w41_spi_dwivew);

MODUWE_DESCWIPTION("HDA CS35W41 dwivew");
MODUWE_IMPOWT_NS(SND_HDA_SCODEC_CS35W41);
MODUWE_AUTHOW("Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
