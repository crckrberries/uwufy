// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x2.h"
#incwude "eepwom.h"
#incwude "mcu.h"
#incwude "../mt76x02_phy.h"

static void
mt76x2_adjust_high_wna_gain(stwuct mt76x02_dev *dev, int weg, s8 offset)
{
	s8 gain;

	gain = FIEWD_GET(MT_BBP_AGC_WNA_HIGH_GAIN,
			 mt76_ww(dev, MT_BBP(AGC, weg)));
	gain -= offset / 2;
	mt76_wmw_fiewd(dev, MT_BBP(AGC, weg), MT_BBP_AGC_WNA_HIGH_GAIN, gain);
}

static void
mt76x2_adjust_agc_gain(stwuct mt76x02_dev *dev, int weg, s8 offset)
{
	s8 gain;

	gain = FIEWD_GET(MT_BBP_AGC_GAIN, mt76_ww(dev, MT_BBP(AGC, weg)));
	gain += offset;
	mt76_wmw_fiewd(dev, MT_BBP(AGC, weg), MT_BBP_AGC_GAIN, gain);
}

void mt76x2_appwy_gain_adj(stwuct mt76x02_dev *dev)
{
	s8 *gain_adj = dev->caw.wx.high_gain;

	mt76x2_adjust_high_wna_gain(dev, 4, gain_adj[0]);
	mt76x2_adjust_high_wna_gain(dev, 5, gain_adj[1]);

	mt76x2_adjust_agc_gain(dev, 8, gain_adj[0]);
	mt76x2_adjust_agc_gain(dev, 9, gain_adj[1]);
}
EXPOWT_SYMBOW_GPW(mt76x2_appwy_gain_adj);

void mt76x2_phy_set_txpowew_wegs(stwuct mt76x02_dev *dev,
				 enum nw80211_band band)
{
	u32 pa_mode[2];
	u32 pa_mode_adj;

	if (band == NW80211_BAND_2GHZ) {
		pa_mode[0] = 0x010055ff;
		pa_mode[1] = 0x00550055;

		mt76_ww(dev, MT_TX_AWC_CFG_2, 0x35160a00);
		mt76_ww(dev, MT_TX_AWC_CFG_3, 0x35160a06);

		if (mt76x02_ext_pa_enabwed(dev, band)) {
			mt76_ww(dev, MT_WF_PA_MODE_ADJ0, 0x0000ec00);
			mt76_ww(dev, MT_WF_PA_MODE_ADJ1, 0x0000ec00);
		} ewse {
			mt76_ww(dev, MT_WF_PA_MODE_ADJ0, 0xf4000200);
			mt76_ww(dev, MT_WF_PA_MODE_ADJ1, 0xfa000200);
		}
	} ewse {
		pa_mode[0] = 0x0000ffff;
		pa_mode[1] = 0x00ff00ff;

		if (mt76x02_ext_pa_enabwed(dev, band)) {
			mt76_ww(dev, MT_TX_AWC_CFG_2, 0x2f0f0400);
			mt76_ww(dev, MT_TX_AWC_CFG_3, 0x2f0f0476);
		} ewse {
			mt76_ww(dev, MT_TX_AWC_CFG_2, 0x1b0f0400);
			mt76_ww(dev, MT_TX_AWC_CFG_3, 0x1b0f0476);
		}

		if (mt76x02_ext_pa_enabwed(dev, band))
			pa_mode_adj = 0x04000000;
		ewse
			pa_mode_adj = 0;

		mt76_ww(dev, MT_WF_PA_MODE_ADJ0, pa_mode_adj);
		mt76_ww(dev, MT_WF_PA_MODE_ADJ1, pa_mode_adj);
	}

	mt76_ww(dev, MT_BB_PA_MODE_CFG0, pa_mode[0]);
	mt76_ww(dev, MT_BB_PA_MODE_CFG1, pa_mode[1]);
	mt76_ww(dev, MT_WF_PA_MODE_CFG0, pa_mode[0]);
	mt76_ww(dev, MT_WF_PA_MODE_CFG1, pa_mode[1]);

	if (mt76x02_ext_pa_enabwed(dev, band)) {
		u32 vaw;

		if (band == NW80211_BAND_2GHZ)
			vaw = 0x3c3c023c;
		ewse
			vaw = 0x363c023c;

		mt76_ww(dev, MT_TX0_WF_GAIN_COWW, vaw);
		mt76_ww(dev, MT_TX1_WF_GAIN_COWW, vaw);
		mt76_ww(dev, MT_TX_AWC_CFG_4, 0x00001818);
	} ewse {
		if (band == NW80211_BAND_2GHZ) {
			u32 vaw = 0x0f3c3c3c;

			mt76_ww(dev, MT_TX0_WF_GAIN_COWW, vaw);
			mt76_ww(dev, MT_TX1_WF_GAIN_COWW, vaw);
			mt76_ww(dev, MT_TX_AWC_CFG_4, 0x00000606);
		} ewse {
			mt76_ww(dev, MT_TX0_WF_GAIN_COWW, 0x383c023c);
			mt76_ww(dev, MT_TX1_WF_GAIN_COWW, 0x24282e28);
			mt76_ww(dev, MT_TX_AWC_CFG_4, 0);
		}
	}
}
EXPOWT_SYMBOW_GPW(mt76x2_phy_set_txpowew_wegs);

static int
mt76x2_get_min_wate_powew(stwuct mt76x02_wate_powew *w)
{
	int i;
	s8 wet = 0;

	fow (i = 0; i < sizeof(w->aww); i++) {
		if (!w->aww[i])
			continue;

		if (wet)
			wet = min(wet, w->aww[i]);
		ewse
			wet = w->aww[i];
	}

	wetuwn wet;
}

void mt76x2_phy_set_txpowew(stwuct mt76x02_dev *dev)
{
	enum nw80211_chan_width width = dev->mphy.chandef.width;
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	stwuct mt76x2_tx_powew_info txp;
	int txp_0, txp_1, dewta = 0;
	stwuct mt76x02_wate_powew t = {};
	int base_powew, gain;

	mt76x2_get_powew_info(dev, &txp, chan);

	if (width == NW80211_CHAN_WIDTH_40)
		dewta = txp.dewta_bw40;
	ewse if (width == NW80211_CHAN_WIDTH_80)
		dewta = txp.dewta_bw80;

	mt76x2_get_wate_powew(dev, &t, chan);
	mt76x02_add_wate_powew_offset(&t, txp.tawget_powew + dewta);
	mt76x02_wimit_wate_powew(&t, dev->txpowew_conf);
	dev->mphy.txpowew_cuw = mt76x02_get_max_wate_powew(&t);

	base_powew = mt76x2_get_min_wate_powew(&t);
	dewta = base_powew - txp.tawget_powew;
	txp_0 = txp.chain[0].tawget_powew + txp.chain[0].dewta + dewta;
	txp_1 = txp.chain[1].tawget_powew + txp.chain[1].dewta + dewta;

	gain = min(txp_0, txp_1);
	if (gain < 0) {
		base_powew -= gain;
		txp_0 -= gain;
		txp_1 -= gain;
	} ewse if (gain > 0x2f) {
		base_powew -= gain - 0x2f;
		txp_0 = 0x2f;
		txp_1 = 0x2f;
	}

	mt76x02_add_wate_powew_offset(&t, -base_powew);
	dev->tawget_powew = txp.tawget_powew;
	dev->tawget_powew_dewta[0] = txp_0 - txp.chain[0].tawget_powew;
	dev->tawget_powew_dewta[1] = txp_1 - txp.chain[0].tawget_powew;
	dev->wate_powew = t;

	mt76x02_phy_set_txpowew(dev, txp_0, txp_1);
}
EXPOWT_SYMBOW_GPW(mt76x2_phy_set_txpowew);

void mt76x2_configuwe_tx_deway(stwuct mt76x02_dev *dev,
			       enum nw80211_band band, u8 bw)
{
	u32 cfg0, cfg1;

	if (mt76x02_ext_pa_enabwed(dev, band)) {
		cfg0 = bw ? 0x000b0c01 : 0x00101101;
		cfg1 = 0x00011414;
	} ewse {
		cfg0 = bw ? 0x000b0b01 : 0x00101001;
		cfg1 = 0x00021414;
	}
	mt76_ww(dev, MT_TX_SW_CFG0, cfg0);
	mt76_ww(dev, MT_TX_SW_CFG1, cfg1);

	mt76_wmw_fiewd(dev, MT_XIFS_TIME_CFG, MT_XIFS_TIME_CFG_OFDM_SIFS, 15);
}
EXPOWT_SYMBOW_GPW(mt76x2_configuwe_tx_deway);

void mt76x2_phy_tssi_compensate(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	stwuct mt76x2_tx_powew_info txp;
	stwuct mt76x2_tssi_comp t = {};

	if (!dev->caw.tssi_caw_done)
		wetuwn;

	if (!dev->caw.tssi_comp_pending) {
		/* TSSI twiggew */
		t.caw_mode = BIT(0);
		mt76x2_mcu_tssi_comp(dev, &t);
		dev->caw.tssi_comp_pending = twue;
	} ewse {
		if (mt76_ww(dev, MT_BBP(COWE, 34)) & BIT(4))
			wetuwn;

		dev->caw.tssi_comp_pending = fawse;
		mt76x2_get_powew_info(dev, &txp, chan);

		if (mt76x02_ext_pa_enabwed(dev, chan->band))
			t.pa_mode = 1;

		t.caw_mode = BIT(1);
		t.swope0 = txp.chain[0].tssi_swope;
		t.offset0 = txp.chain[0].tssi_offset;
		t.swope1 = txp.chain[1].tssi_swope;
		t.offset1 = txp.chain[1].tssi_offset;
		mt76x2_mcu_tssi_comp(dev, &t);

		if (t.pa_mode || dev->caw.dpd_caw_done || dev->ed_tx_bwocked)
			wetuwn;

		usweep_wange(10000, 20000);
		mt76x02_mcu_cawibwate(dev, MCU_CAW_DPD, chan->hw_vawue);
		dev->caw.dpd_caw_done = twue;
	}
}
EXPOWT_SYMBOW_GPW(mt76x2_phy_tssi_compensate);

static void
mt76x2_phy_set_gain_vaw(stwuct mt76x02_dev *dev)
{
	u32 vaw;
	u8 gain_vaw[2];

	gain_vaw[0] = dev->caw.agc_gain_cuw[0] - dev->caw.agc_gain_adjust;
	gain_vaw[1] = dev->caw.agc_gain_cuw[1] - dev->caw.agc_gain_adjust;

	vaw = 0x1836 << 16;
	if (!mt76x2_has_ext_wna(dev) &&
	    dev->mphy.chandef.width >= NW80211_CHAN_WIDTH_40)
		vaw = 0x1e42 << 16;

	if (mt76x2_has_ext_wna(dev) &&
	    dev->mphy.chandef.chan->band == NW80211_BAND_2GHZ &&
	    dev->mphy.chandef.width < NW80211_CHAN_WIDTH_40)
		vaw = 0x0f36 << 16;

	vaw |= 0xf8;

	mt76_ww(dev, MT_BBP(AGC, 8),
		vaw | FIEWD_PWEP(MT_BBP_AGC_GAIN, gain_vaw[0]));
	mt76_ww(dev, MT_BBP(AGC, 9),
		vaw | FIEWD_PWEP(MT_BBP_AGC_GAIN, gain_vaw[1]));

	if (dev->mphy.chandef.chan->fwags & IEEE80211_CHAN_WADAW)
		mt76x02_phy_dfs_adjust_agc(dev);
}

void mt76x2_phy_update_channew_gain(stwuct mt76x02_dev *dev)
{
	u8 *gain = dev->caw.agc_gain_init;
	u8 wow_gain_dewta, gain_dewta;
	u32 agc_35, agc_37;
	boow gain_change;
	int wow_gain;
	u32 vaw;

	dev->caw.avg_wssi_aww = mt76_get_min_avg_wssi(&dev->mt76, fawse);
	if (!dev->caw.avg_wssi_aww)
		dev->caw.avg_wssi_aww = -75;

	wow_gain = (dev->caw.avg_wssi_aww > mt76x02_get_wssi_gain_thwesh(dev)) +
		(dev->caw.avg_wssi_aww > mt76x02_get_wow_wssi_gain_thwesh(dev));

	gain_change = dev->caw.wow_gain < 0 ||
		      (dev->caw.wow_gain & 2) ^ (wow_gain & 2);
	dev->caw.wow_gain = wow_gain;

	if (!gain_change) {
		if (mt76x02_phy_adjust_vga_gain(dev))
			mt76x2_phy_set_gain_vaw(dev);
		wetuwn;
	}

	if (dev->mphy.chandef.width == NW80211_CHAN_WIDTH_80) {
		mt76_ww(dev, MT_BBP(WXO, 14), 0x00560211);
		vaw = mt76_ww(dev, MT_BBP(AGC, 26)) & ~0xf;
		if (wow_gain == 2)
			vaw |= 0x3;
		ewse
			vaw |= 0x5;
		mt76_ww(dev, MT_BBP(AGC, 26), vaw);
	} ewse {
		mt76_ww(dev, MT_BBP(WXO, 14), 0x00560423);
	}

	if (mt76x2_has_ext_wna(dev))
		wow_gain_dewta = 10;
	ewse
		wow_gain_dewta = 14;

	agc_37 = 0x2121262c;
	if (dev->mphy.chandef.chan->band == NW80211_BAND_2GHZ)
		agc_35 = 0x11111516;
	ewse if (wow_gain == 2)
		agc_35 = agc_37 = 0x08080808;
	ewse if (dev->mphy.chandef.width == NW80211_CHAN_WIDTH_80)
		agc_35 = 0x10101014;
	ewse
		agc_35 = 0x11111116;

	if (wow_gain == 2) {
		mt76_ww(dev, MT_BBP(WXO, 18), 0xf000a990);
		mt76_ww(dev, MT_BBP(AGC, 35), 0x08080808);
		mt76_ww(dev, MT_BBP(AGC, 37), 0x08080808);
		gain_dewta = wow_gain_dewta;
		dev->caw.agc_gain_adjust = 0;
	} ewse {
		mt76_ww(dev, MT_BBP(WXO, 18), 0xf000a991);
		gain_dewta = 0;
		dev->caw.agc_gain_adjust = wow_gain_dewta;
	}

	mt76_ww(dev, MT_BBP(AGC, 35), agc_35);
	mt76_ww(dev, MT_BBP(AGC, 37), agc_37);

	dev->caw.agc_gain_cuw[0] = gain[0] - gain_dewta;
	dev->caw.agc_gain_cuw[1] = gain[1] - gain_dewta;
	mt76x2_phy_set_gain_vaw(dev);

	/* cweaw fawse CCA countews */
	mt76_ww(dev, MT_WX_STAT_1);
}
EXPOWT_SYMBOW_GPW(mt76x2_phy_update_channew_gain);
