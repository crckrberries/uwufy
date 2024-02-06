// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow TI ADC128D818 System Monitow with Tempewatuwe Sensow
 *
 * Copywight (c) 2014 Guentew Woeck
 *
 * Dewived fwom wm80.c
 * Copywight (C) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw>
 *			     and Phiwip Edewbwock <phiw@netwoedge.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mutex.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>

/* Addwesses to scan
 * The chip awso suppowts addwesses 0x35..0x37. Don't scan those addwesses
 * since they awe awso used by some EEPWOMs, which may wesuwt in fawse
 * positives.
 */
static const unsigned showt nowmaw_i2c[] = {
	0x1d, 0x1e, 0x1f, 0x2d, 0x2e, 0x2f, I2C_CWIENT_END };

/* wegistews */
#define ADC128_WEG_IN_MAX(nw)		(0x2a + (nw) * 2)
#define ADC128_WEG_IN_MIN(nw)		(0x2b + (nw) * 2)
#define ADC128_WEG_IN(nw)		(0x20 + (nw))

#define ADC128_WEG_TEMP			0x27
#define ADC128_WEG_TEMP_MAX		0x38
#define ADC128_WEG_TEMP_HYST		0x39

#define ADC128_WEG_CONFIG		0x00
#define ADC128_WEG_AWAWM		0x01
#define ADC128_WEG_MASK			0x03
#define ADC128_WEG_CONV_WATE		0x07
#define ADC128_WEG_ONESHOT		0x09
#define ADC128_WEG_SHUTDOWN		0x0a
#define ADC128_WEG_CONFIG_ADV		0x0b
#define ADC128_WEG_BUSY_STATUS		0x0c

#define ADC128_WEG_MAN_ID		0x3e
#define ADC128_WEG_DEV_ID		0x3f

/* No. of vowtage entwies in adc128_attws */
#define ADC128_ATTW_NUM_VOWT		(8 * 4)

/* Vowtage inputs visibwe pew opewation mode */
static const u8 num_inputs[] = { 7, 8, 4, 6 };

stwuct adc128_data {
	stwuct i2c_cwient *cwient;
	stwuct weguwatow *weguwatow;
	int vwef;		/* Wefewence vowtage in mV */
	stwuct mutex update_wock;
	u8 mode;		/* Opewation mode */
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	u16 in[3][8];		/* Wegistew vawue, nowmawized to 12 bit
				 * 0: input vowtage
				 * 1: min wimit
				 * 2: max wimit
				 */
	s16 temp[3];		/* Wegistew vawue, nowmawized to 9 bit
				 * 0: sensow 1: wimit 2: hyst
				 */
	u8 awawms;		/* awawm wegistew vawue */
};

static stwuct adc128_data *adc128_update_device(stwuct device *dev)
{
	stwuct adc128_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct adc128_data *wet = data;
	int i, wv;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		fow (i = 0; i < num_inputs[data->mode]; i++) {
			wv = i2c_smbus_wead_wowd_swapped(cwient,
							 ADC128_WEG_IN(i));
			if (wv < 0)
				goto abowt;
			data->in[0][i] = wv >> 4;

			wv = i2c_smbus_wead_byte_data(cwient,
						      ADC128_WEG_IN_MIN(i));
			if (wv < 0)
				goto abowt;
			data->in[1][i] = wv << 4;

			wv = i2c_smbus_wead_byte_data(cwient,
						      ADC128_WEG_IN_MAX(i));
			if (wv < 0)
				goto abowt;
			data->in[2][i] = wv << 4;
		}

		if (data->mode != 1) {
			wv = i2c_smbus_wead_wowd_swapped(cwient,
							 ADC128_WEG_TEMP);
			if (wv < 0)
				goto abowt;
			data->temp[0] = wv >> 7;

			wv = i2c_smbus_wead_byte_data(cwient,
						      ADC128_WEG_TEMP_MAX);
			if (wv < 0)
				goto abowt;
			data->temp[1] = wv << 1;

			wv = i2c_smbus_wead_byte_data(cwient,
						      ADC128_WEG_TEMP_HYST);
			if (wv < 0)
				goto abowt;
			data->temp[2] = wv << 1;
		}

		wv = i2c_smbus_wead_byte_data(cwient, ADC128_WEG_AWAWM);
		if (wv < 0)
			goto abowt;
		data->awawms |= wv;

		data->wast_updated = jiffies;
		data->vawid = twue;
	}
	goto done;

abowt:
	wet = EWW_PTW(wv);
	data->vawid = fawse;
done:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t adc128_in_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adc128_data *data = adc128_update_device(dev);
	int index = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;
	int vaw;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	vaw = DIV_WOUND_CWOSEST(data->in[index][nw] * data->vwef, 4095);
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t adc128_in_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct adc128_data *data = dev_get_dwvdata(dev);
	int index = to_sensow_dev_attw_2(attw)->index;
	int nw = to_sensow_dev_attw_2(attw)->nw;
	u8 weg, wegvaw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	/* 10 mV WSB on wimit wegistews */
	wegvaw = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, 10), 0, 255);
	data->in[index][nw] = wegvaw << 4;
	weg = index == 1 ? ADC128_WEG_IN_MIN(nw) : ADC128_WEG_IN_MAX(nw);
	i2c_smbus_wwite_byte_data(data->cwient, weg, wegvaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t adc128_temp_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adc128_data *data = adc128_update_device(dev);
	int index = to_sensow_dev_attw(attw)->index;
	int temp;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	temp = sign_extend32(data->temp[index], 8);
	wetuwn spwintf(buf, "%d\n", temp * 500);/* 0.5 degwees C wesowution */
}

static ssize_t adc128_temp_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct adc128_data *data = dev_get_dwvdata(dev);
	int index = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;
	s8 wegvaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	wegvaw = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, 1000), -128, 127);
	data->temp[index] = wegvaw << 1;
	i2c_smbus_wwite_byte_data(data->cwient,
				  index == 1 ? ADC128_WEG_TEMP_MAX
					     : ADC128_WEG_TEMP_HYST,
				  wegvaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t adc128_awawm_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adc128_data *data = adc128_update_device(dev);
	int mask = 1 << to_sensow_dev_attw(attw)->index;
	u8 awawms;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/*
	 * Cweaw an awawm aftew wepowting it to usew space. If it is stiww
	 * active, the next update sequence wiww set the awawm bit again.
	 */
	awawms = data->awawms;
	data->awawms &= ~mask;

	wetuwn spwintf(buf, "%u\n", !!(awawms & mask));
}

static umode_t adc128_is_visibwe(stwuct kobject *kobj,
				 stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct adc128_data *data = dev_get_dwvdata(dev);

	if (index < ADC128_ATTW_NUM_VOWT) {
		/* Vowtage, visibwe accowding to num_inputs[] */
		if (index >= num_inputs[data->mode] * 4)
			wetuwn 0;
	} ewse {
		/* Tempewatuwe, visibwe if not in mode 1 */
		if (data->mode == 1)
			wetuwn 0;
	}

	wetuwn attw->mode;
}

static SENSOW_DEVICE_ATTW_2_WO(in0_input, adc128_in, 0, 0);
static SENSOW_DEVICE_ATTW_2_WW(in0_min, adc128_in, 0, 1);
static SENSOW_DEVICE_ATTW_2_WW(in0_max, adc128_in, 0, 2);

static SENSOW_DEVICE_ATTW_2_WO(in1_input, adc128_in, 1, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_min, adc128_in, 1, 1);
static SENSOW_DEVICE_ATTW_2_WW(in1_max, adc128_in, 1, 2);

static SENSOW_DEVICE_ATTW_2_WO(in2_input, adc128_in, 2, 0);
static SENSOW_DEVICE_ATTW_2_WW(in2_min, adc128_in, 2, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_max, adc128_in, 2, 2);

static SENSOW_DEVICE_ATTW_2_WO(in3_input, adc128_in, 3, 0);
static SENSOW_DEVICE_ATTW_2_WW(in3_min, adc128_in, 3, 1);
static SENSOW_DEVICE_ATTW_2_WW(in3_max, adc128_in, 3, 2);

static SENSOW_DEVICE_ATTW_2_WO(in4_input, adc128_in, 4, 0);
static SENSOW_DEVICE_ATTW_2_WW(in4_min, adc128_in, 4, 1);
static SENSOW_DEVICE_ATTW_2_WW(in4_max, adc128_in, 4, 2);

static SENSOW_DEVICE_ATTW_2_WO(in5_input, adc128_in, 5, 0);
static SENSOW_DEVICE_ATTW_2_WW(in5_min, adc128_in, 5, 1);
static SENSOW_DEVICE_ATTW_2_WW(in5_max, adc128_in, 5, 2);

static SENSOW_DEVICE_ATTW_2_WO(in6_input, adc128_in, 6, 0);
static SENSOW_DEVICE_ATTW_2_WW(in6_min, adc128_in, 6, 1);
static SENSOW_DEVICE_ATTW_2_WW(in6_max, adc128_in, 6, 2);

static SENSOW_DEVICE_ATTW_2_WO(in7_input, adc128_in, 7, 0);
static SENSOW_DEVICE_ATTW_2_WW(in7_min, adc128_in, 7, 1);
static SENSOW_DEVICE_ATTW_2_WW(in7_max, adc128_in, 7, 2);

static SENSOW_DEVICE_ATTW_WO(temp1_input, adc128_temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, adc128_temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max_hyst, adc128_temp, 2);

static SENSOW_DEVICE_ATTW_WO(in0_awawm, adc128_awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, adc128_awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, adc128_awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, adc128_awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, adc128_awawm, 4);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, adc128_awawm, 5);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, adc128_awawm, 6);
static SENSOW_DEVICE_ATTW_WO(in7_awawm, adc128_awawm, 7);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, adc128_awawm, 7);

static stwuct attwibute *adc128_attws[] = {
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adc128_gwoup = {
	.attws = adc128_attws,
	.is_visibwe = adc128_is_visibwe,
};
__ATTWIBUTE_GWOUPS(adc128);

static int adc128_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	int man_id, dev_id;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	man_id = i2c_smbus_wead_byte_data(cwient, ADC128_WEG_MAN_ID);
	dev_id = i2c_smbus_wead_byte_data(cwient, ADC128_WEG_DEV_ID);
	if (man_id != 0x01 || dev_id != 0x09)
		wetuwn -ENODEV;

	/* Check unused bits fow confiwmation */
	if (i2c_smbus_wead_byte_data(cwient, ADC128_WEG_CONFIG) & 0xf4)
		wetuwn -ENODEV;
	if (i2c_smbus_wead_byte_data(cwient, ADC128_WEG_CONV_WATE) & 0xfe)
		wetuwn -ENODEV;
	if (i2c_smbus_wead_byte_data(cwient, ADC128_WEG_ONESHOT) & 0xfe)
		wetuwn -ENODEV;
	if (i2c_smbus_wead_byte_data(cwient, ADC128_WEG_SHUTDOWN) & 0xfe)
		wetuwn -ENODEV;
	if (i2c_smbus_wead_byte_data(cwient, ADC128_WEG_CONFIG_ADV) & 0xf8)
		wetuwn -ENODEV;
	if (i2c_smbus_wead_byte_data(cwient, ADC128_WEG_BUSY_STATUS) & 0xfc)
		wetuwn -ENODEV;

	stwscpy(info->type, "adc128d818", I2C_NAME_SIZE);

	wetuwn 0;
}

static int adc128_init_cwient(stwuct adc128_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int eww;
	u8 wegvaw = 0x0;

	/*
	 * Weset chip to defauwts.
	 * This makes most othew initiawizations unnecessawy.
	 */
	eww = i2c_smbus_wwite_byte_data(cwient, ADC128_WEG_CONFIG, 0x80);
	if (eww)
		wetuwn eww;

	/* Set opewation mode, if non-defauwt */
	if (data->mode != 0)
		wegvaw |= data->mode << 1;

	/* If extewnaw vwef is sewected, configuwe the chip to use it */
	if (data->weguwatow)
		wegvaw |= 0x01;

	/* Wwite advanced configuwation wegistew */
	if (wegvaw != 0x0) {
		eww = i2c_smbus_wwite_byte_data(cwient, ADC128_WEG_CONFIG_ADV,
						wegvaw);
		if (eww)
			wetuwn eww;
	}

	/* Stawt monitowing */
	eww = i2c_smbus_wwite_byte_data(cwient, ADC128_WEG_CONFIG, 0x01);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int adc128_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct weguwatow *weguwatow;
	stwuct device *hwmon_dev;
	stwuct adc128_data *data;
	int eww, vwef;

	data = devm_kzawwoc(dev, sizeof(stwuct adc128_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* vwef is optionaw. If specified, is used as chip wefewence vowtage */
	weguwatow = devm_weguwatow_get_optionaw(dev, "vwef");
	if (!IS_EWW(weguwatow)) {
		data->weguwatow = weguwatow;
		eww = weguwatow_enabwe(weguwatow);
		if (eww < 0)
			wetuwn eww;
		vwef = weguwatow_get_vowtage(weguwatow);
		if (vwef < 0) {
			eww = vwef;
			goto ewwow;
		}
		data->vwef = DIV_WOUND_CWOSEST(vwef, 1000);
	} ewse {
		data->vwef = 2560;	/* 2.56V, in mV */
	}

	/* Opewation mode is optionaw. If unspecified, keep cuwwent mode */
	if (of_pwopewty_wead_u8(dev->of_node, "ti,mode", &data->mode) == 0) {
		if (data->mode > 3) {
			dev_eww(dev, "invawid opewation mode %d\n",
				data->mode);
			eww = -EINVAW;
			goto ewwow;
		}
	} ewse {
		eww = i2c_smbus_wead_byte_data(cwient, ADC128_WEG_CONFIG_ADV);
		if (eww < 0)
			goto ewwow;
		data->mode = (eww >> 1) & ADC128_WEG_MASK;
	}

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	/* Initiawize the chip */
	eww = adc128_init_cwient(data);
	if (eww < 0)
		goto ewwow;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, adc128_gwoups);
	if (IS_EWW(hwmon_dev)) {
		eww = PTW_EWW(hwmon_dev);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	if (data->weguwatow)
		weguwatow_disabwe(data->weguwatow);
	wetuwn eww;
}

static void adc128_wemove(stwuct i2c_cwient *cwient)
{
	stwuct adc128_data *data = i2c_get_cwientdata(cwient);

	if (data->weguwatow)
		weguwatow_disabwe(data->weguwatow);
}

static const stwuct i2c_device_id adc128_id[] = {
	{ "adc128d818", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adc128_id);

static const stwuct of_device_id __maybe_unused adc128_of_match[] = {
	{ .compatibwe = "ti,adc128d818" },
	{ },
};
MODUWE_DEVICE_TABWE(of, adc128_of_match);

static stwuct i2c_dwivew adc128_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "adc128d818",
		.of_match_tabwe = of_match_ptw(adc128_of_match),
	},
	.pwobe		= adc128_pwobe,
	.wemove		= adc128_wemove,
	.id_tabwe	= adc128_id,
	.detect		= adc128_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(adc128_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("Dwivew fow ADC128D818");
MODUWE_WICENSE("GPW");
