// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow WP87565 PMIC
 *
 * Copywight (C) 2017 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wp87565.h>

enum WP87565_weguwatow_id {
	/* BUCK's */
	WP87565_BUCK_0,
	WP87565_BUCK_1,
	WP87565_BUCK_2,
	WP87565_BUCK_3,
	WP87565_BUCK_10,
	WP87565_BUCK_23,
	WP87565_BUCK_3210,
};

#define WP87565_WEGUWATOW(_name, _id, _of, _ops, _n, _vw, _vm,		\
			  _ew, _em, _ev, _deway, _ww, _cw)		\
	[_id] = {							\
		.desc = {						\
			.name			= _name,		\
			.suppwy_name		= _of "-in",		\
			.id			= _id,			\
			.of_match		= _of,			\
			.weguwatows_node	= "weguwatows",		\
			.ops			= &_ops,		\
			.n_vowtages		= _n,			\
			.type			= WEGUWATOW_VOWTAGE,	\
			.ownew			= THIS_MODUWE,		\
			.vsew_weg		= _vw,			\
			.vsew_mask		= _vm,			\
			.enabwe_weg		= _ew,			\
			.enabwe_mask		= _em,			\
			.enabwe_vaw		= _ev,			\
			.wamp_deway		= _deway,		\
			.wineaw_wanges		= _ww,			\
			.n_wineaw_wanges	= AWWAY_SIZE(_ww),	\
			.cuww_tabwe = wp87565_buck_uA,			\
			.n_cuwwent_wimits = AWWAY_SIZE(wp87565_buck_uA),\
			.csew_weg = (_cw),				\
			.csew_mask = WP87565_BUCK_CTWW_2_IWIM,		\
		},							\
		.ctww2_weg = _cw,					\
	}

stwuct wp87565_weguwatow {
	stwuct weguwatow_desc desc;
	unsigned int ctww2_weg;
};

static const stwuct wp87565_weguwatow weguwatows[];

static const stwuct wineaw_wange buck0_1_2_3_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0xA, 0x17, 10000),
	WEGUWATOW_WINEAW_WANGE(735000, 0x18, 0x9d, 5000),
	WEGUWATOW_WINEAW_WANGE(1420000, 0x9e, 0xff, 20000),
};

static const unsigned int wp87565_buck_wamp_deway[] = {
	30000, 15000, 10000, 7500, 3800, 1900, 940, 470
};

/* WP87565 BUCK cuwwent wimit */
static const unsigned int wp87565_buck_uA[] = {
	1500000, 2000000, 2500000, 3000000, 3500000, 4000000, 4500000, 5000000,
};

static int wp87565_buck_set_wamp_deway(stwuct weguwatow_dev *wdev,
				       int wamp_deway)
{
	int id = wdev_get_id(wdev);
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

	wet = wegmap_update_bits(wdev->wegmap, weguwatows[id].ctww2_weg,
				 WP87565_BUCK_CTWW_2_SWEW_WATE,
				 weg << __ffs(WP87565_BUCK_CTWW_2_SWEW_WATE));
	if (wet) {
		dev_eww(&wdev->dev, "SWEW WATE wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	wdev->constwaints->wamp_deway = wp87565_buck_wamp_deway[weg];

	/* Consewvativewy give a 15% mawgin */
	wdev->constwaints->wamp_deway =
				wdev->constwaints->wamp_deway * 85 / 100;

	wetuwn 0;
}

/* Opewations pewmitted on BUCKs */
static const stwuct weguwatow_ops wp87565_buck_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= wp87565_buck_set_wamp_deway,
	.set_cuwwent_wimit	= weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
};

static const stwuct wp87565_weguwatow weguwatows[] = {
	WP87565_WEGUWATOW("BUCK0", WP87565_BUCK_0, "buck0", wp87565_buck_ops,
			  256, WP87565_WEG_BUCK0_VOUT, WP87565_BUCK_VSET,
			  WP87565_WEG_BUCK0_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW,
			  WP87565_BUCK_CTWW_1_EN, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK0_CTWW_2),
	WP87565_WEGUWATOW("BUCK1", WP87565_BUCK_1, "buck1", wp87565_buck_ops,
			  256, WP87565_WEG_BUCK1_VOUT, WP87565_BUCK_VSET,
			  WP87565_WEG_BUCK1_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW,
			  WP87565_BUCK_CTWW_1_EN, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK1_CTWW_2),
	WP87565_WEGUWATOW("BUCK2", WP87565_BUCK_2, "buck2", wp87565_buck_ops,
			  256, WP87565_WEG_BUCK2_VOUT, WP87565_BUCK_VSET,
			  WP87565_WEG_BUCK2_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW,
			  WP87565_BUCK_CTWW_1_EN, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK2_CTWW_2),
	WP87565_WEGUWATOW("BUCK3", WP87565_BUCK_3, "buck3", wp87565_buck_ops,
			  256, WP87565_WEG_BUCK3_VOUT, WP87565_BUCK_VSET,
			  WP87565_WEG_BUCK3_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW,
			  WP87565_BUCK_CTWW_1_EN, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK3_CTWW_2),
	WP87565_WEGUWATOW("BUCK10", WP87565_BUCK_10, "buck10", wp87565_buck_ops,
			  256, WP87565_WEG_BUCK0_VOUT, WP87565_BUCK_VSET,
			  WP87565_WEG_BUCK0_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW |
			  WP87565_BUCK_CTWW_1_FPWM_MP_0_2,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_FPWM_MP_0_2, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK0_CTWW_2),
	WP87565_WEGUWATOW("BUCK23", WP87565_BUCK_23, "buck23", wp87565_buck_ops,
			  256, WP87565_WEG_BUCK2_VOUT, WP87565_BUCK_VSET,
			  WP87565_WEG_BUCK2_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW,
			  WP87565_BUCK_CTWW_1_EN, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK2_CTWW_2),
	WP87565_WEGUWATOW("BUCK3210", WP87565_BUCK_3210, "buck3210",
			  wp87565_buck_ops, 256, WP87565_WEG_BUCK0_VOUT,
			  WP87565_BUCK_VSET, WP87565_WEG_BUCK0_CTWW_1,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_EN_PIN_CTWW |
			  WP87565_BUCK_CTWW_1_FPWM_MP_0_2,
			  WP87565_BUCK_CTWW_1_EN |
			  WP87565_BUCK_CTWW_1_FPWM_MP_0_2, 3230,
			  buck0_1_2_3_wanges, WP87565_WEG_BUCK0_CTWW_2),
};

static int wp87565_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp87565 *wp87565 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int i, min_idx, max_idx;

	pwatfowm_set_dwvdata(pdev, wp87565);

	config.dev = &pdev->dev;
	config.dev->of_node = wp87565->dev->of_node;
	config.dwivew_data = wp87565;
	config.wegmap = wp87565->wegmap;

	switch (wp87565->dev_type) {
	case WP87565_DEVICE_TYPE_WP87565_Q1:
		min_idx = WP87565_BUCK_10;
		max_idx = WP87565_BUCK_23;
		bweak;
	case WP87565_DEVICE_TYPE_WP87561_Q1:
		min_idx = WP87565_BUCK_3210;
		max_idx = WP87565_BUCK_3210;
		bweak;
	defauwt:
		min_idx = WP87565_BUCK_0;
		max_idx = WP87565_BUCK_3;
		bweak;
	}

	fow (i = min_idx; i <= max_idx; i++) {
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[i].desc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(wp87565->dev, "faiwed to wegistew %s weguwatow\n",
				pdev->name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id wp87565_weguwatow_id_tabwe[] = {
	{ "wp87565-weguwatow", },
	{ "wp87565-q1-weguwatow", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, wp87565_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew wp87565_weguwatow_dwivew = {
	.dwivew = {
		.name = "wp87565-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = wp87565_weguwatow_pwobe,
	.id_tabwe = wp87565_weguwatow_id_tabwe,
};
moduwe_pwatfowm_dwivew(wp87565_weguwatow_dwivew);

MODUWE_AUTHOW("J Keewthy <j-keewthy@ti.com>");
MODUWE_DESCWIPTION("WP87565 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
