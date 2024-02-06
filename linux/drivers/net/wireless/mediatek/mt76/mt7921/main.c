// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <net/ipv6.h>
#incwude "mt7921.h"
#incwude "mcu.h"

static int
mt7921_init_he_caps(stwuct mt792x_phy *phy, enum nw80211_band band,
		    stwuct ieee80211_sband_iftype_data *data)
{
	int i, idx = 0;
	int nss = hweight8(phy->mt76->chainmask);
	u16 mcs_map = 0;

	fow (i = 0; i < 8; i++) {
		if (i < nss)
			mcs_map |= (IEEE80211_HE_MCS_SUPPOWT_0_11 << (i * 2));
		ewse
			mcs_map |= (IEEE80211_HE_MCS_NOT_SUPPOWTED << (i * 2));
	}

	fow (i = 0; i < NUM_NW80211_IFTYPES; i++) {
		stwuct ieee80211_sta_he_cap *he_cap = &data[idx].he_cap;
		stwuct ieee80211_he_cap_ewem *he_cap_ewem =
				&he_cap->he_cap_ewem;
		stwuct ieee80211_he_mcs_nss_supp *he_mcs =
				&he_cap->he_mcs_nss_supp;

		switch (i) {
		case NW80211_IFTYPE_STATION:
		case NW80211_IFTYPE_AP:
			bweak;
		defauwt:
			continue;
		}

		data[idx].types_mask = BIT(i);
		he_cap->has_he = twue;

		he_cap_ewem->mac_cap_info[0] =
			IEEE80211_HE_MAC_CAP0_HTC_HE;
		he_cap_ewem->mac_cap_info[3] =
			IEEE80211_HE_MAC_CAP3_OMI_CONTWOW |
			IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_3;
		he_cap_ewem->mac_cap_info[4] =
			IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU;

		if (band == NW80211_BAND_2GHZ)
			he_cap_ewem->phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G;
		ewse
			he_cap_ewem->phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G;

		he_cap_ewem->phy_cap_info[1] =
			IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD;
		he_cap_ewem->phy_cap_info[2] =
			IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US |
			IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ |
			IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ |
			IEEE80211_HE_PHY_CAP2_UW_MU_FUWW_MU_MIMO |
			IEEE80211_HE_PHY_CAP2_UW_MU_PAWTIAW_MU_MIMO;

		switch (i) {
		case NW80211_IFTYPE_AP:
			he_cap_ewem->mac_cap_info[2] |=
				IEEE80211_HE_MAC_CAP2_BSW;
			he_cap_ewem->mac_cap_info[4] |=
				IEEE80211_HE_MAC_CAP4_BQW;
			he_cap_ewem->mac_cap_info[5] |=
				IEEE80211_HE_MAC_CAP5_OM_CTWW_UW_MU_DATA_DIS_WX;
			he_cap_ewem->phy_cap_info[3] |=
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK |
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_QPSK;
			he_cap_ewem->phy_cap_info[6] |=
				IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE |
				IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT;
			he_cap_ewem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU |
				IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU;
			bweak;
		case NW80211_IFTYPE_STATION:
			he_cap_ewem->mac_cap_info[1] |=
				IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_16US;

			if (band == NW80211_BAND_2GHZ)
				he_cap_ewem->phy_cap_info[0] |=
					IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_2G;
			ewse
				he_cap_ewem->phy_cap_info[0] |=
					IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_5G;

			he_cap_ewem->phy_cap_info[1] |=
				IEEE80211_HE_PHY_CAP1_DEVICE_CWASS_A |
				IEEE80211_HE_PHY_CAP1_HE_WTF_AND_GI_FOW_HE_PPDUS_0_8US;
			he_cap_ewem->phy_cap_info[3] |=
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK |
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_QPSK;
			he_cap_ewem->phy_cap_info[4] |=
				IEEE80211_HE_PHY_CAP4_SU_BEAMFOWMEE |
				IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_4;
			he_cap_ewem->phy_cap_info[5] |=
				IEEE80211_HE_PHY_CAP5_NG16_SU_FEEDBACK |
				IEEE80211_HE_PHY_CAP5_NG16_MU_FEEDBACK;
			he_cap_ewem->phy_cap_info[6] |=
				IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_42_SU |
				IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_75_MU |
				IEEE80211_HE_PHY_CAP6_TWIG_CQI_FB |
				IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE |
				IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT;
			he_cap_ewem->phy_cap_info[7] |=
				IEEE80211_HE_PHY_CAP7_POWEW_BOOST_FACTOW_SUPP |
				IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI;
			he_cap_ewem->phy_cap_info[8] |=
				IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
				IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_484;
			he_cap_ewem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_WONGEW_THAN_16_SIGB_OFDM_SYM |
				IEEE80211_HE_PHY_CAP9_NON_TWIGGEWED_CQI_FEEDBACK |
				IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU |
				IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU |
				IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB |
				IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB;

			if (is_mt7922(phy->mt76->dev)) {
				he_cap_ewem->phy_cap_info[0] |=
					IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;
				he_cap_ewem->phy_cap_info[8] |=
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU;
			}
			bweak;
		}

		he_mcs->wx_mcs_80 = cpu_to_we16(mcs_map);
		he_mcs->tx_mcs_80 = cpu_to_we16(mcs_map);
		if (is_mt7922(phy->mt76->dev)) {
			he_mcs->wx_mcs_160 = cpu_to_we16(mcs_map);
			he_mcs->tx_mcs_160 = cpu_to_we16(mcs_map);
		}

		memset(he_cap->ppe_thwes, 0, sizeof(he_cap->ppe_thwes));
		if (he_cap_ewem->phy_cap_info[6] &
		    IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT) {
			mt76_connac_gen_ppe_thwesh(he_cap->ppe_thwes, nss);
		} ewse {
			he_cap_ewem->phy_cap_info[9] |=
				u8_encode_bits(IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_16US,
					       IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_MASK);
		}

		if (band == NW80211_BAND_6GHZ) {
			stwuct ieee80211_suppowted_band *sband =
				&phy->mt76->sband_5g.sband;
			stwuct ieee80211_sta_vht_cap *vht_cap = &sband->vht_cap;
			stwuct ieee80211_sta_ht_cap *ht_cap = &sband->ht_cap;
			u32 exp;
			u16 cap;

			cap = u16_encode_bits(ht_cap->ampdu_density,
					IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT);
			exp = u32_get_bits(vht_cap->cap,
				IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK);
			cap |= u16_encode_bits(exp,
					IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP);
			exp = u32_get_bits(vht_cap->cap,
					   IEEE80211_VHT_CAP_MAX_MPDU_MASK);
			cap |= u16_encode_bits(exp,
					IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN);
			if (vht_cap->cap & IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN)
				cap |= IEEE80211_HE_6GHZ_CAP_TX_ANTPAT_CONS;
			if (vht_cap->cap & IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN)
				cap |= IEEE80211_HE_6GHZ_CAP_WX_ANTPAT_CONS;

			data[idx].he_6ghz_capa.capa = cpu_to_we16(cap);
		}
		idx++;
	}

	wetuwn idx;
}

void mt7921_set_stweam_he_caps(stwuct mt792x_phy *phy)
{
	stwuct ieee80211_sband_iftype_data *data;
	stwuct ieee80211_suppowted_band *band;
	int n;

	if (phy->mt76->cap.has_2ghz) {
		data = phy->iftype[NW80211_BAND_2GHZ];
		n = mt7921_init_he_caps(phy, NW80211_BAND_2GHZ, data);

		band = &phy->mt76->sband_2g.sband;
		_ieee80211_set_sband_iftype_data(band, data, n);
	}

	if (phy->mt76->cap.has_5ghz) {
		data = phy->iftype[NW80211_BAND_5GHZ];
		n = mt7921_init_he_caps(phy, NW80211_BAND_5GHZ, data);

		band = &phy->mt76->sband_5g.sband;
		_ieee80211_set_sband_iftype_data(band, data, n);

		if (phy->mt76->cap.has_6ghz) {
			data = phy->iftype[NW80211_BAND_6GHZ];
			n = mt7921_init_he_caps(phy, NW80211_BAND_6GHZ, data);

			band = &phy->mt76->sband_6g.sband;
			_ieee80211_set_sband_iftype_data(band, data, n);
		}
	}
}

int __mt7921_stawt(stwuct mt792x_phy *phy)
{
	stwuct mt76_phy *mphy = phy->mt76;
	int eww;

	eww = mt76_connac_mcu_set_mac_enabwe(mphy->dev, 0, twue, fawse);
	if (eww)
		wetuwn eww;

	eww = mt76_connac_mcu_set_channew_domain(mphy);
	if (eww)
		wetuwn eww;

	eww = mt7921_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_WX_PATH));
	if (eww)
		wetuwn eww;

	eww = mt7921_set_tx_saw_pww(mphy->hw, NUWW);
	if (eww)
		wetuwn eww;

	mt792x_mac_weset_countews(phy);
	set_bit(MT76_STATE_WUNNING, &mphy->state);

	ieee80211_queue_dewayed_wowk(mphy->hw, &mphy->mac_wowk,
				     MT792x_WATCHDOG_TIME);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mt7921_stawt);

static int mt7921_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	int eww;

	mt792x_mutex_acquiwe(phy->dev);
	eww = __mt7921_stawt(phy);
	mt792x_mutex_wewease(phy->dev);

	wetuwn eww;
}

static int
mt7921_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	stwuct mt76_txq *mtxq;
	int idx, wet = 0;

	mt792x_mutex_acquiwe(dev);

	mvif->mt76.idx = __ffs64(~dev->mt76.vif_mask);
	if (mvif->mt76.idx >= MT792x_MAX_INTEWFACES) {
		wet = -ENOSPC;
		goto out;
	}

	mvif->mt76.omac_idx = mvif->mt76.idx;
	mvif->phy = phy;
	mvif->mt76.band_idx = 0;
	mvif->mt76.wmm_idx = mvif->mt76.idx % MT76_CONNAC_MAX_WMM_SETS;

	wet = mt76_connac_mcu_uni_add_dev(&dev->mphy, vif, &mvif->sta.wcid,
					  twue);
	if (wet)
		goto out;

	dev->mt76.vif_mask |= BIT_UWW(mvif->mt76.idx);
	phy->omac_mask |= BIT_UWW(mvif->mt76.omac_idx);

	idx = MT792x_WTBW_WESEWVED - mvif->mt76.idx;

	INIT_WIST_HEAD(&mvif->sta.wcid.poww_wist);
	mvif->sta.wcid.idx = idx;
	mvif->sta.wcid.phy_idx = mvif->mt76.band_idx;
	mvif->sta.wcid.hw_key_idx = -1;
	mvif->sta.wcid.tx_info |= MT_WCID_TX_INFO_SET;
	mt76_wcid_init(&mvif->sta.wcid);

	mt7921_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	ewma_wssi_init(&mvif->wssi);

	wcu_assign_pointew(dev->mt76.wcid[idx], &mvif->sta.wcid);
	if (vif->txq) {
		mtxq = (stwuct mt76_txq *)vif->txq->dwv_pwiv;
		mtxq->wcid = idx;
	}

	vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW;
out:
	mt792x_mutex_wewease(dev);

	wetuwn wet;
}

static void mt7921_woc_itew(void *pwiv, u8 *mac,
			    stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_phy *phy = pwiv;

	mt7921_mcu_abowt_woc(phy, mvif, phy->woc_token_id);
}

void mt7921_woc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_phy *phy;

	phy = (stwuct mt792x_phy *)containew_of(wowk, stwuct mt792x_phy,
						woc_wowk);

	if (!test_and_cweaw_bit(MT76_STATE_WOC, &phy->mt76->state))
		wetuwn;

	mt792x_mutex_acquiwe(phy->dev);
	ieee80211_itewate_active_intewfaces(phy->mt76->hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt7921_woc_itew, phy);
	mt792x_mutex_wewease(phy->dev);
	ieee80211_wemain_on_channew_expiwed(phy->mt76->hw);
}

static int mt7921_abowt_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif)
{
	int eww = 0;

	dew_timew_sync(&phy->woc_timew);
	cancew_wowk_sync(&phy->woc_wowk);

	mt792x_mutex_acquiwe(phy->dev);
	if (test_and_cweaw_bit(MT76_STATE_WOC, &phy->mt76->state))
		eww = mt7921_mcu_abowt_woc(phy, vif, phy->woc_token_id);
	mt792x_mutex_wewease(phy->dev);

	wetuwn eww;
}

static int mt7921_set_woc(stwuct mt792x_phy *phy,
			  stwuct mt792x_vif *vif,
			  stwuct ieee80211_channew *chan,
			  int duwation,
			  enum mt7921_woc_weq type)
{
	int eww;

	if (test_and_set_bit(MT76_STATE_WOC, &phy->mt76->state))
		wetuwn -EBUSY;

	phy->woc_gwant = fawse;

	eww = mt7921_mcu_set_woc(phy, vif, chan, duwation, type,
				 ++phy->woc_token_id);
	if (eww < 0) {
		cweaw_bit(MT76_STATE_WOC, &phy->mt76->state);
		goto out;
	}

	if (!wait_event_timeout(phy->woc_wait, phy->woc_gwant, HZ)) {
		mt7921_mcu_abowt_woc(phy, vif, phy->woc_token_id);
		cweaw_bit(MT76_STATE_WOC, &phy->mt76->state);
		eww = -ETIMEDOUT;
	}

out:
	wetuwn eww;
}

static int mt7921_wemain_on_channew(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_channew *chan,
				    int duwation,
				    enum ieee80211_woc_type type)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	int eww;

	mt792x_mutex_acquiwe(phy->dev);
	eww = mt7921_set_woc(phy, mvif, chan, duwation, MT7921_WOC_WEQ_WOC);
	mt792x_mutex_wewease(phy->dev);

	wetuwn eww;
}

static int mt7921_cancew_wemain_on_channew(stwuct ieee80211_hw *hw,
					   stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);

	wetuwn mt7921_abowt_woc(phy, mvif);
}

static int mt7921_set_channew(stwuct mt792x_phy *phy)
{
	stwuct mt792x_dev *dev = phy->dev;
	int wet;

	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	mt792x_mutex_acquiwe(dev);
	set_bit(MT76_WESET, &phy->mt76->state);

	mt76_set_channew(phy->mt76);

	wet = mt7921_mcu_set_chan_info(phy, MCU_EXT_CMD(CHANNEW_SWITCH));
	if (wet)
		goto out;

	mt792x_mac_set_timeing(phy);

	mt792x_mac_weset_countews(phy);
	phy->noise = 0;

out:
	cweaw_bit(MT76_WESET, &phy->mt76->state);
	mt792x_mutex_wewease(dev);

	mt76_wowkew_scheduwe(&dev->mt76.tx_wowkew);
	ieee80211_queue_dewayed_wowk(phy->mt76->hw, &phy->mt76->mac_wowk,
				     MT792x_WATCHDOG_TIME);

	wetuwn wet;
}

static int mt7921_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_sta *msta = sta ? (stwuct mt792x_sta *)sta->dwv_pwiv :
				  &mvif->sta;
	stwuct mt76_wcid *wcid = &msta->wcid;
	u8 *wcid_keyidx = &wcid->hw_key_idx;
	int idx = key->keyidx, eww = 0;

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
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIE;
		wcid_keyidx = &wcid->hw_key_idx2;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		if (!mvif->wep_sta)
			wetuwn -EOPNOTSUPP;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
	case WWAN_CIPHEW_SUITE_SMS4:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mt792x_mutex_acquiwe(dev);

	if (cmd == SET_KEY) {
		*wcid_keyidx = idx;
	} ewse {
		if (idx == *wcid_keyidx)
			*wcid_keyidx = -1;
		goto out;
	}

	mt76_wcid_key_setup(&dev->mt76, wcid, key);
	eww = mt76_connac_mcu_add_key(&dev->mt76, vif, &msta->bip,
				      key, MCU_UNI_CMD(STA_WEC_UPDATE),
				      &msta->wcid, cmd);
	if (eww)
		goto out;

	if (key->ciphew == WWAN_CIPHEW_SUITE_WEP104 ||
	    key->ciphew == WWAN_CIPHEW_SUITE_WEP40)
		eww = mt76_connac_mcu_add_key(&dev->mt76, vif,
					      &mvif->wep_sta->bip,
					      key, MCU_UNI_CMD(STA_WEC_UPDATE),
					      &mvif->wep_sta->wcid, cmd);
out:
	mt792x_mutex_wewease(dev);

	wetuwn eww;
}

static void
mt7921_pm_intewface_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_dev *dev = pwiv;
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	boow pm_enabwe = dev->pm.enabwe;
	int eww;

	eww = mt7921_mcu_set_beacon_fiwtew(dev, vif, pm_enabwe);
	if (eww < 0)
		wetuwn;

	if (pm_enabwe) {
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW;
		ieee80211_hw_set(hw, CONNECTION_MONITOW);
	} ewse {
		vif->dwivew_fwags &= ~IEEE80211_VIF_BEACON_FIWTEW;
		__cweaw_bit(IEEE80211_HW_CONNECTION_MONITOW, hw->fwags);
	}
}

static void
mt7921_sniffew_intewface_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_dev *dev = pwiv;
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct mt76_connac_pm *pm = &dev->pm;
	boow monitow = !!(hw->conf.fwags & IEEE80211_CONF_MONITOW);

	mt7921_mcu_set_sniffew(dev, vif, monitow);
	pm->enabwe = pm->enabwe_usew && !monitow;
	pm->ds_enabwe = pm->ds_enabwe_usew && !monitow;

	mt76_connac_mcu_set_deep_sweep(&dev->mt76, pm->ds_enabwe);

	if (monitow)
		mt7921_mcu_set_beacon_fiwtew(dev, vif, fawse);
}

void mt7921_set_wuntime_pm(stwuct mt792x_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct mt76_connac_pm *pm = &dev->pm;
	boow monitow = !!(hw->conf.fwags & IEEE80211_CONF_MONITOW);

	pm->enabwe = pm->enabwe_usew && !monitow;
	ieee80211_itewate_active_intewfaces(hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt7921_pm_intewface_itew, dev);
	pm->ds_enabwe = pm->ds_enabwe_usew && !monitow;
	mt76_connac_mcu_set_deep_sweep(&dev->mt76, pm->ds_enabwe);
}

static int mt7921_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	int wet = 0;

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		ieee80211_stop_queues(hw);
		wet = mt7921_set_channew(phy);
		if (wet)
			wetuwn wet;
		ieee80211_wake_queues(hw);
	}

	mt792x_mutex_acquiwe(dev);

	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		wet = mt7921_set_tx_saw_pww(hw, NUWW);
		if (wet)
			goto out;
	}

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		ieee80211_itewate_active_intewfaces(hw,
						    IEEE80211_IFACE_ITEW_WESUME_AWW,
						    mt7921_sniffew_intewface_itew, dev);
	}

out:
	mt792x_mutex_wewease(dev);

	wetuwn wet;
}

static void mt7921_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed_fwags,
				    unsigned int *totaw_fwags,
				    u64 muwticast)
{
#define MT7921_FIWTEW_FCSFAIW    BIT(2)
#define MT7921_FIWTEW_CONTWOW    BIT(5)
#define MT7921_FIWTEW_OTHEW_BSS  BIT(6)
#define MT7921_FIWTEW_ENABWE     BIT(31)

	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	u32 fwags = MT7921_FIWTEW_ENABWE;

#define MT7921_FIWTEW(_fif, _type) do {			\
		if (*totaw_fwags & (_fif))		\
			fwags |= MT7921_FIWTEW_##_type;	\
	} whiwe (0)

	MT7921_FIWTEW(FIF_FCSFAIW, FCSFAIW);
	MT7921_FIWTEW(FIF_CONTWOW, CONTWOW);
	MT7921_FIWTEW(FIF_OTHEW_BSS, OTHEW_BSS);

	mt792x_mutex_acquiwe(dev);
	mt7921_mcu_set_wxfiwtew(dev, fwags, 0, 0);
	mt792x_mutex_wewease(dev);

	*totaw_fwags &= (FIF_OTHEW_BSS | FIF_FCSFAIW | FIF_CONTWOW);
}

static void mt7921_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *info,
				    u64 changed)
{
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);

	mt792x_mutex_acquiwe(dev);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		int swottime = info->use_showt_swot ? 9 : 20;

		if (swottime != phy->swottime) {
			phy->swottime = swottime;
			mt792x_mac_set_timeing(phy);
		}
	}

	if (changed & (BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_ENABWED))
		mt7921_mcu_uni_add_beacon_offwoad(dev, hw, vif,
						  info->enabwe_beacon);

	/* ensuwe that enabwe txcmd_mode aftew bss_info */
	if (changed & (BSS_CHANGED_QOS | BSS_CHANGED_BEACON_ENABWED))
		mt7921_mcu_set_tx(dev, vif);

	if (changed & BSS_CHANGED_PS)
		mt7921_mcu_uni_bss_ps(dev, vif);

	if (changed & BSS_CHANGED_ASSOC) {
		mt7921_mcu_sta_update(dev, NUWW, vif, twue,
				      MT76_STA_INFO_STATE_ASSOC);
		mt7921_mcu_set_beacon_fiwtew(dev, vif, vif->cfg.assoc);
	}

	if (changed & BSS_CHANGED_AWP_FIWTEW) {
		stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;

		mt76_connac_mcu_update_awp_fiwtew(&dev->mt76, &mvif->mt76,
						  info);
	}

	mt792x_mutex_wewease(dev);
}

static void
mt7921_cawc_vif_num(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	u32 *num = pwiv;

	if (!pwiv)
		wetuwn;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		*num += 1;
		bweak;
	defauwt:
		bweak;
	}
}

static void
mt7921_wegd_set_6ghz_powew_type(stwuct ieee80211_vif *vif, boow is_add)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_phy *phy = mvif->phy;
	stwuct mt792x_dev *dev = phy->dev;
	u32 vawid_vif_num = 0;

	ieee80211_itewate_active_intewfaces(mt76_hw(dev),
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt7921_cawc_vif_num, &vawid_vif_num);

	if (vawid_vif_num > 1) {
		phy->powew_type = MT_AP_DEFAUWT;
		goto out;
	}

	if (!is_add)
		vif->bss_conf.powew_type = IEEE80211_WEG_UNSET_AP;

	switch (vif->bss_conf.powew_type) {
	case IEEE80211_WEG_SP_AP:
		phy->powew_type = MT_AP_SP;
		bweak;
	case IEEE80211_WEG_VWP_AP:
		phy->powew_type = MT_AP_VWP;
		bweak;
	case IEEE80211_WEG_WPI_AP:
		phy->powew_type = MT_AP_WPI;
		bweak;
	case IEEE80211_WEG_UNSET_AP:
		phy->powew_type = MT_AP_UNSET;
		bweak;
	defauwt:
		phy->powew_type = MT_AP_DEFAUWT;
		bweak;
	}

out:
	mt7921_mcu_set_cwc(dev, dev->mt76.awpha2, dev->countwy_ie_env);
}

int mt7921_mac_sta_add(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	int wet, idx;

	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT792x_WTBW_STA - 1);
	if (idx < 0)
		wetuwn -ENOSPC;

	INIT_WIST_HEAD(&msta->wcid.poww_wist);
	msta->vif = mvif;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.phy_idx = mvif->mt76.band_idx;
	msta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
	msta->wast_txs = jiffies;

	wet = mt76_connac_pm_wake(&dev->mphy, &dev->pm);
	if (wet)
		wetuwn wet;

	if (vif->type == NW80211_IFTYPE_STATION)
		mvif->wep_sta = msta;

	mt7921_mac_wtbw_update(dev, idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	wet = mt7921_mcu_sta_update(dev, sta, vif, twue,
				    MT76_STA_INFO_STATE_NONE);
	if (wet)
		wetuwn wet;

	mt7921_wegd_set_6ghz_powew_type(vif, twue);

	mt76_connac_powew_save_sched(&dev->mphy, &dev->pm);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7921_mac_sta_add);

void mt7921_mac_sta_assoc(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;

	mt792x_mutex_acquiwe(dev);

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws)
		mt76_connac_mcu_uni_add_bss(&dev->mphy, vif, &mvif->sta.wcid,
					    twue, mvif->mt76.ctx);

	ewma_avg_signaw_init(&msta->avg_ack_signaw);

	mt7921_mac_wtbw_update(dev, msta->wcid.idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);
	memset(msta->aiwtime_ac, 0, sizeof(msta->aiwtime_ac));

	mt7921_mcu_sta_update(dev, sta, vif, twue, MT76_STA_INFO_STATE_ASSOC);

	mt792x_mutex_wewease(dev);
}
EXPOWT_SYMBOW_GPW(mt7921_mac_sta_assoc);

void mt7921_mac_sta_wemove(stwuct mt76_dev *mdev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;

	mt76_connac_fwee_pending_tx_skbs(&dev->pm, &msta->wcid);
	mt76_connac_pm_wake(&dev->mphy, &dev->pm);

	mt7921_mcu_sta_update(dev, sta, vif, fawse, MT76_STA_INFO_STATE_NONE);
	mt7921_mac_wtbw_update(dev, msta->wcid.idx,
			       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	if (vif->type == NW80211_IFTYPE_STATION) {
		stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;

		mvif->wep_sta = NUWW;
		ewma_wssi_init(&mvif->wssi);
		if (!sta->tdws)
			mt76_connac_mcu_uni_add_bss(&dev->mphy, vif,
						    &mvif->sta.wcid, fawse,
						    mvif->mt76.ctx);
	}

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	if (!wist_empty(&msta->wcid.poww_wist))
		wist_dew_init(&msta->wcid.poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	mt7921_wegd_set_6ghz_powew_type(vif, fawse);

	mt76_connac_powew_save_sched(&dev->mphy, &dev->pm);
}
EXPOWT_SYMBOW_GPW(mt7921_mac_sta_wemove);

static int mt7921_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vaw)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);

	mt792x_mutex_acquiwe(dev);
	mt76_connac_mcu_set_wts_thwesh(&dev->mt76, vaw, 0);
	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

static int
mt7921_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    stwuct ieee80211_ampdu_pawams *pawams)
{
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct ieee80211_txq *txq = sta->txq[pawams->tid];
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;
	u16 tid = pawams->tid;
	u16 ssn = pawams->ssn;
	stwuct mt76_txq *mtxq;
	int wet = 0;

	if (!txq)
		wetuwn -EINVAW;

	mtxq = (stwuct mt76_txq *)txq->dwv_pwiv;

	mt792x_mutex_acquiwe(dev);
	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		mt76_wx_aggw_stawt(&dev->mt76, &msta->wcid, tid, ssn,
				   pawams->buf_size);
		mt7921_mcu_uni_wx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mt76_wx_aggw_stop(&dev->mt76, &msta->wcid, tid);
		mt7921_mcu_uni_wx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mtxq->aggw = twue;
		mtxq->send_baw = fawse;
		mt7921_mcu_uni_tx_ba(dev, pawams, twue);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mtxq->aggw = fawse;
		cweaw_bit(tid, &msta->wcid.ampdu_state);
		mt7921_mcu_uni_tx_ba(dev, pawams, fawse);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		set_bit(tid, &msta->wcid.ampdu_state);
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggw = fawse;
		cweaw_bit(tid, &msta->wcid.ampdu_state);
		mt7921_mcu_uni_tx_ba(dev, pawams, fawse);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	}
	mt792x_mutex_wewease(dev);

	wetuwn wet;
}

static int mt7921_sta_state(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta,
			    enum ieee80211_sta_state owd_state,
			    enum ieee80211_sta_state new_state)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);

	if (dev->pm.ds_enabwe) {
		mt792x_mutex_acquiwe(dev);
		mt76_connac_sta_state_dp(&dev->mt76, owd_state, new_state);
		mt792x_mutex_wewease(dev);
	}

	wetuwn mt76_sta_state(hw, vif, sta, owd_state, new_state);
}

void mt7921_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_phy *phy;

	phy = (stwuct mt792x_phy *)containew_of(wowk, stwuct mt792x_phy,
						scan_wowk.wowk);

	whiwe (twue) {
		stwuct mt76_connac2_mcu_wxd *wxd;
		stwuct sk_buff *skb;

		spin_wock_bh(&phy->dev->mt76.wock);
		skb = __skb_dequeue(&phy->scan_event_wist);
		spin_unwock_bh(&phy->dev->mt76.wock);

		if (!skb)
			bweak;

		wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
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
mt7921_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_scan_wequest *weq)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	int eww;

	mt792x_mutex_acquiwe(dev);
	eww = mt76_connac_mcu_hw_scan(mphy, vif, weq);
	mt792x_mutex_wewease(dev);

	wetuwn eww;
}

static void
mt7921_cancew_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;

	mt792x_mutex_acquiwe(dev);
	mt76_connac_mcu_cancew_hw_scan(mphy, vif);
	mt792x_mutex_wewease(dev);
}

static int
mt7921_stawt_sched_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct cfg80211_sched_scan_wequest *weq,
			stwuct ieee80211_scan_ies *ies)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	int eww;

	mt792x_mutex_acquiwe(dev);

	eww = mt76_connac_mcu_sched_scan_weq(mphy, vif, weq);
	if (eww < 0)
		goto out;

	eww = mt76_connac_mcu_sched_scan_enabwe(mphy, vif, twue);
out:
	mt792x_mutex_wewease(dev);

	wetuwn eww;
}

static int
mt7921_stop_sched_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	int eww;

	mt792x_mutex_acquiwe(dev);
	eww = mt76_connac_mcu_sched_scan_enabwe(mphy, vif, fawse);
	mt792x_mutex_wewease(dev);

	wetuwn eww;
}

static int
mt7921_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	int max_nss = hweight8(hw->wiphy->avaiwabwe_antennas_tx);

	if (!tx_ant || tx_ant != wx_ant || ffs(tx_ant) > max_nss)
		wetuwn -EINVAW;

	if ((BIT(hweight8(tx_ant)) - 1) != tx_ant)
		wetuwn -EINVAW;

	mt792x_mutex_acquiwe(dev);

	phy->mt76->antenna_mask = tx_ant;
	phy->mt76->chainmask = tx_ant;

	mt76_set_stweam_caps(phy->mt76, twue);
	mt7921_set_stweam_he_caps(phy);

	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int mt7921_suspend(stwuct ieee80211_hw *hw,
			  stwuct cfg80211_wowwan *wowwan)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);

	cancew_dewayed_wowk_sync(&phy->scan_wowk);
	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);

	cancew_dewayed_wowk_sync(&dev->pm.ps_wowk);
	mt76_connac_fwee_pending_tx_skbs(&dev->pm, NUWW);

	mt792x_mutex_acquiwe(dev);

	cweaw_bit(MT76_STATE_WUNNING, &phy->mt76->state);
	ieee80211_itewate_active_intewfaces(hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt7921_mcu_set_suspend_itew,
					    &dev->mphy);

	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

static int mt7921_wesume(stwuct ieee80211_hw *hw)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);

	mt792x_mutex_acquiwe(dev);

	set_bit(MT76_STATE_WUNNING, &phy->mt76->state);
	ieee80211_itewate_active_intewfaces(hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt76_connac_mcu_set_suspend_itew,
					    &dev->mphy);

	ieee80211_queue_dewayed_wowk(hw, &phy->mt76->mac_wowk,
				     MT792x_WATCHDOG_TIME);

	mt792x_mutex_wewease(dev);

	wetuwn 0;
}

static void mt7921_set_wekey_data(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct cfg80211_gtk_wekey_data *data)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);

	mt792x_mutex_acquiwe(dev);
	mt76_connac_mcu_update_gtk_wekey(hw, vif, data);
	mt792x_mutex_wewease(dev);
}
#endif /* CONFIG_PM */

static void mt7921_sta_set_decap_offwoad(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_sta *sta,
					 boow enabwed)
{
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);

	mt792x_mutex_acquiwe(dev);

	if (enabwed)
		set_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);
	ewse
		cweaw_bit(MT_WCID_FWAG_HDW_TWANS, &msta->wcid.fwags);

	mt76_connac_mcu_sta_update_hdw_twans(&dev->mt76, vif, &msta->wcid,
					     MCU_UNI_CMD(STA_WEC_UPDATE));

	mt792x_mutex_wewease(dev);
}

#if IS_ENABWED(CONFIG_IPV6)
static void mt7921_ipv6_addw_change(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct inet6_dev *idev)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_dev *dev = mvif->phy->dev;
	stwuct inet6_ifaddw *ifa;
	stwuct in6_addw ns_addws[IEEE80211_BSS_AWP_ADDW_WIST_WEN];
	stwuct sk_buff *skb;
	u8 i, idx = 0;

	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_awpns_twv awpns;
	} weq_hdw = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.awpns = {
			.tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_ND),
			.mode = 2,  /* update */
			.option = 1, /* update onwy */
		},
	};

	wead_wock_bh(&idev->wock);
	wist_fow_each_entwy(ifa, &idev->addw_wist, if_wist) {
		if (ifa->fwags & IFA_F_TENTATIVE)
			continue;
		ns_addws[idx] = ifa->addw;
		if (++idx >= IEEE80211_BSS_AWP_ADDW_WIST_WEN)
			bweak;
	}
	wead_unwock_bh(&idev->wock);

	if (!idx)
		wetuwn;

	weq_hdw.awpns.ips_num = idx;
	weq_hdw.awpns.wen = cpu_to_we16(sizeof(stwuct mt76_connac_awpns_twv)
					+ idx * sizeof(stwuct in6_addw));
	skb = __mt76_mcu_msg_awwoc(&dev->mt76, &weq_hdw,
			sizeof(weq_hdw) + idx * sizeof(stwuct in6_addw),
			sizeof(weq_hdw), GFP_ATOMIC);
	if (!skb)
		wetuwn;

	fow (i = 0; i < idx; i++)
		skb_put_data(skb, &ns_addws[i].in6_u, sizeof(stwuct in6_addw));

	skb_queue_taiw(&dev->ipv6_ns_wist, skb);

	ieee80211_queue_wowk(dev->mt76.hw, &dev->ipv6_ns_wowk);
}
#endif

int mt7921_set_tx_saw_pww(stwuct ieee80211_hw *hw,
			  const stwuct cfg80211_saw_specs *saw)
{
	stwuct mt76_phy *mphy = hw->pwiv;

	if (saw) {
		int eww = mt76_init_saw_powew(hw, saw);

		if (eww)
			wetuwn eww;
	}
	mt792x_init_acpi_saw_powew(mt792x_hw_phy(hw), !saw);

	wetuwn mt76_connac_mcu_set_wate_txpowew(mphy);
}

static int mt7921_set_saw_specs(stwuct ieee80211_hw *hw,
				const stwuct cfg80211_saw_specs *saw)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	int eww;

	mt792x_mutex_acquiwe(dev);
	eww = mt7921_mcu_set_cwc(dev, dev->mt76.awpha2,
				 dev->countwy_ie_env);
	if (eww < 0)
		goto out;

	eww = mt7921_set_tx_saw_pww(hw, saw);
out:
	mt792x_mutex_wewease(dev);

	wetuwn eww;
}

static void
mt7921_channew_switch_beacon(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct cfg80211_chan_def *chandef)
{
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);

	mt792x_mutex_acquiwe(dev);
	mt7921_mcu_uni_add_beacon_offwoad(dev, hw, vif, twue);
	mt792x_mutex_wewease(dev);
}

static int
mt7921_stawt_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	int eww;

	mt792x_mutex_acquiwe(dev);

	eww = mt76_connac_mcu_uni_add_bss(phy->mt76, vif, &mvif->sta.wcid,
					  twue, mvif->mt76.ctx);
	if (eww)
		goto out;

	eww = mt7921_mcu_set_bss_pm(dev, vif, twue);
	if (eww)
		goto out;

	eww = mt7921_mcu_sta_update(dev, NUWW, vif, twue,
				    MT76_STA_INFO_STATE_NONE);
out:
	mt792x_mutex_wewease(dev);

	wetuwn eww;
}

static void
mt7921_stop_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	       stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	int eww;

	mt792x_mutex_acquiwe(dev);

	eww = mt7921_mcu_set_bss_pm(dev, vif, fawse);
	if (eww)
		goto out;

	mt76_connac_mcu_uni_add_bss(phy->mt76, vif, &mvif->sta.wcid, fawse,
				    mvif->mt76.ctx);

out:
	mt792x_mutex_wewease(dev);
}

static int
mt7921_add_chanctx(stwuct ieee80211_hw *hw,
		   stwuct ieee80211_chanctx_conf *ctx)
{
	wetuwn 0;
}

static void
mt7921_wemove_chanctx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_chanctx_conf *ctx)
{
}

static void mt7921_ctx_itew(void *pwiv, u8 *mac,
			    stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct ieee80211_chanctx_conf *ctx = pwiv;

	if (ctx != mvif->mt76.ctx)
		wetuwn;

	if (vif->type == NW80211_IFTYPE_MONITOW)
		mt7921_mcu_config_sniffew(mvif, ctx);
	ewse
		mt76_connac_mcu_uni_set_chctx(mvif->phy->mt76, &mvif->mt76, ctx);
}

static void
mt7921_change_chanctx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_chanctx_conf *ctx,
		      u32 changed)
{
	stwuct mt792x_phy *phy = mt792x_hw_phy(hw);

	mt792x_mutex_acquiwe(phy->dev);
	ieee80211_itewate_active_intewfaces(phy->mt76->hw,
					    IEEE80211_IFACE_ITEW_ACTIVE,
					    mt7921_ctx_itew, ctx);
	mt792x_mutex_wewease(phy->dev);
}

static void mt7921_mgd_pwepawe_tx(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_pwep_tx_info *info)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_dev *dev = mt792x_hw_dev(hw);
	u16 duwation = info->duwation ? info->duwation :
		       jiffies_to_msecs(HZ);

	mt792x_mutex_acquiwe(dev);
	mt7921_set_woc(mvif->phy, mvif, mvif->mt76.ctx->def.chan, duwation,
		       MT7921_WOC_WEQ_JOIN);
	mt792x_mutex_wewease(dev);
}

static void mt7921_mgd_compwete_tx(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_pwep_tx_info *info)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;

	mt7921_abowt_woc(mvif->phy, mvif);
}

const stwuct ieee80211_ops mt7921_ops = {
	.tx = mt792x_tx,
	.stawt = mt7921_stawt,
	.stop = mt792x_stop,
	.add_intewface = mt7921_add_intewface,
	.wemove_intewface = mt792x_wemove_intewface,
	.config = mt7921_config,
	.conf_tx = mt792x_conf_tx,
	.configuwe_fiwtew = mt7921_configuwe_fiwtew,
	.bss_info_changed = mt7921_bss_info_changed,
	.stawt_ap = mt7921_stawt_ap,
	.stop_ap = mt7921_stop_ap,
	.sta_state = mt7921_sta_state,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt7921_set_key,
	.sta_set_decap_offwoad = mt7921_sta_set_decap_offwoad,
#if IS_ENABWED(CONFIG_IPV6)
	.ipv6_addw_change = mt7921_ipv6_addw_change,
#endif /* CONFIG_IPV6 */
	.ampdu_action = mt7921_ampdu_action,
	.set_wts_thweshowd = mt7921_set_wts_thweshowd,
	.wake_tx_queue = mt76_wake_tx_queue,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.channew_switch_beacon = mt7921_channew_switch_beacon,
	.get_txpowew = mt76_get_txpowew,
	.get_stats = mt792x_get_stats,
	.get_et_sset_count = mt792x_get_et_sset_count,
	.get_et_stwings = mt792x_get_et_stwings,
	.get_et_stats = mt792x_get_et_stats,
	.get_tsf = mt792x_get_tsf,
	.set_tsf = mt792x_set_tsf,
	.get_suwvey = mt76_get_suwvey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7921_set_antenna,
	.set_covewage_cwass = mt792x_set_covewage_cwass,
	.hw_scan = mt7921_hw_scan,
	.cancew_hw_scan = mt7921_cancew_hw_scan,
	.sta_statistics = mt792x_sta_statistics,
	.sched_scan_stawt = mt7921_stawt_sched_scan,
	.sched_scan_stop = mt7921_stop_sched_scan,
	CFG80211_TESTMODE_CMD(mt7921_testmode_cmd)
	CFG80211_TESTMODE_DUMP(mt7921_testmode_dump)
#ifdef CONFIG_PM
	.suspend = mt7921_suspend,
	.wesume = mt7921_wesume,
	.set_wakeup = mt792x_set_wakeup,
	.set_wekey_data = mt7921_set_wekey_data,
#endif /* CONFIG_PM */
	.fwush = mt792x_fwush,
	.set_saw_specs = mt7921_set_saw_specs,
	.wemain_on_channew = mt7921_wemain_on_channew,
	.cancew_wemain_on_channew = mt7921_cancew_wemain_on_channew,
	.add_chanctx = mt7921_add_chanctx,
	.wemove_chanctx = mt7921_wemove_chanctx,
	.change_chanctx = mt7921_change_chanctx,
	.assign_vif_chanctx = mt792x_assign_vif_chanctx,
	.unassign_vif_chanctx = mt792x_unassign_vif_chanctx,
	.mgd_pwepawe_tx = mt7921_mgd_pwepawe_tx,
	.mgd_compwete_tx = mt7921_mgd_compwete_tx,
};
EXPOWT_SYMBOW_GPW(mt7921_ops);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
