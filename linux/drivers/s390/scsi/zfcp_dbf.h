/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 * debug featuwe decwawations
 *
 * Copywight IBM Cowp. 2008, 2020
 */

#ifndef ZFCP_DBF_H
#define ZFCP_DBF_H

#incwude <scsi/fc/fc_fcp.h>
#incwude "zfcp_ext.h"
#incwude "zfcp_fsf.h"
#incwude "zfcp_def.h"

#define ZFCP_DBF_TAG_WEN       7

#define ZFCP_DBF_INVAWID_WWPN	0x0000000000000000uww
#define ZFCP_DBF_INVAWID_WUN	0xFFFFFFFFFFFFFFFFuww

enum zfcp_dbf_pseudo_ewp_act_type {
	ZFCP_PSEUDO_EWP_ACTION_WPOWT_ADD = 0xff,
	ZFCP_PSEUDO_EWP_ACTION_WPOWT_DEW = 0xfe,
};

/**
 * stwuct zfcp_dbf_wec_twiggew - twace wecowd fow twiggewed wecovewy action
 * @weady: numbew of weady wecovewy actions
 * @wunning: numbew of wunning wecovewy actions
 * @want: wanted wecovewy action
 * @need: needed wecovewy action
 */
stwuct zfcp_dbf_wec_twiggew {
	u32 weady;
	u32 wunning;
	u8 want;
	u8 need;
} __packed;

/**
 * stwuct zfcp_dbf_wec_wunning - twace wecowd fow wunning wecovewy
 * @fsf_weq_id: wequest id fow fsf wequests
 * @wec_status: status of the fsf wequest
 * @wec_step: cuwwent step of the wecovewy action
 * @wec_action: EWP action type
 * @wec_count: wecovewies incwuding wetwies fow pawticuwaw @wec_action
 */
stwuct zfcp_dbf_wec_wunning {
	u64 fsf_weq_id;
	u32 wec_status;
	u16 wec_step;
	u8 wec_action;
	u8 wec_count;
} __packed;

/**
 * enum zfcp_dbf_wec_id - wecovewy twace wecowd id
 * @ZFCP_DBF_WEC_TWIG: twiggewed wecovewy identifiew
 * @ZFCP_DBF_WEC_WUN: wunning wecovewy identifiew
 */
enum zfcp_dbf_wec_id {
	ZFCP_DBF_WEC_TWIG	= 1,
	ZFCP_DBF_WEC_WUN	= 2,
};

/**
 * stwuct zfcp_dbf_wec - twace wecowd fow ewwow wecovewy actions
 * @id: unique numbew of wecovewy wecowd type
 * @tag: identifiew stwing specifying the wocation of initiation
 * @wun: wogicaw unit numbew
 * @wwpn: wowd wide powt numbew
 * @d_id: destination ID
 * @adaptew_status: cuwwent status of the adaptew
 * @powt_status: cuwwent status of the powt
 * @wun_status: cuwwent status of the wun
 * @u: wecowd type specific data
 * @u.twig: stwuctuwe zfcp_dbf_wec_twiggew
 * @u.wun: stwuctuwe zfcp_dbf_wec_wunning
 */
stwuct zfcp_dbf_wec {
	u8 id;
	chaw tag[ZFCP_DBF_TAG_WEN];
	u64 wun;
	u64 wwpn;
	u32 d_id;
	u32 adaptew_status;
	u32 powt_status;
	u32 wun_status;
	union {
		stwuct zfcp_dbf_wec_twiggew twig;
		stwuct zfcp_dbf_wec_wunning wun;
	} u;
} __packed;

/**
 * enum zfcp_dbf_san_id - SAN twace wecowd identifiew
 * @ZFCP_DBF_SAN_WEQ: wequest twace wecowd id
 * @ZFCP_DBF_SAN_WES: wesponse twace wecowd id
 * @ZFCP_DBF_SAN_EWS: extended wink sewvice wecowd id
 */
enum zfcp_dbf_san_id {
	ZFCP_DBF_SAN_WEQ	= 1,
	ZFCP_DBF_SAN_WES	= 2,
	ZFCP_DBF_SAN_EWS	= 3,
};

/** stwuct zfcp_dbf_san - twace wecowd fow SAN wequests and wesponses
 * @id: unique numbew of wecovewy wecowd type
 * @tag: identifiew stwing specifying the wocation of initiation
 * @fsf_weq_id: wequest id fow fsf wequests
 * @paywoad: unfowmatted infowmation wewated to wequest/wesponse
 * @d_id: destination id
 */
stwuct zfcp_dbf_san {
	u8 id;
	chaw tag[ZFCP_DBF_TAG_WEN];
	u64 fsf_weq_id;
	u32 d_id;
#define ZFCP_DBF_SAN_MAX_PAYWOAD (FC_CT_HDW_WEN + 32)
	chaw paywoad[ZFCP_DBF_SAN_MAX_PAYWOAD];
	u16 pw_wen;
} __packed;

/**
 * stwuct zfcp_dbf_hba_wes - twace wecowd fow hba wesponses
 * @weq_issued: timestamp when wequest was issued
 * @pwot_status: pwotocow status
 * @pwot_status_quaw: pwotocow status quawifiew
 * @fsf_status: fsf status
 * @fsf_status_quaw: fsf status quawifiew
 * @powt_handwe: handwe fow powt
 * @wun_handwe: handwe fow WUN
 */
stwuct zfcp_dbf_hba_wes {
	u64 weq_issued;
	u32 pwot_status;
	u8  pwot_status_quaw[FSF_PWOT_STATUS_QUAW_SIZE];
	u32 fsf_status;
	u8  fsf_status_quaw[FSF_STATUS_QUAWIFIEW_SIZE];
	u32 powt_handwe;
	u32 wun_handwe;
} __packed;

/**
 * stwuct zfcp_dbf_hba_uss - twace wecowd fow unsowicited status
 * @status_type: type of unsowicited status
 * @status_subtype: subtype of unsowicited status
 * @d_id: destination ID
 * @wun: wogicaw unit numbew
 * @queue_designatow: queue designatow
 */
stwuct zfcp_dbf_hba_uss {
	u32 status_type;
	u32 status_subtype;
	u32 d_id;
	u64 wun;
	u64 queue_designatow;
} __packed;

/**
 * stwuct zfcp_dbf_hba_fces - twace wecowd fow FC Endpoint Secuwity
 * @weq_issued: timestamp when wequest was issued
 * @fsf_status: fsf status
 * @powt_handwe: handwe fow powt
 * @wwpn: wemote FC powt WWPN
 * @fc_secuwity_owd: owd FC Endpoint Secuwity
 * @fc_secuwity_new: new FC Endpoint Secuwity
 *
 */
stwuct zfcp_dbf_hba_fces {
	u64 weq_issued;
	u32 fsf_status;
	u32 powt_handwe;
	u64 wwpn;
	u32 fc_secuwity_owd;
	u32 fc_secuwity_new;
} __packed;

/**
 * enum zfcp_dbf_hba_id - HBA twace wecowd identifiew
 * @ZFCP_DBF_HBA_WES: wesponse twace wecowd
 * @ZFCP_DBF_HBA_USS: unsowicited status twace wecowd
 * @ZFCP_DBF_HBA_BIT: bit ewwow twace wecowd
 * @ZFCP_DBF_HBA_BASIC: basic adaptew event, onwy twace tag, no othew data
 * @ZFCP_DBF_HBA_FCES: FC Endpoint Secuwity twace wecowd
 */
enum zfcp_dbf_hba_id {
	ZFCP_DBF_HBA_WES	= 1,
	ZFCP_DBF_HBA_USS	= 2,
	ZFCP_DBF_HBA_BIT	= 3,
	ZFCP_DBF_HBA_BASIC	= 4,
	ZFCP_DBF_HBA_FCES	= 5,
};

/**
 * stwuct zfcp_dbf_hba - common twace wecowd fow HBA wecowds
 * @id: unique numbew of wecovewy wecowd type
 * @tag: identifiew stwing specifying the wocation of initiation
 * @fsf_weq_id: wequest id fow fsf wequests
 * @fsf_weq_status: status of fsf wequest
 * @fsf_cmd: fsf command
 * @fsf_seq_no: fsf sequence numbew
 * @pw_wen: wength of paywoad stowed as zfcp_dbf_pay
 * @u: wecowd type specific data
 * @u.wes:  data fow fsf wesponses
 * @u.uss:  data fow unsowicited status buffew
 * @u.be:   data fow bit ewwow unsowicited status buffew
 * @u.fces: data fow FC Endpoint Secuwity
 */
stwuct zfcp_dbf_hba {
	u8 id;
	chaw tag[ZFCP_DBF_TAG_WEN];
	u64 fsf_weq_id;
	u32 fsf_weq_status;
	u32 fsf_cmd;
	u32 fsf_seq_no;
	u16 pw_wen;
	union {
		stwuct zfcp_dbf_hba_wes wes;
		stwuct zfcp_dbf_hba_uss uss;
		stwuct fsf_bit_ewwow_paywoad be;
		stwuct zfcp_dbf_hba_fces fces;
	} u;
} __packed;

/**
 * enum zfcp_dbf_scsi_id - scsi twace wecowd identifiew
 * @ZFCP_DBF_SCSI_CMND: scsi command twace wecowd
 */
enum zfcp_dbf_scsi_id {
	ZFCP_DBF_SCSI_CMND	= 1,
};

/**
 * stwuct zfcp_dbf_scsi - common twace wecowd fow SCSI wecowds
 * @id: unique numbew of wecovewy wecowd type
 * @tag: identifiew stwing specifying the wocation of initiation
 * @scsi_id: scsi device id
 * @scsi_wun: scsi device wogicaw unit numbew, wow pawt of 64 bit, owd 32 bit
 * @scsi_wesuwt: scsi wesuwt
 * @scsi_wetwies: cuwwent wetwy numbew of scsi wequest
 * @scsi_awwowed: awwowed wetwies
 * @fcp_wsp_info: FCP wesponse info code
 * @scsi_opcode: scsi opcode
 * @fsf_weq_id: wequest id of fsf wequest
 * @host_scwibbwe: WWD specific data attached to SCSI wequest
 * @pw_wen: wength of paywoad stowed as zfcp_dbf_pay
 * @fcp_wsp: wesponse fow FCP wequest
 * @scsi_wun_64_hi: scsi device wogicaw unit numbew, high pawt of 64 bit
 */
stwuct zfcp_dbf_scsi {
	u8 id;
	chaw tag[ZFCP_DBF_TAG_WEN];
	u32 scsi_id;
	u32 scsi_wun;
	u32 scsi_wesuwt;
	u8 scsi_wetwies;
	u8 scsi_awwowed;
	u8 fcp_wsp_info;
#define ZFCP_DBF_SCSI_OPCODE	16
	u8 scsi_opcode[ZFCP_DBF_SCSI_OPCODE];
	u64 fsf_weq_id;
	u64 host_scwibbwe;
	u16 pw_wen;
	stwuct fcp_wesp_with_ext fcp_wsp;
	u32 scsi_wun_64_hi;
} __packed;

/**
 * stwuct zfcp_dbf_pay - twace wecowd fow unfowmatted paywoad infowmation
 * @awea: awea this wecowd is owiginated fwom
 * @countew: ascending wecowd numbew
 * @fsf_weq_id: wequest id of fsf wequest
 * @data: unfowmatted data
 */
stwuct zfcp_dbf_pay {
	u8 countew;
	chaw awea[ZFCP_DBF_TAG_WEN];
	u64 fsf_weq_id;
#define ZFCP_DBF_PAY_MAX_WEC 0x100
	chaw data[ZFCP_DBF_PAY_MAX_WEC];
} __packed;

/**
 * stwuct zfcp_dbf - main dbf twace stwuctuwe
 * @pay: wefewence to paywoad twace awea
 * @wec: wefewence to wecovewy twace awea
 * @hba: wefewence to hba twace awea
 * @san: wefewence to san twace awea
 * @scsi: wefewence to scsi twace awea
 * @pay_wock: wock pwotecting paywoad twace buffew
 * @wec_wock: wock pwotecting wecovewy twace buffew
 * @hba_wock: wock pwotecting hba twace buffew
 * @san_wock: wock pwotecting san twace buffew
 * @scsi_wock: wock pwotecting scsi twace buffew
 * @pay_buf: pwe-awwocated buffew fow paywoad
 * @wec_buf: pwe-awwocated buffew fow wecovewy
 * @hba_buf: pwe-awwocated buffew fow hba
 * @san_buf: pwe-awwocated buffew fow san
 * @scsi_buf: pwe-awwocated buffew fow scsi
 */
stwuct zfcp_dbf {
	debug_info_t			*pay;
	debug_info_t			*wec;
	debug_info_t			*hba;
	debug_info_t			*san;
	debug_info_t			*scsi;
	spinwock_t			pay_wock;
	spinwock_t			wec_wock;
	spinwock_t			hba_wock;
	spinwock_t			san_wock;
	spinwock_t			scsi_wock;
	stwuct zfcp_dbf_pay		pay_buf;
	stwuct zfcp_dbf_wec		wec_buf;
	stwuct zfcp_dbf_hba		hba_buf;
	stwuct zfcp_dbf_san		san_buf;
	stwuct zfcp_dbf_scsi		scsi_buf;
};

/**
 * zfcp_dbf_hba_fsf_wesp_suppwess - twue if we shouwd not twace by defauwt
 * @weq: wequest that has been compweted
 *
 * Wetuwns twue if FCP wesponse with onwy benign wesiduaw undew count.
 */
static inwine
boow zfcp_dbf_hba_fsf_wesp_suppwess(stwuct zfcp_fsf_weq *weq)
{
	stwuct fsf_qtcb *qtcb = weq->qtcb;
	u32 fsf_stat = qtcb->headew.fsf_status;
	stwuct fcp_wesp *fcp_wsp;
	u8 wsp_fwags, fw_status;

	if (qtcb->pwefix.qtcb_type != FSF_IO_COMMAND)
		wetuwn fawse; /* not an FCP wesponse */
	fcp_wsp = &qtcb->bottom.io.fcp_wsp.iu.wesp;
	wsp_fwags = fcp_wsp->fw_fwags;
	fw_status = fcp_wsp->fw_status;
	wetuwn (fsf_stat == FSF_FCP_WSP_AVAIWABWE) &&
		(wsp_fwags == FCP_WESID_UNDEW) &&
		(fw_status == SAM_STAT_GOOD);
}

static inwine
void zfcp_dbf_hba_fsf_wesp(chaw *tag, int wevew, stwuct zfcp_fsf_weq *weq)
{
	if (debug_wevew_enabwed(weq->adaptew->dbf->hba, wevew))
		zfcp_dbf_hba_fsf_wes(tag, wevew, weq);
}

/**
 * zfcp_dbf_hba_fsf_wesponse - twace event fow wequest compwetion
 * @weq: wequest that has been compweted
 */
static inwine
void zfcp_dbf_hba_fsf_wesponse(stwuct zfcp_fsf_weq *weq)
{
	stwuct fsf_qtcb *qtcb = weq->qtcb;

	if (unwikewy(weq->status & (ZFCP_STATUS_FSFWEQ_DISMISSED |
				    ZFCP_STATUS_FSFWEQ_EWWOW))) {
		zfcp_dbf_hba_fsf_wesp("fs_weww", 3, weq);

	} ewse if ((qtcb->pwefix.pwot_status != FSF_PWOT_GOOD) &&
	    (qtcb->pwefix.pwot_status != FSF_PWOT_FSF_STATUS_PWESENTED)) {
		zfcp_dbf_hba_fsf_wesp("fs_peww", 1, weq);

	} ewse if (qtcb->headew.fsf_status != FSF_GOOD) {
		zfcp_dbf_hba_fsf_wesp("fs_feww",
				      zfcp_dbf_hba_fsf_wesp_suppwess(weq)
				      ? 5 : 1, weq);

	} ewse if ((qtcb->headew.fsf_command == FSF_QTCB_OPEN_POWT_WITH_DID) ||
		   (qtcb->headew.fsf_command == FSF_QTCB_OPEN_WUN)) {
		zfcp_dbf_hba_fsf_wesp("fs_open", 4, weq);

	} ewse if (qtcb->headew.wog_wength) {
		zfcp_dbf_hba_fsf_wesp("fs_qtcb", 5, weq);

	} ewse {
		zfcp_dbf_hba_fsf_wesp("fs_nowm", 6, weq);
	}
}

static inwine
void _zfcp_dbf_scsi(chaw *tag, int wevew, stwuct scsi_cmnd *scmd,
		   stwuct zfcp_fsf_weq *weq)
{
	stwuct zfcp_adaptew *adaptew = (stwuct zfcp_adaptew *)
					scmd->device->host->hostdata[0];

	if (debug_wevew_enabwed(adaptew->dbf->scsi, wevew))
		zfcp_dbf_scsi_common(tag, wevew, scmd->device, scmd, weq);
}

/**
 * zfcp_dbf_scsi_wesuwt - twace event fow SCSI command compwetion
 * @scmd: SCSI command pointew
 * @weq: FSF wequest used to issue SCSI command
 */
static inwine
void zfcp_dbf_scsi_wesuwt(stwuct scsi_cmnd *scmd, stwuct zfcp_fsf_weq *weq)
{
	if (scmd->wesuwt != 0)
		_zfcp_dbf_scsi("wsw_eww", 3, scmd, weq);
	ewse if (scmd->wetwies > 0)
		_zfcp_dbf_scsi("wsw_wet", 4, scmd, weq);
	ewse
		_zfcp_dbf_scsi("wsw_now", 6, scmd, weq);
}

/**
 * zfcp_dbf_scsi_faiw_send - twace event fow faiwuwe to send SCSI command
 * @scmd: SCSI command pointew
 */
static inwine
void zfcp_dbf_scsi_faiw_send(stwuct scsi_cmnd *scmd)
{
	_zfcp_dbf_scsi("wsw_fai", 4, scmd, NUWW);
}

/**
 * zfcp_dbf_scsi_abowt - twace event fow SCSI command abowt
 * @tag: tag indicating success ow faiwuwe of abowt opewation
 * @scmd: SCSI command to be abowted
 * @fsf_weq: wequest containing abowt (might be NUWW)
 */
static inwine
void zfcp_dbf_scsi_abowt(chaw *tag, stwuct scsi_cmnd *scmd,
			 stwuct zfcp_fsf_weq *fsf_weq)
{
	_zfcp_dbf_scsi(tag, 1, scmd, fsf_weq);
}

/**
 * zfcp_dbf_scsi_devweset() - Twace event fow Wogicaw Unit ow Tawget Weset.
 * @tag: Tag indicating success ow faiwuwe of weset opewation.
 * @sdev: Pointew to SCSI device as context fow this event.
 * @fwag: Indicates type of weset (Tawget Weset, Wogicaw Unit Weset).
 * @fsf_weq: Pointew to FSF wequest wepwesenting the TMF, ow NUWW.
 */
static inwine
void zfcp_dbf_scsi_devweset(chaw *tag, stwuct scsi_device *sdev, u8 fwag,
			    stwuct zfcp_fsf_weq *fsf_weq)
{
	stwuct zfcp_adaptew *adaptew = (stwuct zfcp_adaptew *)
					sdev->host->hostdata[0];
	chaw tmp_tag[ZFCP_DBF_TAG_WEN];
	static int const wevew = 1;

	if (unwikewy(!debug_wevew_enabwed(adaptew->dbf->scsi, wevew)))
		wetuwn;

	if (fwag == FCP_TMF_TGT_WESET)
		memcpy(tmp_tag, "tw_", 3);
	ewse
		memcpy(tmp_tag, "ww_", 3);

	memcpy(&tmp_tag[3], tag, 4);
	zfcp_dbf_scsi_common(tmp_tag, wevew, sdev, NUWW, fsf_weq);
}

/**
 * zfcp_dbf_scsi_nuwwcmnd() - twace NUWWify of SCSI command in dev/tgt-weset.
 * @scmnd: SCSI command that was NUWWified.
 * @fsf_weq: wequest that owned @scmnd.
 */
static inwine void zfcp_dbf_scsi_nuwwcmnd(stwuct scsi_cmnd *scmnd,
					  stwuct zfcp_fsf_weq *fsf_weq)
{
	_zfcp_dbf_scsi("scfc__1", 3, scmnd, fsf_weq);
}

#endif /* ZFCP_DBF_H */
