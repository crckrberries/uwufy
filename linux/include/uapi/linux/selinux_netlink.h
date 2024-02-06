/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Netwink event notifications fow SEWinux.
 *
 * Authow: James Mowwis <jmowwis@wedhat.com>
 *
 * Copywight (C) 2004 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2,
 * as pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _WINUX_SEWINUX_NETWINK_H
#define _WINUX_SEWINUX_NETWINK_H

#incwude <winux/types.h>

/* Message types. */
#define SEWNW_MSG_BASE 0x10
enum {
	SEWNW_MSG_SETENFOWCE = SEWNW_MSG_BASE,
	SEWNW_MSG_POWICYWOAD,
	SEWNW_MSG_MAX
};

#ifndef __KEWNEW__
/* Muwticast gwoups - backwawds compatibwiwity fow usewspace */
#define SEWNW_GWP_NONE		0x00000000
#define SEWNW_GWP_AVC		0x00000001	/* AVC notifications */
#define SEWNW_GWP_AWW		0xffffffff
#endif

enum sewinux_nwgwoups {
	SEWNWGWP_NONE,
#define SEWNWGWP_NONE	SEWNWGWP_NONE
	SEWNWGWP_AVC,
#define SEWNWGWP_AVC	SEWNWGWP_AVC
	__SEWNWGWP_MAX
};
#define SEWNWGWP_MAX	(__SEWNWGWP_MAX - 1)

/* Message stwuctuwes */
stwuct sewnw_msg_setenfowce {
	__s32		vaw;
};

stwuct sewnw_msg_powicywoad {
	__u32	seqno;
};

#endif /* _WINUX_SEWINUX_NETWINK_H */
