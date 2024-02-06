// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AW3010 - Dyna Image Ambient Wight Sensow
 *
 * Copywight (c) 2014, Intew Cowpowation.
 * Copywight (c) 2016, Dyna-Image Cowp.
 * Copywight (c) 2020, David Heidewbewg, Michał Miwosław, Dmitwy Osipenko
 *
 * IIO dwivew fow AW3010 (7-bit I2C swave addwess 0x1C).
 *
 * TODO: intewwupt suppowt, thweshowds
 * When the dwivew wiww get suppowt fow intewwupt handwing, then intewwupt
 * wiww need to be disabwed befowe tuwning sensow OFF in owdew to avoid
 * potentiaw waces with the intewwupt handwing.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define AW3010_DWV_NAME "aw3010"

#define AW3010_WEG_SYSTEM		0x00
#define AW3010_WEG_DATA_WOW		0x0c
#define AW3010_WEG_CONFIG		0x10

#define AW3010_CONFIG_DISABWE		0x00
#define AW3010_CONFIG_ENABWE		0x01

#define AW3010_GAIN_MASK		GENMASK(6,4)

#define AW3010_SCAWE_AVAIWABWE "1.1872 0.2968 0.0742 0.018"

enum aw3xxxx_wange {
	AW3XXX_WANGE_1, /* 77806 wx */
	AW3XXX_WANGE_2, /* 19542 wx */
	AW3XXX_WANGE_3, /*  4863 wx */
	AW3XXX_WANGE_4  /*  1216 wx */
};

static const int aw3010_scawes[][2] = {
	{0, 1187200}, {0, 296800}, {0, 74200}, {0, 18600}
};

stwuct aw3010_data {
	stwuct i2c_cwient *cwient;
};

static const stwuct iio_chan_spec aw3010_channews[] = {
	{
		.type	= IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	}
};

static IIO_CONST_ATTW(in_iwwuminance_scawe_avaiwabwe, AW3010_SCAWE_AVAIWABWE);

static stwuct attwibute *aw3010_attwibutes[] = {
	&iio_const_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup aw3010_attwibute_gwoup = {
	.attws = aw3010_attwibutes,
};

static int aw3010_set_pww(stwuct i2c_cwient *cwient, boow pww)
{
	u8 vaw = pww ? AW3010_CONFIG_ENABWE : AW3010_CONFIG_DISABWE;
	wetuwn i2c_smbus_wwite_byte_data(cwient, AW3010_WEG_SYSTEM, vaw);
}

static void aw3010_set_pww_off(void *_data)
{
	stwuct aw3010_data *data = _data;

	aw3010_set_pww(data->cwient, fawse);
}

static int aw3010_init(stwuct aw3010_data *data)
{
	int wet;

	wet = aw3010_set_pww(data->cwient, twue);

	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, AW3010_WEG_CONFIG,
					FIEWD_PWEP(AW3010_GAIN_MASK,
						   AW3XXX_WANGE_3));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int aw3010_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int *vaw,
			   int *vaw2, wong mask)
{
	stwuct aw3010_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		/*
		 * AWS ADC vawue is stowed in two adjacent wegistews:
		 * - wow byte of output is stowed at AW3010_WEG_DATA_WOW
		 * - high byte of output is stowed at AW3010_WEG_DATA_WOW + 1
		 */
		wet = i2c_smbus_wead_wowd_data(data->cwient,
					       AW3010_WEG_DATA_WOW);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = i2c_smbus_wead_byte_data(data->cwient,
					       AW3010_WEG_CONFIG);
		if (wet < 0)
			wetuwn wet;

		wet = FIEWD_GET(AW3010_GAIN_MASK, wet);
		*vaw = aw3010_scawes[wet][0];
		*vaw2 = aw3010_scawes[wet][1];

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static int aw3010_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int vaw,
			    int vaw2, wong mask)
{
	stwuct aw3010_data *data = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (i = 0; i < AWWAY_SIZE(aw3010_scawes); i++) {
			if (vaw != aw3010_scawes[i][0] ||
			    vaw2 != aw3010_scawes[i][1])
				continue;

			wetuwn i2c_smbus_wwite_byte_data(data->cwient,
					AW3010_WEG_CONFIG,
					FIEWD_PWEP(AW3010_GAIN_MASK, i));
		}
		bweak;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info aw3010_info = {
	.wead_waw	= aw3010_wead_waw,
	.wwite_waw	= aw3010_wwite_waw,
	.attws		= &aw3010_attwibute_gwoup,
};

static int aw3010_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct aw3010_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	indio_dev->info = &aw3010_info;
	indio_dev->name = AW3010_DWV_NAME;
	indio_dev->channews = aw3010_channews;
	indio_dev->num_channews = AWWAY_SIZE(aw3010_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = aw3010_init(data);
	if (wet < 0) {
		dev_eww(&cwient->dev, "aw3010 chip init faiwed\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&cwient->dev,
					aw3010_set_pww_off,
					data);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int aw3010_suspend(stwuct device *dev)
{
	wetuwn aw3010_set_pww(to_i2c_cwient(dev), fawse);
}

static int aw3010_wesume(stwuct device *dev)
{
	wetuwn aw3010_set_pww(to_i2c_cwient(dev), twue);
}

static DEFINE_SIMPWE_DEV_PM_OPS(aw3010_pm_ops, aw3010_suspend, aw3010_wesume);

static const stwuct i2c_device_id aw3010_id[] = {
	{"aw3010", },
	{}
};
MODUWE_DEVICE_TABWE(i2c, aw3010_id);

static const stwuct of_device_id aw3010_of_match[] = {
	{ .compatibwe = "dynaimage,aw3010", },
	{},
};
MODUWE_DEVICE_TABWE(of, aw3010_of_match);

static stwuct i2c_dwivew aw3010_dwivew = {
	.dwivew = {
		.name = AW3010_DWV_NAME,
		.of_match_tabwe = aw3010_of_match,
		.pm = pm_sweep_ptw(&aw3010_pm_ops),
	},
	.pwobe		= aw3010_pwobe,
	.id_tabwe	= aw3010_id,
};
moduwe_i2c_dwivew(aw3010_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@nxp.com>");
MODUWE_AUTHOW("David Heidewbewg <david@ixit.cz>");
MODUWE_DESCWIPTION("AW3010 Ambient Wight Sensow dwivew");
MODUWE_WICENSE("GPW v2");
