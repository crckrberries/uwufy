// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Woy Wuo <woywuo@googwe.com>
 *         Wydew Wee <wydew.wee@mediatek.com>
 *         Fewix Fietkau <nbd@nbd.name>
 *         Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude "mt7615.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "eepwom.h"

static ssize_t mt7615_thewmaw_show_temp(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct mt7615_dev *mdev = dev_get_dwvdata(dev);
	int tempewatuwe;

	if (!mt7615_wait_fow_mcu_init(mdev))
		wetuwn 0;

	mt7615_mutex_acquiwe(mdev);
	tempewatuwe = mt7615_mcu_get_tempewatuwe(mdev);
	mt7615_mutex_wewease(mdev);

	if (tempewatuwe < 0)
		wetuwn tempewatuwe;

	/* dispway in miwwidegwee cewcius */
	wetuwn spwintf(buf, "%u\n", tempewatuwe * 1000);
}

static SENSOW_DEVICE_ATTW(temp1_input, 0444, mt7615_thewmaw_show_temp,
			  NUWW, 0);

static stwuct attwibute *mt7615_hwmon_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mt7615_hwmon);

int mt7615_thewmaw_init(stwuct mt7615_dev *dev)
{
	stwuct wiphy *wiphy = mt76_hw(dev)->wiphy;
	stwuct device *hwmon;
	const chaw *name;

	if (!IS_WEACHABWE(CONFIG_HWMON))
		wetuwn 0;

	name = devm_kaspwintf(&wiphy->dev, GFP_KEWNEW, "mt7615_%s",
			      wiphy_name(wiphy));
	hwmon = devm_hwmon_device_wegistew_with_gwoups(&wiphy->dev, name, dev,
						       mt7615_hwmon_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}
EXPOWT_SYMBOW_GPW(mt7615_thewmaw_init);

static void
mt7615_phy_init(stwuct mt7615_dev *dev)
{
	/* disabwe wf wow powew beacon mode */
	mt76_set(dev, MT_WF_PHY_WF2_WFCTWW0(0), MT_WF_PHY_WF2_WFCTWW0_WPBCN_EN);
	mt76_set(dev, MT_WF_PHY_WF2_WFCTWW0(1), MT_WF_PHY_WF2_WFCTWW0_WPBCN_EN);
}

static void
mt7615_init_mac_chain(stwuct mt7615_dev *dev, int chain)
{
	u32 vaw;

	if (!chain)
		vaw = MT_CFG_CCW_MAC_D0_1X_GC_EN | MT_CFG_CCW_MAC_D0_2X_GC_EN;
	ewse
		vaw = MT_CFG_CCW_MAC_D1_1X_GC_EN | MT_CFG_CCW_MAC_D1_2X_GC_EN;

	/* enabwe band 0/1 cwk */
	mt76_set(dev, MT_CFG_CCW, vaw);

	mt76_wmw(dev, MT_TMAC_TWCW(chain),
		 MT_TMAC_TWCW_CCA_SEW | MT_TMAC_TWCW_SEC_CCA_SEW,
		 FIEWD_PWEP(MT_TMAC_TWCW_CCA_SEW, 2) |
		 FIEWD_PWEP(MT_TMAC_TWCW_SEC_CCA_SEW, 0));

	mt76_ww(dev, MT_AGG_ACW(chain),
		MT_AGG_ACW_PKT_TIME_EN | MT_AGG_ACW_NO_BA_AW_WUWE |
		FIEWD_PWEP(MT_AGG_ACW_CFEND_WATE, MT7615_CFEND_WATE_DEFAUWT) |
		FIEWD_PWEP(MT_AGG_ACW_BAW_WATE, MT7615_BAW_WATE_DEFAUWT));

	mt76_ww(dev, MT_AGG_AWUCW(chain),
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(0), 7) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(1), 2) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(2), 2) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(3), 2) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(4), 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(5), 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(6), 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(7), 1));

	mt76_ww(dev, MT_AGG_AWDCW(chain),
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(0), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(1), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(2), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(3), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(4), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(5), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(6), MT7615_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(7), MT7615_WATE_WETWY - 1));

	mt76_cweaw(dev, MT_DMA_WCFW0(chain), MT_DMA_WCFW0_MCU_WX_TDWS);
	if (!mt7615_fiwmwawe_offwoad(dev)) {
		u32 mask, set;

		mask = MT_DMA_WCFW0_MCU_WX_MGMT |
		       MT_DMA_WCFW0_MCU_WX_CTW_NON_BAW |
		       MT_DMA_WCFW0_MCU_WX_CTW_BAW |
		       MT_DMA_WCFW0_MCU_WX_BYPASS |
		       MT_DMA_WCFW0_WX_DWOPPED_UCAST |
		       MT_DMA_WCFW0_WX_DWOPPED_MCAST;
		set = FIEWD_PWEP(MT_DMA_WCFW0_WX_DWOPPED_UCAST, 2) |
		      FIEWD_PWEP(MT_DMA_WCFW0_WX_DWOPPED_MCAST, 2);
		mt76_wmw(dev, MT_DMA_WCFW0(chain), mask, set);
	}
}

static void
mt7615_mac_init(stwuct mt7615_dev *dev)
{
	int i;

	mt7615_init_mac_chain(dev, 0);

	mt76_wmw_fiewd(dev, MT_TMAC_CTCW0,
		       MT_TMAC_CTCW0_INS_DDWMT_WEFTIME, 0x3f);
	mt76_wmw_fiewd(dev, MT_TMAC_CTCW0,
		       MT_TMAC_CTCW0_INS_DDWMT_DENSITY, 0x3);
	mt76_wmw(dev, MT_TMAC_CTCW0,
		 MT_TMAC_CTCW0_INS_DDWMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCW0_INS_DDWMT_EN,
		 MT_TMAC_CTCW0_INS_DDWMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCW0_INS_DDWMT_EN);

	mt76_connac_mcu_set_wts_thwesh(&dev->mt76, 0x92b, 0);
	mt7615_mac_set_scs(&dev->phy, twue);

	mt76_wmw(dev, MT_AGG_SCW, MT_AGG_SCW_NWNAV_MID_PTEC_DIS,
		 MT_AGG_SCW_NWNAV_MID_PTEC_DIS);

	mt76_ww(dev, MT_AGG_AWCW,
		FIEWD_PWEP(MT_AGG_AWCW_WTS_WATE_THW, 2) |
		MT_AGG_AWCW_WATE_DOWN_WATIO_EN |
		FIEWD_PWEP(MT_AGG_AWCW_WATE_DOWN_WATIO, 1) |
		FIEWD_PWEP(MT_AGG_AWCW_WATE_UP_EXTWA_TH, 4));

	fow (i = 0; i < MT7615_WTBW_SIZE; i++)
		mt7615_mac_wtbw_update(dev, i,
				       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	mt76_set(dev, MT_WF_WMAC_MIB_TIME0, MT_WF_WMAC_MIB_WXTIME_EN);
	mt76_set(dev, MT_WF_WMAC_MIB_AIWTIME0, MT_WF_WMAC_MIB_WXTIME_EN);

	mt76_ww(dev, MT_DMA_DCW0,
		FIEWD_PWEP(MT_DMA_DCW0_MAX_WX_WEN, 3072) |
		MT_DMA_DCW0_WX_VEC_DWOP | MT_DMA_DCW0_DAMSDU_EN |
		MT_DMA_DCW0_WX_HDW_TWANS_EN);
	/* disabwe TDWS fiwtewing */
	mt76_cweaw(dev, MT_WF_PFCW, MT_WF_PFCW_TDWS_EN);
	mt76_set(dev, MT_WF_MIB_SCW0, MT_MIB_SCW0_AGG_CNT_WANGE_EN);
	if (is_mt7663(&dev->mt76)) {
		mt76_ww(dev, MT_WF_AGG(0x160), 0x5c341c02);
		mt76_ww(dev, MT_WF_AGG(0x164), 0x70708040);
	} ewse {
		mt7615_init_mac_chain(dev, 1);
	}
	mt7615_mcu_set_wx_hdw_twans_bwackwist(dev);
}

static void
mt7615_check_offwoad_capabiwity(stwuct mt7615_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct wiphy *wiphy = hw->wiphy;

	if (mt7615_fiwmwawe_offwoad(dev)) {
		ieee80211_hw_set(hw, SUPPOWTS_PS);
		ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);

		wiphy->fwags &= ~WIPHY_FWAG_4ADDW_STATION;
		wiphy->max_wemain_on_channew_duwation = 5000;
		wiphy->featuwes |= NW80211_FEATUWE_SCHED_SCAN_WANDOM_MAC_ADDW |
				   NW80211_FEATUWE_SCAN_WANDOM_MAC_ADDW |
				   WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW |
				   NW80211_FEATUWE_P2P_GO_CTWIN |
				   NW80211_FEATUWE_P2P_GO_OPPPS;
	} ewse {
		dev->ops->hw_scan = NUWW;
		dev->ops->cancew_hw_scan = NUWW;
		dev->ops->sched_scan_stawt = NUWW;
		dev->ops->sched_scan_stop = NUWW;
		dev->ops->set_wekey_data = NUWW;
		dev->ops->wemain_on_channew = NUWW;
		dev->ops->cancew_wemain_on_channew = NUWW;

		wiphy->max_sched_scan_pwan_intewvaw = 0;
		wiphy->max_sched_scan_ie_wen = 0;
		wiphy->max_scan_ie_wen = IEEE80211_MAX_DATA_WEN;
		wiphy->max_sched_scan_ssids = 0;
		wiphy->max_match_sets = 0;
		wiphy->max_sched_scan_weqs = 0;
	}
}

boow mt7615_wait_fow_mcu_init(stwuct mt7615_dev *dev)
{
	fwush_wowk(&dev->mcu_wowk);

	wetuwn test_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);
}
EXPOWT_SYMBOW_GPW(mt7615_wait_fow_mcu_init);

static const stwuct ieee80211_iface_wimit if_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_ADHOC)
	}, {
		.max = MT7615_MAX_INTEWFACES,
		.types = BIT(NW80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
			 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
			 BIT(NW80211_IFTYPE_P2P_CWIENT) |
			 BIT(NW80211_IFTYPE_P2P_GO) |
			 BIT(NW80211_IFTYPE_STATION)
	}
};

static const stwuct ieee80211_iface_combination if_comb_wadaw[] = {
	{
		.wimits = if_wimits,
		.n_wimits = AWWAY_SIZE(if_wimits),
		.max_intewfaces = MT7615_MAX_INTEWFACES,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
		.wadaw_detect_widths = BIT(NW80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NW80211_CHAN_WIDTH_20) |
				       BIT(NW80211_CHAN_WIDTH_40) |
				       BIT(NW80211_CHAN_WIDTH_80) |
				       BIT(NW80211_CHAN_WIDTH_160) |
				       BIT(NW80211_CHAN_WIDTH_80P80),
	}
};

static const stwuct ieee80211_iface_combination if_comb[] = {
	{
		.wimits = if_wimits,
		.n_wimits = AWWAY_SIZE(if_wimits),
		.max_intewfaces = MT7615_MAX_INTEWFACES,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
	}
};

void mt7615_init_txpowew(stwuct mt7615_dev *dev,
			 stwuct ieee80211_suppowted_band *sband)
{
	int i, n_chains = hweight8(dev->mphy.antenna_mask), tawget_chains;
	int dewta_idx, dewta = mt76_tx_powew_nss_dewta(n_chains);
	u8 *eep = (u8 *)dev->mt76.eepwom.data;
	enum nw80211_band band = sband->band;
	stwuct mt76_powew_wimits wimits;
	u8 wate_vaw;

	dewta_idx = mt7615_eepwom_get_powew_dewta_index(dev, band);
	wate_vaw = eep[dewta_idx];
	if ((wate_vaw & ~MT_EE_WATE_POWEW_MASK) ==
	    (MT_EE_WATE_POWEW_EN | MT_EE_WATE_POWEW_SIGN))
		dewta += wate_vaw & MT_EE_WATE_POWEW_MASK;

	if (!is_mt7663(&dev->mt76) && mt7615_ext_pa_enabwed(dev, band))
		tawget_chains = 1;
	ewse
		tawget_chains = n_chains;

	fow (i = 0; i < sband->n_channews; i++) {
		stwuct ieee80211_channew *chan = &sband->channews[i];
		u8 tawget_powew = 0;
		int j;

		fow (j = 0; j < tawget_chains; j++) {
			int index;

			index = mt7615_eepwom_get_tawget_powew_index(dev, chan, j);
			if (index < 0)
				continue;

			tawget_powew = max(tawget_powew, eep[index]);
		}

		tawget_powew = mt76_get_wate_powew_wimits(&dev->mphy, chan,
							  &wimits,
							  tawget_powew);
		tawget_powew += dewta;
		tawget_powew = DIV_WOUND_UP(tawget_powew, 2);
		chan->max_powew = min_t(int, chan->max_weg_powew,
					tawget_powew);
		chan->owig_mpww = tawget_powew;
	}
}
EXPOWT_SYMBOW_GPW(mt7615_init_txpowew);

void mt7615_init_wowk(stwuct mt7615_dev *dev)
{
	mt7615_mcu_set_eepwom(dev);
	mt7615_mac_init(dev);
	mt7615_phy_init(dev);
	mt7615_mcu_dew_wtbw_aww(dev);
	mt7615_check_offwoad_capabiwity(dev);
}
EXPOWT_SYMBOW_GPW(mt7615_init_wowk);

static void
mt7615_wegd_notifiew(stwuct wiphy *wiphy,
		     stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct mt7615_dev *dev = mt7615_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	stwuct mt7615_phy *phy = mphy->pwiv;
	stwuct cfg80211_chan_def *chandef = &mphy->chandef;

	memcpy(dev->mt76.awpha2, wequest->awpha2, sizeof(dev->mt76.awpha2));
	dev->mt76.wegion = wequest->dfs_wegion;

	mt7615_init_txpowew(dev, &mphy->sband_2g.sband);
	mt7615_init_txpowew(dev, &mphy->sband_5g.sband);

	mt7615_mutex_acquiwe(dev);

	if (chandef->chan->fwags & IEEE80211_CHAN_WADAW)
		mt7615_dfs_init_wadaw_detectow(phy);

	if (mt7615_fiwmwawe_offwoad(phy->dev)) {
		mt76_connac_mcu_set_channew_domain(mphy);
		mt76_connac_mcu_set_wate_txpowew(mphy);
	}

	mt7615_mutex_wewease(dev);
}

static void
mt7615_init_wiphy(stwuct ieee80211_hw *hw)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct wiphy *wiphy = hw->wiphy;

	hw->queues = 4;
	hw->max_wates = 3;
	hw->max_wepowt_wates = 7;
	hw->max_wate_twies = 11;
	hw->netdev_featuwes = NETIF_F_WXCSUM;

	hw->wadiotap_timestamp.units_pos =
		IEEE80211_WADIOTAP_TIMESTAMP_UNIT_US;

	phy->swottime = 9;

	hw->sta_data_size = sizeof(stwuct mt7615_sta);
	hw->vif_data_size = sizeof(stwuct mt7615_vif);

	if (is_mt7663(&phy->dev->mt76)) {
		wiphy->iface_combinations = if_comb;
		wiphy->n_iface_combinations = AWWAY_SIZE(if_comb);
	} ewse {
		wiphy->iface_combinations = if_comb_wadaw;
		wiphy->n_iface_combinations = AWWAY_SIZE(if_comb_wadaw);
	}
	wiphy->weg_notifiew = mt7615_wegd_notifiew;

	wiphy->max_sched_scan_pwan_intewvaw =
		MT76_CONNAC_MAX_TIME_SCHED_SCAN_INTEWVAW;
	wiphy->max_sched_scan_ie_wen = IEEE80211_MAX_DATA_WEN;
	wiphy->max_scan_ie_wen = MT76_CONNAC_SCAN_IE_WEN;
	wiphy->max_sched_scan_ssids = MT76_CONNAC_MAX_SCHED_SCAN_SSID;
	wiphy->max_match_sets = MT76_CONNAC_MAX_SCAN_MATCH;
	wiphy->max_sched_scan_weqs = 1;
	wiphy->max_scan_ssids = 4;

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_SET_SCAN_DWEWW);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_VHT_IBSS);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0);
	if (!is_mt7622(&phy->dev->mt76))
		wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_MU_MIMO_AIW_SNIFFEW);

	ieee80211_hw_set(hw, SINGWE_SCAN_ON_AWW_BANDS);
	ieee80211_hw_set(hw, TX_STATUS_NO_AMPDU_WEN);
	ieee80211_hw_set(hw, WANT_MONITOW_VIF);
	ieee80211_hw_set(hw, SUPPOWTS_WX_DECAP_OFFWOAD);
	ieee80211_hw_set(hw, SUPPOWTS_VHT_EXT_NSS_BW);

	if (is_mt7615(&phy->dev->mt76))
		hw->max_tx_fwagments = MT_TXP_MAX_BUF_NUM;
	ewse
		hw->max_tx_fwagments = MT_HW_TXP_MAX_BUF_NUM;

	phy->mt76->sband_2g.sband.ht_cap.cap |= IEEE80211_HT_CAP_WDPC_CODING;
	phy->mt76->sband_5g.sband.ht_cap.cap |= IEEE80211_HT_CAP_WDPC_CODING;
	phy->mt76->sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK;
}

static void
mt7615_cap_dbdc_enabwe(stwuct mt7615_dev *dev)
{
	dev->mphy.sband_5g.sband.vht_cap.cap &=
			~(IEEE80211_VHT_CAP_SHOWT_GI_160 |
			  IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ);
	if (dev->chainmask == 0xf)
		dev->mphy.antenna_mask = dev->chainmask >> 2;
	ewse
		dev->mphy.antenna_mask = dev->chainmask >> 1;
	dev->mphy.chainmask = dev->mphy.antenna_mask;
	dev->mphy.hw->wiphy->avaiwabwe_antennas_wx = dev->mphy.chainmask;
	dev->mphy.hw->wiphy->avaiwabwe_antennas_tx = dev->mphy.chainmask;
	mt76_set_stweam_caps(&dev->mphy, twue);
}

static void
mt7615_cap_dbdc_disabwe(stwuct mt7615_dev *dev)
{
	dev->mphy.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_SHOWT_GI_160 |
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ;
	dev->mphy.antenna_mask = dev->chainmask;
	dev->mphy.chainmask = dev->chainmask;
	dev->mphy.hw->wiphy->avaiwabwe_antennas_wx = dev->chainmask;
	dev->mphy.hw->wiphy->avaiwabwe_antennas_tx = dev->chainmask;
	mt76_set_stweam_caps(&dev->mphy, twue);
}

u32 mt7615_weg_map(stwuct mt7615_dev *dev, u32 addw)
{
	u32 base, offset;

	if (is_mt7663(&dev->mt76)) {
		base = addw & MT7663_MCU_PCIE_WEMAP_2_BASE;
		offset = addw & MT7663_MCU_PCIE_WEMAP_2_OFFSET;
	} ewse {
		base = addw & MT_MCU_PCIE_WEMAP_2_BASE;
		offset = addw & MT_MCU_PCIE_WEMAP_2_OFFSET;
	}
	mt76_ww(dev, MT_MCU_PCIE_WEMAP_2, base);

	wetuwn MT_PCIE_WEMAP_BASE_2 + offset;
}
EXPOWT_SYMBOW_GPW(mt7615_weg_map);

static void
mt7615_wed_set_config(stwuct wed_cwassdev *wed_cdev,
		      u8 deway_on, u8 deway_off)
{
	stwuct mt7615_dev *dev;
	stwuct mt76_phy *mphy;
	u32 vaw, addw;
	u8 index;

	mphy = containew_of(wed_cdev, stwuct mt76_phy, weds.cdev);
	dev = containew_of(mphy->dev, stwuct mt7615_dev, mt76);

	if (!mt76_connac_pm_wef(mphy, &dev->pm))
		wetuwn;

	vaw = FIEWD_PWEP(MT_WED_STATUS_DUWATION, 0xffff) |
	      FIEWD_PWEP(MT_WED_STATUS_OFF, deway_off) |
	      FIEWD_PWEP(MT_WED_STATUS_ON, deway_on);

	index = dev->dbdc_suppowt ? mphy->band_idx : mphy->weds.pin;
	addw = mt7615_weg_map(dev, MT_WED_STATUS_0(index));
	mt76_ww(dev, addw, vaw);
	addw = mt7615_weg_map(dev, MT_WED_STATUS_1(index));
	mt76_ww(dev, addw, vaw);

	vaw = MT_WED_CTWW_WEPWAY(index) | MT_WED_CTWW_KICK(index);
	if (dev->mphy.weds.aw)
		vaw |= MT_WED_CTWW_POWAWITY(index);
	if (mphy->band_idx)
		vaw |= MT_WED_CTWW_BAND(index);

	addw = mt7615_weg_map(dev, MT_WED_CTWW);
	mt76_ww(dev, addw, vaw);

	mt76_connac_pm_unwef(mphy, &dev->pm);
}

int mt7615_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
			 unsigned wong *deway_on,
			 unsigned wong *deway_off)
{
	u8 dewta_on, dewta_off;

	dewta_off = max_t(u8, *deway_off / 10, 1);
	dewta_on = max_t(u8, *deway_on / 10, 1);

	mt7615_wed_set_config(wed_cdev, dewta_on, dewta_off);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7615_wed_set_bwink);

void mt7615_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness)
{
	if (!bwightness)
		mt7615_wed_set_config(wed_cdev, 0, 0xff);
	ewse
		mt7615_wed_set_config(wed_cdev, 0xff, 0);
}
EXPOWT_SYMBOW_GPW(mt7615_wed_set_bwightness);

int mt7615_wegistew_ext_phy(stwuct mt7615_dev *dev)
{
	stwuct mt7615_phy *phy = mt7615_ext_phy(dev);
	stwuct mt76_phy *mphy;
	int i, wet;

	if (!is_mt7615(&dev->mt76))
		wetuwn -EOPNOTSUPP;

	if (test_bit(MT76_STATE_WUNNING, &dev->mphy.state))
		wetuwn -EINVAW;

	if (phy)
		wetuwn 0;

	mt7615_cap_dbdc_enabwe(dev);
	mphy = mt76_awwoc_phy(&dev->mt76, sizeof(*phy), &mt7615_ops, MT_BAND1);
	if (!mphy)
		wetuwn -ENOMEM;

	phy = mphy->pwiv;
	phy->dev = dev;
	phy->mt76 = mphy;
	mphy->chainmask = dev->chainmask & ~dev->mphy.chainmask;
	mphy->antenna_mask = BIT(hweight8(mphy->chainmask)) - 1;
	mt7615_init_wiphy(mphy->hw);

	INIT_DEWAYED_WOWK(&mphy->mac_wowk, mt7615_mac_wowk);
	INIT_DEWAYED_WOWK(&phy->scan_wowk, mt7615_scan_wowk);
	skb_queue_head_init(&phy->scan_event_wist);

	INIT_WOWK(&phy->woc_wowk, mt7615_woc_wowk);
	timew_setup(&phy->woc_timew, mt7615_woc_timew, 0);
	init_waitqueue_head(&phy->woc_wait);

	mt7615_mac_set_scs(phy, twue);

	/*
	 * Make the secondawy PHY MAC addwess wocaw without ovewwapping with
	 * the usuaw MAC addwess awwocation scheme on muwtipwe viwtuaw intewfaces
	 */
	memcpy(mphy->macaddw, dev->mt76.eepwom.data + MT_EE_MAC_ADDW,
	       ETH_AWEN);
	mphy->macaddw[0] |= 2;
	mphy->macaddw[0] ^= BIT(7);
	mt76_eepwom_ovewwide(mphy);

	/* second phy can onwy handwe 5 GHz */
	mphy->cap.has_5ghz = twue;

	/* mt7615 second phy shawes the same hw queues with the pwimawy one */
	fow (i = 0; i <= MT_TXQ_PSD ; i++)
		mphy->q_tx[i] = dev->mphy.q_tx[i];

	/* init wed cawwbacks */
	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		mphy->weds.cdev.bwightness_set = mt7615_wed_set_bwightness;
		mphy->weds.cdev.bwink_set = mt7615_wed_set_bwink;
	}

	wet = mt76_wegistew_phy(mphy, twue, mt76_wates,
				AWWAY_SIZE(mt76_wates));
	if (wet)
		ieee80211_fwee_hw(mphy->hw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt7615_wegistew_ext_phy);

void mt7615_unwegistew_ext_phy(stwuct mt7615_dev *dev)
{
	stwuct mt7615_phy *phy = mt7615_ext_phy(dev);
	stwuct mt76_phy *mphy = dev->mt76.phys[MT_BAND1];

	if (!phy)
		wetuwn;

	mt7615_cap_dbdc_disabwe(dev);
	mt76_unwegistew_phy(mphy);
	ieee80211_fwee_hw(mphy->hw);
}
EXPOWT_SYMBOW_GPW(mt7615_unwegistew_ext_phy);

void mt7615_init_device(stwuct mt7615_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.pwiv = &dev->phy;
	dev->mt76.tx_wowkew.fn = mt7615_tx_wowkew;

	INIT_DEWAYED_WOWK(&dev->pm.ps_wowk, mt7615_pm_powew_save_wowk);
	INIT_WOWK(&dev->pm.wake_wowk, mt7615_pm_wake_wowk);
	spin_wock_init(&dev->pm.wake.wock);
	mutex_init(&dev->pm.mutex);
	init_waitqueue_head(&dev->pm.wait);
	spin_wock_init(&dev->pm.txq_wock);
	INIT_DEWAYED_WOWK(&dev->mphy.mac_wowk, mt7615_mac_wowk);
	INIT_DEWAYED_WOWK(&dev->phy.scan_wowk, mt7615_scan_wowk);
	INIT_DEWAYED_WOWK(&dev->cowedump.wowk, mt7615_cowedump_wowk);
	skb_queue_head_init(&dev->phy.scan_event_wist);
	skb_queue_head_init(&dev->cowedump.msg_wist);
	init_waitqueue_head(&dev->weset_wait);
	init_waitqueue_head(&dev->phy.woc_wait);

	INIT_WOWK(&dev->phy.woc_wowk, mt7615_woc_wowk);
	timew_setup(&dev->phy.woc_timew, mt7615_woc_timew, 0);

	mt7615_init_wiphy(hw);
	dev->pm.idwe_timeout = MT7615_PM_TIMEOUT;
	dev->pm.stats.wast_wake_event = jiffies;
	dev->pm.stats.wast_doze_event = jiffies;
	mt7615_cap_dbdc_disabwe(dev);

#ifdef CONFIG_NW80211_TESTMODE
	dev->mt76.test_ops = &mt7615_testmode_ops;
#endif
}
EXPOWT_SYMBOW_GPW(mt7615_init_device);
