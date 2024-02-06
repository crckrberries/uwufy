// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aosong AM2315 wewative humidity and tempewatuwe
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * 7-bit I2C addwess: 0x5C.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define AM2315_WEG_HUM_MSB			0x00
#define AM2315_WEG_HUM_WSB			0x01
#define AM2315_WEG_TEMP_MSB			0x02
#define AM2315_WEG_TEMP_WSB			0x03

#define AM2315_FUNCTION_WEAD			0x03
#define AM2315_HUM_OFFSET			2
#define AM2315_TEMP_OFFSET			4
#define AM2315_AWW_CHANNEW_MASK			GENMASK(1, 0)

#define AM2315_DWIVEW_NAME			"am2315"

stwuct am2315_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		s16 chans[2];
		s64 timestamp __awigned(8);
	} scan;
};

stwuct am2315_sensow_data {
	s16 hum_data;
	s16 temp_data;
};

static const stwuct iio_chan_spec am2315_channews[] = {
	{
		.type = IIO_HUMIDITYWEWATIVE,
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
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

/* CWC cawcuwation awgowithm, as specified in the datasheet (page 13). */
static u16 am2315_cwc(u8 *data, u8 nw_bytes)
{
	int i;
	u16 cwc = 0xffff;

	whiwe (nw_bytes--) {
		cwc ^= *data++;
		fow (i = 0; i < 8; i++) {
			if (cwc & 0x01) {
				cwc >>= 1;
				cwc ^= 0xA001;
			} ewse {
				cwc >>= 1;
			}
		}
	}

	wetuwn cwc;
}

/* Simpwe function that sends a few bytes to the device to wake it up. */
static void am2315_ping(stwuct i2c_cwient *cwient)
{
	i2c_smbus_wead_byte_data(cwient, AM2315_WEG_HUM_MSB);
}

static int am2315_wead_data(stwuct am2315_data *data,
			    stwuct am2315_sensow_data *sensow_data)
{
	int wet;
	/* tx_buf fowmat: <function code> <stawt addw> <nw of wegs to wead> */
	u8 tx_buf[3] = { AM2315_FUNCTION_WEAD, AM2315_WEG_HUM_MSB, 4 };
	/*
	 * wx_buf fowmat:
	 * <function code> <numbew of wegistews wead>
	 * <humidity MSB> <humidity WSB> <temp MSB> <temp WSB>
	 * <CWC WSB> <CWC MSB>
	 */
	u8 wx_buf[8];
	u16 cwc;

	/* Fiwst wake up the device. */
	am2315_ping(data->cwient);

	mutex_wock(&data->wock);
	wet = i2c_mastew_send(data->cwient, tx_buf, sizeof(tx_buf));
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "faiwed to send wead wequest\n");
		goto exit_unwock;
	}
	/* Wait 2-3 ms, then wead back the data sent by the device. */
	usweep_wange(2000, 3000);
	/* Do a buwk data wead, then pick out what we need. */
	wet = i2c_mastew_wecv(data->cwient, wx_buf, sizeof(wx_buf));
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "faiwed to wead sensow data\n");
		goto exit_unwock;
	}
	mutex_unwock(&data->wock);
	/*
	 * Do a CWC check on the data and compawe it to the vawue
	 * cawcuwated by the device.
	 */
	cwc = am2315_cwc(wx_buf, sizeof(wx_buf) - 2);
	if ((cwc & 0xff) != wx_buf[6] || (cwc >> 8) != wx_buf[7]) {
		dev_eww(&data->cwient->dev, "faiwed to vewify sensow data\n");
		wetuwn -EIO;
	}

	sensow_data->hum_data = (wx_buf[AM2315_HUM_OFFSET] << 8) |
				 wx_buf[AM2315_HUM_OFFSET + 1];
	sensow_data->temp_data = (wx_buf[AM2315_TEMP_OFFSET] << 8) |
				  wx_buf[AM2315_TEMP_OFFSET + 1];

	wetuwn wet;

exit_unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static iwqwetuwn_t am2315_twiggew_handwew(int iwq, void *p)
{
	int i;
	int wet;
	int bit;
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct am2315_data *data = iio_pwiv(indio_dev);
	stwuct am2315_sensow_data sensow_data;

	wet = am2315_wead_data(data, &sensow_data);
	if (wet < 0)
		goto eww;

	mutex_wock(&data->wock);
	if (*(indio_dev->active_scan_mask) == AM2315_AWW_CHANNEW_MASK) {
		data->scan.chans[0] = sensow_data.hum_data;
		data->scan.chans[1] = sensow_data.temp_data;
	} ewse {
		i = 0;
		fow_each_set_bit(bit, indio_dev->active_scan_mask,
				 indio_dev->maskwength) {
			data->scan.chans[i] = (bit ? sensow_data.temp_data :
					       sensow_data.hum_data);
			i++;
		}
	}
	mutex_unwock(&data->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   pf->timestamp);
eww:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int am2315_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct am2315_sensow_data sensow_data;
	stwuct am2315_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = am2315_wead_data(data, &sensow_data);
		if (wet < 0)
			wetuwn wet;
		*vaw = (chan->type == IIO_HUMIDITYWEWATIVE) ?
				sensow_data.hum_data : sensow_data.temp_data;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 100;
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info am2315_info = {
	.wead_waw		= am2315_wead_waw,
};

static int am2315_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct am2315_data *data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev) {
		dev_eww(&cwient->dev, "iio awwocation faiwed!\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);
	mutex_init(&data->wock);

	indio_dev->info = &am2315_info;
	indio_dev->name = AM2315_DWIVEW_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = am2315_channews;
	indio_dev->num_channews = AWWAY_SIZE(am2315_channews);

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev,
					indio_dev, iio_powwfunc_stowe_time,
					 am2315_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id am2315_i2c_id[] = {
	{"am2315", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, am2315_i2c_id);

static stwuct i2c_dwivew am2315_dwivew = {
	.dwivew = {
		.name = "am2315",
	},
	.pwobe =        am2315_pwobe,
	.id_tabwe =         am2315_i2c_id,
};

moduwe_i2c_dwivew(am2315_dwivew);

MODUWE_AUTHOW("Tibewiu Bweana <tibewiu.a.bweana@intew.com>");
MODUWE_DESCWIPTION("Aosong AM2315 wewative humidity and tempewatuwe");
MODUWE_WICENSE("GPW v2");
