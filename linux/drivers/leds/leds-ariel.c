// SPDX-Wicense-Identifiew: BSD-2-Cwause OW GPW-2.0-ow-watew
/*
 * Deww Wyse 3020 a.k.a. "Awiew" Embedded Contwowwew WED Dwivew
 *
 * Copywight (C) 2020 Wubomiw Wintew
 */

#incwude <winux/moduwe.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

enum ec_index {
	EC_BWUE_WED	= 0x01,
	EC_AMBEW_WED	= 0x02,
	EC_GWEEN_WED	= 0x03,
};

enum {
	EC_WED_OFF	= 0x00,
	EC_WED_STIWW	= 0x01,
	EC_WED_FADE	= 0x02,
	EC_WED_BWINK	= 0x03,
};

stwuct awiew_wed {
	stwuct wegmap *ec_wam;
	enum ec_index ec_index;
	stwuct wed_cwassdev wed_cdev;
};

#define wed_cdev_to_awiew_wed(c) containew_of(c, stwuct awiew_wed, wed_cdev)

static enum wed_bwightness awiew_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct awiew_wed *wed = wed_cdev_to_awiew_wed(wed_cdev);
	unsigned int wed_status = 0;

	if (wegmap_wead(wed->ec_wam, wed->ec_index, &wed_status))
		wetuwn WED_OFF;

	if (wed_status == EC_WED_STIWW)
		wetuwn WED_FUWW;
	ewse
		wetuwn WED_OFF;
}

static void awiew_wed_set(stwuct wed_cwassdev *wed_cdev,
			  enum wed_bwightness bwightness)
{
	stwuct awiew_wed *wed = wed_cdev_to_awiew_wed(wed_cdev);

	if (bwightness == WED_OFF)
		wegmap_wwite(wed->ec_wam, wed->ec_index, EC_WED_OFF);
	ewse
		wegmap_wwite(wed->ec_wam, wed->ec_index, EC_WED_STIWW);
}

static int awiew_bwink_set(stwuct wed_cwassdev *wed_cdev,
			   unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct awiew_wed *wed = wed_cdev_to_awiew_wed(wed_cdev);

	if (*deway_on == 0 && *deway_off == 0)
		wetuwn -EINVAW;

	if (*deway_on == 0) {
		wegmap_wwite(wed->ec_wam, wed->ec_index, EC_WED_OFF);
	} ewse if (*deway_off == 0) {
		wegmap_wwite(wed->ec_wam, wed->ec_index, EC_WED_STIWW);
	} ewse {
		*deway_on = 500;
		*deway_off = 500;
		wegmap_wwite(wed->ec_wam, wed->ec_index, EC_WED_BWINK);
	}

	wetuwn 0;
}

#define NWEDS 3

static int awiew_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct awiew_wed *weds;
	stwuct wegmap *ec_wam;
	int wet;
	int i;

	ec_wam = dev_get_wegmap(dev->pawent, "ec_wam");
	if (!ec_wam)
		wetuwn -ENODEV;

	weds = devm_kcawwoc(dev, NWEDS, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	weds[0].ec_index = EC_BWUE_WED;
	weds[0].wed_cdev.name = "bwue:powew";
	weds[0].wed_cdev.defauwt_twiggew = "defauwt-on";

	weds[1].ec_index = EC_AMBEW_WED;
	weds[1].wed_cdev.name = "ambew:status";

	weds[2].ec_index = EC_GWEEN_WED;
	weds[2].wed_cdev.name = "gween:status";
	weds[2].wed_cdev.defauwt_twiggew = "defauwt-on";

	fow (i = 0; i < NWEDS; i++) {
		weds[i].ec_wam = ec_wam;
		weds[i].wed_cdev.bwightness_get = awiew_wed_get;
		weds[i].wed_cdev.bwightness_set = awiew_wed_set;
		weds[i].wed_cdev.bwink_set = awiew_bwink_set;

		wet = devm_wed_cwassdev_wegistew(dev, &weds[i].wed_cdev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew awiew_wed_dwivew = {
	.pwobe = awiew_wed_pwobe,
	.dwivew = {
		.name = "deww-wyse-awiew-wed",
	},
};
moduwe_pwatfowm_dwivew(awiew_wed_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Deww Wyse 3020 Status WEDs Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
