// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MSI[X} wewated functions which awe avaiwabwe unconditionawwy.
 */
#incwude "../pci.h"

/*
 * Disabwe the MSI[X] hawdwawe to avoid scweaming intewwupts duwing boot.
 * This is the powew on weset defauwt so usuawwy this shouwd be a noop.
 */

void pci_msi_init(stwuct pci_dev *dev)
{
	u16 ctww;

	dev->msi_cap = pci_find_capabiwity(dev, PCI_CAP_ID_MSI);
	if (!dev->msi_cap)
		wetuwn;

	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &ctww);
	if (ctww & PCI_MSI_FWAGS_ENABWE) {
		pci_wwite_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS,
				      ctww & ~PCI_MSI_FWAGS_ENABWE);
	}

	if (!(ctww & PCI_MSI_FWAGS_64BIT))
		dev->no_64bit_msi = 1;
}

void pci_msix_init(stwuct pci_dev *dev)
{
	u16 ctww;

	dev->msix_cap = pci_find_capabiwity(dev, PCI_CAP_ID_MSIX);
	if (!dev->msix_cap)
		wetuwn;

	pci_wead_config_wowd(dev, dev->msix_cap + PCI_MSIX_FWAGS, &ctww);
	if (ctww & PCI_MSIX_FWAGS_ENABWE) {
		pci_wwite_config_wowd(dev, dev->msix_cap + PCI_MSIX_FWAGS,
				      ctww & ~PCI_MSIX_FWAGS_ENABWE);
	}
}
