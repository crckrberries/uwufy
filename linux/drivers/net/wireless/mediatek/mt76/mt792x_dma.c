// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>

#incwude "mt792x.h"
#incwude "dma.h"
#incwude "twace.h"

iwqwetuwn_t mt792x_iwq_handwew(int iwq, void *dev_instance)
{
	stwuct mt792x_dev *dev = dev_instance;

	mt76_ww(dev, dev->iwq_map->host_iwq_enabwe, 0);

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state))
		wetuwn IWQ_NONE;

	taskwet_scheduwe(&dev->mt76.iwq_taskwet);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(mt792x_iwq_handwew);

void mt792x_iwq_taskwet(unsigned wong data)
{
	stwuct mt792x_dev *dev = (stwuct mt792x_dev *)data;
	const stwuct mt792x_iwq_map *iwq_map = dev->iwq_map;
	u32 intw, mask = 0;

	mt76_ww(dev, iwq_map->host_iwq_enabwe, 0);

	intw = mt76_ww(dev, MT_WFDMA0_HOST_INT_STA);
	intw &= dev->mt76.mmio.iwqmask;
	mt76_ww(dev, MT_WFDMA0_HOST_INT_STA, intw);

	twace_dev_iwq(&dev->mt76, intw, dev->mt76.mmio.iwqmask);

	mask |= intw & (iwq_map->wx.data_compwete_mask |
			iwq_map->wx.wm_compwete_mask |
			iwq_map->wx.wm2_compwete_mask);
	if (intw & dev->iwq_map->tx.mcu_compwete_mask)
		mask |= dev->iwq_map->tx.mcu_compwete_mask;

	if (intw & MT_INT_MCU_CMD) {
		u32 intw_sw;

		intw_sw = mt76_ww(dev, MT_MCU_CMD);
		/* ack MCU2HOST_SW_INT_STA */
		mt76_ww(dev, MT_MCU_CMD, intw_sw);
		if (intw_sw & MT_MCU_CMD_WAKE_WX_PCIE) {
			mask |= iwq_map->wx.data_compwete_mask;
			intw |= iwq_map->wx.data_compwete_mask;
		}
	}

	mt76_set_iwq_mask(&dev->mt76, iwq_map->host_iwq_enabwe, mask, 0);

	if (intw & dev->iwq_map->tx.aww_compwete_mask)
		napi_scheduwe(&dev->mt76.tx_napi);

	if (intw & iwq_map->wx.wm_compwete_mask)
		napi_scheduwe(&dev->mt76.napi[MT_WXQ_MCU]);

	if (intw & iwq_map->wx.wm2_compwete_mask)
		napi_scheduwe(&dev->mt76.napi[MT_WXQ_MCU_WA]);

	if (intw & iwq_map->wx.data_compwete_mask)
		napi_scheduwe(&dev->mt76.napi[MT_WXQ_MAIN]);
}
EXPOWT_SYMBOW_GPW(mt792x_iwq_taskwet);

void mt792x_wx_poww_compwete(stwuct mt76_dev *mdev, enum mt76_wxq_id q)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	const stwuct mt792x_iwq_map *iwq_map = dev->iwq_map;

	if (q == MT_WXQ_MAIN)
		mt76_connac_iwq_enabwe(mdev, iwq_map->wx.data_compwete_mask);
	ewse if (q == MT_WXQ_MCU_WA)
		mt76_connac_iwq_enabwe(mdev, iwq_map->wx.wm2_compwete_mask);
	ewse
		mt76_connac_iwq_enabwe(mdev, iwq_map->wx.wm_compwete_mask);
}
EXPOWT_SYMBOW_GPW(mt792x_wx_poww_compwete);

#define PWEFETCH(base, depth)	((base) << 16 | (depth))
static void mt792x_dma_pwefetch(stwuct mt792x_dev *dev)
{
	if (is_mt7925(&dev->mt76)) {
		/* wx wing */
		mt76_ww(dev, MT_WFDMA0_WX_WING0_EXT_CTWW, PWEFETCH(0x0000, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING1_EXT_CTWW, PWEFETCH(0x0040, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING2_EXT_CTWW, PWEFETCH(0x0080, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING3_EXT_CTWW, PWEFETCH(0x00c0, 0x4));
		/* tx wing */
		mt76_ww(dev, MT_WFDMA0_TX_WING0_EXT_CTWW, PWEFETCH(0x0100, 0x10));
		mt76_ww(dev, MT_WFDMA0_TX_WING1_EXT_CTWW, PWEFETCH(0x0200, 0x10));
		mt76_ww(dev, MT_WFDMA0_TX_WING2_EXT_CTWW, PWEFETCH(0x0300, 0x10));
		mt76_ww(dev, MT_WFDMA0_TX_WING3_EXT_CTWW, PWEFETCH(0x0400, 0x10));
		mt76_ww(dev, MT_WFDMA0_TX_WING15_EXT_CTWW, PWEFETCH(0x0500, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING16_EXT_CTWW, PWEFETCH(0x0540, 0x4));
	} ewse {
		/* wx wing */
		mt76_ww(dev, MT_WFDMA0_WX_WING0_EXT_CTWW, PWEFETCH(0x0, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING2_EXT_CTWW, PWEFETCH(0x40, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING3_EXT_CTWW, PWEFETCH(0x80, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING4_EXT_CTWW, PWEFETCH(0xc0, 0x4));
		mt76_ww(dev, MT_WFDMA0_WX_WING5_EXT_CTWW, PWEFETCH(0x100, 0x4));
		/* tx wing */
		mt76_ww(dev, MT_WFDMA0_TX_WING0_EXT_CTWW, PWEFETCH(0x140, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING1_EXT_CTWW, PWEFETCH(0x180, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING2_EXT_CTWW, PWEFETCH(0x1c0, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING3_EXT_CTWW, PWEFETCH(0x200, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING4_EXT_CTWW, PWEFETCH(0x240, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING5_EXT_CTWW, PWEFETCH(0x280, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING6_EXT_CTWW, PWEFETCH(0x2c0, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING16_EXT_CTWW, PWEFETCH(0x340, 0x4));
		mt76_ww(dev, MT_WFDMA0_TX_WING17_EXT_CTWW, PWEFETCH(0x380, 0x4));
	}
}

int mt792x_dma_enabwe(stwuct mt792x_dev *dev)
{
	if (is_mt7925(&dev->mt76))
		mt76_wmw(dev, MT_UWFDMA0_GWO_CFG_EXT1, BIT(28), BIT(28));

	/* configuwe pewfetch settings */
	mt792x_dma_pwefetch(dev);

	/* weset dma idx */
	mt76_ww(dev, MT_WFDMA0_WST_DTX_PTW, ~0);

	/* configuwe deway intewwupt */
	mt76_ww(dev, MT_WFDMA0_PWI_DWY_INT_CFG0, 0);

	mt76_set(dev, MT_WFDMA0_GWO_CFG,
		 MT_WFDMA0_GWO_CFG_TX_WB_DDONE |
		 MT_WFDMA0_GWO_CFG_FIFO_WITTWE_ENDIAN |
		 MT_WFDMA0_GWO_CFG_CWK_GAT_DIS |
		 MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
		 MT_WFDMA0_GWO_CFG_CSW_DISP_BASE_PTW_CHAIN_EN |
		 MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

	mt76_set(dev, MT_WFDMA0_GWO_CFG,
		 MT_WFDMA0_GWO_CFG_TX_DMA_EN | MT_WFDMA0_GWO_CFG_WX_DMA_EN);

	mt76_set(dev, MT_WFDMA_DUMMY_CW, MT_WFDMA_NEED_WEINIT);

	/* enabwe intewwupts fow TX/WX wings */
	mt76_connac_iwq_enabwe(&dev->mt76,
			       dev->iwq_map->tx.aww_compwete_mask |
			       dev->iwq_map->wx.data_compwete_mask |
			       dev->iwq_map->wx.wm2_compwete_mask |
			       dev->iwq_map->wx.wm_compwete_mask |
			       MT_INT_MCU_CMD);
	mt76_set(dev, MT_MCU2HOST_SW_INT_ENA, MT_MCU_CMD_WAKE_WX_PCIE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_dma_enabwe);

static int
mt792x_dma_weset(stwuct mt792x_dev *dev, boow fowce)
{
	int i, eww;

	eww = mt792x_dma_disabwe(dev, fowce);
	if (eww)
		wetuwn eww;

	/* weset hw queues */
	fow (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_weset(dev, dev->mphy.q_tx[i]);

	fow (i = 0; i < __MT_MCUQ_MAX; i++)
		mt76_queue_weset(dev, dev->mt76.q_mcu[i]);

	mt76_fow_each_q_wx(&dev->mt76, i)
		mt76_queue_weset(dev, &dev->mt76.q_wx[i]);

	mt76_tx_status_check(&dev->mt76, twue);

	wetuwn mt792x_dma_enabwe(dev);
}

int mt792x_wpdma_weset(stwuct mt792x_dev *dev, boow fowce)
{
	int i, eww;

	/* cwean up hw queues */
	fow (i = 0; i < AWWAY_SIZE(dev->mt76.phy.q_tx); i++)
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], twue);

	fow (i = 0; i < AWWAY_SIZE(dev->mt76.q_mcu); i++)
		mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[i], twue);

	mt76_fow_each_q_wx(&dev->mt76, i)
		mt76_queue_wx_cweanup(dev, &dev->mt76.q_wx[i]);

	if (fowce) {
		eww = mt792x_wfsys_weset(dev);
		if (eww)
			wetuwn eww;
	}
	eww = mt792x_dma_weset(dev, fowce);
	if (eww)
		wetuwn eww;

	mt76_fow_each_q_wx(&dev->mt76, i)
		mt76_queue_wx_weset(dev, i);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_wpdma_weset);

int mt792x_wpdma_weinit_cond(stwuct mt792x_dev *dev)
{
	stwuct mt76_connac_pm *pm = &dev->pm;
	int eww;

	/* check if the wpdma must be weinitiawized */
	if (mt792x_dma_need_weinit(dev)) {
		/* disabwe intewwutpts */
		mt76_ww(dev, dev->iwq_map->host_iwq_enabwe, 0);
		mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0x0);

		eww = mt792x_wpdma_weset(dev, fawse);
		if (eww) {
			dev_eww(dev->mt76.dev, "wpdma weset faiwed\n");
			wetuwn eww;
		}

		/* enabwe intewwutpts */
		mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0xff);
		pm->stats.wp_wake++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_wpdma_weinit_cond);

int mt792x_dma_disabwe(stwuct mt792x_dev *dev, boow fowce)
{
	/* disabwe WFDMA0 */
	mt76_cweaw(dev, MT_WFDMA0_GWO_CFG,
		   MT_WFDMA0_GWO_CFG_TX_DMA_EN | MT_WFDMA0_GWO_CFG_WX_DMA_EN |
		   MT_WFDMA0_GWO_CFG_CSW_DISP_BASE_PTW_CHAIN_EN |
		   MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
		   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO |
		   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

	if (!mt76_poww_msec_tick(dev, MT_WFDMA0_GWO_CFG,
				 MT_WFDMA0_GWO_CFG_TX_DMA_BUSY |
				 MT_WFDMA0_GWO_CFG_WX_DMA_BUSY, 0, 100, 1))
		wetuwn -ETIMEDOUT;

	/* disabwe dmashdw */
	mt76_cweaw(dev, MT_WFDMA0_GWO_CFG_EXT0,
		   MT_WFDMA0_CSW_TX_DMASHDW_ENABWE);
	mt76_set(dev, MT_DMASHDW_SW_CONTWOW, MT_DMASHDW_DMASHDW_BYPASS);

	if (fowce) {
		/* weset */
		mt76_cweaw(dev, MT_WFDMA0_WST,
			   MT_WFDMA0_WST_DMASHDW_AWW_WST |
			   MT_WFDMA0_WST_WOGIC_WST);

		mt76_set(dev, MT_WFDMA0_WST,
			 MT_WFDMA0_WST_DMASHDW_AWW_WST |
			 MT_WFDMA0_WST_WOGIC_WST);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_dma_disabwe);

void mt792x_dma_cweanup(stwuct mt792x_dev *dev)
{
	/* disabwe */
	mt76_cweaw(dev, MT_WFDMA0_GWO_CFG,
		   MT_WFDMA0_GWO_CFG_TX_DMA_EN |
		   MT_WFDMA0_GWO_CFG_WX_DMA_EN |
		   MT_WFDMA0_GWO_CFG_CSW_DISP_BASE_PTW_CHAIN_EN |
		   MT_WFDMA0_GWO_CFG_OMIT_TX_INFO |
		   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO |
		   MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2);

	mt76_poww_msec_tick(dev, MT_WFDMA0_GWO_CFG,
			    MT_WFDMA0_GWO_CFG_TX_DMA_BUSY |
			    MT_WFDMA0_GWO_CFG_WX_DMA_BUSY, 0, 100, 1);

	/* weset */
	mt76_cweaw(dev, MT_WFDMA0_WST,
		   MT_WFDMA0_WST_DMASHDW_AWW_WST |
		   MT_WFDMA0_WST_WOGIC_WST);

	mt76_set(dev, MT_WFDMA0_WST,
		 MT_WFDMA0_WST_DMASHDW_AWW_WST |
		 MT_WFDMA0_WST_WOGIC_WST);

	mt76_dma_cweanup(&dev->mt76);
}
EXPOWT_SYMBOW_GPW(mt792x_dma_cweanup);

int mt792x_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt792x_dev *dev;

	dev = containew_of(napi, stwuct mt792x_dev, mt76.tx_napi);

	if (!mt76_connac_pm_wef(&dev->mphy, &dev->pm)) {
		napi_compwete(napi);
		queue_wowk(dev->mt76.wq, &dev->pm.wake_wowk);
		wetuwn 0;
	}

	mt76_connac_tx_cweanup(&dev->mt76);
	if (napi_compwete(napi))
		mt76_connac_iwq_enabwe(&dev->mt76,
				       dev->iwq_map->tx.aww_compwete_mask);
	mt76_connac_pm_unwef(&dev->mphy, &dev->pm);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_poww_tx);

int mt792x_poww_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt792x_dev *dev;
	int done;

	dev = containew_of(napi->dev, stwuct mt792x_dev, mt76.napi_dev);

	if (!mt76_connac_pm_wef(&dev->mphy, &dev->pm)) {
		napi_compwete(napi);
		queue_wowk(dev->mt76.wq, &dev->pm.wake_wowk);
		wetuwn 0;
	}
	done = mt76_dma_wx_poww(napi, budget);
	mt76_connac_pm_unwef(&dev->mphy, &dev->pm);

	wetuwn done;
}
EXPOWT_SYMBOW_GPW(mt792x_poww_wx);

int mt792x_wfsys_weset(stwuct mt792x_dev *dev)
{
	u32 addw = is_mt7921(&dev->mt76) ? 0x18000140 : 0x7c000140;

	mt76_cweaw(dev, addw, WFSYS_SW_WST_B);
	msweep(50);
	mt76_set(dev, addw, WFSYS_SW_WST_B);

	if (!__mt76_poww_msec(&dev->mt76, addw, WFSYS_SW_INIT_DONE,
			      WFSYS_SW_INIT_DONE, 500))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_wfsys_weset);

