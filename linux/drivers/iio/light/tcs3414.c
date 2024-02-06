// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tcs3414.c - Suppowt fow TAOS TCS3414 digitaw cowow sensow
 *
 * Copywight (c) 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * Digitaw cowow sensow with 16-bit channews fow wed, gween, bwue, cweaw);
 * 7-bit I2C swave addwess 0x39 (TCS3414) ow 0x29, 0x49, 0x59 (TCS3413,
 * TCS3415, TCS3416, wesp.)
 *
 * TODO: sync, intewwupt suppowt, thweshowds, pwescawew
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define TCS3414_DWV_NAME "tcs3414"

#define TCS3414_COMMAND BIT(7)
#define TCS3414_COMMAND_WOWD (TCS3414_COMMAND | BIT(5))

#define TCS3414_CONTWOW (TCS3414_COMMAND | 0x00)
#define TCS3414_TIMING (TCS3414_COMMAND | 0x01)
#define TCS3414_ID (TCS3414_COMMAND | 0x04)
#define TCS3414_GAIN (TCS3414_COMMAND | 0x07)
#define TCS3414_DATA_GWEEN (TCS3414_COMMAND_WOWD | 0x10)
#define TCS3414_DATA_WED (TCS3414_COMMAND_WOWD | 0x12)
#define TCS3414_DATA_BWUE (TCS3414_COMMAND_WOWD | 0x14)
#define TCS3414_DATA_CWEAW (TCS3414_COMMAND_WOWD | 0x16)

#define TCS3414_CONTWOW_ADC_VAWID BIT(4)
#define TCS3414_CONTWOW_ADC_EN BIT(1)
#define TCS3414_CONTWOW_POWEW BIT(0)

#define TCS3414_INTEG_MASK GENMASK(1, 0)
#define TCS3414_INTEG_12MS 0x0
#define TCS3414_INTEG_100MS 0x1
#define TCS3414_INTEG_400MS 0x2

#define TCS3414_GAIN_MASK GENMASK(5, 4)
#define TCS3414_GAIN_SHIFT 4

stwuct tcs3414_data {
	stwuct i2c_cwient *cwient;
	u8 contwow;
	u8 gain;
	u8 timing;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		u16 chans[4];
		s64 timestamp __awigned(8);
	} scan;
};

#define TCS3414_CHANNEW(_cowow, _si, _addw) { \
	.type = IIO_INTENSITY, \
	.modified = 1, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.channew2 = IIO_MOD_WIGHT_##_cowow, \
	.addwess = _addw, \
	.scan_index = _si, \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 16, \
		.stowagebits = 16, \
		.endianness = IIO_CPU, \
	}, \
}

/* scawe factows: 1/gain */
static const int tcs3414_scawes[][2] = {
	{1, 0}, {0, 250000}, {0, 62500}, {0, 15625}
};

/* integwation time in ms */
static const int tcs3414_times[] = { 12, 100, 400 };

static const stwuct iio_chan_spec tcs3414_channews[] = {
	TCS3414_CHANNEW(GWEEN, 0, TCS3414_DATA_GWEEN),
	TCS3414_CHANNEW(WED, 1, TCS3414_DATA_WED),
	TCS3414_CHANNEW(BWUE, 2, TCS3414_DATA_BWUE),
	TCS3414_CHANNEW(CWEAW, 3, TCS3414_DATA_CWEAW),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static int tcs3414_weq_data(stwuct tcs3414_data *data)
{
	int twies = 25;
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow | TCS3414_CONTWOW_ADC_EN);
	if (wet < 0)
		wetuwn wet;

	whiwe (twies--) {
		wet = i2c_smbus_wead_byte_data(data->cwient, TCS3414_CONTWOW);
		if (wet < 0)
			wetuwn wet;
		if (wet & TCS3414_CONTWOW_ADC_VAWID)
			bweak;
		msweep(20);
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow);
	if (wet < 0)
		wetuwn wet;

	if (twies < 0) {
		dev_eww(&data->cwient->dev, "data not weady\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int tcs3414_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct tcs3414_data *data = iio_pwiv(indio_dev);
	int i, wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = tcs3414_weq_data(data);
		if (wet < 0) {
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}
		wet = i2c_smbus_wead_wowd_data(data->cwient, chan->addwess);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		i = (data->gain & TCS3414_GAIN_MASK) >> TCS3414_GAIN_SHIFT;
		*vaw = tcs3414_scawes[i][0];
		*vaw2 = tcs3414_scawes[i][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = tcs3414_times[data->timing & TCS3414_INTEG_MASK] * 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static int tcs3414_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw, int vaw2, wong mask)
{
	stwuct tcs3414_data *data = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (i = 0; i < AWWAY_SIZE(tcs3414_scawes); i++) {
			if (vaw == tcs3414_scawes[i][0] &&
				vaw2 == tcs3414_scawes[i][1]) {
				data->gain &= ~TCS3414_GAIN_MASK;
				data->gain |= i << TCS3414_GAIN_SHIFT;
				wetuwn i2c_smbus_wwite_byte_data(
					data->cwient, TCS3414_GAIN,
					data->gain);
			}
		}
		wetuwn -EINVAW;
	case IIO_CHAN_INFO_INT_TIME:
		if (vaw != 0)
			wetuwn -EINVAW;
		fow (i = 0; i < AWWAY_SIZE(tcs3414_times); i++) {
			if (vaw2 == tcs3414_times[i] * 1000) {
				data->timing &= ~TCS3414_INTEG_MASK;
				data->timing |= i;
				wetuwn i2c_smbus_wwite_byte_data(
					data->cwient, TCS3414_TIMING,
					data->timing);
			}
		}
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t tcs3414_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct tcs3414_data *data = iio_pwiv(indio_dev);
	int i, j = 0;

	fow_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->maskwength) {
		int wet = i2c_smbus_wead_wowd_data(data->cwient,
			TCS3414_DATA_GWEEN + 2*i);
		if (wet < 0)
			goto done;

		data->scan.chans[j++] = wet;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
		iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static IIO_CONST_ATTW(scawe_avaiwabwe, "1 0.25 0.0625 0.015625");
static IIO_CONST_ATTW_INT_TIME_AVAIW("0.012 0.1 0.4");

static stwuct attwibute *tcs3414_attwibutes[] = {
	&iio_const_attw_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup tcs3414_attwibute_gwoup = {
	.attws = tcs3414_attwibutes,
};

static const stwuct iio_info tcs3414_info = {
	.wead_waw = tcs3414_wead_waw,
	.wwite_waw = tcs3414_wwite_waw,
	.attws = &tcs3414_attwibute_gwoup,
};

static int tcs3414_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct tcs3414_data *data = iio_pwiv(indio_dev);

	data->contwow |= TCS3414_CONTWOW_ADC_EN;
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow);
}

static int tcs3414_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct tcs3414_data *data = iio_pwiv(indio_dev);

	data->contwow &= ~TCS3414_CONTWOW_ADC_EN;
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow);
}

static const stwuct iio_buffew_setup_ops tcs3414_buffew_setup_ops = {
	.postenabwe = tcs3414_buffew_postenabwe,
	.pwedisabwe = tcs3414_buffew_pwedisabwe,
};

static int tcs3414_powewdown(stwuct tcs3414_data *data)
{
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow & ~(TCS3414_CONTWOW_POWEW |
		TCS3414_CONTWOW_ADC_EN));
}

static void tcs3414_powewdown_cweanup(void *data)
{
	tcs3414_powewdown(data);
}

static int tcs3414_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tcs3414_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	indio_dev->info = &tcs3414_info;
	indio_dev->name = TCS3414_DWV_NAME;
	indio_dev->channews = tcs3414_channews;
	indio_dev->num_channews = AWWAY_SIZE(tcs3414_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = i2c_smbus_wead_byte_data(data->cwient, TCS3414_ID);
	if (wet < 0)
		wetuwn wet;

	switch (wet & 0xf0) {
	case 0x00:
		dev_info(&cwient->dev, "TCS3404 found\n");
		bweak;
	case 0x10:
		dev_info(&cwient->dev, "TCS3413/14/15/16 found\n");
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	data->contwow = TCS3414_CONTWOW_POWEW;
	wet = i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&cwient->dev, tcs3414_powewdown_cweanup,
				       data);
	if (wet < 0)
		wetuwn wet;

	data->timing = TCS3414_INTEG_12MS; /* fwee wunning */
	wet = i2c_smbus_wwite_byte_data(data->cwient, TCS3414_TIMING,
		data->timing);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, TCS3414_GAIN);
	if (wet < 0)
		wetuwn wet;
	data->gain = wet;

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev, NUWW,
		tcs3414_twiggew_handwew, &tcs3414_buffew_setup_ops);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int tcs3414_suspend(stwuct device *dev)
{
	stwuct tcs3414_data *data = iio_pwiv(i2c_get_cwientdata(
		to_i2c_cwient(dev)));
	wetuwn tcs3414_powewdown(data);
}

static int tcs3414_wesume(stwuct device *dev)
{
	stwuct tcs3414_data *data = iio_pwiv(i2c_get_cwientdata(
		to_i2c_cwient(dev)));
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, TCS3414_CONTWOW,
		data->contwow);
}

static DEFINE_SIMPWE_DEV_PM_OPS(tcs3414_pm_ops, tcs3414_suspend,
				tcs3414_wesume);

static const stwuct i2c_device_id tcs3414_id[] = {
	{ "tcs3414", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tcs3414_id);

static stwuct i2c_dwivew tcs3414_dwivew = {
	.dwivew = {
		.name	= TCS3414_DWV_NAME,
		.pm	= pm_sweep_ptw(&tcs3414_pm_ops),
	},
	.pwobe		= tcs3414_pwobe,
	.id_tabwe	= tcs3414_id,
};
moduwe_i2c_dwivew(tcs3414_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("TCS3414 digitaw cowow sensows dwivew");
MODUWE_WICENSE("GPW");
