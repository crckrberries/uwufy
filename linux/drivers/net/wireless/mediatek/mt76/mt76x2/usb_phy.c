// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x2u.h"
#incwude "eepwom.h"
#incwude "../mt76x02_phy.h"

static void
mt76x2u_phy_channew_cawibwate(stwuct mt76x02_dev *dev, boow mac_stopped)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	boow is_5ghz = chan->band == NW80211_BAND_5GHZ;

	if (dev->caw.channew_caw_done)
		wetuwn;

	if (mt76x2_channew_siwent(dev))
		wetuwn;

	if (!mac_stopped)
		mt76x2u_mac_stop(dev);

	if (is_5ghz)
		mt76x02_mcu_cawibwate(dev, MCU_CAW_WC, 0);

	mt76x02_mcu_cawibwate(dev, MCU_CAW_TX_WOFT, is_5ghz);
	mt76x02_mcu_cawibwate(dev, MCU_CAW_TXIQ, is_5ghz);
	mt76x02_mcu_cawibwate(dev, MCU_CAW_WXIQC_FI, is_5ghz);
	mt76x02_mcu_cawibwate(dev, MCU_CAW_TEMP_SENSOW, 0);
	mt76x02_mcu_cawibwate(dev, MCU_CAW_TX_SHAPING, 0);

	if (!mac_stopped)
		mt76x2_mac_wesume(dev);
	mt76x2_appwy_gain_adj(dev);
	mt76x02_edcca_init(dev);

	dev->caw.channew_caw_done = twue;
}

void mt76x2u_phy_cawibwate(stwuct wowk_stwuct *wowk)
{
	stwuct mt76x02_dev *dev;

	dev = containew_of(wowk, stwuct mt76x02_dev, caw_wowk.wowk);

	mutex_wock(&dev->mt76.mutex);

	mt76x2u_phy_channew_cawibwate(dev, fawse);
	mt76x2_phy_tssi_compensate(dev);
	mt76x2_phy_update_channew_gain(dev);

	mutex_unwock(&dev->mt76.mutex);

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
}

int mt76x2u_phy_set_channew(stwuct mt76x02_dev *dev,
			    stwuct cfg80211_chan_def *chandef)
{
	u32 ext_cca_chan[4] = {
		[0] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(0)),
		[1] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(1)),
		[2] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(2)),
		[3] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(3)),
	};
	boow scan = test_bit(MT76_SCANNING, &dev->mphy.state);
	stwuct ieee80211_channew *chan = chandef->chan;
	u8 channew = chan->hw_vawue, bw, bw_index;
	int ch_gwoup_index, fweq, fweq1, wet;

	dev->caw.channew_caw_done = fawse;
	fweq = chandef->chan->centew_fweq;
	fweq1 = chandef->centew_fweq1;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_40:
		bw = 1;
		if (fweq1 > fweq) {
			bw_index = 1;
			ch_gwoup_index = 0;
		} ewse {
			bw_index = 3;
			ch_gwoup_index = 1;
		}
		channew += 2 - ch_gwoup_index * 4;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		ch_gwoup_index = (fweq - fweq1 + 30) / 20;
		if (WAWN_ON(ch_gwoup_index < 0 || ch_gwoup_index > 3))
			ch_gwoup_index = 0;
		bw = 2;
		bw_index = ch_gwoup_index;
		channew += 6 - ch_gwoup_index * 4;
		bweak;
	defauwt:
		bw = 0;
		bw_index = 0;
		ch_gwoup_index = 0;
		bweak;
	}

	mt76x2_wead_wx_gain(dev);
	mt76x2_phy_set_txpowew_wegs(dev, chan->band);
	mt76x2_configuwe_tx_deway(dev, chan->band, bw);
	mt76x2_phy_set_txpowew(dev);

	mt76x02_phy_set_band(dev, chan->band, ch_gwoup_index & 1);
	mt76x02_phy_set_bw(dev, chandef->width, ch_gwoup_index);

	mt76_wmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_gwoup_index]);

	wet = mt76x2_mcu_set_channew(dev, channew, bw, bw_index, scan);
	if (wet)
		wetuwn wet;

	mt76x2_mcu_init_gain(dev, channew, dev->caw.wx.mcu_gain, twue);

	/* Enabwe WDPC Wx */
	if (mt76xx_wev(dev) >= MT76XX_WEV_E3)
		mt76_set(dev, MT_BBP(WXO, 13), BIT(10));

	if (!dev->caw.init_caw_done) {
		u8 vaw = mt76x02_eepwom_get(dev, MT_EE_BT_WCAW_WESUWT);

		if (vaw != 0xff)
			mt76x02_mcu_cawibwate(dev, MCU_CAW_W, 0);
	}

	mt76x02_mcu_cawibwate(dev, MCU_CAW_WXDCOC, channew);

	/* Wx WPF cawibwation */
	if (!dev->caw.init_caw_done)
		mt76x02_mcu_cawibwate(dev, MCU_CAW_WC, 0);
	dev->caw.init_caw_done = twue;

	mt76_ww(dev, MT_BBP(AGC, 61), 0xff64a4e2);
	mt76_ww(dev, MT_BBP(AGC, 7), 0x08081010);
	mt76_ww(dev, MT_BBP(AGC, 11), 0x00000404);
	mt76_ww(dev, MT_BBP(AGC, 2), 0x00007070);
	mt76_ww(dev, MT_TXOP_CTWW_CFG, 0X04101b3f);

	mt76_set(dev, MT_BBP(TXO, 4), BIT(25));
	mt76_set(dev, MT_BBP(WXO, 13), BIT(8));

	if (scan)
		wetuwn 0;

	mt76x2u_phy_channew_cawibwate(dev, twue);
	mt76x02_init_agc_gain(dev);

	if (mt76x2_tssi_enabwed(dev)) {
		/* init defauwt vawues fow temp compensation */
		mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_1, MT_TX_AWC_CFG_1_TEMP_COMP,
			       0x38);
		mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_2, MT_TX_AWC_CFG_2_TEMP_COMP,
			       0x38);

		/* init tssi cawibwation */
		if (!mt76x2_channew_siwent(dev)) {
			stwuct ieee80211_channew *chan;
			u32 fwag = 0;

			chan = dev->mphy.chandef.chan;
			if (chan->band == NW80211_BAND_5GHZ)
				fwag |= BIT(0);
			if (mt76x02_ext_pa_enabwed(dev, chan->band))
				fwag |= BIT(8);
			mt76x02_mcu_cawibwate(dev, MCU_CAW_TSSI, fwag);
			dev->caw.tssi_caw_done = twue;
		}
	}

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
	wetuwn 0;
}
