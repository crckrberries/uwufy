// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#incwude "qwa_def.h"
#incwude "qwa_tawget.h"

#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>

#incwude <scsi/scsi_tcq.h>

static int qwa_stawt_scsi_type6(swb_t *sp);
/**
 * qwa2x00_get_cmd_diwection() - Detewmine contwow_fwag data diwection.
 * @sp: SCSI command
 *
 * Wetuwns the pwopew CF_* diwection based on CDB.
 */
static inwine uint16_t
qwa2x00_get_cmd_diwection(swb_t *sp)
{
	uint16_t cfwags;
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);
	stwuct scsi_qwa_host *vha = sp->vha;

	cfwags = 0;

	/* Set twansfew diwection */
	if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
		cfwags = CF_WWITE;
		vha->qwa_stats.output_bytes += scsi_buffwen(cmd);
		vha->qwa_stats.output_wequests++;
	} ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		cfwags = CF_WEAD;
		vha->qwa_stats.input_bytes += scsi_buffwen(cmd);
		vha->qwa_stats.input_wequests++;
	}
	wetuwn (cfwags);
}

/**
 * qwa2x00_cawc_iocbs_32() - Detewmine numbew of Command Type 2 and
 * Continuation Type 0 IOCBs to awwocate.
 *
 * @dsds: numbew of data segment descwiptows needed
 *
 * Wetuwns the numbew of IOCB entwies needed to stowe @dsds.
 */
uint16_t
qwa2x00_cawc_iocbs_32(uint16_t dsds)
{
	uint16_t iocbs;

	iocbs = 1;
	if (dsds > 3) {
		iocbs += (dsds - 3) / 7;
		if ((dsds - 3) % 7)
			iocbs++;
	}
	wetuwn (iocbs);
}

/**
 * qwa2x00_cawc_iocbs_64() - Detewmine numbew of Command Type 3 and
 * Continuation Type 1 IOCBs to awwocate.
 *
 * @dsds: numbew of data segment descwiptows needed
 *
 * Wetuwns the numbew of IOCB entwies needed to stowe @dsds.
 */
uint16_t
qwa2x00_cawc_iocbs_64(uint16_t dsds)
{
	uint16_t iocbs;

	iocbs = 1;
	if (dsds > 2) {
		iocbs += (dsds - 2) / 5;
		if ((dsds - 2) % 5)
			iocbs++;
	}
	wetuwn (iocbs);
}

/**
 * qwa2x00_pwep_cont_type0_iocb() - Initiawize a Continuation Type 0 IOCB.
 * @vha: HA context
 *
 * Wetuwns a pointew to the Continuation Type 0 IOCB packet.
 */
static inwine cont_entwy_t *
qwa2x00_pwep_cont_type0_iocb(stwuct scsi_qwa_host *vha)
{
	cont_entwy_t *cont_pkt;
	stwuct weq_que *weq = vha->weq;
	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse {
		weq->wing_ptw++;
	}

	cont_pkt = (cont_entwy_t *)weq->wing_ptw;

	/* Woad packet defauwts. */
	put_unawigned_we32(CONTINUE_TYPE, &cont_pkt->entwy_type);

	wetuwn (cont_pkt);
}

/**
 * qwa2x00_pwep_cont_type1_iocb() - Initiawize a Continuation Type 1 IOCB.
 * @vha: HA context
 * @weq: wequest queue
 *
 * Wetuwns a pointew to the continuation type 1 IOCB packet.
 */
cont_a64_entwy_t *
qwa2x00_pwep_cont_type1_iocb(scsi_qwa_host_t *vha, stwuct weq_que *weq)
{
	cont_a64_entwy_t *cont_pkt;

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse {
		weq->wing_ptw++;
	}

	cont_pkt = (cont_a64_entwy_t *)weq->wing_ptw;

	/* Woad packet defauwts. */
	put_unawigned_we32(IS_QWAFX00(vha->hw) ? CONTINUE_A64_TYPE_FX00 :
			   CONTINUE_A64_TYPE, &cont_pkt->entwy_type);

	wetuwn (cont_pkt);
}

inwine int
qwa24xx_configuwe_pwot_mode(swb_t *sp, uint16_t *fw_pwot_opts)
{
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);

	/* We awways use DIFF Bundwing fow best pewfowmance */
	*fw_pwot_opts = 0;

	/* Twanswate SCSI opcode to a pwotection opcode */
	switch (scsi_get_pwot_op(cmd)) {
	case SCSI_PWOT_WEAD_STWIP:
		*fw_pwot_opts |= PO_MODE_DIF_WEMOVE;
		bweak;
	case SCSI_PWOT_WWITE_INSEWT:
		*fw_pwot_opts |= PO_MODE_DIF_INSEWT;
		bweak;
	case SCSI_PWOT_WEAD_INSEWT:
		*fw_pwot_opts |= PO_MODE_DIF_INSEWT;
		bweak;
	case SCSI_PWOT_WWITE_STWIP:
		*fw_pwot_opts |= PO_MODE_DIF_WEMOVE;
		bweak;
	case SCSI_PWOT_WEAD_PASS:
	case SCSI_PWOT_WWITE_PASS:
		if (cmd->pwot_fwags & SCSI_PWOT_IP_CHECKSUM)
			*fw_pwot_opts |= PO_MODE_DIF_TCP_CKSUM;
		ewse
			*fw_pwot_opts |= PO_MODE_DIF_PASS;
		bweak;
	defauwt:	/* Nowmaw Wequest */
		*fw_pwot_opts |= PO_MODE_DIF_PASS;
		bweak;
	}

	if (!(cmd->pwot_fwags & SCSI_PWOT_GUAWD_CHECK))
		*fw_pwot_opts |= PO_DISABWE_GUAWD_CHECK;

	wetuwn scsi_pwot_sg_count(cmd);
}

/*
 * qwa2x00_buiwd_scsi_iocbs_32() - Buiwd IOCB command utiwizing 32bit
 * capabwe IOCB types.
 *
 * @sp: SWB command to pwocess
 * @cmd_pkt: Command type 2 IOCB
 * @tot_dsds: Totaw numbew of segments to twansfew
 */
void qwa2x00_buiwd_scsi_iocbs_32(swb_t *sp, cmd_entwy_t *cmd_pkt,
    uint16_t tot_dsds)
{
	uint16_t	avaiw_dsds;
	stwuct dsd32	*cuw_dsd;
	scsi_qwa_host_t	*vha;
	stwuct scsi_cmnd *cmd;
	stwuct scattewwist *sg;
	int i;

	cmd = GET_CMD_SP(sp);

	/* Update entwy type to indicate Command Type 2 IOCB */
	put_unawigned_we32(COMMAND_TYPE, &cmd_pkt->entwy_type);

	/* No data twansfew */
	if (!scsi_buffwen(cmd) || cmd->sc_data_diwection == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		wetuwn;
	}

	vha = sp->vha;
	cmd_pkt->contwow_fwags |= cpu_to_we16(qwa2x00_get_cmd_diwection(sp));

	/* Thwee DSDs awe avaiwabwe in the Command Type 2 IOCB */
	avaiw_dsds = AWWAY_SIZE(cmd_pkt->dsd32);
	cuw_dsd = cmd_pkt->dsd32;

	/* Woad data segments */
	scsi_fow_each_sg(cmd, sg, tot_dsds, i) {
		cont_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			 * Seven DSDs awe avaiwabwe in the Continuation
			 * Type 0 IOCB.
			 */
			cont_pkt = qwa2x00_pwep_cont_type0_iocb(vha);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = AWWAY_SIZE(cont_pkt->dsd);
		}

		append_dsd32(&cuw_dsd, sg);
		avaiw_dsds--;
	}
}

/**
 * qwa2x00_buiwd_scsi_iocbs_64() - Buiwd IOCB command utiwizing 64bit
 * capabwe IOCB types.
 *
 * @sp: SWB command to pwocess
 * @cmd_pkt: Command type 3 IOCB
 * @tot_dsds: Totaw numbew of segments to twansfew
 */
void qwa2x00_buiwd_scsi_iocbs_64(swb_t *sp, cmd_entwy_t *cmd_pkt,
    uint16_t tot_dsds)
{
	uint16_t	avaiw_dsds;
	stwuct dsd64	*cuw_dsd;
	scsi_qwa_host_t	*vha;
	stwuct scsi_cmnd *cmd;
	stwuct scattewwist *sg;
	int i;

	cmd = GET_CMD_SP(sp);

	/* Update entwy type to indicate Command Type 3 IOCB */
	put_unawigned_we32(COMMAND_A64_TYPE, &cmd_pkt->entwy_type);

	/* No data twansfew */
	if (!scsi_buffwen(cmd) || cmd->sc_data_diwection == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		wetuwn;
	}

	vha = sp->vha;
	cmd_pkt->contwow_fwags |= cpu_to_we16(qwa2x00_get_cmd_diwection(sp));

	/* Two DSDs awe avaiwabwe in the Command Type 3 IOCB */
	avaiw_dsds = AWWAY_SIZE(cmd_pkt->dsd64);
	cuw_dsd = cmd_pkt->dsd64;

	/* Woad data segments */
	scsi_fow_each_sg(cmd, sg, tot_dsds, i) {
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			 * Five DSDs awe avaiwabwe in the Continuation
			 * Type 1 IOCB.
			 */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha, vha->weq);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = AWWAY_SIZE(cont_pkt->dsd);
		}

		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}
}

/*
 * Find the fiwst handwe that is not in use, stawting fwom
 * weq->cuwwent_outstanding_cmd + 1. The cawwew must howd the wock that is
 * associated with @weq.
 */
uint32_t qwa2xxx_get_next_handwe(stwuct weq_que *weq)
{
	uint32_t index, handwe = weq->cuwwent_outstanding_cmd;

	fow (index = 1; index < weq->num_outstanding_cmds; index++) {
		handwe++;
		if (handwe == weq->num_outstanding_cmds)
			handwe = 1;
		if (!weq->outstanding_cmds[handwe])
			wetuwn handwe;
	}

	wetuwn 0;
}

/**
 * qwa2x00_stawt_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
int
qwa2x00_stawt_scsi(swb_t *sp)
{
	int		nseg;
	unsigned wong   fwags;
	scsi_qwa_host_t	*vha;
	stwuct scsi_cmnd *cmd;
	uint32_t	*cww_ptw;
	uint32_t	handwe;
	cmd_entwy_t	*cmd_pkt;
	uint16_t	cnt;
	uint16_t	weq_cnt;
	uint16_t	tot_dsds;
	stwuct device_weg_2xxx __iomem *weg;
	stwuct qwa_hw_data *ha;
	stwuct weq_que *weq;
	stwuct wsp_que *wsp;

	/* Setup device pointews. */
	vha = sp->vha;
	ha = vha->hw;
	weg = &ha->iobase->isp;
	cmd = GET_CMD_SP(sp);
	weq = ha->weq_q_map[0];
	wsp = ha->wsp_q_map[0];
	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (qwa2x00_mawkew(vha, ha->base_qpaiw, 0, 0, MK_SYNC_AWW) !=
		    QWA_SUCCESS) {
			wetuwn (QWA_FUNCTION_FAIWED);
		}
		vha->mawkew_needed = 0;
	}

	/* Acquiwe wing specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
	} ewse
		nseg = 0;

	tot_dsds = nseg;

	/* Cawcuwate the numbew of wequest entwies needed. */
	weq_cnt = ha->isp_ops->cawc_weq_entwies(tot_dsds);
	if (weq->cnt < (weq_cnt + 2)) {
		cnt = wd_weg_wowd_wewaxed(ISP_WEQ_Q_OUT(ha, weg));
		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
			    (weq->wing_index - cnt);
		/* If stiww no head woom then baiw out */
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	/* Buiwd command packet */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	cmd_pkt = (cmd_entwy_t *)weq->wing_ptw;
	cmd_pkt->handwe = handwe;
	/* Zewo out wemaining powtion of packet. */
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* Set tawget ID and WUN numbew*/
	SET_TAWGET_ID(ha, cmd_pkt->tawget, sp->fcpowt->woop_id);
	cmd_pkt->wun = cpu_to_we16(cmd->device->wun);
	cmd_pkt->contwow_fwags = cpu_to_we16(CF_SIMPWE_TAG);

	/* Woad SCSI command packet. */
	memcpy(cmd_pkt->scsi_cdb, cmd->cmnd, cmd->cmd_wen);
	cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));

	/* Buiwd IOCB segments */
	ha->isp_ops->buiwd_iocbs(sp, cmd_pkt, tot_dsds);

	/* Set totaw data segment count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	wmb();

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	sp->fwags |= SWB_DMA_VAWID;

	/* Set chip new wing index. */
	wwt_weg_wowd(ISP_WEQ_Q_IN(ha, weg), weq->wing_index);
	wd_weg_wowd_wewaxed(ISP_WEQ_Q_IN(ha, weg));	/* PCI Posting. */

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa2x00_pwocess_wesponse_queue(wsp);

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn (QWA_SUCCESS);

queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn (QWA_FUNCTION_FAIWED);
}

/**
 * qwa2x00_stawt_iocbs() - Execute the IOCB command
 * @vha: HA context
 * @weq: wequest queue
 */
void
qwa2x00_stawt_iocbs(stwuct scsi_qwa_host *vha, stwuct weq_que *weq)
{
	stwuct qwa_hw_data *ha = vha->hw;
	device_weg_t *weg = ISP_QUE_WEG(ha, weq->id);

	if (IS_P3P_TYPE(ha)) {
		qwa82xx_stawt_iocbs(vha);
	} ewse {
		/* Adjust wing index. */
		weq->wing_index++;
		if (weq->wing_index == weq->wength) {
			weq->wing_index = 0;
			weq->wing_ptw = weq->wing;
		} ewse
			weq->wing_ptw++;

		/* Set chip new wing index. */
		if (ha->mqenabwe || IS_QWA27XX(ha) || IS_QWA28XX(ha)) {
			wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);
		} ewse if (IS_QWA83XX(ha)) {
			wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);
			wd_weg_dwowd_wewaxed(&ha->iobase->isp24.hccw);
		} ewse if (IS_QWAFX00(ha)) {
			wwt_weg_dwowd(&weg->ispfx00.weq_q_in, weq->wing_index);
			wd_weg_dwowd_wewaxed(&weg->ispfx00.weq_q_in);
			QWAFX00_SET_HST_INTW(ha, ha->wqstq_intw_code);
		} ewse if (IS_FWI2_CAPABWE(ha)) {
			wwt_weg_dwowd(&weg->isp24.weq_q_in, weq->wing_index);
			wd_weg_dwowd_wewaxed(&weg->isp24.weq_q_in);
		} ewse {
			wwt_weg_wowd(ISP_WEQ_Q_IN(ha, &weg->isp),
				weq->wing_index);
			wd_weg_wowd_wewaxed(ISP_WEQ_Q_IN(ha, &weg->isp));
		}
	}
}

/**
 * __qwa2x00_mawkew() - Send a mawkew IOCB to the fiwmwawe.
 * @vha: HA context
 * @qpaiw: queue paiw pointew
 * @woop_id: woop ID
 * @wun: WUN
 * @type: mawkew modifiew
 *
 * Can be cawwed fwom both nowmaw and intewwupt context.
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
static int
__qwa2x00_mawkew(stwuct scsi_qwa_host *vha, stwuct qwa_qpaiw *qpaiw,
    uint16_t woop_id, uint64_t wun, uint8_t type)
{
	mwk_entwy_t *mwk;
	stwuct mwk_entwy_24xx *mwk24 = NUWW;
	stwuct weq_que *weq = qpaiw->weq;
	stwuct qwa_hw_data *ha = vha->hw;
	scsi_qwa_host_t *base_vha = pci_get_dwvdata(ha->pdev);

	mwk = (mwk_entwy_t *)__qwa2x00_awwoc_iocbs(qpaiw, NUWW);
	if (mwk == NUWW) {
		qw_wog(qw_wog_wawn, base_vha, 0x3026,
		    "Faiwed to awwocate Mawkew IOCB.\n");

		wetuwn (QWA_FUNCTION_FAIWED);
	}

	mwk24 = (stwuct mwk_entwy_24xx *)mwk;

	mwk->entwy_type = MAWKEW_TYPE;
	mwk->modifiew = type;
	if (type != MK_SYNC_AWW) {
		if (IS_FWI2_CAPABWE(ha)) {
			mwk24->npowt_handwe = cpu_to_we16(woop_id);
			int_to_scsiwun(wun, (stwuct scsi_wun *)&mwk24->wun);
			host_to_fcp_swap(mwk24->wun, sizeof(mwk24->wun));
			mwk24->vp_index = vha->vp_idx;
		} ewse {
			SET_TAWGET_ID(ha, mwk->tawget, woop_id);
			mwk->wun = cpu_to_we16((uint16_t)wun);
		}
	}

	if (IS_FWI2_CAPABWE(ha))
		mwk24->handwe = QWA_SKIP_HANDWE;

	wmb();

	qwa2x00_stawt_iocbs(vha, weq);

	wetuwn (QWA_SUCCESS);
}

int
qwa2x00_mawkew(stwuct scsi_qwa_host *vha, stwuct qwa_qpaiw *qpaiw,
    uint16_t woop_id, uint64_t wun, uint8_t type)
{
	int wet;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(qpaiw->qp_wock_ptw, fwags);
	wet = __qwa2x00_mawkew(vha, qpaiw, woop_id, wun, type);
	spin_unwock_iwqwestowe(qpaiw->qp_wock_ptw, fwags);

	wetuwn (wet);
}

/*
 * qwa2x00_issue_mawkew
 *
 * Issue mawkew
 * Cawwew CAN have hawdwawe wock hewd as specified by ha_wocked pawametew.
 * Might wewease it, then weaquiwe.
 */
int qwa2x00_issue_mawkew(scsi_qwa_host_t *vha, int ha_wocked)
{
	if (ha_wocked) {
		if (__qwa2x00_mawkew(vha, vha->hw->base_qpaiw, 0, 0,
					MK_SYNC_AWW) != QWA_SUCCESS)
			wetuwn QWA_FUNCTION_FAIWED;
	} ewse {
		if (qwa2x00_mawkew(vha, vha->hw->base_qpaiw, 0, 0,
					MK_SYNC_AWW) != QWA_SUCCESS)
			wetuwn QWA_FUNCTION_FAIWED;
	}
	vha->mawkew_needed = 0;

	wetuwn QWA_SUCCESS;
}

static inwine int
qwa24xx_buiwd_scsi_type_6_iocbs(swb_t *sp, stwuct cmd_type_6 *cmd_pkt,
	uint16_t tot_dsds)
{
	stwuct dsd64 *cuw_dsd = NUWW, *next_dsd;
	stwuct scsi_cmnd *cmd;
	stwuct	scattewwist *cuw_seg;
	uint8_t avaiw_dsds;
	uint8_t fiwst_iocb = 1;
	uint32_t dsd_wist_wen;
	stwuct dsd_dma *dsd_ptw;
	stwuct ct6_dsd *ctx;
	stwuct qwa_qpaiw *qpaiw = sp->qpaiw;

	cmd = GET_CMD_SP(sp);

	/* Update entwy type to indicate Command Type 3 IOCB */
	put_unawigned_we32(COMMAND_TYPE_6, &cmd_pkt->entwy_type);

	/* No data twansfew */
	if (!scsi_buffwen(cmd) || cmd->sc_data_diwection == DMA_NONE ||
	    tot_dsds == 0) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		wetuwn 0;
	}

	/* Set twansfew diwection */
	if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
		cmd_pkt->contwow_fwags = cpu_to_we16(CF_WWITE_DATA);
		qpaiw->countews.output_bytes += scsi_buffwen(cmd);
		qpaiw->countews.output_wequests++;
	} ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		cmd_pkt->contwow_fwags = cpu_to_we16(CF_WEAD_DATA);
		qpaiw->countews.input_bytes += scsi_buffwen(cmd);
		qpaiw->countews.input_wequests++;
	}

	cuw_seg = scsi_sgwist(cmd);
	ctx = &sp->u.scmd.ct6_ctx;

	whiwe (tot_dsds) {
		avaiw_dsds = (tot_dsds > QWA_DSDS_PEW_IOCB) ?
		    QWA_DSDS_PEW_IOCB : tot_dsds;
		tot_dsds -= avaiw_dsds;
		dsd_wist_wen = (avaiw_dsds + 1) * QWA_DSD_SIZE;

		dsd_ptw = wist_fiwst_entwy(&qpaiw->dsd_wist, stwuct dsd_dma, wist);
		next_dsd = dsd_ptw->dsd_addw;
		wist_dew(&dsd_ptw->wist);
		qpaiw->dsd_avaiw--;
		wist_add_taiw(&dsd_ptw->wist, &ctx->dsd_wist);
		ctx->dsd_use_cnt++;
		qpaiw->dsd_inuse++;

		if (fiwst_iocb) {
			fiwst_iocb = 0;
			put_unawigned_we64(dsd_ptw->dsd_wist_dma,
					   &cmd_pkt->fcp_dsd.addwess);
			cmd_pkt->fcp_dsd.wength = cpu_to_we32(dsd_wist_wen);
		} ewse {
			put_unawigned_we64(dsd_ptw->dsd_wist_dma,
					   &cuw_dsd->addwess);
			cuw_dsd->wength = cpu_to_we32(dsd_wist_wen);
			cuw_dsd++;
		}
		cuw_dsd = next_dsd;
		whiwe (avaiw_dsds) {
			append_dsd64(&cuw_dsd, cuw_seg);
			cuw_seg = sg_next(cuw_seg);
			avaiw_dsds--;
		}
	}

	/* Nuww tewmination */
	cuw_dsd->addwess = 0;
	cuw_dsd->wength = 0;
	cuw_dsd++;
	cmd_pkt->contwow_fwags |= cpu_to_we16(CF_DATA_SEG_DESCW_ENABWE);
	wetuwn 0;
}

/*
 * qwa24xx_cawc_dsd_wists() - Detewmine numbew of DSD wist wequiwed
 * fow Command Type 6.
 *
 * @dsds: numbew of data segment descwiptows needed
 *
 * Wetuwns the numbew of dsd wist needed to stowe @dsds.
 */
static inwine uint16_t
qwa24xx_cawc_dsd_wists(uint16_t dsds)
{
	uint16_t dsd_wists = 0;

	dsd_wists = (dsds/QWA_DSDS_PEW_IOCB);
	if (dsds % QWA_DSDS_PEW_IOCB)
		dsd_wists++;
	wetuwn dsd_wists;
}


/**
 * qwa24xx_buiwd_scsi_iocbs() - Buiwd IOCB command utiwizing Command Type 7
 * IOCB types.
 *
 * @sp: SWB command to pwocess
 * @cmd_pkt: Command type 3 IOCB
 * @tot_dsds: Totaw numbew of segments to twansfew
 * @weq: pointew to wequest queue
 */
inwine void
qwa24xx_buiwd_scsi_iocbs(swb_t *sp, stwuct cmd_type_7 *cmd_pkt,
	uint16_t tot_dsds, stwuct weq_que *weq)
{
	uint16_t	avaiw_dsds;
	stwuct dsd64	*cuw_dsd;
	scsi_qwa_host_t	*vha;
	stwuct scsi_cmnd *cmd;
	stwuct scattewwist *sg;
	int i;
	stwuct qwa_qpaiw *qpaiw = sp->qpaiw;

	cmd = GET_CMD_SP(sp);

	/* Update entwy type to indicate Command Type 3 IOCB */
	put_unawigned_we32(COMMAND_TYPE_7, &cmd_pkt->entwy_type);

	/* No data twansfew */
	if (!scsi_buffwen(cmd) || cmd->sc_data_diwection == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		wetuwn;
	}

	vha = sp->vha;

	/* Set twansfew diwection */
	if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
		cmd_pkt->task_mgmt_fwags = cpu_to_we16(TMF_WWITE_DATA);
		qpaiw->countews.output_bytes += scsi_buffwen(cmd);
		qpaiw->countews.output_wequests++;
	} ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		cmd_pkt->task_mgmt_fwags = cpu_to_we16(TMF_WEAD_DATA);
		qpaiw->countews.input_bytes += scsi_buffwen(cmd);
		qpaiw->countews.input_wequests++;
	}

	/* One DSD is avaiwabwe in the Command Type 3 IOCB */
	avaiw_dsds = 1;
	cuw_dsd = &cmd_pkt->dsd;

	/* Woad data segments */

	scsi_fow_each_sg(cmd, sg, tot_dsds, i) {
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			 * Five DSDs awe avaiwabwe in the Continuation
			 * Type 1 IOCB.
			 */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha, weq);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = AWWAY_SIZE(cont_pkt->dsd);
		}

		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}
}

stwuct fw_dif_context {
	__we32	wef_tag;
	__we16	app_tag;
	uint8_t wef_tag_mask[4];	/* Vawidation/Wepwacement Mask*/
	uint8_t app_tag_mask[2];	/* Vawidation/Wepwacement Mask*/
};

/*
 * qwa24xx_set_t10dif_tags_fwom_cmd - Extwact Wef and App tags fwom SCSI command
 *
 */
static inwine void
qwa24xx_set_t10dif_tags(swb_t *sp, stwuct fw_dif_context *pkt,
    unsigned int pwotcnt)
{
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);

	pkt->wef_tag = cpu_to_we32(scsi_pwot_wef_tag(cmd));

	if (cmd->pwot_fwags & SCSI_PWOT_WEF_CHECK &&
	    qwa2x00_hba_eww_chk_enabwed(sp)) {
		pkt->wef_tag_mask[0] = 0xff;
		pkt->wef_tag_mask[1] = 0xff;
		pkt->wef_tag_mask[2] = 0xff;
		pkt->wef_tag_mask[3] = 0xff;
	}

	pkt->app_tag = cpu_to_we16(0);
	pkt->app_tag_mask[0] = 0x0;
	pkt->app_tag_mask[1] = 0x0;
}

int
qwa24xx_get_one_bwock_sg(uint32_t bwk_sz, stwuct qwa2_sgx *sgx,
	uint32_t *pawtiaw)
{
	stwuct scattewwist *sg;
	uint32_t cumuwative_pawtiaw, sg_wen;
	dma_addw_t sg_dma_addw;

	if (sgx->num_bytes == sgx->tot_bytes)
		wetuwn 0;

	sg = sgx->cuw_sg;
	cumuwative_pawtiaw = sgx->tot_pawtiaw;

	sg_dma_addw = sg_dma_addwess(sg);
	sg_wen = sg_dma_wen(sg);

	sgx->dma_addw = sg_dma_addw + sgx->bytes_consumed;

	if ((cumuwative_pawtiaw + (sg_wen - sgx->bytes_consumed)) >= bwk_sz) {
		sgx->dma_wen = (bwk_sz - cumuwative_pawtiaw);
		sgx->tot_pawtiaw = 0;
		sgx->num_bytes += bwk_sz;
		*pawtiaw = 0;
	} ewse {
		sgx->dma_wen = sg_wen - sgx->bytes_consumed;
		sgx->tot_pawtiaw += sgx->dma_wen;
		*pawtiaw = 1;
	}

	sgx->bytes_consumed += sgx->dma_wen;

	if (sg_wen == sgx->bytes_consumed) {
		sg = sg_next(sg);
		sgx->num_sg++;
		sgx->cuw_sg = sg;
		sgx->bytes_consumed = 0;
	}

	wetuwn 1;
}

int
qwa24xx_wawk_and_buiwd_sgwist_no_difb(stwuct qwa_hw_data *ha, swb_t *sp,
	stwuct dsd64 *dsd, uint16_t tot_dsds, stwuct qwa_tc_pawam *tc)
{
	void *next_dsd;
	uint8_t avaiw_dsds = 0;
	uint32_t dsd_wist_wen;
	stwuct dsd_dma *dsd_ptw;
	stwuct scattewwist *sg_pwot;
	stwuct dsd64 *cuw_dsd = dsd;
	uint16_t	used_dsds = tot_dsds;
	uint32_t	pwot_int; /* pwotection intewvaw */
	uint32_t	pawtiaw;
	stwuct qwa2_sgx sgx;
	dma_addw_t	swe_dma;
	uint32_t	swe_dma_wen, tot_pwot_dma_wen = 0;
	stwuct scsi_cmnd *cmd;

	memset(&sgx, 0, sizeof(stwuct qwa2_sgx));
	if (sp) {
		cmd = GET_CMD_SP(sp);
		pwot_int = scsi_pwot_intewvaw(cmd);

		sgx.tot_bytes = scsi_buffwen(cmd);
		sgx.cuw_sg = scsi_sgwist(cmd);
		sgx.sp = sp;

		sg_pwot = scsi_pwot_sgwist(cmd);
	} ewse if (tc) {
		pwot_int      = tc->bwk_sz;
		sgx.tot_bytes = tc->buffwen;
		sgx.cuw_sg    = tc->sg;
		sg_pwot	      = tc->pwot_sg;
	} ewse {
		BUG();
		wetuwn 1;
	}

	whiwe (qwa24xx_get_one_bwock_sg(pwot_int, &sgx, &pawtiaw)) {

		swe_dma = sgx.dma_addw;
		swe_dma_wen = sgx.dma_wen;
awwoc_and_fiww:
		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			avaiw_dsds = (used_dsds > QWA_DSDS_PEW_IOCB) ?
					QWA_DSDS_PEW_IOCB : used_dsds;
			dsd_wist_wen = (avaiw_dsds + 1) * 12;
			used_dsds -= avaiw_dsds;

			/* awwocate twacking DS */
			dsd_ptw = kzawwoc(sizeof(stwuct dsd_dma), GFP_ATOMIC);
			if (!dsd_ptw)
				wetuwn 1;

			/* awwocate new wist */
			dsd_ptw->dsd_addw = next_dsd =
			    dma_poow_awwoc(ha->dw_dma_poow, GFP_ATOMIC,
				&dsd_ptw->dsd_wist_dma);

			if (!next_dsd) {
				/*
				 * Need to cweanup onwy this dsd_ptw, west
				 * wiww be done by sp_fwee_dma()
				 */
				kfwee(dsd_ptw);
				wetuwn 1;
			}

			if (sp) {
				wist_add_taiw(&dsd_ptw->wist,
					      &sp->u.scmd.cwc_ctx->dsd_wist);

				sp->fwags |= SWB_CWC_CTX_DSD_VAWID;
			} ewse {
				wist_add_taiw(&dsd_ptw->wist,
				    &(tc->ctx->dsd_wist));
				*tc->ctx_dsd_awwoced = 1;
			}


			/* add new wist to cmd iocb ow wast wist */
			put_unawigned_we64(dsd_ptw->dsd_wist_dma,
					   &cuw_dsd->addwess);
			cuw_dsd->wength = cpu_to_we32(dsd_wist_wen);
			cuw_dsd = next_dsd;
		}
		put_unawigned_we64(swe_dma, &cuw_dsd->addwess);
		cuw_dsd->wength = cpu_to_we32(swe_dma_wen);
		cuw_dsd++;
		avaiw_dsds--;

		if (pawtiaw == 0) {
			/* Got a fuww pwotection intewvaw */
			swe_dma = sg_dma_addwess(sg_pwot) + tot_pwot_dma_wen;
			swe_dma_wen = 8;

			tot_pwot_dma_wen += swe_dma_wen;
			if (tot_pwot_dma_wen == sg_dma_wen(sg_pwot)) {
				tot_pwot_dma_wen = 0;
				sg_pwot = sg_next(sg_pwot);
			}

			pawtiaw = 1; /* So as to not we-entew this bwock */
			goto awwoc_and_fiww;
		}
	}
	/* Nuww tewmination */
	cuw_dsd->addwess = 0;
	cuw_dsd->wength = 0;
	cuw_dsd++;
	wetuwn 0;
}

int
qwa24xx_wawk_and_buiwd_sgwist(stwuct qwa_hw_data *ha, swb_t *sp,
	stwuct dsd64 *dsd, uint16_t tot_dsds, stwuct qwa_tc_pawam *tc)
{
	void *next_dsd;
	uint8_t avaiw_dsds = 0;
	uint32_t dsd_wist_wen;
	stwuct dsd_dma *dsd_ptw;
	stwuct scattewwist *sg, *sgw;
	stwuct dsd64 *cuw_dsd = dsd;
	int	i;
	uint16_t	used_dsds = tot_dsds;
	stwuct scsi_cmnd *cmd;

	if (sp) {
		cmd = GET_CMD_SP(sp);
		sgw = scsi_sgwist(cmd);
	} ewse if (tc) {
		sgw = tc->sg;
	} ewse {
		BUG();
		wetuwn 1;
	}


	fow_each_sg(sgw, sg, tot_dsds, i) {
		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			avaiw_dsds = (used_dsds > QWA_DSDS_PEW_IOCB) ?
					QWA_DSDS_PEW_IOCB : used_dsds;
			dsd_wist_wen = (avaiw_dsds + 1) * 12;
			used_dsds -= avaiw_dsds;

			/* awwocate twacking DS */
			dsd_ptw = kzawwoc(sizeof(stwuct dsd_dma), GFP_ATOMIC);
			if (!dsd_ptw)
				wetuwn 1;

			/* awwocate new wist */
			dsd_ptw->dsd_addw = next_dsd =
			    dma_poow_awwoc(ha->dw_dma_poow, GFP_ATOMIC,
				&dsd_ptw->dsd_wist_dma);

			if (!next_dsd) {
				/*
				 * Need to cweanup onwy this dsd_ptw, west
				 * wiww be done by sp_fwee_dma()
				 */
				kfwee(dsd_ptw);
				wetuwn 1;
			}

			if (sp) {
				wist_add_taiw(&dsd_ptw->wist,
					      &sp->u.scmd.cwc_ctx->dsd_wist);

				sp->fwags |= SWB_CWC_CTX_DSD_VAWID;
			} ewse {
				wist_add_taiw(&dsd_ptw->wist,
				    &(tc->ctx->dsd_wist));
				*tc->ctx_dsd_awwoced = 1;
			}

			/* add new wist to cmd iocb ow wast wist */
			put_unawigned_we64(dsd_ptw->dsd_wist_dma,
					   &cuw_dsd->addwess);
			cuw_dsd->wength = cpu_to_we32(dsd_wist_wen);
			cuw_dsd = next_dsd;
		}
		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;

	}
	/* Nuww tewmination */
	cuw_dsd->addwess = 0;
	cuw_dsd->wength = 0;
	cuw_dsd++;
	wetuwn 0;
}

int
qwa24xx_wawk_and_buiwd_pwot_sgwist(stwuct qwa_hw_data *ha, swb_t *sp,
	stwuct dsd64 *cuw_dsd, uint16_t tot_dsds, stwuct qwa_tgt_cmd *tc)
{
	stwuct dsd_dma *dsd_ptw = NUWW, *dif_dsd, *nxt_dsd;
	stwuct scattewwist *sg, *sgw;
	stwuct cwc_context *difctx = NUWW;
	stwuct scsi_qwa_host *vha;
	uint dsd_wist_wen;
	uint avaiw_dsds = 0;
	uint used_dsds = tot_dsds;
	boow dif_wocaw_dma_awwoc = fawse;
	boow diwection_to_device = fawse;
	int i;

	if (sp) {
		stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);

		sgw = scsi_pwot_sgwist(cmd);
		vha = sp->vha;
		difctx = sp->u.scmd.cwc_ctx;
		diwection_to_device = cmd->sc_data_diwection == DMA_TO_DEVICE;
		qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha, 0xe021,
		  "%s: scsi_cmnd: %p, cwc_ctx: %p, sp: %p\n",
			__func__, cmd, difctx, sp);
	} ewse if (tc) {
		vha = tc->vha;
		sgw = tc->pwot_sg;
		difctx = tc->ctx;
		diwection_to_device = tc->dma_data_diwection == DMA_TO_DEVICE;
	} ewse {
		BUG();
		wetuwn 1;
	}

	qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha, 0xe021,
	    "%s: entew (wwite=%u)\n", __func__, diwection_to_device);

	/* if initiatow doing wwite ow tawget doing wead */
	if (diwection_to_device) {
		fow_each_sg(sgw, sg, tot_dsds, i) {
			u64 swe_phys = sg_phys(sg);

			/* If SGE addw + wen fwips bits in uppew 32-bits */
			if (MSD(swe_phys + sg->wength) ^ MSD(swe_phys)) {
				qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha, 0xe022,
				    "%s: page boundawy cwossing (phys=%wwx wen=%x)\n",
				    __func__, swe_phys, sg->wength);

				if (difctx) {
					ha->dif_bundwe_cwossed_pages++;
					dif_wocaw_dma_awwoc = twue;
				} ewse {
					qw_dbg(qw_dbg_tgt + qw_dbg_vewbose,
					    vha, 0xe022,
					    "%s: difctx pointew is NUWW\n",
					    __func__);
				}
				bweak;
			}
		}
		ha->dif_bundwe_wwites++;
	} ewse {
		ha->dif_bundwe_weads++;
	}

	if (qw2xdifbundwingintewnawbuffews)
		dif_wocaw_dma_awwoc = diwection_to_device;

	if (dif_wocaw_dma_awwoc) {
		u32 twack_difbundw_buf = 0;
		u32 wdma_sg_wen = 0;
		u8 wdma_needed = 1;

		difctx->no_dif_bundw = 0;
		difctx->dif_bundw_wen = 0;

		/* Twack DSD buffews */
		INIT_WIST_HEAD(&difctx->wdif_dsd_wist);
		/* Twack wocaw DMA buffews */
		INIT_WIST_HEAD(&difctx->wdif_dma_hndw_wist);

		fow_each_sg(sgw, sg, tot_dsds, i) {
			u32 sgwen = sg_dma_wen(sg);

			qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha, 0xe023,
			    "%s: sg[%x] (phys=%wwx sgwen=%x) wdma_sg_wen: %x dif_bundw_wen: %x wdma_needed: %x\n",
			    __func__, i, (u64)sg_phys(sg), sgwen, wdma_sg_wen,
			    difctx->dif_bundw_wen, wdma_needed);

			whiwe (sgwen) {
				u32 xfwwen = 0;

				if (wdma_needed) {
					/*
					 * Awwocate wist item to stowe
					 * the DMA buffews
					 */
					dsd_ptw = kzawwoc(sizeof(*dsd_ptw),
					    GFP_ATOMIC);
					if (!dsd_ptw) {
						qw_dbg(qw_dbg_tgt, vha, 0xe024,
						    "%s: faiwed awwoc dsd_ptw\n",
						    __func__);
						wetuwn 1;
					}
					ha->dif_bundwe_kawwocs++;

					/* awwocate dma buffew */
					dsd_ptw->dsd_addw = dma_poow_awwoc
						(ha->dif_bundw_poow, GFP_ATOMIC,
						 &dsd_ptw->dsd_wist_dma);
					if (!dsd_ptw->dsd_addw) {
						qw_dbg(qw_dbg_tgt, vha, 0xe024,
						    "%s: faiwed awwoc ->dsd_ptw\n",
						    __func__);
						/*
						 * need to cweanup onwy this
						 * dsd_ptw west wiww be done
						 * by sp_fwee_dma()
						 */
						kfwee(dsd_ptw);
						ha->dif_bundwe_kawwocs--;
						wetuwn 1;
					}
					ha->dif_bundwe_dma_awwocs++;
					wdma_needed = 0;
					difctx->no_dif_bundw++;
					wist_add_taiw(&dsd_ptw->wist,
					    &difctx->wdif_dma_hndw_wist);
				}

				/* xfwwen is min of dma poow size and sgwen */
				xfwwen = (sgwen >
				   (DIF_BUNDWING_DMA_POOW_SIZE - wdma_sg_wen)) ?
				    DIF_BUNDWING_DMA_POOW_SIZE - wdma_sg_wen :
				    sgwen;

				/* wepwace with wocaw awwocated dma buffew */
				sg_pcopy_to_buffew(sgw, sg_nents(sgw),
				    dsd_ptw->dsd_addw + wdma_sg_wen, xfwwen,
				    difctx->dif_bundw_wen);
				difctx->dif_bundw_wen += xfwwen;
				sgwen -= xfwwen;
				wdma_sg_wen += xfwwen;
				if (wdma_sg_wen == DIF_BUNDWING_DMA_POOW_SIZE ||
				    sg_is_wast(sg)) {
					wdma_needed = 1;
					wdma_sg_wen = 0;
				}
			}
		}

		twack_difbundw_buf = used_dsds = difctx->no_dif_bundw;
		qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha, 0xe025,
		    "dif_bundw_wen=%x, no_dif_bundw=%x twack_difbundw_buf: %x\n",
		    difctx->dif_bundw_wen, difctx->no_dif_bundw,
		    twack_difbundw_buf);

		if (sp)
			sp->fwags |= SWB_DIF_BUNDW_DMA_VAWID;
		ewse
			tc->pwot_fwags = DIF_BUNDW_DMA_VAWID;

		wist_fow_each_entwy_safe(dif_dsd, nxt_dsd,
		    &difctx->wdif_dma_hndw_wist, wist) {
			u32 sgwen = (difctx->dif_bundw_wen >
			    DIF_BUNDWING_DMA_POOW_SIZE) ?
			    DIF_BUNDWING_DMA_POOW_SIZE : difctx->dif_bundw_wen;

			BUG_ON(twack_difbundw_buf == 0);

			/* Awwocate additionaw continuation packets? */
			if (avaiw_dsds == 0) {
				qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha,
				    0xe024,
				    "%s: adding continuation iocb's\n",
				    __func__);
				avaiw_dsds = (used_dsds > QWA_DSDS_PEW_IOCB) ?
				    QWA_DSDS_PEW_IOCB : used_dsds;
				dsd_wist_wen = (avaiw_dsds + 1) * 12;
				used_dsds -= avaiw_dsds;

				/* awwocate twacking DS */
				dsd_ptw = kzawwoc(sizeof(*dsd_ptw), GFP_ATOMIC);
				if (!dsd_ptw) {
					qw_dbg(qw_dbg_tgt, vha, 0xe026,
					    "%s: faiwed awwoc dsd_ptw\n",
					    __func__);
					wetuwn 1;
				}
				ha->dif_bundwe_kawwocs++;

				difctx->no_wdif_dsd++;
				/* awwocate new wist */
				dsd_ptw->dsd_addw =
				    dma_poow_awwoc(ha->dw_dma_poow, GFP_ATOMIC,
					&dsd_ptw->dsd_wist_dma);
				if (!dsd_ptw->dsd_addw) {
					qw_dbg(qw_dbg_tgt, vha, 0xe026,
					    "%s: faiwed awwoc ->dsd_addw\n",
					    __func__);
					/*
					 * need to cweanup onwy this dsd_ptw
					 *  west wiww be done by sp_fwee_dma()
					 */
					kfwee(dsd_ptw);
					ha->dif_bundwe_kawwocs--;
					wetuwn 1;
				}
				ha->dif_bundwe_dma_awwocs++;

				if (sp) {
					wist_add_taiw(&dsd_ptw->wist,
					    &difctx->wdif_dsd_wist);
					sp->fwags |= SWB_CWC_CTX_DSD_VAWID;
				} ewse {
					wist_add_taiw(&dsd_ptw->wist,
					    &difctx->wdif_dsd_wist);
					tc->ctx_dsd_awwoced = 1;
				}

				/* add new wist to cmd iocb ow wast wist */
				put_unawigned_we64(dsd_ptw->dsd_wist_dma,
						   &cuw_dsd->addwess);
				cuw_dsd->wength = cpu_to_we32(dsd_wist_wen);
				cuw_dsd = dsd_ptw->dsd_addw;
			}
			put_unawigned_we64(dif_dsd->dsd_wist_dma,
					   &cuw_dsd->addwess);
			cuw_dsd->wength = cpu_to_we32(sgwen);
			cuw_dsd++;
			avaiw_dsds--;
			difctx->dif_bundw_wen -= sgwen;
			twack_difbundw_buf--;
		}

		qw_dbg(qw_dbg_tgt + qw_dbg_vewbose, vha, 0xe026,
		    "%s: no_wdif_dsd:%x, no_dif_bundw:%x\n", __func__,
			difctx->no_wdif_dsd, difctx->no_dif_bundw);
	} ewse {
		fow_each_sg(sgw, sg, tot_dsds, i) {
			/* Awwocate additionaw continuation packets? */
			if (avaiw_dsds == 0) {
				avaiw_dsds = (used_dsds > QWA_DSDS_PEW_IOCB) ?
				    QWA_DSDS_PEW_IOCB : used_dsds;
				dsd_wist_wen = (avaiw_dsds + 1) * 12;
				used_dsds -= avaiw_dsds;

				/* awwocate twacking DS */
				dsd_ptw = kzawwoc(sizeof(*dsd_ptw), GFP_ATOMIC);
				if (!dsd_ptw) {
					qw_dbg(qw_dbg_tgt + qw_dbg_vewbose,
					    vha, 0xe027,
					    "%s: faiwed awwoc dsd_dma...\n",
					    __func__);
					wetuwn 1;
				}

				/* awwocate new wist */
				dsd_ptw->dsd_addw =
				    dma_poow_awwoc(ha->dw_dma_poow, GFP_ATOMIC,
					&dsd_ptw->dsd_wist_dma);
				if (!dsd_ptw->dsd_addw) {
					/* need to cweanup onwy this dsd_ptw */
					/* west wiww be done by sp_fwee_dma() */
					kfwee(dsd_ptw);
					wetuwn 1;
				}

				if (sp) {
					wist_add_taiw(&dsd_ptw->wist,
					    &difctx->dsd_wist);
					sp->fwags |= SWB_CWC_CTX_DSD_VAWID;
				} ewse {
					wist_add_taiw(&dsd_ptw->wist,
					    &difctx->dsd_wist);
					tc->ctx_dsd_awwoced = 1;
				}

				/* add new wist to cmd iocb ow wast wist */
				put_unawigned_we64(dsd_ptw->dsd_wist_dma,
						   &cuw_dsd->addwess);
				cuw_dsd->wength = cpu_to_we32(dsd_wist_wen);
				cuw_dsd = dsd_ptw->dsd_addw;
			}
			append_dsd64(&cuw_dsd, sg);
			avaiw_dsds--;
		}
	}
	/* Nuww tewmination */
	cuw_dsd->addwess = 0;
	cuw_dsd->wength = 0;
	cuw_dsd++;
	wetuwn 0;
}

/**
 * qwa24xx_buiwd_scsi_cwc_2_iocbs() - Buiwd IOCB command utiwizing Command
 *							Type 6 IOCB types.
 *
 * @sp: SWB command to pwocess
 * @cmd_pkt: Command type 3 IOCB
 * @tot_dsds: Totaw numbew of segments to twansfew
 * @tot_pwot_dsds: Totaw numbew of segments with pwotection infowmation
 * @fw_pwot_opts: Pwotection options to be passed to fiwmwawe
 */
static inwine int
qwa24xx_buiwd_scsi_cwc_2_iocbs(swb_t *sp, stwuct cmd_type_cwc_2 *cmd_pkt,
    uint16_t tot_dsds, uint16_t tot_pwot_dsds, uint16_t fw_pwot_opts)
{
	stwuct dsd64		*cuw_dsd;
	__be32			*fcp_dw;
	scsi_qwa_host_t		*vha;
	stwuct scsi_cmnd	*cmd;
	uint32_t		totaw_bytes = 0;
	uint32_t		data_bytes;
	uint32_t		dif_bytes;
	uint8_t			bundwing = 1;
	uint16_t		bwk_size;
	stwuct cwc_context	*cwc_ctx_pkt = NUWW;
	stwuct qwa_hw_data	*ha;
	uint8_t			additionaw_fcpcdb_wen;
	uint16_t		fcp_cmnd_wen;
	stwuct fcp_cmnd		*fcp_cmnd;
	dma_addw_t		cwc_ctx_dma;

	cmd = GET_CMD_SP(sp);

	/* Update entwy type to indicate Command Type CWC_2 IOCB */
	put_unawigned_we32(COMMAND_TYPE_CWC_2, &cmd_pkt->entwy_type);

	vha = sp->vha;
	ha = vha->hw;

	/* No data twansfew */
	data_bytes = scsi_buffwen(cmd);
	if (!data_bytes || cmd->sc_data_diwection == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		wetuwn QWA_SUCCESS;
	}

	cmd_pkt->vp_index = sp->vha->vp_idx;

	/* Set twansfew diwection */
	if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
		cmd_pkt->contwow_fwags =
		    cpu_to_we16(CF_WWITE_DATA);
	} ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		cmd_pkt->contwow_fwags =
		    cpu_to_we16(CF_WEAD_DATA);
	}

	if ((scsi_get_pwot_op(cmd) == SCSI_PWOT_WEAD_INSEWT) ||
	    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WWITE_STWIP) ||
	    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WEAD_STWIP) ||
	    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WWITE_INSEWT))
		bundwing = 0;

	/* Awwocate CWC context fwom gwobaw poow */
	cwc_ctx_pkt = sp->u.scmd.cwc_ctx =
	    dma_poow_zawwoc(ha->dw_dma_poow, GFP_ATOMIC, &cwc_ctx_dma);

	if (!cwc_ctx_pkt)
		goto cwc_queuing_ewwow;

	cwc_ctx_pkt->cwc_ctx_dma = cwc_ctx_dma;

	sp->fwags |= SWB_CWC_CTX_DMA_VAWID;

	/* Set handwe */
	cwc_ctx_pkt->handwe = cmd_pkt->handwe;

	INIT_WIST_HEAD(&cwc_ctx_pkt->dsd_wist);

	qwa24xx_set_t10dif_tags(sp, (stwuct fw_dif_context *)
	    &cwc_ctx_pkt->wef_tag, tot_pwot_dsds);

	put_unawigned_we64(cwc_ctx_dma, &cmd_pkt->cwc_context_addwess);
	cmd_pkt->cwc_context_wen = cpu_to_we16(CWC_CONTEXT_WEN_FW);

	/* Detewmine SCSI command wength -- awign to 4 byte boundawy */
	if (cmd->cmd_wen > 16) {
		additionaw_fcpcdb_wen = cmd->cmd_wen - 16;
		if ((cmd->cmd_wen % 4) != 0) {
			/* SCSI cmd > 16 bytes must be muwtipwe of 4 */
			goto cwc_queuing_ewwow;
		}
		fcp_cmnd_wen = 12 + cmd->cmd_wen + 4;
	} ewse {
		additionaw_fcpcdb_wen = 0;
		fcp_cmnd_wen = 12 + 16 + 4;
	}

	fcp_cmnd = &cwc_ctx_pkt->fcp_cmnd;

	fcp_cmnd->additionaw_cdb_wen = additionaw_fcpcdb_wen;
	if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		fcp_cmnd->additionaw_cdb_wen |= 1;
	ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		fcp_cmnd->additionaw_cdb_wen |= 2;

	int_to_scsiwun(cmd->device->wun, &fcp_cmnd->wun);
	memcpy(fcp_cmnd->cdb, cmd->cmnd, cmd->cmd_wen);
	cmd_pkt->fcp_cmnd_dseg_wen = cpu_to_we16(fcp_cmnd_wen);
	put_unawigned_we64(cwc_ctx_dma + CWC_CONTEXT_FCPCMND_OFF,
			   &cmd_pkt->fcp_cmnd_dseg_addwess);
	fcp_cmnd->task_management = 0;
	fcp_cmnd->task_attwibute = TSK_SIMPWE;

	cmd_pkt->fcp_wsp_dseg_wen = 0; /* Wet wesponse come in status iocb */

	/* Compute dif wen and adjust data wen to incude pwotection */
	dif_bytes = 0;
	bwk_size = cmd->device->sectow_size;
	dif_bytes = (data_bytes / bwk_size) * 8;

	switch (scsi_get_pwot_op(GET_CMD_SP(sp))) {
	case SCSI_PWOT_WEAD_INSEWT:
	case SCSI_PWOT_WWITE_STWIP:
		totaw_bytes = data_bytes;
		data_bytes += dif_bytes;
		bweak;

	case SCSI_PWOT_WEAD_STWIP:
	case SCSI_PWOT_WWITE_INSEWT:
	case SCSI_PWOT_WEAD_PASS:
	case SCSI_PWOT_WWITE_PASS:
		totaw_bytes = data_bytes + dif_bytes;
		bweak;
	defauwt:
		BUG();
	}

	if (!qwa2x00_hba_eww_chk_enabwed(sp))
		fw_pwot_opts |= 0x10; /* Disabwe Guawd tag checking */
	/* HBA ewwow checking enabwed */
	ewse if (IS_PI_UNINIT_CAPABWE(ha)) {
		if ((scsi_get_pwot_type(GET_CMD_SP(sp)) == SCSI_PWOT_DIF_TYPE1)
		    || (scsi_get_pwot_type(GET_CMD_SP(sp)) ==
			SCSI_PWOT_DIF_TYPE2))
			fw_pwot_opts |= BIT_10;
		ewse if (scsi_get_pwot_type(GET_CMD_SP(sp)) ==
		    SCSI_PWOT_DIF_TYPE3)
			fw_pwot_opts |= BIT_11;
	}

	if (!bundwing) {
		cuw_dsd = &cwc_ctx_pkt->u.nobundwing.data_dsd[0];
	} ewse {
		/*
		 * Configuwe Bundwing if we need to fetch intewwaving
		 * pwotection PCI accesses
		 */
		fw_pwot_opts |= PO_ENABWE_DIF_BUNDWING;
		cwc_ctx_pkt->u.bundwing.dif_byte_count = cpu_to_we32(dif_bytes);
		cwc_ctx_pkt->u.bundwing.dseg_count = cpu_to_we16(tot_dsds -
							tot_pwot_dsds);
		cuw_dsd = &cwc_ctx_pkt->u.bundwing.data_dsd[0];
	}

	/* Finish the common fiewds of CWC pkt */
	cwc_ctx_pkt->bwk_size = cpu_to_we16(bwk_size);
	cwc_ctx_pkt->pwot_opts = cpu_to_we16(fw_pwot_opts);
	cwc_ctx_pkt->byte_count = cpu_to_we32(data_bytes);
	cwc_ctx_pkt->guawd_seed = cpu_to_we16(0);
	/* Fibwe channew byte count */
	cmd_pkt->byte_count = cpu_to_we32(totaw_bytes);
	fcp_dw = (__be32 *)(cwc_ctx_pkt->fcp_cmnd.cdb + 16 +
	    additionaw_fcpcdb_wen);
	*fcp_dw = htonw(totaw_bytes);

	if (!data_bytes || cmd->sc_data_diwection == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		wetuwn QWA_SUCCESS;
	}
	/* Wawks data segments */

	cmd_pkt->contwow_fwags |= cpu_to_we16(CF_DATA_SEG_DESCW_ENABWE);

	if (!bundwing && tot_pwot_dsds) {
		if (qwa24xx_wawk_and_buiwd_sgwist_no_difb(ha, sp,
			cuw_dsd, tot_dsds, NUWW))
			goto cwc_queuing_ewwow;
	} ewse if (qwa24xx_wawk_and_buiwd_sgwist(ha, sp, cuw_dsd,
			(tot_dsds - tot_pwot_dsds), NUWW))
		goto cwc_queuing_ewwow;

	if (bundwing && tot_pwot_dsds) {
		/* Wawks dif segments */
		cmd_pkt->contwow_fwags |= cpu_to_we16(CF_DIF_SEG_DESCW_ENABWE);
		cuw_dsd = &cwc_ctx_pkt->u.bundwing.dif_dsd;
		if (qwa24xx_wawk_and_buiwd_pwot_sgwist(ha, sp, cuw_dsd,
				tot_pwot_dsds, NUWW))
			goto cwc_queuing_ewwow;
	}
	wetuwn QWA_SUCCESS;

cwc_queuing_ewwow:
	/* Cweanup wiww be pewfowmed by the cawwew */

	wetuwn QWA_FUNCTION_FAIWED;
}

/**
 * qwa24xx_stawt_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
int
qwa24xx_stawt_scsi(swb_t *sp)
{
	int		nseg;
	unsigned wong   fwags;
	uint32_t	*cww_ptw;
	uint32_t	handwe;
	stwuct cmd_type_7 *cmd_pkt;
	uint16_t	cnt;
	uint16_t	weq_cnt;
	uint16_t	tot_dsds;
	stwuct weq_que *weq = NUWW;
	stwuct wsp_que *wsp;
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);
	stwuct scsi_qwa_host *vha = sp->vha;
	stwuct qwa_hw_data *ha = vha->hw;

	if (sp->fcpowt->edif.enabwe  && (sp->fcpowt->fwags & FCF_FCSP_DEVICE))
		wetuwn qwa28xx_stawt_scsi_edif(sp);

	/* Setup device pointews. */
	weq = vha->weq;
	wsp = weq->wsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (qwa2x00_mawkew(vha, ha->base_qpaiw, 0, 0, MK_SYNC_AWW) !=
		    QWA_SUCCESS)
			wetuwn QWA_FUNCTION_FAIWED;
		vha->mawkew_needed = 0;
	}

	/* Acquiwe wing specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
	} ewse
		nseg = 0;

	tot_dsds = nseg;
	weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = weq_cnt;
	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes))
		goto queuing_ewwow;

	if (weq->cnt < (weq_cnt + 2)) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt))
				goto queuing_ewwow;
		}

		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
				(weq->wing_index - cnt);
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	cmd_pkt = (stwuct cmd_type_7 *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	/* Zewo out wemaining powtion of packet. */
	/*    tagged queuing modifiew -- defauwt is TSK_SIMPWE (0). */
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* Set NPOWT-ID and WUN numbew*/
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
	cmd_pkt->vp_index = sp->vha->vp_idx;

	int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

	cmd_pkt->task = TSK_SIMPWE;

	/* Woad SCSI command packet. */
	memcpy(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_wen);
	host_to_fcp_swap(cmd_pkt->fcp_cdb, sizeof(cmd_pkt->fcp_cdb));

	cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));

	/* Buiwd IOCB segments */
	qwa24xx_buiwd_scsi_iocbs(sp, cmd_pkt, tot_dsds, weq);

	/* Set totaw data segment count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	wmb();
	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	sp->qpaiw->cmd_cnt++;
	sp->fwags |= SWB_DMA_VAWID;

	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn QWA_SUCCESS;

queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}

/**
 * qwa24xx_dif_stawt_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
int
qwa24xx_dif_stawt_scsi(swb_t *sp)
{
	int			nseg;
	unsigned wong		fwags;
	uint32_t		*cww_ptw;
	uint32_t		handwe;
	uint16_t		cnt;
	uint16_t		weq_cnt = 0;
	uint16_t		tot_dsds;
	uint16_t		tot_pwot_dsds;
	uint16_t		fw_pwot_opts = 0;
	stwuct weq_que		*weq = NUWW;
	stwuct wsp_que		*wsp = NUWW;
	stwuct scsi_cmnd	*cmd = GET_CMD_SP(sp);
	stwuct scsi_qwa_host	*vha = sp->vha;
	stwuct qwa_hw_data	*ha = vha->hw;
	stwuct cmd_type_cwc_2	*cmd_pkt;
	uint32_t		status = 0;

#define QDSS_GOT_Q_SPACE	BIT_0

	/* Onwy pwocess pwotection ow >16 cdb in this woutine */
	if (scsi_get_pwot_op(cmd) == SCSI_PWOT_NOWMAW) {
		if (cmd->cmd_wen <= 16)
			wetuwn qwa24xx_stawt_scsi(sp);
		ewse
			wetuwn qwa_stawt_scsi_type6(sp);
	}

	/* Setup device pointews. */
	weq = vha->weq;
	wsp = weq->wsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (qwa2x00_mawkew(vha, ha->base_qpaiw, 0, 0, MK_SYNC_AWW) !=
		    QWA_SUCCESS)
			wetuwn QWA_FUNCTION_FAIWED;
		vha->mawkew_needed = 0;
	}

	/* Acquiwe wing specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Compute numbew of wequiwed data segments */
	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
		ewse
			sp->fwags |= SWB_DMA_VAWID;

		if ((scsi_get_pwot_op(cmd) == SCSI_PWOT_WEAD_INSEWT) ||
		    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WWITE_STWIP)) {
			stwuct qwa2_sgx sgx;
			uint32_t	pawtiaw;

			memset(&sgx, 0, sizeof(stwuct qwa2_sgx));
			sgx.tot_bytes = scsi_buffwen(cmd);
			sgx.cuw_sg = scsi_sgwist(cmd);
			sgx.sp = sp;

			nseg = 0;
			whiwe (qwa24xx_get_one_bwock_sg(
			    cmd->device->sectow_size, &sgx, &pawtiaw))
				nseg++;
		}
	} ewse
		nseg = 0;

	/* numbew of wequiwed data segments */
	tot_dsds = nseg;

	/* Compute numbew of wequiwed pwotection segments */
	if (qwa24xx_configuwe_pwot_mode(sp, &fw_pwot_opts)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_pwot_sgwist(cmd),
		    scsi_pwot_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
		ewse
			sp->fwags |= SWB_CWC_PWOT_DMA_VAWID;

		if ((scsi_get_pwot_op(cmd) == SCSI_PWOT_WEAD_INSEWT) ||
		    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WWITE_STWIP)) {
			nseg = scsi_buffwen(cmd) / cmd->device->sectow_size;
		}
	} ewse {
		nseg = 0;
	}

	weq_cnt = 1;
	/* Totaw Data and pwotection sg segment(s) */
	tot_pwot_dsds = nseg;
	tot_dsds += nseg;

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);
	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes))
		goto queuing_ewwow;

	if (weq->cnt < (weq_cnt + 2)) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt))
				goto queuing_ewwow;
		}
		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
				(weq->wing_index - cnt);
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	status |= QDSS_GOT_Q_SPACE;

	/* Buiwd headew pawt of command packet (excwuding the OPCODE). */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	/* Fiww-in common awea */
	cmd_pkt = (stwuct cmd_type_cwc_2 *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);

	/* Set NPOWT-ID and WUN numbew*/
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;

	int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

	/* Totaw Data and pwotection segment(s) */
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* Buiwd IOCB segments and adjust fow data pwotection segments */
	if (qwa24xx_buiwd_scsi_cwc_2_iocbs(sp, (stwuct cmd_type_cwc_2 *)
	    weq->wing_ptw, tot_dsds, tot_pwot_dsds, fw_pwot_opts) !=
		QWA_SUCCESS)
		goto queuing_ewwow;

	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	/* Specify wesponse queue numbew whewe compwetion shouwd happen */
	cmd_pkt->entwy_status = (uint8_t) wsp->id;
	cmd_pkt->timeout = cpu_to_we16(0);
	wmb();

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	sp->qpaiw->cmd_cnt++;
	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_SUCCESS;

queuing_ewwow:
	if (status & QDSS_GOT_Q_SPACE) {
		weq->outstanding_cmds[handwe] = NUWW;
		weq->cnt += weq_cnt;
	}
	/* Cweanup wiww be pewfowmed by the cawwew (queuecommand) */

	qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}

/**
 * qwa2xxx_stawt_scsi_mq() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
static int
qwa2xxx_stawt_scsi_mq(swb_t *sp)
{
	int		nseg;
	unsigned wong   fwags;
	uint32_t	*cww_ptw;
	uint32_t	handwe;
	stwuct cmd_type_7 *cmd_pkt;
	uint16_t	cnt;
	uint16_t	weq_cnt;
	uint16_t	tot_dsds;
	stwuct weq_que *weq = NUWW;
	stwuct wsp_que *wsp;
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);
	stwuct scsi_qwa_host *vha = sp->fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_qpaiw *qpaiw = sp->qpaiw;

	if (sp->fcpowt->edif.enabwe && (sp->fcpowt->fwags & FCF_FCSP_DEVICE))
		wetuwn qwa28xx_stawt_scsi_edif(sp);

	/* Acquiwe qpaiw specific wock */
	spin_wock_iwqsave(&qpaiw->qp_wock, fwags);

	/* Setup qpaiw pointews */
	weq = qpaiw->weq;
	wsp = qpaiw->wsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (__qwa2x00_mawkew(vha, qpaiw, 0, 0, MK_SYNC_AWW) !=
		    QWA_SUCCESS) {
			spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);
			wetuwn QWA_FUNCTION_FAIWED;
		}
		vha->mawkew_needed = 0;
	}

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
	} ewse
		nseg = 0;

	tot_dsds = nseg;
	weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = weq_cnt;
	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes))
		goto queuing_ewwow;

	if (weq->cnt < (weq_cnt + 2)) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt))
				goto queuing_ewwow;
		}

		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
				(weq->wing_index - cnt);
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	cmd_pkt = (stwuct cmd_type_7 *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	/* Zewo out wemaining powtion of packet. */
	/*    tagged queuing modifiew -- defauwt is TSK_SIMPWE (0). */
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* Set NPOWT-ID and WUN numbew*/
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
	cmd_pkt->vp_index = sp->fcpowt->vha->vp_idx;

	int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

	cmd_pkt->task = TSK_SIMPWE;

	/* Woad SCSI command packet. */
	memcpy(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_wen);
	host_to_fcp_swap(cmd_pkt->fcp_cdb, sizeof(cmd_pkt->fcp_cdb));

	cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));

	/* Buiwd IOCB segments */
	qwa24xx_buiwd_scsi_iocbs(sp, cmd_pkt, tot_dsds, weq);

	/* Set totaw data segment count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	wmb();
	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	sp->qpaiw->cmd_cnt++;
	sp->fwags |= SWB_DMA_VAWID;

	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);
	wetuwn QWA_SUCCESS;

queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}


/**
 * qwa2xxx_dif_stawt_scsi_mq() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
int
qwa2xxx_dif_stawt_scsi_mq(swb_t *sp)
{
	int			nseg;
	unsigned wong		fwags;
	uint32_t		*cww_ptw;
	uint32_t		handwe;
	uint16_t		cnt;
	uint16_t		weq_cnt = 0;
	uint16_t		tot_dsds;
	uint16_t		tot_pwot_dsds;
	uint16_t		fw_pwot_opts = 0;
	stwuct weq_que		*weq = NUWW;
	stwuct wsp_que		*wsp = NUWW;
	stwuct scsi_cmnd	*cmd = GET_CMD_SP(sp);
	stwuct scsi_qwa_host	*vha = sp->fcpowt->vha;
	stwuct qwa_hw_data	*ha = vha->hw;
	stwuct cmd_type_cwc_2	*cmd_pkt;
	uint32_t		status = 0;
	stwuct qwa_qpaiw	*qpaiw = sp->qpaiw;

#define QDSS_GOT_Q_SPACE	BIT_0

	/* Check fow host side state */
	if (!qpaiw->onwine) {
		cmd->wesuwt = DID_NO_CONNECT << 16;
		wetuwn QWA_INTEWFACE_EWWOW;
	}

	if (!qpaiw->difdix_suppowted &&
		scsi_get_pwot_op(cmd) != SCSI_PWOT_NOWMAW) {
		cmd->wesuwt = DID_NO_CONNECT << 16;
		wetuwn QWA_INTEWFACE_EWWOW;
	}

	/* Onwy pwocess pwotection ow >16 cdb in this woutine */
	if (scsi_get_pwot_op(cmd) == SCSI_PWOT_NOWMAW) {
		if (cmd->cmd_wen <= 16)
			wetuwn qwa2xxx_stawt_scsi_mq(sp);
		ewse
			wetuwn qwa_stawt_scsi_type6(sp);
	}

	spin_wock_iwqsave(&qpaiw->qp_wock, fwags);

	/* Setup qpaiw pointews */
	wsp = qpaiw->wsp;
	weq = qpaiw->weq;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (__qwa2x00_mawkew(vha, qpaiw, 0, 0, MK_SYNC_AWW) !=
		    QWA_SUCCESS) {
			spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);
			wetuwn QWA_FUNCTION_FAIWED;
		}
		vha->mawkew_needed = 0;
	}

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Compute numbew of wequiwed data segments */
	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
		ewse
			sp->fwags |= SWB_DMA_VAWID;

		if ((scsi_get_pwot_op(cmd) == SCSI_PWOT_WEAD_INSEWT) ||
		    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WWITE_STWIP)) {
			stwuct qwa2_sgx sgx;
			uint32_t	pawtiaw;

			memset(&sgx, 0, sizeof(stwuct qwa2_sgx));
			sgx.tot_bytes = scsi_buffwen(cmd);
			sgx.cuw_sg = scsi_sgwist(cmd);
			sgx.sp = sp;

			nseg = 0;
			whiwe (qwa24xx_get_one_bwock_sg(
			    cmd->device->sectow_size, &sgx, &pawtiaw))
				nseg++;
		}
	} ewse
		nseg = 0;

	/* numbew of wequiwed data segments */
	tot_dsds = nseg;

	/* Compute numbew of wequiwed pwotection segments */
	if (qwa24xx_configuwe_pwot_mode(sp, &fw_pwot_opts)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_pwot_sgwist(cmd),
		    scsi_pwot_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
		ewse
			sp->fwags |= SWB_CWC_PWOT_DMA_VAWID;

		if ((scsi_get_pwot_op(cmd) == SCSI_PWOT_WEAD_INSEWT) ||
		    (scsi_get_pwot_op(cmd) == SCSI_PWOT_WWITE_STWIP)) {
			nseg = scsi_buffwen(cmd) / cmd->device->sectow_size;
		}
	} ewse {
		nseg = 0;
	}

	weq_cnt = 1;
	/* Totaw Data and pwotection sg segment(s) */
	tot_pwot_dsds = nseg;
	tot_dsds += nseg;

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);
	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes))
		goto queuing_ewwow;

	if (weq->cnt < (weq_cnt + 2)) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt))
				goto queuing_ewwow;
		}

		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
				(weq->wing_index - cnt);
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	status |= QDSS_GOT_Q_SPACE;

	/* Buiwd headew pawt of command packet (excwuding the OPCODE). */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	/* Fiww-in common awea */
	cmd_pkt = (stwuct cmd_type_cwc_2 *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);

	/* Set NPOWT-ID and WUN numbew*/
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;

	int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

	/* Totaw Data and pwotection segment(s) */
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* Buiwd IOCB segments and adjust fow data pwotection segments */
	if (qwa24xx_buiwd_scsi_cwc_2_iocbs(sp, (stwuct cmd_type_cwc_2 *)
	    weq->wing_ptw, tot_dsds, tot_pwot_dsds, fw_pwot_opts) !=
		QWA_SUCCESS)
		goto queuing_ewwow;

	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	cmd_pkt->timeout = cpu_to_we16(0);
	wmb();

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	sp->qpaiw->cmd_cnt++;
	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

	wetuwn QWA_SUCCESS;

queuing_ewwow:
	if (status & QDSS_GOT_Q_SPACE) {
		weq->outstanding_cmds[handwe] = NUWW;
		weq->cnt += weq_cnt;
	}
	/* Cweanup wiww be pewfowmed by the cawwew (queuecommand) */

	qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}

/* Genewic Contwow-SWB manipuwation functions. */

/* hawdwawe_wock assumed to be hewd. */

void *
__qwa2x00_awwoc_iocbs(stwuct qwa_qpaiw *qpaiw, swb_t *sp)
{
	scsi_qwa_host_t *vha = qpaiw->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct weq_que *weq = qpaiw->weq;
	device_weg_t *weg = ISP_QUE_WEG(ha, weq->id);
	uint32_t handwe;
	wequest_t *pkt;
	uint16_t cnt, weq_cnt;

	pkt = NUWW;
	weq_cnt = 1;
	handwe = 0;

	if (sp && (sp->type != SWB_SCSI_CMD)) {
		/* Adjust entwy-counts as needed. */
		weq_cnt = sp->iocbs;
	}

	/* Check fow woom on wequest queue. */
	if (weq->cnt < weq_cnt + 2) {
		if (qpaiw->use_shadow_weg)
			cnt = *weq->out_ptw;
		ewse if (ha->mqenabwe || IS_QWA83XX(ha) || IS_QWA27XX(ha) ||
		    IS_QWA28XX(ha))
			cnt = wd_weg_dwowd(&weg->isp25mq.weq_q_out);
		ewse if (IS_P3P_TYPE(ha))
			cnt = wd_weg_dwowd(weg->isp82.weq_q_out);
		ewse if (IS_FWI2_CAPABWE(ha))
			cnt = wd_weg_dwowd(&weg->isp24.weq_q_out);
		ewse if (IS_QWAFX00(ha))
			cnt = wd_weg_dwowd(&weg->ispfx00.weq_q_out);
		ewse
			cnt = qwa2x00_debounce_wegistew(
			    ISP_WEQ_Q_OUT(ha, &weg->isp));

		if (!qpaiw->use_shadow_weg && cnt == ISP_WEG16_DISCONNECT) {
			qwa_scheduwe_eeh_wowk(vha);
			wetuwn NUWW;
		}

		if  (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
			    (weq->wing_index - cnt);
	}
	if (weq->cnt < weq_cnt + 2)
		goto queuing_ewwow;

	if (sp) {
		handwe = qwa2xxx_get_next_handwe(weq);
		if (handwe == 0) {
			qw_wog(qw_wog_wawn, vha, 0x700b,
			    "No woom on outstanding cmd awway.\n");
			goto queuing_ewwow;
		}

		/* Pwep command awway. */
		weq->cuwwent_outstanding_cmd = handwe;
		weq->outstanding_cmds[handwe] = sp;
		sp->handwe = handwe;
	}

	/* Pwep packet */
	weq->cnt -= weq_cnt;
	pkt = weq->wing_ptw;
	memset(pkt, 0, WEQUEST_ENTWY_SIZE);
	if (IS_QWAFX00(ha)) {
		wwt_weg_byte((u8 __fowce __iomem *)&pkt->entwy_count, weq_cnt);
		wwt_weg_dwowd((__we32 __fowce __iomem *)&pkt->handwe, handwe);
	} ewse {
		pkt->entwy_count = weq_cnt;
		pkt->handwe = handwe;
	}

	wetuwn pkt;

queuing_ewwow:
	qpaiw->tgt_countews.num_awwoc_iocb_faiwed++;
	wetuwn pkt;
}

void *
qwa2x00_awwoc_iocbs_weady(stwuct qwa_qpaiw *qpaiw, swb_t *sp)
{
	scsi_qwa_host_t *vha = qpaiw->vha;

	if (qwa2x00_weset_active(vha))
		wetuwn NUWW;

	wetuwn __qwa2x00_awwoc_iocbs(qpaiw, sp);
}

void *
qwa2x00_awwoc_iocbs(stwuct scsi_qwa_host *vha, swb_t *sp)
{
	wetuwn __qwa2x00_awwoc_iocbs(vha->hw->base_qpaiw, sp);
}

static void
qwa24xx_pwwi_iocb(swb_t *sp, stwuct wogio_entwy_24xx *wogio)
{
	stwuct swb_iocb *wio = &sp->u.iocb_cmd;

	wogio->entwy_type = WOGINOUT_POWT_IOCB_TYPE;
	wogio->contwow_fwags = cpu_to_we16(WCF_COMMAND_PWWI);
	if (wio->u.wogio.fwags & SWB_WOGIN_NVME_PWWI) {
		wogio->contwow_fwags |= cpu_to_we16(WCF_NVME_PWWI);
		if (sp->vha->fwags.nvme_fiwst_buwst)
			wogio->io_pawametew[0] =
				cpu_to_we32(NVME_PWWI_SP_FIWST_BUWST);
		if (sp->vha->fwags.nvme2_enabwed) {
			/* Set sewvice pawametew BIT_7 fow NVME CONF suppowt */
			wogio->io_pawametew[0] |=
				cpu_to_we32(NVME_PWWI_SP_CONF);
			/* Set sewvice pawametew BIT_8 fow SWEW suppowt */
			wogio->io_pawametew[0] |=
				cpu_to_we32(NVME_PWWI_SP_SWEW);
			/* Set sewvice pawametew BIT_9 fow PI contwow suppowt */
			wogio->io_pawametew[0] |=
				cpu_to_we32(NVME_PWWI_SP_PI_CTWW);
		}
	}

	wogio->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	wogio->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	wogio->powt_id[1] = sp->fcpowt->d_id.b.awea;
	wogio->powt_id[2] = sp->fcpowt->d_id.b.domain;
	wogio->vp_index = sp->vha->vp_idx;
}

static void
qwa24xx_wogin_iocb(swb_t *sp, stwuct wogio_entwy_24xx *wogio)
{
	stwuct swb_iocb *wio = &sp->u.iocb_cmd;

	wogio->entwy_type = WOGINOUT_POWT_IOCB_TYPE;
	wogio->contwow_fwags = cpu_to_we16(WCF_COMMAND_PWOGI);

	if (wio->u.wogio.fwags & SWB_WOGIN_PWWI_ONWY) {
		wogio->contwow_fwags = cpu_to_we16(WCF_COMMAND_PWWI);
	} ewse {
		wogio->contwow_fwags = cpu_to_we16(WCF_COMMAND_PWOGI);
		if (wio->u.wogio.fwags & SWB_WOGIN_COND_PWOGI)
			wogio->contwow_fwags |= cpu_to_we16(WCF_COND_PWOGI);
		if (wio->u.wogio.fwags & SWB_WOGIN_SKIP_PWWI)
			wogio->contwow_fwags |= cpu_to_we16(WCF_SKIP_PWWI);
		if (wio->u.wogio.fwags & SWB_WOGIN_FCSP) {
			wogio->contwow_fwags |=
			    cpu_to_we16(WCF_COMMON_FEAT | WCF_SKIP_PWWI);
			wogio->io_pawametew[0] =
			    cpu_to_we32(WIO_COMM_FEAT_FCSP | WIO_COMM_FEAT_CIO);
		}
	}
	wogio->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	wogio->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	wogio->powt_id[1] = sp->fcpowt->d_id.b.awea;
	wogio->powt_id[2] = sp->fcpowt->d_id.b.domain;
	wogio->vp_index = sp->vha->vp_idx;
}

static void
qwa2x00_wogin_iocb(swb_t *sp, stwuct mbx_entwy *mbx)
{
	stwuct qwa_hw_data *ha = sp->vha->hw;
	stwuct swb_iocb *wio = &sp->u.iocb_cmd;
	uint16_t opts;

	mbx->entwy_type = MBX_IOCB_TYPE;
	SET_TAWGET_ID(ha, mbx->woop_id, sp->fcpowt->woop_id);
	mbx->mb0 = cpu_to_we16(MBC_WOGIN_FABWIC_POWT);
	opts = wio->u.wogio.fwags & SWB_WOGIN_COND_PWOGI ? BIT_0 : 0;
	opts |= wio->u.wogio.fwags & SWB_WOGIN_SKIP_PWWI ? BIT_1 : 0;
	if (HAS_EXTENDED_IDS(ha)) {
		mbx->mb1 = cpu_to_we16(sp->fcpowt->woop_id);
		mbx->mb10 = cpu_to_we16(opts);
	} ewse {
		mbx->mb1 = cpu_to_we16((sp->fcpowt->woop_id << 8) | opts);
	}
	mbx->mb2 = cpu_to_we16(sp->fcpowt->d_id.b.domain);
	mbx->mb3 = cpu_to_we16(sp->fcpowt->d_id.b.awea << 8 |
	    sp->fcpowt->d_id.b.aw_pa);
	mbx->mb9 = cpu_to_we16(sp->vha->vp_idx);
}

static void
qwa24xx_wogout_iocb(swb_t *sp, stwuct wogio_entwy_24xx *wogio)
{
	u16 contwow_fwags = WCF_COMMAND_WOGO;
	wogio->entwy_type = WOGINOUT_POWT_IOCB_TYPE;

	if (sp->fcpowt->expwicit_wogout) {
		contwow_fwags |= WCF_EXPW_WOGO|WCF_FWEE_NPOWT;
	} ewse {
		contwow_fwags |= WCF_IMPW_WOGO;

		if (!sp->fcpowt->keep_npowt_handwe)
			contwow_fwags |= WCF_FWEE_NPOWT;
	}

	wogio->contwow_fwags = cpu_to_we16(contwow_fwags);
	wogio->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	wogio->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	wogio->powt_id[1] = sp->fcpowt->d_id.b.awea;
	wogio->powt_id[2] = sp->fcpowt->d_id.b.domain;
	wogio->vp_index = sp->vha->vp_idx;
}

static void
qwa2x00_wogout_iocb(swb_t *sp, stwuct mbx_entwy *mbx)
{
	stwuct qwa_hw_data *ha = sp->vha->hw;

	mbx->entwy_type = MBX_IOCB_TYPE;
	SET_TAWGET_ID(ha, mbx->woop_id, sp->fcpowt->woop_id);
	mbx->mb0 = cpu_to_we16(MBC_WOGOUT_FABWIC_POWT);
	mbx->mb1 = HAS_EXTENDED_IDS(ha) ?
	    cpu_to_we16(sp->fcpowt->woop_id) :
	    cpu_to_we16(sp->fcpowt->woop_id << 8);
	mbx->mb2 = cpu_to_we16(sp->fcpowt->d_id.b.domain);
	mbx->mb3 = cpu_to_we16(sp->fcpowt->d_id.b.awea << 8 |
	    sp->fcpowt->d_id.b.aw_pa);
	mbx->mb9 = cpu_to_we16(sp->vha->vp_idx);
	/* Impwicit: mbx->mbx10 = 0. */
}

static void
qwa24xx_adisc_iocb(swb_t *sp, stwuct wogio_entwy_24xx *wogio)
{
	wogio->entwy_type = WOGINOUT_POWT_IOCB_TYPE;
	wogio->contwow_fwags = cpu_to_we16(WCF_COMMAND_ADISC);
	wogio->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	wogio->vp_index = sp->vha->vp_idx;
}

static void
qwa2x00_adisc_iocb(swb_t *sp, stwuct mbx_entwy *mbx)
{
	stwuct qwa_hw_data *ha = sp->vha->hw;

	mbx->entwy_type = MBX_IOCB_TYPE;
	SET_TAWGET_ID(ha, mbx->woop_id, sp->fcpowt->woop_id);
	mbx->mb0 = cpu_to_we16(MBC_GET_POWT_DATABASE);
	if (HAS_EXTENDED_IDS(ha)) {
		mbx->mb1 = cpu_to_we16(sp->fcpowt->woop_id);
		mbx->mb10 = cpu_to_we16(BIT_0);
	} ewse {
		mbx->mb1 = cpu_to_we16((sp->fcpowt->woop_id << 8) | BIT_0);
	}
	mbx->mb2 = cpu_to_we16(MSW(ha->async_pd_dma));
	mbx->mb3 = cpu_to_we16(WSW(ha->async_pd_dma));
	mbx->mb6 = cpu_to_we16(MSW(MSD(ha->async_pd_dma)));
	mbx->mb7 = cpu_to_we16(WSW(MSD(ha->async_pd_dma)));
	mbx->mb9 = cpu_to_we16(sp->vha->vp_idx);
}

static void
qwa24xx_tm_iocb(swb_t *sp, stwuct tsk_mgmt_entwy *tsk)
{
	uint32_t fwags;
	uint64_t wun;
	stwuct fc_powt *fcpowt = sp->fcpowt;
	scsi_qwa_host_t *vha = fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct swb_iocb *iocb = &sp->u.iocb_cmd;
	stwuct weq_que *weq = sp->qpaiw->weq;

	fwags = iocb->u.tmf.fwags;
	wun = iocb->u.tmf.wun;

	tsk->entwy_type = TSK_MGMT_IOCB_TYPE;
	tsk->entwy_count = 1;
	tsk->handwe = make_handwe(weq->id, tsk->handwe);
	tsk->npowt_handwe = cpu_to_we16(fcpowt->woop_id);
	tsk->timeout = cpu_to_we16(ha->w_a_tov / 10 * 2);
	tsk->contwow_fwags = cpu_to_we32(fwags);
	tsk->powt_id[0] = fcpowt->d_id.b.aw_pa;
	tsk->powt_id[1] = fcpowt->d_id.b.awea;
	tsk->powt_id[2] = fcpowt->d_id.b.domain;
	tsk->vp_index = fcpowt->vha->vp_idx;

	if (fwags & (TCF_WUN_WESET | TCF_ABOWT_TASK_SET|
	    TCF_CWEAW_TASK_SET|TCF_CWEAW_ACA)) {
		int_to_scsiwun(wun, &tsk->wun);
		host_to_fcp_swap((uint8_t *)&tsk->wun,
			sizeof(tsk->wun));
	}
}

static void
qwa2x00_async_done(stwuct swb *sp, int wes)
{
	if (dew_timew(&sp->u.iocb_cmd.timew)) {
		/*
		 * Successfuwwy cancewwed the timeout handwew
		 * wef: TMW
		 */
		if (kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease))
			wetuwn;
	}
	sp->async_done(sp, wes);
}

void
qwa2x00_sp_wewease(stwuct kwef *kwef)
{
	stwuct swb *sp = containew_of(kwef, stwuct swb, cmd_kwef);

	sp->fwee(sp);
}

void
qwa2x00_init_async_sp(swb_t *sp, unsigned wong tmo,
		     void (*done)(stwuct swb *sp, int wes))
{
	timew_setup(&sp->u.iocb_cmd.timew, qwa2x00_sp_timeout, 0);
	sp->done = qwa2x00_async_done;
	sp->async_done = done;
	sp->fwee = qwa2x00_sp_fwee;
	sp->u.iocb_cmd.timeout = qwa2x00_async_iocb_timeout;
	sp->u.iocb_cmd.timew.expiwes = jiffies + tmo * HZ;
	if (IS_QWAFX00(sp->vha->hw) && sp->type == SWB_FXIOCB_DCMD)
		init_compwetion(&sp->u.iocb_cmd.u.fxiocb.fxiocb_comp);
	sp->stawt_timew = 1;
}

static void qwa2x00_ews_dcmd_sp_fwee(swb_t *sp)
{
	stwuct swb_iocb *ewsio = &sp->u.iocb_cmd;

	kfwee(sp->fcpowt);

	if (ewsio->u.ews_wogo.ews_wogo_pywd)
		dma_fwee_cohewent(&sp->vha->hw->pdev->dev, DMA_POOW_SIZE,
		    ewsio->u.ews_wogo.ews_wogo_pywd,
		    ewsio->u.ews_wogo.ews_wogo_pywd_dma);

	dew_timew(&ewsio->timew);
	qwa2x00_wew_sp(sp);
}

static void
qwa2x00_ews_dcmd_iocb_timeout(void *data)
{
	swb_t *sp = data;
	fc_powt_t *fcpowt = sp->fcpowt;
	stwuct scsi_qwa_host *vha = sp->vha;
	stwuct swb_iocb *wio = &sp->u.iocb_cmd;
	unsigned wong fwags = 0;
	int wes, h;

	qw_dbg(qw_dbg_io, vha, 0x3069,
	    "%s Timeout, hdw=%x, powtid=%02x%02x%02x\n",
	    sp->name, sp->handwe, fcpowt->d_id.b.domain, fcpowt->d_id.b.awea,
	    fcpowt->d_id.b.aw_pa);

	/* Abowt the exchange */
	wes = qwa24xx_async_abowt_cmd(sp, fawse);
	if (wes) {
		qw_dbg(qw_dbg_io, vha, 0x3070,
		    "mbx abowt_command faiwed.\n");
		spin_wock_iwqsave(sp->qpaiw->qp_wock_ptw, fwags);
		fow (h = 1; h < sp->qpaiw->weq->num_outstanding_cmds; h++) {
			if (sp->qpaiw->weq->outstanding_cmds[h] == sp) {
				sp->qpaiw->weq->outstanding_cmds[h] = NUWW;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(sp->qpaiw->qp_wock_ptw, fwags);
		compwete(&wio->u.ews_wogo.comp);
	} ewse {
		qw_dbg(qw_dbg_io, vha, 0x3071,
		    "mbx abowt_command success.\n");
	}
}

static void qwa2x00_ews_dcmd_sp_done(swb_t *sp, int wes)
{
	fc_powt_t *fcpowt = sp->fcpowt;
	stwuct swb_iocb *wio = &sp->u.iocb_cmd;
	stwuct scsi_qwa_host *vha = sp->vha;

	qw_dbg(qw_dbg_io, vha, 0x3072,
	    "%s hdw=%x, powtid=%02x%02x%02x done\n",
	    sp->name, sp->handwe, fcpowt->d_id.b.domain,
	    fcpowt->d_id.b.awea, fcpowt->d_id.b.aw_pa);

	compwete(&wio->u.ews_wogo.comp);
}

int
qwa24xx_ews_dcmd_iocb(scsi_qwa_host_t *vha, int ews_opcode,
    powt_id_t wemote_did)
{
	swb_t *sp;
	fc_powt_t *fcpowt = NUWW;
	stwuct swb_iocb *ewsio = NUWW;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct ews_wogo_paywoad wogo_pywd;
	int wvaw = QWA_SUCCESS;

	fcpowt = qwa2x00_awwoc_fcpowt(vha, GFP_KEWNEW);
	if (!fcpowt) {
	       qw_wog(qw_wog_info, vha, 0x70e5, "fcpowt awwocation faiwed\n");
	       wetuwn -ENOMEM;
	}

	/* Awwoc SWB stwuctuwe
	 * wef: INIT
	 */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		kfwee(fcpowt);
		qw_wog(qw_wog_info, vha, 0x70e6,
		 "SWB awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	ewsio = &sp->u.iocb_cmd;
	fcpowt->woop_id = 0xFFFF;
	fcpowt->d_id.b.domain = wemote_did.b.domain;
	fcpowt->d_id.b.awea = wemote_did.b.awea;
	fcpowt->d_id.b.aw_pa = wemote_did.b.aw_pa;

	qw_dbg(qw_dbg_io, vha, 0x3073, "powtid=%02x%02x%02x done\n",
	    fcpowt->d_id.b.domain, fcpowt->d_id.b.awea, fcpowt->d_id.b.aw_pa);

	sp->type = SWB_EWS_DCMD;
	sp->name = "EWS_DCMD";
	sp->fcpowt = fcpowt;
	qwa2x00_init_async_sp(sp, EWS_DCMD_TIMEOUT,
			      qwa2x00_ews_dcmd_sp_done);
	sp->fwee = qwa2x00_ews_dcmd_sp_fwee;
	sp->u.iocb_cmd.timeout = qwa2x00_ews_dcmd_iocb_timeout;
	init_compwetion(&sp->u.iocb_cmd.u.ews_wogo.comp);

	ewsio->u.ews_wogo.ews_wogo_pywd = dma_awwoc_cohewent(&ha->pdev->dev,
			    DMA_POOW_SIZE, &ewsio->u.ews_wogo.ews_wogo_pywd_dma,
			    GFP_KEWNEW);

	if (!ewsio->u.ews_wogo.ews_wogo_pywd) {
		/* wef: INIT */
		kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
		wetuwn QWA_FUNCTION_FAIWED;
	}

	memset(&wogo_pywd, 0, sizeof(stwuct ews_wogo_paywoad));

	ewsio->u.ews_wogo.ews_cmd = ews_opcode;
	wogo_pywd.opcode = ews_opcode;
	wogo_pywd.s_id[0] = vha->d_id.b.aw_pa;
	wogo_pywd.s_id[1] = vha->d_id.b.awea;
	wogo_pywd.s_id[2] = vha->d_id.b.domain;
	host_to_fcp_swap(wogo_pywd.s_id, sizeof(uint32_t));
	memcpy(&wogo_pywd.wwpn, vha->powt_name, WWN_SIZE);

	memcpy(ewsio->u.ews_wogo.ews_wogo_pywd, &wogo_pywd,
	    sizeof(stwuct ews_wogo_paywoad));
	qw_dbg(qw_dbg_disc + qw_dbg_buffew, vha, 0x3075, "WOGO buffew:");
	qw_dump_buffew(qw_dbg_disc + qw_dbg_buffew, vha, 0x010a,
		       ewsio->u.ews_wogo.ews_wogo_pywd,
		       sizeof(*ewsio->u.ews_wogo.ews_wogo_pywd));

	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		/* wef: INIT */
		kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
		wetuwn QWA_FUNCTION_FAIWED;
	}

	qw_dbg(qw_dbg_io, vha, 0x3074,
	    "%s WOGO sent, hdw=%x, woopid=%x, powtid=%02x%02x%02x.\n",
	    sp->name, sp->handwe, fcpowt->woop_id, fcpowt->d_id.b.domain,
	    fcpowt->d_id.b.awea, fcpowt->d_id.b.aw_pa);

	wait_fow_compwetion(&ewsio->u.ews_wogo.comp);

	/* wef: INIT */
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
	wetuwn wvaw;
}

static void
qwa24xx_ews_wogo_iocb(swb_t *sp, stwuct ews_entwy_24xx *ews_iocb)
{
	scsi_qwa_host_t *vha = sp->vha;
	stwuct swb_iocb *ewsio = &sp->u.iocb_cmd;

	ews_iocb->entwy_type = EWS_IOCB_TYPE;
	ews_iocb->entwy_count = 1;
	ews_iocb->sys_define = 0;
	ews_iocb->entwy_status = 0;
	ews_iocb->handwe = sp->handwe;
	ews_iocb->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	ews_iocb->tx_dsd_count = cpu_to_we16(1);
	ews_iocb->vp_index = vha->vp_idx;
	ews_iocb->sof_type = EST_SOFI3;
	ews_iocb->wx_dsd_count = 0;
	ews_iocb->opcode = ewsio->u.ews_wogo.ews_cmd;

	ews_iocb->d_id[0] = sp->fcpowt->d_id.b.aw_pa;
	ews_iocb->d_id[1] = sp->fcpowt->d_id.b.awea;
	ews_iocb->d_id[2] = sp->fcpowt->d_id.b.domain;
	/* Fow SID the byte owdew is diffewent than DID */
	ews_iocb->s_id[1] = vha->d_id.b.aw_pa;
	ews_iocb->s_id[2] = vha->d_id.b.awea;
	ews_iocb->s_id[0] = vha->d_id.b.domain;

	if (ewsio->u.ews_wogo.ews_cmd == EWS_DCMD_PWOGI) {
		if (vha->hw->fwags.edif_enabwed)
			ews_iocb->contwow_fwags = cpu_to_we16(ECF_SEC_WOGIN);
		ewse
			ews_iocb->contwow_fwags = 0;
		ews_iocb->tx_byte_count = ews_iocb->tx_wen =
			cpu_to_we32(sizeof(stwuct ews_pwogi_paywoad));
		put_unawigned_we64(ewsio->u.ews_pwogi.ews_pwogi_pywd_dma,
				   &ews_iocb->tx_addwess);
		ews_iocb->wx_dsd_count = cpu_to_we16(1);
		ews_iocb->wx_byte_count = ews_iocb->wx_wen =
			cpu_to_we32(sizeof(stwuct ews_pwogi_paywoad));
		put_unawigned_we64(ewsio->u.ews_pwogi.ews_wesp_pywd_dma,
				   &ews_iocb->wx_addwess);

		qw_dbg(qw_dbg_io + qw_dbg_buffew, vha, 0x3073,
		    "PWOGI EWS IOCB:\n");
		qw_dump_buffew(qw_wog_info, vha, 0x0109,
		    (uint8_t *)ews_iocb,
		    sizeof(*ews_iocb));
	} ewse {
		ews_iocb->tx_byte_count =
			cpu_to_we32(sizeof(stwuct ews_wogo_paywoad));
		put_unawigned_we64(ewsio->u.ews_wogo.ews_wogo_pywd_dma,
				   &ews_iocb->tx_addwess);
		ews_iocb->tx_wen = cpu_to_we32(sizeof(stwuct ews_wogo_paywoad));

		ews_iocb->wx_byte_count = 0;
		ews_iocb->wx_addwess = 0;
		ews_iocb->wx_wen = 0;
		qw_dbg(qw_dbg_io + qw_dbg_buffew, vha, 0x3076,
		       "WOGO EWS IOCB:");
		qw_dump_buffew(qw_wog_info, vha, 0x010b,
			       ews_iocb,
			       sizeof(*ews_iocb));
	}

	sp->vha->qwa_stats.contwow_wequests++;
}

void
qwa2x00_ews_dcmd2_iocb_timeout(void *data)
{
	swb_t *sp = data;
	fc_powt_t *fcpowt = sp->fcpowt;
	stwuct scsi_qwa_host *vha = sp->vha;
	unsigned wong fwags = 0;
	int wes, h;

	qw_dbg(qw_dbg_io + qw_dbg_disc, vha, 0x3069,
	    "%s hdw=%x EWS Timeout, %8phC powtid=%06x\n",
	    sp->name, sp->handwe, fcpowt->powt_name, fcpowt->d_id.b24);

	/* Abowt the exchange */
	wes = qwa24xx_async_abowt_cmd(sp, fawse);
	qw_dbg(qw_dbg_io, vha, 0x3070,
	    "mbx abowt_command %s\n",
	    (wes == QWA_SUCCESS) ? "successfuw" : "faiwed");
	if (wes) {
		spin_wock_iwqsave(sp->qpaiw->qp_wock_ptw, fwags);
		fow (h = 1; h < sp->qpaiw->weq->num_outstanding_cmds; h++) {
			if (sp->qpaiw->weq->outstanding_cmds[h] == sp) {
				sp->qpaiw->weq->outstanding_cmds[h] = NUWW;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(sp->qpaiw->qp_wock_ptw, fwags);
		sp->done(sp, QWA_FUNCTION_TIMEOUT);
	}
}

void qwa2x00_ews_dcmd2_fwee(scsi_qwa_host_t *vha, stwuct ews_pwogi *ews_pwogi)
{
	if (ews_pwogi->ews_pwogi_pywd)
		dma_fwee_cohewent(&vha->hw->pdev->dev,
				  ews_pwogi->tx_size,
				  ews_pwogi->ews_pwogi_pywd,
				  ews_pwogi->ews_pwogi_pywd_dma);

	if (ews_pwogi->ews_wesp_pywd)
		dma_fwee_cohewent(&vha->hw->pdev->dev,
				  ews_pwogi->wx_size,
				  ews_pwogi->ews_wesp_pywd,
				  ews_pwogi->ews_wesp_pywd_dma);
}

static void qwa2x00_ews_dcmd2_sp_done(swb_t *sp, int wes)
{
	fc_powt_t *fcpowt = sp->fcpowt;
	stwuct swb_iocb *wio = &sp->u.iocb_cmd;
	stwuct scsi_qwa_host *vha = sp->vha;
	stwuct event_awg ea;
	stwuct qwa_wowk_evt *e;
	stwuct fc_powt *confwict_fcpowt;
	powt_id_t cid;	/* confwict Npowt id */
	const __we32 *fw_status = sp->u.iocb_cmd.u.ews_pwogi.fw_status;
	u16 wid;

	qw_dbg(qw_dbg_disc, vha, 0x3072,
	    "%s EWS done wc %d hdw=%x, powtid=%06x %8phC\n",
	    sp->name, wes, sp->handwe, fcpowt->d_id.b24, fcpowt->powt_name);

	fcpowt->fwags &= ~(FCF_ASYNC_SENT|FCF_ASYNC_ACTIVE);
	/* Fow edif, set wogout on dewete to ensuwe any wesiduaw key fwom FW is fwushed.*/
	fcpowt->wogout_on_dewete = 1;
	fcpowt->chip_weset = vha->hw->base_qpaiw->chip_weset;

	if (sp->fwags & SWB_WAKEUP_ON_COMP)
		compwete(&wio->u.ews_pwogi.comp);
	ewse {
		switch (we32_to_cpu(fw_status[0])) {
		case CS_DATA_UNDEWWUN:
		case CS_COMPWETE:
			memset(&ea, 0, sizeof(ea));
			ea.fcpowt = fcpowt;
			ea.wc = wes;
			qwa_handwe_ews_pwogi_done(vha, &ea);
			bweak;

		case CS_IOCB_EWWOW:
			switch (we32_to_cpu(fw_status[1])) {
			case WSC_SCODE_POWTID_USED:
				wid = we32_to_cpu(fw_status[2]) & 0xffff;
				qwt_find_sess_invawidate_othew(vha,
				    wwn_to_u64(fcpowt->powt_name),
				    fcpowt->d_id, wid, &confwict_fcpowt);
				if (confwict_fcpowt) {
					/*
					 * Anothew fcpowt shawes the same
					 * woop_id & npowt id; confwict
					 * fcpowt needs to finish cweanup
					 * befowe this fcpowt can pwoceed
					 * to wogin.
					 */
					confwict_fcpowt->confwict = fcpowt;
					fcpowt->wogin_pause = 1;
					qw_dbg(qw_dbg_disc, vha, 0x20ed,
					    "%s %d %8phC pid %06x inuse with wid %#x.\n",
					    __func__, __WINE__,
					    fcpowt->powt_name,
					    fcpowt->d_id.b24, wid);
				} ewse {
					qw_dbg(qw_dbg_disc, vha, 0x20ed,
					    "%s %d %8phC pid %06x inuse with wid %#x sched dew\n",
					    __func__, __WINE__,
					    fcpowt->powt_name,
					    fcpowt->d_id.b24, wid);
					qwa2x00_cweaw_woop_id(fcpowt);
					set_bit(wid, vha->hw->woop_id_map);
					fcpowt->woop_id = wid;
					fcpowt->keep_npowt_handwe = 0;
					qwt_scheduwe_sess_fow_dewetion(fcpowt);
				}
				bweak;

			case WSC_SCODE_NPOWT_USED:
				cid.b.domain = (we32_to_cpu(fw_status[2]) >> 16)
					& 0xff;
				cid.b.awea   = (we32_to_cpu(fw_status[2]) >>  8)
					& 0xff;
				cid.b.aw_pa  = we32_to_cpu(fw_status[2]) & 0xff;
				cid.b.wsvd_1 = 0;

				qw_dbg(qw_dbg_disc, vha, 0x20ec,
				    "%s %d %8phC wid %#x in use with pid %06x post gnw\n",
				    __func__, __WINE__, fcpowt->powt_name,
				    fcpowt->woop_id, cid.b24);
				set_bit(fcpowt->woop_id,
				    vha->hw->woop_id_map);
				fcpowt->woop_id = FC_NO_WOOP_ID;
				qwa24xx_post_gnw_wowk(vha, fcpowt);
				bweak;

			case WSC_SCODE_NOXCB:
				vha->hw->exch_stawvation++;
				if (vha->hw->exch_stawvation > 5) {
					qw_wog(qw_wog_wawn, vha, 0xd046,
					    "Exchange stawvation. Wesetting WISC\n");
					vha->hw->exch_stawvation = 0;
					set_bit(ISP_ABOWT_NEEDED,
					    &vha->dpc_fwags);
					qwa2xxx_wake_dpc(vha);
					bweak;
				}
				fawwthwough;
			defauwt:
				qw_dbg(qw_dbg_disc, vha, 0x20eb,
				    "%s %8phC cmd ewwow fw_status 0x%x 0x%x 0x%x\n",
				    __func__, sp->fcpowt->powt_name,
				    fw_status[0], fw_status[1], fw_status[2]);

				fcpowt->fwags &= ~FCF_ASYNC_SENT;
				qwt_scheduwe_sess_fow_dewetion(fcpowt);
				bweak;
			}
			bweak;

		defauwt:
			qw_dbg(qw_dbg_disc, vha, 0x20eb,
			    "%s %8phC cmd ewwow 2 fw_status 0x%x 0x%x 0x%x\n",
			    __func__, sp->fcpowt->powt_name,
			    fw_status[0], fw_status[1], fw_status[2]);

			sp->fcpowt->fwags &= ~FCF_ASYNC_SENT;
			qwt_scheduwe_sess_fow_dewetion(fcpowt);
			bweak;
		}

		e = qwa2x00_awwoc_wowk(vha, QWA_EVT_UNMAP);
		if (!e) {
			stwuct swb_iocb *ewsio = &sp->u.iocb_cmd;

			qwa2x00_ews_dcmd2_fwee(vha, &ewsio->u.ews_pwogi);
			/* wef: INIT */
			kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
			wetuwn;
		}
		e->u.iosb.sp = sp;
		qwa2x00_post_wowk(vha, e);
	}
}

int
qwa24xx_ews_dcmd2_iocb(scsi_qwa_host_t *vha, int ews_opcode,
    fc_powt_t *fcpowt, boow wait)
{
	swb_t *sp;
	stwuct swb_iocb *ewsio = NUWW;
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = QWA_SUCCESS;
	void	*ptw, *wesp_ptw;

	/* Awwoc SWB stwuctuwe
	 * wef: INIT
	 */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		qw_wog(qw_wog_info, vha, 0x70e6,
		 "SWB awwocation faiwed\n");
		fcpowt->fwags &= ~FCF_ASYNC_ACTIVE;
		wetuwn -ENOMEM;
	}

	fcpowt->fwags |= FCF_ASYNC_SENT;
	qwa2x00_set_fcpowt_disc_state(fcpowt, DSC_WOGIN_PEND);
	ewsio = &sp->u.iocb_cmd;
	qw_dbg(qw_dbg_io, vha, 0x3073,
	       "%s Entew: PWOGI powtid=%06x\n", __func__, fcpowt->d_id.b24);

	if (wait)
		sp->fwags = SWB_WAKEUP_ON_COMP;

	sp->type = SWB_EWS_DCMD;
	sp->name = "EWS_DCMD";
	sp->fcpowt = fcpowt;
	qwa2x00_init_async_sp(sp, EWS_DCMD_TIMEOUT + 2,
			     qwa2x00_ews_dcmd2_sp_done);
	sp->u.iocb_cmd.timeout = qwa2x00_ews_dcmd2_iocb_timeout;

	ewsio->u.ews_pwogi.tx_size = ewsio->u.ews_pwogi.wx_size = DMA_POOW_SIZE;

	ptw = ewsio->u.ews_pwogi.ews_pwogi_pywd =
	    dma_awwoc_cohewent(&ha->pdev->dev, ewsio->u.ews_pwogi.tx_size,
		&ewsio->u.ews_pwogi.ews_pwogi_pywd_dma, GFP_KEWNEW);

	if (!ewsio->u.ews_pwogi.ews_pwogi_pywd) {
		wvaw = QWA_FUNCTION_FAIWED;
		goto out;
	}

	wesp_ptw = ewsio->u.ews_pwogi.ews_wesp_pywd =
	    dma_awwoc_cohewent(&ha->pdev->dev, ewsio->u.ews_pwogi.wx_size,
		&ewsio->u.ews_pwogi.ews_wesp_pywd_dma, GFP_KEWNEW);

	if (!ewsio->u.ews_pwogi.ews_wesp_pywd) {
		wvaw = QWA_FUNCTION_FAIWED;
		goto out;
	}

	qw_dbg(qw_dbg_io, vha, 0x3073, "PWOGI %p %p\n", ptw, wesp_ptw);

	memset(ptw, 0, sizeof(stwuct ews_pwogi_paywoad));
	memset(wesp_ptw, 0, sizeof(stwuct ews_pwogi_paywoad));
	memcpy(ewsio->u.ews_pwogi.ews_pwogi_pywd->data,
	       (void *)&ha->pwogi_ews_paywd + offsetof(stwuct fc_ews_fwogi, fw_csp),
	       sizeof(ha->pwogi_ews_paywd) - offsetof(stwuct fc_ews_fwogi, fw_csp));

	ewsio->u.ews_pwogi.ews_cmd = ews_opcode;
	ewsio->u.ews_pwogi.ews_pwogi_pywd->opcode = ews_opcode;

	if (ews_opcode == EWS_DCMD_PWOGI && DBEWW_ACTIVE(vha)) {
		stwuct fc_ews_fwogi *p = ptw;

		p->fw_csp.sp_featuwes |= cpu_to_be16(FC_SP_FT_SEC);
	}

	qw_dbg(qw_dbg_disc + qw_dbg_buffew, vha, 0x3073, "PWOGI buffew:\n");
	qw_dump_buffew(qw_dbg_disc + qw_dbg_buffew, vha, 0x0109,
	    (uint8_t *)ewsio->u.ews_pwogi.ews_pwogi_pywd,
	    sizeof(*ewsio->u.ews_pwogi.ews_pwogi_pywd));

	init_compwetion(&ewsio->u.ews_pwogi.comp);
	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		wvaw = QWA_FUNCTION_FAIWED;
	} ewse {
		qw_dbg(qw_dbg_disc, vha, 0x3074,
		    "%s PWOGI sent, hdw=%x, woopid=%x, to powt_id %06x fwom powt_id %06x\n",
		    sp->name, sp->handwe, fcpowt->woop_id,
		    fcpowt->d_id.b24, vha->d_id.b24);
	}

	if (wait) {
		wait_fow_compwetion(&ewsio->u.ews_pwogi.comp);

		if (ewsio->u.ews_pwogi.comp_status != CS_COMPWETE)
			wvaw = QWA_FUNCTION_FAIWED;
	} ewse {
		goto done;
	}

out:
	fcpowt->fwags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	qwa2x00_ews_dcmd2_fwee(vha, &ewsio->u.ews_pwogi);
	/* wef: INIT */
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
done:
	wetuwn wvaw;
}

/* it is assume qpaiw wock is hewd */
void qwa_ews_pt_iocb(stwuct scsi_qwa_host *vha,
	stwuct ews_entwy_24xx *ews_iocb,
	stwuct qwa_ews_pt_awg *a)
{
	ews_iocb->entwy_type = EWS_IOCB_TYPE;
	ews_iocb->entwy_count = 1;
	ews_iocb->sys_define = 0;
	ews_iocb->entwy_status = 0;
	ews_iocb->handwe = QWA_SKIP_HANDWE;
	ews_iocb->npowt_handwe = a->npowt_handwe;
	ews_iocb->wx_xchg_addwess = a->wx_xchg_addwess;
	ews_iocb->tx_dsd_count = cpu_to_we16(1);
	ews_iocb->vp_index = a->vp_idx;
	ews_iocb->sof_type = EST_SOFI3;
	ews_iocb->wx_dsd_count = cpu_to_we16(0);
	ews_iocb->opcode = a->ews_opcode;

	ews_iocb->d_id[0] = a->did.b.aw_pa;
	ews_iocb->d_id[1] = a->did.b.awea;
	ews_iocb->d_id[2] = a->did.b.domain;
	/* Fow SID the byte owdew is diffewent than DID */
	ews_iocb->s_id[1] = vha->d_id.b.aw_pa;
	ews_iocb->s_id[2] = vha->d_id.b.awea;
	ews_iocb->s_id[0] = vha->d_id.b.domain;

	ews_iocb->contwow_fwags = cpu_to_we16(a->contwow_fwags);

	ews_iocb->tx_byte_count = cpu_to_we32(a->tx_byte_count);
	ews_iocb->tx_wen = cpu_to_we32(a->tx_wen);
	put_unawigned_we64(a->tx_addw, &ews_iocb->tx_addwess);

	ews_iocb->wx_byte_count = cpu_to_we32(a->wx_byte_count);
	ews_iocb->wx_wen = cpu_to_we32(a->wx_wen);
	put_unawigned_we64(a->wx_addw, &ews_iocb->wx_addwess);
}

static void
qwa24xx_ews_iocb(swb_t *sp, stwuct ews_entwy_24xx *ews_iocb)
{
	stwuct bsg_job *bsg_job = sp->u.bsg_job;
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;

        ews_iocb->entwy_type = EWS_IOCB_TYPE;
        ews_iocb->entwy_count = 1;
        ews_iocb->sys_define = 0;
        ews_iocb->entwy_status = 0;
        ews_iocb->handwe = sp->handwe;
	ews_iocb->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	ews_iocb->tx_dsd_count = cpu_to_we16(bsg_job->wequest_paywoad.sg_cnt);
	ews_iocb->vp_index = sp->vha->vp_idx;
        ews_iocb->sof_type = EST_SOFI3;
	ews_iocb->wx_dsd_count = cpu_to_we16(bsg_job->wepwy_paywoad.sg_cnt);

	ews_iocb->opcode =
	    sp->type == SWB_EWS_CMD_WPT ?
	    bsg_wequest->wqst_data.w_ews.ews_code :
	    bsg_wequest->wqst_data.h_ews.command_code;
	ews_iocb->d_id[0] = sp->fcpowt->d_id.b.aw_pa;
	ews_iocb->d_id[1] = sp->fcpowt->d_id.b.awea;
	ews_iocb->d_id[2] = sp->fcpowt->d_id.b.domain;
        ews_iocb->contwow_fwags = 0;
        ews_iocb->wx_byte_count =
            cpu_to_we32(bsg_job->wepwy_paywoad.paywoad_wen);
        ews_iocb->tx_byte_count =
            cpu_to_we32(bsg_job->wequest_paywoad.paywoad_wen);

	put_unawigned_we64(sg_dma_addwess(bsg_job->wequest_paywoad.sg_wist),
			   &ews_iocb->tx_addwess);
        ews_iocb->tx_wen = cpu_to_we32(sg_dma_wen
            (bsg_job->wequest_paywoad.sg_wist));

	put_unawigned_we64(sg_dma_addwess(bsg_job->wepwy_paywoad.sg_wist),
			   &ews_iocb->wx_addwess);
        ews_iocb->wx_wen = cpu_to_we32(sg_dma_wen
            (bsg_job->wepwy_paywoad.sg_wist));

	sp->vha->qwa_stats.contwow_wequests++;
}

static void
qwa2x00_ct_iocb(swb_t *sp, ms_iocb_entwy_t *ct_iocb)
{
	uint16_t        avaiw_dsds;
	stwuct dsd64	*cuw_dsd;
	stwuct scattewwist *sg;
	int index;
	uint16_t tot_dsds;
	scsi_qwa_host_t *vha = sp->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct bsg_job *bsg_job = sp->u.bsg_job;
	int entwy_count = 1;

	memset(ct_iocb, 0, sizeof(ms_iocb_entwy_t));
	ct_iocb->entwy_type = CT_IOCB_TYPE;
	ct_iocb->entwy_status = 0;
	ct_iocb->handwe1 = sp->handwe;
	SET_TAWGET_ID(ha, ct_iocb->woop_id, sp->fcpowt->woop_id);
	ct_iocb->status = cpu_to_we16(0);
	ct_iocb->contwow_fwags = cpu_to_we16(0);
	ct_iocb->timeout = 0;
	ct_iocb->cmd_dsd_count =
	    cpu_to_we16(bsg_job->wequest_paywoad.sg_cnt);
	ct_iocb->totaw_dsd_count =
	    cpu_to_we16(bsg_job->wequest_paywoad.sg_cnt + 1);
	ct_iocb->weq_bytecount =
	    cpu_to_we32(bsg_job->wequest_paywoad.paywoad_wen);
	ct_iocb->wsp_bytecount =
	    cpu_to_we32(bsg_job->wepwy_paywoad.paywoad_wen);

	put_unawigned_we64(sg_dma_addwess(bsg_job->wequest_paywoad.sg_wist),
			   &ct_iocb->weq_dsd.addwess);
	ct_iocb->weq_dsd.wength = ct_iocb->weq_bytecount;

	put_unawigned_we64(sg_dma_addwess(bsg_job->wepwy_paywoad.sg_wist),
			   &ct_iocb->wsp_dsd.addwess);
	ct_iocb->wsp_dsd.wength = ct_iocb->wsp_bytecount;

	avaiw_dsds = 1;
	cuw_dsd = &ct_iocb->wsp_dsd;
	index = 0;
	tot_dsds = bsg_job->wepwy_paywoad.sg_cnt;

	fow_each_sg(bsg_job->wepwy_paywoad.sg_wist, sg, tot_dsds, index) {
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			* Five DSDs awe avaiwabwe in the Cont.
			* Type 1 IOCB.
			       */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha,
			    vha->hw->weq_q_map[0]);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = 5;
			entwy_count++;
		}

		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}
	ct_iocb->entwy_count = entwy_count;

	sp->vha->qwa_stats.contwow_wequests++;
}

static void
qwa24xx_ct_iocb(swb_t *sp, stwuct ct_entwy_24xx *ct_iocb)
{
	uint16_t        avaiw_dsds;
	stwuct dsd64	*cuw_dsd;
	stwuct scattewwist *sg;
	int index;
	uint16_t cmd_dsds, wsp_dsds;
	scsi_qwa_host_t *vha = sp->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct bsg_job *bsg_job = sp->u.bsg_job;
	int entwy_count = 1;
	cont_a64_entwy_t *cont_pkt = NUWW;

	ct_iocb->entwy_type = CT_IOCB_TYPE;
        ct_iocb->entwy_status = 0;
        ct_iocb->sys_define = 0;
        ct_iocb->handwe = sp->handwe;

	ct_iocb->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	ct_iocb->vp_index = sp->vha->vp_idx;
	ct_iocb->comp_status = cpu_to_we16(0);

	cmd_dsds = bsg_job->wequest_paywoad.sg_cnt;
	wsp_dsds = bsg_job->wepwy_paywoad.sg_cnt;

	ct_iocb->cmd_dsd_count = cpu_to_we16(cmd_dsds);
        ct_iocb->timeout = 0;
	ct_iocb->wsp_dsd_count = cpu_to_we16(wsp_dsds);
        ct_iocb->cmd_byte_count =
            cpu_to_we32(bsg_job->wequest_paywoad.paywoad_wen);

	avaiw_dsds = 2;
	cuw_dsd = ct_iocb->dsd;
	index = 0;

	fow_each_sg(bsg_job->wequest_paywoad.sg_wist, sg, cmd_dsds, index) {
		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			 * Five DSDs awe avaiwabwe in the Cont.
			 * Type 1 IOCB.
			 */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(
			    vha, ha->weq_q_map[0]);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = 5;
			entwy_count++;
		}

		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}

	index = 0;

	fow_each_sg(bsg_job->wepwy_paywoad.sg_wist, sg, wsp_dsds, index) {
		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			* Five DSDs awe avaiwabwe in the Cont.
			* Type 1 IOCB.
			       */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha,
			    ha->weq_q_map[0]);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = 5;
			entwy_count++;
		}

		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}
        ct_iocb->entwy_count = entwy_count;
}

/*
 * qwa82xx_stawt_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
int
qwa82xx_stawt_scsi(swb_t *sp)
{
	int		nseg;
	unsigned wong   fwags;
	stwuct scsi_cmnd *cmd;
	uint32_t	*cww_ptw;
	uint32_t	handwe;
	uint16_t	cnt;
	uint16_t	weq_cnt;
	uint16_t	tot_dsds;
	stwuct device_weg_82xx __iomem *weg;
	uint32_t dbvaw;
	__be32 *fcp_dw;
	uint8_t additionaw_cdb_wen;
	stwuct ct6_dsd *ctx;
	stwuct scsi_qwa_host *vha = sp->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct weq_que *weq = NUWW;
	stwuct wsp_que *wsp = NUWW;
	stwuct qwa_qpaiw *qpaiw = sp->qpaiw;

	/* Setup device pointews. */
	weg = &ha->iobase->isp82;
	cmd = GET_CMD_SP(sp);
	weq = vha->weq;
	wsp = ha->wsp_q_map[0];

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	dbvaw = 0x04 | (ha->powtnum << 5);

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (qwa2x00_mawkew(vha, ha->base_qpaiw,
			0, 0, MK_SYNC_AWW) != QWA_SUCCESS) {
			qw_wog(qw_wog_wawn, vha, 0x300c,
			    "qwa2x00_mawkew faiwed fow cmd=%p.\n", cmd);
			wetuwn QWA_FUNCTION_FAIWED;
		}
		vha->mawkew_needed = 0;
	}

	/* Acquiwe wing specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
	} ewse
		nseg = 0;

	tot_dsds = nseg;

	if (tot_dsds > qw2xshiftctondsd) {
		stwuct cmd_type_6 *cmd_pkt;
		uint16_t mowe_dsd_wists = 0;
		stwuct dsd_dma *dsd_ptw;
		uint16_t i;

		mowe_dsd_wists = qwa24xx_cawc_dsd_wists(tot_dsds);
		if ((mowe_dsd_wists + qpaiw->dsd_inuse) >= NUM_DSD_CHAIN) {
			qw_dbg(qw_dbg_io, vha, 0x300d,
			    "Num of DSD wist %d is than %d fow cmd=%p.\n",
			    mowe_dsd_wists + qpaiw->dsd_inuse, NUM_DSD_CHAIN,
			    cmd);
			goto queuing_ewwow;
		}

		if (mowe_dsd_wists <= qpaiw->dsd_avaiw)
			goto sufficient_dsds;
		ewse
			mowe_dsd_wists -= qpaiw->dsd_avaiw;

		fow (i = 0; i < mowe_dsd_wists; i++) {
			dsd_ptw = kzawwoc(sizeof(stwuct dsd_dma), GFP_ATOMIC);
			if (!dsd_ptw) {
				qw_wog(qw_wog_fataw, vha, 0x300e,
				    "Faiwed to awwocate memowy fow dsd_dma "
				    "fow cmd=%p.\n", cmd);
				goto queuing_ewwow;
			}

			dsd_ptw->dsd_addw = dma_poow_awwoc(ha->dw_dma_poow,
				GFP_ATOMIC, &dsd_ptw->dsd_wist_dma);
			if (!dsd_ptw->dsd_addw) {
				kfwee(dsd_ptw);
				qw_wog(qw_wog_fataw, vha, 0x300f,
				    "Faiwed to awwocate memowy fow dsd_addw "
				    "fow cmd=%p.\n", cmd);
				goto queuing_ewwow;
			}
			wist_add_taiw(&dsd_ptw->wist, &qpaiw->dsd_wist);
			qpaiw->dsd_avaiw++;
		}

sufficient_dsds:
		weq_cnt = 1;

		if (weq->cnt < (weq_cnt + 2)) {
			cnt = (uint16_t)wd_weg_dwowd_wewaxed(
				&weg->weq_q_out[0]);
			if (weq->wing_index < cnt)
				weq->cnt = cnt - weq->wing_index;
			ewse
				weq->cnt = weq->wength -
					(weq->wing_index - cnt);
			if (weq->cnt < (weq_cnt + 2))
				goto queuing_ewwow;
		}

		ctx = &sp->u.scmd.ct6_ctx;

		memset(ctx, 0, sizeof(stwuct ct6_dsd));
		ctx->fcp_cmnd = dma_poow_zawwoc(ha->fcp_cmnd_dma_poow,
			GFP_ATOMIC, &ctx->fcp_cmnd_dma);
		if (!ctx->fcp_cmnd) {
			qw_wog(qw_wog_fataw, vha, 0x3011,
			    "Faiwed to awwocate fcp_cmnd fow cmd=%p.\n", cmd);
			goto queuing_ewwow;
		}

		/* Initiawize the DSD wist and dma handwe */
		INIT_WIST_HEAD(&ctx->dsd_wist);
		ctx->dsd_use_cnt = 0;

		if (cmd->cmd_wen > 16) {
			additionaw_cdb_wen = cmd->cmd_wen - 16;
			if ((cmd->cmd_wen % 4) != 0) {
				/* SCSI command biggew than 16 bytes must be
				 * muwtipwe of 4
				 */
				qw_wog(qw_wog_wawn, vha, 0x3012,
				    "scsi cmd wen %d not muwtipwe of 4 "
				    "fow cmd=%p.\n", cmd->cmd_wen, cmd);
				goto queuing_ewwow_fcp_cmnd;
			}
			ctx->fcp_cmnd_wen = 12 + cmd->cmd_wen + 4;
		} ewse {
			additionaw_cdb_wen = 0;
			ctx->fcp_cmnd_wen = 12 + 16 + 4;
		}

		cmd_pkt = (stwuct cmd_type_6 *)weq->wing_ptw;
		cmd_pkt->handwe = make_handwe(weq->id, handwe);

		/* Zewo out wemaining powtion of packet. */
		/*    tagged queuing modifiew -- defauwt is TSK_SIMPWE (0). */
		cww_ptw = (uint32_t *)cmd_pkt + 2;
		memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
		cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

		/* Set NPOWT-ID and WUN numbew*/
		cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
		cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
		cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
		cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
		cmd_pkt->vp_index = sp->vha->vp_idx;

		/* Buiwd IOCB segments */
		if (qwa24xx_buiwd_scsi_type_6_iocbs(sp, cmd_pkt, tot_dsds))
			goto queuing_ewwow_fcp_cmnd;

		int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
		host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

		/* buiwd FCP_CMND IU */
		int_to_scsiwun(cmd->device->wun, &ctx->fcp_cmnd->wun);
		ctx->fcp_cmnd->additionaw_cdb_wen = additionaw_cdb_wen;

		if (cmd->sc_data_diwection == DMA_TO_DEVICE)
			ctx->fcp_cmnd->additionaw_cdb_wen |= 1;
		ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
			ctx->fcp_cmnd->additionaw_cdb_wen |= 2;

		/* Popuwate the FCP_PWIO. */
		if (ha->fwags.fcp_pwio_enabwed)
			ctx->fcp_cmnd->task_attwibute |=
			    sp->fcpowt->fcp_pwio << 3;

		memcpy(ctx->fcp_cmnd->cdb, cmd->cmnd, cmd->cmd_wen);

		fcp_dw = (__be32 *)(ctx->fcp_cmnd->cdb + 16 +
		    additionaw_cdb_wen);
		*fcp_dw = htonw((uint32_t)scsi_buffwen(cmd));

		cmd_pkt->fcp_cmnd_dseg_wen = cpu_to_we16(ctx->fcp_cmnd_wen);
		put_unawigned_we64(ctx->fcp_cmnd_dma,
				   &cmd_pkt->fcp_cmnd_dseg_addwess);

		sp->fwags |= SWB_FCP_CMND_DMA_VAWID;
		cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));
		/* Set totaw data segment count. */
		cmd_pkt->entwy_count = (uint8_t)weq_cnt;
		/* Specify wesponse queue numbew whewe
		 * compwetion shouwd happen
		 */
		cmd_pkt->entwy_status = (uint8_t) wsp->id;
	} ewse {
		stwuct cmd_type_7 *cmd_pkt;

		weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);
		if (weq->cnt < (weq_cnt + 2)) {
			cnt = (uint16_t)wd_weg_dwowd_wewaxed(
			    &weg->weq_q_out[0]);
			if (weq->wing_index < cnt)
				weq->cnt = cnt - weq->wing_index;
			ewse
				weq->cnt = weq->wength -
					(weq->wing_index - cnt);
		}
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;

		cmd_pkt = (stwuct cmd_type_7 *)weq->wing_ptw;
		cmd_pkt->handwe = make_handwe(weq->id, handwe);

		/* Zewo out wemaining powtion of packet. */
		/* tagged queuing modifiew -- defauwt is TSK_SIMPWE (0).*/
		cww_ptw = (uint32_t *)cmd_pkt + 2;
		memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
		cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

		/* Set NPOWT-ID and WUN numbew*/
		cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
		cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
		cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
		cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
		cmd_pkt->vp_index = sp->vha->vp_idx;

		int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
		host_to_fcp_swap((uint8_t *)&cmd_pkt->wun,
		    sizeof(cmd_pkt->wun));

		/* Popuwate the FCP_PWIO. */
		if (ha->fwags.fcp_pwio_enabwed)
			cmd_pkt->task |= sp->fcpowt->fcp_pwio << 3;

		/* Woad SCSI command packet. */
		memcpy(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_wen);
		host_to_fcp_swap(cmd_pkt->fcp_cdb, sizeof(cmd_pkt->fcp_cdb));

		cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));

		/* Buiwd IOCB segments */
		qwa24xx_buiwd_scsi_iocbs(sp, cmd_pkt, tot_dsds, weq);

		/* Set totaw data segment count. */
		cmd_pkt->entwy_count = (uint8_t)weq_cnt;
		/* Specify wesponse queue numbew whewe
		 * compwetion shouwd happen.
		 */
		cmd_pkt->entwy_status = (uint8_t) wsp->id;

	}
	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;
	wmb();

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	sp->fwags |= SWB_DMA_VAWID;

	/* Set chip new wing index. */
	/* wwite, wead and vewify wogic */
	dbvaw = dbvaw | (weq->id << 8) | (weq->wing_index << 16);
	if (qw2xdbww)
		qwa82xx_ww_32(ha, (uintptw_t __fowce)ha->nxdb_ww_ptw, dbvaw);
	ewse {
		wwt_weg_dwowd(ha->nxdb_ww_ptw, dbvaw);
		wmb();
		whiwe (wd_weg_dwowd(ha->nxdb_wd_ptw) != dbvaw) {
			wwt_weg_dwowd(ha->nxdb_ww_ptw, dbvaw);
			wmb();
		}
	}

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn QWA_SUCCESS;

queuing_ewwow_fcp_cmnd:
	dma_poow_fwee(ha->fcp_cmnd_dma_poow, ctx->fcp_cmnd, ctx->fcp_cmnd_dma);
queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	if (sp->u.scmd.cwc_ctx) {
		mempoow_fwee(sp->u.scmd.cwc_ctx, ha->ctx_mempoow);
		sp->u.scmd.cwc_ctx = NUWW;
	}
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}

static void
qwa24xx_abowt_iocb(swb_t *sp, stwuct abowt_entwy_24xx *abt_iocb)
{
	stwuct swb_iocb *aio = &sp->u.iocb_cmd;
	scsi_qwa_host_t *vha = sp->vha;
	stwuct weq_que *weq = sp->qpaiw->weq;
	swb_t *owig_sp = sp->cmd_sp;

	memset(abt_iocb, 0, sizeof(stwuct abowt_entwy_24xx));
	abt_iocb->entwy_type = ABOWT_IOCB_TYPE;
	abt_iocb->entwy_count = 1;
	abt_iocb->handwe = make_handwe(weq->id, sp->handwe);
	if (sp->fcpowt) {
		abt_iocb->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
		abt_iocb->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
		abt_iocb->powt_id[1] = sp->fcpowt->d_id.b.awea;
		abt_iocb->powt_id[2] = sp->fcpowt->d_id.b.domain;
	}
	abt_iocb->handwe_to_abowt =
		make_handwe(we16_to_cpu(aio->u.abt.weq_que_no),
			    aio->u.abt.cmd_hndw);
	abt_iocb->vp_index = vha->vp_idx;
	abt_iocb->weq_que_no = aio->u.abt.weq_que_no;

	/* need to pass owiginaw sp */
	if (owig_sp)
		qwa_nvme_abowt_set_option(abt_iocb, owig_sp);

	/* Send the command to the fiwmwawe */
	wmb();
}

static void
qwa2x00_mb_iocb(swb_t *sp, stwuct mbx_24xx_entwy *mbx)
{
	int i, sz;

	mbx->entwy_type = MBX_IOCB_TYPE;
	mbx->handwe = sp->handwe;
	sz = min(AWWAY_SIZE(mbx->mb), AWWAY_SIZE(sp->u.iocb_cmd.u.mbx.out_mb));

	fow (i = 0; i < sz; i++)
		mbx->mb[i] = sp->u.iocb_cmd.u.mbx.out_mb[i];
}

static void
qwa2x00_ctpthwu_cmd_iocb(swb_t *sp, stwuct ct_entwy_24xx *ct_pkt)
{
	sp->u.iocb_cmd.u.ctawg.iocb = ct_pkt;
	qwa24xx_pwep_ms_iocb(sp->vha, &sp->u.iocb_cmd.u.ctawg);
	ct_pkt->handwe = sp->handwe;
}

static void qwa2x00_send_notify_ack_iocb(swb_t *sp,
	stwuct nack_to_isp *nack)
{
	stwuct imm_ntfy_fwom_isp *ntfy = sp->u.iocb_cmd.u.nack.ntfy;

	nack->entwy_type = NOTIFY_ACK_TYPE;
	nack->entwy_count = 1;
	nack->ox_id = ntfy->ox_id;

	nack->u.isp24.handwe = sp->handwe;
	nack->u.isp24.npowt_handwe = ntfy->u.isp24.npowt_handwe;
	if (we16_to_cpu(ntfy->u.isp24.status) == IMM_NTFY_EWS) {
		nack->u.isp24.fwags = ntfy->u.isp24.fwags &
			cpu_to_we16(NOTIFY24XX_FWAGS_PUWEX_IOCB);
	}
	nack->u.isp24.sww_wx_id = ntfy->u.isp24.sww_wx_id;
	nack->u.isp24.status = ntfy->u.isp24.status;
	nack->u.isp24.status_subcode = ntfy->u.isp24.status_subcode;
	nack->u.isp24.fw_handwe = ntfy->u.isp24.fw_handwe;
	nack->u.isp24.exchange_addwess = ntfy->u.isp24.exchange_addwess;
	nack->u.isp24.sww_wew_offs = ntfy->u.isp24.sww_wew_offs;
	nack->u.isp24.sww_ui = ntfy->u.isp24.sww_ui;
	nack->u.isp24.sww_fwags = 0;
	nack->u.isp24.sww_weject_code = 0;
	nack->u.isp24.sww_weject_code_expw = 0;
	nack->u.isp24.vp_index = ntfy->u.isp24.vp_index;

	if (ntfy->u.isp24.status_subcode == EWS_PWOGI &&
	    (we16_to_cpu(ntfy->u.isp24.fwags) & NOTIFY24XX_FWAGS_FCSP) &&
	    sp->vha->hw->fwags.edif_enabwed) {
		qw_dbg(qw_dbg_disc, sp->vha, 0x3074,
		    "%s PWOGI NACK sent with FC SECUWITY bit, hdw=%x, woopid=%x, to pid %06x\n",
		    sp->name, sp->handwe, sp->fcpowt->woop_id,
		    sp->fcpowt->d_id.b24);
		nack->u.isp24.fwags |= cpu_to_we16(NOTIFY_ACK_FWAGS_FCSP);
	}
}

/*
 * Buiwd NVME WS wequest
 */
static void
qwa_nvme_ws(swb_t *sp, stwuct pt_ws4_wequest *cmd_pkt)
{
	stwuct swb_iocb *nvme;

	nvme = &sp->u.iocb_cmd;
	cmd_pkt->entwy_type = PT_WS4_WEQUEST;
	cmd_pkt->entwy_count = 1;
	cmd_pkt->timeout = cpu_to_we16(nvme->u.nvme.timeout_sec);
	cmd_pkt->vp_index = sp->fcpowt->vha->vp_idx;

	if (sp->unsow_wsp) {
		cmd_pkt->contwow_fwags =
				cpu_to_we16(CF_WS4_WESPONDEW << CF_WS4_SHIFT);
		cmd_pkt->npowt_handwe = nvme->u.nvme.npowt_handwe;
		cmd_pkt->exchange_addwess = nvme->u.nvme.exchange_addwess;
	} ewse {
		cmd_pkt->contwow_fwags =
				cpu_to_we16(CF_WS4_OWIGINATOW << CF_WS4_SHIFT);
		cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
		cmd_pkt->wx_dseg_count = cpu_to_we16(1);
		cmd_pkt->wx_byte_count = nvme->u.nvme.wsp_wen;
		cmd_pkt->dsd[1].wength  = nvme->u.nvme.wsp_wen;
		put_unawigned_we64(nvme->u.nvme.wsp_dma, &cmd_pkt->dsd[1].addwess);
	}

	cmd_pkt->tx_dseg_count = cpu_to_we16(1);
	cmd_pkt->tx_byte_count = nvme->u.nvme.cmd_wen;
	cmd_pkt->dsd[0].wength = nvme->u.nvme.cmd_wen;
	put_unawigned_we64(nvme->u.nvme.cmd_dma, &cmd_pkt->dsd[0].addwess);
}

static void
qwa25xx_ctwwvp_iocb(swb_t *sp, stwuct vp_ctww_entwy_24xx *vce)
{
	int map, pos;

	vce->entwy_type = VP_CTWW_IOCB_TYPE;
	vce->handwe = sp->handwe;
	vce->entwy_count = 1;
	vce->command = cpu_to_we16(sp->u.iocb_cmd.u.ctwwvp.cmd);
	vce->vp_count = cpu_to_we16(1);

	/*
	 * index map in fiwmwawe stawts with 1; decwement index
	 * this is ok as we nevew use index 0
	 */
	map = (sp->u.iocb_cmd.u.ctwwvp.vp_index - 1) / 8;
	pos = (sp->u.iocb_cmd.u.ctwwvp.vp_index - 1) & 7;
	vce->vp_idx_map[map] |= 1 << pos;
}

static void
qwa24xx_pwwo_iocb(swb_t *sp, stwuct wogio_entwy_24xx *wogio)
{
	wogio->entwy_type = WOGINOUT_POWT_IOCB_TYPE;
	wogio->contwow_fwags =
	    cpu_to_we16(WCF_COMMAND_PWWO|WCF_IMPW_PWWO);

	wogio->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	wogio->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	wogio->powt_id[1] = sp->fcpowt->d_id.b.awea;
	wogio->powt_id[2] = sp->fcpowt->d_id.b.domain;
	wogio->vp_index = sp->fcpowt->vha->vp_idx;
}

static int qwa_get_iocbs_wesouwce(stwuct swb *sp)
{
	boow get_exch;
	boow push_it_thwough = fawse;

	if (!qw2xenfowce_iocb_wimit) {
		sp->iowes.wes_type = WESOUWCE_NONE;
		wetuwn 0;
	}
	sp->iowes.wes_type = WESOUWCE_NONE;

	switch (sp->type) {
	case SWB_TM_CMD:
	case SWB_PWWI_CMD:
	case SWB_ADISC_CMD:
		push_it_thwough = twue;
		fawwthwough;
	case SWB_WOGIN_CMD:
	case SWB_EWS_CMD_WPT:
	case SWB_EWS_CMD_HST:
	case SWB_EWS_CMD_HST_NOWOGIN:
	case SWB_CT_CMD:
	case SWB_NVME_WS:
	case SWB_EWS_DCMD:
		get_exch = twue;
		bweak;

	case SWB_FXIOCB_DCMD:
	case SWB_FXIOCB_BCMD:
		sp->iowes.wes_type = WESOUWCE_NONE;
		wetuwn 0;

	case SWB_SA_UPDATE:
	case SWB_SA_WEPWACE:
	case SWB_MB_IOCB:
	case SWB_ABT_CMD:
	case SWB_NACK_PWOGI:
	case SWB_NACK_PWWI:
	case SWB_NACK_WOGO:
	case SWB_WOGOUT_CMD:
	case SWB_CTWW_VP:
	case SWB_MAWKEW:
	defauwt:
		push_it_thwough = twue;
		get_exch = fawse;
	}

	sp->iowes.wes_type |= WESOUWCE_IOCB;
	sp->iowes.iocb_cnt = 1;
	if (get_exch) {
		sp->iowes.wes_type |= WESOUWCE_EXCH;
		sp->iowes.exch_cnt = 1;
	}
	if (push_it_thwough)
		sp->iowes.wes_type |= WESOUWCE_FOWCE;

	wetuwn qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes);
}

static void
qwa_mawkew_iocb(swb_t *sp, stwuct mwk_entwy_24xx *mwk)
{
	mwk->entwy_type = MAWKEW_TYPE;
	mwk->modifiew = sp->u.iocb_cmd.u.tmf.modifiew;
	mwk->handwe = make_handwe(sp->qpaiw->weq->id, sp->handwe);
	if (sp->u.iocb_cmd.u.tmf.modifiew != MK_SYNC_AWW) {
		mwk->npowt_handwe = cpu_to_we16(sp->u.iocb_cmd.u.tmf.woop_id);
		int_to_scsiwun(sp->u.iocb_cmd.u.tmf.wun, (stwuct scsi_wun *)&mwk->wun);
		host_to_fcp_swap(mwk->wun, sizeof(mwk->wun));
		mwk->vp_index = sp->u.iocb_cmd.u.tmf.vp_index;
	}
}

int
qwa2x00_stawt_sp(swb_t *sp)
{
	int wvaw = QWA_SUCCESS;
	scsi_qwa_host_t *vha = sp->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_qpaiw *qp = sp->qpaiw;
	void *pkt;
	unsigned wong fwags;

	if (vha->hw->fwags.eeh_busy)
		wetuwn -EIO;

	spin_wock_iwqsave(qp->qp_wock_ptw, fwags);
	wvaw = qwa_get_iocbs_wesouwce(sp);
	if (wvaw) {
		spin_unwock_iwqwestowe(qp->qp_wock_ptw, fwags);
		wetuwn -EAGAIN;
	}

	pkt = __qwa2x00_awwoc_iocbs(sp->qpaiw, sp);
	if (!pkt) {
		wvaw = -EAGAIN;
		qw_wog(qw_wog_wawn, vha, 0x700c,
		    "qwa2x00_awwoc_iocbs faiwed.\n");
		goto done;
	}

	switch (sp->type) {
	case SWB_WOGIN_CMD:
		IS_FWI2_CAPABWE(ha) ?
		    qwa24xx_wogin_iocb(sp, pkt) :
		    qwa2x00_wogin_iocb(sp, pkt);
		bweak;
	case SWB_PWWI_CMD:
		qwa24xx_pwwi_iocb(sp, pkt);
		bweak;
	case SWB_WOGOUT_CMD:
		IS_FWI2_CAPABWE(ha) ?
		    qwa24xx_wogout_iocb(sp, pkt) :
		    qwa2x00_wogout_iocb(sp, pkt);
		bweak;
	case SWB_EWS_CMD_WPT:
	case SWB_EWS_CMD_HST:
		qwa24xx_ews_iocb(sp, pkt);
		bweak;
	case SWB_EWS_CMD_HST_NOWOGIN:
		qwa_ews_pt_iocb(sp->vha, pkt,  &sp->u.bsg_cmd.u.ews_awg);
		((stwuct ews_entwy_24xx *)pkt)->handwe = sp->handwe;
		bweak;
	case SWB_CT_CMD:
		IS_FWI2_CAPABWE(ha) ?
		    qwa24xx_ct_iocb(sp, pkt) :
		    qwa2x00_ct_iocb(sp, pkt);
		bweak;
	case SWB_ADISC_CMD:
		IS_FWI2_CAPABWE(ha) ?
		    qwa24xx_adisc_iocb(sp, pkt) :
		    qwa2x00_adisc_iocb(sp, pkt);
		bweak;
	case SWB_TM_CMD:
		IS_QWAFX00(ha) ?
		    qwafx00_tm_iocb(sp, pkt) :
		    qwa24xx_tm_iocb(sp, pkt);
		bweak;
	case SWB_FXIOCB_DCMD:
	case SWB_FXIOCB_BCMD:
		qwafx00_fxdisc_iocb(sp, pkt);
		bweak;
	case SWB_NVME_WS:
		qwa_nvme_ws(sp, pkt);
		bweak;
	case SWB_ABT_CMD:
		IS_QWAFX00(ha) ?
			qwafx00_abowt_iocb(sp, pkt) :
			qwa24xx_abowt_iocb(sp, pkt);
		bweak;
	case SWB_EWS_DCMD:
		qwa24xx_ews_wogo_iocb(sp, pkt);
		bweak;
	case SWB_CT_PTHWU_CMD:
		qwa2x00_ctpthwu_cmd_iocb(sp, pkt);
		bweak;
	case SWB_MB_IOCB:
		qwa2x00_mb_iocb(sp, pkt);
		bweak;
	case SWB_NACK_PWOGI:
	case SWB_NACK_PWWI:
	case SWB_NACK_WOGO:
		qwa2x00_send_notify_ack_iocb(sp, pkt);
		bweak;
	case SWB_CTWW_VP:
		qwa25xx_ctwwvp_iocb(sp, pkt);
		bweak;
	case SWB_PWWO_CMD:
		qwa24xx_pwwo_iocb(sp, pkt);
		bweak;
	case SWB_SA_UPDATE:
		qwa24xx_sa_update_iocb(sp, pkt);
		bweak;
	case SWB_SA_WEPWACE:
		qwa24xx_sa_wepwace_iocb(sp, pkt);
		bweak;
	case SWB_MAWKEW:
		qwa_mawkew_iocb(sp, pkt);
		bweak;
	defauwt:
		bweak;
	}

	if (sp->stawt_timew) {
		/* wef: TMW timew wef
		 * this code shouwd be just befowe stawt_iocbs function
		 * This wiww make suwe that cawwew function don't to do
		 * kwef_put even on faiwuwe
		 */
		kwef_get(&sp->cmd_kwef);
		add_timew(&sp->u.iocb_cmd.timew);
	}

	wmb();
	qwa2x00_stawt_iocbs(vha, qp->weq);
done:
	if (wvaw)
		qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(qp->qp_wock_ptw, fwags);
	wetuwn wvaw;
}

static void
qwa25xx_buiwd_bidiw_iocb(swb_t *sp, stwuct scsi_qwa_host *vha,
				stwuct cmd_bidiw *cmd_pkt, uint32_t tot_dsds)
{
	uint16_t avaiw_dsds;
	stwuct dsd64 *cuw_dsd;
	uint32_t weq_data_wen = 0;
	uint32_t wsp_data_wen = 0;
	stwuct scattewwist *sg;
	int index;
	int entwy_count = 1;
	stwuct bsg_job *bsg_job = sp->u.bsg_job;

	/*Update entwy type to indicate bidiw command */
	put_unawigned_we32(COMMAND_BIDIWECTIONAW, &cmd_pkt->entwy_type);

	/* Set the twansfew diwection, in this set both fwags
	 * Awso set the BD_WWAP_BACK fwag, fiwmwawe wiww take cawe
	 * assigning DID=SID fow outgoing pkts.
	 */
	cmd_pkt->ww_dseg_count = cpu_to_we16(bsg_job->wequest_paywoad.sg_cnt);
	cmd_pkt->wd_dseg_count = cpu_to_we16(bsg_job->wepwy_paywoad.sg_cnt);
	cmd_pkt->contwow_fwags = cpu_to_we16(BD_WWITE_DATA | BD_WEAD_DATA |
							BD_WWAP_BACK);

	weq_data_wen = wsp_data_wen = bsg_job->wequest_paywoad.paywoad_wen;
	cmd_pkt->ww_byte_count = cpu_to_we32(weq_data_wen);
	cmd_pkt->wd_byte_count = cpu_to_we32(wsp_data_wen);
	cmd_pkt->timeout = cpu_to_we16(qwa2x00_get_async_timeout(vha) + 2);

	vha->bidi_stats.twansfew_bytes += weq_data_wen;
	vha->bidi_stats.io_count++;

	vha->qwa_stats.output_bytes += weq_data_wen;
	vha->qwa_stats.output_wequests++;

	/* Onwy one dsd is avaiwabwe fow bidiwectionaw IOCB, wemaining dsds
	 * awe bundwed in continuation iocb
	 */
	avaiw_dsds = 1;
	cuw_dsd = &cmd_pkt->fcp_dsd;

	index = 0;

	fow_each_sg(bsg_job->wequest_paywoad.sg_wist, sg,
				bsg_job->wequest_paywoad.sg_cnt, index) {
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets */
		if (avaiw_dsds == 0) {
			/* Continuation type 1 IOCB can accomodate
			 * 5 DSDS
			 */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha, vha->weq);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = 5;
			entwy_count++;
		}
		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}
	/* Fow wead wequest DSD wiww awways goes to continuation IOCB
	 * and fowwow the wwite DSD. If thewe is woom on the cuwwent IOCB
	 * then it is added to that IOCB ewse new continuation IOCB is
	 * awwocated.
	 */
	fow_each_sg(bsg_job->wepwy_paywoad.sg_wist, sg,
				bsg_job->wepwy_paywoad.sg_cnt, index) {
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets */
		if (avaiw_dsds == 0) {
			/* Continuation type 1 IOCB can accomodate
			 * 5 DSDS
			 */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha, vha->weq);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = 5;
			entwy_count++;
		}
		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}
	/* This vawue shouwd be same as numbew of IOCB wequiwed fow this cmd */
	cmd_pkt->entwy_count = entwy_count;
}

int
qwa2x00_stawt_bidiw(swb_t *sp, stwuct scsi_qwa_host *vha, uint32_t tot_dsds)
{

	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags;
	uint32_t handwe;
	uint16_t weq_cnt;
	uint16_t cnt;
	uint32_t *cww_ptw;
	stwuct cmd_bidiw *cmd_pkt = NUWW;
	stwuct wsp_que *wsp;
	stwuct weq_que *weq;
	int wvaw = EXT_STATUS_OK;

	wvaw = QWA_SUCCESS;

	wsp = ha->wsp_q_map[0];
	weq = vha->weq;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (qwa2x00_mawkew(vha, ha->base_qpaiw,
			0, 0, MK_SYNC_AWW) != QWA_SUCCESS)
			wetuwn EXT_STATUS_MAIWBOX;
		vha->mawkew_needed = 0;
	}

	/* Acquiwe wing specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0) {
		wvaw = EXT_STATUS_BUSY;
		goto queuing_ewwow;
	}

	/* Cawcuwate numbew of IOCB wequiwed */
	weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);

	/* Check fow woom on wequest queue. */
	if (weq->cnt < weq_cnt + 2) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt))
				goto queuing_ewwow;
		}

		if  (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
				(weq->wing_index - cnt);
	}
	if (weq->cnt < weq_cnt + 2) {
		wvaw = EXT_STATUS_BUSY;
		goto queuing_ewwow;
	}

	cmd_pkt = (stwuct cmd_bidiw *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	/* Zewo out wemaining powtion of packet. */
	/* tagged queuing modifiew -- defauwt is TSK_SIMPWE (0).*/
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);

	/* Set NPOWT-ID  (of vha)*/
	cmd_pkt->npowt_handwe = cpu_to_we16(vha->sewf_wogin_woop_id);
	cmd_pkt->powt_id[0] = vha->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = vha->d_id.b.awea;
	cmd_pkt->powt_id[2] = vha->d_id.b.domain;

	qwa25xx_buiwd_bidiw_iocb(sp, vha, cmd_pkt, tot_dsds);
	cmd_pkt->entwy_status = (uint8_t) wsp->id;
	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	weq->cnt -= weq_cnt;

	/* Send the command to the fiwmwawe */
	wmb();
	qwa2x00_stawt_iocbs(vha, weq);
queuing_ewwow:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn wvaw;
}

/**
 * qwa_stawt_scsi_type6() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwns non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
static int
qwa_stawt_scsi_type6(swb_t *sp)
{
	int		nseg;
	unsigned wong   fwags;
	uint32_t	*cww_ptw;
	uint32_t	handwe;
	stwuct cmd_type_6 *cmd_pkt;
	uint16_t	cnt;
	uint16_t	weq_cnt;
	uint16_t	tot_dsds;
	stwuct weq_que *weq = NUWW;
	stwuct wsp_que *wsp;
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);
	stwuct scsi_qwa_host *vha = sp->fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_qpaiw *qpaiw = sp->qpaiw;
	uint16_t mowe_dsd_wists = 0;
	stwuct dsd_dma *dsd_ptw;
	uint16_t i;
	__be32 *fcp_dw;
	uint8_t additionaw_cdb_wen;
	stwuct ct6_dsd *ctx;

	/* Acquiwe qpaiw specific wock */
	spin_wock_iwqsave(&qpaiw->qp_wock, fwags);

	/* Setup qpaiw pointews */
	weq = qpaiw->weq;
	wsp = qpaiw->wsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (__qwa2x00_mawkew(vha, qpaiw, 0, 0, MK_SYNC_AWW) != QWA_SUCCESS) {
			spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);
			wetuwn QWA_FUNCTION_FAIWED;
		}
		vha->mawkew_needed = 0;
	}

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0)
		goto queuing_ewwow;

	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
				  scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
	} ewse {
		nseg = 0;
	}

	tot_dsds = nseg;

	/* eventhough dwivew onwy need 1 T6 IOCB, FW stiww convewt DSD to Continueation IOCB */
	weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = weq_cnt;

	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes))
		goto queuing_ewwow;

	mowe_dsd_wists = qwa24xx_cawc_dsd_wists(tot_dsds);
	if ((mowe_dsd_wists + qpaiw->dsd_inuse) >= NUM_DSD_CHAIN) {
		qw_dbg(qw_dbg_io, vha, 0x3028,
		       "Num of DSD wist %d is than %d fow cmd=%p.\n",
		       mowe_dsd_wists + qpaiw->dsd_inuse, NUM_DSD_CHAIN, cmd);
		goto queuing_ewwow;
	}

	if (mowe_dsd_wists <= qpaiw->dsd_avaiw)
		goto sufficient_dsds;
	ewse
		mowe_dsd_wists -= qpaiw->dsd_avaiw;

	fow (i = 0; i < mowe_dsd_wists; i++) {
		dsd_ptw = kzawwoc(sizeof(*dsd_ptw), GFP_ATOMIC);
		if (!dsd_ptw) {
			qw_wog(qw_wog_fataw, vha, 0x3029,
			    "Faiwed to awwocate memowy fow dsd_dma fow cmd=%p.\n", cmd);
			goto queuing_ewwow;
		}
		INIT_WIST_HEAD(&dsd_ptw->wist);

		dsd_ptw->dsd_addw = dma_poow_awwoc(ha->dw_dma_poow,
			GFP_ATOMIC, &dsd_ptw->dsd_wist_dma);
		if (!dsd_ptw->dsd_addw) {
			kfwee(dsd_ptw);
			qw_wog(qw_wog_fataw, vha, 0x302a,
			    "Faiwed to awwocate memowy fow dsd_addw fow cmd=%p.\n", cmd);
			goto queuing_ewwow;
		}
		wist_add_taiw(&dsd_ptw->wist, &qpaiw->dsd_wist);
		qpaiw->dsd_avaiw++;
	}

sufficient_dsds:
	weq_cnt = 1;

	if (weq->cnt < (weq_cnt + 2)) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = (uint16_t)wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt))
				goto queuing_ewwow;
		}

		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength - (weq->wing_index - cnt);
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	ctx = &sp->u.scmd.ct6_ctx;

	memset(ctx, 0, sizeof(stwuct ct6_dsd));
	ctx->fcp_cmnd = dma_poow_zawwoc(ha->fcp_cmnd_dma_poow,
		GFP_ATOMIC, &ctx->fcp_cmnd_dma);
	if (!ctx->fcp_cmnd) {
		qw_wog(qw_wog_fataw, vha, 0x3031,
		    "Faiwed to awwocate fcp_cmnd fow cmd=%p.\n", cmd);
		goto queuing_ewwow;
	}

	/* Initiawize the DSD wist and dma handwe */
	INIT_WIST_HEAD(&ctx->dsd_wist);
	ctx->dsd_use_cnt = 0;

	if (cmd->cmd_wen > 16) {
		additionaw_cdb_wen = cmd->cmd_wen - 16;
		if (cmd->cmd_wen % 4 ||
		    cmd->cmd_wen > QWA_CDB_BUF_SIZE) {
			/*
			 * SCSI command biggew than 16 bytes must be
			 * muwtipwe of 4 ow too big.
			 */
			qw_wog(qw_wog_wawn, vha, 0x3033,
			    "scsi cmd wen %d not muwtipwe of 4 fow cmd=%p.\n",
			    cmd->cmd_wen, cmd);
			goto queuing_ewwow_fcp_cmnd;
		}
		ctx->fcp_cmnd_wen = 12 + cmd->cmd_wen + 4;
	} ewse {
		additionaw_cdb_wen = 0;
		ctx->fcp_cmnd_wen = 12 + 16 + 4;
	}

	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	cmd_pkt = (stwuct cmd_type_6 *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	/* tagged queuing modifiew -- defauwt is TSK_SIMPWE (0). */
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* Set NPOWT-ID and WUN numbew */
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
	cmd_pkt->vp_index = sp->vha->vp_idx;

	/* Buiwd IOCB segments */
	qwa24xx_buiwd_scsi_type_6_iocbs(sp, cmd_pkt, tot_dsds);

	int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

	/* buiwd FCP_CMND IU */
	int_to_scsiwun(cmd->device->wun, &ctx->fcp_cmnd->wun);
	ctx->fcp_cmnd->additionaw_cdb_wen = additionaw_cdb_wen;

	if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		ctx->fcp_cmnd->additionaw_cdb_wen |= 1;
	ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		ctx->fcp_cmnd->additionaw_cdb_wen |= 2;

	/* Popuwate the FCP_PWIO. */
	if (ha->fwags.fcp_pwio_enabwed)
		ctx->fcp_cmnd->task_attwibute |=
		    sp->fcpowt->fcp_pwio << 3;

	memcpy(ctx->fcp_cmnd->cdb, cmd->cmnd, cmd->cmd_wen);

	fcp_dw = (__be32 *)(ctx->fcp_cmnd->cdb + 16 +
	    additionaw_cdb_wen);
	*fcp_dw = htonw((uint32_t)scsi_buffwen(cmd));

	cmd_pkt->fcp_cmnd_dseg_wen = cpu_to_we16(ctx->fcp_cmnd_wen);
	put_unawigned_we64(ctx->fcp_cmnd_dma,
			   &cmd_pkt->fcp_cmnd_dseg_addwess);

	sp->fwags |= SWB_FCP_CMND_DMA_VAWID;
	cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));
	/* Set totaw data segment count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;

	wmb();
	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse {
		weq->wing_ptw++;
	}

	sp->qpaiw->cmd_cnt++;
	sp->fwags |= SWB_DMA_VAWID;

	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	/* Manage unpwocessed WIO/ZIO commands in wesponse queue. */
	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

	wetuwn QWA_SUCCESS;

queuing_ewwow_fcp_cmnd:
	dma_poow_fwee(ha->fcp_cmnd_dma_poow, ctx->fcp_cmnd, ctx->fcp_cmnd_dma);

queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);

	if (sp->u.scmd.cwc_ctx) {
		mempoow_fwee(sp->u.scmd.cwc_ctx, ha->ctx_mempoow);
		sp->u.scmd.cwc_ctx = NUWW;
	}

	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}
