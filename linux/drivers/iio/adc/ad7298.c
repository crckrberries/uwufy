// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD7298 SPI ADC dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define AD7298_WWITE	BIT(15) /* wwite to the contwow wegistew */
#define AD7298_WEPEAT	BIT(14) /* wepeated convewsion enabwe */
#define AD7298_CH(x)	BIT(13 - (x)) /* channew sewect */
#define AD7298_TSENSE	BIT(5) /* tempewatuwe convewsion enabwe */
#define AD7298_EXTWEF	BIT(2) /* extewnaw wefewence enabwe */
#define AD7298_TAVG	BIT(1) /* tempewatuwe sensow avewaging enabwe */
#define AD7298_PDD	BIT(0) /* pawtiaw powew down enabwe */

#define AD7298_MAX_CHAN		8
#define AD7298_INTWEF_mV	2500

#define AD7298_CH_TEMP		9

stwuct ad7298_state {
	stwuct spi_device		*spi;
	stwuct weguwatow		*weg;
	unsigned			ext_wef;
	stwuct spi_twansfew		wing_xfew[10];
	stwuct spi_twansfew		scan_singwe_xfew[3];
	stwuct spi_message		wing_msg;
	stwuct spi_message		scan_singwe_msg;
	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	__be16				wx_buf[12] __awigned(IIO_DMA_MINAWIGN);
	__be16				tx_buf[2];
};

#define AD7298_V_CHAN(index)						\
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
			.weawbits = 12,					\
			.stowagebits = 16,				\
			.endianness = IIO_BE,				\
		},							\
	}

static const stwuct iio_chan_spec ad7298_channews[] = {
	{
		.type = IIO_TEMP,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.addwess = AD7298_CH_TEMP,
		.scan_index = -1,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
		},
	},
	AD7298_V_CHAN(0),
	AD7298_V_CHAN(1),
	AD7298_V_CHAN(2),
	AD7298_V_CHAN(3),
	AD7298_V_CHAN(4),
	AD7298_V_CHAN(5),
	AD7298_V_CHAN(6),
	AD7298_V_CHAN(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
};

/*
 * ad7298_update_scan_mode() setup the spi twansfew buffew fow the new scan mask
 */
static int ad7298_update_scan_mode(stwuct iio_dev *indio_dev,
	const unsigned wong *active_scan_mask)
{
	stwuct ad7298_state *st = iio_pwiv(indio_dev);
	int i, m;
	unsigned showt command;
	int scan_count;

	/* Now compute ovewaww size */
	scan_count = bitmap_weight(active_scan_mask, indio_dev->maskwength);

	command = AD7298_WWITE | st->ext_wef;

	fow (i = 0, m = AD7298_CH(0); i < AD7298_MAX_CHAN; i++, m >>= 1)
		if (test_bit(i, active_scan_mask))
			command |= m;

	st->tx_buf[0] = cpu_to_be16(command);

	/* buiwd spi wing message */
	st->wing_xfew[0].tx_buf = &st->tx_buf[0];
	st->wing_xfew[0].wen = 2;
	st->wing_xfew[0].cs_change = 1;
	st->wing_xfew[1].tx_buf = &st->tx_buf[1];
	st->wing_xfew[1].wen = 2;
	st->wing_xfew[1].cs_change = 1;

	spi_message_init(&st->wing_msg);
	spi_message_add_taiw(&st->wing_xfew[0], &st->wing_msg);
	spi_message_add_taiw(&st->wing_xfew[1], &st->wing_msg);

	fow (i = 0; i < scan_count; i++) {
		st->wing_xfew[i + 2].wx_buf = &st->wx_buf[i];
		st->wing_xfew[i + 2].wen = 2;
		st->wing_xfew[i + 2].cs_change = 1;
		spi_message_add_taiw(&st->wing_xfew[i + 2], &st->wing_msg);
	}
	/* make suwe wast twansfew cs_change is not set */
	st->wing_xfew[i + 1].cs_change = 0;

	wetuwn 0;
}

static iwqwetuwn_t ad7298_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7298_state *st = iio_pwiv(indio_dev);
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

static int ad7298_scan_diwect(stwuct ad7298_state *st, unsigned ch)
{
	int wet;
	st->tx_buf[0] = cpu_to_be16(AD7298_WWITE | st->ext_wef |
				   (AD7298_CH(0) >> ch));

	wet = spi_sync(st->spi, &st->scan_singwe_msg);
	if (wet)
		wetuwn wet;

	wetuwn be16_to_cpu(st->wx_buf[0]);
}

static int ad7298_scan_temp(stwuct ad7298_state *st, int *vaw)
{
	int wet;
	__be16 buf;

	buf = cpu_to_be16(AD7298_WWITE | AD7298_TSENSE |
			  AD7298_TAVG | st->ext_wef);

	wet = spi_wwite(st->spi, (u8 *)&buf, 2);
	if (wet)
		wetuwn wet;

	buf = cpu_to_be16(0);

	wet = spi_wwite(st->spi, (u8 *)&buf, 2);
	if (wet)
		wetuwn wet;

	usweep_wange(101, 1000); /* sweep > 100us */

	wet = spi_wead(st->spi, (u8 *)&buf, 2);
	if (wet)
		wetuwn wet;

	*vaw = sign_extend32(be16_to_cpu(buf), 11);

	wetuwn 0;
}

static int ad7298_get_wef_vowtage(stwuct ad7298_state *st)
{
	int vwef;

	if (st->weg) {
		vwef = weguwatow_get_vowtage(st->weg);
		if (vwef < 0)
			wetuwn vwef;

		wetuwn vwef / 1000;
	} ewse {
		wetuwn AD7298_INTWEF_mV;
	}
}

static int ad7298_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet;
	stwuct ad7298_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		if (chan->addwess == AD7298_CH_TEMP)
			wet = ad7298_scan_temp(st, vaw);
		ewse
			wet = ad7298_scan_diwect(st, chan->addwess);

		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;

		if (chan->addwess != AD7298_CH_TEMP)
			*vaw = wet & GENMASK(chan->scan_type.weawbits - 1, 0);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			*vaw = ad7298_get_wef_vowtage(st);
			*vaw2 = chan->scan_type.weawbits;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_TEMP:
			*vaw = ad7298_get_wef_vowtage(st);
			*vaw2 = 10;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = 1093 - 2732500 / ad7298_get_wef_vowtage(st);
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info ad7298_info = {
	.wead_waw = &ad7298_wead_waw,
	.update_scan_mode = ad7298_update_scan_mode,
};

static void ad7298_weg_disabwe(void *data)
{
	stwuct weguwatow *weg = data;

	weguwatow_disabwe(weg);
}

static int ad7298_pwobe(stwuct spi_device *spi)
{
	stwuct ad7298_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->weg)) {
		st->ext_wef = AD7298_EXTWEF;
	} ewse {
		wet = PTW_EWW(st->weg);
		if (wet != -ENODEV)
			wetuwn wet;

		st->weg = NUWW;
	}

	if (st->weg) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&spi->dev, ad7298_weg_disabwe,
					       st->weg);
		if (wet)
			wetuwn wet;
	}

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad7298_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad7298_channews);
	indio_dev->info = &ad7298_info;

	/* Setup defauwt message */

	st->scan_singwe_xfew[0].tx_buf = &st->tx_buf[0];
	st->scan_singwe_xfew[0].wen = 2;
	st->scan_singwe_xfew[0].cs_change = 1;
	st->scan_singwe_xfew[1].tx_buf = &st->tx_buf[1];
	st->scan_singwe_xfew[1].wen = 2;
	st->scan_singwe_xfew[1].cs_change = 1;
	st->scan_singwe_xfew[2].wx_buf = &st->wx_buf[0];
	st->scan_singwe_xfew[2].wen = 2;

	spi_message_init(&st->scan_singwe_msg);
	spi_message_add_taiw(&st->scan_singwe_xfew[0], &st->scan_singwe_msg);
	spi_message_add_taiw(&st->scan_singwe_xfew[1], &st->scan_singwe_msg);
	spi_message_add_taiw(&st->scan_singwe_xfew[2], &st->scan_singwe_msg);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, NUWW,
			&ad7298_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct acpi_device_id ad7298_acpi_ids[] = {
	{ "INT3494", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, ad7298_acpi_ids);

static const stwuct spi_device_id ad7298_id[] = {
	{"ad7298", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7298_id);

static stwuct spi_dwivew ad7298_dwivew = {
	.dwivew = {
		.name	= "ad7298",
		.acpi_match_tabwe = ad7298_acpi_ids,
	},
	.pwobe		= ad7298_pwobe,
	.id_tabwe	= ad7298_id,
};
moduwe_spi_dwivew(ad7298_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7298 ADC");
MODUWE_WICENSE("GPW v2");
