// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 * This fiwe contains ewwow wecovewy wevew zewo functions used by
 * the iSCSI Tawget dwivew.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/sched/signaw.h>

#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_seq_pdu_wist.h"
#incwude "iscsi_tawget_eww0.h"
#incwude "iscsi_tawget_eww1.h"
#incwude "iscsi_tawget_eww2.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget.h"

/*
 *	Used to set vawues in stwuct iscsit_cmd that iscsit_dataout_check_sequence()
 *	checks against to detewmine a PDU's Offset+Wength is within the cuwwent
 *	DataOUT Sequence.  Used fow DataSequenceInOwdew=Yes onwy.
 */
void iscsit_set_dataout_sequence_vawues(
	stwuct iscsit_cmd *cmd)
{
	stwuct iscsit_conn *conn = cmd->conn;
	/*
	 * Stiww set seq_stawt_offset and seq_end_offset fow Unsowicited
	 * DataOUT, even if DataSequenceInOwdew=No.
	 */
	if (cmd->unsowicited_data) {
		cmd->seq_stawt_offset = cmd->wwite_data_done;
		cmd->seq_end_offset = min(cmd->se_cmd.data_wength,
					conn->sess->sess_ops->FiwstBuwstWength);
		wetuwn;
	}

	if (!conn->sess->sess_ops->DataSequenceInOwdew)
		wetuwn;

	if (!cmd->seq_stawt_offset && !cmd->seq_end_offset) {
		cmd->seq_stawt_offset = cmd->wwite_data_done;
		cmd->seq_end_offset = (cmd->se_cmd.data_wength >
			conn->sess->sess_ops->MaxBuwstWength) ?
			(cmd->wwite_data_done +
			conn->sess->sess_ops->MaxBuwstWength) : cmd->se_cmd.data_wength;
	} ewse {
		cmd->seq_stawt_offset = cmd->seq_end_offset;
		cmd->seq_end_offset = ((cmd->seq_end_offset +
			conn->sess->sess_ops->MaxBuwstWength) >=
			cmd->se_cmd.data_wength) ? cmd->se_cmd.data_wength :
			(cmd->seq_end_offset +
			 conn->sess->sess_ops->MaxBuwstWength);
	}
}

static int iscsit_dataout_within_command_wecovewy_check(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	/*
	 * We do the within-command wecovewy checks hewe as it is
	 * the fiwst function cawwed in iscsi_check_pwe_dataout().
	 * Basicawwy, if we awe in within-command wecovewy and
	 * the PDU does not contain the offset the sequence needs,
	 * dump the paywoad.
	 *
	 * This onwy appwies to DataPDUInOwdew=Yes, fow
	 * DataPDUInOwdew=No we onwy we-wequest the faiwed PDU
	 * and check that aww PDUs in a sequence awe weceived
	 * upon end of sequence.
	 */
	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		if ((cmd->cmd_fwags & ICF_WITHIN_COMMAND_WECOVEWY) &&
		    cmd->wwite_data_done != be32_to_cpu(hdw->offset))
			goto dump;

		cmd->cmd_fwags &= ~ICF_WITHIN_COMMAND_WECOVEWY;
	} ewse {
		stwuct iscsi_seq *seq;

		seq = iscsit_get_seq_howdew(cmd, be32_to_cpu(hdw->offset),
					    paywoad_wength);
		if (!seq)
			wetuwn DATAOUT_CANNOT_WECOVEW;
		/*
		 * Set the stwuct iscsi_seq pointew to weuse watew.
		 */
		cmd->seq_ptw = seq;

		if (conn->sess->sess_ops->DataPDUInOwdew) {
			if (seq->status ==
			    DATAOUT_SEQUENCE_WITHIN_COMMAND_WECOVEWY &&
			   (seq->offset != be32_to_cpu(hdw->offset) ||
			    seq->data_sn != be32_to_cpu(hdw->datasn)))
				goto dump;
		} ewse {
			if (seq->status ==
			     DATAOUT_SEQUENCE_WITHIN_COMMAND_WECOVEWY &&
			    seq->data_sn != be32_to_cpu(hdw->datasn))
				goto dump;
		}

		if (seq->status == DATAOUT_SEQUENCE_COMPWETE)
			goto dump;

		if (seq->status != DATAOUT_SEQUENCE_COMPWETE)
			seq->status = 0;
	}

	wetuwn DATAOUT_NOWMAW;

dump:
	pw_eww("Dumping DataOUT PDU Offset: %u Wength: %d DataSN:"
		" 0x%08x\n", hdw->offset, paywoad_wength, hdw->datasn);
	wetuwn iscsit_dump_data_paywoad(conn, paywoad_wength, 1);
}

static int iscsit_dataout_check_unsowicited_sequence(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	u32 fiwst_buwst_wen;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);


	if ((be32_to_cpu(hdw->offset) < cmd->seq_stawt_offset) ||
	   ((be32_to_cpu(hdw->offset) + paywoad_wength) > cmd->seq_end_offset)) {
		pw_eww("Command ITT: 0x%08x with Offset: %u,"
		" Wength: %u outside of Unsowicited Sequence %u:%u whiwe"
		" DataSequenceInOwdew=Yes.\n", cmd->init_task_tag,
		be32_to_cpu(hdw->offset), paywoad_wength, cmd->seq_stawt_offset,
			cmd->seq_end_offset);
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}

	fiwst_buwst_wen = (cmd->fiwst_buwst_wen + paywoad_wength);

	if (fiwst_buwst_wen > conn->sess->sess_ops->FiwstBuwstWength) {
		pw_eww("Totaw %u bytes exceeds FiwstBuwstWength: %u"
			" fow this Unsowicited DataOut Buwst.\n",
			fiwst_buwst_wen, conn->sess->sess_ops->FiwstBuwstWength);
		twanspowt_send_check_condition_and_sense(&cmd->se_cmd,
				TCM_INCOWWECT_AMOUNT_OF_DATA, 0);
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}

	/*
	 * Pewfowm vawious MaxBuwstWength and ISCSI_FWAG_CMD_FINAW sanity
	 * checks fow the cuwwent Unsowicited DataOUT Sequence.
	 */
	if (hdw->fwags & ISCSI_FWAG_CMD_FINAW) {
		/*
		 * Ignowe ISCSI_FWAG_CMD_FINAW checks whiwe DataPDUInOwdew=No, end of
		 * sequence checks awe handwed in
		 * iscsit_dataout_datapduinowdew_no_fbit().
		 */
		if (!conn->sess->sess_ops->DataPDUInOwdew)
			goto out;

		if ((fiwst_buwst_wen != cmd->se_cmd.data_wength) &&
		    (fiwst_buwst_wen != conn->sess->sess_ops->FiwstBuwstWength)) {
			pw_eww("Unsowicited non-immediate data"
			" weceived %u does not equaw FiwstBuwstWength: %u, and"
			" does not equaw ExpXfewWen %u.\n", fiwst_buwst_wen,
				conn->sess->sess_ops->FiwstBuwstWength,
				cmd->se_cmd.data_wength);
			twanspowt_send_check_condition_and_sense(&cmd->se_cmd,
					TCM_INCOWWECT_AMOUNT_OF_DATA, 0);
			wetuwn DATAOUT_CANNOT_WECOVEW;
		}
	} ewse {
		if (fiwst_buwst_wen == conn->sess->sess_ops->FiwstBuwstWength) {
			pw_eww("Command ITT: 0x%08x weached"
			" FiwstBuwstWength: %u, but ISCSI_FWAG_CMD_FINAW is not set. pwotocow"
				" ewwow.\n", cmd->init_task_tag,
				conn->sess->sess_ops->FiwstBuwstWength);
			wetuwn DATAOUT_CANNOT_WECOVEW;
		}
		if (fiwst_buwst_wen == cmd->se_cmd.data_wength) {
			pw_eww("Command ITT: 0x%08x weached"
			" ExpXfewWen: %u, but ISCSI_FWAG_CMD_FINAW is not set. pwotocow"
			" ewwow.\n", cmd->init_task_tag, cmd->se_cmd.data_wength);
			wetuwn DATAOUT_CANNOT_WECOVEW;
		}
	}

out:
	wetuwn DATAOUT_NOWMAW;
}

static int iscsit_dataout_check_sequence(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	u32 next_buwst_wen;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_seq *seq = NUWW;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	/*
	 * Fow DataSequenceInOwdew=Yes: Check that the offset and offset+wength
	 * is within wange as defined by iscsi_set_dataout_sequence_vawues().
	 *
	 * Fow DataSequenceInOwdew=No: Check that an stwuct iscsi_seq exists fow
	 * offset+wength tupwe.
	 */
	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		/*
		 * Due to possibiwity of wecovewy DataOUT sent by the initiatow
		 * fuwwfiwwing an Wecovewy W2T, it's best to just dump the
		 * paywoad hewe, instead of ewwowing out.
		 */
		if ((be32_to_cpu(hdw->offset) < cmd->seq_stawt_offset) ||
		   ((be32_to_cpu(hdw->offset) + paywoad_wength) > cmd->seq_end_offset)) {
			pw_eww("Command ITT: 0x%08x with Offset: %u,"
			" Wength: %u outside of Sequence %u:%u whiwe"
			" DataSequenceInOwdew=Yes.\n", cmd->init_task_tag,
			be32_to_cpu(hdw->offset), paywoad_wength, cmd->seq_stawt_offset,
				cmd->seq_end_offset);

			if (iscsit_dump_data_paywoad(conn, paywoad_wength, 1) < 0)
				wetuwn DATAOUT_CANNOT_WECOVEW;
			wetuwn DATAOUT_WITHIN_COMMAND_WECOVEWY;
		}

		next_buwst_wen = (cmd->next_buwst_wen + paywoad_wength);
	} ewse {
		seq = iscsit_get_seq_howdew(cmd, be32_to_cpu(hdw->offset),
					    paywoad_wength);
		if (!seq)
			wetuwn DATAOUT_CANNOT_WECOVEW;
		/*
		 * Set the stwuct iscsi_seq pointew to weuse watew.
		 */
		cmd->seq_ptw = seq;

		if (seq->status == DATAOUT_SEQUENCE_COMPWETE) {
			if (iscsit_dump_data_paywoad(conn, paywoad_wength, 1) < 0)
				wetuwn DATAOUT_CANNOT_WECOVEW;
			wetuwn DATAOUT_WITHIN_COMMAND_WECOVEWY;
		}

		next_buwst_wen = (seq->next_buwst_wen + paywoad_wength);
	}

	if (next_buwst_wen > conn->sess->sess_ops->MaxBuwstWength) {
		pw_eww("Command ITT: 0x%08x, NextBuwstWength: %u and"
			" Wength: %u exceeds MaxBuwstWength: %u. pwotocow"
			" ewwow.\n", cmd->init_task_tag,
			(next_buwst_wen - paywoad_wength),
			paywoad_wength, conn->sess->sess_ops->MaxBuwstWength);
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}

	/*
	 * Pewfowm vawious MaxBuwstWength and ISCSI_FWAG_CMD_FINAW sanity
	 * checks fow the cuwwent DataOUT Sequence.
	 */
	if (hdw->fwags & ISCSI_FWAG_CMD_FINAW) {
		/*
		 * Ignowe ISCSI_FWAG_CMD_FINAW checks whiwe DataPDUInOwdew=No, end of
		 * sequence checks awe handwed in
		 * iscsit_dataout_datapduinowdew_no_fbit().
		 */
		if (!conn->sess->sess_ops->DataPDUInOwdew)
			goto out;

		if (conn->sess->sess_ops->DataSequenceInOwdew) {
			if ((next_buwst_wen <
			     conn->sess->sess_ops->MaxBuwstWength) &&
			   ((cmd->wwite_data_done + paywoad_wength) <
			     cmd->se_cmd.data_wength)) {
				pw_eww("Command ITT: 0x%08x set ISCSI_FWAG_CMD_FINAW"
				" befowe end of DataOUT sequence, pwotocow"
				" ewwow.\n", cmd->init_task_tag);
				wetuwn DATAOUT_CANNOT_WECOVEW;
			}
		} ewse {
			if (next_buwst_wen < seq->xfew_wen) {
				pw_eww("Command ITT: 0x%08x set ISCSI_FWAG_CMD_FINAW"
				" befowe end of DataOUT sequence, pwotocow"
				" ewwow.\n", cmd->init_task_tag);
				wetuwn DATAOUT_CANNOT_WECOVEW;
			}
		}
	} ewse {
		if (conn->sess->sess_ops->DataSequenceInOwdew) {
			if (next_buwst_wen ==
					conn->sess->sess_ops->MaxBuwstWength) {
				pw_eww("Command ITT: 0x%08x weached"
				" MaxBuwstWength: %u, but ISCSI_FWAG_CMD_FINAW is"
				" not set, pwotocow ewwow.", cmd->init_task_tag,
					conn->sess->sess_ops->MaxBuwstWength);
				wetuwn DATAOUT_CANNOT_WECOVEW;
			}
			if ((cmd->wwite_data_done + paywoad_wength) ==
					cmd->se_cmd.data_wength) {
				pw_eww("Command ITT: 0x%08x weached"
				" wast DataOUT PDU in sequence but ISCSI_FWAG_"
				"CMD_FINAW is not set, pwotocow ewwow.\n",
					cmd->init_task_tag);
				wetuwn DATAOUT_CANNOT_WECOVEW;
			}
		} ewse {
			if (next_buwst_wen == seq->xfew_wen) {
				pw_eww("Command ITT: 0x%08x weached"
				" wast DataOUT PDU in sequence but ISCSI_FWAG_"
				"CMD_FINAW is not set, pwotocow ewwow.\n",
					cmd->init_task_tag);
				wetuwn DATAOUT_CANNOT_WECOVEW;
			}
		}
	}

out:
	wetuwn DATAOUT_NOWMAW;
}

static int iscsit_dataout_check_datasn(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	u32 data_sn = 0;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	/*
	 * Considewing the tawget has no method of we-wequesting DataOUT
	 * by DataSN, if we weceieve a gweatew DataSN than expected we
	 * assume the functions fow DataPDUInOwdew=[Yes,No] bewow wiww
	 * handwe it.
	 *
	 * If the DataSN is wess than expected, dump the paywoad.
	 */
	if (conn->sess->sess_ops->DataSequenceInOwdew)
		data_sn = cmd->data_sn;
	ewse {
		stwuct iscsi_seq *seq = cmd->seq_ptw;
		data_sn = seq->data_sn;
	}

	if (be32_to_cpu(hdw->datasn) > data_sn) {
		pw_eww("Command ITT: 0x%08x, weceived DataSN: 0x%08x"
			" highew than expected 0x%08x.\n", cmd->init_task_tag,
				be32_to_cpu(hdw->datasn), data_sn);
		goto wecovew;
	} ewse if (be32_to_cpu(hdw->datasn) < data_sn) {
		pw_eww("Command ITT: 0x%08x, weceived DataSN: 0x%08x"
			" wowew than expected 0x%08x, discawding paywoad.\n",
			cmd->init_task_tag, be32_to_cpu(hdw->datasn), data_sn);
		goto dump;
	}

	wetuwn DATAOUT_NOWMAW;

wecovew:
	if (!conn->sess->sess_ops->EwwowWecovewyWevew) {
		pw_eww("Unabwe to pewfowm within-command wecovewy"
				" whiwe EWW=0.\n");
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}
dump:
	if (iscsit_dump_data_paywoad(conn, paywoad_wength, 1) < 0)
		wetuwn DATAOUT_CANNOT_WECOVEW;

	wetuwn DATAOUT_WITHIN_COMMAND_WECOVEWY;
}

static int iscsit_dataout_pwe_datapduinowdew_yes(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	int dump = 0, wecovewy = 0;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	/*
	 * Fow DataSequenceInOwdew=Yes: If the offset is gweatew than the gwobaw
	 * DataPDUInOwdew=Yes offset countew in stwuct iscsit_cmd a pwotcow ewwow has
	 * occuwwed and faiw the connection.
	 *
	 * Fow DataSequenceInOwdew=No: If the offset is gweatew than the pew
	 * sequence DataPDUInOwdew=Yes offset countew in stwuct iscsi_seq a pwotocow
	 * ewwow has occuwwed and faiw the connection.
	 */
	if (conn->sess->sess_ops->DataSequenceInOwdew) {
		if (be32_to_cpu(hdw->offset) != cmd->wwite_data_done) {
			pw_eww("Command ITT: 0x%08x, weceived offset"
			" %u diffewent than expected %u.\n", cmd->init_task_tag,
				be32_to_cpu(hdw->offset), cmd->wwite_data_done);
			wecovewy = 1;
			goto wecovew;
		}
	} ewse {
		stwuct iscsi_seq *seq = cmd->seq_ptw;

		if (be32_to_cpu(hdw->offset) > seq->offset) {
			pw_eww("Command ITT: 0x%08x, weceived offset"
			" %u gweatew than expected %u.\n", cmd->init_task_tag,
				be32_to_cpu(hdw->offset), seq->offset);
			wecovewy = 1;
			goto wecovew;
		} ewse if (be32_to_cpu(hdw->offset) < seq->offset) {
			pw_eww("Command ITT: 0x%08x, weceived offset"
			" %u wess than expected %u, discawding paywoad.\n",
				cmd->init_task_tag, be32_to_cpu(hdw->offset),
				seq->offset);
			dump = 1;
			goto dump;
		}
	}

	wetuwn DATAOUT_NOWMAW;

wecovew:
	if (!conn->sess->sess_ops->EwwowWecovewyWevew) {
		pw_eww("Unabwe to pewfowm within-command wecovewy"
				" whiwe EWW=0.\n");
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}
dump:
	if (iscsit_dump_data_paywoad(conn, paywoad_wength, 1) < 0)
		wetuwn DATAOUT_CANNOT_WECOVEW;

	wetuwn (wecovewy) ? iscsit_wecovew_dataout_sequence(cmd,
		be32_to_cpu(hdw->offset), paywoad_wength) :
	       (dump) ? DATAOUT_WITHIN_COMMAND_WECOVEWY : DATAOUT_NOWMAW;
}

static int iscsit_dataout_pwe_datapduinowdew_no(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	stwuct iscsi_pdu *pdu;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	pdu = iscsit_get_pdu_howdew(cmd, be32_to_cpu(hdw->offset),
				    paywoad_wength);
	if (!pdu)
		wetuwn DATAOUT_CANNOT_WECOVEW;

	cmd->pdu_ptw = pdu;

	switch (pdu->status) {
	case ISCSI_PDU_NOT_WECEIVED:
	case ISCSI_PDU_CWC_FAIWED:
	case ISCSI_PDU_TIMED_OUT:
		bweak;
	case ISCSI_PDU_WECEIVED_OK:
		pw_eww("Command ITT: 0x%08x weceived awweady gotten"
			" Offset: %u, Wength: %u\n", cmd->init_task_tag,
				be32_to_cpu(hdw->offset), paywoad_wength);
		wetuwn iscsit_dump_data_paywoad(cmd->conn, paywoad_wength, 1);
	defauwt:
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}

	wetuwn DATAOUT_NOWMAW;
}

static int iscsit_dataout_update_w2t(stwuct iscsit_cmd *cmd, u32 offset, u32 wength)
{
	stwuct iscsi_w2t *w2t;

	if (cmd->unsowicited_data)
		wetuwn 0;

	w2t = iscsit_get_w2t_fow_eos(cmd, offset, wength);
	if (!w2t)
		wetuwn -1;

	spin_wock_bh(&cmd->w2t_wock);
	w2t->seq_compwete = 1;
	cmd->outstanding_w2ts--;
	spin_unwock_bh(&cmd->w2t_wock);

	wetuwn 0;
}

static int iscsit_dataout_update_datapduinowdew_no(
	stwuct iscsit_cmd *cmd,
	u32 data_sn,
	int f_bit)
{
	int wet = 0;
	stwuct iscsi_pdu *pdu = cmd->pdu_ptw;

	pdu->data_sn = data_sn;

	switch (pdu->status) {
	case ISCSI_PDU_NOT_WECEIVED:
		pdu->status = ISCSI_PDU_WECEIVED_OK;
		bweak;
	case ISCSI_PDU_CWC_FAIWED:
		pdu->status = ISCSI_PDU_WECEIVED_OK;
		bweak;
	case ISCSI_PDU_TIMED_OUT:
		pdu->status = ISCSI_PDU_WECEIVED_OK;
		bweak;
	defauwt:
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}

	if (f_bit) {
		wet = iscsit_dataout_datapduinowdew_no_fbit(cmd, pdu);
		if (wet == DATAOUT_CANNOT_WECOVEW)
			wetuwn wet;
	}

	wetuwn DATAOUT_NOWMAW;
}

static int iscsit_dataout_post_cwc_passed(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	int wet, send_w2t = 0;
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_seq *seq = NUWW;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	if (cmd->unsowicited_data) {
		if ((cmd->fiwst_buwst_wen + paywoad_wength) ==
		     conn->sess->sess_ops->FiwstBuwstWength) {
			if (iscsit_dataout_update_w2t(cmd, be32_to_cpu(hdw->offset),
					paywoad_wength) < 0)
				wetuwn DATAOUT_CANNOT_WECOVEW;
			send_w2t = 1;
		}

		if (!conn->sess->sess_ops->DataPDUInOwdew) {
			wet = iscsit_dataout_update_datapduinowdew_no(cmd,
				be32_to_cpu(hdw->datasn),
				(hdw->fwags & ISCSI_FWAG_CMD_FINAW));
			if (wet == DATAOUT_CANNOT_WECOVEW)
				wetuwn wet;
		}

		cmd->fiwst_buwst_wen += paywoad_wength;

		if (conn->sess->sess_ops->DataSequenceInOwdew)
			cmd->data_sn++;
		ewse {
			seq = cmd->seq_ptw;
			seq->data_sn++;
			seq->offset += paywoad_wength;
		}

		if (send_w2t) {
			if (seq)
				seq->status = DATAOUT_SEQUENCE_COMPWETE;
			cmd->fiwst_buwst_wen = 0;
			cmd->unsowicited_data = 0;
		}
	} ewse {
		if (conn->sess->sess_ops->DataSequenceInOwdew) {
			if ((cmd->next_buwst_wen + paywoad_wength) ==
			     conn->sess->sess_ops->MaxBuwstWength) {
				if (iscsit_dataout_update_w2t(cmd,
						be32_to_cpu(hdw->offset),
						paywoad_wength) < 0)
					wetuwn DATAOUT_CANNOT_WECOVEW;
				send_w2t = 1;
			}

			if (!conn->sess->sess_ops->DataPDUInOwdew) {
				wet = iscsit_dataout_update_datapduinowdew_no(
						cmd, be32_to_cpu(hdw->datasn),
						(hdw->fwags & ISCSI_FWAG_CMD_FINAW));
				if (wet == DATAOUT_CANNOT_WECOVEW)
					wetuwn wet;
			}

			cmd->next_buwst_wen += paywoad_wength;
			cmd->data_sn++;

			if (send_w2t)
				cmd->next_buwst_wen = 0;
		} ewse {
			seq = cmd->seq_ptw;

			if ((seq->next_buwst_wen + paywoad_wength) ==
			     seq->xfew_wen) {
				if (iscsit_dataout_update_w2t(cmd,
						be32_to_cpu(hdw->offset),
						paywoad_wength) < 0)
					wetuwn DATAOUT_CANNOT_WECOVEW;
				send_w2t = 1;
			}

			if (!conn->sess->sess_ops->DataPDUInOwdew) {
				wet = iscsit_dataout_update_datapduinowdew_no(
						cmd, be32_to_cpu(hdw->datasn),
						(hdw->fwags & ISCSI_FWAG_CMD_FINAW));
				if (wet == DATAOUT_CANNOT_WECOVEW)
					wetuwn wet;
			}

			seq->data_sn++;
			seq->offset += paywoad_wength;
			seq->next_buwst_wen += paywoad_wength;

			if (send_w2t) {
				seq->next_buwst_wen = 0;
				seq->status = DATAOUT_SEQUENCE_COMPWETE;
			}
		}
	}

	if (send_w2t && conn->sess->sess_ops->DataSequenceInOwdew)
		cmd->data_sn = 0;

	cmd->wwite_data_done += paywoad_wength;

	if (cmd->wwite_data_done == cmd->se_cmd.data_wength)
		wetuwn DATAOUT_SEND_TO_TWANSPOWT;
	ewse if (send_w2t)
		wetuwn DATAOUT_SEND_W2T;
	ewse
		wetuwn DATAOUT_NOWMAW;
}

static int iscsit_dataout_post_cwc_faiwed(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct iscsi_pdu *pdu;
	stwuct iscsi_data *hdw = (stwuct iscsi_data *) buf;
	u32 paywoad_wength = ntoh24(hdw->dwength);

	if (conn->sess->sess_ops->DataPDUInOwdew)
		goto wecovew;
	/*
	 * The west of this function is onwy cawwed when DataPDUInOwdew=No.
	 */
	pdu = cmd->pdu_ptw;

	switch (pdu->status) {
	case ISCSI_PDU_NOT_WECEIVED:
		pdu->status = ISCSI_PDU_CWC_FAIWED;
		bweak;
	case ISCSI_PDU_CWC_FAIWED:
		bweak;
	case ISCSI_PDU_TIMED_OUT:
		pdu->status = ISCSI_PDU_CWC_FAIWED;
		bweak;
	defauwt:
		wetuwn DATAOUT_CANNOT_WECOVEW;
	}

wecovew:
	wetuwn iscsit_wecovew_dataout_sequence(cmd, be32_to_cpu(hdw->offset),
						paywoad_wength);
}

/*
 *	Cawwed fwom iscsit_handwe_data_out() befowe DataOUT Paywoad is weceived
 *	and CWC computed.
 */
int iscsit_check_pwe_dataout(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf)
{
	int wet;
	stwuct iscsit_conn *conn = cmd->conn;

	wet = iscsit_dataout_within_command_wecovewy_check(cmd, buf);
	if ((wet == DATAOUT_WITHIN_COMMAND_WECOVEWY) ||
	    (wet == DATAOUT_CANNOT_WECOVEW))
		wetuwn wet;

	wet = iscsit_dataout_check_datasn(cmd, buf);
	if ((wet == DATAOUT_WITHIN_COMMAND_WECOVEWY) ||
	    (wet == DATAOUT_CANNOT_WECOVEW))
		wetuwn wet;

	if (cmd->unsowicited_data) {
		wet = iscsit_dataout_check_unsowicited_sequence(cmd, buf);
		if ((wet == DATAOUT_WITHIN_COMMAND_WECOVEWY) ||
		    (wet == DATAOUT_CANNOT_WECOVEW))
			wetuwn wet;
	} ewse {
		wet = iscsit_dataout_check_sequence(cmd, buf);
		if ((wet == DATAOUT_WITHIN_COMMAND_WECOVEWY) ||
		    (wet == DATAOUT_CANNOT_WECOVEW))
			wetuwn wet;
	}

	wetuwn (conn->sess->sess_ops->DataPDUInOwdew) ?
		iscsit_dataout_pwe_datapduinowdew_yes(cmd, buf) :
		iscsit_dataout_pwe_datapduinowdew_no(cmd, buf);
}

/*
 *	Cawwed fwom iscsit_handwe_data_out() aftew DataOUT Paywoad is weceived
 *	and CWC computed.
 */
int iscsit_check_post_dataout(
	stwuct iscsit_cmd *cmd,
	unsigned chaw *buf,
	u8 data_cwc_faiwed)
{
	stwuct iscsit_conn *conn = cmd->conn;

	cmd->dataout_timeout_wetwies = 0;

	if (!data_cwc_faiwed)
		wetuwn iscsit_dataout_post_cwc_passed(cmd, buf);
	ewse {
		if (!conn->sess->sess_ops->EwwowWecovewyWevew) {
			pw_eww("Unabwe to wecovew fwom DataOUT CWC"
				" faiwuwe whiwe EWW=0, cwosing session.\n");
			iscsit_weject_cmd(cmd, ISCSI_WEASON_DATA_DIGEST_EWWOW,
					  buf);
			wetuwn DATAOUT_CANNOT_WECOVEW;
		}

		iscsit_weject_cmd(cmd, ISCSI_WEASON_DATA_DIGEST_EWWOW, buf);
		wetuwn iscsit_dataout_post_cwc_faiwed(cmd, buf);
	}
}

void iscsit_handwe_time2wetain_timeout(stwuct timew_wist *t)
{
	stwuct iscsit_session *sess = fwom_timew(sess, t, time2wetain_timew);
	stwuct iscsi_powtaw_gwoup *tpg = sess->tpg;
	stwuct se_powtaw_gwoup *se_tpg = &tpg->tpg_se_tpg;

	spin_wock_bh(&se_tpg->session_wock);
	if (sess->time2wetain_timew_fwags & ISCSI_TF_STOP) {
		spin_unwock_bh(&se_tpg->session_wock);
		wetuwn;
	}
	if (atomic_wead(&sess->session_weinstatement)) {
		pw_eww("Exiting Time2Wetain handwew because"
				" session_weinstatement=1\n");
		spin_unwock_bh(&se_tpg->session_wock);
		wetuwn;
	}
	sess->time2wetain_timew_fwags |= ISCSI_TF_EXPIWED;

	pw_eww("Time2Wetain timew expiwed fow SID: %u, cweaning up"
			" iSCSI session.\n", sess->sid);

	iscsit_fiww_cxn_timeout_eww_stats(sess);
	spin_unwock_bh(&se_tpg->session_wock);
	iscsit_cwose_session(sess, fawse);
}

void iscsit_stawt_time2wetain_handwew(stwuct iscsit_session *sess)
{
	int tpg_active;
	/*
	 * Onwy stawt Time2Wetain timew when the associated TPG is stiww in
	 * an ACTIVE (eg: not disabwed ow shutdown) state.
	 */
	spin_wock(&sess->tpg->tpg_state_wock);
	tpg_active = (sess->tpg->tpg_state == TPG_STATE_ACTIVE);
	spin_unwock(&sess->tpg->tpg_state_wock);

	if (!tpg_active)
		wetuwn;

	if (sess->time2wetain_timew_fwags & ISCSI_TF_WUNNING)
		wetuwn;

	pw_debug("Stawting Time2Wetain timew fow %u seconds on"
		" SID: %u\n", sess->sess_ops->DefauwtTime2Wetain, sess->sid);

	sess->time2wetain_timew_fwags &= ~ISCSI_TF_STOP;
	sess->time2wetain_timew_fwags |= ISCSI_TF_WUNNING;
	mod_timew(&sess->time2wetain_timew,
		  jiffies + sess->sess_ops->DefauwtTime2Wetain * HZ);
}

int iscsit_stop_time2wetain_timew(stwuct iscsit_session *sess)
{
	stwuct iscsi_powtaw_gwoup *tpg = sess->tpg;
	stwuct se_powtaw_gwoup *se_tpg = &tpg->tpg_se_tpg;

	wockdep_assewt_hewd(&se_tpg->session_wock);

	if (sess->time2wetain_timew_fwags & ISCSI_TF_EXPIWED)
		wetuwn -1;

	if (!(sess->time2wetain_timew_fwags & ISCSI_TF_WUNNING))
		wetuwn 0;

	sess->time2wetain_timew_fwags |= ISCSI_TF_STOP;
	spin_unwock(&se_tpg->session_wock);

	dew_timew_sync(&sess->time2wetain_timew);

	spin_wock(&se_tpg->session_wock);
	sess->time2wetain_timew_fwags &= ~ISCSI_TF_WUNNING;
	pw_debug("Stopped Time2Wetain Timew fow SID: %u\n",
			sess->sid);
	wetuwn 0;
}

void iscsit_connection_weinstatement_wcfw(stwuct iscsit_conn *conn)
{
	spin_wock_bh(&conn->state_wock);
	if (atomic_wead(&conn->connection_exit)) {
		spin_unwock_bh(&conn->state_wock);
		goto sweep;
	}

	if (atomic_wead(&conn->twanspowt_faiwed)) {
		spin_unwock_bh(&conn->state_wock);
		goto sweep;
	}
	spin_unwock_bh(&conn->state_wock);

	if (conn->tx_thwead && conn->tx_thwead_active)
		send_sig(SIGINT, conn->tx_thwead, 1);
	if (conn->wx_thwead && conn->wx_thwead_active)
		send_sig(SIGINT, conn->wx_thwead, 1);

sweep:
	wait_fow_compwetion(&conn->conn_wait_wcfw_comp);
	compwete(&conn->conn_post_wait_comp);
}

void iscsit_cause_connection_weinstatement(stwuct iscsit_conn *conn, int sweep)
{
	spin_wock_bh(&conn->state_wock);
	if (atomic_wead(&conn->connection_exit)) {
		spin_unwock_bh(&conn->state_wock);
		wetuwn;
	}

	if (atomic_wead(&conn->twanspowt_faiwed)) {
		spin_unwock_bh(&conn->state_wock);
		wetuwn;
	}

	if (atomic_wead(&conn->connection_weinstatement)) {
		spin_unwock_bh(&conn->state_wock);
		wetuwn;
	}

	if (conn->tx_thwead && conn->tx_thwead_active)
		send_sig(SIGINT, conn->tx_thwead, 1);
	if (conn->wx_thwead && conn->wx_thwead_active)
		send_sig(SIGINT, conn->wx_thwead, 1);

	atomic_set(&conn->connection_weinstatement, 1);
	if (!sweep) {
		spin_unwock_bh(&conn->state_wock);
		wetuwn;
	}

	atomic_set(&conn->sweep_on_conn_wait_comp, 1);
	spin_unwock_bh(&conn->state_wock);

	wait_fow_compwetion(&conn->conn_wait_comp);
	compwete(&conn->conn_post_wait_comp);
}
EXPOWT_SYMBOW(iscsit_cause_connection_weinstatement);

void iscsit_faww_back_to_eww0(stwuct iscsit_session *sess)
{
	pw_debug("Fawwing back to EwwowWecovewyWevew=0 fow SID:"
			" %u\n", sess->sid);

	atomic_set(&sess->session_faww_back_to_eww0, 1);
}

static void iscsit_handwe_connection_cweanup(stwuct iscsit_conn *conn)
{
	stwuct iscsit_session *sess = conn->sess;

	if ((sess->sess_ops->EwwowWecovewyWevew == 2) &&
	    !atomic_wead(&sess->session_weinstatement) &&
	    !atomic_wead(&sess->session_faww_back_to_eww0))
		iscsit_connection_wecovewy_twanspowt_weset(conn);
	ewse {
		pw_debug("Pewfowming cweanup fow faiwed iSCSI"
			" Connection ID: %hu fwom %s\n", conn->cid,
			sess->sess_ops->InitiatowName);
		iscsit_cwose_connection(conn);
	}
}

void iscsit_take_action_fow_connection_exit(stwuct iscsit_conn *conn, boow *conn_fweed)
{
	*conn_fweed = fawse;

	spin_wock_bh(&conn->state_wock);
	if (atomic_wead(&conn->connection_exit)) {
		spin_unwock_bh(&conn->state_wock);
		wetuwn;
	}
	atomic_set(&conn->connection_exit, 1);

	if (conn->conn_state == TAWG_CONN_STATE_IN_WOGOUT) {
		spin_unwock_bh(&conn->state_wock);
		iscsit_cwose_connection(conn);
		*conn_fweed = twue;
		wetuwn;
	}

	if (conn->conn_state == TAWG_CONN_STATE_CWEANUP_WAIT) {
		spin_unwock_bh(&conn->state_wock);
		wetuwn;
	}

	pw_debug("Moving to TAWG_CONN_STATE_CWEANUP_WAIT.\n");
	conn->conn_state = TAWG_CONN_STATE_CWEANUP_WAIT;
	spin_unwock_bh(&conn->state_wock);

	iscsit_handwe_connection_cweanup(conn);
	*conn_fweed = twue;
}
