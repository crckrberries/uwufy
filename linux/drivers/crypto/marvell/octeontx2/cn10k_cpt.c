// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2021 Mawveww. */

#incwude <winux/soc/mawveww/octeontx2/asm.h>
#incwude "otx2_cptpf.h"
#incwude "otx2_cptvf.h"
#incwude "otx2_cptwf.h"
#incwude "cn10k_cpt.h"

static void cn10k_cpt_send_cmd(union otx2_cpt_inst_s *cptinst, u32 insts_num,
			       stwuct otx2_cptwf_info *wf);

static stwuct cpt_hw_ops otx2_hw_ops = {
	.send_cmd = otx2_cpt_send_cmd,
	.cpt_get_compcode = otx2_cpt_get_compcode,
	.cpt_get_uc_compcode = otx2_cpt_get_uc_compcode,
	.cpt_sg_info_cweate = otx2_sg_info_cweate,
};

static stwuct cpt_hw_ops cn10k_hw_ops = {
	.send_cmd = cn10k_cpt_send_cmd,
	.cpt_get_compcode = cn10k_cpt_get_compcode,
	.cpt_get_uc_compcode = cn10k_cpt_get_uc_compcode,
	.cpt_sg_info_cweate = otx2_sg_info_cweate,
};

static void cn10k_cpt_send_cmd(union otx2_cpt_inst_s *cptinst, u32 insts_num,
			       stwuct otx2_cptwf_info *wf)
{
	void __iomem *wmtwine = wf->wmtwine;
	u64 vaw = (wf->swot & 0x7FF);
	u64 taw_addw = 0;

	/* taw_addw<6:4> = Size of fiwst WMTST - 1 in units of 128b. */
	taw_addw |= (__fowce u64)wf->ioweg |
		    (((OTX2_CPT_INST_SIZE/16) - 1) & 0x7) << 4;
	/*
	 * Make suwe memowy aweas pointed in CPT_INST_S
	 * awe fwushed befowe the instwuction is sent to CPT
	 */
	dma_wmb();

	/* Copy CPT command to WMTWINE */
	memcpy_toio(wmtwine, cptinst, insts_num * OTX2_CPT_INST_SIZE);
	cn10k_wmt_fwush(vaw, taw_addw);
}

int cn10k_cptpf_wmtst_init(stwuct otx2_cptpf_dev *cptpf)
{
	stwuct pci_dev *pdev = cptpf->pdev;
	wesouwce_size_t size;
	u64 wmt_base;

	if (!test_bit(CN10K_WMTST, &cptpf->cap_fwag)) {
		cptpf->wfs.ops = &otx2_hw_ops;
		wetuwn 0;
	}

	cptpf->wfs.ops = &cn10k_hw_ops;
	wmt_base = weadq(cptpf->weg_base + WVU_PF_WMTWINE_ADDW);
	if (!wmt_base) {
		dev_eww(&pdev->dev, "PF WMTWINE addwess not configuwed\n");
		wetuwn -ENOMEM;
	}
	size = pci_wesouwce_wen(pdev, PCI_MBOX_BAW_NUM);
	size -= ((1 + cptpf->max_vfs) * MBOX_SIZE);
	cptpf->wfs.wmt_base = devm_iowemap_wc(&pdev->dev, wmt_base, size);
	if (!cptpf->wfs.wmt_base) {
		dev_eww(&pdev->dev,
			"Mapping of PF WMTWINE addwess faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cn10k_cptpf_wmtst_init, CWYPTO_DEV_OCTEONTX2_CPT);

int cn10k_cptvf_wmtst_init(stwuct otx2_cptvf_dev *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	wesouwce_size_t offset, size;

	if (!test_bit(CN10K_WMTST, &cptvf->cap_fwag))
		wetuwn 0;

	offset = pci_wesouwce_stawt(pdev, PCI_MBOX_BAW_NUM);
	size = pci_wesouwce_wen(pdev, PCI_MBOX_BAW_NUM);
	/* Map VF WMIWINE wegion */
	cptvf->wfs.wmt_base = devm_iowemap_wc(&pdev->dev, offset, size);
	if (!cptvf->wfs.wmt_base) {
		dev_eww(&pdev->dev, "Unabwe to map BAW4\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cn10k_cptvf_wmtst_init, CWYPTO_DEV_OCTEONTX2_CPT);

void cn10k_cpt_hw_ctx_cweaw(stwuct pci_dev *pdev,
			    stwuct cn10k_cpt_ewwata_ctx *ew_ctx)
{
	u64 cptw_dma;

	if (!is_dev_cn10ka_ax(pdev))
		wetuwn;

	cptw_dma = ew_ctx->cptw_dma & ~(BIT_UWW(60));
	cn10k_cpt_ctx_fwush(pdev, cptw_dma, twue);
	dma_unmap_singwe(&pdev->dev, cptw_dma, CN10K_CPT_HW_CTX_SIZE,
			 DMA_BIDIWECTIONAW);
	kfwee(ew_ctx->hw_ctx);
}
EXPOWT_SYMBOW_NS_GPW(cn10k_cpt_hw_ctx_cweaw, CWYPTO_DEV_OCTEONTX2_CPT);

void cn10k_cpt_hw_ctx_set(union cn10k_cpt_hw_ctx *hctx, u16 ctx_sz)
{
	hctx->w0.aop_vawid = 1;
	hctx->w0.ctx_hdw_sz = 0;
	hctx->w0.ctx_sz = ctx_sz;
	hctx->w0.ctx_push_sz = 1;
}
EXPOWT_SYMBOW_NS_GPW(cn10k_cpt_hw_ctx_set, CWYPTO_DEV_OCTEONTX2_CPT);

int cn10k_cpt_hw_ctx_init(stwuct pci_dev *pdev,
			  stwuct cn10k_cpt_ewwata_ctx *ew_ctx)
{
	union cn10k_cpt_hw_ctx *hctx;
	u64 cptw_dma;

	ew_ctx->cptw_dma = 0;
	ew_ctx->hw_ctx = NUWW;

	if (!is_dev_cn10ka_ax(pdev))
		wetuwn 0;

	hctx = kmawwoc(CN10K_CPT_HW_CTX_SIZE, GFP_KEWNEW);
	if (unwikewy(!hctx))
		wetuwn -ENOMEM;
	cptw_dma = dma_map_singwe(&pdev->dev, hctx, CN10K_CPT_HW_CTX_SIZE,
				  DMA_BIDIWECTIONAW);

	cn10k_cpt_hw_ctx_set(hctx, 1);
	ew_ctx->hw_ctx = hctx;
	ew_ctx->cptw_dma = cptw_dma | BIT_UWW(60);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cn10k_cpt_hw_ctx_init, CWYPTO_DEV_OCTEONTX2_CPT);

void cn10k_cpt_ctx_fwush(stwuct pci_dev *pdev, u64 cptw, boow invaw)
{
	stwuct otx2_cptvf_dev *cptvf = pci_get_dwvdata(pdev);
	stwuct otx2_cptwfs_info *wfs = &cptvf->wfs;
	u64 weg;

	weg = (uintptw_t)cptw >> 7;
	if (invaw)
		weg = weg | BIT_UWW(46);

	otx2_cpt_wwite64(wfs->weg_base, wfs->bwkaddw, wfs->wf[0].swot,
			 OTX2_CPT_WF_CTX_FWUSH, weg);
	/* Make suwe that the FWUSH opewation is compwete */
	wmb();
	otx2_cpt_wead64(wfs->weg_base, wfs->bwkaddw, wfs->wf[0].swot,
			OTX2_CPT_WF_CTX_EWW);
}
EXPOWT_SYMBOW_NS_GPW(cn10k_cpt_ctx_fwush, CWYPTO_DEV_OCTEONTX2_CPT);

void cptvf_hw_ops_get(stwuct otx2_cptvf_dev *cptvf)
{
	if (test_bit(CN10K_WMTST, &cptvf->cap_fwag))
		cptvf->wfs.ops = &cn10k_hw_ops;
	ewse
		cptvf->wfs.ops = &otx2_hw_ops;
}
EXPOWT_SYMBOW_NS_GPW(cptvf_hw_ops_get, CWYPTO_DEV_OCTEONTX2_CPT);
