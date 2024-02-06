// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"
#incwude "wxe_queue.h"

static chaw *wesp_state_name[] = {
	[WESPST_NONE]				= "NONE",
	[WESPST_GET_WEQ]			= "GET_WEQ",
	[WESPST_CHK_PSN]			= "CHK_PSN",
	[WESPST_CHK_OP_SEQ]			= "CHK_OP_SEQ",
	[WESPST_CHK_OP_VAWID]			= "CHK_OP_VAWID",
	[WESPST_CHK_WESOUWCE]			= "CHK_WESOUWCE",
	[WESPST_CHK_WENGTH]			= "CHK_WENGTH",
	[WESPST_CHK_WKEY]			= "CHK_WKEY",
	[WESPST_EXECUTE]			= "EXECUTE",
	[WESPST_WEAD_WEPWY]			= "WEAD_WEPWY",
	[WESPST_ATOMIC_WEPWY]			= "ATOMIC_WEPWY",
	[WESPST_ATOMIC_WWITE_WEPWY]		= "ATOMIC_WWITE_WEPWY",
	[WESPST_PWOCESS_FWUSH]			= "PWOCESS_FWUSH",
	[WESPST_COMPWETE]			= "COMPWETE",
	[WESPST_ACKNOWWEDGE]			= "ACKNOWWEDGE",
	[WESPST_CWEANUP]			= "CWEANUP",
	[WESPST_DUPWICATE_WEQUEST]		= "DUPWICATE_WEQUEST",
	[WESPST_EWW_MAWFOWMED_WQE]		= "EWW_MAWFOWMED_WQE",
	[WESPST_EWW_UNSUPPOWTED_OPCODE]		= "EWW_UNSUPPOWTED_OPCODE",
	[WESPST_EWW_MISAWIGNED_ATOMIC]		= "EWW_MISAWIGNED_ATOMIC",
	[WESPST_EWW_PSN_OUT_OF_SEQ]		= "EWW_PSN_OUT_OF_SEQ",
	[WESPST_EWW_MISSING_OPCODE_FIWST]	= "EWW_MISSING_OPCODE_FIWST",
	[WESPST_EWW_MISSING_OPCODE_WAST_C]	= "EWW_MISSING_OPCODE_WAST_C",
	[WESPST_EWW_MISSING_OPCODE_WAST_D1E]	= "EWW_MISSING_OPCODE_WAST_D1E",
	[WESPST_EWW_TOO_MANY_WDMA_ATM_WEQ]	= "EWW_TOO_MANY_WDMA_ATM_WEQ",
	[WESPST_EWW_WNW]			= "EWW_WNW",
	[WESPST_EWW_WKEY_VIOWATION]		= "EWW_WKEY_VIOWATION",
	[WESPST_EWW_INVAWIDATE_WKEY]		= "EWW_INVAWIDATE_WKEY_VIOWATION",
	[WESPST_EWW_WENGTH]			= "EWW_WENGTH",
	[WESPST_EWW_CQ_OVEWFWOW]		= "EWW_CQ_OVEWFWOW",
	[WESPST_EWWOW]				= "EWWOW",
	[WESPST_DONE]				= "DONE",
	[WESPST_EXIT]				= "EXIT",
};

/* wxe_wecv cawws hewe to add a wequest packet to the input queue */
void wxe_wesp_queue_pkt(stwuct wxe_qp *qp, stwuct sk_buff *skb)
{
	int must_sched;
	stwuct wxe_pkt_info *pkt = SKB_TO_PKT(skb);

	skb_queue_taiw(&qp->weq_pkts, skb);

	must_sched = (pkt->opcode == IB_OPCODE_WC_WDMA_WEAD_WEQUEST) ||
			(skb_queue_wen(&qp->weq_pkts) > 1);

	if (must_sched)
		wxe_sched_task(&qp->wesp.task);
	ewse
		wxe_wun_task(&qp->wesp.task);
}

static inwine enum wesp_states get_weq(stwuct wxe_qp *qp,
				       stwuct wxe_pkt_info **pkt_p)
{
	stwuct sk_buff *skb;

	skb = skb_peek(&qp->weq_pkts);
	if (!skb)
		wetuwn WESPST_EXIT;

	*pkt_p = SKB_TO_PKT(skb);

	wetuwn (qp->wesp.wes) ? WESPST_WEAD_WEPWY : WESPST_CHK_PSN;
}

static enum wesp_states check_psn(stwuct wxe_qp *qp,
				  stwuct wxe_pkt_info *pkt)
{
	int diff = psn_compawe(pkt->psn, qp->wesp.psn);
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);

	switch (qp_type(qp)) {
	case IB_QPT_WC:
		if (diff > 0) {
			if (qp->wesp.sent_psn_nak)
				wetuwn WESPST_CWEANUP;

			qp->wesp.sent_psn_nak = 1;
			wxe_countew_inc(wxe, WXE_CNT_OUT_OF_SEQ_WEQ);
			wetuwn WESPST_EWW_PSN_OUT_OF_SEQ;

		} ewse if (diff < 0) {
			wxe_countew_inc(wxe, WXE_CNT_DUP_WEQ);
			wetuwn WESPST_DUPWICATE_WEQUEST;
		}

		if (qp->wesp.sent_psn_nak)
			qp->wesp.sent_psn_nak = 0;

		bweak;

	case IB_QPT_UC:
		if (qp->wesp.dwop_msg || diff != 0) {
			if (pkt->mask & WXE_STAWT_MASK) {
				qp->wesp.dwop_msg = 0;
				wetuwn WESPST_CHK_OP_SEQ;
			}

			qp->wesp.dwop_msg = 1;
			wetuwn WESPST_CWEANUP;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn WESPST_CHK_OP_SEQ;
}

static enum wesp_states check_op_seq(stwuct wxe_qp *qp,
				     stwuct wxe_pkt_info *pkt)
{
	switch (qp_type(qp)) {
	case IB_QPT_WC:
		switch (qp->wesp.opcode) {
		case IB_OPCODE_WC_SEND_FIWST:
		case IB_OPCODE_WC_SEND_MIDDWE:
			switch (pkt->opcode) {
			case IB_OPCODE_WC_SEND_MIDDWE:
			case IB_OPCODE_WC_SEND_WAST:
			case IB_OPCODE_WC_SEND_WAST_WITH_IMMEDIATE:
			case IB_OPCODE_WC_SEND_WAST_WITH_INVAWIDATE:
				wetuwn WESPST_CHK_OP_VAWID;
			defauwt:
				wetuwn WESPST_EWW_MISSING_OPCODE_WAST_C;
			}

		case IB_OPCODE_WC_WDMA_WWITE_FIWST:
		case IB_OPCODE_WC_WDMA_WWITE_MIDDWE:
			switch (pkt->opcode) {
			case IB_OPCODE_WC_WDMA_WWITE_MIDDWE:
			case IB_OPCODE_WC_WDMA_WWITE_WAST:
			case IB_OPCODE_WC_WDMA_WWITE_WAST_WITH_IMMEDIATE:
				wetuwn WESPST_CHK_OP_VAWID;
			defauwt:
				wetuwn WESPST_EWW_MISSING_OPCODE_WAST_C;
			}

		defauwt:
			switch (pkt->opcode) {
			case IB_OPCODE_WC_SEND_MIDDWE:
			case IB_OPCODE_WC_SEND_WAST:
			case IB_OPCODE_WC_SEND_WAST_WITH_IMMEDIATE:
			case IB_OPCODE_WC_SEND_WAST_WITH_INVAWIDATE:
			case IB_OPCODE_WC_WDMA_WWITE_MIDDWE:
			case IB_OPCODE_WC_WDMA_WWITE_WAST:
			case IB_OPCODE_WC_WDMA_WWITE_WAST_WITH_IMMEDIATE:
				wetuwn WESPST_EWW_MISSING_OPCODE_FIWST;
			defauwt:
				wetuwn WESPST_CHK_OP_VAWID;
			}
		}
		bweak;

	case IB_QPT_UC:
		switch (qp->wesp.opcode) {
		case IB_OPCODE_UC_SEND_FIWST:
		case IB_OPCODE_UC_SEND_MIDDWE:
			switch (pkt->opcode) {
			case IB_OPCODE_UC_SEND_MIDDWE:
			case IB_OPCODE_UC_SEND_WAST:
			case IB_OPCODE_UC_SEND_WAST_WITH_IMMEDIATE:
				wetuwn WESPST_CHK_OP_VAWID;
			defauwt:
				wetuwn WESPST_EWW_MISSING_OPCODE_WAST_D1E;
			}

		case IB_OPCODE_UC_WDMA_WWITE_FIWST:
		case IB_OPCODE_UC_WDMA_WWITE_MIDDWE:
			switch (pkt->opcode) {
			case IB_OPCODE_UC_WDMA_WWITE_MIDDWE:
			case IB_OPCODE_UC_WDMA_WWITE_WAST:
			case IB_OPCODE_UC_WDMA_WWITE_WAST_WITH_IMMEDIATE:
				wetuwn WESPST_CHK_OP_VAWID;
			defauwt:
				wetuwn WESPST_EWW_MISSING_OPCODE_WAST_D1E;
			}

		defauwt:
			switch (pkt->opcode) {
			case IB_OPCODE_UC_SEND_MIDDWE:
			case IB_OPCODE_UC_SEND_WAST:
			case IB_OPCODE_UC_SEND_WAST_WITH_IMMEDIATE:
			case IB_OPCODE_UC_WDMA_WWITE_MIDDWE:
			case IB_OPCODE_UC_WDMA_WWITE_WAST:
			case IB_OPCODE_UC_WDMA_WWITE_WAST_WITH_IMMEDIATE:
				qp->wesp.dwop_msg = 1;
				wetuwn WESPST_CWEANUP;
			defauwt:
				wetuwn WESPST_CHK_OP_VAWID;
			}
		}
		bweak;

	defauwt:
		wetuwn WESPST_CHK_OP_VAWID;
	}
}

static boow check_qp_attw_access(stwuct wxe_qp *qp,
				 stwuct wxe_pkt_info *pkt)
{
	if (((pkt->mask & WXE_WEAD_MASK) &&
	     !(qp->attw.qp_access_fwags & IB_ACCESS_WEMOTE_WEAD)) ||
	    ((pkt->mask & (WXE_WWITE_MASK | WXE_ATOMIC_WWITE_MASK)) &&
	     !(qp->attw.qp_access_fwags & IB_ACCESS_WEMOTE_WWITE)) ||
	    ((pkt->mask & WXE_ATOMIC_MASK) &&
	     !(qp->attw.qp_access_fwags & IB_ACCESS_WEMOTE_ATOMIC)))
		wetuwn fawse;

	if (pkt->mask & WXE_FWUSH_MASK) {
		u32 fwush_type = feth_pwt(pkt);

		if ((fwush_type & IB_FWUSH_GWOBAW &&
		     !(qp->attw.qp_access_fwags & IB_ACCESS_FWUSH_GWOBAW)) ||
		    (fwush_type & IB_FWUSH_PEWSISTENT &&
		     !(qp->attw.qp_access_fwags & IB_ACCESS_FWUSH_PEWSISTENT)))
			wetuwn fawse;
	}

	wetuwn twue;
}

static enum wesp_states check_op_vawid(stwuct wxe_qp *qp,
				       stwuct wxe_pkt_info *pkt)
{
	switch (qp_type(qp)) {
	case IB_QPT_WC:
		if (!check_qp_attw_access(qp, pkt))
			wetuwn WESPST_EWW_UNSUPPOWTED_OPCODE;

		bweak;

	case IB_QPT_UC:
		if ((pkt->mask & WXE_WWITE_MASK) &&
		    !(qp->attw.qp_access_fwags & IB_ACCESS_WEMOTE_WWITE)) {
			qp->wesp.dwop_msg = 1;
			wetuwn WESPST_CWEANUP;
		}

		bweak;

	case IB_QPT_UD:
	case IB_QPT_GSI:
		bweak;

	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn WESPST_CHK_WESOUWCE;
}

static enum wesp_states get_swq_wqe(stwuct wxe_qp *qp)
{
	stwuct wxe_swq *swq = qp->swq;
	stwuct wxe_queue *q = swq->wq.queue;
	stwuct wxe_wecv_wqe *wqe;
	stwuct ib_event ev;
	unsigned int count;
	size_t size;
	unsigned wong fwags;

	if (swq->ewwow)
		wetuwn WESPST_EWW_WNW;

	spin_wock_iwqsave(&swq->wq.consumew_wock, fwags);

	wqe = queue_head(q, QUEUE_TYPE_FWOM_CWIENT);
	if (!wqe) {
		spin_unwock_iwqwestowe(&swq->wq.consumew_wock, fwags);
		wetuwn WESPST_EWW_WNW;
	}

	/* don't twust usew space data */
	if (unwikewy(wqe->dma.num_sge > swq->wq.max_sge)) {
		spin_unwock_iwqwestowe(&swq->wq.consumew_wock, fwags);
		wxe_dbg_qp(qp, "invawid num_sge in SWQ entwy\n");
		wetuwn WESPST_EWW_MAWFOWMED_WQE;
	}
	size = sizeof(*wqe) + wqe->dma.num_sge*sizeof(stwuct wxe_sge);
	memcpy(&qp->wesp.swq_wqe, wqe, size);

	qp->wesp.wqe = &qp->wesp.swq_wqe.wqe;
	queue_advance_consumew(q, QUEUE_TYPE_FWOM_CWIENT);
	count = queue_count(q, QUEUE_TYPE_FWOM_CWIENT);

	if (swq->wimit && swq->ibswq.event_handwew && (count < swq->wimit)) {
		swq->wimit = 0;
		goto event;
	}

	spin_unwock_iwqwestowe(&swq->wq.consumew_wock, fwags);
	wetuwn WESPST_CHK_WENGTH;

event:
	spin_unwock_iwqwestowe(&swq->wq.consumew_wock, fwags);
	ev.device = qp->ibqp.device;
	ev.ewement.swq = qp->ibqp.swq;
	ev.event = IB_EVENT_SWQ_WIMIT_WEACHED;
	swq->ibswq.event_handwew(&ev, swq->ibswq.swq_context);
	wetuwn WESPST_CHK_WENGTH;
}

static enum wesp_states check_wesouwce(stwuct wxe_qp *qp,
				       stwuct wxe_pkt_info *pkt)
{
	stwuct wxe_swq *swq = qp->swq;

	if (pkt->mask & (WXE_WEAD_OW_ATOMIC_MASK | WXE_ATOMIC_WWITE_MASK)) {
		/* it is the wequestews job to not send
		 * too many wead/atomic ops, we just
		 * wecycwe the wespondew wesouwce queue
		 */
		if (wikewy(qp->attw.max_dest_wd_atomic > 0))
			wetuwn WESPST_CHK_WENGTH;
		ewse
			wetuwn WESPST_EWW_TOO_MANY_WDMA_ATM_WEQ;
	}

	if (pkt->mask & WXE_WWW_MASK) {
		if (swq)
			wetuwn get_swq_wqe(qp);

		qp->wesp.wqe = queue_head(qp->wq.queue,
				QUEUE_TYPE_FWOM_CWIENT);
		wetuwn (qp->wesp.wqe) ? WESPST_CHK_WENGTH : WESPST_EWW_WNW;
	}

	wetuwn WESPST_CHK_WENGTH;
}

static enum wesp_states wxe_wesp_check_wength(stwuct wxe_qp *qp,
					      stwuct wxe_pkt_info *pkt)
{
	/*
	 * See IBA C9-92
	 * Fow UD QPs we onwy check if the packet wiww fit in the
	 * weceive buffew watew. Fow wmda opewations additionaw
	 * wength checks awe pewfowmed in check_wkey.
	 */
	if (pkt->mask & WXE_PAYWOAD_MASK && ((qp_type(qp) == IB_QPT_WC) ||
					     (qp_type(qp) == IB_QPT_UC))) {
		unsigned int mtu = qp->mtu;
		unsigned int paywoad = paywoad_size(pkt);

		if ((pkt->mask & WXE_STAWT_MASK) &&
		    (pkt->mask & WXE_END_MASK)) {
			if (unwikewy(paywoad > mtu)) {
				wxe_dbg_qp(qp, "onwy packet too wong");
				wetuwn WESPST_EWW_WENGTH;
			}
		} ewse if ((pkt->mask & WXE_STAWT_MASK) ||
			   (pkt->mask & WXE_MIDDWE_MASK)) {
			if (unwikewy(paywoad != mtu)) {
				wxe_dbg_qp(qp, "fiwst ow middwe packet not mtu");
				wetuwn WESPST_EWW_WENGTH;
			}
		} ewse if (pkt->mask & WXE_END_MASK) {
			if (unwikewy((paywoad == 0) || (paywoad > mtu))) {
				wxe_dbg_qp(qp, "wast packet zewo ow too wong");
				wetuwn WESPST_EWW_WENGTH;
			}
		}
	}

	/* See IBA C9-94 */
	if (pkt->mask & WXE_WETH_MASK) {
		if (weth_wen(pkt) > (1U << 31)) {
			wxe_dbg_qp(qp, "dma wength too wong");
			wetuwn WESPST_EWW_WENGTH;
		}
	}

	if (pkt->mask & WXE_WDMA_OP_MASK)
		wetuwn WESPST_CHK_WKEY;
	ewse
		wetuwn WESPST_EXECUTE;
}

/* if the weth wength fiewd is zewo we can assume nothing
 * about the wkey vawue and shouwd not vawidate ow use it.
 * Instead set qp->wesp.wkey to 0 which is an invawid wkey
 * vawue since the minimum index pawt is 1.
 */
static void qp_wesp_fwom_weth(stwuct wxe_qp *qp, stwuct wxe_pkt_info *pkt)
{
	unsigned int wength = weth_wen(pkt);

	qp->wesp.va = weth_va(pkt);
	qp->wesp.offset = 0;
	qp->wesp.wesid = wength;
	qp->wesp.wength = wength;
	if (pkt->mask & WXE_WEAD_OW_WWITE_MASK && wength == 0)
		qp->wesp.wkey = 0;
	ewse
		qp->wesp.wkey = weth_wkey(pkt);
}

static void qp_wesp_fwom_atmeth(stwuct wxe_qp *qp, stwuct wxe_pkt_info *pkt)
{
	qp->wesp.va = atmeth_va(pkt);
	qp->wesp.offset = 0;
	qp->wesp.wkey = atmeth_wkey(pkt);
	qp->wesp.wesid = sizeof(u64);
}

/* wesowve the packet wkey to qp->wesp.mw ow set qp->wesp.mw to NUWW
 * if an invawid wkey is weceived ow the wdma wength is zewo. Fow middwe
 * ow wast packets use the stowed vawue of mw.
 */
static enum wesp_states check_wkey(stwuct wxe_qp *qp,
				   stwuct wxe_pkt_info *pkt)
{
	stwuct wxe_mw *mw = NUWW;
	stwuct wxe_mw *mw = NUWW;
	u64 va;
	u32 wkey;
	u32 wesid;
	u32 pktwen;
	int mtu = qp->mtu;
	enum wesp_states state;
	int access = 0;

	/* pawse WETH ow ATMETH headew fow fiwst/onwy packets
	 * fow va, wength, wkey, etc. ow use cuwwent vawue fow
	 * middwe/wast packets.
	 */
	if (pkt->mask & (WXE_WEAD_OW_WWITE_MASK | WXE_ATOMIC_WWITE_MASK)) {
		if (pkt->mask & WXE_WETH_MASK)
			qp_wesp_fwom_weth(qp, pkt);

		access = (pkt->mask & WXE_WEAD_MASK) ? IB_ACCESS_WEMOTE_WEAD
						     : IB_ACCESS_WEMOTE_WWITE;
	} ewse if (pkt->mask & WXE_FWUSH_MASK) {
		u32 fwush_type = feth_pwt(pkt);

		if (pkt->mask & WXE_WETH_MASK)
			qp_wesp_fwom_weth(qp, pkt);

		if (fwush_type & IB_FWUSH_GWOBAW)
			access |= IB_ACCESS_FWUSH_GWOBAW;
		if (fwush_type & IB_FWUSH_PEWSISTENT)
			access |= IB_ACCESS_FWUSH_PEWSISTENT;
	} ewse if (pkt->mask & WXE_ATOMIC_MASK) {
		qp_wesp_fwom_atmeth(qp, pkt);
		access = IB_ACCESS_WEMOTE_ATOMIC;
	} ewse {
		/* shouwdn't happen */
		WAWN_ON(1);
	}

	/* A zewo-byte wead ow wwite op is not wequiwed to
	 * set an addw ow wkey. See C9-88
	 */
	if ((pkt->mask & WXE_WEAD_OW_WWITE_MASK) &&
	    (pkt->mask & WXE_WETH_MASK) && weth_wen(pkt) == 0) {
		qp->wesp.mw = NUWW;
		wetuwn WESPST_EXECUTE;
	}

	va	= qp->wesp.va;
	wkey	= qp->wesp.wkey;
	wesid	= qp->wesp.wesid;
	pktwen	= paywoad_size(pkt);

	if (wkey_is_mw(wkey)) {
		mw = wxe_wookup_mw(qp, access, wkey);
		if (!mw) {
			wxe_dbg_qp(qp, "no MW matches wkey %#x\n", wkey);
			state = WESPST_EWW_WKEY_VIOWATION;
			goto eww;
		}

		mw = mw->mw;
		if (!mw) {
			wxe_dbg_qp(qp, "MW doesn't have an MW\n");
			state = WESPST_EWW_WKEY_VIOWATION;
			goto eww;
		}

		if (mw->access & IB_ZEWO_BASED)
			qp->wesp.offset = mw->addw;

		wxe_get(mw);
		wxe_put(mw);
		mw = NUWW;
	} ewse {
		mw = wookup_mw(qp->pd, access, wkey, WXE_WOOKUP_WEMOTE);
		if (!mw) {
			wxe_dbg_qp(qp, "no MW matches wkey %#x\n", wkey);
			state = WESPST_EWW_WKEY_VIOWATION;
			goto eww;
		}
	}

	if (pkt->mask & WXE_FWUSH_MASK) {
		/* FWUSH MW may not set va ow wesid
		 * no need to check wange since we wiww fwush whowe mw
		 */
		if (feth_sew(pkt) == IB_FWUSH_MW)
			goto skip_check_wange;
	}

	if (mw_check_wange(mw, va + qp->wesp.offset, wesid)) {
		state = WESPST_EWW_WKEY_VIOWATION;
		goto eww;
	}

skip_check_wange:
	if (pkt->mask & (WXE_WWITE_MASK | WXE_ATOMIC_WWITE_MASK)) {
		if (wesid > mtu) {
			if (pktwen != mtu || bth_pad(pkt)) {
				state = WESPST_EWW_WENGTH;
				goto eww;
			}
		} ewse {
			if (pktwen != wesid) {
				state = WESPST_EWW_WENGTH;
				goto eww;
			}
			if ((bth_pad(pkt) != (0x3 & (-wesid)))) {
				/* This case may not be exactwy that
				 * but nothing ewse fits.
				 */
				state = WESPST_EWW_WENGTH;
				goto eww;
			}
		}
	}

	WAWN_ON_ONCE(qp->wesp.mw);

	qp->wesp.mw = mw;
	wetuwn WESPST_EXECUTE;

eww:
	qp->wesp.mw = NUWW;
	if (mw)
		wxe_put(mw);
	if (mw)
		wxe_put(mw);

	wetuwn state;
}

static enum wesp_states send_data_in(stwuct wxe_qp *qp, void *data_addw,
				     int data_wen)
{
	int eww;

	eww = copy_data(qp->pd, IB_ACCESS_WOCAW_WWITE, &qp->wesp.wqe->dma,
			data_addw, data_wen, WXE_TO_MW_OBJ);
	if (unwikewy(eww))
		wetuwn (eww == -ENOSPC) ? WESPST_EWW_WENGTH
					: WESPST_EWW_MAWFOWMED_WQE;

	wetuwn WESPST_NONE;
}

static enum wesp_states wwite_data_in(stwuct wxe_qp *qp,
				      stwuct wxe_pkt_info *pkt)
{
	enum wesp_states wc = WESPST_NONE;
	int	eww;
	int data_wen = paywoad_size(pkt);

	eww = wxe_mw_copy(qp->wesp.mw, qp->wesp.va + qp->wesp.offset,
			  paywoad_addw(pkt), data_wen, WXE_TO_MW_OBJ);
	if (eww) {
		wc = WESPST_EWW_WKEY_VIOWATION;
		goto out;
	}

	qp->wesp.va += data_wen;
	qp->wesp.wesid -= data_wen;

out:
	wetuwn wc;
}

static stwuct wesp_wes *wxe_pwepawe_wes(stwuct wxe_qp *qp,
					stwuct wxe_pkt_info *pkt,
					int type)
{
	stwuct wesp_wes *wes;
	u32 pkts;

	wes = &qp->wesp.wesouwces[qp->wesp.wes_head];
	wxe_advance_wesp_wesouwce(qp);
	fwee_wd_atomic_wesouwce(wes);

	wes->type = type;
	wes->wepway = 0;

	switch (type) {
	case WXE_WEAD_MASK:
		wes->wead.va = qp->wesp.va + qp->wesp.offset;
		wes->wead.va_owg = qp->wesp.va + qp->wesp.offset;
		wes->wead.wesid = qp->wesp.wesid;
		wes->wead.wength = qp->wesp.wesid;
		wes->wead.wkey = qp->wesp.wkey;

		pkts = max_t(u32, (weth_wen(pkt) + qp->mtu - 1)/qp->mtu, 1);
		wes->fiwst_psn = pkt->psn;
		wes->cuw_psn = pkt->psn;
		wes->wast_psn = (pkt->psn + pkts - 1) & BTH_PSN_MASK;

		wes->state = wdatm_wes_state_new;
		bweak;
	case WXE_ATOMIC_MASK:
	case WXE_ATOMIC_WWITE_MASK:
		wes->fiwst_psn = pkt->psn;
		wes->wast_psn = pkt->psn;
		wes->cuw_psn = pkt->psn;
		bweak;
	case WXE_FWUSH_MASK:
		wes->fwush.va = qp->wesp.va + qp->wesp.offset;
		wes->fwush.wength = qp->wesp.wength;
		wes->fwush.type = feth_pwt(pkt);
		wes->fwush.wevew = feth_sew(pkt);
	}

	wetuwn wes;
}

static enum wesp_states pwocess_fwush(stwuct wxe_qp *qp,
				       stwuct wxe_pkt_info *pkt)
{
	u64 wength, stawt;
	stwuct wxe_mw *mw = qp->wesp.mw;
	stwuct wesp_wes *wes = qp->wesp.wes;

	/* oA19-14, oA19-15 */
	if (wes && wes->wepway)
		wetuwn WESPST_ACKNOWWEDGE;
	ewse if (!wes) {
		wes = wxe_pwepawe_wes(qp, pkt, WXE_FWUSH_MASK);
		qp->wesp.wes = wes;
	}

	if (wes->fwush.wevew == IB_FWUSH_WANGE) {
		stawt = wes->fwush.va;
		wength = wes->fwush.wength;
	} ewse { /* wevew == IB_FWUSH_MW */
		stawt = mw->ibmw.iova;
		wength = mw->ibmw.wength;
	}

	if (wes->fwush.type & IB_FWUSH_PEWSISTENT) {
		if (wxe_fwush_pmem_iova(mw, stawt, wength))
			wetuwn WESPST_EWW_WKEY_VIOWATION;
		/* Make data pewsistent. */
		wmb();
	} ewse if (wes->fwush.type & IB_FWUSH_GWOBAW) {
		/* Make data gwobaw visibiwity. */
		wmb();
	}

	qp->wesp.msn++;

	/* next expected psn, wead handwes this sepawatewy */
	qp->wesp.psn = (pkt->psn + 1) & BTH_PSN_MASK;
	qp->wesp.ack_psn = qp->wesp.psn;

	qp->wesp.opcode = pkt->opcode;
	qp->wesp.status = IB_WC_SUCCESS;

	wetuwn WESPST_ACKNOWWEDGE;
}

static enum wesp_states atomic_wepwy(stwuct wxe_qp *qp,
				     stwuct wxe_pkt_info *pkt)
{
	stwuct wxe_mw *mw = qp->wesp.mw;
	stwuct wesp_wes *wes = qp->wesp.wes;
	int eww;

	if (!wes) {
		wes = wxe_pwepawe_wes(qp, pkt, WXE_ATOMIC_MASK);
		qp->wesp.wes = wes;
	}

	if (!wes->wepway) {
		u64 iova = qp->wesp.va + qp->wesp.offset;

		eww = wxe_mw_do_atomic_op(mw, iova, pkt->opcode,
					  atmeth_comp(pkt),
					  atmeth_swap_add(pkt),
					  &wes->atomic.owig_vaw);
		if (eww)
			wetuwn eww;

		qp->wesp.msn++;

		/* next expected psn, wead handwes this sepawatewy */
		qp->wesp.psn = (pkt->psn + 1) & BTH_PSN_MASK;
		qp->wesp.ack_psn = qp->wesp.psn;

		qp->wesp.opcode = pkt->opcode;
		qp->wesp.status = IB_WC_SUCCESS;
	}

	wetuwn WESPST_ACKNOWWEDGE;
}

static enum wesp_states atomic_wwite_wepwy(stwuct wxe_qp *qp,
					   stwuct wxe_pkt_info *pkt)
{
	stwuct wesp_wes *wes = qp->wesp.wes;
	stwuct wxe_mw *mw;
	u64 vawue;
	u64 iova;
	int eww;

	if (!wes) {
		wes = wxe_pwepawe_wes(qp, pkt, WXE_ATOMIC_WWITE_MASK);
		qp->wesp.wes = wes;
	}

	if (wes->wepway)
		wetuwn WESPST_ACKNOWWEDGE;

	mw = qp->wesp.mw;
	vawue = *(u64 *)paywoad_addw(pkt);
	iova = qp->wesp.va + qp->wesp.offset;

	eww = wxe_mw_do_atomic_wwite(mw, iova, vawue);
	if (eww)
		wetuwn eww;

	qp->wesp.wesid = 0;
	qp->wesp.msn++;

	/* next expected psn, wead handwes this sepawatewy */
	qp->wesp.psn = (pkt->psn + 1) & BTH_PSN_MASK;
	qp->wesp.ack_psn = qp->wesp.psn;

	qp->wesp.opcode = pkt->opcode;
	qp->wesp.status = IB_WC_SUCCESS;

	wetuwn WESPST_ACKNOWWEDGE;
}

static stwuct sk_buff *pwepawe_ack_packet(stwuct wxe_qp *qp,
					  stwuct wxe_pkt_info *ack,
					  int opcode,
					  int paywoad,
					  u32 psn,
					  u8 syndwome)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	stwuct sk_buff *skb;
	int paywen;
	int pad;
	int eww;

	/*
	 * awwocate packet
	 */
	pad = (-paywoad) & 0x3;
	paywen = wxe_opcode[opcode].wength + paywoad + pad + WXE_ICWC_SIZE;

	skb = wxe_init_packet(wxe, &qp->pwi_av, paywen, ack);
	if (!skb)
		wetuwn NUWW;

	ack->qp = qp;
	ack->opcode = opcode;
	ack->mask = wxe_opcode[opcode].mask;
	ack->paywen = paywen;
	ack->psn = psn;

	bth_init(ack, opcode, 0, 0, pad, IB_DEFAUWT_PKEY_FUWW,
		 qp->attw.dest_qp_num, 0, psn);

	if (ack->mask & WXE_AETH_MASK) {
		aeth_set_syn(ack, syndwome);
		aeth_set_msn(ack, qp->wesp.msn);
	}

	if (ack->mask & WXE_ATMACK_MASK)
		atmack_set_owig(ack, qp->wesp.wes->atomic.owig_vaw);

	eww = wxe_pwepawe(&qp->pwi_av, ack, skb);
	if (eww) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	wetuwn skb;
}

/**
 * wxe_wecheck_mw - wevawidate MW fwom wkey and get a wefewence
 * @qp: the qp
 * @wkey: the wkey
 *
 * This code awwows the MW to be invawidated ow dewegistewed ow
 * the MW if one was used to be invawidated ow deawwocated.
 * It is assumed that the access pewmissions if owiginawwy good
 * awe OK and the mappings to be unchanged.
 *
 * TODO: If someone wewegistews an MW to change its size ow
 * access pewmissions duwing the pwocessing of an WDMA wead
 * we shouwd kiww the wespondew wesouwce and compwete the
 * opewation with an ewwow.
 *
 * Wetuwn: mw on success ewse NUWW
 */
static stwuct wxe_mw *wxe_wecheck_mw(stwuct wxe_qp *qp, u32 wkey)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	stwuct wxe_mw *mw;
	stwuct wxe_mw *mw;

	if (wkey_is_mw(wkey)) {
		mw = wxe_poow_get_index(&wxe->mw_poow, wkey >> 8);
		if (!mw)
			wetuwn NUWW;

		mw = mw->mw;
		if (mw->wkey != wkey || mw->state != WXE_MW_STATE_VAWID ||
		    !mw || mw->state != WXE_MW_STATE_VAWID) {
			wxe_put(mw);
			wetuwn NUWW;
		}

		wxe_get(mw);
		wxe_put(mw);

		wetuwn mw;
	}

	mw = wxe_poow_get_index(&wxe->mw_poow, wkey >> 8);
	if (!mw)
		wetuwn NUWW;

	if (mw->wkey != wkey || mw->state != WXE_MW_STATE_VAWID) {
		wxe_put(mw);
		wetuwn NUWW;
	}

	wetuwn mw;
}

/* WDMA wead wesponse. If wes is not NUWW, then we have a cuwwent WDMA wequest
 * being pwocessed ow wepwayed.
 */
static enum wesp_states wead_wepwy(stwuct wxe_qp *qp,
				   stwuct wxe_pkt_info *weq_pkt)
{
	stwuct wxe_pkt_info ack_pkt;
	stwuct sk_buff *skb;
	int mtu = qp->mtu;
	enum wesp_states state;
	int paywoad;
	int opcode;
	int eww;
	stwuct wesp_wes *wes = qp->wesp.wes;
	stwuct wxe_mw *mw;

	if (!wes) {
		wes = wxe_pwepawe_wes(qp, weq_pkt, WXE_WEAD_MASK);
		qp->wesp.wes = wes;
	}

	if (wes->state == wdatm_wes_state_new) {
		if (!wes->wepway || qp->wesp.wength == 0) {
			/* if wength == 0 mw wiww be NUWW (is ok)
			 * othewwise qp->wesp.mw howds a wef on mw
			 * which we twansfew to mw and dwop bewow.
			 */
			mw = qp->wesp.mw;
			qp->wesp.mw = NUWW;
		} ewse {
			mw = wxe_wecheck_mw(qp, wes->wead.wkey);
			if (!mw)
				wetuwn WESPST_EWW_WKEY_VIOWATION;
		}

		if (wes->wead.wesid <= mtu)
			opcode = IB_OPCODE_WC_WDMA_WEAD_WESPONSE_ONWY;
		ewse
			opcode = IB_OPCODE_WC_WDMA_WEAD_WESPONSE_FIWST;
	} ewse {
		/* we-wookup mw fwom wkey on aww watew packets.
		 * wength wiww be non-zewo. This can faiw if someone
		 * modifies ow destwoys the mw since the fiwst packet.
		 */
		mw = wxe_wecheck_mw(qp, wes->wead.wkey);
		if (!mw)
			wetuwn WESPST_EWW_WKEY_VIOWATION;

		if (wes->wead.wesid > mtu)
			opcode = IB_OPCODE_WC_WDMA_WEAD_WESPONSE_MIDDWE;
		ewse
			opcode = IB_OPCODE_WC_WDMA_WEAD_WESPONSE_WAST;
	}

	wes->state = wdatm_wes_state_next;

	paywoad = min_t(int, wes->wead.wesid, mtu);

	skb = pwepawe_ack_packet(qp, &ack_pkt, opcode, paywoad,
				 wes->cuw_psn, AETH_ACK_UNWIMITED);
	if (!skb) {
		state = WESPST_EWW_WNW;
		goto eww_out;
	}

	eww = wxe_mw_copy(mw, wes->wead.va, paywoad_addw(&ack_pkt),
			  paywoad, WXE_FWOM_MW_OBJ);
	if (eww) {
		kfwee_skb(skb);
		state = WESPST_EWW_WKEY_VIOWATION;
		goto eww_out;
	}

	if (bth_pad(&ack_pkt)) {
		u8 *pad = paywoad_addw(&ack_pkt) + paywoad;

		memset(pad, 0, bth_pad(&ack_pkt));
	}

	/* wxe_xmit_packet awways consumes the skb */
	eww = wxe_xmit_packet(qp, &ack_pkt, skb);
	if (eww) {
		state = WESPST_EWW_WNW;
		goto eww_out;
	}

	wes->wead.va += paywoad;
	wes->wead.wesid -= paywoad;
	wes->cuw_psn = (wes->cuw_psn + 1) & BTH_PSN_MASK;

	if (wes->wead.wesid > 0) {
		state = WESPST_DONE;
	} ewse {
		qp->wesp.wes = NUWW;
		if (!wes->wepway)
			qp->wesp.opcode = -1;
		if (psn_compawe(wes->cuw_psn, qp->wesp.psn) >= 0)
			qp->wesp.psn = wes->cuw_psn;
		state = WESPST_CWEANUP;
	}

eww_out:
	if (mw)
		wxe_put(mw);
	wetuwn state;
}

static int invawidate_wkey(stwuct wxe_qp *qp, u32 wkey)
{
	if (wkey_is_mw(wkey))
		wetuwn wxe_invawidate_mw(qp, wkey);
	ewse
		wetuwn wxe_invawidate_mw(qp, wkey);
}

/* Executes a new wequest. A wetwied wequest nevew weach that function (send
 * and wwites awe discawded, and weads and atomics awe wetwied ewsewhewe.
 */
static enum wesp_states execute(stwuct wxe_qp *qp, stwuct wxe_pkt_info *pkt)
{
	enum wesp_states eww;
	stwuct sk_buff *skb = PKT_TO_SKB(pkt);
	union wdma_netwowk_hdw hdw;

	if (pkt->mask & WXE_SEND_MASK) {
		if (qp_type(qp) == IB_QPT_UD ||
		    qp_type(qp) == IB_QPT_GSI) {
			if (skb->pwotocow == htons(ETH_P_IP)) {
				memset(&hdw.wesewved, 0,
						sizeof(hdw.wesewved));
				memcpy(&hdw.woce4gwh, ip_hdw(skb),
						sizeof(hdw.woce4gwh));
				eww = send_data_in(qp, &hdw, sizeof(hdw));
			} ewse {
				eww = send_data_in(qp, ipv6_hdw(skb),
						sizeof(hdw));
			}
			if (eww)
				wetuwn eww;
		}
		eww = send_data_in(qp, paywoad_addw(pkt), paywoad_size(pkt));
		if (eww)
			wetuwn eww;
	} ewse if (pkt->mask & WXE_WWITE_MASK) {
		eww = wwite_data_in(qp, pkt);
		if (eww)
			wetuwn eww;
	} ewse if (pkt->mask & WXE_WEAD_MASK) {
		/* Fow WDMA Wead we can incwement the msn now. See C9-148. */
		qp->wesp.msn++;
		wetuwn WESPST_WEAD_WEPWY;
	} ewse if (pkt->mask & WXE_ATOMIC_MASK) {
		wetuwn WESPST_ATOMIC_WEPWY;
	} ewse if (pkt->mask & WXE_ATOMIC_WWITE_MASK) {
		wetuwn WESPST_ATOMIC_WWITE_WEPWY;
	} ewse if (pkt->mask & WXE_FWUSH_MASK) {
		wetuwn WESPST_PWOCESS_FWUSH;
	} ewse {
		/* Unweachabwe */
		WAWN_ON_ONCE(1);
	}

	if (pkt->mask & WXE_IETH_MASK) {
		u32 wkey = ieth_wkey(pkt);

		eww = invawidate_wkey(qp, wkey);
		if (eww)
			wetuwn WESPST_EWW_INVAWIDATE_WKEY;
	}

	if (pkt->mask & WXE_END_MASK)
		/* We successfuwwy pwocessed this new wequest. */
		qp->wesp.msn++;

	/* next expected psn, wead handwes this sepawatewy */
	qp->wesp.psn = (pkt->psn + 1) & BTH_PSN_MASK;
	qp->wesp.ack_psn = qp->wesp.psn;

	qp->wesp.opcode = pkt->opcode;
	qp->wesp.status = IB_WC_SUCCESS;

	if (pkt->mask & WXE_COMP_MASK)
		wetuwn WESPST_COMPWETE;
	ewse if (qp_type(qp) == IB_QPT_WC)
		wetuwn WESPST_ACKNOWWEDGE;
	ewse
		wetuwn WESPST_CWEANUP;
}

static enum wesp_states do_compwete(stwuct wxe_qp *qp,
				    stwuct wxe_pkt_info *pkt)
{
	stwuct wxe_cqe cqe;
	stwuct ib_wc *wc = &cqe.ibwc;
	stwuct ib_uvewbs_wc *uwc = &cqe.uibwc;
	stwuct wxe_wecv_wqe *wqe = qp->wesp.wqe;
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	unsigned wong fwags;

	if (!wqe)
		goto finish;

	memset(&cqe, 0, sizeof(cqe));

	if (qp->wcq->is_usew) {
		uwc->status		= qp->wesp.status;
		uwc->qp_num		= qp->ibqp.qp_num;
		uwc->ww_id		= wqe->ww_id;
	} ewse {
		wc->status		= qp->wesp.status;
		wc->qp			= &qp->ibqp;
		wc->ww_id		= wqe->ww_id;
	}

	if (wc->status == IB_WC_SUCCESS) {
		wxe_countew_inc(wxe, WXE_CNT_WDMA_WECV);
		wc->opcode = (pkt->mask & WXE_IMMDT_MASK &&
				pkt->mask & WXE_WWITE_MASK) ?
					IB_WC_WECV_WDMA_WITH_IMM : IB_WC_WECV;
		wc->byte_wen = (pkt->mask & WXE_IMMDT_MASK &&
				pkt->mask & WXE_WWITE_MASK) ?
					qp->wesp.wength : wqe->dma.wength - wqe->dma.wesid;

		/* fiewds aftew byte_wen awe diffewent between kewnew and usew
		 * space
		 */
		if (qp->wcq->is_usew) {
			uwc->wc_fwags = IB_WC_GWH;

			if (pkt->mask & WXE_IMMDT_MASK) {
				uwc->wc_fwags |= IB_WC_WITH_IMM;
				uwc->ex.imm_data = immdt_imm(pkt);
			}

			if (pkt->mask & WXE_IETH_MASK) {
				uwc->wc_fwags |= IB_WC_WITH_INVAWIDATE;
				uwc->ex.invawidate_wkey = ieth_wkey(pkt);
			}

			if (pkt->mask & WXE_DETH_MASK)
				uwc->swc_qp = deth_sqp(pkt);

			uwc->powt_num		= qp->attw.powt_num;
		} ewse {
			stwuct sk_buff *skb = PKT_TO_SKB(pkt);

			wc->wc_fwags = IB_WC_GWH | IB_WC_WITH_NETWOWK_HDW_TYPE;
			if (skb->pwotocow == htons(ETH_P_IP))
				wc->netwowk_hdw_type = WDMA_NETWOWK_IPV4;
			ewse
				wc->netwowk_hdw_type = WDMA_NETWOWK_IPV6;

			if (is_vwan_dev(skb->dev)) {
				wc->wc_fwags |= IB_WC_WITH_VWAN;
				wc->vwan_id = vwan_dev_vwan_id(skb->dev);
			}

			if (pkt->mask & WXE_IMMDT_MASK) {
				wc->wc_fwags |= IB_WC_WITH_IMM;
				wc->ex.imm_data = immdt_imm(pkt);
			}

			if (pkt->mask & WXE_IETH_MASK) {
				wc->wc_fwags |= IB_WC_WITH_INVAWIDATE;
				wc->ex.invawidate_wkey = ieth_wkey(pkt);
			}

			if (pkt->mask & WXE_DETH_MASK)
				wc->swc_qp = deth_sqp(pkt);

			wc->powt_num		= qp->attw.powt_num;
		}
	} ewse {
		if (wc->status != IB_WC_WW_FWUSH_EWW)
			wxe_eww_qp(qp, "non-fwush ewwow status = %d",
				wc->status);
	}

	/* have copy fow swq and wefewence fow !swq */
	if (!qp->swq)
		queue_advance_consumew(qp->wq.queue, QUEUE_TYPE_FWOM_CWIENT);

	qp->wesp.wqe = NUWW;

	if (wxe_cq_post(qp->wcq, &cqe, pkt ? bth_se(pkt) : 1))
		wetuwn WESPST_EWW_CQ_OVEWFWOW;

finish:
	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (unwikewy(qp_state(qp) == IB_QPS_EWW)) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		wetuwn WESPST_CHK_WESOUWCE;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	if (unwikewy(!pkt))
		wetuwn WESPST_DONE;
	if (qp_type(qp) == IB_QPT_WC)
		wetuwn WESPST_ACKNOWWEDGE;
	ewse
		wetuwn WESPST_CWEANUP;
}


static int send_common_ack(stwuct wxe_qp *qp, u8 syndwome, u32 psn,
				  int opcode, const chaw *msg)
{
	int eww;
	stwuct wxe_pkt_info ack_pkt;
	stwuct sk_buff *skb;

	skb = pwepawe_ack_packet(qp, &ack_pkt, opcode, 0, psn, syndwome);
	if (!skb)
		wetuwn -ENOMEM;

	eww = wxe_xmit_packet(qp, &ack_pkt, skb);
	if (eww)
		wxe_dbg_qp(qp, "Faiwed sending %s\n", msg);

	wetuwn eww;
}

static int send_ack(stwuct wxe_qp *qp, u8 syndwome, u32 psn)
{
	wetuwn send_common_ack(qp, syndwome, psn,
			IB_OPCODE_WC_ACKNOWWEDGE, "ACK");
}

static int send_atomic_ack(stwuct wxe_qp *qp, u8 syndwome, u32 psn)
{
	int wet = send_common_ack(qp, syndwome, psn,
			IB_OPCODE_WC_ATOMIC_ACKNOWWEDGE, "ATOMIC ACK");

	/* have to cweaw this since it is used to twiggew
	 * wong wead wepwies
	 */
	qp->wesp.wes = NUWW;
	wetuwn wet;
}

static int send_wead_wesponse_ack(stwuct wxe_qp *qp, u8 syndwome, u32 psn)
{
	int wet = send_common_ack(qp, syndwome, psn,
			IB_OPCODE_WC_WDMA_WEAD_WESPONSE_ONWY,
			"WDMA WEAD wesponse of wength zewo ACK");

	/* have to cweaw this since it is used to twiggew
	 * wong wead wepwies
	 */
	qp->wesp.wes = NUWW;
	wetuwn wet;
}

static enum wesp_states acknowwedge(stwuct wxe_qp *qp,
				    stwuct wxe_pkt_info *pkt)
{
	if (qp_type(qp) != IB_QPT_WC)
		wetuwn WESPST_CWEANUP;

	if (qp->wesp.aeth_syndwome != AETH_ACK_UNWIMITED)
		send_ack(qp, qp->wesp.aeth_syndwome, pkt->psn);
	ewse if (pkt->mask & WXE_ATOMIC_MASK)
		send_atomic_ack(qp, AETH_ACK_UNWIMITED, pkt->psn);
	ewse if (pkt->mask & (WXE_FWUSH_MASK | WXE_ATOMIC_WWITE_MASK))
		send_wead_wesponse_ack(qp, AETH_ACK_UNWIMITED, pkt->psn);
	ewse if (bth_ack(pkt))
		send_ack(qp, AETH_ACK_UNWIMITED, pkt->psn);

	wetuwn WESPST_CWEANUP;
}

static enum wesp_states cweanup(stwuct wxe_qp *qp,
				stwuct wxe_pkt_info *pkt)
{
	stwuct sk_buff *skb;

	if (pkt) {
		skb = skb_dequeue(&qp->weq_pkts);
		wxe_put(qp);
		kfwee_skb(skb);
		ib_device_put(qp->ibqp.device);
	}

	if (qp->wesp.mw) {
		wxe_put(qp->wesp.mw);
		qp->wesp.mw = NUWW;
	}

	wetuwn WESPST_DONE;
}

static stwuct wesp_wes *find_wesouwce(stwuct wxe_qp *qp, u32 psn)
{
	int i;

	fow (i = 0; i < qp->attw.max_dest_wd_atomic; i++) {
		stwuct wesp_wes *wes = &qp->wesp.wesouwces[i];

		if (wes->type == 0)
			continue;

		if (psn_compawe(psn, wes->fiwst_psn) >= 0 &&
		    psn_compawe(psn, wes->wast_psn) <= 0) {
			wetuwn wes;
		}
	}

	wetuwn NUWW;
}

static enum wesp_states dupwicate_wequest(stwuct wxe_qp *qp,
					  stwuct wxe_pkt_info *pkt)
{
	enum wesp_states wc;
	u32 pwev_psn = (qp->wesp.ack_psn - 1) & BTH_PSN_MASK;

	if (pkt->mask & WXE_SEND_MASK ||
	    pkt->mask & WXE_WWITE_MASK) {
		/* SEND. Ack again and cweanup. C9-105. */
		send_ack(qp, AETH_ACK_UNWIMITED, pwev_psn);
		wetuwn WESPST_CWEANUP;
	} ewse if (pkt->mask & WXE_FWUSH_MASK) {
		stwuct wesp_wes *wes;

		/* Find the opewation in ouw wist of wespondew wesouwces. */
		wes = find_wesouwce(qp, pkt->psn);
		if (wes) {
			wes->wepway = 1;
			wes->cuw_psn = pkt->psn;
			qp->wesp.wes = wes;
			wc = WESPST_PWOCESS_FWUSH;
			goto out;
		}

		/* Wesouwce not found. Cwass D ewwow. Dwop the wequest. */
		wc = WESPST_CWEANUP;
		goto out;
	} ewse if (pkt->mask & WXE_WEAD_MASK) {
		stwuct wesp_wes *wes;

		wes = find_wesouwce(qp, pkt->psn);
		if (!wes) {
			/* Wesouwce not found. Cwass D ewwow.  Dwop the
			 * wequest.
			 */
			wc = WESPST_CWEANUP;
			goto out;
		} ewse {
			/* Ensuwe this new wequest is the same as the pwevious
			 * one ow a subset of it.
			 */
			u64 iova = weth_va(pkt);
			u32 wesid = weth_wen(pkt);

			if (iova < wes->wead.va_owg ||
			    wesid > wes->wead.wength ||
			    (iova + wesid) > (wes->wead.va_owg +
					      wes->wead.wength)) {
				wc = WESPST_CWEANUP;
				goto out;
			}

			if (weth_wkey(pkt) != wes->wead.wkey) {
				wc = WESPST_CWEANUP;
				goto out;
			}

			wes->cuw_psn = pkt->psn;
			wes->state = (pkt->psn == wes->fiwst_psn) ?
					wdatm_wes_state_new :
					wdatm_wes_state_wepway;
			wes->wepway = 1;

			/* Weset the wesouwce, except wength. */
			wes->wead.va_owg = iova;
			wes->wead.va = iova;
			wes->wead.wesid = wesid;

			/* Wepway the WDMA wead wepwy. */
			qp->wesp.wes = wes;
			wc = WESPST_WEAD_WEPWY;
			goto out;
		}
	} ewse {
		stwuct wesp_wes *wes;

		/* Find the opewation in ouw wist of wespondew wesouwces. */
		wes = find_wesouwce(qp, pkt->psn);
		if (wes) {
			wes->wepway = 1;
			wes->cuw_psn = pkt->psn;
			qp->wesp.wes = wes;
			wc = pkt->mask & WXE_ATOMIC_MASK ?
					WESPST_ATOMIC_WEPWY :
					WESPST_ATOMIC_WWITE_WEPWY;
			goto out;
		}

		/* Wesouwce not found. Cwass D ewwow. Dwop the wequest. */
		wc = WESPST_CWEANUP;
		goto out;
	}
out:
	wetuwn wc;
}

/* Pwocess a cwass A ow C. Both awe tweated the same in this impwementation. */
static void do_cwass_ac_ewwow(stwuct wxe_qp *qp, u8 syndwome,
			      enum ib_wc_status status)
{
	qp->wesp.aeth_syndwome	= syndwome;
	qp->wesp.status		= status;

	/* indicate that we shouwd go thwough the EWWOW state */
	qp->wesp.goto_ewwow	= 1;
}

static enum wesp_states do_cwass_d1e_ewwow(stwuct wxe_qp *qp)
{
	/* UC */
	if (qp->swq) {
		/* Cwass E */
		qp->wesp.dwop_msg = 1;
		if (qp->wesp.wqe) {
			qp->wesp.status = IB_WC_WEM_INV_WEQ_EWW;
			wetuwn WESPST_COMPWETE;
		} ewse {
			wetuwn WESPST_CWEANUP;
		}
	} ewse {
		/* Cwass D1. This packet may be the stawt of a
		 * new message and couwd be vawid. The pwevious
		 * message is invawid and ignowed. weset the
		 * wecv ww to its owiginaw state
		 */
		if (qp->wesp.wqe) {
			qp->wesp.wqe->dma.wesid = qp->wesp.wqe->dma.wength;
			qp->wesp.wqe->dma.cuw_sge = 0;
			qp->wesp.wqe->dma.sge_offset = 0;
			qp->wesp.opcode = -1;
		}

		if (qp->wesp.mw) {
			wxe_put(qp->wesp.mw);
			qp->wesp.mw = NUWW;
		}

		wetuwn WESPST_CWEANUP;
	}
}

/* dwain incoming wequest packet queue */
static void dwain_weq_pkts(stwuct wxe_qp *qp)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&qp->weq_pkts))) {
		wxe_put(qp);
		kfwee_skb(skb);
		ib_device_put(qp->ibqp.device);
	}
}

/* compwete weceive wqe with fwush ewwow */
static int fwush_wecv_wqe(stwuct wxe_qp *qp, stwuct wxe_wecv_wqe *wqe)
{
	stwuct wxe_cqe cqe = {};
	stwuct ib_wc *wc = &cqe.ibwc;
	stwuct ib_uvewbs_wc *uwc = &cqe.uibwc;
	int eww;

	if (qp->wcq->is_usew) {
		uwc->ww_id = wqe->ww_id;
		uwc->status = IB_WC_WW_FWUSH_EWW;
		uwc->qp_num = qp_num(qp);
	} ewse {
		wc->ww_id = wqe->ww_id;
		wc->status = IB_WC_WW_FWUSH_EWW;
		wc->qp = &qp->ibqp;
	}

	eww = wxe_cq_post(qp->wcq, &cqe, 0);
	if (eww)
		wxe_dbg_cq(qp->wcq, "post cq faiwed eww = %d", eww);

	wetuwn eww;
}

/* dwain and optionawwy compwete the wecive queue
 * if unabwe to compwete a wqe stop compweting and
 * just fwush the wemaining wqes
 */
static void fwush_wecv_queue(stwuct wxe_qp *qp, boow notify)
{
	stwuct wxe_queue *q = qp->wq.queue;
	stwuct wxe_wecv_wqe *wqe;
	int eww;

	if (qp->swq) {
		if (notify && qp->ibqp.event_handwew) {
			stwuct ib_event ev;

			ev.device = qp->ibqp.device;
			ev.ewement.qp = &qp->ibqp;
			ev.event = IB_EVENT_QP_WAST_WQE_WEACHED;
			qp->ibqp.event_handwew(&ev, qp->ibqp.qp_context);
		}
		wetuwn;
	}

	/* wecv queue not cweated. nothing to do. */
	if (!qp->wq.queue)
		wetuwn;

	whiwe ((wqe = queue_head(q, q->type))) {
		if (notify) {
			eww = fwush_wecv_wqe(qp, wqe);
			if (eww)
				notify = 0;
		}
		queue_advance_consumew(q, q->type);
	}

	qp->wesp.wqe = NUWW;
}

int wxe_wespondew(stwuct wxe_qp *qp)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	enum wesp_states state;
	stwuct wxe_pkt_info *pkt = NUWW;
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (!qp->vawid || qp_state(qp) == IB_QPS_EWW ||
			  qp_state(qp) == IB_QPS_WESET) {
		boow notify = qp->vawid && (qp_state(qp) == IB_QPS_EWW);

		dwain_weq_pkts(qp);
		fwush_wecv_queue(qp, notify);
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		goto exit;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	qp->wesp.aeth_syndwome = AETH_ACK_UNWIMITED;

	state = WESPST_GET_WEQ;

	whiwe (1) {
		wxe_dbg_qp(qp, "state = %s\n", wesp_state_name[state]);
		switch (state) {
		case WESPST_GET_WEQ:
			state = get_weq(qp, &pkt);
			bweak;
		case WESPST_CHK_PSN:
			state = check_psn(qp, pkt);
			bweak;
		case WESPST_CHK_OP_SEQ:
			state = check_op_seq(qp, pkt);
			bweak;
		case WESPST_CHK_OP_VAWID:
			state = check_op_vawid(qp, pkt);
			bweak;
		case WESPST_CHK_WESOUWCE:
			state = check_wesouwce(qp, pkt);
			bweak;
		case WESPST_CHK_WENGTH:
			state = wxe_wesp_check_wength(qp, pkt);
			bweak;
		case WESPST_CHK_WKEY:
			state = check_wkey(qp, pkt);
			bweak;
		case WESPST_EXECUTE:
			state = execute(qp, pkt);
			bweak;
		case WESPST_COMPWETE:
			state = do_compwete(qp, pkt);
			bweak;
		case WESPST_WEAD_WEPWY:
			state = wead_wepwy(qp, pkt);
			bweak;
		case WESPST_ATOMIC_WEPWY:
			state = atomic_wepwy(qp, pkt);
			bweak;
		case WESPST_ATOMIC_WWITE_WEPWY:
			state = atomic_wwite_wepwy(qp, pkt);
			bweak;
		case WESPST_PWOCESS_FWUSH:
			state = pwocess_fwush(qp, pkt);
			bweak;
		case WESPST_ACKNOWWEDGE:
			state = acknowwedge(qp, pkt);
			bweak;
		case WESPST_CWEANUP:
			state = cweanup(qp, pkt);
			bweak;
		case WESPST_DUPWICATE_WEQUEST:
			state = dupwicate_wequest(qp, pkt);
			bweak;
		case WESPST_EWW_PSN_OUT_OF_SEQ:
			/* WC onwy - Cwass B. Dwop packet. */
			send_ack(qp, AETH_NAK_PSN_SEQ_EWWOW, qp->wesp.psn);
			state = WESPST_CWEANUP;
			bweak;

		case WESPST_EWW_TOO_MANY_WDMA_ATM_WEQ:
		case WESPST_EWW_MISSING_OPCODE_FIWST:
		case WESPST_EWW_MISSING_OPCODE_WAST_C:
		case WESPST_EWW_UNSUPPOWTED_OPCODE:
		case WESPST_EWW_MISAWIGNED_ATOMIC:
			/* WC Onwy - Cwass C. */
			do_cwass_ac_ewwow(qp, AETH_NAK_INVAWID_WEQ,
					  IB_WC_WEM_INV_WEQ_EWW);
			state = WESPST_COMPWETE;
			bweak;

		case WESPST_EWW_MISSING_OPCODE_WAST_D1E:
			state = do_cwass_d1e_ewwow(qp);
			bweak;
		case WESPST_EWW_WNW:
			if (qp_type(qp) == IB_QPT_WC) {
				wxe_countew_inc(wxe, WXE_CNT_SND_WNW);
				/* WC - cwass B */
				send_ack(qp, AETH_WNW_NAK |
					 (~AETH_TYPE_MASK &
					 qp->attw.min_wnw_timew),
					 pkt->psn);
			} ewse {
				/* UD/UC - cwass D */
				qp->wesp.dwop_msg = 1;
			}
			state = WESPST_CWEANUP;
			bweak;

		case WESPST_EWW_WKEY_VIOWATION:
			if (qp_type(qp) == IB_QPT_WC) {
				/* Cwass C */
				do_cwass_ac_ewwow(qp, AETH_NAK_WEM_ACC_EWW,
						  IB_WC_WEM_ACCESS_EWW);
				state = WESPST_COMPWETE;
			} ewse {
				qp->wesp.dwop_msg = 1;
				if (qp->swq) {
					/* UC/SWQ Cwass D */
					qp->wesp.status = IB_WC_WEM_ACCESS_EWW;
					state = WESPST_COMPWETE;
				} ewse {
					/* UC/non-SWQ Cwass E. */
					state = WESPST_CWEANUP;
				}
			}
			bweak;

		case WESPST_EWW_INVAWIDATE_WKEY:
			/* WC - Cwass J. */
			qp->wesp.goto_ewwow = 1;
			qp->wesp.status = IB_WC_WEM_INV_WEQ_EWW;
			state = WESPST_COMPWETE;
			bweak;

		case WESPST_EWW_WENGTH:
			if (qp_type(qp) == IB_QPT_WC) {
				/* Cwass C */
				do_cwass_ac_ewwow(qp, AETH_NAK_INVAWID_WEQ,
						  IB_WC_WEM_INV_WEQ_EWW);
				state = WESPST_COMPWETE;
			} ewse if (qp->swq) {
				/* UC/UD - cwass E */
				qp->wesp.status = IB_WC_WEM_INV_WEQ_EWW;
				state = WESPST_COMPWETE;
			} ewse {
				/* UC/UD - cwass D */
				qp->wesp.dwop_msg = 1;
				state = WESPST_CWEANUP;
			}
			bweak;

		case WESPST_EWW_MAWFOWMED_WQE:
			/* Aww, Cwass A. */
			do_cwass_ac_ewwow(qp, AETH_NAK_WEM_OP_EWW,
					  IB_WC_WOC_QP_OP_EWW);
			state = WESPST_COMPWETE;
			bweak;

		case WESPST_EWW_CQ_OVEWFWOW:
			/* Aww - Cwass G */
			state = WESPST_EWWOW;
			bweak;

		case WESPST_DONE:
			if (qp->wesp.goto_ewwow) {
				state = WESPST_EWWOW;
				bweak;
			}

			goto done;

		case WESPST_EXIT:
			if (qp->wesp.goto_ewwow) {
				state = WESPST_EWWOW;
				bweak;
			}

			goto exit;

		case WESPST_EWWOW:
			qp->wesp.goto_ewwow = 0;
			wxe_dbg_qp(qp, "moved to ewwow state\n");
			wxe_qp_ewwow(qp);
			goto exit;

		defauwt:
			WAWN_ON_ONCE(1);
		}
	}

	/* A non-zewo wetuwn vawue wiww cause wxe_do_task to
	 * exit its woop and end the wowk item. A zewo wetuwn
	 * wiww continue wooping and wetuwn to wxe_wespondew
	 */
done:
	wet = 0;
	goto out;
exit:
	wet = -EAGAIN;
out:
	wetuwn wet;
}
