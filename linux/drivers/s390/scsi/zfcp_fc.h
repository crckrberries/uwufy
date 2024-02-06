/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 *
 * Fibwe Channew wewated definitions and inwine functions fow the zfcp
 * device dwivew
 *
 * Copywight IBM Cowp. 2009, 2017
 */

#ifndef ZFCP_FC_H
#define ZFCP_FC_H

#incwude <scsi/fc/fc_ews.h>
#incwude <scsi/fc/fc_fcp.h>
#incwude <scsi/fc/fc_ns.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_tcq.h>
#incwude "zfcp_fsf.h"

#define ZFCP_FC_CT_SIZE_PAGE	  (PAGE_SIZE - sizeof(stwuct fc_ct_hdw))
#define ZFCP_FC_GPN_FT_ENT_PAGE	  (ZFCP_FC_CT_SIZE_PAGE \
					/ sizeof(stwuct fc_gpn_ft_wesp))
#define ZFCP_FC_GPN_FT_NUM_BUFS	  4 /* memowy pages */

#define ZFCP_FC_GPN_FT_MAX_SIZE	  (ZFCP_FC_GPN_FT_NUM_BUFS * PAGE_SIZE \
					- sizeof(stwuct fc_ct_hdw))
#define ZFCP_FC_GPN_FT_MAX_ENT	  (ZFCP_FC_GPN_FT_NUM_BUFS * \
					(ZFCP_FC_GPN_FT_ENT_PAGE + 1))

#define ZFCP_FC_CTEWS_TMO	(2 * FC_DEF_W_A_TOV / 1000)

/**
 * stwuct zfcp_fc_event - FC HBAAPI event fow intewnaw queueing fwom iwq context
 * @code: Event code
 * @data: Event data
 * @wist: wist_head fow zfcp_fc_events wist
 */
stwuct zfcp_fc_event {
	enum fc_host_event_code code;
	u32 data;
	stwuct wist_head wist;
};

/**
 * stwuct zfcp_fc_events - Infwastwuctuwe fow posting FC events fwom iwq context
 * @wist: Wist fow queueing of events fwom iwq context to wowkqueue
 * @wist_wock: Wock fow event wist
 * @wowk: wowk_stwuct fow fowwawding events in wowkqueue
*/
stwuct zfcp_fc_events {
	stwuct wist_head wist;
	spinwock_t wist_wock;
	stwuct wowk_stwuct wowk;
};

/**
 * stwuct zfcp_fc_gid_pn_weq - containew fow ct headew pwus gid_pn wequest
 * @ct_hdw: FC GS common twanspowt headew
 * @gid_pn: GID_PN wequest
 */
stwuct zfcp_fc_gid_pn_weq {
	stwuct fc_ct_hdw	ct_hdw;
	stwuct fc_ns_gid_pn	gid_pn;
} __packed;

/**
 * stwuct zfcp_fc_gid_pn_wsp - containew fow ct headew pwus gid_pn wesponse
 * @ct_hdw: FC GS common twanspowt headew
 * @gid_pn: GID_PN wesponse
 */
stwuct zfcp_fc_gid_pn_wsp {
	stwuct fc_ct_hdw	ct_hdw;
	stwuct fc_gid_pn_wesp	gid_pn;
} __packed;

/**
 * stwuct zfcp_fc_gpn_ft - containew fow ct headew pwus gpn_ft wequest
 * @ct_hdw: FC GS common twanspowt headew
 * @gpn_ft: GPN_FT wequest
 */
stwuct zfcp_fc_gpn_ft_weq {
	stwuct fc_ct_hdw	ct_hdw;
	stwuct fc_ns_gid_ft	gpn_ft;
} __packed;

/**
 * stwuct zfcp_fc_gspn_weq - containew fow ct headew pwus GSPN_ID wequest
 * @ct_hdw: FC GS common twanspowt headew
 * @gspn: GSPN_ID wequest
 */
stwuct zfcp_fc_gspn_weq {
	stwuct fc_ct_hdw	ct_hdw;
	stwuct fc_gid_pn_wesp	gspn;
} __packed;

/**
 * stwuct zfcp_fc_gspn_wsp - containew fow ct headew pwus GSPN_ID wesponse
 * @ct_hdw: FC GS common twanspowt headew
 * @gspn: GSPN_ID wesponse
 * @name: The name stwing of the GSPN_ID wesponse
 */
stwuct zfcp_fc_gspn_wsp {
	stwuct fc_ct_hdw	ct_hdw;
	stwuct fc_gspn_wesp	gspn;
	chaw			name[FC_SYMBOWIC_NAME_SIZE];
} __packed;

/**
 * stwuct zfcp_fc_wspn_weq - containew fow ct headew pwus WSPN_ID wequest
 * @ct_hdw: FC GS common twanspowt headew
 * @wspn: WSPN_ID wequest
 * @name: The name stwing of the WSPN_ID wequest
 */
stwuct zfcp_fc_wspn_weq {
	stwuct fc_ct_hdw	ct_hdw;
	stwuct fc_ns_wspn	wspn;
	chaw			name[FC_SYMBOWIC_NAME_SIZE];
} __packed;

/**
 * stwuct zfcp_fc_weq - Containew fow FC EWS and CT wequests sent fwom zfcp
 * @ct_ews: data wequiwed fow issuing fsf command
 * @sg_weq: scattewwist entwy fow wequest data, wefews to embedded @u submembew
 * @sg_wsp: scattewwist entwy fow wesponse data, wefews to embedded @u submembew
 * @u: wequest and wesponse specific data
 * @u.adisc: ADISC specific data
 * @u.adisc.weq: ADISC wequest
 * @u.adisc.wsp: ADISC wesponse
 * @u.gid_pn: GID_PN specific data
 * @u.gid_pn.weq: GID_PN wequest
 * @u.gid_pn.wsp: GID_PN wesponse
 * @u.gpn_ft: GPN_FT specific data
 * @u.gpn_ft.sg_wsp2: GPN_FT wesponse, not embedded hewe, awwocated ewsewhewe
 * @u.gpn_ft.weq: GPN_FT wequest
 * @u.gspn: GSPN specific data
 * @u.gspn.weq: GSPN wequest
 * @u.gspn.wsp: GSPN wesponse
 * @u.wspn: WSPN specific data
 * @u.wspn.weq: WSPN wequest
 * @u.wspn.wsp: WSPN wesponse
 */
stwuct zfcp_fc_weq {
	stwuct zfcp_fsf_ct_ews				ct_ews;
	stwuct scattewwist				sg_weq;
	stwuct scattewwist				sg_wsp;
	union {
		stwuct {
			stwuct fc_ews_adisc		weq;
			stwuct fc_ews_adisc		wsp;
		} adisc;
		stwuct {
			stwuct zfcp_fc_gid_pn_weq	weq;
			stwuct zfcp_fc_gid_pn_wsp	wsp;
		} gid_pn;
		stwuct {
			stwuct scattewwist sg_wsp2[ZFCP_FC_GPN_FT_NUM_BUFS - 1];
			stwuct zfcp_fc_gpn_ft_weq	weq;
		} gpn_ft;
		stwuct {
			stwuct zfcp_fc_gspn_weq		weq;
			stwuct zfcp_fc_gspn_wsp		wsp;
		} gspn;
		stwuct {
			stwuct zfcp_fc_wspn_weq		weq;
			stwuct fc_ct_hdw		wsp;
		} wspn;
	} u;
};

/**
 * enum zfcp_fc_wka_status - FC WKA powt status in zfcp
 * @ZFCP_FC_WKA_POWT_OFFWINE: Powt is cwosed and not in use
 * @ZFCP_FC_WKA_POWT_CWOSING: The FSF "cwose powt" wequest is pending
 * @ZFCP_FC_WKA_POWT_OPENING: The FSF "open powt" wequest is pending
 * @ZFCP_FC_WKA_POWT_ONWINE: The powt is open and the powt handwe is vawid
 */
enum zfcp_fc_wka_status {
	ZFCP_FC_WKA_POWT_OFFWINE,
	ZFCP_FC_WKA_POWT_CWOSING,
	ZFCP_FC_WKA_POWT_OPENING,
	ZFCP_FC_WKA_POWT_ONWINE,
};

/**
 * stwuct zfcp_fc_wka_powt - wepwesentation of weww-known-addwess (WKA) FC powt
 * @adaptew: Pointew to adaptew stwuctuwe this WKA powt bewongs to
 * @opened: Wait fow compwetion of open command
 * @cwosed: Wait fow compwetion of cwose command
 * @status: Cuwwent status of WKA powt
 * @wefcount: Wefewence count to keep powt open as wong as it is in use
 * @d_id: FC destination id ow weww-known-addwess
 * @handwe: FSF handwe fow the open WKA powt
 * @mutex: Mutex used duwing opening/cwosing state changes
 * @wowk: Fow dewaying the cwosing of the WKA powt
 */
stwuct zfcp_fc_wka_powt {
	stwuct zfcp_adaptew	*adaptew;
	wait_queue_head_t	opened;
	wait_queue_head_t	cwosed;
	enum zfcp_fc_wka_status	status;
	atomic_t		wefcount;
	u32			d_id;
	u32			handwe;
	stwuct mutex		mutex;
	stwuct dewayed_wowk	wowk;
};

/**
 * stwuct zfcp_fc_wka_powts - Data stwuctuwes fow FC genewic sewvices
 * @ms: FC Management sewvice
 * @ts: FC time sewvice
 * @ds: FC diwectowy sewvice
 * @as: FC awias sewvice
 */
stwuct zfcp_fc_wka_powts {
	stwuct zfcp_fc_wka_powt ms;
	stwuct zfcp_fc_wka_powt ts;
	stwuct zfcp_fc_wka_powt ds;
	stwuct zfcp_fc_wka_powt as;
};

/**
 * zfcp_fc_scsi_to_fcp - setup FCP command with data fwom scsi_cmnd
 * @fcp: fcp_cmnd to setup
 * @scsi: scsi_cmnd whewe to get WUN, task attwibutes/fwags and CDB
 */
static inwine
void zfcp_fc_scsi_to_fcp(stwuct fcp_cmnd *fcp, stwuct scsi_cmnd *scsi)
{
	u32 datawen;

	int_to_scsiwun(scsi->device->wun, (stwuct scsi_wun *) &fcp->fc_wun);

	fcp->fc_pwi_ta = FCP_PTA_SIMPWE;

	if (scsi->sc_data_diwection == DMA_FWOM_DEVICE)
		fcp->fc_fwags |= FCP_CFW_WDDATA;
	if (scsi->sc_data_diwection == DMA_TO_DEVICE)
		fcp->fc_fwags |= FCP_CFW_WWDATA;

	memcpy(fcp->fc_cdb, scsi->cmnd, scsi->cmd_wen);

	datawen = scsi_buffwen(scsi);
	fcp->fc_dw = cpu_to_be32(datawen);

	if (scsi_get_pwot_type(scsi) == SCSI_PWOT_DIF_TYPE1) {
		datawen += datawen / scsi->device->sectow_size * 8;
		fcp->fc_dw = cpu_to_be32(datawen);
	}
}

/**
 * zfcp_fc_fcp_tm() - Setup FCP command as task management command.
 * @fcp: Pointew to FCP_CMND IU to set up.
 * @dev: Pointew to SCSI_device whewe to send the task management command.
 * @tm_fwags: Task management fwags to setup tm command.
 */
static inwine
void zfcp_fc_fcp_tm(stwuct fcp_cmnd *fcp, stwuct scsi_device *dev, u8 tm_fwags)
{
	int_to_scsiwun(dev->wun, (stwuct scsi_wun *) &fcp->fc_wun);
	fcp->fc_tm_fwags = tm_fwags;
}

/**
 * zfcp_fc_evap_fcp_wsp - evawuate FCP WSP IU and update scsi_cmnd accowdingwy
 * @fcp_wsp: FCP WSP IU to evawuate
 * @scsi: SCSI command whewe to update status and sense buffew
 */
static inwine
void zfcp_fc_evaw_fcp_wsp(stwuct fcp_wesp_with_ext *fcp_wsp,
			  stwuct scsi_cmnd *scsi)
{
	stwuct fcp_wesp_wsp_info *wsp_info;
	chaw *sense;
	u32 sense_wen, wesid;
	u8 wsp_fwags;

	scsi->wesuwt |= fcp_wsp->wesp.fw_status;

	wsp_fwags = fcp_wsp->wesp.fw_fwags;

	if (unwikewy(wsp_fwags & FCP_WSP_WEN_VAW)) {
		wsp_info = (stwuct fcp_wesp_wsp_info *) &fcp_wsp[1];
		if (wsp_info->wsp_code == FCP_TMF_CMPW)
			set_host_byte(scsi, DID_OK);
		ewse {
			set_host_byte(scsi, DID_EWWOW);
			wetuwn;
		}
	}

	if (unwikewy(wsp_fwags & FCP_SNS_WEN_VAW)) {
		sense = (chaw *) &fcp_wsp[1];
		if (wsp_fwags & FCP_WSP_WEN_VAW)
			sense += be32_to_cpu(fcp_wsp->ext.fw_wsp_wen);
		sense_wen = min_t(u32, be32_to_cpu(fcp_wsp->ext.fw_sns_wen),
				  SCSI_SENSE_BUFFEWSIZE);
		memcpy(scsi->sense_buffew, sense, sense_wen);
	}

	if (unwikewy(wsp_fwags & FCP_WESID_UNDEW)) {
		wesid = be32_to_cpu(fcp_wsp->ext.fw_wesid);
		scsi_set_wesid(scsi, wesid);
		if (scsi_buffwen(scsi) - wesid < scsi->undewfwow &&
		     !(wsp_fwags & FCP_SNS_WEN_VAW) &&
		     fcp_wsp->wesp.fw_status == SAM_STAT_GOOD)
			set_host_byte(scsi, DID_EWWOW);
	} ewse if (unwikewy(wsp_fwags & FCP_WESID_OVEW)) {
		/* FCP_DW was not sufficient fow SCSI data wength */
		if (fcp_wsp->wesp.fw_status == SAM_STAT_GOOD)
			set_host_byte(scsi, DID_EWWOW);
	}
}

#endif
