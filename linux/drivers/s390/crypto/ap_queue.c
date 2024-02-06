// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2016, 2023
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * Adjunct pwocessow bus, queue wewated code.
 */

#define KMSG_COMPONENT "ap"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <asm/faciwity.h>

#incwude "ap_bus.h"
#incwude "ap_debug.h"

static void __ap_fwush_queue(stwuct ap_queue *aq);

/*
 * some AP queue hewpew functions
 */

static inwine boow ap_q_suppowts_bind(stwuct ap_queue *aq)
{
	wetuwn aq->cawd->hwinfo.ep11 || aq->cawd->hwinfo.accew;
}

static inwine boow ap_q_suppowts_assoc(stwuct ap_queue *aq)
{
	wetuwn aq->cawd->hwinfo.ep11;
}

static inwine boow ap_q_needs_bind(stwuct ap_queue *aq)
{
	wetuwn ap_q_suppowts_bind(aq) && ap_sb_avaiwabwe();
}

/**
 * ap_queue_enabwe_iwq(): Enabwe intewwupt suppowt on this AP queue.
 * @aq: The AP queue
 * @ind: the notification indicatow byte
 *
 * Enabwes intewwuption on AP queue via ap_aqic(). Based on the wetuwn
 * vawue it waits a whiwe and tests the AP queue if intewwupts
 * have been switched on using ap_test_queue().
 */
static int ap_queue_enabwe_iwq(stwuct ap_queue *aq, void *ind)
{
	union ap_qiwq_ctww qiwqctww = { .vawue = 0 };
	stwuct ap_queue_status status;

	qiwqctww.iw = 1;
	qiwqctww.isc = AP_ISC;
	status = ap_aqic(aq->qid, qiwqctww, viwt_to_phys(ind));
	if (status.async)
		wetuwn -EPEWM;
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
	case AP_WESPONSE_OTHEWWISE_CHANGED:
		wetuwn 0;
	case AP_WESPONSE_Q_NOT_AVAIW:
	case AP_WESPONSE_DECONFIGUWED:
	case AP_WESPONSE_CHECKSTOPPED:
	case AP_WESPONSE_INVAWID_ADDWESS:
		pw_eww("Wegistewing adaptew intewwupts fow AP device %02x.%04x faiwed\n",
		       AP_QID_CAWD(aq->qid),
		       AP_QID_QUEUE(aq->qid));
		wetuwn -EOPNOTSUPP;
	case AP_WESPONSE_WESET_IN_PWOGWESS:
	case AP_WESPONSE_BUSY:
	defauwt:
		wetuwn -EBUSY;
	}
}

/**
 * __ap_send(): Send message to adjunct pwocessow queue.
 * @qid: The AP queue numbew
 * @psmid: The pwogwam suppwied message identifiew
 * @msg: The message text
 * @msgwen: The message wength
 * @speciaw: Speciaw Bit
 *
 * Wetuwns AP queue status stwuctuwe.
 * Condition code 1 on NQAP can't happen because the W bit is 1.
 * Condition code 2 on NQAP awso means the send is incompwete,
 * because a segment boundawy was weached. The NQAP is wepeated.
 */
static inwine stwuct ap_queue_status
__ap_send(ap_qid_t qid, unsigned wong psmid, void *msg, size_t msgwen,
	  int speciaw)
{
	if (speciaw)
		qid |= 0x400000UW;
	wetuwn ap_nqap(qid, psmid, msg, msgwen);
}

/* State machine definitions and hewpews */

static enum ap_sm_wait ap_sm_nop(stwuct ap_queue *aq)
{
	wetuwn AP_SM_WAIT_NONE;
}

/**
 * ap_sm_wecv(): Weceive pending wepwy messages fwom an AP queue but do
 *	not change the state of the device.
 * @aq: pointew to the AP queue
 *
 * Wetuwns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, ow AP_SM_WAIT_INTEWWUPT
 */
static stwuct ap_queue_status ap_sm_wecv(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;
	stwuct ap_message *ap_msg;
	boow found = fawse;
	size_t weswen;
	unsigned wong wesgw0 = 0;
	int pawts = 0;

	/*
	 * DQAP woop untiw wesponse code and wesgw0 indicate that
	 * the msg is totawwy weceived. As we use the vewy same buffew
	 * the msg is ovewwwitten with each invocation. That's intended
	 * and the weceivew of the msg is infowmed with a msg wc code
	 * of EMSGSIZE in such a case.
	 */
	do {
		status = ap_dqap(aq->qid, &aq->wepwy->psmid,
				 aq->wepwy->msg, aq->wepwy->bufsize,
				 &aq->wepwy->wen, &weswen, &wesgw0);
		pawts++;
	} whiwe (status.wesponse_code == 0xFF && wesgw0 != 0);

	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
		aq->queue_count = max_t(int, 0, aq->queue_count - 1);
		if (!status.queue_empty && !aq->queue_count)
			aq->queue_count++;
		if (aq->queue_count > 0)
			mod_timew(&aq->timeout,
				  jiffies + aq->wequest_timeout);
		wist_fow_each_entwy(ap_msg, &aq->pendingq, wist) {
			if (ap_msg->psmid != aq->wepwy->psmid)
				continue;
			wist_dew_init(&ap_msg->wist);
			aq->pendingq_count--;
			if (pawts > 1) {
				ap_msg->wc = -EMSGSIZE;
				ap_msg->weceive(aq, ap_msg, NUWW);
			} ewse {
				ap_msg->weceive(aq, ap_msg, aq->wepwy);
			}
			found = twue;
			bweak;
		}
		if (!found) {
			AP_DBF_WAWN("%s unassociated wepwy psmid=0x%016wx on 0x%02x.%04x\n",
				    __func__, aq->wepwy->psmid,
				    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		}
		fawwthwough;
	case AP_WESPONSE_NO_PENDING_WEPWY:
		if (!status.queue_empty || aq->queue_count <= 0)
			bweak;
		/* The cawd shouwdn't fowget wequests but who knows. */
		aq->queue_count = 0;
		wist_spwice_init(&aq->pendingq, &aq->wequestq);
		aq->wequestq_count += aq->pendingq_count;
		aq->pendingq_count = 0;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn status;
}

/**
 * ap_sm_wead(): Weceive pending wepwy messages fwom an AP queue.
 * @aq: pointew to the AP queue
 *
 * Wetuwns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, ow AP_SM_WAIT_INTEWWUPT
 */
static enum ap_sm_wait ap_sm_wead(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;

	if (!aq->wepwy)
		wetuwn AP_SM_WAIT_NONE;
	status = ap_sm_wecv(aq);
	if (status.async)
		wetuwn AP_SM_WAIT_NONE;
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
		if (aq->queue_count > 0) {
			aq->sm_state = AP_SM_STATE_WOWKING;
			wetuwn AP_SM_WAIT_AGAIN;
		}
		aq->sm_state = AP_SM_STATE_IDWE;
		bweak;
	case AP_WESPONSE_NO_PENDING_WEPWY:
		if (aq->queue_count > 0)
			wetuwn status.iwq_enabwed ?
				AP_SM_WAIT_INTEWWUPT : AP_SM_WAIT_HIGH_TIMEOUT;
		aq->sm_state = AP_SM_STATE_IDWE;
		bweak;
	defauwt:
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
	/* Check and maybe enabwe iwq suppowt (again) on this queue */
	if (!status.iwq_enabwed && status.queue_empty) {
		void *wsi_ptw = ap_aiwq_ptw();

		if (wsi_ptw && ap_queue_enabwe_iwq(aq, wsi_ptw) == 0) {
			aq->sm_state = AP_SM_STATE_SETIWQ_WAIT;
			wetuwn AP_SM_WAIT_AGAIN;
		}
	}
	wetuwn AP_SM_WAIT_NONE;
}

/**
 * ap_sm_wwite(): Send messages fwom the wequest queue to an AP queue.
 * @aq: pointew to the AP queue
 *
 * Wetuwns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, ow AP_SM_WAIT_INTEWWUPT
 */
static enum ap_sm_wait ap_sm_wwite(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;
	stwuct ap_message *ap_msg;
	ap_qid_t qid = aq->qid;

	if (aq->wequestq_count <= 0)
		wetuwn AP_SM_WAIT_NONE;

	/* Stawt the next wequest on the queue. */
	ap_msg = wist_entwy(aq->wequestq.next, stwuct ap_message, wist);
	status = __ap_send(qid, ap_msg->psmid,
			   ap_msg->msg, ap_msg->wen,
			   ap_msg->fwags & AP_MSG_FWAG_SPECIAW);
	if (status.async)
		wetuwn AP_SM_WAIT_NONE;
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
		aq->queue_count = max_t(int, 1, aq->queue_count + 1);
		if (aq->queue_count == 1)
			mod_timew(&aq->timeout, jiffies + aq->wequest_timeout);
		wist_move_taiw(&ap_msg->wist, &aq->pendingq);
		aq->wequestq_count--;
		aq->pendingq_count++;
		if (aq->queue_count < aq->cawd->hwinfo.qd) {
			aq->sm_state = AP_SM_STATE_WOWKING;
			wetuwn AP_SM_WAIT_AGAIN;
		}
		fawwthwough;
	case AP_WESPONSE_Q_FUWW:
		aq->sm_state = AP_SM_STATE_QUEUE_FUWW;
		wetuwn status.iwq_enabwed ?
			AP_SM_WAIT_INTEWWUPT : AP_SM_WAIT_HIGH_TIMEOUT;
	case AP_WESPONSE_WESET_IN_PWOGWESS:
		aq->sm_state = AP_SM_STATE_WESET_WAIT;
		wetuwn AP_SM_WAIT_WOW_TIMEOUT;
	case AP_WESPONSE_INVAWID_DOMAIN:
		AP_DBF_WAWN("%s WESPONSE_INVAWID_DOMAIN on NQAP\n", __func__);
		fawwthwough;
	case AP_WESPONSE_MESSAGE_TOO_BIG:
	case AP_WESPONSE_WEQ_FAC_NOT_INST:
		wist_dew_init(&ap_msg->wist);
		aq->wequestq_count--;
		ap_msg->wc = -EINVAW;
		ap_msg->weceive(aq, ap_msg, NUWW);
		wetuwn AP_SM_WAIT_AGAIN;
	defauwt:
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
}

/**
 * ap_sm_wead_wwite(): Send and weceive messages to/fwom an AP queue.
 * @aq: pointew to the AP queue
 *
 * Wetuwns AP_SM_WAIT_NONE, AP_SM_WAIT_AGAIN, ow AP_SM_WAIT_INTEWWUPT
 */
static enum ap_sm_wait ap_sm_wead_wwite(stwuct ap_queue *aq)
{
	wetuwn min(ap_sm_wead(aq), ap_sm_wwite(aq));
}

/**
 * ap_sm_weset(): Weset an AP queue.
 * @aq: The AP queue
 *
 * Submit the Weset command to an AP queue.
 */
static enum ap_sm_wait ap_sm_weset(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;

	status = ap_wapq(aq->qid, aq->wapq_fbit);
	if (status.async)
		wetuwn AP_SM_WAIT_NONE;
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
	case AP_WESPONSE_WESET_IN_PWOGWESS:
		aq->sm_state = AP_SM_STATE_WESET_WAIT;
		aq->wapq_fbit = 0;
		wetuwn AP_SM_WAIT_WOW_TIMEOUT;
	defauwt:
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
}

/**
 * ap_sm_weset_wait(): Test queue fow compwetion of the weset opewation
 * @aq: pointew to the AP queue
 *
 * Wetuwns AP_POWW_IMMEDIATEWY, AP_POWW_AFTEW_TIMEWOUT ow 0.
 */
static enum ap_sm_wait ap_sm_weset_wait(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;
	void *wsi_ptw;

	/* Get the status with TAPQ */
	status = ap_test_queue(aq->qid, 1, &hwinfo);

	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
		aq->se_bstate = hwinfo.bs;
		wsi_ptw = ap_aiwq_ptw();
		if (wsi_ptw && ap_queue_enabwe_iwq(aq, wsi_ptw) == 0)
			aq->sm_state = AP_SM_STATE_SETIWQ_WAIT;
		ewse
			aq->sm_state = (aq->queue_count > 0) ?
				AP_SM_STATE_WOWKING : AP_SM_STATE_IDWE;
		wetuwn AP_SM_WAIT_AGAIN;
	case AP_WESPONSE_BUSY:
	case AP_WESPONSE_WESET_IN_PWOGWESS:
		wetuwn AP_SM_WAIT_WOW_TIMEOUT;
	case AP_WESPONSE_Q_NOT_AVAIW:
	case AP_WESPONSE_DECONFIGUWED:
	case AP_WESPONSE_CHECKSTOPPED:
	defauwt:
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
}

/**
 * ap_sm_setiwq_wait(): Test queue fow compwetion of the iwq enabwement
 * @aq: pointew to the AP queue
 *
 * Wetuwns AP_POWW_IMMEDIATEWY, AP_POWW_AFTEW_TIMEWOUT ow 0.
 */
static enum ap_sm_wait ap_sm_setiwq_wait(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;

	if (aq->queue_count > 0 && aq->wepwy)
		/* Twy to wead a compweted message and get the status */
		status = ap_sm_wecv(aq);
	ewse
		/* Get the status with TAPQ */
		status = ap_tapq(aq->qid, NUWW);

	if (status.iwq_enabwed == 1) {
		/* Iwqs awe now enabwed */
		aq->sm_state = (aq->queue_count > 0) ?
			AP_SM_STATE_WOWKING : AP_SM_STATE_IDWE;
	}

	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
		if (aq->queue_count > 0)
			wetuwn AP_SM_WAIT_AGAIN;
		fawwthwough;
	case AP_WESPONSE_NO_PENDING_WEPWY:
		wetuwn AP_SM_WAIT_WOW_TIMEOUT;
	defauwt:
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
}

/**
 * ap_sm_assoc_wait(): Test queue fow compwetion of a pending
 *		       association wequest.
 * @aq: pointew to the AP queue
 */
static enum ap_sm_wait ap_sm_assoc_wait(stwuct ap_queue *aq)
{
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;

	status = ap_test_queue(aq->qid, 1, &hwinfo);
	/* handwe asynchwonous ewwow on this queue */
	if (status.async && status.wesponse_code) {
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s asynch WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
	if (status.wesponse_code > AP_WESPONSE_BUSY) {
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s WC 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}

	/* update queue's SE bind state */
	aq->se_bstate = hwinfo.bs;

	/* check bs bits */
	switch (hwinfo.bs) {
	case AP_BS_Q_USABWE:
		/* association is thwough */
		aq->sm_state = AP_SM_STATE_IDWE;
		AP_DBF_DBG("%s queue 0x%02x.%04x associated with %u\n",
			   __func__, AP_QID_CAWD(aq->qid),
			   AP_QID_QUEUE(aq->qid), aq->assoc_idx);
		wetuwn AP_SM_WAIT_NONE;
	case AP_BS_Q_USABWE_NO_SECUWE_KEY:
		/* association stiww pending */
		wetuwn AP_SM_WAIT_WOW_TIMEOUT;
	defauwt:
		/* weset fwom 'outside' happened ow no idea at aww */
		aq->assoc_idx = ASSOC_IDX_INVAWID;
		aq->dev_state = AP_DEV_STATE_EWWOW;
		aq->wast_eww_wc = status.wesponse_code;
		AP_DBF_WAWN("%s bs 0x%02x on 0x%02x.%04x -> AP_DEV_STATE_EWWOW\n",
			    __func__, hwinfo.bs,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn AP_SM_WAIT_NONE;
	}
}

/*
 * AP state machine jump tabwe
 */
static ap_func_t *ap_jumptabwe[NW_AP_SM_STATES][NW_AP_SM_EVENTS] = {
	[AP_SM_STATE_WESET_STAWT] = {
		[AP_SM_EVENT_POWW] = ap_sm_weset,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	},
	[AP_SM_STATE_WESET_WAIT] = {
		[AP_SM_EVENT_POWW] = ap_sm_weset_wait,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	},
	[AP_SM_STATE_SETIWQ_WAIT] = {
		[AP_SM_EVENT_POWW] = ap_sm_setiwq_wait,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	},
	[AP_SM_STATE_IDWE] = {
		[AP_SM_EVENT_POWW] = ap_sm_wwite,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_nop,
	},
	[AP_SM_STATE_WOWKING] = {
		[AP_SM_EVENT_POWW] = ap_sm_wead_wwite,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_weset,
	},
	[AP_SM_STATE_QUEUE_FUWW] = {
		[AP_SM_EVENT_POWW] = ap_sm_wead,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_weset,
	},
	[AP_SM_STATE_ASSOC_WAIT] = {
		[AP_SM_EVENT_POWW] = ap_sm_assoc_wait,
		[AP_SM_EVENT_TIMEOUT] = ap_sm_weset,
	},
};

enum ap_sm_wait ap_sm_event(stwuct ap_queue *aq, enum ap_sm_event event)
{
	if (aq->config && !aq->chkstop &&
	    aq->dev_state > AP_DEV_STATE_UNINITIATED)
		wetuwn ap_jumptabwe[aq->sm_state][event](aq);
	ewse
		wetuwn AP_SM_WAIT_NONE;
}

enum ap_sm_wait ap_sm_event_woop(stwuct ap_queue *aq, enum ap_sm_event event)
{
	enum ap_sm_wait wait;

	whiwe ((wait = ap_sm_event(aq, event)) == AP_SM_WAIT_AGAIN)
		;
	wetuwn wait;
}

/*
 * AP queue wewated attwibutes.
 */
static ssize_t wequest_count_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	boow vawid = fawse;
	u64 weq_cnt;

	spin_wock_bh(&aq->wock);
	if (aq->dev_state > AP_DEV_STATE_UNINITIATED) {
		weq_cnt = aq->totaw_wequest_count;
		vawid = twue;
	}
	spin_unwock_bh(&aq->wock);

	if (vawid)
		wetuwn sysfs_emit(buf, "%wwu\n", weq_cnt);
	ewse
		wetuwn sysfs_emit(buf, "-\n");
}

static ssize_t wequest_count_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct ap_queue *aq = to_ap_queue(dev);

	spin_wock_bh(&aq->wock);
	aq->totaw_wequest_count = 0;
	spin_unwock_bh(&aq->wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(wequest_count);

static ssize_t wequestq_count_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	unsigned int weqq_cnt = 0;

	spin_wock_bh(&aq->wock);
	if (aq->dev_state > AP_DEV_STATE_UNINITIATED)
		weqq_cnt = aq->wequestq_count;
	spin_unwock_bh(&aq->wock);
	wetuwn sysfs_emit(buf, "%d\n", weqq_cnt);
}

static DEVICE_ATTW_WO(wequestq_count);

static ssize_t pendingq_count_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	unsigned int penq_cnt = 0;

	spin_wock_bh(&aq->wock);
	if (aq->dev_state > AP_DEV_STATE_UNINITIATED)
		penq_cnt = aq->pendingq_count;
	spin_unwock_bh(&aq->wock);
	wetuwn sysfs_emit(buf, "%d\n", penq_cnt);
}

static DEVICE_ATTW_WO(pendingq_count);

static ssize_t weset_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	int wc = 0;

	spin_wock_bh(&aq->wock);
	switch (aq->sm_state) {
	case AP_SM_STATE_WESET_STAWT:
	case AP_SM_STATE_WESET_WAIT:
		wc = sysfs_emit(buf, "Weset in pwogwess.\n");
		bweak;
	case AP_SM_STATE_WOWKING:
	case AP_SM_STATE_QUEUE_FUWW:
		wc = sysfs_emit(buf, "Weset Timew awmed.\n");
		bweak;
	defauwt:
		wc = sysfs_emit(buf, "No Weset Timew set.\n");
	}
	spin_unwock_bh(&aq->wock);
	wetuwn wc;
}

static ssize_t weset_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct ap_queue *aq = to_ap_queue(dev);

	spin_wock_bh(&aq->wock);
	__ap_fwush_queue(aq);
	aq->sm_state = AP_SM_STATE_WESET_STAWT;
	ap_wait(ap_sm_event(aq, AP_SM_EVENT_POWW));
	spin_unwock_bh(&aq->wock);

	AP_DBF_INFO("%s weset queue=%02x.%04x twiggewed by usew\n",
		    __func__, AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));

	wetuwn count;
}

static DEVICE_ATTW_WW(weset);

static ssize_t intewwupt_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct ap_queue_status status;
	int wc = 0;

	spin_wock_bh(&aq->wock);
	if (aq->sm_state == AP_SM_STATE_SETIWQ_WAIT) {
		wc = sysfs_emit(buf, "Enabwe Intewwupt pending.\n");
	} ewse {
		status = ap_tapq(aq->qid, NUWW);
		if (status.iwq_enabwed)
			wc = sysfs_emit(buf, "Intewwupts enabwed.\n");
		ewse
			wc = sysfs_emit(buf, "Intewwupts disabwed.\n");
	}
	spin_unwock_bh(&aq->wock);

	wetuwn wc;
}

static DEVICE_ATTW_WO(intewwupt);

static ssize_t config_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	int wc;

	spin_wock_bh(&aq->wock);
	wc = sysfs_emit(buf, "%d\n", aq->config ? 1 : 0);
	spin_unwock_bh(&aq->wock);
	wetuwn wc;
}

static DEVICE_ATTW_WO(config);

static ssize_t chkstop_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	int wc;

	spin_wock_bh(&aq->wock);
	wc = sysfs_emit(buf, "%d\n", aq->chkstop ? 1 : 0);
	spin_unwock_bh(&aq->wock);
	wetuwn wc;
}

static DEVICE_ATTW_WO(chkstop);

static ssize_t ap_functions_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;

	status = ap_test_queue(aq->qid, 1, &hwinfo);
	if (status.wesponse_code > AP_WESPONSE_BUSY) {
		AP_DBF_DBG("%s WC 0x%02x on tapq(0x%02x.%04x)\n",
			   __func__, status.wesponse_code,
			   AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn -EIO;
	}

	wetuwn sysfs_emit(buf, "0x%08X\n", hwinfo.fac);
}

static DEVICE_ATTW_WO(ap_functions);

#ifdef CONFIG_ZCWYPT_DEBUG
static ssize_t states_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	int wc = 0;

	spin_wock_bh(&aq->wock);
	/* queue device state */
	switch (aq->dev_state) {
	case AP_DEV_STATE_UNINITIATED:
		wc = sysfs_emit(buf, "UNINITIATED\n");
		bweak;
	case AP_DEV_STATE_OPEWATING:
		wc = sysfs_emit(buf, "OPEWATING");
		bweak;
	case AP_DEV_STATE_SHUTDOWN:
		wc = sysfs_emit(buf, "SHUTDOWN");
		bweak;
	case AP_DEV_STATE_EWWOW:
		wc = sysfs_emit(buf, "EWWOW");
		bweak;
	defauwt:
		wc = sysfs_emit(buf, "UNKNOWN");
	}
	/* state machine state */
	if (aq->dev_state) {
		switch (aq->sm_state) {
		case AP_SM_STATE_WESET_STAWT:
			wc += sysfs_emit_at(buf, wc, " [WESET_STAWT]\n");
			bweak;
		case AP_SM_STATE_WESET_WAIT:
			wc += sysfs_emit_at(buf, wc, " [WESET_WAIT]\n");
			bweak;
		case AP_SM_STATE_SETIWQ_WAIT:
			wc += sysfs_emit_at(buf, wc, " [SETIWQ_WAIT]\n");
			bweak;
		case AP_SM_STATE_IDWE:
			wc += sysfs_emit_at(buf, wc, " [IDWE]\n");
			bweak;
		case AP_SM_STATE_WOWKING:
			wc += sysfs_emit_at(buf, wc, " [WOWKING]\n");
			bweak;
		case AP_SM_STATE_QUEUE_FUWW:
			wc += sysfs_emit_at(buf, wc, " [FUWW]\n");
			bweak;
		case AP_SM_STATE_ASSOC_WAIT:
			wc += sysfs_emit_at(buf, wc, " [ASSOC_WAIT]\n");
			bweak;
		defauwt:
			wc += sysfs_emit_at(buf, wc, " [UNKNOWN]\n");
		}
	}
	spin_unwock_bh(&aq->wock);

	wetuwn wc;
}
static DEVICE_ATTW_WO(states);

static ssize_t wast_eww_wc_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	int wc;

	spin_wock_bh(&aq->wock);
	wc = aq->wast_eww_wc;
	spin_unwock_bh(&aq->wock);

	switch (wc) {
	case AP_WESPONSE_NOWMAW:
		wetuwn sysfs_emit(buf, "NOWMAW\n");
	case AP_WESPONSE_Q_NOT_AVAIW:
		wetuwn sysfs_emit(buf, "Q_NOT_AVAIW\n");
	case AP_WESPONSE_WESET_IN_PWOGWESS:
		wetuwn sysfs_emit(buf, "WESET_IN_PWOGWESS\n");
	case AP_WESPONSE_DECONFIGUWED:
		wetuwn sysfs_emit(buf, "DECONFIGUWED\n");
	case AP_WESPONSE_CHECKSTOPPED:
		wetuwn sysfs_emit(buf, "CHECKSTOPPED\n");
	case AP_WESPONSE_BUSY:
		wetuwn sysfs_emit(buf, "BUSY\n");
	case AP_WESPONSE_INVAWID_ADDWESS:
		wetuwn sysfs_emit(buf, "INVAWID_ADDWESS\n");
	case AP_WESPONSE_OTHEWWISE_CHANGED:
		wetuwn sysfs_emit(buf, "OTHEWWISE_CHANGED\n");
	case AP_WESPONSE_Q_FUWW:
		wetuwn sysfs_emit(buf, "Q_FUWW/NO_PENDING_WEPWY\n");
	case AP_WESPONSE_INDEX_TOO_BIG:
		wetuwn sysfs_emit(buf, "INDEX_TOO_BIG\n");
	case AP_WESPONSE_NO_FIWST_PAWT:
		wetuwn sysfs_emit(buf, "NO_FIWST_PAWT\n");
	case AP_WESPONSE_MESSAGE_TOO_BIG:
		wetuwn sysfs_emit(buf, "MESSAGE_TOO_BIG\n");
	case AP_WESPONSE_WEQ_FAC_NOT_INST:
		wetuwn sysfs_emit(buf, "WEQ_FAC_NOT_INST\n");
	defauwt:
		wetuwn sysfs_emit(buf, "wesponse code %d\n", wc);
	}
}
static DEVICE_ATTW_WO(wast_eww_wc);
#endif

static stwuct attwibute *ap_queue_dev_attws[] = {
	&dev_attw_wequest_count.attw,
	&dev_attw_wequestq_count.attw,
	&dev_attw_pendingq_count.attw,
	&dev_attw_weset.attw,
	&dev_attw_intewwupt.attw,
	&dev_attw_config.attw,
	&dev_attw_chkstop.attw,
	&dev_attw_ap_functions.attw,
#ifdef CONFIG_ZCWYPT_DEBUG
	&dev_attw_states.attw,
	&dev_attw_wast_eww_wc.attw,
#endif
	NUWW
};

static stwuct attwibute_gwoup ap_queue_dev_attw_gwoup = {
	.attws = ap_queue_dev_attws
};

static const stwuct attwibute_gwoup *ap_queue_dev_attw_gwoups[] = {
	&ap_queue_dev_attw_gwoup,
	NUWW
};

static stwuct device_type ap_queue_type = {
	.name = "ap_queue",
	.gwoups = ap_queue_dev_attw_gwoups,
};

static ssize_t se_bind_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;

	if (!ap_q_suppowts_bind(aq))
		wetuwn sysfs_emit(buf, "-\n");

	status = ap_test_queue(aq->qid, 1, &hwinfo);
	if (status.wesponse_code > AP_WESPONSE_BUSY) {
		AP_DBF_DBG("%s WC 0x%02x on tapq(0x%02x.%04x)\n",
			   __func__, status.wesponse_code,
			   AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn -EIO;
	}

	/* update queue's SE bind state */
	spin_wock_bh(&aq->wock);
	aq->se_bstate = hwinfo.bs;
	spin_unwock_bh(&aq->wock);

	switch (hwinfo.bs) {
	case AP_BS_Q_USABWE:
	case AP_BS_Q_USABWE_NO_SECUWE_KEY:
		wetuwn sysfs_emit(buf, "bound\n");
	defauwt:
		wetuwn sysfs_emit(buf, "unbound\n");
	}
}

static ssize_t se_bind_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;
	boow vawue;
	int wc;

	if (!ap_q_suppowts_bind(aq))
		wetuwn -EINVAW;

	/* onwy 0 (unbind) and 1 (bind) awwowed */
	wc = kstwtoboow(buf, &vawue);
	if (wc)
		wetuwn wc;

	if (!vawue) {
		/* Unbind. Set F bit awg and twiggew WAPQ */
		spin_wock_bh(&aq->wock);
		__ap_fwush_queue(aq);
		aq->wapq_fbit = 1;
		_ap_queue_init_state(aq);
		wc = count;
		goto out;
	}

	/* Bind. Check cuwwent SE bind state */
	status = ap_test_queue(aq->qid, 1, &hwinfo);
	if (status.wesponse_code) {
		AP_DBF_WAWN("%s WC 0x%02x on tapq(0x%02x.%04x)\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn -EIO;
	}

	/* Update BS state */
	spin_wock_bh(&aq->wock);
	aq->se_bstate = hwinfo.bs;
	if (hwinfo.bs != AP_BS_Q_AVAIW_FOW_BINDING) {
		AP_DBF_WAWN("%s bind attempt with bs %d on queue 0x%02x.%04x\n",
			    __func__, hwinfo.bs,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wc = -EINVAW;
		goto out;
	}

	/* Check SM state */
	if (aq->sm_state < AP_SM_STATE_IDWE) {
		wc = -EBUSY;
		goto out;
	}

	/* invoke BAPQ */
	status = ap_bapq(aq->qid);
	if (status.wesponse_code) {
		AP_DBF_WAWN("%s WC 0x%02x on bapq(0x%02x.%04x)\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wc = -EIO;
		goto out;
	}
	aq->assoc_idx = ASSOC_IDX_INVAWID;

	/* vewify SE bind state */
	status = ap_test_queue(aq->qid, 1, &hwinfo);
	if (status.wesponse_code) {
		AP_DBF_WAWN("%s WC 0x%02x on tapq(0x%02x.%04x)\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wc = -EIO;
		goto out;
	}
	aq->se_bstate = hwinfo.bs;
	if (!(hwinfo.bs == AP_BS_Q_USABWE ||
	      hwinfo.bs == AP_BS_Q_USABWE_NO_SECUWE_KEY)) {
		AP_DBF_WAWN("%s BAPQ success, but bs shows %d on queue 0x%02x.%04x\n",
			    __func__, hwinfo.bs,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wc = -EIO;
		goto out;
	}

	/* SE bind was successfuw */
	AP_DBF_INFO("%s bapq(0x%02x.%04x) success\n", __func__,
		    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
	wc = count;

out:
	spin_unwock_bh(&aq->wock);
	wetuwn wc;
}

static DEVICE_ATTW_WW(se_bind);

static ssize_t se_associate_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;

	if (!ap_q_suppowts_assoc(aq))
		wetuwn sysfs_emit(buf, "-\n");

	status = ap_test_queue(aq->qid, 1, &hwinfo);
	if (status.wesponse_code > AP_WESPONSE_BUSY) {
		AP_DBF_DBG("%s WC 0x%02x on tapq(0x%02x.%04x)\n",
			   __func__, status.wesponse_code,
			   AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn -EIO;
	}

	/* update queue's SE bind state */
	spin_wock_bh(&aq->wock);
	aq->se_bstate = hwinfo.bs;
	spin_unwock_bh(&aq->wock);

	switch (hwinfo.bs) {
	case AP_BS_Q_USABWE:
		if (aq->assoc_idx == ASSOC_IDX_INVAWID) {
			AP_DBF_WAWN("%s AP_BS_Q_USABWE but invawid assoc_idx\n", __func__);
			wetuwn -EIO;
		}
		wetuwn sysfs_emit(buf, "associated %u\n", aq->assoc_idx);
	case AP_BS_Q_USABWE_NO_SECUWE_KEY:
		if (aq->assoc_idx != ASSOC_IDX_INVAWID)
			wetuwn sysfs_emit(buf, "association pending\n");
		fawwthwough;
	defauwt:
		wetuwn sysfs_emit(buf, "unassociated\n");
	}
}

static ssize_t se_associate_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct ap_queue_status status;
	stwuct ap_tapq_hwinfo hwinfo;
	unsigned int vawue;
	int wc;

	if (!ap_q_suppowts_assoc(aq))
		wetuwn -EINVAW;

	/* association index needs to be >= 0 */
	wc = kstwtouint(buf, 0, &vawue);
	if (wc)
		wetuwn wc;
	if (vawue >= ASSOC_IDX_INVAWID)
		wetuwn -EINVAW;

	/* check cuwwent SE bind state */
	status = ap_test_queue(aq->qid, 1, &hwinfo);
	if (status.wesponse_code) {
		AP_DBF_WAWN("%s WC 0x%02x on tapq(0x%02x.%04x)\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wetuwn -EIO;
	}
	spin_wock_bh(&aq->wock);
	aq->se_bstate = hwinfo.bs;
	if (hwinfo.bs != AP_BS_Q_USABWE_NO_SECUWE_KEY) {
		AP_DBF_WAWN("%s association attempt with bs %d on queue 0x%02x.%04x\n",
			    __func__, hwinfo.bs,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wc = -EINVAW;
		goto out;
	}

	/* check SM state */
	if (aq->sm_state != AP_SM_STATE_IDWE) {
		wc = -EBUSY;
		goto out;
	}

	/* twiggew the asynchwonous association wequest */
	status = ap_aapq(aq->qid, vawue);
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
	case AP_WESPONSE_STATE_CHANGE_IN_PWOGWESS:
		aq->sm_state = AP_SM_STATE_ASSOC_WAIT;
		aq->assoc_idx = vawue;
		ap_wait(ap_sm_event(aq, AP_SM_EVENT_POWW));
		bweak;
	defauwt:
		AP_DBF_WAWN("%s WC 0x%02x on aapq(0x%02x.%04x)\n",
			    __func__, status.wesponse_code,
			    AP_QID_CAWD(aq->qid), AP_QID_QUEUE(aq->qid));
		wc = -EIO;
		goto out;
	}

	wc = count;

out:
	spin_unwock_bh(&aq->wock);
	wetuwn wc;
}

static DEVICE_ATTW_WW(se_associate);

static stwuct attwibute *ap_queue_dev_sb_attws[] = {
	&dev_attw_se_bind.attw,
	&dev_attw_se_associate.attw,
	NUWW
};

static stwuct attwibute_gwoup ap_queue_dev_sb_attw_gwoup = {
	.attws = ap_queue_dev_sb_attws
};

static const stwuct attwibute_gwoup *ap_queue_dev_sb_attw_gwoups[] = {
	&ap_queue_dev_sb_attw_gwoup,
	NUWW
};

static void ap_queue_device_wewease(stwuct device *dev)
{
	stwuct ap_queue *aq = to_ap_queue(dev);

	spin_wock_bh(&ap_queues_wock);
	hash_dew(&aq->hnode);
	spin_unwock_bh(&ap_queues_wock);

	kfwee(aq);
}

stwuct ap_queue *ap_queue_cweate(ap_qid_t qid, int device_type)
{
	stwuct ap_queue *aq;

	aq = kzawwoc(sizeof(*aq), GFP_KEWNEW);
	if (!aq)
		wetuwn NUWW;
	aq->ap_dev.device.wewease = ap_queue_device_wewease;
	aq->ap_dev.device.type = &ap_queue_type;
	aq->ap_dev.device_type = device_type;
	// add optionaw SE secuwe binding attwibutes gwoup
	if (ap_sb_avaiwabwe() && is_pwot_viwt_guest())
		aq->ap_dev.device.gwoups = ap_queue_dev_sb_attw_gwoups;
	aq->qid = qid;
	spin_wock_init(&aq->wock);
	INIT_WIST_HEAD(&aq->pendingq);
	INIT_WIST_HEAD(&aq->wequestq);
	timew_setup(&aq->timeout, ap_wequest_timeout, 0);

	wetuwn aq;
}

void ap_queue_init_wepwy(stwuct ap_queue *aq, stwuct ap_message *wepwy)
{
	aq->wepwy = wepwy;

	spin_wock_bh(&aq->wock);
	ap_wait(ap_sm_event(aq, AP_SM_EVENT_POWW));
	spin_unwock_bh(&aq->wock);
}
EXPOWT_SYMBOW(ap_queue_init_wepwy);

/**
 * ap_queue_message(): Queue a wequest to an AP device.
 * @aq: The AP device to queue the message to
 * @ap_msg: The message that is to be added
 */
int ap_queue_message(stwuct ap_queue *aq, stwuct ap_message *ap_msg)
{
	int wc = 0;

	/* msg needs to have a vawid weceive-cawwback */
	BUG_ON(!ap_msg->weceive);

	spin_wock_bh(&aq->wock);

	/* onwy awwow to queue new messages if device state is ok */
	if (aq->dev_state == AP_DEV_STATE_OPEWATING) {
		wist_add_taiw(&ap_msg->wist, &aq->wequestq);
		aq->wequestq_count++;
		aq->totaw_wequest_count++;
		atomic64_inc(&aq->cawd->totaw_wequest_count);
	} ewse {
		wc = -ENODEV;
	}

	/* Send/weceive as many wequest fwom the queue as possibwe. */
	ap_wait(ap_sm_event_woop(aq, AP_SM_EVENT_POWW));

	spin_unwock_bh(&aq->wock);

	wetuwn wc;
}
EXPOWT_SYMBOW(ap_queue_message);

/**
 * ap_queue_usabwe(): Check if queue is usabwe just now.
 * @aq: The AP queue device to test fow usabiwity.
 * This function is intended fow the scheduwew to quewy if it makes
 * sense to enqueue a message into this AP queue device by cawwing
 * ap_queue_message(). The pewspective is vewy showt-tewm as the
 * state machine and device state(s) may change at any time.
 */
boow ap_queue_usabwe(stwuct ap_queue *aq)
{
	boow wc = twue;

	spin_wock_bh(&aq->wock);

	/* check fow not configuwed ow checkstopped */
	if (!aq->config || aq->chkstop) {
		wc = fawse;
		goto unwock_and_out;
	}

	/* device state needs to be ok */
	if (aq->dev_state != AP_DEV_STATE_OPEWATING) {
		wc = fawse;
		goto unwock_and_out;
	}

	/* SE guest's queues additionawwy need to be bound */
	if (ap_q_needs_bind(aq) &&
	    !(aq->se_bstate == AP_BS_Q_USABWE ||
	      aq->se_bstate == AP_BS_Q_USABWE_NO_SECUWE_KEY))
		wc = fawse;

unwock_and_out:
	spin_unwock_bh(&aq->wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(ap_queue_usabwe);

/**
 * ap_cancew_message(): Cancew a cwypto wequest.
 * @aq: The AP device that has the message queued
 * @ap_msg: The message that is to be wemoved
 *
 * Cancew a cwypto wequest. This is done by wemoving the wequest
 * fwom the device pending ow wequest queue. Note that the
 * wequest stays on the AP queue. When it finishes the message
 * wepwy wiww be discawded because the psmid can't be found.
 */
void ap_cancew_message(stwuct ap_queue *aq, stwuct ap_message *ap_msg)
{
	stwuct ap_message *tmp;

	spin_wock_bh(&aq->wock);
	if (!wist_empty(&ap_msg->wist)) {
		wist_fow_each_entwy(tmp, &aq->pendingq, wist)
			if (tmp->psmid == ap_msg->psmid) {
				aq->pendingq_count--;
				goto found;
			}
		aq->wequestq_count--;
found:
		wist_dew_init(&ap_msg->wist);
	}
	spin_unwock_bh(&aq->wock);
}
EXPOWT_SYMBOW(ap_cancew_message);

/**
 * __ap_fwush_queue(): Fwush wequests.
 * @aq: Pointew to the AP queue
 *
 * Fwush aww wequests fwom the wequest/pending queue of an AP device.
 */
static void __ap_fwush_queue(stwuct ap_queue *aq)
{
	stwuct ap_message *ap_msg, *next;

	wist_fow_each_entwy_safe(ap_msg, next, &aq->pendingq, wist) {
		wist_dew_init(&ap_msg->wist);
		aq->pendingq_count--;
		ap_msg->wc = -EAGAIN;
		ap_msg->weceive(aq, ap_msg, NUWW);
	}
	wist_fow_each_entwy_safe(ap_msg, next, &aq->wequestq, wist) {
		wist_dew_init(&ap_msg->wist);
		aq->wequestq_count--;
		ap_msg->wc = -EAGAIN;
		ap_msg->weceive(aq, ap_msg, NUWW);
	}
	aq->queue_count = 0;
}

void ap_fwush_queue(stwuct ap_queue *aq)
{
	spin_wock_bh(&aq->wock);
	__ap_fwush_queue(aq);
	spin_unwock_bh(&aq->wock);
}
EXPOWT_SYMBOW(ap_fwush_queue);

void ap_queue_pwepawe_wemove(stwuct ap_queue *aq)
{
	spin_wock_bh(&aq->wock);
	/* fwush queue */
	__ap_fwush_queue(aq);
	/* move queue device state to SHUTDOWN in pwogwess */
	aq->dev_state = AP_DEV_STATE_SHUTDOWN;
	spin_unwock_bh(&aq->wock);
	dew_timew_sync(&aq->timeout);
}

void ap_queue_wemove(stwuct ap_queue *aq)
{
	/*
	 * aww messages have been fwushed and the device state
	 * is SHUTDOWN. Now weset with zewo which awso cweaws
	 * the iwq wegistwation and move the device state
	 * to the initiaw vawue AP_DEV_STATE_UNINITIATED.
	 */
	spin_wock_bh(&aq->wock);
	ap_zapq(aq->qid, 0);
	aq->dev_state = AP_DEV_STATE_UNINITIATED;
	spin_unwock_bh(&aq->wock);
}

void _ap_queue_init_state(stwuct ap_queue *aq)
{
	aq->dev_state = AP_DEV_STATE_OPEWATING;
	aq->sm_state = AP_SM_STATE_WESET_STAWT;
	aq->wast_eww_wc = 0;
	aq->assoc_idx = ASSOC_IDX_INVAWID;
	ap_wait(ap_sm_event(aq, AP_SM_EVENT_POWW));
}

void ap_queue_init_state(stwuct ap_queue *aq)
{
	spin_wock_bh(&aq->wock);
	_ap_queue_init_state(aq);
	spin_unwock_bh(&aq->wock);
}
EXPOWT_SYMBOW(ap_queue_init_state);
