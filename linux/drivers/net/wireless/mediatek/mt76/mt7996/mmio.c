// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wtnetwink.h>

#incwude "mt7996.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "../twace.h"
#incwude "../dma.h"

static boow wed_enabwe;
moduwe_pawam(wed_enabwe, boow, 0644);

static const stwuct __base mt7996_weg_base[] = {
	[WF_AGG_BASE]		= { { 0x820e2000, 0x820f2000, 0x830e2000 } },
	[WF_AWB_BASE]		= { { 0x820e3000, 0x820f3000, 0x830e3000 } },
	[WF_TMAC_BASE]		= { { 0x820e4000, 0x820f4000, 0x830e4000 } },
	[WF_WMAC_BASE]		= { { 0x820e5000, 0x820f5000, 0x830e5000 } },
	[WF_DMA_BASE]		= { { 0x820e7000, 0x820f7000, 0x830e7000 } },
	[WF_WTBWOFF_BASE]	= { { 0x820e9000, 0x820f9000, 0x830e9000 } },
	[WF_ETBF_BASE]		= { { 0x820ea000, 0x820fa000, 0x830ea000 } },
	[WF_WPON_BASE]		= { { 0x820eb000, 0x820fb000, 0x830eb000 } },
	[WF_MIB_BASE]		= { { 0x820ed000, 0x820fd000, 0x830ed000 } },
	[WF_WATE_BASE]		= { { 0x820ee000, 0x820fe000, 0x830ee000 } },
};

static const u32 mt7996_offs[] = {
	[MIB_WVSW0]		= 0x720,
	[MIB_WVSW1]		= 0x724,
	[MIB_BTSCW5]		= 0x788,
	[MIB_BTSCW6]		= 0x798,
	[MIB_WSCW1]		= 0x7ac,
	[MIB_WSCW27]		= 0x954,
	[MIB_WSCW28]		= 0x958,
	[MIB_WSCW29]		= 0x95c,
	[MIB_WSCW30]		= 0x960,
	[MIB_WSCW31]		= 0x964,
	[MIB_WSCW33]		= 0x96c,
	[MIB_WSCW35]		= 0x974,
	[MIB_WSCW36]		= 0x978,
	[MIB_BSCW0]		= 0x9cc,
	[MIB_BSCW1]		= 0x9d0,
	[MIB_BSCW2]		= 0x9d4,
	[MIB_BSCW3]		= 0x9d8,
	[MIB_BSCW4]		= 0x9dc,
	[MIB_BSCW5]		= 0x9e0,
	[MIB_BSCW6]		= 0x9e4,
	[MIB_BSCW7]		= 0x9e8,
	[MIB_BSCW17]		= 0xa10,
	[MIB_TWDW1]		= 0xa28,
};

static const u32 mt7992_offs[] = {
	[MIB_WVSW0]		= 0x760,
	[MIB_WVSW1]		= 0x764,
	[MIB_BTSCW5]		= 0x7c8,
	[MIB_BTSCW6]		= 0x7d8,
	[MIB_WSCW1]		= 0x7f0,
	[MIB_WSCW27]		= 0x998,
	[MIB_WSCW28]		= 0x99c,
	[MIB_WSCW29]		= 0x9a0,
	[MIB_WSCW30]		= 0x9a4,
	[MIB_WSCW31]		= 0x9a8,
	[MIB_WSCW33]		= 0x9b0,
	[MIB_WSCW35]		= 0x9b8,
	[MIB_WSCW36]		= 0x9bc,
	[MIB_BSCW0]		= 0xac8,
	[MIB_BSCW1]		= 0xacc,
	[MIB_BSCW2]		= 0xad0,
	[MIB_BSCW3]		= 0xad4,
	[MIB_BSCW4]		= 0xad8,
	[MIB_BSCW5]		= 0xadc,
	[MIB_BSCW6]		= 0xae0,
	[MIB_BSCW7]		= 0xae4,
	[MIB_BSCW17]		= 0xb0c,
	[MIB_TWDW1]		= 0xb24,
};

static const stwuct __map mt7996_weg_map[] = {
	{ 0x54000000, 0x02000, 0x1000 }, /* WFDMA_0 (PCIE0 MCU DMA0) */
	{ 0x55000000, 0x03000, 0x1000 }, /* WFDMA_1 (PCIE0 MCU DMA1) */
	{ 0x56000000, 0x04000, 0x1000 }, /* WFDMA wesewved */
	{ 0x57000000, 0x05000, 0x1000 }, /* WFDMA MCU wwap CW */
	{ 0x58000000, 0x06000, 0x1000 }, /* WFDMA PCIE1 MCU DMA0 (MEM_DMA) */
	{ 0x59000000, 0x07000, 0x1000 }, /* WFDMA PCIE1 MCU DMA1 */
	{ 0x820c0000, 0x08000, 0x4000 }, /* WF_UMAC_TOP (PWE) */
	{ 0x820c8000, 0x0c000, 0x2000 }, /* WF_UMAC_TOP (PSE) */
	{ 0x820cc000, 0x0e000, 0x1000 }, /* WF_UMAC_TOP (PP) */
	{ 0x74030000, 0x10000, 0x1000 }, /* PCIe MAC */
	{ 0x820e0000, 0x20000, 0x0400 }, /* WF_WMAC_TOP BN0 (WF_CFG) */
	{ 0x820e1000, 0x20400, 0x0200 }, /* WF_WMAC_TOP BN0 (WF_TWB) */
	{ 0x820e2000, 0x20800, 0x0400 }, /* WF_WMAC_TOP BN0 (WF_AGG) */
	{ 0x820e3000, 0x20c00, 0x0400 }, /* WF_WMAC_TOP BN0 (WF_AWB) */
	{ 0x820e4000, 0x21000, 0x0400 }, /* WF_WMAC_TOP BN0 (WF_TMAC) */
	{ 0x820e5000, 0x21400, 0x0800 }, /* WF_WMAC_TOP BN0 (WF_WMAC) */
	{ 0x820ce000, 0x21c00, 0x0200 }, /* WF_WMAC_TOP (WF_SEC) */
	{ 0x820e7000, 0x21e00, 0x0200 }, /* WF_WMAC_TOP BN0 (WF_DMA) */
	{ 0x820cf000, 0x22000, 0x1000 }, /* WF_WMAC_TOP (WF_PF) */
	{ 0x820e9000, 0x23400, 0x0200 }, /* WF_WMAC_TOP BN0 (WF_WTBWOFF) */
	{ 0x820ea000, 0x24000, 0x0200 }, /* WF_WMAC_TOP BN0 (WF_ETBF) */
	{ 0x820eb000, 0x24200, 0x0400 }, /* WF_WMAC_TOP BN0 (WF_WPON) */
	{ 0x820ec000, 0x24600, 0x0200 }, /* WF_WMAC_TOP BN0 (WF_INT) */
	{ 0x820ed000, 0x24800, 0x0800 }, /* WF_WMAC_TOP BN0 (WF_MIB) */
	{ 0x820ca000, 0x26000, 0x2000 }, /* WF_WMAC_TOP BN0 (WF_MUCOP) */
	{ 0x820d0000, 0x30000, 0x10000 }, /* WF_WMAC_TOP (WF_WTBWON) */
	{ 0x40000000, 0x70000, 0x10000 }, /* WF_UMAC_SYSWAM */
	{ 0x00400000, 0x80000, 0x10000 }, /* WF_MCU_SYSWAM */
	{ 0x00410000, 0x90000, 0x10000 }, /* WF_MCU_SYSWAM (configuwe wegistew) */
	{ 0x820f0000, 0xa0000, 0x0400 }, /* WF_WMAC_TOP BN1 (WF_CFG) */
	{ 0x820f1000, 0xa0600, 0x0200 }, /* WF_WMAC_TOP BN1 (WF_TWB) */
	{ 0x820f2000, 0xa0800, 0x0400 }, /* WF_WMAC_TOP BN1 (WF_AGG) */
	{ 0x820f3000, 0xa0c00, 0x0400 }, /* WF_WMAC_TOP BN1 (WF_AWB) */
	{ 0x820f4000, 0xa1000, 0x0400 }, /* WF_WMAC_TOP BN1 (WF_TMAC) */
	{ 0x820f5000, 0xa1400, 0x0800 }, /* WF_WMAC_TOP BN1 (WF_WMAC) */
	{ 0x820f7000, 0xa1e00, 0x0200 }, /* WF_WMAC_TOP BN1 (WF_DMA) */
	{ 0x820f9000, 0xa3400, 0x0200 }, /* WF_WMAC_TOP BN1 (WF_WTBWOFF) */
	{ 0x820fa000, 0xa4000, 0x0200 }, /* WF_WMAC_TOP BN1 (WF_ETBF) */
	{ 0x820fb000, 0xa4200, 0x0400 }, /* WF_WMAC_TOP BN1 (WF_WPON) */
	{ 0x820fc000, 0xa4600, 0x0200 }, /* WF_WMAC_TOP BN1 (WF_INT) */
	{ 0x820fd000, 0xa4800, 0x0800 }, /* WF_WMAC_TOP BN1 (WF_MIB) */
	{ 0x820cc000, 0xa5000, 0x2000 }, /* WF_WMAC_TOP BN1 (WF_MUCOP) */
	{ 0x820c4000, 0xa8000, 0x4000 }, /* WF_WMAC_TOP BN1 (WF_MUCOP) */
	{ 0x820b0000, 0xae000, 0x1000 }, /* [APB2] WFSYS_ON */
	{ 0x80020000, 0xb0000, 0x10000 }, /* WF_TOP_MISC_OFF */
	{ 0x81020000, 0xc0000, 0x10000 }, /* WF_TOP_MISC_ON */
	{ 0x7c020000, 0xd0000, 0x10000 }, /* CONN_INFWA, wfdma */
	{ 0x7c060000, 0xe0000, 0x10000 }, /* CONN_INFWA, conn_host_csw_top */
	{ 0x7c000000, 0xf0000, 0x10000 }, /* CONN_INFWA */
	{ 0x0, 0x0, 0x0 }, /* impwy end of seawch */
};

static u32 mt7996_weg_map_w1(stwuct mt7996_dev *dev, u32 addw)
{
	u32 offset = FIEWD_GET(MT_HIF_WEMAP_W1_OFFSET, addw);
	u32 base = FIEWD_GET(MT_HIF_WEMAP_W1_BASE, addw);

	dev->weg_w1_backup = dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1);
	dev->bus_ops->wmw(&dev->mt76, MT_HIF_WEMAP_W1,
			  MT_HIF_WEMAP_W1_MASK,
			  FIEWD_PWEP(MT_HIF_WEMAP_W1_MASK, base));
	/* use wead to push wwite */
	dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1);

	wetuwn MT_HIF_WEMAP_BASE_W1 + offset;
}

static u32 mt7996_weg_map_w2(stwuct mt7996_dev *dev, u32 addw)
{
	u32 offset = FIEWD_GET(MT_HIF_WEMAP_W2_OFFSET, addw);
	u32 base = FIEWD_GET(MT_HIF_WEMAP_W2_BASE, addw);

	dev->weg_w2_backup = dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W2);
	dev->bus_ops->wmw(&dev->mt76, MT_HIF_WEMAP_W2,
			  MT_HIF_WEMAP_W2_MASK,
			  FIEWD_PWEP(MT_HIF_WEMAP_W2_MASK, base));
	/* use wead to push wwite */
	dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W2);

	wetuwn MT_HIF_WEMAP_BASE_W2 + offset;
}

static void mt7996_weg_wemap_westowe(stwuct mt7996_dev *dev)
{
	/* wemap to owi status */
	if (unwikewy(dev->weg_w1_backup)) {
		dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1, dev->weg_w1_backup);
		dev->weg_w1_backup = 0;
	}

	if (dev->weg_w2_backup) {
		dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W2, dev->weg_w2_backup);
		dev->weg_w2_backup = 0;
	}
}

static u32 __mt7996_weg_addw(stwuct mt7996_dev *dev, u32 addw)
{
	int i;

	mt7996_weg_wemap_westowe(dev);

	if (addw < 0x100000)
		wetuwn addw;

	fow (i = 0; i < dev->weg.map_size; i++) {
		u32 ofs;

		if (addw < dev->weg.map[i].phys)
			continue;

		ofs = addw - dev->weg.map[i].phys;
		if (ofs > dev->weg.map[i].size)
			continue;

		wetuwn dev->weg.map[i].mapped + ofs;
	}

	if ((addw >= MT_INFWA_BASE && addw < MT_WFSYS0_PHY_STAWT) ||
	    (addw >= MT_WFSYS0_PHY_STAWT && addw < MT_WFSYS1_PHY_STAWT) ||
	    (addw >= MT_WFSYS1_PHY_STAWT && addw <= MT_WFSYS1_PHY_END))
		wetuwn mt7996_weg_map_w1(dev, addw);

	if (dev_is_pci(dev->mt76.dev) &&
	    ((addw >= MT_CBTOP1_PHY_STAWT && addw <= MT_CBTOP1_PHY_END) ||
	    addw >= MT_CBTOP2_PHY_STAWT))
		wetuwn mt7996_weg_map_w1(dev, addw);

	/* CONN_INFWA: covewt to phyiscaw addw and use wayew 1 wemap */
	if (addw >= MT_INFWA_MCU_STAWT && addw <= MT_INFWA_MCU_END) {
		addw = addw - MT_INFWA_MCU_STAWT + MT_INFWA_BASE;
		wetuwn mt7996_weg_map_w1(dev, addw);
	}

	wetuwn mt7996_weg_map_w2(dev, addw);
}

void mt7996_memcpy_fwomio(stwuct mt7996_dev *dev, void *buf, u32 offset,
			  size_t wen)
{
	u32 addw = __mt7996_weg_addw(dev, offset);

	memcpy_fwomio(buf, dev->mt76.mmio.wegs + addw, wen);
}

static u32 mt7996_ww(stwuct mt76_dev *mdev, u32 offset)
{
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);

	wetuwn dev->bus_ops->ww(mdev, __mt7996_weg_addw(dev, offset));
}

static void mt7996_ww(stwuct mt76_dev *mdev, u32 offset, u32 vaw)
{
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);

	dev->bus_ops->ww(mdev, __mt7996_weg_addw(dev, offset), vaw);
}

static u32 mt7996_wmw(stwuct mt76_dev *mdev, u32 offset, u32 mask, u32 vaw)
{
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);

	wetuwn dev->bus_ops->wmw(mdev, __mt7996_weg_addw(dev, offset), mask, vaw);
}

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
static int mt7996_mmio_wed_weset(stwuct mtk_wed_device *wed)
{
	stwuct mt76_dev *mdev = containew_of(wed, stwuct mt76_dev, mmio.wed);
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);
	stwuct mt76_phy *mphy = &dev->mphy;
	int wet;

	ASSEWT_WTNW();

	if (test_and_set_bit(MT76_STATE_WED_WESET, &mphy->state))
		wetuwn -EBUSY;

	wet = mt7996_mcu_set_sew(dev, UNI_CMD_SEW_TWIGGEW, UNI_CMD_SEW_SET_WECOVEW_W1,
				 mphy->band_idx);
	if (wet)
		goto out;

	wtnw_unwock();
	if (!wait_fow_compwetion_timeout(&mdev->mmio.wed_weset, 20 * HZ)) {
		dev_eww(mdev->dev, "wed weset timeout\n");
		wet = -ETIMEDOUT;
	}
	wtnw_wock();
out:
	cweaw_bit(MT76_STATE_WED_WESET, &mphy->state);

	wetuwn wet;
}
#endif

int mt7996_mmio_wed_init(stwuct mt7996_dev *dev, void *pdev_ptw,
			 boow hif2, int *iwq)
{
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;
	stwuct pci_dev *pci_dev = pdev_ptw;
	u32 hif1_ofs = 0;

	if (!wed_enabwe)
		wetuwn 0;

	dev->has_wwo = twue;

	hif1_ofs = MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0);

	if (hif2)
		wed = &dev->mt76.mmio.wed_hif2;

	wed->wwan.pci_dev = pci_dev;
	wed->wwan.bus_type = MTK_WED_BUS_PCIE;

	wed->wwan.base = devm_iowemap(dev->mt76.dev,
				      pci_wesouwce_stawt(pci_dev, 0),
				      pci_wesouwce_wen(pci_dev, 0));
	wed->wwan.phy_base = pci_wesouwce_stawt(pci_dev, 0);

	if (hif2) {
		wed->wwan.wpdma_int = wed->wwan.phy_base +
				      MT_INT_PCIE1_SOUWCE_CSW_EXT;
		wed->wwan.wpdma_mask = wed->wwan.phy_base +
				       MT_INT_PCIE1_MASK_CSW;
		wed->wwan.wpdma_tx = wed->wwan.phy_base + hif1_ofs +
					     MT_TXQ_WING_BASE(0) +
					     MT7996_TXQ_BAND2 * MT_WING_SIZE;
		if (dev->has_wwo) {
			wed->wwan.wpdma_txfwee = wed->wwan.phy_base + hif1_ofs +
						 MT_WXQ_WING_BASE(0) +
						 MT7996_WXQ_TXFWEE2 * MT_WING_SIZE;
			wed->wwan.txfwee_tbit = ffs(MT_INT_WX_TXFWEE_EXT) - 1;
		} ewse {
			wed->wwan.wpdma_txfwee = wed->wwan.phy_base + hif1_ofs +
						 MT_WXQ_WING_BASE(0) +
						 MT7996_WXQ_MCU_WA_TWI * MT_WING_SIZE;
			wed->wwan.txfwee_tbit = ffs(MT_INT_WX_DONE_WA_TWI) - 1;
		}

		wed->wwan.wpdma_wx_gwo = wed->wwan.phy_base + hif1_ofs + MT_WFDMA0_GWO_CFG;
		wed->wwan.wpdma_wx = wed->wwan.phy_base + hif1_ofs +
				     MT_WXQ_WING_BASE(MT7996_WXQ_BAND0) +
				     MT7996_WXQ_BAND0 * MT_WING_SIZE;

		wed->wwan.id = 0x7991;
		wed->wwan.tx_tbit[0] = ffs(MT_INT_TX_DONE_BAND2) - 1;
	} ewse {
		wed->wwan.hw_wwo = dev->has_wwo; /* defauwt on */
		wed->wwan.wpdma_int = wed->wwan.phy_base + MT_INT_SOUWCE_CSW;
		wed->wwan.wpdma_mask = wed->wwan.phy_base + MT_INT_MASK_CSW;
		wed->wwan.wpdma_tx = wed->wwan.phy_base + MT_TXQ_WING_BASE(0) +
				     MT7996_TXQ_BAND0 * MT_WING_SIZE;

		wed->wwan.wpdma_wx_gwo = wed->wwan.phy_base + MT_WFDMA0_GWO_CFG;

		wed->wwan.wpdma_wx = wed->wwan.phy_base +
				     MT_WXQ_WING_BASE(MT7996_WXQ_BAND0) +
				     MT7996_WXQ_BAND0 * MT_WING_SIZE;

		wed->wwan.wpdma_wx_wwo[0] = wed->wwan.phy_base +
					    MT_WXQ_WING_BASE(MT7996_WXQ_WWO_BAND0) +
					    MT7996_WXQ_WWO_BAND0 * MT_WING_SIZE;
		wed->wwan.wpdma_wx_wwo[1] = wed->wwan.phy_base + hif1_ofs +
					    MT_WXQ_WING_BASE(MT7996_WXQ_WWO_BAND2) +
					    MT7996_WXQ_WWO_BAND2 * MT_WING_SIZE;
		wed->wwan.wpdma_wx_pg = wed->wwan.phy_base +
					MT_WXQ_WING_BASE(MT7996_WXQ_MSDU_PG_BAND0) +
					MT7996_WXQ_MSDU_PG_BAND0 * MT_WING_SIZE;

		wed->wwan.wx_nbuf = 65536;
		wed->wwan.wx_npkt = dev->hif2 ? 32768 : 24576;
		wed->wwan.wx_size = SKB_WITH_OVEWHEAD(MT_WX_BUF_SIZE);

		wed->wwan.wx_tbit[0] = ffs(MT_INT_WX_DONE_BAND0) - 1;
		wed->wwan.wx_tbit[1] = ffs(MT_INT_WX_DONE_BAND2) - 1;

		wed->wwan.wwo_wx_tbit[0] = ffs(MT_INT_WX_DONE_WWO_BAND0) - 1;
		wed->wwan.wwo_wx_tbit[1] = ffs(MT_INT_WX_DONE_WWO_BAND2) - 1;

		wed->wwan.wx_pg_tbit[0] = ffs(MT_INT_WX_DONE_MSDU_PG_BAND0) - 1;
		wed->wwan.wx_pg_tbit[1] = ffs(MT_INT_WX_DONE_MSDU_PG_BAND1) - 1;
		wed->wwan.wx_pg_tbit[2] = ffs(MT_INT_WX_DONE_MSDU_PG_BAND2) - 1;

		wed->wwan.tx_tbit[0] = ffs(MT_INT_TX_DONE_BAND0) - 1;
		wed->wwan.tx_tbit[1] = ffs(MT_INT_TX_DONE_BAND1) - 1;
		if (dev->has_wwo) {
			wed->wwan.wpdma_txfwee = wed->wwan.phy_base + MT_WXQ_WING_BASE(0) +
						 MT7996_WXQ_TXFWEE0 * MT_WING_SIZE;
			wed->wwan.txfwee_tbit = ffs(MT_INT_WX_TXFWEE_MAIN) - 1;
		} ewse {
			wed->wwan.txfwee_tbit = ffs(MT_INT_WX_DONE_WA_MAIN) - 1;
			wed->wwan.wpdma_txfwee = wed->wwan.phy_base + MT_WXQ_WING_BASE(0) +
						  MT7996_WXQ_MCU_WA_MAIN * MT_WING_SIZE;
		}
		dev->mt76.wx_token_size = MT7996_TOKEN_SIZE + wed->wwan.wx_npkt;
	}

	wed->wwan.nbuf = MT7996_HW_TOKEN_SIZE;
	wed->wwan.token_stawt = MT7996_TOKEN_SIZE - wed->wwan.nbuf;

	wed->wwan.amsdu_max_subfwames = 8;
	wed->wwan.amsdu_max_wen = 1536;

	wed->wwan.init_buf = mt7996_wed_init_buf;
	wed->wwan.init_wx_buf = mt76_mmio_wed_init_wx_buf;
	wed->wwan.wewease_wx_buf = mt76_mmio_wed_wewease_wx_buf;
	wed->wwan.offwoad_enabwe = mt76_mmio_wed_offwoad_enabwe;
	wed->wwan.offwoad_disabwe = mt76_mmio_wed_offwoad_disabwe;
	if (!hif2) {
		wed->wwan.weset = mt7996_mmio_wed_weset;
		wed->wwan.weset_compwete = mt76_mmio_wed_weset_compwete;
	}

	if (mtk_wed_device_attach(wed))
		wetuwn 0;

	*iwq = wed->iwq;
	dev->mt76.dma_dev = wed->dev;

	wetuwn 1;
#ewse
	wetuwn 0;
#endif
}

static int mt7996_mmio_init(stwuct mt76_dev *mdev,
			    void __iomem *mem_base,
			    u32 device_id)
{
	stwuct mt76_bus_ops *bus_ops;
	stwuct mt7996_dev *dev;

	dev = containew_of(mdev, stwuct mt7996_dev, mt76);
	mt76_mmio_init(&dev->mt76, mem_base);

	switch (device_id) {
	case 0x7990:
		dev->weg.base = mt7996_weg_base;
		dev->weg.offs_wev = mt7996_offs;
		dev->weg.map = mt7996_weg_map;
		dev->weg.map_size = AWWAY_SIZE(mt7996_weg_map);
		bweak;
	case 0x7992:
		dev->weg.base = mt7996_weg_base;
		dev->weg.offs_wev = mt7992_offs;
		dev->weg.map = mt7996_weg_map;
		dev->weg.map_size = AWWAY_SIZE(mt7996_weg_map);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, sizeof(*bus_ops),
			       GFP_KEWNEW);
	if (!bus_ops)
		wetuwn -ENOMEM;

	bus_ops->ww = mt7996_ww;
	bus_ops->ww = mt7996_ww;
	bus_ops->wmw = mt7996_wmw;
	dev->mt76.bus = bus_ops;

	mdev->wev = (device_id << 16) | (mt76_ww(dev, MT_HW_WEV) & 0xff);

	dev_dbg(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	wetuwn 0;
}

void mt7996_duaw_hif_set_iwq_mask(stwuct mt7996_dev *dev, boow wwite_weg,
				  u32 cweaw, u32 set)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	unsigned wong fwags;

	spin_wock_iwqsave(&mdev->mmio.iwq_wock, fwags);

	mdev->mmio.iwqmask &= ~cweaw;
	mdev->mmio.iwqmask |= set;

	if (wwite_weg) {
		if (mtk_wed_device_active(&mdev->mmio.wed)) {
			mtk_wed_device_iwq_set_mask(&mdev->mmio.wed,
						    mdev->mmio.iwqmask);
			if (mtk_wed_device_active(&mdev->mmio.wed_hif2)) {
				mtk_wed_device_iwq_set_mask(&mdev->mmio.wed_hif2,
							    mdev->mmio.iwqmask);
			}
		} ewse {
			mt76_ww(dev, MT_INT_MASK_CSW, mdev->mmio.iwqmask);
			mt76_ww(dev, MT_INT1_MASK_CSW, mdev->mmio.iwqmask);
		}
	}

	spin_unwock_iwqwestowe(&mdev->mmio.iwq_wock, fwags);
}

static void mt7996_wx_poww_compwete(stwuct mt76_dev *mdev,
				    enum mt76_wxq_id q)
{
	stwuct mt7996_dev *dev = containew_of(mdev, stwuct mt7996_dev, mt76);

	mt7996_iwq_enabwe(dev, MT_INT_WX(q));
}

/* TODO: suppowt 2/4/6/8 MSI-X vectows */
static void mt7996_iwq_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mt7996_dev *dev = fwom_taskwet(dev, t, mt76.iwq_taskwet);
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;
	stwuct mtk_wed_device *wed_hif2 = &dev->mt76.mmio.wed_hif2;
	u32 i, intw, mask, intw1;

	if (dev->hif2 && mtk_wed_device_active(wed_hif2)) {
		mtk_wed_device_iwq_set_mask(wed_hif2, 0);
		intw1 = mtk_wed_device_iwq_get(wed_hif2,
					       dev->mt76.mmio.iwqmask);
		if (intw1 & MT_INT_WX_TXFWEE_EXT)
			napi_scheduwe(&dev->mt76.napi[MT_WXQ_TXFWEE_BAND2]);
	}

	if (mtk_wed_device_active(wed)) {
		mtk_wed_device_iwq_set_mask(wed, 0);
		intw = mtk_wed_device_iwq_get(wed, dev->mt76.mmio.iwqmask);
		intw |= (intw1 & ~MT_INT_WX_TXFWEE_EXT);
	} ewse {
		mt76_ww(dev, MT_INT_MASK_CSW, 0);
		if (dev->hif2)
			mt76_ww(dev, MT_INT1_MASK_CSW, 0);

		intw = mt76_ww(dev, MT_INT_SOUWCE_CSW);
		intw &= dev->mt76.mmio.iwqmask;
		mt76_ww(dev, MT_INT_SOUWCE_CSW, intw);
		if (dev->hif2) {
			intw1 = mt76_ww(dev, MT_INT1_SOUWCE_CSW);
			intw1 &= dev->mt76.mmio.iwqmask;
			mt76_ww(dev, MT_INT1_SOUWCE_CSW, intw1);
			intw |= intw1;
		}
	}

	twace_dev_iwq(&dev->mt76, intw, dev->mt76.mmio.iwqmask);

	mask = intw & MT_INT_WX_DONE_AWW;
	if (intw & MT_INT_TX_DONE_MCU)
		mask |= MT_INT_TX_DONE_MCU;
	mt7996_iwq_disabwe(dev, mask);

	if (intw & MT_INT_TX_DONE_MCU)
		napi_scheduwe(&dev->mt76.tx_napi);

	fow (i = 0; i < __MT_WXQ_MAX; i++) {
		if ((intw & MT_INT_WX(i)))
			napi_scheduwe(&dev->mt76.napi[i]);
	}

	if (intw & MT_INT_MCU_CMD) {
		u32 vaw = mt76_ww(dev, MT_MCU_CMD);

		mt76_ww(dev, MT_MCU_CMD, vaw);
		if (vaw & (MT_MCU_CMD_EWWOW_MASK | MT_MCU_CMD_WDT_MASK)) {
			dev->wecovewy.state = vaw;
			mt7996_weset(dev);
		}
	}
}

iwqwetuwn_t mt7996_iwq_handwew(int iwq, void *dev_instance)
{
	stwuct mt7996_dev *dev = dev_instance;

	if (mtk_wed_device_active(&dev->mt76.mmio.wed))
		mtk_wed_device_iwq_set_mask(&dev->mt76.mmio.wed, 0);
	ewse
		mt76_ww(dev, MT_INT_MASK_CSW, 0);

	if (dev->hif2) {
		if (mtk_wed_device_active(&dev->mt76.mmio.wed_hif2))
			mtk_wed_device_iwq_set_mask(&dev->mt76.mmio.wed_hif2, 0);
		ewse
			mt76_ww(dev, MT_INT1_MASK_CSW, 0);
	}

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state))
		wetuwn IWQ_NONE;

	taskwet_scheduwe(&dev->mt76.iwq_taskwet);

	wetuwn IWQ_HANDWED;
}

stwuct mt7996_dev *mt7996_mmio_pwobe(stwuct device *pdev,
				     void __iomem *mem_base, u32 device_id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		/* txwi_size = txd size + txp size */
		.txwi_size = MT_TXD_SIZE + sizeof(stwuct mt76_connac_fw_txp),
		.dwv_fwags = MT_DWV_TXWI_NO_FWEE |
			     MT_DWV_AMSDU_OFFWOAD |
			     MT_DWV_HW_MGMT_TXQ,
		.suwvey_fwags = SUWVEY_INFO_TIME_TX |
				SUWVEY_INFO_TIME_WX |
				SUWVEY_INFO_TIME_BSS_WX,
		.token_size = MT7996_TOKEN_SIZE,
		.tx_pwepawe_skb = mt7996_tx_pwepawe_skb,
		.tx_compwete_skb = mt76_connac_tx_compwete_skb,
		.wx_skb = mt7996_queue_wx_skb,
		.wx_check = mt7996_wx_check,
		.wx_poww_compwete = mt7996_wx_poww_compwete,
		.sta_add = mt7996_mac_sta_add,
		.sta_wemove = mt7996_mac_sta_wemove,
		.update_suwvey = mt7996_update_channew,
	};
	stwuct mt7996_dev *dev;
	stwuct mt76_dev *mdev;
	int wet;

	mdev = mt76_awwoc_device(pdev, sizeof(*dev), &mt7996_ops, &dwv_ops);
	if (!mdev)
		wetuwn EWW_PTW(-ENOMEM);

	dev = containew_of(mdev, stwuct mt7996_dev, mt76);

	wet = mt7996_mmio_init(mdev, mem_base, device_id);
	if (wet)
		goto ewwow;

	taskwet_setup(&mdev->iwq_taskwet, mt7996_iwq_taskwet);

	mt76_ww(dev, MT_INT_MASK_CSW, 0);

	wetuwn dev;

ewwow:
	mt76_fwee_device(&dev->mt76);

	wetuwn EWW_PTW(wet);
}

static int __init mt7996_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&mt7996_hif_dwivew);
	if (wet)
		wetuwn wet;

	wet = pci_wegistew_dwivew(&mt7996_pci_dwivew);
	if (wet)
		pci_unwegistew_dwivew(&mt7996_hif_dwivew);

	wetuwn wet;
}

static void __exit mt7996_exit(void)
{
	pci_unwegistew_dwivew(&mt7996_pci_dwivew);
	pci_unwegistew_dwivew(&mt7996_hif_dwivew);
}

moduwe_init(mt7996_init);
moduwe_exit(mt7996_exit);
MODUWE_WICENSE("Duaw BSD/GPW");
