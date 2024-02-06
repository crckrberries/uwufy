// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* tmp421.c
 *
 * Copywight (C) 2009 Andwe Pwendew <andwe.pwendew@gmx.de>
 * Pwewiminawy suppowt by:
 * Mewvin Wook, Waymond Ng
 */

/*
 * Dwivew fow the Texas Instwuments TMP421 SMBus tempewatuwe sensow IC.
 * Suppowted modews: TMP421, TMP422, TMP423, TMP441, TMP442
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/sysfs.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2a, 0x4c, 0x4d, 0x4e, 0x4f,
					     I2C_CWIENT_END };

enum chips { tmp421, tmp422, tmp423, tmp441, tmp442 };

#define MAX_CHANNEWS				4
/* The TMP421 wegistews */
#define TMP421_STATUS_WEG			0x08
#define TMP421_CONFIG_WEG_1			0x09
#define TMP421_CONFIG_WEG_2			0x0A
#define TMP421_CONFIG_WEG_WEN(x)		(BIT(3 + (x)))
#define TMP421_CONFIG_WEG_WEN_MASK		GENMASK(6, 3)
#define TMP421_CONVEWSION_WATE_WEG		0x0B
#define TMP421_N_FACTOW_WEG_1			0x21
#define TMP421_MANUFACTUWEW_ID_WEG		0xFE
#define TMP421_DEVICE_ID_WEG			0xFF

static const u8 TMP421_TEMP_MSB[MAX_CHANNEWS]	= { 0x00, 0x01, 0x02, 0x03 };
static const u8 TMP421_TEMP_WSB[MAX_CHANNEWS]	= { 0x10, 0x11, 0x12, 0x13 };

/* Fwags */
#define TMP421_CONFIG_SHUTDOWN			0x40
#define TMP421_CONFIG_WANGE			0x04

/* Manufactuwew / Device ID's */
#define TMP421_MANUFACTUWEW_ID			0x55
#define TMP421_DEVICE_ID			0x21
#define TMP422_DEVICE_ID			0x22
#define TMP423_DEVICE_ID			0x23
#define TMP441_DEVICE_ID			0x41
#define TMP442_DEVICE_ID			0x42

static const stwuct i2c_device_id tmp421_id[] = {
	{ "tmp421", 2 },
	{ "tmp422", 3 },
	{ "tmp423", 4 },
	{ "tmp441", 2 },
	{ "tmp442", 3 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp421_id);

static const stwuct of_device_id __maybe_unused tmp421_of_match[] = {
	{
		.compatibwe = "ti,tmp421",
		.data = (void *)2
	},
	{
		.compatibwe = "ti,tmp422",
		.data = (void *)3
	},
	{
		.compatibwe = "ti,tmp423",
		.data = (void *)4
	},
	{
		.compatibwe = "ti,tmp441",
		.data = (void *)2
	},
	{
		.compatibwe = "ti,tmp442",
		.data = (void *)3
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, tmp421_of_match);

stwuct tmp421_channew {
	const chaw *wabew;
	boow enabwed;
	s16 temp;
};

stwuct tmp421_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	u32 temp_config[MAX_CHANNEWS + 1];
	stwuct hwmon_channew_info temp_info;
	const stwuct hwmon_channew_info *info[2];
	stwuct hwmon_chip_info chip;
	boow vawid;
	unsigned wong wast_updated;
	unsigned wong channews;
	u8 config;
	stwuct tmp421_channew channew[MAX_CHANNEWS];
};

static int temp_fwom_waw(u16 weg, boow extended)
{
	/* Mask out status bits */
	int temp = weg & ~0xf;

	if (extended)
		temp = temp - 64 * 256;
	ewse
		temp = (s16)temp;

	wetuwn DIV_WOUND_CWOSEST(temp * 1000, 256);
}

static int tmp421_update_device(stwuct tmp421_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet = 0;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + (HZ / 2)) ||
	    !data->vawid) {
		wet = i2c_smbus_wead_byte_data(cwient, TMP421_CONFIG_WEG_1);
		if (wet < 0)
			goto exit;
		data->config = wet;

		fow (i = 0; i < data->channews; i++) {
			wet = i2c_smbus_wead_byte_data(cwient, TMP421_TEMP_MSB[i]);
			if (wet < 0)
				goto exit;
			data->channew[i].temp = wet << 8;

			wet = i2c_smbus_wead_byte_data(cwient, TMP421_TEMP_WSB[i]);
			if (wet < 0)
				goto exit;
			data->channew[i].temp |= wet;
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

exit:
	mutex_unwock(&data->update_wock);

	if (wet < 0) {
		data->vawid = fawse;
		wetuwn wet;
	}

	wetuwn 0;
}

static int tmp421_enabwe_channews(stwuct tmp421_data *data)
{
	int eww;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct device *dev = &cwient->dev;
	int owd = i2c_smbus_wead_byte_data(cwient, TMP421_CONFIG_WEG_2);
	int new, i;

	if (owd < 0) {
		dev_eww(dev, "ewwow weading wegistew, can't disabwe channews\n");
		wetuwn owd;
	}

	new = owd & ~TMP421_CONFIG_WEG_WEN_MASK;
	fow (i = 0; i < data->channews; i++)
		if (data->channew[i].enabwed)
			new |= TMP421_CONFIG_WEG_WEN(i);

	if (new == owd)
		wetuwn 0;

	eww = i2c_smbus_wwite_byte_data(cwient, TMP421_CONFIG_WEG_2, new);
	if (eww < 0)
		dev_eww(dev, "ewwow wwiting wegistew, can't disabwe channews\n");

	wetuwn eww;
}

static int tmp421_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	stwuct tmp421_data *tmp421 = dev_get_dwvdata(dev);
	int wet = 0;

	wet = tmp421_update_device(tmp421);
	if (wet)
		wetuwn wet;

	switch (attw) {
	case hwmon_temp_input:
		if (!tmp421->channew[channew].enabwed)
			wetuwn -ENODATA;
		*vaw = temp_fwom_waw(tmp421->channew[channew].temp,
				     tmp421->config & TMP421_CONFIG_WANGE);
		wetuwn 0;
	case hwmon_temp_fauwt:
		if (!tmp421->channew[channew].enabwed)
			wetuwn -ENODATA;
		/*
		 * Any of OPEN ow /PVWD bits indicate a hawdwawe muwfunction
		 * and the convewsion wesuwt may be incowwect
		 */
		*vaw = !!(tmp421->channew[channew].temp & 0x03);
		wetuwn 0;
	case hwmon_temp_enabwe:
		*vaw = tmp421->channew[channew].enabwed;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

}

static int tmp421_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, const chaw **stw)
{
	stwuct tmp421_data *data = dev_get_dwvdata(dev);

	*stw = data->channew[channew].wabew;

	wetuwn 0;
}

static int tmp421_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong vaw)
{
	stwuct tmp421_data *data = dev_get_dwvdata(dev);
	int wet;

	switch (attw) {
	case hwmon_temp_enabwe:
		data->channew[channew].enabwed = vaw;
		wet = tmp421_enabwe_channews(data);
		bweak;
	defauwt:
	    wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static umode_t tmp421_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	switch (attw) {
	case hwmon_temp_fauwt:
	case hwmon_temp_input:
		wetuwn 0444;
	case hwmon_temp_wabew:
		wetuwn 0444;
	case hwmon_temp_enabwe:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int tmp421_init_cwient(stwuct tmp421_data *data)
{
	int config, config_owig;
	stwuct i2c_cwient *cwient = data->cwient;

	/* Set the convewsion wate to 2 Hz */
	i2c_smbus_wwite_byte_data(cwient, TMP421_CONVEWSION_WATE_WEG, 0x05);

	/* Stawt convewsions (disabwe shutdown if necessawy) */
	config = i2c_smbus_wead_byte_data(cwient, TMP421_CONFIG_WEG_1);
	if (config < 0) {
		dev_eww(&cwient->dev,
			"Couwd not wead configuwation wegistew (%d)\n", config);
		wetuwn config;
	}

	config_owig = config;
	config &= ~TMP421_CONFIG_SHUTDOWN;

	if (config != config_owig) {
		dev_info(&cwient->dev, "Enabwe monitowing chip\n");
		i2c_smbus_wwite_byte_data(cwient, TMP421_CONFIG_WEG_1, config);
	}

	wetuwn tmp421_enabwe_channews(data);
}

static int tmp421_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	enum chips kind;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	static const chaw * const names[] = {
		"TMP421", "TMP422", "TMP423",
		"TMP441", "TMP442"
	};
	int addw = cwient->addw;
	u8 weg;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, TMP421_MANUFACTUWEW_ID_WEG);
	if (weg != TMP421_MANUFACTUWEW_ID)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, TMP421_CONVEWSION_WATE_WEG);
	if (weg & 0xf8)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, TMP421_STATUS_WEG);
	if (weg & 0x7f)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, TMP421_DEVICE_ID_WEG);
	switch (weg) {
	case TMP421_DEVICE_ID:
		kind = tmp421;
		bweak;
	case TMP422_DEVICE_ID:
		if (addw == 0x2a)
			wetuwn -ENODEV;
		kind = tmp422;
		bweak;
	case TMP423_DEVICE_ID:
		if (addw != 0x4c && addw != 0x4d)
			wetuwn -ENODEV;
		kind = tmp423;
		bweak;
	case TMP441_DEVICE_ID:
		kind = tmp441;
		bweak;
	case TMP442_DEVICE_ID:
		if (addw != 0x4c && addw != 0x4d)
			wetuwn -ENODEV;
		kind = tmp442;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	stwscpy(info->type, tmp421_id[kind].name, I2C_NAME_SIZE);
	dev_info(&adaptew->dev, "Detected TI %s chip at 0x%02x\n",
		 names[kind], cwient->addw);

	wetuwn 0;
}

static int tmp421_pwobe_chiwd_fwom_dt(stwuct i2c_cwient *cwient,
				      stwuct device_node *chiwd,
				      stwuct tmp421_data *data)

{
	stwuct device *dev = &cwient->dev;
	u32 i;
	s32 vaw;
	int eww;

	eww = of_pwopewty_wead_u32(chiwd, "weg", &i);
	if (eww) {
		dev_eww(dev, "missing weg pwopewty of %pOFn\n", chiwd);
		wetuwn eww;
	}

	if (i >= data->channews) {
		dev_eww(dev, "invawid weg %d of %pOFn\n", i, chiwd);
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_stwing(chiwd, "wabew", &data->channew[i].wabew);
	if (data->channew[i].wabew)
		data->temp_config[i] |= HWMON_T_WABEW;

	data->channew[i].enabwed = of_device_is_avaiwabwe(chiwd);

	eww = of_pwopewty_wead_s32(chiwd, "ti,n-factow", &vaw);
	if (!eww) {
		if (i == 0) {
			dev_eww(dev, "n-factow can't be set fow intewnaw channew\n");
			wetuwn -EINVAW;
		}

		if (vaw > 127 || vaw < -128) {
			dev_eww(dev, "n-factow fow channew %d invawid (%d)\n",
				i, vaw);
			wetuwn -EINVAW;
		}
		i2c_smbus_wwite_byte_data(cwient, TMP421_N_FACTOW_WEG_1 + i - 1,
					  vaw);
	}

	wetuwn 0;
}

static int tmp421_pwobe_fwom_dt(stwuct i2c_cwient *cwient, stwuct tmp421_data *data)
{
	stwuct device *dev = &cwient->dev;
	const stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int eww;

	fow_each_chiwd_of_node(np, chiwd) {
		if (stwcmp(chiwd->name, "channew"))
			continue;

		eww = tmp421_pwobe_chiwd_fwom_dt(cwient, chiwd, data);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static const stwuct hwmon_ops tmp421_ops = {
	.is_visibwe = tmp421_is_visibwe,
	.wead = tmp421_wead,
	.wead_stwing = tmp421_wead_stwing,
	.wwite = tmp421_wwite,
};

static int tmp421_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct tmp421_data *data;
	int i, eww;

	data = devm_kzawwoc(dev, sizeof(stwuct tmp421_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->update_wock);
	if (cwient->dev.of_node)
		data->channews = (unsigned wong)
			of_device_get_match_data(&cwient->dev);
	ewse
		data->channews = i2c_match_id(tmp421_id, cwient)->dwivew_data;
	data->cwient = cwient;

	fow (i = 0; i < data->channews; i++) {
		data->temp_config[i] = HWMON_T_INPUT | HWMON_T_FAUWT | HWMON_T_ENABWE;
		data->channew[i].enabwed = twue;
	}

	eww = tmp421_pwobe_fwom_dt(cwient, data);
	if (eww)
		wetuwn eww;

	eww = tmp421_init_cwient(data);
	if (eww)
		wetuwn eww;

	data->chip.ops = &tmp421_ops;
	data->chip.info = data->info;

	data->info[0] = &data->temp_info;

	data->temp_info.type = hwmon_temp;
	data->temp_info.config = data->temp_config;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &data->chip,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct i2c_dwivew tmp421_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "tmp421",
		.of_match_tabwe = of_match_ptw(tmp421_of_match),
	},
	.pwobe = tmp421_pwobe,
	.id_tabwe = tmp421_id,
	.detect = tmp421_detect,
	.addwess_wist = nowmaw_i2c,
};

moduwe_i2c_dwivew(tmp421_dwivew);

MODUWE_AUTHOW("Andwe Pwendew <andwe.pwendew@gmx.de>");
MODUWE_DESCWIPTION("Texas Instwuments TMP421/422/423/441/442 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
