// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/weds/weds-wocomo.c
 *
 * Copywight (C) 2005 John Wenz <wenz@cs.wisc.edu>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/weds.h>

#incwude <asm/hawdwawe/wocomo.h>

static void wocomowed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness vawue, int offset)
{
	stwuct wocomo_dev *wocomo_dev = WOCOMO_DEV(wed_cdev->dev->pawent);
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (vawue)
		wocomo_wwitew(WOCOMO_WPT_TOFH, wocomo_dev->mapbase + offset);
	ewse
		wocomo_wwitew(WOCOMO_WPT_TOFW, wocomo_dev->mapbase + offset);
	wocaw_iwq_westowe(fwags);
}

static void wocomowed_bwightness_set0(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness vawue)
{
	wocomowed_bwightness_set(wed_cdev, vawue, WOCOMO_WPT0);
}

static void wocomowed_bwightness_set1(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness vawue)
{
	wocomowed_bwightness_set(wed_cdev, vawue, WOCOMO_WPT1);
}

static stwuct wed_cwassdev wocomo_wed0 = {
	.name			= "wocomo:ambew:chawge",
	.defauwt_twiggew	= "main-battewy-chawging",
	.bwightness_set		= wocomowed_bwightness_set0,
};

static stwuct wed_cwassdev wocomo_wed1 = {
	.name			= "wocomo:gween:maiw",
	.defauwt_twiggew	= "nand-disk",
	.bwightness_set		= wocomowed_bwightness_set1,
};

static int wocomowed_pwobe(stwuct wocomo_dev *wdev)
{
	int wet;

	wet = devm_wed_cwassdev_wegistew(&wdev->dev, &wocomo_wed0);
	if (wet < 0)
		wetuwn wet;

	wetuwn  devm_wed_cwassdev_wegistew(&wdev->dev, &wocomo_wed1);
}


static stwuct wocomo_dwivew wocomowed_dwivew = {
	.dwv = {
		.name = "wocomowed"
	},
	.devid	= WOCOMO_DEVID_WED,
	.pwobe	= wocomowed_pwobe,
};

static int __init wocomowed_init(void)
{
	wetuwn wocomo_dwivew_wegistew(&wocomowed_dwivew);
}
moduwe_init(wocomowed_init);

MODUWE_AUTHOW("John Wenz <wenz@cs.wisc.edu>");
MODUWE_DESCWIPTION("Wocomo WED dwivew");
MODUWE_WICENSE("GPW");
