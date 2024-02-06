// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/of_pci.h>
#incwude <winux/pci.h>

int (*wtq_pci_pwat_awch_init)(stwuct pci_dev *dev) = NUWW;
int (*wtq_pci_pwat_dev_init)(stwuct pci_dev *dev) = NUWW;

int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	if (wtq_pci_pwat_awch_init)
		wetuwn wtq_pci_pwat_awch_init(dev);

	if (wtq_pci_pwat_dev_init)
		wetuwn wtq_pci_pwat_dev_init(dev);

	wetuwn 0;
}

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn of_iwq_pawse_and_map_pci(dev, swot, pin);
}
