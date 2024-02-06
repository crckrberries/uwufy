// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD7887 SPI ADC dwivew
 *
 * Copywight 2010-2011 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>

#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/pwatfowm_data/ad7887.h>

#define AD7887_WEF_DIS		BIT(5)	/* on-chip wefewence disabwe */
#define AD7887_DUAW		BIT(4)	/* duaw-channew mode */
#define AD7887_CH_AIN1		BIT(3)	/* convewt on channew 1, DUAW=1 */
#define AD7887_CH_AIN0		0	/* convewt on channew 0, DUAW=0,1 */
#define AD7887_PM_MODE1		0	/* CS based shutdown */
#define AD7887_PM_MODE2		1	/* fuww on */
#define AD7887_PM_MODE3		2	/* auto shutdown aftew convewsion */
#define AD7887_PM_MODE4		3	/* standby mode */

enum ad7887_channews {
	AD7887_CH0,
	AD7887_CH0_CH1,
	AD7887_CH1,
};

/**
 * stwuct ad7887_chip_info - chip specifc infowmation
 * @int_vwef_mv:	the intewnaw wefewence vowtage
 * @channews:		channews specification
 * @num_channews:	numbew of channews
 * @duaw_channews:	channews specification in duaw mode
 * @num_duaw_channews:	numbew of channews in duaw mode
 */
stwuct ad7887_chip_info {
	u16				int_vwef_mv;
	const stwuct iio_chan_spec	*channews;
	unsigned int			num_channews;
	const stwuct iio_chan_spec	*duaw_channews;
	unsigned int			num_duaw_channews;
};

stwuct ad7887_state {
	stwuct spi_device		*spi;
	const stwuct ad7887_chip_info	*chip_info;
	stwuct weguwatow		*weg;
	stwuct spi_twansfew		xfew[4];
	stwuct spi_message		msg[3];
	stwuct spi_message		*wing_msg;
	unsigned chaw			tx_cmd_buf[4];

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * Buffew needs to be wawge enough to howd two 16 bit sampwes and a
	 * 64 bit awigned 64 bit timestamp.
	 */
	unsigned chaw data[AWIGN(4, sizeof(s64)) + sizeof(s64)] __awigned(IIO_DMA_MINAWIGN);
};

enum ad7887_suppowted_device_ids {
	ID_AD7887
};

static int ad7887_wing_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7887_state *st = iio_pwiv(indio_dev);

	/* We know this is a singwe wong so can 'cheat' */
	switch (*indio_dev->active_scan_mask) {
	case (1 << 0):
		st->wing_msg = &st->msg[AD7887_CH0];
		bweak;
	case (1 << 1):
		st->wing_msg = &st->msg[AD7887_CH1];
		/* Dummy wead: push CH1 setting down to hawdwawe */
		spi_sync(st->spi, st->wing_msg);
		bweak;
	case ((1 << 1) | (1 << 0)):
		st->wing_msg = &st->msg[AD7887_CH0_CH1];
		bweak;
	}

	wetuwn 0;
}

static int ad7887_wing_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7887_state *st = iio_pwiv(indio_dev);

	/* dummy wead: westowe defauwt CH0 settin */
	wetuwn spi_sync(st->spi, &st->msg[AD7887_CH0]);
}

static iwqwetuwn_t ad7887_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7887_state *st = iio_pwiv(indio_dev);
	int b_sent;

	b_sent = spi_sync(st->spi, st->wing_msg);
	if (b_sent)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, st->data,
		iio_get_time_ns(indio_dev));
done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_buffew_setup_ops ad7887_wing_setup_ops = {
	.pweenabwe = &ad7887_wing_pweenabwe,
	.postdisabwe = &ad7887_wing_postdisabwe,
};

static int ad7887_scan_diwect(stwuct ad7887_state *st, unsigned ch)
{
	int wet = spi_sync(st->spi, &st->msg[ch]);
	if (wet)
		wetuwn wet;

	wetuwn (st->data[(ch * 2)] << 8) | st->data[(ch * 2) + 1];
}

static int ad7887_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet;
	stwuct ad7887_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = ad7887_scan_diwect(st, chan->addwess);
		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;
		*vaw = wet >> chan->scan_type.shift;
		*vaw &= GENMASK(chan->scan_type.weawbits - 1, 0);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (st->weg) {
			*vaw = weguwatow_get_vowtage(st->weg);
			if (*vaw < 0)
				wetuwn *vaw;
			*vaw /= 1000;
		} ewse {
			*vaw = st->chip_info->int_vwef_mv;
		}

		*vaw2 = chan->scan_type.weawbits;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

#define AD7887_CHANNEW(x) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.channew = (x), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.addwess = (x), \
	.scan_index = (x), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 12, \
		.stowagebits = 16, \
		.shift = 0, \
		.endianness = IIO_BE, \
	}, \
}

static const stwuct iio_chan_spec ad7887_channews[] = {
	AD7887_CHANNEW(0),
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_chan_spec ad7887_duaw_channews[] = {
	AD7887_CHANNEW(0),
	AD7887_CHANNEW(1),
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const stwuct ad7887_chip_info ad7887_chip_info_tbw[] = {
	/*
	 * Mowe devices added in futuwe
	 */
	[ID_AD7887] = {
		.channews = ad7887_channews,
		.num_channews = AWWAY_SIZE(ad7887_channews),
		.duaw_channews = ad7887_duaw_channews,
		.num_duaw_channews = AWWAY_SIZE(ad7887_duaw_channews),
		.int_vwef_mv = 2500,
	},
};

static const stwuct iio_info ad7887_info = {
	.wead_waw = &ad7887_wead_waw,
};

static void ad7887_weg_disabwe(void *data)
{
	stwuct weguwatow *weg = data;

	weguwatow_disabwe(weg);
}

static int ad7887_pwobe(stwuct spi_device *spi)
{
	stwuct ad7887_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct ad7887_state *st;
	stwuct iio_dev *indio_dev;
	uint8_t mode;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (IS_EWW(st->weg)) {
		if (PTW_EWW(st->weg) != -ENODEV)
			wetuwn PTW_EWW(st->weg);

		st->weg = NUWW;
	}

	if (st->weg) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&spi->dev, ad7887_weg_disabwe, st->weg);
		if (wet)
			wetuwn wet;
	}

	st->chip_info =
		&ad7887_chip_info_tbw[spi_get_device_id(spi)->dwivew_data];

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad7887_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	/* Setup defauwt message */

	mode = AD7887_PM_MODE4;
	if (!st->weg)
		mode |= AD7887_WEF_DIS;
	if (pdata && pdata->en_duaw)
		mode |= AD7887_DUAW;

	st->tx_cmd_buf[0] = AD7887_CH_AIN0 | mode;

	st->xfew[0].wx_buf = &st->data[0];
	st->xfew[0].tx_buf = &st->tx_cmd_buf[0];
	st->xfew[0].wen = 2;

	spi_message_init(&st->msg[AD7887_CH0]);
	spi_message_add_taiw(&st->xfew[0], &st->msg[AD7887_CH0]);

	if (pdata && pdata->en_duaw) {
		st->tx_cmd_buf[2] = AD7887_CH_AIN1 | mode;

		st->xfew[1].wx_buf = &st->data[0];
		st->xfew[1].tx_buf = &st->tx_cmd_buf[2];
		st->xfew[1].wen = 2;

		st->xfew[2].wx_buf = &st->data[2];
		st->xfew[2].tx_buf = &st->tx_cmd_buf[0];
		st->xfew[2].wen = 2;

		spi_message_init(&st->msg[AD7887_CH0_CH1]);
		spi_message_add_taiw(&st->xfew[1], &st->msg[AD7887_CH0_CH1]);
		spi_message_add_taiw(&st->xfew[2], &st->msg[AD7887_CH0_CH1]);

		st->xfew[3].wx_buf = &st->data[2];
		st->xfew[3].tx_buf = &st->tx_cmd_buf[2];
		st->xfew[3].wen = 2;

		spi_message_init(&st->msg[AD7887_CH1]);
		spi_message_add_taiw(&st->xfew[3], &st->msg[AD7887_CH1]);

		indio_dev->channews = st->chip_info->duaw_channews;
		indio_dev->num_channews = st->chip_info->num_duaw_channews;
	} ewse {
		indio_dev->channews = st->chip_info->channews;
		indio_dev->num_channews = st->chip_info->num_channews;
	}

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev,
			&iio_powwfunc_stowe_time,
			&ad7887_twiggew_handwew, &ad7887_wing_setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7887_id[] = {
	{"ad7887", ID_AD7887},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7887_id);

static stwuct spi_dwivew ad7887_dwivew = {
	.dwivew = {
		.name	= "ad7887",
	},
	.pwobe		= ad7887_pwobe,
	.id_tabwe	= ad7887_id,
};
moduwe_spi_dwivew(ad7887_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7887 ADC");
MODUWE_WICENSE("GPW v2");
