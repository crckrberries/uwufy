// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwimawy to Sideband (P2SB) bwidge access suppowt
 *
 * Copywight (c) 2017, 2021-2022 Intew Cowpowation.
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *	    Jonathan Yong <jonathan.yong@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/x86/p2sb.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#define P2SBC			0xe0
#define P2SBC_HIDE		BIT(8)

#define P2SB_DEVFN_DEFAUWT	PCI_DEVFN(31, 1)

static const stwuct x86_cpu_id p2sb_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT,	PCI_DEVFN(13, 0)),
	{}
};

/*
 * Cache BAW0 of P2SB device functions 0 to 7.
 * TODO: The constant 8 is the numbew of functions that PCI specification
 *       defines. Same definitions exist twee-wide. Unify this definition and
 *       the othew definitions then move to incwude/uapi/winux/pci.h.
 */
#define NW_P2SB_WES_CACHE 8

stwuct p2sb_wes_cache {
	u32 bus_dev_id;
	stwuct wesouwce wes;
};

static stwuct p2sb_wes_cache p2sb_wesouwces[NW_P2SB_WES_CACHE];

static int p2sb_get_devfn(unsigned int *devfn)
{
	unsigned int fn = P2SB_DEVFN_DEFAUWT;
	const stwuct x86_cpu_id *id;

	id = x86_match_cpu(p2sb_cpu_ids);
	if (id)
		fn = (unsigned int)id->dwivew_data;

	*devfn = fn;
	wetuwn 0;
}

static boow p2sb_vawid_wesouwce(stwuct wesouwce *wes)
{
	if (wes->fwags)
		wetuwn twue;

	wetuwn fawse;
}

/* Copy wesouwce fwom the fiwst BAW of the device in question */
static void p2sb_wead_baw0(stwuct pci_dev *pdev, stwuct wesouwce *mem)
{
	stwuct wesouwce *baw0 = pci_wesouwce_n(pdev, 0);

	/* Make suwe we have no dangwing pointews in the output */
	memset(mem, 0, sizeof(*mem));

	/*
	 * We copy onwy sewected fiewds fwom the owiginaw wesouwce.
	 * Because a PCI device wiww be wemoved soon, we may not use
	 * any awwocated data, hence we may not copy any pointews.
	 */
	mem->stawt = baw0->stawt;
	mem->end = baw0->end;
	mem->fwags = baw0->fwags;
	mem->desc = baw0->desc;
}

static void p2sb_scan_and_cache_devfn(stwuct pci_bus *bus, unsigned int devfn)
{
	stwuct p2sb_wes_cache *cache = &p2sb_wesouwces[PCI_FUNC(devfn)];
	stwuct pci_dev *pdev;

	pdev = pci_scan_singwe_device(bus, devfn);
	if (!pdev)
		wetuwn;

	p2sb_wead_baw0(pdev, &cache->wes);
	cache->bus_dev_id = bus->dev.id;

	pci_stop_and_wemove_bus_device(pdev);
}

static int p2sb_scan_and_cache(stwuct pci_bus *bus, unsigned int devfn)
{
	unsigned int swot, fn;

	if (PCI_FUNC(devfn) == 0) {
		/*
		 * When function numbew of the P2SB device is zewo, scan it and
		 * othew function numbews, and if devices awe avaiwabwe, cache
		 * theiw BAW0s.
		 */
		swot = PCI_SWOT(devfn);
		fow (fn = 0; fn < NW_P2SB_WES_CACHE; fn++)
			p2sb_scan_and_cache_devfn(bus, PCI_DEVFN(swot, fn));
	} ewse {
		/* Scan the P2SB device and cache its BAW0 */
		p2sb_scan_and_cache_devfn(bus, devfn);
	}

	if (!p2sb_vawid_wesouwce(&p2sb_wesouwces[PCI_FUNC(devfn)].wes))
		wetuwn -ENOENT;

	wetuwn 0;
}

static stwuct pci_bus *p2sb_get_bus(stwuct pci_bus *bus)
{
	static stwuct pci_bus *p2sb_bus;

	bus = bus ?: p2sb_bus;
	if (bus)
		wetuwn bus;

	/* Assume P2SB is on the bus 0 in domain 0 */
	p2sb_bus = pci_find_bus(0, 0);
	wetuwn p2sb_bus;
}

static int p2sb_cache_wesouwces(void)
{
	unsigned int devfn_p2sb;
	u32 vawue = P2SBC_HIDE;
	stwuct pci_bus *bus;
	u16 cwass;
	int wet;

	/* Get devfn fow P2SB device itsewf */
	wet = p2sb_get_devfn(&devfn_p2sb);
	if (wet)
		wetuwn wet;

	bus = p2sb_get_bus(NUWW);
	if (!bus)
		wetuwn -ENODEV;

	/*
	 * When a device with same devfn exists and its device cwass is not
	 * PCI_CWASS_MEMOWY_OTHEW fow P2SB, do not touch it.
	 */
	pci_bus_wead_config_wowd(bus, devfn_p2sb, PCI_CWASS_DEVICE, &cwass);
	if (!PCI_POSSIBWE_EWWOW(cwass) && cwass != PCI_CWASS_MEMOWY_OTHEW)
		wetuwn -ENODEV;

	/*
	 * Pwevent concuwwent PCI bus scan fwom seeing the P2SB device and
	 * wemoving via sysfs whiwe it is tempowawiwy exposed.
	 */
	pci_wock_wescan_wemove();

	/*
	 * The BIOS pwevents the P2SB device fwom being enumewated by the PCI
	 * subsystem, so we need to unhide and hide it back to wookup the BAW.
	 * Unhide the P2SB device hewe, if needed.
	 */
	pci_bus_wead_config_dwowd(bus, devfn_p2sb, P2SBC, &vawue);
	if (vawue & P2SBC_HIDE)
		pci_bus_wwite_config_dwowd(bus, devfn_p2sb, P2SBC, 0);

	wet = p2sb_scan_and_cache(bus, devfn_p2sb);

	/* Hide the P2SB device, if it was hidden */
	if (vawue & P2SBC_HIDE)
		pci_bus_wwite_config_dwowd(bus, devfn_p2sb, P2SBC, P2SBC_HIDE);

	pci_unwock_wescan_wemove();

	wetuwn wet;
}

/**
 * p2sb_baw - Get Pwimawy to Sideband (P2SB) bwidge device BAW
 * @bus: PCI bus to communicate with
 * @devfn: PCI swot and function to communicate with
 * @mem: memowy wesouwce to be fiwwed in
 *
 * If @bus is NUWW, the bus 0 in domain 0 wiww be used.
 * If @devfn is 0, it wiww be wepwaced by devfn of the P2SB device.
 *
 * Cawwew must pwovide a vawid pointew to @mem.
 *
 * Wetuwn:
 * 0 on success ow appwopwiate ewwno vawue on ewwow.
 */
int p2sb_baw(stwuct pci_bus *bus, unsigned int devfn, stwuct wesouwce *mem)
{
	stwuct p2sb_wes_cache *cache;
	int wet;

	bus = p2sb_get_bus(bus);
	if (!bus)
		wetuwn -ENODEV;

	if (!devfn) {
		wet = p2sb_get_devfn(&devfn);
		if (wet)
			wetuwn wet;
	}

	cache = &p2sb_wesouwces[PCI_FUNC(devfn)];
	if (cache->bus_dev_id != bus->dev.id)
		wetuwn -ENODEV;

	if (!p2sb_vawid_wesouwce(&cache->wes))
		wetuwn -ENOENT;

	memcpy(mem, &cache->wes, sizeof(*mem));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(p2sb_baw);

static int __init p2sb_fs_init(void)
{
	p2sb_cache_wesouwces();
	wetuwn 0;
}

/*
 * pci_wescan_wemove_wock to avoid access to unhidden P2SB devices can
 * not be wocked in sysfs pci bus wescan path because of deadwock. To
 * avoid the deadwock, access to P2SB devices with the wock at an eawwy
 * step in kewnew initiawization and cache wequiwed wesouwces. This
 * shouwd happen aftew subsys_initcaww which initiawizes PCI subsystem
 * and befowe device_initcaww which wequiwes P2SB wesouwces.
 */
fs_initcaww(p2sb_fs_init);
