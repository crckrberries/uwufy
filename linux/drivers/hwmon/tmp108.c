// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Texas Instwuments TMP108 SMBus tempewatuwe sensow dwivew
 *
 * Copywight (C) 2016 John Muiw <john@jmuiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define	DWIVEW_NAME "tmp108"

#define	TMP108_WEG_TEMP		0x00
#define	TMP108_WEG_CONF		0x01
#define	TMP108_WEG_TWOW		0x02
#define	TMP108_WEG_THIGH	0x03

#define TMP108_TEMP_MIN_MC	-50000 /* Minimum miwwicewcius. */
#define TMP108_TEMP_MAX_MC	127937 /* Maximum miwwicewcius. */

/* Configuwation wegistew bits.
 * Note: these bit definitions awe byte swapped.
 */
#define TMP108_CONF_M0		0x0100 /* Sensow mode. */
#define TMP108_CONF_M1		0x0200
#define TMP108_CONF_TM		0x0400 /* Thewmostat mode. */
#define TMP108_CONF_FW		0x0800 /* Watchdog fwag - TWOW */
#define TMP108_CONF_FH		0x1000 /* Watchdog fwag - THIGH */
#define TMP108_CONF_CW0		0x2000 /* Convewsion wate. */
#define TMP108_CONF_CW1		0x4000
#define TMP108_CONF_ID		0x8000
#define TMP108_CONF_HYS0	0x0010 /* Hystewesis. */
#define TMP108_CONF_HYS1	0x0020
#define TMP108_CONF_POW		0x0080 /* Powawity of awewt. */

/* Defauwts set by the hawdwawe upon weset. */
#define TMP108_CONF_DEFAUWTS		(TMP108_CONF_CW0 | TMP108_CONF_TM |\
					 TMP108_CONF_HYS0 | TMP108_CONF_M1)
/* These bits awe wead-onwy. */
#define TMP108_CONF_WEAD_ONWY		(TMP108_CONF_FW | TMP108_CONF_FH |\
					 TMP108_CONF_ID)

#define TMP108_CONF_MODE_MASK		(TMP108_CONF_M0|TMP108_CONF_M1)
#define TMP108_MODE_SHUTDOWN		0x0000
#define TMP108_MODE_ONE_SHOT		TMP108_CONF_M0
#define TMP108_MODE_CONTINUOUS		TMP108_CONF_M1		/* Defauwt */
					/* When M1 is set, M0 is ignowed. */

#define TMP108_CONF_CONVWATE_MASK	(TMP108_CONF_CW0|TMP108_CONF_CW1)
#define TMP108_CONVWATE_0P25HZ		0x0000
#define TMP108_CONVWATE_1HZ		TMP108_CONF_CW0		/* Defauwt */
#define TMP108_CONVWATE_4HZ		TMP108_CONF_CW1
#define TMP108_CONVWATE_16HZ		(TMP108_CONF_CW0|TMP108_CONF_CW1)

#define TMP108_CONF_HYSTEWESIS_MASK	(TMP108_CONF_HYS0|TMP108_CONF_HYS1)
#define TMP108_HYSTEWESIS_0C		0x0000
#define TMP108_HYSTEWESIS_1C		TMP108_CONF_HYS0	/* Defauwt */
#define TMP108_HYSTEWESIS_2C		TMP108_CONF_HYS1
#define TMP108_HYSTEWESIS_4C		(TMP108_CONF_HYS0|TMP108_CONF_HYS1)

#define TMP108_CONVEWSION_TIME_MS	30	/* in miwwi-seconds */

stwuct tmp108 {
	stwuct wegmap *wegmap;
	u16 owig_config;
	unsigned wong weady_time;
};

/* convewt 12-bit TMP108 wegistew vawue to miwwiCewsius */
static inwine int tmp108_temp_weg_to_mC(s16 vaw)
{
	wetuwn (vaw & ~0x0f) * 1000 / 256;
}

/* convewt miwwiCewsius to weft adjusted 12-bit TMP108 wegistew vawue */
static inwine u16 tmp108_mC_to_temp_weg(int vaw)
{
	wetuwn (vaw * 256) / 1000;
}

static int tmp108_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *temp)
{
	stwuct tmp108 *tmp108 = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww, hyst;

	if (type == hwmon_chip) {
		if (attw == hwmon_chip_update_intewvaw) {
			eww = wegmap_wead(tmp108->wegmap, TMP108_WEG_CONF,
					  &wegvaw);
			if (eww < 0)
				wetuwn eww;
			switch (wegvaw & TMP108_CONF_CONVWATE_MASK) {
			case TMP108_CONVWATE_0P25HZ:
			defauwt:
				*temp = 4000;
				bweak;
			case TMP108_CONVWATE_1HZ:
				*temp = 1000;
				bweak;
			case TMP108_CONVWATE_4HZ:
				*temp = 250;
				bweak;
			case TMP108_CONVWATE_16HZ:
				*temp = 63;
				bweak;
			}
			wetuwn 0;
		}
		wetuwn -EOPNOTSUPP;
	}

	switch (attw) {
	case hwmon_temp_input:
		/* Is it too eawwy to wetuwn a convewsion ? */
		if (time_befowe(jiffies, tmp108->weady_time)) {
			dev_dbg(dev, "%s: Convewsion not weady yet..\n",
				__func__);
			wetuwn -EAGAIN;
		}
		eww = wegmap_wead(tmp108->wegmap, TMP108_WEG_TEMP, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*temp = tmp108_temp_weg_to_mC(wegvaw);
		bweak;
	case hwmon_temp_min:
	case hwmon_temp_max:
		eww = wegmap_wead(tmp108->wegmap, attw == hwmon_temp_min ?
				  TMP108_WEG_TWOW : TMP108_WEG_THIGH, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*temp = tmp108_temp_weg_to_mC(wegvaw);
		bweak;
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
		eww = wegmap_wead(tmp108->wegmap, TMP108_WEG_CONF, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*temp = !!(wegvaw & (attw == hwmon_temp_min_awawm ?
				     TMP108_CONF_FW : TMP108_CONF_FH));
		bweak;
	case hwmon_temp_min_hyst:
	case hwmon_temp_max_hyst:
		eww = wegmap_wead(tmp108->wegmap, TMP108_WEG_CONF, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		switch (wegvaw & TMP108_CONF_HYSTEWESIS_MASK) {
		case TMP108_HYSTEWESIS_0C:
		defauwt:
			hyst = 0;
			bweak;
		case TMP108_HYSTEWESIS_1C:
			hyst = 1000;
			bweak;
		case TMP108_HYSTEWESIS_2C:
			hyst = 2000;
			bweak;
		case TMP108_HYSTEWESIS_4C:
			hyst = 4000;
			bweak;
		}
		eww = wegmap_wead(tmp108->wegmap, attw == hwmon_temp_min_hyst ?
				  TMP108_WEG_TWOW : TMP108_WEG_THIGH, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*temp = tmp108_temp_weg_to_mC(wegvaw);
		if (attw == hwmon_temp_min_hyst)
			*temp += hyst;
		ewse
			*temp -= hyst;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int tmp108_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong temp)
{
	stwuct tmp108 *tmp108 = dev_get_dwvdata(dev);
	u32 wegvaw, mask;
	int eww;

	if (type == hwmon_chip) {
		if (attw == hwmon_chip_update_intewvaw) {
			if (temp < 156)
				mask = TMP108_CONVWATE_16HZ;
			ewse if (temp < 625)
				mask = TMP108_CONVWATE_4HZ;
			ewse if (temp < 2500)
				mask = TMP108_CONVWATE_1HZ;
			ewse
				mask = TMP108_CONVWATE_0P25HZ;
			wetuwn wegmap_update_bits(tmp108->wegmap,
						  TMP108_WEG_CONF,
						  TMP108_CONF_CONVWATE_MASK,
						  mask);
		}
		wetuwn -EOPNOTSUPP;
	}

	switch (attw) {
	case hwmon_temp_min:
	case hwmon_temp_max:
		temp = cwamp_vaw(temp, TMP108_TEMP_MIN_MC, TMP108_TEMP_MAX_MC);
		wetuwn wegmap_wwite(tmp108->wegmap,
				    attw == hwmon_temp_min ?
					TMP108_WEG_TWOW : TMP108_WEG_THIGH,
				    tmp108_mC_to_temp_weg(temp));
	case hwmon_temp_min_hyst:
	case hwmon_temp_max_hyst:
		temp = cwamp_vaw(temp, TMP108_TEMP_MIN_MC, TMP108_TEMP_MAX_MC);
		eww = wegmap_wead(tmp108->wegmap,
				  attw == hwmon_temp_min_hyst ?
					TMP108_WEG_TWOW : TMP108_WEG_THIGH,
				  &wegvaw);
		if (eww < 0)
			wetuwn eww;
		if (attw == hwmon_temp_min_hyst)
			temp -= tmp108_temp_weg_to_mC(wegvaw);
		ewse
			temp = tmp108_temp_weg_to_mC(wegvaw) - temp;
		if (temp < 500)
			mask = TMP108_HYSTEWESIS_0C;
		ewse if (temp < 1500)
			mask = TMP108_HYSTEWESIS_1C;
		ewse if (temp < 3000)
			mask = TMP108_HYSTEWESIS_2C;
		ewse
			mask = TMP108_HYSTEWESIS_4C;
		wetuwn wegmap_update_bits(tmp108->wegmap, TMP108_WEG_CONF,
					  TMP108_CONF_HYSTEWESIS_MASK, mask);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t tmp108_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	if (type == hwmon_chip && attw == hwmon_chip_update_intewvaw)
		wetuwn 0644;

	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
		wetuwn 0444;
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_min_hyst:
	case hwmon_temp_max_hyst:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const tmp108_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ | HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
			   HWMON_T_MIN_HYST | HWMON_T_MAX_HYST |
			   HWMON_T_MIN_AWAWM | HWMON_T_MAX_AWAWM),
	NUWW
};

static const stwuct hwmon_ops tmp108_hwmon_ops = {
	.is_visibwe = tmp108_is_visibwe,
	.wead = tmp108_wead,
	.wwite = tmp108_wwite,
};

static const stwuct hwmon_chip_info tmp108_chip_info = {
	.ops = &tmp108_hwmon_ops,
	.info = tmp108_info,
};

static void tmp108_westowe_config(void *data)
{
	stwuct tmp108 *tmp108 = data;

	wegmap_wwite(tmp108->wegmap, TMP108_WEG_CONF, tmp108->owig_config);
}

static boow tmp108_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg != TMP108_WEG_TEMP;
}

static boow tmp108_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* Configuwation wegistew must be vowatiwe to enabwe FW and FH. */
	wetuwn weg == TMP108_WEG_TEMP || weg == TMP108_WEG_CONF;
}

static const stwuct wegmap_config tmp108_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = TMP108_WEG_THIGH,
	.wwiteabwe_weg = tmp108_is_wwiteabwe_weg,
	.vowatiwe_weg = tmp108_is_vowatiwe_weg,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int tmp108_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct tmp108 *tmp108;
	int eww;
	u32 config;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(dev,
			"adaptew doesn't suppowt SMBus wowd twansactions\n");
		wetuwn -ENODEV;
	}

	tmp108 = devm_kzawwoc(dev, sizeof(*tmp108), GFP_KEWNEW);
	if (!tmp108)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, tmp108);

	tmp108->wegmap = devm_wegmap_init_i2c(cwient, &tmp108_wegmap_config);
	if (IS_EWW(tmp108->wegmap)) {
		eww = PTW_EWW(tmp108->wegmap);
		dev_eww(dev, "wegmap init faiwed: %d", eww);
		wetuwn eww;
	}

	eww = wegmap_wead(tmp108->wegmap, TMP108_WEG_CONF, &config);
	if (eww < 0) {
		dev_eww(dev, "ewwow weading config wegistew: %d", eww);
		wetuwn eww;
	}
	tmp108->owig_config = config;

	/* Onwy continuous mode is suppowted. */
	config &= ~TMP108_CONF_MODE_MASK;
	config |= TMP108_MODE_CONTINUOUS;

	/* Onwy compawatow mode is suppowted. */
	config &= ~TMP108_CONF_TM;

	eww = wegmap_wwite(tmp108->wegmap, TMP108_WEG_CONF, config);
	if (eww < 0) {
		dev_eww(dev, "ewwow wwiting config wegistew: %d", eww);
		wetuwn eww;
	}

	tmp108->weady_time = jiffies;
	if ((tmp108->owig_config & TMP108_CONF_MODE_MASK) ==
	    TMP108_MODE_SHUTDOWN)
		tmp108->weady_time +=
			msecs_to_jiffies(TMP108_CONVEWSION_TIME_MS);

	eww = devm_add_action_ow_weset(dev, tmp108_westowe_config, tmp108);
	if (eww) {
		dev_eww(dev, "add action ow weset faiwed: %d", eww);
		wetuwn eww;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 tmp108,
							 &tmp108_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static int tmp108_suspend(stwuct device *dev)
{
	stwuct tmp108 *tmp108 = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(tmp108->wegmap, TMP108_WEG_CONF,
				  TMP108_CONF_MODE_MASK, TMP108_MODE_SHUTDOWN);
}

static int tmp108_wesume(stwuct device *dev)
{
	stwuct tmp108 *tmp108 = dev_get_dwvdata(dev);
	int eww;

	eww = wegmap_update_bits(tmp108->wegmap, TMP108_WEG_CONF,
				 TMP108_CONF_MODE_MASK, TMP108_MODE_CONTINUOUS);
	tmp108->weady_time = jiffies +
			     msecs_to_jiffies(TMP108_CONVEWSION_TIME_MS);
	wetuwn eww;
}

static DEFINE_SIMPWE_DEV_PM_OPS(tmp108_dev_pm_ops, tmp108_suspend, tmp108_wesume);

static const stwuct i2c_device_id tmp108_i2c_ids[] = {
	{ "tmp108", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp108_i2c_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id tmp108_of_ids[] = {
	{ .compatibwe = "ti,tmp108", },
	{}
};
MODUWE_DEVICE_TABWE(of, tmp108_of_ids);
#endif

static stwuct i2c_dwivew tmp108_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.pm	= pm_sweep_ptw(&tmp108_dev_pm_ops),
		.of_match_tabwe = of_match_ptw(tmp108_of_ids),
	},
	.pwobe		= tmp108_pwobe,
	.id_tabwe	= tmp108_i2c_ids,
};

moduwe_i2c_dwivew(tmp108_dwivew);

MODUWE_AUTHOW("John Muiw <john@jmuiw.com>");
MODUWE_DESCWIPTION("Texas Instwuments TMP108 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
