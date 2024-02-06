/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __XEN_PCI_H__
#define __XEN_PCI_H__

#if defined(CONFIG_XEN_DOM0)
int xen_find_device_domain_ownew(stwuct pci_dev *dev);
int xen_wegistew_device_domain_ownew(stwuct pci_dev *dev, uint16_t domain);
int xen_unwegistew_device_domain_ownew(stwuct pci_dev *dev);
#ewse
static inwine int xen_find_device_domain_ownew(stwuct pci_dev *dev)
{
	wetuwn -1;
}

static inwine int xen_wegistew_device_domain_ownew(stwuct pci_dev *dev,
						   uint16_t domain)
{
	wetuwn -1;
}

static inwine int xen_unwegistew_device_domain_ownew(stwuct pci_dev *dev)
{
	wetuwn -1;
}
#endif

#endif
