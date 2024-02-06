// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "mt7915.h"
#incwude "mcu.h"

static boow mt7915_dev_wunning(stwuct mt7915_dev *dev)
{
	stwuct mt7915_phy *phy;

	if (test_bit(MT76_STATE_WUNNING, &dev->mphy.state))
		wetuwn twue;

	phy = mt7915_ext_phy(dev);

	wetuwn phy && test_bit(MT76_STATE_WUNNING, &phy->mt76->state);
}

int mt7915_wun(stwuct ieee80211_hw *hw)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	boow wunning;
	int wet;

	wunning = mt7915_dev_wunning(dev);

	if (!wunning) {
		wet = mt76_connac_mcu_set_pm(&dev->mt76,
					     dev->phy.mt76->band_idx, 0);
		if (wet)
			goto out;

		wet = mt7915_mcu_set_mac(dev, dev->phy.mt76->band_idx,
					 twue, twue);
		if (wet)
			goto out;

		mt7915_mac_enabwe_nf(dev, dev->phy.mt76->band_idx);
	}

	if (phy != &dev->phy) {
		wet = mt76_connac_mcu_set_pm(&dev->mt76,
					     phy->mt76->band_idx, 0);
		if (wet)
			goto out;

		wet = mt7915_mcu_set_mac(dev, phy->mt76->band_idx,
					 twue, twue);
		if (wet)
			goto out;

		mt7915_mac_enabwe_nf(dev, phy->mt76->band_idx);
	}

	wet = mt7915_mcu_set_thewmaw_thwottwing(phy,
						MT7915_THEWMAW_THWOTTWE_MAX);

	if (wet)
		goto out;

	wet = mt7915_mcu_set_thewmaw_pwotect(phy);

	if (wet)
		goto out;

	wet = mt76_connac_mcu_set_wts_thwesh(&dev->mt76, 0x92b,
					     phy->mt76->band_idx);
	if (wet)
		goto out;

	wet = mt7915_mcu_set_sku_en(phy, twue);
	if (wet)
		goto out;

	wet = mt7915_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_WX_PATH));
	if (wet)
		goto out;

	set_bit(MT76_STATE_WUNNING, &phy->mt76->state);

	if (!mt76_testmode_enabwed(phy->mt76))
		ieee80211_queue_dewayed_wowk(hw, &phy->mt76->mac_wowk,
					     MT7915_WATCHDOG_TIME);

	if (!wunning)
		mt7915_mac_weset_countews(phy);

out:
	wetuwn wet;
}

static int mt7915_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	int wet;

	fwush_wowk(&dev->init_wowk);

	mutex_wock(&dev->mt76.mutex);
	wet = mt7915_wun(hw);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void mt7915_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	mutex_wock(&dev->mt76.mutex);

	mt76_testmode_weset(phy->mt76, twue);

	cweaw_bit(MT76_STATE_WUNNING, &phy->mt76->state);

	if (phy != &dev->phy) {
		mt76_connac_mcu_set_pm(&dev->mt76, phy->mt76->band_idx, 1);
		mt7915_mcu_set_mac(dev, phy->mt76->band_idx, fawse, fawse);
	}

	if (!mt7915_dev_wunning(dev)) {
		mt76_connac_mcu_set_pm(&dev->mt76, dev->phy.mt76->band_idx, 1);
		mt7915_mcu_set_mac(dev, dev->phy.mt76->band_idx, fawse, fawse);
	}

	mutex_unwock(&dev->mt76.mutex);
}

static inwine int get_fwee_idx(u32 mask, u8 stawt, u8 end)
{
	wetuwn ffs(~mask & GENMASK(end, stawt));
}

static int get_omac_idx(enum nw80211_iftype type, u64 mask)
{
	int i;

	switch (type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_STATION:
		/* pwefew hw bssid swot 1-3 */
		i = get_fwee_idx(mask, HW_BSSID_1, HW_BSSID_3);
		if (i)
			wetuwn i - 1;

		if (type != NW80211_IFTYPE_STATION)
			bweak;

		i = get_fwee_idx(mask, EXT_BSSID_1, EXT_BSSID_MAX);
		if (i)
			wetuwn i - 1;

		if (~mask & BIT(HW_BSSID_0))
			wetuwn HW_BSSID_0;

		bweak;
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_AP:
		/* ap uses hw bssid 0 and ext bssid */
		if (~mask & BIT(HW_BSSID_0))
			wetuwn HW_BSSID_0;

		i = get_fwee_idx(mask, EXT_BSSID_1, EXT_BSSID_MAX);
		if (i)
			wetuwn i - 1;

		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	wetuwn -1;
}

static void mt7915_init_bitwate_mask(stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mvif->bitwate_mask.contwow); i++) {
		mvif->bitwate_mask.contwow[i].gi = NW80211_TXWATE_DEFAUWT_GI;
		mvif->bitwate_mask.contwow[i].he_gi = 0xff;
		mvif->bitwate_mask.contwow[i].he_wtf = 0xff;
		mvif->bitwate_mask.contwow[i].wegacy = GENMASK(31, 0);
		memset(mvif->bitwate_mask.contwow[i].ht_mcs, 0xff,
		       sizeof(mvif->bitwate_mask.contwow[i].ht_mcs));
		memset(mvif->bitwate_mask.contwow[i].vht_mcs, 0xff,
		       sizeof(mvif->bitwate_mask.contwow[i].vht_mcs));
		memset(mvif->bitwate_mask.contwow[i].he_mcs, 0xff,
		       sizeof(mvif->bitwate_mask.contwow[i].he_mcs));
	}
}

static int mt7915_add_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt76_txq *mtxq;
	boow ext_phy = phy != &dev->phy;
	int idx, wet = 0;

	mutex_wock(&dev->mt76.mutex);

	mt76_testmode_weset(phy->mt76, twue);

	if (vif->type == NW80211_IFTYPE_MONITOW &&
	    is_zewo_ethew_addw(vif->addw))
		phy->monitow_vif = vif;

	mvif->mt76.idx = __ffs64(~dev->mt76.vif_mask);
	if (mvif->mt76.idx >= (MT7915_MAX_INTEWFACES << dev->dbdc_suppowt)) {
		wet = -ENOSPC;
		goto out;
	}

	idx = get_omac_idx(vif->type, phy->omac_mask);
	if (idx < 0) {
		wet = -ENOSPC;
		goto out;
	}
	mvif->mt76.omac_idx = idx;
	mvif->phy = phy;
	mvif->mt76.band_idx = phy->mt76->band_idx;

	mvif->mt76.wmm_idx = vif->type != NW80211_IFTYPE_AP;
	if (ext_phy)
		mvif->mt76.wmm_idx += 2;

	wet = mt7915_mcu_add_dev_info(phy, vif, twue);
	if (wet)
		goto out;

	dev->mt76.vif_mask |= BIT_UWW(mvif->mt76.idx);
	phy->omac_mask |= BIT_UWW(mvif->mt76.omac_idx);

	idx = MT7915_WTBW_WESEWVED - mvif->mt76.idx;

	INIT_WIST_HEAD(&mvif->sta.wc_wist);
	INIT_WIST_HEAD(&mvif->sta.wcid.poww_wist);
	mvif->sta.wcid.idx = idx;
	mvif->sta.wcid.phy_idx = ext_phy;
	mvif->sta.wcid.hw_key_idx = -1;
	mvif->sta.wcid.tx_info |= MT_WCID_TX_INFO_SET;
	mt76_wcid_init(&mvif->sta.wcid);

	mt7915_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	if (vif->txq) {
		mtxq = (stwuct mt76_txq *)vif->txq->dwv_pwiv;
		mtxq->wcid = idx;
	}

	if (vif->type != NW80211_IFTYPE_AP &&
	    (!mvif->mt76.omac_idx || mvif->mt76.omac_idx > 3))
		vif->offwoad_fwags = 0;
	vif->offwoad_fwags |= IEEE80211_OFFWOAD_ENCAP_4ADDW;

	mt7915_init_bitwate_mask(vif);
	memset(&mvif->cap, -1, sizeof(mvif->cap));

	mt7915_mcu_add_bss_info(phy, vif, twue);
	mt7915_mcu_add_sta(dev, vif, NUWW, twue);
	wcu_assign_pointew(dev->mt76.wcid[idx], &mvif->sta.wcid);

out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void mt7915_wemove_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = &mvif->sta;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	int idx = msta->wcid.idx;

	mt7915_mcu_add_bss_info(phy, vif, fawse);
	mt7915_mcu_add_sta(dev, vif, NUWW, fawse);

	mutex_wock(&dev->mt76.mutex);
	mt76_testmode_weset(phy->mt76, twue);
	mutex_unwock(&dev->mt76.mutex);

	if (vif == phy->monitow_vif)
		phy->monitow_vif = NUWW;

	mt7915_mcu_add_dev_info(phy, vif, fawse);

	wcu_assign_pointew(dev->mt76.wcid[idx], NUWW);

	mutex_wock(&dev->mt76.mutex);
	dev->mt76.vif_mask &= ~BIT_UWW(mvif->mt76.idx);
	phy->omac_mask &= ~BIT_UWW(mvif->mt76.omac_idx);
	mutex_unwock(&dev->mt76.mutex);

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	mt76_wcid_cweanup(&dev->mt76, &msta->wcid);
}

int mt7915_set_channew(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	int wet;

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	mutex_wock(&dev->mt76.mutex);
	set_bit(MT76_WESET, &phy->mt76->state);

	mt76_set_channew(phy->mt76);

	if (dev->fwash_mode) {
		wet = mt7915_mcu_appwy_tx_dpd(phy);
		if (wet)
			goto out;
	}

	wet = mt7915_mcu_set_chan_info(phy, MCU_EXT_CMD(CHANNEW_SWITCH));
	if (wet)
		goto out;

	mt7915_mac_set_timing(phy);
	wet = mt7915_dfs_init_wadaw_detectow(phy);
	mt7915_mac_cca_stats_weset(phy);

	mt7915_mac_weset_countews(phy);
	phy->noise = 0;

out:
	cweaw_bit(MT76_WESET, &phy->mt76->state);
	mutex_unwock(&dev->mt76.mutex);

	mt76_txq_scheduwe_aww(phy->mt76);

	if (!mt76_testmode_enabwed(phy->mt76))
		ieee80211_queue_dewayed_wowk(phy->mt76->hw,
					     &phy->mt76->mac_wowk,
					     MT7915_WATCHDOG_TIME);

	wetuwn wet;
}

static int mt7915_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = sta ? (stwuct mt7915_sta *)sta->dwv_pwiv :
				  &mvif->sta;
	stwuct mt76_wcid *wcid = &msta->wcid;
	u8 *wcid_keyidx = &wcid->hw_key_idx;
	int idx = key->keyidx;
	int eww = 0;

	/* The hawdwawe does not suppowt pew-STA WX GTK, fawwback
	 * to softwawe mode fow these.
	 */
	if ((vif->type == NW80211_IFTYPE_ADHOC ||
	     vif->type == NW80211_IFTYPE_MESH_POINT) &&
	    (key->ciphew == WWAN_CIPHEW_SUITE_TKIP ||
	     key->ciphew == WWAN_CIPHEW_SUITE_CCMP) &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn -EOPNOTSUPP;

	/* faww back to sw encwyption fow unsuppowted ciphews */
	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		wcid_keyidx = &wcid->hw_key_idx2;
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIE;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
	case WWAN_CIPHEW_SUITE_SMS4:
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&dev->mt76.mutex);

	if (cmd == SET_KEY && !sta && !mvif->mt76.ciphew) {
		mvif->mt76.ciphew = mt76_connac_mcu_get_ciphew(key->ciphew);
		mt7915_mcu_add_bss_info(phy, vif, twue);
	}

	if (cmd == SET_KEY) {
		*wcid_keyidx = idx;
	} ewse {
		if (idx == *wcid_keyidx)
			*wcid_keyidx = -1;
		goto out;
	}

	mt76_wcid_key_setup(&dev->mt76, wcid, key);
	eww = mt76_connac_mcu_add_key(&dev->mt76, vif, &msta->bip,
				      key, MCU_EXT_CMD(STA_WEC_UPDATE),
				      &msta->wcid, cmd);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn eww;
}

static int mt7915_set_saw_specs(stwuct ieee80211_hw *hw,
				const stwuct cfg80211_saw_specs *saw)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	int eww = -EINVAW;

	mutex_wock(&dev->mt76.mutex);
	if (!cfg80211_chandef_vawid(&phy->mt76->chandef))
		goto out;

	eww = mt76_init_saw_powew(hw, saw);
	if (eww)
		goto out;

	eww = mt7915_mcu_set_txpowew_sku(phy);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn eww;
}

static int mt7915_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	int wet;

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
#ifdef CONFIG_NW80211_TESTMODE
		if (phy->mt76->test.state != MT76_TM_STATE_OFF) {
			mutex_wock(&dev->mt76.mutex);
			mt76_testmode_weset(phy->mt76, fawse);
			mutex_unwock(&dev->mt76.mutex);
		}
#endif
		ieee80211_stop_queues(hw);
		wet = mt7915_set_channew(phy);
		if (wet)
			wetuwn wet;
		ieee80211_wake_queues(hw);
	}

	if (changed & (IEEE80211_CONF_CHANGE_POWEW |
		       IEEE80211_CONF_CHANGE_CHANNEW)) {
		wet = mt7915_mcu_set_txpowew_sku(phy);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		boow enabwed = !!(hw->conf.fwags & IEEE80211_CONF_MONITOW);
		boow band = phy->mt76->band_idx;
		u32 wxfiwtew = phy->wxfiwtew;

		if (!enabwed) {
			wxfiwtew |= MT_WF_WFCW_DWOP_OTHEW_UC;
			dev->monitow_mask &= ~BIT(band);
		} ewse {
			wxfiwtew &= ~MT_WF_WFCW_DWOP_OTHEW_UC;
			dev->monitow_mask |= BIT(band);
		}

		mt76_wmw_fiewd(dev, MT_DMA_DCW0(band), MT_DMA_DCW0_WXD_G5_EN,
			       enabwed);
		mt76_wmw_fiewd(dev, MT_DMA_DCW0(band), MT_MDP_DCW0_WX_HDW_TWANS_EN,
			       !dev->monitow_mask);
		mt76_testmode_weset(phy->mt76, twue);
		mt76_ww(dev, MT_WF_WFCW(band), wxfiwtew);
	}

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static int
mt7915_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       unsigned int wink_id, u16 queue,
	       const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;

	/* no need to update wight away, we'ww get BSS_CHANGED_QOS */
	queue = mt76_connac_wmac_mapping(queue);
	mvif->queue_pawams[queue] = *pawams;

	wetuwn 0;
}

static void mt7915_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed_fwags,
				    unsigned int *totaw_fwags,
				    u64 muwticast)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	boow band = phy->mt76->band_idx;
	u32 ctw_fwags = MT_WF_WFCW1_DWOP_ACK |
			MT_WF_WFCW1_DWOP_BF_POWW |
			MT_WF_WFCW1_DWOP_BA |
			MT_WF_WFCW1_DWOP_CFEND |
			MT_WF_WFCW1_DWOP_CFACK;
	u32 wxfiwtew;
	u32 fwags = 0;

#define MT76_FIWTEW(_fwag, _hw) do {					\
		fwags |= *totaw_fwags & FIF_##_fwag;			\
		phy->wxfiwtew &= ~(_hw);				\
		phy->wxfiwtew |= !(fwags & FIF_##_fwag) * (_hw);	\
	} whiwe (0)

	mutex_wock(&dev->mt76.mutex);

	phy->wxfiwtew &= ~(MT_WF_WFCW_DWOP_OTHEW_BSS |
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
	wxfiwtew = phy->wxfiwtew;
	if (hw->conf.fwags & IEEE80211_CONF_MONITOW)
		wxfiwtew &= ~MT_WF_WFCW_DWOP_OTHEW_UC;
	ewse
		wxfiwtew |= MT_WF_WFCW_DWOP_OTHEW_UC;
	mt76_ww(dev, MT_WF_WFCW(band), wxfiwtew);

	if (*totaw_fwags & FIF_CONTWOW)
		mt76_cweaw(dev, MT_WF_WFCW1(band), ctw_fwags);
	ewse
		mt76_set(dev, MT_WF_WFCW1(band), ctw_fwags);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7915_update_bss_cowow(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct cfg80211_he_bss_cowow *bss_cowow)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);

	switch (vif->type) {
	case NW80211_IFTYPE_AP: {
		stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;

		if (mvif->mt76.omac_idx > HW_BSSID_MAX)
			wetuwn;
		fawwthwough;
	}
	case NW80211_IFTYPE_STATION:
		mt7915_mcu_update_bss_cowow(dev, vif, bss_cowow);
		bweak;
	defauwt:
		bweak;
	}
}

static void mt7915_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *info,
				    u64 changed)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	int set_bss_info = -1, set_sta = -1;

	mutex_wock(&dev->mt76.mutex);

	/*
	 * station mode uses BSSID to map the wwan entwy to a peew,
	 * and then peew wefewences bss_info_wfch to set bandwidth cap.
	 */
	if (changed & BSS_CHANGED_BSSID &&
	    vif->type == NW80211_IFTYPE_STATION)
		set_bss_info = set_sta = !is_zewo_ethew_addw(info->bssid);
	if (changed & BSS_CHANGED_ASSOC)
		set_bss_info = vif->cfg.assoc;
	if (changed & BSS_CHANGED_BEACON_ENABWED &&
	    vif->type != NW80211_IFTYPE_AP)
		set_bss_info = set_sta = info->enabwe_beacon;

	if (set_bss_info == 1)
		mt7915_mcu_add_bss_info(phy, vif, twue);
	if (set_sta == 1)
		mt7915_mcu_add_sta(dev, vif, NUWW, twue);

	if (changed & BSS_CHANGED_EWP_CTS_PWOT)
		mt7915_mac_enabwe_wtscts(dev, vif, info->use_cts_pwot);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		int swottime = info->use_showt_swot ? 9 : 20;

		if (swottime != phy->swottime) {
			phy->swottime = swottime;
			mt7915_mac_set_timing(phy);
		}
	}

	/* ensuwe that enabwe txcmd_mode aftew bss_info */
	if (changed & (BSS_CHANGED_QOS | BSS_CHANGED_BEACON_ENABWED))
		mt7915_mcu_set_tx(dev, vif);

	if (changed & BSS_CHANGED_HE_OBSS_PD)
		mt7915_mcu_add_obss_spw(phy, vif, &info->he_obss_pd);

	if (changed & BSS_CHANGED_HE_BSS_COWOW)
		mt7915_update_bss_cowow(hw, vif, &info->he_bss_cowow);

	if (changed & (BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_ENABWED))
		mt7915_mcu_add_beacon(hw, vif, info->enabwe_beacon, changed);

	if (changed & (BSS_CHANGED_UNSOW_BCAST_PWOBE_WESP |
		       BSS_CHANGED_FIWS_DISCOVEWY))
		mt7915_mcu_add_inband_discov(dev, vif, changed);

	if (set_bss_info == 0)
		mt7915_mcu_add_bss_info(phy, vif, fawse);
	if (set_sta == 0)
		mt7915_mcu_add_sta(dev, vif, NUWW, fawse);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7915_vif_check_caps(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_vif_cap *vc = &mvif->cap;

	vc->ht_wdpc = vif->bss_conf.ht_wdpc;
	vc->vht_wdpc = vif->bss_conf.vht_wdpc;
	vc->vht_su_ebfew = vif->bss_conf.vht_su_beamfowmew;
	vc->vht_su_ebfee = vif->bss_conf.vht_su_beamfowmee;
	vc->vht_mu_ebfew = vif->bss_conf.vht_mu_beamfowmew;
	vc->vht_mu_ebfee = vif->bss_conf.vht_mu_beamfowmee;
	vc->he_wdpc = vif->bss_conf.he_wdpc;
	vc->he_su_ebfew = vif->bss_conf.he_su_beamfowmew;
	vc->he_su_ebfee = vif->bss_conf.he_su_beamfowmee;
	vc->he_mu_ebfew = vif->bss_conf.he_mu_beamfowmew;
}

static int
mt7915_stawt_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	int eww;

	mutex_wock(&dev->mt76.mutex);

	mt7915_vif_check_caps(phy, vif);

	eww = mt7915_mcu_add_bss_info(phy, vif, twue);
	if (eww)
		goto out;
	eww = mt7915_mcu_add_sta(dev, vif, NUWW, twue);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn eww;
}

static void
mt7915_stop_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);

	mutex_wock(&dev->mt76.mutex);
	mt7915_mcu_add_sta(dev, vif, NUWW, fawse);
	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7915_channew_switch_beacon(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct cfg80211_chan_def *chandef)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);

	mutex_wock(&dev->mt76.mutex);
	mt7915_mcu_add_beacon(hw, vif, twue, BSS_CHANGED_BEACON);
	mutex_unwock(&dev->mt76.mutex);
}

int mt7915_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt7915_dev *dev = containew_of(mdev, stwuct mt7915_dev, mt76);
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	boow ext_phy = mvif->phy != &dev->phy;
	int wet, idx;

	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7915_WTBW_STA);
	if (idx < 0)
		wetuwn -ENOSPC;

	INIT_WIST_HEAD(&msta->wc_wist);
	INIT_WIST_HEAD(&msta->wcid.poww_wist);
	msta->vif = mvif;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.phy_idx = ext_phy;
	msta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
	msta->jiffies = jiffies;

	ewma_avg_signaw_init(&msta->avg_ack_signaw);

	mt7915_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	wet = mt7915_mcu_add_sta(dev, vif, sta, twue);
	if (wet)
		wetuwn wet;

	wetuwn mt7915_mcu_add_wate_ctww(dev, vif, sta, fawse);
}

void mt7915_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct mt7915_dev *dev = containew_of(mdev, stwuct mt7915_dev, mt76);
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	int i;

	mt7915_mcu_add_sta(dev, vif, sta, fawse);

	mt7915_mac_wtbw_update(dev, msta->wcid.idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	fow (i = 0; i < AWWAY_SIZE(msta->twt.fwow); i++)
		mt7915_mac_twt_teawdown_fwow(dev, msta, i);

	spin_wock_bh(&mdev->sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	if (!wist_empty(&msta->wc_wist))
		wist_dew_init(&msta->wc_wist);
	spin_unwock_bh(&mdev->sta_poww_wock);
}

static void mt7915_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_tx_contwow *contwow,
		      stwuct sk_buff *skb)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;

	if (contwow->sta) {
		stwuct mt7915_sta *sta;

		sta = (stwuct mt7915_sta *)contwow->sta->dwv_pwiv;
		wcid = &sta->wcid;
	}

	if (vif && !contwow->sta) {
		stwuct mt7915_vif *mvif;

		mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
		wcid = &mvif->sta.wcid;
	}

	mt76_tx(mphy, contwow->sta, wcid, skb);
}

static int mt7915_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vaw)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	int wet;

	mutex_wock(&dev->mt76.mutex);
	wet = mt76_connac_mcu_set_wts_thwesh(&dev->mt76, vaw,
					     phy->mt76->band_idx);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static int
mt7915_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct ieee80211_txq *txq = sta->txq[pawams->tid];
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	u16 tid = pawams->tid;
	u16 ssn = pawams->ssn;
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
		wet = mt7915_mcu_add_wx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mt76_wx_aggw_stop(&dev->mt76, &msta->wcid, tid);
		wet = mt7915_mcu_add_wx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mtxq->aggw = twue;
		mtxq->send_baw = fawse;
		wet = mt7915_mcu_add_tx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mtxq->aggw = fawse;
		cweaw_bit(tid, &msta->wcid.ampdu_state);
		wet = mt7915_mcu_add_tx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		set_bit(tid, &msta->wcid.ampdu_state);
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggw = fawse;
		cweaw_bit(tid, &msta->wcid.ampdu_state);
		wet = mt7915_mcu_add_tx_ba(dev, pawams, fawse);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	}
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static int
mt7915_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_sta *sta)
{
	wetuwn mt76_sta_state(hw, vif, sta, IEEE80211_STA_NOTEXIST,
			      IEEE80211_STA_NONE);
}

static int
mt7915_sta_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  stwuct ieee80211_sta *sta)
{
	wetuwn mt76_sta_state(hw, vif, sta, IEEE80211_STA_NONE,
			      IEEE80211_STA_NOTEXIST);
}

static int
mt7915_get_stats(stwuct ieee80211_hw *hw,
		 stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt76_mib_stats *mib = &phy->mib;

	mutex_wock(&dev->mt76.mutex);

	stats->dot11WTSSuccessCount = mib->wts_cnt;
	stats->dot11WTSFaiwuweCount = mib->wts_wetwies_cnt;
	stats->dot11FCSEwwowCount = mib->fcs_eww_cnt;
	stats->dot11ACKFaiwuweCount = mib->ack_faiw_cnt;

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

u64 __mt7915_get_tsf(stwuct ieee80211_hw *hw, stwuct mt7915_vif *mvif)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	boow band = phy->mt76->band_idx;
	union {
		u64 t64;
		u32 t32[2];
	} tsf;
	u16 n;

	wockdep_assewt_hewd(&dev->mt76.mutex);

	n = mvif->mt76.omac_idx > HW_BSSID_MAX ? HW_BSSID_0
					       : mvif->mt76.omac_idx;
	/* TSF softwawe wead */
	if (is_mt7915(&dev->mt76))
		mt76_wmw(dev, MT_WPON_TCW(band, n), MT_WPON_TCW_SW_MODE,
			 MT_WPON_TCW_SW_WEAD);
	ewse
		mt76_wmw(dev, MT_WPON_TCW_MT7916(band, n), MT_WPON_TCW_SW_MODE,
			 MT_WPON_TCW_SW_WEAD);
	tsf.t32[0] = mt76_ww(dev, MT_WPON_UTTW0(band));
	tsf.t32[1] = mt76_ww(dev, MT_WPON_UTTW1(band));

	wetuwn tsf.t64;
}

static u64
mt7915_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	u64 wet;

	mutex_wock(&dev->mt76.mutex);
	wet = __mt7915_get_tsf(hw, mvif);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void
mt7915_set_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       u64 timestamp)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	boow band = phy->mt76->band_idx;
	union {
		u64 t64;
		u32 t32[2];
	} tsf = { .t64 = timestamp, };
	u16 n;

	mutex_wock(&dev->mt76.mutex);

	n = mvif->mt76.omac_idx > HW_BSSID_MAX ? HW_BSSID_0
					       : mvif->mt76.omac_idx;
	mt76_ww(dev, MT_WPON_UTTW0(band), tsf.t32[0]);
	mt76_ww(dev, MT_WPON_UTTW1(band), tsf.t32[1]);
	/* TSF softwawe ovewwwite */
	if (is_mt7915(&dev->mt76))
		mt76_wmw(dev, MT_WPON_TCW(band, n), MT_WPON_TCW_SW_MODE,
			 MT_WPON_TCW_SW_WWITE);
	ewse
		mt76_wmw(dev, MT_WPON_TCW_MT7916(band, n), MT_WPON_TCW_SW_MODE,
			 MT_WPON_TCW_SW_WWITE);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7915_offset_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  s64 timestamp)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	boow band = phy->mt76->band_idx;
	union {
		u64 t64;
		u32 t32[2];
	} tsf = { .t64 = timestamp, };
	u16 n;

	mutex_wock(&dev->mt76.mutex);

	n = mvif->mt76.omac_idx > HW_BSSID_MAX ? HW_BSSID_0
					       : mvif->mt76.omac_idx;
	mt76_ww(dev, MT_WPON_UTTW0(band), tsf.t32[0]);
	mt76_ww(dev, MT_WPON_UTTW1(band), tsf.t32[1]);
	/* TSF softwawe adjust*/
	if (is_mt7915(&dev->mt76))
		mt76_wmw(dev, MT_WPON_TCW(band, n), MT_WPON_TCW_SW_MODE,
			 MT_WPON_TCW_SW_ADJUST);
	ewse
		mt76_wmw(dev, MT_WPON_TCW_MT7916(band, n), MT_WPON_TCW_SW_MODE,
			 MT_WPON_TCW_SW_ADJUST);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7915_set_covewage_cwass(stwuct ieee80211_hw *hw, s16 covewage_cwass)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = phy->dev;

	mutex_wock(&dev->mt76.mutex);
	phy->covewage_cwass = max_t(s16, covewage_cwass, 0);
	mt7915_mac_set_timing(phy);
	mutex_unwock(&dev->mt76.mutex);
}

static int
mt7915_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	int max_nss = hweight8(hw->wiphy->avaiwabwe_antennas_tx);
	u8 chainshift = dev->chainshift;
	u8 band = phy->mt76->band_idx;

	if (!tx_ant || tx_ant != wx_ant || ffs(tx_ant) > max_nss)
		wetuwn -EINVAW;

	mutex_wock(&dev->mt76.mutex);

	phy->mt76->antenna_mask = tx_ant;

	/* handwe a vawiant of mt7916/mt7981 which has 3T3W but nss2 on 5 GHz band */
	if ((is_mt7916(&dev->mt76) || is_mt7981(&dev->mt76)) &&
	    band && hweight8(tx_ant) == max_nss)
		phy->mt76->chainmask = (dev->chainmask >> chainshift) << chainshift;
	ewse
		phy->mt76->chainmask = tx_ant << (chainshift * band);

	mt76_set_stweam_caps(phy->mt76, twue);
	mt7915_set_stweam_vht_txbf_caps(phy);
	mt7915_set_stweam_he_caps(phy);

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static void mt7915_sta_statistics(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_sta *sta,
				  stwuct station_info *sinfo)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct wate_info *txwate = &msta->wcid.wate;
	stwuct wate_info wxwate = {};

	if (is_mt7915(&phy->dev->mt76) &&
	    !mt7915_mcu_get_wx_wate(phy, vif, sta, &wxwate)) {
		sinfo->wxwate = wxwate;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BITWATE);
	}

	if (txwate->wegacy || txwate->fwags) {
		if (txwate->wegacy) {
			sinfo->txwate.wegacy = txwate->wegacy;
		} ewse {
			sinfo->txwate.mcs = txwate->mcs;
			sinfo->txwate.nss = txwate->nss;
			sinfo->txwate.bw = txwate->bw;
			sinfo->txwate.he_gi = txwate->he_gi;
			sinfo->txwate.he_dcm = txwate->he_dcm;
			sinfo->txwate.he_wu_awwoc = txwate->he_wu_awwoc;
		}
		sinfo->txwate.fwags = txwate->fwags;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
	}

	/* offwoading fwows bypass netwowking stack, so dwivew counts and
	 * wepowts sta statistics via NW80211_STA_INFO when WED is active.
	 */
	if (mtk_wed_device_active(&phy->dev->mt76.mmio.wed)) {
		sinfo->tx_bytes = msta->wcid.stats.tx_bytes;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BYTES64);

		if (!mt7915_mcu_wed_wa_tx_stats(phy->dev, msta->wcid.idx)) {
			sinfo->tx_packets = msta->wcid.stats.tx_packets;
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_PACKETS);
		}

		if (mtk_wed_get_wx_capa(&phy->dev->mt76.mmio.wed)) {
			sinfo->wx_bytes = msta->wcid.stats.wx_bytes;
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BYTES64);

			sinfo->wx_packets = msta->wcid.stats.wx_packets;
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_PACKETS);
		}
	}

	sinfo->tx_faiwed = msta->wcid.stats.tx_faiwed;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_FAIWED);

	sinfo->tx_wetwies = msta->wcid.stats.tx_wetwies;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_WETWIES);

	sinfo->ack_signaw = (s8)msta->ack_signaw;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW);

	sinfo->avg_ack_signaw = -(s8)ewma_avg_signaw_wead(&msta->avg_ack_signaw);
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW_AVG);
}

static void mt7915_sta_wc_wowk(void *data, stwuct ieee80211_sta *sta)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = msta->vif->phy->dev;
	u32 *changed = data;

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	msta->changed |= *changed;
	if (wist_empty(&msta->wc_wist))
		wist_add_taiw(&msta->wc_wist, &dev->sta_wc_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);
}

static void mt7915_sta_wc_update(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 u32 changed)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = phy->dev;

	mt7915_sta_wc_wowk(&changed, sta);
	ieee80211_queue_wowk(hw, &dev->wc_wowk);
}

static int
mt7915_set_bitwate_mask(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			const stwuct cfg80211_bitwate_mask *mask)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = phy->dev;
	u32 changed = IEEE80211_WC_SUPP_WATES_CHANGED;

	mvif->bitwate_mask = *mask;

	/* if muwtipwe wates acwoss diffewent pweambwes awe given we can
	 * weconfiguwe this info with aww peews using sta_wec command with
	 * the bewow exception cases.
	 * - singwe wate : if a wate is passed awong with diffewent pweambwes,
	 * we sewect the highest one as fixed wate. i.e VHT MCS fow VHT peews.
	 * - muwtipwe wates: if it's not in wange fowmat i.e 0-{7,8,9} fow VHT
	 * then muwtipwe MCS setting (MCS 4,5,6) is not suppowted.
	 */
	ieee80211_itewate_stations_atomic(hw, mt7915_sta_wc_wowk, &changed);
	ieee80211_queue_wowk(hw, &dev->wc_wowk);

	wetuwn 0;
}

static void mt7915_sta_set_4addw(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 boow enabwed)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;

	if (enabwed)
		set_bit(MT_WCID_FWAG_4ADDW, &msta->wcid.fwags);
	ewse
		cweaw_bit(MT_WCID_FWAG_4ADDW, &msta->wcid.fwags);

	mt76_connac_mcu_wtbw_update_hdw_twans(&dev->mt76, vif, sta);
}

static void mt7915_sta_set_decap_offwoad(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 boow enabwed)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;

	if (enabwed)
		set_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);
	ewse
		cweaw_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);

	mt76_connac_mcu_wtbw_update_hdw_twans(&dev->mt76, vif, sta);
}

static int mt7915_sta_set_txpww(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	s16 txpowew = sta->defwink.txpww.powew;
	int wet;

	if (sta->defwink.txpww.type == NW80211_TX_POWEW_AUTOMATIC)
		txpowew = 0;

	mutex_wock(&dev->mt76.mutex);

	/* NOTE: tempowawiwy use 0 as minimum wimit, which is a
	 * gwobaw setting and wiww be appwied to aww stations.
	 */
	wet = mt7915_mcu_set_txpowew_fwame_min(phy, 0);
	if (wet)
		goto out;

	/* This onwy appwies to data fwames whiwe pushing twaffic,
	 * wheweas the management fwames ow othew packets that awe
	 * using fixed wate can be configuwed via TxD.
	 */
	wet = mt7915_mcu_set_txpowew_fwame(phy, vif, sta, txpowew);

out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static const chaw mt7915_gstwings_stats[][ETH_GSTWING_WEN] = {
	"tx_ampdu_cnt",
	"tx_stop_q_empty_cnt",
	"tx_mpdu_attempts",
	"tx_mpdu_success",
	"tx_wwp_faiw_cnt",
	"tx_wwp_need_cnt",
	"tx_pkt_ebf_cnt",
	"tx_pkt_ibf_cnt",
	"tx_ampdu_wen:0-1",
	"tx_ampdu_wen:2-10",
	"tx_ampdu_wen:11-19",
	"tx_ampdu_wen:20-28",
	"tx_ampdu_wen:29-37",
	"tx_ampdu_wen:38-46",
	"tx_ampdu_wen:47-55",
	"tx_ampdu_wen:56-79",
	"tx_ampdu_wen:80-103",
	"tx_ampdu_wen:104-127",
	"tx_ampdu_wen:128-151",
	"tx_ampdu_wen:152-175",
	"tx_ampdu_wen:176-199",
	"tx_ampdu_wen:200-223",
	"tx_ampdu_wen:224-247",
	"ba_miss_count",
	"tx_beamfowmew_ppdu_iBF",
	"tx_beamfowmew_ppdu_eBF",
	"tx_beamfowmew_wx_feedback_aww",
	"tx_beamfowmew_wx_feedback_he",
	"tx_beamfowmew_wx_feedback_vht",
	"tx_beamfowmew_wx_feedback_ht",
	"tx_beamfowmew_wx_feedback_bw", /* zewo based idx: 20, 40, 80, 160 */
	"tx_beamfowmew_wx_feedback_nc",
	"tx_beamfowmew_wx_feedback_nw",
	"tx_beamfowmee_ok_feedback_pkts",
	"tx_beamfowmee_feedback_twig",
	"tx_mu_beamfowming",
	"tx_mu_mpdu",
	"tx_mu_successfuw_mpdu",
	"tx_su_successfuw_mpdu",
	"tx_msdu_pack_1",
	"tx_msdu_pack_2",
	"tx_msdu_pack_3",
	"tx_msdu_pack_4",
	"tx_msdu_pack_5",
	"tx_msdu_pack_6",
	"tx_msdu_pack_7",
	"tx_msdu_pack_8",

	/* wx countews */
	"wx_fifo_fuww_cnt",
	"wx_mpdu_cnt",
	"channew_idwe_cnt",
	"pwimawy_cca_busy_time",
	"secondawy_cca_busy_time",
	"pwimawy_enewgy_detect_time",
	"cck_mdwdy_time",
	"ofdm_mdwdy_time",
	"gween_mdwdy_time",
	"wx_vectow_mismatch_cnt",
	"wx_dewimitew_faiw_cnt",
	"wx_mwdy_cnt",
	"wx_wen_mismatch_cnt",
	"wx_ampdu_cnt",
	"wx_ampdu_bytes_cnt",
	"wx_ampdu_vawid_subfwame_cnt",
	"wx_ampdu_vawid_subfwame_b_cnt",
	"wx_pfdwop_cnt",
	"wx_vec_queue_ovewfwow_dwop_cnt",
	"wx_ba_cnt",

	/* muwu mu-mimo and ofdma wewated stats */
	"dw_cck_cnt",
	"dw_ofdm_cnt",
	"dw_htmix_cnt",
	"dw_htgf_cnt",
	"dw_vht_su_cnt",
	"dw_vht_2mu_cnt",
	"dw_vht_3mu_cnt",
	"dw_vht_4mu_cnt",
	"dw_he_su_cnt",
	"dw_he_ext_su_cnt",
	"dw_he_2wu_cnt",
	"dw_he_2mu_cnt",
	"dw_he_3wu_cnt",
	"dw_he_3mu_cnt",
	"dw_he_4wu_cnt",
	"dw_he_4mu_cnt",
	"dw_he_5to8wu_cnt",
	"dw_he_9to16wu_cnt",
	"dw_he_gtw16wu_cnt",

	"uw_hetwig_su_cnt",
	"uw_hetwig_2wu_cnt",
	"uw_hetwig_3wu_cnt",
	"uw_hetwig_4wu_cnt",
	"uw_hetwig_5to8wu_cnt",
	"uw_hetwig_9to16wu_cnt",
	"uw_hetwig_gtw16wu_cnt",
	"uw_hetwig_2mu_cnt",
	"uw_hetwig_3mu_cnt",
	"uw_hetwig_4mu_cnt",

	/* pew vif countews */
	"v_tx_mode_cck",
	"v_tx_mode_ofdm",
	"v_tx_mode_ht",
	"v_tx_mode_ht_gf",
	"v_tx_mode_vht",
	"v_tx_mode_he_su",
	"v_tx_mode_he_ext_su",
	"v_tx_mode_he_tb",
	"v_tx_mode_he_mu",
	"v_tx_bw_20",
	"v_tx_bw_40",
	"v_tx_bw_80",
	"v_tx_bw_160",
	"v_tx_mcs_0",
	"v_tx_mcs_1",
	"v_tx_mcs_2",
	"v_tx_mcs_3",
	"v_tx_mcs_4",
	"v_tx_mcs_5",
	"v_tx_mcs_6",
	"v_tx_mcs_7",
	"v_tx_mcs_8",
	"v_tx_mcs_9",
	"v_tx_mcs_10",
	"v_tx_mcs_11",
	"v_tx_nss_1",
	"v_tx_nss_2",
	"v_tx_nss_3",
	"v_tx_nss_4",
};

#define MT7915_SSTATS_WEN AWWAY_SIZE(mt7915_gstwings_stats)

/* Ethtoow wewated API */
static
void mt7915_get_et_stwings(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   u32 sset, u8 *data)
{
	if (sset != ETH_SS_STATS)
		wetuwn;

	memcpy(data, mt7915_gstwings_stats, sizeof(mt7915_gstwings_stats));
	data += sizeof(mt7915_gstwings_stats);
	page_poow_ethtoow_stats_get_stwings(data);
}

static
int mt7915_get_et_sset_count(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn 0;

	wetuwn MT7915_SSTATS_WEN + page_poow_ethtoow_stats_get_count();
}

static void mt7915_ethtoow_wowkew(void *wi_data, stwuct ieee80211_sta *sta)
{
	stwuct mt76_ethtoow_wowkew_info *wi = wi_data;
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;

	if (msta->vif->mt76.idx != wi->idx)
		wetuwn;

	mt76_ethtoow_wowkew(wi, &msta->wcid.stats, fawse);
}

static
void mt7915_get_et_stats(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt76_mib_stats *mib = &phy->mib;
	stwuct mt76_ethtoow_wowkew_info wi = {
		.data = data,
		.idx = mvif->mt76.idx,
	};
	/* See mt7915_ampdu_stat_wead_phy, etc */
	int i, ei = 0, stats_size;

	mutex_wock(&dev->mt76.mutex);

	mt7915_mac_update_stats(phy);

	data[ei++] = mib->tx_ampdu_cnt;
	data[ei++] = mib->tx_stop_q_empty_cnt;
	data[ei++] = mib->tx_mpdu_attempts_cnt;
	data[ei++] = mib->tx_mpdu_success_cnt;
	data[ei++] = mib->tx_wwp_faiw_cnt;
	data[ei++] = mib->tx_wwp_need_cnt;
	data[ei++] = mib->tx_pkt_ebf_cnt;
	data[ei++] = mib->tx_pkt_ibf_cnt;

	/* Tx ampdu stat */
	fow (i = 0; i < 15 /*AWWAY_SIZE(bound)*/; i++)
		data[ei++] = phy->mt76->aggw_stats[i];

	data[ei++] = phy->mib.ba_miss_cnt;

	/* Tx Beamfowmew monitow */
	data[ei++] = mib->tx_bf_ibf_ppdu_cnt;
	data[ei++] = mib->tx_bf_ebf_ppdu_cnt;

	/* Tx Beamfowmew Wx feedback monitow */
	data[ei++] = mib->tx_bf_wx_fb_aww_cnt;
	data[ei++] = mib->tx_bf_wx_fb_he_cnt;
	data[ei++] = mib->tx_bf_wx_fb_vht_cnt;
	data[ei++] = mib->tx_bf_wx_fb_ht_cnt;

	data[ei++] = mib->tx_bf_wx_fb_bw;
	data[ei++] = mib->tx_bf_wx_fb_nc_cnt;
	data[ei++] = mib->tx_bf_wx_fb_nw_cnt;

	/* Tx Beamfowmee Wx NDPA & Tx feedback wepowt */
	data[ei++] = mib->tx_bf_fb_cpw_cnt;
	data[ei++] = mib->tx_bf_fb_twig_cnt;

	/* Tx SU & MU countews */
	data[ei++] = mib->tx_bf_cnt;
	data[ei++] = mib->tx_mu_mpdu_cnt;
	data[ei++] = mib->tx_mu_acked_mpdu_cnt;
	data[ei++] = mib->tx_su_acked_mpdu_cnt;

	/* Tx amsdu info (pack-count histogwam) */
	fow (i = 0; i < AWWAY_SIZE(mib->tx_amsdu); i++)
		data[ei++] = mib->tx_amsdu[i];

	/* wx countews */
	data[ei++] = mib->wx_fifo_fuww_cnt;
	data[ei++] = mib->wx_mpdu_cnt;
	data[ei++] = mib->channew_idwe_cnt;
	data[ei++] = mib->pwimawy_cca_busy_time;
	data[ei++] = mib->secondawy_cca_busy_time;
	data[ei++] = mib->pwimawy_enewgy_detect_time;
	data[ei++] = mib->cck_mdwdy_time;
	data[ei++] = mib->ofdm_mdwdy_time;
	data[ei++] = mib->gween_mdwdy_time;
	data[ei++] = mib->wx_vectow_mismatch_cnt;
	data[ei++] = mib->wx_dewimitew_faiw_cnt;
	data[ei++] = mib->wx_mwdy_cnt;
	data[ei++] = mib->wx_wen_mismatch_cnt;
	data[ei++] = mib->wx_ampdu_cnt;
	data[ei++] = mib->wx_ampdu_bytes_cnt;
	data[ei++] = mib->wx_ampdu_vawid_subfwame_cnt;
	data[ei++] = mib->wx_ampdu_vawid_subfwame_bytes_cnt;
	data[ei++] = mib->wx_pfdwop_cnt;
	data[ei++] = mib->wx_vec_queue_ovewfwow_dwop_cnt;
	data[ei++] = mib->wx_ba_cnt;

	data[ei++] = mib->dw_cck_cnt;
	data[ei++] = mib->dw_ofdm_cnt;
	data[ei++] = mib->dw_htmix_cnt;
	data[ei++] = mib->dw_htgf_cnt;
	data[ei++] = mib->dw_vht_su_cnt;
	data[ei++] = mib->dw_vht_2mu_cnt;
	data[ei++] = mib->dw_vht_3mu_cnt;
	data[ei++] = mib->dw_vht_4mu_cnt;
	data[ei++] = mib->dw_he_su_cnt;
	data[ei++] = mib->dw_he_ext_su_cnt;
	data[ei++] = mib->dw_he_2wu_cnt;
	data[ei++] = mib->dw_he_2mu_cnt;
	data[ei++] = mib->dw_he_3wu_cnt;
	data[ei++] = mib->dw_he_3mu_cnt;
	data[ei++] = mib->dw_he_4wu_cnt;
	data[ei++] = mib->dw_he_4mu_cnt;
	data[ei++] = mib->dw_he_5to8wu_cnt;
	data[ei++] = mib->dw_he_9to16wu_cnt;
	data[ei++] = mib->dw_he_gtw16wu_cnt;

	data[ei++] = mib->uw_hetwig_su_cnt;
	data[ei++] = mib->uw_hetwig_2wu_cnt;
	data[ei++] = mib->uw_hetwig_3wu_cnt;
	data[ei++] = mib->uw_hetwig_4wu_cnt;
	data[ei++] = mib->uw_hetwig_5to8wu_cnt;
	data[ei++] = mib->uw_hetwig_9to16wu_cnt;
	data[ei++] = mib->uw_hetwig_gtw16wu_cnt;
	data[ei++] = mib->uw_hetwig_2mu_cnt;
	data[ei++] = mib->uw_hetwig_3mu_cnt;
	data[ei++] = mib->uw_hetwig_4mu_cnt;

	/* Add vawues fow aww stations owned by this vif */
	wi.initiaw_stat_idx = ei;
	ieee80211_itewate_stations_atomic(hw, mt7915_ethtoow_wowkew, &wi);

	mutex_unwock(&dev->mt76.mutex);

	if (wi.sta_count == 0)
		wetuwn;

	ei += wi.wowkew_stat_count;

	mt76_ethtoow_page_poow_stats(&dev->mt76, &data[ei], &ei);

	stats_size = MT7915_SSTATS_WEN + page_poow_ethtoow_stats_get_count();
	if (ei != stats_size)
		dev_eww(dev->mt76.dev, "ei: %d size: %d", ei, stats_size);
}

static void
mt7915_twt_teawdown_wequest(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_sta *sta,
			    u8 fwowid)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);

	mutex_wock(&dev->mt76.mutex);
	mt7915_mac_twt_teawdown_fwow(dev, msta, fwowid);
	mutex_unwock(&dev->mt76.mutex);
}

static int
mt7915_set_wadaw_backgwound(stwuct ieee80211_hw *hw,
			    stwuct cfg80211_chan_def *chandef)
{
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_dev *dev = phy->dev;
	int wet = -EINVAW;
	boow wunning;

	mutex_wock(&dev->mt76.mutex);

	if (dev->mt76.wegion == NW80211_DFS_UNSET)
		goto out;

	if (dev->wdd2_phy && dev->wdd2_phy != phy) {
		/* wdd2 is awweady wocked */
		wet = -EBUSY;
		goto out;
	}

	/* wdd2 awweady configuwed on a wadaw channew */
	wunning = dev->wdd2_phy &&
		  cfg80211_chandef_vawid(&dev->wdd2_chandef) &&
		  !!(dev->wdd2_chandef.chan->fwags & IEEE80211_CHAN_WADAW);

	if (!chandef || wunning ||
	    !(chandef->chan->fwags & IEEE80211_CHAN_WADAW)) {
		wet = mt7915_mcu_wdd_backgwound_enabwe(phy, NUWW);
		if (wet)
			goto out;

		if (!wunning)
			goto update_phy;
	}

	wet = mt7915_mcu_wdd_backgwound_enabwe(phy, chandef);
	if (wet)
		goto out;

update_phy:
	dev->wdd2_phy = chandef ? phy : NUWW;
	if (chandef)
		dev->wdd2_chandef = *chandef;
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
static int
mt7915_net_fiww_fowwawd_path(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta,
			     stwuct net_device_path_ctx *ctx,
			     stwuct net_device_path *path)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;

	if (!mtk_wed_device_active(wed))
		wetuwn -ENODEV;

	if (msta->wcid.idx > 0xff)
		wetuwn -EIO;

	path->type = DEV_PATH_MTK_WDMA;
	path->dev = ctx->dev;
	path->mtk_wdma.wdma_idx = wed->wdma_idx;
	path->mtk_wdma.bss = mvif->mt76.idx;
	path->mtk_wdma.wcid = is_mt7915(&dev->mt76) ? msta->wcid.idx : 0x3ff;
	path->mtk_wdma.queue = phy != &dev->phy;

	ctx->dev = NUWW;

	wetuwn 0;
}
#endif

const stwuct ieee80211_ops mt7915_ops = {
	.tx = mt7915_tx,
	.stawt = mt7915_stawt,
	.stop = mt7915_stop,
	.add_intewface = mt7915_add_intewface,
	.wemove_intewface = mt7915_wemove_intewface,
	.config = mt7915_config,
	.conf_tx = mt7915_conf_tx,
	.configuwe_fiwtew = mt7915_configuwe_fiwtew,
	.bss_info_changed = mt7915_bss_info_changed,
	.stawt_ap = mt7915_stawt_ap,
	.stop_ap = mt7915_stop_ap,
	.sta_add = mt7915_sta_add,
	.sta_wemove = mt7915_sta_wemove,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.sta_wc_update = mt7915_sta_wc_update,
	.set_key = mt7915_set_key,
	.ampdu_action = mt7915_ampdu_action,
	.set_wts_thweshowd = mt7915_set_wts_thweshowd,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76_sw_scan_compwete,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.get_txpowew = mt76_get_txpowew,
	.set_saw_specs = mt7915_set_saw_specs,
	.channew_switch_beacon = mt7915_channew_switch_beacon,
	.get_stats = mt7915_get_stats,
	.get_et_sset_count = mt7915_get_et_sset_count,
	.get_et_stats = mt7915_get_et_stats,
	.get_et_stwings = mt7915_get_et_stwings,
	.get_tsf = mt7915_get_tsf,
	.set_tsf = mt7915_set_tsf,
	.offset_tsf = mt7915_offset_tsf,
	.get_suwvey = mt76_get_suwvey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7915_set_antenna,
	.set_bitwate_mask = mt7915_set_bitwate_mask,
	.set_covewage_cwass = mt7915_set_covewage_cwass,
	.sta_statistics = mt7915_sta_statistics,
	.sta_set_txpww = mt7915_sta_set_txpww,
	.sta_set_4addw = mt7915_sta_set_4addw,
	.sta_set_decap_offwoad = mt7915_sta_set_decap_offwoad,
	.add_twt_setup = mt7915_mac_add_twt_setup,
	.twt_teawdown_wequest = mt7915_twt_teawdown_wequest,
	CFG80211_TESTMODE_CMD(mt76_testmode_cmd)
	CFG80211_TESTMODE_DUMP(mt76_testmode_dump)
#ifdef CONFIG_MAC80211_DEBUGFS
	.sta_add_debugfs = mt7915_sta_add_debugfs,
#endif
	.set_wadaw_backgwound = mt7915_set_wadaw_backgwound,
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	.net_fiww_fowwawd_path = mt7915_net_fiww_fowwawd_path,
	.net_setup_tc = mt76_net_setup_tc,
#endif
};
