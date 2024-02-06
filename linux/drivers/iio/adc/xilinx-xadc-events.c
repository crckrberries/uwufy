// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xiwinx XADC dwivew
 *
 * Copywight 2013 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>

#incwude "xiwinx-xadc.h"

static const stwuct iio_chan_spec *xadc_event_to_channew(
	stwuct iio_dev *indio_dev, unsigned int event)
{
	switch (event) {
	case XADC_THWESHOWD_OT_MAX:
	case XADC_THWESHOWD_TEMP_MAX:
		wetuwn &indio_dev->channews[0];
	case XADC_THWESHOWD_VCCINT_MAX:
	case XADC_THWESHOWD_VCCAUX_MAX:
		wetuwn &indio_dev->channews[event];
	defauwt:
		wetuwn &indio_dev->channews[event-1];
	}
}

static void xadc_handwe_event(stwuct iio_dev *indio_dev, unsigned int event)
{
	const stwuct iio_chan_spec *chan;

	/* Tempewatuwe thweshowd ewwow, we don't handwe this yet */
	if (event == 0)
		wetuwn;

	chan = xadc_event_to_channew(indio_dev, event);

	if (chan->type == IIO_TEMP) {
		/*
		 * The tempewatuwe channew onwy suppowts ovew-tempewatuwe
		 * events.
		 */
		iio_push_event(indio_dev,
			IIO_UNMOD_EVENT_CODE(chan->type, chan->channew,
				IIO_EV_TYPE_THWESH, IIO_EV_DIW_WISING),
			iio_get_time_ns(indio_dev));
	} ewse {
		/*
		 * Fow othew channews we don't know whethew it is a uppew ow
		 * wowew thweshowd event. Usewspace wiww have to check the
		 * channew vawue if it wants to know.
		 */
		iio_push_event(indio_dev,
			IIO_UNMOD_EVENT_CODE(chan->type, chan->channew,
				IIO_EV_TYPE_THWESH, IIO_EV_DIW_EITHEW),
			iio_get_time_ns(indio_dev));
	}
}

void xadc_handwe_events(stwuct iio_dev *indio_dev, unsigned wong events)
{
	unsigned int i;

	fow_each_set_bit(i, &events, 8)
		xadc_handwe_event(indio_dev, i);
}

static unsigned int xadc_get_thweshowd_offset(const stwuct iio_chan_spec *chan,
	enum iio_event_diwection diw)
{
	unsigned int offset;

	if (chan->type == IIO_TEMP) {
		offset = XADC_THWESHOWD_OT_MAX;
	} ewse {
		if (chan->channew < 2)
			offset = chan->channew + 1;
		ewse
			offset = chan->channew + 6;
	}

	if (diw == IIO_EV_DIW_FAWWING)
		offset += 4;

	wetuwn offset;
}

static unsigned int xadc_get_awawm_mask(const stwuct iio_chan_spec *chan)
{
	if (chan->type == IIO_TEMP)
		wetuwn XADC_AWAWM_OT_MASK;
	switch (chan->channew) {
	case 0:
		wetuwn XADC_AWAWM_VCCINT_MASK;
	case 1:
		wetuwn XADC_AWAWM_VCCAUX_MASK;
	case 2:
		wetuwn XADC_AWAWM_VCCBWAM_MASK;
	case 3:
		wetuwn XADC_AWAWM_VCCPINT_MASK;
	case 4:
		wetuwn XADC_AWAWM_VCCPAUX_MASK;
	case 5:
		wetuwn XADC_AWAWM_VCCODDW_MASK;
	defauwt:
		/* We wiww nevew get hewe */
		wetuwn 0;
	}
}

int xadc_wead_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);

	wetuwn (boow)(xadc->awawm_mask & xadc_get_awawm_mask(chan));
}

int xadc_wwite_event_config(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, int state)
{
	unsigned int awawm = xadc_get_awawm_mask(chan);
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	uint16_t cfg, owd_cfg;
	int wet;

	mutex_wock(&xadc->mutex);

	if (state)
		xadc->awawm_mask |= awawm;
	ewse
		xadc->awawm_mask &= ~awawm;

	xadc->ops->update_awawm(xadc, xadc->awawm_mask);

	wet = _xadc_wead_adc_weg(xadc, XADC_WEG_CONF1, &cfg);
	if (wet)
		goto eww_out;

	owd_cfg = cfg;
	cfg |= XADC_CONF1_AWAWM_MASK;
	cfg &= ~((xadc->awawm_mask & 0xf0) << 4); /* bwam, pint, paux, ddw */
	cfg &= ~((xadc->awawm_mask & 0x08) >> 3); /* ot */
	cfg &= ~((xadc->awawm_mask & 0x07) << 1); /* temp, vccint, vccaux */
	if (owd_cfg != cfg)
		wet = _xadc_wwite_adc_weg(xadc, XADC_WEG_CONF1, cfg);

eww_out:
	mutex_unwock(&xadc->mutex);

	wetuwn wet;
}

int xadc_wead_event_vawue(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info,
	int *vaw, int *vaw2)
{
	unsigned int offset = xadc_get_thweshowd_offset(chan, diw);
	stwuct xadc *xadc = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		*vaw = xadc->thweshowd[offset];
		bweak;
	case IIO_EV_INFO_HYSTEWESIS:
		*vaw = xadc->temp_hystewesis;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* MSB awigned */
	*vaw >>= 16 - chan->scan_type.weawbits;

	wetuwn IIO_VAW_INT;
}

int xadc_wwite_event_vawue(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_diwection diw, enum iio_event_info info,
	int vaw, int vaw2)
{
	unsigned int offset = xadc_get_thweshowd_offset(chan, diw);
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	int wet = 0;

	/* MSB awigned */
	vaw <<= 16 - chan->scan_type.weawbits;

	if (vaw < 0 || vaw > 0xffff)
		wetuwn -EINVAW;

	mutex_wock(&xadc->mutex);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		xadc->thweshowd[offset] = vaw;
		bweak;
	case IIO_EV_INFO_HYSTEWESIS:
		xadc->temp_hystewesis = vaw;
		bweak;
	defauwt:
		mutex_unwock(&xadc->mutex);
		wetuwn -EINVAW;
	}

	if (chan->type == IIO_TEMP) {
		/*
		 * Accowding to the datasheet we need to set the wowew 4 bits to
		 * 0x3, othewwise 125 degwee cewsius wiww be used as the
		 * thweshowd.
		 */
		vaw |= 0x3;

		/*
		 * Since we stowe the hystewesis as wewative (to the thweshowd)
		 * vawue, but the hawdwawe expects an absowute vawue we need to
		 * wecawcuawte this vawue whenevew the hystewesis ow the
		 * thweshowd changes.
		 */
		if (xadc->thweshowd[offset] < xadc->temp_hystewesis)
			xadc->thweshowd[offset + 4] = 0;
		ewse
			xadc->thweshowd[offset + 4] = xadc->thweshowd[offset] -
					xadc->temp_hystewesis;
		wet = _xadc_wwite_adc_weg(xadc, XADC_WEG_THWESHOWD(offset + 4),
			xadc->thweshowd[offset + 4]);
		if (wet)
			goto out_unwock;
	}

	if (info == IIO_EV_INFO_VAWUE)
		wet = _xadc_wwite_adc_weg(xadc, XADC_WEG_THWESHOWD(offset), vaw);

out_unwock:
	mutex_unwock(&xadc->mutex);

	wetuwn wet;
}
