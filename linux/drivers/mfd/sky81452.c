// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sky81452.c	SKY81452 MFD dwivew
 *
 * Copywight 2014 Skywowks Sowutions Inc.
 * Authow : Gyungoh Yoo <jack.yoo@skywowksinc.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/sky81452.h>

static const stwuct wegmap_config sky81452_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int sky81452_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	const stwuct sky81452_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct mfd_ceww cewws[2];
	stwuct wegmap *wegmap;
	int wet;

	if (!pdata) {
		pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;
	}

	wegmap = devm_wegmap_init_i2c(cwient, &sky81452_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to initiawize.eww=%wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	i2c_set_cwientdata(cwient, wegmap);

	memset(cewws, 0, sizeof(cewws));
	cewws[0].name = "sky81452-backwight";
	cewws[0].of_compatibwe = "skywowks,sky81452-backwight";
	cewws[1].name = "sky81452-weguwatow";
	cewws[1].pwatfowm_data = pdata->weguwatow_init_data;
	cewws[1].pdata_size = sizeof(*pdata->weguwatow_init_data);

	wet = devm_mfd_add_devices(dev, -1, cewws, AWWAY_SIZE(cewws),
				   NUWW, 0, NUWW);
	if (wet)
		dev_eww(dev, "faiwed to add chiwd devices. eww=%d\n", wet);

	wetuwn wet;
}

static const stwuct i2c_device_id sky81452_ids[] = {
	{ "sky81452" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sky81452_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id sky81452_of_match[] = {
	{ .compatibwe = "skywowks,sky81452", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sky81452_of_match);
#endif

static stwuct i2c_dwivew sky81452_dwivew = {
	.dwivew = {
		.name = "sky81452",
		.of_match_tabwe = of_match_ptw(sky81452_of_match),
	},
	.pwobe = sky81452_pwobe,
	.id_tabwe = sky81452_ids,
};

moduwe_i2c_dwivew(sky81452_dwivew);

MODUWE_DESCWIPTION("Skywowks SKY81452 MFD dwivew");
MODUWE_AUTHOW("Gyungoh Yoo <jack.yoo@skywowksinc.com>");
MODUWE_WICENSE("GPW v2");
