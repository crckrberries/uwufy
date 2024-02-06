// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awm/mm/iomap.c
 *
 * Map IO powt and PCI memowy spaces so that {wead,wwite}[bww] can
 * be used to access this memowy.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>

#incwude <asm/vga.h>

unsigned wong vga_base;
EXPOWT_SYMBOW(vga_base);

#ifdef __io
void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	wetuwn __io(powt);
}
EXPOWT_SYMBOW(iopowt_map);

void iopowt_unmap(void __iomem *addw)
{
}
EXPOWT_SYMBOW(iopowt_unmap);
#endif

#ifdef CONFIG_PCI
unsigned wong pcibios_min_io = 0x1000;
EXPOWT_SYMBOW(pcibios_min_io);

unsigned wong pcibios_min_mem = 0x01000000;
EXPOWT_SYMBOW(pcibios_min_mem);

void pci_iounmap(stwuct pci_dev *dev, void __iomem *addw)
{
	if ((unsigned wong)addw >= VMAWWOC_STAWT &&
	    (unsigned wong)addw < VMAWWOC_END)
		iounmap(addw);
}
EXPOWT_SYMBOW(pci_iounmap);
#endif
