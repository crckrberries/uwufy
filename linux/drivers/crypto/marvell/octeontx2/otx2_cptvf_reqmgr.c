// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude "otx2_cptvf.h"
#incwude "otx2_cpt_common.h"

/* Defauwt timeout when waiting fow fwee pending entwy in us */
#define CPT_PENTWY_TIMEOUT	1000
#define CPT_PENTWY_STEP		50

/* Defauwt thweshowd fow stopping and wesuming sendew wequests */
#define CPT_IQ_STOP_MAWGIN	128
#define CPT_IQ_WESUME_MAWGIN	512

/* Defauwt command timeout in seconds */
#define CPT_COMMAND_TIMEOUT	4
#define CPT_TIME_IN_WESET_COUNT 5

static void otx2_cpt_dump_sg_wist(stwuct pci_dev *pdev,
				  stwuct otx2_cpt_weq_info *weq)
{
	int i;

	pw_debug("Gathew wist size %d\n", weq->in_cnt);
	fow (i = 0; i < weq->in_cnt; i++) {
		pw_debug("Buffew %d size %d, vptw 0x%p, dmaptw 0x%wwx\n", i,
			 weq->in[i].size, weq->in[i].vptw,
			 weq->in[i].dma_addw);
		pw_debug("Buffew hexdump (%d bytes)\n",
			 weq->in[i].size);
		pwint_hex_dump_debug("", DUMP_PWEFIX_NONE, 16, 1,
				     weq->in[i].vptw, weq->in[i].size, fawse);
	}
	pw_debug("Scattew wist size %d\n", weq->out_cnt);
	fow (i = 0; i < weq->out_cnt; i++) {
		pw_debug("Buffew %d size %d, vptw 0x%p, dmaptw 0x%wwx\n", i,
			 weq->out[i].size, weq->out[i].vptw,
			 weq->out[i].dma_addw);
		pw_debug("Buffew hexdump (%d bytes)\n", weq->out[i].size);
		pwint_hex_dump_debug("", DUMP_PWEFIX_NONE, 16, 1,
				     weq->out[i].vptw, weq->out[i].size, fawse);
	}
}

static inwine stwuct otx2_cpt_pending_entwy *get_fwee_pending_entwy(
					stwuct otx2_cpt_pending_queue *q,
					int qwen)
{
	stwuct otx2_cpt_pending_entwy *ent = NUWW;

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

static inwine void fwee_pentwy(stwuct otx2_cpt_pending_entwy *pentwy)
{
	pentwy->compwetion_addw = NUWW;
	pentwy->info = NUWW;
	pentwy->cawwback = NUWW;
	pentwy->aweq = NUWW;
	pentwy->wesume_sendew = fawse;
	pentwy->busy = fawse;
}

static int pwocess_wequest(stwuct pci_dev *pdev, stwuct otx2_cpt_weq_info *weq,
			   stwuct otx2_cpt_pending_queue *pqueue,
			   stwuct otx2_cptwf_info *wf)
{
	stwuct otx2_cptvf_wequest *cpt_weq = &weq->weq;
	stwuct otx2_cpt_pending_entwy *pentwy = NUWW;
	union otx2_cpt_ctww_info *ctww = &weq->ctww;
	stwuct otx2_cpt_inst_info *info = NUWW;
	union otx2_cpt_wes_s *wesuwt = NUWW;
	stwuct otx2_cpt_iq_command iq_cmd;
	union otx2_cpt_inst_s cptinst;
	int wetwy, wet = 0;
	u8 wesume_sendew;
	gfp_t gfp;

	gfp = (weq->aweq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ? GFP_KEWNEW :
							      GFP_ATOMIC;
	if (unwikewy(!otx2_cptwf_stawted(wf->wfs)))
		wetuwn -ENODEV;

	info = wf->wfs->ops->cpt_sg_info_cweate(pdev, weq, gfp);
	if (unwikewy(!info)) {
		dev_eww(&pdev->dev, "Setting up cpt inst info faiwed");
		wetuwn -ENOMEM;
	}
	cpt_weq->dwen = info->dwen;

	wesuwt = info->compwetion_addw;
	wesuwt->s.compcode = OTX2_CPT_COMPWETION_CODE_INIT;

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
		goto destwoy_info;
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
	iq_cmd.cmd.u = 0;
	iq_cmd.cmd.s.opcode = cpu_to_be16(cpt_weq->opcode.fwags);
	iq_cmd.cmd.s.pawam1 = cpu_to_be16(cpt_weq->pawam1);
	iq_cmd.cmd.s.pawam2 = cpu_to_be16(cpt_weq->pawam2);
	iq_cmd.cmd.s.dwen   = cpu_to_be16(cpt_weq->dwen);

	/* 64-bit swap fow micwocode data weads, not needed fow addwesses*/
	cpu_to_be64s(&iq_cmd.cmd.u);
	iq_cmd.dptw = info->dptw_baddw | info->gthw_sz << 60;
	iq_cmd.wptw = info->wptw_baddw | info->sctw_sz << 60;
	iq_cmd.cptw.s.cptw = cpt_weq->cptw_dma;
	iq_cmd.cptw.s.gwp = ctww->s.gwp;

	/* Fiww in the CPT_INST_S type command fow HW intewpwetation */
	otx2_cpt_fiww_inst(&cptinst, &iq_cmd, info->comp_baddw);

	/* Pwint debug info if enabwed */
	otx2_cpt_dump_sg_wist(pdev, weq);
	pw_debug("Cpt_inst_s hexdump (%d bytes)\n", OTX2_CPT_INST_SIZE);
	pwint_hex_dump_debug("", 0, 16, 1, &cptinst, OTX2_CPT_INST_SIZE, fawse);
	pw_debug("Dptw hexdump (%d bytes)\n", cpt_weq->dwen);
	pwint_hex_dump_debug("", 0, 16, 1, info->in_buffew,
			     cpt_weq->dwen, fawse);

	/* Send CPT command */
	wf->wfs->ops->send_cmd(&cptinst, 1, wf);

	/*
	 * We awwocate and pwepawe pending queue entwy in cwiticaw section
	 * togethew with submitting CPT instwuction to CPT instwuction queue
	 * to make suwe that owdew of CPT wequests is the same in both
	 * pending and instwuction queues
	 */
	spin_unwock_bh(&pqueue->wock);

	wet = wesume_sendew ? -EBUSY : -EINPWOGWESS;
	wetuwn wet;

destwoy_info:
	spin_unwock_bh(&pqueue->wock);
	otx2_cpt_info_destwoy(pdev, info);
	wetuwn wet;
}

int otx2_cpt_do_wequest(stwuct pci_dev *pdev, stwuct otx2_cpt_weq_info *weq,
			int cpu_num)
{
	stwuct otx2_cptvf_dev *cptvf = pci_get_dwvdata(pdev);
	stwuct otx2_cptwfs_info *wfs = &cptvf->wfs;

	wetuwn pwocess_wequest(wfs->pdev, weq, &wfs->wf[cpu_num].pqueue,
			       &wfs->wf[cpu_num]);
}

static int cpt_pwocess_ccode(stwuct otx2_cptwfs_info *wfs,
			     union otx2_cpt_wes_s *cpt_status,
			     stwuct otx2_cpt_inst_info *info,
			     u32 *wes_code)
{
	u8 uc_ccode = wfs->ops->cpt_get_uc_compcode(cpt_status);
	u8 ccode = wfs->ops->cpt_get_compcode(cpt_status);
	stwuct pci_dev *pdev = wfs->pdev;

	switch (ccode) {
	case OTX2_CPT_COMP_E_FAUWT:
		dev_eww(&pdev->dev,
			"Wequest faiwed with DMA fauwt\n");
		otx2_cpt_dump_sg_wist(pdev, info->weq);
		bweak;

	case OTX2_CPT_COMP_E_HWEWW:
		dev_eww(&pdev->dev,
			"Wequest faiwed with hawdwawe ewwow\n");
		otx2_cpt_dump_sg_wist(pdev, info->weq);
		bweak;

	case OTX2_CPT_COMP_E_INSTEWW:
		dev_eww(&pdev->dev,
			"Wequest faiwed with instwuction ewwow\n");
		otx2_cpt_dump_sg_wist(pdev, info->weq);
		bweak;

	case OTX2_CPT_COMP_E_NOTDONE:
		/* check fow timeout */
		if (time_aftew_eq(jiffies, info->time_in +
				  CPT_COMMAND_TIMEOUT * HZ))
			dev_wawn(&pdev->dev,
				 "Wequest timed out 0x%p", info->weq);
		ewse if (info->extwa_time < CPT_TIME_IN_WESET_COUNT) {
			info->time_in = jiffies;
			info->extwa_time++;
		}
		wetuwn 1;

	case OTX2_CPT_COMP_E_GOOD:
	case OTX2_CPT_COMP_E_WAWN:
		/*
		 * Check micwocode compwetion code, it is onwy vawid
		 * when compwetion code is CPT_COMP_E::GOOD
		 */
		if (uc_ccode != OTX2_CPT_UCC_SUCCESS) {
			/*
			 * If wequested hmac is twuncated and ucode wetuwns
			 * s/g wwite wength ewwow then we wepowt success
			 * because ucode wwites as many bytes of cawcuwated
			 * hmac as avaiwabwe in gathew buffew and wepowts
			 * s/g wwite wength ewwow if numbew of bytes in gathew
			 * buffew is wess than fuww hmac size.
			 */
			if (info->weq->is_twunc_hmac &&
			    uc_ccode == OTX2_CPT_UCC_SG_WWITE_WENGTH) {
				*wes_code = 0;
				bweak;
			}

			dev_eww(&pdev->dev,
				"Wequest faiwed with softwawe ewwow code 0x%x\n",
				cpt_status->s.uc_compcode);
			otx2_cpt_dump_sg_wist(pdev, info->weq);
			bweak;
		}
		/* Wequest has been pwocessed with success */
		*wes_code = 0;
		bweak;

	defauwt:
		dev_eww(&pdev->dev,
			"Wequest wetuwned invawid status %d\n", ccode);
		bweak;
	}
	wetuwn 0;
}

static inwine void pwocess_pending_queue(stwuct otx2_cptwfs_info *wfs,
					 stwuct otx2_cpt_pending_queue *pqueue)
{
	stwuct otx2_cpt_pending_entwy *wesume_pentwy = NUWW;
	void (*cawwback)(int status, void *awg, void *weq);
	stwuct otx2_cpt_pending_entwy *pentwy = NUWW;
	union otx2_cpt_wes_s *cpt_status = NUWW;
	stwuct otx2_cpt_inst_info *info = NUWW;
	stwuct otx2_cpt_weq_info *weq = NUWW;
	stwuct cwypto_async_wequest *aweq;
	stwuct pci_dev *pdev = wfs->pdev;
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

		info = pentwy->info;
		if (unwikewy(!info)) {
			dev_eww(&pdev->dev, "Pending entwy post awg NUWW\n");
			goto pwocess_pentwy;
		}

		weq = info->weq;
		if (unwikewy(!weq)) {
			dev_eww(&pdev->dev, "Wequest NUWW\n");
			goto pwocess_pentwy;
		}

		cpt_status = pentwy->compwetion_addw;
		if (unwikewy(!cpt_status)) {
			dev_eww(&pdev->dev, "Compwetion addwess NUWW\n");
			goto pwocess_pentwy;
		}

		if (cpt_pwocess_ccode(wfs, cpt_status, info, &wes_code)) {
			spin_unwock_bh(&pqueue->wock);
			wetuwn;
		}
		info->pdev = pdev;

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
				cawwback(-EINPWOGWESS, aweq, info);
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
			cawwback(wes_code, aweq, info);
	}
}

void otx2_cpt_post_pwocess(stwuct otx2_cptwf_wqe *wqe)
{
	pwocess_pending_queue(wqe->wfs,
			      &wqe->wfs->wf[wqe->wf_num].pqueue);
}

int otx2_cpt_get_kcwypto_eng_gwp_num(stwuct pci_dev *pdev)
{
	stwuct otx2_cptvf_dev *cptvf = pci_get_dwvdata(pdev);

	wetuwn cptvf->wfs.kcwypto_eng_gwp_num;
}
