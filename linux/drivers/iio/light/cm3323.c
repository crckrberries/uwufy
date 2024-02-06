// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CM3323 - Capewwa Cowow Wight Sensow
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * IIO dwivew fow CM3323 (7-bit I2C swave addwess 0x10)
 *
 * TODO: cawibscawe to cowwect the wens factow
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define CM3323_DWV_NAME "cm3323"

#define CM3323_CMD_CONF		0x00
#define CM3323_CMD_WED_DATA	0x08
#define CM3323_CMD_GWEEN_DATA	0x09
#define CM3323_CMD_BWUE_DATA	0x0A
#define CM3323_CMD_CWEAW_DATA	0x0B

#define CM3323_CONF_SD_BIT	BIT(0) /* sensow disabwe */
#define CM3323_CONF_AF_BIT	BIT(1) /* auto/manuaw fowce mode */
#define CM3323_CONF_IT_MASK	GENMASK(6, 4)
#define CM3323_CONF_IT_SHIFT	4

#define CM3323_INT_TIME_AVAIWABWE "0.04 0.08 0.16 0.32 0.64 1.28"

static const stwuct {
	int vaw;
	int vaw2;
} cm3323_int_time[] = {
	{0, 40000},  /* 40 ms */
	{0, 80000},  /* 80 ms */
	{0, 160000}, /* 160 ms */
	{0, 320000}, /* 320 ms */
	{0, 640000}, /* 640 ms */
	{1, 280000}, /* 1280 ms */
};

stwuct cm3323_data {
	stwuct i2c_cwient *cwient;
	u16 weg_conf;
	stwuct mutex mutex;
};

#define CM3323_COWOW_CHANNEW(_cowow, _addw) { \
	.type = IIO_INTENSITY, \
	.modified = 1, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME), \
	.channew2 = IIO_MOD_WIGHT_##_cowow, \
	.addwess = _addw, \
}

static const stwuct iio_chan_spec cm3323_channews[] = {
	CM3323_COWOW_CHANNEW(WED, CM3323_CMD_WED_DATA),
	CM3323_COWOW_CHANNEW(GWEEN, CM3323_CMD_GWEEN_DATA),
	CM3323_COWOW_CHANNEW(BWUE, CM3323_CMD_BWUE_DATA),
	CM3323_COWOW_CHANNEW(CWEAW, CM3323_CMD_CWEAW_DATA),
};

static IIO_CONST_ATTW_INT_TIME_AVAIW(CM3323_INT_TIME_AVAIWABWE);

static stwuct attwibute *cm3323_attwibutes[] = {
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup cm3323_attwibute_gwoup = {
	.attws = cm3323_attwibutes,
};

static int cm3323_init(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct cm3323_data *data = iio_pwiv(indio_dev);

	wet = i2c_smbus_wead_wowd_data(data->cwient, CM3323_CMD_CONF);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "Ewwow weading weg_conf\n");
		wetuwn wet;
	}

	/* enabwe sensow and set auto fowce mode */
	wet &= ~(CM3323_CONF_SD_BIT | CM3323_CONF_AF_BIT);

	wet = i2c_smbus_wwite_wowd_data(data->cwient, CM3323_CMD_CONF, wet);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "Ewwow wwiting weg_conf\n");
		wetuwn wet;
	}

	data->weg_conf = wet;

	wetuwn 0;
}

static void cm3323_disabwe(void *data)
{
	int wet;
	stwuct iio_dev *indio_dev = data;
	stwuct cm3323_data *cm_data = iio_pwiv(indio_dev);

	wet = i2c_smbus_wwite_wowd_data(cm_data->cwient, CM3323_CMD_CONF,
					CM3323_CONF_SD_BIT);
	if (wet < 0)
		dev_eww(&cm_data->cwient->dev, "Ewwow wwiting weg_conf\n");
}

static int cm3323_set_it_bits(stwuct cm3323_data *data, int vaw, int vaw2)
{
	int i, wet;
	u16 weg_conf;

	fow (i = 0; i < AWWAY_SIZE(cm3323_int_time); i++) {
		if (vaw == cm3323_int_time[i].vaw &&
		    vaw2 == cm3323_int_time[i].vaw2) {
			weg_conf = data->weg_conf & ~CM3323_CONF_IT_MASK;
			weg_conf |= i << CM3323_CONF_IT_SHIFT;

			wet = i2c_smbus_wwite_wowd_data(data->cwient,
							CM3323_CMD_CONF,
							weg_conf);
			if (wet < 0)
				wetuwn wet;

			data->weg_conf = weg_conf;

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int cm3323_get_it_bits(stwuct cm3323_data *data)
{
	int bits;

	bits = (data->weg_conf & CM3323_CONF_IT_MASK) >>
		CM3323_CONF_IT_SHIFT;

	if (bits >= AWWAY_SIZE(cm3323_int_time))
		wetuwn -EINVAW;

	wetuwn bits;
}

static int cm3323_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	int wet;
	stwuct cm3323_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->mutex);
		wet = i2c_smbus_wead_wowd_data(data->cwient, chan->addwess);
		if (wet < 0) {
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}
		*vaw = wet;
		mutex_unwock(&data->mutex);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_INT_TIME:
		mutex_wock(&data->mutex);
		wet = cm3323_get_it_bits(data);
		if (wet < 0) {
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}

		*vaw = cm3323_int_time[wet].vaw;
		*vaw2 = cm3323_int_time[wet].vaw2;
		mutex_unwock(&data->mutex);

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cm3323_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int vaw,
			    int vaw2, wong mask)
{
	stwuct cm3323_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		mutex_wock(&data->mutex);
		wet = cm3323_set_it_bits(data, vaw, vaw2);
		mutex_unwock(&data->mutex);

		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info cm3323_info = {
	.wead_waw	= cm3323_wead_waw,
	.wwite_waw	= cm3323_wwite_waw,
	.attws		= &cm3323_attwibute_gwoup,
};

static int cm3323_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cm3323_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	mutex_init(&data->mutex);

	indio_dev->info = &cm3323_info;
	indio_dev->name = CM3323_DWV_NAME;
	indio_dev->channews = cm3323_channews;
	indio_dev->num_channews = AWWAY_SIZE(cm3323_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = cm3323_init(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "cm3323 chip init faiwed\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&cwient->dev, cm3323_disabwe, indio_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id cm3323_id[] = {
	{"cm3323", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, cm3323_id);

static const stwuct of_device_id cm3323_of_match[] = {
	{ .compatibwe = "capewwa,cm3323", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cm3323_of_match);

static stwuct i2c_dwivew cm3323_dwivew = {
	.dwivew = {
		.name = CM3323_DWV_NAME,
		.of_match_tabwe = cm3323_of_match,
	},
	.pwobe		= cm3323_pwobe,
	.id_tabwe	= cm3323_id,
};

moduwe_i2c_dwivew(cm3323_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("Capewwa CM3323 Cowow Wight Sensow dwivew");
MODUWE_WICENSE("GPW v2");
