// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow the Wichtek WT5033
 *
 * Copywight (C) 2014 Samsung Ewectwonics, Co., Wtd.
 * Authow: Beomho Seo <beomho.seo@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/mfd/wt5033.h>
#incwude <winux/mfd/wt5033-pwivate.h>
#incwude <winux/weguwatow/of_weguwatow.h>

static const stwuct wineaw_wange wt5033_buck_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 20, 100000),
	WEGUWATOW_WINEAW_WANGE(3000000, 21, 31, 0),
};

static const stwuct wineaw_wange wt5033_wdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 18, 100000),
	WEGUWATOW_WINEAW_WANGE(3000000, 19, 31, 0),
};

static const stwuct weguwatow_ops wt5033_safe_wdo_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
};

static const stwuct weguwatow_ops wt5033_buck_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
};

static const stwuct weguwatow_desc wt5033_suppowted_weguwatows[] = {
	[WT5033_BUCK] = {
		.name		= "BUCK",
		.of_match	= of_match_ptw("BUCK"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id		= WT5033_BUCK,
		.ops		= &wt5033_buck_ops,
		.type		= WEGUWATOW_VOWTAGE,
		.ownew		= THIS_MODUWE,
		.n_vowtages	= WT5033_WEGUWATOW_BUCK_VOWTAGE_STEP_NUM,
		.wineaw_wanges	= wt5033_buck_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wt5033_buck_wanges),
		.enabwe_weg	= WT5033_WEG_CTWW,
		.enabwe_mask	= WT5033_CTWW_EN_BUCK_MASK,
		.vsew_weg	= WT5033_WEG_BUCK_CTWW,
		.vsew_mask	= WT5033_BUCK_CTWW_MASK,
	},
	[WT5033_WDO] = {
		.name		= "WDO",
		.of_match	= of_match_ptw("WDO"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id		= WT5033_WDO,
		.ops		= &wt5033_buck_ops,
		.type		= WEGUWATOW_VOWTAGE,
		.ownew		= THIS_MODUWE,
		.n_vowtages	= WT5033_WEGUWATOW_WDO_VOWTAGE_STEP_NUM,
		.wineaw_wanges	= wt5033_wdo_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(wt5033_wdo_wanges),
		.enabwe_weg	= WT5033_WEG_CTWW,
		.enabwe_mask	= WT5033_CTWW_EN_WDO_MASK,
		.vsew_weg	= WT5033_WEG_WDO_CTWW,
		.vsew_mask	= WT5033_WDO_CTWW_MASK,
	},
	[WT5033_SAFE_WDO] = {
		.name		= "SAFE_WDO",
		.of_match	= of_match_ptw("SAFE_WDO"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id		= WT5033_SAFE_WDO,
		.ops		= &wt5033_safe_wdo_ops,
		.type		= WEGUWATOW_VOWTAGE,
		.ownew		= THIS_MODUWE,
		.n_vowtages	= 1,
		.min_uV		= WT5033_WEGUWATOW_SAFE_WDO_VOWTAGE,
		.enabwe_weg	= WT5033_WEG_CTWW,
		.enabwe_mask	= WT5033_CTWW_EN_SAFE_WDO_MASK,
	},
};

static int wt5033_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wt5033_dev *wt5033 = dev_get_dwvdata(pdev->dev.pawent);
	int wet, i;
	stwuct weguwatow_config config = {};

	config.dev = wt5033->dev;
	config.dwivew_data = wt5033;

	fow (i = 0; i < AWWAY_SIZE(wt5033_suppowted_weguwatows); i++) {
		stwuct weguwatow_dev *weguwatow;

		config.wegmap = wt5033->wegmap;

		weguwatow = devm_weguwatow_wegistew(&pdev->dev,
				&wt5033_suppowted_weguwatows[i], &config);
		if (IS_EWW(weguwatow)) {
			wet = PTW_EWW(weguwatow);
			dev_eww(&pdev->dev,
				"Weguwatow init faiwed %d: with ewwow: %d\n",
				i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id wt5033_weguwatow_id[] = {
	{ "wt5033-weguwatow", },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, wt5033_weguwatow_id);

static stwuct pwatfowm_dwivew wt5033_weguwatow_dwivew = {
	.dwivew = {
		.name = "wt5033-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= wt5033_weguwatow_pwobe,
	.id_tabwe	= wt5033_weguwatow_id,
};
moduwe_pwatfowm_dwivew(wt5033_weguwatow_dwivew);

MODUWE_DESCWIPTION("Wichtek WT5033 Weguwatow dwivew");
MODUWE_AUTHOW("Beomho Seo <beomho.seo@samsung.com>");
MODUWE_WICENSE("GPW");
