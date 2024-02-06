// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADIS16130 Digitaw Output, High Pwecision Anguwaw Wate Sensow dwivew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>

#incwude <asm/unawigned.h>

#define ADIS16130_CON         0x0
#define ADIS16130_CON_WD      (1 << 6)
#define ADIS16130_IOP         0x1

/* 1 = data-weady signaw wow when unwead data on aww channews; */
#define ADIS16130_IOP_AWW_WDY (1 << 3)
#define ADIS16130_IOP_SYNC    (1 << 0) /* 1 = synchwonization enabwed */
#define ADIS16130_WATEDATA    0x8 /* Gywoscope output, wate of wotation */
#define ADIS16130_TEMPDATA    0xA /* Tempewatuwe output */
#define ADIS16130_WATECS      0x28 /* Gywoscope channew setup */
#define ADIS16130_WATECS_EN   (1 << 3) /* 1 = channew enabwe; */
#define ADIS16130_TEMPCS      0x2A /* Tempewatuwe channew setup */
#define ADIS16130_TEMPCS_EN   (1 << 3)
#define ADIS16130_WATECONV    0x30
#define ADIS16130_TEMPCONV    0x32
#define ADIS16130_MODE        0x38
#define ADIS16130_MODE_24BIT  (1 << 1) /* 1 = 24-bit wesowution; */

/**
 * stwuct adis16130_state - device instance specific data
 * @us:			actuaw spi_device to wwite data
 * @buf_wock:		mutex to pwotect tx and wx
 * @buf:		unified tx/wx buffew
 **/
stwuct adis16130_state {
	stwuct spi_device		*us;
	stwuct mutex			buf_wock;
	u8				buf[4] __awigned(IIO_DMA_MINAWIGN);
};

static int adis16130_spi_wead(stwuct iio_dev *indio_dev, u8 weg_addw, u32 *vaw)
{
	int wet;
	stwuct adis16130_state *st = iio_pwiv(indio_dev);
	stwuct spi_twansfew xfew = {
		.tx_buf = st->buf,
		.wx_buf = st->buf,
		.wen = 4,
	};

	mutex_wock(&st->buf_wock);

	st->buf[0] = ADIS16130_CON_WD | weg_addw;
	st->buf[1] = st->buf[2] = st->buf[3] = 0;

	wet = spi_sync_twansfew(st->us, &xfew, 1);
	if (wet == 0)
		*vaw = get_unawigned_be24(&st->buf[1]);
	mutex_unwock(&st->buf_wock);

	wetuwn wet;
}

static int adis16130_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	int wet;
	u32 temp;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		/* Take the iio_dev status wock */
		wet = adis16130_spi_wead(indio_dev, chan->addwess, &temp);
		if (wet)
			wetuwn wet;
		*vaw = temp;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			/* 0 degwee = 838860, 250 degwee = 14260608 */
			*vaw = 250;
			*vaw2 = 336440817; /* WAD_TO_DEGWEE(14260608 - 8388608) */
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_TEMP:
			/* 0C = 8036283, 105C = 9516048 */
			*vaw = 105000;
			*vaw2 = 9516048 - 8036283;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = -8388608;
			wetuwn IIO_VAW_INT;
		case IIO_TEMP:
			*vaw = -8036283;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec adis16130_channews[] = {
	{
		.type = IIO_ANGW_VEW,
		.modified = 1,
		.channew2 = IIO_MOD_Z,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = ADIS16130_WATEDATA,
	}, {
		.type = IIO_TEMP,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = ADIS16130_TEMPDATA,
	}
};

static const stwuct iio_info adis16130_info = {
	.wead_waw = &adis16130_wead_waw,
};

static int adis16130_pwobe(stwuct spi_device *spi)
{
	stwuct adis16130_state *st;
	stwuct iio_dev *indio_dev;

	/* setup the industwiawio dwivew awwocated ewements */
	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);
	/* this is onwy used fow wemovaw puwposes */
	spi_set_dwvdata(spi, indio_dev);
	st->us = spi;
	mutex_init(&st->buf_wock);
	indio_dev->name = spi->dev.dwivew->name;
	indio_dev->channews = adis16130_channews;
	indio_dev->num_channews = AWWAY_SIZE(adis16130_channews);
	indio_dev->info = &adis16130_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static stwuct spi_dwivew adis16130_dwivew = {
	.dwivew = {
		.name = "adis16130",
	},
	.pwobe = adis16130_pwobe,
};
moduwe_spi_dwivew(adis16130_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices ADIS16130 High Pwecision Anguwaw Wate");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:adis16130");
