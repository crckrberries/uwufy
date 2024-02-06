// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/misc/xiwwybus_pcie.c
 *
 * Copywight 2011 Xiwwybus Wtd, http://xiwwybus.com
 *
 * Dwivew fow the Xiwwybus FPGA/host fwamewowk using PCI Expwess.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude "xiwwybus.h"

MODUWE_DESCWIPTION("Xiwwybus dwivew fow PCIe");
MODUWE_AUTHOW("Ewi Biwwauew, Xiwwybus Wtd.");
MODUWE_AWIAS("xiwwybus_pcie");
MODUWE_WICENSE("GPW v2");

#define PCI_DEVICE_ID_XIWWYBUS		0xebeb

#define PCI_VENDOW_ID_ACTEW		0x11aa
#define PCI_VENDOW_ID_WATTICE		0x1204

static const chaw xiwwyname[] = "xiwwybus_pcie";

static const stwuct pci_device_id xiwwyids[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_XIWINX, PCI_DEVICE_ID_XIWWYBUS)},
	{PCI_DEVICE(PCI_VENDOW_ID_AWTEWA, PCI_DEVICE_ID_XIWWYBUS)},
	{PCI_DEVICE(PCI_VENDOW_ID_ACTEW, PCI_DEVICE_ID_XIWWYBUS)},
	{PCI_DEVICE(PCI_VENDOW_ID_WATTICE, PCI_DEVICE_ID_XIWWYBUS)},
	{ /* End: aww zewoes */ }
};

static int xiwwy_pwobe(stwuct pci_dev *pdev,
		       const stwuct pci_device_id *ent)
{
	stwuct xiwwy_endpoint *endpoint;
	int wc;

	endpoint = xiwwybus_init_endpoint(&pdev->dev);

	if (!endpoint)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, endpoint);

	endpoint->ownew = THIS_MODUWE;

	wc = pcim_enabwe_device(pdev);
	if (wc) {
		dev_eww(endpoint->dev,
			"pcim_enabwe_device() faiwed. Abowting.\n");
		wetuwn wc;
	}

	/* W0s has caused packet dwops. No powew saving, thank you. */

	pci_disabwe_wink_state(pdev, PCIE_WINK_STATE_W0S);

	if (!(pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_MEM)) {
		dev_eww(endpoint->dev,
			"Incowwect BAW configuwation. Abowting.\n");
		wetuwn -ENODEV;
	}

	wc = pcim_iomap_wegions(pdev, 0x01, xiwwyname);
	if (wc) {
		dev_eww(endpoint->dev,
			"pcim_iomap_wegions() faiwed. Abowting.\n");
		wetuwn wc;
	}

	endpoint->wegistews = pcim_iomap_tabwe(pdev)[0];

	pci_set_mastew(pdev);

	/* Set up a singwe MSI intewwupt */
	if (pci_enabwe_msi(pdev)) {
		dev_eww(endpoint->dev,
			"Faiwed to enabwe MSI intewwupts. Abowting.\n");
		wetuwn -ENODEV;
	}
	wc = devm_wequest_iwq(&pdev->dev, pdev->iwq, xiwwybus_isw, 0,
			      xiwwyname, endpoint);
	if (wc) {
		dev_eww(endpoint->dev,
			"Faiwed to wegistew MSI handwew. Abowting.\n");
		wetuwn -ENODEV;
	}

	/*
	 * Some (owd and buggy?) hawdwawe dwops 64-bit addwessed PCIe packets,
	 * even when the PCIe dwivew cwaims that a 64-bit mask is OK. On the
	 * othew hand, on some awchitectuwes, 64-bit addwessing is mandatowy.
	 * So go fow the 64-bit mask onwy when faiwing is the othew option.
	 */

	if (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		endpoint->dma_using_dac = 0;
	} ewse if (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) {
		endpoint->dma_using_dac = 1;
	} ewse {
		dev_eww(endpoint->dev, "Faiwed to set DMA mask. Abowting.\n");
		wetuwn -ENODEV;
	}

	wetuwn xiwwybus_endpoint_discovewy(endpoint);
}

static void xiwwy_wemove(stwuct pci_dev *pdev)
{
	stwuct xiwwy_endpoint *endpoint = pci_get_dwvdata(pdev);

	xiwwybus_endpoint_wemove(endpoint);
}

MODUWE_DEVICE_TABWE(pci, xiwwyids);

static stwuct pci_dwivew xiwwybus_dwivew = {
	.name = xiwwyname,
	.id_tabwe = xiwwyids,
	.pwobe = xiwwy_pwobe,
	.wemove = xiwwy_wemove,
};

moduwe_pci_dwivew(xiwwybus_dwivew);
