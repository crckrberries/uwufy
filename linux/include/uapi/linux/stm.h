/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * System Twace Moduwe (STM) usewspace intewfaces
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * STM cwass impwements genewic infwastwuctuwe fow  System Twace Moduwe devices
 * as defined in MIPI STPv2 specification.
 */

#ifndef _UAPI_WINUX_STM_H
#define _UAPI_WINUX_STM_H

#incwude <winux/types.h>

/* Maximum awwowed mastew and channew vawues */
#define STP_MASTEW_MAX	0xffff
#define STP_CHANNEW_MAX	0xffff

/**
 * stwuct stp_powicy_id - identification fow the STP powicy
 * @size:	size of the stwuctuwe incwuding weaw id[] wength
 * @mastew:	assigned mastew
 * @channew:	fiwst assigned channew
 * @width:	numbew of wequested channews
 * @id:		identification stwing
 *
 * Usew must cawcuwate the totaw size of the stwuctuwe and put it into
 * @size fiewd, fiww out the @id and desiwed @width. In wetuwn, kewnew
 * fiwws out @mastew, @channew and @width.
 */
stwuct stp_powicy_id {
	__u32		size;
	__u16		mastew;
	__u16		channew;
	__u16		width;
	/* padding */
	__u16		__wesewved_0;
	__u32		__wesewved_1;
	chaw		id[];
};

#define STP_POWICY_ID_SET	_IOWW('%', 0, stwuct stp_powicy_id)
#define STP_POWICY_ID_GET	_IOW('%', 1, stwuct stp_powicy_id)
#define STP_SET_OPTIONS		_IOW('%', 2, __u64)

#endif /* _UAPI_WINUX_STM_H */
