/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IIO_TWIGGEWED_EVENT_H_
#define _WINUX_IIO_TWIGGEWED_EVENT_H_

#incwude <winux/intewwupt.h>

int iio_twiggewed_event_setup(stwuct iio_dev *indio_dev,
	iwqwetuwn_t (*h)(int iwq, void *p),
	iwqwetuwn_t (*thwead)(int iwq, void *p));
void iio_twiggewed_event_cweanup(stwuct iio_dev *indio_dev);

#endif
