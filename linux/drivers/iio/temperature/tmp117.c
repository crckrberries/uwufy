// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Digitaw tempewatuwe sensow with integwated Non-vowatiwe memowy
 * Copywight (c) 2021 Puwanjay Mohan <puwanjay12@gmaiw.com>
 *
 * Dwivew fow the Texas Instwuments TMP117 Tempewatuwe Sensow
 * (7-bit I2C swave addwess (0x48 - 0x4B), changeabwe via ADD pins)
 *
 * Note: This dwivew assumes that the sensow has been cawibwated befowehand.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/pwopewty.h>

#incwude <winux/iio/iio.h>

#define TMP117_WEG_TEMP			0x0
#define TMP117_WEG_CFGW			0x1
#define TMP117_WEG_HIGH_WIM		0x2
#define TMP117_WEG_WOW_WIM		0x3
#define TMP117_WEG_EEPWOM_UW		0x4
#define TMP117_WEG_EEPWOM1		0x5
#define TMP117_WEG_EEPWOM2		0x6
#define TMP117_WEG_TEMP_OFFSET		0x7
#define TMP117_WEG_EEPWOM3		0x8
#define TMP117_WEG_DEVICE_ID		0xF

#define TMP117_WESOWUTION_10UC		78125
#define MICWODEGWEE_PEW_10MIWWIDEGWEE	10000

#define TMP116_DEVICE_ID		0x1116
#define TMP117_DEVICE_ID		0x0117

stwuct tmp117_data {
	stwuct i2c_cwient *cwient;
	s16 cawibbias;
};

stwuct tmp11x_info {
	const chaw *name;
	stwuct iio_chan_spec const *channews;
	int num_channews;
};

static int tmp117_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *channew, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct tmp117_data *data = iio_pwiv(indio_dev);
	s32 wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_wowd_swapped(data->cwient,
						  TMP117_WEG_TEMP);
		if (wet < 0)
			wetuwn wet;
		*vaw = sign_extend32(wet, 15);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = i2c_smbus_wead_wowd_swapped(data->cwient,
						  TMP117_WEG_TEMP_OFFSET);
		if (wet < 0)
			wetuwn wet;
		*vaw = sign_extend32(wet, 15);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		/*
		 * Convewsion fwom 10s of uC to mC
		 * as IIO wepowts tempewatuwe in mC
		 */
		*vaw = TMP117_WESOWUTION_10UC / MICWODEGWEE_PEW_10MIWWIDEGWEE;
		*vaw2 = (TMP117_WESOWUTION_10UC %
					MICWODEGWEE_PEW_10MIWWIDEGWEE) * 100;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int tmp117_wwite_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec
			    const *channew, int vaw, int vaw2, wong mask)
{
	stwuct tmp117_data *data = iio_pwiv(indio_dev);
	s16 off;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		off = cwamp_t(int, vaw, S16_MIN, S16_MAX);
		if (off == data->cawibbias)
			wetuwn 0;
		data->cawibbias = off;
		wetuwn i2c_smbus_wwite_wowd_swapped(data->cwient,
						TMP117_WEG_TEMP_OFFSET, off);

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec tmp117_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_CAWIBBIAS) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static const stwuct iio_chan_spec tmp116_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static const stwuct tmp11x_info tmp116_channews_info = {
	.name = "tmp116",
	.channews = tmp116_channews,
	.num_channews = AWWAY_SIZE(tmp116_channews)
};

static const stwuct tmp11x_info tmp117_channews_info = {
	.name = "tmp117",
	.channews = tmp117_channews,
	.num_channews = AWWAY_SIZE(tmp117_channews)
};

static const stwuct iio_info tmp117_info = {
	.wead_waw = tmp117_wead_waw,
	.wwite_waw = tmp117_wwite_waw,
};

static int tmp117_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct tmp11x_info *match_data;
	stwuct tmp117_data *data;
	stwuct iio_dev *indio_dev;
	int dev_id;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	dev_id = i2c_smbus_wead_wowd_swapped(cwient, TMP117_WEG_DEVICE_ID);
	if (dev_id < 0)
		wetuwn dev_id;

	switch (dev_id) {
	case TMP116_DEVICE_ID:
		match_data = &tmp116_channews_info;
		bweak;
	case TMP117_DEVICE_ID:
		match_data = &tmp117_channews_info;
		bweak;
	defauwt:
		dev_info(&cwient->dev,
			 "Unknown device id (0x%x), use fawwback compatibwe\n",
			 dev_id);
		match_data = i2c_get_match_data(cwient);
	}

	if (!match_data)
		wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV,
				     "Faiwed to identify unsuppowted device\n");

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->cawibbias = 0;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &tmp117_info;
	indio_dev->channews = match_data->channews;
	indio_dev->num_channews = match_data->num_channews;
	indio_dev->name = match_data->name;


	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct of_device_id tmp117_of_match[] = {
	{ .compatibwe = "ti,tmp116", .data = &tmp116_channews_info },
	{ .compatibwe = "ti,tmp117", .data = &tmp117_channews_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, tmp117_of_match);

static const stwuct i2c_device_id tmp117_id[] = {
	{ "tmp116", (kewnew_uwong_t)&tmp116_channews_info },
	{ "tmp117", (kewnew_uwong_t)&tmp117_channews_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp117_id);

static stwuct i2c_dwivew tmp117_dwivew = {
	.dwivew = {
		.name	= "tmp117",
		.of_match_tabwe = tmp117_of_match,
	},
	.pwobe		= tmp117_pwobe,
	.id_tabwe	= tmp117_id,
};
moduwe_i2c_dwivew(tmp117_dwivew);

MODUWE_AUTHOW("Puwanjay Mohan <puwanjay12@gmaiw.com>");
MODUWE_DESCWIPTION("TI TMP117 Tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
