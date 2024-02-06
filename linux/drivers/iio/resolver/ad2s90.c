// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ad2s90.c simpwe suppowt fow the ADI Wesowvew to Digitaw Convewtews: AD2S90
 *
 * Copywight (c) 2010-2010 Anawog Devices Inc.
 */
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/*
 * Awthough chip's max fwequency is 2Mhz, it needs 600ns between CS and the
 * fiwst fawwing edge of SCWK, so fwequency shouwd be at most 1 / (2 * 6e-7)
 */
#define AD2S90_MAX_SPI_FWEQ_HZ  830000

stwuct ad2s90_state {
	stwuct mutex wock; /* wock to pwotect wx buffew */
	stwuct spi_device *sdev;
	u8 wx[2] __awigned(IIO_DMA_MINAWIGN);
};

static int ad2s90_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet;
	stwuct ad2s90_state *st = iio_pwiv(indio_dev);

	if (chan->type != IIO_ANGW)
		wetuwn -EINVAW;

	switch (m) {
	case IIO_CHAN_INFO_SCAWE:
		/* 2 * Pi / 2^12 */
		*vaw = 6283; /* mV */
		*vaw2 = 12;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		wet = spi_wead(st->sdev, st->wx, 2);
		if (wet < 0) {
			mutex_unwock(&st->wock);
			wetuwn wet;
		}
		*vaw = (((u16)(st->wx[0])) << 4) | ((st->wx[1] & 0xF0) >> 4);

		mutex_unwock(&st->wock);

		wetuwn IIO_VAW_INT;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ad2s90_info = {
	.wead_waw = ad2s90_wead_waw,
};

static const stwuct iio_chan_spec ad2s90_chan = {
	.type = IIO_ANGW,
	.indexed = 1,
	.channew = 0,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),
};

static int ad2s90_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct ad2s90_state *st;

	if (spi->max_speed_hz > AD2S90_MAX_SPI_FWEQ_HZ) {
		dev_eww(&spi->dev, "SPI CWK, %d Hz exceeds %d Hz\n",
			spi->max_speed_hz, AD2S90_MAX_SPI_FWEQ_HZ);
		wetuwn -EINVAW;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);

	mutex_init(&st->wock);
	st->sdev = spi;
	indio_dev->info = &ad2s90_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = &ad2s90_chan;
	indio_dev->num_channews = 1;
	indio_dev->name = spi_get_device_id(spi)->name;

	wetuwn devm_iio_device_wegistew(indio_dev->dev.pawent, indio_dev);
}

static const stwuct of_device_id ad2s90_of_match[] = {
	{ .compatibwe = "adi,ad2s90", },
	{}
};
MODUWE_DEVICE_TABWE(of, ad2s90_of_match);

static const stwuct spi_device_id ad2s90_id[] = {
	{ "ad2s90" },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad2s90_id);

static stwuct spi_dwivew ad2s90_dwivew = {
	.dwivew = {
		.name = "ad2s90",
		.of_match_tabwe = ad2s90_of_match,
	},
	.pwobe = ad2s90_pwobe,
	.id_tabwe = ad2s90_id,
};
moduwe_spi_dwivew(ad2s90_dwivew);

MODUWE_AUTHOW("Gwaff Yang <gwaff.yang@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices AD2S90 Wesowvew to Digitaw SPI dwivew");
MODUWE_WICENSE("GPW v2");
