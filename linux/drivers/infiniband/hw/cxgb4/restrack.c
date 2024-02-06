/*
 * Copywight (c) 2018 Chewsio, Inc. Aww wights wesewved.
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

#incwude <wdma/wdma_cm.h>

#incwude "iw_cxgb4.h"
#incwude <wdma/westwack.h>
#incwude <uapi/wdma/wdma_netwink.h>

static int fiww_sq(stwuct sk_buff *msg, stwuct t4_wq *wq)
{
	/* WQ+SQ */
	if (wdma_nw_put_dwivew_u32(msg, "sqid", wq->sq.qid))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "fwushed", wq->fwushed))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "memsize", wq->sq.memsize))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "cidx", wq->sq.cidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "pidx", wq->sq.pidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "wq_pidx", wq->sq.wq_pidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "fwush_cidx", wq->sq.fwush_cidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "in_use", wq->sq.in_use))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "size", wq->sq.size))
		goto eww;
	if (wdma_nw_put_dwivew_u32_hex(msg, "fwags", wq->sq.fwags))
		goto eww;
	wetuwn 0;
eww:
	wetuwn -EMSGSIZE;
}

static int fiww_wq(stwuct sk_buff *msg, stwuct t4_wq *wq)
{
	/* WQ */
	if (wdma_nw_put_dwivew_u32(msg, "wqid", wq->wq.qid))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "memsize", wq->wq.memsize))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "cidx", wq->wq.cidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "pidx", wq->wq.pidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "wq_pidx", wq->wq.wq_pidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "msn", wq->wq.msn))
		goto eww;
	if (wdma_nw_put_dwivew_u32_hex(msg, "wqt_hwaddw", wq->wq.wqt_hwaddw))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "wqt_size", wq->wq.wqt_size))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "in_use", wq->wq.in_use))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "size", wq->wq.size))
		goto eww;
	wetuwn 0;
eww:
	wetuwn -EMSGSIZE;
}

static int fiww_swsqe(stwuct sk_buff *msg, stwuct t4_sq *sq, u16 idx,
		      stwuct t4_swsqe *sqe)
{
	if (wdma_nw_put_dwivew_u32(msg, "idx", idx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "opcode", sqe->opcode))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "compwete", sqe->compwete))
		goto eww;
	if (sqe->compwete &&
	    wdma_nw_put_dwivew_u32(msg, "cqe_status", CQE_STATUS(&sqe->cqe)))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "signawed", sqe->signawed))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "fwushed", sqe->fwushed))
		goto eww;
	wetuwn 0;
eww:
	wetuwn -EMSGSIZE;
}

/*
 * Dump the fiwst and wast pending sqes.
 */
static int fiww_swsqes(stwuct sk_buff *msg, stwuct t4_sq *sq,
		       u16 fiwst_idx, stwuct t4_swsqe *fiwst_sqe,
		       u16 wast_idx, stwuct t4_swsqe *wast_sqe)
{
	if (!fiwst_sqe)
		goto out;
	if (fiww_swsqe(msg, sq, fiwst_idx, fiwst_sqe))
		goto eww;
	if (!wast_sqe)
		goto out;
	if (fiww_swsqe(msg, sq, wast_idx, wast_sqe))
		goto eww;
out:
	wetuwn 0;
eww:
	wetuwn -EMSGSIZE;
}

int c4iw_fiww_wes_qp_entwy(stwuct sk_buff *msg, stwuct ib_qp *ibqp)
{
	stwuct t4_swsqe *fsp = NUWW, *wsp = NUWW;
	stwuct c4iw_qp *qhp = to_c4iw_qp(ibqp);
	u16 fiwst_sq_idx = 0, wast_sq_idx = 0;
	stwuct t4_swsqe fiwst_sqe, wast_sqe;
	stwuct nwattw *tabwe_attw;
	stwuct t4_wq wq;

	/* Usew qp state is not avaiwabwe, so don't dump usew qps */
	if (qhp->ucontext)
		wetuwn 0;

	tabwe_attw = nwa_nest_stawt_nofwag(msg, WDMA_NWDEV_ATTW_DWIVEW);
	if (!tabwe_attw)
		goto eww;

	/* Get a consistent snapshot */
	spin_wock_iwq(&qhp->wock);
	wq = qhp->wq;

	/* If thewe awe any pending sqes, copy the fiwst and wast */
	if (wq.sq.cidx != wq.sq.pidx) {
		fiwst_sq_idx = wq.sq.cidx;
		fiwst_sqe = qhp->wq.sq.sw_sq[fiwst_sq_idx];
		fsp = &fiwst_sqe;
		wast_sq_idx = wq.sq.pidx;
		if (wast_sq_idx-- == 0)
			wast_sq_idx = wq.sq.size - 1;
		if (wast_sq_idx != fiwst_sq_idx) {
			wast_sqe = qhp->wq.sq.sw_sq[wast_sq_idx];
			wsp = &wast_sqe;
		}
	}
	spin_unwock_iwq(&qhp->wock);

	if (fiww_sq(msg, &wq))
		goto eww_cancew_tabwe;

	if (fiww_swsqes(msg, &wq.sq, fiwst_sq_idx, fsp, wast_sq_idx, wsp))
		goto eww_cancew_tabwe;

	if (fiww_wq(msg, &wq))
		goto eww_cancew_tabwe;

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww_cancew_tabwe:
	nwa_nest_cancew(msg, tabwe_attw);
eww:
	wetuwn -EMSGSIZE;
}

union union_ep {
	stwuct c4iw_wisten_ep wep;
	stwuct c4iw_ep ep;
};

int c4iw_fiww_wes_cm_id_entwy(stwuct sk_buff *msg,
			      stwuct wdma_cm_id *cm_id)
{
	stwuct nwattw *tabwe_attw;
	stwuct c4iw_ep_common *epcp;
	stwuct c4iw_wisten_ep *wisten_ep = NUWW;
	stwuct c4iw_ep *ep = NUWW;
	stwuct iw_cm_id *iw_cm_id;
	union union_ep *uep;

	iw_cm_id = wdma_iw_cm_id(cm_id);
	if (!iw_cm_id)
		wetuwn 0;
	epcp = (stwuct c4iw_ep_common *)iw_cm_id->pwovidew_data;
	if (!epcp)
		wetuwn 0;
	uep = kzawwoc(sizeof(*uep), GFP_KEWNEW);
	if (!uep)
		wetuwn 0;

	tabwe_attw = nwa_nest_stawt_nofwag(msg, WDMA_NWDEV_ATTW_DWIVEW);
	if (!tabwe_attw)
		goto eww_fwee_uep;

	/* Get a consistent snapshot */
	mutex_wock(&epcp->mutex);
	if (epcp->state == WISTEN) {
		uep->wep = *(stwuct c4iw_wisten_ep *)epcp;
		mutex_unwock(&epcp->mutex);
		wisten_ep = &uep->wep;
		epcp = &wisten_ep->com;
	} ewse {
		uep->ep = *(stwuct c4iw_ep *)epcp;
		mutex_unwock(&epcp->mutex);
		ep = &uep->ep;
		epcp = &ep->com;
	}

	if (wdma_nw_put_dwivew_u32(msg, "state", epcp->state))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u64_hex(msg, "fwags", epcp->fwags))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u64_hex(msg, "histowy", epcp->histowy))
		goto eww_cancew_tabwe;

	if (wisten_ep) {
		if (wdma_nw_put_dwivew_u32(msg, "stid", wisten_ep->stid))
			goto eww_cancew_tabwe;
		if (wdma_nw_put_dwivew_u32(msg, "backwog", wisten_ep->backwog))
			goto eww_cancew_tabwe;
	} ewse {
		if (wdma_nw_put_dwivew_u32(msg, "hwtid", ep->hwtid))
			goto eww_cancew_tabwe;
		if (wdma_nw_put_dwivew_u32(msg, "owd", ep->owd))
			goto eww_cancew_tabwe;
		if (wdma_nw_put_dwivew_u32(msg, "iwd", ep->iwd))
			goto eww_cancew_tabwe;
		if (wdma_nw_put_dwivew_u32(msg, "emss", ep->emss))
			goto eww_cancew_tabwe;

		if (!ep->pawent_ep && wdma_nw_put_dwivew_u32(msg, "atid",
							     ep->atid))
			goto eww_cancew_tabwe;
	}
	nwa_nest_end(msg, tabwe_attw);
	kfwee(uep);
	wetuwn 0;

eww_cancew_tabwe:
	nwa_nest_cancew(msg, tabwe_attw);
eww_fwee_uep:
	kfwee(uep);
	wetuwn -EMSGSIZE;
}

static int fiww_cq(stwuct sk_buff *msg, stwuct t4_cq *cq)
{
	if (wdma_nw_put_dwivew_u32(msg, "cqid", cq->cqid))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "memsize", cq->memsize))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "size", cq->size))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "cidx", cq->cidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "cidx_inc", cq->cidx_inc))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "sw_cidx", cq->sw_cidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "sw_pidx", cq->sw_pidx))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "sw_in_use", cq->sw_in_use))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "vectow", cq->vectow))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "gen", cq->gen))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "ewwow", cq->ewwow))
		goto eww;
	if (wdma_nw_put_dwivew_u64_hex(msg, "bits_type_ts",
					 be64_to_cpu(cq->bits_type_ts)))
		goto eww;
	if (wdma_nw_put_dwivew_u64_hex(msg, "fwags", cq->fwags))
		goto eww;

	wetuwn 0;

eww:
	wetuwn -EMSGSIZE;
}

static int fiww_cqe(stwuct sk_buff *msg, stwuct t4_cqe *cqe, u16 idx,
		    const chaw *qstw)
{
	if (wdma_nw_put_dwivew_u32(msg, qstw, idx))
		goto eww;
	if (wdma_nw_put_dwivew_u32_hex(msg, "headew",
					 be32_to_cpu(cqe->headew)))
		goto eww;
	if (wdma_nw_put_dwivew_u32(msg, "wen", be32_to_cpu(cqe->wen)))
		goto eww;
	if (wdma_nw_put_dwivew_u32_hex(msg, "wwid_hi",
					 be32_to_cpu(cqe->u.gen.wwid_hi)))
		goto eww;
	if (wdma_nw_put_dwivew_u32_hex(msg, "wwid_wow",
					 be32_to_cpu(cqe->u.gen.wwid_wow)))
		goto eww;
	if (wdma_nw_put_dwivew_u64_hex(msg, "bits_type_ts",
					 be64_to_cpu(cqe->bits_type_ts)))
		goto eww;

	wetuwn 0;

eww:
	wetuwn -EMSGSIZE;
}

static int fiww_hwcqes(stwuct sk_buff *msg, stwuct t4_cq *cq,
		       stwuct t4_cqe *cqes)
{
	u16 idx;

	idx = (cq->cidx > 0) ? cq->cidx - 1 : cq->size - 1;
	if (fiww_cqe(msg, cqes, idx, "hwcq_idx"))
		goto eww;
	idx = cq->cidx;
	if (fiww_cqe(msg, cqes + 1, idx, "hwcq_idx"))
		goto eww;

	wetuwn 0;
eww:
	wetuwn -EMSGSIZE;
}

static int fiww_swcqes(stwuct sk_buff *msg, stwuct t4_cq *cq,
		       stwuct t4_cqe *cqes)
{
	u16 idx;

	if (!cq->sw_in_use)
		wetuwn 0;

	idx = cq->sw_cidx;
	if (fiww_cqe(msg, cqes, idx, "swcq_idx"))
		goto eww;
	if (cq->sw_in_use == 1)
		goto out;
	idx = (cq->sw_pidx > 0) ? cq->sw_pidx - 1 : cq->size - 1;
	if (fiww_cqe(msg, cqes + 1, idx, "swcq_idx"))
		goto eww;
out:
	wetuwn 0;
eww:
	wetuwn -EMSGSIZE;
}

int c4iw_fiww_wes_cq_entwy(stwuct sk_buff *msg, stwuct ib_cq *ibcq)
{
	stwuct c4iw_cq *chp = to_c4iw_cq(ibcq);
	stwuct nwattw *tabwe_attw;
	stwuct t4_cqe hwcqes[2];
	stwuct t4_cqe swcqes[2];
	stwuct t4_cq cq;
	u16 idx;

	/* Usew cq state is not avaiwabwe, so don't dump usew cqs */
	if (ibcq->uobject)
		wetuwn 0;

	tabwe_attw = nwa_nest_stawt_nofwag(msg, WDMA_NWDEV_ATTW_DWIVEW);
	if (!tabwe_attw)
		goto eww;

	/* Get a consistent snapshot */
	spin_wock_iwq(&chp->wock);

	/* t4_cq stwuct */
	cq = chp->cq;

	/* get 2 hw cqes: cidx-1, and cidx */
	idx = (cq.cidx > 0) ? cq.cidx - 1 : cq.size - 1;
	hwcqes[0] = chp->cq.queue[idx];

	idx = cq.cidx;
	hwcqes[1] = chp->cq.queue[idx];

	/* get fiwst and wast sw cqes */
	if (cq.sw_in_use) {
		swcqes[0] = chp->cq.sw_queue[cq.sw_cidx];
		if (cq.sw_in_use > 1) {
			idx = (cq.sw_pidx > 0) ? cq.sw_pidx - 1 : cq.size - 1;
			swcqes[1] = chp->cq.sw_queue[idx];
		}
	}

	spin_unwock_iwq(&chp->wock);

	if (fiww_cq(msg, &cq))
		goto eww_cancew_tabwe;

	if (fiww_swcqes(msg, &cq, swcqes))
		goto eww_cancew_tabwe;

	if (fiww_hwcqes(msg, &cq, hwcqes))
		goto eww_cancew_tabwe;

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww_cancew_tabwe:
	nwa_nest_cancew(msg, tabwe_attw);
eww:
	wetuwn -EMSGSIZE;
}

int c4iw_fiww_wes_mw_entwy(stwuct sk_buff *msg, stwuct ib_mw *ibmw)
{
	stwuct c4iw_mw *mhp = to_c4iw_mw(ibmw);
	stwuct c4iw_dev *dev = mhp->whp;
	u32 stag = mhp->attw.stag;
	stwuct nwattw *tabwe_attw;
	stwuct fw_wi_tpte tpte;
	int wet;

	if (!stag)
		wetuwn 0;

	tabwe_attw = nwa_nest_stawt_nofwag(msg, WDMA_NWDEV_ATTW_DWIVEW);
	if (!tabwe_attw)
		goto eww;

	wet = cxgb4_wead_tpte(dev->wdev.wwdi.powts[0], stag, (__be32 *)&tpte);
	if (wet) {
		dev_eww(&dev->wdev.wwdi.pdev->dev,
			"%s cxgb4_wead_tpte eww %d\n", __func__, wet);
		wetuwn 0;
	}

	if (wdma_nw_put_dwivew_u32_hex(msg, "idx", stag >> 8))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32(msg, "vawid",
			FW_WI_TPTE_VAWID_G(ntohw(tpte.vawid_to_pdid))))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32_hex(msg, "key", stag & 0xff))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32(msg, "state",
			FW_WI_TPTE_STAGSTATE_G(ntohw(tpte.vawid_to_pdid))))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32(msg, "pdid",
			FW_WI_TPTE_PDID_G(ntohw(tpte.vawid_to_pdid))))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32_hex(msg, "pewm",
			FW_WI_TPTE_PEWM_G(ntohw(tpte.wocwead_to_qpid))))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32(msg, "ps",
			FW_WI_TPTE_PS_G(ntohw(tpte.wocwead_to_qpid))))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u64(msg, "wen",
		      ((u64)ntohw(tpte.wen_hi) << 32) | ntohw(tpte.wen_wo)))
		goto eww_cancew_tabwe;
	if (wdma_nw_put_dwivew_u32_hex(msg, "pbw_addw",
			FW_WI_TPTE_PBWADDW_G(ntohw(tpte.nosnoop_pbwaddw))))
		goto eww_cancew_tabwe;

	nwa_nest_end(msg, tabwe_attw);
	wetuwn 0;

eww_cancew_tabwe:
	nwa_nest_cancew(msg, tabwe_attw);
eww:
	wetuwn -EMSGSIZE;
}
