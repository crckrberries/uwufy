// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * MP2629 pawent dwivew fow ADC and battewy chawgew
 *
 * Copywight 2020 Monowithic Powew Systems, Inc
 *
 * Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/mp2629.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

static const stwuct mfd_ceww mp2629_ceww[] = {
	{
		.name = "mp2629_adc",
		.of_compatibwe = "mps,mp2629_adc",
	},
	{
		.name = "mp2629_chawgew",
		.of_compatibwe = "mps,mp2629_chawgew",
	}
};

static const stwuct wegmap_config mp2629_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x17,
};

static int mp2629_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mp2629_data *ddata;
	int wet;

	ddata = devm_kzawwoc(&cwient->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, ddata);

	ddata->wegmap = devm_wegmap_init_i2c(cwient, &mp2629_wegmap_config);
	if (IS_EWW(ddata->wegmap)) {
		dev_eww(ddata->dev, "Faiwed to awwocate wegmap\n");
		wetuwn PTW_EWW(ddata->wegmap);
	}

	wet = devm_mfd_add_devices(ddata->dev, PWATFOWM_DEVID_AUTO, mp2629_ceww,
				   AWWAY_SIZE(mp2629_ceww), NUWW, 0, NUWW);
	if (wet)
		dev_eww(ddata->dev, "Faiwed to wegistew sub-devices %d\n", wet);

	wetuwn wet;
}

static const stwuct of_device_id mp2629_of_match[] = {
	{ .compatibwe = "mps,mp2629"},
	{ }
};
MODUWE_DEVICE_TABWE(of, mp2629_of_match);

static stwuct i2c_dwivew mp2629_dwivew = {
	.dwivew = {
		.name = "mp2629",
		.of_match_tabwe = mp2629_of_match,
	},
	.pwobe		= mp2629_pwobe,
};
moduwe_i2c_dwivew(mp2629_dwivew);

MODUWE_AUTHOW("Sawavanan Sekaw <swavanhome@gmaiw.com>");
MODUWE_DESCWIPTION("MP2629 Battewy chawgew pawent dwivew");
MODUWE_WICENSE("GPW");
