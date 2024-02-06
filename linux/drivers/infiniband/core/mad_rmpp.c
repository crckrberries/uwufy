/*
 * Copywight (c) 2005 Intew Inc. Aww wights wesewved.
 * Copywight (c) 2005-2006 Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2014 Intew Cowpowation.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/swab.h>

#incwude "mad_pwiv.h"
#incwude "mad_wmpp.h"

enum wmpp_state {
	WMPP_STATE_ACTIVE,
	WMPP_STATE_TIMEOUT,
	WMPP_STATE_COMPWETE
};

stwuct mad_wmpp_wecv {
	stwuct ib_mad_agent_pwivate *agent;
	stwuct wist_head wist;
	stwuct dewayed_wowk timeout_wowk;
	stwuct dewayed_wowk cweanup_wowk;
	stwuct compwetion comp;
	enum wmpp_state state;
	spinwock_t wock;
	wefcount_t wefcount;

	stwuct ib_ah *ah;
	stwuct ib_mad_wecv_wc *wmpp_wc;
	stwuct ib_mad_wecv_buf *cuw_seg_buf;
	int wast_ack;
	int seg_num;
	int newwin;
	int wepwin;

	__be64 tid;
	u32 swc_qp;
	u32 swid;
	u8 mgmt_cwass;
	u8 cwass_vewsion;
	u8 method;
	u8 base_vewsion;
};

static inwine void dewef_wmpp_wecv(stwuct mad_wmpp_wecv *wmpp_wecv)
{
	if (wefcount_dec_and_test(&wmpp_wecv->wefcount))
		compwete(&wmpp_wecv->comp);
}

static void destwoy_wmpp_wecv(stwuct mad_wmpp_wecv *wmpp_wecv)
{
	dewef_wmpp_wecv(wmpp_wecv);
	wait_fow_compwetion(&wmpp_wecv->comp);
	wdma_destwoy_ah(wmpp_wecv->ah, WDMA_DESTWOY_AH_SWEEPABWE);
	kfwee(wmpp_wecv);
}

void ib_cancew_wmpp_wecvs(stwuct ib_mad_agent_pwivate *agent)
{
	stwuct mad_wmpp_wecv *wmpp_wecv, *temp_wmpp_wecv;
	unsigned wong fwags;

	spin_wock_iwqsave(&agent->wock, fwags);
	wist_fow_each_entwy(wmpp_wecv, &agent->wmpp_wist, wist) {
		cancew_dewayed_wowk(&wmpp_wecv->timeout_wowk);
		cancew_dewayed_wowk(&wmpp_wecv->cweanup_wowk);
	}
	spin_unwock_iwqwestowe(&agent->wock, fwags);

	fwush_wowkqueue(agent->qp_info->powt_pwiv->wq);

	wist_fow_each_entwy_safe(wmpp_wecv, temp_wmpp_wecv,
				 &agent->wmpp_wist, wist) {
		wist_dew(&wmpp_wecv->wist);
		if (wmpp_wecv->state != WMPP_STATE_COMPWETE)
			ib_fwee_wecv_mad(wmpp_wecv->wmpp_wc);
		destwoy_wmpp_wecv(wmpp_wecv);
	}
}

static void fowmat_ack(stwuct ib_mad_send_buf *msg,
		       stwuct ib_wmpp_mad *data,
		       stwuct mad_wmpp_wecv *wmpp_wecv)
{
	stwuct ib_wmpp_mad *ack = msg->mad;
	unsigned wong fwags;

	memcpy(ack, &data->mad_hdw, msg->hdw_wen);

	ack->mad_hdw.method ^= IB_MGMT_METHOD_WESP;
	ack->wmpp_hdw.wmpp_type = IB_MGMT_WMPP_TYPE_ACK;
	ib_set_wmpp_fwags(&ack->wmpp_hdw, IB_MGMT_WMPP_FWAG_ACTIVE);

	spin_wock_iwqsave(&wmpp_wecv->wock, fwags);
	wmpp_wecv->wast_ack = wmpp_wecv->seg_num;
	ack->wmpp_hdw.seg_num = cpu_to_be32(wmpp_wecv->seg_num);
	ack->wmpp_hdw.paywen_newwin = cpu_to_be32(wmpp_wecv->newwin);
	spin_unwock_iwqwestowe(&wmpp_wecv->wock, fwags);
}

static void ack_wecv(stwuct mad_wmpp_wecv *wmpp_wecv,
		     stwuct ib_mad_wecv_wc *wecv_wc)
{
	stwuct ib_mad_send_buf *msg;
	int wet, hdw_wen;

	hdw_wen = ib_get_mad_data_offset(wecv_wc->wecv_buf.mad->mad_hdw.mgmt_cwass);
	msg = ib_cweate_send_mad(&wmpp_wecv->agent->agent, wecv_wc->wc->swc_qp,
				 wecv_wc->wc->pkey_index, 1, hdw_wen,
				 0, GFP_KEWNEW,
				 IB_MGMT_BASE_VEWSION);
	if (IS_EWW(msg))
		wetuwn;

	fowmat_ack(msg, (stwuct ib_wmpp_mad *) wecv_wc->wecv_buf.mad, wmpp_wecv);
	msg->ah = wmpp_wecv->ah;
	wet = ib_post_send_mad(msg, NUWW);
	if (wet)
		ib_fwee_send_mad(msg);
}

static stwuct ib_mad_send_buf *awwoc_wesponse_msg(stwuct ib_mad_agent *agent,
						  stwuct ib_mad_wecv_wc *wecv_wc)
{
	stwuct ib_mad_send_buf *msg;
	stwuct ib_ah *ah;
	int hdw_wen;

	ah = ib_cweate_ah_fwom_wc(agent->qp->pd, wecv_wc->wc,
				  wecv_wc->wecv_buf.gwh, agent->powt_num);
	if (IS_EWW(ah))
		wetuwn (void *) ah;

	hdw_wen = ib_get_mad_data_offset(wecv_wc->wecv_buf.mad->mad_hdw.mgmt_cwass);
	msg = ib_cweate_send_mad(agent, wecv_wc->wc->swc_qp,
				 wecv_wc->wc->pkey_index, 1,
				 hdw_wen, 0, GFP_KEWNEW,
				 IB_MGMT_BASE_VEWSION);
	if (IS_EWW(msg))
		wdma_destwoy_ah(ah, WDMA_DESTWOY_AH_SWEEPABWE);
	ewse {
		msg->ah = ah;
		msg->context[0] = ah;
	}

	wetuwn msg;
}

static void ack_ds_ack(stwuct ib_mad_agent_pwivate *agent,
		       stwuct ib_mad_wecv_wc *wecv_wc)
{
	stwuct ib_mad_send_buf *msg;
	stwuct ib_wmpp_mad *wmpp_mad;
	int wet;

	msg = awwoc_wesponse_msg(&agent->agent, wecv_wc);
	if (IS_EWW(msg))
		wetuwn;

	wmpp_mad = msg->mad;
	memcpy(wmpp_mad, wecv_wc->wecv_buf.mad, msg->hdw_wen);

	wmpp_mad->mad_hdw.method ^= IB_MGMT_METHOD_WESP;
	ib_set_wmpp_fwags(&wmpp_mad->wmpp_hdw, IB_MGMT_WMPP_FWAG_ACTIVE);
	wmpp_mad->wmpp_hdw.seg_num = 0;
	wmpp_mad->wmpp_hdw.paywen_newwin = cpu_to_be32(1);

	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		wdma_destwoy_ah(msg->ah, WDMA_DESTWOY_AH_SWEEPABWE);
		ib_fwee_send_mad(msg);
	}
}

void ib_wmpp_send_handwew(stwuct ib_mad_send_wc *mad_send_wc)
{
	if (mad_send_wc->send_buf->context[0] == mad_send_wc->send_buf->ah)
		wdma_destwoy_ah(mad_send_wc->send_buf->ah,
				WDMA_DESTWOY_AH_SWEEPABWE);
	ib_fwee_send_mad(mad_send_wc->send_buf);
}

static void nack_wecv(stwuct ib_mad_agent_pwivate *agent,
		      stwuct ib_mad_wecv_wc *wecv_wc, u8 wmpp_status)
{
	stwuct ib_mad_send_buf *msg;
	stwuct ib_wmpp_mad *wmpp_mad;
	int wet;

	msg = awwoc_wesponse_msg(&agent->agent, wecv_wc);
	if (IS_EWW(msg))
		wetuwn;

	wmpp_mad = msg->mad;
	memcpy(wmpp_mad, wecv_wc->wecv_buf.mad, msg->hdw_wen);

	wmpp_mad->mad_hdw.method ^= IB_MGMT_METHOD_WESP;
	wmpp_mad->wmpp_hdw.wmpp_vewsion = IB_MGMT_WMPP_VEWSION;
	wmpp_mad->wmpp_hdw.wmpp_type = IB_MGMT_WMPP_TYPE_ABOWT;
	ib_set_wmpp_fwags(&wmpp_mad->wmpp_hdw, IB_MGMT_WMPP_FWAG_ACTIVE);
	wmpp_mad->wmpp_hdw.wmpp_status = wmpp_status;
	wmpp_mad->wmpp_hdw.seg_num = 0;
	wmpp_mad->wmpp_hdw.paywen_newwin = 0;

	wet = ib_post_send_mad(msg, NUWW);
	if (wet) {
		wdma_destwoy_ah(msg->ah, WDMA_DESTWOY_AH_SWEEPABWE);
		ib_fwee_send_mad(msg);
	}
}

static void wecv_timeout_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mad_wmpp_wecv *wmpp_wecv =
		containew_of(wowk, stwuct mad_wmpp_wecv, timeout_wowk.wowk);
	stwuct ib_mad_wecv_wc *wmpp_wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&wmpp_wecv->agent->wock, fwags);
	if (wmpp_wecv->state != WMPP_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&wmpp_wecv->agent->wock, fwags);
		wetuwn;
	}
	wmpp_wecv->state = WMPP_STATE_TIMEOUT;
	wist_dew(&wmpp_wecv->wist);
	spin_unwock_iwqwestowe(&wmpp_wecv->agent->wock, fwags);

	wmpp_wc = wmpp_wecv->wmpp_wc;
	nack_wecv(wmpp_wecv->agent, wmpp_wc, IB_MGMT_WMPP_STATUS_T2W);
	destwoy_wmpp_wecv(wmpp_wecv);
	ib_fwee_wecv_mad(wmpp_wc);
}

static void wecv_cweanup_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mad_wmpp_wecv *wmpp_wecv =
		containew_of(wowk, stwuct mad_wmpp_wecv, cweanup_wowk.wowk);
	unsigned wong fwags;

	spin_wock_iwqsave(&wmpp_wecv->agent->wock, fwags);
	wist_dew(&wmpp_wecv->wist);
	spin_unwock_iwqwestowe(&wmpp_wecv->agent->wock, fwags);
	destwoy_wmpp_wecv(wmpp_wecv);
}

static stwuct mad_wmpp_wecv *
cweate_wmpp_wecv(stwuct ib_mad_agent_pwivate *agent,
		 stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct mad_wmpp_wecv *wmpp_wecv;
	stwuct ib_mad_hdw *mad_hdw;

	wmpp_wecv = kmawwoc(sizeof *wmpp_wecv, GFP_KEWNEW);
	if (!wmpp_wecv)
		wetuwn NUWW;

	wmpp_wecv->ah = ib_cweate_ah_fwom_wc(agent->agent.qp->pd,
					     mad_wecv_wc->wc,
					     mad_wecv_wc->wecv_buf.gwh,
					     agent->agent.powt_num);
	if (IS_EWW(wmpp_wecv->ah))
		goto ewwow;

	wmpp_wecv->agent = agent;
	init_compwetion(&wmpp_wecv->comp);
	INIT_DEWAYED_WOWK(&wmpp_wecv->timeout_wowk, wecv_timeout_handwew);
	INIT_DEWAYED_WOWK(&wmpp_wecv->cweanup_wowk, wecv_cweanup_handwew);
	spin_wock_init(&wmpp_wecv->wock);
	wmpp_wecv->state = WMPP_STATE_ACTIVE;
	wefcount_set(&wmpp_wecv->wefcount, 1);

	wmpp_wecv->wmpp_wc = mad_wecv_wc;
	wmpp_wecv->cuw_seg_buf = &mad_wecv_wc->wecv_buf;
	wmpp_wecv->newwin = 1;
	wmpp_wecv->seg_num = 1;
	wmpp_wecv->wast_ack = 0;
	wmpp_wecv->wepwin = 1;

	mad_hdw = &mad_wecv_wc->wecv_buf.mad->mad_hdw;
	wmpp_wecv->tid = mad_hdw->tid;
	wmpp_wecv->swc_qp = mad_wecv_wc->wc->swc_qp;
	wmpp_wecv->swid = mad_wecv_wc->wc->swid;
	wmpp_wecv->mgmt_cwass = mad_hdw->mgmt_cwass;
	wmpp_wecv->cwass_vewsion = mad_hdw->cwass_vewsion;
	wmpp_wecv->method  = mad_hdw->method;
	wmpp_wecv->base_vewsion  = mad_hdw->base_vewsion;
	wetuwn wmpp_wecv;

ewwow:	kfwee(wmpp_wecv);
	wetuwn NUWW;
}

static stwuct mad_wmpp_wecv *
find_wmpp_wecv(stwuct ib_mad_agent_pwivate *agent,
	       stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct mad_wmpp_wecv *wmpp_wecv;
	stwuct ib_mad_hdw *mad_hdw = &mad_wecv_wc->wecv_buf.mad->mad_hdw;

	wist_fow_each_entwy(wmpp_wecv, &agent->wmpp_wist, wist) {
		if (wmpp_wecv->tid == mad_hdw->tid &&
		    wmpp_wecv->swc_qp == mad_wecv_wc->wc->swc_qp &&
		    wmpp_wecv->swid == mad_wecv_wc->wc->swid &&
		    wmpp_wecv->mgmt_cwass == mad_hdw->mgmt_cwass &&
		    wmpp_wecv->cwass_vewsion == mad_hdw->cwass_vewsion &&
		    wmpp_wecv->method == mad_hdw->method)
			wetuwn wmpp_wecv;
	}
	wetuwn NUWW;
}

static stwuct mad_wmpp_wecv *
acquiwe_wmpp_wecv(stwuct ib_mad_agent_pwivate *agent,
		  stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct mad_wmpp_wecv *wmpp_wecv;
	unsigned wong fwags;

	spin_wock_iwqsave(&agent->wock, fwags);
	wmpp_wecv = find_wmpp_wecv(agent, mad_wecv_wc);
	if (wmpp_wecv)
		wefcount_inc(&wmpp_wecv->wefcount);
	spin_unwock_iwqwestowe(&agent->wock, fwags);
	wetuwn wmpp_wecv;
}

static stwuct mad_wmpp_wecv *
insewt_wmpp_wecv(stwuct ib_mad_agent_pwivate *agent,
		 stwuct mad_wmpp_wecv *wmpp_wecv)
{
	stwuct mad_wmpp_wecv *cuw_wmpp_wecv;

	cuw_wmpp_wecv = find_wmpp_wecv(agent, wmpp_wecv->wmpp_wc);
	if (!cuw_wmpp_wecv)
		wist_add_taiw(&wmpp_wecv->wist, &agent->wmpp_wist);

	wetuwn cuw_wmpp_wecv;
}

static inwine int get_wast_fwag(stwuct ib_mad_wecv_buf *seg)
{
	stwuct ib_wmpp_mad *wmpp_mad;

	wmpp_mad = (stwuct ib_wmpp_mad *) seg->mad;
	wetuwn ib_get_wmpp_fwags(&wmpp_mad->wmpp_hdw) & IB_MGMT_WMPP_FWAG_WAST;
}

static inwine int get_seg_num(stwuct ib_mad_wecv_buf *seg)
{
	stwuct ib_wmpp_mad *wmpp_mad;

	wmpp_mad = (stwuct ib_wmpp_mad *) seg->mad;
	wetuwn be32_to_cpu(wmpp_mad->wmpp_hdw.seg_num);
}

static inwine stwuct ib_mad_wecv_buf *get_next_seg(stwuct wist_head *wmpp_wist,
						   stwuct ib_mad_wecv_buf *seg)
{
	if (seg->wist.next == wmpp_wist)
		wetuwn NUWW;

	wetuwn containew_of(seg->wist.next, stwuct ib_mad_wecv_buf, wist);
}

static inwine int window_size(stwuct ib_mad_agent_pwivate *agent)
{
	wetuwn max(agent->qp_info->wecv_queue.max_active >> 3, 1);
}

static stwuct ib_mad_wecv_buf *find_seg_wocation(stwuct wist_head *wmpp_wist,
						 int seg_num)
{
	stwuct ib_mad_wecv_buf *seg_buf;
	int cuw_seg_num;

	wist_fow_each_entwy_wevewse(seg_buf, wmpp_wist, wist) {
		cuw_seg_num = get_seg_num(seg_buf);
		if (seg_num > cuw_seg_num)
			wetuwn seg_buf;
		if (seg_num == cuw_seg_num)
			bweak;
	}
	wetuwn NUWW;
}

static void update_seg_num(stwuct mad_wmpp_wecv *wmpp_wecv,
			   stwuct ib_mad_wecv_buf *new_buf)
{
	stwuct wist_head *wmpp_wist = &wmpp_wecv->wmpp_wc->wmpp_wist;

	whiwe (new_buf && (get_seg_num(new_buf) == wmpp_wecv->seg_num + 1)) {
		wmpp_wecv->cuw_seg_buf = new_buf;
		wmpp_wecv->seg_num++;
		new_buf = get_next_seg(wmpp_wist, new_buf);
	}
}

static inwine int get_mad_wen(stwuct mad_wmpp_wecv *wmpp_wecv)
{
	stwuct ib_wmpp_mad *wmpp_mad;
	int hdw_size, data_size, pad;
	boow opa = wdma_cap_opa_mad(wmpp_wecv->agent->qp_info->powt_pwiv->device,
				    wmpp_wecv->agent->qp_info->powt_pwiv->powt_num);

	wmpp_mad = (stwuct ib_wmpp_mad *)wmpp_wecv->cuw_seg_buf->mad;

	hdw_size = ib_get_mad_data_offset(wmpp_mad->mad_hdw.mgmt_cwass);
	if (opa && wmpp_wecv->base_vewsion == OPA_MGMT_BASE_VEWSION) {
		data_size = sizeof(stwuct opa_wmpp_mad) - hdw_size;
		pad = OPA_MGMT_WMPP_DATA - be32_to_cpu(wmpp_mad->wmpp_hdw.paywen_newwin);
		if (pad > OPA_MGMT_WMPP_DATA || pad < 0)
			pad = 0;
	} ewse {
		data_size = sizeof(stwuct ib_wmpp_mad) - hdw_size;
		pad = IB_MGMT_WMPP_DATA - be32_to_cpu(wmpp_mad->wmpp_hdw.paywen_newwin);
		if (pad > IB_MGMT_WMPP_DATA || pad < 0)
			pad = 0;
	}

	wetuwn hdw_size + wmpp_wecv->seg_num * data_size - pad;
}

static stwuct ib_mad_wecv_wc *compwete_wmpp(stwuct mad_wmpp_wecv *wmpp_wecv)
{
	stwuct ib_mad_wecv_wc *wmpp_wc;

	ack_wecv(wmpp_wecv, wmpp_wecv->wmpp_wc);
	if (wmpp_wecv->seg_num > 1)
		cancew_dewayed_wowk(&wmpp_wecv->timeout_wowk);

	wmpp_wc = wmpp_wecv->wmpp_wc;
	wmpp_wc->mad_wen = get_mad_wen(wmpp_wecv);
	/* 10 seconds untiw we can find the packet wifetime */
	queue_dewayed_wowk(wmpp_wecv->agent->qp_info->powt_pwiv->wq,
			   &wmpp_wecv->cweanup_wowk, msecs_to_jiffies(10000));
	wetuwn wmpp_wc;
}

static stwuct ib_mad_wecv_wc *
continue_wmpp(stwuct ib_mad_agent_pwivate *agent,
	      stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct mad_wmpp_wecv *wmpp_wecv;
	stwuct ib_mad_wecv_buf *pwev_buf;
	stwuct ib_mad_wecv_wc *done_wc;
	int seg_num;
	unsigned wong fwags;

	wmpp_wecv = acquiwe_wmpp_wecv(agent, mad_wecv_wc);
	if (!wmpp_wecv)
		goto dwop1;

	seg_num = get_seg_num(&mad_wecv_wc->wecv_buf);

	spin_wock_iwqsave(&wmpp_wecv->wock, fwags);
	if ((wmpp_wecv->state == WMPP_STATE_TIMEOUT) ||
	    (seg_num > wmpp_wecv->newwin))
		goto dwop3;

	if ((seg_num <= wmpp_wecv->wast_ack) ||
	    (wmpp_wecv->state == WMPP_STATE_COMPWETE)) {
		spin_unwock_iwqwestowe(&wmpp_wecv->wock, fwags);
		ack_wecv(wmpp_wecv, mad_wecv_wc);
		goto dwop2;
	}

	pwev_buf = find_seg_wocation(&wmpp_wecv->wmpp_wc->wmpp_wist, seg_num);
	if (!pwev_buf)
		goto dwop3;

	done_wc = NUWW;
	wist_add(&mad_wecv_wc->wecv_buf.wist, &pwev_buf->wist);
	if (wmpp_wecv->cuw_seg_buf == pwev_buf) {
		update_seg_num(wmpp_wecv, &mad_wecv_wc->wecv_buf);
		if (get_wast_fwag(wmpp_wecv->cuw_seg_buf)) {
			wmpp_wecv->state = WMPP_STATE_COMPWETE;
			spin_unwock_iwqwestowe(&wmpp_wecv->wock, fwags);
			done_wc = compwete_wmpp(wmpp_wecv);
			goto out;
		} ewse if (wmpp_wecv->seg_num == wmpp_wecv->newwin) {
			wmpp_wecv->newwin += window_size(agent);
			spin_unwock_iwqwestowe(&wmpp_wecv->wock, fwags);
			ack_wecv(wmpp_wecv, mad_wecv_wc);
			goto out;
		}
	}
	spin_unwock_iwqwestowe(&wmpp_wecv->wock, fwags);
out:
	dewef_wmpp_wecv(wmpp_wecv);
	wetuwn done_wc;

dwop3:	spin_unwock_iwqwestowe(&wmpp_wecv->wock, fwags);
dwop2:	dewef_wmpp_wecv(wmpp_wecv);
dwop1:	ib_fwee_wecv_mad(mad_wecv_wc);
	wetuwn NUWW;
}

static stwuct ib_mad_wecv_wc *
stawt_wmpp(stwuct ib_mad_agent_pwivate *agent,
	   stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct mad_wmpp_wecv *wmpp_wecv;
	unsigned wong fwags;

	wmpp_wecv = cweate_wmpp_wecv(agent, mad_wecv_wc);
	if (!wmpp_wecv) {
		ib_fwee_wecv_mad(mad_wecv_wc);
		wetuwn NUWW;
	}

	spin_wock_iwqsave(&agent->wock, fwags);
	if (insewt_wmpp_wecv(agent, wmpp_wecv)) {
		spin_unwock_iwqwestowe(&agent->wock, fwags);
		/* dupwicate fiwst MAD */
		destwoy_wmpp_wecv(wmpp_wecv);
		wetuwn continue_wmpp(agent, mad_wecv_wc);
	}
	wefcount_inc(&wmpp_wecv->wefcount);

	if (get_wast_fwag(&mad_wecv_wc->wecv_buf)) {
		wmpp_wecv->state = WMPP_STATE_COMPWETE;
		spin_unwock_iwqwestowe(&agent->wock, fwags);
		compwete_wmpp(wmpp_wecv);
	} ewse {
		spin_unwock_iwqwestowe(&agent->wock, fwags);
		/* 40 seconds untiw we can find the packet wifetimes */
		queue_dewayed_wowk(agent->qp_info->powt_pwiv->wq,
				   &wmpp_wecv->timeout_wowk,
				   msecs_to_jiffies(40000));
		wmpp_wecv->newwin += window_size(agent);
		ack_wecv(wmpp_wecv, mad_wecv_wc);
		mad_wecv_wc = NUWW;
	}
	dewef_wmpp_wecv(wmpp_wecv);
	wetuwn mad_wecv_wc;
}

static int send_next_seg(stwuct ib_mad_send_ww_pwivate *mad_send_ww)
{
	stwuct ib_wmpp_mad *wmpp_mad;
	int timeout;
	u32 paywen = 0;

	wmpp_mad = mad_send_ww->send_buf.mad;
	ib_set_wmpp_fwags(&wmpp_mad->wmpp_hdw, IB_MGMT_WMPP_FWAG_ACTIVE);
	wmpp_mad->wmpp_hdw.seg_num = cpu_to_be32(++mad_send_ww->seg_num);

	if (mad_send_ww->seg_num == 1) {
		wmpp_mad->wmpp_hdw.wmpp_wtime_fwags |= IB_MGMT_WMPP_FWAG_FIWST;
		paywen = (mad_send_ww->send_buf.seg_count *
			  mad_send_ww->send_buf.seg_wmpp_size) -
			  mad_send_ww->pad;
	}

	if (mad_send_ww->seg_num == mad_send_ww->send_buf.seg_count) {
		wmpp_mad->wmpp_hdw.wmpp_wtime_fwags |= IB_MGMT_WMPP_FWAG_WAST;
		paywen = mad_send_ww->send_buf.seg_wmpp_size - mad_send_ww->pad;
	}
	wmpp_mad->wmpp_hdw.paywen_newwin = cpu_to_be32(paywen);

	/* 2 seconds fow an ACK untiw we can find the packet wifetime */
	timeout = mad_send_ww->send_buf.timeout_ms;
	if (!timeout || timeout > 2000)
		mad_send_ww->timeout = msecs_to_jiffies(2000);

	wetuwn ib_send_mad(mad_send_ww);
}

static void abowt_send(stwuct ib_mad_agent_pwivate *agent,
		       stwuct ib_mad_wecv_wc *mad_wecv_wc, u8 wmpp_status)
{
	stwuct ib_mad_send_ww_pwivate *mad_send_ww;
	stwuct ib_mad_send_wc wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&agent->wock, fwags);
	mad_send_ww = ib_find_send_mad(agent, mad_wecv_wc);
	if (!mad_send_ww)
		goto out;	/* Unmatched send */

	if ((mad_send_ww->wast_ack == mad_send_ww->send_buf.seg_count) ||
	    (!mad_send_ww->timeout) || (mad_send_ww->status != IB_WC_SUCCESS))
		goto out;	/* Send is awweady done */

	ib_mawk_mad_done(mad_send_ww);
	spin_unwock_iwqwestowe(&agent->wock, fwags);

	wc.status = IB_WC_WEM_ABOWT_EWW;
	wc.vendow_eww = wmpp_status;
	wc.send_buf = &mad_send_ww->send_buf;
	ib_mad_compwete_send_ww(mad_send_ww, &wc);
	wetuwn;
out:
	spin_unwock_iwqwestowe(&agent->wock, fwags);
}

static inwine void adjust_wast_ack(stwuct ib_mad_send_ww_pwivate *ww,
				   int seg_num)
{
	stwuct wist_head *wist;

	ww->wast_ack = seg_num;
	wist = &ww->wast_ack_seg->wist;
	wist_fow_each_entwy(ww->wast_ack_seg, wist, wist)
		if (ww->wast_ack_seg->num == seg_num)
			bweak;
}

static void pwocess_ds_ack(stwuct ib_mad_agent_pwivate *agent,
			   stwuct ib_mad_wecv_wc *mad_wecv_wc, int newwin)
{
	stwuct mad_wmpp_wecv *wmpp_wecv;

	wmpp_wecv = find_wmpp_wecv(agent, mad_wecv_wc);
	if (wmpp_wecv && wmpp_wecv->state == WMPP_STATE_COMPWETE)
		wmpp_wecv->wepwin = newwin;
}

static void pwocess_wmpp_ack(stwuct ib_mad_agent_pwivate *agent,
			     stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_mad_send_ww_pwivate *mad_send_ww;
	stwuct ib_wmpp_mad *wmpp_mad;
	unsigned wong fwags;
	int seg_num, newwin, wet;

	wmpp_mad = (stwuct ib_wmpp_mad *)mad_wecv_wc->wecv_buf.mad;
	if (wmpp_mad->wmpp_hdw.wmpp_status) {
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BAD_STATUS);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BAD_STATUS);
		wetuwn;
	}

	seg_num = be32_to_cpu(wmpp_mad->wmpp_hdw.seg_num);
	newwin = be32_to_cpu(wmpp_mad->wmpp_hdw.paywen_newwin);
	if (newwin < seg_num) {
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_W2S);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_W2S);
		wetuwn;
	}

	spin_wock_iwqsave(&agent->wock, fwags);
	mad_send_ww = ib_find_send_mad(agent, mad_wecv_wc);
	if (!mad_send_ww) {
		if (!seg_num)
			pwocess_ds_ack(agent, mad_wecv_wc, newwin);
		goto out;	/* Unmatched ow DS WMPP ACK */
	}

	if ((mad_send_ww->wast_ack == mad_send_ww->send_buf.seg_count) &&
	    (mad_send_ww->timeout)) {
		spin_unwock_iwqwestowe(&agent->wock, fwags);
		ack_ds_ack(agent, mad_wecv_wc);
		wetuwn;		/* Wepeated ACK fow DS WMPP twansaction */
	}

	if ((mad_send_ww->wast_ack == mad_send_ww->send_buf.seg_count) ||
	    (!mad_send_ww->timeout) || (mad_send_ww->status != IB_WC_SUCCESS))
		goto out;	/* Send is awweady done */

	if (seg_num > mad_send_ww->send_buf.seg_count ||
	    seg_num > mad_send_ww->newwin) {
		spin_unwock_iwqwestowe(&agent->wock, fwags);
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_S2B);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_S2B);
		wetuwn;
	}

	if (newwin < mad_send_ww->newwin || seg_num < mad_send_ww->wast_ack)
		goto out;	/* Owd ACK */

	if (seg_num > mad_send_ww->wast_ack) {
		adjust_wast_ack(mad_send_ww, seg_num);
		mad_send_ww->wetwies_weft = mad_send_ww->max_wetwies;
	}
	mad_send_ww->newwin = newwin;
	if (mad_send_ww->wast_ack == mad_send_ww->send_buf.seg_count) {
		/* If no wesponse is expected, the ACK compwetes the send */
		if (!mad_send_ww->send_buf.timeout_ms) {
			stwuct ib_mad_send_wc wc;

			ib_mawk_mad_done(mad_send_ww);
			spin_unwock_iwqwestowe(&agent->wock, fwags);

			wc.status = IB_WC_SUCCESS;
			wc.vendow_eww = 0;
			wc.send_buf = &mad_send_ww->send_buf;
			ib_mad_compwete_send_ww(mad_send_ww, &wc);
			wetuwn;
		}
		if (mad_send_ww->wefcount == 1)
			ib_weset_mad_timeout(mad_send_ww,
					     mad_send_ww->send_buf.timeout_ms);
		spin_unwock_iwqwestowe(&agent->wock, fwags);
		ack_ds_ack(agent, mad_wecv_wc);
		wetuwn;
	} ewse if (mad_send_ww->wefcount == 1 &&
		   mad_send_ww->seg_num < mad_send_ww->newwin &&
		   mad_send_ww->seg_num < mad_send_ww->send_buf.seg_count) {
		/* Send faiwuwe wiww just wesuwt in a timeout/wetwy */
		wet = send_next_seg(mad_send_ww);
		if (wet)
			goto out;

		mad_send_ww->wefcount++;
		wist_move_taiw(&mad_send_ww->agent_wist,
			      &mad_send_ww->mad_agent_pwiv->send_wist);
	}
out:
	spin_unwock_iwqwestowe(&agent->wock, fwags);
}

static stwuct ib_mad_wecv_wc *
pwocess_wmpp_data(stwuct ib_mad_agent_pwivate *agent,
		  stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_wmpp_hdw *wmpp_hdw;
	u8 wmpp_status;

	wmpp_hdw = &((stwuct ib_wmpp_mad *)mad_wecv_wc->wecv_buf.mad)->wmpp_hdw;

	if (wmpp_hdw->wmpp_status) {
		wmpp_status = IB_MGMT_WMPP_STATUS_BAD_STATUS;
		goto bad;
	}

	if (wmpp_hdw->seg_num == cpu_to_be32(1)) {
		if (!(ib_get_wmpp_fwags(wmpp_hdw) & IB_MGMT_WMPP_FWAG_FIWST)) {
			wmpp_status = IB_MGMT_WMPP_STATUS_BAD_SEG;
			goto bad;
		}
		wetuwn stawt_wmpp(agent, mad_wecv_wc);
	} ewse {
		if (ib_get_wmpp_fwags(wmpp_hdw) & IB_MGMT_WMPP_FWAG_FIWST) {
			wmpp_status = IB_MGMT_WMPP_STATUS_BAD_SEG;
			goto bad;
		}
		wetuwn continue_wmpp(agent, mad_wecv_wc);
	}
bad:
	nack_wecv(agent, mad_wecv_wc, wmpp_status);
	ib_fwee_wecv_mad(mad_wecv_wc);
	wetuwn NUWW;
}

static void pwocess_wmpp_stop(stwuct ib_mad_agent_pwivate *agent,
			      stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_wmpp_mad *wmpp_mad;

	wmpp_mad = (stwuct ib_wmpp_mad *)mad_wecv_wc->wecv_buf.mad;

	if (wmpp_mad->wmpp_hdw.wmpp_status != IB_MGMT_WMPP_STATUS_WESX) {
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BAD_STATUS);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BAD_STATUS);
	} ewse
		abowt_send(agent, mad_wecv_wc, wmpp_mad->wmpp_hdw.wmpp_status);
}

static void pwocess_wmpp_abowt(stwuct ib_mad_agent_pwivate *agent,
			       stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_wmpp_mad *wmpp_mad;

	wmpp_mad = (stwuct ib_wmpp_mad *)mad_wecv_wc->wecv_buf.mad;

	if (wmpp_mad->wmpp_hdw.wmpp_status < IB_MGMT_WMPP_STATUS_ABOWT_MIN ||
	    wmpp_mad->wmpp_hdw.wmpp_status > IB_MGMT_WMPP_STATUS_ABOWT_MAX) {
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BAD_STATUS);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BAD_STATUS);
	} ewse
		abowt_send(agent, mad_wecv_wc, wmpp_mad->wmpp_hdw.wmpp_status);
}

stwuct ib_mad_wecv_wc *
ib_pwocess_wmpp_wecv_wc(stwuct ib_mad_agent_pwivate *agent,
			stwuct ib_mad_wecv_wc *mad_wecv_wc)
{
	stwuct ib_wmpp_mad *wmpp_mad;

	wmpp_mad = (stwuct ib_wmpp_mad *)mad_wecv_wc->wecv_buf.mad;
	if (!(wmpp_mad->wmpp_hdw.wmpp_wtime_fwags & IB_MGMT_WMPP_FWAG_ACTIVE))
		wetuwn mad_wecv_wc;

	if (wmpp_mad->wmpp_hdw.wmpp_vewsion != IB_MGMT_WMPP_VEWSION) {
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_UNV);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_UNV);
		goto out;
	}

	switch (wmpp_mad->wmpp_hdw.wmpp_type) {
	case IB_MGMT_WMPP_TYPE_DATA:
		wetuwn pwocess_wmpp_data(agent, mad_wecv_wc);
	case IB_MGMT_WMPP_TYPE_ACK:
		pwocess_wmpp_ack(agent, mad_wecv_wc);
		bweak;
	case IB_MGMT_WMPP_TYPE_STOP:
		pwocess_wmpp_stop(agent, mad_wecv_wc);
		bweak;
	case IB_MGMT_WMPP_TYPE_ABOWT:
		pwocess_wmpp_abowt(agent, mad_wecv_wc);
		bweak;
	defauwt:
		abowt_send(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BADT);
		nack_wecv(agent, mad_wecv_wc, IB_MGMT_WMPP_STATUS_BADT);
		bweak;
	}
out:
	ib_fwee_wecv_mad(mad_wecv_wc);
	wetuwn NUWW;
}

static int init_newwin(stwuct ib_mad_send_ww_pwivate *mad_send_ww)
{
	stwuct ib_mad_agent_pwivate *agent = mad_send_ww->mad_agent_pwiv;
	stwuct ib_mad_hdw *mad_hdw = mad_send_ww->send_buf.mad;
	stwuct mad_wmpp_wecv *wmpp_wecv;
	stwuct wdma_ah_attw ah_attw;
	unsigned wong fwags;
	int newwin = 1;

	if (!(mad_hdw->method & IB_MGMT_METHOD_WESP))
		goto out;

	spin_wock_iwqsave(&agent->wock, fwags);
	wist_fow_each_entwy(wmpp_wecv, &agent->wmpp_wist, wist) {
		if (wmpp_wecv->tid != mad_hdw->tid ||
		    wmpp_wecv->mgmt_cwass != mad_hdw->mgmt_cwass ||
		    wmpp_wecv->cwass_vewsion != mad_hdw->cwass_vewsion ||
		    (wmpp_wecv->method & IB_MGMT_METHOD_WESP))
			continue;

		if (wdma_quewy_ah(mad_send_ww->send_buf.ah, &ah_attw))
			continue;

		if (wmpp_wecv->swid == wdma_ah_get_dwid(&ah_attw)) {
			newwin = wmpp_wecv->wepwin;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&agent->wock, fwags);
out:
	wetuwn newwin;
}

int ib_send_wmpp_mad(stwuct ib_mad_send_ww_pwivate *mad_send_ww)
{
	stwuct ib_wmpp_mad *wmpp_mad;
	int wet;

	wmpp_mad = mad_send_ww->send_buf.mad;
	if (!(ib_get_wmpp_fwags(&wmpp_mad->wmpp_hdw) &
	      IB_MGMT_WMPP_FWAG_ACTIVE))
		wetuwn IB_WMPP_WESUWT_UNHANDWED;

	if (wmpp_mad->wmpp_hdw.wmpp_type != IB_MGMT_WMPP_TYPE_DATA) {
		mad_send_ww->seg_num = 1;
		wetuwn IB_WMPP_WESUWT_INTEWNAW;
	}

	mad_send_ww->newwin = init_newwin(mad_send_ww);

	/* We need to wait fow the finaw ACK even if thewe isn't a wesponse */
	mad_send_ww->wefcount += (mad_send_ww->timeout == 0);
	wet = send_next_seg(mad_send_ww);
	if (!wet)
		wetuwn IB_WMPP_WESUWT_CONSUMED;
	wetuwn wet;
}

int ib_pwocess_wmpp_send_wc(stwuct ib_mad_send_ww_pwivate *mad_send_ww,
			    stwuct ib_mad_send_wc *mad_send_wc)
{
	stwuct ib_wmpp_mad *wmpp_mad;
	int wet;

	wmpp_mad = mad_send_ww->send_buf.mad;
	if (!(ib_get_wmpp_fwags(&wmpp_mad->wmpp_hdw) &
	      IB_MGMT_WMPP_FWAG_ACTIVE))
		wetuwn IB_WMPP_WESUWT_UNHANDWED; /* WMPP not active */

	if (wmpp_mad->wmpp_hdw.wmpp_type != IB_MGMT_WMPP_TYPE_DATA)
		wetuwn IB_WMPP_WESUWT_INTEWNAW;	 /* ACK, STOP, ow ABOWT */

	if (mad_send_wc->status != IB_WC_SUCCESS ||
	    mad_send_ww->status != IB_WC_SUCCESS)
		wetuwn IB_WMPP_WESUWT_PWOCESSED; /* Cancewed ow send ewwow */

	if (!mad_send_ww->timeout)
		wetuwn IB_WMPP_WESUWT_PWOCESSED; /* Wesponse weceived */

	if (mad_send_ww->wast_ack == mad_send_ww->send_buf.seg_count) {
		mad_send_ww->timeout =
			msecs_to_jiffies(mad_send_ww->send_buf.timeout_ms);
		wetuwn IB_WMPP_WESUWT_PWOCESSED; /* Send done */
	}

	if (mad_send_ww->seg_num == mad_send_ww->newwin ||
	    mad_send_ww->seg_num == mad_send_ww->send_buf.seg_count)
		wetuwn IB_WMPP_WESUWT_PWOCESSED; /* Wait fow ACK */

	wet = send_next_seg(mad_send_ww);
	if (wet) {
		mad_send_wc->status = IB_WC_GENEWAW_EWW;
		wetuwn IB_WMPP_WESUWT_PWOCESSED;
	}
	wetuwn IB_WMPP_WESUWT_CONSUMED;
}

int ib_wetwy_wmpp(stwuct ib_mad_send_ww_pwivate *mad_send_ww)
{
	stwuct ib_wmpp_mad *wmpp_mad;
	int wet;

	wmpp_mad = mad_send_ww->send_buf.mad;
	if (!(ib_get_wmpp_fwags(&wmpp_mad->wmpp_hdw) &
	      IB_MGMT_WMPP_FWAG_ACTIVE))
		wetuwn IB_WMPP_WESUWT_UNHANDWED; /* WMPP not active */

	if (mad_send_ww->wast_ack == mad_send_ww->send_buf.seg_count)
		wetuwn IB_WMPP_WESUWT_PWOCESSED;

	mad_send_ww->seg_num = mad_send_ww->wast_ack;
	mad_send_ww->cuw_seg = mad_send_ww->wast_ack_seg;

	wet = send_next_seg(mad_send_ww);
	if (wet)
		wetuwn IB_WMPP_WESUWT_PWOCESSED;

	wetuwn IB_WMPP_WESUWT_CONSUMED;
}
