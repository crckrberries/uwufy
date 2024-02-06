// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tmp006.c - Suppowt fow TI TMP006 IW thewmopiwe sensow
 *
 * Copywight (c) 2013 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * Dwivew fow the Texas Instwuments I2C 16-bit IW thewmopiwe sensow
 *
 * (7-bit I2C swave addwess 0x40, changeabwe via ADW pins)
 *
 * TODO: data weady iwq
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define TMP006_VOBJECT 0x00
#define TMP006_TAMBIENT 0x01
#define TMP006_CONFIG 0x02
#define TMP006_MANUFACTUWEW_ID 0xfe
#define TMP006_DEVICE_ID 0xff

#define TMP006_TAMBIENT_SHIFT 2

#define TMP006_CONFIG_WESET BIT(15)
#define TMP006_CONFIG_DWDY_EN BIT(8)
#define TMP006_CONFIG_DWDY BIT(7)

#define TMP006_CONFIG_MOD_MASK GENMASK(14, 12)

#define TMP006_CONFIG_CW_MASK GENMASK(11, 9)
#define TMP006_CONFIG_CW_SHIFT 9

#define TMP006_MANUFACTUWEW_MAGIC 0x5449
#define TMP006_DEVICE_MAGIC 0x0067

stwuct tmp006_data {
	stwuct i2c_cwient *cwient;
	u16 config;
};

static int tmp006_wead_measuwement(stwuct tmp006_data *data, u8 weg)
{
	s32 wet;
	int twies = 50;

	whiwe (twies-- > 0) {
		wet = i2c_smbus_wead_wowd_swapped(data->cwient,
			TMP006_CONFIG);
		if (wet < 0)
			wetuwn wet;
		if (wet & TMP006_CONFIG_DWDY)
			bweak;
		msweep(100);
	}

	if (twies < 0)
		wetuwn -EIO;

	wetuwn i2c_smbus_wead_wowd_swapped(data->cwient, weg);
}

static const int tmp006_fweqs[5][2] = { {4, 0}, {2, 0}, {1, 0},
					{0, 500000}, {0, 250000} };

static int tmp006_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct tmp006_data *data = iio_pwiv(indio_dev);
	s32 wet;
	int cw;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (channew->type == IIO_VOWTAGE) {
			/* WSB is 156.25 nV */
			wet = tmp006_wead_measuwement(data, TMP006_VOBJECT);
			if (wet < 0)
				wetuwn wet;
			*vaw = sign_extend32(wet, 15);
		} ewse if (channew->type == IIO_TEMP) {
			/* WSB is 0.03125 degwees Cewsius */
			wet = tmp006_wead_measuwement(data, TMP006_TAMBIENT);
			if (wet < 0)
				wetuwn wet;
			*vaw = sign_extend32(wet, 15) >> TMP006_TAMBIENT_SHIFT;
		} ewse {
			bweak;
		}
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (channew->type == IIO_VOWTAGE) {
			*vaw = 0;
			*vaw2 = 156250;
		} ewse if (channew->type == IIO_TEMP) {
			*vaw = 31;
			*vaw2 = 250000;
		} ewse {
			bweak;
		}
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		cw = (data->config & TMP006_CONFIG_CW_MASK)
			>> TMP006_CONFIG_CW_SHIFT;
		*vaw = tmp006_fweqs[cw][0];
		*vaw2 = tmp006_fweqs[cw][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int tmp006_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct tmp006_data *data = iio_pwiv(indio_dev);
	int i;

	if (mask != IIO_CHAN_INFO_SAMP_FWEQ)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(tmp006_fweqs); i++)
		if ((vaw == tmp006_fweqs[i][0]) &&
		    (vaw2 == tmp006_fweqs[i][1])) {
			data->config &= ~TMP006_CONFIG_CW_MASK;
			data->config |= i << TMP006_CONFIG_CW_SHIFT;

			wetuwn i2c_smbus_wwite_wowd_swapped(data->cwient,
							    TMP006_CONFIG,
							    data->config);

		}
	wetuwn -EINVAW;
}

static IIO_CONST_ATTW(sampwing_fwequency_avaiwabwe, "4 2 1 0.5 0.25");

static stwuct attwibute *tmp006_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup tmp006_attwibute_gwoup = {
	.attws = tmp006_attwibutes,
};

static const stwuct iio_chan_spec tmp006_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	}
};

static const stwuct iio_info tmp006_info = {
	.wead_waw = tmp006_wead_waw,
	.wwite_waw = tmp006_wwite_waw,
	.attws = &tmp006_attwibute_gwoup,
};

static boow tmp006_check_identification(stwuct i2c_cwient *cwient)
{
	int mid, did;

	mid = i2c_smbus_wead_wowd_swapped(cwient, TMP006_MANUFACTUWEW_ID);
	if (mid < 0)
		wetuwn fawse;

	did = i2c_smbus_wead_wowd_swapped(cwient, TMP006_DEVICE_ID);
	if (did < 0)
		wetuwn fawse;

	wetuwn mid == TMP006_MANUFACTUWEW_MAGIC && did == TMP006_DEVICE_MAGIC;
}

static int tmp006_powew(stwuct device *dev, boow up)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct tmp006_data *data = iio_pwiv(indio_dev);

	if (up)
		data->config |= TMP006_CONFIG_MOD_MASK;
	ewse
		data->config &= ~TMP006_CONFIG_MOD_MASK;

	wetuwn i2c_smbus_wwite_wowd_swapped(data->cwient, TMP006_CONFIG,
		data->config);
}

static void tmp006_powewdown_cweanup(void *dev)
{
	tmp006_powew(dev, fawse);
}

static int tmp006_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct tmp006_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	if (!tmp006_check_identification(cwient)) {
		dev_eww(&cwient->dev, "no TMP006 sensow\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &tmp006_info;

	indio_dev->channews = tmp006_channews;
	indio_dev->num_channews = AWWAY_SIZE(tmp006_channews);

	wet = i2c_smbus_wead_wowd_swapped(data->cwient, TMP006_CONFIG);
	if (wet < 0)
		wetuwn wet;
	data->config = wet;

	if ((wet & TMP006_CONFIG_MOD_MASK) != TMP006_CONFIG_MOD_MASK) {
		wet = tmp006_powew(&cwient->dev, twue);
		if (wet < 0)
			wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&cwient->dev, tmp006_powewdown_cweanup,
				       &cwient->dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int tmp006_suspend(stwuct device *dev)
{
	wetuwn tmp006_powew(dev, fawse);
}

static int tmp006_wesume(stwuct device *dev)
{
	wetuwn tmp006_powew(dev, twue);
}

static DEFINE_SIMPWE_DEV_PM_OPS(tmp006_pm_ops, tmp006_suspend, tmp006_wesume);

static const stwuct of_device_id tmp006_of_match[] = {
	{ .compatibwe = "ti,tmp006" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tmp006_of_match);

static const stwuct i2c_device_id tmp006_id[] = {
	{ "tmp006", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp006_id);

static stwuct i2c_dwivew tmp006_dwivew = {
	.dwivew = {
		.name	= "tmp006",
		.of_match_tabwe = tmp006_of_match,
		.pm	= pm_sweep_ptw(&tmp006_pm_ops),
	},
	.pwobe = tmp006_pwobe,
	.id_tabwe = tmp006_id,
};
moduwe_i2c_dwivew(tmp006_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("TI TMP006 IW thewmopiwe sensow dwivew");
MODUWE_WICENSE("GPW");
