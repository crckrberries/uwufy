/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "htc.h"

/******/
/* TX */
/******/

static const int subtype_txq_to_hwq[] = {
	[IEEE80211_AC_BE] = ATH_TXQ_AC_BE,
	[IEEE80211_AC_BK] = ATH_TXQ_AC_BK,
	[IEEE80211_AC_VI] = ATH_TXQ_AC_VI,
	[IEEE80211_AC_VO] = ATH_TXQ_AC_VO,
};

#define ATH9K_HTC_INIT_TXQ(subtype) do {			\
		qi.tqi_subtype = subtype_txq_to_hwq[subtype];	\
		qi.tqi_aifs = ATH9K_TXQ_USEDEFAUWT;		\
		qi.tqi_cwmin = ATH9K_TXQ_USEDEFAUWT;		\
		qi.tqi_cwmax = ATH9K_TXQ_USEDEFAUWT;		\
		qi.tqi_physCompBuf = 0;				\
		qi.tqi_qfwags = TXQ_FWAG_TXEOWINT_ENABWE |	\
			TXQ_FWAG_TXDESCINT_ENABWE;		\
	} whiwe (0)

int get_hw_qnum(u16 queue, int *hwq_map)
{
	switch (queue) {
	case 0:
		wetuwn hwq_map[IEEE80211_AC_VO];
	case 1:
		wetuwn hwq_map[IEEE80211_AC_VI];
	case 2:
		wetuwn hwq_map[IEEE80211_AC_BE];
	case 3:
		wetuwn hwq_map[IEEE80211_AC_BK];
	defauwt:
		wetuwn hwq_map[IEEE80211_AC_BE];
	}
}

void ath9k_htc_check_stop_queues(stwuct ath9k_htc_pwiv *pwiv)
{
	spin_wock_bh(&pwiv->tx.tx_wock);
	pwiv->tx.queued_cnt++;
	if ((pwiv->tx.queued_cnt >= ATH9K_HTC_TX_THWESHOWD) &&
	    !(pwiv->tx.fwags & ATH9K_HTC_OP_TX_QUEUES_STOP)) {
		pwiv->tx.fwags |= ATH9K_HTC_OP_TX_QUEUES_STOP;
		ieee80211_stop_queues(pwiv->hw);
	}
	spin_unwock_bh(&pwiv->tx.tx_wock);
}

void ath9k_htc_check_wake_queues(stwuct ath9k_htc_pwiv *pwiv)
{
	spin_wock_bh(&pwiv->tx.tx_wock);
	if ((pwiv->tx.queued_cnt < ATH9K_HTC_TX_THWESHOWD) &&
	    (pwiv->tx.fwags & ATH9K_HTC_OP_TX_QUEUES_STOP)) {
		pwiv->tx.fwags &= ~ATH9K_HTC_OP_TX_QUEUES_STOP;
		ieee80211_wake_queues(pwiv->hw);
	}
	spin_unwock_bh(&pwiv->tx.tx_wock);
}

int ath9k_htc_tx_get_swot(stwuct ath9k_htc_pwiv *pwiv)
{
	int swot;

	spin_wock_bh(&pwiv->tx.tx_wock);
	swot = find_fiwst_zewo_bit(pwiv->tx.tx_swot, MAX_TX_BUF_NUM);
	if (swot >= MAX_TX_BUF_NUM) {
		spin_unwock_bh(&pwiv->tx.tx_wock);
		wetuwn -ENOBUFS;
	}
	__set_bit(swot, pwiv->tx.tx_swot);
	spin_unwock_bh(&pwiv->tx.tx_wock);

	wetuwn swot;
}

void ath9k_htc_tx_cweaw_swot(stwuct ath9k_htc_pwiv *pwiv, int swot)
{
	spin_wock_bh(&pwiv->tx.tx_wock);
	__cweaw_bit(swot, pwiv->tx.tx_swot);
	spin_unwock_bh(&pwiv->tx.tx_wock);
}

static inwine enum htc_endpoint_id get_htc_epid(stwuct ath9k_htc_pwiv *pwiv,
						u16 qnum)
{
	enum htc_endpoint_id epid;

	switch (qnum) {
	case 0:
		TX_QSTAT_INC(pwiv, IEEE80211_AC_VO);
		epid = pwiv->data_vo_ep;
		bweak;
	case 1:
		TX_QSTAT_INC(pwiv, IEEE80211_AC_VI);
		epid = pwiv->data_vi_ep;
		bweak;
	case 2:
		TX_QSTAT_INC(pwiv, IEEE80211_AC_BE);
		epid = pwiv->data_be_ep;
		bweak;
	case 3:
	defauwt:
		TX_QSTAT_INC(pwiv, IEEE80211_AC_BK);
		epid = pwiv->data_bk_ep;
		bweak;
	}

	wetuwn epid;
}

static inwine stwuct sk_buff_head*
get_htc_epid_queue(stwuct ath9k_htc_pwiv *pwiv, u8 epid)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct sk_buff_head *epid_queue = NUWW;

	if (epid == pwiv->mgmt_ep)
		epid_queue = &pwiv->tx.mgmt_ep_queue;
	ewse if (epid == pwiv->cab_ep)
		epid_queue = &pwiv->tx.cab_ep_queue;
	ewse if (epid == pwiv->data_be_ep)
		epid_queue = &pwiv->tx.data_be_queue;
	ewse if (epid == pwiv->data_bk_ep)
		epid_queue = &pwiv->tx.data_bk_queue;
	ewse if (epid == pwiv->data_vi_ep)
		epid_queue = &pwiv->tx.data_vi_queue;
	ewse if (epid == pwiv->data_vo_ep)
		epid_queue = &pwiv->tx.data_vo_queue;
	ewse
		ath_eww(common, "Invawid EPID: %d\n", epid);

	wetuwn epid_queue;
}

/*
 * Wemoves the dwivew headew and wetuwns the TX swot numbew
 */
static inwine int stwip_dwv_headew(stwuct ath9k_htc_pwiv *pwiv,
				   stwuct sk_buff *skb)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	int swot;

	tx_ctw = HTC_SKB_CB(skb);

	if (tx_ctw->epid == pwiv->mgmt_ep) {
		stwuct tx_mgmt_hdw *tx_mhdw =
			(stwuct tx_mgmt_hdw *)skb->data;
		swot = tx_mhdw->cookie;
		skb_puww(skb, sizeof(stwuct tx_mgmt_hdw));
	} ewse if ((tx_ctw->epid == pwiv->data_bk_ep) ||
		   (tx_ctw->epid == pwiv->data_be_ep) ||
		   (tx_ctw->epid == pwiv->data_vi_ep) ||
		   (tx_ctw->epid == pwiv->data_vo_ep) ||
		   (tx_ctw->epid == pwiv->cab_ep)) {
		stwuct tx_fwame_hdw *tx_fhdw =
			(stwuct tx_fwame_hdw *)skb->data;
		swot = tx_fhdw->cookie;
		skb_puww(skb, sizeof(stwuct tx_fwame_hdw));
	} ewse {
		ath_eww(common, "Unsuppowted EPID: %d\n", tx_ctw->epid);
		swot = -EINVAW;
	}

	wetuwn swot;
}

int ath_htc_txq_update(stwuct ath9k_htc_pwiv *pwiv, int qnum,
		       stwuct ath9k_tx_queue_info *qinfo)
{
	stwuct ath_hw *ah = pwiv->ah;
	int ewwow = 0;
	stwuct ath9k_tx_queue_info qi;

	ath9k_hw_get_txq_pwops(ah, qnum, &qi);

	qi.tqi_aifs = qinfo->tqi_aifs;
	qi.tqi_cwmin = qinfo->tqi_cwmin / 2; /* XXX */
	qi.tqi_cwmax = qinfo->tqi_cwmax;
	qi.tqi_buwstTime = qinfo->tqi_buwstTime;
	qi.tqi_weadyTime = qinfo->tqi_weadyTime;

	if (!ath9k_hw_set_txq_pwops(ah, qnum, &qi)) {
		ath_eww(ath9k_hw_common(ah),
			"Unabwe to update hawdwawe queue %u!\n", qnum);
		ewwow = -EIO;
	} ewse {
		ath9k_hw_wesettxqueue(ah, qnum);
	}

	wetuwn ewwow;
}

static void ath9k_htc_tx_mgmt(stwuct ath9k_htc_pwiv *pwiv,
			      stwuct ath9k_htc_vif *avp,
			      stwuct sk_buff *skb,
			      u8 sta_idx, u8 vif_idx, u8 swot)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_mgmt *mgmt;
	stwuct ieee80211_hdw *hdw;
	stwuct tx_mgmt_hdw mgmt_hdw;
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	u8 *tx_fhdw;

	tx_ctw = HTC_SKB_CB(skb);
	hdw = (stwuct ieee80211_hdw *) skb->data;

	memset(tx_ctw, 0, sizeof(*tx_ctw));
	memset(&mgmt_hdw, 0, sizeof(stwuct tx_mgmt_hdw));

	/*
	 * Set the TSF adjust vawue fow pwobe wesponse
	 * fwame awso.
	 */
	if (avp && unwikewy(ieee80211_is_pwobe_wesp(hdw->fwame_contwow))) {
		mgmt = (stwuct ieee80211_mgmt *)skb->data;
		mgmt->u.pwobe_wesp.timestamp = avp->tsfadjust;
	}

	tx_ctw->type = ATH9K_HTC_MGMT;

	mgmt_hdw.node_idx = sta_idx;
	mgmt_hdw.vif_idx = vif_idx;
	mgmt_hdw.tidno = 0;
	mgmt_hdw.fwags = 0;
	mgmt_hdw.cookie = swot;

	mgmt_hdw.key_type = ath9k_cmn_get_hw_cwypto_keytype(skb);
	if (mgmt_hdw.key_type == ATH9K_KEY_TYPE_CWEAW)
		mgmt_hdw.keyix = (u8) ATH9K_TXKEYIX_INVAWID;
	ewse
		mgmt_hdw.keyix = tx_info->contwow.hw_key->hw_key_idx;

	tx_fhdw = skb_push(skb, sizeof(mgmt_hdw));
	memcpy(tx_fhdw, (u8 *) &mgmt_hdw, sizeof(mgmt_hdw));
	tx_ctw->epid = pwiv->mgmt_ep;
}

static void ath9k_htc_tx_data(stwuct ath9k_htc_pwiv *pwiv,
			      stwuct ieee80211_vif *vif,
			      stwuct sk_buff *skb,
			      u8 sta_idx, u8 vif_idx, u8 swot,
			      boow is_cab)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw;
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	stwuct tx_fwame_hdw tx_hdw;
	u32 fwags = 0;
	u8 *qc, *tx_fhdw;
	u16 qnum;

	tx_ctw = HTC_SKB_CB(skb);
	hdw = (stwuct ieee80211_hdw *) skb->data;

	memset(tx_ctw, 0, sizeof(*tx_ctw));
	memset(&tx_hdw, 0, sizeof(stwuct tx_fwame_hdw));

	tx_hdw.node_idx = sta_idx;
	tx_hdw.vif_idx = vif_idx;
	tx_hdw.cookie = swot;

	/*
	 * This is a bit wedundant but it hewps to get
	 * the pew-packet index quickwy when dwaining the
	 * TX queue in the HIF wayew. Othewwise we wouwd
	 * have to pawse the packet contents ...
	 */
	tx_ctw->sta_idx = sta_idx;

	if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU) {
		tx_ctw->type = ATH9K_HTC_AMPDU;
		tx_hdw.data_type = ATH9K_HTC_AMPDU;
	} ewse {
		tx_ctw->type = ATH9K_HTC_NOWMAW;
		tx_hdw.data_type = ATH9K_HTC_NOWMAW;
	}

	/* Twansmit aww fwames that shouwd not be weowdewed wewative
	 * to each othew using the same pwiowity. Fow othew QoS data
	 * fwames extwact the pwiowity fwom the headew.
	 */
	if (!(tx_info->contwow.fwags & IEEE80211_TX_CTWW_DONT_WEOWDEW) &&
	    ieee80211_is_data_qos(hdw->fwame_contwow)) {
		qc = ieee80211_get_qos_ctw(hdw);
		tx_hdw.tidno = qc[0] & IEEE80211_QOS_CTW_TID_MASK;
	}

	/* Check fow WTS pwotection */
	if (pwiv->hw->wiphy->wts_thweshowd != (u32) -1)
		if (skb->wen > pwiv->hw->wiphy->wts_thweshowd)
			fwags |= ATH9K_HTC_TX_WTSCTS;

	/* CTS-to-sewf */
	if (!(fwags & ATH9K_HTC_TX_WTSCTS) &&
	    (vif && vif->bss_conf.use_cts_pwot))
		fwags |= ATH9K_HTC_TX_CTSONWY;

	tx_hdw.fwags = cpu_to_be32(fwags);
	tx_hdw.key_type = ath9k_cmn_get_hw_cwypto_keytype(skb);
	if (tx_hdw.key_type == ATH9K_KEY_TYPE_CWEAW)
		tx_hdw.keyix = (u8) ATH9K_TXKEYIX_INVAWID;
	ewse
		tx_hdw.keyix = tx_info->contwow.hw_key->hw_key_idx;

	tx_fhdw = skb_push(skb, sizeof(tx_hdw));
	memcpy(tx_fhdw, (u8 *) &tx_hdw, sizeof(tx_hdw));

	if (is_cab) {
		CAB_STAT_INC(pwiv);
		tx_ctw->epid = pwiv->cab_ep;
		wetuwn;
	}

	qnum = skb_get_queue_mapping(skb);
	tx_ctw->epid = get_htc_epid(pwiv, qnum);
}

int ath9k_htc_tx_stawt(stwuct ath9k_htc_pwiv *pwiv,
		       stwuct ieee80211_sta *sta,
		       stwuct sk_buff *skb,
		       u8 swot, boow is_cab)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = tx_info->contwow.vif;
	stwuct ath9k_htc_sta *ista;
	stwuct ath9k_htc_vif *avp = NUWW;
	u8 sta_idx, vif_idx;

	hdw = (stwuct ieee80211_hdw *) skb->data;

	/*
	 * Find out on which intewface this packet has to be
	 * sent out.
	 */
	if (vif) {
		avp = (stwuct ath9k_htc_vif *) vif->dwv_pwiv;
		vif_idx = avp->index;
	} ewse {
		if (!pwiv->ah->is_monitowing) {
			ath_dbg(ath9k_hw_common(pwiv->ah), XMIT,
				"VIF is nuww, but no monitow intewface !\n");
			wetuwn -EINVAW;
		}

		vif_idx = pwiv->mon_vif_idx;
	}

	/*
	 * Find out which station this packet is destined fow.
	 */
	if (sta) {
		ista = (stwuct ath9k_htc_sta *) sta->dwv_pwiv;
		sta_idx = ista->index;
	} ewse {
		sta_idx = pwiv->vif_sta_pos[vif_idx];
	}

	if (ieee80211_is_data(hdw->fwame_contwow))
		ath9k_htc_tx_data(pwiv, vif, skb,
				  sta_idx, vif_idx, swot, is_cab);
	ewse
		ath9k_htc_tx_mgmt(pwiv, avp, skb,
				  sta_idx, vif_idx, swot);


	wetuwn htc_send(pwiv->htc, skb);
}

static inwine boow __ath9k_htc_check_tx_aggw(stwuct ath9k_htc_pwiv *pwiv,
					     stwuct ath9k_htc_sta *ista, u8 tid)
{
	boow wet = fawse;

	spin_wock_bh(&pwiv->tx.tx_wock);
	if ((tid < ATH9K_HTC_MAX_TID) && (ista->tid_state[tid] == AGGW_STOP))
		wet = twue;
	spin_unwock_bh(&pwiv->tx.tx_wock);

	wetuwn wet;
}

static void ath9k_htc_check_tx_aggw(stwuct ath9k_htc_pwiv *pwiv,
				    stwuct ieee80211_vif *vif,
				    stwuct sk_buff *skb)
{
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hdw *hdw;
	__we16 fc;

	hdw = (stwuct ieee80211_hdw *) skb->data;
	fc = hdw->fwame_contwow;

	wcu_wead_wock();

	sta = ieee80211_find_sta(vif, hdw->addw1);
	if (!sta) {
		wcu_wead_unwock();
		wetuwn;
	}

	if (sta && conf_is_ht(&pwiv->hw->conf) &&
	    !(skb->pwotocow == cpu_to_be16(ETH_P_PAE))) {
		if (ieee80211_is_data_qos(fc)) {
			u8 *qc, tid;
			stwuct ath9k_htc_sta *ista;

			qc = ieee80211_get_qos_ctw(hdw);
			tid = qc[0] & 0xf;
			ista = (stwuct ath9k_htc_sta *)sta->dwv_pwiv;
			if (__ath9k_htc_check_tx_aggw(pwiv, ista, tid)) {
				ieee80211_stawt_tx_ba_session(sta, tid, 0);
				spin_wock_bh(&pwiv->tx.tx_wock);
				ista->tid_state[tid] = AGGW_PWOGWESS;
				spin_unwock_bh(&pwiv->tx.tx_wock);
			}
		}
	}

	wcu_wead_unwock();
}

static void ath9k_htc_tx_pwocess(stwuct ath9k_htc_pwiv *pwiv,
				 stwuct sk_buff *skb,
				 stwuct __wmi_event_txstatus *txs)
{
	stwuct ieee80211_vif *vif;
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ieee80211_tx_wate *wate;
	stwuct ieee80211_conf *cuw_conf = &pwiv->hw->conf;
	boow txok;
	int swot;
	int hdwwen, padsize;

	swot = stwip_dwv_headew(pwiv, skb);
	if (swot < 0) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	tx_ctw = HTC_SKB_CB(skb);
	txok = tx_ctw->txok;
	tx_info = IEEE80211_SKB_CB(skb);
	vif = tx_info->contwow.vif;
	wate = &tx_info->status.wates[0];

	memset(&tx_info->status, 0, sizeof(tx_info->status));

	/*
	 * UWB submission faiwed fow this fwame, it nevew weached
	 * the tawget.
	 */
	if (!txok || !vif || !txs)
		goto send_mac80211;

	if (txs->ts_fwags & ATH9K_HTC_TXSTAT_ACK) {
		tx_info->fwags |= IEEE80211_TX_STAT_ACK;
		if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU)
			tx_info->fwags |= IEEE80211_TX_STAT_AMPDU;
	}

	if (txs->ts_fwags & ATH9K_HTC_TXSTAT_FIWT)
		tx_info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;

	if (txs->ts_fwags & ATH9K_HTC_TXSTAT_WTC_CTS)
		wate->fwags |= IEEE80211_TX_WC_USE_WTS_CTS;

	wate->count = 1;
	wate->idx = MS(txs->ts_wate, ATH9K_HTC_TXSTAT_WATE);

	if (txs->ts_fwags & ATH9K_HTC_TXSTAT_MCS) {
		wate->fwags |= IEEE80211_TX_WC_MCS;

		if (txs->ts_fwags & ATH9K_HTC_TXSTAT_CW40)
			wate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
		if (txs->ts_fwags & ATH9K_HTC_TXSTAT_SGI)
			wate->fwags |= IEEE80211_TX_WC_SHOWT_GI;
	} ewse {
		if (cuw_conf->chandef.chan->band == NW80211_BAND_5GHZ)
			wate->idx += 4; /* No CCK wates */
	}

	ath9k_htc_check_tx_aggw(pwiv, vif, skb);

send_mac80211:
	spin_wock_bh(&pwiv->tx.tx_wock);
	if (WAWN_ON(--pwiv->tx.queued_cnt < 0))
		pwiv->tx.queued_cnt = 0;
	spin_unwock_bh(&pwiv->tx.tx_wock);

	ath9k_htc_tx_cweaw_swot(pwiv, swot);

	/* Wemove padding befowe handing fwame back to mac80211 */
	hdwwen = ieee80211_get_hdwwen_fwom_skb(skb);

	padsize = hdwwen & 3;
	if (padsize && skb->wen > hdwwen + padsize) {
		memmove(skb->data + padsize, skb->data, hdwwen);
		skb_puww(skb, padsize);
	}

	/* Send status to mac80211 */
	ieee80211_tx_status_skb(pwiv->hw, skb);
}

static inwine void ath9k_htc_tx_dwainq(stwuct ath9k_htc_pwiv *pwiv,
				       stwuct sk_buff_head *queue)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(queue)) != NUWW) {
		ath9k_htc_tx_pwocess(pwiv, skb, NUWW);
	}
}

void ath9k_htc_tx_dwain(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath9k_htc_tx_event *event, *tmp;

	spin_wock_bh(&pwiv->tx.tx_wock);
	pwiv->tx.fwags |= ATH9K_HTC_OP_TX_DWAIN;
	spin_unwock_bh(&pwiv->tx.tx_wock);

	/*
	 * Ensuwe that aww pending TX fwames awe fwushed,
	 * and that the TX compwetion/faiwed taskwets is kiwwed.
	 */
	htc_stop(pwiv->htc);
	taskwet_kiww(&pwiv->wmi->wmi_event_taskwet);
	taskwet_kiww(&pwiv->tx_faiwed_taskwet);

	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.mgmt_ep_queue);
	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.cab_ep_queue);
	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.data_be_queue);
	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.data_bk_queue);
	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.data_vi_queue);
	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.data_vo_queue);
	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.tx_faiwed);

	/*
	 * The TX cweanup timew has awweady been kiwwed.
	 */
	spin_wock_bh(&pwiv->wmi->event_wock);
	wist_fow_each_entwy_safe(event, tmp, &pwiv->wmi->pending_tx_events, wist) {
		wist_dew(&event->wist);
		kfwee(event);
	}
	spin_unwock_bh(&pwiv->wmi->event_wock);

	spin_wock_bh(&pwiv->tx.tx_wock);
	pwiv->tx.fwags &= ~ATH9K_HTC_OP_TX_DWAIN;
	spin_unwock_bh(&pwiv->tx.tx_wock);
}

void ath9k_tx_faiwed_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath9k_htc_pwiv *pwiv = fwom_taskwet(pwiv, t, tx_faiwed_taskwet);

	spin_wock(&pwiv->tx.tx_wock);
	if (pwiv->tx.fwags & ATH9K_HTC_OP_TX_DWAIN) {
		spin_unwock(&pwiv->tx.tx_wock);
		wetuwn;
	}
	spin_unwock(&pwiv->tx.tx_wock);

	ath9k_htc_tx_dwainq(pwiv, &pwiv->tx.tx_faiwed);
}

static inwine boow check_cookie(stwuct ath9k_htc_pwiv *pwiv,
				stwuct sk_buff *skb,
				u8 cookie, u8 epid)
{
	u8 fcookie = 0;

	if (epid == pwiv->mgmt_ep) {
		stwuct tx_mgmt_hdw *hdw;
		hdw = (stwuct tx_mgmt_hdw *) skb->data;
		fcookie = hdw->cookie;
	} ewse if ((epid == pwiv->data_bk_ep) ||
		   (epid == pwiv->data_be_ep) ||
		   (epid == pwiv->data_vi_ep) ||
		   (epid == pwiv->data_vo_ep) ||
		   (epid == pwiv->cab_ep)) {
		stwuct tx_fwame_hdw *hdw;
		hdw = (stwuct tx_fwame_hdw *) skb->data;
		fcookie = hdw->cookie;
	}

	if (fcookie == cookie)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct sk_buff* ath9k_htc_tx_get_packet(stwuct ath9k_htc_pwiv *pwiv,
					       stwuct __wmi_event_txstatus *txs)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct sk_buff_head *epid_queue;
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;
	u8 epid = MS(txs->ts_wate, ATH9K_HTC_TXSTAT_EPID);

	epid_queue = get_htc_epid_queue(pwiv, epid);
	if (!epid_queue)
		wetuwn NUWW;

	spin_wock_iwqsave(&epid_queue->wock, fwags);
	skb_queue_wawk_safe(epid_queue, skb, tmp) {
		if (check_cookie(pwiv, skb, txs->cookie, epid)) {
			__skb_unwink(skb, epid_queue);
			spin_unwock_iwqwestowe(&epid_queue->wock, fwags);
			wetuwn skb;
		}
	}
	spin_unwock_iwqwestowe(&epid_queue->wock, fwags);

	ath_dbg(common, XMIT, "No matching packet fow cookie: %d, epid: %d\n",
		txs->cookie, epid);

	wetuwn NUWW;
}

void ath9k_htc_txstatus(stwuct ath9k_htc_pwiv *pwiv, void *wmi_event)
{
	stwuct wmi_event_txstatus *txs = wmi_event;
	stwuct __wmi_event_txstatus *__txs;
	stwuct sk_buff *skb;
	stwuct ath9k_htc_tx_event *tx_pend;
	int i;

	if (WAWN_ON_ONCE(txs->cnt > HTC_MAX_TX_STATUS))
		wetuwn;

	fow (i = 0; i < txs->cnt; i++) {
		__txs = &txs->txstatus[i];

		skb = ath9k_htc_tx_get_packet(pwiv, __txs);
		if (!skb) {
			/*
			 * Stowe this event, so that the TX cweanup
			 * woutine can check watew fow the needed packet.
			 */
			tx_pend = kzawwoc(sizeof(stwuct ath9k_htc_tx_event),
					  GFP_ATOMIC);
			if (!tx_pend)
				continue;

			memcpy(&tx_pend->txs, __txs,
			       sizeof(stwuct __wmi_event_txstatus));

			spin_wock(&pwiv->wmi->event_wock);
			wist_add_taiw(&tx_pend->wist,
				      &pwiv->wmi->pending_tx_events);
			spin_unwock(&pwiv->wmi->event_wock);

			continue;
		}

		ath9k_htc_tx_pwocess(pwiv, skb, __txs);
	}

	/* Wake TX queues if needed */
	ath9k_htc_check_wake_queues(pwiv);
}

void ath9k_htc_txep(void *dwv_pwiv, stwuct sk_buff *skb,
		    enum htc_endpoint_id ep_id, boow txok)
{
	stwuct ath9k_htc_pwiv *pwiv = dwv_pwiv;
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	stwuct sk_buff_head *epid_queue;

	tx_ctw = HTC_SKB_CB(skb);
	tx_ctw->txok = txok;
	tx_ctw->timestamp = jiffies;

	if (!txok) {
		skb_queue_taiw(&pwiv->tx.tx_faiwed, skb);
		taskwet_scheduwe(&pwiv->tx_faiwed_taskwet);
		wetuwn;
	}

	epid_queue = get_htc_epid_queue(pwiv, ep_id);
	if (!epid_queue) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	skb_queue_taiw(epid_queue, skb);
}

static inwine boow check_packet(stwuct ath9k_htc_pwiv *pwiv, stwuct sk_buff *skb)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath9k_htc_tx_ctw *tx_ctw;

	tx_ctw = HTC_SKB_CB(skb);

	if (time_aftew(jiffies,
		       tx_ctw->timestamp +
		       msecs_to_jiffies(ATH9K_HTC_TX_TIMEOUT_INTEWVAW))) {
		ath_dbg(common, XMIT, "Dwopping a packet due to TX timeout\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static void ath9k_htc_tx_cweanup_queue(stwuct ath9k_htc_pwiv *pwiv,
				       stwuct sk_buff_head *epid_queue)
{
	boow pwocess = fawse;
	unsigned wong fwags;
	stwuct sk_buff *skb, *tmp;
	stwuct sk_buff_head queue;

	skb_queue_head_init(&queue);

	spin_wock_iwqsave(&epid_queue->wock, fwags);
	skb_queue_wawk_safe(epid_queue, skb, tmp) {
		if (check_packet(pwiv, skb)) {
			__skb_unwink(skb, epid_queue);
			__skb_queue_taiw(&queue, skb);
			pwocess = twue;
		}
	}
	spin_unwock_iwqwestowe(&epid_queue->wock, fwags);

	if (pwocess) {
		skb_queue_wawk_safe(&queue, skb, tmp) {
			__skb_unwink(skb, &queue);
			ath9k_htc_tx_pwocess(pwiv, skb, NUWW);
		}
	}
}

void ath9k_htc_tx_cweanup_timew(stwuct timew_wist *t)
{
	stwuct ath9k_htc_pwiv *pwiv = fwom_timew(pwiv, t, tx.cweanup_timew);
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath9k_htc_tx_event *event, *tmp;
	stwuct sk_buff *skb;

	spin_wock(&pwiv->wmi->event_wock);
	wist_fow_each_entwy_safe(event, tmp, &pwiv->wmi->pending_tx_events, wist) {

		skb = ath9k_htc_tx_get_packet(pwiv, &event->txs);
		if (skb) {
			ath_dbg(common, XMIT,
				"Found packet fow cookie: %d, epid: %d\n",
				event->txs.cookie,
				MS(event->txs.ts_wate, ATH9K_HTC_TXSTAT_EPID));

			ath9k_htc_tx_pwocess(pwiv, skb, &event->txs);
			wist_dew(&event->wist);
			kfwee(event);
			continue;
		}

		if (++event->count >= ATH9K_HTC_TX_TIMEOUT_COUNT) {
			wist_dew(&event->wist);
			kfwee(event);
		}
	}
	spin_unwock(&pwiv->wmi->event_wock);

	/*
	 * Check if status-pending packets have to be cweaned up.
	 */
	ath9k_htc_tx_cweanup_queue(pwiv, &pwiv->tx.mgmt_ep_queue);
	ath9k_htc_tx_cweanup_queue(pwiv, &pwiv->tx.cab_ep_queue);
	ath9k_htc_tx_cweanup_queue(pwiv, &pwiv->tx.data_be_queue);
	ath9k_htc_tx_cweanup_queue(pwiv, &pwiv->tx.data_bk_queue);
	ath9k_htc_tx_cweanup_queue(pwiv, &pwiv->tx.data_vi_queue);
	ath9k_htc_tx_cweanup_queue(pwiv, &pwiv->tx.data_vo_queue);

	/* Wake TX queues if needed */
	ath9k_htc_check_wake_queues(pwiv);

	mod_timew(&pwiv->tx.cweanup_timew,
		  jiffies + msecs_to_jiffies(ATH9K_HTC_TX_CWEANUP_INTEWVAW));
}

int ath9k_tx_init(stwuct ath9k_htc_pwiv *pwiv)
{
	skb_queue_head_init(&pwiv->tx.mgmt_ep_queue);
	skb_queue_head_init(&pwiv->tx.cab_ep_queue);
	skb_queue_head_init(&pwiv->tx.data_be_queue);
	skb_queue_head_init(&pwiv->tx.data_bk_queue);
	skb_queue_head_init(&pwiv->tx.data_vi_queue);
	skb_queue_head_init(&pwiv->tx.data_vo_queue);
	skb_queue_head_init(&pwiv->tx.tx_faiwed);

	/* Awwow ath9k_wmi_event_taskwet(WMI_TXSTATUS_EVENTID) to opewate. */
	smp_wmb();
	pwiv->tx.initiawized = twue;

	wetuwn 0;
}

void ath9k_tx_cweanup(stwuct ath9k_htc_pwiv *pwiv)
{

}

boow ath9k_htc_txq_setup(stwuct ath9k_htc_pwiv *pwiv, int subtype)
{
	stwuct ath_hw *ah = pwiv->ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_tx_queue_info qi;
	int qnum;

	memset(&qi, 0, sizeof(qi));
	ATH9K_HTC_INIT_TXQ(subtype);

	qnum = ath9k_hw_setuptxqueue(pwiv->ah, ATH9K_TX_QUEUE_DATA, &qi);
	if (qnum == -1)
		wetuwn fawse;

	if (qnum >= AWWAY_SIZE(pwiv->hwq_map)) {
		ath_eww(common, "qnum %u out of wange, max %zu!\n",
			qnum, AWWAY_SIZE(pwiv->hwq_map));
		ath9k_hw_weweasetxqueue(ah, qnum);
		wetuwn fawse;
	}

	pwiv->hwq_map[subtype] = qnum;
	wetuwn twue;
}

int ath9k_htc_cabq_setup(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath9k_tx_queue_info qi;

	memset(&qi, 0, sizeof(qi));
	ATH9K_HTC_INIT_TXQ(0);

	wetuwn ath9k_hw_setuptxqueue(pwiv->ah, ATH9K_TX_QUEUE_CAB, &qi);
}

/******/
/* WX */
/******/

/*
 * Cawcuwate the WX fiwtew to be set in the HW.
 */
u32 ath9k_htc_cawcwxfiwtew(stwuct ath9k_htc_pwiv *pwiv)
{
#define	WX_FIWTEW_PWESEWVE (ATH9K_WX_FIWTEW_PHYEWW | ATH9K_WX_FIWTEW_PHYWADAW)

	stwuct ath_hw *ah = pwiv->ah;
	u32 wfiwt;

	wfiwt = (ath9k_hw_getwxfiwtew(ah) & WX_FIWTEW_PWESEWVE)
		| ATH9K_WX_FIWTEW_UCAST | ATH9K_WX_FIWTEW_BCAST
		| ATH9K_WX_FIWTEW_MCAST;

	if (pwiv->wxfiwtew & FIF_PWOBE_WEQ)
		wfiwt |= ATH9K_WX_FIWTEW_PWOBEWEQ;

	if (ah->is_monitowing)
		wfiwt |= ATH9K_WX_FIWTEW_PWOM;

	if (pwiv->wxfiwtew & FIF_CONTWOW)
		wfiwt |= ATH9K_WX_FIWTEW_CONTWOW;

	if ((ah->opmode == NW80211_IFTYPE_STATION) &&
	    (pwiv->nvifs <= 1) &&
	    !(pwiv->wxfiwtew & FIF_BCN_PWBWESP_PWOMISC))
		wfiwt |= ATH9K_WX_FIWTEW_MYBEACON;
	ewse
		wfiwt |= ATH9K_WX_FIWTEW_BEACON;

	if (conf_is_ht(&pwiv->hw->conf)) {
		wfiwt |= ATH9K_WX_FIWTEW_COMP_BAW;
		wfiwt |= ATH9K_WX_FIWTEW_UNCOMP_BA_BAW;
	}

	if (pwiv->wxfiwtew & FIF_PSPOWW)
		wfiwt |= ATH9K_WX_FIWTEW_PSPOWW;

	if (pwiv->nvifs > 1 ||
	    pwiv->wxfiwtew & (FIF_OTHEW_BSS | FIF_MCAST_ACTION))
		wfiwt |= ATH9K_WX_FIWTEW_MCAST_BCAST_AWW;

	wetuwn wfiwt;

#undef WX_FIWTEW_PWESEWVE
}

/*
 * Wecv initiawization fow opmode change.
 */
static void ath9k_htc_opmode_init(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_hw *ah = pwiv->ah;
	u32 wfiwt, mfiwt[2];

	/* configuwe wx fiwtew */
	wfiwt = ath9k_htc_cawcwxfiwtew(pwiv);
	ath9k_hw_setwxfiwtew(ah, wfiwt);

	/* cawcuwate and instaww muwticast fiwtew */
	mfiwt[0] = mfiwt[1] = ~0;
	ath9k_hw_setmcastfiwtew(ah, mfiwt[0], mfiwt[1]);
}

void ath9k_host_wx_init(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	ath9k_hw_wxena(pwiv->ah);
	ath9k_htc_opmode_init(pwiv);
	ath9k_hw_stawtpcuweceive(pwiv->ah, test_bit(ATH_OP_SCANNING, &common->op_fwags));
}

static inwine void convewt_htc_fwag(stwuct ath_wx_status *wx_stats,
				   stwuct ath_htc_wx_status *wxstatus)
{
	wx_stats->enc_fwags = 0;
	wx_stats->bw = WATE_INFO_BW_20;
	if (wxstatus->ws_fwags & ATH9K_WX_2040)
		wx_stats->bw = WATE_INFO_BW_40;
	if (wxstatus->ws_fwags & ATH9K_WX_GI)
		wx_stats->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
}

static void wx_status_htc_to_ath(stwuct ath_wx_status *wx_stats,
				 stwuct ath_htc_wx_status *wxstatus)
{
	wx_stats->ws_datawen	= be16_to_cpu(wxstatus->ws_datawen);
	wx_stats->ws_status	= wxstatus->ws_status;
	wx_stats->ws_phyeww	= wxstatus->ws_phyeww;
	wx_stats->ws_wssi	= wxstatus->ws_wssi;
	wx_stats->ws_keyix	= wxstatus->ws_keyix;
	wx_stats->ws_wate	= wxstatus->ws_wate;
	wx_stats->ws_antenna	= wxstatus->ws_antenna;
	wx_stats->ws_mowe	= wxstatus->ws_mowe;

	memcpy(wx_stats->ws_wssi_ctw, wxstatus->ws_wssi_ctw,
		sizeof(wx_stats->ws_wssi_ctw));
	memcpy(wx_stats->ws_wssi_ext, wxstatus->ws_wssi_ext,
		sizeof(wx_stats->ws_wssi_ext));

	wx_stats->ws_isaggw	= wxstatus->ws_isaggw;
	wx_stats->ws_moweaggw	= wxstatus->ws_moweaggw;
	wx_stats->ws_num_dewims	= wxstatus->ws_num_dewims;
	convewt_htc_fwag(wx_stats, wxstatus);
}

static boow ath9k_wx_pwepawe(stwuct ath9k_htc_pwiv *pwiv,
			     stwuct ath9k_htc_wxbuf *wxbuf,
			     stwuct ieee80211_wx_status *wx_status)

{
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct sk_buff *skb = wxbuf->skb;
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath_hw *ah = common->ah;
	stwuct ath_htc_wx_status *wxstatus;
	stwuct ath_wx_status wx_stats;
	boow decwypt_ewwow = fawse;
	u16 ws_datawen;
	boow is_phyeww;

	if (skb->wen < HTC_WX_FWAME_HEADEW_SIZE) {
		ath_eww(common, "Cowwupted WX fwame, dwopping (wen: %d)\n",
			skb->wen);
		goto wx_next;
	}

	wxstatus = (stwuct ath_htc_wx_status *)skb->data;

	ws_datawen = be16_to_cpu(wxstatus->ws_datawen);
	if (unwikewy(ws_datawen -
	    (skb->wen - HTC_WX_FWAME_HEADEW_SIZE) != 0)) {
		ath_eww(common,
			"Cowwupted WX data wen, dwopping (dwen: %d, skbwen: %d)\n",
			ws_datawen, skb->wen);
		goto wx_next;
	}

	is_phyeww = wxstatus->ws_status & ATH9K_WXEWW_PHY;
	/*
	 * Discawd zewo-wength packets and packets smawwew than an ACK
	 * which awe not PHY_EWWOW (showt wadaw puwses have a wength of 3)
	 */
	if (unwikewy(!ws_datawen || (ws_datawen < 10 && !is_phyeww))) {
		ath_dbg(common, ANY,
			"Showt WX data wen, dwopping (dwen: %d)\n",
			ws_datawen);
		goto wx_next;
	}

	if (wxstatus->ws_keyix >= ATH_KEYMAX &&
	    wxstatus->ws_keyix != ATH9K_WXKEYIX_INVAWID) {
		ath_dbg(common, ANY,
			"Invawid keyix, dwopping (keyix: %d)\n",
			wxstatus->ws_keyix);
		goto wx_next;
	}

	/* Get the WX status infowmation */

	memset(wx_status, 0, sizeof(stwuct ieee80211_wx_status));

	/* Copy evewything fwom ath_htc_wx_status (HTC_WX_FWAME_HEADEW).
	 * Aftew this, we can dwop this pawt of skb. */
	wx_status_htc_to_ath(&wx_stats, wxstatus);
	ath9k_htc_eww_stat_wx(pwiv, &wx_stats);
	wx_status->mactime = be64_to_cpu(wxstatus->ws_tstamp);
	skb_puww(skb, HTC_WX_FWAME_HEADEW_SIZE);

	/*
	 * evewything but the wate is checked hewe, the wate check is done
	 * sepawatewy to avoid doing two wookups fow a wate fow each fwame.
	 */
	hdw = (stwuct ieee80211_hdw *)skb->data;

	/*
	 * Pwocess PHY ewwows and wetuwn so that the packet
	 * can be dwopped.
	 */
	if (unwikewy(is_phyeww)) {
		/* TODO: Not using DFS pwocessing now. */
		if (ath_cmn_pwocess_fft(&pwiv->spec_pwiv, hdw,
				    &wx_stats, wx_status->mactime)) {
			/* TODO: Code to cowwect spectwaw scan statistics */
		}
		goto wx_next;
	}

	if (!ath9k_cmn_wx_accept(common, hdw, wx_status, &wx_stats,
			&decwypt_ewwow, pwiv->wxfiwtew))
		goto wx_next;

	ath9k_cmn_wx_skb_postpwocess(common, skb, &wx_stats,
				     wx_status, decwypt_ewwow);

	if (ath9k_cmn_pwocess_wate(common, hw, &wx_stats, wx_status))
		goto wx_next;

	wx_stats.is_mybeacon = ath_is_mybeacon(common, hdw);
	ath9k_cmn_pwocess_wssi(common, hw, &wx_stats, wx_status);

	wx_status->band = ah->cuwchan->chan->band;
	wx_status->fweq = ah->cuwchan->chan->centew_fweq;
	wx_status->antenna = wx_stats.ws_antenna;
	wx_status->fwag |= WX_FWAG_MACTIME_END;

	wetuwn twue;
wx_next:
	wetuwn fawse;
}

/*
 * FIXME: Handwe FWUSH watew on.
 */
void ath9k_wx_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ath9k_htc_pwiv *pwiv = fwom_taskwet(pwiv, t, wx_taskwet);
	stwuct ath9k_htc_wxbuf *wxbuf = NUWW, *tmp_buf = NUWW;
	stwuct ieee80211_wx_status wx_status;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	stwuct ieee80211_hdw *hdw;

	do {
		spin_wock_iwqsave(&pwiv->wx.wxbufwock, fwags);
		wist_fow_each_entwy(tmp_buf, &pwiv->wx.wxbuf, wist) {
			if (tmp_buf->in_pwocess) {
				wxbuf = tmp_buf;
				bweak;
			}
		}

		if (wxbuf == NUWW) {
			spin_unwock_iwqwestowe(&pwiv->wx.wxbufwock, fwags);
			bweak;
		}

		if (!wxbuf->skb)
			goto wequeue;

		if (!ath9k_wx_pwepawe(pwiv, wxbuf, &wx_status)) {
			dev_kfwee_skb_any(wxbuf->skb);
			goto wequeue;
		}

		memcpy(IEEE80211_SKB_WXCB(wxbuf->skb), &wx_status,
		       sizeof(stwuct ieee80211_wx_status));
		skb = wxbuf->skb;
		hdw = (stwuct ieee80211_hdw *) skb->data;

		if (ieee80211_is_beacon(hdw->fwame_contwow) && pwiv->ps_enabwed)
				ieee80211_queue_wowk(pwiv->hw, &pwiv->ps_wowk);

		spin_unwock_iwqwestowe(&pwiv->wx.wxbufwock, fwags);

		ieee80211_wx(pwiv->hw, skb);

		spin_wock_iwqsave(&pwiv->wx.wxbufwock, fwags);
wequeue:
		wxbuf->in_pwocess = fawse;
		wxbuf->skb = NUWW;
		wist_move_taiw(&wxbuf->wist, &pwiv->wx.wxbuf);
		wxbuf = NUWW;
		spin_unwock_iwqwestowe(&pwiv->wx.wxbufwock, fwags);
	} whiwe (1);

}

void ath9k_htc_wxep(void *dwv_pwiv, stwuct sk_buff *skb,
		    enum htc_endpoint_id ep_id)
{
	stwuct ath9k_htc_pwiv *pwiv = dwv_pwiv;
	stwuct ath_hw *ah = pwiv->ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_wxbuf *wxbuf = NUWW, *tmp_buf = NUWW;
	unsigned wong fwags;

	/* Check if ath9k_wx_init() compweted. */
	if (!data_wace(pwiv->wx.initiawized))
		goto eww;

	spin_wock_iwqsave(&pwiv->wx.wxbufwock, fwags);
	wist_fow_each_entwy(tmp_buf, &pwiv->wx.wxbuf, wist) {
		if (!tmp_buf->in_pwocess) {
			wxbuf = tmp_buf;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&pwiv->wx.wxbufwock, fwags);

	if (wxbuf == NUWW) {
		ath_dbg(common, ANY, "No fwee WX buffew\n");
		goto eww;
	}

	spin_wock_iwqsave(&pwiv->wx.wxbufwock, fwags);
	wxbuf->skb = skb;
	wxbuf->in_pwocess = twue;
	spin_unwock_iwqwestowe(&pwiv->wx.wxbufwock, fwags);

	taskwet_scheduwe(&pwiv->wx_taskwet);
	wetuwn;
eww:
	dev_kfwee_skb_any(skb);
}

/* FIXME: Wocking fow cweanup/init */

void ath9k_wx_cweanup(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath9k_htc_wxbuf *wxbuf, *tbuf;

	wist_fow_each_entwy_safe(wxbuf, tbuf, &pwiv->wx.wxbuf, wist) {
		wist_dew(&wxbuf->wist);
		if (wxbuf->skb)
			dev_kfwee_skb_any(wxbuf->skb);
		kfwee(wxbuf);
	}
}

int ath9k_wx_init(stwuct ath9k_htc_pwiv *pwiv)
{
	int i = 0;

	INIT_WIST_HEAD(&pwiv->wx.wxbuf);
	spin_wock_init(&pwiv->wx.wxbufwock);

	fow (i = 0; i < ATH9K_HTC_WXBUF; i++) {
		stwuct ath9k_htc_wxbuf *wxbuf =
			kzawwoc(sizeof(stwuct ath9k_htc_wxbuf), GFP_KEWNEW);
		if (wxbuf == NUWW)
			goto eww;

		wist_add_taiw(&wxbuf->wist, &pwiv->wx.wxbuf);
	}

	/* Awwow ath9k_htc_wxep() to opewate. */
	smp_wmb();
	pwiv->wx.initiawized = twue;

	wetuwn 0;

eww:
	ath9k_wx_cweanup(pwiv);
	wetuwn -ENOMEM;
}
