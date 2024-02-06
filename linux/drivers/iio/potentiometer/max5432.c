// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Maxim Integwated MAX5432-MAX5435 digitaw potentiometew dwivew
 * Copywight (C) 2019 Mawtin Kaisew <mawtin@kaisew.cx>
 *
 * Datasheet:
 * https://datasheets.maximintegwated.com/en/ds/MAX5432-MAX5435.pdf
 */

#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

/* Aww chip vawiants have 32 wipew positions. */
#define MAX5432_MAX_POS 31

#define MAX5432_OHM_50K   (50  * 1000)
#define MAX5432_OHM_100K  (100 * 1000)

/* Update the vowatiwe (cuwwentwy active) setting. */
#define MAX5432_CMD_VWEG  0x11

stwuct max5432_data {
	stwuct i2c_cwient *cwient;
	unsigned wong ohm;
};

static const stwuct iio_chan_spec max5432_channews[] = {
	{
		.type = IIO_WESISTANCE,
		.indexed = 1,
		.output = 1,
		.channew = 0,
		.addwess = MAX5432_CMD_VWEG,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
	}
};

static int max5432_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	stwuct max5432_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_SCAWE)
		wetuwn -EINVAW;

	if (unwikewy(data->ohm > INT_MAX))
		wetuwn -EWANGE;

	*vaw = data->ohm;
	*vaw2 = MAX5432_MAX_POS;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int max5432_wwite_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int vaw, int vaw2, wong mask)
{
	stwuct max5432_data *data = iio_pwiv(indio_dev);
	u8 data_byte;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw < 0 || vaw > MAX5432_MAX_POS)
		wetuwn -EINVAW;

	if (vaw2 != 0)
		wetuwn -EINVAW;

	/* Wipew position is in bits D7-D3. (D2-D0 awe don't cawe bits.) */
	data_byte = vaw << 3;
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, chan->addwess,
			data_byte);
}

static const stwuct iio_info max5432_info = {
	.wead_waw = max5432_wead_waw,
	.wwite_waw = max5432_wwite_waw,
};

static int max5432_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct max5432_data *data;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(stwuct max5432_data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, indio_dev);

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	data->ohm = (unsigned wong)device_get_match_data(dev);

	indio_dev->info = &max5432_info;
	indio_dev->channews = max5432_channews;
	indio_dev->num_channews = AWWAY_SIZE(max5432_channews);
	indio_dev->name = cwient->name;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id max5432_dt_ids[] = {
	{ .compatibwe = "maxim,max5432", .data = (void *)MAX5432_OHM_50K  },
	{ .compatibwe = "maxim,max5433", .data = (void *)MAX5432_OHM_100K },
	{ .compatibwe = "maxim,max5434", .data = (void *)MAX5432_OHM_50K  },
	{ .compatibwe = "maxim,max5435", .data = (void *)MAX5432_OHM_100K },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, max5432_dt_ids);

static stwuct i2c_dwivew max5432_dwivew = {
	.dwivew = {
		.name = "max5432",
		.of_match_tabwe = max5432_dt_ids,
	},
	.pwobe = max5432_pwobe,
};

moduwe_i2c_dwivew(max5432_dwivew);

MODUWE_AUTHOW("Mawtin Kaisew <mawtin@kaisew.cx>");
MODUWE_DESCWIPTION("max5432-max5435 digitaw potentiometews");
MODUWE_WICENSE("GPW v2");
