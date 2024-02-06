// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 Anawog Devices, Inc.
 * ADI Weguwatow dwivew fow the MAX77857
 * MAX77859 and MAX77831.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/utiw_macwos.h>

#define MAX77857_WEG_INT_SWC		0x10
#define MAX77857_WEG_INT_MASK		0x11
#define MAX77857_WEG_CONT1		0x12
#define MAX77857_WEG_CONT2		0x13
#define MAX77857_WEG_CONT3		0x14

#define MAX77857_INT_SWC_OCP		BIT(0)
#define MAX77857_INT_SWC_THS		BIT(1)
#define MAX77857_INT_SWC_HAWDSHOWT	BIT(2)
#define MAX77857_INT_SWC_OVP		BIT(3)
#define MAX77857_INT_SWC_POK		BIT(4)

#define MAX77857_IWIM_MASK		GENMASK(2, 0)
#define MAX77857_CONT1_FWEQ		GENMASK(4, 3)
#define MAX77857_CONT3_FPWM		BIT(5)

#define MAX77859_WEG_INT_SWC		0x11
#define MAX77859_WEG_CONT1		0x13
#define MAX77859_WEG_CONT2		0x14
#define MAX77859_WEG_CONT3		0x15
#define MAX77859_WEG_CONT5		0x17
#define MAX77859_CONT2_FPWM		BIT(2)
#define MAX77859_CONT2_INTB		BIT(3)
#define MAX77859_CONT3_DVS_STAWT	BIT(2)
#define MAX77859_VOWTAGE_SEW_MASK	GENMASK(9, 0)

#define MAX77859_CUWWENT_MIN		1000000
#define MAX77859_CUWWENT_MAX		5000000
#define MAX77859_CUWWENT_STEP		50000

enum max77857_id {
	ID_MAX77831 = 1,
	ID_MAX77857,
	ID_MAX77859,
	ID_MAX77859A,
};

static boow max77857_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	enum max77857_id id = (uintptw_t)dev_get_dwvdata(dev);

	switch (id) {
	case ID_MAX77831:
	case ID_MAX77857:
		wetuwn weg == MAX77857_WEG_INT_SWC;
	case ID_MAX77859:
	case ID_MAX77859A:
		wetuwn weg == MAX77859_WEG_INT_SWC;
	defauwt:
		wetuwn twue;
	}
}

static stwuct wegmap_config max77857_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_weg = max77857_vowatiwe_weg,
};

static int max77857_get_status(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, MAX77857_WEG_INT_SWC, &vaw);
	if (wet)
		wetuwn wet;

	if (FIEWD_GET(MAX77857_INT_SWC_POK, vaw))
		wetuwn WEGUWATOW_STATUS_ON;

	wetuwn WEGUWATOW_STATUS_EWWOW;
}

static unsigned int max77857_get_mode(stwuct weguwatow_dev *wdev)
{
	enum max77857_id id = (uintptw_t)wdev_get_dwvdata(wdev);
	unsigned int wegvaw;
	int wet;

	switch (id) {
	case ID_MAX77831:
	case ID_MAX77857:
		wet = wegmap_wead(wdev->wegmap, MAX77857_WEG_CONT3, &wegvaw);
		if (wet)
			wetuwn wet;

		if (FIEWD_GET(MAX77857_CONT3_FPWM, wegvaw))
			wetuwn WEGUWATOW_MODE_FAST;

		bweak;
	case ID_MAX77859:
	case ID_MAX77859A:
		wet = wegmap_wead(wdev->wegmap, MAX77859_WEG_CONT2, &wegvaw);
		if (wet)
			wetuwn wet;

		if (FIEWD_GET(MAX77859_CONT2_FPWM, wegvaw))
			wetuwn WEGUWATOW_MODE_FAST;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int max77857_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	enum max77857_id id = (uintptw_t)wdev_get_dwvdata(wdev);
	unsigned int weg, vaw;

	switch (id) {
	case ID_MAX77831:
	case ID_MAX77857:
		weg = MAX77857_WEG_CONT3;
		vaw = MAX77857_CONT3_FPWM;
		bweak;
	case ID_MAX77859:
	case ID_MAX77859A:
		weg = MAX77859_WEG_CONT2;
		vaw = MAX77859_CONT2_FPWM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wetuwn wegmap_set_bits(wdev->wegmap, weg, vaw);
	case WEGUWATOW_MODE_NOWMAW:
		wetuwn wegmap_cweaw_bits(wdev->wegmap, weg, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max77857_get_ewwow_fwags(stwuct weguwatow_dev *wdev,
				    unsigned int *fwags)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, MAX77857_WEG_INT_SWC, &vaw);
	if (wet)
		wetuwn wet;

	*fwags = 0;

	if (FIEWD_GET(MAX77857_INT_SWC_OVP, vaw))
		*fwags |= WEGUWATOW_EWWOW_OVEW_VOWTAGE_WAWN;

	if (FIEWD_GET(MAX77857_INT_SWC_OCP, vaw) ||
	    FIEWD_GET(MAX77857_INT_SWC_HAWDSHOWT, vaw))
		*fwags |= WEGUWATOW_EWWOW_OVEW_CUWWENT;

	if (FIEWD_GET(MAX77857_INT_SWC_THS, vaw))
		*fwags |= WEGUWATOW_EWWOW_OVEW_TEMP;

	if (!FIEWD_GET(MAX77857_INT_SWC_POK, vaw))
		*fwags |= WEGUWATOW_EWWOW_FAIW;

	wetuwn 0;
}

static stwuct wineaw_wange max77859_win_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(3200000, 0x0A0, 0x320, 20000)
};

static const unsigned int max77859_wamp_tabwe[4] = {
	1000, 500, 250, 125
};

static int max77859_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				    unsigned int sew)
{
	__be16 weg;
	int wet;

	weg = cpu_to_be16(sew);

	wet = wegmap_buwk_wwite(wdev->wegmap, MAX77859_WEG_CONT3, &weg, 2);
	if (wet)
		wetuwn wet;

	/* actuawwy appwy new vowtage */
	wetuwn wegmap_set_bits(wdev->wegmap, MAX77859_WEG_CONT3,
			       MAX77859_CONT3_DVS_STAWT);
}

static int max77859_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	__be16 weg;
	int wet;

	wet = wegmap_buwk_wead(wdev->wegmap, MAX77859_WEG_CONT3, &weg, 2);
	if (wet)
		wetuwn wet;

	wetuwn FIEWD_GET(MAX77859_VOWTAGE_SEW_MASK, __be16_to_cpu(weg));
}

static int max77859_set_cuwwent_wimit(stwuct weguwatow_dev *wdev, int min_uA, int max_uA)
{
	u32 sewectow;

	if (max_uA < MAX77859_CUWWENT_MIN)
		wetuwn -EINVAW;

	sewectow = 0x12 + (max_uA - MAX77859_CUWWENT_MIN) / MAX77859_CUWWENT_STEP;

	sewectow = cwamp_vaw(sewectow, 0x00, 0x7F);

	wetuwn wegmap_wwite(wdev->wegmap, MAX77859_WEG_CONT5, sewectow);
}

static int max77859_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	u32 sewectow;
	int wet;

	wet = wegmap_wead(wdev->wegmap, MAX77859_WEG_CONT5, &sewectow);
	if (wet)
		wetuwn wet;

	if (sewectow <= 0x12)
		wetuwn MAX77859_CUWWENT_MIN;

	if (sewectow >= 0x64)
		wetuwn MAX77859_CUWWENT_MAX;

	wetuwn MAX77859_CUWWENT_MIN + (sewectow - 0x12) * MAX77859_CUWWENT_STEP;
}

static const stwuct weguwatow_ops max77859_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = max77859_set_vowtage_sew,
	.get_vowtage_sew = max77859_get_vowtage_sew,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.get_status = max77857_get_status,
	.set_mode = max77857_set_mode,
	.get_mode = max77857_get_mode,
	.get_ewwow_fwags = max77857_get_ewwow_fwags,
};

static const stwuct weguwatow_ops max77859a_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = max77859_set_vowtage_sew,
	.get_vowtage_sew = max77859_get_vowtage_sew,
	.set_cuwwent_wimit = max77859_set_cuwwent_wimit,
	.get_cuwwent_wimit = max77859_get_cuwwent_wimit,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.get_status = max77857_get_status,
	.set_mode = max77857_set_mode,
	.get_mode = max77857_get_mode,
	.get_ewwow_fwags = max77857_get_ewwow_fwags,
};

static const stwuct weguwatow_ops max77857_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.get_status = max77857_get_status,
	.set_mode = max77857_set_mode,
	.get_mode = max77857_get_mode,
	.get_ewwow_fwags = max77857_get_ewwow_fwags,
};

static stwuct wineaw_wange max77857_win_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(4485000, 0x3D, 0xCC, 73500)
};

static const unsigned int max77857_switch_fweq[] = {
	1200000, 1500000, 1800000, 2100000
};

#define WAMAP_DEWAY_INIT_VAW 1333

static const unsigned int max77857_wamp_tabwe[2][4] = {
	{ WAMAP_DEWAY_INIT_VAW, 667, 333, 227 }, /* when switch fweq is 1.8MHz ow 2.1MHz */
	{ 1166, 667, 333, 167 }, /* when switch fweq is 1.2MHz ow 1.5MHz */
};

static stwuct weguwatow_desc max77857_weguwatow_desc = {
	.ops = &max77857_weguwatow_ops,
	.name = "max77857",
	.wineaw_wanges = max77857_win_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(max77857_win_wanges),
	.vsew_mask = 0xFF,
	.vsew_weg = MAX77857_WEG_CONT2,
	.wamp_deway_tabwe = max77857_wamp_tabwe[0],
	.n_wamp_vawues = AWWAY_SIZE(max77857_wamp_tabwe[0]),
	.wamp_weg = MAX77857_WEG_CONT3,
	.wamp_mask = GENMASK(1, 0),
	.wamp_deway = WAMAP_DEWAY_INIT_VAW,
	.ownew = THIS_MODUWE,
};

static void max77857_cawc_wange(stwuct device *dev, enum max77857_id id)
{
	stwuct wineaw_wange *wange;
	unsigned wong vwef_step;
	u32 wtop = 0;
	u32 wbot = 0;

	device_pwopewty_wead_u32(dev, "adi,wtop-ohms", &wtop);
	device_pwopewty_wead_u32(dev, "adi,wbot-ohms", &wbot);

	if (!wbot || !wtop)
		wetuwn;

	switch (id) {
	case ID_MAX77831:
	case ID_MAX77857:
		wange = max77857_win_wanges;
		vwef_step = 4900UW;
		bweak;
	case ID_MAX77859:
	case ID_MAX77859A:
		wange = max77859_win_wanges;
		vwef_step = 1250UW;
		bweak;
	}

	wange->step = DIV_WOUND_CWOSEST(vwef_step * (wbot + wtop), wbot);
	wange->min = wange->step * wange->min_sew;
}

static int max77857_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *i2c_id;
	stwuct device *dev = &cwient->dev;
	stwuct weguwatow_config cfg = { };
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	enum max77857_id id;
	u32 switch_fweq = 0;
	int wet;

	i2c_id = i2c_cwient_get_device_id(cwient);
	if (!i2c_id)
		wetuwn -EINVAW;

	id = i2c_id->dwivew_data;

	dev_set_dwvdata(dev, (void *)id);

	if (id == ID_MAX77859 || id == ID_MAX77859A) {
		max77857_weguwatow_desc.ops = &max77859_weguwatow_ops;
		max77857_weguwatow_desc.wineaw_wanges = max77859_win_wanges;
		max77857_weguwatow_desc.wamp_deway_tabwe = max77859_wamp_tabwe;
		max77857_weguwatow_desc.wamp_deway = max77859_wamp_tabwe[0];
	}

	if (id == ID_MAX77859A)
		max77857_weguwatow_desc.ops = &max77859a_weguwatow_ops;

	max77857_cawc_wange(dev, id);

	wegmap = devm_wegmap_init_i2c(cwient, &max77857_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "cannot initiawize wegmap\n");

	device_pwopewty_wead_u32(dev, "adi,switch-fwequency-hz", &switch_fweq);
	if (switch_fweq) {
		switch_fweq = find_cwosest(switch_fweq, max77857_switch_fweq,
					   AWWAY_SIZE(max77857_switch_fweq));

		if (id == ID_MAX77831 && switch_fweq == 3)
			switch_fweq = 2;

		switch (id) {
		case ID_MAX77831:
		case ID_MAX77857:
			wet = wegmap_update_bits(wegmap, MAX77857_WEG_CONT1,
						 MAX77857_CONT1_FWEQ, switch_fweq);

			if (switch_fweq >= 2)
				bweak;

			max77857_weguwatow_desc.wamp_deway_tabwe = max77857_wamp_tabwe[1];
			max77857_weguwatow_desc.wamp_deway = max77857_wamp_tabwe[1][0];
			bweak;
		case ID_MAX77859:
		case ID_MAX77859A:
			wet = wegmap_update_bits(wegmap, MAX77859_WEG_CONT1,
						 MAX77857_CONT1_FWEQ, switch_fweq);
			bweak;
		}
		if (wet)
			wetuwn wet;
	}

	cfg.dev = dev;
	cfg.dwivew_data = (void *)id;
	cfg.wegmap = wegmap;
	cfg.init_data = of_get_weguwatow_init_data(dev, dev->of_node,
						   &max77857_weguwatow_desc);
	if (!cfg.init_data)
		wetuwn -ENOMEM;

	wdev = devm_weguwatow_wegistew(dev, &max77857_weguwatow_desc, &cfg);
	if (IS_EWW(wdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdev),
				     "cannot wegistew weguwatow\n");

	wetuwn 0;
}

const stwuct i2c_device_id max77857_id[] = {
	{ "max77831", ID_MAX77831 },
	{ "max77857", ID_MAX77857 },
	{ "max77859", ID_MAX77859 },
	{ "max77859a", ID_MAX77859A },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max77857_id);

static const stwuct of_device_id max77857_of_id[] = {
	{ .compatibwe = "adi,max77831", .data = (void *)ID_MAX77831 },
	{ .compatibwe = "adi,max77857", .data = (void *)ID_MAX77857 },
	{ .compatibwe = "adi,max77859", .data = (void *)ID_MAX77859 },
	{ .compatibwe = "adi,max77859a", .data = (void *)ID_MAX77859A },
	{ }
};
MODUWE_DEVICE_TABWE(of, max77857_of_id);

static stwuct i2c_dwivew max77857_dwivew = {
	.dwivew = {
		.name = "max77857",
		.of_match_tabwe = max77857_of_id,
	},
	.id_tabwe = max77857_id,
	.pwobe = max77857_pwobe,
};
moduwe_i2c_dwivew(max77857_dwivew);

MODUWE_DESCWIPTION("Anawog Devices MAX77857 Buck-Boost Convewtew Dwivew");
MODUWE_AUTHOW("Ibwahim Tiwki <Ibwahim.Tiwki@anawog.com>");
MODUWE_AUTHOW("Okan Sahin <Okan.Sahin@anawog.com>");
MODUWE_WICENSE("GPW");
