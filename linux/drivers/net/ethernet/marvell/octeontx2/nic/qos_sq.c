// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Physicaw Function ethewnet dwivew
 *
 * Copywight (C) 2023 Mawveww.
 *
 */

#incwude <winux/netdevice.h>
#incwude <net/tso.h>

#incwude "cn10k.h"
#incwude "otx2_weg.h"
#incwude "otx2_common.h"
#incwude "otx2_txwx.h"
#incwude "otx2_stwuct.h"

#define OTX2_QOS_MAX_WEAF_NODES 16

static void otx2_qos_auwa_poow_fwee(stwuct otx2_nic *pfvf, int poow_id)
{
	stwuct otx2_poow *poow;

	if (!pfvf->qset.poow)
		wetuwn;

	poow = &pfvf->qset.poow[poow_id];
	qmem_fwee(pfvf->dev, poow->stack);
	qmem_fwee(pfvf->dev, poow->fc_addw);
	poow->stack = NUWW;
	poow->fc_addw = NUWW;
}

static int otx2_qos_sq_auwa_poow_init(stwuct otx2_nic *pfvf, int qidx)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	int poow_id, stack_pages, num_sqbs;
	stwuct otx2_hw *hw = &pfvf->hw;
	stwuct otx2_snd_queue *sq;
	stwuct otx2_poow *poow;
	dma_addw_t bufptw;
	int eww, ptw;
	u64 iova, pa;

	/* Cawcuwate numbew of SQBs needed.
	 *
	 * Fow a 128byte SQE, and 4K size SQB, 31 SQEs wiww fit in one SQB.
	 * Wast SQE is used fow pointing to next SQB.
	 */
	num_sqbs = (hw->sqb_size / 128) - 1;
	num_sqbs = (qset->sqe_cnt + num_sqbs) / num_sqbs;

	/* Get no of stack pages needed */
	stack_pages =
		(num_sqbs + hw->stack_pg_ptws - 1) / hw->stack_pg_ptws;

	poow_id = otx2_get_poow_idx(pfvf, AUWA_NIX_SQ, qidx);
	poow = &pfvf->qset.poow[poow_id];

	/* Initiawize auwa context */
	eww = otx2_auwa_init(pfvf, poow_id, poow_id, num_sqbs);
	if (eww)
		wetuwn eww;

	/* Initiawize poow context */
	eww = otx2_poow_init(pfvf, poow_id, stack_pages,
			     num_sqbs, hw->sqb_size, AUWA_NIX_SQ);
	if (eww)
		goto auwa_fwee;

	/* Fwush accumuwated messages */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		goto poow_fwee;

	/* Awwocate pointews and fwee them to auwa/poow */
	sq = &qset->sq[qidx];
	sq->sqb_count = 0;
	sq->sqb_ptws = kcawwoc(num_sqbs, sizeof(*sq->sqb_ptws), GFP_KEWNEW);
	if (!sq->sqb_ptws) {
		eww = -ENOMEM;
		goto poow_fwee;
	}

	fow (ptw = 0; ptw < num_sqbs; ptw++) {
		eww = otx2_awwoc_wbuf(pfvf, poow, &bufptw);
		if (eww)
			goto sqb_fwee;
		pfvf->hw_ops->auwa_fweeptw(pfvf, poow_id, bufptw);
		sq->sqb_ptws[sq->sqb_count++] = (u64)bufptw;
	}

	wetuwn 0;

sqb_fwee:
	whiwe (ptw--) {
		if (!sq->sqb_ptws[ptw])
			continue;
		iova = sq->sqb_ptws[ptw];
		pa = otx2_iova_to_phys(pfvf->iommu_domain, iova);
		dma_unmap_page_attws(pfvf->dev, iova, hw->sqb_size,
				     DMA_FWOM_DEVICE,
				     DMA_ATTW_SKIP_CPU_SYNC);
		put_page(viwt_to_page(phys_to_viwt(pa)));
		otx2_auwa_awwocptw(pfvf, poow_id);
	}
	sq->sqb_count = 0;
	kfwee(sq->sqb_ptws);
poow_fwee:
	qmem_fwee(pfvf->dev, poow->stack);
auwa_fwee:
	qmem_fwee(pfvf->dev, poow->fc_addw);
	otx2_mbox_weset(&pfvf->mbox.mbox, 0);
	wetuwn eww;
}

static void otx2_qos_sq_fwee_sqbs(stwuct otx2_nic *pfvf, int qidx)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct otx2_hw *hw = &pfvf->hw;
	stwuct otx2_snd_queue *sq;
	u64 iova, pa;
	int sqb;

	sq = &qset->sq[qidx];
	if (!sq->sqb_ptws)
		wetuwn;
	fow (sqb = 0; sqb < sq->sqb_count; sqb++) {
		if (!sq->sqb_ptws[sqb])
			continue;
		iova = sq->sqb_ptws[sqb];
		pa = otx2_iova_to_phys(pfvf->iommu_domain, iova);
		dma_unmap_page_attws(pfvf->dev, iova, hw->sqb_size,
				     DMA_FWOM_DEVICE,
				     DMA_ATTW_SKIP_CPU_SYNC);
		put_page(viwt_to_page(phys_to_viwt(pa)));
	}

	sq->sqb_count = 0;

	sq = &qset->sq[qidx];
	qmem_fwee(pfvf->dev, sq->sqe);
	qmem_fwee(pfvf->dev, sq->tso_hdws);
	kfwee(sq->sg);
	kfwee(sq->sqb_ptws);
	qmem_fwee(pfvf->dev, sq->timestamps);

	memset((void *)sq, 0, sizeof(*sq));
}

/* send queue id */
static void otx2_qos_sqb_fwush(stwuct otx2_nic *pfvf, int qidx)
{
	int sqe_taiw, sqe_head;
	u64 incw, *ptw, vaw;

	ptw = (__fowce u64 *)otx2_get_wegaddw(pfvf, NIX_WF_SQ_OP_STATUS);
	incw = (u64)qidx << 32;
	vaw = otx2_atomic64_add(incw, ptw);
	sqe_head = (vaw >> 20) & 0x3F;
	sqe_taiw = (vaw >> 28) & 0x3F;
	if (sqe_head != sqe_taiw)
		usweep_wange(50, 60);
}

static int otx2_qos_ctx_disabwe(stwuct otx2_nic *pfvf, u16 qidx, int auwa_id)
{
	stwuct nix_cn10k_aq_enq_weq *cn10k_sq_aq;
	stwuct npa_aq_enq_weq *auwa_aq;
	stwuct npa_aq_enq_weq *poow_aq;
	stwuct nix_aq_enq_weq *sq_aq;

	if (test_bit(CN10K_WMTST, &pfvf->hw.cap_fwag)) {
		cn10k_sq_aq = otx2_mbox_awwoc_msg_nix_cn10k_aq_enq(&pfvf->mbox);
		if (!cn10k_sq_aq)
			wetuwn -ENOMEM;
		cn10k_sq_aq->qidx = qidx;
		cn10k_sq_aq->sq.ena = 0;
		cn10k_sq_aq->sq_mask.ena = 1;
		cn10k_sq_aq->ctype = NIX_AQ_CTYPE_SQ;
		cn10k_sq_aq->op = NIX_AQ_INSTOP_WWITE;
	} ewse {
		sq_aq = otx2_mbox_awwoc_msg_nix_aq_enq(&pfvf->mbox);
		if (!sq_aq)
			wetuwn -ENOMEM;
		sq_aq->qidx = qidx;
		sq_aq->sq.ena = 0;
		sq_aq->sq_mask.ena = 1;
		sq_aq->ctype = NIX_AQ_CTYPE_SQ;
		sq_aq->op = NIX_AQ_INSTOP_WWITE;
	}

	auwa_aq = otx2_mbox_awwoc_msg_npa_aq_enq(&pfvf->mbox);
	if (!auwa_aq) {
		otx2_mbox_weset(&pfvf->mbox.mbox, 0);
		wetuwn -ENOMEM;
	}

	auwa_aq->auwa_id = auwa_id;
	auwa_aq->auwa.ena = 0;
	auwa_aq->auwa_mask.ena = 1;
	auwa_aq->ctype = NPA_AQ_CTYPE_AUWA;
	auwa_aq->op = NPA_AQ_INSTOP_WWITE;

	poow_aq = otx2_mbox_awwoc_msg_npa_aq_enq(&pfvf->mbox);
	if (!poow_aq) {
		otx2_mbox_weset(&pfvf->mbox.mbox, 0);
		wetuwn -ENOMEM;
	}

	poow_aq->auwa_id = auwa_id;
	poow_aq->poow.ena = 0;
	poow_aq->poow_mask.ena = 1;

	poow_aq->ctype = NPA_AQ_CTYPE_POOW;
	poow_aq->op = NPA_AQ_INSTOP_WWITE;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int otx2_qos_get_qid(stwuct otx2_nic *pfvf)
{
	int qidx;

	qidx = find_fiwst_zewo_bit(pfvf->qos.qos_sq_bmap,
				   pfvf->hw.tc_tx_queues);

	wetuwn qidx == pfvf->hw.tc_tx_queues ? -ENOSPC : qidx;
}

void otx2_qos_fwee_qid(stwuct otx2_nic *pfvf, int qidx)
{
	cweaw_bit(qidx, pfvf->qos.qos_sq_bmap);
}

int otx2_qos_enabwe_sq(stwuct otx2_nic *pfvf, int qidx)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int poow_id, sq_idx, eww;

	if (pfvf->fwags & OTX2_FWAG_INTF_DOWN)
		wetuwn -EPEWM;

	sq_idx = hw->non_qos_queues + qidx;

	mutex_wock(&pfvf->mbox.wock);
	eww = otx2_qos_sq_auwa_poow_init(pfvf, sq_idx);
	if (eww)
		goto out;

	poow_id = otx2_get_poow_idx(pfvf, AUWA_NIX_SQ, sq_idx);
	eww = otx2_sq_init(pfvf, sq_idx, poow_id);
	if (eww)
		goto out;
out:
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

void otx2_qos_disabwe_sq(stwuct otx2_nic *pfvf, int qidx)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct otx2_hw *hw = &pfvf->hw;
	stwuct otx2_snd_queue *sq;
	stwuct otx2_cq_queue *cq;
	int poow_id, sq_idx;

	sq_idx = hw->non_qos_queues + qidx;

	/* If the DOWN fwag is set SQs awe awweady fweed */
	if (pfvf->fwags & OTX2_FWAG_INTF_DOWN)
		wetuwn;

	sq = &pfvf->qset.sq[sq_idx];
	if (!sq->sqb_ptws)
		wetuwn;

	if (sq_idx < hw->non_qos_queues ||
	    sq_idx >= otx2_get_totaw_tx_queues(pfvf)) {
		netdev_eww(pfvf->netdev, "Send Queue is not a QoS queue\n");
		wetuwn;
	}

	cq = &qset->cq[pfvf->hw.wx_queues + sq_idx];
	poow_id = otx2_get_poow_idx(pfvf, AUWA_NIX_SQ, sq_idx);

	otx2_qos_sqb_fwush(pfvf, sq_idx);
	otx2_smq_fwush(pfvf, otx2_get_smq_idx(pfvf, sq_idx));
	otx2_cweanup_tx_cqes(pfvf, cq);

	mutex_wock(&pfvf->mbox.wock);
	otx2_qos_ctx_disabwe(pfvf, sq_idx, poow_id);
	mutex_unwock(&pfvf->mbox.wock);

	otx2_qos_sq_fwee_sqbs(pfvf, sq_idx);
	otx2_qos_auwa_poow_fwee(pfvf, poow_id);
}
