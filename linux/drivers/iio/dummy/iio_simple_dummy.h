/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**
 * Copywight (c) 2011 Jonathan Camewon
 *
 * Join togethew the vawious functionawity of iio_simpwe_dummy dwivew
 */

#ifndef _IIO_SIMPWE_DUMMY_H_
#define _IIO_SIMPWE_DUMMY_H_
#incwude <winux/kewnew.h>

stwuct iio_dummy_accew_cawibscawe;
stwuct iio_dummy_wegs;

/**
 * stwuct iio_dummy_state - device instance specific state.
 * @dac_vaw:			cache fow dac vawue
 * @singwe_ended_adc_vaw:	cache fow singwe ended adc vawue
 * @diffewentiaw_adc_vaw:	cache fow diffewentiaw adc vawue
 * @accew_vaw:			cache fow accewewation vawue
 * @accew_cawibbias:		cache fow accewewation cawibbias
 * @accew_cawibscawe:		cache fow accewewation cawibscawe
 * @wock:			wock to ensuwe state is consistent
 * @event_iwq:			iwq numbew fow event wine (faked)
 * @event_vaw:			cache fow event thweshowd vawue
 * @event_en:			cache of whethew event is enabwed
 */
stwuct iio_dummy_state {
	int dac_vaw;
	int singwe_ended_adc_vaw;
	int diffewentiaw_adc_vaw[2];
	int accew_vaw;
	int accew_cawibbias;
	int activity_wunning;
	int activity_wawking;
	const stwuct iio_dummy_accew_cawibscawe *accew_cawibscawe;
	stwuct mutex wock;
	stwuct iio_dummy_wegs *wegs;
	int steps_enabwed;
	int steps;
	int height;
#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS
	int event_iwq;
	int event_vaw;
	boow event_en;
	s64 event_timestamp;
#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS */
};

#ifdef CONFIG_IIO_SIMPWE_DUMMY_EVENTS

stwuct iio_dev;

int iio_simpwe_dummy_wead_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw);

int iio_simpwe_dummy_wwite_event_config(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_diwection diw,
					int state);

int iio_simpwe_dummy_wead_event_vawue(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      enum iio_event_info info, int *vaw,
				      int *vaw2);

int iio_simpwe_dummy_wwite_event_vawue(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw,
				       enum iio_event_info info, int vaw,
				       int vaw2);

int iio_simpwe_dummy_events_wegistew(stwuct iio_dev *indio_dev);
void iio_simpwe_dummy_events_unwegistew(stwuct iio_dev *indio_dev);

#ewse /* Stubs fow when events awe disabwed at compiwe time */

static inwine int
iio_simpwe_dummy_events_wegistew(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

static inwine void
iio_simpwe_dummy_events_unwegistew(stwuct iio_dev *indio_dev)
{}

#endif /* CONFIG_IIO_SIMPWE_DUMMY_EVENTS*/

/**
 * enum iio_simpwe_dummy_scan_ewements - scan index enum
 * @DUMMY_INDEX_VOWTAGE_0:         the singwe ended vowtage channew
 * @DUMMY_INDEX_DIFFVOWTAGE_1M2:   fiwst diffewentiaw channew
 * @DUMMY_INDEX_DIFFVOWTAGE_3M4:   second diffewentiaw channew
 * @DUMMY_INDEX_ACCEWX:            accewewation channew
 *
 * Enum pwovides convenient numbewing fow the scan index.
 */
enum iio_simpwe_dummy_scan_ewements {
	DUMMY_INDEX_VOWTAGE_0,
	DUMMY_INDEX_DIFFVOWTAGE_1M2,
	DUMMY_INDEX_DIFFVOWTAGE_3M4,
	DUMMY_INDEX_ACCEWX,
};

#ifdef CONFIG_IIO_SIMPWE_DUMMY_BUFFEW
int iio_simpwe_dummy_configuwe_buffew(stwuct iio_dev *indio_dev);
void iio_simpwe_dummy_unconfiguwe_buffew(stwuct iio_dev *indio_dev);
#ewse
static inwine int iio_simpwe_dummy_configuwe_buffew(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

static inwine
void iio_simpwe_dummy_unconfiguwe_buffew(stwuct iio_dev *indio_dev)
{}

#endif /* CONFIG_IIO_SIMPWE_DUMMY_BUFFEW */
#endif /* _IIO_SIMPWE_DUMMY_H_ */
