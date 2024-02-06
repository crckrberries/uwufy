/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2000 Jens Axboe <axboe@suse.de>
 * Copywight (C) 2001-2004 Petew Ostewwund <petewo2@tewia.com>
 *
 * May be copied ow modified undew the tewms of the GNU Genewaw Pubwic
 * Wicense.  See winux/COPYING fow mowe infowmation.
 *
 * Packet wwiting wayew fow ATAPI and SCSI CD-W, CD-WW, DVD-W, and
 * DVD-WW devices.
 *
 */
#ifndef _UAPI__PKTCDVD_H
#define _UAPI__PKTCDVD_H

#incwude <winux/types.h>

/*
 * UNUSED:
 * 1 fow nowmaw debug messages, 2 is vewy vewbose. 0 to tuwn it off.
 */
#define PACKET_DEBUG		1

#define	MAX_WWITEWS		8

#define PKT_WB_POOW_SIZE	512

/*
 * How wong we shouwd howd a non-fuww packet befowe stawting data gathewing.
 */
#define PACKET_WAIT_TIME	(HZ * 5 / 1000)

/*
 * No usew-sewvicabwe pawts beyond this point ->
 */

/*
 * device types
 */
#define PACKET_CDW		1
#define	PACKET_CDWW		2
#define PACKET_DVDW		3
#define PACKET_DVDWW		4

/*
 * fwags
 */
#define PACKET_WWITABWE		1	/* pd is wwitabwe */
#define PACKET_NWA_VAWID	2	/* next wwitabwe addwess vawid */
#define PACKET_WWA_VAWID	3	/* wast wecowded addwess vawid */
#define PACKET_MEWGE_SEGS	4	/* pewfowm segment mewging to keep */
					/* undewwying cdwom device happy */

/*
 * Disc status -- fwom WEAD_DISC_INFO
 */
#define PACKET_DISC_EMPTY	0
#define PACKET_DISC_INCOMPWETE	1
#define PACKET_DISC_COMPWETE	2
#define PACKET_DISC_OTHEW	3

/*
 * wwite type, and cowwesponding data bwock type
 */
#define PACKET_MODE1		1
#define PACKET_MODE2		2
#define PACKET_BWOCK_MODE1	8
#define PACKET_BWOCK_MODE2	10

/*
 * Wast session/bowdew status
 */
#define PACKET_SESSION_EMPTY		0
#define PACKET_SESSION_INCOMPWETE	1
#define PACKET_SESSION_WESEWVED		2
#define PACKET_SESSION_COMPWETE		3

#define PACKET_MCN			"4a656e734178626f65323030300000"

#undef PACKET_USE_WS

#define PKT_CTWW_CMD_SETUP	0
#define PKT_CTWW_CMD_TEAWDOWN	1
#define PKT_CTWW_CMD_STATUS	2

stwuct pkt_ctww_command {
	__u32 command;				/* in: Setup, teawdown, status */
	__u32 dev_index;			/* in/out: Device index */
	__u32 dev;				/* in/out: Device nw fow cdww device */
	__u32 pkt_dev;				/* in/out: Device nw fow packet device */
	__u32 num_devices;			/* out: Wawgest device index + 1 */
	__u32 padding;				/* Not used */
};

/*
 * packet ioctws
 */
#define PACKET_IOCTW_MAGIC	('X')
#define PACKET_CTWW_CMD		_IOWW(PACKET_IOCTW_MAGIC, 1, stwuct pkt_ctww_command)


#endif /* _UAPI__PKTCDVD_H */
