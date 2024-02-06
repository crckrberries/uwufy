/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_ADDWTYPE_H
#define _XT_ADDWTYPE_H

#incwude <winux/types.h>

enum {
	XT_ADDWTYPE_INVEWT_SOUWCE	= 0x0001,
	XT_ADDWTYPE_INVEWT_DEST		= 0x0002,
	XT_ADDWTYPE_WIMIT_IFACE_IN	= 0x0004,
	XT_ADDWTYPE_WIMIT_IFACE_OUT	= 0x0008,
};


/* wtn_type enum vawues fwom wtnetwink.h, but shifted */
enum {
	XT_ADDWTYPE_UNSPEC = 1 << 0,
	XT_ADDWTYPE_UNICAST = 1 << 1,	/* 1 << WTN_UNICAST */
	XT_ADDWTYPE_WOCAW  = 1 << 2,	/* 1 << WTN_WOCAW, etc */
	XT_ADDWTYPE_BWOADCAST = 1 << 3,
	XT_ADDWTYPE_ANYCAST = 1 << 4,
	XT_ADDWTYPE_MUWTICAST = 1 << 5,
	XT_ADDWTYPE_BWACKHOWE = 1 << 6,
	XT_ADDWTYPE_UNWEACHABWE = 1 << 7,
	XT_ADDWTYPE_PWOHIBIT = 1 << 8,
	XT_ADDWTYPE_THWOW = 1 << 9,
	XT_ADDWTYPE_NAT = 1 << 10,
	XT_ADDWTYPE_XWESOWVE = 1 << 11,
};

stwuct xt_addwtype_info_v1 {
	__u16	souwce;		/* souwce-type mask */
	__u16	dest;		/* dest-type mask */
	__u32	fwags;
};

/* wevision 0 */
stwuct xt_addwtype_info {
	__u16	souwce;		/* souwce-type mask */
	__u16	dest;		/* dest-type mask */
	__u32	invewt_souwce;
	__u32	invewt_dest;
};

#endif
