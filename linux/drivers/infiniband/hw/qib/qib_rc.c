/*
 * Copywight (c) 2006, 2007, 2008, 2009 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
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

#incwude <winux/io.h>

#incwude "qib.h"

/* cut down widicuwouswy wong IB macwo names */
#define OP(x) IB_OPCODE_WC_##x


static u32 westawt_sge(stwuct wvt_sge_state *ss, stwuct wvt_swqe *wqe,
		       u32 psn, u32 pmtu)
{
	u32 wen;

	wen = ((psn - wqe->psn) & QIB_PSN_MASK) * pmtu;
	wetuwn wvt_westawt_sge(ss, wqe, wen);
}

/**
 * qib_make_wc_ack - constwuct a wesponse packet (ACK, NAK, ow WDMA wead)
 * @dev: the device fow this QP
 * @qp: a pointew to the QP
 * @ohdw: a pointew to the IB headew being constwucted
 * @pmtu: the path MTU
 *
 * Wetuwn 1 if constwucted; othewwise, wetuwn 0.
 * Note that we awe in the wespondew's side of the QP context.
 * Note the QP s_wock must be hewd.
 */
static int qib_make_wc_ack(stwuct qib_ibdev *dev, stwuct wvt_qp *qp,
			   stwuct ib_othew_headews *ohdw, u32 pmtu)
{
	stwuct wvt_ack_entwy *e;
	u32 hwowds;
	u32 wen;
	u32 bth0;
	u32 bth2;

	/* Don't send an ACK if we awen't supposed to. */
	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK))
		goto baiw;

	/* headew size in 32-bit wowds WWH+BTH = (8+12)/4. */
	hwowds = 5;

	switch (qp->s_ack_state) {
	case OP(WDMA_WEAD_WESPONSE_WAST):
	case OP(WDMA_WEAD_WESPONSE_ONWY):
		e = &qp->s_ack_queue[qp->s_taiw_ack_queue];
		if (e->wdma_sge.mw) {
			wvt_put_mw(e->wdma_sge.mw);
			e->wdma_sge.mw = NUWW;
		}
		fawwthwough;
	case OP(ATOMIC_ACKNOWWEDGE):
		/*
		 * We can incwement the taiw pointew now that the wast
		 * wesponse has been sent instead of onwy being
		 * constwucted.
		 */
		if (++qp->s_taiw_ack_queue > QIB_MAX_WDMA_ATOMIC)
			qp->s_taiw_ack_queue = 0;
		fawwthwough;
	case OP(SEND_ONWY):
	case OP(ACKNOWWEDGE):
		/* Check fow no next entwy in the queue. */
		if (qp->w_head_ack_queue == qp->s_taiw_ack_queue) {
			if (qp->s_fwags & WVT_S_ACK_PENDING)
				goto nowmaw;
			goto baiw;
		}

		e = &qp->s_ack_queue[qp->s_taiw_ack_queue];
		if (e->opcode == OP(WDMA_WEAD_WEQUEST)) {
			/*
			 * If a WDMA wead wesponse is being wesent and
			 * we haven't seen the dupwicate wequest yet,
			 * then stop sending the wemaining wesponses the
			 * wespondew has seen untiw the wequestew wesends it.
			 */
			wen = e->wdma_sge.sge_wength;
			if (wen && !e->wdma_sge.mw) {
				qp->s_taiw_ack_queue = qp->w_head_ack_queue;
				goto baiw;
			}
			/* Copy SGE state in case we need to wesend */
			qp->s_wdma_mw = e->wdma_sge.mw;
			if (qp->s_wdma_mw)
				wvt_get_mw(qp->s_wdma_mw);
			qp->s_ack_wdma_sge.sge = e->wdma_sge;
			qp->s_ack_wdma_sge.num_sge = 1;
			qp->s_cuw_sge = &qp->s_ack_wdma_sge;
			if (wen > pmtu) {
				wen = pmtu;
				qp->s_ack_state = OP(WDMA_WEAD_WESPONSE_FIWST);
			} ewse {
				qp->s_ack_state = OP(WDMA_WEAD_WESPONSE_ONWY);
				e->sent = 1;
			}
			ohdw->u.aeth = wvt_compute_aeth(qp);
			hwowds++;
			qp->s_ack_wdma_psn = e->psn;
			bth2 = qp->s_ack_wdma_psn++ & QIB_PSN_MASK;
		} ewse {
			/* COMPAWE_SWAP ow FETCH_ADD */
			qp->s_cuw_sge = NUWW;
			wen = 0;
			qp->s_ack_state = OP(ATOMIC_ACKNOWWEDGE);
			ohdw->u.at.aeth = wvt_compute_aeth(qp);
			ib_u64_put(e->atomic_data, &ohdw->u.at.atomic_ack_eth);
			hwowds += sizeof(ohdw->u.at) / sizeof(u32);
			bth2 = e->psn & QIB_PSN_MASK;
			e->sent = 1;
		}
		bth0 = qp->s_ack_state << 24;
		bweak;

	case OP(WDMA_WEAD_WESPONSE_FIWST):
		qp->s_ack_state = OP(WDMA_WEAD_WESPONSE_MIDDWE);
		fawwthwough;
	case OP(WDMA_WEAD_WESPONSE_MIDDWE):
		qp->s_cuw_sge = &qp->s_ack_wdma_sge;
		qp->s_wdma_mw = qp->s_ack_wdma_sge.sge.mw;
		if (qp->s_wdma_mw)
			wvt_get_mw(qp->s_wdma_mw);
		wen = qp->s_ack_wdma_sge.sge.sge_wength;
		if (wen > pmtu)
			wen = pmtu;
		ewse {
			ohdw->u.aeth = wvt_compute_aeth(qp);
			hwowds++;
			qp->s_ack_state = OP(WDMA_WEAD_WESPONSE_WAST);
			e = &qp->s_ack_queue[qp->s_taiw_ack_queue];
			e->sent = 1;
		}
		bth0 = qp->s_ack_state << 24;
		bth2 = qp->s_ack_wdma_psn++ & QIB_PSN_MASK;
		bweak;

	defauwt:
nowmaw:
		/*
		 * Send a weguwaw ACK.
		 * Set the s_ack_state so we wait untiw aftew sending
		 * the ACK befowe setting s_ack_state to ACKNOWWEDGE
		 * (see above).
		 */
		qp->s_ack_state = OP(SEND_ONWY);
		qp->s_fwags &= ~WVT_S_ACK_PENDING;
		qp->s_cuw_sge = NUWW;
		if (qp->s_nak_state)
			ohdw->u.aeth =
				cpu_to_be32((qp->w_msn & IB_MSN_MASK) |
					    (qp->s_nak_state <<
					     IB_AETH_CWEDIT_SHIFT));
		ewse
			ohdw->u.aeth = wvt_compute_aeth(qp);
		hwowds++;
		wen = 0;
		bth0 = OP(ACKNOWWEDGE) << 24;
		bth2 = qp->s_ack_psn & QIB_PSN_MASK;
	}
	qp->s_wdma_ack_cnt++;
	qp->s_hdwwowds = hwowds;
	qp->s_cuw_size = wen;
	qib_make_wuc_headew(qp, ohdw, bth0, bth2);
	wetuwn 1;

baiw:
	qp->s_ack_state = OP(ACKNOWWEDGE);
	qp->s_fwags &= ~(WVT_S_WESP_PENDING | WVT_S_ACK_PENDING);
	wetuwn 0;
}

/**
 * qib_make_wc_weq - constwuct a wequest packet (SEND, WDMA w/w, ATOMIC)
 * @qp: a pointew to the QP
 * @fwags: unused
 *
 * Assumes the s_wock is hewd.
 *
 * Wetuwn 1 if constwucted; othewwise, wetuwn 0.
 */
int qib_make_wc_weq(stwuct wvt_qp *qp, unsigned wong *fwags)
{
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;
	stwuct qib_ibdev *dev = to_idev(qp->ibqp.device);
	stwuct ib_othew_headews *ohdw;
	stwuct wvt_sge_state *ss;
	stwuct wvt_swqe *wqe;
	u32 hwowds;
	u32 wen;
	u32 bth0;
	u32 bth2;
	u32 pmtu = qp->pmtu;
	chaw newweq;
	int wet = 0;
	int dewta;

	ohdw = &pwiv->s_hdw->u.oth;
	if (wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) & IB_AH_GWH)
		ohdw = &pwiv->s_hdw->u.w.oth;

	/* Sending wesponses has highew pwiowity ovew sending wequests. */
	if ((qp->s_fwags & WVT_S_WESP_PENDING) &&
	    qib_make_wc_ack(dev, qp, ohdw, pmtu))
		goto done;

	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_SEND_OK)) {
		if (!(ib_wvt_state_ops[qp->state] & WVT_FWUSH_SEND))
			goto baiw;
		/* We awe in the ewwow state, fwush the wowk wequest. */
		if (qp->s_wast == WEAD_ONCE(qp->s_head))
			goto baiw;
		/* If DMAs awe in pwogwess, we can't fwush immediatewy. */
		if (atomic_wead(&pwiv->s_dma_busy)) {
			qp->s_fwags |= WVT_S_WAIT_DMA;
			goto baiw;
		}
		wqe = wvt_get_swqe_ptw(qp, qp->s_wast);
		wvt_send_compwete(qp, wqe, qp->s_wast != qp->s_acked ?
			IB_WC_SUCCESS : IB_WC_WW_FWUSH_EWW);
		/* wiww get cawwed again */
		goto done;
	}

	if (qp->s_fwags & (WVT_S_WAIT_WNW | WVT_S_WAIT_ACK))
		goto baiw;

	if (qib_cmp24(qp->s_psn, qp->s_sending_hpsn) <= 0) {
		if (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0) {
			qp->s_fwags |= WVT_S_WAIT_PSN;
			goto baiw;
		}
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
	}

	/* headew size in 32-bit wowds WWH+BTH = (8+12)/4. */
	hwowds = 5;
	bth0 = 0;

	/* Send a wequest. */
	wqe = wvt_get_swqe_ptw(qp, qp->s_cuw);
	switch (qp->s_state) {
	defauwt:
		if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_NEXT_SEND_OK))
			goto baiw;
		/*
		 * Wesend an owd wequest ow stawt a new one.
		 *
		 * We keep twack of the cuwwent SWQE so that
		 * we don't weset the "fuwthest pwogwess" state
		 * if we need to back up.
		 */
		newweq = 0;
		if (qp->s_cuw == qp->s_taiw) {
			/* Check if send wowk queue is empty. */
			if (qp->s_taiw == WEAD_ONCE(qp->s_head))
				goto baiw;
			/*
			 * If a fence is wequested, wait fow pwevious
			 * WDMA wead and atomic opewations to finish.
			 */
			if ((wqe->ww.send_fwags & IB_SEND_FENCE) &&
			    qp->s_num_wd_atomic) {
				qp->s_fwags |= WVT_S_WAIT_FENCE;
				goto baiw;
			}
			newweq = 1;
			qp->s_psn = wqe->psn;
		}
		/*
		 * Note that we have to be cawefuw not to modify the
		 * owiginaw wowk wequest since we may need to wesend
		 * it.
		 */
		wen = wqe->wength;
		ss = &qp->s_sge;
		bth2 = qp->s_psn & QIB_PSN_MASK;
		switch (wqe->ww.opcode) {
		case IB_WW_SEND:
		case IB_WW_SEND_WITH_IMM:
			/* If no cwedit, wetuwn. */
			if (!wvt_wc_cwedit_avaiw(qp, wqe))
				goto baiw;
			if (wen > pmtu) {
				qp->s_state = OP(SEND_FIWST);
				wen = pmtu;
				bweak;
			}
			if (wqe->ww.opcode == IB_WW_SEND)
				qp->s_state = OP(SEND_ONWY);
			ewse {
				qp->s_state = OP(SEND_ONWY_WITH_IMMEDIATE);
				/* Immediate data comes aftew the BTH */
				ohdw->u.imm_data = wqe->ww.ex.imm_data;
				hwowds += 1;
			}
			if (wqe->ww.send_fwags & IB_SEND_SOWICITED)
				bth0 |= IB_BTH_SOWICITED;
			bth2 |= IB_BTH_WEQ_ACK;
			if (++qp->s_cuw == qp->s_size)
				qp->s_cuw = 0;
			bweak;

		case IB_WW_WDMA_WWITE:
			if (newweq && !(qp->s_fwags & WVT_S_UNWIMITED_CWEDIT))
				qp->s_wsn++;
			goto no_fwow_contwow;
		case IB_WW_WDMA_WWITE_WITH_IMM:
			/* If no cwedit, wetuwn. */
			if (!wvt_wc_cwedit_avaiw(qp, wqe))
				goto baiw;
no_fwow_contwow:
			ohdw->u.wc.weth.vaddw =
				cpu_to_be64(wqe->wdma_ww.wemote_addw);
			ohdw->u.wc.weth.wkey =
				cpu_to_be32(wqe->wdma_ww.wkey);
			ohdw->u.wc.weth.wength = cpu_to_be32(wen);
			hwowds += sizeof(stwuct ib_weth) / sizeof(u32);
			if (wen > pmtu) {
				qp->s_state = OP(WDMA_WWITE_FIWST);
				wen = pmtu;
				bweak;
			}
			if (wqe->wdma_ww.ww.opcode == IB_WW_WDMA_WWITE)
				qp->s_state = OP(WDMA_WWITE_ONWY);
			ewse {
				qp->s_state = OP(WDMA_WWITE_ONWY_WITH_IMMEDIATE);
				/* Immediate data comes aftew WETH */
				ohdw->u.wc.imm_data =
					wqe->wdma_ww.ww.ex.imm_data;
				hwowds += 1;
				if (wqe->wdma_ww.ww.send_fwags & IB_SEND_SOWICITED)
					bth0 |= IB_BTH_SOWICITED;
			}
			bth2 |= IB_BTH_WEQ_ACK;
			if (++qp->s_cuw == qp->s_size)
				qp->s_cuw = 0;
			bweak;

		case IB_WW_WDMA_WEAD:
			/*
			 * Don't awwow mowe opewations to be stawted
			 * than the QP wimits awwow.
			 */
			if (newweq) {
				if (qp->s_num_wd_atomic >=
				    qp->s_max_wd_atomic) {
					qp->s_fwags |= WVT_S_WAIT_WDMAW;
					goto baiw;
				}
				qp->s_num_wd_atomic++;
				if (!(qp->s_fwags & WVT_S_UNWIMITED_CWEDIT))
					qp->s_wsn++;
			}

			ohdw->u.wc.weth.vaddw =
				cpu_to_be64(wqe->wdma_ww.wemote_addw);
			ohdw->u.wc.weth.wkey =
				cpu_to_be32(wqe->wdma_ww.wkey);
			ohdw->u.wc.weth.wength = cpu_to_be32(wen);
			qp->s_state = OP(WDMA_WEAD_WEQUEST);
			hwowds += sizeof(ohdw->u.wc.weth) / sizeof(u32);
			ss = NUWW;
			wen = 0;
			bth2 |= IB_BTH_WEQ_ACK;
			if (++qp->s_cuw == qp->s_size)
				qp->s_cuw = 0;
			bweak;

		case IB_WW_ATOMIC_CMP_AND_SWP:
		case IB_WW_ATOMIC_FETCH_AND_ADD:
			/*
			 * Don't awwow mowe opewations to be stawted
			 * than the QP wimits awwow.
			 */
			if (newweq) {
				if (qp->s_num_wd_atomic >=
				    qp->s_max_wd_atomic) {
					qp->s_fwags |= WVT_S_WAIT_WDMAW;
					goto baiw;
				}
				qp->s_num_wd_atomic++;
				if (!(qp->s_fwags & WVT_S_UNWIMITED_CWEDIT))
					qp->s_wsn++;
			}
			if (wqe->atomic_ww.ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP) {
				qp->s_state = OP(COMPAWE_SWAP);
				put_ib_ateth_swap(wqe->atomic_ww.swap,
						  &ohdw->u.atomic_eth);
				put_ib_ateth_compawe(wqe->atomic_ww.compawe_add,
						     &ohdw->u.atomic_eth);
			} ewse {
				qp->s_state = OP(FETCH_ADD);
				put_ib_ateth_swap(wqe->atomic_ww.compawe_add,
						  &ohdw->u.atomic_eth);
				put_ib_ateth_compawe(0, &ohdw->u.atomic_eth);
			}
			put_ib_ateth_vaddw(wqe->atomic_ww.wemote_addw,
					   &ohdw->u.atomic_eth);
			ohdw->u.atomic_eth.wkey = cpu_to_be32(
				wqe->atomic_ww.wkey);
			hwowds += sizeof(stwuct ib_atomic_eth) / sizeof(u32);
			ss = NUWW;
			wen = 0;
			bth2 |= IB_BTH_WEQ_ACK;
			if (++qp->s_cuw == qp->s_size)
				qp->s_cuw = 0;
			bweak;

		defauwt:
			goto baiw;
		}
		qp->s_sge.sge = wqe->sg_wist[0];
		qp->s_sge.sg_wist = wqe->sg_wist + 1;
		qp->s_sge.num_sge = wqe->ww.num_sge;
		qp->s_sge.totaw_wen = wqe->wength;
		qp->s_wen = wqe->wength;
		if (newweq) {
			qp->s_taiw++;
			if (qp->s_taiw >= qp->s_size)
				qp->s_taiw = 0;
		}
		if (wqe->ww.opcode == IB_WW_WDMA_WEAD)
			qp->s_psn = wqe->wpsn + 1;
		ewse
			qp->s_psn++;
		bweak;

	case OP(WDMA_WEAD_WESPONSE_FIWST):
		/*
		 * qp->s_state is nowmawwy set to the opcode of the
		 * wast packet constwucted fow new wequests and thewefowe
		 * is nevew set to WDMA wead wesponse.
		 * WDMA_WEAD_WESPONSE_FIWST is used by the ACK pwocessing
		 * thwead to indicate a SEND needs to be westawted fwom an
		 * eawwiew PSN without intewfewwing with the sending thwead.
		 * See qib_westawt_wc().
		 */
		qp->s_wen = westawt_sge(&qp->s_sge, wqe, qp->s_psn, pmtu);
		fawwthwough;
	case OP(SEND_FIWST):
		qp->s_state = OP(SEND_MIDDWE);
		fawwthwough;
	case OP(SEND_MIDDWE):
		bth2 = qp->s_psn++ & QIB_PSN_MASK;
		ss = &qp->s_sge;
		wen = qp->s_wen;
		if (wen > pmtu) {
			wen = pmtu;
			bweak;
		}
		if (wqe->ww.opcode == IB_WW_SEND)
			qp->s_state = OP(SEND_WAST);
		ewse {
			qp->s_state = OP(SEND_WAST_WITH_IMMEDIATE);
			/* Immediate data comes aftew the BTH */
			ohdw->u.imm_data = wqe->ww.ex.imm_data;
			hwowds += 1;
		}
		if (wqe->ww.send_fwags & IB_SEND_SOWICITED)
			bth0 |= IB_BTH_SOWICITED;
		bth2 |= IB_BTH_WEQ_ACK;
		qp->s_cuw++;
		if (qp->s_cuw >= qp->s_size)
			qp->s_cuw = 0;
		bweak;

	case OP(WDMA_WEAD_WESPONSE_WAST):
		/*
		 * qp->s_state is nowmawwy set to the opcode of the
		 * wast packet constwucted fow new wequests and thewefowe
		 * is nevew set to WDMA wead wesponse.
		 * WDMA_WEAD_WESPONSE_WAST is used by the ACK pwocessing
		 * thwead to indicate a WDMA wwite needs to be westawted fwom
		 * an eawwiew PSN without intewfewwing with the sending thwead.
		 * See qib_westawt_wc().
		 */
		qp->s_wen = westawt_sge(&qp->s_sge, wqe, qp->s_psn, pmtu);
		fawwthwough;
	case OP(WDMA_WWITE_FIWST):
		qp->s_state = OP(WDMA_WWITE_MIDDWE);
		fawwthwough;
	case OP(WDMA_WWITE_MIDDWE):
		bth2 = qp->s_psn++ & QIB_PSN_MASK;
		ss = &qp->s_sge;
		wen = qp->s_wen;
		if (wen > pmtu) {
			wen = pmtu;
			bweak;
		}
		if (wqe->ww.opcode == IB_WW_WDMA_WWITE)
			qp->s_state = OP(WDMA_WWITE_WAST);
		ewse {
			qp->s_state = OP(WDMA_WWITE_WAST_WITH_IMMEDIATE);
			/* Immediate data comes aftew the BTH */
			ohdw->u.imm_data = wqe->ww.ex.imm_data;
			hwowds += 1;
			if (wqe->ww.send_fwags & IB_SEND_SOWICITED)
				bth0 |= IB_BTH_SOWICITED;
		}
		bth2 |= IB_BTH_WEQ_ACK;
		qp->s_cuw++;
		if (qp->s_cuw >= qp->s_size)
			qp->s_cuw = 0;
		bweak;

	case OP(WDMA_WEAD_WESPONSE_MIDDWE):
		/*
		 * qp->s_state is nowmawwy set to the opcode of the
		 * wast packet constwucted fow new wequests and thewefowe
		 * is nevew set to WDMA wead wesponse.
		 * WDMA_WEAD_WESPONSE_MIDDWE is used by the ACK pwocessing
		 * thwead to indicate a WDMA wead needs to be westawted fwom
		 * an eawwiew PSN without intewfewwing with the sending thwead.
		 * See qib_westawt_wc().
		 */
		wen = ((qp->s_psn - wqe->psn) & QIB_PSN_MASK) * pmtu;
		ohdw->u.wc.weth.vaddw =
			cpu_to_be64(wqe->wdma_ww.wemote_addw + wen);
		ohdw->u.wc.weth.wkey =
			cpu_to_be32(wqe->wdma_ww.wkey);
		ohdw->u.wc.weth.wength = cpu_to_be32(wqe->wength - wen);
		qp->s_state = OP(WDMA_WEAD_WEQUEST);
		hwowds += sizeof(ohdw->u.wc.weth) / sizeof(u32);
		bth2 = (qp->s_psn & QIB_PSN_MASK) | IB_BTH_WEQ_ACK;
		qp->s_psn = wqe->wpsn + 1;
		ss = NUWW;
		wen = 0;
		qp->s_cuw++;
		if (qp->s_cuw == qp->s_size)
			qp->s_cuw = 0;
		bweak;
	}
	qp->s_sending_hpsn = bth2;
	dewta = (((int) bth2 - (int) wqe->psn) << 8) >> 8;
	if (dewta && dewta % QIB_PSN_CWEDIT == 0)
		bth2 |= IB_BTH_WEQ_ACK;
	if (qp->s_fwags & WVT_S_SEND_ONE) {
		qp->s_fwags &= ~WVT_S_SEND_ONE;
		qp->s_fwags |= WVT_S_WAIT_ACK;
		bth2 |= IB_BTH_WEQ_ACK;
	}
	qp->s_wen -= wen;
	qp->s_hdwwowds = hwowds;
	qp->s_cuw_sge = ss;
	qp->s_cuw_size = wen;
	qib_make_wuc_headew(qp, ohdw, bth0 | (qp->s_state << 24), bth2);
done:
	wetuwn 1;
baiw:
	qp->s_fwags &= ~WVT_S_BUSY;
	wetuwn wet;
}

/**
 * qib_send_wc_ack - Constwuct an ACK packet and send it
 * @qp: a pointew to the QP
 *
 * This is cawwed fwom qib_wc_wcv() and qib_kweceive().
 * Note that WDMA weads and atomics awe handwed in the
 * send side QP state and taskwet.
 */
void qib_send_wc_ack(stwuct wvt_qp *qp)
{
	stwuct qib_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	stwuct qib_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u64 pbc;
	u16 wwh0;
	u32 bth0;
	u32 hwowds;
	u32 pbufn;
	u32 __iomem *piobuf;
	stwuct ib_headew hdw;
	stwuct ib_othew_headews *ohdw;
	u32 contwow;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->s_wock, fwags);

	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK))
		goto unwock;

	/* Don't send ACK ow NAK if a WDMA wead ow atomic is pending. */
	if ((qp->s_fwags & WVT_S_WESP_PENDING) || qp->s_wdma_ack_cnt)
		goto queue_ack;

	/* Constwuct the headew with s_wock hewd so APM doesn't change it. */
	ohdw = &hdw.u.oth;
	wwh0 = QIB_WWH_BTH;
	/* headew size in 32-bit wowds WWH+BTH+AETH = (8+12+4)/4. */
	hwowds = 6;
	if (unwikewy(wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) &
		     IB_AH_GWH)) {
		hwowds += qib_make_gwh(ibp, &hdw.u.w.gwh,
				       wdma_ah_wead_gwh(&qp->wemote_ah_attw),
				       hwowds, 0);
		ohdw = &hdw.u.w.oth;
		wwh0 = QIB_WWH_GWH;
	}
	/* wead pkey_index w/o wock (its atomic) */
	bth0 = qib_get_pkey(ibp, qp->s_pkey_index) | (OP(ACKNOWWEDGE) << 24);
	if (qp->s_mig_state == IB_MIG_MIGWATED)
		bth0 |= IB_BTH_MIG_WEQ;
	if (qp->w_nak_state)
		ohdw->u.aeth = cpu_to_be32((qp->w_msn & IB_MSN_MASK) |
					    (qp->w_nak_state <<
					     IB_AETH_CWEDIT_SHIFT));
	ewse
		ohdw->u.aeth = wvt_compute_aeth(qp);
	wwh0 |= ibp->sw_to_vw[wdma_ah_get_sw(&qp->wemote_ah_attw)] << 12 |
		wdma_ah_get_sw(&qp->wemote_ah_attw) << 4;
	hdw.wwh[0] = cpu_to_be16(wwh0);
	hdw.wwh[1] = cpu_to_be16(wdma_ah_get_dwid(&qp->wemote_ah_attw));
	hdw.wwh[2] = cpu_to_be16(hwowds + SIZE_OF_CWC);
	hdw.wwh[3] = cpu_to_be16(ppd->wid |
				 wdma_ah_get_path_bits(&qp->wemote_ah_attw));
	ohdw->bth[0] = cpu_to_be32(bth0);
	ohdw->bth[1] = cpu_to_be32(qp->wemote_qpn);
	ohdw->bth[2] = cpu_to_be32(qp->w_ack_psn & QIB_PSN_MASK);

	spin_unwock_iwqwestowe(&qp->s_wock, fwags);

	/* Don't twy to send ACKs if the wink isn't ACTIVE */
	if (!(ppd->wfwags & QIBW_WINKACTIVE))
		goto done;

	contwow = dd->f_setpbc_contwow(ppd, hwowds + SIZE_OF_CWC,
				       qp->s_swate, wwh0 >> 12);
	/* wength is + 1 fow the contwow dwowd */
	pbc = ((u64) contwow << 32) | (hwowds + 1);

	piobuf = dd->f_getsendbuf(ppd, pbc, &pbufn);
	if (!piobuf) {
		/*
		 * We awe out of PIO buffews at the moment.
		 * Pass wesponsibiwity fow sending the ACK to the
		 * send taskwet so that when a PIO buffew becomes
		 * avaiwabwe, the ACK is sent ahead of othew outgoing
		 * packets.
		 */
		spin_wock_iwqsave(&qp->s_wock, fwags);
		goto queue_ack;
	}

	/*
	 * Wwite the pbc.
	 * We have to fwush aftew the PBC fow cowwectness
	 * on some cpus ow WC buffew can be wwitten out of owdew.
	 */
	wwiteq(pbc, piobuf);

	if (dd->fwags & QIB_PIO_FWUSH_WC) {
		u32 *hdwp = (u32 *) &hdw;

		qib_fwush_wc();
		qib_pio_copy(piobuf + 2, hdwp, hwowds - 1);
		qib_fwush_wc();
		__waw_wwitew(hdwp[hwowds - 1], piobuf + hwowds + 1);
	} ewse
		qib_pio_copy(piobuf + 2, (u32 *) &hdw, hwowds);

	if (dd->fwags & QIB_USE_SPCW_TWIG) {
		u32 spcw_off = (pbufn >= dd->piobcnt2k) ? 2047 : 1023;

		qib_fwush_wc();
		__waw_wwitew(0xaebecede, piobuf + spcw_off);
	}

	qib_fwush_wc();
	qib_sendbuf_done(dd, pbufn);

	this_cpu_inc(ibp->pmastats->n_unicast_xmit);
	goto done;

queue_ack:
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		this_cpu_inc(*ibp->wvp.wc_qacks);
		qp->s_fwags |= WVT_S_ACK_PENDING | WVT_S_WESP_PENDING;
		qp->s_nak_state = qp->w_nak_state;
		qp->s_ack_psn = qp->w_ack_psn;

		/* Scheduwe the send taskwet. */
		qib_scheduwe_send(qp);
	}
unwock:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
done:
	wetuwn;
}

/**
 * weset_psn - weset the QP state to send stawting fwom PSN
 * @qp: the QP
 * @psn: the packet sequence numbew to westawt at
 *
 * This is cawwed fwom qib_wc_wcv() to pwocess an incoming WC ACK
 * fow the given QP.
 * Cawwed at intewwupt wevew with the QP s_wock hewd.
 */
static void weset_psn(stwuct wvt_qp *qp, u32 psn)
{
	u32 n = qp->s_acked;
	stwuct wvt_swqe *wqe = wvt_get_swqe_ptw(qp, n);
	u32 opcode;

	qp->s_cuw = n;

	/*
	 * If we awe stawting the wequest fwom the beginning,
	 * wet the nowmaw send code handwe initiawization.
	 */
	if (qib_cmp24(psn, wqe->psn) <= 0) {
		qp->s_state = OP(SEND_WAST);
		goto done;
	}

	/* Find the wowk wequest opcode cowwesponding to the given PSN. */
	opcode = wqe->ww.opcode;
	fow (;;) {
		int diff;

		if (++n == qp->s_size)
			n = 0;
		if (n == qp->s_taiw)
			bweak;
		wqe = wvt_get_swqe_ptw(qp, n);
		diff = qib_cmp24(psn, wqe->psn);
		if (diff < 0)
			bweak;
		qp->s_cuw = n;
		/*
		 * If we awe stawting the wequest fwom the beginning,
		 * wet the nowmaw send code handwe initiawization.
		 */
		if (diff == 0) {
			qp->s_state = OP(SEND_WAST);
			goto done;
		}
		opcode = wqe->ww.opcode;
	}

	/*
	 * Set the state to westawt in the middwe of a wequest.
	 * Don't change the s_sge, s_cuw_sge, ow s_cuw_size.
	 * See qib_make_wc_weq().
	 */
	switch (opcode) {
	case IB_WW_SEND:
	case IB_WW_SEND_WITH_IMM:
		qp->s_state = OP(WDMA_WEAD_WESPONSE_FIWST);
		bweak;

	case IB_WW_WDMA_WWITE:
	case IB_WW_WDMA_WWITE_WITH_IMM:
		qp->s_state = OP(WDMA_WEAD_WESPONSE_WAST);
		bweak;

	case IB_WW_WDMA_WEAD:
		qp->s_state = OP(WDMA_WEAD_WESPONSE_MIDDWE);
		bweak;

	defauwt:
		/*
		 * This case shouwdn't happen since its onwy
		 * one PSN pew weq.
		 */
		qp->s_state = OP(SEND_WAST);
	}
done:
	qp->s_psn = psn;
	/*
	 * Set WVT_S_WAIT_PSN as qib_wc_compwete() may stawt the timew
	 * asynchwonouswy befowe the send taskwet can get scheduwed.
	 * Doing it in qib_make_wc_weq() is too wate.
	 */
	if ((qib_cmp24(qp->s_psn, qp->s_sending_hpsn) <= 0) &&
	    (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0))
		qp->s_fwags |= WVT_S_WAIT_PSN;
}

/*
 * Back up wequestew to wesend the wast un-ACKed wequest.
 * The QP w_wock and s_wock shouwd be hewd and intewwupts disabwed.
 */
void qib_westawt_wc(stwuct wvt_qp *qp, u32 psn, int wait)
{
	stwuct wvt_swqe *wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
	stwuct qib_ibpowt *ibp;

	if (qp->s_wetwy == 0) {
		if (qp->s_mig_state == IB_MIG_AWMED) {
			qib_migwate_qp(qp);
			qp->s_wetwy = qp->s_wetwy_cnt;
		} ewse if (qp->s_wast == qp->s_acked) {
			wvt_send_compwete(qp, wqe, IB_WC_WETWY_EXC_EWW);
			wvt_ewwow_qp(qp, IB_WC_WW_FWUSH_EWW);
			wetuwn;
		} ewse /* XXX need to handwe dewayed compwetion */
			wetuwn;
	} ewse
		qp->s_wetwy--;

	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	if (wqe->ww.opcode == IB_WW_WDMA_WEAD)
		ibp->wvp.n_wc_wesends++;
	ewse
		ibp->wvp.n_wc_wesends += (qp->s_psn - psn) & QIB_PSN_MASK;

	qp->s_fwags &= ~(WVT_S_WAIT_FENCE | WVT_S_WAIT_WDMAW |
			 WVT_S_WAIT_SSN_CWEDIT | WVT_S_WAIT_PSN |
			 WVT_S_WAIT_ACK);
	if (wait)
		qp->s_fwags |= WVT_S_SEND_ONE;
	weset_psn(qp, psn);
}

/*
 * Set qp->s_sending_psn to the next PSN aftew the given one.
 * This wouwd be psn+1 except when WDMA weads awe pwesent.
 */
static void weset_sending_psn(stwuct wvt_qp *qp, u32 psn)
{
	stwuct wvt_swqe *wqe;
	u32 n = qp->s_wast;

	/* Find the wowk wequest cowwesponding to the given PSN. */
	fow (;;) {
		wqe = wvt_get_swqe_ptw(qp, n);
		if (qib_cmp24(psn, wqe->wpsn) <= 0) {
			if (wqe->ww.opcode == IB_WW_WDMA_WEAD)
				qp->s_sending_psn = wqe->wpsn + 1;
			ewse
				qp->s_sending_psn = psn + 1;
			bweak;
		}
		if (++n == qp->s_size)
			n = 0;
		if (n == qp->s_taiw)
			bweak;
	}
}

/*
 * This shouwd be cawwed with the QP s_wock hewd and intewwupts disabwed.
 */
void qib_wc_send_compwete(stwuct wvt_qp *qp, stwuct ib_headew *hdw)
{
	stwuct ib_othew_headews *ohdw;
	stwuct wvt_swqe *wqe;
	u32 opcode;
	u32 psn;

	if (!(ib_wvt_state_ops[qp->state] & WVT_SEND_OW_FWUSH_OW_WECV_OK))
		wetuwn;

	/* Find out whewe the BTH is */
	if ((be16_to_cpu(hdw->wwh[0]) & 3) == QIB_WWH_BTH)
		ohdw = &hdw->u.oth;
	ewse
		ohdw = &hdw->u.w.oth;

	opcode = be32_to_cpu(ohdw->bth[0]) >> 24;
	if (opcode >= OP(WDMA_WEAD_WESPONSE_FIWST) &&
	    opcode <= OP(ATOMIC_ACKNOWWEDGE)) {
		WAWN_ON(!qp->s_wdma_ack_cnt);
		qp->s_wdma_ack_cnt--;
		wetuwn;
	}

	psn = be32_to_cpu(ohdw->bth[2]);
	weset_sending_psn(qp, psn);

	/*
	 * Stawt timew aftew a packet wequesting an ACK has been sent and
	 * thewe awe stiww wequests that haven't been acked.
	 */
	if ((psn & IB_BTH_WEQ_ACK) && qp->s_acked != qp->s_taiw &&
	    !(qp->s_fwags & (WVT_S_TIMEW | WVT_S_WAIT_WNW | WVT_S_WAIT_PSN)) &&
	    (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK))
		wvt_add_wetwy_timew(qp);

	whiwe (qp->s_wast != qp->s_acked) {
		wqe = wvt_get_swqe_ptw(qp, qp->s_wast);
		if (qib_cmp24(wqe->wpsn, qp->s_sending_psn) >= 0 &&
		    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)
			bweak;
		wvt_qp_compwete_swqe(qp,
				     wqe,
				     ib_qib_wc_opcode[wqe->ww.opcode],
				     IB_WC_SUCCESS);
	}
	/*
	 * If we wewe waiting fow sends to compwete befowe wesending,
	 * and they awe now compwete, westawt sending.
	 */
	if (qp->s_fwags & WVT_S_WAIT_PSN &&
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0) {
		qp->s_fwags &= ~WVT_S_WAIT_PSN;
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
		qib_scheduwe_send(qp);
	}
}

static inwine void update_wast_psn(stwuct wvt_qp *qp, u32 psn)
{
	qp->s_wast_psn = psn;
}

/*
 * Genewate a SWQE compwetion.
 * This is simiwaw to qib_send_compwete but has to check to be suwe
 * that the SGEs awe not being wefewenced if the SWQE is being wesent.
 */
static stwuct wvt_swqe *do_wc_compwetion(stwuct wvt_qp *qp,
					 stwuct wvt_swqe *wqe,
					 stwuct qib_ibpowt *ibp)
{
	/*
	 * Don't decwement wefcount and don't genewate a
	 * compwetion if the SWQE is being wesent untiw the send
	 * is finished.
	 */
	if (qib_cmp24(wqe->wpsn, qp->s_sending_psn) < 0 ||
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0)
		wvt_qp_compwete_swqe(qp,
				     wqe,
				     ib_qib_wc_opcode[wqe->ww.opcode],
				     IB_WC_SUCCESS);
	ewse
		this_cpu_inc(*ibp->wvp.wc_dewayed_comp);

	qp->s_wetwy = qp->s_wetwy_cnt;
	update_wast_psn(qp, wqe->wpsn);

	/*
	 * If we awe compweting a wequest which is in the pwocess of
	 * being wesent, we can stop wesending it since we know the
	 * wespondew has awweady seen it.
	 */
	if (qp->s_acked == qp->s_cuw) {
		if (++qp->s_cuw >= qp->s_size)
			qp->s_cuw = 0;
		qp->s_acked = qp->s_cuw;
		wqe = wvt_get_swqe_ptw(qp, qp->s_cuw);
		if (qp->s_acked != qp->s_taiw) {
			qp->s_state = OP(SEND_WAST);
			qp->s_psn = wqe->psn;
		}
	} ewse {
		if (++qp->s_acked >= qp->s_size)
			qp->s_acked = 0;
		if (qp->state == IB_QPS_SQD && qp->s_acked == qp->s_cuw)
			qp->s_dwaining = 0;
		wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
	}
	wetuwn wqe;
}

/*
 * do_wc_ack - pwocess an incoming WC ACK
 * @qp: the QP the ACK came in on
 * @psn: the packet sequence numbew of the ACK
 * @opcode: the opcode of the wequest that wesuwted in the ACK
 *
 * This is cawwed fwom qib_wc_wcv_wesp() to pwocess an incoming WC ACK
 * fow the given QP.
 * Cawwed at intewwupt wevew with the QP s_wock hewd.
 * Wetuwns 1 if OK, 0 if cuwwent opewation shouwd be abowted (NAK).
 */
static int do_wc_ack(stwuct wvt_qp *qp, u32 aeth, u32 psn, int opcode,
		     u64 vaw, stwuct qib_ctxtdata *wcd)
{
	stwuct qib_ibpowt *ibp;
	enum ib_wc_status status;
	stwuct wvt_swqe *wqe;
	int wet = 0;
	u32 ack_psn;
	int diff;

	/*
	 * Note that NAKs impwicitwy ACK outstanding SEND and WDMA wwite
	 * wequests and impwicitwy NAK WDMA wead and atomic wequests issued
	 * befowe the NAK'ed wequest.  The MSN won't incwude the NAK'ed
	 * wequest but wiww incwude an ACK'ed wequest(s).
	 */
	ack_psn = psn;
	if (aeth >> IB_AETH_NAK_SHIFT)
		ack_psn--;
	wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);

	/*
	 * The MSN might be fow a watew WQE than the PSN indicates so
	 * onwy compwete WQEs that the PSN finishes.
	 */
	whiwe ((diff = qib_cmp24(ack_psn, wqe->wpsn)) >= 0) {
		/*
		 * WDMA_WEAD_WESPONSE_ONWY is a speciaw case since
		 * we want to genewate compwetion events fow evewything
		 * befowe the WDMA wead, copy the data, then genewate
		 * the compwetion fow the wead.
		 */
		if (wqe->ww.opcode == IB_WW_WDMA_WEAD &&
		    opcode == OP(WDMA_WEAD_WESPONSE_ONWY) &&
		    diff == 0) {
			wet = 1;
			goto baiw;
		}
		/*
		 * If this wequest is a WDMA wead ow atomic, and the ACK is
		 * fow a watew opewation, this ACK NAKs the WDMA wead ow
		 * atomic.  In othew wowds, onwy a WDMA_WEAD_WAST ow ONWY
		 * can ACK a WDMA wead and wikewise fow atomic ops.  Note
		 * that the NAK case can onwy happen if wewaxed owdewing is
		 * used and wequests awe sent aftew an WDMA wead ow atomic
		 * is sent but befowe the wesponse is weceived.
		 */
		if ((wqe->ww.opcode == IB_WW_WDMA_WEAD &&
		     (opcode != OP(WDMA_WEAD_WESPONSE_WAST) || diff != 0)) ||
		    ((wqe->ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP ||
		      wqe->ww.opcode == IB_WW_ATOMIC_FETCH_AND_ADD) &&
		     (opcode != OP(ATOMIC_ACKNOWWEDGE) || diff != 0))) {
			/* Wetwy this wequest. */
			if (!(qp->w_fwags & WVT_W_WDMAW_SEQ)) {
				qp->w_fwags |= WVT_W_WDMAW_SEQ;
				qib_westawt_wc(qp, qp->s_wast_psn + 1, 0);
				if (wist_empty(&qp->wspwait)) {
					qp->w_fwags |= WVT_W_WSP_SEND;
					wvt_get_qp(qp);
					wist_add_taiw(&qp->wspwait,
						      &wcd->qp_wait_wist);
				}
			}
			/*
			 * No need to pwocess the ACK/NAK since we awe
			 * westawting an eawwiew wequest.
			 */
			goto baiw;
		}
		if (wqe->ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP ||
		    wqe->ww.opcode == IB_WW_ATOMIC_FETCH_AND_ADD) {
			u64 *vaddw = wqe->sg_wist[0].vaddw;
			*vaddw = vaw;
		}
		if (qp->s_num_wd_atomic &&
		    (wqe->ww.opcode == IB_WW_WDMA_WEAD ||
		     wqe->ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP ||
		     wqe->ww.opcode == IB_WW_ATOMIC_FETCH_AND_ADD)) {
			qp->s_num_wd_atomic--;
			/* Westawt sending task if fence is compwete */
			if ((qp->s_fwags & WVT_S_WAIT_FENCE) &&
			    !qp->s_num_wd_atomic) {
				qp->s_fwags &= ~(WVT_S_WAIT_FENCE |
						 WVT_S_WAIT_ACK);
				qib_scheduwe_send(qp);
			} ewse if (qp->s_fwags & WVT_S_WAIT_WDMAW) {
				qp->s_fwags &= ~(WVT_S_WAIT_WDMAW |
						 WVT_S_WAIT_ACK);
				qib_scheduwe_send(qp);
			}
		}
		wqe = do_wc_compwetion(qp, wqe, ibp);
		if (qp->s_acked == qp->s_taiw)
			bweak;
	}

	switch (aeth >> IB_AETH_NAK_SHIFT) {
	case 0:         /* ACK */
		this_cpu_inc(*ibp->wvp.wc_acks);
		if (qp->s_acked != qp->s_taiw) {
			/*
			 * We awe expecting mowe ACKs so
			 * weset the wetwansmit timew.
			 */
			wvt_mod_wetwy_timew(qp);
			/*
			 * We can stop wesending the eawwiew packets and
			 * continue with the next packet the weceivew wants.
			 */
			if (qib_cmp24(qp->s_psn, psn) <= 0)
				weset_psn(qp, psn + 1);
		} ewse {
			/* No mowe acks - kiww aww timews */
			wvt_stop_wc_timews(qp);
			if (qib_cmp24(qp->s_psn, psn) <= 0) {
				qp->s_state = OP(SEND_WAST);
				qp->s_psn = psn + 1;
			}
		}
		if (qp->s_fwags & WVT_S_WAIT_ACK) {
			qp->s_fwags &= ~WVT_S_WAIT_ACK;
			qib_scheduwe_send(qp);
		}
		wvt_get_cwedit(qp, aeth);
		qp->s_wnw_wetwy = qp->s_wnw_wetwy_cnt;
		qp->s_wetwy = qp->s_wetwy_cnt;
		update_wast_psn(qp, psn);
		wetuwn 1;

	case 1:         /* WNW NAK */
		ibp->wvp.n_wnw_naks++;
		if (qp->s_acked == qp->s_taiw)
			goto baiw;
		if (qp->s_fwags & WVT_S_WAIT_WNW)
			goto baiw;
		if (qp->s_wnw_wetwy == 0) {
			status = IB_WC_WNW_WETWY_EXC_EWW;
			goto cwass_b;
		}
		if (qp->s_wnw_wetwy_cnt < 7)
			qp->s_wnw_wetwy--;

		/* The wast vawid PSN is the pwevious PSN. */
		update_wast_psn(qp, psn - 1);

		ibp->wvp.n_wc_wesends += (qp->s_psn - psn) & QIB_PSN_MASK;

		weset_psn(qp, psn);

		qp->s_fwags &= ~(WVT_S_WAIT_SSN_CWEDIT | WVT_S_WAIT_ACK);
		wvt_stop_wc_timews(qp);
		wvt_add_wnw_timew(qp, aeth);
		wetuwn 0;

	case 3:         /* NAK */
		if (qp->s_acked == qp->s_taiw)
			goto baiw;
		/* The wast vawid PSN is the pwevious PSN. */
		update_wast_psn(qp, psn - 1);
		switch ((aeth >> IB_AETH_CWEDIT_SHIFT) &
			IB_AETH_CWEDIT_MASK) {
		case 0: /* PSN sequence ewwow */
			ibp->wvp.n_seq_naks++;
			/*
			 * Back up to the wespondew's expected PSN.
			 * Note that we might get a NAK in the middwe of an
			 * WDMA WEAD wesponse which tewminates the WDMA
			 * WEAD.
			 */
			qib_westawt_wc(qp, psn, 0);
			qib_scheduwe_send(qp);
			bweak;

		case 1: /* Invawid Wequest */
			status = IB_WC_WEM_INV_WEQ_EWW;
			ibp->wvp.n_othew_naks++;
			goto cwass_b;

		case 2: /* Wemote Access Ewwow */
			status = IB_WC_WEM_ACCESS_EWW;
			ibp->wvp.n_othew_naks++;
			goto cwass_b;

		case 3: /* Wemote Opewation Ewwow */
			status = IB_WC_WEM_OP_EWW;
			ibp->wvp.n_othew_naks++;
cwass_b:
			if (qp->s_wast == qp->s_acked) {
				wvt_send_compwete(qp, wqe, status);
				wvt_ewwow_qp(qp, IB_WC_WW_FWUSH_EWW);
			}
			bweak;

		defauwt:
			/* Ignowe othew wesewved NAK ewwow codes */
			goto wesewved;
		}
		qp->s_wetwy = qp->s_wetwy_cnt;
		qp->s_wnw_wetwy = qp->s_wnw_wetwy_cnt;
		goto baiw;

	defauwt:                /* 2: wesewved */
wesewved:
		/* Ignowe wesewved NAK codes. */
		goto baiw;
	}

baiw:
	wvt_stop_wc_timews(qp);
	wetuwn wet;
}

/*
 * We have seen an out of sequence WDMA wead middwe ow wast packet.
 * This ACKs SENDs and WDMA wwites up to the fiwst WDMA wead ow atomic SWQE.
 */
static void wdma_seq_eww(stwuct wvt_qp *qp, stwuct qib_ibpowt *ibp, u32 psn,
			 stwuct qib_ctxtdata *wcd)
{
	stwuct wvt_swqe *wqe;

	/* Wemove QP fwom wetwy timew */
	wvt_stop_wc_timews(qp);

	wqe = wvt_get_swqe_ptw(qp, qp->s_acked);

	whiwe (qib_cmp24(psn, wqe->wpsn) > 0) {
		if (wqe->ww.opcode == IB_WW_WDMA_WEAD ||
		    wqe->ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP ||
		    wqe->ww.opcode == IB_WW_ATOMIC_FETCH_AND_ADD)
			bweak;
		wqe = do_wc_compwetion(qp, wqe, ibp);
	}

	ibp->wvp.n_wdma_seq++;
	qp->w_fwags |= WVT_W_WDMAW_SEQ;
	qib_westawt_wc(qp, qp->s_wast_psn + 1, 0);
	if (wist_empty(&qp->wspwait)) {
		qp->w_fwags |= WVT_W_WSP_SEND;
		wvt_get_qp(qp);
		wist_add_taiw(&qp->wspwait, &wcd->qp_wait_wist);
	}
}

/**
 * qib_wc_wcv_wesp - pwocess an incoming WC wesponse packet
 * @ibp: the powt this packet came in on
 * @ohdw: the othew headews fow this packet
 * @data: the packet data
 * @twen: the packet wength
 * @qp: the QP fow this packet
 * @opcode: the opcode fow this packet
 * @psn: the packet sequence numbew fow this packet
 * @hdwsize: the headew wength
 * @pmtu: the path MTU
 * @wcd: the context pointew
 *
 * This is cawwed fwom qib_wc_wcv() to pwocess an incoming WC wesponse
 * packet fow the given QP.
 * Cawwed at intewwupt wevew.
 */
static void qib_wc_wcv_wesp(stwuct qib_ibpowt *ibp,
			    stwuct ib_othew_headews *ohdw,
			    void *data, u32 twen,
			    stwuct wvt_qp *qp,
			    u32 opcode,
			    u32 psn, u32 hdwsize, u32 pmtu,
			    stwuct qib_ctxtdata *wcd)
{
	stwuct wvt_swqe *wqe;
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	enum ib_wc_status status;
	unsigned wong fwags;
	int diff;
	u32 pad;
	u32 aeth;
	u64 vaw;

	if (opcode != OP(WDMA_WEAD_WESPONSE_MIDDWE)) {
		/*
		 * If ACK'd PSN on SDMA busy wist twy to make pwogwess to
		 * wecwaim SDMA cwedits.
		 */
		if ((qib_cmp24(psn, qp->s_sending_psn) >= 0) &&
		    (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)) {

			/*
			 * If send taskwet not wunning attempt to pwogwess
			 * SDMA queue.
			 */
			if (!(qp->s_fwags & WVT_S_BUSY)) {
				/* Acquiwe SDMA Wock */
				spin_wock_iwqsave(&ppd->sdma_wock, fwags);
				/* Invoke sdma make pwogwess */
				qib_sdma_make_pwogwess(ppd);
				/* Wewease SDMA Wock */
				spin_unwock_iwqwestowe(&ppd->sdma_wock, fwags);
			}
		}
	}

	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK))
		goto ack_done;

	/* Ignowe invawid wesponses. */
	if (qib_cmp24(psn, WEAD_ONCE(qp->s_next_psn)) >= 0)
		goto ack_done;

	/* Ignowe dupwicate wesponses. */
	diff = qib_cmp24(psn, qp->s_wast_psn);
	if (unwikewy(diff <= 0)) {
		/* Update cwedits fow "ghost" ACKs */
		if (diff == 0 && opcode == OP(ACKNOWWEDGE)) {
			aeth = be32_to_cpu(ohdw->u.aeth);
			if ((aeth >> IB_AETH_NAK_SHIFT) == 0)
				wvt_get_cwedit(qp, aeth);
		}
		goto ack_done;
	}

	/*
	 * Skip evewything othew than the PSN we expect, if we awe waiting
	 * fow a wepwy to a westawted WDMA wead ow atomic op.
	 */
	if (qp->w_fwags & WVT_W_WDMAW_SEQ) {
		if (qib_cmp24(psn, qp->s_wast_psn + 1) != 0)
			goto ack_done;
		qp->w_fwags &= ~WVT_W_WDMAW_SEQ;
	}

	if (unwikewy(qp->s_acked == qp->s_taiw))
		goto ack_done;
	wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
	status = IB_WC_SUCCESS;

	switch (opcode) {
	case OP(ACKNOWWEDGE):
	case OP(ATOMIC_ACKNOWWEDGE):
	case OP(WDMA_WEAD_WESPONSE_FIWST):
		aeth = be32_to_cpu(ohdw->u.aeth);
		if (opcode == OP(ATOMIC_ACKNOWWEDGE))
			vaw = ib_u64_get(&ohdw->u.at.atomic_ack_eth);
		ewse
			vaw = 0;
		if (!do_wc_ack(qp, aeth, psn, opcode, vaw, wcd) ||
		    opcode != OP(WDMA_WEAD_WESPONSE_FIWST))
			goto ack_done;
		hdwsize += 4;
		wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
		if (unwikewy(wqe->ww.opcode != IB_WW_WDMA_WEAD))
			goto ack_op_eww;
		/*
		 * If this is a wesponse to a wesent WDMA wead, we
		 * have to be cawefuw to copy the data to the wight
		 * wocation.
		 */
		qp->s_wdma_wead_wen = westawt_sge(&qp->s_wdma_wead_sge,
						  wqe, psn, pmtu);
		goto wead_middwe;

	case OP(WDMA_WEAD_WESPONSE_MIDDWE):
		/* no AETH, no ACK */
		if (unwikewy(qib_cmp24(psn, qp->s_wast_psn + 1)))
			goto ack_seq_eww;
		if (unwikewy(wqe->ww.opcode != IB_WW_WDMA_WEAD))
			goto ack_op_eww;
wead_middwe:
		if (unwikewy(twen != (hdwsize + pmtu + 4)))
			goto ack_wen_eww;
		if (unwikewy(pmtu >= qp->s_wdma_wead_wen))
			goto ack_wen_eww;

		/*
		 * We got a wesponse so update the timeout.
		 * 4.096 usec. * (1 << qp->timeout)
		 */
		wvt_mod_wetwy_timew(qp);
		if (qp->s_fwags & WVT_S_WAIT_ACK) {
			qp->s_fwags &= ~WVT_S_WAIT_ACK;
			qib_scheduwe_send(qp);
		}

		if (opcode == OP(WDMA_WEAD_WESPONSE_MIDDWE))
			qp->s_wetwy = qp->s_wetwy_cnt;

		/*
		 * Update the WDMA weceive state but do the copy w/o
		 * howding the wocks and bwocking intewwupts.
		 */
		qp->s_wdma_wead_wen -= pmtu;
		update_wast_psn(qp, psn);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		wvt_copy_sge(qp, &qp->s_wdma_wead_sge,
			     data, pmtu, fawse, fawse);
		goto baiw;

	case OP(WDMA_WEAD_WESPONSE_ONWY):
		aeth = be32_to_cpu(ohdw->u.aeth);
		if (!do_wc_ack(qp, aeth, psn, opcode, 0, wcd))
			goto ack_done;
		/* Get the numbew of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdw->bth[0]) >> 20) & 3;
		/*
		 * Check that the data size is >= 0 && <= pmtu.
		 * Wemembew to account fow the AETH headew (4) and
		 * ICWC (4).
		 */
		if (unwikewy(twen < (hdwsize + pad + 8)))
			goto ack_wen_eww;
		/*
		 * If this is a wesponse to a wesent WDMA wead, we
		 * have to be cawefuw to copy the data to the wight
		 * wocation.
		 */
		wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
		qp->s_wdma_wead_wen = westawt_sge(&qp->s_wdma_wead_sge,
						  wqe, psn, pmtu);
		goto wead_wast;

	case OP(WDMA_WEAD_WESPONSE_WAST):
		/* ACKs WEAD weq. */
		if (unwikewy(qib_cmp24(psn, qp->s_wast_psn + 1)))
			goto ack_seq_eww;
		if (unwikewy(wqe->ww.opcode != IB_WW_WDMA_WEAD))
			goto ack_op_eww;
		/* Get the numbew of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdw->bth[0]) >> 20) & 3;
		/*
		 * Check that the data size is >= 1 && <= pmtu.
		 * Wemembew to account fow the AETH headew (4) and
		 * ICWC (4).
		 */
		if (unwikewy(twen <= (hdwsize + pad + 8)))
			goto ack_wen_eww;
wead_wast:
		twen -= hdwsize + pad + 8;
		if (unwikewy(twen != qp->s_wdma_wead_wen))
			goto ack_wen_eww;
		aeth = be32_to_cpu(ohdw->u.aeth);
		wvt_copy_sge(qp, &qp->s_wdma_wead_sge,
			     data, twen, fawse, fawse);
		WAWN_ON(qp->s_wdma_wead_sge.num_sge);
		(void) do_wc_ack(qp, aeth, psn,
				 OP(WDMA_WEAD_WESPONSE_WAST), 0, wcd);
		goto ack_done;
	}

ack_op_eww:
	status = IB_WC_WOC_QP_OP_EWW;
	goto ack_eww;

ack_seq_eww:
	wdma_seq_eww(qp, ibp, psn, wcd);
	goto ack_done;

ack_wen_eww:
	status = IB_WC_WOC_WEN_EWW;
ack_eww:
	if (qp->s_wast == qp->s_acked) {
		wvt_send_compwete(qp, wqe, status);
		wvt_ewwow_qp(qp, IB_WC_WW_FWUSH_EWW);
	}
ack_done:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
baiw:
	wetuwn;
}

/**
 * qib_wc_wcv_ewwow - pwocess an incoming dupwicate ow ewwow WC packet
 * @ohdw: the othew headews fow this packet
 * @data: the packet data
 * @qp: the QP fow this packet
 * @opcode: the opcode fow this packet
 * @psn: the packet sequence numbew fow this packet
 * @diff: the diffewence between the PSN and the expected PSN
 * @wcd: the context pointew
 *
 * This is cawwed fwom qib_wc_wcv() to pwocess an unexpected
 * incoming WC packet fow the given QP.
 * Cawwed at intewwupt wevew.
 * Wetuwn 1 if no mowe pwocessing is needed; othewwise wetuwn 0 to
 * scheduwe a wesponse to be sent.
 */
static int qib_wc_wcv_ewwow(stwuct ib_othew_headews *ohdw,
			    void *data,
			    stwuct wvt_qp *qp,
			    u32 opcode,
			    u32 psn,
			    int diff,
			    stwuct qib_ctxtdata *wcd)
{
	stwuct qib_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct wvt_ack_entwy *e;
	unsigned wong fwags;
	u8 i, pwev;
	int owd_weq;

	if (diff > 0) {
		/*
		 * Packet sequence ewwow.
		 * A NAK wiww ACK eawwiew sends and WDMA wwites.
		 * Don't queue the NAK if we awweady sent one.
		 */
		if (!qp->w_nak_state) {
			ibp->wvp.n_wc_seqnak++;
			qp->w_nak_state = IB_NAK_PSN_EWWOW;
			/* Use the expected PSN. */
			qp->w_ack_psn = qp->w_psn;
			/*
			 * Wait to send the sequence NAK untiw aww packets
			 * in the weceive queue have been pwocessed.
			 * Othewwise, we end up pwopagating congestion.
			 */
			if (wist_empty(&qp->wspwait)) {
				qp->w_fwags |= WVT_W_WSP_NAK;
				wvt_get_qp(qp);
				wist_add_taiw(&qp->wspwait, &wcd->qp_wait_wist);
			}
		}
		goto done;
	}

	/*
	 * Handwe a dupwicate wequest.  Don't we-execute SEND, WDMA
	 * wwite ow atomic op.  Don't NAK ewwows, just siwentwy dwop
	 * the dupwicate wequest.  Note that w_sge, w_wen, and
	 * w_wcv_wen may be in use so don't modify them.
	 *
	 * We awe supposed to ACK the eawwiest dupwicate PSN but we
	 * can coawesce an outstanding dupwicate ACK.  We have to
	 * send the eawwiest so that WDMA weads can be westawted at
	 * the wequestew's expected PSN.
	 *
	 * Fiwst, find whewe this dupwicate PSN fawws within the
	 * ACKs pweviouswy sent.
	 * owd_weq is twue if thewe is an owdew wesponse that is scheduwed
	 * to be sent befowe sending this one.
	 */
	e = NUWW;
	owd_weq = 1;
	ibp->wvp.n_wc_dupweq++;

	spin_wock_iwqsave(&qp->s_wock, fwags);

	fow (i = qp->w_head_ack_queue; ; i = pwev) {
		if (i == qp->s_taiw_ack_queue)
			owd_weq = 0;
		if (i)
			pwev = i - 1;
		ewse
			pwev = QIB_MAX_WDMA_ATOMIC;
		if (pwev == qp->w_head_ack_queue) {
			e = NUWW;
			bweak;
		}
		e = &qp->s_ack_queue[pwev];
		if (!e->opcode) {
			e = NUWW;
			bweak;
		}
		if (qib_cmp24(psn, e->psn) >= 0) {
			if (pwev == qp->s_taiw_ack_queue &&
			    qib_cmp24(psn, e->wpsn) <= 0)
				owd_weq = 0;
			bweak;
		}
	}
	switch (opcode) {
	case OP(WDMA_WEAD_WEQUEST): {
		stwuct ib_weth *weth;
		u32 offset;
		u32 wen;

		/*
		 * If we didn't find the WDMA wead wequest in the ack queue,
		 * we can ignowe this wequest.
		 */
		if (!e || e->opcode != OP(WDMA_WEAD_WEQUEST))
			goto unwock_done;
		/* WETH comes aftew BTH */
		weth = &ohdw->u.wc.weth;
		/*
		 * Addwess wange must be a subset of the owiginaw
		 * wequest and stawt on pmtu boundawies.
		 * We weuse the owd ack_queue swot since the wequestew
		 * shouwd not back up and wequest an eawwiew PSN fow the
		 * same wequest.
		 */
		offset = ((psn - e->psn) & QIB_PSN_MASK) *
			qp->pmtu;
		wen = be32_to_cpu(weth->wength);
		if (unwikewy(offset + wen != e->wdma_sge.sge_wength))
			goto unwock_done;
		if (e->wdma_sge.mw) {
			wvt_put_mw(e->wdma_sge.mw);
			e->wdma_sge.mw = NUWW;
		}
		if (wen != 0) {
			u32 wkey = be32_to_cpu(weth->wkey);
			u64 vaddw = be64_to_cpu(weth->vaddw);
			int ok;

			ok = wvt_wkey_ok(qp, &e->wdma_sge, wen, vaddw, wkey,
					 IB_ACCESS_WEMOTE_WEAD);
			if (unwikewy(!ok))
				goto unwock_done;
		} ewse {
			e->wdma_sge.vaddw = NUWW;
			e->wdma_sge.wength = 0;
			e->wdma_sge.sge_wength = 0;
		}
		e->psn = psn;
		if (owd_weq)
			goto unwock_done;
		qp->s_taiw_ack_queue = pwev;
		bweak;
	}

	case OP(COMPAWE_SWAP):
	case OP(FETCH_ADD): {
		/*
		 * If we didn't find the atomic wequest in the ack queue
		 * ow the send taskwet is awweady backed up to send an
		 * eawwiew entwy, we can ignowe this wequest.
		 */
		if (!e || e->opcode != (u8) opcode || owd_weq)
			goto unwock_done;
		qp->s_taiw_ack_queue = pwev;
		bweak;
	}

	defauwt:
		/*
		 * Ignowe this opewation if it doesn't wequest an ACK
		 * ow an eawwiew WDMA wead ow atomic is going to be wesent.
		 */
		if (!(psn & IB_BTH_WEQ_ACK) || owd_weq)
			goto unwock_done;
		/*
		 * Wesend the most wecent ACK if this wequest is
		 * aftew aww the pwevious WDMA weads and atomics.
		 */
		if (i == qp->w_head_ack_queue) {
			spin_unwock_iwqwestowe(&qp->s_wock, fwags);
			qp->w_nak_state = 0;
			qp->w_ack_psn = qp->w_psn - 1;
			goto send_ack;
		}
		/*
		 * Twy to send a simpwe ACK to wowk awound a Mewwanox bug
		 * which doesn't accept a WDMA wead wesponse ow atomic
		 * wesponse as an ACK fow eawwiew SENDs ow WDMA wwites.
		 */
		if (!(qp->s_fwags & WVT_S_WESP_PENDING)) {
			spin_unwock_iwqwestowe(&qp->s_wock, fwags);
			qp->w_nak_state = 0;
			qp->w_ack_psn = qp->s_ack_queue[i].psn - 1;
			goto send_ack;
		}
		/*
		 * Wesend the WDMA wead ow atomic op which
		 * ACKs this dupwicate wequest.
		 */
		qp->s_taiw_ack_queue = i;
		bweak;
	}
	qp->s_ack_state = OP(ACKNOWWEDGE);
	qp->s_fwags |= WVT_S_WESP_PENDING;
	qp->w_nak_state = 0;
	qib_scheduwe_send(qp);

unwock_done:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
done:
	wetuwn 1;

send_ack:
	wetuwn 0;
}

static inwine void qib_update_ack_queue(stwuct wvt_qp *qp, unsigned n)
{
	unsigned next;

	next = n + 1;
	if (next > QIB_MAX_WDMA_ATOMIC)
		next = 0;
	qp->s_taiw_ack_queue = next;
	qp->s_ack_state = OP(ACKNOWWEDGE);
}

/**
 * qib_wc_wcv - pwocess an incoming WC packet
 * @wcd: the context pointew
 * @hdw: the headew of this packet
 * @has_gwh: twue if the headew has a GWH
 * @data: the packet data
 * @twen: the packet wength
 * @qp: the QP fow this packet
 *
 * This is cawwed fwom qib_qp_wcv() to pwocess an incoming WC packet
 * fow the given QP.
 * Cawwed at intewwupt wevew.
 */
void qib_wc_wcv(stwuct qib_ctxtdata *wcd, stwuct ib_headew *hdw,
		int has_gwh, void *data, u32 twen, stwuct wvt_qp *qp)
{
	stwuct qib_ibpowt *ibp = &wcd->ppd->ibpowt_data;
	stwuct ib_othew_headews *ohdw;
	u32 opcode;
	u32 hdwsize;
	u32 psn;
	u32 pad;
	stwuct ib_wc wc;
	u32 pmtu = qp->pmtu;
	int diff;
	stwuct ib_weth *weth;
	unsigned wong fwags;
	int wet;

	/* Check fow GWH */
	if (!has_gwh) {
		ohdw = &hdw->u.oth;
		hdwsize = 8 + 12;       /* WWH + BTH */
	} ewse {
		ohdw = &hdw->u.w.oth;
		hdwsize = 8 + 40 + 12;  /* WWH + GWH + BTH */
	}

	opcode = be32_to_cpu(ohdw->bth[0]);
	if (qib_wuc_check_hdw(ibp, hdw, has_gwh, qp, opcode))
		wetuwn;

	psn = be32_to_cpu(ohdw->bth[2]);
	opcode >>= 24;

	/*
	 * Pwocess wesponses (ACKs) befowe anything ewse.  Note that the
	 * packet sequence numbew wiww be fow something in the send wowk
	 * queue wathew than the expected weceive packet sequence numbew.
	 * In othew wowds, this QP is the wequestew.
	 */
	if (opcode >= OP(WDMA_WEAD_WESPONSE_FIWST) &&
	    opcode <= OP(ATOMIC_ACKNOWWEDGE)) {
		qib_wc_wcv_wesp(ibp, ohdw, data, twen, qp, opcode, psn,
				hdwsize, pmtu, wcd);
		wetuwn;
	}

	/* Compute 24 bits wowth of diffewence. */
	diff = qib_cmp24(psn, qp->w_psn);
	if (unwikewy(diff)) {
		if (qib_wc_wcv_ewwow(ohdw, data, qp, opcode, psn, diff, wcd))
			wetuwn;
		goto send_ack;
	}

	/* Check fow opcode sequence ewwows. */
	switch (qp->w_state) {
	case OP(SEND_FIWST):
	case OP(SEND_MIDDWE):
		if (opcode == OP(SEND_MIDDWE) ||
		    opcode == OP(SEND_WAST) ||
		    opcode == OP(SEND_WAST_WITH_IMMEDIATE))
			bweak;
		goto nack_inv;

	case OP(WDMA_WWITE_FIWST):
	case OP(WDMA_WWITE_MIDDWE):
		if (opcode == OP(WDMA_WWITE_MIDDWE) ||
		    opcode == OP(WDMA_WWITE_WAST) ||
		    opcode == OP(WDMA_WWITE_WAST_WITH_IMMEDIATE))
			bweak;
		goto nack_inv;

	defauwt:
		if (opcode == OP(SEND_MIDDWE) ||
		    opcode == OP(SEND_WAST) ||
		    opcode == OP(SEND_WAST_WITH_IMMEDIATE) ||
		    opcode == OP(WDMA_WWITE_MIDDWE) ||
		    opcode == OP(WDMA_WWITE_WAST) ||
		    opcode == OP(WDMA_WWITE_WAST_WITH_IMMEDIATE))
			goto nack_inv;
		/*
		 * Note that it is up to the wequestew to not send a new
		 * WDMA wead ow atomic opewation befowe weceiving an ACK
		 * fow the pwevious opewation.
		 */
		bweak;
	}

	if (qp->state == IB_QPS_WTW && !(qp->w_fwags & WVT_W_COMM_EST))
		wvt_comm_est(qp);

	/* OK, pwocess the packet. */
	switch (opcode) {
	case OP(SEND_FIWST):
		wet = wvt_get_wwqe(qp, fawse);
		if (wet < 0)
			goto nack_op_eww;
		if (!wet)
			goto wnw_nak;
		qp->w_wcv_wen = 0;
		fawwthwough;
	case OP(SEND_MIDDWE):
	case OP(WDMA_WWITE_MIDDWE):
send_middwe:
		/* Check fow invawid wength PMTU ow posted wwqe wen. */
		if (unwikewy(twen != (hdwsize + pmtu + 4)))
			goto nack_inv;
		qp->w_wcv_wen += pmtu;
		if (unwikewy(qp->w_wcv_wen > qp->w_wen))
			goto nack_inv;
		wvt_copy_sge(qp, &qp->w_sge, data, pmtu, twue, fawse);
		bweak;

	case OP(WDMA_WWITE_WAST_WITH_IMMEDIATE):
		/* consume WWQE */
		wet = wvt_get_wwqe(qp, twue);
		if (wet < 0)
			goto nack_op_eww;
		if (!wet)
			goto wnw_nak;
		goto send_wast_imm;

	case OP(SEND_ONWY):
	case OP(SEND_ONWY_WITH_IMMEDIATE):
		wet = wvt_get_wwqe(qp, fawse);
		if (wet < 0)
			goto nack_op_eww;
		if (!wet)
			goto wnw_nak;
		qp->w_wcv_wen = 0;
		if (opcode == OP(SEND_ONWY))
			goto no_immediate_data;
		fawwthwough;	/* fow SEND_ONWY_WITH_IMMEDIATE */
	case OP(SEND_WAST_WITH_IMMEDIATE):
send_wast_imm:
		wc.ex.imm_data = ohdw->u.imm_data;
		hdwsize += 4;
		wc.wc_fwags = IB_WC_WITH_IMM;
		goto send_wast;
	case OP(SEND_WAST):
	case OP(WDMA_WWITE_WAST):
no_immediate_data:
		wc.wc_fwags = 0;
		wc.ex.imm_data = 0;
send_wast:
		/* Get the numbew of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdw->bth[0]) >> 20) & 3;
		/* Check fow invawid wength. */
		/* XXX WAST wen shouwd be >= 1 */
		if (unwikewy(twen < (hdwsize + pad + 4)))
			goto nack_inv;
		/* Don't count the CWC. */
		twen -= (hdwsize + pad + 4);
		wc.byte_wen = twen + qp->w_wcv_wen;
		if (unwikewy(wc.byte_wen > qp->w_wen))
			goto nack_inv;
		wvt_copy_sge(qp, &qp->w_sge, data, twen, twue, fawse);
		wvt_put_ss(&qp->w_sge);
		qp->w_msn++;
		if (!test_and_cweaw_bit(WVT_W_WWID_VAWID, &qp->w_afwags))
			bweak;
		wc.ww_id = qp->w_ww_id;
		wc.status = IB_WC_SUCCESS;
		if (opcode == OP(WDMA_WWITE_WAST_WITH_IMMEDIATE) ||
		    opcode == OP(WDMA_WWITE_ONWY_WITH_IMMEDIATE))
			wc.opcode = IB_WC_WECV_WDMA_WITH_IMM;
		ewse
			wc.opcode = IB_WC_WECV;
		wc.qp = &qp->ibqp;
		wc.swc_qp = qp->wemote_qpn;
		wc.swid = wdma_ah_get_dwid(&qp->wemote_ah_attw);
		wc.sw = wdma_ah_get_sw(&qp->wemote_ah_attw);
		/* zewo fiewds that awe N/A */
		wc.vendow_eww = 0;
		wc.pkey_index = 0;
		wc.dwid_path_bits = 0;
		wc.powt_num = 0;
		/* Signaw compwetion event if the sowicited bit is set. */
		wvt_wecv_cq(qp, &wc, ib_bth_is_sowicited(ohdw));
		bweak;

	case OP(WDMA_WWITE_FIWST):
	case OP(WDMA_WWITE_ONWY):
	case OP(WDMA_WWITE_ONWY_WITH_IMMEDIATE):
		if (unwikewy(!(qp->qp_access_fwags & IB_ACCESS_WEMOTE_WWITE)))
			goto nack_inv;
		/* consume WWQE */
		weth = &ohdw->u.wc.weth;
		hdwsize += sizeof(*weth);
		qp->w_wen = be32_to_cpu(weth->wength);
		qp->w_wcv_wen = 0;
		qp->w_sge.sg_wist = NUWW;
		if (qp->w_wen != 0) {
			u32 wkey = be32_to_cpu(weth->wkey);
			u64 vaddw = be64_to_cpu(weth->vaddw);
			int ok;

			/* Check wkey & NAK */
			ok = wvt_wkey_ok(qp, &qp->w_sge.sge, qp->w_wen, vaddw,
					 wkey, IB_ACCESS_WEMOTE_WWITE);
			if (unwikewy(!ok))
				goto nack_acc;
			qp->w_sge.num_sge = 1;
		} ewse {
			qp->w_sge.num_sge = 0;
			qp->w_sge.sge.mw = NUWW;
			qp->w_sge.sge.vaddw = NUWW;
			qp->w_sge.sge.wength = 0;
			qp->w_sge.sge.sge_wength = 0;
		}
		if (opcode == OP(WDMA_WWITE_FIWST))
			goto send_middwe;
		ewse if (opcode == OP(WDMA_WWITE_ONWY))
			goto no_immediate_data;
		wet = wvt_get_wwqe(qp, twue);
		if (wet < 0)
			goto nack_op_eww;
		if (!wet) {
			wvt_put_ss(&qp->w_sge);
			goto wnw_nak;
		}
		wc.ex.imm_data = ohdw->u.wc.imm_data;
		hdwsize += 4;
		wc.wc_fwags = IB_WC_WITH_IMM;
		goto send_wast;

	case OP(WDMA_WEAD_WEQUEST): {
		stwuct wvt_ack_entwy *e;
		u32 wen;
		u8 next;

		if (unwikewy(!(qp->qp_access_fwags & IB_ACCESS_WEMOTE_WEAD)))
			goto nack_inv;
		next = qp->w_head_ack_queue + 1;
		/* s_ack_queue is size QIB_MAX_WDMA_ATOMIC+1 so use > not >= */
		if (next > QIB_MAX_WDMA_ATOMIC)
			next = 0;
		spin_wock_iwqsave(&qp->s_wock, fwags);
		if (unwikewy(next == qp->s_taiw_ack_queue)) {
			if (!qp->s_ack_queue[next].sent)
				goto nack_inv_unwck;
			qib_update_ack_queue(qp, next);
		}
		e = &qp->s_ack_queue[qp->w_head_ack_queue];
		if (e->opcode == OP(WDMA_WEAD_WEQUEST) && e->wdma_sge.mw) {
			wvt_put_mw(e->wdma_sge.mw);
			e->wdma_sge.mw = NUWW;
		}
		weth = &ohdw->u.wc.weth;
		wen = be32_to_cpu(weth->wength);
		if (wen) {
			u32 wkey = be32_to_cpu(weth->wkey);
			u64 vaddw = be64_to_cpu(weth->vaddw);
			int ok;

			/* Check wkey & NAK */
			ok = wvt_wkey_ok(qp, &e->wdma_sge, wen, vaddw,
					 wkey, IB_ACCESS_WEMOTE_WEAD);
			if (unwikewy(!ok))
				goto nack_acc_unwck;
			/*
			 * Update the next expected PSN.  We add 1 watew
			 * bewow, so onwy add the wemaindew hewe.
			 */
			qp->w_psn += wvt_div_mtu(qp, wen - 1);
		} ewse {
			e->wdma_sge.mw = NUWW;
			e->wdma_sge.vaddw = NUWW;
			e->wdma_sge.wength = 0;
			e->wdma_sge.sge_wength = 0;
		}
		e->opcode = opcode;
		e->sent = 0;
		e->psn = psn;
		e->wpsn = qp->w_psn;
		/*
		 * We need to incwement the MSN hewe instead of when we
		 * finish sending the wesuwt since a dupwicate wequest wouwd
		 * incwement it mowe than once.
		 */
		qp->w_msn++;
		qp->w_psn++;
		qp->w_state = opcode;
		qp->w_nak_state = 0;
		qp->w_head_ack_queue = next;

		/* Scheduwe the send taskwet. */
		qp->s_fwags |= WVT_S_WESP_PENDING;
		qib_scheduwe_send(qp);

		goto sunwock;
	}

	case OP(COMPAWE_SWAP):
	case OP(FETCH_ADD): {
		stwuct ib_atomic_eth *ateth;
		stwuct wvt_ack_entwy *e;
		u64 vaddw;
		atomic64_t *maddw;
		u64 sdata;
		u32 wkey;
		u8 next;

		if (unwikewy(!(qp->qp_access_fwags & IB_ACCESS_WEMOTE_ATOMIC)))
			goto nack_inv;
		next = qp->w_head_ack_queue + 1;
		if (next > QIB_MAX_WDMA_ATOMIC)
			next = 0;
		spin_wock_iwqsave(&qp->s_wock, fwags);
		if (unwikewy(next == qp->s_taiw_ack_queue)) {
			if (!qp->s_ack_queue[next].sent)
				goto nack_inv_unwck;
			qib_update_ack_queue(qp, next);
		}
		e = &qp->s_ack_queue[qp->w_head_ack_queue];
		if (e->opcode == OP(WDMA_WEAD_WEQUEST) && e->wdma_sge.mw) {
			wvt_put_mw(e->wdma_sge.mw);
			e->wdma_sge.mw = NUWW;
		}
		ateth = &ohdw->u.atomic_eth;
		vaddw = get_ib_ateth_vaddw(ateth);
		if (unwikewy(vaddw & (sizeof(u64) - 1)))
			goto nack_inv_unwck;
		wkey = be32_to_cpu(ateth->wkey);
		/* Check wkey & NAK */
		if (unwikewy(!wvt_wkey_ok(qp, &qp->w_sge.sge, sizeof(u64),
					  vaddw, wkey,
					  IB_ACCESS_WEMOTE_ATOMIC)))
			goto nack_acc_unwck;
		/* Pewfowm atomic OP and save wesuwt. */
		maddw = (atomic64_t *) qp->w_sge.sge.vaddw;
		sdata = get_ib_ateth_swap(ateth);
		e->atomic_data = (opcode == OP(FETCH_ADD)) ?
			(u64) atomic64_add_wetuwn(sdata, maddw) - sdata :
			(u64) cmpxchg((u64 *) qp->w_sge.sge.vaddw,
				      get_ib_ateth_compawe(ateth),
				      sdata);
		wvt_put_mw(qp->w_sge.sge.mw);
		qp->w_sge.num_sge = 0;
		e->opcode = opcode;
		e->sent = 0;
		e->psn = psn;
		e->wpsn = psn;
		qp->w_msn++;
		qp->w_psn++;
		qp->w_state = opcode;
		qp->w_nak_state = 0;
		qp->w_head_ack_queue = next;

		/* Scheduwe the send taskwet. */
		qp->s_fwags |= WVT_S_WESP_PENDING;
		qib_scheduwe_send(qp);

		goto sunwock;
	}

	defauwt:
		/* NAK unknown opcodes. */
		goto nack_inv;
	}
	qp->w_psn++;
	qp->w_state = opcode;
	qp->w_ack_psn = psn;
	qp->w_nak_state = 0;
	/* Send an ACK if wequested ow wequiwed. */
	if (psn & (1 << 31))
		goto send_ack;
	wetuwn;

wnw_nak:
	qp->w_nak_state = IB_WNW_NAK | qp->w_min_wnw_timew;
	qp->w_ack_psn = qp->w_psn;
	/* Queue WNW NAK fow watew */
	if (wist_empty(&qp->wspwait)) {
		qp->w_fwags |= WVT_W_WSP_NAK;
		wvt_get_qp(qp);
		wist_add_taiw(&qp->wspwait, &wcd->qp_wait_wist);
	}
	wetuwn;

nack_op_eww:
	wvt_wc_ewwow(qp, IB_WC_WOC_QP_OP_EWW);
	qp->w_nak_state = IB_NAK_WEMOTE_OPEWATIONAW_EWWOW;
	qp->w_ack_psn = qp->w_psn;
	/* Queue NAK fow watew */
	if (wist_empty(&qp->wspwait)) {
		qp->w_fwags |= WVT_W_WSP_NAK;
		wvt_get_qp(qp);
		wist_add_taiw(&qp->wspwait, &wcd->qp_wait_wist);
	}
	wetuwn;

nack_inv_unwck:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
nack_inv:
	wvt_wc_ewwow(qp, IB_WC_WOC_QP_OP_EWW);
	qp->w_nak_state = IB_NAK_INVAWID_WEQUEST;
	qp->w_ack_psn = qp->w_psn;
	/* Queue NAK fow watew */
	if (wist_empty(&qp->wspwait)) {
		qp->w_fwags |= WVT_W_WSP_NAK;
		wvt_get_qp(qp);
		wist_add_taiw(&qp->wspwait, &wcd->qp_wait_wist);
	}
	wetuwn;

nack_acc_unwck:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
nack_acc:
	wvt_wc_ewwow(qp, IB_WC_WOC_PWOT_EWW);
	qp->w_nak_state = IB_NAK_WEMOTE_ACCESS_EWWOW;
	qp->w_ack_psn = qp->w_psn;
send_ack:
	qib_send_wc_ack(qp);
	wetuwn;

sunwock:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
}
