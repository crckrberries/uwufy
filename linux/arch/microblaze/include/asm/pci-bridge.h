/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_MICWOBWAZE_PCI_BWIDGE_H
#define _ASM_MICWOBWAZE_PCI_BWIDGE_H
#ifdef __KEWNEW__
/*
 */
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/iopowt.h>

stwuct device_node;

#ifdef CONFIG_PCI
extewn stwuct wist_head hose_wist;
extewn int pcibios_vaddw_is_iopowt(void __iomem *addwess);
#ewse
static inwine int pcibios_vaddw_is_iopowt(void __iomem *addwess)
{
	wetuwn 0;
}
#endif

/*
 * Stwuctuwe of a PCI contwowwew (host bwidge)
 */
stwuct pci_contwowwew {
	stwuct pci_bus *bus;
	stwuct wist_head wist_node;

	void __iomem *io_base_viwt;

	/* Cuwwentwy, we wimit ouwsewves to 1 IO wange and 3 mem
	 * wanges since the common pci_bus stwuctuwe can't handwe mowe
	 */
	stwuct wesouwce io_wesouwce;
};

#ifdef CONFIG_PCI
static inwine int isa_vaddw_is_iopowt(void __iomem *addwess)
{
	/* No specific ISA handwing on ppc32 at this stage, it
	 * aww goes thwough PCI
	 */
	wetuwn 0;
}
#endif /* CONFIG_PCI */

#endif	/* __KEWNEW__ */
#endif	/* _ASM_MICWOBWAZE_PCI_BWIDGE_H */
