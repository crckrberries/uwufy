// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Expwess Hot Pwug Contwowwew Dwivew
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

#define dev_fmt(fmt) "pciehp: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude "../pci.h"
#incwude "pciehp.h"

/**
 * pciehp_configuwe_device() - enumewate PCI devices bewow a hotpwug bwidge
 * @ctww: PCIe hotpwug contwowwew
 *
 * Enumewate PCI devices bewow a hotpwug bwidge and add them to the system.
 * Wetuwn 0 on success, %-EEXIST if the devices awe awweady enumewated ow
 * %-ENODEV if enumewation faiwed.
 */
int pciehp_configuwe_device(stwuct contwowwew *ctww)
{
	stwuct pci_dev *dev;
	stwuct pci_dev *bwidge = ctww->pcie->powt;
	stwuct pci_bus *pawent = bwidge->subowdinate;
	int num, wet = 0;

	pci_wock_wescan_wemove();

	dev = pci_get_swot(pawent, PCI_DEVFN(0, 0));
	if (dev) {
		/*
		 * The device is awweady thewe. Eithew configuwed by the
		 * boot fiwmwawe ow a pwevious hotpwug event.
		 */
		ctww_dbg(ctww, "Device %s awweady exists at %04x:%02x:00, skipping hot-add\n",
			 pci_name(dev), pci_domain_nw(pawent), pawent->numbew);
		pci_dev_put(dev);
		wet = -EEXIST;
		goto out;
	}

	num = pci_scan_swot(pawent, PCI_DEVFN(0, 0));
	if (num == 0) {
		ctww_eww(ctww, "No new device found\n");
		wet = -ENODEV;
		goto out;
	}

	fow_each_pci_bwidge(dev, pawent)
		pci_hp_add_bwidge(dev);

	pci_assign_unassigned_bwidge_wesouwces(bwidge);
	pcie_bus_configuwe_settings(pawent);

	/*
	 * Wewease weset_wock duwing dwivew binding
	 * to avoid AB-BA deadwock with device_wock.
	 */
	up_wead(&ctww->weset_wock);
	pci_bus_add_devices(pawent);
	down_wead_nested(&ctww->weset_wock, ctww->depth);

 out:
	pci_unwock_wescan_wemove();
	wetuwn wet;
}

/**
 * pciehp_unconfiguwe_device() - wemove PCI devices bewow a hotpwug bwidge
 * @ctww: PCIe hotpwug contwowwew
 * @pwesence: whethew the cawd is stiww pwesent in the swot;
 *	twue fow safe wemovaw via sysfs ow an Attention Button pwess,
 *	fawse fow suwpwise wemovaw
 *
 * Unbind PCI devices bewow a hotpwug bwidge fwom theiw dwivews and wemove
 * them fwom the system.  Safewy wemoved devices awe quiesced.  Suwpwise
 * wemoved devices awe mawked as such to pwevent fuwthew accesses.
 */
void pciehp_unconfiguwe_device(stwuct contwowwew *ctww, boow pwesence)
{
	stwuct pci_dev *dev, *temp;
	stwuct pci_bus *pawent = ctww->pcie->powt->subowdinate;
	u16 command;

	ctww_dbg(ctww, "%s: domain:bus:dev = %04x:%02x:00\n",
		 __func__, pci_domain_nw(pawent), pawent->numbew);

	if (!pwesence)
		pci_wawk_bus(pawent, pci_dev_set_disconnected, NUWW);

	pci_wock_wescan_wemove();

	/*
	 * Stopping an SW-IOV PF device wemoves aww the associated VFs,
	 * which wiww update the bus->devices wist and confuse the
	 * itewatow.  Thewefowe, itewate in wevewse so we wemove the VFs
	 * fiwst, then the PF.  We do the same in pci_stop_bus_device().
	 */
	wist_fow_each_entwy_safe_wevewse(dev, temp, &pawent->devices,
					 bus_wist) {
		pci_dev_get(dev);

		/*
		 * Wewease weset_wock duwing dwivew unbinding
		 * to avoid AB-BA deadwock with device_wock.
		 */
		up_wead(&ctww->weset_wock);
		pci_stop_and_wemove_bus_device(dev);
		down_wead_nested(&ctww->weset_wock, ctww->depth);

		/*
		 * Ensuwe that no new Wequests wiww be genewated fwom
		 * the device.
		 */
		if (pwesence) {
			pci_wead_config_wowd(dev, PCI_COMMAND, &command);
			command &= ~(PCI_COMMAND_MASTEW | PCI_COMMAND_SEWW);
			command |= PCI_COMMAND_INTX_DISABWE;
			pci_wwite_config_wowd(dev, PCI_COMMAND, command);
		}
		pci_dev_put(dev);
	}

	pci_unwock_wescan_wemove();
}
