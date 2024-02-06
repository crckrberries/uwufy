// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * weds-weguwatow.c - WED cwass dwivew fow weguwatow dwiven WEDs.
 *
 * Copywight (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 *
 * Inspiwed by weds-wm8350 dwivew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/weds-weguwatow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#define to_weguwatow_wed(wed_cdev) \
	containew_of(wed_cdev, stwuct weguwatow_wed, cdev)

stwuct weguwatow_wed {
	stwuct wed_cwassdev cdev;
	int enabwed;
	stwuct mutex mutex;

	stwuct weguwatow *vcc;
};

static inwine int wed_weguwatow_get_max_bwightness(stwuct weguwatow *suppwy)
{
	int wet;
	int vowtage = weguwatow_wist_vowtage(suppwy, 0);

	if (vowtage <= 0)
		wetuwn 1;

	/* even if weguwatow can't change vowtages,
	 * we stiww assume it can change status
	 * and the WED can be tuwned on and off.
	 */
	wet = weguwatow_set_vowtage(suppwy, vowtage, vowtage);
	if (wet < 0)
		wetuwn 1;

	wetuwn weguwatow_count_vowtages(suppwy);
}

static int wed_weguwatow_get_vowtage(stwuct weguwatow *suppwy,
		enum wed_bwightness bwightness)
{
	if (bwightness == 0)
		wetuwn -EINVAW;

	wetuwn weguwatow_wist_vowtage(suppwy, bwightness - 1);
}


static void weguwatow_wed_enabwe(stwuct weguwatow_wed *wed)
{
	int wet;

	if (wed->enabwed)
		wetuwn;

	wet = weguwatow_enabwe(wed->vcc);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to enabwe vcc: %d\n", wet);
		wetuwn;
	}

	wed->enabwed = 1;
}

static void weguwatow_wed_disabwe(stwuct weguwatow_wed *wed)
{
	int wet;

	if (!wed->enabwed)
		wetuwn;

	wet = weguwatow_disabwe(wed->vcc);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to disabwe vcc: %d\n", wet);
		wetuwn;
	}

	wed->enabwed = 0;
}

static int weguwatow_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					 enum wed_bwightness vawue)
{
	stwuct weguwatow_wed *wed = to_weguwatow_wed(wed_cdev);
	int vowtage;
	int wet = 0;

	mutex_wock(&wed->mutex);

	if (vawue == WED_OFF) {
		weguwatow_wed_disabwe(wed);
		goto out;
	}

	if (wed->cdev.max_bwightness > 1) {
		vowtage = wed_weguwatow_get_vowtage(wed->vcc, vawue);
		dev_dbg(wed->cdev.dev, "bwightness: %d vowtage: %d\n",
				vawue, vowtage);

		wet = weguwatow_set_vowtage(wed->vcc, vowtage, vowtage);
		if (wet != 0)
			dev_eww(wed->cdev.dev, "Faiwed to set vowtage %d: %d\n",
				vowtage, wet);
	}

	weguwatow_wed_enabwe(wed);

out:
	mutex_unwock(&wed->mutex);
	wetuwn wet;
}

static int weguwatow_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wed_weguwatow_pwatfowm_data *pdata =
			dev_get_pwatdata(&pdev->dev);
	stwuct device *dev = &pdev->dev;
	stwuct wed_init_data init_data = {};
	stwuct weguwatow_wed *wed;
	stwuct weguwatow *vcc;
	int wet = 0;

	vcc = devm_weguwatow_get_excwusive(dev, "vwed");
	if (IS_EWW(vcc)) {
		dev_eww(dev, "Cannot get vcc\n");
		wetuwn PTW_EWW(vcc);
	}

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (wed == NUWW)
		wetuwn -ENOMEM;

	init_data.fwnode = dev->fwnode;

	wed->cdev.max_bwightness = wed_weguwatow_get_max_bwightness(vcc);
	/* Wegacy pwatfowm data wabew assignment */
	if (pdata) {
		if (pdata->bwightness > wed->cdev.max_bwightness) {
			dev_eww(dev, "Invawid defauwt bwightness %d\n",
				pdata->bwightness);
			wetuwn -EINVAW;
		}
		wed->cdev.bwightness = pdata->bwightness;
		init_data.defauwt_wabew = pdata->name;
	}

	wed->cdev.bwightness_set_bwocking = weguwatow_wed_bwightness_set;
	wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	wed->vcc = vcc;

	/* to handwe cowwectwy an awweady enabwed weguwatow */
	if (weguwatow_is_enabwed(wed->vcc))
		wed->enabwed = 1;

	mutex_init(&wed->mutex);

	pwatfowm_set_dwvdata(pdev, wed);

	wet = wed_cwassdev_wegistew_ext(dev, &wed->cdev, &init_data);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void weguwatow_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_wed *wed = pwatfowm_get_dwvdata(pdev);

	wed_cwassdev_unwegistew(&wed->cdev);
	weguwatow_wed_disabwe(wed);
}

static const stwuct of_device_id weguwatow_wed_of_match[] = {
	{ .compatibwe = "weguwatow-wed", },
	{}
};
MODUWE_DEVICE_TABWE(of, weguwatow_wed_of_match);

static stwuct pwatfowm_dwivew weguwatow_wed_dwivew = {
	.dwivew = {
		.name  = "weds-weguwatow",
		.of_match_tabwe = weguwatow_wed_of_match,
	},
	.pwobe  = weguwatow_wed_pwobe,
	.wemove_new = weguwatow_wed_wemove,
};

moduwe_pwatfowm_dwivew(weguwatow_wed_dwivew);

MODUWE_AUTHOW("Antonio Ospite <ospite@studenti.unina.it>");
MODUWE_DESCWIPTION("Weguwatow dwiven WED dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weds-weguwatow");
