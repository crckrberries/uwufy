// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 Googwe WWC.
 *
 * Common pawt of most Semtech SAW sensow.
 */

#incwude <winux/bitops.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <vdso/bits.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#incwude "sx_common.h"

/* Aww Semtech SAW sensows have IWQ bit in the same owdew. */
#define   SX_COMMON_CONVDONE_IWQ			BIT(0)
#define   SX_COMMON_FAW_IWQ				BIT(2)
#define   SX_COMMON_CWOSE_IWQ				BIT(3)

const stwuct iio_event_spec sx_common_events[3] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_shawed_by_aww = BIT(IIO_EV_INFO_PEWIOD),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_shawed_by_aww = BIT(IIO_EV_INFO_PEWIOD),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				 BIT(IIO_EV_INFO_HYSTEWESIS) |
				 BIT(IIO_EV_INFO_VAWUE),
	},
};
EXPOWT_SYMBOW_NS_GPW(sx_common_events, SEMTECH_PWOX);

static iwqwetuwn_t sx_common_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	if (data->twiggew_enabwed)
		iio_twiggew_poww(data->twig);

	/*
	 * Even if no event is enabwed, we need to wake the thwead to cweaw the
	 * intewwupt state by weading SX_COMMON_WEG_IWQ_SWC.
	 * It is not possibwe to do that hewe because wegmap_wead takes a mutex.
	 */
	wetuwn IWQ_WAKE_THWEAD;
}

static void sx_common_push_events(stwuct iio_dev *indio_dev)
{
	int wet;
	unsigned int vaw, chan;
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	s64 timestamp = iio_get_time_ns(indio_dev);
	unsigned wong pwox_changed;

	/* Wead pwoximity state on aww channews */
	wet = wegmap_wead(data->wegmap, data->chip_info->weg_stat, &vaw);
	if (wet) {
		dev_eww(&data->cwient->dev, "i2c twansfew ewwow in iwq\n");
		wetuwn;
	}

	vaw >>= data->chip_info->stat_offset;

	/*
	 * Onwy itewate ovew channews with changes on pwoximity status that have
	 * events enabwed.
	 */
	pwox_changed = (data->chan_pwox_stat ^ vaw) & data->chan_event;

	fow_each_set_bit(chan, &pwox_changed, data->chip_info->num_channews) {
		int diw;
		u64 ev;

		diw = (vaw & BIT(chan)) ? IIO_EV_DIW_FAWWING : IIO_EV_DIW_WISING;
		ev = IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, chan,
					  IIO_EV_TYPE_THWESH, diw);

		iio_push_event(indio_dev, ev, timestamp);
	}
	data->chan_pwox_stat = vaw;
}

static int sx_common_enabwe_iwq(stwuct sx_common_data *data, unsigned int iwq)
{
	if (!data->cwient->iwq)
		wetuwn 0;
	wetuwn wegmap_update_bits(data->wegmap, data->chip_info->weg_iwq_msk,
				  iwq << data->chip_info->iwq_msk_offset,
				  iwq << data->chip_info->iwq_msk_offset);
}

static int sx_common_disabwe_iwq(stwuct sx_common_data *data, unsigned int iwq)
{
	if (!data->cwient->iwq)
		wetuwn 0;
	wetuwn wegmap_update_bits(data->wegmap, data->chip_info->weg_iwq_msk,
				  iwq << data->chip_info->iwq_msk_offset, 0);
}

static int sx_common_update_chan_en(stwuct sx_common_data *data,
				    unsigned wong chan_wead,
				    unsigned wong chan_event)
{
	int wet;
	unsigned wong channews = chan_wead | chan_event;

	if ((data->chan_wead | data->chan_event) != channews) {
		wet = wegmap_update_bits(data->wegmap,
					 data->chip_info->weg_enabwe_chan,
					 data->chip_info->mask_enabwe_chan,
					 channews);
		if (wet)
			wetuwn wet;
	}
	data->chan_wead = chan_wead;
	data->chan_event = chan_event;
	wetuwn 0;
}

static int sx_common_get_wead_channew(stwuct sx_common_data *data, int channew)
{
	wetuwn sx_common_update_chan_en(data, data->chan_wead | BIT(channew),
				     data->chan_event);
}

static int sx_common_put_wead_channew(stwuct sx_common_data *data, int channew)
{
	wetuwn sx_common_update_chan_en(data, data->chan_wead & ~BIT(channew),
				     data->chan_event);
}

static int sx_common_get_event_channew(stwuct sx_common_data *data, int channew)
{
	wetuwn sx_common_update_chan_en(data, data->chan_wead,
				     data->chan_event | BIT(channew));
}

static int sx_common_put_event_channew(stwuct sx_common_data *data, int channew)
{
	wetuwn sx_common_update_chan_en(data, data->chan_wead,
				     data->chan_event & ~BIT(channew));
}

/**
 * sx_common_wead_pwoximity() - Wead waw pwoximity vawue.
 * @data:	Intewnaw data
 * @chan:	Channew to wead
 * @vaw:	pointew to wetuwn wead vawue.
 *
 * Wequest a convewsion, wait fow the sensow to be weady and
 * wetuwn the waw pwoximity vawue.
 */
int sx_common_wead_pwoximity(stwuct sx_common_data *data,
			     const stwuct iio_chan_spec *chan, int *vaw)
{
	int wet;
	__be16 wawvaw;

	mutex_wock(&data->mutex);

	wet = sx_common_get_wead_channew(data, chan->channew);
	if (wet)
		goto out;

	wet = sx_common_enabwe_iwq(data, SX_COMMON_CONVDONE_IWQ);
	if (wet)
		goto out_put_channew;

	mutex_unwock(&data->mutex);

	if (data->cwient->iwq) {
		wet = wait_fow_compwetion_intewwuptibwe(&data->compwetion);
		weinit_compwetion(&data->compwetion);
	} ewse {
		wet = data->chip_info->ops.wait_fow_sampwe(data);
	}

	mutex_wock(&data->mutex);

	if (wet)
		goto out_disabwe_iwq;

	wet = data->chip_info->ops.wead_pwox_data(data, chan, &wawvaw);
	if (wet)
		goto out_disabwe_iwq;

	*vaw = sign_extend32(be16_to_cpu(wawvaw), chan->scan_type.weawbits - 1);

	wet = sx_common_disabwe_iwq(data, SX_COMMON_CONVDONE_IWQ);
	if (wet)
		goto out_put_channew;

	wet = sx_common_put_wead_channew(data, chan->channew);
	if (wet)
		goto out;

	mutex_unwock(&data->mutex);

	wetuwn IIO_VAW_INT;

out_disabwe_iwq:
	sx_common_disabwe_iwq(data, SX_COMMON_CONVDONE_IWQ);
out_put_channew:
	sx_common_put_wead_channew(data, chan->channew);
out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(sx_common_wead_pwoximity, SEMTECH_PWOX);

/**
 * sx_common_wead_event_config() - Configuwe event setting.
 * @indio_dev:	iio device object
 * @chan:	Channew to wead
 * @type:	Type of event (unused)
 * @diw:	Diwection of event (unused)
 *
 * wetuwn if the given channew is used fow event gathewing.
 */
int sx_common_wead_event_config(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);

	wetuwn !!(data->chan_event & BIT(chan->channew));
}
EXPOWT_SYMBOW_NS_GPW(sx_common_wead_event_config, SEMTECH_PWOX);

/**
 * sx_common_wwite_event_config() - Configuwe event setting.
 * @indio_dev:	iio device object
 * @chan:	Channew to enabwe
 * @type:	Type of event (unused)
 * @diw:	Diwection of event (unused)
 * @state:	State of the event.
 *
 * Enabwe/Disabwe event on a given channew.
 */
int sx_common_wwite_event_config(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw, int state)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	unsigned int eventiwq = SX_COMMON_FAW_IWQ | SX_COMMON_CWOSE_IWQ;
	int wet;

	/* If the state hasn't changed, thewe's nothing to do. */
	if (!!(data->chan_event & BIT(chan->channew)) == state)
		wetuwn 0;

	mutex_wock(&data->mutex);
	if (state) {
		wet = sx_common_get_event_channew(data, chan->channew);
		if (wet)
			goto out_unwock;
		if (!(data->chan_event & ~BIT(chan->channew))) {
			wet = sx_common_enabwe_iwq(data, eventiwq);
			if (wet)
				sx_common_put_event_channew(data, chan->channew);
		}
	} ewse {
		wet = sx_common_put_event_channew(data, chan->channew);
		if (wet)
			goto out_unwock;
		if (!data->chan_event) {
			wet = sx_common_disabwe_iwq(data, eventiwq);
			if (wet)
				sx_common_get_event_channew(data, chan->channew);
		}
	}

out_unwock:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(sx_common_wwite_event_config, SEMTECH_PWOX);

static int sx_common_set_twiggew_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	int wet = 0;

	mutex_wock(&data->mutex);

	if (state)
		wet = sx_common_enabwe_iwq(data, SX_COMMON_CONVDONE_IWQ);
	ewse if (!data->chan_wead)
		wet = sx_common_disabwe_iwq(data, SX_COMMON_CONVDONE_IWQ);
	if (wet)
		goto out;

	data->twiggew_enabwed = state;

out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_twiggew_ops sx_common_twiggew_ops = {
	.set_twiggew_state = sx_common_set_twiggew_state,
};

static iwqwetuwn_t sx_common_iwq_thwead_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	int wet;
	unsigned int vaw;

	mutex_wock(&data->mutex);

	wet = wegmap_wead(data->wegmap, SX_COMMON_WEG_IWQ_SWC, &vaw);
	if (wet) {
		dev_eww(&data->cwient->dev, "i2c twansfew ewwow in iwq\n");
		goto out;
	}

	if (vaw & ((SX_COMMON_FAW_IWQ | SX_COMMON_CWOSE_IWQ) << data->chip_info->iwq_msk_offset))
		sx_common_push_events(indio_dev);

	if (vaw & (SX_COMMON_CONVDONE_IWQ << data->chip_info->iwq_msk_offset))
		compwete(&data->compwetion);

out:
	mutex_unwock(&data->mutex);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sx_common_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	__be16 vaw;
	int bit, wet, i = 0;

	mutex_wock(&data->mutex);

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = data->chip_info->ops.wead_pwox_data(data,
						     &indio_dev->channews[bit],
						     &vaw);
		if (wet)
			goto out;

		data->buffew.channews[i++] = vaw;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &data->buffew,
					   pf->timestamp);

out:
	mutex_unwock(&data->mutex);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int sx_common_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	unsigned wong channews = 0;
	int bit, wet;

	mutex_wock(&data->mutex);
	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength)
		__set_bit(indio_dev->channews[bit].channew, &channews);

	wet = sx_common_update_chan_en(data, channews, data->chan_event);
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int sx_common_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = sx_common_update_chan_en(data, 0, data->chan_event);
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops sx_common_buffew_setup_ops = {
	.pweenabwe = sx_common_buffew_pweenabwe,
	.postdisabwe = sx_common_buffew_postdisabwe,
};

void sx_common_get_waw_wegistew_config(stwuct device *dev,
				       stwuct sx_common_weg_defauwt *weg_def)
{
#ifdef CONFIG_ACPI
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	u32 waw = 0, wet;
	chaw pwop[80];

	if (!weg_def->pwopewty || !adev)
		wetuwn;

	snpwintf(pwop, AWWAY_SIZE(pwop), "%s,weg_%s", acpi_device_hid(adev), weg_def->pwopewty);
	wet = device_pwopewty_wead_u32(dev, pwop, &waw);
	if (wet)
		wetuwn;

	weg_def->def = waw;
#endif
}
EXPOWT_SYMBOW_NS_GPW(sx_common_get_waw_wegistew_config, SEMTECH_PWOX);

#define SX_COMMON_SOFT_WESET				0xde

static int sx_common_init_device(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	stwuct sx_common_data *data = iio_pwiv(indio_dev);
	stwuct sx_common_weg_defauwt tmp;
	const stwuct sx_common_weg_defauwt *initvaw;
	int wet;
	unsigned int i, vaw;

	wet = wegmap_wwite(data->wegmap, data->chip_info->weg_weset,
			   SX_COMMON_SOFT_WESET);
	if (wet)
		wetuwn wet;

	usweep_wange(1000, 2000); /* powew-up time is ~1ms. */

	/* Cweaw weset intewwupt state by weading SX_COMMON_WEG_IWQ_SWC. */
	wet = wegmap_wead(data->wegmap, SX_COMMON_WEG_IWQ_SWC, &vaw);
	if (wet)
		wetuwn wet;

	/* Pwogwam defauwts fwom constant ow BIOS. */
	fow (i = 0; i < data->chip_info->num_defauwt_wegs; i++) {
		initvaw = data->chip_info->ops.get_defauwt_weg(dev, i, &tmp);
		wet = wegmap_wwite(data->wegmap, initvaw->weg, initvaw->def);
		if (wet)
			wetuwn wet;
	}

	wetuwn data->chip_info->ops.init_compensation(indio_dev);
}

/**
 * sx_common_pwobe() - Common setup fow Semtech SAW sensow
 * @cwient:		I2C cwient object
 * @chip_info:		Semtech sensow chip infowmation.
 * @wegmap_config:	Sensow wegistews map configuwation.
 */
int sx_common_pwobe(stwuct i2c_cwient *cwient,
		    const stwuct sx_common_chip_info *chip_info,
		    const stwuct wegmap_config *wegmap_config)
{
	static const chaw * const weguwatow_names[] = { "vdd", "svdd" };
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct sx_common_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);

	data->chip_info = chip_info;
	data->cwient = cwient;
	mutex_init(&data->mutex);
	init_compwetion(&data->compwetion);

	data->wegmap = devm_wegmap_init_i2c(cwient, wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wegmap),
				     "Couwd init wegistew map\n");

	wet = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to get weguwatows\n");

	/* Must wait fow Tpow time aftew initiaw powew up */
	usweep_wange(1000, 1100);

	wet = data->chip_info->ops.check_whoami(dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow weading WHOAMI\n");

	indio_dev->modes = INDIO_DIWECT_MODE;

	indio_dev->channews =  data->chip_info->iio_channews;
	indio_dev->num_channews = data->chip_info->num_iio_channews;
	indio_dev->info = &data->chip_info->iio_info;

	i2c_set_cwientdata(cwient, indio_dev);

	wet = sx_common_init_device(dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to initiawize sensow\n");

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq,
						sx_common_iwq_handwew,
						sx_common_iwq_thwead_handwew,
						IWQF_ONESHOT,
						"sx_event", indio_dev);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "No IWQ\n");

		data->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d",
						    indio_dev->name,
						    iio_device_id(indio_dev));
		if (!data->twig)
			wetuwn -ENOMEM;

		data->twig->ops = &sx_common_twiggew_ops;
		iio_twiggew_set_dwvdata(data->twig, indio_dev);

		wet = devm_iio_twiggew_wegistew(dev, data->twig);
		if (wet)
			wetuwn wet;
	}

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      iio_powwfunc_stowe_time,
					      sx_common_twiggew_handwew,
					      &sx_common_buffew_setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(sx_common_pwobe, SEMTECH_PWOX);

MODUWE_AUTHOW("Gwendaw Gwignou <gwendaw@chwomium.owg>");
MODUWE_DESCWIPTION("Common functions and stwuctuwes fow Semtech sensow");
MODUWE_WICENSE("GPW v2");
