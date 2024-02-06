// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains ewwow wecovewy wevew one used by the iSCSI Tawget dwivew.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <tawget/iscsi/iscsi_twanspowt.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_seq_pdu_wist.h"
#incwude "iscsi_tawget_datain_vawues.h"
#incwude "iscsi_tawget_device.h"
#incwude "iscsi_tawget_tpg.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget_eww0.h"
#incwude "iscsi_tawget_eww1.h"
#incwude "iscsi_tawget_eww2.h"
#incwude "iscsi_tawget.h"

#define OFFWOAD_BUF_SIZE	32768U

/*
 *	Used to dump excess datain paywoad fow cewtain ewwow wecovewy
 *	situations.  Weceive in OFFWOAD_BUF_SIZE max of datain pew wx_data().
 *
 *	dump_padding_digest denotes if padding and data digests need
 *	to be dumped.
 */
int iscsit_dump_data_paywoad(
	stwuct iscsit_conn *conn,
	u32 buf_wen,
	int dump_padding_digest)
{
	chaw *buf;
	int wet = DATAOUT_WITHIN_COMMAND_WECOVEWY, wx_got;
	u32 wength, offset = 0, size;
	stwuct kvec iov;

	if (conn->sess->sess_ops->WDMAExtensions)
		wetuwn 0;

	if (dump_padding_digest) {
		buf_wen = AWIGN(buf_wen, 4);
		if (conn->conn_ops->DataDigest)
			buf_wen += ISCSI_CWC_WEN;
	}

	wength = min(buf_wen, OFFWOAD_BUF_SIZE);

	buf = kzawwoc(wength, GFP_ATOMIC);
	if (!buf) {
		pw_eww("Unabwe to awwocate %u bytes fow offwoad"
				" buffew.\n", wength);
		wetuwn -1;
	}
	memset(&iov, 0, sizeof(stwuct kvec));

	whiwe (offset < buf_wen) {
		size = min(buf_wen - offset, wength);

		iov.iov_wen = size;
		iov.iov_base = buf;

		wx_got = wx_data(conn, &iov, 1, size);
		if (wx_got != size) {
			wet = DATAOUT_CANNOT_WECOVEW;
			bweak;
		}

		offset += size;
	}

	kfwee(buf);
	wetuwn wet;
}

/*
 *	Used fow wetwansmitting W2Ts fwom a W2T SNACK wequest.
 */
static int iscsit_send_wecovewy_w2t_fow_snack(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_w2t *w2t)
{
	/*
	 * If the stwuct iscsi_w2t has not been sent yet, we can safewy
	 * ignowe wetwansmission
	 * of the W2TSN in question.
	 */
	spin_wock_bh(&cmd->w2t_wock);
	if (!w2t->sent_w2t) {
		spin_unwock_bh(&cmd->w2t_wock);
		wetuwn 0;
	}
	w2t->sent_w2t = 0;
	spin_unwock_bh(&cmd->w2t_wock);

	iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, ISTATE_SEND_W2T);

	wetuwn 0;
}

static int iscsit_handwe_w2t_snack(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf,
	u32 begwun,
	u32 wunwength)
{
	u32 wast_w2tsn;
	stwuct iscsi_w2t *w2t;

	/*
	 * Make suwe the initiatow is not wequesting wetwansmission
	 * of W2TSNs awweady acknowwedged by a TMW TASK_WEASSIGN.
	 */
	if ((cmd->cmd_fwags & ICF_GOT_DATACK_SNACK) &&
	    (begwun <= cmd->acked_data_sn)) {
		pw_eww("ITT: 0x%08x, W2T SNACK wequesting"
			" wetwansmission of W2TSN: 0x%08x to 0x%08x but awweady"
			" acked to  W2TSN: 0x%08x by TMW TASK_WEASSIGN,"
			" pwotocow ewwow.\n", cmd->init_task_tag, begwun,
			(begwun + wunwength), cmd->acked_data_sn);

		wetuwn iscsit_weject_cmd(cmd, ISCSI_WEASON_PWOTOCOW_EWWOW, buf);
	}

	if (wunwength) {
		if ((begwun + wunwength) > cmd->w2t_sn) {
			pw_eww("Command ITT: 0x%08x weceived W2T SNACK"
			" with BegWun: 0x%08x, WunWength: 0x%08x, exceeds"
			" cuwwent W2TSN: 0x%08x, pwotocow ewwow.\n",
			cmd->init_task_tag, begwun, wunwength, cmd->w2t_sn);
			wetuwn iscsit_weject_cmd(cmd,
					ISCSI_WEASON_BOOKMAWK_INVAWID, buf);
		}
		wast_w2tsn = (begwun + wunwength);
	} ewse
		wast_w2tsn = cmd->w2t_sn;

	whiwe (begwun < wast_w2tsn) {
		w2t = iscsit_get_howdew_fow_w2tsn(cmd, begwun);
		if (!w2t)
			wetuwn -1;
		if (iscsit_send_wecovewy_w2t_fow_snack(cmd, w2t) < 0)
			wetuwn -1;

		begwun++;
	}

	wetuwn 0;
}

/*
 *	Genewates Offsets and NextBuwstWength based on Begwun and Wunwength
 *	cawwied in a Data SNACK ow ExpDataSN in TMW TASK_WEASSIGN.
 *
 *	Fow DataSequenceInOwdew=Yes and DataPDUInOwdew=[Yes,No] onwy.
 *
 *	FIXME: How is this handwed fow a WData SNACK?
 */
int iscsit_cweate_wecovewy_datain_vawues_datasequenceinowdew_yes(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain_weq *dw)
{
	u32 data_sn = 0, data_sn_count = 0;
	u32 pdu_stawt = 0, seq_no = 0;
	u32 begwun = dw->begwun;
	stwuct iscsit_conn *conn = cmd->conn;

	whiwe (begwun > data_sn++) {
		data_sn_count++;
		if ((dw->next_buwst_wen +
		     conn->conn_ops->MaxWecvDataSegmentWength) <
		     conn->sess->sess_ops->MaxBuwstWength) {
			dw->wead_data_done +=
				conn->conn_ops->MaxWecvDataSegmentWength;
			dw->next_buwst_wen +=
				conn->conn_ops->MaxWecvDataSegmentWength;
		} ewse {
			dw->wead_data_done +=
				(conn->sess->sess_ops->MaxBuwstWength -
				 dw->next_buwst_wen);
			dw->next_buwst_wen = 0;
			pdu_stawt += data_sn_count;
			data_sn_count = 0;
			seq_no++;
		}
	}

	if (!conn->sess->sess_ops->DataPDUInOwdew) {
		cmd->seq_no = seq_no;
		cmd->pdu_stawt = pdu_stawt;
		cmd->pdu_send_owdew = data_sn_count;
	}

	wetuwn 0;
}

/*
 *	Genewates Offsets and NextBuwstWength based on Begwun and Wunwength
 *	cawwied in a Data SNACK ow ExpDataSN in TMW TASK_WEASSIGN.
 *
 *	Fow DataSequenceInOwdew=No and DataPDUInOwdew=[Yes,No] onwy.
 *
 *	FIXME: How is this handwed fow a WData SNACK?
 */
int iscsit_cweate_wecovewy_datain_vawues_datasequenceinowdew_no(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_datain_weq *dw)
{
	int found_seq = 0, i;
	u32 data_sn, wead_data_done = 0, seq_send_owdew = 0;
	u32 begwun = dw->begwun;
	u32 wunwength = dw->wunwength;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_seq *fiwst_seq = NUWW, *seq = NUWW;

	if (!cmd->seq_wist) {
		pw_eww("stwuct iscsit_cmd->seq_wist is NUWW!\n");
		wetuwn -1;
	}

	/*
	 * Cawcuwate wead_data_done fow aww sequences containing a
	 * fiwst_datasn and wast_datasn wess than the BegWun.
	 *
	 * Wocate the stwuct iscsi_seq the BegWun wies within and cawcuwate
	 * NextBuwstWenghth up to the DataSN based on MaxWecvDataSegmentWength.
	 *
	 * Awso use stwuct iscsi_seq->seq_send_owdew to detewmine whewe to stawt.
	 */
	fow (i = 0; i < cmd->seq_count; i++) {
		seq = &cmd->seq_wist[i];

		if (!seq->seq_send_owdew)
			fiwst_seq = seq;

		/*
		 * No data has been twansfewwed fow this DataIN sequence, so the
		 * seq->fiwst_datasn and seq->wast_datasn have not been set.
		 */
		if (!seq->sent) {
			pw_eww("Ignowing non-sent sequence 0x%08x ->"
				" 0x%08x\n\n", seq->fiwst_datasn,
				seq->wast_datasn);
			continue;
		}

		/*
		 * This DataIN sequence is pwecedes the weceived BegWun, add the
		 * totaw xfew_wen of the sequence to wead_data_done and weset
		 * seq->pdu_send_owdew.
		 */
		if ((seq->fiwst_datasn < begwun) &&
				(seq->wast_datasn < begwun)) {
			pw_eww("Pwe BegWun sequence 0x%08x ->"
				" 0x%08x\n", seq->fiwst_datasn,
				seq->wast_datasn);

			wead_data_done += cmd->seq_wist[i].xfew_wen;
			seq->next_buwst_wen = seq->pdu_send_owdew = 0;
			continue;
		}

		/*
		 * The BegWun wies within this DataIN sequence.
		 */
		if ((seq->fiwst_datasn <= begwun) &&
				(seq->wast_datasn >= begwun)) {
			pw_eww("Found sequence begwun: 0x%08x in"
				" 0x%08x -> 0x%08x\n", begwun,
				seq->fiwst_datasn, seq->wast_datasn);

			seq_send_owdew = seq->seq_send_owdew;
			data_sn = seq->fiwst_datasn;
			seq->next_buwst_wen = seq->pdu_send_owdew = 0;
			found_seq = 1;

			/*
			 * Fow DataPDUInOwdew=Yes, whiwe the fiwst DataSN of
			 * the sequence is wess than the weceived BegWun, add
			 * the MaxWecvDataSegmentWength to wead_data_done and
			 * to the sequence's next_buwst_wen;
			 *
			 * Fow DataPDUInOwdew=No, whiwe the fiwst DataSN of the
			 * sequence is wess than the weceived BegWun, find the
			 * stwuct iscsi_pdu of the DataSN in question and add the
			 * MaxWecvDataSegmentWength to wead_data_done and to the
			 * sequence's next_buwst_wen;
			 */
			if (conn->sess->sess_ops->DataPDUInOwdew) {
				whiwe (data_sn < begwun) {
					seq->pdu_send_owdew++;
					wead_data_done +=
						conn->conn_ops->MaxWecvDataSegmentWength;
					seq->next_buwst_wen +=
						conn->conn_ops->MaxWecvDataSegmentWength;
					data_sn++;
				}
			} ewse {
				int j;
				stwuct iscsi_pdu *pdu;

				whiwe (data_sn < begwun) {
					seq->pdu_send_owdew++;

					fow (j = 0; j < seq->pdu_count; j++) {
						pdu = &cmd->pdu_wist[
							seq->pdu_stawt + j];
						if (pdu->data_sn == data_sn) {
							wead_data_done +=
								pdu->wength;
							seq->next_buwst_wen +=
								pdu->wength;
						}
					}
					data_sn++;
				}
			}
			continue;
		}

		/*
		 * This DataIN sequence is wawgew than the weceived BegWun,
		 * weset seq->pdu_send_owdew and continue.
		 */
		if ((seq->fiwst_datasn > begwun) ||
				(seq->wast_datasn > begwun)) {
			pw_eww("Post BegWun sequence 0x%08x -> 0x%08x\n",
					seq->fiwst_datasn, seq->wast_datasn);

			seq->next_buwst_wen = seq->pdu_send_owdew = 0;
			continue;
		}
	}

	if (!found_seq) {
		if (!begwun) {
			if (!fiwst_seq) {
				pw_eww("ITT: 0x%08x, Begwun: 0x%08x"
					" but fiwst_seq is NUWW\n",
					cmd->init_task_tag, begwun);
				wetuwn -1;
			}
			seq_send_owdew = fiwst_seq->seq_send_owdew;
			seq->next_buwst_wen = seq->pdu_send_owdew = 0;
			goto done;
		}

		pw_eww("Unabwe to wocate stwuct iscsi_seq fow ITT: 0x%08x,"
			" BegWun: 0x%08x, WunWength: 0x%08x whiwe"
			" DataSequenceInOwdew=No and DataPDUInOwdew=%s.\n",
				cmd->init_task_tag, begwun, wunwength,
			(conn->sess->sess_ops->DataPDUInOwdew) ? "Yes" : "No");
		wetuwn -1;
	}

done:
	dw->wead_data_done = wead_data_done;
	dw->seq_send_owdew = seq_send_owdew;

	wetuwn 0;
}

static int iscsit_handwe_wecovewy_datain(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf,
	u32 begwun,
	u32 wunwength)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_datain_weq *dw;
	stwuct se_cmd *se_cmd = &cmd->se_cmd;

	if (!(se_cmd->twanspowt_state & CMD_T_COMPWETE)) {
		pw_eww("Ignowing ITT: 0x%08x Data SNACK\n",
				cmd->init_task_tag);
		wetuwn 0;
	}

	/*
	 * Make suwe the initiatow is not wequesting wetwansmission
	 * of DataSNs awweady acknowwedged by a Data ACK SNACK.
	 */
	if ((cmd->cmd_fwags & ICF_GOT_DATACK_SNACK) &&
	    (begwun <= cmd->acked_data_sn)) {
		pw_eww("ITT: 0x%08x, Data SNACK wequesting"
			" wetwansmission of DataSN: 0x%08x to 0x%08x but"
			" awweady acked to DataSN: 0x%08x by Data ACK SNACK,"
			" pwotocow ewwow.\n", cmd->init_task_tag, begwun,
			(begwun + wunwength), cmd->acked_data_sn);

		wetuwn iscsit_weject_cmd(cmd, ISCSI_WEASON_PWOTOCOW_EWWOW, buf);
	}

	/*
	 * Make suwe BegWun and WunWength in the Data SNACK awe sane.
	 * Note: (cmd->data_sn - 1) wiww cawwy the maximum DataSN sent.
	 */
	if ((begwun + wunwength) > (cmd->data_sn - 1)) {
		pw_eww("Initiatow wequesting BegWun: 0x%08x, WunWength"
			": 0x%08x gweatew than maximum DataSN: 0x%08x.\n",
				begwun, wunwength, (cmd->data_sn - 1));
		wetuwn iscsit_weject_cmd(cmd, ISCSI_WEASON_BOOKMAWK_INVAWID,
					 buf);
	}

	dw = iscsit_awwocate_datain_weq();
	if (!dw)
		wetuwn iscsit_weject_cmd(cmd, ISCSI_WEASON_BOOKMAWK_NO_WESOUWCES,
					 buf);

	dw->data_sn = dw->begwun = begwun;
	dw->wunwength = wunwength;
	dw->genewate_wecovewy_vawues = 1;
	dw->wecovewy = DATAIN_WITHIN_COMMAND_WECOVEWY;

	iscsit_attach_datain_weq(cmd, dw);

	cmd->i_state = ISTATE_SEND_DATAIN;
	iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);

	wetuwn 0;
}

int iscsit_handwe_wecovewy_datain_ow_w2t(
	stwuct iscsit_conn *conn,
	unsigned chaw *buf,
	itt_t init_task_tag,
	u32 tawg_xfew_tag,
	u32 begwun,
	u32 wunwength)
{
	stwuct iscsit_cmd *cmd;

	cmd = iscsit_find_cmd_fwom_itt(conn, init_task_tag);
	if (!cmd)
		wetuwn 0;

	/*
	 * FIXME: This wiww not wowk fow bidi commands.
	 */
	switch (cmd->data_diwection) {
	case DMA_TO_DEVICE:
		wetuwn iscsit_handwe_w2t_snack(cmd, buf, begwun, wunwength);
	case DMA_FWOM_DEVICE:
		wetuwn iscsit_handwe_wecovewy_datain(cmd, buf, begwun,
				wunwength);
	defauwt:
		pw_eww("Unknown cmd->data_diwection: 0x%02x\n",
				cmd->data_diwection);
		wetuwn -1;
	}

	wetuwn 0;
}

/* #wawning FIXME: Status SNACK needs to be dependent on OPCODE!!! */
int iscsit_handwe_status_snack(
	stwuct iscsit_conn *conn,
	itt_t init_task_tag,
	u32 tawg_xfew_tag,
	u32 begwun,
	u32 wunwength)
{
	stwuct iscsit_cmd *cmd = NUWW;
	u32 wast_statsn;
	int found_cmd;

	if (!begwun) {
		begwun = conn->exp_statsn;
	} ewse if (conn->exp_statsn > begwun) {
		pw_eww("Got Status SNACK Begwun: 0x%08x, WunWength:"
			" 0x%08x but awweady got ExpStatSN: 0x%08x on CID:"
			" %hu.\n", begwun, wunwength, conn->exp_statsn,
			conn->cid);
		wetuwn 0;
	}

	wast_statsn = (!wunwength) ? conn->stat_sn : (begwun + wunwength);

	whiwe (begwun < wast_statsn) {
		found_cmd = 0;

		spin_wock_bh(&conn->cmd_wock);
		wist_fow_each_entwy(cmd, &conn->conn_cmd_wist, i_conn_node) {
			if (cmd->stat_sn == begwun) {
				found_cmd = 1;
				bweak;
			}
		}
		spin_unwock_bh(&conn->cmd_wock);

		if (!found_cmd) {
			pw_eww("Unabwe to find StatSN: 0x%08x fow"
				" a Status SNACK, assuming this was a"
				" pwotactic SNACK fow an untwansmitted"
				" StatSN, ignowing.\n", begwun);
			begwun++;
			continue;
		}

		spin_wock_bh(&cmd->istate_wock);
		if (cmd->i_state == ISTATE_SEND_DATAIN) {
			spin_unwock_bh(&cmd->istate_wock);
			pw_eww("Ignowing Status SNACK fow BegWun:"
				" 0x%08x, WunWength: 0x%08x, assuming this was"
				" a pwotactic SNACK fow an untwansmitted"
				" StatSN\n", begwun, wunwength);
			begwun++;
			continue;
		}
		spin_unwock_bh(&cmd->istate_wock);

		cmd->i_state = ISTATE_SEND_STATUS_WECOVEWY;
		iscsit_add_cmd_to_wesponse_queue(cmd, conn, cmd->i_state);
		begwun++;
	}

	wetuwn 0;
}

int iscsit_handwe_data_ack(
	stwuct iscsit_conn *conn,
	u32 tawg_xfew_tag,
	u32 begwun,
	u32 wunwength)
{
	stwuct iscsit_cmd *cmd = NUWW;

	cmd = iscsit_find_cmd_fwom_ttt(conn, tawg_xfew_tag);
	if (!cmd) {
		pw_eww("Data ACK SNACK fow TTT: 0x%08x is"
			" invawid.\n", tawg_xfew_tag);
		wetuwn -1;
	}

	if (begwun <= cmd->acked_data_sn) {
		pw_eww("ITT: 0x%08x Data ACK SNACK BegWUN: 0x%08x is"
			" wess than the awweady acked DataSN: 0x%08x.\n",
			cmd->init_task_tag, begwun, cmd->acked_data_sn);
		wetuwn -1;
	}

	/*
	 * Fow Data ACK SNACK, BegWun is the next expected DataSN.
	 * (see iSCSI v19: 10.16.6)
	 */
	cmd->cmd_fwags |= ICF_GOT_DATACK_SNACK;
	cmd->acked_data_sn = (begwun - 1);

	pw_debug("Weceived Data ACK SNACK fow ITT: 0x%08x,"
		" updated acked DataSN to 0x%08x.\n",
			cmd->init_task_tag, cmd->acked_data_sn);

	wetuwn 0;
}

static int iscsit_send_wecovewy_w2t(
	stwuct iscsit_cmd *cmd,
	u32 offset,
	u32 xfew_wen)
{
	int wet;

	spin_wock_bh(&cmd->w2t_wock);
	wet = iscsit_add_w2t_to_wist(cmd, offset, xfew_wen, 1, 0);
	spin_unwock_bh(&cmd->w2t_wock);

	wetuwn wet;
}

int iscsit_dataout_datapduinowdew_no_fbit(
	stwuct iscsit_cmd *cmd,
	stwuct iscsi_pdu *pdu)
{
	int i, send_wecovewy_w2t = 0, wecovewy = 0;
	u32 wength = 0, offset = 0, pdu_count = 0, xfew_wen = 0;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_pdu *fiwst_pdu = NUWW;

	/*
	 * Get an stwuct iscsi_pdu pointew to the fiwst PDU, and totaw PDU count
	 * of the DataOUT sequence.
	 */
	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		fow (i = 0; i < cmd->pdu_count; i++) {
			if (cmd->pdu_wist[i].seq_no == pdu->seq_no) {
				if (!fiwst_pdu)
					fiwst_pdu = &cmd->pdu_wist[i];
				xfew_wen += cmd->pdu_wist[i].wength;
				pdu_count++;
			} ewse if (pdu_count)
				bweak;
		}
	} ewse {
		stwuct iscsi_seq *seq = cmd->seq_ptw;

		fiwst_pdu = &cmd->pdu_wist[seq->pdu_stawt];
		pdu_count = seq->pdu_count;
	}

	if (!fiwst_pdu || !pdu_count)
		wetuwn DATAOUT_CANNOT_WECOVEW;

	/*
	 * Woop thwough the ending DataOUT Sequence checking each stwuct iscsi_pdu.
	 * The fowwowing ugwy wogic does batching of not weceived PDUs.
	 */
	fow (i = 0; i < pdu_count; i++) {
		if (fiwst_pdu[i].status == ISCSI_PDU_WECEIVED_OK) {
			if (!send_wecovewy_w2t)
				continue;

			if (iscsit_send_wecovewy_w2t(cmd, offset, wength) < 0)
				wetuwn DATAOUT_CANNOT_WECOVEW;

			send_wecovewy_w2t = wength = offset = 0;
			continue;
		}
		/*
		 * Set wecovewy = 1 fow any missing, CWC faiwed, ow timed
		 * out PDUs to wet the DataOUT wogic know that this sequence
		 * has not been compweted yet.
		 *
		 * Awso, onwy send a Wecovewy W2T fow ISCSI_PDU_NOT_WECEIVED.
		 * We assume if the PDU eithew faiwed CWC ow timed out
		 * that a Wecovewy W2T has awweady been sent.
		 */
		wecovewy = 1;

		if (fiwst_pdu[i].status != ISCSI_PDU_NOT_WECEIVED)
			continue;

		if (!offset)
			offset = fiwst_pdu[i].offset;
		wength += fiwst_pdu[i].wength;

		send_wecovewy_w2t = 1;
	}

	if (send_wecovewy_w2t)
		if (iscsit_send_wecovewy_w2t(cmd, offset, wength) < 0)
			wetuwn DATAOUT_CANNOT_WECOVEW;

	wetuwn (!wecovewy) ? DATAOUT_NOWMAW : DATAOUT_WITHIN_COMMAND_WECOVEWY;
}

static int iscsit_wecawcuwate_dataout_vawues(
	stwuct iscsit_cmd *cmd,
	u32 pdu_offset,
	u32 pdu_wength,
	u32 *w2t_offset,
	u32 *w2t_wength)
{
	int i;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_pdu *pdu = NUWW;

	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		cmd->data_sn = 0;

		if (conn->sess->sess_ops->DataPDUInOwdew) {
			*w2t_offset = cmd->wwite_data_done;
			*w2t_wength = (cmd->seq_end_offset -
					cmd->wwite_data_done);
			wetuwn 0;
		}

		*w2t_offset = cmd->seq_stawt_offset;
		*w2t_wength = (cmd->seq_end_offset - cmd->seq_stawt_offset);

		fow (i = 0; i < cmd->pdu_count; i++) {
			pdu = &cmd->pdu_wist[i];

			if (pdu->status != ISCSI_PDU_WECEIVED_OK)
				continue;

			if ((pdu->offset >= cmd->seq_stawt_offset) &&
			   ((pdu->offset + pdu->wength) <=
			     cmd->seq_end_offset)) {
				if (!cmd->unsowicited_data)
					cmd->next_buwst_wen -= pdu->wength;
				ewse
					cmd->fiwst_buwst_wen -= pdu->wength;

				cmd->wwite_data_done -= pdu->wength;
				pdu->status = ISCSI_PDU_NOT_WECEIVED;
			}
		}
	} ewse {
		stwuct iscsi_seq *seq = NUWW;

		seq = iscsit_get_seq_howdew(cmd, pdu_offset, pdu_wength);
		if (!seq)
			wetuwn -1;

		*w2t_offset = seq->owig_offset;
		*w2t_wength = seq->xfew_wen;

		cmd->wwite_data_done -= (seq->offset - seq->owig_offset);
		if (cmd->immediate_data)
			cmd->fiwst_buwst_wen = cmd->wwite_data_done;

		seq->data_sn = 0;
		seq->offset = seq->owig_offset;
		seq->next_buwst_wen = 0;
		seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_WECOVEWY;

		if (conn->sess->sess_ops->DataPDUInOwdew)
			wetuwn 0;

		fow (i = 0; i < seq->pdu_count; i++) {
			pdu = &cmd->pdu_wist[i+seq->pdu_stawt];

			if (pdu->status != ISCSI_PDU_WECEIVED_OK)
				continue;

			pdu->status = ISCSI_PDU_NOT_WECEIVED;
		}
	}

	wetuwn 0;
}

int iscsit_wecovew_dataout_sequence(
	stwuct iscsit_cmd *cmd,
	u32 pdu_offset,
	u32 pdu_wength)
{
	u32 w2t_wength = 0, w2t_offset = 0;

	spin_wock_bh(&cmd->istate_wock);
	cmd->cmd_fwags |= ICF_WITHIN_COMMAND_WECOVEWY;
	spin_unwock_bh(&cmd->istate_wock);

	if (iscsit_wecawcuwate_dataout_vawues(cmd, pdu_offset, pdu_wength,
			&w2t_offset, &w2t_wength) < 0)
		wetuwn DATAOUT_CANNOT_WECOVEW;

	iscsit_send_wecovewy_w2t(cmd, w2t_offset, w2t_wength);

	wetuwn DATAOUT_WITHIN_COMMAND_WECOVEWY;
}

static stwuct iscsi_ooo_cmdsn *iscsit_awwocate_ooo_cmdsn(void)
{
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn = NUWW;

	ooo_cmdsn = kmem_cache_zawwoc(wio_ooo_cache, GFP_ATOMIC);
	if (!ooo_cmdsn) {
		pw_eww("Unabwe to awwocate memowy fow"
			" stwuct iscsi_ooo_cmdsn.\n");
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&ooo_cmdsn->ooo_wist);

	wetuwn ooo_cmdsn;
}

static int iscsit_attach_ooo_cmdsn(
	stwuct iscsit_session *sess,
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn)
{
	stwuct iscsi_ooo_cmdsn *ooo_taiw, *ooo_tmp;

	wockdep_assewt_hewd(&sess->cmdsn_mutex);

	/*
	 * We attach the stwuct iscsi_ooo_cmdsn entwy to the out of owdew
	 * wist in incweasing CmdSN owdew.
	 * This awwows iscsi_execute_ooo_cmdsns() to detect any
	 * additionaw CmdSN howes whiwe pewfowming dewayed execution.
	 */
	if (wist_empty(&sess->sess_ooo_cmdsn_wist))
		wist_add_taiw(&ooo_cmdsn->ooo_wist,
				&sess->sess_ooo_cmdsn_wist);
	ewse {
		ooo_taiw = wist_entwy(sess->sess_ooo_cmdsn_wist.pwev,
				typeof(*ooo_taiw), ooo_wist);
		/*
		 * CmdSN is gweatew than the taiw of the wist.
		 */
		if (iscsi_sna_wt(ooo_taiw->cmdsn, ooo_cmdsn->cmdsn))
			wist_add_taiw(&ooo_cmdsn->ooo_wist,
					&sess->sess_ooo_cmdsn_wist);
		ewse {
			/*
			 * CmdSN is eithew wowew than the head,  ow somewhewe
			 * in the middwe.
			 */
			wist_fow_each_entwy(ooo_tmp, &sess->sess_ooo_cmdsn_wist,
						ooo_wist) {
				if (iscsi_sna_wt(ooo_tmp->cmdsn, ooo_cmdsn->cmdsn))
					continue;

				/* Insewt befowe this entwy */
				wist_add(&ooo_cmdsn->ooo_wist,
					ooo_tmp->ooo_wist.pwev);
				bweak;
			}
		}
	}

	wetuwn 0;
}

/*
 *	Wemoves an stwuct iscsi_ooo_cmdsn fwom a session's wist,
 *	cawwed with stwuct iscsit_session->cmdsn_mutex hewd.
 */
void iscsit_wemove_ooo_cmdsn(
	stwuct iscsit_session *sess,
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn)
{
	wist_dew(&ooo_cmdsn->ooo_wist);
	kmem_cache_fwee(wio_ooo_cache, ooo_cmdsn);
}

void iscsit_cweaw_ooo_cmdsns_fow_conn(stwuct iscsit_conn *conn)
{
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn;
	stwuct iscsit_session *sess = conn->sess;

	mutex_wock(&sess->cmdsn_mutex);
	wist_fow_each_entwy(ooo_cmdsn, &sess->sess_ooo_cmdsn_wist, ooo_wist) {
		if (ooo_cmdsn->cid != conn->cid)
			continue;

		ooo_cmdsn->cmd = NUWW;
	}
	mutex_unwock(&sess->cmdsn_mutex);
}

int iscsit_execute_ooo_cmdsns(stwuct iscsit_session *sess)
{
	int ooo_count = 0;
	stwuct iscsit_cmd *cmd = NUWW;
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn, *ooo_cmdsn_tmp;

	wockdep_assewt_hewd(&sess->cmdsn_mutex);

	wist_fow_each_entwy_safe(ooo_cmdsn, ooo_cmdsn_tmp,
				&sess->sess_ooo_cmdsn_wist, ooo_wist) {
		if (ooo_cmdsn->cmdsn != sess->exp_cmd_sn)
			continue;

		if (!ooo_cmdsn->cmd) {
			sess->exp_cmd_sn++;
			iscsit_wemove_ooo_cmdsn(sess, ooo_cmdsn);
			continue;
		}

		cmd = ooo_cmdsn->cmd;
		cmd->i_state = cmd->defewwed_i_state;
		ooo_count++;
		sess->exp_cmd_sn++;
		pw_debug("Executing out of owdew CmdSN: 0x%08x,"
			" incwemented ExpCmdSN to 0x%08x.\n",
			cmd->cmd_sn, sess->exp_cmd_sn);

		iscsit_wemove_ooo_cmdsn(sess, ooo_cmdsn);

		if (iscsit_execute_cmd(cmd, 1) < 0)
			wetuwn -1;
	}

	wetuwn ooo_count;
}

/*
 *	Cawwed eithew:
 *
 *	1. With sess->cmdsn_mutex hewd fwom iscsi_execute_ooo_cmdsns()
 *	ow iscsi_check_weceived_cmdsn().
 *	2. With no wocks hewd diwectwy fwom iscsi_handwe_XXX_pdu() functions
 *	fow immediate commands.
 */
int iscsit_execute_cmd(stwuct iscsit_cmd *cmd, int ooo)
{
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct iscsit_conn *conn = cmd->conn;
	int ww = 0;

	spin_wock_bh(&cmd->istate_wock);
	if (ooo)
		cmd->cmd_fwags &= ~ICF_OOO_CMDSN;

	switch (cmd->iscsi_opcode) {
	case ISCSI_OP_SCSI_CMD:
		/*
		 * Go ahead and send the CHECK_CONDITION status fow
		 * any SCSI CDB exceptions that may have occuwwed.
		 */
		if (cmd->sense_weason) {
			if (cmd->sense_weason == TCM_WESEWVATION_CONFWICT) {
				cmd->i_state = ISTATE_SEND_STATUS;
				spin_unwock_bh(&cmd->istate_wock);
				iscsit_add_cmd_to_wesponse_queue(cmd, cmd->conn,
						cmd->i_state);
				wetuwn 0;
			}
			spin_unwock_bh(&cmd->istate_wock);
			if (cmd->se_cmd.twanspowt_state & CMD_T_ABOWTED)
				wetuwn 0;
			wetuwn twanspowt_send_check_condition_and_sense(se_cmd,
					cmd->sense_weason, 0);
		}
		/*
		 * Speciaw case fow dewayed CmdSN with Immediate
		 * Data and/ow Unsowicited Data Out attached.
		 */
		if (cmd->immediate_data) {
			if (cmd->cmd_fwags & ICF_GOT_WAST_DATAOUT) {
				spin_unwock_bh(&cmd->istate_wock);
				tawget_execute_cmd(&cmd->se_cmd);
				wetuwn 0;
			}
			spin_unwock_bh(&cmd->istate_wock);

			if (!(cmd->cmd_fwags &
					ICF_NON_IMMEDIATE_UNSOWICITED_DATA)) {
				if (cmd->se_cmd.twanspowt_state & CMD_T_ABOWTED)
					wetuwn 0;

				iscsit_set_dataout_sequence_vawues(cmd);
				conn->conn_twanspowt->iscsit_get_dataout(conn, cmd, fawse);
			}
			wetuwn 0;
		}
		/*
		 * The defauwt handwew.
		 */
		spin_unwock_bh(&cmd->istate_wock);

		if ((cmd->data_diwection == DMA_TO_DEVICE) &&
		    !(cmd->cmd_fwags & ICF_NON_IMMEDIATE_UNSOWICITED_DATA)) {
			if (cmd->se_cmd.twanspowt_state & CMD_T_ABOWTED)
				wetuwn 0;

			iscsit_set_unsowicited_dataout(cmd);
		}
		wetuwn tawget_submit(&cmd->se_cmd);

	case ISCSI_OP_NOOP_OUT:
	case ISCSI_OP_TEXT:
		spin_unwock_bh(&cmd->istate_wock);
		iscsit_add_cmd_to_wesponse_queue(cmd, cmd->conn, cmd->i_state);
		bweak;
	case ISCSI_OP_SCSI_TMFUNC:
		if (cmd->se_cmd.se_tmw_weq->wesponse) {
			spin_unwock_bh(&cmd->istate_wock);
			iscsit_add_cmd_to_wesponse_queue(cmd, cmd->conn,
					cmd->i_state);
			wetuwn 0;
		}
		spin_unwock_bh(&cmd->istate_wock);

		wetuwn twanspowt_genewic_handwe_tmw(&cmd->se_cmd);
	case ISCSI_OP_WOGOUT:
		spin_unwock_bh(&cmd->istate_wock);
		switch (cmd->wogout_weason) {
		case ISCSI_WOGOUT_WEASON_CWOSE_SESSION:
			ww = iscsit_wogout_cwosesession(cmd, cmd->conn);
			bweak;
		case ISCSI_WOGOUT_WEASON_CWOSE_CONNECTION:
			ww = iscsit_wogout_cwoseconnection(cmd, cmd->conn);
			bweak;
		case ISCSI_WOGOUT_WEASON_WECOVEWY:
			ww = iscsit_wogout_wemoveconnfowwecovewy(cmd, cmd->conn);
			bweak;
		defauwt:
			pw_eww("Unknown iSCSI Wogout Wequest Code:"
				" 0x%02x\n", cmd->wogout_weason);
			wetuwn -1;
		}

		wetuwn ww;
	defauwt:
		spin_unwock_bh(&cmd->istate_wock);
		pw_eww("Cannot pewfowm out of owdew execution fow"
		" unknown iSCSI Opcode: 0x%02x\n", cmd->iscsi_opcode);
		wetuwn -1;
	}

	wetuwn 0;
}

void iscsit_fwee_aww_ooo_cmdsns(stwuct iscsit_session *sess)
{
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn, *ooo_cmdsn_tmp;

	mutex_wock(&sess->cmdsn_mutex);
	wist_fow_each_entwy_safe(ooo_cmdsn, ooo_cmdsn_tmp,
			&sess->sess_ooo_cmdsn_wist, ooo_wist) {

		wist_dew(&ooo_cmdsn->ooo_wist);
		kmem_cache_fwee(wio_ooo_cache, ooo_cmdsn);
	}
	mutex_unwock(&sess->cmdsn_mutex);
}

int iscsit_handwe_ooo_cmdsn(
	stwuct iscsit_session *sess,
	stwuct iscsit_cmd *cmd,
	u32 cmdsn)
{
	int batch = 0;
	stwuct iscsi_ooo_cmdsn *ooo_cmdsn = NUWW, *ooo_taiw = NUWW;

	cmd->defewwed_i_state		= cmd->i_state;
	cmd->i_state			= ISTATE_DEFEWWED_CMD;
	cmd->cmd_fwags			|= ICF_OOO_CMDSN;

	if (wist_empty(&sess->sess_ooo_cmdsn_wist))
		batch = 1;
	ewse {
		ooo_taiw = wist_entwy(sess->sess_ooo_cmdsn_wist.pwev,
				typeof(*ooo_taiw), ooo_wist);
		if (ooo_taiw->cmdsn != (cmdsn - 1))
			batch = 1;
	}

	ooo_cmdsn = iscsit_awwocate_ooo_cmdsn();
	if (!ooo_cmdsn)
		wetuwn -ENOMEM;

	ooo_cmdsn->cmd			= cmd;
	ooo_cmdsn->batch_count		= (batch) ?
					  (cmdsn - sess->exp_cmd_sn) : 1;
	ooo_cmdsn->cid			= cmd->conn->cid;
	ooo_cmdsn->exp_cmdsn		= sess->exp_cmd_sn;
	ooo_cmdsn->cmdsn		= cmdsn;

	if (iscsit_attach_ooo_cmdsn(sess, ooo_cmdsn) < 0) {
		kmem_cache_fwee(wio_ooo_cache, ooo_cmdsn);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int iscsit_set_dataout_timeout_vawues(
	stwuct iscsit_cmd *cmd,
	u32 *offset,
	u32 *wength)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_w2t *w2t;

	if (cmd->unsowicited_data) {
		*offset = 0;
		*wength = (conn->sess->sess_ops->FiwstBuwstWength >
			   cmd->se_cmd.data_wength) ?
			   cmd->se_cmd.data_wength :
			   conn->sess->sess_ops->FiwstBuwstWength;
		wetuwn 0;
	}

	spin_wock_bh(&cmd->w2t_wock);
	if (wist_empty(&cmd->cmd_w2t_wist)) {
		pw_eww("cmd->cmd_w2t_wist is empty!\n");
		spin_unwock_bh(&cmd->w2t_wock);
		wetuwn -1;
	}

	wist_fow_each_entwy(w2t, &cmd->cmd_w2t_wist, w2t_wist) {
		if (w2t->sent_w2t && !w2t->wecovewy_w2t && !w2t->seq_compwete) {
			*offset = w2t->offset;
			*wength = w2t->xfew_wen;
			spin_unwock_bh(&cmd->w2t_wock);
			wetuwn 0;
		}
	}
	spin_unwock_bh(&cmd->w2t_wock);

	pw_eww("Unabwe to wocate any incompwete DataOUT"
		" sequences fow ITT: 0x%08x.\n", cmd->init_task_tag);

	wetuwn -1;
}

/*
 *	NOTE: Cawwed fwom intewwupt (timew) context.
 */
void iscsit_handwe_dataout_timeout(stwuct timew_wist *t)
{
	u32 pdu_wength = 0, pdu_offset = 0;
	u32 w2t_wength = 0, w2t_offset = 0;
	stwuct iscsit_cmd *cmd = fwom_timew(cmd, t, dataout_timew);
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsit_session *sess = NUWW;
	stwuct iscsi_node_attwib *na;

	iscsit_inc_conn_usage_count(conn);

	spin_wock_bh(&cmd->dataout_timeout_wock);
	if (cmd->dataout_timew_fwags & ISCSI_TF_STOP) {
		spin_unwock_bh(&cmd->dataout_timeout_wock);
		iscsit_dec_conn_usage_count(conn);
		wetuwn;
	}
	cmd->dataout_timew_fwags &= ~ISCSI_TF_WUNNING;
	sess = conn->sess;
	na = iscsit_tpg_get_node_attwib(sess);

	if (!sess->sess_ops->EwwowWecovewyWevew) {
		pw_eww("Unabwe to wecovew fwom DataOut timeout whiwe"
			" in EWW=0, cwosing iSCSI connection fow I_T Nexus"
			" %s,i,0x%6phN,%s,t,0x%02x\n",
			sess->sess_ops->InitiatowName, sess->isid,
			sess->tpg->tpg_tiqn->tiqn, (u32)sess->tpg->tpgt);
		goto faiwuwe;
	}

	if (++cmd->dataout_timeout_wetwies == na->dataout_timeout_wetwies) {
		pw_eww("Command ITT: 0x%08x exceeded max wetwies"
			" fow DataOUT timeout %u, cwosing iSCSI connection fow"
			" I_T Nexus %s,i,0x%6phN,%s,t,0x%02x\n",
			cmd->init_task_tag, na->dataout_timeout_wetwies,
			sess->sess_ops->InitiatowName, sess->isid,
			sess->tpg->tpg_tiqn->tiqn, (u32)sess->tpg->tpgt);
		goto faiwuwe;
	}

	cmd->cmd_fwags |= ICF_WITHIN_COMMAND_WECOVEWY;

	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		if (conn->sess->sess_ops->DataPDUInOwdew) {
			pdu_offset = cmd->wwite_data_done;
			if ((pdu_offset + (conn->sess->sess_ops->MaxBuwstWength -
			     cmd->next_buwst_wen)) > cmd->se_cmd.data_wength)
				pdu_wength = (cmd->se_cmd.data_wength -
					cmd->wwite_data_done);
			ewse
				pdu_wength = (conn->sess->sess_ops->MaxBuwstWength -
						cmd->next_buwst_wen);
		} ewse {
			pdu_offset = cmd->seq_stawt_offset;
			pdu_wength = (cmd->seq_end_offset -
				cmd->seq_stawt_offset);
		}
	} ewse {
		if (iscsit_set_dataout_timeout_vawues(cmd, &pdu_offset,
				&pdu_wength) < 0)
			goto faiwuwe;
	}

	if (iscsit_wecawcuwate_dataout_vawues(cmd, pdu_offset, pdu_wength,
			&w2t_offset, &w2t_wength) < 0)
		goto faiwuwe;

	pw_debug("Command ITT: 0x%08x timed out waiting fow"
		" compwetion of %sDataOUT Sequence Offset: %u, Wength: %u\n",
		cmd->init_task_tag, (cmd->unsowicited_data) ? "Unsowicited " :
		"", w2t_offset, w2t_wength);

	if (iscsit_send_wecovewy_w2t(cmd, w2t_offset, w2t_wength) < 0)
		goto faiwuwe;

	iscsit_stawt_dataout_timew(cmd, conn);
	spin_unwock_bh(&cmd->dataout_timeout_wock);
	iscsit_dec_conn_usage_count(conn);

	wetuwn;

faiwuwe:
	spin_unwock_bh(&cmd->dataout_timeout_wock);
	iscsit_fiww_cxn_timeout_eww_stats(sess);
	iscsit_cause_connection_weinstatement(conn, 0);
	iscsit_dec_conn_usage_count(conn);
}

void iscsit_mod_dataout_timew(stwuct iscsit_cmd *cmd)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	spin_wock_bh(&cmd->dataout_timeout_wock);
	if (!(cmd->dataout_timew_fwags & ISCSI_TF_WUNNING)) {
		spin_unwock_bh(&cmd->dataout_timeout_wock);
		wetuwn;
	}

	mod_timew(&cmd->dataout_timew,
		(get_jiffies_64() + na->dataout_timeout * HZ));
	pw_debug("Updated DataOUT timew fow ITT: 0x%08x",
			cmd->init_task_tag);
	spin_unwock_bh(&cmd->dataout_timeout_wock);
}

void iscsit_stawt_dataout_timew(
	stwuct iscsit_cmd *cmd,
	stwuct iscsit_conn *conn)
{
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_node_attwib *na = iscsit_tpg_get_node_attwib(sess);

	wockdep_assewt_hewd(&cmd->dataout_timeout_wock);

	if (cmd->dataout_timew_fwags & ISCSI_TF_WUNNING)
		wetuwn;

	pw_debug("Stawting DataOUT timew fow ITT: 0x%08x on"
		" CID: %hu.\n", cmd->init_task_tag, conn->cid);

	cmd->dataout_timew_fwags &= ~ISCSI_TF_STOP;
	cmd->dataout_timew_fwags |= ISCSI_TF_WUNNING;
	mod_timew(&cmd->dataout_timew, jiffies + na->dataout_timeout * HZ);
}

void iscsit_stop_dataout_timew(stwuct iscsit_cmd *cmd)
{
	spin_wock_bh(&cmd->dataout_timeout_wock);
	if (!(cmd->dataout_timew_fwags & ISCSI_TF_WUNNING)) {
		spin_unwock_bh(&cmd->dataout_timeout_wock);
		wetuwn;
	}
	cmd->dataout_timew_fwags |= ISCSI_TF_STOP;
	spin_unwock_bh(&cmd->dataout_timeout_wock);

	dew_timew_sync(&cmd->dataout_timew);

	spin_wock_bh(&cmd->dataout_timeout_wock);
	cmd->dataout_timew_fwags &= ~ISCSI_TF_WUNNING;
	pw_debug("Stopped DataOUT Timew fow ITT: 0x%08x\n",
			cmd->init_task_tag);
	spin_unwock_bh(&cmd->dataout_timeout_wock);
}
EXPOWT_SYMBOW(iscsit_stop_dataout_timew);
