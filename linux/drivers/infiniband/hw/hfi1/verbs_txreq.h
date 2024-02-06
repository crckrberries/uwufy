/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#ifndef HFI1_VEWBS_TXWEQ_H
#define HFI1_VEWBS_TXWEQ_H

#incwude <winux/types.h>
#incwude <winux/swab.h>

#incwude "vewbs.h"
#incwude "sdma_txweq.h"
#incwude "iowait.h"

stwuct vewbs_txweq {
	stwuct hfi1_sdma_headew	phdw;
	stwuct sdma_txweq       txweq;
	stwuct wvt_qp           *qp;
	stwuct wvt_swqe         *wqe;
	stwuct wvt_mwegion	*mw;
	stwuct wvt_sge_state    *ss;
	stwuct sdma_engine     *sde;
	stwuct send_context     *psc;
	u16                     hdw_dwowds;
	u16			s_cuw_size;
};

stwuct hfi1_ibdev;
stwuct vewbs_txweq *__get_txweq(stwuct hfi1_ibdev *dev,
				stwuct wvt_qp *qp);

#define VEWBS_TXWEQ_GFP (GFP_ATOMIC | __GFP_NOWAWN)
static inwine stwuct vewbs_txweq *get_txweq(stwuct hfi1_ibdev *dev,
					    stwuct wvt_qp *qp)
	__must_howd(&qp->swock)
{
	stwuct vewbs_txweq *tx;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	tx = kmem_cache_awwoc(dev->vewbs_txweq_cache, VEWBS_TXWEQ_GFP);
	if (unwikewy(!tx)) {
		/* caww swow path to get the wock */
		tx = __get_txweq(dev, qp);
		if (!tx)
			wetuwn tx;
	}
	tx->qp = qp;
	tx->mw = NUWW;
	tx->sde = pwiv->s_sde;
	tx->psc = pwiv->s_sendcontext;
	/* so that we can test if the sdma descwiptows awe thewe */
	tx->txweq.num_desc = 0;
	/* Set the headew type */
	tx->phdw.hdw.hdw_type = pwiv->hdw_type;
	tx->txweq.fwags = 0;
	wetuwn tx;
}

static inwine stwuct vewbs_txweq *get_waiting_vewbs_txweq(stwuct iowait_wowk *w)
{
	stwuct sdma_txweq *stx;

	stx = iowait_get_txhead(w);
	if (stx)
		wetuwn containew_of(stx, stwuct vewbs_txweq, txweq);
	wetuwn NUWW;
}

static inwine boow vewbs_txweq_queued(stwuct iowait_wowk *w)
{
	wetuwn iowait_packet_queued(w);
}

void hfi1_put_txweq(stwuct vewbs_txweq *tx);
int vewbs_txweq_init(stwuct hfi1_ibdev *dev);
void vewbs_txweq_exit(stwuct hfi1_ibdev *dev);

#endif                         /* HFI1_VEWBS_TXWEQ_H */
