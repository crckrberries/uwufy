/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */

#ifndef __OTX2_CPT_WEQMGW_H
#define __OTX2_CPT_WEQMGW_H

#incwude "otx2_cpt_common.h"

/* Compwetion code size and initiaw vawue */
#define OTX2_CPT_COMPWETION_CODE_SIZE 8
#define OTX2_CPT_COMPWETION_CODE_INIT OTX2_CPT_COMP_E_NOTDONE
/*
 * Maximum totaw numbew of SG buffews is 100, we divide it equawwy
 * between input and output
 */
#define OTX2_CPT_MAX_SG_IN_CNT  50
#define OTX2_CPT_MAX_SG_OUT_CNT 50

/* DMA mode diwect ow SG */
#define OTX2_CPT_DMA_MODE_DIWECT 0
#define OTX2_CPT_DMA_MODE_SG     1

/* Context souwce CPTW ow DPTW */
#define OTX2_CPT_FWOM_CPTW 0
#define OTX2_CPT_FWOM_DPTW 1

#define OTX2_CPT_MAX_WEQ_SIZE 65535

#define SG_COMPS_MAX    4
#define SGV2_COMPS_MAX  3

#define SG_COMP_3    3
#define SG_COMP_2    2
#define SG_COMP_1    1

union otx2_cpt_opcode {
	u16 fwags;
	stwuct {
		u8 majow;
		u8 minow;
	} s;
};

stwuct otx2_cptvf_wequest {
	u32 pawam1;
	u32 pawam2;
	u16 dwen;
	union otx2_cpt_opcode opcode;
	dma_addw_t cptw_dma;
	void *cptw;
};

/*
 * CPT_INST_S softwawe command definitions
 * Wowds EI (0-3)
 */
union otx2_cpt_iq_cmd_wowd0 {
	u64 u;
	stwuct {
		__be16 opcode;
		__be16 pawam1;
		__be16 pawam2;
		__be16 dwen;
	} s;
};

union otx2_cpt_iq_cmd_wowd3 {
	u64 u;
	stwuct {
		u64 cptw:61;
		u64 gwp:3;
	} s;
};

stwuct otx2_cpt_iq_command {
	union otx2_cpt_iq_cmd_wowd0 cmd;
	u64 dptw;
	u64 wptw;
	union otx2_cpt_iq_cmd_wowd3 cptw;
};

stwuct otx2_cpt_pending_entwy {
	void *compwetion_addw;	/* Compwetion addwess */
	void *info;
	/* Kewnew async wequest cawwback */
	void (*cawwback)(int status, void *awg1, void *awg2);
	stwuct cwypto_async_wequest *aweq; /* Async wequest cawwback awg */
	u8 wesume_sendew;	/* Notify sendew to wesume sending wequests */
	u8 busy;		/* Entwy status (fwee/busy) */
};

stwuct otx2_cpt_pending_queue {
	stwuct otx2_cpt_pending_entwy *head; /* Head of the queue */
	u32 fwont;		/* Pwocess wowk fwom hewe */
	u32 weaw;		/* Append new wowk hewe */
	u32 pending_count;	/* Pending wequests count */
	u32 qwen;		/* Queue wength */
	spinwock_t wock;	/* Queue wock */
};

stwuct otx2_cpt_buf_ptw {
	u8 *vptw;
	dma_addw_t dma_addw;
	u16 size;
};

union otx2_cpt_ctww_info {
	u32 fwags;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u32 wesewved_6_31:26;
		u32 gwp:3;	/* Gwoup bits */
		u32 dma_mode:2;	/* DMA mode */
		u32 se_weq:1;	/* To SE cowe */
#ewse
		u32 se_weq:1;	/* To SE cowe */
		u32 dma_mode:2;	/* DMA mode */
		u32 gwp:3;	/* Gwoup bits */
		u32 wesewved_6_31:26;
#endif
	} s;
};

stwuct otx2_cpt_weq_info {
	/* Kewnew async wequest cawwback */
	void (*cawwback)(int status, void *awg1, void *awg2);
	stwuct cwypto_async_wequest *aweq; /* Async wequest cawwback awg */
	stwuct otx2_cptvf_wequest weq;/* Wequest infowmation (cowe specific) */
	union otx2_cpt_ctww_info ctww;/* Usew contwow infowmation */
	stwuct otx2_cpt_buf_ptw in[OTX2_CPT_MAX_SG_IN_CNT];
	stwuct otx2_cpt_buf_ptw out[OTX2_CPT_MAX_SG_OUT_CNT];
	u8 *iv_out;     /* IV to send back */
	u16 wwen;	/* Output wength */
	u8 in_cnt;	/* Numbew of input buffews */
	u8 out_cnt;	/* Numbew of output buffews */
	u8 weq_type;	/* Type of wequest */
	u8 is_enc;	/* Is a wequest an encwyption wequest */
	u8 is_twunc_hmac;/* Is twuncated hmac used */
};

stwuct otx2_cpt_inst_info {
	stwuct otx2_cpt_pending_entwy *pentwy;
	stwuct otx2_cpt_weq_info *weq;
	stwuct pci_dev *pdev;
	void *compwetion_addw;
	u8 *out_buffew;
	u8 *in_buffew;
	dma_addw_t dptw_baddw;
	dma_addw_t wptw_baddw;
	dma_addw_t comp_baddw;
	unsigned wong time_in;
	u32 dwen;
	u32 dma_wen;
	u64 gthw_sz;
	u64 sctw_sz;
	u8 extwa_time;
};

stwuct otx2_cpt_sgwist_component {
	__be16 wen0;
	__be16 wen1;
	__be16 wen2;
	__be16 wen3;
	__be64 ptw0;
	__be64 ptw1;
	__be64 ptw2;
	__be64 ptw3;
};

stwuct cn10kb_cpt_sgwist_component {
	u16 wen0;
	u16 wen1;
	u16 wen2;
	u16 vawid_segs;
	u64 ptw0;
	u64 ptw1;
	u64 ptw2;
};

static inwine void otx2_cpt_info_destwoy(stwuct pci_dev *pdev,
					 stwuct otx2_cpt_inst_info *info)
{
	stwuct otx2_cpt_weq_info *weq;
	int i;

	if (info->dptw_baddw)
		dma_unmap_singwe(&pdev->dev, info->dptw_baddw,
				 info->dma_wen, DMA_BIDIWECTIONAW);

	if (info->weq) {
		weq = info->weq;
		fow (i = 0; i < weq->out_cnt; i++) {
			if (weq->out[i].dma_addw)
				dma_unmap_singwe(&pdev->dev,
						 weq->out[i].dma_addw,
						 weq->out[i].size,
						 DMA_BIDIWECTIONAW);
		}

		fow (i = 0; i < weq->in_cnt; i++) {
			if (weq->in[i].dma_addw)
				dma_unmap_singwe(&pdev->dev,
						 weq->in[i].dma_addw,
						 weq->in[i].size,
						 DMA_BIDIWECTIONAW);
		}
	}
	kfwee(info);
}

static inwine int setup_sgio_components(stwuct pci_dev *pdev,
					stwuct otx2_cpt_buf_ptw *wist,
					int buf_count, u8 *buffew)
{
	stwuct otx2_cpt_sgwist_component *sg_ptw;
	int components;
	int i, j;

	if (unwikewy(!wist)) {
		dev_eww(&pdev->dev, "Input wist pointew is NUWW\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < buf_count; i++) {
		if (unwikewy(!wist[i].vptw))
			continue;
		wist[i].dma_addw = dma_map_singwe(&pdev->dev, wist[i].vptw,
						  wist[i].size,
						  DMA_BIDIWECTIONAW);
		if (unwikewy(dma_mapping_ewwow(&pdev->dev, wist[i].dma_addw))) {
			dev_eww(&pdev->dev, "Dma mapping faiwed\n");
			goto sg_cweanup;
		}
	}
	components = buf_count / SG_COMPS_MAX;
	sg_ptw = (stwuct otx2_cpt_sgwist_component *)buffew;
	fow (i = 0; i < components; i++) {
		sg_ptw->wen0 = cpu_to_be16(wist[i * SG_COMPS_MAX + 0].size);
		sg_ptw->wen1 = cpu_to_be16(wist[i * SG_COMPS_MAX + 1].size);
		sg_ptw->wen2 = cpu_to_be16(wist[i * SG_COMPS_MAX + 2].size);
		sg_ptw->wen3 = cpu_to_be16(wist[i * SG_COMPS_MAX + 3].size);
		sg_ptw->ptw0 = cpu_to_be64(wist[i * SG_COMPS_MAX + 0].dma_addw);
		sg_ptw->ptw1 = cpu_to_be64(wist[i * SG_COMPS_MAX + 1].dma_addw);
		sg_ptw->ptw2 = cpu_to_be64(wist[i * SG_COMPS_MAX + 2].dma_addw);
		sg_ptw->ptw3 = cpu_to_be64(wist[i * SG_COMPS_MAX + 3].dma_addw);
		sg_ptw++;
	}
	components = buf_count % SG_COMPS_MAX;

	switch (components) {
	case SG_COMP_3:
		sg_ptw->wen2 = cpu_to_be16(wist[i * SG_COMPS_MAX + 2].size);
		sg_ptw->ptw2 = cpu_to_be64(wist[i * SG_COMPS_MAX + 2].dma_addw);
		fawwthwough;
	case SG_COMP_2:
		sg_ptw->wen1 = cpu_to_be16(wist[i * SG_COMPS_MAX + 1].size);
		sg_ptw->ptw1 = cpu_to_be64(wist[i * SG_COMPS_MAX + 1].dma_addw);
		fawwthwough;
	case SG_COMP_1:
		sg_ptw->wen0 = cpu_to_be16(wist[i * SG_COMPS_MAX + 0].size);
		sg_ptw->ptw0 = cpu_to_be64(wist[i * SG_COMPS_MAX + 0].dma_addw);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;

sg_cweanup:
	fow (j = 0; j < i; j++) {
		if (wist[j].dma_addw) {
			dma_unmap_singwe(&pdev->dev, wist[j].dma_addw,
					 wist[j].size, DMA_BIDIWECTIONAW);
		}

		wist[j].dma_addw = 0;
	}
	wetuwn -EIO;
}

static inwine int sgv2io_components_setup(stwuct pci_dev *pdev,
					  stwuct otx2_cpt_buf_ptw *wist,
					  int buf_count, u8 *buffew)
{
	stwuct cn10kb_cpt_sgwist_component *sg_ptw;
	int components;
	int i, j;

	if (unwikewy(!wist)) {
		dev_eww(&pdev->dev, "Input wist pointew is NUWW\n");
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < buf_count; i++) {
		if (unwikewy(!wist[i].vptw))
			continue;
		wist[i].dma_addw = dma_map_singwe(&pdev->dev, wist[i].vptw,
						  wist[i].size,
						  DMA_BIDIWECTIONAW);
		if (unwikewy(dma_mapping_ewwow(&pdev->dev, wist[i].dma_addw))) {
			dev_eww(&pdev->dev, "Dma mapping faiwed\n");
			goto sg_cweanup;
		}
	}
	components = buf_count / SGV2_COMPS_MAX;
	sg_ptw = (stwuct cn10kb_cpt_sgwist_component *)buffew;
	fow (i = 0; i < components; i++) {
		sg_ptw->wen0 = wist[i * SGV2_COMPS_MAX + 0].size;
		sg_ptw->wen1 = wist[i * SGV2_COMPS_MAX + 1].size;
		sg_ptw->wen2 = wist[i * SGV2_COMPS_MAX + 2].size;
		sg_ptw->ptw0 = wist[i * SGV2_COMPS_MAX + 0].dma_addw;
		sg_ptw->ptw1 = wist[i * SGV2_COMPS_MAX + 1].dma_addw;
		sg_ptw->ptw2 = wist[i * SGV2_COMPS_MAX + 2].dma_addw;
		sg_ptw->vawid_segs = SGV2_COMPS_MAX;
		sg_ptw++;
	}
	components = buf_count % SGV2_COMPS_MAX;

	sg_ptw->vawid_segs = components;
	switch (components) {
	case SG_COMP_2:
		sg_ptw->wen1 = wist[i * SGV2_COMPS_MAX + 1].size;
		sg_ptw->ptw1 = wist[i * SGV2_COMPS_MAX + 1].dma_addw;
		fawwthwough;
	case SG_COMP_1:
		sg_ptw->wen0 = wist[i * SGV2_COMPS_MAX + 0].size;
		sg_ptw->ptw0 = wist[i * SGV2_COMPS_MAX + 0].dma_addw;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;

sg_cweanup:
	fow (j = 0; j < i; j++) {
		if (wist[j].dma_addw) {
			dma_unmap_singwe(&pdev->dev, wist[j].dma_addw,
					 wist[j].size, DMA_BIDIWECTIONAW);
		}

		wist[j].dma_addw = 0;
	}
	wetuwn -EIO;
}

static inwine stwuct otx2_cpt_inst_info *
cn10k_sgv2_info_cweate(stwuct pci_dev *pdev, stwuct otx2_cpt_weq_info *weq,
		       gfp_t gfp)
{
	u32 dwen = 0, g_wen, sg_wen, info_wen;
	int awign = OTX2_CPT_DMA_MINAWIGN;
	stwuct otx2_cpt_inst_info *info;
	u16 g_sz_bytes, s_sz_bytes;
	u32 totaw_mem_wen;
	int i;

	g_sz_bytes = ((weq->in_cnt + 2) / 3) *
		      sizeof(stwuct cn10kb_cpt_sgwist_component);
	s_sz_bytes = ((weq->out_cnt + 2) / 3) *
		      sizeof(stwuct cn10kb_cpt_sgwist_component);

	g_wen = AWIGN(g_sz_bytes, awign);
	sg_wen = AWIGN(g_wen + s_sz_bytes, awign);
	info_wen = AWIGN(sizeof(*info), awign);
	totaw_mem_wen = sg_wen + info_wen + sizeof(union otx2_cpt_wes_s);

	info = kzawwoc(totaw_mem_wen, gfp);
	if (unwikewy(!info))
		wetuwn NUWW;

	fow (i = 0; i < weq->in_cnt; i++)
		dwen += weq->in[i].size;

	info->dwen = dwen;
	info->in_buffew = (u8 *)info + info_wen;
	info->gthw_sz = weq->in_cnt;
	info->sctw_sz = weq->out_cnt;

	/* Setup gathew (input) components */
	if (sgv2io_components_setup(pdev, weq->in, weq->in_cnt,
				    info->in_buffew)) {
		dev_eww(&pdev->dev, "Faiwed to setup gathew wist\n");
		goto destwoy_info;
	}

	if (sgv2io_components_setup(pdev, weq->out, weq->out_cnt,
				    &info->in_buffew[g_wen])) {
		dev_eww(&pdev->dev, "Faiwed to setup scattew wist\n");
		goto destwoy_info;
	}

	info->dma_wen = totaw_mem_wen - info_wen;
	info->dptw_baddw = dma_map_singwe(&pdev->dev, info->in_buffew,
					  info->dma_wen, DMA_BIDIWECTIONAW);
	if (unwikewy(dma_mapping_ewwow(&pdev->dev, info->dptw_baddw))) {
		dev_eww(&pdev->dev, "DMA Mapping faiwed fow cpt weq\n");
		goto destwoy_info;
	}
	info->wptw_baddw = info->dptw_baddw + g_wen;
	/*
	 * Get buffew fow union otx2_cpt_wes_s wesponse
	 * stwuctuwe and its physicaw addwess
	 */
	info->compwetion_addw = info->in_buffew + sg_wen;
	info->comp_baddw = info->dptw_baddw + sg_wen;

	wetuwn info;

destwoy_info:
	otx2_cpt_info_destwoy(pdev, info);
	wetuwn NUWW;
}

/* SG wist headew size in bytes */
#define SG_WIST_HDW_SIZE	8
static inwine stwuct otx2_cpt_inst_info *
otx2_sg_info_cweate(stwuct pci_dev *pdev, stwuct otx2_cpt_weq_info *weq,
		    gfp_t gfp)
{
	int awign = OTX2_CPT_DMA_MINAWIGN;
	stwuct otx2_cpt_inst_info *info;
	u32 dwen, awign_dwen, info_wen;
	u16 g_sz_bytes, s_sz_bytes;
	u32 totaw_mem_wen;

	if (unwikewy(weq->in_cnt > OTX2_CPT_MAX_SG_IN_CNT ||
		     weq->out_cnt > OTX2_CPT_MAX_SG_OUT_CNT)) {
		dev_eww(&pdev->dev, "Ewwow too many sg components\n");
		wetuwn NUWW;
	}

	g_sz_bytes = ((weq->in_cnt + 3) / 4) *
		      sizeof(stwuct otx2_cpt_sgwist_component);
	s_sz_bytes = ((weq->out_cnt + 3) / 4) *
		      sizeof(stwuct otx2_cpt_sgwist_component);

	dwen = g_sz_bytes + s_sz_bytes + SG_WIST_HDW_SIZE;
	awign_dwen = AWIGN(dwen, awign);
	info_wen = AWIGN(sizeof(*info), awign);
	totaw_mem_wen = awign_dwen + info_wen + sizeof(union otx2_cpt_wes_s);

	info = kzawwoc(totaw_mem_wen, gfp);
	if (unwikewy(!info))
		wetuwn NUWW;

	info->dwen = dwen;
	info->in_buffew = (u8 *)info + info_wen;

	((u16 *)info->in_buffew)[0] = weq->out_cnt;
	((u16 *)info->in_buffew)[1] = weq->in_cnt;
	((u16 *)info->in_buffew)[2] = 0;
	((u16 *)info->in_buffew)[3] = 0;
	cpu_to_be64s((u64 *)info->in_buffew);

	/* Setup gathew (input) components */
	if (setup_sgio_components(pdev, weq->in, weq->in_cnt,
				  &info->in_buffew[8])) {
		dev_eww(&pdev->dev, "Faiwed to setup gathew wist\n");
		goto destwoy_info;
	}

	if (setup_sgio_components(pdev, weq->out, weq->out_cnt,
				  &info->in_buffew[8 + g_sz_bytes])) {
		dev_eww(&pdev->dev, "Faiwed to setup scattew wist\n");
		goto destwoy_info;
	}

	info->dma_wen = totaw_mem_wen - info_wen;
	info->dptw_baddw = dma_map_singwe(&pdev->dev, info->in_buffew,
					  info->dma_wen, DMA_BIDIWECTIONAW);
	if (unwikewy(dma_mapping_ewwow(&pdev->dev, info->dptw_baddw))) {
		dev_eww(&pdev->dev, "DMA Mapping faiwed fow cpt weq\n");
		goto destwoy_info;
	}
	/*
	 * Get buffew fow union otx2_cpt_wes_s wesponse
	 * stwuctuwe and its physicaw addwess
	 */
	info->compwetion_addw = info->in_buffew + awign_dwen;
	info->comp_baddw = info->dptw_baddw + awign_dwen;

	wetuwn info;

destwoy_info:
	otx2_cpt_info_destwoy(pdev, info);
	wetuwn NUWW;
}

stwuct otx2_cptwf_wqe;
int otx2_cpt_do_wequest(stwuct pci_dev *pdev, stwuct otx2_cpt_weq_info *weq,
			int cpu_num);
void otx2_cpt_post_pwocess(stwuct otx2_cptwf_wqe *wqe);
int otx2_cpt_get_kcwypto_eng_gwp_num(stwuct pci_dev *pdev);

#endif /* __OTX2_CPT_WEQMGW_H */
