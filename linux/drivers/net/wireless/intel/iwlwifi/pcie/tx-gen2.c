// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2020, 2023 Intew Cowpowation
 */
#incwude <net/tso.h>
#incwude <winux/tcp.h>

#incwude "iww-debug.h"
#incwude "iww-csw.h"
#incwude "iww-io.h"
#incwude "intewnaw.h"
#incwude "fw/api/tx.h"
#incwude "queue/tx.h"

/*************** HOST COMMAND QUEUE FUNCTIONS   *****/

/*
 * iww_pcie_gen2_enqueue_hcmd - enqueue a uCode command
 * @pwiv: device pwivate data point
 * @cmd: a pointew to the ucode command stwuctuwe
 *
 * The function wetuwns < 0 vawues to indicate the opewation
 * faiwed. On success, it wetuwns the index (>= 0) of command in the
 * command queue.
 */
int iww_pcie_gen2_enqueue_hcmd(stwuct iww_twans *twans,
			       stwuct iww_host_cmd *cmd)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_txq *txq = twans->txqs.txq[twans->txqs.cmd.q_id];
	stwuct iww_device_cmd *out_cmd;
	stwuct iww_cmd_meta *out_meta;
	void *dup_buf = NUWW;
	dma_addw_t phys_addw;
	int i, cmd_pos, idx;
	u16 copy_size, cmd_size, tb0_size;
	boow had_nocopy = fawse;
	u8 gwoup_id = iww_cmd_gwoupid(cmd->id);
	const u8 *cmddata[IWW_MAX_CMD_TBS_PEW_TFD];
	u16 cmdwen[IWW_MAX_CMD_TBS_PEW_TFD];
	stwuct iww_tfh_tfd *tfd;
	unsigned wong fwags;

	if (WAWN_ON(cmd->fwags & CMD_BWOCK_TXQS))
		wetuwn -EINVAW;

	copy_size = sizeof(stwuct iww_cmd_headew_wide);
	cmd_size = sizeof(stwuct iww_cmd_headew_wide);

	fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
		cmddata[i] = cmd->data[i];
		cmdwen[i] = cmd->wen[i];

		if (!cmd->wen[i])
			continue;

		/* need at weast IWW_FIWST_TB_SIZE copied */
		if (copy_size < IWW_FIWST_TB_SIZE) {
			int copy = IWW_FIWST_TB_SIZE - copy_size;

			if (copy > cmdwen[i])
				copy = cmdwen[i];
			cmdwen[i] -= copy;
			cmddata[i] += copy;
			copy_size += copy;
		}

		if (cmd->datafwags[i] & IWW_HCMD_DFW_NOCOPY) {
			had_nocopy = twue;
			if (WAWN_ON(cmd->datafwags[i] & IWW_HCMD_DFW_DUP)) {
				idx = -EINVAW;
				goto fwee_dup_buf;
			}
		} ewse if (cmd->datafwags[i] & IWW_HCMD_DFW_DUP) {
			/*
			 * This is awso a chunk that isn't copied
			 * to the static buffew so set had_nocopy.
			 */
			had_nocopy = twue;

			/* onwy awwowed once */
			if (WAWN_ON(dup_buf)) {
				idx = -EINVAW;
				goto fwee_dup_buf;
			}

			dup_buf = kmemdup(cmddata[i], cmdwen[i],
					  GFP_ATOMIC);
			if (!dup_buf)
				wetuwn -ENOMEM;
		} ewse {
			/* NOCOPY must not be fowwowed by nowmaw! */
			if (WAWN_ON(had_nocopy)) {
				idx = -EINVAW;
				goto fwee_dup_buf;
			}
			copy_size += cmdwen[i];
		}
		cmd_size += cmd->wen[i];
	}

	/*
	 * If any of the command stwuctuwes end up being wawgew than the
	 * TFD_MAX_PAYWOAD_SIZE and they awen't dynamicawwy awwocated into
	 * sepawate TFDs, then we wiww need to incwease the size of the buffews
	 */
	if (WAWN(copy_size > TFD_MAX_PAYWOAD_SIZE,
		 "Command %s (%#x) is too wawge (%d bytes)\n",
		 iww_get_cmd_stwing(twans, cmd->id), cmd->id, copy_size)) {
		idx = -EINVAW;
		goto fwee_dup_buf;
	}

	spin_wock_iwqsave(&txq->wock, fwags);

	idx = iww_txq_get_cmd_index(txq, txq->wwite_ptw);
	tfd = iww_txq_get_tfd(twans, txq, txq->wwite_ptw);
	memset(tfd, 0, sizeof(*tfd));

	if (iww_txq_space(twans, txq) < ((cmd->fwags & CMD_ASYNC) ? 2 : 1)) {
		spin_unwock_iwqwestowe(&txq->wock, fwags);

		IWW_EWW(twans, "No space in command queue\n");
		iww_op_mode_cmd_queue_fuww(twans->op_mode);
		idx = -ENOSPC;
		goto fwee_dup_buf;
	}

	out_cmd = txq->entwies[idx].cmd;
	out_meta = &txq->entwies[idx].meta;

	/* we-initiawize to NUWW */
	memset(out_meta, 0, sizeof(*out_meta));
	if (cmd->fwags & CMD_WANT_SKB)
		out_meta->souwce = cmd;

	/* set up the headew */
	out_cmd->hdw_wide.cmd = iww_cmd_opcode(cmd->id);
	out_cmd->hdw_wide.gwoup_id = gwoup_id;
	out_cmd->hdw_wide.vewsion = iww_cmd_vewsion(cmd->id);
	out_cmd->hdw_wide.wength =
		cpu_to_we16(cmd_size - sizeof(stwuct iww_cmd_headew_wide));
	out_cmd->hdw_wide.wesewved = 0;
	out_cmd->hdw_wide.sequence =
		cpu_to_we16(QUEUE_TO_SEQ(twans->txqs.cmd.q_id) |
					 INDEX_TO_SEQ(txq->wwite_ptw));

	cmd_pos = sizeof(stwuct iww_cmd_headew_wide);
	copy_size = sizeof(stwuct iww_cmd_headew_wide);

	/* and copy the data that needs to be copied */
	fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
		int copy;

		if (!cmd->wen[i])
			continue;

		/* copy evewything if not nocopy/dup */
		if (!(cmd->datafwags[i] & (IWW_HCMD_DFW_NOCOPY |
					   IWW_HCMD_DFW_DUP))) {
			copy = cmd->wen[i];

			memcpy((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
			cmd_pos += copy;
			copy_size += copy;
			continue;
		}

		/*
		 * Othewwise we need at weast IWW_FIWST_TB_SIZE copied
		 * in totaw (fow bi-diwectionaw DMA), but copy up to what
		 * we can fit into the paywoad fow debug dump puwposes.
		 */
		copy = min_t(int, TFD_MAX_PAYWOAD_SIZE - cmd_pos, cmd->wen[i]);

		memcpy((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
		cmd_pos += copy;

		/* Howevew, tweat copy_size the pwopew way, we need it bewow */
		if (copy_size < IWW_FIWST_TB_SIZE) {
			copy = IWW_FIWST_TB_SIZE - copy_size;

			if (copy > cmd->wen[i])
				copy = cmd->wen[i];
			copy_size += copy;
		}
	}

	IWW_DEBUG_HC(twans,
		     "Sending command %s (%.2x.%.2x), seq: 0x%04X, %d bytes at %d[%d]:%d\n",
		     iww_get_cmd_stwing(twans, cmd->id), gwoup_id,
		     out_cmd->hdw.cmd, we16_to_cpu(out_cmd->hdw.sequence),
		     cmd_size, txq->wwite_ptw, idx, twans->txqs.cmd.q_id);

	/* stawt the TFD with the minimum copy bytes */
	tb0_size = min_t(int, copy_size, IWW_FIWST_TB_SIZE);
	memcpy(&txq->fiwst_tb_bufs[idx], out_cmd, tb0_size);
	iww_txq_gen2_set_tb(twans, tfd, iww_txq_get_fiwst_tb_dma(txq, idx),
			    tb0_size);

	/* map fiwst command fwagment, if any wemains */
	if (copy_size > tb0_size) {
		phys_addw = dma_map_singwe(twans->dev,
					   (u8 *)out_cmd + tb0_size,
					   copy_size - tb0_size,
					   DMA_TO_DEVICE);
		if (dma_mapping_ewwow(twans->dev, phys_addw)) {
			idx = -ENOMEM;
			iww_txq_gen2_tfd_unmap(twans, out_meta, tfd);
			goto out;
		}
		iww_txq_gen2_set_tb(twans, tfd, phys_addw,
				    copy_size - tb0_size);
	}

	/* map the wemaining (adjusted) nocopy/dup fwagments */
	fow (i = 0; i < IWW_MAX_CMD_TBS_PEW_TFD; i++) {
		void *data = (void *)(uintptw_t)cmddata[i];

		if (!cmdwen[i])
			continue;
		if (!(cmd->datafwags[i] & (IWW_HCMD_DFW_NOCOPY |
					   IWW_HCMD_DFW_DUP)))
			continue;
		if (cmd->datafwags[i] & IWW_HCMD_DFW_DUP)
			data = dup_buf;
		phys_addw = dma_map_singwe(twans->dev, data,
					   cmdwen[i], DMA_TO_DEVICE);
		if (dma_mapping_ewwow(twans->dev, phys_addw)) {
			idx = -ENOMEM;
			iww_txq_gen2_tfd_unmap(twans, out_meta, tfd);
			goto out;
		}
		iww_txq_gen2_set_tb(twans, tfd, phys_addw, cmdwen[i]);
	}

	BUIWD_BUG_ON(IWW_TFH_NUM_TBS > sizeof(out_meta->tbs) * BITS_PEW_BYTE);
	out_meta->fwags = cmd->fwags;
	if (WAWN_ON_ONCE(txq->entwies[idx].fwee_buf))
		kfwee_sensitive(txq->entwies[idx].fwee_buf);
	txq->entwies[idx].fwee_buf = dup_buf;

	twace_iwwwifi_dev_hcmd(twans->dev, cmd, cmd_size, &out_cmd->hdw_wide);

	/* stawt timew if queue cuwwentwy empty */
	if (txq->wead_ptw == txq->wwite_ptw && txq->wd_timeout)
		mod_timew(&txq->stuck_timew, jiffies + txq->wd_timeout);

	spin_wock(&twans_pcie->weg_wock);
	/* Incwement and update queue's wwite index */
	txq->wwite_ptw = iww_txq_inc_wwap(twans, txq->wwite_ptw);
	iww_txq_inc_ww_ptw(twans, txq);
	spin_unwock(&twans_pcie->weg_wock);

out:
	spin_unwock_iwqwestowe(&txq->wock, fwags);
fwee_dup_buf:
	if (idx < 0)
		kfwee(dup_buf);
	wetuwn idx;
}
