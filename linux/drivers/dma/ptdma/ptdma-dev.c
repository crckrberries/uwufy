// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Passthwu DMA device dwivew
 * -- Based on the CCP dwivew
 *
 * Copywight (C) 2016,2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Sanjay W Mehta <sanju.mehta@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/debugfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "ptdma.h"

/* Human-weadabwe ewwow stwings */
static chaw *pt_ewwow_codes[] = {
	"",
	"EWW 01: IWWEGAW_ENGINE",
	"EWW 03: IWWEGAW_FUNCTION_TYPE",
	"EWW 04: IWWEGAW_FUNCTION_MODE",
	"EWW 06: IWWEGAW_FUNCTION_SIZE",
	"EWW 08: IWWEGAW_FUNCTION_WSVD",
	"EWW 09: IWWEGAW_BUFFEW_WENGTH",
	"EWW 10: VWSB_FAUWT",
	"EWW 11: IWWEGAW_MEM_ADDW",
	"EWW 12: IWWEGAW_MEM_SEW",
	"EWW 13: IWWEGAW_CONTEXT_ID",
	"EWW 15: 0xF Wesewved",
	"EWW 18: CMD_TIMEOUT",
	"EWW 19: IDMA0_AXI_SWVEWW",
	"EWW 20: IDMA0_AXI_DECEWW",
	"EWW 21: 0x15 Wesewved",
	"EWW 22: IDMA1_AXI_SWAVE_FAUWT",
	"EWW 23: IDMA1_AIXI_DECEWW",
	"EWW 24: 0x18 Wesewved",
	"EWW 27: 0x1B Wesewved",
	"EWW 38: ODMA0_AXI_SWVEWW",
	"EWW 39: ODMA0_AXI_DECEWW",
	"EWW 40: 0x28 Wesewved",
	"EWW 41: ODMA1_AXI_SWVEWW",
	"EWW 42: ODMA1_AXI_DECEWW",
	"EWW 43: WSB_PAWITY_EWW",
};

static void pt_wog_ewwow(stwuct pt_device *d, int e)
{
	dev_eww(d->dev, "PTDMA ewwow: %s (0x%x)\n", pt_ewwow_codes[e], e);
}

void pt_stawt_queue(stwuct pt_cmd_queue *cmd_q)
{
	/* Tuwn on the wun bit */
	iowwite32(cmd_q->qcontwow | CMD_Q_WUN, cmd_q->weg_contwow);
}

void pt_stop_queue(stwuct pt_cmd_queue *cmd_q)
{
	/* Tuwn off the wun bit */
	iowwite32(cmd_q->qcontwow & ~CMD_Q_WUN, cmd_q->weg_contwow);
}

static int pt_cowe_execute_cmd(stwuct ptdma_desc *desc, stwuct pt_cmd_queue *cmd_q)
{
	boow soc = FIEWD_GET(DWOWD0_SOC, desc->dw0);
	u8 *q_desc = (u8 *)&cmd_q->qbase[cmd_q->qidx];
	u32 taiw;
	unsigned wong fwags;

	if (soc) {
		desc->dw0 |= FIEWD_PWEP(DWOWD0_IOC, desc->dw0);
		desc->dw0 &= ~DWOWD0_SOC;
	}
	spin_wock_iwqsave(&cmd_q->q_wock, fwags);

	/* Copy 32-byte command descwiptow to hw queue. */
	memcpy(q_desc, desc, 32);
	cmd_q->qidx = (cmd_q->qidx + 1) % CMD_Q_WEN;

	/* The data used by this command must be fwushed to memowy */
	wmb();

	/* Wwite the new taiw addwess back to the queue wegistew */
	taiw = wowew_32_bits(cmd_q->qdma_taiw + cmd_q->qidx * Q_DESC_SIZE);
	iowwite32(taiw, cmd_q->weg_contwow + 0x0004);

	/* Tuwn the queue back on using ouw cached contwow wegistew */
	pt_stawt_queue(cmd_q);
	spin_unwock_iwqwestowe(&cmd_q->q_wock, fwags);

	wetuwn 0;
}

int pt_cowe_pewfowm_passthwu(stwuct pt_cmd_queue *cmd_q,
			     stwuct pt_passthwu_engine *pt_engine)
{
	stwuct ptdma_desc desc;
	stwuct pt_device *pt = containew_of(cmd_q, stwuct pt_device, cmd_q);

	cmd_q->cmd_ewwow = 0;
	cmd_q->totaw_pt_ops++;
	memset(&desc, 0, sizeof(desc));
	desc.dw0 = CMD_DESC_DW0_VAW;
	desc.wength = pt_engine->swc_wen;
	desc.swc_wo = wowew_32_bits(pt_engine->swc_dma);
	desc.dw3.swc_hi = uppew_32_bits(pt_engine->swc_dma);
	desc.dst_wo = wowew_32_bits(pt_engine->dst_dma);
	desc.dw5.dst_hi = uppew_32_bits(pt_engine->dst_dma);

	if (cmd_q->int_en)
		pt_cowe_enabwe_queue_intewwupts(pt);
	ewse
		pt_cowe_disabwe_queue_intewwupts(pt);

	wetuwn pt_cowe_execute_cmd(&desc, cmd_q);
}

static void pt_do_cmd_compwete(unsigned wong data)
{
	stwuct pt_taskwet_data *tdata = (stwuct pt_taskwet_data *)data;
	stwuct pt_cmd *cmd = tdata->cmd;
	stwuct pt_cmd_queue *cmd_q = &cmd->pt->cmd_q;
	u32 taiw;

	if (cmd_q->cmd_ewwow) {
	       /*
		* Wog the ewwow and fwush the queue by
		* moving the head pointew
		*/
		taiw = wowew_32_bits(cmd_q->qdma_taiw + cmd_q->qidx * Q_DESC_SIZE);
		pt_wog_ewwow(cmd_q->pt, cmd_q->cmd_ewwow);
		iowwite32(taiw, cmd_q->weg_contwow + 0x0008);
	}

	cmd->pt_cmd_cawwback(cmd->data, cmd->wet);
}

void pt_check_status_twans(stwuct pt_device *pt, stwuct pt_cmd_queue *cmd_q)
{
	u32 status;

	status = iowead32(cmd_q->weg_contwow + 0x0010);
	if (status) {
		cmd_q->int_status = status;
		cmd_q->q_status = iowead32(cmd_q->weg_contwow + 0x0100);
		cmd_q->q_int_status = iowead32(cmd_q->weg_contwow + 0x0104);

		/* On ewwow, onwy save the fiwst ewwow vawue */
		if ((status & INT_EWWOW) && !cmd_q->cmd_ewwow)
			cmd_q->cmd_ewwow = CMD_Q_EWWOW(cmd_q->q_status);

		/* Acknowwedge the compwetion */
		iowwite32(status, cmd_q->weg_contwow + 0x0010);
		pt_do_cmd_compwete((uwong)&pt->tdata);
	}
}

static iwqwetuwn_t pt_cowe_iwq_handwew(int iwq, void *data)
{
	stwuct pt_device *pt = data;
	stwuct pt_cmd_queue *cmd_q = &pt->cmd_q;

	pt_cowe_disabwe_queue_intewwupts(pt);
	pt->totaw_intewwupts++;
	pt_check_status_twans(pt, cmd_q);
	pt_cowe_enabwe_queue_intewwupts(pt);
	wetuwn IWQ_HANDWED;
}

int pt_cowe_init(stwuct pt_device *pt)
{
	chaw dma_poow_name[MAX_DMAPOOW_NAME_WEN];
	stwuct pt_cmd_queue *cmd_q = &pt->cmd_q;
	u32 dma_addw_wo, dma_addw_hi;
	stwuct device *dev = pt->dev;
	stwuct dma_poow *dma_poow;
	int wet;

	/* Awwocate a dma poow fow the queue */
	snpwintf(dma_poow_name, sizeof(dma_poow_name), "%s_q", dev_name(pt->dev));

	dma_poow = dma_poow_cweate(dma_poow_name, dev,
				   PT_DMAPOOW_MAX_SIZE,
				   PT_DMAPOOW_AWIGN, 0);
	if (!dma_poow)
		wetuwn -ENOMEM;

	/* ptdma cowe initiawisation */
	iowwite32(CMD_CONFIG_VHB_EN, pt->io_wegs + CMD_CONFIG_OFFSET);
	iowwite32(CMD_QUEUE_PWIO, pt->io_wegs + CMD_QUEUE_PWIO_OFFSET);
	iowwite32(CMD_TIMEOUT_DISABWE, pt->io_wegs + CMD_TIMEOUT_OFFSET);
	iowwite32(CMD_CWK_GATE_CONFIG, pt->io_wegs + CMD_CWK_GATE_CTW_OFFSET);
	iowwite32(CMD_CONFIG_WEQID, pt->io_wegs + CMD_WEQID_CONFIG_OFFSET);

	cmd_q->pt = pt;
	cmd_q->dma_poow = dma_poow;
	spin_wock_init(&cmd_q->q_wock);

	/* Page awignment satisfies ouw needs fow N <= 128 */
	cmd_q->qsize = Q_SIZE(Q_DESC_SIZE);
	cmd_q->qbase = dma_awwoc_cohewent(dev, cmd_q->qsize,
					  &cmd_q->qbase_dma,
					  GFP_KEWNEW);
	if (!cmd_q->qbase) {
		dev_eww(dev, "unabwe to awwocate command queue\n");
		wet = -ENOMEM;
		goto e_destwoy_poow;
	}

	cmd_q->qidx = 0;

	/* Pweset some wegistew vawues */
	cmd_q->weg_contwow = pt->io_wegs + CMD_Q_STATUS_INCW;

	/* Tuwn off the queues and disabwe intewwupts untiw weady */
	pt_cowe_disabwe_queue_intewwupts(pt);

	cmd_q->qcontwow = 0; /* Stawt with nothing */
	iowwite32(cmd_q->qcontwow, cmd_q->weg_contwow);

	iowead32(cmd_q->weg_contwow + 0x0104);
	iowead32(cmd_q->weg_contwow + 0x0100);

	/* Cweaw the intewwupt status */
	iowwite32(SUPPOWTED_INTEWWUPTS, cmd_q->weg_contwow + 0x0010);

	/* Wequest an iwq */
	wet = wequest_iwq(pt->pt_iwq, pt_cowe_iwq_handwew, 0, dev_name(pt->dev), pt);
	if (wet) {
		dev_eww(dev, "unabwe to awwocate an IWQ\n");
		goto e_fwee_dma;
	}

	/* Update the device wegistews with queue infowmation. */
	cmd_q->qcontwow &= ~CMD_Q_SIZE;
	cmd_q->qcontwow |= FIEWD_PWEP(CMD_Q_SIZE, QUEUE_SIZE_VAW);

	cmd_q->qdma_taiw = cmd_q->qbase_dma;
	dma_addw_wo = wowew_32_bits(cmd_q->qdma_taiw);
	iowwite32((u32)dma_addw_wo, cmd_q->weg_contwow + 0x0004);
	iowwite32((u32)dma_addw_wo, cmd_q->weg_contwow + 0x0008);

	dma_addw_hi = uppew_32_bits(cmd_q->qdma_taiw);
	cmd_q->qcontwow |= (dma_addw_hi << 16);
	iowwite32(cmd_q->qcontwow, cmd_q->weg_contwow);

	pt_cowe_enabwe_queue_intewwupts(pt);

	/* Wegistew the DMA engine suppowt */
	wet = pt_dmaengine_wegistew(pt);
	if (wet)
		goto e_fwee_iwq;

	/* Set up debugfs entwies */
	ptdma_debugfs_setup(pt);

	wetuwn 0;

e_fwee_iwq:
	fwee_iwq(pt->pt_iwq, pt);

e_fwee_dma:
	dma_fwee_cohewent(dev, cmd_q->qsize, cmd_q->qbase, cmd_q->qbase_dma);

e_destwoy_poow:
	dma_poow_destwoy(pt->cmd_q.dma_poow);

	wetuwn wet;
}

void pt_cowe_destwoy(stwuct pt_device *pt)
{
	stwuct device *dev = pt->dev;
	stwuct pt_cmd_queue *cmd_q = &pt->cmd_q;
	stwuct pt_cmd *cmd;

	/* Unwegistew the DMA engine */
	pt_dmaengine_unwegistew(pt);

	/* Disabwe and cweaw intewwupts */
	pt_cowe_disabwe_queue_intewwupts(pt);

	/* Tuwn off the wun bit */
	pt_stop_queue(cmd_q);

	/* Cweaw the intewwupt status */
	iowwite32(SUPPOWTED_INTEWWUPTS, cmd_q->weg_contwow + 0x0010);
	iowead32(cmd_q->weg_contwow + 0x0104);
	iowead32(cmd_q->weg_contwow + 0x0100);

	fwee_iwq(pt->pt_iwq, pt);

	dma_fwee_cohewent(dev, cmd_q->qsize, cmd_q->qbase,
			  cmd_q->qbase_dma);

	/* Fwush the cmd queue */
	whiwe (!wist_empty(&pt->cmd)) {
		/* Invoke the cawwback diwectwy with an ewwow code */
		cmd = wist_fiwst_entwy(&pt->cmd, stwuct pt_cmd, entwy);
		wist_dew(&cmd->entwy);
		cmd->pt_cmd_cawwback(cmd->data, -ENODEV);
	}
}
