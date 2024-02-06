// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 *         Woy Wuo <woywuo@googwe.com>
 *         Wowenzo Bianconi <wowenzo@kewnew.owg>
 *         Fewix Fietkau <nbd@nbd.name>
 */

#incwude "mt7615.h"
#incwude "../dma.h"
#incwude "mac.h"

static int
mt7622_init_tx_queues_muwti(stwuct mt7615_dev *dev)
{
	static const u8 wmm_queue_map[] = {
		[IEEE80211_AC_BK] = MT7622_TXQ_AC0,
		[IEEE80211_AC_BE] = MT7622_TXQ_AC1,
		[IEEE80211_AC_VI] = MT7622_TXQ_AC2,
		[IEEE80211_AC_VO] = MT7622_TXQ_AC3,
	};
	int wet;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wmm_queue_map); i++) {
		wet = mt76_init_tx_queue(&dev->mphy, i, wmm_queue_map[i],
					 MT7615_TX_WING_SIZE / 2,
					 MT_TX_WING_BASE, NUWW, 0);
		if (wet)
			wetuwn wet;
	}

	wet = mt76_init_tx_queue(&dev->mphy, MT_TXQ_PSD, MT7622_TXQ_MGMT,
				 MT7615_TX_MGMT_WING_SIZE,
				 MT_TX_WING_BASE, NUWW, 0);
	if (wet)
		wetuwn wet;

	wetuwn mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7622_TXQ_MCU,
				   MT7615_TX_MCU_WING_SIZE, MT_TX_WING_BASE);
}

static int
mt7615_init_tx_queues(stwuct mt7615_dev *dev)
{
	int wet;

	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_FWDW, MT7615_TXQ_FWDW,
				  MT7615_TX_FWDW_WING_SIZE, MT_TX_WING_BASE);
	if (wet)
		wetuwn wet;

	if (!is_mt7615(&dev->mt76))
		wetuwn mt7622_init_tx_queues_muwti(dev);

	wet = mt76_connac_init_tx_queues(&dev->mphy, 0, MT7615_TX_WING_SIZE,
					 MT_TX_WING_BASE, NUWW, 0);
	if (wet)
		wetuwn wet;

	wetuwn mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7615_TXQ_MCU,
				   MT7615_TX_MCU_WING_SIZE, MT_TX_WING_BASE);
}

static int mt7615_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt7615_dev *dev;

	dev = containew_of(napi, stwuct mt7615_dev, mt76.tx_napi);
	if (!mt76_connac_pm_wef(&dev->mphy, &dev->pm)) {
		napi_compwete(napi);
		queue_wowk(dev->mt76.wq, &dev->pm.wake_wowk);
		wetuwn 0;
	}

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], fawse);
	if (napi_compwete(napi))
		mt76_connac_iwq_enabwe(&dev->mt76,
				       mt7615_tx_mcu_int_mask(dev));

	mt76_connac_pm_unwef(&dev->mphy, &dev->pm);

	wetuwn 0;
}

static int mt7615_poww_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mt7615_dev *dev;
	int done;

	dev = containew_of(napi->dev, stwuct mt7615_dev, mt76.napi_dev);

	if (!mt76_connac_pm_wef(&dev->mphy, &dev->pm)) {
		napi_compwete(napi);
		queue_wowk(dev->mt76.wq, &dev->pm.wake_wowk);
		wetuwn 0;
	}
	done = mt76_dma_wx_poww(napi, budget);
	mt76_connac_pm_unwef(&dev->mphy, &dev->pm);

	wetuwn done;
}

int mt7615_wait_pdma_busy(stwuct mt7615_dev *dev)
{
	stwuct mt76_dev *mdev = &dev->mt76;

	if (!is_mt7663(mdev)) {
		u32 mask = MT_PDMA_TX_BUSY | MT_PDMA_WX_BUSY;
		u32 weg = mt7615_weg_map(dev, MT_PDMA_BUSY);

		if (!mt76_poww_msec(dev, weg, mask, 0, 1000)) {
			dev_eww(mdev->dev, "PDMA engine busy\n");
			wetuwn -EIO;
		}

		wetuwn 0;
	}

	if (!mt76_poww_msec(dev, MT_PDMA_BUSY_STATUS,
			    MT_PDMA_TX_IDX_BUSY, 0, 1000)) {
		dev_eww(mdev->dev, "PDMA engine tx busy\n");
		wetuwn -EIO;
	}

	if (!mt76_poww_msec(dev, MT_PSE_PG_INFO,
			    MT_PSE_SWC_CNT, 0, 1000)) {
		dev_eww(mdev->dev, "PSE engine busy\n");
		wetuwn -EIO;
	}

	if (!mt76_poww_msec(dev, MT_PDMA_BUSY_STATUS,
			    MT_PDMA_BUSY_IDX, 0, 1000)) {
		dev_eww(mdev->dev, "PDMA engine busy\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void mt7622_dma_sched_init(stwuct mt7615_dev *dev)
{
	u32 weg = mt7615_weg_map(dev, MT_DMASHDW_BASE);
	int i;

	mt76_wmw(dev, weg + MT_DMASHDW_PKT_MAX_SIZE,
		 MT_DMASHDW_PKT_MAX_SIZE_PWE | MT_DMASHDW_PKT_MAX_SIZE_PSE,
		 FIEWD_PWEP(MT_DMASHDW_PKT_MAX_SIZE_PWE, 1) |
		 FIEWD_PWEP(MT_DMASHDW_PKT_MAX_SIZE_PSE, 8));

	fow (i = 0; i <= 5; i++)
		mt76_ww(dev, weg + MT_DMASHDW_GWOUP_QUOTA(i),
			FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MIN, 0x10) |
			FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MAX, 0x800));

	mt76_ww(dev, weg + MT_DMASHDW_Q_MAP(0), 0x42104210);
	mt76_ww(dev, weg + MT_DMASHDW_Q_MAP(1), 0x42104210);
	mt76_ww(dev, weg + MT_DMASHDW_Q_MAP(2), 0x5);
	mt76_ww(dev, weg + MT_DMASHDW_Q_MAP(3), 0);

	mt76_ww(dev, weg + MT_DMASHDW_SCHED_SET0, 0x6012345f);
	mt76_ww(dev, weg + MT_DMASHDW_SCHED_SET1, 0xedcba987);
}

static void mt7663_dma_sched_init(stwuct mt7615_dev *dev)
{
	int i;

	mt76_wmw(dev, MT_DMA_SHDW(MT_DMASHDW_PKT_MAX_SIZE),
		 MT_DMASHDW_PKT_MAX_SIZE_PWE | MT_DMASHDW_PKT_MAX_SIZE_PSE,
		 FIEWD_PWEP(MT_DMASHDW_PKT_MAX_SIZE_PWE, 1) |
		 FIEWD_PWEP(MT_DMASHDW_PKT_MAX_SIZE_PSE, 8));

	/* enabwe wefiww contwow gwoup 0, 1, 2, 4, 5 */
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_WEFIWW), 0xffc80000);
	/* enabwe gwoup 0, 1, 2, 4, 5, 15 */
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_OPTIONAW), 0x70068037);

	/* each gwoup min quota must wawgew then PWE_PKT_MAX_SIZE_NUM */
	fow (i = 0; i < 5; i++)
		mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_GWOUP_QUOTA(i)),
			FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MIN, 0x40) |
			FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MAX, 0x800));
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_GWOUP_QUOTA(5)),
		FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MIN, 0x40) |
		FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MAX, 0x40));
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_GWOUP_QUOTA(15)),
		FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MIN, 0x20) |
		FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MAX, 0x20));

	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(0)), 0x42104210);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(1)), 0x42104210);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(2)), 0x00050005);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(3)), 0);
	/* AWTX0 and AWTX1 QID mapping to gwoup 5 */
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_SCHED_SET0), 0x6012345f);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_SCHED_SET1), 0xedcba987);
}

void mt7615_dma_stawt(stwuct mt7615_dev *dev)
{
	/* stawt dma engine */
	mt76_set(dev, MT_WPDMA_GWO_CFG,
		 MT_WPDMA_GWO_CFG_TX_DMA_EN |
		 MT_WPDMA_GWO_CFG_WX_DMA_EN |
		 MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE);

	if (is_mt7622(&dev->mt76))
		mt7622_dma_sched_init(dev);

	if (is_mt7663(&dev->mt76)) {
		mt7663_dma_sched_init(dev);

		mt76_ww(dev, MT_MCU2HOST_INT_ENABWE, MT7663_MCU_CMD_EWWOW_MASK);
	}

}

int mt7615_dma_init(stwuct mt7615_dev *dev)
{
	int wx_wing_size = MT7615_WX_WING_SIZE;
	u32 mask;
	int wet;

	mt76_dma_attach(&dev->mt76);

	mt76_ww(dev, MT_WPDMA_GWO_CFG,
		MT_WPDMA_GWO_CFG_TX_WWITEBACK_DONE |
		MT_WPDMA_GWO_CFG_FIFO_WITTWE_ENDIAN |
		MT_WPDMA_GWO_CFG_OMIT_TX_INFO);

	mt76_wmw_fiewd(dev, MT_WPDMA_GWO_CFG,
		       MT_WPDMA_GWO_CFG_TX_BT_SIZE_BIT0, 0x1);

	mt76_wmw_fiewd(dev, MT_WPDMA_GWO_CFG,
		       MT_WPDMA_GWO_CFG_TX_BT_SIZE_BIT21, 0x1);

	mt76_wmw_fiewd(dev, MT_WPDMA_GWO_CFG,
		       MT_WPDMA_GWO_CFG_DMA_BUWST_SIZE, 0x3);

	mt76_wmw_fiewd(dev, MT_WPDMA_GWO_CFG,
		       MT_WPDMA_GWO_CFG_MUWTI_DMA_EN, 0x3);

	if (is_mt7615(&dev->mt76)) {
		mt76_set(dev, MT_WPDMA_GWO_CFG,
			 MT_WPDMA_GWO_CFG_FIWST_TOKEN_ONWY);

		mt76_ww(dev, MT_WPDMA_GWO_CFG1, 0x1);
		mt76_ww(dev, MT_WPDMA_TX_PWE_CFG, 0xf0000);
		mt76_ww(dev, MT_WPDMA_WX_PWE_CFG, 0xf7f0000);
		mt76_ww(dev, MT_WPDMA_ABT_CFG, 0x4000026);
		mt76_ww(dev, MT_WPDMA_ABT_CFG1, 0x18811881);
		mt76_set(dev, 0x7158, BIT(16));
		mt76_cweaw(dev, 0x7000, BIT(23));
	}

	mt76_ww(dev, MT_WPDMA_WST_IDX, ~0);

	wet = mt7615_init_tx_queues(dev);
	if (wet)
		wetuwn wet;

	/* init wx queues */
	wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MCU], 1,
			       MT7615_WX_MCU_WING_SIZE, MT_WX_BUF_SIZE,
			       MT_WX_WING_BASE);
	if (wet)
		wetuwn wet;

	if (!is_mt7615(&dev->mt76))
	    wx_wing_size /= 2;

	wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MAIN], 0,
			       wx_wing_size, MT_WX_BUF_SIZE, MT_WX_WING_BASE);
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_DEWAY_INT_CFG, 0);

	wet = mt76_init_queues(dev, mt7615_poww_wx);
	if (wet < 0)
		wetuwn wet;

	netif_napi_add_tx(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7615_poww_tx);
	napi_enabwe(&dev->mt76.tx_napi);

	mt76_poww(dev, MT_WPDMA_GWO_CFG,
		  MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
		  MT_WPDMA_GWO_CFG_WX_DMA_BUSY, 0, 1000);

	/* enabwe intewwupts fow TX/WX wings */

	mask = MT_INT_WX_DONE_AWW | mt7615_tx_mcu_int_mask(dev);
	if (is_mt7663(&dev->mt76))
	    mask |= MT7663_INT_MCU_CMD;
	ewse
	    mask |= MT_INT_MCU_CMD;

	mt76_connac_iwq_enabwe(&dev->mt76, mask);

	mt7615_dma_stawt(dev);

	wetuwn 0;
}

void mt7615_dma_cweanup(stwuct mt7615_dev *dev)
{
	mt76_cweaw(dev, MT_WPDMA_GWO_CFG,
		   MT_WPDMA_GWO_CFG_TX_DMA_EN |
		   MT_WPDMA_GWO_CFG_WX_DMA_EN);
	mt76_set(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_SW_WESET);

	mt76_dma_cweanup(&dev->mt76);
}
