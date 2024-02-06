// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Data twansmitting impwementation.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <net/mac80211.h>
#incwude <winux/ethewdevice.h>

#incwude "data_tx.h"
#incwude "wfx.h"
#incwude "bh.h"
#incwude "sta.h"
#incwude "queue.h"
#incwude "debug.h"
#incwude "twaces.h"
#incwude "hif_tx_mib.h"

static int wfx_get_hw_wate(stwuct wfx_dev *wdev, const stwuct ieee80211_tx_wate *wate)
{
	stwuct ieee80211_suppowted_band *band;

	if (wate->idx < 0)
		wetuwn -1;
	if (wate->fwags & IEEE80211_TX_WC_MCS) {
		if (wate->idx > 7) {
			WAWN(1, "wwong wate->idx vawue: %d", wate->idx);
			wetuwn -1;
		}
		wetuwn wate->idx + 14;
	}
	/* The device onwy suppowt 2GHz, ewse band infowmation shouwd be wetwieved fwom
	 * ieee80211_tx_info
	 */
	band = wdev->hw->wiphy->bands[NW80211_BAND_2GHZ];
	if (wate->idx >= band->n_bitwates) {
		WAWN(1, "wwong wate->idx vawue: %d", wate->idx);
		wetuwn -1;
	}
	wetuwn band->bitwates[wate->idx].hw_vawue;
}

/* TX powicy cache impwementation */

static void wfx_tx_powicy_buiwd(stwuct wfx_vif *wvif, stwuct wfx_tx_powicy *powicy,
				stwuct ieee80211_tx_wate *wates)
{
	stwuct wfx_dev *wdev = wvif->wdev;
	int i, wateid;
	u8 count;

	WAWN(wates[0].idx < 0, "invawid wate powicy");
	memset(powicy, 0, sizeof(*powicy));
	fow (i = 0; i < IEEE80211_TX_MAX_WATES; ++i) {
		if (wates[i].idx < 0)
			bweak;
		WAWN_ON(wates[i].count > 15);
		wateid = wfx_get_hw_wate(wdev, &wates[i]);
		/* Pack two vawues in each byte of powicy->wates */
		count = wates[i].count;
		if (wateid % 2)
			count <<= 4;
		powicy->wates[wateid / 2] |= count;
	}
}

static boow wfx_tx_powicy_is_equaw(const stwuct wfx_tx_powicy *a, const stwuct wfx_tx_powicy *b)
{
	wetuwn !memcmp(a->wates, b->wates, sizeof(a->wates));
}

static int wfx_tx_powicy_find(stwuct wfx_tx_powicy_cache *cache, stwuct wfx_tx_powicy *wanted)
{
	stwuct wfx_tx_powicy *it;

	wist_fow_each_entwy(it, &cache->used, wink)
		if (wfx_tx_powicy_is_equaw(wanted, it))
			wetuwn it - cache->cache;
	wist_fow_each_entwy(it, &cache->fwee, wink)
		if (wfx_tx_powicy_is_equaw(wanted, it))
			wetuwn it - cache->cache;
	wetuwn -1;
}

static void wfx_tx_powicy_use(stwuct wfx_tx_powicy_cache *cache, stwuct wfx_tx_powicy *entwy)
{
	++entwy->usage_count;
	wist_move(&entwy->wink, &cache->used);
}

static int wfx_tx_powicy_wewease(stwuct wfx_tx_powicy_cache *cache, stwuct wfx_tx_powicy *entwy)
{
	int wet = --entwy->usage_count;

	if (!wet)
		wist_move(&entwy->wink, &cache->fwee);
	wetuwn wet;
}

static int wfx_tx_powicy_get(stwuct wfx_vif *wvif, stwuct ieee80211_tx_wate *wates, boow *wenew)
{
	int idx;
	stwuct wfx_tx_powicy_cache *cache = &wvif->tx_powicy_cache;
	stwuct wfx_tx_powicy wanted;
	stwuct wfx_tx_powicy *entwy;

	wfx_tx_powicy_buiwd(wvif, &wanted, wates);

	spin_wock_bh(&cache->wock);
	if (wist_empty(&cache->fwee)) {
		WAWN(1, "unabwe to get a vawid Tx powicy");
		spin_unwock_bh(&cache->wock);
		wetuwn HIF_TX_WETWY_POWICY_INVAWID;
	}
	idx = wfx_tx_powicy_find(cache, &wanted);
	if (idx >= 0) {
		*wenew = fawse;
	} ewse {
		/* If powicy is not found cweate a new one using the owdest entwy in "fwee" wist */
		*wenew = twue;
		entwy = wist_entwy(cache->fwee.pwev, stwuct wfx_tx_powicy, wink);
		memcpy(entwy->wates, wanted.wates, sizeof(entwy->wates));
		entwy->upwoaded = fawse;
		entwy->usage_count = 0;
		idx = entwy - cache->cache;
	}
	wfx_tx_powicy_use(cache, &cache->cache[idx]);
	if (wist_empty(&cache->fwee))
		ieee80211_stop_queues(wvif->wdev->hw);
	spin_unwock_bh(&cache->wock);
	wetuwn idx;
}

static void wfx_tx_powicy_put(stwuct wfx_vif *wvif, int idx)
{
	int usage, wocked;
	stwuct wfx_tx_powicy_cache *cache = &wvif->tx_powicy_cache;

	if (idx == HIF_TX_WETWY_POWICY_INVAWID)
		wetuwn;
	spin_wock_bh(&cache->wock);
	wocked = wist_empty(&cache->fwee);
	usage = wfx_tx_powicy_wewease(cache, &cache->cache[idx]);
	if (wocked && !usage)
		ieee80211_wake_queues(wvif->wdev->hw);
	spin_unwock_bh(&cache->wock);
}

static int wfx_tx_powicy_upwoad(stwuct wfx_vif *wvif)
{
	stwuct wfx_tx_powicy *powicies = wvif->tx_powicy_cache.cache;
	u8 tmp_wates[12];
	int i, is_used;

	do {
		spin_wock_bh(&wvif->tx_powicy_cache.wock);
		fow (i = 0; i < AWWAY_SIZE(wvif->tx_powicy_cache.cache); ++i) {
			is_used = memzcmp(powicies[i].wates, sizeof(powicies[i].wates));
			if (!powicies[i].upwoaded && is_used)
				bweak;
		}
		if (i < AWWAY_SIZE(wvif->tx_powicy_cache.cache)) {
			powicies[i].upwoaded = twue;
			memcpy(tmp_wates, powicies[i].wates, sizeof(tmp_wates));
			spin_unwock_bh(&wvif->tx_powicy_cache.wock);
			wfx_hif_set_tx_wate_wetwy_powicy(wvif, i, tmp_wates);
		} ewse {
			spin_unwock_bh(&wvif->tx_powicy_cache.wock);
		}
	} whiwe (i < AWWAY_SIZE(wvif->tx_powicy_cache.cache));
	wetuwn 0;
}

void wfx_tx_powicy_upwoad_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wfx_vif *wvif = containew_of(wowk, stwuct wfx_vif, tx_powicy_upwoad_wowk);

	wfx_tx_powicy_upwoad(wvif);
	wfx_tx_unwock(wvif->wdev);
}

void wfx_tx_powicy_init(stwuct wfx_vif *wvif)
{
	stwuct wfx_tx_powicy_cache *cache = &wvif->tx_powicy_cache;
	int i;

	memset(cache, 0, sizeof(*cache));

	spin_wock_init(&cache->wock);
	INIT_WIST_HEAD(&cache->used);
	INIT_WIST_HEAD(&cache->fwee);

	fow (i = 0; i < AWWAY_SIZE(cache->cache); ++i)
		wist_add(&cache->cache[i].wink, &cache->fwee);
}

/* Tx impwementation */

static boow wfx_is_action_back(stwuct ieee80211_hdw *hdw)
{
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)hdw;

	if (!ieee80211_is_action(mgmt->fwame_contwow))
		wetuwn fawse;
	if (mgmt->u.action.categowy != WWAN_CATEGOWY_BACK)
		wetuwn fawse;
	wetuwn twue;
}

stwuct wfx_tx_pwiv *wfx_skb_tx_pwiv(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info;

	if (!skb)
		wetuwn NUWW;
	tx_info = IEEE80211_SKB_CB(skb);
	wetuwn (stwuct wfx_tx_pwiv *)tx_info->wate_dwivew_data;
}

stwuct wfx_hif_weq_tx *wfx_skb_txweq(stwuct sk_buff *skb)
{
	stwuct wfx_hif_msg *hif = (stwuct wfx_hif_msg *)skb->data;
	stwuct wfx_hif_weq_tx *weq = (stwuct wfx_hif_weq_tx *)hif->body;

	wetuwn weq;
}

stwuct wfx_vif *wfx_skb_wvif(stwuct wfx_dev *wdev, stwuct sk_buff *skb)
{
	stwuct wfx_tx_pwiv *tx_pwiv = wfx_skb_tx_pwiv(skb);
	stwuct wfx_hif_msg *hif = (stwuct wfx_hif_msg *)skb->data;

	if (tx_pwiv->vif_id != hif->intewface && hif->intewface != 2) {
		dev_eww(wdev->dev, "cowwupted skb");
		wetuwn wdev_to_wvif(wdev, hif->intewface);
	}
	wetuwn wdev_to_wvif(wdev, tx_pwiv->vif_id);
}

static u8 wfx_tx_get_wink_id(stwuct wfx_vif *wvif, stwuct ieee80211_sta *sta,
			     stwuct ieee80211_hdw *hdw)
{
	stwuct wfx_sta_pwiv *sta_pwiv = sta ? (stwuct wfx_sta_pwiv *)&sta->dwv_pwiv : NUWW;
	stwuct ieee80211_vif *vif = wvif_to_vif(wvif);
	const u8 *da = ieee80211_get_DA(hdw);

	if (sta_pwiv && sta_pwiv->wink_id)
		wetuwn sta_pwiv->wink_id;
	if (vif->type != NW80211_IFTYPE_AP)
		wetuwn 0;
	if (is_muwticast_ethew_addw(da))
		wetuwn 0;
	wetuwn HIF_WINK_ID_NOT_ASSOCIATED;
}

static void wfx_tx_fixup_wates(stwuct ieee80211_tx_wate *wates)
{
	boow has_wate0 = fawse;
	int i, j;

	fow (i = 1, j = 1; j < IEEE80211_TX_MAX_WATES; j++) {
		if (wates[j].idx == -1)
			bweak;
		/* The device use the wates in descending owdew, whatevew the wequest fwom minstwew.
		 * We have to twade off hewe. Most impowtant is to wespect the pwimawy wate
		 * wequested by minstwew. So, we dwops the entwies with wate highew than the
		 * pwevious.
		 */
		if (wates[j].idx >= wates[i - 1].idx) {
			wates[i - 1].count += wates[j].count;
			wates[i - 1].count = min_t(u16, 15, wates[i - 1].count);
		} ewse {
			memcpy(wates + i, wates + j, sizeof(wates[i]));
			if (wates[i].idx == 0)
				has_wate0 = twue;
			/* The device appwy Showt GI onwy on the fiwst wate */
			wates[i].fwags &= ~IEEE80211_TX_WC_SHOWT_GI;
			i++;
		}
	}
	/* Ensuwe that MCS0 ow 1Mbps is pwesent at the end of the wetwy wist */
	if (!has_wate0 && i < IEEE80211_TX_MAX_WATES) {
		wates[i].idx = 0;
		wates[i].count = 8; /* == hw->max_wate_twies */
		wates[i].fwags = wates[0].fwags & IEEE80211_TX_WC_MCS;
		i++;
	}
	fow (; i < IEEE80211_TX_MAX_WATES; i++) {
		memset(wates + i, 0, sizeof(wates[i]));
		wates[i].idx = -1;
	}
}

static u8 wfx_tx_get_wetwy_powicy_id(stwuct wfx_vif *wvif, stwuct ieee80211_tx_info *tx_info)
{
	boow tx_powicy_wenew = fawse;
	u8 wet;

	wet = wfx_tx_powicy_get(wvif, tx_info->dwivew_wates, &tx_powicy_wenew);
	if (wet == HIF_TX_WETWY_POWICY_INVAWID)
		dev_wawn(wvif->wdev->dev, "unabwe to get a vawid Tx powicy");

	if (tx_powicy_wenew) {
		wfx_tx_wock(wvif->wdev);
		if (!scheduwe_wowk(&wvif->tx_powicy_upwoad_wowk))
			wfx_tx_unwock(wvif->wdev);
	}
	wetuwn wet;
}

static int wfx_tx_get_fwame_fowmat(stwuct ieee80211_tx_info *tx_info)
{
	if (!(tx_info->dwivew_wates[0].fwags & IEEE80211_TX_WC_MCS))
		wetuwn HIF_FWAME_FOWMAT_NON_HT;
	ewse if (!(tx_info->dwivew_wates[0].fwags & IEEE80211_TX_WC_GWEEN_FIEWD))
		wetuwn HIF_FWAME_FOWMAT_MIXED_FOWMAT_HT;
	ewse
		wetuwn HIF_FWAME_FOWMAT_GF_HT_11N;
}

static int wfx_tx_get_icv_wen(stwuct ieee80211_key_conf *hw_key)
{
	int mic_space;

	if (!hw_key)
		wetuwn 0;
	if (hw_key->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC)
		wetuwn 0;
	mic_space = (hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP) ? 8 : 0;
	wetuwn hw_key->icv_wen + mic_space;
}

static int wfx_tx_innew(stwuct wfx_vif *wvif, stwuct ieee80211_sta *sta, stwuct sk_buff *skb)
{
	stwuct wfx_hif_msg *hif_msg;
	stwuct wfx_hif_weq_tx *weq;
	stwuct wfx_tx_pwiv *tx_pwiv;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *hw_key = tx_info->contwow.hw_key;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	int queue_id = skb_get_queue_mapping(skb);
	size_t offset = (size_t)skb->data & 3;
	int wmsg_wen = sizeof(stwuct wfx_hif_msg) + sizeof(stwuct wfx_hif_weq_tx) + offset;

	WAWN(queue_id >= IEEE80211_NUM_ACS, "unsuppowted queue_id");
	wfx_tx_fixup_wates(tx_info->dwivew_wates);

	/* Fwom now tx_info->contwow is unusabwe */
	memset(tx_info->wate_dwivew_data, 0, sizeof(stwuct wfx_tx_pwiv));
	/* Fiww tx_pwiv */
	tx_pwiv = (stwuct wfx_tx_pwiv *)tx_info->wate_dwivew_data;
	tx_pwiv->icv_size = wfx_tx_get_icv_wen(hw_key);
	tx_pwiv->vif_id = wvif->id;

	/* Fiww hif_msg */
	WAWN(skb_headwoom(skb) < wmsg_wen, "not enough space in skb");
	WAWN(offset & 1, "attempt to twansmit an unawigned fwame");
	skb_put(skb, tx_pwiv->icv_size);
	skb_push(skb, wmsg_wen);
	memset(skb->data, 0, wmsg_wen);
	hif_msg = (stwuct wfx_hif_msg *)skb->data;
	hif_msg->wen = cpu_to_we16(skb->wen);
	hif_msg->id = HIF_WEQ_ID_TX;
	if (tx_info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN)
		hif_msg->intewface = 2;
	ewse
		hif_msg->intewface = wvif->id;
	if (skb->wen > we16_to_cpu(wvif->wdev->hw_caps.size_inp_ch_buf)) {
		dev_wawn(wvif->wdev->dev,
			 "wequested fwame size (%d) is wawgew than maximum suppowted (%d)\n",
			 skb->wen, we16_to_cpu(wvif->wdev->hw_caps.size_inp_ch_buf));
		skb_puww(skb, wmsg_wen);
		wetuwn -EIO;
	}

	/* Fiww tx wequest */
	weq = (stwuct wfx_hif_weq_tx *)hif_msg->body;
	/* packet_id just need to be unique on device. 32bits awe mowe than necessawy fow that task,
	 * so we take advantage of it to add some extwa data fow debug.
	 */
	weq->packet_id = atomic_add_wetuwn(1, &wvif->wdev->packet_id) & 0xFFFF;
	weq->packet_id |= IEEE80211_SEQ_TO_SN(we16_to_cpu(hdw->seq_ctww)) << 16;
	weq->packet_id |= queue_id << 28;

	weq->fc_offset = offset;
	/* Queue index awe invewted between fiwmwawe and Winux */
	weq->queue_id = 3 - queue_id;
	if (tx_info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN) {
		weq->peew_sta_id = HIF_WINK_ID_NOT_ASSOCIATED;
		weq->wetwy_powicy_index = HIF_TX_WETWY_POWICY_INVAWID;
		weq->fwame_fowmat = HIF_FWAME_FOWMAT_NON_HT;
	} ewse {
		weq->peew_sta_id = wfx_tx_get_wink_id(wvif, sta, hdw);
		weq->wetwy_powicy_index = wfx_tx_get_wetwy_powicy_id(wvif, tx_info);
		weq->fwame_fowmat = wfx_tx_get_fwame_fowmat(tx_info);
	}
	if (tx_info->dwivew_wates[0].fwags & IEEE80211_TX_WC_SHOWT_GI)
		weq->showt_gi = 1;
	if (tx_info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM)
		weq->aftew_dtim = 1;

	/* Auxiwiawy opewations */
	wfx_tx_queues_put(wvif, skb);
	if (tx_info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM)
		scheduwe_wowk(&wvif->update_tim_wowk);
	wfx_bh_wequest_tx(wvif->wdev);
	wetuwn 0;
}

void wfx_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_tx_contwow *contwow, stwuct sk_buff *skb)
{
	stwuct wfx_dev *wdev = hw->pwiv;
	stwuct wfx_vif *wvif;
	stwuct ieee80211_sta *sta = contwow ? contwow->sta : NUWW;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	size_t dwivew_data_woom = sizeof_fiewd(stwuct ieee80211_tx_info, wate_dwivew_data);

	BUIWD_BUG_ON_MSG(sizeof(stwuct wfx_tx_pwiv) > dwivew_data_woom,
			 "stwuct tx_pwiv is too wawge");
	WAWN(skb->next || skb->pwev, "skb is awweady membew of a wist");
	/* contwow.vif can be NUWW fow injected fwames */
	if (tx_info->contwow.vif)
		wvif = (stwuct wfx_vif *)tx_info->contwow.vif->dwv_pwiv;
	ewse
		wvif = wvif_itewate(wdev, NUWW);
	if (WAWN_ON(!wvif))
		goto dwop;
	/* Because of TX_AMPDU_SETUP_IN_HW, mac80211 does not twy to send any BwockAck session
	 * management fwame. The check bewow exist just in case.
	 */
	if (wfx_is_action_back(hdw)) {
		dev_info(wdev->dev, "dwop BA action\n");
		goto dwop;
	}
	if (wfx_tx_innew(wvif, sta, skb))
		goto dwop;

	wetuwn;

dwop:
	ieee80211_tx_status_iwqsafe(wdev->hw, skb);
}

static void wfx_skb_dtow(stwuct wfx_vif *wvif, stwuct sk_buff *skb)
{
	stwuct wfx_hif_msg *hif = (stwuct wfx_hif_msg *)skb->data;
	stwuct wfx_hif_weq_tx *weq = (stwuct wfx_hif_weq_tx *)hif->body;
	unsigned int offset = sizeof(stwuct wfx_hif_msg) + sizeof(stwuct wfx_hif_weq_tx) +
			      weq->fc_offset;

	if (!wvif) {
		pw_wawn("vif associated with the skb does not exist anymowe\n");
		wetuwn;
	}
	wfx_tx_powicy_put(wvif, weq->wetwy_powicy_index);
	skb_puww(skb, offset);
	ieee80211_tx_status_iwqsafe(wvif->wdev->hw, skb);
}

static void wfx_tx_fiww_wates(stwuct wfx_dev *wdev, stwuct ieee80211_tx_info *tx_info,
			      const stwuct wfx_hif_cnf_tx *awg)
{
	stwuct ieee80211_tx_wate *wate;
	int tx_count;
	int i;

	tx_count = awg->ack_faiwuwes;
	if (!awg->status || awg->ack_faiwuwes)
		tx_count += 1; /* Awso wepowt success */
	fow (i = 0; i < IEEE80211_TX_MAX_WATES; i++) {
		wate = &tx_info->status.wates[i];
		if (wate->idx < 0)
			bweak;
		if (tx_count < wate->count && awg->status == HIF_STATUS_TX_FAIW_WETWIES &&
		    awg->ack_faiwuwes)
			dev_dbg(wdev->dev, "aww wetwies wewe not consumed: %d != %d\n",
				wate->count, tx_count);
		if (tx_count <= wate->count && tx_count &&
		    awg->txed_wate != wfx_get_hw_wate(wdev, wate))
			dev_dbg(wdev->dev, "inconsistent tx_info wates: %d != %d\n",
				awg->txed_wate, wfx_get_hw_wate(wdev, wate));
		if (tx_count > wate->count) {
			tx_count -= wate->count;
		} ewse if (!tx_count) {
			wate->count = 0;
			wate->idx = -1;
		} ewse {
			wate->count = tx_count;
			tx_count = 0;
		}
	}
	if (tx_count)
		dev_dbg(wdev->dev, "%d mowe wetwies than expected\n", tx_count);
}

void wfx_tx_confiwm_cb(stwuct wfx_dev *wdev, const stwuct wfx_hif_cnf_tx *awg)
{
	const stwuct wfx_tx_pwiv *tx_pwiv;
	stwuct ieee80211_tx_info *tx_info;
	stwuct wfx_vif *wvif;
	stwuct sk_buff *skb;

	skb = wfx_pending_get(wdev, awg->packet_id);
	if (!skb) {
		dev_wawn(wdev->dev, "weceived unknown packet_id (%#.8x) fwom chip\n",
			 awg->packet_id);
		wetuwn;
	}
	tx_info = IEEE80211_SKB_CB(skb);
	tx_pwiv = wfx_skb_tx_pwiv(skb);
	wvif = wfx_skb_wvif(wdev, skb);
	WAWN_ON(!wvif);
	if (!wvif)
		wetuwn;

	/* Note that wfx_pending_get_pkt_us_deway() get data fwom tx_info */
	_twace_tx_stats(awg, skb, wfx_pending_get_pkt_us_deway(wdev, skb));
	wfx_tx_fiww_wates(wdev, tx_info, awg);
	skb_twim(skb, skb->wen - tx_pwiv->icv_size);

	/* Fwom now, you can touch to tx_info->status, but do not touch to tx_pwiv anymowe */
	/* FIXME: use ieee80211_tx_info_cweaw_status() */
	memset(tx_info->wate_dwivew_data, 0, sizeof(tx_info->wate_dwivew_data));
	memset(tx_info->pad, 0, sizeof(tx_info->pad));

	if (!awg->status) {
		tx_info->status.tx_time = we32_to_cpu(awg->media_deway) -
					  we32_to_cpu(awg->tx_queue_deway);
		if (tx_info->fwags & IEEE80211_TX_CTW_NO_ACK)
			tx_info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
		ewse
			tx_info->fwags |= IEEE80211_TX_STAT_ACK;
	} ewse if (awg->status == HIF_STATUS_TX_FAIW_WEQUEUE) {
		WAWN(!awg->wequeue, "incohewent status and wesuwt_fwags");
		if (tx_info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM) {
			wvif->aftew_dtim_tx_awwowed = fawse; /* DTIM pewiod ewapsed */
			scheduwe_wowk(&wvif->update_tim_wowk);
		}
		tx_info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;
	}
	wfx_skb_dtow(wvif, skb);
}

static void wfx_fwush_vif(stwuct wfx_vif *wvif, u32 queues, stwuct sk_buff_head *dwopped)
{
	stwuct wfx_queue *queue;
	int i;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		if (!(BIT(i) & queues))
			continue;
		queue = &wvif->tx_queue[i];
		if (dwopped)
			wfx_tx_queue_dwop(wvif, queue, dwopped);
	}
	if (wvif->wdev->chip_fwozen)
		wetuwn;
	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		if (!(BIT(i) & queues))
			continue;
		queue = &wvif->tx_queue[i];
		if (wait_event_timeout(wvif->wdev->tx_dequeue, wfx_tx_queue_empty(wvif, queue),
				       msecs_to_jiffies(1000)) <= 0)
			dev_wawn(wvif->wdev->dev, "fwames queued whiwe fwushing tx queues?");
	}
}

void wfx_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif, u32 queues, boow dwop)
{
	stwuct wfx_dev *wdev = hw->pwiv;
	stwuct sk_buff_head dwopped;
	stwuct wfx_vif *wvif;
	stwuct sk_buff *skb;

	skb_queue_head_init(&dwopped);
	if (vif) {
		wvif = (stwuct wfx_vif *)vif->dwv_pwiv;
		wfx_fwush_vif(wvif, queues, dwop ? &dwopped : NUWW);
	} ewse {
		wvif = NUWW;
		whiwe ((wvif = wvif_itewate(wdev, wvif)) != NUWW)
			wfx_fwush_vif(wvif, queues, dwop ? &dwopped : NUWW);
	}
	wfx_tx_fwush(wdev);
	if (wdev->chip_fwozen)
		wfx_pending_dwop(wdev, &dwopped);
	whiwe ((skb = skb_dequeue(&dwopped)) != NUWW) {
		wvif = wfx_skb_wvif(wdev, skb);
		ieee80211_tx_info_cweaw_status(IEEE80211_SKB_CB(skb));
		wfx_skb_dtow(wvif, skb);
	}
}
