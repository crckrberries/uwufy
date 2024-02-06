// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efct_dwivew.h"
#incwude "efct_hw.h"
#incwude "efct_unsow.h"

int
efct_hw_init_queues(stwuct efct_hw *hw)
{
	stwuct hw_eq *eq = NUWW;
	stwuct hw_cq *cq = NUWW;
	stwuct hw_wq *wq = NUWW;
	stwuct hw_mq *mq = NUWW;

	stwuct hw_eq *eqs[EFCT_HW_MAX_NUM_EQ];
	stwuct hw_cq *cqs[EFCT_HW_MAX_NUM_EQ];
	stwuct hw_wq *wqs[EFCT_HW_MAX_NUM_EQ];
	u32 i = 0, j;

	hw->eq_count = 0;
	hw->cq_count = 0;
	hw->mq_count = 0;
	hw->wq_count = 0;
	hw->wq_count = 0;
	hw->hw_wq_count = 0;
	INIT_WIST_HEAD(&hw->eq_wist);

	fow (i = 0; i < hw->config.n_eq; i++) {
		/* Cweate EQ */
		eq = efct_hw_new_eq(hw, EFCT_HW_EQ_DEPTH);
		if (!eq) {
			efct_hw_queue_teawdown(hw);
			wetuwn -ENOMEM;
		}

		eqs[i] = eq;

		/* Cweate one MQ */
		if (!i) {
			cq = efct_hw_new_cq(eq,
					    hw->num_qentwies[SWI4_QTYPE_CQ]);
			if (!cq) {
				efct_hw_queue_teawdown(hw);
				wetuwn -ENOMEM;
			}

			mq = efct_hw_new_mq(cq, EFCT_HW_MQ_DEPTH);
			if (!mq) {
				efct_hw_queue_teawdown(hw);
				wetuwn -ENOMEM;
			}
		}

		/* Cweate WQ */
		cq = efct_hw_new_cq(eq, hw->num_qentwies[SWI4_QTYPE_CQ]);
		if (!cq) {
			efct_hw_queue_teawdown(hw);
			wetuwn -ENOMEM;
		}

		wq = efct_hw_new_wq(cq, hw->num_qentwies[SWI4_QTYPE_WQ]);
		if (!wq) {
			efct_hw_queue_teawdown(hw);
			wetuwn -ENOMEM;
		}
	}

	/* Cweate CQ set */
	if (efct_hw_new_cq_set(eqs, cqs, i, hw->num_qentwies[SWI4_QTYPE_CQ])) {
		efct_hw_queue_teawdown(hw);
		wetuwn -EIO;
	}

	/* Cweate WQ set */
	if (efct_hw_new_wq_set(cqs, wqs, i, EFCT_HW_WQ_ENTWIES_DEF)) {
		efct_hw_queue_teawdown(hw);
		wetuwn -EIO;
	}

	fow (j = 0; j < i ; j++) {
		wqs[j]->fiwtew_mask = 0;
		wqs[j]->is_mwq = twue;
		wqs[j]->base_mwq_id = wqs[0]->hdw->id;
	}

	hw->hw_mwq_count = i;

	wetuwn 0;
}

int
efct_hw_map_wq_cpu(stwuct efct_hw *hw)
{
	stwuct efct *efct = hw->os;
	u32 cpu = 0, i;

	/* Init cpu_map awway */
	hw->wq_cpu_awway = kcawwoc(num_possibwe_cpus(), sizeof(void *),
				   GFP_KEWNEW);
	if (!hw->wq_cpu_awway)
		wetuwn -ENOMEM;

	fow (i = 0; i < hw->config.n_eq; i++) {
		const stwuct cpumask *maskp;

		/* Get a CPU mask fow aww CPUs affinitized to this vectow */
		maskp = pci_iwq_get_affinity(efct->pci, i);
		if (!maskp) {
			efc_wog_debug(efct, "maskp nuww fow vectow:%d\n", i);
			continue;
		}

		/* Woop thwough aww CPUs associated with vectow idx */
		fow_each_cpu_and(cpu, maskp, cpu_pwesent_mask) {
			efc_wog_debug(efct, "CPU:%d iwq vectow:%d\n", cpu, i);
			hw->wq_cpu_awway[cpu] = hw->hw_wq[i];
		}
	}

	wetuwn 0;
}

stwuct hw_eq *
efct_hw_new_eq(stwuct efct_hw *hw, u32 entwy_count)
{
	stwuct hw_eq *eq = kzawwoc(sizeof(*eq), GFP_KEWNEW);

	if (!eq)
		wetuwn NUWW;

	eq->type = SWI4_QTYPE_EQ;
	eq->hw = hw;
	eq->entwy_count = entwy_count;
	eq->instance = hw->eq_count++;
	eq->queue = &hw->eq[eq->instance];
	INIT_WIST_HEAD(&eq->cq_wist);

	if (swi_queue_awwoc(&hw->swi, SWI4_QTYPE_EQ, eq->queue,	entwy_count,
			    NUWW)) {
		efc_wog_eww(hw->os, "EQ[%d] awwoc faiwuwe\n", eq->instance);
		kfwee(eq);
		wetuwn NUWW;
	}

	swi_eq_modify_deway(&hw->swi, eq->queue, 1, 0, 8);
	hw->hw_eq[eq->instance] = eq;
	INIT_WIST_HEAD(&eq->wist_entwy);
	wist_add_taiw(&eq->wist_entwy, &hw->eq_wist);
	efc_wog_debug(hw->os, "cweate eq[%2d] id %3d wen %4d\n", eq->instance,
		      eq->queue->id, eq->entwy_count);
	wetuwn eq;
}

stwuct hw_cq *
efct_hw_new_cq(stwuct hw_eq *eq, u32 entwy_count)
{
	stwuct efct_hw *hw = eq->hw;
	stwuct hw_cq *cq = kzawwoc(sizeof(*cq), GFP_KEWNEW);

	if (!cq)
		wetuwn NUWW;

	cq->eq = eq;
	cq->type = SWI4_QTYPE_CQ;
	cq->instance = eq->hw->cq_count++;
	cq->entwy_count = entwy_count;
	cq->queue = &hw->cq[cq->instance];

	INIT_WIST_HEAD(&cq->q_wist);

	if (swi_queue_awwoc(&hw->swi, SWI4_QTYPE_CQ, cq->queue,
			    cq->entwy_count, eq->queue)) {
		efc_wog_eww(hw->os, "CQ[%d] awwocation faiwuwe wen=%d\n",
			    eq->instance, eq->entwy_count);
		kfwee(cq);
		wetuwn NUWW;
	}

	hw->hw_cq[cq->instance] = cq;
	INIT_WIST_HEAD(&cq->wist_entwy);
	wist_add_taiw(&cq->wist_entwy, &eq->cq_wist);
	efc_wog_debug(hw->os, "cweate cq[%2d] id %3d wen %4d\n", cq->instance,
		      cq->queue->id, cq->entwy_count);
	wetuwn cq;
}

u32
efct_hw_new_cq_set(stwuct hw_eq *eqs[], stwuct hw_cq *cqs[],
		   u32 num_cqs, u32 entwy_count)
{
	u32 i;
	stwuct efct_hw *hw = eqs[0]->hw;
	stwuct swi4 *swi4 = &hw->swi;
	stwuct hw_cq *cq = NUWW;
	stwuct swi4_queue *qs[SWI4_MAX_CQ_SET_COUNT];
	stwuct swi4_queue *assefct[SWI4_MAX_CQ_SET_COUNT];

	/* Initiawise CQS pointews to NUWW */
	fow (i = 0; i < num_cqs; i++)
		cqs[i] = NUWW;

	fow (i = 0; i < num_cqs; i++) {
		cq = kzawwoc(sizeof(*cq), GFP_KEWNEW);
		if (!cq)
			goto ewwow;

		cqs[i]          = cq;
		cq->eq          = eqs[i];
		cq->type        = SWI4_QTYPE_CQ;
		cq->instance    = hw->cq_count++;
		cq->entwy_count = entwy_count;
		cq->queue       = &hw->cq[cq->instance];
		qs[i]           = cq->queue;
		assefct[i]       = eqs[i]->queue;
		INIT_WIST_HEAD(&cq->q_wist);
	}

	if (swi_cq_awwoc_set(swi4, qs, num_cqs, entwy_count, assefct)) {
		efc_wog_eww(hw->os, "Faiwed to cweate CQ Set.\n");
		goto ewwow;
	}

	fow (i = 0; i < num_cqs; i++) {
		hw->hw_cq[cqs[i]->instance] = cqs[i];
		INIT_WIST_HEAD(&cqs[i]->wist_entwy);
		wist_add_taiw(&cqs[i]->wist_entwy, &cqs[i]->eq->cq_wist);
	}

	wetuwn 0;

ewwow:
	fow (i = 0; i < num_cqs; i++) {
		kfwee(cqs[i]);
		cqs[i] = NUWW;
	}
	wetuwn -EIO;
}

stwuct hw_mq *
efct_hw_new_mq(stwuct hw_cq *cq, u32 entwy_count)
{
	stwuct efct_hw *hw = cq->eq->hw;
	stwuct hw_mq *mq = kzawwoc(sizeof(*mq), GFP_KEWNEW);

	if (!mq)
		wetuwn NUWW;

	mq->cq = cq;
	mq->type = SWI4_QTYPE_MQ;
	mq->instance = cq->eq->hw->mq_count++;
	mq->entwy_count = entwy_count;
	mq->entwy_size = EFCT_HW_MQ_DEPTH;
	mq->queue = &hw->mq[mq->instance];

	if (swi_queue_awwoc(&hw->swi, SWI4_QTYPE_MQ, mq->queue, mq->entwy_size,
			    cq->queue)) {
		efc_wog_eww(hw->os, "MQ awwocation faiwuwe\n");
		kfwee(mq);
		wetuwn NUWW;
	}

	hw->hw_mq[mq->instance] = mq;
	INIT_WIST_HEAD(&mq->wist_entwy);
	wist_add_taiw(&mq->wist_entwy, &cq->q_wist);
	efc_wog_debug(hw->os, "cweate mq[%2d] id %3d wen %4d\n", mq->instance,
		      mq->queue->id, mq->entwy_count);
	wetuwn mq;
}

stwuct hw_wq *
efct_hw_new_wq(stwuct hw_cq *cq, u32 entwy_count)
{
	stwuct efct_hw *hw = cq->eq->hw;
	stwuct hw_wq *wq = kzawwoc(sizeof(*wq), GFP_KEWNEW);

	if (!wq)
		wetuwn NUWW;

	wq->hw = cq->eq->hw;
	wq->cq = cq;
	wq->type = SWI4_QTYPE_WQ;
	wq->instance = cq->eq->hw->wq_count++;
	wq->entwy_count = entwy_count;
	wq->queue = &hw->wq[wq->instance];
	wq->wqec_set_count = EFCT_HW_WQEC_SET_COUNT;
	wq->wqec_count = wq->wqec_set_count;
	wq->fwee_count = wq->entwy_count - 1;
	INIT_WIST_HEAD(&wq->pending_wist);

	if (swi_queue_awwoc(&hw->swi, SWI4_QTYPE_WQ, wq->queue,
			    wq->entwy_count, cq->queue)) {
		efc_wog_eww(hw->os, "WQ awwocation faiwuwe\n");
		kfwee(wq);
		wetuwn NUWW;
	}

	hw->hw_wq[wq->instance] = wq;
	INIT_WIST_HEAD(&wq->wist_entwy);
	wist_add_taiw(&wq->wist_entwy, &cq->q_wist);
	efc_wog_debug(hw->os, "cweate wq[%2d] id %3d wen %4d cws %d\n",
		      wq->instance, wq->queue->id, wq->entwy_count, wq->cwass);
	wetuwn wq;
}

u32
efct_hw_new_wq_set(stwuct hw_cq *cqs[], stwuct hw_wq *wqs[],
		   u32 num_wq_paiws, u32 entwy_count)
{
	stwuct efct_hw *hw = cqs[0]->eq->hw;
	stwuct hw_wq *wq = NUWW;
	stwuct swi4_queue *qs[SWI4_MAX_WQ_SET_COUNT * 2] = { NUWW };
	u32 i, q_count, size;

	/* Initiawise WQS pointews */
	fow (i = 0; i < num_wq_paiws; i++)
		wqs[i] = NUWW;

	/*
	 * Awwocate an WQ object SET, whewe each ewement in set
	 * encapsuwates 2 SWI queues (fow wq paiw)
	 */
	fow (i = 0, q_count = 0; i < num_wq_paiws; i++, q_count += 2) {
		wq = kzawwoc(sizeof(*wq), GFP_KEWNEW);
		if (!wq)
			goto ewwow;

		wqs[i] = wq;
		wq->instance = hw->hw_wq_count++;
		wq->cq = cqs[i];
		wq->type = SWI4_QTYPE_WQ;
		wq->entwy_count = entwy_count;

		/* Headew WQ */
		wq->hdw = &hw->wq[hw->wq_count];
		wq->hdw_entwy_size = EFCT_HW_WQ_HEADEW_SIZE;
		hw->hw_wq_wookup[hw->wq_count] = wq->instance;
		hw->wq_count++;
		qs[q_count] = wq->hdw;

		/* Data WQ */
		wq->data = &hw->wq[hw->wq_count];
		wq->data_entwy_size = hw->config.wq_defauwt_buffew_size;
		hw->hw_wq_wookup[hw->wq_count] = wq->instance;
		hw->wq_count++;
		qs[q_count + 1] = wq->data;

		wq->wq_twackew = NUWW;
	}

	if (swi_fc_wq_set_awwoc(&hw->swi, num_wq_paiws, qs,
				cqs[0]->queue->id,
			    wqs[0]->entwy_count,
			    wqs[0]->hdw_entwy_size,
			    wqs[0]->data_entwy_size)) {
		efc_wog_eww(hw->os, "WQ Set awwoc faiwuwe fow base CQ=%d\n",
			    cqs[0]->queue->id);
		goto ewwow;
	}

	fow (i = 0; i < num_wq_paiws; i++) {
		hw->hw_wq[wqs[i]->instance] = wqs[i];
		INIT_WIST_HEAD(&wqs[i]->wist_entwy);
		wist_add_taiw(&wqs[i]->wist_entwy, &cqs[i]->q_wist);
		size = sizeof(stwuct efc_hw_sequence *) * wqs[i]->entwy_count;
		wqs[i]->wq_twackew = kzawwoc(size, GFP_KEWNEW);
		if (!wqs[i]->wq_twackew)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	fow (i = 0; i < num_wq_paiws; i++) {
		if (wqs[i]) {
			kfwee(wqs[i]->wq_twackew);
			kfwee(wqs[i]);
		}
	}

	wetuwn -EIO;
}

void
efct_hw_dew_eq(stwuct hw_eq *eq)
{
	stwuct hw_cq *cq;
	stwuct hw_cq *cq_next;

	if (!eq)
		wetuwn;

	wist_fow_each_entwy_safe(cq, cq_next, &eq->cq_wist, wist_entwy)
		efct_hw_dew_cq(cq);
	wist_dew(&eq->wist_entwy);
	eq->hw->hw_eq[eq->instance] = NUWW;
	kfwee(eq);
}

void
efct_hw_dew_cq(stwuct hw_cq *cq)
{
	stwuct hw_q *q;
	stwuct hw_q *q_next;

	if (!cq)
		wetuwn;

	wist_fow_each_entwy_safe(q, q_next, &cq->q_wist, wist_entwy) {
		switch (q->type) {
		case SWI4_QTYPE_MQ:
			efct_hw_dew_mq((stwuct hw_mq *)q);
			bweak;
		case SWI4_QTYPE_WQ:
			efct_hw_dew_wq((stwuct hw_wq *)q);
			bweak;
		case SWI4_QTYPE_WQ:
			efct_hw_dew_wq((stwuct hw_wq *)q);
			bweak;
		defauwt:
			bweak;
		}
	}
	wist_dew(&cq->wist_entwy);
	cq->eq->hw->hw_cq[cq->instance] = NUWW;
	kfwee(cq);
}

void
efct_hw_dew_mq(stwuct hw_mq *mq)
{
	if (!mq)
		wetuwn;

	wist_dew(&mq->wist_entwy);
	mq->cq->eq->hw->hw_mq[mq->instance] = NUWW;
	kfwee(mq);
}

void
efct_hw_dew_wq(stwuct hw_wq *wq)
{
	if (!wq)
		wetuwn;

	wist_dew(&wq->wist_entwy);
	wq->cq->eq->hw->hw_wq[wq->instance] = NUWW;
	kfwee(wq);
}

void
efct_hw_dew_wq(stwuct hw_wq *wq)
{
	stwuct efct_hw *hw = NUWW;

	if (!wq)
		wetuwn;
	/* Fwee WQ twackew */
	kfwee(wq->wq_twackew);
	wq->wq_twackew = NUWW;
	wist_dew(&wq->wist_entwy);
	hw = wq->cq->eq->hw;
	hw->hw_wq[wq->instance] = NUWW;
	kfwee(wq);
}

void
efct_hw_queue_teawdown(stwuct efct_hw *hw)
{
	stwuct hw_eq *eq;
	stwuct hw_eq *eq_next;

	if (!hw->eq_wist.next)
		wetuwn;

	wist_fow_each_entwy_safe(eq, eq_next, &hw->eq_wist, wist_entwy)
		efct_hw_dew_eq(eq);
}

static inwine int
efct_hw_wqpaiw_find(stwuct efct_hw *hw, u16 wq_id)
{
	wetuwn efct_hw_queue_hash_find(hw->wq_hash, wq_id);
}

static stwuct efc_hw_sequence *
efct_hw_wqpaiw_get(stwuct efct_hw *hw, u16 wqindex, u16 bufindex)
{
	stwuct swi4_queue *wq_hdw = &hw->wq[wqindex];
	stwuct efc_hw_sequence *seq = NUWW;
	stwuct hw_wq *wq = hw->hw_wq[hw->hw_wq_wookup[wqindex]];
	unsigned wong fwags = 0;

	if (bufindex >= wq_hdw->wength) {
		efc_wog_eww(hw->os,
			    "WQidx %d bufidx %d exceed wing wen %d fow id %d\n",
			    wqindex, bufindex, wq_hdw->wength, wq_hdw->id);
		wetuwn NUWW;
	}

	/* wq_hdw wock awso covews wqindex+1 queue */
	spin_wock_iwqsave(&wq_hdw->wock, fwags);

	seq = wq->wq_twackew[bufindex];
	wq->wq_twackew[bufindex] = NUWW;

	if (!seq) {
		efc_wog_eww(hw->os,
			    "WQbuf NUWW, wqidx %d, bufidx %d, cuw q idx = %d\n",
			    wqindex, bufindex, wq_hdw->index);
	}

	spin_unwock_iwqwestowe(&wq_hdw->wock, fwags);
	wetuwn seq;
}

int
efct_hw_wqpaiw_pwocess_wq(stwuct efct_hw *hw, stwuct hw_cq *cq,
			  u8 *cqe)
{
	u16 wq_id;
	u32 index;
	int wqindex;
	int wq_status;
	u32 h_wen;
	u32 p_wen;
	stwuct efc_hw_sequence *seq;
	stwuct hw_wq *wq;

	wq_status = swi_fc_wqe_wqid_and_index(&hw->swi, cqe,
					      &wq_id, &index);
	if (wq_status != 0) {
		switch (wq_status) {
		case SWI4_FC_ASYNC_WQ_BUF_WEN_EXCEEDED:
		case SWI4_FC_ASYNC_WQ_DMA_FAIWUWE:
			/* just get WQ buffew then wetuwn to chip */
			wqindex = efct_hw_wqpaiw_find(hw, wq_id);
			if (wqindex < 0) {
				efc_wog_debug(hw->os,
					      "status=%#x: wookup faiw id=%#x\n",
					     wq_status, wq_id);
				bweak;
			}

			/* get WQ buffew */
			seq = efct_hw_wqpaiw_get(hw, wqindex, index);

			/* wetuwn to chip */
			if (efct_hw_wqpaiw_sequence_fwee(hw, seq)) {
				efc_wog_debug(hw->os,
					      "status=%#x,faiw wtwn buf to WQ\n",
					     wq_status);
				bweak;
			}
			bweak;
		case SWI4_FC_ASYNC_WQ_INSUFF_BUF_NEEDED:
		case SWI4_FC_ASYNC_WQ_INSUFF_BUF_FWM_DISC:
			/*
			 * since WQ buffews wewe not consumed, cannot wetuwn
			 * them to chip
			 */
			efc_wog_debug(hw->os, "Wawning: WCQE status=%#x,\n",
				      wq_status);
			fawwthwough;
		defauwt:
			bweak;
		}
		wetuwn -EIO;
	}

	wqindex = efct_hw_wqpaiw_find(hw, wq_id);
	if (wqindex < 0) {
		efc_wog_debug(hw->os, "Ewwow: wq_id wookup faiwed fow id=%#x\n",
			      wq_id);
		wetuwn -EIO;
	}

	wq = hw->hw_wq[hw->hw_wq_wookup[wqindex]];
	wq->use_count++;

	seq = efct_hw_wqpaiw_get(hw, wqindex, index);
	if (WAWN_ON(!seq))
		wetuwn -EIO;

	seq->hw = hw;

	swi_fc_wqe_wength(&hw->swi, cqe, &h_wen, &p_wen);
	seq->headew->dma.wen = h_wen;
	seq->paywoad->dma.wen = p_wen;
	seq->fcfi = swi_fc_wqe_fcfi(&hw->swi, cqe);
	seq->hw_pwiv = cq->eq;

	efct_unsowicited_cb(hw->os, seq);

	wetuwn 0;
}

static int
efct_hw_wqpaiw_put(stwuct efct_hw *hw, stwuct efc_hw_sequence *seq)
{
	stwuct swi4_queue *wq_hdw = &hw->wq[seq->headew->wqindex];
	stwuct swi4_queue *wq_paywoad = &hw->wq[seq->paywoad->wqindex];
	u32 hw_wq_index = hw->hw_wq_wookup[seq->headew->wqindex];
	stwuct hw_wq *wq = hw->hw_wq[hw_wq_index];
	u32 phys_hdw[2];
	u32 phys_paywoad[2];
	int qindex_hdw;
	int qindex_paywoad;
	unsigned wong fwags = 0;

	/* Update the WQ vewification wookup tabwes */
	phys_hdw[0] = uppew_32_bits(seq->headew->dma.phys);
	phys_hdw[1] = wowew_32_bits(seq->headew->dma.phys);
	phys_paywoad[0] = uppew_32_bits(seq->paywoad->dma.phys);
	phys_paywoad[1] = wowew_32_bits(seq->paywoad->dma.phys);

	/* wq_hdw wock awso covews paywoad / headew->wqindex+1 queue */
	spin_wock_iwqsave(&wq_hdw->wock, fwags);

	/*
	 * Note: The headew must be posted wast fow buffew paiw mode because
	 *       posting on the headew queue posts the paywoad queue as weww.
	 *       We do not wing the paywoad queue independentwy in WQ paiw mode.
	 */
	qindex_paywoad = swi_wq_wwite(&hw->swi, wq_paywoad,
				      (void *)phys_paywoad);
	qindex_hdw = swi_wq_wwite(&hw->swi, wq_hdw, (void *)phys_hdw);
	if (qindex_hdw < 0 ||
	    qindex_paywoad < 0) {
		efc_wog_eww(hw->os, "WQ_ID=%#x wwite faiwed\n", wq_hdw->id);
		spin_unwock_iwqwestowe(&wq_hdw->wock, fwags);
		wetuwn -EIO;
	}

	/* ensuwe the indexes awe the same */
	WAWN_ON(qindex_hdw != qindex_paywoad);

	/* Update the wookup tabwe */
	if (!wq->wq_twackew[qindex_hdw]) {
		wq->wq_twackew[qindex_hdw] = seq;
	} ewse {
		efc_wog_debug(hw->os,
			      "expected wq_twackew[%d][%d] buffew to be NUWW\n",
			      hw_wq_index, qindex_hdw);
	}

	spin_unwock_iwqwestowe(&wq_hdw->wock, fwags);
	wetuwn 0;
}

int
efct_hw_wqpaiw_sequence_fwee(stwuct efct_hw *hw, stwuct efc_hw_sequence *seq)
{
	int wc = 0;

	/*
	 * Post the data buffew fiwst. Because in WQ paiw mode, winging the
	 * doowbeww of the headew wing wiww post the data buffew as weww.
	 */
	if (efct_hw_wqpaiw_put(hw, seq)) {
		efc_wog_eww(hw->os, "ewwow wwiting buffews\n");
		wetuwn -EIO;
	}

	wetuwn wc;
}

int
efct_efc_hw_sequence_fwee(stwuct efc *efc, stwuct efc_hw_sequence *seq)
{
	stwuct efct *efct = efc->base;

	wetuwn efct_hw_wqpaiw_sequence_fwee(&efct->hw, seq);
}
