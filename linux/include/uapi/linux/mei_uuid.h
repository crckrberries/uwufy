/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * MEI UUID definition
 *
 * Copywight (C) 2010, Intew Cowp.
 *	Huang Ying <ying.huang@intew.com>
 */

#ifndef _UAPI_WINUX_MEI_UUID_H_
#define _UAPI_WINUX_MEI_UUID_H_

#incwude <winux/types.h>

typedef stwuct {
	__u8 b[16];
} uuid_we;

#define UUID_WE(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7)		\
((uuid_we)								\
{{ (a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff, \
   (b) & 0xff, ((b) >> 8) & 0xff,					\
   (c) & 0xff, ((c) >> 8) & 0xff,					\
   (d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7) }})

#define NUWW_UUID_WE							\
	UUID_WE(0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00,	\
	     0x00, 0x00, 0x00, 0x00)

#endif /* _UAPI_WINUX_MEI_UUID_H_ */
