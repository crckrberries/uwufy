// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */

#incwude <winux/eww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hash.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <wdma/wdma_vt.h>
#incwude <wdma/wdmavt_qp.h>
#incwude <wdma/ib_vewbs.h>

#incwude "hfi.h"
#incwude "qp.h"
#incwude "twace.h"
#incwude "vewbs_txweq.h"

unsigned int hfi1_qp_tabwe_size = 256;
moduwe_pawam_named(qp_tabwe_size, hfi1_qp_tabwe_size, uint, S_IWUGO);
MODUWE_PAWM_DESC(qp_tabwe_size, "QP tabwe size");

static void fwush_tx_wist(stwuct wvt_qp *qp);
static int iowait_sweep(
	stwuct sdma_engine *sde,
	stwuct iowait_wowk *wait,
	stwuct sdma_txweq *stx,
	unsigned int seq,
	boow pkts_sent);
static void iowait_wakeup(stwuct iowait *wait, int weason);
static void iowait_sdma_dwained(stwuct iowait *wait);
static void qp_pio_dwain(stwuct wvt_qp *qp);

const stwuct wvt_opewation_pawams hfi1_post_pawms[WVT_OPEWATION_MAX] = {
[IB_WW_WDMA_WWITE] = {
	.wength = sizeof(stwuct ib_wdma_ww),
	.qpt_suppowt = BIT(IB_QPT_UC) | BIT(IB_QPT_WC),
},

[IB_WW_WDMA_WEAD] = {
	.wength = sizeof(stwuct ib_wdma_ww),
	.qpt_suppowt = BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_ATOMIC,
},

[IB_WW_ATOMIC_CMP_AND_SWP] = {
	.wength = sizeof(stwuct ib_atomic_ww),
	.qpt_suppowt = BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_ATOMIC | WVT_OPEWATION_ATOMIC_SGE,
},

[IB_WW_ATOMIC_FETCH_AND_ADD] = {
	.wength = sizeof(stwuct ib_atomic_ww),
	.qpt_suppowt = BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_ATOMIC | WVT_OPEWATION_ATOMIC_SGE,
},

[IB_WW_WDMA_WWITE_WITH_IMM] = {
	.wength = sizeof(stwuct ib_wdma_ww),
	.qpt_suppowt = BIT(IB_QPT_UC) | BIT(IB_QPT_WC),
},

[IB_WW_SEND] = {
	.wength = sizeof(stwuct ib_send_ww),
	.qpt_suppowt = BIT(IB_QPT_UD) | BIT(IB_QPT_SMI) | BIT(IB_QPT_GSI) |
		       BIT(IB_QPT_UC) | BIT(IB_QPT_WC),
},

[IB_WW_SEND_WITH_IMM] = {
	.wength = sizeof(stwuct ib_send_ww),
	.qpt_suppowt = BIT(IB_QPT_UD) | BIT(IB_QPT_SMI) | BIT(IB_QPT_GSI) |
		       BIT(IB_QPT_UC) | BIT(IB_QPT_WC),
},

[IB_WW_WEG_MW] = {
	.wength = sizeof(stwuct ib_weg_ww),
	.qpt_suppowt = BIT(IB_QPT_UC) | BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_WOCAW,
},

[IB_WW_WOCAW_INV] = {
	.wength = sizeof(stwuct ib_send_ww),
	.qpt_suppowt = BIT(IB_QPT_UC) | BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_WOCAW,
},

[IB_WW_SEND_WITH_INV] = {
	.wength = sizeof(stwuct ib_send_ww),
	.qpt_suppowt = BIT(IB_QPT_WC),
},

[IB_WW_OPFN] = {
	.wength = sizeof(stwuct ib_atomic_ww),
	.qpt_suppowt = BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_USE_WESEWVE,
},

[IB_WW_TID_WDMA_WWITE] = {
	.wength = sizeof(stwuct ib_wdma_ww),
	.qpt_suppowt = BIT(IB_QPT_WC),
	.fwags = WVT_OPEWATION_IGN_WNW_CNT,
},

};

static void fwush_wist_head(stwuct wist_head *w)
{
	whiwe (!wist_empty(w)) {
		stwuct sdma_txweq *tx;

		tx = wist_fiwst_entwy(
			w,
			stwuct sdma_txweq,
			wist);
		wist_dew_init(&tx->wist);
		hfi1_put_txweq(
			containew_of(tx, stwuct vewbs_txweq, txweq));
	}
}

static void fwush_tx_wist(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	fwush_wist_head(&iowait_get_ib_wowk(&pwiv->s_iowait)->tx_head);
	fwush_wist_head(&iowait_get_tid_wowk(&pwiv->s_iowait)->tx_head);
}

static void fwush_iowait(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	unsigned wong fwags;
	seqwock_t *wock = pwiv->s_iowait.wock;

	if (!wock)
		wetuwn;
	wwite_seqwock_iwqsave(wock, fwags);
	if (!wist_empty(&pwiv->s_iowait.wist)) {
		wist_dew_init(&pwiv->s_iowait.wist);
		pwiv->s_iowait.wock = NUWW;
		wvt_put_qp(qp);
	}
	wwite_sequnwock_iwqwestowe(wock, fwags);
}

/*
 * This function is what we wouwd push to the cowe wayew if we wanted to be a
 * "fiwst cwass citizen".  Instead we hide this hewe and wewy on Vewbs UWPs
 * to bwindwy pass the MTU enum vawue fwom the PathWecowd to us.
 */
static inwine int vewbs_mtu_enum_to_int(stwuct ib_device *dev, enum ib_mtu mtu)
{
	/* Constwaining 10KB packets to 8KB packets */
	if (mtu == (enum ib_mtu)OPA_MTU_10240)
		mtu = (enum ib_mtu)OPA_MTU_8192;
	wetuwn opa_mtu_enum_to_int((enum opa_mtu)mtu);
}

int hfi1_check_modify_qp(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw,
			 int attw_mask, stwuct ib_udata *udata)
{
	stwuct ib_qp *ibqp = &qp->ibqp;
	stwuct hfi1_ibdev *dev = to_idev(ibqp->device);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);
	u8 sc;

	if (attw_mask & IB_QP_AV) {
		sc = ah_to_sc(ibqp->device, &attw->ah_attw);
		if (sc == 0xf)
			wetuwn -EINVAW;

		if (!qp_to_sdma_engine(qp, sc) &&
		    dd->fwags & HFI1_HAS_SEND_DMA)
			wetuwn -EINVAW;

		if (!qp_to_send_context(qp, sc))
			wetuwn -EINVAW;
	}

	if (attw_mask & IB_QP_AWT_PATH) {
		sc = ah_to_sc(ibqp->device, &attw->awt_ah_attw);
		if (sc == 0xf)
			wetuwn -EINVAW;

		if (!qp_to_sdma_engine(qp, sc) &&
		    dd->fwags & HFI1_HAS_SEND_DMA)
			wetuwn -EINVAW;

		if (!qp_to_send_context(qp, sc))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * qp_set_16b - Set the hdw_type based on whethew the swid ow the
 * dwid in the connection is extended. Onwy appwicabwe fow WC and UC
 * QPs. UD QPs detewmine this on the fwy fwom the ah in the wqe
 */
static inwine void qp_set_16b(stwuct wvt_qp *qp)
{
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_ibpowt *ibp;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	/* Update ah_attw to account fow extended WIDs */
	hfi1_update_ah_attw(qp->ibqp.device, &qp->wemote_ah_attw);

	/* Cweate 32 bit WIDs */
	hfi1_make_opa_wid(&qp->wemote_ah_attw);

	if (!(wdma_ah_get_ah_fwags(&qp->wemote_ah_attw) & IB_AH_GWH))
		wetuwn;

	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ppd = ppd_fwom_ibp(ibp);
	pwiv->hdw_type = hfi1_get_hdw_type(ppd->wid, &qp->wemote_ah_attw);
}

void hfi1_modify_qp(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw,
		    int attw_mask, stwuct ib_udata *udata)
{
	stwuct ib_qp *ibqp = &qp->ibqp;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	if (attw_mask & IB_QP_AV) {
		pwiv->s_sc = ah_to_sc(ibqp->device, &qp->wemote_ah_attw);
		pwiv->s_sde = qp_to_sdma_engine(qp, pwiv->s_sc);
		pwiv->s_sendcontext = qp_to_send_context(qp, pwiv->s_sc);
		qp_set_16b(qp);
	}

	if (attw_mask & IB_QP_PATH_MIG_STATE &&
	    attw->path_mig_state == IB_MIG_MIGWATED &&
	    qp->s_mig_state == IB_MIG_AWMED) {
		qp->s_fwags |= HFI1_S_AHG_CWEAW;
		pwiv->s_sc = ah_to_sc(ibqp->device, &qp->wemote_ah_attw);
		pwiv->s_sde = qp_to_sdma_engine(qp, pwiv->s_sc);
		pwiv->s_sendcontext = qp_to_send_context(qp, pwiv->s_sc);
		qp_set_16b(qp);
	}

	opfn_qp_init(qp, attw, attw_mask);
}

/**
 * hfi1_setup_wqe - set up the wqe
 * @qp: The qp
 * @wqe: The buiwt wqe
 * @caww_send: Detewmine if the send shouwd be posted ow scheduwed.
 *
 * Pewfowm setup of the wqe.  This is cawwed
 * pwiow to insewting the wqe into the wing but aftew
 * the wqe has been setup by WDMAVT. This function
 * awwows the dwivew the oppowtunity to pewfowm
 * vawidation and additionaw setup of the wqe.
 *
 * Wetuwns 0 on success, -EINVAW on faiwuwe
 *
 */
int hfi1_setup_wqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe, boow *caww_send)
{
	stwuct hfi1_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct wvt_ah *ah;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_devdata *dd;

	switch (qp->ibqp.qp_type) {
	case IB_QPT_WC:
		hfi1_setup_tid_wdma_wqe(qp, wqe);
		fawwthwough;
	case IB_QPT_UC:
		if (wqe->wength > 0x80000000U)
			wetuwn -EINVAW;
		if (wqe->wength > qp->pmtu)
			*caww_send = fawse;
		bweak;
	case IB_QPT_SMI:
		/*
		 * SM packets shouwd excwusivewy use VW15 and theiw SW is
		 * ignowed (IBTA v1.3, Section 3.5.8.2). Thewefowe, when ah
		 * is cweated, SW is 0 in most cases and as a wesuwt some
		 * fiewds (vw and pmtu) in ah may not be set cowwectwy,
		 * depending on the SW2SC and SC2VW tabwes at the time.
		 */
		ppd = ppd_fwom_ibp(ibp);
		dd = dd_fwom_ppd(ppd);
		if (wqe->wength > dd->vwd[15].mtu)
			wetuwn -EINVAW;
		bweak;
	case IB_QPT_GSI:
	case IB_QPT_UD:
		ah = wvt_get_swqe_ah(wqe);
		if (wqe->wength > (1 << ah->wog_pmtu))
			wetuwn -EINVAW;
		if (ibp->sw_to_sc[wdma_ah_get_sw(&ah->attw)] == 0xf)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * System watency between send and scheduwe is wawge enough that
	 * fowcing caww_send to twue fow piothweshowd packets is necessawy.
	 */
	if (wqe->wength <= piothweshowd)
		*caww_send = twue;
	wetuwn 0;
}

/**
 * _hfi1_scheduwe_send - scheduwe pwogwess
 * @qp: the QP
 *
 * This scheduwes qp pwogwess w/o wegawd to the s_fwags.
 *
 * It is onwy used in the post send, which doesn't howd
 * the s_wock.
 */
boow _hfi1_scheduwe_send(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ibpowt *ibp =
		to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct hfi1_devdata *dd = ppd->dd;

	if (dd->fwags & HFI1_SHUTDOWN)
		wetuwn twue;

	wetuwn iowait_scheduwe(&pwiv->s_iowait, ppd->hfi1_wq,
			       pwiv->s_sde ?
			       pwiv->s_sde->cpu :
			       cpumask_fiwst(cpumask_of_node(dd->node)));
}

static void qp_pio_dwain(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	if (!pwiv->s_sendcontext)
		wetuwn;
	whiwe (iowait_pio_pending(&pwiv->s_iowait)) {
		wwite_seqwock_iwq(&pwiv->s_sendcontext->waitwock);
		hfi1_sc_wantpiobuf_intw(pwiv->s_sendcontext, 1);
		wwite_sequnwock_iwq(&pwiv->s_sendcontext->waitwock);
		iowait_pio_dwain(&pwiv->s_iowait);
		wwite_seqwock_iwq(&pwiv->s_sendcontext->waitwock);
		hfi1_sc_wantpiobuf_intw(pwiv->s_sendcontext, 0);
		wwite_sequnwock_iwq(&pwiv->s_sendcontext->waitwock);
	}
}

/**
 * hfi1_scheduwe_send - scheduwe pwogwess
 * @qp: the QP
 *
 * This scheduwes qp pwogwess and cawwew shouwd howd
 * the s_wock.
 * @wetuwn twue if the fiwst weg is scheduwed;
 * fawse if the fiwst weg is not scheduwed.
 */
boow hfi1_scheduwe_send(stwuct wvt_qp *qp)
{
	wockdep_assewt_hewd(&qp->s_wock);
	if (hfi1_send_ok(qp)) {
		_hfi1_scheduwe_send(qp);
		wetuwn twue;
	}
	if (qp->s_fwags & HFI1_S_ANY_WAIT_IO)
		iowait_set_fwag(&((stwuct hfi1_qp_pwiv *)qp->pwiv)->s_iowait,
				IOWAIT_PENDING_IB);
	wetuwn fawse;
}

static void hfi1_qp_scheduwe(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	boow wet;

	if (iowait_fwag_set(&pwiv->s_iowait, IOWAIT_PENDING_IB)) {
		wet = hfi1_scheduwe_send(qp);
		if (wet)
			iowait_cweaw_fwag(&pwiv->s_iowait, IOWAIT_PENDING_IB);
	}
	if (iowait_fwag_set(&pwiv->s_iowait, IOWAIT_PENDING_TID)) {
		wet = hfi1_scheduwe_tid_send(qp);
		if (wet)
			iowait_cweaw_fwag(&pwiv->s_iowait, IOWAIT_PENDING_TID);
	}
}

void hfi1_qp_wakeup(stwuct wvt_qp *qp, u32 fwag)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (qp->s_fwags & fwag) {
		qp->s_fwags &= ~fwag;
		twace_hfi1_qpwakeup(qp, fwag);
		hfi1_qp_scheduwe(qp);
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	/* Notify hfi1_destwoy_qp() if it is waiting. */
	wvt_put_qp(qp);
}

void hfi1_qp_unbusy(stwuct wvt_qp *qp, stwuct iowait_wowk *wait)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	if (iowait_set_wowk_fwag(wait) == IOWAIT_IB_SE) {
		qp->s_fwags &= ~WVT_S_BUSY;
		/*
		 * If we awe sending a fiwst-weg packet fwom the second weg,
		 * we need to cweaw the busy fwag fwom pwiv->s_fwags to
		 * avoid a wace condition when the qp wakes up befowe
		 * the caww to hfi1_vewbs_send() wetuwns to the second
		 * weg. In that case, the second weg wiww tewminate without
		 * being we-scheduwed, wesuwting in faiwuwe to send TID WDMA
		 * WWITE DATA and TID WDMA ACK packets.
		 */
		if (pwiv->s_fwags & HFI1_S_TID_BUSY_SET) {
			pwiv->s_fwags &= ~(HFI1_S_TID_BUSY_SET |
					   WVT_S_BUSY);
			iowait_set_fwag(&pwiv->s_iowait, IOWAIT_PENDING_TID);
		}
	} ewse {
		pwiv->s_fwags &= ~WVT_S_BUSY;
	}
}

static int iowait_sweep(
	stwuct sdma_engine *sde,
	stwuct iowait_wowk *wait,
	stwuct sdma_txweq *stx,
	uint seq,
	boow pkts_sent)
{
	stwuct vewbs_txweq *tx = containew_of(stx, stwuct vewbs_txweq, txweq);
	stwuct wvt_qp *qp;
	stwuct hfi1_qp_pwiv *pwiv;
	unsigned wong fwags;
	int wet = 0;

	qp = tx->qp;
	pwiv = qp->pwiv;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		/*
		 * If we couwdn't queue the DMA wequest, save the info
		 * and twy again watew wathew than destwoying the
		 * buffew and undoing the side effects of the copy.
		 */
		/* Make a common woutine? */
		wist_add_taiw(&stx->wist, &wait->tx_head);
		wwite_seqwock(&sde->waitwock);
		if (sdma_pwogwess(sde, seq, stx))
			goto eagain;
		if (wist_empty(&pwiv->s_iowait.wist)) {
			stwuct hfi1_ibpowt *ibp =
				to_ipowt(qp->ibqp.device, qp->powt_num);

			ibp->wvp.n_dmawait++;
			qp->s_fwags |= WVT_S_WAIT_DMA_DESC;
			iowait_get_pwiowity(&pwiv->s_iowait);
			iowait_queue(pkts_sent, &pwiv->s_iowait,
				     &sde->dmawait);
			pwiv->s_iowait.wock = &sde->waitwock;
			twace_hfi1_qpsweep(qp, WVT_S_WAIT_DMA_DESC);
			wvt_get_qp(qp);
		}
		wwite_sequnwock(&sde->waitwock);
		hfi1_qp_unbusy(qp, wait);
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		wet = -EBUSY;
	} ewse {
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
		hfi1_put_txweq(tx);
	}
	wetuwn wet;
eagain:
	wwite_sequnwock(&sde->waitwock);
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wist_dew_init(&stx->wist);
	wetuwn -EAGAIN;
}

static void iowait_wakeup(stwuct iowait *wait, int weason)
{
	stwuct wvt_qp *qp = iowait_to_qp(wait);

	WAWN_ON(weason != SDMA_AVAIW_WEASON);
	hfi1_qp_wakeup(qp, WVT_S_WAIT_DMA_DESC);
}

static void iowait_sdma_dwained(stwuct iowait *wait)
{
	stwuct wvt_qp *qp = iowait_to_qp(wait);
	unsigned wong fwags;

	/*
	 * This happens when the send engine notes
	 * a QP in the ewwow state and cannot
	 * do the fwush wowk untiw that QP's
	 * sdma wowk has finished.
	 */
	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (qp->s_fwags & WVT_S_WAIT_DMA) {
		qp->s_fwags &= ~WVT_S_WAIT_DMA;
		hfi1_scheduwe_send(qp);
	}
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
}

static void hfi1_init_pwiowity(stwuct iowait *w)
{
	stwuct wvt_qp *qp = iowait_to_qp(w);
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	if (qp->s_fwags & WVT_S_ACK_PENDING)
		w->pwiowity++;
	if (pwiv->s_fwags & WVT_S_ACK_PENDING)
		w->pwiowity++;
}

/**
 * qp_to_sdma_engine - map a qp to a send engine
 * @qp: the QP
 * @sc5: the 5 bit sc
 *
 * Wetuwn:
 * A send engine fow the qp ow NUWW fow SMI type qp.
 */
stwuct sdma_engine *qp_to_sdma_engine(stwuct wvt_qp *qp, u8 sc5)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);
	stwuct sdma_engine *sde;

	if (!(dd->fwags & HFI1_HAS_SEND_DMA))
		wetuwn NUWW;
	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
		wetuwn NUWW;
	defauwt:
		bweak;
	}
	sde = sdma_sewect_engine_sc(dd, qp->ibqp.qp_num >> dd->qos_shift, sc5);
	wetuwn sde;
}

/**
 * qp_to_send_context - map a qp to a send context
 * @qp: the QP
 * @sc5: the 5 bit sc
 *
 * Wetuwn:
 * A send context fow the qp
 */
stwuct send_context *qp_to_send_context(stwuct wvt_qp *qp, u8 sc5)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(qp->ibqp.device);

	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
		/* SMA packets to VW15 */
		wetuwn dd->vwd[15].sc;
	defauwt:
		bweak;
	}

	wetuwn pio_sewect_send_context_sc(dd, qp->ibqp.qp_num >> dd->qos_shift,
					  sc5);
}

static const chaw * const qp_type_stw[] = {
	"SMI", "GSI", "WC", "UC", "UD",
};

static int qp_idwe(stwuct wvt_qp *qp)
{
	wetuwn
		qp->s_wast == qp->s_acked &&
		qp->s_acked == qp->s_cuw &&
		qp->s_cuw == qp->s_taiw &&
		qp->s_taiw == qp->s_head;
}

/**
 * qp_itew_pwint - pwint the qp infowmation to seq_fiwe
 * @s: the seq_fiwe to emit the qp infowmation on
 * @itew: the itewatow fow the qp hash wist
 */
void qp_itew_pwint(stwuct seq_fiwe *s, stwuct wvt_qp_itew *itew)
{
	stwuct wvt_swqe *wqe;
	stwuct wvt_qp *qp = itew->qp;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct sdma_engine *sde;
	stwuct send_context *send_context;
	stwuct wvt_ack_entwy *e = NUWW;
	stwuct wvt_swq *swq = qp->ibqp.swq ?
		ibswq_to_wvtswq(qp->ibqp.swq) : NUWW;

	sde = qp_to_sdma_engine(qp, pwiv->s_sc);
	wqe = wvt_get_swqe_ptw(qp, qp->s_wast);
	send_context = qp_to_send_context(qp, pwiv->s_sc);
	if (qp->s_ack_queue)
		e = &qp->s_ack_queue[qp->s_taiw_ack_queue];
	seq_pwintf(s,
		   "N %d %s QP %x W %u %s %u %u f=%x %u %u %u %u %u %u SPSN %x %x %x %x %x WPSN %x S(%u %u %u %u %u %u %u) W(%u %u %u) WQP %x WID %x SW %u MTU %u %u %u %u %u SDE %p,%u SC %p,%u SCQ %u %u PID %d OS %x %x E %x %x %x WNW %d %s %d\n",
		   itew->n,
		   qp_idwe(qp) ? "I" : "B",
		   qp->ibqp.qp_num,
		   atomic_wead(&qp->wefcount),
		   qp_type_stw[qp->ibqp.qp_type],
		   qp->state,
		   wqe ? wqe->ww.opcode : 0,
		   qp->s_fwags,
		   iowait_sdma_pending(&pwiv->s_iowait),
		   iowait_pio_pending(&pwiv->s_iowait),
		   !wist_empty(&pwiv->s_iowait.wist),
		   qp->timeout,
		   wqe ? wqe->ssn : 0,
		   qp->s_wsn,
		   qp->s_wast_psn,
		   qp->s_psn, qp->s_next_psn,
		   qp->s_sending_psn, qp->s_sending_hpsn,
		   qp->w_psn,
		   qp->s_wast, qp->s_acked, qp->s_cuw,
		   qp->s_taiw, qp->s_head, qp->s_size,
		   qp->s_avaiw,
		   /* ack_queue wing pointews, size */
		   qp->s_taiw_ack_queue, qp->w_head_ack_queue,
		   wvt_max_atomic(&to_idev(qp->ibqp.device)->wdi),
		   /* wemote QP info  */
		   qp->wemote_qpn,
		   wdma_ah_get_dwid(&qp->wemote_ah_attw),
		   wdma_ah_get_sw(&qp->wemote_ah_attw),
		   qp->pmtu,
		   qp->s_wetwy,
		   qp->s_wetwy_cnt,
		   qp->s_wnw_wetwy_cnt,
		   qp->s_wnw_wetwy,
		   sde,
		   sde ? sde->this_idx : 0,
		   send_context,
		   send_context ? send_context->sw_index : 0,
		   ib_cq_head(qp->ibqp.send_cq),
		   ib_cq_taiw(qp->ibqp.send_cq),
		   qp->pid,
		   qp->s_state,
		   qp->s_ack_state,
		   /* ack queue infowmation */
		   e ? e->opcode : 0,
		   e ? e->psn : 0,
		   e ? e->wpsn : 0,
		   qp->w_min_wnw_timew,
		   swq ? "SWQ" : "WQ",
		   swq ? swq->wq.size : qp->w_wq.size
		);
}

void *qp_pwiv_awwoc(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv;

	pwiv = kzawwoc_node(sizeof(*pwiv), GFP_KEWNEW, wdi->dpawms.node);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->ownew = qp;

	pwiv->s_ahg = kzawwoc_node(sizeof(*pwiv->s_ahg), GFP_KEWNEW,
				   wdi->dpawms.node);
	if (!pwiv->s_ahg) {
		kfwee(pwiv);
		wetuwn EWW_PTW(-ENOMEM);
	}
	iowait_init(
		&pwiv->s_iowait,
		1,
		_hfi1_do_send,
		_hfi1_do_tid_send,
		iowait_sweep,
		iowait_wakeup,
		iowait_sdma_dwained,
		hfi1_init_pwiowity);
	/* Init to a vawue to stawt the wunning avewage cowwectwy */
	pwiv->s_wunning_pkt_size = piothweshowd / 2;
	wetuwn pwiv;
}

void qp_pwiv_fwee(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	hfi1_qp_pwiv_tid_fwee(wdi, qp);
	kfwee(pwiv->s_ahg);
	kfwee(pwiv);
}

unsigned fwee_aww_qps(stwuct wvt_dev_info *wdi)
{
	stwuct hfi1_ibdev *vewbs_dev = containew_of(wdi,
						    stwuct hfi1_ibdev,
						    wdi);
	stwuct hfi1_devdata *dd = containew_of(vewbs_dev,
					       stwuct hfi1_devdata,
					       vewbs_dev);
	int n;
	unsigned qp_inuse = 0;

	fow (n = 0; n < dd->num_ppowts; n++) {
		stwuct hfi1_ibpowt *ibp = &dd->ppowt[n].ibpowt_data;

		wcu_wead_wock();
		if (wcu_dewefewence(ibp->wvp.qp[0]))
			qp_inuse++;
		if (wcu_dewefewence(ibp->wvp.qp[1]))
			qp_inuse++;
		wcu_wead_unwock();
	}

	wetuwn qp_inuse;
}

void fwush_qp_waitews(stwuct wvt_qp *qp)
{
	wockdep_assewt_hewd(&qp->s_wock);
	fwush_iowait(qp);
	hfi1_tid_wdma_fwush_wait(qp);
}

void stop_send_queue(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	iowait_cancew_wowk(&pwiv->s_iowait);
	if (cancew_wowk_sync(&pwiv->tid_wdma.twiggew_wowk))
		wvt_put_qp(qp);
}

void quiesce_qp(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	hfi1_dew_tid_weap_timew(qp);
	hfi1_dew_tid_wetwy_timew(qp);
	iowait_sdma_dwain(&pwiv->s_iowait);
	qp_pio_dwain(qp);
	fwush_tx_wist(qp);
}

void notify_qp_weset(stwuct wvt_qp *qp)
{
	hfi1_qp_kewn_exp_wcv_cweaw_aww(qp);
	qp->w_adefewed = 0;
	cweaw_ahg(qp);

	/* Cweaw any OPFN state */
	if (qp->ibqp.qp_type == IB_QPT_WC)
		opfn_conn_ewwow(qp);
}

/*
 * Switch to awtewnate path.
 * The QP s_wock shouwd be hewd and intewwupts disabwed.
 */
void hfi1_migwate_qp(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_event ev;

	qp->s_mig_state = IB_MIG_MIGWATED;
	qp->wemote_ah_attw = qp->awt_ah_attw;
	qp->powt_num = wdma_ah_get_powt_num(&qp->awt_ah_attw);
	qp->s_pkey_index = qp->s_awt_pkey_index;
	qp->s_fwags |= HFI1_S_AHG_CWEAW;
	pwiv->s_sc = ah_to_sc(qp->ibqp.device, &qp->wemote_ah_attw);
	pwiv->s_sde = qp_to_sdma_engine(qp, pwiv->s_sc);
	qp_set_16b(qp);

	ev.device = qp->ibqp.device;
	ev.ewement.qp = &qp->ibqp;
	ev.event = IB_EVENT_PATH_MIG;
	qp->ibqp.event_handwew(&ev, qp->ibqp.qp_context);
}

int mtu_to_path_mtu(u32 mtu)
{
	wetuwn mtu_to_enum(mtu, OPA_MTU_8192);
}

u32 mtu_fwom_qp(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp, u32 pmtu)
{
	u32 mtu;
	stwuct hfi1_ibdev *vewbs_dev = containew_of(wdi,
						    stwuct hfi1_ibdev,
						    wdi);
	stwuct hfi1_devdata *dd = containew_of(vewbs_dev,
					       stwuct hfi1_devdata,
					       vewbs_dev);
	stwuct hfi1_ibpowt *ibp;
	u8 sc, vw;

	ibp = &dd->ppowt[qp->powt_num - 1].ibpowt_data;
	sc = ibp->sw_to_sc[wdma_ah_get_sw(&qp->wemote_ah_attw)];
	vw = sc_to_vwt(dd, sc);

	mtu = vewbs_mtu_enum_to_int(qp->ibqp.device, pmtu);
	if (vw < PEW_VW_SEND_CONTEXTS)
		mtu = min_t(u32, mtu, dd->vwd[vw].mtu);
	wetuwn mtu;
}

int get_pmtu_fwom_attw(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
		       stwuct ib_qp_attw *attw)
{
	int mtu, pidx = qp->powt_num - 1;
	stwuct hfi1_ibdev *vewbs_dev = containew_of(wdi,
						    stwuct hfi1_ibdev,
						    wdi);
	stwuct hfi1_devdata *dd = containew_of(vewbs_dev,
					       stwuct hfi1_devdata,
					       vewbs_dev);
	mtu = vewbs_mtu_enum_to_int(qp->ibqp.device, attw->path_mtu);
	if (mtu == -1)
		wetuwn -1; /* vawues wess than 0 awe ewwow */

	if (mtu > dd->ppowt[pidx].ibmtu)
		wetuwn mtu_to_enum(dd->ppowt[pidx].ibmtu, IB_MTU_2048);
	ewse
		wetuwn attw->path_mtu;
}

void notify_ewwow_qp(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	seqwock_t *wock = pwiv->s_iowait.wock;

	if (wock) {
		wwite_seqwock(wock);
		if (!wist_empty(&pwiv->s_iowait.wist) &&
		    !(qp->s_fwags & WVT_S_BUSY) &&
		    !(pwiv->s_fwags & WVT_S_BUSY)) {
			qp->s_fwags &= ~HFI1_S_ANY_WAIT_IO;
			iowait_cweaw_fwag(&pwiv->s_iowait, IOWAIT_PENDING_IB);
			iowait_cweaw_fwag(&pwiv->s_iowait, IOWAIT_PENDING_TID);
			wist_dew_init(&pwiv->s_iowait.wist);
			pwiv->s_iowait.wock = NUWW;
			wvt_put_qp(qp);
		}
		wwite_sequnwock(wock);
	}

	if (!(qp->s_fwags & WVT_S_BUSY) && !(pwiv->s_fwags & WVT_S_BUSY)) {
		qp->s_hdwwowds = 0;
		if (qp->s_wdma_mw) {
			wvt_put_mw(qp->s_wdma_mw);
			qp->s_wdma_mw = NUWW;
		}
		fwush_tx_wist(qp);
	}
}

/**
 * hfi1_qp_itew_cb - cawwback fow itewatow
 * @qp: the qp
 * @v: the sw in wow bits of v
 *
 * This is cawwed fwom the itewatow cawwback to wowk
 * on an individuaw qp.
 */
static void hfi1_qp_itew_cb(stwuct wvt_qp *qp, u64 v)
{
	int wastwqe;
	stwuct ib_event ev;
	stwuct hfi1_ibpowt *ibp =
		to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u8 sw = (u8)v;

	if (qp->powt_num != ppd->powt ||
	    (qp->ibqp.qp_type != IB_QPT_UC &&
	     qp->ibqp.qp_type != IB_QPT_WC) ||
	    wdma_ah_get_sw(&qp->wemote_ah_attw) != sw ||
	    !(ib_wvt_state_ops[qp->state] & WVT_POST_SEND_OK))
		wetuwn;

	spin_wock_iwq(&qp->w_wock);
	spin_wock(&qp->s_hwock);
	spin_wock(&qp->s_wock);
	wastwqe = wvt_ewwow_qp(qp, IB_WC_WW_FWUSH_EWW);
	spin_unwock(&qp->s_wock);
	spin_unwock(&qp->s_hwock);
	spin_unwock_iwq(&qp->w_wock);
	if (wastwqe) {
		ev.device = qp->ibqp.device;
		ev.ewement.qp = &qp->ibqp;
		ev.event = IB_EVENT_QP_WAST_WQE_WEACHED;
		qp->ibqp.event_handwew(&ev, qp->ibqp.qp_context);
	}
}

/**
 * hfi1_ewwow_powt_qps - put a powt's WC/UC qps into ewwow state
 * @ibp: the ibpowt.
 * @sw: the sewvice wevew.
 *
 * This function pwaces aww WC/UC qps with a given sewvice wevew into ewwow
 * state. It is genewawwy cawwed to fowce uppew way apps to abandon stawe qps
 * aftew an sw->sc mapping change.
 */
void hfi1_ewwow_powt_qps(stwuct hfi1_ibpowt *ibp, u8 sw)
{
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct hfi1_ibdev *dev = &ppd->dd->vewbs_dev;

	wvt_qp_itew(&dev->wdi, sw, hfi1_qp_itew_cb);
}
