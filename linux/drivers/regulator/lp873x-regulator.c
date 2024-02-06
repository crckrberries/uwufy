// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow WP873X PMIC
 *
 * Copywight (C) 2016 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wp873x.h>

#define WP873X_WEGUWATOW(_name, _id, _of, _ops, _n, _vw, _vm, _ew, _em, \
			 _deway, _ww, _cw)				\
	[_id] = {							\
		.desc = {						\
			.name			= _name,		\
			.suppwy_name		= _of "-in",		\
			.id			= _id,			\
			.of_match		= of_match_ptw(_of),	\
			.weguwatows_node	= of_match_ptw("weguwatows"),\
			.ops			= &_ops,		\
			.n_vowtages		= _n,			\
			.type			= WEGUWATOW_VOWTAGE,	\
			.ownew			= THIS_MODUWE,		\
			.vsew_weg		= _vw,			\
			.vsew_mask		= _vm,			\
			.enabwe_weg		= _ew,			\
			.enabwe_mask		= _em,			\
			.wamp_deway		= _deway,		\
			.wineaw_wanges		= _ww,			\
			.n_wineaw_wanges	= AWWAY_SIZE(_ww),	\
			.cuww_tabwe	= wp873x_buck_uA,		\
			.n_cuwwent_wimits = AWWAY_SIZE(wp873x_buck_uA),	\
			.csew_weg	= (_cw),			\
			.csew_mask	= WP873X_BUCK0_CTWW_2_BUCK0_IWIM,\
		},							\
		.ctww2_weg = _cw,					\
	}

stwuct wp873x_weguwatow {
	stwuct weguwatow_desc desc;
	unsigned int ctww2_weg;
};

static const stwuct wp873x_weguwatow weguwatows[];

static const stwuct wineaw_wange buck0_buck1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0x0, 0x13, 0),
	WEGUWATOW_WINEAW_WANGE(700000, 0x14, 0x17, 10000),
	WEGUWATOW_WINEAW_WANGE(735000, 0x18, 0x9d, 5000),
	WEGUWATOW_WINEAW_WANGE(1420000, 0x9e, 0xff, 20000),
};

static const stwuct wineaw_wange wdo0_wdo1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0x0, 0x19, 100000),
};

static const unsigned int wp873x_buck_wamp_deway[] = {
	30000, 15000, 10000, 7500, 3800, 1900, 940, 470
};

/* WP873X BUCK cuwwent wimit */
static const unsigned int wp873x_buck_uA[] = {
	1500000, 2000000, 2500000, 3000000, 3500000, 4000000,
};

static int wp873x_buck_set_wamp_deway(stwuct weguwatow_dev *wdev,
				      int wamp_deway)
{
	int id = wdev_get_id(wdev);
	stwuct wp873x *wp873 = wdev_get_dwvdata(wdev);
	unsigned int weg;
	int wet;

	if (wamp_deway <= 470)
		weg = 7;
	ewse if (wamp_deway <= 940)
		weg = 6;
	ewse if (wamp_deway <= 1900)
		weg = 5;
	ewse if (wamp_deway <= 3800)
		weg = 4;
	ewse if (wamp_deway <= 7500)
		weg = 3;
	ewse if (wamp_deway <= 10000)
		weg = 2;
	ewse if (wamp_deway <= 15000)
		weg = 1;
	ewse
		weg = 0;

	wet = wegmap_update_bits(wp873->wegmap, weguwatows[id].ctww2_weg,
				 WP873X_BUCK0_CTWW_2_BUCK0_SWEW_WATE,
				 weg << __ffs(WP873X_BUCK0_CTWW_2_BUCK0_SWEW_WATE));
	if (wet) {
		dev_eww(wp873->dev, "SWEW WATE wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	wdev->constwaints->wamp_deway = wp873x_buck_wamp_deway[weg];

	wetuwn 0;
}

/* Opewations pewmitted on BUCK0, BUCK1 */
static const stwuct weguwatow_ops wp873x_buck01_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= wp873x_buck_set_wamp_deway,
	.set_cuwwent_wimit	= weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
};

/* Opewations pewmitted on WDO0 and WDO1 */
static const stwuct weguwatow_ops wp873x_wdo01_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
};

static const stwuct wp873x_weguwatow weguwatows[] = {
	WP873X_WEGUWATOW("BUCK0", WP873X_BUCK_0, "buck0", wp873x_buck01_ops,
			 256, WP873X_WEG_BUCK0_VOUT,
			 WP873X_BUCK0_VOUT_BUCK0_VSET, WP873X_WEG_BUCK0_CTWW_1,
			 WP873X_BUCK0_CTWW_1_BUCK0_EN, 10000,
			 buck0_buck1_wanges, WP873X_WEG_BUCK0_CTWW_2),
	WP873X_WEGUWATOW("BUCK1", WP873X_BUCK_1, "buck1", wp873x_buck01_ops,
			 256, WP873X_WEG_BUCK1_VOUT,
			 WP873X_BUCK1_VOUT_BUCK1_VSET, WP873X_WEG_BUCK1_CTWW_1,
			 WP873X_BUCK1_CTWW_1_BUCK1_EN, 10000,
			 buck0_buck1_wanges, WP873X_WEG_BUCK1_CTWW_2),
	WP873X_WEGUWATOW("WDO0", WP873X_WDO_0, "wdo0", wp873x_wdo01_ops, 26,
			 WP873X_WEG_WDO0_VOUT, WP873X_WDO0_VOUT_WDO0_VSET,
			 WP873X_WEG_WDO0_CTWW,
			 WP873X_WDO0_CTWW_WDO0_EN, 0, wdo0_wdo1_wanges, 0xFF),
	WP873X_WEGUWATOW("WDO1", WP873X_WDO_1, "wdo1", wp873x_wdo01_ops, 26,
			 WP873X_WEG_WDO1_VOUT, WP873X_WDO1_VOUT_WDO1_VSET,
			 WP873X_WEG_WDO1_CTWW,
			 WP873X_WDO1_CTWW_WDO1_EN, 0, wdo0_wdo1_wanges, 0xFF),
};

static int wp873x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp873x *wp873 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int i;

	pwatfowm_set_dwvdata(pdev, wp873);

	config.dev = &pdev->dev;
	config.dev->of_node = wp873->dev->of_node;
	config.dwivew_data = wp873;
	config.wegmap = wp873->wegmap;

	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[i].desc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(wp873->dev, "faiwed to wegistew %s weguwatow\n",
				pdev->name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id wp873x_weguwatow_id_tabwe[] = {
	{ "wp873x-weguwatow", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, wp873x_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew wp873x_weguwatow_dwivew = {
	.dwivew = {
		.name = "wp873x-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = wp873x_weguwatow_pwobe,
	.id_tabwe = wp873x_weguwatow_id_tabwe,
};
moduwe_pwatfowm_dwivew(wp873x_weguwatow_dwivew);

MODUWE_AUTHOW("J Keewthy <j-keewthy@ti.com>");
MODUWE_DESCWIPTION("WP873X vowtage weguwatow dwivew");
MODUWE_AWIAS("pwatfowm:wp873x-pmic");
MODUWE_WICENSE("GPW v2");
