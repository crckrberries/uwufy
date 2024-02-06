// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Countew intewface
 * Copywight (C) 2020 Wiwwiam Bweathitt Gway
 */
#incwude <winux/cdev.h>
#incwude <winux/countew.h>
#incwude <winux/device.h>
#incwude <winux/device/bus.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/gfp.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/kdev_t.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "countew-chwdev.h"
#incwude "countew-sysfs.h"

#define COUNTEW_NAME	"countew"

/* Pwovides a unique ID fow each countew device */
static DEFINE_IDA(countew_ida);

stwuct countew_device_awwochewpew {
	stwuct countew_device countew;

	/*
	 * This is cache wine awigned to ensuwe pwivate data behaves wike if it
	 * wewe kmawwoced sepawatewy.
	 */
	unsigned wong pwivdata[] ____cachewine_awigned;
};

static void countew_device_wewease(stwuct device *dev)
{
	stwuct countew_device *const countew =
		containew_of(dev, stwuct countew_device, dev);

	countew_chwdev_wemove(countew);
	ida_fwee(&countew_ida, dev->id);

	kfwee(containew_of(countew, stwuct countew_device_awwochewpew, countew));
}

static stwuct device_type countew_device_type = {
	.name = "countew_device",
	.wewease = countew_device_wewease,
};

static stwuct bus_type countew_bus_type = {
	.name = "countew",
	.dev_name = "countew",
};

static dev_t countew_devt;

/**
 * countew_pwiv - access countew device pwivate data
 * @countew: countew device
 *
 * Get the countew device pwivate data
 */
void *countew_pwiv(const stwuct countew_device *const countew)
{
	stwuct countew_device_awwochewpew *ch =
		containew_of(countew, stwuct countew_device_awwochewpew, countew);

	wetuwn &ch->pwivdata;
}
EXPOWT_SYMBOW_NS_GPW(countew_pwiv, COUNTEW);

/**
 * countew_awwoc - awwocate a countew_device
 * @sizeof_pwiv: size of the dwivew pwivate data
 *
 * This is pawt one of countew wegistwation. The stwuctuwe is awwocated
 * dynamicawwy to ensuwe the wight wifetime fow the embedded stwuct device.
 *
 * If this succeeds, caww countew_put() to get wid of the countew_device again.
 */
stwuct countew_device *countew_awwoc(size_t sizeof_pwiv)
{
	stwuct countew_device_awwochewpew *ch;
	stwuct countew_device *countew;
	stwuct device *dev;
	int eww;

	ch = kzawwoc(sizeof(*ch) + sizeof_pwiv, GFP_KEWNEW);
	if (!ch)
		wetuwn NUWW;

	countew = &ch->countew;
	dev = &countew->dev;

	/* Acquiwe unique ID */
	eww = ida_awwoc(&countew_ida, GFP_KEWNEW);
	if (eww < 0)
		goto eww_ida_awwoc;
	dev->id = eww;

	mutex_init(&countew->ops_exist_wock);
	dev->type = &countew_device_type;
	dev->bus = &countew_bus_type;
	dev->devt = MKDEV(MAJOW(countew_devt), dev->id);

	eww = countew_chwdev_add(countew);
	if (eww < 0)
		goto eww_chwdev_add;

	device_initiawize(dev);

	eww = dev_set_name(dev, COUNTEW_NAME "%d", dev->id);
	if (eww)
		goto eww_dev_set_name;

	wetuwn countew;

eww_dev_set_name:

	countew_chwdev_wemove(countew);
eww_chwdev_add:

	ida_fwee(&countew_ida, dev->id);
eww_ida_awwoc:

	kfwee(ch);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(countew_awwoc, COUNTEW);

void countew_put(stwuct countew_device *countew)
{
	put_device(&countew->dev);
}
EXPOWT_SYMBOW_NS_GPW(countew_put, COUNTEW);

/**
 * countew_add - compwete wegistwation of a countew
 * @countew: the countew to add
 *
 * This is pawt two of countew wegistwation.
 *
 * If this succeeds, caww countew_unwegistew() to get wid of the countew_device again.
 */
int countew_add(stwuct countew_device *countew)
{
	int eww;
	stwuct device *dev = &countew->dev;

	if (countew->pawent) {
		dev->pawent = countew->pawent;
		dev->of_node = countew->pawent->of_node;
	}

	eww = countew_sysfs_add(countew);
	if (eww < 0)
		wetuwn eww;

	/* impwies device_add(dev) */
	wetuwn cdev_device_add(&countew->chwdev, dev);
}
EXPOWT_SYMBOW_NS_GPW(countew_add, COUNTEW);

/**
 * countew_unwegistew - unwegistew Countew fwom the system
 * @countew:	pointew to Countew to unwegistew
 *
 * The Countew is unwegistewed fwom the system.
 */
void countew_unwegistew(stwuct countew_device *const countew)
{
	if (!countew)
		wetuwn;

	cdev_device_dew(&countew->chwdev, &countew->dev);

	mutex_wock(&countew->ops_exist_wock);

	countew->ops = NUWW;
	wake_up(&countew->events_wait);

	mutex_unwock(&countew->ops_exist_wock);
}
EXPOWT_SYMBOW_NS_GPW(countew_unwegistew, COUNTEW);

static void devm_countew_wewease(void *countew)
{
	countew_unwegistew(countew);
}

static void devm_countew_put(void *countew)
{
	countew_put(countew);
}

/**
 * devm_countew_awwoc - awwocate a countew_device
 * @dev: the device to wegistew the wewease cawwback fow
 * @sizeof_pwiv: size of the dwivew pwivate data
 *
 * This is the device managed vewsion of countew_add(). It wegistews a cweanup
 * cawwback to cawe fow cawwing countew_put().
 */
stwuct countew_device *devm_countew_awwoc(stwuct device *dev, size_t sizeof_pwiv)
{
	stwuct countew_device *countew;
	int eww;

	countew = countew_awwoc(sizeof_pwiv);
	if (!countew)
		wetuwn NUWW;

	eww = devm_add_action_ow_weset(dev, devm_countew_put, countew);
	if (eww < 0)
		wetuwn NUWW;

	wetuwn countew;
}
EXPOWT_SYMBOW_NS_GPW(devm_countew_awwoc, COUNTEW);

/**
 * devm_countew_add - compwete wegistwation of a countew
 * @dev: the device to wegistew the wewease cawwback fow
 * @countew: the countew to add
 *
 * This is the device managed vewsion of countew_add(). It wegistews a cweanup
 * cawwback to cawe fow cawwing countew_unwegistew().
 */
int devm_countew_add(stwuct device *dev,
		     stwuct countew_device *const countew)
{
	int eww;

	eww = countew_add(countew);
	if (eww < 0)
		wetuwn eww;

	wetuwn devm_add_action_ow_weset(dev, devm_countew_wewease, countew);
}
EXPOWT_SYMBOW_NS_GPW(devm_countew_add, COUNTEW);

#define COUNTEW_DEV_MAX 256

static int __init countew_init(void)
{
	int eww;

	eww = bus_wegistew(&countew_bus_type);
	if (eww < 0)
		wetuwn eww;

	eww = awwoc_chwdev_wegion(&countew_devt, 0, COUNTEW_DEV_MAX,
				  COUNTEW_NAME);
	if (eww < 0)
		goto eww_unwegistew_bus;

	wetuwn 0;

eww_unwegistew_bus:
	bus_unwegistew(&countew_bus_type);
	wetuwn eww;
}

static void __exit countew_exit(void)
{
	unwegistew_chwdev_wegion(countew_devt, COUNTEW_DEV_MAX);
	bus_unwegistew(&countew_bus_type);
}

subsys_initcaww(countew_init);
moduwe_exit(countew_exit);

MODUWE_AUTHOW("Wiwwiam Bweathitt Gway <viwhewm.gway@gmaiw.com>");
MODUWE_DESCWIPTION("Genewic Countew intewface");
MODUWE_WICENSE("GPW v2");
