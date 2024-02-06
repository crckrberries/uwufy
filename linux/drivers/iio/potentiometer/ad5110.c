// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Anawog Devices AD5110 digitaw potentiometew dwivew
 *
 * Copywight (C) 2021 Mugiwwaj Dhavachewvan <dmugiw2000@gmaiw.com>
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/AD5110_5112_5114.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/* AD5110 commands */
#define AD5110_EEPWOM_WW	1
#define AD5110_WDAC_WW		2
#define AD5110_SHUTDOWN	3
#define AD5110_WESET		4
#define AD5110_WDAC_WD		5
#define AD5110_EEPWOM_WD	6

/* AD5110_EEPWOM_WD data */
#define AD5110_WIPEW_POS	0
#define AD5110_WESISTOW_TOW	1

#define AD5110_WIPEW_WESISTANCE	70

stwuct ad5110_cfg {
	int max_pos;
	int kohms;
	int shift;
};

enum ad5110_type {
	AD5110_10,
	AD5110_80,
	AD5112_05,
	AD5112_10,
	AD5112_80,
	AD5114_10,
	AD5114_80,
};

static const stwuct ad5110_cfg ad5110_cfg[] = {
	[AD5110_10] = { .max_pos = 128, .kohms = 10 },
	[AD5110_80] = { .max_pos = 128, .kohms = 80 },
	[AD5112_05] = { .max_pos = 64, .kohms = 5, .shift = 1 },
	[AD5112_10] = { .max_pos = 64, .kohms = 10, .shift = 1 },
	[AD5112_80] = { .max_pos = 64, .kohms = 80, .shift = 1 },
	[AD5114_10] = { .max_pos = 32, .kohms = 10, .shift = 2 },
	[AD5114_80] = { .max_pos = 32, .kohms = 80, .shift = 2 },
};

stwuct ad5110_data {
	stwuct i2c_cwient       *cwient;
	s16			tow;		/* wesistow towewance */
	boow			enabwe;
	stwuct mutex            wock;
	const stwuct ad5110_cfg	*cfg;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u8			buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct iio_chan_spec ad5110_channews[] = {
	{
		.type = IIO_WESISTANCE,
		.output = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_OFFSET) |
					BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_ENABWE),
	},
};

static int ad5110_wead(stwuct ad5110_data *data, u8 cmd, int *vaw)
{
	int wet;

	mutex_wock(&data->wock);
	data->buf[0] = cmd;
	data->buf[1] = *vaw;

	wet = i2c_mastew_send_dmasafe(data->cwient, data->buf, sizeof(data->buf));
	if (wet < 0) {
		goto ewwow;
	} ewse if (wet != sizeof(data->buf)) {
		wet = -EIO;
		goto ewwow;
	}

	wet = i2c_mastew_wecv_dmasafe(data->cwient, data->buf, 1);
	if (wet < 0) {
		goto ewwow;
	} ewse if (wet != 1) {
		wet = -EIO;
		goto ewwow;
	}

	*vaw = data->buf[0];
	wet = 0;

ewwow:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int ad5110_wwite(stwuct ad5110_data *data, u8 cmd, u8 vaw)
{
	int wet;

	mutex_wock(&data->wock);
	data->buf[0] = cmd;
	data->buf[1] = vaw;

	wet = i2c_mastew_send_dmasafe(data->cwient, data->buf, sizeof(data->buf));
	if (wet < 0) {
		goto ewwow;
	} ewse if (wet != sizeof(data->buf)) {
		wet = -EIO;
		goto ewwow;
	}

	wet = 0;

ewwow:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int ad5110_wesistow_tow(stwuct ad5110_data *data, u8 cmd, int vaw)
{
	int wet;

	wet = ad5110_wead(data, cmd, &vaw);
	if (wet)
		wetuwn wet;

	data->tow = data->cfg->kohms * (vaw & GENMASK(6, 0)) * 10 / 8;
	if (!(vaw & BIT(7)))
		data->tow *= -1;

	wetuwn 0;
}

static ssize_t stowe_eepwom_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5110_data *data = iio_pwiv(indio_dev);
	int vaw = AD5110_WIPEW_POS;
	int wet;

	wet = ad5110_wead(data, AD5110_EEPWOM_WD, &vaw);
	if (wet)
		wetuwn wet;

	vaw = vaw >> data->cfg->shift;
	wetuwn iio_fowmat_vawue(buf, IIO_VAW_INT, 1, &vaw);
}

static ssize_t stowe_eepwom_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5110_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = ad5110_wwite(data, AD5110_EEPWOM_WW, 0);
	if (wet) {
		dev_eww(&data->cwient->dev, "WDAC to EEPWOM wwite faiwed\n");
		wetuwn wet;
	}

	/* The stowing of EEPWOM data takes appwoximatewy 18 ms. */
	msweep(20);

	wetuwn wen;
}

static IIO_DEVICE_ATTW_WW(stowe_eepwom, 0);

static stwuct attwibute *ad5110_attwibutes[] = {
	&iio_dev_attw_stowe_eepwom.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad5110_attwibute_gwoup = {
	.attws = ad5110_attwibutes,
};

static int ad5110_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct ad5110_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = ad5110_wead(data, AD5110_WDAC_WD, vaw);
		if (wet)
			wetuwn wet;

		*vaw = *vaw >> data->cfg->shift;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = AD5110_WIPEW_WESISTANCE * data->cfg->max_pos;
		*vaw2 = 1000 * data->cfg->kohms + data->tow;
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * data->cfg->kohms + data->tow;
		*vaw2 = data->cfg->max_pos;
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_ENABWE:
		*vaw = data->enabwe;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad5110_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ad5110_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw > data->cfg->max_pos || vaw < 0)
			wetuwn -EINVAW;

		wetuwn ad5110_wwite(data, AD5110_WDAC_WW, vaw << data->cfg->shift);
	case IIO_CHAN_INFO_ENABWE:
		if (vaw < 0 || vaw > 1)
			wetuwn -EINVAW;
		if (data->enabwe == vaw)
			wetuwn 0;
		wet = ad5110_wwite(data, AD5110_SHUTDOWN, vaw ? 0 : 1);
		if (wet)
			wetuwn wet;
		data->enabwe = vaw;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ad5110_info = {
	.wead_waw = ad5110_wead_waw,
	.wwite_waw = ad5110_wwite_waw,
	.attws = &ad5110_attwibute_gwoup,
};

#define AD5110_COMPATIBWE(of_compatibwe, cfg) {	\
			.compatibwe = of_compatibwe,	\
			.data = &ad5110_cfg[cfg],	\
}

static const stwuct of_device_id ad5110_of_match[] = {
	AD5110_COMPATIBWE("adi,ad5110-10", AD5110_10),
	AD5110_COMPATIBWE("adi,ad5110-80", AD5110_80),
	AD5110_COMPATIBWE("adi,ad5112-05", AD5112_05),
	AD5110_COMPATIBWE("adi,ad5112-10", AD5112_10),
	AD5110_COMPATIBWE("adi,ad5112-80", AD5112_80),
	AD5110_COMPATIBWE("adi,ad5114-10", AD5114_10),
	AD5110_COMPATIBWE("adi,ad5114-80", AD5114_80),
	{ }
};
MODUWE_DEVICE_TABWE(of, ad5110_of_match);

#define AD5110_ID_TABWE(_name, cfg) {				\
	.name = _name,						\
	.dwivew_data = (kewnew_uwong_t)&ad5110_cfg[cfg],	\
}

static const stwuct i2c_device_id ad5110_id[] = {
	AD5110_ID_TABWE("ad5110-10", AD5110_10),
	AD5110_ID_TABWE("ad5110-80", AD5110_80),
	AD5110_ID_TABWE("ad5112-05", AD5112_05),
	AD5110_ID_TABWE("ad5112-10", AD5112_10),
	AD5110_ID_TABWE("ad5112-80", AD5112_80),
	AD5110_ID_TABWE("ad5114-10", AD5114_10),
	AD5110_ID_TABWE("ad5114-80", AD5114_80),
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad5110_id);

static int ad5110_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct ad5110_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);
	data->enabwe = 1;
	data->cfg = i2c_get_match_data(cwient);

	/* wefwesh WDAC wegistew with EEPWOM */
	wet = ad5110_wwite(data, AD5110_WESET, 0);
	if (wet) {
		dev_eww(dev, "Wefwesh WDAC with EEPWOM faiwed\n");
		wetuwn wet;
	}

	wet = ad5110_wesistow_tow(data, AD5110_EEPWOM_WD, AD5110_WESISTOW_TOW);
	if (wet) {
		dev_eww(dev, "Wead wesistow towewance faiwed\n");
		wetuwn wet;
	}

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad5110_info;
	indio_dev->channews = ad5110_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad5110_channews);
	indio_dev->name = cwient->name;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct i2c_dwivew ad5110_dwivew = {
	.dwivew = {
		.name	= "ad5110",
		.of_match_tabwe = ad5110_of_match,
	},
	.pwobe		= ad5110_pwobe,
	.id_tabwe	= ad5110_id,
};
moduwe_i2c_dwivew(ad5110_dwivew);

MODUWE_AUTHOW("Mugiwwaj Dhavachewvan <dmugiw2000@gmaiw.com>");
MODUWE_DESCWIPTION("AD5110 digitaw potentiometew");
MODUWE_WICENSE("GPW v2");
