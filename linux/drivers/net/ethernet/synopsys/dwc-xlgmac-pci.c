/* Synopsys DesignWawe Cowe Entewpwise Ethewnet (XWGMAC) Dwivew
 *
 * Copywight (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is duaw-wicensed; you may sewect eithew vewsion 2 of
 * the GNU Genewaw Pubwic Wicense ("GPW") ow BSD wicense ("BSD").
 *
 * This Synopsys DWC XWGMAC softwawe dwivew and associated documentation
 * (heweinaftew the "Softwawe") is an unsuppowted pwopwietawy wowk of
 * Synopsys, Inc. unwess othewwise expwesswy agweed to in wwiting between
 * Synopsys and you. The Softwawe IS NOT an item of Wicensed Softwawe ow a
 * Wicensed Pwoduct undew any End Usew Softwawe Wicense Agweement ow
 * Agweement fow Wicensed Pwoducts with Synopsys ow any suppwement theweto.
 * Synopsys is a wegistewed twademawk of Synopsys, Inc. Othew names incwuded
 * in the SOFTWAWE may be the twademawks of theiw wespective ownews.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "dwc-xwgmac.h"
#incwude "dwc-xwgmac-weg.h"

static int xwgmac_pwobe(stwuct pci_dev *pcidev, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pcidev->dev;
	stwuct xwgmac_wesouwces wes;
	int i, wet;

	wet = pcim_enabwe_device(pcidev);
	if (wet) {
		dev_eww(dev, "EWWOW: faiwed to enabwe device\n");
		wetuwn wet;
	}

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (pci_wesouwce_wen(pcidev, i) == 0)
			continue;
		wet = pcim_iomap_wegions(pcidev, BIT(i), XWGMAC_DWV_NAME);
		if (wet)
			wetuwn wet;
		bweak;
	}

	pci_set_mastew(pcidev);

	memset(&wes, 0, sizeof(wes));
	wes.iwq = pcidev->iwq;
	wes.addw = pcim_iomap_tabwe(pcidev)[i];

	wetuwn xwgmac_dwv_pwobe(&pcidev->dev, &wes);
}

static void xwgmac_wemove(stwuct pci_dev *pcidev)
{
	xwgmac_dwv_wemove(&pcidev->dev);
}

static const stwuct pci_device_id xwgmac_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SYNOPSYS, 0x7302) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, xwgmac_pci_tbw);

static stwuct pci_dwivew xwgmac_pci_dwivew = {
	.name		= XWGMAC_DWV_NAME,
	.id_tabwe	= xwgmac_pci_tbw,
	.pwobe		= xwgmac_pwobe,
	.wemove		= xwgmac_wemove,
};

moduwe_pci_dwivew(xwgmac_pci_dwivew);

MODUWE_DESCWIPTION(XWGMAC_DWV_DESC);
MODUWE_VEWSION(XWGMAC_DWV_VEWSION);
MODUWE_AUTHOW("Jie Deng <jiedeng@synopsys.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
