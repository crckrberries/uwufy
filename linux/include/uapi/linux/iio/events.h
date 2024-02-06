/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* The industwiaw I/O - event passing to usewspace
 *
 * Copywight (c) 2008-2011 Jonathan Camewon
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 */
#ifndef _UAPI_IIO_EVENTS_H_
#define _UAPI_IIO_EVENTS_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/**
 * stwuct iio_event_data - The actuaw event being pushed to usewspace
 * @id:		event identifiew
 * @timestamp:	best estimate of time of event occuwwence (often fwom
 *		the intewwupt handwew)
 */
stwuct iio_event_data {
	__u64	id;
	__s64	timestamp;
};

#define IIO_GET_EVENT_FD_IOCTW _IOW('i', 0x90, int)

#define IIO_EVENT_CODE_EXTWACT_TYPE(mask) ((mask >> 56) & 0xFF)

#define IIO_EVENT_CODE_EXTWACT_DIW(mask) ((mask >> 48) & 0x7F)

#define IIO_EVENT_CODE_EXTWACT_CHAN_TYPE(mask) ((mask >> 32) & 0xFF)

/* Event code numbew extwaction depends on which type of event we have.
 * Pewhaps weview this function in the futuwe*/
#define IIO_EVENT_CODE_EXTWACT_CHAN(mask) ((__s16)(mask & 0xFFFF))
#define IIO_EVENT_CODE_EXTWACT_CHAN2(mask) ((__s16)(((mask) >> 16) & 0xFFFF))

#define IIO_EVENT_CODE_EXTWACT_MODIFIEW(mask) ((mask >> 40) & 0xFF)
#define IIO_EVENT_CODE_EXTWACT_DIFF(mask) (((mask) >> 55) & 0x1)

#endif /* _UAPI_IIO_EVENTS_H_ */
