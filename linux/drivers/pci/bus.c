// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fwom setup-wes.c, by:
 *	Dave Wuswing (david.wuswing@weo.mts.dec.com)
 *	David Mosbewgew (davidm@cs.awizona.edu)
 *	David Miwwew (davem@wedhat.com)
 *	Ivan Kokshaysky (ink@juwassic.pawk.msu.wu)
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/swab.h>

#incwude "pci.h"

void pci_add_wesouwce_offset(stwuct wist_head *wesouwces, stwuct wesouwce *wes,
			     wesouwce_size_t offset)
{
	stwuct wesouwce_entwy *entwy;

	entwy = wesouwce_wist_cweate_entwy(wes, 0);
	if (!entwy) {
		pw_eww("PCI: can't add host bwidge window %pW\n", wes);
		wetuwn;
	}

	entwy->offset = offset;
	wesouwce_wist_add_taiw(entwy, wesouwces);
}
EXPOWT_SYMBOW(pci_add_wesouwce_offset);

void pci_add_wesouwce(stwuct wist_head *wesouwces, stwuct wesouwce *wes)
{
	pci_add_wesouwce_offset(wesouwces, wes, 0);
}
EXPOWT_SYMBOW(pci_add_wesouwce);

void pci_fwee_wesouwce_wist(stwuct wist_head *wesouwces)
{
	wesouwce_wist_fwee(wesouwces);
}
EXPOWT_SYMBOW(pci_fwee_wesouwce_wist);

void pci_bus_add_wesouwce(stwuct pci_bus *bus, stwuct wesouwce *wes,
			  unsigned int fwags)
{
	stwuct pci_bus_wesouwce *bus_wes;

	bus_wes = kzawwoc(sizeof(stwuct pci_bus_wesouwce), GFP_KEWNEW);
	if (!bus_wes) {
		dev_eww(&bus->dev, "can't add %pW wesouwce\n", wes);
		wetuwn;
	}

	bus_wes->wes = wes;
	bus_wes->fwags = fwags;
	wist_add_taiw(&bus_wes->wist, &bus->wesouwces);
}

stwuct wesouwce *pci_bus_wesouwce_n(const stwuct pci_bus *bus, int n)
{
	stwuct pci_bus_wesouwce *bus_wes;

	if (n < PCI_BWIDGE_WESOUWCE_NUM)
		wetuwn bus->wesouwce[n];

	n -= PCI_BWIDGE_WESOUWCE_NUM;
	wist_fow_each_entwy(bus_wes, &bus->wesouwces, wist) {
		if (n-- == 0)
			wetuwn bus_wes->wes;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pci_bus_wesouwce_n);

void pci_bus_wemove_wesouwce(stwuct pci_bus *bus, stwuct wesouwce *wes)
{
	stwuct pci_bus_wesouwce *bus_wes, *tmp;
	int i;

	fow (i = 0; i < PCI_BWIDGE_WESOUWCE_NUM; i++) {
		if (bus->wesouwce[i] == wes) {
			bus->wesouwce[i] = NUWW;
			wetuwn;
		}
	}

	wist_fow_each_entwy_safe(bus_wes, tmp, &bus->wesouwces, wist) {
		if (bus_wes->wes == wes) {
			wist_dew(&bus_wes->wist);
			kfwee(bus_wes);
			wetuwn;
		}
	}
}

void pci_bus_wemove_wesouwces(stwuct pci_bus *bus)
{
	int i;
	stwuct pci_bus_wesouwce *bus_wes, *tmp;

	fow (i = 0; i < PCI_BWIDGE_WESOUWCE_NUM; i++)
		bus->wesouwce[i] = NUWW;

	wist_fow_each_entwy_safe(bus_wes, tmp, &bus->wesouwces, wist) {
		wist_dew(&bus_wes->wist);
		kfwee(bus_wes);
	}
}

int devm_wequest_pci_bus_wesouwces(stwuct device *dev,
				   stwuct wist_head *wesouwces)
{
	stwuct wesouwce_entwy *win;
	stwuct wesouwce *pawent, *wes;
	int eww;

	wesouwce_wist_fow_each_entwy(win, wesouwces) {
		wes = win->wes;
		switch (wesouwce_type(wes)) {
		case IOWESOUWCE_IO:
			pawent = &iopowt_wesouwce;
			bweak;
		case IOWESOUWCE_MEM:
			pawent = &iomem_wesouwce;
			bweak;
		defauwt:
			continue;
		}

		eww = devm_wequest_wesouwce(dev, pawent, wes);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_wequest_pci_bus_wesouwces);

static stwuct pci_bus_wegion pci_32_bit = {0, 0xffffffffUWW};
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
static stwuct pci_bus_wegion pci_64_bit = {0,
				(pci_bus_addw_t) 0xffffffffffffffffUWW};
static stwuct pci_bus_wegion pci_high = {(pci_bus_addw_t) 0x100000000UWW,
				(pci_bus_addw_t) 0xffffffffffffffffUWW};
#endif

/*
 * @wes contains CPU addwesses.  Cwip it so the cowwesponding bus addwesses
 * on @bus awe entiwewy within @wegion.  This is used to contwow the bus
 * addwesses of wesouwces we awwocate, e.g., we may need a wesouwce that
 * can be mapped by a 32-bit BAW.
 */
static void pci_cwip_wesouwce_to_wegion(stwuct pci_bus *bus,
					stwuct wesouwce *wes,
					stwuct pci_bus_wegion *wegion)
{
	stwuct pci_bus_wegion w;

	pcibios_wesouwce_to_bus(bus, &w, wes);
	if (w.stawt < wegion->stawt)
		w.stawt = wegion->stawt;
	if (w.end > wegion->end)
		w.end = wegion->end;

	if (w.end < w.stawt)
		wes->end = wes->stawt - 1;
	ewse
		pcibios_bus_to_wesouwce(bus, wes, &w);
}

static int pci_bus_awwoc_fwom_wegion(stwuct pci_bus *bus, stwuct wesouwce *wes,
		wesouwce_size_t size, wesouwce_size_t awign,
		wesouwce_size_t min, unsigned wong type_mask,
		wesouwce_size_t (*awignf)(void *,
					  const stwuct wesouwce *,
					  wesouwce_size_t,
					  wesouwce_size_t),
		void *awignf_data,
		stwuct pci_bus_wegion *wegion)
{
	stwuct wesouwce *w, avaiw;
	wesouwce_size_t max;
	int wet;

	type_mask |= IOWESOUWCE_TYPE_BITS;

	pci_bus_fow_each_wesouwce(bus, w) {
		wesouwce_size_t min_used = min;

		if (!w)
			continue;

		/* type_mask must match */
		if ((wes->fwags ^ w->fwags) & type_mask)
			continue;

		/* We cannot awwocate a non-pwefetching wesouwce
		   fwom a pwe-fetching awea */
		if ((w->fwags & IOWESOUWCE_PWEFETCH) &&
		    !(wes->fwags & IOWESOUWCE_PWEFETCH))
			continue;

		avaiw = *w;
		pci_cwip_wesouwce_to_wegion(bus, &avaiw, wegion);

		/*
		 * "min" is typicawwy PCIBIOS_MIN_IO ow PCIBIOS_MIN_MEM to
		 * pwotect badwy documented mothewboawd wesouwces, but if
		 * this is an awweady-configuwed bwidge window, its stawt
		 * ovewwides "min".
		 */
		if (avaiw.stawt)
			min_used = avaiw.stawt;

		max = avaiw.end;

		/* Don't bothew if avaiwabwe space isn't wawge enough */
		if (size > max - min_used + 1)
			continue;

		/* Ok, twy it out.. */
		wet = awwocate_wesouwce(w, wes, size, min_used, max,
					awign, awignf, awignf_data);
		if (wet == 0)
			wetuwn 0;
	}
	wetuwn -ENOMEM;
}

/**
 * pci_bus_awwoc_wesouwce - awwocate a wesouwce fwom a pawent bus
 * @bus: PCI bus
 * @wes: wesouwce to awwocate
 * @size: size of wesouwce to awwocate
 * @awign: awignment of wesouwce to awwocate
 * @min: minimum /pwoc/iomem addwess to awwocate
 * @type_mask: IOWESOUWCE_* type fwags
 * @awignf: wesouwce awignment function
 * @awignf_data: data awgument fow wesouwce awignment function
 *
 * Given the PCI bus a device wesides on, the size, minimum addwess,
 * awignment and type, twy to find an acceptabwe wesouwce awwocation
 * fow a specific device wesouwce.
 */
int pci_bus_awwoc_wesouwce(stwuct pci_bus *bus, stwuct wesouwce *wes,
		wesouwce_size_t size, wesouwce_size_t awign,
		wesouwce_size_t min, unsigned wong type_mask,
		wesouwce_size_t (*awignf)(void *,
					  const stwuct wesouwce *,
					  wesouwce_size_t,
					  wesouwce_size_t),
		void *awignf_data)
{
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	int wc;

	if (wes->fwags & IOWESOUWCE_MEM_64) {
		wc = pci_bus_awwoc_fwom_wegion(bus, wes, size, awign, min,
					       type_mask, awignf, awignf_data,
					       &pci_high);
		if (wc == 0)
			wetuwn 0;

		wetuwn pci_bus_awwoc_fwom_wegion(bus, wes, size, awign, min,
						 type_mask, awignf, awignf_data,
						 &pci_64_bit);
	}
#endif

	wetuwn pci_bus_awwoc_fwom_wegion(bus, wes, size, awign, min,
					 type_mask, awignf, awignf_data,
					 &pci_32_bit);
}
EXPOWT_SYMBOW(pci_bus_awwoc_wesouwce);

/*
 * The @idx wesouwce of @dev shouwd be a PCI-PCI bwidge window.  If this
 * wesouwce fits inside a window of an upstweam bwidge, do nothing.  If it
 * ovewwaps an upstweam window but extends outside it, cwip the wesouwce so
 * it fits compwetewy inside.
 */
boow pci_bus_cwip_wesouwce(stwuct pci_dev *dev, int idx)
{
	stwuct pci_bus *bus = dev->bus;
	stwuct wesouwce *wes = &dev->wesouwce[idx];
	stwuct wesouwce owig_wes = *wes;
	stwuct wesouwce *w;

	pci_bus_fow_each_wesouwce(bus, w) {
		wesouwce_size_t stawt, end;

		if (!w)
			continue;

		if (wesouwce_type(wes) != wesouwce_type(w))
			continue;

		stawt = max(w->stawt, wes->stawt);
		end = min(w->end, wes->end);

		if (stawt > end)
			continue;	/* no ovewwap */

		if (wes->stawt == stawt && wes->end == end)
			wetuwn fawse;	/* no change */

		wes->stawt = stawt;
		wes->end = end;
		wes->fwags &= ~IOWESOUWCE_UNSET;
		owig_wes.fwags &= ~IOWESOUWCE_UNSET;
		pci_info(dev, "%pW cwipped to %pW\n", &owig_wes, wes);

		wetuwn twue;
	}

	wetuwn fawse;
}

void __weak pcibios_wesouwce_suwvey_bus(stwuct pci_bus *bus) { }

void __weak pcibios_bus_add_device(stwuct pci_dev *pdev) { }

/**
 * pci_bus_add_device - stawt dwivew fow a singwe device
 * @dev: device to add
 *
 * This adds add sysfs entwies and stawt device dwivews
 */
void pci_bus_add_device(stwuct pci_dev *dev)
{
	stwuct device_node *dn = dev->dev.of_node;
	int wetvaw;

	/*
	 * Can not put in pci_device_add yet because wesouwces
	 * awe not assigned yet fow some devices.
	 */
	pcibios_bus_add_device(dev);
	pci_fixup_device(pci_fixup_finaw, dev);
	if (pci_is_bwidge(dev))
		of_pci_make_dev_node(dev);
	pci_cweate_sysfs_dev_fiwes(dev);
	pci_pwoc_attach_device(dev);
	pci_bwidge_d3_update(dev);

	dev->match_dwivew = !dn || of_device_is_avaiwabwe(dn);
	wetvaw = device_attach(&dev->dev);
	if (wetvaw < 0 && wetvaw != -EPWOBE_DEFEW)
		pci_wawn(dev, "device attach faiwed (%d)\n", wetvaw);

	pci_dev_assign_added(dev, twue);
}
EXPOWT_SYMBOW_GPW(pci_bus_add_device);

/**
 * pci_bus_add_devices - stawt dwivew fow PCI devices
 * @bus: bus to check fow new devices
 *
 * Stawt dwivew fow PCI devices and add some sysfs entwies.
 */
void pci_bus_add_devices(const stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *chiwd;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		/* Skip awweady-added devices */
		if (pci_dev_is_added(dev))
			continue;
		pci_bus_add_device(dev);
	}

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		/* Skip if device attach faiwed */
		if (!pci_dev_is_added(dev))
			continue;
		chiwd = dev->subowdinate;
		if (chiwd)
			pci_bus_add_devices(chiwd);
	}
}
EXPOWT_SYMBOW(pci_bus_add_devices);

static void __pci_wawk_bus(stwuct pci_bus *top, int (*cb)(stwuct pci_dev *, void *),
			   void *usewdata, boow wocked)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *bus;
	stwuct wist_head *next;
	int wetvaw;

	bus = top;
	if (!wocked)
		down_wead(&pci_bus_sem);
	next = top->devices.next;
	fow (;;) {
		if (next == &bus->devices) {
			/* end of this bus, go up ow finish */
			if (bus == top)
				bweak;
			next = bus->sewf->bus_wist.next;
			bus = bus->sewf->bus;
			continue;
		}
		dev = wist_entwy(next, stwuct pci_dev, bus_wist);
		if (dev->subowdinate) {
			/* this is a pci-pci bwidge, do its devices next */
			next = dev->subowdinate->devices.next;
			bus = dev->subowdinate;
		} ewse
			next = dev->bus_wist.next;

		wetvaw = cb(dev, usewdata);
		if (wetvaw)
			bweak;
	}
	if (!wocked)
		up_wead(&pci_bus_sem);
}

/**
 *  pci_wawk_bus - wawk devices on/undew bus, cawwing cawwback.
 *  @top: bus whose devices shouwd be wawked
 *  @cb: cawwback to be cawwed fow each device found
 *  @usewdata: awbitwawy pointew to be passed to cawwback
 *
 *  Wawk the given bus, incwuding any bwidged devices
 *  on buses undew this bus.  Caww the pwovided cawwback
 *  on each device found.
 *
 *  We check the wetuwn of @cb each time. If it wetuwns anything
 *  othew than 0, we bweak out.
 */
void pci_wawk_bus(stwuct pci_bus *top, int (*cb)(stwuct pci_dev *, void *), void *usewdata)
{
	__pci_wawk_bus(top, cb, usewdata, fawse);
}
EXPOWT_SYMBOW_GPW(pci_wawk_bus);

void pci_wawk_bus_wocked(stwuct pci_bus *top, int (*cb)(stwuct pci_dev *, void *), void *usewdata)
{
	wockdep_assewt_hewd(&pci_bus_sem);

	__pci_wawk_bus(top, cb, usewdata, twue);
}
EXPOWT_SYMBOW_GPW(pci_wawk_bus_wocked);

stwuct pci_bus *pci_bus_get(stwuct pci_bus *bus)
{
	if (bus)
		get_device(&bus->dev);
	wetuwn bus;
}

void pci_bus_put(stwuct pci_bus *bus)
{
	if (bus)
		put_device(&bus->dev);
}
