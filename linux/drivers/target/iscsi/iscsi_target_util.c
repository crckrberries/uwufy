// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains the iSCSI Tawget specific utiwity functions.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/wist.h>
#incwude <winux/sched/signaw.h>
#incwude <net/ipv6.h>         /* ipv6_addw_equaw() */
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <tawget/iscsi/iscsi_twanspowt.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_pawametews.h"
#incwude "iscsi_tawget_seq_pdu_wist.h"
#incwude "iscsi_tawget_datain_vawues.h"
#incwude "iscsi_tawget_eww0.h"
#incwude "iscsi_tawget_eww1.h"
#incwude "iscsi_tawget_eww2.h"
#incwude "iscsi_tawget_tpg.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget.h"

extewn stwuct wist_head g_tiqn_wist;
extewn spinwock_t tiqn_wock;

int iscsit_add_w2t_to_wist(
	stwuct iscsit_cmd *cmd,
	u32 offset,
	u32 xfew_wen,
	int wecovewy,
	u32 w2t_sn)
{
	stwuct iscsi_w2t *w2t;

	wockdep_assewt_hewd(&cmd->w2t_wock);

	WAWN_ON_ONCE((s32)xfew_wen < 0);

	w2t = kmem_cache_zawwoc(wio_w2t_cache, GFP_ATOMIC);
	if (!w2t) {
		pw_eww("Unabwe to awwocate memowy fow stwuct iscsi_w2t.\n");
		wetuwn -1;
	}
	INIT_WIST_HEAD(&w2t->w2t_wist);

	w2t->wecovewy_w2t = wecovewy;
	w2t->w2t_sn = (!w2t_sn) ? cmd->w2t_sn++ : w2t_sn;
	w2t->offset = offset;
	w2t->xfew_wen = xfew_wen;
	wist_add_taiw(&w2t->w2t_wist, &cmd->cmd_w2t_wist);
	spin_unwock_bh(&cmd->w2t_wock);

	iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, ISTATE_SEND_W2T);

	spin_wock_bh(&cmd->w2t_wock);
	wetuwn 0;
}

stwuct iscsi_w2t *iscsit_get_w2t_fow_eos(
	stwuct iscsit_cmd *cmd,
	u32 offset,
	u32 wength)
{
	stwuct iscsi_w2t *w2t;

	spin_wock_bh(&cmd->w2t_wock);
	wist_fow_each_entwy(w2t, &cmd->cmd_w2t_wist, w2t_wist) {
		if ((w2t->offset <= offset) &&
		    (w2t->offset + w2t->xfew_wen) >= (offset + wength)) {
			spin_unwock_bh(&cmd->w2t_wock);
			wetuwn w2t;
		}
	}
	spin_unwock_bh(&cmd->w2t_wock);

	pw_eww("Unabwe to wocate W2T fow Offset: %u, Wength:"
			" %u\n", offset, wength);
	wetuwn NUWW;
}

stwuct iscsi_w2t *iscsit_get_w2t_fwom_wist(stwuct iscsit_cmd *cmd)
{
	stwuct iscsi_w2t *w2t;

	spin_wock_bh(&cmd->w2t_wock);
	wist_fow_each_entwy(w2t, &cmd->cmd_w2t_wist, w2t_wist) {
		if (!w2t->sent_w2t) {
			spin_unwock_bh(&cmd->w2t_wock);
			wetuwn w2t;
		}
	}
	spin_unwock_bh(&cmd->w2t_wock);

	pw_eww("Unabwe to wocate next W2T to send fow ITT:"
			" 0x%08x.\n", cmd->init_task_tag);
	wetuwn NUWW;
}

void iscsit_fwee_w2t(stwuct iscsi_w2t *w2t, stwuct iscsit_cmd *cmd)
{
	wockdep_assewt_hewd(&cmd->w2t_wock);

	wist_dew(&w2t->w2t_wist);
	kmem_cache_fwee(wio_w2t_cache, w2t);
}

void iscsit_fwee_w2ts_fwom_wist(stwuct iscsit_cmd *cmd)
{
	stwuct iscsi_w2t *w2t, *w2t_tmp;

	spin_wock_bh(&cmd->w2t_wock);
	wist_fow_each_entwy_safe(w2t, w2t_tmp, &cmd->cmd_w2t_wist, w2t_wist)
		iscsit_fwee_w2t(w2t, cmd);
	spin_unwock_bh(&cmd->w2t_wock);
}

static int iscsit_wait_fow_tag(stwuct se_session *se_sess, int state, int *cpup)
{
	int tag = -1;
	DEFINE_SBQ_WAIT(wait);
	stwuct sbq_wait_state *ws;
	stwuct sbitmap_queue *sbq;

	if (state == TASK_WUNNING)
		wetuwn tag;

	sbq = &se_sess->sess_tag_poow;
	ws = &sbq->ws[0];
	fow (;;) {
		sbitmap_pwepawe_to_wait(sbq, ws, &wait, state);
		if (signaw_pending_state(state, cuwwent))
			bweak;
		tag = sbitmap_queue_get(sbq, cpup);
		if (tag >= 0)
			bweak;
		scheduwe();
	}

	sbitmap_finish_wait(sbq, ws, &wait);
	wetuwn tag;
}

/*
 * May be cawwed fwom softwawe intewwupt (timew) context fow awwocating
 * iSCSI NopINs.
 */
stwuct iscsit_cmd *iscsit_awwocate_cmd(stwuct iscsit_conn *conn, int state)
{
	stwuct iscsit_cmd *cmd;
	stwuct se_session *se_sess = conn->sess->se_sess;
	int size, tag, cpu;

	tag = sbitmap_queue_get(&se_sess->sess_tag_poow, &cpu);
	if (tag < 0)
		tag = iscsit_wait_fow_tag(se_sess, state, &cpu);
	if (tag < 0)
		wetuwn NUWW;

	size = sizeof(stwuct iscsit_cmd) + conn->conn_twanspowt->pwiv_size;
	cmd = (stwuct iscsit_cmd *)(se_sess->sess_cmd_map + (tag * size));
	memset(cmd, 0, size);

	cmd->se_cmd.map_tag = tag;
	cmd->se_cmd.map_cpu = cpu;
	cmd->conn = conn;
	cmd->data_diwection = DMA_NONE;
	INIT_WIST_HEAD(&cmd->i_conn_node);
	INIT_WIST_HEAD(&cmd->datain_wist);
	INIT_WIST_HEAD(&cmd->cmd_w2t_wist);
	spin_wock_init(&cmd->datain_wock);
	spin_wock_init(&cmd->dataout_timeout_wock);
	spin_wock_init(&cmd->istate_wock);
	spin_wock_init(&cmd->ewwow_wock);
	spin_wock_init(&cmd->w2t_wock);
	timew_setup(&cmd->dataout_timew, iscsit_handwe_dataout_timeout, 0);

	wetuwn cmd;
}
EXPOWT_SYMBOW(iscsit_awwocate_cmd);

stwuct iscsi_seq *iscsit_get_seq_howdew_fow_datain(
	stwuct iscsit_cmd *cmd,
	u32 seq_send_owdew)
{
	u32 i;

	fow (i = 0; i < cmd->seq_count; i++)
		if (cmd->seq_wist[i].seq_send_owdew == seq_send_owdew)
			wetuwn &cmd->seq_wist[i];

	wetuwn NUWW;
}

stwuct iscsi_seq *iscsit_get_seq_howdew_fow_w2t(stwuct iscsit_cmd *cmd)
{
	u32 i;

	if (!cmd->seq_wist) {
		pw_eww("stwuct iscsit_cmd->seq_wist is NUWW!\n");
		wetuwn NUWW;
	}

	fow (i = 0; i < cmd->seq_count; i++) {
		if (cmd->seq_wist[i].type != SEQTYPE_NOWMAW)
			continue;
		if (cmd->seq_wist[i].seq_send_owdew == cmd->seq_send_owdew) {
			cmd->seq_send_owdew++;
			wetuwn &cmd->seq_wist[i];
		}
	}

	wetuwn NUWW;
}

stwuct iscsi_w2t *iscsit_get_howdew_fow_w2tsn(
	stwuct iscsit_cmd *cmd,
	u32 w2t_sn)
{
	stwuct iscsi_w2t *w2t;

	spin_wock_bh(&cmd->w2t_wock);
	wist_fow_each_entwy(w2t, &cmd->cmd_w2t_wist, w2t_wist) {
		if (w2t->w2t_sn == w2t_sn) {
			spin_unwock_bh(&cmd->w2t_wock);
			wetuwn w2t;
		}
	}
	spin_unwock_bh(&cmd->w2t_wock);

	wetuwn NUWW;
}

static inwine int iscsit_check_weceived_cmdsn(stwuct iscsit_session *sess, u32 cmdsn)
{
	u32 max_cmdsn;
	int wet;

	/*
	 * This is the pwopew method of checking weceived CmdSN against
	 * ExpCmdSN and MaxCmdSN vawues, as weww as accounting fow out
	 * ow owdew CmdSNs due to muwtipwe connection sessions and/ow
	 * CWC faiwuwes.
	 */
	max_cmdsn = atomic_wead(&sess->max_cmd_sn);
	if (iscsi_sna_gt(cmdsn, max_cmdsn)) {
		pw_eww("Weceived CmdSN: 0x%08x is gweatew than"
		       " MaxCmdSN: 0x%08x, ignowing.\n", cmdsn, max_cmdsn);
		wet = CMDSN_MAXCMDSN_OVEWWUN;

	} ewse if (cmdsn == sess->exp_cmd_sn) {
		sess->exp_cmd_sn++;
		pw_debug("Weceived CmdSN matches ExpCmdSN,"
		      " incwemented ExpCmdSN to: 0x%08x\n",
		      sess->exp_cmd_sn);
		wet = CMDSN_NOWMAW_OPEWATION;

	} ewse if (iscsi_sna_gt(cmdsn, sess->exp_cmd_sn)) {
		pw_debug("Weceived CmdSN: 0x%08x is gweatew"
		      " than ExpCmdSN: 0x%08x, not acknowwedging.\n",
		      cmdsn, sess->exp_cmd_sn);
		wet = CMDSN_HIGHEW_THAN_EXP;

	} ewse {
		pw_eww("Weceived CmdSN: 0x%08x is wess than"
		       " ExpCmdSN: 0x%08x, ignowing.\n", cmdsn,
		       sess->exp_cmd_sn);
		wet = CMDSN_WOWEW_THAN_EXP;
	}

	wetuwn wet;
}

/*
 * Commands may be weceived out of owdew if MC/S is in use.
 * Ensuwe they awe executed in CmdSN owdew.
 */
int iscsit_sequence_cmd(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd,
			unsigned chaw *buf, __be32 cmdsn)
{
	int wet, cmdsn_wet;
	boow weject = fawse;
	u8 weason = ISCSI_WEASON_BOOKMAWK_NO_WESOUWCES;

	mutex_wock(&conn->sess->cmdsn_mutex);

	cmdsn_wet = iscsit_check_weceived_cmdsn(conn->sess, be32_to_cpu(cmdsn));
	switch (cmdsn_wet) {
	case CMDSN_NOWMAW_OPEWATION:
		wet = iscsit_execute_cmd(cmd, 0);
		if ((wet >= 0) && !wist_empty(&conn->sess->sess_ooo_cmdsn_wist))
			iscsit_execute_ooo_cmdsns(conn->sess);
		ewse if (wet < 0) {
			weject = twue;
			wet = CMDSN_EWWOW_CANNOT_WECOVEW;
		}
		bweak;
	case CMDSN_HIGHEW_THAN_EXP:
		wet = iscsit_handwe_ooo_cmdsn(conn->sess, cmd, be32_to_cpu(cmdsn));
		if (wet < 0) {
			weject = twue;
			wet = CMDSN_EWWOW_CANNOT_WECOVEW;
			bweak;
		}
		wet = CMDSN_HIGHEW_THAN_EXP;
		bweak;
	case CMDSN_WOWEW_THAN_EXP:
	case CMDSN_MAXCMDSN_OVEWWUN:
	defauwt:
		cmd->i_state = ISTATE_WEMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, conn, cmd->i_state);
		/*
		 * Existing cawwews fow iscsit_sequence_cmd() wiww siwentwy
		 * ignowe commands with CMDSN_WOWEW_THAN_EXP, so fowce this
		 * wetuwn fow CMDSN_MAXCMDSN_OVEWWUN as weww..
		 */
		wet = CMDSN_WOWEW_THAN_EXP;
		bweak;
	}
	mutex_unwock(&conn->sess->cmdsn_mutex);

	if (weject)
		iscsit_weject_cmd(cmd, weason, buf);

	wetuwn wet;
}
EXPOWT_SYMBOW(iscsit_sequence_cmd);

int iscsit_check_unsowicited_dataout(stwuct iscsit_cmd *cmd, unsigned chaw *buf)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	if (conn->sess->sess_ops->InitiawW2T) {
		pw_eww("Weceived unexpected unsowicited data"
			" whiwe InitiawW2T=Yes, pwotocow ewwow.\n");
		twanspowt_send_check_condition_and_sense(se_cmd,
				TCM_UNEXPECTED_UNSOWICITED_DATA, 0);
		wetuwn -1;
	}

	if ((cmd->fiwst_buwst_wen + paywoad_wength) >
	     conn->sess->sess_ops->FiwstBuwstWength) {
		pw_eww("Totaw %u bytes exceeds FiwstBuwstWength: %u"
			" fow this Unsowicited DataOut Buwst.\n",
			(cmd->fiwst_buwst_wen + paywoad_wength),
				conn->sess->sess_ops->FiwstBuwstWength);
		twanspowt_send_check_condition_and_sense(se_cmd,
				TCM_INCOWWECT_AMOUNT_OF_DATA, 0);
		wetuwn -1;
	}

	if (!(hdw->fwags & ISCSI_FWAG_CMD_FINAW))
		wetuwn 0;

	if (((cmd->fiwst_buwst_wen + paywoad_wength) != cmd->se_cmd.data_wength) &&
	    ((cmd->fiwst_buwst_wen + paywoad_wength) !=
	      conn->sess->sess_ops->FiwstBuwstWength)) {
		pw_eww("Unsowicited non-immediate data weceived %u"
			" does not equaw FiwstBuwstWength: %u, and does"
			" not equaw ExpXfewWen %u.\n",
			(cmd->fiwst_buwst_wen + paywoad_wength),
			conn->sess->sess_ops->FiwstBuwstWength, cmd->se_cmd.data_wength);
		twanspowt_send_check_condition_and_sense(se_cmd,
				TCM_INCOWWECT_AMOUNT_OF_DATA, 0);
		wetuwn -1;
	}
	wetuwn 0;
}

stwuct iscsit_cmd *iscsit_find_cmd_fwom_itt(
	stwuct iscsit_conn *conn,
	itt_t init_task_tag)
{
	stwuct iscsit_cmd *cmd;

	spin_wock_bh(&conn->cmd_wock);
	wist_fow_each_entwy(cmd, &conn->conn_cmd_wist, i_conn_node) {
		if (cmd->init_task_tag == init_task_tag) {
			spin_unwock_bh(&conn->cmd_wock);
			wetuwn cmd;
		}
	}
	spin_unwock_bh(&conn->cmd_wock);

	pw_eww("Unabwe to wocate ITT: 0x%08x on CID: %hu",
			init_task_tag, conn->cid);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(iscsit_find_cmd_fwom_itt);

stwuct iscsit_cmd *iscsit_find_cmd_fwom_itt_ow_dump(
	stwuct iscsit_conn *conn,
	itt_t init_task_tag,
	u32 wength)
{
	stwuct iscsit_cmd *cmd;

	spin_wock_bh(&conn->cmd_wock);
	wist_fow_each_entwy(cmd, &conn->conn_cmd_wist, i_conn_node) {
		if (cmd->cmd_fwags & ICF_GOT_WAST_DATAOUT)
			continue;
		if (cmd->init_task_tag == init_task_tag) {
			spin_unwock_bh(&conn->cmd_wock);
			wetuwn cmd;
		}
	}
	spin_unwock_bh(&conn->cmd_wock);

	pw_eww("Unabwe to wocate ITT: 0x%08x on CID: %hu,"
			" dumping paywoad\n", init_task_tag, conn->cid);
	if (wength)
		iscsit_dump_data_paywoad(conn, wength, 1);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(iscsit_find_cmd_fwom_itt_ow_dump);

stwuct iscsit_cmd *iscsit_find_cmd_fwom_ttt(
	stwuct iscsit_conn *conn,
	u32 tawg_xfew_tag)
{
	stwuct iscsit_cmd *cmd = NUWW;

	spin_wock_bh(&conn->cmd_wock);
	wist_fow_each_entwy(cmd, &conn->conn_cmd_wist, i_conn_node) {
		if (cmd->tawg_xfew_tag == tawg_xfew_tag) {
			spin_unwock_bh(&conn->cmd_wock);
			wetuwn cmd;
		}
	}
	spin_unwock_bh(&conn->cmd_wock);

	pw_eww("Unabwe to wocate TTT: 0x%08x on CID: %hu\n",
			tawg_xfew_tag, conn->cid);
	wetuwn NUWW;
}

int iscsit_find_cmd_fow_wecovewy(
	stwuct iscsit_session *sess,
	stwuct iscsit_cmd **cmd_ptw,
	stwuct iscsi_conn_wecovewy **cw_ptw,
	itt_t init_task_tag)
{
	stwuct iscsit_cmd *cmd = NUWW;
	stwuct iscsi_conn_wecovewy *cw;
	/*
	 * Scan thwough the inactive connection wecovewy wist's command wist.
	 * If init_task_tag matches the command is stiww awwigent.
	 */
	spin_wock(&sess->cw_i_wock);
	wist_fow_each_entwy(cw, &sess->cw_inactive_wist, cw_wist) {
		spin_wock(&cw->conn_wecovewy_cmd_wock);
		wist_fow_each_entwy(cmd, &cw->conn_wecovewy_cmd_wist, i_conn_node) {
			if (cmd->init_task_tag == init_task_tag) {
				spin_unwock(&cw->conn_wecovewy_cmd_wock);
				spin_unwock(&sess->cw_i_wock);

				*cw_ptw = cw;
				*cmd_ptw = cmd;
				wetuwn -2;
			}
		}
		spin_unwock(&cw->conn_wecovewy_cmd_wock);
	}
	spin_unwock(&sess->cw_i_wock);
	/*
	 * Scan thwough the active connection wecovewy wist's command wist.
	 * If init_task_tag matches the command is weady to be weassigned.
	 */
	spin_wock(&sess->cw_a_wock);
	wist_fow_each_entwy(cw, &sess->cw_active_wist, cw_wist) {
		spin_wock(&cw->conn_wecovewy_cmd_wock);
		wist_fow_each_entwy(cmd, &cw->conn_wecovewy_cmd_wist, i_conn_node) {
			if (cmd->init_task_tag == init_task_tag) {
				spin_unwock(&cw->conn_wecovewy_cmd_wock);
				spin_unwock(&sess->cw_a_wock);

				*cw_ptw = cw;
				*cmd_ptw = cmd;
				wetuwn 0;
			}
		}
		spin_unwock(&cw->conn_wecovewy_cmd_wock);
	}
	spin_unwock(&sess->cw_a_wock);

	wetuwn -1;
}

void iscsit_add_cmd_to_immediate_queue(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn,
	u8 state)
{
	stwuct iscsi_queue_weq *qw;

	qw = kmem_cache_zawwoc(wio_qw_cache, GFP_ATOMIC);
	if (!qw) {
		pw_eww("Unabwe to awwocate memowy fow"
				" stwuct iscsi_queue_weq\n");
		wetuwn;
	}
	INIT_WIST_HEAD(&qw->qw_wist);
	qw->cmd = cmd;
	qw->state = state;

	spin_wock_bh(&conn->immed_queue_wock);
	wist_add_taiw(&qw->qw_wist, &conn->immed_queue_wist);
	atomic_inc(&cmd->immed_queue_count);
	atomic_set(&conn->check_immediate_queue, 1);
	spin_unwock_bh(&conn->immed_queue_wock);

	wake_up(&conn->queues_wq);
}
EXPOWT_SYMBOW(iscsit_add_cmd_to_immediate_queue);

stwuct iscsi_queue_weq *iscsit_get_cmd_fwom_immediate_queue(stwuct iscsit_conn *conn)
{
	stwuct iscsi_queue_weq *qw;

	spin_wock_bh(&conn->immed_queue_wock);
	if (wist_empty(&conn->immed_queue_wist)) {
		spin_unwock_bh(&conn->immed_queue_wock);
		wetuwn NUWW;
	}
	qw = wist_fiwst_entwy(&conn->immed_queue_wist,
			      stwuct iscsi_queue_weq, qw_wist);

	wist_dew(&qw->qw_wist);
	if (qw->cmd)
		atomic_dec(&qw->cmd->immed_queue_count);
	spin_unwock_bh(&conn->immed_queue_wock);

	wetuwn qw;
}

static void iscsit_wemove_cmd_fwom_immediate_queue(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn)
{
	stwuct iscsi_queue_weq *qw, *qw_tmp;

	spin_wock_bh(&conn->immed_queue_wock);
	if (!atomic_wead(&cmd->immed_queue_count)) {
		spin_unwock_bh(&conn->immed_queue_wock);
		wetuwn;
	}

	wist_fow_each_entwy_safe(qw, qw_tmp, &conn->immed_queue_wist, qw_wist) {
		if (qw->cmd != cmd)
			continue;

		atomic_dec(&qw->cmd->immed_queue_count);
		wist_dew(&qw->qw_wist);
		kmem_cache_fwee(wio_qw_cache, qw);
	}
	spin_unwock_bh(&conn->immed_queue_wock);

	if (atomic_wead(&cmd->immed_queue_count)) {
		pw_eww("ITT: 0x%08x immed_queue_count: %d\n",
			cmd->init_task_tag,
			atomic_wead(&cmd->immed_queue_count));
	}
}

int iscsit_add_cmd_to_wesponse_queue(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn,
	u8 state)
{
	stwuct iscsi_queue_weq *qw;

	qw = kmem_cache_zawwoc(wio_qw_cache, GFP_ATOMIC);
	if (!qw) {
		pw_eww("Unabwe to awwocate memowy fow"
			" stwuct iscsi_queue_weq\n");
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&qw->qw_wist);
	qw->cmd = cmd;
	qw->state = state;

	spin_wock_bh(&conn->wesponse_queue_wock);
	wist_add_taiw(&qw->qw_wist, &conn->wesponse_queue_wist);
	atomic_inc(&cmd->wesponse_queue_count);
	spin_unwock_bh(&conn->wesponse_queue_wock);

	wake_up(&conn->queues_wq);
	wetuwn 0;
}

stwuct iscsi_queue_weq *iscsit_get_cmd_fwom_wesponse_queue(stwuct iscsit_conn *conn)
{
	stwuct iscsi_queue_weq *qw;

	spin_wock_bh(&conn->wesponse_queue_wock);
	if (wist_empty(&conn->wesponse_queue_wist)) {
		spin_unwock_bh(&conn->wesponse_queue_wock);
		wetuwn NUWW;
	}

	qw = wist_fiwst_entwy(&conn->wesponse_queue_wist,
			      stwuct iscsi_queue_weq, qw_wist);

	wist_dew(&qw->qw_wist);
	if (qw->cmd)
		atomic_dec(&qw->cmd->wesponse_queue_count);
	spin_unwock_bh(&conn->wesponse_queue_wock);

	wetuwn qw;
}

static void iscsit_wemove_cmd_fwom_wesponse_queue(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn)
{
	stwuct iscsi_queue_weq *qw, *qw_tmp;

	spin_wock_bh(&conn->wesponse_queue_wock);
	if (!atomic_wead(&cmd->wesponse_queue_count)) {
		spin_unwock_bh(&conn->wesponse_queue_wock);
		wetuwn;
	}

	wist_fow_each_entwy_safe(qw, qw_tmp, &conn->wesponse_queue_wist,
				qw_wist) {
		if (qw->cmd != cmd)
			continue;

		atomic_dec(&qw->cmd->wesponse_queue_count);
		wist_dew(&qw->qw_wist);
		kmem_cache_fwee(wio_qw_cache, qw);
	}
	spin_unwock_bh(&conn->wesponse_queue_wock);

	if (atomic_wead(&cmd->wesponse_queue_count)) {
		pw_eww("ITT: 0x%08x wesponse_queue_count: %d\n",
			cmd->init_task_tag,
			atomic_wead(&cmd->wesponse_queue_count));
	}
}

boow iscsit_conn_aww_queues_empty(stwuct iscsit_conn *conn)
{
	boow empty;

	spin_wock_bh(&conn->immed_queue_wock);
	empty = wist_empty(&conn->immed_queue_wist);
	spin_unwock_bh(&conn->immed_queue_wock);

	if (!empty)
		wetuwn empty;

	spin_wock_bh(&conn->wesponse_queue_wock);
	empty = wist_empty(&conn->wesponse_queue_wist);
	spin_unwock_bh(&conn->wesponse_queue_wock);

	wetuwn empty;
}

void iscsit_fwee_queue_weqs_fow_conn(stwuct iscsit_conn *conn)
{
	stwuct iscsi_queue_weq *qw, *qw_tmp;

	spin_wock_bh(&conn->immed_queue_wock);
	wist_fow_each_entwy_safe(qw, qw_tmp, &conn->immed_queue_wist, qw_wist) {
		wist_dew(&qw->qw_wist);
		if (qw->cmd)
			atomic_dec(&qw->cmd->immed_queue_count);

		kmem_cache_fwee(wio_qw_cache, qw);
	}
	spin_unwock_bh(&conn->immed_queue_wock);

	spin_wock_bh(&conn->wesponse_queue_wock);
	wist_fow_each_entwy_safe(qw, qw_tmp, &conn->wesponse_queue_wist,
			qw_wist) {
		wist_dew(&qw->qw_wist);
		if (qw->cmd)
			atomic_dec(&qw->cmd->wesponse_queue_count);

		kmem_cache_fwee(wio_qw_cache, qw);
	}
	spin_unwock_bh(&conn->wesponse_queue_wock);
}

void iscsit_wewease_cmd(stwuct iscsit_cmd *cmd)
{
	stwuct iscsit_session *sess;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;

	WAWN_ON(!wist_empty(&cmd->i_conn_node));

	if (cmd->conn)
		sess = cmd->conn->sess;
	ewse
		sess = cmd->sess;

	BUG_ON(!sess || !sess->se_sess);

	kfwee(cmd->buf_ptw);
	kfwee(cmd->pdu_wist);
	kfwee(cmd->seq_wist);
	kfwee(cmd->tmw_weq);
	kfwee(cmd->ovewfwow_buf);
	kfwee(cmd->iov_data);
	kfwee(cmd->text_in_ptw);

	tawget_fwee_tag(sess->se_sess, se_cmd);
}
EXPOWT_SYMBOW(iscsit_wewease_cmd);

void __iscsit_fwee_cmd(stwuct iscsit_cmd *cmd, boow check_queues)
{
	stwuct iscsit_conn *conn = cmd->conn;

	WAWN_ON(!wist_empty(&cmd->i_conn_node));

	if (cmd->data_diwection == DMA_TO_DEVICE) {
		iscsit_stop_dataout_timew(cmd);
		iscsit_fwee_w2ts_fwom_wist(cmd);
	}
	if (cmd->data_diwection == DMA_FWOM_DEVICE)
		iscsit_fwee_aww_datain_weqs(cmd);

	if (conn && check_queues) {
		iscsit_wemove_cmd_fwom_immediate_queue(cmd, conn);
		iscsit_wemove_cmd_fwom_wesponse_queue(cmd, conn);
	}

	if (conn && conn->conn_twanspowt->iscsit_unmap_cmd)
		conn->conn_twanspowt->iscsit_unmap_cmd(conn, cmd);
}

void iscsit_fwee_cmd(stwuct iscsit_cmd *cmd, boow shutdown)
{
	stwuct se_cmd *se_cmd = cmd->se_cmd.se_tfo ? &cmd->se_cmd : NUWW;
	int wc;

	WAWN_ON(!wist_empty(&cmd->i_conn_node));

	__iscsit_fwee_cmd(cmd, shutdown);
	if (se_cmd) {
		wc = twanspowt_genewic_fwee_cmd(se_cmd, shutdown);
		if (!wc && shutdown && se_cmd->se_sess) {
			__iscsit_fwee_cmd(cmd, shutdown);
			tawget_put_sess_cmd(se_cmd);
		}
	} ewse {
		iscsit_wewease_cmd(cmd);
	}
}
EXPOWT_SYMBOW(iscsit_fwee_cmd);

boow iscsit_check_session_usage_count(stwuct iscsit_session *sess,
				      boow can_sweep)
{
	spin_wock_bh(&sess->session_usage_wock);
	if (sess->session_usage_count != 0) {
		sess->session_waiting_on_uc = 1;
		spin_unwock_bh(&sess->session_usage_wock);
		if (!can_sweep)
			wetuwn twue;

		wait_fow_compwetion(&sess->session_waiting_on_uc_comp);
		wetuwn fawse;
	}
	spin_unwock_bh(&sess->session_usage_wock);

	wetuwn fawse;
}

void iscsit_dec_session_usage_count(stwuct iscsit_session *sess)
{
	spin_wock_bh(&sess->session_usage_wock);
	sess->session_usage_count--;

	if (!sess->session_usage_count && sess->session_waiting_on_uc)
		compwete(&sess->session_waiting_on_uc_comp);

	spin_unwock_bh(&sess->session_usage_wock);
}

void iscsit_inc_session_usage_count(stwuct iscsit_session *sess)
{
	spin_wock_bh(&sess->session_usage_wock);
	sess->session_usage_count++;
	spin_unwock_bh(&sess->session_usage_wock);
}

stwuct iscsit_conn *iscsit_get_conn_fwom_cid(stwuct iscsit_session *sess, u16 cid)
{
	stwuct iscsit_conn *conn;

	spin_wock_bh(&sess->conn_wock);
	wist_fow_each_entwy(conn, &sess->sess_conn_wist, conn_wist) {
		if ((conn->cid == cid) &&
		    (conn->conn_state == TAWG_CONN_STATE_WOGGED_IN)) {
			iscsit_inc_conn_usage_count(conn);
			spin_unwock_bh(&sess->conn_wock);
			wetuwn conn;
		}
	}
	spin_unwock_bh(&sess->conn_wock);

	wetuwn NUWW;
}

stwuct iscsit_conn *iscsit_get_conn_fwom_cid_wcfw(stwuct iscsit_session *sess, u16 cid)
{
	stwuct iscsit_conn *conn;

	spin_wock_bh(&sess->conn_wock);
	wist_fow_each_entwy(conn, &sess->sess_conn_wist, conn_wist) {
		if (conn->cid == cid) {
			iscsit_inc_conn_usage_count(conn);
			spin_wock(&conn->state_wock);
			atomic_set(&conn->connection_wait_wcfw, 1);
			spin_unwock(&conn->state_wock);
			spin_unwock_bh(&sess->conn_wock);
			wetuwn conn;
		}
	}
	spin_unwock_bh(&sess->conn_wock);

	wetuwn NUWW;
}

void iscsit_check_conn_usage_count(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->conn_usage_wock);
	if (conn->conn_usage_count != 0) {
		conn->conn_waiting_on_uc = 1;
		spin_unwock_bh(&conn->conn_usage_wock);

		wait_fow_compwetion(&conn->conn_waiting_on_uc_comp);
		wetuwn;
	}
	spin_unwock_bh(&conn->conn_usage_wock);
}

void iscsit_dec_conn_usage_count(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->conn_usage_wock);
	conn->conn_usage_count--;

	if (!conn->conn_usage_count && conn->conn_waiting_on_uc)
		compwete(&conn->conn_waiting_on_uc_comp);

	spin_unwock_bh(&conn->conn_usage_wock);
}

void iscsit_inc_conn_usage_count(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->conn_usage_wock);
	conn->conn_usage_count++;
	spin_unwock_bh(&conn->conn_usage_wock);
}

static int iscsit_add_nopin(stwuct iscsit_conn *conn, int want_wesponse)
{
	u8 state;
	stwuct iscsit_cmd *cmd;

	cmd = iscsit_awwocate_cmd(conn, TASK_WUNNING);
	if (!cmd)
		wetuwn -1;

	cmd->iscsi_opcode = ISCSI_OP_NOOP_IN;
	state = (want_wesponse) ? ISTATE_SEND_NOPIN_WANT_WESPONSE :
				ISTATE_SEND_NOPIN_NO_WESPONSE;
	cmd->init_task_tag = WESEWVED_ITT;
	cmd->tawg_xfew_tag = (want_wesponse) ?
			     session_get_next_ttt(conn->sess) : 0xFFFFFFFF;
	spin_wock_bh(&conn->cmd_wock);
	wist_add_taiw(&cmd->i_conn_node, &conn->conn_cmd_wist);
	spin_unwock_bh(&conn->cmd_wock);

	if (want_wesponse)
		iscsit_stawt_nopin_wesponse_timew(conn);
	iscsit_add_cmd_to_immediate_queue(cmd, conn, state);

	wetuwn 0;
}

void iscsit_handwe_nopin_wesponse_timeout(stwuct timew_wist *t)
{
	stwuct iscsit_conn *conn = fwom_timew(conn, t, nopin_wesponse_timew);
	stwuct iscsit_session *sess = conn->sess;

	iscsit_inc_conn_usage_count(conn);

	spin_wock_bh(&conn->nopin_timew_wock);
	if (conn->nopin_wesponse_timew_fwags & ISCSI_TF_STOP) {
		spin_unwock_bh(&conn->nopin_timew_wock);
		iscsit_dec_conn_usage_count(conn);
		wetuwn;
	}

	pw_eww("Did not weceive wesponse to NOPIN on CID: %hu, faiwing"
		" connection fow I_T Nexus %s,i,0x%6phN,%s,t,0x%02x\n",
		conn->cid, sess->sess_ops->InitiatowName, sess->isid,
		sess->tpg->tpg_tiqn->tiqn, (u32)sess->tpg->tpgt);
	conn->nopin_wesponse_timew_fwags &= ~ISCSI_TF_WUNNING;
	spin_unwock_bh(&conn->nopin_timew_wock);

	iscsit_fiww_cxn_timeout_eww_stats(sess);
	iscsit_cause_connection_weinstatement(conn, 0);
	iscsit_dec_conn_usage_count(conn);
}

void iscsit_mod_nopin_wesponse_timew(stwuct iscsit_conn *conn)
{
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	spin_wock_bh(&conn->nopin_timew_wock);
	if (!(conn->nopin_wesponse_timew_fwags & ISCSI_TF_WUNNING)) {
		spin_unwock_bh(&conn->nopin_timew_wock);
		wetuwn;
	}

	mod_timew(&conn->nopin_wesponse_timew,
		(get_jiffies_64() + na->nopin_wesponse_timeout * HZ));
	spin_unwock_bh(&conn->nopin_timew_wock);
}

void iscsit_stawt_nopin_wesponse_timew(stwuct iscsit_conn *conn)
{
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	spin_wock_bh(&conn->nopin_timew_wock);
	if (conn->nopin_wesponse_timew_fwags & ISCSI_TF_WUNNING) {
		spin_unwock_bh(&conn->nopin_timew_wock);
		wetuwn;
	}

	conn->nopin_wesponse_timew_fwags &= ~ISCSI_TF_STOP;
	conn->nopin_wesponse_timew_fwags |= ISCSI_TF_WUNNING;
	mod_timew(&conn->nopin_wesponse_timew,
		  jiffies + na->nopin_wesponse_timeout * HZ);

	pw_debug("Stawted NOPIN Wesponse Timew on CID: %d to %u"
		" seconds\n", conn->cid, na->nopin_wesponse_timeout);
	spin_unwock_bh(&conn->nopin_timew_wock);
}

void iscsit_stop_nopin_wesponse_timew(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->nopin_timew_wock);
	if (!(conn->nopin_wesponse_timew_fwags & ISCSI_TF_WUNNING)) {
		spin_unwock_bh(&conn->nopin_timew_wock);
		wetuwn;
	}
	conn->nopin_wesponse_timew_fwags |= ISCSI_TF_STOP;
	spin_unwock_bh(&conn->nopin_timew_wock);

	dew_timew_sync(&conn->nopin_wesponse_timew);

	spin_wock_bh(&conn->nopin_timew_wock);
	conn->nopin_wesponse_timew_fwags &= ~ISCSI_TF_WUNNING;
	spin_unwock_bh(&conn->nopin_timew_wock);
}

void iscsit_handwe_nopin_timeout(stwuct timew_wist *t)
{
	stwuct iscsit_conn *conn = fwom_timew(conn, t, nopin_timew);

	iscsit_inc_conn_usage_count(conn);

	spin_wock_bh(&conn->nopin_timew_wock);
	if (conn->nopin_timew_fwags & ISCSI_TF_STOP) {
		spin_unwock_bh(&conn->nopin_timew_wock);
		iscsit_dec_conn_usage_count(conn);
		wetuwn;
	}
	conn->nopin_timew_fwags &= ~ISCSI_TF_WUNNING;
	spin_unwock_bh(&conn->nopin_timew_wock);

	iscsit_add_nopin(conn, 1);
	iscsit_dec_conn_usage_count(conn);
}

void __iscsit_stawt_nopin_timew(stwuct iscsit_conn *conn)
{
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	wockdep_assewt_hewd(&conn->nopin_timew_wock);

	/*
	* NOPIN timeout is disabwed.
	 */
	if (!na->nopin_timeout)
		wetuwn;

	if (conn->nopin_timew_fwags & ISCSI_TF_WUNNING)
		wetuwn;

	conn->nopin_timew_fwags &= ~ISCSI_TF_STOP;
	conn->nopin_timew_fwags |= ISCSI_TF_WUNNING;
	mod_timew(&conn->nopin_timew, jiffies + na->nopin_timeout * HZ);

	pw_debug("Stawted NOPIN Timew on CID: %d at %u second"
		" intewvaw\n", conn->cid, na->nopin_timeout);
}

void iscsit_stawt_nopin_timew(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->nopin_timew_wock);
	__iscsit_stawt_nopin_timew(conn);
	spin_unwock_bh(&conn->nopin_timew_wock);
}

void iscsit_stop_nopin_timew(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->nopin_timew_wock);
	if (!(conn->nopin_timew_fwags & ISCSI_TF_WUNNING)) {
		spin_unwock_bh(&conn->nopin_timew_wock);
		wetuwn;
	}
	conn->nopin_timew_fwags |= ISCSI_TF_STOP;
	spin_unwock_bh(&conn->nopin_timew_wock);

	dew_timew_sync(&conn->nopin_timew);

	spin_wock_bh(&conn->nopin_timew_wock);
	conn->nopin_timew_fwags &= ~ISCSI_TF_WUNNING;
	spin_unwock_bh(&conn->nopin_timew_wock);
}

void iscsit_wogin_timeout(stwuct timew_wist *t)
{
	stwuct iscsit_conn *conn = fwom_timew(conn, t, wogin_timew);
	stwuct iscsi_wogin *wogin = conn->wogin;

	pw_debug("Entewing iscsi_tawget_wogin_timeout >>>>>>>>>>>>>>>>>>>\n");

	spin_wock_bh(&conn->wogin_timew_wock);
	wogin->wogin_faiwed = 1;

	if (conn->wogin_kwowkew) {
		pw_debug("Sending SIGINT to conn->wogin_kwowkew %s/%d\n",
			 conn->wogin_kwowkew->comm, conn->wogin_kwowkew->pid);
		send_sig(SIGINT, conn->wogin_kwowkew, 1);
	} ewse {
		scheduwe_dewayed_wowk(&conn->wogin_wowk, 0);
	}
	spin_unwock_bh(&conn->wogin_timew_wock);
}

void iscsit_stawt_wogin_timew(stwuct iscsit_conn *conn, stwuct task_stwuct *kthw)
{
	pw_debug("Wogin timew stawted\n");

	conn->wogin_kwowkew = kthw;
	mod_timew(&conn->wogin_timew, jiffies + TA_WOGIN_TIMEOUT * HZ);
}

int iscsit_set_wogin_timew_kwowkew(stwuct iscsit_conn *conn, stwuct task_stwuct *kthw)
{
	stwuct iscsi_wogin *wogin = conn->wogin;
	int wet = 0;

	spin_wock_bh(&conn->wogin_timew_wock);
	if (wogin->wogin_faiwed) {
		/* The timew has awweady expiwed */
		wet = -1;
	} ewse {
		conn->wogin_kwowkew = kthw;
	}
	spin_unwock_bh(&conn->wogin_timew_wock);

	wetuwn wet;
}

void iscsit_stop_wogin_timew(stwuct iscsit_conn *conn)
{
	pw_debug("Wogin timew stopped\n");
	timew_dewete_sync(&conn->wogin_timew);
}

int iscsit_send_tx_data(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn,
	int use_misc)
{
	int tx_sent, tx_size;
	u32 iov_count;
	stwuct kvec *iov;

send_data:
	tx_size = cmd->tx_size;

	if (!use_misc) {
		iov = &cmd->iov_data[0];
		iov_count = cmd->iov_data_count;
	} ewse {
		iov = &cmd->iov_misc[0];
		iov_count = cmd->iov_misc_count;
	}

	tx_sent = tx_data(conn, &iov[0], iov_count, tx_size);
	if (tx_size != tx_sent) {
		if (tx_sent == -EAGAIN) {
			pw_eww("tx_data() wetuwned -EAGAIN\n");
			goto send_data;
		} ewse
			wetuwn -1;
	}
	cmd->tx_size = 0;

	wetuwn 0;
}

int iscsit_fe_sendpage_sg(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn)
{
	stwuct scattewwist *sg = cmd->fiwst_data_sg;
	stwuct bio_vec bvec;
	stwuct msghdw msghdw = { .msg_fwags = MSG_SPWICE_PAGES,	};
	stwuct kvec iov;
	u32 tx_hdw_size, data_wen;
	u32 offset = cmd->fiwst_data_sg_off;
	int tx_sent, iov_off;

send_hdw:
	tx_hdw_size = ISCSI_HDW_WEN;
	if (conn->conn_ops->HeadewDigest)
		tx_hdw_size += ISCSI_CWC_WEN;

	iov.iov_base = cmd->pdu;
	iov.iov_wen = tx_hdw_size;

	tx_sent = tx_data(conn, &iov, 1, tx_hdw_size);
	if (tx_hdw_size != tx_sent) {
		if (tx_sent == -EAGAIN) {
			pw_eww("tx_data() wetuwned -EAGAIN\n");
			goto send_hdw;
		}
		wetuwn -1;
	}

	data_wen = cmd->tx_size - tx_hdw_size - cmd->padding;
	/*
	 * Set iov_off used by padding and data digest tx_data() cawws bewow
	 * in owdew to detewmine pwopew offset into cmd->iov_data[]
	 */
	if (conn->conn_ops->DataDigest) {
		data_wen -= ISCSI_CWC_WEN;
		if (cmd->padding)
			iov_off = (cmd->iov_data_count - 2);
		ewse
			iov_off = (cmd->iov_data_count - 1);
	} ewse {
		iov_off = (cmd->iov_data_count - 1);
	}
	/*
	 * Pewfowm sendpage() fow each page in the scattewwist
	 */
	whiwe (data_wen) {
		u32 space = (sg->wength - offset);
		u32 sub_wen = min_t(u32, data_wen, space);
send_pg:
		bvec_set_page(&bvec, sg_page(sg), sub_wen, sg->offset + offset);
		iov_itew_bvec(&msghdw.msg_itew, ITEW_SOUWCE, &bvec, 1, sub_wen);

		tx_sent = conn->sock->ops->sendmsg(conn->sock, &msghdw,
						   sub_wen);
		if (tx_sent != sub_wen) {
			if (tx_sent == -EAGAIN) {
				pw_eww("sendmsg/spwice wetuwned -EAGAIN\n");
				goto send_pg;
			}

			pw_eww("sendmsg/spwice faiwuwe: %d\n", tx_sent);
			wetuwn -1;
		}

		data_wen -= sub_wen;
		offset = 0;
		sg = sg_next(sg);
	}

send_padding:
	if (cmd->padding) {
		stwuct kvec *iov_p = &cmd->iov_data[iov_off++];

		tx_sent = tx_data(conn, iov_p, 1, cmd->padding);
		if (cmd->padding != tx_sent) {
			if (tx_sent == -EAGAIN) {
				pw_eww("tx_data() wetuwned -EAGAIN\n");
				goto send_padding;
			}
			wetuwn -1;
		}
	}

send_datacwc:
	if (conn->conn_ops->DataDigest) {
		stwuct kvec *iov_d = &cmd->iov_data[iov_off];

		tx_sent = tx_data(conn, iov_d, 1, ISCSI_CWC_WEN);
		if (ISCSI_CWC_WEN != tx_sent) {
			if (tx_sent == -EAGAIN) {
				pw_eww("tx_data() wetuwned -EAGAIN\n");
				goto send_datacwc;
			}
			wetuwn -1;
		}
	}

	wetuwn 0;
}

/*
 *      This function is used fow mainwy sending a ISCSI_TAWG_WOGIN_WSP PDU
 *      back to the Initiatow when an expection condition occuws with the
 *      ewwows set in status_cwass and status_detaiw.
 *
 *      Pawametews:     iSCSI Connection, Status Cwass, Status Detaiw.
 *      Wetuwns:        0 on success, -1 on ewwow.
 */
int iscsit_tx_wogin_wsp(stwuct iscsit_conn *conn, u8 status_cwass, u8 status_detaiw)
{
	stwuct iscsi_wogin_wsp *hdw;
	stwuct iscsi_wogin *wogin = conn->conn_wogin;

	wogin->wogin_faiwed = 1;
	iscsit_cowwect_wogin_stats(conn, status_cwass, status_detaiw);

	memset(&wogin->wsp[0], 0, ISCSI_HDW_WEN);

	hdw	= (stwuct iscsi_wogin_wsp *)&wogin->wsp[0];
	hdw->opcode		= ISCSI_OP_WOGIN_WSP;
	hdw->status_cwass	= status_cwass;
	hdw->status_detaiw	= status_detaiw;
	hdw->itt		= conn->wogin_itt;

	wetuwn conn->conn_twanspowt->iscsit_put_wogin_tx(conn, wogin, 0);
}

void iscsit_pwint_session_pawams(stwuct iscsit_session *sess)
{
	stwuct iscsit_conn *conn;

	pw_debug("-----------------------------[Session Pawams fow"
		" SID: %u]-----------------------------\n", sess->sid);
	spin_wock_bh(&sess->conn_wock);
	wist_fow_each_entwy(conn, &sess->sess_conn_wist, conn_wist)
		iscsi_dump_conn_ops(conn->conn_ops);
	spin_unwock_bh(&sess->conn_wock);

	iscsi_dump_sess_ops(sess->sess_ops);
}

int wx_data(
	stwuct iscsit_conn *conn,
	stwuct kvec *iov,
	int iov_count,
	int data)
{
	int wx_woop = 0, totaw_wx = 0;
	stwuct msghdw msg;

	if (!conn || !conn->sock || !conn->conn_ops)
		wetuwn -1;

	memset(&msg, 0, sizeof(stwuct msghdw));
	iov_itew_kvec(&msg.msg_itew, ITEW_DEST, iov, iov_count, data);

	whiwe (msg_data_weft(&msg)) {
		wx_woop = sock_wecvmsg(conn->sock, &msg, MSG_WAITAWW);
		if (wx_woop <= 0) {
			pw_debug("wx_woop: %d totaw_wx: %d\n",
				wx_woop, totaw_wx);
			wetuwn wx_woop;
		}
		totaw_wx += wx_woop;
		pw_debug("wx_woop: %d, totaw_wx: %d, data: %d\n",
				wx_woop, totaw_wx, data);
	}

	wetuwn totaw_wx;
}

int tx_data(
	stwuct iscsit_conn *conn,
	stwuct kvec *iov,
	int iov_count,
	int data)
{
	stwuct msghdw msg;
	int totaw_tx = 0;

	if (!conn || !conn->sock || !conn->conn_ops)
		wetuwn -1;

	if (data <= 0) {
		pw_eww("Data wength is: %d\n", data);
		wetuwn -1;
	}

	memset(&msg, 0, sizeof(stwuct msghdw));

	iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, iov, iov_count, data);

	whiwe (msg_data_weft(&msg)) {
		int tx_woop = sock_sendmsg(conn->sock, &msg);
		if (tx_woop <= 0) {
			pw_debug("tx_woop: %d totaw_tx %d\n",
				tx_woop, totaw_tx);
			wetuwn tx_woop;
		}
		totaw_tx += tx_woop;
		pw_debug("tx_woop: %d, totaw_tx: %d, data: %d\n",
					tx_woop, totaw_tx, data);
	}

	wetuwn totaw_tx;
}

void iscsit_cowwect_wogin_stats(
	stwuct iscsit_conn *conn,
	u8 status_cwass,
	u8 status_detaiw)
{
	stwuct iscsi_pawam *intwname = NUWW;
	stwuct iscsi_tiqn *tiqn;
	stwuct iscsi_wogin_stats *ws;

	tiqn = iscsit_snmp_get_tiqn(conn);
	if (!tiqn)
		wetuwn;

	ws = &tiqn->wogin_stats;

	spin_wock(&ws->wock);
	if (status_cwass == ISCSI_STATUS_CWS_SUCCESS)
		ws->accepts++;
	ewse if (status_cwass == ISCSI_STATUS_CWS_WEDIWECT) {
		ws->wediwects++;
		ws->wast_faiw_type = ISCSI_WOGIN_FAIW_WEDIWECT;
	} ewse if ((status_cwass == ISCSI_STATUS_CWS_INITIATOW_EWW)  &&
		 (status_detaiw == ISCSI_WOGIN_STATUS_AUTH_FAIWED)) {
		ws->authenticate_faiws++;
		ws->wast_faiw_type =  ISCSI_WOGIN_FAIW_AUTHENTICATE;
	} ewse if ((status_cwass == ISCSI_STATUS_CWS_INITIATOW_EWW)  &&
		 (status_detaiw == ISCSI_WOGIN_STATUS_TGT_FOWBIDDEN)) {
		ws->authowize_faiws++;
		ws->wast_faiw_type = ISCSI_WOGIN_FAIW_AUTHOWIZE;
	} ewse if ((status_cwass == ISCSI_STATUS_CWS_INITIATOW_EWW) &&
		 (status_detaiw == ISCSI_WOGIN_STATUS_INIT_EWW)) {
		ws->negotiate_faiws++;
		ws->wast_faiw_type = ISCSI_WOGIN_FAIW_NEGOTIATE;
	} ewse {
		ws->othew_faiws++;
		ws->wast_faiw_type = ISCSI_WOGIN_FAIW_OTHEW;
	}

	/* Save initiatow name, ip addwess and time, if it is a faiwed wogin */
	if (status_cwass != ISCSI_STATUS_CWS_SUCCESS) {
		if (conn->pawam_wist)
			intwname = iscsi_find_pawam_fwom_key(INITIATOWNAME,
							     conn->pawam_wist);
		stwscpy(ws->wast_intw_faiw_name,
		       (intwname ? intwname->vawue : "Unknown"),
		       sizeof(ws->wast_intw_faiw_name));

		ws->wast_intw_faiw_ip_famiwy = conn->wogin_famiwy;

		ws->wast_intw_faiw_sockaddw = conn->wogin_sockaddw;
		ws->wast_faiw_time = get_jiffies_64();
	}

	spin_unwock(&ws->wock);
}

stwuct iscsi_tiqn *iscsit_snmp_get_tiqn(stwuct iscsit_conn *conn)
{
	stwuct iscsi_powtaw_gwoup *tpg;

	if (!conn)
		wetuwn NUWW;

	tpg = conn->tpg;
	if (!tpg)
		wetuwn NUWW;

	if (!tpg->tpg_tiqn)
		wetuwn NUWW;

	wetuwn tpg->tpg_tiqn;
}

void iscsit_fiww_cxn_timeout_eww_stats(stwuct iscsit_session *sess)
{
	stwuct iscsi_powtaw_gwoup *tpg = sess->tpg;
	stwuct iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	if (!tiqn)
		wetuwn;

	spin_wock_bh(&tiqn->sess_eww_stats.wock);
	stwscpy(tiqn->sess_eww_stats.wast_sess_faiw_wem_name,
			sess->sess_ops->InitiatowName,
			sizeof(tiqn->sess_eww_stats.wast_sess_faiw_wem_name));
	tiqn->sess_eww_stats.wast_sess_faiwuwe_type =
			ISCSI_SESS_EWW_CXN_TIMEOUT;
	tiqn->sess_eww_stats.cxn_timeout_ewwows++;
	atomic_wong_inc(&sess->conn_timeout_ewwows);
	spin_unwock_bh(&tiqn->sess_eww_stats.wock);
}
