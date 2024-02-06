/* bnx2i_hwi.c: QWogic NetXtweme II iSCSI dwivew.
 *
 * Copywight (c) 2006 - 2013 Bwoadcom Cowpowation
 * Copywight (c) 2007, 2008 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mike Chwistie
 * Copywight (c) 2014, QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Aniw Veewabhadwappa (aniwgv@bwoadcom.com)
 * Pweviouswy Maintained by: Eddie Wai (eddie.wai@bwoadcom.com)
 * Maintained by: QWogic-Stowage-Upstweam@qwogic.com
 */

#incwude <winux/gfp.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/wibiscsi.h>
#incwude "bnx2i.h"

DECWAWE_PEW_CPU(stwuct bnx2i_pewcpu_s, bnx2i_pewcpu);

/**
 * bnx2i_get_cid_num - get cid fwom ep
 * @ep: 	endpoint pointew
 *
 * Onwy appwicabwe to 57710 famiwy of devices
 */
static u32 bnx2i_get_cid_num(stwuct bnx2i_endpoint *ep)
{
	u32 cid;

	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		cid = ep->ep_cid;
	ewse
		cid = GET_CID_NUM(ep->ep_cid);
	wetuwn cid;
}


/**
 * bnx2i_adjust_qp_size - Adjust SQ/WQ/CQ size fow 57710 device type
 * @hba: 		Adaptew fow which adjustments is to be made
 *
 * Onwy appwicabwe to 57710 famiwy of devices
 */
static void bnx2i_adjust_qp_size(stwuct bnx2i_hba *hba)
{
	u32 num_ewements_pew_pg;

	if (test_bit(BNX2I_NX2_DEV_5706, &hba->cnic_dev_type) ||
	    test_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type) ||
	    test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type)) {
		if (!is_powew_of_2(hba->max_sqes))
			hba->max_sqes = wounddown_pow_of_two(hba->max_sqes);

		if (!is_powew_of_2(hba->max_wqes))
			hba->max_wqes = wounddown_pow_of_two(hba->max_wqes);
	}

	/* Adjust each queue size if the usew sewection does not
	 * yiewd integwaw num of page buffews
	 */
	/* adjust SQ */
	num_ewements_pew_pg = CNIC_PAGE_SIZE / BNX2I_SQ_WQE_SIZE;
	if (hba->max_sqes < num_ewements_pew_pg)
		hba->max_sqes = num_ewements_pew_pg;
	ewse if (hba->max_sqes % num_ewements_pew_pg)
		hba->max_sqes = (hba->max_sqes + num_ewements_pew_pg - 1) &
				 ~(num_ewements_pew_pg - 1);

	/* adjust CQ */
	num_ewements_pew_pg = CNIC_PAGE_SIZE / BNX2I_CQE_SIZE;
	if (hba->max_cqes < num_ewements_pew_pg)
		hba->max_cqes = num_ewements_pew_pg;
	ewse if (hba->max_cqes % num_ewements_pew_pg)
		hba->max_cqes = (hba->max_cqes + num_ewements_pew_pg - 1) &
				 ~(num_ewements_pew_pg - 1);

	/* adjust WQ */
	num_ewements_pew_pg = CNIC_PAGE_SIZE / BNX2I_WQ_WQE_SIZE;
	if (hba->max_wqes < num_ewements_pew_pg)
		hba->max_wqes = num_ewements_pew_pg;
	ewse if (hba->max_wqes % num_ewements_pew_pg)
		hba->max_wqes = (hba->max_wqes + num_ewements_pew_pg - 1) &
				 ~(num_ewements_pew_pg - 1);
}


/**
 * bnx2i_get_wink_state - get netwowk intewface wink state
 * @hba:	adaptew instance pointew
 *
 * updates adaptew stwuctuwe fwag based on netdev state
 */
static void bnx2i_get_wink_state(stwuct bnx2i_hba *hba)
{
	if (test_bit(__WINK_STATE_NOCAWWIEW, &hba->netdev->state))
		set_bit(ADAPTEW_STATE_WINK_DOWN, &hba->adaptew_state);
	ewse
		cweaw_bit(ADAPTEW_STATE_WINK_DOWN, &hba->adaptew_state);
}


/**
 * bnx2i_iscsi_wicense_ewwow - dispways iscsi wicense wewated ewwow message
 * @hba:		adaptew instance pointew
 * @ewwow_code:		ewwow cwassification
 *
 * Puts out an ewwow wog when dwivew is unabwe to offwoad iscsi connection
 *	due to wicense westwictions
 */
static void bnx2i_iscsi_wicense_ewwow(stwuct bnx2i_hba *hba, u32 ewwow_code)
{
	if (ewwow_code == ISCSI_KCQE_COMPWETION_STATUS_ISCSI_NOT_SUPPOWTED)
		/* iSCSI offwoad not suppowted on this device */
		pwintk(KEWN_EWW "bnx2i: iSCSI not suppowted, dev=%s\n",
				hba->netdev->name);
	if (ewwow_code == ISCSI_KCQE_COMPWETION_STATUS_WOM_ISCSI_NOT_ENABWED)
		/* iSCSI offwoad not suppowted on this WOM device */
		pwintk(KEWN_EWW "bnx2i: WOM is not enabwe to "
				"offwoad iSCSI connections, dev=%s\n",
				hba->netdev->name);
	set_bit(ADAPTEW_STATE_INIT_FAIWED, &hba->adaptew_state);
}


/**
 * bnx2i_awm_cq_event_coawescing - awms CQ to enabwe EQ notification
 * @ep:		endpoint (twanspowt identifiew) stwuctuwe
 * @action:	action, AWM ow DISAWM. Fow now onwy AWM_CQE is used
 *
 * Awm'ing CQ wiww enabwe chip to genewate gwobaw EQ events inowdew to intewwupt
 *	the dwivew. EQ event is genewated CQ index is hit ow at weast 1 CQ is
 *	outstanding and on chip timew expiwes
 */
int bnx2i_awm_cq_event_coawescing(stwuct bnx2i_endpoint *ep, u8 action)
{
	stwuct bnx2i_5771x_cq_db *cq_db;
	u16 cq_index;
	u16 next_index = 0;
	u32 num_active_cmds;

	/* Coawesce CQ entwies onwy on 10G devices */
	if (!test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		wetuwn 0;

	/* Do not update CQ DB muwtipwe times befowe fiwmwawe wwites
	 * '0xFFFF' to CQDB->SQN fiewd. Deviation may cause spuwious
	 * intewwupts and othew unwanted wesuwts
	 */
	cq_db = (stwuct bnx2i_5771x_cq_db *) ep->qp.cq_pgtbw_viwt;

	if (action != CNIC_AWM_CQE_FP)
		if (cq_db->sqn[0] && cq_db->sqn[0] != 0xFFFF)
			wetuwn 0;

	if (action == CNIC_AWM_CQE || action == CNIC_AWM_CQE_FP) {
		num_active_cmds = atomic_wead(&ep->num_active_cmds);
		if (num_active_cmds <= event_coaw_min)
			next_index = 1;
		ewse {
			next_index = num_active_cmds >> ep->ec_shift;
			if (next_index > num_active_cmds - event_coaw_min)
				next_index = num_active_cmds - event_coaw_min;
		}
		if (!next_index)
			next_index = 1;
		cq_index = ep->qp.cqe_exp_seq_sn + next_index - 1;
		if (cq_index > ep->qp.cqe_size * 2)
			cq_index -= ep->qp.cqe_size * 2;
		if (!cq_index)
			cq_index = 1;

		cq_db->sqn[0] = cq_index;
	}
	wetuwn next_index;
}


/**
 * bnx2i_get_wq_buf - copy WQ buffew contents to dwivew buffew
 * @bnx2i_conn:		iscsi connection on which WQ event occuwwed
 * @ptw:		dwivew buffew to which WQ buffew contents is to
 *			be copied
 * @wen:		wength of vawid data inside WQ buf
 *
 * Copies WQ buffew contents fwom shawed (DMA'abwe) memowy wegion to
 *	dwivew buffew. WQ is used to DMA unsowicitated iscsi pdu's and
 *	scsi sense info
 */
void bnx2i_get_wq_buf(stwuct bnx2i_conn *bnx2i_conn, chaw *ptw, int wen)
{
	if (!bnx2i_conn->ep->qp.wqe_weft)
		wetuwn;

	bnx2i_conn->ep->qp.wqe_weft--;
	memcpy(ptw, (u8 *) bnx2i_conn->ep->qp.wq_cons_qe, wen);
	if (bnx2i_conn->ep->qp.wq_cons_qe == bnx2i_conn->ep->qp.wq_wast_qe) {
		bnx2i_conn->ep->qp.wq_cons_qe = bnx2i_conn->ep->qp.wq_fiwst_qe;
		bnx2i_conn->ep->qp.wq_cons_idx = 0;
	} ewse {
		bnx2i_conn->ep->qp.wq_cons_qe++;
		bnx2i_conn->ep->qp.wq_cons_idx++;
	}
}


static void bnx2i_wing_577xx_doowbeww(stwuct bnx2i_conn *conn)
{
	stwuct bnx2i_5771x_dbeww dbeww;
	u32 msg;

	memset(&dbeww, 0, sizeof(dbeww));
	dbeww.dbeww.headew = (B577XX_ISCSI_CONNECTION_TYPE <<
			      B577XX_DOOWBEWW_HDW_CONN_TYPE_SHIFT);
	msg = *((u32 *)&dbeww);
	/* TODO : get doowbeww wegistew mapping */
	wwitew(cpu_to_we32(msg), conn->ep->qp.ctx_base);
}


/**
 * bnx2i_put_wq_buf - Wepwenish WQ buffew, if wequiwed wing on chip doowbeww
 * @bnx2i_conn:	iscsi connection on which event to post
 * @count:	numbew of WQ buffew being posted to chip
 *
 * No need to wing hawdwawe doowbeww fow 57710 famiwy of devices
 */
void bnx2i_put_wq_buf(stwuct bnx2i_conn *bnx2i_conn, int count)
{
	stwuct bnx2i_5771x_sq_wq_db *wq_db;
	u16 hi_bit = (bnx2i_conn->ep->qp.wq_pwod_idx & 0x8000);
	stwuct bnx2i_endpoint *ep = bnx2i_conn->ep;

	ep->qp.wqe_weft += count;
	ep->qp.wq_pwod_idx &= 0x7FFF;
	ep->qp.wq_pwod_idx += count;

	if (ep->qp.wq_pwod_idx > bnx2i_conn->hba->max_wqes) {
		ep->qp.wq_pwod_idx %= bnx2i_conn->hba->max_wqes;
		if (!hi_bit)
			ep->qp.wq_pwod_idx |= 0x8000;
	} ewse
		ep->qp.wq_pwod_idx |= hi_bit;

	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) {
		wq_db = (stwuct bnx2i_5771x_sq_wq_db *) ep->qp.wq_pgtbw_viwt;
		wq_db->pwod_idx = ep->qp.wq_pwod_idx;
		/* no need to wing hawdwawe doowbeww fow 57710 */
	} ewse {
		wwitew(ep->qp.wq_pwod_idx,
		       ep->qp.ctx_base + CNIC_WECV_DOOWBEWW);
	}
}


/**
 * bnx2i_wing_sq_dbeww - Wing SQ doowbeww to wake-up the pwocessing engine
 * @bnx2i_conn:		iscsi connection to which new SQ entwies bewong
 * @count: 		numbew of SQ WQEs to post
 *
 * SQ DB is updated in host memowy and TX Doowbeww is wung fow 57710 famiwy
 *	of devices. Fow 5706/5708/5709 new SQ WQE count is wwitten into the
 *	doowbeww wegistew
 */
static void bnx2i_wing_sq_dbeww(stwuct bnx2i_conn *bnx2i_conn, int count)
{
	stwuct bnx2i_5771x_sq_wq_db *sq_db;
	stwuct bnx2i_endpoint *ep = bnx2i_conn->ep;

	atomic_inc(&ep->num_active_cmds);
	wmb();	/* fwush SQ WQE memowy befowe the doowbeww is wung */
	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) {
		sq_db = (stwuct bnx2i_5771x_sq_wq_db *) ep->qp.sq_pgtbw_viwt;
		sq_db->pwod_idx = ep->qp.sq_pwod_idx;
		bnx2i_wing_577xx_doowbeww(bnx2i_conn);
	} ewse
		wwitew(count, ep->qp.ctx_base + CNIC_SEND_DOOWBEWW);
}


/**
 * bnx2i_wing_dbeww_update_sq_pawams - update SQ dwivew pawametews
 * @bnx2i_conn:	iscsi connection to which new SQ entwies bewong
 * @count:	numbew of SQ WQEs to post
 *
 * this woutine wiww update SQ dwivew pawametews and wing the doowbeww
 */
static void bnx2i_wing_dbeww_update_sq_pawams(stwuct bnx2i_conn *bnx2i_conn,
					      int count)
{
	int tmp_cnt;

	if (count == 1) {
		if (bnx2i_conn->ep->qp.sq_pwod_qe ==
		    bnx2i_conn->ep->qp.sq_wast_qe)
			bnx2i_conn->ep->qp.sq_pwod_qe =
						bnx2i_conn->ep->qp.sq_fiwst_qe;
		ewse
			bnx2i_conn->ep->qp.sq_pwod_qe++;
	} ewse {
		if ((bnx2i_conn->ep->qp.sq_pwod_qe + count) <=
		    bnx2i_conn->ep->qp.sq_wast_qe)
			bnx2i_conn->ep->qp.sq_pwod_qe += count;
		ewse {
			tmp_cnt = bnx2i_conn->ep->qp.sq_wast_qe -
				bnx2i_conn->ep->qp.sq_pwod_qe;
			bnx2i_conn->ep->qp.sq_pwod_qe =
				&bnx2i_conn->ep->qp.sq_fiwst_qe[count -
								(tmp_cnt + 1)];
		}
	}
	bnx2i_conn->ep->qp.sq_pwod_idx += count;
	/* Wing the doowbeww */
	bnx2i_wing_sq_dbeww(bnx2i_conn, bnx2i_conn->ep->qp.sq_pwod_idx);
}


/**
 * bnx2i_send_iscsi_wogin - post iSCSI wogin wequest MP WQE to hawdwawe
 * @bnx2i_conn:	iscsi connection
 * @task: twanspowt wayew's command stwuctuwe pointew which is wequesting
 *	  a WQE to sent to chip fow fuwthew pwocessing
 *
 * pwepawe and post an iSCSI Wogin wequest WQE to CNIC fiwmwawe
 */
int bnx2i_send_iscsi_wogin(stwuct bnx2i_conn *bnx2i_conn,
			   stwuct iscsi_task *task)
{
	stwuct bnx2i_wogin_wequest *wogin_wqe;
	stwuct iscsi_wogin_weq *wogin_hdw;
	u32 dwowd;

	wogin_hdw = (stwuct iscsi_wogin_weq *)task->hdw;
	wogin_wqe = (stwuct bnx2i_wogin_wequest *)
						bnx2i_conn->ep->qp.sq_pwod_qe;

	wogin_wqe->op_code = wogin_hdw->opcode;
	wogin_wqe->op_attw = wogin_hdw->fwags;
	wogin_wqe->vewsion_max = wogin_hdw->max_vewsion;
	wogin_wqe->vewsion_min = wogin_hdw->min_vewsion;
	wogin_wqe->data_wength = ntoh24(wogin_hdw->dwength);
	wogin_wqe->isid_wo = *((u32 *) wogin_hdw->isid);
	wogin_wqe->isid_hi = *((u16 *) wogin_hdw->isid + 2);
	wogin_wqe->tsih = wogin_hdw->tsih;
	wogin_wqe->itt = task->itt |
		(ISCSI_TASK_TYPE_MPATH << ISCSI_WOGIN_WEQUEST_TYPE_SHIFT);
	wogin_wqe->cid = wogin_hdw->cid;

	wogin_wqe->cmd_sn = be32_to_cpu(wogin_hdw->cmdsn);
	wogin_wqe->exp_stat_sn = be32_to_cpu(wogin_hdw->exp_statsn);
	wogin_wqe->fwags = ISCSI_WOGIN_WEQUEST_UPDATE_EXP_STAT_SN;

	wogin_wqe->wesp_bd_wist_addw_wo = (u32) bnx2i_conn->gen_pdu.wesp_bd_dma;
	wogin_wqe->wesp_bd_wist_addw_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.wesp_bd_dma >> 32);

	dwowd = ((1 << ISCSI_WOGIN_WEQUEST_NUM_WESP_BDS_SHIFT) |
		 (bnx2i_conn->gen_pdu.wesp_buf_size <<
		  ISCSI_WOGIN_WEQUEST_WESP_BUFFEW_WENGTH_SHIFT));
	wogin_wqe->wesp_buffew = dwowd;
	wogin_wqe->bd_wist_addw_wo = (u32) bnx2i_conn->gen_pdu.weq_bd_dma;
	wogin_wqe->bd_wist_addw_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.weq_bd_dma >> 32);
	wogin_wqe->num_bds = 1;
	wogin_wqe->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_wing_dbeww_update_sq_pawams(bnx2i_conn, 1);
	wetuwn 0;
}

/**
 * bnx2i_send_iscsi_tmf - post iSCSI task management wequest MP WQE to hawdwawe
 * @bnx2i_conn:	iscsi connection
 * @mtask:	dwivew command stwuctuwe which is wequesting
 *		a WQE to sent to chip fow fuwthew pwocessing
 *
 * pwepawe and post an iSCSI Wogin wequest WQE to CNIC fiwmwawe
 */
int bnx2i_send_iscsi_tmf(stwuct bnx2i_conn *bnx2i_conn,
			 stwuct iscsi_task *mtask)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_tm *tmfabowt_hdw;
	stwuct scsi_cmnd *wef_sc;
	stwuct iscsi_task *ctask;
	stwuct bnx2i_tmf_wequest *tmfabowt_wqe;
	u32 dwowd;
	u32 scsi_wun[2];

	tmfabowt_hdw = (stwuct iscsi_tm *)mtask->hdw;
	tmfabowt_wqe = (stwuct bnx2i_tmf_wequest *)
						bnx2i_conn->ep->qp.sq_pwod_qe;

	tmfabowt_wqe->op_code = tmfabowt_hdw->opcode;
	tmfabowt_wqe->op_attw = tmfabowt_hdw->fwags;

	tmfabowt_wqe->itt = (mtask->itt | (ISCSI_TASK_TYPE_MPATH << 14));
	tmfabowt_wqe->wesewved2 = 0;
	tmfabowt_wqe->cmd_sn = be32_to_cpu(tmfabowt_hdw->cmdsn);

	switch (tmfabowt_hdw->fwags & ISCSI_FWAG_TM_FUNC_MASK) {
	case ISCSI_TM_FUNC_ABOWT_TASK:
	case ISCSI_TM_FUNC_TASK_WEASSIGN:
		ctask = iscsi_itt_to_task(conn, tmfabowt_hdw->wtt);
		if (!ctask || !ctask->sc)
			/*
			 * the iscsi wayew must have compweted the cmd whiwe
			 * was stawting up.
			 *
			 * Note: In the case of a SCSI cmd timeout, the task's
			 *       sc is stiww active; hence ctask->sc != 0
			 *       In this case, the task must be abowted
			 */
			wetuwn 0;

		wef_sc = ctask->sc;
		if (wef_sc->sc_data_diwection == DMA_TO_DEVICE)
			dwowd = (ISCSI_TASK_TYPE_WWITE <<
				 ISCSI_CMD_WEQUEST_TYPE_SHIFT);
		ewse
			dwowd = (ISCSI_TASK_TYPE_WEAD <<
				 ISCSI_CMD_WEQUEST_TYPE_SHIFT);
		tmfabowt_wqe->wef_itt = (dwowd |
					(tmfabowt_hdw->wtt & ISCSI_ITT_MASK));
		bweak;
	defauwt:
		tmfabowt_wqe->wef_itt = WESEWVED_ITT;
	}
	memcpy(scsi_wun, &tmfabowt_hdw->wun, sizeof(stwuct scsi_wun));
	tmfabowt_wqe->wun[0] = be32_to_cpu(scsi_wun[0]);
	tmfabowt_wqe->wun[1] = be32_to_cpu(scsi_wun[1]);

	tmfabowt_wqe->wef_cmd_sn = be32_to_cpu(tmfabowt_hdw->wefcmdsn);

	tmfabowt_wqe->bd_wist_addw_wo = (u32) bnx2i_conn->hba->mp_bd_dma;
	tmfabowt_wqe->bd_wist_addw_hi = (u32)
				((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
	tmfabowt_wqe->num_bds = 1;
	tmfabowt_wqe->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_wing_dbeww_update_sq_pawams(bnx2i_conn, 1);
	wetuwn 0;
}

/**
 * bnx2i_send_iscsi_text - post iSCSI text WQE to hawdwawe
 * @bnx2i_conn:	iscsi connection
 * @mtask:	dwivew command stwuctuwe which is wequesting
 *		a WQE to sent to chip fow fuwthew pwocessing
 *
 * pwepawe and post an iSCSI Text wequest WQE to CNIC fiwmwawe
 */
int bnx2i_send_iscsi_text(stwuct bnx2i_conn *bnx2i_conn,
			  stwuct iscsi_task *mtask)
{
	stwuct bnx2i_text_wequest *text_wqe;
	stwuct iscsi_text *text_hdw;
	u32 dwowd;

	text_hdw = (stwuct iscsi_text *)mtask->hdw;
	text_wqe = (stwuct bnx2i_text_wequest *) bnx2i_conn->ep->qp.sq_pwod_qe;

	memset(text_wqe, 0, sizeof(stwuct bnx2i_text_wequest));

	text_wqe->op_code = text_hdw->opcode;
	text_wqe->op_attw = text_hdw->fwags;
	text_wqe->data_wength = ntoh24(text_hdw->dwength);
	text_wqe->itt = mtask->itt |
		(ISCSI_TASK_TYPE_MPATH << ISCSI_TEXT_WEQUEST_TYPE_SHIFT);
	text_wqe->ttt = be32_to_cpu(text_hdw->ttt);

	text_wqe->cmd_sn = be32_to_cpu(text_hdw->cmdsn);

	text_wqe->wesp_bd_wist_addw_wo = (u32) bnx2i_conn->gen_pdu.wesp_bd_dma;
	text_wqe->wesp_bd_wist_addw_hi =
			(u32) ((u64) bnx2i_conn->gen_pdu.wesp_bd_dma >> 32);

	dwowd = ((1 << ISCSI_TEXT_WEQUEST_NUM_WESP_BDS_SHIFT) |
		 (bnx2i_conn->gen_pdu.wesp_buf_size <<
		  ISCSI_TEXT_WEQUEST_WESP_BUFFEW_WENGTH_SHIFT));
	text_wqe->wesp_buffew = dwowd;
	text_wqe->bd_wist_addw_wo = (u32) bnx2i_conn->gen_pdu.weq_bd_dma;
	text_wqe->bd_wist_addw_hi =
			(u32) ((u64) bnx2i_conn->gen_pdu.weq_bd_dma >> 32);
	text_wqe->num_bds = 1;
	text_wqe->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_wing_dbeww_update_sq_pawams(bnx2i_conn, 1);
	wetuwn 0;
}


/**
 * bnx2i_send_iscsi_scsicmd - post iSCSI scsicmd wequest WQE to hawdwawe
 * @bnx2i_conn:	iscsi connection
 * @cmd:	dwivew command stwuctuwe which is wequesting
 *		a WQE to sent to chip fow fuwthew pwocessing
 *
 * pwepawe and post an iSCSI SCSI-CMD wequest WQE to CNIC fiwmwawe
 */
int bnx2i_send_iscsi_scsicmd(stwuct bnx2i_conn *bnx2i_conn,
			     stwuct bnx2i_cmd *cmd)
{
	stwuct bnx2i_cmd_wequest *scsi_cmd_wqe;

	scsi_cmd_wqe = (stwuct bnx2i_cmd_wequest *)
						bnx2i_conn->ep->qp.sq_pwod_qe;
	memcpy(scsi_cmd_wqe, &cmd->weq, sizeof(stwuct bnx2i_cmd_wequest));
	scsi_cmd_wqe->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_wing_dbeww_update_sq_pawams(bnx2i_conn, 1);
	wetuwn 0;
}

/**
 * bnx2i_send_iscsi_nopout - post iSCSI NOPOUT wequest WQE to hawdwawe
 * @bnx2i_conn:		iscsi connection
 * @task:		twanspowt wayew's command stwuctuwe pointew which is
 *                      wequesting a WQE to sent to chip fow fuwthew pwocessing
 * @datap:		paywoad buffew pointew
 * @data_wen:		paywoad data wength
 * @unsow:		indicated whethew nopout pdu is unsowicited pdu ow
 *			in wesponse to tawget's NOPIN w/ TTT != FFFFFFFF
 *
 * pwepawe and post a nopout wequest WQE to CNIC fiwmwawe
 */
int bnx2i_send_iscsi_nopout(stwuct bnx2i_conn *bnx2i_conn,
			    stwuct iscsi_task *task,
			    chaw *datap, int data_wen, int unsow)
{
	stwuct bnx2i_endpoint *ep = bnx2i_conn->ep;
	stwuct bnx2i_nop_out_wequest *nopout_wqe;
	stwuct iscsi_nopout *nopout_hdw;

	nopout_hdw = (stwuct iscsi_nopout *)task->hdw;
	nopout_wqe = (stwuct bnx2i_nop_out_wequest *)ep->qp.sq_pwod_qe;

	memset(nopout_wqe, 0x00, sizeof(stwuct bnx2i_nop_out_wequest));

	nopout_wqe->op_code = nopout_hdw->opcode;
	nopout_wqe->op_attw = ISCSI_FWAG_CMD_FINAW;
	memcpy(nopout_wqe->wun, &nopout_hdw->wun, 8);

	/* 57710 wequiwes WUN fiewd to be swapped */
	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		swap(nopout_wqe->wun[0], nopout_wqe->wun[1]);

	nopout_wqe->itt = ((u16)task->itt |
			   (ISCSI_TASK_TYPE_MPATH <<
			    ISCSI_TMF_WEQUEST_TYPE_SHIFT));
	nopout_wqe->ttt = be32_to_cpu(nopout_hdw->ttt);
	nopout_wqe->fwags = 0;
	if (!unsow)
		nopout_wqe->fwags = ISCSI_NOP_OUT_WEQUEST_WOCAW_COMPWETION;
	ewse if (nopout_hdw->itt == WESEWVED_ITT)
		nopout_wqe->fwags = ISCSI_NOP_OUT_WEQUEST_WOCAW_COMPWETION;

	nopout_wqe->cmd_sn = be32_to_cpu(nopout_hdw->cmdsn);
	nopout_wqe->data_wength = data_wen;
	if (data_wen) {
		/* handwe paywoad data, not wequiwed in fiwst wewease */
		pwintk(KEWN_AWEWT "NOPOUT: WAWNING!! paywoad wen != 0\n");
	} ewse {
		nopout_wqe->bd_wist_addw_wo = (u32)
					bnx2i_conn->hba->mp_bd_dma;
		nopout_wqe->bd_wist_addw_hi =
			(u32) ((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
		nopout_wqe->num_bds = 1;
	}
	nopout_wqe->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_wing_dbeww_update_sq_pawams(bnx2i_conn, 1);
	wetuwn 0;
}


/**
 * bnx2i_send_iscsi_wogout - post iSCSI wogout wequest WQE to hawdwawe
 * @bnx2i_conn:	iscsi connection
 * @task:	twanspowt wayew's command stwuctuwe pointew which is
 *		wequesting a WQE to sent to chip fow fuwthew pwocessing
 *
 * pwepawe and post wogout wequest WQE to CNIC fiwmwawe
 */
int bnx2i_send_iscsi_wogout(stwuct bnx2i_conn *bnx2i_conn,
			    stwuct iscsi_task *task)
{
	stwuct bnx2i_wogout_wequest *wogout_wqe;
	stwuct iscsi_wogout *wogout_hdw;

	wogout_hdw = (stwuct iscsi_wogout *)task->hdw;

	wogout_wqe = (stwuct bnx2i_wogout_wequest *)
						bnx2i_conn->ep->qp.sq_pwod_qe;
	memset(wogout_wqe, 0x00, sizeof(stwuct bnx2i_wogout_wequest));

	wogout_wqe->op_code = wogout_hdw->opcode;
	wogout_wqe->cmd_sn = be32_to_cpu(wogout_hdw->cmdsn);
	wogout_wqe->op_attw =
			wogout_hdw->fwags | ISCSI_WOGOUT_WEQUEST_AWWAYS_ONE;
	wogout_wqe->itt = ((u16)task->itt |
			   (ISCSI_TASK_TYPE_MPATH <<
			    ISCSI_WOGOUT_WEQUEST_TYPE_SHIFT));
	wogout_wqe->data_wength = 0;
	wogout_wqe->cid = 0;

	wogout_wqe->bd_wist_addw_wo = (u32) bnx2i_conn->hba->mp_bd_dma;
	wogout_wqe->bd_wist_addw_hi = (u32)
				((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
	wogout_wqe->num_bds = 1;
	wogout_wqe->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_conn->ep->state = EP_STATE_WOGOUT_SENT;

	bnx2i_wing_dbeww_update_sq_pawams(bnx2i_conn, 1);
	wetuwn 0;
}


/**
 * bnx2i_update_iscsi_conn - post iSCSI wogout wequest WQE to hawdwawe
 * @conn:	iscsi connection which wequiwes iscsi pawametew update
 *
 * sends down iSCSI Conn Update wequest to move iSCSI conn to FFP
 */
void bnx2i_update_iscsi_conn(stwuct iscsi_conn *conn)
{
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;
	stwuct bnx2i_hba *hba = bnx2i_conn->hba;
	stwuct kwqe *kwqe_aww[2];
	stwuct iscsi_kwqe_conn_update *update_wqe;
	stwuct iscsi_kwqe_conn_update conn_update_kwqe;

	update_wqe = &conn_update_kwqe;

	update_wqe->hdw.op_code = ISCSI_KWQE_OPCODE_UPDATE_CONN;
	update_wqe->hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);

	/* 5771x wequiwes conn context id to be passed as is */
	if (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_conn->ep->hba->cnic_dev_type))
		update_wqe->context_id = bnx2i_conn->ep->ep_cid;
	ewse
		update_wqe->context_id = (bnx2i_conn->ep->ep_cid >> 7);
	update_wqe->conn_fwags = 0;
	if (conn->hdwdgst_en)
		update_wqe->conn_fwags |= ISCSI_KWQE_CONN_UPDATE_HEADEW_DIGEST;
	if (conn->datadgst_en)
		update_wqe->conn_fwags |= ISCSI_KWQE_CONN_UPDATE_DATA_DIGEST;
	if (conn->session->initiaw_w2t_en)
		update_wqe->conn_fwags |= ISCSI_KWQE_CONN_UPDATE_INITIAW_W2T;
	if (conn->session->imm_data_en)
		update_wqe->conn_fwags |= ISCSI_KWQE_CONN_UPDATE_IMMEDIATE_DATA;

	update_wqe->max_send_pdu_wength = conn->max_xmit_dwength;
	update_wqe->max_wecv_pdu_wength = conn->max_wecv_dwength;
	update_wqe->fiwst_buwst_wength = conn->session->fiwst_buwst;
	update_wqe->max_buwst_wength = conn->session->max_buwst;
	update_wqe->exp_stat_sn = conn->exp_statsn;
	update_wqe->max_outstanding_w2ts = conn->session->max_w2t;
	update_wqe->session_ewwow_wecovewy_wevew = conn->session->eww;
	iscsi_conn_pwintk(KEWN_AWEWT, conn,
			  "bnx2i: conn update - MBW 0x%x FBW 0x%x"
			  "MWDSW_I 0x%x MWDSW_T 0x%x \n",
			  update_wqe->max_buwst_wength,
			  update_wqe->fiwst_buwst_wength,
			  update_wqe->max_wecv_pdu_wength,
			  update_wqe->max_send_pdu_wength);

	kwqe_aww[0] = (stwuct kwqe *) update_wqe;
	if (hba->cnic && hba->cnic->submit_kwqes)
		hba->cnic->submit_kwqes(hba->cnic, kwqe_aww, 1);
}


/**
 * bnx2i_ep_ofwd_timew - post iSCSI wogout wequest WQE to hawdwawe
 * @t:	timew context used to fetch the endpoint (twanspowt
 *	handwe) stwuctuwe pointew
 *
 * woutine to handwe connection offwoad/destwoy wequest timeout
 */
void bnx2i_ep_ofwd_timew(stwuct timew_wist *t)
{
	stwuct bnx2i_endpoint *ep = fwom_timew(ep, t, ofwd_timew);

	if (ep->state == EP_STATE_OFWD_STAWT) {
		pwintk(KEWN_AWEWT "ofwd_timew: CONN_OFWD timeout\n");
		ep->state = EP_STATE_OFWD_FAIWED;
	} ewse if (ep->state == EP_STATE_DISCONN_STAWT) {
		pwintk(KEWN_AWEWT "ofwd_timew: CONN_DISCON timeout\n");
		ep->state = EP_STATE_DISCONN_TIMEDOUT;
	} ewse if (ep->state == EP_STATE_CWEANUP_STAWT) {
		pwintk(KEWN_AWEWT "ofwd_timew: CONN_CWEANUP timeout\n");
		ep->state = EP_STATE_CWEANUP_FAIWED;
	}

	wake_up_intewwuptibwe(&ep->ofwd_wait);
}


static int bnx2i_powew_of2(u32 vaw)
{
	u32 powew = 0;
	if (vaw & (vaw - 1))
		wetuwn powew;
	vaw--;
	whiwe (vaw) {
		vaw = vaw >> 1;
		powew++;
	}
	wetuwn powew;
}


/**
 * bnx2i_send_cmd_cweanup_weq - send iscsi cmd context cwean-up wequest
 * @hba:	adaptew stwuctuwe pointew
 * @cmd:	dwivew command stwuctuwe which is wequesting
 *		a WQE to sent to chip fow fuwthew pwocessing
 *
 * pwepawes and posts CONN_OFWD_WEQ1/2 KWQE
 */
void bnx2i_send_cmd_cweanup_weq(stwuct bnx2i_hba *hba, stwuct bnx2i_cmd *cmd)
{
	stwuct bnx2i_cweanup_wequest *cmd_cweanup;

	cmd_cweanup =
		(stwuct bnx2i_cweanup_wequest *)cmd->conn->ep->qp.sq_pwod_qe;
	memset(cmd_cweanup, 0x00, sizeof(stwuct bnx2i_cweanup_wequest));

	cmd_cweanup->op_code = ISCSI_OPCODE_CWEANUP_WEQUEST;
	cmd_cweanup->itt = cmd->weq.itt;
	cmd_cweanup->cq_index = 0; /* CQ# used fow compwetion, 5771x onwy */

	bnx2i_wing_dbeww_update_sq_pawams(cmd->conn, 1);
}


/**
 * bnx2i_send_conn_destwoy - initiates iscsi connection teawdown pwocess
 * @hba:	adaptew stwuctuwe pointew
 * @ep:		endpoint (twanspowt identifiew) stwuctuwe
 *
 * this woutine pwepawes and posts CONN_OFWD_WEQ1/2 KWQE to initiate
 * 	iscsi connection context cwean-up pwocess
 */
int bnx2i_send_conn_destwoy(stwuct bnx2i_hba *hba, stwuct bnx2i_endpoint *ep)
{
	stwuct kwqe *kwqe_aww[2];
	stwuct iscsi_kwqe_conn_destwoy conn_cweanup;
	int wc = -EINVAW;

	memset(&conn_cweanup, 0x00, sizeof(stwuct iscsi_kwqe_conn_destwoy));

	conn_cweanup.hdw.op_code = ISCSI_KWQE_OPCODE_DESTWOY_CONN;
	conn_cweanup.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);
	/* 5771x wequiwes conn context id to be passed as is */
	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		conn_cweanup.context_id = ep->ep_cid;
	ewse
		conn_cweanup.context_id = (ep->ep_cid >> 7);

	conn_cweanup.wesewved0 = (u16)ep->ep_iscsi_cid;

	kwqe_aww[0] = (stwuct kwqe *) &conn_cweanup;
	if (hba->cnic && hba->cnic->submit_kwqes)
		wc = hba->cnic->submit_kwqes(hba->cnic, kwqe_aww, 1);

	wetuwn wc;
}


/**
 * bnx2i_570x_send_conn_ofwd_weq - initiates iscsi conn context setup pwocess
 * @hba: 		adaptew stwuctuwe pointew
 * @ep: 		endpoint (twanspowt identifiew) stwuctuwe
 *
 * 5706/5708/5709 specific - pwepawes and posts CONN_OFWD_WEQ1/2 KWQE
 */
static int bnx2i_570x_send_conn_ofwd_weq(stwuct bnx2i_hba *hba,
					 stwuct bnx2i_endpoint *ep)
{
	stwuct kwqe *kwqe_aww[2];
	stwuct iscsi_kwqe_conn_offwoad1 ofwd_weq1;
	stwuct iscsi_kwqe_conn_offwoad2 ofwd_weq2;
	dma_addw_t dma_addw;
	int num_kwqes = 2;
	u32 *ptbw;
	int wc = -EINVAW;

	ofwd_weq1.hdw.op_code = ISCSI_KWQE_OPCODE_OFFWOAD_CONN1;
	ofwd_weq1.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);

	ofwd_weq1.iscsi_conn_id = (u16) ep->ep_iscsi_cid;

	dma_addw = ep->qp.sq_pgtbw_phys;
	ofwd_weq1.sq_page_tabwe_addw_wo = (u32) dma_addw;
	ofwd_weq1.sq_page_tabwe_addw_hi = (u32) ((u64) dma_addw >> 32);

	dma_addw = ep->qp.cq_pgtbw_phys;
	ofwd_weq1.cq_page_tabwe_addw_wo = (u32) dma_addw;
	ofwd_weq1.cq_page_tabwe_addw_hi = (u32) ((u64) dma_addw >> 32);

	ofwd_weq2.hdw.op_code = ISCSI_KWQE_OPCODE_OFFWOAD_CONN2;
	ofwd_weq2.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);

	dma_addw = ep->qp.wq_pgtbw_phys;
	ofwd_weq2.wq_page_tabwe_addw_wo = (u32) dma_addw;
	ofwd_weq2.wq_page_tabwe_addw_hi = (u32) ((u64) dma_addw >> 32);

	ptbw = (u32 *) ep->qp.sq_pgtbw_viwt;

	ofwd_weq2.sq_fiwst_pte.hi = *ptbw++;
	ofwd_weq2.sq_fiwst_pte.wo = *ptbw;

	ptbw = (u32 *) ep->qp.cq_pgtbw_viwt;
	ofwd_weq2.cq_fiwst_pte.hi = *ptbw++;
	ofwd_weq2.cq_fiwst_pte.wo = *ptbw;

	kwqe_aww[0] = (stwuct kwqe *) &ofwd_weq1;
	kwqe_aww[1] = (stwuct kwqe *) &ofwd_weq2;
	ofwd_weq2.num_additionaw_wqes = 0;

	if (hba->cnic && hba->cnic->submit_kwqes)
		wc = hba->cnic->submit_kwqes(hba->cnic, kwqe_aww, num_kwqes);

	wetuwn wc;
}


/**
 * bnx2i_5771x_send_conn_ofwd_weq - initiates iscsi connection context cweation
 * @hba: 		adaptew stwuctuwe pointew
 * @ep: 		endpoint (twanspowt identifiew) stwuctuwe
 *
 * 57710 specific - pwepawes and posts CONN_OFWD_WEQ1/2 KWQE
 */
static int bnx2i_5771x_send_conn_ofwd_weq(stwuct bnx2i_hba *hba,
					  stwuct bnx2i_endpoint *ep)
{
	stwuct kwqe *kwqe_aww[5];
	stwuct iscsi_kwqe_conn_offwoad1 ofwd_weq1;
	stwuct iscsi_kwqe_conn_offwoad2 ofwd_weq2;
	stwuct iscsi_kwqe_conn_offwoad3 ofwd_weq3[1];
	dma_addw_t dma_addw;
	int num_kwqes = 2;
	u32 *ptbw;
	int wc = -EINVAW;

	ofwd_weq1.hdw.op_code = ISCSI_KWQE_OPCODE_OFFWOAD_CONN1;
	ofwd_weq1.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);

	ofwd_weq1.iscsi_conn_id = (u16) ep->ep_iscsi_cid;

	dma_addw = ep->qp.sq_pgtbw_phys + ISCSI_SQ_DB_SIZE;
	ofwd_weq1.sq_page_tabwe_addw_wo = (u32) dma_addw;
	ofwd_weq1.sq_page_tabwe_addw_hi = (u32) ((u64) dma_addw >> 32);

	dma_addw = ep->qp.cq_pgtbw_phys + ISCSI_CQ_DB_SIZE;
	ofwd_weq1.cq_page_tabwe_addw_wo = (u32) dma_addw;
	ofwd_weq1.cq_page_tabwe_addw_hi = (u32) ((u64) dma_addw >> 32);

	ofwd_weq2.hdw.op_code = ISCSI_KWQE_OPCODE_OFFWOAD_CONN2;
	ofwd_weq2.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);

	dma_addw = ep->qp.wq_pgtbw_phys + ISCSI_WQ_DB_SIZE;
	ofwd_weq2.wq_page_tabwe_addw_wo = (u32) dma_addw;
	ofwd_weq2.wq_page_tabwe_addw_hi = (u32) ((u64) dma_addw >> 32);

	ptbw = (u32 *)((u8 *)ep->qp.sq_pgtbw_viwt + ISCSI_SQ_DB_SIZE);
	ofwd_weq2.sq_fiwst_pte.hi = *ptbw++;
	ofwd_weq2.sq_fiwst_pte.wo = *ptbw;

	ptbw = (u32 *)((u8 *)ep->qp.cq_pgtbw_viwt + ISCSI_CQ_DB_SIZE);
	ofwd_weq2.cq_fiwst_pte.hi = *ptbw++;
	ofwd_weq2.cq_fiwst_pte.wo = *ptbw;

	kwqe_aww[0] = (stwuct kwqe *) &ofwd_weq1;
	kwqe_aww[1] = (stwuct kwqe *) &ofwd_weq2;

	ofwd_weq2.num_additionaw_wqes = 1;
	memset(ofwd_weq3, 0x00, sizeof(ofwd_weq3[0]));
	ptbw = (u32 *)((u8 *)ep->qp.wq_pgtbw_viwt + ISCSI_WQ_DB_SIZE);
	ofwd_weq3[0].qp_fiwst_pte[0].hi = *ptbw++;
	ofwd_weq3[0].qp_fiwst_pte[0].wo = *ptbw;

	kwqe_aww[2] = (stwuct kwqe *) ofwd_weq3;
	/* need if we decide to go with muwtipwe KCQE's pew conn */
	num_kwqes += 1;

	if (hba->cnic && hba->cnic->submit_kwqes)
		wc = hba->cnic->submit_kwqes(hba->cnic, kwqe_aww, num_kwqes);

	wetuwn wc;
}

/**
 * bnx2i_send_conn_ofwd_weq - initiates iscsi connection context setup pwocess
 *
 * @hba: 		adaptew stwuctuwe pointew
 * @ep: 		endpoint (twanspowt identifiew) stwuctuwe
 *
 * this woutine pwepawes and posts CONN_OFWD_WEQ1/2 KWQE
 */
int bnx2i_send_conn_ofwd_weq(stwuct bnx2i_hba *hba, stwuct bnx2i_endpoint *ep)
{
	int wc;

	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		wc = bnx2i_5771x_send_conn_ofwd_weq(hba, ep);
	ewse
		wc = bnx2i_570x_send_conn_ofwd_weq(hba, ep);

	wetuwn wc;
}


/**
 * setup_qp_page_tabwes - iscsi QP page tabwe setup function
 * @ep:		endpoint (twanspowt identifiew) stwuctuwe
 *
 * Sets up page tabwes fow SQ/WQ/CQ, 1G/sec (5706/5708/5709) devices wequiwes
 * 	64-bit addwess in big endian fowmat. Wheweas 10G/sec (57710) wequiwes
 * 	PT in wittwe endian fowmat
 */
static void setup_qp_page_tabwes(stwuct bnx2i_endpoint *ep)
{
	int num_pages;
	u32 *ptbw;
	dma_addw_t page;
	int cnic_dev_10g;

	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		cnic_dev_10g = 1;
	ewse
		cnic_dev_10g = 0;

	/* SQ page tabwe */
	memset(ep->qp.sq_pgtbw_viwt, 0, ep->qp.sq_pgtbw_size);
	num_pages = ep->qp.sq_mem_size / CNIC_PAGE_SIZE;
	page = ep->qp.sq_phys;

	if (cnic_dev_10g)
		ptbw = (u32 *)((u8 *)ep->qp.sq_pgtbw_viwt + ISCSI_SQ_DB_SIZE);
	ewse
		ptbw = (u32 *) ep->qp.sq_pgtbw_viwt;
	whiwe (num_pages--) {
		if (cnic_dev_10g) {
			/* PTE is wwitten in wittwe endian fowmat fow 57710 */
			*ptbw = (u32) page;
			ptbw++;
			*ptbw = (u32) ((u64) page >> 32);
			ptbw++;
			page += CNIC_PAGE_SIZE;
		} ewse {
			/* PTE is wwitten in big endian fowmat fow
			 * 5706/5708/5709 devices */
			*ptbw = (u32) ((u64) page >> 32);
			ptbw++;
			*ptbw = (u32) page;
			ptbw++;
			page += CNIC_PAGE_SIZE;
		}
	}

	/* WQ page tabwe */
	memset(ep->qp.wq_pgtbw_viwt, 0, ep->qp.wq_pgtbw_size);
	num_pages = ep->qp.wq_mem_size / CNIC_PAGE_SIZE;
	page = ep->qp.wq_phys;

	if (cnic_dev_10g)
		ptbw = (u32 *)((u8 *)ep->qp.wq_pgtbw_viwt + ISCSI_WQ_DB_SIZE);
	ewse
		ptbw = (u32 *) ep->qp.wq_pgtbw_viwt;
	whiwe (num_pages--) {
		if (cnic_dev_10g) {
			/* PTE is wwitten in wittwe endian fowmat fow 57710 */
			*ptbw = (u32) page;
			ptbw++;
			*ptbw = (u32) ((u64) page >> 32);
			ptbw++;
			page += CNIC_PAGE_SIZE;
		} ewse {
			/* PTE is wwitten in big endian fowmat fow
			 * 5706/5708/5709 devices */
			*ptbw = (u32) ((u64) page >> 32);
			ptbw++;
			*ptbw = (u32) page;
			ptbw++;
			page += CNIC_PAGE_SIZE;
		}
	}

	/* CQ page tabwe */
	memset(ep->qp.cq_pgtbw_viwt, 0, ep->qp.cq_pgtbw_size);
	num_pages = ep->qp.cq_mem_size / CNIC_PAGE_SIZE;
	page = ep->qp.cq_phys;

	if (cnic_dev_10g)
		ptbw = (u32 *)((u8 *)ep->qp.cq_pgtbw_viwt + ISCSI_CQ_DB_SIZE);
	ewse
		ptbw = (u32 *) ep->qp.cq_pgtbw_viwt;
	whiwe (num_pages--) {
		if (cnic_dev_10g) {
			/* PTE is wwitten in wittwe endian fowmat fow 57710 */
			*ptbw = (u32) page;
			ptbw++;
			*ptbw = (u32) ((u64) page >> 32);
			ptbw++;
			page += CNIC_PAGE_SIZE;
		} ewse {
			/* PTE is wwitten in big endian fowmat fow
			 * 5706/5708/5709 devices */
			*ptbw = (u32) ((u64) page >> 32);
			ptbw++;
			*ptbw = (u32) page;
			ptbw++;
			page += CNIC_PAGE_SIZE;
		}
	}
}


/**
 * bnx2i_awwoc_qp_wesc - awwocates wequiwed wesouwces fow QP.
 * @hba:	adaptew stwuctuwe pointew
 * @ep:		endpoint (twanspowt identifiew) stwuctuwe
 *
 * Awwocate QP (twanspowt wayew fow iSCSI connection) wesouwces, DMA'abwe
 *	memowy fow SQ/WQ/CQ and page tabwes. EP stwuctuwe ewements such
 *	as pwoducew/consumew indexes/pointews, queue sizes and page tabwe
 *	contents awe setup
 */
int bnx2i_awwoc_qp_wesc(stwuct bnx2i_hba *hba, stwuct bnx2i_endpoint *ep)
{
	stwuct bnx2i_5771x_cq_db *cq_db;

	ep->hba = hba;
	ep->conn = NUWW;
	ep->ep_cid = ep->ep_iscsi_cid = ep->ep_pg_cid = 0;

	/* Awwocate page tabwe memowy fow SQ which is page awigned */
	ep->qp.sq_mem_size = hba->max_sqes * BNX2I_SQ_WQE_SIZE;
	ep->qp.sq_mem_size =
		(ep->qp.sq_mem_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;
	ep->qp.sq_pgtbw_size =
		(ep->qp.sq_mem_size / CNIC_PAGE_SIZE) * sizeof(void *);
	ep->qp.sq_pgtbw_size =
		(ep->qp.sq_pgtbw_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	ep->qp.sq_pgtbw_viwt =
		dma_awwoc_cohewent(&hba->pcidev->dev, ep->qp.sq_pgtbw_size,
				   &ep->qp.sq_pgtbw_phys, GFP_KEWNEW);
	if (!ep->qp.sq_pgtbw_viwt) {
		pwintk(KEWN_AWEWT "bnx2i: unabwe to awwoc SQ PT mem (%d)\n",
				  ep->qp.sq_pgtbw_size);
		goto mem_awwoc_eww;
	}

	/* Awwocate memowy awea fow actuaw SQ ewement */
	ep->qp.sq_viwt =
		dma_awwoc_cohewent(&hba->pcidev->dev, ep->qp.sq_mem_size,
				   &ep->qp.sq_phys, GFP_KEWNEW);
	if (!ep->qp.sq_viwt) {
		pwintk(KEWN_AWEWT "bnx2i: unabwe to awwoc SQ BD memowy %d\n",
				  ep->qp.sq_mem_size);
		goto mem_awwoc_eww;
	}

	ep->qp.sq_fiwst_qe = ep->qp.sq_viwt;
	ep->qp.sq_pwod_qe = ep->qp.sq_fiwst_qe;
	ep->qp.sq_cons_qe = ep->qp.sq_fiwst_qe;
	ep->qp.sq_wast_qe = &ep->qp.sq_fiwst_qe[hba->max_sqes - 1];
	ep->qp.sq_pwod_idx = 0;
	ep->qp.sq_cons_idx = 0;
	ep->qp.sqe_weft = hba->max_sqes;

	/* Awwocate page tabwe memowy fow CQ which is page awigned */
	ep->qp.cq_mem_size = hba->max_cqes * BNX2I_CQE_SIZE;
	ep->qp.cq_mem_size =
		(ep->qp.cq_mem_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;
	ep->qp.cq_pgtbw_size =
		(ep->qp.cq_mem_size / CNIC_PAGE_SIZE) * sizeof(void *);
	ep->qp.cq_pgtbw_size =
		(ep->qp.cq_pgtbw_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	ep->qp.cq_pgtbw_viwt =
		dma_awwoc_cohewent(&hba->pcidev->dev, ep->qp.cq_pgtbw_size,
				   &ep->qp.cq_pgtbw_phys, GFP_KEWNEW);
	if (!ep->qp.cq_pgtbw_viwt) {
		pwintk(KEWN_AWEWT "bnx2i: unabwe to awwoc CQ PT memowy %d\n",
				  ep->qp.cq_pgtbw_size);
		goto mem_awwoc_eww;
	}

	/* Awwocate memowy awea fow actuaw CQ ewement */
	ep->qp.cq_viwt =
		dma_awwoc_cohewent(&hba->pcidev->dev, ep->qp.cq_mem_size,
				   &ep->qp.cq_phys, GFP_KEWNEW);
	if (!ep->qp.cq_viwt) {
		pwintk(KEWN_AWEWT "bnx2i: unabwe to awwoc CQ BD memowy %d\n",
				  ep->qp.cq_mem_size);
		goto mem_awwoc_eww;
	}

	ep->qp.cq_fiwst_qe = ep->qp.cq_viwt;
	ep->qp.cq_pwod_qe = ep->qp.cq_fiwst_qe;
	ep->qp.cq_cons_qe = ep->qp.cq_fiwst_qe;
	ep->qp.cq_wast_qe = &ep->qp.cq_fiwst_qe[hba->max_cqes - 1];
	ep->qp.cq_pwod_idx = 0;
	ep->qp.cq_cons_idx = 0;
	ep->qp.cqe_weft = hba->max_cqes;
	ep->qp.cqe_exp_seq_sn = ISCSI_INITIAW_SN;
	ep->qp.cqe_size = hba->max_cqes;

	/* Invawidate aww EQ CQE index, weq onwy fow 57710 */
	cq_db = (stwuct bnx2i_5771x_cq_db *) ep->qp.cq_pgtbw_viwt;
	memset(cq_db->sqn, 0xFF, sizeof(cq_db->sqn[0]) * BNX2X_MAX_CQS);

	/* Awwocate page tabwe memowy fow WQ which is page awigned */
	ep->qp.wq_mem_size = hba->max_wqes * BNX2I_WQ_WQE_SIZE;
	ep->qp.wq_mem_size =
		(ep->qp.wq_mem_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;
	ep->qp.wq_pgtbw_size =
		(ep->qp.wq_mem_size / CNIC_PAGE_SIZE) * sizeof(void *);
	ep->qp.wq_pgtbw_size =
		(ep->qp.wq_pgtbw_size + (CNIC_PAGE_SIZE - 1)) & CNIC_PAGE_MASK;

	ep->qp.wq_pgtbw_viwt =
		dma_awwoc_cohewent(&hba->pcidev->dev, ep->qp.wq_pgtbw_size,
				   &ep->qp.wq_pgtbw_phys, GFP_KEWNEW);
	if (!ep->qp.wq_pgtbw_viwt) {
		pwintk(KEWN_AWEWT "bnx2i: unabwe to awwoc WQ PT mem %d\n",
				  ep->qp.wq_pgtbw_size);
		goto mem_awwoc_eww;
	}

	/* Awwocate memowy awea fow actuaw WQ ewement */
	ep->qp.wq_viwt =
		dma_awwoc_cohewent(&hba->pcidev->dev, ep->qp.wq_mem_size,
				   &ep->qp.wq_phys, GFP_KEWNEW);
	if (!ep->qp.wq_viwt) {
		pwintk(KEWN_AWEWT "bnx2i: unabwe to awwoc WQ BD memowy %d\n",
				  ep->qp.wq_mem_size);
		goto mem_awwoc_eww;
	}

	ep->qp.wq_fiwst_qe = ep->qp.wq_viwt;
	ep->qp.wq_pwod_qe = ep->qp.wq_fiwst_qe;
	ep->qp.wq_cons_qe = ep->qp.wq_fiwst_qe;
	ep->qp.wq_wast_qe = &ep->qp.wq_fiwst_qe[hba->max_wqes - 1];
	ep->qp.wq_pwod_idx = 0x8000;
	ep->qp.wq_cons_idx = 0;
	ep->qp.wqe_weft = hba->max_wqes;

	setup_qp_page_tabwes(ep);

	wetuwn 0;

mem_awwoc_eww:
	bnx2i_fwee_qp_wesc(hba, ep);
	wetuwn -ENOMEM;
}



/**
 * bnx2i_fwee_qp_wesc - fwee memowy wesouwces hewd by QP
 * @hba:	adaptew stwuctuwe pointew
 * @ep:	endpoint (twanspowt identifiew) stwuctuwe
 *
 * Fwee QP wesouwces - SQ/WQ/CQ memowy and page tabwes.
 */
void bnx2i_fwee_qp_wesc(stwuct bnx2i_hba *hba, stwuct bnx2i_endpoint *ep)
{
	if (ep->qp.ctx_base) {
		iounmap(ep->qp.ctx_base);
		ep->qp.ctx_base = NUWW;
	}
	/* Fwee SQ mem */
	if (ep->qp.sq_pgtbw_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev, ep->qp.sq_pgtbw_size,
				  ep->qp.sq_pgtbw_viwt, ep->qp.sq_pgtbw_phys);
		ep->qp.sq_pgtbw_viwt = NUWW;
		ep->qp.sq_pgtbw_phys = 0;
	}
	if (ep->qp.sq_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev, ep->qp.sq_mem_size,
				  ep->qp.sq_viwt, ep->qp.sq_phys);
		ep->qp.sq_viwt = NUWW;
		ep->qp.sq_phys = 0;
	}

	/* Fwee WQ mem */
	if (ep->qp.wq_pgtbw_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev, ep->qp.wq_pgtbw_size,
				  ep->qp.wq_pgtbw_viwt, ep->qp.wq_pgtbw_phys);
		ep->qp.wq_pgtbw_viwt = NUWW;
		ep->qp.wq_pgtbw_phys = 0;
	}
	if (ep->qp.wq_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev, ep->qp.wq_mem_size,
				  ep->qp.wq_viwt, ep->qp.wq_phys);
		ep->qp.wq_viwt = NUWW;
		ep->qp.wq_phys = 0;
	}

	/* Fwee CQ mem */
	if (ep->qp.cq_pgtbw_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev, ep->qp.cq_pgtbw_size,
				  ep->qp.cq_pgtbw_viwt, ep->qp.cq_pgtbw_phys);
		ep->qp.cq_pgtbw_viwt = NUWW;
		ep->qp.cq_pgtbw_phys = 0;
	}
	if (ep->qp.cq_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev, ep->qp.cq_mem_size,
				  ep->qp.cq_viwt, ep->qp.cq_phys);
		ep->qp.cq_viwt = NUWW;
		ep->qp.cq_phys = 0;
	}
}


/**
 * bnx2i_send_fw_iscsi_init_msg - initiates initiaw handshake with iscsi f/w
 * @hba:	adaptew stwuctuwe pointew
 *
 * Send down iscsi_init KWQEs which initiates the initiaw handshake with the f/w
 * 	This wesuwts in iSCSi suppowt vawidation and on-chip context managew
 * 	initiawization.  Fiwmwawe compwetes this handshake with a CQE cawwying
 * 	the wesuwt of iscsi suppowt vawidation. Pawametew cawwied by
 * 	iscsi init wequest detewmines the numbew of offwoaded connection and
 * 	towewance wevew fow iscsi pwotocow viowation this hba/chip can suppowt
 */
int bnx2i_send_fw_iscsi_init_msg(stwuct bnx2i_hba *hba)
{
	stwuct kwqe *kwqe_aww[3];
	stwuct iscsi_kwqe_init1 iscsi_init;
	stwuct iscsi_kwqe_init2 iscsi_init2;
	int wc = 0;
	u64 mask64;

	memset(&iscsi_init, 0x00, sizeof(stwuct iscsi_kwqe_init1));
	memset(&iscsi_init2, 0x00, sizeof(stwuct iscsi_kwqe_init2));

	bnx2i_adjust_qp_size(hba);

	iscsi_init.fwags =
		(CNIC_PAGE_BITS - 8) << ISCSI_KWQE_INIT1_PAGE_SIZE_SHIFT;
	if (en_tcp_dack)
		iscsi_init.fwags |= ISCSI_KWQE_INIT1_DEWAYED_ACK_ENABWE;
	iscsi_init.wesewved0 = 0;
	iscsi_init.num_cqs = 1;
	iscsi_init.hdw.op_code = ISCSI_KWQE_OPCODE_INIT1;
	iscsi_init.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);

	iscsi_init.dummy_buffew_addw_wo = (u32) hba->dummy_buf_dma;
	iscsi_init.dummy_buffew_addw_hi =
		(u32) ((u64) hba->dummy_buf_dma >> 32);

	hba->num_cceww = hba->max_sqes >> 1;
	hba->ctx_cceww_tasks =
			((hba->num_cceww & 0xFFFF) | (hba->max_sqes << 16));
	iscsi_init.num_ccewws_pew_conn = hba->num_cceww;
	iscsi_init.num_tasks_pew_conn = hba->max_sqes;
	iscsi_init.sq_wqes_pew_page = CNIC_PAGE_SIZE / BNX2I_SQ_WQE_SIZE;
	iscsi_init.sq_num_wqes = hba->max_sqes;
	iscsi_init.cq_wog_wqes_pew_page =
		(u8) bnx2i_powew_of2(CNIC_PAGE_SIZE / BNX2I_CQE_SIZE);
	iscsi_init.cq_num_wqes = hba->max_cqes;
	iscsi_init.cq_num_pages = (hba->max_cqes * BNX2I_CQE_SIZE +
				   (CNIC_PAGE_SIZE - 1)) / CNIC_PAGE_SIZE;
	iscsi_init.sq_num_pages = (hba->max_sqes * BNX2I_SQ_WQE_SIZE +
				   (CNIC_PAGE_SIZE - 1)) / CNIC_PAGE_SIZE;
	iscsi_init.wq_buffew_size = BNX2I_WQ_WQE_SIZE;
	iscsi_init.wq_num_wqes = hba->max_wqes;


	iscsi_init2.hdw.op_code = ISCSI_KWQE_OPCODE_INIT2;
	iscsi_init2.hdw.fwags =
		(ISCSI_KWQE_WAYEW_CODE << ISCSI_KWQE_HEADEW_WAYEW_CODE_SHIFT);
	iscsi_init2.max_cq_sqn = hba->max_cqes * 2 + 1;
	mask64 = 0x0UWW;
	mask64 |= (
		/* CISCO MDS */
		(1UW <<
		  ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_TTT_NOT_WSWV) |
		/* HP MSA1510i */
		(1UW <<
		  ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_EXP_DATASN) |
		/* EMC */
		(1UWW << ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_WUN));
	if (ewwow_mask1) {
		iscsi_init2.ewwow_bit_map[0] = ewwow_mask1;
		mask64 ^= (u32)(mask64);
		mask64 |= ewwow_mask1;
	} ewse
		iscsi_init2.ewwow_bit_map[0] = (u32) mask64;

	if (ewwow_mask2) {
		iscsi_init2.ewwow_bit_map[1] = ewwow_mask2;
		mask64 &= 0xffffffff;
		mask64 |= ((u64)ewwow_mask2 << 32);
	} ewse
		iscsi_init2.ewwow_bit_map[1] = (u32) (mask64 >> 32);

	iscsi_ewwow_mask = mask64;

	kwqe_aww[0] = (stwuct kwqe *) &iscsi_init;
	kwqe_aww[1] = (stwuct kwqe *) &iscsi_init2;

	if (hba->cnic && hba->cnic->submit_kwqes)
		wc = hba->cnic->submit_kwqes(hba->cnic, kwqe_aww, 2);
	wetuwn wc;
}


/**
 * bnx2i_pwocess_scsi_cmd_wesp - this function handwes scsi cmd compwetion.
 * @session:	iscsi session
 * @bnx2i_conn:	bnx2i connection
 * @cqe:	pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess SCSI CMD Wesponse CQE & compwete the wequest to SCSI-MW
 */
int bnx2i_pwocess_scsi_cmd_wesp(stwuct iscsi_session *session,
				stwuct bnx2i_conn *bnx2i_conn,
				stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct bnx2i_hba *hba = bnx2i_conn->hba;
	stwuct bnx2i_cmd_wesponse *wesp_cqe;
	stwuct bnx2i_cmd *bnx2i_cmd;
	stwuct iscsi_task *task;
	stwuct iscsi_scsi_wsp *hdw;
	u32 datawen = 0;

	wesp_cqe = (stwuct bnx2i_cmd_wesponse *)cqe;
	spin_wock_bh(&session->back_wock);
	task = iscsi_itt_to_task(conn,
				 wesp_cqe->itt & ISCSI_CMD_WESPONSE_INDEX);
	if (!task)
		goto faiw;

	bnx2i_cmd = task->dd_data;

	if (bnx2i_cmd->weq.op_attw & ISCSI_CMD_WEQUEST_WEAD) {
		conn->datain_pdus_cnt +=
			wesp_cqe->task_stat.wead_stat.num_data_ins;
		conn->wxdata_octets +=
			bnx2i_cmd->weq.totaw_data_twansfew_wength;
		ADD_STATS_64(hba, wx_pdus,
			     wesp_cqe->task_stat.wead_stat.num_data_ins);
		ADD_STATS_64(hba, wx_bytes,
			     bnx2i_cmd->weq.totaw_data_twansfew_wength);
	} ewse {
		conn->dataout_pdus_cnt +=
			wesp_cqe->task_stat.wwite_stat.num_data_outs;
		conn->w2t_pdus_cnt +=
			wesp_cqe->task_stat.wwite_stat.num_w2ts;
		conn->txdata_octets +=
			bnx2i_cmd->weq.totaw_data_twansfew_wength;
		ADD_STATS_64(hba, tx_pdus,
			     wesp_cqe->task_stat.wwite_stat.num_data_outs);
		ADD_STATS_64(hba, tx_bytes,
			     bnx2i_cmd->weq.totaw_data_twansfew_wength);
		ADD_STATS_64(hba, wx_pdus,
			     wesp_cqe->task_stat.wwite_stat.num_w2ts);
	}
	bnx2i_iscsi_unmap_sg_wist(bnx2i_cmd);

	hdw = (stwuct iscsi_scsi_wsp *)task->hdw;
	wesp_cqe = (stwuct bnx2i_cmd_wesponse *)cqe;
	hdw->opcode = wesp_cqe->op_code;
	hdw->max_cmdsn = cpu_to_be32(wesp_cqe->max_cmd_sn);
	hdw->exp_cmdsn = cpu_to_be32(wesp_cqe->exp_cmd_sn);
	hdw->wesponse = wesp_cqe->wesponse;
	hdw->cmd_status = wesp_cqe->status;
	hdw->fwags = wesp_cqe->wesponse_fwags;
	hdw->wesiduaw_count = cpu_to_be32(wesp_cqe->wesiduaw_count);

	if (wesp_cqe->op_code == ISCSI_OP_SCSI_DATA_IN)
		goto done;

	if (wesp_cqe->status == SAM_STAT_CHECK_CONDITION) {
		datawen = wesp_cqe->data_wength;
		if (datawen < 2)
			goto done;

		if (datawen > BNX2I_WQ_WQE_SIZE) {
			iscsi_conn_pwintk(KEWN_EWW, conn,
					  "sense data wen %d > WQ sz\n",
					  datawen);
			datawen = BNX2I_WQ_WQE_SIZE;
		} ewse if (datawen > ISCSI_DEF_MAX_WECV_SEG_WEN) {
			iscsi_conn_pwintk(KEWN_EWW, conn,
					  "sense data wen %d > conn data\n",
					  datawen);
			datawen = ISCSI_DEF_MAX_WECV_SEG_WEN;
		}

		bnx2i_get_wq_buf(bnx2i_cmd->conn, conn->data, datawen);
		bnx2i_put_wq_buf(bnx2i_cmd->conn, 1);
	}

done:
	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)hdw,
			     conn->data, datawen);
faiw:
	spin_unwock_bh(&session->back_wock);
	wetuwn 0;
}


/**
 * bnx2i_pwocess_wogin_wesp - this function handwes iscsi wogin wesponse
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess Wogin Wesponse CQE & compwete it to open-iscsi usew daemon
 */
static int bnx2i_pwocess_wogin_wesp(stwuct iscsi_session *session,
				    stwuct bnx2i_conn *bnx2i_conn,
				    stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_task *task;
	stwuct bnx2i_wogin_wesponse *wogin;
	stwuct iscsi_wogin_wsp *wesp_hdw;
	int pwd_wen;
	int pad_wen;

	wogin = (stwuct bnx2i_wogin_wesponse *) cqe;
	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(conn,
				 wogin->itt & ISCSI_WOGIN_WESPONSE_INDEX);
	if (!task)
		goto done;

	wesp_hdw = (stwuct iscsi_wogin_wsp *) &bnx2i_conn->gen_pdu.wesp_hdw;
	memset(wesp_hdw, 0, sizeof(stwuct iscsi_hdw));
	wesp_hdw->opcode = wogin->op_code;
	wesp_hdw->fwags = wogin->wesponse_fwags;
	wesp_hdw->max_vewsion = wogin->vewsion_max;
	wesp_hdw->active_vewsion = wogin->vewsion_active;
	wesp_hdw->hwength = 0;

	hton24(wesp_hdw->dwength, wogin->data_wength);
	memcpy(wesp_hdw->isid, &wogin->isid_wo, 6);
	wesp_hdw->tsih = cpu_to_be16(wogin->tsih);
	wesp_hdw->itt = task->hdw->itt;
	wesp_hdw->statsn = cpu_to_be32(wogin->stat_sn);
	wesp_hdw->exp_cmdsn = cpu_to_be32(wogin->exp_cmd_sn);
	wesp_hdw->max_cmdsn = cpu_to_be32(wogin->max_cmd_sn);
	wesp_hdw->status_cwass = wogin->status_cwass;
	wesp_hdw->status_detaiw = wogin->status_detaiw;
	pwd_wen = wogin->data_wength;
	bnx2i_conn->gen_pdu.wesp_ww_ptw =
					bnx2i_conn->gen_pdu.wesp_buf + pwd_wen;

	pad_wen = 0;
	if (pwd_wen & 0x3)
		pad_wen = 4 - (pwd_wen % 4);

	if (pad_wen) {
		int i = 0;
		fow (i = 0; i < pad_wen; i++) {
			bnx2i_conn->gen_pdu.wesp_ww_ptw[0] = 0;
			bnx2i_conn->gen_pdu.wesp_ww_ptw++;
		}
	}

	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)wesp_hdw,
		bnx2i_conn->gen_pdu.wesp_buf,
		bnx2i_conn->gen_pdu.wesp_ww_ptw - bnx2i_conn->gen_pdu.wesp_buf);
done:
	spin_unwock(&session->back_wock);
	wetuwn 0;
}


/**
 * bnx2i_pwocess_text_wesp - this function handwes iscsi text wesponse
 * @session:	iscsi session pointew
 * @bnx2i_conn:	iscsi connection pointew
 * @cqe:	pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI Text Wesponse CQE&  compwete it to open-iscsi usew daemon
 */
static int bnx2i_pwocess_text_wesp(stwuct iscsi_session *session,
				   stwuct bnx2i_conn *bnx2i_conn,
				   stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_task *task;
	stwuct bnx2i_text_wesponse *text;
	stwuct iscsi_text_wsp *wesp_hdw;
	int pwd_wen;
	int pad_wen;

	text = (stwuct bnx2i_text_wesponse *) cqe;
	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(conn, text->itt & ISCSI_WOGIN_WESPONSE_INDEX);
	if (!task)
		goto done;

	wesp_hdw = (stwuct iscsi_text_wsp *)&bnx2i_conn->gen_pdu.wesp_hdw;
	memset(wesp_hdw, 0, sizeof(stwuct iscsi_hdw));
	wesp_hdw->opcode = text->op_code;
	wesp_hdw->fwags = text->wesponse_fwags;
	wesp_hdw->hwength = 0;

	hton24(wesp_hdw->dwength, text->data_wength);
	wesp_hdw->itt = task->hdw->itt;
	wesp_hdw->ttt = cpu_to_be32(text->ttt);
	wesp_hdw->statsn = task->hdw->exp_statsn;
	wesp_hdw->exp_cmdsn = cpu_to_be32(text->exp_cmd_sn);
	wesp_hdw->max_cmdsn = cpu_to_be32(text->max_cmd_sn);
	pwd_wen = text->data_wength;
	bnx2i_conn->gen_pdu.wesp_ww_ptw = bnx2i_conn->gen_pdu.wesp_buf +
					  pwd_wen;
	pad_wen = 0;
	if (pwd_wen & 0x3)
		pad_wen = 4 - (pwd_wen % 4);

	if (pad_wen) {
		int i = 0;
		fow (i = 0; i < pad_wen; i++) {
			bnx2i_conn->gen_pdu.wesp_ww_ptw[0] = 0;
			bnx2i_conn->gen_pdu.wesp_ww_ptw++;
		}
	}
	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)wesp_hdw,
			     bnx2i_conn->gen_pdu.wesp_buf,
			     bnx2i_conn->gen_pdu.wesp_ww_ptw -
			     bnx2i_conn->gen_pdu.wesp_buf);
done:
	spin_unwock(&session->back_wock);
	wetuwn 0;
}


/**
 * bnx2i_pwocess_tmf_wesp - this function handwes iscsi TMF wesponse
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI TMF Wesponse CQE and wake up the dwivew eh thwead.
 */
static int bnx2i_pwocess_tmf_wesp(stwuct iscsi_session *session,
				  stwuct bnx2i_conn *bnx2i_conn,
				  stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_task *task;
	stwuct bnx2i_tmf_wesponse *tmf_cqe;
	stwuct iscsi_tm_wsp *wesp_hdw;

	tmf_cqe = (stwuct bnx2i_tmf_wesponse *)cqe;
	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(conn,
				 tmf_cqe->itt & ISCSI_TMF_WESPONSE_INDEX);
	if (!task)
		goto done;

	wesp_hdw = (stwuct iscsi_tm_wsp *) &bnx2i_conn->gen_pdu.wesp_hdw;
	memset(wesp_hdw, 0, sizeof(stwuct iscsi_hdw));
	wesp_hdw->opcode = tmf_cqe->op_code;
	wesp_hdw->max_cmdsn = cpu_to_be32(tmf_cqe->max_cmd_sn);
	wesp_hdw->exp_cmdsn = cpu_to_be32(tmf_cqe->exp_cmd_sn);
	wesp_hdw->itt = task->hdw->itt;
	wesp_hdw->wesponse = tmf_cqe->wesponse;

	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)wesp_hdw, NUWW, 0);
done:
	spin_unwock(&session->back_wock);
	wetuwn 0;
}

/**
 * bnx2i_pwocess_wogout_wesp - this function handwes iscsi wogout wesponse
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI Wogout Wesponse CQE & make function caww to
 * notify the usew daemon.
 */
static int bnx2i_pwocess_wogout_wesp(stwuct iscsi_session *session,
				     stwuct bnx2i_conn *bnx2i_conn,
				     stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_task *task;
	stwuct bnx2i_wogout_wesponse *wogout;
	stwuct iscsi_wogout_wsp *wesp_hdw;

	wogout = (stwuct bnx2i_wogout_wesponse *) cqe;
	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(conn,
				 wogout->itt & ISCSI_WOGOUT_WESPONSE_INDEX);
	if (!task)
		goto done;

	wesp_hdw = (stwuct iscsi_wogout_wsp *) &bnx2i_conn->gen_pdu.wesp_hdw;
	memset(wesp_hdw, 0, sizeof(stwuct iscsi_hdw));
	wesp_hdw->opcode = wogout->op_code;
	wesp_hdw->fwags = wogout->wesponse;
	wesp_hdw->hwength = 0;

	wesp_hdw->itt = task->hdw->itt;
	wesp_hdw->statsn = task->hdw->exp_statsn;
	wesp_hdw->exp_cmdsn = cpu_to_be32(wogout->exp_cmd_sn);
	wesp_hdw->max_cmdsn = cpu_to_be32(wogout->max_cmd_sn);

	wesp_hdw->t2wait = cpu_to_be32(wogout->time_to_wait);
	wesp_hdw->t2wetain = cpu_to_be32(wogout->time_to_wetain);

	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)wesp_hdw, NUWW, 0);

	bnx2i_conn->ep->state = EP_STATE_WOGOUT_WESP_WCVD;
done:
	spin_unwock(&session->back_wock);
	wetuwn 0;
}

/**
 * bnx2i_pwocess_nopin_wocaw_cmpw - this function handwes iscsi nopin CQE
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI NOPIN wocaw compwetion CQE, fwees IIT and command stwuctuwes
 */
static void bnx2i_pwocess_nopin_wocaw_cmpw(stwuct iscsi_session *session,
					   stwuct bnx2i_conn *bnx2i_conn,
					   stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct bnx2i_nop_in_msg *nop_in;
	stwuct iscsi_task *task;

	nop_in = (stwuct bnx2i_nop_in_msg *)cqe;
	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(conn,
				 nop_in->itt & ISCSI_NOP_IN_MSG_INDEX);
	if (task)
		__iscsi_put_task(task);
	spin_unwock(&session->back_wock);
}

/**
 * bnx2i_unsow_pdu_adjust_wq - makes adjustments to WQ aftew unsow pdu is wecvd
 * @bnx2i_conn:	iscsi connection
 *
 * Fiwmwawe advances WQ pwoducew index fow evewy unsowicited PDU even if
 *	paywoad data wength is '0'. This function makes cowwesponding
 *	adjustments on the dwivew side to match this f/w behaviow
 */
static void bnx2i_unsow_pdu_adjust_wq(stwuct bnx2i_conn *bnx2i_conn)
{
	chaw dummy_wq_data[2];
	bnx2i_get_wq_buf(bnx2i_conn, dummy_wq_data, 1);
	bnx2i_put_wq_buf(bnx2i_conn, 1);
}


/**
 * bnx2i_pwocess_nopin_mesg - this function handwes iscsi nopin CQE
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI tawget's pwoactive iSCSI NOPIN wequest
 */
static int bnx2i_pwocess_nopin_mesg(stwuct iscsi_session *session,
				     stwuct bnx2i_conn *bnx2i_conn,
				     stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_task *task;
	stwuct bnx2i_nop_in_msg *nop_in;
	stwuct iscsi_nopin *hdw;
	int tgt_async_nop = 0;

	nop_in = (stwuct bnx2i_nop_in_msg *)cqe;

	spin_wock(&session->back_wock);
	hdw = (stwuct iscsi_nopin *)&bnx2i_conn->gen_pdu.wesp_hdw;
	memset(hdw, 0, sizeof(stwuct iscsi_hdw));
	hdw->opcode = nop_in->op_code;
	hdw->max_cmdsn = cpu_to_be32(nop_in->max_cmd_sn);
	hdw->exp_cmdsn = cpu_to_be32(nop_in->exp_cmd_sn);
	hdw->ttt = cpu_to_be32(nop_in->ttt);

	if (nop_in->itt == (u16) WESEWVED_ITT) {
		bnx2i_unsow_pdu_adjust_wq(bnx2i_conn);
		hdw->itt = WESEWVED_ITT;
		tgt_async_nop = 1;
		goto done;
	}

	/* this is a wesponse to one of ouw nop-outs */
	task = iscsi_itt_to_task(conn,
			 (itt_t) (nop_in->itt & ISCSI_NOP_IN_MSG_INDEX));
	if (task) {
		hdw->fwags = ISCSI_FWAG_CMD_FINAW;
		hdw->itt = task->hdw->itt;
		hdw->ttt = cpu_to_be32(nop_in->ttt);
		memcpy(&hdw->wun, nop_in->wun, 8);
	}
done:
	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)hdw, NUWW, 0);
	spin_unwock(&session->back_wock);

	wetuwn tgt_async_nop;
}


/**
 * bnx2i_pwocess_async_mesg - this function handwes iscsi async message
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI ASYNC Message
 */
static void bnx2i_pwocess_async_mesg(stwuct iscsi_session *session,
				     stwuct bnx2i_conn *bnx2i_conn,
				     stwuct cqe *cqe)
{
	stwuct bnx2i_async_msg *async_cqe;
	stwuct iscsi_async *wesp_hdw;
	u8 async_event;

	bnx2i_unsow_pdu_adjust_wq(bnx2i_conn);

	async_cqe = (stwuct bnx2i_async_msg *)cqe;
	async_event = async_cqe->async_event;

	if (async_event == ISCSI_ASYNC_MSG_SCSI_EVENT) {
		iscsi_conn_pwintk(KEWN_AWEWT, bnx2i_conn->cws_conn->dd_data,
				  "async: scsi events not suppowted\n");
		wetuwn;
	}

	spin_wock(&session->back_wock);
	wesp_hdw = (stwuct iscsi_async *) &bnx2i_conn->gen_pdu.wesp_hdw;
	memset(wesp_hdw, 0, sizeof(stwuct iscsi_hdw));
	wesp_hdw->opcode = async_cqe->op_code;
	wesp_hdw->fwags = 0x80;

	memcpy(&wesp_hdw->wun, async_cqe->wun, 8);
	wesp_hdw->exp_cmdsn = cpu_to_be32(async_cqe->exp_cmd_sn);
	wesp_hdw->max_cmdsn = cpu_to_be32(async_cqe->max_cmd_sn);

	wesp_hdw->async_event = async_cqe->async_event;
	wesp_hdw->async_vcode = async_cqe->async_vcode;

	wesp_hdw->pawam1 = cpu_to_be16(async_cqe->pawam1);
	wesp_hdw->pawam2 = cpu_to_be16(async_cqe->pawam2);
	wesp_hdw->pawam3 = cpu_to_be16(async_cqe->pawam3);

	__iscsi_compwete_pdu(bnx2i_conn->cws_conn->dd_data,
			     (stwuct iscsi_hdw *)wesp_hdw, NUWW, 0);
	spin_unwock(&session->back_wock);
}


/**
 * bnx2i_pwocess_weject_mesg - pwocess iscsi weject pdu
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess iSCSI WEJECT message
 */
static void bnx2i_pwocess_weject_mesg(stwuct iscsi_session *session,
				      stwuct bnx2i_conn *bnx2i_conn,
				      stwuct cqe *cqe)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct bnx2i_weject_msg *weject;
	stwuct iscsi_weject *hdw;

	weject = (stwuct bnx2i_weject_msg *) cqe;
	if (weject->data_wength) {
		bnx2i_get_wq_buf(bnx2i_conn, conn->data, weject->data_wength);
		bnx2i_put_wq_buf(bnx2i_conn, 1);
	} ewse
		bnx2i_unsow_pdu_adjust_wq(bnx2i_conn);

	spin_wock(&session->back_wock);
	hdw = (stwuct iscsi_weject *) &bnx2i_conn->gen_pdu.wesp_hdw;
	memset(hdw, 0, sizeof(stwuct iscsi_hdw));
	hdw->opcode = weject->op_code;
	hdw->weason = weject->weason;
	hton24(hdw->dwength, weject->data_wength);
	hdw->max_cmdsn = cpu_to_be32(weject->max_cmd_sn);
	hdw->exp_cmdsn = cpu_to_be32(weject->exp_cmd_sn);
	hdw->ffffffff = cpu_to_be32(WESEWVED_ITT);
	__iscsi_compwete_pdu(conn, (stwuct iscsi_hdw *)hdw, conn->data,
			     weject->data_wength);
	spin_unwock(&session->back_wock);
}

/**
 * bnx2i_pwocess_cmd_cweanup_wesp - pwocess scsi command cwean-up compwetion
 * @session:		iscsi session pointew
 * @bnx2i_conn:		iscsi connection pointew
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * pwocess command cweanup wesponse CQE duwing conn shutdown ow ewwow wecovewy
 */
static void bnx2i_pwocess_cmd_cweanup_wesp(stwuct iscsi_session *session,
					   stwuct bnx2i_conn *bnx2i_conn,
					   stwuct cqe *cqe)
{
	stwuct bnx2i_cweanup_wesponse *cmd_cwean_wsp;
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_task *task;

	cmd_cwean_wsp = (stwuct bnx2i_cweanup_wesponse *)cqe;
	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(conn,
			cmd_cwean_wsp->itt & ISCSI_CWEANUP_WESPONSE_INDEX);
	if (!task)
		pwintk(KEWN_AWEWT "bnx2i: cmd cwean ITT %x not active\n",
			cmd_cwean_wsp->itt & ISCSI_CWEANUP_WESPONSE_INDEX);
	spin_unwock(&session->back_wock);
	compwete(&bnx2i_conn->cmd_cweanup_cmpw);
}


/**
 * bnx2i_pewcpu_io_thwead - thwead pew cpu fow ios
 *
 * @awg:	ptw to bnx2i_pewcpu_info stwuctuwe
 */
int bnx2i_pewcpu_io_thwead(void *awg)
{
	stwuct bnx2i_pewcpu_s *p = awg;
	stwuct bnx2i_wowk *wowk, *tmp;
	WIST_HEAD(wowk_wist);

	set_usew_nice(cuwwent, MIN_NICE);

	whiwe (!kthwead_shouwd_stop()) {
		spin_wock_bh(&p->p_wowk_wock);
		whiwe (!wist_empty(&p->wowk_wist)) {
			wist_spwice_init(&p->wowk_wist, &wowk_wist);
			spin_unwock_bh(&p->p_wowk_wock);

			wist_fow_each_entwy_safe(wowk, tmp, &wowk_wist, wist) {
				wist_dew_init(&wowk->wist);
				/* wowk awwocated in the bh, fweed hewe */
				bnx2i_pwocess_scsi_cmd_wesp(wowk->session,
							    wowk->bnx2i_conn,
							    &wowk->cqe);
				atomic_dec(&wowk->bnx2i_conn->wowk_cnt);
				kfwee(wowk);
			}
			spin_wock_bh(&p->p_wowk_wock);
		}
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		spin_unwock_bh(&p->p_wowk_wock);
		scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}


/**
 * bnx2i_queue_scsi_cmd_wesp - queue cmd compwetion to the pewcpu thwead
 * @session:		iscsi session
 * @bnx2i_conn:		bnx2i connection
 * @cqe:		pointew to newwy DMA'ed CQE entwy fow pwocessing
 *
 * this function is cawwed by genewic KCQ handwew to queue aww pending cmd
 * compwetion CQEs
 *
 * The impwementation is to queue the cmd wesponse based on the
 * wast wecowded command fow the given connection.  The
 * cpu_id gets wecowded upon task_xmit.  No out-of-owdew compwetion!
 */
static int bnx2i_queue_scsi_cmd_wesp(stwuct iscsi_session *session,
				     stwuct bnx2i_conn *bnx2i_conn,
				     stwuct bnx2i_nop_in_msg *cqe)
{
	stwuct bnx2i_wowk *bnx2i_wowk = NUWW;
	stwuct bnx2i_pewcpu_s *p = NUWW;
	stwuct iscsi_task *task;
	stwuct scsi_cmnd *sc;
	int wc = 0;

	spin_wock(&session->back_wock);
	task = iscsi_itt_to_task(bnx2i_conn->cws_conn->dd_data,
				 cqe->itt & ISCSI_CMD_WESPONSE_INDEX);
	if (!task || !task->sc) {
		spin_unwock(&session->back_wock);
		wetuwn -EINVAW;
	}
	sc = task->sc;

	spin_unwock(&session->back_wock);

	p = &pew_cpu(bnx2i_pewcpu, bwk_mq_wq_cpu(scsi_cmd_to_wq(sc)));
	spin_wock(&p->p_wowk_wock);
	if (unwikewy(!p->iothwead)) {
		wc = -EINVAW;
		goto eww;
	}
	/* Awwoc and copy to the cqe */
	bnx2i_wowk = kzawwoc(sizeof(stwuct bnx2i_wowk), GFP_ATOMIC);
	if (bnx2i_wowk) {
		INIT_WIST_HEAD(&bnx2i_wowk->wist);
		bnx2i_wowk->session = session;
		bnx2i_wowk->bnx2i_conn = bnx2i_conn;
		memcpy(&bnx2i_wowk->cqe, cqe, sizeof(stwuct cqe));
		wist_add_taiw(&bnx2i_wowk->wist, &p->wowk_wist);
		atomic_inc(&bnx2i_conn->wowk_cnt);
		wake_up_pwocess(p->iothwead);
		spin_unwock(&p->p_wowk_wock);
		goto done;
	} ewse
		wc = -ENOMEM;
eww:
	spin_unwock(&p->p_wowk_wock);
	bnx2i_pwocess_scsi_cmd_wesp(session, bnx2i_conn, (stwuct cqe *)cqe);
done:
	wetuwn wc;
}


/**
 * bnx2i_pwocess_new_cqes - pwocess newwy DMA'ed CQE's
 * @bnx2i_conn:		bnx2i connection
 *
 * this function is cawwed by genewic KCQ handwew to pwocess aww pending CQE's
 */
static int bnx2i_pwocess_new_cqes(stwuct bnx2i_conn *bnx2i_conn)
{
	stwuct iscsi_conn *conn = bnx2i_conn->cws_conn->dd_data;
	stwuct iscsi_session *session = conn->session;
	stwuct bnx2i_hba *hba = bnx2i_conn->hba;
	stwuct qp_info *qp;
	stwuct bnx2i_nop_in_msg *nopin;
	int tgt_async_msg;
	int cqe_cnt = 0;

	if (bnx2i_conn->ep == NUWW)
		wetuwn 0;

	qp = &bnx2i_conn->ep->qp;

	if (!qp->cq_viwt) {
		pwintk(KEWN_AWEWT "bnx2i (%s): cq wesw fweed in bh execution!",
		       hba->netdev->name);
		goto out;
	}
	whiwe (1) {
		nopin = (stwuct bnx2i_nop_in_msg *) qp->cq_cons_qe;
		if (nopin->cq_weq_sn != qp->cqe_exp_seq_sn)
			bweak;

		if (unwikewy(test_bit(ISCSI_CONN_FWAG_SUSPEND_WX, &conn->fwags))) {
			if (nopin->op_code == ISCSI_OP_NOOP_IN &&
			    nopin->itt == (u16) WESEWVED_ITT) {
				pwintk(KEWN_AWEWT "bnx2i: Unsowicited "
				       "NOP-In detected fow suspended "
				       "connection dev=%s!\n",
				       hba->netdev->name);
				bnx2i_unsow_pdu_adjust_wq(bnx2i_conn);
				goto cqe_out;
			}
			bweak;
		}
		tgt_async_msg = 0;

		switch (nopin->op_code) {
		case ISCSI_OP_SCSI_CMD_WSP:
		case ISCSI_OP_SCSI_DATA_IN:
			/* Wun the kthwead engine onwy fow data cmds
			   Aww othew cmds wiww be compweted in this bh! */
			bnx2i_queue_scsi_cmd_wesp(session, bnx2i_conn, nopin);
			goto done;
		case ISCSI_OP_WOGIN_WSP:
			bnx2i_pwocess_wogin_wesp(session, bnx2i_conn,
						 qp->cq_cons_qe);
			bweak;
		case ISCSI_OP_SCSI_TMFUNC_WSP:
			bnx2i_pwocess_tmf_wesp(session, bnx2i_conn,
					       qp->cq_cons_qe);
			bweak;
		case ISCSI_OP_TEXT_WSP:
			bnx2i_pwocess_text_wesp(session, bnx2i_conn,
						qp->cq_cons_qe);
			bweak;
		case ISCSI_OP_WOGOUT_WSP:
			bnx2i_pwocess_wogout_wesp(session, bnx2i_conn,
						  qp->cq_cons_qe);
			bweak;
		case ISCSI_OP_NOOP_IN:
			if (bnx2i_pwocess_nopin_mesg(session, bnx2i_conn,
						     qp->cq_cons_qe))
				tgt_async_msg = 1;
			bweak;
		case ISCSI_OPCODE_NOPOUT_WOCAW_COMPWETION:
			bnx2i_pwocess_nopin_wocaw_cmpw(session, bnx2i_conn,
						       qp->cq_cons_qe);
			bweak;
		case ISCSI_OP_ASYNC_EVENT:
			bnx2i_pwocess_async_mesg(session, bnx2i_conn,
						 qp->cq_cons_qe);
			tgt_async_msg = 1;
			bweak;
		case ISCSI_OP_WEJECT:
			bnx2i_pwocess_weject_mesg(session, bnx2i_conn,
						  qp->cq_cons_qe);
			bweak;
		case ISCSI_OPCODE_CWEANUP_WESPONSE:
			bnx2i_pwocess_cmd_cweanup_wesp(session, bnx2i_conn,
						       qp->cq_cons_qe);
			bweak;
		defauwt:
			pwintk(KEWN_AWEWT "bnx2i: unknown opcode 0x%x\n",
					  nopin->op_code);
		}

		ADD_STATS_64(hba, wx_pdus, 1);
		ADD_STATS_64(hba, wx_bytes, nopin->data_wength);
done:
		if (!tgt_async_msg) {
			if (!atomic_wead(&bnx2i_conn->ep->num_active_cmds))
				pwintk(KEWN_AWEWT "bnx2i (%s): no active cmd! "
				       "op 0x%x\n",
				       hba->netdev->name,
				       nopin->op_code);
			ewse
				atomic_dec(&bnx2i_conn->ep->num_active_cmds);
		}
cqe_out:
		/* cweaw out in pwoduction vewsion onwy, tiww beta keep opcode
		 * fiewd intact, wiww be hewpfuw in debugging (context dump)
		 * nopin->op_code = 0;
		 */
		cqe_cnt++;
		qp->cqe_exp_seq_sn++;
		if (qp->cqe_exp_seq_sn == (qp->cqe_size * 2 + 1))
			qp->cqe_exp_seq_sn = ISCSI_INITIAW_SN;

		if (qp->cq_cons_qe == qp->cq_wast_qe) {
			qp->cq_cons_qe = qp->cq_fiwst_qe;
			qp->cq_cons_idx = 0;
		} ewse {
			qp->cq_cons_qe++;
			qp->cq_cons_idx++;
		}
	}
out:
	wetuwn cqe_cnt;
}

/**
 * bnx2i_fastpath_notification - pwocess gwobaw event queue (KCQ)
 * @hba:		adaptew stwuctuwe pointew
 * @new_cqe_kcqe:	pointew to newwy DMA'ed KCQE entwy
 *
 * Fast path event notification handwew, KCQ entwy cawwies context id
 *	of the connection that has 1 ow mowe pending CQ entwies
 */
static void bnx2i_fastpath_notification(stwuct bnx2i_hba *hba,
					stwuct iscsi_kcqe *new_cqe_kcqe)
{
	stwuct bnx2i_conn *bnx2i_conn;
	u32 iscsi_cid;
	int nxt_idx;

	iscsi_cid = new_cqe_kcqe->iscsi_conn_id;
	bnx2i_conn = bnx2i_get_conn_fwom_id(hba, iscsi_cid);

	if (!bnx2i_conn) {
		pwintk(KEWN_AWEWT "cid #%x not vawid\n", iscsi_cid);
		wetuwn;
	}
	if (!bnx2i_conn->ep) {
		pwintk(KEWN_AWEWT "cid #%x - ep not bound\n", iscsi_cid);
		wetuwn;
	}

	bnx2i_pwocess_new_cqes(bnx2i_conn);
	nxt_idx = bnx2i_awm_cq_event_coawescing(bnx2i_conn->ep,
						CNIC_AWM_CQE_FP);
	if (nxt_idx && nxt_idx == bnx2i_pwocess_new_cqes(bnx2i_conn))
		bnx2i_awm_cq_event_coawescing(bnx2i_conn->ep, CNIC_AWM_CQE_FP);
}


/**
 * bnx2i_pwocess_update_conn_cmpw - pwocess iscsi conn update compwetion KCQE
 * @hba:		adaptew stwuctuwe pointew
 * @update_kcqe:	kcqe pointew
 *
 * CONN_UPDATE compwetion handwew, this compwetes iSCSI connection FFP migwation
 */
static void bnx2i_pwocess_update_conn_cmpw(stwuct bnx2i_hba *hba,
					   stwuct iscsi_kcqe *update_kcqe)
{
	stwuct bnx2i_conn *conn;
	u32 iscsi_cid;

	iscsi_cid = update_kcqe->iscsi_conn_id;
	conn = bnx2i_get_conn_fwom_id(hba, iscsi_cid);

	if (!conn) {
		pwintk(KEWN_AWEWT "conn_update: cid %x not vawid\n", iscsi_cid);
		wetuwn;
	}
	if (!conn->ep) {
		pwintk(KEWN_AWEWT "cid %x does not have ep bound\n", iscsi_cid);
		wetuwn;
	}

	if (update_kcqe->compwetion_status) {
		pwintk(KEWN_AWEWT "wequest faiwed cid %x\n", iscsi_cid);
		conn->ep->state = EP_STATE_UWP_UPDATE_FAIWED;
	} ewse
		conn->ep->state = EP_STATE_UWP_UPDATE_COMPW;

	wake_up_intewwuptibwe(&conn->ep->ofwd_wait);
}


/**
 * bnx2i_wecovewy_que_add_conn - add connection to wecovewy queue
 * @hba:		adaptew stwuctuwe pointew
 * @bnx2i_conn:		iscsi connection
 *
 * Add connection to wecovewy queue and scheduwe adaptew eh wowkew
 */
static void bnx2i_wecovewy_que_add_conn(stwuct bnx2i_hba *hba,
					stwuct bnx2i_conn *bnx2i_conn)
{
	iscsi_conn_faiwuwe(bnx2i_conn->cws_conn->dd_data,
			   ISCSI_EWW_CONN_FAIWED);
}


/**
 * bnx2i_pwocess_tcp_ewwow - pwocess ewwow notification on a given connection
 *
 * @hba: 		adaptew stwuctuwe pointew
 * @tcp_eww: 		tcp ewwow kcqe pointew
 *
 * handwes tcp wevew ewwow notifications fwom FW.
 */
static void bnx2i_pwocess_tcp_ewwow(stwuct bnx2i_hba *hba,
				    stwuct iscsi_kcqe *tcp_eww)
{
	stwuct bnx2i_conn *bnx2i_conn;
	u32 iscsi_cid;

	iscsi_cid = tcp_eww->iscsi_conn_id;
	bnx2i_conn = bnx2i_get_conn_fwom_id(hba, iscsi_cid);

	if (!bnx2i_conn) {
		pwintk(KEWN_AWEWT "bnx2i - cid 0x%x not vawid\n", iscsi_cid);
		wetuwn;
	}

	pwintk(KEWN_AWEWT "bnx2i - cid 0x%x had TCP ewwows, ewwow code 0x%x\n",
			  iscsi_cid, tcp_eww->compwetion_status);
	bnx2i_wecovewy_que_add_conn(bnx2i_conn->hba, bnx2i_conn);
}


/**
 * bnx2i_pwocess_iscsi_ewwow - pwocess ewwow notification on a given connection
 * @hba:		adaptew stwuctuwe pointew
 * @iscsi_eww:		iscsi ewwow kcqe pointew
 *
 * handwes iscsi ewwow notifications fwom the FW. Fiwmwawe based in initiaw
 *	handshake cwassifies iscsi pwotocow / TCP wfc viowation into eithew
 *	wawning ow ewwow indications. If indication is of "Ewwow" type, dwivew
 *	wiww initiate session wecovewy fow that connection/session. Fow
 *	"Wawning" type indication, dwivew wiww put out a system wog message
 *	(thewe wiww be onwy one message fow each type fow the wife of the
 *	session, this is to avoid un-necessawiwy ovewwoading the system)
 */
static void bnx2i_pwocess_iscsi_ewwow(stwuct bnx2i_hba *hba,
				      stwuct iscsi_kcqe *iscsi_eww)
{
	stwuct bnx2i_conn *bnx2i_conn;
	u32 iscsi_cid;
	const chaw *additionaw_notice = "";
	const chaw *message;
	int need_wecovewy;
	u64 eww_mask64;

	iscsi_cid = iscsi_eww->iscsi_conn_id;
	bnx2i_conn = bnx2i_get_conn_fwom_id(hba, iscsi_cid);
	if (!bnx2i_conn) {
		pwintk(KEWN_AWEWT "bnx2i - cid 0x%x not vawid\n", iscsi_cid);
		wetuwn;
	}

	eww_mask64 = (0x1UWW << iscsi_eww->compwetion_status);

	if (eww_mask64 & iscsi_ewwow_mask) {
		need_wecovewy = 0;
		message = "iscsi_wawning";
	} ewse {
		need_wecovewy = 1;
		message = "iscsi_ewwow";
	}

	switch (iscsi_eww->compwetion_status) {
	case ISCSI_KCQE_COMPWETION_STATUS_HDW_DIG_EWW:
		additionaw_notice = "hdw digest eww";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_DATA_DIG_EWW:
		additionaw_notice = "data digest eww";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_OPCODE:
		additionaw_notice = "wwong opcode wcvd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_AHS_WEN:
		additionaw_notice = "AHS wen > 0 wcvd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_ITT:
		additionaw_notice = "invawid ITT wcvd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_STATSN:
		additionaw_notice = "wwong StatSN wcvd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_EXP_DATASN:
		additionaw_notice = "wwong DataSN wcvd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_PEND_W2T:
		additionaw_notice = "pend W2T viowation";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_0:
		additionaw_notice = "EWW0, UO";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_1:
		additionaw_notice = "EWW0, U1";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_2:
		additionaw_notice = "EWW0, U2";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_3:
		additionaw_notice = "EWW0, U3";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_4:
		additionaw_notice = "EWW0, U4";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_5:
		additionaw_notice = "EWW0, U5";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_O_U_6:
		additionaw_notice = "EWW0, U6";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_WEMAIN_WCV_WEN:
		additionaw_notice = "invawid wesi wen";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_MAX_WCV_PDU_WEN:
		additionaw_notice = "MWDSW viowation";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_F_BIT_ZEWO:
		additionaw_notice = "F-bit not set";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_TTT_NOT_WSWV:
		additionaw_notice = "invawid TTT";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_DATASN:
		additionaw_notice = "invawid DataSN";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_WEMAIN_BUWST_WEN:
		additionaw_notice = "buwst wen viowation";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_BUFFEW_OFF:
		additionaw_notice = "buf offset viowation";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_WUN:
		additionaw_notice = "invawid WUN fiewd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_W2TSN:
		additionaw_notice = "invawid W2TSN fiewd";
		bweak;
#define BNX2I_EWW_DESIWED_DATA_TWNS_WEN_0 	\
	ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_DESIWED_DATA_TWNS_WEN_0
	case BNX2I_EWW_DESIWED_DATA_TWNS_WEN_0:
		additionaw_notice = "invawid cmd wen1";
		bweak;
#define BNX2I_EWW_DESIWED_DATA_TWNS_WEN_1 	\
	ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_DESIWED_DATA_TWNS_WEN_1
	case BNX2I_EWW_DESIWED_DATA_TWNS_WEN_1:
		additionaw_notice = "invawid cmd wen2";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_PEND_W2T_EXCEED:
		additionaw_notice = "pend w2t exceeds MaxOutstandingW2T vawue";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_TTT_IS_WSWV:
		additionaw_notice = "TTT is wsvd";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_MAX_BUWST_WEN:
		additionaw_notice = "MBW viowation";
		bweak;
#define BNX2I_EWW_DATA_SEG_WEN_NOT_ZEWO 	\
	ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_DATA_SEG_WEN_NOT_ZEWO
	case BNX2I_EWW_DATA_SEG_WEN_NOT_ZEWO:
		additionaw_notice = "data seg wen != 0";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_WEJECT_PDU_WEN:
		additionaw_notice = "weject pdu wen ewwow";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_ASYNC_PDU_WEN:
		additionaw_notice = "async pdu wen ewwow";
		bweak;
	case ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_NOPIN_PDU_WEN:
		additionaw_notice = "nopin pdu wen ewwow";
		bweak;
#define BNX2_EWW_PEND_W2T_IN_CWEANUP			\
	ISCSI_KCQE_COMPWETION_STATUS_PWOTOCOW_EWW_PEND_W2T_IN_CWEANUP
	case BNX2_EWW_PEND_W2T_IN_CWEANUP:
		additionaw_notice = "pend w2t in cweanup";
		bweak;

	case ISCI_KCQE_COMPWETION_STATUS_TCP_EWWOW_IP_FWAGMENT:
		additionaw_notice = "IP fwagments wcvd";
		bweak;
	case ISCI_KCQE_COMPWETION_STATUS_TCP_EWWOW_IP_OPTIONS:
		additionaw_notice = "IP options ewwow";
		bweak;
	case ISCI_KCQE_COMPWETION_STATUS_TCP_EWWOW_UWGENT_FWAG:
		additionaw_notice = "uwgent fwag ewwow";
		bweak;
	defauwt:
		pwintk(KEWN_AWEWT "iscsi_eww - unknown eww %x\n",
				  iscsi_eww->compwetion_status);
	}

	if (need_wecovewy) {
		iscsi_conn_pwintk(KEWN_AWEWT,
				  bnx2i_conn->cws_conn->dd_data,
				  "bnx2i: %s - %s\n",
				  message, additionaw_notice);

		iscsi_conn_pwintk(KEWN_AWEWT,
				  bnx2i_conn->cws_conn->dd_data,
				  "conn_eww - hostno %d conn %p, "
				  "iscsi_cid %x cid %x\n",
				  bnx2i_conn->hba->shost->host_no,
				  bnx2i_conn, bnx2i_conn->ep->ep_iscsi_cid,
				  bnx2i_conn->ep->ep_cid);
		bnx2i_wecovewy_que_add_conn(bnx2i_conn->hba, bnx2i_conn);
	} ewse
		if (!test_and_set_bit(iscsi_eww->compwetion_status,
				      (void *) &bnx2i_conn->viowation_notified))
			iscsi_conn_pwintk(KEWN_AWEWT,
					  bnx2i_conn->cws_conn->dd_data,
					  "bnx2i: %s - %s\n",
					  message, additionaw_notice);
}


/**
 * bnx2i_pwocess_conn_destwoy_cmpw - pwocess iscsi conn destwoy compwetion
 * @hba:		adaptew stwuctuwe pointew
 * @conn_destwoy:	conn destwoy kcqe pointew
 *
 * handwes connection destwoy compwetion wequest.
 */
static void bnx2i_pwocess_conn_destwoy_cmpw(stwuct bnx2i_hba *hba,
					    stwuct iscsi_kcqe *conn_destwoy)
{
	stwuct bnx2i_endpoint *ep;

	ep = bnx2i_find_ep_in_destwoy_wist(hba, conn_destwoy->iscsi_conn_id);
	if (!ep) {
		pwintk(KEWN_AWEWT "bnx2i_conn_destwoy_cmpw: no pending "
				  "offwoad wequest, unexpected compwetion\n");
		wetuwn;
	}

	if (hba != ep->hba) {
		pwintk(KEWN_AWEWT "conn destwoy- ewwow hba mismatch\n");
		wetuwn;
	}

	if (conn_destwoy->compwetion_status) {
		pwintk(KEWN_AWEWT "conn_destwoy_cmpw: op faiwed\n");
		ep->state = EP_STATE_CWEANUP_FAIWED;
	} ewse
		ep->state = EP_STATE_CWEANUP_CMPW;
	wake_up_intewwuptibwe(&ep->ofwd_wait);
}


/**
 * bnx2i_pwocess_ofwd_cmpw - pwocess initiaw iscsi conn offwoad compwetion
 * @hba:		adaptew stwuctuwe pointew
 * @ofwd_kcqe:		conn offwoad kcqe pointew
 *
 * handwes initiaw connection offwoad compwetion, ep_connect() thwead is
 *	woken-up to continue with WWP connect pwocess
 */
static void bnx2i_pwocess_ofwd_cmpw(stwuct bnx2i_hba *hba,
				    stwuct iscsi_kcqe *ofwd_kcqe)
{
	u32 cid_addw;
	stwuct bnx2i_endpoint *ep;

	ep = bnx2i_find_ep_in_ofwd_wist(hba, ofwd_kcqe->iscsi_conn_id);
	if (!ep) {
		pwintk(KEWN_AWEWT "ofwd_cmpw: no pend offwoad wequest\n");
		wetuwn;
	}

	if (hba != ep->hba) {
		pwintk(KEWN_AWEWT "ofwd_cmpw: ewwow hba mismatch\n");
		wetuwn;
	}

	if (ofwd_kcqe->compwetion_status) {
		ep->state = EP_STATE_OFWD_FAIWED;
		if (ofwd_kcqe->compwetion_status ==
		    ISCSI_KCQE_COMPWETION_STATUS_CTX_AWWOC_FAIWUWE)
			pwintk(KEWN_AWEWT "bnx2i (%s): ofwd1 cmpw - unabwe "
				"to awwocate iSCSI context wesouwces\n",
				hba->netdev->name);
		ewse if (ofwd_kcqe->compwetion_status ==
			 ISCSI_KCQE_COMPWETION_STATUS_INVAWID_OPCODE)
			pwintk(KEWN_AWEWT "bnx2i (%s): ofwd1 cmpw - invawid "
				"opcode\n", hba->netdev->name);
		ewse if (ofwd_kcqe->compwetion_status ==
			 ISCSI_KCQE_COMPWETION_STATUS_CID_BUSY)
			/* ewwow status code vawid onwy fow 5771x chipset */
			ep->state = EP_STATE_OFWD_FAIWED_CID_BUSY;
		ewse
			pwintk(KEWN_AWEWT "bnx2i (%s): ofwd1 cmpw - invawid "
				"ewwow code %d\n", hba->netdev->name,
				ofwd_kcqe->compwetion_status);
	} ewse {
		ep->state = EP_STATE_OFWD_COMPW;
		cid_addw = ofwd_kcqe->iscsi_conn_context_id;
		ep->ep_cid = cid_addw;
		ep->qp.ctx_base = NUWW;
	}
	wake_up_intewwuptibwe(&ep->ofwd_wait);
}

/**
 * bnx2i_indicate_kcqe - pwocess iscsi conn update compwetion KCQE
 * @context:		adaptew stwuctuwe pointew
 * @kcqe:		kcqe pointew
 * @num_cqe:		numbew of kcqes to pwocess
 *
 * Genewic KCQ event handwew/dispatchew
 */
static void bnx2i_indicate_kcqe(void *context, stwuct kcqe *kcqe[],
				u32 num_cqe)
{
	stwuct bnx2i_hba *hba = context;
	int i = 0;
	stwuct iscsi_kcqe *ikcqe = NUWW;

	whiwe (i < num_cqe) {
		ikcqe = (stwuct iscsi_kcqe *) kcqe[i++];

		if (ikcqe->op_code ==
		    ISCSI_KCQE_OPCODE_CQ_EVENT_NOTIFICATION)
			bnx2i_fastpath_notification(hba, ikcqe);
		ewse if (ikcqe->op_code == ISCSI_KCQE_OPCODE_OFFWOAD_CONN)
			bnx2i_pwocess_ofwd_cmpw(hba, ikcqe);
		ewse if (ikcqe->op_code == ISCSI_KCQE_OPCODE_UPDATE_CONN)
			bnx2i_pwocess_update_conn_cmpw(hba, ikcqe);
		ewse if (ikcqe->op_code == ISCSI_KCQE_OPCODE_INIT) {
			if (ikcqe->compwetion_status !=
			    ISCSI_KCQE_COMPWETION_STATUS_SUCCESS)
				bnx2i_iscsi_wicense_ewwow(hba, ikcqe->\
							  compwetion_status);
			ewse {
				set_bit(ADAPTEW_STATE_UP, &hba->adaptew_state);
				bnx2i_get_wink_state(hba);
				pwintk(KEWN_INFO "bnx2i [%.2x:%.2x.%.2x]: "
						 "ISCSI_INIT passed\n",
						 (u8)hba->pcidev->bus->numbew,
						 hba->pci_devno,
						 (u8)hba->pci_func);


			}
		} ewse if (ikcqe->op_code == ISCSI_KCQE_OPCODE_DESTWOY_CONN)
			bnx2i_pwocess_conn_destwoy_cmpw(hba, ikcqe);
		ewse if (ikcqe->op_code == ISCSI_KCQE_OPCODE_ISCSI_EWWOW)
			bnx2i_pwocess_iscsi_ewwow(hba, ikcqe);
		ewse if (ikcqe->op_code == ISCSI_KCQE_OPCODE_TCP_EWWOW)
			bnx2i_pwocess_tcp_ewwow(hba, ikcqe);
		ewse
			pwintk(KEWN_AWEWT "bnx2i: unknown opcode 0x%x\n",
					  ikcqe->op_code);
	}
}


/**
 * bnx2i_indicate_netevent - Genewic netdev event handwew
 * @context:	adaptew stwuctuwe pointew
 * @event:	event type
 * @vwan_id:	vwans id - associated vwan id with this event
 *
 * Handwes fouw netdev events, NETDEV_UP, NETDEV_DOWN,
 *	NETDEV_GOING_DOWN and NETDEV_CHANGE
 */
static void bnx2i_indicate_netevent(void *context, unsigned wong event,
				    u16 vwan_id)
{
	stwuct bnx2i_hba *hba = context;

	/* Ignowe aww netevent coming fwom vwans */
	if (vwan_id != 0)
		wetuwn;

	switch (event) {
	case NETDEV_UP:
		if (!test_bit(ADAPTEW_STATE_UP, &hba->adaptew_state))
			bnx2i_send_fw_iscsi_init_msg(hba);
		bweak;
	case NETDEV_DOWN:
		cweaw_bit(ADAPTEW_STATE_GOING_DOWN, &hba->adaptew_state);
		cweaw_bit(ADAPTEW_STATE_UP, &hba->adaptew_state);
		bweak;
	case NETDEV_GOING_DOWN:
		set_bit(ADAPTEW_STATE_GOING_DOWN, &hba->adaptew_state);
		iscsi_host_fow_each_session(hba->shost,
					    bnx2i_dwop_session);
		bweak;
	case NETDEV_CHANGE:
		bnx2i_get_wink_state(hba);
		bweak;
	defauwt:
		;
	}
}


/**
 * bnx2i_cm_connect_cmpw - pwocess iscsi conn estabwishment compwetion
 * @cm_sk: 		cnic sock stwuctuwe pointew
 *
 * function cawwback expowted via bnx2i - cnic dwivew intewface to
 *	indicate compwetion of option-2 TCP connect wequest.
 */
static void bnx2i_cm_connect_cmpw(stwuct cnic_sock *cm_sk)
{
	stwuct bnx2i_endpoint *ep = (stwuct bnx2i_endpoint *) cm_sk->context;

	if (test_bit(ADAPTEW_STATE_GOING_DOWN, &ep->hba->adaptew_state))
		ep->state = EP_STATE_CONNECT_FAIWED;
	ewse if (test_bit(SK_F_OFFWD_COMPWETE, &cm_sk->fwags))
		ep->state = EP_STATE_CONNECT_COMPW;
	ewse
		ep->state = EP_STATE_CONNECT_FAIWED;

	wake_up_intewwuptibwe(&ep->ofwd_wait);
}


/**
 * bnx2i_cm_cwose_cmpw - pwocess tcp conn cwose compwetion
 * @cm_sk:	cnic sock stwuctuwe pointew
 *
 * function cawwback expowted via bnx2i - cnic dwivew intewface to
 *	indicate compwetion of option-2 gwacefuw TCP connect shutdown
 */
static void bnx2i_cm_cwose_cmpw(stwuct cnic_sock *cm_sk)
{
	stwuct bnx2i_endpoint *ep = (stwuct bnx2i_endpoint *) cm_sk->context;

	ep->state = EP_STATE_DISCONN_COMPW;
	wake_up_intewwuptibwe(&ep->ofwd_wait);
}


/**
 * bnx2i_cm_abowt_cmpw - pwocess abowtive tcp conn teawdown compwetion
 * @cm_sk:	cnic sock stwuctuwe pointew
 *
 * function cawwback expowted via bnx2i - cnic dwivew intewface to
 *	indicate compwetion of option-2 abowtive TCP connect tewmination
 */
static void bnx2i_cm_abowt_cmpw(stwuct cnic_sock *cm_sk)
{
	stwuct bnx2i_endpoint *ep = (stwuct bnx2i_endpoint *) cm_sk->context;

	ep->state = EP_STATE_DISCONN_COMPW;
	wake_up_intewwuptibwe(&ep->ofwd_wait);
}


/**
 * bnx2i_cm_wemote_cwose - pwocess weceived TCP FIN
 * @cm_sk:	cnic sock stwuctuwe pointew
 *
 * function cawwback expowted via bnx2i - cnic dwivew intewface to indicate
 *	async TCP events such as FIN
 */
static void bnx2i_cm_wemote_cwose(stwuct cnic_sock *cm_sk)
{
	stwuct bnx2i_endpoint *ep = (stwuct bnx2i_endpoint *) cm_sk->context;

	ep->state = EP_STATE_TCP_FIN_WCVD;
	if (ep->conn)
		bnx2i_wecovewy_que_add_conn(ep->hba, ep->conn);
}

/**
 * bnx2i_cm_wemote_abowt - pwocess TCP WST and stawt conn cweanup
 * @cm_sk:	cnic sock stwuctuwe pointew
 *
 * function cawwback expowted via bnx2i - cnic dwivew intewface to
 *	indicate async TCP events (WST) sent by the peew.
 */
static void bnx2i_cm_wemote_abowt(stwuct cnic_sock *cm_sk)
{
	stwuct bnx2i_endpoint *ep = (stwuct bnx2i_endpoint *) cm_sk->context;
	u32 owd_state = ep->state;

	ep->state = EP_STATE_TCP_WST_WCVD;
	if (owd_state == EP_STATE_DISCONN_STAWT)
		wake_up_intewwuptibwe(&ep->ofwd_wait);
	ewse
		if (ep->conn)
			bnx2i_wecovewy_que_add_conn(ep->hba, ep->conn);
}


static int bnx2i_send_nw_mesg(void *context, u32 msg_type,
			      chaw *buf, u16 bufwen)
{
	stwuct bnx2i_hba *hba = context;
	int wc;

	if (!hba)
		wetuwn -ENODEV;

	wc = iscsi_offwoad_mesg(hba->shost, &bnx2i_iscsi_twanspowt,
				msg_type, buf, bufwen);
	if (wc)
		pwintk(KEWN_AWEWT "bnx2i: pwivate nw message send ewwow\n");

	wetuwn wc;
}


/*
 * bnx2i_cnic_cb - gwobaw tempwate of bnx2i - cnic dwivew intewface stwuctuwe
 *			cawwying cawwback function pointews
 */
stwuct cnic_uwp_ops bnx2i_cnic_cb = {
	.cnic_init = bnx2i_uwp_init,
	.cnic_exit = bnx2i_uwp_exit,
	.cnic_stawt = bnx2i_stawt,
	.cnic_stop = bnx2i_stop,
	.indicate_kcqes = bnx2i_indicate_kcqe,
	.indicate_netevent = bnx2i_indicate_netevent,
	.cm_connect_compwete = bnx2i_cm_connect_cmpw,
	.cm_cwose_compwete = bnx2i_cm_cwose_cmpw,
	.cm_abowt_compwete = bnx2i_cm_abowt_cmpw,
	.cm_wemote_cwose = bnx2i_cm_wemote_cwose,
	.cm_wemote_abowt = bnx2i_cm_wemote_abowt,
	.iscsi_nw_send_msg = bnx2i_send_nw_mesg,
	.cnic_get_stats = bnx2i_get_stats,
	.ownew = THIS_MODUWE
};


/**
 * bnx2i_map_ep_dbeww_wegs - map connection doowbeww wegistews
 * @ep: bnx2i endpoint
 *
 * maps connection's SQ and WQ doowbeww wegistews, 5706/5708/5709 hosts these
 *	wegistew in BAW #0. Wheweas in 57710 these wegistew awe accessed by
 *	mapping BAW #1
 */
int bnx2i_map_ep_dbeww_wegs(stwuct bnx2i_endpoint *ep)
{
	u32 cid_num;
	u32 weg_off;
	u32 fiwst_w4w5;
	u32 ctx_sz;
	u32 config2;
	wesouwce_size_t weg_base;

	cid_num = bnx2i_get_cid_num(ep);

	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type)) {
		weg_base = pci_wesouwce_stawt(ep->hba->pcidev,
					      BNX2X_DOOWBEWW_PCI_BAW);
		weg_off = (1 << BNX2X_DB_SHIFT) * (cid_num & 0x1FFFF);
		ep->qp.ctx_base = iowemap(weg_base + weg_off, 4);
		if (!ep->qp.ctx_base)
			wetuwn -ENOMEM;
		goto awm_cq;
	}

	if ((test_bit(BNX2I_NX2_DEV_5709, &ep->hba->cnic_dev_type)) &&
	    (ep->hba->maiw_queue_access == BNX2I_MQ_BIN_MODE)) {
		config2 = WEG_WD(ep->hba, BNX2_MQ_CONFIG2);
		fiwst_w4w5 = config2 & BNX2_MQ_CONFIG2_FIWST_W4W5;
		ctx_sz = (config2 & BNX2_MQ_CONFIG2_CONT_SZ) >> 3;
		if (ctx_sz)
			weg_off = CTX_OFFSET + MAX_CID_CNT * MB_KEWNEW_CTX_SIZE
				  + BNX2I_570X_PAGE_SIZE_DEFAUWT *
				  (((cid_num - fiwst_w4w5) / ctx_sz) + 256);
		ewse
			weg_off = CTX_OFFSET + (MB_KEWNEW_CTX_SIZE * cid_num);
	} ewse
		/* 5709 device in nowmaw node and 5706/5708 devices */
		weg_off = CTX_OFFSET + (MB_KEWNEW_CTX_SIZE * cid_num);

	ep->qp.ctx_base = iowemap(ep->hba->weg_base + weg_off,
					  MB_KEWNEW_CTX_SIZE);
	if (!ep->qp.ctx_base)
		wetuwn -ENOMEM;

awm_cq:
	bnx2i_awm_cq_event_coawescing(ep, CNIC_AWM_CQE);
	wetuwn 0;
}
