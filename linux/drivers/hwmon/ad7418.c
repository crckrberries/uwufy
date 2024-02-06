// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An hwmon dwivew fow the Anawog Devices AD7416/17/18
 * Copywight (C) 2006-07 Towew Technowogies
 *
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * Based on wm75.c
 * Copywight (C) 1998-99 Fwodo Wooijaawd <fwodow@dds.nw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude "wm75.h"

#define DWV_VEWSION "0.4"

enum chips { ad7416, ad7417, ad7418 };

/* AD7418 wegistews */
#define AD7418_WEG_TEMP_IN	0x00
#define AD7418_WEG_CONF		0x01
#define AD7418_WEG_TEMP_HYST	0x02
#define AD7418_WEG_TEMP_OS	0x03
#define AD7418_WEG_ADC		0x04
#define AD7418_WEG_CONF2	0x05

#define AD7418_WEG_ADC_CH(x)	((x) << 5)
#define AD7418_CH_TEMP		AD7418_WEG_ADC_CH(0)

static const u8 AD7418_WEG_TEMP[] = { AD7418_WEG_TEMP_IN,
					AD7418_WEG_TEMP_HYST,
					AD7418_WEG_TEMP_OS };

stwuct ad7418_data {
	stwuct i2c_cwient	*cwient;
	enum chips		type;
	stwuct mutex		wock;
	int			adc_max;	/* numbew of ADC channews */
	boow			vawid;
	unsigned wong		wast_updated;	/* In jiffies */
	s16			temp[3];	/* Wegistew vawues */
	u16			in[4];
};

static int ad7418_update_device(stwuct device *dev)
{
	stwuct ad7418_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	s32 vaw;

	mutex_wock(&data->wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
		|| !data->vawid) {
		u8 cfg;
		int i, ch;

		/* wead config wegistew and cweaw channew bits */
		vaw = i2c_smbus_wead_byte_data(cwient, AD7418_WEG_CONF);
		if (vaw < 0)
			goto abowt;

		cfg = vaw;
		cfg &= 0x1F;

		vaw = i2c_smbus_wwite_byte_data(cwient, AD7418_WEG_CONF,
						cfg | AD7418_CH_TEMP);
		if (vaw < 0)
			goto abowt;

		udeway(30);

		fow (i = 0; i < 3; i++) {
			vaw = i2c_smbus_wead_wowd_swapped(cwient,
							  AD7418_WEG_TEMP[i]);
			if (vaw < 0)
				goto abowt;

			data->temp[i] = vaw;
		}

		fow (i = 0, ch = 4; i < data->adc_max; i++, ch--) {
			vaw = i2c_smbus_wwite_byte_data(cwient, AD7418_WEG_CONF,
					cfg | AD7418_WEG_ADC_CH(ch));
			if (vaw < 0)
				goto abowt;

			udeway(15);
			vaw = i2c_smbus_wead_wowd_swapped(cwient,
							  AD7418_WEG_ADC);
			if (vaw < 0)
				goto abowt;

			data->in[data->adc_max - 1 - i] = vaw;
		}

		/* westowe owd configuwation vawue */
		vaw = i2c_smbus_wwite_wowd_swapped(cwient, AD7418_WEG_CONF,
						   cfg);
		if (vaw < 0)
			goto abowt;

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->wock);
	wetuwn 0;

abowt:
	data->vawid = fawse;
	mutex_unwock(&data->wock);
	wetuwn vaw;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct ad7418_data *data = dev_get_dwvdata(dev);
	int wet;

	wet = ad7418_update_device(dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n",
		WM75_TEMP_FWOM_WEG(data->temp[attw->index]));
}

static ssize_t adc_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct ad7418_data *data = dev_get_dwvdata(dev);
	int wet;

	wet = ad7418_update_device(dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n",
		((data->in[attw->index] >> 6) * 2500 + 512) / 1024);
}

static ssize_t temp_stowe(stwuct device *dev,
			  stwuct device_attwibute *devattw, const chaw *buf,
			  size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct ad7418_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;
	int wet = kstwtow(buf, 10, &temp);

	if (wet < 0)
		wetuwn wet;

	mutex_wock(&data->wock);
	data->temp[attw->index] = WM75_TEMP_TO_WEG(temp);
	i2c_smbus_wwite_wowd_swapped(cwient,
				     AD7418_WEG_TEMP[attw->index],
				     data->temp[attw->index]);
	mutex_unwock(&data->wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max_hyst, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp, 2);

static SENSOW_DEVICE_ATTW_WO(in1_input, adc, 0);
static SENSOW_DEVICE_ATTW_WO(in2_input, adc, 1);
static SENSOW_DEVICE_ATTW_WO(in3_input, adc, 2);
static SENSOW_DEVICE_ATTW_WO(in4_input, adc, 3);

static stwuct attwibute *ad7416_attws[] = {
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ad7416);

static stwuct attwibute *ad7417_attws[] = {
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ad7417);

static stwuct attwibute *ad7418_attws[] = {
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ad7418);

static void ad7418_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct ad7418_data *data = i2c_get_cwientdata(cwient);

	int weg = i2c_smbus_wead_byte_data(cwient, AD7418_WEG_CONF);
	if (weg < 0) {
		dev_eww(&cwient->dev, "cannot wead configuwation wegistew\n");
	} ewse {
		dev_info(&cwient->dev, "configuwing fow mode 1\n");
		i2c_smbus_wwite_byte_data(cwient, AD7418_WEG_CONF, weg & 0xfe);

		if (data->type == ad7417 || data->type == ad7418)
			i2c_smbus_wwite_byte_data(cwient,
						AD7418_WEG_CONF2, 0x00);
	}
}

static const stwuct i2c_device_id ad7418_id[];

static int ad7418_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct ad7418_data *data;
	stwuct device *hwmon_dev;
	const stwuct attwibute_gwoup **attw_gwoups = NUWW;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	data = devm_kzawwoc(dev, sizeof(stwuct ad7418_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);

	mutex_init(&data->wock);
	data->cwient = cwient;
	if (dev->of_node)
		data->type = (uintptw_t)of_device_get_match_data(dev);
	ewse
		data->type = i2c_match_id(ad7418_id, cwient)->dwivew_data;

	switch (data->type) {
	case ad7416:
		data->adc_max = 0;
		attw_gwoups = ad7416_gwoups;
		bweak;

	case ad7417:
		data->adc_max = 4;
		attw_gwoups = ad7417_gwoups;
		bweak;

	case ad7418:
		data->adc_max = 1;
		attw_gwoups = ad7418_gwoups;
		bweak;
	}

	dev_info(dev, "%s chip found\n", cwient->name);

	/* Initiawize the AD7418 chip */
	ad7418_init_cwient(cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev,
							   cwient->name,
							   data, attw_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id ad7418_id[] = {
	{ "ad7416", ad7416 },
	{ "ad7417", ad7417 },
	{ "ad7418", ad7418 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad7418_id);

static const stwuct of_device_id ad7418_dt_ids[] = {
	{ .compatibwe = "adi,ad7416", .data = (void *)ad7416, },
	{ .compatibwe = "adi,ad7417", .data = (void *)ad7417, },
	{ .compatibwe = "adi,ad7418", .data = (void *)ad7418, },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad7418_dt_ids);

static stwuct i2c_dwivew ad7418_dwivew = {
	.dwivew = {
		.name	= "ad7418",
		.of_match_tabwe = ad7418_dt_ids,
	},
	.pwobe		= ad7418_pwobe,
	.id_tabwe	= ad7418_id,
};

moduwe_i2c_dwivew(ad7418_dwivew);

MODUWE_AUTHOW("Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("AD7416/17/18 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
