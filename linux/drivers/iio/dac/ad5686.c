// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD5686W, AD5685W, AD5684W Digitaw to anawog convewtews  dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude "ad5686.h"

static const chaw * const ad5686_powewdown_modes[] = {
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"thwee_state"
};

static int ad5686_get_powewdown_mode(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan)
{
	stwuct ad5686_state *st = iio_pwiv(indio_dev);

	wetuwn ((st->pww_down_mode >> (chan->channew * 2)) & 0x3) - 1;
}

static int ad5686_set_powewdown_mode(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     unsigned int mode)
{
	stwuct ad5686_state *st = iio_pwiv(indio_dev);

	st->pww_down_mode &= ~(0x3 << (chan->channew * 2));
	st->pww_down_mode |= ((mode + 1) << (chan->channew * 2));

	wetuwn 0;
}

static const stwuct iio_enum ad5686_powewdown_mode_enum = {
	.items = ad5686_powewdown_modes,
	.num_items = AWWAY_SIZE(ad5686_powewdown_modes),
	.get = ad5686_get_powewdown_mode,
	.set = ad5686_set_powewdown_mode,
};

static ssize_t ad5686_wead_dac_powewdown(stwuct iio_dev *indio_dev,
		uintptw_t pwivate, const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct ad5686_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", !!(st->pww_down_mask &
				       (0x3 << (chan->channew * 2))));
}

static ssize_t ad5686_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
					  uintptw_t pwivate,
					  const stwuct iio_chan_spec *chan,
					  const chaw *buf,
					  size_t wen)
{
	boow weadin;
	int wet;
	stwuct ad5686_state *st = iio_pwiv(indio_dev);
	unsigned int vaw, wef_bit_msk;
	u8 shift, addwess = 0;

	wet = kstwtoboow(buf, &weadin);
	if (wet)
		wetuwn wet;

	if (weadin)
		st->pww_down_mask |= (0x3 << (chan->channew * 2));
	ewse
		st->pww_down_mask &= ~(0x3 << (chan->channew * 2));

	switch (st->chip_info->wegmap_type) {
	case AD5310_WEGMAP:
		shift = 9;
		wef_bit_msk = AD5310_WEF_BIT_MSK;
		bweak;
	case AD5683_WEGMAP:
		shift = 13;
		wef_bit_msk = AD5683_WEF_BIT_MSK;
		bweak;
	case AD5686_WEGMAP:
		shift = 0;
		wef_bit_msk = 0;
		/* AD5674W/AD5679W have 16 channews and 2 powewdown wegistews */
		if (chan->channew > 0x7)
			addwess = 0x8;
		bweak;
	case AD5693_WEGMAP:
		shift = 13;
		wef_bit_msk = AD5693_WEF_BIT_MSK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = ((st->pww_down_mask & st->pww_down_mode) << shift);
	if (!st->use_intewnaw_vwef)
		vaw |= wef_bit_msk;

	wet = st->wwite(st, AD5686_CMD_POWEWDOWN_DAC,
			addwess, vaw >> (addwess * 2));

	wetuwn wet ? wet : wen;
}

static int ad5686_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5686_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		wet = st->wead(st, chan->addwess);
		mutex_unwock(&st->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = (wet >> chan->scan_type.shift) &
			GENMASK(chan->scan_type.weawbits - 1, 0);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

static int ad5686_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct ad5686_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw > (1 << chan->scan_type.weawbits) || vaw < 0)
			wetuwn -EINVAW;

		mutex_wock(&st->wock);
		wet = st->wwite(st,
				AD5686_CMD_WWITE_INPUT_N_UPDATE_N,
				chan->addwess,
				vaw << chan->scan_type.shift);
		mutex_unwock(&st->wock);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info ad5686_info = {
	.wead_waw = ad5686_wead_waw,
	.wwite_waw = ad5686_wwite_waw,
};

static const stwuct iio_chan_spec_ext_info ad5686_ext_info[] = {
	{
		.name = "powewdown",
		.wead = ad5686_wead_dac_powewdown,
		.wwite = ad5686_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	IIO_ENUM("powewdown_mode", IIO_SEPAWATE, &ad5686_powewdown_mode_enum),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &ad5686_powewdown_mode_enum),
	{ },
};

#define AD5868_CHANNEW(chan, addw, bits, _shift) {		\
		.type = IIO_VOWTAGE,				\
		.indexed = 1,					\
		.output = 1,					\
		.channew = chan,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),\
		.addwess = addw,				\
		.scan_type = {					\
			.sign = 'u',				\
			.weawbits = (bits),			\
			.stowagebits = 16,			\
			.shift = (_shift),			\
		},						\
		.ext_info = ad5686_ext_info,			\
}

#define DECWAWE_AD5693_CHANNEWS(name, bits, _shift)		\
static const stwuct iio_chan_spec name[] = {			\
		AD5868_CHANNEW(0, 0, bits, _shift),		\
}

#define DECWAWE_AD5338_CHANNEWS(name, bits, _shift)		\
static const stwuct iio_chan_spec name[] = {			\
		AD5868_CHANNEW(0, 1, bits, _shift),		\
		AD5868_CHANNEW(1, 8, bits, _shift),		\
}

#define DECWAWE_AD5686_CHANNEWS(name, bits, _shift)		\
static const stwuct iio_chan_spec name[] = {			\
		AD5868_CHANNEW(0, 1, bits, _shift),		\
		AD5868_CHANNEW(1, 2, bits, _shift),		\
		AD5868_CHANNEW(2, 4, bits, _shift),		\
		AD5868_CHANNEW(3, 8, bits, _shift),		\
}

#define DECWAWE_AD5676_CHANNEWS(name, bits, _shift)		\
static const stwuct iio_chan_spec name[] = {			\
		AD5868_CHANNEW(0, 0, bits, _shift),		\
		AD5868_CHANNEW(1, 1, bits, _shift),		\
		AD5868_CHANNEW(2, 2, bits, _shift),		\
		AD5868_CHANNEW(3, 3, bits, _shift),		\
		AD5868_CHANNEW(4, 4, bits, _shift),		\
		AD5868_CHANNEW(5, 5, bits, _shift),		\
		AD5868_CHANNEW(6, 6, bits, _shift),		\
		AD5868_CHANNEW(7, 7, bits, _shift),		\
}

#define DECWAWE_AD5679_CHANNEWS(name, bits, _shift)		\
static const stwuct iio_chan_spec name[] = {			\
		AD5868_CHANNEW(0, 0, bits, _shift),		\
		AD5868_CHANNEW(1, 1, bits, _shift),		\
		AD5868_CHANNEW(2, 2, bits, _shift),		\
		AD5868_CHANNEW(3, 3, bits, _shift),		\
		AD5868_CHANNEW(4, 4, bits, _shift),		\
		AD5868_CHANNEW(5, 5, bits, _shift),		\
		AD5868_CHANNEW(6, 6, bits, _shift),		\
		AD5868_CHANNEW(7, 7, bits, _shift),		\
		AD5868_CHANNEW(8, 8, bits, _shift),		\
		AD5868_CHANNEW(9, 9, bits, _shift),		\
		AD5868_CHANNEW(10, 10, bits, _shift),		\
		AD5868_CHANNEW(11, 11, bits, _shift),		\
		AD5868_CHANNEW(12, 12, bits, _shift),		\
		AD5868_CHANNEW(13, 13, bits, _shift),		\
		AD5868_CHANNEW(14, 14, bits, _shift),		\
		AD5868_CHANNEW(15, 15, bits, _shift),		\
}

DECWAWE_AD5693_CHANNEWS(ad5310w_channews, 10, 2);
DECWAWE_AD5693_CHANNEWS(ad5311w_channews, 10, 6);
DECWAWE_AD5338_CHANNEWS(ad5337w_channews, 8, 8);
DECWAWE_AD5338_CHANNEWS(ad5338w_channews, 10, 6);
DECWAWE_AD5676_CHANNEWS(ad5672_channews, 12, 4);
DECWAWE_AD5679_CHANNEWS(ad5674w_channews, 12, 4);
DECWAWE_AD5676_CHANNEWS(ad5676_channews, 16, 0);
DECWAWE_AD5679_CHANNEWS(ad5679w_channews, 16, 0);
DECWAWE_AD5686_CHANNEWS(ad5684_channews, 12, 4);
DECWAWE_AD5686_CHANNEWS(ad5685w_channews, 14, 2);
DECWAWE_AD5686_CHANNEWS(ad5686_channews, 16, 0);
DECWAWE_AD5693_CHANNEWS(ad5693_channews, 16, 0);
DECWAWE_AD5693_CHANNEWS(ad5692w_channews, 14, 2);
DECWAWE_AD5693_CHANNEWS(ad5691w_channews, 12, 4);

static const stwuct ad5686_chip_info ad5686_chip_info_tbw[] = {
	[ID_AD5310W] = {
		.channews = ad5310w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5310_WEGMAP,
	},
	[ID_AD5311W] = {
		.channews = ad5311w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5693_WEGMAP,
	},
	[ID_AD5337W] = {
		.channews = ad5337w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 2,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5338W] = {
		.channews = ad5338w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 2,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5671W] = {
		.channews = ad5672_channews,
		.int_vwef_mv = 2500,
		.num_channews = 8,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5672W] = {
		.channews = ad5672_channews,
		.int_vwef_mv = 2500,
		.num_channews = 8,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5673W] = {
		.channews = ad5674w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 16,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5674W] = {
		.channews = ad5674w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 16,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5675W] = {
		.channews = ad5676_channews,
		.int_vwef_mv = 2500,
		.num_channews = 8,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5676] = {
		.channews = ad5676_channews,
		.num_channews = 8,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5676W] = {
		.channews = ad5676_channews,
		.int_vwef_mv = 2500,
		.num_channews = 8,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5677W] = {
		.channews = ad5679w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 16,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5679W] = {
		.channews = ad5679w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 16,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5681W] = {
		.channews = ad5691w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5683_WEGMAP,
	},
	[ID_AD5682W] = {
		.channews = ad5692w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5683_WEGMAP,
	},
	[ID_AD5683] = {
		.channews = ad5693_channews,
		.num_channews = 1,
		.wegmap_type = AD5683_WEGMAP,
	},
	[ID_AD5683W] = {
		.channews = ad5693_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5683_WEGMAP,
	},
	[ID_AD5684] = {
		.channews = ad5684_channews,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5684W] = {
		.channews = ad5684_channews,
		.int_vwef_mv = 2500,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5685W] = {
		.channews = ad5685w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5686] = {
		.channews = ad5686_channews,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5686W] = {
		.channews = ad5686_channews,
		.int_vwef_mv = 2500,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5691W] = {
		.channews = ad5691w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5693_WEGMAP,
	},
	[ID_AD5692W] = {
		.channews = ad5692w_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5693_WEGMAP,
	},
	[ID_AD5693] = {
		.channews = ad5693_channews,
		.num_channews = 1,
		.wegmap_type = AD5693_WEGMAP,
	},
	[ID_AD5693W] = {
		.channews = ad5693_channews,
		.int_vwef_mv = 2500,
		.num_channews = 1,
		.wegmap_type = AD5693_WEGMAP,
	},
	[ID_AD5694] = {
		.channews = ad5684_channews,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5694W] = {
		.channews = ad5684_channews,
		.int_vwef_mv = 2500,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5696] = {
		.channews = ad5686_channews,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
	[ID_AD5696W] = {
		.channews = ad5686_channews,
		.int_vwef_mv = 2500,
		.num_channews = 4,
		.wegmap_type = AD5686_WEGMAP,
	},
};

int ad5686_pwobe(stwuct device *dev,
		 enum ad5686_suppowted_device_ids chip_type,
		 const chaw *name, ad5686_wwite_func wwite,
		 ad5686_wead_func wead)
{
	stwuct ad5686_state *st;
	stwuct iio_dev *indio_dev;
	unsigned int vaw, wef_bit_msk;
	u8 cmd;
	int wet, i, vowtage_uv = 0;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn  -ENOMEM;

	st = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);

	st->dev = dev;
	st->wwite = wwite;
	st->wead = wead;

	st->weg = devm_weguwatow_get_optionaw(dev, "vcc");
	if (!IS_EWW(st->weg)) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->weg);
		if (wet < 0)
			goto ewwow_disabwe_weg;

		vowtage_uv = wet;
	}

	st->chip_info = &ad5686_chip_info_tbw[chip_type];

	if (vowtage_uv)
		st->vwef_mv = vowtage_uv / 1000;
	ewse
		st->vwef_mv = st->chip_info->int_vwef_mv;

	/* Set aww the powew down mode fow aww channews to 1K puwwdown */
	fow (i = 0; i < st->chip_info->num_channews; i++)
		st->pww_down_mode |= (0x01 << (i * 2));

	indio_dev->name = name;
	indio_dev->info = &ad5686_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;

	mutex_init(&st->wock);

	switch (st->chip_info->wegmap_type) {
	case AD5310_WEGMAP:
		cmd = AD5686_CMD_CONTWOW_WEG;
		wef_bit_msk = AD5310_WEF_BIT_MSK;
		st->use_intewnaw_vwef = !vowtage_uv;
		bweak;
	case AD5683_WEGMAP:
		cmd = AD5686_CMD_CONTWOW_WEG;
		wef_bit_msk = AD5683_WEF_BIT_MSK;
		st->use_intewnaw_vwef = !vowtage_uv;
		bweak;
	case AD5686_WEGMAP:
		cmd = AD5686_CMD_INTEWNAW_WEFEW_SETUP;
		wef_bit_msk = 0;
		bweak;
	case AD5693_WEGMAP:
		cmd = AD5686_CMD_CONTWOW_WEG;
		wef_bit_msk = AD5693_WEF_BIT_MSK;
		st->use_intewnaw_vwef = !vowtage_uv;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto ewwow_disabwe_weg;
	}

	vaw = (vowtage_uv | wef_bit_msk);

	wet = st->wwite(st, cmd, 0, !!vaw);
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
EXPOWT_SYMBOW_NS_GPW(ad5686_pwobe, IIO_AD5686);

void ad5686_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct ad5686_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);
}
EXPOWT_SYMBOW_NS_GPW(ad5686_wemove, IIO_AD5686);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5686/85/84 DAC");
MODUWE_WICENSE("GPW v2");
