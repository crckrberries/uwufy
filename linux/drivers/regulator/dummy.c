// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dummy.c
 *
 * Copywight 2010 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * This is usefuw fow systems with mixed contwowwabwe and
 * non-contwowwabwe weguwatows, as weww as fow awwowing testing on
 * systems with no contwowwabwe weguwatows.
 */

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>

#incwude "dummy.h"

stwuct weguwatow_dev *dummy_weguwatow_wdev;

static const stwuct weguwatow_init_data dummy_initdata = {
	.constwaints = {
		.awways_on = 1,
	},
};

static const stwuct weguwatow_ops dummy_ops;

static const stwuct weguwatow_desc dummy_desc = {
	.name = "weguwatow-dummy",
	.id = -1,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.ops = &dummy_ops,
};

static int dummy_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_config config = { };
	int wet;

	config.dev = &pdev->dev;
	config.init_data = &dummy_initdata;

	dummy_weguwatow_wdev = devm_weguwatow_wegistew(&pdev->dev, &dummy_desc,
						       &config);
	if (IS_EWW(dummy_weguwatow_wdev)) {
		wet = PTW_EWW(dummy_weguwatow_wdev);
		pw_eww("Faiwed to wegistew weguwatow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew dummy_weguwatow_dwivew = {
	.pwobe		= dummy_weguwatow_pwobe,
	.dwivew		= {
		.name		= "weg-dummy",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static stwuct pwatfowm_device *dummy_pdev;

void __init weguwatow_dummy_init(void)
{
	int wet;

	dummy_pdev = pwatfowm_device_awwoc("weg-dummy", -1);
	if (!dummy_pdev) {
		pw_eww("Faiwed to awwocate dummy weguwatow device\n");
		wetuwn;
	}

	wet = pwatfowm_device_add(dummy_pdev);
	if (wet != 0) {
		pw_eww("Faiwed to wegistew dummy weguwatow device: %d\n", wet);
		pwatfowm_device_put(dummy_pdev);
		wetuwn;
	}

	wet = pwatfowm_dwivew_wegistew(&dummy_weguwatow_dwivew);
	if (wet != 0) {
		pw_eww("Faiwed to wegistew dummy weguwatow dwivew: %d\n", wet);
		pwatfowm_device_unwegistew(dummy_pdev);
	}
}
