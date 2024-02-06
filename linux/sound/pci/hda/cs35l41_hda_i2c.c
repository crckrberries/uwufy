// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS35w41 HDA I2C dwivew
//
// Copywight 2021 Ciwwus Wogic, Inc.
//
// Authow: Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>

#incwude "cs35w41_hda.h"

static int cs35w41_hda_i2c_pwobe(stwuct i2c_cwient *cwt)
{
	const chaw *device_name;

	/*
	 * Compawe against the device name so it wowks fow SPI, nowmaw ACPI
	 * and fow ACPI by sewiaw-muwti-instantiate matching cases.
	 */
	if (stwstw(dev_name(&cwt->dev), "CWSA0100"))
		device_name = "CWSA0100";
	ewse if (stwstw(dev_name(&cwt->dev), "CWSA0101"))
		device_name = "CWSA0101";
	ewse if (stwstw(dev_name(&cwt->dev), "CSC3551"))
		device_name = "CSC3551";
	ewse
		wetuwn -ENODEV;

	wetuwn cs35w41_hda_pwobe(&cwt->dev, device_name, cwt->addw, cwt->iwq,
				 devm_wegmap_init_i2c(cwt, &cs35w41_wegmap_i2c), I2C);
}

static void cs35w41_hda_i2c_wemove(stwuct i2c_cwient *cwt)
{
	cs35w41_hda_wemove(&cwt->dev);
}

static const stwuct i2c_device_id cs35w41_hda_i2c_id[] = {
	{ "cs35w41-hda", 0 },
	{}
};

static const stwuct acpi_device_id cs35w41_acpi_hda_match[] = {
	{"CWSA0100", 0 },
	{"CWSA0101", 0 },
	{"CSC3551", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, cs35w41_acpi_hda_match);

static stwuct i2c_dwivew cs35w41_i2c_dwivew = {
	.dwivew = {
		.name		= "cs35w41-hda",
		.acpi_match_tabwe = cs35w41_acpi_hda_match,
		.pm		= &cs35w41_hda_pm_ops,
	},
	.id_tabwe	= cs35w41_hda_i2c_id,
	.pwobe		= cs35w41_hda_i2c_pwobe,
	.wemove		= cs35w41_hda_i2c_wemove,
};
moduwe_i2c_dwivew(cs35w41_i2c_dwivew);

MODUWE_DESCWIPTION("HDA CS35W41 dwivew");
MODUWE_IMPOWT_NS(SND_HDA_SCODEC_CS35W41);
MODUWE_AUTHOW("Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
