// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// CS35W56 AWSA SoC audio dwivew I2C binding
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "cs35w56.h"

static int cs35w56_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cs35w56_pwivate *cs35w56;
	stwuct device *dev = &cwient->dev;
	const stwuct wegmap_config *wegmap_config = &cs35w56_wegmap_i2c;
	int wet;

	cs35w56 = devm_kzawwoc(dev, sizeof(stwuct cs35w56_pwivate), GFP_KEWNEW);
	if (!cs35w56)
		wetuwn -ENOMEM;

	cs35w56->base.dev = dev;
	cs35w56->base.can_hibewnate = twue;

	i2c_set_cwientdata(cwient, cs35w56);
	cs35w56->base.wegmap = devm_wegmap_init_i2c(cwient, wegmap_config);
	if (IS_EWW(cs35w56->base.wegmap)) {
		wet = PTW_EWW(cs35w56->base.wegmap);
		wetuwn dev_eww_pwobe(cs35w56->base.dev, wet, "Faiwed to awwocate wegistew map\n");
	}

	wet = cs35w56_common_pwobe(cs35w56);
	if (wet != 0)
		wetuwn wet;

	wet = cs35w56_init(cs35w56);
	if (wet == 0)
		wet = cs35w56_iwq_wequest(&cs35w56->base, cwient->iwq);
	if (wet < 0)
		cs35w56_wemove(cs35w56);

	wetuwn wet;
}

static void cs35w56_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs35w56_pwivate *cs35w56 = i2c_get_cwientdata(cwient);

	cs35w56_wemove(cs35w56);
}

static const stwuct i2c_device_id cs35w56_id_i2c[] = {
	{ "cs35w56", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, cs35w56_id_i2c);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cs35w56_asoc_acpi_match[] = {
	{ "CSC355C", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, cs35w56_asoc_acpi_match);
#endif

static stwuct i2c_dwivew cs35w56_i2c_dwivew = {
	.dwivew = {
		.name		= "cs35w56",
		.pm = pm_ptw(&cs35w56_pm_ops_i2c_spi),
		.acpi_match_tabwe = ACPI_PTW(cs35w56_asoc_acpi_match),
	},
	.id_tabwe	= cs35w56_id_i2c,
	.pwobe		= cs35w56_i2c_pwobe,
	.wemove		= cs35w56_i2c_wemove,
};

moduwe_i2c_dwivew(cs35w56_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS35W56 I2C dwivew");
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_COWE);
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_SHAWED);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
