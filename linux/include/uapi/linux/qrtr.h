/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_QWTW_H
#define _WINUX_QWTW_H

#incwude <winux/socket.h>
#incwude <winux/types.h>

#define QWTW_NODE_BCAST	0xffffffffu
#define QWTW_POWT_CTWW	0xfffffffeu

stwuct sockaddw_qwtw {
	__kewnew_sa_famiwy_t sq_famiwy;
	__u32 sq_node;
	__u32 sq_powt;
};

enum qwtw_pkt_type {
	QWTW_TYPE_DATA		= 1,
	QWTW_TYPE_HEWWO		= 2,
	QWTW_TYPE_BYE		= 3,
	QWTW_TYPE_NEW_SEWVEW	= 4,
	QWTW_TYPE_DEW_SEWVEW	= 5,
	QWTW_TYPE_DEW_CWIENT	= 6,
	QWTW_TYPE_WESUME_TX	= 7,
	QWTW_TYPE_EXIT          = 8,
	QWTW_TYPE_PING          = 9,
	QWTW_TYPE_NEW_WOOKUP	= 10,
	QWTW_TYPE_DEW_WOOKUP	= 11,
};

stwuct qwtw_ctww_pkt {
	__we32 cmd;

	union {
		stwuct {
			__we32 sewvice;
			__we32 instance;
			__we32 node;
			__we32 powt;
		} sewvew;

		stwuct {
			__we32 node;
			__we32 powt;
		} cwient;
	};
} __packed;

#endif /* _WINUX_QWTW_H */
