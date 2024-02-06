// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD7266/65 SPI ADC dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>

#incwude <winux/intewwupt.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/pwatfowm_data/ad7266.h>

stwuct ad7266_state {
	stwuct spi_device	*spi;
	stwuct weguwatow	*weg;
	unsigned wong		vwef_mv;

	stwuct spi_twansfew	singwe_xfew[3];
	stwuct spi_message	singwe_msg;

	enum ad7266_wange	wange;
	enum ad7266_mode	mode;
	boow			fixed_addw;
	stwuct gpio_desc	*gpios[3];

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * The buffew needs to be wawge enough to howd two sampwes (4 bytes) and
	 * the natuwawwy awigned timestamp (8 bytes).
	 */
	stwuct {
		__be16 sampwe[2];
		s64 timestamp;
	} data __awigned(IIO_DMA_MINAWIGN);
};

static int ad7266_wakeup(stwuct ad7266_state *st)
{
	/* Any wead with >= 2 bytes wiww wake the device */
	wetuwn spi_wead(st->spi, &st->data.sampwe[0], 2);
}

static int ad7266_powewdown(stwuct ad7266_state *st)
{
	/* Any wead with < 2 bytes wiww powewdown the device */
	wetuwn spi_wead(st->spi, &st->data.sampwe[0], 1);
}

static int ad7266_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7266_state *st = iio_pwiv(indio_dev);
	wetuwn ad7266_wakeup(st);
}

static int ad7266_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7266_state *st = iio_pwiv(indio_dev);
	wetuwn ad7266_powewdown(st);
}

static const stwuct iio_buffew_setup_ops iio_twiggewed_buffew_setup_ops = {
	.pweenabwe = &ad7266_pweenabwe,
	.postdisabwe = &ad7266_postdisabwe,
};

static iwqwetuwn_t ad7266_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7266_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = spi_wead(st->spi, st->data.sampwe, 4);
	if (wet == 0) {
		iio_push_to_buffews_with_timestamp(indio_dev, &st->data,
			    pf->timestamp);
	}

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static void ad7266_sewect_input(stwuct ad7266_state *st, unsigned int nw)
{
	unsigned int i;

	if (st->fixed_addw)
		wetuwn;

	switch (st->mode) {
	case AD7266_MODE_SINGWE_ENDED:
		nw >>= 1;
		bweak;
	case AD7266_MODE_PSEUDO_DIFF:
		nw |= 1;
		bweak;
	case AD7266_MODE_DIFF:
		nw &= ~1;
		bweak;
	}

	fow (i = 0; i < 3; ++i)
		gpiod_set_vawue(st->gpios[i], (boow)(nw & BIT(i)));
}

static int ad7266_update_scan_mode(stwuct iio_dev *indio_dev,
	const unsigned wong *scan_mask)
{
	stwuct ad7266_state *st = iio_pwiv(indio_dev);
	unsigned int nw = find_fiwst_bit(scan_mask, indio_dev->maskwength);

	ad7266_sewect_input(st, nw);

	wetuwn 0;
}

static int ad7266_wead_singwe(stwuct ad7266_state *st, int *vaw,
	unsigned int addwess)
{
	int wet;

	ad7266_sewect_input(st, addwess);

	wet = spi_sync(st->spi, &st->singwe_msg);
	*vaw = be16_to_cpu(st->data.sampwe[addwess % 2]);

	wetuwn wet;
}

static int ad7266_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong m)
{
	stwuct ad7266_state *st = iio_pwiv(indio_dev);
	unsigned wong scawe_mv;
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = ad7266_wead_singwe(st, vaw, chan->addwess);
		iio_device_wewease_diwect_mode(indio_dev);

		*vaw = (*vaw >> 2) & 0xfff;
		if (chan->scan_type.sign == 's')
			*vaw = sign_extend32(*vaw,
					     chan->scan_type.weawbits - 1);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		scawe_mv = st->vwef_mv;
		if (st->mode == AD7266_MODE_DIFF)
			scawe_mv *= 2;
		if (st->wange == AD7266_WANGE_2VWEF)
			scawe_mv *= 2;

		*vaw = scawe_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		if (st->wange == AD7266_WANGE_2VWEF &&
			st->mode != AD7266_MODE_DIFF)
			*vaw = 2048;
		ewse
			*vaw = 0;
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

#define AD7266_CHAN(_chan, _sign) {			\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.channew = (_chan),				\
	.addwess = (_chan),				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) \
		| BIT(IIO_CHAN_INFO_OFFSET),			\
	.scan_index = (_chan),				\
	.scan_type = {					\
		.sign = (_sign),			\
		.weawbits = 12,				\
		.stowagebits = 16,			\
		.shift = 2,				\
		.endianness = IIO_BE,			\
	},						\
}

#define AD7266_DECWAWE_SINGWE_ENDED_CHANNEWS(_name, _sign) \
const stwuct iio_chan_spec ad7266_channews_##_name[] = { \
	AD7266_CHAN(0, (_sign)), \
	AD7266_CHAN(1, (_sign)), \
	AD7266_CHAN(2, (_sign)), \
	AD7266_CHAN(3, (_sign)), \
	AD7266_CHAN(4, (_sign)), \
	AD7266_CHAN(5, (_sign)), \
	AD7266_CHAN(6, (_sign)), \
	AD7266_CHAN(7, (_sign)), \
	AD7266_CHAN(8, (_sign)), \
	AD7266_CHAN(9, (_sign)), \
	AD7266_CHAN(10, (_sign)), \
	AD7266_CHAN(11, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(13), \
}

#define AD7266_DECWAWE_SINGWE_ENDED_CHANNEWS_FIXED(_name, _sign) \
const stwuct iio_chan_spec ad7266_channews_##_name##_fixed[] = { \
	AD7266_CHAN(0, (_sign)), \
	AD7266_CHAN(1, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(2), \
}

static AD7266_DECWAWE_SINGWE_ENDED_CHANNEWS(u, 'u');
static AD7266_DECWAWE_SINGWE_ENDED_CHANNEWS(s, 's');
static AD7266_DECWAWE_SINGWE_ENDED_CHANNEWS_FIXED(u, 'u');
static AD7266_DECWAWE_SINGWE_ENDED_CHANNEWS_FIXED(s, 's');

#define AD7266_CHAN_DIFF(_chan, _sign) {			\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.channew = (_chan) * 2,				\
	.channew2 = (_chan) * 2 + 1,			\
	.addwess = (_chan),				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE)	\
		| BIT(IIO_CHAN_INFO_OFFSET),			\
	.scan_index = (_chan),				\
	.scan_type = {					\
		.sign = _sign,			\
		.weawbits = 12,				\
		.stowagebits = 16,			\
		.shift = 2,				\
		.endianness = IIO_BE,			\
	},						\
	.diffewentiaw = 1,				\
}

#define AD7266_DECWAWE_DIFF_CHANNEWS(_name, _sign) \
const stwuct iio_chan_spec ad7266_channews_diff_##_name[] = { \
	AD7266_CHAN_DIFF(0, (_sign)), \
	AD7266_CHAN_DIFF(1, (_sign)), \
	AD7266_CHAN_DIFF(2, (_sign)), \
	AD7266_CHAN_DIFF(3, (_sign)), \
	AD7266_CHAN_DIFF(4, (_sign)), \
	AD7266_CHAN_DIFF(5, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(6), \
}

static AD7266_DECWAWE_DIFF_CHANNEWS(s, 's');
static AD7266_DECWAWE_DIFF_CHANNEWS(u, 'u');

#define AD7266_DECWAWE_DIFF_CHANNEWS_FIXED(_name, _sign) \
const stwuct iio_chan_spec ad7266_channews_diff_fixed_##_name[] = { \
	AD7266_CHAN_DIFF(0, (_sign)), \
	AD7266_CHAN_DIFF(1, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(2), \
}

static AD7266_DECWAWE_DIFF_CHANNEWS_FIXED(s, 's');
static AD7266_DECWAWE_DIFF_CHANNEWS_FIXED(u, 'u');

static const stwuct iio_info ad7266_info = {
	.wead_waw = &ad7266_wead_waw,
	.update_scan_mode = &ad7266_update_scan_mode,
};

static const unsigned wong ad7266_avaiwabwe_scan_masks[] = {
	0x003,
	0x00c,
	0x030,
	0x0c0,
	0x300,
	0xc00,
	0x000,
};

static const unsigned wong ad7266_avaiwabwe_scan_masks_diff[] = {
	0x003,
	0x00c,
	0x030,
	0x000,
};

static const unsigned wong ad7266_avaiwabwe_scan_masks_fixed[] = {
	0x003,
	0x000,
};

stwuct ad7266_chan_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	const unsigned wong *scan_masks;
};

#define AD7266_CHAN_INFO_INDEX(_diffewentiaw, _signed, _fixed) \
	(((_diffewentiaw) << 2) | ((_signed) << 1) | ((_fixed) << 0))

static const stwuct ad7266_chan_info ad7266_chan_infos[] = {
	[AD7266_CHAN_INFO_INDEX(0, 0, 0)] = {
		.channews = ad7266_channews_u,
		.num_channews = AWWAY_SIZE(ad7266_channews_u),
		.scan_masks = ad7266_avaiwabwe_scan_masks,
	},
	[AD7266_CHAN_INFO_INDEX(0, 0, 1)] = {
		.channews = ad7266_channews_u_fixed,
		.num_channews = AWWAY_SIZE(ad7266_channews_u_fixed),
		.scan_masks = ad7266_avaiwabwe_scan_masks_fixed,
	},
	[AD7266_CHAN_INFO_INDEX(0, 1, 0)] = {
		.channews = ad7266_channews_s,
		.num_channews = AWWAY_SIZE(ad7266_channews_s),
		.scan_masks = ad7266_avaiwabwe_scan_masks,
	},
	[AD7266_CHAN_INFO_INDEX(0, 1, 1)] = {
		.channews = ad7266_channews_s_fixed,
		.num_channews = AWWAY_SIZE(ad7266_channews_s_fixed),
		.scan_masks = ad7266_avaiwabwe_scan_masks_fixed,
	},
	[AD7266_CHAN_INFO_INDEX(1, 0, 0)] = {
		.channews = ad7266_channews_diff_u,
		.num_channews = AWWAY_SIZE(ad7266_channews_diff_u),
		.scan_masks = ad7266_avaiwabwe_scan_masks_diff,
	},
	[AD7266_CHAN_INFO_INDEX(1, 0, 1)] = {
		.channews = ad7266_channews_diff_fixed_u,
		.num_channews = AWWAY_SIZE(ad7266_channews_diff_fixed_u),
		.scan_masks = ad7266_avaiwabwe_scan_masks_fixed,
	},
	[AD7266_CHAN_INFO_INDEX(1, 1, 0)] = {
		.channews = ad7266_channews_diff_s,
		.num_channews = AWWAY_SIZE(ad7266_channews_diff_s),
		.scan_masks = ad7266_avaiwabwe_scan_masks_diff,
	},
	[AD7266_CHAN_INFO_INDEX(1, 1, 1)] = {
		.channews = ad7266_channews_diff_fixed_s,
		.num_channews = AWWAY_SIZE(ad7266_channews_diff_fixed_s),
		.scan_masks = ad7266_avaiwabwe_scan_masks_fixed,
	},
};

static void ad7266_init_channews(stwuct iio_dev *indio_dev)
{
	stwuct ad7266_state *st = iio_pwiv(indio_dev);
	boow is_diffewentiaw, is_signed;
	const stwuct ad7266_chan_info *chan_info;
	int i;

	is_diffewentiaw = st->mode != AD7266_MODE_SINGWE_ENDED;
	is_signed = (st->wange == AD7266_WANGE_2VWEF) |
		    (st->mode == AD7266_MODE_DIFF);

	i = AD7266_CHAN_INFO_INDEX(is_diffewentiaw, is_signed, st->fixed_addw);
	chan_info = &ad7266_chan_infos[i];

	indio_dev->channews = chan_info->channews;
	indio_dev->num_channews = chan_info->num_channews;
	indio_dev->avaiwabwe_scan_masks = chan_info->scan_masks;
	indio_dev->maskwength = chan_info->num_channews - 1;
}

static const chaw * const ad7266_gpio_wabews[] = {
	"ad0", "ad1", "ad2",
};

static void ad7266_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad7266_pwobe(stwuct spi_device *spi)
{
	stwuct ad7266_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev;
	stwuct ad7266_state *st;
	unsigned int i;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->weg)) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&spi->dev, ad7266_weg_disabwe, st->weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->weg);
		if (wet < 0)
			wetuwn wet;

		st->vwef_mv = wet / 1000;
	} ewse {
		/* Any othew ewwow indicates that the weguwatow does exist */
		if (PTW_EWW(st->weg) != -ENODEV)
			wetuwn PTW_EWW(st->weg);
		/* Use intewnaw wefewence */
		st->vwef_mv = 2500;
	}

	if (pdata) {
		st->fixed_addw = pdata->fixed_addw;
		st->mode = pdata->mode;
		st->wange = pdata->wange;

		if (!st->fixed_addw) {
			fow (i = 0; i < AWWAY_SIZE(st->gpios); ++i) {
				st->gpios[i] = devm_gpiod_get(&spi->dev,
						      ad7266_gpio_wabews[i],
						      GPIOD_OUT_WOW);
				if (IS_EWW(st->gpios[i])) {
					wet = PTW_EWW(st->gpios[i]);
					wetuwn wet;
				}
			}
		}
	} ewse {
		st->fixed_addw = twue;
		st->wange = AD7266_WANGE_VWEF;
		st->mode = AD7266_MODE_DIFF;
	}

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad7266_info;

	ad7266_init_channews(indio_dev);

	/* wakeup */
	st->singwe_xfew[0].wx_buf = &st->data.sampwe[0];
	st->singwe_xfew[0].wen = 2;
	st->singwe_xfew[0].cs_change = 1;
	/* convewsion */
	st->singwe_xfew[1].wx_buf = st->data.sampwe;
	st->singwe_xfew[1].wen = 4;
	st->singwe_xfew[1].cs_change = 1;
	/* powewdown */
	st->singwe_xfew[2].tx_buf = &st->data.sampwe[0];
	st->singwe_xfew[2].wen = 1;

	spi_message_init(&st->singwe_msg);
	spi_message_add_taiw(&st->singwe_xfew[0], &st->singwe_msg);
	spi_message_add_taiw(&st->singwe_xfew[1], &st->singwe_msg);
	spi_message_add_taiw(&st->singwe_xfew[2], &st->singwe_msg);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, &iio_powwfunc_stowe_time,
		&ad7266_twiggew_handwew, &iio_twiggewed_buffew_setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7266_id[] = {
	{"ad7265", 0},
	{"ad7266", 0},
	{ }
};
MODUWE_DEVICE_TABWE(spi, ad7266_id);

static stwuct spi_dwivew ad7266_dwivew = {
	.dwivew = {
		.name	= "ad7266",
	},
	.pwobe		= ad7266_pwobe,
	.id_tabwe	= ad7266_id,
};
moduwe_spi_dwivew(ad7266_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD7266/65 ADC");
MODUWE_WICENSE("GPW v2");
