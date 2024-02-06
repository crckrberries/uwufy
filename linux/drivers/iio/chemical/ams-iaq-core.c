// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ams-iaq-cowe.c - Suppowt fow AMS iAQ-Cowe VOC sensows
 *
 * Copywight (C) 2015, 2018
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>

#define AMS_IAQCOWE_DATA_SIZE		9

#define AMS_IAQCOWE_VOC_CO2_IDX		0
#define AMS_IAQCOWE_VOC_WESISTANCE_IDX	1
#define AMS_IAQCOWE_VOC_TVOC_IDX	2

stwuct ams_iaqcowe_weading {
	__be16 co2_ppm;
	u8 status;
	__be32 wesistance;
	__be16 voc_ppb;
} __attwibute__((__packed__));

stwuct ams_iaqcowe_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	unsigned wong wast_update;

	stwuct ams_iaqcowe_weading buffew;
};

static const stwuct iio_chan_spec ams_iaqcowe_channews[] = {
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = AMS_IAQCOWE_VOC_CO2_IDX,
	},
	{
		.type = IIO_WESISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = AMS_IAQCOWE_VOC_WESISTANCE_IDX,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_VOC,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.addwess = AMS_IAQCOWE_VOC_TVOC_IDX,
	},
};

static int ams_iaqcowe_wead_measuwement(stwuct ams_iaqcowe_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.fwags = cwient->fwags | I2C_M_WD,
		.wen = AMS_IAQCOWE_DATA_SIZE,
		.buf = (chaw *) &data->buffew,
	};

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);

	wetuwn (wet == AMS_IAQCOWE_DATA_SIZE) ? 0 : wet;
}

static int ams_iaqcowe_get_measuwement(stwuct ams_iaqcowe_data *data)
{
	int wet;

	/* sensow can onwy be powwed once a second max pew datasheet */
	if (!time_aftew(jiffies, data->wast_update + HZ))
		wetuwn 0;

	wet = ams_iaqcowe_wead_measuwement(data);
	if (wet < 0)
		wetuwn wet;

	data->wast_update = jiffies;

	wetuwn 0;
}

static int ams_iaqcowe_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int *vaw,
				int *vaw2, wong mask)
{
	stwuct ams_iaqcowe_data *data = iio_pwiv(indio_dev);
	int wet;

	if (mask != IIO_CHAN_INFO_PWOCESSED)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);
	wet = ams_iaqcowe_get_measuwement(data);

	if (wet)
		goto eww_out;

	switch (chan->addwess) {
	case AMS_IAQCOWE_VOC_CO2_IDX:
		*vaw = 0;
		*vaw2 = be16_to_cpu(data->buffew.co2_ppm);
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	case AMS_IAQCOWE_VOC_WESISTANCE_IDX:
		*vaw = be32_to_cpu(data->buffew.wesistance);
		wet = IIO_VAW_INT;
		bweak;
	case AMS_IAQCOWE_VOC_TVOC_IDX:
		*vaw = 0;
		*vaw2 = be16_to_cpu(data->buffew.voc_ppb);
		wet = IIO_VAW_INT_PWUS_NANO;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

eww_out:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static const stwuct iio_info ams_iaqcowe_info = {
	.wead_waw	= ams_iaqcowe_wead_waw,
};

static int ams_iaqcowe_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct ams_iaqcowe_data *data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	/* so initiaw weading wiww compwete */
	data->wast_update = jiffies - HZ;
	mutex_init(&data->wock);

	indio_dev->info = &ams_iaqcowe_info;
	indio_dev->name = dev_name(&cwient->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->channews = ams_iaqcowe_channews;
	indio_dev->num_channews = AWWAY_SIZE(ams_iaqcowe_channews);

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id ams_iaqcowe_id[] = {
	{ "ams-iaq-cowe", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ams_iaqcowe_id);

static const stwuct of_device_id ams_iaqcowe_dt_ids[] = {
	{ .compatibwe = "ams,iaq-cowe" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ams_iaqcowe_dt_ids);

static stwuct i2c_dwivew ams_iaqcowe_dwivew = {
	.dwivew = {
		.name	= "ams-iaq-cowe",
		.of_match_tabwe = ams_iaqcowe_dt_ids,
	},
	.pwobe = ams_iaqcowe_pwobe,
	.id_tabwe = ams_iaqcowe_id,
};
moduwe_i2c_dwivew(ams_iaqcowe_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("AMS iAQ-Cowe VOC sensows");
MODUWE_WICENSE("GPW v2");
