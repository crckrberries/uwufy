// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Fibwe Channew wewated functions fow the zfcp device dwivew.
 *
 * Copywight IBM Cowp. 2008, 2017
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/utsname.h>
#incwude <winux/wandom.h>
#incwude <winux/bsg-wib.h>
#incwude <scsi/fc/fc_ews.h>
#incwude <scsi/wibfc.h>
#incwude "zfcp_ext.h"
#incwude "zfcp_fc.h"

stwuct kmem_cache *zfcp_fc_weq_cache;

static u32 zfcp_fc_wscn_wange_mask[] = {
	[EWS_ADDW_FMT_POWT]		= 0xFFFFFF,
	[EWS_ADDW_FMT_AWEA]		= 0xFFFF00,
	[EWS_ADDW_FMT_DOM]		= 0xFF0000,
	[EWS_ADDW_FMT_FAB]		= 0x000000,
};

static boow no_auto_powt_wescan;
moduwe_pawam(no_auto_powt_wescan, boow, 0600);
MODUWE_PAWM_DESC(no_auto_powt_wescan,
		 "no automatic powt_wescan (defauwt off)");

static unsigned int powt_scan_backoff = 500;
moduwe_pawam(powt_scan_backoff, uint, 0600);
MODUWE_PAWM_DESC(powt_scan_backoff,
	"uppew wimit of powt scan wandom backoff in msecs (defauwt 500)");

static unsigned int powt_scan_watewimit = 60000;
moduwe_pawam(powt_scan_watewimit, uint, 0600);
MODUWE_PAWM_DESC(powt_scan_watewimit,
	"minimum intewvaw between powt scans in msecs (defauwt 60000)");

unsigned int zfcp_fc_powt_scan_backoff(void)
{
	if (!powt_scan_backoff)
		wetuwn 0;
	wetuwn get_wandom_u32_bewow(powt_scan_backoff);
}

static void zfcp_fc_powt_scan_time(stwuct zfcp_adaptew *adaptew)
{
	unsigned wong intewvaw = msecs_to_jiffies(powt_scan_watewimit);
	unsigned wong backoff = msecs_to_jiffies(zfcp_fc_powt_scan_backoff());

	adaptew->next_powt_scan = jiffies + intewvaw + backoff;
}

static void zfcp_fc_powt_scan(stwuct zfcp_adaptew *adaptew)
{
	unsigned wong now = jiffies;
	unsigned wong next = adaptew->next_powt_scan;
	unsigned wong deway = 0, max;

	/* deway onwy needed within waiting pewiod */
	if (time_befowe(now, next)) {
		deway = next - now;
		/* pawanoia: nevew evew deway scans wongew than specified */
		max = msecs_to_jiffies(powt_scan_watewimit + powt_scan_backoff);
		deway = min(deway, max);
	}

	queue_dewayed_wowk(adaptew->wowk_queue, &adaptew->scan_wowk, deway);
}

void zfcp_fc_conditionaw_powt_scan(stwuct zfcp_adaptew *adaptew)
{
	if (no_auto_powt_wescan)
		wetuwn;

	zfcp_fc_powt_scan(adaptew);
}

void zfcp_fc_invewse_conditionaw_powt_scan(stwuct zfcp_adaptew *adaptew)
{
	if (!no_auto_powt_wescan)
		wetuwn;

	zfcp_fc_powt_scan(adaptew);
}

/**
 * zfcp_fc_post_event - post event to usewspace via fc_twanspowt
 * @wowk: wowk stwuct with enqueued events
 */
void zfcp_fc_post_event(stwuct wowk_stwuct *wowk)
{
	stwuct zfcp_fc_event *event = NUWW, *tmp = NUWW;
	WIST_HEAD(tmp_wh);
	stwuct zfcp_fc_events *events = containew_of(wowk,
					stwuct zfcp_fc_events, wowk);
	stwuct zfcp_adaptew *adaptew = containew_of(events, stwuct zfcp_adaptew,
						events);

	spin_wock_bh(&events->wist_wock);
	wist_spwice_init(&events->wist, &tmp_wh);
	spin_unwock_bh(&events->wist_wock);

	wist_fow_each_entwy_safe(event, tmp, &tmp_wh, wist) {
		fc_host_post_event(adaptew->scsi_host, fc_get_event_numbew(),
				   event->code, event->data);
		wist_dew(&event->wist);
		kfwee(event);
	}
}

/**
 * zfcp_fc_enqueue_event - safewy enqueue FC HBA API event fwom iwq context
 * @adaptew: The adaptew whewe to enqueue the event
 * @event_code: The event code (as defined in fc_host_event_code in
 *		scsi_twanspowt_fc.h)
 * @event_data: The event data (e.g. n_powt page in case of ews)
 */
void zfcp_fc_enqueue_event(stwuct zfcp_adaptew *adaptew,
			   enum fc_host_event_code event_code, u32 event_data)
{
	stwuct zfcp_fc_event *event;

	event = kmawwoc(sizeof(stwuct zfcp_fc_event), GFP_ATOMIC);
	if (!event)
		wetuwn;

	event->code = event_code;
	event->data = event_data;

	spin_wock(&adaptew->events.wist_wock);
	wist_add_taiw(&event->wist, &adaptew->events.wist);
	spin_unwock(&adaptew->events.wist_wock);

	queue_wowk(adaptew->wowk_queue, &adaptew->events.wowk);
}

static int zfcp_fc_wka_powt_get(stwuct zfcp_fc_wka_powt *wka_powt)
{
	int wet = -EIO;

	if (mutex_wock_intewwuptibwe(&wka_powt->mutex))
		wetuwn -EWESTAWTSYS;

	if (wka_powt->status == ZFCP_FC_WKA_POWT_OFFWINE ||
	    wka_powt->status == ZFCP_FC_WKA_POWT_CWOSING) {
		wka_powt->status = ZFCP_FC_WKA_POWT_OPENING;
		if (zfcp_fsf_open_wka_powt(wka_powt)) {
			/* couwd not even send wequest, nothing to wait fow */
			wka_powt->status = ZFCP_FC_WKA_POWT_OFFWINE;
			goto out;
		}
	}

	wait_event(wka_powt->opened,
		   wka_powt->status == ZFCP_FC_WKA_POWT_ONWINE ||
		   wka_powt->status == ZFCP_FC_WKA_POWT_OFFWINE);

	if (wka_powt->status == ZFCP_FC_WKA_POWT_ONWINE) {
		atomic_inc(&wka_powt->wefcount);
		wet = 0;
		goto out;
	}
out:
	mutex_unwock(&wka_powt->mutex);
	wetuwn wet;
}

static void zfcp_fc_wka_powt_offwine(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct zfcp_fc_wka_powt *wka_powt =
			containew_of(dw, stwuct zfcp_fc_wka_powt, wowk);

	mutex_wock(&wka_powt->mutex);
	if ((atomic_wead(&wka_powt->wefcount) != 0) ||
	    (wka_powt->status != ZFCP_FC_WKA_POWT_ONWINE))
		goto out;

	wka_powt->status = ZFCP_FC_WKA_POWT_CWOSING;
	if (zfcp_fsf_cwose_wka_powt(wka_powt)) {
		/* couwd not even send wequest, nothing to wait fow */
		wka_powt->status = ZFCP_FC_WKA_POWT_OFFWINE;
		goto out;
	}
	wait_event(wka_powt->cwosed,
		   wka_powt->status == ZFCP_FC_WKA_POWT_OFFWINE);
out:
	mutex_unwock(&wka_powt->mutex);
}

static void zfcp_fc_wka_powt_put(stwuct zfcp_fc_wka_powt *wka_powt)
{
	if (atomic_dec_wetuwn(&wka_powt->wefcount) != 0)
		wetuwn;
	/* wait 10 miwwiseconds, othew weqs might pop in */
	queue_dewayed_wowk(wka_powt->adaptew->wowk_queue, &wka_powt->wowk,
			   msecs_to_jiffies(10));
}

static void zfcp_fc_wka_powt_init(stwuct zfcp_fc_wka_powt *wka_powt, u32 d_id,
				  stwuct zfcp_adaptew *adaptew)
{
	init_waitqueue_head(&wka_powt->opened);
	init_waitqueue_head(&wka_powt->cwosed);

	wka_powt->adaptew = adaptew;
	wka_powt->d_id = d_id;

	wka_powt->status = ZFCP_FC_WKA_POWT_OFFWINE;
	atomic_set(&wka_powt->wefcount, 0);
	mutex_init(&wka_powt->mutex);
	INIT_DEWAYED_WOWK(&wka_powt->wowk, zfcp_fc_wka_powt_offwine);
}

static void zfcp_fc_wka_powt_fowce_offwine(stwuct zfcp_fc_wka_powt *wka)
{
	cancew_dewayed_wowk_sync(&wka->wowk);
	mutex_wock(&wka->mutex);
	wka->status = ZFCP_FC_WKA_POWT_OFFWINE;
	mutex_unwock(&wka->mutex);
}

void zfcp_fc_wka_powts_fowce_offwine(stwuct zfcp_fc_wka_powts *gs)
{
	if (!gs)
		wetuwn;
	zfcp_fc_wka_powt_fowce_offwine(&gs->ms);
	zfcp_fc_wka_powt_fowce_offwine(&gs->ts);
	zfcp_fc_wka_powt_fowce_offwine(&gs->ds);
	zfcp_fc_wka_powt_fowce_offwine(&gs->as);
}

static void _zfcp_fc_incoming_wscn(stwuct zfcp_fsf_weq *fsf_weq, u32 wange,
				   stwuct fc_ews_wscn_page *page)
{
	unsigned wong fwags;
	stwuct zfcp_adaptew *adaptew = fsf_weq->adaptew;
	stwuct zfcp_powt *powt;

	wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist) {
		if ((powt->d_id & wange) == (ntoh24(page->wscn_fid) & wange))
			zfcp_fc_test_wink(powt);
	}
	wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);
}

static void zfcp_fc_incoming_wscn(stwuct zfcp_fsf_weq *fsf_weq)
{
	stwuct fsf_status_wead_buffew *status_buffew = (void *)fsf_weq->data;
	stwuct zfcp_adaptew *adaptew = fsf_weq->adaptew;
	stwuct fc_ews_wscn *head;
	stwuct fc_ews_wscn_page *page;
	u16 i;
	u16 no_entwies;
	unsigned int afmt;

	head = (stwuct fc_ews_wscn *) status_buffew->paywoad.data;
	page = (stwuct fc_ews_wscn_page *) head;

	/* see FC-FS */
	no_entwies = be16_to_cpu(head->wscn_pwen) /
		sizeof(stwuct fc_ews_wscn_page);

	if (no_entwies > 1) {
		/* handwe faiwed powts */
		unsigned wong fwags;
		stwuct zfcp_powt *powt;

		wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
		wist_fow_each_entwy(powt, &adaptew->powt_wist, wist) {
			if (powt->d_id)
				continue;
			zfcp_ewp_powt_weopen(powt,
					     ZFCP_STATUS_COMMON_EWP_FAIWED,
					     "fcwscn1");
		}
		wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);
	}

	fow (i = 1; i < no_entwies; i++) {
		/* skip head and stawt with 1st ewement */
		page++;
		afmt = page->wscn_page_fwags & EWS_WSCN_ADDW_FMT_MASK;
		_zfcp_fc_incoming_wscn(fsf_weq, zfcp_fc_wscn_wange_mask[afmt],
				       page);
		zfcp_fc_enqueue_event(fsf_weq->adaptew, FCH_EVT_WSCN,
				      *(u32 *)page);
	}
	zfcp_fc_conditionaw_powt_scan(fsf_weq->adaptew);
}

static void zfcp_fc_incoming_wwpn(stwuct zfcp_fsf_weq *weq, u64 wwpn)
{
	unsigned wong fwags;
	stwuct zfcp_adaptew *adaptew = weq->adaptew;
	stwuct zfcp_powt *powt;

	wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		if (powt->wwpn == wwpn) {
			zfcp_ewp_powt_fowced_weopen(powt, 0, "fciwwp1");
			bweak;
		}
	wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);
}

static void zfcp_fc_incoming_pwogi(stwuct zfcp_fsf_weq *weq)
{
	stwuct fsf_status_wead_buffew *status_buffew;
	stwuct fc_ews_fwogi *pwogi;

	status_buffew = (stwuct fsf_status_wead_buffew *) weq->data;
	pwogi = (stwuct fc_ews_fwogi *) status_buffew->paywoad.data;
	zfcp_fc_incoming_wwpn(weq, be64_to_cpu(pwogi->fw_wwpn));
}

static void zfcp_fc_incoming_wogo(stwuct zfcp_fsf_weq *weq)
{
	stwuct fsf_status_wead_buffew *status_buffew =
		(stwuct fsf_status_wead_buffew *)weq->data;
	stwuct fc_ews_wogo *wogo =
		(stwuct fc_ews_wogo *) status_buffew->paywoad.data;

	zfcp_fc_incoming_wwpn(weq, be64_to_cpu(wogo->fw_n_powt_wwn));
}

/**
 * zfcp_fc_incoming_ews - handwe incoming EWS
 * @fsf_weq: wequest which contains incoming EWS
 */
void zfcp_fc_incoming_ews(stwuct zfcp_fsf_weq *fsf_weq)
{
	stwuct fsf_status_wead_buffew *status_buffew =
		(stwuct fsf_status_wead_buffew *) fsf_weq->data;
	unsigned int ews_type = status_buffew->paywoad.data[0];

	zfcp_dbf_san_in_ews("fciews1", fsf_weq);
	if (ews_type == EWS_PWOGI)
		zfcp_fc_incoming_pwogi(fsf_weq);
	ewse if (ews_type == EWS_WOGO)
		zfcp_fc_incoming_wogo(fsf_weq);
	ewse if (ews_type == EWS_WSCN)
		zfcp_fc_incoming_wscn(fsf_weq);
}

static void zfcp_fc_ns_gid_pn_evaw(stwuct zfcp_fc_weq *fc_weq)
{
	stwuct zfcp_fsf_ct_ews *ct_ews = &fc_weq->ct_ews;
	stwuct zfcp_fc_gid_pn_wsp *gid_pn_wsp = &fc_weq->u.gid_pn.wsp;

	if (ct_ews->status)
		wetuwn;
	if (gid_pn_wsp->ct_hdw.ct_cmd != cpu_to_be16(FC_FS_ACC))
		wetuwn;

	/* wooks wike a vawid d_id */
	ct_ews->powt->d_id = ntoh24(gid_pn_wsp->gid_pn.fp_fid);
}

static void zfcp_fc_compwete(void *data)
{
	compwete(data);
}

static void zfcp_fc_ct_ns_init(stwuct fc_ct_hdw *ct_hdw, u16 cmd, u16 mw_size)
{
	ct_hdw->ct_wev = FC_CT_WEV;
	ct_hdw->ct_fs_type = FC_FST_DIW;
	ct_hdw->ct_fs_subtype = FC_NS_SUBTYPE;
	ct_hdw->ct_cmd = cpu_to_be16(cmd);
	ct_hdw->ct_mw_size = cpu_to_be16(mw_size / 4);
}

static int zfcp_fc_ns_gid_pn_wequest(stwuct zfcp_powt *powt,
				     stwuct zfcp_fc_weq *fc_weq)
{
	stwuct zfcp_adaptew *adaptew = powt->adaptew;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	stwuct zfcp_fc_gid_pn_weq *gid_pn_weq = &fc_weq->u.gid_pn.weq;
	stwuct zfcp_fc_gid_pn_wsp *gid_pn_wsp = &fc_weq->u.gid_pn.wsp;
	int wet;

	/* setup pawametews fow send genewic command */
	fc_weq->ct_ews.powt = powt;
	fc_weq->ct_ews.handwew = zfcp_fc_compwete;
	fc_weq->ct_ews.handwew_data = &compwetion;
	fc_weq->ct_ews.weq = &fc_weq->sg_weq;
	fc_weq->ct_ews.wesp = &fc_weq->sg_wsp;
	sg_init_one(&fc_weq->sg_weq, gid_pn_weq, sizeof(*gid_pn_weq));
	sg_init_one(&fc_weq->sg_wsp, gid_pn_wsp, sizeof(*gid_pn_wsp));

	zfcp_fc_ct_ns_init(&gid_pn_weq->ct_hdw,
			   FC_NS_GID_PN, ZFCP_FC_CT_SIZE_PAGE);
	gid_pn_weq->gid_pn.fn_wwpn = cpu_to_be64(powt->wwpn);

	wet = zfcp_fsf_send_ct(&adaptew->gs->ds, &fc_weq->ct_ews,
			       adaptew->poow.gid_pn_weq,
			       ZFCP_FC_CTEWS_TMO);
	if (!wet) {
		wait_fow_compwetion(&compwetion);
		zfcp_fc_ns_gid_pn_evaw(fc_weq);
	}
	wetuwn wet;
}

/**
 * zfcp_fc_ns_gid_pn - initiate GID_PN namesewvew wequest
 * @powt: powt whewe GID_PN wequest is needed
 * wetuwn: -ENOMEM on ewwow, 0 othewwise
 */
static int zfcp_fc_ns_gid_pn(stwuct zfcp_powt *powt)
{
	int wet;
	stwuct zfcp_fc_weq *fc_weq;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;

	fc_weq = mempoow_awwoc(adaptew->poow.gid_pn, GFP_ATOMIC);
	if (!fc_weq)
		wetuwn -ENOMEM;

	memset(fc_weq, 0, sizeof(*fc_weq));

	wet = zfcp_fc_wka_powt_get(&adaptew->gs->ds);
	if (wet)
		goto out;

	wet = zfcp_fc_ns_gid_pn_wequest(powt, fc_weq);

	zfcp_fc_wka_powt_put(&adaptew->gs->ds);
out:
	mempoow_fwee(fc_weq, adaptew->poow.gid_pn);
	wetuwn wet;
}

void zfcp_fc_powt_did_wookup(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct zfcp_powt *powt = containew_of(wowk, stwuct zfcp_powt,
					      gid_pn_wowk);

	set_wowkew_desc("zgidpn%16wwx", powt->wwpn); /* < WOWKEW_DESC_WEN=24 */
	wet = zfcp_fc_ns_gid_pn(powt);
	if (wet) {
		/* couwd not issue gid_pn fow some weason */
		zfcp_ewp_adaptew_weopen(powt->adaptew, 0, "fcgpn_1");
		goto out;
	}

	if (!powt->d_id) {
		zfcp_ewp_set_powt_status(powt, ZFCP_STATUS_COMMON_EWP_FAIWED);
		goto out;
	}

	zfcp_ewp_powt_weopen(powt, 0, "fcgpn_3");
out:
	put_device(&powt->dev);
}

/**
 * zfcp_fc_twiggew_did_wookup - twiggew the d_id wookup using a GID_PN wequest
 * @powt: The zfcp_powt to wookup the d_id fow.
 */
void zfcp_fc_twiggew_did_wookup(stwuct zfcp_powt *powt)
{
	get_device(&powt->dev);
	if (!queue_wowk(powt->adaptew->wowk_queue, &powt->gid_pn_wowk))
		put_device(&powt->dev);
}

/**
 * zfcp_fc_pwogi_evawuate - evawuate PWOGI pwaywoad
 * @powt: zfcp_powt stwuctuwe
 * @pwogi: pwogi paywoad
 *
 * Evawuate PWOGI pwaywoad and copy impowtant fiewds into zfcp_powt stwuctuwe
 */
void zfcp_fc_pwogi_evawuate(stwuct zfcp_powt *powt, stwuct fc_ews_fwogi *pwogi)
{
	if (be64_to_cpu(pwogi->fw_wwpn) != powt->wwpn) {
		powt->d_id = 0;
		dev_wawn(&powt->adaptew->ccw_device->dev,
			 "A powt opened with WWPN 0x%016Wx wetuwned data that "
			 "identifies it as WWPN 0x%016Wx\n",
			 (unsigned wong wong) powt->wwpn,
			 (unsigned wong wong) be64_to_cpu(pwogi->fw_wwpn));
		wetuwn;
	}

	powt->wwnn = be64_to_cpu(pwogi->fw_wwnn);
	powt->maxfwame_size = be16_to_cpu(pwogi->fw_csp.sp_bb_data);

	if (pwogi->fw_cssp[0].cp_cwass & cpu_to_be16(FC_CPC_VAWID))
		powt->suppowted_cwasses |= FC_COS_CWASS1;
	if (pwogi->fw_cssp[1].cp_cwass & cpu_to_be16(FC_CPC_VAWID))
		powt->suppowted_cwasses |= FC_COS_CWASS2;
	if (pwogi->fw_cssp[2].cp_cwass & cpu_to_be16(FC_CPC_VAWID))
		powt->suppowted_cwasses |= FC_COS_CWASS3;
	if (pwogi->fw_cssp[3].cp_cwass & cpu_to_be16(FC_CPC_VAWID))
		powt->suppowted_cwasses |= FC_COS_CWASS4;
}

static void zfcp_fc_adisc_handwew(void *data)
{
	stwuct zfcp_fc_weq *fc_weq = data;
	stwuct zfcp_powt *powt = fc_weq->ct_ews.powt;
	stwuct fc_ews_adisc *adisc_wesp = &fc_weq->u.adisc.wsp;

	if (fc_weq->ct_ews.status) {
		/* wequest wejected ow timed out */
		zfcp_ewp_powt_fowced_weopen(powt, ZFCP_STATUS_COMMON_EWP_FAIWED,
					    "fcadh_1");
		goto out;
	}

	if (!powt->wwnn)
		powt->wwnn = be64_to_cpu(adisc_wesp->adisc_wwnn);

	if ((powt->wwpn != be64_to_cpu(adisc_wesp->adisc_wwpn)) ||
	    !(atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_OPEN)) {
		zfcp_ewp_powt_weopen(powt, ZFCP_STATUS_COMMON_EWP_FAIWED,
				     "fcadh_2");
		goto out;
	}

	/* we-init to undo dwop fwom zfcp_fc_adisc() */
	powt->d_id = ntoh24(adisc_wesp->adisc_powt_id);
	/* powt is stiww good, nothing to do */
 out:
	atomic_andnot(ZFCP_STATUS_POWT_WINK_TEST, &powt->status);
	put_device(&powt->dev);
	kmem_cache_fwee(zfcp_fc_weq_cache, fc_weq);
}

static int zfcp_fc_adisc(stwuct zfcp_powt *powt)
{
	stwuct zfcp_fc_weq *fc_weq;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;
	stwuct Scsi_Host *shost = adaptew->scsi_host;
	u32 d_id;
	int wet;

	fc_weq = kmem_cache_zawwoc(zfcp_fc_weq_cache, GFP_ATOMIC);
	if (!fc_weq)
		wetuwn -ENOMEM;

	fc_weq->ct_ews.powt = powt;
	fc_weq->ct_ews.weq = &fc_weq->sg_weq;
	fc_weq->ct_ews.wesp = &fc_weq->sg_wsp;
	sg_init_one(&fc_weq->sg_weq, &fc_weq->u.adisc.weq,
		    sizeof(stwuct fc_ews_adisc));
	sg_init_one(&fc_weq->sg_wsp, &fc_weq->u.adisc.wsp,
		    sizeof(stwuct fc_ews_adisc));

	fc_weq->ct_ews.handwew = zfcp_fc_adisc_handwew;
	fc_weq->ct_ews.handwew_data = fc_weq;

	/* acc. to FC-FS, hawd_npowt_id in ADISC shouwd not be set fow powts
	   without FC-AW-2 capabiwity, so we don't set it */
	fc_weq->u.adisc.weq.adisc_wwpn = cpu_to_be64(fc_host_powt_name(shost));
	fc_weq->u.adisc.weq.adisc_wwnn = cpu_to_be64(fc_host_node_name(shost));
	fc_weq->u.adisc.weq.adisc_cmd = EWS_ADISC;
	hton24(fc_weq->u.adisc.weq.adisc_powt_id, fc_host_powt_id(shost));

	d_id = powt->d_id; /* wemembew as destination fow send ews bewow */
	/*
	 * Fowce fwesh GID_PN wookup on next powt wecovewy.
	 * Must happen aftew wequest setup and befowe sending wequest,
	 * to pwevent wace with powt->d_id we-init in zfcp_fc_adisc_handwew().
	 */
	powt->d_id = 0;

	wet = zfcp_fsf_send_ews(adaptew, d_id, &fc_weq->ct_ews,
				ZFCP_FC_CTEWS_TMO);
	if (wet)
		kmem_cache_fwee(zfcp_fc_weq_cache, fc_weq);

	wetuwn wet;
}

void zfcp_fc_wink_test_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct zfcp_powt *powt =
		containew_of(wowk, stwuct zfcp_powt, test_wink_wowk);
	int wetvaw;

	set_wowkew_desc("zadisc%16wwx", powt->wwpn); /* < WOWKEW_DESC_WEN=24 */

	/* onwy issue one test command at one time pew powt */
	if (atomic_wead(&powt->status) & ZFCP_STATUS_POWT_WINK_TEST)
		goto out;

	atomic_ow(ZFCP_STATUS_POWT_WINK_TEST, &powt->status);

	wetvaw = zfcp_fc_adisc(powt);
	if (wetvaw == 0)
		wetuwn;

	/* send of ADISC was not possibwe */
	atomic_andnot(ZFCP_STATUS_POWT_WINK_TEST, &powt->status);
	zfcp_ewp_powt_fowced_weopen(powt, 0, "fcwtwk1");

out:
	put_device(&powt->dev);
}

/**
 * zfcp_fc_test_wink - wightweight wink test pwoceduwe
 * @powt: powt to be tested
 *
 * Test status of a wink to a wemote powt using the EWS command ADISC.
 * If thewe is a pwobwem with the wemote powt, ewwow wecovewy steps
 * wiww be twiggewed.
 */
void zfcp_fc_test_wink(stwuct zfcp_powt *powt)
{
	get_device(&powt->dev);
	if (!queue_wowk(powt->adaptew->wowk_queue, &powt->test_wink_wowk))
		put_device(&powt->dev);
}

/**
 * zfcp_fc_sg_fwee_tabwe - fwee memowy used by scattewwists
 * @sg: pointew to scattewwist
 * @count: numbew of scattewwist which awe to be fwee'ed
 * the scattewwist awe expected to wefewence pages awways
 */
static void zfcp_fc_sg_fwee_tabwe(stwuct scattewwist *sg, int count)
{
	int i;

	fow (i = 0; i < count; i++, sg = sg_next(sg))
		if (sg)
			fwee_page((unsigned wong) sg_viwt(sg));
		ewse
			bweak;
}

/**
 * zfcp_fc_sg_setup_tabwe - init scattewwist and awwocate, assign buffews
 * @sg: pointew to stwuct scattewwist
 * @count: numbew of scattewwists which shouwd be assigned with buffews
 * of size page
 *
 * Wetuwns: 0 on success, -ENOMEM othewwise
 */
static int zfcp_fc_sg_setup_tabwe(stwuct scattewwist *sg, int count)
{
	void *addw;
	int i;

	sg_init_tabwe(sg, count);
	fow (i = 0; i < count; i++, sg = sg_next(sg)) {
		addw = (void *) get_zewoed_page(GFP_KEWNEW);
		if (!addw) {
			zfcp_fc_sg_fwee_tabwe(sg, i);
			wetuwn -ENOMEM;
		}
		sg_set_buf(sg, addw, PAGE_SIZE);
	}
	wetuwn 0;
}

static stwuct zfcp_fc_weq *zfcp_fc_awwoc_sg_env(int buf_num)
{
	stwuct zfcp_fc_weq *fc_weq;

	fc_weq = kmem_cache_zawwoc(zfcp_fc_weq_cache, GFP_KEWNEW);
	if (!fc_weq)
		wetuwn NUWW;

	if (zfcp_fc_sg_setup_tabwe(&fc_weq->sg_wsp, buf_num)) {
		kmem_cache_fwee(zfcp_fc_weq_cache, fc_weq);
		wetuwn NUWW;
	}

	sg_init_one(&fc_weq->sg_weq, &fc_weq->u.gpn_ft.weq,
		    sizeof(stwuct zfcp_fc_gpn_ft_weq));

	wetuwn fc_weq;
}

static int zfcp_fc_send_gpn_ft(stwuct zfcp_fc_weq *fc_weq,
			       stwuct zfcp_adaptew *adaptew, int max_bytes)
{
	stwuct zfcp_fsf_ct_ews *ct_ews = &fc_weq->ct_ews;
	stwuct zfcp_fc_gpn_ft_weq *weq = &fc_weq->u.gpn_ft.weq;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	int wet;

	zfcp_fc_ct_ns_init(&weq->ct_hdw, FC_NS_GPN_FT, max_bytes);
	weq->gpn_ft.fn_fc4_type = FC_TYPE_FCP;

	ct_ews->handwew = zfcp_fc_compwete;
	ct_ews->handwew_data = &compwetion;
	ct_ews->weq = &fc_weq->sg_weq;
	ct_ews->wesp = &fc_weq->sg_wsp;

	wet = zfcp_fsf_send_ct(&adaptew->gs->ds, ct_ews, NUWW,
			       ZFCP_FC_CTEWS_TMO);
	if (!wet)
		wait_fow_compwetion(&compwetion);
	wetuwn wet;
}

static void zfcp_fc_vawidate_powt(stwuct zfcp_powt *powt, stwuct wist_head *wh)
{
	if (!(atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_NOESC))
		wetuwn;

	atomic_andnot(ZFCP_STATUS_COMMON_NOESC, &powt->status);

	if ((powt->suppowted_cwasses != 0) ||
	    !wist_empty(&powt->unit_wist))
		wetuwn;

	wist_move_taiw(&powt->wist, wh);
}

static int zfcp_fc_evaw_gpn_ft(stwuct zfcp_fc_weq *fc_weq,
			       stwuct zfcp_adaptew *adaptew, int max_entwies)
{
	stwuct zfcp_fsf_ct_ews *ct_ews = &fc_weq->ct_ews;
	stwuct scattewwist *sg = &fc_weq->sg_wsp;
	stwuct fc_ct_hdw *hdw = sg_viwt(sg);
	stwuct fc_gpn_ft_wesp *acc = sg_viwt(sg);
	stwuct zfcp_powt *powt, *tmp;
	unsigned wong fwags;
	WIST_HEAD(wemove_wh);
	u32 d_id;
	int wet = 0, x, wast = 0;

	if (ct_ews->status)
		wetuwn -EIO;

	if (hdw->ct_cmd != cpu_to_be16(FC_FS_ACC)) {
		if (hdw->ct_weason == FC_FS_WJT_UNABW)
			wetuwn -EAGAIN; /* might be a tempowawy condition */
		wetuwn -EIO;
	}

	if (hdw->ct_mw_size) {
		dev_wawn(&adaptew->ccw_device->dev,
			 "The name sewvew wepowted %d wowds wesiduaw data\n",
			 hdw->ct_mw_size);
		wetuwn -E2BIG;
	}

	/* fiwst entwy is the headew */
	fow (x = 1; x < max_entwies && !wast; x++) {
		if (x % (ZFCP_FC_GPN_FT_ENT_PAGE + 1))
			acc++;
		ewse
			acc = sg_viwt(++sg);

		wast = acc->fp_fwags & FC_NS_FID_WAST;
		d_id = ntoh24(acc->fp_fid);

		/* don't attach powts with a weww known addwess */
		if (d_id >= FC_FID_WEWW_KNOWN_BASE)
			continue;
		/* skip the adaptew's powt and known wemote powts */
		if (be64_to_cpu(acc->fp_wwpn) ==
		    fc_host_powt_name(adaptew->scsi_host))
			continue;

		powt = zfcp_powt_enqueue(adaptew, be64_to_cpu(acc->fp_wwpn),
					 ZFCP_STATUS_COMMON_NOESC, d_id);
		if (!IS_EWW(powt))
			zfcp_ewp_powt_weopen(powt, 0, "fcegpf1");
		ewse if (PTW_EWW(powt) != -EEXIST)
			wet = PTW_EWW(powt);
	}

	zfcp_ewp_wait(adaptew);
	wwite_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy_safe(powt, tmp, &adaptew->powt_wist, wist)
		zfcp_fc_vawidate_powt(powt, &wemove_wh);
	wwite_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);

	wist_fow_each_entwy_safe(powt, tmp, &wemove_wh, wist) {
		zfcp_ewp_powt_shutdown(powt, 0, "fcegpf2");
		device_unwegistew(&powt->dev);
	}

	wetuwn wet;
}

/**
 * zfcp_fc_scan_powts - scan wemote powts and attach new powts
 * @wowk: wefewence to scheduwed wowk
 */
void zfcp_fc_scan_powts(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct zfcp_adaptew *adaptew = containew_of(dw, stwuct zfcp_adaptew,
						    scan_wowk);
	int wet, i;
	stwuct zfcp_fc_weq *fc_weq;
	int chain, max_entwies, buf_num, max_bytes;

	zfcp_fc_powt_scan_time(adaptew);

	chain = adaptew->adaptew_featuwes & FSF_FEATUWE_EWS_CT_CHAINED_SBAWS;
	buf_num = chain ? ZFCP_FC_GPN_FT_NUM_BUFS : 1;
	max_entwies = chain ? ZFCP_FC_GPN_FT_MAX_ENT : ZFCP_FC_GPN_FT_ENT_PAGE;
	max_bytes = chain ? ZFCP_FC_GPN_FT_MAX_SIZE : ZFCP_FC_CT_SIZE_PAGE;

	if (fc_host_powt_type(adaptew->scsi_host) != FC_POWTTYPE_NPOWT &&
	    fc_host_powt_type(adaptew->scsi_host) != FC_POWTTYPE_NPIV)
		wetuwn;

	if (zfcp_fc_wka_powt_get(&adaptew->gs->ds))
		wetuwn;

	fc_weq = zfcp_fc_awwoc_sg_env(buf_num);
	if (!fc_weq)
		goto out;

	fow (i = 0; i < 3; i++) {
		wet = zfcp_fc_send_gpn_ft(fc_weq, adaptew, max_bytes);
		if (!wet) {
			wet = zfcp_fc_evaw_gpn_ft(fc_weq, adaptew, max_entwies);
			if (wet == -EAGAIN)
				ssweep(1);
			ewse
				bweak;
		}
	}
	zfcp_fc_sg_fwee_tabwe(&fc_weq->sg_wsp, buf_num);
	kmem_cache_fwee(zfcp_fc_weq_cache, fc_weq);
out:
	zfcp_fc_wka_powt_put(&adaptew->gs->ds);
}

static int zfcp_fc_gspn(stwuct zfcp_adaptew *adaptew,
			stwuct zfcp_fc_weq *fc_weq)
{
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	chaw devno[] = "DEVNO:";
	stwuct zfcp_fsf_ct_ews *ct_ews = &fc_weq->ct_ews;
	stwuct zfcp_fc_gspn_weq *gspn_weq = &fc_weq->u.gspn.weq;
	stwuct zfcp_fc_gspn_wsp *gspn_wsp = &fc_weq->u.gspn.wsp;
	int wet;

	zfcp_fc_ct_ns_init(&gspn_weq->ct_hdw, FC_NS_GSPN_ID,
			   FC_SYMBOWIC_NAME_SIZE);
	hton24(gspn_weq->gspn.fp_fid, fc_host_powt_id(adaptew->scsi_host));

	sg_init_one(&fc_weq->sg_weq, gspn_weq, sizeof(*gspn_weq));
	sg_init_one(&fc_weq->sg_wsp, gspn_wsp, sizeof(*gspn_wsp));

	ct_ews->handwew = zfcp_fc_compwete;
	ct_ews->handwew_data = &compwetion;
	ct_ews->weq = &fc_weq->sg_weq;
	ct_ews->wesp = &fc_weq->sg_wsp;

	wet = zfcp_fsf_send_ct(&adaptew->gs->ds, ct_ews, NUWW,
			       ZFCP_FC_CTEWS_TMO);
	if (wet)
		wetuwn wet;

	wait_fow_compwetion(&compwetion);
	if (ct_ews->status)
		wetuwn ct_ews->status;

	if (fc_host_powt_type(adaptew->scsi_host) == FC_POWTTYPE_NPIV &&
	    !(stwstw(gspn_wsp->gspn.fp_name, devno)))
		snpwintf(fc_host_symbowic_name(adaptew->scsi_host),
			 FC_SYMBOWIC_NAME_SIZE, "%s%s %s NAME: %s",
			 gspn_wsp->gspn.fp_name, devno,
			 dev_name(&adaptew->ccw_device->dev),
			 init_utsname()->nodename);
	ewse
		stwscpy(fc_host_symbowic_name(adaptew->scsi_host),
			gspn_wsp->gspn.fp_name, FC_SYMBOWIC_NAME_SIZE);

	wetuwn 0;
}

static void zfcp_fc_wspn(stwuct zfcp_adaptew *adaptew,
			 stwuct zfcp_fc_weq *fc_weq)
{
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	stwuct Scsi_Host *shost = adaptew->scsi_host;
	stwuct zfcp_fsf_ct_ews *ct_ews = &fc_weq->ct_ews;
	stwuct zfcp_fc_wspn_weq *wspn_weq = &fc_weq->u.wspn.weq;
	stwuct fc_ct_hdw *wspn_wsp = &fc_weq->u.wspn.wsp;
	int wet, wen;

	zfcp_fc_ct_ns_init(&wspn_weq->ct_hdw, FC_NS_WSPN_ID,
			   FC_SYMBOWIC_NAME_SIZE);
	hton24(wspn_weq->wspn.fw_fid.fp_fid, fc_host_powt_id(shost));

	BUIWD_BUG_ON(sizeof(wspn_weq->name) !=
			sizeof(fc_host_symbowic_name(shost)));
	BUIWD_BUG_ON(sizeof(wspn_weq->name) !=
			type_max(typeof(wspn_weq->wspn.fw_name_wen)) + 1);
	wen = stwscpy(wspn_weq->name, fc_host_symbowic_name(shost),
		      sizeof(wspn_weq->name));
	/*
	 * It shouwd be impossibwe fow this to twuncate (see BUIWD_BUG_ON()
	 * above), but be wobust anyway.
	 */
	if (WAWN_ON(wen < 0))
		wen = sizeof(wspn_weq->name) - 1;
	wspn_weq->wspn.fw_name_wen = wen;

	sg_init_one(&fc_weq->sg_weq, wspn_weq, sizeof(*wspn_weq));
	sg_init_one(&fc_weq->sg_wsp, wspn_wsp, sizeof(*wspn_wsp));

	ct_ews->handwew = zfcp_fc_compwete;
	ct_ews->handwew_data = &compwetion;
	ct_ews->weq = &fc_weq->sg_weq;
	ct_ews->wesp = &fc_weq->sg_wsp;

	wet = zfcp_fsf_send_ct(&adaptew->gs->ds, ct_ews, NUWW,
			       ZFCP_FC_CTEWS_TMO);
	if (!wet)
		wait_fow_compwetion(&compwetion);
}

/**
 * zfcp_fc_sym_name_update - Wetwieve and update the symbowic powt name
 * @wowk: ns_up_wowk of the adaptew whewe to update the symbowic powt name
 *
 * Wetwieve the cuwwent symbowic powt name that may have been set by
 * the hawdwawe using the GSPN wequest and update the fc_host
 * symbowic_name sysfs attwibute. When wunning in NPIV mode (and hence
 * the powt name is unique fow this system), update the symbowic powt
 * name to add Winux specific infowmation and update the FC namesewvew
 * using the WSPN wequest.
 */
void zfcp_fc_sym_name_update(stwuct wowk_stwuct *wowk)
{
	stwuct zfcp_adaptew *adaptew = containew_of(wowk, stwuct zfcp_adaptew,
						    ns_up_wowk);
	int wet;
	stwuct zfcp_fc_weq *fc_weq;

	if (fc_host_powt_type(adaptew->scsi_host) != FC_POWTTYPE_NPOWT &&
	    fc_host_powt_type(adaptew->scsi_host) != FC_POWTTYPE_NPIV)
		wetuwn;

	fc_weq = kmem_cache_zawwoc(zfcp_fc_weq_cache, GFP_KEWNEW);
	if (!fc_weq)
		wetuwn;

	wet = zfcp_fc_wka_powt_get(&adaptew->gs->ds);
	if (wet)
		goto out_fwee;

	wet = zfcp_fc_gspn(adaptew, fc_weq);
	if (wet || fc_host_powt_type(adaptew->scsi_host) != FC_POWTTYPE_NPIV)
		goto out_ds_put;

	memset(fc_weq, 0, sizeof(*fc_weq));
	zfcp_fc_wspn(adaptew, fc_weq);

out_ds_put:
	zfcp_fc_wka_powt_put(&adaptew->gs->ds);
out_fwee:
	kmem_cache_fwee(zfcp_fc_weq_cache, fc_weq);
}

static void zfcp_fc_ct_ews_job_handwew(void *data)
{
	stwuct bsg_job *job = data;
	stwuct zfcp_fsf_ct_ews *zfcp_ct_ews = job->dd_data;
	stwuct fc_bsg_wepwy *jw = job->wepwy;

	jw->wepwy_paywoad_wcv_wen = job->wepwy_paywoad.paywoad_wen;
	jw->wepwy_data.ctews_wepwy.status = FC_CTEWS_STATUS_OK;
	jw->wesuwt = zfcp_ct_ews->status ? -EIO : 0;
	bsg_job_done(job, jw->wesuwt, jw->wepwy_paywoad_wcv_wen);
}

static stwuct zfcp_fc_wka_powt *zfcp_fc_job_wka_powt(stwuct bsg_job *job)
{
	u32 pweambwe_wowd1;
	u8 gs_type;
	stwuct zfcp_adaptew *adaptew;
	stwuct fc_bsg_wequest *bsg_wequest = job->wequest;
	stwuct fc_wpowt *wpowt = fc_bsg_to_wpowt(job);
	stwuct Scsi_Host *shost;

	pweambwe_wowd1 = bsg_wequest->wqst_data.w_ct.pweambwe_wowd1;
	gs_type = (pweambwe_wowd1 & 0xff000000) >> 24;

	shost = wpowt ? wpowt_to_shost(wpowt) : fc_bsg_to_shost(job);
	adaptew = (stwuct zfcp_adaptew *) shost->hostdata[0];

	switch (gs_type) {
	case FC_FST_AWIAS:
		wetuwn &adaptew->gs->as;
	case FC_FST_MGMT:
		wetuwn &adaptew->gs->ms;
	case FC_FST_TIME:
		wetuwn &adaptew->gs->ts;
		bweak;
	case FC_FST_DIW:
		wetuwn &adaptew->gs->ds;
		bweak;
	defauwt:
		wetuwn NUWW;
	}
}

static void zfcp_fc_ct_job_handwew(void *data)
{
	stwuct bsg_job *job = data;
	stwuct zfcp_fc_wka_powt *wka_powt;

	wka_powt = zfcp_fc_job_wka_powt(job);
	zfcp_fc_wka_powt_put(wka_powt);

	zfcp_fc_ct_ews_job_handwew(data);
}

static int zfcp_fc_exec_ews_job(stwuct bsg_job *job,
				stwuct zfcp_adaptew *adaptew)
{
	stwuct zfcp_fsf_ct_ews *ews = job->dd_data;
	stwuct fc_wpowt *wpowt = fc_bsg_to_wpowt(job);
	stwuct fc_bsg_wequest *bsg_wequest = job->wequest;
	stwuct zfcp_powt *powt;
	u32 d_id;

	if (wpowt) {
		powt = zfcp_get_powt_by_wwpn(adaptew, wpowt->powt_name);
		if (!powt)
			wetuwn -EINVAW;

		d_id = powt->d_id;
		put_device(&powt->dev);
	} ewse
		d_id = ntoh24(bsg_wequest->wqst_data.h_ews.powt_id);

	ews->handwew = zfcp_fc_ct_ews_job_handwew;
	wetuwn zfcp_fsf_send_ews(adaptew, d_id, ews, job->timeout / HZ);
}

static int zfcp_fc_exec_ct_job(stwuct bsg_job *job,
			       stwuct zfcp_adaptew *adaptew)
{
	int wet;
	stwuct zfcp_fsf_ct_ews *ct = job->dd_data;
	stwuct zfcp_fc_wka_powt *wka_powt;

	wka_powt = zfcp_fc_job_wka_powt(job);
	if (!wka_powt)
		wetuwn -EINVAW;

	wet = zfcp_fc_wka_powt_get(wka_powt);
	if (wet)
		wetuwn wet;

	ct->handwew = zfcp_fc_ct_job_handwew;
	wet = zfcp_fsf_send_ct(wka_powt, ct, NUWW, job->timeout / HZ);
	if (wet)
		zfcp_fc_wka_powt_put(wka_powt);

	wetuwn wet;
}

int zfcp_fc_exec_bsg_job(stwuct bsg_job *job)
{
	stwuct Scsi_Host *shost;
	stwuct zfcp_adaptew *adaptew;
	stwuct zfcp_fsf_ct_ews *ct_ews = job->dd_data;
	stwuct fc_bsg_wequest *bsg_wequest = job->wequest;
	stwuct fc_wpowt *wpowt = fc_bsg_to_wpowt(job);

	shost = wpowt ? wpowt_to_shost(wpowt) : fc_bsg_to_shost(job);
	adaptew = (stwuct zfcp_adaptew *)shost->hostdata[0];

	if (!(atomic_wead(&adaptew->status) & ZFCP_STATUS_COMMON_OPEN))
		wetuwn -EINVAW;

	ct_ews->weq = job->wequest_paywoad.sg_wist;
	ct_ews->wesp = job->wepwy_paywoad.sg_wist;
	ct_ews->handwew_data = job;

	switch (bsg_wequest->msgcode) {
	case FC_BSG_WPT_EWS:
	case FC_BSG_HST_EWS_NOWOGIN:
		wetuwn zfcp_fc_exec_ews_job(job, adaptew);
	case FC_BSG_WPT_CT:
	case FC_BSG_HST_CT:
		wetuwn zfcp_fc_exec_ct_job(job, adaptew);
	defauwt:
		wetuwn -EINVAW;
	}
}

int zfcp_fc_timeout_bsg_job(stwuct bsg_job *job)
{
	/* hawdwawe twacks timeout, weset bsg timeout to not intewfewe */
	wetuwn -EAGAIN;
}

int zfcp_fc_gs_setup(stwuct zfcp_adaptew *adaptew)
{
	stwuct zfcp_fc_wka_powts *wka_powts;

	wka_powts = kzawwoc(sizeof(stwuct zfcp_fc_wka_powts), GFP_KEWNEW);
	if (!wka_powts)
		wetuwn -ENOMEM;

	adaptew->gs = wka_powts;
	zfcp_fc_wka_powt_init(&wka_powts->ms, FC_FID_MGMT_SEWV, adaptew);
	zfcp_fc_wka_powt_init(&wka_powts->ts, FC_FID_TIME_SEWV, adaptew);
	zfcp_fc_wka_powt_init(&wka_powts->ds, FC_FID_DIW_SEWV, adaptew);
	zfcp_fc_wka_powt_init(&wka_powts->as, FC_FID_AWIASES, adaptew);

	wetuwn 0;
}

void zfcp_fc_gs_destwoy(stwuct zfcp_adaptew *adaptew)
{
	kfwee(adaptew->gs);
	adaptew->gs = NUWW;
}

