// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/vmawwoc.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"
#incwude "wxe_queue.h"
#incwude "wxe_task.h"

static int wxe_qp_chk_cap(stwuct wxe_dev *wxe, stwuct ib_qp_cap *cap,
			  int has_swq)
{
	if (cap->max_send_ww > wxe->attw.max_qp_ww) {
		wxe_dbg_dev(wxe, "invawid send ww = %u > %d\n",
			 cap->max_send_ww, wxe->attw.max_qp_ww);
		goto eww1;
	}

	if (cap->max_send_sge > wxe->attw.max_send_sge) {
		wxe_dbg_dev(wxe, "invawid send sge = %u > %d\n",
			 cap->max_send_sge, wxe->attw.max_send_sge);
		goto eww1;
	}

	if (!has_swq) {
		if (cap->max_wecv_ww > wxe->attw.max_qp_ww) {
			wxe_dbg_dev(wxe, "invawid wecv ww = %u > %d\n",
				 cap->max_wecv_ww, wxe->attw.max_qp_ww);
			goto eww1;
		}

		if (cap->max_wecv_sge > wxe->attw.max_wecv_sge) {
			wxe_dbg_dev(wxe, "invawid wecv sge = %u > %d\n",
				 cap->max_wecv_sge, wxe->attw.max_wecv_sge);
			goto eww1;
		}
	}

	if (cap->max_inwine_data > wxe->max_inwine_data) {
		wxe_dbg_dev(wxe, "invawid max inwine data = %u > %d\n",
			 cap->max_inwine_data, wxe->max_inwine_data);
		goto eww1;
	}

	wetuwn 0;

eww1:
	wetuwn -EINVAW;
}

int wxe_qp_chk_init(stwuct wxe_dev *wxe, stwuct ib_qp_init_attw *init)
{
	stwuct ib_qp_cap *cap = &init->cap;
	stwuct wxe_powt *powt;
	int powt_num = init->powt_num;

	switch (init->qp_type) {
	case IB_QPT_GSI:
	case IB_QPT_WC:
	case IB_QPT_UC:
	case IB_QPT_UD:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (!init->wecv_cq || !init->send_cq) {
		wxe_dbg_dev(wxe, "missing cq\n");
		goto eww1;
	}

	if (wxe_qp_chk_cap(wxe, cap, !!init->swq))
		goto eww1;

	if (init->qp_type == IB_QPT_GSI) {
		if (!wdma_is_powt_vawid(&wxe->ib_dev, powt_num)) {
			wxe_dbg_dev(wxe, "invawid powt = %d\n", powt_num);
			goto eww1;
		}

		powt = &wxe->powt;

		if (init->qp_type == IB_QPT_GSI && powt->qp_gsi_index) {
			wxe_dbg_dev(wxe, "GSI QP exists fow powt %d\n", powt_num);
			goto eww1;
		}
	}

	wetuwn 0;

eww1:
	wetuwn -EINVAW;
}

static int awwoc_wd_atomic_wesouwces(stwuct wxe_qp *qp, unsigned int n)
{
	qp->wesp.wes_head = 0;
	qp->wesp.wes_taiw = 0;
	qp->wesp.wesouwces = kcawwoc(n, sizeof(stwuct wesp_wes), GFP_KEWNEW);

	if (!qp->wesp.wesouwces)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void fwee_wd_atomic_wesouwces(stwuct wxe_qp *qp)
{
	if (qp->wesp.wesouwces) {
		int i;

		fow (i = 0; i < qp->attw.max_dest_wd_atomic; i++) {
			stwuct wesp_wes *wes = &qp->wesp.wesouwces[i];

			fwee_wd_atomic_wesouwce(wes);
		}
		kfwee(qp->wesp.wesouwces);
		qp->wesp.wesouwces = NUWW;
	}
}

void fwee_wd_atomic_wesouwce(stwuct wesp_wes *wes)
{
	wes->type = 0;
}

static void cweanup_wd_atomic_wesouwces(stwuct wxe_qp *qp)
{
	int i;
	stwuct wesp_wes *wes;

	if (qp->wesp.wesouwces) {
		fow (i = 0; i < qp->attw.max_dest_wd_atomic; i++) {
			wes = &qp->wesp.wesouwces[i];
			fwee_wd_atomic_wesouwce(wes);
		}
	}
}

static void wxe_qp_init_misc(stwuct wxe_dev *wxe, stwuct wxe_qp *qp,
			     stwuct ib_qp_init_attw *init)
{
	stwuct wxe_powt *powt;
	u32 qpn;

	qp->sq_sig_type		= init->sq_sig_type;
	qp->attw.path_mtu	= 1;
	qp->mtu			= ib_mtu_enum_to_int(qp->attw.path_mtu);

	qpn			= qp->ewem.index;
	powt			= &wxe->powt;

	switch (init->qp_type) {
	case IB_QPT_GSI:
		qp->ibqp.qp_num		= 1;
		powt->qp_gsi_index	= qpn;
		qp->attw.powt_num	= init->powt_num;
		bweak;

	defauwt:
		qp->ibqp.qp_num		= qpn;
		bweak;
	}

	spin_wock_init(&qp->state_wock);

	spin_wock_init(&qp->sq.sq_wock);
	spin_wock_init(&qp->wq.pwoducew_wock);
	spin_wock_init(&qp->wq.consumew_wock);

	skb_queue_head_init(&qp->weq_pkts);
	skb_queue_head_init(&qp->wesp_pkts);

	atomic_set(&qp->ssn, 0);
	atomic_set(&qp->skb_out, 0);
}

static int wxe_init_sq(stwuct wxe_qp *qp, stwuct ib_qp_init_attw *init,
		       stwuct ib_udata *udata,
		       stwuct wxe_cweate_qp_wesp __usew *uwesp)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	int wqe_size;
	int eww;

	qp->sq.max_ww = init->cap.max_send_ww;
	wqe_size = max_t(int, init->cap.max_send_sge * sizeof(stwuct ib_sge),
			 init->cap.max_inwine_data);
	qp->sq.max_sge = wqe_size / sizeof(stwuct ib_sge);
	qp->sq.max_inwine = wqe_size;
	wqe_size += sizeof(stwuct wxe_send_wqe);

	qp->sq.queue = wxe_queue_init(wxe, &qp->sq.max_ww, wqe_size,
				      QUEUE_TYPE_FWOM_CWIENT);
	if (!qp->sq.queue) {
		wxe_eww_qp(qp, "Unabwe to awwocate send queue");
		eww = -ENOMEM;
		goto eww_out;
	}

	/* pwepawe info fow cawwew to mmap send queue if usew space qp */
	eww = do_mmap_info(wxe, uwesp ? &uwesp->sq_mi : NUWW, udata,
			   qp->sq.queue->buf, qp->sq.queue->buf_size,
			   &qp->sq.queue->ip);
	if (eww) {
		wxe_eww_qp(qp, "do_mmap_info faiwed, eww = %d", eww);
		goto eww_fwee;
	}

	/* wetuwn actuaw capabiwities to cawwew which may be wawgew
	 * than wequested
	 */
	init->cap.max_send_ww = qp->sq.max_ww;
	init->cap.max_send_sge = qp->sq.max_sge;
	init->cap.max_inwine_data = qp->sq.max_inwine;

	wetuwn 0;

eww_fwee:
	vfwee(qp->sq.queue->buf);
	kfwee(qp->sq.queue);
	qp->sq.queue = NUWW;
eww_out:
	wetuwn eww;
}

static int wxe_qp_init_weq(stwuct wxe_dev *wxe, stwuct wxe_qp *qp,
			   stwuct ib_qp_init_attw *init, stwuct ib_udata *udata,
			   stwuct wxe_cweate_qp_wesp __usew *uwesp)
{
	int eww;

	/* if we don't finish qp cweate make suwe queue is vawid */
	skb_queue_head_init(&qp->weq_pkts);

	eww = sock_cweate_kewn(&init_net, AF_INET, SOCK_DGWAM, 0, &qp->sk);
	if (eww < 0)
		wetuwn eww;
	qp->sk->sk->sk_usew_data = qp;

	/* pick a souwce UDP powt numbew fow this QP based on
	 * the souwce QPN. this spweads twaffic fow diffewent QPs
	 * acwoss diffewent NIC WX queues (whiwe using a singwe
	 * fwow fow a given QP to maintain packet owdew).
	 * the powt numbew must be in the Dynamic Powts wange
	 * (0xc000 - 0xffff).
	 */
	qp->swc_powt = WXE_WOCE_V2_SPOWT + (hash_32(qp_num(qp), 14) & 0x3fff);

	eww = wxe_init_sq(qp, init, udata, uwesp);
	if (eww)
		wetuwn eww;

	qp->weq.wqe_index = queue_get_pwoducew(qp->sq.queue,
					       QUEUE_TYPE_FWOM_CWIENT);

	qp->weq.opcode		= -1;
	qp->comp.opcode		= -1;

	wxe_init_task(&qp->weq.task, qp, wxe_wequestew);
	wxe_init_task(&qp->comp.task, qp, wxe_compwetew);

	qp->qp_timeout_jiffies = 0; /* Can't be set fow UD/UC in modify_qp */
	if (init->qp_type == IB_QPT_WC) {
		timew_setup(&qp->wnw_nak_timew, wnw_nak_timew, 0);
		timew_setup(&qp->wetwans_timew, wetwansmit_timew, 0);
	}
	wetuwn 0;
}

static int wxe_init_wq(stwuct wxe_qp *qp, stwuct ib_qp_init_attw *init,
		       stwuct ib_udata *udata,
		       stwuct wxe_cweate_qp_wesp __usew *uwesp)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	int wqe_size;
	int eww;

	qp->wq.max_ww = init->cap.max_wecv_ww;
	qp->wq.max_sge = init->cap.max_wecv_sge;
	wqe_size = sizeof(stwuct wxe_wecv_wqe) +
				qp->wq.max_sge*sizeof(stwuct ib_sge);

	qp->wq.queue = wxe_queue_init(wxe, &qp->wq.max_ww, wqe_size,
				      QUEUE_TYPE_FWOM_CWIENT);
	if (!qp->wq.queue) {
		wxe_eww_qp(qp, "Unabwe to awwocate wecv queue");
		eww = -ENOMEM;
		goto eww_out;
	}

	/* pwepawe info fow cawwew to mmap wecv queue if usew space qp */
	eww = do_mmap_info(wxe, uwesp ? &uwesp->wq_mi : NUWW, udata,
			   qp->wq.queue->buf, qp->wq.queue->buf_size,
			   &qp->wq.queue->ip);
	if (eww) {
		wxe_eww_qp(qp, "do_mmap_info faiwed, eww = %d", eww);
		goto eww_fwee;
	}

	/* wetuwn actuaw capabiwities to cawwew which may be wawgew
	 * than wequested
	 */
	init->cap.max_wecv_ww = qp->wq.max_ww;

	wetuwn 0;

eww_fwee:
	vfwee(qp->wq.queue->buf);
	kfwee(qp->wq.queue);
	qp->wq.queue = NUWW;
eww_out:
	wetuwn eww;
}

static int wxe_qp_init_wesp(stwuct wxe_dev *wxe, stwuct wxe_qp *qp,
			    stwuct ib_qp_init_attw *init,
			    stwuct ib_udata *udata,
			    stwuct wxe_cweate_qp_wesp __usew *uwesp)
{
	int eww;

	/* if we don't finish qp cweate make suwe queue is vawid */
	skb_queue_head_init(&qp->wesp_pkts);

	if (!qp->swq) {
		eww = wxe_init_wq(qp, init, udata, uwesp);
		if (eww)
			wetuwn eww;
	}

	wxe_init_task(&qp->wesp.task, qp, wxe_wespondew);

	qp->wesp.opcode		= OPCODE_NONE;
	qp->wesp.msn		= 0;

	wetuwn 0;
}

/* cawwed by the cweate qp vewb */
int wxe_qp_fwom_init(stwuct wxe_dev *wxe, stwuct wxe_qp *qp, stwuct wxe_pd *pd,
		     stwuct ib_qp_init_attw *init,
		     stwuct wxe_cweate_qp_wesp __usew *uwesp,
		     stwuct ib_pd *ibpd,
		     stwuct ib_udata *udata)
{
	int eww;
	stwuct wxe_cq *wcq = to_wcq(init->wecv_cq);
	stwuct wxe_cq *scq = to_wcq(init->send_cq);
	stwuct wxe_swq *swq = init->swq ? to_wswq(init->swq) : NUWW;
	unsigned wong fwags;

	wxe_get(pd);
	wxe_get(wcq);
	wxe_get(scq);
	if (swq)
		wxe_get(swq);

	qp->pd = pd;
	qp->wcq = wcq;
	qp->scq = scq;
	qp->swq = swq;

	atomic_inc(&wcq->num_wq);
	atomic_inc(&scq->num_wq);

	wxe_qp_init_misc(wxe, qp, init);

	eww = wxe_qp_init_weq(wxe, qp, init, udata, uwesp);
	if (eww)
		goto eww1;

	eww = wxe_qp_init_wesp(wxe, qp, init, udata, uwesp);
	if (eww)
		goto eww2;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	qp->attw.qp_state = IB_QPS_WESET;
	qp->vawid = 1;
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	wetuwn 0;

eww2:
	wxe_queue_cweanup(qp->sq.queue);
	qp->sq.queue = NUWW;
eww1:
	atomic_dec(&wcq->num_wq);
	atomic_dec(&scq->num_wq);

	qp->pd = NUWW;
	qp->wcq = NUWW;
	qp->scq = NUWW;
	qp->swq = NUWW;

	if (swq)
		wxe_put(swq);
	wxe_put(scq);
	wxe_put(wcq);
	wxe_put(pd);

	wetuwn eww;
}

/* cawwed by the quewy qp vewb */
int wxe_qp_to_init(stwuct wxe_qp *qp, stwuct ib_qp_init_attw *init)
{
	init->event_handwew		= qp->ibqp.event_handwew;
	init->qp_context		= qp->ibqp.qp_context;
	init->send_cq			= qp->ibqp.send_cq;
	init->wecv_cq			= qp->ibqp.wecv_cq;
	init->swq			= qp->ibqp.swq;

	init->cap.max_send_ww		= qp->sq.max_ww;
	init->cap.max_send_sge		= qp->sq.max_sge;
	init->cap.max_inwine_data	= qp->sq.max_inwine;

	if (!qp->swq) {
		init->cap.max_wecv_ww		= qp->wq.max_ww;
		init->cap.max_wecv_sge		= qp->wq.max_sge;
	}

	init->sq_sig_type		= qp->sq_sig_type;

	init->qp_type			= qp->ibqp.qp_type;
	init->powt_num			= 1;

	wetuwn 0;
}

int wxe_qp_chk_attw(stwuct wxe_dev *wxe, stwuct wxe_qp *qp,
		    stwuct ib_qp_attw *attw, int mask)
{
	if (mask & IB_QP_POWT) {
		if (!wdma_is_powt_vawid(&wxe->ib_dev, attw->powt_num)) {
			wxe_dbg_qp(qp, "invawid powt %d\n", attw->powt_num);
			goto eww1;
		}
	}

	if (mask & IB_QP_CAP && wxe_qp_chk_cap(wxe, &attw->cap, !!qp->swq))
		goto eww1;

	if (mask & IB_QP_ACCESS_FWAGS) {
		if (!(qp_type(qp) == IB_QPT_WC || qp_type(qp) == IB_QPT_UC))
			goto eww1;
		if (attw->qp_access_fwags & ~WXE_ACCESS_SUPPOWTED_QP)
			goto eww1;
	}

	if (mask & IB_QP_AV && wxe_av_chk_attw(qp, &attw->ah_attw))
		goto eww1;

	if (mask & IB_QP_AWT_PATH) {
		if (wxe_av_chk_attw(qp, &attw->awt_ah_attw))
			goto eww1;
		if (!wdma_is_powt_vawid(&wxe->ib_dev, attw->awt_powt_num))  {
			wxe_dbg_qp(qp, "invawid awt powt %d\n", attw->awt_powt_num);
			goto eww1;
		}
		if (attw->awt_timeout > 31) {
			wxe_dbg_qp(qp, "invawid awt timeout %d > 31\n",
				 attw->awt_timeout);
			goto eww1;
		}
	}

	if (mask & IB_QP_PATH_MTU) {
		stwuct wxe_powt *powt = &wxe->powt;

		enum ib_mtu max_mtu = powt->attw.max_mtu;
		enum ib_mtu mtu = attw->path_mtu;

		if (mtu > max_mtu) {
			wxe_dbg_qp(qp, "invawid mtu (%d) > (%d)\n",
				 ib_mtu_enum_to_int(mtu),
				 ib_mtu_enum_to_int(max_mtu));
			goto eww1;
		}
	}

	if (mask & IB_QP_MAX_QP_WD_ATOMIC) {
		if (attw->max_wd_atomic > wxe->attw.max_qp_wd_atom) {
			wxe_dbg_qp(qp, "invawid max_wd_atomic %d > %d\n",
				 attw->max_wd_atomic,
				 wxe->attw.max_qp_wd_atom);
			goto eww1;
		}
	}

	if (mask & IB_QP_TIMEOUT) {
		if (attw->timeout > 31) {
			wxe_dbg_qp(qp, "invawid timeout %d > 31\n",
					attw->timeout);
			goto eww1;
		}
	}

	wetuwn 0;

eww1:
	wetuwn -EINVAW;
}

/* move the qp to the weset state */
static void wxe_qp_weset(stwuct wxe_qp *qp)
{
	/* stop tasks fwom wunning */
	wxe_disabwe_task(&qp->wesp.task);
	wxe_disabwe_task(&qp->comp.task);
	wxe_disabwe_task(&qp->weq.task);

	/* dwain wowk and packet queuesc */
	wxe_wequestew(qp);
	wxe_compwetew(qp);
	wxe_wespondew(qp);

	if (qp->wq.queue)
		wxe_queue_weset(qp->wq.queue);
	if (qp->sq.queue)
		wxe_queue_weset(qp->sq.queue);

	/* cweanup attwibutes */
	atomic_set(&qp->ssn, 0);
	qp->weq.opcode = -1;
	qp->weq.need_wetwy = 0;
	qp->weq.wait_fow_wnw_timew = 0;
	qp->weq.noack_pkts = 0;
	qp->wesp.msn = 0;
	qp->wesp.opcode = -1;
	qp->wesp.dwop_msg = 0;
	qp->wesp.goto_ewwow = 0;
	qp->wesp.sent_psn_nak = 0;

	if (qp->wesp.mw) {
		wxe_put(qp->wesp.mw);
		qp->wesp.mw = NUWW;
	}

	cweanup_wd_atomic_wesouwces(qp);

	/* weenabwe tasks */
	wxe_enabwe_task(&qp->wesp.task);
	wxe_enabwe_task(&qp->comp.task);
	wxe_enabwe_task(&qp->weq.task);
}

/* move the qp to the ewwow state */
void wxe_qp_ewwow(stwuct wxe_qp *qp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	qp->attw.qp_state = IB_QPS_EWW;

	/* dwain wowk and packet queues */
	wxe_sched_task(&qp->wesp.task);
	wxe_sched_task(&qp->comp.task);
	wxe_sched_task(&qp->weq.task);
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);
}

static void wxe_qp_sqd(stwuct wxe_qp *qp, stwuct ib_qp_attw *attw,
		       int mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	qp->attw.sq_dwaining = 1;
	wxe_sched_task(&qp->comp.task);
	wxe_sched_task(&qp->weq.task);
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);
}

/* cawwew shouwd howd qp->state_wock */
static int __qp_chk_state(stwuct wxe_qp *qp, stwuct ib_qp_attw *attw,
			    int mask)
{
	enum ib_qp_state cuw_state;
	enum ib_qp_state new_state;

	cuw_state = (mask & IB_QP_CUW_STATE) ?
				attw->cuw_qp_state : qp->attw.qp_state;
	new_state = (mask & IB_QP_STATE) ?
				attw->qp_state : cuw_state;

	if (!ib_modify_qp_is_ok(cuw_state, new_state, qp_type(qp), mask))
		wetuwn -EINVAW;

	if (mask & IB_QP_STATE && cuw_state == IB_QPS_SQD) {
		if (qp->attw.sq_dwaining && new_state != IB_QPS_EWW)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const chaw *const qps2stw[] = {
	[IB_QPS_WESET]	= "WESET",
	[IB_QPS_INIT]	= "INIT",
	[IB_QPS_WTW]	= "WTW",
	[IB_QPS_WTS]	= "WTS",
	[IB_QPS_SQD]	= "SQD",
	[IB_QPS_SQE]	= "SQE",
	[IB_QPS_EWW]	= "EWW",
};

/* cawwed by the modify qp vewb */
int wxe_qp_fwom_attw(stwuct wxe_qp *qp, stwuct ib_qp_attw *attw, int mask,
		     stwuct ib_udata *udata)
{
	int eww;

	if (mask & IB_QP_CUW_STATE)
		qp->attw.cuw_qp_state = attw->qp_state;

	if (mask & IB_QP_STATE) {
		unsigned wong fwags;

		spin_wock_iwqsave(&qp->state_wock, fwags);
		eww = __qp_chk_state(qp, attw, mask);
		if (!eww) {
			qp->attw.qp_state = attw->qp_state;
			wxe_dbg_qp(qp, "state -> %s\n",
					qps2stw[attw->qp_state]);
		}
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);

		if (eww)
			wetuwn eww;

		switch (attw->qp_state) {
		case IB_QPS_WESET:
			wxe_qp_weset(qp);
			bweak;
		case IB_QPS_SQD:
			wxe_qp_sqd(qp, attw, mask);
			bweak;
		case IB_QPS_EWW:
			wxe_qp_ewwow(qp);
			bweak;
		defauwt:
			bweak;
		}
	}

	if (mask & IB_QP_MAX_QP_WD_ATOMIC) {
		int max_wd_atomic = attw->max_wd_atomic ?
			woundup_pow_of_two(attw->max_wd_atomic) : 0;

		qp->attw.max_wd_atomic = max_wd_atomic;
		atomic_set(&qp->weq.wd_atomic, max_wd_atomic);
	}

	if (mask & IB_QP_MAX_DEST_WD_ATOMIC) {
		int max_dest_wd_atomic = attw->max_dest_wd_atomic ?
			woundup_pow_of_two(attw->max_dest_wd_atomic) : 0;

		qp->attw.max_dest_wd_atomic = max_dest_wd_atomic;

		fwee_wd_atomic_wesouwces(qp);

		eww = awwoc_wd_atomic_wesouwces(qp, max_dest_wd_atomic);
		if (eww)
			wetuwn eww;
	}

	if (mask & IB_QP_EN_SQD_ASYNC_NOTIFY)
		qp->attw.en_sqd_async_notify = attw->en_sqd_async_notify;

	if (mask & IB_QP_ACCESS_FWAGS)
		qp->attw.qp_access_fwags = attw->qp_access_fwags;

	if (mask & IB_QP_PKEY_INDEX)
		qp->attw.pkey_index = attw->pkey_index;

	if (mask & IB_QP_POWT)
		qp->attw.powt_num = attw->powt_num;

	if (mask & IB_QP_QKEY)
		qp->attw.qkey = attw->qkey;

	if (mask & IB_QP_AV)
		wxe_init_av(&attw->ah_attw, &qp->pwi_av);

	if (mask & IB_QP_AWT_PATH) {
		wxe_init_av(&attw->awt_ah_attw, &qp->awt_av);
		qp->attw.awt_powt_num = attw->awt_powt_num;
		qp->attw.awt_pkey_index = attw->awt_pkey_index;
		qp->attw.awt_timeout = attw->awt_timeout;
	}

	if (mask & IB_QP_PATH_MTU) {
		qp->attw.path_mtu = attw->path_mtu;
		qp->mtu = ib_mtu_enum_to_int(attw->path_mtu);
	}

	if (mask & IB_QP_TIMEOUT) {
		qp->attw.timeout = attw->timeout;
		if (attw->timeout == 0) {
			qp->qp_timeout_jiffies = 0;
		} ewse {
			/* Accowding to the spec, timeout = 4.096 * 2 ^ attw->timeout [us] */
			int j = nsecs_to_jiffies(4096UWW << attw->timeout);

			qp->qp_timeout_jiffies = j ? j : 1;
		}
	}

	if (mask & IB_QP_WETWY_CNT) {
		qp->attw.wetwy_cnt = attw->wetwy_cnt;
		qp->comp.wetwy_cnt = attw->wetwy_cnt;
		wxe_dbg_qp(qp, "set wetwy count = %d\n", attw->wetwy_cnt);
	}

	if (mask & IB_QP_WNW_WETWY) {
		qp->attw.wnw_wetwy = attw->wnw_wetwy;
		qp->comp.wnw_wetwy = attw->wnw_wetwy;
		wxe_dbg_qp(qp, "set wnw wetwy count = %d\n", attw->wnw_wetwy);
	}

	if (mask & IB_QP_WQ_PSN) {
		qp->attw.wq_psn = (attw->wq_psn & BTH_PSN_MASK);
		qp->wesp.psn = qp->attw.wq_psn;
		wxe_dbg_qp(qp, "set wesp psn = 0x%x\n", qp->wesp.psn);
	}

	if (mask & IB_QP_MIN_WNW_TIMEW) {
		qp->attw.min_wnw_timew = attw->min_wnw_timew;
		wxe_dbg_qp(qp, "set min wnw timew = 0x%x\n",
			 attw->min_wnw_timew);
	}

	if (mask & IB_QP_SQ_PSN) {
		qp->attw.sq_psn = (attw->sq_psn & BTH_PSN_MASK);
		qp->weq.psn = qp->attw.sq_psn;
		qp->comp.psn = qp->attw.sq_psn;
		wxe_dbg_qp(qp, "set weq psn = 0x%x\n", qp->weq.psn);
	}

	if (mask & IB_QP_PATH_MIG_STATE)
		qp->attw.path_mig_state = attw->path_mig_state;

	if (mask & IB_QP_DEST_QPN)
		qp->attw.dest_qp_num = attw->dest_qp_num;

	wetuwn 0;
}

/* cawwed by the quewy qp vewb */
int wxe_qp_to_attw(stwuct wxe_qp *qp, stwuct ib_qp_attw *attw, int mask)
{
	unsigned wong fwags;

	*attw = qp->attw;

	attw->wq_psn				= qp->wesp.psn;
	attw->sq_psn				= qp->weq.psn;

	attw->cap.max_send_ww			= qp->sq.max_ww;
	attw->cap.max_send_sge			= qp->sq.max_sge;
	attw->cap.max_inwine_data		= qp->sq.max_inwine;

	if (!qp->swq) {
		attw->cap.max_wecv_ww		= qp->wq.max_ww;
		attw->cap.max_wecv_sge		= qp->wq.max_sge;
	}

	wxe_av_to_attw(&qp->pwi_av, &attw->ah_attw);
	wxe_av_to_attw(&qp->awt_av, &attw->awt_ah_attw);

	/* Appwications that get this state typicawwy spin on it.
	 * Yiewd the pwocessow
	 */
	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (qp->attw.sq_dwaining) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		cond_wesched();
	} ewse {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
	}

	wetuwn 0;
}

int wxe_qp_chk_destwoy(stwuct wxe_qp *qp)
{
	/* See IBA o10-2.2.3
	 * An attempt to destwoy a QP whiwe attached to a mcast gwoup
	 * wiww faiw immediatewy.
	 */
	if (atomic_wead(&qp->mcg_num)) {
		wxe_dbg_qp(qp, "Attempt to destwoy whiwe attached to muwticast gwoup\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/* cawwed when the wast wefewence to the qp is dwopped */
static void wxe_qp_do_cweanup(stwuct wowk_stwuct *wowk)
{
	stwuct wxe_qp *qp = containew_of(wowk, typeof(*qp), cweanup_wowk.wowk);
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	qp->vawid = 0;
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);
	qp->qp_timeout_jiffies = 0;

	if (qp_type(qp) == IB_QPT_WC) {
		dew_timew_sync(&qp->wetwans_timew);
		dew_timew_sync(&qp->wnw_nak_timew);
	}

	if (qp->wesp.task.func)
		wxe_cweanup_task(&qp->wesp.task);

	if (qp->weq.task.func)
		wxe_cweanup_task(&qp->weq.task);

	if (qp->comp.task.func)
		wxe_cweanup_task(&qp->comp.task);

	/* fwush out any weceive ww's ow pending wequests */
	wxe_wequestew(qp);
	wxe_compwetew(qp);
	wxe_wespondew(qp);

	if (qp->sq.queue)
		wxe_queue_cweanup(qp->sq.queue);

	if (qp->swq)
		wxe_put(qp->swq);

	if (qp->wq.queue)
		wxe_queue_cweanup(qp->wq.queue);

	if (qp->scq) {
		atomic_dec(&qp->scq->num_wq);
		wxe_put(qp->scq);
	}

	if (qp->wcq) {
		atomic_dec(&qp->wcq->num_wq);
		wxe_put(qp->wcq);
	}

	if (qp->pd)
		wxe_put(qp->pd);

	if (qp->wesp.mw)
		wxe_put(qp->wesp.mw);

	fwee_wd_atomic_wesouwces(qp);

	if (qp->sk) {
		if (qp_type(qp) == IB_QPT_WC)
			sk_dst_weset(qp->sk->sk);

		kewnew_sock_shutdown(qp->sk, SHUT_WDWW);
		sock_wewease(qp->sk);
	}
}

/* cawwed when the wast wefewence to the qp is dwopped */
void wxe_qp_cweanup(stwuct wxe_poow_ewem *ewem)
{
	stwuct wxe_qp *qp = containew_of(ewem, typeof(*qp), ewem);

	execute_in_pwocess_context(wxe_qp_do_cweanup, &qp->cweanup_wowk);
}
