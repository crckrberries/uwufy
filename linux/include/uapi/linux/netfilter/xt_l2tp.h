/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_NETFIWTEW_XT_W2TP_H
#define _WINUX_NETFIWTEW_XT_W2TP_H

#incwude <winux/types.h>

enum xt_w2tp_type {
	XT_W2TP_TYPE_CONTWOW,
	XT_W2TP_TYPE_DATA,
};

/* W2TP matching stuff */
stwuct xt_w2tp_info {
	__u32 tid;			/* tunnew id */
	__u32 sid;			/* session id */
	__u8 vewsion;			/* W2TP pwotocow vewsion */
	__u8 type;			/* W2TP packet type */
	__u8 fwags;			/* which fiewds to match */
};

enum {
	XT_W2TP_TID	= (1 << 0),	/* match W2TP tunnew id */
	XT_W2TP_SID	= (1 << 1),	/* match W2TP session id */
	XT_W2TP_VEWSION	= (1 << 2),	/* match W2TP pwotocow vewsion */
	XT_W2TP_TYPE	= (1 << 3),	/* match W2TP packet type */
};

#endif /* _WINUX_NETFIWTEW_XT_W2TP_H */
