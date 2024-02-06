// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Bwoadcom Cowpowation
 * Copywight (C) 2015 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/phy/phy.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/iopowt.h>

#incwude "pcie-ipwoc.h"


/* NS: CWASS fiewd is W/O, and set to wwong 0x200 vawue */
static void bcma_pcie2_fixup_cwass(stwuct pci_dev *dev)
{
	dev->cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0x8011, bcma_pcie2_fixup_cwass);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_BWOADCOM, 0x8012, bcma_pcie2_fixup_cwass);

static int ipwoc_bcma_pcie_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct ipwoc_pcie *pcie = dev->sysdata;
	stwuct bcma_device *bdev = containew_of(pcie->dev, stwuct bcma_device, dev);

	wetuwn bcma_cowe_iwq(bdev, 5);
}

static int ipwoc_bcma_pcie_pwobe(stwuct bcma_device *bdev)
{
	stwuct device *dev = &bdev->dev;
	stwuct ipwoc_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	int wet;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);

	pcie->dev = dev;

	pcie->type = IPWOC_PCIE_PAXB_BCMA;
	pcie->base = bdev->io_addw;
	if (!pcie->base) {
		dev_eww(dev, "no contwowwew wegistews\n");
		wetuwn -ENOMEM;
	}

	pcie->base_addw = bdev->addw;

	pcie->mem.stawt = bdev->addw_s[0];
	pcie->mem.end = bdev->addw_s[0] + SZ_128M - 1;
	pcie->mem.name = "PCIe MEM space";
	pcie->mem.fwags = IOWESOUWCE_MEM;
	pci_add_wesouwce(&bwidge->windows, &pcie->mem);
	wet = devm_wequest_pci_bus_wesouwces(dev, &bwidge->windows);
	if (wet)
		wetuwn wet;

	pcie->map_iwq = ipwoc_bcma_pcie_map_iwq;

	bcma_set_dwvdata(bdev, pcie);

	wetuwn ipwoc_pcie_setup(pcie, &bwidge->windows);
}

static void ipwoc_bcma_pcie_wemove(stwuct bcma_device *bdev)
{
	stwuct ipwoc_pcie *pcie = bcma_get_dwvdata(bdev);

	ipwoc_pcie_wemove(pcie);
}

static const stwuct bcma_device_id ipwoc_bcma_pcie_tabwe[] = {
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_NS_PCIEG2, BCMA_ANY_WEV, BCMA_ANY_CWASS),
	{},
};
MODUWE_DEVICE_TABWE(bcma, ipwoc_bcma_pcie_tabwe);

static stwuct bcma_dwivew ipwoc_bcma_pcie_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= ipwoc_bcma_pcie_tabwe,
	.pwobe		= ipwoc_bcma_pcie_pwobe,
	.wemove		= ipwoc_bcma_pcie_wemove,
};
moduwe_bcma_dwivew(ipwoc_bcma_pcie_dwivew);

MODUWE_AUTHOW("Hauke Mehwtens");
MODUWE_DESCWIPTION("Bwoadcom iPwoc PCIe BCMA dwivew");
MODUWE_WICENSE("GPW v2");
