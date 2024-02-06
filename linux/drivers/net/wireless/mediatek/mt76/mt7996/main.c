// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude "mt7996.h"
#incwude "mcu.h"
#incwude "mac.h"

static boow mt7996_dev_wunning(stwuct mt7996_dev *dev)
{
	stwuct mt7996_phy *phy;

	if (test_bit(MT76_STATE_WUNNING, &dev->mphy.state))
		wetuwn twue;

	phy = mt7996_phy2(dev);
	if (phy && test_bit(MT76_STATE_WUNNING, &phy->mt76->state))
		wetuwn twue;

	phy = mt7996_phy3(dev);

	wetuwn phy && test_bit(MT76_STATE_WUNNING, &phy->mt76->state);
}

int mt7996_wun(stwuct ieee80211_hw *hw)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	boow wunning;
	int wet;

	wunning = mt7996_dev_wunning(dev);
	if (!wunning) {
		wet = mt7996_mcu_set_hdw_twans(dev, twue);
		if (wet)
			goto out;
	}

	mt7996_mac_enabwe_nf(dev, phy->mt76->band_idx);

	wet = mt7996_mcu_set_wts_thwesh(phy, 0x92b);
	if (wet)
		goto out;

	wet = mt7996_mcu_set_wadio_en(phy, twue);
	if (wet)
		goto out;

	wet = mt7996_mcu_set_chan_info(phy, UNI_CHANNEW_WX_PATH);
	if (wet)
		goto out;

	wet = mt7996_mcu_set_thewmaw_thwottwing(phy, MT7996_THEWMAW_THWOTTWE_MAX);
	if (wet)
		goto out;

	wet = mt7996_mcu_set_thewmaw_pwotect(phy, twue);
	if (wet)
		goto out;

	set_bit(MT76_STATE_WUNNING, &phy->mt76->state);

	ieee80211_queue_dewayed_wowk(hw, &phy->mt76->mac_wowk,
				     MT7996_WATCHDOG_TIME);

	if (!wunning)
		mt7996_mac_weset_countews(phy);

out:
	wetuwn wet;
}

static int mt7996_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	int wet;

	fwush_wowk(&dev->init_wowk);

	mutex_wock(&dev->mt76.mutex);
	wet = mt7996_wun(hw);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void mt7996_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	mutex_wock(&dev->mt76.mutex);

	mt7996_mcu_set_wadio_en(phy, fawse);

	cweaw_bit(MT76_STATE_WUNNING, &phy->mt76->state);

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

static void mt7996_init_bitwate_mask(stwuct ieee80211_vif *vif)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
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

static int mt7996_add_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt76_txq *mtxq;
	u8 band_idx = phy->mt76->band_idx;
	int idx, wet = 0;

	mutex_wock(&dev->mt76.mutex);

	if (vif->type == NW80211_IFTYPE_MONITOW &&
	    is_zewo_ethew_addw(vif->addw))
		phy->monitow_vif = vif;

	mvif->mt76.idx = __ffs64(~dev->mt76.vif_mask);
	if (mvif->mt76.idx >= mt7996_max_intewface_num(dev)) {
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
	mvif->mt76.band_idx = band_idx;
	mvif->mt76.wmm_idx = vif->type != NW80211_IFTYPE_AP;

	wet = mt7996_mcu_add_dev_info(phy, vif, twue);
	if (wet)
		goto out;

	dev->mt76.vif_mask |= BIT_UWW(mvif->mt76.idx);
	phy->omac_mask |= BIT_UWW(mvif->mt76.omac_idx);

	idx = MT7996_WTBW_WESEWVED - mvif->mt76.idx;

	INIT_WIST_HEAD(&mvif->sta.wc_wist);
	INIT_WIST_HEAD(&mvif->sta.wcid.poww_wist);
	mvif->sta.wcid.idx = idx;
	mvif->sta.wcid.phy_idx = band_idx;
	mvif->sta.wcid.hw_key_idx = -1;
	mvif->sta.wcid.tx_info |= MT_WCID_TX_INFO_SET;
	mt76_wcid_init(&mvif->sta.wcid);

	mt7996_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	if (vif->txq) {
		mtxq = (stwuct mt76_txq *)vif->txq->dwv_pwiv;
		mtxq->wcid = idx;
	}

	if (vif->type != NW80211_IFTYPE_AP &&
	    (!mvif->mt76.omac_idx || mvif->mt76.omac_idx > 3))
		vif->offwoad_fwags = 0;
	vif->offwoad_fwags |= IEEE80211_OFFWOAD_ENCAP_4ADDW;

	if (phy->mt76->chandef.chan->band != NW80211_BAND_2GHZ)
		mvif->mt76.basic_wates_idx = MT7996_BASIC_WATES_TBW + 4;
	ewse
		mvif->mt76.basic_wates_idx = MT7996_BASIC_WATES_TBW;

	mt7996_init_bitwate_mask(vif);

	mt7996_mcu_add_bss_info(phy, vif, twue);
	mt7996_mcu_add_sta(dev, vif, NUWW, twue);
	wcu_assign_pointew(dev->mt76.wcid[idx], &mvif->sta.wcid);

out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void mt7996_wemove_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_sta *msta = &mvif->sta;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	int idx = msta->wcid.idx;

	mt7996_mcu_add_sta(dev, vif, NUWW, fawse);
	mt7996_mcu_add_bss_info(phy, vif, fawse);

	if (vif == phy->monitow_vif)
		phy->monitow_vif = NUWW;

	mt7996_mcu_add_dev_info(phy, vif, fawse);

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

int mt7996_set_channew(stwuct mt7996_phy *phy)
{
	stwuct mt7996_dev *dev = phy->dev;
	int wet;

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	mutex_wock(&dev->mt76.mutex);
	set_bit(MT76_WESET, &phy->mt76->state);

	mt76_set_channew(phy->mt76);

	wet = mt7996_mcu_set_chan_info(phy, UNI_CHANNEW_SWITCH);
	if (wet)
		goto out;

	wet = mt7996_dfs_init_wadaw_detectow(phy);
	mt7996_mac_cca_stats_weset(phy);

	mt7996_mac_weset_countews(phy);
	phy->noise = 0;

out:
	cweaw_bit(MT76_WESET, &phy->mt76->state);
	mutex_unwock(&dev->mt76.mutex);

	mt76_txq_scheduwe_aww(phy->mt76);

	ieee80211_queue_dewayed_wowk(phy->mt76->hw,
				     &phy->mt76->mac_wowk,
				     MT7996_WATCHDOG_TIME);

	wetuwn wet;
}

static int mt7996_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_sta *msta = sta ? (stwuct mt7996_sta *)sta->dwv_pwiv :
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
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&dev->mt76.mutex);

	if (cmd == SET_KEY && !sta && !mvif->mt76.ciphew) {
		mvif->mt76.ciphew = mt76_connac_mcu_get_ciphew(key->ciphew);
		mt7996_mcu_add_bss_info(phy, vif, twue);
	}

	if (cmd == SET_KEY) {
		*wcid_keyidx = idx;
	} ewse {
		if (idx == *wcid_keyidx)
			*wcid_keyidx = -1;
		goto out;
	}

	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	if (key->keyidx == 6 || key->keyidx == 7)
		eww = mt7996_mcu_bcn_pwot_enabwe(dev, vif, key);
	ewse
		eww = mt7996_mcu_add_key(&dev->mt76, vif, key,
					 MCU_WMWA_UNI_CMD(STA_WEC_UPDATE),
					 &msta->wcid, cmd);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn eww;
}

static int mt7996_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	int wet;

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		ieee80211_stop_queues(hw);
		wet = mt7996_set_channew(phy);
		if (wet)
			wetuwn wet;
		ieee80211_wake_queues(hw);
	}

	if (changed & (IEEE80211_CONF_CHANGE_POWEW |
		       IEEE80211_CONF_CHANGE_CHANNEW)) {
		wet = mt7996_mcu_set_txpowew_sku(phy);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		boow enabwed = !!(hw->conf.fwags & IEEE80211_CONF_MONITOW);

		if (!enabwed)
			phy->wxfiwtew |= MT_WF_WFCW_DWOP_OTHEW_UC;
		ewse
			phy->wxfiwtew &= ~MT_WF_WFCW_DWOP_OTHEW_UC;

		mt76_wmw_fiewd(dev, MT_DMA_DCW0(phy->mt76->band_idx),
			       MT_DMA_DCW0_WXD_G5_EN, enabwed);
		mt76_ww(dev, MT_WF_WFCW(phy->mt76->band_idx), phy->wxfiwtew);
	}

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static int
mt7996_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       unsigned int wink_id, u16 queue,
	       const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	const u8 mq_to_aci[] = {
		[IEEE80211_AC_VO] = 3,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
	};

	/* fiwmwawe uses access cwass index */
	mvif->queue_pawams[mq_to_aci[queue]] = *pawams;
	/* no need to update wight away, we'ww get BSS_CHANGED_QOS */

	wetuwn 0;
}

static void mt7996_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed_fwags,
				    unsigned int *totaw_fwags,
				    u64 muwticast)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	u32 ctw_fwags = MT_WF_WFCW1_DWOP_ACK |
			MT_WF_WFCW1_DWOP_BF_POWW |
			MT_WF_WFCW1_DWOP_BA |
			MT_WF_WFCW1_DWOP_CFEND |
			MT_WF_WFCW1_DWOP_CFACK;
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
	mt76_ww(dev, MT_WF_WFCW(phy->mt76->band_idx), phy->wxfiwtew);

	if (*totaw_fwags & FIF_CONTWOW)
		mt76_cweaw(dev, MT_WF_WFCW1(phy->mt76->band_idx), ctw_fwags);
	ewse
		mt76_set(dev, MT_WF_WFCW1(phy->mt76->band_idx), ctw_fwags);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7996_update_bss_cowow(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct cfg80211_he_bss_cowow *bss_cowow)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);

	switch (vif->type) {
	case NW80211_IFTYPE_AP: {
		stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;

		if (mvif->mt76.omac_idx > HW_BSSID_MAX)
			wetuwn;
		fawwthwough;
	}
	case NW80211_IFTYPE_STATION:
		mt7996_mcu_update_bss_cowow(dev, vif, bss_cowow);
		bweak;
	defauwt:
		bweak;
	}
}

static u8
mt7996_get_wates_tabwe(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       boow beacon, boow mcast)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_phy *mphy = hw->pwiv;
	u16 wate;
	u8 i, idx;

	wate = mt76_connac2_mac_tx_wate_vaw(mphy, vif, beacon, mcast);

	if (beacon) {
		stwuct mt7996_phy *phy = mphy->pwiv;

		/* odd index fow dwivew, even index fow fiwmwawe */
		idx = MT7996_BEACON_WATES_TBW + 2 * phy->mt76->band_idx;
		if (phy->beacon_wate != wate)
			mt7996_mcu_set_fixed_wate_tabwe(phy, idx, wate, beacon);

		wetuwn idx;
	}

	idx = FIEWD_GET(MT_TX_WATE_IDX, wate);
	fow (i = 0; i < AWWAY_SIZE(mt76_wates); i++)
		if ((mt76_wates[i].hw_vawue & GENMASK(7, 0)) == idx)
			wetuwn MT7996_BASIC_WATES_TBW + 2 * i;

	wetuwn mvif->basic_wates_idx;
}

static void
mt7996_update_mu_gwoup(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_bss_conf *info)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	u8 band = mvif->mt76.band_idx;
	u32 *mu;

	mu = (u32 *)info->mu_gwoup.membewship;
	mt76_ww(dev, MT_WF_PHYWX_BAND_GID_TAB_VWD0(band), mu[0]);
	mt76_ww(dev, MT_WF_PHYWX_BAND_GID_TAB_VWD1(band), mu[1]);

	mu = (u32 *)info->mu_gwoup.position;
	mt76_ww(dev, MT_WF_PHYWX_BAND_GID_TAB_POS0(band), mu[0]);
	mt76_ww(dev, MT_WF_PHYWX_BAND_GID_TAB_POS1(band), mu[1]);
	mt76_ww(dev, MT_WF_PHYWX_BAND_GID_TAB_POS2(band), mu[2]);
	mt76_ww(dev, MT_WF_PHYWX_BAND_GID_TAB_POS3(band), mu[3]);
}

static void mt7996_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *info,
				    u64 changed)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);

	mutex_wock(&dev->mt76.mutex);

	/* station mode uses BSSID to map the wwan entwy to a peew,
	 * and then peew wefewences bss_info_wfch to set bandwidth cap.
	 */
	if ((changed & BSS_CHANGED_BSSID && !is_zewo_ethew_addw(info->bssid)) ||
	    (changed & BSS_CHANGED_ASSOC && vif->cfg.assoc) ||
	    (changed & BSS_CHANGED_BEACON_ENABWED && info->enabwe_beacon)) {
		mt7996_mcu_add_bss_info(phy, vif, twue);
		mt7996_mcu_add_sta(dev, vif, NUWW, twue);
	}

	if (changed & BSS_CHANGED_EWP_CTS_PWOT)
		mt7996_mac_enabwe_wtscts(dev, vif, info->use_cts_pwot);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		int swottime = info->use_showt_swot ? 9 : 20;

		if (swottime != phy->swottime) {
			phy->swottime = swottime;
			mt7996_mcu_set_timing(phy, vif);
		}
	}

	if (changed & BSS_CHANGED_MCAST_WATE)
		mvif->mcast_wates_idx =
			mt7996_get_wates_tabwe(hw, vif, fawse, twue);

	if (changed & BSS_CHANGED_BASIC_WATES)
		mvif->basic_wates_idx =
			mt7996_get_wates_tabwe(hw, vif, fawse, fawse);

	/* ensuwe that enabwe txcmd_mode aftew bss_info */
	if (changed & (BSS_CHANGED_QOS | BSS_CHANGED_BEACON_ENABWED))
		mt7996_mcu_set_tx(dev, vif);

	if (changed & BSS_CHANGED_HE_OBSS_PD)
		mt7996_mcu_add_obss_spw(phy, vif, &info->he_obss_pd);

	if (changed & BSS_CHANGED_HE_BSS_COWOW)
		mt7996_update_bss_cowow(hw, vif, &info->he_bss_cowow);

	if (changed & (BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_ENABWED)) {
		mvif->beacon_wates_idx =
			mt7996_get_wates_tabwe(hw, vif, twue, fawse);

		mt7996_mcu_add_beacon(hw, vif, info->enabwe_beacon);
	}

	if (changed & (BSS_CHANGED_UNSOW_BCAST_PWOBE_WESP |
		       BSS_CHANGED_FIWS_DISCOVEWY))
		mt7996_mcu_beacon_inband_discov(dev, vif, changed);

	if (changed & BSS_CHANGED_MU_GWOUPS)
		mt7996_update_mu_gwoup(hw, vif, info);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7996_channew_switch_beacon(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct cfg80211_chan_def *chandef)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);

	mutex_wock(&dev->mt76.mutex);
	mt7996_mcu_add_beacon(hw, vif, twue);
	mutex_unwock(&dev->mt76.mutex);
}

int mt7996_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	u8 band_idx = mvif->phy->mt76->band_idx;
	int wet, idx;

	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7996_WTBW_STA);
	if (idx < 0)
		wetuwn -ENOSPC;

	INIT_WIST_HEAD(&msta->wc_wist);
	INIT_WIST_HEAD(&msta->wcid.poww_wist);
	msta->vif = mvif;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.phy_idx = band_idx;
	msta->wcid.tx_info |= MT_WCID_TX_INFO_SET;

	ewma_avg_signaw_init(&msta->avg_ack_signaw);

	mt7996_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	wet = mt7996_mcu_add_sta(dev, vif, sta, twue);
	if (wet)
		wetuwn wet;

	wetuwn mt7996_mcu_add_wate_ctww(dev, vif, sta, fawse);
}

void mt7996_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
	int i;

	mt7996_mcu_add_sta(dev, vif, sta, fawse);

	mt7996_mac_wtbw_update(dev, msta->wcid.idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	fow (i = 0; i < AWWAY_SIZE(msta->twt.fwow); i++)
		mt7996_mac_twt_teawdown_fwow(dev, msta, i);

	spin_wock_bh(&mdev->sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	if (!wist_empty(&msta->wc_wist))
		wist_dew_init(&msta->wc_wist);
	spin_unwock_bh(&mdev->sta_poww_wock);
}

static void mt7996_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_tx_contwow *contwow,
		      stwuct sk_buff *skb)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;

	if (contwow->sta) {
		stwuct mt7996_sta *sta;

		sta = (stwuct mt7996_sta *)contwow->sta->dwv_pwiv;
		wcid = &sta->wcid;
	}

	if (vif && !contwow->sta) {
		stwuct mt7996_vif *mvif;

		mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
		wcid = &mvif->sta.wcid;
	}

	mt76_tx(mphy, contwow->sta, wcid, skb);
}

static int mt7996_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vaw)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	int wet;

	mutex_wock(&phy->dev->mt76.mutex);
	wet = mt7996_mcu_set_wts_thwesh(phy, vaw);
	mutex_unwock(&phy->dev->mt76.mutex);

	wetuwn wet;
}

static int
mt7996_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct ieee80211_txq *txq = sta->txq[pawams->tid];
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
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
		wet = mt7996_mcu_add_wx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mt76_wx_aggw_stop(&dev->mt76, &msta->wcid, tid);
		wet = mt7996_mcu_add_wx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mtxq->aggw = twue;
		mtxq->send_baw = fawse;
		wet = mt7996_mcu_add_tx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mtxq->aggw = fawse;
		cweaw_bit(tid, &msta->wcid.ampdu_state);
		wet = mt7996_mcu_add_tx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		set_bit(tid, &msta->wcid.ampdu_state);
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggw = fawse;
		cweaw_bit(tid, &msta->wcid.ampdu_state);
		wet = mt7996_mcu_add_tx_ba(dev, pawams, fawse);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	}
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static int
mt7996_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_sta *sta)
{
	wetuwn mt76_sta_state(hw, vif, sta, IEEE80211_STA_NOTEXIST,
			      IEEE80211_STA_NONE);
}

static int
mt7996_sta_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  stwuct ieee80211_sta *sta)
{
	wetuwn mt76_sta_state(hw, vif, sta, IEEE80211_STA_NONE,
			      IEEE80211_STA_NOTEXIST);
}

static int
mt7996_get_stats(stwuct ieee80211_hw *hw,
		 stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt76_mib_stats *mib = &phy->mib;

	mutex_wock(&dev->mt76.mutex);

	stats->dot11WTSSuccessCount = mib->wts_cnt;
	stats->dot11WTSFaiwuweCount = mib->wts_wetwies_cnt;
	stats->dot11FCSEwwowCount = mib->fcs_eww_cnt;
	stats->dot11ACKFaiwuweCount = mib->ack_faiw_cnt;

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

u64 __mt7996_get_tsf(stwuct ieee80211_hw *hw, stwuct mt7996_vif *mvif)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	union {
		u64 t64;
		u32 t32[2];
	} tsf;
	u16 n;

	wockdep_assewt_hewd(&dev->mt76.mutex);

	n = mvif->mt76.omac_idx > HW_BSSID_MAX ? HW_BSSID_0
					       : mvif->mt76.omac_idx;
	/* TSF softwawe wead */
	mt76_wmw(dev, MT_WPON_TCW(phy->mt76->band_idx, n), MT_WPON_TCW_SW_MODE,
		 MT_WPON_TCW_SW_WEAD);
	tsf.t32[0] = mt76_ww(dev, MT_WPON_UTTW0(phy->mt76->band_idx));
	tsf.t32[1] = mt76_ww(dev, MT_WPON_UTTW1(phy->mt76->band_idx));

	wetuwn tsf.t64;
}

static u64
mt7996_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	u64 wet;

	mutex_wock(&dev->mt76.mutex);
	wet = __mt7996_get_tsf(hw, mvif);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}

static void
mt7996_set_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       u64 timestamp)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	union {
		u64 t64;
		u32 t32[2];
	} tsf = { .t64 = timestamp, };
	u16 n;

	mutex_wock(&dev->mt76.mutex);

	n = mvif->mt76.omac_idx > HW_BSSID_MAX ? HW_BSSID_0
					       : mvif->mt76.omac_idx;
	mt76_ww(dev, MT_WPON_UTTW0(phy->mt76->band_idx), tsf.t32[0]);
	mt76_ww(dev, MT_WPON_UTTW1(phy->mt76->band_idx), tsf.t32[1]);
	/* TSF softwawe ovewwwite */
	mt76_wmw(dev, MT_WPON_TCW(phy->mt76->band_idx, n), MT_WPON_TCW_SW_MODE,
		 MT_WPON_TCW_SW_WWITE);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7996_offset_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  s64 timestamp)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	union {
		u64 t64;
		u32 t32[2];
	} tsf = { .t64 = timestamp, };
	u16 n;

	mutex_wock(&dev->mt76.mutex);

	n = mvif->mt76.omac_idx > HW_BSSID_MAX ? HW_BSSID_0
					       : mvif->mt76.omac_idx;
	mt76_ww(dev, MT_WPON_UTTW0(phy->mt76->band_idx), tsf.t32[0]);
	mt76_ww(dev, MT_WPON_UTTW1(phy->mt76->band_idx), tsf.t32[1]);
	/* TSF softwawe adjust*/
	mt76_wmw(dev, MT_WPON_TCW(phy->mt76->band_idx, n), MT_WPON_TCW_SW_MODE,
		 MT_WPON_TCW_SW_ADJUST);

	mutex_unwock(&dev->mt76.mutex);
}

static void
mt7996_set_covewage_cwass(stwuct ieee80211_hw *hw, s16 covewage_cwass)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_dev *dev = phy->dev;

	mutex_wock(&dev->mt76.mutex);
	phy->covewage_cwass = max_t(s16, covewage_cwass, 0);
	mt7996_mac_set_covewage_cwass(phy);
	mutex_unwock(&dev->mt76.mutex);
}

static int
mt7996_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	int max_nss = hweight8(hw->wiphy->avaiwabwe_antennas_tx);
	u8 band_idx = phy->mt76->band_idx, shift = dev->chainshift[band_idx];

	if (!tx_ant || tx_ant != wx_ant || ffs(tx_ant) > max_nss)
		wetuwn -EINVAW;

	if ((BIT(hweight8(tx_ant)) - 1) != tx_ant)
		tx_ant = BIT(ffs(tx_ant) - 1) - 1;

	mutex_wock(&dev->mt76.mutex);

	phy->mt76->antenna_mask = tx_ant;

	/* westowe to the owigin chainmask which might have auxiwiawy path */
	if (hweight8(tx_ant) == max_nss && band_idx < MT_BAND2)
		phy->mt76->chainmask = ((dev->chainmask >> shift) &
					(BIT(dev->chainshift[band_idx + 1] - shift) - 1)) << shift;
	ewse if (hweight8(tx_ant) == max_nss)
		phy->mt76->chainmask = (dev->chainmask >> shift) << shift;
	ewse
		phy->mt76->chainmask = tx_ant << shift;

	mt76_set_stweam_caps(phy->mt76, twue);
	mt7996_set_stweam_vht_txbf_caps(phy);
	mt7996_set_stweam_he_eht_caps(phy);
	mt7996_mcu_set_txpowew_sku(phy);

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

static void mt7996_sta_statistics(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_sta *sta,
				  stwuct station_info *sinfo)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
	stwuct wate_info *txwate = &msta->wcid.wate;

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
			sinfo->txwate.eht_gi = txwate->eht_gi;
		}
		sinfo->txwate.fwags = txwate->fwags;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
	}
	sinfo->txwate.fwags = txwate->fwags;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);

	sinfo->tx_faiwed = msta->wcid.stats.tx_faiwed;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_FAIWED);

	sinfo->tx_wetwies = msta->wcid.stats.tx_wetwies;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_WETWIES);

	sinfo->ack_signaw = (s8)msta->ack_signaw;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW);

	sinfo->avg_ack_signaw = -(s8)ewma_avg_signaw_wead(&msta->avg_ack_signaw);
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW_AVG);

	if (mtk_wed_device_active(&phy->dev->mt76.mmio.wed)) {
		sinfo->tx_bytes = msta->wcid.stats.tx_bytes;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BYTES64);

		sinfo->wx_bytes = msta->wcid.stats.wx_bytes;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BYTES64);

		sinfo->tx_packets = msta->wcid.stats.tx_packets;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_PACKETS);

		sinfo->wx_packets = msta->wcid.stats.wx_packets;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_PACKETS);
	}
}

static void mt7996_sta_wc_wowk(void *data, stwuct ieee80211_sta *sta)
{
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
	stwuct mt7996_dev *dev = msta->vif->phy->dev;
	u32 *changed = data;

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	msta->changed |= *changed;
	if (wist_empty(&msta->wc_wist))
		wist_add_taiw(&msta->wc_wist, &dev->sta_wc_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);
}

static void mt7996_sta_wc_update(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 u32 changed)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_dev *dev = phy->dev;

	mt7996_sta_wc_wowk(&changed, sta);
	ieee80211_queue_wowk(hw, &dev->wc_wowk);
}

static int
mt7996_set_bitwate_mask(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			const stwuct cfg80211_bitwate_mask *mask)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_dev *dev = phy->dev;
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
	ieee80211_itewate_stations_atomic(hw, mt7996_sta_wc_wowk, &changed);
	ieee80211_queue_wowk(hw, &dev->wc_wowk);

	wetuwn 0;
}

static void mt7996_sta_set_4addw(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 boow enabwed)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;

	if (enabwed)
		set_bit(MT_WCID_FWAG_4ADDW, &msta->wcid.fwags);
	ewse
		cweaw_bit(MT_WCID_FWAG_4ADDW, &msta->wcid.fwags);

	mt7996_mcu_wtbw_update_hdw_twans(dev, vif, sta);
}

static void mt7996_sta_set_decap_offwoad(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_sta *sta,
					 boow enabwed)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;

	if (enabwed)
		set_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);
	ewse
		cweaw_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);

	mt7996_mcu_wtbw_update_hdw_twans(dev, vif, sta);
}

static const chaw mt7996_gstwings_stats[][ETH_GSTWING_WEN] = {
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
	"wx_vectow_mismatch_cnt",
	"wx_dewimitew_faiw_cnt",
	"wx_wen_mismatch_cnt",
	"wx_ampdu_cnt",
	"wx_ampdu_bytes_cnt",
	"wx_ampdu_vawid_subfwame_cnt",
	"wx_ampdu_vawid_subfwame_b_cnt",
	"wx_pfdwop_cnt",
	"wx_vec_queue_ovewfwow_dwop_cnt",
	"wx_ba_cnt",

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
	"v_tx_mode_eht_su",
	"v_tx_mode_eht_twig",
	"v_tx_mode_eht_mu",
	"v_tx_bw_20",
	"v_tx_bw_40",
	"v_tx_bw_80",
	"v_tx_bw_160",
	"v_tx_bw_320",
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
	"v_tx_mcs_12",
	"v_tx_mcs_13",
	"v_tx_nss_1",
	"v_tx_nss_2",
	"v_tx_nss_3",
	"v_tx_nss_4",
};

#define MT7996_SSTATS_WEN AWWAY_SIZE(mt7996_gstwings_stats)

/* Ethtoow wewated API */
static
void mt7996_get_et_stwings(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   u32 sset, u8 *data)
{
	if (sset == ETH_SS_STATS)
		memcpy(data, mt7996_gstwings_stats,
		       sizeof(mt7996_gstwings_stats));
}

static
int mt7996_get_et_sset_count(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif, int sset)
{
	if (sset == ETH_SS_STATS)
		wetuwn MT7996_SSTATS_WEN;

	wetuwn 0;
}

static void mt7996_ethtoow_wowkew(void *wi_data, stwuct ieee80211_sta *sta)
{
	stwuct mt76_ethtoow_wowkew_info *wi = wi_data;
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;

	if (msta->vif->mt76.idx != wi->idx)
		wetuwn;

	mt76_ethtoow_wowkew(wi, &msta->wcid.stats, twue);
}

static
void mt7996_get_et_stats(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt76_mib_stats *mib = &phy->mib;
	stwuct mt76_ethtoow_wowkew_info wi = {
		.data = data,
		.idx = mvif->mt76.idx,
	};
	/* See mt7996_ampdu_stat_wead_phy, etc */
	int i, ei = 0;

	mutex_wock(&dev->mt76.mutex);

	mt7996_mac_update_stats(phy);

	data[ei++] = mib->tx_ampdu_cnt;
	data[ei++] = mib->tx_stop_q_empty_cnt;
	data[ei++] = mib->tx_mpdu_attempts_cnt;
	data[ei++] = mib->tx_mpdu_success_cnt;
	data[ei++] = mib->tx_wwp_faiw_cnt;
	data[ei++] = mib->tx_wwp_need_cnt;
	data[ei++] = mib->tx_bf_ebf_ppdu_cnt;
	data[ei++] = mib->tx_bf_ibf_ppdu_cnt;

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
	data[ei++] = mib->tx_mu_bf_cnt;
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
	data[ei++] = mib->wx_vectow_mismatch_cnt;
	data[ei++] = mib->wx_dewimitew_faiw_cnt;
	data[ei++] = mib->wx_wen_mismatch_cnt;
	data[ei++] = mib->wx_ampdu_cnt;
	data[ei++] = mib->wx_ampdu_bytes_cnt;
	data[ei++] = mib->wx_ampdu_vawid_subfwame_cnt;
	data[ei++] = mib->wx_ampdu_vawid_subfwame_bytes_cnt;
	data[ei++] = mib->wx_pfdwop_cnt;
	data[ei++] = mib->wx_vec_queue_ovewfwow_dwop_cnt;
	data[ei++] = mib->wx_ba_cnt;

	/* Add vawues fow aww stations owned by this vif */
	wi.initiaw_stat_idx = ei;
	ieee80211_itewate_stations_atomic(hw, mt7996_ethtoow_wowkew, &wi);

	mutex_unwock(&dev->mt76.mutex);

	if (wi.sta_count == 0)
		wetuwn;

	ei += wi.wowkew_stat_count;
	if (ei != MT7996_SSTATS_WEN)
		dev_eww(dev->mt76.dev, "ei: %d  MT7996_SSTATS_WEN: %d",
			ei, (int)MT7996_SSTATS_WEN);
}

static void
mt7996_twt_teawdown_wequest(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_sta *sta,
			    u8 fwowid)
{
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);

	mutex_wock(&dev->mt76.mutex);
	mt7996_mac_twt_teawdown_fwow(dev, msta, fwowid);
	mutex_unwock(&dev->mt76.mutex);
}

static int
mt7996_set_wadaw_backgwound(stwuct ieee80211_hw *hw,
			    stwuct cfg80211_chan_def *chandef)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt7996_dev *dev = phy->dev;
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
		wet = mt7996_mcu_wdd_backgwound_enabwe(phy, NUWW);
		if (wet)
			goto out;

		if (!wunning)
			goto update_phy;
	}

	wet = mt7996_mcu_wdd_backgwound_enabwe(phy, chandef);
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
mt7996_net_fiww_fowwawd_path(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta,
			     stwuct net_device_path_ctx *ctx,
			     stwuct net_device_path *path)
{
	stwuct mt7996_vif *mvif = (stwuct mt7996_vif *)vif->dwv_pwiv;
	stwuct mt7996_sta *msta = (stwuct mt7996_sta *)sta->dwv_pwiv;
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;

	if (phy != &dev->phy && phy->mt76->band_idx == MT_BAND2)
		wed = &dev->mt76.mmio.wed_hif2;

	if (!mtk_wed_device_active(wed))
		wetuwn -ENODEV;

	if (msta->wcid.idx > MT7996_WTBW_STA)
		wetuwn -EIO;

	path->type = DEV_PATH_MTK_WDMA;
	path->dev = ctx->dev;
	path->mtk_wdma.wdma_idx = wed->wdma_idx;
	path->mtk_wdma.bss = mvif->mt76.idx;
	path->mtk_wdma.queue = 0;
	path->mtk_wdma.wcid = msta->wcid.idx;

	path->mtk_wdma.amsdu = mtk_wed_is_amsdu_suppowted(wed);
	ctx->dev = NUWW;

	wetuwn 0;
}

#endif

const stwuct ieee80211_ops mt7996_ops = {
	.tx = mt7996_tx,
	.stawt = mt7996_stawt,
	.stop = mt7996_stop,
	.add_intewface = mt7996_add_intewface,
	.wemove_intewface = mt7996_wemove_intewface,
	.config = mt7996_config,
	.conf_tx = mt7996_conf_tx,
	.configuwe_fiwtew = mt7996_configuwe_fiwtew,
	.bss_info_changed = mt7996_bss_info_changed,
	.sta_add = mt7996_sta_add,
	.sta_wemove = mt7996_sta_wemove,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.sta_wc_update = mt7996_sta_wc_update,
	.set_key = mt7996_set_key,
	.ampdu_action = mt7996_ampdu_action,
	.set_wts_thweshowd = mt7996_set_wts_thweshowd,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76_sw_scan_compwete,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.get_txpowew = mt76_get_txpowew,
	.channew_switch_beacon = mt7996_channew_switch_beacon,
	.get_stats = mt7996_get_stats,
	.get_et_sset_count = mt7996_get_et_sset_count,
	.get_et_stats = mt7996_get_et_stats,
	.get_et_stwings = mt7996_get_et_stwings,
	.get_tsf = mt7996_get_tsf,
	.set_tsf = mt7996_set_tsf,
	.offset_tsf = mt7996_offset_tsf,
	.get_suwvey = mt76_get_suwvey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7996_set_antenna,
	.set_bitwate_mask = mt7996_set_bitwate_mask,
	.set_covewage_cwass = mt7996_set_covewage_cwass,
	.sta_statistics = mt7996_sta_statistics,
	.sta_set_4addw = mt7996_sta_set_4addw,
	.sta_set_decap_offwoad = mt7996_sta_set_decap_offwoad,
	.add_twt_setup = mt7996_mac_add_twt_setup,
	.twt_teawdown_wequest = mt7996_twt_teawdown_wequest,
#ifdef CONFIG_MAC80211_DEBUGFS
	.sta_add_debugfs = mt7996_sta_add_debugfs,
#endif
	.set_wadaw_backgwound = mt7996_set_wadaw_backgwound,
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	.net_fiww_fowwawd_path = mt7996_net_fiww_fowwawd_path,
	.net_setup_tc = mt76_net_setup_tc,
#endif
};
