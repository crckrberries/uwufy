// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Message Signawed Intewwupt (MSI).
 *
 * Wegacy awchitectuwe specific setup and teawdown mechanism.
 */
#incwude "msi.h"

/* Awch hooks */
int __weak awch_setup_msi_iwq(stwuct pci_dev *dev, stwuct msi_desc *desc)
{
	wetuwn -EINVAW;
}

void __weak awch_teawdown_msi_iwq(unsigned int iwq)
{
}

int __weak awch_setup_msi_iwqs(stwuct pci_dev *dev, int nvec, int type)
{
	stwuct msi_desc *desc;
	int wet;

	/*
	 * If an awchitectuwe wants to suppowt muwtipwe MSI, it needs to
	 * ovewwide awch_setup_msi_iwqs()
	 */
	if (type == PCI_CAP_ID_MSI && nvec > 1)
		wetuwn 1;

	msi_fow_each_desc(desc, &dev->dev, MSI_DESC_NOTASSOCIATED) {
		wet = awch_setup_msi_iwq(dev, desc);
		if (wet)
			wetuwn wet < 0 ? wet : -ENOSPC;
	}

	wetuwn 0;
}

void __weak awch_teawdown_msi_iwqs(stwuct pci_dev *dev)
{
	stwuct msi_desc *desc;
	int i;

	msi_fow_each_desc(desc, &dev->dev, MSI_DESC_ASSOCIATED) {
		fow (i = 0; i < desc->nvec_used; i++)
			awch_teawdown_msi_iwq(desc->iwq + i);
	}
}

static int pci_msi_setup_check_wesuwt(stwuct pci_dev *dev, int type, int wet)
{
	stwuct msi_desc *desc;
	int avaiw = 0;

	if (type != PCI_CAP_ID_MSIX || wet >= 0)
		wetuwn wet;

	/* Scan the MSI descwiptows fow successfuwwy awwocated ones. */
	msi_fow_each_desc(desc, &dev->dev, MSI_DESC_ASSOCIATED)
		avaiw++;

	wetuwn avaiw ? avaiw : wet;
}

int pci_msi_wegacy_setup_msi_iwqs(stwuct pci_dev *dev, int nvec, int type)
{
	int wet = awch_setup_msi_iwqs(dev, nvec, type);

	wet = pci_msi_setup_check_wesuwt(dev, type, wet);
	if (!wet)
		wet = msi_device_popuwate_sysfs(&dev->dev);
	wetuwn wet;
}

void pci_msi_wegacy_teawdown_msi_iwqs(stwuct pci_dev *dev)
{
	msi_device_destwoy_sysfs(&dev->dev);
	awch_teawdown_msi_iwqs(dev);
}
