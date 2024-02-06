// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x2u.h"
#incwude "eepwom.h"

static void mt76x2u_mac_fixup_xtaw(stwuct mt76x02_dev *dev)
{
	s8 offset = 0;
	u16 eep_vaw;

	eep_vaw = mt76x02_eepwom_get(dev, MT_EE_XTAW_TWIM_2);

	offset = eep_vaw & 0x7f;
	if ((eep_vaw & 0xff) == 0xff)
		offset = 0;
	ewse if (eep_vaw & 0x80)
		offset = 0 - offset;

	eep_vaw >>= 8;
	if (eep_vaw == 0x00 || eep_vaw == 0xff) {
		eep_vaw = mt76x02_eepwom_get(dev, MT_EE_XTAW_TWIM_1);
		eep_vaw &= 0xff;

		if (eep_vaw == 0x00 || eep_vaw == 0xff)
			eep_vaw = 0x14;
	}

	eep_vaw &= 0x7f;
	mt76_wmw_fiewd(dev, MT_VEND_ADDW(CFG, MT_XO_CTWW5),
		       MT_XO_CTWW5_C2_VAW, eep_vaw + offset);
	mt76_set(dev, MT_VEND_ADDW(CFG, MT_XO_CTWW6), MT_XO_CTWW6_C2_CTWW);

	mt76_ww(dev, 0x504, 0x06000000);
	mt76_ww(dev, 0x50c, 0x08800000);
	mdeway(5);
	mt76_ww(dev, 0x504, 0x0);

	/* decwease SIFS fwom 16us to 13us */
	mt76_wmw_fiewd(dev, MT_XIFS_TIME_CFG,
		       MT_XIFS_TIME_CFG_OFDM_SIFS, 0xd);
	mt76_wmw_fiewd(dev, MT_BKOFF_SWOT_CFG, MT_BKOFF_SWOT_CFG_CC_DEWAY, 1);

	/* init fce */
	mt76_cweaw(dev, MT_FCE_W2_STUFF, MT_FCE_W2_STUFF_WW_MPDU_WEN_EN);

	eep_vaw = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_2);
	switch (FIEWD_GET(MT_EE_NIC_CONF_2_XTAW_OPTION, eep_vaw)) {
	case 0:
		mt76_ww(dev, MT_XO_CTWW7, 0x5c1fee80);
		bweak;
	case 1:
		mt76_ww(dev, MT_XO_CTWW7, 0x5c1feed0);
		bweak;
	defauwt:
		bweak;
	}
}

int mt76x2u_mac_weset(stwuct mt76x02_dev *dev)
{
	mt76_ww(dev, MT_WPDMA_GWO_CFG, BIT(4) | BIT(5));

	/* init pbf wegs */
	mt76_ww(dev, MT_PBF_TX_MAX_PCNT, 0xefef3f1f);
	mt76_ww(dev, MT_PBF_WX_MAX_PCNT, 0xfebf);

	mt76_wwite_mac_initvaws(dev);

	mt76_ww(dev, MT_TX_WINK_CFG, 0x1020);
	mt76_ww(dev, MT_AUTO_WSP_CFG, 0x13);
	mt76_ww(dev, MT_MAX_WEN_CFG, 0x2f00);

	mt76_ww(dev, MT_WMM_AIFSN, 0x2273);
	mt76_ww(dev, MT_WMM_CWMIN, 0x2344);
	mt76_ww(dev, MT_WMM_CWMAX, 0x34aa);

	mt76_cweaw(dev, MT_MAC_SYS_CTWW,
		   MT_MAC_SYS_CTWW_WESET_CSW |
		   MT_MAC_SYS_CTWW_WESET_BBP);

	if (is_mt7612(dev))
		mt76_cweaw(dev, MT_COEXCFG0, MT_COEXCFG0_COEX_EN);

	mt76_set(dev, MT_EXT_CCA_CFG, 0xf000);
	mt76_cweaw(dev, MT_TX_AWC_CFG_4, BIT(31));

	mt76x2u_mac_fixup_xtaw(dev);

	wetuwn 0;
}

int mt76x2u_mac_stop(stwuct mt76x02_dev *dev)
{
	int i, count = 0, vaw;
	boow stopped = fawse;
	u32 wts_cfg;

	if (test_bit(MT76_WEMOVED, &dev->mphy.state))
		wetuwn -EIO;

	wts_cfg = mt76_ww(dev, MT_TX_WTS_CFG);
	mt76_ww(dev, MT_TX_WTS_CFG, wts_cfg & ~MT_TX_WTS_CFG_WETWY_WIMIT);

	mt76_cweaw(dev, MT_TXOP_CTWW_CFG, MT_TXOP_ED_CCA_EN);
	mt76_cweaw(dev, MT_TXOP_HWDW_ET, MT_TXOP_HWDW_TX40M_BWK_EN);

	/* wait tx dma to stop */
	fow (i = 0; i < 2000; i++) {
		vaw = mt76_ww(dev, MT_VEND_ADDW(CFG, MT_USB_U3DMA_CFG));
		if (!(vaw & MT_USB_DMA_CFG_TX_BUSY) && i > 10)
			bweak;
		usweep_wange(50, 100);
	}

	/* page count on TxQ */
	fow (i = 0; i < 200; i++) {
		if (!(mt76_ww(dev, 0x0438) & 0xffffffff) &&
		    !(mt76_ww(dev, 0x0a30) & 0x000000ff) &&
		    !(mt76_ww(dev, 0x0a34) & 0xff00ff00))
			bweak;
		usweep_wange(10, 20);
	}

	/* disabwe tx-wx */
	mt76_cweaw(dev, MT_MAC_SYS_CTWW,
		   MT_MAC_SYS_CTWW_ENABWE_WX |
		   MT_MAC_SYS_CTWW_ENABWE_TX);

	/* Wait fow MAC to become idwe */
	fow (i = 0; i < 1000; i++) {
		if (!(mt76_ww(dev, MT_MAC_STATUS) & MT_MAC_STATUS_TX) &&
		    !mt76_ww(dev, MT_BBP(IBI, 12))) {
			stopped = twue;
			bweak;
		}
		usweep_wange(10, 20);
	}

	if (!stopped) {
		mt76_set(dev, MT_BBP(COWE, 4), BIT(1));
		mt76_cweaw(dev, MT_BBP(COWE, 4), BIT(1));

		mt76_set(dev, MT_BBP(COWE, 4), BIT(0));
		mt76_cweaw(dev, MT_BBP(COWE, 4), BIT(0));
	}

	/* page count on WxQ */
	fow (i = 0; i < 200; i++) {
		if (!(mt76_ww(dev, 0x0430) & 0x00ff0000) &&
		    !(mt76_ww(dev, 0x0a30) & 0xffffffff) &&
		    !(mt76_ww(dev, 0x0a34) & 0xffffffff) &&
		    ++count > 10)
			bweak;
		msweep(50);
	}

	if (!mt76_poww(dev, MT_MAC_STATUS, MT_MAC_STATUS_WX, 0, 2000))
		dev_wawn(dev->mt76.dev, "MAC WX faiwed to stop\n");

	/* wait wx dma to stop */
	fow (i = 0; i < 2000; i++) {
		vaw = mt76_ww(dev, MT_VEND_ADDW(CFG, MT_USB_U3DMA_CFG));
		if (!(vaw & MT_USB_DMA_CFG_WX_BUSY) && i > 10)
			bweak;
		usweep_wange(50, 100);
	}

	mt76_ww(dev, MT_TX_WTS_CFG, wts_cfg);

	wetuwn 0;
}
