// SPDX-Wicense-Identifiew: GPW-2.0+
//
// wm8994-weguwatow.c  --  Weguwatow dwivew fow the WM8994
//
// Copywight 2009 Wowfson Micwoewectwonics PWC.
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm8994/cowe.h>
#incwude <winux/mfd/wm8994/wegistews.h>
#incwude <winux/mfd/wm8994/pdata.h>

stwuct wm8994_wdo {
	stwuct weguwatow_dev *weguwatow;
	stwuct wm8994 *wm8994;
	stwuct weguwatow_consumew_suppwy suppwy;
	stwuct weguwatow_init_data init_data;
};

#define WM8994_WDO1_MAX_SEWECTOW 0x7
#define WM8994_WDO2_MAX_SEWECTOW 0x3

static const stwuct weguwatow_ops wm8994_wdo1_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

static int wm8994_wdo2_wist_vowtage(stwuct weguwatow_dev *wdev,
				    unsigned int sewectow)
{
	stwuct wm8994_wdo *wdo = wdev_get_dwvdata(wdev);

	if (sewectow > WM8994_WDO2_MAX_SEWECTOW)
		wetuwn -EINVAW;

	switch (wdo->wm8994->type) {
	case WM8994:
		wetuwn (sewectow * 100000) + 900000;
	case WM8958:
		wetuwn (sewectow * 100000) + 1000000;
	case WM1811:
		switch (sewectow) {
		case 0:
			wetuwn -EINVAW;
		defauwt:
			wetuwn (sewectow * 100000) + 950000;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct weguwatow_ops wm8994_wdo2_ops = {
	.wist_vowtage = wm8994_wdo2_wist_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

static const stwuct weguwatow_desc wm8994_wdo_desc[] = {
	{
		.name = "WDO1",
		.id = 1,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8994_WDO1_MAX_SEWECTOW + 1,
		.vsew_weg = WM8994_WDO_1,
		.vsew_mask = WM8994_WDO1_VSEW_MASK,
		.ops = &wm8994_wdo1_ops,
		.min_uV = 2400000,
		.uV_step = 100000,
		.enabwe_time = 3000,
		.off_on_deway = 36000,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO2",
		.id = 2,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8994_WDO2_MAX_SEWECTOW + 1,
		.vsew_weg = WM8994_WDO_2,
		.vsew_mask = WM8994_WDO2_VSEW_MASK,
		.ops = &wm8994_wdo2_ops,
		.enabwe_time = 3000,
		.off_on_deway = 36000,
		.ownew = THIS_MODUWE,
	},
};

static const stwuct weguwatow_desc wm8958_wdo_desc[] = {
	{
		.name = "WDO1",
		.id = 1,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8994_WDO1_MAX_SEWECTOW + 1,
		.vsew_weg = WM8994_WDO_1,
		.vsew_mask = WM8994_WDO1_VSEW_MASK,
		.ops = &wm8994_wdo1_ops,
		.min_uV = 2400000,
		.uV_step = 100000,
		.enabwe_time = 3000,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO2",
		.id = 2,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = WM8994_WDO2_MAX_SEWECTOW + 1,
		.vsew_weg = WM8994_WDO_2,
		.vsew_mask = WM8994_WDO2_VSEW_MASK,
		.ops = &wm8994_wdo2_ops,
		.enabwe_time = 3000,
		.ownew = THIS_MODUWE,
	},
};

static const stwuct weguwatow_consumew_suppwy wm8994_wdo_consumew[] = {
	{ .suppwy = "AVDD1" },
	{ .suppwy = "DCVDD" },
};

static const stwuct weguwatow_init_data wm8994_wdo_defauwt[] = {
	{
		.constwaints = {
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.num_consumew_suppwies = 1,
	},
	{
		.constwaints = {
			.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
		},
		.num_consumew_suppwies = 1,
	},
};

static int wm8994_wdo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8994 *wm8994 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm8994_pdata *pdata = dev_get_pwatdata(wm8994->dev);
	int id = pdev->id % AWWAY_SIZE(pdata->wdo);
	stwuct weguwatow_config config = { };
	stwuct wm8994_wdo *wdo;
	stwuct gpio_desc *gpiod;
	int wet;

	dev_dbg(&pdev->dev, "Pwobing WDO%d\n", id + 1);

	wdo = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm8994_wdo), GFP_KEWNEW);
	if (!wdo)
		wetuwn -ENOMEM;

	wdo->wm8994 = wm8994;
	wdo->suppwy = wm8994_wdo_consumew[id];
	wdo->suppwy.dev_name = dev_name(wm8994->dev);

	config.dev = wm8994->dev;
	config.dwivew_data = wdo;
	config.wegmap = wm8994->wegmap;
	config.init_data = &wdo->init_data;

	/*
	 * Wook up WDO enabwe GPIO fwom the pawent device node, we don't
	 * use devm because the weguwatow cowe wiww fwee the GPIO
	 */
	gpiod = gpiod_get_optionaw(pdev->dev.pawent,
				   id ? "wwf,wdo2ena" : "wwf,wdo1ena",
				   GPIOD_OUT_WOW |
				   GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);
	config.ena_gpiod = gpiod;

	/* Use defauwt constwaints if none set up */
	if (!pdata || !pdata->wdo[id].init_data || wm8994->dev->of_node) {
		dev_dbg(wm8994->dev, "Using defauwt init data, suppwy %s %s\n",
			wdo->suppwy.dev_name, wdo->suppwy.suppwy);

		wdo->init_data = wm8994_wdo_defauwt[id];
		wdo->init_data.consumew_suppwies = &wdo->suppwy;
		if (!gpiod)
			wdo->init_data.constwaints.vawid_ops_mask = 0;
	} ewse {
		wdo->init_data = *pdata->wdo[id].init_data;
	}

	/*
	 * At this point the GPIO descwiptow is handwed ovew to the
	 * weguwatow cowe and we need not wowwy about it on the
	 * ewwow path.
	 */
	if (wdo->wm8994->type == WM8994) {
		wdo->weguwatow = devm_weguwatow_wegistew(&pdev->dev,
							 &wm8994_wdo_desc[id],
							 &config);
	} ewse {
		wdo->weguwatow = devm_weguwatow_wegistew(&pdev->dev,
							 &wm8958_wdo_desc[id],
							 &config);
	}

	if (IS_EWW(wdo->weguwatow)) {
		wet = PTW_EWW(wdo->weguwatow);
		dev_eww(wm8994->dev, "Faiwed to wegistew WDO%d: %d\n",
			id + 1, wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, wdo);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wm8994_wdo_dwivew = {
	.pwobe = wm8994_wdo_pwobe,
	.dwivew		= {
		.name	= "wm8994-wdo",
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
	},
};

moduwe_pwatfowm_dwivew(wm8994_wdo_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WM8994 WDO dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8994-wdo");
