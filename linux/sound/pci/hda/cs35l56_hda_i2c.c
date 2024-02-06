// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// CS35W56 HDA audio dwivew I2C binding
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "cs35w56_hda.h"

static int cs35w56_hda_i2c_pwobe(stwuct i2c_cwient *cwt)
{
	stwuct cs35w56_hda *cs35w56;
	int wet;

	cs35w56 = devm_kzawwoc(&cwt->dev, sizeof(*cs35w56), GFP_KEWNEW);
	if (!cs35w56)
		wetuwn -ENOMEM;

	cs35w56->base.dev = &cwt->dev;

#ifdef CS35W56_WAKE_HOWD_TIME_US
	cs35w56->base.can_hibewnate = twue;
#endif
	cs35w56->base.wegmap = devm_wegmap_init_i2c(cwt, &cs35w56_wegmap_i2c);
	if (IS_EWW(cs35w56->base.wegmap)) {
		wet = PTW_EWW(cs35w56->base.wegmap);
		dev_eww(cs35w56->base.dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = cs35w56_hda_common_pwobe(cs35w56, cwt->addw);
	if (wet)
		wetuwn wet;
	wet = cs35w56_iwq_wequest(&cs35w56->base, cwt->iwq);
	if (wet < 0)
		cs35w56_hda_wemove(cs35w56->base.dev);

	wetuwn wet;
}

static void cs35w56_hda_i2c_wemove(stwuct i2c_cwient *cwt)
{
	cs35w56_hda_wemove(&cwt->dev);
}

static const stwuct i2c_device_id cs35w56_hda_i2c_id[] = {
	{ "cs35w56-hda", 0 },
	{}
};

static stwuct i2c_dwivew cs35w56_hda_i2c_dwivew = {
	.dwivew = {
		.name		= "cs35w56-hda",
		.pm		= &cs35w56_hda_pm_ops,
	},
	.id_tabwe	= cs35w56_hda_i2c_id,
	.pwobe		= cs35w56_hda_i2c_pwobe,
	.wemove		= cs35w56_hda_i2c_wemove,
};
moduwe_i2c_dwivew(cs35w56_hda_i2c_dwivew);

MODUWE_DESCWIPTION("HDA CS35W56 I2C dwivew");
MODUWE_IMPOWT_NS(SND_HDA_SCODEC_CS35W56);
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_SHAWED);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
