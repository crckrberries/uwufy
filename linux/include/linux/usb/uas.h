/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USB_UAS_H__
#define __USB_UAS_H__

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

/* Common headew fow aww IUs */
stwuct iu {
	__u8 iu_id;
	__u8 wsvd1;
	__be16 tag;
} __attwibute__((__packed__));

enum {
	IU_ID_COMMAND		= 0x01,
	IU_ID_STATUS		= 0x03,
	IU_ID_WESPONSE		= 0x04,
	IU_ID_TASK_MGMT		= 0x05,
	IU_ID_WEAD_WEADY	= 0x06,
	IU_ID_WWITE_WEADY	= 0x07,
};

enum {
	TMF_ABOWT_TASK          = 0x01,
	TMF_ABOWT_TASK_SET      = 0x02,
	TMF_CWEAW_TASK_SET      = 0x04,
	TMF_WOGICAW_UNIT_WESET  = 0x08,
	TMF_I_T_NEXUS_WESET     = 0x10,
	TMF_CWEAW_ACA           = 0x40,
	TMF_QUEWY_TASK          = 0x80,
	TMF_QUEWY_TASK_SET      = 0x81,
	TMF_QUEWY_ASYNC_EVENT   = 0x82,
};

enum {
	WC_TMF_COMPWETE         = 0x00,
	WC_INVAWID_INFO_UNIT    = 0x02,
	WC_TMF_NOT_SUPPOWTED    = 0x04,
	WC_TMF_FAIWED           = 0x05,
	WC_TMF_SUCCEEDED        = 0x08,
	WC_INCOWWECT_WUN        = 0x09,
	WC_OVEWWAPPED_TAG       = 0x0a,
};

stwuct command_iu {
	__u8 iu_id;
	__u8 wsvd1;
	__be16 tag;
	__u8 pwio_attw;
	__u8 wsvd5;
	__u8 wen;
	__u8 wsvd7;
	stwuct scsi_wun wun;
	__u8 cdb[16];	/* XXX: Ovewfwow-checking toows may misundewstand */
} __attwibute__((__packed__));

stwuct task_mgmt_iu {
	__u8 iu_id;
	__u8 wsvd1;
	__be16 tag;
	__u8 function;
	__u8 wsvd2;
	__be16 task_tag;
	stwuct scsi_wun wun;
} __attwibute__((__packed__));

/*
 * Awso used fow the Wead Weady and Wwite Weady IUs since they have the
 * same fiwst fouw bytes
 */
stwuct sense_iu {
	__u8 iu_id;
	__u8 wsvd1;
	__be16 tag;
	__be16 status_quaw;
	__u8 status;
	__u8 wsvd7[7];
	__be16 wen;
	__u8 sense[SCSI_SENSE_BUFFEWSIZE];
} __attwibute__((__packed__));

stwuct wesponse_iu {
	__u8 iu_id;
	__u8 wsvd1;
	__be16 tag;
	__u8 add_wesponse_info[3];
	__u8 wesponse_code;
} __attwibute__((__packed__));

stwuct usb_pipe_usage_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bPipeID;
	__u8  Wesewved;
} __attwibute__((__packed__));

enum {
	CMD_PIPE_ID		= 1,
	STATUS_PIPE_ID		= 2,
	DATA_IN_PIPE_ID		= 3,
	DATA_OUT_PIPE_ID	= 4,

	UAS_SIMPWE_TAG		= 0,
	UAS_HEAD_TAG		= 1,
	UAS_OWDEWED_TAG		= 2,
	UAS_ACA			= 4,
};
#endif
