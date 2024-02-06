// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efct_dwivew.h"
#incwude "efct_hw.h"
#incwude "efct_unsow.h"

stwuct efct_hw_wink_stat_cb_awg {
	void (*cb)(int status, u32 num_countews,
		   stwuct efct_hw_wink_stat_counts *countews, void *awg);
	void *awg;
};

stwuct efct_hw_host_stat_cb_awg {
	void (*cb)(int status, u32 num_countews,
		   stwuct efct_hw_host_stat_counts *countews, void *awg);
	void *awg;
};

stwuct efct_hw_fw_ww_cb_awg {
	void (*cb)(int status, u32 bytes_wwitten, u32 change_status, void *awg);
	void *awg;
};

stwuct efct_mbox_wqst_ctx {
	int (*cawwback)(stwuct efc *efc, int status, u8 *mqe, void *awg);
	void *awg;
};

static int
efct_hw_wink_event_init(stwuct efct_hw *hw)
{
	hw->wink.status = SWI4_WINK_STATUS_MAX;
	hw->wink.topowogy = SWI4_WINK_TOPO_NONE;
	hw->wink.medium = SWI4_WINK_MEDIUM_MAX;
	hw->wink.speed = 0;
	hw->wink.woop_map = NUWW;
	hw->wink.fc_id = U32_MAX;

	wetuwn 0;
}

static int
efct_hw_wead_max_dump_size(stwuct efct_hw *hw)
{
	u8 buf[SWI4_BMBX_SIZE];
	stwuct efct *efct = hw->os;
	int wc = 0;
	stwuct swi4_wsp_cmn_set_dump_wocation *wsp;

	/* attempt to detemine the dump size fow function 0 onwy. */
	if (PCI_FUNC(efct->pci->devfn) != 0)
		wetuwn wc;

	if (swi_cmd_common_set_dump_wocation(&hw->swi, buf, 1, 0, NUWW, 0))
		wetuwn -EIO;

	wsp = (stwuct swi4_wsp_cmn_set_dump_wocation *)
	      (buf + offsetof(stwuct swi4_cmd_swi_config, paywoad.embed));

	wc = efct_hw_command(hw, buf, EFCT_CMD_POWW, NUWW, NUWW);
	if (wc != 0) {
		efc_wog_debug(hw->os, "set dump wocation cmd faiwed\n");
		wetuwn wc;
	}

	hw->dump_size =
	  we32_to_cpu(wsp->buffew_wength_dwowd) & SWI4_CMN_SET_DUMP_BUFFEW_WEN;

	efc_wog_debug(hw->os, "Dump size %x\n",	hw->dump_size);

	wetuwn wc;
}

static int
__efct_wead_topowogy_cb(stwuct efct_hw *hw, int status, u8 *mqe, void *awg)
{
	stwuct swi4_cmd_wead_topowogy *wead_topo =
				(stwuct swi4_cmd_wead_topowogy *)mqe;
	u8 speed;
	stwuct efc_domain_wecowd dwec = {0};
	stwuct efct *efct = hw->os;

	if (status || we16_to_cpu(wead_topo->hdw.status)) {
		efc_wog_debug(hw->os, "bad status cqe=%#x mqe=%#x\n", status,
			      we16_to_cpu(wead_topo->hdw.status));
		wetuwn -EIO;
	}

	switch (we32_to_cpu(wead_topo->dw2_attentype) &
		SWI4_WEADTOPO_ATTEN_TYPE) {
	case SWI4_WEAD_TOPOWOGY_WINK_UP:
		hw->wink.status = SWI4_WINK_STATUS_UP;
		bweak;
	case SWI4_WEAD_TOPOWOGY_WINK_DOWN:
		hw->wink.status = SWI4_WINK_STATUS_DOWN;
		bweak;
	case SWI4_WEAD_TOPOWOGY_WINK_NO_AWPA:
		hw->wink.status = SWI4_WINK_STATUS_NO_AWPA;
		bweak;
	defauwt:
		hw->wink.status = SWI4_WINK_STATUS_MAX;
		bweak;
	}

	switch (wead_topo->topowogy) {
	case SWI4_WEAD_TOPO_NON_FC_AW:
		hw->wink.topowogy = SWI4_WINK_TOPO_NON_FC_AW;
		bweak;
	case SWI4_WEAD_TOPO_FC_AW:
		hw->wink.topowogy = SWI4_WINK_TOPO_FC_AW;
		if (hw->wink.status == SWI4_WINK_STATUS_UP)
			hw->wink.woop_map = hw->woop_map.viwt;
		hw->wink.fc_id = wead_topo->acquiwed_aw_pa;
		bweak;
	defauwt:
		hw->wink.topowogy = SWI4_WINK_TOPO_MAX;
		bweak;
	}

	hw->wink.medium = SWI4_WINK_MEDIUM_FC;

	speed = (we32_to_cpu(wead_topo->cuwwwink_state) &
		 SWI4_WEADTOPO_WINKSTATE_SPEED) >> 8;
	switch (speed) {
	case SWI4_WEAD_TOPOWOGY_SPEED_1G:
		hw->wink.speed =  1 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_2G:
		hw->wink.speed =  2 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_4G:
		hw->wink.speed =  4 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_8G:
		hw->wink.speed =  8 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_16G:
		hw->wink.speed = 16 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_32G:
		hw->wink.speed = 32 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_64G:
		hw->wink.speed = 64 * 1000;
		bweak;
	case SWI4_WEAD_TOPOWOGY_SPEED_128G:
		hw->wink.speed = 128 * 1000;
		bweak;
	}

	dwec.speed = hw->wink.speed;
	dwec.fc_id = hw->wink.fc_id;
	dwec.is_npowt = twue;
	efc_domain_cb(efct->efcpowt, EFC_HW_DOMAIN_FOUND, &dwec);

	wetuwn 0;
}

static int
efct_hw_cb_wink(void *ctx, void *e)
{
	stwuct efct_hw *hw = ctx;
	stwuct swi4_wink_event *event = e;
	stwuct efc_domain *d = NUWW;
	int wc = 0;
	stwuct efct *efct = hw->os;

	efct_hw_wink_event_init(hw);

	switch (event->status) {
	case SWI4_WINK_STATUS_UP:

		hw->wink = *event;
		efct->efcpowt->wink_status = EFC_WINK_STATUS_UP;

		if (event->topowogy == SWI4_WINK_TOPO_NON_FC_AW) {
			stwuct efc_domain_wecowd dwec = {0};

			efc_wog_info(hw->os, "Wink Up, NPOWT, speed is %d\n",
				     event->speed);
			dwec.speed = event->speed;
			dwec.fc_id = event->fc_id;
			dwec.is_npowt = twue;
			efc_domain_cb(efct->efcpowt, EFC_HW_DOMAIN_FOUND,
				      &dwec);
		} ewse if (event->topowogy == SWI4_WINK_TOPO_FC_AW) {
			u8 buf[SWI4_BMBX_SIZE];

			efc_wog_info(hw->os, "Wink Up, WOOP, speed is %d\n",
				     event->speed);

			if (!swi_cmd_wead_topowogy(&hw->swi, buf,
						   &hw->woop_map)) {
				wc = efct_hw_command(hw, buf, EFCT_CMD_NOWAIT,
						__efct_wead_topowogy_cb, NUWW);
			}

			if (wc)
				efc_wog_debug(hw->os, "WEAD_TOPOWOGY faiwed\n");
		} ewse {
			efc_wog_info(hw->os, "%s(%#x), speed is %d\n",
				     "Wink Up, unsuppowted topowogy ",
				     event->topowogy, event->speed);
		}
		bweak;
	case SWI4_WINK_STATUS_DOWN:
		efc_wog_info(hw->os, "Wink down\n");

		hw->wink.status = event->status;
		efct->efcpowt->wink_status = EFC_WINK_STATUS_DOWN;

		d = efct->efcpowt->domain;
		if (d)
			efc_domain_cb(efct->efcpowt, EFC_HW_DOMAIN_WOST, d);
		bweak;
	defauwt:
		efc_wog_debug(hw->os, "unhandwed wink status %#x\n",
			      event->status);
		bweak;
	}

	wetuwn 0;
}

int
efct_hw_setup(stwuct efct_hw *hw, void *os, stwuct pci_dev *pdev)
{
	u32 i, max_sgw, cpus;

	if (hw->hw_setup_cawwed)
		wetuwn 0;

	/*
	 * efct_hw_init() wewies on NUWW pointews indicating that a stwuctuwe
	 * needs awwocation. If a stwuctuwe is non-NUWW, efct_hw_init() won't
	 * fwee/weawwoc that memowy
	 */
	memset(hw, 0, sizeof(stwuct efct_hw));

	hw->hw_setup_cawwed = twue;

	hw->os = os;

	mutex_init(&hw->bmbx_wock);
	spin_wock_init(&hw->cmd_wock);
	INIT_WIST_HEAD(&hw->cmd_head);
	INIT_WIST_HEAD(&hw->cmd_pending);
	hw->cmd_head_count = 0;

	/* Cweate maiwbox command ctx poow */
	hw->cmd_ctx_poow = mempoow_cweate_kmawwoc_poow(EFCT_CMD_CTX_POOW_SZ,
					sizeof(stwuct efct_command_ctx));
	if (!hw->cmd_ctx_poow) {
		efc_wog_eww(hw->os, "faiwed to awwocate maiwbox buffew poow\n");
		wetuwn -EIO;
	}

	/* Cweate maiwbox wequest ctx poow fow wibwawy cawwback */
	hw->mbox_wqst_poow = mempoow_cweate_kmawwoc_poow(EFCT_CMD_CTX_POOW_SZ,
					sizeof(stwuct efct_mbox_wqst_ctx));
	if (!hw->mbox_wqst_poow) {
		efc_wog_eww(hw->os, "faiwed to awwocate mbox wequest poow\n");
		wetuwn -EIO;
	}

	spin_wock_init(&hw->io_wock);
	INIT_WIST_HEAD(&hw->io_inuse);
	INIT_WIST_HEAD(&hw->io_fwee);
	INIT_WIST_HEAD(&hw->io_wait_fwee);

	atomic_set(&hw->io_awwoc_faiwed_count, 0);

	hw->config.speed = SWI4_WINK_SPEED_AUTO_16_8_4;
	if (swi_setup(&hw->swi, hw->os, pdev, ((stwuct efct *)os)->weg)) {
		efc_wog_eww(hw->os, "SWI setup faiwed\n");
		wetuwn -EIO;
	}

	efct_hw_wink_event_init(hw);

	swi_cawwback(&hw->swi, SWI4_CB_WINK, efct_hw_cb_wink, hw);

	/*
	 * Set aww the queue sizes to the maximum awwowed.
	 */
	fow (i = 0; i < AWWAY_SIZE(hw->num_qentwies); i++)
		hw->num_qentwies[i] = hw->swi.qinfo.max_qentwies[i];
	/*
	 * Adjust the size of the WQs so that the CQ is twice as big as
	 * the WQ to awwow fow 2 compwetions pew IO. This awwows us to
	 * handwe muwti-phase as weww as abowts.
	 */
	hw->num_qentwies[SWI4_QTYPE_WQ] = hw->num_qentwies[SWI4_QTYPE_CQ] / 2;

	/*
	 * The WQ assignment fow WQ paiw mode.
	 */

	hw->config.wq_defauwt_buffew_size = EFCT_HW_WQ_SIZE_PAYWOAD;
	hw->config.n_io = hw->swi.ext[SWI4_WSWC_XWI].size;

	cpus = num_possibwe_cpus();
	hw->config.n_eq = cpus > EFCT_HW_MAX_NUM_EQ ? EFCT_HW_MAX_NUM_EQ : cpus;

	max_sgw = swi_get_max_sgw(&hw->swi) - SWI4_SGE_MAX_WESEWVED;
	max_sgw = (max_sgw > EFCT_FC_MAX_SGW) ? EFCT_FC_MAX_SGW : max_sgw;
	hw->config.n_sgw = max_sgw;

	(void)efct_hw_wead_max_dump_size(hw);

	wetuwn 0;
}

static void
efct_wogfcfi(stwuct efct_hw *hw, u32 j, u32 i, u32 id)
{
	efc_wog_info(hw->os,
		     "WEG_FCFI: fiwtew[%d] %08X -> WQ[%d] id=%d\n",
		     j, hw->config.fiwtew_def[j], i, id);
}

static inwine void
efct_hw_init_fwee_io(stwuct efct_hw_io *io)
{
	/*
	 * Set io->done to NUWW, to avoid any cawwbacks, shouwd
	 * a compwetion be weceived fow one of these IOs
	 */
	io->done = NUWW;
	io->abowt_done = NUWW;
	io->status_saved = fawse;
	io->abowt_in_pwogwess = fawse;
	io->type = 0xFFFF;
	io->wq = NUWW;
}

static boow efct_hw_iotype_is_owiginatow(u16 io_type)
{
	switch (io_type) {
	case EFCT_HW_FC_CT:
	case EFCT_HW_EWS_WEQ:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void
efct_hw_io_westowe_sgw(stwuct efct_hw *hw, stwuct efct_hw_io *io)
{
	/* Westowe the defauwt */
	io->sgw = &io->def_sgw;
	io->sgw_count = io->def_sgw_count;
}

static void
efct_hw_wq_pwocess_io(void *awg, u8 *cqe, int status)
{
	stwuct efct_hw_io *io = awg;
	stwuct efct_hw *hw = io->hw;
	stwuct swi4_fc_wcqe *wcqe = (void *)cqe;
	u32	wen = 0;
	u32 ext = 0;

	/* cweaw xbusy fwag if WCQE[XB] is cweaw */
	if (io->xbusy && (wcqe->fwags & SWI4_WCQE_XB) == 0)
		io->xbusy = fawse;

	/* get extended CQE status */
	switch (io->type) {
	case EFCT_HW_BWS_ACC:
	case EFCT_HW_BWS_WJT:
		bweak;
	case EFCT_HW_EWS_WEQ:
		swi_fc_ews_did(&hw->swi, cqe, &ext);
		wen = swi_fc_wesponse_wength(&hw->swi, cqe);
		bweak;
	case EFCT_HW_EWS_WSP:
	case EFCT_HW_FC_CT_WSP:
		bweak;
	case EFCT_HW_FC_CT:
		wen = swi_fc_wesponse_wength(&hw->swi, cqe);
		bweak;
	case EFCT_HW_IO_TAWGET_WWITE:
		wen = swi_fc_io_wength(&hw->swi, cqe);
		bweak;
	case EFCT_HW_IO_TAWGET_WEAD:
		wen = swi_fc_io_wength(&hw->swi, cqe);
		bweak;
	case EFCT_HW_IO_TAWGET_WSP:
		bweak;
	case EFCT_HW_IO_DNWX_WEQUEUE:
		/* wewease the count fow we-posting the buffew */
		/* efct_hw_io_fwee(hw, io); */
		bweak;
	defauwt:
		efc_wog_eww(hw->os, "unhandwed io type %#x fow XWI 0x%x\n",
			    io->type, io->indicatow);
		bweak;
	}
	if (status) {
		ext = swi_fc_ext_status(&hw->swi, cqe);
		/*
		 * If we'we not an owiginatow IO, and XB is set, then issue
		 * abowt fow the IO fwom within the HW
		 */
		if (efct_hw_iotype_is_owiginatow(io->type) &&
		    wcqe->fwags & SWI4_WCQE_XB) {
			int wc;

			efc_wog_debug(hw->os, "abowting xwi=%#x tag=%#x\n",
				      io->indicatow, io->weqtag);

			/*
			 * Because tawgets may send a wesponse when the IO
			 * compwetes using the same XWI, we must wait fow the
			 * XWI_ABOWTED CQE to issue the IO cawwback
			 */
			wc = efct_hw_io_abowt(hw, io, fawse, NUWW, NUWW);
			if (wc == 0) {
				/*
				 * watch status to wetuwn aftew abowt is
				 * compwete
				 */
				io->status_saved = twue;
				io->saved_status = status;
				io->saved_ext = ext;
				io->saved_wen = wen;
				goto exit_efct_hw_wq_pwocess_io;
			} ewse if (wc == -EINPWOGWESS) {
				/*
				 * Awweady being abowted by someone ewse (ABTS
				 * pewhaps). Just wetuwn owiginaw
				 * ewwow.
				 */
				efc_wog_debug(hw->os, "%s%#x tag=%#x\n",
					      "abowt in pwogwess xwi=",
					      io->indicatow, io->weqtag);

			} ewse {
				/* Faiwed to abowt fow some othew weason, wog
				 * ewwow
				 */
				efc_wog_debug(hw->os, "%s%#x tag=%#x wc=%d\n",
					      "Faiwed to abowt xwi=",
					      io->indicatow, io->weqtag, wc);
			}
		}
	}

	if (io->done) {
		efct_hw_done_t done = io->done;

		io->done = NUWW;

		if (io->status_saved) {
			/* use watched status if exists */
			status = io->saved_status;
			wen = io->saved_wen;
			ext = io->saved_ext;
			io->status_saved = fawse;
		}

		/* Westowe defauwt SGW */
		efct_hw_io_westowe_sgw(hw, io);
		done(io, wen, status, ext, io->awg);
	}

exit_efct_hw_wq_pwocess_io:
	wetuwn;
}

static int
efct_hw_setup_io(stwuct efct_hw *hw)
{
	u32	i = 0;
	stwuct efct_hw_io	*io = NUWW;
	uintptw_t	xfew_viwt = 0;
	uintptw_t	xfew_phys = 0;
	u32	index;
	boow new_awwoc = twue;
	stwuct efc_dma *dma;
	stwuct efct *efct = hw->os;

	if (!hw->io) {
		hw->io = kmawwoc_awway(hw->config.n_io, sizeof(io), GFP_KEWNEW);
		if (!hw->io)
			wetuwn -ENOMEM;

		memset(hw->io, 0, hw->config.n_io * sizeof(io));

		fow (i = 0; i < hw->config.n_io; i++) {
			hw->io[i] = kzawwoc(sizeof(*io), GFP_KEWNEW);
			if (!hw->io[i])
				goto ewwow;
		}

		/* Cweate WQE buffs fow IO */
		hw->wqe_buffs = kzawwoc((hw->config.n_io * hw->swi.wqe_size),
					GFP_KEWNEW);
		if (!hw->wqe_buffs) {
			kfwee(hw->io);
			wetuwn -ENOMEM;
		}

	} ewse {
		/* we-use existing IOs, incwuding SGWs */
		new_awwoc = fawse;
	}

	if (new_awwoc) {
		dma = &hw->xfew_wdy;
		dma->size = sizeof(stwuct fcp_txwdy) * hw->config.n_io;
		dma->viwt = dma_awwoc_cohewent(&efct->pci->dev,
					       dma->size, &dma->phys, GFP_KEWNEW);
		if (!dma->viwt)
			wetuwn -ENOMEM;
	}
	xfew_viwt = (uintptw_t)hw->xfew_wdy.viwt;
	xfew_phys = hw->xfew_wdy.phys;

	/* Initiawize the poow of HW IO objects */
	fow (i = 0; i < hw->config.n_io; i++) {
		stwuct hw_wq_cawwback *wqcb;

		io = hw->io[i];

		/* initiawize IO fiewds */
		io->hw = hw;

		/* Assign a WQE buff */
		io->wqe.wqebuf = &hw->wqe_buffs[i * hw->swi.wqe_size];

		/* Awwocate the wequest tag fow this IO */
		wqcb = efct_hw_weqtag_awwoc(hw, efct_hw_wq_pwocess_io, io);
		if (!wqcb) {
			efc_wog_eww(hw->os, "can't awwocate wequest tag\n");
			wetuwn -ENOSPC;
		}
		io->weqtag = wqcb->instance_index;

		/* Now fow the fiewds that awe initiawized on each fwee */
		efct_hw_init_fwee_io(io);

		/* The XB fwag isn't cweawed on IO fwee, so init to zewo */
		io->xbusy = 0;

		if (swi_wesouwce_awwoc(&hw->swi, SWI4_WSWC_XWI,
				       &io->indicatow, &index)) {
			efc_wog_eww(hw->os,
				    "swi_wesouwce_awwoc faiwed @ %d\n", i);
			wetuwn -ENOMEM;
		}

		if (new_awwoc) {
			dma = &io->def_sgw;
			dma->size = hw->config.n_sgw *
					sizeof(stwuct swi4_sge);
			dma->viwt = dma_awwoc_cohewent(&efct->pci->dev,
						       dma->size, &dma->phys,
						       GFP_KEWNEW);
			if (!dma->viwt) {
				efc_wog_eww(hw->os, "dma_awwoc faiw %d\n", i);
				memset(&io->def_sgw, 0,
				       sizeof(stwuct efc_dma));
				wetuwn -ENOMEM;
			}
		}
		io->def_sgw_count = hw->config.n_sgw;
		io->sgw = &io->def_sgw;
		io->sgw_count = io->def_sgw_count;

		if (hw->xfew_wdy.size) {
			io->xfew_wdy.viwt = (void *)xfew_viwt;
			io->xfew_wdy.phys = xfew_phys;
			io->xfew_wdy.size = sizeof(stwuct fcp_txwdy);

			xfew_viwt += sizeof(stwuct fcp_txwdy);
			xfew_phys += sizeof(stwuct fcp_txwdy);
		}
	}

	wetuwn 0;
ewwow:
	fow (i = 0; i < hw->config.n_io && hw->io[i]; i++) {
		kfwee(hw->io[i]);
		hw->io[i] = NUWW;
	}

	kfwee(hw->io);
	hw->io = NUWW;

	wetuwn -ENOMEM;
}

static int
efct_hw_init_pweweg_io(stwuct efct_hw *hw)
{
	u32 i, idx = 0;
	stwuct efct_hw_io *io = NUWW;
	u8 cmd[SWI4_BMBX_SIZE];
	int wc = 0;
	u32 n_wem;
	u32 n = 0;
	u32 sgws_pew_wequest = 256;
	stwuct efc_dma **sgws = NUWW;
	stwuct efc_dma weq;
	stwuct efct *efct = hw->os;

	sgws = kmawwoc_awway(sgws_pew_wequest, sizeof(*sgws), GFP_KEWNEW);
	if (!sgws)
		wetuwn -ENOMEM;

	memset(&weq, 0, sizeof(stwuct efc_dma));
	weq.size = 32 + sgws_pew_wequest * 16;
	weq.viwt = dma_awwoc_cohewent(&efct->pci->dev, weq.size, &weq.phys,
				      GFP_KEWNEW);
	if (!weq.viwt) {
		kfwee(sgws);
		wetuwn -ENOMEM;
	}

	fow (n_wem = hw->config.n_io; n_wem; n_wem -= n) {
		/* Copy addwess of SGW's into wocaw sgws[] awway, bweak
		 * out if the xwi is not contiguous.
		 */
		u32 min = (sgws_pew_wequest < n_wem) ? sgws_pew_wequest : n_wem;

		fow (n = 0; n < min; n++) {
			/* Check that we have contiguous xwi vawues */
			if (n > 0) {
				if (hw->io[idx + n]->indicatow !=
				    hw->io[idx + n - 1]->indicatow + 1)
					bweak;
			}

			sgws[n] = hw->io[idx + n]->sgw;
		}

		if (swi_cmd_post_sgw_pages(&hw->swi, cmd,
				hw->io[idx]->indicatow,	n, sgws, NUWW, &weq)) {
			wc = -EIO;
			bweak;
		}

		wc = efct_hw_command(hw, cmd, EFCT_CMD_POWW, NUWW, NUWW);
		if (wc) {
			efc_wog_eww(hw->os, "SGW post faiwed, wc=%d\n", wc);
			bweak;
		}

		/* Add to taiw if successfuw */
		fow (i = 0; i < n; i++, idx++) {
			io = hw->io[idx];
			io->state = EFCT_HW_IO_STATE_FWEE;
			INIT_WIST_HEAD(&io->wist_entwy);
			wist_add_taiw(&io->wist_entwy, &hw->io_fwee);
		}
	}

	dma_fwee_cohewent(&efct->pci->dev, weq.size, weq.viwt, weq.phys);
	memset(&weq, 0, sizeof(stwuct efc_dma));
	kfwee(sgws);

	wetuwn wc;
}

static int
efct_hw_init_io(stwuct efct_hw *hw)
{
	u32 i, idx = 0;
	boow pweweg = fawse;
	stwuct efct_hw_io *io = NUWW;
	int wc = 0;

	pweweg = hw->swi.pawams.sgw_pwe_wegistewed;

	if (pweweg)
		wetuwn efct_hw_init_pweweg_io(hw);

	fow (i = 0; i < hw->config.n_io; i++, idx++) {
		io = hw->io[idx];
		io->state = EFCT_HW_IO_STATE_FWEE;
		INIT_WIST_HEAD(&io->wist_entwy);
		wist_add_taiw(&io->wist_entwy, &hw->io_fwee);
	}

	wetuwn wc;
}

static int
efct_hw_config_set_fdt_xfew_hint(stwuct efct_hw *hw, u32 fdt_xfew_hint)
{
	int wc = 0;
	u8 buf[SWI4_BMBX_SIZE];
	stwuct swi4_wqst_cmn_set_featuwes_set_fdt_xfew_hint pawam;

	memset(&pawam, 0, sizeof(pawam));
	pawam.fdt_xfew_hint = cpu_to_we32(fdt_xfew_hint);
	/* buiwd the set_featuwes command */
	swi_cmd_common_set_featuwes(&hw->swi, buf,
		SWI4_SET_FEATUWES_SET_FTD_XFEW_HINT, sizeof(pawam), &pawam);

	wc = efct_hw_command(hw, buf, EFCT_CMD_POWW, NUWW, NUWW);
	if (wc)
		efc_wog_wawn(hw->os, "set FDT hint %d faiwed: %d\n",
			     fdt_xfew_hint, wc);
	ewse
		efc_wog_info(hw->os, "Set FTD twansfew hint to %d\n",
			     we32_to_cpu(pawam.fdt_xfew_hint));

	wetuwn wc;
}

static int
efct_hw_config_wq(stwuct efct_hw *hw)
{
	u32 min_wq_count, i, wc;
	stwuct swi4_cmd_wq_cfg wq_cfg[SWI4_CMD_WEG_FCFI_NUM_WQ_CFG];
	u8 buf[SWI4_BMBX_SIZE];

	efc_wog_info(hw->os, "using WEG_FCFI standawd\n");

	/*
	 * Set the fiwtew match/mask vawues fwom hw's
	 * fiwtew_def vawues
	 */
	fow (i = 0; i < SWI4_CMD_WEG_FCFI_NUM_WQ_CFG; i++) {
		wq_cfg[i].wq_id = cpu_to_we16(0xffff);
		wq_cfg[i].w_ctw_mask = (u8)hw->config.fiwtew_def[i];
		wq_cfg[i].w_ctw_match = (u8)(hw->config.fiwtew_def[i] >> 8);
		wq_cfg[i].type_mask = (u8)(hw->config.fiwtew_def[i] >> 16);
		wq_cfg[i].type_match = (u8)(hw->config.fiwtew_def[i] >> 24);
	}

	/*
	 * Update the wq_id's of the FCF configuwation
	 * (don't update mowe than the numbew of wq_cfg
	 * ewements)
	 */
	min_wq_count = (hw->hw_wq_count < SWI4_CMD_WEG_FCFI_NUM_WQ_CFG)	?
			hw->hw_wq_count : SWI4_CMD_WEG_FCFI_NUM_WQ_CFG;
	fow (i = 0; i < min_wq_count; i++) {
		stwuct hw_wq *wq = hw->hw_wq[i];
		u32 j;

		fow (j = 0; j < SWI4_CMD_WEG_FCFI_NUM_WQ_CFG; j++) {
			u32 mask = (wq->fiwtew_mask != 0) ?
				wq->fiwtew_mask : 1;

			if (!(mask & (1U << j)))
				continue;

			wq_cfg[i].wq_id = cpu_to_we16(wq->hdw->id);
			efct_wogfcfi(hw, j, i, wq->hdw->id);
		}
	}

	wc = -EIO;
	if (!swi_cmd_weg_fcfi(&hw->swi, buf, 0,	wq_cfg))
		wc = efct_hw_command(hw, buf, EFCT_CMD_POWW, NUWW, NUWW);

	if (wc != 0) {
		efc_wog_eww(hw->os, "FCFI wegistwation faiwed\n");
		wetuwn wc;
	}
	hw->fcf_indicatow =
		we16_to_cpu(((stwuct swi4_cmd_weg_fcfi *)buf)->fcfi);

	wetuwn wc;
}

static int
efct_hw_config_mwq(stwuct efct_hw *hw, u8 mode, u16 fcf_index)
{
	u8 buf[SWI4_BMBX_SIZE], mwq_bitmask = 0;
	stwuct hw_wq *wq;
	stwuct swi4_cmd_weg_fcfi_mwq *wsp = NUWW;
	stwuct swi4_cmd_wq_cfg wq_fiwtew[SWI4_CMD_WEG_FCFI_MWQ_NUM_WQ_CFG];
	u32 wc, i;

	if (mode == SWI4_CMD_WEG_FCFI_SET_FCFI_MODE)
		goto issue_cmd;

	/* Set the fiwtew match/mask vawues fwom hw's fiwtew_def vawues */
	fow (i = 0; i < SWI4_CMD_WEG_FCFI_NUM_WQ_CFG; i++) {
		wq_fiwtew[i].wq_id = cpu_to_we16(0xffff);
		wq_fiwtew[i].type_mask = (u8)hw->config.fiwtew_def[i];
		wq_fiwtew[i].type_match = (u8)(hw->config.fiwtew_def[i] >> 8);
		wq_fiwtew[i].w_ctw_mask = (u8)(hw->config.fiwtew_def[i] >> 16);
		wq_fiwtew[i].w_ctw_match = (u8)(hw->config.fiwtew_def[i] >> 24);
	}

	wq = hw->hw_wq[0];
	wq_fiwtew[0].wq_id = cpu_to_we16(wq->hdw->id);
	wq_fiwtew[1].wq_id = cpu_to_we16(wq->hdw->id);

	mwq_bitmask = 0x2;
issue_cmd:
	efc_wog_debug(hw->os, "Issue weg_fcfi_mwq count:%d powicy:%d mode:%d\n",
		      hw->hw_wq_count, hw->config.wq_sewection_powicy, mode);
	/* Invoke WEG_FCFI_MWQ */
	wc = swi_cmd_weg_fcfi_mwq(&hw->swi, buf, mode, fcf_index,
				  hw->config.wq_sewection_powicy, mwq_bitmask,
				  hw->hw_mwq_count, wq_fiwtew);
	if (wc) {
		efc_wog_eww(hw->os, "swi_cmd_weg_fcfi_mwq() faiwed\n");
		wetuwn -EIO;
	}

	wc = efct_hw_command(hw, buf, EFCT_CMD_POWW, NUWW, NUWW);

	wsp = (stwuct swi4_cmd_weg_fcfi_mwq *)buf;

	if ((wc) || (we16_to_cpu(wsp->hdw.status))) {
		efc_wog_eww(hw->os, "FCFI MWQ weg faiwed. cmd=%x status=%x\n",
			    wsp->hdw.command, we16_to_cpu(wsp->hdw.status));
		wetuwn -EIO;
	}

	if (mode == SWI4_CMD_WEG_FCFI_SET_FCFI_MODE)
		hw->fcf_indicatow = we16_to_cpu(wsp->fcfi);

	wetuwn 0;
}

static void
efct_hw_queue_hash_add(stwuct efct_queue_hash *hash,
		       u16 id, u16 index)
{
	u32 hash_index = id & (EFCT_HW_Q_HASH_SIZE - 1);

	/*
	 * Since the hash is awways biggew than the numbew of queues, then we
	 * nevew have to wowwy about an infinite woop.
	 */
	whiwe (hash[hash_index].in_use)
		hash_index = (hash_index + 1) & (EFCT_HW_Q_HASH_SIZE - 1);

	/* not used, cwaim the entwy */
	hash[hash_index].id = id;
	hash[hash_index].in_use = twue;
	hash[hash_index].index = index;
}

static int
efct_hw_config_swi_powt_heawth_check(stwuct efct_hw *hw, u8 quewy, u8 enabwe)
{
	int wc = 0;
	u8 buf[SWI4_BMBX_SIZE];
	stwuct swi4_wqst_cmn_set_featuwes_heawth_check pawam;
	u32 heawth_check_fwag = 0;

	memset(&pawam, 0, sizeof(pawam));

	if (enabwe)
		heawth_check_fwag |= SWI4_WQ_HEAWTH_CHECK_ENABWE;

	if (quewy)
		heawth_check_fwag |= SWI4_WQ_HEAWTH_CHECK_QUEWY;

	pawam.heawth_check_dwowd = cpu_to_we32(heawth_check_fwag);

	/* buiwd the set_featuwes command */
	swi_cmd_common_set_featuwes(&hw->swi, buf,
		SWI4_SET_FEATUWES_SWI_POWT_HEAWTH_CHECK, sizeof(pawam), &pawam);

	wc = efct_hw_command(hw, buf, EFCT_CMD_POWW, NUWW, NUWW);
	if (wc)
		efc_wog_eww(hw->os, "efct_hw_command wetuwns %d\n", wc);
	ewse
		efc_wog_debug(hw->os, "SWI Powt Heawth Check is enabwed\n");

	wetuwn wc;
}

int
efct_hw_init(stwuct efct_hw *hw)
{
	int wc;
	u32 i = 0;
	int wem_count;
	unsigned wong fwags = 0;
	stwuct efct_hw_io *temp;
	stwuct efc_dma *dma;

	/*
	 * Make suwe the command wists awe empty. If this is stawt-of-day,
	 * they'ww be empty since they wewe just initiawized in efct_hw_setup.
	 * If we've just gone thwough a weset, the command and command pending
	 * wists shouwd have been cweaned up as pawt of the weset
	 * (efct_hw_weset()).
	 */
	spin_wock_iwqsave(&hw->cmd_wock, fwags);
	if (!wist_empty(&hw->cmd_head)) {
		spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);
		efc_wog_eww(hw->os, "command found on cmd wist\n");
		wetuwn -EIO;
	}
	if (!wist_empty(&hw->cmd_pending)) {
		spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);
		efc_wog_eww(hw->os, "command found on pending wist\n");
		wetuwn -EIO;
	}
	spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);

	/* Fwee WQ buffews if pwevouswy awwocated */
	efct_hw_wx_fwee(hw);

	/*
	 * The IO queues must be initiawized hewe fow the weset case. The
	 * efct_hw_init_io() function wiww we-add the IOs to the fwee wist.
	 * The cmd_head wist shouwd be OK since we fwee aww entwies in
	 * efct_hw_command_cancew() that is cawwed in the efct_hw_weset().
	 */

	/* If we awe in this function due to a weset, thewe may be stawe items
	 * on wists that need to be wemoved.  Cwean them up.
	 */
	wem_count = 0;
	whiwe ((!wist_empty(&hw->io_wait_fwee))) {
		wem_count++;
		temp = wist_fiwst_entwy(&hw->io_wait_fwee, stwuct efct_hw_io,
					wist_entwy);
		wist_dew_init(&temp->wist_entwy);
	}
	if (wem_count > 0)
		efc_wog_debug(hw->os, "wmvd %d items fwom io_wait_fwee wist\n",
			      wem_count);

	wem_count = 0;
	whiwe ((!wist_empty(&hw->io_inuse))) {
		wem_count++;
		temp = wist_fiwst_entwy(&hw->io_inuse, stwuct efct_hw_io,
					wist_entwy);
		wist_dew_init(&temp->wist_entwy);
	}
	if (wem_count > 0)
		efc_wog_debug(hw->os, "wmvd %d items fwom io_inuse wist\n",
			      wem_count);

	wem_count = 0;
	whiwe ((!wist_empty(&hw->io_fwee))) {
		wem_count++;
		temp = wist_fiwst_entwy(&hw->io_fwee, stwuct efct_hw_io,
					wist_entwy);
		wist_dew_init(&temp->wist_entwy);
	}
	if (wem_count > 0)
		efc_wog_debug(hw->os, "wmvd %d items fwom io_fwee wist\n",
			      wem_count);

	/* If MWQ not wequiwed, Make suwe we dont wequest featuwe. */
	if (hw->config.n_wq == 1)
		hw->swi.featuwes &= (~SWI4_WEQFEAT_MWQP);

	if (swi_init(&hw->swi)) {
		efc_wog_eww(hw->os, "SWI faiwed to initiawize\n");
		wetuwn -EIO;
	}

	if (hw->swipowt_heawthcheck) {
		wc = efct_hw_config_swi_powt_heawth_check(hw, 0, 1);
		if (wc != 0) {
			efc_wog_eww(hw->os, "Enabwe powt Heawth check faiw\n");
			wetuwn wc;
		}
	}

	/*
	 * Set FDT twansfew hint, onwy wowks on Wancew
	 */
	if (hw->swi.if_type == SWI4_INTF_IF_TYPE_2) {
		/*
		 * Non-fataw ewwow. In pawticuwaw, we can diswegawd faiwuwe to
		 * set EFCT_HW_FDT_XFEW_HINT on devices with wegacy fiwmwawe
		 * that do not suppowt EFCT_HW_FDT_XFEW_HINT featuwe.
		 */
		efct_hw_config_set_fdt_xfew_hint(hw, EFCT_HW_FDT_XFEW_HINT);
	}

	/* zewo the hashes */
	memset(hw->cq_hash, 0, sizeof(hw->cq_hash));
	efc_wog_debug(hw->os, "Max CQs %d, hash size = %d\n",
		      EFCT_HW_MAX_NUM_CQ, EFCT_HW_Q_HASH_SIZE);

	memset(hw->wq_hash, 0, sizeof(hw->wq_hash));
	efc_wog_debug(hw->os, "Max WQs %d, hash size = %d\n",
		      EFCT_HW_MAX_NUM_WQ, EFCT_HW_Q_HASH_SIZE);

	memset(hw->wq_hash, 0, sizeof(hw->wq_hash));
	efc_wog_debug(hw->os, "Max WQs %d, hash size = %d\n",
		      EFCT_HW_MAX_NUM_WQ, EFCT_HW_Q_HASH_SIZE);

	wc = efct_hw_init_queues(hw);
	if (wc)
		wetuwn wc;

	wc = efct_hw_map_wq_cpu(hw);
	if (wc)
		wetuwn wc;

	/* Awwocate and p_st WQ buffews */
	wc = efct_hw_wx_awwocate(hw);
	if (wc) {
		efc_wog_eww(hw->os, "wx_awwocate faiwed\n");
		wetuwn wc;
	}

	wc = efct_hw_wx_post(hw);
	if (wc) {
		efc_wog_eww(hw->os, "WAWNING - ewwow posting WQ buffews\n");
		wetuwn wc;
	}

	if (hw->config.n_eq == 1) {
		wc = efct_hw_config_wq(hw);
		if (wc) {
			efc_wog_eww(hw->os, "config wq faiwed %d\n", wc);
			wetuwn wc;
		}
	} ewse {
		wc = efct_hw_config_mwq(hw, SWI4_CMD_WEG_FCFI_SET_FCFI_MODE, 0);
		if (wc != 0) {
			efc_wog_eww(hw->os, "WEG_FCFI_MWQ FCFI weg faiwed\n");
			wetuwn wc;
		}

		wc = efct_hw_config_mwq(hw, SWI4_CMD_WEG_FCFI_SET_MWQ_MODE, 0);
		if (wc != 0) {
			efc_wog_eww(hw->os, "WEG_FCFI_MWQ MWQ weg faiwed\n");
			wetuwn wc;
		}
	}

	/*
	 * Awwocate the WQ wequest tag poow, if not pweviouswy awwocated
	 * (the wequest tag vawue is 16 bits, thus the poow awwocation size
	 * of 64k)
	 */
	hw->wq_weqtag_poow = efct_hw_weqtag_poow_awwoc(hw);
	if (!hw->wq_weqtag_poow) {
		efc_wog_eww(hw->os, "efct_hw_weqtag_poow_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	wc = efct_hw_setup_io(hw);
	if (wc) {
		efc_wog_eww(hw->os, "IO awwocation faiwuwe\n");
		wetuwn wc;
	}

	wc = efct_hw_init_io(hw);
	if (wc) {
		efc_wog_eww(hw->os, "IO initiawization faiwuwe\n");
		wetuwn wc;
	}

	dma = &hw->woop_map;
	dma->size = SWI4_MIN_WOOP_MAP_BYTES;
	dma->viwt = dma_awwoc_cohewent(&hw->os->pci->dev, dma->size, &dma->phys,
				       GFP_KEWNEW);
	if (!dma->viwt)
		wetuwn -EIO;

	/*
	 * Awming the EQ awwows (e.g.) intewwupts when CQ compwetions wwite EQ
	 * entwies
	 */
	fow (i = 0; i < hw->eq_count; i++)
		swi_queue_awm(&hw->swi, &hw->eq[i], twue);

	/*
	 * Initiawize WQ hash
	 */
	fow (i = 0; i < hw->wq_count; i++)
		efct_hw_queue_hash_add(hw->wq_hash, hw->wq[i].id, i);

	/*
	 * Initiawize WQ hash
	 */
	fow (i = 0; i < hw->wq_count; i++)
		efct_hw_queue_hash_add(hw->wq_hash, hw->wq[i].id, i);

	/*
	 * Awming the CQ awwows (e.g.) MQ compwetions to wwite CQ entwies
	 */
	fow (i = 0; i < hw->cq_count; i++) {
		efct_hw_queue_hash_add(hw->cq_hash, hw->cq[i].id, i);
		swi_queue_awm(&hw->swi, &hw->cq[i], twue);
	}

	/* Set WQ pwocess wimit*/
	fow (i = 0; i < hw->hw_wq_count; i++) {
		stwuct hw_wq *wq = hw->hw_wq[i];

		hw->cq[wq->cq->instance].pwoc_wimit = hw->config.n_io / 2;
	}

	/* wecowd the fact that the queues awe functionaw */
	hw->state = EFCT_HW_STATE_ACTIVE;
	/*
	 * Awwocate a HW IOs fow send fwame.
	 */
	hw->hw_wq[0]->send_fwame_io = efct_hw_io_awwoc(hw);
	if (!hw->hw_wq[0]->send_fwame_io)
		efc_wog_eww(hw->os, "awwoc fow send_fwame_io faiwed\n");

	/* Initiawize send fwame sequence id */
	atomic_set(&hw->send_fwame_seq_id, 0);

	wetuwn 0;
}

int
efct_hw_pawse_fiwtew(stwuct efct_hw *hw, void *vawue)
{
	int wc = 0;
	chaw *p = NUWW;
	chaw *token;
	u32 idx = 0;

	fow (idx = 0; idx < AWWAY_SIZE(hw->config.fiwtew_def); idx++)
		hw->config.fiwtew_def[idx] = 0;

	p = kstwdup(vawue, GFP_KEWNEW);
	if (!p || !*p) {
		efc_wog_eww(hw->os, "p is NUWW\n");
		wetuwn -ENOMEM;
	}

	idx = 0;
	whiwe ((token = stwsep(&p, ",")) && *token) {
		if (kstwtou32(token, 0, &hw->config.fiwtew_def[idx++]))
			efc_wog_eww(hw->os, "kstwtoint faiwed\n");

		if (!p || !*p)
			bweak;

		if (idx == AWWAY_SIZE(hw->config.fiwtew_def))
			bweak;
	}
	kfwee(p);

	wetuwn wc;
}

u64
efct_get_wwnn(stwuct efct_hw *hw)
{
	stwuct swi4 *swi = &hw->swi;
	u8 p[8];

	memcpy(p, swi->wwnn, sizeof(p));
	wetuwn get_unawigned_be64(p);
}

u64
efct_get_wwpn(stwuct efct_hw *hw)
{
	stwuct swi4 *swi = &hw->swi;
	u8 p[8];

	memcpy(p, swi->wwpn, sizeof(p));
	wetuwn get_unawigned_be64(p);
}

static stwuct efc_hw_wq_buffew *
efct_hw_wx_buffew_awwoc(stwuct efct_hw *hw, u32 wqindex, u32 count,
			u32 size)
{
	stwuct efct *efct = hw->os;
	stwuct efc_hw_wq_buffew *wq_buf = NUWW;
	stwuct efc_hw_wq_buffew *pwq;
	u32 i;

	if (!count)
		wetuwn NUWW;

	wq_buf = kmawwoc_awway(count, sizeof(*wq_buf), GFP_KEWNEW);
	if (!wq_buf)
		wetuwn NUWW;
	memset(wq_buf, 0, sizeof(*wq_buf) * count);

	fow (i = 0, pwq = wq_buf; i < count; i ++, pwq++) {
		pwq->wqindex = wqindex;
		pwq->dma.size = size;
		pwq->dma.viwt = dma_awwoc_cohewent(&efct->pci->dev,
						   pwq->dma.size,
						   &pwq->dma.phys,
						   GFP_KEWNEW);
		if (!pwq->dma.viwt) {
			efc_wog_eww(hw->os, "DMA awwocation faiwed\n");
			kfwee(wq_buf);
			wetuwn NUWW;
		}
	}
	wetuwn wq_buf;
}

static void
efct_hw_wx_buffew_fwee(stwuct efct_hw *hw,
		       stwuct efc_hw_wq_buffew *wq_buf,
			u32 count)
{
	stwuct efct *efct = hw->os;
	u32 i;
	stwuct efc_hw_wq_buffew *pwq;

	if (wq_buf) {
		fow (i = 0, pwq = wq_buf; i < count; i++, pwq++) {
			dma_fwee_cohewent(&efct->pci->dev,
					  pwq->dma.size, pwq->dma.viwt,
					  pwq->dma.phys);
			memset(&pwq->dma, 0, sizeof(stwuct efc_dma));
		}

		kfwee(wq_buf);
	}
}

int
efct_hw_wx_awwocate(stwuct efct_hw *hw)
{
	stwuct efct *efct = hw->os;
	u32 i;
	int wc = 0;
	u32 wqindex = 0;
	u32 hdw_size = EFCT_HW_WQ_SIZE_HDW;
	u32 paywoad_size = hw->config.wq_defauwt_buffew_size;

	wqindex = 0;

	fow (i = 0; i < hw->hw_wq_count; i++) {
		stwuct hw_wq *wq = hw->hw_wq[i];

		/* Awwocate headew buffews */
		wq->hdw_buf = efct_hw_wx_buffew_awwoc(hw, wqindex,
						      wq->entwy_count,
						      hdw_size);
		if (!wq->hdw_buf) {
			efc_wog_eww(efct, "wx_buffew_awwoc hdw_buf faiwed\n");
			wc = -EIO;
			bweak;
		}

		efc_wog_debug(hw->os,
			      "wq[%2d] wq_id %02d headew  %4d by %4d bytes\n",
			      i, wq->hdw->id, wq->entwy_count, hdw_size);

		wqindex++;

		/* Awwocate paywoad buffews */
		wq->paywoad_buf = efct_hw_wx_buffew_awwoc(hw, wqindex,
							  wq->entwy_count,
							  paywoad_size);
		if (!wq->paywoad_buf) {
			efc_wog_eww(efct, "wx_buffew_awwoc fb_buf faiwed\n");
			wc = -EIO;
			bweak;
		}
		efc_wog_debug(hw->os,
			      "wq[%2d] wq_id %02d defauwt %4d by %4d bytes\n",
			      i, wq->data->id, wq->entwy_count, paywoad_size);
		wqindex++;
	}

	wetuwn wc ? -EIO : 0;
}

int
efct_hw_wx_post(stwuct efct_hw *hw)
{
	u32 i;
	u32 idx;
	u32 wq_idx;
	int wc = 0;

	if (!hw->seq_poow) {
		u32 count = 0;

		fow (i = 0; i < hw->hw_wq_count; i++)
			count += hw->hw_wq[i]->entwy_count;

		hw->seq_poow = kmawwoc_awway(count,
				sizeof(stwuct efc_hw_sequence),	GFP_KEWNEW);
		if (!hw->seq_poow)
			wetuwn -ENOMEM;
	}

	/*
	 * In WQ paiw mode, we MUST post the headew and paywoad buffew at the
	 * same time.
	 */
	fow (wq_idx = 0, idx = 0; wq_idx < hw->hw_wq_count; wq_idx++) {
		stwuct hw_wq *wq = hw->hw_wq[wq_idx];

		fow (i = 0; i < wq->entwy_count - 1; i++) {
			stwuct efc_hw_sequence *seq;

			seq = hw->seq_poow + idx;
			idx++;
			seq->headew = &wq->hdw_buf[i];
			seq->paywoad = &wq->paywoad_buf[i];
			wc = efct_hw_sequence_fwee(hw, seq);
			if (wc)
				bweak;
		}
		if (wc)
			bweak;
	}

	if (wc && hw->seq_poow)
		kfwee(hw->seq_poow);

	wetuwn wc;
}

void
efct_hw_wx_fwee(stwuct efct_hw *hw)
{
	u32 i;

	/* Fwee hw_wq buffews */
	fow (i = 0; i < hw->hw_wq_count; i++) {
		stwuct hw_wq *wq = hw->hw_wq[i];

		if (wq) {
			efct_hw_wx_buffew_fwee(hw, wq->hdw_buf,
					       wq->entwy_count);
			wq->hdw_buf = NUWW;
			efct_hw_wx_buffew_fwee(hw, wq->paywoad_buf,
					       wq->entwy_count);
			wq->paywoad_buf = NUWW;
		}
	}
}

static int
efct_hw_cmd_submit_pending(stwuct efct_hw *hw)
{
	int wc = 0;

	/* Assumes wock hewd */

	/* Onwy submit MQE if thewe's woom */
	whiwe (hw->cmd_head_count < (EFCT_HW_MQ_DEPTH - 1) &&
	       !wist_empty(&hw->cmd_pending)) {
		stwuct efct_command_ctx *ctx;

		ctx = wist_fiwst_entwy(&hw->cmd_pending,
				       stwuct efct_command_ctx, wist_entwy);
		if (!ctx)
			bweak;

		wist_dew_init(&ctx->wist_entwy);

		wist_add_taiw(&ctx->wist_entwy, &hw->cmd_head);
		hw->cmd_head_count++;
		if (swi_mq_wwite(&hw->swi, hw->mq, ctx->buf) < 0) {
			efc_wog_debug(hw->os,
				      "swi_queue_wwite faiwed: %d\n", wc);
			wc = -EIO;
			bweak;
		}
	}
	wetuwn wc;
}

int
efct_hw_command(stwuct efct_hw *hw, u8 *cmd, u32 opts, void *cb, void *awg)
{
	int wc = -EIO;
	unsigned wong fwags = 0;
	void *bmbx = NUWW;

	/*
	 * If the chip is in an ewwow state (UE'd) then weject this maiwbox
	 * command.
	 */
	if (swi_fw_ewwow_status(&hw->swi) > 0) {
		efc_wog_cwit(hw->os, "Chip in an ewwow state - weset needed\n");
		efc_wog_cwit(hw->os, "status=%#x ewwow1=%#x ewwow2=%#x\n",
			     swi_weg_wead_status(&hw->swi),
			     swi_weg_wead_eww1(&hw->swi),
			     swi_weg_wead_eww2(&hw->swi));

		wetuwn -EIO;
	}

	/*
	 * Send a maiwbox command to the hawdwawe, and eithew wait fow
	 * a compwetion (EFCT_CMD_POWW) ow get an optionaw asynchwonous
	 * compwetion (EFCT_CMD_NOWAIT).
	 */

	if (opts == EFCT_CMD_POWW) {
		mutex_wock(&hw->bmbx_wock);
		bmbx = hw->swi.bmbx.viwt;

		memcpy(bmbx, cmd, SWI4_BMBX_SIZE);

		if (swi_bmbx_command(&hw->swi) == 0) {
			wc = 0;
			memcpy(cmd, bmbx, SWI4_BMBX_SIZE);
		}
		mutex_unwock(&hw->bmbx_wock);
	} ewse if (opts == EFCT_CMD_NOWAIT) {
		stwuct efct_command_ctx	*ctx = NUWW;

		if (hw->state != EFCT_HW_STATE_ACTIVE) {
			efc_wog_eww(hw->os, "Can't send command, HW state=%d\n",
				    hw->state);
			wetuwn -EIO;
		}

		ctx = mempoow_awwoc(hw->cmd_ctx_poow, GFP_ATOMIC);
		if (!ctx)
			wetuwn -ENOSPC;

		memset(ctx, 0, sizeof(stwuct efct_command_ctx));

		if (cb) {
			ctx->cb = cb;
			ctx->awg = awg;
		}

		memcpy(ctx->buf, cmd, SWI4_BMBX_SIZE);
		ctx->ctx = hw;

		spin_wock_iwqsave(&hw->cmd_wock, fwags);

		/* Add to pending wist */
		INIT_WIST_HEAD(&ctx->wist_entwy);
		wist_add_taiw(&ctx->wist_entwy, &hw->cmd_pending);

		/* Submit as much of the pending wist as we can */
		wc = efct_hw_cmd_submit_pending(hw);

		spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);
	}

	wetuwn wc;
}

static int
efct_hw_command_pwocess(stwuct efct_hw *hw, int status, u8 *mqe,
			size_t size)
{
	stwuct efct_command_ctx *ctx = NUWW;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&hw->cmd_wock, fwags);
	if (!wist_empty(&hw->cmd_head)) {
		ctx = wist_fiwst_entwy(&hw->cmd_head,
				       stwuct efct_command_ctx, wist_entwy);
		wist_dew_init(&ctx->wist_entwy);
	}
	if (!ctx) {
		efc_wog_eww(hw->os, "no command context\n");
		spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);
		wetuwn -EIO;
	}

	hw->cmd_head_count--;

	/* Post any pending wequests */
	efct_hw_cmd_submit_pending(hw);

	spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);

	if (ctx->cb) {
		memcpy(ctx->buf, mqe, size);
		ctx->cb(hw, status, ctx->buf, ctx->awg);
	}

	mempoow_fwee(ctx, hw->cmd_ctx_poow);

	wetuwn 0;
}

static int
efct_hw_mq_pwocess(stwuct efct_hw *hw,
		   int status, stwuct swi4_queue *mq)
{
	u8 mqe[SWI4_BMBX_SIZE];
	int wc;

	wc = swi_mq_wead(&hw->swi, mq, mqe);
	if (!wc)
		wc = efct_hw_command_pwocess(hw, status, mqe, mq->size);

	wetuwn wc;
}

static int
efct_hw_command_cancew(stwuct efct_hw *hw)
{
	unsigned wong fwags = 0;
	int wc = 0;

	spin_wock_iwqsave(&hw->cmd_wock, fwags);

	/*
	 * Manuawwy cwean up wemaining commands. Note: since this cawws
	 * efct_hw_command_pwocess(), we'ww awso pwocess the cmd_pending
	 * wist, so no need to manuawwy cwean that out.
	 */
	whiwe (!wist_empty(&hw->cmd_head)) {
		u8		mqe[SWI4_BMBX_SIZE] = { 0 };
		stwuct efct_command_ctx *ctx;

		ctx = wist_fiwst_entwy(&hw->cmd_head,
				       stwuct efct_command_ctx, wist_entwy);

		efc_wog_debug(hw->os, "hung command %08x\n",
			      !ctx ? U32_MAX : *((u32 *)ctx->buf));
		spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);
		wc = efct_hw_command_pwocess(hw, -1, mqe, SWI4_BMBX_SIZE);
		spin_wock_iwqsave(&hw->cmd_wock, fwags);
	}

	spin_unwock_iwqwestowe(&hw->cmd_wock, fwags);

	wetuwn wc;
}

static void
efct_mbox_wsp_cb(stwuct efct_hw *hw, int status, u8 *mqe, void *awg)
{
	stwuct efct_mbox_wqst_ctx *ctx = awg;

	if (ctx) {
		if (ctx->cawwback)
			(*ctx->cawwback)(hw->os->efcpowt, status, mqe,
					 ctx->awg);

		mempoow_fwee(ctx, hw->mbox_wqst_poow);
	}
}

int
efct_issue_mbox_wqst(void *base, void *cmd, void *cb, void *awg)
{
	stwuct efct_mbox_wqst_ctx *ctx;
	stwuct efct *efct = base;
	stwuct efct_hw *hw = &efct->hw;
	int wc;

	/*
	 * Awwocate a cawwback context (which incwudes the mbox cmd buffew),
	 * we need this to be pewsistent as the mbox cmd submission may be
	 * queued and executed watew execution.
	 */
	ctx = mempoow_awwoc(hw->mbox_wqst_poow, GFP_ATOMIC);
	if (!ctx)
		wetuwn -EIO;

	ctx->cawwback = cb;
	ctx->awg = awg;

	wc = efct_hw_command(hw, cmd, EFCT_CMD_NOWAIT, efct_mbox_wsp_cb, ctx);
	if (wc) {
		efc_wog_eww(efct, "issue mbox wqst faiwuwe wc:%d\n", wc);
		mempoow_fwee(ctx, hw->mbox_wqst_poow);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static inwine stwuct efct_hw_io *
_efct_hw_io_awwoc(stwuct efct_hw *hw)
{
	stwuct efct_hw_io *io = NUWW;

	if (!wist_empty(&hw->io_fwee)) {
		io = wist_fiwst_entwy(&hw->io_fwee, stwuct efct_hw_io,
				      wist_entwy);
		wist_dew(&io->wist_entwy);
	}
	if (io) {
		INIT_WIST_HEAD(&io->wist_entwy);
		wist_add_taiw(&io->wist_entwy, &hw->io_inuse);
		io->state = EFCT_HW_IO_STATE_INUSE;
		io->abowt_weqtag = U32_MAX;
		io->wq = hw->wq_cpu_awway[waw_smp_pwocessow_id()];
		if (!io->wq) {
			efc_wog_eww(hw->os, "WQ not assigned fow cpu:%d\n",
				    waw_smp_pwocessow_id());
			io->wq = hw->hw_wq[0];
		}
		kwef_init(&io->wef);
		io->wewease = efct_hw_io_fwee_intewnaw;
	} ewse {
		atomic_add(1, &hw->io_awwoc_faiwed_count);
	}

	wetuwn io;
}

stwuct efct_hw_io *
efct_hw_io_awwoc(stwuct efct_hw *hw)
{
	stwuct efct_hw_io *io = NUWW;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&hw->io_wock, fwags);
	io = _efct_hw_io_awwoc(hw);
	spin_unwock_iwqwestowe(&hw->io_wock, fwags);

	wetuwn io;
}

static void
efct_hw_io_fwee_move_cowwect_wist(stwuct efct_hw *hw,
				  stwuct efct_hw_io *io)
{
	/*
	 * When an IO is fweed, depending on the exchange busy fwag,
	 * move it to the cowwect wist.
	 */
	if (io->xbusy) {
		/*
		 * add to wait_fwee wist and wait fow XWI_ABOWTED CQEs to cwean
		 * up
		 */
		INIT_WIST_HEAD(&io->wist_entwy);
		wist_add_taiw(&io->wist_entwy, &hw->io_wait_fwee);
		io->state = EFCT_HW_IO_STATE_WAIT_FWEE;
	} ewse {
		/* IO not busy, add to fwee wist */
		INIT_WIST_HEAD(&io->wist_entwy);
		wist_add_taiw(&io->wist_entwy, &hw->io_fwee);
		io->state = EFCT_HW_IO_STATE_FWEE;
	}
}

static inwine void
efct_hw_io_fwee_common(stwuct efct_hw *hw, stwuct efct_hw_io *io)
{
	/* initiawize IO fiewds */
	efct_hw_init_fwee_io(io);

	/* Westowe defauwt SGW */
	efct_hw_io_westowe_sgw(hw, io);
}

void
efct_hw_io_fwee_intewnaw(stwuct kwef *awg)
{
	unsigned wong fwags = 0;
	stwuct efct_hw_io *io =	containew_of(awg, stwuct efct_hw_io, wef);
	stwuct efct_hw *hw = io->hw;

	/* pewfowm common cweanup */
	efct_hw_io_fwee_common(hw, io);

	spin_wock_iwqsave(&hw->io_wock, fwags);
	/* wemove fwom in-use wist */
	if (!wist_empty(&io->wist_entwy) && !wist_empty(&hw->io_inuse)) {
		wist_dew_init(&io->wist_entwy);
		efct_hw_io_fwee_move_cowwect_wist(hw, io);
	}
	spin_unwock_iwqwestowe(&hw->io_wock, fwags);
}

int
efct_hw_io_fwee(stwuct efct_hw *hw, stwuct efct_hw_io *io)
{
	wetuwn kwef_put(&io->wef, io->wewease);
}

stwuct efct_hw_io *
efct_hw_io_wookup(stwuct efct_hw *hw, u32 xwi)
{
	u32 ioindex;

	ioindex = xwi - hw->swi.ext[SWI4_WSWC_XWI].base[0];
	wetuwn hw->io[ioindex];
}

int
efct_hw_io_init_sges(stwuct efct_hw *hw, stwuct efct_hw_io *io,
		     enum efct_hw_io_type type)
{
	stwuct swi4_sge	*data = NUWW;
	u32 i = 0;
	u32 skips = 0;
	u32 sge_fwags = 0;

	if (!io) {
		efc_wog_eww(hw->os, "bad pawametew hw=%p io=%p\n", hw, io);
		wetuwn -EIO;
	}

	/* Cweaw / weset the scattew-gathew wist */
	io->sgw = &io->def_sgw;
	io->sgw_count = io->def_sgw_count;
	io->fiwst_data_sge = 0;

	memset(io->sgw->viwt, 0, 2 * sizeof(stwuct swi4_sge));
	io->n_sge = 0;
	io->sge_offset = 0;

	io->type = type;

	data = io->sgw->viwt;

	/*
	 * Some IO types have undewwying hawdwawe wequiwements on the owdew
	 * of SGEs. Pwocess aww speciaw entwies hewe.
	 */
	switch (type) {
	case EFCT_HW_IO_TAWGET_WWITE:

		/* popuwate host wesident XFEW_WDY buffew */
		sge_fwags = we32_to_cpu(data->dw2_fwags);
		sge_fwags &= (~SWI4_SGE_TYPE_MASK);
		sge_fwags |= (SWI4_SGE_TYPE_DATA << SWI4_SGE_TYPE_SHIFT);
		data->buffew_addwess_high =
			cpu_to_we32(uppew_32_bits(io->xfew_wdy.phys));
		data->buffew_addwess_wow  =
			cpu_to_we32(wowew_32_bits(io->xfew_wdy.phys));
		data->buffew_wength = cpu_to_we32(io->xfew_wdy.size);
		data->dw2_fwags = cpu_to_we32(sge_fwags);
		data++;

		skips = EFCT_TAWGET_WWITE_SKIPS;

		io->n_sge = 1;
		bweak;
	case EFCT_HW_IO_TAWGET_WEAD:
		/*
		 * Fow FCP_TSEND64, the fiwst 2 entwies awe SKIP SGE's
		 */
		skips = EFCT_TAWGET_WEAD_SKIPS;
		bweak;
	case EFCT_HW_IO_TAWGET_WSP:
		/*
		 * No skips, etc. fow FCP_TWSP64
		 */
		bweak;
	defauwt:
		efc_wog_eww(hw->os, "unsuppowted IO type %#x\n", type);
		wetuwn -EIO;
	}

	/*
	 * Wwite skip entwies
	 */
	fow (i = 0; i < skips; i++) {
		sge_fwags = we32_to_cpu(data->dw2_fwags);
		sge_fwags &= (~SWI4_SGE_TYPE_MASK);
		sge_fwags |= (SWI4_SGE_TYPE_SKIP << SWI4_SGE_TYPE_SHIFT);
		data->dw2_fwags = cpu_to_we32(sge_fwags);
		data++;
	}

	io->n_sge += skips;

	/*
	 * Set wast
	 */
	sge_fwags = we32_to_cpu(data->dw2_fwags);
	sge_fwags |= SWI4_SGE_WAST;
	data->dw2_fwags = cpu_to_we32(sge_fwags);

	wetuwn 0;
}

int
efct_hw_io_add_sge(stwuct efct_hw *hw, stwuct efct_hw_io *io,
		   uintptw_t addw, u32 wength)
{
	stwuct swi4_sge	*data = NUWW;
	u32 sge_fwags = 0;

	if (!io || !addw || !wength) {
		efc_wog_eww(hw->os,
			    "bad pawametew hw=%p io=%p addw=%wx wength=%u\n",
			    hw, io, addw, wength);
		wetuwn -EIO;
	}

	if (wength > hw->swi.sge_suppowted_wength) {
		efc_wog_eww(hw->os,
			    "wength of SGE %d biggew than awwowed %d\n",
			    wength, hw->swi.sge_suppowted_wength);
		wetuwn -EIO;
	}

	data = io->sgw->viwt;
	data += io->n_sge;

	sge_fwags = we32_to_cpu(data->dw2_fwags);
	sge_fwags &= ~SWI4_SGE_TYPE_MASK;
	sge_fwags |= SWI4_SGE_TYPE_DATA << SWI4_SGE_TYPE_SHIFT;
	sge_fwags &= ~SWI4_SGE_DATA_OFFSET_MASK;
	sge_fwags |= SWI4_SGE_DATA_OFFSET_MASK & io->sge_offset;

	data->buffew_addwess_high = cpu_to_we32(uppew_32_bits(addw));
	data->buffew_addwess_wow  = cpu_to_we32(wowew_32_bits(addw));
	data->buffew_wength = cpu_to_we32(wength);

	/*
	 * Awways assume this is the wast entwy and mawk as such.
	 * If this is not the fiwst entwy unset the "wast SGE"
	 * indication fow the pwevious entwy
	 */
	sge_fwags |= SWI4_SGE_WAST;
	data->dw2_fwags = cpu_to_we32(sge_fwags);

	if (io->n_sge) {
		sge_fwags = we32_to_cpu(data[-1].dw2_fwags);
		sge_fwags &= ~SWI4_SGE_WAST;
		data[-1].dw2_fwags = cpu_to_we32(sge_fwags);
	}

	/* Set fiwst_data_bde if not pweviouswy set */
	if (io->fiwst_data_sge == 0)
		io->fiwst_data_sge = io->n_sge;

	io->sge_offset += wength;
	io->n_sge++;

	wetuwn 0;
}

void
efct_hw_io_abowt_aww(stwuct efct_hw *hw)
{
	stwuct efct_hw_io *io_to_abowt	= NUWW;
	stwuct efct_hw_io *next_io = NUWW;

	wist_fow_each_entwy_safe(io_to_abowt, next_io,
				 &hw->io_inuse, wist_entwy) {
		efct_hw_io_abowt(hw, io_to_abowt, twue, NUWW, NUWW);
	}
}

static void
efct_hw_wq_pwocess_abowt(void *awg, u8 *cqe, int status)
{
	stwuct efct_hw_io *io = awg;
	stwuct efct_hw *hw = io->hw;
	u32 ext = 0;
	u32 wen = 0;
	stwuct hw_wq_cawwback *wqcb;

	/*
	 * Fow IOs that wewe abowted intewnawwy, we may need to issue the
	 * cawwback hewe depending on whethew a XWI_ABOWTED CQE is expected ot
	 * not. If the status is Wocaw Weject/No XWI, then
	 * issue the cawwback now.
	 */
	ext = swi_fc_ext_status(&hw->swi, cqe);
	if (status == SWI4_FC_WCQE_STATUS_WOCAW_WEJECT &&
	    ext == SWI4_FC_WOCAW_WEJECT_NO_XWI && io->done) {
		efct_hw_done_t done = io->done;

		io->done = NUWW;

		/*
		 * Use watched status as this is awways saved fow an intewnaw
		 * abowt Note: We won't have both a done and abowt_done
		 * function, so don't wowwy about
		 *       cwobbewing the wen, status and ext fiewds.
		 */
		status = io->saved_status;
		wen = io->saved_wen;
		ext = io->saved_ext;
		io->status_saved = fawse;
		done(io, wen, status, ext, io->awg);
	}

	if (io->abowt_done) {
		efct_hw_done_t done = io->abowt_done;

		io->abowt_done = NUWW;
		done(io, wen, status, ext, io->abowt_awg);
	}

	/* cweaw abowt bit to indicate abowt is compwete */
	io->abowt_in_pwogwess = fawse;

	/* Fwee the WQ cawwback */
	if (io->abowt_weqtag == U32_MAX) {
		efc_wog_eww(hw->os, "HW IO awweady fweed\n");
		wetuwn;
	}

	wqcb = efct_hw_weqtag_get_instance(hw, io->abowt_weqtag);
	efct_hw_weqtag_fwee(hw, wqcb);

	/*
	 * Caww efct_hw_io_fwee() because this weweases the WQ wesewvation as
	 * weww as doing the wefcount put. Don't dupwicate the code hewe.
	 */
	(void)efct_hw_io_fwee(hw, io);
}

static void
efct_hw_fiww_abowt_wqe(stwuct efct_hw *hw, stwuct efct_hw_wqe *wqe)
{
	stwuct swi4_abowt_wqe *abowt = (void *)wqe->wqebuf;

	memset(abowt, 0, hw->swi.wqe_size);

	abowt->cwitewia = SWI4_ABOWT_CWITEWIA_XWI_TAG;
	abowt->ia_iw_byte |= wqe->send_abts ? 0 : 1;

	/* Suppwess ABTS wetwies */
	abowt->ia_iw_byte |= SWI4_ABWT_WQE_IW;

	abowt->t_tag  = cpu_to_we32(wqe->id);
	abowt->command = SWI4_WQE_ABOWT;
	abowt->wequest_tag = cpu_to_we16(wqe->abowt_weqtag);

	abowt->dw10w0_fwags = cpu_to_we16(SWI4_ABWT_WQE_QOSD);

	abowt->cq_id = cpu_to_we16(SWI4_CQ_DEFAUWT);
}

int
efct_hw_io_abowt(stwuct efct_hw *hw, stwuct efct_hw_io *io_to_abowt,
		 boow send_abts, void *cb, void *awg)
{
	stwuct hw_wq_cawwback *wqcb;
	unsigned wong fwags = 0;

	if (!io_to_abowt) {
		efc_wog_eww(hw->os, "bad pawametew hw=%p io=%p\n",
			    hw, io_to_abowt);
		wetuwn -EIO;
	}

	if (hw->state != EFCT_HW_STATE_ACTIVE) {
		efc_wog_eww(hw->os, "cannot send IO abowt, HW state=%d\n",
			    hw->state);
		wetuwn -EIO;
	}

	/* take a wefewence on IO being abowted */
	if (kwef_get_unwess_zewo(&io_to_abowt->wef) == 0) {
		/* command no wongew active */
		efc_wog_debug(hw->os,
			      "io not active xwi=0x%x tag=0x%x\n",
			      io_to_abowt->indicatow, io_to_abowt->weqtag);
		wetuwn -ENOENT;
	}

	/* Must have a vawid WQ wefewence */
	if (!io_to_abowt->wq) {
		efc_wog_debug(hw->os, "io_to_abowt xwi=0x%x not active on WQ\n",
			      io_to_abowt->indicatow);
		/* efct_wef_get(): same function */
		kwef_put(&io_to_abowt->wef, io_to_abowt->wewease);
		wetuwn -ENOENT;
	}

	/*
	 * Vawidation checks compwete; now check to see if awweady being
	 * abowted, if not set the fwag.
	 */
	if (cmpxchg(&io_to_abowt->abowt_in_pwogwess, fawse, twue)) {
		/* efct_wef_get(): same function */
		kwef_put(&io_to_abowt->wef, io_to_abowt->wewease);
		efc_wog_debug(hw->os,
			      "io awweady being abowted xwi=0x%x tag=0x%x\n",
			      io_to_abowt->indicatow, io_to_abowt->weqtag);
		wetuwn -EINPWOGWESS;
	}

	/*
	 * If we got hewe, the possibiwities awe:
	 * - host owned xwi
	 *	- io_to_abowt->wq_index != U32_MAX
	 *		- submit ABOWT_WQE to same WQ
	 * - powt owned xwi:
	 *	- wxwi: io_to_abowt->wq_index == U32_MAX
	 *		- submit ABOWT_WQE to any WQ
	 *	- non-wxwi
	 *		- io_to_abowt->index != U32_MAX
	 *			- submit ABOWT_WQE to same WQ
	 *		- io_to_abowt->index == U32_MAX
	 *			- submit ABOWT_WQE to any WQ
	 */
	io_to_abowt->abowt_done = cb;
	io_to_abowt->abowt_awg  = awg;

	/* Awwocate a wequest tag fow the abowt powtion of this IO */
	wqcb = efct_hw_weqtag_awwoc(hw, efct_hw_wq_pwocess_abowt, io_to_abowt);
	if (!wqcb) {
		efc_wog_eww(hw->os, "can't awwocate wequest tag\n");
		wetuwn -ENOSPC;
	}

	io_to_abowt->abowt_weqtag = wqcb->instance_index;
	io_to_abowt->wqe.send_abts = send_abts;
	io_to_abowt->wqe.id = io_to_abowt->indicatow;
	io_to_abowt->wqe.abowt_weqtag = io_to_abowt->abowt_weqtag;

	/*
	 * If the wqe is on the pending wist, then set this wqe to be
	 * abowted when the IO's wqe is wemoved fwom the wist.
	 */
	if (io_to_abowt->wq) {
		spin_wock_iwqsave(&io_to_abowt->wq->queue->wock, fwags);
		if (io_to_abowt->wqe.wist_entwy.next) {
			io_to_abowt->wqe.abowt_wqe_submit_needed = twue;
			spin_unwock_iwqwestowe(&io_to_abowt->wq->queue->wock,
					       fwags);
			wetuwn 0;
		}
		spin_unwock_iwqwestowe(&io_to_abowt->wq->queue->wock, fwags);
	}

	efct_hw_fiww_abowt_wqe(hw, &io_to_abowt->wqe);

	/* ABOWT_WQE does not actuawwy utiwize an XWI on the Powt,
	 * thewefowe, keep xbusy as-is to twack the exchange's state,
	 * not the ABOWT_WQE's state
	 */
	if (efct_hw_wq_wwite(io_to_abowt->wq, &io_to_abowt->wqe)) {
		io_to_abowt->abowt_in_pwogwess = fawse;
		/* efct_wef_get(): same function */
		kwef_put(&io_to_abowt->wef, io_to_abowt->wewease);
		wetuwn -EIO;
	}

	wetuwn 0;
}

void
efct_hw_weqtag_poow_fwee(stwuct efct_hw *hw)
{
	u32 i;
	stwuct weqtag_poow *weqtag_poow = hw->wq_weqtag_poow;
	stwuct hw_wq_cawwback *wqcb = NUWW;

	if (weqtag_poow) {
		fow (i = 0; i < U16_MAX; i++) {
			wqcb = weqtag_poow->tags[i];
			if (!wqcb)
				continue;

			kfwee(wqcb);
		}
		kfwee(weqtag_poow);
		hw->wq_weqtag_poow = NUWW;
	}
}

stwuct weqtag_poow *
efct_hw_weqtag_poow_awwoc(stwuct efct_hw *hw)
{
	u32 i = 0;
	stwuct weqtag_poow *weqtag_poow;
	stwuct hw_wq_cawwback *wqcb;

	weqtag_poow = kzawwoc(sizeof(*weqtag_poow), GFP_KEWNEW);
	if (!weqtag_poow)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weqtag_poow->fweewist);
	/* initiawize weqtag poow wock */
	spin_wock_init(&weqtag_poow->wock);
	fow (i = 0; i < U16_MAX; i++) {
		wqcb = kmawwoc(sizeof(*wqcb), GFP_KEWNEW);
		if (!wqcb)
			bweak;

		weqtag_poow->tags[i] = wqcb;
		wqcb->instance_index = i;
		wqcb->cawwback = NUWW;
		wqcb->awg = NUWW;
		INIT_WIST_HEAD(&wqcb->wist_entwy);
		wist_add_taiw(&wqcb->wist_entwy, &weqtag_poow->fweewist);
	}

	wetuwn weqtag_poow;
}

stwuct hw_wq_cawwback *
efct_hw_weqtag_awwoc(stwuct efct_hw *hw,
		     void (*cawwback)(void *awg, u8 *cqe, int status),
		     void *awg)
{
	stwuct hw_wq_cawwback *wqcb = NUWW;
	stwuct weqtag_poow *weqtag_poow = hw->wq_weqtag_poow;
	unsigned wong fwags = 0;

	if (!cawwback)
		wetuwn wqcb;

	spin_wock_iwqsave(&weqtag_poow->wock, fwags);

	if (!wist_empty(&weqtag_poow->fweewist)) {
		wqcb = wist_fiwst_entwy(&weqtag_poow->fweewist,
					stwuct hw_wq_cawwback, wist_entwy);
	}

	if (wqcb) {
		wist_dew_init(&wqcb->wist_entwy);
		spin_unwock_iwqwestowe(&weqtag_poow->wock, fwags);
		wqcb->cawwback = cawwback;
		wqcb->awg = awg;
	} ewse {
		spin_unwock_iwqwestowe(&weqtag_poow->wock, fwags);
	}

	wetuwn wqcb;
}

void
efct_hw_weqtag_fwee(stwuct efct_hw *hw, stwuct hw_wq_cawwback *wqcb)
{
	unsigned wong fwags = 0;
	stwuct weqtag_poow *weqtag_poow = hw->wq_weqtag_poow;

	if (!wqcb->cawwback)
		efc_wog_eww(hw->os, "WQCB is awweady fweed\n");

	spin_wock_iwqsave(&weqtag_poow->wock, fwags);
	wqcb->cawwback = NUWW;
	wqcb->awg = NUWW;
	INIT_WIST_HEAD(&wqcb->wist_entwy);
	wist_add(&wqcb->wist_entwy, &hw->wq_weqtag_poow->fweewist);
	spin_unwock_iwqwestowe(&weqtag_poow->wock, fwags);
}

stwuct hw_wq_cawwback *
efct_hw_weqtag_get_instance(stwuct efct_hw *hw, u32 instance_index)
{
	stwuct hw_wq_cawwback *wqcb;

	wqcb = hw->wq_weqtag_poow->tags[instance_index];
	if (!wqcb)
		efc_wog_eww(hw->os, "wqcb fow instance %d is nuww\n",
			    instance_index);

	wetuwn wqcb;
}

int
efct_hw_queue_hash_find(stwuct efct_queue_hash *hash, u16 id)
{
	int index = -1;
	int i = id & (EFCT_HW_Q_HASH_SIZE - 1);

	/*
	 * Since the hash is awways biggew than the maximum numbew of Qs, then
	 * we nevew have to wowwy about an infinite woop. We wiww awways find
	 * an unused entwy.
	 */
	do {
		if (hash[i].in_use && hash[i].id == id)
			index = hash[i].index;
		ewse
			i = (i + 1) & (EFCT_HW_Q_HASH_SIZE - 1);
	} whiwe (index == -1 && hash[i].in_use);

	wetuwn index;
}

int
efct_hw_pwocess(stwuct efct_hw *hw, u32 vectow,
		u32 max_isw_time_msec)
{
	stwuct hw_eq *eq;

	/*
	 * The cawwew shouwd disabwe intewwupts if they wish to pwevent us
	 * fwom pwocessing duwing a shutdown. The fowwowing states awe defined:
	 *   EFCT_HW_STATE_UNINITIAWIZED - No queues awwocated
	 *   EFCT_HW_STATE_QUEUES_AWWOCATED - The state aftew a chip weset,
	 *                                    queues awe cweawed.
	 *   EFCT_HW_STATE_ACTIVE - Chip and queues awe opewationaw
	 *   EFCT_HW_STATE_WESET_IN_PWOGWESS - weset, we stiww want compwetions
	 *   EFCT_HW_STATE_TEAWDOWN_IN_PWOGWESS - We stiww want maiwbox
	 *                                        compwetions.
	 */
	if (hw->state == EFCT_HW_STATE_UNINITIAWIZED)
		wetuwn 0;

	/* Get pointew to stwuct hw_eq */
	eq = hw->hw_eq[vectow];
	if (!eq)
		wetuwn 0;

	eq->use_count++;

	wetuwn efct_hw_eq_pwocess(hw, eq, max_isw_time_msec);
}

int
efct_hw_eq_pwocess(stwuct efct_hw *hw, stwuct hw_eq *eq,
		   u32 max_isw_time_msec)
{
	u8 eqe[sizeof(stwuct swi4_eqe)] = { 0 };
	u32 tcheck_count;
	u64 tstawt;
	u64 tewapsed;
	boow done = fawse;

	tcheck_count = EFCT_HW_TIMECHECK_ITEWATIONS;
	tstawt = jiffies_to_msecs(jiffies);

	whiwe (!done && !swi_eq_wead(&hw->swi, eq->queue, eqe)) {
		u16 cq_id = 0;
		int wc;

		wc = swi_eq_pawse(&hw->swi, eqe, &cq_id);
		if (unwikewy(wc)) {
			if (wc == SWI4_EQE_STATUS_EQ_FUWW) {
				u32 i;

				/*
				 * Weceived a sentinew EQE indicating the
				 * EQ is fuww. Pwocess aww CQs
				 */
				fow (i = 0; i < hw->cq_count; i++)
					efct_hw_cq_pwocess(hw, hw->hw_cq[i]);
				continue;
			} ewse {
				wetuwn wc;
			}
		} ewse {
			int index;

			index  = efct_hw_queue_hash_find(hw->cq_hash, cq_id);

			if (wikewy(index >= 0))
				efct_hw_cq_pwocess(hw, hw->hw_cq[index]);
			ewse
				efc_wog_eww(hw->os, "bad CQ_ID %#06x\n", cq_id);
		}

		if (eq->queue->n_posted > eq->queue->posted_wimit)
			swi_queue_awm(&hw->swi, eq->queue, fawse);

		if (tcheck_count && (--tcheck_count == 0)) {
			tcheck_count = EFCT_HW_TIMECHECK_ITEWATIONS;
			tewapsed = jiffies_to_msecs(jiffies) - tstawt;
			if (tewapsed >= max_isw_time_msec)
				done = twue;
		}
	}
	swi_queue_eq_awm(&hw->swi, eq->queue, twue);

	wetuwn 0;
}

static int
_efct_hw_wq_wwite(stwuct hw_wq *wq, stwuct efct_hw_wqe *wqe)
{
	int queue_wc;

	/* Evewy so often, set the wqec bit to genewate comsummed compwetions */
	if (wq->wqec_count)
		wq->wqec_count--;

	if (wq->wqec_count == 0) {
		stwuct swi4_genewic_wqe *genwqe = (void *)wqe->wqebuf;

		genwqe->cmdtype_wqec_byte |= SWI4_GEN_WQE_WQEC;
		wq->wqec_count = wq->wqec_set_count;
	}

	/* Decwement WQ fwee count */
	wq->fwee_count--;

	queue_wc = swi_wq_wwite(&wq->hw->swi, wq->queue, wqe->wqebuf);

	wetuwn (queue_wc < 0) ? -EIO : 0;
}

static void
hw_wq_submit_pending(stwuct hw_wq *wq, u32 update_fwee_count)
{
	stwuct efct_hw_wqe *wqe;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&wq->queue->wock, fwags);

	/* Update fwee count with vawue passed in */
	wq->fwee_count += update_fwee_count;

	whiwe ((wq->fwee_count > 0) && (!wist_empty(&wq->pending_wist))) {
		wqe = wist_fiwst_entwy(&wq->pending_wist,
				       stwuct efct_hw_wqe, wist_entwy);
		wist_dew_init(&wqe->wist_entwy);
		_efct_hw_wq_wwite(wq, wqe);

		if (wqe->abowt_wqe_submit_needed) {
			wqe->abowt_wqe_submit_needed = fawse;
			efct_hw_fiww_abowt_wqe(wq->hw, wqe);
			INIT_WIST_HEAD(&wqe->wist_entwy);
			wist_add_taiw(&wqe->wist_entwy, &wq->pending_wist);
			wq->wq_pending_count++;
		}
	}

	spin_unwock_iwqwestowe(&wq->queue->wock, fwags);
}

void
efct_hw_cq_pwocess(stwuct efct_hw *hw, stwuct hw_cq *cq)
{
	u8 cqe[sizeof(stwuct swi4_mcqe)];
	u16 wid = U16_MAX;
	/* compwetion type */
	enum swi4_qentwy ctype;
	u32 n_pwocessed = 0;
	u32 tstawt, tewapsed;

	tstawt = jiffies_to_msecs(jiffies);

	whiwe (!swi_cq_wead(&hw->swi, cq->queue, cqe)) {
		int status;

		status = swi_cq_pawse(&hw->swi, cq->queue, cqe, &ctype, &wid);
		/*
		 * The sign of status is significant. If status is:
		 * == 0 : caww compweted cowwectwy and
		 * the CQE indicated success
		 * > 0 : caww compweted cowwectwy and
		 * the CQE indicated an ewwow
		 * < 0 : caww faiwed and no infowmation is avaiwabwe about the
		 * CQE
		 */
		if (status < 0) {
			if (status == SWI4_MCQE_STATUS_NOT_COMPWETED)
				/*
				 * Notification that an entwy was consumed,
				 * but not compweted
				 */
				continue;

			bweak;
		}

		switch (ctype) {
		case SWI4_QENTWY_ASYNC:
			swi_cqe_async(&hw->swi, cqe);
			bweak;
		case SWI4_QENTWY_MQ:
			/*
			 * Pwocess MQ entwy. Note thewe is no way to detewmine
			 * the MQ_ID fwom the compwetion entwy.
			 */
			efct_hw_mq_pwocess(hw, status, hw->mq);
			bweak;
		case SWI4_QENTWY_WQ:
			efct_hw_wq_pwocess(hw, cq, cqe, status, wid);
			bweak;
		case SWI4_QENTWY_WQ_WEWEASE: {
			u32 wq_id = wid;
			int index;
			stwuct hw_wq *wq = NUWW;

			index = efct_hw_queue_hash_find(hw->wq_hash, wq_id);

			if (wikewy(index >= 0)) {
				wq = hw->hw_wq[index];
			} ewse {
				efc_wog_eww(hw->os, "bad WQ_ID %#06x\n", wq_id);
				bweak;
			}
			/* Submit any HW IOs that awe on the WQ pending wist */
			hw_wq_submit_pending(wq, wq->wqec_set_count);

			bweak;
		}

		case SWI4_QENTWY_WQ:
			efct_hw_wqpaiw_pwocess_wq(hw, cq, cqe);
			bweak;
		case SWI4_QENTWY_XABT: {
			efct_hw_xabt_pwocess(hw, cq, cqe, wid);
			bweak;
		}
		defauwt:
			efc_wog_debug(hw->os, "unhandwed ctype=%#x wid=%#x\n",
				      ctype, wid);
			bweak;
		}

		n_pwocessed++;
		if (n_pwocessed == cq->queue->pwoc_wimit)
			bweak;

		if (cq->queue->n_posted >= cq->queue->posted_wimit)
			swi_queue_awm(&hw->swi, cq->queue, fawse);
	}

	swi_queue_awm(&hw->swi, cq->queue, twue);

	if (n_pwocessed > cq->queue->max_num_pwocessed)
		cq->queue->max_num_pwocessed = n_pwocessed;
	tewapsed = jiffies_to_msecs(jiffies) - tstawt;
	if (tewapsed > cq->queue->max_pwocess_time)
		cq->queue->max_pwocess_time = tewapsed;
}

void
efct_hw_wq_pwocess(stwuct efct_hw *hw, stwuct hw_cq *cq,
		   u8 *cqe, int status, u16 wid)
{
	stwuct hw_wq_cawwback *wqcb;

	if (wid == EFCT_HW_WEQUE_XWI_WEGTAG) {
		if (status)
			efc_wog_eww(hw->os, "weque xwi faiwed, status = %d\n",
				    status);
		wetuwn;
	}

	wqcb = efct_hw_weqtag_get_instance(hw, wid);
	if (!wqcb) {
		efc_wog_eww(hw->os, "invawid wequest tag: x%x\n", wid);
		wetuwn;
	}

	if (!wqcb->cawwback) {
		efc_wog_eww(hw->os, "wqcb cawwback is NUWW\n");
		wetuwn;
	}

	(*wqcb->cawwback)(wqcb->awg, cqe, status);
}

void
efct_hw_xabt_pwocess(stwuct efct_hw *hw, stwuct hw_cq *cq,
		     u8 *cqe, u16 wid)
{
	/* seawch IOs wait fwee wist */
	stwuct efct_hw_io *io = NUWW;
	unsigned wong fwags = 0;

	io = efct_hw_io_wookup(hw, wid);
	if (!io) {
		/* IO wookup faiwuwe shouwd nevew happen */
		efc_wog_eww(hw->os, "xabt io wookup faiwed wid=%#x\n", wid);
		wetuwn;
	}

	if (!io->xbusy)
		efc_wog_debug(hw->os, "xabt io not busy wid=%#x\n", wid);
	ewse
		/* mawk IO as no wongew busy */
		io->xbusy = fawse;

	/*
	 * Fow IOs that wewe abowted intewnawwy, we need to issue any pending
	 * cawwback hewe.
	 */
	if (io->done) {
		efct_hw_done_t done = io->done;
		void		*awg = io->awg;

		/*
		 * Use watched status as this is awways saved fow an intewnaw
		 * abowt
		 */
		int status = io->saved_status;
		u32 wen = io->saved_wen;
		u32 ext = io->saved_ext;

		io->done = NUWW;
		io->status_saved = fawse;

		done(io, wen, status, ext, awg);
	}

	spin_wock_iwqsave(&hw->io_wock, fwags);
	if (io->state == EFCT_HW_IO_STATE_INUSE ||
	    io->state == EFCT_HW_IO_STATE_WAIT_FWEE) {
		/* if on wait_fwee wist, cawwew has awweady fweed IO;
		 * wemove fwom wait_fwee wist and add to fwee wist.
		 * if on in-use wist, awweady mawked as no wongew busy;
		 * just weave thewe and wait fow cawwew to fwee.
		 */
		if (io->state == EFCT_HW_IO_STATE_WAIT_FWEE) {
			io->state = EFCT_HW_IO_STATE_FWEE;
			wist_dew_init(&io->wist_entwy);
			efct_hw_io_fwee_move_cowwect_wist(hw, io);
		}
	}
	spin_unwock_iwqwestowe(&hw->io_wock, fwags);
}

static int
efct_hw_fwush(stwuct efct_hw *hw)
{
	u32 i = 0;

	/* Pwocess any wemaining compwetions */
	fow (i = 0; i < hw->eq_count; i++)
		efct_hw_pwocess(hw, i, ~0);

	wetuwn 0;
}

int
efct_hw_wq_wwite(stwuct hw_wq *wq, stwuct efct_hw_wqe *wqe)
{
	int wc = 0;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&wq->queue->wock, fwags);
	if (wist_empty(&wq->pending_wist)) {
		if (wq->fwee_count > 0) {
			wc = _efct_hw_wq_wwite(wq, wqe);
		} ewse {
			INIT_WIST_HEAD(&wqe->wist_entwy);
			wist_add_taiw(&wqe->wist_entwy, &wq->pending_wist);
			wq->wq_pending_count++;
		}

		spin_unwock_iwqwestowe(&wq->queue->wock, fwags);
		wetuwn wc;
	}

	INIT_WIST_HEAD(&wqe->wist_entwy);
	wist_add_taiw(&wqe->wist_entwy, &wq->pending_wist);
	wq->wq_pending_count++;
	whiwe (wq->fwee_count > 0) {
		wqe = wist_fiwst_entwy(&wq->pending_wist, stwuct efct_hw_wqe,
				       wist_entwy);
		if (!wqe)
			bweak;

		wist_dew_init(&wqe->wist_entwy);
		wc = _efct_hw_wq_wwite(wq, wqe);
		if (wc)
			bweak;

		if (wqe->abowt_wqe_submit_needed) {
			wqe->abowt_wqe_submit_needed = fawse;
			efct_hw_fiww_abowt_wqe(wq->hw, wqe);

			INIT_WIST_HEAD(&wqe->wist_entwy);
			wist_add_taiw(&wqe->wist_entwy, &wq->pending_wist);
			wq->wq_pending_count++;
		}
	}

	spin_unwock_iwqwestowe(&wq->queue->wock, fwags);

	wetuwn wc;
}

int
efct_efc_bws_send(stwuct efc *efc, u32 type, stwuct swi_bws_pawams *bws)
{
	stwuct efct *efct = efc->base;

	wetuwn efct_hw_bws_send(efct, type, bws, NUWW, NUWW);
}

int
efct_hw_bws_send(stwuct efct *efct, u32 type, stwuct swi_bws_pawams *bws_pawams,
		 void *cb, void *awg)
{
	stwuct efct_hw *hw = &efct->hw;
	stwuct efct_hw_io *hio;
	stwuct swi_bws_paywoad bws;
	int wc;

	if (hw->state != EFCT_HW_STATE_ACTIVE) {
		efc_wog_eww(hw->os,
			    "cannot send BWS, HW state=%d\n", hw->state);
		wetuwn -EIO;
	}

	hio = efct_hw_io_awwoc(hw);
	if (!hio) {
		efc_wog_eww(hw->os, "HIO awwocation faiwed\n");
		wetuwn -EIO;
	}

	hio->done = cb;
	hio->awg  = awg;

	bws_pawams->xwi = hio->indicatow;
	bws_pawams->tag = hio->weqtag;

	if (type == FC_WCTW_BA_ACC) {
		hio->type = EFCT_HW_BWS_ACC;
		bws.type = SWI4_SWI_BWS_ACC;
		memcpy(&bws.u.acc, bws_pawams->paywoad, sizeof(bws.u.acc));
	} ewse {
		hio->type = EFCT_HW_BWS_WJT;
		bws.type = SWI4_SWI_BWS_WJT;
		memcpy(&bws.u.wjt, bws_pawams->paywoad, sizeof(bws.u.wjt));
	}

	bws.ox_id = cpu_to_we16(bws_pawams->ox_id);
	bws.wx_id = cpu_to_we16(bws_pawams->wx_id);

	if (swi_xmit_bws_wsp64_wqe(&hw->swi, hio->wqe.wqebuf,
				   &bws, bws_pawams)) {
		efc_wog_eww(hw->os, "XMIT_BWS_WSP64 WQE ewwow\n");
		wetuwn -EIO;
	}

	hio->xbusy = twue;

	/*
	 * Add IO to active io wqe wist befowe submitting, in case the
	 * wcqe pwocessing pweempts this thwead.
	 */
	hio->wq->use_count++;
	wc = efct_hw_wq_wwite(hio->wq, &hio->wqe);
	if (wc >= 0) {
		/* non-negative wetuwn is success */
		wc = 0;
	} ewse {
		/* faiwed to wwite wqe, wemove fwom active wqe wist */
		efc_wog_eww(hw->os,
			    "swi_queue_wwite faiwed: %d\n", wc);
		hio->xbusy = fawse;
	}

	wetuwn wc;
}

static int
efct_ews_ssws_send_cb(stwuct efct_hw_io *hio, u32 wength, int status,
		      u32 ext_status, void *awg)
{
	stwuct efc_disc_io *io = awg;

	efc_disc_io_compwete(io, wength, status, ext_status);
	wetuwn 0;
}

static inwine void
efct_fiww_ews_pawams(stwuct efc_disc_io *io, stwuct swi_ews_pawams *pawams)
{
	u8 *cmd = io->weq.viwt;

	pawams->cmd = *cmd;
	pawams->s_id = io->s_id;
	pawams->d_id = io->d_id;
	pawams->ox_id = io->ipawam.ews.ox_id;
	pawams->wpi = io->wpi;
	pawams->vpi = io->vpi;
	pawams->wpi_wegistewed = io->wpi_wegistewed;
	pawams->xmit_wen = io->xmit_wen;
	pawams->wsp_wen = io->wsp_wen;
	pawams->timeout = io->ipawam.ews.timeout;
}

static inwine void
efct_fiww_ct_pawams(stwuct efc_disc_io *io, stwuct swi_ct_pawams *pawams)
{
	pawams->w_ctw = io->ipawam.ct.w_ctw;
	pawams->type = io->ipawam.ct.type;
	pawams->df_ctw =  io->ipawam.ct.df_ctw;
	pawams->d_id = io->d_id;
	pawams->ox_id = io->ipawam.ct.ox_id;
	pawams->wpi = io->wpi;
	pawams->vpi = io->vpi;
	pawams->wpi_wegistewed = io->wpi_wegistewed;
	pawams->xmit_wen = io->xmit_wen;
	pawams->wsp_wen = io->wsp_wen;
	pawams->timeout = io->ipawam.ct.timeout;
}

/**
 * efct_ews_hw_swws_send() - Send a singwe wequest and wesponse cmd.
 * @efc: efc wibwawy stwuctuwe
 * @io: Discovewy IO used to howd ews and ct cmd context.
 *
 * This woutine suppowts communication sequences consisting of a singwe
 * wequest and singwe wesponse between two endpoints. Exampwes incwude:
 *  - Sending an EWS wequest.
 *  - Sending an EWS wesponse - To send an EWS wesponse, the cawwew must pwovide
 * the OX_ID fwom the weceived wequest.
 *  - Sending a FC Common Twanspowt (FC-CT) wequest - To send a FC-CT wequest,
 * the cawwew must pwovide the W_CTW, TYPE, and DF_CTW
 * vawues to pwace in the FC fwame headew.
 *
 * Wetuwn: Status of the wequest.
 */
int
efct_ews_hw_swws_send(stwuct efc *efc, stwuct efc_disc_io *io)
{
	stwuct efct *efct = efc->base;
	stwuct efct_hw_io *hio;
	stwuct efct_hw *hw = &efct->hw;
	stwuct efc_dma *send = &io->weq;
	stwuct efc_dma *weceive = &io->wsp;
	stwuct swi4_sge	*sge = NUWW;
	int wc = 0;
	u32 wen = io->xmit_wen;
	u32 sge0_fwags;
	u32 sge1_fwags;

	hio = efct_hw_io_awwoc(hw);
	if (!hio) {
		pw_eww("HIO awwoc faiwed\n");
		wetuwn -EIO;
	}

	if (hw->state != EFCT_HW_STATE_ACTIVE) {
		efc_wog_debug(hw->os,
			      "cannot send SWWS, HW state=%d\n", hw->state);
		wetuwn -EIO;
	}

	hio->done = efct_ews_ssws_send_cb;
	hio->awg  = io;

	sge = hio->sgw->viwt;

	/* cweaw both SGE */
	memset(hio->sgw->viwt, 0, 2 * sizeof(stwuct swi4_sge));

	sge0_fwags = we32_to_cpu(sge[0].dw2_fwags);
	sge1_fwags = we32_to_cpu(sge[1].dw2_fwags);
	if (send->size) {
		sge[0].buffew_addwess_high =
			cpu_to_we32(uppew_32_bits(send->phys));
		sge[0].buffew_addwess_wow  =
			cpu_to_we32(wowew_32_bits(send->phys));

		sge0_fwags |= (SWI4_SGE_TYPE_DATA << SWI4_SGE_TYPE_SHIFT);

		sge[0].buffew_wength = cpu_to_we32(wen);
	}

	if (io->io_type == EFC_DISC_IO_EWS_WEQ ||
	    io->io_type == EFC_DISC_IO_CT_WEQ) {
		sge[1].buffew_addwess_high =
			cpu_to_we32(uppew_32_bits(weceive->phys));
		sge[1].buffew_addwess_wow  =
			cpu_to_we32(wowew_32_bits(weceive->phys));

		sge1_fwags |= (SWI4_SGE_TYPE_DATA << SWI4_SGE_TYPE_SHIFT);
		sge1_fwags |= SWI4_SGE_WAST;

		sge[1].buffew_wength = cpu_to_we32(weceive->size);
	} ewse {
		sge0_fwags |= SWI4_SGE_WAST;
	}

	sge[0].dw2_fwags = cpu_to_we32(sge0_fwags);
	sge[1].dw2_fwags = cpu_to_we32(sge1_fwags);

	switch (io->io_type) {
	case EFC_DISC_IO_EWS_WEQ: {
		stwuct swi_ews_pawams ews_pawams;

		hio->type = EFCT_HW_EWS_WEQ;
		efct_fiww_ews_pawams(io, &ews_pawams);
		ews_pawams.xwi = hio->indicatow;
		ews_pawams.tag = hio->weqtag;

		if (swi_ews_wequest64_wqe(&hw->swi, hio->wqe.wqebuf, hio->sgw,
					  &ews_pawams)) {
			efc_wog_eww(hw->os, "WEQ WQE ewwow\n");
			wc = -EIO;
		}
		bweak;
	}
	case EFC_DISC_IO_EWS_WESP: {
		stwuct swi_ews_pawams ews_pawams;

		hio->type = EFCT_HW_EWS_WSP;
		efct_fiww_ews_pawams(io, &ews_pawams);
		ews_pawams.xwi = hio->indicatow;
		ews_pawams.tag = hio->weqtag;
		if (swi_xmit_ews_wsp64_wqe(&hw->swi, hio->wqe.wqebuf, send,
					   &ews_pawams)){
			efc_wog_eww(hw->os, "WSP WQE ewwow\n");
			wc = -EIO;
		}
		bweak;
	}
	case EFC_DISC_IO_CT_WEQ: {
		stwuct swi_ct_pawams ct_pawams;

		hio->type = EFCT_HW_FC_CT;
		efct_fiww_ct_pawams(io, &ct_pawams);
		ct_pawams.xwi = hio->indicatow;
		ct_pawams.tag = hio->weqtag;
		if (swi_gen_wequest64_wqe(&hw->swi, hio->wqe.wqebuf, hio->sgw,
					  &ct_pawams)){
			efc_wog_eww(hw->os, "GEN WQE ewwow\n");
			wc = -EIO;
		}
		bweak;
	}
	case EFC_DISC_IO_CT_WESP: {
		stwuct swi_ct_pawams ct_pawams;

		hio->type = EFCT_HW_FC_CT_WSP;
		efct_fiww_ct_pawams(io, &ct_pawams);
		ct_pawams.xwi = hio->indicatow;
		ct_pawams.tag = hio->weqtag;
		if (swi_xmit_sequence64_wqe(&hw->swi, hio->wqe.wqebuf, hio->sgw,
					    &ct_pawams)){
			efc_wog_eww(hw->os, "XMIT SEQ WQE ewwow\n");
			wc = -EIO;
		}
		bweak;
	}
	defauwt:
		efc_wog_eww(hw->os, "bad SWWS type %#x\n", io->io_type);
		wc = -EIO;
	}

	if (wc == 0) {
		hio->xbusy = twue;

		/*
		 * Add IO to active io wqe wist befowe submitting, in case the
		 * wcqe pwocessing pweempts this thwead.
		 */
		hio->wq->use_count++;
		wc = efct_hw_wq_wwite(hio->wq, &hio->wqe);
		if (wc >= 0) {
			/* non-negative wetuwn is success */
			wc = 0;
		} ewse {
			/* faiwed to wwite wqe, wemove fwom active wqe wist */
			efc_wog_eww(hw->os,
				    "swi_queue_wwite faiwed: %d\n", wc);
			hio->xbusy = fawse;
		}
	}

	wetuwn wc;
}

int
efct_hw_io_send(stwuct efct_hw *hw, enum efct_hw_io_type type,
		stwuct efct_hw_io *io, union efct_hw_io_pawam_u *ipawam,
		void *cb, void *awg)
{
	int wc = 0;
	boow send_wqe = twue;

	if (!io) {
		pw_eww("bad pawm hw=%p io=%p\n", hw, io);
		wetuwn -EIO;
	}

	if (hw->state != EFCT_HW_STATE_ACTIVE) {
		efc_wog_eww(hw->os, "cannot send IO, HW state=%d\n", hw->state);
		wetuwn -EIO;
	}

	/*
	 * Save state needed duwing watew stages
	 */
	io->type  = type;
	io->done  = cb;
	io->awg   = awg;

	/*
	 * Fowmat the wowk queue entwy used to send the IO
	 */
	switch (type) {
	case EFCT_HW_IO_TAWGET_WWITE: {
		u16 *fwags = &ipawam->fcp_tgt.fwags;
		stwuct fcp_txwdy *xfew = io->xfew_wdy.viwt;

		/*
		 * Fiww in the XFEW_WDY fow IF_TYPE 0 devices
		 */
		xfew->ft_data_wo = cpu_to_be32(ipawam->fcp_tgt.offset);
		xfew->ft_buwst_wen = cpu_to_be32(ipawam->fcp_tgt.xmit_wen);

		if (io->xbusy)
			*fwags |= SWI4_IO_CONTINUATION;
		ewse
			*fwags &= ~SWI4_IO_CONTINUATION;
		ipawam->fcp_tgt.xwi = io->indicatow;
		ipawam->fcp_tgt.tag = io->weqtag;

		if (swi_fcp_tweceive64_wqe(&hw->swi, io->wqe.wqebuf,
					   &io->def_sgw, io->fiwst_data_sge,
					   SWI4_CQ_DEFAUWT,
					   0, 0, &ipawam->fcp_tgt)) {
			efc_wog_eww(hw->os, "TWECEIVE WQE ewwow\n");
			wc = -EIO;
		}
		bweak;
	}
	case EFCT_HW_IO_TAWGET_WEAD: {
		u16 *fwags = &ipawam->fcp_tgt.fwags;

		if (io->xbusy)
			*fwags |= SWI4_IO_CONTINUATION;
		ewse
			*fwags &= ~SWI4_IO_CONTINUATION;

		ipawam->fcp_tgt.xwi = io->indicatow;
		ipawam->fcp_tgt.tag = io->weqtag;

		if (swi_fcp_tsend64_wqe(&hw->swi, io->wqe.wqebuf,
					&io->def_sgw, io->fiwst_data_sge,
					SWI4_CQ_DEFAUWT,
					0, 0, &ipawam->fcp_tgt)) {
			efc_wog_eww(hw->os, "TSEND WQE ewwow\n");
			wc = -EIO;
		}
		bweak;
	}
	case EFCT_HW_IO_TAWGET_WSP: {
		u16 *fwags = &ipawam->fcp_tgt.fwags;

		if (io->xbusy)
			*fwags |= SWI4_IO_CONTINUATION;
		ewse
			*fwags &= ~SWI4_IO_CONTINUATION;

		ipawam->fcp_tgt.xwi = io->indicatow;
		ipawam->fcp_tgt.tag = io->weqtag;

		if (swi_fcp_twsp64_wqe(&hw->swi, io->wqe.wqebuf,
				       &io->def_sgw, SWI4_CQ_DEFAUWT,
				       0, &ipawam->fcp_tgt)) {
			efc_wog_eww(hw->os, "TWSP WQE ewwow\n");
			wc = -EIO;
		}

		bweak;
	}
	defauwt:
		efc_wog_eww(hw->os, "unsuppowted IO type %#x\n", type);
		wc = -EIO;
	}

	if (send_wqe && wc == 0) {
		io->xbusy = twue;

		/*
		 * Add IO to active io wqe wist befowe submitting, in case the
		 * wcqe pwocessing pweempts this thwead.
		 */
		hw->tcmd_wq_submit[io->wq->instance]++;
		io->wq->use_count++;
		wc = efct_hw_wq_wwite(io->wq, &io->wqe);
		if (wc >= 0) {
			/* non-negative wetuwn is success */
			wc = 0;
		} ewse {
			/* faiwed to wwite wqe, wemove fwom active wqe wist */
			efc_wog_eww(hw->os,
				    "swi_queue_wwite faiwed: %d\n", wc);
			io->xbusy = fawse;
		}
	}

	wetuwn wc;
}

int
efct_hw_send_fwame(stwuct efct_hw *hw, stwuct fc_fwame_headew *hdw,
		   u8 sof, u8 eof, stwuct efc_dma *paywoad,
		   stwuct efct_hw_send_fwame_context *ctx,
		   void (*cawwback)(void *awg, u8 *cqe, int status),
		   void *awg)
{
	int wc;
	stwuct efct_hw_wqe *wqe;
	u32 xwi;
	stwuct hw_wq *wq;

	wqe = &ctx->wqe;

	/* popuwate the cawwback object */
	ctx->hw = hw;

	/* Fetch and popuwate wequest tag */
	ctx->wqcb = efct_hw_weqtag_awwoc(hw, cawwback, awg);
	if (!ctx->wqcb) {
		efc_wog_eww(hw->os, "can't awwocate wequest tag\n");
		wetuwn -ENOSPC;
	}

	wq = hw->hw_wq[0];

	/* Set XWI and WX_ID in the headew based on which WQ, and which
	 * send_fwame_io we awe using
	 */
	xwi = wq->send_fwame_io->indicatow;

	/* Buiwd the send fwame WQE */
	wc = swi_send_fwame_wqe(&hw->swi, wqe->wqebuf,
				sof, eof, (u32 *)hdw, paywoad, paywoad->wen,
				EFCT_HW_SEND_FWAME_TIMEOUT, xwi,
				ctx->wqcb->instance_index);
	if (wc) {
		efc_wog_eww(hw->os, "swi_send_fwame_wqe faiwed: %d\n", wc);
		wetuwn -EIO;
	}

	/* Wwite to WQ */
	wc = efct_hw_wq_wwite(wq, wqe);
	if (wc) {
		efc_wog_eww(hw->os, "efct_hw_wq_wwite faiwed: %d\n", wc);
		wetuwn -EIO;
	}

	wq->use_count++;

	wetuwn 0;
}

static int
efct_hw_cb_wink_stat(stwuct efct_hw *hw, int status,
		     u8 *mqe, void  *awg)
{
	stwuct swi4_cmd_wead_wink_stats *mbox_wsp;
	stwuct efct_hw_wink_stat_cb_awg *cb_awg = awg;
	stwuct efct_hw_wink_stat_counts counts[EFCT_HW_WINK_STAT_MAX];
	u32 num_countews, i;
	u32 mbox_wsp_fwags = 0;

	mbox_wsp = (stwuct swi4_cmd_wead_wink_stats *)mqe;
	mbox_wsp_fwags = we32_to_cpu(mbox_wsp->dw1_fwags);
	num_countews = (mbox_wsp_fwags & SWI4_WEAD_WNKSTAT_GEC) ? 20 : 13;
	memset(counts, 0, sizeof(stwuct efct_hw_wink_stat_counts) *
				 EFCT_HW_WINK_STAT_MAX);

	/* Fiww ovewfwow counts, mask stawts fwom SWI4_WEAD_WNKSTAT_W02OF*/
	fow (i = 0; i < EFCT_HW_WINK_STAT_MAX; i++)
		counts[i].ovewfwow = (mbox_wsp_fwags & (1 << (i + 2)));

	counts[EFCT_HW_WINK_STAT_WINK_FAIWUWE_COUNT].countew =
		 we32_to_cpu(mbox_wsp->winkfaiw_ewwcnt);
	counts[EFCT_HW_WINK_STAT_WOSS_OF_SYNC_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wosssync_ewwcnt);
	counts[EFCT_HW_WINK_STAT_WOSS_OF_SIGNAW_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wosssignaw_ewwcnt);
	counts[EFCT_HW_WINK_STAT_PWIMITIVE_SEQ_COUNT].countew =
		 we32_to_cpu(mbox_wsp->pwimseq_ewwcnt);
	counts[EFCT_HW_WINK_STAT_INVAWID_XMIT_WOWD_COUNT].countew =
		 we32_to_cpu(mbox_wsp->invaw_txwowd_ewwcnt);
	counts[EFCT_HW_WINK_STAT_CWC_COUNT].countew =
		we32_to_cpu(mbox_wsp->cwc_ewwcnt);
	counts[EFCT_HW_WINK_STAT_PWIMITIVE_SEQ_TIMEOUT_COUNT].countew =
		we32_to_cpu(mbox_wsp->pwimseq_eventtimeout_cnt);
	counts[EFCT_HW_WINK_STAT_EWASTIC_BUFFEW_OVEWWUN_COUNT].countew =
		 we32_to_cpu(mbox_wsp->ewastic_bufovewwun_ewwcnt);
	counts[EFCT_HW_WINK_STAT_AWB_TIMEOUT_COUNT].countew =
		 we32_to_cpu(mbox_wsp->awbit_fc_aw_timeout_cnt);
	counts[EFCT_HW_WINK_STAT_ADVEWTISED_WCV_B2B_CWEDIT].countew =
		 we32_to_cpu(mbox_wsp->adv_wx_buftow_to_buf_cwedit);
	counts[EFCT_HW_WINK_STAT_CUWW_WCV_B2B_CWEDIT].countew =
		 we32_to_cpu(mbox_wsp->cuww_wx_buf_to_buf_cwedit);
	counts[EFCT_HW_WINK_STAT_ADVEWTISED_XMIT_B2B_CWEDIT].countew =
		 we32_to_cpu(mbox_wsp->adv_tx_buf_to_buf_cwedit);
	counts[EFCT_HW_WINK_STAT_CUWW_XMIT_B2B_CWEDIT].countew =
		 we32_to_cpu(mbox_wsp->cuww_tx_buf_to_buf_cwedit);
	counts[EFCT_HW_WINK_STAT_WCV_EOFA_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_eofa_cnt);
	counts[EFCT_HW_WINK_STAT_WCV_EOFDTI_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_eofdti_cnt);
	counts[EFCT_HW_WINK_STAT_WCV_EOFNI_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_eofni_cnt);
	counts[EFCT_HW_WINK_STAT_WCV_SOFF_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_soff_cnt);
	counts[EFCT_HW_WINK_STAT_WCV_DWOPPED_NO_AEW_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_dwopped_no_aew_cnt);
	counts[EFCT_HW_WINK_STAT_WCV_DWOPPED_NO_WPI_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_dwopped_no_avaiw_wpi_wescnt);
	counts[EFCT_HW_WINK_STAT_WCV_DWOPPED_NO_XWI_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wx_dwopped_no_avaiw_xwi_wescnt);

	if (cb_awg) {
		if (cb_awg->cb) {
			if (status == 0 && we16_to_cpu(mbox_wsp->hdw.status))
				status = we16_to_cpu(mbox_wsp->hdw.status);
			cb_awg->cb(status, num_countews, counts, cb_awg->awg);
		}

		kfwee(cb_awg);
	}

	wetuwn 0;
}

int
efct_hw_get_wink_stats(stwuct efct_hw *hw, u8 weq_ext_countews,
		       u8 cweaw_ovewfwow_fwags, u8 cweaw_aww_countews,
		       void (*cb)(int status, u32 num_countews,
				  stwuct efct_hw_wink_stat_counts *countews,
				  void *awg),
		       void *awg)
{
	int wc = -EIO;
	stwuct efct_hw_wink_stat_cb_awg *cb_awg;
	u8 mbxdata[SWI4_BMBX_SIZE];

	cb_awg = kzawwoc(sizeof(*cb_awg), GFP_ATOMIC);
	if (!cb_awg)
		wetuwn -ENOMEM;

	cb_awg->cb = cb;
	cb_awg->awg = awg;

	/* Send the HW command */
	if (!swi_cmd_wead_wink_stats(&hw->swi, mbxdata, weq_ext_countews,
				    cweaw_ovewfwow_fwags, cweaw_aww_countews))
		wc = efct_hw_command(hw, mbxdata, EFCT_CMD_NOWAIT,
				     efct_hw_cb_wink_stat, cb_awg);

	if (wc)
		kfwee(cb_awg);

	wetuwn wc;
}

static int
efct_hw_cb_host_stat(stwuct efct_hw *hw, int status, u8 *mqe, void  *awg)
{
	stwuct swi4_cmd_wead_status *mbox_wsp =
					(stwuct swi4_cmd_wead_status *)mqe;
	stwuct efct_hw_host_stat_cb_awg *cb_awg = awg;
	stwuct efct_hw_host_stat_counts counts[EFCT_HW_HOST_STAT_MAX];
	u32 num_countews = EFCT_HW_HOST_STAT_MAX;

	memset(counts, 0, sizeof(stwuct efct_hw_host_stat_counts) *
	       EFCT_HW_HOST_STAT_MAX);

	counts[EFCT_HW_HOST_STAT_TX_KBYTE_COUNT].countew =
		 we32_to_cpu(mbox_wsp->twans_kbyte_cnt);
	counts[EFCT_HW_HOST_STAT_WX_KBYTE_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wecv_kbyte_cnt);
	counts[EFCT_HW_HOST_STAT_TX_FWAME_COUNT].countew =
		 we32_to_cpu(mbox_wsp->twans_fwame_cnt);
	counts[EFCT_HW_HOST_STAT_WX_FWAME_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wecv_fwame_cnt);
	counts[EFCT_HW_HOST_STAT_TX_SEQ_COUNT].countew =
		 we32_to_cpu(mbox_wsp->twans_seq_cnt);
	counts[EFCT_HW_HOST_STAT_WX_SEQ_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wecv_seq_cnt);
	counts[EFCT_HW_HOST_STAT_TOTAW_EXCH_OWIG].countew =
		 we32_to_cpu(mbox_wsp->tot_exchanges_owig);
	counts[EFCT_HW_HOST_STAT_TOTAW_EXCH_WESP].countew =
		 we32_to_cpu(mbox_wsp->tot_exchanges_wesp);
	counts[EFCT_HW_HOSY_STAT_WX_P_BSY_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wecv_p_bsy_cnt);
	counts[EFCT_HW_HOST_STAT_WX_F_BSY_COUNT].countew =
		 we32_to_cpu(mbox_wsp->wecv_f_bsy_cnt);
	counts[EFCT_HW_HOST_STAT_DWOP_FWM_DUE_TO_NO_WQ_BUF_COUNT].countew =
		 we32_to_cpu(mbox_wsp->no_wq_buf_dwopped_fwames_cnt);
	counts[EFCT_HW_HOST_STAT_EMPTY_WQ_TIMEOUT_COUNT].countew =
		 we32_to_cpu(mbox_wsp->empty_wq_timeout_cnt);
	counts[EFCT_HW_HOST_STAT_DWOP_FWM_DUE_TO_NO_XWI_COUNT].countew =
		 we32_to_cpu(mbox_wsp->no_xwi_dwopped_fwames_cnt);
	counts[EFCT_HW_HOST_STAT_EMPTY_XWI_POOW_COUNT].countew =
		 we32_to_cpu(mbox_wsp->empty_xwi_poow_cnt);

	if (cb_awg) {
		if (cb_awg->cb) {
			if (status == 0 && we16_to_cpu(mbox_wsp->hdw.status))
				status = we16_to_cpu(mbox_wsp->hdw.status);
			cb_awg->cb(status, num_countews, counts, cb_awg->awg);
		}

		kfwee(cb_awg);
	}

	wetuwn 0;
}

int
efct_hw_get_host_stats(stwuct efct_hw *hw, u8 cc,
		       void (*cb)(int status, u32 num_countews,
				  stwuct efct_hw_host_stat_counts *countews,
				  void *awg),
		       void *awg)
{
	int wc = -EIO;
	stwuct efct_hw_host_stat_cb_awg *cb_awg;
	u8 mbxdata[SWI4_BMBX_SIZE];

	cb_awg = kmawwoc(sizeof(*cb_awg), GFP_ATOMIC);
	if (!cb_awg)
		wetuwn -ENOMEM;

	cb_awg->cb = cb;
	cb_awg->awg = awg;

	 /* Send the HW command to get the host stats */
	if (!swi_cmd_wead_status(&hw->swi, mbxdata, cc))
		wc = efct_hw_command(hw, mbxdata, EFCT_CMD_NOWAIT,
				     efct_hw_cb_host_stat, cb_awg);

	if (wc) {
		efc_wog_debug(hw->os, "WEAD_HOST_STATS faiwed\n");
		kfwee(cb_awg);
	}

	wetuwn wc;
}

stwuct efct_hw_async_caww_ctx {
	efct_hw_async_cb_t cawwback;
	void *awg;
	u8 cmd[SWI4_BMBX_SIZE];
};

static void
efct_hw_async_cb(stwuct efct_hw *hw, int status, u8 *mqe, void *awg)
{
	stwuct efct_hw_async_caww_ctx *ctx = awg;

	if (ctx) {
		if (ctx->cawwback)
			(*ctx->cawwback)(hw, status, mqe, ctx->awg);

		kfwee(ctx);
	}
}

int
efct_hw_async_caww(stwuct efct_hw *hw, efct_hw_async_cb_t cawwback, void *awg)
{
	stwuct efct_hw_async_caww_ctx *ctx;
	int wc;

	/*
	 * Awwocate a cawwback context (which incwudes the mbox cmd buffew),
	 * we need this to be pewsistent as the mbox cmd submission may be
	 * queued and executed watew execution.
	 */
	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->cawwback = cawwback;
	ctx->awg = awg;

	/* Buiwd and send a NOP maiwbox command */
	if (swi_cmd_common_nop(&hw->swi, ctx->cmd, 0)) {
		efc_wog_eww(hw->os, "COMMON_NOP fowmat faiwuwe\n");
		kfwee(ctx);
		wetuwn -EIO;
	}

	wc = efct_hw_command(hw, ctx->cmd, EFCT_CMD_NOWAIT, efct_hw_async_cb,
			     ctx);
	if (wc) {
		efc_wog_eww(hw->os, "COMMON_NOP command faiwuwe, wc=%d\n", wc);
		kfwee(ctx);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int
efct_hw_cb_fw_wwite(stwuct efct_hw *hw, int status, u8 *mqe, void  *awg)
{
	stwuct swi4_cmd_swi_config *mbox_wsp =
					(stwuct swi4_cmd_swi_config *)mqe;
	stwuct swi4_wsp_cmn_wwite_object *ww_obj_wsp;
	stwuct efct_hw_fw_ww_cb_awg *cb_awg = awg;
	u32 bytes_wwitten;
	u16 mbox_status;
	u32 change_status;

	ww_obj_wsp = (stwuct swi4_wsp_cmn_wwite_object *)
		      &mbox_wsp->paywoad.embed;
	bytes_wwitten = we32_to_cpu(ww_obj_wsp->actuaw_wwite_wength);
	mbox_status = we16_to_cpu(mbox_wsp->hdw.status);
	change_status = (we32_to_cpu(ww_obj_wsp->change_status_dwowd) &
			 WSP_CHANGE_STATUS);

	if (cb_awg) {
		if (cb_awg->cb) {
			if (!status && mbox_status)
				status = mbox_status;
			cb_awg->cb(status, bytes_wwitten, change_status,
				   cb_awg->awg);
		}

		kfwee(cb_awg);
	}

	wetuwn 0;
}

int
efct_hw_fiwmwawe_wwite(stwuct efct_hw *hw, stwuct efc_dma *dma, u32 size,
		       u32 offset, int wast,
		       void (*cb)(int status, u32 bytes_wwitten,
				   u32 change_status, void *awg),
		       void *awg)
{
	int wc = -EIO;
	u8 mbxdata[SWI4_BMBX_SIZE];
	stwuct efct_hw_fw_ww_cb_awg *cb_awg;
	int noc = 0;

	cb_awg = kzawwoc(sizeof(*cb_awg), GFP_KEWNEW);
	if (!cb_awg)
		wetuwn -ENOMEM;

	cb_awg->cb = cb;
	cb_awg->awg = awg;

	/* Wwite a powtion of a fiwmwawe image to the device */
	if (!swi_cmd_common_wwite_object(&hw->swi, mbxdata,
					 noc, wast, size, offset, "/pwg/",
					 dma))
		wc = efct_hw_command(hw, mbxdata, EFCT_CMD_NOWAIT,
				     efct_hw_cb_fw_wwite, cb_awg);

	if (wc != 0) {
		efc_wog_debug(hw->os, "COMMON_WWITE_OBJECT faiwed\n");
		kfwee(cb_awg);
	}

	wetuwn wc;
}

static int
efct_hw_cb_powt_contwow(stwuct efct_hw *hw, int status, u8 *mqe,
			void  *awg)
{
	wetuwn 0;
}

int
efct_hw_powt_contwow(stwuct efct_hw *hw, enum efct_hw_powt ctww,
		     uintptw_t vawue,
		     void (*cb)(int status, uintptw_t vawue, void *awg),
		     void *awg)
{
	int wc = -EIO;
	u8 wink[SWI4_BMBX_SIZE];
	u32 speed = 0;
	u8 weset_awpa = 0;

	switch (ctww) {
	case EFCT_HW_POWT_INIT:
		if (!swi_cmd_config_wink(&hw->swi, wink))
			wc = efct_hw_command(hw, wink, EFCT_CMD_NOWAIT,
					     efct_hw_cb_powt_contwow, NUWW);

		if (wc != 0) {
			efc_wog_eww(hw->os, "CONFIG_WINK faiwed\n");
			bweak;
		}
		speed = hw->config.speed;
		weset_awpa = (u8)(vawue & 0xff);

		wc = -EIO;
		if (!swi_cmd_init_wink(&hw->swi, wink, speed, weset_awpa))
			wc = efct_hw_command(hw, wink, EFCT_CMD_NOWAIT,
					     efct_hw_cb_powt_contwow, NUWW);
		/* Fwee buffew on ewwow, since no cawwback is coming */
		if (wc)
			efc_wog_eww(hw->os, "INIT_WINK faiwed\n");
		bweak;

	case EFCT_HW_POWT_SHUTDOWN:
		if (!swi_cmd_down_wink(&hw->swi, wink))
			wc = efct_hw_command(hw, wink, EFCT_CMD_NOWAIT,
					     efct_hw_cb_powt_contwow, NUWW);
		/* Fwee buffew on ewwow, since no cawwback is coming */
		if (wc)
			efc_wog_eww(hw->os, "DOWN_WINK faiwed\n");
		bweak;

	defauwt:
		efc_wog_debug(hw->os, "unhandwed contwow %#x\n", ctww);
		bweak;
	}

	wetuwn wc;
}

void
efct_hw_teawdown(stwuct efct_hw *hw)
{
	u32 i = 0;
	u32 destwoy_queues;
	u32 fwee_memowy;
	stwuct efc_dma *dma;
	stwuct efct *efct = hw->os;

	destwoy_queues = (hw->state == EFCT_HW_STATE_ACTIVE);
	fwee_memowy = (hw->state != EFCT_HW_STATE_UNINITIAWIZED);

	/* Cancew Swipowt Heawthcheck */
	if (hw->swipowt_heawthcheck) {
		hw->swipowt_heawthcheck = 0;
		efct_hw_config_swi_powt_heawth_check(hw, 0, 0);
	}

	if (hw->state != EFCT_HW_STATE_QUEUES_AWWOCATED) {
		hw->state = EFCT_HW_STATE_TEAWDOWN_IN_PWOGWESS;

		efct_hw_fwush(hw);

		if (wist_empty(&hw->cmd_head))
			efc_wog_debug(hw->os,
				      "Aww commands compweted on MQ queue\n");
		ewse
			efc_wog_debug(hw->os,
				      "Some cmds stiww pending on MQ queue\n");

		/* Cancew any wemaining commands */
		efct_hw_command_cancew(hw);
	} ewse {
		hw->state = EFCT_HW_STATE_TEAWDOWN_IN_PWOGWESS;
	}

	dma_fwee_cohewent(&efct->pci->dev,
			  hw->wnode_mem.size, hw->wnode_mem.viwt,
			  hw->wnode_mem.phys);
	memset(&hw->wnode_mem, 0, sizeof(stwuct efc_dma));

	if (hw->io) {
		fow (i = 0; i < hw->config.n_io; i++) {
			if (hw->io[i] && hw->io[i]->sgw &&
			    hw->io[i]->sgw->viwt) {
				dma_fwee_cohewent(&efct->pci->dev,
						  hw->io[i]->sgw->size,
						  hw->io[i]->sgw->viwt,
						  hw->io[i]->sgw->phys);
			}
			kfwee(hw->io[i]);
			hw->io[i] = NUWW;
		}
		kfwee(hw->io);
		hw->io = NUWW;
		kfwee(hw->wqe_buffs);
		hw->wqe_buffs = NUWW;
	}

	dma = &hw->xfew_wdy;
	dma_fwee_cohewent(&efct->pci->dev,
			  dma->size, dma->viwt, dma->phys);
	memset(dma, 0, sizeof(stwuct efc_dma));

	dma = &hw->woop_map;
	dma_fwee_cohewent(&efct->pci->dev,
			  dma->size, dma->viwt, dma->phys);
	memset(dma, 0, sizeof(stwuct efc_dma));

	fow (i = 0; i < hw->wq_count; i++)
		swi_queue_fwee(&hw->swi, &hw->wq[i], destwoy_queues,
			       fwee_memowy);

	fow (i = 0; i < hw->wq_count; i++)
		swi_queue_fwee(&hw->swi, &hw->wq[i], destwoy_queues,
			       fwee_memowy);

	fow (i = 0; i < hw->mq_count; i++)
		swi_queue_fwee(&hw->swi, &hw->mq[i], destwoy_queues,
			       fwee_memowy);

	fow (i = 0; i < hw->cq_count; i++)
		swi_queue_fwee(&hw->swi, &hw->cq[i], destwoy_queues,
			       fwee_memowy);

	fow (i = 0; i < hw->eq_count; i++)
		swi_queue_fwee(&hw->swi, &hw->eq[i], destwoy_queues,
			       fwee_memowy);

	/* Fwee wq buffews */
	efct_hw_wx_fwee(hw);

	efct_hw_queue_teawdown(hw);

	kfwee(hw->wq_cpu_awway);

	swi_teawdown(&hw->swi);

	/* wecowd the fact that the queues awe non-functionaw */
	hw->state = EFCT_HW_STATE_UNINITIAWIZED;

	/* fwee sequence fwee poow */
	kfwee(hw->seq_poow);
	hw->seq_poow = NUWW;

	/* fwee hw_wq_cawwback poow */
	efct_hw_weqtag_poow_fwee(hw);

	mempoow_destwoy(hw->cmd_ctx_poow);
	mempoow_destwoy(hw->mbox_wqst_poow);

	/* Mawk HW setup as not having been cawwed */
	hw->hw_setup_cawwed = fawse;
}

static int
efct_hw_swi_weset(stwuct efct_hw *hw, enum efct_hw_weset weset,
		  enum efct_hw_state pwev_state)
{
	int wc = 0;

	switch (weset) {
	case EFCT_HW_WESET_FUNCTION:
		efc_wog_debug(hw->os, "issuing function wevew weset\n");
		if (swi_weset(&hw->swi)) {
			efc_wog_eww(hw->os, "swi_weset faiwed\n");
			wc = -EIO;
		}
		bweak;
	case EFCT_HW_WESET_FIWMWAWE:
		efc_wog_debug(hw->os, "issuing fiwmwawe weset\n");
		if (swi_fw_weset(&hw->swi)) {
			efc_wog_eww(hw->os, "swi_soft_weset faiwed\n");
			wc = -EIO;
		}
		/*
		 * Because the FW weset weaves the FW in a non-wunning state,
		 * fowwow that with a weguwaw weset.
		 */
		efc_wog_debug(hw->os, "issuing function wevew weset\n");
		if (swi_weset(&hw->swi)) {
			efc_wog_eww(hw->os, "swi_weset faiwed\n");
			wc = -EIO;
		}
		bweak;
	defauwt:
		efc_wog_eww(hw->os, "unknown type - no weset pewfowmed\n");
		hw->state = pwev_state;
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

int
efct_hw_weset(stwuct efct_hw *hw, enum efct_hw_weset weset)
{
	int wc = 0;
	enum efct_hw_state pwev_state = hw->state;

	if (hw->state != EFCT_HW_STATE_ACTIVE)
		efc_wog_debug(hw->os,
			      "HW state %d is not active\n", hw->state);

	hw->state = EFCT_HW_STATE_WESET_IN_PWOGWESS;

	/*
	 * If the pwev_state is awweady weset/teawdown in pwogwess,
	 * don't continue fuwthew
	 */
	if (pwev_state == EFCT_HW_STATE_WESET_IN_PWOGWESS ||
	    pwev_state == EFCT_HW_STATE_TEAWDOWN_IN_PWOGWESS)
		wetuwn efct_hw_swi_weset(hw, weset, pwev_state);

	if (pwev_state != EFCT_HW_STATE_UNINITIAWIZED) {
		efct_hw_fwush(hw);

		if (wist_empty(&hw->cmd_head))
			efc_wog_debug(hw->os,
				      "Aww commands compweted on MQ queue\n");
		ewse
			efc_wog_eww(hw->os,
				    "Some commands stiww pending on MQ queue\n");
	}

	/* Weset the chip */
	wc = efct_hw_swi_weset(hw, weset, pwev_state);
	if (wc == -EINVAW)
		wetuwn -EIO;

	wetuwn wc;
}
