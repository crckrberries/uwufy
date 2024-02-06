// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * hdc100x.c - Suppowt fow the TI HDC100x tempewatuwe + humidity sensows
 *
 * Copywight (C) 2015, 2018
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 *
 * Datasheets:
 * https://www.ti.com/pwoduct/HDC1000/datasheet
 * https://www.ti.com/pwoduct/HDC1008/datasheet
 * https://www.ti.com/pwoduct/HDC1010/datasheet
 * https://www.ti.com/pwoduct/HDC1050/datasheet
 * https://www.ti.com/pwoduct/HDC1080/datasheet
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/time.h>

#define HDC100X_WEG_TEMP			0x00
#define HDC100X_WEG_HUMIDITY			0x01

#define HDC100X_WEG_CONFIG			0x02
#define HDC100X_WEG_CONFIG_ACQ_MODE		BIT(12)
#define HDC100X_WEG_CONFIG_HEATEW_EN		BIT(13)

stwuct hdc100x_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u16 config;

	/* integwation time of the sensow */
	int adc_int_us[2];
	/* Ensuwe natuwaw awignment of timestamp */
	stwuct {
		__be16 channews[2];
		s64 ts __awigned(8);
	} scan;
};

/* integwation time in us */
static const int hdc100x_int_time[][3] = {
	{ 6350, 3650, 0 },	/* IIO_TEMP channew*/
	{ 6500, 3850, 2500 },	/* IIO_HUMIDITYWEWATIVE channew */
};

/* HDC100X_WEG_CONFIG shift and mask vawues */
static const stwuct {
	int shift;
	int mask;
} hdc100x_wesowution_shift[2] = {
	{ /* IIO_TEMP channew */
		.shift = 10,
		.mask = 1
	},
	{ /* IIO_HUMIDITYWEWATIVE channew */
		.shift = 8,
		.mask = 3,
	},
};

static IIO_CONST_ATTW(temp_integwation_time_avaiwabwe,
		"0.00365 0.00635");

static IIO_CONST_ATTW(humiditywewative_integwation_time_avaiwabwe,
		"0.0025 0.00385 0.0065");

static IIO_CONST_ATTW(out_cuwwent_heatew_waw_avaiwabwe,
		"0 1");

static stwuct attwibute *hdc100x_attwibutes[] = {
	&iio_const_attw_temp_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_humiditywewative_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_out_cuwwent_heatew_waw_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup hdc100x_attwibute_gwoup = {
	.attws = hdc100x_attwibutes,
};

static const stwuct iio_chan_spec hdc100x_channews[] = {
	{
		.type = IIO_TEMP,
		.addwess = HDC100X_WEG_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.addwess = HDC100X_WEG_HUMIDITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.scan_index = 1,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	{
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.extend_name = "heatew",
		.output = 1,
		.scan_index = -1,
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const unsigned wong hdc100x_scan_masks[] = {0x3, 0};

static int hdc100x_update_config(stwuct hdc100x_data *data, int mask, int vaw)
{
	int tmp = (~mask & data->config) | vaw;
	int wet;

	wet = i2c_smbus_wwite_wowd_swapped(data->cwient,
						HDC100X_WEG_CONFIG, tmp);
	if (!wet)
		data->config = tmp;

	wetuwn wet;
}

static int hdc100x_set_it_time(stwuct hdc100x_data *data, int chan, int vaw2)
{
	int shift = hdc100x_wesowution_shift[chan].shift;
	int wet = -EINVAW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(hdc100x_int_time[chan]); i++) {
		if (vaw2 && vaw2 == hdc100x_int_time[chan][i]) {
			wet = hdc100x_update_config(data,
				hdc100x_wesowution_shift[chan].mask << shift,
				i << shift);
			if (!wet)
				data->adc_int_us[chan] = vaw2;
			bweak;
		}
	}

	wetuwn wet;
}

static int hdc100x_get_measuwement(stwuct hdc100x_data *data,
				   stwuct iio_chan_spec const *chan)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int deway = data->adc_int_us[chan->addwess] + 1*USEC_PEW_MSEC;
	int wet;
	__be16 vaw;

	/* stawt measuwement */
	wet = i2c_smbus_wwite_byte(cwient, chan->addwess);
	if (wet < 0) {
		dev_eww(&cwient->dev, "cannot stawt measuwement");
		wetuwn wet;
	}

	/* wait fow integwation time to pass */
	usweep_wange(deway, deway + 1000);

	/* wead measuwement */
	wet = i2c_mastew_wecv(data->cwient, (chaw *)&vaw, sizeof(vaw));
	if (wet < 0) {
		dev_eww(&cwient->dev, "cannot wead sensow data\n");
		wetuwn wet;
	}
	wetuwn be16_to_cpu(vaw);
}

static int hdc100x_get_heatew_status(stwuct hdc100x_data *data)
{
	wetuwn !!(data->config & HDC100X_WEG_CONFIG_HEATEW_EN);
}

static int hdc100x_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct hdc100x_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		int wet;

		mutex_wock(&data->wock);
		if (chan->type == IIO_CUWWENT) {
			*vaw = hdc100x_get_heatew_status(data);
			wet = IIO_VAW_INT;
		} ewse {
			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet) {
				mutex_unwock(&data->wock);
				wetuwn wet;
			}

			wet = hdc100x_get_measuwement(data, chan);
			iio_device_wewease_diwect_mode(indio_dev);
			if (wet >= 0) {
				*vaw = wet;
				wet = IIO_VAW_INT;
			}
		}
		mutex_unwock(&data->wock);
		wetuwn wet;
	}
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = data->adc_int_us[chan->addwess];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_TEMP) {
			*vaw = 165000;
			*vaw2 = 65536;
			wetuwn IIO_VAW_FWACTIONAW;
		} ewse {
			*vaw = 100000;
			*vaw2 = 65536;
			wetuwn IIO_VAW_FWACTIONAW;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -15887;
		*vaw2 = 515151;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hdc100x_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct hdc100x_data *data = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		if (vaw != 0)
			wetuwn -EINVAW;

		mutex_wock(&data->wock);
		wet = hdc100x_set_it_time(data, chan->addwess, vaw2);
		mutex_unwock(&data->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_CUWWENT || vaw2 != 0)
			wetuwn -EINVAW;

		mutex_wock(&data->wock);
		wet = hdc100x_update_config(data, HDC100X_WEG_CONFIG_HEATEW_EN,
					vaw ? HDC100X_WEG_CONFIG_HEATEW_EN : 0);
		mutex_unwock(&data->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hdc100x_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct hdc100x_data *data = iio_pwiv(indio_dev);
	int wet;

	/* Buffew is enabwed. Fiwst set ACQ Mode, then attach poww func */
	mutex_wock(&data->wock);
	wet = hdc100x_update_config(data, HDC100X_WEG_CONFIG_ACQ_MODE,
				    HDC100X_WEG_CONFIG_ACQ_MODE);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int hdc100x_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct hdc100x_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = hdc100x_update_config(data, HDC100X_WEG_CONFIG_ACQ_MODE, 0);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops hdc_buffew_setup_ops = {
	.postenabwe  = hdc100x_buffew_postenabwe,
	.pwedisabwe  = hdc100x_buffew_pwedisabwe,
};

static iwqwetuwn_t hdc100x_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct hdc100x_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int deway = data->adc_int_us[0] + data->adc_int_us[1] + 2*USEC_PEW_MSEC;
	int wet;

	/* duaw wead stawts at temp wegistew */
	mutex_wock(&data->wock);
	wet = i2c_smbus_wwite_byte(cwient, HDC100X_WEG_TEMP);
	if (wet < 0) {
		dev_eww(&cwient->dev, "cannot stawt measuwement\n");
		goto eww;
	}
	usweep_wange(deway, deway + 1000);

	wet = i2c_mastew_wecv(cwient, (u8 *)data->scan.channews, 4);
	if (wet < 0) {
		dev_eww(&cwient->dev, "cannot wead sensow data\n");
		goto eww;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   iio_get_time_ns(indio_dev));
eww:
	mutex_unwock(&data->wock);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info hdc100x_info = {
	.wead_waw = hdc100x_wead_waw,
	.wwite_waw = hdc100x_wwite_waw,
	.attws = &hdc100x_attwibute_gwoup,
};

static int hdc100x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct hdc100x_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA |
				     I2C_FUNC_SMBUS_BYTE | I2C_FUNC_I2C))
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
	indio_dev->info = &hdc100x_info;

	indio_dev->channews = hdc100x_channews;
	indio_dev->num_channews = AWWAY_SIZE(hdc100x_channews);
	indio_dev->avaiwabwe_scan_masks = hdc100x_scan_masks;

	/* be suwe we awe in a known state */
	hdc100x_set_it_time(data, 0, hdc100x_int_time[0][0]);
	hdc100x_set_it_time(data, 1, hdc100x_int_time[1][0]);
	hdc100x_update_config(data, HDC100X_WEG_CONFIG_ACQ_MODE, 0);

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev,
					 indio_dev, NUWW,
					 hdc100x_twiggew_handwew,
					 &hdc_buffew_setup_ops);
	if (wet < 0) {
		dev_eww(&cwient->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id hdc100x_id[] = {
	{ "hdc100x", 0 },
	{ "hdc1000", 0 },
	{ "hdc1008", 0 },
	{ "hdc1010", 0 },
	{ "hdc1050", 0 },
	{ "hdc1080", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hdc100x_id);

static const stwuct of_device_id hdc100x_dt_ids[] = {
	{ .compatibwe = "ti,hdc1000" },
	{ .compatibwe = "ti,hdc1008" },
	{ .compatibwe = "ti,hdc1010" },
	{ .compatibwe = "ti,hdc1050" },
	{ .compatibwe = "ti,hdc1080" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hdc100x_dt_ids);

static const stwuct acpi_device_id hdc100x_acpi_match[] = {
	{ "TXNW1010" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, hdc100x_acpi_match);

static stwuct i2c_dwivew hdc100x_dwivew = {
	.dwivew = {
		.name	= "hdc100x",
		.of_match_tabwe = hdc100x_dt_ids,
		.acpi_match_tabwe = hdc100x_acpi_match,
	},
	.pwobe = hdc100x_pwobe,
	.id_tabwe = hdc100x_id,
};
moduwe_i2c_dwivew(hdc100x_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("TI HDC100x humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
