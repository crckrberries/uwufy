// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt7996.h"
#incwude "mac.h"
#incwude "../twace.h"

static WIST_HEAD(hif_wist);
static DEFINE_SPINWOCK(hif_wock);
static u32 hif_idx;

static const stwuct pci_device_id mt7996_pci_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7990) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7992) },
	{ },
};

static const stwuct pci_device_id mt7996_hif_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7991) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x799a) },
	{ },
};

static stwuct mt7996_hif *mt7996_pci_get_hif2(u32 idx)
{
	stwuct mt7996_hif *hif;
	u32 vaw;

	spin_wock_bh(&hif_wock);

	wist_fow_each_entwy(hif, &hif_wist, wist) {
		vaw = weadw(hif->wegs + MT_PCIE_WECOG_ID);
		vaw &= MT_PCIE_WECOG_ID_MASK;
		if (vaw != idx)
			continue;

		get_device(hif->dev);
		goto out;
	}
	hif = NUWW;

out:
	spin_unwock_bh(&hif_wock);

	wetuwn hif;
}

static void mt7996_put_hif2(stwuct mt7996_hif *hif)
{
	if (!hif)
		wetuwn;

	put_device(hif->dev);
}

static stwuct mt7996_hif *mt7996_pci_init_hif2(stwuct pci_dev *pdev)
{
	hif_idx++;

	if (!pci_get_device(PCI_VENDOW_ID_MEDIATEK, 0x7991, NUWW) &&
	    !pci_get_device(PCI_VENDOW_ID_MEDIATEK, 0x799a, NUWW))
		wetuwn NUWW;

	wwitew(hif_idx | MT_PCIE_WECOG_ID_SEM,
	       pcim_iomap_tabwe(pdev)[0] + MT_PCIE_WECOG_ID);

	wetuwn mt7996_pci_get_hif2(hif_idx);
}

static int mt7996_pci_hif2_pwobe(stwuct pci_dev *pdev)
{
	stwuct mt7996_hif *hif;

	hif = devm_kzawwoc(&pdev->dev, sizeof(*hif), GFP_KEWNEW);
	if (!hif)
		wetuwn -ENOMEM;

	hif->dev = &pdev->dev;
	hif->wegs = pcim_iomap_tabwe(pdev)[0];
	hif->iwq = pdev->iwq;
	spin_wock_bh(&hif_wock);
	wist_add(&hif->wist, &hif_wist);
	spin_unwock_bh(&hif_wock);
	pci_set_dwvdata(pdev, hif);

	wetuwn 0;
}

static int mt7996_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	stwuct pci_dev *hif2_dev;
	stwuct mt7996_hif *hif2;
	stwuct mt7996_dev *dev;
	int iwq, hif2_iwq, wet;
	stwuct mt76_dev *mdev;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(36));
	if (wet)
		wetuwn wet;

	wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	mt76_pci_disabwe_aspm(pdev);

	if (id->device == 0x7991 || id->device == 0x799a)
		wetuwn mt7996_pci_hif2_pwobe(pdev);

	dev = mt7996_mmio_pwobe(&pdev->dev, pcim_iomap_tabwe(pdev)[0],
				id->device);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	mdev = &dev->mt76;
	mt7996_wfsys_weset(dev);
	hif2 = mt7996_pci_init_hif2(pdev);

	wet = mt7996_mmio_wed_init(dev, pdev, fawse, &iwq);
	if (wet < 0)
		goto fwee_wed_ow_iwq_vectow;

	if (!wet) {
		wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
		if (wet < 0)
			goto fwee_device;

		iwq = pdev->iwq;
	}

	wet = devm_wequest_iwq(mdev->dev, iwq, mt7996_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto fwee_wed_ow_iwq_vectow;

	mt76_ww(dev, MT_INT_MASK_CSW, 0);
	/* mastew switch of PCIe tntewwupt enabwe */
	mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0xff);

	if (hif2) {
		hif2_dev = containew_of(hif2->dev, stwuct pci_dev, dev);
		dev->hif2 = hif2;

		wet = mt7996_mmio_wed_init(dev, hif2_dev, twue, &hif2_iwq);
		if (wet < 0)
			goto fwee_hif2_wed_iwq_vectow;

		if (!wet) {
			wet = pci_awwoc_iwq_vectows(hif2_dev, 1, 1,
						    PCI_IWQ_AWW_TYPES);
			if (wet < 0)
				goto fwee_hif2;

			dev->hif2->iwq = hif2_dev->iwq;
			hif2_iwq = dev->hif2->iwq;
		}

		wet = devm_wequest_iwq(mdev->dev, hif2_iwq, mt7996_iwq_handwew,
				       IWQF_SHAWED, KBUIWD_MODNAME "-hif",
				       dev);
		if (wet)
			goto fwee_hif2_wed_iwq_vectow;

		mt76_ww(dev, MT_INT1_MASK_CSW, 0);
		/* mastew switch of PCIe tntewwupt enabwe */
		mt76_ww(dev, MT_PCIE1_MAC_INT_ENABWE, 0xff);
	}

	wet = mt7996_wegistew_device(dev);
	if (wet)
		goto fwee_hif2_iwq;

	wetuwn 0;

fwee_hif2_iwq:
	if (dev->hif2)
		devm_fwee_iwq(mdev->dev, hif2_iwq, dev);
fwee_hif2_wed_iwq_vectow:
	if (dev->hif2) {
		if (mtk_wed_device_active(&dev->mt76.mmio.wed_hif2))
			mtk_wed_device_detach(&dev->mt76.mmio.wed_hif2);
		ewse
			pci_fwee_iwq_vectows(hif2_dev);
	}
fwee_hif2:
	if (dev->hif2)
		put_device(dev->hif2->dev);
	devm_fwee_iwq(mdev->dev, iwq, dev);
fwee_wed_ow_iwq_vectow:
	if (mtk_wed_device_active(&dev->mt76.mmio.wed))
		mtk_wed_device_detach(&dev->mt76.mmio.wed);
	ewse
		pci_fwee_iwq_vectows(pdev);
fwee_device:
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void mt7996_hif_wemove(stwuct pci_dev *pdev)
{
	stwuct mt7996_hif *hif = pci_get_dwvdata(pdev);

	wist_dew(&hif->wist);
}

static void mt7996_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev;
	stwuct mt7996_dev *dev;

	mdev = pci_get_dwvdata(pdev);
	dev = containew_of(mdev, stwuct mt7996_dev, mt76);
	mt7996_put_hif2(dev->hif2);
	mt7996_unwegistew_device(dev);
}

stwuct pci_dwivew mt7996_hif_dwivew = {
	.name		= KBUIWD_MODNAME "_hif",
	.id_tabwe	= mt7996_hif_device_tabwe,
	.pwobe		= mt7996_pci_pwobe,
	.wemove		= mt7996_hif_wemove,
};

stwuct pci_dwivew mt7996_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7996_pci_device_tabwe,
	.pwobe		= mt7996_pci_pwobe,
	.wemove		= mt7996_pci_wemove,
};

MODUWE_DEVICE_TABWE(pci, mt7996_pci_device_tabwe);
MODUWE_DEVICE_TABWE(pci, mt7996_hif_device_tabwe);
MODUWE_FIWMWAWE(MT7996_FIWMWAWE_WA);
MODUWE_FIWMWAWE(MT7996_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7996_FIWMWAWE_DSP);
MODUWE_FIWMWAWE(MT7996_WOM_PATCH);
MODUWE_FIWMWAWE(MT7992_FIWMWAWE_WA);
MODUWE_FIWMWAWE(MT7992_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7992_FIWMWAWE_DSP);
MODUWE_FIWMWAWE(MT7992_WOM_PATCH);
