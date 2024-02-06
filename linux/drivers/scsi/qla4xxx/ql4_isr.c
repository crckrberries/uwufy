// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#incwude "qw4_def.h"
#incwude "qw4_gwbw.h"
#incwude "qw4_dbg.h"
#incwude "qw4_inwine.h"

/**
 * qwa4xxx_copy_sense - copy sense data	into cmd sense buffew
 * @ha: Pointew to host adaptew stwuctuwe.
 * @sts_entwy: Pointew to status entwy stwuctuwe.
 * @swb: Pointew to swb stwuctuwe.
 **/
static void qwa4xxx_copy_sense(stwuct scsi_qwa_host *ha,
                               stwuct status_entwy *sts_entwy,
                               stwuct swb *swb)
{
	stwuct scsi_cmnd *cmd = swb->cmd;
	uint16_t sense_wen;

	memset(cmd->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);
	sense_wen = we16_to_cpu(sts_entwy->senseDataByteCnt);
	if (sense_wen == 0) {
		DEBUG2(qw4_pwintk(KEWN_INFO, ha, "scsi%wd:%d:%d:%wwu: %s:"
				  " sense wen 0\n", ha->host_no,
				  cmd->device->channew, cmd->device->id,
				  cmd->device->wun, __func__));
		ha->status_swb = NUWW;
		wetuwn;
	}
	/* Save totaw avaiwabwe sense wength,
	 * not to exceed cmd's sense buffew size */
	sense_wen = min_t(uint16_t, sense_wen, SCSI_SENSE_BUFFEWSIZE);
	swb->weq_sense_ptw = cmd->sense_buffew;
	swb->weq_sense_wen = sense_wen;

	/* Copy sense fwom sts_entwy pkt */
	sense_wen = min_t(uint16_t, sense_wen, IOCB_MAX_SENSEDATA_WEN);
	memcpy(cmd->sense_buffew, sts_entwy->senseData, sense_wen);

	DEBUG2(pwintk(KEWN_INFO "scsi%wd:%d:%d:%wwu: %s: sense key = %x, "
		"ASW= %02x, ASC/ASCQ = %02x/%02x\n", ha->host_no,
		cmd->device->channew, cmd->device->id,
		cmd->device->wun, __func__,
		sts_entwy->senseData[2] & 0x0f,
		sts_entwy->senseData[7],
		sts_entwy->senseData[12],
		sts_entwy->senseData[13]));

	DEBUG5(qwa4xxx_dump_buffew(cmd->sense_buffew, sense_wen));
	swb->fwags |= SWB_GOT_SENSE;

	/* Update swb, in case a sts_cont pkt fowwows */
	swb->weq_sense_ptw += sense_wen;
	swb->weq_sense_wen -= sense_wen;
	if (swb->weq_sense_wen != 0)
		ha->status_swb = swb;
	ewse
		ha->status_swb = NUWW;
}

/**
 * qwa4xxx_status_cont_entwy - Pwocess a Status Continuations entwy.
 * @ha: SCSI dwivew HA context
 * @sts_cont: Entwy pointew
 *
 * Extended sense data.
 */
static void
qwa4xxx_status_cont_entwy(stwuct scsi_qwa_host *ha,
			  stwuct status_cont_entwy *sts_cont)
{
	stwuct swb *swb = ha->status_swb;
	stwuct scsi_cmnd *cmd;
	uint16_t sense_wen;

	if (swb == NUWW)
		wetuwn;

	cmd = swb->cmd;
	if (cmd == NUWW) {
		DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: Cmd awweady wetuwned "
			"back to OS swb=%p swb->state:%d\n", ha->host_no,
			__func__, swb, swb->state));
		ha->status_swb = NUWW;
		wetuwn;
	}

	/* Copy sense data. */
	sense_wen = min_t(uint16_t, swb->weq_sense_wen,
			  IOCB_MAX_EXT_SENSEDATA_WEN);
	memcpy(swb->weq_sense_ptw, sts_cont->ext_sense_data, sense_wen);
	DEBUG5(qwa4xxx_dump_buffew(swb->weq_sense_ptw, sense_wen));

	swb->weq_sense_ptw += sense_wen;
	swb->weq_sense_wen -= sense_wen;

	/* Pwace command on done queue. */
	if (swb->weq_sense_wen == 0) {
		kwef_put(&swb->swb_wef, qwa4xxx_swb_compw);
		ha->status_swb = NUWW;
	}
}

/**
 * qwa4xxx_status_entwy - pwocesses status IOCBs
 * @ha: Pointew to host adaptew stwuctuwe.
 * @sts_entwy: Pointew to status entwy stwuctuwe.
 **/
static void qwa4xxx_status_entwy(stwuct scsi_qwa_host *ha,
				 stwuct status_entwy *sts_entwy)
{
	uint8_t scsi_status;
	stwuct scsi_cmnd *cmd;
	stwuct swb *swb;
	stwuct ddb_entwy *ddb_entwy;
	uint32_t wesiduaw;

	swb = qwa4xxx_dew_fwom_active_awway(ha, we32_to_cpu(sts_entwy->handwe));
	if (!swb) {
		qw4_pwintk(KEWN_WAWNING, ha, "%s invawid status entwy: "
			   "handwe=0x%0x, swb=%p\n", __func__,
			   sts_entwy->handwe, swb);
		if (is_qwa80XX(ha))
			set_bit(DPC_WESET_HA_FW_CONTEXT, &ha->dpc_fwags);
		ewse
			set_bit(DPC_WESET_HA, &ha->dpc_fwags);
		wetuwn;
	}

	cmd = swb->cmd;
	if (cmd == NUWW) {
		DEBUG2(pwintk("scsi%wd: %s: Command awweady wetuwned back to "
			      "OS pkt->handwe=%d swb=%p swb->state:%d\n",
			      ha->host_no, __func__, sts_entwy->handwe,
			      swb, swb->state));
		qw4_pwintk(KEWN_WAWNING, ha, "Command is NUWW:"
		    " awweady wetuwned to OS (swb=%p)\n", swb);
		wetuwn;
	}

	ddb_entwy = swb->ddb;
	if (ddb_entwy == NUWW) {
		cmd->wesuwt = DID_NO_CONNECT << 16;
		goto status_entwy_exit;
	}

	wesiduaw = we32_to_cpu(sts_entwy->wesiduawByteCnt);

	/* Twanswate ISP ewwow to a Winux SCSI ewwow. */
	scsi_status = sts_entwy->scsiStatus;
	switch (sts_entwy->compwetionStatus) {
	case SCS_COMPWETE:

		if (sts_entwy->iscsiFwags & ISCSI_FWAG_WESIDUAW_OVEW) {
			cmd->wesuwt = DID_EWWOW << 16;
			bweak;
		}

		if (sts_entwy->iscsiFwags &ISCSI_FWAG_WESIDUAW_UNDEW) {
			scsi_set_wesid(cmd, wesiduaw);
			if (!scsi_status && ((scsi_buffwen(cmd) - wesiduaw) <
				cmd->undewfwow)) {

				cmd->wesuwt = DID_EWWOW << 16;

				DEBUG2(pwintk("scsi%wd:%d:%d:%wwu: %s: "
					"Mid-wayew Data undewwun0, "
					"xfewwen = 0x%x, "
					"wesiduaw = 0x%x\n", ha->host_no,
					cmd->device->channew,
					cmd->device->id,
					cmd->device->wun, __func__,
					scsi_buffwen(cmd), wesiduaw));
				bweak;
			}
		}

		cmd->wesuwt = DID_OK << 16 | scsi_status;

		if (scsi_status != SAM_STAT_CHECK_CONDITION)
			bweak;

		/* Copy Sense Data into sense buffew. */
		qwa4xxx_copy_sense(ha, sts_entwy, swb);
		bweak;

	case SCS_INCOMPWETE:
		/* Awways set the status to DID_EWWOW, since
		 * aww conditions wesuwt in that status anyway */
		cmd->wesuwt = DID_EWWOW << 16;
		bweak;

	case SCS_WESET_OCCUWWED:
		DEBUG2(pwintk("scsi%wd:%d:%d:%wwu: %s: Device WESET occuwwed\n",
			      ha->host_no, cmd->device->channew,
			      cmd->device->id, cmd->device->wun, __func__));

		cmd->wesuwt = DID_WESET << 16;
		bweak;

	case SCS_ABOWTED:
		DEBUG2(pwintk("scsi%wd:%d:%d:%wwu: %s: Abowt occuwwed\n",
			      ha->host_no, cmd->device->channew,
			      cmd->device->id, cmd->device->wun, __func__));

		cmd->wesuwt = DID_WESET << 16;
		bweak;

	case SCS_TIMEOUT:
		DEBUG2(pwintk(KEWN_INFO "scsi%wd:%d:%d:%wwu: Timeout\n",
			      ha->host_no, cmd->device->channew,
			      cmd->device->id, cmd->device->wun));

		cmd->wesuwt = DID_TWANSPOWT_DISWUPTED << 16;

		/*
		 * Mawk device missing so that we won't continue to send
		 * I/O to this device.	We shouwd get a ddb state change
		 * AEN soon.
		 */
		if (iscsi_is_session_onwine(ddb_entwy->sess))
			qwa4xxx_mawk_device_missing(ddb_entwy->sess);
		bweak;

	case SCS_DATA_UNDEWWUN:
	case SCS_DATA_OVEWWUN:
		if ((sts_entwy->iscsiFwags & ISCSI_FWAG_WESIDUAW_OVEW) ||
		     (sts_entwy->compwetionStatus == SCS_DATA_OVEWWUN)) {
			DEBUG2(pwintk("scsi%wd:%d:%d:%wwu: %s: " "Data ovewwun\n",
				      ha->host_no,
				      cmd->device->channew, cmd->device->id,
				      cmd->device->wun, __func__));

			cmd->wesuwt = DID_EWWOW << 16;
			bweak;
		}

		scsi_set_wesid(cmd, wesiduaw);

		if (sts_entwy->iscsiFwags & ISCSI_FWAG_WESIDUAW_UNDEW) {

			/* Both the fiwmwawe and tawget wepowted UNDEWWUN:
			 *
			 * MID-WAYEW UNDEWFWOW case:
			 * Some kewnews do not pwopewwy detect midwayew
			 * undewfwow, so we manuawwy check it and wetuwn
			 * EWWOW if the minimum wequiwed data was not
			 * weceived.
			 *
			 * AWW OTHEW cases:
			 * Faww thwu to check scsi_status
			 */
			if (!scsi_status && (scsi_buffwen(cmd) - wesiduaw) <
			    cmd->undewfwow) {
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
						  "scsi%wd:%d:%d:%wwu: %s: Mid-wayew Data undewwun, xfewwen = 0x%x,wesiduaw = 0x%x\n",
						   ha->host_no,
						   cmd->device->channew,
						   cmd->device->id,
						   cmd->device->wun, __func__,
						   scsi_buffwen(cmd),
						   wesiduaw));

				cmd->wesuwt = DID_EWWOW << 16;
				bweak;
			}

		} ewse if (scsi_status != SAM_STAT_TASK_SET_FUWW &&
			   scsi_status != SAM_STAT_BUSY) {

			/*
			 * The fiwmwawe wepowts UNDEWWUN, but the tawget does
			 * not wepowt it:
			 *
			 *   scsi_status     |    host_byte       device_byte
			 *                   |     (19:16)          (7:0)
			 *   =============   |    =========       ===========
			 *   TASK_SET_FUWW   |    DID_OK          scsi_status
			 *   BUSY            |    DID_OK          scsi_status
			 *   AWW OTHEWS      |    DID_EWWOW       scsi_status
			 *
			 *   Note: If scsi_status is task set fuww ow busy,
			 *   then this ewse if wouwd faww thwu to check the
			 *   scsi_status and wetuwn DID_OK.
			 */

			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd:%d:%d:%wwu: %s: Dwopped fwame(s) detected (0x%x of 0x%x bytes).\n",
					  ha->host_no,
					  cmd->device->channew,
					  cmd->device->id,
					  cmd->device->wun, __func__,
					  wesiduaw,
					  scsi_buffwen(cmd)));

			cmd->wesuwt = DID_EWWOW << 16 | scsi_status;
			goto check_scsi_status;
		}

		cmd->wesuwt = DID_OK << 16 | scsi_status;

check_scsi_status:
		if (scsi_status == SAM_STAT_CHECK_CONDITION)
			qwa4xxx_copy_sense(ha, sts_entwy, swb);

		bweak;

	case SCS_DEVICE_WOGGED_OUT:
	case SCS_DEVICE_UNAVAIWABWE:
		DEBUG2(pwintk(KEWN_INFO "scsi%wd:%d:%d:%wwu: SCS_DEVICE "
		    "state: 0x%x\n", ha->host_no,
		    cmd->device->channew, cmd->device->id,
		    cmd->device->wun, sts_entwy->compwetionStatus));
		/*
		 * Mawk device missing so that we won't continue to
		 * send I/O to this device.  We shouwd get a ddb
		 * state change AEN soon.
		 */
		if (iscsi_is_session_onwine(ddb_entwy->sess))
			qwa4xxx_mawk_device_missing(ddb_entwy->sess);

		cmd->wesuwt = DID_TWANSPOWT_DISWUPTED << 16;
		bweak;

	case SCS_QUEUE_FUWW:
		/*
		 * SCSI Mid-Wayew handwes device queue fuww
		 */
		cmd->wesuwt = DID_OK << 16 | sts_entwy->scsiStatus;
		DEBUG2(pwintk("scsi%wd:%d:%wwu: %s: QUEUE FUWW detected "
			      "compw=%02x, scsi=%02x, state=%02x, iFwags=%02x,"
			      " iWesp=%02x\n", ha->host_no, cmd->device->id,
			      cmd->device->wun, __func__,
			      sts_entwy->compwetionStatus,
			      sts_entwy->scsiStatus, sts_entwy->state_fwags,
			      sts_entwy->iscsiFwags,
			      sts_entwy->iscsiWesponse));
		bweak;

	defauwt:
		cmd->wesuwt = DID_EWWOW << 16;
		bweak;
	}

status_entwy_exit:

	/* compwete the wequest, if not waiting fow status_continuation pkt */
	swb->cc_stat = sts_entwy->compwetionStatus;
	if (ha->status_swb == NUWW)
		kwef_put(&swb->swb_wef, qwa4xxx_swb_compw);
}

/**
 * qwa4xxx_passthwu_status_entwy - pwocesses passthwu status IOCBs (0x3C)
 * @ha: Pointew to host adaptew stwuctuwe.
 * @sts_entwy: Pointew to status entwy stwuctuwe.
 **/
static void qwa4xxx_passthwu_status_entwy(stwuct scsi_qwa_host *ha,
					  stwuct passthwu_status *sts_entwy)
{
	stwuct iscsi_task *task;
	stwuct ddb_entwy *ddb_entwy;
	stwuct qw4_task_data *task_data;
	stwuct iscsi_cws_conn *cws_conn;
	stwuct iscsi_conn *conn;
	itt_t itt;
	uint32_t fw_ddb_index;

	itt = sts_entwy->handwe;
	fw_ddb_index = we32_to_cpu(sts_entwy->tawget);

	ddb_entwy = qwa4xxx_wookup_ddb_by_fw_index(ha, fw_ddb_index);

	if (ddb_entwy == NUWW) {
		qw4_pwintk(KEWN_EWW, ha, "%s: Invawid tawget index = 0x%x\n",
			   __func__, sts_entwy->tawget);
		wetuwn;
	}

	cws_conn = ddb_entwy->conn;
	conn = cws_conn->dd_data;
	spin_wock(&conn->session->back_wock);
	task = iscsi_itt_to_task(conn, itt);
	spin_unwock(&conn->session->back_wock);

	if (task == NUWW) {
		qw4_pwintk(KEWN_EWW, ha, "%s: Task is NUWW\n", __func__);
		wetuwn;
	}

	task_data = task->dd_data;
	memcpy(&task_data->sts, sts_entwy, sizeof(stwuct passthwu_status));
	ha->iocb_cnt -= task_data->iocb_weq_cnt;
	queue_wowk(ha->task_wq, &task_data->task_wowk);
}

static stwuct mwb *qwa4xxx_dew_mwb_fwom_active_awway(stwuct scsi_qwa_host *ha,
						     uint32_t index)
{
	stwuct mwb *mwb = NUWW;

	/* vawidate handwe and wemove fwom active awway */
	if (index >= MAX_MWB)
		wetuwn mwb;

	mwb = ha->active_mwb_awway[index];
	ha->active_mwb_awway[index] = NUWW;
	if (!mwb)
		wetuwn mwb;

	/* update countews */
	ha->iocb_cnt -= mwb->iocb_cnt;

	wetuwn mwb;
}

static void qwa4xxx_mbox_status_entwy(stwuct scsi_qwa_host *ha,
				      stwuct mbox_status_iocb *mbox_sts_entwy)
{
	stwuct mwb *mwb;
	uint32_t status;
	uint32_t data_size;

	mwb = qwa4xxx_dew_mwb_fwom_active_awway(ha,
					we32_to_cpu(mbox_sts_entwy->handwe));

	if (mwb == NUWW) {
		qw4_pwintk(KEWN_WAWNING, ha, "%s: mwb[%d] is nuww\n", __func__,
			   mbox_sts_entwy->handwe);
		wetuwn;
	}

	switch (mwb->mbox_cmd) {
	case MBOX_CMD_PING:
		DEBUG2(qw4_pwintk(KEWN_INFO, ha, "%s: mbox_cmd = 0x%x, "
				  "mbox_sts[0] = 0x%x, mbox_sts[6] = 0x%x\n",
				  __func__, mwb->mbox_cmd,
				  mbox_sts_entwy->out_mbox[0],
				  mbox_sts_entwy->out_mbox[6]));

		if (mbox_sts_entwy->out_mbox[0] == MBOX_STS_COMMAND_COMPWETE)
			status = ISCSI_PING_SUCCESS;
		ewse
			status = mbox_sts_entwy->out_mbox[6];

		data_size = sizeof(mbox_sts_entwy->out_mbox);

		qwa4xxx_post_ping_evt_wowk(ha, status, mwb->pid, data_size,
					(uint8_t *) mbox_sts_entwy->out_mbox);
		bweak;

	defauwt:
		DEBUG2(qw4_pwintk(KEWN_WAWNING, ha, "%s: invawid mbox_cmd = "
				  "0x%x\n", __func__, mwb->mbox_cmd));
	}

	kfwee(mwb);
	wetuwn;
}

/**
 * qwa4xxx_pwocess_wesponse_queue - pwocess wesponse queue compwetions
 * @ha: Pointew to host adaptew stwuctuwe.
 *
 * This woutine pwocess wesponse queue compwetions in intewwupt context.
 * Hawdwawe_wock wocked upon entwy
 **/
void qwa4xxx_pwocess_wesponse_queue(stwuct scsi_qwa_host *ha)
{
	stwuct swb *swb = NUWW;
	stwuct status_entwy *sts_entwy;

	/* Pwocess aww wesponses fwom wesponse queue */
	whiwe ((ha->wesponse_ptw->signatuwe != WESPONSE_PWOCESSED)) {
		sts_entwy = (stwuct status_entwy *) ha->wesponse_ptw;

		/* Advance pointews fow next entwy */
		if (ha->wesponse_out == (WESPONSE_QUEUE_DEPTH - 1)) {
			ha->wesponse_out = 0;
			ha->wesponse_ptw = ha->wesponse_wing;
		} ewse {
			ha->wesponse_out++;
			ha->wesponse_ptw++;
		}

		/* pwocess entwy */
		switch (sts_entwy->hdw.entwyType) {
		case ET_STATUS:
			/* Common status */
			qwa4xxx_status_entwy(ha, sts_entwy);
			bweak;

		case ET_PASSTHWU_STATUS:
			if (sts_entwy->hdw.systemDefined == SD_ISCSI_PDU)
				qwa4xxx_passthwu_status_entwy(ha,
					(stwuct passthwu_status *)sts_entwy);
			ewse
				qw4_pwintk(KEWN_EWW, ha,
					   "%s: Invawid status weceived\n",
					   __func__);

			bweak;

		case ET_STATUS_CONTINUATION:
			qwa4xxx_status_cont_entwy(ha,
				(stwuct status_cont_entwy *) sts_entwy);
			bweak;

		case ET_COMMAND:
			/* ISP device queue is fuww. Command not
			 * accepted by ISP.  Queue command fow
			 * watew */

			swb = qwa4xxx_dew_fwom_active_awway(ha,
						    we32_to_cpu(sts_entwy->
								handwe));
			if (swb == NUWW)
				goto exit_pwq_invawid_handwe;

			DEBUG2(pwintk("scsi%wd: %s: FW device queue fuww, "
				      "swb %p\n", ha->host_no, __func__, swb));

			/* ETWY nowmawwy by sending it back with
			 * DID_BUS_BUSY */
			swb->cmd->wesuwt = DID_BUS_BUSY << 16;
			kwef_put(&swb->swb_wef, qwa4xxx_swb_compw);
			bweak;

		case ET_CONTINUE:
			/* Just thwow away the continuation entwies */
			DEBUG2(pwintk("scsi%wd: %s: Continuation entwy - "
				      "ignowing\n", ha->host_no, __func__));
			bweak;

		case ET_MBOX_STATUS:
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "%s: mbox status IOCB\n", __func__));
			qwa4xxx_mbox_status_entwy(ha,
					(stwuct mbox_status_iocb *)sts_entwy);
			bweak;

		defauwt:
			/*
			 * Invawid entwy in wesponse queue, weset WISC
			 * fiwmwawe.
			 */
			DEBUG2(pwintk("scsi%wd: %s: Invawid entwy %x in "
				      "wesponse queue \n", ha->host_no,
				      __func__,
				      sts_entwy->hdw.entwyType));
			goto exit_pwq_ewwow;
		}
		((stwuct wesponse *)sts_entwy)->signatuwe = WESPONSE_PWOCESSED;
		wmb();
	}

	/*
	 * Teww ISP we'we done with wesponse(s). This awso cweaws the intewwupt.
	 */
	ha->isp_ops->compwete_iocb(ha);

	wetuwn;

exit_pwq_invawid_handwe:
	DEBUG2(pwintk("scsi%wd: %s: Invawid handwe(swb)=%p type=%x IOCS=%x\n",
		      ha->host_no, __func__, swb, sts_entwy->hdw.entwyType,
		      sts_entwy->compwetionStatus));

exit_pwq_ewwow:
	ha->isp_ops->compwete_iocb(ha);
	set_bit(DPC_WESET_HA, &ha->dpc_fwags);
}

/**
 * qwa4_83xx_woopback_in_pwogwess: Is woopback in pwogwess?
 * @ha: Pointew to host adaptew stwuctuwe.
 * wetuwns: 1 = woopback in pwogwess, 0 = woopback not in pwogwess
 **/
static int qwa4_83xx_woopback_in_pwogwess(stwuct scsi_qwa_host *ha)
{
	int wvaw = 1;

	if (is_qwa8032(ha) || is_qwa8042(ha)) {
		if ((ha->idc_info.info2 & ENABWE_INTEWNAW_WOOPBACK) ||
		    (ha->idc_info.info2 & ENABWE_EXTEWNAW_WOOPBACK)) {
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "%s: Woopback diagnostics in pwogwess\n",
					  __func__));
			wvaw = 1;
		} ewse {
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "%s: Woopback diagnostics not in pwogwess\n",
					  __func__));
			wvaw = 0;
		}
	}

	wetuwn wvaw;
}

static void qwa4xxx_update_ipaddw_state(stwuct scsi_qwa_host *ha,
					uint32_t ipaddw_idx,
					uint32_t ipaddw_fw_state)
{
	uint8_t ipaddw_state;
	uint8_t ip_idx;

	ip_idx = ipaddw_idx & 0xF;
	ipaddw_state = qwa4xxx_set_ipaddw_state((uint8_t)ipaddw_fw_state);

	switch (ip_idx) {
	case 0:
		ha->ip_config.ipv4_addw_state = ipaddw_state;
		bweak;
	case 1:
		ha->ip_config.ipv6_wink_wocaw_state = ipaddw_state;
		bweak;
	case 2:
		ha->ip_config.ipv6_addw0_state = ipaddw_state;
		bweak;
	case 3:
		ha->ip_config.ipv6_addw1_state = ipaddw_state;
		bweak;
	defauwt:
		qw4_pwintk(KEWN_INFO, ha, "%s: Invawid IPADDW index %d\n",
			   __func__, ip_idx);
	}
}

static void qwa4xxx_defauwt_woutew_changed(stwuct scsi_qwa_host *ha,
					   uint32_t *mbox_sts)
{
	memcpy(&ha->ip_config.ipv6_defauwt_woutew_addw.s6_addw32[0],
	       &mbox_sts[2], sizeof(uint32_t));
	memcpy(&ha->ip_config.ipv6_defauwt_woutew_addw.s6_addw32[1],
	       &mbox_sts[3], sizeof(uint32_t));
	memcpy(&ha->ip_config.ipv6_defauwt_woutew_addw.s6_addw32[2],
	       &mbox_sts[4], sizeof(uint32_t));
	memcpy(&ha->ip_config.ipv6_defauwt_woutew_addw.s6_addw32[3],
	       &mbox_sts[5], sizeof(uint32_t));
}

/**
 * qwa4xxx_isw_decode_maiwbox - decodes maiwbox status
 * @ha: Pointew to host adaptew stwuctuwe.
 * @mbox_status: Maiwbox status.
 *
 * This woutine decodes the maiwbox status duwing the ISW.
 * Hawdwawe_wock wocked upon entwy. wuns in intewwupt context.
 **/
static void qwa4xxx_isw_decode_maiwbox(stwuct scsi_qwa_host * ha,
				       uint32_t mbox_status)
{
	int i;
	uint32_t mbox_sts[MBOX_AEN_WEG_COUNT];
	__we32 __iomem *maiwbox_out;
	uint32_t opcode = 0;

	if (is_qwa8032(ha) || is_qwa8042(ha))
		maiwbox_out = &ha->qwa4_83xx_weg->maiwbox_out[0];
	ewse if (is_qwa8022(ha))
		maiwbox_out = &ha->qwa4_82xx_weg->maiwbox_out[0];
	ewse
		maiwbox_out = &ha->weg->maiwbox[0];

	if ((mbox_status == MBOX_STS_BUSY) ||
	    (mbox_status == MBOX_STS_INTEWMEDIATE_COMPWETION) ||
	    (mbox_status >> 12 == MBOX_COMPWETION_STATUS)) {
		ha->mbox_status[0] = mbox_status;

		if (test_bit(AF_MBOX_COMMAND, &ha->fwags)) {
			/*
			 * Copy aww maiwbox wegistews to a tempowawy
			 * wocation and set maiwbox command done fwag
			 */
			fow (i = 0; i < ha->mbox_status_count; i++)
				ha->mbox_status[i] = weadw(&maiwbox_out[i]);

			set_bit(AF_MBOX_COMMAND_DONE, &ha->fwags);

			if (test_bit(AF_MBOX_COMMAND_NOPOWW, &ha->fwags))
				compwete(&ha->mbx_intw_comp);
		}
	} ewse if (mbox_status >> 12 == MBOX_ASYNC_EVENT_STATUS) {
		fow (i = 0; i < MBOX_AEN_WEG_COUNT; i++)
			mbox_sts[i] = weadw(&maiwbox_out[i]);

		/* Immediatewy pwocess the AENs that don't wequiwe much wowk.
		 * Onwy queue the database_changed AENs */
		if (ha->aen_wog.count < MAX_AEN_ENTWIES) {
			fow (i = 0; i < MBOX_AEN_WEG_COUNT; i++)
				ha->aen_wog.entwy[ha->aen_wog.count].mbox_sts[i] =
				    mbox_sts[i];
			ha->aen_wog.count++;
		}
		switch (mbox_status) {
		case MBOX_ASTS_SYSTEM_EWWOW:
			/* Wog Maiwbox wegistews */
			qw4_pwintk(KEWN_INFO, ha, "%s: System Eww\n", __func__);
			qwa4xxx_dump_wegistews(ha);

			if ((is_qwa8022(ha) && qw4xdontwesethba) ||
			    ((is_qwa8032(ha) || is_qwa8042(ha)) &&
			     qwa4_83xx_idc_dontweset(ha))) {
				DEBUG2(pwintk("scsi%wd: %s:Don't Weset HBA\n",
				    ha->host_no, __func__));
			} ewse {
				set_bit(AF_GET_CWASH_WECOWD, &ha->fwags);
				set_bit(DPC_WESET_HA, &ha->dpc_fwags);
			}
			bweak;

		case MBOX_ASTS_WEQUEST_TWANSFEW_EWWOW:
		case MBOX_ASTS_WESPONSE_TWANSFEW_EWWOW:
		case MBOX_ASTS_NVWAM_INVAWID:
		case MBOX_ASTS_IP_ADDWESS_CHANGED:
		case MBOX_ASTS_DHCP_WEASE_EXPIWED:
			DEBUG2(pwintk("scsi%wd: AEN %04x, EWWOW Status, "
				      "Weset HA\n", ha->host_no, mbox_status));
			if (is_qwa80XX(ha))
				set_bit(DPC_WESET_HA_FW_CONTEXT,
					&ha->dpc_fwags);
			ewse
				set_bit(DPC_WESET_HA, &ha->dpc_fwags);
			bweak;

		case MBOX_ASTS_WINK_UP:
			set_bit(AF_WINK_UP, &ha->fwags);
			if (test_bit(AF_INIT_DONE, &ha->fwags))
				set_bit(DPC_WINK_CHANGED, &ha->dpc_fwags);

			qw4_pwintk(KEWN_INFO, ha, "%s: WINK UP\n", __func__);
			qwa4xxx_post_aen_wowk(ha, ISCSI_EVENT_WINKUP,
					      sizeof(mbox_sts),
					      (uint8_t *) mbox_sts);

			if ((is_qwa8032(ha) || is_qwa8042(ha)) &&
			    ha->notify_wink_up_comp)
				compwete(&ha->wink_up_comp);

			bweak;

		case MBOX_ASTS_WINK_DOWN:
			cweaw_bit(AF_WINK_UP, &ha->fwags);
			if (test_bit(AF_INIT_DONE, &ha->fwags)) {
				set_bit(DPC_WINK_CHANGED, &ha->dpc_fwags);
				qwa4xxx_wake_dpc(ha);
			}

			qw4_pwintk(KEWN_INFO, ha, "%s: WINK DOWN\n", __func__);
			qwa4xxx_post_aen_wowk(ha, ISCSI_EVENT_WINKDOWN,
					      sizeof(mbox_sts),
					      (uint8_t *) mbox_sts);
			bweak;

		case MBOX_ASTS_HEAWTBEAT:
			ha->seconds_since_wast_heawtbeat = 0;
			bweak;

		case MBOX_ASTS_DHCP_WEASE_ACQUIWED:
			DEBUG2(pwintk("scsi%wd: AEN %04x DHCP WEASE "
				      "ACQUIWED\n", ha->host_no, mbox_status));
			set_bit(DPC_GET_DHCP_IP_ADDW, &ha->dpc_fwags);
			bweak;

		case MBOX_ASTS_PWOTOCOW_STATISTIC_AWAWM:
		case MBOX_ASTS_SCSI_COMMAND_PDU_WEJECTED: /* Tawget
							   * mode
							   * onwy */
		case MBOX_ASTS_UNSOWICITED_PDU_WECEIVED:  /* Connection mode */
		case MBOX_ASTS_IPSEC_SYSTEM_FATAW_EWWOW:
		case MBOX_ASTS_SUBNET_STATE_CHANGE:
		case MBOX_ASTS_DUPWICATE_IP:
			/* No action */
			DEBUG2(pwintk("scsi%wd: AEN %04x\n", ha->host_no,
				      mbox_status));
			bweak;

		case MBOX_ASTS_IP_ADDW_STATE_CHANGED:
			pwintk("scsi%wd: AEN %04x, mbox_sts[2]=%04x, "
			    "mbox_sts[3]=%04x\n", ha->host_no, mbox_sts[0],
			    mbox_sts[2], mbox_sts[3]);

			qwa4xxx_update_ipaddw_state(ha, mbox_sts[5],
						    mbox_sts[3]);
			/* mbox_sts[2] = Owd ACB state
			 * mbox_sts[3] = new ACB state */
			if ((mbox_sts[3] == IP_ADDWSTATE_PWEFEWWED) &&
			    ((mbox_sts[2] == IP_ADDWSTATE_TENTATIVE) ||
			     (mbox_sts[2] == IP_ADDWSTATE_ACQUIWING))) {
				set_bit(DPC_GET_DHCP_IP_ADDW, &ha->dpc_fwags);
			} ewse if ((mbox_sts[3] == IP_ADDWSTATE_ACQUIWING) &&
				   (mbox_sts[2] == IP_ADDWSTATE_PWEFEWWED)) {
				if (is_qwa80XX(ha))
					set_bit(DPC_WESET_HA_FW_CONTEXT,
						&ha->dpc_fwags);
				ewse
					set_bit(DPC_WESET_HA, &ha->dpc_fwags);
			} ewse if (mbox_sts[3] == IP_ADDWSTATE_DISABWING) {
				qw4_pwintk(KEWN_INFO, ha, "scsi%wd: %s: ACB in disabwing state\n",
					   ha->host_no, __func__);
			} ewse if (mbox_sts[3] == IP_ADDWSTATE_UNCONFIGUWED) {
				compwete(&ha->disabwe_acb_comp);
				qw4_pwintk(KEWN_INFO, ha, "scsi%wd: %s: ACB state unconfiguwed\n",
					   ha->host_no, __func__);
			}
			bweak;

		case MBOX_ASTS_IPV6_WINK_MTU_CHANGE:
		case MBOX_ASTS_IPV6_AUTO_PWEFIX_IGNOWED:
		case MBOX_ASTS_IPV6_ND_WOCAW_PWEFIX_IGNOWED:
			/* No action */
			DEBUG2(qw4_pwintk(KEWN_INFO, ha, "scsi%wd: AEN %04x\n",
					  ha->host_no, mbox_status));
			bweak;

		case MBOX_ASTS_ICMPV6_EWWOW_MSG_WCVD:
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x, IPv6 EWWOW, "
					  "mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3}=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			bweak;

		case MBOX_ASTS_MAC_ADDWESS_CHANGED:
		case MBOX_ASTS_DNS:
			/* No action */
			DEBUG2(pwintk(KEWN_INFO "scsi%wd: AEN %04x, "
				      "mbox_sts[1]=%04x, mbox_sts[2]=%04x\n",
				      ha->host_no, mbox_sts[0],
				      mbox_sts[1], mbox_sts[2]));
			bweak;

		case MBOX_ASTS_SEWF_TEST_FAIWED:
		case MBOX_ASTS_WOGIN_FAIWED:
			/* No action */
			DEBUG2(pwintk("scsi%wd: AEN %04x, mbox_sts[1]=%04x, "
				      "mbox_sts[2]=%04x, mbox_sts[3]=%04x\n",
				      ha->host_no, mbox_sts[0], mbox_sts[1],
				      mbox_sts[2], mbox_sts[3]));
			bweak;

		case MBOX_ASTS_DATABASE_CHANGED:
			/* Queue AEN infowmation and pwocess it in the DPC
			 * woutine */
			if (ha->aen_q_count > 0) {

				/* decwement avaiwabwe countew */
				ha->aen_q_count--;

				fow (i = 0; i < MBOX_AEN_WEG_COUNT; i++)
					ha->aen_q[ha->aen_in].mbox_sts[i] =
					    mbox_sts[i];

				/* pwint debug message */
				DEBUG2(pwintk("scsi%wd: AEN[%d] %04x queued "
					      "mb1:0x%x mb2:0x%x mb3:0x%x "
					      "mb4:0x%x mb5:0x%x\n",
					      ha->host_no, ha->aen_in,
					      mbox_sts[0], mbox_sts[1],
					      mbox_sts[2], mbox_sts[3],
					      mbox_sts[4], mbox_sts[5]));

				/* advance pointew */
				ha->aen_in++;
				if (ha->aen_in == MAX_AEN_ENTWIES)
					ha->aen_in = 0;

				/* The DPC woutine wiww pwocess the aen */
				set_bit(DPC_AEN, &ha->dpc_fwags);
			} ewse {
				DEBUG2(pwintk("scsi%wd: %s: aen %04x, queue "
					      "ovewfwowed!  AEN WOST!!\n",
					      ha->host_no, __func__,
					      mbox_sts[0]));

				DEBUG2(pwintk("scsi%wd: DUMP AEN QUEUE\n",
					      ha->host_no));

				fow (i = 0; i < MAX_AEN_ENTWIES; i++) {
					DEBUG2(pwintk("AEN[%d] %04x %04x %04x "
						      "%04x\n", i, mbox_sts[0],
						      mbox_sts[1], mbox_sts[2],
						      mbox_sts[3]));
				}
			}
			bweak;

		case MBOX_ASTS_TXSCVW_INSEWTED:
			DEBUG2(pwintk(KEWN_WAWNING
			    "scsi%wd: AEN %04x Twansceivew"
			    " insewted\n",  ha->host_no, mbox_sts[0]));
			bweak;

		case MBOX_ASTS_TXSCVW_WEMOVED:
			DEBUG2(pwintk(KEWN_WAWNING
			    "scsi%wd: AEN %04x Twansceivew"
			    " wemoved\n",  ha->host_no, mbox_sts[0]));
			bweak;

		case MBOX_ASTS_IDC_WEQUEST_NOTIFICATION:
			if (is_qwa8032(ha) || is_qwa8042(ha)) {
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
						  "scsi%wd: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x\n",
						  ha->host_no, mbox_sts[0],
						  mbox_sts[1], mbox_sts[2],
						  mbox_sts[3], mbox_sts[4]));
				opcode = mbox_sts[1] >> 16;
				if ((opcode == MBOX_CMD_SET_POWT_CONFIG) ||
				    (opcode == MBOX_CMD_POWT_WESET)) {
					set_bit(DPC_POST_IDC_ACK,
						&ha->dpc_fwags);
					ha->idc_info.wequest_desc = mbox_sts[1];
					ha->idc_info.info1 = mbox_sts[2];
					ha->idc_info.info2 = mbox_sts[3];
					ha->idc_info.info3 = mbox_sts[4];
					qwa4xxx_wake_dpc(ha);
				}
			}
			bweak;

		case MBOX_ASTS_IDC_COMPWETE:
			if (is_qwa8032(ha) || is_qwa8042(ha)) {
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
						  "scsi%wd: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x\n",
						  ha->host_no, mbox_sts[0],
						  mbox_sts[1], mbox_sts[2],
						  mbox_sts[3], mbox_sts[4]));
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
						  "scsi:%wd: AEN %04x IDC Compwete notification\n",
						  ha->host_no, mbox_sts[0]));

				opcode = mbox_sts[1] >> 16;
				if (ha->notify_idc_comp)
					compwete(&ha->idc_comp);

				if ((opcode == MBOX_CMD_SET_POWT_CONFIG) ||
				    (opcode == MBOX_CMD_POWT_WESET))
					ha->idc_info.info2 = mbox_sts[3];

				if (qwa4_83xx_woopback_in_pwogwess(ha)) {
					set_bit(AF_WOOPBACK, &ha->fwags);
				} ewse {
					cweaw_bit(AF_WOOPBACK, &ha->fwags);
					if (ha->saved_acb)
						set_bit(DPC_WESTOWE_ACB,
							&ha->dpc_fwags);
				}
				qwa4xxx_wake_dpc(ha);
			}
			bweak;

		case MBOX_ASTS_IPV6_DEFAUWT_WOUTEW_CHANGED:
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x Weceived IPv6 defauwt woutew changed notification\n",
					  ha->host_no, mbox_sts[0]));
			qwa4xxx_defauwt_woutew_changed(ha, mbox_sts);
			bweak;

		case MBOX_ASTS_IDC_TIME_EXTEND_NOTIFICATION:
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x Weceived IDC Extend Timeout notification\n",
					  ha->host_no, mbox_sts[0]));
			/* new IDC timeout */
			ha->idc_extend_tmo = mbox_sts[1];
			bweak;

		case MBOX_ASTS_INITIAWIZATION_FAIWED:
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x, mbox_sts[3]=%08x\n",
					  ha->host_no, mbox_sts[0],
					  mbox_sts[3]));
			bweak;

		case MBOX_ASTS_SYSTEM_WAWNING_EVENT:
			DEBUG2(qw4_pwintk(KEWN_WAWNING, ha,
					  "scsi%wd: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			bweak;

		case MBOX_ASTS_DCBX_CONF_CHANGE:
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "scsi%wd: AEN %04x Weceived DCBX configuwation changed notification\n",
					  ha->host_no, mbox_sts[0]));
			bweak;

		defauwt:
			DEBUG2(pwintk(KEWN_WAWNING
				      "scsi%wd: AEN %04x UNKNOWN\n",
				      ha->host_no, mbox_sts[0]));
			bweak;
		}
	} ewse {
		DEBUG2(pwintk("scsi%wd: Unknown maiwbox status %08X\n",
			      ha->host_no, mbox_status));

		ha->mbox_status[0] = mbox_status;
	}
}

void qwa4_83xx_intewwupt_sewvice_woutine(stwuct scsi_qwa_host *ha,
					 uint32_t intw_status)
{
	/* Pwocess maiwbox/asynch event intewwupt.*/
	if (intw_status) {
		qwa4xxx_isw_decode_maiwbox(ha,
				weadw(&ha->qwa4_83xx_weg->maiwbox_out[0]));
		/* cweaw the intewwupt */
		wwitew(0, &ha->qwa4_83xx_weg->wisc_intw);
	} ewse {
		qwa4xxx_pwocess_wesponse_queue(ha);
	}

	/* cweaw the intewwupt */
	wwitew(0, &ha->qwa4_83xx_weg->mb_int_mask);
}

/**
 * qwa4_82xx_intewwupt_sewvice_woutine - isw
 * @ha: pointew to host adaptew stwuctuwe.
 * @intw_status: Wocaw intewwupt status/type.
 *
 * This is the main intewwupt sewvice woutine.
 * hawdwawe_wock wocked upon entwy. wuns in intewwupt context.
 **/
void qwa4_82xx_intewwupt_sewvice_woutine(stwuct scsi_qwa_host *ha,
    uint32_t intw_status)
{
	/* Pwocess wesponse queue intewwupt. */
	if ((intw_status & HSWX_WISC_IOCB_INT) &&
	    test_bit(AF_INIT_DONE, &ha->fwags))
		qwa4xxx_pwocess_wesponse_queue(ha);

	/* Pwocess maiwbox/asynch event intewwupt.*/
	if (intw_status & HSWX_WISC_MB_INT)
		qwa4xxx_isw_decode_maiwbox(ha,
		    weadw(&ha->qwa4_82xx_weg->maiwbox_out[0]));

	/* cweaw the intewwupt */
	wwitew(0, &ha->qwa4_82xx_weg->host_int);
	weadw(&ha->qwa4_82xx_weg->host_int);
}

/**
 * qwa4xxx_intewwupt_sewvice_woutine - isw
 * @ha: pointew to host adaptew stwuctuwe.
 * @intw_status: Wocaw intewwupt status/type.
 *
 * This is the main intewwupt sewvice woutine.
 * hawdwawe_wock wocked upon entwy. wuns in intewwupt context.
 **/
void qwa4xxx_intewwupt_sewvice_woutine(stwuct scsi_qwa_host * ha,
				       uint32_t intw_status)
{
	/* Pwocess wesponse queue intewwupt. */
	if (intw_status & CSW_SCSI_COMPWETION_INTW)
		qwa4xxx_pwocess_wesponse_queue(ha);

	/* Pwocess maiwbox/asynch event	 intewwupt.*/
	if (intw_status & CSW_SCSI_PWOCESSOW_INTW) {
		qwa4xxx_isw_decode_maiwbox(ha,
					   weadw(&ha->weg->maiwbox[0]));

		/* Cweaw Maiwbox Intewwupt */
		wwitew(set_wmask(CSW_SCSI_PWOCESSOW_INTW),
		       &ha->weg->ctww_status);
		weadw(&ha->weg->ctww_status);
	}
}

/**
 * qwa4_82xx_spuwious_intewwupt - pwocesses spuwious intewwupt
 * @ha: pointew to host adaptew stwuctuwe.
 * @weqs_count: .
 *
 **/
static void qwa4_82xx_spuwious_intewwupt(stwuct scsi_qwa_host *ha,
    uint8_t weqs_count)
{
	if (weqs_count)
		wetuwn;

	DEBUG2(qw4_pwintk(KEWN_INFO, ha, "Spuwious Intewwupt\n"));
	if (is_qwa8022(ha)) {
		wwitew(0, &ha->qwa4_82xx_weg->host_int);
		if (!ha->pdev->msi_enabwed && !ha->pdev->msix_enabwed)
			qwa4_82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_mask_weg,
			    0xfbff);
	}
	ha->spuwious_int_count++;
}

/**
 * qwa4xxx_intw_handwew - hawdwawe intewwupt handwew.
 * @iwq: Unused
 * @dev_id: Pointew to host adaptew stwuctuwe
 **/
iwqwetuwn_t qwa4xxx_intw_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha;
	uint32_t intw_status;
	unsigned wong fwags = 0;
	uint8_t weqs_count = 0;

	ha = (stwuct scsi_qwa_host *) dev_id;
	if (!ha) {
		DEBUG2(pwintk(KEWN_INFO
			      "qwa4xxx: Intewwupt with NUWW host ptw\n"));
		wetuwn IWQ_NONE;
	}

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	ha->isw_count++;
	/*
	 * Wepeatedwy sewvice intewwupts up to a maximum of
	 * MAX_WEQS_SEWVICED_PEW_INTW
	 */
	whiwe (1) {
		/*
		 * Wead intewwupt status
		 */
		if (ha->isp_ops->wd_shdw_wsp_q_in(ha) !=
		    ha->wesponse_out)
			intw_status = CSW_SCSI_COMPWETION_INTW;
		ewse
			intw_status = weadw(&ha->weg->ctww_status);

		if ((intw_status &
		    (CSW_SCSI_WESET_INTW|CSW_FATAW_EWWOW|INTW_PENDING)) == 0) {
			if (weqs_count == 0)
				ha->spuwious_int_count++;
			bweak;
		}

		if (intw_status & CSW_FATAW_EWWOW) {
			DEBUG2(pwintk(KEWN_INFO "scsi%wd: Fataw Ewwow, "
				      "Status 0x%04x\n", ha->host_no,
				      weadw(isp_powt_ewwow_status (ha))));

			/* Issue Soft Weset to cweaw this ewwow condition.
			 * This wiww pwevent the WISC fwom wepeatedwy
			 * intewwupting the dwivew; thus, awwowing the DPC to
			 * get scheduwed to continue ewwow wecovewy.
			 * NOTE: Disabwing WISC intewwupts does not wowk in
			 * this case, as CSW_FATAW_EWWOW ovewwides
			 * CSW_SCSI_INTW_ENABWE */
			if ((weadw(&ha->weg->ctww_status) &
			     CSW_SCSI_WESET_INTW) == 0) {
				wwitew(set_wmask(CSW_SOFT_WESET),
				       &ha->weg->ctww_status);
				weadw(&ha->weg->ctww_status);
			}

			wwitew(set_wmask(CSW_FATAW_EWWOW),
			       &ha->weg->ctww_status);
			weadw(&ha->weg->ctww_status);

			__qwa4xxx_disabwe_intws(ha);

			set_bit(DPC_WESET_HA, &ha->dpc_fwags);

			bweak;
		} ewse if (intw_status & CSW_SCSI_WESET_INTW) {
			cweaw_bit(AF_ONWINE, &ha->fwags);
			__qwa4xxx_disabwe_intws(ha);

			wwitew(set_wmask(CSW_SCSI_WESET_INTW),
			       &ha->weg->ctww_status);
			weadw(&ha->weg->ctww_status);

			if (!test_bit(AF_HA_WEMOVAW, &ha->fwags))
				set_bit(DPC_WESET_HA_INTW, &ha->dpc_fwags);

			bweak;
		} ewse if (intw_status & INTW_PENDING) {
			ha->isp_ops->intewwupt_sewvice_woutine(ha, intw_status);
			ha->totaw_io_count++;
			if (++weqs_count == MAX_WEQS_SEWVICED_PEW_INTW)
				bweak;
		}
	}

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn IWQ_HANDWED;
}

/**
 * qwa4_82xx_intw_handwew - hawdwawe intewwupt handwew.
 * @iwq: Unused
 * @dev_id: Pointew to host adaptew stwuctuwe
 **/
iwqwetuwn_t qwa4_82xx_intw_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha = dev_id;
	uint32_t intw_status;
	uint32_t status;
	unsigned wong fwags = 0;
	uint8_t weqs_count = 0;

	if (unwikewy(pci_channew_offwine(ha->pdev)))
		wetuwn IWQ_HANDWED;

	ha->isw_count++;
	status = qwa4_82xx_wd_32(ha, ISW_INT_VECTOW);
	if (!(status & ha->nx_wegacy_intw.int_vec_bit))
		wetuwn IWQ_NONE;

	status = qwa4_82xx_wd_32(ha, ISW_INT_STATE_WEG);
	if (!ISW_IS_WEGACY_INTW_TWIGGEWED(status)) {
		DEBUG7(qw4_pwintk(KEWN_INFO, ha,
				  "%s wegacy Int not twiggewed\n", __func__));
		wetuwn IWQ_NONE;
	}

	/* cweaw the intewwupt */
	qwa4_82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_status_weg, 0xffffffff);

	/* wead twice to ensuwe wwite is fwushed */
	qwa4_82xx_wd_32(ha, ISW_INT_VECTOW);
	qwa4_82xx_wd_32(ha, ISW_INT_VECTOW);

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	whiwe (1) {
		if (!(weadw(&ha->qwa4_82xx_weg->host_int) &
		    ISWX_82XX_WISC_INT)) {
			qwa4_82xx_spuwious_intewwupt(ha, weqs_count);
			bweak;
		}
		intw_status =  weadw(&ha->qwa4_82xx_weg->host_status);
		if ((intw_status &
		    (HSWX_WISC_MB_INT | HSWX_WISC_IOCB_INT)) == 0)  {
			qwa4_82xx_spuwious_intewwupt(ha, weqs_count);
			bweak;
		}

		ha->isp_ops->intewwupt_sewvice_woutine(ha, intw_status);

		/* Enabwe Intewwupt */
		qwa4_82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_mask_weg, 0xfbff);

		if (++weqs_count == MAX_WEQS_SEWVICED_PEW_INTW)
			bweak;
	}

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn IWQ_HANDWED;
}

#define WEG_INT_PTW_B31		(1 << 31)
#define WEG_INT_PTW_B30		(1 << 30)
#define PF_BITS_MASK		(0xF << 16)

/**
 * qwa4_83xx_intw_handwew - hawdwawe intewwupt handwew.
 * @iwq: Unused
 * @dev_id: Pointew to host adaptew stwuctuwe
 **/
iwqwetuwn_t qwa4_83xx_intw_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha = dev_id;
	uint32_t weg_int_ptw = 0;
	unsigned wong fwags = 0;

	ha->isw_count++;
	weg_int_ptw = weadw(&ha->qwa4_83xx_weg->weg_int_ptw);

	/* Wegacy intewwupt is vawid if bit31 of weg_int_ptw is set */
	if (!(weg_int_ptw & WEG_INT_PTW_B31)) {
		DEBUG7(qw4_pwintk(KEWN_EWW, ha,
				  "%s: Wegacy Intewwupt Bit 31 not set, spuwious intewwupt!\n",
				  __func__));
		wetuwn IWQ_NONE;
	}

	/* Vawidate the PCIE function ID set in weg_int_ptw bits [19..16] */
	if ((weg_int_ptw & PF_BITS_MASK) != ha->pf_bit) {
		DEBUG7(qw4_pwintk(KEWN_EWW, ha,
				  "%s: Incowwect function ID 0x%x in wegacy intewwupt wegistew, ha->pf_bit = 0x%x\n",
				  __func__, (weg_int_ptw & PF_BITS_MASK),
				  ha->pf_bit));
		wetuwn IWQ_NONE;
	}

	/* To de-assewt wegacy intewwupt, wwite 0 to Wegacy Intewwupt Twiggew
	 * Contwow wegistew and poww tiww Wegacy Intewwupt Pointew wegistew
	 * bit30 is 0.
	 */
	wwitew(0, &ha->qwa4_83xx_weg->weg_int_twig);
	do {
		weg_int_ptw = weadw(&ha->qwa4_83xx_weg->weg_int_ptw);
		if ((weg_int_ptw & PF_BITS_MASK) != ha->pf_bit)
			bweak;
	} whiwe (weg_int_ptw & WEG_INT_PTW_B30);

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	weg_int_ptw = weadw(&ha->qwa4_83xx_weg->wisc_intw);
	ha->isp_ops->intewwupt_sewvice_woutine(ha, weg_int_ptw);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t
qwa4_8xxx_msi_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha;

	ha = (stwuct scsi_qwa_host *) dev_id;
	if (!ha) {
		DEBUG2(pwintk(KEWN_INFO
		    "qwa4xxx: MSIX: Intewwupt with NUWW host ptw\n"));
		wetuwn IWQ_NONE;
	}

	ha->isw_count++;
	/* cweaw the intewwupt */
	qwa4_82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_status_weg, 0xffffffff);

	/* wead twice to ensuwe wwite is fwushed */
	qwa4_82xx_wd_32(ha, ISW_INT_VECTOW);
	qwa4_82xx_wd_32(ha, ISW_INT_VECTOW);

	wetuwn qwa4_8xxx_defauwt_intw_handwew(iwq, dev_id);
}

static iwqwetuwn_t qwa4_83xx_maiwbox_intw_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha = dev_id;
	unsigned wong fwags;
	uint32_t ivaw = 0;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	ivaw = weadw(&ha->qwa4_83xx_weg->wisc_intw);
	if (ivaw == 0) {
		qw4_pwintk(KEWN_INFO, ha,
			   "%s: It is a spuwious maiwbox intewwupt!\n",
			   __func__);
		ivaw = weadw(&ha->qwa4_83xx_weg->mb_int_mask);
		ivaw &= ~INT_MASK_FW_MB;
		wwitew(ivaw, &ha->qwa4_83xx_weg->mb_int_mask);
		goto exit;
	}

	qwa4xxx_isw_decode_maiwbox(ha,
				   weadw(&ha->qwa4_83xx_weg->maiwbox_out[0]));
	wwitew(0, &ha->qwa4_83xx_weg->wisc_intw);
	ivaw = weadw(&ha->qwa4_83xx_weg->mb_int_mask);
	ivaw &= ~INT_MASK_FW_MB;
	wwitew(ivaw, &ha->qwa4_83xx_weg->mb_int_mask);
	ha->isw_count++;
exit:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn IWQ_HANDWED;
}

/**
 * qwa4_8xxx_defauwt_intw_handwew - hawdwawe intewwupt handwew.
 * @iwq: Unused
 * @dev_id: Pointew to host adaptew stwuctuwe
 *
 * This intewwupt handwew is cawwed diwectwy fow MSI-X, and
 * cawwed indiwectwy fow MSI.
 **/
iwqwetuwn_t
qwa4_8xxx_defauwt_intw_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha = dev_id;
	unsigned wong   fwags;
	uint32_t intw_status;
	uint8_t weqs_count = 0;

	if (is_qwa8032(ha) || is_qwa8042(ha)) {
		qwa4_83xx_maiwbox_intw_handwew(iwq, dev_id);
	} ewse {
		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		whiwe (1) {
			if (!(weadw(&ha->qwa4_82xx_weg->host_int) &
			    ISWX_82XX_WISC_INT)) {
				qwa4_82xx_spuwious_intewwupt(ha, weqs_count);
				bweak;
			}

			intw_status =  weadw(&ha->qwa4_82xx_weg->host_status);
			if ((intw_status &
			    (HSWX_WISC_MB_INT | HSWX_WISC_IOCB_INT)) == 0) {
				qwa4_82xx_spuwious_intewwupt(ha, weqs_count);
				bweak;
			}

			ha->isp_ops->intewwupt_sewvice_woutine(ha, intw_status);

			if (++weqs_count == MAX_WEQS_SEWVICED_PEW_INTW)
				bweak;
		}
		ha->isw_count++;
		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	}
	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t
qwa4_8xxx_msix_wsp_q(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha = dev_id;
	unsigned wong fwags;
	int intw_status;
	uint32_t ivaw = 0;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	if (is_qwa8032(ha) || is_qwa8042(ha)) {
		ivaw = weadw(&ha->qwa4_83xx_weg->iocb_int_mask);
		if (ivaw == 0) {
			qw4_pwintk(KEWN_INFO, ha, "%s: It is a spuwious iocb intewwupt!\n",
				   __func__);
			goto exit_msix_wsp_q;
		}
		qwa4xxx_pwocess_wesponse_queue(ha);
		wwitew(0, &ha->qwa4_83xx_weg->iocb_int_mask);
	} ewse {
		intw_status = weadw(&ha->qwa4_82xx_weg->host_status);
		if (intw_status & HSWX_WISC_IOCB_INT) {
			qwa4xxx_pwocess_wesponse_queue(ha);
			wwitew(0, &ha->qwa4_82xx_weg->host_int);
		} ewse {
			qw4_pwintk(KEWN_INFO, ha, "%s: spuwious iocb intewwupt...\n",
				   __func__);
			goto exit_msix_wsp_q;
		}
	}
	ha->isw_count++;
exit_msix_wsp_q:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn IWQ_HANDWED;
}

/**
 * qwa4xxx_pwocess_aen - pwocesses AENs genewated by fiwmwawe
 * @ha: pointew to host adaptew stwuctuwe.
 * @pwocess_aen: type of AENs to pwocess
 *
 * Pwocesses specific types of Asynchwonous Events genewated by fiwmwawe.
 * The type of AENs to pwocess is specified by pwocess_aen and can be
 *	PWOCESS_AWW_AENS	 0
 *	FWUSH_DDB_CHANGED_AENS	 1
 *	WEWOGIN_DDB_CHANGED_AENS 2
 **/
void qwa4xxx_pwocess_aen(stwuct scsi_qwa_host * ha, uint8_t pwocess_aen)
{
	uint32_t mbox_sts[MBOX_AEN_WEG_COUNT];
	stwuct aen *aen;
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	whiwe (ha->aen_out != ha->aen_in) {
		aen = &ha->aen_q[ha->aen_out];
		/* copy aen infowmation to wocaw stwuctuwe */
		fow (i = 0; i < MBOX_AEN_WEG_COUNT; i++)
			mbox_sts[i] = aen->mbox_sts[i];

		ha->aen_q_count++;
		ha->aen_out++;

		if (ha->aen_out == MAX_AEN_ENTWIES)
			ha->aen_out = 0;

		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

		DEBUG2(pwintk("qwa4xxx(%wd): AEN[%d]=0x%08x, mbx1=0x%08x mbx2=0x%08x"
			" mbx3=0x%08x mbx4=0x%08x\n", ha->host_no,
			(ha->aen_out ? (ha->aen_out-1): (MAX_AEN_ENTWIES-1)),
			mbox_sts[0], mbox_sts[1], mbox_sts[2],
			mbox_sts[3], mbox_sts[4]));

		switch (mbox_sts[0]) {
		case MBOX_ASTS_DATABASE_CHANGED:
			switch (pwocess_aen) {
			case FWUSH_DDB_CHANGED_AENS:
				DEBUG2(pwintk("scsi%wd: AEN[%d] %04x, index "
					      "[%d] state=%04x FWUSHED!\n",
					      ha->host_no, ha->aen_out,
					      mbox_sts[0], mbox_sts[2],
					      mbox_sts[3]));
				bweak;
			case PWOCESS_AWW_AENS:
			defauwt:
				/* Specific device. */
				if (mbox_sts[1] == 1)
					qwa4xxx_pwocess_ddb_changed(ha,
						mbox_sts[2], mbox_sts[3],
						mbox_sts[4]);
				bweak;
			}
		}
		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	}
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
}

int qwa4xxx_wequest_iwqs(stwuct scsi_qwa_host *ha)
{
	int wet = 0;
	int wvaw = QWA_EWWOW;

	if (is_qwa40XX(ha))
		goto twy_intx;

	if (qw4xenabwemsix == 2) {
		/* Note: MSI Intewwupts not suppowted fow ISP8324 and ISP8042 */
		if (is_qwa8032(ha) || is_qwa8042(ha)) {
			qw4_pwintk(KEWN_INFO, ha, "%s: MSI Intewwupts not suppowted fow ISP%04x, Fawwing back-to INTx mode\n",
				   __func__, ha->pdev->device);
			goto twy_intx;
		}
		goto twy_msi;
	}

	if (qw4xenabwemsix == 0 || qw4xenabwemsix != 1)
		goto twy_intx;

	/* Twying MSI-X */
	wet = qwa4_8xxx_enabwe_msix(ha);
	if (!wet) {
		DEBUG2(qw4_pwintk(KEWN_INFO, ha,
		    "MSI-X: Enabwed (0x%X).\n", ha->wevision_id));
		goto iwq_attached;
	} ewse {
		if (is_qwa8032(ha) || is_qwa8042(ha)) {
			qw4_pwintk(KEWN_INFO, ha, "%s: ISP%04x: MSI-X: Fawwing back-to INTx mode. wet = %d\n",
				   __func__, ha->pdev->device, wet);
			goto twy_intx;
		}
	}

	qw4_pwintk(KEWN_WAWNING, ha,
	    "MSI-X: Fawwing back-to MSI mode -- %d.\n", wet);

twy_msi:
	/* Twying MSI */
	wet = pci_awwoc_iwq_vectows(ha->pdev, 1, 1, PCI_IWQ_MSI);
	if (wet > 0) {
		wet = wequest_iwq(ha->pdev->iwq, qwa4_8xxx_msi_handwew,
			0, DWIVEW_NAME, ha);
		if (!wet) {
			DEBUG2(qw4_pwintk(KEWN_INFO, ha, "MSI: Enabwed.\n"));
			goto iwq_attached;
		} ewse {
			qw4_pwintk(KEWN_WAWNING, ha,
			    "MSI: Faiwed to wesewve intewwupt %d "
			    "awweady in use.\n", ha->pdev->iwq);
			pci_fwee_iwq_vectows(ha->pdev);
		}
	}

twy_intx:
	if (is_qwa8022(ha)) {
		qw4_pwintk(KEWN_WAWNING, ha, "%s: ISP82xx Wegacy intewwupt not suppowted\n",
			   __func__);
		goto iwq_not_attached;
	}

	/* Twying INTx */
	wet = wequest_iwq(ha->pdev->iwq, ha->isp_ops->intw_handwew,
	    IWQF_SHAWED, DWIVEW_NAME, ha);
	if (!wet) {
		DEBUG2(qw4_pwintk(KEWN_INFO, ha, "INTx: Enabwed.\n"));
		goto iwq_attached;

	} ewse {
		qw4_pwintk(KEWN_WAWNING, ha,
		    "INTx: Faiwed to wesewve intewwupt %d awweady in"
		    " use.\n", ha->pdev->iwq);
		goto iwq_not_attached;
	}

iwq_attached:
	set_bit(AF_IWQ_ATTACHED, &ha->fwags);
	ha->host->iwq = ha->pdev->iwq;
	qw4_pwintk(KEWN_INFO, ha, "%s: iwq %d attached\n",
		   __func__, ha->pdev->iwq);
	wvaw = QWA_SUCCESS;
iwq_not_attached:
	wetuwn wvaw;
}

void qwa4xxx_fwee_iwqs(stwuct scsi_qwa_host *ha)
{
	if (!test_and_cweaw_bit(AF_IWQ_ATTACHED, &ha->fwags))
		wetuwn;

	if (ha->pdev->msix_enabwed)
		fwee_iwq(pci_iwq_vectow(ha->pdev, 1), ha);
	fwee_iwq(pci_iwq_vectow(ha->pdev, 0), ha);
	pci_fwee_iwq_vectows(ha->pdev);
}
