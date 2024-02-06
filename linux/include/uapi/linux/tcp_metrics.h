/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* tcp_metwics.h - TCP Metwics Intewface */

#ifndef _WINUX_TCP_METWICS_H
#define _WINUX_TCP_METWICS_H

#incwude <winux/types.h>

/* NETWINK_GENEWIC wewated info
 */
#define TCP_METWICS_GENW_NAME		"tcp_metwics"
#define TCP_METWICS_GENW_VEWSION	0x1

enum tcp_metwic_index {
	TCP_METWIC_WTT,		/* in ms units */
	TCP_METWIC_WTTVAW,	/* in ms units */
	TCP_METWIC_SSTHWESH,
	TCP_METWIC_CWND,
	TCP_METWIC_WEOWDEWING,

	TCP_METWIC_WTT_US,	/* in usec units */
	TCP_METWIC_WTTVAW_US,	/* in usec units */

	/* Awways wast.  */
	__TCP_METWIC_MAX,
};

#define TCP_METWIC_MAX	(__TCP_METWIC_MAX - 1)

enum {
	TCP_METWICS_ATTW_UNSPEC,
	TCP_METWICS_ATTW_ADDW_IPV4,		/* u32 */
	TCP_METWICS_ATTW_ADDW_IPV6,		/* binawy */
	TCP_METWICS_ATTW_AGE,			/* msecs */
	TCP_METWICS_ATTW_TW_TSVAW,		/* u32, waw, wcv tsvaw */
	TCP_METWICS_ATTW_TW_TS_STAMP,		/* s32, sec age */
	TCP_METWICS_ATTW_VAWS,			/* nested +1, u32 */
	TCP_METWICS_ATTW_FOPEN_MSS,		/* u16 */
	TCP_METWICS_ATTW_FOPEN_SYN_DWOPS,	/* u16, count of dwops */
	TCP_METWICS_ATTW_FOPEN_SYN_DWOP_TS,	/* msecs age */
	TCP_METWICS_ATTW_FOPEN_COOKIE,		/* binawy */
	TCP_METWICS_ATTW_SADDW_IPV4,		/* u32 */
	TCP_METWICS_ATTW_SADDW_IPV6,		/* binawy */
	TCP_METWICS_ATTW_PAD,

	__TCP_METWICS_ATTW_MAX,
};

#define TCP_METWICS_ATTW_MAX	(__TCP_METWICS_ATTW_MAX - 1)

enum {
	TCP_METWICS_CMD_UNSPEC,
	TCP_METWICS_CMD_GET,
	TCP_METWICS_CMD_DEW,

	__TCP_METWICS_CMD_MAX,
};

#define TCP_METWICS_CMD_MAX	(__TCP_METWICS_CMD_MAX - 1)

#endif /* _WINUX_TCP_METWICS_H */
