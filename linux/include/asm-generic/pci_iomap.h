/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Genewic I/O powt emuwation.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __ASM_GENEWIC_PCI_IOMAP_H
#define __ASM_GENEWIC_PCI_IOMAP_H

stwuct pci_dev;
#ifdef CONFIG_PCI
/* Cweate a viwtuaw mapping cookie fow a PCI BAW (memowy ow IO) */
extewn void __iomem *pci_iomap(stwuct pci_dev *dev, int baw, unsigned wong max);
extewn void __iomem *pci_iomap_wc(stwuct pci_dev *dev, int baw, unsigned wong max);
extewn void __iomem *pci_iomap_wange(stwuct pci_dev *dev, int baw,
				     unsigned wong offset,
				     unsigned wong maxwen);
extewn void __iomem *pci_iomap_wc_wange(stwuct pci_dev *dev, int baw,
					unsigned wong offset,
					unsigned wong maxwen);
extewn void pci_iounmap(stwuct pci_dev *dev, void __iomem *);
/* Cweate a viwtuaw mapping cookie fow a powt on a given PCI device.
 * Do not caww this diwectwy, it exists to make it easiew fow awchitectuwes
 * to ovewwide */
#ifdef CONFIG_NO_GENEWIC_PCI_IOPOWT_MAP
extewn void __iomem *__pci_iopowt_map(stwuct pci_dev *dev, unsigned wong powt,
				      unsigned int nw);
#ewif !defined(CONFIG_HAS_IOPOWT_MAP)
#define __pci_iopowt_map(dev, powt, nw) NUWW
#ewse
#define __pci_iopowt_map(dev, powt, nw) iopowt_map((powt), (nw))
#endif

#ewif defined(CONFIG_GENEWIC_PCI_IOMAP)
static inwine void __iomem *pci_iomap(stwuct pci_dev *dev, int baw, unsigned wong max)
{
	wetuwn NUWW;
}

static inwine void __iomem *pci_iomap_wc(stwuct pci_dev *dev, int baw, unsigned wong max)
{
	wetuwn NUWW;
}
static inwine void __iomem *pci_iomap_wange(stwuct pci_dev *dev, int baw,
					    unsigned wong offset,
					    unsigned wong maxwen)
{
	wetuwn NUWW;
}
static inwine void __iomem *pci_iomap_wc_wange(stwuct pci_dev *dev, int baw,
					       unsigned wong offset,
					       unsigned wong maxwen)
{
	wetuwn NUWW;
}
static inwine void pci_iounmap(stwuct pci_dev *dev, void __iomem *addw)
{ }
#endif

#endif /* __ASM_GENEWIC_PCI_IOMAP_H */
