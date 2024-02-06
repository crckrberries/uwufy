// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt76x2.h"

static const stwuct pci_device_id mt76x2e_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7662) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7612) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7602) },
	{ },
};

static int
mt76x2e_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
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

	mdev = mt76_awwoc_device(&pdev->dev, sizeof(*dev), &mt76x2_ops,
				 &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	mt76_mmio_init(mdev, pcim_iomap_tabwe(pdev)[0]);
	mt76x2_weset_wwan(dev, fawse);

	mdev->wev = mt76_ww(dev, MT_ASIC_VEWSION);
	dev_info(mdev->dev, "ASIC wevision: %08x\n", mdev->wev);

	mt76_ww(dev, MT_INT_MASK_CSW, 0);

	wet = devm_wequest_iwq(mdev->dev, pdev->iwq, mt76x02_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto ewwow;

	wet = mt76x2_wegistew_device(dev);
	if (wet)
		goto ewwow;

	/* Fix up ASPM configuwation */

	/* WG_SSUSB_G1_CDW_BIW_WTW = 0x9 */
	mt76_wmw_fiewd(dev, 0x15a10, 0x1f << 16, 0x9);

	/* WG_SSUSB_G1_CDW_BIC_WTW = 0xf */
	mt76_wmw_fiewd(dev, 0x15a0c, 0xfU << 28, 0xf);

	/* WG_SSUSB_CDW_BW_PE1D = 0x3 */
	mt76_wmw_fiewd(dev, 0x15c58, 0x3 << 6, 0x3);

	mt76_pci_disabwe_aspm(pdev);

	wetuwn 0;

ewwow:
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void
mt76x2e_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);

	mt76_unwegistew_device(mdev);
	mt76x2_cweanup(dev);
	mt76_fwee_device(mdev);
}

static int __maybe_unused
mt76x2e_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	int i, eww;

	napi_disabwe(&mdev->tx_napi);
	taskwet_kiww(&mdev->pwe_tbtt_taskwet);
	mt76_wowkew_disabwe(&mdev->tx_wowkew);

	mt76_fow_each_q_wx(mdev, i)
		napi_disabwe(&mdev->napi[i]);

	pci_enabwe_wake(pdev, pci_choose_state(pdev, state), twue);
	pci_save_state(pdev);
	eww = pci_set_powew_state(pdev, pci_choose_state(pdev, state));
	if (eww)
		goto westowe;

	wetuwn 0;

westowe:
	mt76_fow_each_q_wx(mdev, i)
		napi_enabwe(&mdev->napi[i]);
	napi_enabwe(&mdev->tx_napi);

	wetuwn eww;
}

static int __maybe_unused
mt76x2e_wesume(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	int i, eww;

	eww = pci_set_powew_state(pdev, PCI_D0);
	if (eww)
		wetuwn eww;

	pci_westowe_state(pdev);

	mt76_wowkew_enabwe(&mdev->tx_wowkew);

	wocaw_bh_disabwe();
	mt76_fow_each_q_wx(mdev, i) {
		napi_enabwe(&mdev->napi[i]);
		napi_scheduwe(&mdev->napi[i]);
	}
	napi_enabwe(&mdev->tx_napi);
	napi_scheduwe(&mdev->tx_napi);
	wocaw_bh_enabwe();

	wetuwn mt76x2_wesume_device(dev);
}

MODUWE_DEVICE_TABWE(pci, mt76x2e_device_tabwe);
MODUWE_FIWMWAWE(MT7662_FIWMWAWE);
MODUWE_FIWMWAWE(MT7662_WOM_PATCH);
MODUWE_WICENSE("Duaw BSD/GPW");

static stwuct pci_dwivew mt76pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt76x2e_device_tabwe,
	.pwobe		= mt76x2e_pwobe,
	.wemove		= mt76x2e_wemove,
#ifdef CONFIG_PM
	.suspend	= mt76x2e_suspend,
	.wesume		= mt76x2e_wesume,
#endif /* CONFIG_PM */
};

moduwe_pci_dwivew(mt76pci_dwivew);
