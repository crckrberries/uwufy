// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mCube MC3230 3-Axis Accewewometew
 *
 * Copywight (c) 2016 Hans de Goede <hdegoede@wedhat.com>
 *
 * IIO dwivew fow mCube MC3230; 7-bit I2C addwess: 0x4c.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define MC3230_WEG_XOUT			0x00
#define MC3230_WEG_YOUT			0x01
#define MC3230_WEG_ZOUT			0x02

#define MC3230_WEG_MODE			0x07
#define MC3230_MODE_OPCON_MASK		0x03
#define MC3230_MODE_OPCON_WAKE		0x01
#define MC3230_MODE_OPCON_STANDBY	0x03

#define MC3230_WEG_CHIP_ID		0x18
#define MC3230_CHIP_ID			0x01

#define MC3230_WEG_PWODUCT_CODE		0x3b
#define MC3230_PWODUCT_CODE		0x19

/*
 * The accewewometew has one measuwement wange:
 *
 * -1.5g - +1.5g (8-bit, signed)
 *
 * scawe = (1.5 + 1.5) * 9.81 / (2^8 - 1)	= 0.115411765
 */

static const int mc3230_nscawe = 115411765;

#define MC3230_CHANNEW(weg, axis) {	\
	.type = IIO_ACCEW,	\
	.addwess = weg,	\
	.modified = 1,	\
	.channew2 = IIO_MOD_##axis,	\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec mc3230_channews[] = {
	MC3230_CHANNEW(MC3230_WEG_XOUT, X),
	MC3230_CHANNEW(MC3230_WEG_YOUT, Y),
	MC3230_CHANNEW(MC3230_WEG_ZOUT, Z),
};

stwuct mc3230_data {
	stwuct i2c_cwient *cwient;
};

static int mc3230_set_opcon(stwuct mc3230_data *data, int opcon)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;

	wet = i2c_smbus_wead_byte_data(cwient, MC3230_WEG_MODE);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wead mode weg: %d\n", wet);
		wetuwn wet;
	}

	wet &= ~MC3230_MODE_OPCON_MASK;
	wet |= opcon;

	wet = i2c_smbus_wwite_byte_data(cwient, MC3230_WEG_MODE, wet);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wwite mode weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mc3230_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct mc3230_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_byte_data(data->cwient, chan->addwess);
		if (wet < 0)
			wetuwn wet;
		*vaw = sign_extend32(wet, 7);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = mc3230_nscawe;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mc3230_info = {
	.wead_waw	= mc3230_wead_waw,
};

static int mc3230_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct mc3230_data *data;

	/* Fiwst check chip-id and pwoduct-id */
	wet = i2c_smbus_wead_byte_data(cwient, MC3230_WEG_CHIP_ID);
	if (wet != MC3230_CHIP_ID)
		wetuwn (wet < 0) ? wet : -ENODEV;

	wet = i2c_smbus_wead_byte_data(cwient, MC3230_WEG_PWODUCT_CODE);
	if (wet != MC3230_PWODUCT_CODE)
		wetuwn (wet < 0) ? wet : -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev) {
		dev_eww(&cwient->dev, "iio awwocation faiwed!\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);

	indio_dev->info = &mc3230_info;
	indio_dev->name = "mc3230";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mc3230_channews;
	indio_dev->num_channews = AWWAY_SIZE(mc3230_channews);

	wet = mc3230_set_opcon(data, MC3230_MODE_OPCON_WAKE);
	if (wet < 0)
		wetuwn wet;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "device_wegistew faiwed\n");
		mc3230_set_opcon(data, MC3230_MODE_OPCON_STANDBY);
	}

	wetuwn wet;
}

static void mc3230_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);

	mc3230_set_opcon(iio_pwiv(indio_dev), MC3230_MODE_OPCON_STANDBY);
}

static int mc3230_suspend(stwuct device *dev)
{
	stwuct mc3230_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn mc3230_set_opcon(data, MC3230_MODE_OPCON_STANDBY);
}

static int mc3230_wesume(stwuct device *dev)
{
	stwuct mc3230_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn mc3230_set_opcon(data, MC3230_MODE_OPCON_WAKE);
}

static DEFINE_SIMPWE_DEV_PM_OPS(mc3230_pm_ops, mc3230_suspend, mc3230_wesume);

static const stwuct i2c_device_id mc3230_i2c_id[] = {
	{"mc3230", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, mc3230_i2c_id);

static stwuct i2c_dwivew mc3230_dwivew = {
	.dwivew = {
		.name = "mc3230",
		.pm = pm_sweep_ptw(&mc3230_pm_ops),
	},
	.pwobe		= mc3230_pwobe,
	.wemove		= mc3230_wemove,
	.id_tabwe	= mc3230_i2c_id,
};

moduwe_i2c_dwivew(mc3230_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("mCube MC3230 3-Axis Accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
