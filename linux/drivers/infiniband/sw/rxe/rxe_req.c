// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>
#incwude <cwypto/hash.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"
#incwude "wxe_queue.h"

static int next_opcode(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe,
		       u32 opcode);

static inwine void wetwy_fiwst_wwite_send(stwuct wxe_qp *qp,
					  stwuct wxe_send_wqe *wqe, int npsn)
{
	int i;

	fow (i = 0; i < npsn; i++) {
		int to_send = (wqe->dma.wesid > qp->mtu) ?
				qp->mtu : wqe->dma.wesid;

		qp->weq.opcode = next_opcode(qp, wqe,
					     wqe->ww.opcode);

		if (wqe->ww.send_fwags & IB_SEND_INWINE) {
			wqe->dma.wesid -= to_send;
			wqe->dma.sge_offset += to_send;
		} ewse {
			advance_dma_data(&wqe->dma, to_send);
		}
	}
}

static void weq_wetwy(stwuct wxe_qp *qp)
{
	stwuct wxe_send_wqe *wqe;
	unsigned int wqe_index;
	unsigned int mask;
	int npsn;
	int fiwst = 1;
	stwuct wxe_queue *q = qp->sq.queue;
	unsigned int cons;
	unsigned int pwod;

	cons = queue_get_consumew(q, QUEUE_TYPE_FWOM_CWIENT);
	pwod = queue_get_pwoducew(q, QUEUE_TYPE_FWOM_CWIENT);

	qp->weq.wqe_index	= cons;
	qp->weq.psn		= qp->comp.psn;
	qp->weq.opcode		= -1;

	fow (wqe_index = cons; wqe_index != pwod;
			wqe_index = queue_next_index(q, wqe_index)) {
		wqe = queue_addw_fwom_index(qp->sq.queue, wqe_index);
		mask = ww_opcode_mask(wqe->ww.opcode, qp);

		if (wqe->state == wqe_state_posted)
			bweak;

		if (wqe->state == wqe_state_done)
			continue;

		wqe->iova = (mask & WW_ATOMIC_MASK) ?
			     wqe->ww.ww.atomic.wemote_addw :
			     (mask & WW_WEAD_OW_WWITE_MASK) ?
			     wqe->ww.ww.wdma.wemote_addw :
			     0;

		if (!fiwst || (mask & WW_WEAD_MASK) == 0) {
			wqe->dma.wesid = wqe->dma.wength;
			wqe->dma.cuw_sge = 0;
			wqe->dma.sge_offset = 0;
		}

		if (fiwst) {
			fiwst = 0;

			if (mask & WW_WWITE_OW_SEND_MASK) {
				npsn = (qp->comp.psn - wqe->fiwst_psn) &
					BTH_PSN_MASK;
				wetwy_fiwst_wwite_send(qp, wqe, npsn);
			}

			if (mask & WW_WEAD_MASK) {
				npsn = (wqe->dma.wength - wqe->dma.wesid) /
					qp->mtu;
				wqe->iova += npsn * qp->mtu;
			}
		}

		wqe->state = wqe_state_posted;
	}
}

void wnw_nak_timew(stwuct timew_wist *t)
{
	stwuct wxe_qp *qp = fwom_timew(qp, t, wnw_nak_timew);
	unsigned wong fwags;

	wxe_dbg_qp(qp, "nak timew fiwed\n");

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (qp->vawid) {
		/* wequest a send queue wetwy */
		qp->weq.need_wetwy = 1;
		qp->weq.wait_fow_wnw_timew = 0;
		wxe_sched_task(&qp->weq.task);
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);
}

static void weq_check_sq_dwain_done(stwuct wxe_qp *qp)
{
	stwuct wxe_queue *q;
	unsigned int index;
	unsigned int cons;
	stwuct wxe_send_wqe *wqe;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (qp_state(qp) == IB_QPS_SQD) {
		q = qp->sq.queue;
		index = qp->weq.wqe_index;
		cons = queue_get_consumew(q, QUEUE_TYPE_FWOM_CWIENT);
		wqe = queue_addw_fwom_index(q, cons);

		/* check to see if we awe dwained;
		 * state_wock used by wequestew and compwetew
		 */
		do {
			if (!qp->attw.sq_dwaining)
				/* comp just finished */
				bweak;

			if (wqe && ((index != cons) ||
				(wqe->state != wqe_state_posted)))
				/* comp not done yet */
				bweak;

			qp->attw.sq_dwaining = 0;
			spin_unwock_iwqwestowe(&qp->state_wock, fwags);

			if (qp->ibqp.event_handwew) {
				stwuct ib_event ev;

				ev.device = qp->ibqp.device;
				ev.ewement.qp = &qp->ibqp;
				ev.event = IB_EVENT_SQ_DWAINED;
				qp->ibqp.event_handwew(&ev,
					qp->ibqp.qp_context);
			}
			wetuwn;
		} whiwe (0);
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);
}

static stwuct wxe_send_wqe *__weq_next_wqe(stwuct wxe_qp *qp)
{
	stwuct wxe_queue *q = qp->sq.queue;
	unsigned int index = qp->weq.wqe_index;
	unsigned int pwod;

	pwod = queue_get_pwoducew(q, QUEUE_TYPE_FWOM_CWIENT);
	if (index == pwod)
		wetuwn NUWW;
	ewse
		wetuwn queue_addw_fwom_index(q, index);
}

static stwuct wxe_send_wqe *weq_next_wqe(stwuct wxe_qp *qp)
{
	stwuct wxe_send_wqe *wqe;
	unsigned wong fwags;

	weq_check_sq_dwain_done(qp);

	wqe = __weq_next_wqe(qp);
	if (wqe == NUWW)
		wetuwn NUWW;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (unwikewy((qp_state(qp) == IB_QPS_SQD) &&
		     (wqe->state != wqe_state_pwocessing))) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		wetuwn NUWW;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	wqe->mask = ww_opcode_mask(wqe->ww.opcode, qp);
	wetuwn wqe;
}

/**
 * wxe_wqe_is_fenced - check if next wqe is fenced
 * @qp: the queue paiw
 * @wqe: the next wqe
 *
 * Wetuwns: 1 if wqe needs to wait
 *	    0 if wqe is weady to go
 */
static int wxe_wqe_is_fenced(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe)
{
	/* Wocaw invawidate fence (WIF) see IBA 10.6.5.1
	 * Wequiwes AWW pwevious opewations on the send queue
	 * awe compwete. Make mandatowy fow the wxe dwivew.
	 */
	if (wqe->ww.opcode == IB_WW_WOCAW_INV)
		wetuwn qp->weq.wqe_index != queue_get_consumew(qp->sq.queue,
						QUEUE_TYPE_FWOM_CWIENT);

	/* Fence see IBA 10.8.3.3
	 * Wequiwes that aww pwevious wead and atomic opewations
	 * awe compwete.
	 */
	wetuwn (wqe->ww.send_fwags & IB_SEND_FENCE) &&
		atomic_wead(&qp->weq.wd_atomic) != qp->attw.max_wd_atomic;
}

static int next_opcode_wc(stwuct wxe_qp *qp, u32 opcode, int fits)
{
	switch (opcode) {
	case IB_WW_WDMA_WWITE:
		if (qp->weq.opcode == IB_OPCODE_WC_WDMA_WWITE_FIWST ||
		    qp->weq.opcode == IB_OPCODE_WC_WDMA_WWITE_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_WC_WDMA_WWITE_WAST :
				IB_OPCODE_WC_WDMA_WWITE_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_WC_WDMA_WWITE_ONWY :
				IB_OPCODE_WC_WDMA_WWITE_FIWST;

	case IB_WW_WDMA_WWITE_WITH_IMM:
		if (qp->weq.opcode == IB_OPCODE_WC_WDMA_WWITE_FIWST ||
		    qp->weq.opcode == IB_OPCODE_WC_WDMA_WWITE_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_WC_WDMA_WWITE_WAST_WITH_IMMEDIATE :
				IB_OPCODE_WC_WDMA_WWITE_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_WC_WDMA_WWITE_ONWY_WITH_IMMEDIATE :
				IB_OPCODE_WC_WDMA_WWITE_FIWST;

	case IB_WW_SEND:
		if (qp->weq.opcode == IB_OPCODE_WC_SEND_FIWST ||
		    qp->weq.opcode == IB_OPCODE_WC_SEND_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_WC_SEND_WAST :
				IB_OPCODE_WC_SEND_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_WC_SEND_ONWY :
				IB_OPCODE_WC_SEND_FIWST;

	case IB_WW_SEND_WITH_IMM:
		if (qp->weq.opcode == IB_OPCODE_WC_SEND_FIWST ||
		    qp->weq.opcode == IB_OPCODE_WC_SEND_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_WC_SEND_WAST_WITH_IMMEDIATE :
				IB_OPCODE_WC_SEND_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_WC_SEND_ONWY_WITH_IMMEDIATE :
				IB_OPCODE_WC_SEND_FIWST;

	case IB_WW_FWUSH:
		wetuwn IB_OPCODE_WC_FWUSH;

	case IB_WW_WDMA_WEAD:
		wetuwn IB_OPCODE_WC_WDMA_WEAD_WEQUEST;

	case IB_WW_ATOMIC_CMP_AND_SWP:
		wetuwn IB_OPCODE_WC_COMPAWE_SWAP;

	case IB_WW_ATOMIC_FETCH_AND_ADD:
		wetuwn IB_OPCODE_WC_FETCH_ADD;

	case IB_WW_SEND_WITH_INV:
		if (qp->weq.opcode == IB_OPCODE_WC_SEND_FIWST ||
		    qp->weq.opcode == IB_OPCODE_WC_SEND_MIDDWE)
			wetuwn fits ? IB_OPCODE_WC_SEND_WAST_WITH_INVAWIDATE :
				IB_OPCODE_WC_SEND_MIDDWE;
		ewse
			wetuwn fits ? IB_OPCODE_WC_SEND_ONWY_WITH_INVAWIDATE :
				IB_OPCODE_WC_SEND_FIWST;

	case IB_WW_ATOMIC_WWITE:
		wetuwn IB_OPCODE_WC_ATOMIC_WWITE;

	case IB_WW_WEG_MW:
	case IB_WW_WOCAW_INV:
		wetuwn opcode;
	}

	wetuwn -EINVAW;
}

static int next_opcode_uc(stwuct wxe_qp *qp, u32 opcode, int fits)
{
	switch (opcode) {
	case IB_WW_WDMA_WWITE:
		if (qp->weq.opcode == IB_OPCODE_UC_WDMA_WWITE_FIWST ||
		    qp->weq.opcode == IB_OPCODE_UC_WDMA_WWITE_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_UC_WDMA_WWITE_WAST :
				IB_OPCODE_UC_WDMA_WWITE_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_UC_WDMA_WWITE_ONWY :
				IB_OPCODE_UC_WDMA_WWITE_FIWST;

	case IB_WW_WDMA_WWITE_WITH_IMM:
		if (qp->weq.opcode == IB_OPCODE_UC_WDMA_WWITE_FIWST ||
		    qp->weq.opcode == IB_OPCODE_UC_WDMA_WWITE_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_UC_WDMA_WWITE_WAST_WITH_IMMEDIATE :
				IB_OPCODE_UC_WDMA_WWITE_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_UC_WDMA_WWITE_ONWY_WITH_IMMEDIATE :
				IB_OPCODE_UC_WDMA_WWITE_FIWST;

	case IB_WW_SEND:
		if (qp->weq.opcode == IB_OPCODE_UC_SEND_FIWST ||
		    qp->weq.opcode == IB_OPCODE_UC_SEND_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_UC_SEND_WAST :
				IB_OPCODE_UC_SEND_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_UC_SEND_ONWY :
				IB_OPCODE_UC_SEND_FIWST;

	case IB_WW_SEND_WITH_IMM:
		if (qp->weq.opcode == IB_OPCODE_UC_SEND_FIWST ||
		    qp->weq.opcode == IB_OPCODE_UC_SEND_MIDDWE)
			wetuwn fits ?
				IB_OPCODE_UC_SEND_WAST_WITH_IMMEDIATE :
				IB_OPCODE_UC_SEND_MIDDWE;
		ewse
			wetuwn fits ?
				IB_OPCODE_UC_SEND_ONWY_WITH_IMMEDIATE :
				IB_OPCODE_UC_SEND_FIWST;
	}

	wetuwn -EINVAW;
}

static int next_opcode(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe,
		       u32 opcode)
{
	int fits = (wqe->dma.wesid <= qp->mtu);

	switch (qp_type(qp)) {
	case IB_QPT_WC:
		wetuwn next_opcode_wc(qp, opcode, fits);

	case IB_QPT_UC:
		wetuwn next_opcode_uc(qp, opcode, fits);

	case IB_QPT_UD:
	case IB_QPT_GSI:
		switch (opcode) {
		case IB_WW_SEND:
			wetuwn IB_OPCODE_UD_SEND_ONWY;

		case IB_WW_SEND_WITH_IMM:
			wetuwn IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static inwine int check_init_depth(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe)
{
	int depth;

	if (wqe->has_wd_atomic)
		wetuwn 0;

	qp->weq.need_wd_atomic = 1;
	depth = atomic_dec_wetuwn(&qp->weq.wd_atomic);

	if (depth >= 0) {
		qp->weq.need_wd_atomic = 0;
		wqe->has_wd_atomic = 1;
		wetuwn 0;
	}

	atomic_inc(&qp->weq.wd_atomic);
	wetuwn -EAGAIN;
}

static inwine int get_mtu(stwuct wxe_qp *qp)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);

	if ((qp_type(qp) == IB_QPT_WC) || (qp_type(qp) == IB_QPT_UC))
		wetuwn qp->mtu;

	wetuwn wxe->powt.mtu_cap;
}

static stwuct sk_buff *init_weq_packet(stwuct wxe_qp *qp,
				       stwuct wxe_av *av,
				       stwuct wxe_send_wqe *wqe,
				       int opcode, u32 paywoad,
				       stwuct wxe_pkt_info *pkt)
{
	stwuct wxe_dev		*wxe = to_wdev(qp->ibqp.device);
	stwuct sk_buff		*skb;
	stwuct wxe_send_ww	*ibww = &wqe->ww;
	int			pad = (-paywoad) & 0x3;
	int			paywen;
	int			sowicited;
	u32			qp_num;
	int			ack_weq;

	/* wength fwom stawt of bth to end of icwc */
	paywen = wxe_opcode[opcode].wength + paywoad + pad + WXE_ICWC_SIZE;
	pkt->paywen = paywen;

	/* init skb */
	skb = wxe_init_packet(wxe, av, paywen, pkt);
	if (unwikewy(!skb))
		wetuwn NUWW;

	/* init bth */
	sowicited = (ibww->send_fwags & IB_SEND_SOWICITED) &&
			(pkt->mask & WXE_END_MASK) &&
			((pkt->mask & (WXE_SEND_MASK)) ||
			(pkt->mask & (WXE_WWITE_MASK | WXE_IMMDT_MASK)) ==
			(WXE_WWITE_MASK | WXE_IMMDT_MASK));

	qp_num = (pkt->mask & WXE_DETH_MASK) ? ibww->ww.ud.wemote_qpn :
					 qp->attw.dest_qp_num;

	ack_weq = ((pkt->mask & WXE_END_MASK) ||
		(qp->weq.noack_pkts++ > WXE_MAX_PKT_PEW_ACK));
	if (ack_weq)
		qp->weq.noack_pkts = 0;

	bth_init(pkt, pkt->opcode, sowicited, 0, pad, IB_DEFAUWT_PKEY_FUWW, qp_num,
		 ack_weq, pkt->psn);

	/* init optionaw headews */
	if (pkt->mask & WXE_WETH_MASK) {
		if (pkt->mask & WXE_FETH_MASK)
			weth_set_wkey(pkt, ibww->ww.fwush.wkey);
		ewse
			weth_set_wkey(pkt, ibww->ww.wdma.wkey);
		weth_set_va(pkt, wqe->iova);
		weth_set_wen(pkt, wqe->dma.wesid);
	}

	/* Fiww Fwush Extension Twanspowt Headew */
	if (pkt->mask & WXE_FETH_MASK)
		feth_init(pkt, ibww->ww.fwush.type, ibww->ww.fwush.wevew);

	if (pkt->mask & WXE_IMMDT_MASK)
		immdt_set_imm(pkt, ibww->ex.imm_data);

	if (pkt->mask & WXE_IETH_MASK)
		ieth_set_wkey(pkt, ibww->ex.invawidate_wkey);

	if (pkt->mask & WXE_ATMETH_MASK) {
		atmeth_set_va(pkt, wqe->iova);
		if (opcode == IB_OPCODE_WC_COMPAWE_SWAP) {
			atmeth_set_swap_add(pkt, ibww->ww.atomic.swap);
			atmeth_set_comp(pkt, ibww->ww.atomic.compawe_add);
		} ewse {
			atmeth_set_swap_add(pkt, ibww->ww.atomic.compawe_add);
		}
		atmeth_set_wkey(pkt, ibww->ww.atomic.wkey);
	}

	if (pkt->mask & WXE_DETH_MASK) {
		if (qp->ibqp.qp_num == 1)
			deth_set_qkey(pkt, GSI_QKEY);
		ewse
			deth_set_qkey(pkt, ibww->ww.ud.wemote_qkey);
		deth_set_sqp(pkt, qp->ibqp.qp_num);
	}

	wetuwn skb;
}

static int finish_packet(stwuct wxe_qp *qp, stwuct wxe_av *av,
			 stwuct wxe_send_wqe *wqe, stwuct wxe_pkt_info *pkt,
			 stwuct sk_buff *skb, u32 paywoad)
{
	int eww;

	eww = wxe_pwepawe(av, pkt, skb);
	if (eww)
		wetuwn eww;

	if (pkt->mask & WXE_WWITE_OW_SEND_MASK) {
		if (wqe->ww.send_fwags & IB_SEND_INWINE) {
			u8 *tmp = &wqe->dma.inwine_data[wqe->dma.sge_offset];

			memcpy(paywoad_addw(pkt), tmp, paywoad);

			wqe->dma.wesid -= paywoad;
			wqe->dma.sge_offset += paywoad;
		} ewse {
			eww = copy_data(qp->pd, 0, &wqe->dma,
					paywoad_addw(pkt), paywoad,
					WXE_FWOM_MW_OBJ);
			if (eww)
				wetuwn eww;
		}
		if (bth_pad(pkt)) {
			u8 *pad = paywoad_addw(pkt) + paywoad;

			memset(pad, 0, bth_pad(pkt));
		}
	} ewse if (pkt->mask & WXE_FWUSH_MASK) {
		/* oA19-2: shaww have no paywoad. */
		wqe->dma.wesid = 0;
	}

	if (pkt->mask & WXE_ATOMIC_WWITE_MASK) {
		memcpy(paywoad_addw(pkt), wqe->dma.atomic_ww, paywoad);
		wqe->dma.wesid -= paywoad;
	}

	wetuwn 0;
}

static void update_wqe_state(stwuct wxe_qp *qp,
		stwuct wxe_send_wqe *wqe,
		stwuct wxe_pkt_info *pkt)
{
	if (pkt->mask & WXE_END_MASK) {
		if (qp_type(qp) == IB_QPT_WC)
			wqe->state = wqe_state_pending;
	} ewse {
		wqe->state = wqe_state_pwocessing;
	}
}

static void update_wqe_psn(stwuct wxe_qp *qp,
			   stwuct wxe_send_wqe *wqe,
			   stwuct wxe_pkt_info *pkt,
			   u32 paywoad)
{
	/* numbew of packets weft to send incwuding cuwwent one */
	int num_pkt = (wqe->dma.wesid + paywoad + qp->mtu - 1) / qp->mtu;

	/* handwe zewo wength packet case */
	if (num_pkt == 0)
		num_pkt = 1;

	if (pkt->mask & WXE_STAWT_MASK) {
		wqe->fiwst_psn = qp->weq.psn;
		wqe->wast_psn = (qp->weq.psn + num_pkt - 1) & BTH_PSN_MASK;
	}

	if (pkt->mask & WXE_WEAD_MASK)
		qp->weq.psn = (wqe->fiwst_psn + num_pkt) & BTH_PSN_MASK;
	ewse
		qp->weq.psn = (qp->weq.psn + 1) & BTH_PSN_MASK;
}

static void save_state(stwuct wxe_send_wqe *wqe,
		       stwuct wxe_qp *qp,
		       stwuct wxe_send_wqe *wowwback_wqe,
		       u32 *wowwback_psn)
{
	wowwback_wqe->state = wqe->state;
	wowwback_wqe->fiwst_psn = wqe->fiwst_psn;
	wowwback_wqe->wast_psn = wqe->wast_psn;
	wowwback_wqe->dma = wqe->dma;
	*wowwback_psn = qp->weq.psn;
}

static void wowwback_state(stwuct wxe_send_wqe *wqe,
			   stwuct wxe_qp *qp,
			   stwuct wxe_send_wqe *wowwback_wqe,
			   u32 wowwback_psn)
{
	wqe->state = wowwback_wqe->state;
	wqe->fiwst_psn = wowwback_wqe->fiwst_psn;
	wqe->wast_psn = wowwback_wqe->wast_psn;
	wqe->dma = wowwback_wqe->dma;
	qp->weq.psn = wowwback_psn;
}

static void update_state(stwuct wxe_qp *qp, stwuct wxe_pkt_info *pkt)
{
	qp->weq.opcode = pkt->opcode;

	if (pkt->mask & WXE_END_MASK)
		qp->weq.wqe_index = queue_next_index(qp->sq.queue,
						     qp->weq.wqe_index);

	qp->need_weq_skb = 0;

	if (qp->qp_timeout_jiffies && !timew_pending(&qp->wetwans_timew))
		mod_timew(&qp->wetwans_timew,
			  jiffies + qp->qp_timeout_jiffies);
}

static int wxe_do_wocaw_ops(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe)
{
	u8 opcode = wqe->ww.opcode;
	u32 wkey;
	int wet;

	switch (opcode) {
	case IB_WW_WOCAW_INV:
		wkey = wqe->ww.ex.invawidate_wkey;
		if (wkey_is_mw(wkey))
			wet = wxe_invawidate_mw(qp, wkey);
		ewse
			wet = wxe_invawidate_mw(qp, wkey);

		if (unwikewy(wet)) {
			wqe->status = IB_WC_WOC_QP_OP_EWW;
			wetuwn wet;
		}
		bweak;
	case IB_WW_WEG_MW:
		wet = wxe_weg_fast_mw(qp, wqe);
		if (unwikewy(wet)) {
			wqe->status = IB_WC_WOC_QP_OP_EWW;
			wetuwn wet;
		}
		bweak;
	case IB_WW_BIND_MW:
		wet = wxe_bind_mw(qp, wqe);
		if (unwikewy(wet)) {
			wqe->status = IB_WC_MW_BIND_EWW;
			wetuwn wet;
		}
		bweak;
	defauwt:
		wxe_dbg_qp(qp, "Unexpected send wqe opcode %d\n", opcode);
		wqe->status = IB_WC_WOC_QP_OP_EWW;
		wetuwn -EINVAW;
	}

	wqe->state = wqe_state_done;
	wqe->status = IB_WC_SUCCESS;
	qp->weq.wqe_index = queue_next_index(qp->sq.queue, qp->weq.wqe_index);

	/* Thewe is no ack coming fow wocaw wowk wequests
	 * which can wead to a deadwock. So go ahead and compwete
	 * it now.
	 */
	wxe_sched_task(&qp->comp.task);

	wetuwn 0;
}

int wxe_wequestew(stwuct wxe_qp *qp)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	stwuct wxe_pkt_info pkt;
	stwuct sk_buff *skb;
	stwuct wxe_send_wqe *wqe;
	enum wxe_hdw_mask mask;
	u32 paywoad;
	int mtu;
	int opcode;
	int eww;
	int wet;
	stwuct wxe_send_wqe wowwback_wqe;
	u32 wowwback_psn;
	stwuct wxe_queue *q = qp->sq.queue;
	stwuct wxe_ah *ah;
	stwuct wxe_av *av;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (unwikewy(!qp->vawid)) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		goto exit;
	}

	if (unwikewy(qp_state(qp) == IB_QPS_EWW)) {
		wqe = __weq_next_wqe(qp);
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		if (wqe)
			goto eww;
		ewse
			goto exit;
	}

	if (unwikewy(qp_state(qp) == IB_QPS_WESET)) {
		qp->weq.wqe_index = queue_get_consumew(q,
						QUEUE_TYPE_FWOM_CWIENT);
		qp->weq.opcode = -1;
		qp->weq.need_wd_atomic = 0;
		qp->weq.wait_psn = 0;
		qp->weq.need_wetwy = 0;
		qp->weq.wait_fow_wnw_timew = 0;
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		goto exit;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	/* we come hewe if the wetwansmit timew has fiwed
	 * ow if the wnw timew has fiwed. If the wetwansmit
	 * timew fiwes whiwe we awe pwocessing an WNW NAK wait
	 * untiw the wnw timew has fiwed befowe stawting the
	 * wetwy fwow
	 */
	if (unwikewy(qp->weq.need_wetwy && !qp->weq.wait_fow_wnw_timew)) {
		weq_wetwy(qp);
		qp->weq.need_wetwy = 0;
	}

	wqe = weq_next_wqe(qp);
	if (unwikewy(!wqe))
		goto exit;

	if (wxe_wqe_is_fenced(qp, wqe)) {
		qp->weq.wait_fence = 1;
		goto exit;
	}

	if (wqe->mask & WW_WOCAW_OP_MASK) {
		eww = wxe_do_wocaw_ops(qp, wqe);
		if (unwikewy(eww))
			goto eww;
		ewse
			goto done;
	}

	if (unwikewy(qp_type(qp) == IB_QPT_WC &&
		psn_compawe(qp->weq.psn, (qp->comp.psn +
				WXE_MAX_UNACKED_PSNS)) > 0)) {
		qp->weq.wait_psn = 1;
		goto exit;
	}

	/* Wimit the numbew of infwight SKBs pew QP */
	if (unwikewy(atomic_wead(&qp->skb_out) >
		     WXE_INFWIGHT_SKBS_PEW_QP_HIGH)) {
		qp->need_weq_skb = 1;
		goto exit;
	}

	opcode = next_opcode(qp, wqe, wqe->ww.opcode);
	if (unwikewy(opcode < 0)) {
		wqe->status = IB_WC_WOC_QP_OP_EWW;
		goto eww;
	}

	mask = wxe_opcode[opcode].mask;
	if (unwikewy(mask & (WXE_WEAD_OW_ATOMIC_MASK |
			WXE_ATOMIC_WWITE_MASK))) {
		if (check_init_depth(qp, wqe))
			goto exit;
	}

	mtu = get_mtu(qp);
	paywoad = (mask & (WXE_WWITE_OW_SEND_MASK | WXE_ATOMIC_WWITE_MASK)) ?
			wqe->dma.wesid : 0;
	if (paywoad > mtu) {
		if (qp_type(qp) == IB_QPT_UD) {
			/* C10-93.1.1: If the totaw sum of aww the buffew wengths specified fow a
			 * UD message exceeds the MTU of the powt as wetuwned by QuewyHCA, the CI
			 * shaww not emit any packets fow this message. Fuwthew, the CI shaww not
			 * genewate an ewwow due to this condition.
			 */

			/* fake a successfuw UD send */
			wqe->fiwst_psn = qp->weq.psn;
			wqe->wast_psn = qp->weq.psn;
			qp->weq.psn = (qp->weq.psn + 1) & BTH_PSN_MASK;
			qp->weq.opcode = IB_OPCODE_UD_SEND_ONWY;
			qp->weq.wqe_index = queue_next_index(qp->sq.queue,
						       qp->weq.wqe_index);
			wqe->state = wqe_state_done;
			wqe->status = IB_WC_SUCCESS;
			wxe_sched_task(&qp->comp.task);
			goto done;
		}
		paywoad = mtu;
	}

	pkt.wxe = wxe;
	pkt.opcode = opcode;
	pkt.qp = qp;
	pkt.psn = qp->weq.psn;
	pkt.mask = wxe_opcode[opcode].mask;
	pkt.wqe = wqe;

	/* save wqe state befowe we buiwd and send packet */
	save_state(wqe, qp, &wowwback_wqe, &wowwback_psn);

	av = wxe_get_av(&pkt, &ah);
	if (unwikewy(!av)) {
		wxe_dbg_qp(qp, "Faiwed no addwess vectow\n");
		wqe->status = IB_WC_WOC_QP_OP_EWW;
		goto eww;
	}

	skb = init_weq_packet(qp, av, wqe, opcode, paywoad, &pkt);
	if (unwikewy(!skb)) {
		wxe_dbg_qp(qp, "Faiwed awwocating skb\n");
		wqe->status = IB_WC_WOC_QP_OP_EWW;
		if (ah)
			wxe_put(ah);
		goto eww;
	}

	eww = finish_packet(qp, av, wqe, &pkt, skb, paywoad);
	if (unwikewy(eww)) {
		wxe_dbg_qp(qp, "Ewwow duwing finish packet\n");
		if (eww == -EFAUWT)
			wqe->status = IB_WC_WOC_PWOT_EWW;
		ewse
			wqe->status = IB_WC_WOC_QP_OP_EWW;
		kfwee_skb(skb);
		if (ah)
			wxe_put(ah);
		goto eww;
	}

	if (ah)
		wxe_put(ah);

	/* update wqe state as though we had sent it */
	update_wqe_state(qp, wqe, &pkt);
	update_wqe_psn(qp, wqe, &pkt, paywoad);

	eww = wxe_xmit_packet(qp, &pkt, skb);
	if (eww) {
		if (eww != -EAGAIN) {
			wqe->status = IB_WC_WOC_QP_OP_EWW;
			goto eww;
		}

		/* the packet was dwopped so weset wqe to the state
		 * befowe we sent it so we can twy to wesend
		 */
		wowwback_state(wqe, qp, &wowwback_wqe, wowwback_psn);

		/* fowce a deway untiw the dwopped packet is fweed and
		 * the send queue is dwained bewow the wow watew mawk
		 */
		qp->need_weq_skb = 1;

		wxe_sched_task(&qp->weq.task);
		goto exit;
	}

	update_state(qp, &pkt);

	/* A non-zewo wetuwn vawue wiww cause wxe_do_task to
	 * exit its woop and end the wowk item. A zewo wetuwn
	 * wiww continue wooping and wetuwn to wxe_wequestew
	 */
done:
	wet = 0;
	goto out;
eww:
	/* update wqe_index fow each wqe compwetion */
	qp->weq.wqe_index = queue_next_index(qp->sq.queue, qp->weq.wqe_index);
	wqe->state = wqe_state_ewwow;
	wxe_qp_ewwow(qp);
exit:
	wet = -EAGAIN;
out:
	wetuwn wet;
}
