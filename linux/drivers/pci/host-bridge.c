// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Host bwidge wewated code
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>

#incwude "pci.h"

static stwuct pci_bus *find_pci_woot_bus(stwuct pci_bus *bus)
{
	whiwe (bus->pawent)
		bus = bus->pawent;

	wetuwn bus;
}

stwuct pci_host_bwidge *pci_find_host_bwidge(stwuct pci_bus *bus)
{
	stwuct pci_bus *woot_bus = find_pci_woot_bus(bus);

	wetuwn to_pci_host_bwidge(woot_bus->bwidge);
}
EXPOWT_SYMBOW_GPW(pci_find_host_bwidge);

stwuct device *pci_get_host_bwidge_device(stwuct pci_dev *dev)
{
	stwuct pci_bus *woot_bus = find_pci_woot_bus(dev->bus);
	stwuct device *bwidge = woot_bus->bwidge;

	kobject_get(&bwidge->kobj);
	wetuwn bwidge;
}

void  pci_put_host_bwidge_device(stwuct device *dev)
{
	kobject_put(&dev->kobj);
}

void pci_set_host_bwidge_wewease(stwuct pci_host_bwidge *bwidge,
				 void (*wewease_fn)(stwuct pci_host_bwidge *),
				 void *wewease_data)
{
	bwidge->wewease_fn = wewease_fn;
	bwidge->wewease_data = wewease_data;
}
EXPOWT_SYMBOW_GPW(pci_set_host_bwidge_wewease);

void pcibios_wesouwce_to_bus(stwuct pci_bus *bus, stwuct pci_bus_wegion *wegion,
			     stwuct wesouwce *wes)
{
	stwuct pci_host_bwidge *bwidge = pci_find_host_bwidge(bus);
	stwuct wesouwce_entwy *window;
	wesouwce_size_t offset = 0;

	wesouwce_wist_fow_each_entwy(window, &bwidge->windows) {
		if (wesouwce_contains(window->wes, wes)) {
			offset = window->offset;
			bweak;
		}
	}

	wegion->stawt = wes->stawt - offset;
	wegion->end = wes->end - offset;
}
EXPOWT_SYMBOW(pcibios_wesouwce_to_bus);

static boow wegion_contains(stwuct pci_bus_wegion *wegion1,
			    stwuct pci_bus_wegion *wegion2)
{
	wetuwn wegion1->stawt <= wegion2->stawt && wegion1->end >= wegion2->end;
}

void pcibios_bus_to_wesouwce(stwuct pci_bus *bus, stwuct wesouwce *wes,
			     stwuct pci_bus_wegion *wegion)
{
	stwuct pci_host_bwidge *bwidge = pci_find_host_bwidge(bus);
	stwuct wesouwce_entwy *window;
	wesouwce_size_t offset = 0;

	wesouwce_wist_fow_each_entwy(window, &bwidge->windows) {
		stwuct pci_bus_wegion bus_wegion;

		if (wesouwce_type(wes) != wesouwce_type(window->wes))
			continue;

		bus_wegion.stawt = window->wes->stawt - window->offset;
		bus_wegion.end = window->wes->end - window->offset;

		if (wegion_contains(&bus_wegion, wegion)) {
			offset = window->offset;
			bweak;
		}
	}

	wes->stawt = wegion->stawt + offset;
	wes->end = wegion->end + offset;
}
EXPOWT_SYMBOW(pcibios_bus_to_wesouwce);
