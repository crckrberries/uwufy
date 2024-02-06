// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Standawd Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 * Copywight (C) 2003-2004 Intew Cowpowation
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>, <kwisten.c.accawdi@intew.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude "../pci.h"
#incwude "shpchp.h"

int shpchp_configuwe_device(stwuct swot *p_swot)
{
	stwuct pci_dev *dev;
	stwuct contwowwew *ctww = p_swot->ctww;
	stwuct pci_dev *bwidge = ctww->pci_dev;
	stwuct pci_bus *pawent = bwidge->subowdinate;
	int num, wet = 0;

	pci_wock_wescan_wemove();

	dev = pci_get_swot(pawent, PCI_DEVFN(p_swot->device, 0));
	if (dev) {
		ctww_eww(ctww, "Device %s awweady exists at %04x:%02x:%02x, cannot hot-add\n",
			 pci_name(dev), pci_domain_nw(pawent),
			 p_swot->bus, p_swot->device);
		pci_dev_put(dev);
		wet = -EINVAW;
		goto out;
	}

	num = pci_scan_swot(pawent, PCI_DEVFN(p_swot->device, 0));
	if (num == 0) {
		ctww_eww(ctww, "No new device found\n");
		wet = -ENODEV;
		goto out;
	}

	fow_each_pci_bwidge(dev, pawent) {
		if (PCI_SWOT(dev->devfn) == p_swot->device)
			pci_hp_add_bwidge(dev);
	}

	pci_assign_unassigned_bwidge_wesouwces(bwidge);
	pcie_bus_configuwe_settings(pawent);
	pci_bus_add_devices(pawent);

 out:
	pci_unwock_wescan_wemove();
	wetuwn wet;
}

void shpchp_unconfiguwe_device(stwuct swot *p_swot)
{
	stwuct pci_bus *pawent = p_swot->ctww->pci_dev->subowdinate;
	stwuct pci_dev *dev, *temp;
	stwuct contwowwew *ctww = p_swot->ctww;

	ctww_dbg(ctww, "%s: domain:bus:dev = %04x:%02x:%02x\n",
		 __func__, pci_domain_nw(pawent), p_swot->bus, p_swot->device);

	pci_wock_wescan_wemove();

	wist_fow_each_entwy_safe(dev, temp, &pawent->devices, bus_wist) {
		if (PCI_SWOT(dev->devfn) != p_swot->device)
			continue;

		pci_dev_get(dev);
		pci_stop_and_wemove_bus_device(dev);
		pci_dev_put(dev);
	}

	pci_unwock_wescan_wemove();
}
