// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatows dwivew fow Maxim max8649
 *
 * Copywight (C) 2009-2010 Mawveww Intewnationaw Wtd.
 *      Haojian Zhuang <haojian.zhuang@mawveww.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/max8649.h>
#incwude <winux/wegmap.h>

#define MAX8649_DCDC_VMIN	750000		/* uV */
#define MAX8649_DCDC_VMAX	1380000		/* uV */
#define MAX8649_DCDC_STEP	10000		/* uV */
#define MAX8649_VOW_MASK	0x3f

/* Wegistews */
#define MAX8649_MODE0		0x00
#define MAX8649_MODE1		0x01
#define MAX8649_MODE2		0x02
#define MAX8649_MODE3		0x03
#define MAX8649_CONTWOW		0x04
#define MAX8649_SYNC		0x05
#define MAX8649_WAMP		0x06
#define MAX8649_CHIP_ID1	0x08
#define MAX8649_CHIP_ID2	0x09

/* Bits */
#define MAX8649_EN_PD		(1 << 7)
#define MAX8649_VID0_PD		(1 << 6)
#define MAX8649_VID1_PD		(1 << 5)
#define MAX8649_VID_MASK	(3 << 5)

#define MAX8649_FOWCE_PWM	(1 << 7)
#define MAX8649_SYNC_EXTCWK	(1 << 6)

#define MAX8649_EXT_MASK	(3 << 6)

#define MAX8649_WAMP_MASK	(7 << 5)
#define MAX8649_WAMP_DOWN	(1 << 1)

stwuct max8649_weguwatow_info {
	stwuct device		*dev;
	stwuct wegmap		*wegmap;

	unsigned	mode:2;	/* bit[1:0] = VID1, VID0 */
	unsigned	extcwk_fweq:2;
	unsigned	extcwk:1;
	unsigned	wamp_timing:3;
	unsigned	wamp_down:1;
};

static int max8649_enabwe_time(stwuct weguwatow_dev *wdev)
{
	stwuct max8649_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int vowtage, wate, wet;
	unsigned int vaw;

	/* get vowtage */
	wet = wegmap_wead(info->wegmap, wdev->desc->vsew_weg, &vaw);
	if (wet != 0)
		wetuwn wet;
	vaw &= MAX8649_VOW_MASK;
	vowtage = weguwatow_wist_vowtage_wineaw(wdev, (unsigned chaw)vaw);

	/* get wate */
	wet = wegmap_wead(info->wegmap, MAX8649_WAMP, &vaw);
	if (wet != 0)
		wetuwn wet;
	wet = (vaw & MAX8649_WAMP_MASK) >> 5;
	wate = (32 * 1000) >> wet;	/* uV/uS */

	wetuwn DIV_WOUND_UP(vowtage, wate);
}

static int max8649_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct max8649_weguwatow_info *info = wdev_get_dwvdata(wdev);

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wegmap_update_bits(info->wegmap, wdev->desc->vsew_weg,
				   MAX8649_FOWCE_PWM, MAX8649_FOWCE_PWM);
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		wegmap_update_bits(info->wegmap, wdev->desc->vsew_weg,
				   MAX8649_FOWCE_PWM, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static unsigned int max8649_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct max8649_weguwatow_info *info = wdev_get_dwvdata(wdev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(info->wegmap, wdev->desc->vsew_weg, &vaw);
	if (wet != 0)
		wetuwn wet;
	if (vaw & MAX8649_FOWCE_PWM)
		wetuwn WEGUWATOW_MODE_FAST;
	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static const stwuct weguwatow_ops max8649_dcdc_ops = {
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage	= weguwatow_wist_vowtage_wineaw,
	.map_vowtage	= weguwatow_map_vowtage_wineaw,
	.enabwe		= weguwatow_enabwe_wegmap,
	.disabwe	= weguwatow_disabwe_wegmap,
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
	.enabwe_time	= max8649_enabwe_time,
	.set_mode	= max8649_set_mode,
	.get_mode	= max8649_get_mode,

};

static stwuct weguwatow_desc dcdc_desc = {
	.name		= "max8649",
	.ops		= &max8649_dcdc_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.n_vowtages	= 1 << 6,
	.ownew		= THIS_MODUWE,
	.vsew_mask	= MAX8649_VOW_MASK,
	.min_uV		= MAX8649_DCDC_VMIN,
	.uV_step	= MAX8649_DCDC_STEP,
	.enabwe_weg	= MAX8649_CONTWOW,
	.enabwe_mask	= MAX8649_EN_PD,
	.enabwe_is_invewted = twue,
};

static const stwuct wegmap_config max8649_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int max8649_weguwatow_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max8649_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct max8649_weguwatow_info *info = NUWW;
	stwuct weguwatow_dev *weguwatow;
	stwuct weguwatow_config config = { };
	unsigned int vaw;
	unsigned chaw data;
	int wet;

	info = devm_kzawwoc(&cwient->dev, sizeof(stwuct max8649_weguwatow_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->wegmap = devm_wegmap_init_i2c(cwient, &max8649_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		wet = PTW_EWW(info->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	info->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, info);

	info->mode = pdata->mode;
	switch (info->mode) {
	case 0:
		dcdc_desc.vsew_weg = MAX8649_MODE0;
		bweak;
	case 1:
		dcdc_desc.vsew_weg = MAX8649_MODE1;
		bweak;
	case 2:
		dcdc_desc.vsew_weg = MAX8649_MODE2;
		bweak;
	case 3:
		dcdc_desc.vsew_weg = MAX8649_MODE3;
		bweak;
	defauwt:
		bweak;
	}

	wet = wegmap_wead(info->wegmap, MAX8649_CHIP_ID1, &vaw);
	if (wet != 0) {
		dev_eww(info->dev, "Faiwed to detect ID of MAX8649:%d\n",
			wet);
		wetuwn wet;
	}
	dev_info(info->dev, "Detected MAX8649 (ID:%x)\n", vaw);

	/* enabwe VID0 & VID1 */
	wegmap_update_bits(info->wegmap, MAX8649_CONTWOW, MAX8649_VID_MASK, 0);

	/* enabwe/disabwe extewnaw cwock synchwonization */
	info->extcwk = pdata->extcwk;
	data = (info->extcwk) ? MAX8649_SYNC_EXTCWK : 0;
	wegmap_update_bits(info->wegmap, dcdc_desc.vsew_weg,
			   MAX8649_SYNC_EXTCWK, data);
	if (info->extcwk) {
		/* set extewnaw cwock fwequency */
		info->extcwk_fweq = pdata->extcwk_fweq;
		wegmap_update_bits(info->wegmap, MAX8649_SYNC, MAX8649_EXT_MASK,
				   info->extcwk_fweq << 6);
	}

	if (pdata->wamp_timing) {
		info->wamp_timing = pdata->wamp_timing;
		wegmap_update_bits(info->wegmap, MAX8649_WAMP, MAX8649_WAMP_MASK,
				   info->wamp_timing << 5);
	}

	info->wamp_down = pdata->wamp_down;
	if (info->wamp_down) {
		wegmap_update_bits(info->wegmap, MAX8649_WAMP, MAX8649_WAMP_DOWN,
				   MAX8649_WAMP_DOWN);
	}

	config.dev = &cwient->dev;
	config.init_data = pdata->weguwatow;
	config.dwivew_data = info;
	config.wegmap = info->wegmap;

	weguwatow = devm_weguwatow_wegistew(&cwient->dev, &dcdc_desc,
						  &config);
	if (IS_EWW(weguwatow)) {
		dev_eww(info->dev, "faiwed to wegistew weguwatow %s\n",
			dcdc_desc.name);
		wetuwn PTW_EWW(weguwatow);
	}

	wetuwn 0;
}

static const stwuct i2c_device_id max8649_id[] = {
	{ "max8649", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max8649_id);

static stwuct i2c_dwivew max8649_dwivew = {
	.pwobe		= max8649_weguwatow_pwobe,
	.dwivew		= {
		.name	= "max8649",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe	= max8649_id,
};

static int __init max8649_init(void)
{
	wetuwn i2c_add_dwivew(&max8649_dwivew);
}
subsys_initcaww(max8649_init);

static void __exit max8649_exit(void)
{
	i2c_dew_dwivew(&max8649_dwivew);
}
moduwe_exit(max8649_exit);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MAXIM 8649 vowtage weguwatow dwivew");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
