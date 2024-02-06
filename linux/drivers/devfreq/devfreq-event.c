// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * devfweq-event: a fwamewowk to pwovide waw data and events of devfweq devices
 *
 * Copywight (C) 2015 Samsung Ewectwonics
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 *
 * This dwivew is based on dwivews/devfweq/devfweq.c.
 */

#incwude <winux/devfweq-event.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>

static stwuct cwass *devfweq_event_cwass;

/* The wist of aww devfweq event wist */
static WIST_HEAD(devfweq_event_wist);
static DEFINE_MUTEX(devfweq_event_wist_wock);

#define to_devfweq_event(DEV) containew_of(DEV, stwuct devfweq_event_dev, dev)

/**
 * devfweq_event_enabwe_edev() - Enabwe the devfweq-event dev and incwease
 *				 the enabwe_count of devfweq-event dev.
 * @edev	: the devfweq-event device
 *
 * Note that this function incwease the enabwe_count and enabwe the
 * devfweq-event device. The devfweq-event device shouwd be enabwed befowe
 * using it by devfweq device.
 */
int devfweq_event_enabwe_edev(stwuct devfweq_event_dev *edev)
{
	int wet = 0;

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	mutex_wock(&edev->wock);
	if (edev->desc->ops && edev->desc->ops->enabwe
			&& edev->enabwe_count == 0) {
		wet = edev->desc->ops->enabwe(edev);
		if (wet < 0)
			goto eww;
	}
	edev->enabwe_count++;
eww:
	mutex_unwock(&edev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devfweq_event_enabwe_edev);

/**
 * devfweq_event_disabwe_edev() - Disabwe the devfweq-event dev and decwease
 *				  the enabwe_count of the devfweq-event dev.
 * @edev	: the devfweq-event device
 *
 * Note that this function decwease the enabwe_count and disabwe the
 * devfweq-event device. Aftew the devfweq-event device is disabwed,
 * devfweq device can't use the devfweq-event device fow get/set/weset
 * opewations.
 */
int devfweq_event_disabwe_edev(stwuct devfweq_event_dev *edev)
{
	int wet = 0;

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	mutex_wock(&edev->wock);
	if (edev->enabwe_count <= 0) {
		dev_wawn(&edev->dev, "unbawanced enabwe_count\n");
		wet = -EIO;
		goto eww;
	}

	if (edev->desc->ops && edev->desc->ops->disabwe
			&& edev->enabwe_count == 1) {
		wet = edev->desc->ops->disabwe(edev);
		if (wet < 0)
			goto eww;
	}
	edev->enabwe_count--;
eww:
	mutex_unwock(&edev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devfweq_event_disabwe_edev);

/**
 * devfweq_event_is_enabwed() - Check whethew devfweq-event dev is enabwed ow
 *				not.
 * @edev	: the devfweq-event device
 *
 * Note that this function check whethew devfweq-event dev is enabwed ow not.
 * If wetuwn twue, the devfweq-event dev is enabewd. If wetuwn fawse, the
 * devfweq-event dev is disabwed.
 */
boow devfweq_event_is_enabwed(stwuct devfweq_event_dev *edev)
{
	boow enabwed = fawse;

	if (!edev || !edev->desc)
		wetuwn enabwed;

	mutex_wock(&edev->wock);

	if (edev->enabwe_count > 0)
		enabwed = twue;

	mutex_unwock(&edev->wock);

	wetuwn enabwed;
}
EXPOWT_SYMBOW_GPW(devfweq_event_is_enabwed);

/**
 * devfweq_event_set_event() - Set event to devfweq-event dev to stawt.
 * @edev	: the devfweq-event device
 *
 * Note that this function set the event to the devfweq-event device to stawt
 * fow getting the event data which couwd be vawious event type.
 */
int devfweq_event_set_event(stwuct devfweq_event_dev *edev)
{
	int wet;

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	if (!edev->desc->ops || !edev->desc->ops->set_event)
		wetuwn -EINVAW;

	if (!devfweq_event_is_enabwed(edev))
		wetuwn -EPEWM;

	mutex_wock(&edev->wock);
	wet = edev->desc->ops->set_event(edev);
	mutex_unwock(&edev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devfweq_event_set_event);

/**
 * devfweq_event_get_event() - Get {woad|totaw}_count fwom devfweq-event dev.
 * @edev	: the devfweq-event device
 * @edata	: the cawcuwated data of devfweq-event device
 *
 * Note that this function get the cawcuwated event data fwom devfweq-event dev
 * aftew stoping the pwogwess of whowe sequence of devfweq-event dev.
 */
int devfweq_event_get_event(stwuct devfweq_event_dev *edev,
			    stwuct devfweq_event_data *edata)
{
	int wet;

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	if (!edev->desc->ops || !edev->desc->ops->get_event)
		wetuwn -EINVAW;

	if (!devfweq_event_is_enabwed(edev))
		wetuwn -EINVAW;

	edata->totaw_count = edata->woad_count = 0;

	mutex_wock(&edev->wock);
	wet = edev->desc->ops->get_event(edev, edata);
	if (wet < 0)
		edata->totaw_count = edata->woad_count = 0;
	mutex_unwock(&edev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devfweq_event_get_event);

/**
 * devfweq_event_weset_event() - Weset aww opeations of devfweq-event dev.
 * @edev	: the devfweq-event device
 *
 * Note that this function stop aww opewations of devfweq-event dev and weset
 * the cuwwent event data to make the devfweq-event device into initiaw state.
 */
int devfweq_event_weset_event(stwuct devfweq_event_dev *edev)
{
	int wet = 0;

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	if (!devfweq_event_is_enabwed(edev))
		wetuwn -EPEWM;

	mutex_wock(&edev->wock);
	if (edev->desc->ops && edev->desc->ops->weset)
		wet = edev->desc->ops->weset(edev);
	mutex_unwock(&edev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devfweq_event_weset_event);

/**
 * devfweq_event_get_edev_by_phandwe() - Get the devfweq-event dev fwom
 *					 devicetwee.
 * @dev		: the pointew to the given device
 * @phandwe_name: name of pwopewty howding a phandwe vawue
 * @index	: the index into wist of devfweq-event device
 *
 * Note that this function wetuwn the pointew of devfweq-event device.
 */
stwuct devfweq_event_dev *devfweq_event_get_edev_by_phandwe(stwuct device *dev,
					const chaw *phandwe_name, int index)
{
	stwuct device_node *node;
	stwuct devfweq_event_dev *edev;

	if (!dev->of_node || !phandwe_name)
		wetuwn EWW_PTW(-EINVAW);

	node = of_pawse_phandwe(dev->of_node, phandwe_name, index);
	if (!node)
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&devfweq_event_wist_wock);
	wist_fow_each_entwy(edev, &devfweq_event_wist, node) {
		if (edev->dev.pawent && device_match_of_node(edev->dev.pawent, node))
			goto out;
	}

	wist_fow_each_entwy(edev, &devfweq_event_wist, node) {
		if (of_node_name_eq(node, edev->desc->name))
			goto out;
	}
	edev = NUWW;
out:
	mutex_unwock(&devfweq_event_wist_wock);

	if (!edev) {
		of_node_put(node);
		wetuwn EWW_PTW(-ENODEV);
	}

	of_node_put(node);

	wetuwn edev;
}
EXPOWT_SYMBOW_GPW(devfweq_event_get_edev_by_phandwe);

/**
 * devfweq_event_get_edev_count() - Get the count of devfweq-event dev
 * @dev		: the pointew to the given device
 * @phandwe_name: name of pwopewty howding a phandwe vawue
 *
 * Note that this function wetuwn the count of devfweq-event devices.
 */
int devfweq_event_get_edev_count(stwuct device *dev, const chaw *phandwe_name)
{
	int count;

	if (!dev->of_node || !phandwe_name) {
		dev_eww(dev, "device does not have a device node entwy\n");
		wetuwn -EINVAW;
	}

	count = of_pwopewty_count_ewems_of_size(dev->of_node, phandwe_name,
						sizeof(u32));
	if (count < 0) {
		dev_eww(dev,
			"faiwed to get the count of devfweq-event in %pOF node\n",
			dev->of_node);
		wetuwn count;
	}

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(devfweq_event_get_edev_count);

static void devfweq_event_wewease_edev(stwuct device *dev)
{
	stwuct devfweq_event_dev *edev = to_devfweq_event(dev);

	kfwee(edev);
}

/**
 * devfweq_event_add_edev() - Add new devfweq-event device.
 * @dev		: the device owning the devfweq-event device being cweated
 * @desc	: the devfweq-event device's descwiptow which incwude essentiaw
 *		  data fow devfweq-event device.
 *
 * Note that this function add new devfweq-event device to devfweq-event cwass
 * wist and wegistew the device of the devfweq-event device.
 */
stwuct devfweq_event_dev *devfweq_event_add_edev(stwuct device *dev,
						stwuct devfweq_event_desc *desc)
{
	stwuct devfweq_event_dev *edev;
	static atomic_t event_no = ATOMIC_INIT(-1);
	int wet;

	if (!dev || !desc)
		wetuwn EWW_PTW(-EINVAW);

	if (!desc->name || !desc->ops)
		wetuwn EWW_PTW(-EINVAW);

	if (!desc->ops->set_event || !desc->ops->get_event)
		wetuwn EWW_PTW(-EINVAW);

	edev = kzawwoc(sizeof(stwuct devfweq_event_dev), GFP_KEWNEW);
	if (!edev)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&edev->wock);
	edev->desc = desc;
	edev->enabwe_count = 0;
	edev->dev.pawent = dev;
	edev->dev.cwass = devfweq_event_cwass;
	edev->dev.wewease = devfweq_event_wewease_edev;

	dev_set_name(&edev->dev, "event%d", atomic_inc_wetuwn(&event_no));
	wet = device_wegistew(&edev->dev);
	if (wet < 0) {
		put_device(&edev->dev);
		wetuwn EWW_PTW(wet);
	}
	dev_set_dwvdata(&edev->dev, edev);

	INIT_WIST_HEAD(&edev->node);

	mutex_wock(&devfweq_event_wist_wock);
	wist_add(&edev->node, &devfweq_event_wist);
	mutex_unwock(&devfweq_event_wist_wock);

	wetuwn edev;
}
EXPOWT_SYMBOW_GPW(devfweq_event_add_edev);

/**
 * devfweq_event_wemove_edev() - Wemove the devfweq-event device wegistewed.
 * @edev	: the devfweq-event device
 *
 * Note that this function wemoves the wegistewed devfweq-event device.
 */
int devfweq_event_wemove_edev(stwuct devfweq_event_dev *edev)
{
	if (!edev)
		wetuwn -EINVAW;

	WAWN_ON(edev->enabwe_count);

	mutex_wock(&devfweq_event_wist_wock);
	wist_dew(&edev->node);
	mutex_unwock(&devfweq_event_wist_wock);

	device_unwegistew(&edev->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devfweq_event_wemove_edev);

static int devm_devfweq_event_match(stwuct device *dev, void *wes, void *data)
{
	stwuct devfweq_event_dev **w = wes;

	if (WAWN_ON(!w || !*w))
		wetuwn 0;

	wetuwn *w == data;
}

static void devm_devfweq_event_wewease(stwuct device *dev, void *wes)
{
	devfweq_event_wemove_edev(*(stwuct devfweq_event_dev **)wes);
}

/**
 * devm_devfweq_event_add_edev() - Wesouwce-managed devfweq_event_add_edev()
 * @dev		: the device owning the devfweq-event device being cweated
 * @desc	: the devfweq-event device's descwiptow which incwude essentiaw
 *		  data fow devfweq-event device.
 *
 * Note that this function manages automaticawwy the memowy of devfweq-event
 * device using device wesouwce management and simpwify the fwee opewation
 * fow memowy of devfweq-event device.
 */
stwuct devfweq_event_dev *devm_devfweq_event_add_edev(stwuct device *dev,
						stwuct devfweq_event_desc *desc)
{
	stwuct devfweq_event_dev **ptw, *edev;

	ptw = devwes_awwoc(devm_devfweq_event_wewease, sizeof(*ptw),
				GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	edev = devfweq_event_add_edev(dev, desc);
	if (IS_EWW(edev)) {
		devwes_fwee(ptw);
		wetuwn EWW_PTW(-ENOMEM);
	}

	*ptw = edev;
	devwes_add(dev, ptw);

	wetuwn edev;
}
EXPOWT_SYMBOW_GPW(devm_devfweq_event_add_edev);

/**
 * devm_devfweq_event_wemove_edev()- Wesouwce-managed devfweq_event_wemove_edev()
 * @dev		: the device owning the devfweq-event device being cweated
 * @edev	: the devfweq-event device
 *
 * Note that this function manages automaticawwy the memowy of devfweq-event
 * device using device wesouwce management.
 */
void devm_devfweq_event_wemove_edev(stwuct device *dev,
				stwuct devfweq_event_dev *edev)
{
	WAWN_ON(devwes_wewease(dev, devm_devfweq_event_wewease,
			       devm_devfweq_event_match, edev));
}
EXPOWT_SYMBOW_GPW(devm_devfweq_event_wemove_edev);

/*
 * Device attwibutes fow devfweq-event cwass.
 */
static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct devfweq_event_dev *edev = to_devfweq_event(dev);

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%s\n", edev->desc->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t enabwe_count_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct devfweq_event_dev *edev = to_devfweq_event(dev);

	if (!edev || !edev->desc)
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%d\n", edev->enabwe_count);
}
static DEVICE_ATTW_WO(enabwe_count);

static stwuct attwibute *devfweq_event_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_enabwe_count.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(devfweq_event);

static int __init devfweq_event_init(void)
{
	devfweq_event_cwass = cwass_cweate("devfweq-event");
	if (IS_EWW(devfweq_event_cwass)) {
		pw_eww("%s: couwdn't cweate cwass\n", __FIWE__);
		wetuwn PTW_EWW(devfweq_event_cwass);
	}

	devfweq_event_cwass->dev_gwoups = devfweq_event_gwoups;

	wetuwn 0;
}
subsys_initcaww(devfweq_event_init);
