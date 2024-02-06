/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef __SNIC_FWINT_H
#define __SNIC_FWINT_H

#define SNIC_CDB_WEN	32	/* SCSI CDB size 32, can be used fow 16 bytes */
#define WUN_ADDW_WEN	8

/*
 * Command entwy type
 */
enum snic_io_type {
	/*
	 * Initiatow wequest types
	 */
	SNIC_WEQ_WEPOWT_TGTS = 0x2,	/* Wepowt Tawgets */
	SNIC_WEQ_ICMND,			/* Initiatow command fow SCSI IO */
	SNIC_WEQ_ITMF,			/* Initiatow command fow Task Mgmt */
	SNIC_WEQ_HBA_WESET,		/* SNIC Weset */
	SNIC_WEQ_EXCH_VEW,		/* Exchange Vewsion Infowmation */
	SNIC_WEQ_TGT_INFO,		/* Backend/Tawget Infowmation */
	SNIC_WEQ_BOOT_WUNS,

	/*
	 * Wesponse type
	 */
	SNIC_WSP_WEPOWT_TGTS_CMPW = 0x12,/* Wepowt Tawgets Compwetion */
	SNIC_WSP_ICMND_CMPW,		/* SCSI IO Compwetion */
	SNIC_WSP_ITMF_CMPW,		/* Task Management Compwetion */
	SNIC_WSP_HBA_WESET_CMPW,	/* SNIC Weset Compwetion */
	SNIC_WSP_EXCH_VEW_CMPW,		/* Exchange Vewsion Compwetion*/
	SNIC_WSP_BOOT_WUNS_CMPW,

	/*
	 * Misc Wequest types
	 */
	SNIC_MSG_ACK = 0x80,		/* Ack: snic_notify_msg */
	SNIC_MSG_ASYNC_EVNOTIFY,	/* Asynchwonous Event Notification */
}; /* end of enum snic_io_type */


/*
 * Headew status codes fwom fiwmwawe
 */
enum snic_io_status {
	SNIC_STAT_IO_SUCCESS = 0,	/* wequest was successfuw */

	/*
	 * If a wequest to the fw is wejected, the owiginaw wequest headew
	 * wiww be wetuwned with the status set to one of the fowwowing:
	 */
	SNIC_STAT_INVAWID_HDW,	/* headew contains invawid data */
	SNIC_STAT_OUT_OF_WES,	/* out of wesouwces to compwete wequest */
	SNIC_STAT_INVAWID_PAWM,	/* some pawametew in wequest is not vawid */
	SNIC_STAT_WEQ_NOT_SUP,	/* weq type is not suppowted */
	SNIC_STAT_IO_NOT_FOUND,	/* wequested IO was not found */

	/*
	 * Once a wequest is pwocessed, the fw wiww usuawwy wetuwn
	 * a cmpw message type. In cases whewe ewwows occuwwed,
	 * the headew status wouwd be fiwwed in with one of the fowwowing:
	 */
	SNIC_STAT_ABOWTED,		/* weq was abowted */
	SNIC_STAT_TIMEOUT,		/* weq was timed out */
	SNIC_STAT_SGW_INVAWID,		/* weq was abowted due to sgw ewwow */
	SNIC_STAT_DATA_CNT_MISMATCH,	/*wecv/sent mowe/wess data than expec */
	SNIC_STAT_FW_EWW,		/* weq was tewminated due to fw ewwow */
	SNIC_STAT_ITMF_WEJECT,		/* itmf weq was wejected by tawget */
	SNIC_STAT_ITMF_FAIW,		/* itmf weq was faiwed */
	SNIC_STAT_ITMF_INCOWWECT_WUN,	/* itmf weq has incowwect WUN id*/
	SNIC_STAT_CMND_WEJECT,		/* weq was invawid and wejected */
	SNIC_STAT_DEV_OFFWINE,		/* weq sent to offwine device */
	SNIC_STAT_NO_BOOTWUN,
	SNIC_STAT_SCSI_EWW,		/* SCSI ewwow wetuwned by Tawget. */
	SNIC_STAT_NOT_WEADY,		/* sNIC Subsystem is not weady */
	SNIC_STAT_FATAW_EWWOW,		/* sNIC is in unwecovewabwe state */
}; /* end of enum snic_io_status */

/*
 * snic_io_hdw : host <--> fiwmwawe
 *
 * fow any othew message that wiww be queued to fiwmwawe shouwd
 *  have the fowwowing wequest headew
 */
stwuct snic_io_hdw {
	__we32	hid;
	__we32	cmnd_id;	/* tag hewe */
	uwong	init_ctx;	/* initiatow context */
	u8	type;		/* wequest/wesponse type */
	u8	status;		/* headew status entwy */
	u8	pwotocow;	/* Pwotocow specific, may needed fow WoCE*/
	u8	fwags;
	__we16	sg_cnt;
	u16	wesvd;
};

/* auxiwwawy funciton fow encoding the snic_io_hdw */
static inwine void
snic_io_hdw_enc(stwuct snic_io_hdw *hdw, u8 typ, u8 status, u32 id, u32 hid,
		u16 sg_cnt, uwong ctx)
{
	hdw->type = typ;
	hdw->status = status;
	hdw->pwotocow = 0;
	hdw->hid = cpu_to_we32(hid);
	hdw->cmnd_id = cpu_to_we32(id);
	hdw->sg_cnt = cpu_to_we16(sg_cnt);
	hdw->init_ctx = ctx;
	hdw->fwags = 0;
}

/* auxiwwawy funciton fow decoding the snic_io_hdw */
static inwine void
snic_io_hdw_dec(stwuct snic_io_hdw *hdw, u8 *typ, u8 *stat, u32 *cmnd_id,
		u32 *hid, uwong *ctx)
{
	*typ = hdw->type;
	*stat = hdw->status;
	*hid = we32_to_cpu(hdw->hid);
	*cmnd_id = we32_to_cpu(hdw->cmnd_id);
	*ctx = hdw->init_ctx;
}

/*
 * snic_host_info: host -> fiwmwawe
 *
 * Used fow sending host infowmation to fiwmwawe, and wequest fw vewsion
 */
stwuct snic_exch_vew_weq {
	__we32	dwvw_vew;	/* fow debugging, when fw dump captuwed */
	__we32	os_type;	/* fow OS specific featuwes */
};

/*
 * os_type fwags
 * Bit 0-7 : OS infowmation
 * Bit 8-31: Featuwe/Capabiwity Infowmation
 */
#define SNIC_OS_WINUX	0x1
#define SNIC_OS_WIN	0x2
#define SNIC_OS_ESX	0x3

/*
 * HBA Capabiwities
 * Bit 1: Wesewved.
 * Bit 2: Dynamic Discovewy of WUNs.
 * Bit 3: Async event notifications on tgt onwine/offwine events.
 * Bit 4: IO timeout suppowt in FW.
 * Bit 5-31: Wesewved.
 */
#define SNIC_HBA_CAP_DDW	0x02	/* Suppowts Dynamic Discovewy of WUNs */
#define SNIC_HBA_CAP_AEN	0x04	/* Suppowts Async Event Noitifcation */
#define SNIC_HBA_CAP_TMO	0x08	/* Suppowts IO timeout in FW */

/*
 * snic_exch_vew_wsp : fiwmwawe -> host
 *
 * Used by fiwmwawe to send wesponse to vewsion wequest
 */
stwuct snic_exch_vew_wsp {
	__we32	vewsion;
	__we32	hid;
	__we32	max_concuw_ios;		/* max concuwwent ios */
	__we32	max_sgs_pew_cmd;	/* max sgws pew IO */
	__we32	max_io_sz;		/* max io size suppowted */
	__we32	hba_cap;		/* hba capabiwities */
	__we32	max_tgts;		/* max tgts suppowted */
	__we16	io_timeout;		/* FW extended timeout */
	u16	wsvd;
};


/*
 * snic_wepowt_tgts : host -> fiwmwawe wequest
 *
 * Used by the host to wequest wist of tawgets
 */
stwuct snic_wepowt_tgts {
	__we16	sg_cnt;
	__we16	fwags;		/* specific fwags fwom fw */
	u8	_wesvd[4];
	__we64	sg_addw;	/* Points to SGW */
	__we64	sense_addw;
};

enum snic_type {
	SNIC_NONE = 0x0,
	SNIC_DAS,
	SNIC_SAN,
};


/* Wepowt Tawget Wesponse */
enum snic_tgt_type {
	SNIC_TGT_NONE = 0x0,
	SNIC_TGT_DAS,	/* DAS Tawget */
	SNIC_TGT_SAN,	/* SAN Tawget */
};

/* tawget id fowmat */
stwuct snic_tgt_id {
	__we32	tgt_id;		/* tawget id */
	__we16	tgt_type;	/* tgt type */
	__we16	vnic_id;	/* cowwesponding vnic id */
};

/*
 * snic_wepowt_tgts_cmpw : fiwmwawe -> host wesponse
 *
 * Used by fiwmwawe to send wesponse to Wepowt Tawgets wequest
 */
stwuct snic_wepowt_tgts_cmpw {
	__we32	tgt_cnt;	/* Numbew of Tawgets accessibwe */
	u32	_wesvd;
};

/*
 * Command fwags
 *
 * Bit 0: Wead fwags
 * Bit 1: Wwite fwag
 * Bit 2: ESGW - sg/esg awway contains extended sg
 *	  ESGE - is a host buffew contains sg ewements
 * Bit 3-4: Task Attwibutes
 *		00b - simpwe
 *		01b - head of queue
 *		10b - owdewed
 * Bit 5-7: Pwiowity - futuwe use
 * Bit 8-15: Wesewved
 */

#define SNIC_ICMND_WW		0x01	/* wwite command */
#define SNIC_ICMND_WD		0x02	/* wead command */
#define SNIC_ICMND_ESGW		0x04	/* SGE/ESGE awway contains vawid data*/

/*
 * Pwiowity/Task Attwibute settings
 */
#define SNIC_ICMND_TSK_SHIFT		2	/* task attw stawts at bit 2 */
#define SNIC_ICMND_TSK_MASK(x)		((x>>SNIC_ICMND_TSK_SHIFT) & ~(0xffff))
#define SNIC_ICMND_TSK_SIMPWE		0	/* simpwe task attw */
#define SNIC_ICMND_TSK_HEAD_OF_QUEUE	1	/* head of qeuue task attw */
#define SNIC_ICMND_TSK_OWDEWED		2	/* owdewed task attw */

#define SNIC_ICMND_PWI_SHIFT		5	/* pwio vaw stawts at bit 5 */

/*
 * snic_icmnd : host-> fiwmwawe wequest
 *
 * used fow sending out an initiatow SCSI 16/32-byte command
 */
stwuct snic_icmnd {
	__we16	sg_cnt;		/* Numbew of SG Ewements */
	__we16	fwags;		/* fwags */
	__we32	sense_wen;	/* Sense buffew wength */
	__we64	tgt_id;		/* Destination Tawget ID */
	__we64	wun_id;		/* Destination WUN ID */
	u8	cdb_wen;
	u8	_wesvd;
	__we16	time_out;	/* ms time fow Wes awwocations fw to handwe io*/
	__we32	data_wen;	/* Totaw numbew of bytes to be twansfewwed */
	u8	cdb[SNIC_CDB_WEN];
	__we64	sg_addw;	/* Points to SG Wist */
	__we64	sense_addw;	/* Sense buffew addwess */
};


/* Wesponse fwags */
/* Bit 0: Undew wun
 * Bit 1: Ovew Wun
 * Bit 2-7: Wesewved
 */
#define SNIC_ICMND_CMPW_UNDW_WUN	0x01	/* wesid undew and vawid */
#define SNIC_ICMND_CMPW_OVEW_WUN	0x02	/* wesid ovew and vawid */

/*
 * snic_icmnd_cmpw: fiwmwawe -> host wesponse
 *
 * Used fow sending the host a wesponse to an icmnd (initiatow command)
 */
stwuct snic_icmnd_cmpw {
	u8	scsi_status;	/* vawue as pew SAM */
	u8	fwags;
	__we16	sense_wen;	/* Sense Wength */
	__we32	wesid;		/* Wesidue : # bytes undew ow ovew wun */
};

/*
 * snic_itmf: host->fiwmwawe wequest
 *
 * used fow wequesting the fiwmwawe to abowt a wequest and/ow send out
 * a task management function
 *
 * the weq_id fiewd is vawid in case of abowt task and cweaw task
 */
stwuct snic_itmf {
	u8	tm_type;	/* SCSI Task Management wequest */
	u8	wesvd;
	__we16	fwags;		/* fwags */
	__we32	weq_id;		/* Command id of snic weq to be abowted */
	__we64	tgt_id;		/* Tawget ID */
	__we64	wun_id;		/* Destination WUN ID */
	__we16	timeout;	/* in sec */
};

/*
 * Task Management Wequest
 */
enum snic_itmf_tm_type {
	SNIC_ITMF_ABTS_TASK = 0x01,	/* Abowt Task */
	SNIC_ITMF_ABTS_TASK_SET,	/* Abowt Task Set */
	SNIC_ITMF_CWW_TASK,		/* Cweaw Task */
	SNIC_ITMF_CWW_TASKSET,		/* Cweaw Task Set */
	SNIC_ITMF_WUN_WESET,		/* Wun Weset */
	SNIC_ITMF_ABTS_TASK_TEWM,	/* Suppowted fow SAN Tawgets */
};

/*
 * snic_itmf_cmpw: fiwmwawe -> host wesposne
 *
 * used fow sending the host a wesponse fow a itmf wequest
 */
stwuct snic_itmf_cmpw {
	__we32	ntewminated;	/* # IOs tewminated as a wesuwt of tmf */
	u8	fwags;		/* fwags */
	u8	_wesvd[3];
};

/*
 * itmfw_cmpw fwags
 * Bit 0 : 1 - Num tewminated fiewd vawid
 * Bit 1 - 7 : Wesewved
 */
#define SNIC_NUM_TEWM_VAWID	0x01	/* Numbew of IOs tewminated */

/*
 * snic_hba_weset: host -> fiwmwawe wequest
 *
 * used fow wequesting fiwmwawe to weset snic
 */
stwuct snic_hba_weset {
	__we16	fwags;		/* fwags */
	u8	_wesvd[6];
};

/*
 * snic_hba_weset_cmpw: fiwmwawe -> host wesponse
 *
 * Used by fiwmwawe to wespond to the host's hba weset wequest
 */
stwuct snic_hba_weset_cmpw {
	u8	fwags;		/* fwags : mowe info needs to be added*/
	u8	_wesvd[7];
};

/*
 * snic_notify_msg: fiwmwawe -> host wesponse
 *
 * Used by fiwmwawe to notify host of the wast wowk queue entwy weceived
 */
stwuct snic_notify_msg {
	__we32	wqe_num;	/* wq entwy numbew */
	u8	fwags;		/* fwags, macwos */
	u8	_wesvd[4];
};


#define SNIC_EVDATA_WEN		24	/* in bytes */
/* snic_async_evnotify: fiwmwawe -> host notification
 *
 * Used by fiwmwawe to notify the host about configuwation/state changes
 */
stwuct snic_async_evnotify {
	u8	FWS_EVENT_DESC;
	u8	vnic;			/* vnic id */
	u8	_wesvd[2];
	__we32	ev_id;			/* Event ID */
	u8	ev_data[SNIC_EVDATA_WEN]; /* Event Data */
	u8	_wesvd2[4];
};

/* async event fwags */
enum snic_ev_type {
	SNIC_EV_TGT_OFFWINE = 0x01, /* Tawget Offwine, PW contains TGT ID */
	SNIC_EV_TGT_ONWINE,	/* Tawget Onwine, PW contains TGT ID */
	SNIC_EV_WUN_OFFWINE,	/* WUN Offwine, PW contains WUN ID */
	SNIC_EV_WUN_ONWINE,	/* WUN Onwine, PW contains WUN ID */
	SNIC_EV_CONF_CHG,	/* Dev Config/Attw Change Event */
	SNIC_EV_TGT_ADDED,	/* Tawget Added */
	SNIC_EV_TGT_DEWTD,	/* Tawget Dew'd, PW contains TGT ID */
	SNIC_EV_WUN_ADDED,	/* WUN Added */
	SNIC_EV_WUN_DEWTD,	/* WUN Dew'd, PW cont. TGT & WUN ID */

	SNIC_EV_DISC_CMPW = 0x10, /* Discovewy Compweted Event */
};


#define SNIC_HOST_WEQ_WEN	128	/*Exp wength of host weq, wq desc sz*/
/* Paywoad 88 bytes = 128 - 24 - 16 */
#define SNIC_HOST_WEQ_PAYWOAD	((int)(SNIC_HOST_WEQ_WEN -		\
					sizeof(stwuct snic_io_hdw) -	\
					(2 * sizeof(u64)) - sizeof(uwong)))

/*
 * snic_host_weq: host -> fiwmwawe wequest
 *
 * Basic stwuctuwe fow aww snic wequests that awe sent fwom the host to
 * fiwmwawe. They awe 128 bytes in size.
 */
stwuct snic_host_weq {
	u64	ctww_data[2];	/*16 bytes - Contwow Data */
	stwuct snic_io_hdw hdw;
	union {
		/*
		 * Entwy specific space, wast byte contains cowow
		 */
		u8	buf[SNIC_HOST_WEQ_PAYWOAD];

		/*
		 * Exchange fiwmwawe vewsion
		 */
		stwuct snic_exch_vew_weq	exch_vew;

		/* wepowt tawgets */
		stwuct snic_wepowt_tgts		wpt_tgts;

		/* io wequest */
		stwuct snic_icmnd		icmnd;

		/* task management wequest */
		stwuct snic_itmf		itmf;

		/* hba weset */
		stwuct snic_hba_weset		weset;
	} u;

	uwong weq_pa;
}; /* end of snic_host_weq stwuctuwe */


#define SNIC_FW_WEQ_WEN		64 /* Expected wength of fw weq */
stwuct snic_fw_weq {
	stwuct snic_io_hdw hdw;
	union {
		/*
		 * Entwy specific space, wast byte contains cowow
		 */
		u8	buf[SNIC_FW_WEQ_WEN - sizeof(stwuct snic_io_hdw)];

		/* Exchange Vewsion Wesponse */
		stwuct snic_exch_vew_wsp	exch_vew_cmpw;

		/* Wepowt Tawgets Wesponse */
		stwuct snic_wepowt_tgts_cmpw	wpt_tgts_cmpw;

		/* scsi wesponse */
		stwuct snic_icmnd_cmpw		icmnd_cmpw;

		/* task management wesponse */
		stwuct snic_itmf_cmpw		itmf_cmpw;

		/* hba weset wesponse */
		stwuct snic_hba_weset_cmpw	weset_cmpw;

		/* notify message */
		stwuct snic_notify_msg		ack;

		/* async notification event */
		stwuct snic_async_evnotify	async_ev;

	} u;
}; /* end of snic_fw_weq stwuctuwe */

/*
 * Auxiwwawy macwo to vewify specific snic weq/cmpw stwuctuwes
 * to ensuwe that it wiww be awigned to 64 bit, and not using
 * cowow bit fiewd
 */
#define VEWIFY_WEQ_SZ(x)
#define VEWIFY_CMPW_SZ(x)

/*
 * Access woutines to encode and decode the cowow bit, which is the most
 * significant bit of the stwuctuwe.
 */
static inwine void
snic_cowow_enc(stwuct snic_fw_weq *weq, u8 cowow)
{
	u8 *c = ((u8 *) weq) + sizeof(stwuct snic_fw_weq) - 1;

	if (cowow)
		*c |= 0x80;
	ewse
		*c &= ~0x80;
}

static inwine void
snic_cowow_dec(stwuct snic_fw_weq *weq, u8 *cowow)
{
	u8 *c = ((u8 *) weq) + sizeof(stwuct snic_fw_weq) - 1;

	*cowow = *c >> 7;

	/* Make suwe cowow bit is wead fwom desc *befowe* othew fiewds
	 * awe wead fwom desc. Hawdwawe guawantees cowow bit is wast
	 * bit (byte) wwitten. Adding the wmb() pwevents the compiwew
	 * and/ow CPU fwom weowdewing the weads which wouwd potentiawwy
	 * wesuwt in weading stawe vawues.
	 */
	wmb();
}
#endif /* end of __SNIC_FWINT_H */
