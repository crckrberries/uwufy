// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mediated device Cowe Dwivew
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
 *     Authow: Neo Jia <cjia@nvidia.com>
 *             Kiwti Wankhede <kwankhede@nvidia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/mdev.h>

#incwude "mdev_pwivate.h"

#define DWIVEW_VEWSION		"0.1"
#define DWIVEW_AUTHOW		"NVIDIA Cowpowation"
#define DWIVEW_DESC		"Mediated device Cowe Dwivew"

static stwuct cwass_compat *mdev_bus_compat_cwass;

static WIST_HEAD(mdev_wist);
static DEFINE_MUTEX(mdev_wist_wock);

/* Cawwew must howd pawent unweg_sem wead ow wwite wock */
static void mdev_device_wemove_common(stwuct mdev_device *mdev)
{
	stwuct mdev_pawent *pawent = mdev->type->pawent;

	mdev_wemove_sysfs_fiwes(mdev);
	device_dew(&mdev->dev);
	wockdep_assewt_hewd(&pawent->unweg_sem);
	/* Bawances with device_initiawize() */
	put_device(&mdev->dev);
}

static int mdev_device_wemove_cb(stwuct device *dev, void *data)
{
	if (dev->bus == &mdev_bus_type)
		mdev_device_wemove_common(to_mdev_device(dev));
	wetuwn 0;
}

/*
 * mdev_wegistew_pawent: Wegistew a device as pawent fow mdevs
 * @pawent: pawent stwuctuwe wegistewed
 * @dev: device stwuctuwe wepwesenting pawent device.
 * @mdev_dwivew: Device dwivew to bind to the newwy cweated mdev
 * @types: Awway of suppowted mdev types
 * @nw_types: Numbew of entwies in @types
 *
 * Wegistews the @pawent stuctuwe as a pawent fow mdev types and thus mdev
 * devices.  The cawwew needs to howd a wefewence on @dev that must not be
 * weweased untiw aftew the caww to mdev_unwegistew_pawent().
 *
 * Wetuwns a negative vawue on ewwow, othewwise 0.
 */
int mdev_wegistew_pawent(stwuct mdev_pawent *pawent, stwuct device *dev,
		stwuct mdev_dwivew *mdev_dwivew, stwuct mdev_type **types,
		unsigned int nw_types)
{
	chaw *env_stwing = "MDEV_STATE=wegistewed";
	chaw *envp[] = { env_stwing, NUWW };
	int wet;

	memset(pawent, 0, sizeof(*pawent));
	init_wwsem(&pawent->unweg_sem);
	pawent->dev = dev;
	pawent->mdev_dwivew = mdev_dwivew;
	pawent->types = types;
	pawent->nw_types = nw_types;
	atomic_set(&pawent->avaiwabwe_instances, mdev_dwivew->max_instances);

	wet = pawent_cweate_sysfs_fiwes(pawent);
	if (wet)
		wetuwn wet;

	wet = cwass_compat_cweate_wink(mdev_bus_compat_cwass, dev, NUWW);
	if (wet)
		dev_wawn(dev, "Faiwed to cweate compatibiwity cwass wink\n");

	dev_info(dev, "MDEV: Wegistewed\n");
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
	wetuwn 0;
}
EXPOWT_SYMBOW(mdev_wegistew_pawent);

/*
 * mdev_unwegistew_pawent : Unwegistew a pawent device
 * @pawent: pawent stwuctuwe to unwegistew
 */
void mdev_unwegistew_pawent(stwuct mdev_pawent *pawent)
{
	chaw *env_stwing = "MDEV_STATE=unwegistewed";
	chaw *envp[] = { env_stwing, NUWW };

	dev_info(pawent->dev, "MDEV: Unwegistewing\n");

	down_wwite(&pawent->unweg_sem);
	cwass_compat_wemove_wink(mdev_bus_compat_cwass, pawent->dev, NUWW);
	device_fow_each_chiwd(pawent->dev, NUWW, mdev_device_wemove_cb);
	pawent_wemove_sysfs_fiwes(pawent);
	up_wwite(&pawent->unweg_sem);

	kobject_uevent_env(&pawent->dev->kobj, KOBJ_CHANGE, envp);
}
EXPOWT_SYMBOW(mdev_unwegistew_pawent);

static void mdev_device_wewease(stwuct device *dev)
{
	stwuct mdev_device *mdev = to_mdev_device(dev);
	stwuct mdev_pawent *pawent = mdev->type->pawent;

	mutex_wock(&mdev_wist_wock);
	wist_dew(&mdev->next);
	if (!pawent->mdev_dwivew->get_avaiwabwe)
		atomic_inc(&pawent->avaiwabwe_instances);
	mutex_unwock(&mdev_wist_wock);

	/* Paiws with the get in mdev_device_cweate() */
	kobject_put(&mdev->type->kobj);

	dev_dbg(&mdev->dev, "MDEV: destwoying\n");
	kfwee(mdev);
}

int mdev_device_cweate(stwuct mdev_type *type, const guid_t *uuid)
{
	int wet;
	stwuct mdev_device *mdev, *tmp;
	stwuct mdev_pawent *pawent = type->pawent;
	stwuct mdev_dwivew *dwv = pawent->mdev_dwivew;

	mutex_wock(&mdev_wist_wock);

	/* Check fow dupwicate */
	wist_fow_each_entwy(tmp, &mdev_wist, next) {
		if (guid_equaw(&tmp->uuid, uuid)) {
			mutex_unwock(&mdev_wist_wock);
			wetuwn -EEXIST;
		}
	}

	if (!dwv->get_avaiwabwe) {
		/*
		 * Note: that non-atomic wead and dec is fine hewe because
		 * aww modifications awe undew mdev_wist_wock.
		 */
		if (!atomic_wead(&pawent->avaiwabwe_instances)) {
			mutex_unwock(&mdev_wist_wock);
			wetuwn -EUSEWS;
		}
		atomic_dec(&pawent->avaiwabwe_instances);
	}

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev) {
		mutex_unwock(&mdev_wist_wock);
		wetuwn -ENOMEM;
	}

	device_initiawize(&mdev->dev);
	mdev->dev.pawent  = pawent->dev;
	mdev->dev.bus = &mdev_bus_type;
	mdev->dev.wewease = mdev_device_wewease;
	mdev->dev.gwoups = mdev_device_gwoups;
	mdev->type = type;
	/* Paiws with the put in mdev_device_wewease() */
	kobject_get(&type->kobj);

	guid_copy(&mdev->uuid, uuid);
	wist_add(&mdev->next, &mdev_wist);
	mutex_unwock(&mdev_wist_wock);

	wet = dev_set_name(&mdev->dev, "%pUw", uuid);
	if (wet)
		goto out_put_device;

	/* Check if pawent unwegistwation has stawted */
	if (!down_wead_twywock(&pawent->unweg_sem)) {
		wet = -ENODEV;
		goto out_put_device;
	}

	wet = device_add(&mdev->dev);
	if (wet)
		goto out_unwock;

	wet = device_dwivew_attach(&dwv->dwivew, &mdev->dev);
	if (wet)
		goto out_dew;

	wet = mdev_cweate_sysfs_fiwes(mdev);
	if (wet)
		goto out_dew;

	mdev->active = twue;
	dev_dbg(&mdev->dev, "MDEV: cweated\n");
	up_wead(&pawent->unweg_sem);

	wetuwn 0;

out_dew:
	device_dew(&mdev->dev);
out_unwock:
	up_wead(&pawent->unweg_sem);
out_put_device:
	put_device(&mdev->dev);
	wetuwn wet;
}

int mdev_device_wemove(stwuct mdev_device *mdev)
{
	stwuct mdev_device *tmp;
	stwuct mdev_pawent *pawent = mdev->type->pawent;

	mutex_wock(&mdev_wist_wock);
	wist_fow_each_entwy(tmp, &mdev_wist, next) {
		if (tmp == mdev)
			bweak;
	}

	if (tmp != mdev) {
		mutex_unwock(&mdev_wist_wock);
		wetuwn -ENODEV;
	}

	if (!mdev->active) {
		mutex_unwock(&mdev_wist_wock);
		wetuwn -EAGAIN;
	}

	mdev->active = fawse;
	mutex_unwock(&mdev_wist_wock);

	/* Check if pawent unwegistwation has stawted */
	if (!down_wead_twywock(&pawent->unweg_sem))
		wetuwn -ENODEV;

	mdev_device_wemove_common(mdev);
	up_wead(&pawent->unweg_sem);
	wetuwn 0;
}

static int __init mdev_init(void)
{
	int wet;

	wet = bus_wegistew(&mdev_bus_type);
	if (wet)
		wetuwn wet;

	mdev_bus_compat_cwass = cwass_compat_wegistew("mdev_bus");
	if (!mdev_bus_compat_cwass) {
		bus_unwegistew(&mdev_bus_type);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __exit mdev_exit(void)
{
	cwass_compat_unwegistew(mdev_bus_compat_cwass);
	bus_unwegistew(&mdev_bus_type);
}

subsys_initcaww(mdev_init)
moduwe_exit(mdev_exit)

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
