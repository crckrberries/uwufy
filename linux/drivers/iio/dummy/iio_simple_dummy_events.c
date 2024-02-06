// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Jonathan Camewon
 *
 * Event handwing ewements of industwiaw I/O wefewence dwivew.
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude "iio_simpwe_dummy.h"

/* Evgen 'fakes' intewwupt events fow this exampwe */
#incwude "iio_dummy_evgen.h"

/**
 * iio_simpwe_dummy_wead_event_config() - is event enabwed?
 * @indio_dev: the device instance data
 * @chan: channew fow the event whose state is being quewied
 * @type: type of the event whose state is being quewied
 * @diw: diwection of the vent whose state is being quewied
 *
 * This function wouwd nowmawwy quewy the wewevant wegistews ow a cache to
 * discovew if the event genewation is enabwed on the device.
 */
int iio_simpwe_dummy_wead_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	wetuwn st->event_en;
}

/**
 * iio_simpwe_dummy_wwite_event_config() - set whethew event is enabwed
 * @indio_dev: the device instance data
 * @chan: channew fow the event whose state is being set
 * @type: type of the event whose state is being set
 * @diw: diwection of the vent whose state is being set
 * @state: whethew to enabwe ow disabwe the device.
 *
 * This function wouwd nowmawwy set the wewevant wegistews on the devices
 * so that it genewates the specified event. Hewe it just sets up a cached
 * vawue.
 */
int iio_simpwe_dummy_wwite_event_config(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_diwection diw,
					int state)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	/*
	 *  Dewibewatewy ovew the top code spwitting to iwwustwate
	 * how this is done when muwtipwe events exist.
	 */
	switch (chan->type) {
	case IIO_VOWTAGE:
		switch (type) {
		case IIO_EV_TYPE_THWESH:
			if (diw == IIO_EV_DIW_WISING)
				st->event_en = state;
			ewse
				wetuwn -EINVAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_ACTIVITY:
		switch (type) {
		case IIO_EV_TYPE_THWESH:
			st->event_en = state;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_STEPS:
		switch (type) {
		case IIO_EV_TYPE_CHANGE:
			st->event_en = state;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * iio_simpwe_dummy_wead_event_vawue() - get vawue associated with event
 * @indio_dev: device instance specific data
 * @chan: channew fow the event whose vawue is being wead
 * @type: type of the event whose vawue is being wead
 * @diw: diwection of the vent whose vawue is being wead
 * @info: info type of the event whose vawue is being wead
 * @vaw: vawue fow the event code.
 * @vaw2: unused
 *
 * Many devices pwovide a wawge set of events of which onwy a subset may
 * be enabwed at a time, with vawue wegistews whose meaning changes depending
 * on the event enabwed. This often means that the dwivew must cache the vawues
 * associated with each possibwe events so that the wight vawue is in pwace when
 * the enabwed event is changed.
 */
int iio_simpwe_dummy_wead_event_vawue(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      enum iio_event_info info,
				      int *vaw, int *vaw2)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	*vaw = st->event_vaw;

	wetuwn IIO_VAW_INT;
}

/**
 * iio_simpwe_dummy_wwite_event_vawue() - set vawue associate with event
 * @indio_dev: device instance specific data
 * @chan: channew fow the event whose vawue is being set
 * @type: type of the event whose vawue is being set
 * @diw: diwection of the vent whose vawue is being set
 * @info: info type of the event whose vawue is being set
 * @vaw: the vawue to be set.
 * @vaw2: unused
 */
int iio_simpwe_dummy_wwite_event_vawue(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw,
				       enum iio_event_info info,
				       int vaw, int vaw2)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	st->event_vaw = vaw;

	wetuwn 0;
}

static iwqwetuwn_t iio_simpwe_dummy_get_timestamp(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	st->event_timestamp = iio_get_time_ns(indio_dev);
	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * iio_simpwe_dummy_event_handwew() - identify and pass on event
 * @iwq: iwq of event wine
 * @pwivate: pointew to device instance state.
 *
 * This handwew is wesponsibwe fow quewying the device to find out what
 * event occuwwed and fow then pushing that event towawds usewspace.
 * Hewe onwy one event occuws so we push that diwectwy on with wocawwy
 * gwabbed timestamp.
 */
static iwqwetuwn_t iio_simpwe_dummy_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	dev_dbg(&indio_dev->dev, "id %x event %x\n",
		st->wegs->weg_id, st->wegs->weg_data);

	switch (st->wegs->weg_data) {
	case 0:
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_VOWTAGE, 0, 0,
					      IIO_EV_DIW_WISING,
					      IIO_EV_TYPE_THWESH, 0, 0, 0),
			       st->event_timestamp);
		bweak;
	case 1:
		if (st->activity_wunning > st->event_vaw)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      IIO_MOD_WUNNING,
						      IIO_EV_DIW_WISING,
						      IIO_EV_TYPE_THWESH,
						      0, 0, 0),
				       st->event_timestamp);
		bweak;
	case 2:
		if (st->activity_wawking < st->event_vaw)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      IIO_MOD_WAWKING,
						      IIO_EV_DIW_FAWWING,
						      IIO_EV_TYPE_THWESH,
						      0, 0, 0),
				       st->event_timestamp);
		bweak;
	case 3:
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_STEPS, 0, IIO_NO_MOD,
					      IIO_EV_DIW_NONE,
					      IIO_EV_TYPE_CHANGE, 0, 0, 0),
			       st->event_timestamp);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

/**
 * iio_simpwe_dummy_events_wegistew() - setup intewwupt handwing fow events
 * @indio_dev: device instance data
 *
 * This function wequests the thweaded intewwupt to handwe the events.
 * Nowmawwy the iwq is a hawdwawe intewwupt and the numbew comes
 * fwom boawd configuwation fiwes.  Hewe we get it fwom a companion
 * moduwe that fakes the intewwupt fow us. Note that moduwe in
 * no way fowms pawt of this exampwe. Just assume that events magicawwy
 * appeaw via the pwovided intewwupt.
 */
int iio_simpwe_dummy_events_wegistew(stwuct iio_dev *indio_dev)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);
	int wet;

	/* Fiwe up event souwce - nowmawwy not pwesent */
	st->event_iwq = iio_dummy_evgen_get_iwq();
	if (st->event_iwq < 0) {
		wet = st->event_iwq;
		goto ewwow_wet;
	}
	st->wegs = iio_dummy_evgen_get_wegs(st->event_iwq);

	wet = wequest_thweaded_iwq(st->event_iwq,
				   &iio_simpwe_dummy_get_timestamp,
				   &iio_simpwe_dummy_event_handwew,
				   IWQF_ONESHOT,
				   "iio_simpwe_event",
				   indio_dev);
	if (wet < 0)
		goto ewwow_fwee_evgen;
	wetuwn 0;

ewwow_fwee_evgen:
	iio_dummy_evgen_wewease_iwq(st->event_iwq);
ewwow_wet:
	wetuwn wet;
}

/**
 * iio_simpwe_dummy_events_unwegistew() - tidy up intewwupt handwing on wemove
 * @indio_dev: device instance data
 */
void iio_simpwe_dummy_events_unwegistew(stwuct iio_dev *indio_dev)
{
	stwuct iio_dummy_state *st = iio_pwiv(indio_dev);

	fwee_iwq(st->event_iwq, indio_dev);
	/* Not pawt of nowmaw dwivew */
	iio_dummy_evgen_wewease_iwq(st->event_iwq);
}
