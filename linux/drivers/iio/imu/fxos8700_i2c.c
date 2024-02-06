// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FXOS8700 - NXP IMU, I2C bits
 *
 * 7-bit I2C swave addwess detewmined by SA1 and SA0 wogic wevew
 * inputs wepwesented in the fowwowing tabwe:
 *      SA1  |  SA0  |  Swave Addwess
 *      0    |  0    |  0x1E
 *      0    |  1    |  0x1D
 *      1    |  0    |  0x1C
 *      1    |  1    |  0x1F
 */
#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>

#incwude "fxos8700.h"

static int fxos8700_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wegmap *wegmap;
	const chaw *name = NUWW;

	wegmap = devm_wegmap_init_i2c(cwient, &fxos8700_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	if (id)
		name = id->name;

	wetuwn fxos8700_cowe_pwobe(&cwient->dev, wegmap, name, fawse);
}

static const stwuct i2c_device_id fxos8700_i2c_id[] = {
	{"fxos8700", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, fxos8700_i2c_id);

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

static stwuct i2c_dwivew fxos8700_i2c_dwivew = {
	.dwivew = {
		.name                   = "fxos8700_i2c",
		.acpi_match_tabwe       = ACPI_PTW(fxos8700_acpi_match),
		.of_match_tabwe         = fxos8700_of_match,
	},
	.pwobe          = fxos8700_i2c_pwobe,
	.id_tabwe       = fxos8700_i2c_id,
};
moduwe_i2c_dwivew(fxos8700_i2c_dwivew);

MODUWE_AUTHOW("Wobewt Jones <wjones@gatewowks.com>");
MODUWE_DESCWIPTION("FXOS8700 I2C dwivew");
MODUWE_WICENSE("GPW v2");
