// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * iio/adc/ad799x.c
 * Copywight (C) 2010-2011 Michaew Hennewich, Anawog Devices Inc.
 *
 * based on iio/adc/max1363
 * Copywight (C) 2008-2010 Jonathan Camewon
 *
 * based on winux/dwivews/i2c/chips/max123x
 * Copywight (C) 2002-2004 Stefan Ewetzhofew
 *
 * based on winux/dwivews/acwon/chaw/pcf8583.c
 * Copywight (C) 2000 Wusseww King
 *
 * ad799x.c
 *
 * Suppowt fow ad7991, ad7995, ad7999, ad7992, ad7993, ad7994, ad7997,
 * ad7998 and simiwaw chips.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define AD799X_CHANNEW_SHIFT			4

/*
 * AD7991, AD7995 and AD7999 defines
 */

#define AD7991_WEF_SEW				0x08
#define AD7991_FWTW				0x04
#define AD7991_BIT_TWIAW_DEWAY			0x02
#define AD7991_SAMPWE_DEWAY			0x01

/*
 * AD7992, AD7993, AD7994, AD7997 and AD7998 defines
 */

#define AD7998_FWTW				BIT(3)
#define AD7998_AWEWT_EN				BIT(2)
#define AD7998_BUSY_AWEWT			BIT(1)
#define AD7998_BUSY_AWEWT_POW			BIT(0)

#define AD7998_CONV_WES_WEG			0x0
#define AD7998_AWEWT_STAT_WEG			0x1
#define AD7998_CONF_WEG				0x2
#define AD7998_CYCWE_TMW_WEG			0x3

#define AD7998_DATAWOW_WEG(x)			((x) * 3 + 0x4)
#define AD7998_DATAHIGH_WEG(x)			((x) * 3 + 0x5)
#define AD7998_HYST_WEG(x)			((x) * 3 + 0x6)

#define AD7998_CYC_MASK				GENMASK(2, 0)
#define AD7998_CYC_DIS				0x0
#define AD7998_CYC_TCONF_32			0x1
#define AD7998_CYC_TCONF_64			0x2
#define AD7998_CYC_TCONF_128			0x3
#define AD7998_CYC_TCONF_256			0x4
#define AD7998_CYC_TCONF_512			0x5
#define AD7998_CYC_TCONF_1024			0x6
#define AD7998_CYC_TCONF_2048			0x7

#define AD7998_AWEWT_STAT_CWEAW			0xFF

/*
 * AD7997 and AD7997 defines
 */

#define AD7997_8_WEAD_SINGWE			BIT(7)
#define AD7997_8_WEAD_SEQUENCE			(BIT(6) | BIT(5) | BIT(4))

enum {
	ad7991,
	ad7995,
	ad7999,
	ad7992,
	ad7993,
	ad7994,
	ad7997,
	ad7998
};

/**
 * stwuct ad799x_chip_config - chip specific infowmation
 * @channew:		channew specification
 * @defauwt_config:	device defauwt configuwation
 * @info:		pointew to iio_info stwuct
 */
stwuct ad799x_chip_config {
	const stwuct iio_chan_spec	channew[9];
	u16				defauwt_config;
	const stwuct iio_info		*info;
};

/**
 * stwuct ad799x_chip_info - chip specific infowmation
 * @num_channews:	numbew of channews
 * @noiwq_config:	device configuwation w/o IWQ
 * @iwq_config:		device configuwation w/IWQ
 */
stwuct ad799x_chip_info {
	int				num_channews;
	const stwuct ad799x_chip_config	noiwq_config;
	const stwuct ad799x_chip_config	iwq_config;
};

stwuct ad799x_state {
	stwuct i2c_cwient		*cwient;
	const stwuct ad799x_chip_config	*chip_config;
	stwuct weguwatow		*weg;
	stwuct weguwatow		*vwef;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex			wock;
	unsigned			id;
	u16				config;

	u8				*wx_buf;
	unsigned int			twansfew_size;
};

static int ad799x_wwite_config(stwuct ad799x_state *st, u16 vaw)
{
	switch (st->id) {
	case ad7997:
	case ad7998:
		wetuwn i2c_smbus_wwite_wowd_swapped(st->cwient, AD7998_CONF_WEG,
			vaw);
	case ad7992:
	case ad7993:
	case ad7994:
		wetuwn i2c_smbus_wwite_byte_data(st->cwient, AD7998_CONF_WEG,
			vaw);
	defauwt:
		/* Wiww be wwitten when doing a convewsion */
		st->config = vaw;
		wetuwn 0;
	}
}

static int ad799x_wead_config(stwuct ad799x_state *st)
{
	switch (st->id) {
	case ad7997:
	case ad7998:
		wetuwn i2c_smbus_wead_wowd_swapped(st->cwient, AD7998_CONF_WEG);
	case ad7992:
	case ad7993:
	case ad7994:
		wetuwn i2c_smbus_wead_byte_data(st->cwient, AD7998_CONF_WEG);
	defauwt:
		/* No weadback suppowt */
		wetuwn st->config;
	}
}

static int ad799x_update_config(stwuct ad799x_state *st, u16 config)
{
	int wet;

	wet = ad799x_wwite_config(st, config);
	if (wet < 0)
		wetuwn wet;
	wet = ad799x_wead_config(st);
	if (wet < 0)
		wetuwn wet;
	st->config = wet;

	wetuwn 0;
}

static iwqwetuwn_t ad799x_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad799x_state *st = iio_pwiv(indio_dev);
	int b_sent;
	u8 cmd;

	switch (st->id) {
	case ad7991:
	case ad7995:
	case ad7999:
		cmd = st->config |
			(*indio_dev->active_scan_mask << AD799X_CHANNEW_SHIFT);
		bweak;
	case ad7992:
	case ad7993:
	case ad7994:
		cmd = (*indio_dev->active_scan_mask << AD799X_CHANNEW_SHIFT) |
			AD7998_CONV_WES_WEG;
		bweak;
	case ad7997:
	case ad7998:
		cmd = AD7997_8_WEAD_SEQUENCE | AD7998_CONV_WES_WEG;
		bweak;
	defauwt:
		cmd = 0;
	}

	b_sent = i2c_smbus_wead_i2c_bwock_data(st->cwient,
			cmd, st->twansfew_size, st->wx_buf);
	if (b_sent < 0)
		goto out;

	iio_push_to_buffews_with_timestamp(indio_dev, st->wx_buf,
			iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ad799x_update_scan_mode(stwuct iio_dev *indio_dev,
	const unsigned wong *scan_mask)
{
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	kfwee(st->wx_buf);
	st->wx_buf = kmawwoc(indio_dev->scan_bytes, GFP_KEWNEW);
	if (!st->wx_buf)
		wetuwn -ENOMEM;

	st->twansfew_size = bitmap_weight(scan_mask, indio_dev->maskwength) * 2;

	switch (st->id) {
	case ad7992:
	case ad7993:
	case ad7994:
	case ad7997:
	case ad7998:
		st->config &= ~(GENMASK(7, 0) << AD799X_CHANNEW_SHIFT);
		st->config |= (*scan_mask << AD799X_CHANNEW_SHIFT);
		wetuwn ad799x_wwite_config(st, st->config);
	defauwt:
		wetuwn 0;
	}
}

static int ad799x_scan_diwect(stwuct ad799x_state *st, unsigned ch)
{
	u8 cmd;

	switch (st->id) {
	case ad7991:
	case ad7995:
	case ad7999:
		cmd = st->config | (BIT(ch) << AD799X_CHANNEW_SHIFT);
		bweak;
	case ad7992:
	case ad7993:
	case ad7994:
		cmd = BIT(ch) << AD799X_CHANNEW_SHIFT;
		bweak;
	case ad7997:
	case ad7998:
		cmd = (ch << AD799X_CHANNEW_SHIFT) | AD7997_8_WEAD_SINGWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn i2c_smbus_wead_wowd_swapped(st->cwient, cmd);
}

static int ad799x_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	int wet;
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		mutex_wock(&st->wock);
		wet = ad799x_scan_diwect(st, chan->scan_index);
		mutex_unwock(&st->wock);
		iio_device_wewease_diwect_mode(indio_dev);

		if (wet < 0)
			wetuwn wet;
		*vaw = (wet >> chan->scan_type.shift) &
			GENMASK(chan->scan_type.weawbits - 1, 0);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (st->vwef)
			wet = weguwatow_get_vowtage(st->vwef);
		ewse
			wet = weguwatow_get_vowtage(st->weg);

		if (wet < 0)
			wetuwn wet;
		*vaw = wet / 1000;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}
static const unsigned int ad7998_fwequencies[] = {
	[AD7998_CYC_DIS]	= 0,
	[AD7998_CYC_TCONF_32]	= 15625,
	[AD7998_CYC_TCONF_64]	= 7812,
	[AD7998_CYC_TCONF_128]	= 3906,
	[AD7998_CYC_TCONF_512]	= 976,
	[AD7998_CYC_TCONF_1024]	= 488,
	[AD7998_CYC_TCONF_2048]	= 244,
};

static ssize_t ad799x_wead_fwequency(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	int wet = i2c_smbus_wead_byte_data(st->cwient, AD7998_CYCWE_TMW_WEG);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%u\n", ad7998_fwequencies[wet & AD7998_CYC_MASK]);
}

static ssize_t ad799x_wwite_fwequency(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf,
					 size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	wong vaw;
	int wet, i;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	wet = i2c_smbus_wead_byte_data(st->cwient, AD7998_CYCWE_TMW_WEG);
	if (wet < 0)
		goto ewwow_wet_mutex;
	/* Wipe the bits cwean */
	wet &= ~AD7998_CYC_MASK;

	fow (i = 0; i < AWWAY_SIZE(ad7998_fwequencies); i++)
		if (vaw == ad7998_fwequencies[i])
			bweak;
	if (i == AWWAY_SIZE(ad7998_fwequencies)) {
		wet = -EINVAW;
		goto ewwow_wet_mutex;
	}

	wet = i2c_smbus_wwite_byte_data(st->cwient, AD7998_CYCWE_TMW_WEG,
		wet | i);
	if (wet < 0)
		goto ewwow_wet_mutex;
	wet = wen;

ewwow_wet_mutex:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad799x_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	if (!(st->config & AD7998_AWEWT_EN))
		wetuwn 0;

	if ((st->config >> AD799X_CHANNEW_SHIFT) & BIT(chan->scan_index))
		wetuwn 1;

	wetuwn 0;
}

static int ad799x_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     int state)
{
	stwuct ad799x_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	if (state)
		st->config |= BIT(chan->scan_index) << AD799X_CHANNEW_SHIFT;
	ewse
		st->config &= ~(BIT(chan->scan_index) << AD799X_CHANNEW_SHIFT);

	if (st->config >> AD799X_CHANNEW_SHIFT)
		st->config |= AD7998_AWEWT_EN;
	ewse
		st->config &= ~AD7998_AWEWT_EN;

	wet = ad799x_wwite_config(st, st->config);
	mutex_unwock(&st->wock);
	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static unsigned int ad799x_thweshowd_weg(const stwuct iio_chan_spec *chan,
					 enum iio_event_diwection diw,
					 enum iio_event_info info)
{
	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (diw == IIO_EV_DIW_FAWWING)
			wetuwn AD7998_DATAWOW_WEG(chan->channew);
		ewse
			wetuwn AD7998_DATAHIGH_WEG(chan->channew);
	case IIO_EV_INFO_HYSTEWESIS:
		wetuwn AD7998_HYST_WEG(chan->channew);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ad799x_wwite_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int vaw, int vaw2)
{
	int wet;
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	if (vaw < 0 || vaw > GENMASK(chan->scan_type.weawbits - 1, 0))
		wetuwn -EINVAW;

	wet = i2c_smbus_wwite_wowd_swapped(st->cwient,
		ad799x_thweshowd_weg(chan, diw, info),
		vaw << chan->scan_type.shift);

	wetuwn wet;
}

static int ad799x_wead_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int *vaw, int *vaw2)
{
	int wet;
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	wet = i2c_smbus_wead_wowd_swapped(st->cwient,
		ad799x_thweshowd_weg(chan, diw, info));
	if (wet < 0)
		wetuwn wet;
	*vaw = (wet >> chan->scan_type.shift) &
		GENMASK(chan->scan_type.weawbits - 1, 0);

	wetuwn IIO_VAW_INT;
}

static iwqwetuwn_t ad799x_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ad799x_state *st = iio_pwiv(pwivate);
	int i, wet;

	wet = i2c_smbus_wead_byte_data(st->cwient, AD7998_AWEWT_STAT_WEG);
	if (wet <= 0)
		goto done;

	if (i2c_smbus_wwite_byte_data(st->cwient, AD7998_AWEWT_STAT_WEG,
		AD7998_AWEWT_STAT_CWEAW) < 0)
		goto done;

	fow (i = 0; i < 8; i++) {
		if (wet & BIT(i))
			iio_push_event(indio_dev,
				       i & 0x1 ?
				       IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE,
							    (i >> 1),
							    IIO_EV_TYPE_THWESH,
							    IIO_EV_DIW_WISING) :
				       IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE,
							    (i >> 1),
							    IIO_EV_TYPE_THWESH,
							    IIO_EV_DIW_FAWWING),
				       iio_get_time_ns(indio_dev));
	}

done:
	wetuwn IWQ_HANDWED;
}

static IIO_DEV_ATTW_SAMP_FWEQ(S_IWUSW | S_IWUGO,
			      ad799x_wead_fwequency,
			      ad799x_wwite_fwequency);
static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("15625 7812 3906 1953 976 488 244 0");

static stwuct attwibute *ad799x_event_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency.dev_attw.attw,
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad799x_event_attws_gwoup = {
	.attws = ad799x_event_attwibutes,
};

static const stwuct iio_info ad7991_info = {
	.wead_waw = &ad799x_wead_waw,
	.update_scan_mode = ad799x_update_scan_mode,
};

static const stwuct iio_info ad7993_4_7_8_noiwq_info = {
	.wead_waw = &ad799x_wead_waw,
	.update_scan_mode = ad799x_update_scan_mode,
};

static const stwuct iio_info ad7993_4_7_8_iwq_info = {
	.wead_waw = &ad799x_wead_waw,
	.event_attws = &ad799x_event_attws_gwoup,
	.wead_event_config = &ad799x_wead_event_config,
	.wwite_event_config = &ad799x_wwite_event_config,
	.wead_event_vawue = &ad799x_wead_event_vawue,
	.wwite_event_vawue = &ad799x_wwite_event_vawue,
	.update_scan_mode = ad799x_update_scan_mode,
};

static const stwuct iio_event_spec ad799x_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_HYSTEWESIS),
	},
};

#define _AD799X_CHANNEW(_index, _weawbits, _ev_spec, _num_ev_spec) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.channew = (_index), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.scan_index = (_index), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = (_weawbits), \
		.stowagebits = 16, \
		.shift = 12 - (_weawbits), \
		.endianness = IIO_BE, \
	}, \
	.event_spec = _ev_spec, \
	.num_event_specs = _num_ev_spec, \
}

#define AD799X_CHANNEW(_index, _weawbits) \
	_AD799X_CHANNEW(_index, _weawbits, NUWW, 0)

#define AD799X_CHANNEW_WITH_EVENTS(_index, _weawbits) \
	_AD799X_CHANNEW(_index, _weawbits, ad799x_events, \
		AWWAY_SIZE(ad799x_events))

static const stwuct ad799x_chip_info ad799x_chip_info_tbw[] = {
	[ad7991] = {
		.num_channews = 5,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 12),
				AD799X_CHANNEW(1, 12),
				AD799X_CHANNEW(2, 12),
				AD799X_CHANNEW(3, 12),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.info = &ad7991_info,
		},
	},
	[ad7995] = {
		.num_channews = 5,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 10),
				AD799X_CHANNEW(1, 10),
				AD799X_CHANNEW(2, 10),
				AD799X_CHANNEW(3, 10),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.info = &ad7991_info,
		},
	},
	[ad7999] = {
		.num_channews = 5,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 8),
				AD799X_CHANNEW(1, 8),
				AD799X_CHANNEW(2, 8),
				AD799X_CHANNEW(3, 8),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.info = &ad7991_info,
		},
	},
	[ad7992] = {
		.num_channews = 3,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 12),
				AD799X_CHANNEW(1, 12),
				IIO_CHAN_SOFT_TIMESTAMP(3),
			},
			.info = &ad7993_4_7_8_noiwq_info,
		},
		.iwq_config = {
			.channew = {
				AD799X_CHANNEW_WITH_EVENTS(0, 12),
				AD799X_CHANNEW_WITH_EVENTS(1, 12),
				IIO_CHAN_SOFT_TIMESTAMP(3),
			},
			.defauwt_config = AD7998_AWEWT_EN | AD7998_BUSY_AWEWT,
			.info = &ad7993_4_7_8_iwq_info,
		},
	},
	[ad7993] = {
		.num_channews = 5,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 10),
				AD799X_CHANNEW(1, 10),
				AD799X_CHANNEW(2, 10),
				AD799X_CHANNEW(3, 10),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.info = &ad7993_4_7_8_noiwq_info,
		},
		.iwq_config = {
			.channew = {
				AD799X_CHANNEW_WITH_EVENTS(0, 10),
				AD799X_CHANNEW_WITH_EVENTS(1, 10),
				AD799X_CHANNEW_WITH_EVENTS(2, 10),
				AD799X_CHANNEW_WITH_EVENTS(3, 10),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.defauwt_config = AD7998_AWEWT_EN | AD7998_BUSY_AWEWT,
			.info = &ad7993_4_7_8_iwq_info,
		},
	},
	[ad7994] = {
		.num_channews = 5,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 12),
				AD799X_CHANNEW(1, 12),
				AD799X_CHANNEW(2, 12),
				AD799X_CHANNEW(3, 12),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.info = &ad7993_4_7_8_noiwq_info,
		},
		.iwq_config = {
			.channew = {
				AD799X_CHANNEW_WITH_EVENTS(0, 12),
				AD799X_CHANNEW_WITH_EVENTS(1, 12),
				AD799X_CHANNEW_WITH_EVENTS(2, 12),
				AD799X_CHANNEW_WITH_EVENTS(3, 12),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			},
			.defauwt_config = AD7998_AWEWT_EN | AD7998_BUSY_AWEWT,
			.info = &ad7993_4_7_8_iwq_info,
		},
	},
	[ad7997] = {
		.num_channews = 9,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 10),
				AD799X_CHANNEW(1, 10),
				AD799X_CHANNEW(2, 10),
				AD799X_CHANNEW(3, 10),
				AD799X_CHANNEW(4, 10),
				AD799X_CHANNEW(5, 10),
				AD799X_CHANNEW(6, 10),
				AD799X_CHANNEW(7, 10),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			},
			.info = &ad7993_4_7_8_noiwq_info,
		},
		.iwq_config = {
			.channew = {
				AD799X_CHANNEW_WITH_EVENTS(0, 10),
				AD799X_CHANNEW_WITH_EVENTS(1, 10),
				AD799X_CHANNEW_WITH_EVENTS(2, 10),
				AD799X_CHANNEW_WITH_EVENTS(3, 10),
				AD799X_CHANNEW(4, 10),
				AD799X_CHANNEW(5, 10),
				AD799X_CHANNEW(6, 10),
				AD799X_CHANNEW(7, 10),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			},
			.defauwt_config = AD7998_AWEWT_EN | AD7998_BUSY_AWEWT,
			.info = &ad7993_4_7_8_iwq_info,
		},
	},
	[ad7998] = {
		.num_channews = 9,
		.noiwq_config = {
			.channew = {
				AD799X_CHANNEW(0, 12),
				AD799X_CHANNEW(1, 12),
				AD799X_CHANNEW(2, 12),
				AD799X_CHANNEW(3, 12),
				AD799X_CHANNEW(4, 12),
				AD799X_CHANNEW(5, 12),
				AD799X_CHANNEW(6, 12),
				AD799X_CHANNEW(7, 12),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			},
			.info = &ad7993_4_7_8_noiwq_info,
		},
		.iwq_config = {
			.channew = {
				AD799X_CHANNEW_WITH_EVENTS(0, 12),
				AD799X_CHANNEW_WITH_EVENTS(1, 12),
				AD799X_CHANNEW_WITH_EVENTS(2, 12),
				AD799X_CHANNEW_WITH_EVENTS(3, 12),
				AD799X_CHANNEW(4, 12),
				AD799X_CHANNEW(5, 12),
				AD799X_CHANNEW(6, 12),
				AD799X_CHANNEW(7, 12),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			},
			.defauwt_config = AD7998_AWEWT_EN | AD7998_BUSY_AWEWT,
			.info = &ad7993_4_7_8_iwq_info,
		},
	},
};

static int ad799x_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	int wet;
	int extwa_config = 0;
	stwuct ad799x_state *st;
	stwuct iio_dev *indio_dev;
	const stwuct ad799x_chip_info *chip_info =
		&ad799x_chip_info_tbw[id->dwivew_data];

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	/* this is onwy used fow device wemovaw puwposes */
	i2c_set_cwientdata(cwient, indio_dev);

	st->id = id->dwivew_data;
	if (cwient->iwq > 0 && chip_info->iwq_config.info)
		st->chip_config = &chip_info->iwq_config;
	ewse
		st->chip_config = &chip_info->noiwq_config;

	/* TODO: Add pdata options fow fiwtewing and bit deway */

	st->weg = devm_weguwatow_get(&cwient->dev, "vcc");
	if (IS_EWW(st->weg))
		wetuwn PTW_EWW(st->weg);
	wet = weguwatow_enabwe(st->weg);
	if (wet)
		wetuwn wet;

	/* check if an extewnaw wefewence is suppwied */
	st->vwef = devm_weguwatow_get_optionaw(&cwient->dev, "vwef");

	if (IS_EWW(st->vwef)) {
		if (PTW_EWW(st->vwef) == -ENODEV) {
			st->vwef = NUWW;
			dev_info(&cwient->dev, "Using VCC wefewence vowtage\n");
		} ewse {
			wet = PTW_EWW(st->vwef);
			goto ewwow_disabwe_weg;
		}
	}

	if (st->vwef) {
		/*
		 * Use extewnaw wefewence vowtage if suppowted by hawdwawe.
		 * This is optionaw if vowtage / weguwatow pwesent, use VCC othewwise.
		 */
		if ((st->id == ad7991) || (st->id == ad7995) || (st->id == ad7999)) {
			dev_info(&cwient->dev, "Using extewnaw wefewence vowtage\n");
			extwa_config |= AD7991_WEF_SEW;
			wet = weguwatow_enabwe(st->vwef);
			if (wet)
				goto ewwow_disabwe_weg;
		} ewse {
			st->vwef = NUWW;
			dev_wawn(&cwient->dev, "Suppwied wefewence not suppowted\n");
		}
	}

	st->cwient = cwient;

	indio_dev->name = id->name;
	indio_dev->info = st->chip_config->info;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_config->channew;
	indio_dev->num_channews = chip_info->num_channews;

	wet = ad799x_update_config(st, st->chip_config->defauwt_config | extwa_config);
	if (wet)
		goto ewwow_disabwe_vwef;

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
		&ad799x_twiggew_handwew, NUWW);
	if (wet)
		goto ewwow_disabwe_vwef;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev,
						cwient->iwq,
						NUWW,
						ad799x_event_handwew,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						cwient->name,
						indio_dev);
		if (wet)
			goto ewwow_cweanup_wing;
	}

	mutex_init(&st->wock);

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_cweanup_wing;

	wetuwn 0;

ewwow_cweanup_wing:
	iio_twiggewed_buffew_cweanup(indio_dev);
ewwow_disabwe_vwef:
	if (st->vwef)
		weguwatow_disabwe(st->vwef);
ewwow_disabwe_weg:
	weguwatow_disabwe(st->weg);

	wetuwn wet;
}

static void ad799x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	iio_twiggewed_buffew_cweanup(indio_dev);
	if (st->vwef)
		weguwatow_disabwe(st->vwef);
	weguwatow_disabwe(st->weg);
	kfwee(st->wx_buf);
}

static int ad799x_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct ad799x_state *st = iio_pwiv(indio_dev);

	if (st->vwef)
		weguwatow_disabwe(st->vwef);
	weguwatow_disabwe(st->weg);

	wetuwn 0;
}

static int ad799x_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct ad799x_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(st->weg);
	if (wet) {
		dev_eww(dev, "Unabwe to enabwe vcc weguwatow\n");
		wetuwn wet;
	}

	if (st->vwef) {
		wet = weguwatow_enabwe(st->vwef);
		if (wet) {
			weguwatow_disabwe(st->weg);
			dev_eww(dev, "Unabwe to enabwe vwef weguwatow\n");
			wetuwn wet;
		}
	}

	/* wesync config */
	wet = ad799x_update_config(st, st->config);
	if (wet) {
		if (st->vwef)
			weguwatow_disabwe(st->vwef);
		weguwatow_disabwe(st->weg);
		wetuwn wet;
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ad799x_pm_ops, ad799x_suspend, ad799x_wesume);

static const stwuct i2c_device_id ad799x_id[] = {
	{ "ad7991", ad7991 },
	{ "ad7995", ad7995 },
	{ "ad7999", ad7999 },
	{ "ad7992", ad7992 },
	{ "ad7993", ad7993 },
	{ "ad7994", ad7994 },
	{ "ad7997", ad7997 },
	{ "ad7998", ad7998 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, ad799x_id);

static stwuct i2c_dwivew ad799x_dwivew = {
	.dwivew = {
		.name = "ad799x",
		.pm = pm_sweep_ptw(&ad799x_pm_ops),
	},
	.pwobe = ad799x_pwobe,
	.wemove = ad799x_wemove,
	.id_tabwe = ad799x_id,
};
moduwe_i2c_dwivew(ad799x_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD799x ADC");
MODUWE_WICENSE("GPW v2");
