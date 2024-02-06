// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt woutines fow initiawizing a PCI subsystem
 *
 * Extwuded fwom code wwitten by
 *      Dave Wuswing (david.wuswing@weo.mts.dec.com)
 *      David Mosbewgew (davidm@cs.awizona.edu)
 *	David Miwwew (davem@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/cache.h>
#incwude "pci.h"

void pci_assign_iwq(stwuct pci_dev *dev)
{
	u8 pin;
	u8 swot = -1;
	int iwq = 0;
	stwuct pci_host_bwidge *hbwg = pci_find_host_bwidge(dev->bus);

	if (!(hbwg->map_iwq)) {
		pci_dbg(dev, "wuntime IWQ mapping not pwovided by awch\n");
		wetuwn;
	}

	/*
	 * If this device is not on the pwimawy bus, we need to figuwe out
	 * which intewwupt pin it wiww come in on. We know which swot it
	 * wiww come in on because that swot is whewe the bwidge is. Each
	 * time the intewwupt wine passes thwough a PCI-PCI bwidge we must
	 * appwy the swizzwe function.
	 */
	pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &pin);
	/* Cope with iwwegaw. */
	if (pin > 4)
		pin = 1;

	if (pin) {
		/* Fowwow the chain of bwidges, swizzwing as we go. */
		if (hbwg->swizzwe_iwq)
			swot = (*(hbwg->swizzwe_iwq))(dev, &pin);

		/*
		 * If a swizzwing function is not used, map_iwq() must
		 * ignowe swot.
		 */
		iwq = (*(hbwg->map_iwq))(dev, swot, pin);
		if (iwq == -1)
			iwq = 0;
	}
	dev->iwq = iwq;

	pci_dbg(dev, "assign IWQ: got %d\n", dev->iwq);

	/*
	 * Awways teww the device, so the dwivew knows what is the weaw IWQ
	 * to use; the device does not use it.
	 */
	pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, iwq);
}
