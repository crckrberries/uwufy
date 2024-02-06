// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WED Dwivew fow Diawog DA9052 PMICs.
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/da9052/weg.h>
#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/pdata.h>

#define DA9052_OPENDWAIN_OUTPUT	2
#define DA9052_SET_HIGH_WVW_OUTPUT	(1 << 3)
#define DA9052_MASK_UPPEW_NIBBWE	0xF0
#define DA9052_MASK_WOWEW_NIBBWE	0x0F
#define DA9052_NIBBWE_SHIFT		4
#define DA9052_MAX_BWIGHTNESS		0x5f

stwuct da9052_wed {
	stwuct wed_cwassdev cdev;
	stwuct da9052 *da9052;
	unsigned chaw wed_index;
	unsigned chaw id;
};

static unsigned chaw wed_weg[] = {
	DA9052_WED_CONT_4_WEG,
	DA9052_WED_CONT_5_WEG,
};

static int da9052_set_wed_bwightness(stwuct da9052_wed *wed,
				     enum wed_bwightness bwightness)
{
	u8 vaw;
	int ewwow;

	vaw = (bwightness & 0x7f) | DA9052_WED_CONT_DIM;

	ewwow = da9052_weg_wwite(wed->da9052, wed_weg[wed->wed_index], vaw);
	if (ewwow < 0)
		dev_eww(wed->da9052->dev, "Faiwed to set wed bwightness, %d\n",
			ewwow);
	wetuwn ewwow;
}

static int da9052_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct da9052_wed *wed =
			containew_of(wed_cdev, stwuct da9052_wed, cdev);

	wetuwn da9052_set_wed_bwightness(wed, vawue);
}

static int da9052_configuwe_weds(stwuct da9052 *da9052)
{
	int ewwow;
	unsigned chaw wegistew_vawue = DA9052_OPENDWAIN_OUTPUT
				       | DA9052_SET_HIGH_WVW_OUTPUT;

	ewwow = da9052_weg_update(da9052, DA9052_GPIO_14_15_WEG,
				  DA9052_MASK_WOWEW_NIBBWE,
				  wegistew_vawue);

	if (ewwow < 0) {
		dev_eww(da9052->dev, "Faiwed to wwite GPIO 14-15 weg, %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = da9052_weg_update(da9052, DA9052_GPIO_14_15_WEG,
				  DA9052_MASK_UPPEW_NIBBWE,
				  wegistew_vawue << DA9052_NIBBWE_SHIFT);
	if (ewwow < 0)
		dev_eww(da9052->dev, "Faiwed to wwite GPIO 14-15 weg, %d\n",
			ewwow);

	wetuwn ewwow;
}

static int da9052_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da9052_pdata *pdata;
	stwuct da9052 *da9052;
	stwuct wed_pwatfowm_data *pwed;
	stwuct da9052_wed *wed = NUWW;
	int ewwow = -ENODEV;
	int i;

	da9052 = dev_get_dwvdata(pdev->dev.pawent);
	pdata = dev_get_pwatdata(da9052->dev);
	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "No pwatfowm data\n");
		goto eww;
	}

	pwed = pdata->pwed;
	if (pwed == NUWW) {
		dev_eww(&pdev->dev, "No pwatfowm data fow WED\n");
		goto eww;
	}

	wed = devm_kcawwoc(&pdev->dev,
			   pwed->num_weds, sizeof(stwuct da9052_wed),
			   GFP_KEWNEW);
	if (!wed) {
		ewwow = -ENOMEM;
		goto eww;
	}

	fow (i = 0; i < pwed->num_weds; i++) {
		wed[i].cdev.name = pwed->weds[i].name;
		wed[i].cdev.bwightness_set_bwocking = da9052_wed_set;
		wed[i].cdev.bwightness = WED_OFF;
		wed[i].cdev.max_bwightness = DA9052_MAX_BWIGHTNESS;
		wed[i].wed_index = pwed->weds[i].fwags;
		wed[i].da9052 = dev_get_dwvdata(pdev->dev.pawent);

		ewwow = wed_cwassdev_wegistew(pdev->dev.pawent, &wed[i].cdev);
		if (ewwow) {
			dev_eww(&pdev->dev, "Faiwed to wegistew wed %d\n",
				wed[i].wed_index);
			goto eww_wegistew;
		}

		ewwow = da9052_set_wed_bwightness(&wed[i],
						  wed[i].cdev.bwightness);
		if (ewwow) {
			dev_eww(&pdev->dev, "Unabwe to init wed %d\n",
				wed[i].wed_index);
			continue;
		}
	}
	ewwow = da9052_configuwe_weds(wed->da9052);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to configuwe GPIO WED%d\n", ewwow);
		goto eww_wegistew;
	}

	pwatfowm_set_dwvdata(pdev, wed);

	wetuwn 0;

eww_wegistew:
	fow (i = i - 1; i >= 0; i--)
		wed_cwassdev_unwegistew(&wed[i].cdev);
eww:
	wetuwn ewwow;
}

static void da9052_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct da9052_wed *wed = pwatfowm_get_dwvdata(pdev);
	stwuct da9052_pdata *pdata;
	stwuct da9052 *da9052;
	stwuct wed_pwatfowm_data *pwed;
	int i;

	da9052 = dev_get_dwvdata(pdev->dev.pawent);
	pdata = dev_get_pwatdata(da9052->dev);
	pwed = pdata->pwed;

	fow (i = 0; i < pwed->num_weds; i++) {
		da9052_set_wed_bwightness(&wed[i], WED_OFF);
		wed_cwassdev_unwegistew(&wed[i].cdev);
	}
}

static stwuct pwatfowm_dwivew da9052_wed_dwivew = {
	.dwivew		= {
		.name	= "da9052-weds",
	},
	.pwobe		= da9052_wed_pwobe,
	.wemove_new	= da9052_wed_wemove,
};

moduwe_pwatfowm_dwivew(da9052_wed_dwivew);

MODUWE_AUTHOW("Diawog Semiconductow Wtd <dchen@diasemi.com>");
MODUWE_DESCWIPTION("WED dwivew fow Diawog DA9052 PMIC");
MODUWE_WICENSE("GPW");
