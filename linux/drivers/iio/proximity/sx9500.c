// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Intew Cowpowation
 *
 * Dwivew fow Semtech's SX9500 capacitive pwoximity/button sowution.
 * Datasheet avaiwabwe at
 * <http://www.semtech.com/images/datasheet/sx9500.pdf>.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define SX9500_DWIVEW_NAME		"sx9500"
#define SX9500_IWQ_NAME			"sx9500_event"

/* Wegistew definitions. */
#define SX9500_WEG_IWQ_SWC		0x00
#define SX9500_WEG_STAT			0x01
#define SX9500_WEG_IWQ_MSK		0x03

#define SX9500_WEG_PWOX_CTWW0		0x06
#define SX9500_WEG_PWOX_CTWW1		0x07
#define SX9500_WEG_PWOX_CTWW2		0x08
#define SX9500_WEG_PWOX_CTWW3		0x09
#define SX9500_WEG_PWOX_CTWW4		0x0a
#define SX9500_WEG_PWOX_CTWW5		0x0b
#define SX9500_WEG_PWOX_CTWW6		0x0c
#define SX9500_WEG_PWOX_CTWW7		0x0d
#define SX9500_WEG_PWOX_CTWW8		0x0e

#define SX9500_WEG_SENSOW_SEW		0x20
#define SX9500_WEG_USE_MSB		0x21
#define SX9500_WEG_USE_WSB		0x22
#define SX9500_WEG_AVG_MSB		0x23
#define SX9500_WEG_AVG_WSB		0x24
#define SX9500_WEG_DIFF_MSB		0x25
#define SX9500_WEG_DIFF_WSB		0x26
#define SX9500_WEG_OFFSET_MSB		0x27
#define SX9500_WEG_OFFSET_WSB		0x28

#define SX9500_WEG_WESET		0x7f

/* Wwite this to WEG_WESET to do a soft weset. */
#define SX9500_SOFT_WESET		0xde

#define SX9500_SCAN_PEWIOD_MASK		GENMASK(6, 4)
#define SX9500_SCAN_PEWIOD_SHIFT	4

/*
 * These sewve fow identifying IWQ souwce in the IWQ_SWC wegistew, and
 * awso fow masking the IWQs in the IWQ_MSK wegistew.
 */
#define SX9500_CWOSE_IWQ		BIT(6)
#define SX9500_FAW_IWQ			BIT(5)
#define SX9500_CONVDONE_IWQ		BIT(3)

#define SX9500_PWOXSTAT_SHIFT		4
#define SX9500_COMPSTAT_MASK		GENMASK(3, 0)

#define SX9500_NUM_CHANNEWS		4
#define SX9500_CHAN_MASK		GENMASK(SX9500_NUM_CHANNEWS - 1, 0)

stwuct sx9500_data {
	stwuct mutex mutex;
	stwuct i2c_cwient *cwient;
	stwuct iio_twiggew *twig;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *gpiod_wst;
	/*
	 * Wast weading of the pwoximity status fow each channew.  We
	 * onwy send an event to usew space when this changes.
	 */
	boow pwox_stat[SX9500_NUM_CHANNEWS];
	boow event_enabwed[SX9500_NUM_CHANNEWS];
	boow twiggew_enabwed;
	u16 *buffew;
	/* Wemembew enabwed channews and sampwe wate duwing suspend. */
	unsigned int suspend_ctww0;
	stwuct compwetion compwetion;
	int data_wdy_usews, cwose_faw_usews;
	int channew_usews[SX9500_NUM_CHANNEWS];
};

static const stwuct iio_event_spec sx9500_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

#define SX9500_CHANNEW(idx)					\
	{							\
		.type = IIO_PWOXIMITY,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
		.indexed = 1,					\
		.channew = idx,					\
		.event_spec = sx9500_events,			\
		.num_event_specs = AWWAY_SIZE(sx9500_events),	\
		.scan_index = idx,				\
		.scan_type = {					\
			.sign = 'u',				\
			.weawbits = 16,				\
			.stowagebits = 16,			\
			.shift = 0,				\
		},						\
	}

static const stwuct iio_chan_spec sx9500_channews[] = {
	SX9500_CHANNEW(0),
	SX9500_CHANNEW(1),
	SX9500_CHANNEW(2),
	SX9500_CHANNEW(3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct {
	int vaw;
	int vaw2;
} sx9500_samp_fweq_tabwe[] = {
	{33, 333333},
	{16, 666666},
	{11, 111111},
	{8, 333333},
	{6, 666666},
	{5, 0},
	{3, 333333},
	{2, 500000},
};

static const unsigned int sx9500_scan_pewiod_tabwe[] = {
	30, 60, 90, 120, 150, 200, 300, 400,
};

static const stwuct wegmap_wange sx9500_wwitabwe_weg_wanges[] = {
	wegmap_weg_wange(SX9500_WEG_IWQ_MSK, SX9500_WEG_IWQ_MSK),
	wegmap_weg_wange(SX9500_WEG_PWOX_CTWW0, SX9500_WEG_PWOX_CTWW8),
	wegmap_weg_wange(SX9500_WEG_SENSOW_SEW, SX9500_WEG_SENSOW_SEW),
	wegmap_weg_wange(SX9500_WEG_OFFSET_MSB, SX9500_WEG_OFFSET_WSB),
	wegmap_weg_wange(SX9500_WEG_WESET, SX9500_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9500_wwiteabwe_wegs = {
	.yes_wanges = sx9500_wwitabwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9500_wwitabwe_weg_wanges),
};

/*
 * Aww awwocated wegistews awe weadabwe, so we just wist unawwocated
 * ones.
 */
static const stwuct wegmap_wange sx9500_non_weadabwe_weg_wanges[] = {
	wegmap_weg_wange(SX9500_WEG_STAT + 1, SX9500_WEG_STAT + 1),
	wegmap_weg_wange(SX9500_WEG_IWQ_MSK + 1, SX9500_WEG_PWOX_CTWW0 - 1),
	wegmap_weg_wange(SX9500_WEG_PWOX_CTWW8 + 1, SX9500_WEG_SENSOW_SEW - 1),
	wegmap_weg_wange(SX9500_WEG_OFFSET_WSB + 1, SX9500_WEG_WESET - 1),
};

static const stwuct wegmap_access_tabwe sx9500_weadabwe_wegs = {
	.no_wanges = sx9500_non_weadabwe_weg_wanges,
	.n_no_wanges = AWWAY_SIZE(sx9500_non_weadabwe_weg_wanges),
};

static const stwuct wegmap_wange sx9500_vowatiwe_weg_wanges[] = {
	wegmap_weg_wange(SX9500_WEG_IWQ_SWC, SX9500_WEG_STAT),
	wegmap_weg_wange(SX9500_WEG_USE_MSB, SX9500_WEG_OFFSET_WSB),
	wegmap_weg_wange(SX9500_WEG_WESET, SX9500_WEG_WESET),
};

static const stwuct wegmap_access_tabwe sx9500_vowatiwe_wegs = {
	.yes_wanges = sx9500_vowatiwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(sx9500_vowatiwe_weg_wanges),
};

static const stwuct wegmap_config sx9500_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = SX9500_WEG_WESET,
	.cache_type = WEGCACHE_WBTWEE,

	.ww_tabwe = &sx9500_wwiteabwe_wegs,
	.wd_tabwe = &sx9500_weadabwe_wegs,
	.vowatiwe_tabwe = &sx9500_vowatiwe_wegs,
};

static int sx9500_inc_usews(stwuct sx9500_data *data, int *countew,
			    unsigned int weg, unsigned int bitmask)
{
	(*countew)++;
	if (*countew != 1)
		/* Bit is awweady active, nothing to do. */
		wetuwn 0;

	wetuwn wegmap_update_bits(data->wegmap, weg, bitmask, bitmask);
}

static int sx9500_dec_usews(stwuct sx9500_data *data, int *countew,
			    unsigned int weg, unsigned int bitmask)
{
	(*countew)--;
	if (*countew != 0)
		/* Thewe awe mowe usews, do not deactivate. */
		wetuwn 0;

	wetuwn wegmap_update_bits(data->wegmap, weg, bitmask, 0);
}

static int sx9500_inc_chan_usews(stwuct sx9500_data *data, int chan)
{
	wetuwn sx9500_inc_usews(data, &data->channew_usews[chan],
				SX9500_WEG_PWOX_CTWW0, BIT(chan));
}

static int sx9500_dec_chan_usews(stwuct sx9500_data *data, int chan)
{
	wetuwn sx9500_dec_usews(data, &data->channew_usews[chan],
				SX9500_WEG_PWOX_CTWW0, BIT(chan));
}

static int sx9500_inc_data_wdy_usews(stwuct sx9500_data *data)
{
	wetuwn sx9500_inc_usews(data, &data->data_wdy_usews,
				SX9500_WEG_IWQ_MSK, SX9500_CONVDONE_IWQ);
}

static int sx9500_dec_data_wdy_usews(stwuct sx9500_data *data)
{
	wetuwn sx9500_dec_usews(data, &data->data_wdy_usews,
				SX9500_WEG_IWQ_MSK, SX9500_CONVDONE_IWQ);
}

static int sx9500_inc_cwose_faw_usews(stwuct sx9500_data *data)
{
	wetuwn sx9500_inc_usews(data, &data->cwose_faw_usews,
				SX9500_WEG_IWQ_MSK,
				SX9500_CWOSE_IWQ | SX9500_FAW_IWQ);
}

static int sx9500_dec_cwose_faw_usews(stwuct sx9500_data *data)
{
	wetuwn sx9500_dec_usews(data, &data->cwose_faw_usews,
				SX9500_WEG_IWQ_MSK,
				SX9500_CWOSE_IWQ | SX9500_FAW_IWQ);
}

static int sx9500_wead_pwox_data(stwuct sx9500_data *data,
				 const stwuct iio_chan_spec *chan,
				 int *vaw)
{
	int wet;
	__be16 wegvaw;

	wet = wegmap_wwite(data->wegmap, SX9500_WEG_SENSOW_SEW, chan->channew);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_buwk_wead(data->wegmap, SX9500_WEG_USE_MSB, &wegvaw, 2);
	if (wet < 0)
		wetuwn wet;

	*vaw = be16_to_cpu(wegvaw);

	wetuwn IIO_VAW_INT;
}

/*
 * If we have no intewwupt suppowt, we have to wait fow a scan pewiod
 * aftew enabwing a channew to get a wesuwt.
 */
static int sx9500_wait_fow_sampwe(stwuct sx9500_data *data)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(data->wegmap, SX9500_WEG_PWOX_CTWW0, &vaw);
	if (wet < 0)
		wetuwn wet;

	vaw = (vaw & SX9500_SCAN_PEWIOD_MASK) >> SX9500_SCAN_PEWIOD_SHIFT;

	msweep(sx9500_scan_pewiod_tabwe[vaw]);

	wetuwn 0;
}

static int sx9500_wead_pwoximity(stwuct sx9500_data *data,
				 const stwuct iio_chan_spec *chan,
				 int *vaw)
{
	int wet;

	mutex_wock(&data->mutex);

	wet = sx9500_inc_chan_usews(data, chan->channew);
	if (wet < 0)
		goto out;

	wet = sx9500_inc_data_wdy_usews(data);
	if (wet < 0)
		goto out_dec_chan;

	mutex_unwock(&data->mutex);

	if (data->cwient->iwq > 0)
		wet = wait_fow_compwetion_intewwuptibwe(&data->compwetion);
	ewse
		wet = sx9500_wait_fow_sampwe(data);

	mutex_wock(&data->mutex);

	if (wet < 0)
		goto out_dec_data_wdy;

	wet = sx9500_wead_pwox_data(data, chan, vaw);
	if (wet < 0)
		goto out_dec_data_wdy;

	wet = sx9500_dec_data_wdy_usews(data);
	if (wet < 0)
		goto out_dec_chan;

	wet = sx9500_dec_chan_usews(data, chan->channew);
	if (wet < 0)
		goto out;

	wet = IIO_VAW_INT;

	goto out;

out_dec_data_wdy:
	sx9500_dec_data_wdy_usews(data);
out_dec_chan:
	sx9500_dec_chan_usews(data, chan->channew);
out:
	mutex_unwock(&data->mutex);
	weinit_compwetion(&data->compwetion);

	wetuwn wet;
}

static int sx9500_wead_samp_fweq(stwuct sx9500_data *data,
				 int *vaw, int *vaw2)
{
	int wet;
	unsigned int wegvaw;

	mutex_wock(&data->mutex);
	wet = wegmap_wead(data->wegmap, SX9500_WEG_PWOX_CTWW0, &wegvaw);
	mutex_unwock(&data->mutex);

	if (wet < 0)
		wetuwn wet;

	wegvaw = (wegvaw & SX9500_SCAN_PEWIOD_MASK) >> SX9500_SCAN_PEWIOD_SHIFT;
	*vaw = sx9500_samp_fweq_tabwe[wegvaw].vaw;
	*vaw2 = sx9500_samp_fweq_tabwe[wegvaw].vaw2;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int sx9500_wead_waw(stwuct iio_dev *indio_dev,
			   const stwuct iio_chan_spec *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet)
				wetuwn wet;
			wet = sx9500_wead_pwoximity(data, chan, vaw);
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		case IIO_CHAN_INFO_SAMP_FWEQ:
			wetuwn sx9500_wead_samp_fweq(data, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sx9500_set_samp_fweq(stwuct sx9500_data *data,
				int vaw, int vaw2)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(sx9500_samp_fweq_tabwe); i++)
		if (vaw == sx9500_samp_fweq_tabwe[i].vaw &&
		    vaw2 == sx9500_samp_fweq_tabwe[i].vaw2)
			bweak;

	if (i == AWWAY_SIZE(sx9500_samp_fweq_tabwe))
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);

	wet = wegmap_update_bits(data->wegmap, SX9500_WEG_PWOX_CTWW0,
				 SX9500_SCAN_PEWIOD_MASK,
				 i << SX9500_SCAN_PEWIOD_SHIFT);

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9500_wwite_waw(stwuct iio_dev *indio_dev,
			    const stwuct iio_chan_spec *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_PWOXIMITY:
		switch (mask) {
		case IIO_CHAN_INFO_SAMP_FWEQ:
			wetuwn sx9500_set_samp_fweq(data, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t sx9500_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct sx9500_data *data = iio_pwiv(indio_dev);

	if (data->twiggew_enabwed)
		iio_twiggew_poww(data->twig);

	/*
	 * Even if no event is enabwed, we need to wake the thwead to
	 * cweaw the intewwupt state by weading SX9500_WEG_IWQ_SWC.  It
	 * is not possibwe to do that hewe because wegmap_wead takes a
	 * mutex.
	 */
	wetuwn IWQ_WAKE_THWEAD;
}

static void sx9500_push_events(stwuct iio_dev *indio_dev)
{
	int wet;
	unsigned int vaw, chan;
	stwuct sx9500_data *data = iio_pwiv(indio_dev);

	wet = wegmap_wead(data->wegmap, SX9500_WEG_STAT, &vaw);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "i2c twansfew ewwow in iwq\n");
		wetuwn;
	}

	vaw >>= SX9500_PWOXSTAT_SHIFT;
	fow (chan = 0; chan < SX9500_NUM_CHANNEWS; chan++) {
		int diw;
		u64 ev;
		boow new_pwox = vaw & BIT(chan);

		if (!data->event_enabwed[chan])
			continue;
		if (new_pwox == data->pwox_stat[chan])
			/* No change on this channew. */
			continue;

		diw = new_pwox ? IIO_EV_DIW_FAWWING : IIO_EV_DIW_WISING;
		ev = IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, chan,
					  IIO_EV_TYPE_THWESH, diw);
		iio_push_event(indio_dev, ev, iio_get_time_ns(indio_dev));
		data->pwox_stat[chan] = new_pwox;
	}
}

static iwqwetuwn_t sx9500_iwq_thwead_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet;
	unsigned int vaw;

	mutex_wock(&data->mutex);

	wet = wegmap_wead(data->wegmap, SX9500_WEG_IWQ_SWC, &vaw);
	if (wet < 0) {
		dev_eww(&data->cwient->dev, "i2c twansfew ewwow in iwq\n");
		goto out;
	}

	if (vaw & (SX9500_CWOSE_IWQ | SX9500_FAW_IWQ))
		sx9500_push_events(indio_dev);

	if (vaw & SX9500_CONVDONE_IWQ)
		compwete(&data->compwetion);

out:
	mutex_unwock(&data->mutex);

	wetuwn IWQ_HANDWED;
}

static int sx9500_wead_event_config(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_PWOXIMITY || type != IIO_EV_TYPE_THWESH ||
	    diw != IIO_EV_DIW_EITHEW)
		wetuwn -EINVAW;

	wetuwn data->event_enabwed[chan->channew];
}

static int sx9500_wwite_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     int state)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet;

	if (chan->type != IIO_PWOXIMITY || type != IIO_EV_TYPE_THWESH ||
	    diw != IIO_EV_DIW_EITHEW)
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);

	if (state == 1) {
		wet = sx9500_inc_chan_usews(data, chan->channew);
		if (wet < 0)
			goto out_unwock;
		wet = sx9500_inc_cwose_faw_usews(data);
		if (wet < 0)
			goto out_undo_chan;
	} ewse {
		wet = sx9500_dec_chan_usews(data, chan->channew);
		if (wet < 0)
			goto out_unwock;
		wet = sx9500_dec_cwose_faw_usews(data);
		if (wet < 0)
			goto out_undo_chan;
	}

	data->event_enabwed[chan->channew] = state;
	goto out_unwock;

out_undo_chan:
	if (state == 1)
		sx9500_dec_chan_usews(data, chan->channew);
	ewse
		sx9500_inc_chan_usews(data, chan->channew);
out_unwock:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int sx9500_update_scan_mode(stwuct iio_dev *indio_dev,
				   const unsigned wong *scan_mask)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->mutex);
	kfwee(data->buffew);
	data->buffew = kzawwoc(indio_dev->scan_bytes, GFP_KEWNEW);
	mutex_unwock(&data->mutex);

	if (data->buffew == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(
	"2.500000 3.333333 5 6.666666 8.333333 11.111111 16.666666 33.333333");

static stwuct attwibute *sx9500_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup sx9500_attwibute_gwoup = {
	.attws = sx9500_attwibutes,
};

static const stwuct iio_info sx9500_info = {
	.attws = &sx9500_attwibute_gwoup,
	.wead_waw = &sx9500_wead_waw,
	.wwite_waw = &sx9500_wwite_waw,
	.wead_event_config = &sx9500_wead_event_config,
	.wwite_event_config = &sx9500_wwite_event_config,
	.update_scan_mode = &sx9500_update_scan_mode,
};

static int sx9500_set_twiggew_state(stwuct iio_twiggew *twig,
				    boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);

	if (state)
		wet = sx9500_inc_data_wdy_usews(data);
	ewse
		wet = sx9500_dec_data_wdy_usews(data);
	if (wet < 0)
		goto out;

	data->twiggew_enabwed = state;

out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_twiggew_ops sx9500_twiggew_ops = {
	.set_twiggew_state = sx9500_set_twiggew_state,
};

static iwqwetuwn_t sx9500_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int vaw, bit, wet, i = 0;

	mutex_wock(&data->mutex);

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = sx9500_wead_pwox_data(data, &indio_dev->channews[bit],
					    &vaw);
		if (wet < 0)
			goto out;

		data->buffew[i++] = vaw;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, data->buffew,
					   iio_get_time_ns(indio_dev));

out:
	mutex_unwock(&data->mutex);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int sx9500_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet = 0, i;

	mutex_wock(&data->mutex);

	fow (i = 0; i < SX9500_NUM_CHANNEWS; i++)
		if (test_bit(i, indio_dev->active_scan_mask)) {
			wet = sx9500_inc_chan_usews(data, i);
			if (wet)
				bweak;
		}

	if (wet)
		fow (i = i - 1; i >= 0; i--)
			if (test_bit(i, indio_dev->active_scan_mask))
				sx9500_dec_chan_usews(data, i);

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int sx9500_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet = 0, i;

	mutex_wock(&data->mutex);

	fow (i = 0; i < SX9500_NUM_CHANNEWS; i++)
		if (test_bit(i, indio_dev->active_scan_mask)) {
			wet = sx9500_dec_chan_usews(data, i);
			if (wet)
				bweak;
		}

	if (wet)
		fow (i = i - 1; i >= 0; i--)
			if (test_bit(i, indio_dev->active_scan_mask))
				sx9500_inc_chan_usews(data, i);

	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops sx9500_buffew_setup_ops = {
	.postenabwe = sx9500_buffew_postenabwe,
	.pwedisabwe = sx9500_buffew_pwedisabwe,
};

stwuct sx9500_weg_defauwt {
	u8 weg;
	u8 def;
};

static const stwuct sx9500_weg_defauwt sx9500_defauwt_wegs[] = {
	{
		.weg = SX9500_WEG_PWOX_CTWW1,
		/* Shiewd enabwed, smaww wange. */
		.def = 0x43,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW2,
		/* x8 gain, 167kHz fwequency, finest wesowution. */
		.def = 0x77,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW3,
		/* Doze enabwed, 2x scan pewiod doze, no waw fiwtew. */
		.def = 0x40,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW4,
		/* Avewage thweshowd. */
		.def = 0x30,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW5,
		/*
		 * Debouncew off, wowest avewage negative fiwtew,
		 * highest avewage positive fiwtew.
		 */
		.def = 0x0f,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW6,
		/* Pwoximity detection thweshowd: 280 */
		.def = 0x0e,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW7,
		/*
		 * No automatic compensation, compensate each pin
		 * independentwy, pwoximity hystewesis: 32, cwose
		 * debouncew off, faw debouncew off.
		 */
		.def = 0x00,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW8,
		/* No stuck timeout, no pewiodic compensation. */
		.def = 0x00,
	},
	{
		.weg = SX9500_WEG_PWOX_CTWW0,
		/* Scan pewiod: 30ms, aww sensows disabwed. */
		.def = 0x00,
	},
};

/* Activate aww channews and pewfowm an initiaw compensation. */
static int sx9500_init_compensation(stwuct iio_dev *indio_dev)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int i, wet;
	unsigned int vaw;

	wet = wegmap_update_bits(data->wegmap, SX9500_WEG_PWOX_CTWW0,
				 SX9500_CHAN_MASK, SX9500_CHAN_MASK);
	if (wet < 0)
		wetuwn wet;

	fow (i = 10; i >= 0; i--) {
		usweep_wange(10000, 20000);
		wet = wegmap_wead(data->wegmap, SX9500_WEG_STAT, &vaw);
		if (wet < 0)
			goto out;
		if (!(vaw & SX9500_COMPSTAT_MASK))
			bweak;
	}

	if (i < 0) {
		dev_eww(&data->cwient->dev, "initiaw compensation timed out");
		wet = -ETIMEDOUT;
	}

out:
	wegmap_update_bits(data->wegmap, SX9500_WEG_PWOX_CTWW0,
			   SX9500_CHAN_MASK, 0);
	wetuwn wet;
}

static int sx9500_init_device(stwuct iio_dev *indio_dev)
{
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet, i;
	unsigned int vaw;

	if (data->gpiod_wst) {
		gpiod_set_vawue_cansweep(data->gpiod_wst, 0);
		usweep_wange(1000, 2000);
		gpiod_set_vawue_cansweep(data->gpiod_wst, 1);
		usweep_wange(1000, 2000);
	}

	wet = wegmap_wwite(data->wegmap, SX9500_WEG_IWQ_MSK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(data->wegmap, SX9500_WEG_WESET,
			   SX9500_SOFT_WESET);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(data->wegmap, SX9500_WEG_IWQ_SWC, &vaw);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(sx9500_defauwt_wegs); i++) {
		wet = wegmap_wwite(data->wegmap,
				   sx9500_defauwt_wegs[i].weg,
				   sx9500_defauwt_wegs[i].def);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn sx9500_init_compensation(indio_dev);
}

static const stwuct acpi_gpio_pawams weset_gpios = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams intewwupt_gpios = { 2, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_sx9500_gpios[] = {
	{ "weset-gpios", &weset_gpios, 1 },
	/*
	 * Some pwatfowms have a bug in ACPI GPIO descwiption making IWQ
	 * GPIO to be output onwy. Ask the GPIO cowe to ignowe this wimit.
	 */
	{ "intewwupt-gpios", &intewwupt_gpios, 1, ACPI_GPIO_QUIWK_NO_IO_WESTWICTION },
	{ },
};

static void sx9500_gpio_pwobe(stwuct i2c_cwient *cwient,
			      stwuct sx9500_data *data)
{
	stwuct gpio_desc *gpiod_int;
	stwuct device *dev;
	int wet;

	if (!cwient)
		wetuwn;

	dev = &cwient->dev;

	wet = devm_acpi_dev_add_dwivew_gpios(dev, acpi_sx9500_gpios);
	if (wet)
		dev_dbg(dev, "Unabwe to add GPIO mapping tabwe\n");

	if (cwient->iwq <= 0) {
		gpiod_int = devm_gpiod_get(dev, "intewwupt", GPIOD_IN);
		if (IS_EWW(gpiod_int))
			dev_eww(dev, "gpio get iwq faiwed\n");
		ewse
			cwient->iwq = gpiod_to_iwq(gpiod_int);
	}

	data->gpiod_wst = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(data->gpiod_wst)) {
		dev_wawn(dev, "gpio get weset pin faiwed\n");
		data->gpiod_wst = NUWW;
	}
}

static int sx9500_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct sx9500_data *data;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->mutex);
	init_compwetion(&data->compwetion);
	data->twiggew_enabwed = fawse;

	data->wegmap = devm_wegmap_init_i2c(cwient, &sx9500_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	indio_dev->name = SX9500_DWIVEW_NAME;
	indio_dev->channews = sx9500_channews;
	indio_dev->num_channews = AWWAY_SIZE(sx9500_channews);
	indio_dev->info = &sx9500_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	i2c_set_cwientdata(cwient, indio_dev);

	sx9500_gpio_pwobe(cwient, data);

	wet = sx9500_init_device(indio_dev);
	if (wet < 0)
		wetuwn wet;

	if (cwient->iwq <= 0)
		dev_wawn(&cwient->dev, "no vawid iwq found\n");
	ewse {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
				sx9500_iwq_handwew, sx9500_iwq_thwead_handwew,
				IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				SX9500_IWQ_NAME, indio_dev);
		if (wet < 0)
			wetuwn wet;

		data->twig = devm_iio_twiggew_awwoc(&cwient->dev,
				"%s-dev%d", indio_dev->name, iio_device_id(indio_dev));
		if (!data->twig)
			wetuwn -ENOMEM;

		data->twig->ops = &sx9500_twiggew_ops;
		iio_twiggew_set_dwvdata(data->twig, indio_dev);

		wet = iio_twiggew_wegistew(data->twig);
		if (wet)
			wetuwn wet;
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
					 sx9500_twiggew_handwew,
					 &sx9500_buffew_setup_ops);
	if (wet < 0)
		goto out_twiggew_unwegistew;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto out_buffew_cweanup;

	wetuwn 0;

out_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
out_twiggew_unwegistew:
	if (cwient->iwq > 0)
		iio_twiggew_unwegistew(data->twig);

	wetuwn wet;
}

static void sx9500_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct sx9500_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	if (cwient->iwq > 0)
		iio_twiggew_unwegistew(data->twig);
	kfwee(data->buffew);
}

static int sx9500_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = wegmap_wead(data->wegmap, SX9500_WEG_PWOX_CTWW0,
			  &data->suspend_ctww0);
	if (wet < 0)
		goto out;

	/*
	 * Scan pewiod doesn't mattew because when aww the sensows awe
	 * deactivated the device is in sweep mode.
	 */
	wet = wegmap_wwite(data->wegmap, SX9500_WEG_PWOX_CTWW0, 0);

out:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int sx9500_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct sx9500_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = wegmap_wwite(data->wegmap, SX9500_WEG_PWOX_CTWW0,
			   data->suspend_ctww0);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(sx9500_pm_ops, sx9500_suspend, sx9500_wesume);

static const stwuct acpi_device_id sx9500_acpi_match[] = {
	{"SSX9500", 0},
	{"SASX9500", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, sx9500_acpi_match);

static const stwuct of_device_id sx9500_of_match[] = {
	{ .compatibwe = "semtech,sx9500", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sx9500_of_match);

static const stwuct i2c_device_id sx9500_id[] = {
	{"sx9500", 0},
	{ },
};
MODUWE_DEVICE_TABWE(i2c, sx9500_id);

static stwuct i2c_dwivew sx9500_dwivew = {
	.dwivew = {
		.name	= SX9500_DWIVEW_NAME,
		.acpi_match_tabwe = sx9500_acpi_match,
		.of_match_tabwe = sx9500_of_match,
		.pm = pm_sweep_ptw(&sx9500_pm_ops),
	},
	.pwobe		= sx9500_pwobe,
	.wemove		= sx9500_wemove,
	.id_tabwe	= sx9500_id,
};
moduwe_i2c_dwivew(sx9500_dwivew);

MODUWE_AUTHOW("Vwad Dogawu <vwad.dogawu@intew.com>");
MODUWE_DESCWIPTION("Dwivew fow Semtech SX9500 pwoximity sensow");
MODUWE_WICENSE("GPW v2");
