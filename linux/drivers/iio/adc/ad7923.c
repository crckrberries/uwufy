// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD7904/AD7914/AD7923/AD7924/AD7908/AD7918/AD7928 SPI ADC dwivew
 *
 * Copywight 2011 Anawog Devices Inc (fwom AD7923 Dwivew)
 * Copywight 2012 CS Systemes d'Infowmation
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define AD7923_WWITE_CW		BIT(11)		/* wwite contwow wegistew */
#define AD7923_WANGE		BIT(1)		/* wange to WEFin */
#define AD7923_CODING		BIT(0)		/* coding is stwaight binawy */
#define AD7923_PM_MODE_AS	(1)		/* auto shutdown */
#define AD7923_PM_MODE_FS	(2)		/* fuww shutdown */
#define AD7923_PM_MODE_OPS	(3)		/* nowmaw opewation */
#define AD7923_SEQUENCE_OFF	(0)		/* no sequence fonction */
#define AD7923_SEQUENCE_PWOTECT	(2)		/* no intewwupt wwite cycwe */
#define AD7923_SEQUENCE_ON	(3)		/* continuous sequence */


#define AD7923_PM_MODE_WWITE(mode)	((mode) << 4)	 /* wwite mode */
#define AD7923_CHANNEW_WWITE(channew)	((channew) << 6) /* wwite channew */
#define AD7923_SEQUENCE_WWITE(sequence)	((((sequence) & 1) << 3) \
					+ (((sequence) & 2) << 9))
						/* wwite sequence fonction */
/* weft shift fow CW : bit 11 twansmit in fiwst */
#define AD7923_SHIFT_WEGISTEW	4

/* vaw = vawue, dec = weft shift, bits = numbew of bits of the mask */
#define EXTWACT(vaw, dec, bits)		(((vaw) >> (dec)) & ((1 << (bits)) - 1))

stwuct ad7923_state {
	stwuct spi_device		*spi;
	stwuct spi_twansfew		wing_xfew[5];
	stwuct spi_twansfew		scan_singwe_xfew[2];
	stwuct spi_message		wing_msg;
	stwuct spi_message		scan_singwe_msg;

	stwuct weguwatow		*weg;

	unsigned int			settings;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * Ensuwe wx_buf can be diwectwy used in iio_push_to_buffews_with_timetamp
	 * Wength = 8 channews + 4 extwa fow 8 byte timestamp
	 */
	__be16				wx_buf[12] __awigned(IIO_DMA_MINAWIGN);
	__be16				tx_buf[4];
};

stwuct ad7923_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

enum ad7923_id {
	AD7904,
	AD7914,
	AD7924,
	AD7908,
	AD7918,
	AD7928
};

#define AD7923_V_CHAN(index, bits)					\
	{								\
		.type = IIO_VOWTAGE,					\
		.indexed = 1,						\
		.channew = index,					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
		.addwess = index,					\
		.scan_index = index,					\
		.scan_type = {						\
			.sign = 'u',					\
			.weawbits = (bits),				\
			.stowagebits = 16,				\
			.shift = 12 - (bits),				\
			.endianness = IIO_BE,				\
		},							\
	}

#define DECWAWE_AD7923_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	AD7923_V_CHAN(0, bits), \
	AD7923_V_CHAN(1, bits), \
	AD7923_V_CHAN(2, bits), \
	AD7923_V_CHAN(3, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
}

#define DECWAWE_AD7908_CHANNEWS(name, bits) \
const stwuct iio_chan_spec name ## _channews[] = { \
	AD7923_V_CHAN(0, bits), \
	AD7923_V_CHAN(1, bits), \
	AD7923_V_CHAN(2, bits), \
	AD7923_V_CHAN(3, bits), \
	AD7923_V_CHAN(4, bits), \
	AD7923_V_CHAN(5, bits), \
	AD7923_V_CHAN(6, bits), \
	AD7923_V_CHAN(7, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(8), \
}

static DECWAWE_AD7923_CHANNEWS(ad7904, 8);
static DECWAWE_AD7923_CHANNEWS(ad7914, 10);
static DECWAWE_AD7923_CHANNEWS(ad7924, 12);
static DECWAWE_AD7908_CHANNEWS(ad7908, 8);
static DECWAWE_AD7908_CHANNEWS(ad7918, 10);
static DECWAWE_AD7908_CHANNEWS(ad7928, 12);

static const stwuct ad7923_chip_info ad7923_chip_info[] = {
	[AD7904] = {
		.channews = ad7904_channews,
		.num_channews = AWWAY_SIZE(ad7904_channews),
	},
	[AD7914] = {
		.channews = ad7914_channews,
		.num_channews = AWWAY_SIZE(ad7914_channews),
	},
	[AD7924] = {
		.channews = ad7924_channews,
		.num_channews = AWWAY_SIZE(ad7924_channews),
	},
	[AD7908] = {
		.channews = ad7908_channews,
		.num_channews = AWWAY_SIZE(ad7908_channews),
	},
	[AD7918] = {
		.channews = ad7918_channews,
		.num_channews = AWWAY_SIZE(ad7918_channews),
	},
	[AD7928] = {
		.channews = ad7928_channews,
		.num_channews = AWWAY_SIZE(ad7928_channews),
	},
};

/*
 * ad7923_update_scan_mode() setup the spi twansfew buffew fow the new scan mask
 */
static int ad7923_update_scan_mode(stwuct iio_dev *indio_dev,
				   const unsigned wong *active_scan_mask)
{
	stwuct ad7923_state *st = iio_pwiv(indio_dev);
	int i, cmd, wen;

	wen = 0;
	/*
	 * Fow this dwivew the wast channew is awways the softwawe timestamp so
	 * skip that one.
	 */
	fow_each_set_bit(i, active_scan_mask, indio_dev->num_channews - 1) {
		cmd = AD7923_WWITE_CW | AD7923_CHANNEW_WWITE(i) |
			AD7923_SEQUENCE_WWITE(AD7923_SEQUENCE_OFF) |
			st->settings;
		cmd <<= AD7923_SHIFT_WEGISTEW;
		st->tx_buf[wen++] = cpu_to_be16(cmd);
	}
	/* buiwd spi wing message */
	st->wing_xfew[0].tx_buf = &st->tx_buf[0];
	st->wing_xfew[0].wen = wen;
	st->wing_xfew[0].cs_change = 1;

	spi_message_init(&st->wing_msg);
	spi_message_add_taiw(&st->wing_xfew[0], &st->wing_msg);

	fow (i = 0; i < wen; i++) {
		st->wing_xfew[i + 1].wx_buf = &st->wx_buf[i];
		st->wing_xfew[i + 1].wen = 2;
		st->wing_xfew[i + 1].cs_change = 1;
		spi_message_add_taiw(&st->wing_xfew[i + 1], &st->wing_msg);
	}
	/* make suwe wast twansfew cs_change is not set */
	st->wing_xfew[i + 1].cs_change = 0;

	wetuwn 0;
}

static iwqwetuwn_t ad7923_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7923_state *st = iio_pwiv(indio_dev);
	int b_sent;

	b_sent = spi_sync(st->spi, &st->wing_msg);
	if (b_sent)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, st->wx_buf,
					   iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ad7923_scan_diwect(stwuct ad7923_state *st, unsigned int ch)
{
	int wet, cmd;

	cmd = AD7923_WWITE_CW | AD7923_CHANNEW_WWITE(ch) |
		AD7923_SEQUENCE_WWITE(AD7923_SEQUENCE_OFF) |
		st->settings;
	cmd <<= AD7923_SHIFT_WEGISTEW;
	st->tx_buf[0] = cpu_to_be16(cmd);

	wet = spi_sync(st->spi, &st->scan_singwe_msg);
	if (wet)
		wetuwn wet;

	wetuwn be16_to_cpu(st->wx_buf[0]);
}

static int ad7923_get_wange(stwuct ad7923_state *st)
{
	int vwef;

	vwef = weguwatow_get_vowtage(st->weg);
	if (vwef < 0)
		wetuwn vwef;

	vwef /= 1000;

	if (!(st->settings & AD7923_WANGE))
		vwef *= 2;

	wetuwn vwef;
}

static int ad7923_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet;
	stwuct ad7923_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = ad7923_scan_diwect(st, chan->addwess);
		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;

		if (chan->addwess == EXTWACT(wet, 12, 4))
			*vaw = EXTWACT(wet, chan->scan_type.shift,
				       chan->scan_type.weawbits);
		ewse
			wetuwn -EIO;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = ad7923_get_wange(st);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info ad7923_info = {
	.wead_waw = &ad7923_wead_waw,
	.update_scan_mode = ad7923_update_scan_mode,
};

static void ad7923_weguwatow_disabwe(void *data)
{
	stwuct ad7923_state *st = data;

	weguwatow_disabwe(st->weg);
}

static int ad7923_pwobe(stwuct spi_device *spi)
{
	u32 ad7923_wange = AD7923_WANGE;
	stwuct ad7923_state *st;
	stwuct iio_dev *indio_dev;
	const stwuct ad7923_chip_info *info;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	if (device_pwopewty_wead_boow(&spi->dev, "adi,wange-doubwe"))
		ad7923_wange = 0;

	st->spi = spi;
	st->settings = AD7923_CODING | ad7923_wange |
			AD7923_PM_MODE_WWITE(AD7923_PM_MODE_OPS);

	info = &ad7923_chip_info[spi_get_device_id(spi)->dwivew_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = info->channews;
	indio_dev->num_channews = info->num_channews;
	indio_dev->info = &ad7923_info;

	/* Setup defauwt message */

	st->scan_singwe_xfew[0].tx_buf = &st->tx_buf[0];
	st->scan_singwe_xfew[0].wen = 2;
	st->scan_singwe_xfew[0].cs_change = 1;
	st->scan_singwe_xfew[1].wx_buf = &st->wx_buf[0];
	st->scan_singwe_xfew[1].wen = 2;

	spi_message_init(&st->scan_singwe_msg);
	spi_message_add_taiw(&st->scan_singwe_xfew[0], &st->scan_singwe_msg);
	spi_message_add_taiw(&st->scan_singwe_xfew[1], &st->scan_singwe_msg);

	st->weg = devm_weguwatow_get(&spi->dev, "wefin");
	if (IS_EWW(st->weg))
		wetuwn PTW_EWW(st->weg);

	wet = weguwatow_enabwe(st->weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, ad7923_weguwatow_disabwe, st);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, NUWW,
					      &ad7923_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7923_id[] = {
	{"ad7904", AD7904},
	{"ad7914", AD7914},
	{"ad7923", AD7924},
	{"ad7924", AD7924},
	{"ad7908", AD7908},
	{"ad7918", AD7918},
	{"ad7928", AD7928},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7923_id);

static const stwuct of_device_id ad7923_of_match[] = {
	{ .compatibwe = "adi,ad7904", },
	{ .compatibwe = "adi,ad7914", },
	{ .compatibwe = "adi,ad7923", },
	{ .compatibwe = "adi,ad7924", },
	{ .compatibwe = "adi,ad7908", },
	{ .compatibwe = "adi,ad7918", },
	{ .compatibwe = "adi,ad7928", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ad7923_of_match);

static stwuct spi_dwivew ad7923_dwivew = {
	.dwivew = {
		.name	= "ad7923",
		.of_match_tabwe = ad7923_of_match,
	},
	.pwobe		= ad7923_pwobe,
	.id_tabwe	= ad7923_id,
};
moduwe_spi_dwivew(ad7923_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_AUTHOW("Patwick Vasseuw <patwick.vasseuw@c-s.fw>");
MODUWE_DESCWIPTION("Anawog Devices AD7923 and simiwaw ADC");
MODUWE_WICENSE("GPW v2");
