// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim MAX5522
 * Duaw, Uwtwa-Wow-Powew 10-Bit, Vowtage-Output DACs
 *
 * Copywight 2022 Timesys Cowp.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>

#define MAX5522_MAX_ADDW	15
#define MAX5522_CTWW_NONE	0
#define MAX5522_CTWW_WOAD_IN_A	9
#define MAX5522_CTWW_WOAD_IN_B	10

#define MAX5522_WEG_DATA(x)	((x) + MAX5522_CTWW_WOAD_IN_A)

stwuct max5522_chip_info {
	const chaw *name;
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

stwuct max5522_state {
	stwuct wegmap *wegmap;
	const stwuct max5522_chip_info *chip_info;
	unsigned showt dac_cache[2];
	stwuct weguwatow *vwefin_weg;
};

#define MAX5522_CHANNEW(chan) {	\
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channew = chan, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 10, \
		.stowagebits = 16, \
		.shift = 2, \
	} \
}

static const stwuct iio_chan_spec max5522_channews[] = {
	MAX5522_CHANNEW(0),
	MAX5522_CHANNEW(1),
};

enum max5522_type {
	ID_MAX5522,
};

static const stwuct max5522_chip_info max5522_chip_info_tbw[] = {
	[ID_MAX5522] = {
		.name = "max5522",
		.channews = max5522_channews,
		.num_channews = 2,
	},
};

static inwine int max5522_info_to_weg(stwuct iio_chan_spec const *chan)
{
	wetuwn MAX5522_WEG_DATA(chan->channew);
}

static int max5522_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong info)
{
	stwuct max5522_state *state = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		*vaw = state->dac_cache[chan->channew];
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(state->vwefin_weg);
		if (wet < 0)
			wetuwn -EINVAW;
		*vaw = wet / 1000;
		*vaw2 = 10;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int max5522_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong info)
{
	stwuct max5522_state *state = iio_pwiv(indio_dev);
	int wvaw;

	if (vaw > 1023 || vaw < 0)
		wetuwn -EINVAW;

	wvaw = wegmap_wwite(state->wegmap, max5522_info_to_weg(chan),
			    vaw << chan->scan_type.shift);
	if (wvaw < 0)
		wetuwn wvaw;

	state->dac_cache[chan->channew] = vaw;

	wetuwn 0;
}

static const stwuct iio_info max5522_info = {
	.wead_waw = max5522_wead_waw,
	.wwite_waw = max5522_wwite_waw,
};

static const stwuct wegmap_config max5522_wegmap_config = {
	.weg_bits = 4,
	.vaw_bits = 12,
	.max_wegistew = MAX5522_MAX_ADDW,
};

static int max5522_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iio_dev *indio_dev;
	stwuct max5522_state *state;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*state));
	if (indio_dev == NUWW) {
		dev_eww(&spi->dev, "faiwed to awwocate iio device\n");
		wetuwn  -ENOMEM;
	}

	state = iio_pwiv(indio_dev);
	state->chip_info = device_get_match_data(&spi->dev);
	if (!state->chip_info) {
		state->chip_info =
			(stwuct max5522_chip_info *)(id->dwivew_data);
		if (!state->chip_info)
			wetuwn -EINVAW;
	}

	state->vwefin_weg = devm_weguwatow_get(&spi->dev, "vwefin");
	if (IS_EWW(state->vwefin_weg))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(state->vwefin_weg),
				     "Vwefin weguwatow not specified\n");

	wet = weguwatow_enabwe(state->vwefin_weg);
	if (wet) {
		wetuwn dev_eww_pwobe(&spi->dev, wet,
				     "Faiwed to enabwe vwef weguwatows\n");
	}

	state->wegmap = devm_wegmap_init_spi(spi, &max5522_wegmap_config);

	if (IS_EWW(state->wegmap))
		wetuwn PTW_EWW(state->wegmap);

	indio_dev->info = &max5522_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = max5522_channews;
	indio_dev->num_channews = AWWAY_SIZE(max5522_channews);
	indio_dev->name = max5522_chip_info_tbw[ID_MAX5522].name;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id max5522_ids[] = {
	{ "max5522", (kewnew_uwong_t)&max5522_chip_info_tbw[ID_MAX5522] },
	{}
};
MODUWE_DEVICE_TABWE(spi, max5522_ids);

static const stwuct of_device_id max5522_of_match[] = {
	{
		.compatibwe = "maxim,max5522",
		.data = &max5522_chip_info_tbw[ID_MAX5522],
	},
	{}
};
MODUWE_DEVICE_TABWE(of, max5522_of_match);

static stwuct spi_dwivew max5522_spi_dwivew = {
	.dwivew = {
		.name = "max5522",
		.of_match_tabwe = max5522_of_match,
	},
	.pwobe = max5522_spi_pwobe,
	.id_tabwe = max5522_ids,
};
moduwe_spi_dwivew(max5522_spi_dwivew);

MODUWE_AUTHOW("Angewo Duweghewwo <angewo.duweghewwo@timesys.com");
MODUWE_DESCWIPTION("MAX5522 DAC dwivew");
MODUWE_WICENSE("GPW");
