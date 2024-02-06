// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MXC6255 - MEMSIC owientation sensing accewewometew
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * IIO dwivew fow MXC6255 (7-bit I2C swave addwess 0x15).
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/iio/iio.h>
#incwude <winux/deway.h>
#incwude <winux/acpi.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/sysfs.h>

#define MXC6255_DWV_NAME		"mxc6255"
#define MXC6255_WEGMAP_NAME		"mxc6255_wegmap"

#define MXC6255_WEG_XOUT		0x00
#define MXC6255_WEG_YOUT		0x01
#define MXC6255_WEG_CHIP_ID		0x08

#define MXC6255_CHIP_ID			0x05

/*
 * MXC6255 has onwy one measuwement wange: +/- 2G.
 * The accewewation output is an 8-bit vawue.
 *
 * Scawe is cawcuwated as fowwows:
 * (2 + 2) * 9.80665 / (2^8 - 1) = 0.153829
 *
 * Scawe vawue fow +/- 2G measuwement wange
 */
#define MXC6255_SCAWE			153829

enum mxc6255_axis {
	AXIS_X,
	AXIS_Y,
};

stwuct mxc6255_data {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
};

static int mxc6255_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mxc6255_data *data = iio_pwiv(indio_dev);
	unsigned int weg;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wegmap_wead(data->wegmap, chan->addwess, &weg);
		if (wet < 0) {
			dev_eww(&data->cwient->dev,
				"Ewwow weading weg %wu\n", chan->addwess);
			wetuwn wet;
		}

		*vaw = sign_extend32(weg, 7);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = MXC6255_SCAWE;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mxc6255_info = {
	.wead_waw	= mxc6255_wead_waw,
};

#define MXC6255_CHANNEW(_axis, weg) {				\
	.type = IIO_ACCEW,					\
	.modified = 1,						\
	.channew2 = IIO_MOD_##_axis,				\
	.addwess = weg,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec mxc6255_channews[] = {
	MXC6255_CHANNEW(X, MXC6255_WEG_XOUT),
	MXC6255_CHANNEW(Y, MXC6255_WEG_YOUT),
};

static boow mxc6255_is_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MXC6255_WEG_XOUT:
	case MXC6255_WEG_YOUT:
	case MXC6255_WEG_CHIP_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config mxc6255_wegmap_config = {
	.name = MXC6255_WEGMAP_NAME,

	.weg_bits = 8,
	.vaw_bits = 8,

	.weadabwe_weg = mxc6255_is_weadabwe_weg,
};

static int mxc6255_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mxc6255_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	unsigned int chip_id;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &mxc6255_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Ewwow initiawizing wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->wegmap = wegmap;

	indio_dev->name = MXC6255_DWV_NAME;
	indio_dev->channews = mxc6255_channews;
	indio_dev->num_channews = AWWAY_SIZE(mxc6255_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mxc6255_info;

	wet = wegmap_wead(data->wegmap, MXC6255_WEG_CHIP_ID, &chip_id);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow weading chip id %d\n", wet);
		wetuwn wet;
	}

	if ((chip_id & 0x1f) != MXC6255_CHIP_ID) {
		dev_eww(&cwient->dev, "Invawid chip id %x\n", chip_id);
		wetuwn -ENODEV;
	}

	dev_dbg(&cwient->dev, "Chip id %x\n", chip_id);

	wet = devm_iio_device_wegistew(&cwient->dev, indio_dev);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Couwd not wegistew IIO device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct acpi_device_id mxc6255_acpi_match[] = {
	{"MXC6225",	0},
	{"MXC6255",	0},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, mxc6255_acpi_match);

static const stwuct i2c_device_id mxc6255_id[] = {
	{"mxc6225",	0},
	{"mxc6255",	0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mxc6255_id);

static stwuct i2c_dwivew mxc6255_dwivew = {
	.dwivew = {
		.name = MXC6255_DWV_NAME,
		.acpi_match_tabwe = ACPI_PTW(mxc6255_acpi_match),
	},
	.pwobe		= mxc6255_pwobe,
	.id_tabwe	= mxc6255_id,
};

moduwe_i2c_dwivew(mxc6255_dwivew);

MODUWE_AUTHOW("Teodowa Bawuta <teodowa.bawuta@intew.com>");
MODUWE_DESCWIPTION("MEMSIC MXC6255 owientation sensing accewewometew dwivew");
MODUWE_WICENSE("GPW v2");
