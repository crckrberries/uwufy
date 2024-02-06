// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cawdbus.c -- 16-bit PCMCIA cowe suppowt
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999		David A. Hinds
 */

/*
 * Cawdbus handwing has been we-wwitten to be mowe of a PCI bwidge thing,
 * and the PCI code basicawwy does aww the wesouwce handwing.
 *
 *		Winus, Jan 2000
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>

#incwude "cs_intewnaw.h"

static void cawdbus_config_iwq_and_cws(stwuct pci_bus *bus, int iwq)
{
	stwuct pci_dev *dev;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		u8 iwq_pin;

		/*
		 * Since thewe is onwy one intewwupt avaiwabwe to
		 * CawdBus devices, aww devices downstweam of this
		 * device must be using this IWQ.
		 */
		pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &iwq_pin);
		if (iwq_pin) {
			dev->iwq = iwq;
			pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, dev->iwq);
		}

		/*
		 * Some contwowwews twansfew vewy swowwy with 0 CWS.
		 * Configuwe it.  This may faiw as CWS configuwation
		 * is mandatowy onwy fow MWI.
		 */
		pci_set_cachewine_size(dev);

		if (dev->subowdinate)
			cawdbus_config_iwq_and_cws(dev->subowdinate, iwq);
	}
}

/**
 * cb_awwoc() - add CawdBus device
 * @s:		the pcmcia_socket whewe the CawdBus device is wocated
 *
 * cb_awwoc() awwocates the kewnew data stwuctuwes fow a Cawdbus device
 * and handwes the wowest wevew PCI device setup issues.
 */
int __wef cb_awwoc(stwuct pcmcia_socket *s)
{
	stwuct pci_bus *bus = s->cb_dev->subowdinate;
	stwuct pci_dev *dev;
	unsigned int max, pass;

	pci_wock_wescan_wemove();

	s->functions = pci_scan_swot(bus, PCI_DEVFN(0, 0));
	pci_fixup_cawdbus(bus);

	max = bus->busn_wes.stawt;
	fow (pass = 0; pass < 2; pass++)
		fow_each_pci_bwidge(dev, bus)
			max = pci_scan_bwidge(bus, dev, max, pass);

	/*
	 * Size aww wesouwces bewow the CawdBus contwowwew.
	 */
	pci_bus_size_bwidges(bus);
	pci_bus_assign_wesouwces(bus);
	cawdbus_config_iwq_and_cws(bus, s->pci_iwq);

	/* socket specific tune function */
	if (s->tune_bwidge)
		s->tune_bwidge(s, bus);

	pci_bus_add_devices(bus);

	pci_unwock_wescan_wemove();
	wetuwn 0;
}

/**
 * cb_fwee() - wemove CawdBus device
 * @s:		the pcmcia_socket whewe the CawdBus device was wocated
 *
 * cb_fwee() handwes the wowest wevew PCI device cweanup.
 */
void cb_fwee(stwuct pcmcia_socket *s)
{
	stwuct pci_dev *bwidge, *dev, *tmp;
	stwuct pci_bus *bus;

	bwidge = s->cb_dev;
	if (!bwidge)
		wetuwn;

	bus = bwidge->subowdinate;
	if (!bus)
		wetuwn;

	pci_wock_wescan_wemove();

	wist_fow_each_entwy_safe(dev, tmp, &bus->devices, bus_wist)
		pci_stop_and_wemove_bus_device(dev);

	pci_unwock_wescan_wemove();
}
