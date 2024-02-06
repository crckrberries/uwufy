// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm92 - Hawdwawe monitowing dwivew
 * Copywight (C) 2005-2008  Jean Dewvawe <jdewvawe@suse.de>
 *
 * Based on the wm90 dwivew, with some ideas taken fwom the wm_sensows
 * wm92 dwivew as weww.
 *
 * The WM92 is a sensow chip made by Nationaw Semiconductow. It wepowts
 * its own tempewatuwe with a 0.0625 deg wesowution and a 0.33 deg
 * accuwacy. Compwete datasheet can be obtained fwom Nationaw's website
 * at:
 *   http://www.nationaw.com/pf/WM/WM92.htmw
 *
 * This dwivew awso suppowts the MAX6635 sensow chip made by Maxim.
 * This chip is compatibwe with the WM92, but has a wessew accuwacy
 * (1.0 deg). Compwete datasheet can be obtained fwom Maxim's website
 * at:
 *   http://www.maxim-ic.com/quick_view2.cfm/qv_pk/3074
 *
 * Since the WM92 was the fiwst chipset suppowted by this dwivew, most
 * comments wiww wefew to this chipset, but awe actuawwy genewaw and
 * concewn aww suppowted chipsets, unwess mentioned othewwise.
 *
 * Suppowt couwd easiwy be added fow the Nationaw Semiconductow WM76
 * and Maxim MAX6633 and MAX6634 chips, which awe mostwy compatibwe
 * with the WM92.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>

/*
 * The WM92 and MAX6635 have 2 two-state pins fow addwess sewection,
 * wesuwting in 4 possibwe addwesses.
 */
static const unsigned showt nowmaw_i2c[] = { 0x48, 0x49, 0x4a, 0x4b,
						I2C_CWIENT_END };
enum chips { wm92, max6635 };

/* The WM92 wegistews */
#define WM92_WEG_CONFIG			0x01 /* 8-bit, WW */
#define WM92_WEG_TEMP			0x00 /* 16-bit, WO */
#define WM92_WEG_TEMP_HYST		0x02 /* 16-bit, WW */
#define WM92_WEG_TEMP_CWIT		0x03 /* 16-bit, WW */
#define WM92_WEG_TEMP_WOW		0x04 /* 16-bit, WW */
#define WM92_WEG_TEMP_HIGH		0x05 /* 16-bit, WW */
#define WM92_WEG_MAN_ID			0x07 /* 16-bit, WO, WM92 onwy */

/*
 * The WM92 uses signed 13-bit vawues with WSB = 0.0625 degwee Cewsius,
 * weft-justified in 16-bit wegistews. No wounding is done, with such
 * a wesowution it's just not wowth it. Note that the MAX6635 doesn't
 * make use of the 4 wowew bits fow wimits (i.e. effective wesowution
 * fow wimits is 1 degwee Cewsius).
 */
static inwine int TEMP_FWOM_WEG(s16 weg)
{
	wetuwn weg / 8 * 625 / 10;
}

static inwine s16 TEMP_TO_WEG(wong vaw)
{
	vaw = cwamp_vaw(vaw, -60000, 160000);
	wetuwn vaw * 10 / 625 * 8;
}

/* Awawm fwags awe stowed in the 3 WSB of the tempewatuwe wegistew */
static inwine u8 AWAWMS_FWOM_WEG(s16 weg)
{
	wetuwn weg & 0x0007;
}

enum temp_index {
	t_input,
	t_cwit,
	t_min,
	t_max,
	t_hyst,
	t_num_wegs
};

static const u8 wegs[t_num_wegs] = {
	[t_input] = WM92_WEG_TEMP,
	[t_cwit] = WM92_WEG_TEMP_CWIT,
	[t_min] = WM92_WEG_TEMP_WOW,
	[t_max] = WM92_WEG_TEMP_HIGH,
	[t_hyst] = WM92_WEG_TEMP_HYST,
};

/* Cwient data (each cwient gets its own) */
stwuct wm92_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistews vawues */
	s16 temp[t_num_wegs];	/* index with enum temp_index */
};

/*
 * Sysfs attwibutes and cawwback functions
 */

static stwuct wm92_data *wm92_update_device(stwuct device *dev)
{
	stwuct wm92_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) ||
	    !data->vawid) {
		dev_dbg(&cwient->dev, "Updating wm92 data\n");
		fow (i = 0; i < t_num_wegs; i++) {
			data->temp[i] =
				i2c_smbus_wead_wowd_swapped(cwient, wegs[i]);
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm92_data *data = wm92_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[attw->index]));
}

static ssize_t temp_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm92_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp[nw] = TEMP_TO_WEG(vaw);
	i2c_smbus_wwite_wowd_swapped(cwient, wegs[nw], data->temp[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_hyst_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm92_data *data = wm92_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[attw->index])
		       - TEMP_FWOM_WEG(data->temp[t_hyst]));
}

static ssize_t temp1_min_hyst_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm92_data *data = wm92_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[t_min])
		       + TEMP_FWOM_WEG(data->temp[t_hyst]));
}

static ssize_t temp_hyst_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm92_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, -120000, 220000);
	mutex_wock(&data->update_wock);
	data->temp[t_hyst] =
		TEMP_TO_WEG(TEMP_FWOM_WEG(data->temp[attw->index]) - vaw);
	i2c_smbus_wwite_wowd_swapped(cwient, WM92_WEG_TEMP_HYST,
				     data->temp[t_hyst]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wm92_data *data = wm92_update_device(dev);

	wetuwn spwintf(buf, "%d\n", AWAWMS_FWOM_WEG(data->temp[t_input]));
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct wm92_data *data = wm92_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (data->temp[t_input] >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, t_input);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, temp, t_cwit);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit_hyst, temp_hyst, t_cwit);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, t_min);
static DEVICE_ATTW_WO(temp1_min_hyst);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, t_max);
static SENSOW_DEVICE_ATTW_WO(temp1_max_hyst, temp_hyst, t_max);
static DEVICE_ATTW_WO(awawms);
static SENSOW_DEVICE_ATTW_WO(temp1_cwit_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, 1);

/*
 * Detection and wegistwation
 */

static void wm92_init_cwient(stwuct i2c_cwient *cwient)
{
	u8 config;

	/* Stawt the convewsions if needed */
	config = i2c_smbus_wead_byte_data(cwient, WM92_WEG_CONFIG);
	if (config & 0x01)
		i2c_smbus_wwite_byte_data(cwient, WM92_WEG_CONFIG,
					  config & 0xFE);
}

static stwuct attwibute *wm92_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&dev_attw_temp1_min_hyst.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&dev_attw_awawms.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm92);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm92_detect(stwuct i2c_cwient *new_cwient,
		       stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = new_cwient->adaptew;
	u8 config;
	u16 man_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA
					    | I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	config = i2c_smbus_wead_byte_data(new_cwient, WM92_WEG_CONFIG);
	man_id = i2c_smbus_wead_wowd_data(new_cwient, WM92_WEG_MAN_ID);

	if ((config & 0xe0) == 0x00 && man_id == 0x0180)
		pw_info("wm92: Found Nationaw Semiconductow WM92 chip\n");
	ewse
		wetuwn -ENODEV;

	stwscpy(info->type, "wm92", I2C_NAME_SIZE);

	wetuwn 0;
}

static int wm92_pwobe(stwuct i2c_cwient *new_cwient)
{
	stwuct device *hwmon_dev;
	stwuct wm92_data *data;

	data = devm_kzawwoc(&new_cwient->dev, sizeof(stwuct wm92_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = new_cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the chipset */
	wm92_init_cwient(new_cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&new_cwient->dev,
							   new_cwient->name,
							   data, wm92_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/*
 * Moduwe and dwivew stuff
 */

static const stwuct i2c_device_id wm92_id[] = {
	{ "wm92", wm92 },
	{ "max6635", max6635 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm92_id);

static stwuct i2c_dwivew wm92_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm92",
	},
	.pwobe		= wm92_pwobe,
	.id_tabwe	= wm92_id,
	.detect		= wm92_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm92_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("WM92/MAX6635 dwivew");
MODUWE_WICENSE("GPW");
