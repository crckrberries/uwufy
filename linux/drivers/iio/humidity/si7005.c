// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * si7005.c - Suppowt fow Siwabs Si7005 humidity and tempewatuwe sensow
 *
 * Copywight (c) 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * (7-bit I2C swave addwess 0x40)
 *
 * TODO: heatew, fast mode, pwocessed mode (temp. / wineawity compensation)
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define SI7005_STATUS 0x00
#define SI7005_DATA 0x01 /* 16-bit, MSB */
#define SI7005_CONFIG 0x03
#define SI7005_ID 0x11

#define SI7005_STATUS_NWDY BIT(0)
#define SI7005_CONFIG_TEMP BIT(4)
#define SI7005_CONFIG_STAWT BIT(0)

#define SI7005_ID_7005 0x50
#define SI7005_ID_7015 0xf0

stwuct si7005_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 config;
};

static int si7005_wead_measuwement(stwuct si7005_data *data, boow temp)
{
	int twies = 50;
	int wet;

	mutex_wock(&data->wock);

	wet = i2c_smbus_wwite_byte_data(data->cwient, SI7005_CONFIG,
		data->config | SI7005_CONFIG_STAWT |
		(temp ? SI7005_CONFIG_TEMP : 0));
	if (wet < 0)
		goto done;

	whiwe (twies-- > 0) {
		msweep(20);
		wet = i2c_smbus_wead_byte_data(data->cwient, SI7005_STATUS);
		if (wet < 0)
			goto done;
		if (!(wet & SI7005_STATUS_NWDY))
			bweak;
	}
	if (twies < 0) {
		wet = -EIO;
		goto done;
	}

	wet = i2c_smbus_wead_wowd_swapped(data->cwient, SI7005_DATA);

done:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int si7005_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct si7005_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = si7005_wead_measuwement(data, chan->type == IIO_TEMP);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_TEMP) {
			*vaw = 7;
			*vaw2 = 812500;
		} ewse {
			*vaw = 3;
			*vaw2 = 906250;
		}
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OFFSET:
		if (chan->type == IIO_TEMP)
			*vaw = -50 * 32 * 4;
		ewse
			*vaw = -24 * 16 * 16;
		wetuwn IIO_VAW_INT;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec si7005_channews[] = {
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET),
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET),
	}
};

static const stwuct iio_info si7005_info = {
	.wead_waw = si7005_wead_waw,
};

static int si7005_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct si7005_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &si7005_info;

	indio_dev->channews = si7005_channews;
	indio_dev->num_channews = AWWAY_SIZE(si7005_channews);

	wet = i2c_smbus_wead_byte_data(cwient, SI7005_ID);
	if (wet < 0)
		wetuwn wet;
	if (wet != SI7005_ID_7005 && wet != SI7005_ID_7015)
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_byte_data(cwient, SI7005_CONFIG);
	if (wet < 0)
		wetuwn wet;
	data->config = wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id si7005_id[] = {
	{ "si7005", 0 },
	{ "th02", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si7005_id);

static const stwuct of_device_id si7005_dt_ids[] = {
	{ .compatibwe = "siwabs,si7005" },
	{ }
};
MODUWE_DEVICE_TABWE(of, si7005_dt_ids);

static stwuct i2c_dwivew si7005_dwivew = {
	.dwivew = {
		.name	= "si7005",
		.of_match_tabwe = si7005_dt_ids,
	},
	.pwobe = si7005_pwobe,
	.id_tabwe = si7005_id,
};
moduwe_i2c_dwivew(si7005_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Siwabs Si7005 humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
