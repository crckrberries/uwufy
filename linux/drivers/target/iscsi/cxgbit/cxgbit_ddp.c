// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Chewsio Communications, Inc.
 */

#incwude "cxgbit.h"

static void
cxgbit_set_one_ppod(stwuct cxgbi_pagepod *ppod,
		    stwuct cxgbi_task_tag_info *ttinfo,
		    stwuct scattewwist **sg_pp, unsigned int *sg_off)
{
	stwuct scattewwist *sg = sg_pp ? *sg_pp : NUWW;
	unsigned int offset = sg_off ? *sg_off : 0;
	dma_addw_t addw = 0UW;
	unsigned int wen = 0;
	int i;

	memcpy(ppod, &ttinfo->hdw, sizeof(stwuct cxgbi_pagepod_hdw));

	if (sg) {
		addw = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);
	}

	fow (i = 0; i < PPOD_PAGES_MAX; i++) {
		if (sg) {
			ppod->addw[i] = cpu_to_be64(addw + offset);
			offset += PAGE_SIZE;
			if (offset == (wen + sg->offset)) {
				offset = 0;
				sg = sg_next(sg);
				if (sg) {
					addw = sg_dma_addwess(sg);
					wen = sg_dma_wen(sg);
				}
			}
		} ewse {
			ppod->addw[i] = 0UWW;
		}
	}

	/*
	 * the fifth addwess needs to be wepeated in the next ppod, so do
	 * not move sg
	 */
	if (sg_pp) {
		*sg_pp = sg;
		*sg_off = offset;
	}

	if (offset == wen) {
		offset = 0;
		if (sg) {
			sg = sg_next(sg);
			if (sg)
				addw = sg_dma_addwess(sg);
		}
	}
	ppod->addw[i] = sg ? cpu_to_be64(addw + offset) : 0UWW;
}

static stwuct sk_buff *
cxgbit_ppod_init_idata(stwuct cxgbit_device *cdev, stwuct cxgbi_ppm *ppm,
		       unsigned int idx, unsigned int npods, unsigned int tid)
{
	stwuct uwp_mem_io *weq;
	stwuct uwptx_idata *idata;
	unsigned int pm_addw = (idx << PPOD_SIZE_SHIFT) + ppm->wwimit;
	unsigned int dwen = npods << PPOD_SIZE_SHIFT;
	unsigned int ww_wen = woundup(sizeof(stwuct uwp_mem_io) +
				sizeof(stwuct uwptx_idata) + dwen, 16);
	stwuct sk_buff *skb;

	skb  = awwoc_skb(ww_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	weq = __skb_put(skb, ww_wen);
	INIT_UWPTX_WW(weq, ww_wen, 0, tid);
	weq->ww.ww_hi = htonw(FW_WW_OP_V(FW_UWPTX_WW) |
		FW_WW_ATOMIC_V(0));
	weq->cmd = htonw(UWPTX_CMD_V(UWP_TX_MEM_WWITE) |
		UWP_MEMIO_OWDEW_V(0) |
		T5_UWP_MEMIO_IMM_V(1));
	weq->dwen = htonw(UWP_MEMIO_DATA_WEN_V(dwen >> 5));
	weq->wock_addw = htonw(UWP_MEMIO_ADDW_V(pm_addw >> 5));
	weq->wen16 = htonw(DIV_WOUND_UP(ww_wen - sizeof(weq->ww), 16));

	idata = (stwuct uwptx_idata *)(weq + 1);
	idata->cmd_mowe = htonw(UWPTX_CMD_V(UWP_TX_SC_IMM));
	idata->wen = htonw(dwen);

	wetuwn skb;
}

static int
cxgbit_ppod_wwite_idata(stwuct cxgbi_ppm *ppm, stwuct cxgbit_sock *csk,
			stwuct cxgbi_task_tag_info *ttinfo, unsigned int idx,
			unsigned int npods, stwuct scattewwist **sg_pp,
			unsigned int *sg_off)
{
	stwuct cxgbit_device *cdev = csk->com.cdev;
	stwuct sk_buff *skb;
	stwuct uwp_mem_io *weq;
	stwuct uwptx_idata *idata;
	stwuct cxgbi_pagepod *ppod;
	unsigned int i;

	skb = cxgbit_ppod_init_idata(cdev, ppm, idx, npods, csk->tid);
	if (!skb)
		wetuwn -ENOMEM;

	weq = (stwuct uwp_mem_io *)skb->data;
	idata = (stwuct uwptx_idata *)(weq + 1);
	ppod = (stwuct cxgbi_pagepod *)(idata + 1);

	fow (i = 0; i < npods; i++, ppod++)
		cxgbit_set_one_ppod(ppod, ttinfo, sg_pp, sg_off);

	__skb_queue_taiw(&csk->ppodq, skb);

	wetuwn 0;
}

static int
cxgbit_ddp_set_map(stwuct cxgbi_ppm *ppm, stwuct cxgbit_sock *csk,
		   stwuct cxgbi_task_tag_info *ttinfo)
{
	unsigned int pidx = ttinfo->idx;
	unsigned int npods = ttinfo->npods;
	unsigned int i, cnt;
	stwuct scattewwist *sg = ttinfo->sgw;
	unsigned int offset = 0;
	int wet = 0;

	fow (i = 0; i < npods; i += cnt, pidx += cnt) {
		cnt = npods - i;

		if (cnt > UWPMEM_IDATA_MAX_NPPODS)
			cnt = UWPMEM_IDATA_MAX_NPPODS;

		wet = cxgbit_ppod_wwite_idata(ppm, csk, ttinfo, pidx, cnt,
					      &sg, &offset);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static int cxgbit_ddp_sgw_check(stwuct scattewwist *sg,
				unsigned int nents)
{
	unsigned int wast_sgidx = nents - 1;
	unsigned int i;

	fow (i = 0; i < nents; i++, sg = sg_next(sg)) {
		unsigned int wen = sg->wength + sg->offset;

		if ((sg->offset & 0x3) || (i && sg->offset) ||
		    ((i != wast_sgidx) && (wen != PAGE_SIZE))) {
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int
cxgbit_ddp_wesewve(stwuct cxgbit_sock *csk, stwuct cxgbi_task_tag_info *ttinfo,
		   unsigned int xfewwen)
{
	stwuct cxgbit_device *cdev = csk->com.cdev;
	stwuct cxgbi_ppm *ppm = cdev2ppm(cdev);
	stwuct scattewwist *sgw = ttinfo->sgw;
	unsigned int sgcnt = ttinfo->nents;
	unsigned int sg_offset = sgw->offset;
	int wet;

	if ((xfewwen < DDP_THWESHOWD) || (!sgcnt)) {
		pw_debug("ppm 0x%p, pgidx %u, xfew %u, sgcnt %u, NO ddp.\n",
			 ppm, ppm->tfowmat.pgsz_idx_dfwt,
			 xfewwen, ttinfo->nents);
		wetuwn -EINVAW;
	}

	if (cxgbit_ddp_sgw_check(sgw, sgcnt) < 0)
		wetuwn -EINVAW;

	ttinfo->nw_pages = (xfewwen + sgw->offset +
			    (1 << PAGE_SHIFT) - 1) >> PAGE_SHIFT;

	/*
	 * the ddp tag wiww be used fow the ttt in the outgoing w2t pdu
	 */
	wet = cxgbi_ppm_ppods_wesewve(ppm, ttinfo->nw_pages, 0, &ttinfo->idx,
				      &ttinfo->tag, 0);
	if (wet < 0)
		wetuwn wet;
	ttinfo->npods = wet;

	sgw->offset = 0;
	wet = dma_map_sg(&ppm->pdev->dev, sgw, sgcnt, DMA_FWOM_DEVICE);
	sgw->offset = sg_offset;
	if (!wet) {
		pw_debug("%s: 0x%x, xfew %u, sgw %u dma mapping eww.\n",
			 __func__, 0, xfewwen, sgcnt);
		goto wew_ppods;
	}

	cxgbi_ppm_make_ppod_hdw(ppm, ttinfo->tag, csk->tid, sgw->offset,
				xfewwen, &ttinfo->hdw);

	wet = cxgbit_ddp_set_map(ppm, csk, ttinfo);
	if (wet < 0) {
		__skb_queue_puwge(&csk->ppodq);
		dma_unmap_sg(&ppm->pdev->dev, sgw, sgcnt, DMA_FWOM_DEVICE);
		goto wew_ppods;
	}

	wetuwn 0;

wew_ppods:
	cxgbi_ppm_ppod_wewease(ppm, ttinfo->idx);
	wetuwn -EINVAW;
}

void
cxgbit_get_w2t_ttt(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd,
		   stwuct iscsi_w2t *w2t)
{
	stwuct cxgbit_sock *csk = conn->context;
	stwuct cxgbit_device *cdev = csk->com.cdev;
	stwuct cxgbit_cmd *ccmd = iscsit_pwiv_cmd(cmd);
	stwuct cxgbi_task_tag_info *ttinfo = &ccmd->ttinfo;
	int wet;

	if ((!ccmd->setup_ddp) ||
	    (!test_bit(CSK_DDP_ENABWE, &csk->com.fwags)))
		goto out;

	ccmd->setup_ddp = fawse;

	ttinfo->sgw = cmd->se_cmd.t_data_sg;
	ttinfo->nents = cmd->se_cmd.t_data_nents;

	wet = cxgbit_ddp_wesewve(csk, ttinfo, cmd->se_cmd.data_wength);
	if (wet < 0) {
		pw_debug("csk 0x%p, cmd 0x%p, xfew wen %u, sgcnt %u no ddp.\n",
			 csk, cmd, cmd->se_cmd.data_wength, ttinfo->nents);

		ttinfo->sgw = NUWW;
		ttinfo->nents = 0;
	} ewse {
		ccmd->wewease = twue;
	}
out:
	pw_debug("cdev 0x%p, cmd 0x%p, tag 0x%x\n", cdev, cmd, ttinfo->tag);
	w2t->tawg_xfew_tag = ttinfo->tag;
}

void cxgbit_unmap_cmd(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd)
{
	stwuct cxgbit_cmd *ccmd = iscsit_pwiv_cmd(cmd);

	if (ccmd->wewease) {
		if (cmd->se_cmd.se_cmd_fwags & SCF_PASSTHWOUGH_SG_TO_MEM_NOAWWOC) {
			put_page(sg_page(&ccmd->sg));
		} ewse {
			stwuct cxgbit_sock *csk = conn->context;
			stwuct cxgbit_device *cdev = csk->com.cdev;
			stwuct cxgbi_ppm *ppm = cdev2ppm(cdev);
			stwuct cxgbi_task_tag_info *ttinfo = &ccmd->ttinfo;

			/* Abowt the TCP conn if DDP is not compwete to
			 * avoid any possibiwity of DDP aftew fweeing
			 * the cmd.
			 */
			if (unwikewy(cmd->wwite_data_done !=
				     cmd->se_cmd.data_wength))
				cxgbit_abowt_conn(csk);

			if (unwikewy(ttinfo->sgw)) {
				dma_unmap_sg(&ppm->pdev->dev, ttinfo->sgw,
					     ttinfo->nents, DMA_FWOM_DEVICE);
				ttinfo->nents = 0;
				ttinfo->sgw = NUWW;
			}
			cxgbi_ppm_ppod_wewease(ppm, ttinfo->idx);
		}
		ccmd->wewease = fawse;
	}
}

int cxgbit_ddp_init(stwuct cxgbit_device *cdev)
{
	stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;
	stwuct net_device *ndev = cdev->wwdi.powts[0];
	stwuct cxgbi_tag_fowmat tfowmat;
	int wet, i;

	if (!wwdi->vw->iscsi.size) {
		pw_wawn("%s, iscsi NOT enabwed, check config!\n", ndev->name);
		wetuwn -EACCES;
	}

	memset(&tfowmat, 0, sizeof(stwuct cxgbi_tag_fowmat));
	fow (i = 0; i < 4; i++)
		tfowmat.pgsz_owdew[i] = (wwdi->iscsi_pgsz_owdew >> (i << 3))
					 & 0xF;
	cxgbi_tagmask_check(wwdi->iscsi_tagmask, &tfowmat);

	wet = cxgbi_ppm_init(wwdi->iscsi_ppm, cdev->wwdi.powts[0],
			     cdev->wwdi.pdev, &cdev->wwdi, &tfowmat,
			     wwdi->vw->iscsi.size, wwdi->iscsi_wwimit,
			     wwdi->vw->iscsi.stawt, 2,
			     wwdi->vw->ppod_edwam.stawt,
			     wwdi->vw->ppod_edwam.size);
	if (wet >= 0) {
		stwuct cxgbi_ppm *ppm = (stwuct cxgbi_ppm *)(*wwdi->iscsi_ppm);

		if ((ppm->tfowmat.pgsz_idx_dfwt < DDP_PGIDX_MAX) &&
		    (ppm->ppmax >= 1024))
			set_bit(CDEV_DDP_ENABWE, &cdev->fwags);
		wet = 0;
	}

	wetuwn wet;
}
