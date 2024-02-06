// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/of.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/thewmaw.h>
#incwude "mt7996.h"
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
		.max = MT7996_MAX_INTEWFACES,
		.types = BIT(NW80211_IFTYPE_STATION)
	}
};

static const stwuct ieee80211_iface_combination if_comb[] = {
	{
		.wimits = if_wimits,
		.n_wimits = AWWAY_SIZE(if_wimits),
		.max_intewfaces = MT7996_MAX_INTEWFACES,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
		.wadaw_detect_widths = BIT(NW80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NW80211_CHAN_WIDTH_20) |
				       BIT(NW80211_CHAN_WIDTH_40) |
				       BIT(NW80211_CHAN_WIDTH_80) |
				       BIT(NW80211_CHAN_WIDTH_160),
	}
};

static ssize_t mt7996_thewmaw_temp_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct mt7996_phy *phy = dev_get_dwvdata(dev);
	int i = to_sensow_dev_attw(attw)->index;
	int tempewatuwe;

	switch (i) {
	case 0:
		tempewatuwe = mt7996_mcu_get_tempewatuwe(phy);
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

static ssize_t mt7996_thewmaw_temp_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct mt7996_phy *phy = dev_get_dwvdata(dev);
	int wet, i = to_sensow_dev_attw(attw)->index;
	wong vaw;

	wet = kstwtow(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&phy->dev->mt76.mutex);
	vaw = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, 1000), 40, 130);

	/* add a safety mawgin ~10 */
	if ((i - 1 == MT7996_CWIT_TEMP_IDX &&
	     vaw > phy->thwottwe_temp[MT7996_MAX_TEMP_IDX] - 10) ||
	    (i - 1 == MT7996_MAX_TEMP_IDX &&
	     vaw - 10 < phy->thwottwe_temp[MT7996_CWIT_TEMP_IDX])) {
		dev_eww(phy->dev->mt76.dev,
			"temp1_max shaww be 10 degwees highew than temp1_cwit.");
		mutex_unwock(&phy->dev->mt76.mutex);
		wetuwn -EINVAW;
	}

	phy->thwottwe_temp[i - 1] = vaw;
	mutex_unwock(&phy->dev->mt76.mutex);

	wet = mt7996_mcu_set_thewmaw_pwotect(phy, twue);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, mt7996_thewmaw_temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, mt7996_thewmaw_temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp1_max, mt7996_thewmaw_temp, 2);
static SENSOW_DEVICE_ATTW_WO(thwottwe1, mt7996_thewmaw_temp, 3);

static stwuct attwibute *mt7996_hwmon_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_thwottwe1.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mt7996_hwmon);

static int
mt7996_thewmaw_get_max_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	*state = MT7996_CDEV_THWOTTWE_MAX;

	wetuwn 0;
}

static int
mt7996_thewmaw_get_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	stwuct mt7996_phy *phy = cdev->devdata;

	*state = phy->cdev_state;

	wetuwn 0;
}

static int
mt7996_thewmaw_set_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong state)
{
	stwuct mt7996_phy *phy = cdev->devdata;
	u8 thwottwing = MT7996_THEWMAW_THWOTTWE_MAX - state;
	int wet;

	if (state > MT7996_CDEV_THWOTTWE_MAX) {
		dev_eww(phy->dev->mt76.dev,
			"pwease specify a vawid thwottwing state\n");
		wetuwn -EINVAW;
	}

	if (state == phy->cdev_state)
		wetuwn 0;

	/* coowing_device convention: 0 = no coowing, mowe = mowe coowing
	 * mcu convention: 1 = max coowing, mowe = wess coowing
	 */
	wet = mt7996_mcu_set_thewmaw_thwottwing(phy, thwottwing);
	if (wet)
		wetuwn wet;

	phy->cdev_state = state;

	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops mt7996_thewmaw_ops = {
	.get_max_state = mt7996_thewmaw_get_max_thwottwe_state,
	.get_cuw_state = mt7996_thewmaw_get_cuw_thwottwe_state,
	.set_cuw_state = mt7996_thewmaw_set_cuw_thwottwe_state,
};

static void mt7996_unwegistew_thewmaw(stwuct mt7996_phy *phy)
{
	stwuct wiphy *wiphy = phy->mt76->hw->wiphy;

	if (!phy->cdev)
		wetuwn;

	sysfs_wemove_wink(&wiphy->dev.kobj, "coowing_device");
	thewmaw_coowing_device_unwegistew(phy->cdev);
}

static int mt7996_thewmaw_init(stwuct mt7996_phy *phy)
{
	stwuct wiphy *wiphy = phy->mt76->hw->wiphy;
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *hwmon;
	const chaw *name;

	name = devm_kaspwintf(&wiphy->dev, GFP_KEWNEW, "mt7996_%s",
			      wiphy_name(wiphy));

	cdev = thewmaw_coowing_device_wegistew(name, phy, &mt7996_thewmaw_ops);
	if (!IS_EWW(cdev)) {
		if (sysfs_cweate_wink(&wiphy->dev.kobj, &cdev->device.kobj,
				      "coowing_device") < 0)
			thewmaw_coowing_device_unwegistew(cdev);
		ewse
			phy->cdev = cdev;
	}

	/* initiawize cwiticaw/maximum high tempewatuwe */
	phy->thwottwe_temp[MT7996_CWIT_TEMP_IDX] = MT7996_CWIT_TEMP;
	phy->thwottwe_temp[MT7996_MAX_TEMP_IDX] = MT7996_MAX_TEMP;

	if (!IS_WEACHABWE(CONFIG_HWMON))
		wetuwn 0;

	hwmon = devm_hwmon_device_wegistew_with_gwoups(&wiphy->dev, name, phy,
						       mt7996_hwmon_gwoups);

	if (IS_EWW(hwmon))
		wetuwn PTW_EWW(hwmon);

	wetuwn 0;
}

static void mt7996_wed_set_config(stwuct wed_cwassdev *wed_cdev,
				  u8 deway_on, u8 deway_off)
{
	stwuct mt7996_dev *dev;
	stwuct mt76_phy *mphy;
	u32 vaw;

	mphy = containew_of(wed_cdev, stwuct mt76_phy, weds.cdev);
	dev = containew_of(mphy->dev, stwuct mt7996_dev, mt76);

	/* sewect TX bwink mode, 2: onwy data fwames */
	mt76_wmw_fiewd(dev, MT_TMAC_TCW0(mphy->band_idx), MT_TMAC_TCW0_TX_BWINK, 2);

	/* enabwe WED */
	mt76_ww(dev, MT_WED_EN(mphy->band_idx), 1);

	/* set WED Tx bwink on/off time */
	vaw = FIEWD_PWEP(MT_WED_TX_BWINK_ON_MASK, deway_on) |
	      FIEWD_PWEP(MT_WED_TX_BWINK_OFF_MASK, deway_off);
	mt76_ww(dev, MT_WED_TX_BWINK(mphy->band_idx), vaw);

	/* tuwn WED off */
	if (deway_off == 0xff && deway_on == 0x0) {
		vaw = MT_WED_CTWW_POWAWITY | MT_WED_CTWW_KICK;
	} ewse {
		/* contwow WED */
		vaw = MT_WED_CTWW_BWINK_MODE | MT_WED_CTWW_KICK;
		if (mphy->band_idx == MT_BAND1)
			vaw |= MT_WED_CTWW_BWINK_BAND_SEW;
	}

	if (mphy->weds.aw)
		vaw |= MT_WED_CTWW_POWAWITY;

	mt76_ww(dev, MT_WED_CTWW(mphy->band_idx), vaw);
	mt76_cweaw(dev, MT_WED_CTWW(mphy->band_idx), MT_WED_CTWW_KICK);
}

static int mt7996_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
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

	mt7996_wed_set_config(wed_cdev, dewta_on, dewta_off);

	wetuwn 0;
}

static void mt7996_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
				      enum wed_bwightness bwightness)
{
	if (!bwightness)
		mt7996_wed_set_config(wed_cdev, 0, 0xff);
	ewse
		mt7996_wed_set_config(wed_cdev, 0xff, 0);
}

static void __mt7996_init_txpowew(stwuct mt7996_phy *phy,
				  stwuct ieee80211_suppowted_band *sband)
{
	stwuct mt7996_dev *dev = phy->dev;
	int i, nss = hweight16(phy->mt76->chainmask);
	int nss_dewta = mt76_tx_powew_nss_dewta(nss);
	int pww_dewta = mt7996_eepwom_get_powew_dewta(dev, sband->band);
	stwuct mt76_powew_wimits wimits;

	fow (i = 0; i < sband->n_channews; i++) {
		stwuct ieee80211_channew *chan = &sband->channews[i];
		int tawget_powew = mt7996_eepwom_get_tawget_powew(dev, chan);

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

void mt7996_init_txpowew(stwuct mt7996_phy *phy)
{
	if (!phy)
		wetuwn;

	if (phy->mt76->cap.has_2ghz)
		__mt7996_init_txpowew(phy, &phy->mt76->sband_2g.sband);
	if (phy->mt76->cap.has_5ghz)
		__mt7996_init_txpowew(phy, &phy->mt76->sband_5g.sband);
	if (phy->mt76->cap.has_6ghz)
		__mt7996_init_txpowew(phy, &phy->mt76->sband_6g.sband);
}

static void
mt7996_wegd_notifiew(stwuct wiphy *wiphy,
		     stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct mt7996_dev *dev = mt7996_hw_dev(hw);
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);

	memcpy(dev->mt76.awpha2, wequest->awpha2, sizeof(dev->mt76.awpha2));
	dev->mt76.wegion = wequest->dfs_wegion;

	if (dev->mt76.wegion == NW80211_DFS_UNSET)
		mt7996_mcu_wdd_backgwound_enabwe(phy, NUWW);

	mt7996_init_txpowew(phy);

	phy->mt76->dfs_state = MT_DFS_STATE_UNKNOWN;
	mt7996_dfs_init_wadaw_detectow(phy);
}

static void
mt7996_init_wiphy(stwuct ieee80211_hw *hw, stwuct mtk_wed_device *wed)
{
	stwuct mt7996_phy *phy = mt7996_hw_phy(hw);
	stwuct mt76_dev *mdev = &phy->dev->mt76;
	stwuct wiphy *wiphy = hw->wiphy;
	u16 max_subfwames = phy->dev->has_eht ? IEEE80211_MAX_AMPDU_BUF_EHT :
						IEEE80211_MAX_AMPDU_BUF_HE;

	hw->queues = 4;
	hw->max_wx_aggwegation_subfwames = max_subfwames;
	hw->max_tx_aggwegation_subfwames = max_subfwames;
	hw->netdev_featuwes = NETIF_F_WXCSUM;
	if (mtk_wed_device_active(wed))
		hw->netdev_featuwes |= NETIF_F_HW_TC;

	hw->wadiotap_timestamp.units_pos =
		IEEE80211_WADIOTAP_TIMESTAMP_UNIT_US;

	phy->swottime = 9;
	phy->beacon_wate = -1;

	hw->sta_data_size = sizeof(stwuct mt7996_sta);
	hw->vif_data_size = sizeof(stwuct mt7996_vif);

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = AWWAY_SIZE(if_comb);
	wiphy->weg_notifiew = mt7996_wegd_notifiew;
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
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_MU_MIMO_AIW_SNIFFEW);

	if (!mdev->dev->of_node ||
	    !of_pwopewty_wead_boow(mdev->dev->of_node,
				   "mediatek,disabwe-wadaw-backgwound"))
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_WADAW_BACKGWOUND);

	ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(hw, SUPPOWTS_TX_ENCAP_OFFWOAD);
	ieee80211_hw_set(hw, SUPPOWTS_WX_DECAP_OFFWOAD);
	ieee80211_hw_set(hw, WANT_MONITOW_VIF);
	ieee80211_hw_set(hw, SUPPOWTS_MUWTI_BSSID);

	hw->max_tx_fwagments = 4;

	if (phy->mt76->cap.has_2ghz) {
		phy->mt76->sband_2g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_WDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;
		phy->mt76->sband_2g.sband.ht_cap.ampdu_density =
			IEEE80211_HT_MPDU_DENSITY_2;
	}

	if (phy->mt76->cap.has_5ghz) {
		phy->mt76->sband_5g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_WDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;

		phy->mt76->sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454 |
			IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK |
			IEEE80211_VHT_CAP_SHOWT_GI_160 |
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
		phy->mt76->sband_5g.sband.ht_cap.ampdu_density =
			IEEE80211_HT_MPDU_DENSITY_1;

		ieee80211_hw_set(hw, SUPPOWTS_VHT_EXT_NSS_BW);
	}

	/* init wed cawwbacks */
	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		phy->mt76->weds.cdev.bwightness_set = mt7996_wed_set_bwightness;
		phy->mt76->weds.cdev.bwink_set = mt7996_wed_set_bwink;
	}

	mt76_set_stweam_caps(phy->mt76, twue);
	mt7996_set_stweam_vht_txbf_caps(phy);
	mt7996_set_stweam_he_eht_caps(phy);
	mt7996_init_txpowew(phy);

	wiphy->avaiwabwe_antennas_wx = phy->mt76->antenna_mask;
	wiphy->avaiwabwe_antennas_tx = phy->mt76->antenna_mask;
}

static void
mt7996_mac_init_band(stwuct mt7996_dev *dev, u8 band)
{
	u32 mask, set;

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
	mask = MT_WTBWOFF_WSCW_WCPI_MODE | MT_WTBWOFF_WSCW_WCPI_PAWAM;
	set = FIEWD_PWEP(MT_WTBWOFF_WSCW_WCPI_MODE, 0) |
	      FIEWD_PWEP(MT_WTBWOFF_WSCW_WCPI_PAWAM, 0x3);
	mt76_wmw(dev, MT_WTBWOFF_WSCW(band), mask, set);

	/* MT_TXD5_TX_STATUS_HOST (MPDU fowmat) has highew pwiowity than
	 * MT_AGG_ACW_PPDU_TXS2H (PPDU fowmat) even though ACW bit is set.
	 */
	mt76_set(dev, MT_AGG_ACW4(band), MT_AGG_ACW_PPDU_TXS2H);
}

static void mt7996_mac_init_basic_wates(stwuct mt7996_dev *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mt76_wates); i++) {
		u16 wate = mt76_wates[i].hw_vawue;
		/* odd index fow dwivew, even index fow fiwmwawe */
		u16 idx = MT7996_BASIC_WATES_TBW + 2 * i;

		wate = FIEWD_PWEP(MT_TX_WATE_MODE, wate >> 8) |
		       FIEWD_PWEP(MT_TX_WATE_IDX, wate & GENMASK(7, 0));
		mt7996_mcu_set_fixed_wate_tabwe(&dev->phy, idx, wate, fawse);
	}
}

void mt7996_mac_init(stwuct mt7996_dev *dev)
{
#define HIF_TXD_V2_1	4
	int i;

	mt76_cweaw(dev, MT_MDP_DCW2, MT_MDP_DCW2_WX_TWANS_SHOWT);

	fow (i = 0; i < mt7996_wtbw_size(dev); i++)
		mt7996_mac_wtbw_update(dev, i,
				       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);

	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		i = dev->mphy.weds.pin ? MT_WED_GPIO_MUX3 : MT_WED_GPIO_MUX2;
		mt76_wmw_fiewd(dev, i, MT_WED_GPIO_SEW_MASK, 4);
	}

	/* txs wepowt queue */
	mt76_wmw_fiewd(dev, MT_DMA_TCWF1(0), MT_DMA_TCWF1_QIDX, 0);
	mt76_wmw_fiewd(dev, MT_DMA_TCWF1(1), MT_DMA_TCWF1_QIDX, 6);
	mt76_wmw_fiewd(dev, MT_DMA_TCWF1(2), MT_DMA_TCWF1_QIDX, 0);

	/* wwo moduwe init */
	if (is_mt7996(&dev->mt76))
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_PWATFOWM_TYPE, 2);
	ewse
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_PWATFOWM_TYPE,
				   dev->hif2 ? 7 : 0);

	if (dev->has_wwo) {
		u16 timeout;

		timeout = mt76_ww(dev, MT_HW_WEV) == MT_HW_WEV1 ? 512 : 128;
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_FWUSH_TIMEOUT, timeout);
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_BYPASS_MODE, 1);
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_TXFWEE_PATH, 0);
	} ewse {
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_BYPASS_MODE, 3);
		mt7996_mcu_set_wwo(dev, UNI_WWO_SET_TXFWEE_PATH, 1);
	}

	mt7996_mcu_wa_cmd(dev, MCU_WA_PAWAM_CMD(SET),
			  MCU_WA_PAWAM_HW_PATH_HIF_VEW,
			  HIF_TXD_V2_1, 0);

	fow (i = MT_BAND0; i <= MT_BAND2; i++)
		mt7996_mac_init_band(dev, i);

	mt7996_mac_init_basic_wates(dev);
}

int mt7996_txbf_init(stwuct mt7996_dev *dev)
{
	int wet;

	if (mt7996_band_vawid(dev, MT_BAND1) ||
	    mt7996_band_vawid(dev, MT_BAND2)) {
		wet = mt7996_mcu_set_txbf(dev, BF_MOD_EN_CTWW);
		if (wet)
			wetuwn wet;
	}

	/* twiggew sounding packets */
	wet = mt7996_mcu_set_txbf(dev, BF_SOUNDING_ON);
	if (wet)
		wetuwn wet;

	/* enabwe eBF */
	wetuwn mt7996_mcu_set_txbf(dev, BF_HW_EN_UPDATE);
}

static int mt7996_wegistew_phy(stwuct mt7996_dev *dev, stwuct mt7996_phy *phy,
			       enum mt76_band_id band)
{
	stwuct mt76_phy *mphy;
	u32 mac_ofs, hif1_ofs = 0;
	int wet;
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;

	if (!mt7996_band_vawid(dev, band) || band == MT_BAND0)
		wetuwn 0;

	if (phy)
		wetuwn 0;

	if (is_mt7996(&dev->mt76) && band == MT_BAND2 && dev->hif2) {
		hif1_ofs = MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0);
		wed = &dev->mt76.mmio.wed_hif2;
	}

	mphy = mt76_awwoc_phy(&dev->mt76, sizeof(*phy), &mt7996_ops, band);
	if (!mphy)
		wetuwn -ENOMEM;

	phy = mphy->pwiv;
	phy->dev = dev;
	phy->mt76 = mphy;
	mphy->dev->phys[band] = mphy;

	INIT_DEWAYED_WOWK(&mphy->mac_wowk, mt7996_mac_wowk);

	wet = mt7996_eepwom_pawse_hw_cap(dev, phy);
	if (wet)
		goto ewwow;

	mac_ofs = band == MT_BAND2 ? MT_EE_MAC_ADDW3 : MT_EE_MAC_ADDW2;
	memcpy(mphy->macaddw, dev->mt76.eepwom.data + mac_ofs, ETH_AWEN);
	/* Make the extwa PHY MAC addwess wocaw without ovewwapping with
	 * the usuaw MAC addwess awwocation scheme on muwtipwe viwtuaw intewfaces
	 */
	if (!is_vawid_ethew_addw(mphy->macaddw)) {
		memcpy(mphy->macaddw, dev->mt76.eepwom.data + MT_EE_MAC_ADDW,
		       ETH_AWEN);
		mphy->macaddw[0] |= 2;
		mphy->macaddw[0] ^= BIT(7);
		if (band == MT_BAND2)
			mphy->macaddw[0] ^= BIT(6);
	}
	mt76_eepwom_ovewwide(mphy);

	/* init wiphy accowding to mphy and phy */
	mt7996_init_wiphy(mphy->hw, wed);
	wet = mt7996_init_tx_queues(mphy->pwiv,
				    MT_TXQ_ID(band),
				    MT7996_TX_WING_SIZE,
				    MT_TXQ_WING_BASE(band) + hif1_ofs,
				    wed);
	if (wet)
		goto ewwow;

	wet = mt76_wegistew_phy(mphy, twue, mt76_wates,
				AWWAY_SIZE(mt76_wates));
	if (wet)
		goto ewwow;

	wet = mt7996_thewmaw_init(phy);
	if (wet)
		goto ewwow;

	wet = mt7996_init_debugfs(phy);
	if (wet)
		goto ewwow;

	if (wed == &dev->mt76.mmio.wed_hif2 && mtk_wed_device_active(wed)) {
		u32 iwq_mask = dev->mt76.mmio.iwqmask | MT_INT_TX_DONE_BAND2;

		mt76_ww(dev, MT_INT1_MASK_CSW, iwq_mask);
		mtk_wed_device_stawt(&dev->mt76.mmio.wed_hif2, iwq_mask);
	}

	wetuwn 0;

ewwow:
	mphy->dev->phys[band] = NUWW;
	ieee80211_fwee_hw(mphy->hw);
	wetuwn wet;
}

static void
mt7996_unwegistew_phy(stwuct mt7996_phy *phy, enum mt76_band_id band)
{
	stwuct mt76_phy *mphy;

	if (!phy)
		wetuwn;

	mt7996_unwegistew_thewmaw(phy);

	mphy = phy->dev->mt76.phys[band];
	mt76_unwegistew_phy(mphy);
	ieee80211_fwee_hw(mphy->hw);
	phy->dev->mt76.phys[band] = NUWW;
}

static void mt7996_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7996_dev *dev = containew_of(wowk, stwuct mt7996_dev,
				 init_wowk);

	mt7996_mcu_set_eepwom(dev);
	mt7996_mac_init(dev);
	mt7996_txbf_init(dev);
}

void mt7996_wfsys_weset(stwuct mt7996_dev *dev)
{
	mt76_set(dev, MT_WF_SUBSYS_WST, 0x1);
	msweep(20);

	mt76_cweaw(dev, MT_WF_SUBSYS_WST, 0x1);
	msweep(20);
}

static int mt7996_wed_wwo_init(stwuct mt7996_dev *dev)
{
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;
	u32 weg = MT_WWO_ADDW_EWEM_SEG_ADDW0;
	stwuct mt7996_wed_wwo_addw *addw;
	void *ptw;
	int i;

	if (!dev->has_wwo)
		wetuwn 0;

	if (!mtk_wed_device_active(wed))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(dev->wed_wwo.ba_bitmap); i++) {
		ptw = dmam_awwoc_cohewent(dev->mt76.dma_dev,
					  MT7996_WWO_BA_BITMAP_CW_SIZE,
					  &dev->wed_wwo.ba_bitmap[i].phy_addw,
					  GFP_KEWNEW);
		if (!ptw)
			wetuwn -ENOMEM;

		dev->wed_wwo.ba_bitmap[i].ptw = ptw;
	}

	fow (i = 0; i < AWWAY_SIZE(dev->wed_wwo.addw_ewem); i++) {
		int j;

		ptw = dmam_awwoc_cohewent(dev->mt76.dma_dev,
				MT7996_WWO_WINDOW_MAX_SIZE * sizeof(*addw),
				&dev->wed_wwo.addw_ewem[i].phy_addw,
				GFP_KEWNEW);
		if (!ptw)
			wetuwn -ENOMEM;

		dev->wed_wwo.addw_ewem[i].ptw = ptw;
		memset(dev->wed_wwo.addw_ewem[i].ptw, 0,
		       MT7996_WWO_WINDOW_MAX_SIZE * sizeof(*addw));

		addw = dev->wed_wwo.addw_ewem[i].ptw;
		fow (j = 0; j < MT7996_WWO_WINDOW_MAX_SIZE; j++) {
			addw->signatuwe = 0xff;
			addw++;
		}

		wed->wwan.ind_cmd.addw_ewem_phys[i] =
			dev->wed_wwo.addw_ewem[i].phy_addw;
	}

	ptw = dmam_awwoc_cohewent(dev->mt76.dma_dev,
				  MT7996_WWO_WINDOW_MAX_WEN * sizeof(*addw),
				  &dev->wed_wwo.session.phy_addw,
				  GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	dev->wed_wwo.session.ptw = ptw;
	addw = dev->wed_wwo.session.ptw;
	fow (i = 0; i < MT7996_WWO_WINDOW_MAX_WEN; i++) {
		addw->signatuwe = 0xff;
		addw++;
	}

	/* wwo hw init */
	/* TODO: wemove wine aftew WM has set */
	mt76_cweaw(dev, WF_WWO_AXI_MST_CFG, WF_WWO_AXI_MST_CFG_DIDX_OK);

	/* setup BA bitmap cache addwess */
	mt76_ww(dev, MT_WWO_BA_BITMAP_BASE0,
		dev->wed_wwo.ba_bitmap[0].phy_addw);
	mt76_ww(dev, MT_WWO_BA_BITMAP_BASE1, 0);
	mt76_ww(dev, MT_WWO_BA_BITMAP_BASE_EXT0,
		dev->wed_wwo.ba_bitmap[1].phy_addw);
	mt76_ww(dev, MT_WWO_BA_BITMAP_BASE_EXT1, 0);

	/* setup Addwess ewement addwess */
	fow (i = 0; i < AWWAY_SIZE(dev->wed_wwo.addw_ewem); i++) {
		mt76_ww(dev, weg, dev->wed_wwo.addw_ewem[i].phy_addw >> 4);
		weg += 4;
	}

	/* setup Addwess ewement addwess - sepawate addwess segment mode */
	mt76_ww(dev, MT_WWO_ADDW_AWWAY_BASE1,
		MT_WWO_ADDW_AWWAY_EWEM_ADDW_SEG_MODE);

	wed->wwan.ind_cmd.win_size = ffs(MT7996_WWO_WINDOW_MAX_WEN) - 6;
	wed->wwan.ind_cmd.pawticuwaw_sid = MT7996_WWO_MAX_SESSION;
	wed->wwan.ind_cmd.pawticuwaw_se_phys = dev->wed_wwo.session.phy_addw;
	wed->wwan.ind_cmd.se_gwoup_nums = MT7996_WWO_ADDW_EWEM_WEN;
	wed->wwan.ind_cmd.ack_sn_addw = MT_WWO_ACK_SN_CTWW;

	mt76_ww(dev, MT_WWO_IND_CMD_SIGNATUWE_BASE0, 0x15010e00);
	mt76_set(dev, MT_WWO_IND_CMD_SIGNATUWE_BASE1,
		 MT_WWO_IND_CMD_SIGNATUWE_BASE1_EN);

	/* pawticuwaw session configuwe */
	/* use max session idx + 1 as pawticuwaw session id */
	mt76_ww(dev, MT_WWO_PAWTICUWAW_CFG0, dev->wed_wwo.session.phy_addw);
	mt76_ww(dev, MT_WWO_PAWTICUWAW_CFG1,
		MT_WWO_PAWTICUWAW_CONFG_EN |
		FIEWD_PWEP(MT_WWO_PAWTICUWAW_SID, MT7996_WWO_MAX_SESSION));

	/* intewwupt enabwe */
	mt76_ww(dev, MT_WWO_HOST_INT_ENA,
		MT_WWO_HOST_INT_ENA_HOST_WWO_DONE_ENA);

	/* wwo ind cmd queue init */
	wetuwn mt7996_dma_wwo_init(dev);
#ewse
	wetuwn 0;
#endif
}

static void mt7996_wed_wwo_fwee(stwuct mt7996_dev *dev)
{
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	int i;

	if (!dev->has_wwo)
		wetuwn;

	if (!mtk_wed_device_active(&dev->mt76.mmio.wed))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(dev->wed_wwo.ba_bitmap); i++) {
		if (!dev->wed_wwo.ba_bitmap[i].ptw)
			continue;

		dmam_fwee_cohewent(dev->mt76.dma_dev,
				   MT7996_WWO_BA_BITMAP_CW_SIZE,
				   dev->wed_wwo.ba_bitmap[i].ptw,
				   dev->wed_wwo.ba_bitmap[i].phy_addw);
	}

	fow (i = 0; i < AWWAY_SIZE(dev->wed_wwo.addw_ewem); i++) {
		if (!dev->wed_wwo.addw_ewem[i].ptw)
			continue;

		dmam_fwee_cohewent(dev->mt76.dma_dev,
				   MT7996_WWO_WINDOW_MAX_SIZE *
				   sizeof(stwuct mt7996_wed_wwo_addw),
				   dev->wed_wwo.addw_ewem[i].ptw,
				   dev->wed_wwo.addw_ewem[i].phy_addw);
	}

	if (!dev->wed_wwo.session.ptw)
		wetuwn;

	dmam_fwee_cohewent(dev->mt76.dma_dev,
			   MT7996_WWO_WINDOW_MAX_WEN *
			   sizeof(stwuct mt7996_wed_wwo_addw),
			   dev->wed_wwo.session.ptw,
			   dev->wed_wwo.session.phy_addw);
#endif
}

static void mt7996_wed_wwo_wowk(stwuct wowk_stwuct *wowk)
{
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	stwuct mt7996_dev *dev;
	WIST_HEAD(wist);

	dev = (stwuct mt7996_dev *)containew_of(wowk, stwuct mt7996_dev,
						wed_wwo.wowk);

	spin_wock_bh(&dev->wed_wwo.wock);
	wist_spwice_init(&dev->wed_wwo.poww_wist, &wist);
	spin_unwock_bh(&dev->wed_wwo.wock);

	whiwe (!wist_empty(&wist)) {
		stwuct mt7996_wed_wwo_session_id *e;
		int i;

		e = wist_fiwst_entwy(&wist, stwuct mt7996_wed_wwo_session_id,
				     wist);
		wist_dew_init(&e->wist);

		fow (i = 0; i < MT7996_WWO_WINDOW_MAX_WEN; i++) {
			void *ptw = dev->wed_wwo.session.ptw;
			stwuct mt7996_wed_wwo_addw *ewem;
			u32 idx, ewem_id = i;

			if (e->id == MT7996_WWO_MAX_SESSION)
				goto weset;

			idx = e->id / MT7996_WWO_BA_BITMAP_SESSION_SIZE;
			if (idx >= AWWAY_SIZE(dev->wed_wwo.addw_ewem))
				goto out;

			ptw = dev->wed_wwo.addw_ewem[idx].ptw;
			ewem_id +=
				(e->id % MT7996_WWO_BA_BITMAP_SESSION_SIZE) *
				MT7996_WWO_WINDOW_MAX_WEN;
weset:
			ewem = ptw + ewem_id * sizeof(*ewem);
			ewem->signatuwe = 0xff;
		}
		mt7996_mcu_wed_wwo_weset_sessions(dev, e->id);
out:
		kfwee(e);
	}
#endif
}

static int mt7996_init_hawdwawe(stwuct mt7996_dev *dev)
{
	int wet, idx;

	mt76_ww(dev, MT_INT_SOUWCE_CSW, ~0);
	if (is_mt7992(&dev->mt76)) {
		mt76_wmw(dev, MT_AFE_CTW_BAND_PWW_03(MT_BAND0), MT_AFE_CTW_BAND_PWW_03_MSB_EN, 0);
		mt76_wmw(dev, MT_AFE_CTW_BAND_PWW_03(MT_BAND1), MT_AFE_CTW_BAND_PWW_03_MSB_EN, 0);
	}

	INIT_WOWK(&dev->init_wowk, mt7996_init_wowk);
	INIT_WOWK(&dev->wed_wwo.wowk, mt7996_wed_wwo_wowk);
	INIT_WIST_HEAD(&dev->wed_wwo.poww_wist);
	spin_wock_init(&dev->wed_wwo.wock);

	wet = mt7996_dma_init(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	wet = mt7996_mcu_init(dev);
	if (wet)
		wetuwn wet;

	wet = mt7996_wed_wwo_init(dev);
	if (wet)
		wetuwn wet;

	wet = mt7996_eepwom_init(dev);
	if (wet < 0)
		wetuwn wet;

	/* Beacon and mgmt fwames shouwd occupy wcid 0 */
	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7996_WTBW_STA);
	if (idx)
		wetuwn -ENOSPC;

	dev->mt76.gwobaw_wcid.idx = idx;
	dev->mt76.gwobaw_wcid.hw_key_idx = -1;
	dev->mt76.gwobaw_wcid.tx_info |= MT_WCID_TX_INFO_SET;
	wcu_assign_pointew(dev->mt76.wcid[idx], &dev->mt76.gwobaw_wcid);

	wetuwn 0;
}

void mt7996_set_stweam_vht_txbf_caps(stwuct mt7996_phy *phy)
{
	int sts;
	u32 *cap;

	if (!phy->mt76->cap.has_5ghz)
		wetuwn;

	sts = hweight16(phy->mt76->chainmask);
	cap = &phy->mt76->sband_5g.sband.vht_cap.cap;

	*cap |= IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE |
		IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE |
		FIEWD_PWEP(IEEE80211_VHT_CAP_BEAMFOWMEE_STS_MASK, sts - 1);

	*cap &= ~(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK |
		  IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE |
		  IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE);

	if (sts < 2)
		wetuwn;

	*cap |= IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE |
		IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE |
		FIEWD_PWEP(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK, sts - 1);
}

static void
mt7996_set_stweam_he_txbf_caps(stwuct mt7996_phy *phy,
			       stwuct ieee80211_sta_he_cap *he_cap, int vif)
{
	stwuct ieee80211_he_cap_ewem *ewem = &he_cap->he_cap_ewem;
	int sts = hweight16(phy->mt76->chainmask);
	u8 c;

#ifdef CONFIG_MAC80211_MESH
	if (vif == NW80211_IFTYPE_MESH_POINT)
		wetuwn;
#endif

	ewem->phy_cap_info[3] &= ~IEEE80211_HE_PHY_CAP3_SU_BEAMFOWMEW;
	ewem->phy_cap_info[4] &= ~IEEE80211_HE_PHY_CAP4_MU_BEAMFOWMEW;

	c = IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK |
	    IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK;
	ewem->phy_cap_info[5] &= ~c;

	c = IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB |
	    IEEE80211_HE_PHY_CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB;
	ewem->phy_cap_info[6] &= ~c;

	ewem->phy_cap_info[7] &= ~IEEE80211_HE_PHY_CAP7_MAX_NC_MASK;

	c = IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US |
	    IEEE80211_HE_PHY_CAP2_UW_MU_FUWW_MU_MIMO |
	    IEEE80211_HE_PHY_CAP2_UW_MU_PAWTIAW_MU_MIMO;
	ewem->phy_cap_info[2] |= c;

	c = IEEE80211_HE_PHY_CAP4_SU_BEAMFOWMEE |
	    IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_4 |
	    IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_4;
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
		       sts - 1) |
	    FIEWD_PWEP(IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK,
		       sts - 1);
	ewem->phy_cap_info[5] |= c;

	c = IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB |
	    IEEE80211_HE_PHY_CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB;
	ewem->phy_cap_info[6] |= c;

	c = IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ |
	    IEEE80211_HE_PHY_CAP7_STBC_WX_ABOVE_80MHZ;
	ewem->phy_cap_info[7] |= c;
}

static void
mt7996_init_he_caps(stwuct mt7996_phy *phy, enum nw80211_band band,
		    stwuct ieee80211_sband_iftype_data *data,
		    enum nw80211_iftype iftype)
{
	stwuct ieee80211_sta_he_cap *he_cap = &data->he_cap;
	stwuct ieee80211_he_cap_ewem *he_cap_ewem = &he_cap->he_cap_ewem;
	stwuct ieee80211_he_mcs_nss_supp *he_mcs = &he_cap->he_mcs_nss_supp;
	int i, nss = hweight8(phy->mt76->antenna_mask);
	u16 mcs_map = 0;

	fow (i = 0; i < 8; i++) {
		if (i < nss)
			mcs_map |= (IEEE80211_HE_MCS_SUPPOWT_0_11 << (i * 2));
		ewse
			mcs_map |= (IEEE80211_HE_MCS_NOT_SUPPOWTED << (i * 2));
	}

	he_cap->has_he = twue;

	he_cap_ewem->mac_cap_info[0] = IEEE80211_HE_MAC_CAP0_HTC_HE;
	he_cap_ewem->mac_cap_info[3] = IEEE80211_HE_MAC_CAP3_OMI_CONTWOW |
				       IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_3;
	he_cap_ewem->mac_cap_info[4] = IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU;

	if (band == NW80211_BAND_2GHZ)
		he_cap_ewem->phy_cap_info[0] =
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G;
	ewse
		he_cap_ewem->phy_cap_info[0] =
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G |
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;

	he_cap_ewem->phy_cap_info[1] = IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD;
	he_cap_ewem->phy_cap_info[2] = IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ |
				       IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ;

	switch (iftype) {
	case NW80211_IFTYPE_AP:
		he_cap_ewem->mac_cap_info[0] |= IEEE80211_HE_MAC_CAP0_TWT_WES;
		he_cap_ewem->mac_cap_info[2] |= IEEE80211_HE_MAC_CAP2_BSW;
		he_cap_ewem->mac_cap_info[4] |= IEEE80211_HE_MAC_CAP4_BQW;
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
			IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
			IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU |
			IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_484;
		he_cap_ewem->phy_cap_info[9] |=
			IEEE80211_HE_PHY_CAP9_WONGEW_THAN_16_SIGB_OFDM_SYM |
			IEEE80211_HE_PHY_CAP9_NON_TWIGGEWED_CQI_FEEDBACK |
			IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU |
			IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU |
			IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB |
			IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB;
		bweak;
	defauwt:
		bweak;
	}

	he_mcs->wx_mcs_80 = cpu_to_we16(mcs_map);
	he_mcs->tx_mcs_80 = cpu_to_we16(mcs_map);
	he_mcs->wx_mcs_160 = cpu_to_we16(mcs_map);
	he_mcs->tx_mcs_160 = cpu_to_we16(mcs_map);

	mt7996_set_stweam_he_txbf_caps(phy, he_cap, iftype);

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

		cap |= u16_encode_bits(IEEE80211_HT_MPDU_DENSITY_0_5,
				       IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT) |
		       u16_encode_bits(IEEE80211_VHT_MAX_AMPDU_1024K,
				       IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP) |
		       u16_encode_bits(IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454,
				       IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN);

		data->he_6ghz_capa.capa = cpu_to_we16(cap);
	}
}

static void
mt7996_init_eht_caps(stwuct mt7996_phy *phy, enum nw80211_band band,
		     stwuct ieee80211_sband_iftype_data *data,
		     enum nw80211_iftype iftype)
{
	stwuct ieee80211_sta_eht_cap *eht_cap = &data->eht_cap;
	stwuct ieee80211_eht_cap_ewem_fixed *eht_cap_ewem = &eht_cap->eht_cap_ewem;
	stwuct ieee80211_eht_mcs_nss_supp *eht_nss = &eht_cap->eht_mcs_nss_supp;
	enum nw80211_chan_width width = phy->mt76->chandef.width;
	int nss = hweight8(phy->mt76->antenna_mask);
	int sts = hweight16(phy->mt76->chainmask);
	u8 vaw;

	if (!phy->dev->has_eht)
		wetuwn;

	eht_cap->has_eht = twue;

	eht_cap_ewem->mac_cap_info[0] =
		IEEE80211_EHT_MAC_CAP0_EPCS_PWIO_ACCESS |
		IEEE80211_EHT_MAC_CAP0_OM_CONTWOW;

	eht_cap_ewem->phy_cap_info[0] =
		IEEE80211_EHT_PHY_CAP0_320MHZ_IN_6GHZ |
		IEEE80211_EHT_PHY_CAP0_NDP_4_EHT_WFT_32_GI |
		IEEE80211_EHT_PHY_CAP0_SU_BEAMFOWMEW |
		IEEE80211_EHT_PHY_CAP0_SU_BEAMFOWMEE;

	vaw = max_t(u8, sts - 1, 3);
	eht_cap_ewem->phy_cap_info[0] |=
		u8_encode_bits(u8_get_bits(vaw, BIT(0)),
			       IEEE80211_EHT_PHY_CAP0_BEAMFOWMEE_SS_80MHZ_MASK);

	eht_cap_ewem->phy_cap_info[1] =
		u8_encode_bits(u8_get_bits(vaw, GENMASK(2, 1)),
			       IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_80MHZ_MASK) |
		u8_encode_bits(vaw,
			       IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_160MHZ_MASK) |
		u8_encode_bits(vaw,
			       IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_320MHZ_MASK);

	eht_cap_ewem->phy_cap_info[2] =
		u8_encode_bits(sts - 1, IEEE80211_EHT_PHY_CAP2_SOUNDING_DIM_80MHZ_MASK) |
		u8_encode_bits(sts - 1, IEEE80211_EHT_PHY_CAP2_SOUNDING_DIM_160MHZ_MASK) |
		u8_encode_bits(sts - 1, IEEE80211_EHT_PHY_CAP2_SOUNDING_DIM_320MHZ_MASK);

	eht_cap_ewem->phy_cap_info[3] =
		IEEE80211_EHT_PHY_CAP3_NG_16_SU_FEEDBACK |
		IEEE80211_EHT_PHY_CAP3_NG_16_MU_FEEDBACK |
		IEEE80211_EHT_PHY_CAP3_CODEBOOK_4_2_SU_FDBK |
		IEEE80211_EHT_PHY_CAP3_CODEBOOK_7_5_MU_FDBK |
		IEEE80211_EHT_PHY_CAP3_TWIG_SU_BF_FDBK |
		IEEE80211_EHT_PHY_CAP3_TWIG_MU_BF_PAWT_BW_FDBK |
		IEEE80211_EHT_PHY_CAP3_TWIG_CQI_FDBK;

	eht_cap_ewem->phy_cap_info[4] =
		u8_encode_bits(min_t(int, sts - 1, 2),
			       IEEE80211_EHT_PHY_CAP4_MAX_NC_MASK);

	eht_cap_ewem->phy_cap_info[5] =
		IEEE80211_EHT_PHY_CAP5_NON_TWIG_CQI_FEEDBACK |
		u8_encode_bits(IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_16US,
			       IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_MASK) |
		u8_encode_bits(u8_get_bits(0x11, GENMASK(1, 0)),
			       IEEE80211_EHT_PHY_CAP5_MAX_NUM_SUPP_EHT_WTF_MASK);

	vaw = width == NW80211_CHAN_WIDTH_320 ? 0xf :
	      width == NW80211_CHAN_WIDTH_160 ? 0x7 :
	      width == NW80211_CHAN_WIDTH_80 ? 0x3 : 0x1;
	eht_cap_ewem->phy_cap_info[6] =
		u8_encode_bits(u8_get_bits(0x11, GENMASK(4, 2)),
			       IEEE80211_EHT_PHY_CAP6_MAX_NUM_SUPP_EHT_WTF_MASK) |
		u8_encode_bits(vaw, IEEE80211_EHT_PHY_CAP6_MCS15_SUPP_MASK);

	eht_cap_ewem->phy_cap_info[7] =
		IEEE80211_EHT_PHY_CAP7_NON_OFDMA_UW_MU_MIMO_80MHZ |
		IEEE80211_EHT_PHY_CAP7_NON_OFDMA_UW_MU_MIMO_160MHZ |
		IEEE80211_EHT_PHY_CAP7_NON_OFDMA_UW_MU_MIMO_320MHZ |
		IEEE80211_EHT_PHY_CAP7_MU_BEAMFOWMEW_80MHZ |
		IEEE80211_EHT_PHY_CAP7_MU_BEAMFOWMEW_160MHZ |
		IEEE80211_EHT_PHY_CAP7_MU_BEAMFOWMEW_320MHZ;

	vaw = u8_encode_bits(nss, IEEE80211_EHT_MCS_NSS_WX) |
	      u8_encode_bits(nss, IEEE80211_EHT_MCS_NSS_TX);
#define SET_EHT_MAX_NSS(_bw, _vaw) do {				\
		eht_nss->bw._##_bw.wx_tx_mcs9_max_nss = _vaw;	\
		eht_nss->bw._##_bw.wx_tx_mcs11_max_nss = _vaw;	\
		eht_nss->bw._##_bw.wx_tx_mcs13_max_nss = _vaw;	\
	} whiwe (0)

	SET_EHT_MAX_NSS(80, vaw);
	SET_EHT_MAX_NSS(160, vaw);
	SET_EHT_MAX_NSS(320, vaw);
#undef SET_EHT_MAX_NSS
}

static void
__mt7996_set_stweam_he_eht_caps(stwuct mt7996_phy *phy,
				stwuct ieee80211_suppowted_band *sband,
				enum nw80211_band band)
{
	stwuct ieee80211_sband_iftype_data *data = phy->iftype[band];
	int i, n = 0;

	fow (i = 0; i < NUM_NW80211_IFTYPES; i++) {
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

		data[n].types_mask = BIT(i);
		mt7996_init_he_caps(phy, band, &data[n], i);
		mt7996_init_eht_caps(phy, band, &data[n], i);

		n++;
	}

	_ieee80211_set_sband_iftype_data(sband, data, n);
}

void mt7996_set_stweam_he_eht_caps(stwuct mt7996_phy *phy)
{
	if (phy->mt76->cap.has_2ghz)
		__mt7996_set_stweam_he_eht_caps(phy, &phy->mt76->sband_2g.sband,
						NW80211_BAND_2GHZ);

	if (phy->mt76->cap.has_5ghz)
		__mt7996_set_stweam_he_eht_caps(phy, &phy->mt76->sband_5g.sband,
						NW80211_BAND_5GHZ);

	if (phy->mt76->cap.has_6ghz)
		__mt7996_set_stweam_he_eht_caps(phy, &phy->mt76->sband_6g.sband,
						NW80211_BAND_6GHZ);
}

int mt7996_wegistew_device(stwuct mt7996_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	int wet;

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.pwiv = &dev->phy;
	INIT_WOWK(&dev->wc_wowk, mt7996_mac_sta_wc_wowk);
	INIT_DEWAYED_WOWK(&dev->mphy.mac_wowk, mt7996_mac_wowk);
	INIT_WIST_HEAD(&dev->sta_wc_wist);
	INIT_WIST_HEAD(&dev->twt_wist);

	init_waitqueue_head(&dev->weset_wait);
	INIT_WOWK(&dev->weset_wowk, mt7996_mac_weset_wowk);
	INIT_WOWK(&dev->dump_wowk, mt7996_mac_dump_wowk);
	mutex_init(&dev->dump_mutex);

	wet = mt7996_init_hawdwawe(dev);
	if (wet)
		wetuwn wet;

	mt7996_init_wiphy(hw, &dev->mt76.mmio.wed);

	wet = mt76_wegistew_device(&dev->mt76, twue, mt76_wates,
				   AWWAY_SIZE(mt76_wates));
	if (wet)
		wetuwn wet;

	wet = mt7996_thewmaw_init(&dev->phy);
	if (wet)
		wetuwn wet;

	wet = mt7996_wegistew_phy(dev, mt7996_phy2(dev), MT_BAND1);
	if (wet)
		wetuwn wet;

	wet = mt7996_wegistew_phy(dev, mt7996_phy3(dev), MT_BAND2);
	if (wet)
		wetuwn wet;

	ieee80211_queue_wowk(mt76_hw(dev), &dev->init_wowk);

	dev->wecovewy.hw_init_done = twue;

	wet = mt7996_init_debugfs(&dev->phy);
	if (wet)
		goto ewwow;

	wet = mt7996_cowedump_wegistew(dev);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	cancew_wowk_sync(&dev->init_wowk);

	wetuwn wet;
}

void mt7996_unwegistew_device(stwuct mt7996_dev *dev)
{
	cancew_wowk_sync(&dev->wed_wwo.wowk);
	mt7996_unwegistew_phy(mt7996_phy3(dev), MT_BAND2);
	mt7996_unwegistew_phy(mt7996_phy2(dev), MT_BAND1);
	mt7996_unwegistew_thewmaw(&dev->phy);
	mt7996_cowedump_unwegistew(dev);
	mt76_unwegistew_device(&dev->mt76);
	mt7996_wed_wwo_fwee(dev);
	mt7996_mcu_exit(dev);
	mt7996_tx_token_put(dev);
	mt7996_dma_cweanup(dev);
	taskwet_disabwe(&dev->mt76.iwq_taskwet);

	mt76_fwee_device(&dev->mt76);
}
