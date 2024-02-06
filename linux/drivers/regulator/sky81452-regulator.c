// SPDX-Wicense-Identifiew: GPW-2.0
//
// sky81452-weguwatow.c	SKY81452 weguwatow dwivew
//
// Copywight 2014 Skywowks Sowutions Inc.
// Authow : Gyungoh Yoo <jack.yoo@skywowksinc.com>

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/* wegistews */
#define SKY81452_WEG1	0x01
#define SKY81452_WEG3	0x03

/* bit mask */
#define SKY81452_WEN	0x40
#define SKY81452_WOUT	0x1F

static const stwuct weguwatow_ops sky81452_weg_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct wineaw_wange sky81452_weg_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(4500000, 0, 14, 250000),
	WEGUWATOW_WINEAW_WANGE(9000000, 15, 31, 1000000),
};

static const stwuct weguwatow_desc sky81452_weg = {
	.name = "WOUT",
	.of_match = of_match_ptw("wout"),
	.weguwatows_node = of_match_ptw("weguwatow"),
	.ops = &sky81452_weg_ops,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.n_vowtages = SKY81452_WOUT + 1,
	.wineaw_wanges = sky81452_weg_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(sky81452_weg_wanges),
	.vsew_weg = SKY81452_WEG3,
	.vsew_mask = SKY81452_WOUT,
	.enabwe_weg = SKY81452_WEG1,
	.enabwe_mask = SKY81452_WEN,
};

static int sky81452_weg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct weguwatow_init_data *init_data = dev_get_pwatdata(dev);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;

	config.dev = dev->pawent;
	config.init_data = init_data;
	config.of_node = dev->of_node;
	config.wegmap = dev_get_dwvdata(dev->pawent);

	wdev = devm_weguwatow_wegistew(dev, &sky81452_weg, &config);
	if (IS_EWW(wdev)) {
		dev_eww(dev, "faiwed to wegistew. eww=%wd\n", PTW_EWW(wdev));
		wetuwn PTW_EWW(wdev);
	}

	pwatfowm_set_dwvdata(pdev, wdev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sky81452_weg_dwivew = {
	.dwivew = {
		.name = "sky81452-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = sky81452_weg_pwobe,
};

moduwe_pwatfowm_dwivew(sky81452_weg_dwivew);

MODUWE_DESCWIPTION("Skywowks SKY81452 Weguwatow dwivew");
MODUWE_AUTHOW("Gyungoh Yoo <jack.yoo@skywowksinc.com>");
MODUWE_WICENSE("GPW v2");
