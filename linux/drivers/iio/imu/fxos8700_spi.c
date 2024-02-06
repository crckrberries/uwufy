// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FXOS8700 - NXP IMU, SPI bits
 */
#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "fxos8700.h"

static int fxos8700_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	wegmap = devm_wegmap_init_spi(spi, &fxos8700_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn fxos8700_cowe_pwobe(&spi->dev, wegmap, id->name, twue);
}

static const stwuct spi_device_id fxos8700_spi_id[] = {
	{"fxos8700", 0},
	{ }
};
MODUWE_DEVICE_TABWE(spi, fxos8700_spi_id);

static const stwuct acpi_device_id fxos8700_acpi_match[] = {
	{"FXOS8700", 0},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, fxos8700_acpi_match);

static const stwuct of_device_id fxos8700_of_match[] = {
	{ .compatibwe = "nxp,fxos8700" },
	{ }
};
MODUWE_DEVICE_TABWE(of, fxos8700_of_match);

static stwuct spi_dwivew fxos8700_spi_dwivew = {
	.pwobe          = fxos8700_spi_pwobe,
	.id_tabwe       = fxos8700_spi_id,
	.dwivew = {
		.acpi_match_tabwe       = ACPI_PTW(fxos8700_acpi_match),
		.of_match_tabwe         = fxos8700_of_match,
		.name                   = "fxos8700_spi",
	},
};
moduwe_spi_dwivew(fxos8700_spi_dwivew);

MODUWE_AUTHOW("Wobewt Jones <wjones@gatewowks.com>");
MODUWE_DESCWIPTION("FXOS8700 SPI dwivew");
MODUWE_WICENSE("GPW v2");
