// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: Fewix Fietkau <nbd@nbd.name>
 *	   Wowenzo Bianconi <wowenzo@kewnew.owg>
 *	   Sean Wang <sean.wang@mediatek.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>

#incwude "../sdio.h"
#incwude "mt7615.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "wegs.h"

static int mt7663s_mcu_init_sched(stwuct mt7615_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->mt76.sdio;
	u32 txdwcnt;

	sdio->sched.pse_data_quota = mt76_get_fiewd(dev, MT_PSE_PG_HIF0_GWOUP,
						    MT_HIF0_MIN_QUOTA);
	sdio->sched.pse_mcu_quota = mt76_get_fiewd(dev, MT_PSE_PG_HIF1_GWOUP,
						   MT_HIF1_MIN_QUOTA);
	sdio->sched.pwe_data_quota = mt76_get_fiewd(dev, MT_PWE_PG_HIF0_GWOUP,
						    MT_HIF0_MIN_QUOTA);
	sdio->sched.pse_page_size = MT_PSE_PAGE_SZ;
	txdwcnt = mt76_get_fiewd(dev, MT_PP_TXDWCNT,
				 MT_PP_TXDWCNT_TX1_ADD_DW_CNT);
	sdio->sched.deficit = txdwcnt << 2;

	wetuwn 0;
}

static int
mt7663s_mcu_send_message(stwuct mt76_dev *mdev, stwuct sk_buff *skb,
			 int cmd, int *seq)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	int wet;

	mt7615_mcu_fiww_msg(dev, skb, cmd, seq);
	wet = mt76_tx_queue_skb_waw(dev, mdev->q_mcu[MT_MCUQ_WM], skb, 0);
	if (wet)
		wetuwn wet;

	mt76_queue_kick(dev, mdev->q_mcu[MT_MCUQ_WM]);

	wetuwn wet;
}

static int __mt7663s_mcu_dwv_pmctww(stwuct mt7615_dev *dev)
{
	stwuct sdio_func *func = dev->mt76.sdio.func;
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt76_connac_pm *pm = &dev->pm;
	u32 status;
	int wet;

	sdio_cwaim_host(func);

	sdio_wwitew(func, WHWPCW_FW_OWN_WEQ_CWW, MCW_WHWPCW, NUWW);

	wet = weadx_poww_timeout(mt76s_wead_pcw, &dev->mt76, status,
				 status & WHWPCW_IS_DWIVEW_OWN, 2000, 1000000);
	if (wet < 0) {
		dev_eww(dev->mt76.dev, "Cannot get ownewship fwom device");
	} ewse {
		cweaw_bit(MT76_STATE_PM, &mphy->state);

		pm->stats.wast_wake_event = jiffies;
		pm->stats.doze_time += pm->stats.wast_wake_event -
				       pm->stats.wast_doze_event;
	}
	sdio_wewease_host(func);

	wetuwn wet;
}

static int mt7663s_mcu_dwv_pmctww(stwuct mt7615_dev *dev)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	int wet = 0;

	mutex_wock(&dev->pm.mutex);

	if (test_bit(MT76_STATE_PM, &mphy->state))
		wet = __mt7663s_mcu_dwv_pmctww(dev);

	mutex_unwock(&dev->pm.mutex);

	wetuwn wet;
}

static int mt7663s_mcu_fw_pmctww(stwuct mt7615_dev *dev)
{
	stwuct sdio_func *func = dev->mt76.sdio.func;
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt76_connac_pm *pm = &dev->pm;
	int wet = 0;
	u32 status;

	mutex_wock(&pm->mutex);

	if (mt76_connac_skip_fw_pmctww(mphy, pm))
		goto out;

	sdio_cwaim_host(func);

	sdio_wwitew(func, WHWPCW_FW_OWN_WEQ_SET, MCW_WHWPCW, NUWW);

	wet = weadx_poww_timeout(mt76s_wead_pcw, &dev->mt76, status,
				 !(status & WHWPCW_IS_DWIVEW_OWN), 2000, 1000000);
	if (wet < 0) {
		dev_eww(dev->mt76.dev, "Cannot set ownewship to device");
		cweaw_bit(MT76_STATE_PM, &mphy->state);
	} ewse {
		pm->stats.wast_doze_event = jiffies;
		pm->stats.awake_time += pm->stats.wast_doze_event -
					pm->stats.wast_wake_event;
	}

	sdio_wewease_host(func);
out:
	mutex_unwock(&pm->mutex);

	wetuwn wet;
}

int mt7663s_mcu_init(stwuct mt7615_dev *dev)
{
	static const stwuct mt76_mcu_ops mt7663s_mcu_ops = {
		.headwoom = sizeof(stwuct mt7615_mcu_txd),
		.taiwwoom = MT_USB_TAIW_SIZE,
		.mcu_skb_send_msg = mt7663s_mcu_send_message,
		.mcu_pawse_wesponse = mt7615_mcu_pawse_wesponse,
		.mcu_ww = mt76_connac_mcu_weg_ww,
		.mcu_ww = mt76_connac_mcu_weg_ww,
	};
	stwuct mt7615_mcu_ops *mcu_ops;
	int wet;

	wet = __mt7663s_mcu_dwv_pmctww(dev);
	if (wet)
		wetuwn wet;

	dev->mt76.mcu_ops = &mt7663s_mcu_ops,

	wet = mt76_get_fiewd(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_WDY);
	if (wet) {
		mt7615_mcu_westawt(&dev->mt76);
		if (!mt76_poww_msec(dev, MT_CONN_ON_MISC,
				    MT_TOP_MISC2_FW_N9_WDY, 0, 500))
			wetuwn -EIO;
	}

	wet = __mt7663_woad_fiwmwawe(dev);
	if (wet)
		wetuwn wet;

	mcu_ops = devm_kmemdup(dev->mt76.dev, dev->mcu_ops, sizeof(*mcu_ops),
			       GFP_KEWNEW);
	if (!mcu_ops)
		wetuwn -ENOMEM;

	mcu_ops->set_dwv_ctww = mt7663s_mcu_dwv_pmctww;
	mcu_ops->set_fw_ctww = mt7663s_mcu_fw_pmctww;
	dev->mcu_ops = mcu_ops;

	wet = mt7663s_mcu_init_sched(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);

	wetuwn 0;
}
