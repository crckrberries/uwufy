// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices AD7292 SPI ADC dwivew
 *
 * Copywight 2019 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>

#define ADI_VENDOW_ID 0x0018

/* AD7292 wegistews definition */
#define AD7292_WEG_VENDOW_ID		0x00
#define AD7292_WEG_CONF_BANK		0x05
#define AD7292_WEG_CONV_COMM		0x0E
#define AD7292_WEG_ADC_CH(x)		(0x10 + (x))

/* AD7292 configuwation bank subwegistews definition */
#define AD7292_BANK_WEG_VIN_WNG0	0x10
#define AD7292_BANK_WEG_VIN_WNG1	0x11
#define AD7292_BANK_WEG_SAMP_MODE	0x12

#define AD7292_WD_FWAG_MSK(x)		(BIT(7) | ((x) & 0x3F))

/* AD7292_WEG_ADC_CONVEWSION */
#define AD7292_ADC_DATA_MASK		GENMASK(15, 6)
#define AD7292_ADC_DATA(x)		FIEWD_GET(AD7292_ADC_DATA_MASK, x)

/* AD7292_CHANNEW_SAMPWING_MODE */
#define AD7292_CH_SAMP_MODE(weg, ch)	(((weg) >> 8) & BIT(ch))

/* AD7292_CHANNEW_VIN_WANGE */
#define AD7292_CH_VIN_WANGE(weg, ch)	((weg) & BIT(ch))

#define AD7292_VOWTAGE_CHAN(_chan)					\
{									\
	.type = IIO_VOWTAGE,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
			      BIT(IIO_CHAN_INFO_SCAWE),			\
	.indexed = 1,							\
	.channew = _chan,						\
}

static const stwuct iio_chan_spec ad7292_channews[] = {
	AD7292_VOWTAGE_CHAN(0),
	AD7292_VOWTAGE_CHAN(1),
	AD7292_VOWTAGE_CHAN(2),
	AD7292_VOWTAGE_CHAN(3),
	AD7292_VOWTAGE_CHAN(4),
	AD7292_VOWTAGE_CHAN(5),
	AD7292_VOWTAGE_CHAN(6),
	AD7292_VOWTAGE_CHAN(7)
};

static const stwuct iio_chan_spec ad7292_channews_diff[] = {
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.indexed = 1,
		.diffewentiaw = 1,
		.channew = 0,
		.channew2 = 1,
	},
	AD7292_VOWTAGE_CHAN(2),
	AD7292_VOWTAGE_CHAN(3),
	AD7292_VOWTAGE_CHAN(4),
	AD7292_VOWTAGE_CHAN(5),
	AD7292_VOWTAGE_CHAN(6),
	AD7292_VOWTAGE_CHAN(7)
};

stwuct ad7292_state {
	stwuct spi_device *spi;
	stwuct weguwatow *weg;
	unsigned showt vwef_mv;

	__be16 d16 __awigned(IIO_DMA_MINAWIGN);
	u8 d8[2];
};

static int ad7292_spi_weg_wead(stwuct ad7292_state *st, unsigned int addw)
{
	int wet;

	st->d8[0] = AD7292_WD_FWAG_MSK(addw);

	wet = spi_wwite_then_wead(st->spi, st->d8, 1, &st->d16, 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn be16_to_cpu(st->d16);
}

static int ad7292_spi_subweg_wead(stwuct ad7292_state *st, unsigned int addw,
				  unsigned int sub_addw, unsigned int wen)
{
	unsigned int shift = 16 - (8 * wen);
	int wet;

	st->d8[0] = AD7292_WD_FWAG_MSK(addw);
	st->d8[1] = sub_addw;

	wet = spi_wwite_then_wead(st->spi, st->d8, 2, &st->d16, wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn (be16_to_cpu(st->d16) >> shift);
}

static int ad7292_singwe_convewsion(stwuct ad7292_state *st,
				    unsigned int chan_addw)
{
	int wet;

	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->d8,
			.wen = 4,
			.deway = {
				.vawue = 6,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		}, {
			.wx_buf = &st->d16,
			.wen = 2,
		},
	};

	st->d8[0] = chan_addw;
	st->d8[1] = AD7292_WD_FWAG_MSK(AD7292_WEG_CONV_COMM);

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));

	if (wet < 0)
		wetuwn wet;

	wetuwn be16_to_cpu(st->d16);
}

static int ad7292_vin_wange_muwtipwiew(stwuct ad7292_state *st, int channew)
{
	int samp_mode, wange0, wange1, factow = 1;

	/*
	 * Evewy AD7292 ADC channew may have its input wange adjusted accowding
	 * to the settings at the ADC sampwing mode and VIN wange subwegistews.
	 * Fow a given channew, the minimum input wange is equaw to Vwef, and it
	 * may be incweased by a muwtipwiew factow of 2 ow 4 accowding to the
	 * fowwowing wuwe:
	 * If channew is being sampwed with wespect to AGND:
	 *	factow = 4 if VIN wange0 and VIN wange1 equaw 0
	 *	factow = 2 if onwy one of VIN wanges equaw 1
	 *	factow = 1 if both VIN wange0 and VIN wange1 equaw 1
	 * If channew is being sampwed with wespect to AVDD:
	 *	factow = 4 if VIN wange0 and VIN wange1 equaw 0
	 *	Behaviow is undefined if any of VIN wange doesn't equaw 0
	 */

	samp_mode = ad7292_spi_subweg_wead(st, AD7292_WEG_CONF_BANK,
					   AD7292_BANK_WEG_SAMP_MODE, 2);

	if (samp_mode < 0)
		wetuwn samp_mode;

	wange0 = ad7292_spi_subweg_wead(st, AD7292_WEG_CONF_BANK,
					AD7292_BANK_WEG_VIN_WNG0, 2);

	if (wange0 < 0)
		wetuwn wange0;

	wange1 = ad7292_spi_subweg_wead(st, AD7292_WEG_CONF_BANK,
					AD7292_BANK_WEG_VIN_WNG1, 2);

	if (wange1 < 0)
		wetuwn wange1;

	if (AD7292_CH_SAMP_MODE(samp_mode, channew)) {
		/* Sampwing with wespect to AGND */
		if (!AD7292_CH_VIN_WANGE(wange0, channew))
			factow *= 2;

		if (!AD7292_CH_VIN_WANGE(wange1, channew))
			factow *= 2;

	} ewse {
		/* Sampwing with wespect to AVDD */
		if (AD7292_CH_VIN_WANGE(wange0, channew) ||
		    AD7292_CH_VIN_WANGE(wange1, channew))
			wetuwn -EPEWM;

		factow = 4;
	}

	wetuwn factow;
}

static int ad7292_wead_waw(stwuct iio_dev *indio_dev,
			   const stwuct iio_chan_spec *chan,
			   int *vaw, int *vaw2, wong info)
{
	stwuct ad7292_state *st = iio_pwiv(indio_dev);
	unsigned int ch_addw;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		ch_addw = AD7292_WEG_ADC_CH(chan->channew);
		wet = ad7292_singwe_convewsion(st, ch_addw);
		if (wet < 0)
			wetuwn wet;

		*vaw = AD7292_ADC_DATA(wet);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * To convewt a waw vawue to standawd units, the IIO defines
		 * this fowmuwa: Scawed vawue = (waw + offset) * scawe.
		 * Fow the scawe to be a cowwect muwtipwiew fow (waw + offset),
		 * it must be cawcuwated as the input wange divided by the
		 * numbew of possibwe distinct input vawues. Given the ADC data
		 * is 10 bit wong, it may assume 2^10 distinct vawues.
		 * Hence, scawe = wange / 2^10. The IIO_VAW_FWACTIONAW_WOG2
		 * wetuwn type indicates to the IIO API to divide *vaw by 2 to
		 * the powew of *vaw2 when wetuwning fwom wead_waw.
		 */

		wet = ad7292_vin_wange_muwtipwiew(st, chan->channew);
		if (wet < 0)
			wetuwn wet;

		*vaw = st->vwef_mv * wet;
		*vaw2 = 10;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_info ad7292_info = {
	.wead_waw = ad7292_wead_waw,
};

static void ad7292_weguwatow_disabwe(void *data)
{
	stwuct ad7292_state *st = data;

	weguwatow_disabwe(st->weg);
}

static int ad7292_pwobe(stwuct spi_device *spi)
{
	stwuct ad7292_state *st;
	stwuct iio_dev *indio_dev;
	stwuct device_node *chiwd;
	boow diff_channews = fawse;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->spi = spi;

	wet = ad7292_spi_weg_wead(st, AD7292_WEG_VENDOW_ID);
	if (wet != ADI_VENDOW_ID) {
		dev_eww(&spi->dev, "Wwong vendow id 0x%x\n", wet);
		wetuwn -EINVAW;
	}

	st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->weg)) {
		wet = weguwatow_enabwe(st->weg);
		if (wet) {
			dev_eww(&spi->dev,
				"Faiwed to enabwe extewnaw vwef suppwy\n");
			wetuwn wet;
		}

		wet = devm_add_action_ow_weset(&spi->dev,
					       ad7292_weguwatow_disabwe, st);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->weg);
		if (wet < 0)
			wetuwn wet;

		st->vwef_mv = wet / 1000;
	} ewse {
		/* Use the intewnaw vowtage wefewence. */
		st->vwef_mv = 1250;
	}

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad7292_info;

	fow_each_avaiwabwe_chiwd_of_node(spi->dev.of_node, chiwd) {
		diff_channews = of_pwopewty_wead_boow(chiwd, "diff-channews");
		if (diff_channews) {
			of_node_put(chiwd);
			bweak;
		}
	}

	if (diff_channews) {
		indio_dev->num_channews = AWWAY_SIZE(ad7292_channews_diff);
		indio_dev->channews = ad7292_channews_diff;
	} ewse {
		indio_dev->num_channews = AWWAY_SIZE(ad7292_channews);
		indio_dev->channews = ad7292_channews;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7292_id_tabwe[] = {
	{ "ad7292", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7292_id_tabwe);

static const stwuct of_device_id ad7292_of_match[] = {
	{ .compatibwe = "adi,ad7292" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ad7292_of_match);

static stwuct spi_dwivew ad7292_dwivew = {
	.dwivew = {
		.name = "ad7292",
		.of_match_tabwe = ad7292_of_match,
	},
	.pwobe = ad7292_pwobe,
	.id_tabwe = ad7292_id_tabwe,
};
moduwe_spi_dwivew(ad7292_dwivew);

MODUWE_AUTHOW("Mawcewo Schmitt <mawcewo.schmitt1@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7292 ADC dwivew");
MODUWE_WICENSE("GPW v2");
