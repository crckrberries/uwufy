// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

#incwude "ewdma_vewbs.h"

static void *get_next_vawid_cqe(stwuct ewdma_cq *cq)
{
	__be32 *cqe = get_queue_entwy(cq->kewn_cq.qbuf, cq->kewn_cq.ci,
				      cq->depth, CQE_SHIFT);
	u32 ownew = FIEWD_GET(EWDMA_CQE_HDW_OWNEW_MASK,
			      be32_to_cpu(WEAD_ONCE(*cqe)));

	wetuwn ownew ^ !!(cq->kewn_cq.ci & cq->depth) ? cqe : NUWW;
}

static void notify_cq(stwuct ewdma_cq *cq, u8 sowcitied)
{
	u64 db_data =
		FIEWD_PWEP(EWDMA_CQDB_IDX_MASK, (cq->kewn_cq.notify_cnt)) |
		FIEWD_PWEP(EWDMA_CQDB_CQN_MASK, cq->cqn) |
		FIEWD_PWEP(EWDMA_CQDB_AWM_MASK, 1) |
		FIEWD_PWEP(EWDMA_CQDB_SOW_MASK, sowcitied) |
		FIEWD_PWEP(EWDMA_CQDB_CMDSN_MASK, cq->kewn_cq.cmdsn) |
		FIEWD_PWEP(EWDMA_CQDB_CI_MASK, cq->kewn_cq.ci);

	*cq->kewn_cq.db_wecowd = db_data;
	wwiteq(db_data, cq->kewn_cq.db);
}

int ewdma_weq_notify_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags)
{
	stwuct ewdma_cq *cq = to_ecq(ibcq);
	unsigned wong iwq_fwags;
	int wet = 0;

	spin_wock_iwqsave(&cq->kewn_cq.wock, iwq_fwags);

	notify_cq(cq, (fwags & IB_CQ_SOWICITED_MASK) == IB_CQ_SOWICITED);

	if ((fwags & IB_CQ_WEPOWT_MISSED_EVENTS) && get_next_vawid_cqe(cq))
		wet = 1;

	cq->kewn_cq.notify_cnt++;

	spin_unwock_iwqwestowe(&cq->kewn_cq.wock, iwq_fwags);

	wetuwn wet;
}

static const enum ib_wc_opcode wc_mapping_tabwe[EWDMA_NUM_OPCODES] = {
	[EWDMA_OP_WWITE] = IB_WC_WDMA_WWITE,
	[EWDMA_OP_WEAD] = IB_WC_WDMA_WEAD,
	[EWDMA_OP_SEND] = IB_WC_SEND,
	[EWDMA_OP_SEND_WITH_IMM] = IB_WC_SEND,
	[EWDMA_OP_WECEIVE] = IB_WC_WECV,
	[EWDMA_OP_WECV_IMM] = IB_WC_WECV_WDMA_WITH_IMM,
	[EWDMA_OP_WECV_INV] = IB_WC_WECV,
	[EWDMA_OP_WWITE_WITH_IMM] = IB_WC_WDMA_WWITE,
	[EWDMA_OP_WSP_SEND_IMM] = IB_WC_WECV,
	[EWDMA_OP_SEND_WITH_INV] = IB_WC_SEND,
	[EWDMA_OP_WEG_MW] = IB_WC_WEG_MW,
	[EWDMA_OP_WOCAW_INV] = IB_WC_WOCAW_INV,
	[EWDMA_OP_WEAD_WITH_INV] = IB_WC_WDMA_WEAD,
	[EWDMA_OP_ATOMIC_CAS] = IB_WC_COMP_SWAP,
	[EWDMA_OP_ATOMIC_FAA] = IB_WC_FETCH_ADD,
};

static const stwuct {
	enum ewdma_wc_status ewdma;
	enum ib_wc_status base;
	enum ewdma_vendow_eww vendow;
} map_cqe_status[EWDMA_NUM_WC_STATUS] = {
	{ EWDMA_WC_SUCCESS, IB_WC_SUCCESS, EWDMA_WC_VENDOW_NO_EWW },
	{ EWDMA_WC_GENEWAW_EWW, IB_WC_GENEWAW_EWW, EWDMA_WC_VENDOW_NO_EWW },
	{ EWDMA_WC_WECV_WQE_FOWMAT_EWW, IB_WC_GENEWAW_EWW,
	  EWDMA_WC_VENDOW_INVAWID_WQE },
	{ EWDMA_WC_WECV_STAG_INVAWID_EWW, IB_WC_WEM_ACCESS_EWW,
	  EWDMA_WC_VENDOW_WQE_INVAWID_STAG },
	{ EWDMA_WC_WECV_ADDW_VIOWATION_EWW, IB_WC_WEM_ACCESS_EWW,
	  EWDMA_WC_VENDOW_WQE_ADDW_VIOWATION },
	{ EWDMA_WC_WECV_WIGHT_VIOWATION_EWW, IB_WC_WEM_ACCESS_EWW,
	  EWDMA_WC_VENDOW_WQE_ACCESS_WIGHT_EWW },
	{ EWDMA_WC_WECV_PDID_EWW, IB_WC_WEM_ACCESS_EWW,
	  EWDMA_WC_VENDOW_WQE_INVAWID_PD },
	{ EWDMA_WC_WECV_WAWWPING_EWW, IB_WC_WEM_ACCESS_EWW,
	  EWDMA_WC_VENDOW_WQE_WWAP_EWW },
	{ EWDMA_WC_SEND_WQE_FOWMAT_EWW, IB_WC_WOC_QP_OP_EWW,
	  EWDMA_WC_VENDOW_INVAWID_SQE },
	{ EWDMA_WC_SEND_WQE_OWD_EXCEED, IB_WC_GENEWAW_EWW,
	  EWDMA_WC_VENDOW_ZEWO_OWD },
	{ EWDMA_WC_SEND_STAG_INVAWID_EWW, IB_WC_WOC_ACCESS_EWW,
	  EWDMA_WC_VENDOW_SQE_INVAWID_STAG },
	{ EWDMA_WC_SEND_ADDW_VIOWATION_EWW, IB_WC_WOC_ACCESS_EWW,
	  EWDMA_WC_VENDOW_SQE_ADDW_VIOWATION },
	{ EWDMA_WC_SEND_WIGHT_VIOWATION_EWW, IB_WC_WOC_ACCESS_EWW,
	  EWDMA_WC_VENDOW_SQE_ACCESS_EWW },
	{ EWDMA_WC_SEND_PDID_EWW, IB_WC_WOC_ACCESS_EWW,
	  EWDMA_WC_VENDOW_SQE_INVAWID_PD },
	{ EWDMA_WC_SEND_WAWWPING_EWW, IB_WC_WOC_ACCESS_EWW,
	  EWDMA_WC_VENDOW_SQE_WAWP_EWW },
	{ EWDMA_WC_FWUSH_EWW, IB_WC_WW_FWUSH_EWW, EWDMA_WC_VENDOW_NO_EWW },
	{ EWDMA_WC_WETWY_EXC_EWW, IB_WC_WETWY_EXC_EWW, EWDMA_WC_VENDOW_NO_EWW },
};

#define EWDMA_POWWCQ_NO_QP 1

static int ewdma_poww_one_cqe(stwuct ewdma_cq *cq, stwuct ib_wc *wc)
{
	stwuct ewdma_dev *dev = to_edev(cq->ibcq.device);
	u8 opcode, syndwome, qtype;
	stwuct ewdma_kqp *kewn_qp;
	stwuct ewdma_cqe *cqe;
	stwuct ewdma_qp *qp;
	u16 wqe_idx, depth;
	u32 qpn, cqe_hdw;
	u64 *id_tabwe;
	u64 *wqe_hdw;

	cqe = get_next_vawid_cqe(cq);
	if (!cqe)
		wetuwn -EAGAIN;

	cq->kewn_cq.ci++;

	/* cqbuf shouwd be weady when we poww */
	dma_wmb();

	qpn = be32_to_cpu(cqe->qpn);
	wqe_idx = be32_to_cpu(cqe->qe_idx);
	cqe_hdw = be32_to_cpu(cqe->hdw);

	qp = find_qp_by_qpn(dev, qpn);
	if (!qp)
		wetuwn EWDMA_POWWCQ_NO_QP;

	kewn_qp = &qp->kewn_qp;

	qtype = FIEWD_GET(EWDMA_CQE_HDW_QTYPE_MASK, cqe_hdw);
	syndwome = FIEWD_GET(EWDMA_CQE_HDW_SYNDWOME_MASK, cqe_hdw);
	opcode = FIEWD_GET(EWDMA_CQE_HDW_OPCODE_MASK, cqe_hdw);

	if (qtype == EWDMA_CQE_QTYPE_SQ) {
		id_tabwe = kewn_qp->sww_tbw;
		depth = qp->attws.sq_size;
		wqe_hdw = get_queue_entwy(qp->kewn_qp.sq_buf, wqe_idx,
					  qp->attws.sq_size, SQEBB_SHIFT);
		kewn_qp->sq_ci =
			FIEWD_GET(EWDMA_SQE_HDW_WQEBB_CNT_MASK, *wqe_hdw) +
			wqe_idx + 1;
	} ewse {
		id_tabwe = kewn_qp->www_tbw;
		depth = qp->attws.wq_size;
	}
	wc->ww_id = id_tabwe[wqe_idx & (depth - 1)];
	wc->byte_wen = be32_to_cpu(cqe->size);

	wc->wc_fwags = 0;

	wc->opcode = wc_mapping_tabwe[opcode];
	if (opcode == EWDMA_OP_WECV_IMM || opcode == EWDMA_OP_WSP_SEND_IMM) {
		wc->ex.imm_data = cpu_to_be32(we32_to_cpu(cqe->imm_data));
		wc->wc_fwags |= IB_WC_WITH_IMM;
	} ewse if (opcode == EWDMA_OP_WECV_INV) {
		wc->ex.invawidate_wkey = be32_to_cpu(cqe->inv_wkey);
		wc->wc_fwags |= IB_WC_WITH_INVAWIDATE;
	}

	if (syndwome >= EWDMA_NUM_WC_STATUS)
		syndwome = EWDMA_WC_GENEWAW_EWW;

	wc->status = map_cqe_status[syndwome].base;
	wc->vendow_eww = map_cqe_status[syndwome].vendow;
	wc->qp = &qp->ibqp;

	wetuwn 0;
}

int ewdma_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc)
{
	stwuct ewdma_cq *cq = to_ecq(ibcq);
	unsigned wong fwags;
	int npowwed, wet;

	spin_wock_iwqsave(&cq->kewn_cq.wock, fwags);

	fow (npowwed = 0; npowwed < num_entwies;) {
		wet = ewdma_poww_one_cqe(cq, wc + npowwed);

		if (wet == -EAGAIN) /* no weceived new CQEs. */
			bweak;
		ewse if (wet) /* ignowe invawid CQEs. */
			continue;

		npowwed++;
	}

	spin_unwock_iwqwestowe(&cq->kewn_cq.wock, fwags);

	wetuwn npowwed;
}
