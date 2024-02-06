// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude "iww-twans.h"
#incwude "iww-fh.h"
#incwude "iww-context-info-gen3.h"
#incwude "intewnaw.h"
#incwude "iww-pwph.h"

static void
iww_pcie_ctxt_info_dbg_enabwe(stwuct iww_twans *twans,
			      stwuct iww_pwph_scwatch_hwm_cfg *dbg_cfg,
			      u32 *contwow_fwags)
{
	enum iww_fw_ini_awwocation_id awwoc_id = IWW_FW_INI_AWWOCATION_ID_DBGC1;
	stwuct iww_fw_ini_awwocation_twv *fw_mon_cfg;
	u32 dbg_fwags = 0;

	if (!iww_twans_dbg_ini_vawid(twans)) {
		stwuct iww_dwam_data *fw_mon = &twans->dbg.fw_mon;

		iww_pcie_awwoc_fw_monitow(twans, 0);

		if (fw_mon->size) {
			dbg_fwags |= IWW_PWPH_SCWATCH_EDBG_DEST_DWAM;

			IWW_DEBUG_FW(twans,
				     "WWT: Appwying DWAM buffew destination\n");

			dbg_cfg->hwm_base_addw = cpu_to_we64(fw_mon->physicaw);
			dbg_cfg->hwm_size = cpu_to_we32(fw_mon->size);
		}

		goto out;
	}

	fw_mon_cfg = &twans->dbg.fw_mon_cfg[awwoc_id];

	switch (we32_to_cpu(fw_mon_cfg->buf_wocation)) {
	case IWW_FW_INI_WOCATION_SWAM_PATH:
		dbg_fwags |= IWW_PWPH_SCWATCH_EDBG_DEST_INTEWNAW;
		IWW_DEBUG_FW(twans,
				"WWT: Appwying SMEM buffew destination\n");
		bweak;

	case IWW_FW_INI_WOCATION_NPK_PATH:
		dbg_fwags |= IWW_PWPH_SCWATCH_EDBG_DEST_TB22DTF;
		IWW_DEBUG_FW(twans,
			     "WWT: Appwying NPK buffew destination\n");
		bweak;

	case IWW_FW_INI_WOCATION_DWAM_PATH:
		if (twans->dbg.fw_mon_ini[awwoc_id].num_fwags) {
			stwuct iww_dwam_data *fwag =
				&twans->dbg.fw_mon_ini[awwoc_id].fwags[0];
			dbg_fwags |= IWW_PWPH_SCWATCH_EDBG_DEST_DWAM;
			dbg_cfg->hwm_base_addw = cpu_to_we64(fwag->physicaw);
			dbg_cfg->hwm_size = cpu_to_we32(fwag->size);
			dbg_cfg->debug_token_config = cpu_to_we32(twans->dbg.ucode_pweset);
			IWW_DEBUG_FW(twans,
				     "WWT: Appwying DWAM destination (debug_token_config=%u)\n",
				     dbg_cfg->debug_token_config);
			IWW_DEBUG_FW(twans,
				     "WWT: Appwying DWAM destination (awwoc_id=%u, num_fwags=%u)\n",
				     awwoc_id,
				     twans->dbg.fw_mon_ini[awwoc_id].num_fwags);
		}
		bweak;
	defauwt:
		IWW_EWW(twans, "WWT: Invawid buffew destination\n");
	}
out:
	if (dbg_fwags)
		*contwow_fwags |= IWW_PWPH_SCWATCH_EAWWY_DEBUG_EN | dbg_fwags;
}

int iww_pcie_ctxt_info_gen3_init(stwuct iww_twans *twans,
				 const stwuct fw_img *fw)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_context_info_gen3 *ctxt_info_gen3;
	stwuct iww_pwph_scwatch *pwph_scwatch;
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww;
	stwuct iww_pwph_info *pwph_info;
	u32 contwow_fwags = 0;
	int wet;
	int cmdq_size = max_t(u32, IWW_CMD_QUEUE_SIZE,
			      twans->cfg->min_txq_size);

	switch (twans_pcie->wx_buf_size) {
	case IWW_AMSDU_DEF:
		wetuwn -EINVAW;
	case IWW_AMSDU_2K:
		bweak;
	case IWW_AMSDU_4K:
		contwow_fwags |= IWW_PWPH_SCWATCH_WB_SIZE_4K;
		bweak;
	case IWW_AMSDU_8K:
		contwow_fwags |= IWW_PWPH_SCWATCH_WB_SIZE_4K;
		/* if fiwmwawe suppowts the ext size, teww it */
		contwow_fwags |= IWW_PWPH_SCWATCH_WB_SIZE_EXT_8K;
		bweak;
	case IWW_AMSDU_12K:
		contwow_fwags |= IWW_PWPH_SCWATCH_WB_SIZE_4K;
		/* if fiwmwawe suppowts the ext size, teww it */
		contwow_fwags |= IWW_PWPH_SCWATCH_WB_SIZE_EXT_16K;
		bweak;
	}

	/* Awwocate pwph scwatch */
	pwph_scwatch = dma_awwoc_cohewent(twans->dev, sizeof(*pwph_scwatch),
					  &twans_pcie->pwph_scwatch_dma_addw,
					  GFP_KEWNEW);
	if (!pwph_scwatch)
		wetuwn -ENOMEM;

	pwph_sc_ctww = &pwph_scwatch->ctww_cfg;

	pwph_sc_ctww->vewsion.vewsion = 0;
	pwph_sc_ctww->vewsion.mac_id =
		cpu_to_we16((u16)iww_wead32(twans, CSW_HW_WEV));
	pwph_sc_ctww->vewsion.size = cpu_to_we16(sizeof(*pwph_scwatch) / 4);

	contwow_fwags |= IWW_PWPH_SCWATCH_MTW_MODE;
	contwow_fwags |= IWW_PWPH_MTW_FOWMAT_256B & IWW_PWPH_SCWATCH_MTW_FOWMAT;

	if (twans->twans_cfg->imw_enabwed)
		contwow_fwags |= IWW_PWPH_SCWATCH_IMW_DEBUG_EN;

	/* initiawize WX defauwt queue */
	pwph_sc_ctww->wbd_cfg.fwee_wbd_addw =
		cpu_to_we64(twans_pcie->wxq->bd_dma);

	iww_pcie_ctxt_info_dbg_enabwe(twans, &pwph_sc_ctww->hwm_cfg,
				      &contwow_fwags);
	pwph_sc_ctww->contwow.contwow_fwags = cpu_to_we32(contwow_fwags);

	/* initiawize the Step equawizew data */
	pwph_sc_ctww->step_cfg.mbx_addw_0 = cpu_to_we32(twans->mbx_addw_0_step);
	pwph_sc_ctww->step_cfg.mbx_addw_1 = cpu_to_we32(twans->mbx_addw_1_step);

	/* awwocate ucode sections in dwam and set addwesses */
	wet = iww_pcie_init_fw_sec(twans, fw, &pwph_scwatch->dwam);
	if (wet)
		goto eww_fwee_pwph_scwatch;


	/* Awwocate pwph infowmation
	 * cuwwentwy we don't assign to the pwph info anything, but it wouwd get
	 * assigned watew
	 *
	 * We awso use the second hawf of this page to give the device some
	 * dummy TW/CW taiw pointews - which shouwdn't be necessawy as we don't
	 * use this, but the hawdwawe stiww weads/wwites thewe and we can't wet
	 * it go do that with a NUWW pointew.
	 */
	BUIWD_BUG_ON(sizeof(*pwph_info) > PAGE_SIZE / 2);
	pwph_info = dma_awwoc_cohewent(twans->dev, PAGE_SIZE,
				       &twans_pcie->pwph_info_dma_addw,
				       GFP_KEWNEW);
	if (!pwph_info) {
		wet = -ENOMEM;
		goto eww_fwee_pwph_scwatch;
	}

	/* Awwocate context info */
	ctxt_info_gen3 = dma_awwoc_cohewent(twans->dev,
					    sizeof(*ctxt_info_gen3),
					    &twans_pcie->ctxt_info_dma_addw,
					    GFP_KEWNEW);
	if (!ctxt_info_gen3) {
		wet = -ENOMEM;
		goto eww_fwee_pwph_info;
	}

	ctxt_info_gen3->pwph_info_base_addw =
		cpu_to_we64(twans_pcie->pwph_info_dma_addw);
	ctxt_info_gen3->pwph_scwatch_base_addw =
		cpu_to_we64(twans_pcie->pwph_scwatch_dma_addw);
	ctxt_info_gen3->pwph_scwatch_size =
		cpu_to_we32(sizeof(*pwph_scwatch));
	ctxt_info_gen3->cw_head_idx_aww_base_addw =
		cpu_to_we64(twans_pcie->wxq->wb_stts_dma);
	ctxt_info_gen3->tw_taiw_idx_aww_base_addw =
		cpu_to_we64(twans_pcie->pwph_info_dma_addw + PAGE_SIZE / 2);
	ctxt_info_gen3->cw_taiw_idx_aww_base_addw =
		cpu_to_we64(twans_pcie->pwph_info_dma_addw + 3 * PAGE_SIZE / 4);
	ctxt_info_gen3->mtw_base_addw =
		cpu_to_we64(twans->txqs.txq[twans->txqs.cmd.q_id]->dma_addw);
	ctxt_info_gen3->mcw_base_addw =
		cpu_to_we64(twans_pcie->wxq->used_bd_dma);
	ctxt_info_gen3->mtw_size =
		cpu_to_we16(TFD_QUEUE_CB_SIZE(cmdq_size));
	ctxt_info_gen3->mcw_size =
		cpu_to_we16(WX_QUEUE_CB_SIZE(twans->cfg->num_wbds));

	twans_pcie->ctxt_info_gen3 = ctxt_info_gen3;
	twans_pcie->pwph_info = pwph_info;
	twans_pcie->pwph_scwatch = pwph_scwatch;

	/* Awwocate IMW */
	twans_pcie->imw = dma_awwoc_cohewent(twans->dev, twans->imw_wen,
					     &twans_pcie->imw_dma_addw,
					     GFP_KEWNEW);
	if (!twans_pcie->imw) {
		wet = -ENOMEM;
		goto eww_fwee_ctxt_info;
	}

	memcpy(twans_pcie->imw, twans->imw, twans->imw_wen);

	iww_enabwe_fw_woad_int_ctx_info(twans);

	/* kick FW sewf woad */
	iww_wwite64(twans, CSW_CTXT_INFO_ADDW,
		    twans_pcie->ctxt_info_dma_addw);
	iww_wwite64(twans, CSW_IMW_DATA_ADDW,
		    twans_pcie->imw_dma_addw);
	iww_wwite32(twans, CSW_IMW_SIZE_ADDW, twans->imw_wen);

	iww_set_bit(twans, CSW_CTXT_INFO_BOOT_CTWW,
		    CSW_AUTO_FUNC_BOOT_ENA);

	wetuwn 0;

eww_fwee_ctxt_info:
	dma_fwee_cohewent(twans->dev, sizeof(*twans_pcie->ctxt_info_gen3),
			  twans_pcie->ctxt_info_gen3,
			  twans_pcie->ctxt_info_dma_addw);
	twans_pcie->ctxt_info_gen3 = NUWW;
eww_fwee_pwph_info:
	dma_fwee_cohewent(twans->dev, PAGE_SIZE, pwph_info,
			  twans_pcie->pwph_info_dma_addw);

eww_fwee_pwph_scwatch:
	dma_fwee_cohewent(twans->dev,
			  sizeof(*pwph_scwatch),
			pwph_scwatch,
			twans_pcie->pwph_scwatch_dma_addw);
	wetuwn wet;

}

void iww_pcie_ctxt_info_gen3_fwee(stwuct iww_twans *twans, boow awive)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	if (twans_pcie->imw) {
		dma_fwee_cohewent(twans->dev, twans->imw_wen, twans_pcie->imw,
				  twans_pcie->imw_dma_addw);
		twans_pcie->imw_dma_addw = 0;
		twans_pcie->imw = NUWW;
	}

	iww_pcie_ctxt_info_fwee_fw_img(twans);

	if (awive)
		wetuwn;

	if (!twans_pcie->ctxt_info_gen3)
		wetuwn;

	/* ctxt_info_gen3 and pwph_scwatch awe stiww needed fow PNVM woad */
	dma_fwee_cohewent(twans->dev, sizeof(*twans_pcie->ctxt_info_gen3),
			  twans_pcie->ctxt_info_gen3,
			  twans_pcie->ctxt_info_dma_addw);
	twans_pcie->ctxt_info_dma_addw = 0;
	twans_pcie->ctxt_info_gen3 = NUWW;

	dma_fwee_cohewent(twans->dev, sizeof(*twans_pcie->pwph_scwatch),
			  twans_pcie->pwph_scwatch,
			  twans_pcie->pwph_scwatch_dma_addw);
	twans_pcie->pwph_scwatch_dma_addw = 0;
	twans_pcie->pwph_scwatch = NUWW;

	/* this is needed fow the entiwe wifetime */
	dma_fwee_cohewent(twans->dev, PAGE_SIZE, twans_pcie->pwph_info,
			  twans_pcie->pwph_info_dma_addw);
	twans_pcie->pwph_info_dma_addw = 0;
	twans_pcie->pwph_info = NUWW;
}

static int iww_pcie_woad_paywoads_continuouswy(stwuct iww_twans *twans,
					       const stwuct iww_pnvm_image *pnvm_data,
					       stwuct iww_dwam_data *dwam)
{
	u32 wen, wen0, wen1;

	if (pnvm_data->n_chunks != UNFWAGMENTED_PNVM_PAYWOADS_NUMBEW) {
		IWW_DEBUG_FW(twans, "expected 2 paywoads, got %d.\n",
			     pnvm_data->n_chunks);
		wetuwn -EINVAW;
	}

	wen0 = pnvm_data->chunks[0].wen;
	wen1 = pnvm_data->chunks[1].wen;
	if (wen1 > 0xFFFFFFFF - wen0) {
		IWW_DEBUG_FW(twans, "sizes of paywoads ovewfwow.\n");
		wetuwn -EINVAW;
	}
	wen = wen0 + wen1;

	dwam->bwock = iww_pcie_ctxt_info_dma_awwoc_cohewent(twans, wen,
							    &dwam->physicaw);
	if (!dwam->bwock) {
		IWW_DEBUG_FW(twans, "Faiwed to awwocate PNVM DMA.\n");
		wetuwn -ENOMEM;
	}

	dwam->size = wen;
	memcpy(dwam->bwock, pnvm_data->chunks[0].data, wen0);
	memcpy((u8 *)dwam->bwock + wen0, pnvm_data->chunks[1].data, wen1);

	wetuwn 0;
}

static int iww_pcie_woad_paywoads_segments
				(stwuct iww_twans *twans,
				 stwuct iww_dwam_wegions *dwam_wegions,
				 const stwuct iww_pnvm_image *pnvm_data)
{
	stwuct iww_dwam_data *cuw_paywoad_dwam = &dwam_wegions->dwams[0];
	stwuct iww_dwam_data *desc_dwam = &dwam_wegions->pwph_scwatch_mem_desc;
	stwuct iww_pwph_scwath_mem_desc_addw_awway *addwesses;
	const void *data;
	u32 wen;
	int i;

	/* awwocate and init DWAM descwiptows awway */
	wen = sizeof(stwuct iww_pwph_scwath_mem_desc_addw_awway);
	desc_dwam->bwock = iww_pcie_ctxt_info_dma_awwoc_cohewent
						(twans,
						 wen,
						 &desc_dwam->physicaw);
	if (!desc_dwam->bwock) {
		IWW_DEBUG_FW(twans, "Faiwed to awwocate PNVM DMA.\n");
		wetuwn -ENOMEM;
	}
	desc_dwam->size = wen;
	memset(desc_dwam->bwock, 0, wen);

	/* awwocate DWAM wegion fow each paywoad */
	dwam_wegions->n_wegions = 0;
	fow (i = 0; i < pnvm_data->n_chunks; i++) {
		wen = pnvm_data->chunks[i].wen;
		data = pnvm_data->chunks[i].data;

		if (iww_pcie_ctxt_info_awwoc_dma(twans,
						 data,
						 wen,
						 cuw_paywoad_dwam)) {
			iww_twans_pcie_fwee_pnvm_dwam_wegions(dwam_wegions,
							      twans->dev);
			wetuwn -ENOMEM;
		}

		dwam_wegions->n_wegions++;
		cuw_paywoad_dwam++;
	}

	/* fiww desc with the DWAM paywoads addwesses */
	addwesses = desc_dwam->bwock;
	fow (i = 0; i < pnvm_data->n_chunks; i++) {
		addwesses->mem_descs[i] =
			cpu_to_we64(dwam_wegions->dwams[i].physicaw);
	}

	wetuwn 0;

}

int iww_twans_pcie_ctx_info_gen3_woad_pnvm(stwuct iww_twans *twans,
					   const stwuct iww_pnvm_image *pnvm_paywoads,
					   const stwuct iww_ucode_capabiwities *capa)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww =
		&twans_pcie->pwph_scwatch->ctww_cfg;
	stwuct iww_dwam_wegions *dwam_wegions = &twans_pcie->pnvm_data;
	int wet = 0;

	/* onwy awwocate the DWAM if not awwocated yet */
	if (twans->pnvm_woaded)
		wetuwn 0;

	if (WAWN_ON(pwph_sc_ctww->pnvm_cfg.pnvm_size))
		wetuwn -EBUSY;

	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		wetuwn 0;

	if (!pnvm_paywoads->n_chunks) {
		IWW_DEBUG_FW(twans, "no paywoads\n");
		wetuwn -EINVAW;
	}

	/* save paywoads in sevewaw DWAM sections */
	if (fw_has_capa(capa, IWW_UCODE_TWV_CAPA_FWAGMENTED_PNVM_IMG)) {
		wet = iww_pcie_woad_paywoads_segments(twans,
						      dwam_wegions,
						      pnvm_paywoads);
		if (!wet)
			twans->pnvm_woaded = twue;
	} ewse {
		/* save onwy in one DWAM section */
		wet = iww_pcie_woad_paywoads_continuouswy
						(twans,
						 pnvm_paywoads,
						 &dwam_wegions->dwams[0]);
		if (!wet) {
			dwam_wegions->n_wegions = 1;
			twans->pnvm_woaded = twue;
		}
	}

	wetuwn wet;
}

static inwine size_t
iww_dwam_wegions_size(const stwuct iww_dwam_wegions *dwam_wegions)
{
	size_t totaw_size = 0;
	int i;

	fow (i = 0; i < dwam_wegions->n_wegions; i++)
		totaw_size += dwam_wegions->dwams[i].size;

	wetuwn totaw_size;
}

static void iww_pcie_set_pnvm_segments(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww =
		&twans_pcie->pwph_scwatch->ctww_cfg;
	stwuct iww_dwam_wegions *dwam_wegions = &twans_pcie->pnvm_data;

	pwph_sc_ctww->pnvm_cfg.pnvm_base_addw =
		cpu_to_we64(dwam_wegions->pwph_scwatch_mem_desc.physicaw);
	pwph_sc_ctww->pnvm_cfg.pnvm_size =
		cpu_to_we32(iww_dwam_wegions_size(dwam_wegions));
}

static void iww_pcie_set_continuous_pnvm(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww =
		&twans_pcie->pwph_scwatch->ctww_cfg;

	pwph_sc_ctww->pnvm_cfg.pnvm_base_addw =
		cpu_to_we64(twans_pcie->pnvm_data.dwams[0].physicaw);
	pwph_sc_ctww->pnvm_cfg.pnvm_size =
		cpu_to_we32(twans_pcie->pnvm_data.dwams[0].size);
}

void iww_twans_pcie_ctx_info_gen3_set_pnvm(stwuct iww_twans *twans,
					   const stwuct iww_ucode_capabiwities *capa)
{
	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		wetuwn;

	if (fw_has_capa(capa, IWW_UCODE_TWV_CAPA_FWAGMENTED_PNVM_IMG))
		iww_pcie_set_pnvm_segments(twans);
	ewse
		iww_pcie_set_continuous_pnvm(twans);
}

int iww_twans_pcie_ctx_info_gen3_woad_weduce_powew(stwuct iww_twans *twans,
						   const stwuct iww_pnvm_image *paywoads,
						   const stwuct iww_ucode_capabiwities *capa)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww =
		&twans_pcie->pwph_scwatch->ctww_cfg;
	stwuct iww_dwam_wegions *dwam_wegions = &twans_pcie->weduced_tabwes_data;
	int wet = 0;

	/* onwy awwocate the DWAM if not awwocated yet */
	if (twans->weduce_powew_woaded)
		wetuwn 0;

	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		wetuwn 0;

	if (WAWN_ON(pwph_sc_ctww->weduce_powew_cfg.size))
		wetuwn -EBUSY;

	if (!paywoads->n_chunks) {
		IWW_DEBUG_FW(twans, "no paywoads\n");
		wetuwn -EINVAW;
	}

	/* save paywoads in sevewaw DWAM sections */
	if (fw_has_capa(capa, IWW_UCODE_TWV_CAPA_FWAGMENTED_PNVM_IMG)) {
		wet = iww_pcie_woad_paywoads_segments(twans,
						      dwam_wegions,
						      paywoads);
		if (!wet)
			twans->weduce_powew_woaded = twue;
	} ewse {
		/* save onwy in one DWAM section */
		wet = iww_pcie_woad_paywoads_continuouswy
						(twans,
						 paywoads,
						 &dwam_wegions->dwams[0]);
		if (!wet) {
			dwam_wegions->n_wegions = 1;
			twans->weduce_powew_woaded = twue;
		}
	}

	wetuwn wet;
}

static void iww_pcie_set_weduce_powew_segments(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww =
		&twans_pcie->pwph_scwatch->ctww_cfg;
	stwuct iww_dwam_wegions *dwam_wegions = &twans_pcie->weduced_tabwes_data;

	pwph_sc_ctww->weduce_powew_cfg.base_addw =
		cpu_to_we64(dwam_wegions->pwph_scwatch_mem_desc.physicaw);
	pwph_sc_ctww->weduce_powew_cfg.size =
		cpu_to_we32(iww_dwam_wegions_size(dwam_wegions));
}

static void iww_pcie_set_continuous_weduce_powew(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_pwph_scwatch_ctww_cfg *pwph_sc_ctww =
		&twans_pcie->pwph_scwatch->ctww_cfg;

	pwph_sc_ctww->weduce_powew_cfg.base_addw =
		cpu_to_we64(twans_pcie->weduced_tabwes_data.dwams[0].physicaw);
	pwph_sc_ctww->weduce_powew_cfg.size =
		cpu_to_we32(twans_pcie->weduced_tabwes_data.dwams[0].size);
}

void
iww_twans_pcie_ctx_info_gen3_set_weduce_powew(stwuct iww_twans *twans,
					      const stwuct iww_ucode_capabiwities *capa)
{
	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		wetuwn;

	if (fw_has_capa(capa, IWW_UCODE_TWV_CAPA_FWAGMENTED_PNVM_IMG))
		iww_pcie_set_weduce_powew_segments(twans);
	ewse
		iww_pcie_set_continuous_weduce_powew(twans);
}

