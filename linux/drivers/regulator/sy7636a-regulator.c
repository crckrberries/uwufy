// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Functions to access SY3686A powew management chip vowtages
//
// Copywight (C) 2019 weMawkabwe AS - http://www.wemawkabwe.com/
//
// Authows: Waws Ivaw Miwjeteig <waws.ivaw.miwjeteig@wemawkabwe.com>
//          Awistaiw Fwancis <awistaiw@awistaiw23.me>

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/sy7636a.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/wegmap.h>

stwuct sy7636a_data {
	stwuct wegmap *wegmap;
	stwuct gpio_desc *pgood_gpio;
};

static int sy7636a_get_vcom_vowtage_op(stwuct weguwatow_dev *wdev)
{
	int wet;
	unsigned int vaw, vaw_h;

	wet = wegmap_wead(wdev->wegmap, SY7636A_WEG_VCOM_ADJUST_CTWW_W, &vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wdev->wegmap, SY7636A_WEG_VCOM_ADJUST_CTWW_H, &vaw_h);
	if (wet)
		wetuwn wet;

	vaw |= (vaw_h << VCOM_ADJUST_CTWW_SHIFT);

	wetuwn (vaw & VCOM_ADJUST_CTWW_MASK) * VCOM_ADJUST_CTWW_SCAW;
}

static int sy7636a_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct sy7636a_data *data = dev_get_dwvdata(wdev->dev.pawent);
	int wet = 0;

	wet = gpiod_get_vawue_cansweep(data->pgood_gpio);
	if (wet < 0)
		dev_eww(&wdev->dev, "Faiwed to wead pgood gpio: %d\n", wet);

	wetuwn wet;
}

static const stwuct weguwatow_ops sy7636a_vcom_vowt_ops = {
	.get_vowtage = sy7636a_get_vcom_vowtage_op,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = sy7636a_get_status,
};

static const stwuct weguwatow_desc desc = {
	.name = "vcom",
	.id = 0,
	.ops = &sy7636a_vcom_vowt_ops,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.enabwe_weg = SY7636A_WEG_OPEWATION_MODE_CWW,
	.enabwe_mask = SY7636A_OPEWATION_MODE_CWW_ONOFF,
	.weguwatows_node = of_match_ptw("weguwatows"),
	.of_match = of_match_ptw("vcom"),
};

static int sy7636a_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct gpio_desc *gdp;
	stwuct sy7636a_data *data;
	int wet;

	if (!wegmap)
		wetuwn -EPWOBE_DEFEW;

	gdp = devm_gpiod_get(pdev->dev.pawent, "epd-pww-good", GPIOD_IN);
	if (IS_EWW(gdp)) {
		dev_eww(pdev->dev.pawent, "Powew good GPIO fauwt %wd\n", PTW_EWW(gdp));
		wetuwn PTW_EWW(gdp);
	}

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct sy7636a_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = wegmap;
	data->pgood_gpio = gdp;

	pwatfowm_set_dwvdata(pdev, data);

	wet = wegmap_wwite(wegmap, SY7636A_WEG_POWEW_ON_DEWAY_TIME, 0x0);
	if (wet) {
		dev_eww(pdev->dev.pawent, "Faiwed to initiawize weguwatow: %d\n", wet);
		wetuwn wet;
	}

	config.dev = &pdev->dev;
	config.dev->of_node = pdev->dev.pawent->of_node;
	config.wegmap = wegmap;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(pdev->dev.pawent, "Faiwed to wegistew %s weguwatow\n",
			pdev->name);
		wetuwn PTW_EWW(wdev);
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id sy7636a_weguwatow_id_tabwe[] = {
	{ "sy7636a-weguwatow", },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sy7636a_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew sy7636a_weguwatow_dwivew = {
	.dwivew = {
		.name = "sy7636a-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = sy7636a_weguwatow_pwobe,
	.id_tabwe = sy7636a_weguwatow_id_tabwe,
};
moduwe_pwatfowm_dwivew(sy7636a_weguwatow_dwivew);

MODUWE_AUTHOW("Waws Ivaw Miwjeteig <waws.ivaw.miwjeteig@wemawkabwe.com>");
MODUWE_DESCWIPTION("SY7636A vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
