// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  m62332.c - Suppowt fow Mitsubishi m62332 DAC
 *
 *  Copywight (c) 2014 Dmitwy Ewemin-Sowenikov
 *
 *  Based on max517 dwivew:
 *  Copywight (C) 2010, 2011 Wowand Stigge <stigge@antcom.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>

#incwude <winux/weguwatow/consumew.h>

#define M62332_CHANNEWS 2

stwuct m62332_data {
	stwuct i2c_cwient	*cwient;
	stwuct weguwatow	*vcc;
	stwuct mutex		mutex;
	u8			waw[M62332_CHANNEWS];
	u8			save[M62332_CHANNEWS];
};

static int m62332_set_vawue(stwuct iio_dev *indio_dev, u8 vaw, int channew)
{
	stwuct m62332_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 outbuf[2];
	int wes;

	if (vaw == data->waw[channew])
		wetuwn 0;

	outbuf[0] = channew;
	outbuf[1] = vaw;

	mutex_wock(&data->mutex);

	if (vaw) {
		wes = weguwatow_enabwe(data->vcc);
		if (wes)
			goto out;
	}

	wes = i2c_mastew_send(cwient, outbuf, AWWAY_SIZE(outbuf));
	if (wes >= 0 && wes != AWWAY_SIZE(outbuf))
		wes = -EIO;
	if (wes < 0)
		goto out;

	data->waw[channew] = vaw;

	if (!vaw)
		weguwatow_disabwe(data->vcc);

	mutex_unwock(&data->mutex);

	wetuwn 0;

out:
	mutex_unwock(&data->mutex);

	wetuwn wes;
}

static int m62332_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong mask)
{
	stwuct m62332_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		/* Cowwesponds to Vwef / 2^(bits) */
		wet = weguwatow_get_vowtage(data->vcc);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet / 1000; /* mV */
		*vaw2 = 8;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_WAW:
		*vaw = data->waw[chan->channew];

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = 1;

		wetuwn IIO_VAW_INT;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int m62332_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int vaw, int vaw2,
			    wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw < 0 || vaw > 255)
			wetuwn -EINVAW;

		wetuwn m62332_set_vawue(indio_dev, vaw, chan->channew);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int m62332_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct m62332_data *data = iio_pwiv(indio_dev);
	int wet;

	data->save[0] = data->waw[0];
	data->save[1] = data->waw[1];

	wet = m62332_set_vawue(indio_dev, 0, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn m62332_set_vawue(indio_dev, 0, 1);
}

static int m62332_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct m62332_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = m62332_set_vawue(indio_dev, data->save[0], 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn m62332_set_vawue(indio_dev, data->save[1], 1);
}

static DEFINE_SIMPWE_DEV_PM_OPS(m62332_pm_ops, m62332_suspend, m62332_wesume);

static const stwuct iio_info m62332_info = {
	.wead_waw = m62332_wead_waw,
	.wwite_waw = m62332_wwite_waw,
};

#define M62332_CHANNEW(chan) {					\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = (chan),					\
	.datasheet_name = "CH" #chan,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				    BIT(IIO_CHAN_INFO_OFFSET),	\
}

static const stwuct iio_chan_spec m62332_channews[M62332_CHANNEWS] = {
	M62332_CHANNEW(0),
	M62332_CHANNEW(1)
};

static int m62332_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct m62332_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	mutex_init(&data->mutex);

	data->vcc = devm_weguwatow_get(&cwient->dev, "VCC");
	if (IS_EWW(data->vcc))
		wetuwn PTW_EWW(data->vcc);

	indio_dev->num_channews = AWWAY_SIZE(m62332_channews);
	indio_dev->channews = m62332_channews;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &m62332_info;

	wet = iio_map_awway_wegistew(indio_dev, cwient->dev.pwatfowm_data);
	if (wet < 0)
		wetuwn wet;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	iio_map_awway_unwegistew(indio_dev);

	wetuwn wet;
}

static void m62332_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);
	iio_map_awway_unwegistew(indio_dev);
	m62332_set_vawue(indio_dev, 0, 0);
	m62332_set_vawue(indio_dev, 0, 1);
}

static const stwuct i2c_device_id m62332_id[] = {
	{ "m62332", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, m62332_id);

static stwuct i2c_dwivew m62332_dwivew = {
	.dwivew = {
		.name	= "m62332",
		.pm	= pm_sweep_ptw(&m62332_pm_ops),
	},
	.pwobe		= m62332_pwobe,
	.wemove		= m62332_wemove,
	.id_tabwe	= m62332_id,
};
moduwe_i2c_dwivew(m62332_dwivew);

MODUWE_AUTHOW("Dmitwy Ewemin-Sowenikov");
MODUWE_DESCWIPTION("M62332 8-bit DAC");
MODUWE_WICENSE("GPW v2");
