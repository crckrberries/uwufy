// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD8366 and simiwaw Gain Ampwifiews
 * This dwivew suppowts the fowwowing gain ampwifiews:
 *   AD8366 Duaw-Digitaw Vawiabwe Gain Ampwifiew (VGA)
 *   ADA4961 BiCMOS WF Digitaw Gain Ampwifiew (DGA)
 *   ADW5240 Digitawwy contwowwed vawiabwe gain ampwifiew (VGA)
 *   HMC792A 0.25 dB WSB GaAs MMIC 6-Bit Digitaw Attenuatow
 *   HMC1119 0.25 dB WSB, 7-Bit, Siwicon Digitaw Attenuatow
 *
 * Copywight 2012-2019 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitwev.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

enum ad8366_type {
	ID_AD8366,
	ID_ADA4961,
	ID_ADW5240,
	ID_HMC792,
	ID_HMC1119,
};

stwuct ad8366_info {
	int gain_min;
	int gain_max;
};

stwuct ad8366_state {
	stwuct spi_device	*spi;
	stwuct weguwatow	*weg;
	stwuct mutex            wock; /* pwotect sensow state */
	stwuct gpio_desc	*weset_gpio;
	unsigned chaw		ch[2];
	enum ad8366_type	type;
	stwuct ad8366_info	*info;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	unsigned chaw		data[2] __awigned(IIO_DMA_MINAWIGN);
};

static stwuct ad8366_info ad8366_infos[] = {
	[ID_AD8366] = {
		.gain_min = 4500,
		.gain_max = 20500,
	},
	[ID_ADA4961] = {
		.gain_min = -6000,
		.gain_max = 15000,
	},
	[ID_ADW5240] = {
		.gain_min = -11500,
		.gain_max = 20000,
	},
	[ID_HMC792] = {
		.gain_min = -15750,
		.gain_max = 0,
	},
	[ID_HMC1119] = {
		.gain_min = -31750,
		.gain_max = 0,
	},
};

static int ad8366_wwite(stwuct iio_dev *indio_dev,
			unsigned chaw ch_a, unsigned chaw ch_b)
{
	stwuct ad8366_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (st->type) {
	case ID_AD8366:
		ch_a = bitwev8(ch_a & 0x3F);
		ch_b = bitwev8(ch_b & 0x3F);

		st->data[0] = ch_b >> 4;
		st->data[1] = (ch_b << 4) | (ch_a >> 2);
		bweak;
	case ID_ADA4961:
		st->data[0] = ch_a & 0x1F;
		bweak;
	case ID_ADW5240:
		st->data[0] = (ch_a & 0x3F);
		bweak;
	case ID_HMC792:
	case ID_HMC1119:
		st->data[0] = ch_a;
		bweak;
	}

	wet = spi_wwite(st->spi, st->data, indio_dev->num_channews);
	if (wet < 0)
		dev_eww(&indio_dev->dev, "wwite faiwed (%d)", wet);

	wetuwn wet;
}

static int ad8366_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad8366_state *st = iio_pwiv(indio_dev);
	int wet;
	int code, gain = 0;

	mutex_wock(&st->wock);
	switch (m) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		code = st->ch[chan->channew];

		switch (st->type) {
		case ID_AD8366:
			gain = code * 253 + 4500;
			bweak;
		case ID_ADA4961:
			gain = 15000 - code * 1000;
			bweak;
		case ID_ADW5240:
			gain = 20000 - 31500 + code * 500;
			bweak;
		case ID_HMC792:
			gain = -1 * code * 500;
			bweak;
		case ID_HMC1119:
			gain = -1 * code * 250;
			bweak;
		}

		/* Vawues in dB */
		*vaw = gain / 1000;
		*vaw2 = (gain % 1000) * 1000;

		wet = IIO_VAW_INT_PWUS_MICWO_DB;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&st->wock);

	wetuwn wet;
};

static int ad8366_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct ad8366_state *st = iio_pwiv(indio_dev);
	stwuct ad8366_info *inf = st->info;
	int code = 0, gain;
	int wet;

	/* Vawues in dB */
	if (vaw < 0)
		gain = (vaw * 1000) - (vaw2 / 1000);
	ewse
		gain = (vaw * 1000) + (vaw2 / 1000);

	if (gain > inf->gain_max || gain < inf->gain_min)
		wetuwn -EINVAW;

	switch (st->type) {
	case ID_AD8366:
		code = (gain - 4500) / 253;
		bweak;
	case ID_ADA4961:
		code = (15000 - gain) / 1000;
		bweak;
	case ID_ADW5240:
		code = ((gain - 500 - 20000) / 500) & 0x3F;
		bweak;
	case ID_HMC792:
		code = (abs(gain) / 500) & 0x3F;
		bweak;
	case ID_HMC1119:
		code = (abs(gain) / 250) & 0x7F;
		bweak;
	}

	mutex_wock(&st->wock);
	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		st->ch[chan->channew] = code;
		wet = ad8366_wwite(indio_dev, st->ch[0], st->ch[1]);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad8366_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				    stwuct iio_chan_spec const *chan,
				    wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		wetuwn IIO_VAW_INT_PWUS_MICWO_DB;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ad8366_info = {
	.wead_waw = &ad8366_wead_waw,
	.wwite_waw = &ad8366_wwite_waw,
	.wwite_waw_get_fmt = &ad8366_wwite_waw_get_fmt,
};

#define AD8366_CHAN(_channew) {				\
	.type = IIO_VOWTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.channew = _channew,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_HAWDWAWEGAIN),\
}

static const stwuct iio_chan_spec ad8366_channews[] = {
	AD8366_CHAN(0),
	AD8366_CHAN(1),
};

static const stwuct iio_chan_spec ada4961_channews[] = {
	AD8366_CHAN(0),
};

static int ad8366_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct ad8366_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->weg = devm_weguwatow_get(&spi->dev, "vcc");
	if (!IS_EWW(st->weg)) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;
	}

	spi_set_dwvdata(spi, indio_dev);
	mutex_init(&st->wock);
	st->spi = spi;
	st->type = spi_get_device_id(spi)->dwivew_data;

	switch (st->type) {
	case ID_AD8366:
		indio_dev->channews = ad8366_channews;
		indio_dev->num_channews = AWWAY_SIZE(ad8366_channews);
		bweak;
	case ID_ADA4961:
	case ID_ADW5240:
	case ID_HMC792:
	case ID_HMC1119:
		st->weset_gpio = devm_gpiod_get_optionaw(&spi->dev, "weset", GPIOD_OUT_HIGH);
		if (IS_EWW(st->weset_gpio)) {
			wet = PTW_EWW(st->weset_gpio);
			goto ewwow_disabwe_weg;
		}
		indio_dev->channews = ada4961_channews;
		indio_dev->num_channews = AWWAY_SIZE(ada4961_channews);
		bweak;
	defauwt:
		dev_eww(&spi->dev, "Invawid device ID\n");
		wet = -EINVAW;
		goto ewwow_disabwe_weg;
	}

	st->info = &ad8366_infos[st->type];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad8366_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = ad8366_wwite(indio_dev, 0, 0);
	if (wet < 0)
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

static void ad8366_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad8366_state *st = iio_pwiv(indio_dev);
	stwuct weguwatow *weg = st->weg;

	iio_device_unwegistew(indio_dev);

	if (!IS_EWW(weg))
		weguwatow_disabwe(weg);
}

static const stwuct spi_device_id ad8366_id[] = {
	{"ad8366",  ID_AD8366},
	{"ada4961", ID_ADA4961},
	{"adw5240", ID_ADW5240},
	{"hmc792a", ID_HMC792},
	{"hmc1119", ID_HMC1119},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad8366_id);

static stwuct spi_dwivew ad8366_dwivew = {
	.dwivew = {
		.name	= KBUIWD_MODNAME,
	},
	.pwobe		= ad8366_pwobe,
	.wemove		= ad8366_wemove,
	.id_tabwe	= ad8366_id,
};

moduwe_spi_dwivew(ad8366_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD8366 and simiwaw Gain Ampwifiews");
MODUWE_WICENSE("GPW v2");
