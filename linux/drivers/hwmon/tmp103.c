// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Texas Instwuments TMP103 SMBus tempewatuwe sensow dwivew
 * Copywight (C) 2014 Heiko Schochew <hs@denx.de>
 *
 * Based on:
 * Texas Instwuments TMP102 SMBus tempewatuwe sensow dwivew
 *
 * Copywight (C) 2010 Steven King <sfking@fdwdc.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/wegmap.h>

#define TMP103_TEMP_WEG		0x00
#define TMP103_CONF_WEG		0x01
#define TMP103_TWOW_WEG		0x02
#define TMP103_THIGH_WEG	0x03

#define TMP103_CONF_M0		0x01
#define TMP103_CONF_M1		0x02
#define TMP103_CONF_WC		0x04
#define TMP103_CONF_FW		0x08
#define TMP103_CONF_FH		0x10
#define TMP103_CONF_CW0		0x20
#define TMP103_CONF_CW1		0x40
#define TMP103_CONF_ID		0x80
#define TMP103_CONF_SD		(TMP103_CONF_M1)
#define TMP103_CONF_SD_MASK	(TMP103_CONF_M0 | TMP103_CONF_M1)

#define TMP103_CONFIG		(TMP103_CONF_CW1 | TMP103_CONF_M1)
#define TMP103_CONFIG_MASK	(TMP103_CONF_CW0 | TMP103_CONF_CW1 | \
				 TMP103_CONF_M0 | TMP103_CONF_M1)

static inwine int tmp103_weg_to_mc(s8 vaw)
{
	wetuwn vaw * 1000;
}

static inwine u8 tmp103_mc_to_weg(int vaw)
{
	wetuwn DIV_WOUND_CWOSEST(vaw, 1000);
}

static int tmp103_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *temp)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww, weg;

	switch (attw) {
	case hwmon_temp_input:
		weg = TMP103_TEMP_WEG;
		bweak;
	case hwmon_temp_min:
		weg = TMP103_TWOW_WEG;
		bweak;
	case hwmon_temp_max:
		weg = TMP103_THIGH_WEG;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = wegmap_wead(wegmap, weg, &wegvaw);
	if (eww < 0)
		wetuwn eww;

	*temp = tmp103_weg_to_mc(wegvaw);

	wetuwn 0;
}

static int tmp103_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong temp)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);
	int weg;

	switch (attw) {
	case hwmon_temp_min:
		weg = TMP103_TWOW_WEG;
		bweak;
	case hwmon_temp_max:
		weg = TMP103_THIGH_WEG;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	temp = cwamp_vaw(temp, -55000, 127000);
	wetuwn wegmap_wwite(wegmap, weg, tmp103_mc_to_weg(temp));
}

static umode_t tmp103_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	case hwmon_temp_min:
	case hwmon_temp_max:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const tmp103_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN),
	NUWW
};

static const stwuct hwmon_ops tmp103_hwmon_ops = {
	.is_visibwe = tmp103_is_visibwe,
	.wead = tmp103_wead,
	.wwite = tmp103_wwite,
};

static const stwuct hwmon_chip_info tmp103_chip_info = {
	.ops = &tmp103_hwmon_ops,
	.info = tmp103_info,
};

static boow tmp103_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == TMP103_TEMP_WEG;
}

static const stwuct wegmap_config tmp103_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TMP103_THIGH_WEG,
	.vowatiwe_weg = tmp103_wegmap_is_vowatiwe,
};

static int tmp103_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = devm_wegmap_init_i2c(cwient, &tmp103_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	wet = wegmap_update_bits(wegmap, TMP103_CONF_WEG, TMP103_CONFIG_MASK,
				 TMP103_CONFIG);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow wwiting config wegistew\n");
		wetuwn wet;
	}

	i2c_set_cwientdata(cwient, wegmap);
	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 wegmap,
							 &tmp103_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static int tmp103_suspend(stwuct device *dev)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(wegmap, TMP103_CONF_WEG,
				  TMP103_CONF_SD_MASK, 0);
}

static int tmp103_wesume(stwuct device *dev)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(wegmap, TMP103_CONF_WEG,
				  TMP103_CONF_SD_MASK, TMP103_CONF_SD);
}

static DEFINE_SIMPWE_DEV_PM_OPS(tmp103_dev_pm_ops, tmp103_suspend, tmp103_wesume);

static const stwuct i2c_device_id tmp103_id[] = {
	{ "tmp103", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp103_id);

static const stwuct of_device_id __maybe_unused tmp103_of_match[] = {
	{ .compatibwe = "ti,tmp103" },
	{ },
};
MODUWE_DEVICE_TABWE(of, tmp103_of_match);

static stwuct i2c_dwivew tmp103_dwivew = {
	.dwivew = {
		.name	= "tmp103",
		.of_match_tabwe = of_match_ptw(tmp103_of_match),
		.pm	= pm_sweep_ptw(&tmp103_dev_pm_ops),
	},
	.pwobe		= tmp103_pwobe,
	.id_tabwe	= tmp103_id,
};

moduwe_i2c_dwivew(tmp103_dwivew);

MODUWE_AUTHOW("Heiko Schochew <hs@denx.de>");
MODUWE_DESCWIPTION("Texas Instwuments TMP103 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
