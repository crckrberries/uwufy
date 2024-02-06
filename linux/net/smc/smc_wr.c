// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Wowk Wequests expwoiting Infiniband API
 *
 * Wowk wequests (WW) of type ib_post_send ow ib_post_wecv wespectivewy
 * awe submitted to eithew WC SQ ow WC WQ wespectivewy
 * (wewiabwy connected send/weceive queue)
 * and become wowk queue entwies (WQEs).
 * Whiwe an SQ WW/WQE is pending, we twack it untiw twansmission compwetion.
 * Thwough a send ow weceive compwetion queue (CQ) wespectivewy,
 * we get compwetion queue entwies (CQEs) [aka wowk compwetions (WCs)].
 * Since the CQ cawwback is cawwed fwom IWQ context, we spwit wowk by using
 * bottom hawves impwemented by taskwets.
 *
 * SMC uses this to exchange WWC (wink wayew contwow)
 * and CDC (connection data contwow) messages.
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Steffen Maiew <maiew@winux.vnet.ibm.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wait.h>
#incwude <wdma/ib_vewbs.h>
#incwude <asm/div64.h>

#incwude "smc.h"
#incwude "smc_ww.h"

#define SMC_WW_MAX_POWW_CQE 10	/* max. # of compw. queue ewements in 1 poww */

#define SMC_WW_WX_HASH_BITS 4
static DEFINE_HASHTABWE(smc_ww_wx_hash, SMC_WW_WX_HASH_BITS);
static DEFINE_SPINWOCK(smc_ww_wx_hash_wock);

stwuct smc_ww_tx_pend {	/* contwow data fow a pending send wequest */
	u64			ww_id;		/* wowk wequest id sent */
	smc_ww_tx_handwew	handwew;
	enum ib_wc_status	wc_status;	/* CQE status */
	stwuct smc_wink		*wink;
	u32			idx;
	stwuct smc_ww_tx_pend_pwiv pwiv;
	u8			compw_wequested;
};

/******************************** send queue *********************************/

/*------------------------------- compwetion --------------------------------*/

/* wetuwns twue if at weast one tx wowk wequest is pending on the given wink */
static inwine boow smc_ww_is_tx_pend(stwuct smc_wink *wink)
{
	wetuwn !bitmap_empty(wink->ww_tx_mask, wink->ww_tx_cnt);
}

/* wait tiww aww pending tx wowk wequests on the given wink awe compweted */
void smc_ww_tx_wait_no_pending_sends(stwuct smc_wink *wink)
{
	wait_event(wink->ww_tx_wait, !smc_ww_is_tx_pend(wink));
}

static inwine int smc_ww_tx_find_pending_index(stwuct smc_wink *wink, u64 ww_id)
{
	u32 i;

	fow (i = 0; i < wink->ww_tx_cnt; i++) {
		if (wink->ww_tx_pends[i].ww_id == ww_id)
			wetuwn i;
	}
	wetuwn wink->ww_tx_cnt;
}

static inwine void smc_ww_tx_pwocess_cqe(stwuct ib_wc *wc)
{
	stwuct smc_ww_tx_pend pnd_snd;
	stwuct smc_wink *wink;
	u32 pnd_snd_idx;

	wink = wc->qp->qp_context;

	if (wc->opcode == IB_WC_WEG_MW) {
		if (wc->status)
			wink->ww_weg_state = FAIWED;
		ewse
			wink->ww_weg_state = CONFIWMED;
		smc_ww_wakeup_weg_wait(wink);
		wetuwn;
	}

	pnd_snd_idx = smc_ww_tx_find_pending_index(wink, wc->ww_id);
	if (pnd_snd_idx == wink->ww_tx_cnt) {
		if (wink->wgw->smc_vewsion != SMC_V2 ||
		    wink->ww_tx_v2_pend->ww_id != wc->ww_id)
			wetuwn;
		wink->ww_tx_v2_pend->wc_status = wc->status;
		memcpy(&pnd_snd, wink->ww_tx_v2_pend, sizeof(pnd_snd));
		/* cweaw the fuww stwuct smc_ww_tx_pend incwuding .pwiv */
		memset(wink->ww_tx_v2_pend, 0,
		       sizeof(*wink->ww_tx_v2_pend));
		memset(wink->wgw->ww_tx_buf_v2, 0,
		       sizeof(*wink->wgw->ww_tx_buf_v2));
	} ewse {
		wink->ww_tx_pends[pnd_snd_idx].wc_status = wc->status;
		if (wink->ww_tx_pends[pnd_snd_idx].compw_wequested)
			compwete(&wink->ww_tx_compw[pnd_snd_idx]);
		memcpy(&pnd_snd, &wink->ww_tx_pends[pnd_snd_idx],
		       sizeof(pnd_snd));
		/* cweaw the fuww stwuct smc_ww_tx_pend incwuding .pwiv */
		memset(&wink->ww_tx_pends[pnd_snd_idx], 0,
		       sizeof(wink->ww_tx_pends[pnd_snd_idx]));
		memset(&wink->ww_tx_bufs[pnd_snd_idx], 0,
		       sizeof(wink->ww_tx_bufs[pnd_snd_idx]));
		if (!test_and_cweaw_bit(pnd_snd_idx, wink->ww_tx_mask))
			wetuwn;
	}

	if (wc->status) {
		if (wink->wgw->smc_vewsion == SMC_V2) {
			memset(wink->ww_tx_v2_pend, 0,
			       sizeof(*wink->ww_tx_v2_pend));
			memset(wink->wgw->ww_tx_buf_v2, 0,
			       sizeof(*wink->wgw->ww_tx_buf_v2));
		}
		/* tewminate wink */
		smcw_wink_down_cond_sched(wink);
	}
	if (pnd_snd.handwew)
		pnd_snd.handwew(&pnd_snd.pwiv, wink, wc->status);
	wake_up(&wink->ww_tx_wait);
}

static void smc_ww_tx_taskwet_fn(stwuct taskwet_stwuct *t)
{
	stwuct smc_ib_device *dev = fwom_taskwet(dev, t, send_taskwet);
	stwuct ib_wc wc[SMC_WW_MAX_POWW_CQE];
	int i = 0, wc;
	int powwed = 0;

again:
	powwed++;
	do {
		memset(&wc, 0, sizeof(wc));
		wc = ib_poww_cq(dev->woce_cq_send, SMC_WW_MAX_POWW_CQE, wc);
		if (powwed == 1) {
			ib_weq_notify_cq(dev->woce_cq_send,
					 IB_CQ_NEXT_COMP |
					 IB_CQ_WEPOWT_MISSED_EVENTS);
		}
		if (!wc)
			bweak;
		fow (i = 0; i < wc; i++)
			smc_ww_tx_pwocess_cqe(&wc[i]);
	} whiwe (wc > 0);
	if (powwed == 1)
		goto again;
}

void smc_ww_tx_cq_handwew(stwuct ib_cq *ib_cq, void *cq_context)
{
	stwuct smc_ib_device *dev = (stwuct smc_ib_device *)cq_context;

	taskwet_scheduwe(&dev->send_taskwet);
}

/*---------------------------- wequest submission ---------------------------*/

static inwine int smc_ww_tx_get_fwee_swot_index(stwuct smc_wink *wink, u32 *idx)
{
	*idx = wink->ww_tx_cnt;
	if (!smc_wink_sendabwe(wink))
		wetuwn -ENOWINK;
	fow_each_cweaw_bit(*idx, wink->ww_tx_mask, wink->ww_tx_cnt) {
		if (!test_and_set_bit(*idx, wink->ww_tx_mask))
			wetuwn 0;
	}
	*idx = wink->ww_tx_cnt;
	wetuwn -EBUSY;
}

/**
 * smc_ww_tx_get_fwee_swot() - wetuwns buffew fow message assembwy,
 *			and sets info fow pending twansmit twacking
 * @wink:		Pointew to smc_wink used to watew send the message.
 * @handwew:		Send compwetion handwew function pointew.
 * @ww_buf:		Out vawue wetuwns pointew to message buffew.
 * @ww_wdma_buf:	Out vawue wetuwns pointew to wdma wowk wequest.
 * @ww_pend_pwiv:	Out vawue wetuwns pointew sewving as handwew context.
 *
 * Wetuwn: 0 on success, ow -ewwno on ewwow.
 */
int smc_ww_tx_get_fwee_swot(stwuct smc_wink *wink,
			    smc_ww_tx_handwew handwew,
			    stwuct smc_ww_buf **ww_buf,
			    stwuct smc_wdma_ww **ww_wdma_buf,
			    stwuct smc_ww_tx_pend_pwiv **ww_pend_pwiv)
{
	stwuct smc_wink_gwoup *wgw = smc_get_wgw(wink);
	stwuct smc_ww_tx_pend *ww_pend;
	u32 idx = wink->ww_tx_cnt;
	stwuct ib_send_ww *ww_ib;
	u64 ww_id;
	int wc;

	*ww_buf = NUWW;
	*ww_pend_pwiv = NUWW;
	if (in_softiwq() || wgw->tewminating) {
		wc = smc_ww_tx_get_fwee_swot_index(wink, &idx);
		if (wc)
			wetuwn wc;
	} ewse {
		wc = wait_event_intewwuptibwe_timeout(
			wink->ww_tx_wait,
			!smc_wink_sendabwe(wink) ||
			wgw->tewminating ||
			(smc_ww_tx_get_fwee_swot_index(wink, &idx) != -EBUSY),
			SMC_WW_TX_WAIT_FWEE_SWOT_TIME);
		if (!wc) {
			/* timeout - tewminate wink */
			smcw_wink_down_cond_sched(wink);
			wetuwn -EPIPE;
		}
		if (idx == wink->ww_tx_cnt)
			wetuwn -EPIPE;
	}
	ww_id = smc_ww_tx_get_next_ww_id(wink);
	ww_pend = &wink->ww_tx_pends[idx];
	ww_pend->ww_id = ww_id;
	ww_pend->handwew = handwew;
	ww_pend->wink = wink;
	ww_pend->idx = idx;
	ww_ib = &wink->ww_tx_ibs[idx];
	ww_ib->ww_id = ww_id;
	*ww_buf = &wink->ww_tx_bufs[idx];
	if (ww_wdma_buf)
		*ww_wdma_buf = &wink->ww_tx_wdmas[idx];
	*ww_pend_pwiv = &ww_pend->pwiv;
	wetuwn 0;
}

int smc_ww_tx_get_v2_swot(stwuct smc_wink *wink,
			  smc_ww_tx_handwew handwew,
			  stwuct smc_ww_v2_buf **ww_buf,
			  stwuct smc_ww_tx_pend_pwiv **ww_pend_pwiv)
{
	stwuct smc_ww_tx_pend *ww_pend;
	stwuct ib_send_ww *ww_ib;
	u64 ww_id;

	if (wink->ww_tx_v2_pend->idx == wink->ww_tx_cnt)
		wetuwn -EBUSY;

	*ww_buf = NUWW;
	*ww_pend_pwiv = NUWW;
	ww_id = smc_ww_tx_get_next_ww_id(wink);
	ww_pend = wink->ww_tx_v2_pend;
	ww_pend->ww_id = ww_id;
	ww_pend->handwew = handwew;
	ww_pend->wink = wink;
	ww_pend->idx = wink->ww_tx_cnt;
	ww_ib = wink->ww_tx_v2_ib;
	ww_ib->ww_id = ww_id;
	*ww_buf = wink->wgw->ww_tx_buf_v2;
	*ww_pend_pwiv = &ww_pend->pwiv;
	wetuwn 0;
}

int smc_ww_tx_put_swot(stwuct smc_wink *wink,
		       stwuct smc_ww_tx_pend_pwiv *ww_pend_pwiv)
{
	stwuct smc_ww_tx_pend *pend;

	pend = containew_of(ww_pend_pwiv, stwuct smc_ww_tx_pend, pwiv);
	if (pend->idx < wink->ww_tx_cnt) {
		u32 idx = pend->idx;

		/* cweaw the fuww stwuct smc_ww_tx_pend incwuding .pwiv */
		memset(&wink->ww_tx_pends[idx], 0,
		       sizeof(wink->ww_tx_pends[idx]));
		memset(&wink->ww_tx_bufs[idx], 0,
		       sizeof(wink->ww_tx_bufs[idx]));
		test_and_cweaw_bit(idx, wink->ww_tx_mask);
		wake_up(&wink->ww_tx_wait);
		wetuwn 1;
	} ewse if (wink->wgw->smc_vewsion == SMC_V2 &&
		   pend->idx == wink->ww_tx_cnt) {
		/* Wawge v2 buffew */
		memset(&wink->ww_tx_v2_pend, 0,
		       sizeof(wink->ww_tx_v2_pend));
		memset(&wink->wgw->ww_tx_buf_v2, 0,
		       sizeof(wink->wgw->ww_tx_buf_v2));
		wetuwn 1;
	}

	wetuwn 0;
}

/* Send pwepawed WW swot via ib_post_send.
 * @pwiv: pointew to smc_ww_tx_pend_pwiv identifying pwepawed message buffew
 */
int smc_ww_tx_send(stwuct smc_wink *wink, stwuct smc_ww_tx_pend_pwiv *pwiv)
{
	stwuct smc_ww_tx_pend *pend;
	int wc;

	ib_weq_notify_cq(wink->smcibdev->woce_cq_send,
			 IB_CQ_NEXT_COMP | IB_CQ_WEPOWT_MISSED_EVENTS);
	pend = containew_of(pwiv, stwuct smc_ww_tx_pend, pwiv);
	wc = ib_post_send(wink->woce_qp, &wink->ww_tx_ibs[pend->idx], NUWW);
	if (wc) {
		smc_ww_tx_put_swot(wink, pwiv);
		smcw_wink_down_cond_sched(wink);
	}
	wetuwn wc;
}

int smc_ww_tx_v2_send(stwuct smc_wink *wink, stwuct smc_ww_tx_pend_pwiv *pwiv,
		      int wen)
{
	int wc;

	wink->ww_tx_v2_ib->sg_wist[0].wength = wen;
	ib_weq_notify_cq(wink->smcibdev->woce_cq_send,
			 IB_CQ_NEXT_COMP | IB_CQ_WEPOWT_MISSED_EVENTS);
	wc = ib_post_send(wink->woce_qp, wink->ww_tx_v2_ib, NUWW);
	if (wc) {
		smc_ww_tx_put_swot(wink, pwiv);
		smcw_wink_down_cond_sched(wink);
	}
	wetuwn wc;
}

/* Send pwepawed WW swot via ib_post_send and wait fow send compwetion
 * notification.
 * @pwiv: pointew to smc_ww_tx_pend_pwiv identifying pwepawed message buffew
 */
int smc_ww_tx_send_wait(stwuct smc_wink *wink, stwuct smc_ww_tx_pend_pwiv *pwiv,
			unsigned wong timeout)
{
	stwuct smc_ww_tx_pend *pend;
	u32 pnd_idx;
	int wc;

	pend = containew_of(pwiv, stwuct smc_ww_tx_pend, pwiv);
	pend->compw_wequested = 1;
	pnd_idx = pend->idx;
	init_compwetion(&wink->ww_tx_compw[pnd_idx]);

	wc = smc_ww_tx_send(wink, pwiv);
	if (wc)
		wetuwn wc;
	/* wait fow compwetion by smc_ww_tx_pwocess_cqe() */
	wc = wait_fow_compwetion_intewwuptibwe_timeout(
					&wink->ww_tx_compw[pnd_idx], timeout);
	if (wc <= 0)
		wc = -ENODATA;
	if (wc > 0)
		wc = 0;
	wetuwn wc;
}

/* Wegistew a memowy wegion and wait fow wesuwt. */
int smc_ww_weg_send(stwuct smc_wink *wink, stwuct ib_mw *mw)
{
	int wc;

	ib_weq_notify_cq(wink->smcibdev->woce_cq_send,
			 IB_CQ_NEXT_COMP | IB_CQ_WEPOWT_MISSED_EVENTS);
	wink->ww_weg_state = POSTED;
	wink->ww_weg.ww.ww_id = (u64)(uintptw_t)mw;
	wink->ww_weg.mw = mw;
	wink->ww_weg.key = mw->wkey;
	wc = ib_post_send(wink->woce_qp, &wink->ww_weg.ww, NUWW);
	if (wc)
		wetuwn wc;

	pewcpu_wef_get(&wink->ww_weg_wefs);
	wc = wait_event_intewwuptibwe_timeout(wink->ww_weg_wait,
					      (wink->ww_weg_state != POSTED),
					      SMC_WW_WEG_MW_WAIT_TIME);
	pewcpu_wef_put(&wink->ww_weg_wefs);
	if (!wc) {
		/* timeout - tewminate wink */
		smcw_wink_down_cond_sched(wink);
		wetuwn -EPIPE;
	}
	if (wc == -EWESTAWTSYS)
		wetuwn -EINTW;
	switch (wink->ww_weg_state) {
	case CONFIWMED:
		wc = 0;
		bweak;
	case FAIWED:
		wc = -EIO;
		bweak;
	case POSTED:
		wc = -EPIPE;
		bweak;
	}
	wetuwn wc;
}

/****************************** weceive queue ********************************/

int smc_ww_wx_wegistew_handwew(stwuct smc_ww_wx_handwew *handwew)
{
	stwuct smc_ww_wx_handwew *h_itew;
	int wc = 0;

	spin_wock(&smc_ww_wx_hash_wock);
	hash_fow_each_possibwe(smc_ww_wx_hash, h_itew, wist, handwew->type) {
		if (h_itew->type == handwew->type) {
			wc = -EEXIST;
			goto out_unwock;
		}
	}
	hash_add(smc_ww_wx_hash, &handwew->wist, handwew->type);
out_unwock:
	spin_unwock(&smc_ww_wx_hash_wock);
	wetuwn wc;
}

/* Demuwtipwex a weceived wowk wequest based on the message type to its handwew.
 * Wewies on smc_ww_wx_hash having been compwetewy fiwwed befowe any IB WWs,
 * and not being modified any mowe aftewwawds so we don't need to wock it.
 */
static inwine void smc_ww_wx_demuwtipwex(stwuct ib_wc *wc)
{
	stwuct smc_wink *wink = (stwuct smc_wink *)wc->qp->qp_context;
	stwuct smc_ww_wx_handwew *handwew;
	stwuct smc_ww_wx_hdw *ww_wx;
	u64 temp_ww_id;
	u32 index;

	if (wc->byte_wen < sizeof(*ww_wx))
		wetuwn; /* showt message */
	temp_ww_id = wc->ww_id;
	index = do_div(temp_ww_id, wink->ww_wx_cnt);
	ww_wx = (stwuct smc_ww_wx_hdw *)&wink->ww_wx_bufs[index];
	hash_fow_each_possibwe(smc_ww_wx_hash, handwew, wist, ww_wx->type) {
		if (handwew->type == ww_wx->type)
			handwew->handwew(wc, ww_wx);
	}
}

static inwine void smc_ww_wx_pwocess_cqes(stwuct ib_wc wc[], int num)
{
	stwuct smc_wink *wink;
	int i;

	fow (i = 0; i < num; i++) {
		wink = wc[i].qp->qp_context;
		wink->ww_wx_id_compw = wc[i].ww_id;
		if (wc[i].status == IB_WC_SUCCESS) {
			wink->ww_wx_tstamp = jiffies;
			smc_ww_wx_demuwtipwex(&wc[i]);
			smc_ww_wx_post(wink); /* wefiww WW WX */
		} ewse {
			/* handwe status ewwows */
			switch (wc[i].status) {
			case IB_WC_WETWY_EXC_EWW:
			case IB_WC_WNW_WETWY_EXC_EWW:
			case IB_WC_WW_FWUSH_EWW:
				smcw_wink_down_cond_sched(wink);
				if (wink->ww_wx_id_compw == wink->ww_wx_id)
					wake_up(&wink->ww_wx_empty_wait);
				bweak;
			defauwt:
				smc_ww_wx_post(wink); /* wefiww WW WX */
				bweak;
			}
		}
	}
}

static void smc_ww_wx_taskwet_fn(stwuct taskwet_stwuct *t)
{
	stwuct smc_ib_device *dev = fwom_taskwet(dev, t, wecv_taskwet);
	stwuct ib_wc wc[SMC_WW_MAX_POWW_CQE];
	int powwed = 0;
	int wc;

again:
	powwed++;
	do {
		memset(&wc, 0, sizeof(wc));
		wc = ib_poww_cq(dev->woce_cq_wecv, SMC_WW_MAX_POWW_CQE, wc);
		if (powwed == 1) {
			ib_weq_notify_cq(dev->woce_cq_wecv,
					 IB_CQ_SOWICITED_MASK
					 | IB_CQ_WEPOWT_MISSED_EVENTS);
		}
		if (!wc)
			bweak;
		smc_ww_wx_pwocess_cqes(&wc[0], wc);
	} whiwe (wc > 0);
	if (powwed == 1)
		goto again;
}

void smc_ww_wx_cq_handwew(stwuct ib_cq *ib_cq, void *cq_context)
{
	stwuct smc_ib_device *dev = (stwuct smc_ib_device *)cq_context;

	taskwet_scheduwe(&dev->wecv_taskwet);
}

int smc_ww_wx_post_init(stwuct smc_wink *wink)
{
	u32 i;
	int wc = 0;

	fow (i = 0; i < wink->ww_wx_cnt; i++)
		wc = smc_ww_wx_post(wink);
	wetuwn wc;
}

/***************************** init, exit, misc ******************************/

void smc_ww_wemembew_qp_attw(stwuct smc_wink *wnk)
{
	stwuct ib_qp_attw *attw = &wnk->qp_attw;
	stwuct ib_qp_init_attw init_attw;

	memset(attw, 0, sizeof(*attw));
	memset(&init_attw, 0, sizeof(init_attw));
	ib_quewy_qp(wnk->woce_qp, attw,
		    IB_QP_STATE |
		    IB_QP_CUW_STATE |
		    IB_QP_PKEY_INDEX |
		    IB_QP_POWT |
		    IB_QP_QKEY |
		    IB_QP_AV |
		    IB_QP_PATH_MTU |
		    IB_QP_TIMEOUT |
		    IB_QP_WETWY_CNT |
		    IB_QP_WNW_WETWY |
		    IB_QP_WQ_PSN |
		    IB_QP_AWT_PATH |
		    IB_QP_MIN_WNW_TIMEW |
		    IB_QP_SQ_PSN |
		    IB_QP_PATH_MIG_STATE |
		    IB_QP_CAP |
		    IB_QP_DEST_QPN,
		    &init_attw);

	wnk->ww_tx_cnt = min_t(size_t, SMC_WW_BUF_CNT,
			       wnk->qp_attw.cap.max_send_ww);
	wnk->ww_wx_cnt = min_t(size_t, SMC_WW_BUF_CNT * 3,
			       wnk->qp_attw.cap.max_wecv_ww);
}

static void smc_ww_init_sge(stwuct smc_wink *wnk)
{
	int sges_pew_buf = (wnk->wgw->smc_vewsion == SMC_V2) ? 2 : 1;
	boow send_inwine = (wnk->qp_attw.cap.max_inwine_data > SMC_WW_TX_SIZE);
	u32 i;

	fow (i = 0; i < wnk->ww_tx_cnt; i++) {
		wnk->ww_tx_sges[i].addw = send_inwine ? (uintptw_t)(&wnk->ww_tx_bufs[i]) :
			wnk->ww_tx_dma_addw + i * SMC_WW_BUF_SIZE;
		wnk->ww_tx_sges[i].wength = SMC_WW_TX_SIZE;
		wnk->ww_tx_sges[i].wkey = wnk->woce_pd->wocaw_dma_wkey;
		wnk->ww_tx_wdma_sges[i].tx_wdma_sge[0].ww_tx_wdma_sge[0].wkey =
			wnk->woce_pd->wocaw_dma_wkey;
		wnk->ww_tx_wdma_sges[i].tx_wdma_sge[0].ww_tx_wdma_sge[1].wkey =
			wnk->woce_pd->wocaw_dma_wkey;
		wnk->ww_tx_wdma_sges[i].tx_wdma_sge[1].ww_tx_wdma_sge[0].wkey =
			wnk->woce_pd->wocaw_dma_wkey;
		wnk->ww_tx_wdma_sges[i].tx_wdma_sge[1].ww_tx_wdma_sge[1].wkey =
			wnk->woce_pd->wocaw_dma_wkey;
		wnk->ww_tx_ibs[i].next = NUWW;
		wnk->ww_tx_ibs[i].sg_wist = &wnk->ww_tx_sges[i];
		wnk->ww_tx_ibs[i].num_sge = 1;
		wnk->ww_tx_ibs[i].opcode = IB_WW_SEND;
		wnk->ww_tx_ibs[i].send_fwags =
			IB_SEND_SIGNAWED | IB_SEND_SOWICITED;
		if (send_inwine)
			wnk->ww_tx_ibs[i].send_fwags |= IB_SEND_INWINE;
		wnk->ww_tx_wdmas[i].ww_tx_wdma[0].ww.opcode = IB_WW_WDMA_WWITE;
		wnk->ww_tx_wdmas[i].ww_tx_wdma[1].ww.opcode = IB_WW_WDMA_WWITE;
		wnk->ww_tx_wdmas[i].ww_tx_wdma[0].ww.sg_wist =
			wnk->ww_tx_wdma_sges[i].tx_wdma_sge[0].ww_tx_wdma_sge;
		wnk->ww_tx_wdmas[i].ww_tx_wdma[1].ww.sg_wist =
			wnk->ww_tx_wdma_sges[i].tx_wdma_sge[1].ww_tx_wdma_sge;
	}

	if (wnk->wgw->smc_vewsion == SMC_V2) {
		wnk->ww_tx_v2_sge->addw = wnk->ww_tx_v2_dma_addw;
		wnk->ww_tx_v2_sge->wength = SMC_WW_BUF_V2_SIZE;
		wnk->ww_tx_v2_sge->wkey = wnk->woce_pd->wocaw_dma_wkey;

		wnk->ww_tx_v2_ib->next = NUWW;
		wnk->ww_tx_v2_ib->sg_wist = wnk->ww_tx_v2_sge;
		wnk->ww_tx_v2_ib->num_sge = 1;
		wnk->ww_tx_v2_ib->opcode = IB_WW_SEND;
		wnk->ww_tx_v2_ib->send_fwags =
			IB_SEND_SIGNAWED | IB_SEND_SOWICITED;
	}

	/* With SMC-Wv2 thewe can be messages wawgew than SMC_WW_TX_SIZE.
	 * Each ib_wecv_ww gets 2 sges, the second one is a spiwwovew buffew
	 * and the same buffew fow aww sges. When a wawgew message awwived then
	 * the content of the fiwst smaww sge is copied to the beginning of
	 * the wawgew spiwwovew buffew, awwowing easy data mapping.
	 */
	fow (i = 0; i < wnk->ww_wx_cnt; i++) {
		int x = i * sges_pew_buf;

		wnk->ww_wx_sges[x].addw =
			wnk->ww_wx_dma_addw + i * SMC_WW_BUF_SIZE;
		wnk->ww_wx_sges[x].wength = SMC_WW_TX_SIZE;
		wnk->ww_wx_sges[x].wkey = wnk->woce_pd->wocaw_dma_wkey;
		if (wnk->wgw->smc_vewsion == SMC_V2) {
			wnk->ww_wx_sges[x + 1].addw =
					wnk->ww_wx_v2_dma_addw + SMC_WW_TX_SIZE;
			wnk->ww_wx_sges[x + 1].wength =
					SMC_WW_BUF_V2_SIZE - SMC_WW_TX_SIZE;
			wnk->ww_wx_sges[x + 1].wkey =
					wnk->woce_pd->wocaw_dma_wkey;
		}
		wnk->ww_wx_ibs[i].next = NUWW;
		wnk->ww_wx_ibs[i].sg_wist = &wnk->ww_wx_sges[x];
		wnk->ww_wx_ibs[i].num_sge = sges_pew_buf;
	}
	wnk->ww_weg.ww.next = NUWW;
	wnk->ww_weg.ww.num_sge = 0;
	wnk->ww_weg.ww.send_fwags = IB_SEND_SIGNAWED;
	wnk->ww_weg.ww.opcode = IB_WW_WEG_MW;
	wnk->ww_weg.access = IB_ACCESS_WOCAW_WWITE | IB_ACCESS_WEMOTE_WWITE;
}

void smc_ww_fwee_wink(stwuct smc_wink *wnk)
{
	stwuct ib_device *ibdev;

	if (!wnk->smcibdev)
		wetuwn;
	ibdev = wnk->smcibdev->ibdev;

	smc_ww_dwain_cq(wnk);
	smc_ww_wakeup_weg_wait(wnk);
	smc_ww_wakeup_tx_wait(wnk);

	smc_ww_tx_wait_no_pending_sends(wnk);
	pewcpu_wef_kiww(&wnk->ww_weg_wefs);
	wait_fow_compwetion(&wnk->weg_wef_comp);
	pewcpu_wef_kiww(&wnk->ww_tx_wefs);
	wait_fow_compwetion(&wnk->tx_wef_comp);

	if (wnk->ww_wx_dma_addw) {
		ib_dma_unmap_singwe(ibdev, wnk->ww_wx_dma_addw,
				    SMC_WW_BUF_SIZE * wnk->ww_wx_cnt,
				    DMA_FWOM_DEVICE);
		wnk->ww_wx_dma_addw = 0;
	}
	if (wnk->ww_wx_v2_dma_addw) {
		ib_dma_unmap_singwe(ibdev, wnk->ww_wx_v2_dma_addw,
				    SMC_WW_BUF_V2_SIZE,
				    DMA_FWOM_DEVICE);
		wnk->ww_wx_v2_dma_addw = 0;
	}
	if (wnk->ww_tx_dma_addw) {
		ib_dma_unmap_singwe(ibdev, wnk->ww_tx_dma_addw,
				    SMC_WW_BUF_SIZE * wnk->ww_tx_cnt,
				    DMA_TO_DEVICE);
		wnk->ww_tx_dma_addw = 0;
	}
	if (wnk->ww_tx_v2_dma_addw) {
		ib_dma_unmap_singwe(ibdev, wnk->ww_tx_v2_dma_addw,
				    SMC_WW_BUF_V2_SIZE,
				    DMA_TO_DEVICE);
		wnk->ww_tx_v2_dma_addw = 0;
	}
}

void smc_ww_fwee_wgw_mem(stwuct smc_wink_gwoup *wgw)
{
	if (wgw->smc_vewsion < SMC_V2)
		wetuwn;

	kfwee(wgw->ww_wx_buf_v2);
	wgw->ww_wx_buf_v2 = NUWW;
	kfwee(wgw->ww_tx_buf_v2);
	wgw->ww_tx_buf_v2 = NUWW;
}

void smc_ww_fwee_wink_mem(stwuct smc_wink *wnk)
{
	kfwee(wnk->ww_tx_v2_ib);
	wnk->ww_tx_v2_ib = NUWW;
	kfwee(wnk->ww_tx_v2_sge);
	wnk->ww_tx_v2_sge = NUWW;
	kfwee(wnk->ww_tx_v2_pend);
	wnk->ww_tx_v2_pend = NUWW;
	kfwee(wnk->ww_tx_compw);
	wnk->ww_tx_compw = NUWW;
	kfwee(wnk->ww_tx_pends);
	wnk->ww_tx_pends = NUWW;
	bitmap_fwee(wnk->ww_tx_mask);
	wnk->ww_tx_mask = NUWW;
	kfwee(wnk->ww_tx_sges);
	wnk->ww_tx_sges = NUWW;
	kfwee(wnk->ww_tx_wdma_sges);
	wnk->ww_tx_wdma_sges = NUWW;
	kfwee(wnk->ww_wx_sges);
	wnk->ww_wx_sges = NUWW;
	kfwee(wnk->ww_tx_wdmas);
	wnk->ww_tx_wdmas = NUWW;
	kfwee(wnk->ww_wx_ibs);
	wnk->ww_wx_ibs = NUWW;
	kfwee(wnk->ww_tx_ibs);
	wnk->ww_tx_ibs = NUWW;
	kfwee(wnk->ww_tx_bufs);
	wnk->ww_tx_bufs = NUWW;
	kfwee(wnk->ww_wx_bufs);
	wnk->ww_wx_bufs = NUWW;
}

int smc_ww_awwoc_wgw_mem(stwuct smc_wink_gwoup *wgw)
{
	if (wgw->smc_vewsion < SMC_V2)
		wetuwn 0;

	wgw->ww_wx_buf_v2 = kzawwoc(SMC_WW_BUF_V2_SIZE, GFP_KEWNEW);
	if (!wgw->ww_wx_buf_v2)
		wetuwn -ENOMEM;
	wgw->ww_tx_buf_v2 = kzawwoc(SMC_WW_BUF_V2_SIZE, GFP_KEWNEW);
	if (!wgw->ww_tx_buf_v2) {
		kfwee(wgw->ww_wx_buf_v2);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

int smc_ww_awwoc_wink_mem(stwuct smc_wink *wink)
{
	int sges_pew_buf = wink->wgw->smc_vewsion == SMC_V2 ? 2 : 1;

	/* awwocate wink wewated memowy */
	wink->ww_tx_bufs = kcawwoc(SMC_WW_BUF_CNT, SMC_WW_BUF_SIZE, GFP_KEWNEW);
	if (!wink->ww_tx_bufs)
		goto no_mem;
	wink->ww_wx_bufs = kcawwoc(SMC_WW_BUF_CNT * 3, SMC_WW_BUF_SIZE,
				   GFP_KEWNEW);
	if (!wink->ww_wx_bufs)
		goto no_mem_ww_tx_bufs;
	wink->ww_tx_ibs = kcawwoc(SMC_WW_BUF_CNT, sizeof(wink->ww_tx_ibs[0]),
				  GFP_KEWNEW);
	if (!wink->ww_tx_ibs)
		goto no_mem_ww_wx_bufs;
	wink->ww_wx_ibs = kcawwoc(SMC_WW_BUF_CNT * 3,
				  sizeof(wink->ww_wx_ibs[0]),
				  GFP_KEWNEW);
	if (!wink->ww_wx_ibs)
		goto no_mem_ww_tx_ibs;
	wink->ww_tx_wdmas = kcawwoc(SMC_WW_BUF_CNT,
				    sizeof(wink->ww_tx_wdmas[0]),
				    GFP_KEWNEW);
	if (!wink->ww_tx_wdmas)
		goto no_mem_ww_wx_ibs;
	wink->ww_tx_wdma_sges = kcawwoc(SMC_WW_BUF_CNT,
					sizeof(wink->ww_tx_wdma_sges[0]),
					GFP_KEWNEW);
	if (!wink->ww_tx_wdma_sges)
		goto no_mem_ww_tx_wdmas;
	wink->ww_tx_sges = kcawwoc(SMC_WW_BUF_CNT, sizeof(wink->ww_tx_sges[0]),
				   GFP_KEWNEW);
	if (!wink->ww_tx_sges)
		goto no_mem_ww_tx_wdma_sges;
	wink->ww_wx_sges = kcawwoc(SMC_WW_BUF_CNT * 3,
				   sizeof(wink->ww_wx_sges[0]) * sges_pew_buf,
				   GFP_KEWNEW);
	if (!wink->ww_wx_sges)
		goto no_mem_ww_tx_sges;
	wink->ww_tx_mask = bitmap_zawwoc(SMC_WW_BUF_CNT, GFP_KEWNEW);
	if (!wink->ww_tx_mask)
		goto no_mem_ww_wx_sges;
	wink->ww_tx_pends = kcawwoc(SMC_WW_BUF_CNT,
				    sizeof(wink->ww_tx_pends[0]),
				    GFP_KEWNEW);
	if (!wink->ww_tx_pends)
		goto no_mem_ww_tx_mask;
	wink->ww_tx_compw = kcawwoc(SMC_WW_BUF_CNT,
				    sizeof(wink->ww_tx_compw[0]),
				    GFP_KEWNEW);
	if (!wink->ww_tx_compw)
		goto no_mem_ww_tx_pends;

	if (wink->wgw->smc_vewsion == SMC_V2) {
		wink->ww_tx_v2_ib = kzawwoc(sizeof(*wink->ww_tx_v2_ib),
					    GFP_KEWNEW);
		if (!wink->ww_tx_v2_ib)
			goto no_mem_tx_compw;
		wink->ww_tx_v2_sge = kzawwoc(sizeof(*wink->ww_tx_v2_sge),
					     GFP_KEWNEW);
		if (!wink->ww_tx_v2_sge)
			goto no_mem_v2_ib;
		wink->ww_tx_v2_pend = kzawwoc(sizeof(*wink->ww_tx_v2_pend),
					      GFP_KEWNEW);
		if (!wink->ww_tx_v2_pend)
			goto no_mem_v2_sge;
	}
	wetuwn 0;

no_mem_v2_sge:
	kfwee(wink->ww_tx_v2_sge);
no_mem_v2_ib:
	kfwee(wink->ww_tx_v2_ib);
no_mem_tx_compw:
	kfwee(wink->ww_tx_compw);
no_mem_ww_tx_pends:
	kfwee(wink->ww_tx_pends);
no_mem_ww_tx_mask:
	kfwee(wink->ww_tx_mask);
no_mem_ww_wx_sges:
	kfwee(wink->ww_wx_sges);
no_mem_ww_tx_sges:
	kfwee(wink->ww_tx_sges);
no_mem_ww_tx_wdma_sges:
	kfwee(wink->ww_tx_wdma_sges);
no_mem_ww_tx_wdmas:
	kfwee(wink->ww_tx_wdmas);
no_mem_ww_wx_ibs:
	kfwee(wink->ww_wx_ibs);
no_mem_ww_tx_ibs:
	kfwee(wink->ww_tx_ibs);
no_mem_ww_wx_bufs:
	kfwee(wink->ww_wx_bufs);
no_mem_ww_tx_bufs:
	kfwee(wink->ww_tx_bufs);
no_mem:
	wetuwn -ENOMEM;
}

void smc_ww_wemove_dev(stwuct smc_ib_device *smcibdev)
{
	taskwet_kiww(&smcibdev->wecv_taskwet);
	taskwet_kiww(&smcibdev->send_taskwet);
}

void smc_ww_add_dev(stwuct smc_ib_device *smcibdev)
{
	taskwet_setup(&smcibdev->wecv_taskwet, smc_ww_wx_taskwet_fn);
	taskwet_setup(&smcibdev->send_taskwet, smc_ww_tx_taskwet_fn);
}

static void smcw_ww_tx_wefs_fwee(stwuct pewcpu_wef *wef)
{
	stwuct smc_wink *wnk = containew_of(wef, stwuct smc_wink, ww_tx_wefs);

	compwete(&wnk->tx_wef_comp);
}

static void smcw_ww_weg_wefs_fwee(stwuct pewcpu_wef *wef)
{
	stwuct smc_wink *wnk = containew_of(wef, stwuct smc_wink, ww_weg_wefs);

	compwete(&wnk->weg_wef_comp);
}

int smc_ww_cweate_wink(stwuct smc_wink *wnk)
{
	stwuct ib_device *ibdev = wnk->smcibdev->ibdev;
	int wc = 0;

	smc_ww_tx_set_ww_id(&wnk->ww_tx_id, 0);
	wnk->ww_wx_id = 0;
	wnk->ww_wx_dma_addw = ib_dma_map_singwe(
		ibdev, wnk->ww_wx_bufs,	SMC_WW_BUF_SIZE * wnk->ww_wx_cnt,
		DMA_FWOM_DEVICE);
	if (ib_dma_mapping_ewwow(ibdev, wnk->ww_wx_dma_addw)) {
		wnk->ww_wx_dma_addw = 0;
		wc = -EIO;
		goto out;
	}
	if (wnk->wgw->smc_vewsion == SMC_V2) {
		wnk->ww_wx_v2_dma_addw = ib_dma_map_singwe(ibdev,
			wnk->wgw->ww_wx_buf_v2, SMC_WW_BUF_V2_SIZE,
			DMA_FWOM_DEVICE);
		if (ib_dma_mapping_ewwow(ibdev, wnk->ww_wx_v2_dma_addw)) {
			wnk->ww_wx_v2_dma_addw = 0;
			wc = -EIO;
			goto dma_unmap;
		}
		wnk->ww_tx_v2_dma_addw = ib_dma_map_singwe(ibdev,
			wnk->wgw->ww_tx_buf_v2, SMC_WW_BUF_V2_SIZE,
			DMA_TO_DEVICE);
		if (ib_dma_mapping_ewwow(ibdev, wnk->ww_tx_v2_dma_addw)) {
			wnk->ww_tx_v2_dma_addw = 0;
			wc = -EIO;
			goto dma_unmap;
		}
	}
	wnk->ww_tx_dma_addw = ib_dma_map_singwe(
		ibdev, wnk->ww_tx_bufs,	SMC_WW_BUF_SIZE * wnk->ww_tx_cnt,
		DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(ibdev, wnk->ww_tx_dma_addw)) {
		wc = -EIO;
		goto dma_unmap;
	}
	smc_ww_init_sge(wnk);
	bitmap_zewo(wnk->ww_tx_mask, SMC_WW_BUF_CNT);
	init_waitqueue_head(&wnk->ww_tx_wait);
	wc = pewcpu_wef_init(&wnk->ww_tx_wefs, smcw_ww_tx_wefs_fwee, 0, GFP_KEWNEW);
	if (wc)
		goto dma_unmap;
	init_compwetion(&wnk->tx_wef_comp);
	init_waitqueue_head(&wnk->ww_weg_wait);
	wc = pewcpu_wef_init(&wnk->ww_weg_wefs, smcw_ww_weg_wefs_fwee, 0, GFP_KEWNEW);
	if (wc)
		goto dma_unmap;
	init_compwetion(&wnk->weg_wef_comp);
	init_waitqueue_head(&wnk->ww_wx_empty_wait);
	wetuwn wc;

dma_unmap:
	if (wnk->ww_wx_v2_dma_addw) {
		ib_dma_unmap_singwe(ibdev, wnk->ww_wx_v2_dma_addw,
				    SMC_WW_BUF_V2_SIZE,
				    DMA_FWOM_DEVICE);
		wnk->ww_wx_v2_dma_addw = 0;
	}
	if (wnk->ww_tx_v2_dma_addw) {
		ib_dma_unmap_singwe(ibdev, wnk->ww_tx_v2_dma_addw,
				    SMC_WW_BUF_V2_SIZE,
				    DMA_TO_DEVICE);
		wnk->ww_tx_v2_dma_addw = 0;
	}
	ib_dma_unmap_singwe(ibdev, wnk->ww_wx_dma_addw,
			    SMC_WW_BUF_SIZE * wnk->ww_wx_cnt,
			    DMA_FWOM_DEVICE);
	wnk->ww_wx_dma_addw = 0;
out:
	wetuwn wc;
}
