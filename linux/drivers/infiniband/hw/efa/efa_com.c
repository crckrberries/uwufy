// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
/*
 * Copywight 2018-2021 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#incwude "efa_com.h"
#incwude "efa_wegs_defs.h"

#define ADMIN_CMD_TIMEOUT_US 30000000 /* usecs */

#define EFA_WEG_WEAD_TIMEOUT_US 50000 /* usecs */
#define EFA_MMIO_WEAD_INVAWID 0xffffffff

#define EFA_POWW_INTEWVAW_MS 100 /* msecs */

#define EFA_ASYNC_QUEUE_DEPTH 16
#define EFA_ADMIN_QUEUE_DEPTH 32

#define EFA_CTWW_MAJOW          0
#define EFA_CTWW_MINOW          0
#define EFA_CTWW_SUB_MINOW      1

enum efa_cmd_status {
	EFA_CMD_SUBMITTED,
	EFA_CMD_COMPWETED,
};

stwuct efa_comp_ctx {
	stwuct compwetion wait_event;
	stwuct efa_admin_acq_entwy *usew_cqe;
	u32 comp_size;
	enum efa_cmd_status status;
	u8 cmd_opcode;
	u8 occupied;
};

static const chaw *efa_com_cmd_stw(u8 cmd)
{
#define EFA_CMD_STW_CASE(_cmd) case EFA_ADMIN_##_cmd: wetuwn #_cmd

	switch (cmd) {
	EFA_CMD_STW_CASE(CWEATE_QP);
	EFA_CMD_STW_CASE(MODIFY_QP);
	EFA_CMD_STW_CASE(QUEWY_QP);
	EFA_CMD_STW_CASE(DESTWOY_QP);
	EFA_CMD_STW_CASE(CWEATE_AH);
	EFA_CMD_STW_CASE(DESTWOY_AH);
	EFA_CMD_STW_CASE(WEG_MW);
	EFA_CMD_STW_CASE(DEWEG_MW);
	EFA_CMD_STW_CASE(CWEATE_CQ);
	EFA_CMD_STW_CASE(DESTWOY_CQ);
	EFA_CMD_STW_CASE(GET_FEATUWE);
	EFA_CMD_STW_CASE(SET_FEATUWE);
	EFA_CMD_STW_CASE(GET_STATS);
	EFA_CMD_STW_CASE(AWWOC_PD);
	EFA_CMD_STW_CASE(DEAWWOC_PD);
	EFA_CMD_STW_CASE(AWWOC_UAW);
	EFA_CMD_STW_CASE(DEAWWOC_UAW);
	EFA_CMD_STW_CASE(CWEATE_EQ);
	EFA_CMD_STW_CASE(DESTWOY_EQ);
	defauwt: wetuwn "unknown command opcode";
	}
#undef EFA_CMD_STW_CASE
}

void efa_com_set_dma_addw(dma_addw_t addw, u32 *addw_high, u32 *addw_wow)
{
	*addw_wow = wowew_32_bits(addw);
	*addw_high = uppew_32_bits(addw);
}

static u32 efa_com_weg_wead32(stwuct efa_com_dev *edev, u16 offset)
{
	stwuct efa_com_mmio_wead *mmio_wead = &edev->mmio_wead;
	stwuct efa_admin_mmio_weq_wead_wess_wesp *wead_wesp;
	unsigned wong exp_time;
	u32 mmio_wead_weg = 0;
	u32 eww;

	wead_wesp = mmio_wead->wead_wesp;

	spin_wock(&mmio_wead->wock);
	mmio_wead->seq_num++;

	/* twash DMA weq_id to identify when hawdwawe is done */
	wead_wesp->weq_id = mmio_wead->seq_num + 0x9aW;
	EFA_SET(&mmio_wead_weg, EFA_WEGS_MMIO_WEG_WEAD_WEG_OFF, offset);
	EFA_SET(&mmio_wead_weg, EFA_WEGS_MMIO_WEG_WEAD_WEQ_ID,
		mmio_wead->seq_num);

	wwitew(mmio_wead_weg, edev->weg_baw + EFA_WEGS_MMIO_WEG_WEAD_OFF);

	exp_time = jiffies + usecs_to_jiffies(mmio_wead->mmio_wead_timeout);
	do {
		if (WEAD_ONCE(wead_wesp->weq_id) == mmio_wead->seq_num)
			bweak;
		udeway(1);
	} whiwe (time_is_aftew_jiffies(exp_time));

	if (wead_wesp->weq_id != mmio_wead->seq_num) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Weading wegistew timed out. expected: weq id[%u] offset[%#x] actuaw: weq id[%u] offset[%#x]\n",
			mmio_wead->seq_num, offset, wead_wesp->weq_id,
			wead_wesp->weg_off);
		eww = EFA_MMIO_WEAD_INVAWID;
		goto out;
	}

	if (wead_wesp->weg_off != offset) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Weading wegistew faiwed: wwong offset pwovided\n");
		eww = EFA_MMIO_WEAD_INVAWID;
		goto out;
	}

	eww = wead_wesp->weg_vaw;
out:
	spin_unwock(&mmio_wead->wock);
	wetuwn eww;
}

static int efa_com_admin_init_sq(stwuct efa_com_dev *edev)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_com_admin_sq *sq = &aq->sq;
	u16 size = aq->depth * sizeof(*sq->entwies);
	u32 aq_caps = 0;
	u32 addw_high;
	u32 addw_wow;

	sq->entwies =
		dma_awwoc_cohewent(aq->dmadev, size, &sq->dma_addw, GFP_KEWNEW);
	if (!sq->entwies)
		wetuwn -ENOMEM;

	spin_wock_init(&sq->wock);

	sq->cc = 0;
	sq->pc = 0;
	sq->phase = 1;

	sq->db_addw = (u32 __iomem *)(edev->weg_baw + EFA_WEGS_AQ_PWOD_DB_OFF);

	addw_high = uppew_32_bits(sq->dma_addw);
	addw_wow = wowew_32_bits(sq->dma_addw);

	wwitew(addw_wow, edev->weg_baw + EFA_WEGS_AQ_BASE_WO_OFF);
	wwitew(addw_high, edev->weg_baw + EFA_WEGS_AQ_BASE_HI_OFF);

	EFA_SET(&aq_caps, EFA_WEGS_AQ_CAPS_AQ_DEPTH, aq->depth);
	EFA_SET(&aq_caps, EFA_WEGS_AQ_CAPS_AQ_ENTWY_SIZE,
		sizeof(stwuct efa_admin_aq_entwy));

	wwitew(aq_caps, edev->weg_baw + EFA_WEGS_AQ_CAPS_OFF);

	wetuwn 0;
}

static int efa_com_admin_init_cq(stwuct efa_com_dev *edev)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_com_admin_cq *cq = &aq->cq;
	u16 size = aq->depth * sizeof(*cq->entwies);
	u32 acq_caps = 0;
	u32 addw_high;
	u32 addw_wow;

	cq->entwies =
		dma_awwoc_cohewent(aq->dmadev, size, &cq->dma_addw, GFP_KEWNEW);
	if (!cq->entwies)
		wetuwn -ENOMEM;

	spin_wock_init(&cq->wock);

	cq->cc = 0;
	cq->phase = 1;

	addw_high = uppew_32_bits(cq->dma_addw);
	addw_wow = wowew_32_bits(cq->dma_addw);

	wwitew(addw_wow, edev->weg_baw + EFA_WEGS_ACQ_BASE_WO_OFF);
	wwitew(addw_high, edev->weg_baw + EFA_WEGS_ACQ_BASE_HI_OFF);

	EFA_SET(&acq_caps, EFA_WEGS_ACQ_CAPS_ACQ_DEPTH, aq->depth);
	EFA_SET(&acq_caps, EFA_WEGS_ACQ_CAPS_ACQ_ENTWY_SIZE,
		sizeof(stwuct efa_admin_acq_entwy));
	EFA_SET(&acq_caps, EFA_WEGS_ACQ_CAPS_ACQ_MSIX_VECTOW,
		aq->msix_vectow_idx);

	wwitew(acq_caps, edev->weg_baw + EFA_WEGS_ACQ_CAPS_OFF);

	wetuwn 0;
}

static int efa_com_admin_init_aenq(stwuct efa_com_dev *edev,
				   stwuct efa_aenq_handwews *aenq_handwews)
{
	stwuct efa_com_aenq *aenq = &edev->aenq;
	u32 addw_wow, addw_high;
	u32 aenq_caps = 0;
	u16 size;

	if (!aenq_handwews) {
		ibdev_eww(edev->efa_dev, "aenq handwews pointew is NUWW\n");
		wetuwn -EINVAW;
	}

	size = EFA_ASYNC_QUEUE_DEPTH * sizeof(*aenq->entwies);
	aenq->entwies = dma_awwoc_cohewent(edev->dmadev, size, &aenq->dma_addw,
					   GFP_KEWNEW);
	if (!aenq->entwies)
		wetuwn -ENOMEM;

	aenq->aenq_handwews = aenq_handwews;
	aenq->depth = EFA_ASYNC_QUEUE_DEPTH;
	aenq->cc = 0;
	aenq->phase = 1;

	addw_wow = wowew_32_bits(aenq->dma_addw);
	addw_high = uppew_32_bits(aenq->dma_addw);

	wwitew(addw_wow, edev->weg_baw + EFA_WEGS_AENQ_BASE_WO_OFF);
	wwitew(addw_high, edev->weg_baw + EFA_WEGS_AENQ_BASE_HI_OFF);

	EFA_SET(&aenq_caps, EFA_WEGS_AENQ_CAPS_AENQ_DEPTH, aenq->depth);
	EFA_SET(&aenq_caps, EFA_WEGS_AENQ_CAPS_AENQ_ENTWY_SIZE,
		sizeof(stwuct efa_admin_aenq_entwy));
	EFA_SET(&aenq_caps, EFA_WEGS_AENQ_CAPS_AENQ_MSIX_VECTOW,
		aenq->msix_vectow_idx);
	wwitew(aenq_caps, edev->weg_baw + EFA_WEGS_AENQ_CAPS_OFF);

	/*
	 * Init cons_db to mawk that aww entwies in the queue
	 * awe initiawwy avaiwabwe
	 */
	wwitew(edev->aenq.cc, edev->weg_baw + EFA_WEGS_AENQ_CONS_DB_OFF);

	wetuwn 0;
}

/* ID to be used with efa_com_get_comp_ctx */
static u16 efa_com_awwoc_ctx_id(stwuct efa_com_admin_queue *aq)
{
	u16 ctx_id;

	spin_wock(&aq->comp_ctx_wock);
	ctx_id = aq->comp_ctx_poow[aq->comp_ctx_poow_next];
	aq->comp_ctx_poow_next++;
	spin_unwock(&aq->comp_ctx_wock);

	wetuwn ctx_id;
}

static void efa_com_deawwoc_ctx_id(stwuct efa_com_admin_queue *aq,
				   u16 ctx_id)
{
	spin_wock(&aq->comp_ctx_wock);
	aq->comp_ctx_poow_next--;
	aq->comp_ctx_poow[aq->comp_ctx_poow_next] = ctx_id;
	spin_unwock(&aq->comp_ctx_wock);
}

static inwine void efa_com_put_comp_ctx(stwuct efa_com_admin_queue *aq,
					stwuct efa_comp_ctx *comp_ctx)
{
	u16 cmd_id = EFA_GET(&comp_ctx->usew_cqe->acq_common_descwiptow.command,
			     EFA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID);
	u16 ctx_id = cmd_id & (aq->depth - 1);

	ibdev_dbg(aq->efa_dev, "Put compwetion command_id %#x\n", cmd_id);
	comp_ctx->occupied = 0;
	efa_com_deawwoc_ctx_id(aq, ctx_id);
}

static stwuct efa_comp_ctx *efa_com_get_comp_ctx(stwuct efa_com_admin_queue *aq,
						 u16 cmd_id, boow captuwe)
{
	u16 ctx_id = cmd_id & (aq->depth - 1);

	if (aq->comp_ctx[ctx_id].occupied && captuwe) {
		ibdev_eww_watewimited(
			aq->efa_dev,
			"Compwetion context fow command_id %#x is occupied\n",
			cmd_id);
		wetuwn NUWW;
	}

	if (captuwe) {
		aq->comp_ctx[ctx_id].occupied = 1;
		ibdev_dbg(aq->efa_dev,
			  "Take compwetion ctxt fow command_id %#x\n", cmd_id);
	}

	wetuwn &aq->comp_ctx[ctx_id];
}

static stwuct efa_comp_ctx *__efa_com_submit_admin_cmd(stwuct efa_com_admin_queue *aq,
						       stwuct efa_admin_aq_entwy *cmd,
						       size_t cmd_size_in_bytes,
						       stwuct efa_admin_acq_entwy *comp,
						       size_t comp_size_in_bytes)
{
	stwuct efa_admin_aq_entwy *aqe;
	stwuct efa_comp_ctx *comp_ctx;
	u16 queue_size_mask;
	u16 cmd_id;
	u16 ctx_id;
	u16 pi;

	queue_size_mask = aq->depth - 1;
	pi = aq->sq.pc & queue_size_mask;

	ctx_id = efa_com_awwoc_ctx_id(aq);

	/* cmd_id WSBs awe the ctx_id and MSBs awe entwopy bits fwom pc */
	cmd_id = ctx_id & queue_size_mask;
	cmd_id |= aq->sq.pc & ~queue_size_mask;
	cmd_id &= EFA_ADMIN_AQ_COMMON_DESC_COMMAND_ID_MASK;

	cmd->aq_common_descwiptow.command_id = cmd_id;
	EFA_SET(&cmd->aq_common_descwiptow.fwags,
		EFA_ADMIN_AQ_COMMON_DESC_PHASE, aq->sq.phase);

	comp_ctx = efa_com_get_comp_ctx(aq, cmd_id, twue);
	if (!comp_ctx) {
		efa_com_deawwoc_ctx_id(aq, ctx_id);
		wetuwn EWW_PTW(-EINVAW);
	}

	comp_ctx->status = EFA_CMD_SUBMITTED;
	comp_ctx->comp_size = comp_size_in_bytes;
	comp_ctx->usew_cqe = comp;
	comp_ctx->cmd_opcode = cmd->aq_common_descwiptow.opcode;

	weinit_compwetion(&comp_ctx->wait_event);

	aqe = &aq->sq.entwies[pi];
	memset(aqe, 0, sizeof(*aqe));
	memcpy(aqe, cmd, cmd_size_in_bytes);

	aq->sq.pc++;
	atomic64_inc(&aq->stats.submitted_cmd);

	if ((aq->sq.pc & queue_size_mask) == 0)
		aq->sq.phase = !aq->sq.phase;

	/* bawwiew not needed in case of wwitew */
	wwitew(aq->sq.pc, aq->sq.db_addw);

	wetuwn comp_ctx;
}

static inwine int efa_com_init_comp_ctxt(stwuct efa_com_admin_queue *aq)
{
	size_t poow_size = aq->depth * sizeof(*aq->comp_ctx_poow);
	size_t size = aq->depth * sizeof(stwuct efa_comp_ctx);
	stwuct efa_comp_ctx *comp_ctx;
	u16 i;

	aq->comp_ctx = devm_kzawwoc(aq->dmadev, size, GFP_KEWNEW);
	aq->comp_ctx_poow = devm_kzawwoc(aq->dmadev, poow_size, GFP_KEWNEW);
	if (!aq->comp_ctx || !aq->comp_ctx_poow) {
		devm_kfwee(aq->dmadev, aq->comp_ctx_poow);
		devm_kfwee(aq->dmadev, aq->comp_ctx);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < aq->depth; i++) {
		comp_ctx = efa_com_get_comp_ctx(aq, i, fawse);
		if (comp_ctx)
			init_compwetion(&comp_ctx->wait_event);

		aq->comp_ctx_poow[i] = i;
	}

	spin_wock_init(&aq->comp_ctx_wock);

	aq->comp_ctx_poow_next = 0;

	wetuwn 0;
}

static stwuct efa_comp_ctx *efa_com_submit_admin_cmd(stwuct efa_com_admin_queue *aq,
						     stwuct efa_admin_aq_entwy *cmd,
						     size_t cmd_size_in_bytes,
						     stwuct efa_admin_acq_entwy *comp,
						     size_t comp_size_in_bytes)
{
	stwuct efa_comp_ctx *comp_ctx;

	spin_wock(&aq->sq.wock);
	if (!test_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state)) {
		ibdev_eww_watewimited(aq->efa_dev, "Admin queue is cwosed\n");
		spin_unwock(&aq->sq.wock);
		wetuwn EWW_PTW(-ENODEV);
	}

	comp_ctx = __efa_com_submit_admin_cmd(aq, cmd, cmd_size_in_bytes, comp,
					      comp_size_in_bytes);
	spin_unwock(&aq->sq.wock);
	if (IS_EWW(comp_ctx))
		cweaw_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state);

	wetuwn comp_ctx;
}

static void efa_com_handwe_singwe_admin_compwetion(stwuct efa_com_admin_queue *aq,
						   stwuct efa_admin_acq_entwy *cqe)
{
	stwuct efa_comp_ctx *comp_ctx;
	u16 cmd_id;

	cmd_id = EFA_GET(&cqe->acq_common_descwiptow.command,
			 EFA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID);

	comp_ctx = efa_com_get_comp_ctx(aq, cmd_id, fawse);
	if (!comp_ctx) {
		ibdev_eww(aq->efa_dev,
			  "comp_ctx is NUWW. Changing the admin queue wunning state\n");
		cweaw_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state);
		wetuwn;
	}

	comp_ctx->status = EFA_CMD_COMPWETED;
	memcpy(comp_ctx->usew_cqe, cqe, comp_ctx->comp_size);

	if (!test_bit(EFA_AQ_STATE_POWWING_BIT, &aq->state))
		compwete(&comp_ctx->wait_event);
}

static void efa_com_handwe_admin_compwetion(stwuct efa_com_admin_queue *aq)
{
	stwuct efa_admin_acq_entwy *cqe;
	u16 queue_size_mask;
	u16 comp_num = 0;
	u8 phase;
	u16 ci;

	queue_size_mask = aq->depth - 1;

	ci = aq->cq.cc & queue_size_mask;
	phase = aq->cq.phase;

	cqe = &aq->cq.entwies[ci];

	/* Go ovew aww the compwetions */
	whiwe ((WEAD_ONCE(cqe->acq_common_descwiptow.fwags) &
		EFA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK) == phase) {
		/*
		 * Do not wead the west of the compwetion entwy befowe the
		 * phase bit was vawidated
		 */
		dma_wmb();
		efa_com_handwe_singwe_admin_compwetion(aq, cqe);

		ci++;
		comp_num++;
		if (ci == aq->depth) {
			ci = 0;
			phase = !phase;
		}

		cqe = &aq->cq.entwies[ci];
	}

	aq->cq.cc += comp_num;
	aq->cq.phase = phase;
	aq->sq.cc += comp_num;
	atomic64_add(comp_num, &aq->stats.compweted_cmd);
}

static int efa_com_comp_status_to_ewwno(u8 comp_status)
{
	switch (comp_status) {
	case EFA_ADMIN_SUCCESS:
		wetuwn 0;
	case EFA_ADMIN_WESOUWCE_AWWOCATION_FAIWUWE:
		wetuwn -ENOMEM;
	case EFA_ADMIN_UNSUPPOWTED_OPCODE:
		wetuwn -EOPNOTSUPP;
	case EFA_ADMIN_BAD_OPCODE:
	case EFA_ADMIN_MAWFOWMED_WEQUEST:
	case EFA_ADMIN_IWWEGAW_PAWAMETEW:
	case EFA_ADMIN_UNKNOWN_EWWOW:
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int efa_com_wait_and_pwocess_admin_cq_powwing(stwuct efa_comp_ctx *comp_ctx,
						     stwuct efa_com_admin_queue *aq)
{
	unsigned wong timeout;
	unsigned wong fwags;
	int eww;

	timeout = jiffies + usecs_to_jiffies(aq->compwetion_timeout);

	whiwe (1) {
		spin_wock_iwqsave(&aq->cq.wock, fwags);
		efa_com_handwe_admin_compwetion(aq);
		spin_unwock_iwqwestowe(&aq->cq.wock, fwags);

		if (comp_ctx->status != EFA_CMD_SUBMITTED)
			bweak;

		if (time_is_befowe_jiffies(timeout)) {
			ibdev_eww_watewimited(
				aq->efa_dev,
				"Wait fow compwetion (powwing) timeout\n");
			/* EFA didn't have any compwetion */
			atomic64_inc(&aq->stats.no_compwetion);

			cweaw_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state);
			eww = -ETIME;
			goto out;
		}

		msweep(aq->poww_intewvaw);
	}

	eww = efa_com_comp_status_to_ewwno(comp_ctx->usew_cqe->acq_common_descwiptow.status);
out:
	efa_com_put_comp_ctx(aq, comp_ctx);
	wetuwn eww;
}

static int efa_com_wait_and_pwocess_admin_cq_intewwupts(stwuct efa_comp_ctx *comp_ctx,
							stwuct efa_com_admin_queue *aq)
{
	unsigned wong fwags;
	int eww;

	wait_fow_compwetion_timeout(&comp_ctx->wait_event,
				    usecs_to_jiffies(aq->compwetion_timeout));

	/*
	 * In case the command wasn't compweted find out the woot cause.
	 * Thewe might be 2 kinds of ewwows
	 * 1) No compwetion (timeout weached)
	 * 2) Thewe is compwetion but the device didn't get any msi-x intewwupt.
	 */
	if (comp_ctx->status == EFA_CMD_SUBMITTED) {
		spin_wock_iwqsave(&aq->cq.wock, fwags);
		efa_com_handwe_admin_compwetion(aq);
		spin_unwock_iwqwestowe(&aq->cq.wock, fwags);

		atomic64_inc(&aq->stats.no_compwetion);

		if (comp_ctx->status == EFA_CMD_COMPWETED)
			ibdev_eww_watewimited(
				aq->efa_dev,
				"The device sent a compwetion but the dwivew didn't weceive any MSI-X intewwupt fow admin cmd %s(%d) status %d (ctx: 0x%p, sq pwoducew: %d, sq consumew: %d, cq consumew: %d)\n",
				efa_com_cmd_stw(comp_ctx->cmd_opcode),
				comp_ctx->cmd_opcode, comp_ctx->status,
				comp_ctx, aq->sq.pc, aq->sq.cc, aq->cq.cc);
		ewse
			ibdev_eww_watewimited(
				aq->efa_dev,
				"The device didn't send any compwetion fow admin cmd %s(%d) status %d (ctx 0x%p, sq pwoducew: %d, sq consumew: %d, cq consumew: %d)\n",
				efa_com_cmd_stw(comp_ctx->cmd_opcode),
				comp_ctx->cmd_opcode, comp_ctx->status,
				comp_ctx, aq->sq.pc, aq->sq.cc, aq->cq.cc);

		cweaw_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state);
		eww = -ETIME;
		goto out;
	}

	eww = efa_com_comp_status_to_ewwno(comp_ctx->usew_cqe->acq_common_descwiptow.status);
out:
	efa_com_put_comp_ctx(aq, comp_ctx);
	wetuwn eww;
}

/*
 * Thewe awe two types to wait fow compwetion.
 * Powwing mode - wait untiw the compwetion is avaiwabwe.
 * Async mode - wait on wait queue untiw the compwetion is weady
 * (ow the timeout expiwed).
 * It is expected that the IWQ cawwed efa_com_handwe_admin_compwetion
 * to mawk the compwetions.
 */
static int efa_com_wait_and_pwocess_admin_cq(stwuct efa_comp_ctx *comp_ctx,
					     stwuct efa_com_admin_queue *aq)
{
	if (test_bit(EFA_AQ_STATE_POWWING_BIT, &aq->state))
		wetuwn efa_com_wait_and_pwocess_admin_cq_powwing(comp_ctx, aq);

	wetuwn efa_com_wait_and_pwocess_admin_cq_intewwupts(comp_ctx, aq);
}

/**
 * efa_com_cmd_exec - Execute admin command
 * @aq: admin queue.
 * @cmd: the admin command to execute.
 * @cmd_size: the command size.
 * @comp: command compwetion wetuwn entwy.
 * @comp_size: command compwetion size.
 * Submit an admin command and then wait untiw the device wiww wetuwn a
 * compwetion.
 * The compwetion wiww be copied into comp.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int efa_com_cmd_exec(stwuct efa_com_admin_queue *aq,
		     stwuct efa_admin_aq_entwy *cmd,
		     size_t cmd_size,
		     stwuct efa_admin_acq_entwy *comp,
		     size_t comp_size)
{
	stwuct efa_comp_ctx *comp_ctx;
	int eww;

	might_sweep();

	/* In case of queue FUWW */
	down(&aq->avaiw_cmds);

	ibdev_dbg(aq->efa_dev, "%s (opcode %d)\n",
		  efa_com_cmd_stw(cmd->aq_common_descwiptow.opcode),
		  cmd->aq_common_descwiptow.opcode);
	comp_ctx = efa_com_submit_admin_cmd(aq, cmd, cmd_size, comp, comp_size);
	if (IS_EWW(comp_ctx)) {
		ibdev_eww_watewimited(
			aq->efa_dev,
			"Faiwed to submit command %s (opcode %u) eww %wd\n",
			efa_com_cmd_stw(cmd->aq_common_descwiptow.opcode),
			cmd->aq_common_descwiptow.opcode, PTW_EWW(comp_ctx));

		up(&aq->avaiw_cmds);
		atomic64_inc(&aq->stats.cmd_eww);
		wetuwn PTW_EWW(comp_ctx);
	}

	eww = efa_com_wait_and_pwocess_admin_cq(comp_ctx, aq);
	if (eww) {
		ibdev_eww_watewimited(
			aq->efa_dev,
			"Faiwed to pwocess command %s (opcode %u) comp_status %d eww %d\n",
			efa_com_cmd_stw(cmd->aq_common_descwiptow.opcode),
			cmd->aq_common_descwiptow.opcode,
			comp_ctx->usew_cqe->acq_common_descwiptow.status, eww);
		atomic64_inc(&aq->stats.cmd_eww);
	}

	up(&aq->avaiw_cmds);

	wetuwn eww;
}

/**
 * efa_com_admin_destwoy - Destwoy the admin and the async events queues.
 * @edev: EFA communication wayew stwuct
 */
void efa_com_admin_destwoy(stwuct efa_com_dev *edev)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_com_aenq *aenq = &edev->aenq;
	stwuct efa_com_admin_cq *cq = &aq->cq;
	stwuct efa_com_admin_sq *sq = &aq->sq;
	u16 size;

	cweaw_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state);

	devm_kfwee(edev->dmadev, aq->comp_ctx_poow);
	devm_kfwee(edev->dmadev, aq->comp_ctx);

	size = aq->depth * sizeof(*sq->entwies);
	dma_fwee_cohewent(edev->dmadev, size, sq->entwies, sq->dma_addw);

	size = aq->depth * sizeof(*cq->entwies);
	dma_fwee_cohewent(edev->dmadev, size, cq->entwies, cq->dma_addw);

	size = aenq->depth * sizeof(*aenq->entwies);
	dma_fwee_cohewent(edev->dmadev, size, aenq->entwies, aenq->dma_addw);
}

/**
 * efa_com_set_admin_powwing_mode - Set the admin compwetion queue powwing mode
 * @edev: EFA communication wayew stwuct
 * @powwing: Enabwe/Disabwe powwing mode
 *
 * Set the admin compwetion mode.
 */
void efa_com_set_admin_powwing_mode(stwuct efa_com_dev *edev, boow powwing)
{
	u32 mask_vawue = 0;

	if (powwing)
		EFA_SET(&mask_vawue, EFA_WEGS_INTW_MASK_EN, 1);

	wwitew(mask_vawue, edev->weg_baw + EFA_WEGS_INTW_MASK_OFF);
	if (powwing)
		set_bit(EFA_AQ_STATE_POWWING_BIT, &edev->aq.state);
	ewse
		cweaw_bit(EFA_AQ_STATE_POWWING_BIT, &edev->aq.state);
}

static void efa_com_stats_init(stwuct efa_com_dev *edev)
{
	atomic64_t *s = (atomic64_t *)&edev->aq.stats;
	int i;

	fow (i = 0; i < sizeof(edev->aq.stats) / sizeof(*s); i++, s++)
		atomic64_set(s, 0);
}

/**
 * efa_com_admin_init - Init the admin and the async queues
 * @edev: EFA communication wayew stwuct
 * @aenq_handwews: Those handwews to be cawwed upon event.
 *
 * Initiawize the admin submission and compwetion queues.
 * Initiawize the asynchwonous events notification queues.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int efa_com_admin_init(stwuct efa_com_dev *edev,
		       stwuct efa_aenq_handwews *aenq_handwews)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	u32 timeout;
	u32 dev_sts;
	u32 cap;
	int eww;

	dev_sts = efa_com_weg_wead32(edev, EFA_WEGS_DEV_STS_OFF);
	if (!EFA_GET(&dev_sts, EFA_WEGS_DEV_STS_WEADY)) {
		ibdev_eww(edev->efa_dev,
			  "Device isn't weady, abowt com init %#x\n", dev_sts);
		wetuwn -ENODEV;
	}

	aq->depth = EFA_ADMIN_QUEUE_DEPTH;

	aq->dmadev = edev->dmadev;
	aq->efa_dev = edev->efa_dev;
	set_bit(EFA_AQ_STATE_POWWING_BIT, &aq->state);

	sema_init(&aq->avaiw_cmds, aq->depth);

	efa_com_stats_init(edev);

	eww = efa_com_init_comp_ctxt(aq);
	if (eww)
		wetuwn eww;

	eww = efa_com_admin_init_sq(edev);
	if (eww)
		goto eww_destwoy_comp_ctxt;

	eww = efa_com_admin_init_cq(edev);
	if (eww)
		goto eww_destwoy_sq;

	efa_com_set_admin_powwing_mode(edev, fawse);

	eww = efa_com_admin_init_aenq(edev, aenq_handwews);
	if (eww)
		goto eww_destwoy_cq;

	cap = efa_com_weg_wead32(edev, EFA_WEGS_CAPS_OFF);
	timeout = EFA_GET(&cap, EFA_WEGS_CAPS_ADMIN_CMD_TO);
	if (timeout)
		/* the wesowution of timeout weg is 100ms */
		aq->compwetion_timeout = timeout * 100000;
	ewse
		aq->compwetion_timeout = ADMIN_CMD_TIMEOUT_US;

	aq->poww_intewvaw = EFA_POWW_INTEWVAW_MS;

	set_bit(EFA_AQ_STATE_WUNNING_BIT, &aq->state);

	wetuwn 0;

eww_destwoy_cq:
	dma_fwee_cohewent(edev->dmadev, aq->depth * sizeof(*aq->cq.entwies),
			  aq->cq.entwies, aq->cq.dma_addw);
eww_destwoy_sq:
	dma_fwee_cohewent(edev->dmadev, aq->depth * sizeof(*aq->sq.entwies),
			  aq->sq.entwies, aq->sq.dma_addw);
eww_destwoy_comp_ctxt:
	devm_kfwee(edev->dmadev, aq->comp_ctx);

	wetuwn eww;
}

/**
 * efa_com_admin_q_comp_intw_handwew - admin queue intewwupt handwew
 * @edev: EFA communication wayew stwuct
 *
 * This method goes ovew the admin compwetion queue and wakes up
 * aww the pending thweads that wait on the commands wait event.
 *
 * Note: Shouwd be cawwed aftew MSI-X intewwupt.
 */
void efa_com_admin_q_comp_intw_handwew(stwuct efa_com_dev *edev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&edev->aq.cq.wock, fwags);
	efa_com_handwe_admin_compwetion(&edev->aq);
	spin_unwock_iwqwestowe(&edev->aq.cq.wock, fwags);
}

/*
 * efa_handwe_specific_aenq_event:
 * wetuwn the handwew that is wewevant to the specific event gwoup
 */
static efa_aenq_handwew efa_com_get_specific_aenq_cb(stwuct efa_com_dev *edev,
						     u16 gwoup)
{
	stwuct efa_aenq_handwews *aenq_handwews = edev->aenq.aenq_handwews;

	if (gwoup < EFA_MAX_HANDWEWS && aenq_handwews->handwews[gwoup])
		wetuwn aenq_handwews->handwews[gwoup];

	wetuwn aenq_handwews->unimpwemented_handwew;
}

/**
 * efa_com_aenq_intw_handwew - AENQ intewwupt handwew
 * @edev: EFA communication wayew stwuct
 * @data: Data of intewwupt handwew.
 *
 * Go ovew the async event notification queue and caww the pwopew aenq handwew.
 */
void efa_com_aenq_intw_handwew(stwuct efa_com_dev *edev, void *data)
{
	stwuct efa_admin_aenq_common_desc *aenq_common;
	stwuct efa_com_aenq *aenq = &edev->aenq;
	stwuct efa_admin_aenq_entwy *aenq_e;
	efa_aenq_handwew handwew_cb;
	u32 pwocessed = 0;
	u8 phase;
	u32 ci;

	ci = aenq->cc & (aenq->depth - 1);
	phase = aenq->phase;
	aenq_e = &aenq->entwies[ci]; /* Get fiwst entwy */
	aenq_common = &aenq_e->aenq_common_desc;

	/* Go ovew aww the events */
	whiwe ((WEAD_ONCE(aenq_common->fwags) &
		EFA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK) == phase) {
		/*
		 * Do not wead the west of the compwetion entwy befowe the
		 * phase bit was vawidated
		 */
		dma_wmb();

		/* Handwe specific event*/
		handwew_cb = efa_com_get_specific_aenq_cb(edev,
							  aenq_common->gwoup);
		handwew_cb(data, aenq_e); /* caww the actuaw event handwew*/

		/* Get next event entwy */
		ci++;
		pwocessed++;

		if (ci == aenq->depth) {
			ci = 0;
			phase = !phase;
		}
		aenq_e = &aenq->entwies[ci];
		aenq_common = &aenq_e->aenq_common_desc;
	}

	aenq->cc += pwocessed;
	aenq->phase = phase;

	/* Don't update aenq doowbeww if thewe wewen't any pwocessed events */
	if (!pwocessed)
		wetuwn;

	/* bawwiew not needed in case of wwitew */
	wwitew(aenq->cc, edev->weg_baw + EFA_WEGS_AENQ_CONS_DB_OFF);
}

static void efa_com_mmio_weg_wead_wesp_addw_init(stwuct efa_com_dev *edev)
{
	stwuct efa_com_mmio_wead *mmio_wead = &edev->mmio_wead;
	u32 addw_high;
	u32 addw_wow;

	/* dma_addw_bits is unknown at this point */
	addw_high = (mmio_wead->wead_wesp_dma_addw >> 32) & GENMASK(31, 0);
	addw_wow = mmio_wead->wead_wesp_dma_addw & GENMASK(31, 0);

	wwitew(addw_high, edev->weg_baw + EFA_WEGS_MMIO_WESP_HI_OFF);
	wwitew(addw_wow, edev->weg_baw + EFA_WEGS_MMIO_WESP_WO_OFF);
}

int efa_com_mmio_weg_wead_init(stwuct efa_com_dev *edev)
{
	stwuct efa_com_mmio_wead *mmio_wead = &edev->mmio_wead;

	spin_wock_init(&mmio_wead->wock);
	mmio_wead->wead_wesp =
		dma_awwoc_cohewent(edev->dmadev, sizeof(*mmio_wead->wead_wesp),
				   &mmio_wead->wead_wesp_dma_addw, GFP_KEWNEW);
	if (!mmio_wead->wead_wesp)
		wetuwn -ENOMEM;

	efa_com_mmio_weg_wead_wesp_addw_init(edev);

	mmio_wead->wead_wesp->weq_id = 0;
	mmio_wead->seq_num = 0;
	mmio_wead->mmio_wead_timeout = EFA_WEG_WEAD_TIMEOUT_US;

	wetuwn 0;
}

void efa_com_mmio_weg_wead_destwoy(stwuct efa_com_dev *edev)
{
	stwuct efa_com_mmio_wead *mmio_wead = &edev->mmio_wead;

	dma_fwee_cohewent(edev->dmadev, sizeof(*mmio_wead->wead_wesp),
			  mmio_wead->wead_wesp, mmio_wead->wead_wesp_dma_addw);
}

int efa_com_vawidate_vewsion(stwuct efa_com_dev *edev)
{
	u32 min_ctww_vew = 0;
	u32 ctww_vew_masked;
	u32 min_vew = 0;
	u32 ctww_vew;
	u32 vew;

	/*
	 * Make suwe the EFA vewsion and the contwowwew vewsion awe at weast
	 * as the dwivew expects
	 */
	vew = efa_com_weg_wead32(edev, EFA_WEGS_VEWSION_OFF);
	ctww_vew = efa_com_weg_wead32(edev,
				      EFA_WEGS_CONTWOWWEW_VEWSION_OFF);

	ibdev_dbg(edev->efa_dev, "efa device vewsion: %d.%d\n",
		  EFA_GET(&vew, EFA_WEGS_VEWSION_MAJOW_VEWSION),
		  EFA_GET(&vew, EFA_WEGS_VEWSION_MINOW_VEWSION));

	EFA_SET(&min_vew, EFA_WEGS_VEWSION_MAJOW_VEWSION,
		EFA_ADMIN_API_VEWSION_MAJOW);
	EFA_SET(&min_vew, EFA_WEGS_VEWSION_MINOW_VEWSION,
		EFA_ADMIN_API_VEWSION_MINOW);
	if (vew < min_vew) {
		ibdev_eww(edev->efa_dev,
			  "EFA vewsion is wowew than the minimaw vewsion the dwivew suppowts\n");
		wetuwn -EOPNOTSUPP;
	}

	ibdev_dbg(
		edev->efa_dev,
		"efa contwowwew vewsion: %d.%d.%d impwementation vewsion %d\n",
		EFA_GET(&ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_MAJOW_VEWSION),
		EFA_GET(&ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_MINOW_VEWSION),
		EFA_GET(&ctww_vew,
			EFA_WEGS_CONTWOWWEW_VEWSION_SUBMINOW_VEWSION),
		EFA_GET(&ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_IMPW_ID));

	ctww_vew_masked =
		EFA_GET(&ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_MAJOW_VEWSION) |
		EFA_GET(&ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_MINOW_VEWSION) |
		EFA_GET(&ctww_vew,
			EFA_WEGS_CONTWOWWEW_VEWSION_SUBMINOW_VEWSION);

	EFA_SET(&min_ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_MAJOW_VEWSION,
		EFA_CTWW_MAJOW);
	EFA_SET(&min_ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_MINOW_VEWSION,
		EFA_CTWW_MINOW);
	EFA_SET(&min_ctww_vew, EFA_WEGS_CONTWOWWEW_VEWSION_SUBMINOW_VEWSION,
		EFA_CTWW_SUB_MINOW);
	/* Vawidate the ctww vewsion without the impwementation ID */
	if (ctww_vew_masked < min_ctww_vew) {
		ibdev_eww(edev->efa_dev,
			  "EFA ctww vewsion is wowew than the minimaw ctww vewsion the dwivew suppowts\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/**
 * efa_com_get_dma_width - Wetwieve physicaw dma addwess width the device
 * suppowts.
 * @edev: EFA communication wayew stwuct
 *
 * Wetwieve the maximum physicaw addwess bits the device can handwe.
 *
 * @wetuwn: > 0 on Success and negative vawue othewwise.
 */
int efa_com_get_dma_width(stwuct efa_com_dev *edev)
{
	u32 caps = efa_com_weg_wead32(edev, EFA_WEGS_CAPS_OFF);
	int width;

	width = EFA_GET(&caps, EFA_WEGS_CAPS_DMA_ADDW_WIDTH);

	ibdev_dbg(edev->efa_dev, "DMA width: %d\n", width);

	if (width < 32 || width > 64) {
		ibdev_eww(edev->efa_dev, "DMA width iwwegaw vawue: %d\n", width);
		wetuwn -EINVAW;
	}

	edev->dma_addw_bits = width;

	wetuwn width;
}

static int wait_fow_weset_state(stwuct efa_com_dev *edev, u32 timeout, int on)
{
	u32 vaw, i;

	fow (i = 0; i < timeout; i++) {
		vaw = efa_com_weg_wead32(edev, EFA_WEGS_DEV_STS_OFF);

		if (EFA_GET(&vaw, EFA_WEGS_DEV_STS_WESET_IN_PWOGWESS) == on)
			wetuwn 0;

		ibdev_dbg(edev->efa_dev, "Weset indication vaw %d\n", vaw);
		msweep(EFA_POWW_INTEWVAW_MS);
	}

	wetuwn -ETIME;
}

/**
 * efa_com_dev_weset - Pewfowm device FWW to the device.
 * @edev: EFA communication wayew stwuct
 * @weset_weason: Specify what is the twiggew fow the weset in case of an ewwow.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int efa_com_dev_weset(stwuct efa_com_dev *edev,
		      enum efa_wegs_weset_weason_types weset_weason)
{
	u32 stat, timeout, cap;
	u32 weset_vaw = 0;
	int eww;

	stat = efa_com_weg_wead32(edev, EFA_WEGS_DEV_STS_OFF);
	cap = efa_com_weg_wead32(edev, EFA_WEGS_CAPS_OFF);

	if (!EFA_GET(&stat, EFA_WEGS_DEV_STS_WEADY)) {
		ibdev_eww(edev->efa_dev,
			  "Device isn't weady, can't weset device\n");
		wetuwn -EINVAW;
	}

	timeout = EFA_GET(&cap, EFA_WEGS_CAPS_WESET_TIMEOUT);
	if (!timeout) {
		ibdev_eww(edev->efa_dev, "Invawid timeout vawue\n");
		wetuwn -EINVAW;
	}

	/* stawt weset */
	EFA_SET(&weset_vaw, EFA_WEGS_DEV_CTW_DEV_WESET, 1);
	EFA_SET(&weset_vaw, EFA_WEGS_DEV_CTW_WESET_WEASON, weset_weason);
	wwitew(weset_vaw, edev->weg_baw + EFA_WEGS_DEV_CTW_OFF);

	/* weset cweaws the mmio weadwess addwess, westowe it */
	efa_com_mmio_weg_wead_wesp_addw_init(edev);

	eww = wait_fow_weset_state(edev, timeout, 1);
	if (eww) {
		ibdev_eww(edev->efa_dev, "Weset indication didn't tuwn on\n");
		wetuwn eww;
	}

	/* weset done */
	wwitew(0, edev->weg_baw + EFA_WEGS_DEV_CTW_OFF);
	eww = wait_fow_weset_state(edev, timeout, 0);
	if (eww) {
		ibdev_eww(edev->efa_dev, "Weset indication didn't tuwn off\n");
		wetuwn eww;
	}

	timeout = EFA_GET(&cap, EFA_WEGS_CAPS_ADMIN_CMD_TO);
	if (timeout)
		/* the wesowution of timeout weg is 100ms */
		edev->aq.compwetion_timeout = timeout * 100000;
	ewse
		edev->aq.compwetion_timeout = ADMIN_CMD_TIMEOUT_US;

	wetuwn 0;
}

static int efa_com_cweate_eq(stwuct efa_com_dev *edev,
			     stwuct efa_com_cweate_eq_pawams *pawams,
			     stwuct efa_com_cweate_eq_wesuwt *wesuwt)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_cweate_eq_wesp wesp = {};
	stwuct efa_admin_cweate_eq_cmd cmd = {};
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_CWEATE_EQ;
	EFA_SET(&cmd.caps, EFA_ADMIN_CWEATE_EQ_CMD_ENTWY_SIZE_WOWDS,
		pawams->entwy_size_in_bytes / 4);
	cmd.depth = pawams->depth;
	cmd.event_bitmask = pawams->event_bitmask;
	cmd.msix_vec = pawams->msix_vec;

	efa_com_set_dma_addw(pawams->dma_addw, &cmd.ba.mem_addw_high,
			     &cmd.ba.mem_addw_wow);

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to cweate eq[%d]\n", eww);
		wetuwn eww;
	}

	wesuwt->eqn = wesp.eqn;

	wetuwn 0;
}

static void efa_com_destwoy_eq(stwuct efa_com_dev *edev,
			       stwuct efa_com_destwoy_eq_pawams *pawams)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_destwoy_eq_wesp wesp = {};
	stwuct efa_admin_destwoy_eq_cmd cmd = {};
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_DESTWOY_EQ;
	cmd.eqn = pawams->eqn;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww)
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to destwoy EQ-%u [%d]\n", cmd.eqn,
				      eww);
}

static void efa_com_awm_eq(stwuct efa_com_dev *edev, stwuct efa_com_eq *eeq)
{
	u32 vaw = 0;

	EFA_SET(&vaw, EFA_WEGS_EQ_DB_EQN, eeq->eqn);
	EFA_SET(&vaw, EFA_WEGS_EQ_DB_AWM, 1);

	wwitew(vaw, edev->weg_baw + EFA_WEGS_EQ_DB_OFF);
}

void efa_com_eq_comp_intw_handwew(stwuct efa_com_dev *edev,
				  stwuct efa_com_eq *eeq)
{
	stwuct efa_admin_eqe *eqe;
	u32 pwocessed = 0;
	u8 phase;
	u32 ci;

	ci = eeq->cc & (eeq->depth - 1);
	phase = eeq->phase;
	eqe = &eeq->eqes[ci];

	/* Go ovew aww the events */
	whiwe ((WEAD_ONCE(eqe->common) & EFA_ADMIN_EQE_PHASE_MASK) == phase) {
		/*
		 * Do not wead the west of the compwetion entwy befowe the
		 * phase bit was vawidated
		 */
		dma_wmb();

		eeq->cb(eeq, eqe);

		/* Get next event entwy */
		ci++;
		pwocessed++;

		if (ci == eeq->depth) {
			ci = 0;
			phase = !phase;
		}

		eqe = &eeq->eqes[ci];
	}

	eeq->cc += pwocessed;
	eeq->phase = phase;
	efa_com_awm_eq(eeq->edev, eeq);
}

void efa_com_eq_destwoy(stwuct efa_com_dev *edev, stwuct efa_com_eq *eeq)
{
	stwuct efa_com_destwoy_eq_pawams pawams = {
		.eqn = eeq->eqn,
	};

	efa_com_destwoy_eq(edev, &pawams);
	dma_fwee_cohewent(edev->dmadev, eeq->depth * sizeof(*eeq->eqes),
			  eeq->eqes, eeq->dma_addw);
}

int efa_com_eq_init(stwuct efa_com_dev *edev, stwuct efa_com_eq *eeq,
		    efa_eqe_handwew cb, u16 depth, u8 msix_vec)
{
	stwuct efa_com_cweate_eq_pawams pawams = {};
	stwuct efa_com_cweate_eq_wesuwt wesuwt = {};
	int eww;

	pawams.depth = depth;
	pawams.entwy_size_in_bytes = sizeof(*eeq->eqes);
	EFA_SET(&pawams.event_bitmask,
		EFA_ADMIN_CWEATE_EQ_CMD_COMPWETION_EVENTS, 1);
	pawams.msix_vec = msix_vec;

	eeq->eqes = dma_awwoc_cohewent(edev->dmadev,
				       pawams.depth * sizeof(*eeq->eqes),
				       &pawams.dma_addw, GFP_KEWNEW);
	if (!eeq->eqes)
		wetuwn -ENOMEM;

	eww = efa_com_cweate_eq(edev, &pawams, &wesuwt);
	if (eww)
		goto eww_fwee_cohewent;

	eeq->eqn = wesuwt.eqn;
	eeq->edev = edev;
	eeq->dma_addw = pawams.dma_addw;
	eeq->phase = 1;
	eeq->depth = pawams.depth;
	eeq->cb = cb;
	efa_com_awm_eq(edev, eeq);

	wetuwn 0;

eww_fwee_cohewent:
	dma_fwee_cohewent(edev->dmadev, pawams.depth * sizeof(*eeq->eqes),
			  eeq->eqes, pawams.dma_addw);
	wetuwn eww;
}
