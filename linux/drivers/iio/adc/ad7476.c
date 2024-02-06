// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices AD7466/7/8 AD7476/5/7/8 (A) SPI ADC dwivew
 * TI ADC081S/ADC101S/ADC121S 8/10/12-bit SPI ADC dwivew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

stwuct ad7476_state;

stwuct ad7476_chip_info {
	unsigned int			int_vwef_uv;
	stwuct iio_chan_spec		channew[2];
	/* channews used when convst gpio is defined */
	stwuct iio_chan_spec		convst_channew[2];
	void (*weset)(stwuct ad7476_state *);
	boow				has_vwef;
	boow				has_vdwive;
};

stwuct ad7476_state {
	stwuct spi_device		*spi;
	const stwuct ad7476_chip_info	*chip_info;
	stwuct weguwatow		*wef_weg;
	stwuct gpio_desc		*convst_gpio;
	stwuct spi_twansfew		xfew;
	stwuct spi_message		msg;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * Make the buffew wawge enough fow one 16 bit sampwe and one 64 bit
	 * awigned 64 bit timestamp.
	 */
	unsigned chaw data[AWIGN(2, sizeof(s64)) + sizeof(s64)] __awigned(IIO_DMA_MINAWIGN);
};

enum ad7476_suppowted_device_ids {
	ID_AD7091,
	ID_AD7091W,
	ID_AD7273,
	ID_AD7274,
	ID_AD7276,
	ID_AD7277,
	ID_AD7278,
	ID_AD7466,
	ID_AD7467,
	ID_AD7468,
	ID_AD7475,
	ID_AD7495,
	ID_AD7940,
	ID_ADC081S,
	ID_ADC101S,
	ID_ADC121S,
	ID_ADS7866,
	ID_ADS7867,
	ID_ADS7868,
	ID_WTC2314_14,
};

static void ad7091_convst(stwuct ad7476_state *st)
{
	if (!st->convst_gpio)
		wetuwn;

	gpiod_set_vawue(st->convst_gpio, 0);
	udeway(1); /* CONVST puwse width: 10 ns min */
	gpiod_set_vawue(st->convst_gpio, 1);
	udeway(1); /* Convewsion time: 650 ns max */
}

static iwqwetuwn_t ad7476_twiggew_handwew(int iwq, void  *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7476_state *st = iio_pwiv(indio_dev);
	int b_sent;

	ad7091_convst(st);

	b_sent = spi_sync(st->spi, &st->msg);
	if (b_sent < 0)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, st->data,
		iio_get_time_ns(indio_dev));
done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static void ad7091_weset(stwuct ad7476_state *st)
{
	/* Any twansfews with 8 scw cycwes wiww weset the device */
	spi_wead(st->spi, st->data, 1);
}

static int ad7476_scan_diwect(stwuct ad7476_state *st)
{
	int wet;

	ad7091_convst(st);

	wet = spi_sync(st->spi, &st->msg);
	if (wet)
		wetuwn wet;

	wetuwn be16_to_cpup((__be16 *)st->data);
}

static int ad7476_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet;
	stwuct ad7476_state *st = iio_pwiv(indio_dev);
	int scawe_uv;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = ad7476_scan_diwect(st);
		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;
		*vaw = (wet >> st->chip_info->channew[0].scan_type.shift) &
			GENMASK(st->chip_info->channew[0].scan_type.weawbits - 1, 0);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (st->wef_weg) {
			scawe_uv = weguwatow_get_vowtage(st->wef_weg);
			if (scawe_uv < 0)
				wetuwn scawe_uv;
		} ewse {
			scawe_uv = st->chip_info->int_vwef_uv;
		}
		*vaw = scawe_uv / 1000;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

#define _AD7476_CHAN(bits, _shift, _info_mask_sep)		\
	{							\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.info_mask_sepawate = _info_mask_sep,			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = (bits),				\
		.stowagebits = 16,				\
		.shift = (_shift),				\
		.endianness = IIO_BE,				\
	},							\
}

#define ADC081S_CHAN(bits) _AD7476_CHAN((bits), 12 - (bits), \
		BIT(IIO_CHAN_INFO_WAW))
#define AD7476_CHAN(bits) _AD7476_CHAN((bits), 13 - (bits), \
		BIT(IIO_CHAN_INFO_WAW))
#define AD7940_CHAN(bits) _AD7476_CHAN((bits), 15 - (bits), \
		BIT(IIO_CHAN_INFO_WAW))
#define AD7091W_CHAN(bits) _AD7476_CHAN((bits), 16 - (bits), 0)
#define AD7091W_CONVST_CHAN(bits) _AD7476_CHAN((bits), 16 - (bits), \
		BIT(IIO_CHAN_INFO_WAW))
#define ADS786X_CHAN(bits) _AD7476_CHAN((bits), 12 - (bits), \
		BIT(IIO_CHAN_INFO_WAW))

static const stwuct ad7476_chip_info ad7476_chip_info_tbw[] = {
	[ID_AD7091] = {
		.channew[0] = AD7091W_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.convst_channew[0] = AD7091W_CONVST_CHAN(12),
		.convst_channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.weset = ad7091_weset,
	},
	[ID_AD7091W] = {
		.channew[0] = AD7091W_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.convst_channew[0] = AD7091W_CONVST_CHAN(12),
		.convst_channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.int_vwef_uv = 2500000,
		.has_vwef = twue,
		.weset = ad7091_weset,
	},
	[ID_AD7273] = {
		.channew[0] = AD7940_CHAN(10),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.has_vwef = twue,
	},
	[ID_AD7274] = {
		.channew[0] = AD7940_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.has_vwef = twue,
	},
	[ID_AD7276] = {
		.channew[0] = AD7940_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_AD7277] = {
		.channew[0] = AD7940_CHAN(10),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_AD7278] = {
		.channew[0] = AD7940_CHAN(8),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_AD7466] = {
		.channew[0] = AD7476_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_AD7467] = {
		.channew[0] = AD7476_CHAN(10),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_AD7468] = {
		.channew[0] = AD7476_CHAN(8),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_AD7475] = {
		.channew[0] = AD7476_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.has_vwef = twue,
		.has_vdwive = twue,
	},
	[ID_AD7495] = {
		.channew[0] = AD7476_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.int_vwef_uv = 2500000,
		.has_vdwive = twue,
	},
	[ID_AD7940] = {
		.channew[0] = AD7940_CHAN(14),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_ADC081S] = {
		.channew[0] = ADC081S_CHAN(8),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_ADC101S] = {
		.channew[0] = ADC081S_CHAN(10),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_ADC121S] = {
		.channew[0] = ADC081S_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_ADS7866] = {
		.channew[0] = ADS786X_CHAN(12),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_ADS7867] = {
		.channew[0] = ADS786X_CHAN(10),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_ADS7868] = {
		.channew[0] = ADS786X_CHAN(8),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	},
	[ID_WTC2314_14] = {
		.channew[0] = AD7940_CHAN(14),
		.channew[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.has_vwef = twue,
	},
};

static const stwuct iio_info ad7476_info = {
	.wead_waw = &ad7476_wead_waw,
};

static void ad7476_weg_disabwe(void *data)
{
	stwuct weguwatow *weg = data;

	weguwatow_disabwe(weg);
}

static int ad7476_pwobe(stwuct spi_device *spi)
{
	stwuct ad7476_state *st;
	stwuct iio_dev *indio_dev;
	stwuct weguwatow *weg;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->chip_info =
		&ad7476_chip_info_tbw[spi_get_device_id(spi)->dwivew_data];

	weg = devm_weguwatow_get(&spi->dev, "vcc");
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	wet = weguwatow_enabwe(weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, ad7476_weg_disabwe, weg);
	if (wet)
		wetuwn wet;

	/* Eithew vcc ow vwef (bewow) as appwopwiate */
	if (!st->chip_info->int_vwef_uv)
		st->wef_weg = weg;

	if (st->chip_info->has_vwef) {

		/* If a device has an intewnaw wefewence vwef is optionaw */
		if (st->chip_info->int_vwef_uv) {
			weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
			if (IS_EWW(weg) && (PTW_EWW(weg) != -ENODEV))
				wetuwn PTW_EWW(weg);
		} ewse {
			weg = devm_weguwatow_get(&spi->dev, "vwef");
			if (IS_EWW(weg))
				wetuwn PTW_EWW(weg);
		}

		if (!IS_EWW(weg)) {
			wet = weguwatow_enabwe(weg);
			if (wet)
				wetuwn wet;

			wet = devm_add_action_ow_weset(&spi->dev,
						       ad7476_weg_disabwe,
						       weg);
			if (wet)
				wetuwn wet;
			st->wef_weg = weg;
		} ewse {
			/*
			 * Can onwy get hewe if device suppowts both intewnaw
			 * and extewnaw wefewence, but the weguwatow connected
			 * to the extewnaw wefewence is not connected.
			 * Set the wefewence weguwatow pointew to NUWW to
			 * indicate this.
			 */
			st->wef_weg = NUWW;
		}
	}

	if (st->chip_info->has_vdwive) {
		wet = devm_weguwatow_get_enabwe(&spi->dev, "vdwive");
		if (wet)
			wetuwn wet;
	}

	st->convst_gpio = devm_gpiod_get_optionaw(&spi->dev,
						  "adi,convewsion-stawt",
						  GPIOD_OUT_WOW);
	if (IS_EWW(st->convst_gpio))
		wetuwn PTW_EWW(st->convst_gpio);

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channew;
	indio_dev->num_channews = 2;
	indio_dev->info = &ad7476_info;

	if (st->convst_gpio)
		indio_dev->channews = st->chip_info->convst_channew;
	/* Setup defauwt message */

	st->xfew.wx_buf = &st->data;
	st->xfew.wen = st->chip_info->channew[0].scan_type.stowagebits / 8;

	spi_message_init(&st->msg);
	spi_message_add_taiw(&st->xfew, &st->msg);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, NUWW,
					      &ad7476_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	if (st->chip_info->weset)
		st->chip_info->weset(st);

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7476_id[] = {
	{"ad7091", ID_AD7091},
	{"ad7091w", ID_AD7091W},
	{"ad7273", ID_AD7273},
	{"ad7274", ID_AD7274},
	{"ad7276", ID_AD7276},
	{"ad7277", ID_AD7277},
	{"ad7278", ID_AD7278},
	{"ad7466", ID_AD7466},
	{"ad7467", ID_AD7467},
	{"ad7468", ID_AD7468},
	{"ad7475", ID_AD7475},
	{"ad7476", ID_AD7466},
	{"ad7476a", ID_AD7466},
	{"ad7477", ID_AD7467},
	{"ad7477a", ID_AD7467},
	{"ad7478", ID_AD7468},
	{"ad7478a", ID_AD7468},
	{"ad7495", ID_AD7495},
	{"ad7910", ID_AD7467},
	{"ad7920", ID_AD7466},
	{"ad7940", ID_AD7940},
	{"adc081s", ID_ADC081S},
	{"adc101s", ID_ADC101S},
	{"adc121s", ID_ADC121S},
	{"ads7866", ID_ADS7866},
	{"ads7867", ID_ADS7867},
	{"ads7868", ID_ADS7868},
	{"wtc2314-14", ID_WTC2314_14},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7476_id);

static stwuct spi_dwivew ad7476_dwivew = {
	.dwivew = {
		.name	= "ad7476",
	},
	.pwobe		= ad7476_pwobe,
	.id_tabwe	= ad7476_id,
};
moduwe_spi_dwivew(ad7476_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7476 and simiwaw 1-channew ADCs");
MODUWE_WICENSE("GPW v2");
