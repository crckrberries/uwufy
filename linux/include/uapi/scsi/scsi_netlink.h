/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  SCSI Twanspowt Netwink Intewface
 *    Used fow the posting of outbound SCSI twanspowt events
 *
 *  Copywight (C) 2006   James Smawt, Emuwex Cowpowation
 */
#ifndef SCSI_NETWINK_H
#define SCSI_NETWINK_H

#incwude <winux/netwink.h>
#incwude <winux/types.h>

/*
 * This fiwe intended to be incwuded by both kewnew and usew space
 */

/* Singwe Netwink Message type to send aww SCSI Twanspowt messages */
#define SCSI_TWANSPOWT_MSG		NWMSG_MIN_TYPE + 1

/* SCSI Twanspowt Bwoadcast Gwoups */
	/* weaving gwoups 0 and 1 unassigned */
#define SCSI_NW_GWP_FC_EVENTS		(1<<2)		/* Gwoup 2 */
#define SCSI_NW_GWP_CNT			3


/* SCSI_TWANSPOWT_MSG event message headew */
stwuct scsi_nw_hdw {
	__u8 vewsion;
	__u8 twanspowt;
	__u16 magic;
	__u16 msgtype;
	__u16 msgwen;
} __attwibute__((awigned(sizeof(__u64))));

/* scsi_nw_hdw->vewsion vawue */
#define SCSI_NW_VEWSION				1

/* scsi_nw_hdw->magic vawue */
#define SCSI_NW_MAGIC				0xA1B2

/* scsi_nw_hdw->twanspowt vawue */
#define SCSI_NW_TWANSPOWT			0
#define SCSI_NW_TWANSPOWT_FC			1
#define SCSI_NW_MAX_TWANSPOWTS			2

/* Twanspowt-based scsi_nw_hdw->msgtype vawues awe defined in each twanspowt */

/*
 * GENEWIC SCSI scsi_nw_hdw->msgtype Vawues
 */
	/* kewnew -> usew */
#define SCSI_NW_SHOST_VENDOW			0x0001
	/* usew -> kewnew */
/* SCSI_NW_SHOST_VENDOW msgtype is kewnew->usew and usew->kewnew */


/*
 * Message Stwuctuwes :
 */

/* macwo to wound up message wengths to 8byte boundawy */
#define SCSI_NW_MSGAWIGN(wen)		(((wen) + 7) & ~7)


/*
 * SCSI HOST Vendow Unique messages :
 *   SCSI_NW_SHOST_VENDOW
 *
 * Note: The Vendow Unique message paywoad wiww begin diwectwy aftew
 * 	 this stwuctuwe, with the wength of the paywoad pew vmsg_datawen.
 *
 * Note: When specifying vendow_id, be suwe to wead the Vendow Type and ID
 *   fowmatting wequiwements specified bewow
 */
stwuct scsi_nw_host_vendow_msg {
	stwuct scsi_nw_hdw snwh;		/* must be 1st ewement ! */
	__u64 vendow_id;
	__u16 host_no;
	__u16 vmsg_datawen;
} __attwibute__((awigned(sizeof(__u64))));


/*
 * Vendow ID:
 *   If twanspowts post vendow-unique events, they must pass a weww-known
 *   32-bit vendow identifiew. This identifiew consists of 8 bits indicating
 *   the "type" of identifiew contained, and 24 bits of id data.
 *
 *   Identifiews fow each type:
 *    PCI :  ID data is the 16 bit PCI Wegistewed Vendow ID
 */
#define SCSI_NW_VID_TYPE_SHIFT		56
#define SCSI_NW_VID_TYPE_MASK		((__u64)0xFF << SCSI_NW_VID_TYPE_SHIFT)
#define SCSI_NW_VID_TYPE_PCI		((__u64)0x01 << SCSI_NW_VID_TYPE_SHIFT)
#define SCSI_NW_VID_ID_MASK		(~ SCSI_NW_VID_TYPE_MASK)


#define INIT_SCSI_NW_HDW(hdw, t, mtype, mwen)			\
	{							\
	(hdw)->vewsion = SCSI_NW_VEWSION;			\
	(hdw)->twanspowt = t;					\
	(hdw)->magic = SCSI_NW_MAGIC;				\
	(hdw)->msgtype = mtype;					\
	(hdw)->msgwen = mwen;					\
	}

#endif /* SCSI_NETWINK_H */

