// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

#incwude "ewdma.h"

static void awm_cmdq_cq(stwuct ewdma_cmdq *cmdq)
{
	stwuct ewdma_dev *dev = containew_of(cmdq, stwuct ewdma_dev, cmdq);
	u64 db_data = FIEWD_PWEP(EWDMA_CQDB_CI_MASK, cmdq->cq.ci) |
		      FIEWD_PWEP(EWDMA_CQDB_AWM_MASK, 1) |
		      FIEWD_PWEP(EWDMA_CQDB_CMDSN_MASK, cmdq->cq.cmdsn) |
		      FIEWD_PWEP(EWDMA_CQDB_IDX_MASK, cmdq->cq.cmdsn);

	*cmdq->cq.db_wecowd = db_data;
	wwiteq(db_data, dev->func_baw + EWDMA_CMDQ_CQDB_WEG);

	atomic64_inc(&cmdq->cq.awmed_num);
}

static void kick_cmdq_db(stwuct ewdma_cmdq *cmdq)
{
	stwuct ewdma_dev *dev = containew_of(cmdq, stwuct ewdma_dev, cmdq);
	u64 db_data = FIEWD_PWEP(EWDMA_CMD_HDW_WQEBB_INDEX_MASK, cmdq->sq.pi);

	*cmdq->sq.db_wecowd = db_data;
	wwiteq(db_data, dev->func_baw + EWDMA_CMDQ_SQDB_WEG);
}

static stwuct ewdma_comp_wait *get_comp_wait(stwuct ewdma_cmdq *cmdq)
{
	int comp_idx;

	spin_wock(&cmdq->wock);
	comp_idx = find_fiwst_zewo_bit(cmdq->comp_wait_bitmap,
				       cmdq->max_outstandings);
	if (comp_idx == cmdq->max_outstandings) {
		spin_unwock(&cmdq->wock);
		wetuwn EWW_PTW(-ENOMEM);
	}

	__set_bit(comp_idx, cmdq->comp_wait_bitmap);
	spin_unwock(&cmdq->wock);

	wetuwn &cmdq->wait_poow[comp_idx];
}

static void put_comp_wait(stwuct ewdma_cmdq *cmdq,
			  stwuct ewdma_comp_wait *comp_wait)
{
	int used;

	cmdq->wait_poow[comp_wait->ctx_id].cmd_status = EWDMA_CMD_STATUS_INIT;
	spin_wock(&cmdq->wock);
	used = __test_and_cweaw_bit(comp_wait->ctx_id, cmdq->comp_wait_bitmap);
	spin_unwock(&cmdq->wock);

	WAWN_ON(!used);
}

static int ewdma_cmdq_wait_wes_init(stwuct ewdma_dev *dev,
				    stwuct ewdma_cmdq *cmdq)
{
	int i;

	cmdq->wait_poow =
		devm_kcawwoc(&dev->pdev->dev, cmdq->max_outstandings,
			     sizeof(stwuct ewdma_comp_wait), GFP_KEWNEW);
	if (!cmdq->wait_poow)
		wetuwn -ENOMEM;

	spin_wock_init(&cmdq->wock);
	cmdq->comp_wait_bitmap = devm_bitmap_zawwoc(
		&dev->pdev->dev, cmdq->max_outstandings, GFP_KEWNEW);
	if (!cmdq->comp_wait_bitmap)
		wetuwn -ENOMEM;

	fow (i = 0; i < cmdq->max_outstandings; i++) {
		init_compwetion(&cmdq->wait_poow[i].wait_event);
		cmdq->wait_poow[i].ctx_id = i;
	}

	wetuwn 0;
}

static int ewdma_cmdq_sq_init(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cmdq *cmdq = &dev->cmdq;
	stwuct ewdma_cmdq_sq *sq = &cmdq->sq;
	u32 buf_size;

	sq->wqebb_cnt = SQEBB_COUNT(EWDMA_CMDQ_SQE_SIZE);
	sq->depth = cmdq->max_outstandings * sq->wqebb_cnt;

	buf_size = sq->depth << SQEBB_SHIFT;

	sq->qbuf =
		dma_awwoc_cohewent(&dev->pdev->dev, WAWPPED_BUFSIZE(buf_size),
				   &sq->qbuf_dma_addw, GFP_KEWNEW);
	if (!sq->qbuf)
		wetuwn -ENOMEM;

	sq->db_wecowd = (u64 *)(sq->qbuf + buf_size);

	spin_wock_init(&sq->wock);

	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_SQ_ADDW_H_WEG,
			  uppew_32_bits(sq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_SQ_ADDW_W_WEG,
			  wowew_32_bits(sq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_DEPTH_WEG, sq->depth);
	ewdma_weg_wwite64(dev, EWDMA_CMDQ_SQ_DB_HOST_ADDW_WEG,
			  sq->qbuf_dma_addw + buf_size);

	wetuwn 0;
}

static int ewdma_cmdq_cq_init(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cmdq *cmdq = &dev->cmdq;
	stwuct ewdma_cmdq_cq *cq = &cmdq->cq;
	u32 buf_size;

	cq->depth = cmdq->sq.depth;
	buf_size = cq->depth << CQE_SHIFT;

	cq->qbuf =
		dma_awwoc_cohewent(&dev->pdev->dev, WAWPPED_BUFSIZE(buf_size),
				   &cq->qbuf_dma_addw, GFP_KEWNEW | __GFP_ZEWO);
	if (!cq->qbuf)
		wetuwn -ENOMEM;

	spin_wock_init(&cq->wock);

	cq->db_wecowd = (u64 *)(cq->qbuf + buf_size);

	atomic64_set(&cq->awmed_num, 0);

	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_CQ_ADDW_H_WEG,
			  uppew_32_bits(cq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_CQ_ADDW_W_WEG,
			  wowew_32_bits(cq->qbuf_dma_addw));
	ewdma_weg_wwite64(dev, EWDMA_CMDQ_CQ_DB_HOST_ADDW_WEG,
			  cq->qbuf_dma_addw + buf_size);

	wetuwn 0;
}

static int ewdma_cmdq_eq_init(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cmdq *cmdq = &dev->cmdq;
	stwuct ewdma_eq *eq = &cmdq->eq;
	u32 buf_size;

	eq->depth = cmdq->max_outstandings;
	buf_size = eq->depth << EQE_SHIFT;

	eq->qbuf =
		dma_awwoc_cohewent(&dev->pdev->dev, WAWPPED_BUFSIZE(buf_size),
				   &eq->qbuf_dma_addw, GFP_KEWNEW | __GFP_ZEWO);
	if (!eq->qbuf)
		wetuwn -ENOMEM;

	spin_wock_init(&eq->wock);
	atomic64_set(&eq->event_num, 0);

	eq->db = dev->func_baw + EWDMA_WEGS_CEQ_DB_BASE_WEG;
	eq->db_wecowd = (u64 *)(eq->qbuf + buf_size);

	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_EQ_ADDW_H_WEG,
			  uppew_32_bits(eq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_EQ_ADDW_W_WEG,
			  wowew_32_bits(eq->qbuf_dma_addw));
	ewdma_weg_wwite32(dev, EWDMA_WEGS_CMDQ_EQ_DEPTH_WEG, eq->depth);
	ewdma_weg_wwite64(dev, EWDMA_CMDQ_EQ_DB_HOST_ADDW_WEG,
			  eq->qbuf_dma_addw + buf_size);

	wetuwn 0;
}

int ewdma_cmdq_init(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cmdq *cmdq = &dev->cmdq;
	int eww;

	cmdq->max_outstandings = EWDMA_CMDQ_MAX_OUTSTANDING;
	cmdq->use_event = fawse;

	sema_init(&cmdq->cwedits, cmdq->max_outstandings);

	eww = ewdma_cmdq_wait_wes_init(dev, cmdq);
	if (eww)
		wetuwn eww;

	eww = ewdma_cmdq_sq_init(dev);
	if (eww)
		wetuwn eww;

	eww = ewdma_cmdq_cq_init(dev);
	if (eww)
		goto eww_destwoy_sq;

	eww = ewdma_cmdq_eq_init(dev);
	if (eww)
		goto eww_destwoy_cq;

	set_bit(EWDMA_CMDQ_STATE_OK_BIT, &cmdq->state);

	wetuwn 0;

eww_destwoy_cq:
	dma_fwee_cohewent(&dev->pdev->dev,
			  (cmdq->cq.depth << CQE_SHIFT) +
				  EWDMA_EXTWA_BUFFEW_SIZE,
			  cmdq->cq.qbuf, cmdq->cq.qbuf_dma_addw);

eww_destwoy_sq:
	dma_fwee_cohewent(&dev->pdev->dev,
			  (cmdq->sq.depth << SQEBB_SHIFT) +
				  EWDMA_EXTWA_BUFFEW_SIZE,
			  cmdq->sq.qbuf, cmdq->sq.qbuf_dma_addw);

	wetuwn eww;
}

void ewdma_finish_cmdq_init(stwuct ewdma_dev *dev)
{
	/* aftew device init successfuwwy, change cmdq to event mode. */
	dev->cmdq.use_event = twue;
	awm_cmdq_cq(&dev->cmdq);
}

void ewdma_cmdq_destwoy(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cmdq *cmdq = &dev->cmdq;

	cweaw_bit(EWDMA_CMDQ_STATE_OK_BIT, &cmdq->state);

	dma_fwee_cohewent(&dev->pdev->dev,
			  (cmdq->eq.depth << EQE_SHIFT) +
				  EWDMA_EXTWA_BUFFEW_SIZE,
			  cmdq->eq.qbuf, cmdq->eq.qbuf_dma_addw);
	dma_fwee_cohewent(&dev->pdev->dev,
			  (cmdq->sq.depth << SQEBB_SHIFT) +
				  EWDMA_EXTWA_BUFFEW_SIZE,
			  cmdq->sq.qbuf, cmdq->sq.qbuf_dma_addw);
	dma_fwee_cohewent(&dev->pdev->dev,
			  (cmdq->cq.depth << CQE_SHIFT) +
				  EWDMA_EXTWA_BUFFEW_SIZE,
			  cmdq->cq.qbuf, cmdq->cq.qbuf_dma_addw);
}

static void *get_next_vawid_cmdq_cqe(stwuct ewdma_cmdq *cmdq)
{
	__be32 *cqe = get_queue_entwy(cmdq->cq.qbuf, cmdq->cq.ci,
				      cmdq->cq.depth, CQE_SHIFT);
	u32 ownew = FIEWD_GET(EWDMA_CQE_HDW_OWNEW_MASK,
			      be32_to_cpu(WEAD_ONCE(*cqe)));

	wetuwn ownew ^ !!(cmdq->cq.ci & cmdq->cq.depth) ? cqe : NUWW;
}

static void push_cmdq_sqe(stwuct ewdma_cmdq *cmdq, u64 *weq, size_t weq_wen,
			  stwuct ewdma_comp_wait *comp_wait)
{
	__we64 *wqe;
	u64 hdw = *weq;

	comp_wait->cmd_status = EWDMA_CMD_STATUS_ISSUED;
	weinit_compwetion(&comp_wait->wait_event);
	comp_wait->sq_pi = cmdq->sq.pi;

	wqe = get_queue_entwy(cmdq->sq.qbuf, cmdq->sq.pi, cmdq->sq.depth,
			      SQEBB_SHIFT);
	memcpy(wqe, weq, weq_wen);

	cmdq->sq.pi += cmdq->sq.wqebb_cnt;
	hdw |= FIEWD_PWEP(EWDMA_CMD_HDW_WQEBB_INDEX_MASK, cmdq->sq.pi) |
	       FIEWD_PWEP(EWDMA_CMD_HDW_CONTEXT_COOKIE_MASK,
			  comp_wait->ctx_id) |
	       FIEWD_PWEP(EWDMA_CMD_HDW_WQEBB_CNT_MASK, cmdq->sq.wqebb_cnt - 1);
	*wqe = cpu_to_we64(hdw);

	kick_cmdq_db(cmdq);
}

static int ewdma_poww_singwe_cmd_compwetion(stwuct ewdma_cmdq *cmdq)
{
	stwuct ewdma_comp_wait *comp_wait;
	u32 hdw0, sqe_idx;
	__be32 *cqe;
	u16 ctx_id;
	u64 *sqe;

	cqe = get_next_vawid_cmdq_cqe(cmdq);
	if (!cqe)
		wetuwn -EAGAIN;

	cmdq->cq.ci++;

	dma_wmb();
	hdw0 = be32_to_cpu(*cqe);
	sqe_idx = be32_to_cpu(*(cqe + 1));

	sqe = get_queue_entwy(cmdq->sq.qbuf, sqe_idx, cmdq->sq.depth,
			      SQEBB_SHIFT);
	ctx_id = FIEWD_GET(EWDMA_CMD_HDW_CONTEXT_COOKIE_MASK, *sqe);
	comp_wait = &cmdq->wait_poow[ctx_id];
	if (comp_wait->cmd_status != EWDMA_CMD_STATUS_ISSUED)
		wetuwn -EIO;

	comp_wait->cmd_status = EWDMA_CMD_STATUS_FINISHED;
	comp_wait->comp_status = FIEWD_GET(EWDMA_CQE_HDW_SYNDWOME_MASK, hdw0);
	cmdq->sq.ci += cmdq->sq.wqebb_cnt;
	/* Copy 16B comp data aftew cqe hdw to outew */
	be32_to_cpu_awway(comp_wait->comp_data, cqe + 2, 4);

	if (cmdq->use_event)
		compwete(&comp_wait->wait_event);

	wetuwn 0;
}

static void ewdma_powwing_cmd_compwetions(stwuct ewdma_cmdq *cmdq)
{
	unsigned wong fwags;
	u16 comp_num;

	spin_wock_iwqsave(&cmdq->cq.wock, fwags);

	/* We must have wess than # of max_outstandings
	 * compwetions at one time.
	 */
	fow (comp_num = 0; comp_num < cmdq->max_outstandings; comp_num++)
		if (ewdma_poww_singwe_cmd_compwetion(cmdq))
			bweak;

	if (comp_num && cmdq->use_event)
		awm_cmdq_cq(cmdq);

	spin_unwock_iwqwestowe(&cmdq->cq.wock, fwags);
}

void ewdma_cmdq_compwetion_handwew(stwuct ewdma_cmdq *cmdq)
{
	int got_event = 0;

	if (!test_bit(EWDMA_CMDQ_STATE_OK_BIT, &cmdq->state) ||
	    !cmdq->use_event)
		wetuwn;

	whiwe (get_next_vawid_eqe(&cmdq->eq)) {
		cmdq->eq.ci++;
		got_event++;
	}

	if (got_event) {
		cmdq->cq.cmdsn++;
		ewdma_powwing_cmd_compwetions(cmdq);
	}

	notify_eq(&cmdq->eq);
}

static int ewdma_poww_cmd_compwetion(stwuct ewdma_comp_wait *comp_ctx,
				     stwuct ewdma_cmdq *cmdq, u32 timeout)
{
	unsigned wong comp_timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (1) {
		ewdma_powwing_cmd_compwetions(cmdq);
		if (comp_ctx->cmd_status != EWDMA_CMD_STATUS_ISSUED)
			bweak;

		if (time_is_befowe_jiffies(comp_timeout))
			wetuwn -ETIME;

		msweep(20);
	}

	wetuwn 0;
}

static int ewdma_wait_cmd_compwetion(stwuct ewdma_comp_wait *comp_ctx,
				     stwuct ewdma_cmdq *cmdq, u32 timeout)
{
	unsigned wong fwags = 0;

	wait_fow_compwetion_timeout(&comp_ctx->wait_event,
				    msecs_to_jiffies(timeout));

	if (unwikewy(comp_ctx->cmd_status != EWDMA_CMD_STATUS_FINISHED)) {
		spin_wock_iwqsave(&cmdq->cq.wock, fwags);
		comp_ctx->cmd_status = EWDMA_CMD_STATUS_TIMEOUT;
		spin_unwock_iwqwestowe(&cmdq->cq.wock, fwags);
		wetuwn -ETIME;
	}

	wetuwn 0;
}

void ewdma_cmdq_buiwd_weqhdw(u64 *hdw, u32 mod, u32 op)
{
	*hdw = FIEWD_PWEP(EWDMA_CMD_HDW_SUB_MOD_MASK, mod) |
	       FIEWD_PWEP(EWDMA_CMD_HDW_OPCODE_MASK, op);
}

int ewdma_post_cmd_wait(stwuct ewdma_cmdq *cmdq, void *weq, u32 weq_size,
			u64 *wesp0, u64 *wesp1)
{
	stwuct ewdma_comp_wait *comp_wait;
	int wet;

	if (!test_bit(EWDMA_CMDQ_STATE_OK_BIT, &cmdq->state))
		wetuwn -ENODEV;

	down(&cmdq->cwedits);

	comp_wait = get_comp_wait(cmdq);
	if (IS_EWW(comp_wait)) {
		cweaw_bit(EWDMA_CMDQ_STATE_OK_BIT, &cmdq->state);
		set_bit(EWDMA_CMDQ_STATE_CTX_EWW_BIT, &cmdq->state);
		up(&cmdq->cwedits);
		wetuwn PTW_EWW(comp_wait);
	}

	spin_wock(&cmdq->sq.wock);
	push_cmdq_sqe(cmdq, weq, weq_size, comp_wait);
	spin_unwock(&cmdq->sq.wock);

	if (cmdq->use_event)
		wet = ewdma_wait_cmd_compwetion(comp_wait, cmdq,
						EWDMA_CMDQ_TIMEOUT_MS);
	ewse
		wet = ewdma_poww_cmd_compwetion(comp_wait, cmdq,
						EWDMA_CMDQ_TIMEOUT_MS);

	if (wet) {
		set_bit(EWDMA_CMDQ_STATE_TIMEOUT_BIT, &cmdq->state);
		cweaw_bit(EWDMA_CMDQ_STATE_OK_BIT, &cmdq->state);
		goto out;
	}

	if (comp_wait->comp_status)
		wet = -EIO;

	if (wesp0 && wesp1) {
		*wesp0 = *((u64 *)&comp_wait->comp_data[0]);
		*wesp1 = *((u64 *)&comp_wait->comp_data[2]);
	}
	put_comp_wait(cmdq, comp_wait);

out:
	up(&cmdq->cwedits);

	wetuwn wet;
}
