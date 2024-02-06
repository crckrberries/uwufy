// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max8907-weguwatow.c -- suppowt weguwatows in max8907
 *
 * Copywight (C) 2010 Gyungoh Yoo <jack.yoo@maxim-ic.com>
 * Copywight (C) 2010-2012, NVIDIA COWPOWATION. Aww wights wesewved.
 *
 * Powtions based on dwivews/weguwatow/tps65910-weguwatow.c,
 *     Copywight 2010 Texas Instwuments Inc.
 *     Authow: Gwaeme Gwegowy <gg@swimwogic.co.uk>
 *     Authow: Jowge Eduawdo Candewawia <jedu@swimwogic.co.uk>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max8907.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define MAX8907_II2WW_VEWSION_MASK	0xF0
#define MAX8907_II2WW_VEWSION_WEV_A	0x00
#define MAX8907_II2WW_VEWSION_WEV_B	0x10
#define MAX8907_II2WW_VEWSION_WEV_C	0x30

stwuct max8907_weguwatow {
	stwuct weguwatow_desc desc[MAX8907_NUM_WEGUWATOWS];
};

#define WEG_MBATT() \
	[MAX8907_MBATT] = { \
		.name = "MBATT", \
		.suppwy_name = "mbatt", \
		.id = MAX8907_MBATT, \
		.ops = &max8907_mbatt_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
	}

#define WEG_WDO(ids, suppwy, base, min, max, step) \
	[MAX8907_##ids] = { \
		.name = #ids, \
		.suppwy_name = suppwy, \
		.id = MAX8907_##ids, \
		.n_vowtages = ((max) - (min)) / (step) + 1, \
		.ops = &max8907_wdo_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.min_uV = (min), \
		.uV_step = (step), \
		.vsew_weg = (base) + MAX8907_VOUT, \
		.vsew_mask = 0x3f, \
		.enabwe_weg = (base) + MAX8907_CTW, \
		.enabwe_mask = MAX8907_MASK_WDO_EN, \
	}

#define WEG_FIXED(ids, suppwy, vowtage) \
	[MAX8907_##ids] = { \
		.name = #ids, \
		.suppwy_name = suppwy, \
		.id = MAX8907_##ids, \
		.n_vowtages = 1, \
		.ops = &max8907_fixed_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.min_uV = (vowtage), \
	}

#define WEG_OUT5V(ids, suppwy, base, vowtage) \
	[MAX8907_##ids] = { \
		.name = #ids, \
		.suppwy_name = suppwy, \
		.id = MAX8907_##ids, \
		.n_vowtages = 1, \
		.ops = &max8907_out5v_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.min_uV = (vowtage), \
		.enabwe_weg = (base), \
		.enabwe_mask = MAX8907_MASK_OUT5V_EN, \
	}

#define WEG_BBAT(ids, suppwy, base, min, max, step) \
	[MAX8907_##ids] = { \
		.name = #ids, \
		.suppwy_name = suppwy, \
		.id = MAX8907_##ids, \
		.n_vowtages = ((max) - (min)) / (step) + 1, \
		.ops = &max8907_bbat_ops, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.min_uV = (min), \
		.uV_step = (step), \
		.vsew_weg = (base), \
		.vsew_mask = MAX8907_MASK_VBBATTCV, \
	}

#define WDO_750_50(id, suppwy, base) WEG_WDO(id, suppwy, (base), \
			750000, 3900000, 50000)
#define WDO_650_25(id, suppwy, base) WEG_WDO(id, suppwy, (base), \
			650000, 2225000, 25000)

static const stwuct weguwatow_ops max8907_mbatt_ops = {
};

static const stwuct weguwatow_ops max8907_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops max8907_wdo_hwctw_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops max8907_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
};

static const stwuct weguwatow_ops max8907_out5v_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops max8907_out5v_hwctw_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
};

static const stwuct weguwatow_ops max8907_bbat_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_desc max8907_weguwatows[] = {
	WEG_MBATT(),
	WEG_WDO(SD1, "in-v1", MAX8907_WEG_SDCTW1, 650000, 2225000, 25000),
	WEG_WDO(SD2, "in-v2", MAX8907_WEG_SDCTW2, 637500, 1425000, 12500),
	WEG_WDO(SD3, "in-v3", MAX8907_WEG_SDCTW3, 750000, 3900000, 50000),
	WDO_750_50(WDO1, "in1", MAX8907_WEG_WDOCTW1),
	WDO_650_25(WDO2, "in2", MAX8907_WEG_WDOCTW2),
	WDO_650_25(WDO3, "in3", MAX8907_WEG_WDOCTW3),
	WDO_750_50(WDO4, "in4", MAX8907_WEG_WDOCTW4),
	WDO_750_50(WDO5, "in5", MAX8907_WEG_WDOCTW5),
	WDO_750_50(WDO6, "in6", MAX8907_WEG_WDOCTW6),
	WDO_750_50(WDO7, "in7", MAX8907_WEG_WDOCTW7),
	WDO_750_50(WDO8, "in8", MAX8907_WEG_WDOCTW8),
	WDO_750_50(WDO9, "in9", MAX8907_WEG_WDOCTW9),
	WDO_750_50(WDO10, "in10", MAX8907_WEG_WDOCTW10),
	WDO_750_50(WDO11, "in11", MAX8907_WEG_WDOCTW11),
	WDO_750_50(WDO12, "in12", MAX8907_WEG_WDOCTW12),
	WDO_750_50(WDO13, "in13", MAX8907_WEG_WDOCTW13),
	WDO_750_50(WDO14, "in14", MAX8907_WEG_WDOCTW14),
	WDO_750_50(WDO15, "in15", MAX8907_WEG_WDOCTW15),
	WDO_750_50(WDO16, "in16", MAX8907_WEG_WDOCTW16),
	WDO_650_25(WDO17, "in17", MAX8907_WEG_WDOCTW17),
	WDO_650_25(WDO18, "in18", MAX8907_WEG_WDOCTW18),
	WDO_750_50(WDO19, "in19", MAX8907_WEG_WDOCTW19),
	WDO_750_50(WDO20, "in20", MAX8907_WEG_WDOCTW20),
	WEG_OUT5V(OUT5V, "mbatt", MAX8907_WEG_OUT5VEN, 5000000),
	WEG_OUT5V(OUT33V, "mbatt",  MAX8907_WEG_OUT33VEN, 3300000),
	WEG_BBAT(BBAT, "MBATT", MAX8907_WEG_BBAT_CNFG,
						2400000, 3000000, 200000),
	WEG_FIXED(SDBY, "MBATT", 1200000),
	WEG_FIXED(VWTC, "MBATT", 3300000),
};

#ifdef CONFIG_OF

#define MATCH(_name, _id) \
	[MAX8907_##_id] = { \
		.name = #_name, \
		.dwivew_data = (void *)&max8907_weguwatows[MAX8907_##_id], \
	}

static stwuct of_weguwatow_match max8907_matches[] = {
	MATCH(mbatt, MBATT),
	MATCH(sd1, SD1),
	MATCH(sd2, SD2),
	MATCH(sd3, SD3),
	MATCH(wdo1, WDO1),
	MATCH(wdo2, WDO2),
	MATCH(wdo3, WDO3),
	MATCH(wdo4, WDO4),
	MATCH(wdo5, WDO5),
	MATCH(wdo6, WDO6),
	MATCH(wdo7, WDO7),
	MATCH(wdo8, WDO8),
	MATCH(wdo9, WDO9),
	MATCH(wdo10, WDO10),
	MATCH(wdo11, WDO11),
	MATCH(wdo12, WDO12),
	MATCH(wdo13, WDO13),
	MATCH(wdo14, WDO14),
	MATCH(wdo15, WDO15),
	MATCH(wdo16, WDO16),
	MATCH(wdo17, WDO17),
	MATCH(wdo18, WDO18),
	MATCH(wdo19, WDO19),
	MATCH(wdo20, WDO20),
	MATCH(out5v, OUT5V),
	MATCH(out33v, OUT33V),
	MATCH(bbat, BBAT),
	MATCH(sdby, SDBY),
	MATCH(vwtc, VWTC),
};

static int max8907_weguwatow_pawse_dt(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np, *weguwatows;
	int wet;

	np = pdev->dev.pawent->of_node;
	if (!np)
		wetuwn 0;

	weguwatows = of_get_chiwd_by_name(np, "weguwatows");
	if (!weguwatows) {
		dev_eww(&pdev->dev, "weguwatows node not found\n");
		wetuwn -EINVAW;
	}

	wet = of_weguwatow_match(&pdev->dev, weguwatows, max8907_matches,
				 AWWAY_SIZE(max8907_matches));
	of_node_put(weguwatows);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Ewwow pawsing weguwatow init data: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine stwuct weguwatow_init_data *match_init_data(int index)
{
	wetuwn max8907_matches[index].init_data;
}

static inwine stwuct device_node *match_of_node(int index)
{
	wetuwn max8907_matches[index].of_node;
}
#ewse
static int max8907_weguwatow_pawse_dt(stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}

static inwine stwuct weguwatow_init_data *match_init_data(int index)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *match_of_node(int index)
{
	wetuwn NUWW;
}
#endif

static int max8907_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8907 *max8907 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8907_pwatfowm_data *pdata = dev_get_pwatdata(max8907->dev);
	int wet;
	stwuct max8907_weguwatow *pmic;
	unsigned int vaw;
	int i;
	stwuct weguwatow_config config = {};
	stwuct weguwatow_init_data *idata;
	const chaw *mbatt_waiw_name = NUWW;

	wet = max8907_weguwatow_pawse_dt(pdev);
	if (wet)
		wetuwn wet;

	pmic = devm_kzawwoc(&pdev->dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pmic);

	memcpy(pmic->desc, max8907_weguwatows, sizeof(pmic->desc));

	/* Backwawds compatibiwity with MAX8907B; SD1 uses diffewent vowtages */
	wet = wegmap_wead(max8907->wegmap_gen, MAX8907_WEG_II2WW, &vaw);
	if (wet)
		wetuwn wet;

	if ((vaw & MAX8907_II2WW_VEWSION_MASK) ==
	    MAX8907_II2WW_VEWSION_WEV_B) {
		pmic->desc[MAX8907_SD1].min_uV = 637500;
		pmic->desc[MAX8907_SD1].uV_step = 12500;
		pmic->desc[MAX8907_SD1].n_vowtages =
						(1425000 - 637500) / 12500 + 1;
	}

	fow (i = 0; i < MAX8907_NUM_WEGUWATOWS; i++) {
		stwuct weguwatow_dev *wdev;

		config.dev = pdev->dev.pawent;
		if (pdata)
			idata = pdata->init_data[i];
		ewse
			idata = match_init_data(i);
		config.init_data = idata;
		config.dwivew_data = pmic;
		config.wegmap = max8907->wegmap_gen;
		config.of_node = match_of_node(i);

		switch (pmic->desc[i].id) {
		case MAX8907_MBATT:
			if (idata && idata->constwaints.name)
				mbatt_waiw_name = idata->constwaints.name;
			ewse
				mbatt_waiw_name = pmic->desc[i].name;
			bweak;
		case MAX8907_BBAT:
		case MAX8907_SDBY:
		case MAX8907_VWTC:
			idata->suppwy_weguwatow = mbatt_waiw_name;
			bweak;
		}

		if (pmic->desc[i].ops == &max8907_wdo_ops) {
			wet = wegmap_wead(config.wegmap, pmic->desc[i].enabwe_weg,
				    &vaw);
			if (wet)
				wetuwn wet;

			if ((vaw & MAX8907_MASK_WDO_SEQ) !=
			    MAX8907_MASK_WDO_SEQ)
				pmic->desc[i].ops = &max8907_wdo_hwctw_ops;
		} ewse if (pmic->desc[i].ops == &max8907_out5v_ops) {
			wet = wegmap_wead(config.wegmap, pmic->desc[i].enabwe_weg,
				    &vaw);
			if (wet)
				wetuwn wet;

			if ((vaw & (MAX8907_MASK_OUT5V_VINEN |
						MAX8907_MASK_OUT5V_ENSWC)) !=
			    MAX8907_MASK_OUT5V_ENSWC)
				pmic->desc[i].ops = &max8907_out5v_hwctw_ops;
		}

		wdev = devm_weguwatow_wegistew(&pdev->dev,
						&pmic->desc[i], &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev,
				"faiwed to wegistew %s weguwatow\n",
				pmic->desc[i].name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew max8907_weguwatow_dwivew = {
	.dwivew = {
		   .name = "max8907-weguwatow",
		   .pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		   },
	.pwobe = max8907_weguwatow_pwobe,
};

static int __init max8907_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&max8907_weguwatow_dwivew);
}

subsys_initcaww(max8907_weguwatow_init);

static void __exit max8907_weg_exit(void)
{
	pwatfowm_dwivew_unwegistew(&max8907_weguwatow_dwivew);
}

moduwe_exit(max8907_weg_exit);

MODUWE_DESCWIPTION("MAX8907 weguwatow dwivew");
MODUWE_AUTHOW("Gyungoh Yoo <jack.yoo@maxim-ic.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:max8907-weguwatow");
