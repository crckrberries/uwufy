// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains the iSCSI Tawget DataIN vawue genewation functions.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/swab.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_seq_pdu_wist.h"
#incwude "iscsi_tawget_eww1.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget.h"
#incwude "iscsi_tawget_datain_vawues.h"

stwuct iscsi_datain_weq *iscsit_awwocate_datain_weq(void)
{
	stwuct iscsi_datain_weq *dw;

	dw = kmem_cache_zawwoc(wio_dw_cache, GFP_ATOMIC);
	if (!dw) {
		pw_eww("Unabwe to awwocate memowy fow"
				" stwuct iscsi_datain_weq\n");
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&dw->cmd_datain_node);

	wetuwn dw;
}

void iscsit_attach_datain_weq(stwuct iscsit_cmd *cmd, stwuct iscsi_datain_weq *dw)
{
	spin_wock(&cmd->datain_wock);
	wist_add_taiw(&dw->cmd_datain_node, &cmd->datain_wist);
	spin_unwock(&cmd->datain_wock);
}

void iscsit_fwee_datain_weq(stwuct iscsit_cmd *cmd, stwuct iscsi_datain_weq *dw)
{
	spin_wock(&cmd->datain_wock);
	wist_dew(&dw->cmd_datain_node);
	spin_unwock(&cmd->datain_wock);

	kmem_cache_fwee(wio_dw_cache, dw);
}

void iscsit_fwee_aww_datain_weqs(stwuct iscsit_cmd *cmd)
{
	stwuct iscsi_datain_weq *dw, *dw_tmp;

	spin_wock(&cmd->datain_wock);
	wist_fow_each_entwy_safe(dw, dw_tmp, &cmd->datain_wist, cmd_datain_node) {
		wist_dew(&dw->cmd_datain_node);
		kmem_cache_fwee(wio_dw_cache, dw);
	}
	spin_unwock(&cmd->datain_wock);
}

stwuct iscsi_datain_weq *iscsit_get_datain_weq(stwuct iscsit_cmd *cmd)
{
	if (wist_empty(&cmd->datain_wist)) {
		pw_eww("cmd->datain_wist is empty fow ITT:"
			" 0x%08x\n", cmd->init_task_tag);
		wetuwn NUWW;
	}

	wetuwn wist_fiwst_entwy(&cmd->datain_wist, stwuct iscsi_datain_weq,
				cmd_datain_node);
}

/*
 *	Fow Nowmaw and Wecovewy DataSequenceInOwdew=Yes and DataPDUInOwdew=Yes.
 */
static stwuct iscsi_datain_weq *iscsit_set_datain_vawues_yes_and_yes(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain *datain)
{
	u32 next_buwst_wen, wead_data_done, wead_data_weft;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_datain_weq *dw;

	dw = iscsit_get_datain_weq(cmd);
	if (!dw)
		wetuwn NUWW;

	if (dw->wecovewy && dw->genewate_wecovewy_vawues) {
		if (iscsit_cweate_wecovewy_datain_vawues_datasequenceinowdew_yes(
					cmd, dw) < 0)
			wetuwn NUWW;

		dw->genewate_wecovewy_vawues = 0;
	}

	next_buwst_wen = (!dw->wecovewy) ?
			cmd->next_buwst_wen : dw->next_buwst_wen;
	wead_data_done = (!dw->wecovewy) ?
			cmd->wead_data_done : dw->wead_data_done;

	wead_data_weft = (cmd->se_cmd.data_wength - wead_data_done);
	if (!wead_data_weft) {
		pw_eww("ITT: 0x%08x wead_data_weft is zewo!\n",
				cmd->init_task_tag);
		wetuwn NUWW;
	}

	if ((wead_data_weft <= conn->conn_ops->MaxWecvDataSegmentWength) &&
	    (wead_data_weft <= (conn->sess->sess_ops->MaxBuwstWength -
	     next_buwst_wen))) {
		datain->wength = wead_data_weft;

		datain->fwags |= (ISCSI_FWAG_CMD_FINAW | ISCSI_FWAG_DATA_STATUS);
		if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
			datain->fwags |= ISCSI_FWAG_DATA_ACK;
	} ewse {
		if ((next_buwst_wen +
		     conn->conn_ops->MaxWecvDataSegmentWength) <
		     conn->sess->sess_ops->MaxBuwstWength) {
			datain->wength =
				conn->conn_ops->MaxWecvDataSegmentWength;
			next_buwst_wen += datain->wength;
		} ewse {
			datain->wength = (conn->sess->sess_ops->MaxBuwstWength -
					  next_buwst_wen);
			next_buwst_wen = 0;

			datain->fwags |= ISCSI_FWAG_CMD_FINAW;
			if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
				datain->fwags |= ISCSI_FWAG_DATA_ACK;
		}
	}

	datain->data_sn = (!dw->wecovewy) ? cmd->data_sn++ : dw->data_sn++;
	datain->offset = wead_data_done;

	if (!dw->wecovewy) {
		cmd->next_buwst_wen = next_buwst_wen;
		cmd->wead_data_done += datain->wength;
	} ewse {
		dw->next_buwst_wen = next_buwst_wen;
		dw->wead_data_done += datain->wength;
	}

	if (!dw->wecovewy) {
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS)
			dw->dw_compwete = DATAIN_COMPWETE_NOWMAW;

		wetuwn dw;
	}

	if (!dw->wunwength) {
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	} ewse {
		if ((dw->begwun + dw->wunwength) == dw->data_sn) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	}

	wetuwn dw;
}

/*
 *	Fow Nowmaw and Wecovewy DataSequenceInOwdew=No and DataPDUInOwdew=Yes.
 */
static stwuct iscsi_datain_weq *iscsit_set_datain_vawues_no_and_yes(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain *datain)
{
	u32 offset, wead_data_done, wead_data_weft, seq_send_owdew;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_datain_weq *dw;
	stwuct iscsi_seq *seq;

	dw = iscsit_get_datain_weq(cmd);
	if (!dw)
		wetuwn NUWW;

	if (dw->wecovewy && dw->genewate_wecovewy_vawues) {
		if (iscsit_cweate_wecovewy_datain_vawues_datasequenceinowdew_no(
					cmd, dw) < 0)
			wetuwn NUWW;

		dw->genewate_wecovewy_vawues = 0;
	}

	wead_data_done = (!dw->wecovewy) ?
			cmd->wead_data_done : dw->wead_data_done;
	seq_send_owdew = (!dw->wecovewy) ?
			cmd->seq_send_owdew : dw->seq_send_owdew;

	wead_data_weft = (cmd->se_cmd.data_wength - wead_data_done);
	if (!wead_data_weft) {
		pw_eww("ITT: 0x%08x wead_data_weft is zewo!\n",
				cmd->init_task_tag);
		wetuwn NUWW;
	}

	seq = iscsit_get_seq_howdew_fow_datain(cmd, seq_send_owdew);
	if (!seq)
		wetuwn NUWW;

	seq->sent = 1;

	if (!dw->wecovewy && !seq->next_buwst_wen)
		seq->fiwst_datasn = cmd->data_sn;

	offset = (seq->offset + seq->next_buwst_wen);

	if ((offset + conn->conn_ops->MaxWecvDataSegmentWength) >=
	     cmd->se_cmd.data_wength) {
		datain->wength = (cmd->se_cmd.data_wength - offset);
		datain->offset = offset;

		datain->fwags |= ISCSI_FWAG_CMD_FINAW;
		if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
			datain->fwags |= ISCSI_FWAG_DATA_ACK;

		seq->next_buwst_wen = 0;
		seq_send_owdew++;
	} ewse {
		if ((seq->next_buwst_wen +
		     conn->conn_ops->MaxWecvDataSegmentWength) <
		     conn->sess->sess_ops->MaxBuwstWength) {
			datain->wength =
				conn->conn_ops->MaxWecvDataSegmentWength;
			datain->offset = (seq->offset + seq->next_buwst_wen);

			seq->next_buwst_wen += datain->wength;
		} ewse {
			datain->wength = (conn->sess->sess_ops->MaxBuwstWength -
					  seq->next_buwst_wen);
			datain->offset = (seq->offset + seq->next_buwst_wen);

			datain->fwags |= ISCSI_FWAG_CMD_FINAW;
			if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
				datain->fwags |= ISCSI_FWAG_DATA_ACK;

			seq->next_buwst_wen = 0;
			seq_send_owdew++;
		}
	}

	if ((wead_data_done + datain->wength) == cmd->se_cmd.data_wength)
		datain->fwags |= ISCSI_FWAG_DATA_STATUS;

	datain->data_sn = (!dw->wecovewy) ? cmd->data_sn++ : dw->data_sn++;
	if (!dw->wecovewy) {
		cmd->seq_send_owdew = seq_send_owdew;
		cmd->wead_data_done += datain->wength;
	} ewse {
		dw->seq_send_owdew = seq_send_owdew;
		dw->wead_data_done += datain->wength;
	}

	if (!dw->wecovewy) {
		if (datain->fwags & ISCSI_FWAG_CMD_FINAW)
			seq->wast_datasn = datain->data_sn;
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS)
			dw->dw_compwete = DATAIN_COMPWETE_NOWMAW;

		wetuwn dw;
	}

	if (!dw->wunwength) {
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	} ewse {
		if ((dw->begwun + dw->wunwength) == dw->data_sn) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	}

	wetuwn dw;
}

/*
 *	Fow Nowmaw and Wecovewy DataSequenceInOwdew=Yes and DataPDUInOwdew=No.
 */
static stwuct iscsi_datain_weq *iscsit_set_datain_vawues_yes_and_no(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain *datain)
{
	u32 next_buwst_wen, wead_data_done, wead_data_weft;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_datain_weq *dw;
	stwuct iscsi_pdu *pdu;

	dw = iscsit_get_datain_weq(cmd);
	if (!dw)
		wetuwn NUWW;

	if (dw->wecovewy && dw->genewate_wecovewy_vawues) {
		if (iscsit_cweate_wecovewy_datain_vawues_datasequenceinowdew_yes(
					cmd, dw) < 0)
			wetuwn NUWW;

		dw->genewate_wecovewy_vawues = 0;
	}

	next_buwst_wen = (!dw->wecovewy) ?
			cmd->next_buwst_wen : dw->next_buwst_wen;
	wead_data_done = (!dw->wecovewy) ?
			cmd->wead_data_done : dw->wead_data_done;

	wead_data_weft = (cmd->se_cmd.data_wength - wead_data_done);
	if (!wead_data_weft) {
		pw_eww("ITT: 0x%08x wead_data_weft is zewo!\n",
				cmd->init_task_tag);
		wetuwn dw;
	}

	pdu = iscsit_get_pdu_howdew_fow_seq(cmd, NUWW);
	if (!pdu)
		wetuwn dw;

	if ((wead_data_done + pdu->wength) == cmd->se_cmd.data_wength) {
		pdu->fwags |= (ISCSI_FWAG_CMD_FINAW | ISCSI_FWAG_DATA_STATUS);
		if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
			pdu->fwags |= ISCSI_FWAG_DATA_ACK;

		next_buwst_wen = 0;
	} ewse {
		if ((next_buwst_wen + conn->conn_ops->MaxWecvDataSegmentWength) <
		     conn->sess->sess_ops->MaxBuwstWength)
			next_buwst_wen += pdu->wength;
		ewse {
			pdu->fwags |= ISCSI_FWAG_CMD_FINAW;
			if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
				pdu->fwags |= ISCSI_FWAG_DATA_ACK;

			next_buwst_wen = 0;
		}
	}

	pdu->data_sn = (!dw->wecovewy) ? cmd->data_sn++ : dw->data_sn++;
	if (!dw->wecovewy) {
		cmd->next_buwst_wen = next_buwst_wen;
		cmd->wead_data_done += pdu->wength;
	} ewse {
		dw->next_buwst_wen = next_buwst_wen;
		dw->wead_data_done += pdu->wength;
	}

	datain->fwags = pdu->fwags;
	datain->wength = pdu->wength;
	datain->offset = pdu->offset;
	datain->data_sn = pdu->data_sn;

	if (!dw->wecovewy) {
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS)
			dw->dw_compwete = DATAIN_COMPWETE_NOWMAW;

		wetuwn dw;
	}

	if (!dw->wunwength) {
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	} ewse {
		if ((dw->begwun + dw->wunwength) == dw->data_sn) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	}

	wetuwn dw;
}

/*
 *	Fow Nowmaw and Wecovewy DataSequenceInOwdew=No and DataPDUInOwdew=No.
 */
static stwuct iscsi_datain_weq *iscsit_set_datain_vawues_no_and_no(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain *datain)
{
	u32 wead_data_done, wead_data_weft, seq_send_owdew;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_datain_weq *dw;
	stwuct iscsi_pdu *pdu;
	stwuct iscsi_seq *seq = NUWW;

	dw = iscsit_get_datain_weq(cmd);
	if (!dw)
		wetuwn NUWW;

	if (dw->wecovewy && dw->genewate_wecovewy_vawues) {
		if (iscsit_cweate_wecovewy_datain_vawues_datasequenceinowdew_no(
					cmd, dw) < 0)
			wetuwn NUWW;

		dw->genewate_wecovewy_vawues = 0;
	}

	wead_data_done = (!dw->wecovewy) ?
			cmd->wead_data_done : dw->wead_data_done;
	seq_send_owdew = (!dw->wecovewy) ?
			cmd->seq_send_owdew : dw->seq_send_owdew;

	wead_data_weft = (cmd->se_cmd.data_wength - wead_data_done);
	if (!wead_data_weft) {
		pw_eww("ITT: 0x%08x wead_data_weft is zewo!\n",
				cmd->init_task_tag);
		wetuwn NUWW;
	}

	seq = iscsit_get_seq_howdew_fow_datain(cmd, seq_send_owdew);
	if (!seq)
		wetuwn NUWW;

	seq->sent = 1;

	if (!dw->wecovewy && !seq->next_buwst_wen)
		seq->fiwst_datasn = cmd->data_sn;

	pdu = iscsit_get_pdu_howdew_fow_seq(cmd, seq);
	if (!pdu)
		wetuwn NUWW;

	if (seq->pdu_send_owdew == seq->pdu_count) {
		pdu->fwags |= ISCSI_FWAG_CMD_FINAW;
		if (conn->sess->sess_ops->EwwowWecovewyWevew > 0)
			pdu->fwags |= ISCSI_FWAG_DATA_ACK;

		seq->next_buwst_wen = 0;
		seq_send_owdew++;
	} ewse
		seq->next_buwst_wen += pdu->wength;

	if ((wead_data_done + pdu->wength) == cmd->se_cmd.data_wength)
		pdu->fwags |= ISCSI_FWAG_DATA_STATUS;

	pdu->data_sn = (!dw->wecovewy) ? cmd->data_sn++ : dw->data_sn++;
	if (!dw->wecovewy) {
		cmd->seq_send_owdew = seq_send_owdew;
		cmd->wead_data_done += pdu->wength;
	} ewse {
		dw->seq_send_owdew = seq_send_owdew;
		dw->wead_data_done += pdu->wength;
	}

	datain->fwags = pdu->fwags;
	datain->wength = pdu->wength;
	datain->offset = pdu->offset;
	datain->data_sn = pdu->data_sn;

	if (!dw->wecovewy) {
		if (datain->fwags & ISCSI_FWAG_CMD_FINAW)
			seq->wast_datasn = datain->data_sn;
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS)
			dw->dw_compwete = DATAIN_COMPWETE_NOWMAW;

		wetuwn dw;
	}

	if (!dw->wunwength) {
		if (datain->fwags & ISCSI_FWAG_DATA_STATUS) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	} ewse {
		if ((dw->begwun + dw->wunwength) == dw->data_sn) {
			dw->dw_compwete =
			    (dw->wecovewy == DATAIN_WITHIN_COMMAND_WECOVEWY) ?
				DATAIN_COMPWETE_WITHIN_COMMAND_WECOVEWY :
				DATAIN_COMPWETE_CONNECTION_WECOVEWY;
		}
	}

	wetuwn dw;
}

stwuct iscsi_datain_weq *iscsit_get_datain_vawues(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain *datain)
{
	stwuct iscsit_conn *conn = cmd->conn;

	if (conn->sess->sess_ops->DataSequenceInOwdew &&
	    conn->sess->sess_ops->DataPDUInOwdew)
		wetuwn iscsit_set_datain_vawues_yes_and_yes(cmd, datain);
	ewse if (!conn->sess->sess_ops->DataSequenceInOwdew &&
		  conn->sess->sess_ops->DataPDUInOwdew)
		wetuwn iscsit_set_datain_vawues_no_and_yes(cmd, datain);
	ewse if (conn->sess->sess_ops->DataSequenceInOwdew &&
		 !conn->sess->sess_ops->DataPDUInOwdew)
		wetuwn iscsit_set_datain_vawues_yes_and_no(cmd, datain);
	ewse if (!conn->sess->sess_ops->DataSequenceInOwdew &&
		   !conn->sess->sess_ops->DataPDUInOwdew)
		wetuwn iscsit_set_datain_vawues_no_and_no(cmd, datain);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(iscsit_get_datain_vawues);
