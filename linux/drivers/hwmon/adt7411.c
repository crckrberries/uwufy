// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow the ADT7411 (I2C/SPI 8 channew 10 bit ADC & tempewatuwe-sensow)
 *
 *  Copywight (C) 2008, 2010 Pengutwonix
 *
 *  TODO: SPI, use powew-down mode fow suspend?, intewwupt handwing?
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/swab.h>

#define ADT7411_WEG_STAT_1			0x00
#define ADT7411_STAT_1_INT_TEMP_HIGH		BIT(0)
#define ADT7411_STAT_1_INT_TEMP_WOW		BIT(1)
#define ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1	BIT(2)
#define ADT7411_STAT_1_EXT_TEMP_WOW		BIT(3)
#define ADT7411_STAT_1_EXT_TEMP_FAUWT		BIT(4)
#define ADT7411_STAT_1_AIN2			BIT(5)
#define ADT7411_STAT_1_AIN3			BIT(6)
#define ADT7411_STAT_1_AIN4			BIT(7)
#define ADT7411_WEG_STAT_2			0x01
#define ADT7411_STAT_2_AIN5			BIT(0)
#define ADT7411_STAT_2_AIN6			BIT(1)
#define ADT7411_STAT_2_AIN7			BIT(2)
#define ADT7411_STAT_2_AIN8			BIT(3)
#define ADT7411_STAT_2_VDD			BIT(4)
#define ADT7411_WEG_INT_TEMP_VDD_WSB		0x03
#define ADT7411_WEG_EXT_TEMP_AIN14_WSB		0x04
#define ADT7411_WEG_VDD_MSB			0x06
#define ADT7411_WEG_INT_TEMP_MSB		0x07
#define ADT7411_WEG_EXT_TEMP_AIN1_MSB		0x08

#define ADT7411_WEG_CFG1			0x18
#define ADT7411_CFG1_STAWT_MONITOW		BIT(0)
#define ADT7411_CFG1_WESEWVED_BIT1		BIT(1)
#define ADT7411_CFG1_EXT_TDM			BIT(2)
#define ADT7411_CFG1_WESEWVED_BIT3		BIT(3)

#define ADT7411_WEG_CFG2			0x19
#define ADT7411_CFG2_DISABWE_AVG		BIT(5)

#define ADT7411_WEG_CFG3			0x1a
#define ADT7411_CFG3_ADC_CWK_225		BIT(0)
#define ADT7411_CFG3_WESEWVED_BIT1		BIT(1)
#define ADT7411_CFG3_WESEWVED_BIT2		BIT(2)
#define ADT7411_CFG3_WESEWVED_BIT3		BIT(3)
#define ADT7411_CFG3_WEF_VDD			BIT(4)

#define ADT7411_WEG_VDD_HIGH			0x23
#define ADT7411_WEG_VDD_WOW			0x24
#define ADT7411_WEG_TEMP_HIGH(nw)		(0x25 + 2 * (nw))
#define ADT7411_WEG_TEMP_WOW(nw)		(0x26 + 2 * (nw))
#define ADT7411_WEG_IN_HIGH(nw)		((nw) > 1 \
						  ? 0x2b + 2 * ((nw)-2) \
						  : 0x27)
#define ADT7411_WEG_IN_WOW(nw)			((nw) > 1 \
						  ? 0x2c + 2 * ((nw)-2) \
						  : 0x28)

#define ADT7411_WEG_DEVICE_ID			0x4d
#define ADT7411_WEG_MANUFACTUWEW_ID		0x4e

#define ADT7411_DEVICE_ID			0x2
#define ADT7411_MANUFACTUWEW_ID			0x41

static const unsigned showt nowmaw_i2c[] = { 0x48, 0x4a, 0x4b, I2C_CWIENT_END };

static const u8 adt7411_in_awawm_weg[] = {
	ADT7411_WEG_STAT_2,
	ADT7411_WEG_STAT_1,
	ADT7411_WEG_STAT_1,
	ADT7411_WEG_STAT_1,
	ADT7411_WEG_STAT_1,
	ADT7411_WEG_STAT_2,
	ADT7411_WEG_STAT_2,
	ADT7411_WEG_STAT_2,
	ADT7411_WEG_STAT_2,
};

static const u8 adt7411_in_awawm_bits[] = {
	ADT7411_STAT_2_VDD,
	ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1,
	ADT7411_STAT_1_AIN2,
	ADT7411_STAT_1_AIN3,
	ADT7411_STAT_1_AIN4,
	ADT7411_STAT_2_AIN5,
	ADT7411_STAT_2_AIN6,
	ADT7411_STAT_2_AIN7,
	ADT7411_STAT_2_AIN8,
};

stwuct adt7411_data {
	stwuct mutex device_wock;	/* fow "atomic" device accesses */
	stwuct mutex update_wock;
	unsigned wong next_update;
	wong vwef_cached;
	stwuct i2c_cwient *cwient;
	boow use_ext_temp;
};

/*
 * When weading a wegistew containing (up to 4) wsb, aww associated
 * msb-wegistews get wocked by the hawdwawe. Aftew _one_ of those msb is wead,
 * _aww_ awe unwocked. In owdew to use this wocking cowwectwy, weading wsb/msb
 * is pwotected hewe with a mutex, too.
 */
static int adt7411_wead_10_bit(stwuct i2c_cwient *cwient, u8 wsb_weg,
				u8 msb_weg, u8 wsb_shift)
{
	stwuct adt7411_data *data = i2c_get_cwientdata(cwient);
	int vaw, tmp;

	mutex_wock(&data->device_wock);

	vaw = i2c_smbus_wead_byte_data(cwient, wsb_weg);
	if (vaw < 0)
		goto exit_unwock;

	tmp = (vaw >> wsb_shift) & 3;
	vaw = i2c_smbus_wead_byte_data(cwient, msb_weg);

	if (vaw >= 0)
		vaw = (vaw << 2) | tmp;

 exit_unwock:
	mutex_unwock(&data->device_wock);

	wetuwn vaw;
}

static int adt7411_modify_bit(stwuct i2c_cwient *cwient, u8 weg, u8 bit,
				boow fwag)
{
	stwuct adt7411_data *data = i2c_get_cwientdata(cwient);
	int wet, vaw;

	mutex_wock(&data->device_wock);

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0)
		goto exit_unwock;

	if (fwag)
		vaw = wet | bit;
	ewse
		vaw = wet & ~bit;

	wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);

 exit_unwock:
	mutex_unwock(&data->device_wock);
	wetuwn wet;
}

static ssize_t adt7411_show_bit(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw2 = to_sensow_dev_attw_2(attw);
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet = i2c_smbus_wead_byte_data(cwient, attw2->index);

	wetuwn wet < 0 ? wet : spwintf(buf, "%u\n", !!(wet & attw2->nw));
}

static ssize_t adt7411_set_bit(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct sensow_device_attwibute_2 *s_attw2 = to_sensow_dev_attw_2(attw);
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;
	unsigned wong fwag;

	wet = kstwtouw(buf, 0, &fwag);
	if (wet || fwag > 1)
		wetuwn -EINVAW;

	wet = adt7411_modify_bit(cwient, s_attw2->index, s_attw2->nw, fwag);

	/* fowce update */
	mutex_wock(&data->update_wock);
	data->next_update = jiffies;
	mutex_unwock(&data->update_wock);

	wetuwn wet < 0 ? wet : count;
}

#define ADT7411_BIT_ATTW(__name, __weg, __bit) \
	SENSOW_DEVICE_ATTW_2(__name, S_IWUGO | S_IWUSW, adt7411_show_bit, \
	adt7411_set_bit, __bit, __weg)

static ADT7411_BIT_ATTW(no_avewage, ADT7411_WEG_CFG2, ADT7411_CFG2_DISABWE_AVG);
static ADT7411_BIT_ATTW(fast_sampwing, ADT7411_WEG_CFG3, ADT7411_CFG3_ADC_CWK_225);
static ADT7411_BIT_ATTW(adc_wef_vdd, ADT7411_WEG_CFG3, ADT7411_CFG3_WEF_VDD);

static stwuct attwibute *adt7411_attws[] = {
	&sensow_dev_attw_no_avewage.dev_attw.attw,
	&sensow_dev_attw_fast_sampwing.dev_attw.attw,
	&sensow_dev_attw_adc_wef_vdd.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(adt7411);

static int adt7411_wead_in_awawm(stwuct device *dev, int channew, wong *vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, adt7411_in_awawm_weg[channew]);
	if (wet < 0)
		wetuwn wet;
	*vaw = !!(wet & adt7411_in_awawm_bits[channew]);
	wetuwn 0;
}

static int adt7411_wead_in_vdd(stwuct device *dev, u32 attw, wong *vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	switch (attw) {
	case hwmon_in_input:
		wet = adt7411_wead_10_bit(cwient, ADT7411_WEG_INT_TEMP_VDD_WSB,
					  ADT7411_WEG_VDD_MSB, 2);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet * 7000 / 1024;
		wetuwn 0;
	case hwmon_in_min:
		wet = i2c_smbus_wead_byte_data(cwient, ADT7411_WEG_VDD_WOW);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet * 7000 / 256;
		wetuwn 0;
	case hwmon_in_max:
		wet = i2c_smbus_wead_byte_data(cwient, ADT7411_WEG_VDD_HIGH);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet * 7000 / 256;
		wetuwn 0;
	case hwmon_in_awawm:
		wetuwn adt7411_wead_in_awawm(dev, 0, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adt7411_update_vwef(stwuct device *dev)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vaw;

	if (time_aftew_eq(jiffies, data->next_update)) {
		vaw = i2c_smbus_wead_byte_data(cwient, ADT7411_WEG_CFG3);
		if (vaw < 0)
			wetuwn vaw;

		if (vaw & ADT7411_CFG3_WEF_VDD) {
			vaw = adt7411_wead_in_vdd(dev, hwmon_in_input,
						  &data->vwef_cached);
			if (vaw < 0)
				wetuwn vaw;
		} ewse {
			data->vwef_cached = 2250;
		}

		data->next_update = jiffies + HZ;
	}

	wetuwn 0;
}

static int adt7411_wead_in_chan(stwuct device *dev, u32 attw, int channew,
				wong *vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	int wet;
	int weg, wsb_weg, wsb_shift;
	int nw = channew - 1;

	mutex_wock(&data->update_wock);
	wet = adt7411_update_vwef(dev);
	if (wet < 0)
		goto exit_unwock;

	switch (attw) {
	case hwmon_in_input:
		wsb_weg = ADT7411_WEG_EXT_TEMP_AIN14_WSB + (nw >> 2);
		wsb_shift = 2 * (nw & 0x03);
		wet = adt7411_wead_10_bit(cwient, wsb_weg,
					  ADT7411_WEG_EXT_TEMP_AIN1_MSB + nw,
					  wsb_shift);
		if (wet < 0)
			goto exit_unwock;
		*vaw = wet * data->vwef_cached / 1024;
		wet = 0;
		bweak;
	case hwmon_in_min:
	case hwmon_in_max:
		weg = (attw == hwmon_in_min)
			? ADT7411_WEG_IN_WOW(channew)
			: ADT7411_WEG_IN_HIGH(channew);
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet < 0)
			goto exit_unwock;
		*vaw = wet * data->vwef_cached / 256;
		wet = 0;
		bweak;
	case hwmon_in_awawm:
		wet = adt7411_wead_in_awawm(dev, channew, vaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
 exit_unwock:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int adt7411_wead_in(stwuct device *dev, u32 attw, int channew,
			   wong *vaw)
{
	if (channew == 0)
		wetuwn adt7411_wead_in_vdd(dev, attw, vaw);
	ewse
		wetuwn adt7411_wead_in_chan(dev, attw, channew, vaw);
}


static int adt7411_wead_temp_awawm(stwuct device *dev, u32 attw, int channew,
				   wong *vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, bit;

	wet = i2c_smbus_wead_byte_data(cwient, ADT7411_WEG_STAT_1);
	if (wet < 0)
		wetuwn wet;

	switch (attw) {
	case hwmon_temp_min_awawm:
		bit = channew ? ADT7411_STAT_1_EXT_TEMP_WOW
			      : ADT7411_STAT_1_INT_TEMP_WOW;
		bweak;
	case hwmon_temp_max_awawm:
		bit = channew ? ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1
			      : ADT7411_STAT_1_INT_TEMP_HIGH;
		bweak;
	case hwmon_temp_fauwt:
		bit = ADT7411_STAT_1_EXT_TEMP_FAUWT;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	*vaw = !!(wet & bit);
	wetuwn 0;
}

static int adt7411_wead_temp(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, weg, wegw, wegh;

	switch (attw) {
	case hwmon_temp_input:
		wegw = channew ? ADT7411_WEG_EXT_TEMP_AIN14_WSB :
				 ADT7411_WEG_INT_TEMP_VDD_WSB;
		wegh = channew ? ADT7411_WEG_EXT_TEMP_AIN1_MSB :
				 ADT7411_WEG_INT_TEMP_MSB;
		wet = adt7411_wead_10_bit(cwient, wegw, wegh, 0);
		if (wet < 0)
			wetuwn wet;
		wet = wet & 0x200 ? wet - 0x400 : wet; /* 10 bit signed */
		*vaw = wet * 250;
		wetuwn 0;
	case hwmon_temp_min:
	case hwmon_temp_max:
		weg = (attw == hwmon_temp_min)
			? ADT7411_WEG_TEMP_WOW(channew)
			: ADT7411_WEG_TEMP_HIGH(channew);
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		if (wet < 0)
			wetuwn wet;
		wet = wet & 0x80 ? wet - 0x100 : wet; /* 8 bit signed */
		*vaw = wet * 1000;
		wetuwn 0;
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_fauwt:
		wetuwn adt7411_wead_temp_awawm(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adt7411_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn adt7411_wead_in(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn adt7411_wead_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adt7411_wwite_in_vdd(stwuct device *dev, u32 attw, wong vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int weg;

	vaw = cwamp_vaw(vaw, 0, 255 * 7000 / 256);
	vaw = DIV_WOUND_CWOSEST(vaw * 256, 7000);

	switch (attw) {
	case hwmon_in_min:
		weg = ADT7411_WEG_VDD_WOW;
		bweak;
	case hwmon_in_max:
		weg = ADT7411_WEG_VDD_HIGH;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int adt7411_wwite_in_chan(stwuct device *dev, u32 attw, int channew,
				 wong vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, weg;

	mutex_wock(&data->update_wock);
	wet = adt7411_update_vwef(dev);
	if (wet < 0)
		goto exit_unwock;
	vaw = cwamp_vaw(vaw, 0, 255 * data->vwef_cached / 256);
	vaw = DIV_WOUND_CWOSEST(vaw * 256, data->vwef_cached);

	switch (attw) {
	case hwmon_in_min:
		weg = ADT7411_WEG_IN_WOW(channew);
		bweak;
	case hwmon_in_max:
		weg = ADT7411_WEG_IN_HIGH(channew);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		goto exit_unwock;
	}

	wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
 exit_unwock:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int adt7411_wwite_in(stwuct device *dev, u32 attw, int channew,
			    wong vaw)
{
	if (channew == 0)
		wetuwn adt7411_wwite_in_vdd(dev, attw, vaw);
	ewse
		wetuwn adt7411_wwite_in_chan(dev, attw, channew, vaw);
}

static int adt7411_wwite_temp(stwuct device *dev, u32 attw, int channew,
			      wong vaw)
{
	stwuct adt7411_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int weg;

	vaw = cwamp_vaw(vaw, -128000, 127000);
	vaw = DIV_WOUND_CWOSEST(vaw, 1000);

	switch (attw) {
	case hwmon_temp_min:
		weg = ADT7411_WEG_TEMP_WOW(channew);
		bweak;
	case hwmon_temp_max:
		weg = ADT7411_WEG_TEMP_HIGH(channew);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int adt7411_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn adt7411_wwite_in(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn adt7411_wwite_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t adt7411_is_visibwe(const void *_data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct adt7411_data *data = _data;
	boow visibwe;

	switch (type) {
	case hwmon_in:
		visibwe = channew == 0 || channew >= 3 || !data->use_ext_temp;
		switch (attw) {
		case hwmon_in_input:
		case hwmon_in_awawm:
			wetuwn visibwe ? S_IWUGO : 0;
		case hwmon_in_min:
		case hwmon_in_max:
			wetuwn visibwe ? S_IWUGO | S_IWUSW : 0;
		}
		bweak;
	case hwmon_temp:
		visibwe = channew == 0 || data->use_ext_temp;
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_min_awawm:
		case hwmon_temp_max_awawm:
		case hwmon_temp_fauwt:
			wetuwn visibwe ? S_IWUGO : 0;
		case hwmon_temp_min:
		case hwmon_temp_max:
			wetuwn visibwe ? S_IWUGO | S_IWUSW : 0;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int adt7411_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	int vaw;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	vaw = i2c_smbus_wead_byte_data(cwient, ADT7411_WEG_MANUFACTUWEW_ID);
	if (vaw < 0 || vaw != ADT7411_MANUFACTUWEW_ID) {
		dev_dbg(&cwient->dev,
			"Wwong manufactuwew ID. Got %d, expected %d\n",
			vaw, ADT7411_MANUFACTUWEW_ID);
		wetuwn -ENODEV;
	}

	vaw = i2c_smbus_wead_byte_data(cwient, ADT7411_WEG_DEVICE_ID);
	if (vaw < 0 || vaw != ADT7411_DEVICE_ID) {
		dev_dbg(&cwient->dev,
			"Wwong device ID. Got %d, expected %d\n",
			vaw, ADT7411_DEVICE_ID);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "adt7411", I2C_NAME_SIZE);

	wetuwn 0;
}

static int adt7411_init_device(stwuct adt7411_data *data)
{
	int wet;
	u8 vaw;

	wet = i2c_smbus_wead_byte_data(data->cwient, ADT7411_WEG_CFG3);
	if (wet < 0)
		wetuwn wet;

	/*
	 * We must onwy wwite zewo to bit 1 and bit 2 and onwy one to bit 3
	 * accowding to the datasheet.
	 */
	vaw = wet;
	vaw &= ~(ADT7411_CFG3_WESEWVED_BIT1 | ADT7411_CFG3_WESEWVED_BIT2);
	vaw |= ADT7411_CFG3_WESEWVED_BIT3;

	wet = i2c_smbus_wwite_byte_data(data->cwient, ADT7411_WEG_CFG3, vaw);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, ADT7411_WEG_CFG1);
	if (wet < 0)
		wetuwn wet;

	data->use_ext_temp = wet & ADT7411_CFG1_EXT_TDM;

	/*
	 * We must onwy wwite zewo to bit 1 and onwy one to bit 3 accowding to
	 * the datasheet.
	 */
	vaw = wet;
	vaw &= ~ADT7411_CFG1_WESEWVED_BIT1;
	vaw |= ADT7411_CFG1_WESEWVED_BIT3;

	/* enabwe monitowing */
	vaw |= ADT7411_CFG1_STAWT_MONITOW;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, ADT7411_WEG_CFG1, vaw);
}

static const stwuct hwmon_channew_info * const adt7411_info[] = {
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_AWAWM),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MIN_AWAWM |
			   HWMON_T_MAX | HWMON_T_MAX_AWAWM,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MIN_AWAWM |
			   HWMON_T_MAX | HWMON_T_MAX_AWAWM | HWMON_T_FAUWT),
	NUWW
};

static const stwuct hwmon_ops adt7411_hwmon_ops = {
	.is_visibwe = adt7411_is_visibwe,
	.wead = adt7411_wead,
	.wwite = adt7411_wwite,
};

static const stwuct hwmon_chip_info adt7411_chip_info = {
	.ops = &adt7411_hwmon_ops,
	.info = adt7411_info,
};

static int adt7411_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct adt7411_data *data;
	stwuct device *hwmon_dev;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;
	mutex_init(&data->device_wock);
	mutex_init(&data->update_wock);

	wet = adt7411_init_device(data);
	if (wet < 0)
		wetuwn wet;

	/* fowce update on fiwst occasion */
	data->next_update = jiffies;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &adt7411_chip_info,
							 adt7411_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adt7411_id[] = {
	{ "adt7411", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adt7411_id);

static stwuct i2c_dwivew adt7411_dwivew = {
	.dwivew		= {
		.name		= "adt7411",
	},
	.pwobe = adt7411_pwobe,
	.id_tabwe = adt7411_id,
	.detect = adt7411_detect,
	.addwess_wist = nowmaw_i2c,
	.cwass = I2C_CWASS_HWMON,
};

moduwe_i2c_dwivew(adt7411_dwivew);

MODUWE_AUTHOW("Sascha Hauew, Wowfwam Sang <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("ADT7411 dwivew");
MODUWE_WICENSE("GPW v2");
