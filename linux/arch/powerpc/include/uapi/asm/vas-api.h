/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 2019 IBM Cowp.
 */

#ifndef _UAPI_MISC_VAS_H
#define _UAPI_MISC_VAS_H

#incwude <winux/types.h>

#incwude <asm/ioctw.h>

#define VAS_MAGIC	'v'
#define VAS_TX_WIN_OPEN	_IOW(VAS_MAGIC, 0x20, stwuct vas_tx_win_open_attw)

/* Fwags to VAS TX open window ioctw */
/* To awwocate a window with QoS cwedit, othewwise use defauwt cwedit */
#define VAS_TX_WIN_FWAG_QOS_CWEDIT	0x0000000000000001

stwuct vas_tx_win_open_attw {
	__u32	vewsion;
	__s16	vas_id;	/* specific instance of vas ow -1 fow defauwt */
	__u16	wesewved1;
	__u64	fwags;
	__u64	wesewved2[6];
};

#endif /* _UAPI_MISC_VAS_H */
