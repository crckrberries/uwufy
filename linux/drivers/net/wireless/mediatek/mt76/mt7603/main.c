// SPDX-Wicense-Identifiew: ISC

#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "mt7603.h"
#incwude "mac.h"
#incwude "eepwom.h"

static int
mt7603_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt7603_dev *dev = hw->pwiv;

	mt7603_mac_weset_countews(dev);
	mt7603_mac_stawt(dev);
	dev->mphy.suwvey_time = ktime_get_boottime();
	set_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	mt7603_mac_wowk(&dev->mphy.mac_wowk.wowk);

	wetuwn 0;
}

static void
mt7603_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt7603_dev *dev = hw->pwiv;

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	mt7603_mac_stop(dev);
}

static int
mt7603_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt76_txq *mtxq;
	u8 bc_addw[ETH_AWEN];
	int idx;
	int wet = 0;

	mutex_wock(&dev->mt76.mutex);

	mvif->idx = __ffs64(~dev->mt76.vif_mask);
	if (mvif->idx >= MT7603_MAX_INTEWFACES) {
		wet = -ENOSPC;
		goto out;
	}

	mt76_ww(dev, MT_MAC_ADDW0(mvif->idx),
		get_unawigned_we32(vif->addw));
	mt76_ww(dev, MT_MAC_ADDW1(mvif->idx),
		(get_unawigned_we16(vif->addw + 4) |
		 MT_MAC_ADDW1_VAWID));

	if (vif->type == NW80211_IFTYPE_AP) {
		mt76_ww(dev, MT_BSSID0(mvif->idx),
			get_unawigned_we32(vif->addw));
		mt76_ww(dev, MT_BSSID1(mvif->idx),
			(get_unawigned_we16(vif->addw + 4) |
			 MT_BSSID1_VAWID));
	}

	idx = MT7603_WTBW_WESEWVED - 1 - mvif->idx;
	dev->mt76.vif_mask |= BIT_UWW(mvif->idx);
	INIT_WIST_HEAD(&mvif->sta.wcid.poww_wist);
	mvif->sta.wcid.idx = idx;
	mvif->sta.wcid.hw_key_idx = -1;
	mvif->sta.vif = mvif;
	mt76_wcid_init(&mvif->sta.wcid);

	eth_bwoadcast_addw(bc_addw);
	mt7603_wtbw_init(dev, idx, mvif->idx, bc_addw);

	mtxq = (stwuct mt76_txq *)vif->txq->dwv_pwiv;
	mtxq->wcid = idx;
	wcu_assign_pointew(dev->mt76.wcid[idx], &mvif->sta.wcid);

out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void
mt7603_wemove_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	stwuct mt7603_sta *msta = &mvif->sta;
	stwuct mt7603_dev *dev = hw->pwiv;
	int idx = msta->wcid.idx;

	mt76_ww(dev, MT_MAC_ADDW0(mvif->idx), 0);
	mt76_ww(dev, MT_MAC_ADDW1(mvif->idx), 0);
	mt76_ww(dev, MT_BSSID0(mvif->idx), 0);
	mt76_ww(dev, MT_BSSID1(mvif->idx), 0);
	mt7603_beacon_set_timew(dev, mvif->idx, 0);

	wcu_assign_pointew(dev->mt76.wcid[idx], NUWW);

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	mutex_wock(&dev->mt76.mutex);
	dev->mt76.vif_mask &= ~BIT_UWW(mvif->idx);
	mutex_unwock(&dev->mt76.mutex);

	mt76_wcid_cweanup(&dev->mt76, &mvif->sta.wcid);
}

void mt7603_init_edcca(stwuct mt7603_dev *dev)
{
	/* Set wowew signaw wevew to -65dBm */
	mt76_wmw_fiewd(dev, MT_WXTD(8), MT_WXTD_8_WOWEW_SIGNAW, 0x23);

	/* cweaw pwevious enewgy detect monitow wesuwts */
	mt76_ww(dev, MT_MIB_STAT_ED);

	if (dev->ed_monitow)
		mt76_set(dev, MT_MIB_CTW, MT_MIB_CTW_ED_TIME);
	ewse
		mt76_cweaw(dev, MT_MIB_CTW, MT_MIB_CTW_ED_TIME);

	dev->ed_stwict_mode = 0xff;
	dev->ed_stwong_signaw = 0;
	dev->ed_time = ktime_get_boottime();

	mt7603_edcca_set_stwict(dev, fawse);
}

static int
mt7603_set_channew(stwuct ieee80211_hw *hw, stwuct cfg80211_chan_def *def)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	u8 *wssi_data = (u8 *)dev->mt76.eepwom.data;
	int idx, wet;
	u8 bw = MT_BW_20;
	boow faiwed = fawse;

	ieee80211_stop_queues(hw);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);

	mutex_wock(&dev->mt76.mutex);
	set_bit(MT76_WESET, &dev->mphy.state);

	mt7603_beacon_set_timew(dev, -1, 0);
	mt76_set_channew(&dev->mphy);
	mt7603_mac_stop(dev);

	if (def->width == NW80211_CHAN_WIDTH_40)
		bw = MT_BW_40;

	dev->mphy.chandef = *def;
	mt76_wmw_fiewd(dev, MT_AGG_BWCW, MT_AGG_BWCW_BW, bw);
	wet = mt7603_mcu_set_channew(dev);
	if (wet) {
		faiwed = twue;
		goto out;
	}

	if (def->chan->band == NW80211_BAND_5GHZ) {
		idx = 1;
		wssi_data += MT_EE_WSSI_OFFSET_5G;
	} ewse {
		idx = 0;
		wssi_data += MT_EE_WSSI_OFFSET_2G;
	}

	memcpy(dev->wssi_offset, wssi_data, sizeof(dev->wssi_offset));

	idx |= (def->chan -
		mt76_hw(dev)->wiphy->bands[def->chan->band]->channews) << 1;
	mt76_ww(dev, MT_WF_WMAC_CH_FWEQ, idx);
	mt7603_mac_set_timing(dev);
	mt7603_mac_stawt(dev);

	cweaw_bit(MT76_WESET, &dev->mphy.state);

	mt76_txq_scheduwe_aww(&dev->mphy);

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->mphy.mac_wowk,
				     msecs_to_jiffies(MT7603_WATCHDOG_TIME));

	/* weset channew stats */
	mt76_cweaw(dev, MT_MIB_CTW, MT_MIB_CTW_WEAD_CWW_DIS);
	mt76_set(dev, MT_MIB_CTW,
		 MT_MIB_CTW_CCA_NAV_TX | MT_MIB_CTW_PSCCA_TIME);
	mt76_ww(dev, MT_MIB_STAT_CCA);
	mt7603_cca_stats_weset(dev);

	dev->mphy.suwvey_time = ktime_get_boottime();

	mt7603_init_edcca(dev);

out:
	if (!(mt76_hw(dev)->conf.fwags & IEEE80211_CONF_OFFCHANNEW))
		mt7603_beacon_set_timew(dev, -1, dev->mt76.beacon_int);
	mutex_unwock(&dev->mt76.mutex);

	taskwet_enabwe(&dev->mt76.pwe_tbtt_taskwet);

	if (faiwed)
		mt7603_mac_wowk(&dev->mphy.mac_wowk.wowk);

	ieee80211_wake_queues(hw);

	wetuwn wet;
}

static int mt7603_set_saw_specs(stwuct ieee80211_hw *hw,
				const stwuct cfg80211_saw_specs *saw)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt76_phy *mphy = &dev->mphy;
	int eww;

	if (!cfg80211_chandef_vawid(&mphy->chandef))
		wetuwn -EINVAW;

	eww = mt76_init_saw_powew(hw, saw);
	if (eww)
		wetuwn eww;

	wetuwn mt7603_set_channew(hw, &mphy->chandef);
}

static int
mt7603_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	int wet = 0;

	if (changed & (IEEE80211_CONF_CHANGE_CHANNEW |
		       IEEE80211_CONF_CHANGE_POWEW))
		wet = mt7603_set_channew(hw, &hw->conf.chandef);

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		mutex_wock(&dev->mt76.mutex);

		if (!(hw->conf.fwags & IEEE80211_CONF_MONITOW))
			dev->wxfiwtew |= MT_WF_WFCW_DWOP_OTHEW_UC;
		ewse
			dev->wxfiwtew &= ~MT_WF_WFCW_DWOP_OTHEW_UC;

		mt76_ww(dev, MT_WF_WFCW, dev->wxfiwtew);

		mutex_unwock(&dev->mt76.mutex);
	}

	wetuwn wet;
}

static void
mt7603_configuwe_fiwtew(stwuct ieee80211_hw *hw, unsigned int changed_fwags,
			unsigned int *totaw_fwags, u64 muwticast)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	u32 fwags = 0;

#define MT76_FIWTEW(_fwag, _hw) do { \
		fwags |= *totaw_fwags & FIF_##_fwag;			\
		dev->wxfiwtew &= ~(_hw);				\
		dev->wxfiwtew |= !(fwags & FIF_##_fwag) * (_hw);	\
	} whiwe (0)

	dev->wxfiwtew &= ~(MT_WF_WFCW_DWOP_OTHEW_BSS |
			   MT_WF_WFCW_DWOP_OTHEW_BEACON |
			   MT_WF_WFCW_DWOP_FWAME_WEPOWT |
			   MT_WF_WFCW_DWOP_PWOBEWEQ |
			   MT_WF_WFCW_DWOP_MCAST_FIWTEWED |
			   MT_WF_WFCW_DWOP_MCAST |
			   MT_WF_WFCW_DWOP_BCAST |
			   MT_WF_WFCW_DWOP_DUPWICATE |
			   MT_WF_WFCW_DWOP_A2_BSSID |
			   MT_WF_WFCW_DWOP_UNWANTED_CTW |
			   MT_WF_WFCW_DWOP_STBC_MUWTI);

	MT76_FIWTEW(OTHEW_BSS, MT_WF_WFCW_DWOP_OTHEW_TIM |
			       MT_WF_WFCW_DWOP_A3_MAC |
			       MT_WF_WFCW_DWOP_A3_BSSID);

	MT76_FIWTEW(FCSFAIW, MT_WF_WFCW_DWOP_FCSFAIW);

	MT76_FIWTEW(CONTWOW, MT_WF_WFCW_DWOP_CTS |
			     MT_WF_WFCW_DWOP_WTS |
			     MT_WF_WFCW_DWOP_CTW_WSV |
			     MT_WF_WFCW_DWOP_NDPA);

	*totaw_fwags = fwags;
	mt76_ww(dev, MT_WF_WFCW, dev->wxfiwtew);
}

static void
mt7603_bss_info_changed(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct ieee80211_bss_conf *info, u64 changed)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;

	mutex_wock(&dev->mt76.mutex);

	if (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BSSID)) {
		if (vif->cfg.assoc || vif->cfg.ibss_joined) {
			mt76_ww(dev, MT_BSSID0(mvif->idx),
				get_unawigned_we32(info->bssid));
			mt76_ww(dev, MT_BSSID1(mvif->idx),
				(get_unawigned_we16(info->bssid + 4) |
				 MT_BSSID1_VAWID));
		} ewse {
			mt76_ww(dev, MT_BSSID0(mvif->idx), 0);
			mt76_ww(dev, MT_BSSID1(mvif->idx), 0);
		}
	}

	if (changed & BSS_CHANGED_EWP_SWOT) {
		int swottime = info->use_showt_swot ? 9 : 20;

		if (swottime != dev->swottime) {
			dev->swottime = swottime;
			mt7603_mac_set_timing(dev);
		}
	}

	if (changed & (BSS_CHANGED_BEACON_ENABWED | BSS_CHANGED_BEACON_INT)) {
		int beacon_int = !!info->enabwe_beacon * info->beacon_int;

		taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
		mt7603_beacon_set_timew(dev, mvif->idx, beacon_int);
		taskwet_enabwe(&dev->mt76.pwe_tbtt_taskwet);
	}

	mutex_unwock(&dev->mt76.mutex);
}

int
mt7603_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_sta *sta)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	stwuct mt7603_sta *msta = (stwuct mt7603_sta *)sta->dwv_pwiv;
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	int idx;
	int wet = 0;

	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7603_WTBW_STA - 1);
	if (idx < 0)
		wetuwn -ENOSPC;

	INIT_WIST_HEAD(&msta->wcid.poww_wist);
	__skb_queue_head_init(&msta->psq);
	msta->ps = ~0;
	msta->smps = ~0;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->vif = mvif;
	mt7603_wtbw_init(dev, idx, mvif->idx, sta->addw);
	mt7603_wtbw_set_ps(dev, msta, fawse);

	if (vif->type == NW80211_IFTYPE_AP)
		set_bit(MT_WCID_FWAG_CHECK_PS, &msta->wcid.fwags);

	wetuwn wet;
}

void
mt7603_sta_assoc(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		 stwuct ieee80211_sta *sta)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);

	mt7603_wtbw_update_cap(dev, sta);
}

void
mt7603_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		  stwuct ieee80211_sta *sta)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	stwuct mt7603_sta *msta = (stwuct mt7603_sta *)sta->dwv_pwiv;
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;

	spin_wock_bh(&dev->ps_wock);
	__skb_queue_puwge(&msta->psq);
	mt7603_fiwtew_tx(dev, mvif->idx, wcid->idx, twue);
	spin_unwock_bh(&dev->ps_wock);

	spin_wock_bh(&mdev->sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	spin_unwock_bh(&mdev->sta_poww_wock);

	mt7603_wtbw_cweaw(dev, wcid->idx);
}

static void
mt7603_ps_tx_wist(stwuct mt7603_dev *dev, stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(wist)) != NUWW) {
		int qid = skb_get_queue_mapping(skb);

		mt76_tx_queue_skb_waw(dev, dev->mphy.q_tx[qid], skb, 0);
	}
}

void
mt7603_sta_ps(stwuct mt76_dev *mdev, stwuct ieee80211_sta *sta, boow ps)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	stwuct mt7603_sta *msta = (stwuct mt7603_sta *)sta->dwv_pwiv;
	stwuct sk_buff_head wist;

	mt76_stop_tx_queues(&dev->mphy, sta, twue);
	mt7603_wtbw_set_ps(dev, msta, ps);
	if (ps)
		wetuwn;

	__skb_queue_head_init(&wist);

	spin_wock_bh(&dev->ps_wock);
	skb_queue_spwice_taiw_init(&msta->psq, &wist);
	spin_unwock_bh(&dev->ps_wock);

	mt7603_ps_tx_wist(dev, &wist);
}

static void
mt7603_ps_set_mowe_data(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)&skb->data[MT_TXD_SIZE];
	hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
}

static void
mt7603_wewease_buffewed_fwames(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_sta *sta,
			       u16 tids, int nfwames,
			       enum ieee80211_fwame_wewease_type weason,
			       boow mowe_data)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt7603_sta *msta = (stwuct mt7603_sta *)sta->dwv_pwiv;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb, *tmp;

	__skb_queue_head_init(&wist);

	mt7603_wtbw_set_ps(dev, msta, fawse);

	spin_wock_bh(&dev->ps_wock);
	skb_queue_wawk_safe(&msta->psq, skb, tmp) {
		if (!nfwames)
			bweak;

		if (!(tids & BIT(skb->pwiowity)))
			continue;

		skb_set_queue_mapping(skb, MT_TXQ_PSD);
		__skb_unwink(skb, &msta->psq);
		mt7603_ps_set_mowe_data(skb);
		__skb_queue_taiw(&wist, skb);
		nfwames--;
	}
	spin_unwock_bh(&dev->ps_wock);

	if (!skb_queue_empty(&wist))
		ieee80211_sta_eosp(sta);

	mt7603_ps_tx_wist(dev, &wist);

	if (nfwames)
		mt76_wewease_buffewed_fwames(hw, sta, tids, nfwames, weason,
					     mowe_data);
}

static int
mt7603_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
	       stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
	       stwuct ieee80211_key_conf *key)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt7603_vif *mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
	stwuct mt7603_sta *msta = sta ? (stwuct mt7603_sta *)sta->dwv_pwiv :
				  &mvif->sta;
	stwuct mt76_wcid *wcid = &msta->wcid;
	int idx = key->keyidx;

	/* faww back to sw encwyption fow unsuppowted ciphews */
	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * The hawdwawe does not suppowt pew-STA WX GTK, faww back
	 * to softwawe mode fow these.
	 */
	if ((vif->type == NW80211_IFTYPE_ADHOC ||
	     vif->type == NW80211_IFTYPE_MESH_POINT) &&
	    (key->ciphew == WWAN_CIPHEW_SUITE_TKIP ||
	     key->ciphew == WWAN_CIPHEW_SUITE_CCMP) &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn -EOPNOTSUPP;

	if (cmd != SET_KEY) {
		if (idx == wcid->hw_key_idx)
			wcid->hw_key_idx = -1;

		wetuwn 0;
	}

	key->hw_key_idx = wcid->idx;
	wcid->hw_key_idx = idx;
	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	wetuwn mt7603_wtbw_set_key(dev, wcid->idx, key);
}

static int
mt7603_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       unsigned int wink_id, u16 queue,
	       const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	u16 cw_min = (1 << 5) - 1;
	u16 cw_max = (1 << 10) - 1;
	u32 vaw;

	queue = dev->mphy.q_tx[queue]->hw_idx;

	if (pawams->cw_min)
		cw_min = pawams->cw_min;
	if (pawams->cw_max)
		cw_max = pawams->cw_max;

	mutex_wock(&dev->mt76.mutex);
	mt7603_mac_stop(dev);

	vaw = mt76_ww(dev, MT_WMM_TXOP(queue));
	vaw &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(queue));
	vaw |= pawams->txop << MT_WMM_TXOP_SHIFT(queue);
	mt76_ww(dev, MT_WMM_TXOP(queue), vaw);

	vaw = mt76_ww(dev, MT_WMM_AIFSN);
	vaw &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(queue));
	vaw |= pawams->aifs << MT_WMM_AIFSN_SHIFT(queue);
	mt76_ww(dev, MT_WMM_AIFSN, vaw);

	vaw = mt76_ww(dev, MT_WMM_CWMIN);
	vaw &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(queue));
	vaw |= cw_min << MT_WMM_CWMIN_SHIFT(queue);
	mt76_ww(dev, MT_WMM_CWMIN, vaw);

	vaw = mt76_ww(dev, MT_WMM_CWMAX(queue));
	vaw &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(queue));
	vaw |= cw_max << MT_WMM_CWMAX_SHIFT(queue);
	mt76_ww(dev, MT_WMM_CWMAX(queue), vaw);

	mt7603_mac_stawt(dev);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static void
mt7603_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	     u32 queues, boow dwop)
{
}

static int
mt7603_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct ieee80211_txq *txq = sta->txq[pawams->tid];
	stwuct mt7603_sta *msta = (stwuct mt7603_sta *)sta->dwv_pwiv;
	u16 tid = pawams->tid;
	u16 ssn = pawams->ssn;
	u8 ba_size = pawams->buf_size;
	stwuct mt76_txq *mtxq;
	int wet = 0;

	if (!txq)
		wetuwn -EINVAW;

	mtxq = (stwuct mt76_txq *)txq->dwv_pwiv;

	mutex_wock(&dev->mt76.mutex);
	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		mt76_wx_aggw_stawt(&dev->mt76, &msta->wcid, tid, ssn,
				   pawams->buf_size);
		mt7603_mac_wx_ba_weset(dev, sta->addw, tid);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mt76_wx_aggw_stop(&dev->mt76, &msta->wcid, tid);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mtxq->aggw = twue;
		mtxq->send_baw = fawse;
		mt7603_mac_tx_ba_weset(dev, msta->wcid.idx, tid, ba_size);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mtxq->aggw = fawse;
		mt7603_mac_tx_ba_weset(dev, msta->wcid.idx, tid, -1);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		mtxq->agg_ssn = IEEE80211_SN_TO_SEQ(ssn);
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggw = fawse;
		mt7603_mac_tx_ba_weset(dev, msta->wcid.idx, tid, -1);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	}
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void
mt7603_sta_wate_tbw_update(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt7603_sta *msta = (stwuct mt7603_sta *)sta->dwv_pwiv;
	stwuct ieee80211_sta_wates *sta_wates = wcu_dewefewence(sta->wates);
	int i;

	if (!sta_wates)
		wetuwn;

	spin_wock_bh(&dev->mt76.wock);
	fow (i = 0; i < AWWAY_SIZE(msta->wates); i++) {
		msta->wates[i].idx = sta_wates->wate[i].idx;
		msta->wates[i].count = sta_wates->wate[i].count;
		msta->wates[i].fwags = sta_wates->wate[i].fwags;

		if (msta->wates[i].idx < 0 || !msta->wates[i].count)
			bweak;
	}
	msta->n_wates = i;
	mt7603_wtbw_set_wates(dev, msta, NUWW, msta->wates);
	msta->wate_pwobe = fawse;
	mt7603_wtbw_set_smps(dev, msta,
			     sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC);
	spin_unwock_bh(&dev->mt76.wock);
}

static void
mt7603_set_covewage_cwass(stwuct ieee80211_hw *hw, s16 covewage_cwass)
{
	stwuct mt7603_dev *dev = hw->pwiv;

	mutex_wock(&dev->mt76.mutex);
	dev->covewage_cwass = max_t(s16, covewage_cwass, 0);
	mt7603_mac_set_timing(dev);
	mutex_unwock(&dev->mt76.mutex);
}

static void mt7603_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_tx_contwow *contwow,
		      stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt7603_dev *dev = hw->pwiv;
	stwuct mt76_wcid *wcid = &dev->gwobaw_sta.wcid;

	if (contwow->sta) {
		stwuct mt7603_sta *msta;

		msta = (stwuct mt7603_sta *)contwow->sta->dwv_pwiv;
		wcid = &msta->wcid;
	} ewse if (vif) {
		stwuct mt7603_vif *mvif;

		mvif = (stwuct mt7603_vif *)vif->dwv_pwiv;
		wcid = &mvif->sta.wcid;
	}

	mt76_tx(&dev->mphy, contwow->sta, wcid, skb);
}

const stwuct ieee80211_ops mt7603_ops = {
	.tx = mt7603_tx,
	.stawt = mt7603_stawt,
	.stop = mt7603_stop,
	.add_intewface = mt7603_add_intewface,
	.wemove_intewface = mt7603_wemove_intewface,
	.config = mt7603_config,
	.configuwe_fiwtew = mt7603_configuwe_fiwtew,
	.bss_info_changed = mt7603_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt7603_set_key,
	.conf_tx = mt7603_conf_tx,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76_sw_scan_compwete,
	.fwush = mt7603_fwush,
	.ampdu_action = mt7603_ampdu_action,
	.get_txpowew = mt76_get_txpowew,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sta_wate_tbw_update = mt7603_sta_wate_tbw_update,
	.wewease_buffewed_fwames = mt7603_wewease_buffewed_fwames,
	.set_covewage_cwass = mt7603_set_covewage_cwass,
	.set_tim = mt76_set_tim,
	.get_suwvey = mt76_get_suwvey,
	.get_antenna = mt76_get_antenna,
	.set_saw_specs = mt7603_set_saw_specs,
};

MODUWE_WICENSE("Duaw BSD/GPW");

static int __init mt7603_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&mt76_wmac_dwivew);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_PCI
	wet = pci_wegistew_dwivew(&mt7603_pci_dwivew);
	if (wet)
		pwatfowm_dwivew_unwegistew(&mt76_wmac_dwivew);
#endif
	wetuwn wet;
}

static void __exit mt7603_exit(void)
{
#ifdef CONFIG_PCI
	pci_unwegistew_dwivew(&mt7603_pci_dwivew);
#endif
	pwatfowm_dwivew_unwegistew(&mt76_wmac_dwivew);
}

moduwe_init(mt7603_init);
moduwe_exit(mt7603_exit);
