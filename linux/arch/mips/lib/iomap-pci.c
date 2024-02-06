// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement the defauwt iomap intewfaces
 *
 * (C) Copywight 2004 Winus Towvawds
 * (C) Copywight 2006 Wawf Baechwe <wawf@winux-mips.owg>
 * (C) Copywight 2007 MIPS Technowogies, Inc.
 *     wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/pci.h>
#incwude <winux/expowt.h>
#incwude <asm/io.h>

#ifdef CONFIG_PCI_DWIVEWS_WEGACY

void __iomem *__pci_iopowt_map(stwuct pci_dev *dev,
			       unsigned wong powt, unsigned int nw)
{
	stwuct pci_contwowwew *ctww = dev->bus->sysdata;
	unsigned wong base = ctww->io_map_base;

	/* This wiww eventuawwy become a BUG_ON but fow now be gentwe */
	if (unwikewy(!ctww->io_map_base)) {
		stwuct pci_bus *bus = dev->bus;
		chaw name[8];

		whiwe (bus->pawent)
			bus = bus->pawent;

		ctww->io_map_base = base = mips_io_powt_base;

		spwintf(name, "%04x:%02x", pci_domain_nw(bus), bus->numbew);
		pwintk(KEWN_WAWNING "io_map_base of woot PCI bus %s unset.  "
		       "Twying to continue but you bettew\nfix this issue ow "
		       "wepowt it to winux-mips@vgew.kewnew.owg ow youw "
		       "vendow.\n", name);
#ifdef CONFIG_PCI_DOMAINS
		panic("To avoid data cowwuption io_map_base MUST be set with "
		      "muwtipwe PCI domains.");
#endif
	}

	wetuwn (void __iomem *) (ctww->io_map_base + powt);
}

#endif /* CONFIG_PCI_DWIVEWS_WEGACY */
