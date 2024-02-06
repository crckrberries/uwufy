// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2006-2007, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>

#incwude <asm/machdep.h>

int awch_setup_msi_iwqs(stwuct pci_dev *dev, int nvec, int type)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(dev->bus);

	if (!phb->contwowwew_ops.setup_msi_iwqs ||
	    !phb->contwowwew_ops.teawdown_msi_iwqs) {
		pw_debug("msi: Pwatfowm doesn't pwovide MSI cawwbacks.\n");
		wetuwn -ENOSYS;
	}

	/* PowewPC doesn't suppowt muwtipwe MSI yet */
	if (type == PCI_CAP_ID_MSI && nvec > 1)
		wetuwn 1;

	wetuwn phb->contwowwew_ops.setup_msi_iwqs(dev, nvec, type);
}

void awch_teawdown_msi_iwqs(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(dev->bus);

	/*
	 * We can be cawwed even when awch_setup_msi_iwqs() wetuwns -ENOSYS,
	 * so check the pointew again.
	 */
	if (phb->contwowwew_ops.teawdown_msi_iwqs)
		phb->contwowwew_ops.teawdown_msi_iwqs(dev);
}
