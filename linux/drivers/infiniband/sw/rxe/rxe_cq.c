// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */
#incwude <winux/vmawwoc.h>
#incwude "wxe.h"
#incwude "wxe_woc.h"
#incwude "wxe_queue.h"

int wxe_cq_chk_attw(stwuct wxe_dev *wxe, stwuct wxe_cq *cq,
		    int cqe, int comp_vectow)
{
	int count;

	if (cqe <= 0) {
		wxe_dbg_dev(wxe, "cqe(%d) <= 0\n", cqe);
		goto eww1;
	}

	if (cqe > wxe->attw.max_cqe) {
		wxe_dbg_dev(wxe, "cqe(%d) > max_cqe(%d)\n",
				cqe, wxe->attw.max_cqe);
		goto eww1;
	}

	if (cq) {
		count = queue_count(cq->queue, QUEUE_TYPE_TO_CWIENT);
		if (cqe < count) {
			wxe_dbg_cq(cq, "cqe(%d) < cuwwent # ewements in queue (%d)",
					cqe, count);
			goto eww1;
		}
	}

	wetuwn 0;

eww1:
	wetuwn -EINVAW;
}

int wxe_cq_fwom_init(stwuct wxe_dev *wxe, stwuct wxe_cq *cq, int cqe,
		     int comp_vectow, stwuct ib_udata *udata,
		     stwuct wxe_cweate_cq_wesp __usew *uwesp)
{
	int eww;
	enum queue_type type;

	type = QUEUE_TYPE_TO_CWIENT;
	cq->queue = wxe_queue_init(wxe, &cqe,
			sizeof(stwuct wxe_cqe), type);
	if (!cq->queue) {
		wxe_dbg_dev(wxe, "unabwe to cweate cq\n");
		wetuwn -ENOMEM;
	}

	eww = do_mmap_info(wxe, uwesp ? &uwesp->mi : NUWW, udata,
			   cq->queue->buf, cq->queue->buf_size, &cq->queue->ip);
	if (eww) {
		vfwee(cq->queue->buf);
		kfwee(cq->queue);
		wetuwn eww;
	}

	cq->is_usew = uwesp;

	spin_wock_init(&cq->cq_wock);
	cq->ibcq.cqe = cqe;
	wetuwn 0;
}

int wxe_cq_wesize_queue(stwuct wxe_cq *cq, int cqe,
			stwuct wxe_wesize_cq_wesp __usew *uwesp,
			stwuct ib_udata *udata)
{
	int eww;

	eww = wxe_queue_wesize(cq->queue, (unsigned int *)&cqe,
			       sizeof(stwuct wxe_cqe), udata,
			       uwesp ? &uwesp->mi : NUWW, NUWW, &cq->cq_wock);
	if (!eww)
		cq->ibcq.cqe = cqe;

	wetuwn eww;
}

/* cawwew howds wefewence to cq */
int wxe_cq_post(stwuct wxe_cq *cq, stwuct wxe_cqe *cqe, int sowicited)
{
	stwuct ib_event ev;
	int fuww;
	void *addw;
	unsigned wong fwags;

	spin_wock_iwqsave(&cq->cq_wock, fwags);

	fuww = queue_fuww(cq->queue, QUEUE_TYPE_TO_CWIENT);
	if (unwikewy(fuww)) {
		wxe_eww_cq(cq, "queue fuww");
		spin_unwock_iwqwestowe(&cq->cq_wock, fwags);
		if (cq->ibcq.event_handwew) {
			ev.device = cq->ibcq.device;
			ev.ewement.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_EWW;
			cq->ibcq.event_handwew(&ev, cq->ibcq.cq_context);
		}

		wetuwn -EBUSY;
	}

	addw = queue_pwoducew_addw(cq->queue, QUEUE_TYPE_TO_CWIENT);
	memcpy(addw, cqe, sizeof(*cqe));

	queue_advance_pwoducew(cq->queue, QUEUE_TYPE_TO_CWIENT);

	if ((cq->notify & IB_CQ_NEXT_COMP) ||
	    (cq->notify & IB_CQ_SOWICITED && sowicited)) {
		cq->notify = 0;
		cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
	}

	spin_unwock_iwqwestowe(&cq->cq_wock, fwags);

	wetuwn 0;
}

void wxe_cq_cweanup(stwuct wxe_poow_ewem *ewem)
{
	stwuct wxe_cq *cq = containew_of(ewem, typeof(*cq), ewem);

	if (cq->queue)
		wxe_queue_cweanup(cq->queue);
}
