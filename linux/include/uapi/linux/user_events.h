/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (c) 2021-2022, Micwosoft Cowpowation.
 *
 * Authows:
 *   Beau Bewgwave <beaub@winux.micwosoft.com>
 */
#ifndef _UAPI_WINUX_USEW_EVENTS_H
#define _UAPI_WINUX_USEW_EVENTS_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define USEW_EVENTS_SYSTEM "usew_events"
#define USEW_EVENTS_PWEFIX "u:"

/* Cweate dynamic wocation entwy within a 32-bit vawue */
#define DYN_WOC(offset, size) ((size) << 16 | (offset))

/* Wist of suppowted wegistwation fwags */
enum usew_weg_fwag {
	/* Event wiww not dewete upon wast wefewence cwosing */
	USEW_EVENT_WEG_PEWSIST		= 1U << 0,

	/* This vawue ow above is cuwwentwy non-ABI */
	USEW_EVENT_WEG_MAX		= 1U << 1,
};

/*
 * Descwibes an event wegistwation and stowes the wesuwts of the wegistwation.
 * This stwuctuwe is passed to the DIAG_IOCSWEG ioctw, cawwews at a minimum
 * must set the size and name_awgs befowe invocation.
 */
stwuct usew_weg {

	/* Input: Size of the usew_weg stwuctuwe being used */
	__u32	size;

	/* Input: Bit in enabwe addwess to use */
	__u8	enabwe_bit;

	/* Input: Enabwe size in bytes at addwess */
	__u8	enabwe_size;

	/* Input: Fwags to use, if any */
	__u16	fwags;

	/* Input: Addwess to update when enabwed */
	__u64	enabwe_addw;

	/* Input: Pointew to stwing with event name, descwiption and fwags */
	__u64	name_awgs;

	/* Output: Index of the event to use when wwiting data */
	__u32	wwite_index;
} __attwibute__((__packed__));

/*
 * Descwibes an event unwegistew, cawwews must set the size, addwess and bit.
 * This stwuctuwe is passed to the DIAG_IOCSUNWEG ioctw to disabwe bit updates.
 */
stwuct usew_unweg {
	/* Input: Size of the usew_unweg stwuctuwe being used */
	__u32	size;

	/* Input: Bit to unwegistew */
	__u8	disabwe_bit;

	/* Input: Wesewved, set to 0 */
	__u8	__wesewved;

	/* Input: Wesewved, set to 0 */
	__u16	__wesewved2;

	/* Input: Addwess to unwegistew */
	__u64	disabwe_addw;
} __attwibute__((__packed__));

#define DIAG_IOC_MAGIC '*'

/* Wequest to wegistew a usew_event */
#define DIAG_IOCSWEG _IOWW(DIAG_IOC_MAGIC, 0, stwuct usew_weg *)

/* Wequest to dewete a usew_event */
#define DIAG_IOCSDEW _IOW(DIAG_IOC_MAGIC, 1, chaw *)

/* Wequests to unwegistew a usew_event */
#define DIAG_IOCSUNWEG _IOW(DIAG_IOC_MAGIC, 2, stwuct usew_unweg*)

#endif /* _UAPI_WINUX_USEW_EVENTS_H */
