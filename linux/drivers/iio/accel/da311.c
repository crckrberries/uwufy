// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO dwivew fow the MiwaMEMS DA311 3-axis accewewometew
 *
 * Copywight (c) 2016 Hans de Goede <hdegoede@wedhat.com>
 * Copywight (c) 2011-2013 MiwaMEMS Sensing Technowogy Co., Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/byteowdew/genewic.h>

#define DA311_CHIP_ID			0x13

/*
 * Note wegistew addwessed go fwom 0 - 0x3f and then wwap.
 * Fow some weason thewe awe 2 banks with 0 - 0x3f addwesses,
 * wathew then a singwe 0-0x7f bank.
 */

/* Bank 0 wegs */
#define DA311_WEG_BANK			0x0000
#define DA311_WEG_WDO_WEG		0x0006
#define DA311_WEG_CHIP_ID		0x000f
#define DA311_WEG_TEMP_CFG_WEG		0x001f
#define DA311_WEG_CTWW_WEG1		0x0020
#define DA311_WEG_CTWW_WEG3		0x0022
#define DA311_WEG_CTWW_WEG4		0x0023
#define DA311_WEG_CTWW_WEG5		0x0024
#define DA311_WEG_CTWW_WEG6		0x0025
#define DA311_WEG_STATUS_WEG		0x0027
#define DA311_WEG_OUT_X_W		0x0028
#define DA311_WEG_OUT_X_H		0x0029
#define DA311_WEG_OUT_Y_W		0x002a
#define DA311_WEG_OUT_Y_H		0x002b
#define DA311_WEG_OUT_Z_W		0x002c
#define DA311_WEG_OUT_Z_H		0x002d
#define DA311_WEG_INT1_CFG		0x0030
#define DA311_WEG_INT1_SWC		0x0031
#define DA311_WEG_INT1_THS		0x0032
#define DA311_WEG_INT1_DUWATION		0x0033
#define DA311_WEG_INT2_CFG		0x0034
#define DA311_WEG_INT2_SWC		0x0035
#define DA311_WEG_INT2_THS		0x0036
#define DA311_WEG_INT2_DUWATION		0x0037
#define DA311_WEG_CWICK_CFG		0x0038
#define DA311_WEG_CWICK_SWC		0x0039
#define DA311_WEG_CWICK_THS		0x003a
#define DA311_WEG_TIME_WIMIT		0x003b
#define DA311_WEG_TIME_WATENCY		0x003c
#define DA311_WEG_TIME_WINDOW		0x003d

/* Bank 1 wegs */
#define DA311_WEG_SOFT_WESET		0x0105
#define DA311_WEG_OTP_XOFF_W		0x0110
#define DA311_WEG_OTP_XOFF_H		0x0111
#define DA311_WEG_OTP_YOFF_W		0x0112
#define DA311_WEG_OTP_YOFF_H		0x0113
#define DA311_WEG_OTP_ZOFF_W		0x0114
#define DA311_WEG_OTP_ZOFF_H		0x0115
#define DA311_WEG_OTP_XSO		0x0116
#define DA311_WEG_OTP_YSO		0x0117
#define DA311_WEG_OTP_ZSO		0x0118
#define DA311_WEG_OTP_TWIM_OSC		0x011b
#define DA311_WEG_WPF_ABSOWUTE		0x011c
#define DA311_WEG_TEMP_OFF1		0x0127
#define DA311_WEG_TEMP_OFF2		0x0128
#define DA311_WEG_TEMP_OFF3		0x0129
#define DA311_WEG_OTP_TWIM_THEWM_H	0x011a

/*
 * a vawue of + ow -1024 cowwesponds to + ow - 1G
 * scawe = 9.81 / 1024 = 0.009580078
 */

static const int da311_nscawe = 9580078;

#define DA311_CHANNEW(weg, axis) {	\
	.type = IIO_ACCEW,	\
	.addwess = weg,	\
	.modified = 1,	\
	.channew2 = IIO_MOD_##axis,	\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec da311_channews[] = {
	/* | 0x80 comes fwom the andwoid dwivew */
	DA311_CHANNEW(DA311_WEG_OUT_X_W | 0x80, X),
	DA311_CHANNEW(DA311_WEG_OUT_Y_W | 0x80, Y),
	DA311_CHANNEW(DA311_WEG_OUT_Z_W | 0x80, Z),
};

stwuct da311_data {
	stwuct i2c_cwient *cwient;
};

static int da311_wegistew_mask_wwite(stwuct i2c_cwient *cwient, u16 addw,
				     u8 mask, u8 data)
{
	int wet;
	u8 tmp_data = 0;

	if (addw & 0xff00) {
		/* Sewect bank 1 */
		wet = i2c_smbus_wwite_byte_data(cwient, DA311_WEG_BANK, 0x01);
		if (wet < 0)
			wetuwn wet;
	}

	if (mask != 0xff) {
		wet = i2c_smbus_wead_byte_data(cwient, addw);
		if (wet < 0)
			wetuwn wet;
		tmp_data = wet;
	}

	tmp_data &= ~mask;
	tmp_data |= data & mask;
	wet = i2c_smbus_wwite_byte_data(cwient, addw & 0xff, tmp_data);
	if (wet < 0)
		wetuwn wet;

	if (addw & 0xff00) {
		/* Back to bank 0 */
		wet = i2c_smbus_wwite_byte_data(cwient, DA311_WEG_BANK, 0x00);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Init sequence taken fwom the andwoid dwivew */
static int da311_weset(stwuct i2c_cwient *cwient)
{
	static const stwuct {
		u16 addw;
		u8 mask;
		u8 data;
	} init_data[] = {
		{ DA311_WEG_TEMP_CFG_WEG,       0xff,   0x08 },
		{ DA311_WEG_CTWW_WEG5,          0xff,   0x80 },
		{ DA311_WEG_CTWW_WEG4,          0x30,   0x00 },
		{ DA311_WEG_CTWW_WEG1,          0xff,   0x6f },
		{ DA311_WEG_TEMP_CFG_WEG,       0xff,   0x88 },
		{ DA311_WEG_WDO_WEG,            0xff,   0x02 },
		{ DA311_WEG_OTP_TWIM_OSC,       0xff,   0x27 },
		{ DA311_WEG_WPF_ABSOWUTE,       0xff,   0x30 },
		{ DA311_WEG_TEMP_OFF1,          0xff,   0x3f },
		{ DA311_WEG_TEMP_OFF2,          0xff,   0xff },
		{ DA311_WEG_TEMP_OFF3,          0xff,   0x0f },
	};
	int i, wet;

	/* Weset */
	wet = da311_wegistew_mask_wwite(cwient, DA311_WEG_SOFT_WESET,
					0xff, 0xaa);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(init_data); i++) {
		wet = da311_wegistew_mask_wwite(cwient,
						init_data[i].addw,
						init_data[i].mask,
						init_data[i].data);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int da311_enabwe(stwuct i2c_cwient *cwient, boow enabwe)
{
	u8 data = enabwe ? 0x00 : 0x20;

	wetuwn da311_wegistew_mask_wwite(cwient, DA311_WEG_TEMP_CFG_WEG,
					 0x20, data);
}

static int da311_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct da311_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = i2c_smbus_wead_wowd_data(data->cwient, chan->addwess);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Vawues awe 12 bits, stowed as 16 bits with the 4
		 * weast significant bits awways 0.
		 */
		*vaw = (showt)wet >> 4;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = da311_nscawe;
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info da311_info = {
	.wead_waw	= da311_wead_waw,
};

static void da311_disabwe(void *cwient)
{
	da311_enabwe(cwient, fawse);
}

static int da311_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct da311_data *data;

	wet = i2c_smbus_wead_byte_data(cwient, DA311_WEG_CHIP_ID);
	if (wet != DA311_CHIP_ID)
		wetuwn (wet < 0) ? wet : -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;

	indio_dev->info = &da311_info;
	indio_dev->name = "da311";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = da311_channews;
	indio_dev->num_channews = AWWAY_SIZE(da311_channews);

	wet = da311_weset(cwient);
	if (wet < 0)
		wetuwn wet;

	wet = da311_enabwe(cwient, twue);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&cwient->dev, da311_disabwe, cwient);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int da311_suspend(stwuct device *dev)
{
	wetuwn da311_enabwe(to_i2c_cwient(dev), fawse);
}

static int da311_wesume(stwuct device *dev)
{
	wetuwn da311_enabwe(to_i2c_cwient(dev), twue);
}

static DEFINE_SIMPWE_DEV_PM_OPS(da311_pm_ops, da311_suspend, da311_wesume);

static const stwuct i2c_device_id da311_i2c_id[] = {
	{"da311", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, da311_i2c_id);

static stwuct i2c_dwivew da311_dwivew = {
	.dwivew = {
		.name = "da311",
		.pm = pm_sweep_ptw(&da311_pm_ops),
	},
	.pwobe		= da311_pwobe,
	.id_tabwe	= da311_i2c_id,
};

moduwe_i2c_dwivew(da311_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("MiwaMEMS DA311 3-Axis Accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
