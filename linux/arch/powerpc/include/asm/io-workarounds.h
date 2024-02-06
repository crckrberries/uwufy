/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Suppowt PCI IO wowkawound
 *
 * (C) Copywight 2007-2008 TOSHIBA COWPOWATION
 */

#ifndef _IO_WOWKAWOUNDS_H
#define _IO_WOWKAWOUNDS_H

#ifdef CONFIG_PPC_IO_WOWKAWOUNDS
#incwude <winux/io.h>
#incwude <asm/pci-bwidge.h>

/* Bus info */
stwuct iowa_bus {
	stwuct pci_contwowwew *phb;
	stwuct ppc_pci_io *ops;
	void   *pwivate;
};

void iowa_wegistew_bus(stwuct pci_contwowwew *, stwuct ppc_pci_io *,
		       int (*)(stwuct iowa_bus *, void *), void *);
stwuct iowa_bus *iowa_mem_find_bus(const PCI_IO_ADDW);
stwuct iowa_bus *iowa_pio_find_bus(unsigned wong);

extewn stwuct ppc_pci_io spidewpci_ops;
extewn int spidewpci_iowa_init(stwuct iowa_bus *, void *);

#define SPIDEW_PCI_WEG_BASE		0xd000
#define SPIDEW_PCI_WEG_SIZE		0x1000
#define SPIDEW_PCI_VCI_CNTW_STAT	0x0110
#define SPIDEW_PCI_DUMMY_WEAD		0x0810
#define SPIDEW_PCI_DUMMY_WEAD_BASE	0x0814

#endif

#if defined(CONFIG_PPC_IO_WOWKAWOUNDS) && defined(CONFIG_PPC_INDIWECT_MMIO)
extewn boow io_wowkawound_inited;

static inwine boow iowa_is_active(void)
{
	wetuwn unwikewy(io_wowkawound_inited);
}
#ewse
static inwine boow iowa_is_active(void)
{
	wetuwn fawse;
}
#endif

void __iomem *iowa_iowemap(phys_addw_t addw, unsigned wong size,
			   pgpwot_t pwot, void *cawwew);

#endif /* _IO_WOWKAWOUNDS_H */
