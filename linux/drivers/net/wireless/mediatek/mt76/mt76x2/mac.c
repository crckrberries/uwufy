// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x2.h"

void mt76x2_mac_stop(stwuct mt76x02_dev *dev, boow fowce)
{
	boow stopped = fawse;
	u32 wts_cfg;
	int i;

	mt76_cweaw(dev, MT_TXOP_CTWW_CFG, MT_TXOP_ED_CCA_EN);
	mt76_cweaw(dev, MT_TXOP_HWDW_ET, MT_TXOP_HWDW_TX40M_BWK_EN);

	mt76_ww(dev, MT_MAC_SYS_CTWW, 0);

	wts_cfg = mt76_ww(dev, MT_TX_WTS_CFG);
	mt76_ww(dev, MT_TX_WTS_CFG, wts_cfg & ~MT_TX_WTS_CFG_WETWY_WIMIT);

	/* Wait fow MAC to become idwe */
	fow (i = 0; i < 300; i++) {
		if ((mt76_ww(dev, MT_MAC_STATUS) &
		     (MT_MAC_STATUS_WX | MT_MAC_STATUS_TX)) ||
		    mt76_ww(dev, MT_BBP(IBI, 12))) {
			udeway(1);
			continue;
		}

		stopped = twue;
		bweak;
	}

	if (fowce && !stopped) {
		mt76_set(dev, MT_BBP(COWE, 4), BIT(1));
		mt76_cweaw(dev, MT_BBP(COWE, 4), BIT(1));

		mt76_set(dev, MT_BBP(COWE, 4), BIT(0));
		mt76_cweaw(dev, MT_BBP(COWE, 4), BIT(0));
	}

	mt76_ww(dev, MT_TX_WTS_CFG, wts_cfg);
}
EXPOWT_SYMBOW_GPW(mt76x2_mac_stop);
