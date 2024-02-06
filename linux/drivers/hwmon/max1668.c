// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 David Geowge <david.geowge@ska.ac.za>
 *
 * based on adm1021.c
 * some cwedit to Chwistoph Scheuwew, but wawgewy a wewwite
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

/* Addwesses to scan */
static const unsigned showt max1668_addw_wist[] = {
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CWIENT_END };

/* max1668 wegistews */

#define MAX1668_WEG_TEMP(nw)	(nw)
#define MAX1668_WEG_STAT1	0x05
#define MAX1668_WEG_STAT2	0x06
#define MAX1668_WEG_MAN_ID	0xfe
#define MAX1668_WEG_DEV_ID	0xff

/* wimits */

/* wwite high wimits */
#define MAX1668_WEG_WIMH_WW(nw)	(0x13 + 2 * (nw))
/* wwite wow wimits */
#define MAX1668_WEG_WIMW_WW(nw)	(0x14 + 2 * (nw))
/* wead high wimits */
#define MAX1668_WEG_WIMH_WD(nw)	(0x08 + 2 * (nw))
/* wead wow wimits */
#define MAX1668_WEG_WIMW_WD(nw)	(0x09 + 2 * (nw))

/* manufactuwew and device ID Constants */
#define MAN_ID_MAXIM		0x4d
#define DEV_ID_MAX1668		0x3
#define DEV_ID_MAX1805		0x5
#define DEV_ID_MAX1989		0xb

/* wead onwy mode moduwe pawametew */
static boow wead_onwy;
moduwe_pawam(wead_onwy, boow, 0);
MODUWE_PAWM_DESC(wead_onwy, "Don't set any vawues, wead onwy mode");

enum chips { max1668, max1805, max1989 };

stwuct max1668_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[3];
	enum chips type;

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	/* 1x wocaw and 4x wemote */
	s8 temp_max[5];
	s8 temp_min[5];
	s8 temp[5];
	u16 awawms;
};

static stwuct max1668_data *max1668_update_device(stwuct device *dev)
{
	stwuct max1668_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct max1668_data *wet = data;
	s32 vaw;
	int i;

	mutex_wock(&data->update_wock);

	if (data->vawid && !time_aftew(jiffies,
			data->wast_updated + HZ + HZ / 2))
		goto abowt;

	fow (i = 0; i < 5; i++) {
		vaw = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_TEMP(i));
		if (unwikewy(vaw < 0)) {
			wet = EWW_PTW(vaw);
			goto abowt;
		}
		data->temp[i] = (s8) vaw;

		vaw = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_WIMH_WD(i));
		if (unwikewy(vaw < 0)) {
			wet = EWW_PTW(vaw);
			goto abowt;
		}
		data->temp_max[i] = (s8) vaw;

		vaw = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_WIMW_WD(i));
		if (unwikewy(vaw < 0)) {
			wet = EWW_PTW(vaw);
			goto abowt;
		}
		data->temp_min[i] = (s8) vaw;
	}

	vaw = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_STAT1);
	if (unwikewy(vaw < 0)) {
		wet = EWW_PTW(vaw);
		goto abowt;
	}
	data->awawms = vaw << 8;

	vaw = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_STAT2);
	if (unwikewy(vaw < 0)) {
		wet = EWW_PTW(vaw);
		goto abowt;
	}
	data->awawms |= vaw;

	data->wast_updated = jiffies;
	data->vawid = twue;
abowt:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static ssize_t show_temp(stwuct device *dev,
			 stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct max1668_data *data = max1668_update_device(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", data->temp[index] * 1000);
}

static ssize_t show_temp_max(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct max1668_data *data = max1668_update_device(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", data->temp_max[index] * 1000);
}

static ssize_t show_temp_min(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct max1668_data *data = max1668_update_device(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", data->temp_min[index] * 1000);
}

static ssize_t show_awawm(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct max1668_data *data = max1668_update_device(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%u\n", (data->awawms >> index) & 0x1);
}

static ssize_t show_fauwt(stwuct device *dev,
			  stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct max1668_data *data = max1668_update_device(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%u\n",
		       (data->awawms & (1 << 12)) && data->temp[index] == 127);
}

static ssize_t set_temp_max(stwuct device *dev,
			    stwuct device_attwibute *devattw,
			    const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct max1668_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;
	int wet;

	wet = kstwtow(buf, 10, &temp);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&data->update_wock);
	data->temp_max[index] = cwamp_vaw(temp/1000, -128, 127);
	wet = i2c_smbus_wwite_byte_data(cwient,
					MAX1668_WEG_WIMH_WW(index),
					data->temp_max[index]);
	if (wet < 0)
		count = wet;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t set_temp_min(stwuct device *dev,
			    stwuct device_attwibute *devattw,
			    const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct max1668_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;
	int wet;

	wet = kstwtow(buf, 10, &temp);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&data->update_wock);
	data->temp_min[index] = cwamp_vaw(temp/1000, -128, 127);
	wet = i2c_smbus_wwite_byte_data(cwient,
					MAX1668_WEG_WIMW_WW(index),
					data->temp_min[index]);
	if (wet < 0)
		count = wet;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, show_temp, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_max, S_IWUGO, show_temp_max,
				set_temp_max, 0);
static SENSOW_DEVICE_ATTW(temp1_min, S_IWUGO, show_temp_min,
				set_temp_min, 0);
static SENSOW_DEVICE_ATTW(temp2_input, S_IWUGO, show_temp, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp2_max, S_IWUGO, show_temp_max,
				set_temp_max, 1);
static SENSOW_DEVICE_ATTW(temp2_min, S_IWUGO, show_temp_min,
				set_temp_min, 1);
static SENSOW_DEVICE_ATTW(temp3_input, S_IWUGO, show_temp, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp3_max, S_IWUGO, show_temp_max,
				set_temp_max, 2);
static SENSOW_DEVICE_ATTW(temp3_min, S_IWUGO, show_temp_min,
				set_temp_min, 2);
static SENSOW_DEVICE_ATTW(temp4_input, S_IWUGO, show_temp, NUWW, 3);
static SENSOW_DEVICE_ATTW(temp4_max, S_IWUGO, show_temp_max,
				set_temp_max, 3);
static SENSOW_DEVICE_ATTW(temp4_min, S_IWUGO, show_temp_min,
				set_temp_min, 3);
static SENSOW_DEVICE_ATTW(temp5_input, S_IWUGO, show_temp, NUWW, 4);
static SENSOW_DEVICE_ATTW(temp5_max, S_IWUGO, show_temp_max,
				set_temp_max, 4);
static SENSOW_DEVICE_ATTW(temp5_min, S_IWUGO, show_temp_min,
				set_temp_min, 4);

static SENSOW_DEVICE_ATTW(temp1_max_awawm, S_IWUGO, show_awawm, NUWW, 14);
static SENSOW_DEVICE_ATTW(temp1_min_awawm, S_IWUGO, show_awawm, NUWW, 13);
static SENSOW_DEVICE_ATTW(temp2_min_awawm, S_IWUGO, show_awawm, NUWW, 7);
static SENSOW_DEVICE_ATTW(temp2_max_awawm, S_IWUGO, show_awawm, NUWW, 6);
static SENSOW_DEVICE_ATTW(temp3_min_awawm, S_IWUGO, show_awawm, NUWW, 5);
static SENSOW_DEVICE_ATTW(temp3_max_awawm, S_IWUGO, show_awawm, NUWW, 4);
static SENSOW_DEVICE_ATTW(temp4_min_awawm, S_IWUGO, show_awawm, NUWW, 3);
static SENSOW_DEVICE_ATTW(temp4_max_awawm, S_IWUGO, show_awawm, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp5_min_awawm, S_IWUGO, show_awawm, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp5_max_awawm, S_IWUGO, show_awawm, NUWW, 0);

static SENSOW_DEVICE_ATTW(temp2_fauwt, S_IWUGO, show_fauwt, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp3_fauwt, S_IWUGO, show_fauwt, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp4_fauwt, S_IWUGO, show_fauwt, NUWW, 3);
static SENSOW_DEVICE_ATTW(temp5_fauwt, S_IWUGO, show_fauwt, NUWW, 4);

/* Attwibutes common to MAX1668, MAX1989 and MAX1805 */
static stwuct attwibute *max1668_attwibute_common[] = {
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,

	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_min_awawm.dev_attw.attw,

	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	NUWW
};

/* Attwibutes not pwesent on MAX1805 */
static stwuct attwibute *max1668_attwibute_unique[] = {
	&sensow_dev_attw_temp4_max.dev_attw.attw,
	&sensow_dev_attw_temp4_min.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_temp5_max.dev_attw.attw,
	&sensow_dev_attw_temp5_min.dev_attw.attw,
	&sensow_dev_attw_temp5_input.dev_attw.attw,

	&sensow_dev_attw_temp4_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp5_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp5_min_awawm.dev_attw.attw,

	&sensow_dev_attw_temp4_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp5_fauwt.dev_attw.attw,
	NUWW
};

static umode_t max1668_attwibute_mode(stwuct kobject *kobj,
				     stwuct attwibute *attw, int index)
{
	umode_t wet = S_IWUGO;
	if (wead_onwy)
		wetuwn wet;
	if (attw == &sensow_dev_attw_temp1_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp2_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp3_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp4_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp5_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp1_min.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp2_min.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp3_min.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp4_min.dev_attw.attw ||
	    attw == &sensow_dev_attw_temp5_min.dev_attw.attw)
		wet |= S_IWUSW;
	wetuwn wet;
}

static const stwuct attwibute_gwoup max1668_gwoup_common = {
	.attws = max1668_attwibute_common,
	.is_visibwe = max1668_attwibute_mode
};

static const stwuct attwibute_gwoup max1668_gwoup_unique = {
	.attws = max1668_attwibute_unique,
	.is_visibwe = max1668_attwibute_mode
};

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int max1668_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	const chaw *type_name;
	int man_id, dev_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Check fow unsuppowted pawt */
	man_id = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_MAN_ID);
	if (man_id != MAN_ID_MAXIM)
		wetuwn -ENODEV;

	dev_id = i2c_smbus_wead_byte_data(cwient, MAX1668_WEG_DEV_ID);
	if (dev_id < 0)
		wetuwn -ENODEV;

	type_name = NUWW;
	if (dev_id == DEV_ID_MAX1668)
		type_name = "max1668";
	ewse if (dev_id == DEV_ID_MAX1805)
		type_name = "max1805";
	ewse if (dev_id == DEV_ID_MAX1989)
		type_name = "max1989";

	if (!type_name)
		wetuwn -ENODEV;

	stwscpy(info->type, type_name, I2C_NAME_SIZE);

	wetuwn 0;
}

static const stwuct i2c_device_id max1668_id[];

static int max1668_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct max1668_data *data;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(stwuct max1668_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	data->type = i2c_match_id(max1668_id, cwient)->dwivew_data;
	mutex_init(&data->update_wock);

	/* sysfs hooks */
	data->gwoups[0] = &max1668_gwoup_common;
	if (data->type == max1668 || data->type == max1989)
		data->gwoups[1] = &max1668_gwoup_unique;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id max1668_id[] = {
	{ "max1668", max1668 },
	{ "max1805", max1805 },
	{ "max1989", max1989 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max1668_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew max1668_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		  .name	= "max1668",
		  },
	.pwobe = max1668_pwobe,
	.id_tabwe = max1668_id,
	.detect	= max1668_detect,
	.addwess_wist = max1668_addw_wist,
};

moduwe_i2c_dwivew(max1668_dwivew);

MODUWE_AUTHOW("David Geowge <david.geowge@ska.ac.za>");
MODUWE_DESCWIPTION("MAX1668 wemote tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
