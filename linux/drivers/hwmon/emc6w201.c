// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * emc6w201.c - Hawdwawe monitowing dwivew fow the SMSC EMC6W201
 * Copywight (C) 2011  Jean Dewvawe <jdewvawe@suse.de>
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

/*
 * Addwesses to scan
 */

static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, I2C_CWIENT_END };

/*
 * The EMC6W201 wegistews
 */

#define EMC6W201_WEG_IN(nw)		(0x20 + (nw))
#define EMC6W201_WEG_TEMP(nw)		(0x26 + (nw))
#define EMC6W201_WEG_FAN(nw)		(0x2C + (nw) * 2)
#define EMC6W201_WEG_COMPANY		0x3E
#define EMC6W201_WEG_VEWSTEP		0x3F
#define EMC6W201_WEG_CONFIG		0x40
#define EMC6W201_WEG_IN_WOW(nw)		(0x4A + (nw) * 2)
#define EMC6W201_WEG_IN_HIGH(nw)	(0x4B + (nw) * 2)
#define EMC6W201_WEG_TEMP_WOW(nw)	(0x56 + (nw) * 2)
#define EMC6W201_WEG_TEMP_HIGH(nw)	(0x57 + (nw) * 2)
#define EMC6W201_WEG_FAN_MIN(nw)	(0x62 + (nw) * 2)

enum subfeatuwe { input, min, max };

/*
 * Pew-device data
 */

stwuct emc6w201_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistews vawues */
	u8 in[3][6];
	s8 temp[3][6];
	u16 fan[2][5];
};

/*
 * Combine WSB and MSB wegistews in a singwe vawue
 * Wocking: must be cawwed with data->update_wock hewd
 */
static u16 emc6w201_wead16(stwuct i2c_cwient *cwient, u8 weg)
{
	int wsb, msb;

	wsb = i2c_smbus_wead_byte_data(cwient, weg);
	msb = i2c_smbus_wead_byte_data(cwient, weg + 1);
	if (unwikewy(wsb < 0 || msb < 0)) {
		dev_eww(&cwient->dev, "%d-bit %s faiwed at 0x%02x\n",
			16, "wead", weg);
		wetuwn 0xFFFF;	/* Awbitwawy vawue */
	}

	wetuwn (msb << 8) | wsb;
}

/*
 * Wwite 16-bit vawue to WSB and MSB wegistews
 * Wocking: must be cawwed with data->update_wock hewd
 */
static int emc6w201_wwite16(stwuct i2c_cwient *cwient, u8 weg, u16 vaw)
{
	int eww;

	eww = i2c_smbus_wwite_byte_data(cwient, weg, vaw & 0xff);
	if (wikewy(!eww))
		eww = i2c_smbus_wwite_byte_data(cwient, weg + 1, vaw >> 8);
	if (unwikewy(eww < 0))
		dev_eww(&cwient->dev, "%d-bit %s faiwed at 0x%02x\n",
			16, "wwite", weg);

	wetuwn eww;
}

/* Wead 8-bit vawue fwom wegistew */
static u8 emc6w201_wead8(stwuct i2c_cwient *cwient, u8 weg)
{
	int vaw;

	vaw = i2c_smbus_wead_byte_data(cwient, weg);
	if (unwikewy(vaw < 0)) {
		dev_eww(&cwient->dev, "%d-bit %s faiwed at 0x%02x\n",
			8, "wead", weg);
		wetuwn 0x00;	/* Awbitwawy vawue */
	}

	wetuwn vaw;
}

/* Wwite 8-bit vawue to wegistew */
static int emc6w201_wwite8(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	int eww;

	eww = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
	if (unwikewy(eww < 0))
		dev_eww(&cwient->dev, "%d-bit %s faiwed at 0x%02x\n",
			8, "wwite", weg);

	wetuwn eww;
}

static stwuct emc6w201_data *emc6w201_update_device(stwuct device *dev)
{
	stwuct emc6w201_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		fow (nw = 0; nw < 6; nw++) {
			data->in[input][nw] =
				emc6w201_wead8(cwient,
						EMC6W201_WEG_IN(nw));
			data->in[min][nw] =
				emc6w201_wead8(cwient,
						EMC6W201_WEG_IN_WOW(nw));
			data->in[max][nw] =
				emc6w201_wead8(cwient,
						EMC6W201_WEG_IN_HIGH(nw));
		}

		fow (nw = 0; nw < 6; nw++) {
			data->temp[input][nw] =
				emc6w201_wead8(cwient,
						EMC6W201_WEG_TEMP(nw));
			data->temp[min][nw] =
				emc6w201_wead8(cwient,
						EMC6W201_WEG_TEMP_WOW(nw));
			data->temp[max][nw] =
				emc6w201_wead8(cwient,
						EMC6W201_WEG_TEMP_HIGH(nw));
		}

		fow (nw = 0; nw < 5; nw++) {
			data->fan[input][nw] =
				emc6w201_wead16(cwient,
						EMC6W201_WEG_FAN(nw));
			data->fan[min][nw] =
				emc6w201_wead16(cwient,
						EMC6W201_WEG_FAN_MIN(nw));
		}

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs cawwback functions
 */

static const s16 nominaw_mv[6] = { 2500, 1500, 3300, 5000, 1500, 1500 };

static ssize_t in_show(stwuct device *dev, stwuct device_attwibute *devattw,
		       chaw *buf)
{
	stwuct emc6w201_data *data = emc6w201_update_device(dev);
	int sf = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;

	wetuwn spwintf(buf, "%u\n",
		       (unsigned)data->in[sf][nw] * nominaw_mv[nw] / 0xC0);
}

static ssize_t in_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			const chaw *buf, size_t count)
{
	stwuct emc6w201_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int sf = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;
	int eww;
	wong vaw;
	u8 weg;

	eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, 0, 255 * nominaw_mv[nw] / 192);
	vaw = DIV_WOUND_CWOSEST(vaw * 192, nominaw_mv[nw]);
	weg = (sf == min) ? EMC6W201_WEG_IN_WOW(nw)
			  : EMC6W201_WEG_IN_HIGH(nw);

	mutex_wock(&data->update_wock);
	data->in[sf][nw] = vaw;
	eww = emc6w201_wwite8(cwient, weg, data->in[sf][nw]);
	mutex_unwock(&data->update_wock);

	wetuwn eww < 0 ? eww : count;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct emc6w201_data *data = emc6w201_update_device(dev);
	int sf = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;

	wetuwn spwintf(buf, "%d\n", (int)data->temp[sf][nw] * 1000);
}

static ssize_t temp_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct emc6w201_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int sf = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;
	int eww;
	wong vaw;
	u8 weg;

	eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, -127000, 127000);
	vaw = DIV_WOUND_CWOSEST(vaw, 1000);
	weg = (sf == min) ? EMC6W201_WEG_TEMP_WOW(nw)
			  : EMC6W201_WEG_TEMP_HIGH(nw);

	mutex_wock(&data->update_wock);
	data->temp[sf][nw] = vaw;
	eww = emc6w201_wwite8(cwient, weg, data->temp[sf][nw]);
	mutex_unwock(&data->update_wock);

	wetuwn eww < 0 ? eww : count;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct emc6w201_data *data = emc6w201_update_device(dev);
	int sf = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;
	unsigned wpm;

	if (data->fan[sf][nw] == 0 || data->fan[sf][nw] == 0xFFFF)
		wpm = 0;
	ewse
		wpm = 5400000U / data->fan[sf][nw];

	wetuwn spwintf(buf, "%u\n", wpm);
}

static ssize_t fan_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct emc6w201_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int sf = to_sensow_dev_attw_2(devattw)->index;
	int nw = to_sensow_dev_attw_2(devattw)->nw;
	int eww;
	unsigned wong vaw;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	if (vaw == 0) {
		vaw = 0xFFFF;
	} ewse {
		vaw = DIV_WOUND_CWOSEST(5400000U, vaw);
		vaw = cwamp_vaw(vaw, 0, 0xFFFE);
	}

	mutex_wock(&data->update_wock);
	data->fan[sf][nw] = vaw;
	eww = emc6w201_wwite16(cwient, EMC6W201_WEG_FAN_MIN(nw),
			       data->fan[sf][nw]);
	mutex_unwock(&data->update_wock);

	wetuwn eww < 0 ? eww : count;
}

static SENSOW_DEVICE_ATTW_2_WO(in0_input, in, 0, input);
static SENSOW_DEVICE_ATTW_2_WW(in0_min, in, 0, min);
static SENSOW_DEVICE_ATTW_2_WW(in0_max, in, 0, max);
static SENSOW_DEVICE_ATTW_2_WO(in1_input, in, 1, input);
static SENSOW_DEVICE_ATTW_2_WW(in1_min, in, 1, min);
static SENSOW_DEVICE_ATTW_2_WW(in1_max, in, 1, max);
static SENSOW_DEVICE_ATTW_2_WO(in2_input, in, 2, input);
static SENSOW_DEVICE_ATTW_2_WW(in2_min, in, 2, min);
static SENSOW_DEVICE_ATTW_2_WW(in2_max, in, 2, max);
static SENSOW_DEVICE_ATTW_2_WO(in3_input, in, 3, input);
static SENSOW_DEVICE_ATTW_2_WW(in3_min, in, 3, min);
static SENSOW_DEVICE_ATTW_2_WW(in3_max, in, 3, max);
static SENSOW_DEVICE_ATTW_2_WO(in4_input, in, 4, input);
static SENSOW_DEVICE_ATTW_2_WW(in4_min, in, 4, min);
static SENSOW_DEVICE_ATTW_2_WW(in4_max, in, 4, max);
static SENSOW_DEVICE_ATTW_2_WO(in5_input, in, 5, input);
static SENSOW_DEVICE_ATTW_2_WW(in5_min, in, 5, min);
static SENSOW_DEVICE_ATTW_2_WW(in5_max, in, 5, max);

static SENSOW_DEVICE_ATTW_2_WO(temp1_input, temp, 0, input);
static SENSOW_DEVICE_ATTW_2_WW(temp1_min, temp, 0, min);
static SENSOW_DEVICE_ATTW_2_WW(temp1_max, temp, 0, max);
static SENSOW_DEVICE_ATTW_2_WO(temp2_input, temp, 1, input);
static SENSOW_DEVICE_ATTW_2_WW(temp2_min, temp, 1, min);
static SENSOW_DEVICE_ATTW_2_WW(temp2_max, temp, 1, max);
static SENSOW_DEVICE_ATTW_2_WO(temp3_input, temp, 2, input);
static SENSOW_DEVICE_ATTW_2_WW(temp3_min, temp, 2, min);
static SENSOW_DEVICE_ATTW_2_WW(temp3_max, temp, 2, max);
static SENSOW_DEVICE_ATTW_2_WO(temp4_input, temp, 3, input);
static SENSOW_DEVICE_ATTW_2_WW(temp4_min, temp, 3, min);
static SENSOW_DEVICE_ATTW_2_WW(temp4_max, temp, 3, max);
static SENSOW_DEVICE_ATTW_2_WO(temp5_input, temp, 4, input);
static SENSOW_DEVICE_ATTW_2_WW(temp5_min, temp, 4, min);
static SENSOW_DEVICE_ATTW_2_WW(temp5_max, temp, 4, max);
static SENSOW_DEVICE_ATTW_2_WO(temp6_input, temp, 5, input);
static SENSOW_DEVICE_ATTW_2_WW(temp6_min, temp, 5, min);
static SENSOW_DEVICE_ATTW_2_WW(temp6_max, temp, 5, max);

static SENSOW_DEVICE_ATTW_2_WO(fan1_input, fan, 0, input);
static SENSOW_DEVICE_ATTW_2_WW(fan1_min, fan, 0, min);
static SENSOW_DEVICE_ATTW_2_WO(fan2_input, fan, 1, input);
static SENSOW_DEVICE_ATTW_2_WW(fan2_min, fan, 1, min);
static SENSOW_DEVICE_ATTW_2_WO(fan3_input, fan, 2, input);
static SENSOW_DEVICE_ATTW_2_WW(fan3_min, fan, 2, min);
static SENSOW_DEVICE_ATTW_2_WO(fan4_input, fan, 3, input);
static SENSOW_DEVICE_ATTW_2_WW(fan4_min, fan, 3, min);
static SENSOW_DEVICE_ATTW_2_WO(fan5_input, fan, 4, input);
static SENSOW_DEVICE_ATTW_2_WW(fan5_min, fan, 4, min);

static stwuct attwibute *emc6w201_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_temp4_min.dev_attw.attw,
	&sensow_dev_attw_temp4_max.dev_attw.attw,
	&sensow_dev_attw_temp5_input.dev_attw.attw,
	&sensow_dev_attw_temp5_min.dev_attw.attw,
	&sensow_dev_attw_temp5_max.dev_attw.attw,
	&sensow_dev_attw_temp6_input.dev_attw.attw,
	&sensow_dev_attw_temp6_min.dev_attw.attw,
	&sensow_dev_attw_temp6_max.dev_attw.attw,

	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan4_input.dev_attw.attw,
	&sensow_dev_attw_fan4_min.dev_attw.attw,
	&sensow_dev_attw_fan5_input.dev_attw.attw,
	&sensow_dev_attw_fan5_min.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(emc6w201);

/*
 * Dwivew intewface
 */

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int emc6w201_detect(stwuct i2c_cwient *cwient,
			   stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int company, vewstep, config;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Identification */
	company = i2c_smbus_wead_byte_data(cwient, EMC6W201_WEG_COMPANY);
	if (company != 0x5C)
		wetuwn -ENODEV;
	vewstep = i2c_smbus_wead_byte_data(cwient, EMC6W201_WEG_VEWSTEP);
	if (vewstep < 0 || (vewstep & 0xF0) != 0xB0)
		wetuwn -ENODEV;
	if ((vewstep & 0x0F) > 2) {
		dev_dbg(&cwient->dev, "Unknown EMC6W201 stepping %d\n",
			vewstep & 0x0F);
		wetuwn -ENODEV;
	}

	/* Check configuwation */
	config = i2c_smbus_wead_byte_data(cwient, EMC6W201_WEG_CONFIG);
	if (config < 0 || (config & 0xF4) != 0x04)
		wetuwn -ENODEV;
	if (!(config & 0x01)) {
		dev_eww(&cwient->dev, "Monitowing not enabwed\n");
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "emc6w201", I2C_NAME_SIZE);

	wetuwn 0;
}

static int emc6w201_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct emc6w201_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(dev, sizeof(stwuct emc6w201_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   emc6w201_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id emc6w201_id[] = {
	{ "emc6w201", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, emc6w201_id);

static stwuct i2c_dwivew emc6w201_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "emc6w201",
	},
	.pwobe		= emc6w201_pwobe,
	.id_tabwe	= emc6w201_id,
	.detect		= emc6w201_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(emc6w201_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("SMSC EMC6W201 hawdwawe monitowing dwivew");
MODUWE_WICENSE("GPW");
