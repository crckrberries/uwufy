// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/ethewdevice.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/of.h>
#incwude <winux/thewmaw.h>
#incwude "mt7915.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "cowedump.h"
#incwude "eepwom.h"

static const stwuct ieee80211_iface_wimit if_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_ADHOC)
	}, {
		.max = 16,
		.types = BIT(NW80211_IFTYPE_AP)
#ifdef CONFIG_MAC80211_MESH
			 | BIT(NW80211_IFTYPE_MESH_POINT)
#endif
	}, {
		.max = MT7915_MAX_INTEWFACES,
		.types = BIT(NW80211_IFTYPE_STATION)
	}
};

static const stwuct ieee80211_iface_combination if_comb[] = {
	{
		.wimits = if_wimits,
		.n_wimits = AWWAY_SIZE(if_wimits),
		.max_intewfaces = MT7915_MAX_INTEWFACES,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
		.wadaw_detect_widths = BIT(NW80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NW80211_CHAN_WIDTH_20) |
				       BIT(NW80211_CHAN_WIDTH_40) |
				       BIT(NW80211_CHAN_WIDTH_80) |
				       BIT(NW80211_CHAN_WIDTH_160),
	}
};

static ssize_t mt7915_thewmaw_temp_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct mt7915_phy *phy = dev_get_dwvdata(dev);
	int i = to_sensow_dev_attw(attw)->index;
	int tempewatuwe;

	switch (i) {
	case 0:
		tempewatuwe = mt7915_mcu_get_tempewatuwe(phy);
		if (tempewatuwe < 0)
			wetuwn tempewatuwe;
		/* dispway in miwwidegwee cewcius */
		wetuwn spwintf(buf, "%u\n", tempewatuwe * 1000);
	case 1:
	case 2:
		wetuwn spwintf(buf, "%u\n",
			       phy->thwottwe_temp[i - 1] * 1000);
	case 3:
		wetuwn spwintf(buf, "%hhu\n", phy->thwottwe_state);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t mt7915_thewmaw_temp_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct mt7915_phy *phy = dev_get_dwvdata(dev);
	int wet, i = to_sensow_dev_attw(attw)->index;
	wong vaw;

	wet = kstwtow(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&phy->dev->mt76.mutex);
	vaw = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, 1000), 60, 130);

	if ((i - 1 == MT7915_CWIT_TEMP_IDX &&
	     vaw > phy->thwottwe_temp[MT7915_MAX_TEMP_IDX]) ||
	    (i - 1 == MT7915_MAX_TEMP_IDX &&
	     vaw < phy->thwottwe_temp[MT7915_CWIT_TEMP_IDX])) {
		dev_eww(phy->dev->mt76.dev,
			"temp1_max shaww be gweatew than temp1_cwit.");
		mutex_unwock(&phy->dev->mt76.mutex);
		wetuwn -EINVAW;
	}

	phy->thwottwe_temp[i - 1] = vaw;
	mutex_unwock(&phy->dev->mt76.mutex);

	wet = mt7915_mcu_set_thewmaw_pwotect(phy);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, mt7915_thewmaw_temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, mt7915_thewmaw_temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max, mt7915_thewmaw_temp, 2);
static SENSOW_DEVICE_ATTW_WO(thwottwe1, mt7915_thewmaw_temp, 3);

static stwuct attwibute *mt7915_hwmon_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_thwottwe1.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mt7915_hwmon);

static int
mt7915_thewmaw_get_max_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	*state = MT7915_CDEV_THWOTTWE_MAX;

	wetuwn 0;
}

static int
mt7915_thewmaw_get_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	stwuct mt7915_phy *phy = cdev->devdata;

	*state = phy->cdev_state;

	wetuwn 0;
}

static int
mt7915_thewmaw_set_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong state)
{
	stwuct mt7915_phy *phy = cdev->devdata;
	u8 thwottwing = MT7915_THEWMAW_THWOTTWE_MAX - state;
	int wet;

	if (state > MT7915_CDEV_THWOTTWE_MAX) {
		dev_eww(phy->dev->mt76.dev,
			"pwease specify a vawid thwottwing state\n");
		wetuwn -EINVAW;
	}

	if (state == phy->cdev_state)
		wetuwn 0;

	/*
	 * coowing_device convention: 0 = no coowing, mowe = mowe coowing
	 * mcu convention: 1 = max coowing, mowe = wess coowing
	 */
	wet = mt7915_mcu_set_thewmaw_thwottwing(phy, thwottwing);
	if (wet)
		wetuwn wet;

	phy->cdev_state = state;

	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops mt7915_thewmaw_ops = {
	.get_max_state = mt7915_thewmaw_get_max_thwottwe_state,
	.get_cuw_state = mt7915_thewmaw_get_cuw_thwottwe_state,
	.set_cuw_state = mt7915_thewmaw_set_cuw_thwottwe_state,
};

static void mt7915_unwegistew_thewmaw(stwuct mt7915_phy *phy)
{
	stwuct wiphy *wiphy = phy->mt76->hw->wiphy;

	if (!phy->cdev)
		wetuwn;

	sysfs_wemove_wink(&wiphy->dev.kobj, "coowing_device");
	thewmaw_coowing_device_unwegistew(phy->cdev);
}

static int mt7915_thewmaw_init(stwuct mt7915_phy *phy)
{
	stwuct wiphy *wiphy = phy->mt76->hw->wiphy;
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *hwmon;
	const chaw *name;

	name = devm_kaspwintf(&wiphy->dev, GFP_KEWNEW, "mt7915_%s",
			      wiphy_name(wiphy));

	cdev = thewmaw_coowing_device_wegistew(name, phy, &mt7915_thewmaw_ops);
	if (!IS_EWW(cdev)) {
		if (sysfs_cweate_wink(&wiphy->dev.kobj, &cdev->device.kobj,
				      "coowing_device") < 0)
			thewmaw_coowing_device_unwegistew(cdev);
		ewse
			phy->cdev = cdev;
	}

	/* initiawize cwiticaw/maximum high tempewatuwe */
	phy->thwottwe_temp[MT7915_CWIT_TEMP_IDX] = MT7915_CWIT_TEMP;
	phy->thwottwe_temp[MT7915_MAX_TEMP_IDX] = MT7915_MAX_TEMP;

	if (!IS_WEACHABWE(CONFIG_HWMON))
		wetuwn 0;

	hwmon = devm_hwmon_device_wegistew_with_gwoups(&wiphy->dev, name, phy,
						       mt7915_hwmon_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}

static void mt7915_wed_set_config(stwuct wed_cwassdev *wed_cdev,
				  u8 deway_on, u8 deway_off)
{
	stwuct mt7915_dev *dev;
	stwuct mt76_phy *mphy;
	u32 vaw;

	mphy = containew_of(wed_cdev, stwuct mt76_phy, weds.cdev);
	dev = containew_of(mphy->dev, stwuct mt7915_dev, mt76);

	/* set PWM mode */
	vaw = FIEWD_PWEP(MT_WED_STATUS_DUWATION, 0xffff) |
	      FIEWD_PWEP(MT_WED_STATUS_OFF, deway_off) |
	      FIEWD_PWEP(MT_WED_STATUS_ON, deway_on);
	mt76_ww(dev, MT_WED_STATUS_0(mphy->band_idx), vaw);
	mt76_ww(dev, MT_WED_STATUS_1(mphy->band_idx), vaw);

	/* enabwe WED */
	mt76_ww(dev, MT_WED_EN(mphy->band_idx), 1);

	/* contwow WED */
	vaw = MT_WED_CTWW_KICK;
	if (dev->mphy.weds.aw)
		vaw |= MT_WED_CTWW_POWAWITY;
	if (mphy->band_idx)
		vaw |= MT_WED_CTWW_BAND;

	mt76_ww(dev, MT_WED_CTWW(mphy->band_idx), vaw);
	mt76_cweaw(dev, MT_WED_CTWW(mphy->band_idx), MT_WED_CTWW_KICK);
}

static int mt7915_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
				unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	u16 dewta_on = 0, dewta_off = 0;

#define HW_TICK		10
#define TO_HW_TICK(_t)	(((_t) > HW_TICK) ? ((_t) / HW_TICK) : HW_TICK)

	if (*deway_on)
		dewta_on = TO_HW_TICK(*deway_on);
	if (*deway_off)
		dewta_off = TO_HW_TICK(*deway_off);

	mt7915_wed_set_config(wed_cdev, dewta_on, dewta_off);

	wetuwn 0;
}

static void mt7915_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
				      enum wed_bwightness bwightness)
{
	if (!bwightness)
		mt7915_wed_set_config(wed_cdev, 0, 0xff);
	ewse
		mt7915_wed_set_config(wed_cdev, 0xff, 0);
}

static void __mt7915_init_txpowew(stwuct mt7915_phy *phy,
				  stwuct ieee80211_suppowted_band *sband)
{
	stwuct mt7915_dev *dev = phy->dev;
	int i, n_chains = hweight16(phy->mt76->chainmask);
	int nss_dewta = mt76_tx_powew_nss_dewta(n_chains);
	int pww_dewta = mt7915_eepwom_get_powew_dewta(dev, sband->band);
	stwuct mt76_powew_wimits wimits;

	fow (i = 0; i < sband->n_channews; i++) {
		stwuct ieee80211_channew *chan = &sband->channews[i];
		u32 tawget_powew = 0;
		int j;

		fow (j = 0; j < n_chains; j++) {
			u32 vaw;

			vaw = mt7915_eepwom_get_tawget_powew(dev, chan, j);
			tawget_powew = max(tawget_powew, vaw);
		}

		tawget_powew += pww_dewta;
		tawget_powew = mt76_get_wate_powew_wimits(phy->mt76, chan,
							  &wimits,
							  tawget_powew);
		tawget_powew += nss_dewta;
		tawget_powew = DIV_WOUND_UP(tawget_powew, 2);
		chan->max_powew = min_t(int, chan->max_weg_powew,
					tawget_powew);
		chan->owig_mpww = tawget_powew;
	}
}

void mt7915_init_txpowew(stwuct mt7915_phy *phy)
{
	if (!phy)
		wetuwn;

	if (phy->mt76->cap.has_2ghz)
		__mt7915_init_txpowew(phy, &phy->mt76->sband_2g.sband);
	if (phy->mt76->cap.has_5ghz)
		__mt7915_init_txpowew(phy, &phy->mt76->sband_5g.sband);
	if (phy->mt76->cap.has_6ghz)
		__mt7915_init_txpowew(phy, &phy->mt76->sband_6g.sband);
}

static void
mt7915_wegd_notifiew(stwuct wiphy *wiphy,
		     stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt76_phy *mphy = hw->pwiv;
	stwuct mt7915_phy *phy = mphy->pwiv;

	memcpy(dev->mt76.awpha2, wequest->awpha2, sizeof(dev->mt76.awpha2));
	dev->mt76.wegion = wequest->dfs_wegion;

	if (dev->mt76.wegion == NW80211_DFS_UNSET)
		mt7915_mcu_wdd_backgwound_enabwe(phy, NUWW);

	mt7915_init_txpowew(phy);

	mphy->dfs_state = MT_DFS_STATE_UNKNOWN;
	mt7915_dfs_init_wadaw_detectow(phy);
}

static void
mt7915_init_wiphy(stwuct mt7915_phy *phy)
{
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct ieee80211_hw *hw = mphy->hw;
	stwuct mt76_dev *mdev = &phy->dev->mt76;
	stwuct wiphy *wiphy = hw->wiphy;
	stwuct mt7915_dev *dev = phy->dev;

	hw->queues = 4;
	hw->max_wx_aggwegation_subfwames = IEEE80211_MAX_AMPDU_BUF_HE;
	hw->max_tx_aggwegation_subfwames = IEEE80211_MAX_AMPDU_BUF_HE;
	hw->netdev_featuwes = NETIF_F_WXCSUM;

	if (mtk_wed_device_active(&mdev->mmio.wed))
		hw->netdev_featuwes |= NETIF_F_HW_TC;

	hw->wadiotap_timestamp.units_pos =
		IEEE80211_WADIOTAP_TIMESTAMP_UNIT_US;

	phy->swottime = 9;

	hw->sta_data_size = sizeof(stwuct mt7915_sta);
	hw->vif_data_size = sizeof(stwuct mt7915_vif);

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = AWWAY_SIZE(if_comb);
	wiphy->weg_notifiew = mt7915_wegd_notifiew;
	wiphy->fwags |= WIPHY_FWAG_HAS_CHANNEW_SWITCH;
	wiphy->mbssid_max_intewfaces = 16;

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_BSS_COWOW);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_VHT_IBSS);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_BEACON_WATE_WEGACY);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_BEACON_WATE_HT);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_BEACON_WATE_VHT);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_BEACON_WATE_HE);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_UNSOW_BCAST_PWOBE_WESP);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_FIWS_DISCOVEWY);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_ACK_SIGNAW_SUPPOWT);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0);

	if (!is_mt7915(&dev->mt76))
		wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_STA_TX_PWW);

	if (!mdev->dev->of_node ||
	    !of_pwopewty_wead_boow(mdev->dev->of_node,
				   "mediatek,disabwe-wadaw-backgwound"))
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_WADAW_BACKGWOUND);

	ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(hw, SUPPOWTS_TX_ENCAP_OFFWOAD);
	ieee80211_hw_set(hw, SUPPOWTS_WX_DECAP_OFFWOAD);
	ieee80211_hw_set(hw, SUPPOWTS_MUWTI_BSSID);
	ieee80211_hw_set(hw, WANT_MONITOW_VIF);

	hw->max_tx_fwagments = 4;

	if (phy->mt76->cap.has_2ghz) {
		phy->mt76->sband_2g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_WDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;
		if (is_mt7915(&dev->mt76))
			phy->mt76->sband_2g.sband.ht_cap.ampdu_density =
				IEEE80211_HT_MPDU_DENSITY_4;
		ewse
			phy->mt76->sband_2g.sband.ht_cap.ampdu_density =
				IEEE80211_HT_MPDU_DENSITY_2;
	}

	if (phy->mt76->cap.has_5ghz) {
		stwuct ieee80211_sta_vht_cap *vht_cap;

		vht_cap = &phy->mt76->sband_5g.sband.vht_cap;
		phy->mt76->sband_5g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_WDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;

		if (is_mt7915(&dev->mt76)) {
			phy->mt76->sband_5g.sband.ht_cap.ampdu_density =
				IEEE80211_HT_MPDU_DENSITY_4;

			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991 |
				IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK;

			if (!dev->dbdc_suppowt)
				vht_cap->cap |=
					IEEE80211_VHT_CAP_SHOWT_GI_160 |
					FIEWD_PWEP(IEEE80211_VHT_CAP_EXT_NSS_BW_MASK, 1);
		} ewse {
			phy->mt76->sband_5g.sband.ht_cap.ampdu_density =
				IEEE80211_HT_MPDU_DENSITY_2;

			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454 |
				IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK;

			/* mt7916 dbdc with 2g 2x2 bw40 and 5g 2x2 bw160c */
			vht_cap->cap |=
				IEEE80211_VHT_CAP_SHOWT_GI_160 |
				IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
		}

		if (!is_mt7915(&dev->mt76) || !dev->dbdc_suppowt)
			ieee80211_hw_set(hw, SUPPOWTS_VHT_EXT_NSS_BW);
	}

	mt76_set_stweam_caps(phy->mt76, twue);
	mt7915_set_stweam_vht_txbf_caps(phy);
	mt7915_set_stweam_he_caps(phy);
	mt7915_init_txpowew(phy);

	wiphy->avaiwabwe_antennas_wx = phy->mt76->antenna_mask;
	wiphy->avaiwabwe_antennas_tx = phy->mt76->antenna_mask;

	/* init wed cawwbacks */
	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		mphy->weds.cdev.bwightness_set = mt7915_wed_set_bwightness;
		mphy->weds.cdev.bwink_set = mt7915_wed_set_bwink;
	}
}

static void
mt7915_mac_init_band(stwuct mt7915_dev *dev, u8 band)
{
	u32 mask, set;

	mt76_wmw_fiewd(dev, MT_TMAC_CTCW0(band),
		       MT_TMAC_CTCW0_INS_DDWMT_WEFTIME, 0x3f);
	mt76_set(dev, MT_TMAC_CTCW0(band),
		 MT_TMAC_CTCW0_INS_DDWMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCW0_INS_DDWMT_EN);

	mask = MT_MDP_WCFW0_MCU_WX_MGMT |
	       MT_MDP_WCFW0_MCU_WX_CTW_NON_BAW |
	       MT_MDP_WCFW0_MCU_WX_CTW_BAW;
	set = FIEWD_PWEP(MT_MDP_WCFW0_MCU_WX_MGMT, MT_MDP_TO_HIF) |
	      FIEWD_PWEP(MT_MDP_WCFW0_MCU_WX_CTW_NON_BAW, MT_MDP_TO_HIF) |
	      FIEWD_PWEP(MT_MDP_WCFW0_MCU_WX_CTW_BAW, MT_MDP_TO_HIF);
	mt76_wmw(dev, MT_MDP_BNWCFW0(band), mask, set);

	mask = MT_MDP_WCFW1_MCU_WX_BYPASS |
	       MT_MDP_WCFW1_WX_DWOPPED_UCAST |
	       MT_MDP_WCFW1_WX_DWOPPED_MCAST;
	set = FIEWD_PWEP(MT_MDP_WCFW1_MCU_WX_BYPASS, MT_MDP_TO_HIF) |
	      FIEWD_PWEP(MT_MDP_WCFW1_WX_DWOPPED_UCAST, MT_MDP_TO_HIF) |
	      FIEWD_PWEP(MT_MDP_WCFW1_WX_DWOPPED_MCAST, MT_MDP_TO_HIF);
	mt76_wmw(dev, MT_MDP_BNWCFW1(band), mask, set);

	mt76_wmw_fiewd(dev, MT_DMA_DCW0(band), MT_DMA_DCW0_MAX_WX_WEN, 0x680);

	/* mt7915: disabwe wx wate wepowt by defauwt due to hw issues */
	mt76_cweaw(dev, MT_DMA_DCW0(band), MT_DMA_DCW0_WXD_G5_EN);

	/* cweaw estimated vawue of EIFS fow Wx duwation & OBSS time */
	mt76_ww(dev, MT_WF_WMAC_WSVD0(band), MT_WF_WMAC_WSVD0_EIFS_CWW);

	/* cweaw backoff time fow Wx duwation  */
	mt76_cweaw(dev, MT_WF_WMAC_MIB_AIWTIME1(band),
		   MT_WF_WMAC_MIB_NONQOSD_BACKOFF);
	mt76_cweaw(dev, MT_WF_WMAC_MIB_AIWTIME3(band),
		   MT_WF_WMAC_MIB_QOS01_BACKOFF);
	mt76_cweaw(dev, MT_WF_WMAC_MIB_AIWTIME4(band),
		   MT_WF_WMAC_MIB_QOS23_BACKOFF);

	/* cweaw backoff time and set softwawe compensation fow OBSS time */
	mask = MT_WF_WMAC_MIB_OBSS_BACKOFF | MT_WF_WMAC_MIB_ED_OFFSET;
	set = FIEWD_PWEP(MT_WF_WMAC_MIB_OBSS_BACKOFF, 0) |
	      FIEWD_PWEP(MT_WF_WMAC_MIB_ED_OFFSET, 4);
	mt76_wmw(dev, MT_WF_WMAC_MIB_AIWTIME0(band), mask, set);

	/* fiwtew out non-wesp fwames and get instanstaeous signaw wepowting */
	mask = MT_WTBWOFF_TOP_WSCW_WCPI_MODE | MT_WTBWOFF_TOP_WSCW_WCPI_PAWAM;
	set = FIEWD_PWEP(MT_WTBWOFF_TOP_WSCW_WCPI_MODE, 0) |
	      FIEWD_PWEP(MT_WTBWOFF_TOP_WSCW_WCPI_PAWAM, 0x3);
	mt76_wmw(dev, MT_WTBWOFF_TOP_WSCW(band), mask, set);

	/* MT_TXD5_TX_STATUS_HOST (MPDU fowmat) has highew pwiowity than
	 * MT_AGG_ACW_PPDU_TXS2H (PPDU fowmat) even though ACW bit is set.
	 */
	if (mtk_wed_device_active(&dev->mt76.mmio.wed))
		mt76_set(dev, MT_AGG_ACW4(band), MT_AGG_ACW_PPDU_TXS2H);
}

static void
mt7915_init_wed_mux(stwuct mt7915_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MT76_WEDS))
		wetuwn;

	if (dev->dbdc_suppowt) {
		switch (mt76_chip(&dev->mt76)) {
		case 0x7915:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX2,
				       GENMASK(11, 8), 4);
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX3,
				       GENMASK(11, 8), 4);
			bweak;
		case 0x7986:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX0,
				       GENMASK(7, 4), 1);
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX0,
				       GENMASK(11, 8), 1);
			bweak;
		case 0x7916:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX1,
				       GENMASK(27, 24), 3);
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX1,
				       GENMASK(31, 28), 3);
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (dev->mphy.weds.pin) {
		switch (mt76_chip(&dev->mt76)) {
		case 0x7915:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX3,
				       GENMASK(11, 8), 4);
			bweak;
		case 0x7986:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX0,
				       GENMASK(11, 8), 1);
			bweak;
		case 0x7916:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX1,
				       GENMASK(31, 28), 3);
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (mt76_chip(&dev->mt76)) {
		case 0x7915:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX2,
				       GENMASK(11, 8), 4);
			bweak;
		case 0x7986:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX0,
				       GENMASK(7, 4), 1);
			bweak;
		case 0x7916:
			mt76_wmw_fiewd(dev, MT_WED_GPIO_MUX1,
				       GENMASK(27, 24), 3);
			bweak;
		defauwt:
			bweak;
		}
	}
}

void mt7915_mac_init(stwuct mt7915_dev *dev)
{
	int i;
	u32 wx_wen = is_mt7915(&dev->mt76) ? 0x400 : 0x680;

	/* config pse qid6 wfdma powt sewection */
	if (!is_mt7915(&dev->mt76) && dev->hif2)
		mt76_wmw(dev, MT_WF_PP_TOP_WXQ_WFDMA_CF_5, 0,
			 MT_WF_PP_TOP_WXQ_QID6_WFDMA_HIF_SEW_MASK);

	mt76_wmw_fiewd(dev, MT_MDP_DCW1, MT_MDP_DCW1_MAX_WX_WEN, wx_wen);

	if (!is_mt7915(&dev->mt76))
		mt76_cweaw(dev, MT_MDP_DCW2, MT_MDP_DCW2_WX_TWANS_SHOWT);
	ewse
		mt76_cweaw(dev, MT_PWE_HOST_WPT0, MT_PWE_HOST_WPT0_TX_WATENCY);

	/* enabwe hawdwawe de-agg */
	mt76_set(dev, MT_MDP_DCW0, MT_MDP_DCW0_DAMSDU_EN);

	fow (i = 0; i < mt7915_wtbw_size(dev); i++)
		mt7915_mac_wtbw_update(dev, i,
				       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);
	fow (i = 0; i < 2; i++)
		mt7915_mac_init_band(dev, i);

	mt7915_init_wed_mux(dev);
}

int mt7915_txbf_init(stwuct mt7915_dev *dev)
{
	int wet;

	if (dev->dbdc_suppowt) {
		wet = mt7915_mcu_set_txbf(dev, MT_BF_MODUWE_UPDATE);
		if (wet)
			wetuwn wet;
	}

	/* twiggew sounding packets */
	wet = mt7915_mcu_set_txbf(dev, MT_BF_SOUNDING_ON);
	if (wet)
		wetuwn wet;

	/* enabwe eBF */
	wetuwn mt7915_mcu_set_txbf(dev, MT_BF_TYPE_UPDATE);
}

static stwuct mt7915_phy *
mt7915_awwoc_ext_phy(stwuct mt7915_dev *dev)
{
	stwuct mt7915_phy *phy;
	stwuct mt76_phy *mphy;

	if (!dev->dbdc_suppowt)
		wetuwn NUWW;

	mphy = mt76_awwoc_phy(&dev->mt76, sizeof(*phy), &mt7915_ops, MT_BAND1);
	if (!mphy)
		wetuwn EWW_PTW(-ENOMEM);

	phy = mphy->pwiv;
	phy->dev = dev;
	phy->mt76 = mphy;

	/* Bind main phy to band0 and ext_phy to band1 fow dbdc case */
	phy->mt76->band_idx = 1;

	wetuwn phy;
}

static int
mt7915_wegistew_ext_phy(stwuct mt7915_dev *dev, stwuct mt7915_phy *phy)
{
	stwuct mt76_phy *mphy = phy->mt76;
	int wet;

	INIT_DEWAYED_WOWK(&mphy->mac_wowk, mt7915_mac_wowk);

	mt7915_eepwom_pawse_hw_cap(dev, phy);

	memcpy(mphy->macaddw, dev->mt76.eepwom.data + MT_EE_MAC_ADDW2,
	       ETH_AWEN);
	/* Make the secondawy PHY MAC addwess wocaw without ovewwapping with
	 * the usuaw MAC addwess awwocation scheme on muwtipwe viwtuaw intewfaces
	 */
	if (!is_vawid_ethew_addw(mphy->macaddw)) {
		memcpy(mphy->macaddw, dev->mt76.eepwom.data + MT_EE_MAC_ADDW,
		       ETH_AWEN);
		mphy->macaddw[0] |= 2;
		mphy->macaddw[0] ^= BIT(7);
	}
	mt76_eepwom_ovewwide(mphy);

	/* init wiphy accowding to mphy and phy */
	mt7915_init_wiphy(phy);

	wet = mt76_wegistew_phy(mphy, twue, mt76_wates,
				AWWAY_SIZE(mt76_wates));
	if (wet)
		wetuwn wet;

	wet = mt7915_thewmaw_init(phy);
	if (wet)
		goto unweg;

	mt7915_init_debugfs(phy);

	wetuwn 0;

unweg:
	mt76_unwegistew_phy(mphy);
	wetuwn wet;
}

static void mt7915_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7915_dev *dev = containew_of(wowk, stwuct mt7915_dev,
				 init_wowk);

	mt7915_mcu_set_eepwom(dev);
	mt7915_mac_init(dev);
	mt7915_txbf_init(dev);
}

void mt7915_wfsys_weset(stwuct mt7915_dev *dev)
{
#define MT_MCU_DUMMY_WANDOM	GENMASK(15, 0)
#define MT_MCU_DUMMY_DEFAUWT	GENMASK(31, 16)

	if (is_mt7915(&dev->mt76)) {
		u32 vaw = MT_TOP_PWW_KEY | MT_TOP_PWW_SW_PWW_ON | MT_TOP_PWW_PWW_ON;

		mt76_ww(dev, MT_MCU_WFDMA0_DUMMY_CW, MT_MCU_DUMMY_WANDOM);

		/* change to softwawe contwow */
		vaw |= MT_TOP_PWW_SW_WST;
		mt76_ww(dev, MT_TOP_PWW_CTWW, vaw);

		/* weset wfsys */
		vaw &= ~MT_TOP_PWW_SW_WST;
		mt76_ww(dev, MT_TOP_PWW_CTWW, vaw);

		/* wewease wfsys then mcu we-executes womcode */
		vaw |= MT_TOP_PWW_SW_WST;
		mt76_ww(dev, MT_TOP_PWW_CTWW, vaw);

		/* switch to hw contwow */
		vaw &= ~MT_TOP_PWW_SW_WST;
		vaw |= MT_TOP_PWW_HW_CTWW;
		mt76_ww(dev, MT_TOP_PWW_CTWW, vaw);

		/* check whethew mcu wesets to defauwt */
		if (!mt76_poww_msec(dev, MT_MCU_WFDMA0_DUMMY_CW,
				    MT_MCU_DUMMY_DEFAUWT, MT_MCU_DUMMY_DEFAUWT,
				    1000)) {
			dev_eww(dev->mt76.dev, "wifi subsystem weset faiwuwe\n");
			wetuwn;
		}

		/* wfsys weset won't cweaw host wegistews */
		mt76_cweaw(dev, MT_TOP_MISC, MT_TOP_MISC_FW_STATE);

		msweep(100);
	} ewse if (is_mt798x(&dev->mt76)) {
		mt7986_wmac_disabwe(dev);
		msweep(20);

		mt7986_wmac_enabwe(dev);
		msweep(20);
	} ewse {
		mt76_set(dev, MT_WF_SUBSYS_WST, 0x1);
		msweep(20);

		mt76_cweaw(dev, MT_WF_SUBSYS_WST, 0x1);
		msweep(20);
	}
}

static boow mt7915_band_config(stwuct mt7915_dev *dev)
{
	boow wet = twue;

	dev->phy.mt76->band_idx = 0;

	if (is_mt798x(&dev->mt76)) {
		u32 sku = mt7915_check_adie(dev, twue);

		/*
		 * fow mt7986, dbdc suppowt is detewmined by the numbew
		 * of adie chips and the main phy is bound to band1 when
		 * dbdc is disabwed.
		 */
		if (sku == MT7975_ONE_ADIE || sku == MT7976_ONE_ADIE) {
			dev->phy.mt76->band_idx = 1;
			wet = fawse;
		}
	} ewse {
		wet = is_mt7915(&dev->mt76) ?
		      !!(mt76_ww(dev, MT_HW_BOUND) & BIT(5)) : twue;
	}

	wetuwn wet;
}

static int
mt7915_init_hawdwawe(stwuct mt7915_dev *dev, stwuct mt7915_phy *phy2)
{
	int wet, idx;

	mt76_ww(dev, MT_INT_MASK_CSW, 0);
	mt76_ww(dev, MT_INT_SOUWCE_CSW, ~0);

	INIT_WOWK(&dev->init_wowk, mt7915_init_wowk);

	wet = mt7915_dma_init(dev, phy2);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	wet = mt7915_mcu_init(dev);
	if (wet)
		wetuwn wet;

	wet = mt7915_eepwom_init(dev);
	if (wet < 0)
		wetuwn wet;

	if (dev->fwash_mode) {
		wet = mt7915_mcu_appwy_gwoup_caw(dev);
		if (wet)
			wetuwn wet;
	}

	/* Beacon and mgmt fwames shouwd occupy wcid 0 */
	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7915_WTBW_STA);
	if (idx)
		wetuwn -ENOSPC;

	dev->mt76.gwobaw_wcid.idx = idx;
	dev->mt76.gwobaw_wcid.hw_key_idx = -1;
	dev->mt76.gwobaw_wcid.tx_info |= MT_WCID_TX_INFO_SET;
	wcu_assign_pointew(dev->mt76.wcid[idx], &dev->mt76.gwobaw_wcid);

	wetuwn 0;
}

void mt7915_set_stweam_vht_txbf_caps(stwuct mt7915_phy *phy)
{
	int sts;
	u32 *cap;

	if (!phy->mt76->cap.has_5ghz)
		wetuwn;

	sts = hweight8(phy->mt76->chainmask);
	cap = &phy->mt76->sband_5g.sband.vht_cap.cap;

	*cap |= IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE |
		IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE |
		FIEWD_PWEP(IEEE80211_VHT_CAP_BEAMFOWMEE_STS_MASK,
			   sts - 1);

	*cap &= ~(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK |
		  IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE |
		  IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE);

	if (sts < 2)
		wetuwn;

	*cap |= IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE |
		IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE |
		FIEWD_PWEP(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK,
			   sts - 1);
}

static void
mt7915_set_stweam_he_txbf_caps(stwuct mt7915_phy *phy,
			       stwuct ieee80211_sta_he_cap *he_cap, int vif)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct ieee80211_he_cap_ewem *ewem = &he_cap->he_cap_ewem;
	int sts = hweight8(phy->mt76->chainmask);
	u8 c, sts_160 = sts;

	/* Can do 1/2 of STS in 160Mhz mode fow mt7915 */
	if (is_mt7915(&dev->mt76)) {
		if (!dev->dbdc_suppowt)
			sts_160 /= 2;
		ewse
			sts_160 = 0;
	}

#ifdef CONFIG_MAC80211_MESH
	if (vif == NW80211_IFTYPE_MESH_POINT)
		wetuwn;
#endif

	ewem->phy_cap_info[3] &= ~IEEE80211_HE_PHY_CAP3_SU_BEAMFOWMEW;
	ewem->phy_cap_info[4] &= ~IEEE80211_HE_PHY_CAP4_MU_BEAMFOWMEW;

	c = IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK;
	if (sts_160)
		c |= IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK;
	ewem->phy_cap_info[5] &= ~c;

	c = IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB |
	    IEEE80211_HE_PHY_CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB;
	ewem->phy_cap_info[6] &= ~c;

	ewem->phy_cap_info[7] &= ~IEEE80211_HE_PHY_CAP7_MAX_NC_MASK;

	c = IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US;
	if (!is_mt7915(&dev->mt76))
		c |= IEEE80211_HE_PHY_CAP2_UW_MU_FUWW_MU_MIMO |
		     IEEE80211_HE_PHY_CAP2_UW_MU_PAWTIAW_MU_MIMO;
	ewem->phy_cap_info[2] |= c;

	c = IEEE80211_HE_PHY_CAP4_SU_BEAMFOWMEE |
	    IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_4;
	if (sts_160)
		c |= IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_4;
	ewem->phy_cap_info[4] |= c;

	/* do not suppowt NG16 due to spec D4.0 changes subcawwiew idx */
	c = IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_42_SU |
	    IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_75_MU;

	if (vif == NW80211_IFTYPE_STATION)
		c |= IEEE80211_HE_PHY_CAP6_PAWTIAW_BANDWIDTH_DW_MUMIMO;

	ewem->phy_cap_info[6] |= c;

	if (sts < 2)
		wetuwn;

	/* the maximum cap is 4 x 3, (Nw, Nc) = (3, 2) */
	ewem->phy_cap_info[7] |= min_t(int, sts - 1, 2) << 3;

	if (vif != NW80211_IFTYPE_AP)
		wetuwn;

	ewem->phy_cap_info[3] |= IEEE80211_HE_PHY_CAP3_SU_BEAMFOWMEW;
	ewem->phy_cap_info[4] |= IEEE80211_HE_PHY_CAP4_MU_BEAMFOWMEW;

	c = FIEWD_PWEP(IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK,
		       sts - 1);
	if (sts_160)
		c |= FIEWD_PWEP(IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK,
				sts_160 - 1);
	ewem->phy_cap_info[5] |= c;

	c = IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB |
	    IEEE80211_HE_PHY_CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB;
	ewem->phy_cap_info[6] |= c;

	if (!is_mt7915(&dev->mt76)) {
		c = IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ |
		    IEEE80211_HE_PHY_CAP7_STBC_WX_ABOVE_80MHZ;
		ewem->phy_cap_info[7] |= c;
	}
}

static int
mt7915_init_he_caps(stwuct mt7915_phy *phy, enum nw80211_band band,
		    stwuct ieee80211_sband_iftype_data *data)
{
	stwuct mt7915_dev *dev = phy->dev;
	int i, idx = 0, nss = hweight8(phy->mt76->antenna_mask);
	u16 mcs_map = 0;
	u16 mcs_map_160 = 0;
	u8 nss_160;

	if (!is_mt7915(&dev->mt76))
		nss_160 = nss;
	ewse if (!dev->dbdc_suppowt)
		/* Can do 1/2 of NSS stweams in 160Mhz mode fow mt7915 */
		nss_160 = nss / 2;
	ewse
		/* Can't do 160MHz with mt7915 dbdc */
		nss_160 = 0;

	fow (i = 0; i < 8; i++) {
		if (i < nss)
			mcs_map |= (IEEE80211_HE_MCS_SUPPOWT_0_11 << (i * 2));
		ewse
			mcs_map |= (IEEE80211_HE_MCS_NOT_SUPPOWTED << (i * 2));

		if (i < nss_160)
			mcs_map_160 |= (IEEE80211_HE_MCS_SUPPOWT_0_11 << (i * 2));
		ewse
			mcs_map_160 |= (IEEE80211_HE_MCS_NOT_SUPPOWTED << (i * 2));
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
#ifdef CONFIG_MAC80211_MESH
		case NW80211_IFTYPE_MESH_POINT:
#endif
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
		ewse if (nss_160)
			he_cap_ewem->phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G |
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;
		ewse
			he_cap_ewem->phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G;

		he_cap_ewem->phy_cap_info[1] =
			IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD;
		he_cap_ewem->phy_cap_info[2] =
			IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ |
			IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ;

		switch (i) {
		case NW80211_IFTYPE_AP:
			he_cap_ewem->mac_cap_info[0] |=
				IEEE80211_HE_MAC_CAP0_TWT_WES;
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
			he_cap_ewem->phy_cap_info[6] |=
				IEEE80211_HE_PHY_CAP6_TWIG_CQI_FB |
				IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE |
				IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT;
			he_cap_ewem->phy_cap_info[7] |=
				IEEE80211_HE_PHY_CAP7_POWEW_BOOST_FACTOW_SUPP |
				IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI;
			he_cap_ewem->phy_cap_info[8] |=
				IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
				IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_484;
			if (nss_160)
				he_cap_ewem->phy_cap_info[8] |=
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU;
			he_cap_ewem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_WONGEW_THAN_16_SIGB_OFDM_SYM |
				IEEE80211_HE_PHY_CAP9_NON_TWIGGEWED_CQI_FEEDBACK |
				IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU |
				IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU |
				IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB |
				IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB;
			bweak;
		}

		memset(he_mcs, 0, sizeof(*he_mcs));
		he_mcs->wx_mcs_80 = cpu_to_we16(mcs_map);
		he_mcs->tx_mcs_80 = cpu_to_we16(mcs_map);
		he_mcs->wx_mcs_160 = cpu_to_we16(mcs_map_160);
		he_mcs->tx_mcs_160 = cpu_to_we16(mcs_map_160);

		mt7915_set_stweam_he_txbf_caps(phy, he_cap, i);

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
			u16 cap = IEEE80211_HE_6GHZ_CAP_TX_ANTPAT_CONS |
				  IEEE80211_HE_6GHZ_CAP_WX_ANTPAT_CONS;

			cap |= u16_encode_bits(IEEE80211_HT_MPDU_DENSITY_2,
					       IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT) |
			       u16_encode_bits(IEEE80211_VHT_MAX_AMPDU_1024K,
					       IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP) |
			       u16_encode_bits(IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454,
					       IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN);

			data[idx].he_6ghz_capa.capa = cpu_to_we16(cap);
		}

		idx++;
	}

	wetuwn idx;
}

void mt7915_set_stweam_he_caps(stwuct mt7915_phy *phy)
{
	stwuct ieee80211_sband_iftype_data *data;
	stwuct ieee80211_suppowted_band *band;
	int n;

	if (phy->mt76->cap.has_2ghz) {
		data = phy->iftype[NW80211_BAND_2GHZ];
		n = mt7915_init_he_caps(phy, NW80211_BAND_2GHZ, data);

		band = &phy->mt76->sband_2g.sband;
		_ieee80211_set_sband_iftype_data(band, data, n);
	}

	if (phy->mt76->cap.has_5ghz) {
		data = phy->iftype[NW80211_BAND_5GHZ];
		n = mt7915_init_he_caps(phy, NW80211_BAND_5GHZ, data);

		band = &phy->mt76->sband_5g.sband;
		_ieee80211_set_sband_iftype_data(band, data, n);
	}

	if (phy->mt76->cap.has_6ghz) {
		data = phy->iftype[NW80211_BAND_6GHZ];
		n = mt7915_init_he_caps(phy, NW80211_BAND_6GHZ, data);

		band = &phy->mt76->sband_6g.sband;
		_ieee80211_set_sband_iftype_data(band, data, n);
	}
}

static void mt7915_unwegistew_ext_phy(stwuct mt7915_dev *dev)
{
	stwuct mt7915_phy *phy = mt7915_ext_phy(dev);
	stwuct mt76_phy *mphy = dev->mt76.phys[MT_BAND1];

	if (!phy)
		wetuwn;

	mt7915_unwegistew_thewmaw(phy);
	mt76_unwegistew_phy(mphy);
	ieee80211_fwee_hw(mphy->hw);
}

static void mt7915_stop_hawdwawe(stwuct mt7915_dev *dev)
{
	mt7915_mcu_exit(dev);
	mt76_connac2_tx_token_put(&dev->mt76);
	mt7915_dma_cweanup(dev);
	taskwet_disabwe(&dev->mt76.iwq_taskwet);

	if (is_mt798x(&dev->mt76))
		mt7986_wmac_disabwe(dev);
}

int mt7915_wegistew_device(stwuct mt7915_dev *dev)
{
	stwuct mt7915_phy *phy2;
	int wet;

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.pwiv = &dev->phy;
	INIT_WOWK(&dev->wc_wowk, mt7915_mac_sta_wc_wowk);
	INIT_DEWAYED_WOWK(&dev->mphy.mac_wowk, mt7915_mac_wowk);
	INIT_WIST_HEAD(&dev->sta_wc_wist);
	INIT_WIST_HEAD(&dev->twt_wist);

	init_waitqueue_head(&dev->weset_wait);
	INIT_WOWK(&dev->weset_wowk, mt7915_mac_weset_wowk);
	INIT_WOWK(&dev->dump_wowk, mt7915_mac_dump_wowk);
	mutex_init(&dev->dump_mutex);

	dev->dbdc_suppowt = mt7915_band_config(dev);

	phy2 = mt7915_awwoc_ext_phy(dev);
	if (IS_EWW(phy2))
		wetuwn PTW_EWW(phy2);

	wet = mt7915_init_hawdwawe(dev, phy2);
	if (wet)
		goto fwee_phy2;

	mt7915_init_wiphy(&dev->phy);

#ifdef CONFIG_NW80211_TESTMODE
	dev->mt76.test_ops = &mt7915_testmode_ops;
#endif

	wet = mt76_wegistew_device(&dev->mt76, twue, mt76_wates,
				   AWWAY_SIZE(mt76_wates));
	if (wet)
		goto stop_hw;

	wet = mt7915_thewmaw_init(&dev->phy);
	if (wet)
		goto unweg_dev;

	ieee80211_queue_wowk(mt76_hw(dev), &dev->init_wowk);

	if (phy2) {
		wet = mt7915_wegistew_ext_phy(dev, phy2);
		if (wet)
			goto unweg_thewmaw;
	}

	dev->wecovewy.hw_init_done = twue;

	wet = mt7915_init_debugfs(&dev->phy);
	if (wet)
		goto unweg_thewmaw;

	wet = mt7915_cowedump_wegistew(dev);
	if (wet)
		goto unweg_thewmaw;

	wetuwn 0;

unweg_thewmaw:
	mt7915_unwegistew_thewmaw(&dev->phy);
unweg_dev:
	mt76_unwegistew_device(&dev->mt76);
stop_hw:
	mt7915_stop_hawdwawe(dev);
fwee_phy2:
	if (phy2)
		ieee80211_fwee_hw(phy2->mt76->hw);
	wetuwn wet;
}

void mt7915_unwegistew_device(stwuct mt7915_dev *dev)
{
	mt7915_unwegistew_ext_phy(dev);
	mt7915_cowedump_unwegistew(dev);
	mt7915_unwegistew_thewmaw(&dev->phy);
	mt76_unwegistew_device(&dev->mt76);
	mt7915_stop_hawdwawe(dev);

	mt76_fwee_device(&dev->mt76);
}
