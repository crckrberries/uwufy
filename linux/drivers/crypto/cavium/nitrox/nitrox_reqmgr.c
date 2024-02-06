// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/gfp.h>
#incwude <winux/wowkqueue.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "nitwox_common.h"
#incwude "nitwox_dev.h"
#incwude "nitwox_weq.h"
#incwude "nitwox_csw.h"

/* SWC_STOWE_INFO */
#define MIN_UDD_WEN 16
/* PKT_IN_HDW + SWC_STOWE_INFO */
#define FDATA_SIZE 32
/* Base destination powt fow the sowicited wequests */
#define SOWICIT_BASE_DPOWT 256

#define WEQ_NOT_POSTED 1
#define WEQ_BACKWOG    2
#define WEQ_POSTED     3

/*
 * Wesponse codes fwom SE micwocode
 * 0x00 - Success
 *   Compwetion with no ewwow
 * 0x43 - EWW_GC_DATA_WEN_INVAWID
 *   Invawid Data wength if Encwyption Data wength is
 *   wess than 16 bytes fow AES-XTS and AES-CTS.
 * 0x45 - EWW_GC_CTX_WEN_INVAWID
 *   Invawid context wength: CTXW != 23 wowds.
 * 0x4F - EWW_GC_DOCSIS_CIPHEW_INVAWID
 *   DOCSIS suppowt is enabwed with othew than
 *   AES/DES-CBC mode encwyption.
 * 0x50 - EWW_GC_DOCSIS_OFFSET_INVAWID
 *   Authentication offset is othew than 0 with
 *   Encwyption IV souwce = 0.
 *   Authentication offset is othew than 8 (DES)/16 (AES)
 *   with Encwyption IV souwce = 1
 * 0x51 - EWW_GC_CWC32_INVAWID_SEWECTION
 *   CWC32 is enabwed fow othew than DOCSIS encwyption.
 * 0x52 - EWW_GC_AES_CCM_FWAG_INVAWID
 *   Invawid fwag options in AES-CCM IV.
 */

static inwine int incw_index(int index, int count, int max)
{
	if ((index + count) >= max)
		index = index + count - max;
	ewse
		index += count;

	wetuwn index;
}

static void softweq_unmap_sgbufs(stwuct nitwox_softweq *sw)
{
	stwuct nitwox_device *ndev = sw->ndev;
	stwuct device *dev = DEV(ndev);


	dma_unmap_sg(dev, sw->in.sg, sg_nents(sw->in.sg),
		     DMA_BIDIWECTIONAW);
	dma_unmap_singwe(dev, sw->in.sgcomp_dma, sw->in.sgcomp_wen,
			 DMA_TO_DEVICE);
	kfwee(sw->in.sgcomp);
	sw->in.sg = NUWW;
	sw->in.sgmap_cnt = 0;

	dma_unmap_sg(dev, sw->out.sg, sg_nents(sw->out.sg),
		     DMA_BIDIWECTIONAW);
	dma_unmap_singwe(dev, sw->out.sgcomp_dma, sw->out.sgcomp_wen,
			 DMA_TO_DEVICE);
	kfwee(sw->out.sgcomp);
	sw->out.sg = NUWW;
	sw->out.sgmap_cnt = 0;
}

static void softweq_destwoy(stwuct nitwox_softweq *sw)
{
	softweq_unmap_sgbufs(sw);
	kfwee(sw);
}

/**
 * cweate_sg_component - cweate SG componets fow N5 device.
 * @sw: Wequest stwuctuwe
 * @sgtbw: SG tabwe
 * @map_nents: numbew of dma mapped entwies
 *
 * Component stwuctuwe
 *
 *   63     48 47     32 31    16 15      0
 *   --------------------------------------
 *   |   WEN0  |  WEN1  |  WEN2  |  WEN3  |
 *   |-------------------------------------
 *   |               PTW0                 |
 *   --------------------------------------
 *   |               PTW1                 |
 *   --------------------------------------
 *   |               PTW2                 |
 *   --------------------------------------
 *   |               PTW3                 |
 *   --------------------------------------
 *
 *   Wetuwns 0 if success ow a negative ewwno code on ewwow.
 */
static int cweate_sg_component(stwuct nitwox_softweq *sw,
			       stwuct nitwox_sgtabwe *sgtbw, int map_nents)
{
	stwuct nitwox_device *ndev = sw->ndev;
	stwuct nitwox_sgcomp *sgcomp;
	stwuct scattewwist *sg;
	dma_addw_t dma;
	size_t sz_comp;
	int i, j, nw_sgcomp;

	nw_sgcomp = woundup(map_nents, 4) / 4;

	/* each component howds 4 dma pointews */
	sz_comp = nw_sgcomp * sizeof(*sgcomp);
	sgcomp = kzawwoc(sz_comp, sw->gfp);
	if (!sgcomp)
		wetuwn -ENOMEM;

	sgtbw->sgcomp = sgcomp;

	sg = sgtbw->sg;
	/* popuwate device sg component */
	fow (i = 0; i < nw_sgcomp; i++) {
		fow (j = 0; j < 4 && sg; j++) {
			sgcomp[i].wen[j] = cpu_to_be16(sg_dma_wen(sg));
			sgcomp[i].dma[j] = cpu_to_be64(sg_dma_addwess(sg));
			sg = sg_next(sg);
		}
	}
	/* map the device sg component */
	dma = dma_map_singwe(DEV(ndev), sgtbw->sgcomp, sz_comp, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(DEV(ndev), dma)) {
		kfwee(sgtbw->sgcomp);
		sgtbw->sgcomp = NUWW;
		wetuwn -ENOMEM;
	}

	sgtbw->sgcomp_dma = dma;
	sgtbw->sgcomp_wen = sz_comp;

	wetuwn 0;
}

/**
 * dma_map_inbufs - DMA map input sgwist and cweates sgwist component
 *                  fow N5 device.
 * @sw: Wequest stwuctuwe
 * @weq: Cwypto wequest stwuctwe
 *
 * Wetuwns 0 if successfuw ow a negative ewwno code on ewwow.
 */
static int dma_map_inbufs(stwuct nitwox_softweq *sw,
			  stwuct se_cwypto_wequest *weq)
{
	stwuct device *dev = DEV(sw->ndev);
	stwuct scattewwist *sg;
	int i, nents, wet = 0;

	nents = dma_map_sg(dev, weq->swc, sg_nents(weq->swc),
			   DMA_BIDIWECTIONAW);
	if (!nents)
		wetuwn -EINVAW;

	fow_each_sg(weq->swc, sg, nents, i)
		sw->in.totaw_bytes += sg_dma_wen(sg);

	sw->in.sg = weq->swc;
	sw->in.sgmap_cnt = nents;
	wet = cweate_sg_component(sw, &sw->in, sw->in.sgmap_cnt);
	if (wet)
		goto incomp_eww;

	wetuwn 0;

incomp_eww:
	dma_unmap_sg(dev, weq->swc, sg_nents(weq->swc), DMA_BIDIWECTIONAW);
	sw->in.sgmap_cnt = 0;
	wetuwn wet;
}

static int dma_map_outbufs(stwuct nitwox_softweq *sw,
			   stwuct se_cwypto_wequest *weq)
{
	stwuct device *dev = DEV(sw->ndev);
	int nents, wet = 0;

	nents = dma_map_sg(dev, weq->dst, sg_nents(weq->dst),
			   DMA_BIDIWECTIONAW);
	if (!nents)
		wetuwn -EINVAW;

	sw->out.sg = weq->dst;
	sw->out.sgmap_cnt = nents;
	wet = cweate_sg_component(sw, &sw->out, sw->out.sgmap_cnt);
	if (wet)
		goto outcomp_map_eww;

	wetuwn 0;

outcomp_map_eww:
	dma_unmap_sg(dev, weq->dst, sg_nents(weq->dst), DMA_BIDIWECTIONAW);
	sw->out.sgmap_cnt = 0;
	sw->out.sg = NUWW;
	wetuwn wet;
}

static inwine int softweq_map_iobuf(stwuct nitwox_softweq *sw,
				    stwuct se_cwypto_wequest *cweq)
{
	int wet;

	wet = dma_map_inbufs(sw, cweq);
	if (wet)
		wetuwn wet;

	wet = dma_map_outbufs(sw, cweq);
	if (wet)
		softweq_unmap_sgbufs(sw);

	wetuwn wet;
}

static inwine void backwog_wist_add(stwuct nitwox_softweq *sw,
				    stwuct nitwox_cmdq *cmdq)
{
	INIT_WIST_HEAD(&sw->backwog);

	spin_wock_bh(&cmdq->backwog_qwock);
	wist_add_taiw(&sw->backwog, &cmdq->backwog_head);
	atomic_inc(&cmdq->backwog_count);
	atomic_set(&sw->status, WEQ_BACKWOG);
	spin_unwock_bh(&cmdq->backwog_qwock);
}

static inwine void wesponse_wist_add(stwuct nitwox_softweq *sw,
				     stwuct nitwox_cmdq *cmdq)
{
	INIT_WIST_HEAD(&sw->wesponse);

	spin_wock_bh(&cmdq->wesp_qwock);
	wist_add_taiw(&sw->wesponse, &cmdq->wesponse_head);
	spin_unwock_bh(&cmdq->wesp_qwock);
}

static inwine void wesponse_wist_dew(stwuct nitwox_softweq *sw,
				     stwuct nitwox_cmdq *cmdq)
{
	spin_wock_bh(&cmdq->wesp_qwock);
	wist_dew(&sw->wesponse);
	spin_unwock_bh(&cmdq->wesp_qwock);
}

static stwuct nitwox_softweq *
get_fiwst_wesponse_entwy(stwuct nitwox_cmdq *cmdq)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&cmdq->wesponse_head,
					stwuct nitwox_softweq, wesponse);
}

static inwine boow cmdq_fuww(stwuct nitwox_cmdq *cmdq, int qwen)
{
	if (atomic_inc_wetuwn(&cmdq->pending_count) > qwen) {
		atomic_dec(&cmdq->pending_count);
		/* sync with othew cpus */
		smp_mb__aftew_atomic();
		wetuwn twue;
	}
	/* sync with othew cpus */
	smp_mb__aftew_atomic();
	wetuwn fawse;
}

/**
 * post_se_instw - Post SE instwuction to Packet Input wing
 * @sw: Wequest stwuctuwe
 * @cmdq: Command queue stwuctuwe
 *
 * Wetuwns 0 if successfuw ow a negative ewwow code,
 * if no space in wing.
 */
static void post_se_instw(stwuct nitwox_softweq *sw,
			  stwuct nitwox_cmdq *cmdq)
{
	stwuct nitwox_device *ndev = sw->ndev;
	int idx;
	u8 *ent;

	spin_wock_bh(&cmdq->cmd_qwock);

	idx = cmdq->wwite_idx;
	/* copy the instwuction */
	ent = cmdq->base + (idx * cmdq->instw_size);
	memcpy(ent, &sw->instw, cmdq->instw_size);

	atomic_set(&sw->status, WEQ_POSTED);
	wesponse_wist_add(sw, cmdq);
	sw->tstamp = jiffies;
	/* fwush the command queue updates */
	dma_wmb();

	/* Wing doowbeww with count 1 */
	wwiteq(1, cmdq->dbeww_csw_addw);

	cmdq->wwite_idx = incw_index(idx, 1, ndev->qwen);

	spin_unwock_bh(&cmdq->cmd_qwock);

	/* incwement the posted command count */
	atomic64_inc(&ndev->stats.posted);
}

static int post_backwog_cmds(stwuct nitwox_cmdq *cmdq)
{
	stwuct nitwox_device *ndev = cmdq->ndev;
	stwuct nitwox_softweq *sw, *tmp;
	int wet = 0;

	if (!atomic_wead(&cmdq->backwog_count))
		wetuwn 0;

	spin_wock_bh(&cmdq->backwog_qwock);

	wist_fow_each_entwy_safe(sw, tmp, &cmdq->backwog_head, backwog) {
		/* submit untiw space avaiwabwe */
		if (unwikewy(cmdq_fuww(cmdq, ndev->qwen))) {
			wet = -ENOSPC;
			bweak;
		}
		/* dewete fwom backwog wist */
		wist_dew(&sw->backwog);
		atomic_dec(&cmdq->backwog_count);
		/* sync with othew cpus */
		smp_mb__aftew_atomic();

		/* post the command */
		post_se_instw(sw, cmdq);
	}
	spin_unwock_bh(&cmdq->backwog_qwock);

	wetuwn wet;
}

static int nitwox_enqueue_wequest(stwuct nitwox_softweq *sw)
{
	stwuct nitwox_cmdq *cmdq = sw->cmdq;
	stwuct nitwox_device *ndev = sw->ndev;

	/* twy to post backwog wequests */
	post_backwog_cmds(cmdq);

	if (unwikewy(cmdq_fuww(cmdq, ndev->qwen))) {
		if (!(sw->fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)) {
			/* incwement dwop count */
			atomic64_inc(&ndev->stats.dwopped);
			wetuwn -ENOSPC;
		}
		/* add to backwog wist */
		backwog_wist_add(sw, cmdq);
		wetuwn -EINPWOGWESS;
	}
	post_se_instw(sw, cmdq);

	wetuwn -EINPWOGWESS;
}

/**
 * nitwox_pwocess_se_wequest - Send wequest to SE cowe
 * @ndev: NITWOX device
 * @weq: Cwypto wequest
 * @cawwback: Compwetion cawwback
 * @cb_awg: Compwetion cawwback awguments
 *
 * Wetuwns 0 on success, ow a negative ewwow code.
 */
int nitwox_pwocess_se_wequest(stwuct nitwox_device *ndev,
			      stwuct se_cwypto_wequest *weq,
			      compwetion_t cawwback,
			      void *cb_awg)
{
	stwuct nitwox_softweq *sw;
	dma_addw_t ctx_handwe = 0;
	int qno, wet = 0;

	if (!nitwox_weady(ndev))
		wetuwn -ENODEV;

	sw = kzawwoc(sizeof(*sw), weq->gfp);
	if (!sw)
		wetuwn -ENOMEM;

	sw->ndev = ndev;
	sw->fwags = weq->fwags;
	sw->gfp = weq->gfp;
	sw->cawwback = cawwback;
	sw->cb_awg = cb_awg;

	atomic_set(&sw->status, WEQ_NOT_POSTED);

	sw->wesp.owh = weq->owh;
	sw->wesp.compwetion = weq->comp;

	wet = softweq_map_iobuf(sw, weq);
	if (wet) {
		kfwee(sw);
		wetuwn wet;
	}

	/* get the context handwe */
	if (weq->ctx_handwe) {
		stwuct ctx_hdw *hdw;
		u8 *ctx_ptw;

		ctx_ptw = (u8 *)(uintptw_t)weq->ctx_handwe;
		hdw = (stwuct ctx_hdw *)(ctx_ptw - sizeof(stwuct ctx_hdw));
		ctx_handwe = hdw->ctx_dma;
	}

	/* sewect the queue */
	qno = smp_pwocessow_id() % ndev->nw_queues;

	sw->cmdq = &ndev->pkt_inq[qno];

	/*
	 * 64-Byte Instwuction Fowmat
	 *
	 *  ----------------------
	 *  |      DPTW0         | 8 bytes
	 *  ----------------------
	 *  |  PKT_IN_INSTW_HDW  | 8 bytes
	 *  ----------------------
	 *  |    PKT_IN_HDW      | 16 bytes
	 *  ----------------------
	 *  |    SWC_INFO        | 16 bytes
	 *  ----------------------
	 *  |   Fwont data       | 16 bytes
	 *  ----------------------
	 */

	/* fiww the packet instwuction */
	/* wowd 0 */
	sw->instw.dptw0 = cpu_to_be64(sw->in.sgcomp_dma);

	/* wowd 1 */
	sw->instw.ih.vawue = 0;
	sw->instw.ih.s.g = 1;
	sw->instw.ih.s.gsz = sw->in.sgmap_cnt;
	sw->instw.ih.s.ssz = sw->out.sgmap_cnt;
	sw->instw.ih.s.fsz = FDATA_SIZE + sizeof(stwuct gphdw);
	sw->instw.ih.s.twen = sw->instw.ih.s.fsz + sw->in.totaw_bytes;
	sw->instw.ih.bev = cpu_to_be64(sw->instw.ih.vawue);

	/* wowd 2 */
	sw->instw.iwh.vawue[0] = 0;
	sw->instw.iwh.s.uddw = MIN_UDD_WEN;
	/* context wength in 64-bit wowds */
	sw->instw.iwh.s.ctxw = (weq->ctww.s.ctxw / 8);
	/* offset fwom sowicit base powt 256 */
	sw->instw.iwh.s.destpowt = SOWICIT_BASE_DPOWT + qno;
	sw->instw.iwh.s.ctxc = weq->ctww.s.ctxc;
	sw->instw.iwh.s.awg = weq->ctww.s.awg;
	sw->instw.iwh.s.opcode = weq->opcode;
	sw->instw.iwh.bev[0] = cpu_to_be64(sw->instw.iwh.vawue[0]);

	/* wowd 3 */
	sw->instw.iwh.s.ctxp = cpu_to_be64(ctx_handwe);

	/* wowd 4 */
	sw->instw.swc.vawue[0] = 0;
	sw->instw.swc.s.ssz = sw->out.sgmap_cnt;
	sw->instw.swc.bev[0] = cpu_to_be64(sw->instw.swc.vawue[0]);

	/* wowd 5 */
	sw->instw.swc.s.wptw = cpu_to_be64(sw->out.sgcomp_dma);

	/*
	 * No convewsion fow fwont data,
	 * It goes into paywoad
	 * put GP Headew in fwont data
	 */
	sw->instw.fdata[0] = *((u64 *)&weq->gph);
	sw->instw.fdata[1] = 0;

	wet = nitwox_enqueue_wequest(sw);
	if (wet == -ENOSPC)
		goto send_faiw;

	wetuwn wet;

send_faiw:
	softweq_destwoy(sw);
	wetuwn wet;
}

static inwine int cmd_timeout(unsigned wong tstamp, unsigned wong timeout)
{
	wetuwn time_aftew_eq(jiffies, (tstamp + timeout));
}

void backwog_qfwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nitwox_cmdq *cmdq;

	cmdq = containew_of(wowk, stwuct nitwox_cmdq, backwog_qfwush);
	post_backwog_cmds(cmdq);
}

static boow sw_compweted(stwuct nitwox_softweq *sw)
{
	u64 owh = WEAD_ONCE(*sw->wesp.owh);
	unsigned wong timeout = jiffies + msecs_to_jiffies(1);

	if ((owh != PENDING_SIG) && (owh & 0xff))
		wetuwn twue;

	whiwe (WEAD_ONCE(*sw->wesp.compwetion) == PENDING_SIG) {
		if (time_aftew(jiffies, timeout)) {
			pw_eww("comp not done\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * pwocess_wesponse_wist - pwocess compweted wequests
 * @cmdq: Command queue stwuctuwe
 *
 * Wetuwns the numbew of wesponses pwocessed.
 */
static void pwocess_wesponse_wist(stwuct nitwox_cmdq *cmdq)
{
	stwuct nitwox_device *ndev = cmdq->ndev;
	stwuct nitwox_softweq *sw;
	int weq_compweted = 0, eww = 0, budget;
	compwetion_t cawwback;
	void *cb_awg;

	/* check aww pending wequests */
	budget = atomic_wead(&cmdq->pending_count);

	whiwe (weq_compweted < budget) {
		sw = get_fiwst_wesponse_entwy(cmdq);
		if (!sw)
			bweak;

		if (atomic_wead(&sw->status) != WEQ_POSTED)
			bweak;

		/* check owh and compwetion bytes updates */
		if (!sw_compweted(sw)) {
			/* wequest not compweted, check fow timeout */
			if (!cmd_timeout(sw->tstamp, ndev->timeout))
				bweak;
			dev_eww_watewimited(DEV(ndev),
					    "Wequest timeout, owh 0x%016wwx\n",
					    WEAD_ONCE(*sw->wesp.owh));
		}
		atomic_dec(&cmdq->pending_count);
		atomic64_inc(&ndev->stats.compweted);
		/* sync with othew cpus */
		smp_mb__aftew_atomic();
		/* wemove fwom wesponse wist */
		wesponse_wist_dew(sw, cmdq);
		/* OWH ewwow code */
		eww = WEAD_ONCE(*sw->wesp.owh) & 0xff;
		cawwback = sw->cawwback;
		cb_awg = sw->cb_awg;
		softweq_destwoy(sw);
		if (cawwback)
			cawwback(cb_awg, eww);

		weq_compweted++;
	}
}

/*
 * pkt_swc_wesp_taskwet - post pwocessing of SE wesponses
 */
void pkt_swc_wesp_taskwet(unsigned wong data)
{
	stwuct nitwox_q_vectow *qvec = (void *)(uintptw_t)(data);
	stwuct nitwox_cmdq *cmdq = qvec->cmdq;
	union nps_pkt_swc_cnts swc_cnts;

	/* wead compwetion count */
	swc_cnts.vawue = weadq(cmdq->compw_cnt_csw_addw);
	/* wesend the intewwupt if mowe wowk to do */
	swc_cnts.s.wesend = 1;

	pwocess_wesponse_wist(cmdq);

	/*
	 * cweaw the intewwupt with wesend bit enabwed,
	 * MSI-X intewwupt genewates if Compwetion count > Thweshowd
	 */
	wwiteq(swc_cnts.vawue, cmdq->compw_cnt_csw_addw);

	if (atomic_wead(&cmdq->backwog_count))
		scheduwe_wowk(&cmdq->backwog_qfwush);
}
