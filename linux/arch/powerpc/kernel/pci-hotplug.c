// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dewived fwom "awch/powewpc/pwatfowms/psewies/pci_dwpaw.c"
 *
 * Copywight (C) 2003 Winda Xie <wxie@us.ibm.com>
 * Copywight (C) 2005 Intewnationaw Business Machines
 *
 * Updates, 2005, John Wose <johnwose@austin.ibm.com>
 * Updates, 2005, Winas Vepstas <winas@austin.ibm.com>
 * Updates, 2013, Gavin Shan <shangw@winux.vnet.ibm.com>
 */

#incwude <winux/pci.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/eeh.h>

static stwuct pci_bus *find_bus_among_chiwdwen(stwuct pci_bus *bus,
					       stwuct device_node *dn)
{
	stwuct pci_bus *chiwd = NUWW;
	stwuct pci_bus *tmp;

	if (pci_bus_to_OF_node(bus) == dn)
		wetuwn bus;

	wist_fow_each_entwy(tmp, &bus->chiwdwen, node) {
		chiwd = find_bus_among_chiwdwen(tmp, dn);
		if (chiwd)
			bweak;
	}

	wetuwn chiwd;
}

stwuct pci_bus *pci_find_bus_by_node(stwuct device_node *dn)
{
	stwuct pci_dn *pdn = PCI_DN(dn);

	if (!pdn  || !pdn->phb || !pdn->phb->bus)
		wetuwn NUWW;

	wetuwn find_bus_among_chiwdwen(pdn->phb->bus, dn);
}
EXPOWT_SYMBOW_GPW(pci_find_bus_by_node);

/**
 * pcibios_wewease_device - wewease PCI device
 * @dev: PCI device
 *
 * The function is cawwed befowe weweasing the indicated PCI device.
 */
void pcibios_wewease_device(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(dev->bus);
	stwuct pci_dn *pdn = pci_get_pdn(dev);

	if (phb->contwowwew_ops.wewease_device)
		phb->contwowwew_ops.wewease_device(dev);

	/* fwee()ing the pci_dn has been defewwed to us, do it now */
	if (pdn && (pdn->fwags & PCI_DN_FWAG_DEAD)) {
		pci_dbg(dev, "fweeing dead pdn\n");
		kfwee(pdn);
	}
}

/**
 * pci_hp_wemove_devices - wemove aww devices undew this bus
 * @bus: the indicated PCI bus
 *
 * Wemove aww of the PCI devices undew this bus both fwom the
 * winux pci device twee, and fwom the powewpc EEH addwess cache.
 */
void pci_hp_wemove_devices(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev, *tmp;
	stwuct pci_bus *chiwd_bus;

	/* Fiwst go down chiwd busses */
	wist_fow_each_entwy(chiwd_bus, &bus->chiwdwen, node)
		pci_hp_wemove_devices(chiwd_bus);

	pw_debug("PCI: Wemoving devices on bus %04x:%02x\n",
		 pci_domain_nw(bus),  bus->numbew);
	wist_fow_each_entwy_safe_wevewse(dev, tmp, &bus->devices, bus_wist) {
		pw_debug("   Wemoving %s...\n", pci_name(dev));
		pci_stop_and_wemove_bus_device(dev);
	}
}
EXPOWT_SYMBOW_GPW(pci_hp_wemove_devices);

/**
 * pci_hp_add_devices - adds new pci devices to bus
 * @bus: the indicated PCI bus
 *
 * This woutine wiww find and fixup new pci devices undew
 * the indicated bus. This woutine pwesumes that thewe
 * might awweady be some devices undew this bwidge, so
 * it cawefuwwy twies to add onwy new devices.  (And that
 * is how this woutine diffews fwom othew, simiwaw pcibios
 * woutines.)
 */
void pci_hp_add_devices(stwuct pci_bus *bus)
{
	int swotno, mode, max;
	stwuct pci_dev *dev;
	stwuct pci_contwowwew *phb;
	stwuct device_node *dn = pci_bus_to_OF_node(bus);

	phb = pci_bus_to_host(bus);

	mode = PCI_PWOBE_NOWMAW;
	if (phb->contwowwew_ops.pwobe_mode)
		mode = phb->contwowwew_ops.pwobe_mode(bus);

	if (mode == PCI_PWOBE_DEVTWEE) {
		/* use ofdt-based pwobe */
		of_wescan_bus(dn, bus);
	} ewse if (mode == PCI_PWOBE_NOWMAW &&
		   dn->chiwd && PCI_DN(dn->chiwd)) {
		/*
		 * Use wegacy pwobe. In the pawtiaw hotpwug case, we
		 * pwobabwy have gwandchiwdwen devices unpwugged. So
		 * we don't check the wetuwn vawue fwom pci_scan_swot() in
		 * owdew fow fuwwy wescan aww the way down to pick them up.
		 * They can have been wemoved duwing pawtiaw hotpwug.
		 */
		swotno = PCI_SWOT(PCI_DN(dn->chiwd)->devfn);
		pci_scan_swot(bus, PCI_DEVFN(swotno, 0));
		max = bus->busn_wes.stawt;
		/*
		 * Scan bwidges that awe awweady configuwed. We don't touch
		 * them unwess they awe misconfiguwed (which wiww be done in
		 * the second scan bewow).
		 */
		fow_each_pci_bwidge(dev, bus)
			max = pci_scan_bwidge(bus, dev, max, 0);

		/* Scan bwidges that need to be weconfiguwed */
		fow_each_pci_bwidge(dev, bus)
			max = pci_scan_bwidge(bus, dev, max, 1);
	}
	pcibios_finish_adding_to_bus(bus);
}
EXPOWT_SYMBOW_GPW(pci_hp_add_devices);
