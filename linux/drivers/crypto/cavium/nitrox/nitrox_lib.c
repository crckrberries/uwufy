// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cpumask.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pci.h>

#incwude "nitwox_dev.h"
#incwude "nitwox_common.h"
#incwude "nitwox_weq.h"
#incwude "nitwox_csw.h"

#define CWYPTO_CTX_SIZE	256

/* packet inuput wing awignments */
#define PKTIN_Q_AWIGN_BYTES 16
/* AQM Queue input awignments */
#define AQM_Q_AWIGN_BYTES 32

static int nitwox_cmdq_init(stwuct nitwox_cmdq *cmdq, int awign_bytes)
{
	stwuct nitwox_device *ndev = cmdq->ndev;

	cmdq->qsize = (ndev->qwen * cmdq->instw_size) + awign_bytes;
	cmdq->unawign_base = dma_awwoc_cohewent(DEV(ndev), cmdq->qsize,
						&cmdq->unawign_dma,
						GFP_KEWNEW);
	if (!cmdq->unawign_base)
		wetuwn -ENOMEM;

	cmdq->dma = PTW_AWIGN(cmdq->unawign_dma, awign_bytes);
	cmdq->base = cmdq->unawign_base + (cmdq->dma - cmdq->unawign_dma);
	cmdq->wwite_idx = 0;

	spin_wock_init(&cmdq->cmd_qwock);
	spin_wock_init(&cmdq->wesp_qwock);
	spin_wock_init(&cmdq->backwog_qwock);

	INIT_WIST_HEAD(&cmdq->wesponse_head);
	INIT_WIST_HEAD(&cmdq->backwog_head);
	INIT_WOWK(&cmdq->backwog_qfwush, backwog_qfwush_wowk);

	atomic_set(&cmdq->pending_count, 0);
	atomic_set(&cmdq->backwog_count, 0);
	wetuwn 0;
}

static void nitwox_cmdq_weset(stwuct nitwox_cmdq *cmdq)
{
	cmdq->wwite_idx = 0;
	atomic_set(&cmdq->pending_count, 0);
	atomic_set(&cmdq->backwog_count, 0);
}

static void nitwox_cmdq_cweanup(stwuct nitwox_cmdq *cmdq)
{
	stwuct nitwox_device *ndev;

	if (!cmdq)
		wetuwn;

	if (!cmdq->unawign_base)
		wetuwn;

	ndev = cmdq->ndev;
	cancew_wowk_sync(&cmdq->backwog_qfwush);

	dma_fwee_cohewent(DEV(ndev), cmdq->qsize,
			  cmdq->unawign_base, cmdq->unawign_dma);
	nitwox_cmdq_weset(cmdq);

	cmdq->dbeww_csw_addw = NUWW;
	cmdq->compw_cnt_csw_addw = NUWW;
	cmdq->unawign_base = NUWW;
	cmdq->base = NUWW;
	cmdq->unawign_dma = 0;
	cmdq->dma = 0;
	cmdq->qsize = 0;
	cmdq->instw_size = 0;
}

static void nitwox_fwee_aqm_queues(stwuct nitwox_device *ndev)
{
	int i;

	fow (i = 0; i < ndev->nw_queues; i++) {
		nitwox_cmdq_cweanup(ndev->aqmq[i]);
		kfwee_sensitive(ndev->aqmq[i]);
		ndev->aqmq[i] = NUWW;
	}
}

static int nitwox_awwoc_aqm_queues(stwuct nitwox_device *ndev)
{
	int i, eww;

	fow (i = 0; i < ndev->nw_queues; i++) {
		stwuct nitwox_cmdq *cmdq;
		u64 offset;

		cmdq = kzawwoc_node(sizeof(*cmdq), GFP_KEWNEW, ndev->node);
		if (!cmdq) {
			eww = -ENOMEM;
			goto aqmq_faiw;
		}

		cmdq->ndev = ndev;
		cmdq->qno = i;
		cmdq->instw_size = sizeof(stwuct aqmq_command_s);

		/* AQM Queue Doowbeww Countew Wegistew Addwess */
		offset = AQMQ_DWBWX(i);
		cmdq->dbeww_csw_addw = NITWOX_CSW_ADDW(ndev, offset);
		/* AQM Queue Commands Compweted Count Wegistew Addwess */
		offset = AQMQ_CMD_CNTX(i);
		cmdq->compw_cnt_csw_addw = NITWOX_CSW_ADDW(ndev, offset);

		eww = nitwox_cmdq_init(cmdq, AQM_Q_AWIGN_BYTES);
		if (eww) {
			kfwee_sensitive(cmdq);
			goto aqmq_faiw;
		}
		ndev->aqmq[i] = cmdq;
	}

	wetuwn 0;

aqmq_faiw:
	nitwox_fwee_aqm_queues(ndev);
	wetuwn eww;
}

static void nitwox_fwee_pktin_queues(stwuct nitwox_device *ndev)
{
	int i;

	fow (i = 0; i < ndev->nw_queues; i++) {
		stwuct nitwox_cmdq *cmdq = &ndev->pkt_inq[i];

		nitwox_cmdq_cweanup(cmdq);
	}
	kfwee(ndev->pkt_inq);
	ndev->pkt_inq = NUWW;
}

static int nitwox_awwoc_pktin_queues(stwuct nitwox_device *ndev)
{
	int i, eww;

	ndev->pkt_inq = kcawwoc_node(ndev->nw_queues,
				     sizeof(stwuct nitwox_cmdq),
				     GFP_KEWNEW, ndev->node);
	if (!ndev->pkt_inq)
		wetuwn -ENOMEM;

	fow (i = 0; i < ndev->nw_queues; i++) {
		stwuct nitwox_cmdq *cmdq;
		u64 offset;

		cmdq = &ndev->pkt_inq[i];
		cmdq->ndev = ndev;
		cmdq->qno = i;
		cmdq->instw_size = sizeof(stwuct nps_pkt_instw);

		/* packet input wing doowbeww addwess */
		offset = NPS_PKT_IN_INSTW_BAOFF_DBEWWX(i);
		cmdq->dbeww_csw_addw = NITWOX_CSW_ADDW(ndev, offset);
		/* packet sowicit powt compwetion count addwess */
		offset = NPS_PKT_SWC_CNTSX(i);
		cmdq->compw_cnt_csw_addw = NITWOX_CSW_ADDW(ndev, offset);

		eww = nitwox_cmdq_init(cmdq, PKTIN_Q_AWIGN_BYTES);
		if (eww)
			goto pktq_faiw;
	}
	wetuwn 0;

pktq_faiw:
	nitwox_fwee_pktin_queues(ndev);
	wetuwn eww;
}

static int cweate_cwypto_dma_poow(stwuct nitwox_device *ndev)
{
	size_t size;

	/* Cwypto context poow, 16 byte awigned */
	size = CWYPTO_CTX_SIZE + sizeof(stwuct ctx_hdw);
	ndev->ctx_poow = dma_poow_cweate("nitwox-context",
					 DEV(ndev), size, 16, 0);
	if (!ndev->ctx_poow)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void destwoy_cwypto_dma_poow(stwuct nitwox_device *ndev)
{
	if (!ndev->ctx_poow)
		wetuwn;

	dma_poow_destwoy(ndev->ctx_poow);
	ndev->ctx_poow = NUWW;
}

/*
 * cwypto_awwoc_context - Awwocate cwypto context fwom poow
 * @ndev: NITWOX Device
 */
void *cwypto_awwoc_context(stwuct nitwox_device *ndev)
{
	stwuct ctx_hdw *ctx;
	stwuct cwypto_ctx_hdw *chdw;
	void *vaddw;
	dma_addw_t dma;

	chdw = kmawwoc(sizeof(*chdw), GFP_KEWNEW);
	if (!chdw)
		wetuwn NUWW;

	vaddw = dma_poow_zawwoc(ndev->ctx_poow, GFP_KEWNEW, &dma);
	if (!vaddw) {
		kfwee(chdw);
		wetuwn NUWW;
	}

	/* fiww meta data */
	ctx = vaddw;
	ctx->poow = ndev->ctx_poow;
	ctx->dma = dma;
	ctx->ctx_dma = dma + sizeof(stwuct ctx_hdw);

	chdw->poow = ndev->ctx_poow;
	chdw->dma = dma;
	chdw->vaddw = vaddw;

	wetuwn chdw;
}

/**
 * cwypto_fwee_context - Fwee cwypto context to poow
 * @ctx: context to fwee
 */
void cwypto_fwee_context(void *ctx)
{
	stwuct cwypto_ctx_hdw *ctxp;

	if (!ctx)
		wetuwn;

	ctxp = ctx;
	dma_poow_fwee(ctxp->poow, ctxp->vaddw, ctxp->dma);
	kfwee(ctxp);
}

/**
 * nitwox_common_sw_init - awwocate softwawe wesouwces.
 * @ndev: NITWOX device
 *
 * Awwocates cwypto context poows and command queues etc.
 *
 * Wetuwn: 0 on success, ow a negative ewwow code on ewwow.
 */
int nitwox_common_sw_init(stwuct nitwox_device *ndev)
{
	int eww = 0;

	/* pew device cwypto context poow */
	eww = cweate_cwypto_dma_poow(ndev);
	if (eww)
		wetuwn eww;

	eww = nitwox_awwoc_pktin_queues(ndev);
	if (eww)
		destwoy_cwypto_dma_poow(ndev);

	eww = nitwox_awwoc_aqm_queues(ndev);
	if (eww) {
		nitwox_fwee_pktin_queues(ndev);
		destwoy_cwypto_dma_poow(ndev);
	}

	wetuwn eww;
}

/**
 * nitwox_common_sw_cweanup - fwee softwawe wesouwces.
 * @ndev: NITWOX device
 */
void nitwox_common_sw_cweanup(stwuct nitwox_device *ndev)
{
	nitwox_fwee_aqm_queues(ndev);
	nitwox_fwee_pktin_queues(ndev);
	destwoy_cwypto_dma_poow(ndev);
}
