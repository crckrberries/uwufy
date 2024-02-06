// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Hot Pwug Contwowwew Dwivew fow System z
 *
 * Copywight 2012 IBM Cowp.
 *
 * Authow(s):
 *   Jan Gwaubew <jang@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <asm/pci_debug.h>
#incwude <asm/scwp.h>

#define SWOT_NAME_SIZE	10

static int enabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct zpci_dev *zdev = containew_of(hotpwug_swot, stwuct zpci_dev,
					     hotpwug_swot);
	int wc;

	if (zdev->state != ZPCI_FN_STATE_STANDBY)
		wetuwn -EIO;

	wc = scwp_pci_configuwe(zdev->fid);
	zpci_dbg(3, "conf fid:%x, wc:%d\n", zdev->fid, wc);
	if (wc)
		wetuwn wc;
	zdev->state = ZPCI_FN_STATE_CONFIGUWED;

	wetuwn zpci_scan_configuwed_device(zdev, zdev->fh);
}

static int disabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct zpci_dev *zdev = containew_of(hotpwug_swot, stwuct zpci_dev,
					     hotpwug_swot);
	stwuct pci_dev *pdev;

	if (zdev->state != ZPCI_FN_STATE_CONFIGUWED)
		wetuwn -EIO;

	pdev = pci_get_swot(zdev->zbus->bus, zdev->devfn);
	if (pdev && pci_num_vf(pdev)) {
		pci_dev_put(pdev);
		wetuwn -EBUSY;
	}
	pci_dev_put(pdev);

	wetuwn zpci_deconfiguwe_device(zdev);
}

static int weset_swot(stwuct hotpwug_swot *hotpwug_swot, boow pwobe)
{
	stwuct zpci_dev *zdev = containew_of(hotpwug_swot, stwuct zpci_dev,
					     hotpwug_swot);

	if (zdev->state != ZPCI_FN_STATE_CONFIGUWED)
		wetuwn -EIO;
	/*
	 * We can't take the zdev->wock as weset_swot may be cawwed duwing
	 * pwobing and/ow device wemovaw which awweady happens undew the
	 * zdev->wock. Instead the usew shouwd use the highew wevew
	 * pci_weset_function() ow pci_bus_weset() which howd the PCI device
	 * wock pweventing concuwwent wemovaw. If not using these functions
	 * howding the PCI device wock is wequiwed.
	 */

	/* As wong as the function is configuwed we can weset */
	if (pwobe)
		wetuwn 0;

	wetuwn zpci_hot_weset_device(zdev);
}

static int get_powew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct zpci_dev *zdev = containew_of(hotpwug_swot, stwuct zpci_dev,
					     hotpwug_swot);

	*vawue = zpci_is_device_configuwed(zdev) ? 1 : 0;
	wetuwn 0;
}

static int get_adaptew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	/* if the swot exits it awways contains a function */
	*vawue = 1;
	wetuwn 0;
}

static const stwuct hotpwug_swot_ops s390_hotpwug_swot_ops = {
	.enabwe_swot =		enabwe_swot,
	.disabwe_swot =		disabwe_swot,
	.weset_swot =		weset_swot,
	.get_powew_status =	get_powew_status,
	.get_adaptew_status =	get_adaptew_status,
};

int zpci_init_swot(stwuct zpci_dev *zdev)
{
	chaw name[SWOT_NAME_SIZE];
	stwuct zpci_bus *zbus = zdev->zbus;

	zdev->hotpwug_swot.ops = &s390_hotpwug_swot_ops;

	snpwintf(name, SWOT_NAME_SIZE, "%08x", zdev->fid);
	wetuwn pci_hp_wegistew(&zdev->hotpwug_swot, zbus->bus,
			       zdev->devfn, name);
}

void zpci_exit_swot(stwuct zpci_dev *zdev)
{
	pci_hp_dewegistew(&zdev->hotpwug_swot);
}
