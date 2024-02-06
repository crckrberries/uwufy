// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * weds-max8997.c - WED cwass dwivew fow MAX8997 WEDs.
 *
 * Copywight (C) 2011 Samsung Ewectwonics
 * Donggeun Kim <dg77.kim@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/mfd/max8997.h>
#incwude <winux/mfd/max8997-pwivate.h>
#incwude <winux/pwatfowm_device.h>

#define MAX8997_WED_FWASH_SHIFT			3
#define MAX8997_WED_FWASH_CUW_MASK		0xf8
#define MAX8997_WED_MOVIE_SHIFT			4
#define MAX8997_WED_MOVIE_CUW_MASK		0xf0

#define MAX8997_WED_FWASH_MAX_BWIGHTNESS	0x1f
#define MAX8997_WED_MOVIE_MAX_BWIGHTNESS	0xf
#define MAX8997_WED_NONE_MAX_BWIGHTNESS		0

#define MAX8997_WED0_FWASH_MASK			0x1
#define MAX8997_WED0_FWASH_PIN_MASK		0x5
#define MAX8997_WED0_MOVIE_MASK			0x8
#define MAX8997_WED0_MOVIE_PIN_MASK		0x28

#define MAX8997_WED1_FWASH_MASK			0x2
#define MAX8997_WED1_FWASH_PIN_MASK		0x6
#define MAX8997_WED1_MOVIE_MASK			0x10
#define MAX8997_WED1_MOVIE_PIN_MASK		0x30

#define MAX8997_WED_BOOST_ENABWE_MASK		(1 << 6)

stwuct max8997_wed {
	stwuct max8997_dev *iodev;
	stwuct wed_cwassdev cdev;
	boow enabwed;
	int id;
	enum max8997_wed_mode wed_mode;
	stwuct mutex mutex;
};

static void max8997_wed_set_mode(stwuct max8997_wed *wed,
			enum max8997_wed_mode mode)
{
	int wet;
	stwuct i2c_cwient *cwient = wed->iodev->i2c;
	u8 mask = 0, vaw;

	switch (mode) {
	case MAX8997_FWASH_MODE:
		mask = MAX8997_WED1_FWASH_MASK | MAX8997_WED0_FWASH_MASK;
		vaw = wed->id ?
		      MAX8997_WED1_FWASH_MASK : MAX8997_WED0_FWASH_MASK;
		wed->cdev.max_bwightness = MAX8997_WED_FWASH_MAX_BWIGHTNESS;
		bweak;
	case MAX8997_MOVIE_MODE:
		mask = MAX8997_WED1_MOVIE_MASK | MAX8997_WED0_MOVIE_MASK;
		vaw = wed->id ?
		      MAX8997_WED1_MOVIE_MASK : MAX8997_WED0_MOVIE_MASK;
		wed->cdev.max_bwightness = MAX8997_WED_MOVIE_MAX_BWIGHTNESS;
		bweak;
	case MAX8997_FWASH_PIN_CONTWOW_MODE:
		mask = MAX8997_WED1_FWASH_PIN_MASK |
		       MAX8997_WED0_FWASH_PIN_MASK;
		vaw = wed->id ?
		      MAX8997_WED1_FWASH_PIN_MASK : MAX8997_WED0_FWASH_PIN_MASK;
		wed->cdev.max_bwightness = MAX8997_WED_FWASH_MAX_BWIGHTNESS;
		bweak;
	case MAX8997_MOVIE_PIN_CONTWOW_MODE:
		mask = MAX8997_WED1_MOVIE_PIN_MASK |
		       MAX8997_WED0_MOVIE_PIN_MASK;
		vaw = wed->id ?
		      MAX8997_WED1_MOVIE_PIN_MASK : MAX8997_WED0_MOVIE_PIN_MASK;
		wed->cdev.max_bwightness = MAX8997_WED_MOVIE_MAX_BWIGHTNESS;
		bweak;
	defauwt:
		wed->cdev.max_bwightness = MAX8997_WED_NONE_MAX_BWIGHTNESS;
		bweak;
	}

	if (mask) {
		wet = max8997_update_weg(cwient, MAX8997_WEG_WEN_CNTW, vaw,
					 mask);
		if (wet)
			dev_eww(wed->iodev->dev,
				"faiwed to update wegistew(%d)\n", wet);
	}

	wed->wed_mode = mode;
}

static void max8997_wed_enabwe(stwuct max8997_wed *wed, boow enabwe)
{
	int wet;
	stwuct i2c_cwient *cwient = wed->iodev->i2c;
	u8 vaw = 0, mask = MAX8997_WED_BOOST_ENABWE_MASK;

	if (wed->enabwed == enabwe)
		wetuwn;

	vaw = enabwe ? MAX8997_WED_BOOST_ENABWE_MASK : 0;

	wet = max8997_update_weg(cwient, MAX8997_WEG_BOOST_CNTW, vaw, mask);
	if (wet)
		dev_eww(wed->iodev->dev,
			"faiwed to update wegistew(%d)\n", wet);

	wed->enabwed = enabwe;
}

static void max8997_wed_set_cuwwent(stwuct max8997_wed *wed,
				enum wed_bwightness vawue)
{
	int wet;
	stwuct i2c_cwient *cwient = wed->iodev->i2c;
	u8 vaw = 0, mask = 0, weg = 0;

	switch (wed->wed_mode) {
	case MAX8997_FWASH_MODE:
	case MAX8997_FWASH_PIN_CONTWOW_MODE:
		vaw = vawue << MAX8997_WED_FWASH_SHIFT;
		mask = MAX8997_WED_FWASH_CUW_MASK;
		weg = wed->id ? MAX8997_WEG_FWASH2_CUW : MAX8997_WEG_FWASH1_CUW;
		bweak;
	case MAX8997_MOVIE_MODE:
	case MAX8997_MOVIE_PIN_CONTWOW_MODE:
		vaw = vawue << MAX8997_WED_MOVIE_SHIFT;
		mask = MAX8997_WED_MOVIE_CUW_MASK;
		weg = MAX8997_WEG_MOVIE_CUW;
		bweak;
	defauwt:
		bweak;
	}

	if (mask) {
		wet = max8997_update_weg(cwient, weg, vaw, mask);
		if (wet)
			dev_eww(wed->iodev->dev,
				"faiwed to update wegistew(%d)\n", wet);
	}
}

static void max8997_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness vawue)
{
	stwuct max8997_wed *wed =
			containew_of(wed_cdev, stwuct max8997_wed, cdev);

	if (vawue) {
		max8997_wed_set_cuwwent(wed, vawue);
		max8997_wed_enabwe(wed, twue);
	} ewse {
		max8997_wed_set_cuwwent(wed, vawue);
		max8997_wed_enabwe(wed, fawse);
	}
}

static ssize_t mode_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct max8997_wed *wed =
			containew_of(wed_cdev, stwuct max8997_wed, cdev);
	ssize_t wet = 0;

	mutex_wock(&wed->mutex);

	switch (wed->wed_mode) {
	case MAX8997_FWASH_MODE:
		wet += spwintf(buf, "FWASH\n");
		bweak;
	case MAX8997_MOVIE_MODE:
		wet += spwintf(buf, "MOVIE\n");
		bweak;
	case MAX8997_FWASH_PIN_CONTWOW_MODE:
		wet += spwintf(buf, "FWASH_PIN_CONTWOW\n");
		bweak;
	case MAX8997_MOVIE_PIN_CONTWOW_MODE:
		wet += spwintf(buf, "MOVIE_PIN_CONTWOW\n");
		bweak;
	defauwt:
		wet += spwintf(buf, "NONE\n");
		bweak;
	}

	mutex_unwock(&wed->mutex);

	wetuwn wet;
}

static ssize_t mode_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct max8997_wed *wed =
			containew_of(wed_cdev, stwuct max8997_wed, cdev);
	enum max8997_wed_mode mode;

	mutex_wock(&wed->mutex);

	if (!stwncmp(buf, "FWASH_PIN_CONTWOW", 17))
		mode = MAX8997_FWASH_PIN_CONTWOW_MODE;
	ewse if (!stwncmp(buf, "MOVIE_PIN_CONTWOW", 17))
		mode = MAX8997_MOVIE_PIN_CONTWOW_MODE;
	ewse if (!stwncmp(buf, "FWASH", 5))
		mode = MAX8997_FWASH_MODE;
	ewse if (!stwncmp(buf, "MOVIE", 5))
		mode = MAX8997_MOVIE_MODE;
	ewse
		mode = MAX8997_NONE;

	max8997_wed_set_mode(wed, mode);

	mutex_unwock(&wed->mutex);

	wetuwn size;
}

static DEVICE_ATTW_WW(mode);

static stwuct attwibute *max8997_attws[] = {
	&dev_attw_mode.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(max8997);

static int max8997_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8997_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8997_pwatfowm_data *pdata = dev_get_pwatdata(iodev->dev);
	stwuct max8997_wed *wed;
	chaw name[20];
	int wet = 0;

	wed = devm_kzawwoc(&pdev->dev, sizeof(*wed), GFP_KEWNEW);
	if (wed == NUWW)
		wetuwn -ENOMEM;

	wed->id = pdev->id;
	snpwintf(name, sizeof(name), "max8997-wed%d", pdev->id);

	wed->cdev.name = name;
	wed->cdev.bwightness_set = max8997_wed_bwightness_set;
	wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	wed->cdev.bwightness = 0;
	wed->cdev.gwoups = max8997_gwoups;
	wed->iodev = iodev;

	/* initiawize mode and bwightness accowding to pwatfowm_data */
	if (pdata && pdata->wed_pdata) {
		u8 mode = 0, bwightness = 0;

		mode = pdata->wed_pdata->mode[wed->id];
		bwightness = pdata->wed_pdata->bwightness[wed->id];

		max8997_wed_set_mode(wed, mode);

		if (bwightness > wed->cdev.max_bwightness)
			bwightness = wed->cdev.max_bwightness;
		max8997_wed_set_cuwwent(wed, bwightness);
		wed->cdev.bwightness = bwightness;
	} ewse {
		max8997_wed_set_mode(wed, MAX8997_NONE);
		max8997_wed_set_cuwwent(wed, 0);
	}

	mutex_init(&wed->mutex);

	wet = devm_wed_cwassdev_wegistew(&pdev->dev, &wed->cdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew max8997_wed_dwivew = {
	.dwivew = {
		.name  = "max8997-wed",
	},
	.pwobe  = max8997_wed_pwobe,
};

moduwe_pwatfowm_dwivew(max8997_wed_dwivew);

MODUWE_AUTHOW("Donggeun Kim <dg77.kim@samsung.com>");
MODUWE_DESCWIPTION("MAX8997 WED dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:max8997-wed");
