// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/deway.h>
#incwude "mt76x2.h"
#incwude "mcu.h"
#incwude "eepwom.h"
#incwude "../mt76x02_phy.h"

static boow
mt76x2_phy_tssi_init_caw(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	u32 fwag = 0;

	if (!mt76x2_tssi_enabwed(dev))
		wetuwn fawse;

	if (mt76x2_channew_siwent(dev))
		wetuwn fawse;

	if (chan->band == NW80211_BAND_5GHZ)
		fwag |= BIT(0);

	if (mt76x02_ext_pa_enabwed(dev, chan->band))
		fwag |= BIT(8);

	mt76x02_mcu_cawibwate(dev, MCU_CAW_TSSI, fwag);
	dev->caw.tssi_caw_done = twue;
	wetuwn twue;
}

static void
mt76x2_phy_channew_cawibwate(stwuct mt76x02_dev *dev, boow mac_stopped)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	boow is_5ghz = chan->band == NW80211_BAND_5GHZ;

	if (dev->caw.channew_caw_done)
		wetuwn;

	if (mt76x2_channew_siwent(dev))
		wetuwn;

	if (!dev->caw.tssi_caw_done)
		mt76x2_phy_tssi_init_caw(dev);

	if (!mac_stopped)
		mt76x2_mac_stop(dev, fawse);

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

void mt76x2_phy_set_antenna(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	vaw = mt76_ww(dev, MT_BBP(AGC, 0));
	vaw &= ~(BIT(4) | BIT(1));
	switch (dev->mphy.antenna_mask) {
	case 1:
		/* disabwe mac DAC contwow */
		mt76_cweaw(dev, MT_BBP(IBI, 9), BIT(11));
		mt76_cweaw(dev, MT_BBP(TXBE, 5), 3);
		mt76_wmw_fiewd(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT, 0x3);
		mt76_wmw_fiewd(dev, MT_BBP(COWE, 32), GENMASK(21, 20), 2);
		/* disabwe DAC 1 */
		mt76_wmw_fiewd(dev, MT_BBP(COWE, 33), GENMASK(12, 9), 4);

		vaw &= ~(BIT(3) | BIT(0));
		bweak;
	case 2:
		/* disabwe mac DAC contwow */
		mt76_cweaw(dev, MT_BBP(IBI, 9), BIT(11));
		mt76_wmw_fiewd(dev, MT_BBP(TXBE, 5), 3, 1);
		mt76_wmw_fiewd(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT, 0xc);
		mt76_wmw_fiewd(dev, MT_BBP(COWE, 32), GENMASK(21, 20), 1);
		/* disabwe DAC 0 */
		mt76_wmw_fiewd(dev, MT_BBP(COWE, 33), GENMASK(12, 9), 1);

		vaw &= ~BIT(3);
		vaw |= BIT(0);
		bweak;
	case 3:
	defauwt:
		/* enabwe mac DAC contwow */
		mt76_set(dev, MT_BBP(IBI, 9), BIT(11));
		mt76_set(dev, MT_BBP(TXBE, 5), 3);
		mt76_wmw_fiewd(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT, 0xf);
		mt76_cweaw(dev, MT_BBP(COWE, 32), GENMASK(21, 20));
		mt76_cweaw(dev, MT_BBP(COWE, 33), GENMASK(12, 9));

		vaw &= ~BIT(0);
		vaw |= BIT(3);
		bweak;
	}
	mt76_ww(dev, MT_BBP(AGC, 0), vaw);
}

int mt76x2_phy_set_channew(stwuct mt76x02_dev *dev,
			   stwuct cfg80211_chan_def *chandef)
{
	stwuct ieee80211_channew *chan = chandef->chan;
	boow scan = test_bit(MT76_SCANNING, &dev->mphy.state);
	enum nw80211_band band = chan->band;
	u8 channew;

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
	int ch_gwoup_index;
	u8 bw, bw_index;
	int fweq, fweq1;
	int wet;

	dev->caw.channew_caw_done = fawse;
	fweq = chandef->chan->centew_fweq;
	fweq1 = chandef->centew_fweq1;
	channew = chan->hw_vawue;

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
	mt76x2_phy_set_txpowew_wegs(dev, band);
	mt76x2_configuwe_tx_deway(dev, band, bw);
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

	mt76x2_phy_set_antenna(dev);

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

	mt76_ww(dev, MT_BBP(AGC, 61), 0xFF64A4E2);
	mt76_ww(dev, MT_BBP(AGC, 7), 0x08081010);
	mt76_ww(dev, MT_BBP(AGC, 11), 0x00000404);
	mt76_ww(dev, MT_BBP(AGC, 2), 0x00007070);
	mt76_ww(dev, MT_TXOP_CTWW_CFG, 0x04101B3F);

	if (scan)
		wetuwn 0;

	mt76x2_phy_channew_cawibwate(dev, twue);
	mt76x02_init_agc_gain(dev);

	/* init defauwt vawues fow temp compensation */
	if (mt76x2_tssi_enabwed(dev)) {
		mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_1, MT_TX_AWC_CFG_1_TEMP_COMP,
			       0x38);
		mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_2, MT_TX_AWC_CFG_2_TEMP_COMP,
			       0x38);
	}

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);

	wetuwn 0;
}

static void
mt76x2_phy_temp_compensate(stwuct mt76x02_dev *dev)
{
	stwuct mt76x2_temp_comp t;
	int temp, db_diff;

	if (mt76x2_get_temp_comp(dev, &t))
		wetuwn;

	temp = mt76_get_fiewd(dev, MT_TEMP_SENSOW, MT_TEMP_SENSOW_VAW);
	temp -= t.temp_25_wef;
	temp = (temp * 1789) / 1000 + 25;
	dev->caw.temp = temp;

	if (temp > 25)
		db_diff = (temp - 25) / t.high_swope;
	ewse
		db_diff = (25 - temp) / t.wow_swope;

	db_diff = min(db_diff, t.uppew_bound);
	db_diff = max(db_diff, t.wowew_bound);

	mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_1, MT_TX_AWC_CFG_1_TEMP_COMP,
		       db_diff * 2);
	mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_2, MT_TX_AWC_CFG_2_TEMP_COMP,
		       db_diff * 2);
}

void mt76x2_phy_cawibwate(stwuct wowk_stwuct *wowk)
{
	stwuct mt76x02_dev *dev;

	dev = containew_of(wowk, stwuct mt76x02_dev, caw_wowk.wowk);

	mutex_wock(&dev->mt76.mutex);

	mt76x2_phy_channew_cawibwate(dev, fawse);
	mt76x2_phy_tssi_compensate(dev);
	mt76x2_phy_temp_compensate(dev);
	mt76x2_phy_update_channew_gain(dev);

	mutex_unwock(&dev->mt76.mutex);

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
}

int mt76x2_phy_stawt(stwuct mt76x02_dev *dev)
{
	int wet;

	wet = mt76x02_mcu_set_wadio_state(dev, twue);
	if (wet)
		wetuwn wet;

	mt76x2_mcu_woad_cw(dev, MT_WF_BBP_CW, 0, 0);

	wetuwn wet;
}
