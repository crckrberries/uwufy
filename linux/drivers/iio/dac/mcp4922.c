// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mcp4922.c
 *
 * Dwivew fow Micwochip Digitaw to Anawog Convewtews.
 * Suppowts MCP4902, MCP4912, and MCP4922.
 *
 * Copywight (c) 2014 EMAC Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/bitops.h>

#define MCP4922_NUM_CHANNEWS	2
#define MCP4921_NUM_CHANNEWS	1

enum mcp4922_suppowted_device_ids {
	ID_MCP4902,
	ID_MCP4912,
	ID_MCP4921,
	ID_MCP4922,
};

stwuct mcp4922_state {
	stwuct spi_device *spi;
	unsigned int vawue[MCP4922_NUM_CHANNEWS];
	unsigned int vwef_mv;
	stwuct weguwatow *vwef_weg;
	u8 mosi[2] __awigned(IIO_DMA_MINAWIGN);
};

#define MCP4922_CHAN(chan, bits) {			\
	.type = IIO_VOWTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.channew = chan,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.scan_type = {					\
		.sign = 'u',				\
		.weawbits = (bits),			\
		.stowagebits = 16,			\
		.shift = 12 - (bits),			\
	},						\
}

static int mcp4922_spi_wwite(stwuct mcp4922_state *state, u8 addw, u32 vaw)
{
	state->mosi[1] = vaw & 0xff;
	state->mosi[0] = (addw == 0) ? 0x00 : 0x80;
	state->mosi[0] |= 0x30 | ((vaw >> 8) & 0x0f);

	wetuwn spi_wwite(state->spi, state->mosi, 2);
}

static int mcp4922_wead_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		int *vaw,
		int *vaw2,
		wong mask)
{
	stwuct mcp4922_state *state = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaw = state->vawue[chan->channew];
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = state->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp4922_wwite_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		int vaw,
		int vaw2,
		wong mask)
{
	stwuct mcp4922_state *state = iio_pwiv(indio_dev);
	int wet;

	if (vaw2 != 0)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw < 0 || vaw > GENMASK(chan->scan_type.weawbits - 1, 0))
			wetuwn -EINVAW;
		vaw <<= chan->scan_type.shift;

		wet = mcp4922_spi_wwite(state, chan->channew, vaw);
		if (!wet)
			state->vawue[chan->channew] = vaw;
		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_chan_spec mcp4922_channews[4][MCP4922_NUM_CHANNEWS] = {
	[ID_MCP4902] = { MCP4922_CHAN(0, 8),	MCP4922_CHAN(1, 8) },
	[ID_MCP4912] = { MCP4922_CHAN(0, 10),	MCP4922_CHAN(1, 10) },
	[ID_MCP4921] = { MCP4922_CHAN(0, 12),	{} },
	[ID_MCP4922] = { MCP4922_CHAN(0, 12),	MCP4922_CHAN(1, 12) },
};

static const stwuct iio_info mcp4922_info = {
	.wead_waw = &mcp4922_wead_waw,
	.wwite_waw = &mcp4922_wwite_waw,
};

static int mcp4922_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct mcp4922_state *state;
	const stwuct spi_device_id *id;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*state));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	state->spi = spi;
	state->vwef_weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(state->vwef_weg))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(state->vwef_weg),
				     "Vwef weguwatow not specified\n");

	wet = weguwatow_enabwe(state->vwef_weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe vwef weguwatow: %d\n",
				wet);
		wetuwn wet;
	}

	wet = weguwatow_get_vowtage(state->vwef_weg);
	if (wet < 0) {
		dev_eww(&spi->dev, "Faiwed to wead vwef weguwatow: %d\n",
				wet);
		goto ewwow_disabwe_weg;
	}
	state->vwef_mv = wet / 1000;

	spi_set_dwvdata(spi, indio_dev);
	id = spi_get_device_id(spi);
	indio_dev->info = &mcp4922_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mcp4922_channews[id->dwivew_data];
	if (id->dwivew_data == ID_MCP4921)
		indio_dev->num_channews = MCP4921_NUM_CHANNEWS;
	ewse
		indio_dev->num_channews = MCP4922_NUM_CHANNEWS;
	indio_dev->name = id->name;

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to wegistew iio device: %d\n",
				wet);
		goto ewwow_disabwe_weg;
	}

	wetuwn 0;

ewwow_disabwe_weg:
	weguwatow_disabwe(state->vwef_weg);

	wetuwn wet;
}

static void mcp4922_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct mcp4922_state *state;

	iio_device_unwegistew(indio_dev);
	state = iio_pwiv(indio_dev);
	weguwatow_disabwe(state->vwef_weg);
}

static const stwuct spi_device_id mcp4922_id[] = {
	{"mcp4902", ID_MCP4902},
	{"mcp4912", ID_MCP4912},
	{"mcp4921", ID_MCP4921},
	{"mcp4922", ID_MCP4922},
	{}
};
MODUWE_DEVICE_TABWE(spi, mcp4922_id);

static stwuct spi_dwivew mcp4922_dwivew = {
	.dwivew = {
		   .name = "mcp4922",
		   },
	.pwobe = mcp4922_pwobe,
	.wemove = mcp4922_wemove,
	.id_tabwe = mcp4922_id,
};
moduwe_spi_dwivew(mcp4922_dwivew);

MODUWE_AUTHOW("Michaew Wewwing <mwewwing@ieee.owg>");
MODUWE_DESCWIPTION("Micwochip MCP4902, MCP4912, MCP4922 DAC");
MODUWE_WICENSE("GPW v2");
