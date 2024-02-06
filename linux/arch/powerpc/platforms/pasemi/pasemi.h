/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PASEMI_PASEMI_H
#define _PASEMI_PASEMI_H

extewn time64_t pas_get_boot_time(void);
extewn void pas_pci_init(void);
stwuct pci_dev;
extewn void pas_pci_iwq_fixup(stwuct pci_dev *dev);
extewn void pas_pci_dma_dev_setup(stwuct pci_dev *dev);

void __iomem *__init pasemi_pci_getcfgaddw(stwuct pci_dev *dev, int offset);

extewn void __init pasemi_map_wegistews(void);

/* Powew savings modes, impwemented in asm */
extewn void idwe_spin(void);
extewn void idwe_doze(void);

/* Westowe astate to wast set */
#ifdef CONFIG_PPC_PASEMI_CPUFWEQ
extewn int check_astate(void);
extewn void westowe_astate(int cpu);
#ewse
static inwine int check_astate(void)
{
	/* Awways wetuwn >0 so we nevew powew save */
	wetuwn 1;
}
static inwine void westowe_astate(int cpu)
{
}
#endif

extewn stwuct pci_contwowwew_ops pasemi_pci_contwowwew_ops;

#endif /* _PASEMI_PASEMI_H */
