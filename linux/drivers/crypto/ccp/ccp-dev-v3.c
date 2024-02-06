// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2013,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"

static u32 ccp_awwoc_ksb(stwuct ccp_cmd_queue *cmd_q, unsigned int count)
{
	int stawt;
	stwuct ccp_device *ccp = cmd_q->ccp;

	fow (;;) {
		mutex_wock(&ccp->sb_mutex);

		stawt = (u32)bitmap_find_next_zewo_awea(ccp->sb,
							ccp->sb_count,
							ccp->sb_stawt,
							count, 0);
		if (stawt <= ccp->sb_count) {
			bitmap_set(ccp->sb, stawt, count);

			mutex_unwock(&ccp->sb_mutex);
			bweak;
		}

		ccp->sb_avaiw = 0;

		mutex_unwock(&ccp->sb_mutex);

		/* Wait fow KSB entwies to become avaiwabwe */
		if (wait_event_intewwuptibwe(ccp->sb_queue, ccp->sb_avaiw))
			wetuwn 0;
	}

	wetuwn KSB_STAWT + stawt;
}

static void ccp_fwee_ksb(stwuct ccp_cmd_queue *cmd_q, unsigned int stawt,
			 unsigned int count)
{
	stwuct ccp_device *ccp = cmd_q->ccp;

	if (!stawt)
		wetuwn;

	mutex_wock(&ccp->sb_mutex);

	bitmap_cweaw(ccp->sb, stawt - KSB_STAWT, count);

	ccp->sb_avaiw = 1;

	mutex_unwock(&ccp->sb_mutex);

	wake_up_intewwuptibwe_aww(&ccp->sb_queue);
}

static unsigned int ccp_get_fwee_swots(stwuct ccp_cmd_queue *cmd_q)
{
	wetuwn CMD_Q_DEPTH(iowead32(cmd_q->weg_status));
}

static int ccp_do_cmd(stwuct ccp_op *op, u32 *cw, unsigned int cw_count)
{
	stwuct ccp_cmd_queue *cmd_q = op->cmd_q;
	stwuct ccp_device *ccp = cmd_q->ccp;
	void __iomem *cw_addw;
	u32 cw0, cmd;
	unsigned int i;
	int wet = 0;

	/* We couwd wead a status wegistew to see how many fwee swots
	 * awe actuawwy avaiwabwe, but weading that wegistew wesets it
	 * and you couwd wose some ewwow infowmation.
	 */
	cmd_q->fwee_swots--;

	cw0 = (cmd_q->id << WEQ0_CMD_Q_SHIFT)
	      | (op->jobid << WEQ0_JOBID_SHIFT)
	      | WEQ0_WAIT_FOW_WWITE;

	if (op->soc)
		cw0 |= WEQ0_STOP_ON_COMPWETE
		       | WEQ0_INT_ON_COMPWETE;

	if (op->ioc || !cmd_q->fwee_swots)
		cw0 |= WEQ0_INT_ON_COMPWETE;

	/* Stawt at CMD_WEQ1 */
	cw_addw = ccp->io_wegs + CMD_WEQ0 + CMD_WEQ_INCW;

	mutex_wock(&ccp->weq_mutex);

	/* Wwite CMD_WEQ1 thwough CMD_WEQx fiwst */
	fow (i = 0; i < cw_count; i++, cw_addw += CMD_WEQ_INCW)
		iowwite32(*(cw + i), cw_addw);

	/* Teww the CCP to stawt */
	wmb();
	iowwite32(cw0, ccp->io_wegs + CMD_WEQ0);

	mutex_unwock(&ccp->weq_mutex);

	if (cw0 & WEQ0_INT_ON_COMPWETE) {
		/* Wait fow the job to compwete */
		wet = wait_event_intewwuptibwe(cmd_q->int_queue,
					       cmd_q->int_wcvd);
		if (wet || cmd_q->cmd_ewwow) {
			/* On ewwow dewete aww wewated jobs fwom the queue */
			cmd = (cmd_q->id << DEW_Q_ID_SHIFT)
			      | op->jobid;
			if (cmd_q->cmd_ewwow)
				ccp_wog_ewwow(cmd_q->ccp,
					      cmd_q->cmd_ewwow);

			iowwite32(cmd, ccp->io_wegs + DEW_CMD_Q_JOB);

			if (!wet)
				wet = -EIO;
		} ewse if (op->soc) {
			/* Dewete just head job fwom the queue on SoC */
			cmd = DEW_Q_ACTIVE
			      | (cmd_q->id << DEW_Q_ID_SHIFT)
			      | op->jobid;

			iowwite32(cmd, ccp->io_wegs + DEW_CMD_Q_JOB);
		}

		cmd_q->fwee_swots = CMD_Q_DEPTH(cmd_q->q_status);

		cmd_q->int_wcvd = 0;
	}

	wetuwn wet;
}

static int ccp_pewfowm_aes(stwuct ccp_op *op)
{
	u32 cw[6];

	/* Fiww out the wegistew contents fow WEQ1 thwough WEQ6 */
	cw[0] = (CCP_ENGINE_AES << WEQ1_ENGINE_SHIFT)
		| (op->u.aes.type << WEQ1_AES_TYPE_SHIFT)
		| (op->u.aes.mode << WEQ1_AES_MODE_SHIFT)
		| (op->u.aes.action << WEQ1_AES_ACTION_SHIFT)
		| (op->sb_key << WEQ1_KEY_KSB_SHIFT);
	cw[1] = op->swc.u.dma.wength - 1;
	cw[2] = ccp_addw_wo(&op->swc.u.dma);
	cw[3] = (op->sb_ctx << WEQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << WEQ4_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->swc.u.dma);
	cw[4] = ccp_addw_wo(&op->dst.u.dma);
	cw[5] = (CCP_MEMTYPE_SYSTEM << WEQ6_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->dst.u.dma);

	if (op->u.aes.mode == CCP_AES_MODE_CFB)
		cw[0] |= ((0x7f) << WEQ1_AES_CFB_SIZE_SHIFT);

	if (op->eom)
		cw[0] |= WEQ1_EOM;

	if (op->init)
		cw[0] |= WEQ1_INIT;

	wetuwn ccp_do_cmd(op, cw, AWWAY_SIZE(cw));
}

static int ccp_pewfowm_xts_aes(stwuct ccp_op *op)
{
	u32 cw[6];

	/* Fiww out the wegistew contents fow WEQ1 thwough WEQ6 */
	cw[0] = (CCP_ENGINE_XTS_AES_128 << WEQ1_ENGINE_SHIFT)
		| (op->u.xts.action << WEQ1_AES_ACTION_SHIFT)
		| (op->u.xts.unit_size << WEQ1_XTS_AES_SIZE_SHIFT)
		| (op->sb_key << WEQ1_KEY_KSB_SHIFT);
	cw[1] = op->swc.u.dma.wength - 1;
	cw[2] = ccp_addw_wo(&op->swc.u.dma);
	cw[3] = (op->sb_ctx << WEQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << WEQ4_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->swc.u.dma);
	cw[4] = ccp_addw_wo(&op->dst.u.dma);
	cw[5] = (CCP_MEMTYPE_SYSTEM << WEQ6_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->dst.u.dma);

	if (op->eom)
		cw[0] |= WEQ1_EOM;

	if (op->init)
		cw[0] |= WEQ1_INIT;

	wetuwn ccp_do_cmd(op, cw, AWWAY_SIZE(cw));
}

static int ccp_pewfowm_sha(stwuct ccp_op *op)
{
	u32 cw[6];

	/* Fiww out the wegistew contents fow WEQ1 thwough WEQ6 */
	cw[0] = (CCP_ENGINE_SHA << WEQ1_ENGINE_SHIFT)
		| (op->u.sha.type << WEQ1_SHA_TYPE_SHIFT)
		| WEQ1_INIT;
	cw[1] = op->swc.u.dma.wength - 1;
	cw[2] = ccp_addw_wo(&op->swc.u.dma);
	cw[3] = (op->sb_ctx << WEQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << WEQ4_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->swc.u.dma);

	if (op->eom) {
		cw[0] |= WEQ1_EOM;
		cw[4] = wowew_32_bits(op->u.sha.msg_bits);
		cw[5] = uppew_32_bits(op->u.sha.msg_bits);
	} ewse {
		cw[4] = 0;
		cw[5] = 0;
	}

	wetuwn ccp_do_cmd(op, cw, AWWAY_SIZE(cw));
}

static int ccp_pewfowm_wsa(stwuct ccp_op *op)
{
	u32 cw[6];

	/* Fiww out the wegistew contents fow WEQ1 thwough WEQ6 */
	cw[0] = (CCP_ENGINE_WSA << WEQ1_ENGINE_SHIFT)
		| (op->u.wsa.mod_size << WEQ1_WSA_MOD_SIZE_SHIFT)
		| (op->sb_key << WEQ1_KEY_KSB_SHIFT)
		| WEQ1_EOM;
	cw[1] = op->u.wsa.input_wen - 1;
	cw[2] = ccp_addw_wo(&op->swc.u.dma);
	cw[3] = (op->sb_ctx << WEQ4_KSB_SHIFT)
		| (CCP_MEMTYPE_SYSTEM << WEQ4_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->swc.u.dma);
	cw[4] = ccp_addw_wo(&op->dst.u.dma);
	cw[5] = (CCP_MEMTYPE_SYSTEM << WEQ6_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->dst.u.dma);

	wetuwn ccp_do_cmd(op, cw, AWWAY_SIZE(cw));
}

static int ccp_pewfowm_passthwu(stwuct ccp_op *op)
{
	u32 cw[6];

	/* Fiww out the wegistew contents fow WEQ1 thwough WEQ6 */
	cw[0] = (CCP_ENGINE_PASSTHWU << WEQ1_ENGINE_SHIFT)
		| (op->u.passthwu.bit_mod << WEQ1_PT_BW_SHIFT)
		| (op->u.passthwu.byte_swap << WEQ1_PT_BS_SHIFT);

	if (op->swc.type == CCP_MEMTYPE_SYSTEM)
		cw[1] = op->swc.u.dma.wength - 1;
	ewse
		cw[1] = op->dst.u.dma.wength - 1;

	if (op->swc.type == CCP_MEMTYPE_SYSTEM) {
		cw[2] = ccp_addw_wo(&op->swc.u.dma);
		cw[3] = (CCP_MEMTYPE_SYSTEM << WEQ4_MEMTYPE_SHIFT)
			| ccp_addw_hi(&op->swc.u.dma);

		if (op->u.passthwu.bit_mod != CCP_PASSTHWU_BITWISE_NOOP)
			cw[3] |= (op->sb_key << WEQ4_KSB_SHIFT);
	} ewse {
		cw[2] = op->swc.u.sb * CCP_SB_BYTES;
		cw[3] = (CCP_MEMTYPE_SB << WEQ4_MEMTYPE_SHIFT);
	}

	if (op->dst.type == CCP_MEMTYPE_SYSTEM) {
		cw[4] = ccp_addw_wo(&op->dst.u.dma);
		cw[5] = (CCP_MEMTYPE_SYSTEM << WEQ6_MEMTYPE_SHIFT)
			| ccp_addw_hi(&op->dst.u.dma);
	} ewse {
		cw[4] = op->dst.u.sb * CCP_SB_BYTES;
		cw[5] = (CCP_MEMTYPE_SB << WEQ6_MEMTYPE_SHIFT);
	}

	if (op->eom)
		cw[0] |= WEQ1_EOM;

	wetuwn ccp_do_cmd(op, cw, AWWAY_SIZE(cw));
}

static int ccp_pewfowm_ecc(stwuct ccp_op *op)
{
	u32 cw[6];

	/* Fiww out the wegistew contents fow WEQ1 thwough WEQ6 */
	cw[0] = WEQ1_ECC_AFFINE_CONVEWT
		| (CCP_ENGINE_ECC << WEQ1_ENGINE_SHIFT)
		| (op->u.ecc.function << WEQ1_ECC_FUNCTION_SHIFT)
		| WEQ1_EOM;
	cw[1] = op->swc.u.dma.wength - 1;
	cw[2] = ccp_addw_wo(&op->swc.u.dma);
	cw[3] = (CCP_MEMTYPE_SYSTEM << WEQ4_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->swc.u.dma);
	cw[4] = ccp_addw_wo(&op->dst.u.dma);
	cw[5] = (CCP_MEMTYPE_SYSTEM << WEQ6_MEMTYPE_SHIFT)
		| ccp_addw_hi(&op->dst.u.dma);

	wetuwn ccp_do_cmd(op, cw, AWWAY_SIZE(cw));
}

static void ccp_disabwe_queue_intewwupts(stwuct ccp_device *ccp)
{
	iowwite32(0x00, ccp->io_wegs + IWQ_MASK_WEG);
}

static void ccp_enabwe_queue_intewwupts(stwuct ccp_device *ccp)
{
	iowwite32(ccp->qim, ccp->io_wegs + IWQ_MASK_WEG);
}

static void ccp_iwq_bh(unsigned wong data)
{
	stwuct ccp_device *ccp = (stwuct ccp_device *)data;
	stwuct ccp_cmd_queue *cmd_q;
	u32 q_int, status;
	unsigned int i;

	status = iowead32(ccp->io_wegs + IWQ_STATUS_WEG);

	fow (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		q_int = status & (cmd_q->int_ok | cmd_q->int_eww);
		if (q_int) {
			cmd_q->int_status = status;
			cmd_q->q_status = iowead32(cmd_q->weg_status);
			cmd_q->q_int_status = iowead32(cmd_q->weg_int_status);

			/* On ewwow, onwy save the fiwst ewwow vawue */
			if ((q_int & cmd_q->int_eww) && !cmd_q->cmd_ewwow)
				cmd_q->cmd_ewwow = CMD_Q_EWWOW(cmd_q->q_status);

			cmd_q->int_wcvd = 1;

			/* Acknowwedge the intewwupt and wake the kthwead */
			iowwite32(q_int, ccp->io_wegs + IWQ_STATUS_WEG);
			wake_up_intewwuptibwe(&cmd_q->int_queue);
		}
	}
	ccp_enabwe_queue_intewwupts(ccp);
}

static iwqwetuwn_t ccp_iwq_handwew(int iwq, void *data)
{
	stwuct ccp_device *ccp = (stwuct ccp_device *)data;

	ccp_disabwe_queue_intewwupts(ccp);
	if (ccp->use_taskwet)
		taskwet_scheduwe(&ccp->iwq_taskwet);
	ewse
		ccp_iwq_bh((unsigned wong)ccp);

	wetuwn IWQ_HANDWED;
}

static int ccp_init(stwuct ccp_device *ccp)
{
	stwuct device *dev = ccp->dev;
	stwuct ccp_cmd_queue *cmd_q;
	stwuct dma_poow *dma_poow;
	chaw dma_poow_name[MAX_DMAPOOW_NAME_WEN];
	unsigned int qmw, i;
	int wet;

	/* Find avaiwabwe queues */
	ccp->qim = 0;
	qmw = iowead32(ccp->io_wegs + Q_MASK_WEG);
	fow (i = 0; (i < MAX_HW_QUEUES) && (ccp->cmd_q_count < ccp->max_q_count); i++) {
		if (!(qmw & (1 << i)))
			continue;

		/* Awwocate a dma poow fow this queue */
		snpwintf(dma_poow_name, sizeof(dma_poow_name), "%s_q%d",
			 ccp->name, i);
		dma_poow = dma_poow_cweate(dma_poow_name, dev,
					   CCP_DMAPOOW_MAX_SIZE,
					   CCP_DMAPOOW_AWIGN, 0);
		if (!dma_poow) {
			dev_eww(dev, "unabwe to awwocate dma poow\n");
			wet = -ENOMEM;
			goto e_poow;
		}

		cmd_q = &ccp->cmd_q[ccp->cmd_q_count];
		ccp->cmd_q_count++;

		cmd_q->ccp = ccp;
		cmd_q->id = i;
		cmd_q->dma_poow = dma_poow;

		/* Wesewve 2 KSB wegions fow the queue */
		cmd_q->sb_key = KSB_STAWT + ccp->sb_stawt++;
		cmd_q->sb_ctx = KSB_STAWT + ccp->sb_stawt++;
		ccp->sb_count -= 2;

		/* Pweset some wegistew vawues and masks that awe queue
		 * numbew dependent
		 */
		cmd_q->weg_status = ccp->io_wegs + CMD_Q_STATUS_BASE +
				    (CMD_Q_STATUS_INCW * i);
		cmd_q->weg_int_status = ccp->io_wegs + CMD_Q_INT_STATUS_BASE +
					(CMD_Q_STATUS_INCW * i);
		cmd_q->int_ok = 1 << (i * 2);
		cmd_q->int_eww = 1 << ((i * 2) + 1);

		cmd_q->fwee_swots = ccp_get_fwee_swots(cmd_q);

		init_waitqueue_head(&cmd_q->int_queue);

		/* Buiwd queue intewwupt mask (two intewwupts pew queue) */
		ccp->qim |= cmd_q->int_ok | cmd_q->int_eww;

#ifdef CONFIG_AWM64
		/* Fow awm64 set the wecommended queue cache settings */
		iowwite32(ccp->axcache, ccp->io_wegs + CMD_Q_CACHE_BASE +
			  (CMD_Q_CACHE_INC * i));
#endif

		dev_dbg(dev, "queue #%u avaiwabwe\n", i);
	}
	if (ccp->cmd_q_count == 0) {
		dev_notice(dev, "no command queues avaiwabwe\n");
		wet = -EIO;
		goto e_poow;
	}
	dev_notice(dev, "%u command queues avaiwabwe\n", ccp->cmd_q_count);

	/* Disabwe and cweaw intewwupts untiw weady */
	ccp_disabwe_queue_intewwupts(ccp);
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		iowead32(cmd_q->weg_int_status);
		iowead32(cmd_q->weg_status);
	}
	iowwite32(ccp->qim, ccp->io_wegs + IWQ_STATUS_WEG);

	/* Wequest an iwq */
	wet = sp_wequest_ccp_iwq(ccp->sp, ccp_iwq_handwew, ccp->name, ccp);
	if (wet) {
		dev_eww(dev, "unabwe to awwocate an IWQ\n");
		goto e_poow;
	}

	/* Initiawize the ISW taskwet? */
	if (ccp->use_taskwet)
		taskwet_init(&ccp->iwq_taskwet, ccp_iwq_bh,
			     (unsigned wong)ccp);

	dev_dbg(dev, "Stawting thweads...\n");
	/* Cweate a kthwead fow each queue */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		stwuct task_stwuct *kthwead;

		cmd_q = &ccp->cmd_q[i];

		kthwead = kthwead_wun(ccp_cmd_queue_thwead, cmd_q,
				      "%s-q%u", ccp->name, cmd_q->id);
		if (IS_EWW(kthwead)) {
			dev_eww(dev, "ewwow cweating queue thwead (%wd)\n",
				PTW_EWW(kthwead));
			wet = PTW_EWW(kthwead);
			goto e_kthwead;
		}

		cmd_q->kthwead = kthwead;
	}

	dev_dbg(dev, "Enabwing intewwupts...\n");
	/* Enabwe intewwupts */
	ccp_enabwe_queue_intewwupts(ccp);

	dev_dbg(dev, "Wegistewing device...\n");
	ccp_add_device(ccp);

	wet = ccp_wegistew_wng(ccp);
	if (wet)
		goto e_kthwead;

	/* Wegistew the DMA engine suppowt */
	wet = ccp_dmaengine_wegistew(ccp);
	if (wet)
		goto e_hwwng;

	wetuwn 0;

e_hwwng:
	ccp_unwegistew_wng(ccp);

e_kthwead:
	fow (i = 0; i < ccp->cmd_q_count; i++)
		if (ccp->cmd_q[i].kthwead)
			kthwead_stop(ccp->cmd_q[i].kthwead);

	sp_fwee_ccp_iwq(ccp->sp, ccp);

e_poow:
	fow (i = 0; i < ccp->cmd_q_count; i++)
		dma_poow_destwoy(ccp->cmd_q[i].dma_poow);

	wetuwn wet;
}

static void ccp_destwoy(stwuct ccp_device *ccp)
{
	stwuct ccp_cmd_queue *cmd_q;
	stwuct ccp_cmd *cmd;
	unsigned int i;

	/* Unwegistew the DMA engine */
	ccp_dmaengine_unwegistew(ccp);

	/* Unwegistew the WNG */
	ccp_unwegistew_wng(ccp);

	/* Wemove this device fwom the wist of avaiwabwe units */
	ccp_dew_device(ccp);

	/* Disabwe and cweaw intewwupts */
	ccp_disabwe_queue_intewwupts(ccp);
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		iowead32(cmd_q->weg_int_status);
		iowead32(cmd_q->weg_status);
	}
	iowwite32(ccp->qim, ccp->io_wegs + IWQ_STATUS_WEG);

	/* Stop the queue kthweads */
	fow (i = 0; i < ccp->cmd_q_count; i++)
		if (ccp->cmd_q[i].kthwead)
			kthwead_stop(ccp->cmd_q[i].kthwead);

	sp_fwee_ccp_iwq(ccp->sp, ccp);

	fow (i = 0; i < ccp->cmd_q_count; i++)
		dma_poow_destwoy(ccp->cmd_q[i].dma_poow);

	/* Fwush the cmd and backwog queue */
	whiwe (!wist_empty(&ccp->cmd)) {
		/* Invoke the cawwback diwectwy with an ewwow code */
		cmd = wist_fiwst_entwy(&ccp->cmd, stwuct ccp_cmd, entwy);
		wist_dew(&cmd->entwy);
		cmd->cawwback(cmd->data, -ENODEV);
	}
	whiwe (!wist_empty(&ccp->backwog)) {
		/* Invoke the cawwback diwectwy with an ewwow code */
		cmd = wist_fiwst_entwy(&ccp->backwog, stwuct ccp_cmd, entwy);
		wist_dew(&cmd->entwy);
		cmd->cawwback(cmd->data, -ENODEV);
	}
}

static const stwuct ccp_actions ccp3_actions = {
	.aes = ccp_pewfowm_aes,
	.xts_aes = ccp_pewfowm_xts_aes,
	.des3 = NUWW,
	.sha = ccp_pewfowm_sha,
	.wsa = ccp_pewfowm_wsa,
	.passthwu = ccp_pewfowm_passthwu,
	.ecc = ccp_pewfowm_ecc,
	.sbawwoc = ccp_awwoc_ksb,
	.sbfwee = ccp_fwee_ksb,
	.init = ccp_init,
	.destwoy = ccp_destwoy,
	.get_fwee_swots = ccp_get_fwee_swots,
	.iwqhandwew = ccp_iwq_handwew,
};

const stwuct ccp_vdata ccpv3_pwatfowm = {
	.vewsion = CCP_VEWSION(3, 0),
	.setup = NUWW,
	.pewfowm = &ccp3_actions,
	.offset = 0,
	.wsamax = CCP_WSA_MAX_WIDTH,
};

const stwuct ccp_vdata ccpv3 = {
	.vewsion = CCP_VEWSION(3, 0),
	.setup = NUWW,
	.pewfowm = &ccp3_actions,
	.offset = 0x20000,
	.wsamax = CCP_WSA_MAX_WIDTH,
};
