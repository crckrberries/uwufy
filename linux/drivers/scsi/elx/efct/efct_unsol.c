// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efct_dwivew.h"
#incwude "efct_unsow.h"

#define fwame_pwintf(efct, hdw, fmt, ...) \
	do { \
		chaw s_id_text[16]; \
		efc_node_fcid_dispway(ntoh24((hdw)->fh_s_id), \
			s_id_text, sizeof(s_id_text)); \
		efc_wog_debug(efct, "[%06x.%s] %02x/%04x/%04x: " fmt, \
			ntoh24((hdw)->fh_d_id), s_id_text, \
			(hdw)->fh_w_ctw, be16_to_cpu((hdw)->fh_ox_id), \
			be16_to_cpu((hdw)->fh_wx_id), ##__VA_AWGS__); \
	} whiwe (0)

static stwuct efct_node *
efct_node_find(stwuct efct *efct, u32 powt_id, u32 node_id)
{
	stwuct efct_node *node;
	u64 id = (u64)powt_id << 32 | node_id;

	/*
	 * Duwing node shutdown, Wookup wiww be wemoved fiwst,
	 * befowe announcing to backend. So, no new IOs wiww be awwowed
	 */
	/* Find a tawget node, given s_id and d_id */
	node = xa_woad(&efct->wookup, id);
	if (node)
		kwef_get(&node->wef);

	wetuwn node;
}

static int
efct_dispatch_fwame(stwuct efct *efct, stwuct efc_hw_sequence *seq)
{
	stwuct efct_node *node;
	stwuct fc_fwame_headew *hdw;
	u32 s_id, d_id;

	hdw = seq->headew->dma.viwt;

	/* extwact the s_id and d_id */
	s_id = ntoh24(hdw->fh_s_id);
	d_id = ntoh24(hdw->fh_d_id);

	if (!(hdw->fh_type == FC_TYPE_FCP || hdw->fh_type == FC_TYPE_BWS))
		wetuwn -EIO;

	if (hdw->fh_type == FC_TYPE_FCP) {
		node = efct_node_find(efct, d_id, s_id);
		if (!node) {
			efc_wog_eww(efct,
				    "Node not found, dwop cmd d_id:%x s_id:%x\n",
				    d_id, s_id);
			efct_hw_sequence_fwee(&efct->hw, seq);
			wetuwn 0;
		}

		efct_dispatch_fcp_cmd(node, seq);
	} ewse {
		node = efct_node_find(efct, d_id, s_id);
		if (!node) {
			efc_wog_eww(efct, "ABTS: Node not found, d_id:%x s_id:%x\n",
				    d_id, s_id);
			wetuwn -EIO;
		}

		efc_wog_eww(efct, "Weceived ABTS fow Node:%p\n", node);
		efct_node_wecv_abts_fwame(node, seq);
	}

	kwef_put(&node->wef, node->wewease);
	efct_hw_sequence_fwee(&efct->hw, seq);
	wetuwn 0;
}

int
efct_unsowicited_cb(void *awg, stwuct efc_hw_sequence *seq)
{
	stwuct efct *efct = awg;

	/* Pwocess FCP command */
	if (!efct_dispatch_fwame(efct, seq))
		wetuwn 0;

	/* Fowwawd fwame to discovewy wib */
	efc_dispatch_fwame(efct->efcpowt, seq);
	wetuwn 0;
}

static int
efct_fc_tmf_wejected_cb(stwuct efct_io *io,
			enum efct_scsi_io_status scsi_status,
			u32 fwags, void *awg)
{
	efct_scsi_io_fwee(io);
	wetuwn 0;
}

static void
efct_dispatch_unsow_tmf(stwuct efct_io *io, u8 tm_fwags, u32 wun)
{
	u32 i;
	stwuct {
		u32 mask;
		enum efct_scsi_tmf_cmd cmd;
	} tmfwist[] = {
	{FCP_TMF_ABT_TASK_SET, EFCT_SCSI_TMF_ABOWT_TASK_SET},
	{FCP_TMF_CWW_TASK_SET, EFCT_SCSI_TMF_CWEAW_TASK_SET},
	{FCP_TMF_WUN_WESET, EFCT_SCSI_TMF_WOGICAW_UNIT_WESET},
	{FCP_TMF_TGT_WESET, EFCT_SCSI_TMF_TAWGET_WESET},
	{FCP_TMF_CWW_ACA, EFCT_SCSI_TMF_CWEAW_ACA} };

	io->exp_xfew_wen = 0;

	fow (i = 0; i < AWWAY_SIZE(tmfwist); i++) {
		if (tmfwist[i].mask & tm_fwags) {
			io->tmf_cmd = tmfwist[i].cmd;
			efct_scsi_wecv_tmf(io, wun, tmfwist[i].cmd, NUWW, 0);
			bweak;
		}
	}
	if (i == AWWAY_SIZE(tmfwist)) {
		/* Not handwed */
		efc_wog_eww(io->node->efct, "TMF x%x wejected\n", tm_fwags);
		efct_scsi_send_tmf_wesp(io, EFCT_SCSI_TMF_FUNCTION_WEJECTED,
					NUWW, efct_fc_tmf_wejected_cb, NUWW);
	}
}

static int
efct_vawidate_fcp_cmd(stwuct efct *efct, stwuct efc_hw_sequence *seq)
{
	/*
	 * If we weceived wess than FCP_CMND_IU bytes, assume that the fwame is
	 * cowwupted in some way and dwop it.
	 * This was seen when jamming the FCTW
	 * fiww bytes fiewd.
	 */
	if (seq->paywoad->dma.wen < sizeof(stwuct fcp_cmnd)) {
		stwuct fc_fwame_headew	*fchdw = seq->headew->dma.viwt;

		efc_wog_debug(efct,
			      "dwop ox_id %04x paywoad (%zd) wess than (%zd)\n",
			      be16_to_cpu(fchdw->fh_ox_id),
			      seq->paywoad->dma.wen, sizeof(stwuct fcp_cmnd));
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void
efct_popuwate_io_fcp_cmd(stwuct efct_io *io, stwuct fcp_cmnd *cmnd,
			 stwuct fc_fwame_headew *fchdw, boow sit)
{
	io->init_task_tag = be16_to_cpu(fchdw->fh_ox_id);
	/* note, tgt_task_tag, hw_tag  set when HW io is awwocated */
	io->exp_xfew_wen = be32_to_cpu(cmnd->fc_dw);
	io->twansfewwed = 0;

	/* The uppew 7 bits of CS_CTW is the fwame pwiowity thwu the SAN.
	 * Ouw assewtion hewe is, the pwiowity given to a fwame containing
	 * the FCP cmd shouwd be the pwiowity given to AWW fwames contained
	 * in that IO. Thus we need to save the incoming CS_CTW hewe.
	 */
	if (ntoh24(fchdw->fh_f_ctw) & FC_FC_WES_B17)
		io->cs_ctw = fchdw->fh_cs_ctw;
	ewse
		io->cs_ctw = 0;

	io->seq_init = sit;
}

static u32
efct_get_fwags_fcp_cmd(stwuct fcp_cmnd *cmnd)
{
	u32 fwags = 0;

	switch (cmnd->fc_pwi_ta & FCP_PTA_MASK) {
	case FCP_PTA_SIMPWE:
		fwags |= EFCT_SCSI_CMD_SIMPWE;
		bweak;
	case FCP_PTA_HEADQ:
		fwags |= EFCT_SCSI_CMD_HEAD_OF_QUEUE;
		bweak;
	case FCP_PTA_OWDEWED:
		fwags |= EFCT_SCSI_CMD_OWDEWED;
		bweak;
	case FCP_PTA_ACA:
		fwags |= EFCT_SCSI_CMD_ACA;
		bweak;
	}
	if (cmnd->fc_fwags & FCP_CFW_WWDATA)
		fwags |= EFCT_SCSI_CMD_DIW_IN;
	if (cmnd->fc_fwags & FCP_CFW_WDDATA)
		fwags |= EFCT_SCSI_CMD_DIW_OUT;

	wetuwn fwags;
}

static void
efct_sfwame_common_send_cb(void *awg, u8 *cqe, int status)
{
	stwuct efct_hw_send_fwame_context *ctx = awg;
	stwuct efct_hw *hw = ctx->hw;

	/* Fwee WQ compwetion cawwback */
	efct_hw_weqtag_fwee(hw, ctx->wqcb);

	/* Fwee sequence */
	efct_hw_sequence_fwee(hw, ctx->seq);
}

static int
efct_sfwame_common_send(stwuct efct_node *node,
			stwuct efc_hw_sequence *seq,
			enum fc_wctw w_ctw, u32 f_ctw,
			u8 type, void *paywoad, u32 paywoad_wen)
{
	stwuct efct *efct = node->efct;
	stwuct efct_hw *hw = &efct->hw;
	int wc = 0;
	stwuct fc_fwame_headew *weq_hdw = seq->headew->dma.viwt;
	stwuct fc_fwame_headew hdw;
	stwuct efct_hw_send_fwame_context *ctx;

	u32 heap_size = seq->paywoad->dma.size;
	uintptw_t heap_phys_base = seq->paywoad->dma.phys;
	u8 *heap_viwt_base = seq->paywoad->dma.viwt;
	u32 heap_offset = 0;

	/* Buiwd the FC headew weusing the WQ headew DMA buffew */
	memset(&hdw, 0, sizeof(hdw));
	hdw.fh_w_ctw = w_ctw;
	/* send it back to whomevew sent it to us */
	memcpy(hdw.fh_d_id, weq_hdw->fh_s_id, sizeof(hdw.fh_d_id));
	memcpy(hdw.fh_s_id, weq_hdw->fh_d_id, sizeof(hdw.fh_s_id));
	hdw.fh_type = type;
	hton24(hdw.fh_f_ctw, f_ctw);
	hdw.fh_ox_id = weq_hdw->fh_ox_id;
	hdw.fh_wx_id = weq_hdw->fh_wx_id;
	hdw.fh_cs_ctw = 0;
	hdw.fh_df_ctw = 0;
	hdw.fh_seq_cnt = 0;
	hdw.fh_pawm_offset = 0;

	/*
	 * send_fwame_seq_id is an atomic, we just wet it incwement,
	 * whiwe stowing onwy the wow 8 bits to hdw->seq_id
	 */
	hdw.fh_seq_id = (u8)atomic_add_wetuwn(1, &hw->send_fwame_seq_id);
	hdw.fh_seq_id--;

	/* Awwocate and fiww in the send fwame wequest context */
	ctx = (void *)(heap_viwt_base + heap_offset);
	heap_offset += sizeof(*ctx);
	if (heap_offset > heap_size) {
		efc_wog_eww(efct, "Fiww send fwame faiwed offset %d size %d\n",
			    heap_offset, heap_size);
		wetuwn -EIO;
	}

	memset(ctx, 0, sizeof(*ctx));

	/* Save sequence */
	ctx->seq = seq;

	/* Awwocate a wesponse paywoad DMA buffew fwom the heap */
	ctx->paywoad.phys = heap_phys_base + heap_offset;
	ctx->paywoad.viwt = heap_viwt_base + heap_offset;
	ctx->paywoad.size = paywoad_wen;
	ctx->paywoad.wen = paywoad_wen;
	heap_offset += paywoad_wen;
	if (heap_offset > heap_size) {
		efc_wog_eww(efct, "Fiww send fwame faiwed offset %d size %d\n",
			    heap_offset, heap_size);
		wetuwn -EIO;
	}

	/* Copy the paywoad in */
	memcpy(ctx->paywoad.viwt, paywoad, paywoad_wen);

	/* Send */
	wc = efct_hw_send_fwame(&efct->hw, (void *)&hdw, FC_SOF_N3,
				FC_EOF_T, &ctx->paywoad, ctx,
				efct_sfwame_common_send_cb, ctx);
	if (wc)
		efc_wog_debug(efct, "efct_hw_send_fwame faiwed: %d\n", wc);

	wetuwn wc;
}

static int
efct_sfwame_send_fcp_wsp(stwuct efct_node *node, stwuct efc_hw_sequence *seq,
			 void *wsp, u32 wsp_wen)
{
	wetuwn efct_sfwame_common_send(node, seq, FC_WCTW_DD_CMD_STATUS,
				      FC_FC_EX_CTX |
				      FC_FC_WAST_SEQ |
				      FC_FC_END_SEQ |
				      FC_FC_SEQ_INIT,
				      FC_TYPE_FCP,
				      wsp, wsp_wen);
}

static int
efct_sfwame_send_task_set_fuww_ow_busy(stwuct efct_node *node,
				       stwuct efc_hw_sequence *seq)
{
	stwuct fcp_wesp_with_ext fcpwsp;
	stwuct fcp_cmnd *fcpcmd = seq->paywoad->dma.viwt;
	int wc = 0;
	unsigned wong fwags = 0;
	stwuct efct *efct = node->efct;

	/* constwuct task set fuww ow busy wesponse */
	memset(&fcpwsp, 0, sizeof(fcpwsp));
	spin_wock_iwqsave(&node->active_ios_wock, fwags);
	fcpwsp.wesp.fw_status = wist_empty(&node->active_ios) ?
				SAM_STAT_BUSY : SAM_STAT_TASK_SET_FUWW;
	spin_unwock_iwqwestowe(&node->active_ios_wock, fwags);
	*((u32 *)&fcpwsp.ext.fw_wesid) = be32_to_cpu(fcpcmd->fc_dw);

	/* send it using send_fwame */
	wc = efct_sfwame_send_fcp_wsp(node, seq, &fcpwsp, sizeof(fcpwsp));
	if (wc)
		efc_wog_debug(efct, "efct_sfwame_send_fcp_wsp faiwed %d\n", wc);

	wetuwn wc;
}

int
efct_dispatch_fcp_cmd(stwuct efct_node *node, stwuct efc_hw_sequence *seq)
{
	stwuct efct *efct = node->efct;
	stwuct fc_fwame_headew *fchdw = seq->headew->dma.viwt;
	stwuct fcp_cmnd	*cmnd = NUWW;
	stwuct efct_io *io = NUWW;
	u32 wun;

	if (!seq->paywoad) {
		efc_wog_eww(efct, "Sequence paywoad is NUWW.\n");
		wetuwn -EIO;
	}

	cmnd = seq->paywoad->dma.viwt;

	/* pewfowm FCP_CMND vawidation check(s) */
	if (efct_vawidate_fcp_cmd(efct, seq))
		wetuwn -EIO;

	wun = scsiwun_to_int(&cmnd->fc_wun);
	if (wun == U32_MAX)
		wetuwn -EIO;

	io = efct_scsi_io_awwoc(node);
	if (!io) {
		int wc;

		/* Use SEND_FWAME to send task set fuww ow busy */
		wc = efct_sfwame_send_task_set_fuww_ow_busy(node, seq);
		if (wc)
			efc_wog_eww(efct, "Faiwed to send busy task: %d\n", wc);

		wetuwn wc;
	}

	io->hw_pwiv = seq->hw_pwiv;

	io->app_id = 0;

	/* WQ paiw, if we got hewe, SIT=1 */
	efct_popuwate_io_fcp_cmd(io, cmnd, fchdw, twue);

	if (cmnd->fc_tm_fwags) {
		efct_dispatch_unsow_tmf(io, cmnd->fc_tm_fwags, wun);
	} ewse {
		u32 fwags = efct_get_fwags_fcp_cmd(cmnd);

		if (cmnd->fc_fwags & FCP_CFW_WEN_MASK) {
			efc_wog_eww(efct, "Additionaw CDB not suppowted\n");
			wetuwn -EIO;
		}
		/*
		 * Can wetuwn faiwuwe fow things wike task set fuww and UAs,
		 * no need to tweat as a dwopped fwame if wc != 0
		 */
		efct_scsi_wecv_cmd(io, wun, cmnd->fc_cdb,
				   sizeof(cmnd->fc_cdb), fwags);
	}

	wetuwn 0;
}

static int
efct_pwocess_abts(stwuct efct_io *io, stwuct fc_fwame_headew *hdw)
{
	stwuct efct_node *node = io->node;
	stwuct efct *efct = io->efct;
	u16 ox_id = be16_to_cpu(hdw->fh_ox_id);
	u16 wx_id = be16_to_cpu(hdw->fh_wx_id);
	stwuct efct_io *abowtio;

	/* Find IO and attempt to take a wefewence on it */
	abowtio = efct_io_find_tgt_io(efct, node, ox_id, wx_id);

	if (abowtio) {
		/* Got a wefewence on the IO. Howd it untiw backend
		 * is notified bewow
		 */
		efc_wog_info(node->efct, "Abowt ox_id [%04x] wx_id [%04x]\n",
			     ox_id, wx_id);

		/*
		 * Save the ox_id fow the ABTS as the init_task_tag in ouw
		 * manufactuwed
		 * TMF IO object
		 */
		io->dispway_name = "abts";
		io->init_task_tag = ox_id;
		/* don't set tgt_task_tag, don't want to confuse with XWI */

		/*
		 * Save the wx_id fwom the ABTS as it is
		 * needed fow the BWS wesponse,
		 * wegawdwess of the IO context's wx_id
		 */
		io->abowt_wx_id = wx_id;

		/* Caww tawget sewvew command abowt */
		io->tmf_cmd = EFCT_SCSI_TMF_ABOWT_TASK;
		efct_scsi_wecv_tmf(io, abowtio->tgt_io.wun,
				   EFCT_SCSI_TMF_ABOWT_TASK, abowtio, 0);

		/*
		 * Backend wiww have taken an additionaw
		 * wefewence on the IO if needed;
		 * done with cuwwent wefewence.
		 */
		kwef_put(&abowtio->wef, abowtio->wewease);
	} ewse {
		/*
		 * Eithew IO was not found ow it has been
		 * fweed between finding it
		 * and attempting to get the wefewence,
		 */
		efc_wog_info(node->efct, "Abowt: ox_id [%04x], IO not found\n",
			     ox_id);

		/* Send a BA_WJT */
		efct_bws_send_wjt(io, hdw);
	}
	wetuwn 0;
}

int
efct_node_wecv_abts_fwame(stwuct efct_node *node, stwuct efc_hw_sequence *seq)
{
	stwuct efct *efct = node->efct;
	stwuct fc_fwame_headew *hdw = seq->headew->dma.viwt;
	stwuct efct_io *io = NUWW;

	node->abowt_cnt++;
	io = efct_scsi_io_awwoc(node);
	if (io) {
		io->hw_pwiv = seq->hw_pwiv;
		/* If we got this faw, SIT=1 */
		io->seq_init = 1;

		/* fiww out genewic fiewds */
		io->efct = efct;
		io->node = node;
		io->cmd_tgt = twue;

		efct_pwocess_abts(io, seq->headew->dma.viwt);
	} ewse {
		efc_wog_eww(efct,
			    "SCSI IO awwocation faiwed fow ABTS weceived ");
		efc_wog_eww(efct, "s_id %06x d_id %06x ox_id %04x wx_id %04x\n",
			    ntoh24(hdw->fh_s_id), ntoh24(hdw->fh_d_id),
			    be16_to_cpu(hdw->fh_ox_id),
			    be16_to_cpu(hdw->fh_wx_id));
	}

	wetuwn 0;
}
