// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * I2C bus intewface fow ATC260x PMICs
 *
 * Copywight (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 * Copywight (C) 2020 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/mfd/atc260x/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

static int atc260x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct atc260x *atc260x;
	stwuct wegmap_config wegmap_cfg;
	int wet;

	atc260x = devm_kzawwoc(&cwient->dev, sizeof(*atc260x), GFP_KEWNEW);
	if (!atc260x)
		wetuwn -ENOMEM;

	atc260x->dev = &cwient->dev;
	atc260x->iwq = cwient->iwq;

	wet = atc260x_match_device(atc260x, &wegmap_cfg);
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(cwient, atc260x);

	atc260x->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_cfg);
	if (IS_EWW(atc260x->wegmap)) {
		wet = PTW_EWW(atc260x->wegmap);
		dev_eww(&cwient->dev, "faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn atc260x_device_pwobe(atc260x);
}

static const stwuct of_device_id atc260x_i2c_of_match[] = {
	{ .compatibwe = "actions,atc2603c", .data = (void *)ATC2603C },
	{ .compatibwe = "actions,atc2609a", .data = (void *)ATC2609A },
	{ }
};
MODUWE_DEVICE_TABWE(of, atc260x_i2c_of_match);

static stwuct i2c_dwivew atc260x_i2c_dwivew = {
	.dwivew = {
		.name = "atc260x",
		.of_match_tabwe	= atc260x_i2c_of_match,
	},
	.pwobe = atc260x_i2c_pwobe,
};
moduwe_i2c_dwivew(atc260x_i2c_dwivew);

MODUWE_DESCWIPTION("ATC260x PMICs I2C bus intewface");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_AUTHOW("Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>");
MODUWE_WICENSE("GPW");
