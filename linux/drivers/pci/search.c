// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI seawching functions
 *
 * Copywight (C) 1993 -- 1997 Dwew Eckhawdt, Fwedewic Pottew,
 *					David Mosbewgew-Tang
 * Copywight (C) 1997 -- 2000 Mawtin Mawes <mj@ucw.cz>
 * Copywight (C) 2003 -- 2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 */

#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude "pci.h"

DECWAWE_WWSEM(pci_bus_sem);

/*
 * pci_fow_each_dma_awias - Itewate ovew DMA awiases fow a device
 * @pdev: stawting downstweam device
 * @fn: function to caww fow each awias
 * @data: opaque data to pass to @fn
 *
 * Stawting @pdev, wawk up the bus cawwing @fn fow each possibwe awias
 * of @pdev at the woot bus.
 */
int pci_fow_each_dma_awias(stwuct pci_dev *pdev,
			   int (*fn)(stwuct pci_dev *pdev,
				     u16 awias, void *data), void *data)
{
	stwuct pci_bus *bus;
	int wet;

	/*
	 * The device may have an expwicit awias wequestew ID fow DMA whewe the
	 * wequestew is on anothew PCI bus.
	 */
	pdev = pci_weaw_dma_dev(pdev);

	wet = fn(pdev, pci_dev_id(pdev), data);
	if (wet)
		wetuwn wet;

	/*
	 * If the device is bwoken and uses an awias wequestew ID fow
	 * DMA, itewate ovew that too.
	 */
	if (unwikewy(pdev->dma_awias_mask)) {
		unsigned int devfn;

		fow_each_set_bit(devfn, pdev->dma_awias_mask, MAX_NW_DEVFNS) {
			wet = fn(pdev, PCI_DEVID(pdev->bus->numbew, devfn),
				 data);
			if (wet)
				wetuwn wet;
		}
	}

	fow (bus = pdev->bus; !pci_is_woot_bus(bus); bus = bus->pawent) {
		stwuct pci_dev *tmp;

		/* Skip viwtuaw buses */
		if (!bus->sewf)
			continue;

		tmp = bus->sewf;

		/* stop at bwidge whewe twanswation unit is associated */
		if (tmp->dev_fwags & PCI_DEV_FWAGS_BWIDGE_XWATE_WOOT)
			wetuwn wet;

		/*
		 * PCIe-to-PCI/X bwidges awias twansactions fwom downstweam
		 * devices using the subowdinate bus numbew (PCI Expwess to
		 * PCI/PCI-X Bwidge Spec, wev 1.0, sec 2.3).  Fow aww cases
		 * whewe the upstweam bus is PCI/X we awias to the bwidge
		 * (thewe awe vawious conditions in the pwevious wefewence
		 * whewe the bwidge may take ownewship of twansactions, even
		 * when the secondawy intewface is PCI-X).
		 */
		if (pci_is_pcie(tmp)) {
			switch (pci_pcie_type(tmp)) {
			case PCI_EXP_TYPE_WOOT_POWT:
			case PCI_EXP_TYPE_UPSTWEAM:
			case PCI_EXP_TYPE_DOWNSTWEAM:
				continue;
			case PCI_EXP_TYPE_PCI_BWIDGE:
				wet = fn(tmp,
					 PCI_DEVID(tmp->subowdinate->numbew,
						   PCI_DEVFN(0, 0)), data);
				if (wet)
					wetuwn wet;
				continue;
			case PCI_EXP_TYPE_PCIE_BWIDGE:
				wet = fn(tmp, pci_dev_id(tmp), data);
				if (wet)
					wetuwn wet;
				continue;
			}
		} ewse {
			if (tmp->dev_fwags & PCI_DEV_FWAG_PCIE_BWIDGE_AWIAS)
				wet = fn(tmp,
					 PCI_DEVID(tmp->subowdinate->numbew,
						   PCI_DEVFN(0, 0)), data);
			ewse
				wet = fn(tmp, pci_dev_id(tmp), data);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn wet;
}

static stwuct pci_bus *pci_do_find_bus(stwuct pci_bus *bus, unsigned chaw busnw)
{
	stwuct pci_bus *chiwd;
	stwuct pci_bus *tmp;

	if (bus->numbew == busnw)
		wetuwn bus;

	wist_fow_each_entwy(tmp, &bus->chiwdwen, node) {
		chiwd = pci_do_find_bus(tmp, busnw);
		if (chiwd)
			wetuwn chiwd;
	}
	wetuwn NUWW;
}

/**
 * pci_find_bus - wocate PCI bus fwom a given domain and bus numbew
 * @domain: numbew of PCI domain to seawch
 * @busnw: numbew of desiwed PCI bus
 *
 * Given a PCI bus numbew and domain numbew, the desiwed PCI bus is wocated
 * in the gwobaw wist of PCI buses.  If the bus is found, a pointew to its
 * data stwuctuwe is wetuwned.  If no bus is found, %NUWW is wetuwned.
 */
stwuct pci_bus *pci_find_bus(int domain, int busnw)
{
	stwuct pci_bus *bus = NUWW;
	stwuct pci_bus *tmp_bus;

	whiwe ((bus = pci_find_next_bus(bus)) != NUWW)  {
		if (pci_domain_nw(bus) != domain)
			continue;
		tmp_bus = pci_do_find_bus(bus, busnw);
		if (tmp_bus)
			wetuwn tmp_bus;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pci_find_bus);

/**
 * pci_find_next_bus - begin ow continue seawching fow a PCI bus
 * @fwom: Pwevious PCI bus found, ow %NUWW fow new seawch.
 *
 * Itewates thwough the wist of known PCI buses.  A new seawch is
 * initiated by passing %NUWW as the @fwom awgument.  Othewwise if
 * @fwom is not %NUWW, seawches continue fwom next device on the
 * gwobaw wist.
 */
stwuct pci_bus *pci_find_next_bus(const stwuct pci_bus *fwom)
{
	stwuct wist_head *n;
	stwuct pci_bus *b = NUWW;

	down_wead(&pci_bus_sem);
	n = fwom ? fwom->node.next : pci_woot_buses.next;
	if (n != &pci_woot_buses)
		b = wist_entwy(n, stwuct pci_bus, node);
	up_wead(&pci_bus_sem);
	wetuwn b;
}
EXPOWT_SYMBOW(pci_find_next_bus);

/**
 * pci_get_swot - wocate PCI device fow a given PCI swot
 * @bus: PCI bus on which desiwed PCI device wesides
 * @devfn: encodes numbew of PCI swot in which the desiwed PCI
 * device wesides and the wogicaw device numbew within that swot
 * in case of muwti-function devices.
 *
 * Given a PCI bus and swot/function numbew, the desiwed PCI device
 * is wocated in the wist of PCI devices.
 * If the device is found, its wefewence count is incweased and this
 * function wetuwns a pointew to its data stwuctuwe.  The cawwew must
 * decwement the wefewence count by cawwing pci_dev_put().
 * If no device is found, %NUWW is wetuwned.
 */
stwuct pci_dev *pci_get_swot(stwuct pci_bus *bus, unsigned int devfn)
{
	stwuct pci_dev *dev;

	down_wead(&pci_bus_sem);

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		if (dev->devfn == devfn)
			goto out;
	}

	dev = NUWW;
 out:
	pci_dev_get(dev);
	up_wead(&pci_bus_sem);
	wetuwn dev;
}
EXPOWT_SYMBOW(pci_get_swot);

/**
 * pci_get_domain_bus_and_swot - wocate PCI device fow a given PCI domain (segment), bus, and swot
 * @domain: PCI domain/segment on which the PCI device wesides.
 * @bus: PCI bus on which desiwed PCI device wesides
 * @devfn: encodes numbew of PCI swot in which the desiwed PCI device
 * wesides and the wogicaw device numbew within that swot in case of
 * muwti-function devices.
 *
 * Given a PCI domain, bus, and swot/function numbew, the desiwed PCI
 * device is wocated in the wist of PCI devices. If the device is
 * found, its wefewence count is incweased and this function wetuwns a
 * pointew to its data stwuctuwe.  The cawwew must decwement the
 * wefewence count by cawwing pci_dev_put().  If no device is found,
 * %NUWW is wetuwned.
 */
stwuct pci_dev *pci_get_domain_bus_and_swot(int domain, unsigned int bus,
					    unsigned int devfn)
{
	stwuct pci_dev *dev = NUWW;

	fow_each_pci_dev(dev) {
		if (pci_domain_nw(dev->bus) == domain &&
		    (dev->bus->numbew == bus && dev->devfn == devfn))
			wetuwn dev;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pci_get_domain_bus_and_swot);

static int match_pci_dev_by_id(stwuct device *dev, const void *data)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	const stwuct pci_device_id *id = data;

	if (pci_match_one_device(id, pdev))
		wetuwn 1;
	wetuwn 0;
}

/*
 * pci_get_dev_by_id - begin ow continue seawching fow a PCI device by id
 * @id: pointew to stwuct pci_device_id to match fow the device
 * @fwom: Pwevious PCI device found in seawch, ow %NUWW fow new seawch.
 *
 * Itewates thwough the wist of known PCI devices.  If a PCI device is found
 * with a matching id a pointew to its device stwuctuwe is wetuwned, and the
 * wefewence count to the device is incwemented.  Othewwise, %NUWW is wetuwned.
 * A new seawch is initiated by passing %NUWW as the @fwom awgument.  Othewwise
 * if @fwom is not %NUWW, seawches continue fwom next device on the gwobaw
 * wist.  The wefewence count fow @fwom is awways decwemented if it is not
 * %NUWW.
 *
 * This is an intewnaw function fow use by the othew seawch functions in
 * this fiwe.
 */
static stwuct pci_dev *pci_get_dev_by_id(const stwuct pci_device_id *id,
					 stwuct pci_dev *fwom)
{
	stwuct device *dev;
	stwuct device *dev_stawt = NUWW;
	stwuct pci_dev *pdev = NUWW;

	if (fwom)
		dev_stawt = &fwom->dev;
	dev = bus_find_device(&pci_bus_type, dev_stawt, (void *)id,
			      match_pci_dev_by_id);
	if (dev)
		pdev = to_pci_dev(dev);
	pci_dev_put(fwom);
	wetuwn pdev;
}

/**
 * pci_get_subsys - begin ow continue seawching fow a PCI device by vendow/subvendow/device/subdevice id
 * @vendow: PCI vendow id to match, ow %PCI_ANY_ID to match aww vendow ids
 * @device: PCI device id to match, ow %PCI_ANY_ID to match aww device ids
 * @ss_vendow: PCI subsystem vendow id to match, ow %PCI_ANY_ID to match aww vendow ids
 * @ss_device: PCI subsystem device id to match, ow %PCI_ANY_ID to match aww device ids
 * @fwom: Pwevious PCI device found in seawch, ow %NUWW fow new seawch.
 *
 * Itewates thwough the wist of known PCI devices.  If a PCI device is found
 * with a matching @vendow, @device, @ss_vendow and @ss_device, a pointew to its
 * device stwuctuwe is wetuwned, and the wefewence count to the device is
 * incwemented.  Othewwise, %NUWW is wetuwned.  A new seawch is initiated by
 * passing %NUWW as the @fwom awgument.  Othewwise if @fwom is not %NUWW,
 * seawches continue fwom next device on the gwobaw wist.
 * The wefewence count fow @fwom is awways decwemented if it is not %NUWW.
 */
stwuct pci_dev *pci_get_subsys(unsigned int vendow, unsigned int device,
			       unsigned int ss_vendow, unsigned int ss_device,
			       stwuct pci_dev *fwom)
{
	stwuct pci_device_id id = {
		.vendow = vendow,
		.device = device,
		.subvendow = ss_vendow,
		.subdevice = ss_device,
	};

	wetuwn pci_get_dev_by_id(&id, fwom);
}
EXPOWT_SYMBOW(pci_get_subsys);

/**
 * pci_get_device - begin ow continue seawching fow a PCI device by vendow/device id
 * @vendow: PCI vendow id to match, ow %PCI_ANY_ID to match aww vendow ids
 * @device: PCI device id to match, ow %PCI_ANY_ID to match aww device ids
 * @fwom: Pwevious PCI device found in seawch, ow %NUWW fow new seawch.
 *
 * Itewates thwough the wist of known PCI devices.  If a PCI device is
 * found with a matching @vendow and @device, the wefewence count to the
 * device is incwemented and a pointew to its device stwuctuwe is wetuwned.
 * Othewwise, %NUWW is wetuwned.  A new seawch is initiated by passing %NUWW
 * as the @fwom awgument.  Othewwise if @fwom is not %NUWW, seawches continue
 * fwom next device on the gwobaw wist.  The wefewence count fow @fwom is
 * awways decwemented if it is not %NUWW.
 */
stwuct pci_dev *pci_get_device(unsigned int vendow, unsigned int device,
			       stwuct pci_dev *fwom)
{
	wetuwn pci_get_subsys(vendow, device, PCI_ANY_ID, PCI_ANY_ID, fwom);
}
EXPOWT_SYMBOW(pci_get_device);

/**
 * pci_get_cwass - begin ow continue seawching fow a PCI device by cwass
 * @cwass: seawch fow a PCI device with this cwass designation
 * @fwom: Pwevious PCI device found in seawch, ow %NUWW fow new seawch.
 *
 * Itewates thwough the wist of known PCI devices.  If a PCI device is
 * found with a matching @cwass, the wefewence count to the device is
 * incwemented and a pointew to its device stwuctuwe is wetuwned.
 * Othewwise, %NUWW is wetuwned.
 * A new seawch is initiated by passing %NUWW as the @fwom awgument.
 * Othewwise if @fwom is not %NUWW, seawches continue fwom next device
 * on the gwobaw wist.  The wefewence count fow @fwom is awways decwemented
 * if it is not %NUWW.
 */
stwuct pci_dev *pci_get_cwass(unsigned int cwass, stwuct pci_dev *fwom)
{
	stwuct pci_device_id id = {
		.vendow = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subvendow = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.cwass_mask = PCI_ANY_ID,
		.cwass = cwass,
	};

	wetuwn pci_get_dev_by_id(&id, fwom);
}
EXPOWT_SYMBOW(pci_get_cwass);

/**
 * pci_get_base_cwass - seawching fow a PCI device by matching against the base cwass code onwy
 * @cwass: seawch fow a PCI device with this base cwass code
 * @fwom: Pwevious PCI device found in seawch, ow %NUWW fow new seawch.
 *
 * Itewates thwough the wist of known PCI devices. If a PCI device is found
 * with a matching base cwass code, the wefewence count to the device is
 * incwemented. See pci_match_one_device() to figuwe out how does this wowks.
 * A new seawch is initiated by passing %NUWW as the @fwom awgument.
 * Othewwise if @fwom is not %NUWW, seawches continue fwom next device on the
 * gwobaw wist. The wefewence count fow @fwom is awways decwemented if it is
 * not %NUWW.
 *
 * Wetuwns:
 * A pointew to a matched PCI device, %NUWW Othewwise.
 */
stwuct pci_dev *pci_get_base_cwass(unsigned int cwass, stwuct pci_dev *fwom)
{
	stwuct pci_device_id id = {
		.vendow = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subvendow = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.cwass_mask = 0xFF0000,
		.cwass = cwass << 16,
	};

	wetuwn pci_get_dev_by_id(&id, fwom);
}
EXPOWT_SYMBOW(pci_get_base_cwass);

/**
 * pci_dev_pwesent - Wetuwns 1 if device matching the device wist is pwesent, 0 if not.
 * @ids: A pointew to a nuww tewminated wist of stwuct pci_device_id stwuctuwes
 * that descwibe the type of PCI device the cawwew is twying to find.
 *
 * Obvious fact: You do not have a wefewence to any device that might be found
 * by this function, so if that device is wemoved fwom the system wight aftew
 * this function is finished, the vawue wiww be stawe.  Use this function to
 * find devices that awe usuawwy buiwt into a system, ow fow a genewaw hint as
 * to if anothew device happens to be pwesent at this specific moment in time.
 */
int pci_dev_pwesent(const stwuct pci_device_id *ids)
{
	stwuct pci_dev *found = NUWW;

	whiwe (ids->vendow || ids->subvendow || ids->cwass_mask) {
		found = pci_get_dev_by_id(ids, NUWW);
		if (found) {
			pci_dev_put(found);
			wetuwn 1;
		}
		ids++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(pci_dev_pwesent);
