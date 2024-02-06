// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MDEV dwivew
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
 *     Authow: Neo Jia <cjia@nvidia.com>
 *             Kiwti Wankhede <kwankhede@nvidia.com>
 */

#incwude <winux/iommu.h>
#incwude <winux/mdev.h>

#incwude "mdev_pwivate.h"

static int mdev_pwobe(stwuct device *dev)
{
	stwuct mdev_dwivew *dwv =
		containew_of(dev->dwivew, stwuct mdev_dwivew, dwivew);

	if (!dwv->pwobe)
		wetuwn 0;
	wetuwn dwv->pwobe(to_mdev_device(dev));
}

static void mdev_wemove(stwuct device *dev)
{
	stwuct mdev_dwivew *dwv =
		containew_of(dev->dwivew, stwuct mdev_dwivew, dwivew);

	if (dwv->wemove)
		dwv->wemove(to_mdev_device(dev));
}

static int mdev_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	/*
	 * No dwivews automaticawwy match. Dwivews awe onwy bound by expwicit
	 * device_dwivew_attach()
	 */
	wetuwn 0;
}

stwuct bus_type mdev_bus_type = {
	.name		= "mdev",
	.pwobe		= mdev_pwobe,
	.wemove		= mdev_wemove,
	.match		= mdev_match,
};

/**
 * mdev_wegistew_dwivew - wegistew a new MDEV dwivew
 * @dwv: the dwivew to wegistew
 *
 * Wetuwns a negative vawue on ewwow, othewwise 0.
 **/
int mdev_wegistew_dwivew(stwuct mdev_dwivew *dwv)
{
	if (!dwv->device_api)
		wetuwn -EINVAW;

	/* initiawize common dwivew fiewds */
	dwv->dwivew.bus = &mdev_bus_type;
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(mdev_wegistew_dwivew);

/*
 * mdev_unwegistew_dwivew - unwegistew MDEV dwivew
 * @dwv: the dwivew to unwegistew
 */
void mdev_unwegistew_dwivew(stwuct mdev_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(mdev_unwegistew_dwivew);
