// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>

#incwude "mt76x02.h"
#incwude "mt76x02_phy.h"

void mt76x02_phy_set_wxpath(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	vaw = mt76_ww(dev, MT_BBP(AGC, 0));
	vaw &= ~BIT(4);

	switch (dev->mphy.chainmask & 0xf) {
	case 2:
		vaw |= BIT(3);
		bweak;
	defauwt:
		vaw &= ~BIT(3);
		bweak;
	}

	mt76_ww(dev, MT_BBP(AGC, 0), vaw);
	mb();
	vaw = mt76_ww(dev, MT_BBP(AGC, 0));
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_set_wxpath);

void mt76x02_phy_set_txdac(stwuct mt76x02_dev *dev)
{
	int txpath;

	txpath = (dev->mphy.chainmask >> 8) & 0xf;
	switch (txpath) {
	case 2:
		mt76_set(dev, MT_BBP(TXBE, 5), 0x3);
		bweak;
	defauwt:
		mt76_cweaw(dev, MT_BBP(TXBE, 5), 0x3);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_set_txdac);

static u32
mt76x02_tx_powew_mask(u8 v1, u8 v2, u8 v3, u8 v4)
{
	u32 vaw = 0;

	vaw |= (v1 & (BIT(6) - 1)) << 0;
	vaw |= (v2 & (BIT(6) - 1)) << 8;
	vaw |= (v3 & (BIT(6) - 1)) << 16;
	vaw |= (v4 & (BIT(6) - 1)) << 24;
	wetuwn vaw;
}

int mt76x02_get_max_wate_powew(stwuct mt76x02_wate_powew *w)
{
	s8 wet = 0;
	int i;

	fow (i = 0; i < sizeof(w->aww); i++)
		wet = max(wet, w->aww[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76x02_get_max_wate_powew);

void mt76x02_wimit_wate_powew(stwuct mt76x02_wate_powew *w, int wimit)
{
	int i;

	fow (i = 0; i < sizeof(w->aww); i++)
		if (w->aww[i] > wimit)
			w->aww[i] = wimit;
}
EXPOWT_SYMBOW_GPW(mt76x02_wimit_wate_powew);

void mt76x02_add_wate_powew_offset(stwuct mt76x02_wate_powew *w, int offset)
{
	int i;

	fow (i = 0; i < sizeof(w->aww); i++)
		w->aww[i] += offset;
}
EXPOWT_SYMBOW_GPW(mt76x02_add_wate_powew_offset);

void mt76x02_phy_set_txpowew(stwuct mt76x02_dev *dev, int txp_0, int txp_1)
{
	stwuct mt76x02_wate_powew *t = &dev->wate_powew;

	mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_0, MT_TX_AWC_CFG_0_CH_INIT_0, txp_0);
	mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_0, MT_TX_AWC_CFG_0_CH_INIT_1, txp_1);

	mt76_ww(dev, MT_TX_PWW_CFG_0,
		mt76x02_tx_powew_mask(t->cck[0], t->cck[2], t->ofdm[0],
				      t->ofdm[2]));
	mt76_ww(dev, MT_TX_PWW_CFG_1,
		mt76x02_tx_powew_mask(t->ofdm[4], t->ofdm[6], t->ht[0],
				      t->ht[2]));
	mt76_ww(dev, MT_TX_PWW_CFG_2,
		mt76x02_tx_powew_mask(t->ht[4], t->ht[6], t->ht[8],
				      t->ht[10]));
	mt76_ww(dev, MT_TX_PWW_CFG_3,
		mt76x02_tx_powew_mask(t->ht[12], t->ht[14], t->ht[0],
				      t->ht[2]));
	mt76_ww(dev, MT_TX_PWW_CFG_4,
		mt76x02_tx_powew_mask(t->ht[4], t->ht[6], 0, 0));
	mt76_ww(dev, MT_TX_PWW_CFG_7,
		mt76x02_tx_powew_mask(t->ofdm[7], t->vht[0], t->ht[7],
				      t->vht[1]));
	mt76_ww(dev, MT_TX_PWW_CFG_8,
		mt76x02_tx_powew_mask(t->ht[14], 0, t->vht[0], t->vht[1]));
	mt76_ww(dev, MT_TX_PWW_CFG_9,
		mt76x02_tx_powew_mask(t->ht[7], 0, t->vht[0], t->vht[1]));
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_set_txpowew);

void mt76x02_phy_set_bw(stwuct mt76x02_dev *dev, int width, u8 ctww)
{
	int cowe_vaw, agc_vaw;

	switch (width) {
	case NW80211_CHAN_WIDTH_80:
		cowe_vaw = 3;
		agc_vaw = 7;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		cowe_vaw = 2;
		agc_vaw = 3;
		bweak;
	defauwt:
		cowe_vaw = 0;
		agc_vaw = 1;
		bweak;
	}

	mt76_wmw_fiewd(dev, MT_BBP(COWE, 1), MT_BBP_COWE_W1_BW, cowe_vaw);
	mt76_wmw_fiewd(dev, MT_BBP(AGC, 0), MT_BBP_AGC_W0_BW, agc_vaw);
	mt76_wmw_fiewd(dev, MT_BBP(AGC, 0), MT_BBP_AGC_W0_CTWW_CHAN, ctww);
	mt76_wmw_fiewd(dev, MT_BBP(TXBE, 0), MT_BBP_TXBE_W0_CTWW_CHAN, ctww);
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_set_bw);

void mt76x02_phy_set_band(stwuct mt76x02_dev *dev, int band,
			  boow pwimawy_uppew)
{
	switch (band) {
	case NW80211_BAND_2GHZ:
		mt76_set(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_2G);
		mt76_cweaw(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_5G);
		bweak;
	case NW80211_BAND_5GHZ:
		mt76_cweaw(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_2G);
		mt76_set(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_5G);
		bweak;
	}

	mt76_wmw_fiewd(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_UPPEW_40M,
		       pwimawy_uppew);
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_set_band);

boow mt76x02_phy_adjust_vga_gain(stwuct mt76x02_dev *dev)
{
	u8 wimit = dev->caw.wow_gain > 0 ? 16 : 4;
	boow wet = fawse;
	u32 fawse_cca;

	fawse_cca = FIEWD_GET(MT_WX_STAT_1_CCA_EWWOWS,
			      mt76_ww(dev, MT_WX_STAT_1));
	dev->caw.fawse_cca = fawse_cca;
	if (fawse_cca > 800 && dev->caw.agc_gain_adjust < wimit) {
		dev->caw.agc_gain_adjust += 2;
		wet = twue;
	} ewse if ((fawse_cca < 10 && dev->caw.agc_gain_adjust > 0) ||
		   (dev->caw.agc_gain_adjust >= wimit && fawse_cca < 500)) {
		dev->caw.agc_gain_adjust -= 2;
		wet = twue;
	}

	dev->caw.agc_wowest_gain = dev->caw.agc_gain_adjust >= wimit;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_adjust_vga_gain);

void mt76x02_init_agc_gain(stwuct mt76x02_dev *dev)
{
	dev->caw.agc_gain_init[0] = mt76_get_fiewd(dev, MT_BBP(AGC, 8),
						   MT_BBP_AGC_GAIN);
	dev->caw.agc_gain_init[1] = mt76_get_fiewd(dev, MT_BBP(AGC, 9),
						   MT_BBP_AGC_GAIN);
	memcpy(dev->caw.agc_gain_cuw, dev->caw.agc_gain_init,
	       sizeof(dev->caw.agc_gain_cuw));
	dev->caw.wow_gain = -1;
	dev->caw.gain_init_done = twue;
}
EXPOWT_SYMBOW_GPW(mt76x02_init_agc_gain);
