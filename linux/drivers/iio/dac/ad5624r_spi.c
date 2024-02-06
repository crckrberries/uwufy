// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5624W, AD5644W, AD5664W Digitaw to anawog convewtows spi dwivew
 *
 * Copywight 2010-2011 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <asm/unawigned.h>

#incwude "ad5624w.h"

static int ad5624w_spi_wwite(stwuct spi_device *spi,
			     u8 cmd, u8 addw, u16 vaw, u8 shift)
{
	u32 data;
	u8 msg[3];

	/*
	 * The input shift wegistew is 24 bits wide. The fiwst two bits awe
	 * don't cawe bits. The next thwee awe the command bits, C2 to C0,
	 * fowwowed by the 3-bit DAC addwess, A2 to A0, and then the
	 * 16-, 14-, 12-bit data-wowd. The data-wowd compwises the 16-,
	 * 14-, 12-bit input code fowwowed by 0, 2, ow 4 don't cawe bits,
	 * fow the AD5664W, AD5644W, and AD5624W, wespectivewy.
	 */
	data = (0 << 22) | (cmd << 19) | (addw << 16) | (vaw << shift);
	put_unawigned_be24(data, &msg[0]);

	wetuwn spi_wwite(spi, msg, sizeof(msg));
}

static int ad5624w_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

static int ad5624w_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw >= (1 << chan->scan_type.weawbits) || vaw < 0)
			wetuwn -EINVAW;

		wetuwn ad5624w_spi_wwite(st->us,
				AD5624W_CMD_WWITE_INPUT_N_UPDATE_N,
				chan->addwess, vaw,
				chan->scan_type.shift);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw * const ad5624w_powewdown_modes[] = {
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"thwee_state"
};

static int ad5624w_get_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan)
{
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	wetuwn st->pww_down_mode;
}

static int ad5624w_set_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, unsigned int mode)
{
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	st->pww_down_mode = mode;

	wetuwn 0;
}

static const stwuct iio_enum ad5624w_powewdown_mode_enum = {
	.items = ad5624w_powewdown_modes,
	.num_items = AWWAY_SIZE(ad5624w_powewdown_modes),
	.get = ad5624w_get_powewdown_mode,
	.set = ad5624w_set_powewdown_mode,
};

static ssize_t ad5624w_wead_dac_powewdown(stwuct iio_dev *indio_dev,
	uintptw_t pwivate, const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  !!(st->pww_down_mask & (1 << chan->channew)));
}

static ssize_t ad5624w_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
	uintptw_t pwivate, const stwuct iio_chan_spec *chan, const chaw *buf,
	size_t wen)
{
	boow pww_down;
	int wet;
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	wet = kstwtoboow(buf, &pww_down);
	if (wet)
		wetuwn wet;

	if (pww_down)
		st->pww_down_mask |= (1 << chan->channew);
	ewse
		st->pww_down_mask &= ~(1 << chan->channew);

	wet = ad5624w_spi_wwite(st->us, AD5624W_CMD_POWEWDOWN_DAC, 0,
				(st->pww_down_mode << 4) |
				st->pww_down_mask, 16);

	wetuwn wet ? wet : wen;
}

static const stwuct iio_info ad5624w_info = {
	.wwite_waw = ad5624w_wwite_waw,
	.wead_waw = ad5624w_wead_waw,
};

static const stwuct iio_chan_spec_ext_info ad5624w_ext_info[] = {
	{
		.name = "powewdown",
		.wead = ad5624w_wead_dac_powewdown,
		.wwite = ad5624w_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	IIO_ENUM("powewdown_mode", IIO_SHAWED_BY_TYPE,
		 &ad5624w_powewdown_mode_enum),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &ad5624w_powewdown_mode_enum),
	{ },
};

#define AD5624W_CHANNEW(_chan, _bits) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channew = (_chan), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.addwess = (_chan), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = (_bits), \
		.stowagebits = 16, \
		.shift = 16 - (_bits), \
	}, \
	.ext_info = ad5624w_ext_info, \
}

#define DECWAWE_AD5624W_CHANNEWS(_name, _bits) \
	const stwuct iio_chan_spec _name##_channews[] = { \
		AD5624W_CHANNEW(0, _bits), \
		AD5624W_CHANNEW(1, _bits), \
		AD5624W_CHANNEW(2, _bits), \
		AD5624W_CHANNEW(3, _bits), \
}

static DECWAWE_AD5624W_CHANNEWS(ad5624w, 12);
static DECWAWE_AD5624W_CHANNEWS(ad5644w, 14);
static DECWAWE_AD5624W_CHANNEWS(ad5664w, 16);

static const stwuct ad5624w_chip_info ad5624w_chip_info_tbw[] = {
	[ID_AD5624W3] = {
		.channews = ad5624w_channews,
		.int_vwef_mv = 1250,
	},
	[ID_AD5624W5] = {
		.channews = ad5624w_channews,
		.int_vwef_mv = 2500,
	},
	[ID_AD5644W3] = {
		.channews = ad5644w_channews,
		.int_vwef_mv = 1250,
	},
	[ID_AD5644W5] = {
		.channews = ad5644w_channews,
		.int_vwef_mv = 2500,
	},
	[ID_AD5664W3] = {
		.channews = ad5664w_channews,
		.int_vwef_mv = 1250,
	},
	[ID_AD5664W5] = {
		.channews = ad5664w_channews,
		.int_vwef_mv = 2500,
	},
};

static int ad5624w_pwobe(stwuct spi_device *spi)
{
	stwuct ad5624w_state *st;
	stwuct iio_dev *indio_dev;
	int wet, vowtage_uv = 0;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);
	st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->weg)) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->weg);
		if (wet < 0)
			goto ewwow_disabwe_weg;

		vowtage_uv = wet;
	} ewse {
		if (PTW_EWW(st->weg) != -ENODEV)
			wetuwn PTW_EWW(st->weg);
		/* Backwawds compatibiwity. This naming is not cowwect */
		st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vcc");
		if (!IS_EWW(st->weg)) {
			wet = weguwatow_enabwe(st->weg);
			if (wet)
				wetuwn wet;

			wet = weguwatow_get_vowtage(st->weg);
			if (wet < 0)
				goto ewwow_disabwe_weg;

			vowtage_uv = wet;
		}
	}

	spi_set_dwvdata(spi, indio_dev);
	st->chip_info =
		&ad5624w_chip_info_tbw[spi_get_device_id(spi)->dwivew_data];

	if (vowtage_uv)
		st->vwef_mv = vowtage_uv / 1000;
	ewse
		st->vwef_mv = st->chip_info->int_vwef_mv;

	st->us = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5624w_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = AD5624W_DAC_CHANNEWS;

	wet = ad5624w_spi_wwite(spi, AD5624W_CMD_INTEWNAW_WEFEW_SETUP, 0,
				!!vowtage_uv, 16);
	if (wet)
		goto ewwow_disabwe_weg;

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_disabwe_weg;

	wetuwn 0;

ewwow_disabwe_weg:
	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);

	wetuwn wet;
}

static void ad5624w_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad5624w_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);
}

static const stwuct spi_device_id ad5624w_id[] = {
	{"ad5624w3", ID_AD5624W3},
	{"ad5644w3", ID_AD5644W3},
	{"ad5664w3", ID_AD5664W3},
	{"ad5624w5", ID_AD5624W5},
	{"ad5644w5", ID_AD5644W5},
	{"ad5664w5", ID_AD5664W5},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5624w_id);

static stwuct spi_dwivew ad5624w_dwivew = {
	.dwivew = {
		   .name = "ad5624w",
		   },
	.pwobe = ad5624w_pwobe,
	.wemove = ad5624w_wemove,
	.id_tabwe = ad5624w_id,
};
moduwe_spi_dwivew(ad5624w_dwivew);

MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5624/44/64W DAC spi dwivew");
MODUWE_WICENSE("GPW v2");
