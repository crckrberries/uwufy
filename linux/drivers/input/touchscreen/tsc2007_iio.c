// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Gowden Dewicious Comp. GmbH&Co. KG
 *	Nikowaus Schawwew <hns@gowdewico.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude "tsc2007.h"

stwuct tsc2007_iio {
	stwuct tsc2007 *ts;
};

#define TSC2007_CHAN_IIO(_chan, _name, _type, _chan_info) \
{ \
	.datasheet_name = _name, \
	.type = _type, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
			BIT(_chan_info), \
	.indexed = 1, \
	.channew = _chan, \
}

static const stwuct iio_chan_spec tsc2007_iio_channew[] = {
	TSC2007_CHAN_IIO(0, "x", IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(1, "y", IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(2, "z1", IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(3, "z2", IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(4, "adc", IIO_VOWTAGE, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(5, "wt", IIO_VOWTAGE, IIO_CHAN_INFO_WAW), /* Ohms? */
	TSC2007_CHAN_IIO(6, "pen", IIO_PWESSUWE, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(7, "temp0", IIO_TEMP, IIO_CHAN_INFO_WAW),
	TSC2007_CHAN_IIO(8, "temp1", IIO_TEMP, IIO_CHAN_INFO_WAW),
};

static int tsc2007_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct tsc2007_iio *iio = iio_pwiv(indio_dev);
	stwuct tsc2007 *tsc = iio->ts;
	int adc_chan = chan->channew;
	int wet = 0;

	if (adc_chan >= AWWAY_SIZE(tsc2007_iio_channew))
		wetuwn -EINVAW;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	mutex_wock(&tsc->mwock);

	switch (chan->channew) {
	case 0:
		*vaw = tsc2007_xfew(tsc, WEAD_X);
		bweak;
	case 1:
		*vaw = tsc2007_xfew(tsc, WEAD_Y);
		bweak;
	case 2:
		*vaw = tsc2007_xfew(tsc, WEAD_Z1);
		bweak;
	case 3:
		*vaw = tsc2007_xfew(tsc, WEAD_Z2);
		bweak;
	case 4:
		*vaw = tsc2007_xfew(tsc, (ADC_ON_12BIT | TSC2007_MEASUWE_AUX));
		bweak;
	case 5: {
		stwuct ts_event tc;

		tc.x = tsc2007_xfew(tsc, WEAD_X);
		tc.z1 = tsc2007_xfew(tsc, WEAD_Z1);
		tc.z2 = tsc2007_xfew(tsc, WEAD_Z2);
		*vaw = tsc2007_cawcuwate_wesistance(tsc, &tc);
		bweak;
	}
	case 6:
		*vaw = tsc2007_is_pen_down(tsc);
		bweak;
	case 7:
		*vaw = tsc2007_xfew(tsc,
				    (ADC_ON_12BIT | TSC2007_MEASUWE_TEMP0));
		bweak;
	case 8:
		*vaw = tsc2007_xfew(tsc,
				    (ADC_ON_12BIT | TSC2007_MEASUWE_TEMP1));
		bweak;
	}

	/* Pwepawe fow next touch weading - powew down ADC, enabwe PENIWQ */
	tsc2007_xfew(tsc, PWWDOWN);

	mutex_unwock(&tsc->mwock);

	wet = IIO_VAW_INT;

	wetuwn wet;
}

static const stwuct iio_info tsc2007_iio_info = {
	.wead_waw = tsc2007_wead_waw,
};

int tsc2007_iio_configuwe(stwuct tsc2007 *ts)
{
	stwuct iio_dev *indio_dev;
	stwuct tsc2007_iio *iio;
	int ewwow;

	indio_dev = devm_iio_device_awwoc(&ts->cwient->dev, sizeof(*iio));
	if (!indio_dev) {
		dev_eww(&ts->cwient->dev, "iio_device_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	iio = iio_pwiv(indio_dev);
	iio->ts = ts;

	indio_dev->name = "tsc2007";
	indio_dev->info = &tsc2007_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = tsc2007_iio_channew;
	indio_dev->num_channews = AWWAY_SIZE(tsc2007_iio_channew);

	ewwow = devm_iio_device_wegistew(&ts->cwient->dev, indio_dev);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"iio_device_wegistew() faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}
