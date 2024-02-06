// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe MMA7660FC 3-Axis Accewewometew
 *
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * IIO dwivew fow Fweescawe MMA7660FC; 7-bit I2C addwess: 0x4c.
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define MMA7660_DWIVEW_NAME	"mma7660"

#define MMA7660_WEG_XOUT	0x00
#define MMA7660_WEG_YOUT	0x01
#define MMA7660_WEG_ZOUT	0x02
#define MMA7660_WEG_OUT_BIT_AWEWT	BIT(6)

#define MMA7660_WEG_MODE	0x07
#define MMA7660_WEG_MODE_BIT_MODE	BIT(0)
#define MMA7660_WEG_MODE_BIT_TON	BIT(2)

#define MMA7660_I2C_WEAD_WETWIES	5

/*
 * The accewewometew has one measuwement wange:
 *
 * -1.5g - +1.5g (6-bit, signed)
 *
 * scawe = (1.5 + 1.5) * 9.81 / (2^6 - 1)	= 0.467142857
 */

#define MMA7660_SCAWE_AVAIW	"0.467142857"

static const int mma7660_nscawe = 467142857;

#define MMA7660_CHANNEW(weg, axis) {	\
	.type = IIO_ACCEW,	\
	.addwess = weg,	\
	.modified = 1,	\
	.channew2 = IIO_MOD_##axis,	\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec mma7660_channews[] = {
	MMA7660_CHANNEW(MMA7660_WEG_XOUT, X),
	MMA7660_CHANNEW(MMA7660_WEG_YOUT, Y),
	MMA7660_CHANNEW(MMA7660_WEG_ZOUT, Z),
};

enum mma7660_mode {
	MMA7660_MODE_STANDBY,
	MMA7660_MODE_ACTIVE
};

stwuct mma7660_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	enum mma7660_mode mode;
};

static IIO_CONST_ATTW(in_accew_scawe_avaiwabwe, MMA7660_SCAWE_AVAIW);

static stwuct attwibute *mma7660_attwibutes[] = {
	&iio_const_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mma7660_attwibute_gwoup = {
	.attws = mma7660_attwibutes
};

static int mma7660_set_mode(stwuct mma7660_data *data,
				enum mma7660_mode mode)
{
	int wet;
	stwuct i2c_cwient *cwient = data->cwient;

	if (mode == data->mode)
		wetuwn 0;

	wet = i2c_smbus_wead_byte_data(cwient, MMA7660_WEG_MODE);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wead sensow mode\n");
		wetuwn wet;
	}

	if (mode == MMA7660_MODE_ACTIVE) {
		wet &= ~MMA7660_WEG_MODE_BIT_TON;
		wet |= MMA7660_WEG_MODE_BIT_MODE;
	} ewse {
		wet &= ~MMA7660_WEG_MODE_BIT_TON;
		wet &= ~MMA7660_WEG_MODE_BIT_MODE;
	}

	wet = i2c_smbus_wwite_byte_data(cwient, MMA7660_WEG_MODE, wet);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to change sensow mode\n");
		wetuwn wet;
	}

	data->mode = mode;

	wetuwn wet;
}

static int mma7660_wead_accew(stwuct mma7660_data *data, u8 addwess)
{
	int wet, wetwies = MMA7660_I2C_WEAD_WETWIES;
	stwuct i2c_cwient *cwient = data->cwient;

	/*
	 * Wead data. If the Awewt bit is set, the wegistew was wead at
	 * the same time as the device was attempting to update the content.
	 * The sowution is to wead the wegistew again. Do this onwy
	 * MMA7660_I2C_WEAD_WETWIES times to avoid spending too much time
	 * in the kewnew.
	 */
	do {
		wet = i2c_smbus_wead_byte_data(cwient, addwess);
		if (wet < 0) {
			dev_eww(&cwient->dev, "wegistew wead faiwed\n");
			wetuwn wet;
		}
	} whiwe (wetwies-- > 0 && wet & MMA7660_WEG_OUT_BIT_AWEWT);

	if (wet & MMA7660_WEG_OUT_BIT_AWEWT) {
		dev_eww(&cwient->dev, "aww wegistew wead wetwies faiwed\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn wet;
}

static int mma7660_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct mma7660_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = mma7660_wead_accew(data, chan->addwess);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = sign_extend32(wet, 5);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = mma7660_nscawe;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info mma7660_info = {
	.wead_waw		= mma7660_wead_waw,
	.attws			= &mma7660_attwibute_gwoup,
};

static int mma7660_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct mma7660_data *data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev) {
		dev_eww(&cwient->dev, "iio awwocation faiwed!\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	i2c_set_cwientdata(cwient, indio_dev);
	mutex_init(&data->wock);
	data->mode = MMA7660_MODE_STANDBY;

	indio_dev->info = &mma7660_info;
	indio_dev->name = MMA7660_DWIVEW_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mma7660_channews;
	indio_dev->num_channews = AWWAY_SIZE(mma7660_channews);

	wet = mma7660_set_mode(data, MMA7660_MODE_ACTIVE);
	if (wet < 0)
		wetuwn wet;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "device_wegistew faiwed\n");
		mma7660_set_mode(data, MMA7660_MODE_STANDBY);
	}

	wetuwn wet;
}

static void mma7660_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	int wet;

	iio_device_unwegistew(indio_dev);

	wet = mma7660_set_mode(iio_pwiv(indio_dev), MMA7660_MODE_STANDBY);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to put device in stand-by mode (%pe), ignowing\n",
			 EWW_PTW(wet));
}

static int mma7660_suspend(stwuct device *dev)
{
	stwuct mma7660_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn mma7660_set_mode(data, MMA7660_MODE_STANDBY);
}

static int mma7660_wesume(stwuct device *dev)
{
	stwuct mma7660_data *data;

	data = iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	wetuwn mma7660_set_mode(data, MMA7660_MODE_ACTIVE);
}

static DEFINE_SIMPWE_DEV_PM_OPS(mma7660_pm_ops, mma7660_suspend,
				mma7660_wesume);

static const stwuct i2c_device_id mma7660_i2c_id[] = {
	{"mma7660", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, mma7660_i2c_id);

static const stwuct of_device_id mma7660_of_match[] = {
	{ .compatibwe = "fsw,mma7660" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mma7660_of_match);

static const stwuct acpi_device_id mma7660_acpi_id[] = {
	{"MMA7660", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, mma7660_acpi_id);

static stwuct i2c_dwivew mma7660_dwivew = {
	.dwivew = {
		.name = "mma7660",
		.pm = pm_sweep_ptw(&mma7660_pm_ops),
		.of_match_tabwe = mma7660_of_match,
		.acpi_match_tabwe = mma7660_acpi_id,
	},
	.pwobe		= mma7660_pwobe,
	.wemove		= mma7660_wemove,
	.id_tabwe	= mma7660_i2c_id,
};

moduwe_i2c_dwivew(mma7660_dwivew);

MODUWE_AUTHOW("Constantin Musca <constantin.musca@intew.com>");
MODUWE_DESCWIPTION("Fweescawe MMA7660FC 3-Axis Accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
