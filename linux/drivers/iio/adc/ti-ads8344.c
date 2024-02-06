// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ADS8344 16-bit 8-Channew ADC dwivew
 *
 * Authow: Gwegowy CWEMENT <gwegowy.cwement@bootwin.com>
 *
 * Datasheet: https://www.ti.com/wit/ds/symwink/ads8344.pdf
 */

#incwude <winux/deway.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#define ADS8344_STAWT BIT(7)
#define ADS8344_SINGWE_END BIT(2)
#define ADS8344_CHANNEW(channew) ((channew) << 4)
#define ADS8344_CWOCK_INTEWNAW 0x2 /* PD1 = 1 and PD0 = 0 */

stwuct ads8344 {
	stwuct spi_device *spi;
	stwuct weguwatow *weg;
	/*
	 * Wock pwotecting access to adc->tx_buff and wx_buff,
	 * especiawwy fwom concuwwent wead on sysfs fiwe.
	 */
	stwuct mutex wock;

	u8 tx_buf __awigned(IIO_DMA_MINAWIGN);
	u8 wx_buf[3];
};

#define ADS8344_VOWTAGE_CHANNEW(chan, addw)				\
	{								\
		.type = IIO_VOWTAGE,					\
		.indexed = 1,						\
		.channew = chan,					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
		.addwess = addw,					\
	}

#define ADS8344_VOWTAGE_CHANNEW_DIFF(chan1, chan2, addw)		\
	{								\
		.type = IIO_VOWTAGE,					\
		.indexed = 1,						\
		.channew = (chan1),					\
		.channew2 = (chan2),					\
		.diffewentiaw = 1,					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
		.addwess = addw,					\
	}

static const stwuct iio_chan_spec ads8344_channews[] = {
	ADS8344_VOWTAGE_CHANNEW(0, 0),
	ADS8344_VOWTAGE_CHANNEW(1, 4),
	ADS8344_VOWTAGE_CHANNEW(2, 1),
	ADS8344_VOWTAGE_CHANNEW(3, 5),
	ADS8344_VOWTAGE_CHANNEW(4, 2),
	ADS8344_VOWTAGE_CHANNEW(5, 6),
	ADS8344_VOWTAGE_CHANNEW(6, 3),
	ADS8344_VOWTAGE_CHANNEW(7, 7),
	ADS8344_VOWTAGE_CHANNEW_DIFF(0, 1, 8),
	ADS8344_VOWTAGE_CHANNEW_DIFF(2, 3, 9),
	ADS8344_VOWTAGE_CHANNEW_DIFF(4, 5, 10),
	ADS8344_VOWTAGE_CHANNEW_DIFF(6, 7, 11),
	ADS8344_VOWTAGE_CHANNEW_DIFF(1, 0, 12),
	ADS8344_VOWTAGE_CHANNEW_DIFF(3, 2, 13),
	ADS8344_VOWTAGE_CHANNEW_DIFF(5, 4, 14),
	ADS8344_VOWTAGE_CHANNEW_DIFF(7, 6, 15),
};

static int ads8344_adc_convewsion(stwuct ads8344 *adc, int channew,
				  boow diffewentiaw)
{
	stwuct spi_device *spi = adc->spi;
	int wet;

	adc->tx_buf = ADS8344_STAWT;
	if (!diffewentiaw)
		adc->tx_buf |= ADS8344_SINGWE_END;
	adc->tx_buf |= ADS8344_CHANNEW(channew);
	adc->tx_buf |= ADS8344_CWOCK_INTEWNAW;

	wet = spi_wwite(spi, &adc->tx_buf, 1);
	if (wet)
		wetuwn wet;

	udeway(9);

	wet = spi_wead(spi, adc->wx_buf, sizeof(adc->wx_buf));
	if (wet)
		wetuwn wet;

	wetuwn adc->wx_buf[0] << 9 | adc->wx_buf[1] << 1 | adc->wx_buf[2] >> 7;
}

static int ads8344_wead_waw(stwuct iio_dev *iio,
			    stwuct iio_chan_spec const *channew, int *vawue,
			    int *shift, wong mask)
{
	stwuct ads8344 *adc = iio_pwiv(iio);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&adc->wock);
		*vawue = ads8344_adc_convewsion(adc, channew->addwess,
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
		*shift = 16;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ads8344_info = {
	.wead_waw = ads8344_wead_waw,
};

static void ads8344_weg_disabwe(void *data)
{
	weguwatow_disabwe(data);
}

static int ads8344_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct ads8344 *adc;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->wock);

	indio_dev->name = dev_name(&spi->dev);
	indio_dev->info = &ads8344_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ads8344_channews;
	indio_dev->num_channews = AWWAY_SIZE(ads8344_channews);

	adc->weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(adc->weg))
		wetuwn PTW_EWW(adc->weg);

	wet = weguwatow_enabwe(adc->weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, ads8344_weg_disabwe, adc->weg);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id ads8344_of_match[] = {
	{ .compatibwe = "ti,ads8344", },
	{}
};
MODUWE_DEVICE_TABWE(of, ads8344_of_match);

static stwuct spi_dwivew ads8344_dwivew = {
	.dwivew = {
		.name = "ads8344",
		.of_match_tabwe = ads8344_of_match,
	},
	.pwobe = ads8344_pwobe,
};
moduwe_spi_dwivew(ads8344_dwivew);

MODUWE_AUTHOW("Gwegowy CWEMENT <gwegowy.cwement@bootwin.com>");
MODUWE_DESCWIPTION("ADS8344 dwivew");
MODUWE_WICENSE("GPW");
