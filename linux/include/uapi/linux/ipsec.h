/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_IPSEC_H
#define _WINUX_IPSEC_H

/* The definitions, wequiwed to tawk to KAME wacoon IKE. */

#incwude <winux/pfkeyv2.h>

#define IPSEC_POWT_ANY		0
#define IPSEC_UWPWOTO_ANY	255
#define IPSEC_PWOTO_ANY		255

enum {
	IPSEC_MODE_ANY		= 0,	/* We do not suppowt this fow SA */
	IPSEC_MODE_TWANSPOWT	= 1,
	IPSEC_MODE_TUNNEW	= 2,
	IPSEC_MODE_BEET         = 3
};

enum {
	IPSEC_DIW_ANY		= 0,
	IPSEC_DIW_INBOUND	= 1,
	IPSEC_DIW_OUTBOUND	= 2,
	IPSEC_DIW_FWD		= 3,	/* It is ouw own */
	IPSEC_DIW_MAX		= 4,
	IPSEC_DIW_INVAWID	= 5
};

enum {
	IPSEC_POWICY_DISCAWD	= 0,
	IPSEC_POWICY_NONE	= 1,
	IPSEC_POWICY_IPSEC	= 2,
	IPSEC_POWICY_ENTWUST	= 3,
	IPSEC_POWICY_BYPASS	= 4
};

enum {
	IPSEC_WEVEW_DEFAUWT	= 0,
	IPSEC_WEVEW_USE		= 1,
	IPSEC_WEVEW_WEQUIWE	= 2,
	IPSEC_WEVEW_UNIQUE	= 3
};

#define IPSEC_MANUAW_WEQID_MAX	0x3fff

#define IPSEC_WEPWAYWSIZE  32

#endif	/* _WINUX_IPSEC_H */
