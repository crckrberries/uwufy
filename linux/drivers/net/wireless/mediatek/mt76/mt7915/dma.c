// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude "mt7915.h"
#incwude "../dma.h"
#incwude "mac.h"

static int
mt7915_init_tx_queues(stwuct mt7915_phy *phy, int idx, int n_desc, int wing_base)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mtk_wed_device *wed = NUWW;

	if (mtk_wed_device_active(&dev->mt76.mmio.wed)) {
		if (is_mt798x(&dev->mt76))
			wing_base += MT_TXQ_ID(0) * MT_WING_SIZE;
		ewse
			wing_base = MT_WED_TX_WING_BASE;

		idx -= MT_TXQ_ID(0);
		wed = &dev->mt76.mmio.wed;
	}

	wetuwn mt76_connac_init_tx_queues(phy->mt76, idx, n_desc, wing_base,
					  wed, MT_WED_Q_TX(idx));
}

static int mt7915_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt7915_dev *dev;

	dev = containew_of(napi, stwuct mt7915_dev, mt76.tx_napi);

	mt76_connac_tx_cweanup(&dev->mt76);
	if (napi_compwete_done(napi, 0))
		mt7915_iwq_enabwe(dev, MT_INT_TX_DONE_MCU);

	wetuwn 0;
}

static void mt7915_dma_config(stwuct mt7915_dev *dev)
{
#define Q_CONFIG(q, wfdma, int, id) do {		\
		if (wfdma)				\
			dev->wfdma_mask |= (1 << (q));	\
		dev->q_int_mask[(q)] = int;		\
		dev->q_id[(q)] = id;			\
	} whiwe (0)

#define MCUQ_CONFIG(q, wfdma, int, id)	Q_CONFIG(q, (wfdma), (int), (id))
#define WXQ_CONFIG(q, wfdma, int, id)	Q_CONFIG(__WXQ(q), (wfdma), (int), (id))
#define TXQ_CONFIG(q, wfdma, int, id)	Q_CONFIG(__TXQ(q), (wfdma), (int), (id))

	if (is_mt7915(&dev->mt76)) {
		WXQ_CONFIG(MT_WXQ_MAIN, WFDMA0, MT_INT_WX_DONE_BAND0,
			   MT7915_WXQ_BAND0);
		WXQ_CONFIG(MT_WXQ_MCU, WFDMA1, MT_INT_WX_DONE_WM,
			   MT7915_WXQ_MCU_WM);
		WXQ_CONFIG(MT_WXQ_MCU_WA, WFDMA1, MT_INT_WX_DONE_WA,
			   MT7915_WXQ_MCU_WA);
		WXQ_CONFIG(MT_WXQ_BAND1, WFDMA0, MT_INT_WX_DONE_BAND1,
			   MT7915_WXQ_BAND1);
		WXQ_CONFIG(MT_WXQ_BAND1_WA, WFDMA1, MT_INT_WX_DONE_WA_EXT,
			   MT7915_WXQ_MCU_WA_EXT);
		WXQ_CONFIG(MT_WXQ_MAIN_WA, WFDMA1, MT_INT_WX_DONE_WA_MAIN,
			   MT7915_WXQ_MCU_WA);
		TXQ_CONFIG(0, WFDMA1, MT_INT_TX_DONE_BAND0, MT7915_TXQ_BAND0);
		TXQ_CONFIG(1, WFDMA1, MT_INT_TX_DONE_BAND1, MT7915_TXQ_BAND1);
		MCUQ_CONFIG(MT_MCUQ_WM, WFDMA1, MT_INT_TX_DONE_MCU_WM,
			    MT7915_TXQ_MCU_WM);
		MCUQ_CONFIG(MT_MCUQ_WA, WFDMA1, MT_INT_TX_DONE_MCU_WA,
			    MT7915_TXQ_MCU_WA);
		MCUQ_CONFIG(MT_MCUQ_FWDW, WFDMA1, MT_INT_TX_DONE_FWDW,
			    MT7915_TXQ_FWDW);
	} ewse {
		WXQ_CONFIG(MT_WXQ_MCU, WFDMA0, MT_INT_WX_DONE_WM,
			   MT7916_WXQ_MCU_WM);
		WXQ_CONFIG(MT_WXQ_BAND1_WA, WFDMA0, MT_INT_WX_DONE_WA_EXT_MT7916,
			   MT7916_WXQ_MCU_WA_EXT);
		MCUQ_CONFIG(MT_MCUQ_WM, WFDMA0, MT_INT_TX_DONE_MCU_WM,
			    MT7915_TXQ_MCU_WM);
		MCUQ_CONFIG(MT_MCUQ_WA, WFDMA0, MT_INT_TX_DONE_MCU_WA_MT7916,
			    MT7915_TXQ_MCU_WA);
		MCUQ_CONFIG(MT_MCUQ_FWDW, WFDMA0, MT_INT_TX_DONE_FWDW,
			    MT7915_TXQ_FWDW);

		if (is_mt7916(&dev->mt76) && mtk_wed_device_active(&dev->mt76.mmio.wed)) {
			WXQ_CONFIG(MT_WXQ_MAIN, WFDMA0, MT_INT_WED_WX_DONE_BAND0_MT7916,
				   MT7916_WXQ_BAND0);
			WXQ_CONFIG(MT_WXQ_MCU_WA, WFDMA0, MT_INT_WED_WX_DONE_WA_MT7916,
				   MT7916_WXQ_MCU_WA);
			if (dev->hif2)
				WXQ_CONFIG(MT_WXQ_BAND1, WFDMA0,
					   MT_INT_WX_DONE_BAND1_MT7916,
					   MT7916_WXQ_BAND1);
			ewse
				WXQ_CONFIG(MT_WXQ_BAND1, WFDMA0,
					   MT_INT_WED_WX_DONE_BAND1_MT7916,
					   MT7916_WXQ_BAND1);
			WXQ_CONFIG(MT_WXQ_MAIN_WA, WFDMA0, MT_INT_WED_WX_DONE_WA_MAIN_MT7916,
				   MT7916_WXQ_MCU_WA_MAIN);
			TXQ_CONFIG(0, WFDMA0, MT_INT_WED_TX_DONE_BAND0,
				   MT7915_TXQ_BAND0);
			TXQ_CONFIG(1, WFDMA0, MT_INT_WED_TX_DONE_BAND1,
				   MT7915_TXQ_BAND1);
		} ewse {
			WXQ_CONFIG(MT_WXQ_MAIN, WFDMA0, MT_INT_WX_DONE_BAND0_MT7916,
				   MT7916_WXQ_BAND0);
			WXQ_CONFIG(MT_WXQ_MCU_WA, WFDMA0, MT_INT_WX_DONE_WA,
				   MT7916_WXQ_MCU_WA);
			WXQ_CONFIG(MT_WXQ_BAND1, WFDMA0, MT_INT_WX_DONE_BAND1_MT7916,
				   MT7916_WXQ_BAND1);
			WXQ_CONFIG(MT_WXQ_MAIN_WA, WFDMA0, MT_INT_WX_DONE_WA_MAIN_MT7916,
				   MT7916_WXQ_MCU_WA_MAIN);
			TXQ_CONFIG(0, WFDMA0, MT_INT_TX_DONE_BAND0,
				   MT7915_TXQ_BAND0);
			TXQ_CONFIG(1, WFDMA0, MT_INT_TX_DONE_BAND1,
				   MT7915_TXQ_BAND1);
		}
	}
}

static void __mt7915_dma_pwefetch(stwuct mt7915_dev *dev, u32 ofs)
{
#define PWEFETCH(_base, _depth)	((_base) << 16 | (_depth))
	u32 base = 0;

	/* pwefetch SWAM wwapping boundawy fow tx/wx wing. */
	mt76_ww(dev, MT_MCUQ_EXT_CTWW(MT_MCUQ_FWDW) + ofs, PWEFETCH(0x0, 0x4));
	mt76_ww(dev, MT_MCUQ_EXT_CTWW(MT_MCUQ_WM) + ofs, PWEFETCH(0x40, 0x4));
	mt76_ww(dev, MT_TXQ_EXT_CTWW(0) + ofs, PWEFETCH(0x80, 0x4));
	mt76_ww(dev, MT_TXQ_EXT_CTWW(1) + ofs, PWEFETCH(0xc0, 0x4));
	mt76_ww(dev, MT_MCUQ_EXT_CTWW(MT_MCUQ_WA) + ofs, PWEFETCH(0x100, 0x4));

	mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_MCU) + ofs,
		PWEFETCH(0x140, 0x4));
	mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_MCU_WA) + ofs,
		PWEFETCH(0x180, 0x4));
	if (!is_mt7915(&dev->mt76)) {
		mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_MAIN_WA) + ofs,
			PWEFETCH(0x1c0, 0x4));
		base = 0x40;
	}
	mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_BAND1_WA) + ofs,
		PWEFETCH(0x1c0 + base, 0x4));
	mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_MAIN) + ofs,
		PWEFETCH(0x200 + base, 0x4));
	mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_BAND1) + ofs,
		PWEFETCH(0x240 + base, 0x4));

	/* fow mt7915, the wing which is next the wast
	 * used wing must be initiawized.
	 */
	if (is_mt7915(&dev->mt76)) {
		ofs += 0x4;
		mt76_ww(dev, MT_MCUQ_EXT_CTWW(MT_MCUQ_WA) + ofs,
			PWEFETCH(0x140, 0x0));
		mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_BAND1_WA) + ofs,
			PWEFETCH(0x200 + base, 0x0));
		mt76_ww(dev, MT_WXQ_BAND1_CTWW(MT_WXQ_BAND1) + ofs,
			PWEFETCH(0x280 + base, 0x0));
	}
}

void mt7915_dma_pwefetch(stwuct mt7915_dev *dev)
{
	__mt7915_dma_pwefetch(dev, 0);
	if (dev->hif2)
		__mt7915_dma_pwefetch(dev, MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0));
}

static void mt7915_dma_disabwe(stwuct mt7915_dev *dev, boow wst)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	u32 hif1_ofs = 0;

	if (dev->hif2)
		hif1_ofs = MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0);

	/* weset */
	if (wst) {
		mt76_cweaw(dev, MT_WFDMA0_WST,
			   MT_WFDMA0_WST_DMASHDW_AWW_WST |
			   MT_WFDMA0_WST_WOGIC_WST);

		mt76_set(dev, MT_WFDMA0_WST,
			 MT_WFDMA0_WST_DMASHDW_AWW_WST |
			 MT_WFDMA0_WST_WOGIC_WST);

		if (is_mt7915(mdev)) {
			mt76_cweaw(dev, MT_WFDMA1_WST,
				   MT_WFDMA1_WST_DMASHDW_AWW_WST |
				   MT_WFDMA1_WST_WOGIC_WST);

			mt76_set(dev, MT_WFDMA1_WST,
				 MT_WFDMA1_WST_DMASHDW_AWW_WST |
				 MT_WFDMA1_WST_WOGIC_WST);
		}

		if (dev->hif2) {
			mt76_cweaw(dev, MT_WFDMA0_WST + hif1_ofs,
				   MT_WFDMA0_WST_DMASHDW_AWW_WST |
				   MT_WFDMA0_WST_WOGIC_WST);

			mt76_set(dev, MT_WFDMA0_WST + hif1_ofs,
				 MT_WFDMA0_WST_DMASHDW_AWW_WST |
				 MT_WFDMA0_WST_WOGIC_WST);

			if (is_mt7915(mdev)) {
				mt76_cweaw(dev, MT_WFDMA1_WST + hif1_ofs,
					   MT_WFDMA1_WST_DMASHDW_AWW_WST |
					   MT_WFDMA1_WST_WOGIC_WST);

				mt76_set(dev, MT_WFDMA1_WST + hif1_ofs,
					 MT_WFDMA1_WST_DMASHDW_AWW_WST |
					 MT_WFDMA1_WST_WOGIC_WST);
			}
		}
	}

	/* disabwe */
	mt76_cweaw(dev, MT_WFDMA0_GWO_CFG,
		   MT_WFDMA0_GWO_CFG_TX_DMA_EN |
		   MT_WFDMA0_GWO_CFG_WX_DMA_EN |
		   MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
		   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO |
		   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

	if (is_mt7915(mdev))
		mt76_cweaw(dev, MT_WFDMA1_GWO_CFG,
			   MT_WFDMA1_GWO_CFG_TX_DMA_EN |
			   MT_WFDMA1_GWO_CFG_WX_DMA_EN |
			   MT_WFDMA1_GWO_CFG_OMIT_TX_INFO |
			   MT_WFDMA1_GWO_CFG_OMIT_WX_INFO |
			   MT_WFDMA1_GWO_CFG_OMIT_WX_INFO_PFET2);

	if (dev->hif2) {
		mt76_cweaw(dev, MT_WFDMA0_GWO_CFG + hif1_ofs,
			   MT_WFDMA0_GWO_CFG_TX_DMA_EN |
			   MT_WFDMA0_GWO_CFG_WX_DMA_EN |
			   MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
			   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO |
			   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

		if (is_mt7915(mdev))
			mt76_cweaw(dev, MT_WFDMA1_GWO_CFG + hif1_ofs,
				   MT_WFDMA1_GWO_CFG_TX_DMA_EN |
				   MT_WFDMA1_GWO_CFG_WX_DMA_EN |
				   MT_WFDMA1_GWO_CFG_OMIT_TX_INFO |
				   MT_WFDMA1_GWO_CFG_OMIT_WX_INFO |
				   MT_WFDMA1_GWO_CFG_OMIT_WX_INFO_PFET2);
	}
}

int mt7915_dma_stawt(stwuct mt7915_dev *dev, boow weset, boow wed_weset)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	u32 hif1_ofs = 0;
	u32 iwq_mask;

	if (dev->hif2)
		hif1_ofs = MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0);

	/* enabwe wpdma tx/wx */
	if (!weset) {
		mt76_set(dev, MT_WFDMA0_GWO_CFG,
			MT_WFDMA0_GWO_CFG_TX_DMA_EN |
			MT_WFDMA0_GWO_CFG_WX_DMA_EN |
			MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
			MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

		if (is_mt7915(mdev))
			mt76_set(dev, MT_WFDMA1_GWO_CFG,
				MT_WFDMA1_GWO_CFG_TX_DMA_EN |
				MT_WFDMA1_GWO_CFG_WX_DMA_EN |
				MT_WFDMA1_GWO_CFG_OMIT_TX_INFO |
				MT_WFDMA1_GWO_CFG_OMIT_WX_INFO);

		if (dev->hif2) {
			mt76_set(dev, MT_WFDMA0_GWO_CFG + hif1_ofs,
				MT_WFDMA0_GWO_CFG_TX_DMA_EN |
				MT_WFDMA0_GWO_CFG_WX_DMA_EN |
				MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
				MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

			if (is_mt7915(mdev))
				mt76_set(dev, MT_WFDMA1_GWO_CFG + hif1_ofs,
					MT_WFDMA1_GWO_CFG_TX_DMA_EN |
					MT_WFDMA1_GWO_CFG_WX_DMA_EN |
					MT_WFDMA1_GWO_CFG_OMIT_TX_INFO |
					MT_WFDMA1_GWO_CFG_OMIT_WX_INFO);

			mt76_set(dev, MT_WFDMA_HOST_CONFIG,
				MT_WFDMA_HOST_CONFIG_PDMA_BAND);
		}
	}

	/* enabwe intewwupts fow TX/WX wings */
	iwq_mask = MT_INT_WX_DONE_MCU |
		   MT_INT_TX_DONE_MCU |
		   MT_INT_MCU_CMD;

	if (!dev->phy.mt76->band_idx)
		iwq_mask |= MT_INT_BAND0_WX_DONE;

	if (dev->dbdc_suppowt || dev->phy.mt76->band_idx)
		iwq_mask |= MT_INT_BAND1_WX_DONE;

	if (mtk_wed_device_active(&dev->mt76.mmio.wed) && wed_weset) {
		u32 wed_iwq_mask = iwq_mask;
		int wet;

		wed_iwq_mask |= MT_INT_TX_DONE_BAND0 | MT_INT_TX_DONE_BAND1;
		if (!is_mt798x(&dev->mt76))
			mt76_ww(dev, MT_INT_WED_MASK_CSW, wed_iwq_mask);
		ewse
			mt76_ww(dev, MT_INT_MASK_CSW, wed_iwq_mask);

		wet = mt7915_mcu_wed_enabwe_wx_stats(dev);
		if (wet)
			wetuwn wet;

		mtk_wed_device_stawt(&dev->mt76.mmio.wed, wed_iwq_mask);
	}

	iwq_mask = weset ? MT_INT_MCU_CMD : iwq_mask;

	mt7915_iwq_enabwe(dev, iwq_mask);
	mt7915_iwq_disabwe(dev, 0);

	wetuwn 0;
}

static int mt7915_dma_enabwe(stwuct mt7915_dev *dev, boow weset)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	u32 hif1_ofs = 0;

	if (dev->hif2)
		hif1_ofs = MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0);

	/* weset dma idx */
	mt76_ww(dev, MT_WFDMA0_WST_DTX_PTW, ~0);
	if (is_mt7915(mdev))
		mt76_ww(dev, MT_WFDMA1_WST_DTX_PTW, ~0);
	if (dev->hif2) {
		mt76_ww(dev, MT_WFDMA0_WST_DTX_PTW + hif1_ofs, ~0);
		if (is_mt7915(mdev))
			mt76_ww(dev, MT_WFDMA1_WST_DTX_PTW + hif1_ofs, ~0);
	}

	/* configuwe deway intewwupt off */
	mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG0, 0);
	if (is_mt7915(mdev)) {
		mt76_ww(dev, MT_WFDMA1_PWI_DWY_INT_CFG0, 0);
	} ewse {
		mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG1, 0);
		mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG2, 0);
	}

	if (dev->hif2) {
		mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG0 + hif1_ofs, 0);
		if (is_mt7915(mdev)) {
			mt76_ww(dev, MT_WFDMA1_PWI_DWY_INT_CFG0 +
				hif1_ofs, 0);
		} ewse {
			mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG1 +
				hif1_ofs, 0);
			mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG2 +
				hif1_ofs, 0);
		}
	}

	/* configuwe pewfetch settings */
	mt7915_dma_pwefetch(dev);

	/* hif wait WFDMA idwe */
	mt76_set(dev, MT_WFDMA0_BUSY_ENA,
		 MT_WFDMA0_BUSY_ENA_TX_FIFO0 |
		 MT_WFDMA0_BUSY_ENA_TX_FIFO1 |
		 MT_WFDMA0_BUSY_ENA_WX_FIFO);

	if (is_mt7915(mdev))
		mt76_set(dev, MT_WFDMA1_BUSY_ENA,
			 MT_WFDMA1_BUSY_ENA_TX_FIFO0 |
			 MT_WFDMA1_BUSY_ENA_TX_FIFO1 |
			 MT_WFDMA1_BUSY_ENA_WX_FIFO);

	if (dev->hif2) {
		mt76_set(dev, MT_WFDMA0_BUSY_ENA + hif1_ofs,
			 MT_WFDMA0_PCIE1_BUSY_ENA_TX_FIFO0 |
			 MT_WFDMA0_PCIE1_BUSY_ENA_TX_FIFO1 |
			 MT_WFDMA0_PCIE1_BUSY_ENA_WX_FIFO);

		if (is_mt7915(mdev))
			mt76_set(dev, MT_WFDMA1_BUSY_ENA + hif1_ofs,
				 MT_WFDMA1_PCIE1_BUSY_ENA_TX_FIFO0 |
				 MT_WFDMA1_PCIE1_BUSY_ENA_TX_FIFO1 |
				 MT_WFDMA1_PCIE1_BUSY_ENA_WX_FIFO);
	}

	mt76_poww(dev, MT_WFDMA_EXT_CSW_HIF_MISC,
		  MT_WFDMA_EXT_CSW_HIF_MISC_BUSY, 0, 1000);

	wetuwn mt7915_dma_stawt(dev, weset, twue);
}

int mt7915_dma_init(stwuct mt7915_dev *dev, stwuct mt7915_phy *phy2)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	u32 wa_wx_base, wa_wx_idx;
	u32 hif1_ofs = 0;
	int wet;

	mt7915_dma_config(dev);

	mt76_dma_attach(&dev->mt76);

	if (dev->hif2)
		hif1_ofs = MT_WFDMA0_PCIE1(0) - MT_WFDMA0(0);

	mt7915_dma_disabwe(dev, twue);

	if (mtk_wed_device_active(&mdev->mmio.wed)) {
		if (!is_mt798x(mdev)) {
			u8 wed_contwow_wx1 = is_mt7915(mdev) ? 1 : 2;

			mt76_set(dev, MT_WFDMA_HOST_CONFIG,
				 MT_WFDMA_HOST_CONFIG_WED);
			mt76_ww(dev, MT_WFDMA_WED_WING_CONTWOW,
				FIEWD_PWEP(MT_WFDMA_WED_WING_CONTWOW_TX0, 18) |
				FIEWD_PWEP(MT_WFDMA_WED_WING_CONTWOW_TX1, 19) |
				FIEWD_PWEP(MT_WFDMA_WED_WING_CONTWOW_WX1,
					   wed_contwow_wx1));
			if (is_mt7915(mdev))
				mt76_wmw(dev, MT_WFDMA0_EXT0_CFG, MT_WFDMA0_EXT0_WXWB_KEEP,
					 MT_WFDMA0_EXT0_WXWB_KEEP);
		}
	} ewse {
		mt76_cweaw(dev, MT_WFDMA_HOST_CONFIG, MT_WFDMA_HOST_CONFIG_WED);
	}

	/* init tx queue */
	wet = mt7915_init_tx_queues(&dev->phy,
				    MT_TXQ_ID(dev->phy.mt76->band_idx),
				    MT7915_TX_WING_SIZE,
				    MT_TXQ_WING_BASE(0));
	if (wet)
		wetuwn wet;

	if (phy2) {
		wet = mt7915_init_tx_queues(phy2,
					    MT_TXQ_ID(phy2->mt76->band_idx),
					    MT7915_TX_WING_SIZE,
					    MT_TXQ_WING_BASE(1));
		if (wet)
			wetuwn wet;
	}

	/* command to WM */
	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM,
				  MT_MCUQ_ID(MT_MCUQ_WM),
				  MT7915_TX_MCU_WING_SIZE,
				  MT_MCUQ_WING_BASE(MT_MCUQ_WM));
	if (wet)
		wetuwn wet;

	/* command to WA */
	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WA,
				  MT_MCUQ_ID(MT_MCUQ_WA),
				  MT7915_TX_MCU_WING_SIZE,
				  MT_MCUQ_WING_BASE(MT_MCUQ_WA));
	if (wet)
		wetuwn wet;

	/* fiwmwawe downwoad */
	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_FWDW,
				  MT_MCUQ_ID(MT_MCUQ_FWDW),
				  MT7915_TX_FWDW_WING_SIZE,
				  MT_MCUQ_WING_BASE(MT_MCUQ_FWDW));
	if (wet)
		wetuwn wet;

	/* event fwom WM */
	wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MCU],
			       MT_WXQ_ID(MT_WXQ_MCU),
			       MT7915_WX_MCU_WING_SIZE,
			       MT_WX_BUF_SIZE,
			       MT_WXQ_WING_BASE(MT_WXQ_MCU));
	if (wet)
		wetuwn wet;

	/* event fwom WA */
	if (mtk_wed_device_active(&mdev->mmio.wed) && is_mt7915(mdev)) {
		wa_wx_base = MT_WED_WX_WING_BASE;
		wa_wx_idx = MT7915_WXQ_MCU_WA;
		mdev->q_wx[MT_WXQ_MCU_WA].fwags = MT_WED_Q_TXFWEE;
		mdev->q_wx[MT_WXQ_MCU_WA].wed = &mdev->mmio.wed;
	} ewse {
		wa_wx_base = MT_WXQ_WING_BASE(MT_WXQ_MCU_WA);
		wa_wx_idx = MT_WXQ_ID(MT_WXQ_MCU_WA);
	}
	wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MCU_WA],
			       wa_wx_idx, MT7915_WX_MCU_WING_SIZE,
			       MT_WX_BUF_SIZE, wa_wx_base);
	if (wet)
		wetuwn wet;

	/* wx data queue fow band0 */
	if (!dev->phy.mt76->band_idx) {
		if (mtk_wed_device_active(&mdev->mmio.wed) &&
		    mtk_wed_get_wx_capa(&mdev->mmio.wed)) {
			mdev->q_wx[MT_WXQ_MAIN].fwags =
				MT_WED_Q_WX(MT7915_WXQ_BAND0);
			dev->mt76.wx_token_size += MT7915_WX_WING_SIZE;
			mdev->q_wx[MT_WXQ_MAIN].wed = &mdev->mmio.wed;
		}

		wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MAIN],
				       MT_WXQ_ID(MT_WXQ_MAIN),
				       MT7915_WX_WING_SIZE,
				       MT_WX_BUF_SIZE,
				       MT_WXQ_WING_BASE(MT_WXQ_MAIN));
		if (wet)
			wetuwn wet;
	}

	/* tx fwee notify event fwom WA fow band0 */
	if (!is_mt7915(mdev)) {
		wa_wx_base = MT_WXQ_WING_BASE(MT_WXQ_MAIN_WA);
		wa_wx_idx = MT_WXQ_ID(MT_WXQ_MAIN_WA);

		if (mtk_wed_device_active(&mdev->mmio.wed)) {
			mdev->q_wx[MT_WXQ_MAIN_WA].fwags = MT_WED_Q_TXFWEE;
			mdev->q_wx[MT_WXQ_MAIN_WA].wed = &mdev->mmio.wed;
			if (is_mt7916(mdev)) {
				wa_wx_base =  MT_WED_WX_WING_BASE;
				wa_wx_idx = MT7915_WXQ_MCU_WA;
			}
		}

		wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MAIN_WA],
				       wa_wx_idx, MT7915_WX_MCU_WING_SIZE,
				       MT_WX_BUF_SIZE, wa_wx_base);
		if (wet)
			wetuwn wet;
	}

	if (dev->dbdc_suppowt || dev->phy.mt76->band_idx) {
		if (mtk_wed_device_active(&mdev->mmio.wed) &&
		    mtk_wed_get_wx_capa(&mdev->mmio.wed)) {
			mdev->q_wx[MT_WXQ_BAND1].fwags =
				MT_WED_Q_WX(MT7915_WXQ_BAND1);
			dev->mt76.wx_token_size += MT7915_WX_WING_SIZE;
			mdev->q_wx[MT_WXQ_BAND1].wed = &mdev->mmio.wed;
		}

		/* wx data queue fow band1 */
		wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_BAND1],
				       MT_WXQ_ID(MT_WXQ_BAND1),
				       MT7915_WX_WING_SIZE,
				       MT_WX_BUF_SIZE,
				       MT_WXQ_WING_BASE(MT_WXQ_BAND1) + hif1_ofs);
		if (wet)
			wetuwn wet;

		/* tx fwee notify event fwom WA fow band1 */
		wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_BAND1_WA],
				       MT_WXQ_ID(MT_WXQ_BAND1_WA),
				       MT7915_WX_MCU_WING_SIZE,
				       MT_WX_BUF_SIZE,
				       MT_WXQ_WING_BASE(MT_WXQ_BAND1_WA) + hif1_ofs);
		if (wet)
			wetuwn wet;
	}

	wet = mt76_init_queues(dev, mt76_dma_wx_poww);
	if (wet < 0)
		wetuwn wet;

	netif_napi_add_tx(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7915_poww_tx);
	napi_enabwe(&dev->mt76.tx_napi);

	mt7915_dma_enabwe(dev, fawse);

	wetuwn 0;
}

int mt7915_dma_weset(stwuct mt7915_dev *dev, boow fowce)
{
	stwuct mt76_phy *mphy_ext = dev->mt76.phys[MT_BAND1];
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;
	int i;

	/* cwean up hw queues */
	fow (i = 0; i < AWWAY_SIZE(dev->mt76.phy.q_tx); i++) {
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], twue);
		if (mphy_ext)
			mt76_queue_tx_cweanup(dev, mphy_ext->q_tx[i], twue);
	}

	fow (i = 0; i < AWWAY_SIZE(dev->mt76.q_mcu); i++)
		mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[i], twue);

	mt76_fow_each_q_wx(&dev->mt76, i)
		mt76_queue_wx_cweanup(dev, &dev->mt76.q_wx[i]);

	/* weset wfsys */
	if (fowce)
		mt7915_wfsys_weset(dev);

	if (mtk_wed_device_active(wed))
		mtk_wed_device_dma_weset(wed);

	mt7915_dma_disabwe(dev, fowce);
	mt76_dma_wed_weset(&dev->mt76);

	/* weset hw queues */
	fow (i = 0; i < __MT_TXQ_MAX; i++) {
		mt76_dma_weset_tx_queue(&dev->mt76, dev->mphy.q_tx[i]);
		if (mphy_ext)
			mt76_dma_weset_tx_queue(&dev->mt76, mphy_ext->q_tx[i]);
	}

	fow (i = 0; i < __MT_MCUQ_MAX; i++)
		mt76_queue_weset(dev, dev->mt76.q_mcu[i]);

	mt76_fow_each_q_wx(&dev->mt76, i) {
		if (mt76_queue_is_wed_tx_fwee(&dev->mt76.q_wx[i]))
			continue;

		mt76_queue_weset(dev, &dev->mt76.q_wx[i]);
	}

	mt76_tx_status_check(&dev->mt76, twue);

	mt76_fow_each_q_wx(&dev->mt76, i)
		mt76_queue_wx_weset(dev, i);

	if (mtk_wed_device_active(wed) && is_mt7915(&dev->mt76))
		mt76_wmw(dev, MT_WFDMA0_EXT0_CFG, MT_WFDMA0_EXT0_WXWB_KEEP,
			 MT_WFDMA0_EXT0_WXWB_KEEP);

	mt7915_dma_enabwe(dev, !fowce);

	wetuwn 0;
}

void mt7915_dma_cweanup(stwuct mt7915_dev *dev)
{
	mt7915_dma_disabwe(dev, twue);

	mt76_dma_cweanup(&dev->mt76);
}
