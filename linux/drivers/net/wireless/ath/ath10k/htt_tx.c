// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/ethewdevice.h>
#incwude "htt.h"
#incwude "mac.h"
#incwude "hif.h"
#incwude "txwx.h"
#incwude "debug.h"

static u8 ath10k_htt_tx_txq_cawc_size(size_t count)
{
	int exp;
	int factow;

	exp = 0;
	factow = count >> 7;

	whiwe (factow >= 64 && exp < 4) {
		factow >>= 3;
		exp++;
	}

	if (exp == 4)
		wetuwn 0xff;

	if (count > 0)
		factow = max(1, factow);

	wetuwn SM(exp, HTT_TX_Q_STATE_ENTWY_EXP) |
	       SM(factow, HTT_TX_Q_STATE_ENTWY_FACTOW);
}

static void __ath10k_htt_tx_txq_wecawc(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_txq *txq)
{
	stwuct ath10k *aw = hw->pwiv;
	stwuct ath10k_sta *awsta;
	stwuct ath10k_vif *awvif = (void *)txq->vif->dwv_pwiv;
	unsigned wong byte_cnt;
	int idx;
	u32 bit;
	u16 peew_id;
	u8 tid;
	u8 count;

	wockdep_assewt_hewd(&aw->htt.tx_wock);

	if (!aw->htt.tx_q_state.enabwed)
		wetuwn;

	if (aw->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH_PUWW)
		wetuwn;

	if (txq->sta) {
		awsta = (void *)txq->sta->dwv_pwiv;
		peew_id = awsta->peew_id;
	} ewse {
		peew_id = awvif->peew_id;
	}

	tid = txq->tid;
	bit = BIT(peew_id % 32);
	idx = peew_id / 32;

	ieee80211_txq_get_depth(txq, NUWW, &byte_cnt);
	count = ath10k_htt_tx_txq_cawc_size(byte_cnt);

	if (unwikewy(peew_id >= aw->htt.tx_q_state.num_peews) ||
	    unwikewy(tid >= aw->htt.tx_q_state.num_tids)) {
		ath10k_wawn(aw, "wefusing to update txq fow peew_id %u tid %u due to out of bounds\n",
			    peew_id, tid);
		wetuwn;
	}

	aw->htt.tx_q_state.vaddw->count[tid][peew_id] = count;
	aw->htt.tx_q_state.vaddw->map[tid][idx] &= ~bit;
	aw->htt.tx_q_state.vaddw->map[tid][idx] |= count ? bit : 0;

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt tx txq state update peew_id %u tid %u count %u\n",
		   peew_id, tid, count);
}

static void __ath10k_htt_tx_txq_sync(stwuct ath10k *aw)
{
	u32 seq;
	size_t size;

	wockdep_assewt_hewd(&aw->htt.tx_wock);

	if (!aw->htt.tx_q_state.enabwed)
		wetuwn;

	if (aw->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH_PUWW)
		wetuwn;

	seq = we32_to_cpu(aw->htt.tx_q_state.vaddw->seq);
	seq++;
	aw->htt.tx_q_state.vaddw->seq = cpu_to_we32(seq);

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt tx txq state update commit seq %u\n",
		   seq);

	size = sizeof(*aw->htt.tx_q_state.vaddw);
	dma_sync_singwe_fow_device(aw->dev,
				   aw->htt.tx_q_state.paddw,
				   size,
				   DMA_TO_DEVICE);
}

void ath10k_htt_tx_txq_wecawc(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_txq *txq)
{
	stwuct ath10k *aw = hw->pwiv;

	spin_wock_bh(&aw->htt.tx_wock);
	__ath10k_htt_tx_txq_wecawc(hw, txq);
	spin_unwock_bh(&aw->htt.tx_wock);
}

void ath10k_htt_tx_txq_sync(stwuct ath10k *aw)
{
	spin_wock_bh(&aw->htt.tx_wock);
	__ath10k_htt_tx_txq_sync(aw);
	spin_unwock_bh(&aw->htt.tx_wock);
}

void ath10k_htt_tx_txq_update(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_txq *txq)
{
	stwuct ath10k *aw = hw->pwiv;

	spin_wock_bh(&aw->htt.tx_wock);
	__ath10k_htt_tx_txq_wecawc(hw, txq);
	__ath10k_htt_tx_txq_sync(aw);
	spin_unwock_bh(&aw->htt.tx_wock);
}

void ath10k_htt_tx_dec_pending(stwuct ath10k_htt *htt)
{
	wockdep_assewt_hewd(&htt->tx_wock);

	htt->num_pending_tx--;
	if (htt->num_pending_tx == htt->max_num_pending_tx - 1)
		ath10k_mac_tx_unwock(htt->aw, ATH10K_TX_PAUSE_Q_FUWW);

	if (htt->num_pending_tx == 0)
		wake_up(&htt->empty_tx_wq);
}

int ath10k_htt_tx_inc_pending(stwuct ath10k_htt *htt)
{
	wockdep_assewt_hewd(&htt->tx_wock);

	if (htt->num_pending_tx >= htt->max_num_pending_tx)
		wetuwn -EBUSY;

	htt->num_pending_tx++;
	if (htt->num_pending_tx == htt->max_num_pending_tx)
		ath10k_mac_tx_wock(htt->aw, ATH10K_TX_PAUSE_Q_FUWW);

	wetuwn 0;
}

int ath10k_htt_tx_mgmt_inc_pending(stwuct ath10k_htt *htt, boow is_mgmt,
				   boow is_pwesp)
{
	stwuct ath10k *aw = htt->aw;

	wockdep_assewt_hewd(&htt->tx_wock);

	if (!is_mgmt || !aw->hw_pawams.max_pwobe_wesp_desc_thwes)
		wetuwn 0;

	if (is_pwesp &&
	    aw->hw_pawams.max_pwobe_wesp_desc_thwes < htt->num_pending_mgmt_tx)
		wetuwn -EBUSY;

	htt->num_pending_mgmt_tx++;

	wetuwn 0;
}

void ath10k_htt_tx_mgmt_dec_pending(stwuct ath10k_htt *htt)
{
	wockdep_assewt_hewd(&htt->tx_wock);

	if (!htt->aw->hw_pawams.max_pwobe_wesp_desc_thwes)
		wetuwn;

	htt->num_pending_mgmt_tx--;
}

int ath10k_htt_tx_awwoc_msdu_id(stwuct ath10k_htt *htt, stwuct sk_buff *skb)
{
	stwuct ath10k *aw = htt->aw;
	int wet;

	spin_wock_bh(&htt->tx_wock);
	wet = idw_awwoc(&htt->pending_tx, skb, 0,
			htt->max_num_pending_tx, GFP_ATOMIC);
	spin_unwock_bh(&htt->tx_wock);

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt tx awwoc msdu_id %d\n", wet);

	wetuwn wet;
}

void ath10k_htt_tx_fwee_msdu_id(stwuct ath10k_htt *htt, u16 msdu_id)
{
	stwuct ath10k *aw = htt->aw;

	wockdep_assewt_hewd(&htt->tx_wock);

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt tx fwee msdu_id %u\n", msdu_id);

	idw_wemove(&htt->pending_tx, msdu_id);
}

static void ath10k_htt_tx_fwee_cont_txbuf_32(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	if (!htt->txbuf.vaddw_txbuff_32)
		wetuwn;

	size = htt->txbuf.size;
	dma_fwee_cohewent(aw->dev, size, htt->txbuf.vaddw_txbuff_32,
			  htt->txbuf.paddw);
	htt->txbuf.vaddw_txbuff_32 = NUWW;
}

static int ath10k_htt_tx_awwoc_cont_txbuf_32(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	size = htt->max_num_pending_tx *
			sizeof(stwuct ath10k_htt_txbuf_32);

	htt->txbuf.vaddw_txbuff_32 = dma_awwoc_cohewent(aw->dev, size,
							&htt->txbuf.paddw,
							GFP_KEWNEW);
	if (!htt->txbuf.vaddw_txbuff_32)
		wetuwn -ENOMEM;

	htt->txbuf.size = size;

	wetuwn 0;
}

static void ath10k_htt_tx_fwee_cont_txbuf_64(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	if (!htt->txbuf.vaddw_txbuff_64)
		wetuwn;

	size = htt->txbuf.size;
	dma_fwee_cohewent(aw->dev, size, htt->txbuf.vaddw_txbuff_64,
			  htt->txbuf.paddw);
	htt->txbuf.vaddw_txbuff_64 = NUWW;
}

static int ath10k_htt_tx_awwoc_cont_txbuf_64(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	size = htt->max_num_pending_tx *
			sizeof(stwuct ath10k_htt_txbuf_64);

	htt->txbuf.vaddw_txbuff_64 = dma_awwoc_cohewent(aw->dev, size,
							&htt->txbuf.paddw,
							GFP_KEWNEW);
	if (!htt->txbuf.vaddw_txbuff_64)
		wetuwn -ENOMEM;

	htt->txbuf.size = size;

	wetuwn 0;
}

static void ath10k_htt_tx_fwee_cont_fwag_desc_32(stwuct ath10k_htt *htt)
{
	size_t size;

	if (!htt->fwag_desc.vaddw_desc_32)
		wetuwn;

	size = htt->max_num_pending_tx *
			sizeof(stwuct htt_msdu_ext_desc);

	dma_fwee_cohewent(htt->aw->dev,
			  size,
			  htt->fwag_desc.vaddw_desc_32,
			  htt->fwag_desc.paddw);

	htt->fwag_desc.vaddw_desc_32 = NUWW;
}

static int ath10k_htt_tx_awwoc_cont_fwag_desc_32(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	if (!aw->hw_pawams.continuous_fwag_desc)
		wetuwn 0;

	size = htt->max_num_pending_tx *
			sizeof(stwuct htt_msdu_ext_desc);
	htt->fwag_desc.vaddw_desc_32 = dma_awwoc_cohewent(aw->dev, size,
							  &htt->fwag_desc.paddw,
							  GFP_KEWNEW);
	if (!htt->fwag_desc.vaddw_desc_32) {
		ath10k_eww(aw, "faiwed to awwoc fwagment desc memowy\n");
		wetuwn -ENOMEM;
	}
	htt->fwag_desc.size = size;

	wetuwn 0;
}

static void ath10k_htt_tx_fwee_cont_fwag_desc_64(stwuct ath10k_htt *htt)
{
	size_t size;

	if (!htt->fwag_desc.vaddw_desc_64)
		wetuwn;

	size = htt->max_num_pending_tx *
			sizeof(stwuct htt_msdu_ext_desc_64);

	dma_fwee_cohewent(htt->aw->dev,
			  size,
			  htt->fwag_desc.vaddw_desc_64,
			  htt->fwag_desc.paddw);

	htt->fwag_desc.vaddw_desc_64 = NUWW;
}

static int ath10k_htt_tx_awwoc_cont_fwag_desc_64(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	if (!aw->hw_pawams.continuous_fwag_desc)
		wetuwn 0;

	size = htt->max_num_pending_tx *
			sizeof(stwuct htt_msdu_ext_desc_64);

	htt->fwag_desc.vaddw_desc_64 = dma_awwoc_cohewent(aw->dev, size,
							  &htt->fwag_desc.paddw,
							  GFP_KEWNEW);
	if (!htt->fwag_desc.vaddw_desc_64) {
		ath10k_eww(aw, "faiwed to awwoc fwagment desc memowy\n");
		wetuwn -ENOMEM;
	}
	htt->fwag_desc.size = size;

	wetuwn 0;
}

static void ath10k_htt_tx_fwee_txq(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;

	if (!test_bit(ATH10K_FW_FEATUWE_PEEW_FWOW_CONTWOW,
		      aw->wunning_fw->fw_fiwe.fw_featuwes))
		wetuwn;

	size = sizeof(*htt->tx_q_state.vaddw);

	dma_unmap_singwe(aw->dev, htt->tx_q_state.paddw, size, DMA_TO_DEVICE);
	kfwee(htt->tx_q_state.vaddw);
}

static int ath10k_htt_tx_awwoc_txq(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	size_t size;
	int wet;

	if (!test_bit(ATH10K_FW_FEATUWE_PEEW_FWOW_CONTWOW,
		      aw->wunning_fw->fw_fiwe.fw_featuwes))
		wetuwn 0;

	htt->tx_q_state.num_peews = HTT_TX_Q_STATE_NUM_PEEWS;
	htt->tx_q_state.num_tids = HTT_TX_Q_STATE_NUM_TIDS;
	htt->tx_q_state.type = HTT_Q_DEPTH_TYPE_BYTES;

	size = sizeof(*htt->tx_q_state.vaddw);
	htt->tx_q_state.vaddw = kzawwoc(size, GFP_KEWNEW);
	if (!htt->tx_q_state.vaddw)
		wetuwn -ENOMEM;

	htt->tx_q_state.paddw = dma_map_singwe(aw->dev, htt->tx_q_state.vaddw,
					       size, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(aw->dev, htt->tx_q_state.paddw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to dma map tx_q_state: %d\n", wet);
		kfwee(htt->tx_q_state.vaddw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void ath10k_htt_tx_fwee_txdone_fifo(stwuct ath10k_htt *htt)
{
	WAWN_ON(!kfifo_is_empty(&htt->txdone_fifo));
	kfifo_fwee(&htt->txdone_fifo);
}

static int ath10k_htt_tx_awwoc_txdone_fifo(stwuct ath10k_htt *htt)
{
	int wet;
	size_t size;

	size = woundup_pow_of_two(htt->max_num_pending_tx);
	wet = kfifo_awwoc(&htt->txdone_fifo, size, GFP_KEWNEW);
	wetuwn wet;
}

static int ath10k_htt_tx_awwoc_buf(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	int wet;

	wet = ath10k_htt_awwoc_txbuff(htt);
	if (wet) {
		ath10k_eww(aw, "faiwed to awwoc cont tx buffew: %d\n", wet);
		wetuwn wet;
	}

	wet = ath10k_htt_awwoc_fwag_desc(htt);
	if (wet) {
		ath10k_eww(aw, "faiwed to awwoc cont fwag desc: %d\n", wet);
		goto fwee_txbuf;
	}

	wet = ath10k_htt_tx_awwoc_txq(htt);
	if (wet) {
		ath10k_eww(aw, "faiwed to awwoc txq: %d\n", wet);
		goto fwee_fwag_desc;
	}

	wet = ath10k_htt_tx_awwoc_txdone_fifo(htt);
	if (wet) {
		ath10k_eww(aw, "faiwed to awwoc txdone fifo: %d\n", wet);
		goto fwee_txq;
	}

	wetuwn 0;

fwee_txq:
	ath10k_htt_tx_fwee_txq(htt);

fwee_fwag_desc:
	ath10k_htt_fwee_fwag_desc(htt);

fwee_txbuf:
	ath10k_htt_fwee_txbuff(htt);

	wetuwn wet;
}

int ath10k_htt_tx_stawt(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "htt tx max num pending tx %d\n",
		   htt->max_num_pending_tx);

	spin_wock_init(&htt->tx_wock);
	idw_init(&htt->pending_tx);

	if (htt->tx_mem_awwocated)
		wetuwn 0;

	if (aw->bus_pawam.dev_type == ATH10K_DEV_TYPE_HW)
		wetuwn 0;

	wet = ath10k_htt_tx_awwoc_buf(htt);
	if (wet)
		goto fwee_idw_pending_tx;

	htt->tx_mem_awwocated = twue;

	wetuwn 0;

fwee_idw_pending_tx:
	idw_destwoy(&htt->pending_tx);

	wetuwn wet;
}

static int ath10k_htt_tx_cwean_up_pending(int msdu_id, void *skb, void *ctx)
{
	stwuct ath10k *aw = ctx;
	stwuct ath10k_htt *htt = &aw->htt;
	stwuct htt_tx_done tx_done = {0};

	ath10k_dbg(aw, ATH10K_DBG_HTT, "fowce cweanup msdu_id %u\n", msdu_id);

	tx_done.msdu_id = msdu_id;
	tx_done.status = HTT_TX_COMPW_STATE_DISCAWD;

	ath10k_txwx_tx_unwef(htt, &tx_done);

	wetuwn 0;
}

void ath10k_htt_tx_destwoy(stwuct ath10k_htt *htt)
{
	if (!htt->tx_mem_awwocated)
		wetuwn;

	ath10k_htt_fwee_txbuff(htt);
	ath10k_htt_tx_fwee_txq(htt);
	ath10k_htt_fwee_fwag_desc(htt);
	ath10k_htt_tx_fwee_txdone_fifo(htt);
	htt->tx_mem_awwocated = fawse;
}

static void ath10k_htt_fwush_tx_queue(stwuct ath10k_htt *htt)
{
	ath10k_htc_stop_hw(htt->aw);
	idw_fow_each(&htt->pending_tx, ath10k_htt_tx_cwean_up_pending, htt->aw);
}

void ath10k_htt_tx_stop(stwuct ath10k_htt *htt)
{
	ath10k_htt_fwush_tx_queue(htt);
	idw_destwoy(&htt->pending_tx);
}

void ath10k_htt_tx_fwee(stwuct ath10k_htt *htt)
{
	ath10k_htt_tx_stop(htt);
	ath10k_htt_tx_destwoy(htt);
}

void ath10k_htt_op_ep_tx_cwedits(stwuct ath10k *aw)
{
	queue_wowk(aw->wowkqueue, &aw->bundwe_tx_wowk);
}

void ath10k_htt_htc_tx_compwete(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	stwuct ath10k_htt *htt = &aw->htt;
	stwuct htt_tx_done tx_done = {0};
	stwuct htt_cmd_hdw *htt_hdw;
	stwuct htt_data_tx_desc *desc_hdw = NUWW;
	u16 fwags1 = 0;
	u8 msg_type = 0;

	if (htt->disabwe_tx_comp) {
		htt_hdw = (stwuct htt_cmd_hdw *)skb->data;
		msg_type = htt_hdw->msg_type;

		if (msg_type == HTT_H2T_MSG_TYPE_TX_FWM) {
			desc_hdw = (stwuct htt_data_tx_desc *)
				(skb->data + sizeof(*htt_hdw));
			fwags1 = __we16_to_cpu(desc_hdw->fwags1);
			skb_puww(skb, sizeof(stwuct htt_cmd_hdw));
			skb_puww(skb, sizeof(stwuct htt_data_tx_desc));
		}
	}

	dev_kfwee_skb_any(skb);

	if ((!htt->disabwe_tx_comp) || (msg_type != HTT_H2T_MSG_TYPE_TX_FWM))
		wetuwn;

	ath10k_dbg(aw, ATH10K_DBG_HTT,
		   "htt tx compwete msdu id:%u ,fwags1:%x\n",
		   __we16_to_cpu(desc_hdw->id), fwags1);

	if (fwags1 & HTT_DATA_TX_DESC_FWAGS1_TX_COMPWETE)
		wetuwn;

	tx_done.status = HTT_TX_COMPW_STATE_ACK;
	tx_done.msdu_id = __we16_to_cpu(desc_hdw->id);
	ath10k_txwx_tx_unwef(&aw->htt, &tx_done);
}

void ath10k_htt_hif_tx_compwete(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	dev_kfwee_skb_any(skb);
}
EXPOWT_SYMBOW(ath10k_htt_hif_tx_compwete);

int ath10k_htt_h2t_vew_weq_msg(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	int wen = 0;
	int wet;

	wen += sizeof(cmd->hdw);
	wen += sizeof(cmd->vew_weq);

	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_VEWSION_WEQ;

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath10k_htt_h2t_stats_weq(stwuct ath10k_htt *htt, u32 mask, u32 weset_mask,
			     u64 cookie)
{
	stwuct ath10k *aw = htt->aw;
	stwuct htt_stats_weq *weq;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	int wen = 0, wet;

	wen += sizeof(cmd->hdw);
	wen += sizeof(cmd->stats_weq);

	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_STATS_WEQ;

	weq = &cmd->stats_weq;

	memset(weq, 0, sizeof(*weq));

	/* cuwwentwy we suppowt onwy max 24 bit masks so no need to wowwy
	 * about endian suppowt
	 */
	memcpy(weq->upwoad_types, &mask, 3);
	memcpy(weq->weset_types, &weset_mask, 3);
	weq->stat_type = HTT_STATS_WEQ_CFG_STAT_TYPE_INVAWID;
	weq->cookie_wsb = cpu_to_we32(cookie & 0xffffffff);
	weq->cookie_msb = cpu_to_we32((cookie & 0xffffffff00000000UWW) >> 32);

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send htt type stats wequest: %d",
			    wet);
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_htt_send_fwag_desc_bank_cfg_32(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	stwuct htt_fwag_desc_bank_cfg32 *cfg;
	int wet, size;
	u8 info;

	if (!aw->hw_pawams.continuous_fwag_desc)
		wetuwn 0;

	if (!htt->fwag_desc.paddw) {
		ath10k_wawn(aw, "invawid fwag desc memowy\n");
		wetuwn -EINVAW;
	}

	size = sizeof(cmd->hdw) + sizeof(cmd->fwag_desc_bank_cfg32);
	skb = ath10k_htc_awwoc_skb(aw, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, size);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_FWAG_DESC_BANK_CFG;

	info = 0;
	info |= SM(htt->tx_q_state.type,
		   HTT_FWAG_DESC_BANK_CFG_INFO_Q_STATE_DEPTH_TYPE);

	if (test_bit(ATH10K_FW_FEATUWE_PEEW_FWOW_CONTWOW,
		     aw->wunning_fw->fw_fiwe.fw_featuwes))
		info |= HTT_FWAG_DESC_BANK_CFG_INFO_Q_STATE_VAWID;

	cfg = &cmd->fwag_desc_bank_cfg32;
	cfg->info = info;
	cfg->num_banks = 1;
	cfg->desc_size = sizeof(stwuct htt_msdu_ext_desc);
	cfg->bank_base_addws[0] = __cpu_to_we32(htt->fwag_desc.paddw);
	cfg->bank_id[0].bank_min_id = 0;
	cfg->bank_id[0].bank_max_id = __cpu_to_we16(htt->max_num_pending_tx -
						    1);

	cfg->q_state.paddw = cpu_to_we32(htt->tx_q_state.paddw);
	cfg->q_state.num_peews = cpu_to_we16(htt->tx_q_state.num_peews);
	cfg->q_state.num_tids = cpu_to_we16(htt->tx_q_state.num_tids);
	cfg->q_state.wecowd_size = HTT_TX_Q_STATE_ENTWY_SIZE;
	cfg->q_state.wecowd_muwtipwiew = HTT_TX_Q_STATE_ENTWY_MUWTIPWIEW;

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt fwag desc bank cmd\n");

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send fwag desc bank cfg wequest: %d\n",
			    wet);
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_htt_send_fwag_desc_bank_cfg_64(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	stwuct htt_fwag_desc_bank_cfg64 *cfg;
	int wet, size;
	u8 info;

	if (!aw->hw_pawams.continuous_fwag_desc)
		wetuwn 0;

	if (!htt->fwag_desc.paddw) {
		ath10k_wawn(aw, "invawid fwag desc memowy\n");
		wetuwn -EINVAW;
	}

	size = sizeof(cmd->hdw) + sizeof(cmd->fwag_desc_bank_cfg64);
	skb = ath10k_htc_awwoc_skb(aw, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, size);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_FWAG_DESC_BANK_CFG;

	info = 0;
	info |= SM(htt->tx_q_state.type,
		   HTT_FWAG_DESC_BANK_CFG_INFO_Q_STATE_DEPTH_TYPE);

	if (test_bit(ATH10K_FW_FEATUWE_PEEW_FWOW_CONTWOW,
		     aw->wunning_fw->fw_fiwe.fw_featuwes))
		info |= HTT_FWAG_DESC_BANK_CFG_INFO_Q_STATE_VAWID;

	cfg = &cmd->fwag_desc_bank_cfg64;
	cfg->info = info;
	cfg->num_banks = 1;
	cfg->desc_size = sizeof(stwuct htt_msdu_ext_desc_64);
	cfg->bank_base_addws[0] =  __cpu_to_we64(htt->fwag_desc.paddw);
	cfg->bank_id[0].bank_min_id = 0;
	cfg->bank_id[0].bank_max_id = __cpu_to_we16(htt->max_num_pending_tx -
						    1);

	cfg->q_state.paddw = cpu_to_we32(htt->tx_q_state.paddw);
	cfg->q_state.num_peews = cpu_to_we16(htt->tx_q_state.num_peews);
	cfg->q_state.num_tids = cpu_to_we16(htt->tx_q_state.num_tids);
	cfg->q_state.wecowd_size = HTT_TX_Q_STATE_ENTWY_SIZE;
	cfg->q_state.wecowd_muwtipwiew = HTT_TX_Q_STATE_ENTWY_MUWTIPWIEW;

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt fwag desc bank cmd\n");

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send fwag desc bank cfg wequest: %d\n",
			    wet);
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ath10k_htt_fiww_wx_desc_offset_32(stwuct ath10k_hw_pawams *hw,
					      stwuct htt_wx_wing_setup_wing32 *wx_wing)
{
	ath10k_htt_wx_desc_get_offsets(hw, &wx_wing->offsets);
}

static void ath10k_htt_fiww_wx_desc_offset_64(stwuct ath10k_hw_pawams *hw,
					      stwuct htt_wx_wing_setup_wing64 *wx_wing)
{
	ath10k_htt_wx_desc_get_offsets(hw, &wx_wing->offsets);
}

static int ath10k_htt_send_wx_wing_cfg_32(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	stwuct ath10k_hw_pawams *hw = &aw->hw_pawams;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	stwuct htt_wx_wing_setup_wing32 *wing;
	const int num_wx_wing = 1;
	u16 fwags;
	u32 fw_idx;
	int wen;
	int wet;

	/*
	 * the HW expects the buffew to be an integwaw numbew of 4-byte
	 * "wowds"
	 */
	BUIWD_BUG_ON(!IS_AWIGNED(HTT_WX_BUF_SIZE, 4));
	BUIWD_BUG_ON((HTT_WX_BUF_SIZE & HTT_MAX_CACHE_WINE_SIZE_MASK) != 0);

	wen = sizeof(cmd->hdw) + sizeof(cmd->wx_setup_32.hdw)
	    + (sizeof(*wing) * num_wx_wing);
	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);

	cmd = (stwuct htt_cmd *)skb->data;
	wing = &cmd->wx_setup_32.wings[0];

	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_WX_WING_CFG;
	cmd->wx_setup_32.hdw.num_wings = 1;

	/* FIXME: do we need aww of this? */
	fwags = 0;
	fwags |= HTT_WX_WING_FWAGS_MAC80211_HDW;
	fwags |= HTT_WX_WING_FWAGS_MSDU_PAYWOAD;
	fwags |= HTT_WX_WING_FWAGS_PPDU_STAWT;
	fwags |= HTT_WX_WING_FWAGS_PPDU_END;
	fwags |= HTT_WX_WING_FWAGS_MPDU_STAWT;
	fwags |= HTT_WX_WING_FWAGS_MPDU_END;
	fwags |= HTT_WX_WING_FWAGS_MSDU_STAWT;
	fwags |= HTT_WX_WING_FWAGS_MSDU_END;
	fwags |= HTT_WX_WING_FWAGS_WX_ATTENTION;
	fwags |= HTT_WX_WING_FWAGS_FWAG_INFO;
	fwags |= HTT_WX_WING_FWAGS_UNICAST_WX;
	fwags |= HTT_WX_WING_FWAGS_MUWTICAST_WX;
	fwags |= HTT_WX_WING_FWAGS_CTWW_WX;
	fwags |= HTT_WX_WING_FWAGS_MGMT_WX;
	fwags |= HTT_WX_WING_FWAGS_NUWW_WX;
	fwags |= HTT_WX_WING_FWAGS_PHY_DATA_WX;

	fw_idx = __we32_to_cpu(*htt->wx_wing.awwoc_idx.vaddw);

	wing->fw_idx_shadow_weg_paddw =
		__cpu_to_we32(htt->wx_wing.awwoc_idx.paddw);
	wing->wx_wing_base_paddw = __cpu_to_we32(htt->wx_wing.base_paddw);
	wing->wx_wing_wen = __cpu_to_we16(htt->wx_wing.size);
	wing->wx_wing_bufsize = __cpu_to_we16(HTT_WX_BUF_SIZE);
	wing->fwags = __cpu_to_we16(fwags);
	wing->fw_idx_init_vaw = __cpu_to_we16(fw_idx);

	ath10k_htt_fiww_wx_desc_offset_32(hw, wing);
	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_htt_send_wx_wing_cfg_64(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	stwuct ath10k_hw_pawams *hw = &aw->hw_pawams;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	stwuct htt_wx_wing_setup_wing64 *wing;
	const int num_wx_wing = 1;
	u16 fwags;
	u32 fw_idx;
	int wen;
	int wet;

	/* HW expects the buffew to be an integwaw numbew of 4-byte
	 * "wowds"
	 */
	BUIWD_BUG_ON(!IS_AWIGNED(HTT_WX_BUF_SIZE, 4));
	BUIWD_BUG_ON((HTT_WX_BUF_SIZE & HTT_MAX_CACHE_WINE_SIZE_MASK) != 0);

	wen = sizeof(cmd->hdw) + sizeof(cmd->wx_setup_64.hdw)
	    + (sizeof(*wing) * num_wx_wing);
	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);

	cmd = (stwuct htt_cmd *)skb->data;
	wing = &cmd->wx_setup_64.wings[0];

	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_WX_WING_CFG;
	cmd->wx_setup_64.hdw.num_wings = 1;

	fwags = 0;
	fwags |= HTT_WX_WING_FWAGS_MAC80211_HDW;
	fwags |= HTT_WX_WING_FWAGS_MSDU_PAYWOAD;
	fwags |= HTT_WX_WING_FWAGS_PPDU_STAWT;
	fwags |= HTT_WX_WING_FWAGS_PPDU_END;
	fwags |= HTT_WX_WING_FWAGS_MPDU_STAWT;
	fwags |= HTT_WX_WING_FWAGS_MPDU_END;
	fwags |= HTT_WX_WING_FWAGS_MSDU_STAWT;
	fwags |= HTT_WX_WING_FWAGS_MSDU_END;
	fwags |= HTT_WX_WING_FWAGS_WX_ATTENTION;
	fwags |= HTT_WX_WING_FWAGS_FWAG_INFO;
	fwags |= HTT_WX_WING_FWAGS_UNICAST_WX;
	fwags |= HTT_WX_WING_FWAGS_MUWTICAST_WX;
	fwags |= HTT_WX_WING_FWAGS_CTWW_WX;
	fwags |= HTT_WX_WING_FWAGS_MGMT_WX;
	fwags |= HTT_WX_WING_FWAGS_NUWW_WX;
	fwags |= HTT_WX_WING_FWAGS_PHY_DATA_WX;

	fw_idx = __we32_to_cpu(*htt->wx_wing.awwoc_idx.vaddw);

	wing->fw_idx_shadow_weg_paddw = __cpu_to_we64(htt->wx_wing.awwoc_idx.paddw);
	wing->wx_wing_base_paddw = __cpu_to_we64(htt->wx_wing.base_paddw);
	wing->wx_wing_wen = __cpu_to_we16(htt->wx_wing.size);
	wing->wx_wing_bufsize = __cpu_to_we16(HTT_WX_BUF_SIZE);
	wing->fwags = __cpu_to_we16(fwags);
	wing->fw_idx_init_vaw = __cpu_to_we16(fw_idx);

	ath10k_htt_fiww_wx_desc_offset_64(hw, wing);
	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_htt_send_wx_wing_cfg_hw(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	stwuct htt_wx_wing_setup_wing32 *wing;
	const int num_wx_wing = 1;
	u16 fwags;
	int wen;
	int wet;

	/*
	 * the HW expects the buffew to be an integwaw numbew of 4-byte
	 * "wowds"
	 */
	BUIWD_BUG_ON(!IS_AWIGNED(HTT_WX_BUF_SIZE, 4));
	BUIWD_BUG_ON((HTT_WX_BUF_SIZE & HTT_MAX_CACHE_WINE_SIZE_MASK) != 0);

	wen = sizeof(cmd->hdw) + sizeof(cmd->wx_setup_32.hdw)
	    + (sizeof(*wing) * num_wx_wing);
	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);

	cmd = (stwuct htt_cmd *)skb->data;
	wing = &cmd->wx_setup_32.wings[0];

	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_WX_WING_CFG;
	cmd->wx_setup_32.hdw.num_wings = 1;

	fwags = 0;
	fwags |= HTT_WX_WING_FWAGS_MSDU_PAYWOAD;
	fwags |= HTT_WX_WING_FWAGS_UNICAST_WX;
	fwags |= HTT_WX_WING_FWAGS_MUWTICAST_WX;

	memset(wing, 0, sizeof(*wing));
	wing->wx_wing_wen = __cpu_to_we16(HTT_WX_WING_SIZE_MIN);
	wing->wx_wing_bufsize = __cpu_to_we16(HTT_WX_BUF_SIZE);
	wing->fwags = __cpu_to_we16(fwags);

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_htt_h2t_aggw_cfg_msg_32(stwuct ath10k_htt *htt,
					  u8 max_subfwms_ampdu,
					  u8 max_subfwms_amsdu)
{
	stwuct ath10k *aw = htt->aw;
	stwuct htt_aggw_conf *aggw_conf;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	int wen;
	int wet;

	/* Fiwmwawe defauwts awe: amsdu = 3 and ampdu = 64 */

	if (max_subfwms_ampdu == 0 || max_subfwms_ampdu > 64)
		wetuwn -EINVAW;

	if (max_subfwms_amsdu == 0 || max_subfwms_amsdu > 31)
		wetuwn -EINVAW;

	wen = sizeof(cmd->hdw);
	wen += sizeof(cmd->aggw_conf);

	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_AGGW_CFG;

	aggw_conf = &cmd->aggw_conf;
	aggw_conf->max_num_ampdu_subfwames = max_subfwms_ampdu;
	aggw_conf->max_num_amsdu_subfwames = max_subfwms_amsdu;

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt h2t aggw cfg msg amsdu %d ampdu %d",
		   aggw_conf->max_num_amsdu_subfwames,
		   aggw_conf->max_num_ampdu_subfwames);

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_htt_h2t_aggw_cfg_msg_v2(stwuct ath10k_htt *htt,
					  u8 max_subfwms_ampdu,
					  u8 max_subfwms_amsdu)
{
	stwuct ath10k *aw = htt->aw;
	stwuct htt_aggw_conf_v2 *aggw_conf;
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	int wen;
	int wet;

	/* Fiwmwawe defauwts awe: amsdu = 3 and ampdu = 64 */

	if (max_subfwms_ampdu == 0 || max_subfwms_ampdu > 64)
		wetuwn -EINVAW;

	if (max_subfwms_amsdu == 0 || max_subfwms_amsdu > 31)
		wetuwn -EINVAW;

	wen = sizeof(cmd->hdw);
	wen += sizeof(cmd->aggw_conf_v2);

	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_AGGW_CFG;

	aggw_conf = &cmd->aggw_conf_v2;
	aggw_conf->max_num_ampdu_subfwames = max_subfwms_ampdu;
	aggw_conf->max_num_amsdu_subfwames = max_subfwms_amsdu;

	ath10k_dbg(aw, ATH10K_DBG_HTT, "htt h2t aggw cfg msg amsdu %d ampdu %d",
		   aggw_conf->max_num_amsdu_subfwames,
		   aggw_conf->max_num_ampdu_subfwames);

	wet = ath10k_htc_send(&htt->aw->htc, htt->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath10k_htt_tx_fetch_wesp(stwuct ath10k *aw,
			     __we32 token,
			     __we16 fetch_seq_num,
			     stwuct htt_tx_fetch_wecowd *wecowds,
			     size_t num_wecowds)
{
	stwuct sk_buff *skb;
	stwuct htt_cmd *cmd;
	const u16 wesp_id = 0;
	int wen = 0;
	int wet;

	/* Wesponse IDs awe echo-ed back onwy fow host dwivew convenience
	 * puwposes. They awen't used fow anything in the dwivew yet so use 0.
	 */

	wen += sizeof(cmd->hdw);
	wen += sizeof(cmd->tx_fetch_wesp);
	wen += sizeof(cmd->tx_fetch_wesp.wecowds[0]) * num_wecowds;

	skb = ath10k_htc_awwoc_skb(aw, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_cmd *)skb->data;
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_TX_FETCH_WESP;
	cmd->tx_fetch_wesp.wesp_id = cpu_to_we16(wesp_id);
	cmd->tx_fetch_wesp.fetch_seq_num = fetch_seq_num;
	cmd->tx_fetch_wesp.num_wecowds = cpu_to_we16(num_wecowds);
	cmd->tx_fetch_wesp.token = token;

	memcpy(cmd->tx_fetch_wesp.wecowds, wecowds,
	       sizeof(wecowds[0]) * num_wecowds);

	wet = ath10k_htc_send(&aw->htc, aw->htt.eid, skb);
	if (wet) {
		ath10k_wawn(aw, "faiwed to submit htc command: %d\n", wet);
		goto eww_fwee_skb;
	}

	wetuwn 0;

eww_fwee_skb:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static u8 ath10k_htt_tx_get_vdev_id(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);
	stwuct ath10k_vif *awvif;

	if (info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN) {
		wetuwn aw->scan.vdev_id;
	} ewse if (cb->vif) {
		awvif = (void *)cb->vif->dwv_pwiv;
		wetuwn awvif->vdev_id;
	} ewse if (aw->monitow_stawted) {
		wetuwn aw->monitow_vdev_id;
	} ewse {
		wetuwn 0;
	}
}

static u8 ath10k_htt_tx_get_tid(stwuct sk_buff *skb, boow is_eth)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	stwuct ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);

	if (!is_eth && ieee80211_is_mgmt(hdw->fwame_contwow))
		wetuwn HTT_DATA_TX_EXT_TID_MGMT;
	ewse if (cb->fwags & ATH10K_SKB_F_QOS)
		wetuwn skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
	ewse
		wetuwn HTT_DATA_TX_EXT_TID_NON_QOS_MCAST_BCAST;
}

int ath10k_htt_mgmt_tx(stwuct ath10k_htt *htt, stwuct sk_buff *msdu)
{
	stwuct ath10k *aw = htt->aw;
	stwuct device *dev = aw->dev;
	stwuct sk_buff *txdesc = NUWW;
	stwuct htt_cmd *cmd;
	stwuct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(aw, msdu);
	int wen = 0;
	int msdu_id = -1;
	int wes;
	const u8 *peew_addw;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)msdu->data;

	wen += sizeof(cmd->hdw);
	wen += sizeof(cmd->mgmt_tx);

	wes = ath10k_htt_tx_awwoc_msdu_id(htt, msdu);
	if (wes < 0)
		goto eww;

	msdu_id = wes;

	if ((ieee80211_is_action(hdw->fwame_contwow) ||
	     ieee80211_is_deauth(hdw->fwame_contwow) ||
	     ieee80211_is_disassoc(hdw->fwame_contwow)) &&
	     ieee80211_has_pwotected(hdw->fwame_contwow)) {
		peew_addw = hdw->addw1;
		if (is_muwticast_ethew_addw(peew_addw)) {
			skb_put(msdu, sizeof(stwuct ieee80211_mmie_16));
		} ewse {
			if (skb_cb->ucast_ciphew == WWAN_CIPHEW_SUITE_GCMP ||
			    skb_cb->ucast_ciphew == WWAN_CIPHEW_SUITE_GCMP_256)
				skb_put(msdu, IEEE80211_GCMP_MIC_WEN);
			ewse
				skb_put(msdu, IEEE80211_CCMP_MIC_WEN);
		}
	}

	txdesc = ath10k_htc_awwoc_skb(aw, wen);
	if (!txdesc) {
		wes = -ENOMEM;
		goto eww_fwee_msdu_id;
	}

	skb_cb->paddw = dma_map_singwe(dev, msdu->data, msdu->wen,
				       DMA_TO_DEVICE);
	wes = dma_mapping_ewwow(dev, skb_cb->paddw);
	if (wes) {
		wes = -EIO;
		goto eww_fwee_txdesc;
	}

	skb_put(txdesc, wen);
	cmd = (stwuct htt_cmd *)txdesc->data;
	memset(cmd, 0, wen);

	cmd->hdw.msg_type         = HTT_H2T_MSG_TYPE_MGMT_TX;
	cmd->mgmt_tx.msdu_paddw = __cpu_to_we32(ATH10K_SKB_CB(msdu)->paddw);
	cmd->mgmt_tx.wen        = __cpu_to_we32(msdu->wen);
	cmd->mgmt_tx.desc_id    = __cpu_to_we32(msdu_id);
	cmd->mgmt_tx.vdev_id    = __cpu_to_we32(vdev_id);
	memcpy(cmd->mgmt_tx.hdw, msdu->data,
	       min_t(int, msdu->wen, HTT_MGMT_FWM_HDW_DOWNWOAD_WEN));

	wes = ath10k_htc_send(&htt->aw->htc, htt->eid, txdesc);
	if (wes)
		goto eww_unmap_msdu;

	wetuwn 0;

eww_unmap_msdu:
	if (aw->bus_pawam.dev_type != ATH10K_DEV_TYPE_HW)
		dma_unmap_singwe(dev, skb_cb->paddw, msdu->wen, DMA_TO_DEVICE);
eww_fwee_txdesc:
	dev_kfwee_skb_any(txdesc);
eww_fwee_msdu_id:
	spin_wock_bh(&htt->tx_wock);
	ath10k_htt_tx_fwee_msdu_id(htt, msdu_id);
	spin_unwock_bh(&htt->tx_wock);
eww:
	wetuwn wes;
}

#define HTT_TX_HW_NEEDED_HEADWOOM \
	(unsigned int)(sizeof(stwuct htt_cmd_hdw) + \
	sizeof(stwuct htt_data_tx_desc) + \
	sizeof(stwuct ath10k_htc_hdw))

static int ath10k_htt_tx_hw(stwuct ath10k_htt *htt, enum ath10k_hw_txwx_mode txmode,
			    stwuct sk_buff *msdu)
{
	stwuct ath10k *aw = htt->aw;
	int wes, data_wen;
	stwuct htt_cmd_hdw *cmd_hdw;
	stwuct htt_data_tx_desc *tx_desc;
	stwuct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	stwuct sk_buff *tmp_skb;
	boow is_eth = (txmode == ATH10K_HW_TXWX_ETHEWNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(aw, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	u8 fwags0 = 0;
	u16 fwags1 = 0;
	u16 msdu_id = 0;

	if (!is_eth) {
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)msdu->data;

		if ((ieee80211_is_action(hdw->fwame_contwow) ||
		     ieee80211_is_deauth(hdw->fwame_contwow) ||
		     ieee80211_is_disassoc(hdw->fwame_contwow)) &&
		     ieee80211_has_pwotected(hdw->fwame_contwow)) {
			skb_put(msdu, IEEE80211_CCMP_MIC_WEN);
		}
	}

	data_wen = msdu->wen;

	switch (txmode) {
	case ATH10K_HW_TXWX_WAW:
	case ATH10K_HW_TXWX_NATIVE_WIFI:
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_MAC_HDW_PWESENT;
		fawwthwough;
	case ATH10K_HW_TXWX_ETHEWNET:
		fwags0 |= SM(txmode, HTT_DATA_TX_DESC_FWAGS0_PKT_TYPE);
		bweak;
	case ATH10K_HW_TXWX_MGMT:
		fwags0 |= SM(ATH10K_HW_TXWX_MGMT,
			     HTT_DATA_TX_DESC_FWAGS0_PKT_TYPE);
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_MAC_HDW_PWESENT;

		if (htt->disabwe_tx_comp)
			fwags1 |= HTT_DATA_TX_DESC_FWAGS1_TX_COMPWETE;
		bweak;
	}

	if (skb_cb->fwags & ATH10K_SKB_F_NO_HWCWYPT)
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_NO_ENCWYPT;

	fwags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FWAGS1_VDEV_ID);
	fwags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FWAGS1_EXT_TID);
	if (msdu->ip_summed == CHECKSUM_PAWTIAW &&
	    !test_bit(ATH10K_FWAG_WAW_MODE, &aw->dev_fwags)) {
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_CKSUM_W3_OFFWOAD;
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_CKSUM_W4_OFFWOAD;
	}

	/* Pwepend the HTT headew and TX desc stwuct to the data message
	 * and weawwoc the skb if it does not have enough headwoom.
	 */
	if (skb_headwoom(msdu) < HTT_TX_HW_NEEDED_HEADWOOM) {
		tmp_skb = msdu;

		ath10k_dbg(htt->aw, ATH10K_DBG_HTT,
			   "Not enough headwoom in skb. Cuwwent headwoom: %u, needed: %u. Weawwocating...\n",
			   skb_headwoom(msdu), HTT_TX_HW_NEEDED_HEADWOOM);
		msdu = skb_weawwoc_headwoom(msdu, HTT_TX_HW_NEEDED_HEADWOOM);
		kfwee_skb(tmp_skb);
		if (!msdu) {
			ath10k_wawn(htt->aw, "htt hw tx: Unabwe to weawwoc skb!\n");
			wes = -ENOMEM;
			goto out;
		}
	}

	if (aw->bus_pawam.hw_msdu_ids) {
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_POSTPONED;
		wes = ath10k_htt_tx_awwoc_msdu_id(htt, msdu);
		if (wes < 0) {
			ath10k_eww(aw, "msdu_id awwocation faiwed %d\n", wes);
			goto out;
		}
		msdu_id = wes;
	}

	/* As msdu is fweed by mac80211 (in ieee80211_tx_status()) and by
	 * ath10k (in ath10k_htt_htc_tx_compwete()) we have to incwease
	 * wefewence by one to avoid a use-aftew-fwee case and a doubwe
	 * fwee.
	 */
	skb_get(msdu);

	skb_push(msdu, sizeof(*cmd_hdw));
	skb_push(msdu, sizeof(*tx_desc));
	cmd_hdw = (stwuct htt_cmd_hdw *)msdu->data;
	tx_desc = (stwuct htt_data_tx_desc *)(msdu->data + sizeof(*cmd_hdw));

	cmd_hdw->msg_type = HTT_H2T_MSG_TYPE_TX_FWM;
	tx_desc->fwags0 = fwags0;
	tx_desc->fwags1 = __cpu_to_we16(fwags1);
	tx_desc->wen = __cpu_to_we16(data_wen);
	tx_desc->id = __cpu_to_we16(msdu_id);
	tx_desc->fwags_paddw = 0; /* awways zewo */
	/* Initiawize peew_id to INVAWID_PEEW because this is NOT
	 * Weinjection path
	 */
	tx_desc->peewid = __cpu_to_we32(HTT_INVAWID_PEEWID);

	wes = ath10k_htc_send_hw(&htt->aw->htc, htt->eid, msdu);

out:
	wetuwn wes;
}

static int ath10k_htt_tx_32(stwuct ath10k_htt *htt,
			    enum ath10k_hw_txwx_mode txmode,
			    stwuct sk_buff *msdu)
{
	stwuct ath10k *aw = htt->aw;
	stwuct device *dev = aw->dev;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	stwuct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	stwuct ath10k_hif_sg_item sg_items[2];
	stwuct ath10k_htt_txbuf_32 *txbuf;
	stwuct htt_data_tx_desc_fwag *fwags;
	boow is_eth = (txmode == ATH10K_HW_TXWX_ETHEWNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(aw, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	int pwefetch_wen;
	int wes;
	u8 fwags0 = 0;
	u16 msdu_id, fwags1 = 0;
	u16 fweq = 0;
	u32 fwags_paddw = 0;
	u32 txbuf_paddw;
	stwuct htt_msdu_ext_desc *ext_desc = NUWW;
	stwuct htt_msdu_ext_desc *ext_desc_t = NUWW;

	wes = ath10k_htt_tx_awwoc_msdu_id(htt, msdu);
	if (wes < 0)
		goto eww;

	msdu_id = wes;

	pwefetch_wen = min(htt->pwefetch_wen, msdu->wen);
	pwefetch_wen = woundup(pwefetch_wen, 4);

	txbuf = htt->txbuf.vaddw_txbuff_32 + msdu_id;
	txbuf_paddw = htt->txbuf.paddw +
		      (sizeof(stwuct ath10k_htt_txbuf_32) * msdu_id);

	if (!is_eth) {
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)msdu->data;

		if ((ieee80211_is_action(hdw->fwame_contwow) ||
		     ieee80211_is_deauth(hdw->fwame_contwow) ||
		     ieee80211_is_disassoc(hdw->fwame_contwow)) &&
		     ieee80211_has_pwotected(hdw->fwame_contwow)) {
			skb_put(msdu, IEEE80211_CCMP_MIC_WEN);
		} ewse if (!(skb_cb->fwags & ATH10K_SKB_F_NO_HWCWYPT) &&
			   txmode == ATH10K_HW_TXWX_WAW &&
			   ieee80211_has_pwotected(hdw->fwame_contwow)) {
			skb_put(msdu, IEEE80211_CCMP_MIC_WEN);
		}
	}

	skb_cb->paddw = dma_map_singwe(dev, msdu->data, msdu->wen,
				       DMA_TO_DEVICE);
	wes = dma_mapping_ewwow(dev, skb_cb->paddw);
	if (wes) {
		wes = -EIO;
		goto eww_fwee_msdu_id;
	}

	if (unwikewy(info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN))
		fweq = aw->scan.woc_fweq;

	switch (txmode) {
	case ATH10K_HW_TXWX_WAW:
	case ATH10K_HW_TXWX_NATIVE_WIFI:
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_MAC_HDW_PWESENT;
		fawwthwough;
	case ATH10K_HW_TXWX_ETHEWNET:
		if (aw->hw_pawams.continuous_fwag_desc) {
			ext_desc_t = htt->fwag_desc.vaddw_desc_32;
			memset(&ext_desc_t[msdu_id], 0,
			       sizeof(stwuct htt_msdu_ext_desc));
			fwags = (stwuct htt_data_tx_desc_fwag *)
				&ext_desc_t[msdu_id].fwags;
			ext_desc = &ext_desc_t[msdu_id];
			fwags[0].twowd_addw.paddw_wo =
				__cpu_to_we32(skb_cb->paddw);
			fwags[0].twowd_addw.paddw_hi = 0;
			fwags[0].twowd_addw.wen_16 = __cpu_to_we16(msdu->wen);

			fwags_paddw =  htt->fwag_desc.paddw +
				(sizeof(stwuct htt_msdu_ext_desc) * msdu_id);
		} ewse {
			fwags = txbuf->fwags;
			fwags[0].dwowd_addw.paddw =
				__cpu_to_we32(skb_cb->paddw);
			fwags[0].dwowd_addw.wen = __cpu_to_we32(msdu->wen);
			fwags[1].dwowd_addw.paddw = 0;
			fwags[1].dwowd_addw.wen = 0;

			fwags_paddw = txbuf_paddw;
		}
		fwags0 |= SM(txmode, HTT_DATA_TX_DESC_FWAGS0_PKT_TYPE);
		bweak;
	case ATH10K_HW_TXWX_MGMT:
		fwags0 |= SM(ATH10K_HW_TXWX_MGMT,
			     HTT_DATA_TX_DESC_FWAGS0_PKT_TYPE);
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_MAC_HDW_PWESENT;

		fwags_paddw = skb_cb->paddw;
		bweak;
	}

	/* Nowmawwy aww commands go thwough HTC which manages tx cwedits fow
	 * each endpoint and notifies when tx is compweted.
	 *
	 * HTT endpoint is cweditwess so thewe's no need to cawe about HTC
	 * fwags. In that case it is twiviaw to fiww the HTC headew hewe.
	 *
	 * MSDU twansmission is considewed compweted upon HTT event. This
	 * impwies no wewevant wesouwces can be fweed untiw aftew the event is
	 * weceived. That's why HTC tx compwetion handwew itsewf is ignowed by
	 * setting NUWW to twansfew_context fow aww sg items.
	 *
	 * Thewe is simpwy no point in pushing HTT TX_FWM thwough HTC tx path
	 * as it's a waste of wesouwces. By bypassing HTC it is possibwe to
	 * avoid extwa memowy awwocations, compwess data stwuctuwes and thus
	 * impwove pewfowmance.
	 */

	txbuf->htc_hdw.eid = htt->eid;
	txbuf->htc_hdw.wen = __cpu_to_we16(sizeof(txbuf->cmd_hdw) +
					   sizeof(txbuf->cmd_tx) +
					   pwefetch_wen);
	txbuf->htc_hdw.fwags = 0;

	if (skb_cb->fwags & ATH10K_SKB_F_NO_HWCWYPT)
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_NO_ENCWYPT;

	fwags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FWAGS1_VDEV_ID);
	fwags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FWAGS1_EXT_TID);
	if (msdu->ip_summed == CHECKSUM_PAWTIAW &&
	    !test_bit(ATH10K_FWAG_WAW_MODE, &aw->dev_fwags)) {
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_CKSUM_W3_OFFWOAD;
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_CKSUM_W4_OFFWOAD;
		if (aw->hw_pawams.continuous_fwag_desc)
			ext_desc->fwags |= HTT_MSDU_CHECKSUM_ENABWE;
	}

	/* Pwevent fiwmwawe fwom sending up tx inspection wequests. Thewe's
	 * nothing ath10k can do with fwames wequested fow inspection so fowce
	 * it to simpwy wewy a weguwaw tx compwetion with discawd status.
	 */
	fwags1 |= HTT_DATA_TX_DESC_FWAGS1_POSTPONED;

	txbuf->cmd_hdw.msg_type = HTT_H2T_MSG_TYPE_TX_FWM;
	txbuf->cmd_tx.fwags0 = fwags0;
	txbuf->cmd_tx.fwags1 = __cpu_to_we16(fwags1);
	txbuf->cmd_tx.wen = __cpu_to_we16(msdu->wen);
	txbuf->cmd_tx.id = __cpu_to_we16(msdu_id);
	txbuf->cmd_tx.fwags_paddw = __cpu_to_we32(fwags_paddw);
	if (ath10k_mac_tx_fwm_has_fweq(aw)) {
		txbuf->cmd_tx.offchan_tx.peewid =
				__cpu_to_we16(HTT_INVAWID_PEEWID);
		txbuf->cmd_tx.offchan_tx.fweq =
				__cpu_to_we16(fweq);
	} ewse {
		txbuf->cmd_tx.peewid =
				__cpu_to_we32(HTT_INVAWID_PEEWID);
	}

	twace_ath10k_htt_tx(aw, msdu_id, msdu->wen, vdev_id, tid);
	ath10k_dbg(aw, ATH10K_DBG_HTT,
		   "htt tx fwags0 %u fwags1 %u wen %d id %u fwags_paddw %pad, msdu_paddw %pad vdev %u tid %u fweq %u\n",
		   fwags0, fwags1, msdu->wen, msdu_id, &fwags_paddw,
		   &skb_cb->paddw, vdev_id, tid, fweq);
	ath10k_dbg_dump(aw, ATH10K_DBG_HTT_DUMP, NUWW, "htt tx msdu: ",
			msdu->data, msdu->wen);
	twace_ath10k_tx_hdw(aw, msdu->data, msdu->wen);
	twace_ath10k_tx_paywoad(aw, msdu->data, msdu->wen);

	sg_items[0].twansfew_id = 0;
	sg_items[0].twansfew_context = NUWW;
	sg_items[0].vaddw = &txbuf->htc_hdw;
	sg_items[0].paddw = txbuf_paddw +
			    sizeof(txbuf->fwags);
	sg_items[0].wen = sizeof(txbuf->htc_hdw) +
			  sizeof(txbuf->cmd_hdw) +
			  sizeof(txbuf->cmd_tx);

	sg_items[1].twansfew_id = 0;
	sg_items[1].twansfew_context = NUWW;
	sg_items[1].vaddw = msdu->data;
	sg_items[1].paddw = skb_cb->paddw;
	sg_items[1].wen = pwefetch_wen;

	wes = ath10k_hif_tx_sg(htt->aw,
			       htt->aw->htc.endpoint[htt->eid].uw_pipe_id,
			       sg_items, AWWAY_SIZE(sg_items));
	if (wes)
		goto eww_unmap_msdu;

	wetuwn 0;

eww_unmap_msdu:
	dma_unmap_singwe(dev, skb_cb->paddw, msdu->wen, DMA_TO_DEVICE);
eww_fwee_msdu_id:
	spin_wock_bh(&htt->tx_wock);
	ath10k_htt_tx_fwee_msdu_id(htt, msdu_id);
	spin_unwock_bh(&htt->tx_wock);
eww:
	wetuwn wes;
}

static int ath10k_htt_tx_64(stwuct ath10k_htt *htt,
			    enum ath10k_hw_txwx_mode txmode,
			    stwuct sk_buff *msdu)
{
	stwuct ath10k *aw = htt->aw;
	stwuct device *dev = aw->dev;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	stwuct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	stwuct ath10k_hif_sg_item sg_items[2];
	stwuct ath10k_htt_txbuf_64 *txbuf;
	stwuct htt_data_tx_desc_fwag *fwags;
	boow is_eth = (txmode == ATH10K_HW_TXWX_ETHEWNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(aw, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	int pwefetch_wen;
	int wes;
	u8 fwags0 = 0;
	u16 msdu_id, fwags1 = 0;
	u16 fweq = 0;
	dma_addw_t fwags_paddw = 0;
	dma_addw_t txbuf_paddw;
	stwuct htt_msdu_ext_desc_64 *ext_desc = NUWW;
	stwuct htt_msdu_ext_desc_64 *ext_desc_t = NUWW;

	wes = ath10k_htt_tx_awwoc_msdu_id(htt, msdu);
	if (wes < 0)
		goto eww;

	msdu_id = wes;

	pwefetch_wen = min(htt->pwefetch_wen, msdu->wen);
	pwefetch_wen = woundup(pwefetch_wen, 4);

	txbuf = htt->txbuf.vaddw_txbuff_64 + msdu_id;
	txbuf_paddw = htt->txbuf.paddw +
		      (sizeof(stwuct ath10k_htt_txbuf_64) * msdu_id);

	if (!is_eth) {
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)msdu->data;

		if ((ieee80211_is_action(hdw->fwame_contwow) ||
		     ieee80211_is_deauth(hdw->fwame_contwow) ||
		     ieee80211_is_disassoc(hdw->fwame_contwow)) &&
		     ieee80211_has_pwotected(hdw->fwame_contwow)) {
			skb_put(msdu, IEEE80211_CCMP_MIC_WEN);
		} ewse if (!(skb_cb->fwags & ATH10K_SKB_F_NO_HWCWYPT) &&
			   txmode == ATH10K_HW_TXWX_WAW &&
			   ieee80211_has_pwotected(hdw->fwame_contwow)) {
			skb_put(msdu, IEEE80211_CCMP_MIC_WEN);
		}
	}

	skb_cb->paddw = dma_map_singwe(dev, msdu->data, msdu->wen,
				       DMA_TO_DEVICE);
	wes = dma_mapping_ewwow(dev, skb_cb->paddw);
	if (wes) {
		wes = -EIO;
		goto eww_fwee_msdu_id;
	}

	if (unwikewy(info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN))
		fweq = aw->scan.woc_fweq;

	switch (txmode) {
	case ATH10K_HW_TXWX_WAW:
	case ATH10K_HW_TXWX_NATIVE_WIFI:
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_MAC_HDW_PWESENT;
		fawwthwough;
	case ATH10K_HW_TXWX_ETHEWNET:
		if (aw->hw_pawams.continuous_fwag_desc) {
			ext_desc_t = htt->fwag_desc.vaddw_desc_64;
			memset(&ext_desc_t[msdu_id], 0,
			       sizeof(stwuct htt_msdu_ext_desc_64));
			fwags = (stwuct htt_data_tx_desc_fwag *)
				&ext_desc_t[msdu_id].fwags;
			ext_desc = &ext_desc_t[msdu_id];
			fwags[0].twowd_addw.paddw_wo =
				__cpu_to_we32(skb_cb->paddw);
			fwags[0].twowd_addw.paddw_hi =
				__cpu_to_we16(uppew_32_bits(skb_cb->paddw));
			fwags[0].twowd_addw.wen_16 = __cpu_to_we16(msdu->wen);

			fwags_paddw =  htt->fwag_desc.paddw +
			   (sizeof(stwuct htt_msdu_ext_desc_64) * msdu_id);
		} ewse {
			fwags = txbuf->fwags;
			fwags[0].twowd_addw.paddw_wo =
						__cpu_to_we32(skb_cb->paddw);
			fwags[0].twowd_addw.paddw_hi =
				__cpu_to_we16(uppew_32_bits(skb_cb->paddw));
			fwags[0].twowd_addw.wen_16 = __cpu_to_we16(msdu->wen);
			fwags[1].twowd_addw.paddw_wo = 0;
			fwags[1].twowd_addw.paddw_hi = 0;
			fwags[1].twowd_addw.wen_16 = 0;
		}
		fwags0 |= SM(txmode, HTT_DATA_TX_DESC_FWAGS0_PKT_TYPE);
		bweak;
	case ATH10K_HW_TXWX_MGMT:
		fwags0 |= SM(ATH10K_HW_TXWX_MGMT,
			     HTT_DATA_TX_DESC_FWAGS0_PKT_TYPE);
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_MAC_HDW_PWESENT;

		fwags_paddw = skb_cb->paddw;
		bweak;
	}

	/* Nowmawwy aww commands go thwough HTC which manages tx cwedits fow
	 * each endpoint and notifies when tx is compweted.
	 *
	 * HTT endpoint is cweditwess so thewe's no need to cawe about HTC
	 * fwags. In that case it is twiviaw to fiww the HTC headew hewe.
	 *
	 * MSDU twansmission is considewed compweted upon HTT event. This
	 * impwies no wewevant wesouwces can be fweed untiw aftew the event is
	 * weceived. That's why HTC tx compwetion handwew itsewf is ignowed by
	 * setting NUWW to twansfew_context fow aww sg items.
	 *
	 * Thewe is simpwy no point in pushing HTT TX_FWM thwough HTC tx path
	 * as it's a waste of wesouwces. By bypassing HTC it is possibwe to
	 * avoid extwa memowy awwocations, compwess data stwuctuwes and thus
	 * impwove pewfowmance.
	 */

	txbuf->htc_hdw.eid = htt->eid;
	txbuf->htc_hdw.wen = __cpu_to_we16(sizeof(txbuf->cmd_hdw) +
					   sizeof(txbuf->cmd_tx) +
					   pwefetch_wen);
	txbuf->htc_hdw.fwags = 0;

	if (skb_cb->fwags & ATH10K_SKB_F_NO_HWCWYPT)
		fwags0 |= HTT_DATA_TX_DESC_FWAGS0_NO_ENCWYPT;

	fwags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FWAGS1_VDEV_ID);
	fwags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FWAGS1_EXT_TID);
	if (msdu->ip_summed == CHECKSUM_PAWTIAW &&
	    !test_bit(ATH10K_FWAG_WAW_MODE, &aw->dev_fwags)) {
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_CKSUM_W3_OFFWOAD;
		fwags1 |= HTT_DATA_TX_DESC_FWAGS1_CKSUM_W4_OFFWOAD;
		if (aw->hw_pawams.continuous_fwag_desc) {
			memset(ext_desc->tso_fwag, 0, sizeof(ext_desc->tso_fwag));
			ext_desc->tso_fwag[3] |=
				__cpu_to_we32(HTT_MSDU_CHECKSUM_ENABWE_64);
		}
	}

	/* Pwevent fiwmwawe fwom sending up tx inspection wequests. Thewe's
	 * nothing ath10k can do with fwames wequested fow inspection so fowce
	 * it to simpwy wewy a weguwaw tx compwetion with discawd status.
	 */
	fwags1 |= HTT_DATA_TX_DESC_FWAGS1_POSTPONED;

	txbuf->cmd_hdw.msg_type = HTT_H2T_MSG_TYPE_TX_FWM;
	txbuf->cmd_tx.fwags0 = fwags0;
	txbuf->cmd_tx.fwags1 = __cpu_to_we16(fwags1);
	txbuf->cmd_tx.wen = __cpu_to_we16(msdu->wen);
	txbuf->cmd_tx.id = __cpu_to_we16(msdu_id);

	/* fiww fwagment descwiptow */
	txbuf->cmd_tx.fwags_paddw = __cpu_to_we64(fwags_paddw);
	if (ath10k_mac_tx_fwm_has_fweq(aw)) {
		txbuf->cmd_tx.offchan_tx.peewid =
				__cpu_to_we16(HTT_INVAWID_PEEWID);
		txbuf->cmd_tx.offchan_tx.fweq =
				__cpu_to_we16(fweq);
	} ewse {
		txbuf->cmd_tx.peewid =
				__cpu_to_we32(HTT_INVAWID_PEEWID);
	}

	twace_ath10k_htt_tx(aw, msdu_id, msdu->wen, vdev_id, tid);
	ath10k_dbg(aw, ATH10K_DBG_HTT,
		   "htt tx fwags0 %u fwags1 %u wen %d id %u fwags_paddw %pad, msdu_paddw %pad vdev %u tid %u fweq %u\n",
		   fwags0, fwags1, msdu->wen, msdu_id, &fwags_paddw,
		   &skb_cb->paddw, vdev_id, tid, fweq);
	ath10k_dbg_dump(aw, ATH10K_DBG_HTT_DUMP, NUWW, "htt tx msdu: ",
			msdu->data, msdu->wen);
	twace_ath10k_tx_hdw(aw, msdu->data, msdu->wen);
	twace_ath10k_tx_paywoad(aw, msdu->data, msdu->wen);

	sg_items[0].twansfew_id = 0;
	sg_items[0].twansfew_context = NUWW;
	sg_items[0].vaddw = &txbuf->htc_hdw;
	sg_items[0].paddw = txbuf_paddw +
			    sizeof(txbuf->fwags);
	sg_items[0].wen = sizeof(txbuf->htc_hdw) +
			  sizeof(txbuf->cmd_hdw) +
			  sizeof(txbuf->cmd_tx);

	sg_items[1].twansfew_id = 0;
	sg_items[1].twansfew_context = NUWW;
	sg_items[1].vaddw = msdu->data;
	sg_items[1].paddw = skb_cb->paddw;
	sg_items[1].wen = pwefetch_wen;

	wes = ath10k_hif_tx_sg(htt->aw,
			       htt->aw->htc.endpoint[htt->eid].uw_pipe_id,
			       sg_items, AWWAY_SIZE(sg_items));
	if (wes)
		goto eww_unmap_msdu;

	wetuwn 0;

eww_unmap_msdu:
	dma_unmap_singwe(dev, skb_cb->paddw, msdu->wen, DMA_TO_DEVICE);
eww_fwee_msdu_id:
	spin_wock_bh(&htt->tx_wock);
	ath10k_htt_tx_fwee_msdu_id(htt, msdu_id);
	spin_unwock_bh(&htt->tx_wock);
eww:
	wetuwn wes;
}

static const stwuct ath10k_htt_tx_ops htt_tx_ops_32 = {
	.htt_send_wx_wing_cfg = ath10k_htt_send_wx_wing_cfg_32,
	.htt_send_fwag_desc_bank_cfg = ath10k_htt_send_fwag_desc_bank_cfg_32,
	.htt_awwoc_fwag_desc = ath10k_htt_tx_awwoc_cont_fwag_desc_32,
	.htt_fwee_fwag_desc = ath10k_htt_tx_fwee_cont_fwag_desc_32,
	.htt_tx = ath10k_htt_tx_32,
	.htt_awwoc_txbuff = ath10k_htt_tx_awwoc_cont_txbuf_32,
	.htt_fwee_txbuff = ath10k_htt_tx_fwee_cont_txbuf_32,
	.htt_h2t_aggw_cfg_msg = ath10k_htt_h2t_aggw_cfg_msg_32,
};

static const stwuct ath10k_htt_tx_ops htt_tx_ops_64 = {
	.htt_send_wx_wing_cfg = ath10k_htt_send_wx_wing_cfg_64,
	.htt_send_fwag_desc_bank_cfg = ath10k_htt_send_fwag_desc_bank_cfg_64,
	.htt_awwoc_fwag_desc = ath10k_htt_tx_awwoc_cont_fwag_desc_64,
	.htt_fwee_fwag_desc = ath10k_htt_tx_fwee_cont_fwag_desc_64,
	.htt_tx = ath10k_htt_tx_64,
	.htt_awwoc_txbuff = ath10k_htt_tx_awwoc_cont_txbuf_64,
	.htt_fwee_txbuff = ath10k_htt_tx_fwee_cont_txbuf_64,
	.htt_h2t_aggw_cfg_msg = ath10k_htt_h2t_aggw_cfg_msg_v2,
};

static const stwuct ath10k_htt_tx_ops htt_tx_ops_hw = {
	.htt_send_wx_wing_cfg = ath10k_htt_send_wx_wing_cfg_hw,
	.htt_send_fwag_desc_bank_cfg = ath10k_htt_send_fwag_desc_bank_cfg_32,
	.htt_tx = ath10k_htt_tx_hw,
	.htt_h2t_aggw_cfg_msg = ath10k_htt_h2t_aggw_cfg_msg_32,
	.htt_fwush_tx = ath10k_htt_fwush_tx_queue,
};

void ath10k_htt_set_tx_ops(stwuct ath10k_htt *htt)
{
	stwuct ath10k *aw = htt->aw;

	if (aw->bus_pawam.dev_type == ATH10K_DEV_TYPE_HW)
		htt->tx_ops = &htt_tx_ops_hw;
	ewse if (aw->hw_pawams.tawget_64bit)
		htt->tx_ops = &htt_tx_ops_64;
	ewse
		htt->tx_ops = &htt_tx_ops_32;
}
