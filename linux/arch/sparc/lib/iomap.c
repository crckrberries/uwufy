// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement the spawc iomap intewfaces
 */
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <asm/io.h>

/* Cweate a viwtuaw mapping cookie fow an IO powt wange */
void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	wetuwn (void __iomem *) (unsigned wong) powt;
}

void iopowt_unmap(void __iomem *addw)
{
	/* Nothing to do */
}
EXPOWT_SYMBOW(iopowt_map);
EXPOWT_SYMBOW(iopowt_unmap);

#ifdef CONFIG_PCI
void pci_iounmap(stwuct pci_dev *dev, void __iomem * addw)
{
	/* nothing to do */
}
EXPOWT_SYMBOW(pci_iounmap);
#endif
