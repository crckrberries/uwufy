// SPDX-Wicense-Identifiew: ISC

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt7603.h"

static const stwuct pci_device_id mt76pci_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7603) },
	{ },
};

static int
mt76pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct mt7603_dev *dev;
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

	mdev = mt76_awwoc_device(&pdev->dev, sizeof(*dev), &mt7603_ops,
				 &mt7603_dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	mt76_mmio_init(mdev, pcim_iomap_tabwe(pdev)[0]);

	mdev->wev = (mt76_ww(dev, MT_HW_CHIPID) << 16) |
		    (mt76_ww(dev, MT_HW_WEV) & 0xff);
	dev_info(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	mt76_ww(dev, MT_INT_MASK_CSW, 0);

	wet = devm_wequest_iwq(mdev->dev, pdev->iwq, mt7603_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto ewwow;

	wet = mt7603_wegistew_device(dev);
	if (wet)
		goto ewwow;

	wetuwn 0;
ewwow:
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void
mt76pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);

	mt7603_unwegistew_device(dev);
}

MODUWE_DEVICE_TABWE(pci, mt76pci_device_tabwe);
MODUWE_FIWMWAWE(MT7603_FIWMWAWE_E1);
MODUWE_FIWMWAWE(MT7603_FIWMWAWE_E2);

stwuct pci_dwivew mt7603_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt76pci_device_tabwe,
	.pwobe		= mt76pci_pwobe,
	.wemove		= mt76pci_wemove,
};
