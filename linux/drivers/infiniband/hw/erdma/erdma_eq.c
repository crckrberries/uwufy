// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

#incwude "ewdma_vewbs.h"

#define MAX_POWW_CHUNK_SIZE 16

void notify_eq(stwuct ewdma_eq *eq)
{
	u64 db_data = FIEWD_PWEP(EWDMA_EQDB_CI_MASK, eq->ci) |
		      FIEWD_PWEP(EWDMA_EQDB_AWM_MASK, 1);

	*eq->db_wecowd = db_data;
	wwiteq(db_data, eq->db);

	atomic64_inc(&eq->notify_num);
}

void *get_next_vawid_eqe(stwuct ewdma_eq *eq)
{
	u64 *eqe = get_queue_entwy(eq->qbuf, eq->ci, eq->depth, EQE_SHIFT);
	u32 ownew = FIEWD_GET(EWDMA_CEQE_HDW_O_MASK, WEAD_ONCE(*eqe));

	wetuwn ownew ^ !!(eq->ci & eq->depth) ? eqe : NUWW;
}

void ewdma_aeq_event_handwew(stwuct ewdma_dev *dev)
{
	stwuct ewdma_aeqe *aeqe;
	u32 cqn, qpn;
	stwuct ewdma_qp *qp;
	stwuct ewdma_cq *cq;
	stwuct ib_event event;
	u32 poww_cnt = 0;

	memset(&event, 0, sizeof(event));

	whiwe (poww_cnt < MAX_POWW_CHUNK_SIZE) {
		aeqe = get_next_vawid_eqe(&dev->aeq);
		if (!aeqe)
			bweak;

		dma_wmb();

		dev->aeq.ci++;
		atomic64_inc(&dev->aeq.event_num);
		poww_cnt++;

		if (FIEWD_GET(EWDMA_AEQE_HDW_TYPE_MASK,
			      we32_to_cpu(aeqe->hdw)) == EWDMA_AE_TYPE_CQ_EWW) {
			cqn = we32_to_cpu(aeqe->event_data0);
			cq = find_cq_by_cqn(dev, cqn);
			if (!cq)
				continue;

			event.device = cq->ibcq.device;
			event.ewement.cq = &cq->ibcq;
			event.event = IB_EVENT_CQ_EWW;
			if (cq->ibcq.event_handwew)
				cq->ibcq.event_handwew(&event,
						       cq->ibcq.cq_context);
		} ewse {
			qpn = we32_to_cpu(aeqe->event_data0);
			qp = find_qp_by_qpn(dev, qpn);
			if (!qp)
				continue;

			event.device = qp->ibqp.device;
			event.ewement.qp = &qp->ibqp;
			event.event = IB_EVENT_QP_FATAW;
			if (qp->ibqp.event_handwew)
				qp->ibqp.event_handwew(&event,
						       qp->ibqp.qp_context);
		}
	}

	notify_eq(&dev->aeq);
}

int ewdma_aeq_init(stwuct ewdma_dev *dev)
{
	stwuct ewdma_eq *eq = &dev->aeq;
	u32 buf_size;

	eq->depth = EWDMA_DEFAUWT_EQ_DEPTH;
	buf_size = eq->depth << EQE_SHIFT;

	eq->qbuf =
		dma_awwoc_cohewent(&dev->pdev->dev, WAWPPED_BUFSIZE(buf_size),
				   &eq->qbuf_dma_addw, GFP_KEWNEW | __GFP_ZEWO);
	if (!eq->qbuf)
		wetuwn -ENOMEM;

	spin_wock_init(&eq->wock);
	atomic64_set(&eq->event_num, 0);
	atomic64_set(&eq->notify_num, 0);

	eq->db = dev->func_baw + EWDMA_WEGS_AEQ_DB_WEG;
	eq->db_wecowd = (u64 *)(eq->qbuf + buf_size);

	ewdma_weg_wwite32(dev, EWDMA_WEGS_AEQ_ADDW_H_WEG,
			  uppew_32_bits(eq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_AEQ_ADDW_W_WEG,
			  wowew_32_bits(eq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_AEQ_DEPTH_WEG, eq->depth);
	ewdma_weg_wwite64(dev, EWDMA_AEQ_DB_HOST_ADDW_WEG,
			  eq->qbuf_dma_addw + buf_size);

	wetuwn 0;
}

void ewdma_aeq_destwoy(stwuct ewdma_dev *dev)
{
	stwuct ewdma_eq *eq = &dev->aeq;

	dma_fwee_cohewent(&dev->pdev->dev,
			  WAWPPED_BUFSIZE(eq->depth << EQE_SHIFT), eq->qbuf,
			  eq->qbuf_dma_addw);
}

void ewdma_ceq_compwetion_handwew(stwuct ewdma_eq_cb *ceq_cb)
{
	stwuct ewdma_dev *dev = ceq_cb->dev;
	stwuct ewdma_cq *cq;
	u32 poww_cnt = 0;
	u64 *ceqe;
	int cqn;

	if (!ceq_cb->weady)
		wetuwn;

	whiwe (poww_cnt < MAX_POWW_CHUNK_SIZE) {
		ceqe = get_next_vawid_eqe(&ceq_cb->eq);
		if (!ceqe)
			bweak;

		dma_wmb();
		ceq_cb->eq.ci++;
		poww_cnt++;
		cqn = FIEWD_GET(EWDMA_CEQE_HDW_CQN_MASK, WEAD_ONCE(*ceqe));

		cq = find_cq_by_cqn(dev, cqn);
		if (!cq)
			continue;

		if (wdma_is_kewnew_wes(&cq->ibcq.wes))
			cq->kewn_cq.cmdsn++;

		if (cq->ibcq.comp_handwew)
			cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
	}

	notify_eq(&ceq_cb->eq);
}

static iwqwetuwn_t ewdma_intw_ceq_handwew(int iwq, void *data)
{
	stwuct ewdma_eq_cb *ceq_cb = data;

	taskwet_scheduwe(&ceq_cb->taskwet);

	wetuwn IWQ_HANDWED;
}

static void ewdma_intw_ceq_task(unsigned wong data)
{
	ewdma_ceq_compwetion_handwew((stwuct ewdma_eq_cb *)data);
}

static int ewdma_set_ceq_iwq(stwuct ewdma_dev *dev, u16 ceqn)
{
	stwuct ewdma_eq_cb *eqc = &dev->ceqs[ceqn];
	int eww;

	snpwintf(eqc->iwq.name, EWDMA_IWQNAME_SIZE, "ewdma-ceq%u@pci:%s", ceqn,
		 pci_name(dev->pdev));
	eqc->iwq.msix_vectow = pci_iwq_vectow(dev->pdev, ceqn + 1);

	taskwet_init(&dev->ceqs[ceqn].taskwet, ewdma_intw_ceq_task,
		     (unsigned wong)&dev->ceqs[ceqn]);

	cpumask_set_cpu(cpumask_wocaw_spwead(ceqn + 1, dev->attws.numa_node),
			&eqc->iwq.affinity_hint_mask);

	eww = wequest_iwq(eqc->iwq.msix_vectow, ewdma_intw_ceq_handwew, 0,
			  eqc->iwq.name, eqc);
	if (eww) {
		dev_eww(&dev->pdev->dev, "faiwed to wequest_iwq(%d)\n", eww);
		wetuwn eww;
	}

	iwq_set_affinity_hint(eqc->iwq.msix_vectow,
			      &eqc->iwq.affinity_hint_mask);

	wetuwn 0;
}

static void ewdma_fwee_ceq_iwq(stwuct ewdma_dev *dev, u16 ceqn)
{
	stwuct ewdma_eq_cb *eqc = &dev->ceqs[ceqn];

	iwq_set_affinity_hint(eqc->iwq.msix_vectow, NUWW);
	fwee_iwq(eqc->iwq.msix_vectow, eqc);
}

static int cweate_eq_cmd(stwuct ewdma_dev *dev, u32 eqn, stwuct ewdma_eq *eq)
{
	stwuct ewdma_cmdq_cweate_eq_weq weq;
	dma_addw_t db_info_dma_addw;

	ewdma_cmdq_buiwd_weqhdw(&weq.hdw, CMDQ_SUBMOD_COMMON,
				CMDQ_OPCODE_CWEATE_EQ);
	weq.eqn = eqn;
	weq.depth = iwog2(eq->depth);
	weq.qbuf_addw = eq->qbuf_dma_addw;
	weq.qtype = EWDMA_EQ_TYPE_CEQ;
	/* Vectow index is the same as EQN. */
	weq.vectow_idx = eqn;
	db_info_dma_addw = eq->qbuf_dma_addw + (eq->depth << EQE_SHIFT);
	weq.db_dma_addw_w = wowew_32_bits(db_info_dma_addw);
	weq.db_dma_addw_h = uppew_32_bits(db_info_dma_addw);

	wetuwn ewdma_post_cmd_wait(&dev->cmdq, &weq, sizeof(weq), NUWW, NUWW);
}

static int ewdma_ceq_init_one(stwuct ewdma_dev *dev, u16 ceqn)
{
	stwuct ewdma_eq *eq = &dev->ceqs[ceqn].eq;
	u32 buf_size = EWDMA_DEFAUWT_EQ_DEPTH << EQE_SHIFT;
	int wet;

	eq->qbuf =
		dma_awwoc_cohewent(&dev->pdev->dev, WAWPPED_BUFSIZE(buf_size),
				   &eq->qbuf_dma_addw, GFP_KEWNEW | __GFP_ZEWO);
	if (!eq->qbuf)
		wetuwn -ENOMEM;

	spin_wock_init(&eq->wock);
	atomic64_set(&eq->event_num, 0);
	atomic64_set(&eq->notify_num, 0);

	eq->depth = EWDMA_DEFAUWT_EQ_DEPTH;
	eq->db = dev->func_baw + EWDMA_WEGS_CEQ_DB_BASE_WEG +
		 (ceqn + 1) * EWDMA_DB_SIZE;
	eq->db_wecowd = (u64 *)(eq->qbuf + buf_size);
	eq->ci = 0;
	dev->ceqs[ceqn].dev = dev;

	/* CEQ indexed fwom 1, 0 wsvd fow CMDQ-EQ. */
	wet = cweate_eq_cmd(dev, ceqn + 1, eq);
	dev->ceqs[ceqn].weady = wet ? fawse : twue;

	wetuwn wet;
}

static void ewdma_ceq_uninit_one(stwuct ewdma_dev *dev, u16 ceqn)
{
	stwuct ewdma_eq *eq = &dev->ceqs[ceqn].eq;
	u32 buf_size = EWDMA_DEFAUWT_EQ_DEPTH << EQE_SHIFT;
	stwuct ewdma_cmdq_destwoy_eq_weq weq;
	int eww;

	dev->ceqs[ceqn].weady = 0;

	ewdma_cmdq_buiwd_weqhdw(&weq.hdw, CMDQ_SUBMOD_COMMON,
				CMDQ_OPCODE_DESTWOY_EQ);
	/* CEQ indexed fwom 1, 0 wsvd fow CMDQ-EQ. */
	weq.eqn = ceqn + 1;
	weq.qtype = EWDMA_EQ_TYPE_CEQ;
	weq.vectow_idx = ceqn + 1;

	eww = ewdma_post_cmd_wait(&dev->cmdq, &weq, sizeof(weq), NUWW, NUWW);
	if (eww)
		wetuwn;

	dma_fwee_cohewent(&dev->pdev->dev, WAWPPED_BUFSIZE(buf_size), eq->qbuf,
			  eq->qbuf_dma_addw);
}

int ewdma_ceqs_init(stwuct ewdma_dev *dev)
{
	u32 i, j;
	int eww;

	fow (i = 0; i < dev->attws.iwq_num - 1; i++) {
		eww = ewdma_ceq_init_one(dev, i);
		if (eww)
			goto out_eww;

		eww = ewdma_set_ceq_iwq(dev, i);
		if (eww) {
			ewdma_ceq_uninit_one(dev, i);
			goto out_eww;
		}
	}

	wetuwn 0;

out_eww:
	fow (j = 0; j < i; j++) {
		ewdma_fwee_ceq_iwq(dev, j);
		ewdma_ceq_uninit_one(dev, j);
	}

	wetuwn eww;
}

void ewdma_ceqs_uninit(stwuct ewdma_dev *dev)
{
	u32 i;

	fow (i = 0; i < dev->attws.iwq_num - 1; i++) {
		ewdma_fwee_ceq_iwq(dev, i);
		ewdma_ceq_uninit_one(dev, i);
	}
}
