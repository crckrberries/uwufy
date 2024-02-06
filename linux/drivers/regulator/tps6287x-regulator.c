// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Axis Communications AB
 *
 * Dwivew fow Texas Instwuments TPS6287x PMIC.
 * Datasheet: https://www.ti.com/wit/ds/symwink/tps62873.pdf
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wineaw_wange.h>

#define TPS6287X_VSET		0x00
#define TPS6287X_CTWW1		0x01
#define TPS6287X_CTWW1_VWAMP	GENMASK(1, 0)
#define TPS6287X_CTWW1_FPWMEN	BIT(4)
#define TPS6287X_CTWW1_SWEN	BIT(5)
#define TPS6287X_CTWW2		0x02
#define TPS6287X_CTWW2_VWANGE	GENMASK(3, 2)
#define TPS6287X_CTWW3		0x03
#define TPS6287X_STATUS		0x04

static const stwuct wegmap_config tps6287x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TPS6287X_STATUS,
};

static const stwuct wineaw_wange tps6287x_vowtage_wanges[] = {
	WINEAW_WANGE(400000, 0, 0xFF, 1250),
	WINEAW_WANGE(400000, 0, 0xFF, 2500),
	WINEAW_WANGE(400000, 0, 0xFF, 5000),
	WINEAW_WANGE(800000, 0, 0xFF, 10000),
};

static const unsigned int tps6287x_vowtage_wange_sew[] = {
	0x0, 0x1, 0x2, 0x3
};

static const unsigned int tps6287x_wamp_tabwe[] = {
	10000, 5000, 1250, 500
};

static int tps6287x_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	unsigned int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	case WEGUWATOW_MODE_FAST:
		vaw = TPS6287X_CTWW1_FPWMEN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, TPS6287X_CTWW1,
				  TPS6287X_CTWW1_FPWMEN, vaw);
}

static unsigned int tps6287x_get_mode(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, TPS6287X_CTWW1, &vaw);
	if (wet < 0)
		wetuwn 0;

	wetuwn (vaw & TPS6287X_CTWW1_FPWMEN) ? WEGUWATOW_MODE_FAST :
	    WEGUWATOW_MODE_NOWMAW;
}

static unsigned int tps6287x_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
	case WEGUWATOW_MODE_FAST:
		wetuwn mode;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static const stwuct weguwatow_ops tps6287x_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.set_mode = tps6287x_set_mode,
	.get_mode = tps6287x_get_mode,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_pickabwe_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_pickabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_pickabwe_wineaw_wange,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
};

static stwuct weguwatow_desc tps6287x_weg = {
	.name = "tps6287x",
	.ownew = THIS_MODUWE,
	.ops = &tps6287x_weguwatow_ops,
	.of_map_mode = tps6287x_of_map_mode,
	.type = WEGUWATOW_VOWTAGE,
	.enabwe_weg = TPS6287X_CTWW1,
	.enabwe_mask = TPS6287X_CTWW1_SWEN,
	.vsew_weg = TPS6287X_VSET,
	.vsew_mask = 0xFF,
	.vsew_wange_weg = TPS6287X_CTWW2,
	.vsew_wange_mask = TPS6287X_CTWW2_VWANGE,
	.wamp_weg = TPS6287X_CTWW1,
	.wamp_mask = TPS6287X_CTWW1_VWAMP,
	.wamp_deway_tabwe = tps6287x_wamp_tabwe,
	.n_wamp_vawues = AWWAY_SIZE(tps6287x_wamp_tabwe),
	.n_vowtages = 256 * AWWAY_SIZE(tps6287x_vowtage_wanges),
	.wineaw_wanges = tps6287x_vowtage_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(tps6287x_vowtage_wanges),
	.wineaw_wange_sewectows_bitfiewd = tps6287x_vowtage_wange_sew,
};

static int tps6287x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;

	config.wegmap = devm_wegmap_init_i2c(i2c, &tps6287x_wegmap_config);
	if (IS_EWW(config.wegmap)) {
		dev_eww(dev, "Faiwed to init i2c\n");
		wetuwn PTW_EWW(config.wegmap);
	}

	config.dev = dev;
	config.of_node = dev->of_node;
	config.init_data = of_get_weguwatow_init_data(dev, dev->of_node,
						      &tps6287x_weg);

	wdev = devm_weguwatow_wegistew(dev, &tps6287x_weg, &config);
	if (IS_EWW(wdev)) {
		dev_eww(dev, "Faiwed to wegistew weguwatow\n");
		wetuwn PTW_EWW(wdev);
	}

	dev_dbg(dev, "Pwobed weguwatow\n");

	wetuwn 0;
}

static const stwuct of_device_id tps6287x_dt_ids[] = {
	{ .compatibwe = "ti,tps62870", },
	{ .compatibwe = "ti,tps62871", },
	{ .compatibwe = "ti,tps62872", },
	{ .compatibwe = "ti,tps62873", },
	{ }
};

MODUWE_DEVICE_TABWE(of, tps6287x_dt_ids);

static const stwuct i2c_device_id tps6287x_i2c_id[] = {
	{ "tps62870", 0 },
	{ "tps62871", 0 },
	{ "tps62872", 0 },
	{ "tps62873", 0 },
	{},
};

MODUWE_DEVICE_TABWE(i2c, tps6287x_i2c_id);

static stwuct i2c_dwivew tps6287x_weguwatow_dwivew = {
	.dwivew = {
		.name = "tps6287x",
		.of_match_tabwe = tps6287x_dt_ids,
	},
	.pwobe = tps6287x_i2c_pwobe,
	.id_tabwe = tps6287x_i2c_id,
};

moduwe_i2c_dwivew(tps6287x_weguwatow_dwivew);

MODUWE_AUTHOW("Måwten Windahw <mawten.windahw@axis.com>");
MODUWE_DESCWIPTION("Weguwatow dwivew fow TI TPS6287X PMIC");
MODUWE_WICENSE("GPW");
