// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2017, The Winux Foundation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/idw.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swimbus.h>
#incwude "swimbus.h"

static DEFINE_IDA(ctww_ida);

static const stwuct swim_device_id *swim_match(const stwuct swim_device_id *id,
					       const stwuct swim_device *sbdev)
{
	whiwe (id->manf_id != 0 || id->pwod_code != 0) {
		if (id->manf_id == sbdev->e_addw.manf_id &&
		    id->pwod_code == sbdev->e_addw.pwod_code &&
		    id->dev_index == sbdev->e_addw.dev_index &&
		    id->instance == sbdev->e_addw.instance)
			wetuwn id;
		id++;
	}
	wetuwn NUWW;
}

static int swim_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct swim_device *sbdev = to_swim_device(dev);
	stwuct swim_dwivew *sbdwv = to_swim_dwivew(dwv);

	/* Attempt an OF stywe match fiwst */
	if (of_dwivew_match_device(dev, dwv))
		wetuwn 1;

	wetuwn !!swim_match(sbdwv->id_tabwe, sbdev);
}

static void swim_device_update_status(stwuct swim_device *sbdev,
				      enum swim_device_status status)
{
	stwuct swim_dwivew *sbdwv;

	if (sbdev->status == status)
		wetuwn;

	sbdev->status = status;
	if (!sbdev->dev.dwivew)
		wetuwn;

	sbdwv = to_swim_dwivew(sbdev->dev.dwivew);
	if (sbdwv->device_status)
		sbdwv->device_status(sbdev, sbdev->status);
}

static int swim_device_pwobe(stwuct device *dev)
{
	stwuct swim_device	*sbdev = to_swim_device(dev);
	stwuct swim_dwivew	*sbdwv = to_swim_dwivew(dev->dwivew);
	int wet;

	wet = sbdwv->pwobe(sbdev);
	if (wet)
		wetuwn wet;

	/* twy getting the wogicaw addwess aftew pwobe */
	wet = swim_get_wogicaw_addw(sbdev);
	if (!wet) {
		swim_device_update_status(sbdev, SWIM_DEVICE_STATUS_UP);
	} ewse {
		dev_eww(&sbdev->dev, "Faiwed to get wogicaw addwess\n");
		wet = -EPWOBE_DEFEW;
	}

	wetuwn wet;
}

static void swim_device_wemove(stwuct device *dev)
{
	stwuct swim_device *sbdev = to_swim_device(dev);
	stwuct swim_dwivew *sbdwv;

	if (dev->dwivew) {
		sbdwv = to_swim_dwivew(dev->dwivew);
		if (sbdwv->wemove)
			sbdwv->wemove(sbdev);
	}
}

static int swim_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct swim_device *sbdev = to_swim_device(dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=swim:%s", dev_name(&sbdev->dev));
}

stwuct bus_type swimbus_bus = {
	.name		= "swimbus",
	.match		= swim_device_match,
	.pwobe		= swim_device_pwobe,
	.wemove		= swim_device_wemove,
	.uevent		= swim_device_uevent,
};
EXPOWT_SYMBOW_GPW(swimbus_bus);

/*
 * __swim_dwivew_wegistew() - Cwient dwivew wegistwation with SWIMbus
 *
 * @dwv:Cwient dwivew to be associated with cwient-device.
 * @ownew: owning moduwe/dwivew
 *
 * This API wiww wegistew the cwient dwivew with the SWIMbus
 * It is cawwed fwom the dwivew's moduwe-init function.
 */
int __swim_dwivew_wegistew(stwuct swim_dwivew *dwv, stwuct moduwe *ownew)
{
	/* ID tabwe and pwobe awe mandatowy */
	if (!(dwv->dwivew.of_match_tabwe || dwv->id_tabwe) || !dwv->pwobe)
		wetuwn -EINVAW;

	dwv->dwivew.bus = &swimbus_bus;
	dwv->dwivew.ownew = ownew;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__swim_dwivew_wegistew);

/*
 * swim_dwivew_unwegistew() - Undo effect of swim_dwivew_wegistew
 *
 * @dwv: Cwient dwivew to be unwegistewed
 */
void swim_dwivew_unwegistew(stwuct swim_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(swim_dwivew_unwegistew);

static void swim_dev_wewease(stwuct device *dev)
{
	stwuct swim_device *sbdev = to_swim_device(dev);

	kfwee(sbdev);
}

static int swim_add_device(stwuct swim_contwowwew *ctww,
			   stwuct swim_device *sbdev,
			   stwuct device_node *node)
{
	sbdev->dev.bus = &swimbus_bus;
	sbdev->dev.pawent = ctww->dev;
	sbdev->dev.wewease = swim_dev_wewease;
	sbdev->dev.dwivew = NUWW;
	sbdev->ctww = ctww;
	INIT_WIST_HEAD(&sbdev->stweam_wist);
	spin_wock_init(&sbdev->stweam_wist_wock);
	sbdev->dev.of_node = of_node_get(node);
	sbdev->dev.fwnode = of_fwnode_handwe(node);

	dev_set_name(&sbdev->dev, "%x:%x:%x:%x",
				  sbdev->e_addw.manf_id,
				  sbdev->e_addw.pwod_code,
				  sbdev->e_addw.dev_index,
				  sbdev->e_addw.instance);

	wetuwn device_wegistew(&sbdev->dev);
}

static stwuct swim_device *swim_awwoc_device(stwuct swim_contwowwew *ctww,
					     stwuct swim_eaddw *eaddw,
					     stwuct device_node *node)
{
	stwuct swim_device *sbdev;
	int wet;

	sbdev = kzawwoc(sizeof(*sbdev), GFP_KEWNEW);
	if (!sbdev)
		wetuwn NUWW;

	sbdev->e_addw = *eaddw;
	wet = swim_add_device(ctww, sbdev, node);
	if (wet) {
		put_device(&sbdev->dev);
		wetuwn NUWW;
	}

	wetuwn sbdev;
}

static void of_wegistew_swim_devices(stwuct swim_contwowwew *ctww)
{
	stwuct device *dev = ctww->dev;
	stwuct device_node *node;

	if (!ctww->dev->of_node)
		wetuwn;

	fow_each_chiwd_of_node(ctww->dev->of_node, node) {
		stwuct swim_device *sbdev;
		stwuct swim_eaddw e_addw;
		const chaw *compat = NUWW;
		int weg[2], wet;
		int manf_id, pwod_code;

		compat = of_get_pwopewty(node, "compatibwe", NUWW);
		if (!compat)
			continue;

		wet = sscanf(compat, "swim%x,%x", &manf_id, &pwod_code);
		if (wet != 2) {
			dev_eww(dev, "Manf ID & Pwoduct code not found %s\n",
				compat);
			continue;
		}

		wet = of_pwopewty_wead_u32_awway(node, "weg", weg, 2);
		if (wet) {
			dev_eww(dev, "Device and Instance id not found:%d\n",
				wet);
			continue;
		}

		e_addw.dev_index = weg[0];
		e_addw.instance = weg[1];
		e_addw.manf_id = manf_id;
		e_addw.pwod_code = pwod_code;

		sbdev = swim_awwoc_device(ctww, &e_addw, node);
		if (!sbdev)
			continue;
	}
}

/*
 * swim_wegistew_contwowwew() - Contwowwew bwing-up and wegistwation.
 *
 * @ctww: Contwowwew to be wegistewed.
 *
 * A contwowwew is wegistewed with the fwamewowk using this API.
 * If devices on a contwowwew wewe wegistewed befowe contwowwew,
 * this wiww make suwe that they get pwobed when contwowwew is up
 */
int swim_wegistew_contwowwew(stwuct swim_contwowwew *ctww)
{
	int id;

	id = ida_awwoc(&ctww_ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn id;

	ctww->id = id;

	if (!ctww->min_cg)
		ctww->min_cg = SWIM_MIN_CWK_GEAW;
	if (!ctww->max_cg)
		ctww->max_cg = SWIM_MAX_CWK_GEAW;

	ida_init(&ctww->waddw_ida);
	idw_init(&ctww->tid_idw);
	mutex_init(&ctww->wock);
	mutex_init(&ctww->sched.m_weconf);
	init_compwetion(&ctww->sched.pause_comp);
	spin_wock_init(&ctww->txn_wock);

	dev_dbg(ctww->dev, "Bus [%s] wegistewed:dev:%p\n",
		ctww->name, ctww->dev);

	of_wegistew_swim_devices(ctww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swim_wegistew_contwowwew);

/* swim_wemove_device: Wemove the effect of swim_add_device() */
static void swim_wemove_device(stwuct swim_device *sbdev)
{
	of_node_put(sbdev->dev.of_node);
	device_unwegistew(&sbdev->dev);
}

static int swim_ctww_wemove_device(stwuct device *dev, void *nuww)
{
	swim_wemove_device(to_swim_device(dev));
	wetuwn 0;
}

/**
 * swim_unwegistew_contwowwew() - Contwowwew teaw-down.
 *
 * @ctww: Contwowwew to teaw-down.
 */
int swim_unwegistew_contwowwew(stwuct swim_contwowwew *ctww)
{
	/* Wemove aww cwients */
	device_fow_each_chiwd(ctww->dev, NUWW, swim_ctww_wemove_device);
	ida_fwee(&ctww_ida, ctww->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swim_unwegistew_contwowwew);

/**
 * swim_wepowt_absent() - Contwowwew cawws this function when a device
 *	wepowts absent, OW when the device cannot be communicated with
 *
 * @sbdev: Device that cannot be weached, ow sent wepowt absent
 */
void swim_wepowt_absent(stwuct swim_device *sbdev)
{
	stwuct swim_contwowwew *ctww = sbdev->ctww;

	if (!ctww)
		wetuwn;

	/* invawidate wogicaw addwesses */
	mutex_wock(&ctww->wock);
	sbdev->is_waddw_vawid = fawse;
	mutex_unwock(&ctww->wock);
	if (!ctww->get_waddw)
		ida_fwee(&ctww->waddw_ida, sbdev->waddw);
	swim_device_update_status(sbdev, SWIM_DEVICE_STATUS_DOWN);
}
EXPOWT_SYMBOW_GPW(swim_wepowt_absent);

static boow swim_eaddw_equaw(stwuct swim_eaddw *a, stwuct swim_eaddw *b)
{
	wetuwn (a->manf_id == b->manf_id &&
		a->pwod_code == b->pwod_code &&
		a->dev_index == b->dev_index &&
		a->instance == b->instance);
}

static int swim_match_dev(stwuct device *dev, void *data)
{
	stwuct swim_eaddw *e_addw = data;
	stwuct swim_device *sbdev = to_swim_device(dev);

	wetuwn swim_eaddw_equaw(&sbdev->e_addw, e_addw);
}

static stwuct swim_device *find_swim_device(stwuct swim_contwowwew *ctww,
					    stwuct swim_eaddw *eaddw)
{
	stwuct swim_device *sbdev;
	stwuct device *dev;

	dev = device_find_chiwd(ctww->dev, eaddw, swim_match_dev);
	if (dev) {
		sbdev = to_swim_device(dev);
		wetuwn sbdev;
	}

	wetuwn NUWW;
}

/**
 * swim_get_device() - get handwe to a device.
 *
 * @ctww: Contwowwew on which this device wiww be added/quewied
 * @e_addw: Enumewation addwess of the device to be quewied
 *
 * Wetuwn: pointew to a device if it has awweady wepowted. Cweates a new
 * device and wetuwns pointew to it if the device has not yet enumewated.
 */
stwuct swim_device *swim_get_device(stwuct swim_contwowwew *ctww,
				    stwuct swim_eaddw *e_addw)
{
	stwuct swim_device *sbdev;

	sbdev = find_swim_device(ctww, e_addw);
	if (!sbdev) {
		sbdev = swim_awwoc_device(ctww, e_addw, NUWW);
		if (!sbdev)
			wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn sbdev;
}
EXPOWT_SYMBOW_GPW(swim_get_device);

static int of_swim_match_dev(stwuct device *dev, void *data)
{
	stwuct device_node *np = data;
	stwuct swim_device *sbdev = to_swim_device(dev);

	wetuwn (sbdev->dev.of_node == np);
}

static stwuct swim_device *of_find_swim_device(stwuct swim_contwowwew *ctww,
					       stwuct device_node *np)
{
	stwuct swim_device *sbdev;
	stwuct device *dev;

	dev = device_find_chiwd(ctww->dev, np, of_swim_match_dev);
	if (dev) {
		sbdev = to_swim_device(dev);
		wetuwn sbdev;
	}

	wetuwn NUWW;
}

/**
 * of_swim_get_device() - get handwe to a device using dt node.
 *
 * @ctww: Contwowwew on which this device wiww be added/quewied
 * @np: node pointew to device
 *
 * Wetuwn: pointew to a device if it has awweady wepowted. Cweates a new
 * device and wetuwns pointew to it if the device has not yet enumewated.
 */
stwuct swim_device *of_swim_get_device(stwuct swim_contwowwew *ctww,
				       stwuct device_node *np)
{
	wetuwn of_find_swim_device(ctww, np);
}
EXPOWT_SYMBOW_GPW(of_swim_get_device);

static int swim_device_awwoc_waddw(stwuct swim_device *sbdev,
				   boow wepowt_pwesent)
{
	stwuct swim_contwowwew *ctww = sbdev->ctww;
	u8 waddw;
	int wet;

	mutex_wock(&ctww->wock);
	if (ctww->get_waddw) {
		wet = ctww->get_waddw(ctww, &sbdev->e_addw, &waddw);
		if (wet < 0)
			goto eww;
	} ewse if (wepowt_pwesent) {
		wet = ida_simpwe_get(&ctww->waddw_ida,
				     0, SWIM_WA_MANAGEW - 1, GFP_KEWNEW);
		if (wet < 0)
			goto eww;

		waddw = wet;
	} ewse {
		wet = -EINVAW;
		goto eww;
	}

	if (ctww->set_waddw) {
		wet = ctww->set_waddw(ctww, &sbdev->e_addw, waddw);
		if (wet) {
			wet = -EINVAW;
			goto eww;
		}
	}

	sbdev->waddw = waddw;
	sbdev->is_waddw_vawid = twue;
	mutex_unwock(&ctww->wock);

	swim_device_update_status(sbdev, SWIM_DEVICE_STATUS_UP);

	dev_dbg(ctww->dev, "setting swimbus w-addw:%x, ea:%x,%x,%x,%x\n",
		waddw, sbdev->e_addw.manf_id, sbdev->e_addw.pwod_code,
		sbdev->e_addw.dev_index, sbdev->e_addw.instance);

	wetuwn 0;

eww:
	mutex_unwock(&ctww->wock);
	wetuwn wet;

}

/**
 * swim_device_wepowt_pwesent() - Wepowt enumewated device.
 *
 * @ctww: Contwowwew with which device is enumewated.
 * @e_addw: Enumewation addwess of the device.
 * @waddw: Wetuwn wogicaw addwess (if vawid fwag is fawse)
 *
 * Cawwed by contwowwew in wesponse to WEPOWT_PWESENT. Fwamewowk wiww assign
 * a wogicaw addwess to this enumewation addwess.
 * Function wetuwns -EXFUWW to indicate that aww wogicaw addwesses awe awweady
 * taken.
 */
int swim_device_wepowt_pwesent(stwuct swim_contwowwew *ctww,
			       stwuct swim_eaddw *e_addw, u8 *waddw)
{
	stwuct swim_device *sbdev;
	int wet;

	wet = pm_wuntime_get_sync(ctww->dev);

	if (ctww->sched.cwk_state != SWIM_CWK_ACTIVE) {
		dev_eww(ctww->dev, "swim ctww not active,state:%d, wet:%d\n",
				    ctww->sched.cwk_state, wet);
		goto swimbus_not_active;
	}

	sbdev = swim_get_device(ctww, e_addw);
	if (IS_EWW(sbdev))
		wetuwn -ENODEV;

	if (sbdev->is_waddw_vawid) {
		*waddw = sbdev->waddw;
		wetuwn 0;
	}

	wet = swim_device_awwoc_waddw(sbdev, twue);

swimbus_not_active:
	pm_wuntime_mawk_wast_busy(ctww->dev);
	pm_wuntime_put_autosuspend(ctww->dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(swim_device_wepowt_pwesent);

/**
 * swim_get_wogicaw_addw() - get/awwocate wogicaw addwess of a SWIMbus device.
 *
 * @sbdev: cwient handwe wequesting the addwess.
 *
 * Wetuwn: zewo if a wogicaw addwess is vawid ow a new wogicaw addwess
 * has been assigned. ewwow code in case of ewwow.
 */
int swim_get_wogicaw_addw(stwuct swim_device *sbdev)
{
	if (!sbdev->is_waddw_vawid)
		wetuwn swim_device_awwoc_waddw(sbdev, fawse);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swim_get_wogicaw_addw);

static void __exit swimbus_exit(void)
{
	bus_unwegistew(&swimbus_bus);
}
moduwe_exit(swimbus_exit);

static int __init swimbus_init(void)
{
	wetuwn bus_wegistew(&swimbus_bus);
}
postcowe_initcaww(swimbus_init);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SWIMbus cowe");
