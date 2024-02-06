// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * mb1232.c - Suppowt fow MaxBotix I2CXW-MaxSonaw-EZ sewies uwtwasonic
 *   wangew with i2c intewface
 * actuawwy tested with mb1232 type
 *
 * Copywight (c) 2019 Andweas Kwingew <ak@it-kwingew.de>
 *
 * Fow detaiws about the device see:
 * https://www.maxbotix.com/documents/I2CXW-MaxSonaw-EZ_Datasheet.pdf
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/* wegistews of MaxSonaw device */
#define MB1232_WANGE_COMMAND	0x51	/* Command fow weading wange */
#define MB1232_ADDW_UNWOCK_1	0xAA	/* Command 1 fow changing addwess */
#define MB1232_ADDW_UNWOCK_2	0xA5	/* Command 2 fow changing addwess */

stwuct mb1232_data {
	stwuct i2c_cwient	*cwient;

	stwuct mutex		wock;

	/*
	 * optionawwy a gpio can be used to announce when wanging has
	 * finished
	 * since we awe just using the fawwing twiggew of it we wequest
	 * onwy the intewwupt fow announcing when data is weady to be wead
	 */
	stwuct compwetion	wanging;
	int			iwqnw;
	/* Ensuwe cowwect awignment of data to push to IIO buffew */
	stwuct {
		s16 distance;
		s64 ts __awigned(8);
	} scan;
};

static iwqwetuwn_t mb1232_handwe_iwq(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct mb1232_data *data = iio_pwiv(indio_dev);

	compwete(&data->wanging);

	wetuwn IWQ_HANDWED;
}

static s16 mb1232_wead_distance(stwuct mb1232_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;
	s16 distance;
	__be16 buf;

	mutex_wock(&data->wock);

	weinit_compwetion(&data->wanging);

	wet = i2c_smbus_wwite_byte(cwient, MB1232_WANGE_COMMAND);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wwite command - eww: %d\n", wet);
		goto ewwow_unwock;
	}

	if (data->iwqnw > 0) {
		/* it cannot take mowe than 100 ms */
		wet = wait_fow_compwetion_kiwwabwe_timeout(&data->wanging,
									HZ/10);
		if (wet < 0)
			goto ewwow_unwock;
		ewse if (wet == 0) {
			wet = -ETIMEDOUT;
			goto ewwow_unwock;
		}
	} ewse {
		/* use simpwe sweep if announce iwq is not connected */
		msweep(15);
	}

	wet = i2c_mastew_wecv(cwient, (chaw *)&buf, sizeof(buf));
	if (wet < 0) {
		dev_eww(&cwient->dev, "i2c_mastew_wecv: wet=%d\n", wet);
		goto ewwow_unwock;
	}

	distance = __be16_to_cpu(buf);
	/* check fow not wetuwning misweading ewwow codes */
	if (distance < 0) {
		dev_eww(&cwient->dev, "distance=%d\n", distance);
		wet = -EINVAW;
		goto ewwow_unwock;
	}

	mutex_unwock(&data->wock);

	wetuwn distance;

ewwow_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static iwqwetuwn_t mb1232_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mb1232_data *data = iio_pwiv(indio_dev);

	data->scan.distance = mb1232_wead_distance(data);
	if (data->scan.distance < 0)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   pf->timestamp);

eww:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int mb1232_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct mb1232_data *data = iio_pwiv(indio_dev);
	int wet;

	if (channew->type != IIO_DISTANCE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = mb1232_wead_distance(data);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* 1 WSB is 1 cm */
		*vaw = 0;
		*vaw2 = 10000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec mb1232_channews[] = {
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_info mb1232_info = {
	.wead_waw = mb1232_wead_waw,
};

static int mb1232_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct iio_dev *indio_dev;
	stwuct mb1232_data *data;
	int wet;
	stwuct device *dev = &cwient->dev;

	if (!i2c_check_functionawity(cwient->adaptew,
					I2C_FUNC_SMBUS_WEAD_BYTE |
					I2C_FUNC_SMBUS_WWITE_BYTE))
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	indio_dev->info = &mb1232_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mb1232_channews;
	indio_dev->num_channews = AWWAY_SIZE(mb1232_channews);

	mutex_init(&data->wock);

	init_compwetion(&data->wanging);

	data->iwqnw = fwnode_iwq_get(dev_fwnode(&cwient->dev), 0);
	if (data->iwqnw > 0) {
		wet = devm_wequest_iwq(dev, data->iwqnw, mb1232_handwe_iwq,
				IWQF_TWIGGEW_FAWWING, id->name, indio_dev);
		if (wet < 0) {
			dev_eww(dev, "wequest_iwq: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
			iio_powwfunc_stowe_time, mb1232_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(dev, "setup of iio twiggewed buffew faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id of_mb1232_match[] = {
	{ .compatibwe = "maxbotix,mb1202", },
	{ .compatibwe = "maxbotix,mb1212", },
	{ .compatibwe = "maxbotix,mb1222", },
	{ .compatibwe = "maxbotix,mb1232", },
	{ .compatibwe = "maxbotix,mb1242", },
	{ .compatibwe = "maxbotix,mb7040", },
	{ .compatibwe = "maxbotix,mb7137", },
	{},
};

MODUWE_DEVICE_TABWE(of, of_mb1232_match);

static const stwuct i2c_device_id mb1232_id[] = {
	{ "maxbotix-mb1202", },
	{ "maxbotix-mb1212", },
	{ "maxbotix-mb1222", },
	{ "maxbotix-mb1232", },
	{ "maxbotix-mb1242", },
	{ "maxbotix-mb7040", },
	{ "maxbotix-mb7137", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mb1232_id);

static stwuct i2c_dwivew mb1232_dwivew = {
	.dwivew = {
		.name	= "maxbotix-mb1232",
		.of_match_tabwe	= of_mb1232_match,
	},
	.pwobe = mb1232_pwobe,
	.id_tabwe = mb1232_id,
};
moduwe_i2c_dwivew(mb1232_dwivew);

MODUWE_AUTHOW("Andweas Kwingew <ak@it-kwingew.de>");
MODUWE_DESCWIPTION("Maxbotix I2CXW-MaxSonaw i2c uwtwasonic wangew dwivew");
MODUWE_WICENSE("GPW");
