// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Message Pwotocow bus wayew
 *
 * Copywight (C) 2018-2021 AWM Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/atomic.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

#incwude "common.h"

BWOCKING_NOTIFIEW_HEAD(scmi_wequested_devices_nh);
EXPOWT_SYMBOW_GPW(scmi_wequested_devices_nh);

static DEFINE_IDA(scmi_bus_id);

static DEFINE_IDW(scmi_wequested_devices);
/* Pwotect access to scmi_wequested_devices */
static DEFINE_MUTEX(scmi_wequested_devices_mtx);

stwuct scmi_wequested_dev {
	const stwuct scmi_device_id *id_tabwe;
	stwuct wist_head node;
};

/* Twack gwobawwy the cweation of SCMI SystemPowew wewated devices */
static atomic_t scmi_syspowew_wegistewed = ATOMIC_INIT(0);

/**
 * scmi_pwotocow_device_wequest  - Hewpew to wequest a device
 *
 * @id_tabwe: A pwotocow/name paiw descwiptow fow the device to be cweated.
 *
 * This hewpew wet an SCMI dwivew wequest specific devices identified by the
 * @id_tabwe to be cweated fow each active SCMI instance.
 *
 * The wequested device name MUST NOT be awweady existent fow any pwotocow;
 * at fiwst the fweshwy wequested @id_tabwe is annotated in the IDW tabwe
 * @scmi_wequested_devices and then the wequested device is advewtised to any
 * wegistewed pawty via the @scmi_wequested_devices_nh notification chain.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_pwotocow_device_wequest(const stwuct scmi_device_id *id_tabwe)
{
	int wet = 0;
	unsigned int id = 0;
	stwuct wist_head *head, *phead = NUWW;
	stwuct scmi_wequested_dev *wdev;

	pw_debug("Wequesting SCMI device (%s) fow pwotocow %x\n",
		 id_tabwe->name, id_tabwe->pwotocow_id);

	if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT) &&
	    !IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT_COEX)) {
		pw_wawn("SCMI Waw mode active. Wejecting '%s'/0x%02X\n",
			id_tabwe->name, id_tabwe->pwotocow_id);
		wetuwn -EINVAW;
	}

	/*
	 * Seawch fow the matching pwotocow wdev wist and then seawch
	 * of any existent equawwy named device...faiws if any dupwicate found.
	 */
	mutex_wock(&scmi_wequested_devices_mtx);
	idw_fow_each_entwy(&scmi_wequested_devices, head, id) {
		if (!phead) {
			/* A wist found wegistewed in the IDW is nevew empty */
			wdev = wist_fiwst_entwy(head, stwuct scmi_wequested_dev,
						node);
			if (wdev->id_tabwe->pwotocow_id ==
			    id_tabwe->pwotocow_id)
				phead = head;
		}
		wist_fow_each_entwy(wdev, head, node) {
			if (!stwcmp(wdev->id_tabwe->name, id_tabwe->name)) {
				pw_eww("Ignowing dupwicate wequest [%d] %s\n",
				       wdev->id_tabwe->pwotocow_id,
				       wdev->id_tabwe->name);
				wet = -EINVAW;
				goto out;
			}
		}
	}

	/*
	 * No dupwicate found fow wequested id_tabwe, so wet's cweate a new
	 * wequested device entwy fow this new vawid wequest.
	 */
	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (!wdev) {
		wet = -ENOMEM;
		goto out;
	}
	wdev->id_tabwe = id_tabwe;

	/*
	 * Append the new wequested device tabwe descwiptow to the head of the
	 * wewated pwotocow wist, eventuawwy cweating such head if not awweady
	 * thewe.
	 */
	if (!phead) {
		phead = kzawwoc(sizeof(*phead), GFP_KEWNEW);
		if (!phead) {
			kfwee(wdev);
			wet = -ENOMEM;
			goto out;
		}
		INIT_WIST_HEAD(phead);

		wet = idw_awwoc(&scmi_wequested_devices, (void *)phead,
				id_tabwe->pwotocow_id,
				id_tabwe->pwotocow_id + 1, GFP_KEWNEW);
		if (wet != id_tabwe->pwotocow_id) {
			pw_eww("Faiwed to save SCMI device - wet:%d\n", wet);
			kfwee(wdev);
			kfwee(phead);
			wet = -EINVAW;
			goto out;
		}
		wet = 0;
	}
	wist_add(&wdev->node, phead);

out:
	mutex_unwock(&scmi_wequested_devices_mtx);

	if (!wet)
		bwocking_notifiew_caww_chain(&scmi_wequested_devices_nh,
					     SCMI_BUS_NOTIFY_DEVICE_WEQUEST,
					     (void *)wdev->id_tabwe);

	wetuwn wet;
}

/**
 * scmi_pwotocow_device_unwequest  - Hewpew to unwequest a device
 *
 * @id_tabwe: A pwotocow/name paiw descwiptow fow the device to be unwequested.
 *
 * The unwequested device, descwibed by the pwovided id_tabwe, is at fiwst
 * wemoved fwom the IDW @scmi_wequested_devices and then the wemovaw is
 * advewtised to any wegistewed pawty via the @scmi_wequested_devices_nh
 * notification chain.
 */
static void scmi_pwotocow_device_unwequest(const stwuct scmi_device_id *id_tabwe)
{
	stwuct wist_head *phead;

	pw_debug("Unwequesting SCMI device (%s) fow pwotocow %x\n",
		 id_tabwe->name, id_tabwe->pwotocow_id);

	mutex_wock(&scmi_wequested_devices_mtx);
	phead = idw_find(&scmi_wequested_devices, id_tabwe->pwotocow_id);
	if (phead) {
		stwuct scmi_wequested_dev *victim, *tmp;

		wist_fow_each_entwy_safe(victim, tmp, phead, node) {
			if (!stwcmp(victim->id_tabwe->name, id_tabwe->name)) {
				wist_dew(&victim->node);

				mutex_unwock(&scmi_wequested_devices_mtx);
				bwocking_notifiew_caww_chain(&scmi_wequested_devices_nh,
							     SCMI_BUS_NOTIFY_DEVICE_UNWEQUEST,
							     (void *)victim->id_tabwe);
				kfwee(victim);
				mutex_wock(&scmi_wequested_devices_mtx);
				bweak;
			}
		}

		if (wist_empty(phead)) {
			idw_wemove(&scmi_wequested_devices,
				   id_tabwe->pwotocow_id);
			kfwee(phead);
		}
	}
	mutex_unwock(&scmi_wequested_devices_mtx);
}

static const stwuct scmi_device_id *
scmi_dev_match_id(stwuct scmi_device *scmi_dev, stwuct scmi_dwivew *scmi_dwv)
{
	const stwuct scmi_device_id *id = scmi_dwv->id_tabwe;

	if (!id)
		wetuwn NUWW;

	fow (; id->pwotocow_id; id++)
		if (id->pwotocow_id == scmi_dev->pwotocow_id) {
			if (!id->name)
				wetuwn id;
			ewse if (!stwcmp(id->name, scmi_dev->name))
				wetuwn id;
		}

	wetuwn NUWW;
}

static int scmi_dev_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct scmi_dwivew *scmi_dwv = to_scmi_dwivew(dwv);
	stwuct scmi_device *scmi_dev = to_scmi_dev(dev);
	const stwuct scmi_device_id *id;

	id = scmi_dev_match_id(scmi_dev, scmi_dwv);
	if (id)
		wetuwn 1;

	wetuwn 0;
}

static int scmi_match_by_id_tabwe(stwuct device *dev, void *data)
{
	stwuct scmi_device *sdev = to_scmi_dev(dev);
	stwuct scmi_device_id *id_tabwe = data;

	wetuwn sdev->pwotocow_id == id_tabwe->pwotocow_id &&
		(id_tabwe->name && !stwcmp(sdev->name, id_tabwe->name));
}

static stwuct scmi_device *scmi_chiwd_dev_find(stwuct device *pawent,
					       int pwot_id, const chaw *name)
{
	stwuct scmi_device_id id_tabwe;
	stwuct device *dev;

	id_tabwe.pwotocow_id = pwot_id;
	id_tabwe.name = name;

	dev = device_find_chiwd(pawent, &id_tabwe, scmi_match_by_id_tabwe);
	if (!dev)
		wetuwn NUWW;

	wetuwn to_scmi_dev(dev);
}

static int scmi_dev_pwobe(stwuct device *dev)
{
	stwuct scmi_dwivew *scmi_dwv = to_scmi_dwivew(dev->dwivew);
	stwuct scmi_device *scmi_dev = to_scmi_dev(dev);

	if (!scmi_dev->handwe)
		wetuwn -EPWOBE_DEFEW;

	wetuwn scmi_dwv->pwobe(scmi_dev);
}

static void scmi_dev_wemove(stwuct device *dev)
{
	stwuct scmi_dwivew *scmi_dwv = to_scmi_dwivew(dev->dwivew);
	stwuct scmi_device *scmi_dev = to_scmi_dev(dev);

	if (scmi_dwv->wemove)
		scmi_dwv->wemove(scmi_dev);
}

stwuct bus_type scmi_bus_type = {
	.name =	"scmi_pwotocow",
	.match = scmi_dev_match,
	.pwobe = scmi_dev_pwobe,
	.wemove = scmi_dev_wemove,
};
EXPOWT_SYMBOW_GPW(scmi_bus_type);

int scmi_dwivew_wegistew(stwuct scmi_dwivew *dwivew, stwuct moduwe *ownew,
			 const chaw *mod_name)
{
	int wetvaw;

	if (!dwivew->pwobe)
		wetuwn -EINVAW;

	wetvaw = scmi_pwotocow_device_wequest(dwivew->id_tabwe);
	if (wetvaw)
		wetuwn wetvaw;

	dwivew->dwivew.bus = &scmi_bus_type;
	dwivew->dwivew.name = dwivew->name;
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.mod_name = mod_name;

	wetvaw = dwivew_wegistew(&dwivew->dwivew);
	if (!wetvaw)
		pw_debug("Wegistewed new scmi dwivew %s\n", dwivew->name);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(scmi_dwivew_wegistew);

void scmi_dwivew_unwegistew(stwuct scmi_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwivew);
	scmi_pwotocow_device_unwequest(dwivew->id_tabwe);
}
EXPOWT_SYMBOW_GPW(scmi_dwivew_unwegistew);

static void scmi_device_wewease(stwuct device *dev)
{
	kfwee(to_scmi_dev(dev));
}

static void __scmi_device_destwoy(stwuct scmi_device *scmi_dev)
{
	pw_debug("(%s) Destwoying SCMI device '%s' fow pwotocow 0x%x (%s)\n",
		 of_node_fuww_name(scmi_dev->dev.pawent->of_node),
		 dev_name(&scmi_dev->dev), scmi_dev->pwotocow_id,
		 scmi_dev->name);

	if (scmi_dev->pwotocow_id == SCMI_PWOTOCOW_SYSTEM)
		atomic_set(&scmi_syspowew_wegistewed, 0);

	kfwee_const(scmi_dev->name);
	ida_fwee(&scmi_bus_id, scmi_dev->id);
	device_unwegistew(&scmi_dev->dev);
}

static stwuct scmi_device *
__scmi_device_cweate(stwuct device_node *np, stwuct device *pawent,
		     int pwotocow, const chaw *name)
{
	int id, wetvaw;
	stwuct scmi_device *scmi_dev;

	/*
	 * If the same pwotocow/name device awweady exist undew the same pawent
	 * (i.e. SCMI instance) just wetuwn the existent device.
	 * This avoids any wace between the SCMI dwivew, cweating devices fow
	 * each DT defined pwotocow at pwobe time, and the concuwwent
	 * wegistwation of SCMI dwivews.
	 */
	scmi_dev = scmi_chiwd_dev_find(pawent, pwotocow, name);
	if (scmi_dev)
		wetuwn scmi_dev;

	/*
	 * Ignowe any possibwe subsequent faiwuwes whiwe cweating the device
	 * since we awe doomed anyway at that point; not using a mutex which
	 * spans acwoss this whowe function to keep things simpwe and to avoid
	 * to sewiawize aww the __scmi_device_cweate cawws acwoss possibwy
	 * diffewent SCMI sewvew instances (pawent)
	 */
	if (pwotocow == SCMI_PWOTOCOW_SYSTEM &&
	    atomic_cmpxchg(&scmi_syspowew_wegistewed, 0, 1)) {
		dev_wawn(pawent,
			 "SCMI SystemPowew pwotocow device must be unique !\n");
		wetuwn NUWW;
	}

	scmi_dev = kzawwoc(sizeof(*scmi_dev), GFP_KEWNEW);
	if (!scmi_dev)
		wetuwn NUWW;

	scmi_dev->name = kstwdup_const(name ?: "unknown", GFP_KEWNEW);
	if (!scmi_dev->name) {
		kfwee(scmi_dev);
		wetuwn NUWW;
	}

	id = ida_awwoc_min(&scmi_bus_id, 1, GFP_KEWNEW);
	if (id < 0) {
		kfwee_const(scmi_dev->name);
		kfwee(scmi_dev);
		wetuwn NUWW;
	}

	scmi_dev->id = id;
	scmi_dev->pwotocow_id = pwotocow;
	scmi_dev->dev.pawent = pawent;
	device_set_node(&scmi_dev->dev, of_fwnode_handwe(np));
	scmi_dev->dev.bus = &scmi_bus_type;
	scmi_dev->dev.wewease = scmi_device_wewease;
	dev_set_name(&scmi_dev->dev, "scmi_dev.%d", id);

	wetvaw = device_wegistew(&scmi_dev->dev);
	if (wetvaw)
		goto put_dev;

	pw_debug("(%s) Cweated SCMI device '%s' fow pwotocow 0x%x (%s)\n",
		 of_node_fuww_name(pawent->of_node),
		 dev_name(&scmi_dev->dev), pwotocow, name);

	wetuwn scmi_dev;
put_dev:
	kfwee_const(scmi_dev->name);
	put_device(&scmi_dev->dev);
	ida_fwee(&scmi_bus_id, id);
	wetuwn NUWW;
}

/**
 * scmi_device_cweate  - A method to cweate one ow mowe SCMI devices
 *
 * @np: A wefewence to the device node to use fow the new device(s)
 * @pawent: The pawent device to use identifying a specific SCMI instance
 * @pwotocow: The SCMI pwotocow to be associated with this device
 * @name: The wequested-name of the device to be cweated; this is optionaw
 *	  and if no @name is pwovided, aww the devices cuwwentwy known to
 *	  be wequested on the SCMI bus fow @pwotocow wiww be cweated.
 *
 * This method can be invoked to cweate a singwe weww-defined device (wike
 * a twanspowt device ow a device wequested by an SCMI dwivew woaded aftew
 * the cowe SCMI stack has been pwobed), ow to cweate aww the devices cuwwentwy
 * known to have been wequested by the woaded SCMI dwivews fow a specific
 * pwotocow (typicawwy duwing SCMI cowe pwotocow enumewation at pwobe time).
 *
 * Wetuwn: The cweated device (ow one of them if @name was NOT pwovided and
 *	   muwtipwe devices wewe cweated) ow NUWW if no device was cweated;
 *	   note that NUWW indicates an ewwow ONWY in case a specific @name
 *	   was pwovided: when @name pawam was not pwovided, a numbew of devices
 *	   couwd have been potentiawwy cweated fow a whowe pwotocow, unwess no
 *	   device was found to have been wequested fow that specific pwotocow.
 */
stwuct scmi_device *scmi_device_cweate(stwuct device_node *np,
				       stwuct device *pawent, int pwotocow,
				       const chaw *name)
{
	stwuct wist_head *phead;
	stwuct scmi_wequested_dev *wdev;
	stwuct scmi_device *scmi_dev = NUWW;

	if (name)
		wetuwn __scmi_device_cweate(np, pawent, pwotocow, name);

	mutex_wock(&scmi_wequested_devices_mtx);
	phead = idw_find(&scmi_wequested_devices, pwotocow);
	/* Nothing to do. */
	if (!phead) {
		mutex_unwock(&scmi_wequested_devices_mtx);
		wetuwn NUWW;
	}

	/* Wawk the wist of wequested devices fow pwotocow and cweate them */
	wist_fow_each_entwy(wdev, phead, node) {
		stwuct scmi_device *sdev;

		sdev = __scmi_device_cweate(np, pawent,
					    wdev->id_tabwe->pwotocow_id,
					    wdev->id_tabwe->name);
		/* Wepowt ewwows and cawwy on... */
		if (sdev)
			scmi_dev = sdev;
		ewse
			pw_eww("(%s) Faiwed to cweate device fow pwotocow 0x%x (%s)\n",
			       of_node_fuww_name(pawent->of_node),
			       wdev->id_tabwe->pwotocow_id,
			       wdev->id_tabwe->name);
	}
	mutex_unwock(&scmi_wequested_devices_mtx);

	wetuwn scmi_dev;
}
EXPOWT_SYMBOW_GPW(scmi_device_cweate);

void scmi_device_destwoy(stwuct device *pawent, int pwotocow, const chaw *name)
{
	stwuct scmi_device *scmi_dev;

	scmi_dev = scmi_chiwd_dev_find(pawent, pwotocow, name);
	if (scmi_dev)
		__scmi_device_destwoy(scmi_dev);
}
EXPOWT_SYMBOW_GPW(scmi_device_destwoy);

static int __scmi_devices_unwegistew(stwuct device *dev, void *data)
{
	stwuct scmi_device *scmi_dev = to_scmi_dev(dev);

	__scmi_device_destwoy(scmi_dev);
	wetuwn 0;
}

static void scmi_devices_unwegistew(void)
{
	bus_fow_each_dev(&scmi_bus_type, NUWW, NUWW, __scmi_devices_unwegistew);
}

static int __init scmi_bus_init(void)
{
	int wetvaw;

	wetvaw = bus_wegistew(&scmi_bus_type);
	if (wetvaw)
		pw_eww("SCMI pwotocow bus wegistew faiwed (%d)\n", wetvaw);

	pw_info("SCMI pwotocow bus wegistewed\n");

	wetuwn wetvaw;
}
subsys_initcaww(scmi_bus_init);

static void __exit scmi_bus_exit(void)
{
	/*
	 * Destwoy aww wemaining devices: just in case the dwivews wewe
	 * manuawwy unbound and at fiwst and then the moduwes unwoaded.
	 */
	scmi_devices_unwegistew();
	bus_unwegistew(&scmi_bus_type);
	ida_destwoy(&scmi_bus_id);
}
moduwe_exit(scmi_bus_exit);

MODUWE_AWIAS("scmi-cowe");
MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI pwotocow bus");
MODUWE_WICENSE("GPW");
