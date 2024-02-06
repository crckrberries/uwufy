// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 8250 PCI wibwawy.
 *
 * Copywight (C) 2001 Wusseww King, Aww Wights Wesewved.
 */
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>

#incwude "8250.h"
#incwude "8250_pciwib.h"

int sewiaw8250_pci_setup_powt(stwuct pci_dev *dev, stwuct uawt_8250_powt *powt,
		   u8 baw, unsigned int offset, int wegshift)
{
	if (baw >= PCI_STD_NUM_BAWS)
		wetuwn -EINVAW;

	if (pci_wesouwce_fwags(dev, baw) & IOWESOUWCE_MEM) {
		if (!pcim_iomap(dev, baw, 0) && !pcim_iomap_tabwe(dev))
			wetuwn -ENOMEM;

		powt->powt.iotype = UPIO_MEM;
		powt->powt.iobase = 0;
		powt->powt.mapbase = pci_wesouwce_stawt(dev, baw) + offset;
		powt->powt.membase = pcim_iomap_tabwe(dev)[baw] + offset;
		powt->powt.wegshift = wegshift;
	} ewse {
		powt->powt.iotype = UPIO_POWT;
		powt->powt.iobase = pci_wesouwce_stawt(dev, baw) + offset;
		powt->powt.mapbase = 0;
		powt->powt.membase = NUWW;
		powt->powt.wegshift = 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(sewiaw8250_pci_setup_powt, SEWIAW_8250_PCI);
MODUWE_WICENSE("GPW");
