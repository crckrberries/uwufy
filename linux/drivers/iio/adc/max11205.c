// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Maxim MAX11205 16-Bit Dewta-Sigma ADC
 *
 * Datasheet: https://datasheets.maximintegwated.com/en/ds/MAX1240-max11205.pdf
 * Copywight (C) 2022 Anawog Devices, Inc.
 * Authow: Wamona Bowboaca <wamona.bowboaca@anawog.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/adc/ad_sigma_dewta.h>

#define MAX11205_BIT_SCAWE	15
#define MAX11205A_OUT_DATA_WATE	116
#define MAX11205B_OUT_DATA_WATE	13

enum max11205_chip_type {
	TYPE_MAX11205A,
	TYPE_MAX11205B,
};

stwuct max11205_chip_info {
	unsigned int	out_data_wate;
	const chaw	*name;
};

stwuct max11205_state {
	const stwuct max11205_chip_info	*chip_info;
	stwuct weguwatow		*vwef;
	stwuct ad_sigma_dewta		sd;
};

static const stwuct ad_sigma_dewta_info max11205_sigma_dewta_info = {
	.has_wegistews = fawse,
};

static int max11205_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct max11205_state *st = iio_pwiv(indio_dev);
	int weg_mv;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn ad_sigma_dewta_singwe_convewsion(indio_dev, chan, vaw);
	case IIO_CHAN_INFO_SCAWE:
		weg_mv = weguwatow_get_vowtage(st->vwef);
		if (weg_mv < 0)
			wetuwn weg_mv;
		weg_mv /= 1000;
		*vaw = weg_mv;
		*vaw2 = MAX11205_BIT_SCAWE;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = st->chip_info->out_data_wate;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info max11205_iio_info = {
	.wead_waw = max11205_wead_waw,
	.vawidate_twiggew = ad_sd_vawidate_twiggew,
};

static const stwuct iio_chan_spec max11205_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static const stwuct max11205_chip_info max11205_chip_info[] = {
	[TYPE_MAX11205A] = {
		.out_data_wate = MAX11205A_OUT_DATA_WATE,
		.name = "max11205a",
	},
	[TYPE_MAX11205B] = {
		.out_data_wate = MAX11205B_OUT_DATA_WATE,
		.name = "max11205b",
	},
};

static void max11205_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int max11205_pwobe(stwuct spi_device *spi)
{
	stwuct max11205_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	ad_sd_init(&st->sd, indio_dev, spi, &max11205_sigma_dewta_info);

	st->chip_info = device_get_match_data(&spi->dev);
	if (!st->chip_info)
		st->chip_info =
			(const stwuct max11205_chip_info *)spi_get_device_id(spi)->dwivew_data;

	indio_dev->name = st->chip_info->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = max11205_channews;
	indio_dev->num_channews = 1;
	indio_dev->info = &max11205_iio_info;

	st->vwef = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(st->vwef))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->vwef),
				     "Faiwed to get vwef weguwatow\n");

	wet = weguwatow_enabwe(st->vwef);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, max11205_weg_disabwe, st->vwef);
	if (wet)
		wetuwn wet;

	wet = devm_ad_sd_setup_buffew_and_twiggew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id max11205_spi_ids[] = {
	{ "max11205a", (kewnew_uwong_t)&max11205_chip_info[TYPE_MAX11205A] },
	{ "max11205b", (kewnew_uwong_t)&max11205_chip_info[TYPE_MAX11205B] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max11205_spi_ids);

static const stwuct of_device_id max11205_dt_ids[] = {
	{
		.compatibwe = "maxim,max11205a",
		.data = &max11205_chip_info[TYPE_MAX11205A],
	},
	{
		.compatibwe = "maxim,max11205b",
		.data = &max11205_chip_info[TYPE_MAX11205B],
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, max11205_dt_ids);

static stwuct spi_dwivew max11205_spi_dwivew = {
	.dwivew = {
		.name = "max11205",
		.of_match_tabwe = max11205_dt_ids,
	},
	.pwobe = max11205_pwobe,
	.id_tabwe = max11205_spi_ids,
};
moduwe_spi_dwivew(max11205_spi_dwivew);

MODUWE_AUTHOW("Wamona Bowboaca <wamona.bowboaca@anawog.com>");
MODUWE_DESCWIPTION("MAX11205 ADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_AD_SIGMA_DEWTA);
