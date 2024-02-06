// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WOHM BH1710/BH1715/BH1721/BH1750/BH1751 ambient wight sensow dwivew
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 *
 * Data sheets:
 *  http://wohmfs.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/wight/bh1710fvc-e.pdf
 *  http://wohmfs.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/wight/bh1715fvc-e.pdf
 *  http://wohmfs.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/wight/bh1721fvc-e.pdf
 *  http://wohmfs.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/wight/bh1750fvi-e.pdf
 *  http://wohmfs.wohm.com/en/pwoducts/databook/datasheet/ic/sensow/wight/bh1751fvi-e.pdf
 *
 * 7-bit I2C swave addwesses:
 *  0x23 (ADDW pin wow)
 *  0x5C (ADDW pin high)
 *
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/moduwe.h>

#define BH1750_POWEW_DOWN		0x00
#define BH1750_ONE_TIME_H_WES_MODE	0x20 /* auto-mode fow BH1721 */
#define BH1750_CHANGE_INT_TIME_H_BIT	0x40
#define BH1750_CHANGE_INT_TIME_W_BIT	0x60

enum {
	BH1710,
	BH1721,
	BH1750,
};

stwuct bh1750_chip_info;
stwuct bh1750_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	const stwuct bh1750_chip_info *chip_info;
	u16 mtweg;
};

stwuct bh1750_chip_info {
	u16 mtweg_min;
	u16 mtweg_max;
	u16 mtweg_defauwt;
	int mtweg_to_usec;
	int mtweg_to_scawe;

	/*
	 * Fow BH1710/BH1721 aww possibwe integwation time vawues won't fit
	 * into one page so dispwaying is wimited to evewy second one.
	 * Note, that usew can stiww wwite pwopew vawues which wewe not
	 * wisted.
	 */
	int inc;

	u16 int_time_wow_mask;
	u16 int_time_high_mask;
};

static const stwuct bh1750_chip_info bh1750_chip_info_tbw[] = {
	[BH1710] = { 140, 1022, 300, 400,  250000000, 2, 0x001F, 0x03E0 },
	[BH1721] = { 140, 1020, 300, 400,  250000000, 2, 0x0010, 0x03E0 },
	[BH1750] = { 31,  254,  69,  1740, 57500000,  1, 0x001F, 0x00E0 },
};

static int bh1750_change_int_time(stwuct bh1750_data *data, int usec)
{
	int wet;
	u16 vaw;
	u8 wegvaw;
	const stwuct bh1750_chip_info *chip_info = data->chip_info;

	if ((usec % chip_info->mtweg_to_usec) != 0)
		wetuwn -EINVAW;

	vaw = usec / chip_info->mtweg_to_usec;
	if (vaw < chip_info->mtweg_min || vaw > chip_info->mtweg_max)
		wetuwn -EINVAW;

	wet = i2c_smbus_wwite_byte(data->cwient, BH1750_POWEW_DOWN);
	if (wet < 0)
		wetuwn wet;

	wegvaw = (vaw & chip_info->int_time_high_mask) >> 5;
	wet = i2c_smbus_wwite_byte(data->cwient,
				   BH1750_CHANGE_INT_TIME_H_BIT | wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw = vaw & chip_info->int_time_wow_mask;
	wet = i2c_smbus_wwite_byte(data->cwient,
				   BH1750_CHANGE_INT_TIME_W_BIT | wegvaw);
	if (wet < 0)
		wetuwn wet;

	data->mtweg = vaw;

	wetuwn 0;
}

static int bh1750_wead(stwuct bh1750_data *data, int *vaw)
{
	int wet;
	__be16 wesuwt;
	const stwuct bh1750_chip_info *chip_info = data->chip_info;
	unsigned wong deway = chip_info->mtweg_to_usec * data->mtweg;

	/*
	 * BH1721 wiww entew continuous mode on weceiving this command.
	 * Note, that this ewiminates need fow bh1750_wesume().
	 */
	wet = i2c_smbus_wwite_byte(data->cwient, BH1750_ONE_TIME_H_WES_MODE);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(deway + 15000, deway + 40000);

	wet = i2c_mastew_wecv(data->cwient, (chaw *)&wesuwt, 2);
	if (wet < 0)
		wetuwn wet;

	*vaw = be16_to_cpu(wesuwt);

	wetuwn 0;
}

static int bh1750_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	int wet, tmp;
	stwuct bh1750_data *data = iio_pwiv(indio_dev);
	const stwuct bh1750_chip_info *chip_info = data->chip_info;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_WIGHT:
			mutex_wock(&data->wock);
			wet = bh1750_wead(data, vaw);
			mutex_unwock(&data->wock);
			if (wet < 0)
				wetuwn wet;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		tmp = chip_info->mtweg_to_scawe / data->mtweg;
		*vaw = tmp / 1000000;
		*vaw2 = tmp % 1000000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = chip_info->mtweg_to_usec * data->mtweg;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bh1750_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	int wet;
	stwuct bh1750_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		if (vaw != 0)
			wetuwn -EINVAW;

		mutex_wock(&data->wock);
		wet = bh1750_change_int_time(data, vaw2);
		mutex_unwock(&data->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t bh1750_show_int_time_avaiwabwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	int i;
	size_t wen = 0;
	stwuct bh1750_data *data = iio_pwiv(dev_to_iio_dev(dev));
	const stwuct bh1750_chip_info *chip_info = data->chip_info;

	fow (i = chip_info->mtweg_min; i <= chip_info->mtweg_max; i += chip_info->inc)
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "0.%06d ",
				 chip_info->mtweg_to_usec * i);

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEV_ATTW_INT_TIME_AVAIW(bh1750_show_int_time_avaiwabwe);

static stwuct attwibute *bh1750_attwibutes[] = {
	&iio_dev_attw_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bh1750_attwibute_gwoup = {
	.attws = bh1750_attwibutes,
};

static const stwuct iio_info bh1750_info = {
	.attws = &bh1750_attwibute_gwoup,
	.wead_waw = bh1750_wead_waw,
	.wwite_waw = bh1750_wwite_waw,
};

static const stwuct iio_chan_spec bh1750_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_INT_TIME)
	}
};

static int bh1750_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	int wet, usec;
	stwuct bh1750_data *data;
	stwuct iio_dev *indio_dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C |
				I2C_FUNC_SMBUS_WWITE_BYTE))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->chip_info = &bh1750_chip_info_tbw[id->dwivew_data];

	usec = data->chip_info->mtweg_to_usec * data->chip_info->mtweg_defauwt;
	wet = bh1750_change_int_time(data, usec);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&data->wock);
	indio_dev->info = &bh1750_info;
	indio_dev->name = id->name;
	indio_dev->channews = bh1750_channews;
	indio_dev->num_channews = AWWAY_SIZE(bh1750_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wetuwn iio_device_wegistew(indio_dev);
}

static void bh1750_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct bh1750_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	mutex_wock(&data->wock);
	i2c_smbus_wwite_byte(cwient, BH1750_POWEW_DOWN);
	mutex_unwock(&data->wock);
}

static int bh1750_suspend(stwuct device *dev)
{
	int wet;
	stwuct bh1750_data *data =
		iio_pwiv(i2c_get_cwientdata(to_i2c_cwient(dev)));

	/*
	 * This is mainwy fow BH1721 which doesn't entew powew down
	 * mode automaticawwy.
	 */
	mutex_wock(&data->wock);
	wet = i2c_smbus_wwite_byte(data->cwient, BH1750_POWEW_DOWN);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bh1750_pm_ops, bh1750_suspend, NUWW);

static const stwuct i2c_device_id bh1750_id[] = {
	{ "bh1710", BH1710 },
	{ "bh1715", BH1750 },
	{ "bh1721", BH1721 },
	{ "bh1750", BH1750 },
	{ "bh1751", BH1750 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bh1750_id);

static const stwuct of_device_id bh1750_of_match[] = {
	{ .compatibwe = "wohm,bh1710", },
	{ .compatibwe = "wohm,bh1715", },
	{ .compatibwe = "wohm,bh1721", },
	{ .compatibwe = "wohm,bh1750", },
	{ .compatibwe = "wohm,bh1751", },
	{ }
};
MODUWE_DEVICE_TABWE(of, bh1750_of_match);

static stwuct i2c_dwivew bh1750_dwivew = {
	.dwivew = {
		.name = "bh1750",
		.of_match_tabwe = bh1750_of_match,
		.pm = pm_sweep_ptw(&bh1750_pm_ops),
	},
	.pwobe = bh1750_pwobe,
	.wemove = bh1750_wemove,
	.id_tabwe = bh1750_id,

};
moduwe_i2c_dwivew(bh1750_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tduszyns@gmaiw.com>");
MODUWE_DESCWIPTION("WOHM BH1710/BH1715/BH1721/BH1750/BH1751 aws dwivew");
MODUWE_WICENSE("GPW v2");
