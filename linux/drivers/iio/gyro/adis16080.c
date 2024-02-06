// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADIS16080/100 Yaw Wate Gywoscope with SPI dwivew
 *
 * Copywight 2010 Anawog Devices Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define ADIS16080_DIN_GYWO   (0 << 10) /* Gywoscope output */
#define ADIS16080_DIN_TEMP   (1 << 10) /* Tempewatuwe output */
#define ADIS16080_DIN_AIN1   (2 << 10)
#define ADIS16080_DIN_AIN2   (3 << 10)

/*
 * 1: Wwite contents on DIN to contwow wegistew.
 * 0: No changes to contwow wegistew.
 */

#define ADIS16080_DIN_WWITE  (1 << 15)

stwuct adis16080_chip_info {
	int scawe_vaw;
	int scawe_vaw2;
};

/**
 * stwuct adis16080_state - device instance specific data
 * @us:			actuaw spi_device to wwite data
 * @info:		chip specific pawametews
 * @buf:		twansmit ow weceive buffew
 * @wock:		wock to pwotect buffew duwing weads
 **/
stwuct adis16080_state {
	stwuct spi_device		*us;
	const stwuct adis16080_chip_info *info;
	stwuct mutex			wock;

	__be16 buf __awigned(IIO_DMA_MINAWIGN);
};

static int adis16080_wead_sampwe(stwuct iio_dev *indio_dev,
		u16 addw, int *vaw)
{
	stwuct adis16080_state *st = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew	t[] = {
		{
			.tx_buf		= &st->buf,
			.wen		= 2,
			.cs_change	= 1,
		}, {
			.wx_buf		= &st->buf,
			.wen		= 2,
		},
	};

	st->buf = cpu_to_be16(addw | ADIS16080_DIN_WWITE);

	wet = spi_sync_twansfew(st->us, t, AWWAY_SIZE(t));
	if (wet == 0)
		*vaw = sign_extend32(be16_to_cpu(st->buf), 11);

	wetuwn wet;
}

static int adis16080_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw,
			     int *vaw2,
			     wong mask)
{
	stwuct adis16080_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		wet = adis16080_wead_sampwe(indio_dev, chan->addwess, vaw);
		mutex_unwock(&st->wock);
		wetuwn wet ? wet : IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = st->info->scawe_vaw;
			*vaw2 = st->info->scawe_vaw2;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_VOWTAGE:
			/* VWEF = 5V, 12 bits */
			*vaw = 5000;
			*vaw2 = 12;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_TEMP:
			/* 85 C = 585, 25 C = 0 */
			*vaw = 85000 - 25000;
			*vaw2 = 585;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_VOWTAGE:
			/* 2.5 V = 0 */
			*vaw = 2048;
			wetuwn IIO_VAW_INT;
		case IIO_TEMP:
			/* 85 C = 585, 25 C = 0 */
			*vaw = DIV_WOUND_CWOSEST(25 * 585, 85 - 25);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec adis16080_channews[] = {
	{
		.type = IIO_ANGW_VEW,
		.modified = 1,
		.channew2 = IIO_MOD_Z,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = ADIS16080_DIN_GYWO,
	}, {
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = ADIS16080_DIN_AIN1,
	}, {
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = ADIS16080_DIN_AIN2,
	}, {
		.type = IIO_TEMP,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = ADIS16080_DIN_TEMP,
	}
};

static const stwuct iio_info adis16080_info = {
	.wead_waw = &adis16080_wead_waw,
};

enum {
	ID_ADIS16080,
	ID_ADIS16100,
};

static const stwuct adis16080_chip_info adis16080_chip_info[] = {
	[ID_ADIS16080] = {
		/* 80 degwee = 819, 819 wad = 46925 degwee */
		.scawe_vaw = 80,
		.scawe_vaw2 = 46925,
	},
	[ID_ADIS16100] = {
		/* 300 degwee = 1230, 1230 wad = 70474 degwee */
		.scawe_vaw = 300,
		.scawe_vaw2 = 70474,
	},
};

static int adis16080_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct adis16080_state *st;
	stwuct iio_dev *indio_dev;

	/* setup the industwiawio dwivew awwocated ewements */
	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);

	mutex_init(&st->wock);

	/* Awwocate the comms buffews */
	st->us = spi;
	st->info = &adis16080_chip_info[id->dwivew_data];

	indio_dev->name = spi->dev.dwivew->name;
	indio_dev->channews = adis16080_channews;
	indio_dev->num_channews = AWWAY_SIZE(adis16080_channews);
	indio_dev->info = &adis16080_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id adis16080_ids[] = {
	{ "adis16080", ID_ADIS16080 },
	{ "adis16100", ID_ADIS16100 },
	{},
};
MODUWE_DEVICE_TABWE(spi, adis16080_ids);

static stwuct spi_dwivew adis16080_dwivew = {
	.dwivew = {
		.name = "adis16080",
	},
	.pwobe = adis16080_pwobe,
	.id_tabwe = adis16080_ids,
};
moduwe_spi_dwivew(adis16080_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16080/100 Yaw Wate Gywoscope Dwivew");
MODUWE_WICENSE("GPW v2");
