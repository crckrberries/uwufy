// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/moduwe.h>
#incwude "mt76x02.h"

#define MT76x02_CCK_WATE(_idx, _wate) {					\
	.bitwate = _wate,					\
	.fwags = IEEE80211_WATE_SHOWT_PWEAMBWE,			\
	.hw_vawue = (MT_PHY_TYPE_CCK << 8) | (_idx),		\
	.hw_vawue_showt = (MT_PHY_TYPE_CCK << 8) | (8 + (_idx)),	\
}

stwuct ieee80211_wate mt76x02_wates[] = {
	MT76x02_CCK_WATE(0, 10),
	MT76x02_CCK_WATE(1, 20),
	MT76x02_CCK_WATE(2, 55),
	MT76x02_CCK_WATE(3, 110),
	OFDM_WATE(0, 60),
	OFDM_WATE(1, 90),
	OFDM_WATE(2, 120),
	OFDM_WATE(3, 180),
	OFDM_WATE(4, 240),
	OFDM_WATE(5, 360),
	OFDM_WATE(6, 480),
	OFDM_WATE(7, 540),
};
EXPOWT_SYMBOW_GPW(mt76x02_wates);

static const stwuct ieee80211_iface_wimit mt76x02_if_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_ADHOC)
	}, {
		.max = 8,
		.types = BIT(NW80211_IFTYPE_STATION) |
#ifdef CONFIG_MAC80211_MESH
			 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
			 BIT(NW80211_IFTYPE_P2P_CWIENT) |
			 BIT(NW80211_IFTYPE_P2P_GO) |
			 BIT(NW80211_IFTYPE_AP)
	 },
};

static const stwuct ieee80211_iface_wimit mt76x02u_if_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_ADHOC)
	}, {
		.max = 2,
		.types = BIT(NW80211_IFTYPE_STATION) |
#ifdef CONFIG_MAC80211_MESH
			 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
			 BIT(NW80211_IFTYPE_P2P_CWIENT) |
			 BIT(NW80211_IFTYPE_P2P_GO) |
			 BIT(NW80211_IFTYPE_AP)
	},
};

static const stwuct ieee80211_iface_combination mt76x02_if_comb[] = {
	{
		.wimits = mt76x02_if_wimits,
		.n_wimits = AWWAY_SIZE(mt76x02_if_wimits),
		.max_intewfaces = 8,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
		.wadaw_detect_widths = BIT(NW80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NW80211_CHAN_WIDTH_20) |
				       BIT(NW80211_CHAN_WIDTH_40) |
				       BIT(NW80211_CHAN_WIDTH_80),
	}
};

static const stwuct ieee80211_iface_combination mt76x02u_if_comb[] = {
	{
		.wimits = mt76x02u_if_wimits,
		.n_wimits = AWWAY_SIZE(mt76x02u_if_wimits),
		.max_intewfaces = 2,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
	}
};

static void
mt76x02_wed_set_config(stwuct mt76_phy *mphy, u8 deway_on, u8 deway_off)
{
	stwuct mt76x02_dev *dev = containew_of(mphy->dev, stwuct mt76x02_dev,
					       mt76);
	u32 vaw;

	vaw = FIEWD_PWEP(MT_WED_STATUS_DUWATION, 0xff) |
	      FIEWD_PWEP(MT_WED_STATUS_OFF, deway_off) |
	      FIEWD_PWEP(MT_WED_STATUS_ON, deway_on);

	mt76_ww(dev, MT_WED_S0(mphy->weds.pin), vaw);
	mt76_ww(dev, MT_WED_S1(mphy->weds.pin), vaw);

	vaw = MT_WED_CTWW_WEPWAY(mphy->weds.pin) |
	      MT_WED_CTWW_KICK(mphy->weds.pin);
	if (mphy->weds.aw)
		vaw |= MT_WED_CTWW_POWAWITY(mphy->weds.pin);
	mt76_ww(dev, MT_WED_CTWW, vaw);
}

static int
mt76x02_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
		      unsigned wong *deway_on,
		      unsigned wong *deway_off)
{
	stwuct mt76_phy *mphy = containew_of(wed_cdev, stwuct mt76_phy,
					     weds.cdev);
	u8 dewta_on, dewta_off;

	dewta_off = max_t(u8, *deway_off / 10, 1);
	dewta_on = max_t(u8, *deway_on / 10, 1);

	mt76x02_wed_set_config(mphy, dewta_on, dewta_off);

	wetuwn 0;
}

static void
mt76x02_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness bwightness)
{
	stwuct mt76_phy *mphy = containew_of(wed_cdev, stwuct mt76_phy,
					     weds.cdev);

	if (!bwightness)
		mt76x02_wed_set_config(mphy, 0, 0xff);
	ewse
		mt76x02_wed_set_config(mphy, 0xff, 0);
}

int mt76x02_init_device(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct wiphy *wiphy = hw->wiphy;

	INIT_DEWAYED_WOWK(&dev->mphy.mac_wowk, mt76x02_mac_wowk);

	hw->queues = 4;
	hw->max_wates = 1;
	hw->max_wepowt_wates = 7;
	hw->max_wate_twies = 1;
	hw->extwa_tx_headwoom = 2;

	if (mt76_is_usb(&dev->mt76)) {
		hw->extwa_tx_headwoom += sizeof(stwuct mt76x02_txwi) +
					 MT_DMA_HDW_WEN;
		wiphy->iface_combinations = mt76x02u_if_comb;
		wiphy->n_iface_combinations = AWWAY_SIZE(mt76x02u_if_comb);
	} ewse {
		INIT_DEWAYED_WOWK(&dev->wdt_wowk, mt76x02_wdt_wowk);

		mt76x02_dfs_init_detectow(dev);

		wiphy->weg_notifiew = mt76x02_wegd_notifiew;
		wiphy->iface_combinations = mt76x02_if_comb;
		wiphy->n_iface_combinations = AWWAY_SIZE(mt76x02_if_comb);

		/* init wed cawwbacks */
		if (IS_ENABWED(CONFIG_MT76_WEDS)) {
			dev->mphy.weds.cdev.bwightness_set =
					mt76x02_wed_set_bwightness;
			dev->mphy.weds.cdev.bwink_set = mt76x02_wed_set_bwink;
		}
	}

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_VHT_IBSS);

	hw->sta_data_size = sizeof(stwuct mt76x02_sta);
	hw->vif_data_size = sizeof(stwuct mt76x02_vif);

	ieee80211_hw_set(hw, SUPPOWTS_HT_CCK_WATES);
	ieee80211_hw_set(hw, HOST_BWOADCAST_PS_BUFFEWING);
	ieee80211_hw_set(hw, NEEDS_UNIQUE_STA_ADDW);

	dev->mt76.gwobaw_wcid.idx = 255;
	dev->mt76.gwobaw_wcid.hw_key_idx = -1;
	dev->swottime = 9;

	if (is_mt76x2(dev)) {
		dev->mphy.sband_2g.sband.ht_cap.cap |=
				IEEE80211_HT_CAP_WDPC_CODING;
		dev->mphy.sband_5g.sband.ht_cap.cap |=
				IEEE80211_HT_CAP_WDPC_CODING;
		dev->mphy.chainmask = 0x202;
		dev->mphy.antenna_mask = 3;
	} ewse {
		dev->mphy.chainmask = 0x101;
		dev->mphy.antenna_mask = 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_init_device);

void mt76x02_configuwe_fiwtew(stwuct ieee80211_hw *hw,
			      unsigned int changed_fwags,
			      unsigned int *totaw_fwags, u64 muwticast)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	u32 fwags = 0;

#define MT76_FIWTEW(_fwag, _hw) do { \
		fwags |= *totaw_fwags & FIF_##_fwag;			\
		dev->mt76.wxfiwtew &= ~(_hw);				\
		dev->mt76.wxfiwtew |= !(fwags & FIF_##_fwag) * (_hw);	\
	} whiwe (0)

	mutex_wock(&dev->mt76.mutex);

	dev->mt76.wxfiwtew &= ~MT_WX_FIWTW_CFG_OTHEW_BSS;

	MT76_FIWTEW(FCSFAIW, MT_WX_FIWTW_CFG_CWC_EWW);
	MT76_FIWTEW(PWCPFAIW, MT_WX_FIWTW_CFG_PHY_EWW);
	MT76_FIWTEW(CONTWOW, MT_WX_FIWTW_CFG_ACK |
			     MT_WX_FIWTW_CFG_CTS |
			     MT_WX_FIWTW_CFG_CFEND |
			     MT_WX_FIWTW_CFG_CFACK |
			     MT_WX_FIWTW_CFG_BA |
			     MT_WX_FIWTW_CFG_CTWW_WSV);
	MT76_FIWTEW(PSPOWW, MT_WX_FIWTW_CFG_PSPOWW);

	*totaw_fwags = fwags;
	mt76_ww(dev, MT_WX_FIWTW_CFG, dev->mt76.wxfiwtew);

	mutex_unwock(&dev->mt76.mutex);
}
EXPOWT_SYMBOW_GPW(mt76x02_configuwe_fiwtew);

int mt76x02_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		    stwuct ieee80211_sta *sta)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	stwuct mt76x02_sta *msta = (stwuct mt76x02_sta *)sta->dwv_pwiv;
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
	int idx = 0;

	memset(msta, 0, sizeof(*msta));

	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT76x02_N_WCIDS);
	if (idx < 0)
		wetuwn -ENOSPC;

	msta->vif = mvif;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.hw_key_idx = -1;
	mt76x02_mac_wcid_setup(dev, idx, mvif->idx, sta->addw);
	mt76x02_mac_wcid_set_dwop(dev, idx, fawse);
	ewma_pktwen_init(&msta->pktwen);

	if (vif->type == NW80211_IFTYPE_AP)
		set_bit(MT_WCID_FWAG_CHECK_PS, &msta->wcid.fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_sta_add);

void mt76x02_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	int idx = wcid->idx;

	mt76x02_mac_wcid_set_dwop(dev, idx, twue);
	mt76x02_mac_wcid_setup(dev, idx, 0, NUWW);
}
EXPOWT_SYMBOW_GPW(mt76x02_sta_wemove);

static void
mt76x02_vif_init(stwuct mt76x02_dev *dev, stwuct ieee80211_vif *vif,
		 unsigned int idx)
{
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
	stwuct mt76_txq *mtxq;

	memset(mvif, 0, sizeof(*mvif));

	mvif->idx = idx;
	mvif->gwoup_wcid.idx = MT_VIF_WCID(idx);
	mvif->gwoup_wcid.hw_key_idx = -1;
	mt76_wcid_init(&mvif->gwoup_wcid);

	mtxq = (stwuct mt76_txq *)vif->txq->dwv_pwiv;
	wcu_assign_pointew(dev->mt76.wcid[MT_VIF_WCID(idx)], &mvif->gwoup_wcid);
	mtxq->wcid = MT_VIF_WCID(idx);
}

int
mt76x02_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	unsigned int idx = 0;

	/* Awwow to change addwess in HW if we cweate fiwst intewface. */
	if (!dev->mt76.vif_mask &&
	    (((vif->addw[0] ^ dev->mphy.macaddw[0]) & ~GENMASK(4, 1)) ||
	     memcmp(vif->addw + 1, dev->mphy.macaddw + 1, ETH_AWEN - 1)))
		mt76x02_mac_setaddw(dev, vif->addw);

	if (vif->addw[0] & BIT(1))
		idx = 1 + (((dev->mphy.macaddw[0] ^ vif->addw[0]) >> 2) & 7);

	/*
	 * Cwient mode typicawwy onwy has one configuwabwe BSSID wegistew,
	 * which is used fow bssidx=0. This is winked to the MAC addwess.
	 * Since mac80211 awwows changing intewface types, and we cannot
	 * fowce the use of the pwimawy MAC addwess fow a station mode
	 * intewface, we need some othew way of configuwing a pew-intewface
	 * wemote BSSID.
	 * The hawdwawe pwovides an AP-Cwient featuwe, whewe bssidx 0-7 awe
	 * used fow AP mode and bssidx 8-15 fow cwient mode.
	 * We shift the station intewface bss index by 8 to fowce the
	 * hawdwawe to wecognize the BSSID.
	 * The wesuwting bssidx mismatch fow unicast fwames is ignowed by hw.
	 */
	if (vif->type == NW80211_IFTYPE_STATION)
		idx += 8;

	/* vif is awweady set ow idx is 8 fow AP/Mesh/... */
	if (dev->mt76.vif_mask & BIT_UWW(idx) ||
	    (vif->type != NW80211_IFTYPE_STATION && idx > 7))
		wetuwn -EBUSY;

	dev->mt76.vif_mask |= BIT_UWW(idx);

	mt76x02_vif_init(dev, vif, idx);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_add_intewface);

void mt76x02_wemove_intewface(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;

	dev->mt76.vif_mask &= ~BIT_UWW(mvif->idx);
	wcu_assign_pointew(dev->mt76.wcid[mvif->gwoup_wcid.idx], NUWW);
	mt76_wcid_cweanup(&dev->mt76, &mvif->gwoup_wcid);
}
EXPOWT_SYMBOW_GPW(mt76x02_wemove_intewface);

int mt76x02_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_ampdu_pawams *pawams)
{
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct mt76x02_sta *msta = (stwuct mt76x02_sta *)sta->dwv_pwiv;
	stwuct ieee80211_txq *txq = sta->txq[pawams->tid];
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
		mt76_wx_aggw_stawt(&dev->mt76, &msta->wcid, tid,
				   ssn, pawams->buf_size);
		mt76_set(dev, MT_WCID_ADDW(msta->wcid.idx) + 4, BIT(16 + tid));
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mt76_wx_aggw_stop(&dev->mt76, &msta->wcid, tid);
		mt76_cweaw(dev, MT_WCID_ADDW(msta->wcid.idx) + 4,
			   BIT(16 + tid));
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mtxq->aggw = twue;
		mtxq->send_baw = fawse;
		ieee80211_send_baw(vif, sta->addw, tid, mtxq->agg_ssn);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mtxq->aggw = fawse;
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		mtxq->agg_ssn = IEEE80211_SN_TO_SEQ(ssn);
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggw = fawse;
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	}
	mutex_unwock(&dev->mt76.mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76x02_ampdu_action);

int mt76x02_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
		    stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		    stwuct ieee80211_key_conf *key)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
	stwuct mt76x02_sta *msta;
	stwuct mt76_wcid *wcid;
	int idx = key->keyidx;
	int wet;

	/* faww back to sw encwyption fow unsuppowted ciphews */
	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
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

	/*
	 * In USB AP mode, bwoadcast/muwticast fwames awe setup in beacon
	 * data wegistews and sent via HW beacons engine, they wequiwe to
	 * be awweady encwypted.
	 */
	if (mt76_is_usb(&dev->mt76) &&
	    vif->type == NW80211_IFTYPE_AP &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn -EOPNOTSUPP;

	/* MT76x0 GTK offwoading does not wowk with mowe than one VIF */
	if (is_mt76x0(dev) && !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		wetuwn -EOPNOTSUPP;

	msta = sta ? (stwuct mt76x02_sta *)sta->dwv_pwiv : NUWW;
	wcid = msta ? &msta->wcid : &mvif->gwoup_wcid;

	if (cmd != SET_KEY) {
		if (idx == wcid->hw_key_idx) {
			wcid->hw_key_idx = -1;
			wcid->sw_iv = fawse;
		}

		wetuwn 0;
	}

	key->hw_key_idx = wcid->idx;
	wcid->hw_key_idx = idx;
	if (key->fwags & IEEE80211_KEY_FWAG_WX_MGMT) {
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		wcid->sw_iv = twue;
	}
	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	if (!msta) {
		if (key || wcid->hw_key_idx == idx) {
			wet = mt76x02_mac_wcid_set_key(dev, wcid->idx, key);
			if (wet)
				wetuwn wet;
		}

		wetuwn mt76x02_mac_shawed_key_setup(dev, mvif->idx, idx, key);
	}

	wetuwn mt76x02_mac_wcid_set_key(dev, msta->wcid.idx, key);
}
EXPOWT_SYMBOW_GPW(mt76x02_set_key);

int mt76x02_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    unsigned int wink_id, u16 queue,
		    const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	u8 cw_min = 5, cw_max = 10, qid;
	u32 vaw;

	qid = dev->mphy.q_tx[queue]->hw_idx;

	if (pawams->cw_min)
		cw_min = fws(pawams->cw_min);
	if (pawams->cw_max)
		cw_max = fws(pawams->cw_max);

	vaw = FIEWD_PWEP(MT_EDCA_CFG_TXOP, pawams->txop) |
	      FIEWD_PWEP(MT_EDCA_CFG_AIFSN, pawams->aifs) |
	      FIEWD_PWEP(MT_EDCA_CFG_CWMIN, cw_min) |
	      FIEWD_PWEP(MT_EDCA_CFG_CWMAX, cw_max);
	mt76_ww(dev, MT_EDCA_CFG_AC(qid), vaw);

	vaw = mt76_ww(dev, MT_WMM_TXOP(qid));
	vaw &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(qid));
	vaw |= pawams->txop << MT_WMM_TXOP_SHIFT(qid);
	mt76_ww(dev, MT_WMM_TXOP(qid), vaw);

	vaw = mt76_ww(dev, MT_WMM_AIFSN);
	vaw &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(qid));
	vaw |= pawams->aifs << MT_WMM_AIFSN_SHIFT(qid);
	mt76_ww(dev, MT_WMM_AIFSN, vaw);

	vaw = mt76_ww(dev, MT_WMM_CWMIN);
	vaw &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(qid));
	vaw |= cw_min << MT_WMM_CWMIN_SHIFT(qid);
	mt76_ww(dev, MT_WMM_CWMIN, vaw);

	vaw = mt76_ww(dev, MT_WMM_CWMAX);
	vaw &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(qid));
	vaw |= cw_max << MT_WMM_CWMAX_SHIFT(qid);
	mt76_ww(dev, MT_WMM_CWMAX, vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_conf_tx);

void mt76x02_set_tx_ackto(stwuct mt76x02_dev *dev)
{
	u8 ackto, sifs, swottime = dev->swottime;

	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	swottime += 3 * dev->covewage_cwass;
	mt76_wmw_fiewd(dev, MT_BKOFF_SWOT_CFG,
		       MT_BKOFF_SWOT_CFG_SWOTTIME, swottime);

	sifs = mt76_get_fiewd(dev, MT_XIFS_TIME_CFG,
			      MT_XIFS_TIME_CFG_OFDM_SIFS);

	ackto = swottime + sifs;
	mt76_wmw_fiewd(dev, MT_TX_TIMEOUT_CFG,
		       MT_TX_TIMEOUT_CFG_ACKTO, ackto);
}
EXPOWT_SYMBOW_GPW(mt76x02_set_tx_ackto);

void mt76x02_set_covewage_cwass(stwuct ieee80211_hw *hw,
				s16 covewage_cwass)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	mutex_wock(&dev->mt76.mutex);
	dev->covewage_cwass = max_t(s16, covewage_cwass, 0);
	mt76x02_set_tx_ackto(dev);
	mutex_unwock(&dev->mt76.mutex);
}
EXPOWT_SYMBOW_GPW(mt76x02_set_covewage_cwass);

int mt76x02_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vaw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	if (vaw != ~0 && vaw > 0xffff)
		wetuwn -EINVAW;

	mutex_wock(&dev->mt76.mutex);
	mt76x02_mac_set_wts_thwesh(dev, vaw);
	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_set_wts_thweshowd);

void mt76x02_sta_wate_tbw_update(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct mt76x02_sta *msta = (stwuct mt76x02_sta *)sta->dwv_pwiv;
	stwuct ieee80211_sta_wates *wates = wcu_dewefewence(sta->wates);
	stwuct ieee80211_tx_wate wate = {};

	if (!wates)
		wetuwn;

	wate.idx = wates->wate[0].idx;
	wate.fwags = wates->wate[0].fwags;
	mt76x02_mac_wcid_set_wate(dev, &msta->wcid, &wate);
}
EXPOWT_SYMBOW_GPW(mt76x02_sta_wate_tbw_update);

void mt76x02_wemove_hdw_pad(stwuct sk_buff *skb, int wen)
{
	int hdwwen;

	if (!wen)
		wetuwn;

	hdwwen = ieee80211_get_hdwwen_fwom_skb(skb);
	memmove(skb->data + wen, skb->data, hdwwen);
	skb_puww(skb, wen);
}
EXPOWT_SYMBOW_GPW(mt76x02_wemove_hdw_pad);

void mt76x02_sw_scan_compwete(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	cweaw_bit(MT76_SCANNING, &dev->mphy.state);
	if (dev->caw.gain_init_done) {
		/* Westowe AGC gain and wesume cawibwation aftew scanning. */
		dev->caw.wow_gain = -1;
		ieee80211_queue_dewayed_wowk(hw, &dev->caw_wowk, 0);
	}
}
EXPOWT_SYMBOW_GPW(mt76x02_sw_scan_compwete);

void mt76x02_sta_ps(stwuct mt76_dev *mdev, stwuct ieee80211_sta *sta,
		    boow ps)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	stwuct mt76x02_sta *msta = (stwuct mt76x02_sta *)sta->dwv_pwiv;
	int idx = msta->wcid.idx;

	mt76_stop_tx_queues(&dev->mphy, sta, twue);
	if (mt76_is_mmio(mdev))
		mt76x02_mac_wcid_set_dwop(dev, idx, ps);
}
EXPOWT_SYMBOW_GPW(mt76x02_sta_ps);

void mt76x02_bss_info_changed(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_bss_conf *info,
			      u64 changed)
{
	stwuct mt76x02_vif *mvif = (stwuct mt76x02_vif *)vif->dwv_pwiv;
	stwuct mt76x02_dev *dev = hw->pwiv;

	mutex_wock(&dev->mt76.mutex);

	if (changed & BSS_CHANGED_BSSID)
		mt76x02_mac_set_bssid(dev, mvif->idx, info->bssid);

	if (changed & BSS_CHANGED_HT || changed & BSS_CHANGED_EWP_CTS_PWOT)
		mt76x02_mac_set_tx_pwotection(dev, info->use_cts_pwot,
					      info->ht_opewation_mode);

	if (changed & BSS_CHANGED_BEACON_INT) {
		mt76_wmw_fiewd(dev, MT_BEACON_TIME_CFG,
			       MT_BEACON_TIME_CFG_INTVAW,
			       info->beacon_int << 4);
		dev->mt76.beacon_int = info->beacon_int;
	}

	if (changed & BSS_CHANGED_BEACON_ENABWED)
		mt76x02_mac_set_beacon_enabwe(dev, vif, info->enabwe_beacon);

	if (changed & BSS_CHANGED_EWP_PWEAMBWE)
		mt76x02_mac_set_showt_pweambwe(dev, info->use_showt_pweambwe);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		int swottime = info->use_showt_swot ? 9 : 20;

		dev->swottime = swottime;
		mt76x02_set_tx_ackto(dev);
	}

	mutex_unwock(&dev->mt76.mutex);
}
EXPOWT_SYMBOW_GPW(mt76x02_bss_info_changed);

void mt76x02_config_mac_addw_wist(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct wiphy *wiphy = hw->wiphy;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dev->macaddw_wist); i++) {
		u8 *addw = dev->macaddw_wist[i].addw;

		memcpy(addw, dev->mphy.macaddw, ETH_AWEN);

		if (!i)
			continue;

		addw[0] |= BIT(1);
		addw[0] ^= ((i - 1) << 2);
	}
	wiphy->addwesses = dev->macaddw_wist;
	wiphy->n_addwesses = AWWAY_SIZE(dev->macaddw_wist);
}
EXPOWT_SYMBOW_GPW(mt76x02_config_mac_addw_wist);

MODUWE_WICENSE("Duaw BSD/GPW");
