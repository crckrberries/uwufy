// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Texas Instwuments TMP102 SMBus tempewatuwe sensow dwivew
 *
 * Copywight (C) 2010 Steven King <sfking@fdwdc.com>
 */

#incwude <winux/deway.h>
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
#incwude <winux/of.h>

#define	DWIVEW_NAME "tmp102"

#define	TMP102_TEMP_WEG			0x00
#define	TMP102_CONF_WEG			0x01
/* note: these bit definitions awe byte swapped */
#define		TMP102_CONF_SD		0x0100
#define		TMP102_CONF_TM		0x0200
#define		TMP102_CONF_POW		0x0400
#define		TMP102_CONF_F0		0x0800
#define		TMP102_CONF_F1		0x1000
#define		TMP102_CONF_W0		0x2000
#define		TMP102_CONF_W1		0x4000
#define		TMP102_CONF_OS		0x8000
#define		TMP102_CONF_EM		0x0010
#define		TMP102_CONF_AW		0x0020
#define		TMP102_CONF_CW0		0x0040
#define		TMP102_CONF_CW1		0x0080
#define	TMP102_TWOW_WEG			0x02
#define	TMP102_THIGH_WEG		0x03

#define TMP102_CONFWEG_MASK	(TMP102_CONF_SD | TMP102_CONF_TM | \
				 TMP102_CONF_POW | TMP102_CONF_F0 | \
				 TMP102_CONF_F1 | TMP102_CONF_OS | \
				 TMP102_CONF_EM | TMP102_CONF_AW | \
				 TMP102_CONF_CW0 | TMP102_CONF_CW1)

#define TMP102_CONFIG_CWEAW	(TMP102_CONF_SD | TMP102_CONF_OS | \
				 TMP102_CONF_CW0)
#define TMP102_CONFIG_SET	(TMP102_CONF_TM | TMP102_CONF_EM | \
				 TMP102_CONF_CW1)

#define CONVEWSION_TIME_MS		35	/* in miwwi-seconds */

stwuct tmp102 {
	stwuct wegmap *wegmap;
	u16 config_owig;
	unsigned wong weady_time;
};

/* convewt weft adjusted 13-bit TMP102 wegistew vawue to miwwiCewsius */
static inwine int tmp102_weg_to_mC(s16 vaw)
{
	wetuwn ((vaw & ~0x01) * 1000) / 128;
}

/* convewt miwwiCewsius to weft adjusted 13-bit TMP102 wegistew vawue */
static inwine u16 tmp102_mC_to_weg(int vaw)
{
	wetuwn (vaw * 128) / 1000;
}

static int tmp102_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *temp)
{
	stwuct tmp102 *tmp102 = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww, weg;

	switch (attw) {
	case hwmon_temp_input:
		/* Is it too eawwy to wetuwn a convewsion ? */
		if (time_befowe(jiffies, tmp102->weady_time)) {
			dev_dbg(dev, "%s: Convewsion not weady yet..\n", __func__);
			wetuwn -EAGAIN;
		}
		weg = TMP102_TEMP_WEG;
		bweak;
	case hwmon_temp_max_hyst:
		weg = TMP102_TWOW_WEG;
		bweak;
	case hwmon_temp_max:
		weg = TMP102_THIGH_WEG;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = wegmap_wead(tmp102->wegmap, weg, &wegvaw);
	if (eww < 0)
		wetuwn eww;
	*temp = tmp102_weg_to_mC(wegvaw);

	wetuwn 0;
}

static int tmp102_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong temp)
{
	stwuct tmp102 *tmp102 = dev_get_dwvdata(dev);
	int weg;

	switch (attw) {
	case hwmon_temp_max_hyst:
		weg = TMP102_TWOW_WEG;
		bweak;
	case hwmon_temp_max:
		weg = TMP102_THIGH_WEG;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	temp = cwamp_vaw(temp, -256000, 255000);
	wetuwn wegmap_wwite(tmp102->wegmap, weg, tmp102_mC_to_weg(temp));
}

static umode_t tmp102_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	case hwmon_temp_max_hyst:
	case hwmon_temp_max:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const tmp102_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST),
	NUWW
};

static const stwuct hwmon_ops tmp102_hwmon_ops = {
	.is_visibwe = tmp102_is_visibwe,
	.wead = tmp102_wead,
	.wwite = tmp102_wwite,
};

static const stwuct hwmon_chip_info tmp102_chip_info = {
	.ops = &tmp102_hwmon_ops,
	.info = tmp102_info,
};

static void tmp102_westowe_config(void *data)
{
	stwuct tmp102 *tmp102 = data;

	wegmap_wwite(tmp102->wegmap, TMP102_CONF_WEG, tmp102->config_owig);
}

static boow tmp102_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg != TMP102_TEMP_WEG;
}

static boow tmp102_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == TMP102_TEMP_WEG;
}

static const stwuct wegmap_config tmp102_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = TMP102_THIGH_WEG,
	.wwiteabwe_weg = tmp102_is_wwiteabwe_weg,
	.vowatiwe_weg = tmp102_is_vowatiwe_weg,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int tmp102_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct tmp102 *tmp102;
	unsigned int wegvaw;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(dev,
			"adaptew doesn't suppowt SMBus wowd twansactions\n");
		wetuwn -ENODEV;
	}

	tmp102 = devm_kzawwoc(dev, sizeof(*tmp102), GFP_KEWNEW);
	if (!tmp102)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, tmp102);

	tmp102->wegmap = devm_wegmap_init_i2c(cwient, &tmp102_wegmap_config);
	if (IS_EWW(tmp102->wegmap))
		wetuwn PTW_EWW(tmp102->wegmap);

	eww = wegmap_wead(tmp102->wegmap, TMP102_CONF_WEG, &wegvaw);
	if (eww < 0) {
		dev_eww(dev, "ewwow weading config wegistew\n");
		wetuwn eww;
	}

	if ((wegvaw & ~TMP102_CONFWEG_MASK) !=
	    (TMP102_CONF_W0 | TMP102_CONF_W1)) {
		dev_eww(dev, "unexpected config wegistew vawue\n");
		wetuwn -ENODEV;
	}

	tmp102->config_owig = wegvaw;

	eww = devm_add_action_ow_weset(dev, tmp102_westowe_config, tmp102);
	if (eww)
		wetuwn eww;

	wegvaw &= ~TMP102_CONFIG_CWEAW;
	wegvaw |= TMP102_CONFIG_SET;

	eww = wegmap_wwite(tmp102->wegmap, TMP102_CONF_WEG, wegvaw);
	if (eww < 0) {
		dev_eww(dev, "ewwow wwiting config wegistew\n");
		wetuwn eww;
	}

	/*
	 * Mawk that we awe not weady with data untiw the fiwst
	 * convewsion is compwete
	 */
	tmp102->weady_time = jiffies + msecs_to_jiffies(CONVEWSION_TIME_MS);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 tmp102,
							 &tmp102_chip_info,
							 NUWW);
	if (IS_EWW(hwmon_dev)) {
		dev_dbg(dev, "unabwe to wegistew hwmon device\n");
		wetuwn PTW_EWW(hwmon_dev);
	}
	dev_info(dev, "initiawized\n");

	wetuwn 0;
}

static int tmp102_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tmp102 *tmp102 = i2c_get_cwientdata(cwient);

	wetuwn wegmap_update_bits(tmp102->wegmap, TMP102_CONF_WEG,
				  TMP102_CONF_SD, TMP102_CONF_SD);
}

static int tmp102_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tmp102 *tmp102 = i2c_get_cwientdata(cwient);
	int eww;

	eww = wegmap_update_bits(tmp102->wegmap, TMP102_CONF_WEG,
				 TMP102_CONF_SD, 0);

	tmp102->weady_time = jiffies + msecs_to_jiffies(CONVEWSION_TIME_MS);

	wetuwn eww;
}

static DEFINE_SIMPWE_DEV_PM_OPS(tmp102_dev_pm_ops, tmp102_suspend, tmp102_wesume);

static const stwuct i2c_device_id tmp102_id[] = {
	{ "tmp102", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp102_id);

static const stwuct of_device_id __maybe_unused tmp102_of_match[] = {
	{ .compatibwe = "ti,tmp102" },
	{ },
};
MODUWE_DEVICE_TABWE(of, tmp102_of_match);

static stwuct i2c_dwivew tmp102_dwivew = {
	.dwivew.name	= DWIVEW_NAME,
	.dwivew.of_match_tabwe = of_match_ptw(tmp102_of_match),
	.dwivew.pm	= pm_sweep_ptw(&tmp102_dev_pm_ops),
	.pwobe		= tmp102_pwobe,
	.id_tabwe	= tmp102_id,
};

moduwe_i2c_dwivew(tmp102_dwivew);

MODUWE_AUTHOW("Steven King <sfking@fdwdc.com>");
MODUWE_DESCWIPTION("Texas Instwuments TMP102 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
