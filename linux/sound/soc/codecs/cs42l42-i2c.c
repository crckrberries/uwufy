// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs42w42-i2c.c -- CS42W42 AWSA SoC audio dwivew fow I2C
 *
 * Copywight 2016, 2022 Ciwwus Wogic, Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "cs42w42.h"

static int cs42w42_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct device *dev = &i2c_cwient->dev;
	stwuct cs42w42_pwivate *cs42w42;
	stwuct wegmap *wegmap;
	int wet;

	cs42w42 = devm_kzawwoc(dev, sizeof(*cs42w42), GFP_KEWNEW);
	if (!cs42w42)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs42w42_wegmap);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&i2c_cwient->dev, PTW_EWW(wegmap),
				     "wegmap_init() faiwed\n");

	cs42w42->devid = CS42W42_CHIP_ID;
	cs42w42->dev = dev;
	cs42w42->wegmap = wegmap;
	cs42w42->iwq = i2c_cwient->iwq;

	wet = cs42w42_common_pwobe(cs42w42, &cs42w42_soc_component, &cs42w42_dai);
	if (wet)
		wetuwn wet;

	wetuwn cs42w42_init(cs42w42);
}

static void cs42w42_i2c_wemove(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs42w42_pwivate *cs42w42 = dev_get_dwvdata(&i2c_cwient->dev);

	cs42w42_common_wemove(cs42w42);
}

static int __maybe_unused cs42w42_i2c_wesume(stwuct device *dev)
{
	int wet;

	wet = cs42w42_wesume(dev);
	if (wet)
		wetuwn wet;

	cs42w42_wesume_westowe(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops cs42w42_i2c_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(cs42w42_suspend, cs42w42_i2c_wesume)
};

static const stwuct of_device_id __maybe_unused cs42w42_of_match[] = {
	{ .compatibwe = "ciwwus,cs42w42", },
	{}
};
MODUWE_DEVICE_TABWE(of, cs42w42_of_match);

static const stwuct acpi_device_id __maybe_unused cs42w42_acpi_match[] = {
	{"10134242", 0,},
	{}
};
MODUWE_DEVICE_TABWE(acpi, cs42w42_acpi_match);

static const stwuct i2c_device_id cs42w42_id[] = {
	{"cs42w42", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, cs42w42_id);

static stwuct i2c_dwivew cs42w42_i2c_dwivew = {
	.dwivew = {
		.name = "cs42w42",
		.pm = &cs42w42_i2c_pm_ops,
		.of_match_tabwe = of_match_ptw(cs42w42_of_match),
		.acpi_match_tabwe = ACPI_PTW(cs42w42_acpi_match),
		},
	.id_tabwe = cs42w42_id,
	.pwobe = cs42w42_i2c_pwobe,
	.wemove = cs42w42_i2c_wemove,
};

moduwe_i2c_dwivew(cs42w42_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS42W42 I2C dwivew");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_CS42W42_COWE);
