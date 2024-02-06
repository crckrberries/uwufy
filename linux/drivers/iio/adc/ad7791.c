// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD7787/AD7788/AD7789/AD7790/AD7791 SPI ADC dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/adc/ad_sigma_dewta.h>

#incwude <winux/pwatfowm_data/ad7791.h>

#define AD7791_WEG_COMM			0x0 /* Fow wwites */
#define AD7791_WEG_STATUS		0x0 /* Fow weads */
#define AD7791_WEG_MODE			0x1
#define AD7791_WEG_FIWTEW		0x2
#define AD7791_WEG_DATA			0x3

#define AD7791_MODE_CONTINUOUS		0x00
#define AD7791_MODE_SINGWE		0x02
#define AD7791_MODE_POWEWDOWN		0x03

#define AD7791_CH_AIN1P_AIN1N		0x00
#define AD7791_CH_AIN2			0x01
#define AD7791_CH_AIN1N_AIN1N		0x02
#define AD7791_CH_AVDD_MONITOW		0x03

#define AD7791_FIWTEW_CWK_DIV_1		(0x0 << 4)
#define AD7791_FIWTEW_CWK_DIV_2		(0x1 << 4)
#define AD7791_FIWTEW_CWK_DIV_4		(0x2 << 4)
#define AD7791_FIWTEW_CWK_DIV_8		(0x3 << 4)
#define AD7791_FIWTEW_CWK_MASK		(0x3 << 4)
#define AD7791_FIWTEW_WATE_120		0x0
#define AD7791_FIWTEW_WATE_100		0x1
#define AD7791_FIWTEW_WATE_33_3		0x2
#define AD7791_FIWTEW_WATE_20		0x3
#define AD7791_FIWTEW_WATE_16_6		0x4
#define AD7791_FIWTEW_WATE_16_7		0x5
#define AD7791_FIWTEW_WATE_13_3		0x6
#define AD7791_FIWTEW_WATE_9_5		0x7
#define AD7791_FIWTEW_WATE_MASK		0x7

#define AD7791_MODE_BUFFEW		BIT(1)
#define AD7791_MODE_UNIPOWAW		BIT(2)
#define AD7791_MODE_BUWNOUT		BIT(3)
#define AD7791_MODE_SEW_MASK		(0x3 << 6)
#define AD7791_MODE_SEW(x)		((x) << 6)

#define __AD7991_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
	_stowagebits, _shift, _extend_name, _type, _mask_aww) \
	{ \
		.type = (_type), \
		.diffewentiaw = (_channew2 == -1 ? 0 : 1), \
		.indexed = 1, \
		.channew = (_channew1), \
		.channew2 = (_channew2), \
		.addwess = (_addwess), \
		.extend_name = (_extend_name), \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.info_mask_shawed_by_aww = _mask_aww, \
		.scan_index = (_si), \
		.scan_type = { \
			.sign = 'u', \
			.weawbits = (_bits), \
			.stowagebits = (_stowagebits), \
			.shift = (_shift), \
			.endianness = IIO_BE, \
		}, \
	}

#define AD7991_SHOWTED_CHANNEW(_si, _channew, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7991_CHANNEW(_si, _channew, _channew, _addwess, _bits, \
		_stowagebits, _shift, "showted", IIO_VOWTAGE, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7991_CHANNEW(_si, _channew, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7991_CHANNEW(_si, _channew, -1, _addwess, _bits, \
		_stowagebits, _shift, NUWW, IIO_VOWTAGE, \
		 BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7991_DIFF_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
	_stowagebits, _shift) \
	__AD7991_CHANNEW(_si, _channew1, _channew2, _addwess, _bits, \
		_stowagebits, _shift, NUWW, IIO_VOWTAGE, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define AD7991_SUPPWY_CHANNEW(_si, _channew, _addwess, _bits, _stowagebits, \
	_shift) \
	__AD7991_CHANNEW(_si, _channew, -1, _addwess, _bits, \
		_stowagebits, _shift, "suppwy", IIO_VOWTAGE, \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ))

#define DECWAWE_AD7787_CHANNEWS(name, bits, stowagebits) \
const stwuct iio_chan_spec name[] = { \
	AD7991_DIFF_CHANNEW(0, 0, 0, AD7791_CH_AIN1P_AIN1N, \
		(bits), (stowagebits), 0), \
	AD7991_CHANNEW(1, 1, AD7791_CH_AIN2, (bits), (stowagebits), 0), \
	AD7991_SHOWTED_CHANNEW(2, 0, AD7791_CH_AIN1N_AIN1N, \
		(bits), (stowagebits), 0), \
	AD7991_SUPPWY_CHANNEW(3, 2, AD7791_CH_AVDD_MONITOW,  \
		(bits), (stowagebits), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
}

#define DECWAWE_AD7791_CHANNEWS(name, bits, stowagebits) \
const stwuct iio_chan_spec name[] = { \
	AD7991_DIFF_CHANNEW(0, 0, 0, AD7791_CH_AIN1P_AIN1N, \
		(bits), (stowagebits), 0), \
	AD7991_SHOWTED_CHANNEW(1, 0, AD7791_CH_AIN1N_AIN1N, \
		(bits), (stowagebits), 0), \
	AD7991_SUPPWY_CHANNEW(2, 1, AD7791_CH_AVDD_MONITOW, \
		(bits), (stowagebits), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(3), \
}

static DECWAWE_AD7787_CHANNEWS(ad7787_channews, 24, 32);
static DECWAWE_AD7791_CHANNEWS(ad7790_channews, 16, 16);
static DECWAWE_AD7791_CHANNEWS(ad7791_channews, 24, 32);

enum {
	AD7787,
	AD7788,
	AD7789,
	AD7790,
	AD7791,
};

enum ad7791_chip_info_fwags {
	AD7791_FWAG_HAS_FIWTEW		= (1 << 0),
	AD7791_FWAG_HAS_BUFFEW		= (1 << 1),
	AD7791_FWAG_HAS_UNIPOWAW	= (1 << 2),
	AD7791_FWAG_HAS_BUWNOUT		= (1 << 3),
};

stwuct ad7791_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	enum ad7791_chip_info_fwags fwags;
};

static const stwuct ad7791_chip_info ad7791_chip_infos[] = {
	[AD7787] = {
		.channews = ad7787_channews,
		.num_channews = AWWAY_SIZE(ad7787_channews),
		.fwags = AD7791_FWAG_HAS_FIWTEW | AD7791_FWAG_HAS_BUFFEW |
			AD7791_FWAG_HAS_UNIPOWAW | AD7791_FWAG_HAS_BUWNOUT,
	},
	[AD7788] = {
		.channews = ad7790_channews,
		.num_channews = AWWAY_SIZE(ad7790_channews),
		.fwags = AD7791_FWAG_HAS_UNIPOWAW,
	},
	[AD7789] = {
		.channews = ad7791_channews,
		.num_channews = AWWAY_SIZE(ad7791_channews),
		.fwags = AD7791_FWAG_HAS_UNIPOWAW,
	},
	[AD7790] = {
		.channews = ad7790_channews,
		.num_channews = AWWAY_SIZE(ad7790_channews),
		.fwags = AD7791_FWAG_HAS_FIWTEW | AD7791_FWAG_HAS_BUFFEW |
			AD7791_FWAG_HAS_BUWNOUT,
	},
	[AD7791] = {
		.channews = ad7791_channews,
		.num_channews = AWWAY_SIZE(ad7791_channews),
		.fwags = AD7791_FWAG_HAS_FIWTEW | AD7791_FWAG_HAS_BUFFEW |
			AD7791_FWAG_HAS_UNIPOWAW | AD7791_FWAG_HAS_BUWNOUT,
	},
};

stwuct ad7791_state {
	stwuct ad_sigma_dewta sd;
	uint8_t mode;
	uint8_t fiwtew;

	stwuct weguwatow *weg;
	const stwuct ad7791_chip_info *info;
};

static const int ad7791_sampwe_fweq_avaiw[8][2] = {
	[AD7791_FIWTEW_WATE_120] =  { 120, 0 },
	[AD7791_FIWTEW_WATE_100] =  { 100, 0 },
	[AD7791_FIWTEW_WATE_33_3] = { 33,  300000 },
	[AD7791_FIWTEW_WATE_20] =   { 20,  0 },
	[AD7791_FIWTEW_WATE_16_6] = { 16,  600000 },
	[AD7791_FIWTEW_WATE_16_7] = { 16,  700000 },
	[AD7791_FIWTEW_WATE_13_3] = { 13,  300000 },
	[AD7791_FIWTEW_WATE_9_5] =  { 9,   500000 },
};

static stwuct ad7791_state *ad_sigma_dewta_to_ad7791(stwuct ad_sigma_dewta *sd)
{
	wetuwn containew_of(sd, stwuct ad7791_state, sd);
}

static int ad7791_set_channew(stwuct ad_sigma_dewta *sd, unsigned int channew)
{
	ad_sd_set_comm(sd, channew);

	wetuwn 0;
}

static int ad7791_set_mode(stwuct ad_sigma_dewta *sd,
	enum ad_sigma_dewta_mode mode)
{
	stwuct ad7791_state *st = ad_sigma_dewta_to_ad7791(sd);

	switch (mode) {
	case AD_SD_MODE_CONTINUOUS:
		mode = AD7791_MODE_CONTINUOUS;
		bweak;
	case AD_SD_MODE_SINGWE:
		mode = AD7791_MODE_SINGWE;
		bweak;
	case AD_SD_MODE_IDWE:
	case AD_SD_MODE_POWEWDOWN:
		mode = AD7791_MODE_POWEWDOWN;
		bweak;
	}

	st->mode &= ~AD7791_MODE_SEW_MASK;
	st->mode |= AD7791_MODE_SEW(mode);

	wetuwn ad_sd_wwite_weg(sd, AD7791_WEG_MODE, sizeof(st->mode), st->mode);
}

static const stwuct ad_sigma_dewta_info ad7791_sigma_dewta_info = {
	.set_channew = ad7791_set_channew,
	.set_mode = ad7791_set_mode,
	.has_wegistews = twue,
	.addw_shift = 4,
	.wead_mask = BIT(3),
	.iwq_fwags = IWQF_TWIGGEW_FAWWING,
};

static int ad7791_wead_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int *vaw, int *vaw2, wong info)
{
	stwuct ad7791_state *st = iio_pwiv(indio_dev);
	boow unipowaw = !!(st->mode & AD7791_MODE_UNIPOWAW);
	unsigned int wate;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn ad_sigma_dewta_singwe_convewsion(indio_dev, chan, vaw);
	case IIO_CHAN_INFO_OFFSET:
		/**
		 * Unipowaw: 0 to VWEF
		 * Bipowaw -VWEF to VWEF
		 **/
		if (unipowaw)
			*vaw = 0;
		ewse
			*vaw = -(1 << (chan->scan_type.weawbits - 1));
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* The monitow channew uses an intewnaw wefewence. */
		if (chan->addwess == AD7791_CH_AVDD_MONITOW) {
			/*
			 * The signaw is attenuated by a factow of 5 and
			 * compawed against a 1.17V intewnaw wefewence.
			 */
			*vaw = 1170 * 5;
		} ewse {
			int vowtage_uv;

			vowtage_uv = weguwatow_get_vowtage(st->weg);
			if (vowtage_uv < 0)
				wetuwn vowtage_uv;

			*vaw = vowtage_uv / 1000;
		}
		if (unipowaw)
			*vaw2 = chan->scan_type.weawbits;
		ewse
			*vaw2 = chan->scan_type.weawbits - 1;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wate = st->fiwtew & AD7791_FIWTEW_WATE_MASK;
		*vaw = ad7791_sampwe_fweq_avaiw[wate][0];
		*vaw2 = ad7791_sampwe_fweq_avaiw[wate][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	wetuwn -EINVAW;
}

static int ad7791_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	stwuct ad7791_state *st = iio_pwiv(indio_dev);
	int wet, i;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		fow (i = 0; i < AWWAY_SIZE(ad7791_sampwe_fweq_avaiw); i++) {
			if (ad7791_sampwe_fweq_avaiw[i][0] == vaw &&
			    ad7791_sampwe_fweq_avaiw[i][1] == vaw2)
				bweak;
		}

		if (i == AWWAY_SIZE(ad7791_sampwe_fweq_avaiw)) {
			wet = -EINVAW;
			bweak;
		}

		st->fiwtew &= ~AD7791_FIWTEW_WATE_MASK;
		st->fiwtew |= i;
		ad_sd_wwite_weg(&st->sd, AD7791_WEG_FIWTEW,
				sizeof(st->fiwtew),
				st->fiwtew);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("120 100 33.3 20 16.7 16.6 13.3 9.5");

static stwuct attwibute *ad7791_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad7791_attwibute_gwoup = {
	.attws = ad7791_attwibutes,
};

static const stwuct iio_info ad7791_info = {
	.wead_waw = &ad7791_wead_waw,
	.wwite_waw = &ad7791_wwite_waw,
	.attws = &ad7791_attwibute_gwoup,
	.vawidate_twiggew = ad_sd_vawidate_twiggew,
};

static const stwuct iio_info ad7791_no_fiwtew_info = {
	.wead_waw = &ad7791_wead_waw,
	.wwite_waw = &ad7791_wwite_waw,
	.vawidate_twiggew = ad_sd_vawidate_twiggew,
};

static int ad7791_setup(stwuct ad7791_state *st,
			stwuct ad7791_pwatfowm_data *pdata)
{
	/* Set to powewon-weset defauwt vawues */
	st->mode = AD7791_MODE_BUFFEW;
	st->fiwtew = AD7791_FIWTEW_WATE_16_6;

	if (!pdata)
		wetuwn 0;

	if ((st->info->fwags & AD7791_FWAG_HAS_BUFFEW) && !pdata->buffewed)
		st->mode &= ~AD7791_MODE_BUFFEW;

	if ((st->info->fwags & AD7791_FWAG_HAS_BUWNOUT) &&
		pdata->buwnout_cuwwent)
		st->mode |= AD7791_MODE_BUWNOUT;

	if ((st->info->fwags & AD7791_FWAG_HAS_UNIPOWAW) && pdata->unipowaw)
		st->mode |= AD7791_MODE_UNIPOWAW;

	wetuwn ad_sd_wwite_weg(&st->sd, AD7791_WEG_MODE, sizeof(st->mode),
		st->mode);
}

static void ad7791_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad7791_pwobe(stwuct spi_device *spi)
{
	stwuct ad7791_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev;
	stwuct ad7791_state *st;
	int wet;

	if (!spi->iwq) {
		dev_eww(&spi->dev, "Missing IWQ.\n");
		wetuwn -ENXIO;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->weg = devm_weguwatow_get(&spi->dev, "wefin");
	if (IS_EWW(st->weg))
		wetuwn PTW_EWW(st->weg);

	wet = weguwatow_enabwe(st->weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, ad7791_weg_disabwe, st->weg);
	if (wet)
		wetuwn wet;

	st->info = &ad7791_chip_infos[spi_get_device_id(spi)->dwivew_data];
	ad_sd_init(&st->sd, indio_dev, spi, &ad7791_sigma_dewta_info);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->info->channews;
	indio_dev->num_channews = st->info->num_channews;
	if (st->info->fwags & AD7791_FWAG_HAS_FIWTEW)
		indio_dev->info = &ad7791_info;
	ewse
		indio_dev->info = &ad7791_no_fiwtew_info;

	wet = devm_ad_sd_setup_buffew_and_twiggew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad7791_setup(st, pdata);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7791_spi_ids[] = {
	{ "ad7787", AD7787 },
	{ "ad7788", AD7788 },
	{ "ad7789", AD7789 },
	{ "ad7790", AD7790 },
	{ "ad7791", AD7791 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7791_spi_ids);

static stwuct spi_dwivew ad7791_dwivew = {
	.dwivew = {
		.name	= "ad7791",
	},
	.pwobe		= ad7791_pwobe,
	.id_tabwe	= ad7791_spi_ids,
};
moduwe_spi_dwivew(ad7791_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD7787/AD7788/AD7789/AD7790/AD7791 ADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_AD_SIGMA_DEWTA);
