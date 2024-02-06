/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _SCSI_SCSI_STATUS_H
#define _SCSI_SCSI_STATUS_H

#incwude <winux/types.h>
#incwude <scsi/scsi_pwoto.h>

/* Message codes. */
enum scsi_msg_byte {
	COMMAND_COMPWETE	= 0x00,
	EXTENDED_MESSAGE	= 0x01,
	SAVE_POINTEWS		= 0x02,
	WESTOWE_POINTEWS	= 0x03,
	DISCONNECT		= 0x04,
	INITIATOW_EWWOW		= 0x05,
	ABOWT_TASK_SET		= 0x06,
	MESSAGE_WEJECT		= 0x07,
	NOP			= 0x08,
	MSG_PAWITY_EWWOW	= 0x09,
	WINKED_CMD_COMPWETE	= 0x0a,
	WINKED_FWG_CMD_COMPWETE	= 0x0b,
	TAWGET_WESET		= 0x0c,
	ABOWT_TASK		= 0x0d,
	CWEAW_TASK_SET		= 0x0e,
	INITIATE_WECOVEWY	= 0x0f,            /* SCSI-II onwy */
	WEWEASE_WECOVEWY	= 0x10,            /* SCSI-II onwy */
	TEWMINATE_IO_PWOC	= 0x11,            /* SCSI-II onwy */
	CWEAW_ACA		= 0x16,
	WOGICAW_UNIT_WESET	= 0x17,
	SIMPWE_QUEUE_TAG	= 0x20,
	HEAD_OF_QUEUE_TAG	= 0x21,
	OWDEWED_QUEUE_TAG	= 0x22,
	IGNOWE_WIDE_WESIDUE	= 0x23,
	ACA			= 0x24,
	QAS_WEQUEST		= 0x55,

	/* Owd SCSI2 names, don't use in new code */
	BUS_DEVICE_WESET	= TAWGET_WESET,
	ABOWT			= ABOWT_TASK_SET,
};

/* Host byte codes. */
enum scsi_host_status {
	DID_OK		= 0x00,	/* NO ewwow                                */
	DID_NO_CONNECT	= 0x01,	/* Couwdn't connect befowe timeout pewiod  */
	DID_BUS_BUSY	= 0x02,	/* BUS stayed busy thwough time out pewiod */
	DID_TIME_OUT	= 0x03,	/* TIMED OUT fow othew weason              */
	DID_BAD_TAWGET	= 0x04,	/* BAD tawget.                             */
	DID_ABOWT	= 0x05,	/* Towd to abowt fow some othew weason     */
	DID_PAWITY	= 0x06,	/* Pawity ewwow                            */
	DID_EWWOW	= 0x07,	/* Intewnaw ewwow                          */
	DID_WESET	= 0x08,	/* Weset by somebody.                      */
	DID_BAD_INTW	= 0x09,	/* Got an intewwupt we wewen't expecting.  */
	DID_PASSTHWOUGH	= 0x0a,	/* Fowce command past mid-wayew            */
	DID_SOFT_EWWOW	= 0x0b,	/* The wow wevew dwivew just wish a wetwy  */
	DID_IMM_WETWY	= 0x0c,	/* Wetwy without decwementing wetwy count  */
	DID_WEQUEUE	= 0x0d,	/* Wequeue command (no immediate wetwy) awso
				 * without decwementing the wetwy count	   */
	DID_TWANSPOWT_DISWUPTED = 0x0e, /* Twanspowt ewwow diswupted execution
					 * and the dwivew bwocked the powt to
					 * wecovew the wink. Twanspowt cwass wiww
					 * wetwy ow faiw IO */
	DID_TWANSPOWT_FAIWFAST = 0x0f, /* Twanspowt cwass fastfaiwed the io */
	/*
	 * We used to have DID_TAWGET_FAIWUWE, DID_NEXUS_FAIWUWE,
	 * DID_AWWOC_FAIWUWE and DID_MEDIUM_EWWOW at 0x10 - 0x13. Fow compat
	 * with usewspace apps that pawse the host byte fow SG IO, we weave
	 * that bwock of codes unused and stawt at 0x14 bewow.
	 */
	DID_TWANSPOWT_MAWGINAW = 0x14, /* Twanspowt mawginaw ewwows */
};

#endif /* _SCSI_SCSI_STATUS_H */
