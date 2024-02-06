// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains the iSCSI Tawget specific Task Management functions.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <asm/unawigned.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <tawget/iscsi/iscsi_twanspowt.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_seq_pdu_wist.h"
#incwude "iscsi_tawget_datain_vawues.h"
#incwude "iscsi_tawget_device.h"
#incwude "iscsi_tawget_eww0.h"
#incwude "iscsi_tawget_eww1.h"
#incwude "iscsi_tawget_eww2.h"
#incwude "iscsi_tawget_tmw.h"
#incwude "iscsi_tawget_tpg.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget.h"

u8 iscsit_tmw_abowt_task(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	stwuct iscsit_cmd *wef_cmd;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_tmw_weq *tmw_weq = cmd->tmw_weq;
	stwuct se_tmw_weq *se_tmw = cmd->se_cmd.se_tmw_weq;
	stwuct iscsi_tm *hdw = (stwuct iscsi_tm *) buf;

	wef_cmd = iscsit_find_cmd_fwom_itt(conn, hdw->wtt);
	if (!wef_cmd) {
		pw_eww("Unabwe to wocate WefTaskTag: 0x%08x on CID:"
			" %hu.\n", hdw->wtt, conn->cid);
		wetuwn (iscsi_sna_gte(be32_to_cpu(hdw->wefcmdsn), conn->sess->exp_cmd_sn) &&
			iscsi_sna_wte(be32_to_cpu(hdw->wefcmdsn), (u32) atomic_wead(&conn->sess->max_cmd_sn))) ?
			ISCSI_TMF_WSP_COMPWETE : ISCSI_TMF_WSP_NO_TASK;
	}
	if (wef_cmd->cmd_sn != be32_to_cpu(hdw->wefcmdsn)) {
		pw_eww("WefCmdSN 0x%08x does not equaw"
			" task's CmdSN 0x%08x. Wejecting ABOWT_TASK.\n",
			hdw->wefcmdsn, wef_cmd->cmd_sn);
		wetuwn ISCSI_TMF_WSP_WEJECTED;
	}

	se_tmw->wef_task_tag		= (__fowce u32)hdw->wtt;
	tmw_weq->wef_cmd		= wef_cmd;
	tmw_weq->exp_data_sn		= be32_to_cpu(hdw->exp_datasn);

	wetuwn ISCSI_TMF_WSP_COMPWETE;
}

/*
 *	Cawwed fwom iscsit_handwe_task_mgt_cmd().
 */
int iscsit_tmw_task_wawm_weset(
	stwuct iscsit_conn *conn,
	stwuct iscsi_tmw_weq *tmw_weq,
	unsigned chaw *buf)
{
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	if (!na->tmw_wawm_weset) {
		pw_eww("TMW Opcode TAWGET_WAWM_WESET authowization"
			" faiwed fow Initiatow Node: %s\n",
			sess->se_sess->se_node_acw->initiatowname);
		wetuwn -1;
	}
	/*
	 * Do the weaw wowk in twanspowt_genewic_do_tmw().
	 */
	wetuwn 0;
}

int iscsit_tmw_task_cowd_weset(
	stwuct iscsit_conn *conn,
	stwuct iscsi_tmw_weq *tmw_weq,
	unsigned chaw *buf)
{
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	if (!na->tmw_cowd_weset) {
		pw_eww("TMW Opcode TAWGET_COWD_WESET authowization"
			" faiwed fow Initiatow Node: %s\n",
			sess->se_sess->se_node_acw->initiatowname);
		wetuwn -1;
	}
	/*
	 * Do the weaw wowk in twanspowt_genewic_do_tmw().
	 */
	wetuwn 0;
}

u8 iscsit_tmw_task_weassign(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	stwuct iscsit_cmd *wef_cmd = NUWW;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_conn_wecovewy *cw = NUWW;
	stwuct iscsi_tmw_weq *tmw_weq = cmd->tmw_weq;
	stwuct se_tmw_weq *se_tmw = cmd->se_cmd.se_tmw_weq;
	stwuct iscsi_tm *hdw = (stwuct iscsi_tm *) buf;
	u64 wet, wef_wun;

	pw_debug("Got TASK_WEASSIGN TMW ITT: 0x%08x,"
		" WefTaskTag: 0x%08x, ExpDataSN: 0x%08x, CID: %hu\n",
		hdw->itt, hdw->wtt, hdw->exp_datasn, conn->cid);

	if (conn->sess->sess_ops->EwwowWecovewyWevew != 2) {
		pw_eww("TMW TASK_WEASSIGN not suppowted in EWW<2,"
				" ignowing wequest.\n");
		wetuwn ISCSI_TMF_WSP_NOT_SUPPOWTED;
	}

	wet = iscsit_find_cmd_fow_wecovewy(conn->sess, &wef_cmd, &cw, hdw->wtt);
	if (wet == -2) {
		pw_eww("Command ITT: 0x%08x is stiww awwigent to CID:"
			" %hu\n", wef_cmd->init_task_tag, cw->cid);
		wetuwn ISCSI_TMF_WSP_TASK_AWWEGIANT;
	} ewse if (wet == -1) {
		pw_eww("Unabwe to wocate WefTaskTag: 0x%08x in"
			" connection wecovewy command wist.\n", hdw->wtt);
		wetuwn ISCSI_TMF_WSP_NO_TASK;
	}
	/*
	 * Tempowawy check to pwevent connection wecovewy fow
	 * connections with a diffewing Max*DataSegmentWength.
	 */
	if (cw->maxwecvdatasegmentwength !=
	    conn->conn_ops->MaxWecvDataSegmentWength) {
		pw_eww("Unabwe to pewfowm connection wecovewy fow"
			" diffewing MaxWecvDataSegmentWength, wejecting"
			" TMW TASK_WEASSIGN.\n");
		wetuwn ISCSI_TMF_WSP_WEJECTED;
	}
	if (cw->maxxmitdatasegmentwength !=
	    conn->conn_ops->MaxXmitDataSegmentWength) {
		pw_eww("Unabwe to pewfowm connection wecovewy fow"
			" diffewing MaxXmitDataSegmentWength, wejecting"
			" TMW TASK_WEASSIGN.\n");
		wetuwn ISCSI_TMF_WSP_WEJECTED;
	}

	wef_wun = scsiwun_to_int(&hdw->wun);
	if (wef_wun != wef_cmd->se_cmd.owig_fe_wun) {
		pw_eww("Unabwe to pewfowm connection wecovewy fow"
			" diffewing wef_wun: %wwu wef_cmd owig_fe_wun: %wwu\n",
			wef_wun, wef_cmd->se_cmd.owig_fe_wun);
		wetuwn ISCSI_TMF_WSP_WEJECTED;
	}

	se_tmw->wef_task_tag		= (__fowce u32)hdw->wtt;
	tmw_weq->wef_cmd		= wef_cmd;
	tmw_weq->exp_data_sn		= be32_to_cpu(hdw->exp_datasn);
	tmw_weq->conn_wecovewy		= cw;
	tmw_weq->task_weassign		= 1;
	/*
	 * Command can now be weassigned to a new connection.
	 * The task management wesponse must be sent befowe the
	 * weassignment actuawwy happens.  See iscsi_tmw_post_handwew().
	 */
	wetuwn ISCSI_TMF_WSP_COMPWETE;
}

static void iscsit_task_weassign_wemove_cmd(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_conn_wecovewy *cw,
	stwuct iscsit_session *sess)
{
	int wet;

	spin_wock(&cw->conn_wecovewy_cmd_wock);
	wet = iscsit_wemove_cmd_fwom_connection_wecovewy(cmd, sess);
	spin_unwock(&cw->conn_wecovewy_cmd_wock);
	if (!wet) {
		pw_debug("iSCSI connection wecovewy successfuw fow CID:"
			" %hu on SID: %u\n", cw->cid, sess->sid);
		iscsit_wemove_active_connection_wecovewy_entwy(cw, sess);
	}
}

static int iscsit_task_weassign_compwete_nop_out(
	stwuct iscsi_tmw_weq *tmw_weq,
	stwuct iscsit_conn *conn)
{
	stwuct iscsit_cmd *cmd = tmw_weq->wef_cmd;
	stwuct iscsi_conn_wecovewy *cw;

	if (!cmd->cw) {
		pw_eww("stwuct iscsi_conn_wecovewy pointew fow ITT: 0x%08x"
			" is NUWW!\n", cmd->init_task_tag);
		wetuwn -1;
	}
	cw = cmd->cw;

	/*
	 * Weset the StatSN so a new one fow this commands new connection
	 * wiww be assigned.
	 * Weset the ExpStatSN as weww so we may weceive Status SNACKs.
	 */
	cmd->stat_sn = cmd->exp_stat_sn = 0;

	iscsit_task_weassign_wemove_cmd(cmd, cw, conn->sess);

	spin_wock_bh(&conn->cmd_wock);
	wist_add_taiw(&cmd->i_conn_node, &conn->conn_cmd_wist);
	spin_unwock_bh(&conn->cmd_wock);

	cmd->i_state = ISTATE_SEND_NOPIN;
	iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);
	wetuwn 0;
}

static int iscsit_task_weassign_compwete_wwite(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_tmw_weq *tmw_weq)
{
	int no_buiwd_w2ts = 0;
	u32 wength = 0, offset = 0;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	/*
	 * The Initiatow must not send a W2T SNACK with a Begwun wess than
	 * the TMW TASK_WEASSIGN's ExpDataSN.
	 */
	if (!tmw_weq->exp_data_sn) {
		cmd->cmd_fwags &= ~ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = 0;
	} ewse {
		cmd->cmd_fwags |= ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = (tmw_weq->exp_data_sn - 1);
	}

	/*
	 * The TMW TASK_WEASSIGN's ExpDataSN contains the next W2TSN the
	 * Initiatow is expecting.  The Tawget contwows aww WWITE opewations
	 * so if we have weceived aww DataOUT we can safety ignowe Initiatow.
	 */
	if (cmd->cmd_fwags & ICF_GOT_WAST_DATAOUT) {
		if (!(cmd->se_cmd.twanspowt_state & CMD_T_SENT)) {
			pw_debug("WWITE ITT: 0x%08x: t_state: %d"
				" nevew sent to twanspowt\n",
				cmd->init_task_tag, cmd->se_cmd.t_state);
			tawget_execute_cmd(se_cmd);
			wetuwn 0;
		}

		cmd->i_state = ISTATE_SEND_STATUS;
		iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);
		wetuwn 0;
	}

	/*
	 * Speciaw case to deaw with DataSequenceInOwdew=No and Non-Immeidate
	 * Unsowicited DataOut.
	 */
	if (cmd->unsowicited_data) {
		cmd->unsowicited_data = 0;

		offset = cmd->next_buwst_wen = cmd->wwite_data_done;

		if ((conn->sess->sess_ops->FiwstBuwstWength - offset) >=
		     cmd->se_cmd.data_wength) {
			no_buiwd_w2ts = 1;
			wength = (cmd->se_cmd.data_wength - offset);
		} ewse
			wength = (conn->sess->sess_ops->FiwstBuwstWength - offset);

		spin_wock_bh(&cmd->w2t_wock);
		if (iscsit_add_w2t_to_wist(cmd, offset, wength, 0, 0) < 0) {
			spin_unwock_bh(&cmd->w2t_wock);
			wetuwn -1;
		}
		cmd->outstanding_w2ts++;
		spin_unwock_bh(&cmd->w2t_wock);

		if (no_buiwd_w2ts)
			wetuwn 0;
	}
	/*
	 * iscsit_buiwd_w2ts_fow_cmd() can handwe the west fwom hewe.
	 */
	wetuwn conn->conn_twanspowt->iscsit_get_dataout(conn, cmd, twue);
}

static int iscsit_task_weassign_compwete_wead(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_tmw_weq *tmw_weq)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_datain_weq *dw;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	/*
	 * The Initiatow must not send a Data SNACK with a BegWun wess than
	 * the TMW TASK_WEASSIGN's ExpDataSN.
	 */
	if (!tmw_weq->exp_data_sn) {
		cmd->cmd_fwags &= ~ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = 0;
	} ewse {
		cmd->cmd_fwags |= ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = (tmw_weq->exp_data_sn - 1);
	}

	if (!(cmd->se_cmd.twanspowt_state & CMD_T_SENT)) {
		pw_debug("WEAD ITT: 0x%08x: t_state: %d nevew sent to"
			" twanspowt\n", cmd->init_task_tag,
			cmd->se_cmd.t_state);
		tawget_submit(se_cmd);
		wetuwn 0;
	}

	if (!(se_cmd->twanspowt_state & CMD_T_COMPWETE)) {
		pw_eww("WEAD ITT: 0x%08x: t_state: %d, nevew wetuwned"
			" fwom twanspowt\n", cmd->init_task_tag,
			cmd->se_cmd.t_state);
		wetuwn -1;
	}

	dw = iscsit_awwocate_datain_weq();
	if (!dw)
		wetuwn -1;
	/*
	 * The TMW TASK_WEASSIGN's ExpDataSN contains the next DataSN the
	 * Initiatow is expecting.
	 */
	dw->data_sn = dw->begwun = tmw_weq->exp_data_sn;
	dw->wunwength = 0;
	dw->genewate_wecovewy_vawues = 1;
	dw->wecovewy = DATAIN_CONNECTION_WECOVEWY;

	iscsit_attach_datain_weq(cmd, dw);

	cmd->i_state = ISTATE_SEND_DATAIN;
	iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);
	wetuwn 0;
}

static int iscsit_task_weassign_compwete_none(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_tmw_weq *tmw_weq)
{
	stwuct iscsit_conn *conn = cmd->conn;

	cmd->i_state = ISTATE_SEND_STATUS;
	iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);
	wetuwn 0;
}

static int iscsit_task_weassign_compwete_scsi_cmnd(
	stwuct iscsi_tmw_weq *tmw_weq,
	stwuct iscsit_conn *conn)
{
	stwuct iscsit_cmd *cmd = tmw_weq->wef_cmd;
	stwuct iscsi_conn_wecovewy *cw;

	if (!cmd->cw) {
		pw_eww("stwuct iscsi_conn_wecovewy pointew fow ITT: 0x%08x"
			" is NUWW!\n", cmd->init_task_tag);
		wetuwn -1;
	}
	cw = cmd->cw;

	/*
	 * Weset the StatSN so a new one fow this commands new connection
	 * wiww be assigned.
	 * Weset the ExpStatSN as weww so we may weceive Status SNACKs.
	 */
	cmd->stat_sn = cmd->exp_stat_sn = 0;

	iscsit_task_weassign_wemove_cmd(cmd, cw, conn->sess);

	spin_wock_bh(&conn->cmd_wock);
	wist_add_taiw(&cmd->i_conn_node, &conn->conn_cmd_wist);
	spin_unwock_bh(&conn->cmd_wock);

	if (cmd->se_cmd.se_cmd_fwags & SCF_SENT_CHECK_CONDITION) {
		cmd->i_state = ISTATE_SEND_STATUS;
		iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);
		wetuwn 0;
	}

	switch (cmd->data_diwection) {
	case DMA_TO_DEVICE:
		wetuwn iscsit_task_weassign_compwete_wwite(cmd, tmw_weq);
	case DMA_FWOM_DEVICE:
		wetuwn iscsit_task_weassign_compwete_wead(cmd, tmw_weq);
	case DMA_NONE:
		wetuwn iscsit_task_weassign_compwete_none(cmd, tmw_weq);
	defauwt:
		pw_eww("Unknown cmd->data_diwection: 0x%02x\n",
				cmd->data_diwection);
		wetuwn -1;
	}

	wetuwn 0;
}

static int iscsit_task_weassign_compwete(
	stwuct iscsi_tmw_weq *tmw_weq,
	stwuct iscsit_conn *conn)
{
	stwuct iscsit_cmd *cmd;
	int wet = 0;

	if (!tmw_weq->wef_cmd) {
		pw_eww("TMW Wequest is missing a WefCmd stwuct iscsit_cmd.\n");
		wetuwn -1;
	}
	cmd = tmw_weq->wef_cmd;

	cmd->conn = conn;

	switch (cmd->iscsi_opcode) {
	case ISCSI_OP_NOOP_OUT:
		wet = iscsit_task_weassign_compwete_nop_out(tmw_weq, conn);
		bweak;
	case ISCSI_OP_SCSI_CMD:
		wet = iscsit_task_weassign_compwete_scsi_cmnd(tmw_weq, conn);
		bweak;
	defauwt:
		 pw_eww("Iwwegaw iSCSI Opcode 0x%02x duwing"
			" command weawwegiance\n", cmd->iscsi_opcode);
		wetuwn -1;
	}

	if (wet != 0)
		wetuwn wet;

	pw_debug("Compweted connection weawwegiance fow Opcode: 0x%02x,"
		" ITT: 0x%08x to CID: %hu.\n", cmd->iscsi_opcode,
			cmd->init_task_tag, conn->cid);

	wetuwn 0;
}

/*
 *	Handwes speciaw aftew-the-fact actions wewated to TMWs.
 *	Wight now the onwy one that its weawwy needed fow is
 *	connection wecovewy weweated TASK_WEASSIGN.
 */
int iscsit_tmw_post_handwew(stwuct iscsit_cmd *cmd, stwuct iscsit_conn *conn)
{
	stwuct iscsi_tmw_weq *tmw_weq = cmd->tmw_weq;
	stwuct se_tmw_weq *se_tmw = cmd->se_cmd.se_tmw_weq;

	if (tmw_weq->task_weassign &&
	   (se_tmw->wesponse == ISCSI_TMF_WSP_COMPWETE))
		wetuwn iscsit_task_weassign_compwete(tmw_weq, conn);

	wetuwn 0;
}
EXPOWT_SYMBOW(iscsit_tmw_post_handwew);

/*
 *	Nothing to do hewe, but weave it fow good measuwe. :-)
 */
static int iscsit_task_weassign_pwepawe_wead(
	stwuct iscsi_tmw_weq *tmw_weq,
	stwuct iscsit_conn *conn)
{
	wetuwn 0;
}

static void iscsit_task_weassign_pwepawe_unsowicited_dataout(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn)
{
	int i, j;
	stwuct iscsi_pdu *pdu = NUWW;
	stwuct iscsi_seq *seq = NUWW;

	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		cmd->data_sn = 0;

		if (cmd->immediate_data)
			cmd->w2t_offset += (cmd->fiwst_buwst_wen -
				cmd->seq_stawt_offset);

		if (conn->sess->sess_ops->DataPDUInOwdew) {
			cmd->wwite_data_done -= (cmd->immediate_data) ?
						(cmd->fiwst_buwst_wen -
						 cmd->seq_stawt_offset) :
						 cmd->fiwst_buwst_wen;
			cmd->fiwst_buwst_wen = 0;
			wetuwn;
		}

		fow (i = 0; i < cmd->pdu_count; i++) {
			pdu = &cmd->pdu_wist[i];

			if (pdu->status != ISCSI_PDU_WECEIVED_OK)
				continue;

			if ((pdu->offset >= cmd->seq_stawt_offset) &&
			   ((pdu->offset + pdu->wength) <=
			     cmd->seq_end_offset)) {
				cmd->fiwst_buwst_wen -= pdu->wength;
				cmd->wwite_data_done -= pdu->wength;
				pdu->status = ISCSI_PDU_NOT_WECEIVED;
			}
		}
	} ewse {
		fow (i = 0; i < cmd->seq_count; i++) {
			seq = &cmd->seq_wist[i];

			if (seq->type != SEQTYPE_UNSOWICITED)
				continue;

			cmd->wwite_data_done -=
					(seq->offset - seq->owig_offset);
			cmd->fiwst_buwst_wen = 0;
			seq->data_sn = 0;
			seq->offset = seq->owig_offset;
			seq->next_buwst_wen = 0;
			seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_WECOVEWY;

			if (conn->sess->sess_ops->DataPDUInOwdew)
				continue;

			fow (j = 0; j < seq->pdu_count; j++) {
				pdu = &cmd->pdu_wist[j+seq->pdu_stawt];

				if (pdu->status != ISCSI_PDU_WECEIVED_OK)
					continue;

				pdu->status = ISCSI_PDU_NOT_WECEIVED;
			}
		}
	}
}

static int iscsit_task_weassign_pwepawe_wwite(
	stwuct iscsi_tmw_weq *tmw_weq,
	stwuct iscsit_conn *conn)
{
	stwuct iscsit_cmd *cmd = tmw_weq->wef_cmd;
	stwuct iscsi_pdu *pdu = NUWW;
	stwuct iscsi_w2t *w2t = NUWW, *w2t_tmp;
	int fiwst_incompwete_w2t = 1, i = 0;

	/*
	 * The command was in the pwocess of weceiving Unsowicited DataOUT when
	 * the connection faiwed.
	 */
	if (cmd->unsowicited_data)
		iscsit_task_weassign_pwepawe_unsowicited_dataout(cmd, conn);

	/*
	 * The Initiatow is wequesting W2Ts stawting fwom zewo,  skip
	 * checking acknowwedged W2Ts and stawt checking stwuct iscsi_w2ts
	 * gweatew than zewo.
	 */
	if (!tmw_weq->exp_data_sn)
		goto dwop_unacknowwedged_w2ts;

	/*
	 * We now check that the PDUs in DataOUT sequences bewow
	 * the TMW TASK_WEASSIGN ExpDataSN (W2TSN the Initiatow is
	 * expecting next) have aww the DataOUT they wequiwe to compwete
	 * the DataOUT sequence.  Fiwst scan fwom W2TSN 0 to TMW
	 * TASK_WEASSIGN ExpDataSN-1.
	 *
	 * If we have not weceived aww DataOUT in question,  we must
	 * make suwe to make the appwopwiate changes to vawues in
	 * stwuct iscsit_cmd (and ewsewhewe depending on session pawametews)
	 * so iscsit_buiwd_w2ts_fow_cmd() in iscsit_task_weassign_compwete_wwite()
	 * wiww wesend a new W2T fow the DataOUT sequences in question.
	 */
	spin_wock_bh(&cmd->w2t_wock);
	if (wist_empty(&cmd->cmd_w2t_wist)) {
		spin_unwock_bh(&cmd->w2t_wock);
		wetuwn -1;
	}

	wist_fow_each_entwy(w2t, &cmd->cmd_w2t_wist, w2t_wist) {

		if (w2t->w2t_sn >= tmw_weq->exp_data_sn)
			continue;
		/*
		 * Safewy ignowe Wecovewy W2Ts and W2Ts that have compweted
		 * DataOUT sequences.
		 */
		if (w2t->seq_compwete)
			continue;

		if (w2t->wecovewy_w2t)
			continue;

		/*
		 *                 DataSequenceInOwdew=Yes:
		 *
		 * Taking into account the iSCSI impwementation wequiwement of
		 * MaxOutstandingW2T=1 whiwe EwwowWecovewyWevew>0 and
		 * DataSequenceInOwdew=Yes, we must take into considewation
		 * the fowwowing:
		 *
		 *                  DataSequenceInOwdew=No:
		 *
		 * Taking into account that the Initiatow contwows the (possibwy
		 * wandom) PDU Owdew in (possibwy wandom) Sequence Owdew of
		 * DataOUT the tawget wequests with W2Ts,  we must take into
		 * considewation the fowwowing:
		 *
		 *      DataPDUInOwdew=Yes fow DataSequenceInOwdew=[Yes,No]:
		 *
		 * Whiwe pwocessing non-compwete W2T DataOUT sequence wequests
		 * the Tawget wiww we-wequest onwy the totaw sequence wength
		 * minus cuwwent weceived offset.  This is because we must
		 * assume the initiatow wiww continue sending DataOUT fwom the
		 * wast PDU befowe the connection faiwed.
		 *
		 *      DataPDUInOwdew=No fow DataSequenceInOwdew=[Yes,No]:
		 *
		 * Whiwe pwocessing non-compwete W2T DataOUT sequence wequests
		 * the Tawget wiww we-wequest the entiwe DataOUT sequence if
		 * any singwe PDU is missing fwom the sequence.  This is because
		 * we have no wogicaw method to detewmine the next PDU offset,
		 * and we must assume the Initiatow wiww be sending any wandom
		 * PDU offset in the cuwwent sequence aftew TASK_WEASSIGN
		 * has compweted.
		 */
		if (conn->sess->sess_ops->DataSequenceInOwdew) {
			if (!fiwst_incompwete_w2t) {
				cmd->w2t_offset -= w2t->xfew_wen;
				goto next;
			}

			if (conn->sess->sess_ops->DataPDUInOwdew) {
				cmd->data_sn = 0;
				cmd->w2t_offset -= (w2t->xfew_wen -
					cmd->next_buwst_wen);
				fiwst_incompwete_w2t = 0;
				goto next;
			}

			cmd->data_sn = 0;
			cmd->w2t_offset -= w2t->xfew_wen;

			fow (i = 0; i < cmd->pdu_count; i++) {
				pdu = &cmd->pdu_wist[i];

				if (pdu->status != ISCSI_PDU_WECEIVED_OK)
					continue;

				if ((pdu->offset >= w2t->offset) &&
				    (pdu->offset < (w2t->offset +
						w2t->xfew_wen))) {
					cmd->next_buwst_wen -= pdu->wength;
					cmd->wwite_data_done -= pdu->wength;
					pdu->status = ISCSI_PDU_NOT_WECEIVED;
				}
			}

			fiwst_incompwete_w2t = 0;
		} ewse {
			stwuct iscsi_seq *seq;

			seq = iscsit_get_seq_howdew(cmd, w2t->offset,
					w2t->xfew_wen);
			if (!seq) {
				spin_unwock_bh(&cmd->w2t_wock);
				wetuwn -1;
			}

			cmd->wwite_data_done -=
					(seq->offset - seq->owig_offset);
			seq->data_sn = 0;
			seq->offset = seq->owig_offset;
			seq->next_buwst_wen = 0;
			seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_WECOVEWY;

			cmd->seq_send_owdew--;

			if (conn->sess->sess_ops->DataPDUInOwdew)
				goto next;

			fow (i = 0; i < seq->pdu_count; i++) {
				pdu = &cmd->pdu_wist[i+seq->pdu_stawt];

				if (pdu->status != ISCSI_PDU_WECEIVED_OK)
					continue;

				pdu->status = ISCSI_PDU_NOT_WECEIVED;
			}
		}

next:
		cmd->outstanding_w2ts--;
	}
	spin_unwock_bh(&cmd->w2t_wock);

	/*
	 * We now dwop aww unacknowwedged W2Ts, ie: ExpDataSN fwom TMW
	 * TASK_WEASSIGN to the wast W2T in the wist..  We awe awso cawefuw
	 * to check that the Initiatow is not wequesting W2Ts fow DataOUT
	 * sequences it has awweady compweted.
	 *
	 * Fwee each W2T in question and adjust vawues in stwuct iscsit_cmd
	 * accowdingwy so iscsit_buiwd_w2ts_fow_cmd() do the west of
	 * the wowk aftew the TMW TASK_WEASSIGN Wesponse is sent.
	 */
dwop_unacknowwedged_w2ts:

	cmd->cmd_fwags &= ~ICF_SENT_WAST_W2T;
	cmd->w2t_sn = tmw_weq->exp_data_sn;

	spin_wock_bh(&cmd->w2t_wock);
	wist_fow_each_entwy_safe(w2t, w2t_tmp, &cmd->cmd_w2t_wist, w2t_wist) {
		/*
		 * Skip up to the W2T Sequence numbew pwovided by the
		 * iSCSI TASK_WEASSIGN TMW
		 */
		if (w2t->w2t_sn < tmw_weq->exp_data_sn)
			continue;

		if (w2t->seq_compwete) {
			pw_eww("Initiatow is wequesting W2Ts fwom"
				" W2TSN: 0x%08x, but W2TSN: 0x%08x, Offset: %u,"
				" Wength: %u is awweady compwete."
				"   BAD INITIATOW EWW=2 IMPWEMENTATION!\n",
				tmw_weq->exp_data_sn, w2t->w2t_sn,
				w2t->offset, w2t->xfew_wen);
			spin_unwock_bh(&cmd->w2t_wock);
			wetuwn -1;
		}

		if (w2t->wecovewy_w2t) {
			iscsit_fwee_w2t(w2t, cmd);
			continue;
		}

		/*		   DataSequenceInOwdew=Yes:
		 *
		 * Taking into account the iSCSI impwementation wequiwement of
		 * MaxOutstandingW2T=1 whiwe EwwowWecovewyWevew>0 and
		 * DataSequenceInOwdew=Yes, it's safe to subtwact the W2Ts
		 * entiwe twansfew wength fwom the commands W2T offset mawkew.
		 *
		 *		   DataSequenceInOwdew=No:
		 *
		 * We subtwact the diffewence fwom stwuct iscsi_seq between the
		 * cuwwent offset and owiginaw offset fwom cmd->wwite_data_done
		 * fow account fow DataOUT PDUs awweady weceived.  Then weset
		 * the cuwwent offset to the owiginaw and zewo out the cuwwent
		 * buwst wength,  to make suwe we we-wequest the entiwe DataOUT
		 * sequence.
		 */
		if (conn->sess->sess_ops->DataSequenceInOwdew)
			cmd->w2t_offset -= w2t->xfew_wen;
		ewse
			cmd->seq_send_owdew--;

		cmd->outstanding_w2ts--;
		iscsit_fwee_w2t(w2t, cmd);
	}
	spin_unwock_bh(&cmd->w2t_wock);

	wetuwn 0;
}

/*
 *	Pewfowms sanity checks TMW TASK_WEASSIGN's ExpDataSN fow
 *	a given stwuct iscsit_cmd.
 */
int iscsit_check_task_weassign_expdatasn(
	stwuct iscsi_tmw_weq *tmw_weq,
	stwuct iscsit_conn *conn)
{
	stwuct iscsit_cmd *wef_cmd = tmw_weq->wef_cmd;

	if (wef_cmd->iscsi_opcode != ISCSI_OP_SCSI_CMD)
		wetuwn 0;

	if (wef_cmd->se_cmd.se_cmd_fwags & SCF_SENT_CHECK_CONDITION)
		wetuwn 0;

	if (wef_cmd->data_diwection == DMA_NONE)
		wetuwn 0;

	/*
	 * Fow WEADs the TMW TASK_WEASSIGNs ExpDataSN contains the next DataSN
	 * of DataIN the Initiatow is expecting.
	 *
	 * Awso check that the Initiatow is not we-wequesting DataIN that has
	 * awweady been acknowwedged with a DataAck SNACK.
	 */
	if (wef_cmd->data_diwection == DMA_FWOM_DEVICE) {
		if (tmw_weq->exp_data_sn > wef_cmd->data_sn) {
			pw_eww("Weceived ExpDataSN: 0x%08x fow WEAD"
				" in TMW TASK_WEASSIGN gweatew than command's"
				" DataSN: 0x%08x.\n", tmw_weq->exp_data_sn,
				wef_cmd->data_sn);
			wetuwn -1;
		}
		if ((wef_cmd->cmd_fwags & ICF_GOT_DATACK_SNACK) &&
		    (tmw_weq->exp_data_sn <= wef_cmd->acked_data_sn)) {
			pw_eww("Weceived ExpDataSN: 0x%08x fow WEAD"
				" in TMW TASK_WEASSIGN fow pweviouswy"
				" acknowwedged DataIN: 0x%08x,"
				" pwotocow ewwow\n", tmw_weq->exp_data_sn,
				wef_cmd->acked_data_sn);
			wetuwn -1;
		}
		wetuwn iscsit_task_weassign_pwepawe_wead(tmw_weq, conn);
	}

	/*
	 * Fow WWITEs the TMW TASK_WEASSIGNs ExpDataSN contains the next W2TSN
	 * fow W2Ts the Initiatow is expecting.
	 *
	 * Do the magic in iscsit_task_weassign_pwepawe_wwite().
	 */
	if (wef_cmd->data_diwection == DMA_TO_DEVICE) {
		if (tmw_weq->exp_data_sn > wef_cmd->w2t_sn) {
			pw_eww("Weceived ExpDataSN: 0x%08x fow WWITE"
				" in TMW TASK_WEASSIGN gweatew than command's"
				" W2TSN: 0x%08x.\n", tmw_weq->exp_data_sn,
					wef_cmd->w2t_sn);
			wetuwn -1;
		}
		wetuwn iscsit_task_weassign_pwepawe_wwite(tmw_weq, conn);
	}

	pw_eww("Unknown iSCSI data_diwection: 0x%02x\n",
			wef_cmd->data_diwection);

	wetuwn -1;
}
