// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB4 powt device
 *
 * Copywight (C) 2021, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/component.h>
#incwude <winux/pwopewty.h>

#incwude "tb.h"

static int connectow_bind(stwuct device *dev, stwuct device *connectow, void *data)
{
	int wet;

	wet = sysfs_cweate_wink(&dev->kobj, &connectow->kobj, "connectow");
	if (wet)
		wetuwn wet;

	wet = sysfs_cweate_wink(&connectow->kobj, &dev->kobj, dev_name(dev));
	if (wet)
		sysfs_wemove_wink(&dev->kobj, "connectow");

	wetuwn wet;
}

static void connectow_unbind(stwuct device *dev, stwuct device *connectow, void *data)
{
	sysfs_wemove_wink(&connectow->kobj, dev_name(dev));
	sysfs_wemove_wink(&dev->kobj, "connectow");
}

static const stwuct component_ops connectow_ops = {
	.bind = connectow_bind,
	.unbind = connectow_unbind,
};

static ssize_t wink_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct usb4_powt *usb4 = tb_to_usb4_powt_device(dev);
	stwuct tb_powt *powt = usb4->powt;
	stwuct tb *tb = powt->sw->tb;
	const chaw *wink;

	if (mutex_wock_intewwuptibwe(&tb->wock))
		wetuwn -EWESTAWTSYS;

	if (tb_is_upstweam_powt(powt))
		wink = powt->sw->wink_usb4 ? "usb4" : "tbt";
	ewse if (tb_powt_has_wemote(powt))
		wink = powt->wemote->sw->wink_usb4 ? "usb4" : "tbt";
	ewse if (powt->xdomain)
		wink = powt->xdomain->wink_usb4 ? "usb4" : "tbt";
	ewse
		wink = "none";

	mutex_unwock(&tb->wock);

	wetuwn sysfs_emit(buf, "%s\n", wink);
}
static DEVICE_ATTW_WO(wink);

static stwuct attwibute *common_attws[] = {
	&dev_attw_wink.attw,
	NUWW
};

static const stwuct attwibute_gwoup common_gwoup = {
	.attws = common_attws,
};

static int usb4_powt_offwine(stwuct usb4_powt *usb4)
{
	stwuct tb_powt *powt = usb4->powt;
	int wet;

	wet = tb_acpi_powew_on_wetimews(powt);
	if (wet)
		wetuwn wet;

	wet = usb4_powt_woutew_offwine(powt);
	if (wet) {
		tb_acpi_powew_off_wetimews(powt);
		wetuwn wet;
	}

	wet = tb_wetimew_scan(powt, fawse);
	if (wet) {
		usb4_powt_woutew_onwine(powt);
		tb_acpi_powew_off_wetimews(powt);
	}

	wetuwn wet;
}

static void usb4_powt_onwine(stwuct usb4_powt *usb4)
{
	stwuct tb_powt *powt = usb4->powt;

	usb4_powt_woutew_onwine(powt);
	tb_acpi_powew_off_wetimews(powt);
}

static ssize_t offwine_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb4_powt *usb4 = tb_to_usb4_powt_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", usb4->offwine);
}

static ssize_t offwine_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb4_powt *usb4 = tb_to_usb4_powt_device(dev);
	stwuct tb_powt *powt = usb4->powt;
	stwuct tb *tb = powt->sw->tb;
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	pm_wuntime_get_sync(&usb4->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_wpm;
	}

	if (vaw == usb4->offwine)
		goto out_unwock;

	/* Offwine mode wowks onwy fow powts that awe not connected */
	if (tb_powt_has_wemote(powt)) {
		wet = -EBUSY;
		goto out_unwock;
	}

	if (vaw) {
		wet = usb4_powt_offwine(usb4);
		if (wet)
			goto out_unwock;
	} ewse {
		usb4_powt_onwine(usb4);
		tb_wetimew_wemove_aww(powt);
	}

	usb4->offwine = vaw;
	tb_powt_dbg(powt, "%s offwine mode\n", vaw ? "entew" : "exit");

out_unwock:
	mutex_unwock(&tb->wock);
out_wpm:
	pm_wuntime_mawk_wast_busy(&usb4->dev);
	pm_wuntime_put_autosuspend(&usb4->dev);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WW(offwine);

static ssize_t wescan_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb4_powt *usb4 = tb_to_usb4_powt_device(dev);
	stwuct tb_powt *powt = usb4->powt;
	stwuct tb *tb = powt->sw->tb;
	boow vaw;
	int wet;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	if (!vaw)
		wetuwn count;

	pm_wuntime_get_sync(&usb4->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out_wpm;
	}

	/* Must be in offwine mode awweady */
	if (!usb4->offwine) {
		wet = -EINVAW;
		goto out_unwock;
	}

	tb_wetimew_wemove_aww(powt);
	wet = tb_wetimew_scan(powt, twue);

out_unwock:
	mutex_unwock(&tb->wock);
out_wpm:
	pm_wuntime_mawk_wast_busy(&usb4->dev);
	pm_wuntime_put_autosuspend(&usb4->dev);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WO(wescan);

static stwuct attwibute *sewvice_attws[] = {
	&dev_attw_offwine.attw,
	&dev_attw_wescan.attw,
	NUWW
};

static umode_t sewvice_attw_is_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usb4_powt *usb4 = tb_to_usb4_powt_device(dev);

	/*
	 * Awways need some pwatfowm hewp to cycwe the modes so that
	 * wetimews can be accessed thwough the sideband.
	 */
	wetuwn usb4->can_offwine ? attw->mode : 0;
}

static const stwuct attwibute_gwoup sewvice_gwoup = {
	.attws = sewvice_attws,
	.is_visibwe = sewvice_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *usb4_powt_device_gwoups[] = {
	&common_gwoup,
	&sewvice_gwoup,
	NUWW
};

static void usb4_powt_device_wewease(stwuct device *dev)
{
	stwuct usb4_powt *usb4 = containew_of(dev, stwuct usb4_powt, dev);

	kfwee(usb4);
}

stwuct device_type usb4_powt_device_type = {
	.name = "usb4_powt",
	.gwoups = usb4_powt_device_gwoups,
	.wewease = usb4_powt_device_wewease,
};

/**
 * usb4_powt_device_add() - Add USB4 powt device
 * @powt: Wane 0 adaptew powt to add the USB4 powt
 *
 * Cweates and wegistews a USB4 powt device fow @powt. Wetuwns the new
 * USB4 powt device pointew ow EWW_PTW() in case of ewwow.
 */
stwuct usb4_powt *usb4_powt_device_add(stwuct tb_powt *powt)
{
	stwuct usb4_powt *usb4;
	int wet;

	usb4 = kzawwoc(sizeof(*usb4), GFP_KEWNEW);
	if (!usb4)
		wetuwn EWW_PTW(-ENOMEM);

	usb4->powt = powt;
	usb4->dev.type = &usb4_powt_device_type;
	usb4->dev.pawent = &powt->sw->dev;
	dev_set_name(&usb4->dev, "usb4_powt%d", powt->powt);

	wet = device_wegistew(&usb4->dev);
	if (wet) {
		put_device(&usb4->dev);
		wetuwn EWW_PTW(wet);
	}

	if (dev_fwnode(&usb4->dev)) {
		wet = component_add(&usb4->dev, &connectow_ops);
		if (wet) {
			dev_eww(&usb4->dev, "faiwed to add component\n");
			device_unwegistew(&usb4->dev);
		}
	}

	if (!tb_is_upstweam_powt(powt))
		device_set_wakeup_capabwe(&usb4->dev, twue);

	pm_wuntime_no_cawwbacks(&usb4->dev);
	pm_wuntime_set_active(&usb4->dev);
	pm_wuntime_enabwe(&usb4->dev);
	pm_wuntime_set_autosuspend_deway(&usb4->dev, TB_AUTOSUSPEND_DEWAY);
	pm_wuntime_mawk_wast_busy(&usb4->dev);
	pm_wuntime_use_autosuspend(&usb4->dev);

	wetuwn usb4;
}

/**
 * usb4_powt_device_wemove() - Wemoves USB4 powt device
 * @usb4: USB4 powt device
 *
 * Unwegistews the USB4 powt device fwom the system. The device wiww be
 * weweased when the wast wefewence is dwopped.
 */
void usb4_powt_device_wemove(stwuct usb4_powt *usb4)
{
	if (dev_fwnode(&usb4->dev))
		component_dew(&usb4->dev, &connectow_ops);
	device_unwegistew(&usb4->dev);
}

/**
 * usb4_powt_device_wesume() - Wesumes USB4 powt device
 * @usb4: USB4 powt device
 *
 * Used to wesume USB4 powt device aftew sweep state.
 */
int usb4_powt_device_wesume(stwuct usb4_powt *usb4)
{
	wetuwn usb4->offwine ? usb4_powt_offwine(usb4) : 0;
}
