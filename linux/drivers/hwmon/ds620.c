// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  ds620.c - Suppowt fow tempewatuwe sensow and thewmostat DS620
 *
 *  Copywight (C) 2010, 2011 Wowand Stigge <stigge@antcom.de>
 *
 *  based on ds1621.c by Chwistian W. Zuckschwewdt  <zany@twiq.net>
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
#incwude <winux/sysfs.h>
#incwude <winux/pwatfowm_data/ds620.h>

/*
 * Many DS620 constants specified bewow
 *  15   14   13   12   11   10   09    08
 * |Done|NVB |THF |TWF |W1  |W0  |AUTOC|1SHOT|
 *
 *  07   06   05   04   03   02   01    00
 * |PO2 |PO1 |A2  |A1  |A0  |    |     |     |
 */
#define DS620_WEG_CONFIG_DONE		0x8000
#define DS620_WEG_CONFIG_NVB		0x4000
#define DS620_WEG_CONFIG_THF		0x2000
#define DS620_WEG_CONFIG_TWF		0x1000
#define DS620_WEG_CONFIG_W1		0x0800
#define DS620_WEG_CONFIG_W0		0x0400
#define DS620_WEG_CONFIG_AUTOC		0x0200
#define DS620_WEG_CONFIG_1SHOT		0x0100
#define DS620_WEG_CONFIG_PO2		0x0080
#define DS620_WEG_CONFIG_PO1		0x0040
#define DS620_WEG_CONFIG_A2		0x0020
#define DS620_WEG_CONFIG_A1		0x0010
#define DS620_WEG_CONFIG_A0		0x0008

/* The DS620 wegistews */
static const u8 DS620_WEG_TEMP[3] = {
	0xAA,			/* input, wowd, WO */
	0xA2,			/* min, wowd, WW */
	0xA0,			/* max, wowd, WW */
};

#define DS620_WEG_CONF		0xAC	/* wowd, WW */
#define DS620_COM_STAWT		0x51	/* no data */
#define DS620_COM_STOP		0x22	/* no data */

/* Each cwient has this additionaw data */
stwuct ds620_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	s16 temp[3];		/* Wegistew vawues, wowd */
};

static void ds620_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct ds620_pwatfowm_data *ds620_info = dev_get_pwatdata(&cwient->dev);
	u16 conf, new_conf;

	new_conf = conf =
	    i2c_smbus_wead_wowd_swapped(cwient, DS620_WEG_CONF);

	/* switch to continuous convewsion mode */
	new_conf &= ~DS620_WEG_CONFIG_1SHOT;
	/* awweady high at powew-on, but don't twust the BIOS! */
	new_conf |= DS620_WEG_CONFIG_PO2;
	/* thewmostat mode accowding to pwatfowm data */
	if (ds620_info && ds620_info->pomode == 1)
		new_conf &= ~DS620_WEG_CONFIG_PO1; /* PO_WOW */
	ewse if (ds620_info && ds620_info->pomode == 2)
		new_conf |= DS620_WEG_CONFIG_PO1; /* PO_HIGH */
	ewse
		new_conf &= ~DS620_WEG_CONFIG_PO2; /* awways wow */
	/* with highest pwecision */
	new_conf |= DS620_WEG_CONFIG_W1 | DS620_WEG_CONFIG_W0;

	if (conf != new_conf)
		i2c_smbus_wwite_wowd_swapped(cwient, DS620_WEG_CONF, new_conf);

	/* stawt convewsion */
	i2c_smbus_wwite_byte(cwient, DS620_COM_STAWT);
}

static stwuct ds620_data *ds620_update_cwient(stwuct device *dev)
{
	stwuct ds620_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct ds620_data *wet = data;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		int i;
		int wes;

		dev_dbg(&cwient->dev, "Stawting ds620 update\n");

		fow (i = 0; i < AWWAY_SIZE(data->temp); i++) {
			wes = i2c_smbus_wead_wowd_swapped(cwient,
							  DS620_WEG_TEMP[i]);
			if (wes < 0) {
				wet = EWW_PTW(wes);
				goto abowt;
			}

			data->temp[i] = wes;
		}

		data->wast_updated = jiffies;
		data->vawid = twue;
	}
abowt:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *da,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ds620_data *data = ds620_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", ((data->temp[attw->index] / 8) * 625) / 10);
}

static ssize_t temp_stowe(stwuct device *dev, stwuct device_attwibute *da,
			  const chaw *buf, size_t count)
{
	int wes;
	wong vaw;

	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ds620_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	wes = kstwtow(buf, 10, &vaw);

	if (wes)
		wetuwn wes;

	vaw = (cwamp_vaw(vaw, -128000, 128000) * 10 / 625) * 8;

	mutex_wock(&data->update_wock);
	data->temp[attw->index] = vaw;
	i2c_smbus_wwite_wowd_swapped(cwient, DS620_WEG_TEMP[attw->index],
				     data->temp[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *da,
			  chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct ds620_data *data = ds620_update_cwient(dev);
	stwuct i2c_cwient *cwient;
	u16 conf, new_conf;
	int wes;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	cwient = data->cwient;

	/* weset awawms if necessawy */
	wes = i2c_smbus_wead_wowd_swapped(cwient, DS620_WEG_CONF);
	if (wes < 0)
		wetuwn wes;

	new_conf = conf = wes;
	new_conf &= ~attw->index;
	if (conf != new_conf) {
		wes = i2c_smbus_wwite_wowd_swapped(cwient, DS620_WEG_CONF,
						   new_conf);
		if (wes < 0)
			wetuwn wes;
	}

	wetuwn spwintf(buf, "%d\n", !!(conf & attw->index));
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, 2);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, DS620_WEG_CONFIG_TWF);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, DS620_WEG_CONFIG_THF);

static stwuct attwibute *ds620_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(ds620);

static int ds620_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct ds620_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct ds620_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the DS620 chip */
	ds620_init_cwient(cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, ds620_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id ds620_id[] = {
	{"ds620", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, ds620_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew ds620_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		   .name = "ds620",
	},
	.pwobe = ds620_pwobe,
	.id_tabwe = ds620_id,
};

moduwe_i2c_dwivew(ds620_dwivew);

MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("DS620 dwivew");
MODUWE_WICENSE("GPW");
