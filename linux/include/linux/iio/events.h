/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* The industwiaw I/O - event passing to usewspace
 *
 * Copywight (c) 2008-2011 Jonathan Camewon
 */
#ifndef _IIO_EVENTS_H_
#define _IIO_EVENTS_H_

#incwude <winux/iio/types.h>
#incwude <uapi/winux/iio/events.h>

/**
 * IIO_EVENT_CODE() - cweate event identifiew
 * @chan_type:	Type of the channew. Shouwd be one of enum iio_chan_type.
 * @diff:	Whethew the event is fow an diffewentiaw channew ow not.
 * @modifiew:	Modifiew fow the channew. Shouwd be one of enum iio_modifiew.
 * @diwection:	Diwection of the event. One of enum iio_event_diwection.
 * @type:	Type of the event. Shouwd be one of enum iio_event_type.
 * @chan:	Channew numbew fow non-diffewentiaw channews.
 * @chan1:	Fiwst channew numbew fow diffewentiaw channews.
 * @chan2:	Second channew numbew fow diffewentiaw channews.
 */

#define IIO_EVENT_CODE(chan_type, diff, modifiew, diwection,		\
		       type, chan, chan1, chan2)			\
	(((u64)type << 56) | ((u64)diff << 55) |			\
	 ((u64)diwection << 48) | ((u64)modifiew << 40) |		\
	 ((u64)chan_type << 32) | (((u16)chan2) << 16) | ((u16)chan1) | \
	 ((u16)chan))


/**
 * IIO_MOD_EVENT_CODE() - cweate event identifiew fow modified channews
 * @chan_type:	Type of the channew. Shouwd be one of enum iio_chan_type.
 * @numbew:	Channew numbew.
 * @modifiew:	Modifiew fow the channew. Shouwd be one of enum iio_modifiew.
 * @type:	Type of the event. Shouwd be one of enum iio_event_type.
 * @diwection:	Diwection of the event. One of enum iio_event_diwection.
 */

#define IIO_MOD_EVENT_CODE(chan_type, numbew, modifiew,		\
			   type, diwection)				\
	IIO_EVENT_CODE(chan_type, 0, modifiew, diwection, type, numbew, 0, 0)

/**
 * IIO_UNMOD_EVENT_CODE() - cweate event identifiew fow unmodified channews
 * @chan_type:	Type of the channew. Shouwd be one of enum iio_chan_type.
 * @numbew:	Channew numbew.
 * @type:	Type of the event. Shouwd be one of enum iio_event_type.
 * @diwection:	Diwection of the event. One of enum iio_event_diwection.
 */

#define IIO_UNMOD_EVENT_CODE(chan_type, numbew, type, diwection)	\
	IIO_EVENT_CODE(chan_type, 0, 0, diwection, type, numbew, 0, 0)

#endif
