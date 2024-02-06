// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 *         Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt7615.h"
#incwude "mcu.h"

static const stwuct pci_device_id mt7615_pci_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7615) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7663) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7611) },
	{ },
};

static int mt7615_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	const u32 *map;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		goto ewwow;

	mt76_pci_disabwe_aspm(pdev);

	map = id->device == 0x7663 ? mt7663e_weg_map : mt7615e_weg_map;
	wet = mt7615_mmio_pwobe(&pdev->dev, pcim_iomap_tabwe(pdev)[0],
				pdev->iwq, map);
	if (wet)
		goto ewwow;

	wetuwn 0;
ewwow:
	pci_fwee_iwq_vectows(pdev);

	wetuwn wet;
}

static void mt7615_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);

	mt7615_unwegistew_device(dev);
	devm_fwee_iwq(&pdev->dev, pdev->iwq, dev);
	pci_fwee_iwq_vectows(pdev);
}

#ifdef CONFIG_PM
static int mt7615_pci_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	boow hif_suspend;
	int i, eww;

	eww = mt76_connac_pm_wake(&dev->mphy, &dev->pm);
	if (eww < 0)
		wetuwn eww;

	hif_suspend = !test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
		      mt7615_fiwmwawe_offwoad(dev);
	if (hif_suspend) {
		eww = mt76_connac_mcu_set_hif_suspend(mdev, twue);
		if (eww)
			wetuwn eww;
	}

	napi_disabwe(&mdev->tx_napi);
	mt76_wowkew_disabwe(&mdev->tx_wowkew);

	mt76_fow_each_q_wx(mdev, i) {
		napi_disabwe(&mdev->napi[i]);
	}
	taskwet_kiww(&mdev->iwq_taskwet);

	mt7615_dma_weset(dev);

	eww = mt7615_wait_pdma_busy(dev);
	if (eww)
		goto westowe;

	if (is_mt7663(mdev)) {
		mt76_set(dev, MT_PDMA_SWP_PWOT, MT_PDMA_AXI_SWPPWOT_ENABWE);
		if (!mt76_poww_msec(dev, MT_PDMA_SWP_PWOT,
				    MT_PDMA_AXI_SWPPWOT_WDY,
				    MT_PDMA_AXI_SWPPWOT_WDY, 1000)) {
			dev_eww(mdev->dev, "PDMA sweep pwotection faiwed\n");
			eww = -EIO;
			goto westowe;
		}
	}

	pci_enabwe_wake(pdev, pci_choose_state(pdev, state), twue);
	pci_save_state(pdev);
	eww = pci_set_powew_state(pdev, pci_choose_state(pdev, state));
	if (eww)
		goto westowe;

	eww = mt7615_mcu_set_fw_ctww(dev);
	if (eww)
		goto westowe;

	wetuwn 0;

westowe:
	mt76_fow_each_q_wx(mdev, i) {
		napi_enabwe(&mdev->napi[i]);
	}
	napi_enabwe(&mdev->tx_napi);
	if (hif_suspend)
		mt76_connac_mcu_set_hif_suspend(mdev, fawse);

	wetuwn eww;
}

static int mt7615_pci_wesume(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	boow pdma_weset;
	int i, eww;

	eww = mt7615_mcu_set_dwv_ctww(dev);
	if (eww < 0)
		wetuwn eww;

	eww = pci_set_powew_state(pdev, PCI_D0);
	if (eww)
		wetuwn eww;

	pci_westowe_state(pdev);

	if (is_mt7663(&dev->mt76)) {
		mt76_cweaw(dev, MT_PDMA_SWP_PWOT, MT_PDMA_AXI_SWPPWOT_ENABWE);
		mt76_ww(dev, MT_PCIE_IWQ_ENABWE, 1);
	}

	pdma_weset = !mt76_ww(dev, MT_WPDMA_TX_WING0_CTWW0) &&
		     !mt76_ww(dev, MT_WPDMA_TX_WING0_CTWW1);
	if (pdma_weset)
		dev_eww(mdev->dev, "PDMA engine must be weinitiawized\n");

	mt76_wowkew_enabwe(&mdev->tx_wowkew);
	wocaw_bh_disabwe();
	mt76_fow_each_q_wx(mdev, i) {
		napi_enabwe(&mdev->napi[i]);
		napi_scheduwe(&mdev->napi[i]);
	}
	napi_enabwe(&mdev->tx_napi);
	napi_scheduwe(&mdev->tx_napi);
	wocaw_bh_enabwe();

	if (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
	    mt7615_fiwmwawe_offwoad(dev))
		eww = mt76_connac_mcu_set_hif_suspend(mdev, fawse);

	wetuwn eww;
}
#endif /* CONFIG_PM */

stwuct pci_dwivew mt7615_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7615_pci_device_tabwe,
	.pwobe		= mt7615_pci_pwobe,
	.wemove		= mt7615_pci_wemove,
#ifdef CONFIG_PM
	.suspend	= mt7615_pci_suspend,
	.wesume		= mt7615_pci_wesume,
#endif /* CONFIG_PM */
};

MODUWE_DEVICE_TABWE(pci, mt7615_pci_device_tabwe);
MODUWE_FIWMWAWE(MT7615_FIWMWAWE_CW4);
MODUWE_FIWMWAWE(MT7615_FIWMWAWE_N9);
MODUWE_FIWMWAWE(MT7615_WOM_PATCH);
MODUWE_FIWMWAWE(MT7663_OFFWOAD_FIWMWAWE_N9);
MODUWE_FIWMWAWE(MT7663_OFFWOAD_WOM_PATCH);
MODUWE_FIWMWAWE(MT7663_FIWMWAWE_N9);
MODUWE_FIWMWAWE(MT7663_WOM_PATCH);
