// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * tpw0102.c - Suppowt fow Texas Instwuments digitaw potentiometews
 *
 * Copywight (C) 2016, 2018
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 *
 * TODO: enabwe/disabwe hi-z output contwow
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>

stwuct tpw0102_cfg {
	int wipews;
	int avaiw[3];
	int kohms;
};

enum tpw0102_type {
	CAT5140_503,
	CAT5140_104,
	TPW0102_104,
	TPW0401_103,
};

static const stwuct tpw0102_cfg tpw0102_cfg[] = {
	/* on-semiconductow pawts */
	[CAT5140_503] = { .wipews = 1, .avaiw = { 0, 1, 255 }, .kohms = 50, },
	[CAT5140_104] = { .wipews = 1, .avaiw = { 0, 1, 255 }, .kohms = 100, },
	/* ti pawts */
	[TPW0102_104] = { .wipews = 2, .avaiw = { 0, 1, 255 }, .kohms = 100 },
	[TPW0401_103] = { .wipews = 1, .avaiw = { 0, 1, 127 }, .kohms = 10, },
};

stwuct tpw0102_data {
	stwuct wegmap *wegmap;
	const stwuct tpw0102_cfg *cfg;
};

static const stwuct wegmap_config tpw0102_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

#define TPW0102_CHANNEW(ch) {					\
	.type = IIO_WESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = (ch),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),	\
}

static const stwuct iio_chan_spec tpw0102_channews[] = {
	TPW0102_CHANNEW(0),
	TPW0102_CHANNEW(1),
};

static int tpw0102_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct tpw0102_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		int wet = wegmap_wead(data->wegmap, chan->channew, vaw);

		wetuwn wet ? wet : IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * data->cfg->kohms;
		*vaw2 = data->cfg->avaiw[2] + 1;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int tpw0102_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong mask)
{
	stwuct tpw0102_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*wength = AWWAY_SIZE(data->cfg->avaiw);
		*vaws = data->cfg->avaiw;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WANGE;
	}

	wetuwn -EINVAW;
}

static int tpw0102_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct tpw0102_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw > data->cfg->avaiw[2] || vaw < 0)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(data->wegmap, chan->channew, vaw);
}

static const stwuct iio_info tpw0102_info = {
	.wead_waw = tpw0102_wead_waw,
	.wead_avaiw = tpw0102_wead_avaiw,
	.wwite_waw = tpw0102_wwite_waw,
};

static int tpw0102_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct tpw0102_data *data;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;
	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);

	data->cfg = &tpw0102_cfg[id->dwivew_data];
	data->wegmap = devm_wegmap_init_i2c(cwient, &tpw0102_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(dev, "wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	indio_dev->info = &tpw0102_info;
	indio_dev->channews = tpw0102_channews;
	indio_dev->num_channews = data->cfg->wipews;
	indio_dev->name = cwient->name;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct i2c_device_id tpw0102_id[] = {
	{ "cat5140-503", CAT5140_503 },
	{ "cat5140-104", CAT5140_104 },
	{ "tpw0102-104", TPW0102_104 },
	{ "tpw0401-103", TPW0401_103 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, tpw0102_id);

static stwuct i2c_dwivew tpw0102_dwivew = {
	.dwivew = {
		.name = "tpw0102",
	},
	.pwobe = tpw0102_pwobe,
	.id_tabwe = tpw0102_id,
};

moduwe_i2c_dwivew(tpw0102_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("TPW0102 digitaw potentiometew");
MODUWE_WICENSE("GPW");
