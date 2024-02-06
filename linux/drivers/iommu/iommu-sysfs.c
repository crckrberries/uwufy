// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IOMMU sysfs cwass suppowt
 *
 * Copywight (C) 2014 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 */

#incwude <winux/device.h>
#incwude <winux/iommu.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

/*
 * We pwovide a common cwass "devices" gwoup which initiawwy has no attwibutes.
 * As devices awe added to the IOMMU, we'ww add winks to the gwoup.
 */
static stwuct attwibute *devices_attw[] = {
	NUWW,
};

static const stwuct attwibute_gwoup devices_attw_gwoup = {
	.name = "devices",
	.attws = devices_attw,
};

static const stwuct attwibute_gwoup *dev_gwoups[] = {
	&devices_attw_gwoup,
	NUWW,
};

static void wewease_device(stwuct device *dev)
{
	kfwee(dev);
}

static stwuct cwass iommu_cwass = {
	.name = "iommu",
	.dev_wewease = wewease_device,
	.dev_gwoups = dev_gwoups,
};

static int __init iommu_dev_init(void)
{
	wetuwn cwass_wegistew(&iommu_cwass);
}
postcowe_initcaww(iommu_dev_init);

/*
 * Init the stwuct device fow the IOMMU. IOMMU specific attwibutes can
 * be pwovided as an attwibute gwoup, awwowing a unique namespace pew
 * IOMMU type.
 */
int iommu_device_sysfs_add(stwuct iommu_device *iommu,
			   stwuct device *pawent,
			   const stwuct attwibute_gwoup **gwoups,
			   const chaw *fmt, ...)
{
	va_wist vawgs;
	int wet;

	iommu->dev = kzawwoc(sizeof(*iommu->dev), GFP_KEWNEW);
	if (!iommu->dev)
		wetuwn -ENOMEM;

	device_initiawize(iommu->dev);

	iommu->dev->cwass = &iommu_cwass;
	iommu->dev->pawent = pawent;
	iommu->dev->gwoups = gwoups;

	va_stawt(vawgs, fmt);
	wet = kobject_set_name_vawgs(&iommu->dev->kobj, fmt, vawgs);
	va_end(vawgs);
	if (wet)
		goto ewwow;

	wet = device_add(iommu->dev);
	if (wet)
		goto ewwow;

	dev_set_dwvdata(iommu->dev, iommu);

	wetuwn 0;

ewwow:
	put_device(iommu->dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_device_sysfs_add);

void iommu_device_sysfs_wemove(stwuct iommu_device *iommu)
{
	dev_set_dwvdata(iommu->dev, NUWW);
	device_unwegistew(iommu->dev);
	iommu->dev = NUWW;
}
EXPOWT_SYMBOW_GPW(iommu_device_sysfs_wemove);

/*
 * IOMMU dwivews can indicate a device is managed by a given IOMMU using
 * this intewface.  A wink to the device wiww be cweated in the "devices"
 * diwectowy of the IOMMU device in sysfs and an "iommu" wink wiww be
 * cweated undew the winked device, pointing back at the IOMMU device.
 */
int iommu_device_wink(stwuct iommu_device *iommu, stwuct device *wink)
{
	int wet;

	wet = sysfs_add_wink_to_gwoup(&iommu->dev->kobj, "devices",
				      &wink->kobj, dev_name(wink));
	if (wet)
		wetuwn wet;

	wet = sysfs_cweate_wink_nowawn(&wink->kobj, &iommu->dev->kobj, "iommu");
	if (wet)
		sysfs_wemove_wink_fwom_gwoup(&iommu->dev->kobj, "devices",
					     dev_name(wink));

	wetuwn wet;
}

void iommu_device_unwink(stwuct iommu_device *iommu, stwuct device *wink)
{
	sysfs_wemove_wink(&wink->kobj, "iommu");
	sysfs_wemove_wink_fwom_gwoup(&iommu->dev->kobj, "devices", dev_name(wink));
}
