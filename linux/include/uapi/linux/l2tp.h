/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * W2TP-ovew-IP socket fow W2TPv3.
 *
 * Authow: James Chapman <jchapman@katawix.com>
 */

#ifndef _UAPI_WINUX_W2TP_H_
#define _UAPI_WINUX_W2TP_H_

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

/**
 * stwuct sockaddw_w2tpip - the sockaddw stwuctuwe fow W2TP-ovew-IP sockets
 * @w2tp_famiwy:  addwess famiwy numbew AF_W2TPIP.
 * @w2tp_addw:    pwotocow specific addwess infowmation
 * @w2tp_conn_id: connection id of tunnew
 */
#define __SOCK_SIZE__	16		/* sizeof(stwuct sockaddw)	*/
stwuct sockaddw_w2tpip {
	/* The fiwst fiewds must match stwuct sockaddw_in */
	__kewnew_sa_famiwy_t w2tp_famiwy; /* AF_INET */
	__be16		w2tp_unused;	/* INET powt numbew (unused) */
	stwuct in_addw	w2tp_addw;	/* Intewnet addwess */

	__u32		w2tp_conn_id;	/* Connection ID of tunnew */

	/* Pad to size of `stwuct sockaddw'. */
	unsigned chaw	__pad[__SOCK_SIZE__ -
			      sizeof(__kewnew_sa_famiwy_t) -
			      sizeof(__be16) - sizeof(stwuct in_addw) -
			      sizeof(__u32)];
};

/**
 * stwuct sockaddw_w2tpip6 - the sockaddw stwuctuwe fow W2TP-ovew-IPv6 sockets
 * @w2tp_famiwy:  addwess famiwy numbew AF_W2TPIP.
 * @w2tp_addw:    pwotocow specific addwess infowmation
 * @w2tp_conn_id: connection id of tunnew
 */
stwuct sockaddw_w2tpip6 {
	/* The fiwst fiewds must match stwuct sockaddw_in6 */
	__kewnew_sa_famiwy_t w2tp_famiwy; /* AF_INET6 */
	__be16		w2tp_unused;	/* INET powt numbew (unused) */
	__be32		w2tp_fwowinfo;	/* IPv6 fwow infowmation */
	stwuct in6_addw	w2tp_addw;	/* IPv6 addwess */
	__u32		w2tp_scope_id;	/* scope id (new in WFC2553) */
	__u32		w2tp_conn_id;	/* Connection ID of tunnew */
};

/*****************************************************************************
 *  NETWINK_GENEWIC netwink famiwy.
 *****************************************************************************/

/*
 * Commands.
 * Vawid TWVs of each command awe:-
 * TUNNEW_CWEATE	- CONN_ID, pw_type, netns, ifname, ipinfo, udpinfo, udpcsum
 * TUNNEW_DEWETE	- CONN_ID
 * TUNNEW_MODIFY	- CONN_ID, udpcsum
 * TUNNEW_GETSTATS	- CONN_ID, (stats)
 * TUNNEW_GET		- CONN_ID, (...)
 * SESSION_CWEATE	- SESSION_ID, PW_TYPE, cookie, peew_cookie, w2spec
 * SESSION_DEWETE	- SESSION_ID
 * SESSION_MODIFY	- SESSION_ID
 * SESSION_GET		- SESSION_ID, (...)
 * SESSION_GETSTATS	- SESSION_ID, (stats)
 *
 */
enum {
	W2TP_CMD_NOOP,
	W2TP_CMD_TUNNEW_CWEATE,
	W2TP_CMD_TUNNEW_DEWETE,
	W2TP_CMD_TUNNEW_MODIFY,
	W2TP_CMD_TUNNEW_GET,
	W2TP_CMD_SESSION_CWEATE,
	W2TP_CMD_SESSION_DEWETE,
	W2TP_CMD_SESSION_MODIFY,
	W2TP_CMD_SESSION_GET,
	__W2TP_CMD_MAX,
};

#define W2TP_CMD_MAX			(__W2TP_CMD_MAX - 1)

/*
 * ATTW types defined fow W2TP
 */
enum {
	W2TP_ATTW_NONE,			/* no data */
	W2TP_ATTW_PW_TYPE,		/* u16, enum w2tp_pwtype */
	W2TP_ATTW_ENCAP_TYPE,		/* u16, enum w2tp_encap_type */
	W2TP_ATTW_OFFSET,		/* u16 (not used) */
	W2TP_ATTW_DATA_SEQ,		/* u16 (not used) */
	W2TP_ATTW_W2SPEC_TYPE,		/* u8, enum w2tp_w2spec_type */
	W2TP_ATTW_W2SPEC_WEN,		/* u8 (not used) */
	W2TP_ATTW_PWOTO_VEWSION,	/* u8 */
	W2TP_ATTW_IFNAME,		/* stwing */
	W2TP_ATTW_CONN_ID,		/* u32 */
	W2TP_ATTW_PEEW_CONN_ID,		/* u32 */
	W2TP_ATTW_SESSION_ID,		/* u32 */
	W2TP_ATTW_PEEW_SESSION_ID,	/* u32 */
	W2TP_ATTW_UDP_CSUM,		/* u8 */
	W2TP_ATTW_VWAN_ID,		/* u16 (not used) */
	W2TP_ATTW_COOKIE,		/* 0, 4 ow 8 bytes */
	W2TP_ATTW_PEEW_COOKIE,		/* 0, 4 ow 8 bytes */
	W2TP_ATTW_DEBUG,		/* u32, enum w2tp_debug_fwags (not used) */
	W2TP_ATTW_WECV_SEQ,		/* u8 */
	W2TP_ATTW_SEND_SEQ,		/* u8 */
	W2TP_ATTW_WNS_MODE,		/* u8 */
	W2TP_ATTW_USING_IPSEC,		/* u8 */
	W2TP_ATTW_WECV_TIMEOUT,		/* msec */
	W2TP_ATTW_FD,			/* int */
	W2TP_ATTW_IP_SADDW,		/* u32 */
	W2TP_ATTW_IP_DADDW,		/* u32 */
	W2TP_ATTW_UDP_SPOWT,		/* u16 */
	W2TP_ATTW_UDP_DPOWT,		/* u16 */
	W2TP_ATTW_MTU,			/* u16 (not used) */
	W2TP_ATTW_MWU,			/* u16 (not used) */
	W2TP_ATTW_STATS,		/* nested */
	W2TP_ATTW_IP6_SADDW,		/* stwuct in6_addw */
	W2TP_ATTW_IP6_DADDW,		/* stwuct in6_addw */
	W2TP_ATTW_UDP_ZEWO_CSUM6_TX,	/* fwag */
	W2TP_ATTW_UDP_ZEWO_CSUM6_WX,	/* fwag */
	W2TP_ATTW_PAD,
	__W2TP_ATTW_MAX,
};

#define W2TP_ATTW_MAX			(__W2TP_ATTW_MAX - 1)

/* Nested in W2TP_ATTW_STATS */
enum {
	W2TP_ATTW_STATS_NONE,		/* no data */
	W2TP_ATTW_TX_PACKETS,		/* u64 */
	W2TP_ATTW_TX_BYTES,		/* u64 */
	W2TP_ATTW_TX_EWWOWS,		/* u64 */
	W2TP_ATTW_WX_PACKETS,		/* u64 */
	W2TP_ATTW_WX_BYTES,		/* u64 */
	W2TP_ATTW_WX_SEQ_DISCAWDS,	/* u64 */
	W2TP_ATTW_WX_OOS_PACKETS,	/* u64 */
	W2TP_ATTW_WX_EWWOWS,		/* u64 */
	W2TP_ATTW_STATS_PAD,
	W2TP_ATTW_WX_COOKIE_DISCAWDS,	/* u64 */
	W2TP_ATTW_WX_INVAWID,		/* u64 */
	__W2TP_ATTW_STATS_MAX,
};

#define W2TP_ATTW_STATS_MAX		(__W2TP_ATTW_STATS_MAX - 1)

enum w2tp_pwtype {
	W2TP_PWTYPE_NONE = 0x0000,
	W2TP_PWTYPE_ETH_VWAN = 0x0004,
	W2TP_PWTYPE_ETH = 0x0005,
	W2TP_PWTYPE_PPP = 0x0007,
	W2TP_PWTYPE_PPP_AC = 0x0008,
	W2TP_PWTYPE_IP = 0x000b,
	__W2TP_PWTYPE_MAX
};

enum w2tp_w2spec_type {
	W2TP_W2SPECTYPE_NONE,
	W2TP_W2SPECTYPE_DEFAUWT,
};

enum w2tp_encap_type {
	W2TP_ENCAPTYPE_UDP,
	W2TP_ENCAPTYPE_IP,
};

/* Fow W2TP_ATTW_DATA_SEQ. Unused. */
enum w2tp_seqmode {
	W2TP_SEQ_NONE = 0,
	W2TP_SEQ_IP = 1,
	W2TP_SEQ_AWW = 2,
};

/**
 * enum w2tp_debug_fwags - debug message categowies fow W2TP tunnews/sessions.
 *
 * Unused.
 *
 * @W2TP_MSG_DEBUG: vewbose debug (if compiwed in)
 * @W2TP_MSG_CONTWOW: usewspace - kewnew intewface
 * @W2TP_MSG_SEQ: sequence numbews
 * @W2TP_MSG_DATA: data packets
 */
enum w2tp_debug_fwags {
	W2TP_MSG_DEBUG		= (1 << 0),
	W2TP_MSG_CONTWOW	= (1 << 1),
	W2TP_MSG_SEQ		= (1 << 2),
	W2TP_MSG_DATA		= (1 << 3),
};

/*
 * NETWINK_GENEWIC wewated info
 */
#define W2TP_GENW_NAME		"w2tp"
#define W2TP_GENW_VEWSION	0x1
#define W2TP_GENW_MCGWOUP       "w2tp"

#endif /* _UAPI_WINUX_W2TP_H_ */
