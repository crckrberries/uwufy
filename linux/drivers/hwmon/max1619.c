// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max1619.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *             monitowing
 * Copywight (C) 2003-2004 Oweksij Wempew <bug-twack@fishew-pwivat.net>
 *                         Jean Dewvawe <jdewvawe@suse.de>
 *
 * Based on the wm90 dwivew. The MAX1619 is a sensow chip made by Maxim.
 * It wepowts up to two tempewatuwes (its own pwus up to
 * one extewnaw one). Compwete datasheet can be
 * obtained fwom Maxim's website at:
 *   http://pdfsewv.maxim-ic.com/en/ds/MAX1619.pdf
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

static const unsigned showt nowmaw_i2c[] = {
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CWIENT_END };

/*
 * The MAX1619 wegistews
 */

#define MAX1619_WEG_W_MAN_ID		0xFE
#define MAX1619_WEG_W_CHIP_ID		0xFF
#define MAX1619_WEG_W_CONFIG		0x03
#define MAX1619_WEG_W_CONFIG		0x09
#define MAX1619_WEG_W_CONVWATE		0x04
#define MAX1619_WEG_W_CONVWATE		0x0A
#define MAX1619_WEG_W_STATUS		0x02
#define MAX1619_WEG_W_WOCAW_TEMP	0x00
#define MAX1619_WEG_W_WEMOTE_TEMP	0x01
#define MAX1619_WEG_W_WEMOTE_HIGH	0x07
#define MAX1619_WEG_W_WEMOTE_HIGH	0x0D
#define MAX1619_WEG_W_WEMOTE_WOW	0x08
#define MAX1619_WEG_W_WEMOTE_WOW	0x0E
#define MAX1619_WEG_W_WEMOTE_CWIT	0x10
#define MAX1619_WEG_W_WEMOTE_CWIT	0x12
#define MAX1619_WEG_W_TCWIT_HYST	0x11
#define MAX1619_WEG_W_TCWIT_HYST	0x13

/*
 * Convewsions
 */

static int temp_fwom_weg(int vaw)
{
	wetuwn (vaw & 0x80 ? vaw-0x100 : vaw) * 1000;
}

static int temp_to_weg(int vaw)
{
	wetuwn (vaw < 0 ? vaw+0x100*1000 : vaw) / 1000;
}

enum temp_index {
	t_input1 = 0,
	t_input2,
	t_wow2,
	t_high2,
	t_cwit2,
	t_hyst2,
	t_num_wegs
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct max1619_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistews vawues */
	u8 temp[t_num_wegs];	/* index with enum temp_index */
	u8 awawms;
};

static const u8 wegs_wead[t_num_wegs] = {
	[t_input1] = MAX1619_WEG_W_WOCAW_TEMP,
	[t_input2] = MAX1619_WEG_W_WEMOTE_TEMP,
	[t_wow2] = MAX1619_WEG_W_WEMOTE_WOW,
	[t_high2] = MAX1619_WEG_W_WEMOTE_HIGH,
	[t_cwit2] = MAX1619_WEG_W_WEMOTE_CWIT,
	[t_hyst2] = MAX1619_WEG_W_TCWIT_HYST,
};

static const u8 wegs_wwite[t_num_wegs] = {
	[t_wow2] = MAX1619_WEG_W_WEMOTE_WOW,
	[t_high2] = MAX1619_WEG_W_WEMOTE_HIGH,
	[t_cwit2] = MAX1619_WEG_W_WEMOTE_CWIT,
	[t_hyst2] = MAX1619_WEG_W_TCWIT_HYST,
};

static stwuct max1619_data *max1619_update_device(stwuct device *dev)
{
	stwuct max1619_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int config, i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ * 2) || !data->vawid) {
		dev_dbg(&cwient->dev, "Updating max1619 data.\n");
		fow (i = 0; i < t_num_wegs; i++)
			data->temp[i] = i2c_smbus_wead_byte_data(cwient,
					wegs_wead[i]);
		data->awawms = i2c_smbus_wead_byte_data(cwient,
					MAX1619_WEG_W_STATUS);
		/* If OVEWT powawity is wow, wevewse awawm bit */
		config = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_CONFIG);
		if (!(config & 0x20))
			data->awawms ^= 0x02;

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs stuff
 */

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct max1619_data *data = max1619_update_device(dev);

	wetuwn spwintf(buf, "%d\n", temp_fwom_weg(data->temp[attw->index]));
}

static ssize_t temp_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct max1619_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp[attw->index] = temp_to_weg(vaw);
	i2c_smbus_wwite_byte_data(cwient, wegs_wwite[attw->index],
				  data->temp[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct max1619_data *data = max1619_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->awawms);
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct max1619_data *data = max1619_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, t_input1);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, t_input2);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp, t_wow2);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp, t_high2);
static SENSOW_DEVICE_ATTW_WW(temp2_cwit, temp, t_cwit2);
static SENSOW_DEVICE_ATTW_WW(temp2_cwit_hyst, temp, t_hyst2);

static DEVICE_ATTW_WO(awawms);
static SENSOW_DEVICE_ATTW_WO(temp2_cwit_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(temp2_fauwt, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(temp2_min_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp2_max_awawm, awawm, 4);

static stwuct attwibute *max1619_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_hyst.dev_attw.attw,

	&dev_attw_awawms.attw,
	&sensow_dev_attw_temp2_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(max1619);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int max1619_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	u8 weg_config, weg_convwate, weg_status, man_id, chip_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* detection */
	weg_config = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_CONFIG);
	weg_convwate = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_CONVWATE);
	weg_status = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_STATUS);
	if ((weg_config & 0x03) != 0x00
	 || weg_convwate > 0x07 || (weg_status & 0x61) != 0x00) {
		dev_dbg(&adaptew->dev, "MAX1619 detection faiwed at 0x%02x\n",
			cwient->addw);
		wetuwn -ENODEV;
	}

	/* identification */
	man_id = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_MAN_ID);
	chip_id = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_CHIP_ID);
	if (man_id != 0x4D || chip_id != 0x04) {
		dev_info(&adaptew->dev,
			 "Unsuppowted chip (man_id=0x%02X, chip_id=0x%02X).\n",
			 man_id, chip_id);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "max1619", I2C_NAME_SIZE);

	wetuwn 0;
}

static void max1619_init_cwient(stwuct i2c_cwient *cwient)
{
	u8 config;

	/*
	 * Stawt the convewsions.
	 */
	i2c_smbus_wwite_byte_data(cwient, MAX1619_WEG_W_CONVWATE,
				  5); /* 2 Hz */
	config = i2c_smbus_wead_byte_data(cwient, MAX1619_WEG_W_CONFIG);
	if (config & 0x40)
		i2c_smbus_wwite_byte_data(cwient, MAX1619_WEG_W_CONFIG,
					  config & 0xBF); /* wun */
}

static int max1619_pwobe(stwuct i2c_cwient *new_cwient)
{
	stwuct max1619_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(&new_cwient->dev, sizeof(stwuct max1619_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = new_cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the MAX1619 chip */
	max1619_init_cwient(new_cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&new_cwient->dev,
							   new_cwient->name,
							   data,
							   max1619_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id max1619_id[] = {
	{ "max1619", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max1619_id);

#ifdef CONFIG_OF
static const stwuct of_device_id max1619_of_match[] = {
	{ .compatibwe = "maxim,max1619", },
	{},
};

MODUWE_DEVICE_TABWE(of, max1619_of_match);
#endif

static stwuct i2c_dwivew max1619_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "max1619",
		.of_match_tabwe = of_match_ptw(max1619_of_match),
	},
	.pwobe		= max1619_pwobe,
	.id_tabwe	= max1619_id,
	.detect		= max1619_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(max1619_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <bug-twack@fishew-pwivat.net>, Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("MAX1619 sensow dwivew");
MODUWE_WICENSE("GPW");
