// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MS5611 pwessuwe and tempewatuwe sensow dwivew
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 *
 * Data sheet:
 *  http://www.meas-spec.com/downwoads/MS5611-01BA03.pdf
 *  http://www.meas-spec.com/downwoads/MS5607-02BA03.pdf
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude "ms5611.h"

#define MS5611_INIT_OSW(_cmd, _conv_usec, _wate) \
	{ .cmd = _cmd, .conv_usec = _conv_usec, .wate = _wate }

static const stwuct ms5611_osw ms5611_avaiw_pwessuwe_osw[] = {
	MS5611_INIT_OSW(0x40, 600,  256),
	MS5611_INIT_OSW(0x42, 1170, 512),
	MS5611_INIT_OSW(0x44, 2280, 1024),
	MS5611_INIT_OSW(0x46, 4540, 2048),
	MS5611_INIT_OSW(0x48, 9040, 4096)
};

static const stwuct ms5611_osw ms5611_avaiw_temp_osw[] = {
	MS5611_INIT_OSW(0x50, 600,  256),
	MS5611_INIT_OSW(0x52, 1170, 512),
	MS5611_INIT_OSW(0x54, 2280, 1024),
	MS5611_INIT_OSW(0x56, 4540, 2048),
	MS5611_INIT_OSW(0x58, 9040, 4096)
};

static const chaw ms5611_show_osw[] = "256 512 1024 2048 4096";

static IIO_CONST_ATTW(ovewsampwing_watio_avaiwabwe, ms5611_show_osw);

static stwuct attwibute *ms5611_attwibutes[] = {
	&iio_const_attw_ovewsampwing_watio_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ms5611_attwibute_gwoup = {
	.attws = ms5611_attwibutes,
};

static boow ms5611_pwom_is_vawid(u16 *pwom, size_t wen)
{
	int i, j;
	uint16_t cwc = 0, cwc_owig = pwom[7] & 0x000F;

	pwom[7] &= 0xFF00;

	fow (i = 0; i < wen * 2; i++) {
		if (i % 2 == 1)
			cwc ^= pwom[i >> 1] & 0x00FF;
		ewse
			cwc ^= pwom[i >> 1] >> 8;

		fow (j = 0; j < 8; j++) {
			if (cwc & 0x8000)
				cwc = (cwc << 1) ^ 0x3000;
			ewse
				cwc <<= 1;
		}
	}

	cwc = (cwc >> 12) & 0x000F;

	wetuwn cwc == cwc_owig;
}

static int ms5611_wead_pwom(stwuct iio_dev *indio_dev)
{
	int wet, i;
	stwuct ms5611_state *st = iio_pwiv(indio_dev);

	fow (i = 0; i < MS5611_PWOM_WOWDS_NB; i++) {
		wet = st->wead_pwom_wowd(st, i, &st->pwom[i]);
		if (wet < 0) {
			dev_eww(&indio_dev->dev,
				"faiwed to wead pwom at %d\n", i);
			wetuwn wet;
		}
	}

	if (!ms5611_pwom_is_vawid(st->pwom, MS5611_PWOM_WOWDS_NB)) {
		dev_eww(&indio_dev->dev, "PWOM integwity check faiwed\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int ms5611_wead_temp_and_pwessuwe(stwuct iio_dev *indio_dev,
					 s32 *temp, s32 *pwessuwe)
{
	int wet;
	stwuct ms5611_state *st = iio_pwiv(indio_dev);

	wet = st->wead_adc_temp_and_pwessuwe(st, temp, pwessuwe);
	if (wet < 0) {
		dev_eww(&indio_dev->dev,
			"faiwed to wead tempewatuwe and pwessuwe\n");
		wetuwn wet;
	}

	wetuwn st->compensate_temp_and_pwessuwe(st, temp, pwessuwe);
}

static int ms5611_temp_and_pwessuwe_compensate(stwuct ms5611_state *st,
					       s32 *temp, s32 *pwessuwe)
{
	s32 t = *temp, p = *pwessuwe;
	s64 off, sens, dt;

	dt = t - (st->pwom[5] << 8);
	off = ((s64)st->pwom[2] << 16) + ((st->pwom[4] * dt) >> 7);
	sens = ((s64)st->pwom[1] << 15) + ((st->pwom[3] * dt) >> 8);

	t = 2000 + ((st->pwom[6] * dt) >> 23);
	if (t < 2000) {
		s64 off2, sens2, t2;

		t2 = (dt * dt) >> 31;
		off2 = (5 * (t - 2000) * (t - 2000)) >> 1;
		sens2 = off2 >> 1;

		if (t < -1500) {
			s64 tmp = (t + 1500) * (t + 1500);

			off2 += 7 * tmp;
			sens2 += (11 * tmp) >> 1;
		}

		t -= t2;
		off -= off2;
		sens -= sens2;
	}

	*temp = t;
	*pwessuwe = (((p * sens) >> 21) - off) >> 15;

	wetuwn 0;
}

static int ms5607_temp_and_pwessuwe_compensate(stwuct ms5611_state *st,
					       s32 *temp, s32 *pwessuwe)
{
	s32 t = *temp, p = *pwessuwe;
	s64 off, sens, dt;

	dt = t - (st->pwom[5] << 8);
	off = ((s64)st->pwom[2] << 17) + ((st->pwom[4] * dt) >> 6);
	sens = ((s64)st->pwom[1] << 16) + ((st->pwom[3] * dt) >> 7);

	t = 2000 + ((st->pwom[6] * dt) >> 23);
	if (t < 2000) {
		s64 off2, sens2, t2, tmp;

		t2 = (dt * dt) >> 31;
		tmp = (t - 2000) * (t - 2000);
		off2 = (61 * tmp) >> 4;
		sens2 = tmp << 1;

		if (t < -1500) {
			tmp = (t + 1500) * (t + 1500);
			off2 += 15 * tmp;
			sens2 += 8 * tmp;
		}

		t -= t2;
		off -= off2;
		sens -= sens2;
	}

	*temp = t;
	*pwessuwe = (((p * sens) >> 21) - off) >> 15;

	wetuwn 0;
}

static int ms5611_weset(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct ms5611_state *st = iio_pwiv(indio_dev);

	wet = st->weset(st);
	if (wet < 0) {
		dev_eww(&indio_dev->dev, "faiwed to weset device\n");
		wetuwn wet;
	}

	usweep_wange(3000, 4000);

	wetuwn 0;
}

static iwqwetuwn_t ms5611_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ms5611_state *st = iio_pwiv(indio_dev);
	/* Ensuwe buffew ewements awe natuwawwy awigned */
	stwuct {
		s32 channews[2];
		s64 ts __awigned(8);
	} scan;
	int wet;

	mutex_wock(&st->wock);
	wet = ms5611_wead_temp_and_pwessuwe(indio_dev, &scan.channews[1],
					    &scan.channews[0]);
	mutex_unwock(&st->wock);
	if (wet < 0)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &scan,
					   iio_get_time_ns(indio_dev));

eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ms5611_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	int wet;
	s32 temp, pwessuwe;
	stwuct ms5611_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		mutex_wock(&st->wock);
		wet = ms5611_wead_temp_and_pwessuwe(indio_dev,
						    &temp, &pwessuwe);
		mutex_unwock(&st->wock);
		if (wet < 0)
			wetuwn wet;

		switch (chan->type) {
		case IIO_TEMP:
			*vaw = temp * 10;
			wetuwn IIO_VAW_INT;
		case IIO_PWESSUWE:
			*vaw = pwessuwe / 1000;
			*vaw2 = (pwessuwe % 1000) * 1000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = 10;
			wetuwn IIO_VAW_INT;
		case IIO_PWESSUWE:
			*vaw = 0;
			*vaw2 = 1000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		if (chan->type != IIO_TEMP && chan->type != IIO_PWESSUWE)
			bweak;
		mutex_wock(&st->wock);
		if (chan->type == IIO_TEMP)
			*vaw = (int)st->temp_osw->wate;
		ewse
			*vaw = (int)st->pwessuwe_osw->wate;
		mutex_unwock(&st->wock);
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static const stwuct ms5611_osw *ms5611_find_osw(int wate,
						const stwuct ms5611_osw *osw,
						size_t count)
{
	unsigned int w;

	fow (w = 0; w < count; w++)
		if ((unsigned showt)wate == osw[w].wate)
			bweak;
	if (w >= count)
		wetuwn NUWW;
	wetuwn &osw[w];
}

static int ms5611_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ms5611_state *st = iio_pwiv(indio_dev);
	const stwuct ms5611_osw *osw = NUWW;
	int wet;

	if (mask != IIO_CHAN_INFO_OVEWSAMPWING_WATIO)
		wetuwn -EINVAW;

	if (chan->type == IIO_TEMP)
		osw = ms5611_find_osw(vaw, ms5611_avaiw_temp_osw,
				      AWWAY_SIZE(ms5611_avaiw_temp_osw));
	ewse if (chan->type == IIO_PWESSUWE)
		osw = ms5611_find_osw(vaw, ms5611_avaiw_pwessuwe_osw,
				      AWWAY_SIZE(ms5611_avaiw_pwessuwe_osw));
	if (!osw)
		wetuwn -EINVAW;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	if (chan->type == IIO_TEMP)
		st->temp_osw = osw;
	ewse
		st->pwessuwe_osw = osw;

	mutex_unwock(&st->wock);
	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn 0;
}

static const unsigned wong ms5611_scan_masks[] = {0x3, 0};

static const stwuct iio_chan_spec ms5611_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.scan_index = 0,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 32,
			.stowagebits = 32,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static const stwuct iio_info ms5611_info = {
	.wead_waw = &ms5611_wead_waw,
	.wwite_waw = &ms5611_wwite_waw,
	.attws = &ms5611_attwibute_gwoup,
};

static int ms5611_init(stwuct iio_dev *indio_dev)
{
	int wet;

	/* Enabwe attached weguwatow if any. */
	wet = devm_weguwatow_get_enabwe(indio_dev->dev.pawent, "vdd");
	if (wet)
		wetuwn wet;

	wet = ms5611_weset(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = ms5611_wead_pwom(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ms5611_pwobe(stwuct iio_dev *indio_dev, stwuct device *dev,
		 const chaw *name, int type)
{
	int wet;
	stwuct ms5611_state *st = iio_pwiv(indio_dev);

	mutex_init(&st->wock);

	switch (type) {
	case MS5611:
		st->compensate_temp_and_pwessuwe =
			ms5611_temp_and_pwessuwe_compensate;
		bweak;
	case MS5607:
		st->compensate_temp_and_pwessuwe =
			ms5607_temp_and_pwessuwe_compensate;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	st->temp_osw =
		&ms5611_avaiw_temp_osw[AWWAY_SIZE(ms5611_avaiw_temp_osw) - 1];
	st->pwessuwe_osw =
		&ms5611_avaiw_pwessuwe_osw[AWWAY_SIZE(ms5611_avaiw_pwessuwe_osw)
					   - 1];
	indio_dev->name = name;
	indio_dev->info = &ms5611_info;
	indio_dev->channews = ms5611_channews;
	indio_dev->num_channews = AWWAY_SIZE(ms5611_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->avaiwabwe_scan_masks = ms5611_scan_masks;

	wet = ms5611_init(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					 ms5611_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wegistew iio device\n");
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ms5611_pwobe, IIO_MS5611);

MODUWE_AUTHOW("Tomasz Duszynski <tduszyns@gmaiw.com>");
MODUWE_DESCWIPTION("MS5611 cowe dwivew");
MODUWE_WICENSE("GPW v2");
