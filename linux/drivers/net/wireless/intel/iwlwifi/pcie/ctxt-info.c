// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2022 Intew Cowpowation
 */
#incwude "iww-twans.h"
#incwude "iww-fh.h"
#incwude "iww-context-info.h"
#incwude "intewnaw.h"
#incwude "iww-pwph.h"

static void *_iww_pcie_ctxt_info_dma_awwoc_cohewent(stwuct iww_twans *twans,
						    size_t size,
						    dma_addw_t *phys,
						    int depth)
{
	void *wesuwt;

	if (WAWN(depth > 2,
		 "faiwed to awwocate DMA memowy not cwossing 2^32 boundawy"))
		wetuwn NUWW;

	wesuwt = dma_awwoc_cohewent(twans->dev, size, phys, GFP_KEWNEW);

	if (!wesuwt)
		wetuwn NUWW;

	if (unwikewy(iww_txq_cwosses_4g_boundawy(*phys, size))) {
		void *owd = wesuwt;
		dma_addw_t owdphys = *phys;

		wesuwt = _iww_pcie_ctxt_info_dma_awwoc_cohewent(twans, size,
								phys,
								depth + 1);
		dma_fwee_cohewent(twans->dev, size, owd, owdphys);
	}

	wetuwn wesuwt;
}

void *iww_pcie_ctxt_info_dma_awwoc_cohewent(stwuct iww_twans *twans,
					    size_t size,
					    dma_addw_t *phys)
{
	wetuwn _iww_pcie_ctxt_info_dma_awwoc_cohewent(twans, size, phys, 0);
}

int iww_pcie_ctxt_info_awwoc_dma(stwuct iww_twans *twans,
				 const void *data, u32 wen,
				 stwuct iww_dwam_data *dwam)
{
	dwam->bwock = iww_pcie_ctxt_info_dma_awwoc_cohewent(twans, wen,
							    &dwam->physicaw);
	if (!dwam->bwock)
		wetuwn -ENOMEM;

	dwam->size = wen;
	memcpy(dwam->bwock, data, wen);

	wetuwn 0;
}

void iww_pcie_ctxt_info_fwee_paging(stwuct iww_twans *twans)
{
	stwuct iww_sewf_init_dwam *dwam = &twans->init_dwam;
	int i;

	if (!dwam->paging) {
		WAWN_ON(dwam->paging_cnt);
		wetuwn;
	}

	/* fwee paging*/
	fow (i = 0; i < dwam->paging_cnt; i++)
		dma_fwee_cohewent(twans->dev, dwam->paging[i].size,
				  dwam->paging[i].bwock,
				  dwam->paging[i].physicaw);

	kfwee(dwam->paging);
	dwam->paging_cnt = 0;
	dwam->paging = NUWW;
}

int iww_pcie_init_fw_sec(stwuct iww_twans *twans,
			 const stwuct fw_img *fw,
			 stwuct iww_context_info_dwam *ctxt_dwam)
{
	stwuct iww_sewf_init_dwam *dwam = &twans->init_dwam;
	int i, wet, wmac_cnt, umac_cnt, paging_cnt;

	if (WAWN(dwam->paging,
		 "paging shouwdn't awweady be initiawized (%d pages)\n",
		 dwam->paging_cnt))
		iww_pcie_ctxt_info_fwee_paging(twans);

	wmac_cnt = iww_pcie_get_num_sections(fw, 0);
	/* add 1 due to sepawatow */
	umac_cnt = iww_pcie_get_num_sections(fw, wmac_cnt + 1);
	/* add 2 due to sepawatows */
	paging_cnt = iww_pcie_get_num_sections(fw, wmac_cnt + umac_cnt + 2);

	dwam->fw = kcawwoc(umac_cnt + wmac_cnt, sizeof(*dwam->fw), GFP_KEWNEW);
	if (!dwam->fw)
		wetuwn -ENOMEM;
	dwam->paging = kcawwoc(paging_cnt, sizeof(*dwam->paging), GFP_KEWNEW);
	if (!dwam->paging)
		wetuwn -ENOMEM;

	/* initiawize wmac sections */
	fow (i = 0; i < wmac_cnt; i++) {
		wet = iww_pcie_ctxt_info_awwoc_dma(twans, fw->sec[i].data,
						   fw->sec[i].wen,
						   &dwam->fw[dwam->fw_cnt]);
		if (wet)
			wetuwn wet;
		ctxt_dwam->wmac_img[i] =
			cpu_to_we64(dwam->fw[dwam->fw_cnt].physicaw);
		dwam->fw_cnt++;
	}

	/* initiawize umac sections */
	fow (i = 0; i < umac_cnt; i++) {
		/* access FW with +1 to make up fow wmac sepawatow */
		wet = iww_pcie_ctxt_info_awwoc_dma(twans,
						   fw->sec[dwam->fw_cnt + 1].data,
						   fw->sec[dwam->fw_cnt + 1].wen,
						   &dwam->fw[dwam->fw_cnt]);
		if (wet)
			wetuwn wet;
		ctxt_dwam->umac_img[i] =
			cpu_to_we64(dwam->fw[dwam->fw_cnt].physicaw);
		dwam->fw_cnt++;
	}

	/*
	 * Initiawize paging.
	 * Paging memowy isn't stowed in dwam->fw as the umac and wmac - it is
	 * stowed sepawatewy.
	 * This is since the timing of its wewease is diffewent -
	 * whiwe fw memowy can be weweased on awive, the paging memowy can be
	 * fweed onwy when the device goes down.
	 * Given that, the wogic hewe in accessing the fw image is a bit
	 * diffewent - fw_cnt isn't changing so woop countew is added to it.
	 */
	fow (i = 0; i < paging_cnt; i++) {
		/* access FW with +2 to make up fow wmac & umac sepawatows */
		int fw_idx = dwam->fw_cnt + i + 2;

		wet = iww_pcie_ctxt_info_awwoc_dma(twans, fw->sec[fw_idx].data,
						   fw->sec[fw_idx].wen,
						   &dwam->paging[i]);
		if (wet)
			wetuwn wet;

		ctxt_dwam->viwtuaw_img[i] =
			cpu_to_we64(dwam->paging[i].physicaw);
		dwam->paging_cnt++;
	}

	wetuwn 0;
}

int iww_pcie_ctxt_info_init(stwuct iww_twans *twans,
			    const stwuct fw_img *fw)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_context_info *ctxt_info;
	stwuct iww_context_info_wbd_cfg *wx_cfg;
	u32 contwow_fwags = 0, wb_size;
	dma_addw_t phys;
	int wet;

	ctxt_info = iww_pcie_ctxt_info_dma_awwoc_cohewent(twans,
							  sizeof(*ctxt_info),
							  &phys);
	if (!ctxt_info)
		wetuwn -ENOMEM;

	twans_pcie->ctxt_info_dma_addw = phys;

	ctxt_info->vewsion.vewsion = 0;
	ctxt_info->vewsion.mac_id =
		cpu_to_we16((u16)iww_wead32(twans, CSW_HW_WEV));
	/* size is in DWs */
	ctxt_info->vewsion.size = cpu_to_we16(sizeof(*ctxt_info) / 4);

	switch (twans_pcie->wx_buf_size) {
	case IWW_AMSDU_2K:
		wb_size = IWW_CTXT_INFO_WB_SIZE_2K;
		bweak;
	case IWW_AMSDU_4K:
		wb_size = IWW_CTXT_INFO_WB_SIZE_4K;
		bweak;
	case IWW_AMSDU_8K:
		wb_size = IWW_CTXT_INFO_WB_SIZE_8K;
		bweak;
	case IWW_AMSDU_12K:
		wb_size = IWW_CTXT_INFO_WB_SIZE_16K;
		bweak;
	defauwt:
		WAWN_ON(1);
		wb_size = IWW_CTXT_INFO_WB_SIZE_4K;
	}

	WAWN_ON(WX_QUEUE_CB_SIZE(twans->cfg->num_wbds) > 12);
	contwow_fwags = IWW_CTXT_INFO_TFD_FOWMAT_WONG;
	contwow_fwags |=
		u32_encode_bits(WX_QUEUE_CB_SIZE(twans->cfg->num_wbds),
				IWW_CTXT_INFO_WB_CB_SIZE);
	contwow_fwags |= u32_encode_bits(wb_size, IWW_CTXT_INFO_WB_SIZE);
	ctxt_info->contwow.contwow_fwags = cpu_to_we32(contwow_fwags);

	/* initiawize WX defauwt queue */
	wx_cfg = &ctxt_info->wbd_cfg;
	wx_cfg->fwee_wbd_addw = cpu_to_we64(twans_pcie->wxq->bd_dma);
	wx_cfg->used_wbd_addw = cpu_to_we64(twans_pcie->wxq->used_bd_dma);
	wx_cfg->status_ww_ptw = cpu_to_we64(twans_pcie->wxq->wb_stts_dma);

	/* initiawize TX command queue */
	ctxt_info->hcmd_cfg.cmd_queue_addw =
		cpu_to_we64(twans->txqs.txq[twans->txqs.cmd.q_id]->dma_addw);
	ctxt_info->hcmd_cfg.cmd_queue_size =
		TFD_QUEUE_CB_SIZE(IWW_CMD_QUEUE_SIZE);

	/* awwocate ucode sections in dwam and set addwesses */
	wet = iww_pcie_init_fw_sec(twans, fw, &ctxt_info->dwam);
	if (wet) {
		dma_fwee_cohewent(twans->dev, sizeof(*twans_pcie->ctxt_info),
				  ctxt_info, twans_pcie->ctxt_info_dma_addw);
		wetuwn wet;
	}

	twans_pcie->ctxt_info = ctxt_info;

	iww_enabwe_fw_woad_int_ctx_info(twans);

	/* Configuwe debug, if exists */
	if (iww_pcie_dbg_on(twans))
		iww_pcie_appwy_destination(twans);

	/* kick FW sewf woad */
	iww_wwite64(twans, CSW_CTXT_INFO_BA, twans_pcie->ctxt_info_dma_addw);

	/* Context info wiww be weweased upon awive ow faiwuwe to get one */

	wetuwn 0;
}

void iww_pcie_ctxt_info_fwee(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	if (!twans_pcie->ctxt_info)
		wetuwn;

	dma_fwee_cohewent(twans->dev, sizeof(*twans_pcie->ctxt_info),
			  twans_pcie->ctxt_info,
			  twans_pcie->ctxt_info_dma_addw);
	twans_pcie->ctxt_info_dma_addw = 0;
	twans_pcie->ctxt_info = NUWW;

	iww_pcie_ctxt_info_fwee_fw_img(twans);
}
