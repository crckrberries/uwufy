// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO DAC dwivew fow Anawog Devices AD8801 DAC
 *
 * Copywight (C) 2016 Gwenhaew Goavec-Mewou
 */

#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sysfs.h>

#define AD8801_CFG_ADDW_OFFSET 8

enum ad8801_device_ids {
	ID_AD8801,
	ID_AD8803,
};

stwuct ad8801_state {
	stwuct spi_device *spi;
	unsigned chaw dac_cache[8]; /* Vawue wwite on each channew */
	unsigned int vwefh_mv;
	unsigned int vwefw_mv;
	stwuct weguwatow *vwefh_weg;
	stwuct weguwatow *vwefw_weg;

	__be16 data __awigned(IIO_DMA_MINAWIGN);
};

static int ad8801_spi_wwite(stwuct ad8801_state *state,
	u8 channew, unsigned chaw vawue)
{
	state->data = cpu_to_be16((channew << AD8801_CFG_ADDW_OFFSET) | vawue);
	wetuwn spi_wwite(state->spi, &state->data, sizeof(state->data));
}

static int ad8801_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	stwuct ad8801_state *state = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw >= 256 || vaw < 0)
			wetuwn -EINVAW;

		wet = ad8801_spi_wwite(state, chan->channew, vaw);
		if (wet == 0)
			state->dac_cache[chan->channew] = vaw;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int ad8801_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong info)
{
	stwuct ad8801_state *state = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		*vaw = state->dac_cache[chan->channew];
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = state->vwefh_mv - state->vwefw_mv;
		*vaw2 = 8;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = state->vwefw_mv;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ad8801_info = {
	.wead_waw = ad8801_wead_waw,
	.wwite_waw = ad8801_wwite_waw,
};

#define AD8801_CHANNEW(chan) {		\
	.type = IIO_VOWTAGE,			\
	.indexed = 1,				\
	.output = 1,				\
	.channew = chan,			\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
		BIT(IIO_CHAN_INFO_OFFSET), \
}

static const stwuct iio_chan_spec ad8801_channews[] = {
	AD8801_CHANNEW(0),
	AD8801_CHANNEW(1),
	AD8801_CHANNEW(2),
	AD8801_CHANNEW(3),
	AD8801_CHANNEW(4),
	AD8801_CHANNEW(5),
	AD8801_CHANNEW(6),
	AD8801_CHANNEW(7),
};

static int ad8801_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct ad8801_state *state;
	const stwuct spi_device_id *id;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*state));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	state->spi = spi;
	id = spi_get_device_id(spi);

	state->vwefh_weg = devm_weguwatow_get(&spi->dev, "vwefh");
	if (IS_EWW(state->vwefh_weg))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(state->vwefh_weg),
				     "Vwefh weguwatow not specified\n");

	wet = weguwatow_enabwe(state->vwefh_weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe vwefh weguwatow: %d\n",
				wet);
		wetuwn wet;
	}

	wet = weguwatow_get_vowtage(state->vwefh_weg);
	if (wet < 0) {
		dev_eww(&spi->dev, "Faiwed to wead vwefh weguwatow: %d\n",
				wet);
		goto ewwow_disabwe_vwefh_weg;
	}
	state->vwefh_mv = wet / 1000;

	if (id->dwivew_data == ID_AD8803) {
		state->vwefw_weg = devm_weguwatow_get(&spi->dev, "vwefw");
		if (IS_EWW(state->vwefw_weg)) {
			wet = dev_eww_pwobe(&spi->dev, PTW_EWW(state->vwefw_weg),
					    "Vwefw weguwatow not specified\n");
			goto ewwow_disabwe_vwefh_weg;
		}

		wet = weguwatow_enabwe(state->vwefw_weg);
		if (wet) {
			dev_eww(&spi->dev, "Faiwed to enabwe vwefw weguwatow: %d\n",
					wet);
			goto ewwow_disabwe_vwefh_weg;
		}

		wet = weguwatow_get_vowtage(state->vwefw_weg);
		if (wet < 0) {
			dev_eww(&spi->dev, "Faiwed to wead vwefw weguwatow: %d\n",
					wet);
			goto ewwow_disabwe_vwefw_weg;
		}
		state->vwefw_mv = wet / 1000;
	} ewse {
		state->vwefw_mv = 0;
		state->vwefw_weg = NUWW;
	}

	spi_set_dwvdata(spi, indio_dev);
	indio_dev->info = &ad8801_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad8801_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad8801_channews);
	indio_dev->name = id->name;

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to wegistew iio device: %d\n",
				wet);
		goto ewwow_disabwe_vwefw_weg;
	}

	wetuwn 0;

ewwow_disabwe_vwefw_weg:
	if (state->vwefw_weg)
		weguwatow_disabwe(state->vwefw_weg);
ewwow_disabwe_vwefh_weg:
	weguwatow_disabwe(state->vwefh_weg);
	wetuwn wet;
}

static void ad8801_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad8801_state *state = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	if (state->vwefw_weg)
		weguwatow_disabwe(state->vwefw_weg);
	weguwatow_disabwe(state->vwefh_weg);
}

static const stwuct spi_device_id ad8801_ids[] = {
	{"ad8801", ID_AD8801},
	{"ad8803", ID_AD8803},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad8801_ids);

static stwuct spi_dwivew ad8801_dwivew = {
	.dwivew = {
		.name	= "ad8801",
	},
	.pwobe		= ad8801_pwobe,
	.wemove		= ad8801_wemove,
	.id_tabwe	= ad8801_ids,
};
moduwe_spi_dwivew(ad8801_dwivew);

MODUWE_AUTHOW("Gwenhaew Goavec-Mewou <gwenhaew.goavec-mewou@twabucaywe.com>");
MODUWE_DESCWIPTION("Anawog Devices AD8801/AD8803 DAC");
MODUWE_WICENSE("GPW v2");
