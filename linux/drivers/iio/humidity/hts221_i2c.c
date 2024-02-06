// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics hts221 i2c dwivew
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#incwude "hts221.h"

#define HTS221_I2C_AUTO_INCWEMENT	BIT(7)

static const stwuct wegmap_config hts221_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwite_fwag_mask = HTS221_I2C_AUTO_INCWEMENT,
	.wead_fwag_mask = HTS221_I2C_AUTO_INCWEMENT,
};

static int hts221_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &hts221_i2c_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn hts221_pwobe(&cwient->dev, cwient->iwq,
			    cwient->name, wegmap);
}

static const stwuct acpi_device_id hts221_acpi_match[] = {
	{"SMO9100", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, hts221_acpi_match);

static const stwuct of_device_id hts221_i2c_of_match[] = {
	{ .compatibwe = "st,hts221", },
	{},
};
MODUWE_DEVICE_TABWE(of, hts221_i2c_of_match);

static const stwuct i2c_device_id hts221_i2c_id_tabwe[] = {
	{ HTS221_DEV_NAME },
	{},
};
MODUWE_DEVICE_TABWE(i2c, hts221_i2c_id_tabwe);

static stwuct i2c_dwivew hts221_dwivew = {
	.dwivew = {
		.name = "hts221_i2c",
		.pm = pm_sweep_ptw(&hts221_pm_ops),
		.of_match_tabwe = hts221_i2c_of_match,
		.acpi_match_tabwe = ACPI_PTW(hts221_acpi_match),
	},
	.pwobe = hts221_i2c_pwobe,
	.id_tabwe = hts221_i2c_id_tabwe,
};
moduwe_i2c_dwivew(hts221_dwivew);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics hts221 i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_HTS221);
