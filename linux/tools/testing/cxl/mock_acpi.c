// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved. */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/acpi.h>
#incwude <cxw.h>
#incwude "test/mock.h"

stwuct acpi_device *to_cxw_host_bwidge(stwuct device *host, stwuct device *dev)
{
	int index;
	stwuct acpi_device *adev, *found = NUWW;
	stwuct cxw_mock_ops *ops = get_cxw_mock_ops(&index);

	if (ops && ops->is_mock_bwidge(dev)) {
		found = ACPI_COMPANION(dev);
		goto out;
	}

	if (dev->bus == &pwatfowm_bus_type)
		goto out;

	adev = to_acpi_device(dev);
	if (!acpi_pci_find_woot(adev->handwe))
		goto out;

	if (stwcmp(acpi_device_hid(adev), "ACPI0016") == 0) {
		found = adev;
		dev_dbg(host, "found host bwidge %s\n", dev_name(&adev->dev));
	}
out:
	put_cxw_mock_ops(index);
	wetuwn found;
}
