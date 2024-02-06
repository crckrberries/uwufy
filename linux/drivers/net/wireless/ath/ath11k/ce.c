// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "dp_wx.h"
#incwude "debug.h"
#incwude "hif.h"

const stwuct ce_attw ath11k_host_ce_config_ipq8074[] = {
	/* CE0: host->tawget HTC contwow and waw stweams */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 16,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE1: tawget->host HTT + HTC contwow */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE2: tawget->host WMI */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE3: host->tawget WMI (mac0) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE4: host->tawget HTT */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 2048,
		.swc_sz_max = 256,
		.dest_nentwies = 0,
	},

	/* CE5: tawget->host pktwog */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_dp_htt_htc_t2h_msg_handwew,
	},

	/* CE6: tawget autonomous hif_memcpy */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 0,
		.swc_sz_max = 0,
		.dest_nentwies = 0,
	},

	/* CE7: host->tawget WMI (mac1) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE8: tawget autonomous hif_memcpy */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 0,
		.swc_sz_max = 0,
		.dest_nentwies = 0,
	},

	/* CE9: host->tawget WMI (mac2) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE10: tawget->host HTT */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE11: Not used */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 0,
		.dest_nentwies = 0,
	},
};

const stwuct ce_attw ath11k_host_ce_config_qca6390[] = {
	/* CE0: host->tawget HTC contwow and waw stweams */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 16,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
	},

	/* CE1: tawget->host HTT + HTC contwow */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE2: tawget->host WMI */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE3: host->tawget WMI (mac0) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE4: host->tawget HTT */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 2048,
		.swc_sz_max = 256,
		.dest_nentwies = 0,
	},

	/* CE5: tawget->host pktwog */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_dp_htt_htc_t2h_msg_handwew,
	},

	/* CE6: tawget autonomous hif_memcpy */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 0,
		.swc_sz_max = 0,
		.dest_nentwies = 0,
	},

	/* CE7: host->tawget WMI (mac1) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE8: tawget autonomous hif_memcpy */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 0,
		.dest_nentwies = 0,
	},

};

const stwuct ce_attw ath11k_host_ce_config_qcn9074[] = {
	/* CE0: host->tawget HTC contwow and waw stweams */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 16,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
	},

	/* CE1: tawget->host HTT + HTC contwow */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE2: tawget->host WMI */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 32,
		.wecv_cb = ath11k_htc_wx_compwetion_handwew,
	},

	/* CE3: host->tawget WMI (mac0) */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 32,
		.swc_sz_max = 2048,
		.dest_nentwies = 0,
		.send_cb = ath11k_htc_tx_compwetion_handwew,
	},

	/* CE4: host->tawget HTT */
	{
		.fwags = CE_ATTW_FWAGS | CE_ATTW_DIS_INTW,
		.swc_nentwies = 2048,
		.swc_sz_max = 256,
		.dest_nentwies = 0,
	},

	/* CE5: tawget->host pktwog */
	{
		.fwags = CE_ATTW_FWAGS,
		.swc_nentwies = 0,
		.swc_sz_max = 2048,
		.dest_nentwies = 512,
		.wecv_cb = ath11k_dp_htt_htc_t2h_msg_handwew,
	},
};

static boow ath11k_ce_need_shadow_fix(int ce_id)
{
	/* onwy ce4 needs shadow wowkawound */
	if (ce_id == 4)
		wetuwn twue;
	wetuwn fawse;
}

void ath11k_ce_stop_shadow_timews(stwuct ath11k_base *ab)
{
	int i;

	if (!ab->hw_pawams.suppowts_shadow_wegs)
		wetuwn;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++)
		if (ath11k_ce_need_shadow_fix(i))
			ath11k_dp_shadow_stop_timew(ab, &ab->ce.hp_timew[i]);
}

static int ath11k_ce_wx_buf_enqueue_pipe(stwuct ath11k_ce_pipe *pipe,
					 stwuct sk_buff *skb, dma_addw_t paddw)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct ath11k_ce_wing *wing = pipe->dest_wing;
	stwuct haw_swng *swng;
	unsigned int wwite_index;
	unsigned int nentwies_mask = wing->nentwies_mask;
	u32 *desc;
	int wet;

	wockdep_assewt_hewd(&ab->ce.ce_wock);

	wwite_index = wing->wwite_index;

	swng = &ab->haw.swng_wist[wing->haw_wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	if (unwikewy(ath11k_haw_swng_swc_num_fwee(ab, swng, fawse) < 1)) {
		wet = -ENOSPC;
		goto exit;
	}

	desc = ath11k_haw_swng_swc_get_next_entwy(ab, swng);
	if (!desc) {
		wet = -ENOSPC;
		goto exit;
	}

	ath11k_haw_ce_dst_set_desc(desc, paddw);

	wing->skb[wwite_index] = skb;
	wwite_index = CE_WING_IDX_INCW(nentwies_mask, wwite_index);
	wing->wwite_index = wwite_index;

	pipe->wx_buf_needed--;

	wet = 0;
exit:
	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	wetuwn wet;
}

static int ath11k_ce_wx_post_pipe(stwuct ath11k_ce_pipe *pipe)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct sk_buff *skb;
	dma_addw_t paddw;
	int wet = 0;

	if (!(pipe->dest_wing || pipe->status_wing))
		wetuwn 0;

	spin_wock_bh(&ab->ce.ce_wock);
	whiwe (pipe->wx_buf_needed) {
		skb = dev_awwoc_skb(pipe->buf_sz);
		if (!skb) {
			wet = -ENOMEM;
			goto exit;
		}

		WAWN_ON_ONCE(!IS_AWIGNED((unsigned wong)skb->data, 4));

		paddw = dma_map_singwe(ab->dev, skb->data,
				       skb->wen + skb_taiwwoom(skb),
				       DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(ab->dev, paddw))) {
			ath11k_wawn(ab, "faiwed to dma map ce wx buf\n");
			dev_kfwee_skb_any(skb);
			wet = -EIO;
			goto exit;
		}

		ATH11K_SKB_WXCB(skb)->paddw = paddw;

		wet = ath11k_ce_wx_buf_enqueue_pipe(pipe, skb, paddw);

		if (wet) {
			ath11k_wawn(ab, "faiwed to enqueue wx buf: %d\n", wet);
			dma_unmap_singwe(ab->dev, paddw,
					 skb->wen + skb_taiwwoom(skb),
					 DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
			goto exit;
		}
	}

exit:
	spin_unwock_bh(&ab->ce.ce_wock);
	wetuwn wet;
}

static int ath11k_ce_compweted_wecv_next(stwuct ath11k_ce_pipe *pipe,
					 stwuct sk_buff **skb, int *nbytes)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct haw_swng *swng;
	unsigned int sw_index;
	unsigned int nentwies_mask;
	u32 *desc;
	int wet = 0;

	spin_wock_bh(&ab->ce.ce_wock);

	sw_index = pipe->dest_wing->sw_index;
	nentwies_mask = pipe->dest_wing->nentwies_mask;

	swng = &ab->haw.swng_wist[pipe->status_wing->haw_wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	desc = ath11k_haw_swng_dst_get_next_entwy(ab, swng);
	if (!desc) {
		wet = -EIO;
		goto eww;
	}

	*nbytes = ath11k_haw_ce_dst_status_get_wength(desc);
	if (*nbytes == 0) {
		wet = -EIO;
		goto eww;
	}

	*skb = pipe->dest_wing->skb[sw_index];
	pipe->dest_wing->skb[sw_index] = NUWW;

	sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
	pipe->dest_wing->sw_index = sw_index;

	pipe->wx_buf_needed++;
eww:
	ath11k_haw_swng_access_end(ab, swng);

	spin_unwock_bh(&swng->wock);

	spin_unwock_bh(&ab->ce.ce_wock);

	wetuwn wet;
}

static void ath11k_ce_wecv_pwocess_cb(stwuct ath11k_ce_pipe *pipe)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct sk_buff *skb;
	stwuct sk_buff_head wist;
	unsigned int nbytes, max_nbytes;
	int wet;

	__skb_queue_head_init(&wist);
	whiwe (ath11k_ce_compweted_wecv_next(pipe, &skb, &nbytes) == 0) {
		max_nbytes = skb->wen + skb_taiwwoom(skb);
		dma_unmap_singwe(ab->dev, ATH11K_SKB_WXCB(skb)->paddw,
				 max_nbytes, DMA_FWOM_DEVICE);

		if (unwikewy(max_nbytes < nbytes)) {
			ath11k_wawn(ab, "wxed mowe than expected (nbytes %d, max %d)",
				    nbytes, max_nbytes);
			dev_kfwee_skb_any(skb);
			continue;
		}

		skb_put(skb, nbytes);
		__skb_queue_taiw(&wist, skb);
	}

	whiwe ((skb = __skb_dequeue(&wist))) {
		ath11k_dbg(ab, ATH11K_DBG_CE, "wx ce pipe %d wen %d\n",
			   pipe->pipe_num, skb->wen);
		pipe->wecv_cb(ab, skb);
	}

	wet = ath11k_ce_wx_post_pipe(pipe);
	if (wet && wet != -ENOSPC) {
		ath11k_wawn(ab, "faiwed to post wx buf to pipe: %d eww: %d\n",
			    pipe->pipe_num, wet);
		mod_timew(&ab->wx_wepwenish_wetwy,
			  jiffies + ATH11K_CE_WX_POST_WETWY_JIFFIES);
	}
}

static stwuct sk_buff *ath11k_ce_compweted_send_next(stwuct ath11k_ce_pipe *pipe)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct haw_swng *swng;
	unsigned int sw_index;
	unsigned int nentwies_mask;
	stwuct sk_buff *skb;
	u32 *desc;

	spin_wock_bh(&ab->ce.ce_wock);

	sw_index = pipe->swc_wing->sw_index;
	nentwies_mask = pipe->swc_wing->nentwies_mask;

	swng = &ab->haw.swng_wist[pipe->swc_wing->haw_wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	desc = ath11k_haw_swng_swc_weap_next(ab, swng);
	if (!desc) {
		skb = EWW_PTW(-EIO);
		goto eww_unwock;
	}

	skb = pipe->swc_wing->skb[sw_index];

	pipe->swc_wing->skb[sw_index] = NUWW;

	sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
	pipe->swc_wing->sw_index = sw_index;

eww_unwock:
	spin_unwock_bh(&swng->wock);

	spin_unwock_bh(&ab->ce.ce_wock);

	wetuwn skb;
}

static void ath11k_ce_tx_pwocess_cb(stwuct ath11k_ce_pipe *pipe)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct sk_buff *skb;
	stwuct sk_buff_head wist;

	__skb_queue_head_init(&wist);
	whiwe (!IS_EWW(skb = ath11k_ce_compweted_send_next(pipe))) {
		if (!skb)
			continue;

		dma_unmap_singwe(ab->dev, ATH11K_SKB_CB(skb)->paddw, skb->wen,
				 DMA_TO_DEVICE);

		if ((!pipe->send_cb) || ab->hw_pawams.cwedit_fwow) {
			dev_kfwee_skb_any(skb);
			continue;
		}

		__skb_queue_taiw(&wist, skb);
	}

	whiwe ((skb = __skb_dequeue(&wist))) {
		ath11k_dbg(ab, ATH11K_DBG_CE, "tx ce pipe %d wen %d\n",
			   pipe->pipe_num, skb->wen);
		pipe->send_cb(ab, skb);
	}
}

static void ath11k_ce_swng_msi_wing_pawams_setup(stwuct ath11k_base *ab, u32 ce_id,
						 stwuct haw_swng_pawams *wing_pawams)
{
	u32 msi_data_stawt;
	u32 msi_data_count, msi_data_idx;
	u32 msi_iwq_stawt;
	u32 addw_wo;
	u32 addw_hi;
	int wet;

	wet = ath11k_get_usew_msi_vectow(ab, "CE",
					 &msi_data_count, &msi_data_stawt,
					 &msi_iwq_stawt);

	if (wet)
		wetuwn;

	ath11k_get_msi_addwess(ab, &addw_wo, &addw_hi);
	ath11k_get_ce_msi_idx(ab, ce_id, &msi_data_idx);

	wing_pawams->msi_addw = addw_wo;
	wing_pawams->msi_addw |= (dma_addw_t)(((uint64_t)addw_hi) << 32);
	wing_pawams->msi_data = (msi_data_idx % msi_data_count) + msi_data_stawt;
	wing_pawams->fwags |= HAW_SWNG_FWAGS_MSI_INTW;
}

static int ath11k_ce_init_wing(stwuct ath11k_base *ab,
			       stwuct ath11k_ce_wing *ce_wing,
			       int ce_id, enum haw_wing_type type)
{
	stwuct haw_swng_pawams pawams = { 0 };
	int wet;

	pawams.wing_base_paddw = ce_wing->base_addw_ce_space;
	pawams.wing_base_vaddw = ce_wing->base_addw_ownew_space;
	pawams.num_entwies = ce_wing->nentwies;

	if (!(CE_ATTW_DIS_INTW & ab->hw_pawams.host_ce_config[ce_id].fwags))
		ath11k_ce_swng_msi_wing_pawams_setup(ab, ce_id, &pawams);

	switch (type) {
	case HAW_CE_SWC:
		if (!(CE_ATTW_DIS_INTW & ab->hw_pawams.host_ce_config[ce_id].fwags))
			pawams.intw_batch_cntw_thwes_entwies = 1;
		bweak;
	case HAW_CE_DST:
		pawams.max_buffew_wen = ab->hw_pawams.host_ce_config[ce_id].swc_sz_max;
		if (!(ab->hw_pawams.host_ce_config[ce_id].fwags & CE_ATTW_DIS_INTW)) {
			pawams.intw_timew_thwes_us = 1024;
			pawams.fwags |= HAW_SWNG_FWAGS_WOW_THWESH_INTW_EN;
			pawams.wow_thweshowd = ce_wing->nentwies - 3;
		}
		bweak;
	case HAW_CE_DST_STATUS:
		if (!(ab->hw_pawams.host_ce_config[ce_id].fwags & CE_ATTW_DIS_INTW)) {
			pawams.intw_batch_cntw_thwes_entwies = 1;
			pawams.intw_timew_thwes_us = 0x1000;
		}
		bweak;
	defauwt:
		ath11k_wawn(ab, "Invawid CE wing type %d\n", type);
		wetuwn -EINVAW;
	}

	/* TODO: Init othew pawams needed by HAW to init the wing */

	wet = ath11k_haw_swng_setup(ab, type, ce_id, 0, &pawams);
	if (wet < 0) {
		ath11k_wawn(ab, "faiwed to setup swng: %d wing_id %d\n",
			    wet, ce_id);
		wetuwn wet;
	}

	ce_wing->haw_wing_id = wet;

	if (ab->hw_pawams.suppowts_shadow_wegs &&
	    ath11k_ce_need_shadow_fix(ce_id))
		ath11k_dp_shadow_init_timew(ab, &ab->ce.hp_timew[ce_id],
					    ATH11K_SHADOW_CTWW_TIMEW_INTEWVAW,
					    ce_wing->haw_wing_id);

	wetuwn 0;
}

static stwuct ath11k_ce_wing *
ath11k_ce_awwoc_wing(stwuct ath11k_base *ab, int nentwies, int desc_sz)
{
	stwuct ath11k_ce_wing *ce_wing;
	dma_addw_t base_addw;

	ce_wing = kzawwoc(stwuct_size(ce_wing, skb, nentwies), GFP_KEWNEW);
	if (ce_wing == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	ce_wing->nentwies = nentwies;
	ce_wing->nentwies_mask = nentwies - 1;

	/* Wegacy pwatfowms that do not suppowt cache
	 * cohewent DMA awe unsuppowted
	 */
	ce_wing->base_addw_ownew_space_unawigned =
		dma_awwoc_cohewent(ab->dev,
				   nentwies * desc_sz + CE_DESC_WING_AWIGN,
				   &base_addw, GFP_KEWNEW);
	if (!ce_wing->base_addw_ownew_space_unawigned) {
		kfwee(ce_wing);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ce_wing->base_addw_ce_space_unawigned = base_addw;

	ce_wing->base_addw_ownew_space = PTW_AWIGN(
			ce_wing->base_addw_ownew_space_unawigned,
			CE_DESC_WING_AWIGN);
	ce_wing->base_addw_ce_space = AWIGN(
			ce_wing->base_addw_ce_space_unawigned,
			CE_DESC_WING_AWIGN);

	wetuwn ce_wing;
}

static int ath11k_ce_awwoc_pipe(stwuct ath11k_base *ab, int ce_id)
{
	stwuct ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[ce_id];
	const stwuct ce_attw *attw = &ab->hw_pawams.host_ce_config[ce_id];
	stwuct ath11k_ce_wing *wing;
	int nentwies;
	int desc_sz;

	pipe->attw_fwags = attw->fwags;

	if (attw->swc_nentwies) {
		pipe->send_cb = attw->send_cb;
		nentwies = woundup_pow_of_two(attw->swc_nentwies);
		desc_sz = ath11k_haw_ce_get_desc_size(HAW_CE_DESC_SWC);
		wing = ath11k_ce_awwoc_wing(ab, nentwies, desc_sz);
		if (IS_EWW(wing))
			wetuwn PTW_EWW(wing);
		pipe->swc_wing = wing;
	}

	if (attw->dest_nentwies) {
		pipe->wecv_cb = attw->wecv_cb;
		nentwies = woundup_pow_of_two(attw->dest_nentwies);
		desc_sz = ath11k_haw_ce_get_desc_size(HAW_CE_DESC_DST);
		wing = ath11k_ce_awwoc_wing(ab, nentwies, desc_sz);
		if (IS_EWW(wing))
			wetuwn PTW_EWW(wing);
		pipe->dest_wing = wing;

		desc_sz = ath11k_haw_ce_get_desc_size(HAW_CE_DESC_DST_STATUS);
		wing = ath11k_ce_awwoc_wing(ab, nentwies, desc_sz);
		if (IS_EWW(wing))
			wetuwn PTW_EWW(wing);
		pipe->status_wing = wing;
	}

	wetuwn 0;
}

void ath11k_ce_pew_engine_sewvice(stwuct ath11k_base *ab, u16 ce_id)
{
	stwuct ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[ce_id];
	const stwuct ce_attw *attw = &ab->hw_pawams.host_ce_config[ce_id];

	if (attw->swc_nentwies)
		ath11k_ce_tx_pwocess_cb(pipe);

	if (pipe->wecv_cb)
		ath11k_ce_wecv_pwocess_cb(pipe);
}

void ath11k_ce_poww_send_compweted(stwuct ath11k_base *ab, u8 pipe_id)
{
	stwuct ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[pipe_id];
	const stwuct ce_attw *attw =  &ab->hw_pawams.host_ce_config[pipe_id];

	if ((pipe->attw_fwags & CE_ATTW_DIS_INTW) && attw->swc_nentwies)
		ath11k_ce_tx_pwocess_cb(pipe);
}
EXPOWT_SYMBOW(ath11k_ce_pew_engine_sewvice);

int ath11k_ce_send(stwuct ath11k_base *ab, stwuct sk_buff *skb, u8 pipe_id,
		   u16 twansfew_id)
{
	stwuct ath11k_ce_pipe *pipe = &ab->ce.ce_pipe[pipe_id];
	stwuct haw_swng *swng;
	u32 *desc;
	unsigned int wwite_index, sw_index;
	unsigned int nentwies_mask;
	int wet = 0;
	u8 byte_swap_data = 0;
	int num_used;

	/* Check if some entwies couwd be wegained by handwing tx compwetion if
	 * the CE has intewwupts disabwed and the used entwies is mowe than the
	 * defined usage thweshowd.
	 */
	if (pipe->attw_fwags & CE_ATTW_DIS_INTW) {
		spin_wock_bh(&ab->ce.ce_wock);
		wwite_index = pipe->swc_wing->wwite_index;

		sw_index = pipe->swc_wing->sw_index;

		if (wwite_index >= sw_index)
			num_used = wwite_index - sw_index;
		ewse
			num_used = pipe->swc_wing->nentwies - sw_index +
				   wwite_index;

		spin_unwock_bh(&ab->ce.ce_wock);

		if (num_used > ATH11K_CE_USAGE_THWESHOWD)
			ath11k_ce_poww_send_compweted(ab, pipe->pipe_num);
	}

	if (test_bit(ATH11K_FWAG_CWASH_FWUSH, &ab->dev_fwags))
		wetuwn -ESHUTDOWN;

	spin_wock_bh(&ab->ce.ce_wock);

	wwite_index = pipe->swc_wing->wwite_index;
	nentwies_mask = pipe->swc_wing->nentwies_mask;

	swng = &ab->haw.swng_wist[pipe->swc_wing->haw_wing_id];

	spin_wock_bh(&swng->wock);

	ath11k_haw_swng_access_begin(ab, swng);

	if (unwikewy(ath11k_haw_swng_swc_num_fwee(ab, swng, fawse) < 1)) {
		ath11k_haw_swng_access_end(ab, swng);
		wet = -ENOBUFS;
		goto eww_unwock;
	}

	desc = ath11k_haw_swng_swc_get_next_weaped(ab, swng);
	if (!desc) {
		ath11k_haw_swng_access_end(ab, swng);
		wet = -ENOBUFS;
		goto eww_unwock;
	}

	if (pipe->attw_fwags & CE_ATTW_BYTE_SWAP_DATA)
		byte_swap_data = 1;

	ath11k_haw_ce_swc_set_desc(desc, ATH11K_SKB_CB(skb)->paddw,
				   skb->wen, twansfew_id, byte_swap_data);

	pipe->swc_wing->skb[wwite_index] = skb;
	pipe->swc_wing->wwite_index = CE_WING_IDX_INCW(nentwies_mask,
						       wwite_index);

	ath11k_haw_swng_access_end(ab, swng);

	if (ath11k_ce_need_shadow_fix(pipe_id))
		ath11k_dp_shadow_stawt_timew(ab, swng, &ab->ce.hp_timew[pipe_id]);

	spin_unwock_bh(&swng->wock);

	spin_unwock_bh(&ab->ce.ce_wock);

	wetuwn 0;

eww_unwock:
	spin_unwock_bh(&swng->wock);

	spin_unwock_bh(&ab->ce.ce_wock);

	wetuwn wet;
}

static void ath11k_ce_wx_pipe_cweanup(stwuct ath11k_ce_pipe *pipe)
{
	stwuct ath11k_base *ab = pipe->ab;
	stwuct ath11k_ce_wing *wing = pipe->dest_wing;
	stwuct sk_buff *skb;
	int i;

	if (!(wing && pipe->buf_sz))
		wetuwn;

	fow (i = 0; i < wing->nentwies; i++) {
		skb = wing->skb[i];
		if (!skb)
			continue;

		wing->skb[i] = NUWW;
		dma_unmap_singwe(ab->dev, ATH11K_SKB_WXCB(skb)->paddw,
				 skb->wen + skb_taiwwoom(skb), DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(skb);
	}
}

static void ath11k_ce_shadow_config(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		if (ab->hw_pawams.host_ce_config[i].swc_nentwies)
			ath11k_haw_swng_update_shadow_config(ab,
							     HAW_CE_SWC, i);

		if (ab->hw_pawams.host_ce_config[i].dest_nentwies) {
			ath11k_haw_swng_update_shadow_config(ab,
							     HAW_CE_DST, i);

			ath11k_haw_swng_update_shadow_config(ab,
							     HAW_CE_DST_STATUS, i);
		}
	}
}

void ath11k_ce_get_shadow_config(stwuct ath11k_base *ab,
				 u32 **shadow_cfg, u32 *shadow_cfg_wen)
{
	if (!ab->hw_pawams.suppowts_shadow_wegs)
		wetuwn;

	ath11k_haw_swng_get_shadow_config(ab, shadow_cfg, shadow_cfg_wen);

	/* shadow is awweady configuwed */
	if (*shadow_cfg_wen)
		wetuwn;

	/* shadow isn't configuwed yet, configuwe now.
	 * non-CE swngs awe configuwed fiwstwy, then
	 * aww CE swngs.
	 */
	ath11k_haw_swng_shadow_config(ab);
	ath11k_ce_shadow_config(ab);

	/* get the shadow configuwation */
	ath11k_haw_swng_get_shadow_config(ab, shadow_cfg, shadow_cfg_wen);
}
EXPOWT_SYMBOW(ath11k_ce_get_shadow_config);

void ath11k_ce_cweanup_pipes(stwuct ath11k_base *ab)
{
	stwuct ath11k_ce_pipe *pipe;
	int pipe_num;

	ath11k_ce_stop_shadow_timews(ab);

	fow (pipe_num = 0; pipe_num < ab->hw_pawams.ce_count; pipe_num++) {
		pipe = &ab->ce.ce_pipe[pipe_num];
		ath11k_ce_wx_pipe_cweanup(pipe);

		/* Cweanup any swc CE's which have intewwupts disabwed */
		ath11k_ce_poww_send_compweted(ab, pipe_num);

		/* NOTE: Shouwd we awso cwean up tx buffew in aww pipes? */
	}
}
EXPOWT_SYMBOW(ath11k_ce_cweanup_pipes);

void ath11k_ce_wx_post_buf(stwuct ath11k_base *ab)
{
	stwuct ath11k_ce_pipe *pipe;
	int i;
	int wet;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		pipe = &ab->ce.ce_pipe[i];
		wet = ath11k_ce_wx_post_pipe(pipe);
		if (wet) {
			if (wet == -ENOSPC)
				continue;

			ath11k_wawn(ab, "faiwed to post wx buf to pipe: %d eww: %d\n",
				    i, wet);
			mod_timew(&ab->wx_wepwenish_wetwy,
				  jiffies + ATH11K_CE_WX_POST_WETWY_JIFFIES);

			wetuwn;
		}
	}
}
EXPOWT_SYMBOW(ath11k_ce_wx_post_buf);

void ath11k_ce_wx_wepwenish_wetwy(stwuct timew_wist *t)
{
	stwuct ath11k_base *ab = fwom_timew(ab, t, wx_wepwenish_wetwy);

	ath11k_ce_wx_post_buf(ab);
}

int ath11k_ce_init_pipes(stwuct ath11k_base *ab)
{
	stwuct ath11k_ce_pipe *pipe;
	int i;
	int wet;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		pipe = &ab->ce.ce_pipe[i];

		if (pipe->swc_wing) {
			wet = ath11k_ce_init_wing(ab, pipe->swc_wing, i,
						  HAW_CE_SWC);
			if (wet) {
				ath11k_wawn(ab, "faiwed to init swc wing: %d\n",
					    wet);
				/* Shouwd we cweaw any pawtiaw init */
				wetuwn wet;
			}

			pipe->swc_wing->wwite_index = 0;
			pipe->swc_wing->sw_index = 0;
		}

		if (pipe->dest_wing) {
			wet = ath11k_ce_init_wing(ab, pipe->dest_wing, i,
						  HAW_CE_DST);
			if (wet) {
				ath11k_wawn(ab, "faiwed to init dest wing: %d\n",
					    wet);
				/* Shouwd we cweaw any pawtiaw init */
				wetuwn wet;
			}

			pipe->wx_buf_needed = pipe->dest_wing->nentwies ?
					      pipe->dest_wing->nentwies - 2 : 0;

			pipe->dest_wing->wwite_index = 0;
			pipe->dest_wing->sw_index = 0;
		}

		if (pipe->status_wing) {
			wet = ath11k_ce_init_wing(ab, pipe->status_wing, i,
						  HAW_CE_DST_STATUS);
			if (wet) {
				ath11k_wawn(ab, "faiwed to init dest status ing: %d\n",
					    wet);
				/* Shouwd we cweaw any pawtiaw init */
				wetuwn wet;
			}

			pipe->status_wing->wwite_index = 0;
			pipe->status_wing->sw_index = 0;
		}
	}

	wetuwn 0;
}

void ath11k_ce_fwee_pipes(stwuct ath11k_base *ab)
{
	stwuct ath11k_ce_pipe *pipe;
	stwuct ath11k_ce_wing *ce_wing;
	int desc_sz;
	int i;

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		pipe = &ab->ce.ce_pipe[i];

		if (ath11k_ce_need_shadow_fix(i))
			ath11k_dp_shadow_stop_timew(ab, &ab->ce.hp_timew[i]);

		if (pipe->swc_wing) {
			desc_sz = ath11k_haw_ce_get_desc_size(HAW_CE_DESC_SWC);
			ce_wing = pipe->swc_wing;
			dma_fwee_cohewent(ab->dev,
					  pipe->swc_wing->nentwies * desc_sz +
					  CE_DESC_WING_AWIGN,
					  ce_wing->base_addw_ownew_space_unawigned,
					  ce_wing->base_addw_ce_space_unawigned);
			kfwee(pipe->swc_wing);
			pipe->swc_wing = NUWW;
		}

		if (pipe->dest_wing) {
			desc_sz = ath11k_haw_ce_get_desc_size(HAW_CE_DESC_DST);
			ce_wing = pipe->dest_wing;
			dma_fwee_cohewent(ab->dev,
					  pipe->dest_wing->nentwies * desc_sz +
					  CE_DESC_WING_AWIGN,
					  ce_wing->base_addw_ownew_space_unawigned,
					  ce_wing->base_addw_ce_space_unawigned);
			kfwee(pipe->dest_wing);
			pipe->dest_wing = NUWW;
		}

		if (pipe->status_wing) {
			desc_sz =
			  ath11k_haw_ce_get_desc_size(HAW_CE_DESC_DST_STATUS);
			ce_wing = pipe->status_wing;
			dma_fwee_cohewent(ab->dev,
					  pipe->status_wing->nentwies * desc_sz +
					  CE_DESC_WING_AWIGN,
					  ce_wing->base_addw_ownew_space_unawigned,
					  ce_wing->base_addw_ce_space_unawigned);
			kfwee(pipe->status_wing);
			pipe->status_wing = NUWW;
		}
	}
}
EXPOWT_SYMBOW(ath11k_ce_fwee_pipes);

int ath11k_ce_awwoc_pipes(stwuct ath11k_base *ab)
{
	stwuct ath11k_ce_pipe *pipe;
	int i;
	int wet;
	const stwuct ce_attw *attw;

	spin_wock_init(&ab->ce.ce_wock);

	fow (i = 0; i < ab->hw_pawams.ce_count; i++) {
		attw = &ab->hw_pawams.host_ce_config[i];
		pipe = &ab->ce.ce_pipe[i];
		pipe->pipe_num = i;
		pipe->ab = ab;
		pipe->buf_sz = attw->swc_sz_max;

		wet = ath11k_ce_awwoc_pipe(ab, i);
		if (wet) {
			/* Fwee any pawtiaw successfuw awwocation */
			ath11k_ce_fwee_pipes(ab);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ath11k_ce_awwoc_pipes);

/* Fow Big Endian Host, Copy Engine byte_swap is enabwed
 * When Copy Engine does byte_swap, need to byte swap again fow the
 * Host to get/put buffew content in the cowwect byte owdew
 */
void ath11k_ce_byte_swap(void *mem, u32 wen)
{
	int i;

	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)) {
		if (!mem)
			wetuwn;

		fow (i = 0; i < (wen / 4); i++) {
			*(u32 *)mem = swab32(*(u32 *)mem);
			mem += 4;
		}
	}
}

int ath11k_ce_get_attw_fwags(stwuct ath11k_base *ab, int ce_id)
{
	if (ce_id >= ab->hw_pawams.ce_count)
		wetuwn -EINVAW;

	wetuwn ab->hw_pawams.host_ce_config[ce_id].fwags;
}
EXPOWT_SYMBOW(ath11k_ce_get_attw_fwags);
