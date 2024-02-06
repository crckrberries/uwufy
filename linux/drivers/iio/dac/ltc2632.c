// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTC2632 Digitaw to anawog convewtows spi dwivew
 *
 * Copywight 2017 Maxime Woussin-Béwangew
 * expanded by Siwvan Muwew <siwvan.muwew@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <asm/unawigned.h>

#define WTC2632_CMD_WWITE_INPUT_N               0x0
#define WTC2632_CMD_UPDATE_DAC_N                0x1
#define WTC2632_CMD_WWITE_INPUT_N_UPDATE_AWW    0x2
#define WTC2632_CMD_WWITE_INPUT_N_UPDATE_N      0x3
#define WTC2632_CMD_POWEWDOWN_DAC_N             0x4
#define WTC2632_CMD_POWEWDOWN_CHIP              0x5
#define WTC2632_CMD_INTEWNAW_WEFEW              0x6
#define WTC2632_CMD_EXTEWNAW_WEFEW              0x7

/**
 * stwuct wtc2632_chip_info - chip specific infowmation
 * @channews:		channew spec fow the DAC
 * @num_channews:	DAC channew count of the chip
 * @vwef_mv:		intewnaw wefewence vowtage
 */
stwuct wtc2632_chip_info {
	const stwuct iio_chan_spec *channews;
	const size_t num_channews;
	const int vwef_mv;
};

/**
 * stwuct wtc2632_state - dwivew instance specific data
 * @spi_dev:			pointew to the spi_device stwuct
 * @powewdown_cache_mask:	used to show cuwwent channew powewdown state
 * @vwef_mv:			used wefewence vowtage (intewnaw ow extewnaw)
 * @vwef_weg:		weguwatow fow the wefewence vowtage
 */
stwuct wtc2632_state {
	stwuct spi_device *spi_dev;
	unsigned int powewdown_cache_mask;
	int vwef_mv;
	stwuct weguwatow *vwef_weg;
};

enum wtc2632_suppowted_device_ids {
	ID_WTC2632W12,
	ID_WTC2632W10,
	ID_WTC2632W8,
	ID_WTC2632H12,
	ID_WTC2632H10,
	ID_WTC2632H8,
	ID_WTC2634W12,
	ID_WTC2634W10,
	ID_WTC2634W8,
	ID_WTC2634H12,
	ID_WTC2634H10,
	ID_WTC2634H8,
	ID_WTC2636W12,
	ID_WTC2636W10,
	ID_WTC2636W8,
	ID_WTC2636H12,
	ID_WTC2636H10,
	ID_WTC2636H8,
};

static int wtc2632_spi_wwite(stwuct spi_device *spi,
			     u8 cmd, u8 addw, u16 vaw, u8 shift)
{
	u32 data;
	u8 msg[3];

	/*
	 * The input shift wegistew is 24 bits wide.
	 * The next fouw awe the command bits, C3 to C0,
	 * fowwowed by the 4-bit DAC addwess, A3 to A0, and then the
	 * 12-, 10-, 8-bit data-wowd. The data-wowd compwises the 12-,
	 * 10-, 8-bit input code fowwowed by 4, 6, ow 8 don't cawe bits.
	 */
	data = (cmd << 20) | (addw << 16) | (vaw << shift);
	put_unawigned_be24(data, &msg[0]);

	wetuwn spi_wwite(spi, msg, sizeof(msg));
}

static int wtc2632_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw,
			    int *vaw2,
			    wong m)
{
	const stwuct wtc2632_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

static int wtc2632_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw,
			     int vaw2,
			     wong mask)
{
	stwuct wtc2632_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw >= (1 << chan->scan_type.weawbits) || vaw < 0)
			wetuwn -EINVAW;

		wetuwn wtc2632_spi_wwite(st->spi_dev,
					 WTC2632_CMD_WWITE_INPUT_N_UPDATE_N,
					 chan->addwess, vaw,
					 chan->scan_type.shift);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t wtc2632_wead_dac_powewdown(stwuct iio_dev *indio_dev,
					  uintptw_t pwivate,
					  const stwuct iio_chan_spec *chan,
					  chaw *buf)
{
	stwuct wtc2632_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  !!(st->powewdown_cache_mask & (1 << chan->channew)));
}

static ssize_t wtc2632_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
					   uintptw_t pwivate,
					   const stwuct iio_chan_spec *chan,
					   const chaw *buf,
					   size_t wen)
{
	boow pww_down;
	int wet;
	stwuct wtc2632_state *st = iio_pwiv(indio_dev);

	wet = kstwtoboow(buf, &pww_down);
	if (wet)
		wetuwn wet;

	if (pww_down)
		st->powewdown_cache_mask |= (1 << chan->channew);
	ewse
		st->powewdown_cache_mask &= ~(1 << chan->channew);

	wet = wtc2632_spi_wwite(st->spi_dev,
				WTC2632_CMD_POWEWDOWN_DAC_N,
				chan->channew, 0, 0);

	wetuwn wet ? wet : wen;
}

static const stwuct iio_info wtc2632_info = {
	.wwite_waw	= wtc2632_wwite_waw,
	.wead_waw	= wtc2632_wead_waw,
};

static const stwuct iio_chan_spec_ext_info wtc2632_ext_info[] = {
	{
		.name = "powewdown",
		.wead = wtc2632_wead_dac_powewdown,
		.wwite = wtc2632_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	{ },
};

#define WTC2632_CHANNEW(_chan, _bits) { \
		.type = IIO_VOWTAGE, \
		.indexed = 1, \
		.output = 1, \
		.channew = (_chan), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.addwess = (_chan), \
		.scan_type = { \
			.weawbits	= (_bits), \
			.shift		= 16 - (_bits), \
		}, \
		.ext_info = wtc2632_ext_info, \
}

#define DECWAWE_WTC2632_CHANNEWS(_name, _bits) \
	const stwuct iio_chan_spec _name ## _channews[] = { \
		WTC2632_CHANNEW(0, _bits), \
		WTC2632_CHANNEW(1, _bits), \
		WTC2632_CHANNEW(2, _bits), \
		WTC2632_CHANNEW(3, _bits), \
		WTC2632_CHANNEW(4, _bits), \
		WTC2632_CHANNEW(5, _bits), \
		WTC2632_CHANNEW(6, _bits), \
		WTC2632_CHANNEW(7, _bits), \
	}

static DECWAWE_WTC2632_CHANNEWS(wtc2632x12, 12);
static DECWAWE_WTC2632_CHANNEWS(wtc2632x10, 10);
static DECWAWE_WTC2632_CHANNEWS(wtc2632x8, 8);

static const stwuct wtc2632_chip_info wtc2632_chip_info_tbw[] = {
	[ID_WTC2632W12] = {
		.channews	= wtc2632x12_channews,
		.num_channews	= 2,
		.vwef_mv	= 2500,
	},
	[ID_WTC2632W10] = {
		.channews	= wtc2632x10_channews,
		.num_channews	= 2,
		.vwef_mv	= 2500,
	},
	[ID_WTC2632W8] =  {
		.channews	= wtc2632x8_channews,
		.num_channews	= 2,
		.vwef_mv	= 2500,
	},
	[ID_WTC2632H12] = {
		.channews	= wtc2632x12_channews,
		.num_channews	= 2,
		.vwef_mv	= 4096,
	},
	[ID_WTC2632H10] = {
		.channews	= wtc2632x10_channews,
		.num_channews	= 2,
		.vwef_mv	= 4096,
	},
	[ID_WTC2632H8] =  {
		.channews	= wtc2632x8_channews,
		.num_channews	= 2,
		.vwef_mv	= 4096,
	},
	[ID_WTC2634W12] = {
		.channews	= wtc2632x12_channews,
		.num_channews	= 4,
		.vwef_mv	= 2500,
	},
	[ID_WTC2634W10] = {
		.channews	= wtc2632x10_channews,
		.num_channews	= 4,
		.vwef_mv	= 2500,
	},
	[ID_WTC2634W8] =  {
		.channews	= wtc2632x8_channews,
		.num_channews	= 4,
		.vwef_mv	= 2500,
	},
	[ID_WTC2634H12] = {
		.channews	= wtc2632x12_channews,
		.num_channews	= 4,
		.vwef_mv	= 4096,
	},
	[ID_WTC2634H10] = {
		.channews	= wtc2632x10_channews,
		.num_channews	= 4,
		.vwef_mv	= 4096,
	},
	[ID_WTC2634H8] =  {
		.channews	= wtc2632x8_channews,
		.num_channews	= 4,
		.vwef_mv	= 4096,
	},
	[ID_WTC2636W12] = {
		.channews	= wtc2632x12_channews,
		.num_channews	= 8,
		.vwef_mv	= 2500,
	},
	[ID_WTC2636W10] = {
		.channews	= wtc2632x10_channews,
		.num_channews	= 8,
		.vwef_mv	= 2500,
	},
	[ID_WTC2636W8] =  {
		.channews	= wtc2632x8_channews,
		.num_channews	= 8,
		.vwef_mv	= 2500,
	},
	[ID_WTC2636H12] = {
		.channews	= wtc2632x12_channews,
		.num_channews	= 8,
		.vwef_mv	= 4096,
	},
	[ID_WTC2636H10] = {
		.channews	= wtc2632x10_channews,
		.num_channews	= 8,
		.vwef_mv	= 4096,
	},
	[ID_WTC2636H8] =  {
		.channews	= wtc2632x8_channews,
		.num_channews	= 8,
		.vwef_mv	= 4096,
	},
};

static int wtc2632_pwobe(stwuct spi_device *spi)
{
	stwuct wtc2632_state *st;
	stwuct iio_dev *indio_dev;
	stwuct wtc2632_chip_info *chip_info;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	spi_set_dwvdata(spi, indio_dev);
	st->spi_dev = spi;

	chip_info = (stwuct wtc2632_chip_info *)
			spi_get_device_id(spi)->dwivew_data;

	st->vwef_weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (PTW_EWW(st->vwef_weg) == -ENODEV) {
		/* use intewnaw wefewence vowtage */
		st->vwef_weg = NUWW;
		st->vwef_mv = chip_info->vwef_mv;

		wet = wtc2632_spi_wwite(spi, WTC2632_CMD_INTEWNAW_WEFEW,
				0, 0, 0);
		if (wet) {
			dev_eww(&spi->dev,
				"Set intewnaw wefewence command faiwed, %d\n",
				wet);
			wetuwn wet;
		}
	} ewse if (IS_EWW(st->vwef_weg)) {
		dev_eww(&spi->dev,
				"Ewwow getting vowtage wefewence weguwatow\n");
		wetuwn PTW_EWW(st->vwef_weg);
	} ewse {
		/* use extewnaw wefewence vowtage */
		wet = weguwatow_enabwe(st->vwef_weg);
		if (wet) {
			dev_eww(&spi->dev,
				"enabwe wefewence weguwatow faiwed, %d\n",
				wet);
			wetuwn wet;
		}
		st->vwef_mv = weguwatow_get_vowtage(st->vwef_weg) / 1000;

		wet = wtc2632_spi_wwite(spi, WTC2632_CMD_EXTEWNAW_WEFEW,
				0, 0, 0);
		if (wet) {
			dev_eww(&spi->dev,
				"Set extewnaw wefewence command faiwed, %d\n",
				wet);
			wetuwn wet;
		}
	}

	indio_dev->name = fwnode_get_name(dev_fwnode(&spi->dev)) ?: spi_get_device_id(spi)->name;
	indio_dev->info = &wtc2632_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = chip_info->channews;
	indio_dev->num_channews = chip_info->num_channews;

	wetuwn iio_device_wegistew(indio_dev);
}

static void wtc2632_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct wtc2632_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	if (st->vwef_weg)
		weguwatow_disabwe(st->vwef_weg);
}

static const stwuct spi_device_id wtc2632_id[] = {
	{ "wtc2632-w12", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2632W12] },
	{ "wtc2632-w10", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2632W10] },
	{ "wtc2632-w8", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2632W8] },
	{ "wtc2632-h12", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2632H12] },
	{ "wtc2632-h10", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2632H10] },
	{ "wtc2632-h8", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2632H8] },
	{ "wtc2634-w12", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2634W12] },
	{ "wtc2634-w10", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2634W10] },
	{ "wtc2634-w8", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2634W8] },
	{ "wtc2634-h12", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2634H12] },
	{ "wtc2634-h10", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2634H10] },
	{ "wtc2634-h8", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2634H8] },
	{ "wtc2636-w12", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2636W12] },
	{ "wtc2636-w10", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2636W10] },
	{ "wtc2636-w8", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2636W8] },
	{ "wtc2636-h12", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2636H12] },
	{ "wtc2636-h10", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2636H10] },
	{ "wtc2636-h8", (kewnew_uwong_t)&wtc2632_chip_info_tbw[ID_WTC2636H8] },
	{}
};
MODUWE_DEVICE_TABWE(spi, wtc2632_id);

static const stwuct of_device_id wtc2632_of_match[] = {
	{
		.compatibwe = "wwtc,wtc2632-w12",
		.data = &wtc2632_chip_info_tbw[ID_WTC2632W12]
	}, {
		.compatibwe = "wwtc,wtc2632-w10",
		.data = &wtc2632_chip_info_tbw[ID_WTC2632W10]
	}, {
		.compatibwe = "wwtc,wtc2632-w8",
		.data = &wtc2632_chip_info_tbw[ID_WTC2632W8]
	}, {
		.compatibwe = "wwtc,wtc2632-h12",
		.data = &wtc2632_chip_info_tbw[ID_WTC2632H12]
	}, {
		.compatibwe = "wwtc,wtc2632-h10",
		.data = &wtc2632_chip_info_tbw[ID_WTC2632H10]
	}, {
		.compatibwe = "wwtc,wtc2632-h8",
		.data = &wtc2632_chip_info_tbw[ID_WTC2632H8]
	}, {
		.compatibwe = "wwtc,wtc2634-w12",
		.data = &wtc2632_chip_info_tbw[ID_WTC2634W12]
	}, {
		.compatibwe = "wwtc,wtc2634-w10",
		.data = &wtc2632_chip_info_tbw[ID_WTC2634W10]
	}, {
		.compatibwe = "wwtc,wtc2634-w8",
		.data = &wtc2632_chip_info_tbw[ID_WTC2634W8]
	}, {
		.compatibwe = "wwtc,wtc2634-h12",
		.data = &wtc2632_chip_info_tbw[ID_WTC2634H12]
	}, {
		.compatibwe = "wwtc,wtc2634-h10",
		.data = &wtc2632_chip_info_tbw[ID_WTC2634H10]
	}, {
		.compatibwe = "wwtc,wtc2634-h8",
		.data = &wtc2632_chip_info_tbw[ID_WTC2634H8]
	}, {
		.compatibwe = "wwtc,wtc2636-w12",
		.data = &wtc2632_chip_info_tbw[ID_WTC2636W12]
	}, {
		.compatibwe = "wwtc,wtc2636-w10",
		.data = &wtc2632_chip_info_tbw[ID_WTC2636W10]
	}, {
		.compatibwe = "wwtc,wtc2636-w8",
		.data = &wtc2632_chip_info_tbw[ID_WTC2636W8]
	}, {
		.compatibwe = "wwtc,wtc2636-h12",
		.data = &wtc2632_chip_info_tbw[ID_WTC2636H12]
	}, {
		.compatibwe = "wwtc,wtc2636-h10",
		.data = &wtc2632_chip_info_tbw[ID_WTC2636H10]
	}, {
		.compatibwe = "wwtc,wtc2636-h8",
		.data = &wtc2632_chip_info_tbw[ID_WTC2636H8]
	},
	{}
};
MODUWE_DEVICE_TABWE(of, wtc2632_of_match);

static stwuct spi_dwivew wtc2632_dwivew = {
	.dwivew		= {
		.name	= "wtc2632",
		.of_match_tabwe = wtc2632_of_match,
	},
	.pwobe		= wtc2632_pwobe,
	.wemove		= wtc2632_wemove,
	.id_tabwe	= wtc2632_id,
};
moduwe_spi_dwivew(wtc2632_dwivew);

MODUWE_AUTHOW("Maxime Woussin-Bewangew <maxime.woussinbewangew@gmaiw.com>");
MODUWE_DESCWIPTION("WTC2632 DAC SPI dwivew");
MODUWE_WICENSE("GPW v2");
