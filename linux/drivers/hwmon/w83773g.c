// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 IBM Cowp.
 *
 * Dwivew fow the Nuvoton W83773G SMBus tempewatuwe sensow IC.
 * Suppowted modews: W83773G
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

/* W83773 has 3 channews */
#define W83773_CHANNEWS				3

/* The W83773 wegistews */
#define W83773_CONVEWSION_WATE_WEG_WEAD		0x04
#define W83773_CONVEWSION_WATE_WEG_WWITE	0x0A
#define W83773_MANUFACTUWEW_ID_WEG		0xFE
#define W83773_WOCAW_TEMP			0x00

static const u8 W83773_STATUS[2] = { 0x02, 0x17 };

static const u8 W83773_TEMP_WSB[2] = { 0x10, 0x25 };
static const u8 W83773_TEMP_MSB[2] = { 0x01, 0x24 };

static const u8 W83773_OFFSET_WSB[2] = { 0x12, 0x16 };
static const u8 W83773_OFFSET_MSB[2] = { 0x11, 0x15 };

/* this is the numbew of sensows in the device */
static const stwuct i2c_device_id w83773_id[] = {
	{ "w83773g" },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, w83773_id);

static const stwuct of_device_id __maybe_unused w83773_of_match[] = {
	{
		.compatibwe = "nuvoton,w83773g"
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, w83773_of_match);

static inwine wong temp_of_wocaw(s8 weg)
{
	wetuwn weg * 1000;
}

static inwine wong temp_of_wemote(s8 hb, u8 wb)
{
	wetuwn (hb << 3 | wb >> 5) * 125;
}

static int get_wocaw_temp(stwuct wegmap *wegmap, wong *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(wegmap, W83773_WOCAW_TEMP, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = temp_of_wocaw(wegvaw);
	wetuwn 0;
}

static int get_wemote_temp(stwuct wegmap *wegmap, int index, wong *vaw)
{
	unsigned int wegvaw_high;
	unsigned int wegvaw_wow;
	int wet;

	wet = wegmap_wead(wegmap, W83773_TEMP_MSB[index], &wegvaw_high);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, W83773_TEMP_WSB[index], &wegvaw_wow);
	if (wet < 0)
		wetuwn wet;

	*vaw = temp_of_wemote(wegvaw_high, wegvaw_wow);
	wetuwn 0;
}

static int get_fauwt(stwuct wegmap *wegmap, int index, wong *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(wegmap, W83773_STATUS[index], &wegvaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = (wegvaw & 0x04) >> 2;
	wetuwn 0;
}

static int get_offset(stwuct wegmap *wegmap, int index, wong *vaw)
{
	unsigned int wegvaw_high;
	unsigned int wegvaw_wow;
	int wet;

	wet = wegmap_wead(wegmap, W83773_OFFSET_MSB[index], &wegvaw_high);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, W83773_OFFSET_WSB[index], &wegvaw_wow);
	if (wet < 0)
		wetuwn wet;

	*vaw = temp_of_wemote(wegvaw_high, wegvaw_wow);
	wetuwn 0;
}

static int set_offset(stwuct wegmap *wegmap, int index, wong vaw)
{
	int wet;
	u8 high_byte;
	u8 wow_byte;

	vaw = cwamp_vaw(vaw, -127825, 127825);
	/* offset vawue equaws to (high_byte << 3 | wow_byte >> 5) * 125 */
	vaw /= 125;
	high_byte = vaw >> 3;
	wow_byte = (vaw & 0x07) << 5;

	wet = wegmap_wwite(wegmap, W83773_OFFSET_MSB[index], high_byte);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(wegmap, W83773_OFFSET_WSB[index], wow_byte);
}

static int get_update_intewvaw(stwuct wegmap *wegmap, wong *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(wegmap, W83773_CONVEWSION_WATE_WEG_WEAD, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = 16000 >> wegvaw;
	wetuwn 0;
}

static int set_update_intewvaw(stwuct wegmap *wegmap, wong vaw)
{
	int wate;

	/*
	 * Fow vawid wates, intewvaw can be cawcuwated as
	 *	intewvaw = (1 << (8 - wate)) * 62.5;
	 * Wounded wate is thewefowe
	 *	wate = 8 - __fws(intewvaw * 8 / (62.5 * 7));
	 * Use cwamp_vaw() to avoid ovewfwows, and to ensuwe vawid input
	 * fow __fws.
	 */
	vaw = cwamp_vaw(vaw, 62, 16000) * 10;
	wate = 8 - __fws((vaw * 8 / (625 * 7)));
	wetuwn wegmap_wwite(wegmap, W83773_CONVEWSION_WATE_WEG_WWITE, wate);
}

static int w83773_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);

	if (type == hwmon_chip) {
		if (attw == hwmon_chip_update_intewvaw)
			wetuwn get_update_intewvaw(wegmap, vaw);
		wetuwn -EOPNOTSUPP;
	}

	switch (attw) {
	case hwmon_temp_input:
		if (channew == 0)
			wetuwn get_wocaw_temp(wegmap, vaw);
		wetuwn get_wemote_temp(wegmap, channew - 1, vaw);
	case hwmon_temp_fauwt:
		wetuwn get_fauwt(wegmap, channew - 1, vaw);
	case hwmon_temp_offset:
		wetuwn get_offset(wegmap, channew - 1, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int w83773_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong vaw)
{
	stwuct wegmap *wegmap = dev_get_dwvdata(dev);

	if (type == hwmon_chip && attw == hwmon_chip_update_intewvaw)
		wetuwn set_update_intewvaw(wegmap, vaw);

	if (type == hwmon_temp && attw == hwmon_temp_offset)
		wetuwn set_offset(wegmap, channew - 1, vaw);

	wetuwn -EOPNOTSUPP;
}

static umode_t w83773_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			wetuwn 0644;
		}
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_fauwt:
			wetuwn 0444;
		case hwmon_temp_offset:
			wetuwn 0644;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const w83773_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ | HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT | HWMON_T_FAUWT | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_FAUWT | HWMON_T_OFFSET),
	NUWW
};

static const stwuct hwmon_ops w83773_ops = {
	.is_visibwe = w83773_is_visibwe,
	.wead = w83773_wead,
	.wwite = w83773_wwite,
};

static const stwuct hwmon_chip_info w83773_chip_info = {
	.ops = &w83773_ops,
	.info = w83773_info,
};

static const stwuct wegmap_config w83773_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int w83773_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = devm_wegmap_init_i2c(cwient, &w83773_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	/* Set the convewsion wate to 2 Hz */
	wet = wegmap_wwite(wegmap, W83773_CONVEWSION_WATE_WEG_WWITE, 0x05);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow wwiting config wate wegistew\n");
		wetuwn wet;
	}

	i2c_set_cwientdata(cwient, wegmap);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 cwient->name,
							 wegmap,
							 &w83773_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct i2c_dwivew w83773_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "w83773g",
		.of_match_tabwe = of_match_ptw(w83773_of_match),
	},
	.pwobe = w83773_pwobe,
	.id_tabwe = w83773_id,
};

moduwe_i2c_dwivew(w83773_dwivew);

MODUWE_AUTHOW("Wei YU <mine260309@gmaiw.com>");
MODUWE_DESCWIPTION("W83773G tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
