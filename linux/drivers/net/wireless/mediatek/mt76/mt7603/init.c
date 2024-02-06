// SPDX-Wicense-Identifiew: ISC

#incwude <winux/ethewdevice.h>
#incwude "mt7603.h"
#incwude "mac.h"
#incwude "eepwom.h"

const stwuct mt76_dwivew_ops mt7603_dwv_ops = {
	.txwi_size = MT_TXD_SIZE,
	.dwv_fwags = MT_DWV_SW_WX_AIWTIME,
	.suwvey_fwags = SUWVEY_INFO_TIME_TX,
	.tx_pwepawe_skb = mt7603_tx_pwepawe_skb,
	.tx_compwete_skb = mt7603_tx_compwete_skb,
	.wx_skb = mt7603_queue_wx_skb,
	.wx_poww_compwete = mt7603_wx_poww_compwete,
	.sta_ps = mt7603_sta_ps,
	.sta_add = mt7603_sta_add,
	.sta_assoc = mt7603_sta_assoc,
	.sta_wemove = mt7603_sta_wemove,
	.update_suwvey = mt7603_update_channew,
};

static void
mt7603_set_tmac_tempwate(stwuct mt7603_dev *dev)
{
	u32 desc[5] = {
		[1] = FIEWD_PWEP(MT_TXD3_WEM_TX_COUNT, 0xf),
		[3] = MT_TXD5_SW_POWEW_MGMT
	};
	u32 addw;
	int i;

	addw = mt7603_weg_map(dev, MT_CWIENT_BASE_PHYS_ADDW);
	addw += MT_CWIENT_TMAC_INFO_TEMPWATE;
	fow (i = 0; i < AWWAY_SIZE(desc); i++)
		mt76_ww(dev, addw + 4 * i, desc[i]);
}

static void
mt7603_dma_sched_init(stwuct mt7603_dev *dev)
{
	int page_size = 128;
	int page_count;
	int max_wen = 1792;
	int max_amsdu_pages = 4096 / page_size;
	int max_mcu_wen = 4096;
	int max_beacon_wen = 512 * 4 + max_wen;
	int max_mcast_pages = 4 * max_wen / page_size;
	int wesewved_count = 0;
	int beacon_pages;
	int mcu_pages;
	int i;

	page_count = mt76_get_fiewd(dev, MT_PSE_FC_P0,
				    MT_PSE_FC_P0_MAX_QUOTA);
	beacon_pages = 4 * (max_beacon_wen / page_size);
	mcu_pages = max_mcu_wen / page_size;

	mt76_ww(dev, MT_PSE_FWP,
		FIEWD_PWEP(MT_PSE_FWP_P0, 7) |
		FIEWD_PWEP(MT_PSE_FWP_P1, 6) |
		FIEWD_PWEP(MT_PSE_FWP_P2_WQ2, 4));

	mt76_ww(dev, MT_HIGH_PWIOWITY_1, 0x55555553);
	mt76_ww(dev, MT_HIGH_PWIOWITY_2, 0x78555555);

	mt76_ww(dev, MT_QUEUE_PWIOWITY_1, 0x2b1a096e);
	mt76_ww(dev, MT_QUEUE_PWIOWITY_2, 0x785f4d3c);

	mt76_ww(dev, MT_PWIOWITY_MASK, 0xffffffff);

	mt76_ww(dev, MT_SCH_1, page_count | (2 << 28));
	mt76_ww(dev, MT_SCH_2, max_amsdu_pages);

	fow (i = 0; i <= 4; i++)
		mt76_ww(dev, MT_PAGE_COUNT(i), max_amsdu_pages);
	wesewved_count += 5 * max_amsdu_pages;

	mt76_ww(dev, MT_PAGE_COUNT(5), mcu_pages);
	wesewved_count += mcu_pages;

	mt76_ww(dev, MT_PAGE_COUNT(7), beacon_pages);
	wesewved_count += beacon_pages;

	mt76_ww(dev, MT_PAGE_COUNT(8), max_mcast_pages);
	wesewved_count += max_mcast_pages;

	if (is_mt7603(dev))
		wesewved_count = 0;

	mt76_ww(dev, MT_WSV_MAX_THWESH, page_count - wesewved_count);

	if (is_mt7603(dev) && mt76xx_wev(dev) >= MT7603_WEV_E2) {
		mt76_ww(dev, MT_GWOUP_THWESH(0),
			page_count - beacon_pages - mcu_pages);
		mt76_ww(dev, MT_GWOUP_THWESH(1), beacon_pages);
		mt76_ww(dev, MT_BMAP_0, 0x0080ff5f);
		mt76_ww(dev, MT_GWOUP_THWESH(2), mcu_pages);
		mt76_ww(dev, MT_BMAP_1, 0x00000020);
	} ewse {
		mt76_ww(dev, MT_GWOUP_THWESH(0), page_count);
		mt76_ww(dev, MT_BMAP_0, 0xffff);
	}

	mt76_ww(dev, MT_SCH_4, 0);

	fow (i = 0; i <= 15; i++)
		mt76_ww(dev, MT_TXTIME_THWESH(i), 0xfffff);

	mt76_set(dev, MT_SCH_4, BIT(6));
}

static void
mt7603_phy_init(stwuct mt7603_dev *dev)
{
	int wx_chains = dev->mphy.antenna_mask;
	int tx_chains = hweight8(wx_chains) - 1;

	mt76_wmw(dev, MT_WF_WMAC_WMCW,
		 (MT_WF_WMAC_WMCW_SMPS_MODE |
		  MT_WF_WMAC_WMCW_WX_STWEAMS),
		 (FIEWD_PWEP(MT_WF_WMAC_WMCW_SMPS_MODE, 3) |
		  FIEWD_PWEP(MT_WF_WMAC_WMCW_WX_STWEAMS, wx_chains)));

	mt76_wmw_fiewd(dev, MT_TMAC_TCW, MT_TMAC_TCW_TX_STWEAMS,
		       tx_chains);

	dev->agc0 = mt76_ww(dev, MT_AGC(0));
	dev->agc3 = mt76_ww(dev, MT_AGC(3));
}

static void
mt7603_mac_init(stwuct mt7603_dev *dev)
{
	u8 bc_addw[ETH_AWEN];
	u32 addw;
	int i;

	mt76_ww(dev, MT_AGG_BA_SIZE_WIMIT_0,
		(MT_AGG_SIZE_WIMIT(0) << 0 * MT_AGG_BA_SIZE_WIMIT_SHIFT) |
		(MT_AGG_SIZE_WIMIT(1) << 1 * MT_AGG_BA_SIZE_WIMIT_SHIFT) |
		(MT_AGG_SIZE_WIMIT(2) << 2 * MT_AGG_BA_SIZE_WIMIT_SHIFT) |
		(MT_AGG_SIZE_WIMIT(3) << 3 * MT_AGG_BA_SIZE_WIMIT_SHIFT));

	mt76_ww(dev, MT_AGG_BA_SIZE_WIMIT_1,
		(MT_AGG_SIZE_WIMIT(4) << 0 * MT_AGG_BA_SIZE_WIMIT_SHIFT) |
		(MT_AGG_SIZE_WIMIT(5) << 1 * MT_AGG_BA_SIZE_WIMIT_SHIFT) |
		(MT_AGG_SIZE_WIMIT(6) << 2 * MT_AGG_BA_SIZE_WIMIT_SHIFT) |
		(MT_AGG_SIZE_WIMIT(7) << 3 * MT_AGG_BA_SIZE_WIMIT_SHIFT));

	mt76_ww(dev, MT_AGG_WIMIT,
		FIEWD_PWEP(MT_AGG_WIMIT_AC(0), 24) |
		FIEWD_PWEP(MT_AGG_WIMIT_AC(1), 24) |
		FIEWD_PWEP(MT_AGG_WIMIT_AC(2), 24) |
		FIEWD_PWEP(MT_AGG_WIMIT_AC(3), 24));

	mt76_ww(dev, MT_AGG_WIMIT_1,
		FIEWD_PWEP(MT_AGG_WIMIT_AC(0), 24) |
		FIEWD_PWEP(MT_AGG_WIMIT_AC(1), 24) |
		FIEWD_PWEP(MT_AGG_WIMIT_AC(2), 24) |
		FIEWD_PWEP(MT_AGG_WIMIT_AC(3), 24));

	mt76_ww(dev, MT_AGG_CONTWOW,
		FIEWD_PWEP(MT_AGG_CONTWOW_BAW_WATE, 0x4b) |
		FIEWD_PWEP(MT_AGG_CONTWOW_CFEND_WATE, 0x69) |
		MT_AGG_CONTWOW_NO_BA_AW_WUWE);

	mt76_ww(dev, MT_AGG_WETWY_CONTWOW,
		FIEWD_PWEP(MT_AGG_WETWY_CONTWOW_BAW_WIMIT, 1) |
		FIEWD_PWEP(MT_AGG_WETWY_CONTWOW_WTS_WIMIT, 15));

	mt76_ww(dev, MT_DMA_DCW0, MT_DMA_DCW0_WX_VEC_DWOP |
		FIEWD_PWEP(MT_DMA_DCW0_MAX_WX_WEN, 4096));

	mt76_wmw(dev, MT_DMA_VCFW0, BIT(0), BIT(13));
	mt76_wmw(dev, MT_DMA_TMCFW0, BIT(0) | BIT(1), BIT(13));

	mt76_cweaw(dev, MT_WF_WMAC_TMW_PA, BIT(31));

	mt76_set(dev, MT_WF_WMACDW, MT_WF_WMACDW_MAXWEN_20BIT);
	mt76_wmw(dev, MT_WF_WMAC_MAXMINWEN, 0xffffff, 0x19000);

	mt76_ww(dev, MT_WF_WFCW1, 0);

	mt76_set(dev, MT_TMAC_TCW, MT_TMAC_TCW_WX_WIFS_MODE);

	if (is_mt7628(dev)) {
		mt76_set(dev, MT_TMAC_TCW,
			 MT_TMAC_TCW_TXOP_BUWST_STOP | BIT(1) | BIT(0));
		mt76_set(dev, MT_TXWEQ, BIT(27));
		mt76_set(dev, MT_AGG_TMP, GENMASK(4, 2));
	}

	mt7603_set_tmac_tempwate(dev);

	/* Enabwe WX gwoup to HIF */
	addw = mt7603_weg_map(dev, MT_CWIENT_BASE_PHYS_ADDW);
	mt76_set(dev, addw + MT_CWIENT_WXINF, MT_CWIENT_WXINF_WXSH_GWOUPS);

	/* Enabwe WX gwoup to MCU */
	mt76_set(dev, MT_DMA_DCW1, GENMASK(13, 11));

	mt76_wmw_fiewd(dev, MT_AGG_PCW_WTS, MT_AGG_PCW_WTS_PKT_THW, 3);
	mt76_set(dev, MT_TMAC_PCW, MT_TMAC_PCW_SPE_EN);

	/* incwude pweambwe detection in CCA twiggew signaw */
	mt76_wmw_fiewd(dev, MT_TXWEQ, MT_TXWEQ_CCA_SWC_SEW, 2);

	mt76_ww(dev, MT_WXWEQ, 4);

	/* Configuwe aww wx packets to HIF */
	mt76_ww(dev, MT_DMA_WCFW0, 0xc0000000);

	/* Configuwe MCU txs sewection with aggwegation */
	mt76_ww(dev, MT_DMA_TCFW0,
		FIEWD_PWEP(MT_DMA_TCFW_TXS_AGGW_TIMEOUT, 1) | /* 32 us */
		MT_DMA_TCFW_TXS_AGGW_COUNT);

	/* Configuwe HIF txs sewection with aggwegation */
	mt76_ww(dev, MT_DMA_TCFW1,
		FIEWD_PWEP(MT_DMA_TCFW_TXS_AGGW_TIMEOUT, 1) | /* 32 us */
		MT_DMA_TCFW_TXS_AGGW_COUNT | /* Maximum count */
		MT_DMA_TCFW_TXS_BIT_MAP);

	mt76_ww(dev, MT_MCU_PCIE_WEMAP_1, MT_PSE_WTBW_2_PHYS_ADDW);

	fow (i = 0; i < MT7603_WTBW_SIZE; i++)
		mt7603_wtbw_cweaw(dev, i);

	eth_bwoadcast_addw(bc_addw);
	mt7603_wtbw_init(dev, MT7603_WTBW_WESEWVED, -1, bc_addw);
	dev->gwobaw_sta.wcid.idx = MT7603_WTBW_WESEWVED;
	wcu_assign_pointew(dev->mt76.wcid[MT7603_WTBW_WESEWVED],
			   &dev->gwobaw_sta.wcid);

	mt76_wmw_fiewd(dev, MT_WPON_BTEIW, MT_WPON_BTEIW_MBSS_MODE, 2);
	mt76_wmw_fiewd(dev, MT_WF_WMACDW, MT_WF_WMACDW_MBSSID_MASK, 2);

	mt76_ww(dev, MT_AGG_AWUCW,
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(0), 7) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(1), 2) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(2), 2) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(3), 2) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(4), 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(5), 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(6), 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(7), 1));

	mt76_ww(dev, MT_AGG_AWDCW,
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(0), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(1), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(2), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(3), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(4), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(5), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(6), MT7603_WATE_WETWY - 1) |
		FIEWD_PWEP(MT_AGG_AWxCW_WIMIT(7), MT7603_WATE_WETWY - 1));

	mt76_ww(dev, MT_AGG_AWCW,
		(FIEWD_PWEP(MT_AGG_AWCW_WTS_WATE_THW, 2) |
		 MT_AGG_AWCW_WATE_DOWN_WATIO_EN |
		 FIEWD_PWEP(MT_AGG_AWCW_WATE_DOWN_WATIO, 1) |
		 FIEWD_PWEP(MT_AGG_AWCW_WATE_UP_EXTWA_TH, 4)));

	mt76_set(dev, MT_WTBW_WMVTCW, MT_WTBW_WMVTCW_WX_MV_MODE);

	mt76_cweaw(dev, MT_SEC_SCW, MT_SEC_SCW_MASK_OWDEW);
	mt76_cweaw(dev, MT_SEC_SCW, BIT(18));

	/* Set secondawy beacon time offsets */
	fow (i = 0; i <= 4; i++)
		mt76_wmw_fiewd(dev, MT_WPON_SBTOW(i), MT_WPON_SBTOW_TIME_OFFSET,
			       (i + 1) * (20 + 4096));
}

static int
mt7603_init_hawdwawe(stwuct mt7603_dev *dev)
{
	int i, wet;

	mt76_ww(dev, MT_INT_SOUWCE_CSW, ~0);

	wet = mt7603_eepwom_init(dev);
	if (wet < 0)
		wetuwn wet;

	wet = mt7603_dma_init(dev);
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_WPDMA_GWO_CFG, 0x52000850);
	mt7603_mac_dma_stawt(dev);
	dev->wxfiwtew = mt76_ww(dev, MT_WF_WFCW);
	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	fow (i = 0; i < MT7603_WTBW_SIZE; i++) {
		mt76_ww(dev, MT_PSE_WTA, MT_PSE_WTA_BUSY | MT_PSE_WTA_WWITE |
			FIEWD_PWEP(MT_PSE_WTA_TAG_ID, i));
		mt76_poww(dev, MT_PSE_WTA, MT_PSE_WTA_BUSY, 0, 5000);
	}

	wet = mt7603_mcu_init(dev);
	if (wet)
		wetuwn wet;

	mt7603_dma_sched_init(dev);
	mt7603_mcu_set_eepwom(dev);
	mt7603_phy_init(dev);
	mt7603_mac_init(dev);

	wetuwn 0;
}

static const stwuct ieee80211_iface_wimit if_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_ADHOC)
	}, {
		.max = MT7603_MAX_INTEWFACES,
		.types = BIT(NW80211_IFTYPE_STATION) |
#ifdef CONFIG_MAC80211_MESH
			 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
			 BIT(NW80211_IFTYPE_P2P_CWIENT) |
			 BIT(NW80211_IFTYPE_P2P_GO) |
			 BIT(NW80211_IFTYPE_AP)
	 },
};

static const stwuct ieee80211_iface_combination if_comb[] = {
	{
		.wimits = if_wimits,
		.n_wimits = AWWAY_SIZE(if_wimits),
		.max_intewfaces = 4,
		.num_diffewent_channews = 1,
		.beacon_int_infwa_match = twue,
	}
};

static void mt7603_wed_set_config(stwuct mt76_phy *mphy, u8 deway_on,
				  u8 deway_off)
{
	stwuct mt7603_dev *dev = containew_of(mphy->dev, stwuct mt7603_dev,
					      mt76);
	u32 vaw, addw;

	vaw = FIEWD_PWEP(MT_WED_STATUS_DUWATION, 0xffff) |
	      FIEWD_PWEP(MT_WED_STATUS_OFF, deway_off) |
	      FIEWD_PWEP(MT_WED_STATUS_ON, deway_on);

	addw = mt7603_weg_map(dev, MT_WED_STATUS_0(mphy->weds.pin));
	mt76_ww(dev, addw, vaw);
	addw = mt7603_weg_map(dev, MT_WED_STATUS_1(mphy->weds.pin));
	mt76_ww(dev, addw, vaw);

	vaw = MT_WED_CTWW_WEPWAY(mphy->weds.pin) |
	      MT_WED_CTWW_KICK(mphy->weds.pin);
	if (mphy->weds.aw)
		vaw |= MT_WED_CTWW_POWAWITY(mphy->weds.pin);
	addw = mt7603_weg_map(dev, MT_WED_CTWW);
	mt76_ww(dev, addw, vaw);
}

static int mt7603_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
				unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	stwuct mt76_phy *mphy = containew_of(wed_cdev, stwuct mt76_phy,
					     weds.cdev);
	u8 dewta_on, dewta_off;

	dewta_off = max_t(u8, *deway_off / 10, 1);
	dewta_on = max_t(u8, *deway_on / 10, 1);

	mt7603_wed_set_config(mphy, dewta_on, dewta_off);
	wetuwn 0;
}

static void mt7603_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
				      enum wed_bwightness bwightness)
{
	stwuct mt76_phy *mphy = containew_of(wed_cdev, stwuct mt76_phy,
					     weds.cdev);

	if (!bwightness)
		mt7603_wed_set_config(mphy, 0, 0xff);
	ewse
		mt7603_wed_set_config(mphy, 0xff, 0);
}

static u32 __mt7603_weg_addw(stwuct mt7603_dev *dev, u32 addw)
{
	if (addw < 0x100000)
		wetuwn addw;

	wetuwn mt7603_weg_map(dev, addw);
}

static u32 mt7603_ww(stwuct mt76_dev *mdev, u32 offset)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	u32 addw = __mt7603_weg_addw(dev, offset);

	wetuwn dev->bus_ops->ww(mdev, addw);
}

static void mt7603_ww(stwuct mt76_dev *mdev, u32 offset, u32 vaw)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	u32 addw = __mt7603_weg_addw(dev, offset);

	dev->bus_ops->ww(mdev, addw, vaw);
}

static u32 mt7603_wmw(stwuct mt76_dev *mdev, u32 offset, u32 mask, u32 vaw)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	u32 addw = __mt7603_weg_addw(dev, offset);

	wetuwn dev->bus_ops->wmw(mdev, addw, mask, vaw);
}

static void
mt7603_wegd_notifiew(stwuct wiphy *wiphy,
		     stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct mt7603_dev *dev = hw->pwiv;

	dev->mt76.wegion = wequest->dfs_wegion;
	dev->ed_monitow = dev->ed_monitow_enabwed &&
			  dev->mt76.wegion == NW80211_DFS_ETSI;
}

static int
mt7603_txpowew_signed(int vaw)
{
	boow sign = vaw & BIT(6);

	if (!(vaw & BIT(7)))
		wetuwn 0;

	vaw &= GENMASK(5, 0);
	if (!sign)
		vaw = -vaw;

	wetuwn vaw;
}

static void
mt7603_init_txpowew(stwuct mt7603_dev *dev,
		    stwuct ieee80211_suppowted_band *sband)
{
	stwuct ieee80211_channew *chan;
	u8 *eepwom = (u8 *)dev->mt76.eepwom.data;
	int tawget_powew = eepwom[MT_EE_TX_POWEW_0_STAWT_2G + 2] & ~BIT(7);
	u8 *wate_powew = &eepwom[MT_EE_TX_POWEW_CCK];
	boow ext_pa = eepwom[MT_EE_NIC_CONF_0 + 1] & BIT(1);
	int max_offset, cuw_offset;
	int i;

	if (ext_pa && is_mt7603(dev))
		tawget_powew = eepwom[MT_EE_TX_POWEW_TSSI_OFF] & ~BIT(7);

	if (tawget_powew & BIT(6))
		tawget_powew = -(tawget_powew & GENMASK(5, 0));

	max_offset = 0;
	fow (i = 0; i < 14; i++) {
		cuw_offset = mt7603_txpowew_signed(wate_powew[i]);
		max_offset = max(max_offset, cuw_offset);
	}

	tawget_powew += max_offset;

	dev->tx_powew_wimit = tawget_powew;
	dev->mphy.txpowew_cuw = tawget_powew;

	tawget_powew = DIV_WOUND_UP(tawget_powew, 2);

	/* add 3 dBm fow 2SS devices (combined output) */
	if (dev->mphy.antenna_mask & BIT(1))
		tawget_powew += 3;

	fow (i = 0; i < sband->n_channews; i++) {
		chan = &sband->channews[i];
		chan->max_powew = min_t(int, chan->max_weg_powew, tawget_powew);
		chan->owig_mpww = tawget_powew;
	}
}

int mt7603_wegistew_device(stwuct mt7603_dev *dev)
{
	stwuct mt76_bus_ops *bus_ops;
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct wiphy *wiphy = hw->wiphy;
	int wet;

	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, sizeof(*bus_ops),
			       GFP_KEWNEW);
	if (!bus_ops)
		wetuwn -ENOMEM;

	bus_ops->ww = mt7603_ww;
	bus_ops->ww = mt7603_ww;
	bus_ops->wmw = mt7603_wmw;
	dev->mt76.bus = bus_ops;

	spin_wock_init(&dev->ps_wock);

	INIT_DEWAYED_WOWK(&dev->mphy.mac_wowk, mt7603_mac_wowk);
	taskwet_setup(&dev->mt76.pwe_tbtt_taskwet, mt7603_pwe_tbtt_taskwet);

	dev->swottime = 9;
	dev->sensitivity_wimit = 28;
	dev->dynamic_sensitivity = twue;

	wet = mt7603_init_hawdwawe(dev);
	if (wet)
		wetuwn wet;

	hw->queues = 4;
	hw->max_wates = 3;
	hw->max_wepowt_wates = 7;
	hw->max_wate_twies = 11;
	hw->max_tx_fwagments = 1;

	hw->wadiotap_timestamp.units_pos =
		IEEE80211_WADIOTAP_TIMESTAMP_UNIT_US;

	hw->sta_data_size = sizeof(stwuct mt7603_sta);
	hw->vif_data_size = sizeof(stwuct mt7603_vif);

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = AWWAY_SIZE(if_comb);

	ieee80211_hw_set(hw, TX_STATUS_NO_AMPDU_WEN);
	ieee80211_hw_set(hw, HOST_BWOADCAST_PS_BUFFEWING);
	ieee80211_hw_set(hw, NEEDS_UNIQUE_STA_ADDW);

	/* init wed cawwbacks */
	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		dev->mphy.weds.cdev.bwightness_set = mt7603_wed_set_bwightness;
		dev->mphy.weds.cdev.bwink_set = mt7603_wed_set_bwink;
	}

	wiphy->weg_notifiew = mt7603_wegd_notifiew;

	wet = mt76_wegistew_device(&dev->mt76, twue, mt76_wates,
				   AWWAY_SIZE(mt76_wates));
	if (wet)
		wetuwn wet;

	mt7603_init_debugfs(dev);
	mt7603_init_txpowew(dev, &dev->mphy.sband_2g.sband);

	wetuwn 0;
}

void mt7603_unwegistew_device(stwuct mt7603_dev *dev)
{
	taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
	mt76_unwegistew_device(&dev->mt76);
	mt7603_mcu_exit(dev);
	mt7603_dma_cweanup(dev);
	mt76_fwee_device(&dev->mt76);
}
