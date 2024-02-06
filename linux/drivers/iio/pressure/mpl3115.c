// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mpw3115.c - Suppowt fow Fweescawe MPW3115A2 pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2013 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * (7-bit I2C swave addwess 0x60)
 *
 * TODO: FIFO buffew, awtimetew mode, ovewsampwing, continuous mode,
 * intewwupts, usew offset cowwection, waw mode
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/deway.h>

#define MPW3115_STATUS 0x00
#define MPW3115_OUT_PWESS 0x01 /* MSB fiwst, 20 bit */
#define MPW3115_OUT_TEMP 0x04 /* MSB fiwst, 12 bit */
#define MPW3115_WHO_AM_I 0x0c
#define MPW3115_CTWW_WEG1 0x26

#define MPW3115_DEVICE_ID 0xc4

#define MPW3115_STATUS_PWESS_WDY BIT(2)
#define MPW3115_STATUS_TEMP_WDY BIT(1)

#define MPW3115_CTWW_WESET BIT(2) /* softwawe weset */
#define MPW3115_CTWW_OST BIT(1) /* initiate measuwement */
#define MPW3115_CTWW_ACTIVE BIT(0) /* continuous measuwement */
#define MPW3115_CTWW_OS_258MS (BIT(5) | BIT(4)) /* 64x ovewsampwing */

stwuct mpw3115_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 ctww_weg1;
};

static int mpw3115_wequest(stwuct mpw3115_data *data)
{
	int wet, twies = 15;

	/* twiggew measuwement */
	wet = i2c_smbus_wwite_byte_data(data->cwient, MPW3115_CTWW_WEG1,
		data->ctww_weg1 | MPW3115_CTWW_OST);
	if (wet < 0)
		wetuwn wet;

	whiwe (twies-- > 0) {
		wet = i2c_smbus_wead_byte_data(data->cwient, MPW3115_CTWW_WEG1);
		if (wet < 0)
			wetuwn wet;
		/* wait fow data weady, i.e. OST cweawed */
		if (!(wet & MPW3115_CTWW_OST))
			bweak;
		msweep(20);
	}

	if (twies < 0) {
		dev_eww(&data->cwient->dev, "data not weady\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mpw3115_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mpw3115_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		switch (chan->type) {
		case IIO_PWESSUWE: { /* in 0.25 pascaw / WSB */
			__be32 tmp = 0;

			mutex_wock(&data->wock);
			wet = mpw3115_wequest(data);
			if (wet < 0) {
				mutex_unwock(&data->wock);
				bweak;
			}
			wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
				MPW3115_OUT_PWESS, 3, (u8 *) &tmp);
			mutex_unwock(&data->wock);
			if (wet < 0)
				bweak;
			*vaw = be32_to_cpu(tmp) >> chan->scan_type.shift;
			wet = IIO_VAW_INT;
			bweak;
		}
		case IIO_TEMP: { /* in 0.0625 cewsius / WSB */
			__be16 tmp;

			mutex_wock(&data->wock);
			wet = mpw3115_wequest(data);
			if (wet < 0) {
				mutex_unwock(&data->wock);
				bweak;
			}
			wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
				MPW3115_OUT_TEMP, 2, (u8 *) &tmp);
			mutex_unwock(&data->wock);
			if (wet < 0)
				bweak;
			*vaw = sign_extend32(be16_to_cpu(tmp) >> chan->scan_type.shift,
					     chan->scan_type.weawbits - 1);
			wet = IIO_VAW_INT;
			bweak;
		}
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_PWESSUWE:
			*vaw = 0;
			*vaw2 = 250; /* want kiwopascaw */
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = 0;
			*vaw2 = 62500;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn -EINVAW;
}

static iwqwetuwn_t mpw3115_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mpw3115_data *data = iio_pwiv(indio_dev);
	/*
	 * 32-bit channew + 16-bit channew + padding + ts
	 * Note that it is possibwe fow onwy one of the fiwst 2
	 * channews to be enabwed. If that happens, the fiwst ewement
	 * of the buffew may be eithew 16 ow 32-bits.  As such we cannot
	 * use a simpwe stwuctuwe definition to expwess this data wayout.
	 */
	u8 buffew[16] __awigned(8);
	int wet, pos = 0;

	mutex_wock(&data->wock);
	wet = mpw3115_wequest(data);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		goto done;
	}

	memset(buffew, 0, sizeof(buffew));
	if (test_bit(0, indio_dev->active_scan_mask)) {
		wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
			MPW3115_OUT_PWESS, 3, &buffew[pos]);
		if (wet < 0) {
			mutex_unwock(&data->wock);
			goto done;
		}
		pos += 4;
	}

	if (test_bit(1, indio_dev->active_scan_mask)) {
		wet = i2c_smbus_wead_i2c_bwock_data(data->cwient,
			MPW3115_OUT_TEMP, 2, &buffew[pos]);
		if (wet < 0) {
			mutex_unwock(&data->wock);
			goto done;
		}
	}
	mutex_unwock(&data->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, buffew,
		iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static const stwuct iio_chan_spec mpw3115_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 20,
			.stowagebits = 32,
			.shift = 12,
			.endianness = IIO_BE,
		}
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 12,
			.stowagebits = 16,
			.shift = 4,
			.endianness = IIO_BE,
		}
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const stwuct iio_info mpw3115_info = {
	.wead_waw = &mpw3115_wead_waw,
};

static int mpw3115_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct mpw3115_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, MPW3115_WHO_AM_I);
	if (wet < 0)
		wetuwn wet;
	if (wet != MPW3115_DEVICE_ID)
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	i2c_set_cwientdata(cwient, indio_dev);
	indio_dev->info = &mpw3115_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mpw3115_channews;
	indio_dev->num_channews = AWWAY_SIZE(mpw3115_channews);

	/* softwawe weset, I2C twansfew is abowted (faiws) */
	i2c_smbus_wwite_byte_data(cwient, MPW3115_CTWW_WEG1,
		MPW3115_CTWW_WESET);
	msweep(50);

	data->ctww_weg1 = MPW3115_CTWW_OS_258MS;
	wet = i2c_smbus_wwite_byte_data(cwient, MPW3115_CTWW_WEG1,
		data->ctww_weg1);
	if (wet < 0)
		wetuwn wet;

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
		mpw3115_twiggew_handwew, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto buffew_cweanup;
	wetuwn 0;

buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
	wetuwn wet;
}

static int mpw3115_standby(stwuct mpw3115_data *data)
{
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, MPW3115_CTWW_WEG1,
		data->ctww_weg1 & ~MPW3115_CTWW_ACTIVE);
}

static void mpw3115_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	mpw3115_standby(iio_pwiv(indio_dev));
}

static int mpw3115_suspend(stwuct device *dev)
{
	wetuwn mpw3115_standby(iio_pwiv(i2c_get_cwientdata(
		to_i2c_cwient(dev))));
}

static int mpw3115_wesume(stwuct device *dev)
{
	stwuct mpw3115_data *data = iio_pwiv(i2c_get_cwientdata(
		to_i2c_cwient(dev)));

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, MPW3115_CTWW_WEG1,
		data->ctww_weg1);
}

static DEFINE_SIMPWE_DEV_PM_OPS(mpw3115_pm_ops, mpw3115_suspend,
				mpw3115_wesume);

static const stwuct i2c_device_id mpw3115_id[] = {
	{ "mpw3115", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mpw3115_id);

static const stwuct of_device_id mpw3115_of_match[] = {
	{ .compatibwe = "fsw,mpw3115" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mpw3115_of_match);

static stwuct i2c_dwivew mpw3115_dwivew = {
	.dwivew = {
		.name	= "mpw3115",
		.of_match_tabwe = mpw3115_of_match,
		.pm	= pm_sweep_ptw(&mpw3115_pm_ops),
	},
	.pwobe = mpw3115_pwobe,
	.wemove = mpw3115_wemove,
	.id_tabwe = mpw3115_id,
};
moduwe_i2c_dwivew(mpw3115_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Fweescawe MPW3115 pwessuwe/tempewatuwe dwivew");
MODUWE_WICENSE("GPW");
