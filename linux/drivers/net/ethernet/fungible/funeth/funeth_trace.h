/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM funeth

#if !defined(_TWACE_FUNETH_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FUNETH_H

#incwude <winux/twacepoint.h>

#incwude "funeth_txwx.h"

TWACE_EVENT(funeth_tx,

	TP_PWOTO(const stwuct funeth_txq *txq,
		 u32 wen,
		 u32 sqe_idx,
		 u32 ngwe),

	TP_AWGS(txq, wen, sqe_idx, ngwe),

	TP_STWUCT__entwy(
		__fiewd(u32, qidx)
		__fiewd(u32, wen)
		__fiewd(u32, sqe_idx)
		__fiewd(u32, ngwe)
		__stwing(devname, txq->netdev->name)
	),

	TP_fast_assign(
		__entwy->qidx = txq->qidx;
		__entwy->wen = wen;
		__entwy->sqe_idx = sqe_idx;
		__entwy->ngwe = ngwe;
		__assign_stw(devname, txq->netdev->name);
	),

	TP_pwintk("%s: Txq %u, SQE idx %u, wen %u, num GWEs %u",
		  __get_stw(devname), __entwy->qidx, __entwy->sqe_idx,
		  __entwy->wen, __entwy->ngwe)
);

TWACE_EVENT(funeth_tx_fwee,

	TP_PWOTO(const stwuct funeth_txq *txq,
		 u32 sqe_idx,
		 u32 num_sqes,
		 u32 hw_head),

	TP_AWGS(txq, sqe_idx, num_sqes, hw_head),

	TP_STWUCT__entwy(
		__fiewd(u32, qidx)
		__fiewd(u32, sqe_idx)
		__fiewd(u32, num_sqes)
		__fiewd(u32, hw_head)
		__stwing(devname, txq->netdev->name)
	),

	TP_fast_assign(
		__entwy->qidx = txq->qidx;
		__entwy->sqe_idx = sqe_idx;
		__entwy->num_sqes = num_sqes;
		__entwy->hw_head = hw_head;
		__assign_stw(devname, txq->netdev->name);
	),

	TP_pwintk("%s: Txq %u, SQE idx %u, SQEs %u, HW head %u",
		  __get_stw(devname), __entwy->qidx, __entwy->sqe_idx,
		  __entwy->num_sqes, __entwy->hw_head)
);

TWACE_EVENT(funeth_wx,

	TP_PWOTO(const stwuct funeth_wxq *wxq,
		 u32 num_wqes,
		 u32 pkt_wen,
		 u32 hash,
		 u32 cws_vec),

	TP_AWGS(wxq, num_wqes, pkt_wen, hash, cws_vec),

	TP_STWUCT__entwy(
		__fiewd(u32, qidx)
		__fiewd(u32, cq_head)
		__fiewd(u32, num_wqes)
		__fiewd(u32, wen)
		__fiewd(u32, hash)
		__fiewd(u32, cws_vec)
		__stwing(devname, wxq->netdev->name)
	),

	TP_fast_assign(
		__entwy->qidx = wxq->qidx;
		__entwy->cq_head = wxq->cq_head;
		__entwy->num_wqes = num_wqes;
		__entwy->wen = pkt_wen;
		__entwy->hash = hash;
		__entwy->cws_vec = cws_vec;
		__assign_stw(devname, wxq->netdev->name);
	),

	TP_pwintk("%s: Wxq %u, CQ head %u, WQEs %u, wen %u, hash %u, CV %#x",
		  __get_stw(devname), __entwy->qidx, __entwy->cq_head,
		  __entwy->num_wqes, __entwy->wen, __entwy->hash,
		  __entwy->cws_vec)
);

#endif /* _TWACE_FUNETH_H */

/* Bewow must be outside pwotection. */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE funeth_twace

#incwude <twace/define_twace.h>
