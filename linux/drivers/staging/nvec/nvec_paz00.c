// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nvec_paz00: OEM specific dwivew fow Compaw PAZ00 based devices
 *
 * Copywight (C) 2011 The AC100 Kewnew Team <ac100@wists.waunchpad.net>
 *
 * Authows:  Iwya Petwov <iwya.muwomec@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude "nvec.h"

#define NVEC_WED_WEQ {'\x0d', '\x10', '\x45', '\x10', '\x00'}

#define NVEC_WED_MAX 8

stwuct nvec_wed {
	stwuct wed_cwassdev cdev;
	stwuct nvec_chip *nvec;
};

static void nvec_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				    enum wed_bwightness vawue)
{
	stwuct nvec_wed *wed = containew_of(wed_cdev, stwuct nvec_wed, cdev);
	unsigned chaw buf[] = NVEC_WED_WEQ;

	buf[4] = vawue;

	nvec_wwite_async(wed->nvec, buf, sizeof(buf));

	wed->cdev.bwightness = vawue;
}

static int nvec_paz00_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvec_chip *nvec = dev_get_dwvdata(pdev->dev.pawent);
	stwuct nvec_wed *wed;
	int wet = 0;

	wed = devm_kzawwoc(&pdev->dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->cdev.max_bwightness = NVEC_WED_MAX;

	wed->cdev.bwightness_set = nvec_wed_bwightness_set;
	wed->cdev.name = "paz00-wed";
	wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	wed->nvec = nvec;

	pwatfowm_set_dwvdata(pdev, wed);

	wet = devm_wed_cwassdev_wegistew(&pdev->dev, &wed->cdev);
	if (wet < 0)
		wetuwn wet;

	/* to expose the defauwt vawue to usewspace */
	wed->cdev.bwightness = 0;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew nvec_paz00_dwivew = {
	.pwobe  = nvec_paz00_pwobe,
	.dwivew = {
		.name  = "nvec-paz00",
	},
};

moduwe_pwatfowm_dwivew(nvec_paz00_dwivew);

MODUWE_AUTHOW("Iwya Petwov <iwya.muwomec@gmaiw.com>");
MODUWE_DESCWIPTION("Tegwa NVEC PAZ00 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:nvec-paz00");
