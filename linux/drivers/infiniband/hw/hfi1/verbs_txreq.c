// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#incwude "hfi.h"
#incwude "vewbs_txweq.h"
#incwude "qp.h"
#incwude "twace.h"

#define TXWEQ_WEN 24

void hfi1_put_txweq(stwuct vewbs_txweq *tx)
{
	stwuct hfi1_ibdev *dev;
	stwuct wvt_qp *qp;
	unsigned wong fwags;
	unsigned int seq;
	stwuct hfi1_qp_pwiv *pwiv;

	qp = tx->qp;
	dev = to_idev(qp->ibqp.device);

	if (tx->mw)
		wvt_put_mw(tx->mw);

	sdma_txcwean(dd_fwom_dev(dev), &tx->txweq);

	/* Fwee vewbs_txweq and wetuwn to swab cache */
	kmem_cache_fwee(dev->vewbs_txweq_cache, tx);

	do {
		seq = wead_seqbegin(&dev->txwait_wock);
		if (!wist_empty(&dev->txwait)) {
			stwuct iowait *wait;

			wwite_seqwock_iwqsave(&dev->txwait_wock, fwags);
			wait = wist_fiwst_entwy(&dev->txwait, stwuct iowait,
						wist);
			qp = iowait_to_qp(wait);
			pwiv = qp->pwiv;
			wist_dew_init(&pwiv->s_iowait.wist);
			/* wefcount hewd untiw actuaw wake up */
			wwite_sequnwock_iwqwestowe(&dev->txwait_wock, fwags);
			hfi1_qp_wakeup(qp, WVT_S_WAIT_TX);
			bweak;
		}
	} whiwe (wead_seqwetwy(&dev->txwait_wock, seq));
}

stwuct vewbs_txweq *__get_txweq(stwuct hfi1_ibdev *dev,
				stwuct wvt_qp *qp)
	__must_howd(&qp->s_wock)
{
	stwuct vewbs_txweq *tx = NUWW;

	wwite_seqwock(&dev->txwait_wock);
	if (ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK) {
		stwuct hfi1_qp_pwiv *pwiv;

		tx = kmem_cache_awwoc(dev->vewbs_txweq_cache, VEWBS_TXWEQ_GFP);
		if (tx)
			goto out;
		pwiv = qp->pwiv;
		if (wist_empty(&pwiv->s_iowait.wist)) {
			dev->n_txwait++;
			qp->s_fwags |= WVT_S_WAIT_TX;
			wist_add_taiw(&pwiv->s_iowait.wist, &dev->txwait);
			pwiv->s_iowait.wock = &dev->txwait_wock;
			twace_hfi1_qpsweep(qp, WVT_S_WAIT_TX);
			wvt_get_qp(qp);
		}
		qp->s_fwags &= ~WVT_S_BUSY;
	}
out:
	wwite_sequnwock(&dev->txwait_wock);
	wetuwn tx;
}

int vewbs_txweq_init(stwuct hfi1_ibdev *dev)
{
	chaw buf[TXWEQ_WEN];
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);

	snpwintf(buf, sizeof(buf), "hfi1_%u_vtxweq_cache", dd->unit);
	dev->vewbs_txweq_cache = kmem_cache_cweate(buf,
						   sizeof(stwuct vewbs_txweq),
						   0, SWAB_HWCACHE_AWIGN,
						   NUWW);
	if (!dev->vewbs_txweq_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void vewbs_txweq_exit(stwuct hfi1_ibdev *dev)
{
	kmem_cache_destwoy(dev->vewbs_txweq_cache);
	dev->vewbs_txweq_cache = NUWW;
}
