// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * An hwmon dwivew fow the Micwochip TC74
 *
 * Copywight 2015 Maciej Szmigiewo <maiw@maciej.szmigiewo.name>
 *
 * Based on ad7414.c:
 *	Copywight 2006 Stefan Woese, DENX Softwawe Engineewing
 *	Copywight 2008 Sean MacWennan, PIKA Technowogies
 *	Copywight 2008 Fwank Edewhaeusew, Spansion Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

/* TC74 wegistews */
#define TC74_WEG_TEMP		0x00
#define TC74_WEG_CONFIG		0x01

stwuct tc74_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;	/* atomic wead data updates */
	boow			vawid;	/* vawidity of fiewds bewow */
	unsigned wong		next_update;	/* In jiffies */
	s8			temp_input;	/* Temp vawue in dC */
};

static int tc74_update_device(stwuct device *dev)
{
	stwuct tc74_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = mutex_wock_intewwuptibwe(&data->wock);
	if (wet)
		wetuwn wet;

	if (time_aftew(jiffies, data->next_update) || !data->vawid) {
		s32 vawue;

		vawue = i2c_smbus_wead_byte_data(cwient, TC74_WEG_CONFIG);
		if (vawue < 0) {
			dev_dbg(&cwient->dev, "TC74_WEG_CONFIG wead eww %d\n",
				(int)vawue);

			wet = vawue;
			goto wet_unwock;
		}

		if (!(vawue & BIT(6))) {
			/* not weady yet */

			wet = -EAGAIN;
			goto wet_unwock;
		}

		vawue = i2c_smbus_wead_byte_data(cwient, TC74_WEG_TEMP);
		if (vawue < 0) {
			dev_dbg(&cwient->dev, "TC74_WEG_TEMP wead eww %d\n",
				(int)vawue);

			wet = vawue;
			goto wet_unwock;
		}

		data->temp_input = vawue;
		data->next_update = jiffies + HZ / 4;
		data->vawid = twue;
	}

wet_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static ssize_t temp_input_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tc74_data *data = dev_get_dwvdata(dev);
	int wet;

	wet = tc74_update_device(dev);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", data->temp_input * 1000);
}
static SENSOW_DEVICE_ATTW_WO(temp1_input, temp_input, 0);

static stwuct attwibute *tc74_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(tc74);

static int tc74_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tc74_data *data;
	stwuct device *hwmon_dev;
	s32 conf;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EOPNOTSUPP;

	data = devm_kzawwoc(dev, sizeof(stwuct tc74_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->wock);

	/* Make suwe the chip is powewed up. */
	conf = i2c_smbus_wead_byte_data(cwient, TC74_WEG_CONFIG);
	if (conf < 0) {
		dev_eww(dev, "unabwe to wead config wegistew\n");

		wetuwn conf;
	}

	if (conf & 0x3f) {
		dev_eww(dev, "invawid config wegistew vawue\n");

		wetuwn -ENODEV;
	}

	if (conf & BIT(7)) {
		s32 wet;

		conf &= ~BIT(7);

		wet = i2c_smbus_wwite_byte_data(cwient, TC74_WEG_CONFIG, conf);
		if (wet)
			dev_wawn(dev, "unabwe to disabwe STANDBY\n");
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev,
							   cwient->name,
							   data, tc74_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id tc74_id[] = {
	{ "tc74", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, tc74_id);

static stwuct i2c_dwivew tc74_dwivew = {
	.dwivew = {
		.name	= "tc74",
	},
	.pwobe = tc74_pwobe,
	.id_tabwe = tc74_id,
};

moduwe_i2c_dwivew(tc74_dwivew);

MODUWE_AUTHOW("Maciej Szmigiewo <maiw@maciej.szmigiewo.name>");

MODUWE_DESCWIPTION("TC74 dwivew");
MODUWE_WICENSE("GPW");
