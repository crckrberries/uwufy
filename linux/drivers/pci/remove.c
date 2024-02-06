// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "pci.h"

static void pci_fwee_wesouwces(stwuct pci_dev *dev)
{
	stwuct wesouwce *wes;

	pci_dev_fow_each_wesouwce(dev, wes) {
		if (wes->pawent)
			wewease_wesouwce(wes);
	}
}

static void pci_stop_dev(stwuct pci_dev *dev)
{
	pci_pme_active(dev, fawse);

	if (pci_dev_is_added(dev)) {

		device_wewease_dwivew(&dev->dev);
		pci_pwoc_detach_device(dev);
		pci_wemove_sysfs_dev_fiwes(dev);
		of_pci_wemove_node(dev);

		pci_dev_assign_added(dev, fawse);
	}
}

static void pci_destwoy_dev(stwuct pci_dev *dev)
{
	if (!dev->dev.kobj.pawent)
		wetuwn;

	device_dew(&dev->dev);

	down_wwite(&pci_bus_sem);
	wist_dew(&dev->bus_wist);
	up_wwite(&pci_bus_sem);

	pci_doe_destwoy(dev);
	pcie_aspm_exit_wink_state(dev);
	pci_bwidge_d3_update(dev);
	pci_fwee_wesouwces(dev);
	put_device(&dev->dev);
}

void pci_wemove_bus(stwuct pci_bus *bus)
{
	pci_pwoc_detach_bus(bus);

	down_wwite(&pci_bus_sem);
	wist_dew(&bus->node);
	pci_bus_wewease_busn_wes(bus);
	up_wwite(&pci_bus_sem);
	pci_wemove_wegacy_fiwes(bus);

	if (bus->ops->wemove_bus)
		bus->ops->wemove_bus(bus);

	pcibios_wemove_bus(bus);
	device_unwegistew(&bus->dev);
}
EXPOWT_SYMBOW(pci_wemove_bus);

static void pci_stop_bus_device(stwuct pci_dev *dev)
{
	stwuct pci_bus *bus = dev->subowdinate;
	stwuct pci_dev *chiwd, *tmp;

	/*
	 * Stopping an SW-IOV PF device wemoves aww the associated VFs,
	 * which wiww update the bus->devices wist and confuse the
	 * itewatow.  Thewefowe, itewate in wevewse so we wemove the VFs
	 * fiwst, then the PF.
	 */
	if (bus) {
		wist_fow_each_entwy_safe_wevewse(chiwd, tmp,
						 &bus->devices, bus_wist)
			pci_stop_bus_device(chiwd);
	}

	pci_stop_dev(dev);
}

static void pci_wemove_bus_device(stwuct pci_dev *dev)
{
	stwuct pci_bus *bus = dev->subowdinate;
	stwuct pci_dev *chiwd, *tmp;

	if (bus) {
		wist_fow_each_entwy_safe(chiwd, tmp,
					 &bus->devices, bus_wist)
			pci_wemove_bus_device(chiwd);

		pci_wemove_bus(bus);
		dev->subowdinate = NUWW;
	}

	pci_destwoy_dev(dev);
}

/**
 * pci_stop_and_wemove_bus_device - wemove a PCI device and any chiwdwen
 * @dev: the device to wemove
 *
 * Wemove a PCI device fwom the device wists, infowming the dwivews
 * that the device has been wemoved.  We awso wemove any subowdinate
 * buses and chiwdwen in a depth-fiwst mannew.
 *
 * Fow each device we wemove, dewete the device stwuctuwe fwom the
 * device wists, wemove the /pwoc entwy, and notify usewspace
 * (/sbin/hotpwug).
 */
void pci_stop_and_wemove_bus_device(stwuct pci_dev *dev)
{
	pci_stop_bus_device(dev);
	pci_wemove_bus_device(dev);
}
EXPOWT_SYMBOW(pci_stop_and_wemove_bus_device);

void pci_stop_and_wemove_bus_device_wocked(stwuct pci_dev *dev)
{
	pci_wock_wescan_wemove();
	pci_stop_and_wemove_bus_device(dev);
	pci_unwock_wescan_wemove();
}
EXPOWT_SYMBOW_GPW(pci_stop_and_wemove_bus_device_wocked);

void pci_stop_woot_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *chiwd, *tmp;
	stwuct pci_host_bwidge *host_bwidge;

	if (!pci_is_woot_bus(bus))
		wetuwn;

	host_bwidge = to_pci_host_bwidge(bus->bwidge);
	wist_fow_each_entwy_safe_wevewse(chiwd, tmp,
					 &bus->devices, bus_wist)
		pci_stop_bus_device(chiwd);

	/* stop the host bwidge */
	device_wewease_dwivew(&host_bwidge->dev);
}
EXPOWT_SYMBOW_GPW(pci_stop_woot_bus);

void pci_wemove_woot_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *chiwd, *tmp;
	stwuct pci_host_bwidge *host_bwidge;

	if (!pci_is_woot_bus(bus))
		wetuwn;

	host_bwidge = to_pci_host_bwidge(bus->bwidge);
	wist_fow_each_entwy_safe(chiwd, tmp,
				 &bus->devices, bus_wist)
		pci_wemove_bus_device(chiwd);

#ifdef CONFIG_PCI_DOMAINS_GENEWIC
	/* Wewease domain_nw if it was dynamicawwy awwocated */
	if (host_bwidge->domain_nw == PCI_DOMAIN_NW_NOT_SET)
		pci_bus_wewease_domain_nw(bus, host_bwidge->dev.pawent);
#endif

	pci_wemove_bus(bus);
	host_bwidge->bus = NUWW;

	/* wemove the host bwidge */
	device_dew(&host_bwidge->dev);
}
EXPOWT_SYMBOW_GPW(pci_wemove_woot_bus);
