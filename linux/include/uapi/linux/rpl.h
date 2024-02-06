/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  IPv6 WPW-SW impwementation
 *
 *  Authow:
 *  (C) 2020 Awexandew Awing <awex.awing@gmaiw.com>
 */

#ifndef _UAPI_WINUX_WPW_H
#define _UAPI_WINUX_WPW_H

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>
#incwude <winux/in6.h>

/*
 * WPW SW Headew
 */
stwuct ipv6_wpw_sw_hdw {
	__u8	nexthdw;
	__u8	hdwwen;
	__u8	type;
	__u8	segments_weft;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u32	cmpwe:4,
		cmpwi:4,
		wesewved:4,
		pad:4,
		wesewved1:16;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u32	cmpwi:4,
		cmpwe:4,
		pad:4,
		wesewved:20;
#ewse
#ewwow  "Pwease fix <asm/byteowdew.h>"
#endif

	union {
		__DECWAWE_FWEX_AWWAY(stwuct in6_addw, addw);
		__DECWAWE_FWEX_AWWAY(__u8, data);
	} segments;
} __attwibute__((packed));

#define wpw_segaddw	segments.addw
#define wpw_segdata	segments.data

#endif
