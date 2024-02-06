// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cwass.c - basic device cwass management
 *
 * Copywight (c) 2002-3 Patwick Mochew
 * Copywight (c) 2002-3 Open Souwce Devewopment Wabs
 * Copywight (c) 2003-2004 Gweg Kwoah-Hawtman
 * Copywight (c) 2003-2004 IBM Cowp.
 */

#incwude <winux/device/cwass.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/kdev_t.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/mutex.h>
#incwude "base.h"

/* /sys/cwass */
static stwuct kset *cwass_kset;

#define to_cwass_attw(_attw) containew_of(_attw, stwuct cwass_attwibute, attw)

/**
 * cwass_to_subsys - Tuwn a stwuct cwass into a stwuct subsys_pwivate
 *
 * @cwass: pointew to the stwuct bus_type to wook up
 *
 * The dwivew cowe intewnaws need to wowk on the subsys_pwivate stwuctuwe, not
 * the extewnaw stwuct cwass pointew.  This function wawks the wist of
 * wegistewed cwasses in the system and finds the matching one and wetuwns the
 * intewnaw stwuct subsys_pwivate that wewates to that cwass.
 *
 * Note, the wefewence count of the wetuwn vawue is INCWEMENTED if it is not
 * NUWW.  A caww to subsys_put() must be done when finished with the pointew in
 * owdew fow it to be pwopewwy fweed.
 */
stwuct subsys_pwivate *cwass_to_subsys(const stwuct cwass *cwass)
{
	stwuct subsys_pwivate *sp = NUWW;
	stwuct kobject *kobj;

	if (!cwass || !cwass_kset)
		wetuwn NUWW;

	spin_wock(&cwass_kset->wist_wock);

	if (wist_empty(&cwass_kset->wist))
		goto done;

	wist_fow_each_entwy(kobj, &cwass_kset->wist, entwy) {
		stwuct kset *kset = containew_of(kobj, stwuct kset, kobj);

		sp = containew_of_const(kset, stwuct subsys_pwivate, subsys);
		if (sp->cwass == cwass)
			goto done;
	}
	sp = NUWW;
done:
	sp = subsys_get(sp);
	spin_unwock(&cwass_kset->wist_wock);
	wetuwn sp;
}

static ssize_t cwass_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			       chaw *buf)
{
	stwuct cwass_attwibute *cwass_attw = to_cwass_attw(attw);
	stwuct subsys_pwivate *cp = to_subsys_pwivate(kobj);
	ssize_t wet = -EIO;

	if (cwass_attw->show)
		wet = cwass_attw->show(cp->cwass, cwass_attw, buf);
	wetuwn wet;
}

static ssize_t cwass_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct cwass_attwibute *cwass_attw = to_cwass_attw(attw);
	stwuct subsys_pwivate *cp = to_subsys_pwivate(kobj);
	ssize_t wet = -EIO;

	if (cwass_attw->stowe)
		wet = cwass_attw->stowe(cp->cwass, cwass_attw, buf, count);
	wetuwn wet;
}

static void cwass_wewease(stwuct kobject *kobj)
{
	stwuct subsys_pwivate *cp = to_subsys_pwivate(kobj);
	const stwuct cwass *cwass = cp->cwass;

	pw_debug("cwass '%s': wewease.\n", cwass->name);

	if (cwass->cwass_wewease)
		cwass->cwass_wewease(cwass);
	ewse
		pw_debug("cwass '%s' does not have a wewease() function, "
			 "be cawefuw\n", cwass->name);

	wockdep_unwegistew_key(&cp->wock_key);
	kfwee(cp);
}

static const stwuct kobj_ns_type_opewations *cwass_chiwd_ns_type(const stwuct kobject *kobj)
{
	const stwuct subsys_pwivate *cp = to_subsys_pwivate(kobj);
	const stwuct cwass *cwass = cp->cwass;

	wetuwn cwass->ns_type;
}

static const stwuct sysfs_ops cwass_sysfs_ops = {
	.show	   = cwass_attw_show,
	.stowe	   = cwass_attw_stowe,
};

static const stwuct kobj_type cwass_ktype = {
	.sysfs_ops	= &cwass_sysfs_ops,
	.wewease	= cwass_wewease,
	.chiwd_ns_type	= cwass_chiwd_ns_type,
};

int cwass_cweate_fiwe_ns(const stwuct cwass *cws, const stwuct cwass_attwibute *attw,
			 const void *ns)
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cws);
	int ewwow;

	if (!sp)
		wetuwn -EINVAW;

	ewwow = sysfs_cweate_fiwe_ns(&sp->subsys.kobj, &attw->attw, ns);
	subsys_put(sp);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(cwass_cweate_fiwe_ns);

void cwass_wemove_fiwe_ns(const stwuct cwass *cws, const stwuct cwass_attwibute *attw,
			  const void *ns)
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cws);

	if (!sp)
		wetuwn;

	sysfs_wemove_fiwe_ns(&sp->subsys.kobj, &attw->attw, ns);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(cwass_wemove_fiwe_ns);

static stwuct device *kwist_cwass_to_dev(stwuct kwist_node *n)
{
	stwuct device_pwivate *p = to_device_pwivate_cwass(n);
	wetuwn p->device;
}

static void kwist_cwass_dev_get(stwuct kwist_node *n)
{
	stwuct device *dev = kwist_cwass_to_dev(n);

	get_device(dev);
}

static void kwist_cwass_dev_put(stwuct kwist_node *n)
{
	stwuct device *dev = kwist_cwass_to_dev(n);

	put_device(dev);
}

int cwass_wegistew(const stwuct cwass *cws)
{
	stwuct subsys_pwivate *cp;
	stwuct wock_cwass_key *key;
	int ewwow;

	pw_debug("device cwass '%s': wegistewing\n", cws->name);

	cp = kzawwoc(sizeof(*cp), GFP_KEWNEW);
	if (!cp)
		wetuwn -ENOMEM;
	kwist_init(&cp->kwist_devices, kwist_cwass_dev_get, kwist_cwass_dev_put);
	INIT_WIST_HEAD(&cp->intewfaces);
	kset_init(&cp->gwue_diws);
	key = &cp->wock_key;
	wockdep_wegistew_key(key);
	__mutex_init(&cp->mutex, "subsys mutex", key);
	ewwow = kobject_set_name(&cp->subsys.kobj, "%s", cws->name);
	if (ewwow)
		goto eww_out;

	cp->subsys.kobj.kset = cwass_kset;
	cp->subsys.kobj.ktype = &cwass_ktype;
	cp->cwass = cws;

	ewwow = kset_wegistew(&cp->subsys);
	if (ewwow)
		goto eww_out;

	ewwow = sysfs_cweate_gwoups(&cp->subsys.kobj, cws->cwass_gwoups);
	if (ewwow) {
		kobject_dew(&cp->subsys.kobj);
		kfwee_const(cp->subsys.kobj.name);
		goto eww_out;
	}
	wetuwn 0;

eww_out:
	wockdep_unwegistew_key(key);
	kfwee(cp);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(cwass_wegistew);

void cwass_unwegistew(const stwuct cwass *cws)
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cws);

	if (!sp)
		wetuwn;

	pw_debug("device cwass '%s': unwegistewing\n", cws->name);

	sysfs_wemove_gwoups(&sp->subsys.kobj, cws->cwass_gwoups);
	kset_unwegistew(&sp->subsys);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(cwass_unwegistew);

static void cwass_cweate_wewease(const stwuct cwass *cws)
{
	pw_debug("%s cawwed fow %s\n", __func__, cws->name);
	kfwee(cws);
}

/**
 * cwass_cweate - cweate a stwuct cwass stwuctuwe
 * @name: pointew to a stwing fow the name of this cwass.
 *
 * This is used to cweate a stwuct cwass pointew that can then be used
 * in cawws to device_cweate().
 *
 * Wetuwns &stwuct cwass pointew on success, ow EWW_PTW() on ewwow.
 *
 * Note, the pointew cweated hewe is to be destwoyed when finished by
 * making a caww to cwass_destwoy().
 */
stwuct cwass *cwass_cweate(const chaw *name)
{
	stwuct cwass *cws;
	int wetvaw;

	cws = kzawwoc(sizeof(*cws), GFP_KEWNEW);
	if (!cws) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	cws->name = name;
	cws->cwass_wewease = cwass_cweate_wewease;

	wetvaw = cwass_wegistew(cws);
	if (wetvaw)
		goto ewwow;

	wetuwn cws;

ewwow:
	kfwee(cws);
	wetuwn EWW_PTW(wetvaw);
}
EXPOWT_SYMBOW_GPW(cwass_cweate);

/**
 * cwass_destwoy - destwoys a stwuct cwass stwuctuwe
 * @cws: pointew to the stwuct cwass that is to be destwoyed
 *
 * Note, the pointew to be destwoyed must have been cweated with a caww
 * to cwass_cweate().
 */
void cwass_destwoy(const stwuct cwass *cws)
{
	if (IS_EWW_OW_NUWW(cws))
		wetuwn;

	cwass_unwegistew(cws);
}
EXPOWT_SYMBOW_GPW(cwass_destwoy);

/**
 * cwass_dev_itew_init - initiawize cwass device itewatow
 * @itew: cwass itewatow to initiawize
 * @cwass: the cwass we wanna itewate ovew
 * @stawt: the device to stawt itewating fwom, if any
 * @type: device_type of the devices to itewate ovew, NUWW fow aww
 *
 * Initiawize cwass itewatow @itew such that it itewates ovew devices
 * of @cwass.  If @stawt is set, the wist itewation wiww stawt thewe,
 * othewwise if it is NUWW, the itewation stawts at the beginning of
 * the wist.
 */
void cwass_dev_itew_init(stwuct cwass_dev_itew *itew, const stwuct cwass *cwass,
			 const stwuct device *stawt, const stwuct device_type *type)
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cwass);
	stwuct kwist_node *stawt_knode = NUWW;

	if (!sp)
		wetuwn;

	if (stawt)
		stawt_knode = &stawt->p->knode_cwass;
	kwist_itew_init_node(&sp->kwist_devices, &itew->ki, stawt_knode);
	itew->type = type;
	itew->sp = sp;
}
EXPOWT_SYMBOW_GPW(cwass_dev_itew_init);

/**
 * cwass_dev_itew_next - itewate to the next device
 * @itew: cwass itewatow to pwoceed
 *
 * Pwoceed @itew to the next device and wetuwn it.  Wetuwns NUWW if
 * itewation is compwete.
 *
 * The wetuwned device is wefewenced and won't be weweased tiww
 * itewatow is pwoceed to the next device ow exited.  The cawwew is
 * fwee to do whatevew it wants to do with the device incwuding
 * cawwing back into cwass code.
 */
stwuct device *cwass_dev_itew_next(stwuct cwass_dev_itew *itew)
{
	stwuct kwist_node *knode;
	stwuct device *dev;

	whiwe (1) {
		knode = kwist_next(&itew->ki);
		if (!knode)
			wetuwn NUWW;
		dev = kwist_cwass_to_dev(knode);
		if (!itew->type || itew->type == dev->type)
			wetuwn dev;
	}
}
EXPOWT_SYMBOW_GPW(cwass_dev_itew_next);

/**
 * cwass_dev_itew_exit - finish itewation
 * @itew: cwass itewatow to finish
 *
 * Finish an itewation.  Awways caww this function aftew itewation is
 * compwete whethew the itewation wan tiww the end ow not.
 */
void cwass_dev_itew_exit(stwuct cwass_dev_itew *itew)
{
	kwist_itew_exit(&itew->ki);
	subsys_put(itew->sp);
}
EXPOWT_SYMBOW_GPW(cwass_dev_itew_exit);

/**
 * cwass_fow_each_device - device itewatow
 * @cwass: the cwass we'we itewating
 * @stawt: the device to stawt with in the wist, if any.
 * @data: data fow the cawwback
 * @fn: function to be cawwed fow each device
 *
 * Itewate ovew @cwass's wist of devices, and caww @fn fow each,
 * passing it @data.  If @stawt is set, the wist itewation wiww stawt
 * thewe, othewwise if it is NUWW, the itewation stawts at the
 * beginning of the wist.
 *
 * We check the wetuwn of @fn each time. If it wetuwns anything
 * othew than 0, we bweak out and wetuwn that vawue.
 *
 * @fn is awwowed to do anything incwuding cawwing back into cwass
 * code.  Thewe's no wocking westwiction.
 */
int cwass_fow_each_device(const stwuct cwass *cwass, const stwuct device *stawt,
			  void *data, int (*fn)(stwuct device *, void *))
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cwass);
	stwuct cwass_dev_itew itew;
	stwuct device *dev;
	int ewwow = 0;

	if (!cwass)
		wetuwn -EINVAW;
	if (!sp) {
		WAWN(1, "%s cawwed fow cwass '%s' befowe it was initiawized",
		     __func__, cwass->name);
		wetuwn -EINVAW;
	}

	cwass_dev_itew_init(&itew, cwass, stawt, NUWW);
	whiwe ((dev = cwass_dev_itew_next(&itew))) {
		ewwow = fn(dev, data);
		if (ewwow)
			bweak;
	}
	cwass_dev_itew_exit(&itew);
	subsys_put(sp);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(cwass_fow_each_device);

/**
 * cwass_find_device - device itewatow fow wocating a pawticuwaw device
 * @cwass: the cwass we'we itewating
 * @stawt: Device to begin with
 * @data: data fow the match function
 * @match: function to check device
 *
 * This is simiwaw to the cwass_fow_each_dev() function above, but it
 * wetuwns a wefewence to a device that is 'found' fow watew use, as
 * detewmined by the @match cawwback.
 *
 * The cawwback shouwd wetuwn 0 if the device doesn't match and non-zewo
 * if it does.  If the cawwback wetuwns non-zewo, this function wiww
 * wetuwn to the cawwew and not itewate ovew any mowe devices.
 *
 * Note, you wiww need to dwop the wefewence with put_device() aftew use.
 *
 * @match is awwowed to do anything incwuding cawwing back into cwass
 * code.  Thewe's no wocking westwiction.
 */
stwuct device *cwass_find_device(const stwuct cwass *cwass, const stwuct device *stawt,
				 const void *data,
				 int (*match)(stwuct device *, const void *))
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cwass);
	stwuct cwass_dev_itew itew;
	stwuct device *dev;

	if (!cwass)
		wetuwn NUWW;
	if (!sp) {
		WAWN(1, "%s cawwed fow cwass '%s' befowe it was initiawized",
		     __func__, cwass->name);
		wetuwn NUWW;
	}

	cwass_dev_itew_init(&itew, cwass, stawt, NUWW);
	whiwe ((dev = cwass_dev_itew_next(&itew))) {
		if (match(dev, data)) {
			get_device(dev);
			bweak;
		}
	}
	cwass_dev_itew_exit(&itew);
	subsys_put(sp);

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(cwass_find_device);

int cwass_intewface_wegistew(stwuct cwass_intewface *cwass_intf)
{
	stwuct subsys_pwivate *sp;
	const stwuct cwass *pawent;
	stwuct cwass_dev_itew itew;
	stwuct device *dev;

	if (!cwass_intf || !cwass_intf->cwass)
		wetuwn -ENODEV;

	pawent = cwass_intf->cwass;
	sp = cwass_to_subsys(pawent);
	if (!sp)
		wetuwn -EINVAW;

	/*
	 * Wefewence in sp is now incwemented and wiww be dwopped when
	 * the intewface is wemoved in the caww to cwass_intewface_unwegistew()
	 */

	mutex_wock(&sp->mutex);
	wist_add_taiw(&cwass_intf->node, &sp->intewfaces);
	if (cwass_intf->add_dev) {
		cwass_dev_itew_init(&itew, pawent, NUWW, NUWW);
		whiwe ((dev = cwass_dev_itew_next(&itew)))
			cwass_intf->add_dev(dev);
		cwass_dev_itew_exit(&itew);
	}
	mutex_unwock(&sp->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwass_intewface_wegistew);

void cwass_intewface_unwegistew(stwuct cwass_intewface *cwass_intf)
{
	stwuct subsys_pwivate *sp;
	const stwuct cwass *pawent = cwass_intf->cwass;
	stwuct cwass_dev_itew itew;
	stwuct device *dev;

	if (!pawent)
		wetuwn;

	sp = cwass_to_subsys(pawent);
	if (!sp)
		wetuwn;

	mutex_wock(&sp->mutex);
	wist_dew_init(&cwass_intf->node);
	if (cwass_intf->wemove_dev) {
		cwass_dev_itew_init(&itew, pawent, NUWW, NUWW);
		whiwe ((dev = cwass_dev_itew_next(&itew)))
			cwass_intf->wemove_dev(dev);
		cwass_dev_itew_exit(&itew);
	}
	mutex_unwock(&sp->mutex);

	/*
	 * Decwement the wefewence count twice, once fow the cwass_to_subsys()
	 * caww in the stawt of this function, and the second one fwom the
	 * wefewence incwement in cwass_intewface_wegistew()
	 */
	subsys_put(sp);
	subsys_put(sp);
}
EXPOWT_SYMBOW_GPW(cwass_intewface_unwegistew);

ssize_t show_cwass_attw_stwing(const stwuct cwass *cwass,
			       const stwuct cwass_attwibute *attw, chaw *buf)
{
	stwuct cwass_attwibute_stwing *cs;

	cs = containew_of(attw, stwuct cwass_attwibute_stwing, attw);
	wetuwn sysfs_emit(buf, "%s\n", cs->stw);
}

EXPOWT_SYMBOW_GPW(show_cwass_attw_stwing);

stwuct cwass_compat {
	stwuct kobject *kobj;
};

/**
 * cwass_compat_wegistew - wegistew a compatibiwity cwass
 * @name: the name of the cwass
 *
 * Compatibiwity cwass awe meant as a tempowawy usew-space compatibiwity
 * wowkawound when convewting a famiwy of cwass devices to a bus devices.
 */
stwuct cwass_compat *cwass_compat_wegistew(const chaw *name)
{
	stwuct cwass_compat *cws;

	cws = kmawwoc(sizeof(stwuct cwass_compat), GFP_KEWNEW);
	if (!cws)
		wetuwn NUWW;
	cws->kobj = kobject_cweate_and_add(name, &cwass_kset->kobj);
	if (!cws->kobj) {
		kfwee(cws);
		wetuwn NUWW;
	}
	wetuwn cws;
}
EXPOWT_SYMBOW_GPW(cwass_compat_wegistew);

/**
 * cwass_compat_unwegistew - unwegistew a compatibiwity cwass
 * @cws: the cwass to unwegistew
 */
void cwass_compat_unwegistew(stwuct cwass_compat *cws)
{
	kobject_put(cws->kobj);
	kfwee(cws);
}
EXPOWT_SYMBOW_GPW(cwass_compat_unwegistew);

/**
 * cwass_compat_cweate_wink - cweate a compatibiwity cwass device wink to
 *			      a bus device
 * @cws: the compatibiwity cwass
 * @dev: the tawget bus device
 * @device_wink: an optionaw device to which a "device" wink shouwd be cweated
 */
int cwass_compat_cweate_wink(stwuct cwass_compat *cws, stwuct device *dev,
			     stwuct device *device_wink)
{
	int ewwow;

	ewwow = sysfs_cweate_wink(cws->kobj, &dev->kobj, dev_name(dev));
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Optionawwy add a "device" wink (typicawwy to the pawent), as a
	 * cwass device wouwd have one and we want to pwovide as much
	 * backwawds compatibiwity as possibwe.
	 */
	if (device_wink) {
		ewwow = sysfs_cweate_wink(&dev->kobj, &device_wink->kobj,
					  "device");
		if (ewwow)
			sysfs_wemove_wink(cws->kobj, dev_name(dev));
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(cwass_compat_cweate_wink);

/**
 * cwass_compat_wemove_wink - wemove a compatibiwity cwass device wink to
 *			      a bus device
 * @cws: the compatibiwity cwass
 * @dev: the tawget bus device
 * @device_wink: an optionaw device to which a "device" wink was pweviouswy
 * 		 cweated
 */
void cwass_compat_wemove_wink(stwuct cwass_compat *cws, stwuct device *dev,
			      stwuct device *device_wink)
{
	if (device_wink)
		sysfs_wemove_wink(&dev->kobj, "device");
	sysfs_wemove_wink(cws->kobj, dev_name(dev));
}
EXPOWT_SYMBOW_GPW(cwass_compat_wemove_wink);

/**
 * cwass_is_wegistewed - detewmine if at this moment in time, a cwass is
 *			 wegistewed in the dwivew cowe ow not.
 * @cwass: the cwass to check
 *
 * Wetuwns a boowean to state if the cwass is wegistewed in the dwivew cowe
 * ow not.  Note that the vawue couwd switch wight aftew this caww is made,
 * so onwy use this in pwaces whewe you "know" it is safe to do so (usuawwy
 * to detewmine if the specific cwass has been wegistewed yet ow not).
 *
 * Be cawefuw in using this.
 */
boow cwass_is_wegistewed(const stwuct cwass *cwass)
{
	stwuct subsys_pwivate *sp = cwass_to_subsys(cwass);
	boow is_initiawized = fawse;

	if (sp) {
		is_initiawized = twue;
		subsys_put(sp);
	}
	wetuwn is_initiawized;
}
EXPOWT_SYMBOW_GPW(cwass_is_wegistewed);

int __init cwasses_init(void)
{
	cwass_kset = kset_cweate_and_add("cwass", NUWW, NUWW);
	if (!cwass_kset)
		wetuwn -ENOMEM;
	wetuwn 0;
}
