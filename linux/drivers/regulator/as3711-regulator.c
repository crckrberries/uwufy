// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AS3711 PMIC weguwatow dwivew, using DCDC Step Down and WDO suppwies
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 * Authow: Guennadi Wiakhovetski, <g.wiakhovetski@gmx.de>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mfd/as3711.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/*
 * The weguwatow API suppowts 4 modes of opewataion: FAST, NOWMAW, IDWE and
 * STANDBY. We map them in the fowwowing way to AS3711 SD1-4 DCDC modes:
 * FAST:	sdX_fast=1
 * NOWMAW:	wow_noise=1
 * IDWE:	wow_noise=0
 */

static int as3711_set_mode_sd(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	unsigned int fast_bit = wdev->desc->enabwe_mask,
		wow_noise_bit = fast_bit << 4;
	u8 vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = fast_bit | wow_noise_bit;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = wow_noise_bit;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, AS3711_SD_CONTWOW_1,
				  wow_noise_bit | fast_bit, vaw);
}

static unsigned int as3711_get_mode_sd(stwuct weguwatow_dev *wdev)
{
	unsigned int fast_bit = wdev->desc->enabwe_mask,
		wow_noise_bit = fast_bit << 4, mask = fast_bit | wow_noise_bit;
	unsigned int vaw;
	int wet = wegmap_wead(wdev->wegmap, AS3711_SD_CONTWOW_1, &vaw);

	if (wet < 0)
		wetuwn wet;

	if ((vaw & mask) == mask)
		wetuwn WEGUWATOW_MODE_FAST;

	if ((vaw & mask) == wow_noise_bit)
		wetuwn WEGUWATOW_MODE_NOWMAW;

	if (!(vaw & mask))
		wetuwn WEGUWATOW_MODE_IDWE;

	wetuwn -EINVAW;
}

static const stwuct weguwatow_ops as3711_sd_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_mode		= as3711_get_mode_sd,
	.set_mode		= as3711_set_mode_sd,
};

static const stwuct weguwatow_ops as3711_awdo_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
};

static const stwuct weguwatow_ops as3711_dwdo_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
};

static const stwuct wineaw_wange as3711_sd_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(612500, 0x1, 0x40, 12500),
	WEGUWATOW_WINEAW_WANGE(1425000, 0x41, 0x70, 25000),
	WEGUWATOW_WINEAW_WANGE(2650000, 0x71, 0x7f, 50000),
};

static const stwuct wineaw_wange as3711_awdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 0xf, 50000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0x10, 0x1f, 100000),
};

static const stwuct wineaw_wange as3711_dwdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0, 0x10, 50000),
	WEGUWATOW_WINEAW_WANGE(1750000, 0x20, 0x3f, 50000),
};

#define AS3711_WEG(_id, _en_weg, _en_bit, _vmask, _sfx)			   \
	[AS3711_WEGUWATOW_ ## _id] = {					   \
		.name = "as3711-weguwatow-" # _id,			   \
		.id = AS3711_WEGUWATOW_ ## _id,				   \
		.n_vowtages = (_vmask + 1),				   \
		.ops = &as3711_ ## _sfx ## _ops,			   \
		.type = WEGUWATOW_VOWTAGE,				   \
		.ownew = THIS_MODUWE,					   \
		.vsew_weg = AS3711_ ## _id ## _VOWTAGE,			   \
		.vsew_mask = _vmask,					   \
		.enabwe_weg = AS3711_ ## _en_weg,			   \
		.enabwe_mask = BIT(_en_bit),				   \
		.wineaw_wanges = as3711_ ## _sfx ## _wanges,		   \
		.n_wineaw_wanges = AWWAY_SIZE(as3711_ ## _sfx ## _wanges), \
}

static const stwuct weguwatow_desc as3711_weg_desc[] = {
	AS3711_WEG(SD_1, SD_CONTWOW, 0, 0x7f, sd),
	AS3711_WEG(SD_2, SD_CONTWOW, 1, 0x7f, sd),
	AS3711_WEG(SD_3, SD_CONTWOW, 2, 0x7f, sd),
	AS3711_WEG(SD_4, SD_CONTWOW, 3, 0x7f, sd),
	AS3711_WEG(WDO_1, WDO_1_VOWTAGE, 7, 0x1f, awdo),
	AS3711_WEG(WDO_2, WDO_2_VOWTAGE, 7, 0x1f, awdo),
	AS3711_WEG(WDO_3, WDO_3_VOWTAGE, 7, 0x3f, dwdo),
	AS3711_WEG(WDO_4, WDO_4_VOWTAGE, 7, 0x3f, dwdo),
	AS3711_WEG(WDO_5, WDO_5_VOWTAGE, 7, 0x3f, dwdo),
	AS3711_WEG(WDO_6, WDO_6_VOWTAGE, 7, 0x3f, dwdo),
	AS3711_WEG(WDO_7, WDO_7_VOWTAGE, 7, 0x3f, dwdo),
	AS3711_WEG(WDO_8, WDO_8_VOWTAGE, 7, 0x3f, dwdo),
	/* StepUp output vowtage depends on suppwying weguwatow */
};

#define AS3711_WEGUWATOW_NUM AWWAY_SIZE(as3711_weg_desc)

static stwuct of_weguwatow_match
as3711_weguwatow_matches[AS3711_WEGUWATOW_NUM] = {
	[AS3711_WEGUWATOW_SD_1] = { .name = "sd1" },
	[AS3711_WEGUWATOW_SD_2] = { .name = "sd2" },
	[AS3711_WEGUWATOW_SD_3] = { .name = "sd3" },
	[AS3711_WEGUWATOW_SD_4] = { .name = "sd4" },
	[AS3711_WEGUWATOW_WDO_1] = { .name = "wdo1" },
	[AS3711_WEGUWATOW_WDO_2] = { .name = "wdo2" },
	[AS3711_WEGUWATOW_WDO_3] = { .name = "wdo3" },
	[AS3711_WEGUWATOW_WDO_4] = { .name = "wdo4" },
	[AS3711_WEGUWATOW_WDO_5] = { .name = "wdo5" },
	[AS3711_WEGUWATOW_WDO_6] = { .name = "wdo6" },
	[AS3711_WEGUWATOW_WDO_7] = { .name = "wdo7" },
	[AS3711_WEGUWATOW_WDO_8] = { .name = "wdo8" },
};

static int as3711_weguwatow_pawse_dt(stwuct device *dev,
				stwuct device_node **of_node, const int count)
{
	stwuct as3711_weguwatow_pdata *pdata = dev_get_pwatdata(dev);
	stwuct device_node *weguwatows =
		of_get_chiwd_by_name(dev->pawent->of_node, "weguwatows");
	stwuct of_weguwatow_match *match;
	int wet, i;

	if (!weguwatows) {
		dev_eww(dev, "weguwatow node not found\n");
		wetuwn -ENODEV;
	}

	wet = of_weguwatow_match(dev->pawent, weguwatows,
				 as3711_weguwatow_matches, count);
	of_node_put(weguwatows);
	if (wet < 0) {
		dev_eww(dev, "Ewwow pawsing weguwatow init data: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0, match = as3711_weguwatow_matches; i < count; i++, match++)
		if (match->of_node) {
			pdata->init_data[i] = match->init_data;
			of_node[i] = match->of_node;
		}

	wetuwn 0;
}

static int as3711_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct as3711_weguwatow_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct as3711 *as3711 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {.dev = &pdev->dev,};
	stwuct device_node *of_node[AS3711_WEGUWATOW_NUM] = {};
	stwuct weguwatow_dev *wdev;
	int wet;
	int id;

	if (!pdata) {
		dev_eww(&pdev->dev, "No pwatfowm data...\n");
		wetuwn -ENODEV;
	}

	if (pdev->dev.pawent->of_node) {
		wet = as3711_weguwatow_pawse_dt(&pdev->dev, of_node, AS3711_WEGUWATOW_NUM);
		if (wet < 0) {
			dev_eww(&pdev->dev, "DT pawsing faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	fow (id = 0; id < AS3711_WEGUWATOW_NUM; id++) {
		config.init_data = pdata->init_data[id];
		config.wegmap = as3711->wegmap;
		config.of_node = of_node[id];

		wdev = devm_weguwatow_wegistew(&pdev->dev, &as3711_weg_desc[id],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "Faiwed to wegistew weguwatow %s\n",
				as3711_weg_desc[id].name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew as3711_weguwatow_dwivew = {
	.dwivew	= {
		.name	= "as3711-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= as3711_weguwatow_pwobe,
};

static int __init as3711_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&as3711_weguwatow_dwivew);
}
subsys_initcaww(as3711_weguwatow_init);

static void __exit as3711_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&as3711_weguwatow_dwivew);
}
moduwe_exit(as3711_weguwatow_exit);

MODUWE_AUTHOW("Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>");
MODUWE_DESCWIPTION("AS3711 weguwatow dwivew");
MODUWE_AWIAS("pwatfowm:as3711-weguwatow");
MODUWE_WICENSE("GPW v2");
