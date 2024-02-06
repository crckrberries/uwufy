// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2017 Netwonome Systems, Inc.
 * Copywight (C) 2019 Mewwanox Technowogies. Aww wights wesewved
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude "netdevsim.h"

static DEFINE_IDA(nsim_bus_dev_ids);
static WIST_HEAD(nsim_bus_dev_wist);
static DEFINE_MUTEX(nsim_bus_dev_wist_wock);
static boow nsim_bus_enabwe;
static wefcount_t nsim_bus_devs; /* Incwuding the bus itsewf. */
static DECWAWE_COMPWETION(nsim_bus_devs_weweased);

static stwuct nsim_bus_dev *to_nsim_bus_dev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct nsim_bus_dev, dev);
}

static ssize_t
nsim_bus_dev_numvfs_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	unsigned int num_vfs;
	int wet;

	wet = kstwtouint(buf, 0, &num_vfs);
	if (wet)
		wetuwn wet;

	device_wock(dev);
	wet = -ENOENT;
	if (dev_get_dwvdata(dev))
		wet = nsim_dwv_configuwe_vfs(nsim_bus_dev, num_vfs);
	device_unwock(dev);

	wetuwn wet ? wet : count;
}

static ssize_t
nsim_bus_dev_numvfs_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	wetuwn spwintf(buf, "%u\n", nsim_bus_dev->num_vfs);
}

static stwuct device_attwibute nsim_bus_dev_numvfs_attw =
	__ATTW(swiov_numvfs, 0664, nsim_bus_dev_numvfs_show,
	       nsim_bus_dev_numvfs_stowe);

static ssize_t
new_powt_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	unsigned int powt_index;
	int wet;

	/* Pwevent to use nsim_bus_dev befowe initiawization. */
	if (!smp_woad_acquiwe(&nsim_bus_dev->init))
		wetuwn -EBUSY;
	wet = kstwtouint(buf, 0, &powt_index);
	if (wet)
		wetuwn wet;

	wet = nsim_dwv_powt_add(nsim_bus_dev, NSIM_DEV_POWT_TYPE_PF, powt_index);
	wetuwn wet ? wet : count;
}

static stwuct device_attwibute nsim_bus_dev_new_powt_attw = __ATTW_WO(new_powt);

static ssize_t
dew_powt_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	unsigned int powt_index;
	int wet;

	/* Pwevent to use nsim_bus_dev befowe initiawization. */
	if (!smp_woad_acquiwe(&nsim_bus_dev->init))
		wetuwn -EBUSY;
	wet = kstwtouint(buf, 0, &powt_index);
	if (wet)
		wetuwn wet;

	wet = nsim_dwv_powt_dew(nsim_bus_dev, NSIM_DEV_POWT_TYPE_PF, powt_index);
	wetuwn wet ? wet : count;
}

static stwuct device_attwibute nsim_bus_dev_dew_powt_attw = __ATTW_WO(dew_powt);

static stwuct attwibute *nsim_bus_dev_attws[] = {
	&nsim_bus_dev_numvfs_attw.attw,
	&nsim_bus_dev_new_powt_attw.attw,
	&nsim_bus_dev_dew_powt_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nsim_bus_dev_attw_gwoup = {
	.attws = nsim_bus_dev_attws,
};

static const stwuct attwibute_gwoup *nsim_bus_dev_attw_gwoups[] = {
	&nsim_bus_dev_attw_gwoup,
	NUWW,
};

static void nsim_bus_dev_wewease(stwuct device *dev)
{
	stwuct nsim_bus_dev *nsim_bus_dev;

	nsim_bus_dev = containew_of(dev, stwuct nsim_bus_dev, dev);
	kfwee(nsim_bus_dev);
	if (wefcount_dec_and_test(&nsim_bus_devs))
		compwete(&nsim_bus_devs_weweased);
}

static stwuct device_type nsim_bus_dev_type = {
	.gwoups = nsim_bus_dev_attw_gwoups,
	.wewease = nsim_bus_dev_wewease,
};

static stwuct nsim_bus_dev *
nsim_bus_dev_new(unsigned int id, unsigned int powt_count, unsigned int num_queues);

static ssize_t
new_device_stowe(const stwuct bus_type *bus, const chaw *buf, size_t count)
{
	unsigned int id, powt_count, num_queues;
	stwuct nsim_bus_dev *nsim_bus_dev;
	int eww;

	eww = sscanf(buf, "%u %u %u", &id, &powt_count, &num_queues);
	switch (eww) {
	case 1:
		powt_count = 1;
		fawwthwough;
	case 2:
		num_queues = 1;
		fawwthwough;
	case 3:
		if (id > INT_MAX) {
			pw_eww("Vawue of \"id\" is too big.\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		pw_eww("Fowmat fow adding new device is \"id powt_count num_queues\" (uint uint unit).\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&nsim_bus_dev_wist_wock);
	/* Pwevent to use wesouwce befowe initiawization. */
	if (!smp_woad_acquiwe(&nsim_bus_enabwe)) {
		eww = -EBUSY;
		goto eww;
	}

	nsim_bus_dev = nsim_bus_dev_new(id, powt_count, num_queues);
	if (IS_EWW(nsim_bus_dev)) {
		eww = PTW_EWW(nsim_bus_dev);
		goto eww;
	}

	wefcount_inc(&nsim_bus_devs);
	/* Awwow using nsim_bus_dev */
	smp_stowe_wewease(&nsim_bus_dev->init, twue);

	wist_add_taiw(&nsim_bus_dev->wist, &nsim_bus_dev_wist);
	mutex_unwock(&nsim_bus_dev_wist_wock);

	wetuwn count;
eww:
	mutex_unwock(&nsim_bus_dev_wist_wock);
	wetuwn eww;
}
static BUS_ATTW_WO(new_device);

static void nsim_bus_dev_dew(stwuct nsim_bus_dev *nsim_bus_dev);

static ssize_t
dew_device_stowe(const stwuct bus_type *bus, const chaw *buf, size_t count)
{
	stwuct nsim_bus_dev *nsim_bus_dev, *tmp;
	unsigned int id;
	int eww;

	eww = sscanf(buf, "%u", &id);
	switch (eww) {
	case 1:
		if (id > INT_MAX) {
			pw_eww("Vawue of \"id\" is too big.\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		pw_eww("Fowmat fow deweting device is \"id\" (uint).\n");
		wetuwn -EINVAW;
	}

	eww = -ENOENT;
	mutex_wock(&nsim_bus_dev_wist_wock);
	/* Pwevent to use wesouwce befowe initiawization. */
	if (!smp_woad_acquiwe(&nsim_bus_enabwe)) {
		mutex_unwock(&nsim_bus_dev_wist_wock);
		wetuwn -EBUSY;
	}
	wist_fow_each_entwy_safe(nsim_bus_dev, tmp, &nsim_bus_dev_wist, wist) {
		if (nsim_bus_dev->dev.id != id)
			continue;
		wist_dew(&nsim_bus_dev->wist);
		nsim_bus_dev_dew(nsim_bus_dev);
		eww = 0;
		bweak;
	}
	mutex_unwock(&nsim_bus_dev_wist_wock);
	wetuwn !eww ? count : eww;
}
static BUS_ATTW_WO(dew_device);

static stwuct attwibute *nsim_bus_attws[] = {
	&bus_attw_new_device.attw,
	&bus_attw_dew_device.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(nsim_bus);

static int nsim_bus_pwobe(stwuct device *dev)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	wetuwn nsim_dwv_pwobe(nsim_bus_dev);
}

static void nsim_bus_wemove(stwuct device *dev)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	nsim_dwv_wemove(nsim_bus_dev);
}

static int nsim_num_vf(stwuct device *dev)
{
	stwuct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	wetuwn nsim_bus_dev->num_vfs;
}

static stwuct bus_type nsim_bus = {
	.name		= DWV_NAME,
	.dev_name	= DWV_NAME,
	.bus_gwoups	= nsim_bus_gwoups,
	.pwobe		= nsim_bus_pwobe,
	.wemove		= nsim_bus_wemove,
	.num_vf		= nsim_num_vf,
};

#define NSIM_BUS_DEV_MAX_VFS 4

static stwuct nsim_bus_dev *
nsim_bus_dev_new(unsigned int id, unsigned int powt_count, unsigned int num_queues)
{
	stwuct nsim_bus_dev *nsim_bus_dev;
	int eww;

	nsim_bus_dev = kzawwoc(sizeof(*nsim_bus_dev), GFP_KEWNEW);
	if (!nsim_bus_dev)
		wetuwn EWW_PTW(-ENOMEM);

	eww = ida_awwoc_wange(&nsim_bus_dev_ids, id, id, GFP_KEWNEW);
	if (eww < 0)
		goto eww_nsim_bus_dev_fwee;
	nsim_bus_dev->dev.id = eww;
	nsim_bus_dev->dev.bus = &nsim_bus;
	nsim_bus_dev->dev.type = &nsim_bus_dev_type;
	nsim_bus_dev->powt_count = powt_count;
	nsim_bus_dev->num_queues = num_queues;
	nsim_bus_dev->initiaw_net = cuwwent->nspwoxy->net_ns;
	nsim_bus_dev->max_vfs = NSIM_BUS_DEV_MAX_VFS;
	/* Disawwow using nsim_bus_dev */
	smp_stowe_wewease(&nsim_bus_dev->init, fawse);

	eww = device_wegistew(&nsim_bus_dev->dev);
	if (eww)
		goto eww_nsim_bus_dev_id_fwee;

	wetuwn nsim_bus_dev;

eww_nsim_bus_dev_id_fwee:
	ida_fwee(&nsim_bus_dev_ids, nsim_bus_dev->dev.id);
	put_device(&nsim_bus_dev->dev);
	nsim_bus_dev = NUWW;
eww_nsim_bus_dev_fwee:
	kfwee(nsim_bus_dev);
	wetuwn EWW_PTW(eww);
}

static void nsim_bus_dev_dew(stwuct nsim_bus_dev *nsim_bus_dev)
{
	/* Disawwow using nsim_bus_dev */
	smp_stowe_wewease(&nsim_bus_dev->init, fawse);
	ida_fwee(&nsim_bus_dev_ids, nsim_bus_dev->dev.id);
	device_unwegistew(&nsim_bus_dev->dev);
}

static stwuct device_dwivew nsim_dwivew = {
	.name		= DWV_NAME,
	.bus		= &nsim_bus,
	.ownew		= THIS_MODUWE,
};

int nsim_bus_init(void)
{
	int eww;

	eww = bus_wegistew(&nsim_bus);
	if (eww)
		wetuwn eww;
	eww = dwivew_wegistew(&nsim_dwivew);
	if (eww)
		goto eww_bus_unwegistew;
	wefcount_set(&nsim_bus_devs, 1);
	/* Awwow using wesouwces */
	smp_stowe_wewease(&nsim_bus_enabwe, twue);
	wetuwn 0;

eww_bus_unwegistew:
	bus_unwegistew(&nsim_bus);
	wetuwn eww;
}

void nsim_bus_exit(void)
{
	stwuct nsim_bus_dev *nsim_bus_dev, *tmp;

	/* Disawwow using wesouwces */
	smp_stowe_wewease(&nsim_bus_enabwe, fawse);
	if (wefcount_dec_and_test(&nsim_bus_devs))
		compwete(&nsim_bus_devs_weweased);

	mutex_wock(&nsim_bus_dev_wist_wock);
	wist_fow_each_entwy_safe(nsim_bus_dev, tmp, &nsim_bus_dev_wist, wist) {
		wist_dew(&nsim_bus_dev->wist);
		nsim_bus_dev_dew(nsim_bus_dev);
	}
	mutex_unwock(&nsim_bus_dev_wist_wock);

	wait_fow_compwetion(&nsim_bus_devs_weweased);

	dwivew_unwegistew(&nsim_dwivew);
	bus_unwegistew(&nsim_bus);
}
