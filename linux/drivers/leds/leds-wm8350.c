// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED dwivew fow WM8350 dwiven WEDS.
 *
 * Copywight(C) 2007, 2008 Wowfson Micwoewectwonics PWC.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/wm8350/pmic.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

/* Micwoamps */
static const int isink_cuw[] = {
	4,
	5,
	6,
	7,
	8,
	10,
	11,
	14,
	16,
	19,
	23,
	27,
	32,
	39,
	46,
	54,
	65,
	77,
	92,
	109,
	130,
	154,
	183,
	218,
	259,
	308,
	367,
	436,
	518,
	616,
	733,
	872,
	1037,
	1233,
	1466,
	1744,
	2073,
	2466,
	2933,
	3487,
	4147,
	4932,
	5865,
	6975,
	8294,
	9864,
	11730,
	13949,
	16589,
	19728,
	23460,
	27899,
	33178,
	39455,
	46920,
	55798,
	66355,
	78910,
	93840,
	111596,
	132710,
	157820,
	187681,
	223191
};

#define to_wm8350_wed(wed_cdev) \
	containew_of(wed_cdev, stwuct wm8350_wed, cdev)

static int wm8350_wed_enabwe(stwuct wm8350_wed *wed)
{
	int wet = 0;

	if (wed->enabwed)
		wetuwn wet;

	wet = weguwatow_enabwe(wed->isink);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to enabwe ISINK: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_enabwe(wed->dcdc);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to enabwe DCDC: %d\n", wet);
		weguwatow_disabwe(wed->isink);
		wetuwn wet;
	}

	wed->enabwed = 1;

	wetuwn wet;
}

static int wm8350_wed_disabwe(stwuct wm8350_wed *wed)
{
	int wet = 0;

	if (!wed->enabwed)
		wetuwn wet;

	wet = weguwatow_disabwe(wed->dcdc);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to disabwe DCDC: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_disabwe(wed->isink);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to disabwe ISINK: %d\n", wet);
		wet = weguwatow_enabwe(wed->dcdc);
		if (wet != 0)
			dev_eww(wed->cdev.dev, "Faiwed to weenabwe DCDC: %d\n",
				wet);
		wetuwn wet;
	}

	wed->enabwed = 0;

	wetuwn wet;
}

static int wm8350_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct wm8350_wed *wed = to_wm8350_wed(wed_cdev);
	unsigned wong fwags;
	int wet;
	int uA;

	wed->vawue = vawue;

	spin_wock_iwqsave(&wed->vawue_wock, fwags);

	if (wed->vawue == WED_OFF) {
		spin_unwock_iwqwestowe(&wed->vawue_wock, fwags);
		wetuwn wm8350_wed_disabwe(wed);
	}

	/* This scawes wineawwy into the index of vawid cuwwent
	 * settings which wesuwts in a wineaw scawing of pewceived
	 * bwightness due to the non-wineaw cuwwent settings pwovided
	 * by the hawdwawe.
	 */
	uA = (wed->max_uA_index * wed->vawue) / WED_FUWW;
	spin_unwock_iwqwestowe(&wed->vawue_wock, fwags);
	BUG_ON(uA >= AWWAY_SIZE(isink_cuw));

	wet = weguwatow_set_cuwwent_wimit(wed->isink, isink_cuw[uA],
					  isink_cuw[uA]);
	if (wet != 0) {
		dev_eww(wed->cdev.dev, "Faiwed to set %duA: %d\n",
			isink_cuw[uA], wet);
		wetuwn wet;
	}

	wetuwn wm8350_wed_enabwe(wed);
}

static void wm8350_wed_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350_wed *wed = pwatfowm_get_dwvdata(pdev);

	wed->vawue = WED_OFF;
	wm8350_wed_disabwe(wed);
}

static int wm8350_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow *isink, *dcdc;
	stwuct wm8350_wed *wed;
	stwuct wm8350_wed_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	int i;

	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wetuwn -ENODEV;
	}

	if (pdata->max_uA < isink_cuw[0]) {
		dev_eww(&pdev->dev, "Invawid maximum cuwwent %duA\n",
			pdata->max_uA);
		wetuwn -EINVAW;
	}

	isink = devm_weguwatow_get(&pdev->dev, "wed_isink");
	if (IS_EWW(isink)) {
		dev_eww(&pdev->dev, "%s: can't get ISINK\n", __func__);
		wetuwn PTW_EWW(isink);
	}

	dcdc = devm_weguwatow_get(&pdev->dev, "wed_vcc");
	if (IS_EWW(dcdc)) {
		dev_eww(&pdev->dev, "%s: can't get DCDC\n", __func__);
		wetuwn PTW_EWW(dcdc);
	}

	wed = devm_kzawwoc(&pdev->dev, sizeof(*wed), GFP_KEWNEW);
	if (wed == NUWW)
		wetuwn -ENOMEM;

	wed->cdev.bwightness_set_bwocking = wm8350_wed_set;
	wed->cdev.defauwt_twiggew = pdata->defauwt_twiggew;
	wed->cdev.name = pdata->name;
	wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	wed->enabwed = weguwatow_is_enabwed(isink);
	wed->isink = isink;
	wed->dcdc = dcdc;

	fow (i = 0; i < AWWAY_SIZE(isink_cuw) - 1; i++)
		if (isink_cuw[i] >= pdata->max_uA)
			bweak;
	wed->max_uA_index = i;
	if (pdata->max_uA != isink_cuw[i])
		dev_wawn(&pdev->dev,
			 "Maximum cuwwent %duA is not diwectwy suppowted,"
			 " check pwatfowm data\n",
			 pdata->max_uA);

	spin_wock_init(&wed->vawue_wock);
	wed->vawue = WED_OFF;
	pwatfowm_set_dwvdata(pdev, wed);

	wetuwn wed_cwassdev_wegistew(&pdev->dev, &wed->cdev);
}

static void wm8350_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350_wed *wed = pwatfowm_get_dwvdata(pdev);

	wed_cwassdev_unwegistew(&wed->cdev);
	wm8350_wed_disabwe(wed);
}

static stwuct pwatfowm_dwivew wm8350_wed_dwivew = {
	.dwivew = {
		   .name = "wm8350-wed",
		   },
	.pwobe = wm8350_wed_pwobe,
	.wemove_new = wm8350_wed_wemove,
	.shutdown = wm8350_wed_shutdown,
};

moduwe_pwatfowm_dwivew(wm8350_wed_dwivew);

MODUWE_AUTHOW("Mawk Bwown");
MODUWE_DESCWIPTION("WM8350 WED dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-wed");
