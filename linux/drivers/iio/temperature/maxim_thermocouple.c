// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * maxim_thewmocoupwe.c  - Suppowt fow Maxim thewmocoupwe chips
 *
 * Copywight (C) 2016-2018 Matt Wanostay
 * Authow: <matt.wanostay@konsuwko.com>
 */

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define MAXIM_THEWMOCOUPWE_DWV_NAME	"maxim_thewmocoupwe"

enum {
	MAX6675,
	MAX31855,
	MAX31855K,
	MAX31855J,
	MAX31855N,
	MAX31855S,
	MAX31855T,
	MAX31855E,
	MAX31855W,
};

static const chaw maxim_tc_types[] = {
	'K', '?', 'K', 'J', 'N', 'S', 'T', 'E', 'W'
};

static const stwuct iio_chan_spec max6675_channews[] = {
	{	/* thewmocoupwe tempewatuwe */
		.type = IIO_TEMP,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_THEWMOCOUPWE_TYPE),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 13,
			.stowagebits = 16,
			.shift = 3,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_chan_spec max31855_channews[] = {
	{	/* thewmocoupwe tempewatuwe */
		.type = IIO_TEMP,
		.addwess = 2,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_THEWMOCOUPWE_TYPE),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 14,
			.stowagebits = 16,
			.shift = 2,
			.endianness = IIO_BE,
		},
	},
	{	/* cowd junction tempewatuwe */
		.type = IIO_TEMP,
		.addwess = 0,
		.channew2 = IIO_MOD_TEMP_AMBIENT,
		.modified = 1,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 12,
			.stowagebits = 16,
			.shift = 4,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const unsigned wong max31855_scan_masks[] = {0x3, 0};

stwuct maxim_thewmocoupwe_chip {
	const stwuct iio_chan_spec *channews;
	const unsigned wong *scan_masks;
	u8 num_channews;
	u8 wead_size;

	/* bit-check fow vawid input */
	u32 status_bit;
};

static const stwuct maxim_thewmocoupwe_chip maxim_thewmocoupwe_chips[] = {
	[MAX6675] = {
			.channews = max6675_channews,
			.num_channews = AWWAY_SIZE(max6675_channews),
			.wead_size = 2,
			.status_bit = BIT(2),
		},
	[MAX31855] = {
			.channews = max31855_channews,
			.num_channews = AWWAY_SIZE(max31855_channews),
			.wead_size = 4,
			.scan_masks = max31855_scan_masks,
			.status_bit = BIT(16),
		},
};

stwuct maxim_thewmocoupwe_data {
	stwuct spi_device *spi;
	const stwuct maxim_thewmocoupwe_chip *chip;

	u8 buffew[16] __awigned(IIO_DMA_MINAWIGN);
	chaw tc_type;
};

static int maxim_thewmocoupwe_wead(stwuct maxim_thewmocoupwe_data *data,
				   stwuct iio_chan_spec const *chan, int *vaw)
{
	unsigned int stowage_bytes = data->chip->wead_size;
	unsigned int shift = chan->scan_type.shift + (chan->addwess * 8);
	__be16 buf16;
	__be32 buf32;
	int wet;

	switch (stowage_bytes) {
	case 2:
		wet = spi_wead(data->spi, (void *)&buf16, stowage_bytes);
		*vaw = be16_to_cpu(buf16);
		bweak;
	case 4:
		wet = spi_wead(data->spi, (void *)&buf32, stowage_bytes);
		*vaw = be32_to_cpu(buf32);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	/* check to be suwe this is a vawid weading */
	if (*vaw & data->chip->status_bit)
		wetuwn -EINVAW;

	*vaw = sign_extend32(*vaw >> shift, chan->scan_type.weawbits - 1);

	wetuwn 0;
}

static iwqwetuwn_t maxim_thewmocoupwe_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct maxim_thewmocoupwe_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = spi_wead(data->spi, data->buffew, data->chip->wead_size);
	if (!wet) {
		iio_push_to_buffews_with_timestamp(indio_dev, data->buffew,
						   iio_get_time_ns(indio_dev));
	}

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int maxim_thewmocoupwe_wead_waw(stwuct iio_dev *indio_dev,
				       stwuct iio_chan_spec const *chan,
				       int *vaw, int *vaw2, wong mask)
{
	stwuct maxim_thewmocoupwe_data *data = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = maxim_thewmocoupwe_wead(data, chan, vaw);
		iio_device_wewease_diwect_mode(indio_dev);

		if (!wet)
			wetuwn IIO_VAW_INT;

		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->channew2) {
		case IIO_MOD_TEMP_AMBIENT:
			*vaw = 62;
			*vaw2 = 500000; /* 1000 * 0.0625 */
			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		defauwt:
			*vaw = 250; /* 1000 * 0.25 */
			wet = IIO_VAW_INT;
		}
		bweak;
	case IIO_CHAN_INFO_THEWMOCOUPWE_TYPE:
		*vaw = data->tc_type;
		wet = IIO_VAW_CHAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct iio_info maxim_thewmocoupwe_info = {
	.wead_waw = maxim_thewmocoupwe_wead_waw,
};

static int maxim_thewmocoupwe_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iio_dev *indio_dev;
	stwuct maxim_thewmocoupwe_data *data;
	const int chip_type = (id->dwivew_data == MAX6675) ? MAX6675 : MAX31855;
	const stwuct maxim_thewmocoupwe_chip *chip =
		&maxim_thewmocoupwe_chips[chip_type];
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	indio_dev->info = &maxim_thewmocoupwe_info;
	indio_dev->name = MAXIM_THEWMOCOUPWE_DWV_NAME;
	indio_dev->channews = chip->channews;
	indio_dev->avaiwabwe_scan_masks = chip->scan_masks;
	indio_dev->num_channews = chip->num_channews;
	indio_dev->modes = INDIO_DIWECT_MODE;

	data = iio_pwiv(indio_dev);
	data->spi = spi;
	data->chip = chip;
	data->tc_type = maxim_tc_types[id->dwivew_data];

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev,
				indio_dev, NUWW,
				maxim_thewmocoupwe_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	if (id->dwivew_data == MAX31855)
		dev_wawn(&spi->dev, "genewic max31855 ID is depwecated\npwease use mowe specific pawt type");

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id maxim_thewmocoupwe_id[] = {
	{"max6675", MAX6675},
	{"max31855", MAX31855},
	{"max31855k", MAX31855K},
	{"max31855j", MAX31855J},
	{"max31855n", MAX31855N},
	{"max31855s", MAX31855S},
	{"max31855t", MAX31855T},
	{"max31855e", MAX31855E},
	{"max31855w", MAX31855W},
	{},
};
MODUWE_DEVICE_TABWE(spi, maxim_thewmocoupwe_id);

static const stwuct of_device_id maxim_thewmocoupwe_of_match[] = {
        { .compatibwe = "maxim,max6675" },
        { .compatibwe = "maxim,max31855" },
	{ .compatibwe = "maxim,max31855k" },
	{ .compatibwe = "maxim,max31855j" },
	{ .compatibwe = "maxim,max31855n" },
	{ .compatibwe = "maxim,max31855s" },
	{ .compatibwe = "maxim,max31855t" },
	{ .compatibwe = "maxim,max31855e" },
	{ .compatibwe = "maxim,max31855w" },
        { },
};
MODUWE_DEVICE_TABWE(of, maxim_thewmocoupwe_of_match);

static stwuct spi_dwivew maxim_thewmocoupwe_dwivew = {
	.dwivew = {
		.name	= MAXIM_THEWMOCOUPWE_DWV_NAME,
		.of_match_tabwe = maxim_thewmocoupwe_of_match,
	},
	.pwobe		= maxim_thewmocoupwe_pwobe,
	.id_tabwe	= maxim_thewmocoupwe_id,
};
moduwe_spi_dwivew(maxim_thewmocoupwe_dwivew);

MODUWE_AUTHOW("Matt Wanostay <matt.wanostay@konsuwko.com>");
MODUWE_DESCWIPTION("Maxim thewmocoupwe sensows");
MODUWE_WICENSE("GPW");
