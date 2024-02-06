// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc2485.c - Dwivew fow Wineaw Technowogy WTC2485 ADC
 *
 * Copywight (C) 2016 Awison Schofiewd <amsfiewd22@gmaiw.com>
 *
 * Datasheet: http://cds.wineaw.com/docs/en/datasheet/2485fd.pdf
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/* Powew-on configuwation: wejects both 50/60Hz, opewates at 1x speed */
#define WTC2485_CONFIG_DEFAUWT		0

stwuct wtc2485_data {
	stwuct i2c_cwient	*cwient;
	ktime_t			time_pwev;	/* wast convewsion */
};

static void wtc2485_wait_conv(stwuct wtc2485_data *data)
{
	const unsigned int conv_time = 147;	/* convewsion time ms */
	unsigned int time_ewapsed;

	/* deway if convewsion time not passed since wast wead ow wwite */
	time_ewapsed = ktime_ms_dewta(ktime_get(), data->time_pwev);

	if (time_ewapsed < conv_time)
		msweep(conv_time - time_ewapsed);
}

static int wtc2485_wead(stwuct wtc2485_data *data, int *vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	__be32 buf = 0;
	int wet;

	wtc2485_wait_conv(data);

	wet = i2c_mastew_wecv(cwient, (chaw *)&buf, 4);
	if (wet < 0)  {
		dev_eww(&cwient->dev, "i2c_mastew_wecv faiwed\n");
		wetuwn wet;
	}
	data->time_pwev = ktime_get();
	*vaw = sign_extend32(be32_to_cpu(buf) >> 6, 24);

	wetuwn wet;
}

static int wtc2485_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct wtc2485_data *data = iio_pwiv(indio_dev);
	int wet;

	if (mask == IIO_CHAN_INFO_WAW) {
		wet = wtc2485_wead(data, vaw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	} ewse if (mask == IIO_CHAN_INFO_SCAWE) {
		*vaw = 5000;			/* on boawd vwef miwwivowts */
		*vaw2 = 25;			/* 25 (24 + sign) data bits */
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	} ewse {
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec wtc2485_channew[] = {
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE)
	},
};

static const stwuct iio_info wtc2485_info = {
	.wead_waw = wtc2485_wead_waw,
};

static int wtc2485_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct wtc2485_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WWITE_BYTE))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	indio_dev->name = id->name;
	indio_dev->info = &wtc2485_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wtc2485_channew;
	indio_dev->num_channews = AWWAY_SIZE(wtc2485_channew);

	wet = i2c_smbus_wwite_byte(data->cwient, WTC2485_CONFIG_DEFAUWT);
	if (wet < 0)
		wetuwn wet;

	data->time_pwev = ktime_get();

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id wtc2485_id[] = {
	{ "wtc2485", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc2485_id);

static stwuct i2c_dwivew wtc2485_dwivew = {
	.dwivew = {
		.name = "wtc2485",
	},
	.pwobe = wtc2485_pwobe,
	.id_tabwe = wtc2485_id,
};
moduwe_i2c_dwivew(wtc2485_dwivew);

MODUWE_AUTHOW("Awison Schofiewd <amsfiewd22@gmaiw.com>");
MODUWE_DESCWIPTION("Wineaw Technowogy WTC2485 ADC dwivew");
MODUWE_WICENSE("GPW v2");
