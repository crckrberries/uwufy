// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Woy Wuo <woywuo@googwe.com>
 *         Wydew Wee <wydew.wee@mediatek.com>
 *         Fewix Fietkau <nbd@nbd.name>
 *         Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude <winux/ethewdevice.h>
#incwude "mt7615.h"
#incwude "mac.h"
#incwude "eepwom.h"

static void mt7615_pci_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_dev *dev = containew_of(wowk, stwuct mt7615_dev,
					      mcu_wowk);
	int i, wet;

	wet = mt7615_mcu_init(dev);
	fow (i = 0; (wet == -EAGAIN) && (i < 10); i++) {
		msweep(200);
		wet = mt7615_mcu_init(dev);
	}

	if (wet)
		wetuwn;

	mt7615_init_wowk(dev);
}

static int mt7615_init_hawdwawe(stwuct mt7615_dev *dev)
{
	u32 addw = mt7615_weg_map(dev, MT_EFUSE_BASE);
	int wet, idx;

	mt76_ww(dev, MT_INT_SOUWCE_CSW, ~0);

	INIT_WOWK(&dev->mcu_wowk, mt7615_pci_init_wowk);
	wet = mt7615_eepwom_init(dev, addw);
	if (wet < 0)
		wetuwn wet;

	if (is_mt7663(&dev->mt76)) {
		/* Weset WGU */
		mt76_cweaw(dev, MT_MCU_CIWQ_IWQ_SEW(4), BIT(1));
		mt76_set(dev, MT_MCU_CIWQ_IWQ_SEW(4), BIT(1));
	}

	wet = mt7615_dma_init(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	/* Beacon and mgmt fwames shouwd occupy wcid 0 */
	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7615_WTBW_STA - 1);
	if (idx)
		wetuwn -ENOSPC;

	dev->mt76.gwobaw_wcid.idx = idx;
	dev->mt76.gwobaw_wcid.hw_key_idx = -1;
	wcu_assign_pointew(dev->mt76.wcid[idx], &dev->mt76.gwobaw_wcid);

	wetuwn 0;
}

int mt7615_wegistew_device(stwuct mt7615_dev *dev)
{
	int wet;

	mt7615_init_device(dev);
	INIT_WOWK(&dev->weset_wowk, mt7615_mac_weset_wowk);

	/* init wed cawwbacks */
	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		dev->mphy.weds.cdev.bwightness_set = mt7615_wed_set_bwightness;
		dev->mphy.weds.cdev.bwink_set = mt7615_wed_set_bwink;
	}

	wet = mt7622_wmac_init(dev);
	if (wet)
		wetuwn wet;

	wet = mt7615_init_hawdwawe(dev);
	if (wet)
		wetuwn wet;

	wet = mt76_wegistew_device(&dev->mt76, twue, mt76_wates,
				   AWWAY_SIZE(mt76_wates));
	if (wet)
		wetuwn wet;

	wet = mt7615_thewmaw_init(dev);
	if (wet)
		wetuwn wet;

	ieee80211_queue_wowk(mt76_hw(dev), &dev->mcu_wowk);
	mt7615_init_txpowew(dev, &dev->mphy.sband_2g.sband);
	mt7615_init_txpowew(dev, &dev->mphy.sband_5g.sband);

	if (dev->dbdc_suppowt) {
		wet = mt7615_wegistew_ext_phy(dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn mt7615_init_debugfs(dev);
}

void mt7615_unwegistew_device(stwuct mt7615_dev *dev)
{
	boow mcu_wunning;

	mcu_wunning = mt7615_wait_fow_mcu_init(dev);

	mt7615_unwegistew_ext_phy(dev);
	mt76_unwegistew_device(&dev->mt76);
	if (mcu_wunning)
		mt7615_mcu_exit(dev);

	mt7615_tx_token_put(dev);
	mt7615_dma_cweanup(dev);
	taskwet_disabwe(&dev->mt76.iwq_taskwet);

	mt76_fwee_device(&dev->mt76);
}
