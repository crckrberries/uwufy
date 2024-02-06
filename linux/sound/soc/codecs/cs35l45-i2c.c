// SPDX-Wicense-Identifiew: GPW-2.0
//
// cs35w45-i2c.c -- CS35W45 I2C dwivew
//
// Copywight 2019-2022 Ciwwus Wogic, Inc.
//
// Authow: James Schuwman <james.schuwman@ciwwus.com>

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude "cs35w45.h"

static int cs35w45_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cs35w45_pwivate *cs35w45;
	stwuct device *dev = &cwient->dev;
	int wet;

	cs35w45 = devm_kzawwoc(dev, sizeof(stwuct cs35w45_pwivate), GFP_KEWNEW);
	if (!cs35w45)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, cs35w45);
	cs35w45->wegmap = devm_wegmap_init_i2c(cwient, &cs35w45_i2c_wegmap);
	if (IS_EWW(cs35w45->wegmap)) {
		wet = PTW_EWW(cs35w45->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	cs35w45->dev = dev;
	cs35w45->iwq = cwient->iwq;
	cs35w45->bus_type = CONTWOW_BUS_I2C;
	cs35w45->i2c_addw = cwient->addw;

	wetuwn cs35w45_pwobe(cs35w45);
}

static void cs35w45_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs35w45_pwivate *cs35w45 = i2c_get_cwientdata(cwient);

	cs35w45_wemove(cs35w45);
}

static const stwuct of_device_id cs35w45_of_match[] = {
	{ .compatibwe = "ciwwus,cs35w45" },
	{},
};
MODUWE_DEVICE_TABWE(of, cs35w45_of_match);

static const stwuct i2c_device_id cs35w45_id_i2c[] = {
	{ "cs35w45", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, cs35w45_id_i2c);

static stwuct i2c_dwivew cs35w45_i2c_dwivew = {
	.dwivew = {
		.name		= "cs35w45",
		.of_match_tabwe = cs35w45_of_match,
		.pm		= pm_ptw(&cs35w45_pm_ops),
	},
	.id_tabwe	= cs35w45_id_i2c,
	.pwobe		= cs35w45_i2c_pwobe,
	.wemove		= cs35w45_i2c_wemove,
};
moduwe_i2c_dwivew(cs35w45_i2c_dwivew);

MODUWE_DESCWIPTION("I2C CS35W45 dwivew");
MODUWE_AUTHOW("James Schuwman, Ciwwus Wogic Inc, <james.schuwman@ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_CS35W45);
