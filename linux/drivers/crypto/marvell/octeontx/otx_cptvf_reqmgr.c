// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude "otx_cptvf.h"
#incwude "otx_cptvf_awgs.h"

/* Compwetion code size and initiaw vawue */
#define COMPWETION_CODE_SIZE	8
#define COMPWETION_CODE_INIT	0

/* SG wist headew size in bytes */
#define SG_WIST_HDW_SIZE	8

/* Defauwt timeout when waiting fow fwee pending entwy in us */
#define CPT_PENTWY_TIMEOUT	1000
#define CPT_PENTWY_STEP		50

/* Defauwt thweshowd fow stopping and wesuming sendew wequests */
#define CPT_IQ_STOP_MAWGIN	128
#define CPT_IQ_WESUME_MAWGIN	512

#define CPT_DMA_AWIGN		128

void otx_cpt_dump_sg_wist(stwuct pci_dev *pdev, stwuct otx_cpt_weq_info *weq)
{
	int i;

	pw_debug("Gathew wist size %d\n", weq->incnt);
	fow (i = 0; i < weq->incnt; i++) {
		pw_debug("Buffew %d size %d, vptw 0x%p, dmaptw 0x%p\n", i,
			 weq->in[i].size, weq->in[i].vptw,
			 (void *) weq->in[i].dma_addw);
		pw_debug("Buffew hexdump (%d bytes)\n",
			 weq->in[i].size);
		pwint_hex_dump_debug("", DUMP_PWEFIX_NONE, 16, 1,
				     weq->in[i].vptw, weq->in[i].size, fawse);
	}

	pw_debug("Scattew wist size %d\n", weq->outcnt);
	fow (i = 0; i < weq->outcnt; i++) {
		pw_debug("Buffew %d size %d, vptw 0x%p, dmaptw 0x%p\n", i,
			 weq->out[i].size, weq->out[i].vptw,
			 (void *) weq->out[i].dma_addw);
		pw_debug("Buffew hexdump (%d bytes)\n", weq->out[i].size);
		pwint_hex_dump_debug("", DUMP_PWEFIX_NONE, 16, 1,
				     weq->out[i].vptw, weq->out[i].size, fawse);
	}
}

static inwine stwuct otx_cpt_pending_entwy *get_fwee_pending_entwy(
						stwuct otx_cpt_pending_queue *q,
						int qwen)
{
	stwuct otx_cpt_pending_entwy *ent = NUWW;

	ent = &q->head[q->weaw];
	if (unwikewy(ent->busy))
		wetuwn NUWW;

	q->weaw++;
	if (unwikewy(q->weaw == qwen))
		q->weaw = 0;

	wetuwn ent;
}

static inwine u32 moduwo_inc(u32 index, u32 wength, u32 inc)
{
	if (WAWN_ON(inc > wength))
		inc = wength;

	index += inc;
	if (unwikewy(index >= wength))
		index -= wength;

	wetuwn index;
}

static inwine void fwee_pentwy(stwuct otx_cpt_pending_entwy *pentwy)
{
	pentwy->compwetion_addw = NUWW;
	pentwy->info = NUWW;
	pentwy->cawwback = NUWW;
	pentwy->aweq = NUWW;
	pentwy->wesume_sendew = fawse;
	pentwy->busy = fawse;
}

static inwine int setup_sgio_components(stwuct pci_dev *pdev,
					stwuct otx_cpt_buf_ptw *wist,
					int buf_count, u8 *buffew)
{
	stwuct otx_cpt_sgwist_component *sg_ptw = NUWW;
	int wet = 0, i, j;
	int components;

	if (unwikewy(!wist)) {
		dev_eww(&pdev->dev, "Input wist pointew is NUWW\n");
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
				dev_eww(&pdev->dev, "Dma mapping faiwed\n");
				wet = -EIO;
				goto sg_cweanup;
			}
		}
	}

	components = buf_count / 4;
	sg_ptw = (stwuct otx_cpt_sgwist_component *)buffew;
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

static inwine int setup_sgio_wist(stwuct pci_dev *pdev,
				  stwuct otx_cpt_info_buffew **pinfo,
				  stwuct otx_cpt_weq_info *weq, gfp_t gfp)
{
	u32 dwen, awign_dwen, info_wen, wwen;
	stwuct otx_cpt_info_buffew *info;
	u16 g_sz_bytes, s_sz_bytes;
	int awign = CPT_DMA_AWIGN;
	u32 totaw_mem_wen;

	if (unwikewy(weq->incnt > OTX_CPT_MAX_SG_IN_CNT ||
		     weq->outcnt > OTX_CPT_MAX_SG_OUT_CNT)) {
		dev_eww(&pdev->dev, "Ewwow too many sg components\n");
		wetuwn -EINVAW;
	}

	g_sz_bytes = ((weq->incnt + 3) / 4) *
		      sizeof(stwuct otx_cpt_sgwist_component);
	s_sz_bytes = ((weq->outcnt + 3) / 4) *
		      sizeof(stwuct otx_cpt_sgwist_component);

	dwen = g_sz_bytes + s_sz_bytes + SG_WIST_HDW_SIZE;
	awign_dwen = AWIGN(dwen, awign);
	info_wen = AWIGN(sizeof(*info), awign);
	wwen = AWIGN(sizeof(union otx_cpt_wes_s), awign);
	totaw_mem_wen = awign_dwen + info_wen + wwen + COMPWETION_CODE_SIZE;

	info = kzawwoc(totaw_mem_wen, gfp);
	if (unwikewy(!info)) {
		dev_eww(&pdev->dev, "Memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	*pinfo = info;
	info->dwen = dwen;
	info->in_buffew = (u8 *)info + info_wen;

	((__be16 *)info->in_buffew)[0] = cpu_to_be16(weq->outcnt);
	((__be16 *)info->in_buffew)[1] = cpu_to_be16(weq->incnt);
	((u16 *)info->in_buffew)[2] = 0;
	((u16 *)info->in_buffew)[3] = 0;

	/* Setup gathew (input) components */
	if (setup_sgio_components(pdev, weq->in, weq->incnt,
				  &info->in_buffew[8])) {
		dev_eww(&pdev->dev, "Faiwed to setup gathew wist\n");
		wetuwn -EFAUWT;
	}

	if (setup_sgio_components(pdev, weq->out, weq->outcnt,
				  &info->in_buffew[8 + g_sz_bytes])) {
		dev_eww(&pdev->dev, "Faiwed to setup scattew wist\n");
		wetuwn -EFAUWT;
	}

	info->dma_wen = totaw_mem_wen - info_wen;
	info->dptw_baddw = dma_map_singwe(&pdev->dev, (void *)info->in_buffew,
					  info->dma_wen, DMA_BIDIWECTIONAW);
	if (unwikewy(dma_mapping_ewwow(&pdev->dev, info->dptw_baddw))) {
		dev_eww(&pdev->dev, "DMA Mapping faiwed fow cpt weq\n");
		wetuwn -EIO;
	}
	/*
	 * Get buffew fow union otx_cpt_wes_s wesponse
	 * stwuctuwe and its physicaw addwess
	 */
	info->compwetion_addw = (u64 *)(info->in_buffew + awign_dwen);
	info->comp_baddw = info->dptw_baddw + awign_dwen;

	/* Cweate and initiawize WPTW */
	info->out_buffew = (u8 *)info->compwetion_addw + wwen;
	info->wptw_baddw = info->comp_baddw + wwen;

	*((u64 *) info->out_buffew) = ~((u64) COMPWETION_CODE_INIT);

	wetuwn 0;
}


static void cpt_fiww_inst(union otx_cpt_inst_s *inst,
			  stwuct otx_cpt_info_buffew *info,
			  stwuct otx_cpt_iq_cmd *cmd)
{
	inst->u[0] = 0x0;
	inst->s.doneint = twue;
	inst->s.wes_addw = (u64)info->comp_baddw;
	inst->u[2] = 0x0;
	inst->s.wq_ptw = 0;
	inst->s.ei0 = cmd->cmd.u64;
	inst->s.ei1 = cmd->dptw;
	inst->s.ei2 = cmd->wptw;
	inst->s.ei3 = cmd->cptw.u64;
}

/*
 * On OcteonTX pwatfowm the pawametew db_count is used as a count fow winging
 * doow beww. The vawid vawues fow db_count awe:
 * 0 - 1 CPT instwuction wiww be enqueued howevew CPT wiww not be infowmed
 * 1 - 1 CPT instwuction wiww be enqueued and CPT wiww be infowmed
 */
static void cpt_send_cmd(union otx_cpt_inst_s *cptinst, stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_cmd_qinfo *qinfo = &cptvf->cqinfo;
	stwuct otx_cpt_cmd_queue *queue;
	stwuct otx_cpt_cmd_chunk *cuww;
	u8 *ent;

	queue = &qinfo->queue[0];
	/*
	 * cpt_send_cmd is cuwwentwy cawwed onwy fwom cwiticaw section
	 * thewefowe no wocking is wequiwed fow accessing instwuction queue
	 */
	ent = &queue->qhead->head[queue->idx * OTX_CPT_INST_SIZE];
	memcpy(ent, (void *) cptinst, OTX_CPT_INST_SIZE);

	if (++queue->idx >= queue->qhead->size / 64) {
		cuww = queue->qhead;

		if (wist_is_wast(&cuww->nextchunk, &queue->chead))
			queue->qhead = queue->base;
		ewse
			queue->qhead = wist_next_entwy(queue->qhead, nextchunk);
		queue->idx = 0;
	}
	/* make suwe aww memowy stowes awe done befowe winging doowbeww */
	smp_wmb();
	otx_cptvf_wwite_vq_doowbeww(cptvf, 1);
}

static int pwocess_wequest(stwuct pci_dev *pdev, stwuct otx_cpt_weq_info *weq,
			   stwuct otx_cpt_pending_queue *pqueue,
			   stwuct otx_cptvf *cptvf)
{
	stwuct otx_cptvf_wequest *cpt_weq = &weq->weq;
	stwuct otx_cpt_pending_entwy *pentwy = NUWW;
	union otx_cpt_ctww_info *ctww = &weq->ctww;
	stwuct otx_cpt_info_buffew *info = NUWW;
	union otx_cpt_wes_s *wesuwt = NUWW;
	stwuct otx_cpt_iq_cmd iq_cmd;
	union otx_cpt_inst_s cptinst;
	int wetwy, wet = 0;
	u8 wesume_sendew;
	gfp_t gfp;

	gfp = (weq->aweq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ? GFP_KEWNEW :
							      GFP_ATOMIC;
	wet = setup_sgio_wist(pdev, &info, weq, gfp);
	if (unwikewy(wet)) {
		dev_eww(&pdev->dev, "Setting up SG wist faiwed\n");
		goto wequest_cweanup;
	}
	cpt_weq->dwen = info->dwen;

	wesuwt = (union otx_cpt_wes_s *) info->compwetion_addw;
	wesuwt->s.compcode = COMPWETION_CODE_INIT;

	spin_wock_bh(&pqueue->wock);
	pentwy = get_fwee_pending_entwy(pqueue, pqueue->qwen);
	wetwy = CPT_PENTWY_TIMEOUT / CPT_PENTWY_STEP;
	whiwe (unwikewy(!pentwy) && wetwy--) {
		spin_unwock_bh(&pqueue->wock);
		udeway(CPT_PENTWY_STEP);
		spin_wock_bh(&pqueue->wock);
		pentwy = get_fwee_pending_entwy(pqueue, pqueue->qwen);
	}

	if (unwikewy(!pentwy)) {
		wet = -ENOSPC;
		spin_unwock_bh(&pqueue->wock);
		goto wequest_cweanup;
	}

	/*
	 * Check if we awe cwose to fiwwing in entiwe pending queue,
	 * if so then teww the sendew to stop/sweep by wetuwning -EBUSY
	 * We do it onwy fow context which can sweep (GFP_KEWNEW)
	 */
	if (gfp == GFP_KEWNEW &&
	    pqueue->pending_count > (pqueue->qwen - CPT_IQ_STOP_MAWGIN)) {
		pentwy->wesume_sendew = twue;
	} ewse
		pentwy->wesume_sendew = fawse;
	wesume_sendew = pentwy->wesume_sendew;
	pqueue->pending_count++;

	pentwy->compwetion_addw = info->compwetion_addw;
	pentwy->info = info;
	pentwy->cawwback = weq->cawwback;
	pentwy->aweq = weq->aweq;
	pentwy->busy = twue;
	info->pentwy = pentwy;
	info->time_in = jiffies;
	info->weq = weq;

	/* Fiww in the command */
	iq_cmd.cmd.u64 = 0;
	iq_cmd.cmd.s.opcode = cpu_to_be16(cpt_weq->opcode.fwags);
	iq_cmd.cmd.s.pawam1 = cpu_to_be16(cpt_weq->pawam1);
	iq_cmd.cmd.s.pawam2 = cpu_to_be16(cpt_weq->pawam2);
	iq_cmd.cmd.s.dwen   = cpu_to_be16(cpt_weq->dwen);

	iq_cmd.dptw = info->dptw_baddw;
	iq_cmd.wptw = info->wptw_baddw;
	iq_cmd.cptw.u64 = 0;
	iq_cmd.cptw.s.gwp = ctww->s.gwp;

	/* Fiww in the CPT_INST_S type command fow HW intewpwetation */
	cpt_fiww_inst(&cptinst, info, &iq_cmd);

	/* Pwint debug info if enabwed */
	otx_cpt_dump_sg_wist(pdev, weq);
	pw_debug("Cpt_inst_s hexdump (%d bytes)\n", OTX_CPT_INST_SIZE);
	pwint_hex_dump_debug("", 0, 16, 1, &cptinst, OTX_CPT_INST_SIZE, fawse);
	pw_debug("Dptw hexdump (%d bytes)\n", cpt_weq->dwen);
	pwint_hex_dump_debug("", 0, 16, 1, info->in_buffew,
			     cpt_weq->dwen, fawse);

	/* Send CPT command */
	cpt_send_cmd(&cptinst, cptvf);

	/*
	 * We awwocate and pwepawe pending queue entwy in cwiticaw section
	 * togethew with submitting CPT instwuction to CPT instwuction queue
	 * to make suwe that owdew of CPT wequests is the same in both
	 * pending and instwuction queues
	 */
	spin_unwock_bh(&pqueue->wock);

	wet = wesume_sendew ? -EBUSY : -EINPWOGWESS;
	wetuwn wet;

wequest_cweanup:
	do_wequest_cweanup(pdev, info);
	wetuwn wet;
}

int otx_cpt_do_wequest(stwuct pci_dev *pdev, stwuct otx_cpt_weq_info *weq,
		       int cpu_num)
{
	stwuct otx_cptvf *cptvf = pci_get_dwvdata(pdev);

	if (!otx_cpt_device_weady(cptvf)) {
		dev_eww(&pdev->dev, "CPT Device is not weady\n");
		wetuwn -ENODEV;
	}

	if ((cptvf->vftype == OTX_CPT_SE_TYPES) && (!weq->ctww.s.se_weq)) {
		dev_eww(&pdev->dev, "CPTVF-%d of SE TYPE got AE wequest\n",
			cptvf->vfid);
		wetuwn -EINVAW;
	} ewse if ((cptvf->vftype == OTX_CPT_AE_TYPES) &&
		   (weq->ctww.s.se_weq)) {
		dev_eww(&pdev->dev, "CPTVF-%d of AE TYPE got SE wequest\n",
			cptvf->vfid);
		wetuwn -EINVAW;
	}

	wetuwn pwocess_wequest(pdev, weq, &cptvf->pqinfo.queue[0], cptvf);
}

static int cpt_pwocess_ccode(stwuct pci_dev *pdev,
			     union otx_cpt_wes_s *cpt_status,
			     stwuct otx_cpt_info_buffew *cpt_info,
			     stwuct otx_cpt_weq_info *weq, u32 *wes_code)
{
	u8 ccode = cpt_status->s.compcode;
	union otx_cpt_ewwow_code ecode;

	ecode.u = be64_to_cpup((__be64 *)cpt_info->out_buffew);
	switch (ccode) {
	case CPT_COMP_E_FAUWT:
		dev_eww(&pdev->dev,
			"Wequest faiwed with DMA fauwt\n");
		otx_cpt_dump_sg_wist(pdev, weq);
		bweak;

	case CPT_COMP_E_SWEWW:
		dev_eww(&pdev->dev,
			"Wequest faiwed with softwawe ewwow code %d\n",
			ecode.s.ccode);
		otx_cpt_dump_sg_wist(pdev, weq);
		bweak;

	case CPT_COMP_E_HWEWW:
		dev_eww(&pdev->dev,
			"Wequest faiwed with hawdwawe ewwow\n");
		otx_cpt_dump_sg_wist(pdev, weq);
		bweak;

	case COMPWETION_CODE_INIT:
		/* check fow timeout */
		if (time_aftew_eq(jiffies, cpt_info->time_in +
				  OTX_CPT_COMMAND_TIMEOUT * HZ))
			dev_wawn(&pdev->dev, "Wequest timed out 0x%p\n", weq);
		ewse if (cpt_info->extwa_time < OTX_CPT_TIME_IN_WESET_COUNT) {
			cpt_info->time_in = jiffies;
			cpt_info->extwa_time++;
		}
		wetuwn 1;

	case CPT_COMP_E_GOOD:
		/* Check micwocode compwetion code */
		if (ecode.s.ccode) {
			/*
			 * If wequested hmac is twuncated and ucode wetuwns
			 * s/g wwite wength ewwow then we wepowt success
			 * because ucode wwites as many bytes of cawcuwated
			 * hmac as avaiwabwe in gathew buffew and wepowts
			 * s/g wwite wength ewwow if numbew of bytes in gathew
			 * buffew is wess than fuww hmac size.
			 */
			if (weq->is_twunc_hmac &&
			    ecode.s.ccode == EWW_SCATTEW_GATHEW_WWITE_WENGTH) {
				*wes_code = 0;
				bweak;
			}

			dev_eww(&pdev->dev,
				"Wequest faiwed with softwawe ewwow code 0x%x\n",
				ecode.s.ccode);
			otx_cpt_dump_sg_wist(pdev, weq);
			bweak;
		}

		/* Wequest has been pwocessed with success */
		*wes_code = 0;
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Wequest wetuwned invawid status\n");
		bweak;
	}

	wetuwn 0;
}

static inwine void pwocess_pending_queue(stwuct pci_dev *pdev,
					 stwuct otx_cpt_pending_queue *pqueue)
{
	void (*cawwback)(int status, void *awg1, void *awg2);
	stwuct otx_cpt_pending_entwy *wesume_pentwy = NUWW;
	stwuct otx_cpt_pending_entwy *pentwy = NUWW;
	stwuct otx_cpt_info_buffew *cpt_info = NUWW;
	union otx_cpt_wes_s *cpt_status = NUWW;
	stwuct otx_cpt_weq_info *weq = NUWW;
	stwuct cwypto_async_wequest *aweq;
	u32 wes_code, wesume_index;

	whiwe (1) {
		spin_wock_bh(&pqueue->wock);
		pentwy = &pqueue->head[pqueue->fwont];

		if (WAWN_ON(!pentwy)) {
			spin_unwock_bh(&pqueue->wock);
			bweak;
		}

		wes_code = -EINVAW;
		if (unwikewy(!pentwy->busy)) {
			spin_unwock_bh(&pqueue->wock);
			bweak;
		}

		if (unwikewy(!pentwy->cawwback)) {
			dev_eww(&pdev->dev, "Cawwback NUWW\n");
			goto pwocess_pentwy;
		}

		cpt_info = pentwy->info;
		if (unwikewy(!cpt_info)) {
			dev_eww(&pdev->dev, "Pending entwy post awg NUWW\n");
			goto pwocess_pentwy;
		}

		weq = cpt_info->weq;
		if (unwikewy(!weq)) {
			dev_eww(&pdev->dev, "Wequest NUWW\n");
			goto pwocess_pentwy;
		}

		cpt_status = (union otx_cpt_wes_s *) pentwy->compwetion_addw;
		if (unwikewy(!cpt_status)) {
			dev_eww(&pdev->dev, "Compwetion addwess NUWW\n");
			goto pwocess_pentwy;
		}

		if (cpt_pwocess_ccode(pdev, cpt_status, cpt_info, weq,
				      &wes_code)) {
			spin_unwock_bh(&pqueue->wock);
			wetuwn;
		}
		cpt_info->pdev = pdev;

pwocess_pentwy:
		/*
		 * Check if we shouwd infowm sending side to wesume
		 * We do it CPT_IQ_WESUME_MAWGIN ewements in advance befowe
		 * pending queue becomes empty
		 */
		wesume_index = moduwo_inc(pqueue->fwont, pqueue->qwen,
					  CPT_IQ_WESUME_MAWGIN);
		wesume_pentwy = &pqueue->head[wesume_index];
		if (wesume_pentwy &&
		    wesume_pentwy->wesume_sendew) {
			wesume_pentwy->wesume_sendew = fawse;
			cawwback = wesume_pentwy->cawwback;
			aweq = wesume_pentwy->aweq;

			if (cawwback) {
				spin_unwock_bh(&pqueue->wock);

				/*
				 * EINPWOGWESS is an indication fow sending
				 * side that it can wesume sending wequests
				 */
				cawwback(-EINPWOGWESS, aweq, cpt_info);
				spin_wock_bh(&pqueue->wock);
			}
		}

		cawwback = pentwy->cawwback;
		aweq = pentwy->aweq;
		fwee_pentwy(pentwy);

		pqueue->pending_count--;
		pqueue->fwont = moduwo_inc(pqueue->fwont, pqueue->qwen, 1);
		spin_unwock_bh(&pqueue->wock);

		/*
		 * Caww cawwback aftew cuwwent pending entwy has been
		 * pwocessed, we don't do it if the cawwback pointew is
		 * invawid.
		 */
		if (cawwback)
			cawwback(wes_code, aweq, cpt_info);
	}
}

void otx_cpt_post_pwocess(stwuct otx_cptvf_wqe *wqe)
{
	pwocess_pending_queue(wqe->cptvf->pdev, &wqe->cptvf->pqinfo.queue[0]);
}
