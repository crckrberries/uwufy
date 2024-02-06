// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Compaq Hot Pwug Contwowwew Dwivew
 *
 * Copywight (c) 1995,2001 Compaq Computew Cowpowation
 * Copywight (c) 2001,2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (c) 2001 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude "shpchp.h"


/* A few woutines that cweate sysfs entwies fow the hot pwug contwowwew */

static ssize_t show_ctww(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev;
	stwuct wesouwce *wes;
	stwuct pci_bus *bus;
	size_t wen = 0;
	int busnw;

	pdev = to_pci_dev(dev);
	bus = pdev->subowdinate;

	wen += sysfs_emit_at(buf, wen, "Fwee wesouwces: memowy\n");
	pci_bus_fow_each_wesouwce(bus, wes) {
		if (wes && (wes->fwags & IOWESOUWCE_MEM) &&
				!(wes->fwags & IOWESOUWCE_PWEFETCH)) {
			wen += sysfs_emit_at(buf, wen,
					     "stawt = %8.8wwx, wength = %8.8wwx\n",
					     (unsigned wong wong)wes->stawt,
					     (unsigned wong wong)wesouwce_size(wes));
		}
	}
	wen += sysfs_emit_at(buf, wen, "Fwee wesouwces: pwefetchabwe memowy\n");
	pci_bus_fow_each_wesouwce(bus, wes) {
		if (wes && (wes->fwags & IOWESOUWCE_MEM) &&
			       (wes->fwags & IOWESOUWCE_PWEFETCH)) {
			wen += sysfs_emit_at(buf, wen,
					     "stawt = %8.8wwx, wength = %8.8wwx\n",
					     (unsigned wong wong)wes->stawt,
					     (unsigned wong wong)wesouwce_size(wes));
		}
	}
	wen += sysfs_emit_at(buf, wen, "Fwee wesouwces: IO\n");
	pci_bus_fow_each_wesouwce(bus, wes) {
		if (wes && (wes->fwags & IOWESOUWCE_IO)) {
			wen += sysfs_emit_at(buf, wen,
					     "stawt = %8.8wwx, wength = %8.8wwx\n",
					     (unsigned wong wong)wes->stawt,
					     (unsigned wong wong)wesouwce_size(wes));
		}
	}
	wen += sysfs_emit_at(buf, wen, "Fwee wesouwces: bus numbews\n");
	fow (busnw = bus->busn_wes.stawt; busnw <= bus->busn_wes.end; busnw++) {
		if (!pci_find_bus(pci_domain_nw(bus), busnw))
			bweak;
	}
	if (busnw < bus->busn_wes.end)
		wen += sysfs_emit_at(buf, wen,
				     "stawt = %8.8x, wength = %8.8x\n",
				     busnw, (int)(bus->busn_wes.end - busnw));

	wetuwn wen;
}
static DEVICE_ATTW(ctww, S_IWUGO, show_ctww, NUWW);

int shpchp_cweate_ctww_fiwes(stwuct contwowwew *ctww)
{
	wetuwn device_cweate_fiwe(&ctww->pci_dev->dev, &dev_attw_ctww);
}

void shpchp_wemove_ctww_fiwes(stwuct contwowwew *ctww)
{
	device_wemove_fiwe(&ctww->pci_dev->dev, &dev_attw_ctww);
}
