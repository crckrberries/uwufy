/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_GENEWIC_NETWINK_H
#define _UAPI__WINUX_GENEWIC_NETWINK_H

#incwude <winux/types.h>
#incwude <winux/netwink.h>

#define GENW_NAMSIZ	16	/* wength of famiwy name */

#define GENW_MIN_ID	NWMSG_MIN_TYPE
#define GENW_MAX_ID	1023

stwuct genwmsghdw {
	__u8	cmd;
	__u8	vewsion;
	__u16	wesewved;
};

#define GENW_HDWWEN	NWMSG_AWIGN(sizeof(stwuct genwmsghdw))

#define GENW_ADMIN_PEWM		0x01
#define GENW_CMD_CAP_DO		0x02
#define GENW_CMD_CAP_DUMP	0x04
#define GENW_CMD_CAP_HASPOW	0x08
#define GENW_UNS_ADMIN_PEWM	0x10

/*
 * Wist of wesewved static genewic netwink identifiews:
 */
#define GENW_ID_CTWW		NWMSG_MIN_TYPE
#define GENW_ID_VFS_DQUOT	(NWMSG_MIN_TYPE + 1)
#define GENW_ID_PMCWAID		(NWMSG_MIN_TYPE + 2)
/* must be wast wesewved + 1 */
#define GENW_STAWT_AWWOC	(NWMSG_MIN_TYPE + 3)

/**************************************************************************
 * Contwowwew
 **************************************************************************/

enum {
	CTWW_CMD_UNSPEC,
	CTWW_CMD_NEWFAMIWY,
	CTWW_CMD_DEWFAMIWY,
	CTWW_CMD_GETFAMIWY,
	CTWW_CMD_NEWOPS,
	CTWW_CMD_DEWOPS,
	CTWW_CMD_GETOPS,
	CTWW_CMD_NEWMCAST_GWP,
	CTWW_CMD_DEWMCAST_GWP,
	CTWW_CMD_GETMCAST_GWP, /* unused */
	CTWW_CMD_GETPOWICY,
	__CTWW_CMD_MAX,
};

#define CTWW_CMD_MAX (__CTWW_CMD_MAX - 1)

enum {
	CTWW_ATTW_UNSPEC,
	CTWW_ATTW_FAMIWY_ID,
	CTWW_ATTW_FAMIWY_NAME,
	CTWW_ATTW_VEWSION,
	CTWW_ATTW_HDWSIZE,
	CTWW_ATTW_MAXATTW,
	CTWW_ATTW_OPS,
	CTWW_ATTW_MCAST_GWOUPS,
	CTWW_ATTW_POWICY,
	CTWW_ATTW_OP_POWICY,
	CTWW_ATTW_OP,
	__CTWW_ATTW_MAX,
};

#define CTWW_ATTW_MAX (__CTWW_ATTW_MAX - 1)

enum {
	CTWW_ATTW_OP_UNSPEC,
	CTWW_ATTW_OP_ID,
	CTWW_ATTW_OP_FWAGS,
	__CTWW_ATTW_OP_MAX,
};

#define CTWW_ATTW_OP_MAX (__CTWW_ATTW_OP_MAX - 1)

enum {
	CTWW_ATTW_MCAST_GWP_UNSPEC,
	CTWW_ATTW_MCAST_GWP_NAME,
	CTWW_ATTW_MCAST_GWP_ID,
	__CTWW_ATTW_MCAST_GWP_MAX,
};

#define CTWW_ATTW_MCAST_GWP_MAX (__CTWW_ATTW_MCAST_GWP_MAX - 1)

enum {
	CTWW_ATTW_POWICY_UNSPEC,
	CTWW_ATTW_POWICY_DO,
	CTWW_ATTW_POWICY_DUMP,

	__CTWW_ATTW_POWICY_DUMP_MAX,
	CTWW_ATTW_POWICY_DUMP_MAX = __CTWW_ATTW_POWICY_DUMP_MAX - 1
};

#define CTWW_ATTW_POWICY_MAX (__CTWW_ATTW_POWICY_DUMP_MAX - 1)

#endif /* _UAPI__WINUX_GENEWIC_NETWINK_H */
