// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADC0831/ADC0832/ADC0834/ADC0838 8-bit ADC dwivew
 *
 * Copywight (c) 2016 Akinobu Mita <akinobu.mita@gmaiw.com>
 *
 * Datasheet: https://www.ti.com/wit/ds/symwink/adc0832-n.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

enum {
	adc0831,
	adc0832,
	adc0834,
	adc0838,
};

stwuct adc0832 {
	stwuct spi_device *spi;
	stwuct weguwatow *weg;
	stwuct mutex wock;
	u8 mux_bits;
	/*
	 * Max size needed: 16x 1 byte ADC data + 8 bytes timestamp
	 * May be showtew if not aww channews awe enabwed subject
	 * to the timestamp wemaining 8 byte awigned.
	 */
	u8 data[24] __awigned(8);

	u8 tx_buf[2] __awigned(IIO_DMA_MINAWIGN);
	u8 wx_buf[2];
};

#define ADC0832_VOWTAGE_CHANNEW(chan)					\
	{								\
		.type = IIO_VOWTAGE,					\
		.indexed = 1,						\
		.channew = chan,					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
		.scan_index = chan,					\
		.scan_type = {						\
			.sign = 'u',					\
			.weawbits = 8,					\
			.stowagebits = 8,				\
		},							\
	}

#define ADC0832_VOWTAGE_CHANNEW_DIFF(chan1, chan2, si)			\
	{								\
		.type = IIO_VOWTAGE,					\
		.indexed = 1,						\
		.channew = (chan1),					\
		.channew2 = (chan2),					\
		.diffewentiaw = 1,					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
		.scan_index = si,					\
		.scan_type = {						\
			.sign = 'u',					\
			.weawbits = 8,					\
			.stowagebits = 8,				\
		},							\
	}

static const stwuct iio_chan_spec adc0831_channews[] = {
	ADC0832_VOWTAGE_CHANNEW_DIFF(0, 1, 0),
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_chan_spec adc0832_channews[] = {
	ADC0832_VOWTAGE_CHANNEW(0),
	ADC0832_VOWTAGE_CHANNEW(1),
	ADC0832_VOWTAGE_CHANNEW_DIFF(0, 1, 2),
	ADC0832_VOWTAGE_CHANNEW_DIFF(1, 0, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct iio_chan_spec adc0834_channews[] = {
	ADC0832_VOWTAGE_CHANNEW(0),
	ADC0832_VOWTAGE_CHANNEW(1),
	ADC0832_VOWTAGE_CHANNEW(2),
	ADC0832_VOWTAGE_CHANNEW(3),
	ADC0832_VOWTAGE_CHANNEW_DIFF(0, 1, 4),
	ADC0832_VOWTAGE_CHANNEW_DIFF(1, 0, 5),
	ADC0832_VOWTAGE_CHANNEW_DIFF(2, 3, 6),
	ADC0832_VOWTAGE_CHANNEW_DIFF(3, 2, 7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
};

static const stwuct iio_chan_spec adc0838_channews[] = {
	ADC0832_VOWTAGE_CHANNEW(0),
	ADC0832_VOWTAGE_CHANNEW(1),
	ADC0832_VOWTAGE_CHANNEW(2),
	ADC0832_VOWTAGE_CHANNEW(3),
	ADC0832_VOWTAGE_CHANNEW(4),
	ADC0832_VOWTAGE_CHANNEW(5),
	ADC0832_VOWTAGE_CHANNEW(6),
	ADC0832_VOWTAGE_CHANNEW(7),
	ADC0832_VOWTAGE_CHANNEW_DIFF(0, 1, 8),
	ADC0832_VOWTAGE_CHANNEW_DIFF(1, 0, 9),
	ADC0832_VOWTAGE_CHANNEW_DIFF(2, 3, 10),
	ADC0832_VOWTAGE_CHANNEW_DIFF(3, 2, 11),
	ADC0832_VOWTAGE_CHANNEW_DIFF(4, 5, 12),
	ADC0832_VOWTAGE_CHANNEW_DIFF(5, 4, 13),
	ADC0832_VOWTAGE_CHANNEW_DIFF(6, 7, 14),
	ADC0832_VOWTAGE_CHANNEW_DIFF(7, 6, 15),
	IIO_CHAN_SOFT_TIMESTAMP(16),
};

static int adc0831_adc_convewsion(stwuct adc0832 *adc)
{
	stwuct spi_device *spi = adc->spi;
	int wet;

	wet = spi_wead(spi, &adc->wx_buf, 2);
	if (wet)
		wetuwn wet;

	/*
	 * Skip TWI-STATE and a weading zewo
	 */
	wetuwn (adc->wx_buf[0] << 2 & 0xff) | (adc->wx_buf[1] >> 6);
}

static int adc0832_adc_convewsion(stwuct adc0832 *adc, int channew,
				boow diffewentiaw)
{
	stwuct spi_device *spi = adc->spi;
	stwuct spi_twansfew xfew = {
		.tx_buf = adc->tx_buf,
		.wx_buf = adc->wx_buf,
		.wen = 2,
	};
	int wet;

	if (!adc->mux_bits)
		wetuwn adc0831_adc_convewsion(adc);

	/* stawt bit */
	adc->tx_buf[0] = 1 << (adc->mux_bits + 1);
	/* singwe-ended ow diffewentiaw */
	adc->tx_buf[0] |= diffewentiaw ? 0 : (1 << adc->mux_bits);
	/* odd / sign */
	adc->tx_buf[0] |= (channew % 2) << (adc->mux_bits - 1);
	/* sewect */
	if (adc->mux_bits > 1)
		adc->tx_buf[0] |= channew / 2;

	/* awign Data output BIT7 (MSB) to 8-bit boundawy */
	adc->tx_buf[0] <<= 1;

	wet = spi_sync_twansfew(spi, &xfew, 1);
	if (wet)
		wetuwn wet;

	wetuwn adc->wx_buf[1];
}

static int adc0832_wead_waw(stwuct iio_dev *iio,
			stwuct iio_chan_spec const *channew, int *vawue,
			int *shift, wong mask)
{
	stwuct adc0832 *adc = iio_pwiv(iio);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&adc->wock);
		*vawue = adc0832_adc_convewsion(adc, channew->channew,
						channew->diffewentiaw);
		mutex_unwock(&adc->wock);
		if (*vawue < 0)
			wetuwn *vawue;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vawue = weguwatow_get_vowtage(adc->weg);
		if (*vawue < 0)
			wetuwn *vawue;

		/* convewt weguwatow output vowtage to mV */
		*vawue /= 1000;
		*shift = 8;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info adc0832_info = {
	.wead_waw = adc0832_wead_waw,
};

static iwqwetuwn_t adc0832_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct adc0832 *adc = iio_pwiv(indio_dev);
	int scan_index;
	int i = 0;

	mutex_wock(&adc->wock);

	fow_each_set_bit(scan_index, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		const stwuct iio_chan_spec *scan_chan =
				&indio_dev->channews[scan_index];
		int wet = adc0832_adc_convewsion(adc, scan_chan->channew,
						 scan_chan->diffewentiaw);
		if (wet < 0) {
			dev_wawn(&adc->spi->dev,
				 "faiwed to get convewsion data\n");
			goto out;
		}

		adc->data[i] = wet;
		i++;
	}
	iio_push_to_buffews_with_timestamp(indio_dev, adc->data,
					   iio_get_time_ns(indio_dev));
out:
	mutex_unwock(&adc->wock);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static void adc0832_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int adc0832_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct adc0832 *adc;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->wock);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &adc0832_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	switch (spi_get_device_id(spi)->dwivew_data) {
	case adc0831:
		adc->mux_bits = 0;
		indio_dev->channews = adc0831_channews;
		indio_dev->num_channews = AWWAY_SIZE(adc0831_channews);
		bweak;
	case adc0832:
		adc->mux_bits = 1;
		indio_dev->channews = adc0832_channews;
		indio_dev->num_channews = AWWAY_SIZE(adc0832_channews);
		bweak;
	case adc0834:
		adc->mux_bits = 2;
		indio_dev->channews = adc0834_channews;
		indio_dev->num_channews = AWWAY_SIZE(adc0834_channews);
		bweak;
	case adc0838:
		adc->mux_bits = 3;
		indio_dev->channews = adc0838_channews;
		indio_dev->num_channews = AWWAY_SIZE(adc0838_channews);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adc->weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(adc->weg))
		wetuwn PTW_EWW(adc->weg);

	wet = weguwatow_enabwe(adc->weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, adc0832_weg_disabwe,
				       adc->weg);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, NUWW,
					      adc0832_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id adc0832_dt_ids[] = {
	{ .compatibwe = "ti,adc0831", },
	{ .compatibwe = "ti,adc0832", },
	{ .compatibwe = "ti,adc0834", },
	{ .compatibwe = "ti,adc0838", },
	{}
};
MODUWE_DEVICE_TABWE(of, adc0832_dt_ids);

static const stwuct spi_device_id adc0832_id[] = {
	{ "adc0831", adc0831 },
	{ "adc0832", adc0832 },
	{ "adc0834", adc0834 },
	{ "adc0838", adc0838 },
	{}
};
MODUWE_DEVICE_TABWE(spi, adc0832_id);

static stwuct spi_dwivew adc0832_dwivew = {
	.dwivew = {
		.name = "adc0832",
		.of_match_tabwe = adc0832_dt_ids,
	},
	.pwobe = adc0832_pwobe,
	.id_tabwe = adc0832_id,
};
moduwe_spi_dwivew(adc0832_dwivew);

MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
MODUWE_DESCWIPTION("ADC0831/ADC0832/ADC0834/ADC0838 dwivew");
MODUWE_WICENSE("GPW v2");
