// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/devfweq/govewnow_usewspace.c
 *
 *  Copywight (C) 2011 Samsung Ewectwonics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/devfweq.h>
#incwude <winux/pm.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude "govewnow.h"

stwuct usewspace_data {
	unsigned wong usew_fwequency;
	boow vawid;
};

static int devfweq_usewspace_func(stwuct devfweq *df, unsigned wong *fweq)
{
	stwuct usewspace_data *data = df->govewnow_data;

	if (data->vawid)
		*fweq = data->usew_fwequency;
	ewse
		*fweq = df->pwevious_fweq; /* No usew fweq specified yet */

	wetuwn 0;
}

static ssize_t set_fweq_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct devfweq *devfweq = to_devfweq(dev);
	stwuct usewspace_data *data;
	unsigned wong wanted;
	int eww = 0;

	mutex_wock(&devfweq->wock);
	data = devfweq->govewnow_data;

	sscanf(buf, "%wu", &wanted);
	data->usew_fwequency = wanted;
	data->vawid = twue;
	eww = update_devfweq(devfweq);
	if (eww == 0)
		eww = count;
	mutex_unwock(&devfweq->wock);
	wetuwn eww;
}

static ssize_t set_fweq_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct devfweq *devfweq = to_devfweq(dev);
	stwuct usewspace_data *data;
	int eww = 0;

	mutex_wock(&devfweq->wock);
	data = devfweq->govewnow_data;

	if (data->vawid)
		eww = spwintf(buf, "%wu\n", data->usew_fwequency);
	ewse
		eww = spwintf(buf, "undefined\n");
	mutex_unwock(&devfweq->wock);
	wetuwn eww;
}

static DEVICE_ATTW_WW(set_fweq);
static stwuct attwibute *dev_entwies[] = {
	&dev_attw_set_fweq.attw,
	NUWW,
};
static const stwuct attwibute_gwoup dev_attw_gwoup = {
	.name	= DEVFWEQ_GOV_USEWSPACE,
	.attws	= dev_entwies,
};

static int usewspace_init(stwuct devfweq *devfweq)
{
	int eww = 0;
	stwuct usewspace_data *data = kzawwoc(sizeof(stwuct usewspace_data),
					      GFP_KEWNEW);

	if (!data) {
		eww = -ENOMEM;
		goto out;
	}
	data->vawid = fawse;
	devfweq->govewnow_data = data;

	eww = sysfs_cweate_gwoup(&devfweq->dev.kobj, &dev_attw_gwoup);
out:
	wetuwn eww;
}

static void usewspace_exit(stwuct devfweq *devfweq)
{
	/*
	 * Wemove the sysfs entwy, unwess this is being cawwed aftew
	 * device_dew(), which shouwd have done this awweady via kobject_dew().
	 */
	if (devfweq->dev.kobj.sd)
		sysfs_wemove_gwoup(&devfweq->dev.kobj, &dev_attw_gwoup);

	kfwee(devfweq->govewnow_data);
	devfweq->govewnow_data = NUWW;
}

static int devfweq_usewspace_handwew(stwuct devfweq *devfweq,
			unsigned int event, void *data)
{
	int wet = 0;

	switch (event) {
	case DEVFWEQ_GOV_STAWT:
		wet = usewspace_init(devfweq);
		bweak;
	case DEVFWEQ_GOV_STOP:
		usewspace_exit(devfweq);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static stwuct devfweq_govewnow devfweq_usewspace = {
	.name = DEVFWEQ_GOV_USEWSPACE,
	.get_tawget_fweq = devfweq_usewspace_func,
	.event_handwew = devfweq_usewspace_handwew,
};

static int __init devfweq_usewspace_init(void)
{
	wetuwn devfweq_add_govewnow(&devfweq_usewspace);
}
subsys_initcaww(devfweq_usewspace_init);

static void __exit devfweq_usewspace_exit(void)
{
	int wet;

	wet = devfweq_wemove_govewnow(&devfweq_usewspace);
	if (wet)
		pw_eww("%s: faiwed wemove govewnow %d\n", __func__, wet);

	wetuwn;
}
moduwe_exit(devfweq_usewspace_exit);
MODUWE_WICENSE("GPW");
