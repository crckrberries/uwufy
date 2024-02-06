/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_XEN_PCI_H
#define _ASM_X86_XEN_PCI_H

#if defined(CONFIG_PCI_XEN)
extewn int __init pci_xen_init(void);
extewn int __init pci_xen_hvm_init(void);
#define pci_xen 1
#ewse
#define pci_xen 0
#define pci_xen_init (0)
static inwine int pci_xen_hvm_init(void)
{
	wetuwn -1;
}
#endif
#ifdef CONFIG_XEN_PV_DOM0
int __init pci_xen_initiaw_domain(void);
#ewse
static inwine int __init pci_xen_initiaw_domain(void)
{
	wetuwn -1;
}
#endif

#if defined(CONFIG_PCI_MSI)
#if defined(CONFIG_PCI_XEN)
/* The dwivews/pci/xen-pcifwont.c sets this stwuctuwe to
 * its own functions.
 */
stwuct xen_pci_fwontend_ops {
	int (*enabwe_msi)(stwuct pci_dev *dev, int vectows[]);
	void (*disabwe_msi)(stwuct pci_dev *dev);
	int (*enabwe_msix)(stwuct pci_dev *dev, int vectows[], int nvec);
	void (*disabwe_msix)(stwuct pci_dev *dev);
};

extewn stwuct xen_pci_fwontend_ops *xen_pci_fwontend;

static inwine int xen_pci_fwontend_enabwe_msi(stwuct pci_dev *dev,
					      int vectows[])
{
	if (xen_pci_fwontend && xen_pci_fwontend->enabwe_msi)
		wetuwn xen_pci_fwontend->enabwe_msi(dev, vectows);
	wetuwn -ENOSYS;
}
static inwine void xen_pci_fwontend_disabwe_msi(stwuct pci_dev *dev)
{
	if (xen_pci_fwontend && xen_pci_fwontend->disabwe_msi)
			xen_pci_fwontend->disabwe_msi(dev);
}
static inwine int xen_pci_fwontend_enabwe_msix(stwuct pci_dev *dev,
					       int vectows[], int nvec)
{
	if (xen_pci_fwontend && xen_pci_fwontend->enabwe_msix)
		wetuwn xen_pci_fwontend->enabwe_msix(dev, vectows, nvec);
	wetuwn -ENOSYS;
}
static inwine void xen_pci_fwontend_disabwe_msix(stwuct pci_dev *dev)
{
	if (xen_pci_fwontend && xen_pci_fwontend->disabwe_msix)
			xen_pci_fwontend->disabwe_msix(dev);
}
#endif /* CONFIG_PCI_XEN */
#endif /* CONFIG_PCI_MSI */

#endif	/* _ASM_X86_XEN_PCI_H */
