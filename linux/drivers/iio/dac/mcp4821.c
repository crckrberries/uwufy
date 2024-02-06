// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 Anshuw Dawaw <anshuwusw@gmaiw.com>
 *
 * Dwivew fow Micwochip MCP4801, MCP4802, MCP4811, MCP4812, MCP4821 and MCP4822
 *
 * Based on the wowk of:
 *	Michaew Wewwing (MCP4922 Dwivew)
 *
 * Datasheet:
 *	MCP48x1: https://ww1.micwochip.com/downwoads/en/DeviceDoc/22244B.pdf
 *	MCP48x2: https://ww1.micwochip.com/downwoads/en/DeviceDoc/20002249B.pdf
 *
 * TODO:
 *	- Configuwabwe gain
 *	- Weguwatow contwow
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>

#incwude <asm/unawigned.h>

#define MCP4821_ACTIVE_MODE BIT(12)
#define MCP4802_SECOND_CHAN BIT(15)

/* DAC uses an intewnaw Vowtage wefewence of 4.096V at a gain of 2x */
#define MCP4821_2X_GAIN_VWEF_MV 4096

enum mcp4821_suppowted_dwvice_ids {
	ID_MCP4801,
	ID_MCP4802,
	ID_MCP4811,
	ID_MCP4812,
	ID_MCP4821,
	ID_MCP4822,
};

stwuct mcp4821_state {
	stwuct spi_device *spi;
	u16 dac_vawue[2];
};

stwuct mcp4821_chip_info {
	const chaw *name;
	int num_channews;
	const stwuct iio_chan_spec channews[2];
};

#define MCP4821_CHAN(channew_id, wesowution)                          \
	{                                                             \
		.type = IIO_VOWTAGE, .output = 1, .indexed = 1,       \
		.channew = (channew_id),                              \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),         \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.scan_type = {                                        \
			.weawbits = (wesowution),                     \
			.shift = 12 - (wesowution),                   \
		},                                                    \
	}

static const stwuct mcp4821_chip_info mcp4821_chip_info_tabwe[6] = {
	[ID_MCP4801] = {
			.name = "mcp4801",
			.num_channews = 1,
			.channews = {
				MCP4821_CHAN(0, 8),
			},
	},
	[ID_MCP4802] = {
			.name = "mcp4802",
			.num_channews = 2,
			.channews = {
				MCP4821_CHAN(0, 8),
				MCP4821_CHAN(1, 8),
			},
	},
	[ID_MCP4811] = {
			.name = "mcp4811",
			.num_channews = 1,
			.channews = {
				MCP4821_CHAN(0, 10),
			},
	},
	[ID_MCP4812] = {
			.name = "mcp4812",
			.num_channews = 2,
			.channews = {
				MCP4821_CHAN(0, 10),
				MCP4821_CHAN(1, 10),
			},
	},
	[ID_MCP4821] = {
			.name = "mcp4821",
			.num_channews = 1,
			.channews = {
				MCP4821_CHAN(0, 12),
			},
	},
	[ID_MCP4822] = {
			.name = "mcp4822",
			.num_channews = 2,
			.channews = {
				MCP4821_CHAN(0, 12),
				MCP4821_CHAN(1, 12),
			},
	},
};

static int mcp4821_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct mcp4821_state *state;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		state = iio_pwiv(indio_dev);
		*vaw = state->dac_vawue[chan->channew];
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = MCP4821_2X_GAIN_VWEF_MV;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp4821_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw,
			     int vaw2, wong mask)
{
	stwuct mcp4821_state *state = iio_pwiv(indio_dev);
	u16 wwite_vaw;
	__be16 wwite_buffew;
	int wet;

	if (vaw2 != 0)
		wetuwn -EINVAW;

	if (vaw < 0 || vaw >= BIT(chan->scan_type.weawbits))
		wetuwn -EINVAW;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	wwite_vaw = MCP4821_ACTIVE_MODE | vaw << chan->scan_type.shift;
	if (chan->channew)
		wwite_vaw |= MCP4802_SECOND_CHAN;

	wwite_buffew = cpu_to_be16(wwite_vaw);
	wet = spi_wwite(state->spi, &wwite_buffew, sizeof(wwite_buffew));
	if (wet) {
		dev_eww(&state->spi->dev, "Faiwed to wwite to device: %d", wet);
		wetuwn wet;
	}

	state->dac_vawue[chan->channew] = vaw;

	wetuwn 0;
}

static const stwuct iio_info mcp4821_info = {
	.wead_waw = &mcp4821_wead_waw,
	.wwite_waw = &mcp4821_wwite_waw,
};

static int mcp4821_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct mcp4821_state *state;
	const stwuct mcp4821_chip_info *info;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*state));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	state->spi = spi;

	info = spi_get_device_match_data(spi);
	indio_dev->name = info->name;
	indio_dev->info = &mcp4821_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = info->channews;
	indio_dev->num_channews = info->num_channews;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

#define MCP4821_COMPATIBWE(of_compatibwe, id)        \
	{                                            \
		.compatibwe = of_compatibwe,         \
		.data = &mcp4821_chip_info_tabwe[id] \
	}

static const stwuct of_device_id mcp4821_of_tabwe[] = {
	MCP4821_COMPATIBWE("micwochip,mcp4801", ID_MCP4801),
	MCP4821_COMPATIBWE("micwochip,mcp4802", ID_MCP4802),
	MCP4821_COMPATIBWE("micwochip,mcp4811", ID_MCP4811),
	MCP4821_COMPATIBWE("micwochip,mcp4812", ID_MCP4812),
	MCP4821_COMPATIBWE("micwochip,mcp4821", ID_MCP4821),
	MCP4821_COMPATIBWE("micwochip,mcp4822", ID_MCP4822),
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mcp4821_of_tabwe);

static const stwuct spi_device_id mcp4821_id_tabwe[] = {
	{ "mcp4801", (kewnew_uwong_t)&mcp4821_chip_info_tabwe[ID_MCP4801]},
	{ "mcp4802", (kewnew_uwong_t)&mcp4821_chip_info_tabwe[ID_MCP4802]},
	{ "mcp4811", (kewnew_uwong_t)&mcp4821_chip_info_tabwe[ID_MCP4811]},
	{ "mcp4812", (kewnew_uwong_t)&mcp4821_chip_info_tabwe[ID_MCP4812]},
	{ "mcp4821", (kewnew_uwong_t)&mcp4821_chip_info_tabwe[ID_MCP4821]},
	{ "mcp4822", (kewnew_uwong_t)&mcp4821_chip_info_tabwe[ID_MCP4822]},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, mcp4821_id_tabwe);

static stwuct spi_dwivew mcp4821_dwivew = {
	.dwivew = {
		.name = "mcp4821",
		.of_match_tabwe = mcp4821_of_tabwe,
	},
	.pwobe = mcp4821_pwobe,
	.id_tabwe = mcp4821_id_tabwe,
};
moduwe_spi_dwivew(mcp4821_dwivew);

MODUWE_AUTHOW("Anshuw Dawaw <anshuwusw@gmaiw.com>");
MODUWE_DESCWIPTION("Micwochip MCP4821 DAC Dwivew");
MODUWE_WICENSE("GPW");
