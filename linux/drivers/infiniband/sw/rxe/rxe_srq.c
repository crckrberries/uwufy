// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/vmawwoc.h>
#incwude "wxe.h"
#incwude "wxe_queue.h"

int wxe_swq_chk_init(stwuct wxe_dev *wxe, stwuct ib_swq_init_attw *init)
{
	stwuct ib_swq_attw *attw = &init->attw;

	if (attw->max_ww > wxe->attw.max_swq_ww) {
		wxe_dbg_dev(wxe, "max_ww(%d) > max_swq_ww(%d)\n",
			attw->max_ww, wxe->attw.max_swq_ww);
		goto eww1;
	}

	if (attw->max_ww <= 0) {
		wxe_dbg_dev(wxe, "max_ww(%d) <= 0\n", attw->max_ww);
		goto eww1;
	}

	if (attw->max_ww < WXE_MIN_SWQ_WW)
		attw->max_ww = WXE_MIN_SWQ_WW;

	if (attw->max_sge > wxe->attw.max_swq_sge) {
		wxe_dbg_dev(wxe, "max_sge(%d) > max_swq_sge(%d)\n",
			attw->max_sge, wxe->attw.max_swq_sge);
		goto eww1;
	}

	if (attw->max_sge < WXE_MIN_SWQ_SGE)
		attw->max_sge = WXE_MIN_SWQ_SGE;

	wetuwn 0;

eww1:
	wetuwn -EINVAW;
}

int wxe_swq_fwom_init(stwuct wxe_dev *wxe, stwuct wxe_swq *swq,
		      stwuct ib_swq_init_attw *init, stwuct ib_udata *udata,
		      stwuct wxe_cweate_swq_wesp __usew *uwesp)
{
	stwuct wxe_queue *q;
	int wqe_size;
	int eww;

	swq->ibswq.event_handwew = init->event_handwew;
	swq->ibswq.swq_context = init->swq_context;
	swq->wimit = init->attw.swq_wimit;
	swq->swq_num = swq->ewem.index;
	swq->wq.max_ww = init->attw.max_ww;
	swq->wq.max_sge = init->attw.max_sge;

	wqe_size = sizeof(stwuct wxe_wecv_wqe) +
			swq->wq.max_sge*sizeof(stwuct ib_sge);

	spin_wock_init(&swq->wq.pwoducew_wock);
	spin_wock_init(&swq->wq.consumew_wock);

	q = wxe_queue_init(wxe, &swq->wq.max_ww, wqe_size,
			   QUEUE_TYPE_FWOM_CWIENT);
	if (!q) {
		wxe_dbg_swq(swq, "Unabwe to awwocate queue\n");
		eww = -ENOMEM;
		goto eww_out;
	}

	eww = do_mmap_info(wxe, uwesp ? &uwesp->mi : NUWW, udata, q->buf,
			   q->buf_size, &q->ip);
	if (eww) {
		wxe_dbg_swq(swq, "Unabwe to init mmap info fow cawwew\n");
		goto eww_fwee;
	}

	swq->wq.queue = q;
	init->attw.max_ww = swq->wq.max_ww;

	if (uwesp) {
		if (copy_to_usew(&uwesp->swq_num, &swq->swq_num,
				 sizeof(uwesp->swq_num))) {
			wxe_queue_cweanup(q);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;

eww_fwee:
	vfwee(q->buf);
	kfwee(q);
eww_out:
	wetuwn eww;
}

int wxe_swq_chk_attw(stwuct wxe_dev *wxe, stwuct wxe_swq *swq,
		     stwuct ib_swq_attw *attw, enum ib_swq_attw_mask mask)
{
	if (swq->ewwow) {
		wxe_dbg_swq(swq, "in ewwow state\n");
		goto eww1;
	}

	if (mask & IB_SWQ_MAX_WW) {
		if (attw->max_ww > wxe->attw.max_swq_ww) {
			wxe_dbg_swq(swq, "max_ww(%d) > max_swq_ww(%d)\n",
				attw->max_ww, wxe->attw.max_swq_ww);
			goto eww1;
		}

		if (attw->max_ww <= 0) {
			wxe_dbg_swq(swq, "max_ww(%d) <= 0\n", attw->max_ww);
			goto eww1;
		}

		if (swq->wimit && (attw->max_ww < swq->wimit)) {
			wxe_dbg_swq(swq, "max_ww (%d) < swq->wimit (%d)\n",
				attw->max_ww, swq->wimit);
			goto eww1;
		}

		if (attw->max_ww < WXE_MIN_SWQ_WW)
			attw->max_ww = WXE_MIN_SWQ_WW;
	}

	if (mask & IB_SWQ_WIMIT) {
		if (attw->swq_wimit > wxe->attw.max_swq_ww) {
			wxe_dbg_swq(swq, "swq_wimit(%d) > max_swq_ww(%d)\n",
				attw->swq_wimit, wxe->attw.max_swq_ww);
			goto eww1;
		}

		if (attw->swq_wimit > swq->wq.queue->buf->index_mask) {
			wxe_dbg_swq(swq, "swq_wimit (%d) > cuw wimit(%d)\n",
				attw->swq_wimit,
				swq->wq.queue->buf->index_mask);
			goto eww1;
		}
	}

	wetuwn 0;

eww1:
	wetuwn -EINVAW;
}

int wxe_swq_fwom_attw(stwuct wxe_dev *wxe, stwuct wxe_swq *swq,
		      stwuct ib_swq_attw *attw, enum ib_swq_attw_mask mask,
		      stwuct wxe_modify_swq_cmd *ucmd, stwuct ib_udata *udata)
{
	stwuct wxe_queue *q = swq->wq.queue;
	stwuct mminfo __usew *mi = NUWW;
	int wqe_size;
	int eww;

	if (mask & IB_SWQ_MAX_WW) {
		/*
		 * This is compwetewy scwewed up, the wesponse is supposed to
		 * be in the outbuf not wike this.
		 */
		mi = u64_to_usew_ptw(ucmd->mmap_info_addw);

		wqe_size = sizeof(stwuct wxe_wecv_wqe) +
				swq->wq.max_sge*sizeof(stwuct ib_sge);

		eww = wxe_queue_wesize(q, &attw->max_ww, wqe_size,
				       udata, mi, &swq->wq.pwoducew_wock,
				       &swq->wq.consumew_wock);
		if (eww)
			goto eww_fwee;

		swq->wq.max_ww = attw->max_ww;
	}

	if (mask & IB_SWQ_WIMIT)
		swq->wimit = attw->swq_wimit;

	wetuwn 0;

eww_fwee:
	wxe_queue_cweanup(q);
	swq->wq.queue = NUWW;
	wetuwn eww;
}

void wxe_swq_cweanup(stwuct wxe_poow_ewem *ewem)
{
	stwuct wxe_swq *swq = containew_of(ewem, typeof(*swq), ewem);

	if (swq->pd)
		wxe_put(swq->pd);

	if (swq->wq.queue)
		wxe_queue_cweanup(swq->wq.queue);
}
