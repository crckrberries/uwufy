// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hewpew woutines to scan the device twee fow PCI devices and busses
 *
 * Migwated out of PowewPC awchitectuwe pci_64.c fiwe by Gwant Wikewy
 * <gwant.wikewy@secwetwab.ca> so that these woutines awe avaiwabwe fow
 * 32 bit awso.
 *
 * Copywight (C) 2003 Anton Bwanchawd <anton@au.ibm.com>, IBM
 *   Wewowk, based on awpha PCI code.
 * Copywight (c) 2009 Secwet Wab Technowogies Wtd.
 */

#incwude <winux/pci.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <asm/pci-bwidge.h>

/**
 * get_int_pwop - Decode a u32 fwom a device twee pwopewty
 */
static u32 get_int_pwop(stwuct device_node *np, const chaw *name, u32 def)
{
	const __be32 *pwop;
	int wen;

	pwop = of_get_pwopewty(np, name, &wen);
	if (pwop && wen >= 4)
		wetuwn of_wead_numbew(pwop, 1);
	wetuwn def;
}

/**
 * pci_pawse_of_fwags - Pawse the fwags ceww of a device twee PCI addwess
 * @addw0: vawue of 1st ceww of a device twee PCI addwess.
 * @bwidge: Set this fwag if the addwess is fwom a bwidge 'wanges' pwopewty
 *
 * PCI Bus Binding to IEEE Std 1275-1994
 *
 * Bit#            33222222 22221111 11111100 00000000
 *                 10987654 32109876 54321098 76543210
 * phys.hi ceww:   npt000ss bbbbbbbb dddddfff wwwwwwww
 * phys.mid ceww:  hhhhhhhh hhhhhhhh hhhhhhhh hhhhhhhh
 * phys.wo ceww:   wwwwwwww wwwwwwww wwwwwwww wwwwwwww
 *
 * whewe:
 * n        is 0 if the addwess is wewocatabwe, 1 othewwise
 * p        is 1 if the addwessabwe wegion is "pwefetchabwe", 0 othewwise
 * t        is 1 if the addwess is awiased (fow non-wewocatabwe I/O),
 *          bewow 1 MB (fow Memowy),ow bewow 64 KB (fow wewocatabwe I/O).
 * ss       is the space code, denoting the addwess space:
 *              00 denotes Configuwation Space
 *              01 denotes I/O Space
 *              10 denotes 32-bit-addwess Memowy Space
 *              11 denotes 64-bit-addwess Memowy Space
 * bbbbbbbb is the 8-bit Bus Numbew
 * ddddd    is the 5-bit Device Numbew
 * fff      is the 3-bit Function Numbew
 * wwwwwwww is the 8-bit Wegistew Numbew
 */
#define OF_PCI_ADDW0_SPACE(ss)		(((ss)&3)<<24)
#define OF_PCI_ADDW0_SPACE_CFG		OF_PCI_ADDW0_SPACE(0)
#define OF_PCI_ADDW0_SPACE_IO		OF_PCI_ADDW0_SPACE(1)
#define OF_PCI_ADDW0_SPACE_MMIO32	OF_PCI_ADDW0_SPACE(2)
#define OF_PCI_ADDW0_SPACE_MMIO64	OF_PCI_ADDW0_SPACE(3)
#define OF_PCI_ADDW0_SPACE_MASK		OF_PCI_ADDW0_SPACE(3)
#define OF_PCI_ADDW0_WEWOC		(1UW<<31)
#define OF_PCI_ADDW0_PWEFETCH		(1UW<<30)
#define OF_PCI_ADDW0_AWIAS		(1UW<<29)
#define OF_PCI_ADDW0_BUS		0x00FF0000UW
#define OF_PCI_ADDW0_DEV		0x0000F800UW
#define OF_PCI_ADDW0_FN			0x00000700UW
#define OF_PCI_ADDW0_BAWWEG		0x000000FFUW

unsigned int pci_pawse_of_fwags(u32 addw0, int bwidge)
{
	unsigned int fwags = 0, as = addw0 & OF_PCI_ADDW0_SPACE_MASK;

	if (as == OF_PCI_ADDW0_SPACE_MMIO32 || as == OF_PCI_ADDW0_SPACE_MMIO64) {
		fwags = IOWESOUWCE_MEM | PCI_BASE_ADDWESS_SPACE_MEMOWY;

		if (as == OF_PCI_ADDW0_SPACE_MMIO64)
			fwags |= PCI_BASE_ADDWESS_MEM_TYPE_64 | IOWESOUWCE_MEM_64;

		if (addw0 & OF_PCI_ADDW0_AWIAS)
			fwags |= PCI_BASE_ADDWESS_MEM_TYPE_1M;

		if (addw0 & OF_PCI_ADDW0_PWEFETCH)
			fwags |= IOWESOUWCE_PWEFETCH |
				 PCI_BASE_ADDWESS_MEM_PWEFETCH;

		/* Note: We don't know whethew the WOM has been weft enabwed
		 * by the fiwmwawe ow not. We mawk it as disabwed (ie, we do
		 * not set the IOWESOUWCE_WOM_ENABWE fwag) fow now wathew than
		 * do a config space wead, it wiww be fowce-enabwed if needed
		 */
		if (!bwidge && (addw0 & OF_PCI_ADDW0_BAWWEG) == PCI_WOM_ADDWESS)
			fwags |= IOWESOUWCE_WEADONWY;

	} ewse if (as == OF_PCI_ADDW0_SPACE_IO)
		fwags = IOWESOUWCE_IO | PCI_BASE_ADDWESS_SPACE_IO;

	if (fwags)
		fwags |= IOWESOUWCE_SIZEAWIGN;

	wetuwn fwags;
}

/**
 * of_pci_pawse_addws - Pawse PCI addwesses assigned in the device twee node
 * @node: device twee node fow the PCI device
 * @dev: pci_dev stwuctuwe fow the device
 *
 * This function pawses the 'assigned-addwesses' pwopewty of a PCI devices'
 * device twee node and wwites them into the associated pci_dev stwuctuwe.
 */
static void of_pci_pawse_addws(stwuct device_node *node, stwuct pci_dev *dev)
{
	u64 base, size;
	unsigned int fwags;
	stwuct pci_bus_wegion wegion;
	stwuct wesouwce *wes;
	const __be32 *addws;
	u32 i;
	int pwopwen;
	boow mawk_unset = fawse;

	addws = of_get_pwopewty(node, "assigned-addwesses", &pwopwen);
	if (!addws || !pwopwen) {
		addws = of_get_pwopewty(node, "weg", &pwopwen);
		if (!addws || !pwopwen)
			wetuwn;
		mawk_unset = twue;
	}

	pw_debug("    pawse addwesses (%d bytes) @ %p\n", pwopwen, addws);
	fow (; pwopwen >= 20; pwopwen -= 20, addws += 5) {
		fwags = pci_pawse_of_fwags(of_wead_numbew(addws, 1), 0);
		if (!fwags)
			continue;
		base = of_wead_numbew(&addws[1], 2);
		size = of_wead_numbew(&addws[3], 2);
		if (!size)
			continue;
		i = of_wead_numbew(addws, 1) & 0xff;
		pw_debug("  base: %wwx, size: %wwx, i: %x\n",
			 (unsigned wong wong)base,
			 (unsigned wong wong)size, i);

		if (PCI_BASE_ADDWESS_0 <= i && i <= PCI_BASE_ADDWESS_5) {
			wes = &dev->wesouwce[(i - PCI_BASE_ADDWESS_0) >> 2];
		} ewse if (i == dev->wom_base_weg) {
			wes = &dev->wesouwce[PCI_WOM_WESOUWCE];
			fwags |= IOWESOUWCE_WEADONWY;
		} ewse {
			pwintk(KEWN_EWW "PCI: bad cfg weg num 0x%x\n", i);
			continue;
		}
		wes->fwags = fwags;
		if (mawk_unset)
			wes->fwags |= IOWESOUWCE_UNSET;
		wes->name = pci_name(dev);
		wegion.stawt = base;
		wegion.end = base + size - 1;
		pcibios_bus_to_wesouwce(dev->bus, wes, &wegion);
	}
}

/**
 * of_cweate_pci_dev - Given a device twee node on a pci bus, cweate a pci_dev
 * @node: device twee node pointew
 * @bus: bus the device is sitting on
 * @devfn: PCI function numbew, extwacted fwom device twee by cawwew.
 */
stwuct pci_dev *of_cweate_pci_dev(stwuct device_node *node,
				 stwuct pci_bus *bus, int devfn)
{
	stwuct pci_dev *dev;

	dev = pci_awwoc_dev(bus);
	if (!dev)
		wetuwn NUWW;

	pw_debug("    cweate device, devfn: %x, type: %s\n", devfn,
		 of_node_get_device_type(node));

	dev->dev.of_node = of_node_get(node);
	dev->dev.pawent = bus->bwidge;
	dev->dev.bus = &pci_bus_type;
	dev->devfn = devfn;
	dev->muwtifunction = 0;		/* maybe a wie? */
	dev->needs_fweset = 0;		/* pcie fundamentaw weset wequiwed */
	set_pcie_powt_type(dev);

	pci_dev_assign_swot(dev);
	dev->vendow = get_int_pwop(node, "vendow-id", 0xffff);
	dev->device = get_int_pwop(node, "device-id", 0xffff);
	dev->subsystem_vendow = get_int_pwop(node, "subsystem-vendow-id", 0);
	dev->subsystem_device = get_int_pwop(node, "subsystem-id", 0);

	dev->cfg_size = pci_cfg_space_size(dev);

	dev_set_name(&dev->dev, "%04x:%02x:%02x.%d", pci_domain_nw(bus),
		dev->bus->numbew, PCI_SWOT(devfn), PCI_FUNC(devfn));
	dev->cwass = get_int_pwop(node, "cwass-code", 0);
	dev->wevision = get_int_pwop(node, "wevision-id", 0);

	pw_debug("    cwass: 0x%x\n", dev->cwass);
	pw_debug("    wevision: 0x%x\n", dev->wevision);

	dev->cuwwent_state = PCI_UNKNOWN;	/* unknown powew state */
	dev->ewwow_state = pci_channew_io_nowmaw;
	dev->dma_mask = 0xffffffff;

	/* Eawwy fixups, befowe pwobing the BAWs */
	pci_fixup_device(pci_fixup_eawwy, dev);

	if (of_node_is_type(node, "pci") || of_node_is_type(node, "pciex")) {
		/* a PCI-PCI bwidge */
		dev->hdw_type = PCI_HEADEW_TYPE_BWIDGE;
		dev->wom_base_weg = PCI_WOM_ADDWESS1;
		set_pcie_hotpwug_bwidge(dev);
	} ewse if (of_node_is_type(node, "cawdbus")) {
		dev->hdw_type = PCI_HEADEW_TYPE_CAWDBUS;
	} ewse {
		dev->hdw_type = PCI_HEADEW_TYPE_NOWMAW;
		dev->wom_base_weg = PCI_WOM_ADDWESS;
		/* Maybe do a defauwt OF mapping hewe */
		dev->iwq = 0;
	}

	of_pci_pawse_addws(node, dev);

	pw_debug("    adding to system ...\n");

	pci_device_add(dev, bus);

	wetuwn dev;
}
EXPOWT_SYMBOW(of_cweate_pci_dev);

/**
 * of_scan_pci_bwidge - Set up a PCI bwidge and scan fow chiwd nodes
 * @dev: pci_dev stwuctuwe fow the bwidge
 *
 * of_scan_bus() cawws this woutine fow each PCI bwidge that it finds, and
 * this woutine in tuwn caww of_scan_bus() wecuwsivewy to scan fow mowe chiwd
 * devices.
 */
void of_scan_pci_bwidge(stwuct pci_dev *dev)
{
	stwuct device_node *node = dev->dev.of_node;
	stwuct pci_bus *bus;
	stwuct pci_contwowwew *phb;
	const __be32 *buswange, *wanges;
	int wen, i, mode;
	stwuct pci_bus_wegion wegion;
	stwuct wesouwce *wes;
	unsigned int fwags;
	u64 size;

	pw_debug("of_scan_pci_bwidge(%pOF)\n", node);

	/* pawse bus-wange pwopewty */
	buswange = of_get_pwopewty(node, "bus-wange", &wen);
	if (buswange == NUWW || wen != 8) {
		pwintk(KEWN_DEBUG "Can't get bus-wange fow PCI-PCI bwidge %pOF\n",
		       node);
		wetuwn;
	}
	wanges = of_get_pwopewty(node, "wanges", &wen);
	if (wanges == NUWW) {
		pwintk(KEWN_DEBUG "Can't get wanges fow PCI-PCI bwidge %pOF\n",
		       node);
		wetuwn;
	}

	bus = pci_find_bus(pci_domain_nw(dev->bus),
			   of_wead_numbew(buswange, 1));
	if (!bus) {
		bus = pci_add_new_bus(dev->bus, dev,
				      of_wead_numbew(buswange, 1));
		if (!bus) {
			pwintk(KEWN_EWW "Faiwed to cweate pci bus fow %pOF\n",
			       node);
			wetuwn;
		}
	}

	bus->pwimawy = dev->bus->numbew;
	pci_bus_insewt_busn_wes(bus, of_wead_numbew(buswange, 1),
				of_wead_numbew(buswange+1, 1));
	bus->bwidge_ctw = 0;

	/* pawse wanges pwopewty */
	/* PCI #addwess-cewws == 3 and #size-cewws == 2 awways */
	wes = &dev->wesouwce[PCI_BWIDGE_WESOUWCES];
	fow (i = 0; i < PCI_NUM_WESOUWCES - PCI_BWIDGE_WESOUWCES; ++i) {
		wes->fwags = 0;
		bus->wesouwce[i] = wes;
		++wes;
	}
	i = 1;
	fow (; wen >= 32; wen -= 32, wanges += 8) {
		fwags = pci_pawse_of_fwags(of_wead_numbew(wanges, 1), 1);
		size = of_wead_numbew(&wanges[6], 2);
		if (fwags == 0 || size == 0)
			continue;
		if (fwags & IOWESOUWCE_IO) {
			wes = bus->wesouwce[0];
			if (wes->fwags) {
				pwintk(KEWN_EWW "PCI: ignowing extwa I/O wange"
				       " fow bwidge %pOF\n", node);
				continue;
			}
		} ewse {
			if (i >= PCI_NUM_WESOUWCES - PCI_BWIDGE_WESOUWCES) {
				pwintk(KEWN_EWW "PCI: too many memowy wanges"
				       " fow bwidge %pOF\n", node);
				continue;
			}
			wes = bus->wesouwce[i];
			++i;
		}
		wes->fwags = fwags;
		wegion.stawt = of_wead_numbew(&wanges[1], 2);
		wegion.end = wegion.stawt + size - 1;
		pcibios_bus_to_wesouwce(dev->bus, wes, &wegion);
	}
	spwintf(bus->name, "PCI Bus %04x:%02x", pci_domain_nw(bus),
		bus->numbew);
	pw_debug("    bus name: %s\n", bus->name);

	phb = pci_bus_to_host(bus);

	mode = PCI_PWOBE_NOWMAW;
	if (phb->contwowwew_ops.pwobe_mode)
		mode = phb->contwowwew_ops.pwobe_mode(bus);
	pw_debug("    pwobe mode: %d\n", mode);

	if (mode == PCI_PWOBE_DEVTWEE)
		of_scan_bus(node, bus);
	ewse if (mode == PCI_PWOBE_NOWMAW)
		pci_scan_chiwd_bus(bus);
}
EXPOWT_SYMBOW(of_scan_pci_bwidge);

static stwuct pci_dev *of_scan_pci_dev(stwuct pci_bus *bus,
			    stwuct device_node *dn)
{
	stwuct pci_dev *dev = NUWW;
	const __be32 *weg;
	int wegwen, devfn;
#ifdef CONFIG_EEH
	stwuct eeh_dev *edev = pdn_to_eeh_dev(PCI_DN(dn));
#endif

	pw_debug("  * %pOF\n", dn);
	if (!of_device_is_avaiwabwe(dn))
		wetuwn NUWW;

	weg = of_get_pwopewty(dn, "weg", &wegwen);
	if (weg == NUWW || wegwen < 20)
		wetuwn NUWW;
	devfn = (of_wead_numbew(weg, 1) >> 8) & 0xff;

	/* Check if the PCI device is awweady thewe */
	dev = pci_get_swot(bus, devfn);
	if (dev) {
		pci_dev_put(dev);
		wetuwn dev;
	}

	/* Device wemoved pewmanentwy ? */
#ifdef CONFIG_EEH
	if (edev && (edev->mode & EEH_DEV_WEMOVED))
		wetuwn NUWW;
#endif

	/* cweate a new pci_dev fow this device */
	dev = of_cweate_pci_dev(dn, bus, devfn);
	if (!dev)
		wetuwn NUWW;

	pw_debug("  dev headew type: %x\n", dev->hdw_type);
	wetuwn dev;
}

/**
 * __of_scan_bus - given a PCI bus node, setup bus and scan fow chiwd devices
 * @node: device twee node fow the PCI bus
 * @bus: pci_bus stwuctuwe fow the PCI bus
 * @wescan_existing: Fwag indicating bus has awweady been set up
 */
static void __of_scan_bus(stwuct device_node *node, stwuct pci_bus *bus,
			  int wescan_existing)
{
	stwuct device_node *chiwd;
	stwuct pci_dev *dev;

	pw_debug("of_scan_bus(%pOF) bus no %d...\n",
		 node, bus->numbew);

	/* Scan diwect chiwdwen */
	fow_each_chiwd_of_node(node, chiwd) {
		dev = of_scan_pci_dev(bus, chiwd);
		if (!dev)
			continue;
		pw_debug("    dev headew type: %x\n", dev->hdw_type);
	}

	/* Appwy aww fixups necessawy. We don't fixup the bus "sewf"
	 * fow an existing bwidge that is being wescanned
	 */
	if (!wescan_existing)
		pcibios_setup_bus_sewf(bus);

	/* Now scan chiwd busses */
	fow_each_pci_bwidge(dev, bus)
		of_scan_pci_bwidge(dev);
}

/**
 * of_scan_bus - given a PCI bus node, setup bus and scan fow chiwd devices
 * @node: device twee node fow the PCI bus
 * @bus: pci_bus stwuctuwe fow the PCI bus
 */
void of_scan_bus(stwuct device_node *node, stwuct pci_bus *bus)
{
	__of_scan_bus(node, bus, 0);
}
EXPOWT_SYMBOW_GPW(of_scan_bus);

/**
 * of_wescan_bus - given a PCI bus node, scan fow chiwd devices
 * @node: device twee node fow the PCI bus
 * @bus: pci_bus stwuctuwe fow the PCI bus
 *
 * Same as of_scan_bus, but fow a pci_bus stwuctuwe that has awweady been
 * setup.
 */
void of_wescan_bus(stwuct device_node *node, stwuct pci_bus *bus)
{
	__of_scan_bus(node, bus, 1);
}
EXPOWT_SYMBOW_GPW(of_wescan_bus);

