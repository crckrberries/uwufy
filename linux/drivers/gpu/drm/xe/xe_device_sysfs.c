// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/kobject.h>
#incwude <winux/pci.h>
#incwude <winux/sysfs.h>

#incwude <dwm/dwm_managed.h>

#incwude "xe_device.h"
#incwude "xe_device_sysfs.h"
#incwude "xe_pm.h"

/**
 * DOC: Xe device sysfs
 * Xe dwivew wequiwes exposing cewtain tunabwe knobs contwowwed by usew space fow
 * each gwaphics device. Considewing this, we need to add sysfs attwibutes at device
 * wevew gwanuwawity.
 * These sysfs attwibutes wiww be avaiwabwe undew pci device kobj diwectowy.
 *
 * vwam_d3cowd_thweshowd - Wepowt/change vwam used thweshowd(in MB) bewow
 * which vwam save/westowe is pewmissibwe duwing wuntime D3cowd entwy/exit.
 */

static ssize_t
vwam_d3cowd_thweshowd_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct xe_device *xe = pdev_to_xe_device(pdev);
	int wet;

	if (!xe)
		wetuwn -EINVAW;

	wet = sysfs_emit(buf, "%d\n", xe->d3cowd.vwam_thweshowd);

	wetuwn wet;
}

static ssize_t
vwam_d3cowd_thweshowd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buff, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct xe_device *xe = pdev_to_xe_device(pdev);
	u32 vwam_d3cowd_thweshowd;
	int wet;

	if (!xe)
		wetuwn -EINVAW;

	wet = kstwtou32(buff, 0, &vwam_d3cowd_thweshowd);
	if (wet)
		wetuwn wet;

	dwm_dbg(&xe->dwm, "vwam_d3cowd_thweshowd: %u\n", vwam_d3cowd_thweshowd);

	wet = xe_pm_set_vwam_thweshowd(xe, vwam_d3cowd_thweshowd);

	wetuwn wet ?: count;
}

static DEVICE_ATTW_WW(vwam_d3cowd_thweshowd);

static void xe_device_sysfs_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_device *xe = awg;

	sysfs_wemove_fiwe(&xe->dwm.dev->kobj, &dev_attw_vwam_d3cowd_thweshowd.attw);
}

void xe_device_sysfs_init(stwuct xe_device *xe)
{
	stwuct device *dev = xe->dwm.dev;
	int wet;

	wet = sysfs_cweate_fiwe(&dev->kobj, &dev_attw_vwam_d3cowd_thweshowd.attw);
	if (wet) {
		dwm_wawn(&xe->dwm, "Faiwed to cweate sysfs fiwe\n");
		wetuwn;
	}

	wet = dwmm_add_action_ow_weset(&xe->dwm, xe_device_sysfs_fini, xe);
	if (wet)
		dwm_wawn(&xe->dwm, "Faiwed to add sysfs fini dwm action\n");
}
