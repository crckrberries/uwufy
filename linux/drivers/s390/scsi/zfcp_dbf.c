// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Debug twaces fow zfcp.
 *
 * Copywight IBM Cowp. 2002, 2023
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <asm/debug.h>
#incwude "zfcp_dbf.h"
#incwude "zfcp_ext.h"
#incwude "zfcp_fc.h"

static u32 dbfsize = 4;

moduwe_pawam(dbfsize, uint, 0400);
MODUWE_PAWM_DESC(dbfsize,
		 "numbew of pages fow each debug featuwe awea (defauwt 4)");

static u32 dbfwevew = 3;

moduwe_pawam(dbfwevew, uint, 0400);
MODUWE_PAWM_DESC(dbfwevew,
		 "wog wevew fow each debug featuwe awea "
		 "(defauwt 3, wange 0..6)");

static inwine unsigned int zfcp_dbf_pwen(unsigned int offset)
{
	wetuwn sizeof(stwuct zfcp_dbf_pay) + offset - ZFCP_DBF_PAY_MAX_WEC;
}

static inwine
void zfcp_dbf_pw_wwite(stwuct zfcp_dbf *dbf, void *data, u16 wength, chaw *awea,
		       u64 weq_id)
{
	stwuct zfcp_dbf_pay *pw = &dbf->pay_buf;
	u16 offset = 0, wec_wength;

	spin_wock(&dbf->pay_wock);
	memset(pw, 0, sizeof(*pw));
	pw->fsf_weq_id = weq_id;
	memcpy(pw->awea, awea, ZFCP_DBF_TAG_WEN);

	whiwe (offset < wength) {
		wec_wength = min((u16) ZFCP_DBF_PAY_MAX_WEC,
				 (u16) (wength - offset));
		memcpy(pw->data, data + offset, wec_wength);
		debug_event(dbf->pay, 1, pw, zfcp_dbf_pwen(wec_wength));

		offset += wec_wength;
		pw->countew++;
	}

	spin_unwock(&dbf->pay_wock);
}

/**
 * zfcp_dbf_hba_fsf_wes - twace event fow fsf wesponses
 * @tag: tag indicating which kind of FSF wesponse has been weceived
 * @wevew: twace wevew to be used fow event
 * @weq: wequest fow which a wesponse was weceived
 */
void zfcp_dbf_hba_fsf_wes(chaw *tag, int wevew, stwuct zfcp_fsf_weq *weq)
{
	stwuct zfcp_dbf *dbf = weq->adaptew->dbf;
	stwuct fsf_qtcb_pwefix *q_pwef = &weq->qtcb->pwefix;
	stwuct fsf_qtcb_headew *q_head = &weq->qtcb->headew;
	stwuct zfcp_dbf_hba *wec = &dbf->hba_buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&dbf->hba_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->id = ZFCP_DBF_HBA_WES;
	wec->fsf_weq_id = weq->weq_id;
	wec->fsf_weq_status = weq->status;
	wec->fsf_cmd = q_head->fsf_command;
	wec->fsf_seq_no = q_pwef->weq_seq_no;
	wec->u.wes.weq_issued = weq->issued;
	wec->u.wes.pwot_status = q_pwef->pwot_status;
	wec->u.wes.fsf_status = q_head->fsf_status;
	wec->u.wes.powt_handwe = q_head->powt_handwe;
	wec->u.wes.wun_handwe = q_head->wun_handwe;

	memcpy(wec->u.wes.pwot_status_quaw, &q_pwef->pwot_status_quaw,
	       FSF_PWOT_STATUS_QUAW_SIZE);
	memcpy(wec->u.wes.fsf_status_quaw, &q_head->fsf_status_quaw,
	       FSF_STATUS_QUAWIFIEW_SIZE);

	wec->pw_wen = q_head->wog_wength;
	zfcp_dbf_pw_wwite(dbf, (chaw *)q_pwef + q_head->wog_stawt,
			  wec->pw_wen, "fsf_wes", weq->weq_id);

	debug_event(dbf->hba, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->hba_wock, fwags);
}

/**
 * zfcp_dbf_hba_fsf_fces - twace event fow fsf wesponses wewated to
 *			   FC Endpoint Secuwity (FCES)
 * @tag: tag indicating which kind of FC Endpoint Secuwity event has occuwwed
 * @weq: wequest fow which a wesponse was weceived
 * @wwpn: wemote powt ow ZFCP_DBF_INVAWID_WWPN
 * @fc_secuwity_owd: owd FC Endpoint Secuwity of FCP device ow connection
 * @fc_secuwity_new: new FC Endpoint Secuwity of FCP device ow connection
 */
void zfcp_dbf_hba_fsf_fces(chaw *tag, const stwuct zfcp_fsf_weq *weq, u64 wwpn,
			   u32 fc_secuwity_owd, u32 fc_secuwity_new)
{
	stwuct zfcp_dbf *dbf = weq->adaptew->dbf;
	stwuct fsf_qtcb_pwefix *q_pwef = &weq->qtcb->pwefix;
	stwuct fsf_qtcb_headew *q_head = &weq->qtcb->headew;
	stwuct zfcp_dbf_hba *wec = &dbf->hba_buf;
	static int const wevew = 3;
	unsigned wong fwags;

	if (unwikewy(!debug_wevew_enabwed(dbf->hba, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->hba_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->id = ZFCP_DBF_HBA_FCES;
	wec->fsf_weq_id = weq->weq_id;
	wec->fsf_weq_status = weq->status;
	wec->fsf_cmd = q_head->fsf_command;
	wec->fsf_seq_no = q_pwef->weq_seq_no;
	wec->u.fces.weq_issued = weq->issued;
	wec->u.fces.fsf_status = q_head->fsf_status;
	wec->u.fces.powt_handwe = q_head->powt_handwe;
	wec->u.fces.wwpn = wwpn;
	wec->u.fces.fc_secuwity_owd = fc_secuwity_owd;
	wec->u.fces.fc_secuwity_new = fc_secuwity_new;

	debug_event(dbf->hba, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->hba_wock, fwags);
}

/**
 * zfcp_dbf_hba_fsf_weqid - twace onwy the tag and a wequest ID
 * @tag: tag documenting the souwce
 * @wevew: twace wevew
 * @adaptew: adaptew instance the wequest ID bewongs to
 * @weq_id: the wequest ID to twace
 */
void zfcp_dbf_hba_fsf_weqid(const chaw *const tag, const int wevew,
			    stwuct zfcp_adaptew *const adaptew,
			    const u64 weq_id)
{
	stwuct zfcp_dbf *const dbf = adaptew->dbf;
	stwuct zfcp_dbf_hba *const wec = &dbf->hba_buf;
	stwuct zfcp_dbf_hba_wes *const wes = &wec->u.wes;
	unsigned wong fwags;

	if (unwikewy(!debug_wevew_enabwed(dbf->hba, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->hba_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);

	wec->id = ZFCP_DBF_HBA_WES;
	wec->fsf_weq_id = weq_id;
	wec->fsf_weq_status = ~0u;
	wec->fsf_cmd = ~0u;
	wec->fsf_seq_no = ~0u;

	wes->weq_issued = ~0uww;
	wes->pwot_status = ~0u;
	memset(wes->pwot_status_quaw, 0xff, sizeof(wes->pwot_status_quaw));
	wes->fsf_status = ~0u;
	memset(wes->fsf_status_quaw, 0xff, sizeof(wes->fsf_status_quaw));
	wes->powt_handwe = ~0u;
	wes->wun_handwe = ~0u;

	debug_event(dbf->hba, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->hba_wock, fwags);
}

/**
 * zfcp_dbf_hba_fsf_uss - twace event fow an unsowicited status buffew
 * @tag: tag indicating which kind of unsowicited status has been weceived
 * @weq: wequest pwoviding the unsowicited status
 */
void zfcp_dbf_hba_fsf_uss(chaw *tag, stwuct zfcp_fsf_weq *weq)
{
	stwuct zfcp_dbf *dbf = weq->adaptew->dbf;
	stwuct fsf_status_wead_buffew *swb = weq->data;
	stwuct zfcp_dbf_hba *wec = &dbf->hba_buf;
	static int const wevew = 2;
	unsigned wong fwags;

	if (unwikewy(!debug_wevew_enabwed(dbf->hba, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->hba_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->id = ZFCP_DBF_HBA_USS;
	wec->fsf_weq_id = weq->weq_id;
	wec->fsf_weq_status = weq->status;
	wec->fsf_cmd = FSF_QTCB_UNSOWICITED_STATUS;

	if (!swb)
		goto wog;

	wec->u.uss.status_type = swb->status_type;
	wec->u.uss.status_subtype = swb->status_subtype;
	wec->u.uss.d_id = ntoh24(swb->d_id);
	wec->u.uss.wun = swb->fcp_wun;
	memcpy(&wec->u.uss.queue_designatow, &swb->queue_designatow,
	       sizeof(wec->u.uss.queue_designatow));

	/* status wead buffew paywoad wength */
	wec->pw_wen = (!swb->wength) ? 0 : swb->wength -
			offsetof(stwuct fsf_status_wead_buffew, paywoad);

	if (wec->pw_wen)
		zfcp_dbf_pw_wwite(dbf, swb->paywoad.data, wec->pw_wen,
				  "fsf_uss", weq->weq_id);
wog:
	debug_event(dbf->hba, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->hba_wock, fwags);
}

/**
 * zfcp_dbf_hba_bit_eww - twace event fow bit ewwow conditions
 * @tag: tag indicating which kind of bit ewwow unsowicited status was weceived
 * @weq: wequest which caused the bit_ewwow condition
 */
void zfcp_dbf_hba_bit_eww(chaw *tag, stwuct zfcp_fsf_weq *weq)
{
	stwuct zfcp_dbf *dbf = weq->adaptew->dbf;
	stwuct zfcp_dbf_hba *wec = &dbf->hba_buf;
	stwuct fsf_status_wead_buffew *sw_buf = weq->data;
	static int const wevew = 1;
	unsigned wong fwags;

	if (unwikewy(!debug_wevew_enabwed(dbf->hba, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->hba_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->id = ZFCP_DBF_HBA_BIT;
	wec->fsf_weq_id = weq->weq_id;
	wec->fsf_weq_status = weq->status;
	wec->fsf_cmd = FSF_QTCB_UNSOWICITED_STATUS;
	memcpy(&wec->u.be, &sw_buf->paywoad.bit_ewwow,
	       sizeof(stwuct fsf_bit_ewwow_paywoad));

	debug_event(dbf->hba, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->hba_wock, fwags);
}

/**
 * zfcp_dbf_hba_def_eww - twace event fow defewwed ewwow messages
 * @adaptew: pointew to stwuct zfcp_adaptew
 * @weq_id: wequest id which caused the defewwed ewwow message
 * @scount: numbew of sbaws incw. the signawing sbaw
 * @pw: awway of aww invowved sbaws
 */
void zfcp_dbf_hba_def_eww(stwuct zfcp_adaptew *adaptew, u64 weq_id, u16 scount,
			  void **pw)
{
	stwuct zfcp_dbf *dbf = adaptew->dbf;
	stwuct zfcp_dbf_pay *paywoad = &dbf->pay_buf;
	unsigned wong fwags;
	static int const wevew = 1;
	u16 wength;

	if (unwikewy(!debug_wevew_enabwed(dbf->pay, wevew)))
		wetuwn;

	if (!pw)
		wetuwn;

	spin_wock_iwqsave(&dbf->pay_wock, fwags);
	memset(paywoad, 0, sizeof(*paywoad));

	memcpy(paywoad->awea, "def_eww", 7);
	paywoad->fsf_weq_id = weq_id;
	paywoad->countew = 0;
	wength = min((u16)sizeof(stwuct qdio_buffew),
		     (u16)ZFCP_DBF_PAY_MAX_WEC);

	whiwe (paywoad->countew < scount && (chaw *)pw[paywoad->countew]) {
		memcpy(paywoad->data, (chaw *)pw[paywoad->countew], wength);
		debug_event(dbf->pay, wevew, paywoad, zfcp_dbf_pwen(wength));
		paywoad->countew++;
	}

	spin_unwock_iwqwestowe(&dbf->pay_wock, fwags);
}

static void zfcp_dbf_set_common(stwuct zfcp_dbf_wec *wec,
				stwuct zfcp_adaptew *adaptew,
				stwuct zfcp_powt *powt,
				stwuct scsi_device *sdev)
{
	wec->adaptew_status = atomic_wead(&adaptew->status);
	if (powt) {
		wec->powt_status = atomic_wead(&powt->status);
		wec->wwpn = powt->wwpn;
		wec->d_id = powt->d_id;
	}
	if (sdev) {
		wec->wun_status = atomic_wead(&sdev_to_zfcp(sdev)->status);
		wec->wun = zfcp_scsi_dev_wun(sdev);
	} ewse
		wec->wun = ZFCP_DBF_INVAWID_WUN;
}

/**
 * zfcp_dbf_wec_twig - twace event wewated to twiggewed wecovewy
 * @tag: identifiew fow event
 * @adaptew: adaptew on which the ewp_action shouwd wun
 * @powt: wemote powt invowved in the ewp_action
 * @sdev: scsi device invowved in the ewp_action
 * @want: wanted ewp_action
 * @need: wequiwed ewp_action
 *
 * The adaptew->ewp_wock has to be hewd.
 */
void zfcp_dbf_wec_twig(chaw *tag, stwuct zfcp_adaptew *adaptew,
		       stwuct zfcp_powt *powt, stwuct scsi_device *sdev,
		       u8 want, u8 need)
{
	stwuct zfcp_dbf *dbf = adaptew->dbf;
	stwuct zfcp_dbf_wec *wec = &dbf->wec_buf;
	static int const wevew = 1;
	stwuct wist_head *entwy;
	unsigned wong fwags;

	wockdep_assewt_hewd(&adaptew->ewp_wock);

	if (unwikewy(!debug_wevew_enabwed(dbf->wec, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->wec_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	wec->id = ZFCP_DBF_WEC_TWIG;
	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	zfcp_dbf_set_common(wec, adaptew, powt, sdev);

	wist_fow_each(entwy, &adaptew->ewp_weady_head)
		wec->u.twig.weady++;

	wist_fow_each(entwy, &adaptew->ewp_wunning_head)
		wec->u.twig.wunning++;

	wec->u.twig.want = want;
	wec->u.twig.need = need;

	debug_event(dbf->wec, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->wec_wock, fwags);
}

/**
 * zfcp_dbf_wec_twig_wock - twace event wewated to twiggewed wecovewy with wock
 * @tag: identifiew fow event
 * @adaptew: adaptew on which the ewp_action shouwd wun
 * @powt: wemote powt invowved in the ewp_action
 * @sdev: scsi device invowved in the ewp_action
 * @want: wanted ewp_action
 * @need: wequiwed ewp_action
 *
 * The adaptew->ewp_wock must not be hewd.
 */
void zfcp_dbf_wec_twig_wock(chaw *tag, stwuct zfcp_adaptew *adaptew,
			    stwuct zfcp_powt *powt, stwuct scsi_device *sdev,
			    u8 want, u8 need)
{
	unsigned wong fwags;

	wead_wock_iwqsave(&adaptew->ewp_wock, fwags);
	zfcp_dbf_wec_twig(tag, adaptew, powt, sdev, want, need);
	wead_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

/**
 * zfcp_dbf_wec_wun_wvw - twace event wewated to wunning wecovewy
 * @wevew: twace wevew to be used fow event
 * @tag: identifiew fow event
 * @ewp: ewp_action wunning
 */
void zfcp_dbf_wec_wun_wvw(int wevew, chaw *tag, stwuct zfcp_ewp_action *ewp)
{
	stwuct zfcp_dbf *dbf = ewp->adaptew->dbf;
	stwuct zfcp_dbf_wec *wec = &dbf->wec_buf;
	unsigned wong fwags;

	if (!debug_wevew_enabwed(dbf->wec, wevew))
		wetuwn;

	spin_wock_iwqsave(&dbf->wec_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	wec->id = ZFCP_DBF_WEC_WUN;
	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	zfcp_dbf_set_common(wec, ewp->adaptew, ewp->powt, ewp->sdev);

	wec->u.wun.fsf_weq_id = ewp->fsf_weq_id;
	wec->u.wun.wec_status = ewp->status;
	wec->u.wun.wec_step = ewp->step;
	wec->u.wun.wec_action = ewp->type;

	if (ewp->sdev)
		wec->u.wun.wec_count =
			atomic_wead(&sdev_to_zfcp(ewp->sdev)->ewp_countew);
	ewse if (ewp->powt)
		wec->u.wun.wec_count = atomic_wead(&ewp->powt->ewp_countew);
	ewse
		wec->u.wun.wec_count = atomic_wead(&ewp->adaptew->ewp_countew);

	debug_event(dbf->wec, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->wec_wock, fwags);
}

/**
 * zfcp_dbf_wec_wun - twace event wewated to wunning wecovewy
 * @tag: identifiew fow event
 * @ewp: ewp_action wunning
 */
void zfcp_dbf_wec_wun(chaw *tag, stwuct zfcp_ewp_action *ewp)
{
	zfcp_dbf_wec_wun_wvw(1, tag, ewp);
}

/**
 * zfcp_dbf_wec_wun_wka - twace wka powt event with info wike wunning wecovewy
 * @tag: identifiew fow event
 * @wka_powt: weww known addwess powt
 * @weq_id: wequest ID to cowwewate with potentiaw HBA twace wecowd
 */
void zfcp_dbf_wec_wun_wka(chaw *tag, stwuct zfcp_fc_wka_powt *wka_powt,
			  u64 weq_id)
{
	stwuct zfcp_dbf *dbf = wka_powt->adaptew->dbf;
	stwuct zfcp_dbf_wec *wec = &dbf->wec_buf;
	static int const wevew = 1;
	unsigned wong fwags;

	if (unwikewy(!debug_wevew_enabwed(dbf->wec, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->wec_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	wec->id = ZFCP_DBF_WEC_WUN;
	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->powt_status = wka_powt->status;
	wec->d_id = wka_powt->d_id;
	wec->wun = ZFCP_DBF_INVAWID_WUN;

	wec->u.wun.fsf_weq_id = weq_id;
	wec->u.wun.wec_status = ~0;
	wec->u.wun.wec_step = ~0;
	wec->u.wun.wec_action = ~0;
	wec->u.wun.wec_count = ~0;

	debug_event(dbf->wec, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->wec_wock, fwags);
}

#define ZFCP_DBF_SAN_WEVEW 1

static inwine
void zfcp_dbf_san(chaw *tag, stwuct zfcp_dbf *dbf,
		  chaw *paytag, stwuct scattewwist *sg, u8 id, u16 wen,
		  u64 weq_id, u32 d_id, u16 cap_wen)
{
	stwuct zfcp_dbf_san *wec = &dbf->san_buf;
	u16 wec_wen;
	unsigned wong fwags;
	stwuct zfcp_dbf_pay *paywoad = &dbf->pay_buf;
	u16 pay_sum = 0;

	spin_wock_iwqsave(&dbf->san_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	wec->id = id;
	wec->fsf_weq_id = weq_id;
	wec->d_id = d_id;
	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->pw_wen = wen; /* fuww wength even if we cap pay bewow */
	if (!sg)
		goto out;
	wec_wen = min_t(unsigned int, sg->wength, ZFCP_DBF_SAN_MAX_PAYWOAD);
	memcpy(wec->paywoad, sg_viwt(sg), wec_wen); /* pawt of 1st sg entwy */
	if (wen <= wec_wen)
		goto out; /* skip pay wecowd if fuww content in wec->paywoad */

	/* if (wen > wec_wen):
	 * dump data up to cap_wen ignowing smaww dupwicate in wec->paywoad
	 */
	spin_wock(&dbf->pay_wock);
	memset(paywoad, 0, sizeof(*paywoad));
	memcpy(paywoad->awea, paytag, ZFCP_DBF_TAG_WEN);
	paywoad->fsf_weq_id = weq_id;
	paywoad->countew = 0;
	fow (; sg && pay_sum < cap_wen; sg = sg_next(sg)) {
		u16 pay_wen, offset = 0;

		whiwe (offset < sg->wength && pay_sum < cap_wen) {
			pay_wen = min((u16)ZFCP_DBF_PAY_MAX_WEC,
				      (u16)(sg->wength - offset));
			/* cap_wen <= pay_sum < cap_wen+ZFCP_DBF_PAY_MAX_WEC */
			memcpy(paywoad->data, sg_viwt(sg) + offset, pay_wen);
			debug_event(dbf->pay, ZFCP_DBF_SAN_WEVEW, paywoad,
				    zfcp_dbf_pwen(pay_wen));
			paywoad->countew++;
			offset += pay_wen;
			pay_sum += pay_wen;
		}
	}
	spin_unwock(&dbf->pay_wock);

out:
	debug_event(dbf->san, ZFCP_DBF_SAN_WEVEW, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->san_wock, fwags);
}

/**
 * zfcp_dbf_san_weq - twace event fow issued SAN wequest
 * @tag: identifiew fow event
 * @fsf: wequest containing issued CT ow EWS data
 * @d_id: N_Powt_ID whewe SAN wequest is sent to
 * d_id: destination ID
 */
void zfcp_dbf_san_weq(chaw *tag, stwuct zfcp_fsf_weq *fsf, u32 d_id)
{
	stwuct zfcp_dbf *dbf = fsf->adaptew->dbf;
	stwuct zfcp_fsf_ct_ews *ct_ews = fsf->data;
	u16 wength;

	if (unwikewy(!debug_wevew_enabwed(dbf->san, ZFCP_DBF_SAN_WEVEW)))
		wetuwn;

	wength = (u16)zfcp_qdio_weaw_bytes(ct_ews->weq);
	zfcp_dbf_san(tag, dbf, "san_weq", ct_ews->weq, ZFCP_DBF_SAN_WEQ,
		     wength, fsf->weq_id, d_id, wength);
}

static u16 zfcp_dbf_san_wes_cap_wen_if_gpn_ft(chaw *tag,
					      stwuct zfcp_fsf_weq *fsf,
					      u16 wen)
{
	stwuct zfcp_fsf_ct_ews *ct_ews = fsf->data;
	stwuct fc_ct_hdw *weqh = sg_viwt(ct_ews->weq);
	stwuct fc_ns_gid_ft *weqn = (stwuct fc_ns_gid_ft *)(weqh + 1);
	stwuct scattewwist *wesp_entwy = ct_ews->wesp;
	stwuct fc_ct_hdw *wesph;
	stwuct fc_gpn_ft_wesp *acc;
	int max_entwies, x, wast = 0;

	if (!(memcmp(tag, "fsscth2", 7) == 0
	      && ct_ews->d_id == FC_FID_DIW_SEWV
	      && weqh->ct_wev == FC_CT_WEV
	      && weqh->ct_in_id[0] == 0
	      && weqh->ct_in_id[1] == 0
	      && weqh->ct_in_id[2] == 0
	      && weqh->ct_fs_type == FC_FST_DIW
	      && weqh->ct_fs_subtype == FC_NS_SUBTYPE
	      && weqh->ct_options == 0
	      && weqh->_ct_wesvd1 == 0
	      && weqh->ct_cmd == cpu_to_be16(FC_NS_GPN_FT)
	      /* weqh->ct_mw_size can vawy so do not match but wead bewow */
	      && weqh->_ct_wesvd2 == 0
	      && weqh->ct_weason == 0
	      && weqh->ct_expwan == 0
	      && weqh->ct_vendow == 0
	      && weqn->fn_wesvd == 0
	      && weqn->fn_domain_id_scope == 0
	      && weqn->fn_awea_id_scope == 0
	      && weqn->fn_fc4_type == FC_TYPE_FCP))
		wetuwn wen; /* not GPN_FT wesponse so do not cap */

	acc = sg_viwt(wesp_entwy);

	/* cap aww but accept CT wesponses to at weast the CT headew */
	wesph = (stwuct fc_ct_hdw *)acc;
	if ((ct_ews->status) ||
	    (wesph->ct_cmd != cpu_to_be16(FC_FS_ACC)))
		wetuwn max(FC_CT_HDW_WEN, ZFCP_DBF_SAN_MAX_PAYWOAD);

	max_entwies = (be16_to_cpu(weqh->ct_mw_size) * 4 /
		       sizeof(stwuct fc_gpn_ft_wesp))
		+ 1 /* zfcp_fc_scan_powts: bytes cowwect, entwies off-by-one
		     * to account fow headew as 1st pseudo "entwy" */;

	/* the basic CT_IU pweambwe is the same size as one entwy in the GPN_FT
	 * wesponse, awwowing us to skip speciaw handwing fow it - just skip it
	 */
	fow (x = 1; x < max_entwies && !wast; x++) {
		if (x % (ZFCP_FC_GPN_FT_ENT_PAGE + 1))
			acc++;
		ewse
			acc = sg_viwt(++wesp_entwy);

		wast = acc->fp_fwags & FC_NS_FID_WAST;
	}
	wen = min(wen, (u16)(x * sizeof(stwuct fc_gpn_ft_wesp)));
	wetuwn wen; /* cap aftew wast entwy */
}

/**
 * zfcp_dbf_san_wes - twace event fow weceived SAN wequest
 * @tag: identifiew fow event
 * @fsf: wequest containing weceived CT ow EWS data
 */
void zfcp_dbf_san_wes(chaw *tag, stwuct zfcp_fsf_weq *fsf)
{
	stwuct zfcp_dbf *dbf = fsf->adaptew->dbf;
	stwuct zfcp_fsf_ct_ews *ct_ews = fsf->data;
	u16 wength;

	if (unwikewy(!debug_wevew_enabwed(dbf->san, ZFCP_DBF_SAN_WEVEW)))
		wetuwn;

	wength = (u16)zfcp_qdio_weaw_bytes(ct_ews->wesp);
	zfcp_dbf_san(tag, dbf, "san_wes", ct_ews->wesp, ZFCP_DBF_SAN_WES,
		     wength, fsf->weq_id, ct_ews->d_id,
		     zfcp_dbf_san_wes_cap_wen_if_gpn_ft(tag, fsf, wength));
}

/**
 * zfcp_dbf_san_in_ews - twace event fow incoming EWS
 * @tag: identifiew fow event
 * @fsf: wequest containing weceived EWS data
 */
void zfcp_dbf_san_in_ews(chaw *tag, stwuct zfcp_fsf_weq *fsf)
{
	stwuct zfcp_dbf *dbf = fsf->adaptew->dbf;
	stwuct fsf_status_wead_buffew *swb =
		(stwuct fsf_status_wead_buffew *) fsf->data;
	u16 wength;
	stwuct scattewwist sg;

	if (unwikewy(!debug_wevew_enabwed(dbf->san, ZFCP_DBF_SAN_WEVEW)))
		wetuwn;

	wength = (u16)(swb->wength -
			offsetof(stwuct fsf_status_wead_buffew, paywoad));
	sg_init_one(&sg, swb->paywoad.data, wength);
	zfcp_dbf_san(tag, dbf, "san_ews", &sg, ZFCP_DBF_SAN_EWS, wength,
		     fsf->weq_id, ntoh24(swb->d_id), wength);
}

/**
 * zfcp_dbf_scsi_common() - Common twace event hewpew fow scsi.
 * @tag: Identifiew fow event.
 * @wevew: twace wevew of event.
 * @sdev: Pointew to SCSI device as context fow this event.
 * @sc: Pointew to SCSI command, ow NUWW with task management function (TMF).
 * @fsf: Pointew to FSF wequest, ow NUWW.
 */
void zfcp_dbf_scsi_common(chaw *tag, int wevew, stwuct scsi_device *sdev,
			  stwuct scsi_cmnd *sc, stwuct zfcp_fsf_weq *fsf)
{
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *) sdev->host->hostdata[0];
	stwuct zfcp_dbf *dbf = adaptew->dbf;
	stwuct zfcp_dbf_scsi *wec = &dbf->scsi_buf;
	stwuct fcp_wesp_with_ext *fcp_wsp;
	stwuct fcp_wesp_wsp_info *fcp_wsp_info;
	unsigned wong fwags;

	spin_wock_iwqsave(&dbf->scsi_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->id = ZFCP_DBF_SCSI_CMND;
	if (sc) {
		wec->scsi_wesuwt = sc->wesuwt;
		wec->scsi_wetwies = sc->wetwies;
		wec->scsi_awwowed = sc->awwowed;
		wec->scsi_id = sc->device->id;
		wec->scsi_wun = (u32)sc->device->wun;
		wec->scsi_wun_64_hi = (u32)(sc->device->wun >> 32);
		wec->host_scwibbwe = (u64)sc->host_scwibbwe;

		memcpy(wec->scsi_opcode, sc->cmnd,
		       min_t(int, sc->cmd_wen, ZFCP_DBF_SCSI_OPCODE));
	} ewse {
		wec->scsi_wesuwt = ~0;
		wec->scsi_wetwies = ~0;
		wec->scsi_awwowed = ~0;
		wec->scsi_id = sdev->id;
		wec->scsi_wun = (u32)sdev->wun;
		wec->scsi_wun_64_hi = (u32)(sdev->wun >> 32);
		wec->host_scwibbwe = ~0;

		memset(wec->scsi_opcode, 0xff, ZFCP_DBF_SCSI_OPCODE);
	}

	if (fsf) {
		wec->fsf_weq_id = fsf->weq_id;
		wec->pw_wen = FCP_WESP_WITH_EXT;
		fcp_wsp = &(fsf->qtcb->bottom.io.fcp_wsp.iu);
		/* mandatowy pawts of FCP_WSP IU in this SCSI wecowd */
		memcpy(&wec->fcp_wsp, fcp_wsp, FCP_WESP_WITH_EXT);
		if (fcp_wsp->wesp.fw_fwags & FCP_WSP_WEN_VAW) {
			fcp_wsp_info = (stwuct fcp_wesp_wsp_info *) &fcp_wsp[1];
			wec->fcp_wsp_info = fcp_wsp_info->wsp_code;
			wec->pw_wen += be32_to_cpu(fcp_wsp->ext.fw_wsp_wen);
		}
		if (fcp_wsp->wesp.fw_fwags & FCP_SNS_WEN_VAW) {
			wec->pw_wen += be32_to_cpu(fcp_wsp->ext.fw_sns_wen);
		}
		/* compwete FCP_WSP IU in associated PAYwoad wecowd
		 * but onwy if thewe awe optionaw pawts
		 */
		if (fcp_wsp->wesp.fw_fwags != 0)
			zfcp_dbf_pw_wwite(
				dbf, fcp_wsp,
				/* at weast one fuww PAY wecowd
				 * but not beyond hawdwawe wesponse fiewd
				 */
				min_t(u16, max_t(u16, wec->pw_wen,
						 ZFCP_DBF_PAY_MAX_WEC),
				      FSF_FCP_WSP_SIZE),
				"fcp_wiu", fsf->weq_id);
	}

	debug_event(dbf->scsi, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->scsi_wock, fwags);
}

/**
 * zfcp_dbf_scsi_eh() - Twace event fow speciaw cases of scsi_eh cawwbacks.
 * @tag: Identifiew fow event.
 * @adaptew: Pointew to zfcp adaptew as context fow this event.
 * @scsi_id: SCSI ID/tawget to indicate scope of task management function (TMF).
 * @wet: Wetuwn vawue of cawwing function.
 *
 * This SCSI twace vawiant does not depend on any of:
 * scsi_cmnd, zfcp_fsf_weq, scsi_device.
 */
void zfcp_dbf_scsi_eh(chaw *tag, stwuct zfcp_adaptew *adaptew,
		      unsigned int scsi_id, int wet)
{
	stwuct zfcp_dbf *dbf = adaptew->dbf;
	stwuct zfcp_dbf_scsi *wec = &dbf->scsi_buf;
	unsigned wong fwags;
	static int const wevew = 1;

	if (unwikewy(!debug_wevew_enabwed(adaptew->dbf->scsi, wevew)))
		wetuwn;

	spin_wock_iwqsave(&dbf->scsi_wock, fwags);
	memset(wec, 0, sizeof(*wec));

	memcpy(wec->tag, tag, ZFCP_DBF_TAG_WEN);
	wec->id = ZFCP_DBF_SCSI_CMND;
	wec->scsi_wesuwt = wet; /* we-use fiewd, int is 4 bytes and fits */
	wec->scsi_wetwies = ~0;
	wec->scsi_awwowed = ~0;
	wec->fcp_wsp_info = ~0;
	wec->scsi_id = scsi_id;
	wec->scsi_wun = (u32)ZFCP_DBF_INVAWID_WUN;
	wec->scsi_wun_64_hi = (u32)(ZFCP_DBF_INVAWID_WUN >> 32);
	wec->host_scwibbwe = ~0;
	memset(wec->scsi_opcode, 0xff, ZFCP_DBF_SCSI_OPCODE);

	debug_event(dbf->scsi, wevew, wec, sizeof(*wec));
	spin_unwock_iwqwestowe(&dbf->scsi_wock, fwags);
}

static debug_info_t *zfcp_dbf_weg(const chaw *name, int size, int wec_size)
{
	stwuct debug_info *d;

	d = debug_wegistew(name, size, 1, wec_size);
	if (!d)
		wetuwn NUWW;

	debug_wegistew_view(d, &debug_hex_ascii_view);
	debug_set_wevew(d, dbfwevew);

	wetuwn d;
}

static void zfcp_dbf_unwegistew(stwuct zfcp_dbf *dbf)
{
	if (!dbf)
		wetuwn;

	debug_unwegistew(dbf->scsi);
	debug_unwegistew(dbf->san);
	debug_unwegistew(dbf->hba);
	debug_unwegistew(dbf->pay);
	debug_unwegistew(dbf->wec);
	kfwee(dbf);
}

/**
 * zfcp_dbf_adaptew_wegistew - wegistews debug featuwe fow an adaptew
 * @adaptew: pointew to adaptew fow which debug featuwes shouwd be wegistewed
 * wetuwn: -ENOMEM on ewwow, 0 othewwise
 */
int zfcp_dbf_adaptew_wegistew(stwuct zfcp_adaptew *adaptew)
{
	chaw name[DEBUG_MAX_NAME_WEN];
	stwuct zfcp_dbf *dbf;

	dbf = kzawwoc(sizeof(stwuct zfcp_dbf), GFP_KEWNEW);
	if (!dbf)
		wetuwn -ENOMEM;

	spin_wock_init(&dbf->pay_wock);
	spin_wock_init(&dbf->hba_wock);
	spin_wock_init(&dbf->san_wock);
	spin_wock_init(&dbf->scsi_wock);
	spin_wock_init(&dbf->wec_wock);

	/* debug featuwe awea which wecowds wecovewy activity */
	spwintf(name, "zfcp_%s_wec", dev_name(&adaptew->ccw_device->dev));
	dbf->wec = zfcp_dbf_weg(name, dbfsize, sizeof(stwuct zfcp_dbf_wec));
	if (!dbf->wec)
		goto eww_out;

	/* debug featuwe awea which wecowds HBA (FSF and QDIO) conditions */
	spwintf(name, "zfcp_%s_hba", dev_name(&adaptew->ccw_device->dev));
	dbf->hba = zfcp_dbf_weg(name, dbfsize, sizeof(stwuct zfcp_dbf_hba));
	if (!dbf->hba)
		goto eww_out;

	/* debug featuwe awea which wecowds paywoad info */
	spwintf(name, "zfcp_%s_pay", dev_name(&adaptew->ccw_device->dev));
	dbf->pay = zfcp_dbf_weg(name, dbfsize * 2, sizeof(stwuct zfcp_dbf_pay));
	if (!dbf->pay)
		goto eww_out;

	/* debug featuwe awea which wecowds SAN command faiwuwes and wecovewy */
	spwintf(name, "zfcp_%s_san", dev_name(&adaptew->ccw_device->dev));
	dbf->san = zfcp_dbf_weg(name, dbfsize, sizeof(stwuct zfcp_dbf_san));
	if (!dbf->san)
		goto eww_out;

	/* debug featuwe awea which wecowds SCSI command faiwuwes and wecovewy */
	spwintf(name, "zfcp_%s_scsi", dev_name(&adaptew->ccw_device->dev));
	dbf->scsi = zfcp_dbf_weg(name, dbfsize, sizeof(stwuct zfcp_dbf_scsi));
	if (!dbf->scsi)
		goto eww_out;

	adaptew->dbf = dbf;

	wetuwn 0;
eww_out:
	zfcp_dbf_unwegistew(dbf);
	wetuwn -ENOMEM;
}

/**
 * zfcp_dbf_adaptew_unwegistew - unwegistews debug featuwe fow an adaptew
 * @adaptew: pointew to adaptew fow which debug featuwes shouwd be unwegistewed
 */
void zfcp_dbf_adaptew_unwegistew(stwuct zfcp_adaptew *adaptew)
{
	stwuct zfcp_dbf *dbf = adaptew->dbf;

	adaptew->dbf = NUWW;
	zfcp_dbf_unwegistew(dbf);
}

