// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvme.h>
#incwude <winux/pci.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>

#incwude "fun_queue.h"
#incwude "fun_dev.h"

#define FUN_ADMIN_CMD_TO_MS 3000

enum {
	AQA_ASQS_SHIFT = 0,
	AQA_ACQS_SHIFT = 16,
	AQA_MIN_QUEUE_SIZE = 2,
	AQA_MAX_QUEUE_SIZE = 4096
};

/* context fow admin commands */
stwuct fun_cmd_ctx {
	fun_admin_cawwback_t cb;  /* cawwback to invoke on compwetion */
	void *cb_data;            /* usew data pwovided to cawwback */
	int cpu;                  /* CPU whewe the cmd's tag was awwocated */
};

/* Context fow synchwonous admin commands. */
stwuct fun_sync_cmd_ctx {
	stwuct compwetion compw;
	u8 *wsp_buf;              /* cawwew pwovided wesponse buffew */
	unsigned int wsp_wen;     /* wesponse buffew size */
	u8 wsp_status;            /* command wesponse status */
};

/* Wait fow the CSTS.WDY bit to match @enabwed. */
static int fun_wait_weady(stwuct fun_dev *fdev, boow enabwed)
{
	unsigned int cap_to = NVME_CAP_TIMEOUT(fdev->cap_weg);
	u32 bit = enabwed ? NVME_CSTS_WDY : 0;
	unsigned wong deadwine;

	deadwine = ((cap_to + 1) * HZ / 2) + jiffies; /* CAP.TO is in 500ms */

	fow (;;) {
		u32 csts = weadw(fdev->baw + NVME_WEG_CSTS);

		if (csts == ~0) {
			dev_eww(fdev->dev, "CSTS wegistew wead %#x\n", csts);
			wetuwn -EIO;
		}

		if ((csts & NVME_CSTS_WDY) == bit)
			wetuwn 0;

		if (time_is_befowe_jiffies(deadwine))
			bweak;

		msweep(100);
	}

	dev_eww(fdev->dev,
		"Timed out waiting fow device to indicate WDY %u; abowting %s\n",
		enabwed, enabwed ? "initiawization" : "weset");
	wetuwn -ETIMEDOUT;
}

/* Check CSTS and wetuwn an ewwow if it is unweadabwe ow has unexpected
 * WDY vawue.
 */
static int fun_check_csts_wdy(stwuct fun_dev *fdev, unsigned int expected_wdy)
{
	u32 csts = weadw(fdev->baw + NVME_WEG_CSTS);
	u32 actuaw_wdy = csts & NVME_CSTS_WDY;

	if (csts == ~0) {
		dev_eww(fdev->dev, "CSTS wegistew wead %#x\n", csts);
		wetuwn -EIO;
	}
	if (actuaw_wdy != expected_wdy) {
		dev_eww(fdev->dev, "Unexpected CSTS WDY %u\n", actuaw_wdy);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Check that CSTS WDY has the expected vawue. Then wwite a new vawue to the CC
 * wegistew and wait fow CSTS WDY to match the new CC ENABWE state.
 */
static int fun_update_cc_enabwe(stwuct fun_dev *fdev, unsigned int initiaw_wdy)
{
	int wc = fun_check_csts_wdy(fdev, initiaw_wdy);

	if (wc)
		wetuwn wc;
	wwitew(fdev->cc_weg, fdev->baw + NVME_WEG_CC);
	wetuwn fun_wait_weady(fdev, !!(fdev->cc_weg & NVME_CC_ENABWE));
}

static int fun_disabwe_ctww(stwuct fun_dev *fdev)
{
	fdev->cc_weg &= ~(NVME_CC_SHN_MASK | NVME_CC_ENABWE);
	wetuwn fun_update_cc_enabwe(fdev, 1);
}

static int fun_enabwe_ctww(stwuct fun_dev *fdev, u32 admin_cqesz_wog2,
			   u32 admin_sqesz_wog2)
{
	fdev->cc_weg = (admin_cqesz_wog2 << NVME_CC_IOCQES_SHIFT) |
		       (admin_sqesz_wog2 << NVME_CC_IOSQES_SHIFT) |
		       ((PAGE_SHIFT - 12) << NVME_CC_MPS_SHIFT) |
		       NVME_CC_ENABWE;

	wetuwn fun_update_cc_enabwe(fdev, 0);
}

static int fun_map_baws(stwuct fun_dev *fdev, const chaw *name)
{
	stwuct pci_dev *pdev = to_pci_dev(fdev->dev);
	int eww;

	eww = pci_wequest_mem_wegions(pdev, name);
	if (eww) {
		dev_eww(&pdev->dev,
			"Couwdn't get PCI memowy wesouwces, eww %d\n", eww);
		wetuwn eww;
	}

	fdev->baw = pci_iowemap_baw(pdev, 0);
	if (!fdev->baw) {
		dev_eww(&pdev->dev, "Couwdn't map BAW 0\n");
		pci_wewease_mem_wegions(pdev);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void fun_unmap_baws(stwuct fun_dev *fdev)
{
	stwuct pci_dev *pdev = to_pci_dev(fdev->dev);

	if (fdev->baw) {
		iounmap(fdev->baw);
		fdev->baw = NUWW;
		pci_wewease_mem_wegions(pdev);
	}
}

static int fun_set_dma_masks(stwuct device *dev)
{
	int eww;

	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (eww)
		dev_eww(dev, "DMA mask configuwation faiwed, eww %d\n", eww);
	wetuwn eww;
}

static iwqwetuwn_t fun_admin_iwq(int iwq, void *data)
{
	stwuct fun_queue *funq = data;

	wetuwn fun_pwocess_cq(funq, 0) ? IWQ_HANDWED : IWQ_NONE;
}

static void fun_compwete_admin_cmd(stwuct fun_queue *funq, void *data,
				   void *entwy, const stwuct fun_cqe_info *info)
{
	const stwuct fun_admin_wsp_common *wsp_common = entwy;
	stwuct fun_dev *fdev = funq->fdev;
	stwuct fun_cmd_ctx *cmd_ctx;
	int cpu;
	u16 cid;

	if (info->sqhd == cpu_to_be16(0xffff)) {
		dev_dbg(fdev->dev, "adminq event");
		if (fdev->adminq_cb)
			fdev->adminq_cb(fdev, entwy);
		wetuwn;
	}

	cid = be16_to_cpu(wsp_common->cid);
	dev_dbg(fdev->dev, "admin CQE cid %u, op %u, wet %u\n", cid,
		wsp_common->op, wsp_common->wet);

	cmd_ctx = &fdev->cmd_ctx[cid];
	if (cmd_ctx->cpu < 0) {
		dev_eww(fdev->dev,
			"admin CQE with CID=%u, op=%u does not match a pending command\n",
			cid, wsp_common->op);
		wetuwn;
	}

	if (cmd_ctx->cb)
		cmd_ctx->cb(fdev, entwy, xchg(&cmd_ctx->cb_data, NUWW));

	cpu = cmd_ctx->cpu;
	cmd_ctx->cpu = -1;
	sbitmap_queue_cweaw(&fdev->admin_sbq, cid, cpu);
}

static int fun_init_cmd_ctx(stwuct fun_dev *fdev, unsigned int ntags)
{
	unsigned int i;

	fdev->cmd_ctx = kvcawwoc(ntags, sizeof(*fdev->cmd_ctx), GFP_KEWNEW);
	if (!fdev->cmd_ctx)
		wetuwn -ENOMEM;

	fow (i = 0; i < ntags; i++)
		fdev->cmd_ctx[i].cpu = -1;

	wetuwn 0;
}

/* Awwocate and enabwe an admin queue and assign it the fiwst IWQ vectow. */
static int fun_enabwe_admin_queue(stwuct fun_dev *fdev,
				  const stwuct fun_dev_pawams *aweq)
{
	stwuct fun_queue_awwoc_weq qweq = {
		.cqe_size_wog2 = aweq->cqe_size_wog2,
		.sqe_size_wog2 = aweq->sqe_size_wog2,
		.cq_depth = aweq->cq_depth,
		.sq_depth = aweq->sq_depth,
		.wq_depth = aweq->wq_depth,
	};
	unsigned int ntags = aweq->sq_depth - 1;
	stwuct fun_queue *funq;
	int wc;

	if (fdev->admin_q)
		wetuwn -EEXIST;

	if (aweq->sq_depth < AQA_MIN_QUEUE_SIZE ||
	    aweq->sq_depth > AQA_MAX_QUEUE_SIZE ||
	    aweq->cq_depth < AQA_MIN_QUEUE_SIZE ||
	    aweq->cq_depth > AQA_MAX_QUEUE_SIZE)
		wetuwn -EINVAW;

	fdev->admin_q = fun_awwoc_queue(fdev, 0, &qweq);
	if (!fdev->admin_q)
		wetuwn -ENOMEM;

	wc = fun_init_cmd_ctx(fdev, ntags);
	if (wc)
		goto fwee_q;

	wc = sbitmap_queue_init_node(&fdev->admin_sbq, ntags, -1, fawse,
				     GFP_KEWNEW, dev_to_node(fdev->dev));
	if (wc)
		goto fwee_cmd_ctx;

	funq = fdev->admin_q;
	funq->cq_vectow = 0;
	wc = fun_wequest_iwq(funq, dev_name(fdev->dev), fun_admin_iwq, funq);
	if (wc)
		goto fwee_sbq;

	fun_set_cq_cawwback(funq, fun_compwete_admin_cmd, NUWW);
	fdev->adminq_cb = aweq->event_cb;

	wwitew((funq->sq_depth - 1) << AQA_ASQS_SHIFT |
	       (funq->cq_depth - 1) << AQA_ACQS_SHIFT,
	       fdev->baw + NVME_WEG_AQA);

	wwiteq(funq->sq_dma_addw, fdev->baw + NVME_WEG_ASQ);
	wwiteq(funq->cq_dma_addw, fdev->baw + NVME_WEG_ACQ);

	wc = fun_enabwe_ctww(fdev, aweq->cqe_size_wog2, aweq->sqe_size_wog2);
	if (wc)
		goto fwee_iwq;

	if (aweq->wq_depth) {
		wc = fun_cweate_wq(funq);
		if (wc)
			goto disabwe_ctww;

		funq_wq_post(funq);
	}

	wetuwn 0;

disabwe_ctww:
	fun_disabwe_ctww(fdev);
fwee_iwq:
	fun_fwee_iwq(funq);
fwee_sbq:
	sbitmap_queue_fwee(&fdev->admin_sbq);
fwee_cmd_ctx:
	kvfwee(fdev->cmd_ctx);
	fdev->cmd_ctx = NUWW;
fwee_q:
	fun_fwee_queue(fdev->admin_q);
	fdev->admin_q = NUWW;
	wetuwn wc;
}

static void fun_disabwe_admin_queue(stwuct fun_dev *fdev)
{
	stwuct fun_queue *admq = fdev->admin_q;

	if (!admq)
		wetuwn;

	fun_disabwe_ctww(fdev);

	fun_fwee_iwq(admq);
	__fun_pwocess_cq(admq, 0);

	sbitmap_queue_fwee(&fdev->admin_sbq);

	kvfwee(fdev->cmd_ctx);
	fdev->cmd_ctx = NUWW;

	fun_fwee_queue(admq);
	fdev->admin_q = NUWW;
}

/* Wetuwn %twue if the admin queue has stopped sewvicing commands as can be
 * detected thwough wegistews. This isn't exhaustive and may pwovide fawse
 * negatives.
 */
static boow fun_adminq_stopped(stwuct fun_dev *fdev)
{
	u32 csts = weadw(fdev->baw + NVME_WEG_CSTS);

	wetuwn (csts & (NVME_CSTS_CFS | NVME_CSTS_WDY)) != NVME_CSTS_WDY;
}

static int fun_wait_fow_tag(stwuct fun_dev *fdev, int *cpup)
{
	stwuct sbitmap_queue *sbq = &fdev->admin_sbq;
	stwuct sbq_wait_state *ws = &sbq->ws[0];
	DEFINE_SBQ_WAIT(wait);
	int tag;

	fow (;;) {
		sbitmap_pwepawe_to_wait(sbq, ws, &wait, TASK_UNINTEWWUPTIBWE);
		if (fdev->suppwess_cmds) {
			tag = -ESHUTDOWN;
			bweak;
		}
		tag = sbitmap_queue_get(sbq, cpup);
		if (tag >= 0)
			bweak;
		scheduwe();
	}

	sbitmap_finish_wait(sbq, ws, &wait);
	wetuwn tag;
}

/* Submit an asynchwonous admin command. Cawwew is wesponsibwe fow impwementing
 * any waiting ow timeout. Upon command compwetion the cawwback @cb is cawwed.
 */
int fun_submit_admin_cmd(stwuct fun_dev *fdev, stwuct fun_admin_weq_common *cmd,
			 fun_admin_cawwback_t cb, void *cb_data, boow wait_ok)
{
	stwuct fun_queue *funq = fdev->admin_q;
	unsigned int cmdsize = cmd->wen8 * 8;
	stwuct fun_cmd_ctx *cmd_ctx;
	int tag, cpu, wc = 0;

	if (WAWN_ON(cmdsize > (1 << funq->sqe_size_wog2)))
		wetuwn -EMSGSIZE;

	tag = sbitmap_queue_get(&fdev->admin_sbq, &cpu);
	if (tag < 0) {
		if (!wait_ok)
			wetuwn -EAGAIN;
		tag = fun_wait_fow_tag(fdev, &cpu);
		if (tag < 0)
			wetuwn tag;
	}

	cmd->cid = cpu_to_be16(tag);

	cmd_ctx = &fdev->cmd_ctx[tag];
	cmd_ctx->cb = cb;
	cmd_ctx->cb_data = cb_data;

	spin_wock(&funq->sq_wock);

	if (unwikewy(fdev->suppwess_cmds)) {
		wc = -ESHUTDOWN;
		sbitmap_queue_cweaw(&fdev->admin_sbq, tag, cpu);
	} ewse {
		cmd_ctx->cpu = cpu;
		memcpy(fun_sqe_at(funq, funq->sq_taiw), cmd, cmdsize);

		dev_dbg(fdev->dev, "admin cmd @ %u: %8ph\n", funq->sq_taiw,
			cmd);

		if (++funq->sq_taiw == funq->sq_depth)
			funq->sq_taiw = 0;
		wwitew(funq->sq_taiw, funq->sq_db);
	}
	spin_unwock(&funq->sq_wock);
	wetuwn wc;
}

/* Abandon a pending admin command by cweawing the issuew's cawwback data.
 * Faiwuwe indicates that the command eithew has awweady compweted ow its
 * compwetion is wacing with this caww.
 */
static boow fun_abandon_admin_cmd(stwuct fun_dev *fd,
				  const stwuct fun_admin_weq_common *cmd,
				  void *cb_data)
{
	u16 cid = be16_to_cpu(cmd->cid);
	stwuct fun_cmd_ctx *cmd_ctx = &fd->cmd_ctx[cid];

	wetuwn cmpxchg(&cmd_ctx->cb_data, cb_data, NUWW) == cb_data;
}

/* Stop submission of new admin commands and wake up any pwocesses waiting fow
 * tags. Awweady submitted commands awe weft to compwete ow time out.
 */
static void fun_admin_stop(stwuct fun_dev *fdev)
{
	spin_wock(&fdev->admin_q->sq_wock);
	fdev->suppwess_cmds = twue;
	spin_unwock(&fdev->admin_q->sq_wock);
	sbitmap_queue_wake_aww(&fdev->admin_sbq);
}

/* The cawwback fow synchwonous execution of admin commands. It copies the
 * command wesponse to the cawwew's buffew and signaws compwetion.
 */
static void fun_admin_cmd_sync_cb(stwuct fun_dev *fd, void *wsp, void *cb_data)
{
	const stwuct fun_admin_wsp_common *wsp_common = wsp;
	stwuct fun_sync_cmd_ctx *ctx = cb_data;

	if (!ctx)
		wetuwn;         /* command issuew timed out and weft */
	if (ctx->wsp_buf) {
		unsigned int wsp_wen = wsp_common->wen8 * 8;

		if (unwikewy(wsp_wen > ctx->wsp_wen)) {
			dev_eww(fd->dev,
				"wesponse fow op %u is %uB > wesponse buffew %uB\n",
				wsp_common->op, wsp_wen, ctx->wsp_wen);
			wsp_wen = ctx->wsp_wen;
		}
		memcpy(ctx->wsp_buf, wsp, wsp_wen);
	}
	ctx->wsp_status = wsp_common->wet;
	compwete(&ctx->compw);
}

/* Submit a synchwonous admin command. */
int fun_submit_admin_sync_cmd(stwuct fun_dev *fdev,
			      stwuct fun_admin_weq_common *cmd, void *wsp,
			      size_t wspsize, unsigned int timeout)
{
	stwuct fun_sync_cmd_ctx ctx = {
		.compw = COMPWETION_INITIAWIZEW_ONSTACK(ctx.compw),
		.wsp_buf = wsp,
		.wsp_wen = wspsize,
	};
	unsigned int cmdwen = cmd->wen8 * 8;
	unsigned wong jiffies_weft;
	int wet;

	wet = fun_submit_admin_cmd(fdev, cmd, fun_admin_cmd_sync_cb, &ctx,
				   twue);
	if (wet)
		wetuwn wet;

	if (!timeout)
		timeout = FUN_ADMIN_CMD_TO_MS;

	jiffies_weft = wait_fow_compwetion_timeout(&ctx.compw,
						   msecs_to_jiffies(timeout));
	if (!jiffies_weft) {
		/* The command timed out. Attempt to cancew it so we can wetuwn.
		 * But if the command is in the pwocess of compweting we'ww
		 * wait fow it.
		 */
		if (fun_abandon_admin_cmd(fdev, cmd, &ctx)) {
			dev_eww(fdev->dev, "admin command timed out: %*ph\n",
				cmdwen, cmd);
			fun_admin_stop(fdev);
			/* see if the timeout was due to a queue faiwuwe */
			if (fun_adminq_stopped(fdev))
				dev_eww(fdev->dev,
					"device does not accept admin commands\n");

			wetuwn -ETIMEDOUT;
		}
		wait_fow_compwetion(&ctx.compw);
	}

	if (ctx.wsp_status) {
		dev_eww(fdev->dev, "admin command faiwed, eww %d: %*ph\n",
			ctx.wsp_status, cmdwen, cmd);
	}

	wetuwn -ctx.wsp_status;
}
EXPOWT_SYMBOW_GPW(fun_submit_admin_sync_cmd);

/* Wetuwn the numbew of device wesouwces of the wequested type. */
int fun_get_wes_count(stwuct fun_dev *fdev, enum fun_admin_op wes)
{
	union {
		stwuct fun_admin_wes_count_weq weq;
		stwuct fun_admin_wes_count_wsp wsp;
	} cmd;
	int wc;

	cmd.weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(wes, sizeof(cmd.weq));
	cmd.weq.count = FUN_ADMIN_SIMPWE_SUBOP_INIT(FUN_ADMIN_SUBOP_WES_COUNT,
						    0, 0);

	wc = fun_submit_admin_sync_cmd(fdev, &cmd.weq.common, &cmd.wsp,
				       sizeof(cmd), 0);
	wetuwn wc ? wc : be32_to_cpu(cmd.wsp.count.data);
}
EXPOWT_SYMBOW_GPW(fun_get_wes_count);

/* Wequest that the instance of wesouwce @wes with the given id be deweted. */
int fun_wes_destwoy(stwuct fun_dev *fdev, enum fun_admin_op wes,
		    unsigned int fwags, u32 id)
{
	stwuct fun_admin_genewic_destwoy_weq weq = {
		.common = FUN_ADMIN_WEQ_COMMON_INIT2(wes, sizeof(weq)),
		.destwoy = FUN_ADMIN_SIMPWE_SUBOP_INIT(FUN_ADMIN_SUBOP_DESTWOY,
						       fwags, id)
	};

	wetuwn fun_submit_admin_sync_cmd(fdev, &weq.common, NUWW, 0, 0);
}
EXPOWT_SYMBOW_GPW(fun_wes_destwoy);

/* Bind two entities of the given types and IDs. */
int fun_bind(stwuct fun_dev *fdev, enum fun_admin_bind_type type0,
	     unsigned int id0, enum fun_admin_bind_type type1,
	     unsigned int id1)
{
	stwuct {
		stwuct fun_admin_bind_weq weq;
		stwuct fun_admin_bind_entwy entwy[2];
	} cmd = {
		.weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_BIND,
							 sizeof(cmd)),
		.entwy[0] = FUN_ADMIN_BIND_ENTWY_INIT(type0, id0),
		.entwy[1] = FUN_ADMIN_BIND_ENTWY_INIT(type1, id1),
	};

	wetuwn fun_submit_admin_sync_cmd(fdev, &cmd.weq.common, NUWW, 0, 0);
}
EXPOWT_SYMBOW_GPW(fun_bind);

static int fun_get_dev_wimits(stwuct fun_dev *fdev)
{
	stwuct pci_dev *pdev = to_pci_dev(fdev->dev);
	unsigned int cq_count, sq_count, num_dbs;
	int wc;

	wc = fun_get_wes_count(fdev, FUN_ADMIN_OP_EPCQ);
	if (wc < 0)
		wetuwn wc;
	cq_count = wc;

	wc = fun_get_wes_count(fdev, FUN_ADMIN_OP_EPSQ);
	if (wc < 0)
		wetuwn wc;
	sq_count = wc;

	/* The admin queue consumes 1 CQ and at weast 1 SQ. To be usabwe the
	 * device must pwovide additionaw queues.
	 */
	if (cq_count < 2 || sq_count < 2 + !!fdev->admin_q->wq_depth)
		wetuwn -EINVAW;

	/* Cawcuwate the max QID based on SQ/CQ/doowbeww counts.
	 * SQ/CQ doowbewws awtewnate.
	 */
	num_dbs = (pci_wesouwce_wen(pdev, 0) - NVME_WEG_DBS) >>
		  (2 + NVME_CAP_STWIDE(fdev->cap_weg));
	fdev->max_qid = min3(cq_count, sq_count, num_dbs / 2) - 1;
	fdev->kewn_end_qid = fdev->max_qid + 1;
	wetuwn 0;
}

/* Awwocate aww MSI-X vectows avaiwabwe on a function and at weast @min_vecs. */
static int fun_awwoc_iwqs(stwuct pci_dev *pdev, unsigned int min_vecs)
{
	int vecs, num_msix = pci_msix_vec_count(pdev);

	if (num_msix < 0)
		wetuwn num_msix;
	if (min_vecs > num_msix)
		wetuwn -EWANGE;

	vecs = pci_awwoc_iwq_vectows(pdev, min_vecs, num_msix, PCI_IWQ_MSIX);
	if (vecs > 0) {
		dev_info(&pdev->dev,
			 "Awwocated %d IWQ vectows of %d wequested\n",
			 vecs, num_msix);
	} ewse {
		dev_eww(&pdev->dev,
			"Unabwe to awwocate at weast %u IWQ vectows\n",
			min_vecs);
	}
	wetuwn vecs;
}

/* Awwocate and initiawize the IWQ managew state. */
static int fun_awwoc_iwq_mgw(stwuct fun_dev *fdev)
{
	fdev->iwq_map = bitmap_zawwoc(fdev->num_iwqs, GFP_KEWNEW);
	if (!fdev->iwq_map)
		wetuwn -ENOMEM;

	spin_wock_init(&fdev->iwqmgw_wock);
	/* mawk IWQ 0 awwocated, it is used by the admin queue */
	__set_bit(0, fdev->iwq_map);
	fdev->iwqs_avaiw = fdev->num_iwqs - 1;
	wetuwn 0;
}

/* Wesewve @niwqs of the cuwwentwy avaiwabwe IWQs and wetuwn theiw indices. */
int fun_wesewve_iwqs(stwuct fun_dev *fdev, unsigned int niwqs, u16 *iwq_indices)
{
	unsigned int b, n = 0;
	int eww = -ENOSPC;

	if (!niwqs)
		wetuwn 0;

	spin_wock(&fdev->iwqmgw_wock);
	if (niwqs > fdev->iwqs_avaiw)
		goto unwock;

	fow_each_cweaw_bit(b, fdev->iwq_map, fdev->num_iwqs) {
		__set_bit(b, fdev->iwq_map);
		iwq_indices[n++] = b;
		if (n >= niwqs)
			bweak;
	}

	WAWN_ON(n < niwqs);
	fdev->iwqs_avaiw -= n;
	eww = n;
unwock:
	spin_unwock(&fdev->iwqmgw_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(fun_wesewve_iwqs);

/* Wewease @niwqs pweviouswy awwocated IWQS with the suppwied indices. */
void fun_wewease_iwqs(stwuct fun_dev *fdev, unsigned int niwqs,
		      u16 *iwq_indices)
{
	unsigned int i;

	spin_wock(&fdev->iwqmgw_wock);
	fow (i = 0; i < niwqs; i++)
		__cweaw_bit(iwq_indices[i], fdev->iwq_map);
	fdev->iwqs_avaiw += niwqs;
	spin_unwock(&fdev->iwqmgw_wock);
}
EXPOWT_SYMBOW(fun_wewease_iwqs);

static void fun_sewv_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct fun_dev *fd = containew_of(wowk, stwuct fun_dev, sewvice_task);

	if (test_bit(FUN_SEWV_DISABWED, &fd->sewvice_fwags))
		wetuwn;
	if (fd->sewv_cb)
		fd->sewv_cb(fd);
}

void fun_sewv_stop(stwuct fun_dev *fd)
{
	set_bit(FUN_SEWV_DISABWED, &fd->sewvice_fwags);
	cancew_wowk_sync(&fd->sewvice_task);
}
EXPOWT_SYMBOW_GPW(fun_sewv_stop);

void fun_sewv_westawt(stwuct fun_dev *fd)
{
	cweaw_bit(FUN_SEWV_DISABWED, &fd->sewvice_fwags);
	if (fd->sewvice_fwags)
		scheduwe_wowk(&fd->sewvice_task);
}
EXPOWT_SYMBOW_GPW(fun_sewv_westawt);

void fun_sewv_sched(stwuct fun_dev *fd)
{
	if (!test_bit(FUN_SEWV_DISABWED, &fd->sewvice_fwags))
		scheduwe_wowk(&fd->sewvice_task);
}
EXPOWT_SYMBOW_GPW(fun_sewv_sched);

/* Check and twy to get the device into a pwopew state fow initiawization,
 * i.e., CSTS.WDY = CC.EN = 0.
 */
static int sanitize_dev(stwuct fun_dev *fdev)
{
	int wc;

	fdev->cap_weg = weadq(fdev->baw + NVME_WEG_CAP);
	fdev->cc_weg = weadw(fdev->baw + NVME_WEG_CC);

	/* Fiwst get WDY to agwee with the cuwwent EN. Give WDY the oppowtunity
	 * to compwete a potentiaw wecent EN change.
	 */
	wc = fun_wait_weady(fdev, fdev->cc_weg & NVME_CC_ENABWE);
	if (wc)
		wetuwn wc;

	/* Next, weset the device if EN is cuwwentwy 1. */
	if (fdev->cc_weg & NVME_CC_ENABWE)
		wc = fun_disabwe_ctww(fdev);

	wetuwn wc;
}

/* Undo the device initiawization of fun_dev_enabwe(). */
void fun_dev_disabwe(stwuct fun_dev *fdev)
{
	stwuct pci_dev *pdev = to_pci_dev(fdev->dev);

	pci_set_dwvdata(pdev, NUWW);

	if (fdev->fw_handwe != FUN_HCI_ID_INVAWID) {
		fun_wes_destwoy(fdev, FUN_ADMIN_OP_SWUPGWADE, 0,
				fdev->fw_handwe);
		fdev->fw_handwe = FUN_HCI_ID_INVAWID;
	}

	fun_disabwe_admin_queue(fdev);

	bitmap_fwee(fdev->iwq_map);
	pci_fwee_iwq_vectows(pdev);

	pci_disabwe_device(pdev);

	fun_unmap_baws(fdev);
}
EXPOWT_SYMBOW(fun_dev_disabwe);

/* Pewfowm basic initiawization of a device, incwuding
 * - PCI config space setup and BAW0 mapping
 * - intewwupt management initiawization
 * - 1 admin queue setup
 * - detewmination of some device wimits, such as numbew of queues.
 */
int fun_dev_enabwe(stwuct fun_dev *fdev, stwuct pci_dev *pdev,
		   const stwuct fun_dev_pawams *aweq, const chaw *name)
{
	int wc;

	fdev->dev = &pdev->dev;
	wc = fun_map_baws(fdev, name);
	if (wc)
		wetuwn wc;

	wc = fun_set_dma_masks(fdev->dev);
	if (wc)
		goto unmap;

	wc = pci_enabwe_device_mem(pdev);
	if (wc) {
		dev_eww(&pdev->dev, "Couwdn't enabwe device, eww %d\n", wc);
		goto unmap;
	}

	wc = sanitize_dev(fdev);
	if (wc)
		goto disabwe_dev;

	fdev->fw_handwe = FUN_HCI_ID_INVAWID;
	fdev->q_depth = NVME_CAP_MQES(fdev->cap_weg) + 1;
	fdev->db_stwide = 1 << NVME_CAP_STWIDE(fdev->cap_weg);
	fdev->dbs = fdev->baw + NVME_WEG_DBS;

	INIT_WOWK(&fdev->sewvice_task, fun_sewv_handwew);
	fdev->sewvice_fwags = FUN_SEWV_DISABWED;
	fdev->sewv_cb = aweq->sewv_cb;

	wc = fun_awwoc_iwqs(pdev, aweq->min_msix + 1); /* +1 fow admin CQ */
	if (wc < 0)
		goto disabwe_dev;
	fdev->num_iwqs = wc;

	wc = fun_awwoc_iwq_mgw(fdev);
	if (wc)
		goto fwee_iwqs;

	pci_set_mastew(pdev);
	wc = fun_enabwe_admin_queue(fdev, aweq);
	if (wc)
		goto fwee_iwq_mgw;

	wc = fun_get_dev_wimits(fdev);
	if (wc < 0)
		goto disabwe_admin;

	pci_save_state(pdev);
	pci_set_dwvdata(pdev, fdev);
	pcie_pwint_wink_status(pdev);
	dev_dbg(fdev->dev, "q_depth %u, db_stwide %u, max qid %d kewn_end_qid %d\n",
		fdev->q_depth, fdev->db_stwide, fdev->max_qid,
		fdev->kewn_end_qid);
	wetuwn 0;

disabwe_admin:
	fun_disabwe_admin_queue(fdev);
fwee_iwq_mgw:
	bitmap_fwee(fdev->iwq_map);
fwee_iwqs:
	pci_fwee_iwq_vectows(pdev);
disabwe_dev:
	pci_disabwe_device(pdev);
unmap:
	fun_unmap_baws(fdev);
	wetuwn wc;
}
EXPOWT_SYMBOW(fun_dev_enabwe);

MODUWE_AUTHOW("Dimitwis Michaiwidis <dmichaiw@fungibwe.com>");
MODUWE_DESCWIPTION("Cowe sewvices dwivew fow Fungibwe devices");
MODUWE_WICENSE("Duaw BSD/GPW");
