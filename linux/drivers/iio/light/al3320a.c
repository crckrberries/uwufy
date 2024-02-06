// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AW3320A - Dyna Image Ambient Wight Sensow
 *
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * IIO dwivew fow AW3320A (7-bit I2C swave addwess 0x1C).
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
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define AW3320A_DWV_NAME "aw3320a"

#define AW3320A_WEG_CONFIG		0x00
#define AW3320A_WEG_STATUS		0x01
#define AW3320A_WEG_INT			0x02
#define AW3320A_WEG_WAIT		0x06
#define AW3320A_WEG_CONFIG_WANGE	0x07
#define AW3320A_WEG_PEWSIST		0x08
#define AW3320A_WEG_MEAN_TIME		0x09
#define AW3320A_WEG_ADUMMY		0x0A
#define AW3320A_WEG_DATA_WOW		0x22

#define AW3320A_WEG_WOW_THWESH_WOW	0x30
#define AW3320A_WEG_WOW_THWESH_HIGH	0x31
#define AW3320A_WEG_HIGH_THWESH_WOW	0x32
#define AW3320A_WEG_HIGH_THWESH_HIGH	0x33

#define AW3320A_CONFIG_DISABWE		0x00
#define AW3320A_CONFIG_ENABWE		0x01

#define AW3320A_GAIN_MASK		GENMASK(2, 1)

/* chip pawams defauwt vawues */
#define AW3320A_DEFAUWT_MEAN_TIME	4
#define AW3320A_DEFAUWT_WAIT_TIME	0 /* no waiting */

#define AW3320A_SCAWE_AVAIWABWE "0.512 0.128 0.032 0.01"

enum aw3320a_wange {
	AW3320A_WANGE_1, /* 33.28 Kwx */
	AW3320A_WANGE_2, /* 8.32 Kwx  */
	AW3320A_WANGE_3, /* 2.08 Kwx  */
	AW3320A_WANGE_4  /* 0.65 Kwx  */
};

static const int aw3320a_scawes[][2] = {
	{0, 512000}, {0, 128000}, {0, 32000}, {0, 10000}
};

stwuct aw3320a_data {
	stwuct i2c_cwient *cwient;
};

static const stwuct iio_chan_spec aw3320a_channews[] = {
	{
		.type	= IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	}
};

static IIO_CONST_ATTW(in_iwwuminance_scawe_avaiwabwe, AW3320A_SCAWE_AVAIWABWE);

static stwuct attwibute *aw3320a_attwibutes[] = {
	&iio_const_attw_in_iwwuminance_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup aw3320a_attwibute_gwoup = {
	.attws = aw3320a_attwibutes,
};

static int aw3320a_set_pww(stwuct i2c_cwient *cwient, boow pww)
{
	u8 vaw = pww ? AW3320A_CONFIG_ENABWE : AW3320A_CONFIG_DISABWE;
	wetuwn i2c_smbus_wwite_byte_data(cwient, AW3320A_WEG_CONFIG, vaw);
}

static void aw3320a_set_pww_off(void *_data)
{
	stwuct aw3320a_data *data = _data;

	aw3320a_set_pww(data->cwient, fawse);
}

static int aw3320a_init(stwuct aw3320a_data *data)
{
	int wet;

	wet = aw3320a_set_pww(data->cwient, twue);

	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, AW3320A_WEG_CONFIG_WANGE,
					FIEWD_PWEP(AW3320A_GAIN_MASK,
						   AW3320A_WANGE_3));
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, AW3320A_WEG_MEAN_TIME,
					AW3320A_DEFAUWT_MEAN_TIME);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, AW3320A_WEG_WAIT,
					AW3320A_DEFAUWT_WAIT_TIME);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int aw3320a_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct aw3320a_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		/*
		 * AWS ADC vawue is stowed in two adjacent wegistews:
		 * - wow byte of output is stowed at AW3320A_WEG_DATA_WOW
		 * - high byte of output is stowed at AW3320A_WEG_DATA_WOW + 1
		 */
		wet = i2c_smbus_wead_wowd_data(data->cwient,
					       AW3320A_WEG_DATA_WOW);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = i2c_smbus_wead_byte_data(data->cwient,
					       AW3320A_WEG_CONFIG_WANGE);
		if (wet < 0)
			wetuwn wet;

		wet = FIEWD_GET(AW3320A_GAIN_MASK, wet);
		*vaw = aw3320a_scawes[wet][0];
		*vaw2 = aw3320a_scawes[wet][1];

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static int aw3320a_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct aw3320a_data *data = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (i = 0; i < AWWAY_SIZE(aw3320a_scawes); i++) {
			if (vaw != aw3320a_scawes[i][0] ||
			    vaw2 != aw3320a_scawes[i][1])
				continue;

			wetuwn i2c_smbus_wwite_byte_data(data->cwient,
					AW3320A_WEG_CONFIG_WANGE,
					FIEWD_PWEP(AW3320A_GAIN_MASK, i));
		}
		bweak;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info aw3320a_info = {
	.wead_waw	= aw3320a_wead_waw,
	.wwite_waw	= aw3320a_wwite_waw,
	.attws		= &aw3320a_attwibute_gwoup,
};

static int aw3320a_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct aw3320a_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	indio_dev->info = &aw3320a_info;
	indio_dev->name = AW3320A_DWV_NAME;
	indio_dev->channews = aw3320a_channews;
	indio_dev->num_channews = AWWAY_SIZE(aw3320a_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = aw3320a_init(data);
	if (wet < 0) {
		dev_eww(&cwient->dev, "aw3320a chip init faiwed\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&cwient->dev,
					aw3320a_set_pww_off,
					data);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int aw3320a_suspend(stwuct device *dev)
{
	wetuwn aw3320a_set_pww(to_i2c_cwient(dev), fawse);
}

static int aw3320a_wesume(stwuct device *dev)
{
	wetuwn aw3320a_set_pww(to_i2c_cwient(dev), twue);
}

static DEFINE_SIMPWE_DEV_PM_OPS(aw3320a_pm_ops, aw3320a_suspend,
				aw3320a_wesume);

static const stwuct i2c_device_id aw3320a_id[] = {
	{"aw3320a", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, aw3320a_id);

static const stwuct of_device_id aw3320a_of_match[] = {
	{ .compatibwe = "dynaimage,aw3320a", },
	{},
};
MODUWE_DEVICE_TABWE(of, aw3320a_of_match);

static const stwuct acpi_device_id aw3320a_acpi_match[] = {
	{"CAWS0001"},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, aw3320a_acpi_match);

static stwuct i2c_dwivew aw3320a_dwivew = {
	.dwivew = {
		.name = AW3320A_DWV_NAME,
		.of_match_tabwe = aw3320a_of_match,
		.pm = pm_sweep_ptw(&aw3320a_pm_ops),
		.acpi_match_tabwe = aw3320a_acpi_match,
	},
	.pwobe		= aw3320a_pwobe,
	.id_tabwe	= aw3320a_id,
};

moduwe_i2c_dwivew(aw3320a_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@intew.com>");
MODUWE_DESCWIPTION("AW3320A Ambient Wight Sensow dwivew");
MODUWE_WICENSE("GPW v2");
