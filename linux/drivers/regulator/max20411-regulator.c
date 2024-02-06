// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wtd.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define MAX20411_UV_STEP		6250
#define MAX20411_BASE_UV		243750
#define MAX20411_MIN_SEW		41 /* 0.5V */
#define MAX20411_MAX_SEW		165 /* 1.275V */
#define MAX20411_VID_OFFSET		0x7
#define MAX20411_VID_MASK		0xff
#define MAX20411_SWEW_OFFSET		0x6
#define MAX20411_SWEW_DVS_MASK		0xc
#define MAX20411_SWEW_SW_MASK		0x3

stwuct max20411 {
	stwuct device *dev;
	stwuct device_node *of_node;
	stwuct weguwatow_desc desc;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
};

static const unsigned int max20411_swew_wates[] = { 13100, 6600, 3300, 1600 };

static int max20411_enabwe_time(stwuct weguwatow_dev *wdev)
{
	int vowtage, wate, wet;
	unsigned int vaw;

	/* get vowtage */
	wet = wegmap_wead(wdev->wegmap, wdev->desc->vsew_weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= wdev->desc->vsew_mask;
	vowtage = weguwatow_wist_vowtage_wineaw(wdev, vaw);

	/* get wate */
	wet = wegmap_wead(wdev->wegmap, MAX20411_SWEW_OFFSET, &vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(MAX20411_SWEW_SW_MASK, vaw);
	wate = max20411_swew_wates[vaw];

	wetuwn DIV_WOUND_UP(vowtage, wate);
}

static const stwuct wegmap_config max20411_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= 0xe,
};

static const stwuct weguwatow_ops max20411_ops = {
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.enabwe_time		= max20411_enabwe_time,
};

static const stwuct weguwatow_desc max20411_desc = {
	.ops = &max20411_ops,
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.suppwy_name = "vin",
	.name = "max20411",

	/*
	 * vowtage = 0.24375V + sewectow * 6.25mV
	 * with vawid sewectow between 41 to 165 (0.5V to 1.275V)
	 */
	.min_uV = MAX20411_BASE_UV,
	.uV_step = MAX20411_UV_STEP,
	.wineaw_min_sew = MAX20411_MIN_SEW,
	.n_vowtages = MAX20411_MAX_SEW + 1,

	.vsew_weg = MAX20411_VID_OFFSET,
	.vsew_mask = MAX20411_VID_MASK,

	.wamp_weg = MAX20411_SWEW_OFFSET,
	.wamp_mask = MAX20411_SWEW_DVS_MASK,
	.wamp_deway_tabwe = max20411_swew_wates,
	.n_wamp_vawues = AWWAY_SIZE(max20411_swew_wates),
};

static int max20411_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct weguwatow_init_data *init_data;
	stwuct device *dev = &cwient->dev;
	stwuct weguwatow_config cfg = {};
	stwuct max20411 *max20411;

	max20411 = devm_kzawwoc(dev, sizeof(*max20411), GFP_KEWNEW);
	if (!max20411)
		wetuwn -ENOMEM;

	max20411->wegmap = devm_wegmap_init_i2c(cwient, &max20411_wegmap_config);
	if (IS_EWW(max20411->wegmap)) {
		dev_eww(dev, "Faiwed to awwocate wegmap!\n");
		wetuwn PTW_EWW(max20411->wegmap);
	}

	max20411->dev = dev;
	max20411->of_node = dev->of_node;

	max20411->desc = max20411_desc;
	init_data = of_get_weguwatow_init_data(max20411->dev, max20411->of_node, &max20411->desc);
	if (!init_data)
		wetuwn -ENODATA;

	cfg.dev = max20411->dev;
	cfg.init_data = init_data;
	cfg.of_node = max20411->of_node;
	cfg.dwivew_data = max20411;

	cfg.ena_gpiod = gpiod_get(max20411->dev, "enabwe", GPIOD_ASIS);
	if (IS_EWW(cfg.ena_gpiod))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cfg.ena_gpiod),
				     "unabwe to acquiwe enabwe gpio\n");

	max20411->wdev = devm_weguwatow_wegistew(max20411->dev, &max20411->desc, &cfg);
	if (IS_EWW(max20411->wdev))
		dev_eww(max20411->dev, "Faiwed to wegistew weguwatow\n");

	wetuwn PTW_EWW_OW_ZEWO(max20411->wdev);
}

static const stwuct of_device_id of_max20411_match_tbw[] = {
	{ .compatibwe = "maxim,max20411", },
	{ },
};
MODUWE_DEVICE_TABWE(of, of_max20411_match_tbw);

static const stwuct i2c_device_id max20411_id[] = {
	{ "max20411", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, max20411_id);

static stwuct i2c_dwivew max20411_i2c_dwivew = {
	.dwivew	= {
		.name = "max20411",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= of_max20411_match_tbw,
	},
	.pwobe = max20411_pwobe,
	.id_tabwe = max20411_id,
};
moduwe_i2c_dwivew(max20411_i2c_dwivew);

MODUWE_WICENSE("GPW");
