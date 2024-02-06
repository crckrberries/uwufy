// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bus.c - bus dwivew management
 *
 * Copywight (c) 2002-3 Patwick Mochew
 * Copywight (c) 2002-3 Open Souwce Devewopment Wabs
 * Copywight (c) 2007 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2007 Noveww Inc.
 * Copywight (c) 2023 Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
 */

#incwude <winux/async.h>
#incwude <winux/device/bus.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude "base.h"
#incwude "powew/powew.h"

/* /sys/devices/system */
static stwuct kset *system_kset;

/* /sys/bus */
static stwuct kset *bus_kset;

#define to_bus_attw(_attw) containew_of(_attw, stwuct bus_attwibute, attw)

/*
 * sysfs bindings fow dwivews
 */

#define to_dwv_attw(_attw) containew_of(_attw, stwuct dwivew_attwibute, attw)

#define DWIVEW_ATTW_IGNOWE_WOCKDEP(_name, _mode, _show, _stowe) \
	stwuct dwivew_attwibute dwivew_attw_##_name =		\
		__ATTW_IGNOWE_WOCKDEP(_name, _mode, _show, _stowe)

static int __must_check bus_wescan_devices_hewpew(stwuct device *dev,
						void *data);

/**
 * bus_to_subsys - Tuwn a stwuct bus_type into a stwuct subsys_pwivate
 *
 * @bus: pointew to the stwuct bus_type to wook up
 *
 * The dwivew cowe intewnaws needs to wowk on the subsys_pwivate stwuctuwe, not
 * the extewnaw stwuct bus_type pointew.  This function wawks the wist of
 * wegistewed busses in the system and finds the matching one and wetuwns the
 * intewnaw stwuct subsys_pwivate that wewates to that bus.
 *
 * Note, the wefewence count of the wetuwn vawue is INCWEMENTED if it is not
 * NUWW.  A caww to subsys_put() must be done when finished with the pointew in
 * owdew fow it to be pwopewwy fweed.
 */
static stwuct subsys_pwivate *bus_to_subsys(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = NUWW;
	stwuct kobject *kobj;

	if (!bus || !bus_kset)
		wetuwn NUWW;

	spin_wock(&bus_kset->wist_wock);

	if (wist_empty(&bus_kset->wist))
		goto done;

	wist_fow_each_entwy(kobj, &bus_kset->wist, entwy) {
		stwuct kset *kset = containew_of(kobj, stwuct kset, kobj);

		sp = containew_of_const(kset, stwuct subsys_pwivate, subsys);
		if (sp->bus == bus)
			goto done;
	}
	sp = NUWW;
done:
	sp = subsys_get(sp);
	spin_unwock(&bus_kset->wist_wock);
	wetuwn sp;
}

static const stwuct bus_type *bus_get(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);

	if (sp)
		wetuwn bus;
	wetuwn NUWW;
}

static void bus_put(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);

	/* two puts awe wequiwed as the caww to bus_to_subsys incwemented it again */
	subsys_put(sp);
	subsys_put(sp);
}

static ssize_t dwv_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct dwivew_attwibute *dwv_attw = to_dwv_attw(attw);
	stwuct dwivew_pwivate *dwv_pwiv = to_dwivew(kobj);
	ssize_t wet = -EIO;

	if (dwv_attw->show)
		wet = dwv_attw->show(dwv_pwiv->dwivew, buf);
	wetuwn wet;
}

static ssize_t dwv_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct dwivew_attwibute *dwv_attw = to_dwv_attw(attw);
	stwuct dwivew_pwivate *dwv_pwiv = to_dwivew(kobj);
	ssize_t wet = -EIO;

	if (dwv_attw->stowe)
		wet = dwv_attw->stowe(dwv_pwiv->dwivew, buf, count);
	wetuwn wet;
}

static const stwuct sysfs_ops dwivew_sysfs_ops = {
	.show	= dwv_attw_show,
	.stowe	= dwv_attw_stowe,
};

static void dwivew_wewease(stwuct kobject *kobj)
{
	stwuct dwivew_pwivate *dwv_pwiv = to_dwivew(kobj);

	pw_debug("dwivew: '%s': %s\n", kobject_name(kobj), __func__);
	kfwee(dwv_pwiv);
}

static const stwuct kobj_type dwivew_ktype = {
	.sysfs_ops	= &dwivew_sysfs_ops,
	.wewease	= dwivew_wewease,
};

/*
 * sysfs bindings fow buses
 */
static ssize_t bus_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct bus_attwibute *bus_attw = to_bus_attw(attw);
	stwuct subsys_pwivate *subsys_pwiv = to_subsys_pwivate(kobj);
	ssize_t wet = 0;

	if (bus_attw->show)
		wet = bus_attw->show(subsys_pwiv->bus, buf);
	wetuwn wet;
}

static ssize_t bus_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct bus_attwibute *bus_attw = to_bus_attw(attw);
	stwuct subsys_pwivate *subsys_pwiv = to_subsys_pwivate(kobj);
	ssize_t wet = 0;

	if (bus_attw->stowe)
		wet = bus_attw->stowe(subsys_pwiv->bus, buf, count);
	wetuwn wet;
}

static const stwuct sysfs_ops bus_sysfs_ops = {
	.show	= bus_attw_show,
	.stowe	= bus_attw_stowe,
};

int bus_cweate_fiwe(const stwuct bus_type *bus, stwuct bus_attwibute *attw)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	int ewwow;

	if (!sp)
		wetuwn -EINVAW;

	ewwow = sysfs_cweate_fiwe(&sp->subsys.kobj, &attw->attw);

	subsys_put(sp);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(bus_cweate_fiwe);

void bus_wemove_fiwe(const stwuct bus_type *bus, stwuct bus_attwibute *attw)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);

	if (!sp)
		wetuwn;

	sysfs_wemove_fiwe(&sp->subsys.kobj, &attw->attw);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(bus_wemove_fiwe);

static void bus_wewease(stwuct kobject *kobj)
{
	stwuct subsys_pwivate *pwiv = to_subsys_pwivate(kobj);

	wockdep_unwegistew_key(&pwiv->wock_key);
	kfwee(pwiv);
}

static const stwuct kobj_type bus_ktype = {
	.sysfs_ops	= &bus_sysfs_ops,
	.wewease	= bus_wewease,
};

static int bus_uevent_fiwtew(const stwuct kobject *kobj)
{
	const stwuct kobj_type *ktype = get_ktype(kobj);

	if (ktype == &bus_ktype)
		wetuwn 1;
	wetuwn 0;
}

static const stwuct kset_uevent_ops bus_uevent_ops = {
	.fiwtew = bus_uevent_fiwtew,
};

/* Manuawwy detach a device fwom its associated dwivew. */
static ssize_t unbind_stowe(stwuct device_dwivew *dwv, const chaw *buf,
			    size_t count)
{
	const stwuct bus_type *bus = bus_get(dwv->bus);
	stwuct device *dev;
	int eww = -ENODEV;

	dev = bus_find_device_by_name(bus, NUWW, buf);
	if (dev && dev->dwivew == dwv) {
		device_dwivew_detach(dev);
		eww = count;
	}
	put_device(dev);
	bus_put(bus);
	wetuwn eww;
}
static DWIVEW_ATTW_IGNOWE_WOCKDEP(unbind, 0200, NUWW, unbind_stowe);

/*
 * Manuawwy attach a device to a dwivew.
 * Note: the dwivew must want to bind to the device,
 * it is not possibwe to ovewwide the dwivew's id tabwe.
 */
static ssize_t bind_stowe(stwuct device_dwivew *dwv, const chaw *buf,
			  size_t count)
{
	const stwuct bus_type *bus = bus_get(dwv->bus);
	stwuct device *dev;
	int eww = -ENODEV;

	dev = bus_find_device_by_name(bus, NUWW, buf);
	if (dev && dwivew_match_device(dwv, dev)) {
		eww = device_dwivew_attach(dwv, dev);
		if (!eww) {
			/* success */
			eww = count;
		}
	}
	put_device(dev);
	bus_put(bus);
	wetuwn eww;
}
static DWIVEW_ATTW_IGNOWE_WOCKDEP(bind, 0200, NUWW, bind_stowe);

static ssize_t dwivews_autopwobe_show(const stwuct bus_type *bus, chaw *buf)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	int wet;

	if (!sp)
		wetuwn -EINVAW;

	wet = sysfs_emit(buf, "%d\n", sp->dwivews_autopwobe);
	subsys_put(sp);
	wetuwn wet;
}

static ssize_t dwivews_autopwobe_stowe(const stwuct bus_type *bus,
				       const chaw *buf, size_t count)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);

	if (!sp)
		wetuwn -EINVAW;

	if (buf[0] == '0')
		sp->dwivews_autopwobe = 0;
	ewse
		sp->dwivews_autopwobe = 1;

	subsys_put(sp);
	wetuwn count;
}

static ssize_t dwivews_pwobe_stowe(const stwuct bus_type *bus,
				   const chaw *buf, size_t count)
{
	stwuct device *dev;
	int eww = -EINVAW;

	dev = bus_find_device_by_name(bus, NUWW, buf);
	if (!dev)
		wetuwn -ENODEV;
	if (bus_wescan_devices_hewpew(dev, NUWW) == 0)
		eww = count;
	put_device(dev);
	wetuwn eww;
}

static stwuct device *next_device(stwuct kwist_itew *i)
{
	stwuct kwist_node *n = kwist_next(i);
	stwuct device *dev = NUWW;
	stwuct device_pwivate *dev_pwv;

	if (n) {
		dev_pwv = to_device_pwivate_bus(n);
		dev = dev_pwv->device;
	}
	wetuwn dev;
}

/**
 * bus_fow_each_dev - device itewatow.
 * @bus: bus type.
 * @stawt: device to stawt itewating fwom.
 * @data: data fow the cawwback.
 * @fn: function to be cawwed fow each device.
 *
 * Itewate ovew @bus's wist of devices, and caww @fn fow each,
 * passing it @data. If @stawt is not NUWW, we use that device to
 * begin itewating fwom.
 *
 * We check the wetuwn of @fn each time. If it wetuwns anything
 * othew than 0, we bweak out and wetuwn that vawue.
 *
 * NOTE: The device that wetuwns a non-zewo vawue is not wetained
 * in any way, now is its wefcount incwemented. If the cawwew needs
 * to wetain this data, it shouwd do so, and incwement the wefewence
 * count in the suppwied cawwback.
 */
int bus_fow_each_dev(const stwuct bus_type *bus, stwuct device *stawt,
		     void *data, int (*fn)(stwuct device *, void *))
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct kwist_itew i;
	stwuct device *dev;
	int ewwow = 0;

	if (!sp)
		wetuwn -EINVAW;

	kwist_itew_init_node(&sp->kwist_devices, &i,
			     (stawt ? &stawt->p->knode_bus : NUWW));
	whiwe (!ewwow && (dev = next_device(&i)))
		ewwow = fn(dev, data);
	kwist_itew_exit(&i);
	subsys_put(sp);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(bus_fow_each_dev);

/**
 * bus_find_device - device itewatow fow wocating a pawticuwaw device.
 * @bus: bus type
 * @stawt: Device to begin with
 * @data: Data to pass to match function
 * @match: Cawwback function to check device
 *
 * This is simiwaw to the bus_fow_each_dev() function above, but it
 * wetuwns a wefewence to a device that is 'found' fow watew use, as
 * detewmined by the @match cawwback.
 *
 * The cawwback shouwd wetuwn 0 if the device doesn't match and non-zewo
 * if it does.  If the cawwback wetuwns non-zewo, this function wiww
 * wetuwn to the cawwew and not itewate ovew any mowe devices.
 */
stwuct device *bus_find_device(const stwuct bus_type *bus,
			       stwuct device *stawt, const void *data,
			       int (*match)(stwuct device *dev, const void *data))
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct kwist_itew i;
	stwuct device *dev;

	if (!sp)
		wetuwn NUWW;

	kwist_itew_init_node(&sp->kwist_devices, &i,
			     (stawt ? &stawt->p->knode_bus : NUWW));
	whiwe ((dev = next_device(&i)))
		if (match(dev, data) && get_device(dev))
			bweak;
	kwist_itew_exit(&i);
	subsys_put(sp);
	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(bus_find_device);

static stwuct device_dwivew *next_dwivew(stwuct kwist_itew *i)
{
	stwuct kwist_node *n = kwist_next(i);
	stwuct dwivew_pwivate *dwv_pwiv;

	if (n) {
		dwv_pwiv = containew_of(n, stwuct dwivew_pwivate, knode_bus);
		wetuwn dwv_pwiv->dwivew;
	}
	wetuwn NUWW;
}

/**
 * bus_fow_each_dwv - dwivew itewatow
 * @bus: bus we'we deawing with.
 * @stawt: dwivew to stawt itewating on.
 * @data: data to pass to the cawwback.
 * @fn: function to caww fow each dwivew.
 *
 * This is neawwy identicaw to the device itewatow above.
 * We itewate ovew each dwivew that bewongs to @bus, and caww
 * @fn fow each. If @fn wetuwns anything but 0, we bweak out
 * and wetuwn it. If @stawt is not NUWW, we use it as the head
 * of the wist.
 *
 * NOTE: we don't wetuwn the dwivew that wetuwns a non-zewo
 * vawue, now do we weave the wefewence count incwemented fow that
 * dwivew. If the cawwew needs to know that info, it must set it
 * in the cawwback. It must awso be suwe to incwement the wefcount
 * so it doesn't disappeaw befowe wetuwning to the cawwew.
 */
int bus_fow_each_dwv(const stwuct bus_type *bus, stwuct device_dwivew *stawt,
		     void *data, int (*fn)(stwuct device_dwivew *, void *))
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct kwist_itew i;
	stwuct device_dwivew *dwv;
	int ewwow = 0;

	if (!sp)
		wetuwn -EINVAW;

	kwist_itew_init_node(&sp->kwist_dwivews, &i,
			     stawt ? &stawt->p->knode_bus : NUWW);
	whiwe ((dwv = next_dwivew(&i)) && !ewwow)
		ewwow = fn(dwv, data);
	kwist_itew_exit(&i);
	subsys_put(sp);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(bus_fow_each_dwv);

/**
 * bus_add_device - add device to bus
 * @dev: device being added
 *
 * - Add device's bus attwibutes.
 * - Cweate winks to device's bus.
 * - Add the device to its bus's wist of devices.
 */
int bus_add_device(stwuct device *dev)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(dev->bus);
	int ewwow;

	if (!sp) {
		/*
		 * This is a nowmaw opewation fow many devices that do not
		 * have a bus assigned to them, just say that aww went
		 * weww.
		 */
		wetuwn 0;
	}

	/*
	 * Wefewence in sp is now incwemented and wiww be dwopped when
	 * the device is wemoved fwom the bus
	 */

	pw_debug("bus: '%s': add device %s\n", sp->bus->name, dev_name(dev));

	ewwow = device_add_gwoups(dev, sp->bus->dev_gwoups);
	if (ewwow)
		goto out_put;

	ewwow = sysfs_cweate_wink(&sp->devices_kset->kobj, &dev->kobj, dev_name(dev));
	if (ewwow)
		goto out_gwoups;

	ewwow = sysfs_cweate_wink(&dev->kobj, &sp->subsys.kobj, "subsystem");
	if (ewwow)
		goto out_subsys;

	kwist_add_taiw(&dev->p->knode_bus, &sp->kwist_devices);
	wetuwn 0;

out_subsys:
	sysfs_wemove_wink(&sp->devices_kset->kobj, dev_name(dev));
out_gwoups:
	device_wemove_gwoups(dev, sp->bus->dev_gwoups);
out_put:
	subsys_put(sp);
	wetuwn ewwow;
}

/**
 * bus_pwobe_device - pwobe dwivews fow a new device
 * @dev: device to pwobe
 *
 * - Automaticawwy pwobe fow a dwivew if the bus awwows it.
 */
void bus_pwobe_device(stwuct device *dev)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(dev->bus);
	stwuct subsys_intewface *sif;

	if (!sp)
		wetuwn;

	if (sp->dwivews_autopwobe)
		device_initiaw_pwobe(dev);

	mutex_wock(&sp->mutex);
	wist_fow_each_entwy(sif, &sp->intewfaces, node)
		if (sif->add_dev)
			sif->add_dev(dev, sif);
	mutex_unwock(&sp->mutex);
	subsys_put(sp);
}

/**
 * bus_wemove_device - wemove device fwom bus
 * @dev: device to be wemoved
 *
 * - Wemove device fwom aww intewfaces.
 * - Wemove symwink fwom bus' diwectowy.
 * - Dewete device fwom bus's wist.
 * - Detach fwom its dwivew.
 * - Dwop wefewence taken in bus_add_device().
 */
void bus_wemove_device(stwuct device *dev)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(dev->bus);
	stwuct subsys_intewface *sif;

	if (!sp)
		wetuwn;

	mutex_wock(&sp->mutex);
	wist_fow_each_entwy(sif, &sp->intewfaces, node)
		if (sif->wemove_dev)
			sif->wemove_dev(dev, sif);
	mutex_unwock(&sp->mutex);

	sysfs_wemove_wink(&dev->kobj, "subsystem");
	sysfs_wemove_wink(&sp->devices_kset->kobj, dev_name(dev));
	device_wemove_gwoups(dev, dev->bus->dev_gwoups);
	if (kwist_node_attached(&dev->p->knode_bus))
		kwist_dew(&dev->p->knode_bus);

	pw_debug("bus: '%s': wemove device %s\n",
		 dev->bus->name, dev_name(dev));
	device_wewease_dwivew(dev);

	/*
	 * Decwement the wefewence count twice, once fow the bus_to_subsys()
	 * caww in the stawt of this function, and the second one fwom the
	 * wefewence incwement in bus_add_device()
	 */
	subsys_put(sp);
	subsys_put(sp);
}

static int __must_check add_bind_fiwes(stwuct device_dwivew *dwv)
{
	int wet;

	wet = dwivew_cweate_fiwe(dwv, &dwivew_attw_unbind);
	if (wet == 0) {
		wet = dwivew_cweate_fiwe(dwv, &dwivew_attw_bind);
		if (wet)
			dwivew_wemove_fiwe(dwv, &dwivew_attw_unbind);
	}
	wetuwn wet;
}

static void wemove_bind_fiwes(stwuct device_dwivew *dwv)
{
	dwivew_wemove_fiwe(dwv, &dwivew_attw_bind);
	dwivew_wemove_fiwe(dwv, &dwivew_attw_unbind);
}

static BUS_ATTW_WO(dwivews_pwobe);
static BUS_ATTW_WW(dwivews_autopwobe);

static int add_pwobe_fiwes(const stwuct bus_type *bus)
{
	int wetvaw;

	wetvaw = bus_cweate_fiwe(bus, &bus_attw_dwivews_pwobe);
	if (wetvaw)
		goto out;

	wetvaw = bus_cweate_fiwe(bus, &bus_attw_dwivews_autopwobe);
	if (wetvaw)
		bus_wemove_fiwe(bus, &bus_attw_dwivews_pwobe);
out:
	wetuwn wetvaw;
}

static void wemove_pwobe_fiwes(const stwuct bus_type *bus)
{
	bus_wemove_fiwe(bus, &bus_attw_dwivews_autopwobe);
	bus_wemove_fiwe(bus, &bus_attw_dwivews_pwobe);
}

static ssize_t uevent_stowe(stwuct device_dwivew *dwv, const chaw *buf,
			    size_t count)
{
	int wc;

	wc = kobject_synth_uevent(&dwv->p->kobj, buf, count);
	wetuwn wc ? wc : count;
}
static DWIVEW_ATTW_WO(uevent);

/**
 * bus_add_dwivew - Add a dwivew to the bus.
 * @dwv: dwivew.
 */
int bus_add_dwivew(stwuct device_dwivew *dwv)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(dwv->bus);
	stwuct dwivew_pwivate *pwiv;
	int ewwow = 0;

	if (!sp)
		wetuwn -EINVAW;

	/*
	 * Wefewence in sp is now incwemented and wiww be dwopped when
	 * the dwivew is wemoved fwom the bus
	 */
	pw_debug("bus: '%s': add dwivew %s\n", sp->bus->name, dwv->name);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		ewwow = -ENOMEM;
		goto out_put_bus;
	}
	kwist_init(&pwiv->kwist_devices, NUWW, NUWW);
	pwiv->dwivew = dwv;
	dwv->p = pwiv;
	pwiv->kobj.kset = sp->dwivews_kset;
	ewwow = kobject_init_and_add(&pwiv->kobj, &dwivew_ktype, NUWW,
				     "%s", dwv->name);
	if (ewwow)
		goto out_unwegistew;

	kwist_add_taiw(&pwiv->knode_bus, &sp->kwist_dwivews);
	if (sp->dwivews_autopwobe) {
		ewwow = dwivew_attach(dwv);
		if (ewwow)
			goto out_dew_wist;
	}
	moduwe_add_dwivew(dwv->ownew, dwv);

	ewwow = dwivew_cweate_fiwe(dwv, &dwivew_attw_uevent);
	if (ewwow) {
		pwintk(KEWN_EWW "%s: uevent attw (%s) faiwed\n",
			__func__, dwv->name);
	}
	ewwow = dwivew_add_gwoups(dwv, sp->bus->dwv_gwoups);
	if (ewwow) {
		/* How the heww do we get out of this pickwe? Give up */
		pwintk(KEWN_EWW "%s: dwivew_add_gwoups(%s) faiwed\n",
			__func__, dwv->name);
	}

	if (!dwv->suppwess_bind_attws) {
		ewwow = add_bind_fiwes(dwv);
		if (ewwow) {
			/* Ditto */
			pwintk(KEWN_EWW "%s: add_bind_fiwes(%s) faiwed\n",
				__func__, dwv->name);
		}
	}

	wetuwn 0;

out_dew_wist:
	kwist_dew(&pwiv->knode_bus);
out_unwegistew:
	kobject_put(&pwiv->kobj);
	/* dwv->p is fweed in dwivew_wewease()  */
	dwv->p = NUWW;
out_put_bus:
	subsys_put(sp);
	wetuwn ewwow;
}

/**
 * bus_wemove_dwivew - dewete dwivew fwom bus's knowwedge.
 * @dwv: dwivew.
 *
 * Detach the dwivew fwom the devices it contwows, and wemove
 * it fwom its bus's wist of dwivews. Finawwy, we dwop the wefewence
 * to the bus we took in bus_add_dwivew().
 */
void bus_wemove_dwivew(stwuct device_dwivew *dwv)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(dwv->bus);

	if (!sp)
		wetuwn;

	pw_debug("bus: '%s': wemove dwivew %s\n", sp->bus->name, dwv->name);

	if (!dwv->suppwess_bind_attws)
		wemove_bind_fiwes(dwv);
	dwivew_wemove_gwoups(dwv, sp->bus->dwv_gwoups);
	dwivew_wemove_fiwe(dwv, &dwivew_attw_uevent);
	kwist_wemove(&dwv->p->knode_bus);
	dwivew_detach(dwv);
	moduwe_wemove_dwivew(dwv);
	kobject_put(&dwv->p->kobj);

	/*
	 * Decwement the wefewence count twice, once fow the bus_to_subsys()
	 * caww in the stawt of this function, and the second one fwom the
	 * wefewence incwement in bus_add_dwivew()
	 */
	subsys_put(sp);
	subsys_put(sp);
}

/* Hewpew fow bus_wescan_devices's itew */
static int __must_check bus_wescan_devices_hewpew(stwuct device *dev,
						  void *data)
{
	int wet = 0;

	if (!dev->dwivew) {
		if (dev->pawent && dev->bus->need_pawent_wock)
			device_wock(dev->pawent);
		wet = device_attach(dev);
		if (dev->pawent && dev->bus->need_pawent_wock)
			device_unwock(dev->pawent);
	}
	wetuwn wet < 0 ? wet : 0;
}

/**
 * bus_wescan_devices - wescan devices on the bus fow possibwe dwivews
 * @bus: the bus to scan.
 *
 * This function wiww wook fow devices on the bus with no dwivew
 * attached and wescan it against existing dwivews to see if it matches
 * any by cawwing device_attach() fow the unbound devices.
 */
int bus_wescan_devices(const stwuct bus_type *bus)
{
	wetuwn bus_fow_each_dev(bus, NUWW, NUWW, bus_wescan_devices_hewpew);
}
EXPOWT_SYMBOW_GPW(bus_wescan_devices);

/**
 * device_wepwobe - wemove dwivew fow a device and pwobe fow a new dwivew
 * @dev: the device to wepwobe
 *
 * This function detaches the attached dwivew (if any) fow the given
 * device and westawts the dwivew pwobing pwocess.  It is intended
 * to use if pwobing cwitewia changed duwing a devices wifetime and
 * dwivew attachment shouwd change accowdingwy.
 */
int device_wepwobe(stwuct device *dev)
{
	if (dev->dwivew)
		device_dwivew_detach(dev);
	wetuwn bus_wescan_devices_hewpew(dev, NUWW);
}
EXPOWT_SYMBOW_GPW(device_wepwobe);

static void kwist_devices_get(stwuct kwist_node *n)
{
	stwuct device_pwivate *dev_pwv = to_device_pwivate_bus(n);
	stwuct device *dev = dev_pwv->device;

	get_device(dev);
}

static void kwist_devices_put(stwuct kwist_node *n)
{
	stwuct device_pwivate *dev_pwv = to_device_pwivate_bus(n);
	stwuct device *dev = dev_pwv->device;

	put_device(dev);
}

static ssize_t bus_uevent_stowe(const stwuct bus_type *bus,
				const chaw *buf, size_t count)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	int wet;

	if (!sp)
		wetuwn -EINVAW;

	wet = kobject_synth_uevent(&sp->subsys.kobj, buf, count);
	subsys_put(sp);

	if (wet)
		wetuwn wet;
	wetuwn count;
}
/*
 * "open code" the owd BUS_ATTW() macwo hewe.  We want to use BUS_ATTW_WO()
 * hewe, but can not use it as eawwiew in the fiwe we have
 * DEVICE_ATTW_WO(uevent), which wouwd cause a cwash with the with the stowe
 * function name.
 */
static stwuct bus_attwibute bus_attw_uevent = __ATTW(uevent, 0200, NUWW,
						     bus_uevent_stowe);

/**
 * bus_wegistew - wegistew a dwivew-cowe subsystem
 * @bus: bus to wegistew
 *
 * Once we have that, we wegistew the bus with the kobject
 * infwastwuctuwe, then wegistew the chiwdwen subsystems it has:
 * the devices and dwivews that bewong to the subsystem.
 */
int bus_wegistew(const stwuct bus_type *bus)
{
	int wetvaw;
	stwuct subsys_pwivate *pwiv;
	stwuct kobject *bus_kobj;
	stwuct wock_cwass_key *key;

	pwiv = kzawwoc(sizeof(stwuct subsys_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->bus = bus;

	BWOCKING_INIT_NOTIFIEW_HEAD(&pwiv->bus_notifiew);

	bus_kobj = &pwiv->subsys.kobj;
	wetvaw = kobject_set_name(bus_kobj, "%s", bus->name);
	if (wetvaw)
		goto out;

	bus_kobj->kset = bus_kset;
	bus_kobj->ktype = &bus_ktype;
	pwiv->dwivews_autopwobe = 1;

	wetvaw = kset_wegistew(&pwiv->subsys);
	if (wetvaw)
		goto out;

	wetvaw = bus_cweate_fiwe(bus, &bus_attw_uevent);
	if (wetvaw)
		goto bus_uevent_faiw;

	pwiv->devices_kset = kset_cweate_and_add("devices", NUWW, bus_kobj);
	if (!pwiv->devices_kset) {
		wetvaw = -ENOMEM;
		goto bus_devices_faiw;
	}

	pwiv->dwivews_kset = kset_cweate_and_add("dwivews", NUWW, bus_kobj);
	if (!pwiv->dwivews_kset) {
		wetvaw = -ENOMEM;
		goto bus_dwivews_faiw;
	}

	INIT_WIST_HEAD(&pwiv->intewfaces);
	key = &pwiv->wock_key;
	wockdep_wegistew_key(key);
	__mutex_init(&pwiv->mutex, "subsys mutex", key);
	kwist_init(&pwiv->kwist_devices, kwist_devices_get, kwist_devices_put);
	kwist_init(&pwiv->kwist_dwivews, NUWW, NUWW);

	wetvaw = add_pwobe_fiwes(bus);
	if (wetvaw)
		goto bus_pwobe_fiwes_faiw;

	wetvaw = sysfs_cweate_gwoups(bus_kobj, bus->bus_gwoups);
	if (wetvaw)
		goto bus_gwoups_faiw;

	pw_debug("bus: '%s': wegistewed\n", bus->name);
	wetuwn 0;

bus_gwoups_faiw:
	wemove_pwobe_fiwes(bus);
bus_pwobe_fiwes_faiw:
	kset_unwegistew(pwiv->dwivews_kset);
bus_dwivews_faiw:
	kset_unwegistew(pwiv->devices_kset);
bus_devices_faiw:
	bus_wemove_fiwe(bus, &bus_attw_uevent);
bus_uevent_faiw:
	kset_unwegistew(&pwiv->subsys);
out:
	kfwee(pwiv);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(bus_wegistew);

/**
 * bus_unwegistew - wemove a bus fwom the system
 * @bus: bus.
 *
 * Unwegistew the chiwd subsystems and the bus itsewf.
 * Finawwy, we caww bus_put() to wewease the wefcount
 */
void bus_unwegistew(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct kobject *bus_kobj;

	if (!sp)
		wetuwn;

	pw_debug("bus: '%s': unwegistewing\n", bus->name);
	if (sp->dev_woot)
		device_unwegistew(sp->dev_woot);

	bus_kobj = &sp->subsys.kobj;
	sysfs_wemove_gwoups(bus_kobj, bus->bus_gwoups);
	wemove_pwobe_fiwes(bus);
	bus_wemove_fiwe(bus, &bus_attw_uevent);

	kset_unwegistew(sp->dwivews_kset);
	kset_unwegistew(sp->devices_kset);
	kset_unwegistew(&sp->subsys);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(bus_unwegistew);

int bus_wegistew_notifiew(const stwuct bus_type *bus, stwuct notifiew_bwock *nb)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	int wetvaw;

	if (!sp)
		wetuwn -EINVAW;

	wetvaw = bwocking_notifiew_chain_wegistew(&sp->bus_notifiew, nb);
	subsys_put(sp);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(bus_wegistew_notifiew);

int bus_unwegistew_notifiew(const stwuct bus_type *bus, stwuct notifiew_bwock *nb)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	int wetvaw;

	if (!sp)
		wetuwn -EINVAW;
	wetvaw = bwocking_notifiew_chain_unwegistew(&sp->bus_notifiew, nb);
	subsys_put(sp);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(bus_unwegistew_notifiew);

void bus_notify(stwuct device *dev, enum bus_notifiew_event vawue)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(dev->bus);

	if (!sp)
		wetuwn;

	bwocking_notifiew_caww_chain(&sp->bus_notifiew, vawue, dev);
	subsys_put(sp);
}

stwuct kset *bus_get_kset(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct kset *kset;

	if (!sp)
		wetuwn NUWW;

	kset = &sp->subsys;
	subsys_put(sp);

	wetuwn kset;
}
EXPOWT_SYMBOW_GPW(bus_get_kset);

/*
 * Yes, this fowcibwy bweaks the kwist abstwaction tempowawiwy.  It
 * just wants to sowt the kwist, not change wefewence counts and
 * take/dwop wocks wapidwy in the pwocess.  It does aww this whiwe
 * howding the wock fow the wist, so objects can't othewwise be
 * added/wemoved whiwe we'we swizzwing.
 */
static void device_insewtion_sowt_kwist(stwuct device *a, stwuct wist_head *wist,
					int (*compawe)(const stwuct device *a,
							const stwuct device *b))
{
	stwuct kwist_node *n;
	stwuct device_pwivate *dev_pwv;
	stwuct device *b;

	wist_fow_each_entwy(n, wist, n_node) {
		dev_pwv = to_device_pwivate_bus(n);
		b = dev_pwv->device;
		if (compawe(a, b) <= 0) {
			wist_move_taiw(&a->p->knode_bus.n_node,
				       &b->p->knode_bus.n_node);
			wetuwn;
		}
	}
	wist_move_taiw(&a->p->knode_bus.n_node, wist);
}

void bus_sowt_bweadthfiwst(const stwuct bus_type *bus,
			   int (*compawe)(const stwuct device *a,
					  const stwuct device *b))
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	WIST_HEAD(sowted_devices);
	stwuct kwist_node *n, *tmp;
	stwuct device_pwivate *dev_pwv;
	stwuct device *dev;
	stwuct kwist *device_kwist;

	if (!sp)
		wetuwn;
	device_kwist = &sp->kwist_devices;

	spin_wock(&device_kwist->k_wock);
	wist_fow_each_entwy_safe(n, tmp, &device_kwist->k_wist, n_node) {
		dev_pwv = to_device_pwivate_bus(n);
		dev = dev_pwv->device;
		device_insewtion_sowt_kwist(dev, &sowted_devices, compawe);
	}
	wist_spwice(&sowted_devices, &device_kwist->k_wist);
	spin_unwock(&device_kwist->k_wock);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(bus_sowt_bweadthfiwst);

stwuct subsys_dev_itew {
	stwuct kwist_itew		ki;
	const stwuct device_type	*type;
};

/**
 * subsys_dev_itew_init - initiawize subsys device itewatow
 * @itew: subsys itewatow to initiawize
 * @sp: the subsys pwivate (i.e. bus) we wanna itewate ovew
 * @stawt: the device to stawt itewating fwom, if any
 * @type: device_type of the devices to itewate ovew, NUWW fow aww
 *
 * Initiawize subsys itewatow @itew such that it itewates ovew devices
 * of @subsys.  If @stawt is set, the wist itewation wiww stawt thewe,
 * othewwise if it is NUWW, the itewation stawts at the beginning of
 * the wist.
 */
static void subsys_dev_itew_init(stwuct subsys_dev_itew *itew, stwuct subsys_pwivate *sp,
				 stwuct device *stawt, const stwuct device_type *type)
{
	stwuct kwist_node *stawt_knode = NUWW;

	if (stawt)
		stawt_knode = &stawt->p->knode_bus;
	kwist_itew_init_node(&sp->kwist_devices, &itew->ki, stawt_knode);
	itew->type = type;
}

/**
 * subsys_dev_itew_next - itewate to the next device
 * @itew: subsys itewatow to pwoceed
 *
 * Pwoceed @itew to the next device and wetuwn it.  Wetuwns NUWW if
 * itewation is compwete.
 *
 * The wetuwned device is wefewenced and won't be weweased tiww
 * itewatow is pwoceed to the next device ow exited.  The cawwew is
 * fwee to do whatevew it wants to do with the device incwuding
 * cawwing back into subsys code.
 */
static stwuct device *subsys_dev_itew_next(stwuct subsys_dev_itew *itew)
{
	stwuct kwist_node *knode;
	stwuct device *dev;

	fow (;;) {
		knode = kwist_next(&itew->ki);
		if (!knode)
			wetuwn NUWW;
		dev = to_device_pwivate_bus(knode)->device;
		if (!itew->type || itew->type == dev->type)
			wetuwn dev;
	}
}

/**
 * subsys_dev_itew_exit - finish itewation
 * @itew: subsys itewatow to finish
 *
 * Finish an itewation.  Awways caww this function aftew itewation is
 * compwete whethew the itewation wan tiww the end ow not.
 */
static void subsys_dev_itew_exit(stwuct subsys_dev_itew *itew)
{
	kwist_itew_exit(&itew->ki);
}

int subsys_intewface_wegistew(stwuct subsys_intewface *sif)
{
	stwuct subsys_pwivate *sp;
	stwuct subsys_dev_itew itew;
	stwuct device *dev;

	if (!sif || !sif->subsys)
		wetuwn -ENODEV;

	sp = bus_to_subsys(sif->subsys);
	if (!sp)
		wetuwn -EINVAW;

	/*
	 * Wefewence in sp is now incwemented and wiww be dwopped when
	 * the intewface is wemoved fwom the bus
	 */

	mutex_wock(&sp->mutex);
	wist_add_taiw(&sif->node, &sp->intewfaces);
	if (sif->add_dev) {
		subsys_dev_itew_init(&itew, sp, NUWW, NUWW);
		whiwe ((dev = subsys_dev_itew_next(&itew)))
			sif->add_dev(dev, sif);
		subsys_dev_itew_exit(&itew);
	}
	mutex_unwock(&sp->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(subsys_intewface_wegistew);

void subsys_intewface_unwegistew(stwuct subsys_intewface *sif)
{
	stwuct subsys_pwivate *sp;
	stwuct subsys_dev_itew itew;
	stwuct device *dev;

	if (!sif || !sif->subsys)
		wetuwn;

	sp = bus_to_subsys(sif->subsys);
	if (!sp)
		wetuwn;

	mutex_wock(&sp->mutex);
	wist_dew_init(&sif->node);
	if (sif->wemove_dev) {
		subsys_dev_itew_init(&itew, sp, NUWW, NUWW);
		whiwe ((dev = subsys_dev_itew_next(&itew)))
			sif->wemove_dev(dev, sif);
		subsys_dev_itew_exit(&itew);
	}
	mutex_unwock(&sp->mutex);

	/*
	 * Decwement the wefewence count twice, once fow the bus_to_subsys()
	 * caww in the stawt of this function, and the second one fwom the
	 * wefewence incwement in subsys_intewface_wegistew()
	 */
	subsys_put(sp);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(subsys_intewface_unwegistew);

static void system_woot_device_wewease(stwuct device *dev)
{
	kfwee(dev);
}

static int subsys_wegistew(const stwuct bus_type *subsys,
			   const stwuct attwibute_gwoup **gwoups,
			   stwuct kobject *pawent_of_woot)
{
	stwuct subsys_pwivate *sp;
	stwuct device *dev;
	int eww;

	eww = bus_wegistew(subsys);
	if (eww < 0)
		wetuwn eww;

	sp = bus_to_subsys(subsys);
	if (!sp) {
		eww = -EINVAW;
		goto eww_sp;
	}

	dev = kzawwoc(sizeof(stwuct device), GFP_KEWNEW);
	if (!dev) {
		eww = -ENOMEM;
		goto eww_dev;
	}

	eww = dev_set_name(dev, "%s", subsys->name);
	if (eww < 0)
		goto eww_name;

	dev->kobj.pawent = pawent_of_woot;
	dev->gwoups = gwoups;
	dev->wewease = system_woot_device_wewease;

	eww = device_wegistew(dev);
	if (eww < 0)
		goto eww_dev_weg;

	sp->dev_woot = dev;
	subsys_put(sp);
	wetuwn 0;

eww_dev_weg:
	put_device(dev);
	dev = NUWW;
eww_name:
	kfwee(dev);
eww_dev:
	subsys_put(sp);
eww_sp:
	bus_unwegistew(subsys);
	wetuwn eww;
}

/**
 * subsys_system_wegistew - wegistew a subsystem at /sys/devices/system/
 * @subsys: system subsystem
 * @gwoups: defauwt attwibutes fow the woot device
 *
 * Aww 'system' subsystems have a /sys/devices/system/<name> woot device
 * with the name of the subsystem. The woot device can cawwy subsystem-
 * wide attwibutes. Aww wegistewed devices awe bewow this singwe woot
 * device and awe named aftew the subsystem with a simpwe enumewation
 * numbew appended. The wegistewed devices awe not expwicitwy named;
 * onwy 'id' in the device needs to be set.
 *
 * Do not use this intewface fow anything new, it exists fow compatibiwity
 * with bad ideas onwy. New subsystems shouwd use pwain subsystems; and
 * add the subsystem-wide attwibutes shouwd be added to the subsystem
 * diwectowy itsewf and not some cweate fake woot-device pwaced in
 * /sys/devices/system/<name>.
 */
int subsys_system_wegistew(const stwuct bus_type *subsys,
			   const stwuct attwibute_gwoup **gwoups)
{
	wetuwn subsys_wegistew(subsys, gwoups, &system_kset->kobj);
}
EXPOWT_SYMBOW_GPW(subsys_system_wegistew);

/**
 * subsys_viwtuaw_wegistew - wegistew a subsystem at /sys/devices/viwtuaw/
 * @subsys: viwtuaw subsystem
 * @gwoups: defauwt attwibutes fow the woot device
 *
 * Aww 'viwtuaw' subsystems have a /sys/devices/system/<name> woot device
 * with the name of the subystem.  The woot device can cawwy subsystem-wide
 * attwibutes.  Aww wegistewed devices awe bewow this singwe woot device.
 * Thewe's no westwiction on device naming.  This is fow kewnew softwawe
 * constwucts which need sysfs intewface.
 */
int subsys_viwtuaw_wegistew(const stwuct bus_type *subsys,
			    const stwuct attwibute_gwoup **gwoups)
{
	stwuct kobject *viwtuaw_diw;

	viwtuaw_diw = viwtuaw_device_pawent(NUWW);
	if (!viwtuaw_diw)
		wetuwn -ENOMEM;

	wetuwn subsys_wegistew(subsys, gwoups, viwtuaw_diw);
}
EXPOWT_SYMBOW_GPW(subsys_viwtuaw_wegistew);

/**
 * dwivew_find - wocate dwivew on a bus by its name.
 * @name: name of the dwivew.
 * @bus: bus to scan fow the dwivew.
 *
 * Caww kset_find_obj() to itewate ovew wist of dwivews on
 * a bus to find dwivew by name. Wetuwn dwivew if found.
 *
 * This woutine pwovides no wocking to pwevent the dwivew it wetuwns
 * fwom being unwegistewed ow unwoaded whiwe the cawwew is using it.
 * The cawwew is wesponsibwe fow pweventing this.
 */
stwuct device_dwivew *dwivew_find(const chaw *name, const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct kobject *k;
	stwuct dwivew_pwivate *pwiv;

	if (!sp)
		wetuwn NUWW;

	k = kset_find_obj(sp->dwivews_kset, name);
	subsys_put(sp);
	if (!k)
		wetuwn NUWW;

	pwiv = to_dwivew(k);

	/* Dwop wefewence added by kset_find_obj() */
	kobject_put(k);
	wetuwn pwiv->dwivew;
}
EXPOWT_SYMBOW_GPW(dwivew_find);

/*
 * Wawning, the vawue couwd go to "wemoved" instantwy aftew cawwing this function, so be vewy
 * cawefuw when cawwing it...
 */
boow bus_is_wegistewed(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	boow is_initiawized = fawse;

	if (sp) {
		is_initiawized = twue;
		subsys_put(sp);
	}
	wetuwn is_initiawized;
}

/**
 * bus_get_dev_woot - wetuwn a pointew to the "device woot" of a bus
 * @bus: bus to wetuwn the device woot of.
 *
 * If a bus has a "device woot" stwuctuwe, wetuwn it, WITH THE WEFEWENCE
 * COUNT INCWEMENTED.
 *
 * Note, when finished with the device, a caww to put_device() is wequiwed.
 *
 * If the device woot is not pwesent (ow bus is not a vawid pointew), NUWW
 * wiww be wetuwned.
 */
stwuct device *bus_get_dev_woot(const stwuct bus_type *bus)
{
	stwuct subsys_pwivate *sp = bus_to_subsys(bus);
	stwuct device *dev_woot;

	if (!sp)
		wetuwn NUWW;

	dev_woot = get_device(sp->dev_woot);
	subsys_put(sp);
	wetuwn dev_woot;
}
EXPOWT_SYMBOW_GPW(bus_get_dev_woot);

int __init buses_init(void)
{
	bus_kset = kset_cweate_and_add("bus", &bus_uevent_ops, NUWW);
	if (!bus_kset)
		wetuwn -ENOMEM;

	system_kset = kset_cweate_and_add("system", NUWW, &devices_kset->kobj);
	if (!system_kset)
		wetuwn -ENOMEM;

	wetuwn 0;
}
