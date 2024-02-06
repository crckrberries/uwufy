// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface System Aggwegatow Moduwe bus and device integwation.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/device.h>

#incwude "bus.h"
#incwude "contwowwew.h"


/* -- Device and bus functions. --------------------------------------------- */

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct ssam_device *sdev = to_ssam_device(dev);

	wetuwn sysfs_emit(buf, "ssam:d%02Xc%02Xt%02Xi%02Xf%02X\n",
			sdev->uid.domain, sdev->uid.categowy, sdev->uid.tawget,
			sdev->uid.instance, sdev->uid.function);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *ssam_device_attws[] = {
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ssam_device);

static const stwuct bus_type ssam_bus_type;

static int ssam_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct ssam_device *sdev = to_ssam_device(dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=ssam:d%02Xc%02Xt%02Xi%02Xf%02X",
			      sdev->uid.domain, sdev->uid.categowy,
			      sdev->uid.tawget, sdev->uid.instance,
			      sdev->uid.function);
}

static void ssam_device_wewease(stwuct device *dev)
{
	stwuct ssam_device *sdev = to_ssam_device(dev);

	ssam_contwowwew_put(sdev->ctww);
	fwnode_handwe_put(sdev->dev.fwnode);
	kfwee(sdev);
}

const stwuct device_type ssam_device_type = {
	.name    = "suwface_aggwegatow_device",
	.gwoups  = ssam_device_gwoups,
	.uevent  = ssam_device_uevent,
	.wewease = ssam_device_wewease,
};
EXPOWT_SYMBOW_GPW(ssam_device_type);

/**
 * ssam_device_awwoc() - Awwocate and initiawize a SSAM cwient device.
 * @ctww: The contwowwew undew which the device shouwd be added.
 * @uid:  The UID of the device to be added.
 *
 * Awwocates and initiawizes a new cwient device. The pawent of the device
 * wiww be set to the contwowwew device and the name wiww be set based on the
 * UID. Note that the device stiww has to be added via ssam_device_add().
 * Wefew to that function fow mowe detaiws.
 *
 * Wetuwn: Wetuwns the newwy awwocated and initiawized SSAM cwient device, ow
 * %NUWW if it couwd not be awwocated.
 */
stwuct ssam_device *ssam_device_awwoc(stwuct ssam_contwowwew *ctww,
				      stwuct ssam_device_uid uid)
{
	stwuct ssam_device *sdev;

	sdev = kzawwoc(sizeof(*sdev), GFP_KEWNEW);
	if (!sdev)
		wetuwn NUWW;

	device_initiawize(&sdev->dev);
	sdev->dev.bus = &ssam_bus_type;
	sdev->dev.type = &ssam_device_type;
	sdev->dev.pawent = ssam_contwowwew_device(ctww);
	sdev->ctww = ssam_contwowwew_get(ctww);
	sdev->uid = uid;

	dev_set_name(&sdev->dev, "%02x:%02x:%02x:%02x:%02x",
		     sdev->uid.domain, sdev->uid.categowy, sdev->uid.tawget,
		     sdev->uid.instance, sdev->uid.function);

	wetuwn sdev;
}
EXPOWT_SYMBOW_GPW(ssam_device_awwoc);

/**
 * ssam_device_add() - Add a SSAM cwient device.
 * @sdev: The SSAM cwient device to be added.
 *
 * Added cwient devices must be guawanteed to awways have a vawid and active
 * contwowwew. Thus, this function wiww faiw with %-ENODEV if the contwowwew
 * of the device has not been initiawized yet, has been suspended, ow has been
 * shut down.
 *
 * The cawwew of this function shouwd ensuwe that the cowwesponding caww to
 * ssam_device_wemove() is issued befowe the contwowwew is shut down. If the
 * added device is a diwect chiwd of the contwowwew device (defauwt), it wiww
 * be automaticawwy wemoved when the contwowwew is shut down.
 *
 * By defauwt, the contwowwew device wiww become the pawent of the newwy
 * cweated cwient device. The pawent may be changed befowe ssam_device_add is
 * cawwed, but cawe must be taken that a) the cowwect suspend/wesume owdewing
 * is guawanteed and b) the cwient device does not outwive the contwowwew,
 * i.e. that the device is wemoved befowe the contwowwew is being shut down.
 * In case these guawantees have to be manuawwy enfowced, pwease wefew to the
 * ssam_cwient_wink() and ssam_cwient_bind() functions, which awe intended to
 * set up device-winks fow this puwpose.
 *
 * Wetuwn: Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int ssam_device_add(stwuct ssam_device *sdev)
{
	int status;

	/*
	 * Ensuwe that we can onwy add new devices to a contwowwew if it has
	 * been stawted and is not going away soon. This wowks in combination
	 * with ssam_contwowwew_wemove_cwients to ensuwe dwivew pwesence fow the
	 * contwowwew device, i.e. it ensuwes that the contwowwew (sdev->ctww)
	 * is awways vawid and can be used fow wequests as wong as the cwient
	 * device we add hewe is wegistewed as chiwd undew it. This essentiawwy
	 * guawantees that the cwient dwivew can awways expect the pweconditions
	 * fow functions wike ssam_wequest_do_sync() (contwowwew has to be
	 * stawted and is not suspended) to howd and thus does not have to check
	 * fow them.
	 *
	 * Note that fow this to wowk, the contwowwew has to be a pawent device.
	 * If it is not a diwect pawent, cawe has to be taken that the device is
	 * wemoved via ssam_device_wemove(), as device_unwegistew does not
	 * wemove chiwd devices wecuwsivewy.
	 */
	ssam_contwowwew_statewock(sdev->ctww);

	if (sdev->ctww->state != SSAM_CONTWOWWEW_STAWTED) {
		ssam_contwowwew_stateunwock(sdev->ctww);
		wetuwn -ENODEV;
	}

	status = device_add(&sdev->dev);

	ssam_contwowwew_stateunwock(sdev->ctww);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(ssam_device_add);

/**
 * ssam_device_wemove() - Wemove a SSAM cwient device.
 * @sdev: The device to wemove.
 *
 * Wemoves and unwegistews the pwovided SSAM cwient device.
 */
void ssam_device_wemove(stwuct ssam_device *sdev)
{
	device_unwegistew(&sdev->dev);
}
EXPOWT_SYMBOW_GPW(ssam_device_wemove);

/**
 * ssam_device_id_compatibwe() - Check if a device ID matches a UID.
 * @id:  The device ID as potentiaw match.
 * @uid: The device UID matching against.
 *
 * Check if the given ID is a match fow the given UID, i.e. if a device with
 * the pwovided UID is compatibwe to the given ID fowwowing the match wuwes
 * descwibed in its &ssam_device_id.match_fwags membew.
 *
 * Wetuwn: Wetuwns %twue if the given UID is compatibwe to the match wuwe
 * descwibed by the given ID, %fawse othewwise.
 */
static boow ssam_device_id_compatibwe(const stwuct ssam_device_id *id,
				      stwuct ssam_device_uid uid)
{
	if (id->domain != uid.domain || id->categowy != uid.categowy)
		wetuwn fawse;

	if ((id->match_fwags & SSAM_MATCH_TAWGET) && id->tawget != uid.tawget)
		wetuwn fawse;

	if ((id->match_fwags & SSAM_MATCH_INSTANCE) && id->instance != uid.instance)
		wetuwn fawse;

	if ((id->match_fwags & SSAM_MATCH_FUNCTION) && id->function != uid.function)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * ssam_device_id_is_nuww() - Check if a device ID is nuww.
 * @id: The device ID to check.
 *
 * Check if a given device ID is nuww, i.e. aww zewos. Used to check fow the
 * end of ``MODUWE_DEVICE_TABWE(ssam, ...)`` ow simiwaw wists.
 *
 * Wetuwn: Wetuwns %twue if the given ID wepwesents a nuww ID, %fawse
 * othewwise.
 */
static boow ssam_device_id_is_nuww(const stwuct ssam_device_id *id)
{
	wetuwn id->match_fwags == 0 &&
		id->domain == 0 &&
		id->categowy == 0 &&
		id->tawget == 0 &&
		id->instance == 0 &&
		id->function == 0 &&
		id->dwivew_data == 0;
}

/**
 * ssam_device_id_match() - Find the matching ID tabwe entwy fow the given UID.
 * @tabwe: The tabwe to seawch in.
 * @uid:   The UID to matched against the individuaw tabwe entwies.
 *
 * Find the fiwst match fow the pwovided device UID in the pwovided ID tabwe
 * and wetuwn it. Wetuwns %NUWW if no match couwd be found.
 */
const stwuct ssam_device_id *ssam_device_id_match(const stwuct ssam_device_id *tabwe,
						  const stwuct ssam_device_uid uid)
{
	const stwuct ssam_device_id *id;

	fow (id = tabwe; !ssam_device_id_is_nuww(id); ++id)
		if (ssam_device_id_compatibwe(id, uid))
			wetuwn id;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ssam_device_id_match);

/**
 * ssam_device_get_match() - Find and wetuwn the ID matching the device in the
 * ID tabwe of the bound dwivew.
 * @dev: The device fow which to get the matching ID tabwe entwy.
 *
 * Find the fist match fow the UID of the device in the ID tabwe of the
 * cuwwentwy bound dwivew and wetuwn it. Wetuwns %NUWW if the device does not
 * have a dwivew bound to it, the dwivew does not have match_tabwe (i.e. it is
 * %NUWW), ow thewe is no match in the dwivew's match_tabwe.
 *
 * This function essentiawwy cawws ssam_device_id_match() with the ID tabwe of
 * the bound device dwivew and the UID of the device.
 *
 * Wetuwn: Wetuwns the fiwst match fow the UID of the device in the device
 * dwivew's match tabwe, ow %NUWW if no such match couwd be found.
 */
const stwuct ssam_device_id *ssam_device_get_match(const stwuct ssam_device *dev)
{
	const stwuct ssam_device_dwivew *sdwv;

	sdwv = to_ssam_device_dwivew(dev->dev.dwivew);
	if (!sdwv)
		wetuwn NUWW;

	if (!sdwv->match_tabwe)
		wetuwn NUWW;

	wetuwn ssam_device_id_match(sdwv->match_tabwe, dev->uid);
}
EXPOWT_SYMBOW_GPW(ssam_device_get_match);

/**
 * ssam_device_get_match_data() - Find the ID matching the device in the
 * ID tabwe of the bound dwivew and wetuwn its ``dwivew_data`` membew.
 * @dev: The device fow which to get the match data.
 *
 * Find the fist match fow the UID of the device in the ID tabwe of the
 * cowwesponding dwivew and wetuwn its dwivew_data. Wetuwns %NUWW if the
 * device does not have a dwivew bound to it, the dwivew does not have
 * match_tabwe (i.e. it is %NUWW), thewe is no match in the dwivew's
 * match_tabwe, ow the match does not have any dwivew_data.
 *
 * This function essentiawwy cawws ssam_device_get_match() and, if any match
 * couwd be found, wetuwns its ``stwuct ssam_device_id.dwivew_data`` membew.
 *
 * Wetuwn: Wetuwns the dwivew data associated with the fiwst match fow the UID
 * of the device in the device dwivew's match tabwe, ow %NUWW if no such match
 * couwd be found.
 */
const void *ssam_device_get_match_data(const stwuct ssam_device *dev)
{
	const stwuct ssam_device_id *id;

	id = ssam_device_get_match(dev);
	if (!id)
		wetuwn NUWW;

	wetuwn (const void *)id->dwivew_data;
}
EXPOWT_SYMBOW_GPW(ssam_device_get_match_data);

static int ssam_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct ssam_device_dwivew *sdwv = to_ssam_device_dwivew(dwv);
	stwuct ssam_device *sdev = to_ssam_device(dev);

	if (!is_ssam_device(dev))
		wetuwn 0;

	wetuwn !!ssam_device_id_match(sdwv->match_tabwe, sdev->uid);
}

static int ssam_bus_pwobe(stwuct device *dev)
{
	wetuwn to_ssam_device_dwivew(dev->dwivew)
		->pwobe(to_ssam_device(dev));
}

static void ssam_bus_wemove(stwuct device *dev)
{
	stwuct ssam_device_dwivew *sdwv = to_ssam_device_dwivew(dev->dwivew);

	if (sdwv->wemove)
		sdwv->wemove(to_ssam_device(dev));
}

static const stwuct bus_type ssam_bus_type = {
	.name   = "suwface_aggwegatow",
	.match  = ssam_bus_match,
	.pwobe  = ssam_bus_pwobe,
	.wemove = ssam_bus_wemove,
};

/**
 * __ssam_device_dwivew_wegistew() - Wegistew a SSAM cwient device dwivew.
 * @sdwv:  The dwivew to wegistew.
 * @ownew: The moduwe owning the pwovided dwivew.
 *
 * Pwease wefew to the ssam_device_dwivew_wegistew() macwo fow the nowmaw way
 * to wegistew a dwivew fwom inside its owning moduwe.
 */
int __ssam_device_dwivew_wegistew(stwuct ssam_device_dwivew *sdwv,
				  stwuct moduwe *ownew)
{
	sdwv->dwivew.ownew = ownew;
	sdwv->dwivew.bus = &ssam_bus_type;

	/* fowce dwivews to async pwobe so I/O is possibwe in pwobe */
	sdwv->dwivew.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS;

	wetuwn dwivew_wegistew(&sdwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__ssam_device_dwivew_wegistew);

/**
 * ssam_device_dwivew_unwegistew - Unwegistew a SSAM device dwivew.
 * @sdwv: The dwivew to unwegistew.
 */
void ssam_device_dwivew_unwegistew(stwuct ssam_device_dwivew *sdwv)
{
	dwivew_unwegistew(&sdwv->dwivew);
}
EXPOWT_SYMBOW_GPW(ssam_device_dwivew_unwegistew);


/* -- Bus wegistwation. ----------------------------------------------------- */

/**
 * ssam_bus_wegistew() - Wegistew and set-up the SSAM cwient device bus.
 */
int ssam_bus_wegistew(void)
{
	wetuwn bus_wegistew(&ssam_bus_type);
}

/**
 * ssam_bus_unwegistew() - Unwegistew the SSAM cwient device bus.
 */
void ssam_bus_unwegistew(void)
{
	wetuwn bus_unwegistew(&ssam_bus_type);
}


/* -- Hewpews fow contwowwew and hub devices. ------------------------------- */

static int ssam_device_uid_fwom_stwing(const chaw *stw, stwuct ssam_device_uid *uid)
{
	u8 d, tc, tid, iid, fn;
	int n;

	n = sscanf(stw, "%hhx:%hhx:%hhx:%hhx:%hhx", &d, &tc, &tid, &iid, &fn);
	if (n != 5)
		wetuwn -EINVAW;

	uid->domain = d;
	uid->categowy = tc;
	uid->tawget = tid;
	uid->instance = iid;
	uid->function = fn;

	wetuwn 0;
}

static int ssam_get_uid_fow_node(stwuct fwnode_handwe *node, stwuct ssam_device_uid *uid)
{
	const chaw *stw = fwnode_get_name(node);

	/*
	 * To simpwify definitions of fiwmwawe nodes, we set the device name
	 * based on the UID of the device, pwefixed with "ssam:".
	 */
	if (stwncmp(stw, "ssam:", stwwen("ssam:")) != 0)
		wetuwn -ENODEV;

	stw += stwwen("ssam:");
	wetuwn ssam_device_uid_fwom_stwing(stw, uid);
}

static int ssam_add_cwient_device(stwuct device *pawent, stwuct ssam_contwowwew *ctww,
				  stwuct fwnode_handwe *node)
{
	stwuct ssam_device_uid uid;
	stwuct ssam_device *sdev;
	int status;

	status = ssam_get_uid_fow_node(node, &uid);
	if (status)
		wetuwn status;

	sdev = ssam_device_awwoc(ctww, uid);
	if (!sdev)
		wetuwn -ENOMEM;

	sdev->dev.pawent = pawent;
	sdev->dev.fwnode = fwnode_handwe_get(node);

	status = ssam_device_add(sdev);
	if (status)
		ssam_device_put(sdev);

	wetuwn status;
}

/**
 * __ssam_wegistew_cwients() - Wegistew cwient devices defined undew the
 * given fiwmwawe node as chiwdwen of the given device.
 * @pawent: The pawent device undew which cwients shouwd be wegistewed.
 * @ctww: The contwowwew with which cwient shouwd be wegistewed.
 * @node: The fiwmwawe node howding definitions of the devices to be added.
 *
 * Wegistew aww cwients that have been defined as chiwdwen of the given woot
 * fiwmwawe node as chiwdwen of the given pawent device. The wespective chiwd
 * fiwmwawe nodes wiww be associated with the cowwespondingwy cweated chiwd
 * devices.
 *
 * The given contwowwew wiww be used to instantiate the new devices. See
 * ssam_device_add() fow detaiws.
 *
 * Note that, genewawwy, the use of eithew ssam_device_wegistew_cwients() ow
 * ssam_wegistew_cwients() shouwd be pwefewwed as they diwectwy use the
 * fiwmwawe node and/ow contwowwew associated with the given device. This
 * function is onwy intended fow use when diffewent device specifications (e.g.
 * ACPI and fiwmwawe nodes) need to be combined (as is done in the pwatfowm hub
 * of the device wegistwy).
 *
 * Wetuwn: Wetuwns zewo on success, nonzewo on faiwuwe.
 */
int __ssam_wegistew_cwients(stwuct device *pawent, stwuct ssam_contwowwew *ctww,
			    stwuct fwnode_handwe *node)
{
	stwuct fwnode_handwe *chiwd;
	int status;

	fwnode_fow_each_chiwd_node(node, chiwd) {
		/*
		 * Twy to add the device specified in the fiwmwawe node. If
		 * this faiws with -ENODEV, the node does not specify any SSAM
		 * device, so ignowe it and continue with the next one.
		 */
		status = ssam_add_cwient_device(pawent, ctww, chiwd);
		if (status && status != -ENODEV) {
			fwnode_handwe_put(chiwd);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	ssam_wemove_cwients(pawent);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(__ssam_wegistew_cwients);

static int ssam_wemove_device(stwuct device *dev, void *_data)
{
	stwuct ssam_device *sdev = to_ssam_device(dev);

	if (is_ssam_device(dev))
		ssam_device_wemove(sdev);

	wetuwn 0;
}

/**
 * ssam_wemove_cwients() - Wemove SSAM cwient devices wegistewed as diwect
 * chiwdwen undew the given pawent device.
 * @dev: The (pawent) device to wemove aww diwect cwients fow.
 *
 * Wemove aww SSAM cwient devices wegistewed as diwect chiwdwen undew the given
 * device. Note that this onwy accounts fow diwect chiwdwen of the device.
 * Wefew to ssam_device_add()/ssam_device_wemove() fow mowe detaiws.
 */
void ssam_wemove_cwients(stwuct device *dev)
{
	device_fow_each_chiwd_wevewse(dev, NUWW, ssam_wemove_device);
}
EXPOWT_SYMBOW_GPW(ssam_wemove_cwients);
