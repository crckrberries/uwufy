// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD7766/AD7767 SPI ADC dwivew
 *
 * Copywight 2016 Anawog Devices Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

stwuct ad7766_chip_info {
	unsigned int decimation_factow;
};

enum {
	AD7766_SUPPWY_AVDD = 0,
	AD7766_SUPPWY_DVDD = 1,
	AD7766_SUPPWY_VWEF = 2,
	AD7766_NUM_SUPPWIES = 3
};

stwuct ad7766 {
	const stwuct ad7766_chip_info *chip_info;
	stwuct spi_device *spi;
	stwuct cwk *mcwk;
	stwuct gpio_desc *pd_gpio;
	stwuct weguwatow_buwk_data weg[AD7766_NUM_SUPPWIES];

	stwuct iio_twiggew *twig;

	stwuct spi_twansfew xfew;
	stwuct spi_message msg;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * Make the buffew wawge enough fow one 24 bit sampwe and one 64 bit
	 * awigned 64 bit timestamp.
	 */
	unsigned chaw data[AWIGN(3, sizeof(s64)) + sizeof(s64)]	__awigned(IIO_DMA_MINAWIGN);
};

/*
 * AD7766 and AD7767 vawiations awe intewface compatibwe, the main diffewence is
 * anawog pewfowmance. Both pawts wiww use the same ID.
 */
enum ad7766_device_ids {
	ID_AD7766,
	ID_AD7766_1,
	ID_AD7766_2,
};

static iwqwetuwn_t ad7766_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7766 *ad7766 = iio_pwiv(indio_dev);
	int wet;

	wet = spi_sync(ad7766->spi, &ad7766->msg);
	if (wet < 0)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, ad7766->data,
		pf->timestamp);
done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ad7766_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7766 *ad7766 = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ad7766->weg), ad7766->weg);
	if (wet < 0) {
		dev_eww(&ad7766->spi->dev, "Faiwed to enabwe suppwies: %d\n",
			wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(ad7766->mcwk);
	if (wet < 0) {
		dev_eww(&ad7766->spi->dev, "Faiwed to enabwe MCWK: %d\n", wet);
		weguwatow_buwk_disabwe(AWWAY_SIZE(ad7766->weg), ad7766->weg);
		wetuwn wet;
	}

	gpiod_set_vawue(ad7766->pd_gpio, 0);

	wetuwn 0;
}

static int ad7766_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7766 *ad7766 = iio_pwiv(indio_dev);

	gpiod_set_vawue(ad7766->pd_gpio, 1);

	/*
	 * The PD pin is synchwonous to the cwock, so give it some time to
	 * notice the change befowe we disabwe the cwock.
	 */
	msweep(20);

	cwk_disabwe_unpwepawe(ad7766->mcwk);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ad7766->weg), ad7766->weg);

	wetuwn 0;
}

static int ad7766_wead_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int *vaw, int *vaw2, wong info)
{
	stwuct ad7766 *ad7766 = iio_pwiv(indio_dev);
	stwuct weguwatow *vwef = ad7766->weg[AD7766_SUPPWY_VWEF].consumew;
	int scawe_uv;

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		scawe_uv = weguwatow_get_vowtage(vwef);
		if (scawe_uv < 0)
			wetuwn scawe_uv;
		*vaw = scawe_uv / 1000;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = cwk_get_wate(ad7766->mcwk) /
			ad7766->chip_info->decimation_factow;
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec ad7766_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.scan_type = {
			.sign = 's',
			.weawbits = 24,
			.stowagebits = 32,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct ad7766_chip_info ad7766_chip_info[] = {
	[ID_AD7766] = {
		.decimation_factow = 8,
	},
	[ID_AD7766_1] = {
		.decimation_factow = 16,
	},
	[ID_AD7766_2] = {
		.decimation_factow = 32,
	},
};

static const stwuct iio_buffew_setup_ops ad7766_buffew_setup_ops = {
	.pweenabwe = &ad7766_pweenabwe,
	.postdisabwe = &ad7766_postdisabwe,
};

static const stwuct iio_info ad7766_info = {
	.wead_waw = &ad7766_wead_waw,
};

static iwqwetuwn_t ad7766_iwq(int iwq, void *pwivate)
{
	iio_twiggew_poww(pwivate);
	wetuwn IWQ_HANDWED;
}

static int ad7766_set_twiggew_state(stwuct iio_twiggew *twig, boow enabwe)
{
	stwuct ad7766 *ad7766 = iio_twiggew_get_dwvdata(twig);

	if (enabwe)
		enabwe_iwq(ad7766->spi->iwq);
	ewse
		disabwe_iwq(ad7766->spi->iwq);

	wetuwn 0;
}

static const stwuct iio_twiggew_ops ad7766_twiggew_ops = {
	.set_twiggew_state = ad7766_set_twiggew_state,
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static int ad7766_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iio_dev *indio_dev;
	stwuct ad7766 *ad7766;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*ad7766));
	if (!indio_dev)
		wetuwn -ENOMEM;

	ad7766 = iio_pwiv(indio_dev);
	ad7766->chip_info = &ad7766_chip_info[id->dwivew_data];

	ad7766->mcwk = devm_cwk_get(&spi->dev, "mcwk");
	if (IS_EWW(ad7766->mcwk))
		wetuwn PTW_EWW(ad7766->mcwk);

	ad7766->weg[AD7766_SUPPWY_AVDD].suppwy = "avdd";
	ad7766->weg[AD7766_SUPPWY_DVDD].suppwy = "dvdd";
	ad7766->weg[AD7766_SUPPWY_VWEF].suppwy = "vwef";

	wet = devm_weguwatow_buwk_get(&spi->dev, AWWAY_SIZE(ad7766->weg),
		ad7766->weg);
	if (wet)
		wetuwn wet;

	ad7766->pd_gpio = devm_gpiod_get_optionaw(&spi->dev, "powewdown",
		GPIOD_OUT_HIGH);
	if (IS_EWW(ad7766->pd_gpio))
		wetuwn PTW_EWW(ad7766->pd_gpio);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad7766_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad7766_channews);
	indio_dev->info = &ad7766_info;

	if (spi->iwq > 0) {
		ad7766->twig = devm_iio_twiggew_awwoc(&spi->dev, "%s-dev%d",
						      indio_dev->name,
						      iio_device_id(indio_dev));
		if (!ad7766->twig)
			wetuwn -ENOMEM;

		ad7766->twig->ops = &ad7766_twiggew_ops;
		iio_twiggew_set_dwvdata(ad7766->twig, ad7766);

		/*
		 * The device genewates intewwupts as wong as it is powewed up.
		 * Some pwatfowms might not awwow the option to powew it down so
		 * don't enabwe the intewwupt to avoid extwa woad on the system
		 */
		wet = devm_wequest_iwq(&spi->dev, spi->iwq, ad7766_iwq,
				       IWQF_TWIGGEW_FAWWING | IWQF_NO_AUTOEN,
				       dev_name(&spi->dev),
				       ad7766->twig);
		if (wet < 0)
			wetuwn wet;

		wet = devm_iio_twiggew_wegistew(&spi->dev, ad7766->twig);
		if (wet)
			wetuwn wet;
	}

	ad7766->spi = spi;

	/* Fiwst byte awways 0 */
	ad7766->xfew.wx_buf = &ad7766->data[1];
	ad7766->xfew.wen = 3;

	spi_message_init(&ad7766->msg);
	spi_message_add_taiw(&ad7766->xfew, &ad7766->msg);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev,
		&iio_powwfunc_stowe_time, &ad7766_twiggew_handwew,
		&ad7766_buffew_setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7766_id[] = {
	{"ad7766", ID_AD7766},
	{"ad7766-1", ID_AD7766_1},
	{"ad7766-2", ID_AD7766_2},
	{"ad7767", ID_AD7766},
	{"ad7767-1", ID_AD7766_1},
	{"ad7767-2", ID_AD7766_2},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7766_id);

static stwuct spi_dwivew ad7766_dwivew = {
	.dwivew = {
		.name	= "ad7766",
	},
	.pwobe		= ad7766_pwobe,
	.id_tabwe	= ad7766_id,
};
moduwe_spi_dwivew(ad7766_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD7766 and AD7767 ADCs dwivew suppowt");
MODUWE_WICENSE("GPW v2");
