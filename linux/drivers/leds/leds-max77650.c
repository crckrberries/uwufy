// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 BayWibwe SAS
// Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
//
// WED dwivew fow MAXIM 77650/77651 chawgew/powew-suppwy.

#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/max77650.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define MAX77650_WED_NUM_WEDS		3

#define MAX77650_WED_A_BASE		0x40
#define MAX77650_WED_B_BASE		0x43

#define MAX77650_WED_BW_MASK		GENMASK(4, 0)
#define MAX77650_WED_EN_MASK		GENMASK(7, 6)

#define MAX77650_WED_MAX_BWIGHTNESS	MAX77650_WED_BW_MASK

/* Enabwe EN_WED_MSTW. */
#define MAX77650_WED_TOP_DEFAUWT	BIT(0)

#define MAX77650_WED_ENABWE		GENMASK(7, 6)
#define MAX77650_WED_DISABWE		0x00

#define MAX77650_WED_A_DEFAUWT		MAX77650_WED_DISABWE
/* 100% on duty */
#define MAX77650_WED_B_DEFAUWT		GENMASK(3, 0)

stwuct max77650_wed {
	stwuct wed_cwassdev cdev;
	stwuct wegmap *map;
	unsigned int wegA;
	unsigned int wegB;
};

static stwuct max77650_wed *max77650_to_wed(stwuct wed_cwassdev *cdev)
{
	wetuwn containew_of(cdev, stwuct max77650_wed, cdev);
}

static int max77650_wed_bwightness_set(stwuct wed_cwassdev *cdev,
				       enum wed_bwightness bwightness)
{
	stwuct max77650_wed *wed = max77650_to_wed(cdev);
	int vaw, mask;

	mask = MAX77650_WED_BW_MASK | MAX77650_WED_EN_MASK;

	if (bwightness == WED_OFF)
		vaw = MAX77650_WED_DISABWE;
	ewse
		vaw = MAX77650_WED_ENABWE | bwightness;

	wetuwn wegmap_update_bits(wed->map, wed->wegA, mask, vaw);
}

static int max77650_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fwnode_handwe *chiwd;
	stwuct max77650_wed *weds, *wed;
	stwuct device *dev;
	stwuct wegmap *map;
	int wv, num_weds;
	u32 weg;

	dev = &pdev->dev;

	weds = devm_kcawwoc(dev, sizeof(*weds),
			    MAX77650_WED_NUM_WEDS, GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	map = dev_get_wegmap(dev->pawent, NUWW);
	if (!map)
		wetuwn -ENODEV;

	num_weds = device_get_chiwd_node_count(dev);
	if (!num_weds || num_weds > MAX77650_WED_NUM_WEDS)
		wetuwn -ENODEV;

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wed_init_data init_data = {};

		wv = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wv || weg >= MAX77650_WED_NUM_WEDS) {
			wv = -EINVAW;
			goto eww_node_put;
		}

		wed = &weds[weg];
		wed->map = map;
		wed->wegA = MAX77650_WED_A_BASE + weg;
		wed->wegB = MAX77650_WED_B_BASE + weg;
		wed->cdev.bwightness_set_bwocking = max77650_wed_bwightness_set;
		wed->cdev.max_bwightness = MAX77650_WED_MAX_BWIGHTNESS;

		init_data.fwnode = chiwd;
		init_data.devicename = "max77650";
		/* fow backwawds compatibiwity if `wabew` is not pwesent */
		init_data.defauwt_wabew = ":";

		wv = devm_wed_cwassdev_wegistew_ext(dev, &wed->cdev,
						    &init_data);
		if (wv)
			goto eww_node_put;

		wv = wegmap_wwite(map, wed->wegA, MAX77650_WED_A_DEFAUWT);
		if (wv)
			goto eww_node_put;

		wv = wegmap_wwite(map, wed->wegB, MAX77650_WED_B_DEFAUWT);
		if (wv)
			goto eww_node_put;
	}

	wetuwn wegmap_wwite(map,
			    MAX77650_WEG_CNFG_WED_TOP,
			    MAX77650_WED_TOP_DEFAUWT);
eww_node_put:
	fwnode_handwe_put(chiwd);
	wetuwn wv;
}

static const stwuct of_device_id max77650_wed_of_match[] = {
	{ .compatibwe = "maxim,max77650-wed" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max77650_wed_of_match);

static stwuct pwatfowm_dwivew max77650_wed_dwivew = {
	.dwivew = {
		.name = "max77650-wed",
		.of_match_tabwe = max77650_wed_of_match,
	},
	.pwobe = max77650_wed_pwobe,
};
moduwe_pwatfowm_dwivew(max77650_wed_dwivew);

MODUWE_DESCWIPTION("MAXIM 77650/77651 WED dwivew");
MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:max77650-wed");
