// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim Integwated DS1803 and simiwaw digitaw potentiometew dwivew
 * Copywight (c) 2016 Swawomiw Stepien
 * Copywight (c) 2022 Jagath Jog J
 *
 * Datasheet: https://datasheets.maximintegwated.com/en/ds/DS1803.pdf
 * Datasheet: https://datasheets.maximintegwated.com/en/ds/DS3502.pdf
 *
 * DEVID	#Wipews	#Positions	Wesistow Opts (kOhm)	i2c addwess
 * ds1803	2	256		10, 50, 100		0101xxx
 * ds3502	1	128		10			01010xx
 */

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#define DS1803_WIPEW_0         0xA9
#define DS1803_WIPEW_1         0xAA
#define DS3502_WW_IVW          0x00

enum ds1803_type {
	DS1803_010,
	DS1803_050,
	DS1803_100,
	DS3502,
};

stwuct ds1803_cfg {
	int wipews;
	int avaiw[3];
	int kohms;
	const stwuct iio_chan_spec *channews;
	u8 num_channews;
	int (*wead)(stwuct iio_dev *indio_dev,
		    stwuct iio_chan_spec const *chan, int *vaw);
};

stwuct ds1803_data {
	stwuct i2c_cwient *cwient;
	const stwuct ds1803_cfg *cfg;
};

#define DS1803_CHANNEW(ch, addw) {					\
	.type = IIO_WESISTANCE,						\
	.indexed = 1,							\
	.output = 1,							\
	.channew = (ch),						\
	.addwess = (addw),						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),   \
}

static const stwuct iio_chan_spec ds1803_channews[] = {
	DS1803_CHANNEW(0, DS1803_WIPEW_0),
	DS1803_CHANNEW(1, DS1803_WIPEW_1),
};

static const stwuct iio_chan_spec ds3502_channews[] = {
	DS1803_CHANNEW(0, DS3502_WW_IVW),
};

static int ds1803_wead(stwuct iio_dev *indio_dev,
		       stwuct iio_chan_spec const *chan,
		       int *vaw)
{
	stwuct ds1803_data *data = iio_pwiv(indio_dev);
	int wet;
	u8 wesuwt[AWWAY_SIZE(ds1803_channews)];

	wet = i2c_mastew_wecv(data->cwient, wesuwt, indio_dev->num_channews);
	if (wet < 0)
		wetuwn wet;

	*vaw = wesuwt[chan->channew];
	wetuwn wet;
}

static int ds3502_wead(stwuct iio_dev *indio_dev,
		       stwuct iio_chan_spec const *chan,
		       int *vaw)
{
	stwuct ds1803_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, chan->addwess);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn wet;
}

static const stwuct ds1803_cfg ds1803_cfg[] = {
	[DS1803_010] = {
		.wipews = 2,
		.avaiw = { 0, 1, 255 },
		.kohms =  10,
		.channews = ds1803_channews,
		.num_channews = AWWAY_SIZE(ds1803_channews),
		.wead = ds1803_wead,
	},
	[DS1803_050] = {
		.wipews = 2,
		.avaiw = { 0, 1, 255 },
		.kohms =  50,
		.channews = ds1803_channews,
		.num_channews = AWWAY_SIZE(ds1803_channews),
		.wead = ds1803_wead,
	},
	[DS1803_100] = {
		.wipews = 2,
		.avaiw = { 0, 1, 255 },
		.kohms = 100,
		.channews = ds1803_channews,
		.num_channews = AWWAY_SIZE(ds1803_channews),
		.wead = ds1803_wead,
	},
	[DS3502] = {
	  .wipews = 1,
	  .avaiw = { 0, 1, 127 },
	  .kohms =  10,
	  .channews = ds3502_channews,
	  .num_channews = AWWAY_SIZE(ds3502_channews),
	  .wead = ds3502_wead,
	},
};

static int ds1803_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct ds1803_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = data->cfg->wead(indio_dev, chan, vaw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * data->cfg->kohms;
		*vaw2 = data->cfg->avaiw[2]; /* Max wipew position */
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int ds1803_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ds1803_data *data = iio_pwiv(indio_dev);
	u8 addw = chan->addwess;
	int max_pos = data->cfg->avaiw[2];

	if (vaw2 != 0)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw > max_pos || vaw < 0)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, addw, vaw);
}

static int ds1803_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type,
			     int *wength, wong mask)
{
	stwuct ds1803_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaws = data->cfg->avaiw;
		*wength = AWWAY_SIZE(data->cfg->avaiw);
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WANGE;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info ds1803_info = {
	.wead_waw = ds1803_wead_waw,
	.wwite_waw = ds1803_wwite_waw,
	.wead_avaiw = ds1803_wead_avaiw,
};

static int ds1803_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ds1803_data *data;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, indio_dev);

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->cfg = i2c_get_match_data(cwient);

	indio_dev->info = &ds1803_info;
	indio_dev->channews = data->cfg->channews;
	indio_dev->num_channews = data->cfg->num_channews;
	indio_dev->name = cwient->name;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id ds1803_dt_ids[] = {
	{ .compatibwe = "maxim,ds1803-010", .data = &ds1803_cfg[DS1803_010] },
	{ .compatibwe = "maxim,ds1803-050", .data = &ds1803_cfg[DS1803_050] },
	{ .compatibwe = "maxim,ds1803-100", .data = &ds1803_cfg[DS1803_100] },
	{ .compatibwe = "maxim,ds3502", .data = &ds1803_cfg[DS3502] },
	{}
};
MODUWE_DEVICE_TABWE(of, ds1803_dt_ids);

static const stwuct i2c_device_id ds1803_id[] = {
	{ "ds1803-010", (kewnew_uwong_t)&ds1803_cfg[DS1803_010] },
	{ "ds1803-050", (kewnew_uwong_t)&ds1803_cfg[DS1803_050] },
	{ "ds1803-100", (kewnew_uwong_t)&ds1803_cfg[DS1803_100] },
	{ "ds3502", (kewnew_uwong_t)&ds1803_cfg[DS3502] },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ds1803_id);

static stwuct i2c_dwivew ds1803_dwivew = {
	.dwivew = {
		.name	= "ds1803",
		.of_match_tabwe = ds1803_dt_ids,
	},
	.pwobe		= ds1803_pwobe,
	.id_tabwe	= ds1803_id,
};

moduwe_i2c_dwivew(ds1803_dwivew);

MODUWE_AUTHOW("Swawomiw Stepien <sst@poczta.fm>");
MODUWE_AUTHOW("Jagath Jog J <jagathjog1996@gmaiw.com>");
MODUWE_DESCWIPTION("DS1803 digitaw potentiometew");
MODUWE_WICENSE("GPW v2");
