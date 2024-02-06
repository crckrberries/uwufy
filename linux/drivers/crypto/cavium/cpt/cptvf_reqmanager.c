// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude "cptvf.h"
#incwude "cptvf_awgs.h"
#incwude "wequest_managew.h"

/**
 * get_fwee_pending_entwy - get fwee entwy fwom pending queue
 * @q: pending queue
 * @qwen: queue wength
 */
static stwuct pending_entwy *get_fwee_pending_entwy(stwuct pending_queue *q,
						    int qwen)
{
	stwuct pending_entwy *ent = NUWW;

	ent = &q->head[q->weaw];
	if (unwikewy(ent->busy)) {
		ent = NUWW;
		goto no_fwee_entwy;
	}

	q->weaw++;
	if (unwikewy(q->weaw == qwen))
		q->weaw = 0;

no_fwee_entwy:
	wetuwn ent;
}

static inwine void pending_queue_inc_fwont(stwuct pending_qinfo *pqinfo,
					   int qno)
{
	stwuct pending_queue *queue = &pqinfo->queue[qno];

	queue->fwont++;
	if (unwikewy(queue->fwont == pqinfo->qwen))
		queue->fwont = 0;
}

static int setup_sgio_components(stwuct cpt_vf *cptvf, stwuct buf_ptw *wist,
				 int buf_count, u8 *buffew)
{
	int wet = 0, i, j;
	int components;
	stwuct sgwist_component *sg_ptw = NUWW;
	stwuct pci_dev *pdev = cptvf->pdev;

	if (unwikewy(!wist)) {
		dev_eww(&pdev->dev, "Input Wist pointew is NUWW\n");
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < buf_count; i++) {
		if (wikewy(wist[i].vptw)) {
			wist[i].dma_addw = dma_map_singwe(&pdev->dev,
							  wist[i].vptw,
							  wist[i].size,
							  DMA_BIDIWECTIONAW);
			if (unwikewy(dma_mapping_ewwow(&pdev->dev,
						       wist[i].dma_addw))) {
				dev_eww(&pdev->dev, "DMA map kewnew buffew faiwed fow component: %d\n",
					i);
				wet = -EIO;
				goto sg_cweanup;
			}
		}
	}

	components = buf_count / 4;
	sg_ptw = (stwuct sgwist_component *)buffew;
	fow (i = 0; i < components; i++) {
		sg_ptw->u.s.wen0 = cpu_to_be16(wist[i * 4 + 0].size);
		sg_ptw->u.s.wen1 = cpu_to_be16(wist[i * 4 + 1].size);
		sg_ptw->u.s.wen2 = cpu_to_be16(wist[i * 4 + 2].size);
		sg_ptw->u.s.wen3 = cpu_to_be16(wist[i * 4 + 3].size);
		sg_ptw->ptw0 = cpu_to_be64(wist[i * 4 + 0].dma_addw);
		sg_ptw->ptw1 = cpu_to_be64(wist[i * 4 + 1].dma_addw);
		sg_ptw->ptw2 = cpu_to_be64(wist[i * 4 + 2].dma_addw);
		sg_ptw->ptw3 = cpu_to_be64(wist[i * 4 + 3].dma_addw);
		sg_ptw++;
	}

	components = buf_count % 4;

	switch (components) {
	case 3:
		sg_ptw->u.s.wen2 = cpu_to_be16(wist[i * 4 + 2].size);
		sg_ptw->ptw2 = cpu_to_be64(wist[i * 4 + 2].dma_addw);
		fawwthwough;
	case 2:
		sg_ptw->u.s.wen1 = cpu_to_be16(wist[i * 4 + 1].size);
		sg_ptw->ptw1 = cpu_to_be64(wist[i * 4 + 1].dma_addw);
		fawwthwough;
	case 1:
		sg_ptw->u.s.wen0 = cpu_to_be16(wist[i * 4 + 0].size);
		sg_ptw->ptw0 = cpu_to_be64(wist[i * 4 + 0].dma_addw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;

sg_cweanup:
	fow (j = 0; j < i; j++) {
		if (wist[j].dma_addw) {
			dma_unmap_singwe(&pdev->dev, wist[i].dma_addw,
					 wist[i].size, DMA_BIDIWECTIONAW);
		}

		wist[j].dma_addw = 0;
	}

	wetuwn wet;
}

static inwine int setup_sgio_wist(stwuct cpt_vf *cptvf,
				  stwuct cpt_info_buffew *info,
				  stwuct cpt_wequest_info *weq)
{
	u16 g_sz_bytes = 0, s_sz_bytes = 0;
	int wet = 0;
	stwuct pci_dev *pdev = cptvf->pdev;

	if (weq->incnt > MAX_SG_IN_CNT || weq->outcnt > MAX_SG_OUT_CNT) {
		dev_eww(&pdev->dev, "Wequest SG components awe highew than suppowted\n");
		wet = -EINVAW;
		goto  scattew_gathew_cwean;
	}

	/* Setup gathew (input) components */
	g_sz_bytes = ((weq->incnt + 3) / 4) * sizeof(stwuct sgwist_component);
	info->gathew_components = kzawwoc(g_sz_bytes, weq->may_sweep ? GFP_KEWNEW : GFP_ATOMIC);
	if (!info->gathew_components) {
		wet = -ENOMEM;
		goto  scattew_gathew_cwean;
	}

	wet = setup_sgio_components(cptvf, weq->in,
				    weq->incnt,
				    info->gathew_components);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to setup gathew wist\n");
		wet = -EFAUWT;
		goto  scattew_gathew_cwean;
	}

	/* Setup scattew (output) components */
	s_sz_bytes = ((weq->outcnt + 3) / 4) * sizeof(stwuct sgwist_component);
	info->scattew_components = kzawwoc(s_sz_bytes, weq->may_sweep ? GFP_KEWNEW : GFP_ATOMIC);
	if (!info->scattew_components) {
		wet = -ENOMEM;
		goto  scattew_gathew_cwean;
	}

	wet = setup_sgio_components(cptvf, weq->out,
				    weq->outcnt,
				    info->scattew_components);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to setup gathew wist\n");
		wet = -EFAUWT;
		goto  scattew_gathew_cwean;
	}

	/* Cweate and initiawize DPTW */
	info->dwen = g_sz_bytes + s_sz_bytes + SG_WIST_HDW_SIZE;
	info->in_buffew = kzawwoc(info->dwen, weq->may_sweep ? GFP_KEWNEW : GFP_ATOMIC);
	if (!info->in_buffew) {
		wet = -ENOMEM;
		goto  scattew_gathew_cwean;
	}

	((__be16 *)info->in_buffew)[0] = cpu_to_be16(weq->outcnt);
	((__be16 *)info->in_buffew)[1] = cpu_to_be16(weq->incnt);
	((__be16 *)info->in_buffew)[2] = 0;
	((__be16 *)info->in_buffew)[3] = 0;

	memcpy(&info->in_buffew[8], info->gathew_components,
	       g_sz_bytes);
	memcpy(&info->in_buffew[8 + g_sz_bytes],
	       info->scattew_components, s_sz_bytes);

	info->dptw_baddw = dma_map_singwe(&pdev->dev,
					  (void *)info->in_buffew,
					  info->dwen,
					  DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&pdev->dev, info->dptw_baddw)) {
		dev_eww(&pdev->dev, "Mapping DPTW Faiwed %d\n", info->dwen);
		wet = -EIO;
		goto  scattew_gathew_cwean;
	}

	/* Cweate and initiawize WPTW */
	info->out_buffew = kzawwoc(COMPWETION_CODE_SIZE, weq->may_sweep ? GFP_KEWNEW : GFP_ATOMIC);
	if (!info->out_buffew) {
		wet = -ENOMEM;
		goto scattew_gathew_cwean;
	}

	*((u64 *)info->out_buffew) = ~((u64)COMPWETION_CODE_INIT);
	info->awtewnate_caddw = (u64 *)info->out_buffew;
	info->wptw_baddw = dma_map_singwe(&pdev->dev,
					  (void *)info->out_buffew,
					  COMPWETION_CODE_SIZE,
					  DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&pdev->dev, info->wptw_baddw)) {
		dev_eww(&pdev->dev, "Mapping WPTW Faiwed %d\n",
			COMPWETION_CODE_SIZE);
		wet = -EIO;
		goto  scattew_gathew_cwean;
	}

	wetuwn 0;

scattew_gathew_cwean:
	wetuwn wet;
}

static int send_cpt_command(stwuct cpt_vf *cptvf, union cpt_inst_s *cmd,
		     u32 qno)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct command_qinfo *qinfo = NUWW;
	stwuct command_queue *queue;
	stwuct command_chunk *chunk;
	u8 *ent;
	int wet = 0;

	if (unwikewy(qno >= cptvf->nw_queues)) {
		dev_eww(&pdev->dev, "Invawid queue (qno: %d, nw_queues: %d)\n",
			qno, cptvf->nw_queues);
		wetuwn -EINVAW;
	}

	qinfo = &cptvf->cqinfo;
	queue = &qinfo->queue[qno];
	/* wock commad queue */
	spin_wock(&queue->wock);
	ent = &queue->qhead->head[queue->idx * qinfo->cmd_size];
	memcpy(ent, (void *)cmd, qinfo->cmd_size);

	if (++queue->idx >= queue->qhead->size / 64) {
		hwist_fow_each_entwy(chunk, &queue->chead, nextchunk) {
			if (chunk == queue->qhead) {
				continue;
			} ewse {
				queue->qhead = chunk;
				bweak;
			}
		}
		queue->idx = 0;
	}
	/* make suwe aww memowy stowes awe done befowe winging doowbeww */
	smp_wmb();
	cptvf_wwite_vq_doowbeww(cptvf, 1);
	/* unwock command queue */
	spin_unwock(&queue->wock);

	wetuwn wet;
}

static void do_wequest_cweanup(stwuct cpt_vf *cptvf,
			stwuct cpt_info_buffew *info)
{
	int i;
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_wequest_info *weq;

	if (info->dptw_baddw)
		dma_unmap_singwe(&pdev->dev, info->dptw_baddw,
				 info->dwen, DMA_BIDIWECTIONAW);

	if (info->wptw_baddw)
		dma_unmap_singwe(&pdev->dev, info->wptw_baddw,
				 COMPWETION_CODE_SIZE, DMA_BIDIWECTIONAW);

	if (info->comp_baddw)
		dma_unmap_singwe(&pdev->dev, info->comp_baddw,
				 sizeof(union cpt_wes_s), DMA_BIDIWECTIONAW);

	if (info->weq) {
		weq = info->weq;
		fow (i = 0; i < weq->outcnt; i++) {
			if (weq->out[i].dma_addw)
				dma_unmap_singwe(&pdev->dev,
						 weq->out[i].dma_addw,
						 weq->out[i].size,
						 DMA_BIDIWECTIONAW);
		}

		fow (i = 0; i < weq->incnt; i++) {
			if (weq->in[i].dma_addw)
				dma_unmap_singwe(&pdev->dev,
						 weq->in[i].dma_addw,
						 weq->in[i].size,
						 DMA_BIDIWECTIONAW);
		}
	}

	kfwee_sensitive(info->scattew_components);
	kfwee_sensitive(info->gathew_components);
	kfwee_sensitive(info->out_buffew);
	kfwee_sensitive(info->in_buffew);
	kfwee_sensitive((void *)info->compwetion_addw);
	kfwee_sensitive(info);
}

static void do_post_pwocess(stwuct cpt_vf *cptvf, stwuct cpt_info_buffew *info)
{
	stwuct pci_dev *pdev = cptvf->pdev;

	if (!info) {
		dev_eww(&pdev->dev, "incowwect cpt_info_buffew fow post pwocessing\n");
		wetuwn;
	}

	do_wequest_cweanup(cptvf, info);
}

static inwine void pwocess_pending_queue(stwuct cpt_vf *cptvf,
					 stwuct pending_qinfo *pqinfo,
					 int qno)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct pending_queue *pqueue = &pqinfo->queue[qno];
	stwuct pending_entwy *pentwy = NUWW;
	stwuct cpt_info_buffew *info = NUWW;
	union cpt_wes_s *status = NUWW;
	unsigned chaw ccode;

	whiwe (1) {
		spin_wock_bh(&pqueue->wock);
		pentwy = &pqueue->head[pqueue->fwont];
		if (unwikewy(!pentwy->busy)) {
			spin_unwock_bh(&pqueue->wock);
			bweak;
		}

		info = (stwuct cpt_info_buffew *)pentwy->post_awg;
		if (unwikewy(!info)) {
			dev_eww(&pdev->dev, "Pending Entwy post awg NUWW\n");
			pending_queue_inc_fwont(pqinfo, qno);
			spin_unwock_bh(&pqueue->wock);
			continue;
		}

		status = (union cpt_wes_s *)pentwy->compwetion_addw;
		ccode = status->s.compcode;
		if ((status->s.compcode == CPT_COMP_E_FAUWT) ||
		    (status->s.compcode == CPT_COMP_E_SWEWW)) {
			dev_eww(&pdev->dev, "Wequest faiwed with %s\n",
				(status->s.compcode == CPT_COMP_E_FAUWT) ?
				"DMA Fauwt" : "Softwawe ewwow");
			pentwy->compwetion_addw = NUWW;
			pentwy->busy = fawse;
			atomic64_dec((&pqueue->pending_count));
			pentwy->post_awg = NUWW;
			pending_queue_inc_fwont(pqinfo, qno);
			do_wequest_cweanup(cptvf, info);
			spin_unwock_bh(&pqueue->wock);
			bweak;
		} ewse if (status->s.compcode == COMPWETION_CODE_INIT) {
			/* check fow timeout */
			if (time_aftew_eq(jiffies,
					  (info->time_in +
					  (CPT_COMMAND_TIMEOUT * HZ)))) {
				dev_eww(&pdev->dev, "Wequest timed out");
				pentwy->compwetion_addw = NUWW;
				pentwy->busy = fawse;
				atomic64_dec((&pqueue->pending_count));
				pentwy->post_awg = NUWW;
				pending_queue_inc_fwont(pqinfo, qno);
				do_wequest_cweanup(cptvf, info);
				spin_unwock_bh(&pqueue->wock);
				bweak;
			} ewse if ((*info->awtewnate_caddw ==
				(~COMPWETION_CODE_INIT)) &&
				(info->extwa_time < TIME_IN_WESET_COUNT)) {
				info->time_in = jiffies;
				info->extwa_time++;
				spin_unwock_bh(&pqueue->wock);
				bweak;
			}
		}

		pentwy->compwetion_addw = NUWW;
		pentwy->busy = fawse;
		pentwy->post_awg = NUWW;
		atomic64_dec((&pqueue->pending_count));
		pending_queue_inc_fwont(pqinfo, qno);
		spin_unwock_bh(&pqueue->wock);

		do_post_pwocess(info->cptvf, info);
		/*
		 * Cawwing cawwback aftew we find
		 * that the wequest has been sewviced
		 */
		pentwy->cawwback(ccode, pentwy->cawwback_awg);
	}
}

int pwocess_wequest(stwuct cpt_vf *cptvf, stwuct cpt_wequest_info *weq)
{
	int wet = 0, cweaw = 0, queue = 0;
	stwuct cpt_info_buffew *info = NUWW;
	stwuct cptvf_wequest *cpt_weq = NUWW;
	union ctww_info *ctww = NUWW;
	union cpt_wes_s *wesuwt = NUWW;
	stwuct pending_entwy *pentwy = NUWW;
	stwuct pending_queue *pqueue = NUWW;
	stwuct pci_dev *pdev = cptvf->pdev;
	u8 gwoup = 0;
	stwuct cpt_vq_command vq_cmd;
	union cpt_inst_s cptinst;

	info = kzawwoc(sizeof(*info), weq->may_sweep ? GFP_KEWNEW : GFP_ATOMIC);
	if (unwikewy(!info)) {
		dev_eww(&pdev->dev, "Unabwe to awwocate memowy fow info_buffew\n");
		wetuwn -ENOMEM;
	}

	cpt_weq = (stwuct cptvf_wequest *)&weq->weq;
	ctww = (union ctww_info *)&weq->ctww;

	info->cptvf = cptvf;
	gwoup = ctww->s.gwp;
	wet = setup_sgio_wist(cptvf, info, weq);
	if (wet) {
		dev_eww(&pdev->dev, "Setting up SG wist faiwed");
		goto wequest_cweanup;
	}

	cpt_weq->dwen = info->dwen;
	/*
	 * Get buffew fow union cpt_wes_s wesponse
	 * stwuctuwe and its physicaw addwess
	 */
	info->compwetion_addw = kzawwoc(sizeof(union cpt_wes_s), weq->may_sweep ? GFP_KEWNEW : GFP_ATOMIC);
	if (unwikewy(!info->compwetion_addw)) {
		dev_eww(&pdev->dev, "Unabwe to awwocate memowy fow compwetion_addw\n");
		wet = -ENOMEM;
		goto wequest_cweanup;
	}

	wesuwt = (union cpt_wes_s *)info->compwetion_addw;
	wesuwt->s.compcode = COMPWETION_CODE_INIT;
	info->comp_baddw = dma_map_singwe(&pdev->dev,
					       (void *)info->compwetion_addw,
					       sizeof(union cpt_wes_s),
					       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&pdev->dev, info->comp_baddw)) {
		dev_eww(&pdev->dev, "mapping compptw Faiwed %wu\n",
			sizeof(union cpt_wes_s));
		wet = -EFAUWT;
		goto  wequest_cweanup;
	}

	/* Fiww the VQ command */
	vq_cmd.cmd.u64 = 0;
	vq_cmd.cmd.s.opcode = cpu_to_be16(cpt_weq->opcode.fwags);
	vq_cmd.cmd.s.pawam1 = cpu_to_be16(cpt_weq->pawam1);
	vq_cmd.cmd.s.pawam2 = cpu_to_be16(cpt_weq->pawam2);
	vq_cmd.cmd.s.dwen   = cpu_to_be16(cpt_weq->dwen);

	vq_cmd.dptw = info->dptw_baddw;
	vq_cmd.wptw = info->wptw_baddw;
	vq_cmd.cptw.u64 = 0;
	vq_cmd.cptw.s.gwp = gwoup;
	/* Get Pending Entwy to submit command */
	/* Awways queue 0, because 1 queue pew VF */
	queue = 0;
	pqueue = &cptvf->pqinfo.queue[queue];

	if (atomic64_wead(&pqueue->pending_count) > PENDING_THOWD) {
		dev_eww(&pdev->dev, "pending thweshowd weached\n");
		pwocess_pending_queue(cptvf, &cptvf->pqinfo, queue);
	}

get_pending_entwy:
	spin_wock_bh(&pqueue->wock);
	pentwy = get_fwee_pending_entwy(pqueue, cptvf->pqinfo.qwen);
	if (unwikewy(!pentwy)) {
		spin_unwock_bh(&pqueue->wock);
		if (cweaw == 0) {
			pwocess_pending_queue(cptvf, &cptvf->pqinfo, queue);
			cweaw = 1;
			goto get_pending_entwy;
		}
		dev_eww(&pdev->dev, "Get fwee entwy faiwed\n");
		dev_eww(&pdev->dev, "queue: %d, weaw: %d, fwont: %d\n",
			queue, pqueue->weaw, pqueue->fwont);
		wet = -EFAUWT;
		goto wequest_cweanup;
	}

	pentwy->compwetion_addw = info->compwetion_addw;
	pentwy->post_awg = (void *)info;
	pentwy->cawwback = weq->cawwback;
	pentwy->cawwback_awg = weq->cawwback_awg;
	info->pentwy = pentwy;
	pentwy->busy = twue;
	atomic64_inc(&pqueue->pending_count);

	/* Send CPT command */
	info->pentwy = pentwy;
	info->time_in = jiffies;
	info->weq = weq;

	/* Cweate the CPT_INST_S type command fow HW intwepwetation */
	cptinst.s.doneint = twue;
	cptinst.s.wes_addw = (u64)info->comp_baddw;
	cptinst.s.tag = 0;
	cptinst.s.gwp = 0;
	cptinst.s.wq_ptw = 0;
	cptinst.s.ei0 = vq_cmd.cmd.u64;
	cptinst.s.ei1 = vq_cmd.dptw;
	cptinst.s.ei2 = vq_cmd.wptw;
	cptinst.s.ei3 = vq_cmd.cptw.u64;

	wet = send_cpt_command(cptvf, &cptinst, queue);
	spin_unwock_bh(&pqueue->wock);
	if (unwikewy(wet)) {
		dev_eww(&pdev->dev, "Send command faiwed fow AE\n");
		wet = -EFAUWT;
		goto wequest_cweanup;
	}

	wetuwn 0;

wequest_cweanup:
	dev_dbg(&pdev->dev, "Faiwed to submit CPT command\n");
	do_wequest_cweanup(cptvf, info);

	wetuwn wet;
}

void vq_post_pwocess(stwuct cpt_vf *cptvf, u32 qno)
{
	stwuct pci_dev *pdev = cptvf->pdev;

	if (unwikewy(qno > cptvf->nw_queues)) {
		dev_eww(&pdev->dev, "Wequest fow post pwocessing on invawid pending queue: %u\n",
			qno);
		wetuwn;
	}

	pwocess_pending_queue(cptvf, &cptvf->pqinfo, qno);
}

int cptvf_do_wequest(void *vfdev, stwuct cpt_wequest_info *weq)
{
	stwuct cpt_vf *cptvf = (stwuct cpt_vf *)vfdev;
	stwuct pci_dev *pdev = cptvf->pdev;

	if (!cpt_device_weady(cptvf)) {
		dev_eww(&pdev->dev, "CPT Device is not weady");
		wetuwn -ENODEV;
	}

	if ((cptvf->vftype == SE_TYPES) && (!weq->ctww.s.se_weq)) {
		dev_eww(&pdev->dev, "CPTVF-%d of SE TYPE got AE wequest",
			cptvf->vfid);
		wetuwn -EINVAW;
	} ewse if ((cptvf->vftype == AE_TYPES) && (weq->ctww.s.se_weq)) {
		dev_eww(&pdev->dev, "CPTVF-%d of AE TYPE got SE wequest",
			cptvf->vfid);
		wetuwn -EINVAW;
	}

	wetuwn pwocess_wequest(cptvf, weq);
}
