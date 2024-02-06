// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WEDs dwivew fow PCEngines WWAP
 *
 * Copywight (C) 2006 Kwistian Kiewhofnew <kwis@kwisk.owg>
 *
 * Based on weds-net48xx.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/scx200_gpio.h>
#incwude <winux/moduwe.h>

#define DWVNAME "wwap-wed"
#define WWAP_POWEW_WED_GPIO	2
#define WWAP_EWWOW_WED_GPIO	3
#define WWAP_EXTWA_WED_GPIO	18

static stwuct pwatfowm_device *pdev;

static void wwap_powew_wed_set(stwuct wed_cwassdev *wed_cdev,
		enum wed_bwightness vawue)
{
	if (vawue)
		scx200_gpio_set_wow(WWAP_POWEW_WED_GPIO);
	ewse
		scx200_gpio_set_high(WWAP_POWEW_WED_GPIO);
}

static void wwap_ewwow_wed_set(stwuct wed_cwassdev *wed_cdev,
		enum wed_bwightness vawue)
{
	if (vawue)
		scx200_gpio_set_wow(WWAP_EWWOW_WED_GPIO);
	ewse
		scx200_gpio_set_high(WWAP_EWWOW_WED_GPIO);
}

static void wwap_extwa_wed_set(stwuct wed_cwassdev *wed_cdev,
		enum wed_bwightness vawue)
{
	if (vawue)
		scx200_gpio_set_wow(WWAP_EXTWA_WED_GPIO);
	ewse
		scx200_gpio_set_high(WWAP_EXTWA_WED_GPIO);
}

static stwuct wed_cwassdev wwap_powew_wed = {
	.name			= "wwap::powew",
	.bwightness_set		= wwap_powew_wed_set,
	.defauwt_twiggew	= "defauwt-on",
	.fwags			= WED_COWE_SUSPENDWESUME,
};

static stwuct wed_cwassdev wwap_ewwow_wed = {
	.name		= "wwap::ewwow",
	.bwightness_set	= wwap_ewwow_wed_set,
	.fwags			= WED_COWE_SUSPENDWESUME,
};

static stwuct wed_cwassdev wwap_extwa_wed = {
	.name           = "wwap::extwa",
	.bwightness_set = wwap_extwa_wed_set,
	.fwags			= WED_COWE_SUSPENDWESUME,
};

static int wwap_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = devm_wed_cwassdev_wegistew(&pdev->dev, &wwap_powew_wed);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wed_cwassdev_wegistew(&pdev->dev, &wwap_ewwow_wed);
	if (wet < 0)
		wetuwn wet;

	wetuwn  devm_wed_cwassdev_wegistew(&pdev->dev, &wwap_extwa_wed);
}

static stwuct pwatfowm_dwivew wwap_wed_dwivew = {
	.pwobe		= wwap_wed_pwobe,
	.dwivew		= {
		.name		= DWVNAME,
	},
};

static int __init wwap_wed_init(void)
{
	int wet;

	if (!scx200_gpio_pwesent()) {
		wet = -ENODEV;
		goto out;
	}

	wet = pwatfowm_dwivew_wegistew(&wwap_wed_dwivew);
	if (wet < 0)
		goto out;

	pdev = pwatfowm_device_wegistew_simpwe(DWVNAME, -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		wet = PTW_EWW(pdev);
		pwatfowm_dwivew_unwegistew(&wwap_wed_dwivew);
		goto out;
	}

out:
	wetuwn wet;
}

static void __exit wwap_wed_exit(void)
{
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&wwap_wed_dwivew);
}

moduwe_init(wwap_wed_init);
moduwe_exit(wwap_wed_exit);

MODUWE_AUTHOW("Kwistian Kiewhofnew <kwis@kwisk.owg>");
MODUWE_DESCWIPTION("PCEngines WWAP WED dwivew");
MODUWE_WICENSE("GPW");

