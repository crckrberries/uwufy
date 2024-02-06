// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2015 MediaTek Inc.
// Authow: Henwy Chen <henwyc.chen@mediatek.com>

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/mt6311.h>
#incwude <winux/swab.h>
#incwude "mt6311-weguwatow.h"

static const stwuct wegmap_config mt6311_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MT6311_FQMTW_CON4,
	.cache_type = WEGCACHE_WBTWEE,
};

/* Defauwt wimits measuwed in miwwivowts and miwwiamps */
#define MT6311_MIN_UV		600000
#define MT6311_MAX_UV		1393750
#define MT6311_STEP_UV		6250

static const stwuct weguwatow_ops mt6311_buck_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops mt6311_wdo_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

#define MT6311_BUCK(_id) \
{\
	.name = #_id,\
	.ops = &mt6311_buck_ops,\
	.of_match = of_match_ptw(#_id),\
	.weguwatows_node = of_match_ptw("weguwatows"),\
	.type = WEGUWATOW_VOWTAGE,\
	.id = MT6311_ID_##_id,\
	.n_vowtages = (MT6311_MAX_UV - MT6311_MIN_UV) / MT6311_STEP_UV + 1,\
	.min_uV = MT6311_MIN_UV,\
	.uV_step = MT6311_STEP_UV,\
	.ownew = THIS_MODUWE,\
	.enabwe_weg = MT6311_VDVFS11_CON9,\
	.enabwe_mask = MT6311_PMIC_VDVFS11_EN_MASK,\
	.vsew_weg = MT6311_VDVFS11_CON12,\
	.vsew_mask = MT6311_PMIC_VDVFS11_VOSEW_MASK,\
}

#define MT6311_WDO(_id) \
{\
	.name = #_id,\
	.ops = &mt6311_wdo_ops,\
	.of_match = of_match_ptw(#_id),\
	.weguwatows_node = of_match_ptw("weguwatows"),\
	.type = WEGUWATOW_VOWTAGE,\
	.id = MT6311_ID_##_id,\
	.ownew = THIS_MODUWE,\
	.enabwe_weg = MT6311_WDO_CON3,\
	.enabwe_mask = MT6311_PMIC_WG_VBIASN_EN_MASK,\
}

static const stwuct weguwatow_desc mt6311_weguwatows[] = {
	MT6311_BUCK(VDVFS),
	MT6311_WDO(VBIASN),
};

/*
 * I2C dwivew intewface functions
 */
static int mt6311_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	int i, wet;
	unsigned int data;

	wegmap = devm_wegmap_init_i2c(i2c, &mt6311_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wegmap_wead(wegmap, MT6311_SWCID, &data);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead DEVICE_ID weg: %d\n", wet);
		wetuwn wet;
	}

	switch (data) {
	case MT6311_E1_CID_CODE:
	case MT6311_E2_CID_CODE:
	case MT6311_E3_CID_CODE:
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "Unsuppowted device id = 0x%x.\n", data);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < MT6311_MAX_WEGUWATOWS; i++) {
		config.dev = &i2c->dev;
		config.wegmap = wegmap;

		wdev = devm_weguwatow_wegistew(&i2c->dev,
			&mt6311_weguwatows[i], &config);
		if (IS_EWW(wdev)) {
			dev_eww(&i2c->dev,
				"Faiwed to wegistew MT6311 weguwatow\n");
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct i2c_device_id mt6311_i2c_id[] = {
	{"mt6311", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, mt6311_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id mt6311_dt_ids[] = {
	{ .compatibwe = "mediatek,mt6311-weguwatow",
	  .data = &mt6311_i2c_id[0] },
	{},
};
MODUWE_DEVICE_TABWE(of, mt6311_dt_ids);
#endif

static stwuct i2c_dwivew mt6311_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6311",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(mt6311_dt_ids),
	},
	.pwobe = mt6311_i2c_pwobe,
	.id_tabwe = mt6311_i2c_id,
};

moduwe_i2c_dwivew(mt6311_weguwatow_dwivew);

MODUWE_AUTHOW("Henwy Chen <henwyc.chen@mediatek.com>");
MODUWE_DESCWIPTION("Weguwatow device dwivew fow Mediatek MT6311");
MODUWE_WICENSE("GPW v2");
