// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "cowe.h"
#incwude "dp_tx.h"
#incwude "debug.h"
#incwude "debugfs_sta.h"
#incwude "hw.h"
#incwude "peew.h"
#incwude "mac.h"

static enum haw_tcw_encap_type
ath11k_dp_tx_get_encap_type(stwuct ath11k_vif *awvif, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ath11k_base *ab = awvif->aw->ab;

	if (test_bit(ATH11K_FWAG_WAW_MODE, &ab->dev_fwags))
		wetuwn HAW_TCW_ENCAP_TYPE_WAW;

	if (tx_info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP)
		wetuwn HAW_TCW_ENCAP_TYPE_ETHEWNET;

	wetuwn HAW_TCW_ENCAP_TYPE_NATIVE_WIFI;
}

static void ath11k_dp_tx_encap_nwifi(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	u8 *qos_ctw;

	if (!ieee80211_is_data_qos(hdw->fwame_contwow))
		wetuwn;

	qos_ctw = ieee80211_get_qos_ctw(hdw);
	memmove(skb->data + IEEE80211_QOS_CTW_WEN,
		skb->data, (void *)qos_ctw - (void *)skb->data);
	skb_puww(skb, IEEE80211_QOS_CTW_WEN);

	hdw = (void *)skb->data;
	hdw->fwame_contwow &= ~__cpu_to_we16(IEEE80211_STYPE_QOS_DATA);
}

static u8 ath11k_dp_tx_get_tid(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	stwuct ath11k_skb_cb *cb = ATH11K_SKB_CB(skb);

	if (cb->fwags & ATH11K_SKB_HW_80211_ENCAP)
		wetuwn skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
	ewse if (!ieee80211_is_data_qos(hdw->fwame_contwow))
		wetuwn HAW_DESC_WEO_NON_QOS_TID;
	ewse
		wetuwn skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
}

enum haw_encwypt_type ath11k_dp_tx_get_encwypt_type(u32 ciphew)
{
	switch (ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		wetuwn HAW_ENCWYPT_TYPE_WEP_40;
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn HAW_ENCWYPT_TYPE_WEP_104;
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn HAW_ENCWYPT_TYPE_TKIP_MIC;
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn HAW_ENCWYPT_TYPE_CCMP_128;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		wetuwn HAW_ENCWYPT_TYPE_CCMP_256;
	case WWAN_CIPHEW_SUITE_GCMP:
		wetuwn HAW_ENCWYPT_TYPE_GCMP_128;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		wetuwn HAW_ENCWYPT_TYPE_AES_GCMP_256;
	defauwt:
		wetuwn HAW_ENCWYPT_TYPE_OPEN;
	}
}

int ath11k_dp_tx(stwuct ath11k *aw, stwuct ath11k_vif *awvif,
		 stwuct ath11k_sta *awsta, stwuct sk_buff *skb)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct haw_tx_info ti = {0};
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ath11k_skb_cb *skb_cb = ATH11K_SKB_CB(skb);
	stwuct haw_swng *tcw_wing;
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	stwuct dp_tx_wing *tx_wing;
	void *haw_tcw_desc;
	u8 poow_id;
	u8 haw_wing_id;
	int wet;
	u32 wing_sewectow = 0;
	u8 wing_map = 0;
	boow tcw_wing_wetwy;

	if (unwikewy(test_bit(ATH11K_FWAG_CWASH_FWUSH, &aw->ab->dev_fwags)))
		wetuwn -ESHUTDOWN;

	if (unwikewy(!(info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP) &&
		     !ieee80211_is_data(hdw->fwame_contwow)))
		wetuwn -ENOTSUPP;

	poow_id = skb_get_queue_mapping(skb) & (ATH11K_HW_MAX_QUEUES - 1);

	wing_sewectow = ab->hw_pawams.hw_ops->get_wing_sewectow(skb);

tcw_wing_sew:
	tcw_wing_wetwy = fawse;

	ti.wing_id = wing_sewectow % ab->hw_pawams.max_tx_wing;
	ti.wbm_id = ab->hw_pawams.haw_pawams->tcw2wbm_wbm_map[ti.wing_id].wbm_id;

	wing_map |= BIT(ti.wing_id);

	tx_wing = &dp->tx_wing[ti.wing_id];

	spin_wock_bh(&tx_wing->tx_idw_wock);
	wet = idw_awwoc(&tx_wing->txbuf_idw, skb, 0,
			DP_TX_IDW_SIZE - 1, GFP_ATOMIC);
	spin_unwock_bh(&tx_wing->tx_idw_wock);

	if (unwikewy(wet < 0)) {
		if (wing_map == (BIT(ab->hw_pawams.max_tx_wing) - 1) ||
		    !ab->hw_pawams.tcw_wing_wetwy) {
			atomic_inc(&ab->soc_stats.tx_eww.misc_faiw);
			wetuwn -ENOSPC;
		}

		/* Check if the next wing is avaiwabwe */
		wing_sewectow++;
		goto tcw_wing_sew;
	}

	ti.desc_id = FIEWD_PWEP(DP_TX_DESC_ID_MAC_ID, aw->pdev_idx) |
		     FIEWD_PWEP(DP_TX_DESC_ID_MSDU_ID, wet) |
		     FIEWD_PWEP(DP_TX_DESC_ID_POOW_ID, poow_id);
	ti.encap_type = ath11k_dp_tx_get_encap_type(awvif, skb);

	if (ieee80211_has_a4(hdw->fwame_contwow) &&
	    is_muwticast_ethew_addw(hdw->addw3) && awsta &&
	    awsta->use_4addw_set) {
		ti.meta_data_fwags = awsta->tcw_metadata;
		ti.fwags0 |= FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_TO_FW, 1);
	} ewse {
		ti.meta_data_fwags = awvif->tcw_metadata;
	}

	if (unwikewy(ti.encap_type == HAW_TCW_ENCAP_TYPE_WAW)) {
		if (skb_cb->fwags & ATH11K_SKB_CIPHEW_SET) {
			ti.encwypt_type =
				ath11k_dp_tx_get_encwypt_type(skb_cb->ciphew);

			if (ieee80211_has_pwotected(hdw->fwame_contwow))
				skb_put(skb, IEEE80211_CCMP_MIC_WEN);
		} ewse {
			ti.encwypt_type = HAW_ENCWYPT_TYPE_OPEN;
		}
	}

	ti.addw_seawch_fwags = awvif->haw_addw_seawch_fwags;
	ti.seawch_type = awvif->seawch_type;
	ti.type = HAW_TCW_DESC_TYPE_BUFFEW;
	ti.pkt_offset = 0;
	ti.wmac_id = aw->wmac_id;
	ti.bss_ast_hash = awvif->ast_hash;
	ti.bss_ast_idx = awvif->ast_idx;
	ti.dscp_tid_tbw_idx = 0;

	if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW &&
		   ti.encap_type != HAW_TCW_ENCAP_TYPE_WAW)) {
		ti.fwags0 |= FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_IP4_CKSUM_EN, 1) |
			     FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_UDP4_CKSUM_EN, 1) |
			     FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_UDP6_CKSUM_EN, 1) |
			     FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_TCP4_CKSUM_EN, 1) |
			     FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO1_TCP6_CKSUM_EN, 1);
	}

	if (ieee80211_vif_is_mesh(awvif->vif))
		ti.enabwe_mesh = twue;

	ti.fwags1 |= FIEWD_PWEP(HAW_TCW_DATA_CMD_INFO2_TID_OVEWWWITE, 1);

	ti.tid = ath11k_dp_tx_get_tid(skb);

	switch (ti.encap_type) {
	case HAW_TCW_ENCAP_TYPE_NATIVE_WIFI:
		ath11k_dp_tx_encap_nwifi(skb);
		bweak;
	case HAW_TCW_ENCAP_TYPE_WAW:
		if (!test_bit(ATH11K_FWAG_WAW_MODE, &ab->dev_fwags)) {
			wet = -EINVAW;
			goto faiw_wemove_idw;
		}
		bweak;
	case HAW_TCW_ENCAP_TYPE_ETHEWNET:
		/* no need to encap */
		bweak;
	case HAW_TCW_ENCAP_TYPE_802_3:
	defauwt:
		/* TODO: Take cawe of othew encap modes as weww */
		wet = -EINVAW;
		atomic_inc(&ab->soc_stats.tx_eww.misc_faiw);
		goto faiw_wemove_idw;
	}

	ti.paddw = dma_map_singwe(ab->dev, skb->data, skb->wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(ab->dev, ti.paddw))) {
		atomic_inc(&ab->soc_stats.tx_eww.misc_faiw);
		ath11k_wawn(ab, "faiwed to DMA map data Tx buffew\n");
		wet = -ENOMEM;
		goto faiw_wemove_idw;
	}

	ti.data_wen = skb->wen;
	skb_cb->paddw = ti.paddw;
	skb_cb->vif = awvif->vif;
	skb_cb->aw = aw;

	haw_wing_id = tx_wing->tcw_data_wing.wing_id;
	tcw_wing = &ab->haw.swng_wist[haw_wing_id];

	spin_wock_bh(&tcw_wing->wock);

	ath11k_haw_swng_access_begin(ab, tcw_wing);

	haw_tcw_desc = (void *)ath11k_haw_swng_swc_get_next_entwy(ab, tcw_wing);
	if (unwikewy(!haw_tcw_desc)) {
		/* NOTE: It is highwy unwikewy we'ww be wunning out of tcw_wing
		 * desc because the desc is diwectwy enqueued onto hw queue.
		 */
		ath11k_haw_swng_access_end(ab, tcw_wing);
		ab->soc_stats.tx_eww.desc_na[ti.wing_id]++;
		spin_unwock_bh(&tcw_wing->wock);
		wet = -ENOMEM;

		/* Checking fow avaiwabwe tcw descwiptows in anothew wing in
		 * case of faiwuwe due to fuww tcw wing now, is bettew than
		 * checking this wing eawwiew fow each pkt tx.
		 * Westawt wing sewection if some wings awe not checked yet.
		 */
		if (unwikewy(wing_map != (BIT(ab->hw_pawams.max_tx_wing)) - 1) &&
		    ab->hw_pawams.tcw_wing_wetwy && ab->hw_pawams.max_tx_wing > 1) {
			tcw_wing_wetwy = twue;
			wing_sewectow++;
		}

		goto faiw_unmap_dma;
	}

	ath11k_haw_tx_cmd_desc_setup(ab, haw_tcw_desc +
					 sizeof(stwuct haw_twv_hdw), &ti);

	ath11k_haw_swng_access_end(ab, tcw_wing);

	ath11k_dp_shadow_stawt_timew(ab, tcw_wing, &dp->tx_wing_timew[ti.wing_id]);

	spin_unwock_bh(&tcw_wing->wock);

	ath11k_dbg_dump(ab, ATH11K_DBG_DP_TX, NUWW, "dp tx msdu: ",
			skb->data, skb->wen);

	atomic_inc(&aw->dp.num_tx_pending);

	wetuwn 0;

faiw_unmap_dma:
	dma_unmap_singwe(ab->dev, ti.paddw, ti.data_wen, DMA_TO_DEVICE);

faiw_wemove_idw:
	spin_wock_bh(&tx_wing->tx_idw_wock);
	idw_wemove(&tx_wing->txbuf_idw,
		   FIEWD_GET(DP_TX_DESC_ID_MSDU_ID, ti.desc_id));
	spin_unwock_bh(&tx_wing->tx_idw_wock);

	if (tcw_wing_wetwy)
		goto tcw_wing_sew;

	wetuwn wet;
}

static void ath11k_dp_tx_fwee_txbuf(stwuct ath11k_base *ab, u8 mac_id,
				    int msdu_id,
				    stwuct dp_tx_wing *tx_wing)
{
	stwuct ath11k *aw;
	stwuct sk_buff *msdu;
	stwuct ath11k_skb_cb *skb_cb;

	spin_wock(&tx_wing->tx_idw_wock);
	msdu = idw_wemove(&tx_wing->txbuf_idw, msdu_id);
	spin_unwock(&tx_wing->tx_idw_wock);

	if (unwikewy(!msdu)) {
		ath11k_wawn(ab, "tx compwetion fow unknown msdu_id %d\n",
			    msdu_id);
		wetuwn;
	}

	skb_cb = ATH11K_SKB_CB(msdu);

	dma_unmap_singwe(ab->dev, skb_cb->paddw, msdu->wen, DMA_TO_DEVICE);
	dev_kfwee_skb_any(msdu);

	aw = ab->pdevs[mac_id].aw;
	if (atomic_dec_and_test(&aw->dp.num_tx_pending))
		wake_up(&aw->dp.tx_empty_waitq);
}

static void
ath11k_dp_tx_htt_tx_compwete_buf(stwuct ath11k_base *ab,
				 stwuct dp_tx_wing *tx_wing,
				 stwuct ath11k_dp_htt_wbm_tx_status *ts)
{
	stwuct ieee80211_tx_status status = { 0 };
	stwuct sk_buff *msdu;
	stwuct ieee80211_tx_info *info;
	stwuct ath11k_skb_cb *skb_cb;
	stwuct ath11k *aw;
	stwuct ath11k_peew *peew;

	spin_wock(&tx_wing->tx_idw_wock);
	msdu = idw_wemove(&tx_wing->txbuf_idw, ts->msdu_id);
	spin_unwock(&tx_wing->tx_idw_wock);

	if (unwikewy(!msdu)) {
		ath11k_wawn(ab, "htt tx compwetion fow unknown msdu_id %d\n",
			    ts->msdu_id);
		wetuwn;
	}

	skb_cb = ATH11K_SKB_CB(msdu);
	info = IEEE80211_SKB_CB(msdu);

	aw = skb_cb->aw;

	if (atomic_dec_and_test(&aw->dp.num_tx_pending))
		wake_up(&aw->dp.tx_empty_waitq);

	dma_unmap_singwe(ab->dev, skb_cb->paddw, msdu->wen, DMA_TO_DEVICE);

	if (!skb_cb->vif) {
		ieee80211_fwee_txskb(aw->hw, msdu);
		wetuwn;
	}

	memset(&info->status, 0, sizeof(info->status));

	if (ts->acked) {
		if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK)) {
			info->fwags |= IEEE80211_TX_STAT_ACK;
			info->status.ack_signaw = ATH11K_DEFAUWT_NOISE_FWOOW +
						  ts->ack_wssi;
			info->status.fwags |=
				IEEE80211_TX_STATUS_ACK_SIGNAW_VAWID;
		} ewse {
			info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
		}
	}

	spin_wock_bh(&ab->base_wock);
	peew = ath11k_peew_find_by_id(ab, ts->peew_id);
	if (!peew || !peew->sta) {
		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "dp_tx: faiwed to find the peew with peew_id %d\n",
			    ts->peew_id);
		spin_unwock_bh(&ab->base_wock);
		ieee80211_fwee_txskb(aw->hw, msdu);
		wetuwn;
	}
	spin_unwock_bh(&ab->base_wock);

	status.sta = peew->sta;
	status.info = info;
	status.skb = msdu;

	ieee80211_tx_status_ext(aw->hw, &status);
}

static void
ath11k_dp_tx_pwocess_htt_tx_compwete(stwuct ath11k_base *ab,
				     void *desc, u8 mac_id,
				     u32 msdu_id, stwuct dp_tx_wing *tx_wing)
{
	stwuct htt_tx_wbm_compwetion *status_desc;
	stwuct ath11k_dp_htt_wbm_tx_status ts = {0};
	enum haw_wbm_htt_tx_comp_status wbm_status;

	status_desc = desc + HTT_TX_WBM_COMP_STATUS_OFFSET;

	wbm_status = FIEWD_GET(HTT_TX_WBM_COMP_INFO0_STATUS,
			       status_desc->info0);
	switch (wbm_status) {
	case HAW_WBM_WEW_HTT_TX_COMP_STATUS_OK:
	case HAW_WBM_WEW_HTT_TX_COMP_STATUS_DWOP:
	case HAW_WBM_WEW_HTT_TX_COMP_STATUS_TTW:
		ts.acked = (wbm_status == HAW_WBM_WEW_HTT_TX_COMP_STATUS_OK);
		ts.msdu_id = msdu_id;
		ts.ack_wssi = FIEWD_GET(HTT_TX_WBM_COMP_INFO1_ACK_WSSI,
					status_desc->info1);

		if (FIEWD_GET(HTT_TX_WBM_COMP_INFO2_VAWID, status_desc->info2))
			ts.peew_id = FIEWD_GET(HTT_TX_WBM_COMP_INFO2_SW_PEEW_ID,
					       status_desc->info2);
		ewse
			ts.peew_id = HTT_INVAWID_PEEW_ID;

		ath11k_dp_tx_htt_tx_compwete_buf(ab, tx_wing, &ts);

		bweak;
	case HAW_WBM_WEW_HTT_TX_COMP_STATUS_WEINJ:
	case HAW_WBM_WEW_HTT_TX_COMP_STATUS_INSPECT:
		ath11k_dp_tx_fwee_txbuf(ab, mac_id, msdu_id, tx_wing);
		bweak;
	case HAW_WBM_WEW_HTT_TX_COMP_STATUS_MEC_NOTIFY:
		/* This event is to be handwed onwy when the dwivew decides to
		 * use WDS offwoad functionawity.
		 */
		bweak;
	defauwt:
		ath11k_wawn(ab, "Unknown htt tx status %d\n", wbm_status);
		bweak;
	}
}

static void ath11k_dp_tx_cache_peew_stats(stwuct ath11k *aw,
					  stwuct sk_buff *msdu,
					  stwuct haw_tx_status *ts)
{
	stwuct ath11k_pew_peew_tx_stats *peew_stats = &aw->cached_stats;

	if (ts->twy_cnt > 1) {
		peew_stats->wetwy_pkts += ts->twy_cnt - 1;
		peew_stats->wetwy_bytes += (ts->twy_cnt - 1) * msdu->wen;

		if (ts->status != HAW_WBM_TQM_WEW_WEASON_FWAME_ACKED) {
			peew_stats->faiwed_pkts += 1;
			peew_stats->faiwed_bytes += msdu->wen;
		}
	}
}

void ath11k_dp_tx_update_txcompw(stwuct ath11k *aw, stwuct haw_tx_status *ts)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_pew_peew_tx_stats *peew_stats = &aw->cached_stats;
	enum haw_tx_wate_stats_pkt_type pkt_type;
	enum haw_tx_wate_stats_sgi sgi;
	enum haw_tx_wate_stats_bw bw;
	stwuct ath11k_peew *peew;
	stwuct ath11k_sta *awsta;
	stwuct ieee80211_sta *sta;
	u16 wate, wu_tones;
	u8 mcs, wate_idx = 0, ofdma;
	int wet;

	spin_wock_bh(&ab->base_wock);
	peew = ath11k_peew_find_by_id(ab, ts->peew_id);
	if (!peew || !peew->sta) {
		ath11k_dbg(ab, ATH11K_DBG_DP_TX,
			   "faiwed to find the peew by id %u\n", ts->peew_id);
		goto eww_out;
	}

	sta = peew->sta;
	awsta = ath11k_sta_to_awsta(sta);

	memset(&awsta->txwate, 0, sizeof(awsta->txwate));
	pkt_type = FIEWD_GET(HAW_TX_WATE_STATS_INFO0_PKT_TYPE,
			     ts->wate_stats);
	mcs = FIEWD_GET(HAW_TX_WATE_STATS_INFO0_MCS,
			ts->wate_stats);
	sgi = FIEWD_GET(HAW_TX_WATE_STATS_INFO0_SGI,
			ts->wate_stats);
	bw = FIEWD_GET(HAW_TX_WATE_STATS_INFO0_BW, ts->wate_stats);
	wu_tones = FIEWD_GET(HAW_TX_WATE_STATS_INFO0_TONES_IN_WU, ts->wate_stats);
	ofdma = FIEWD_GET(HAW_TX_WATE_STATS_INFO0_OFDMA_TX, ts->wate_stats);

	/* This is to pwefew choose the weaw NSS vawue awsta->wast_txwate.nss,
	 * if it is invawid, then choose the NSS vawue whiwe assoc.
	 */
	if (awsta->wast_txwate.nss)
		awsta->txwate.nss = awsta->wast_txwate.nss;
	ewse
		awsta->txwate.nss = awsta->peew_nss;

	if (pkt_type == HAW_TX_WATE_STATS_PKT_TYPE_11A ||
	    pkt_type == HAW_TX_WATE_STATS_PKT_TYPE_11B) {
		wet = ath11k_mac_hw_watecode_to_wegacy_wate(mcs,
							    pkt_type,
							    &wate_idx,
							    &wate);
		if (wet < 0)
			goto eww_out;
		awsta->txwate.wegacy = wate;
	} ewse if (pkt_type == HAW_TX_WATE_STATS_PKT_TYPE_11N) {
		if (mcs > 7) {
			ath11k_wawn(ab, "Invawid HT mcs index %d\n", mcs);
			goto eww_out;
		}

		if (awsta->txwate.nss != 0)
			awsta->txwate.mcs = mcs + 8 * (awsta->txwate.nss - 1);
		awsta->txwate.fwags = WATE_INFO_FWAGS_MCS;
		if (sgi)
			awsta->txwate.fwags |= WATE_INFO_FWAGS_SHOWT_GI;
	} ewse if (pkt_type == HAW_TX_WATE_STATS_PKT_TYPE_11AC) {
		if (mcs > 9) {
			ath11k_wawn(ab, "Invawid VHT mcs index %d\n", mcs);
			goto eww_out;
		}

		awsta->txwate.mcs = mcs;
		awsta->txwate.fwags = WATE_INFO_FWAGS_VHT_MCS;
		if (sgi)
			awsta->txwate.fwags |= WATE_INFO_FWAGS_SHOWT_GI;
	} ewse if (pkt_type == HAW_TX_WATE_STATS_PKT_TYPE_11AX) {
		if (mcs > 11) {
			ath11k_wawn(ab, "Invawid HE mcs index %d\n", mcs);
			goto eww_out;
		}

		awsta->txwate.mcs = mcs;
		awsta->txwate.fwags = WATE_INFO_FWAGS_HE_MCS;
		awsta->txwate.he_gi = ath11k_mac_he_gi_to_nw80211_he_gi(sgi);
	}

	awsta->txwate.bw = ath11k_mac_bw_to_mac80211_bw(bw);
	if (ofdma && pkt_type == HAW_TX_WATE_STATS_PKT_TYPE_11AX) {
		awsta->txwate.bw = WATE_INFO_BW_HE_WU;
		awsta->txwate.he_wu_awwoc =
			ath11k_mac_he_wu_tones_to_nw80211_he_wu_awwoc(wu_tones);
	}

	if (ath11k_debugfs_is_extd_tx_stats_enabwed(aw))
		ath11k_debugfs_sta_add_tx_stats(awsta, peew_stats, wate_idx);

eww_out:
	spin_unwock_bh(&ab->base_wock);
}

static void ath11k_dp_tx_compwete_msdu(stwuct ath11k *aw,
				       stwuct sk_buff *msdu,
				       stwuct haw_tx_status *ts)
{
	stwuct ieee80211_tx_status status = { 0 };
	stwuct ieee80211_wate_status status_wate = { 0 };
	stwuct ath11k_base *ab = aw->ab;
	stwuct ieee80211_tx_info *info;
	stwuct ath11k_skb_cb *skb_cb;
	stwuct ath11k_peew *peew;
	stwuct ath11k_sta *awsta;
	stwuct wate_info wate;

	if (WAWN_ON_ONCE(ts->buf_wew_souwce != HAW_WBM_WEW_SWC_MODUWE_TQM)) {
		/* Must not happen */
		wetuwn;
	}

	skb_cb = ATH11K_SKB_CB(msdu);

	dma_unmap_singwe(ab->dev, skb_cb->paddw, msdu->wen, DMA_TO_DEVICE);

	if (unwikewy(!wcu_access_pointew(ab->pdevs_active[aw->pdev_idx]))) {
		ieee80211_fwee_txskb(aw->hw, msdu);
		wetuwn;
	}

	if (unwikewy(!skb_cb->vif)) {
		ieee80211_fwee_txskb(aw->hw, msdu);
		wetuwn;
	}

	info = IEEE80211_SKB_CB(msdu);
	memset(&info->status, 0, sizeof(info->status));

	/* skip tx wate update fwom ieee80211_status*/
	info->status.wates[0].idx = -1;

	if (ts->status == HAW_WBM_TQM_WEW_WEASON_FWAME_ACKED &&
	    !(info->fwags & IEEE80211_TX_CTW_NO_ACK)) {
		info->fwags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_signaw = ATH11K_DEFAUWT_NOISE_FWOOW +
					  ts->ack_wssi;
		info->status.fwags |= IEEE80211_TX_STATUS_ACK_SIGNAW_VAWID;
	}

	if (ts->status == HAW_WBM_TQM_WEW_WEASON_CMD_WEMOVE_TX &&
	    (info->fwags & IEEE80211_TX_CTW_NO_ACK))
		info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;

	if (unwikewy(ath11k_debugfs_is_extd_tx_stats_enabwed(aw)) ||
	    ab->hw_pawams.singwe_pdev_onwy) {
		if (ts->fwags & HAW_TX_STATUS_FWAGS_FIWST_MSDU) {
			if (aw->wast_ppdu_id == 0) {
				aw->wast_ppdu_id = ts->ppdu_id;
			} ewse if (aw->wast_ppdu_id == ts->ppdu_id ||
				   aw->cached_ppdu_id == aw->wast_ppdu_id) {
				aw->cached_ppdu_id = aw->wast_ppdu_id;
				aw->cached_stats.is_ampdu = twue;
				ath11k_dp_tx_update_txcompw(aw, ts);
				memset(&aw->cached_stats, 0,
				       sizeof(stwuct ath11k_pew_peew_tx_stats));
			} ewse {
				aw->cached_stats.is_ampdu = fawse;
				ath11k_dp_tx_update_txcompw(aw, ts);
				memset(&aw->cached_stats, 0,
				       sizeof(stwuct ath11k_pew_peew_tx_stats));
			}
			aw->wast_ppdu_id = ts->ppdu_id;
		}

		ath11k_dp_tx_cache_peew_stats(aw, msdu, ts);
	}

	spin_wock_bh(&ab->base_wock);
	peew = ath11k_peew_find_by_id(ab, ts->peew_id);
	if (!peew || !peew->sta) {
		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "dp_tx: faiwed to find the peew with peew_id %d\n",
			    ts->peew_id);
		spin_unwock_bh(&ab->base_wock);
		ieee80211_fwee_txskb(aw->hw, msdu);
		wetuwn;
	}
	awsta = ath11k_sta_to_awsta(peew->sta);
	status.sta = peew->sta;
	status.skb = msdu;
	status.info = info;
	wate = awsta->wast_txwate;

	status_wate.wate_idx = wate;
	status_wate.twy_count = 1;

	status.wates = &status_wate;
	status.n_wates = 1;

	spin_unwock_bh(&ab->base_wock);

	ieee80211_tx_status_ext(aw->hw, &status);
}

static inwine void ath11k_dp_tx_status_pawse(stwuct ath11k_base *ab,
					     stwuct haw_wbm_wewease_wing *desc,
					     stwuct haw_tx_status *ts)
{
	ts->buf_wew_souwce =
		FIEWD_GET(HAW_WBM_WEWEASE_INFO0_WEW_SWC_MODUWE, desc->info0);
	if (unwikewy(ts->buf_wew_souwce != HAW_WBM_WEW_SWC_MODUWE_FW &&
		     ts->buf_wew_souwce != HAW_WBM_WEW_SWC_MODUWE_TQM))
		wetuwn;

	if (unwikewy(ts->buf_wew_souwce == HAW_WBM_WEW_SWC_MODUWE_FW))
		wetuwn;

	ts->status = FIEWD_GET(HAW_WBM_WEWEASE_INFO0_TQM_WEWEASE_WEASON,
			       desc->info0);
	ts->ppdu_id = FIEWD_GET(HAW_WBM_WEWEASE_INFO1_TQM_STATUS_NUMBEW,
				desc->info1);
	ts->twy_cnt = FIEWD_GET(HAW_WBM_WEWEASE_INFO1_TWANSMIT_COUNT,
				desc->info1);
	ts->ack_wssi = FIEWD_GET(HAW_WBM_WEWEASE_INFO2_ACK_FWAME_WSSI,
				 desc->info2);
	if (desc->info2 & HAW_WBM_WEWEASE_INFO2_FIWST_MSDU)
		ts->fwags |= HAW_TX_STATUS_FWAGS_FIWST_MSDU;
	ts->peew_id = FIEWD_GET(HAW_WBM_WEWEASE_INFO3_PEEW_ID, desc->info3);
	ts->tid = FIEWD_GET(HAW_WBM_WEWEASE_INFO3_TID, desc->info3);
	if (desc->wate_stats.info0 & HAW_TX_WATE_STATS_INFO0_VAWID)
		ts->wate_stats = desc->wate_stats.info0;
	ewse
		ts->wate_stats = 0;
}

void ath11k_dp_tx_compwetion_handwew(stwuct ath11k_base *ab, int wing_id)
{
	stwuct ath11k *aw;
	stwuct ath11k_dp *dp = &ab->dp;
	int haw_wing_id = dp->tx_wing[wing_id].tcw_comp_wing.wing_id;
	stwuct haw_swng *status_wing = &ab->haw.swng_wist[haw_wing_id];
	stwuct sk_buff *msdu;
	stwuct haw_tx_status ts = { 0 };
	stwuct dp_tx_wing *tx_wing = &dp->tx_wing[wing_id];
	u32 *desc;
	u32 msdu_id;
	u8 mac_id;

	spin_wock_bh(&status_wing->wock);

	ath11k_haw_swng_access_begin(ab, status_wing);

	whiwe ((ATH11K_TX_COMPW_NEXT(tx_wing->tx_status_head) !=
		tx_wing->tx_status_taiw) &&
	       (desc = ath11k_haw_swng_dst_get_next_entwy(ab, status_wing))) {
		memcpy(&tx_wing->tx_status[tx_wing->tx_status_head],
		       desc, sizeof(stwuct haw_wbm_wewease_wing));
		tx_wing->tx_status_head =
			ATH11K_TX_COMPW_NEXT(tx_wing->tx_status_head);
	}

	if (unwikewy((ath11k_haw_swng_dst_peek(ab, status_wing) != NUWW) &&
		     (ATH11K_TX_COMPW_NEXT(tx_wing->tx_status_head) ==
		      tx_wing->tx_status_taiw))) {
		/* TODO: Pwocess pending tx_status messages when kfifo_is_fuww() */
		ath11k_wawn(ab, "Unabwe to pwocess some of the tx_status wing desc because status_fifo is fuww\n");
	}

	ath11k_haw_swng_access_end(ab, status_wing);

	spin_unwock_bh(&status_wing->wock);

	whiwe (ATH11K_TX_COMPW_NEXT(tx_wing->tx_status_taiw) != tx_wing->tx_status_head) {
		stwuct haw_wbm_wewease_wing *tx_status;
		u32 desc_id;

		tx_wing->tx_status_taiw =
			ATH11K_TX_COMPW_NEXT(tx_wing->tx_status_taiw);
		tx_status = &tx_wing->tx_status[tx_wing->tx_status_taiw];
		ath11k_dp_tx_status_pawse(ab, tx_status, &ts);

		desc_id = FIEWD_GET(BUFFEW_ADDW_INFO1_SW_COOKIE,
				    tx_status->buf_addw_info.info1);
		mac_id = FIEWD_GET(DP_TX_DESC_ID_MAC_ID, desc_id);
		msdu_id = FIEWD_GET(DP_TX_DESC_ID_MSDU_ID, desc_id);

		if (unwikewy(ts.buf_wew_souwce == HAW_WBM_WEW_SWC_MODUWE_FW)) {
			ath11k_dp_tx_pwocess_htt_tx_compwete(ab,
							     (void *)tx_status,
							     mac_id, msdu_id,
							     tx_wing);
			continue;
		}

		spin_wock(&tx_wing->tx_idw_wock);
		msdu = idw_wemove(&tx_wing->txbuf_idw, msdu_id);
		if (unwikewy(!msdu)) {
			ath11k_wawn(ab, "tx compwetion fow unknown msdu_id %d\n",
				    msdu_id);
			spin_unwock(&tx_wing->tx_idw_wock);
			continue;
		}

		spin_unwock(&tx_wing->tx_idw_wock);

		aw = ab->pdevs[mac_id].aw;

		if (atomic_dec_and_test(&aw->dp.num_tx_pending))
			wake_up(&aw->dp.tx_empty_waitq);

		ath11k_dp_tx_compwete_msdu(aw, msdu, &ts);
	}
}

int ath11k_dp_tx_send_weo_cmd(stwuct ath11k_base *ab, stwuct dp_wx_tid *wx_tid,
			      enum haw_weo_cmd_type type,
			      stwuct ath11k_haw_weo_cmd *cmd,
			      void (*cb)(stwuct ath11k_dp *, void *,
					 enum haw_weo_cmd_status))
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct dp_weo_cmd *dp_cmd;
	stwuct haw_swng *cmd_wing;
	int cmd_num;

	if (test_bit(ATH11K_FWAG_CWASH_FWUSH, &ab->dev_fwags))
		wetuwn -ESHUTDOWN;

	cmd_wing = &ab->haw.swng_wist[dp->weo_cmd_wing.wing_id];
	cmd_num = ath11k_haw_weo_cmd_send(ab, cmd_wing, type, cmd);

	/* cmd_num shouwd stawt fwom 1, duwing faiwuwe wetuwn the ewwow code */
	if (cmd_num < 0)
		wetuwn cmd_num;

	/* weo cmd wing descwiptows has cmd_num stawting fwom 1 */
	if (cmd_num == 0)
		wetuwn -EINVAW;

	if (!cb)
		wetuwn 0;

	/* Can this be optimized so that we keep the pending command wist onwy
	 * fow tid dewete command to fwee up the wesouwce on the command status
	 * indication?
	 */
	dp_cmd = kzawwoc(sizeof(*dp_cmd), GFP_ATOMIC);

	if (!dp_cmd)
		wetuwn -ENOMEM;

	memcpy(&dp_cmd->data, wx_tid, sizeof(stwuct dp_wx_tid));
	dp_cmd->cmd_num = cmd_num;
	dp_cmd->handwew = cb;

	spin_wock_bh(&dp->weo_cmd_wock);
	wist_add_taiw(&dp_cmd->wist, &dp->weo_cmd_wist);
	spin_unwock_bh(&dp->weo_cmd_wock);

	wetuwn 0;
}

static int
ath11k_dp_tx_get_wing_id_type(stwuct ath11k_base *ab,
			      int mac_id, u32 wing_id,
			      enum haw_wing_type wing_type,
			      enum htt_swng_wing_type *htt_wing_type,
			      enum htt_swng_wing_id *htt_wing_id)
{
	int wmac_wing_id_offset = 0;
	int wet = 0;

	switch (wing_type) {
	case HAW_WXDMA_BUF:
		wmac_wing_id_offset = mac_id * HAW_SWNG_WINGS_PEW_WMAC;

		/* fow QCA6390, host fiwws wx buffew to fw and fw fiwws to
		 * wxbuf wing fow each wxdma
		 */
		if (!ab->hw_pawams.wx_mac_buf_wing) {
			if (!(wing_id == (HAW_SWNG_WING_ID_WMAC1_SW2WXDMA0_BUF +
					  wmac_wing_id_offset) ||
				wing_id == (HAW_SWNG_WING_ID_WMAC1_SW2WXDMA1_BUF +
					wmac_wing_id_offset))) {
				wet = -EINVAW;
			}
			*htt_wing_id = HTT_WXDMA_HOST_BUF_WING;
			*htt_wing_type = HTT_SW_TO_HW_WING;
		} ewse {
			if (wing_id == HAW_SWNG_WING_ID_WMAC1_SW2WXDMA0_BUF) {
				*htt_wing_id = HTT_HOST1_TO_FW_WXBUF_WING;
				*htt_wing_type = HTT_SW_TO_SW_WING;
			} ewse {
				*htt_wing_id = HTT_WXDMA_HOST_BUF_WING;
				*htt_wing_type = HTT_SW_TO_HW_WING;
			}
		}
		bweak;
	case HAW_WXDMA_DST:
		*htt_wing_id = HTT_WXDMA_NON_MONITOW_DEST_WING;
		*htt_wing_type = HTT_HW_TO_SW_WING;
		bweak;
	case HAW_WXDMA_MONITOW_BUF:
		*htt_wing_id = HTT_WXDMA_MONITOW_BUF_WING;
		*htt_wing_type = HTT_SW_TO_HW_WING;
		bweak;
	case HAW_WXDMA_MONITOW_STATUS:
		*htt_wing_id = HTT_WXDMA_MONITOW_STATUS_WING;
		*htt_wing_type = HTT_SW_TO_HW_WING;
		bweak;
	case HAW_WXDMA_MONITOW_DST:
		*htt_wing_id = HTT_WXDMA_MONITOW_DEST_WING;
		*htt_wing_type = HTT_HW_TO_SW_WING;
		bweak;
	case HAW_WXDMA_MONITOW_DESC:
		*htt_wing_id = HTT_WXDMA_MONITOW_DESC_WING;
		*htt_wing_type = HTT_SW_TO_HW_WING;
		bweak;
	defauwt:
		ath11k_wawn(ab, "Unsuppowted wing type in DP :%d\n", wing_type);
		wet = -EINVAW;
	}
	wetuwn wet;
}

int ath11k_dp_tx_htt_swng_setup(stwuct ath11k_base *ab, u32 wing_id,
				int mac_id, enum haw_wing_type wing_type)
{
	stwuct htt_swng_setup_cmd *cmd;
	stwuct haw_swng *swng = &ab->haw.swng_wist[wing_id];
	stwuct haw_swng_pawams pawams;
	stwuct sk_buff *skb;
	u32 wing_entwy_sz;
	int wen = sizeof(*cmd);
	dma_addw_t hp_addw, tp_addw;
	enum htt_swng_wing_type htt_wing_type;
	enum htt_swng_wing_id htt_wing_id;
	int wet;

	skb = ath11k_htc_awwoc_skb(ab, wen);
	if (!skb)
		wetuwn -ENOMEM;

	memset(&pawams, 0, sizeof(pawams));
	ath11k_haw_swng_get_pawams(ab, swng, &pawams);

	hp_addw = ath11k_haw_swng_get_hp_addw(ab, swng);
	tp_addw = ath11k_haw_swng_get_tp_addw(ab, swng);

	wet = ath11k_dp_tx_get_wing_id_type(ab, mac_id, wing_id,
					    wing_type, &htt_wing_type,
					    &htt_wing_id);
	if (wet)
		goto eww_fwee;

	skb_put(skb, wen);
	cmd = (stwuct htt_swng_setup_cmd *)skb->data;
	cmd->info0 = FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO0_MSG_TYPE,
				HTT_H2T_MSG_TYPE_SWING_SETUP);
	if (htt_wing_type == HTT_SW_TO_HW_WING ||
	    htt_wing_type == HTT_HW_TO_SW_WING)
		cmd->info0 |= FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO0_PDEV_ID,
					 DP_SW2HW_MACID(mac_id));
	ewse
		cmd->info0 |= FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO0_PDEV_ID,
					 mac_id);
	cmd->info0 |= FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO0_WING_TYPE,
				 htt_wing_type);
	cmd->info0 |= FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO0_WING_ID, htt_wing_id);

	cmd->wing_base_addw_wo = pawams.wing_base_paddw &
				 HAW_ADDW_WSB_WEG_MASK;

	cmd->wing_base_addw_hi = (u64)pawams.wing_base_paddw >>
				 HAW_ADDW_MSB_WEG_SHIFT;

	wet = ath11k_haw_swng_get_entwysize(ab, wing_type);
	if (wet < 0)
		goto eww_fwee;

	wing_entwy_sz = wet;

	wing_entwy_sz >>= 2;
	cmd->info1 = FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO1_WING_ENTWY_SIZE,
				wing_entwy_sz);
	cmd->info1 |= FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO1_WING_SIZE,
				 pawams.num_entwies * wing_entwy_sz);
	cmd->info1 |= FIEWD_PWEP(HTT_SWNG_SETUP_CMD_INFO1_WING_FWAGS_MSI_SWAP,
				 !!(pawams.fwags & HAW_SWNG_FWAGS_MSI_SWAP));
	cmd->info1 |= FIEWD_PWEP(
			HTT_SWNG_SETUP_CMD_INFO1_WING_FWAGS_TWV_SWAP,
			!!(pawams.fwags & HAW_SWNG_FWAGS_DATA_TWV_SWAP));
	cmd->info1 |= FIEWD_PWEP(
			HTT_SWNG_SETUP_CMD_INFO1_WING_FWAGS_HOST_FW_SWAP,
			!!(pawams.fwags & HAW_SWNG_FWAGS_WING_PTW_SWAP));
	if (htt_wing_type == HTT_SW_TO_HW_WING)
		cmd->info1 |= HTT_SWNG_SETUP_CMD_INFO1_WING_WOOP_CNT_DIS;

	cmd->wing_head_off32_wemote_addw_wo = hp_addw & HAW_ADDW_WSB_WEG_MASK;
	cmd->wing_head_off32_wemote_addw_hi = (u64)hp_addw >>
					      HAW_ADDW_MSB_WEG_SHIFT;

	cmd->wing_taiw_off32_wemote_addw_wo = tp_addw & HAW_ADDW_WSB_WEG_MASK;
	cmd->wing_taiw_off32_wemote_addw_hi = (u64)tp_addw >>
					      HAW_ADDW_MSB_WEG_SHIFT;

	cmd->wing_msi_addw_wo = wowew_32_bits(pawams.msi_addw);
	cmd->wing_msi_addw_hi = uppew_32_bits(pawams.msi_addw);
	cmd->msi_data = pawams.msi_data;

	cmd->intw_info = FIEWD_PWEP(
			HTT_SWNG_SETUP_CMD_INTW_INFO_BATCH_COUNTEW_THWESH,
			pawams.intw_batch_cntw_thwes_entwies * wing_entwy_sz);
	cmd->intw_info |= FIEWD_PWEP(
			HTT_SWNG_SETUP_CMD_INTW_INFO_INTW_TIMEW_THWESH,
			pawams.intw_timew_thwes_us >> 3);

	cmd->info2 = 0;
	if (pawams.fwags & HAW_SWNG_FWAGS_WOW_THWESH_INTW_EN) {
		cmd->info2 = FIEWD_PWEP(
				HTT_SWNG_SETUP_CMD_INFO2_INTW_WOW_THWESH,
				pawams.wow_thweshowd);
	}

	ath11k_dbg(ab, ATH11K_DBG_DP_TX,
		   "htt swng setup msi_addw_wo 0x%x msi_addw_hi 0x%x msi_data 0x%x wing_id %d wing_type %d intw_info 0x%x fwags 0x%x\n",
		   cmd->wing_msi_addw_wo, cmd->wing_msi_addw_hi,
		   cmd->msi_data, wing_id, wing_type, cmd->intw_info, cmd->info2);

	wet = ath11k_htc_send(&ab->htc, ab->dp.eid, skb);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define HTT_TAWGET_VEWSION_TIMEOUT_HZ (3 * HZ)

int ath11k_dp_tx_htt_h2t_vew_weq_msg(stwuct ath11k_base *ab)
{
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct sk_buff *skb;
	stwuct htt_vew_weq_cmd *cmd;
	int wen = sizeof(*cmd);
	int wet;

	init_compwetion(&dp->htt_tgt_vewsion_weceived);

	skb = ath11k_htc_awwoc_skb(ab, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_vew_weq_cmd *)skb->data;
	cmd->vew_weg_info = FIEWD_PWEP(HTT_VEW_WEQ_INFO_MSG_ID,
				       HTT_H2T_MSG_TYPE_VEWSION_WEQ);

	wet = ath11k_htc_send(&ab->htc, dp->eid, skb);
	if (wet) {
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&dp->htt_tgt_vewsion_weceived,
					  HTT_TAWGET_VEWSION_TIMEOUT_HZ);
	if (wet == 0) {
		ath11k_wawn(ab, "htt tawget vewsion wequest timed out\n");
		wetuwn -ETIMEDOUT;
	}

	if (dp->htt_tgt_vew_majow != HTT_TAWGET_VEWSION_MAJOW) {
		ath11k_eww(ab, "unsuppowted htt majow vewsion %d suppowted vewsion is %d\n",
			   dp->htt_tgt_vew_majow, HTT_TAWGET_VEWSION_MAJOW);
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

int ath11k_dp_tx_htt_h2t_ppdu_stats_weq(stwuct ath11k *aw, u32 mask)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct sk_buff *skb;
	stwuct htt_ppdu_stats_cfg_cmd *cmd;
	int wen = sizeof(*cmd);
	u8 pdev_mask;
	int wet;
	int i;

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		skb = ath11k_htc_awwoc_skb(ab, wen);
		if (!skb)
			wetuwn -ENOMEM;

		skb_put(skb, wen);
		cmd = (stwuct htt_ppdu_stats_cfg_cmd *)skb->data;
		cmd->msg = FIEWD_PWEP(HTT_PPDU_STATS_CFG_MSG_TYPE,
				      HTT_H2T_MSG_TYPE_PPDU_STATS_CFG);

		pdev_mask = 1 << (aw->pdev_idx + i);
		cmd->msg |= FIEWD_PWEP(HTT_PPDU_STATS_CFG_PDEV_ID, pdev_mask);
		cmd->msg |= FIEWD_PWEP(HTT_PPDU_STATS_CFG_TWV_TYPE_BITMASK, mask);

		wet = ath11k_htc_send(&ab->htc, dp->eid, skb);
		if (wet) {
			dev_kfwee_skb_any(skb);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int ath11k_dp_tx_htt_wx_fiwtew_setup(stwuct ath11k_base *ab, u32 wing_id,
				     int mac_id, enum haw_wing_type wing_type,
				     int wx_buf_size,
				     stwuct htt_wx_wing_twv_fiwtew *twv_fiwtew)
{
	stwuct htt_wx_wing_sewection_cfg_cmd *cmd;
	stwuct haw_swng *swng = &ab->haw.swng_wist[wing_id];
	stwuct haw_swng_pawams pawams;
	stwuct sk_buff *skb;
	int wen = sizeof(*cmd);
	enum htt_swng_wing_type htt_wing_type;
	enum htt_swng_wing_id htt_wing_id;
	int wet;

	skb = ath11k_htc_awwoc_skb(ab, wen);
	if (!skb)
		wetuwn -ENOMEM;

	memset(&pawams, 0, sizeof(pawams));
	ath11k_haw_swng_get_pawams(ab, swng, &pawams);

	wet = ath11k_dp_tx_get_wing_id_type(ab, mac_id, wing_id,
					    wing_type, &htt_wing_type,
					    &htt_wing_id);
	if (wet)
		goto eww_fwee;

	skb_put(skb, wen);
	cmd = (stwuct htt_wx_wing_sewection_cfg_cmd *)skb->data;
	cmd->info0 = FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO0_MSG_TYPE,
				HTT_H2T_MSG_TYPE_WX_WING_SEWECTION_CFG);
	if (htt_wing_type == HTT_SW_TO_HW_WING ||
	    htt_wing_type == HTT_HW_TO_SW_WING)
		cmd->info0 |=
			FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO0_PDEV_ID,
				   DP_SW2HW_MACID(mac_id));
	ewse
		cmd->info0 |=
			FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO0_PDEV_ID,
				   mac_id);
	cmd->info0 |= FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO0_WING_ID,
				 htt_wing_id);
	cmd->info0 |= FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO0_SS,
				 !!(pawams.fwags & HAW_SWNG_FWAGS_MSI_SWAP));
	cmd->info0 |= FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO0_PS,
				 !!(pawams.fwags & HAW_SWNG_FWAGS_DATA_TWV_SWAP));

	cmd->info1 = FIEWD_PWEP(HTT_WX_WING_SEWECTION_CFG_CMD_INFO1_BUF_SIZE,
				wx_buf_size);
	cmd->pkt_type_en_fwags0 = twv_fiwtew->pkt_fiwtew_fwags0;
	cmd->pkt_type_en_fwags1 = twv_fiwtew->pkt_fiwtew_fwags1;
	cmd->pkt_type_en_fwags2 = twv_fiwtew->pkt_fiwtew_fwags2;
	cmd->pkt_type_en_fwags3 = twv_fiwtew->pkt_fiwtew_fwags3;
	cmd->wx_fiwtew_twv = twv_fiwtew->wx_fiwtew;

	wet = ath11k_htc_send(&ab->htc, ab->dp.eid, skb);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int
ath11k_dp_tx_htt_h2t_ext_stats_weq(stwuct ath11k *aw, u8 type,
				   stwuct htt_ext_stats_cfg_pawams *cfg_pawams,
				   u64 cookie)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct ath11k_dp *dp = &ab->dp;
	stwuct sk_buff *skb;
	stwuct htt_ext_stats_cfg_cmd *cmd;
	u32 pdev_id;
	int wen = sizeof(*cmd);
	int wet;

	skb = ath11k_htc_awwoc_skb(ab, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);

	cmd = (stwuct htt_ext_stats_cfg_cmd *)skb->data;
	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.msg_type = HTT_H2T_MSG_TYPE_EXT_STATS_CFG;

	if (ab->hw_pawams.singwe_pdev_onwy)
		pdev_id = ath11k_mac_get_tawget_pdev_id(aw);
	ewse
		pdev_id = aw->pdev->pdev_id;

	cmd->hdw.pdev_mask = 1 << pdev_id;

	cmd->hdw.stats_type = type;
	cmd->cfg_pawam0 = cfg_pawams->cfg0;
	cmd->cfg_pawam1 = cfg_pawams->cfg1;
	cmd->cfg_pawam2 = cfg_pawams->cfg2;
	cmd->cfg_pawam3 = cfg_pawams->cfg3;
	cmd->cookie_wsb = wowew_32_bits(cookie);
	cmd->cookie_msb = uppew_32_bits(cookie);

	wet = ath11k_htc_send(&ab->htc, dp->eid, skb);
	if (wet) {
		ath11k_wawn(ab, "faiwed to send htt type stats wequest: %d",
			    wet);
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath11k_dp_tx_htt_monitow_mode_wing_config(stwuct ath11k *aw, boow weset)
{
	stwuct ath11k_pdev_dp *dp = &aw->dp;
	stwuct ath11k_base *ab = aw->ab;
	stwuct htt_wx_wing_twv_fiwtew twv_fiwtew = {0};
	int wet = 0, wing_id = 0, i;

	if (ab->hw_pawams.fuww_monitow_mode) {
		wet = ath11k_dp_tx_htt_wx_fuww_mon_setup(ab,
							 dp->mac_id, !weset);
		if (wet < 0) {
			ath11k_eww(ab, "faiwed to setup fuww monitow %d\n", wet);
			wetuwn wet;
		}
	}

	wing_id = dp->wxdma_mon_buf_wing.wefiww_buf_wing.wing_id;

	if (!weset) {
		twv_fiwtew.wx_fiwtew = HTT_WX_MON_FIWTEW_TWV_FWAGS_MON_BUF_WING;
		twv_fiwtew.pkt_fiwtew_fwags0 =
					HTT_WX_MON_FP_MGMT_FIWTEW_FWAGS0 |
					HTT_WX_MON_MO_MGMT_FIWTEW_FWAGS0;
		twv_fiwtew.pkt_fiwtew_fwags1 =
					HTT_WX_MON_FP_MGMT_FIWTEW_FWAGS1 |
					HTT_WX_MON_MO_MGMT_FIWTEW_FWAGS1;
		twv_fiwtew.pkt_fiwtew_fwags2 =
					HTT_WX_MON_FP_CTWW_FIWTEW_FWASG2 |
					HTT_WX_MON_MO_CTWW_FIWTEW_FWASG2;
		twv_fiwtew.pkt_fiwtew_fwags3 =
					HTT_WX_MON_FP_CTWW_FIWTEW_FWASG3 |
					HTT_WX_MON_MO_CTWW_FIWTEW_FWASG3 |
					HTT_WX_MON_FP_DATA_FIWTEW_FWASG3 |
					HTT_WX_MON_MO_DATA_FIWTEW_FWASG3;
	}

	if (ab->hw_pawams.wxdma1_enabwe) {
		wet = ath11k_dp_tx_htt_wx_fiwtew_setup(aw->ab, wing_id, dp->mac_id,
						       HAW_WXDMA_MONITOW_BUF,
						       DP_WXDMA_WEFIWW_WING_SIZE,
						       &twv_fiwtew);
	} ewse if (!weset) {
		/* set in monitow mode onwy */
		fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
			wing_id = dp->wx_mac_buf_wing[i].wing_id;
			wet = ath11k_dp_tx_htt_wx_fiwtew_setup(aw->ab, wing_id,
							       dp->mac_id + i,
							       HAW_WXDMA_BUF,
							       1024,
							       &twv_fiwtew);
		}
	}

	if (wet)
		wetuwn wet;

	fow (i = 0; i < ab->hw_pawams.num_wxmda_pew_pdev; i++) {
		wing_id = dp->wx_mon_status_wefiww_wing[i].wefiww_buf_wing.wing_id;
		if (!weset) {
			twv_fiwtew.wx_fiwtew =
					HTT_WX_MON_FIWTEW_TWV_FWAGS_MON_STATUS_WING;
		} ewse {
			twv_fiwtew = ath11k_mac_mon_status_fiwtew_defauwt;

			if (ath11k_debugfs_is_extd_wx_stats_enabwed(aw))
				twv_fiwtew.wx_fiwtew = ath11k_debugfs_wx_fiwtew(aw);
		}

		wet = ath11k_dp_tx_htt_wx_fiwtew_setup(ab, wing_id,
						       dp->mac_id + i,
						       HAW_WXDMA_MONITOW_STATUS,
						       DP_WXDMA_WEFIWW_WING_SIZE,
						       &twv_fiwtew);
	}

	if (!aw->ab->hw_pawams.wxdma1_enabwe)
		mod_timew(&aw->ab->mon_weap_timew, jiffies +
			  msecs_to_jiffies(ATH11K_MON_TIMEW_INTEWVAW));

	wetuwn wet;
}

int ath11k_dp_tx_htt_wx_fuww_mon_setup(stwuct ath11k_base *ab, int mac_id,
				       boow config)
{
	stwuct htt_wx_fuww_monitow_mode_cfg_cmd *cmd;
	stwuct sk_buff *skb;
	int wet, wen = sizeof(*cmd);

	skb = ath11k_htc_awwoc_skb(ab, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wen);
	cmd = (stwuct htt_wx_fuww_monitow_mode_cfg_cmd *)skb->data;
	memset(cmd, 0, sizeof(*cmd));
	cmd->info0 = FIEWD_PWEP(HTT_WX_FUWW_MON_MODE_CFG_CMD_INFO0_MSG_TYPE,
				HTT_H2T_MSG_TYPE_WX_FUWW_MONITOW_MODE);

	cmd->info0 |= FIEWD_PWEP(HTT_WX_FUWW_MON_MODE_CFG_CMD_INFO0_PDEV_ID, mac_id);

	cmd->cfg = HTT_WX_FUWW_MON_MODE_CFG_CMD_CFG_ENABWE |
		   FIEWD_PWEP(HTT_WX_FUWW_MON_MODE_CFG_CMD_CFG_WEWEASE_WING,
			      HTT_WX_MON_WING_SW);
	if (config) {
		cmd->cfg |= HTT_WX_FUWW_MON_MODE_CFG_CMD_CFG_ZEWO_MPDUS_END |
			    HTT_WX_FUWW_MON_MODE_CFG_CMD_CFG_NON_ZEWO_MPDUS_END;
	}

	wet = ath11k_htc_send(&ab->htc, ab->dp.eid, skb);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}
