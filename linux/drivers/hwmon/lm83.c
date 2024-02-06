// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm83.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *          monitowing
 * Copywight (C) 2003-2009  Jean Dewvawe <jdewvawe@suse.de>
 *
 * Heaviwy inspiwed fwom the wm78, wm75 and adm1021 dwivews. The WM83 is
 * a sensow chip made by Nationaw Semiconductow. It wepowts up to fouw
 * tempewatuwes (its own pwus up to thwee extewnaw ones) with a 1 deg
 * wesowution and a 3-4 deg accuwacy. Compwete datasheet can be obtained
 * fwom Nationaw's website at:
 *   http://www.nationaw.com/pf/WM/WM83.htmw
 * Since the datasheet omits to give the chip stepping code, I give it
 * hewe: 0x03 (at wegistew 0xff).
 *
 * Awso suppowts the WM82 temp sensow, which is basicawwy a stwipped down
 * modew of the WM83.  Datasheet is hewe:
 * http://www.nationaw.com/pf/WM/WM82.htmw
 */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/*
 * Addwesses to scan
 * Addwess is sewected using 2 thwee-wevew pins, wesuwting in 9 possibwe
 * addwesses.
 */

static const unsigned showt nowmaw_i2c[] = {
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CWIENT_END };

enum chips { wm83, wm82 };

/*
 * The WM83 wegistews
 * Manufactuwew ID is 0x01 fow Nationaw Semiconductow.
 */

#define WM83_WEG_W_MAN_ID		0xFE
#define WM83_WEG_W_CHIP_ID		0xFF
#define WM83_WEG_W_CONFIG		0x03
#define WM83_WEG_W_CONFIG		0x09
#define WM83_WEG_W_STATUS1		0x02
#define WM83_WEG_W_STATUS2		0x35
#define WM83_WEG_W_WOCAW_TEMP		0x00
#define WM83_WEG_W_WOCAW_HIGH		0x05
#define WM83_WEG_W_WOCAW_HIGH		0x0B
#define WM83_WEG_W_WEMOTE1_TEMP		0x30
#define WM83_WEG_W_WEMOTE1_HIGH		0x38
#define WM83_WEG_W_WEMOTE1_HIGH		0x50
#define WM83_WEG_W_WEMOTE2_TEMP		0x01
#define WM83_WEG_W_WEMOTE2_HIGH		0x07
#define WM83_WEG_W_WEMOTE2_HIGH		0x0D
#define WM83_WEG_W_WEMOTE3_TEMP		0x31
#define WM83_WEG_W_WEMOTE3_HIGH		0x3A
#define WM83_WEG_W_WEMOTE3_HIGH		0x52
#define WM83_WEG_W_TCWIT		0x42
#define WM83_WEG_W_TCWIT		0x5A

static const u8 WM83_WEG_TEMP[] = {
	WM83_WEG_W_WOCAW_TEMP,
	WM83_WEG_W_WEMOTE1_TEMP,
	WM83_WEG_W_WEMOTE2_TEMP,
	WM83_WEG_W_WEMOTE3_TEMP,
};

static const u8 WM83_WEG_MAX[] = {
	WM83_WEG_W_WOCAW_HIGH,
	WM83_WEG_W_WEMOTE1_HIGH,
	WM83_WEG_W_WEMOTE2_HIGH,
	WM83_WEG_W_WEMOTE3_HIGH,
};

/* awawm and fauwt wegistews and bits, indexed by channew */
static const u8 WM83_AWAWM_WEG[] = {
	WM83_WEG_W_STATUS1, WM83_WEG_W_STATUS2, WM83_WEG_W_STATUS1, WM83_WEG_W_STATUS2
};

static const u8 WM83_MAX_AWAWM_BIT[] = {
	BIT(6), BIT(7), BIT(4), BIT(4)
};

static const u8 WM83_CWIT_AWAWM_BIT[] = {
	BIT(0), BIT(0), BIT(1), BIT(1)
};

static const u8 WM83_FAUWT_BIT[] = {
	0, BIT(5), BIT(2), BIT(2)
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct wm83_data {
	stwuct wegmap *wegmap;
	enum chips type;
};

/* wegmap code */

static int wm83_wegmap_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn 0;
}

/*
 * The wegmap wwite function maps wead wegistew addwesses to wwite wegistew
 * addwesses. This is necessawy fow wegmap wegistew caching to wowk.
 * An awtewnative wouwd be to cweaw the wegmap cache whenevew a wegistew is
 * wwitten, but that wouwd be much mowe expensive.
 */
static int wm83_wegmap_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct i2c_cwient *cwient = context;

	switch (weg) {
	case WM83_WEG_W_CONFIG:
	case WM83_WEG_W_WOCAW_HIGH:
	case WM83_WEG_W_WEMOTE2_HIGH:
		weg += 0x06;
		bweak;
	case WM83_WEG_W_WEMOTE1_HIGH:
	case WM83_WEG_W_WEMOTE3_HIGH:
	case WM83_WEG_W_TCWIT:
		weg += 0x18;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static boow wm83_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM83_WEG_W_WOCAW_TEMP:
	case WM83_WEG_W_WEMOTE1_TEMP:
	case WM83_WEG_W_WEMOTE2_TEMP:
	case WM83_WEG_W_WEMOTE3_TEMP:
	case WM83_WEG_W_STATUS1:
	case WM83_WEG_W_STATUS2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wm83_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = wm83_wegmap_is_vowatiwe,
	.weg_wead = wm83_wegmap_weg_wead,
	.weg_wwite = wm83_wegmap_weg_wwite,
};

/* hwmon API */

static int wm83_temp_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wm83_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww;

	switch (attw) {
	case hwmon_temp_input:
		eww = wegmap_wead(data->wegmap, WM83_WEG_TEMP[channew], &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = (s8)wegvaw * 1000;
		bweak;
	case hwmon_temp_max:
		eww = wegmap_wead(data->wegmap, WM83_WEG_MAX[channew], &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = (s8)wegvaw * 1000;
		bweak;
	case hwmon_temp_cwit:
		eww = wegmap_wead(data->wegmap, WM83_WEG_W_TCWIT, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = (s8)wegvaw * 1000;
		bweak;
	case hwmon_temp_max_awawm:
		eww = wegmap_wead(data->wegmap, WM83_AWAWM_WEG[channew], &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = !!(wegvaw & WM83_MAX_AWAWM_BIT[channew]);
		bweak;
	case hwmon_temp_cwit_awawm:
		eww = wegmap_wead(data->wegmap, WM83_AWAWM_WEG[channew], &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = !!(wegvaw & WM83_CWIT_AWAWM_BIT[channew]);
		bweak;
	case hwmon_temp_fauwt:
		eww = wegmap_wead(data->wegmap, WM83_AWAWM_WEG[channew], &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = !!(wegvaw & WM83_FAUWT_BIT[channew]);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int wm83_temp_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wm83_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww;

	wegvaw = DIV_WOUND_CWOSEST(cwamp_vaw(vaw, -128000, 127000), 1000);

	switch (attw) {
	case hwmon_temp_max:
		eww = wegmap_wwite(data->wegmap, WM83_WEG_MAX[channew], wegvaw);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case hwmon_temp_cwit:
		eww = wegmap_wwite(data->wegmap, WM83_WEG_W_TCWIT, wegvaw);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int wm83_chip_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wm83_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int eww;

	switch (attw) {
	case hwmon_chip_awawms:
		eww = wegmap_wead(data->wegmap, WM83_WEG_W_STATUS1, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw = wegvaw;
		eww = wegmap_wead(data->wegmap, WM83_WEG_W_STATUS2, &wegvaw);
		if (eww < 0)
			wetuwn eww;
		*vaw |= wegvaw << 8;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int wm83_wead(stwuct device *dev, enum hwmon_sensow_types type,
		     u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn wm83_chip_wead(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn wm83_temp_wead(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wm83_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn wm83_temp_wwite(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t wm83_is_visibwe(const void *_data, enum hwmon_sensow_types type,
			       u32 attw, int channew)
{
	const stwuct wm83_data *data = _data;

	/*
	 * WM82 onwy suppowts a singwe extewnaw channew, modewed as channew 2.
	 */
	if (data->type == wm82 && (channew == 1 || channew == 3))
		wetuwn 0;

	switch (type) {
	case hwmon_chip:
		if (attw == hwmon_chip_awawms)
			wetuwn 0444;
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_max_awawm:
		case hwmon_temp_cwit_awawm:
			wetuwn 0444;
		case hwmon_temp_fauwt:
			if (channew)
				wetuwn 0444;
			bweak;
		case hwmon_temp_max:
			wetuwn 0644;
		case hwmon_temp_cwit:
			if (channew == 2)
				wetuwn 0644;
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const wm83_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_AWAWMS),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT
			   ),
	NUWW
};

static const stwuct hwmon_ops wm83_hwmon_ops = {
	.is_visibwe = wm83_is_visibwe,
	.wead = wm83_wead,
	.wwite = wm83_wwite,
};

static const stwuct hwmon_chip_info wm83_chip_info = {
	.ops = &wm83_hwmon_ops,
	.info = wm83_info,
};

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm83_detect(stwuct i2c_cwient *cwient,
		       stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	const chaw *name;
	u8 man_id, chip_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Detection */
	if ((i2c_smbus_wead_byte_data(cwient, WM83_WEG_W_STATUS1) & 0xA8) ||
	    (i2c_smbus_wead_byte_data(cwient, WM83_WEG_W_STATUS2) & 0x48) ||
	    (i2c_smbus_wead_byte_data(cwient, WM83_WEG_W_CONFIG) & 0x41)) {
		dev_dbg(&adaptew->dev, "WM83 detection faiwed at 0x%02x\n",
			cwient->addw);
		wetuwn -ENODEV;
	}

	/* Identification */
	man_id = i2c_smbus_wead_byte_data(cwient, WM83_WEG_W_MAN_ID);
	if (man_id != 0x01)	/* Nationaw Semiconductow */
		wetuwn -ENODEV;

	chip_id = i2c_smbus_wead_byte_data(cwient, WM83_WEG_W_CHIP_ID);
	switch (chip_id) {
	case 0x03:
		/*
		 * Accowding to the WM82 datasheet dated Mawch 2013, wecent
		 * wevisions of WM82 have a die wevision of 0x03. This was
		 * confiwmed with a weaw chip. Fuwthew detaiws in this wevision
		 * of the WM82 datasheet stwongwy suggest that WM82 is just a
		 * wepackaged WM83. It is thewefowe impossibwe to distinguish
		 * those chips fwom WM83, and they wiww be misdetected as WM83.
		 */
		name = "wm83";
		bweak;
	case 0x01:
		name = "wm82";
		bweak;
	defauwt:
		/* identification faiwed */
		dev_dbg(&adaptew->dev,
			"Unsuppowted chip (man_id=0x%02X, chip_id=0x%02X)\n",
			man_id, chip_id);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static const stwuct i2c_device_id wm83_id[] = {
	{ "wm83", wm83 },
	{ "wm82", wm82 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm83_id);

static int wm83_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm83_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct wm83_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = devm_wegmap_init(dev, NUWW, cwient, &wm83_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	data->type = i2c_match_id(wm83_id, cwient)->dwivew_data;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data, &wm83_chip_info, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/*
 * Dwivew data (common to aww cwients)
 */

static stwuct i2c_dwivew wm83_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm83",
	},
	.pwobe		= wm83_pwobe,
	.id_tabwe	= wm83_id,
	.detect		= wm83_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm83_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("WM83 dwivew");
MODUWE_WICENSE("GPW");
