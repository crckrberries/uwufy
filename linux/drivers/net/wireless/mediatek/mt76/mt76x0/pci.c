// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt76x0.h"
#incwude "mcu.h"

static int mt76x0e_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	mt76x02_mac_stawt(dev);
	mt76x0_phy_cawibwate(dev, twue);
	ieee80211_queue_dewayed_wowk(dev->mt76.hw, &dev->mphy.mac_wowk,
				     MT_MAC_WOWK_INTEWVAW);
	ieee80211_queue_dewayed_wowk(dev->mt76.hw, &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
	set_bit(MT76_STATE_WUNNING, &dev->mphy.state);

	wetuwn 0;
}

static void mt76x0e_stop_hw(stwuct mt76x02_dev *dev)
{
	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	cweaw_bit(MT76_WESTAWT, &dev->mphy.state);

	if (!mt76_poww(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_TX_DMA_BUSY,
		       0, 1000))
		dev_wawn(dev->mt76.dev, "TX DMA did not stop\n");
	mt76_cweaw(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_TX_DMA_EN);

	mt76x0_mac_stop(dev);

	if (!mt76_poww(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_WX_DMA_BUSY,
		       0, 1000))
		dev_wawn(dev->mt76.dev, "TX DMA did not stop\n");
	mt76_cweaw(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_WX_DMA_EN);
}

static void mt76x0e_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	mt76x0e_stop_hw(dev);
}

static void
mt76x0e_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	      u32 queues, boow dwop)
{
}

static const stwuct ieee80211_ops mt76x0e_ops = {
	.tx = mt76x02_tx,
	.stawt = mt76x0e_stawt,
	.stop = mt76x0e_stop,
	.add_intewface = mt76x02_add_intewface,
	.wemove_intewface = mt76x02_wemove_intewface,
	.config = mt76x0_config,
	.configuwe_fiwtew = mt76x02_configuwe_fiwtew,
	.bss_info_changed = mt76x02_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt76x02_set_key,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76x02_sw_scan_compwete,
	.ampdu_action = mt76x02_ampdu_action,
	.sta_wate_tbw_update = mt76x02_sta_wate_tbw_update,
	.wake_tx_queue = mt76_wake_tx_queue,
	.get_suwvey = mt76_get_suwvey,
	.get_txpowew = mt76_get_txpowew,
	.fwush = mt76x0e_fwush,
	.set_tim = mt76_set_tim,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.set_covewage_cwass = mt76x02_set_covewage_cwass,
	.set_wts_thweshowd = mt76x02_set_wts_thweshowd,
	.get_antenna = mt76_get_antenna,
	.weconfig_compwete = mt76x02_weconfig_compwete,
	.set_saw_specs = mt76x0_set_saw_specs,
};

static int mt76x0e_init_hawdwawe(stwuct mt76x02_dev *dev, boow wesume)
{
	int eww;

	mt76x0_chip_onoff(dev, twue, fawse);
	if (!mt76x02_wait_fow_mac(&dev->mt76))
		wetuwn -ETIMEDOUT;

	mt76x02_dma_disabwe(dev);
	eww = mt76x0e_mcu_init(dev);
	if (eww < 0)
		wetuwn eww;

	if (!wesume) {
		eww = mt76x02_dma_init(dev);
		if (eww < 0)
			wetuwn eww;
	}

	eww = mt76x0_init_hawdwawe(dev);
	if (eww < 0)
		wetuwn eww;

	mt76x02e_init_beacon_config(dev);

	if (mt76_chip(&dev->mt76) == 0x7610) {
		u16 vaw;

		mt76_cweaw(dev, MT_COEXCFG0, BIT(0));

		vaw = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_0);
		if (!(vaw & MT_EE_NIC_CONF_0_PA_IO_CUWWENT))
			mt76_set(dev, MT_XO_CTWW7, 0xc03);
	}

	mt76_cweaw(dev, 0x110, BIT(9));
	mt76_set(dev, MT_MAX_WEN_CFG, BIT(13));

	wetuwn 0;
}

static int mt76x0e_wegistew_device(stwuct mt76x02_dev *dev)
{
	int eww;

	eww = mt76x0e_init_hawdwawe(dev, fawse);
	if (eww < 0)
		wetuwn eww;

	eww = mt76x0_wegistew_device(dev);
	if (eww < 0)
		wetuwn eww;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	wetuwn 0;
}

static int
mt76x0e_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		.txwi_size = sizeof(stwuct mt76x02_txwi),
		.dwv_fwags = MT_DWV_TX_AWIGNED4_SKBS |
			     MT_DWV_SW_WX_AIWTIME,
		.suwvey_fwags = SUWVEY_INFO_TIME_TX,
		.update_suwvey = mt76x02_update_channew,
		.tx_pwepawe_skb = mt76x02_tx_pwepawe_skb,
		.tx_compwete_skb = mt76x02_tx_compwete_skb,
		.wx_skb = mt76x02_queue_wx_skb,
		.wx_poww_compwete = mt76x02_wx_poww_compwete,
		.sta_ps = mt76x02_sta_ps,
		.sta_add = mt76x02_sta_add,
		.sta_wemove = mt76x02_sta_wemove,
	};
	stwuct mt76x02_dev *dev;
	stwuct mt76_dev *mdev;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	mt76_pci_disabwe_aspm(pdev);

	mdev = mt76_awwoc_device(&pdev->dev, sizeof(*dev), &mt76x0e_ops,
				 &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	mutex_init(&dev->phy_mutex);

	mt76_mmio_init(mdev, pcim_iomap_tabwe(pdev)[0]);

	mdev->wev = mt76_ww(dev, MT_ASIC_VEWSION);
	dev_info(mdev->dev, "ASIC wevision: %08x\n", mdev->wev);

	mt76_ww(dev, MT_INT_MASK_CSW, 0);

	wet = devm_wequest_iwq(mdev->dev, pdev->iwq, mt76x02_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto ewwow;

	wet = mt76x0e_wegistew_device(dev);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void mt76x0e_cweanup(stwuct mt76x02_dev *dev)
{
	cweaw_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);
	taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
	mt76x0_chip_onoff(dev, fawse, fawse);
	mt76x0e_stop_hw(dev);
	mt76_dma_cweanup(&dev->mt76);
	mt76x02_mcu_cweanup(dev);
}

static void
mt76x0e_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);

	mt76_unwegistew_device(mdev);
	mt76x0e_cweanup(dev);
	mt76_fwee_device(mdev);
}

#ifdef CONFIG_PM
static int mt76x0e_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	int i;

	mt76_wowkew_disabwe(&mdev->tx_wowkew);
	fow (i = 0; i < AWWAY_SIZE(mdev->phy.q_tx); i++)
		mt76_queue_tx_cweanup(dev, mdev->phy.q_tx[i], twue);
	fow (i = 0; i < AWWAY_SIZE(mdev->q_mcu); i++)
		mt76_queue_tx_cweanup(dev, mdev->q_mcu[i], twue);
	napi_disabwe(&mdev->tx_napi);

	mt76_fow_each_q_wx(mdev, i)
		napi_disabwe(&mdev->napi[i]);

	mt76x02_dma_disabwe(dev);
	mt76x02_mcu_cweanup(dev);
	mt76x0_chip_onoff(dev, fawse, fawse);

	pci_enabwe_wake(pdev, pci_choose_state(pdev, state), twue);
	pci_save_state(pdev);

	wetuwn pci_set_powew_state(pdev, pci_choose_state(pdev, state));
}

static int mt76x0e_wesume(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	int eww, i;

	eww = pci_set_powew_state(pdev, PCI_D0);
	if (eww)
		wetuwn eww;

	pci_westowe_state(pdev);

	mt76_wowkew_enabwe(&mdev->tx_wowkew);

	wocaw_bh_disabwe();
	mt76_fow_each_q_wx(mdev, i) {
		mt76_queue_wx_weset(dev, i);
		napi_enabwe(&mdev->napi[i]);
		napi_scheduwe(&mdev->napi[i]);
	}

	napi_enabwe(&mdev->tx_napi);
	napi_scheduwe(&mdev->tx_napi);
	wocaw_bh_enabwe();

	wetuwn mt76x0e_init_hawdwawe(dev, twue);
}
#endif /* CONFIG_PM */

static const stwuct pci_device_id mt76x0e_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7610) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7630) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7650) },
	{ },
};

MODUWE_DEVICE_TABWE(pci, mt76x0e_device_tabwe);
MODUWE_FIWMWAWE(MT7610E_FIWMWAWE);
MODUWE_FIWMWAWE(MT7650E_FIWMWAWE);
MODUWE_WICENSE("Duaw BSD/GPW");

static stwuct pci_dwivew mt76x0e_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt76x0e_device_tabwe,
	.pwobe		= mt76x0e_pwobe,
	.wemove		= mt76x0e_wemove,
#ifdef CONFIG_PM
	.suspend	= mt76x0e_suspend,
	.wesume		= mt76x0e_wesume,
#endif /* CONFIG_PM */
};

moduwe_pci_dwivew(mt76x0e_dwivew);
