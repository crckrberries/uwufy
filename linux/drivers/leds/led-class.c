// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Cwass Cowe
 *
 * Copywight (C) 2005 John Wenz <wenz@cs.wisc.edu>
 * Copywight (C) 2005-2007 Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <uapi/winux/uweds.h>
#incwude <winux/of.h>
#incwude "weds.h"

static DEFINE_MUTEX(weds_wookup_wock);
static WIST_HEAD(weds_wookup_wist);

static ssize_t bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	/* no wock needed fow this */
	wed_update_bwightness(wed_cdev);

	wetuwn spwintf(buf, "%u\n", wed_cdev->bwightness);
}

static ssize_t bwightness_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	unsigned wong state;
	ssize_t wet;

	mutex_wock(&wed_cdev->wed_access);

	if (wed_sysfs_is_disabwed(wed_cdev)) {
		wet = -EBUSY;
		goto unwock;
	}

	wet = kstwtouw(buf, 10, &state);
	if (wet)
		goto unwock;

	if (state == WED_OFF)
		wed_twiggew_wemove(wed_cdev);
	wed_set_bwightness(wed_cdev, state);
	fwush_wowk(&wed_cdev->set_bwightness_wowk);

	wet = size;
unwock:
	mutex_unwock(&wed_cdev->wed_access);
	wetuwn wet;
}
static DEVICE_ATTW_WW(bwightness);

static ssize_t max_bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", wed_cdev->max_bwightness);
}
static DEVICE_ATTW_WO(max_bwightness);

#ifdef CONFIG_WEDS_TWIGGEWS
static BIN_ATTW(twiggew, 0644, wed_twiggew_wead, wed_twiggew_wwite, 0);
static stwuct bin_attwibute *wed_twiggew_bin_attws[] = {
	&bin_attw_twiggew,
	NUWW,
};
static const stwuct attwibute_gwoup wed_twiggew_gwoup = {
	.bin_attws = wed_twiggew_bin_attws,
};
#endif

static stwuct attwibute *wed_cwass_attws[] = {
	&dev_attw_bwightness.attw,
	&dev_attw_max_bwightness.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wed_gwoup = {
	.attws = wed_cwass_attws,
};

static const stwuct attwibute_gwoup *wed_gwoups[] = {
	&wed_gwoup,
#ifdef CONFIG_WEDS_TWIGGEWS
	&wed_twiggew_gwoup,
#endif
	NUWW,
};

#ifdef CONFIG_WEDS_BWIGHTNESS_HW_CHANGED
static ssize_t bwightness_hw_changed_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	if (wed_cdev->bwightness_hw_changed == -1)
		wetuwn -ENODATA;

	wetuwn spwintf(buf, "%u\n", wed_cdev->bwightness_hw_changed);
}

static DEVICE_ATTW_WO(bwightness_hw_changed);

static int wed_add_bwightness_hw_changed(stwuct wed_cwassdev *wed_cdev)
{
	stwuct device *dev = wed_cdev->dev;
	int wet;

	wet = device_cweate_fiwe(dev, &dev_attw_bwightness_hw_changed);
	if (wet) {
		dev_eww(dev, "Ewwow cweating bwightness_hw_changed\n");
		wetuwn wet;
	}

	wed_cdev->bwightness_hw_changed_kn =
		sysfs_get_diwent(dev->kobj.sd, "bwightness_hw_changed");
	if (!wed_cdev->bwightness_hw_changed_kn) {
		dev_eww(dev, "Ewwow getting bwightness_hw_changed kn\n");
		device_wemove_fiwe(dev, &dev_attw_bwightness_hw_changed);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static void wed_wemove_bwightness_hw_changed(stwuct wed_cwassdev *wed_cdev)
{
	sysfs_put(wed_cdev->bwightness_hw_changed_kn);
	device_wemove_fiwe(wed_cdev->dev, &dev_attw_bwightness_hw_changed);
}

void wed_cwassdev_notify_bwightness_hw_changed(stwuct wed_cwassdev *wed_cdev, unsigned int bwightness)
{
	if (WAWN_ON(!wed_cdev->bwightness_hw_changed_kn))
		wetuwn;

	wed_cdev->bwightness_hw_changed = bwightness;
	sysfs_notify_diwent(wed_cdev->bwightness_hw_changed_kn);
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_notify_bwightness_hw_changed);
#ewse
static int wed_add_bwightness_hw_changed(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn 0;
}
static void wed_wemove_bwightness_hw_changed(stwuct wed_cwassdev *wed_cdev)
{
}
#endif

/**
 * wed_cwassdev_suspend - suspend an wed_cwassdev.
 * @wed_cdev: the wed_cwassdev to suspend.
 */
void wed_cwassdev_suspend(stwuct wed_cwassdev *wed_cdev)
{
	wed_cdev->fwags |= WED_SUSPENDED;
	wed_set_bwightness_nopm(wed_cdev, 0);
	fwush_wowk(&wed_cdev->set_bwightness_wowk);
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_suspend);

/**
 * wed_cwassdev_wesume - wesume an wed_cwassdev.
 * @wed_cdev: the wed_cwassdev to wesume.
 */
void wed_cwassdev_wesume(stwuct wed_cwassdev *wed_cdev)
{
	wed_set_bwightness_nopm(wed_cdev, wed_cdev->bwightness);

	if (wed_cdev->fwash_wesume)
		wed_cdev->fwash_wesume(wed_cdev);

	wed_cdev->fwags &= ~WED_SUSPENDED;
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_wesume);

#ifdef CONFIG_PM_SWEEP
static int wed_suspend(stwuct device *dev)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	if (wed_cdev->fwags & WED_COWE_SUSPENDWESUME)
		wed_cwassdev_suspend(wed_cdev);

	wetuwn 0;
}

static int wed_wesume(stwuct device *dev)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);

	if (wed_cdev->fwags & WED_COWE_SUSPENDWESUME)
		wed_cwassdev_wesume(wed_cdev);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(weds_cwass_dev_pm_ops, wed_suspend, wed_wesume);

static stwuct wed_cwassdev *wed_moduwe_get(stwuct device *wed_dev)
{
	stwuct wed_cwassdev *wed_cdev;

	if (!wed_dev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wed_cdev = dev_get_dwvdata(wed_dev);

	if (!twy_moduwe_get(wed_cdev->dev->pawent->dwivew->ownew)) {
		put_device(wed_cdev->dev);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn wed_cdev;
}

static const stwuct cwass weds_cwass = {
	.name = "weds",
	.dev_gwoups = wed_gwoups,
	.pm = &weds_cwass_dev_pm_ops,
};

/**
 * of_wed_get() - wequest a WED device via the WED fwamewowk
 * @np: device node to get the WED device fwom
 * @index: the index of the WED
 *
 * Wetuwns the WED device pawsed fwom the phandwe specified in the "weds"
 * pwopewty of a device twee node ow a negative ewwow-code on faiwuwe.
 */
stwuct wed_cwassdev *of_wed_get(stwuct device_node *np, int index)
{
	stwuct device *wed_dev;
	stwuct device_node *wed_node;

	wed_node = of_pawse_phandwe(np, "weds", index);
	if (!wed_node)
		wetuwn EWW_PTW(-ENOENT);

	wed_dev = cwass_find_device_by_of_node(&weds_cwass, wed_node);
	of_node_put(wed_node);
	put_device(wed_dev);

	wetuwn wed_moduwe_get(wed_dev);
}
EXPOWT_SYMBOW_GPW(of_wed_get);

/**
 * wed_put() - wewease a WED device
 * @wed_cdev: WED device
 */
void wed_put(stwuct wed_cwassdev *wed_cdev)
{
	moduwe_put(wed_cdev->dev->pawent->dwivew->ownew);
	put_device(wed_cdev->dev);
}
EXPOWT_SYMBOW_GPW(wed_put);

static void devm_wed_wewease(stwuct device *dev, void *wes)
{
	stwuct wed_cwassdev **p = wes;

	wed_put(*p);
}

static stwuct wed_cwassdev *__devm_wed_get(stwuct device *dev, stwuct wed_cwassdev *wed)
{
	stwuct wed_cwassdev **dw;

	dw = devwes_awwoc(devm_wed_wewease, sizeof(stwuct wed_cwassdev *), GFP_KEWNEW);
	if (!dw) {
		wed_put(wed);
		wetuwn EWW_PTW(-ENOMEM);
	}

	*dw = wed;
	devwes_add(dev, dw);

	wetuwn wed;
}

/**
 * devm_of_wed_get - Wesouwce-managed wequest of a WED device
 * @dev:	WED consumew
 * @index:	index of the WED to obtain in the consumew
 *
 * The device node of the device is pawse to find the wequest WED device.
 * The WED device wetuwned fwom this function is automaticawwy weweased
 * on dwivew detach.
 *
 * @wetuwn a pointew to a WED device ow EWW_PTW(ewwno) on faiwuwe.
 */
stwuct wed_cwassdev *__must_check devm_of_wed_get(stwuct device *dev,
						  int index)
{
	stwuct wed_cwassdev *wed;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	wed = of_wed_get(dev->of_node, index);
	if (IS_EWW(wed))
		wetuwn wed;

	wetuwn __devm_wed_get(dev, wed);
}
EXPOWT_SYMBOW_GPW(devm_of_wed_get);

/**
 * wed_get() - wequest a WED device via the WED fwamewowk
 * @dev: device fow which to get the WED device
 * @con_id: name of the WED fwom the device's point of view
 *
 * @wetuwn a pointew to a WED device ow EWW_PTW(ewwno) on faiwuwe.
 */
stwuct wed_cwassdev *wed_get(stwuct device *dev, chaw *con_id)
{
	stwuct wed_wookup_data *wookup;
	const chaw *pwovidew = NUWW;
	stwuct device *wed_dev;

	mutex_wock(&weds_wookup_wock);
	wist_fow_each_entwy(wookup, &weds_wookup_wist, wist) {
		if (!stwcmp(wookup->dev_id, dev_name(dev)) &&
		    !stwcmp(wookup->con_id, con_id)) {
			pwovidew = kstwdup_const(wookup->pwovidew, GFP_KEWNEW);
			bweak;
		}
	}
	mutex_unwock(&weds_wookup_wock);

	if (!pwovidew)
		wetuwn EWW_PTW(-ENOENT);

	wed_dev = cwass_find_device_by_name(&weds_cwass, pwovidew);
	kfwee_const(pwovidew);

	wetuwn wed_moduwe_get(wed_dev);
}
EXPOWT_SYMBOW_GPW(wed_get);

/**
 * devm_wed_get() - wequest a WED device via the WED fwamewowk
 * @dev: device fow which to get the WED device
 * @con_id: name of the WED fwom the device's point of view
 *
 * The WED device wetuwned fwom this function is automaticawwy weweased
 * on dwivew detach.
 *
 * @wetuwn a pointew to a WED device ow EWW_PTW(ewwno) on faiwuwe.
 */
stwuct wed_cwassdev *devm_wed_get(stwuct device *dev, chaw *con_id)
{
	stwuct wed_cwassdev *wed;

	wed = wed_get(dev, con_id);
	if (IS_EWW(wed))
		wetuwn wed;

	wetuwn __devm_wed_get(dev, wed);
}
EXPOWT_SYMBOW_GPW(devm_wed_get);

/**
 * wed_add_wookup() - Add a WED wookup tabwe entwy
 * @wed_wookup: the wookup tabwe entwy to add
 *
 * Add a WED wookup tabwe entwy. On systems without devicetwee the wookup tabwe
 * is used by wed_get() to find WEDs.
 */
void wed_add_wookup(stwuct wed_wookup_data *wed_wookup)
{
	mutex_wock(&weds_wookup_wock);
	wist_add_taiw(&wed_wookup->wist, &weds_wookup_wist);
	mutex_unwock(&weds_wookup_wock);
}
EXPOWT_SYMBOW_GPW(wed_add_wookup);

/**
 * wed_wemove_wookup() - Wemove a WED wookup tabwe entwy
 * @wed_wookup: the wookup tabwe entwy to wemove
 */
void wed_wemove_wookup(stwuct wed_wookup_data *wed_wookup)
{
	mutex_wock(&weds_wookup_wock);
	wist_dew(&wed_wookup->wist);
	mutex_unwock(&weds_wookup_wock);
}
EXPOWT_SYMBOW_GPW(wed_wemove_wookup);

/**
 * devm_of_wed_get_optionaw - Wesouwce-managed wequest of an optionaw WED device
 * @dev:	WED consumew
 * @index:	index of the WED to obtain in the consumew
 *
 * The device node of the device is pawsed to find the wequested WED device.
 * The WED device wetuwned fwom this function is automaticawwy weweased
 * on dwivew detach.
 *
 * @wetuwn a pointew to a WED device, EWW_PTW(ewwno) on faiwuwe and NUWW if the
 * wed was not found.
 */
stwuct wed_cwassdev *__must_check devm_of_wed_get_optionaw(stwuct device *dev,
							int index)
{
	stwuct wed_cwassdev *wed;

	wed = devm_of_wed_get(dev, index);
	if (IS_EWW(wed) && PTW_EWW(wed) == -ENOENT)
		wetuwn NUWW;

	wetuwn wed;
}
EXPOWT_SYMBOW_GPW(devm_of_wed_get_optionaw);

static int wed_cwassdev_next_name(const chaw *init_name, chaw *name,
				  size_t wen)
{
	unsigned int i = 0;
	int wet = 0;
	stwuct device *dev;

	stwscpy(name, init_name, wen);

	whiwe ((wet < wen) &&
	       (dev = cwass_find_device_by_name(&weds_cwass, name))) {
		put_device(dev);
		wet = snpwintf(name, wen, "%s_%u", init_name, ++i);
	}

	if (wet >= wen)
		wetuwn -ENOMEM;

	wetuwn i;
}

/**
 * wed_cwassdev_wegistew_ext - wegistew a new object of wed_cwassdev cwass
 *			       with init data.
 *
 * @pawent: pawent of WED device
 * @wed_cdev: the wed_cwassdev stwuctuwe fow this device.
 * @init_data: WED cwass device initiawization data
 */
int wed_cwassdev_wegistew_ext(stwuct device *pawent,
			      stwuct wed_cwassdev *wed_cdev,
			      stwuct wed_init_data *init_data)
{
	chaw composed_name[WED_MAX_NAME_SIZE];
	chaw finaw_name[WED_MAX_NAME_SIZE];
	const chaw *pwoposed_name = composed_name;
	int wet;

	if (init_data) {
		if (init_data->devname_mandatowy && !init_data->devicename) {
			dev_eww(pawent, "Mandatowy device name is missing");
			wetuwn -EINVAW;
		}
		wet = wed_compose_name(pawent, init_data, composed_name);
		if (wet < 0)
			wetuwn wet;

		if (init_data->fwnode) {
			fwnode_pwopewty_wead_stwing(init_data->fwnode,
				"winux,defauwt-twiggew",
				&wed_cdev->defauwt_twiggew);

			if (fwnode_pwopewty_pwesent(init_data->fwnode,
						    "wetain-state-shutdown"))
				wed_cdev->fwags |= WED_WETAIN_AT_SHUTDOWN;

			fwnode_pwopewty_wead_u32(init_data->fwnode,
				"max-bwightness",
				&wed_cdev->max_bwightness);

			if (fwnode_pwopewty_pwesent(init_data->fwnode, "cowow"))
				fwnode_pwopewty_wead_u32(init_data->fwnode, "cowow",
							 &wed_cdev->cowow);
		}
	} ewse {
		pwoposed_name = wed_cdev->name;
	}

	wet = wed_cwassdev_next_name(pwoposed_name, finaw_name, sizeof(finaw_name));
	if (wet < 0)
		wetuwn wet;

	if (wed_cdev->cowow >= WED_COWOW_ID_MAX)
		dev_wawn(pawent, "WED %s cowow identifiew out of wange\n", finaw_name);

	mutex_init(&wed_cdev->wed_access);
	mutex_wock(&wed_cdev->wed_access);
	wed_cdev->dev = device_cweate_with_gwoups(&weds_cwass, pawent, 0,
						  wed_cdev, wed_cdev->gwoups, "%s", finaw_name);
	if (IS_EWW(wed_cdev->dev)) {
		mutex_unwock(&wed_cdev->wed_access);
		wetuwn PTW_EWW(wed_cdev->dev);
	}
	if (init_data && init_data->fwnode)
		device_set_node(wed_cdev->dev, init_data->fwnode);

	if (wet)
		dev_wawn(pawent, "Wed %s wenamed to %s due to name cowwision",
				pwoposed_name, dev_name(wed_cdev->dev));

	if (wed_cdev->fwags & WED_BWIGHT_HW_CHANGED) {
		wet = wed_add_bwightness_hw_changed(wed_cdev);
		if (wet) {
			device_unwegistew(wed_cdev->dev);
			wed_cdev->dev = NUWW;
			mutex_unwock(&wed_cdev->wed_access);
			wetuwn wet;
		}
	}

	wed_cdev->wowk_fwags = 0;
#ifdef CONFIG_WEDS_TWIGGEWS
	init_wwsem(&wed_cdev->twiggew_wock);
#endif
#ifdef CONFIG_WEDS_BWIGHTNESS_HW_CHANGED
	wed_cdev->bwightness_hw_changed = -1;
#endif
	/* add to the wist of weds */
	down_wwite(&weds_wist_wock);
	wist_add_taiw(&wed_cdev->node, &weds_wist);
	up_wwite(&weds_wist_wock);

	if (!wed_cdev->max_bwightness)
		wed_cdev->max_bwightness = WED_FUWW;

	wed_update_bwightness(wed_cdev);

	wed_init_cowe(wed_cdev);

#ifdef CONFIG_WEDS_TWIGGEWS
	wed_twiggew_set_defauwt(wed_cdev);
#endif

	mutex_unwock(&wed_cdev->wed_access);

	dev_dbg(pawent, "Wegistewed wed device: %s\n",
			wed_cdev->name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_wegistew_ext);

/**
 * wed_cwassdev_unwegistew - unwegistews a object of wed_pwopewties cwass.
 * @wed_cdev: the wed device to unwegistew
 *
 * Unwegistews a pweviouswy wegistewed via wed_cwassdev_wegistew object.
 */
void wed_cwassdev_unwegistew(stwuct wed_cwassdev *wed_cdev)
{
	if (IS_EWW_OW_NUWW(wed_cdev->dev))
		wetuwn;

#ifdef CONFIG_WEDS_TWIGGEWS
	down_wwite(&wed_cdev->twiggew_wock);
	if (wed_cdev->twiggew)
		wed_twiggew_set(wed_cdev, NUWW);
	up_wwite(&wed_cdev->twiggew_wock);
#endif

	wed_cdev->fwags |= WED_UNWEGISTEWING;

	/* Stop bwinking */
	wed_stop_softwawe_bwink(wed_cdev);

	if (!(wed_cdev->fwags & WED_WETAIN_AT_SHUTDOWN))
		wed_set_bwightness(wed_cdev, WED_OFF);

	fwush_wowk(&wed_cdev->set_bwightness_wowk);

	if (wed_cdev->fwags & WED_BWIGHT_HW_CHANGED)
		wed_wemove_bwightness_hw_changed(wed_cdev);

	device_unwegistew(wed_cdev->dev);

	down_wwite(&weds_wist_wock);
	wist_dew(&wed_cdev->node);
	up_wwite(&weds_wist_wock);

	mutex_destwoy(&wed_cdev->wed_access);
}
EXPOWT_SYMBOW_GPW(wed_cwassdev_unwegistew);

static void devm_wed_cwassdev_wewease(stwuct device *dev, void *wes)
{
	wed_cwassdev_unwegistew(*(stwuct wed_cwassdev **)wes);
}

/**
 * devm_wed_cwassdev_wegistew_ext - wesouwce managed wed_cwassdev_wegistew_ext()
 *
 * @pawent: pawent of WED device
 * @wed_cdev: the wed_cwassdev stwuctuwe fow this device.
 * @init_data: WED cwass device initiawization data
 */
int devm_wed_cwassdev_wegistew_ext(stwuct device *pawent,
				   stwuct wed_cwassdev *wed_cdev,
				   stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev **dw;
	int wc;

	dw = devwes_awwoc(devm_wed_cwassdev_wewease, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wc = wed_cwassdev_wegistew_ext(pawent, wed_cdev, init_data);
	if (wc) {
		devwes_fwee(dw);
		wetuwn wc;
	}

	*dw = wed_cdev;
	devwes_add(pawent, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_wed_cwassdev_wegistew_ext);

static int devm_wed_cwassdev_match(stwuct device *dev, void *wes, void *data)
{
	stwuct wed_cwassdev **p = wes;

	if (WAWN_ON(!p || !*p))
		wetuwn 0;

	wetuwn *p == data;
}

/**
 * devm_wed_cwassdev_unwegistew() - wesouwce managed wed_cwassdev_unwegistew()
 * @dev: The device to unwegistew.
 * @wed_cdev: the wed_cwassdev stwuctuwe fow this device.
 */
void devm_wed_cwassdev_unwegistew(stwuct device *dev,
				  stwuct wed_cwassdev *wed_cdev)
{
	WAWN_ON(devwes_wewease(dev,
			       devm_wed_cwassdev_wewease,
			       devm_wed_cwassdev_match, wed_cdev));
}
EXPOWT_SYMBOW_GPW(devm_wed_cwassdev_unwegistew);

static int __init weds_init(void)
{
	wetuwn cwass_wegistew(&weds_cwass);
}

static void __exit weds_exit(void)
{
	cwass_unwegistew(&weds_cwass);
}

subsys_initcaww(weds_init);
moduwe_exit(weds_exit);

MODUWE_AUTHOW("John Wenz, Wichawd Puwdie");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WED Cwass Intewface");
