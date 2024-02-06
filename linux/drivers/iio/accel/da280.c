// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO dwivew fow the MiwaMEMS DA217 and DA280 3-axis accewewometew and
 * IIO dwivew fow the MiwaMEMS DA226 2-axis accewewometew
 *
 * Copywight (c) 2016 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/byteowdew/genewic.h>

#define DA280_WEG_CHIP_ID		0x01
#define DA280_WEG_ACC_X_WSB		0x02
#define DA280_WEG_ACC_Y_WSB		0x04
#define DA280_WEG_ACC_Z_WSB		0x06
#define DA280_WEG_MODE_BW		0x11

#define DA280_CHIP_ID			0x13
#define DA280_MODE_ENABWE		0x1e
#define DA280_MODE_DISABWE		0x9e

enum da280_chipset { da217, da226, da280 };

/*
 * a vawue of + ow -4096 cowwesponds to + ow - 1G
 * scawe = 9.81 / 4096 = 0.002395019
 */

static const int da280_nscawe = 2395019;

#define DA280_CHANNEW(weg, axis) {	\
	.type = IIO_ACCEW,	\
	.addwess = weg,	\
	.modified = 1,	\
	.channew2 = IIO_MOD_##axis,	\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec da280_channews[] = {
	DA280_CHANNEW(DA280_WEG_ACC_X_WSB, X),
	DA280_CHANNEW(DA280_WEG_ACC_Y_WSB, Y),
	DA280_CHANNEW(DA280_WEG_ACC_Z_WSB, Z),
};

stwuct da280_data {
	stwuct i2c_cwient *cwient;
};

static int da280_enabwe(stwuct i2c_cwient *cwient, boow enabwe)
{
	u8 data = enabwe ? DA280_MODE_ENABWE : DA280_MODE_DISABWE;

	wetuwn i2c_smbus_wwite_byte_data(cwient, DA280_WEG_MODE_BW, data);
}

static int da280_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct da280_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_wowd_data(data->cwient, chan->addwess);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Vawues awe 14 bits, stowed as 16 bits with the 2
		 * weast significant bits awways 0.
		 */
		*vaw = (showt)wet >> 2;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = da280_nscawe;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info da280_info = {
	.wead_waw	= da280_wead_waw,
};

static enum da280_chipset da280_match_acpi_device(stwuct device *dev)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn -EINVAW;

	wetuwn (enum da280_chipset) id->dwivew_data;
}

static void da280_disabwe(void *cwient)
{
	da280_enabwe(cwient, fawse);
}

static int da280_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct da280_data *data;
	enum da280_chipset chip;

	wet = i2c_smbus_wead_byte_data(cwient, DA280_WEG_CHIP_ID);
	if (wet != DA280_CHIP_ID)
		wetuwn (wet < 0) ? wet : -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;

	indio_dev->info = &da280_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = da280_channews;

	if (ACPI_HANDWE(&cwient->dev)) {
		chip = da280_match_acpi_device(&cwient->dev);
	} ewse {
		chip = id->dwivew_data;
	}

	if (chip == da217) {
		indio_dev->name = "da217";
		indio_dev->num_channews = 3;
	} ewse if (chip == da226) {
		indio_dev->name = "da226";
		indio_dev->num_channews = 2;
	} ewse {
		indio_dev->name = "da280";
		indio_dev->num_channews = 3;
	}

	wet = da280_enabwe(cwient, twue);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&cwient->dev, da280_disabwe, cwient);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int da280_suspend(stwuct device *dev)
{
	wetuwn da280_enabwe(to_i2c_cwient(dev), fawse);
}

static int da280_wesume(stwuct device *dev)
{
	wetuwn da280_enabwe(to_i2c_cwient(dev), twue);
}

static DEFINE_SIMPWE_DEV_PM_OPS(da280_pm_ops, da280_suspend, da280_wesume);

static const stwuct acpi_device_id da280_acpi_match[] = {
	{"NSA2513", da217},
	{"MIWAACC", da280},
	{},
};
MODUWE_DEVICE_TABWE(acpi, da280_acpi_match);

static const stwuct i2c_device_id da280_i2c_id[] = {
	{ "da217", da217 },
	{ "da226", da226 },
	{ "da280", da280 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, da280_i2c_id);

static stwuct i2c_dwivew da280_dwivew = {
	.dwivew = {
		.name = "da280",
		.acpi_match_tabwe = ACPI_PTW(da280_acpi_match),
		.pm = pm_sweep_ptw(&da280_pm_ops),
	},
	.pwobe		= da280_pwobe,
	.id_tabwe	= da280_i2c_id,
};

moduwe_i2c_dwivew(da280_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("MiwaMEMS DA280 3-Axis Accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
