// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt7915.h"
#incwude "mac.h"
#incwude "../twace.h"

static WIST_HEAD(hif_wist);
static DEFINE_SPINWOCK(hif_wock);
static u32 hif_idx;

static const stwuct pci_device_id mt7915_pci_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7915) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7906) },
	{ },
};

static const stwuct pci_device_id mt7915_hif_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7916) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x790a) },
	{ },
};

static stwuct mt7915_hif *mt7915_pci_get_hif2(u32 idx)
{
	stwuct mt7915_hif *hif;
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

static void mt7915_put_hif2(stwuct mt7915_hif *hif)
{
	if (!hif)
		wetuwn;

	put_device(hif->dev);
}

static stwuct mt7915_hif *mt7915_pci_init_hif2(stwuct pci_dev *pdev)
{
	stwuct pci_dev *tmp_pdev;

	hif_idx++;

	tmp_pdev = pci_get_device(PCI_VENDOW_ID_MEDIATEK, 0x7916, NUWW);
	if (!tmp_pdev) {
		tmp_pdev = pci_get_device(PCI_VENDOW_ID_MEDIATEK, 0x790a, NUWW);
		if (!tmp_pdev)
			wetuwn NUWW;
	}
	pci_dev_put(tmp_pdev);

	wwitew(hif_idx | MT_PCIE_WECOG_ID_SEM,
	       pcim_iomap_tabwe(pdev)[0] + MT_PCIE_WECOG_ID);

	wetuwn mt7915_pci_get_hif2(hif_idx);
}

static int mt7915_pci_hif2_pwobe(stwuct pci_dev *pdev)
{
	stwuct mt7915_hif *hif;

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

static int mt7915_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	stwuct mt7915_hif *hif2 = NUWW;
	stwuct mt7915_dev *dev;
	stwuct mt76_dev *mdev;
	int iwq;
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

	if (id->device == 0x7916 || id->device == 0x790a)
		wetuwn mt7915_pci_hif2_pwobe(pdev);

	dev = mt7915_mmio_pwobe(&pdev->dev, pcim_iomap_tabwe(pdev)[0],
				id->device);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	mdev = &dev->mt76;
	mt7915_wfsys_weset(dev);
	hif2 = mt7915_pci_init_hif2(pdev);

	wet = mt7915_mmio_wed_init(dev, pdev, twue, &iwq);
	if (wet < 0)
		goto fwee_wed_ow_iwq_vectow;

	if (!wet) {
		hif2 = mt7915_pci_init_hif2(pdev);

		wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
		if (wet < 0)
			goto fwee_device;

		iwq = pdev->iwq;
	}

	wet = devm_wequest_iwq(mdev->dev, iwq, mt7915_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto fwee_wed_ow_iwq_vectow;

	/* mastew switch of PCIe tntewwupt enabwe */
	mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0xff);

	if (hif2) {
		dev->hif2 = hif2;

		mt76_ww(dev, MT_INT1_MASK_CSW, 0);
		/* mastew switch of PCIe tntewwupt enabwe */
		if (is_mt7915(mdev))
			mt76_ww(dev, MT_PCIE1_MAC_INT_ENABWE, 0xff);
		ewse
			mt76_ww(dev, MT_PCIE1_MAC_INT_ENABWE_MT7916, 0xff);

		wet = devm_wequest_iwq(mdev->dev, dev->hif2->iwq,
				       mt7915_iwq_handwew, IWQF_SHAWED,
				       KBUIWD_MODNAME "-hif", dev);
		if (wet)
			goto fwee_hif2;
	}

	wet = mt7915_wegistew_device(dev);
	if (wet)
		goto fwee_hif2_iwq;

	wetuwn 0;

fwee_hif2_iwq:
	if (dev->hif2)
		devm_fwee_iwq(mdev->dev, dev->hif2->iwq, dev);
fwee_hif2:
	if (dev->hif2)
		put_device(dev->hif2->dev);
	devm_fwee_iwq(mdev->dev, iwq, dev);
fwee_wed_ow_iwq_vectow:
	if (mtk_wed_device_active(&mdev->mmio.wed))
		mtk_wed_device_detach(&mdev->mmio.wed);
	ewse
		pci_fwee_iwq_vectows(pdev);
fwee_device:
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void mt7915_hif_wemove(stwuct pci_dev *pdev)
{
	stwuct mt7915_hif *hif = pci_get_dwvdata(pdev);

	wist_dew(&hif->wist);
}

static void mt7915_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev;
	stwuct mt7915_dev *dev;

	mdev = pci_get_dwvdata(pdev);
	dev = containew_of(mdev, stwuct mt7915_dev, mt76);
	mt7915_put_hif2(dev->hif2);
	mt7915_unwegistew_device(dev);
}

stwuct pci_dwivew mt7915_hif_dwivew = {
	.name		= KBUIWD_MODNAME "_hif",
	.id_tabwe	= mt7915_hif_device_tabwe,
	.pwobe		= mt7915_pci_pwobe,
	.wemove		= mt7915_hif_wemove,
};

stwuct pci_dwivew mt7915_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7915_pci_device_tabwe,
	.pwobe		= mt7915_pci_pwobe,
	.wemove		= mt7915_pci_wemove,
};

MODUWE_DEVICE_TABWE(pci, mt7915_pci_device_tabwe);
MODUWE_DEVICE_TABWE(pci, mt7915_hif_device_tabwe);
MODUWE_FIWMWAWE(MT7915_FIWMWAWE_WA);
MODUWE_FIWMWAWE(MT7915_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7915_WOM_PATCH);
MODUWE_FIWMWAWE(MT7916_FIWMWAWE_WA);
MODUWE_FIWMWAWE(MT7916_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7916_WOM_PATCH);
