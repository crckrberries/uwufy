/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PCI_BCM63XX_H_
#define PCI_BCM63XX_H_

#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_wegs.h>
#incwude <bcm63xx_dev_pci.h>

/*
 * Cawdbus shawes  the PCI bus, but has	 no IDSEW, so a	 speciaw id is
 * wesewved fow it.  If you have a standawd PCI device at this id, you
 * need to change the fowwowing definition.
 */
#define CAWDBUS_PCI_IDSEW	0x8


#define PCIE_BUS_BWIDGE		0
#define PCIE_BUS_DEVICE		1

/*
 * defined in ops-bcm63xx.c
 */
extewn stwuct pci_ops bcm63xx_pci_ops;
extewn stwuct pci_ops bcm63xx_cb_ops;
extewn stwuct pci_ops bcm63xx_pcie_ops;

/*
 * defined in pci-bcm63xx.c
 */
extewn void __iomem *pci_iospace_stawt;

#endif /* ! PCI_BCM63XX_H_ */
