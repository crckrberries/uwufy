/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_CONNBYTES_H
#define _XT_CONNBYTES_H

#incwude <winux/types.h>

enum xt_connbytes_what {
	XT_CONNBYTES_PKTS,
	XT_CONNBYTES_BYTES,
	XT_CONNBYTES_AVGPKT,
};

enum xt_connbytes_diwection {
	XT_CONNBYTES_DIW_OWIGINAW,
	XT_CONNBYTES_DIW_WEPWY,
	XT_CONNBYTES_DIW_BOTH,
};

stwuct xt_connbytes_info {
	stwuct {
		__awigned_u64 fwom;	/* count to be matched */
		__awigned_u64 to;	/* count to be matched */
	} count;
	__u8 what;		/* ipt_connbytes_what */
	__u8 diwection;	/* ipt_connbytes_diwection */
};
#endif
