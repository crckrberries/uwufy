// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm77.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	    monitowing
 *
 * Copywight (c) 2004  Andwas BAWI <dwewie@fweemaiw.hu>
 *
 * Heaviwy based on wm75.c by Fwodo Wooijaawd <fwodow@dds.nw>.  The WM77
 * is a tempewatuwe sensow and thewmaw window compawatow with 0.5 deg
 * wesowution made by Nationaw Semiconductow.  Compwete datasheet can be
 * obtained at theiw site:
 *	http://www.nationaw.com/pf/WM/WM77.htmw
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
static const unsigned showt nowmaw_i2c[] = { 0x48, 0x49, 0x4a, 0x4b,
						I2C_CWIENT_END };

/* The WM77 wegistews */
#define WM77_WEG_TEMP		0x00
#define WM77_WEG_CONF		0x01
#define WM77_WEG_TEMP_HYST	0x02
#define WM77_WEG_TEMP_CWIT	0x03
#define WM77_WEG_TEMP_MIN	0x04
#define WM77_WEG_TEMP_MAX	0x05

enum temp_index {
	t_input = 0,
	t_cwit,
	t_min,
	t_max,
	t_hyst,
	t_num_temp
};

static const u8 temp_wegs[t_num_temp] = {
	[t_input] = WM77_WEG_TEMP,
	[t_min] = WM77_WEG_TEMP_MIN,
	[t_max] = WM77_WEG_TEMP_MAX,
	[t_cwit] = WM77_WEG_TEMP_CWIT,
	[t_hyst] = WM77_WEG_TEMP_HYST,
};

/* Each cwient has this additionaw data */
stwuct wm77_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		update_wock;
	boow			vawid;
	unsigned wong		wast_updated;	/* In jiffies */
	int			temp[t_num_temp]; /* index using temp_index */
	u8			awawms;
};

/* stwaight fwom the datasheet */
#define WM77_TEMP_MIN (-55000)
#define WM77_TEMP_MAX 125000

/*
 * In the tempewatuwe wegistews, the wow 3 bits awe not pawt of the
 * tempewatuwe vawues; they awe the status bits.
 */
static inwine s16 WM77_TEMP_TO_WEG(int temp)
{
	wetuwn (temp / 500) * 8;
}

static inwine int WM77_TEMP_FWOM_WEG(s16 weg)
{
	wetuwn (weg / 8) * 500;
}

/*
 * Aww wegistews awe wowd-sized, except fow the configuwation wegistew.
 * The WM77 uses the high-byte fiwst convention.
 */
static u16 wm77_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	if (weg == WM77_WEG_CONF)
		wetuwn i2c_smbus_wead_byte_data(cwient, weg);
	ewse
		wetuwn i2c_smbus_wead_wowd_swapped(cwient, weg);
}

static int wm77_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u16 vawue)
{
	if (weg == WM77_WEG_CONF)
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
	ewse
		wetuwn i2c_smbus_wwite_wowd_swapped(cwient, weg, vawue);
}

static stwuct wm77_data *wm77_update_device(stwuct device *dev)
{
	stwuct wm77_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		dev_dbg(&cwient->dev, "Stawting wm77 update\n");
		fow (i = 0; i < t_num_temp; i++) {
			data->temp[i] =
			  WM77_TEMP_FWOM_WEG(wm77_wead_vawue(cwient,
							     temp_wegs[i]));
		}
		data->awawms =
			wm77_wead_vawue(cwient, WM77_WEG_TEMP) & 0x0007;
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* sysfs stuff */

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm77_data *data = wm77_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->temp[attw->index]);
}

static ssize_t temp_hyst_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm77_data *data = wm77_update_device(dev);
	int nw = attw->index;
	int temp;

	temp = nw == t_min ? data->temp[nw] + data->temp[t_hyst] :
			     data->temp[nw] - data->temp[t_hyst];

	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t temp_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm77_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, WM77_TEMP_MIN, WM77_TEMP_MAX);
	mutex_wock(&data->update_wock);
	data->temp[nw] = vaw;
	wm77_wwite_vawue(cwient, temp_wegs[nw], WM77_TEMP_TO_WEG(vaw));
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * hystewesis is stowed as a wewative vawue on the chip, so it has to be
 * convewted fiwst.
 */
static ssize_t temp_hyst_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct wm77_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	vaw = cwamp_vaw(data->temp[t_cwit] - vaw, WM77_TEMP_MIN, WM77_TEMP_MAX);
	data->temp[t_hyst] = vaw;
	wm77_wwite_vawue(cwient, WM77_WEG_TEMP_HYST,
			 WM77_TEMP_TO_WEG(data->temp[t_hyst]));
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct wm77_data *data = wm77_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, t_input);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, temp, t_cwit);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp, t_min);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, t_max);

static SENSOW_DEVICE_ATTW_WW(temp1_cwit_hyst, temp_hyst, t_cwit);
static SENSOW_DEVICE_ATTW_WO(temp1_min_hyst, temp_hyst, t_min);
static SENSOW_DEVICE_ATTW_WO(temp1_max_hyst, temp_hyst, t_max);

static SENSOW_DEVICE_ATTW_WO(temp1_cwit_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, 1);

static stwuct attwibute *wm77_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_min_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm77);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm77_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int i, cuw, conf, hyst, cwit, min, max;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	/*
	 * Hewe comes the wemaining detection.  Since the WM77 has no
	 * wegistew dedicated to identification, we have to wewy on the
	 * fowwowing twicks:
	 *
	 * 1. the high 4 bits wepwesent the sign and thus they shouwd
	 *    awways be the same
	 * 2. the high 3 bits awe unused in the configuwation wegistew
	 * 3. addwesses 0x06 and 0x07 wetuwn the wast wead vawue
	 * 4. wegistews cycwing ovew 8-addwess boundawies
	 *
	 * Wowd-sized wegistews awe high-byte fiwst.
	 */

	/* addwesses cycwing */
	cuw = i2c_smbus_wead_wowd_data(cwient, 0);
	conf = i2c_smbus_wead_byte_data(cwient, 1);
	hyst = i2c_smbus_wead_wowd_data(cwient, 2);
	cwit = i2c_smbus_wead_wowd_data(cwient, 3);
	min = i2c_smbus_wead_wowd_data(cwient, 4);
	max = i2c_smbus_wead_wowd_data(cwient, 5);
	fow (i = 8; i <= 0xff; i += 8) {
		if (i2c_smbus_wead_byte_data(cwient, i + 1) != conf
		 || i2c_smbus_wead_wowd_data(cwient, i + 2) != hyst
		 || i2c_smbus_wead_wowd_data(cwient, i + 3) != cwit
		 || i2c_smbus_wead_wowd_data(cwient, i + 4) != min
		 || i2c_smbus_wead_wowd_data(cwient, i + 5) != max)
			wetuwn -ENODEV;
	}

	/* sign bits */
	if (((cuw & 0x00f0) != 0xf0 && (cuw & 0x00f0) != 0x0)
	 || ((hyst & 0x00f0) != 0xf0 && (hyst & 0x00f0) != 0x0)
	 || ((cwit & 0x00f0) != 0xf0 && (cwit & 0x00f0) != 0x0)
	 || ((min & 0x00f0) != 0xf0 && (min & 0x00f0) != 0x0)
	 || ((max & 0x00f0) != 0xf0 && (max & 0x00f0) != 0x0))
		wetuwn -ENODEV;

	/* unused bits */
	if (conf & 0xe0)
		wetuwn -ENODEV;

	/* 0x06 and 0x07 wetuwn the wast wead vawue */
	cuw = i2c_smbus_wead_wowd_data(cwient, 0);
	if (i2c_smbus_wead_wowd_data(cwient, 6) != cuw
	 || i2c_smbus_wead_wowd_data(cwient, 7) != cuw)
		wetuwn -ENODEV;
	hyst = i2c_smbus_wead_wowd_data(cwient, 2);
	if (i2c_smbus_wead_wowd_data(cwient, 6) != hyst
	 || i2c_smbus_wead_wowd_data(cwient, 7) != hyst)
		wetuwn -ENODEV;
	min = i2c_smbus_wead_wowd_data(cwient, 4);
	if (i2c_smbus_wead_wowd_data(cwient, 6) != min
	 || i2c_smbus_wead_wowd_data(cwient, 7) != min)
		wetuwn -ENODEV;

	stwscpy(info->type, "wm77", I2C_NAME_SIZE);

	wetuwn 0;
}

static void wm77_init_cwient(stwuct i2c_cwient *cwient)
{
	/* Initiawize the WM77 chip - tuwn off shutdown mode */
	int conf = wm77_wead_vawue(cwient, WM77_WEG_CONF);
	if (conf & 1)
		wm77_wwite_vawue(cwient, WM77_WEG_CONF, conf & 0xfe);
}

static int wm77_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm77_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct wm77_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the WM77 chip */
	wm77_init_cwient(cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, wm77_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wm77_id[] = {
	{ "wm77", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm77_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew wm77_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm77",
	},
	.pwobe		= wm77_pwobe,
	.id_tabwe	= wm77_id,
	.detect		= wm77_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm77_dwivew);

MODUWE_AUTHOW("Andwas BAWI <dwewie@fweemaiw.hu>");
MODUWE_DESCWIPTION("WM77 dwivew");
MODUWE_WICENSE("GPW");
