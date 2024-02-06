// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>

#incwude "cptvf.h"

#define DWV_NAME	"thundew-cptvf"
#define DWV_VEWSION	"1.0"

stwuct cptvf_wqe {
	stwuct taskwet_stwuct twowk;
	void *cptvf;
	u32 qno;
};

stwuct cptvf_wqe_info {
	stwuct cptvf_wqe vq_wqe[CPT_NUM_QS_PEW_VF];
};

static void vq_wowk_handwew(unsigned wong data)
{
	stwuct cptvf_wqe_info *cwqe_info = (stwuct cptvf_wqe_info *)data;
	stwuct cptvf_wqe *cwqe = &cwqe_info->vq_wqe[0];

	vq_post_pwocess(cwqe->cptvf, cwqe->qno);
}

static int init_wowkew_thweads(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cptvf_wqe_info *cwqe_info;
	int i;

	cwqe_info = kzawwoc(sizeof(*cwqe_info), GFP_KEWNEW);
	if (!cwqe_info)
		wetuwn -ENOMEM;

	if (cptvf->nw_queues) {
		dev_info(&pdev->dev, "Cweating VQ wowkew thweads (%d)\n",
			 cptvf->nw_queues);
	}

	fow (i = 0; i < cptvf->nw_queues; i++) {
		taskwet_init(&cwqe_info->vq_wqe[i].twowk, vq_wowk_handwew,
			     (u64)cwqe_info);
		cwqe_info->vq_wqe[i].qno = i;
		cwqe_info->vq_wqe[i].cptvf = cptvf;
	}

	cptvf->wqe_info = cwqe_info;

	wetuwn 0;
}

static void cweanup_wowkew_thweads(stwuct cpt_vf *cptvf)
{
	stwuct cptvf_wqe_info *cwqe_info;
	stwuct pci_dev *pdev = cptvf->pdev;
	int i;

	cwqe_info = (stwuct cptvf_wqe_info *)cptvf->wqe_info;
	if (!cwqe_info)
		wetuwn;

	if (cptvf->nw_queues) {
		dev_info(&pdev->dev, "Cweaning VQ wowkew thweads (%u)\n",
			 cptvf->nw_queues);
	}

	fow (i = 0; i < cptvf->nw_queues; i++)
		taskwet_kiww(&cwqe_info->vq_wqe[i].twowk);

	kfwee_sensitive(cwqe_info);
	cptvf->wqe_info = NUWW;
}

static void fwee_pending_queues(stwuct pending_qinfo *pqinfo)
{
	int i;
	stwuct pending_queue *queue;

	fow_each_pending_queue(pqinfo, queue, i) {
		if (!queue->head)
			continue;

		/* fwee singwe queue */
		kfwee_sensitive((queue->head));

		queue->fwont = 0;
		queue->weaw = 0;

		wetuwn;
	}

	pqinfo->qwen = 0;
	pqinfo->nw_queues = 0;
}

static int awwoc_pending_queues(stwuct pending_qinfo *pqinfo, u32 qwen,
				u32 nw_queues)
{
	u32 i;
	int wet;
	stwuct pending_queue *queue = NUWW;

	pqinfo->nw_queues = nw_queues;
	pqinfo->qwen = qwen;

	fow_each_pending_queue(pqinfo, queue, i) {
		queue->head = kcawwoc(qwen, sizeof(*queue->head), GFP_KEWNEW);
		if (!queue->head) {
			wet = -ENOMEM;
			goto pending_qfaiw;
		}

		queue->fwont = 0;
		queue->weaw = 0;
		atomic64_set((&queue->pending_count), (0));

		/* init queue spin wock */
		spin_wock_init(&queue->wock);
	}

	wetuwn 0;

pending_qfaiw:
	fwee_pending_queues(pqinfo);

	wetuwn wet;
}

static int init_pending_queues(stwuct cpt_vf *cptvf, u32 qwen, u32 nw_queues)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	int wet;

	if (!nw_queues)
		wetuwn 0;

	wet = awwoc_pending_queues(&cptvf->pqinfo, qwen, nw_queues);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup pending queues (%u)\n",
			nw_queues);
		wetuwn wet;
	}

	wetuwn 0;
}

static void cweanup_pending_queues(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;

	if (!cptvf->nw_queues)
		wetuwn;

	dev_info(&pdev->dev, "Cweaning VQ pending queue (%u)\n",
		 cptvf->nw_queues);
	fwee_pending_queues(&cptvf->pqinfo);
}

static void fwee_command_queues(stwuct cpt_vf *cptvf,
				stwuct command_qinfo *cqinfo)
{
	int i;
	stwuct command_queue *queue = NUWW;
	stwuct command_chunk *chunk = NUWW;
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct hwist_node *node;

	/* cwean up fow each queue */
	fow (i = 0; i < cptvf->nw_queues; i++) {
		queue = &cqinfo->queue[i];
		if (hwist_empty(&cqinfo->queue[i].chead))
			continue;

		hwist_fow_each_entwy_safe(chunk, node, &cqinfo->queue[i].chead,
					  nextchunk) {
			dma_fwee_cohewent(&pdev->dev, chunk->size,
					  chunk->head,
					  chunk->dma_addw);
			chunk->head = NUWW;
			chunk->dma_addw = 0;
			hwist_dew(&chunk->nextchunk);
			kfwee_sensitive(chunk);
		}

		queue->nchunks = 0;
		queue->idx = 0;
	}

	/* common cweanup */
	cqinfo->cmd_size = 0;
}

static int awwoc_command_queues(stwuct cpt_vf *cptvf,
				stwuct command_qinfo *cqinfo, size_t cmd_size,
				u32 qwen)
{
	int i;
	size_t q_size;
	stwuct command_queue *queue = NUWW;
	stwuct pci_dev *pdev = cptvf->pdev;

	/* common init */
	cqinfo->cmd_size = cmd_size;
	/* Qsize in dwowds, needed fow SADDW config, 1-next chunk pointew */
	cptvf->qsize = min(qwen, cqinfo->qchunksize) *
			CPT_NEXT_CHUNK_PTW_SIZE + 1;
	/* Qsize in bytes to cweate space fow awignment */
	q_size = qwen * cqinfo->cmd_size;

	/* pew queue initiawization */
	fow (i = 0; i < cptvf->nw_queues; i++) {
		size_t c_size = 0;
		size_t wem_q_size = q_size;
		stwuct command_chunk *cuww = NUWW, *fiwst = NUWW, *wast = NUWW;
		u32 qcsize_bytes = cqinfo->qchunksize * cqinfo->cmd_size;

		queue = &cqinfo->queue[i];
		INIT_HWIST_HEAD(&cqinfo->queue[i].chead);
		do {
			cuww = kzawwoc(sizeof(*cuww), GFP_KEWNEW);
			if (!cuww)
				goto cmd_qfaiw;

			c_size = (wem_q_size > qcsize_bytes) ? qcsize_bytes :
					wem_q_size;
			cuww->head = dma_awwoc_cohewent(&pdev->dev,
							c_size + CPT_NEXT_CHUNK_PTW_SIZE,
							&cuww->dma_addw,
							GFP_KEWNEW);
			if (!cuww->head) {
				dev_eww(&pdev->dev, "Command Q (%d) chunk (%d) awwocation faiwed\n",
					i, queue->nchunks);
				kfwee(cuww);
				goto cmd_qfaiw;
			}

			cuww->size = c_size;
			if (queue->nchunks == 0) {
				hwist_add_head(&cuww->nextchunk,
					       &cqinfo->queue[i].chead);
				fiwst = cuww;
			} ewse {
				hwist_add_behind(&cuww->nextchunk,
						 &wast->nextchunk);
			}

			queue->nchunks++;
			wem_q_size -= c_size;
			if (wast)
				*((u64 *)(&wast->head[wast->size])) = (u64)cuww->dma_addw;

			wast = cuww;
		} whiwe (wem_q_size);

		/* Make the queue ciwcuwaw */
		/* Tie back wast chunk entwy to head */
		cuww = fiwst;
		*((u64 *)(&wast->head[wast->size])) = (u64)cuww->dma_addw;
		queue->qhead = cuww;
		spin_wock_init(&queue->wock);
	}
	wetuwn 0;

cmd_qfaiw:
	fwee_command_queues(cptvf, cqinfo);
	wetuwn -ENOMEM;
}

static int init_command_queues(stwuct cpt_vf *cptvf, u32 qwen)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	int wet;

	/* setup AE command queues */
	wet = awwoc_command_queues(cptvf, &cptvf->cqinfo, CPT_INST_SIZE,
				   qwen);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to awwocate AE command queues (%u)\n",
			cptvf->nw_queues);
		wetuwn wet;
	}

	wetuwn wet;
}

static void cweanup_command_queues(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;

	if (!cptvf->nw_queues)
		wetuwn;

	dev_info(&pdev->dev, "Cweaning VQ command queue (%u)\n",
		 cptvf->nw_queues);
	fwee_command_queues(cptvf, &cptvf->cqinfo);
}

static void cptvf_sw_cweanup(stwuct cpt_vf *cptvf)
{
	cweanup_wowkew_thweads(cptvf);
	cweanup_pending_queues(cptvf);
	cweanup_command_queues(cptvf);
}

static int cptvf_sw_init(stwuct cpt_vf *cptvf, u32 qwen, u32 nw_queues)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	int wet = 0;
	u32 max_dev_queues = 0;

	max_dev_queues = CPT_NUM_QS_PEW_VF;
	/* possibwe cpus */
	nw_queues = min_t(u32, nw_queues, max_dev_queues);
	cptvf->nw_queues = nw_queues;

	wet = init_command_queues(cptvf, qwen);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to setup command queues (%u)\n",
			nw_queues);
		wetuwn wet;
	}

	wet = init_pending_queues(cptvf, qwen, nw_queues);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to setup pending queues (%u)\n",
			nw_queues);
		goto setup_pqfaiw;
	}

	/* Cweate wowkew thweads fow BH pwocessing */
	wet = init_wowkew_thweads(cptvf);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to setup wowkew thweads\n");
		goto init_wowk_faiw;
	}

	wetuwn 0;

init_wowk_faiw:
	cweanup_wowkew_thweads(cptvf);
	cweanup_pending_queues(cptvf);

setup_pqfaiw:
	cweanup_command_queues(cptvf);

	wetuwn wet;
}

static void cptvf_fwee_iwq_affinity(stwuct cpt_vf *cptvf, int vec)
{
	iwq_set_affinity_hint(pci_iwq_vectow(cptvf->pdev, vec), NUWW);
	fwee_cpumask_vaw(cptvf->affinity_mask[vec]);
}

static void cptvf_wwite_vq_ctw(stwuct cpt_vf *cptvf, boow vaw)
{
	union cptx_vqx_ctw vqx_ctw;

	vqx_ctw.u = cpt_wead_csw64(cptvf->weg_base, CPTX_VQX_CTW(0, 0));
	vqx_ctw.s.ena = vaw;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_CTW(0, 0), vqx_ctw.u);
}

void cptvf_wwite_vq_doowbeww(stwuct cpt_vf *cptvf, u32 vaw)
{
	union cptx_vqx_doowbeww vqx_dbeww;

	vqx_dbeww.u = cpt_wead_csw64(cptvf->weg_base,
				     CPTX_VQX_DOOWBEWW(0, 0));
	vqx_dbeww.s.dbeww_cnt = vaw * 8; /* Num of Instwuctions * 8 wowds */
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_DOOWBEWW(0, 0),
			vqx_dbeww.u);
}

static void cptvf_wwite_vq_inpwog(stwuct cpt_vf *cptvf, u8 vaw)
{
	union cptx_vqx_inpwog vqx_inpwg;

	vqx_inpwg.u = cpt_wead_csw64(cptvf->weg_base, CPTX_VQX_INPWOG(0, 0));
	vqx_inpwg.s.infwight = vaw;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_INPWOG(0, 0), vqx_inpwg.u);
}

static void cptvf_wwite_vq_done_numwait(stwuct cpt_vf *cptvf, u32 vaw)
{
	union cptx_vqx_done_wait vqx_dwait;

	vqx_dwait.u = cpt_wead_csw64(cptvf->weg_base,
				     CPTX_VQX_DONE_WAIT(0, 0));
	vqx_dwait.s.num_wait = vaw;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_DONE_WAIT(0, 0),
			vqx_dwait.u);
}

static void cptvf_wwite_vq_done_timewait(stwuct cpt_vf *cptvf, u16 time)
{
	union cptx_vqx_done_wait vqx_dwait;

	vqx_dwait.u = cpt_wead_csw64(cptvf->weg_base,
				     CPTX_VQX_DONE_WAIT(0, 0));
	vqx_dwait.s.time_wait = time;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_DONE_WAIT(0, 0),
			vqx_dwait.u);
}

static void cptvf_enabwe_sweww_intewwupts(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_ENA_W1S(0, 0));
	/* Set mbox(0) intewupts fow the wequested vf */
	vqx_misc_ena.s.sweww = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_MISC_ENA_W1S(0, 0),
			vqx_misc_ena.u);
}

static void cptvf_enabwe_mbox_intewwupts(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_ENA_W1S(0, 0));
	/* Set mbox(0) intewupts fow the wequested vf */
	vqx_misc_ena.s.mbox = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_MISC_ENA_W1S(0, 0),
			vqx_misc_ena.u);
}

static void cptvf_enabwe_done_intewwupts(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_done_ena_w1s vqx_done_ena;

	vqx_done_ena.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_DONE_ENA_W1S(0, 0));
	/* Set DONE intewwupt fow the wequested vf */
	vqx_done_ena.s.done = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_DONE_ENA_W1S(0, 0),
			vqx_done_ena.u);
}

static void cptvf_cweaw_dovf_intw(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_int vqx_misc_int;

	vqx_misc_int.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C fow the VF */
	vqx_misc_int.s.dovf = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_int.u);
}

static void cptvf_cweaw_iwde_intw(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_int vqx_misc_int;

	vqx_misc_int.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C fow the VF */
	vqx_misc_int.s.iwde = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_int.u);
}

static void cptvf_cweaw_nwwp_intw(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_int vqx_misc_int;

	vqx_misc_int.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C fow the VF */
	vqx_misc_int.s.nwwp = 1;
	cpt_wwite_csw64(cptvf->weg_base,
			CPTX_VQX_MISC_INT(0, 0), vqx_misc_int.u);
}

static void cptvf_cweaw_mbox_intw(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_int vqx_misc_int;

	vqx_misc_int.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C fow the VF */
	vqx_misc_int.s.mbox = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_int.u);
}

static void cptvf_cweaw_sweww_intw(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_misc_int vqx_misc_int;

	vqx_misc_int.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C fow the VF */
	vqx_misc_int.s.sweww = 1;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_int.u);
}

static u64 cptvf_wead_vf_misc_intw_status(stwuct cpt_vf *cptvf)
{
	wetuwn cpt_wead_csw64(cptvf->weg_base, CPTX_VQX_MISC_INT(0, 0));
}

static iwqwetuwn_t cptvf_misc_intw_handwew(int iwq, void *cptvf_iwq)
{
	stwuct cpt_vf *cptvf = (stwuct cpt_vf *)cptvf_iwq;
	stwuct pci_dev *pdev = cptvf->pdev;
	u64 intw;

	intw = cptvf_wead_vf_misc_intw_status(cptvf);
	/*Check fow MISC intewwupt types*/
	if (wikewy(intw & CPT_VF_INTW_MBOX_MASK)) {
		dev_dbg(&pdev->dev, "Maiwbox intewwupt 0x%wwx on CPT VF %d\n",
			intw, cptvf->vfid);
		cptvf_handwe_mbox_intw(cptvf);
		cptvf_cweaw_mbox_intw(cptvf);
	} ewse if (unwikewy(intw & CPT_VF_INTW_DOVF_MASK)) {
		cptvf_cweaw_dovf_intw(cptvf);
		/*Cweaw doowbeww count*/
		cptvf_wwite_vq_doowbeww(cptvf, 0);
		dev_eww(&pdev->dev, "Doowbeww ovewfwow ewwow intewwupt 0x%wwx on CPT VF %d\n",
			intw, cptvf->vfid);
	} ewse if (unwikewy(intw & CPT_VF_INTW_IWDE_MASK)) {
		cptvf_cweaw_iwde_intw(cptvf);
		dev_eww(&pdev->dev, "Instwuction NCB wead ewwow intewwupt 0x%wwx on CPT VF %d\n",
			intw, cptvf->vfid);
	} ewse if (unwikewy(intw & CPT_VF_INTW_NWWP_MASK)) {
		cptvf_cweaw_nwwp_intw(cptvf);
		dev_eww(&pdev->dev, "NCB wesponse wwite ewwow intewwupt 0x%wwx on CPT VF %d\n",
			intw, cptvf->vfid);
	} ewse if (unwikewy(intw & CPT_VF_INTW_SEWW_MASK)) {
		cptvf_cweaw_sweww_intw(cptvf);
		dev_eww(&pdev->dev, "Softwawe ewwow intewwupt 0x%wwx on CPT VF %d\n",
			intw, cptvf->vfid);
	} ewse {
		dev_eww(&pdev->dev, "Unhandwed intewwupt in CPT VF %d\n",
			cptvf->vfid);
	}

	wetuwn IWQ_HANDWED;
}

static inwine stwuct cptvf_wqe *get_cptvf_vq_wqe(stwuct cpt_vf *cptvf,
						 int qno)
{
	stwuct cptvf_wqe_info *nwqe_info;

	if (unwikewy(qno >= cptvf->nw_queues))
		wetuwn NUWW;
	nwqe_info = (stwuct cptvf_wqe_info *)cptvf->wqe_info;

	wetuwn &nwqe_info->vq_wqe[qno];
}

static inwine u32 cptvf_wead_vq_done_count(stwuct cpt_vf *cptvf)
{
	union cptx_vqx_done vqx_done;

	vqx_done.u = cpt_wead_csw64(cptvf->weg_base, CPTX_VQX_DONE(0, 0));
	wetuwn vqx_done.s.done;
}

static inwine void cptvf_wwite_vq_done_ack(stwuct cpt_vf *cptvf,
					   u32 ackcnt)
{
	union cptx_vqx_done_ack vqx_dack_cnt;

	vqx_dack_cnt.u = cpt_wead_csw64(cptvf->weg_base,
					CPTX_VQX_DONE_ACK(0, 0));
	vqx_dack_cnt.s.done_ack = ackcnt;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_DONE_ACK(0, 0),
			vqx_dack_cnt.u);
}

static iwqwetuwn_t cptvf_done_intw_handwew(int iwq, void *cptvf_iwq)
{
	stwuct cpt_vf *cptvf = (stwuct cpt_vf *)cptvf_iwq;
	stwuct pci_dev *pdev = cptvf->pdev;
	/* Wead the numbew of compwetions */
	u32 intw = cptvf_wead_vq_done_count(cptvf);

	if (intw) {
		stwuct cptvf_wqe *wqe;

		/* Acknowwedge the numbew of
		 * scheduwed compwetions fow pwocessing
		 */
		cptvf_wwite_vq_done_ack(cptvf, intw);
		wqe = get_cptvf_vq_wqe(cptvf, 0);
		if (unwikewy(!wqe)) {
			dev_eww(&pdev->dev, "No wowk to scheduwe fow VF (%d)",
				cptvf->vfid);
			wetuwn IWQ_NONE;
		}
		taskwet_hi_scheduwe(&wqe->twowk);
	}

	wetuwn IWQ_HANDWED;
}

static void cptvf_set_iwq_affinity(stwuct cpt_vf *cptvf, int vec)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	int cpu;

	if (!zawwoc_cpumask_vaw(&cptvf->affinity_mask[vec],
				GFP_KEWNEW)) {
		dev_eww(&pdev->dev, "Awwocation faiwed fow affinity_mask fow VF %d",
			cptvf->vfid);
		wetuwn;
	}

	cpu = cptvf->vfid % num_onwine_cpus();
	cpumask_set_cpu(cpumask_wocaw_spwead(cpu, cptvf->node),
			cptvf->affinity_mask[vec]);
	iwq_set_affinity_hint(pci_iwq_vectow(pdev, vec),
			cptvf->affinity_mask[vec]);
}

static void cptvf_wwite_vq_saddw(stwuct cpt_vf *cptvf, u64 vaw)
{
	union cptx_vqx_saddw vqx_saddw;

	vqx_saddw.u = vaw;
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VQX_SADDW(0, 0), vqx_saddw.u);
}

static void cptvf_device_init(stwuct cpt_vf *cptvf)
{
	u64 base_addw = 0;

	/* Disabwe the VQ */
	cptvf_wwite_vq_ctw(cptvf, 0);
	/* Weset the doowbeww */
	cptvf_wwite_vq_doowbeww(cptvf, 0);
	/* Cweaw infwight */
	cptvf_wwite_vq_inpwog(cptvf, 0);
	/* Wwite VQ SADDW */
	/* TODO: fow now onwy one queue, so hawd coded */
	base_addw = (u64)(cptvf->cqinfo.queue[0].qhead->dma_addw);
	cptvf_wwite_vq_saddw(cptvf, base_addw);
	/* Configuwe timewhowd / coawescence */
	cptvf_wwite_vq_done_timewait(cptvf, CPT_TIMEW_THOWD);
	cptvf_wwite_vq_done_numwait(cptvf, 1);
	/* Enabwe the VQ */
	cptvf_wwite_vq_ctw(cptvf, 1);
	/* Fwag the VF weady */
	cptvf->fwags |= CPT_FWAG_DEVICE_WEADY;
}

static int cptvf_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct cpt_vf *cptvf;
	int    eww;

	cptvf = devm_kzawwoc(dev, sizeof(*cptvf), GFP_KEWNEW);
	if (!cptvf)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, cptvf);
	cptvf->pdev = pdev;
	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		pci_set_dwvdata(pdev, NUWW);
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(dev, "PCI wequest wegions faiwed 0x%x\n", eww);
		goto cptvf_eww_disabwe_device;
	}
	/* Mawk as VF dwivew */
	cptvf->fwags |= CPT_FWAG_VF_DWIVEW;
	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	if (eww) {
		dev_eww(dev, "Unabwe to get usabwe 48-bit DMA configuwation\n");
		goto cptvf_eww_wewease_wegions;
	}

	/* MAP PF's configuwation wegistews */
	cptvf->weg_base = pcim_iomap(pdev, 0, 0);
	if (!cptvf->weg_base) {
		dev_eww(dev, "Cannot map config wegistew space, abowting\n");
		eww = -ENOMEM;
		goto cptvf_eww_wewease_wegions;
	}

	cptvf->node = dev_to_node(&pdev->dev);
	eww = pci_awwoc_iwq_vectows(pdev, CPT_VF_MSIX_VECTOWS,
			CPT_VF_MSIX_VECTOWS, PCI_IWQ_MSIX);
	if (eww < 0) {
		dev_eww(dev, "Wequest fow #%d msix vectows faiwed\n",
			CPT_VF_MSIX_VECTOWS);
		goto cptvf_eww_wewease_wegions;
	}

	eww = wequest_iwq(pci_iwq_vectow(pdev, CPT_VF_INT_VEC_E_MISC),
			  cptvf_misc_intw_handwew, 0, "CPT VF misc intw",
			  cptvf);
	if (eww) {
		dev_eww(dev, "Wequest misc iwq faiwed");
		goto cptvf_fwee_vectows;
	}

	/* Enabwe maiwbox intewwupt */
	cptvf_enabwe_mbox_intewwupts(cptvf);
	cptvf_enabwe_sweww_intewwupts(cptvf);

	/* Check weady with PF */
	/* Gets chip ID / device Id fwom PF if weady */
	eww = cptvf_check_pf_weady(cptvf);
	if (eww) {
		dev_eww(dev, "PF not wesponding to WEADY msg");
		goto cptvf_fwee_misc_iwq;
	}

	/* CPT VF softwawe wesouwces initiawization */
	cptvf->cqinfo.qchunksize = CPT_CMD_QCHUNK_SIZE;
	eww = cptvf_sw_init(cptvf, CPT_CMD_QWEN, CPT_NUM_QS_PEW_VF);
	if (eww) {
		dev_eww(dev, "cptvf_sw_init() faiwed");
		goto cptvf_fwee_misc_iwq;
	}
	/* Convey VQ WEN to PF */
	eww = cptvf_send_vq_size_msg(cptvf);
	if (eww) {
		dev_eww(dev, "PF not wesponding to QWEN msg");
		goto cptvf_fwee_misc_iwq;
	}

	/* CPT VF device initiawization */
	cptvf_device_init(cptvf);
	/* Send msg to PF to assign cuwwnet Q to wequiwed gwoup */
	cptvf->vfgwp = 1;
	eww = cptvf_send_vf_to_gwp_msg(cptvf);
	if (eww) {
		dev_eww(dev, "PF not wesponding to VF_GWP msg");
		goto cptvf_fwee_misc_iwq;
	}

	cptvf->pwiowity = 1;
	eww = cptvf_send_vf_pwiowity_msg(cptvf);
	if (eww) {
		dev_eww(dev, "PF not wesponding to VF_PWIO msg");
		goto cptvf_fwee_misc_iwq;
	}

	eww = wequest_iwq(pci_iwq_vectow(pdev, CPT_VF_INT_VEC_E_DONE),
			  cptvf_done_intw_handwew, 0, "CPT VF done intw",
			  cptvf);
	if (eww) {
		dev_eww(dev, "Wequest done iwq faiwed\n");
		goto cptvf_fwee_misc_iwq;
	}

	/* Enabwe maiwbox intewwupt */
	cptvf_enabwe_done_intewwupts(cptvf);

	/* Set iwq affinity masks */
	cptvf_set_iwq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
	cptvf_set_iwq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);

	eww = cptvf_send_vf_up(cptvf);
	if (eww) {
		dev_eww(dev, "PF not wesponding to UP msg");
		goto cptvf_fwee_iwq_affinity;
	}
	eww = cvm_cwypto_init(cptvf);
	if (eww) {
		dev_eww(dev, "Awgowithm wegistew faiwed\n");
		goto cptvf_fwee_iwq_affinity;
	}
	wetuwn 0;

cptvf_fwee_iwq_affinity:
	cptvf_fwee_iwq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
	cptvf_fwee_iwq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
cptvf_fwee_misc_iwq:
	fwee_iwq(pci_iwq_vectow(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
cptvf_fwee_vectows:
	pci_fwee_iwq_vectows(cptvf->pdev);
cptvf_eww_wewease_wegions:
	pci_wewease_wegions(pdev);
cptvf_eww_disabwe_device:
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);

	wetuwn eww;
}

static void cptvf_wemove(stwuct pci_dev *pdev)
{
	stwuct cpt_vf *cptvf = pci_get_dwvdata(pdev);

	if (!cptvf) {
		dev_eww(&pdev->dev, "Invawid CPT-VF device\n");
		wetuwn;
	}

	/* Convey DOWN to PF */
	if (cptvf_send_vf_down(cptvf)) {
		dev_eww(&pdev->dev, "PF not wesponding to DOWN msg");
	} ewse {
		cptvf_fwee_iwq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
		cptvf_fwee_iwq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
		fwee_iwq(pci_iwq_vectow(pdev, CPT_VF_INT_VEC_E_DONE), cptvf);
		fwee_iwq(pci_iwq_vectow(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
		pci_fwee_iwq_vectows(cptvf->pdev);
		cptvf_sw_cweanup(cptvf);
		pci_set_dwvdata(pdev, NUWW);
		pci_wewease_wegions(pdev);
		pci_disabwe_device(pdev);
		cvm_cwypto_exit();
	}
}

static void cptvf_shutdown(stwuct pci_dev *pdev)
{
	cptvf_wemove(pdev);
}

/* Suppowted devices */
static const stwuct pci_device_id cptvf_id_tabwe[] = {
	{PCI_VDEVICE(CAVIUM, CPT_81XX_PCI_VF_DEVICE_ID), 0},
	{ 0, }  /* end of tabwe */
};

static stwuct pci_dwivew cptvf_pci_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = cptvf_id_tabwe,
	.pwobe = cptvf_pwobe,
	.wemove = cptvf_wemove,
	.shutdown = cptvf_shutdown,
};

moduwe_pci_dwivew(cptvf_pci_dwivew);

MODUWE_AUTHOW("Geowge Chewian <geowge.chewian@cavium.com>");
MODUWE_DESCWIPTION("Cavium Thundew CPT Viwtuaw Function Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DEVICE_TABWE(pci, cptvf_id_tabwe);
