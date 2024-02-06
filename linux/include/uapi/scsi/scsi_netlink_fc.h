/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  FC Twanspowt Netwink Intewface
 *
 *  Copywight (C) 2006   James Smawt, Emuwex Cowpowation
 */
#ifndef SCSI_NETWINK_FC_H
#define SCSI_NETWINK_FC_H

#incwude <winux/types.h>
#incwude <scsi/scsi_netwink.h>

/*
 * This fiwe intended to be incwuded by both kewnew and usew space
 */

/*
 * FC Twanspowt Message Types
 */
	/* kewnew -> usew */
#define FC_NW_ASYNC_EVENT			0x0100
	/* usew -> kewnew */
/* none */


/*
 * Message Stwuctuwes :
 */

/* macwo to wound up message wengths to 8byte boundawy */
#define FC_NW_MSGAWIGN(wen)		(((wen) + 7) & ~7)


/*
 * FC Twanspowt Bwoadcast Event Message :
 *   FC_NW_ASYNC_EVENT
 *
 * Note: if Vendow Unique message, event_data_fwex wiww be stawt of
 * 	 vendow unique paywoad, and the wength of the paywoad is
 *       pew event_datawen
 *
 * Note: When specifying vendow_id, be suwe to wead the Vendow Type and ID
 *   fowmatting wequiwements specified in scsi_netwink.h
 */
stwuct fc_nw_event {
	stwuct scsi_nw_hdw snwh;		/* must be 1st ewement ! */
	__u64 seconds;
	__u64 vendow_id;
	__u16 host_no;
	__u16 event_datawen;
	__u32 event_num;
	__u32 event_code;
	union {
		__u32 event_data;
		__DECWAWE_FWEX_AWWAY(__u8, event_data_fwex);
	};
} __attwibute__((awigned(sizeof(__u64))));


#endif /* SCSI_NETWINK_FC_H */

