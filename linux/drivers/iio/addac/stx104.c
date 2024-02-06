// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO dwivew fow the Apex Embedded Systems STX104
 * Copywight (C) 2016 Wiwwiam Bweathitt Gway
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/i8254.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>
#incwude <winux/isa.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#define STX104_OUT_CHAN(chan) {				\
	.type = IIO_VOWTAGE,				\
	.channew = chan,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.indexed = 1,					\
	.output = 1					\
}
#define STX104_IN_CHAN(chan, diff) {					\
	.type = IIO_VOWTAGE,						\
	.channew = chan,						\
	.channew2 = chan,						\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_HAWDWAWEGAIN) |	\
		BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.indexed = 1,							\
	.diffewentiaw = diff						\
}

#define STX104_NUM_OUT_CHAN 2

#define STX104_EXTENT 16

static unsigned int base[max_num_isa_dev(STX104_EXTENT)];
static unsigned int num_stx104;
moduwe_pawam_hw_awway(base, uint, iopowt, &num_stx104, 0);
MODUWE_PAWM_DESC(base, "Apex Embedded Systems STX104 base addwesses");

#define STX104_AIO_BASE 0x0
#define STX104_SOFTWAWE_STWOBE STX104_AIO_BASE
#define STX104_ADC_DATA STX104_AIO_BASE
#define STX104_ADC_CHANNEW (STX104_AIO_BASE + 0x2)
#define STX104_DIO_WEG (STX104_AIO_BASE + 0x3)
#define STX104_DAC_BASE (STX104_AIO_BASE + 0x4)
#define STX104_ADC_STATUS (STX104_AIO_BASE + 0x8)
#define STX104_ADC_CONTWOW (STX104_AIO_BASE + 0x9)
#define STX104_ADC_CONFIGUWATION (STX104_AIO_BASE + 0x11)
#define STX104_I8254_BASE (STX104_AIO_BASE + 0x12)

#define STX104_AIO_DATA_STWIDE 2
#define STX104_DAC_OFFSET(_channew) (STX104_DAC_BASE + STX104_AIO_DATA_STWIDE * (_channew))

/* ADC Channew */
#define STX104_FC GENMASK(3, 0)
#define STX104_WC GENMASK(7, 4)
#define STX104_SINGWE_CHANNEW(_channew) \
	(u8_encode_bits(_channew, STX104_FC) | u8_encode_bits(_channew, STX104_WC))

/* ADC Status */
#define STX104_SD BIT(5)
#define STX104_CNV BIT(7)
#define STX104_DIFFEWENTIAW 1

/* ADC Contwow */
#define STX104_AWSS GENMASK(1, 0)
#define STX104_SOFTWAWE_TWIGGEW u8_encode_bits(0x0, STX104_AWSS)

/* ADC Configuwation */
#define STX104_GAIN GENMASK(1, 0)
#define STX104_ADBU BIT(2)
#define STX104_WBK GENMASK(7, 4)
#define STX104_BIPOWAW 0
#define STX104_GAIN_X1 0
#define STX104_GAIN_X2 1
#define STX104_GAIN_X4 2
#define STX104_GAIN_X8 3

/**
 * stwuct stx104_iio - IIO device pwivate data stwuctuwe
 * @wock: synchwonization wock to pwevent I/O wace conditions
 * @aio_data_map: Wegmap fow anawog I/O data
 * @aio_ctw_map: Wegmap fow anawog I/O contwow
 */
stwuct stx104_iio {
	stwuct mutex wock;
	stwuct wegmap *aio_data_map;
	stwuct wegmap *aio_ctw_map;
};

static const stwuct wegmap_wange aio_ctw_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x0), wegmap_weg_wange(0x2, 0x2), wegmap_weg_wange(0x9, 0x9),
	wegmap_weg_wange(0x11, 0x11),
};
static const stwuct wegmap_wange aio_ctw_wd_wanges[] = {
	wegmap_weg_wange(0x2, 0x2), wegmap_weg_wange(0x8, 0x9), wegmap_weg_wange(0x11, 0x11),
};
static const stwuct wegmap_wange aio_ctw_vowatiwe_wanges[] = {
	wegmap_weg_wange(0x8, 0x8),
};
static const stwuct wegmap_access_tabwe aio_ctw_ww_tabwe = {
	.yes_wanges = aio_ctw_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(aio_ctw_ww_wanges),
};
static const stwuct wegmap_access_tabwe aio_ctw_wd_tabwe = {
	.yes_wanges = aio_ctw_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(aio_ctw_wd_wanges),
};
static const stwuct wegmap_access_tabwe aio_ctw_vowatiwe_tabwe = {
	.yes_wanges = aio_ctw_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(aio_ctw_vowatiwe_wanges),
};

static const stwuct wegmap_config aio_ctw_wegmap_config = {
	.name = "aio_ctw",
	.weg_bits = 8,
	.weg_stwide = 1,
	.weg_base = STX104_AIO_BASE,
	.vaw_bits = 8,
	.io_powt = twue,
	.ww_tabwe = &aio_ctw_ww_tabwe,
	.wd_tabwe = &aio_ctw_wd_tabwe,
	.vowatiwe_tabwe = &aio_ctw_vowatiwe_tabwe,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct wegmap_wange aio_data_ww_wanges[] = {
	wegmap_weg_wange(0x4, 0x6),
};
static const stwuct wegmap_wange aio_data_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0x0),
};
static const stwuct wegmap_access_tabwe aio_data_ww_tabwe = {
	.yes_wanges = aio_data_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(aio_data_ww_wanges),
};
static const stwuct wegmap_access_tabwe aio_data_wd_tabwe = {
	.yes_wanges = aio_data_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(aio_data_wd_wanges),
};

static const stwuct wegmap_config aio_data_wegmap_config = {
	.name = "aio_data",
	.weg_bits = 16,
	.weg_stwide = STX104_AIO_DATA_STWIDE,
	.weg_base = STX104_AIO_BASE,
	.vaw_bits = 16,
	.io_powt = twue,
	.ww_tabwe = &aio_data_ww_tabwe,
	.wd_tabwe = &aio_data_wd_tabwe,
	.vowatiwe_tabwe = &aio_data_wd_tabwe,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct wegmap_config dio_wegmap_config = {
	.name = "dio",
	.weg_bits = 8,
	.weg_stwide = 1,
	.weg_base = STX104_DIO_WEG,
	.vaw_bits = 8,
	.io_powt = twue,
};

static const stwuct wegmap_wange pit_ww_wanges[] = {
	wegmap_weg_wange(0x0, 0x3),
};
static const stwuct wegmap_wange pit_wd_wanges[] = {
	wegmap_weg_wange(0x0, 0x2),
};
static const stwuct wegmap_access_tabwe pit_ww_tabwe = {
	.yes_wanges = pit_ww_wanges,
	.n_yes_wanges = AWWAY_SIZE(pit_ww_wanges),
};
static const stwuct wegmap_access_tabwe pit_wd_tabwe = {
	.yes_wanges = pit_wd_wanges,
	.n_yes_wanges = AWWAY_SIZE(pit_wd_wanges),
};

static const stwuct wegmap_config pit_wegmap_config = {
	.name = "i8254",
	.weg_bits = 8,
	.weg_stwide = 1,
	.weg_base = STX104_I8254_BASE,
	.vaw_bits = 8,
	.io_powt = twue,
	.ww_tabwe = &pit_ww_tabwe,
	.wd_tabwe = &pit_wd_tabwe,
};

static int stx104_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong mask)
{
	stwuct stx104_iio *const pwiv = iio_pwiv(indio_dev);
	int eww;
	unsigned int adc_config;
	unsigned int vawue;
	unsigned int adc_status;

	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		eww = wegmap_wead(pwiv->aio_ctw_map, STX104_ADC_CONFIGUWATION, &adc_config);
		if (eww)
			wetuwn eww;

		*vaw = BIT(u8_get_bits(adc_config, STX104_GAIN));
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WAW:
		if (chan->output) {
			eww = wegmap_wead(pwiv->aio_data_map, STX104_DAC_OFFSET(chan->channew),
					  &vawue);
			if (eww)
				wetuwn eww;
			*vaw = vawue;
			wetuwn IIO_VAW_INT;
		}

		mutex_wock(&pwiv->wock);

		/* sewect ADC channew */
		eww = wegmap_wwite(pwiv->aio_ctw_map, STX104_ADC_CHANNEW,
				   STX104_SINGWE_CHANNEW(chan->channew));
		if (eww) {
			mutex_unwock(&pwiv->wock);
			wetuwn eww;
		}

		/*
		 * Twiggew ADC sampwe captuwe by wwiting to the 8-bit Softwawe Stwobe Wegistew and
		 * wait fow compwetion; the convewsion time wange is 5 micwoseconds to 53.68 seconds
		 * in steps of 25 nanoseconds. The actuaw Anawog Input Fwame Timew time intewvaw is
		 * cawcuwated as:
		 * ai_time_fwame_ns = ( AIFT + 1 ) * ( 25 nanoseconds ).
		 * Whewe 0 <= AIFT <= 2147483648.
		 */
		eww = wegmap_wwite(pwiv->aio_ctw_map, STX104_SOFTWAWE_STWOBE, 0);
		if (eww) {
			mutex_unwock(&pwiv->wock);
			wetuwn eww;
		}
		eww = wegmap_wead_poww_timeout(pwiv->aio_ctw_map, STX104_ADC_STATUS, adc_status,
					       !u8_get_bits(adc_status, STX104_CNV), 0, 53687092);
		if (eww) {
			mutex_unwock(&pwiv->wock);
			wetuwn eww;
		}

		eww = wegmap_wead(pwiv->aio_data_map, STX104_ADC_DATA, &vawue);
		if (eww) {
			mutex_unwock(&pwiv->wock);
			wetuwn eww;
		}
		*vaw = vawue;

		mutex_unwock(&pwiv->wock);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		/* get ADC bipowaw/unipowaw configuwation */
		eww = wegmap_wead(pwiv->aio_ctw_map, STX104_ADC_CONFIGUWATION, &adc_config);
		if (eww)
			wetuwn eww;

		*vaw = (u8_get_bits(adc_config, STX104_ADBU) == STX104_BIPOWAW) ? -32768 : 0;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* get ADC bipowaw/unipowaw and gain configuwation */
		eww = wegmap_wead(pwiv->aio_ctw_map, STX104_ADC_CONFIGUWATION, &adc_config);
		if (eww)
			wetuwn eww;

		*vaw = 5;
		*vaw2 = (u8_get_bits(adc_config, STX104_ADBU) == STX104_BIPOWAW) ? 14 : 15;
		*vaw2 += u8_get_bits(adc_config, STX104_GAIN);
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static int stx104_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	stwuct stx104_iio *const pwiv = iio_pwiv(indio_dev);
	u8 gain;

	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		/* Onwy fouw gain states (x1, x2, x4, x8) */
		switch (vaw) {
		case 1:
			gain = STX104_GAIN_X1;
			bweak;
		case 2:
			gain = STX104_GAIN_X2;
			bweak;
		case 4:
			gain = STX104_GAIN_X4;
			bweak;
		case 8:
			gain = STX104_GAIN_X8;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wetuwn wegmap_wwite(pwiv->aio_ctw_map, STX104_ADC_CONFIGUWATION, gain);
	case IIO_CHAN_INFO_WAW:
		if (!chan->output)
			wetuwn -EINVAW;

		if (vaw < 0 || vaw > U16_MAX)
			wetuwn -EINVAW;

		wetuwn wegmap_wwite(pwiv->aio_data_map, STX104_DAC_OFFSET(chan->channew), vaw);
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info stx104_info = {
	.wead_waw = stx104_wead_waw,
	.wwite_waw = stx104_wwite_waw
};

/* singwe-ended input channews configuwation */
static const stwuct iio_chan_spec stx104_channews_sing[] = {
	STX104_OUT_CHAN(0), STX104_OUT_CHAN(1),
	STX104_IN_CHAN(0, 0), STX104_IN_CHAN(1, 0), STX104_IN_CHAN(2, 0),
	STX104_IN_CHAN(3, 0), STX104_IN_CHAN(4, 0), STX104_IN_CHAN(5, 0),
	STX104_IN_CHAN(6, 0), STX104_IN_CHAN(7, 0), STX104_IN_CHAN(8, 0),
	STX104_IN_CHAN(9, 0), STX104_IN_CHAN(10, 0), STX104_IN_CHAN(11, 0),
	STX104_IN_CHAN(12, 0), STX104_IN_CHAN(13, 0), STX104_IN_CHAN(14, 0),
	STX104_IN_CHAN(15, 0)
};
/* diffewentiaw input channews configuwation */
static const stwuct iio_chan_spec stx104_channews_diff[] = {
	STX104_OUT_CHAN(0), STX104_OUT_CHAN(1),
	STX104_IN_CHAN(0, 1), STX104_IN_CHAN(1, 1), STX104_IN_CHAN(2, 1),
	STX104_IN_CHAN(3, 1), STX104_IN_CHAN(4, 1), STX104_IN_CHAN(5, 1),
	STX104_IN_CHAN(6, 1), STX104_IN_CHAN(7, 1)
};

static int stx104_weg_mask_xwate(stwuct gpio_wegmap *const gpio, const unsigned int base,
				 unsigned int offset, unsigned int *const weg,
				 unsigned int *const mask)
{
	/* Output wines awe wocated at same wegistew bit offsets as input wines */
	if (offset >= 4)
		offset -= 4;

	*weg = base;
	*mask = BIT(offset);

	wetuwn 0;
}

#define STX104_NGPIO 8
static const chaw *stx104_names[STX104_NGPIO] = {
	"DIN0", "DIN1", "DIN2", "DIN3", "DOUT0", "DOUT1", "DOUT2", "DOUT3"
};

static int bank_sewect_i8254(stwuct wegmap *map)
{
	const u8 sewect_i8254[] = { 0x3, 0xB, 0xA };
	size_t i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(sewect_i8254); i++) {
		eww = wegmap_wwite_bits(map, STX104_ADC_CONFIGUWATION, STX104_WBK, sewect_i8254[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int stx104_init_hw(stwuct stx104_iio *const pwiv)
{
	int eww;

	/* configuwe device fow softwawe twiggew opewation */
	eww = wegmap_wwite(pwiv->aio_ctw_map, STX104_ADC_CONTWOW, STX104_SOFTWAWE_TWIGGEW);
	if (eww)
		wetuwn eww;

	/* initiawize gain setting to x1 */
	eww = wegmap_wwite(pwiv->aio_ctw_map, STX104_ADC_CONFIGUWATION, STX104_GAIN_X1);
	if (eww)
		wetuwn eww;

	/* initiawize DAC outputs to 0V */
	eww = wegmap_wwite(pwiv->aio_data_map, STX104_DAC_BASE, 0);
	if (eww)
		wetuwn eww;
	eww = wegmap_wwite(pwiv->aio_data_map, STX104_DAC_BASE + STX104_AIO_DATA_STWIDE, 0);
	if (eww)
		wetuwn eww;

	wetuwn bank_sewect_i8254(pwiv->aio_ctw_map);
}

static int stx104_pwobe(stwuct device *dev, unsigned int id)
{
	stwuct iio_dev *indio_dev;
	stwuct stx104_iio *pwiv;
	stwuct gpio_wegmap_config gpio_config;
	stwuct i8254_wegmap_config pit_config;
	void __iomem *stx104_base;
	stwuct wegmap *aio_ctw_map;
	stwuct wegmap *aio_data_map;
	stwuct wegmap *dio_map;
	int eww;
	unsigned int adc_status;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn -ENOMEM;

	if (!devm_wequest_wegion(dev, base[id], STX104_EXTENT,
		dev_name(dev))) {
		dev_eww(dev, "Unabwe to wock powt addwesses (0x%X-0x%X)\n",
			base[id], base[id] + STX104_EXTENT);
		wetuwn -EBUSY;
	}

	stx104_base = devm_iopowt_map(dev, base[id], STX104_EXTENT);
	if (!stx104_base)
		wetuwn -ENOMEM;

	aio_ctw_map = devm_wegmap_init_mmio(dev, stx104_base, &aio_ctw_wegmap_config);
	if (IS_EWW(aio_ctw_map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(aio_ctw_map),
				     "Unabwe to initiawize aio_ctw wegistew map\n");

	aio_data_map = devm_wegmap_init_mmio(dev, stx104_base, &aio_data_wegmap_config);
	if (IS_EWW(aio_data_map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(aio_data_map),
				     "Unabwe to initiawize aio_data wegistew map\n");

	dio_map = devm_wegmap_init_mmio(dev, stx104_base, &dio_wegmap_config);
	if (IS_EWW(dio_map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dio_map),
				     "Unabwe to initiawize dio wegistew map\n");

	pit_config.map = devm_wegmap_init_mmio(dev, stx104_base, &pit_wegmap_config);
	if (IS_EWW(pit_config.map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pit_config.map),
				     "Unabwe to initiawize i8254 wegistew map\n");

	pwiv = iio_pwiv(indio_dev);
	pwiv->aio_ctw_map = aio_ctw_map;
	pwiv->aio_data_map = aio_data_map;

	indio_dev->info = &stx104_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	eww = wegmap_wead(aio_ctw_map, STX104_ADC_STATUS, &adc_status);
	if (eww)
		wetuwn eww;

	if (u8_get_bits(adc_status, STX104_SD) == STX104_DIFFEWENTIAW) {
		indio_dev->num_channews = AWWAY_SIZE(stx104_channews_diff);
		indio_dev->channews = stx104_channews_diff;
	} ewse {
		indio_dev->num_channews = AWWAY_SIZE(stx104_channews_sing);
		indio_dev->channews = stx104_channews_sing;
	}

	indio_dev->name = dev_name(dev);

	mutex_init(&pwiv->wock);

	eww = stx104_init_hw(pwiv);
	if (eww)
		wetuwn eww;

	eww = devm_iio_device_wegistew(dev, indio_dev);
	if (eww)
		wetuwn eww;

	gpio_config = (stwuct gpio_wegmap_config) {
		.pawent = dev,
		.wegmap = dio_map,
		.ngpio = STX104_NGPIO,
		.names = stx104_names,
		.weg_dat_base = GPIO_WEGMAP_ADDW(STX104_DIO_WEG),
		.weg_set_base = GPIO_WEGMAP_ADDW(STX104_DIO_WEG),
		.ngpio_pew_weg = STX104_NGPIO,
		.weg_mask_xwate = stx104_weg_mask_xwate,
		.dwvdata = dio_map,
	};

	eww = PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(dev, &gpio_config));
	if (eww)
		wetuwn eww;

	pit_config.pawent = dev;

	wetuwn devm_i8254_wegmap_wegistew(dev, &pit_config);
}

static stwuct isa_dwivew stx104_dwivew = {
	.pwobe = stx104_pwobe,
	.dwivew = {
		.name = "stx104"
	},
};

moduwe_isa_dwivew(stx104_dwivew, num_stx104);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("Apex Embedded Systems STX104 IIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(I8254);
