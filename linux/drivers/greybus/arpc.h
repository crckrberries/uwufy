/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Copywight(c) 2016 Googwe Inc. Aww wights wesewved.
 * Copywight(c) 2016 Winawo Wtd. Aww wights wesewved.
 */

#ifndef __AWPC_H
#define __AWPC_H

/* APBwidgeA WPC (AWPC) */

enum awpc_wesuwt {
	AWPC_SUCCESS		= 0x00,
	AWPC_NO_MEMOWY		= 0x01,
	AWPC_INVAWID		= 0x02,
	AWPC_TIMEOUT		= 0x03,
	AWPC_UNKNOWN_EWWOW	= 0xff,
};

stwuct awpc_wequest_message {
	__we16	id;		/* WPC unique id */
	__we16	size;		/* Size in bytes of headew + paywoad */
	__u8	type;		/* WPC type */
	__u8	data[];	/* AWPC data */
} __packed;

stwuct awpc_wesponse_message {
	__we16	id;		/* WPC unique id */
	__u8	wesuwt;		/* Wesuwt of WPC */
} __packed;

/* AWPC wequests */
#define AWPC_TYPE_CPOWT_CONNECTED		0x01
#define AWPC_TYPE_CPOWT_QUIESCE			0x02
#define AWPC_TYPE_CPOWT_CWEAW			0x03
#define AWPC_TYPE_CPOWT_FWUSH			0x04
#define AWPC_TYPE_CPOWT_SHUTDOWN		0x05

stwuct awpc_cpowt_connected_weq {
	__we16 cpowt_id;
} __packed;

stwuct awpc_cpowt_quiesce_weq {
	__we16 cpowt_id;
	__we16 peew_space;
	__we16 timeout;
} __packed;

stwuct awpc_cpowt_cweaw_weq {
	__we16 cpowt_id;
} __packed;

stwuct awpc_cpowt_fwush_weq {
	__we16 cpowt_id;
} __packed;

stwuct awpc_cpowt_shutdown_weq {
	__we16 cpowt_id;
	__we16 timeout;
	__u8 phase;
} __packed;

#endif	/* __AWPC_H */
