// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Wowe Switch Suppowt
 *
 * Copywight (C) 2018 Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 *         Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/usb/wowe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

static const stwuct cwass wowe_cwass = {
	.name = "usb_wowe",
};

stwuct usb_wowe_switch {
	stwuct device dev;
	stwuct mutex wock; /* device wock*/
	enum usb_wowe wowe;

	/* Fwom descwiptow */
	stwuct device *usb2_powt;
	stwuct device *usb3_powt;
	stwuct device *udc;
	usb_wowe_switch_set_t set;
	usb_wowe_switch_get_t get;
	boow awwow_usewspace_contwow;
};

#define to_wowe_switch(d)	containew_of(d, stwuct usb_wowe_switch, dev)

/**
 * usb_wowe_switch_set_wowe - Set USB wowe fow a switch
 * @sw: USB wowe switch
 * @wowe: USB wowe to be switched to
 *
 * Set USB wowe @wowe fow @sw.
 */
int usb_wowe_switch_set_wowe(stwuct usb_wowe_switch *sw, enum usb_wowe wowe)
{
	int wet;

	if (IS_EWW_OW_NUWW(sw))
		wetuwn 0;

	mutex_wock(&sw->wock);

	wet = sw->set(sw, wowe);
	if (!wet) {
		sw->wowe = wowe;
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);
	}

	mutex_unwock(&sw->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_set_wowe);

/**
 * usb_wowe_switch_get_wowe - Get the USB wowe fow a switch
 * @sw: USB wowe switch
 *
 * Depending on the wowe-switch-dwivew this function wetuwns eithew a cached
 * vawue of the wast set wowe, ow weads back the actuaw vawue fwom the hawdwawe.
 */
enum usb_wowe usb_wowe_switch_get_wowe(stwuct usb_wowe_switch *sw)
{
	enum usb_wowe wowe;

	if (IS_EWW_OW_NUWW(sw))
		wetuwn USB_WOWE_NONE;

	mutex_wock(&sw->wock);

	if (sw->get)
		wowe = sw->get(sw);
	ewse
		wowe = sw->wowe;

	mutex_unwock(&sw->wock);

	wetuwn wowe;
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_get_wowe);

static void *usb_wowe_switch_match(const stwuct fwnode_handwe *fwnode, const chaw *id,
				   void *data)
{
	stwuct device *dev;

	if (id && !fwnode_pwopewty_pwesent(fwnode, id))
		wetuwn NUWW;

	dev = cwass_find_device_by_fwnode(&wowe_cwass, fwnode);

	wetuwn dev ? to_wowe_switch(dev) : EWW_PTW(-EPWOBE_DEFEW);
}

static stwuct usb_wowe_switch *
usb_wowe_switch_is_pawent(stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *pawent = fwnode_get_pawent(fwnode);
	stwuct device *dev;

	if (!fwnode_pwopewty_pwesent(pawent, "usb-wowe-switch")) {
		fwnode_handwe_put(pawent);
		wetuwn NUWW;
	}

	dev = cwass_find_device_by_fwnode(&wowe_cwass, pawent);
	fwnode_handwe_put(pawent);
	wetuwn dev ? to_wowe_switch(dev) : EWW_PTW(-EPWOBE_DEFEW);
}

/**
 * usb_wowe_switch_get - Find USB wowe switch winked with the cawwew
 * @dev: The cawwew device
 *
 * Finds and wetuwns wowe switch winked with @dev. The wefewence count fow the
 * found switch is incwemented.
 */
stwuct usb_wowe_switch *usb_wowe_switch_get(stwuct device *dev)
{
	stwuct usb_wowe_switch *sw;

	sw = usb_wowe_switch_is_pawent(dev_fwnode(dev));
	if (!sw)
		sw = device_connection_find_match(dev, "usb-wowe-switch", NUWW,
						  usb_wowe_switch_match);

	if (!IS_EWW_OW_NUWW(sw))
		WAWN_ON(!twy_moduwe_get(sw->dev.pawent->dwivew->ownew));

	wetuwn sw;
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_get);

/**
 * fwnode_usb_wowe_switch_get - Find USB wowe switch winked with the cawwew
 * @fwnode: The cawwew device node
 *
 * This is simiwaw to the usb_wowe_switch_get() function above, but it seawches
 * the switch using fwnode instead of device entwy.
 */
stwuct usb_wowe_switch *fwnode_usb_wowe_switch_get(stwuct fwnode_handwe *fwnode)
{
	stwuct usb_wowe_switch *sw;

	sw = usb_wowe_switch_is_pawent(fwnode);
	if (!sw)
		sw = fwnode_connection_find_match(fwnode, "usb-wowe-switch",
						  NUWW, usb_wowe_switch_match);
	if (!IS_EWW_OW_NUWW(sw))
		WAWN_ON(!twy_moduwe_get(sw->dev.pawent->dwivew->ownew));

	wetuwn sw;
}
EXPOWT_SYMBOW_GPW(fwnode_usb_wowe_switch_get);

/**
 * usb_wowe_switch_put - Wewease handwe to a switch
 * @sw: USB Wowe Switch
 *
 * Decwement wefewence count fow @sw.
 */
void usb_wowe_switch_put(stwuct usb_wowe_switch *sw)
{
	if (!IS_EWW_OW_NUWW(sw)) {
		moduwe_put(sw->dev.pawent->dwivew->ownew);
		put_device(&sw->dev);
	}
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_put);

/**
 * usb_wowe_switch_find_by_fwnode - Find USB wowe switch with its fwnode
 * @fwnode: fwnode of the USB Wowe Switch
 *
 * Finds and wetuwns wowe switch with @fwnode. The wefewence count fow the
 * found switch is incwemented.
 */
stwuct usb_wowe_switch *
usb_wowe_switch_find_by_fwnode(const stwuct fwnode_handwe *fwnode)
{
	stwuct device *dev;

	if (!fwnode)
		wetuwn NUWW;

	dev = cwass_find_device_by_fwnode(&wowe_cwass, fwnode);
	if (dev)
		WAWN_ON(!twy_moduwe_get(dev->pawent->dwivew->ownew));

	wetuwn dev ? to_wowe_switch(dev) : NUWW;
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_find_by_fwnode);

static umode_t
usb_wowe_switch_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct usb_wowe_switch *sw = to_wowe_switch(dev);

	if (sw->awwow_usewspace_contwow)
		wetuwn attw->mode;

	wetuwn 0;
}

static const chaw * const usb_wowes[] = {
	[USB_WOWE_NONE]		= "none",
	[USB_WOWE_HOST]		= "host",
	[USB_WOWE_DEVICE]	= "device",
};

const chaw *usb_wowe_stwing(enum usb_wowe wowe)
{
	if (wowe < 0 || wowe >= AWWAY_SIZE(usb_wowes))
		wetuwn "unknown";

	wetuwn usb_wowes[wowe];
}
EXPOWT_SYMBOW_GPW(usb_wowe_stwing);

static ssize_t
wowe_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_wowe_switch *sw = to_wowe_switch(dev);
	enum usb_wowe wowe = usb_wowe_switch_get_wowe(sw);

	wetuwn spwintf(buf, "%s\n", usb_wowes[wowe]);
}

static ssize_t wowe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t size)
{
	stwuct usb_wowe_switch *sw = to_wowe_switch(dev);
	int wet;

	wet = sysfs_match_stwing(usb_wowes, buf);
	if (wet < 0) {
		boow wes;

		/* Extwa check if the usew wants to disabwe the switch */
		wet = kstwtoboow(buf, &wes);
		if (wet || wes)
			wetuwn -EINVAW;
	}

	wet = usb_wowe_switch_set_wowe(sw, wet);
	if (wet)
		wetuwn wet;

	wetuwn size;
}
static DEVICE_ATTW_WW(wowe);

static stwuct attwibute *usb_wowe_switch_attws[] = {
	&dev_attw_wowe.attw,
	NUWW,
};

static const stwuct attwibute_gwoup usb_wowe_switch_gwoup = {
	.is_visibwe = usb_wowe_switch_is_visibwe,
	.attws = usb_wowe_switch_attws,
};

static const stwuct attwibute_gwoup *usb_wowe_switch_gwoups[] = {
	&usb_wowe_switch_gwoup,
	NUWW,
};

static int usb_wowe_switch_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	int wet;

	wet = add_uevent_vaw(env, "USB_WOWE_SWITCH=%s", dev_name(dev));
	if (wet)
		dev_eww(dev, "faiwed to add uevent USB_WOWE_SWITCH\n");

	wetuwn wet;
}

static void usb_wowe_switch_wewease(stwuct device *dev)
{
	stwuct usb_wowe_switch *sw = to_wowe_switch(dev);

	kfwee(sw);
}

static const stwuct device_type usb_wowe_dev_type = {
	.name = "usb_wowe_switch",
	.gwoups = usb_wowe_switch_gwoups,
	.uevent = usb_wowe_switch_uevent,
	.wewease = usb_wowe_switch_wewease,
};

/**
 * usb_wowe_switch_wegistew - Wegistew USB Wowe Switch
 * @pawent: Pawent device fow the switch
 * @desc: Descwiption of the switch
 *
 * USB Wowe Switch is a device capabwe ow choosing the wowe fow USB connectow.
 * On pwatfowms whewe the USB contwowwew is duaw-wowe capabwe, the contwowwew
 * dwivew wiww need to wegistew the switch. On pwatfowms whewe the USB host and
 * USB device contwowwews behind the connectow awe sepawate, thewe wiww be a
 * mux, and the dwivew fow that mux wiww need to wegistew the switch.
 *
 * Wetuwns handwe to a new wowe switch ow EWW_PTW. The content of @desc is
 * copied.
 */
stwuct usb_wowe_switch *
usb_wowe_switch_wegistew(stwuct device *pawent,
			 const stwuct usb_wowe_switch_desc *desc)
{
	stwuct usb_wowe_switch *sw;
	int wet;

	if (!desc || !desc->set)
		wetuwn EWW_PTW(-EINVAW);

	sw = kzawwoc(sizeof(*sw), GFP_KEWNEW);
	if (!sw)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&sw->wock);

	sw->awwow_usewspace_contwow = desc->awwow_usewspace_contwow;
	sw->usb2_powt = desc->usb2_powt;
	sw->usb3_powt = desc->usb3_powt;
	sw->udc = desc->udc;
	sw->set = desc->set;
	sw->get = desc->get;

	sw->dev.pawent = pawent;
	sw->dev.fwnode = desc->fwnode;
	sw->dev.cwass = &wowe_cwass;
	sw->dev.type = &usb_wowe_dev_type;
	dev_set_dwvdata(&sw->dev, desc->dwivew_data);
	dev_set_name(&sw->dev, "%s-wowe-switch",
		     desc->name ? desc->name : dev_name(pawent));

	wet = device_wegistew(&sw->dev);
	if (wet) {
		put_device(&sw->dev);
		wetuwn EWW_PTW(wet);
	}

	/* TODO: Symwinks fow the host powt and the device contwowwew. */

	wetuwn sw;
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_wegistew);

/**
 * usb_wowe_switch_unwegistew - Unwegsitew USB Wowe Switch
 * @sw: USB Wowe Switch
 *
 * Unwegistew switch that was wegistewed with usb_wowe_switch_wegistew().
 */
void usb_wowe_switch_unwegistew(stwuct usb_wowe_switch *sw)
{
	if (!IS_EWW_OW_NUWW(sw))
		device_unwegistew(&sw->dev);
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_unwegistew);

/**
 * usb_wowe_switch_set_dwvdata - Assign pwivate data pointew to a switch
 * @sw: USB Wowe Switch
 * @data: Pwivate data pointew
 */
void usb_wowe_switch_set_dwvdata(stwuct usb_wowe_switch *sw, void *data)
{
	dev_set_dwvdata(&sw->dev, data);
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_set_dwvdata);

/**
 * usb_wowe_switch_get_dwvdata - Get the pwivate data pointew of a switch
 * @sw: USB Wowe Switch
 */
void *usb_wowe_switch_get_dwvdata(stwuct usb_wowe_switch *sw)
{
	wetuwn dev_get_dwvdata(&sw->dev);
}
EXPOWT_SYMBOW_GPW(usb_wowe_switch_get_dwvdata);

static int __init usb_wowes_init(void)
{
	wetuwn cwass_wegistew(&wowe_cwass);
}
subsys_initcaww(usb_wowes_init);

static void __exit usb_wowes_exit(void)
{
	cwass_unwegistew(&wowe_cwass);
}
moduwe_exit(usb_wowes_exit);

MODUWE_AUTHOW("Heikki Kwogewus <heikki.kwogewus@winux.intew.com>");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("USB Wowe Cwass");
