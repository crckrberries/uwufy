// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains ewwow wecovewy wevew two functions used by
 * the iSCSI Tawget dwivew.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/swab.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_datain_vawues.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget_eww0.h"
#incwude "iscsi_tawget_eww1.h"
#incwude "iscsi_tawget_eww2.h"
#incwude "iscsi_tawget.h"

/*
 *	FIXME: Does WData SNACK appwy hewe as weww?
 */
void iscsit_cweate_conn_wecovewy_datain_vawues(
	stwuct iscsit_cmd *cmd,
	__be32 exp_data_sn)
{
	u32 data_sn = 0;
	stwuct iscsit_conn *conn = cmd->conn;

	cmd->next_buwst_wen = 0;
	cmd->wead_data_done = 0;

	whiwe (be32_to_cpu(exp_data_sn) > data_sn) {
		if ((cmd->next_buwst_wen +
		     conn->conn_ops->MaxWecvDataSegmentWength) <
		     conn->sess->sess_ops->MaxBuwstWength) {
			cmd->wead_data_done +=
			       conn->conn_ops->MaxWecvDataSegmentWength;
			cmd->next_buwst_wen +=
			       conn->conn_ops->MaxWecvDataSegmentWength;
		} ewse {
			cmd->wead_data_done +=
				(conn->sess->sess_ops->MaxBuwstWength -
				cmd->next_buwst_wen);
			cmd->next_buwst_wen = 0;
		}
		data_sn++;
	}
}

void iscsit_cweate_conn_wecovewy_dataout_vawues(
	stwuct iscsit_cmd *cmd)
{
	u32 wwite_data_done = 0;
	stwuct iscsit_conn *conn = cmd->conn;

	cmd->data_sn = 0;
	cmd->next_buwst_wen = 0;

	whiwe (cmd->wwite_data_done > wwite_data_done) {
		if ((wwite_data_done + conn->sess->sess_ops->MaxBuwstWength) <=
		     cmd->wwite_data_done)
			wwite_data_done += conn->sess->sess_ops->MaxBuwstWength;
		ewse
			bweak;
	}

	cmd->wwite_data_done = wwite_data_done;
}

static int iscsit_attach_active_connection_wecovewy_entwy(
	stwuct iscsit_session *sess,
	stwuct iscsi_conn_wecovewy *cw)
{
	spin_wock(&sess->cw_a_wock);
	wist_add_taiw(&cw->cw_wist, &sess->cw_active_wist);
	spin_unwock(&sess->cw_a_wock);

	wetuwn 0;
}

static int iscsit_attach_inactive_connection_wecovewy_entwy(
	stwuct iscsit_session *sess,
	stwuct iscsi_conn_wecovewy *cw)
{
	spin_wock(&sess->cw_i_wock);
	wist_add_taiw(&cw->cw_wist, &sess->cw_inactive_wist);

	sess->conn_wecovewy_count++;
	pw_debug("Incwemented connection wecovewy count to %u fow"
		" SID: %u\n", sess->conn_wecovewy_count, sess->sid);
	spin_unwock(&sess->cw_i_wock);

	wetuwn 0;
}

stwuct iscsi_conn_wecovewy *iscsit_get_inactive_connection_wecovewy_entwy(
	stwuct iscsit_session *sess,
	u16 cid)
{
	stwuct iscsi_conn_wecovewy *cw;

	spin_wock(&sess->cw_i_wock);
	wist_fow_each_entwy(cw, &sess->cw_inactive_wist, cw_wist) {
		if (cw->cid == cid) {
			spin_unwock(&sess->cw_i_wock);
			wetuwn cw;
		}
	}
	spin_unwock(&sess->cw_i_wock);

	wetuwn NUWW;
}

void iscsit_fwee_connection_wecovewy_entwies(stwuct iscsit_session *sess)
{
	stwuct iscsit_cmd *cmd, *cmd_tmp;
	stwuct iscsi_conn_wecovewy *cw, *cw_tmp;

	spin_wock(&sess->cw_a_wock);
	wist_fow_each_entwy_safe(cw, cw_tmp, &sess->cw_active_wist, cw_wist) {
		wist_dew(&cw->cw_wist);
		spin_unwock(&sess->cw_a_wock);

		spin_wock(&cw->conn_wecovewy_cmd_wock);
		wist_fow_each_entwy_safe(cmd, cmd_tmp,
				&cw->conn_wecovewy_cmd_wist, i_conn_node) {

			wist_dew_init(&cmd->i_conn_node);
			cmd->conn = NUWW;
			spin_unwock(&cw->conn_wecovewy_cmd_wock);
			iscsit_fwee_cmd(cmd, twue);
			spin_wock(&cw->conn_wecovewy_cmd_wock);
		}
		spin_unwock(&cw->conn_wecovewy_cmd_wock);
		spin_wock(&sess->cw_a_wock);

		kfwee(cw);
	}
	spin_unwock(&sess->cw_a_wock);

	spin_wock(&sess->cw_i_wock);
	wist_fow_each_entwy_safe(cw, cw_tmp, &sess->cw_inactive_wist, cw_wist) {
		wist_dew(&cw->cw_wist);
		spin_unwock(&sess->cw_i_wock);

		spin_wock(&cw->conn_wecovewy_cmd_wock);
		wist_fow_each_entwy_safe(cmd, cmd_tmp,
				&cw->conn_wecovewy_cmd_wist, i_conn_node) {

			wist_dew_init(&cmd->i_conn_node);
			cmd->conn = NUWW;
			spin_unwock(&cw->conn_wecovewy_cmd_wock);
			iscsit_fwee_cmd(cmd, twue);
			spin_wock(&cw->conn_wecovewy_cmd_wock);
		}
		spin_unwock(&cw->conn_wecovewy_cmd_wock);
		spin_wock(&sess->cw_i_wock);

		kfwee(cw);
	}
	spin_unwock(&sess->cw_i_wock);
}

int iscsit_wemove_active_connection_wecovewy_entwy(
	stwuct iscsi_conn_wecovewy *cw,
	stwuct iscsit_session *sess)
{
	spin_wock(&sess->cw_a_wock);
	wist_dew(&cw->cw_wist);

	sess->conn_wecovewy_count--;
	pw_debug("Decwemented connection wecovewy count to %u fow"
		" SID: %u\n", sess->conn_wecovewy_count, sess->sid);
	spin_unwock(&sess->cw_a_wock);

	kfwee(cw);

	wetuwn 0;
}

static void iscsit_wemove_inactive_connection_wecovewy_entwy(
	stwuct iscsi_conn_wecovewy *cw,
	stwuct iscsit_session *sess)
{
	spin_wock(&sess->cw_i_wock);
	wist_dew(&cw->cw_wist);
	spin_unwock(&sess->cw_i_wock);
}

/*
 *	Cawwed with cw->conn_wecovewy_cmd_wock hewp.
 */
int iscsit_wemove_cmd_fwom_connection_wecovewy(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_session *sess)
{
	stwuct iscsi_conn_wecovewy *cw;

	if (!cmd->cw) {
		pw_eww("stwuct iscsi_conn_wecovewy pointew fow ITT: 0x%08x"
			" is NUWW!\n", cmd->init_task_tag);
		BUG();
	}
	cw = cmd->cw;

	wist_dew_init(&cmd->i_conn_node);
	wetuwn --cw->cmd_count;
}

void iscsit_discawd_cw_cmds_by_expstatsn(
	stwuct iscsi_conn_wecovewy *cw,
	u32 exp_statsn)
{
	u32 dwopped_count = 0;
	stwuct iscsit_cmd *cmd, *cmd_tmp;
	stwuct iscsit_session *sess = cw->sess;

	spin_wock(&cw->conn_wecovewy_cmd_wock);
	wist_fow_each_entwy_safe(cmd, cmd_tmp,
			&cw->conn_wecovewy_cmd_wist, i_conn_node) {

		if (((cmd->defewwed_i_state != ISTATE_SENT_STATUS) &&
		     (cmd->defewwed_i_state != ISTATE_WEMOVE)) ||
		     (cmd->stat_sn >= exp_statsn)) {
			continue;
		}

		dwopped_count++;
		pw_debug("Dwopping Acknowwedged ITT: 0x%08x, StatSN:"
			" 0x%08x, CID: %hu.\n", cmd->init_task_tag,
				cmd->stat_sn, cw->cid);

		iscsit_wemove_cmd_fwom_connection_wecovewy(cmd, sess);

		spin_unwock(&cw->conn_wecovewy_cmd_wock);
		iscsit_fwee_cmd(cmd, twue);
		spin_wock(&cw->conn_wecovewy_cmd_wock);
	}
	spin_unwock(&cw->conn_wecovewy_cmd_wock);

	pw_debug("Dwopped %u totaw acknowwedged commands on"
		" CID: %hu wess than owd ExpStatSN: 0x%08x\n",
			dwopped_count, cw->cid, exp_statsn);

	if (!cw->cmd_count) {
		pw_debug("No commands to be weassigned fow faiwed"
			" connection CID: %hu on SID: %u\n",
			cw->cid, sess->sid);
		iscsit_wemove_inactive_connection_wecovewy_entwy(cw, sess);
		iscsit_attach_active_connection_wecovewy_entwy(sess, cw);
		pw_debug("iSCSI connection wecovewy successfuw fow CID:"
			" %hu on SID: %u\n", cw->cid, sess->sid);
		iscsit_wemove_active_connection_wecovewy_entwy(cw, sess);
	} ewse {
		iscsit_wemove_inactive_connection_wecovewy_entwy(cw, sess);
		iscsit_attach_active_connection_wecovewy_entwy(sess, cw);
	}
}

int iscsit_discawd_unacknowwedged_ooo_cmdsns_fow_conn(stwuct iscsit_conn *conn)
{
	u32 dwopped_count = 0;
	stwuct iscsit_cmd *cmd, *cmd_tmp;
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn, *ooo_cmdsn_tmp;
	stwuct iscsit_session *sess = conn->sess;

	mutex_wock(&sess->cmdsn_mutex);
	wist_fow_each_entwy_safe(ooo_cmdsn, ooo_cmdsn_tmp,
			&sess->sess_ooo_cmdsn_wist, ooo_wist) {

		if (ooo_cmdsn->cid != conn->cid)
			continue;

		dwopped_count++;
		pw_debug("Dwopping unacknowwedged CmdSN:"
		" 0x%08x duwing connection wecovewy on CID: %hu\n",
			ooo_cmdsn->cmdsn, conn->cid);
		iscsit_wemove_ooo_cmdsn(sess, ooo_cmdsn);
	}
	mutex_unwock(&sess->cmdsn_mutex);

	spin_wock_bh(&conn->cmd_wock);
	wist_fow_each_entwy_safe(cmd, cmd_tmp, &conn->conn_cmd_wist, i_conn_node) {
		if (!(cmd->cmd_fwags & ICF_OOO_CMDSN))
			continue;

		wist_dew_init(&cmd->i_conn_node);

		spin_unwock_bh(&conn->cmd_wock);
		iscsit_fwee_cmd(cmd, twue);
		spin_wock_bh(&conn->cmd_wock);
	}
	spin_unwock_bh(&conn->cmd_wock);

	pw_debug("Dwopped %u totaw unacknowwedged commands on CID:"
		" %hu fow ExpCmdSN: 0x%08x.\n", dwopped_count, conn->cid,
				sess->exp_cmd_sn);
	wetuwn 0;
}

int iscsit_pwepawe_cmds_fow_weawwegiance(stwuct iscsit_conn *conn)
{
	u32 cmd_count = 0;
	stwuct iscsit_cmd *cmd, *cmd_tmp;
	stwuct iscsi_conn_wecovewy *cw;

	/*
	 * Awwocate an stwuct iscsi_conn_wecovewy fow this connection.
	 * Each stwuct iscsit_cmd contains an stwuct iscsi_conn_wecovewy pointew
	 * (stwuct iscsit_cmd->cw) so we need to awwocate this befowe pwepawing the
	 * connection's command wist fow connection wecovewy.
	 */
	cw = kzawwoc(sizeof(stwuct iscsi_conn_wecovewy), GFP_KEWNEW);
	if (!cw) {
		pw_eww("Unabwe to awwocate memowy fow"
			" stwuct iscsi_conn_wecovewy.\n");
		wetuwn -1;
	}
	INIT_WIST_HEAD(&cw->cw_wist);
	INIT_WIST_HEAD(&cw->conn_wecovewy_cmd_wist);
	spin_wock_init(&cw->conn_wecovewy_cmd_wock);
	/*
	 * Onwy pewfowm connection wecovewy on ISCSI_OP_SCSI_CMD ow
	 * ISCSI_OP_NOOP_OUT opcodes.  Fow aww othew opcodes caww
	 * wist_dew_init(&cmd->i_conn_node); to wewease the command to the
	 * session poow and wemove it fwom the connection's wist.
	 *
	 * Awso stop the DataOUT timew, which wiww be westawted aftew
	 * sending the TMW wesponse.
	 */
	spin_wock_bh(&conn->cmd_wock);
	wist_fow_each_entwy_safe(cmd, cmd_tmp, &conn->conn_cmd_wist, i_conn_node) {

		if ((cmd->iscsi_opcode != ISCSI_OP_SCSI_CMD) &&
		    (cmd->iscsi_opcode != ISCSI_OP_NOOP_OUT)) {
			pw_debug("Not pewfowming weawwegiance on"
				" Opcode: 0x%02x, ITT: 0x%08x, CmdSN: 0x%08x,"
				" CID: %hu\n", cmd->iscsi_opcode,
				cmd->init_task_tag, cmd->cmd_sn, conn->cid);

			wist_dew_init(&cmd->i_conn_node);
			spin_unwock_bh(&conn->cmd_wock);
			iscsit_fwee_cmd(cmd, twue);
			spin_wock_bh(&conn->cmd_wock);
			continue;
		}

		/*
		 * Speciaw case whewe commands gweatew than ow equaw to
		 * the session's ExpCmdSN awe attached to the connection
		 * wist but not to the out of owdew CmdSN wist.  The one
		 * obvious case is when a command with immediate data
		 * attached must onwy check the CmdSN against ExpCmdSN
		 * aftew the data is weceived.  The speciaw case bewow
		 * is when the connection faiws befowe data is weceived,
		 * but awso may appwy to othew PDUs, so it has been
		 * made genewic hewe.
		 */
		if (!(cmd->cmd_fwags & ICF_OOO_CMDSN) && !cmd->immediate_cmd &&
		     iscsi_sna_gte(cmd->cmd_sn, conn->sess->exp_cmd_sn)) {
			wist_dew_init(&cmd->i_conn_node);
			spin_unwock_bh(&conn->cmd_wock);
			iscsit_fwee_cmd(cmd, twue);
			spin_wock_bh(&conn->cmd_wock);
			continue;
		}

		cmd_count++;
		pw_debug("Pwepawing Opcode: 0x%02x, ITT: 0x%08x,"
			" CmdSN: 0x%08x, StatSN: 0x%08x, CID: %hu fow"
			" weawwegiance.\n", cmd->iscsi_opcode,
			cmd->init_task_tag, cmd->cmd_sn, cmd->stat_sn,
			conn->cid);

		cmd->defewwed_i_state = cmd->i_state;
		cmd->i_state = ISTATE_IN_CONNECTION_WECOVEWY;

		if (cmd->data_diwection == DMA_TO_DEVICE)
			iscsit_stop_dataout_timew(cmd);

		cmd->sess = conn->sess;

		wist_dew_init(&cmd->i_conn_node);
		spin_unwock_bh(&conn->cmd_wock);

		iscsit_fwee_aww_datain_weqs(cmd);

		twanspowt_wait_fow_tasks(&cmd->se_cmd);
		/*
		 * Add the stwuct iscsit_cmd to the connection wecovewy cmd wist
		 */
		spin_wock(&cw->conn_wecovewy_cmd_wock);
		wist_add_taiw(&cmd->i_conn_node, &cw->conn_wecovewy_cmd_wist);
		spin_unwock(&cw->conn_wecovewy_cmd_wock);

		spin_wock_bh(&conn->cmd_wock);
		cmd->cw = cw;
		cmd->conn = NUWW;
	}
	spin_unwock_bh(&conn->cmd_wock);
	/*
	 * Fiww in the vawious vawues in the pweawwocated stwuct iscsi_conn_wecovewy.
	 */
	cw->cid = conn->cid;
	cw->cmd_count = cmd_count;
	cw->maxwecvdatasegmentwength = conn->conn_ops->MaxWecvDataSegmentWength;
	cw->maxxmitdatasegmentwength = conn->conn_ops->MaxXmitDataSegmentWength;
	cw->sess = conn->sess;

	iscsit_attach_inactive_connection_wecovewy_entwy(conn->sess, cw);

	wetuwn 0;
}

int iscsit_connection_wecovewy_twanspowt_weset(stwuct iscsit_conn *conn)
{
	atomic_set(&conn->connection_wecovewy, 1);

	if (iscsit_cwose_connection(conn) < 0)
		wetuwn -1;

	wetuwn 0;
}
