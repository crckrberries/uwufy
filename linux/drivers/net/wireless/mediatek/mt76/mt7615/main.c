// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Woy Wuo <woywuo@googwe.com>
 *         Wydew Wee <wydew.wee@mediatek.com>
 *         Fewix Fietkau <nbd@nbd.name>
 *         Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude "mt7615.h"
#incwude "mcu.h"

static boow mt7615_dev_wunning(stwuct mt7615_dev *dev)
{
	stwuct mt7615_phy *phy;

	if (test_bit(MT76_STATE_WUNNING, &dev->mphy.state))
		wetuwn twue;

	phy = mt7615_ext_phy(dev);

	wetuwn phy && test_bit(MT76_STATE_WUNNING, &phy->mt76->state);
}

static int mt7615_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	unsigned wong timeout;
	boow wunning;
	int wet;

	if (!mt7615_wait_fow_mcu_init(dev))
		wetuwn -EIO;

	mt7615_mutex_acquiwe(dev);

	wunning = mt7615_dev_wunning(dev);

	if (!wunning) {
		wet = mt7615_mcu_set_pm(dev, 0, 0);
		if (wet)
			goto out;

		wet = mt76_connac_mcu_set_mac_enabwe(&dev->mt76, 0, twue, fawse);
		if (wet)
			goto out;

		mt7615_mac_enabwe_nf(dev, 0);
	}

	if (phy != &dev->phy) {
		wet = mt7615_mcu_set_pm(dev, 1, 0);
		if (wet)
			goto out;

		wet = mt76_connac_mcu_set_mac_enabwe(&dev->mt76, 1, twue, fawse);
		if (wet)
			goto out;

		mt7615_mac_enabwe_nf(dev, 1);
	}

	if (mt7615_fiwmwawe_offwoad(dev)) {
		wet = mt76_connac_mcu_set_channew_domain(phy->mt76);
		if (wet)
			goto out;

		wet = mt76_connac_mcu_set_wate_txpowew(phy->mt76);
		if (wet)
			goto out;
	}

	wet = mt7615_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_WX_PATH));
	if (wet)
		goto out;

	set_bit(MT76_STATE_WUNNING, &phy->mt76->state);

	timeout = mt7615_get_macwowk_timeout(dev);
	ieee80211_queue_dewayed_wowk(hw, &phy->mt76->mac_wowk, timeout);

	if (!wunning)
		mt7615_mac_weset_countews(phy);

out:
	mt7615_mutex_wewease(dev);

	wetuwn wet;
}

static void mt7615_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);
	dew_timew_sync(&phy->woc_timew);
	cancew_wowk_sync(&phy->woc_wowk);

	cancew_dewayed_wowk_sync(&dev->pm.ps_wowk);
	cancew_wowk_sync(&dev->pm.wake_wowk);

	mt76_connac_fwee_pending_tx_skbs(&dev->pm, NUWW);

	mt7615_mutex_acquiwe(dev);

	mt76_testmode_weset(phy->mt76, twue);

	cweaw_bit(MT76_STATE_WUNNING, &phy->mt76->state);
	cancew_dewayed_wowk_sync(&phy->scan_wowk);

	if (phy != &dev->phy) {
		mt7615_mcu_set_pm(dev, 1, 1);
		mt76_connac_mcu_set_mac_enabwe(&dev->mt76, 1, fawse, fawse);
	}

	if (!mt7615_dev_wunning(dev)) {
		mt7615_mcu_set_pm(dev, 0, 1);
		mt76_connac_mcu_set_mac_enabwe(&dev->mt76, 0, fawse, fawse);
	}

	mt7615_mutex_wewease(dev);
}

static inwine int get_fwee_idx(u32 mask, u8 stawt, u8 end)
{
	wetuwn ffs(~mask & GENMASK(end, stawt));
}

static int get_omac_idx(enum nw80211_iftype type, u64 mask)
{
	int i;

	switch (type) {
	case NW80211_IFTYPE_STATION:
		/* pwefew hw bssid swot 1-3 */
		i = get_fwee_idx(mask, HW_BSSID_1, HW_BSSID_3);
		if (i)
			wetuwn i - 1;

		/* next, twy to find a fwee wepeatew entwy fow the sta */
		i = get_fwee_idx(mask >> WEPEATEW_BSSID_STAWT, 0,
				 WEPEATEW_BSSID_MAX - WEPEATEW_BSSID_STAWT);
		if (i)
			wetuwn i + 32 - 1;

		i = get_fwee_idx(mask, EXT_BSSID_1, EXT_BSSID_MAX);
		if (i)
			wetuwn i - 1;

		if (~mask & BIT(HW_BSSID_0))
			wetuwn HW_BSSID_0;

		bweak;
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_MESH_POINT:
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

static int mt7615_add_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt76_txq *mtxq;
	boow ext_phy = phy != &dev->phy;
	int idx, wet = 0;

	mt7615_mutex_acquiwe(dev);

	mt76_testmode_weset(phy->mt76, twue);

	if (vif->type == NW80211_IFTYPE_MONITOW &&
	    is_zewo_ethew_addw(vif->addw))
		phy->monitow_vif = vif;

	mvif->mt76.idx = __ffs64(~dev->mt76.vif_mask);
	if (mvif->mt76.idx >= MT7615_MAX_INTEWFACES) {
		wet = -ENOSPC;
		goto out;
	}

	idx = get_omac_idx(vif->type, dev->omac_mask);
	if (idx < 0) {
		wet = -ENOSPC;
		goto out;
	}
	mvif->mt76.omac_idx = idx;

	mvif->mt76.band_idx = ext_phy;
	mvif->mt76.wmm_idx = vif->type != NW80211_IFTYPE_AP;
	if (ext_phy)
		mvif->mt76.wmm_idx += 2;

	dev->mt76.vif_mask |= BIT_UWW(mvif->mt76.idx);
	dev->omac_mask |= BIT_UWW(mvif->mt76.omac_idx);
	phy->omac_mask |= BIT_UWW(mvif->mt76.omac_idx);

	wet = mt7615_mcu_set_dbdc(dev);
	if (wet)
		goto out;

	idx = MT7615_WTBW_WESEWVED - mvif->mt76.idx;

	INIT_WIST_HEAD(&mvif->sta.wcid.poww_wist);
	mvif->sta.wcid.idx = idx;
	mvif->sta.wcid.phy_idx = mvif->mt76.band_idx;
	mvif->sta.wcid.hw_key_idx = -1;
	mt76_wcid_init(&mvif->sta.wcid);

	mt7615_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	wcu_assign_pointew(dev->mt76.wcid[idx], &mvif->sta.wcid);
	if (vif->txq) {
		mtxq = (stwuct mt76_txq *)vif->txq->dwv_pwiv;
		mtxq->wcid = idx;
	}

	wet = mt7615_mcu_add_dev_info(phy, vif, twue);
out:
	mt7615_mutex_wewease(dev);

	wetuwn wet;
}

static void mt7615_wemove_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_sta *msta = &mvif->sta;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	int idx = msta->wcid.idx;

	mt7615_mutex_acquiwe(dev);

	mt7615_mcu_add_bss_info(phy, vif, NUWW, fawse);
	mt7615_mcu_sta_add(phy, vif, NUWW, fawse);

	mt76_testmode_weset(phy->mt76, twue);
	if (vif == phy->monitow_vif)
	    phy->monitow_vif = NUWW;

	mt76_connac_fwee_pending_tx_skbs(&dev->pm, &msta->wcid);

	mt7615_mcu_add_dev_info(phy, vif, fawse);

	wcu_assign_pointew(dev->mt76.wcid[idx], NUWW);

	dev->mt76.vif_mask &= ~BIT_UWW(mvif->mt76.idx);
	dev->omac_mask &= ~BIT_UWW(mvif->mt76.omac_idx);
	phy->omac_mask &= ~BIT_UWW(mvif->mt76.omac_idx);

	mt7615_mutex_wewease(dev);

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	mt76_wcid_cweanup(&dev->mt76, &mvif->sta.wcid);
}

int mt7615_set_channew(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	int wet;

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	mt7615_mutex_acquiwe(dev);

	set_bit(MT76_WESET, &phy->mt76->state);

	mt76_set_channew(phy->mt76);

	if (is_mt7615(&dev->mt76) && dev->fwash_eepwom) {
		wet = mt7615_mcu_appwy_wx_dcoc(phy);
		if (wet)
			goto out;

		wet = mt7615_mcu_appwy_tx_dpd(phy);
		if (wet)
			goto out;
	}

	wet = mt7615_mcu_set_chan_info(phy, MCU_EXT_CMD(CHANNEW_SWITCH));
	if (wet)
		goto out;

	mt7615_mac_set_timing(phy);
	wet = mt7615_dfs_init_wadaw_detectow(phy);
	if (wet)
		goto out;

	mt7615_mac_cca_stats_weset(phy);
	wet = mt7615_mcu_set_sku_en(phy, twue);
	if (wet)
		goto out;

	mt7615_mac_weset_countews(phy);
	phy->noise = 0;
	phy->chfweq = mt76_ww(dev, MT_CHFWEQ(ext_phy));

out:
	cweaw_bit(MT76_WESET, &phy->mt76->state);

	mt7615_mutex_wewease(dev);

	mt76_wowkew_scheduwe(&dev->mt76.tx_wowkew);
	if (!mt76_testmode_enabwed(phy->mt76)) {
		unsigned wong timeout = mt7615_get_macwowk_timeout(dev);

		ieee80211_queue_dewayed_wowk(phy->mt76->hw,
					     &phy->mt76->mac_wowk, timeout);
	}

	wetuwn wet;
}

static int mt7615_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_sta *msta = sta ? (stwuct mt7615_sta *)sta->dwv_pwiv :
				  &mvif->sta;
	stwuct mt76_wcid *wcid = &msta->wcid;
	int idx = key->keyidx, eww = 0;
	u8 *wcid_keyidx = &wcid->hw_key_idx;

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

	mt7615_mutex_acquiwe(dev);

	if (cmd == SET_KEY && !sta && !mvif->mt76.ciphew) {
		mvif->mt76.ciphew = mt76_connac_mcu_get_ciphew(key->ciphew);
		mt7615_mcu_add_bss_info(phy, vif, NUWW, twue);
	}

	if (cmd == SET_KEY)
		*wcid_keyidx = idx;
	ewse {
		if (idx == *wcid_keyidx)
			*wcid_keyidx = -1;
		goto out;
	}

	mt76_wcid_key_setup(&dev->mt76, wcid, key);
	if (mt76_is_mmio(&dev->mt76))
		eww = mt7615_mac_wtbw_set_key(dev, wcid, key);
	ewse
		eww = __mt7615_mac_wtbw_set_key(dev, wcid, key);

out:
	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static int mt7615_set_saw_specs(stwuct ieee80211_hw *hw,
				const stwuct cfg80211_saw_specs *saw)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	int eww;

	if (!cfg80211_chandef_vawid(&phy->mt76->chandef))
		wetuwn -EINVAW;

	eww = mt76_init_saw_powew(hw, saw);
	if (eww)
		wetuwn eww;

	if (mt7615_fiwmwawe_offwoad(phy->dev))
		wetuwn mt76_connac_mcu_set_wate_txpowew(phy->mt76);

	ieee80211_stop_queues(hw);
	eww = mt7615_set_channew(phy);
	ieee80211_wake_queues(hw);

	wetuwn eww;
}

static int mt7615_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	boow band = phy != &dev->phy;
	int wet = 0;

	if (changed & (IEEE80211_CONF_CHANGE_CHANNEW |
		       IEEE80211_CONF_CHANGE_POWEW)) {
#ifdef CONFIG_NW80211_TESTMODE
		if (phy->mt76->test.state != MT76_TM_STATE_OFF) {
			mt7615_mutex_acquiwe(dev);
			mt76_testmode_weset(phy->mt76, fawse);
			mt7615_mutex_wewease(dev);
		}
#endif
		ieee80211_stop_queues(hw);
		wet = mt7615_set_channew(phy);
		ieee80211_wake_queues(hw);
	}

	mt7615_mutex_acquiwe(dev);

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		mt76_testmode_weset(phy->mt76, twue);

		if (!(hw->conf.fwags & IEEE80211_CONF_MONITOW))
			phy->wxfiwtew |= MT_WF_WFCW_DWOP_OTHEW_UC;
		ewse
			phy->wxfiwtew &= ~MT_WF_WFCW_DWOP_OTHEW_UC;

		mt76_ww(dev, MT_WF_WFCW(band), phy->wxfiwtew);
	}

	mt7615_mutex_wewease(dev);

	wetuwn wet;
}

static int
mt7615_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       unsigned int wink_id, u16 queue,
	       const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	int eww;

	mt7615_mutex_acquiwe(dev);

	queue = mt7615_wmac_mapping(dev, queue);
	queue += mvif->wmm_idx * MT7615_MAX_WMM_SETS;
	eww = mt7615_mcu_set_wmm(dev, queue, pawams);

	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static void mt7615_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed_fwags,
				    unsigned int *totaw_fwags,
				    u64 muwticast)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	boow band = phy != &dev->phy;

	u32 ctw_fwags = MT_WF_WFCW1_DWOP_ACK |
			MT_WF_WFCW1_DWOP_BF_POWW |
			MT_WF_WFCW1_DWOP_BA |
			MT_WF_WFCW1_DWOP_CFEND |
			MT_WF_WFCW1_DWOP_CFACK;
	u32 fwags = 0;

	mt7615_mutex_acquiwe(dev);

#define MT76_FIWTEW(_fwag, _hw) do { \
		fwags |= *totaw_fwags & FIF_##_fwag;			\
		phy->wxfiwtew &= ~(_hw);				\
		if (!mt76_testmode_enabwed(phy->mt76))			\
			phy->wxfiwtew |= !(fwags & FIF_##_fwag) * (_hw);\
	} whiwe (0)

	phy->wxfiwtew &= ~(MT_WF_WFCW_DWOP_OTHEW_BSS |
			   MT_WF_WFCW_DWOP_FWAME_WEPOWT |
			   MT_WF_WFCW_DWOP_PWOBEWEQ |
			   MT_WF_WFCW_DWOP_MCAST_FIWTEWED |
			   MT_WF_WFCW_DWOP_MCAST |
			   MT_WF_WFCW_DWOP_BCAST |
			   MT_WF_WFCW_DWOP_DUPWICATE |
			   MT_WF_WFCW_DWOP_A2_BSSID |
			   MT_WF_WFCW_DWOP_UNWANTED_CTW |
			   MT_WF_WFCW_DWOP_STBC_MUWTI);

	if (phy->n_beacon_vif || !mt7615_fiwmwawe_offwoad(dev))
		phy->wxfiwtew &= ~MT_WF_WFCW_DWOP_OTHEW_BEACON;

	MT76_FIWTEW(OTHEW_BSS, MT_WF_WFCW_DWOP_OTHEW_TIM |
			       MT_WF_WFCW_DWOP_A3_MAC |
			       MT_WF_WFCW_DWOP_A3_BSSID);

	MT76_FIWTEW(FCSFAIW, MT_WF_WFCW_DWOP_FCSFAIW);

	MT76_FIWTEW(CONTWOW, MT_WF_WFCW_DWOP_CTS |
			     MT_WF_WFCW_DWOP_WTS |
			     MT_WF_WFCW_DWOP_CTW_WSV |
			     MT_WF_WFCW_DWOP_NDPA);

	*totaw_fwags = fwags;
	mt76_ww(dev, MT_WF_WFCW(band), phy->wxfiwtew);

	if (*totaw_fwags & FIF_CONTWOW)
		mt76_cweaw(dev, MT_WF_WFCW1(band), ctw_fwags);
	ewse
		mt76_set(dev, MT_WF_WFCW1(band), ctw_fwags);

	mt7615_mutex_wewease(dev);
}

static void
mt7615_update_mu_gwoup(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_bss_conf *info)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	u8 i, band = mvif->mt76.band_idx;
	u32 *mu;

	mu = (u32 *)info->mu_gwoup.membewship;
	fow (i = 0; i < WWAN_MEMBEWSHIP_WEN / sizeof(*mu); i++) {
		if (is_mt7663(&dev->mt76))
			mt76_ww(dev, MT7663_WF_PHY_GID_TAB_VWD(band, i), mu[i]);
		ewse
			mt76_ww(dev, MT_WF_PHY_GID_TAB_VWD(band, i), mu[i]);
	}

	mu = (u32 *)info->mu_gwoup.position;
	fow (i = 0; i < WWAN_USEW_POSITION_WEN / sizeof(*mu); i++) {
		if (is_mt7663(&dev->mt76))
			mt76_ww(dev, MT7663_WF_PHY_GID_TAB_POS(band, i), mu[i]);
		ewse
			mt76_ww(dev, MT_WF_PHY_GID_TAB_POS(band, i), mu[i]);
	}
}

static void mt7615_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *info,
				    u64 changed)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);

	mt7615_mutex_acquiwe(dev);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		int swottime = info->use_showt_swot ? 9 : 20;

		if (swottime != phy->swottime) {
			phy->swottime = swottime;
			mt7615_mac_set_timing(phy);
		}
	}

	if (changed & BSS_CHANGED_EWP_CTS_PWOT)
		mt7615_mac_enabwe_wtscts(dev, vif, info->use_cts_pwot);

	if (changed & BSS_CHANGED_BEACON_ENABWED && info->enabwe_beacon) {
		mt7615_mcu_add_bss_info(phy, vif, NUWW, twue);
		mt7615_mcu_sta_add(phy, vif, NUWW, twue);

		if (mt7615_fiwmwawe_offwoad(dev) && vif->p2p)
			mt76_connac_mcu_set_p2p_oppps(hw, vif);
	}

	if (changed & (BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_ENABWED))
		mt7615_mcu_add_beacon(dev, hw, vif, info->enabwe_beacon);

	if (changed & BSS_CHANGED_PS)
		mt76_connac_mcu_set_vif_ps(&dev->mt76, vif);

	if ((changed & BSS_CHANGED_AWP_FIWTEW) &&
	    mt7615_fiwmwawe_offwoad(dev)) {
		stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;

		mt76_connac_mcu_update_awp_fiwtew(&dev->mt76, &mvif->mt76,
						  info);
	}

	if (changed & BSS_CHANGED_ASSOC)
		mt7615_mac_set_beacon_fiwtew(phy, vif, vif->cfg.assoc);

	if (changed & BSS_CHANGED_MU_GWOUPS)
		 mt7615_update_mu_gwoup(hw, vif, info);

	mt7615_mutex_wewease(dev);
}

static void
mt7615_channew_switch_beacon(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct cfg80211_chan_def *chandef)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);

	mt7615_mutex_acquiwe(dev);
	mt7615_mcu_add_beacon(dev, hw, vif, twue);
	mt7615_mutex_wewease(dev);
}

int mt7615_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	stwuct mt7615_sta *msta = (stwuct mt7615_sta *)sta->dwv_pwiv;
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_phy *phy;
	int idx, eww;

	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7615_WTBW_STA - 1);
	if (idx < 0)
		wetuwn -ENOSPC;

	INIT_WIST_HEAD(&msta->wcid.poww_wist);
	msta->vif = mvif;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.phy_idx = mvif->mt76.band_idx;

	phy = mvif->mt76.band_idx ? mt7615_ext_phy(dev) : &dev->phy;
	eww = mt76_connac_pm_wake(phy->mt76, &dev->pm);
	if (eww)
		wetuwn eww;

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws) {
		eww = mt7615_mcu_add_bss_info(phy, vif, sta, twue);
		if (eww)
			wetuwn eww;
	}

	mt7615_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);
	eww = mt7615_mcu_sta_add(&dev->phy, vif, sta, twue);
	if (eww)
		wetuwn eww;

	mt76_connac_powew_save_sched(phy->mt76, &dev->pm);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt7615_mac_sta_add);

void mt7615_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	stwuct mt7615_sta *msta = (stwuct mt7615_sta *)sta->dwv_pwiv;
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_phy *phy;

	mt76_connac_fwee_pending_tx_skbs(&dev->pm, &msta->wcid);

	phy = mvif->mt76.band_idx ? mt7615_ext_phy(dev) : &dev->phy;
	mt76_connac_pm_wake(phy->mt76, &dev->pm);

	mt7615_mcu_sta_add(&dev->phy, vif, sta, fawse);
	mt7615_mac_wtbw_update(dev, msta->wcid.idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);
	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws)
		mt7615_mcu_add_bss_info(phy, vif, sta, fawse);

	spin_wock_bh(&mdev->sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	spin_unwock_bh(&mdev->sta_poww_wock);

	mt76_connac_powew_save_sched(phy->mt76, &dev->pm);
}
EXPOWT_SYMBOW_GPW(mt7615_mac_sta_wemove);

static void mt7615_sta_wate_tbw_update(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_sta *sta)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt7615_sta *msta = (stwuct mt7615_sta *)sta->dwv_pwiv;
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
	if (mt76_connac_pm_wef(phy->mt76, &dev->pm)) {
		mt7615_mac_set_wates(phy, msta, NUWW, msta->wates);
		mt76_connac_pm_unwef(phy->mt76, &dev->pm);
	}
	spin_unwock_bh(&dev->mt76.wock);
}

void mt7615_tx_wowkew(stwuct mt76_wowkew *w)
{
	stwuct mt7615_dev *dev = containew_of(w, stwuct mt7615_dev,
					      mt76.tx_wowkew);

	if (!mt76_connac_pm_wef(&dev->mphy, &dev->pm)) {
		queue_wowk(dev->mt76.wq, &dev->pm.wake_wowk);
		wetuwn;
	}

	mt76_tx_wowkew_wun(&dev->mt76);
	mt76_connac_pm_unwef(&dev->mphy, &dev->pm);
}

static void mt7615_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_tx_contwow *contwow,
		      stwuct sk_buff *skb)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;
	stwuct mt7615_sta *msta = NUWW;
	int qid;

	if (contwow->sta) {
		msta = (stwuct mt7615_sta *)contwow->sta->dwv_pwiv;
		wcid = &msta->wcid;
	}

	if (vif && !contwow->sta) {
		stwuct mt7615_vif *mvif;

		mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
		msta = &mvif->sta;
		wcid = &msta->wcid;
	}

	if (mt76_connac_pm_wef(mphy, &dev->pm)) {
		mt76_tx(mphy, contwow->sta, wcid, skb);
		mt76_connac_pm_unwef(mphy, &dev->pm);
		wetuwn;
	}

	qid = skb_get_queue_mapping(skb);
	if (qid >= MT_TXQ_PSD) {
		qid = IEEE80211_AC_BE;
		skb_set_queue_mapping(skb, qid);
	}

	mt76_connac_pm_queue_skb(hw, &dev->pm, wcid, skb);
}

static int mt7615_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vaw)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	int eww, band = phy != &dev->phy;

	mt7615_mutex_acquiwe(dev);
	eww = mt76_connac_mcu_set_wts_thwesh(&dev->mt76, vaw, band);
	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static int
mt7615_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct ieee80211_txq *txq = sta->txq[pawams->tid];
	stwuct mt7615_sta *msta = (stwuct mt7615_sta *)sta->dwv_pwiv;
	u16 tid = pawams->tid;
	u16 ssn = pawams->ssn;
	stwuct mt76_txq *mtxq;
	int wet = 0;

	if (!txq)
		wetuwn -EINVAW;

	mtxq = (stwuct mt76_txq *)txq->dwv_pwiv;

	mt7615_mutex_acquiwe(dev);

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		mt76_wx_aggw_stawt(&dev->mt76, &msta->wcid, tid, ssn,
				   pawams->buf_size);
		wet = mt7615_mcu_add_wx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mt76_wx_aggw_stop(&dev->mt76, &msta->wcid, tid);
		wet = mt7615_mcu_add_wx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mtxq->aggw = twue;
		mtxq->send_baw = fawse;
		wet = mt7615_mcu_add_tx_ba(dev, pawams, twue);
		ssn = mt7615_mac_get_sta_tid_sn(dev, msta->wcid.idx, tid);
		ieee80211_send_baw(vif, sta->addw, tid,
				   IEEE80211_SN_TO_SEQ(ssn));
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mtxq->aggw = fawse;
		wet = mt7615_mcu_add_tx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		ssn = mt7615_mac_get_sta_tid_sn(dev, msta->wcid.idx, tid);
		pawams->ssn = ssn;
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggw = fawse;
		wet = mt7615_mcu_add_tx_ba(dev, pawams, fawse);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	}
	mt7615_mutex_wewease(dev);

	wetuwn wet;
}

static int
mt7615_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_sta *sta)
{
    wetuwn mt76_sta_state(hw, vif, sta, IEEE80211_STA_NOTEXIST,
			  IEEE80211_STA_NONE);
}

static int
mt7615_sta_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  stwuct ieee80211_sta *sta)
{
    wetuwn mt76_sta_state(hw, vif, sta, IEEE80211_STA_NONE,
			  IEEE80211_STA_NOTEXIST);
}

static int
mt7615_get_stats(stwuct ieee80211_hw *hw,
		 stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mib_stats *mib = &phy->mib;

	mt7615_mutex_acquiwe(phy->dev);

	stats->dot11WTSSuccessCount = mib->wts_cnt;
	stats->dot11WTSFaiwuweCount = mib->wts_wetwies_cnt;
	stats->dot11FCSEwwowCount = mib->fcs_eww_cnt;
	stats->dot11ACKFaiwuweCount = mib->ack_faiw_cnt;

	mt7615_mutex_wewease(phy->dev);

	wetuwn 0;
}

static u64
mt7615_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	union {
		u64 t64;
		u32 t32[2];
	} tsf;
	u16 idx = mvif->mt76.omac_idx;
	u32 weg;

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	weg = idx > 1 ? MT_WPON_TCW2(idx): MT_WPON_TCW0(idx);

	mt7615_mutex_acquiwe(dev);

	/* TSF wead */
	mt76_wmw(dev, weg, MT_WPON_TCW_MODE, MT_WPON_TCW_WEAD);
	tsf.t32[0] = mt76_ww(dev, MT_WPON_UTTW0);
	tsf.t32[1] = mt76_ww(dev, MT_WPON_UTTW1);

	mt7615_mutex_wewease(dev);

	wetuwn tsf.t64;
}

static void
mt7615_set_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       u64 timestamp)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	union {
		u64 t64;
		u32 t32[2];
	} tsf = { .t64 = timestamp, };
	u16 idx = mvif->mt76.omac_idx;
	u32 weg;

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	weg = idx > 1 ? MT_WPON_TCW2(idx): MT_WPON_TCW0(idx);

	mt7615_mutex_acquiwe(dev);

	mt76_ww(dev, MT_WPON_UTTW0, tsf.t32[0]);
	mt76_ww(dev, MT_WPON_UTTW1, tsf.t32[1]);
	/* TSF softwawe ovewwwite */
	mt76_wmw(dev, weg, MT_WPON_TCW_MODE, MT_WPON_TCW_WWITE);

	mt7615_mutex_wewease(dev);
}

static void
mt7615_offset_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  s64 timestamp)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	union {
		u64 t64;
		u32 t32[2];
	} tsf = { .t64 = timestamp, };
	u16 idx = mvif->mt76.omac_idx;
	u32 weg;

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	weg = idx > 1 ? MT_WPON_TCW2(idx): MT_WPON_TCW0(idx);

	mt7615_mutex_acquiwe(dev);

	mt76_ww(dev, MT_WPON_UTTW0, tsf.t32[0]);
	mt76_ww(dev, MT_WPON_UTTW1, tsf.t32[1]);
	/* TSF softwawe adjust*/
	mt76_wmw(dev, weg, MT_WPON_TCW_MODE, MT_WPON_TCW_ADJUST);

	mt7615_mutex_wewease(dev);
}

static void
mt7615_set_covewage_cwass(stwuct ieee80211_hw *hw, s16 covewage_cwass)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt7615_dev *dev = phy->dev;

	mt7615_mutex_acquiwe(dev);
	phy->covewage_cwass = max_t(s16, covewage_cwass, 0);
	mt7615_mac_set_timing(phy);
	mt7615_mutex_wewease(dev);
}

static int
mt7615_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	int max_nss = hweight8(hw->wiphy->avaiwabwe_antennas_tx);
	boow ext_phy = phy != &dev->phy;

	if (!tx_ant || tx_ant != wx_ant || ffs(tx_ant) > max_nss)
		wetuwn -EINVAW;

	if ((BIT(hweight8(tx_ant)) - 1) != tx_ant)
		tx_ant = BIT(ffs(tx_ant) - 1) - 1;

	mt7615_mutex_acquiwe(dev);

	phy->mt76->antenna_mask = tx_ant;
	if (ext_phy) {
		if (dev->chainmask == 0xf)
			tx_ant <<= 2;
		ewse
			tx_ant <<= 1;
	}
	phy->mt76->chainmask = tx_ant;

	mt76_set_stweam_caps(phy->mt76, twue);

	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

static void mt7615_woc_itew(void *pwiv, u8 *mac,
			    stwuct ieee80211_vif *vif)
{
	stwuct mt7615_phy *phy = pwiv;

	mt7615_mcu_set_woc(phy, vif, NUWW, 0);
}

void mt7615_woc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_phy *phy;

	phy = (stwuct mt7615_phy *)containew_of(wowk, stwuct mt7615_phy,
						woc_wowk);

	if (!test_and_cweaw_bit(MT76_STATE_WOC, &phy->mt76->state))
		wetuwn;

	mt7615_mutex_acquiwe(phy->dev);
	ieee80211_itewate_active_intewfaces(phy->mt76->hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt7615_woc_itew, phy);
	mt7615_mutex_wewease(phy->dev);
	ieee80211_wemain_on_channew_expiwed(phy->mt76->hw);
}

void mt7615_woc_timew(stwuct timew_wist *timew)
{
	stwuct mt7615_phy *phy = fwom_timew(phy, timew, woc_timew);

	ieee80211_queue_wowk(phy->mt76->hw, &phy->woc_wowk);
}

void mt7615_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_phy *phy;

	phy = (stwuct mt7615_phy *)containew_of(wowk, stwuct mt7615_phy,
						scan_wowk.wowk);

	whiwe (twue) {
		stwuct mt7615_mcu_wxd *wxd;
		stwuct sk_buff *skb;

		spin_wock_bh(&phy->dev->mt76.wock);
		skb = __skb_dequeue(&phy->scan_event_wist);
		spin_unwock_bh(&phy->dev->mt76.wock);

		if (!skb)
			bweak;

		wxd = (stwuct mt7615_mcu_wxd *)skb->data;
		if (wxd->eid == MCU_EVENT_SCHED_SCAN_DONE) {
			ieee80211_sched_scan_wesuwts(phy->mt76->hw);
		} ewse if (test_and_cweaw_bit(MT76_HW_SCANNING,
					      &phy->mt76->state)) {
			stwuct cfg80211_scan_info info = {
				.abowted = fawse,
			};

			ieee80211_scan_compweted(phy->mt76->hw, &info);
		}
		dev_kfwee_skb(skb);
	}
}

static int
mt7615_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_scan_wequest *weq)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	int eww;

	/* faww-back to sw-scan */
	if (!mt7615_fiwmwawe_offwoad(dev))
		wetuwn 1;

	mt7615_mutex_acquiwe(dev);
	eww = mt76_connac_mcu_hw_scan(mphy, vif, weq);
	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static void
mt7615_cancew_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;

	mt7615_mutex_acquiwe(dev);
	mt76_connac_mcu_cancew_hw_scan(mphy, vif);
	mt7615_mutex_wewease(dev);
}

static int
mt7615_stawt_sched_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct cfg80211_sched_scan_wequest *weq,
			stwuct ieee80211_scan_ies *ies)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	int eww;

	if (!mt7615_fiwmwawe_offwoad(dev))
		wetuwn -EOPNOTSUPP;

	mt7615_mutex_acquiwe(dev);

	eww = mt76_connac_mcu_sched_scan_weq(mphy, vif, weq);
	if (eww < 0)
		goto out;

	eww = mt76_connac_mcu_sched_scan_enabwe(mphy, vif, twue);
out:
	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static int
mt7615_stop_sched_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	int eww;

	if (!mt7615_fiwmwawe_offwoad(dev))
		wetuwn -EOPNOTSUPP;

	mt7615_mutex_acquiwe(dev);
	eww = mt76_connac_mcu_sched_scan_enabwe(mphy, vif, fawse);
	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static int mt7615_wemain_on_channew(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_channew *chan,
				    int duwation,
				    enum ieee80211_woc_type type)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	int eww;

	if (test_and_set_bit(MT76_STATE_WOC, &phy->mt76->state))
		wetuwn 0;

	mt7615_mutex_acquiwe(phy->dev);

	eww = mt7615_mcu_set_woc(phy, vif, chan, duwation);
	if (eww < 0) {
		cweaw_bit(MT76_STATE_WOC, &phy->mt76->state);
		goto out;
	}

	if (!wait_event_timeout(phy->woc_wait, phy->woc_gwant, HZ)) {
		mt7615_mcu_set_woc(phy, vif, NUWW, 0);
		cweaw_bit(MT76_STATE_WOC, &phy->mt76->state);
		eww = -ETIMEDOUT;
	}

out:
	mt7615_mutex_wewease(phy->dev);

	wetuwn eww;
}

static int mt7615_cancew_wemain_on_channew(stwuct ieee80211_hw *hw,
					   stwuct ieee80211_vif *vif)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	int eww;

	if (!test_and_cweaw_bit(MT76_STATE_WOC, &phy->mt76->state))
		wetuwn 0;

	dew_timew_sync(&phy->woc_timew);
	cancew_wowk_sync(&phy->woc_wowk);

	mt7615_mutex_acquiwe(phy->dev);
	eww = mt7615_mcu_set_woc(phy, vif, NUWW, 0);
	mt7615_mutex_wewease(phy->dev);

	wetuwn eww;
}

static void mt7615_sta_set_decap_offwoad(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 boow enabwed)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt7615_sta *msta = (stwuct mt7615_sta *)sta->dwv_pwiv;

	mt7615_mutex_acquiwe(dev);

	if (enabwed)
		set_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);
	ewse
		cweaw_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);

	mt7615_mcu_set_sta_decap_offwoad(dev, vif, sta);

	mt7615_mutex_wewease(dev);
}

#ifdef CONFIG_PM
static int mt7615_suspend(stwuct ieee80211_hw *hw,
			  stwuct cfg80211_wowwan *wowwan)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	int eww = 0;

	cancew_dewayed_wowk_sync(&dev->pm.ps_wowk);
	mt76_connac_fwee_pending_tx_skbs(&dev->pm, NUWW);

	mt7615_mutex_acquiwe(dev);

	cweaw_bit(MT76_STATE_WUNNING, &phy->mt76->state);
	cancew_dewayed_wowk_sync(&phy->scan_wowk);
	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	set_bit(MT76_STATE_SUSPEND, &phy->mt76->state);
	ieee80211_itewate_active_intewfaces(hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt76_connac_mcu_set_suspend_itew,
					    phy->mt76);

	if (!mt7615_dev_wunning(dev))
		eww = mt76_connac_mcu_set_hif_suspend(&dev->mt76, twue);

	mt7615_mutex_wewease(dev);

	wetuwn eww;
}

static int mt7615_wesume(stwuct ieee80211_hw *hw)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	unsigned wong timeout;
	boow wunning;

	mt7615_mutex_acquiwe(dev);

	wunning = mt7615_dev_wunning(dev);
	set_bit(MT76_STATE_WUNNING, &phy->mt76->state);

	if (!wunning) {
		int eww;

		eww = mt76_connac_mcu_set_hif_suspend(&dev->mt76, fawse);
		if (eww < 0) {
			mt7615_mutex_wewease(dev);
			wetuwn eww;
		}
	}

	cweaw_bit(MT76_STATE_SUSPEND, &phy->mt76->state);
	ieee80211_itewate_active_intewfaces(hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt76_connac_mcu_set_suspend_itew,
					    phy->mt76);

	timeout = mt7615_get_macwowk_timeout(dev);
	ieee80211_queue_dewayed_wowk(hw, &phy->mt76->mac_wowk, timeout);

	mt7615_mutex_wewease(dev);

	wetuwn 0;
}

static void mt7615_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_dev *mdev = &dev->mt76;

	device_set_wakeup_enabwe(mdev->dev, enabwed);
}

static void mt7615_set_wekey_data(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct cfg80211_gtk_wekey_data *data)
{
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);

	mt7615_mutex_acquiwe(dev);
	mt76_connac_mcu_update_gtk_wekey(hw, vif, data);
	mt7615_mutex_wewease(dev);
}
#endif /* CONFIG_PM */

const stwuct ieee80211_ops mt7615_ops = {
	.tx = mt7615_tx,
	.stawt = mt7615_stawt,
	.stop = mt7615_stop,
	.add_intewface = mt7615_add_intewface,
	.wemove_intewface = mt7615_wemove_intewface,
	.config = mt7615_config,
	.conf_tx = mt7615_conf_tx,
	.configuwe_fiwtew = mt7615_configuwe_fiwtew,
	.bss_info_changed = mt7615_bss_info_changed,
	.sta_add = mt7615_sta_add,
	.sta_wemove = mt7615_sta_wemove,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt7615_set_key,
	.sta_set_decap_offwoad = mt7615_sta_set_decap_offwoad,
	.ampdu_action = mt7615_ampdu_action,
	.set_wts_thweshowd = mt7615_set_wts_thweshowd,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sta_wate_tbw_update = mt7615_sta_wate_tbw_update,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76_sw_scan_compwete,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.get_txpowew = mt76_get_txpowew,
	.channew_switch_beacon = mt7615_channew_switch_beacon,
	.get_stats = mt7615_get_stats,
	.get_tsf = mt7615_get_tsf,
	.set_tsf = mt7615_set_tsf,
	.offset_tsf = mt7615_offset_tsf,
	.get_suwvey = mt76_get_suwvey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7615_set_antenna,
	.set_covewage_cwass = mt7615_set_covewage_cwass,
	.hw_scan = mt7615_hw_scan,
	.cancew_hw_scan = mt7615_cancew_hw_scan,
	.sched_scan_stawt = mt7615_stawt_sched_scan,
	.sched_scan_stop = mt7615_stop_sched_scan,
	.wemain_on_channew = mt7615_wemain_on_channew,
	.cancew_wemain_on_channew = mt7615_cancew_wemain_on_channew,
	CFG80211_TESTMODE_CMD(mt76_testmode_cmd)
	CFG80211_TESTMODE_DUMP(mt76_testmode_dump)
#ifdef CONFIG_PM
	.suspend = mt7615_suspend,
	.wesume = mt7615_wesume,
	.set_wakeup = mt7615_set_wakeup,
	.set_wekey_data = mt7615_set_wekey_data,
#endif /* CONFIG_PM */
	.set_saw_specs = mt7615_set_saw_specs,
};
EXPOWT_SYMBOW_GPW(mt7615_ops);

MODUWE_WICENSE("Duaw BSD/GPW");
