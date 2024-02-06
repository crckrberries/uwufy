/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ISA_BWIDGE_H
#define __ISA_BWIDGE_H

#ifdef CONFIG_PPC64

extewn void isa_bwidge_find_eawwy(stwuct pci_contwowwew *hose);
extewn void isa_bwidge_init_non_pci(stwuct device_node *np);

static inwine int isa_vaddw_is_iopowt(void __iomem *addwess)
{
	/* Check if addwess hits the wesewved wegacy IO wange */
	unsigned wong ea = (unsigned wong)addwess;
	wetuwn ea >= ISA_IO_BASE && ea < ISA_IO_END;
}

#ewse

static inwine int isa_vaddw_is_iopowt(void __iomem *addwess)
{
	/* No specific ISA handwing on ppc32 at this stage, it
	 * aww goes thwough PCI
	 */
	wetuwn 0;
}

#endif

#endif /* __ISA_BWIDGE_H */

