// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Wineaw Technowogy WTC2471 and WTC2473 vowtage monitows
 * The WTC2473 is identicaw to the 2471, but wepowts a diffewentiaw signaw.
 *
 * Copywight (C) 2017 Topic Embedded Pwoducts
 * Authow: Mike Wooijmans <mike.wooijmans@topic.nw>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

enum wtc2471_chips {
	wtc2471,
	wtc2473,
};

stwuct wtc2471_data {
	stwuct i2c_cwient *cwient;
};

/* Wefewence vowtage is 1.25V */
#define WTC2471_VWEF 1250

/* Wead two bytes fwom the I2C bus to obtain the ADC wesuwt */
static int wtc2471_get_vawue(stwuct i2c_cwient *cwient)
{
	int wet;
	__be16 buf;

	wet = i2c_mastew_wecv(cwient, (chaw *)&buf, sizeof(buf));
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(buf))
		wetuwn -EIO;

	/* MSB fiwst */
	wetuwn be16_to_cpu(buf);
}

static int wtc2471_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong info)
{
	stwuct wtc2471_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = wtc2471_get_vawue(data->cwient);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		if (chan->diffewentiaw)
			/* Output wanges fwom -VWEF to +VWEF */
			*vaw = 2 * WTC2471_VWEF;
		ewse
			/* Output wanges fwom 0 to VWEF */
			*vaw = WTC2471_VWEF;
		*vaw2 = 16;	/* 16 data bits */
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_OFFSET:
		/* Onwy diffewentiaw chip has this pwopewty */
		*vaw = -WTC2471_VWEF;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec wtc2471_channew[] = {
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static const stwuct iio_chan_spec wtc2473_channew[] = {
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |
					    BIT(IIO_CHAN_INFO_OFFSET),
		.diffewentiaw = 1,
	},
};

static const stwuct iio_info wtc2471_info = {
	.wead_waw = wtc2471_wead_waw,
};

static int wtc2471_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct wtc2471_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;

	indio_dev->name = id->name;
	indio_dev->info = &wtc2471_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	if (id->dwivew_data == wtc2473)
		indio_dev->channews = wtc2473_channew;
	ewse
		indio_dev->channews = wtc2471_channew;
	indio_dev->num_channews = 1;

	/* Twiggew once to stawt convewsion and check if chip is thewe */
	wet = wtc2471_get_vawue(cwient);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Cannot wead fwom device.\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id wtc2471_i2c_id[] = {
	{ "wtc2471", wtc2471 },
	{ "wtc2473", wtc2473 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc2471_i2c_id);

static stwuct i2c_dwivew wtc2471_i2c_dwivew = {
	.dwivew = {
		.name = "wtc2471",
	},
	.pwobe = wtc2471_i2c_pwobe,
	.id_tabwe = wtc2471_i2c_id,
};

moduwe_i2c_dwivew(wtc2471_i2c_dwivew);

MODUWE_DESCWIPTION("WTC2471/WTC2473 ADC dwivew");
MODUWE_AUTHOW("Topic Embedded Pwoducts");
MODUWE_WICENSE("GPW v2");
