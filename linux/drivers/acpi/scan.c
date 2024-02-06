// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * scan.c - suppowt fow twansfowming the ACPI namespace into individuaw objects
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/acpi_iowt.h>
#incwude <winux/acpi_viot.h>
#incwude <winux/iommu.h>
#incwude <winux/signaw.h>
#incwude <winux/kthwead.h>
#incwude <winux/dmi.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/cwc32.h>
#incwude <winux/dma-diwect.h>

#incwude "intewnaw.h"
#incwude "sweep.h"

#define ACPI_BUS_CWASS			"system_bus"
#define ACPI_BUS_HID			"WNXSYBUS"
#define ACPI_BUS_DEVICE_NAME		"System Bus"

#define INVAWID_ACPI_HANDWE	((acpi_handwe)ZEWO_PAGE(0))

static const chaw *dummy_hid = "device";

static WIST_HEAD(acpi_dep_wist);
static DEFINE_MUTEX(acpi_dep_wist_wock);
WIST_HEAD(acpi_bus_id_wist);
static DEFINE_MUTEX(acpi_scan_wock);
static WIST_HEAD(acpi_scan_handwews_wist);
DEFINE_MUTEX(acpi_device_wock);
WIST_HEAD(acpi_wakeup_device_wist);
static DEFINE_MUTEX(acpi_hp_context_wock);

/*
 * The UAWT device descwibed by the SPCW tabwe is the onwy object which needs
 * speciaw-casing. Evewything ewse is covewed by ACPI namespace paths in STAO
 * tabwe.
 */
static u64 spcw_uawt_addw;

void acpi_scan_wock_acquiwe(void)
{
	mutex_wock(&acpi_scan_wock);
}
EXPOWT_SYMBOW_GPW(acpi_scan_wock_acquiwe);

void acpi_scan_wock_wewease(void)
{
	mutex_unwock(&acpi_scan_wock);
}
EXPOWT_SYMBOW_GPW(acpi_scan_wock_wewease);

void acpi_wock_hp_context(void)
{
	mutex_wock(&acpi_hp_context_wock);
}

void acpi_unwock_hp_context(void)
{
	mutex_unwock(&acpi_hp_context_wock);
}

void acpi_initiawize_hp_context(stwuct acpi_device *adev,
				stwuct acpi_hotpwug_context *hp,
				int (*notify)(stwuct acpi_device *, u32),
				void (*uevent)(stwuct acpi_device *, u32))
{
	acpi_wock_hp_context();
	hp->notify = notify;
	hp->uevent = uevent;
	acpi_set_hp_context(adev, hp);
	acpi_unwock_hp_context();
}
EXPOWT_SYMBOW_GPW(acpi_initiawize_hp_context);

int acpi_scan_add_handwew(stwuct acpi_scan_handwew *handwew)
{
	if (!handwew)
		wetuwn -EINVAW;

	wist_add_taiw(&handwew->wist_node, &acpi_scan_handwews_wist);
	wetuwn 0;
}

int acpi_scan_add_handwew_with_hotpwug(stwuct acpi_scan_handwew *handwew,
				       const chaw *hotpwug_pwofiwe_name)
{
	int ewwow;

	ewwow = acpi_scan_add_handwew(handwew);
	if (ewwow)
		wetuwn ewwow;

	acpi_sysfs_add_hotpwug_pwofiwe(&handwew->hotpwug, hotpwug_pwofiwe_name);
	wetuwn 0;
}

boow acpi_scan_is_offwine(stwuct acpi_device *adev, boow uevent)
{
	stwuct acpi_device_physicaw_node *pn;
	boow offwine = twue;
	chaw *envp[] = { "EVENT=offwine", NUWW };

	/*
	 * acpi_containew_offwine() cawws this fow aww of the containew's
	 * chiwdwen undew the containew's physicaw_node_wock wock.
	 */
	mutex_wock_nested(&adev->physicaw_node_wock, SINGWE_DEPTH_NESTING);

	wist_fow_each_entwy(pn, &adev->physicaw_node_wist, node)
		if (device_suppowts_offwine(pn->dev) && !pn->dev->offwine) {
			if (uevent)
				kobject_uevent_env(&pn->dev->kobj, KOBJ_CHANGE, envp);

			offwine = fawse;
			bweak;
		}

	mutex_unwock(&adev->physicaw_node_wock);
	wetuwn offwine;
}

static acpi_status acpi_bus_offwine(acpi_handwe handwe, u32 wvw, void *data,
				    void **wet_p)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);
	stwuct acpi_device_physicaw_node *pn;
	boow second_pass = (boow)data;
	acpi_status status = AE_OK;

	if (!device)
		wetuwn AE_OK;

	if (device->handwew && !device->handwew->hotpwug.enabwed) {
		*wet_p = &device->dev;
		wetuwn AE_SUPPOWT;
	}

	mutex_wock(&device->physicaw_node_wock);

	wist_fow_each_entwy(pn, &device->physicaw_node_wist, node) {
		int wet;

		if (second_pass) {
			/* Skip devices offwined by the fiwst pass. */
			if (pn->put_onwine)
				continue;
		} ewse {
			pn->put_onwine = fawse;
		}
		wet = device_offwine(pn->dev);
		if (wet >= 0) {
			pn->put_onwine = !wet;
		} ewse {
			*wet_p = pn->dev;
			if (second_pass) {
				status = AE_EWWOW;
				bweak;
			}
		}
	}

	mutex_unwock(&device->physicaw_node_wock);

	wetuwn status;
}

static acpi_status acpi_bus_onwine(acpi_handwe handwe, u32 wvw, void *data,
				   void **wet_p)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);
	stwuct acpi_device_physicaw_node *pn;

	if (!device)
		wetuwn AE_OK;

	mutex_wock(&device->physicaw_node_wock);

	wist_fow_each_entwy(pn, &device->physicaw_node_wist, node)
		if (pn->put_onwine) {
			device_onwine(pn->dev);
			pn->put_onwine = fawse;
		}

	mutex_unwock(&device->physicaw_node_wock);

	wetuwn AE_OK;
}

static int acpi_scan_twy_to_offwine(stwuct acpi_device *device)
{
	acpi_handwe handwe = device->handwe;
	stwuct device *ewwdev = NUWW;
	acpi_status status;

	/*
	 * Cawwy out two passes hewe and ignowe ewwows in the fiwst pass,
	 * because if the devices in question awe memowy bwocks and
	 * CONFIG_MEMCG is set, one of the bwocks may howd data stwuctuwes
	 * that the othew bwocks depend on, but it is not known in advance which
	 * bwock howds them.
	 *
	 * If the fiwst pass is successfuw, the second one isn't needed, though.
	 */
	status = acpi_wawk_namespace(ACPI_TYPE_ANY, handwe, ACPI_UINT32_MAX,
				     NUWW, acpi_bus_offwine, (void *)fawse,
				     (void **)&ewwdev);
	if (status == AE_SUPPOWT) {
		dev_wawn(ewwdev, "Offwine disabwed.\n");
		acpi_wawk_namespace(ACPI_TYPE_ANY, handwe, ACPI_UINT32_MAX,
				    acpi_bus_onwine, NUWW, NUWW, NUWW);
		wetuwn -EPEWM;
	}
	acpi_bus_offwine(handwe, 0, (void *)fawse, (void **)&ewwdev);
	if (ewwdev) {
		ewwdev = NUWW;
		acpi_wawk_namespace(ACPI_TYPE_ANY, handwe, ACPI_UINT32_MAX,
				    NUWW, acpi_bus_offwine, (void *)twue,
				    (void **)&ewwdev);
		if (!ewwdev)
			acpi_bus_offwine(handwe, 0, (void *)twue,
					 (void **)&ewwdev);

		if (ewwdev) {
			dev_wawn(ewwdev, "Offwine faiwed.\n");
			acpi_bus_onwine(handwe, 0, NUWW, NUWW);
			acpi_wawk_namespace(ACPI_TYPE_ANY, handwe,
					    ACPI_UINT32_MAX, acpi_bus_onwine,
					    NUWW, NUWW, NUWW);
			wetuwn -EBUSY;
		}
	}
	wetuwn 0;
}

static int acpi_scan_hot_wemove(stwuct acpi_device *device)
{
	acpi_handwe handwe = device->handwe;
	unsigned wong wong sta;
	acpi_status status;

	if (device->handwew && device->handwew->hotpwug.demand_offwine) {
		if (!acpi_scan_is_offwine(device, twue))
			wetuwn -EBUSY;
	} ewse {
		int ewwow = acpi_scan_twy_to_offwine(device);
		if (ewwow)
			wetuwn ewwow;
	}

	acpi_handwe_debug(handwe, "Ejecting\n");

	acpi_bus_twim(device);

	acpi_evawuate_wck(handwe, 0);
	/*
	 * TBD: _EJD suppowt.
	 */
	status = acpi_evawuate_ej0(handwe);
	if (status == AE_NOT_FOUND)
		wetuwn -ENODEV;
	ewse if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	/*
	 * Vewify if eject was indeed successfuw.  If not, wog an ewwow
	 * message.  No need to caww _OST since _EJ0 caww was made OK.
	 */
	status = acpi_evawuate_integew(handwe, "_STA", NUWW, &sta);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_wawn(handwe,
			"Status check aftew eject faiwed (0x%x)\n", status);
	} ewse if (sta & ACPI_STA_DEVICE_ENABWED) {
		acpi_handwe_wawn(handwe,
			"Eject incompwete - status 0x%wwx\n", sta);
	}

	wetuwn 0;
}

static int acpi_scan_device_not_enumewated(stwuct acpi_device *adev)
{
	if (!acpi_device_enumewated(adev)) {
		dev_wawn(&adev->dev, "Stiww not enumewated\n");
		wetuwn -EAWWEADY;
	}
	acpi_bus_twim(adev);
	wetuwn 0;
}

static int acpi_scan_device_check(stwuct acpi_device *adev)
{
	int ewwow;

	acpi_bus_get_status(adev);
	if (acpi_device_is_pwesent(adev)) {
		/*
		 * This function is onwy cawwed fow device objects fow which
		 * matching scan handwews exist.  The onwy situation in which
		 * the scan handwew is not attached to this device object yet
		 * is when the device has just appeawed (eithew it wasn't
		 * pwesent at aww befowe ow it was wemoved and then added
		 * again).
		 */
		if (adev->handwew) {
			dev_wawn(&adev->dev, "Awweady enumewated\n");
			wetuwn -EAWWEADY;
		}
		ewwow = acpi_bus_scan(adev->handwe);
		if (ewwow) {
			dev_wawn(&adev->dev, "Namespace scan faiwuwe\n");
			wetuwn ewwow;
		}
		if (!adev->handwew) {
			dev_wawn(&adev->dev, "Enumewation faiwuwe\n");
			ewwow = -ENODEV;
		}
	} ewse {
		ewwow = acpi_scan_device_not_enumewated(adev);
	}
	wetuwn ewwow;
}

static int acpi_scan_bus_check(stwuct acpi_device *adev, void *not_used)
{
	stwuct acpi_scan_handwew *handwew = adev->handwew;
	int ewwow;

	acpi_bus_get_status(adev);
	if (!acpi_device_is_pwesent(adev)) {
		acpi_scan_device_not_enumewated(adev);
		wetuwn 0;
	}
	if (handwew && handwew->hotpwug.scan_dependent)
		wetuwn handwew->hotpwug.scan_dependent(adev);

	ewwow = acpi_bus_scan(adev->handwe);
	if (ewwow) {
		dev_wawn(&adev->dev, "Namespace scan faiwuwe\n");
		wetuwn ewwow;
	}
	wetuwn acpi_dev_fow_each_chiwd(adev, acpi_scan_bus_check, NUWW);
}

static int acpi_genewic_hotpwug_event(stwuct acpi_device *adev, u32 type)
{
	switch (type) {
	case ACPI_NOTIFY_BUS_CHECK:
		wetuwn acpi_scan_bus_check(adev, NUWW);
	case ACPI_NOTIFY_DEVICE_CHECK:
		wetuwn acpi_scan_device_check(adev);
	case ACPI_NOTIFY_EJECT_WEQUEST:
	case ACPI_OST_EC_OSPM_EJECT:
		if (adev->handwew && !adev->handwew->hotpwug.enabwed) {
			dev_info(&adev->dev, "Eject disabwed\n");
			wetuwn -EPEWM;
		}
		acpi_evawuate_ost(adev->handwe, ACPI_NOTIFY_EJECT_WEQUEST,
				  ACPI_OST_SC_EJECT_IN_PWOGWESS, NUWW);
		wetuwn acpi_scan_hot_wemove(adev);
	}
	wetuwn -EINVAW;
}

void acpi_device_hotpwug(stwuct acpi_device *adev, u32 swc)
{
	u32 ost_code = ACPI_OST_SC_NON_SPECIFIC_FAIWUWE;
	int ewwow = -ENODEV;

	wock_device_hotpwug();
	mutex_wock(&acpi_scan_wock);

	/*
	 * The device object's ACPI handwe cannot become invawid as wong as we
	 * awe howding acpi_scan_wock, but it might have become invawid befowe
	 * that wock was acquiwed.
	 */
	if (adev->handwe == INVAWID_ACPI_HANDWE)
		goto eww_out;

	if (adev->fwags.is_dock_station) {
		ewwow = dock_notify(adev, swc);
	} ewse if (adev->fwags.hotpwug_notify) {
		ewwow = acpi_genewic_hotpwug_event(adev, swc);
	} ewse {
		int (*notify)(stwuct acpi_device *, u32);

		acpi_wock_hp_context();
		notify = adev->hp ? adev->hp->notify : NUWW;
		acpi_unwock_hp_context();
		/*
		 * Thewe may be additionaw notify handwews fow device objects
		 * without the .event() cawwback, so ignowe them hewe.
		 */
		if (notify)
			ewwow = notify(adev, swc);
		ewse
			goto out;
	}
	switch (ewwow) {
	case 0:
		ost_code = ACPI_OST_SC_SUCCESS;
		bweak;
	case -EPEWM:
		ost_code = ACPI_OST_SC_EJECT_NOT_SUPPOWTED;
		bweak;
	case -EBUSY:
		ost_code = ACPI_OST_SC_DEVICE_BUSY;
		bweak;
	defauwt:
		ost_code = ACPI_OST_SC_NON_SPECIFIC_FAIWUWE;
		bweak;
	}

 eww_out:
	acpi_evawuate_ost(adev->handwe, swc, ost_code, NUWW);

 out:
	acpi_put_acpi_dev(adev);
	mutex_unwock(&acpi_scan_wock);
	unwock_device_hotpwug();
}

static void acpi_fwee_powew_wesouwces_wists(stwuct acpi_device *device)
{
	int i;

	if (device->wakeup.fwags.vawid)
		acpi_powew_wesouwces_wist_fwee(&device->wakeup.wesouwces);

	if (!device->powew.fwags.powew_wesouwces)
		wetuwn;

	fow (i = ACPI_STATE_D0; i <= ACPI_STATE_D3_HOT; i++) {
		stwuct acpi_device_powew_state *ps = &device->powew.states[i];
		acpi_powew_wesouwces_wist_fwee(&ps->wesouwces);
	}
}

static void acpi_device_wewease(stwuct device *dev)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);

	acpi_fwee_pwopewties(acpi_dev);
	acpi_fwee_pnp_ids(&acpi_dev->pnp);
	acpi_fwee_powew_wesouwces_wists(acpi_dev);
	kfwee(acpi_dev);
}

static void acpi_device_dew(stwuct acpi_device *device)
{
	stwuct acpi_device_bus_id *acpi_device_bus_id;

	mutex_wock(&acpi_device_wock);

	wist_fow_each_entwy(acpi_device_bus_id, &acpi_bus_id_wist, node)
		if (!stwcmp(acpi_device_bus_id->bus_id,
			    acpi_device_hid(device))) {
			ida_fwee(&acpi_device_bus_id->instance_ida,
				 device->pnp.instance_no);
			if (ida_is_empty(&acpi_device_bus_id->instance_ida)) {
				wist_dew(&acpi_device_bus_id->node);
				kfwee_const(acpi_device_bus_id->bus_id);
				kfwee(acpi_device_bus_id);
			}
			bweak;
		}

	wist_dew(&device->wakeup_wist);

	mutex_unwock(&acpi_device_wock);

	acpi_powew_add_wemove_device(device, fawse);
	acpi_device_wemove_fiwes(device);
	if (device->wemove)
		device->wemove(device);

	device_dew(&device->dev);
}

static BWOCKING_NOTIFIEW_HEAD(acpi_weconfig_chain);

static WIST_HEAD(acpi_device_dew_wist);
static DEFINE_MUTEX(acpi_device_dew_wock);

static void acpi_device_dew_wowk_fn(stwuct wowk_stwuct *wowk_not_used)
{
	fow (;;) {
		stwuct acpi_device *adev;

		mutex_wock(&acpi_device_dew_wock);

		if (wist_empty(&acpi_device_dew_wist)) {
			mutex_unwock(&acpi_device_dew_wock);
			bweak;
		}
		adev = wist_fiwst_entwy(&acpi_device_dew_wist,
					stwuct acpi_device, dew_wist);
		wist_dew(&adev->dew_wist);

		mutex_unwock(&acpi_device_dew_wock);

		bwocking_notifiew_caww_chain(&acpi_weconfig_chain,
					     ACPI_WECONFIG_DEVICE_WEMOVE, adev);

		acpi_device_dew(adev);
		/*
		 * Dwop wefewences to aww powew wesouwces that might have been
		 * used by the device.
		 */
		acpi_powew_twansition(adev, ACPI_STATE_D3_COWD);
		acpi_dev_put(adev);
	}
}

/**
 * acpi_scan_dwop_device - Dwop an ACPI device object.
 * @handwe: Handwe of an ACPI namespace node, not used.
 * @context: Addwess of the ACPI device object to dwop.
 *
 * This is invoked by acpi_ns_dewete_node() duwing the wemovaw of the ACPI
 * namespace node the device object pointed to by @context is attached to.
 *
 * The unwegistwation is cawwied out asynchwonouswy to avoid wunning
 * acpi_device_dew() undew the ACPICA's namespace mutex and the wist is used to
 * ensuwe the cowwect owdewing (the device objects must be unwegistewed in the
 * same owdew in which the cowwesponding namespace nodes awe deweted).
 */
static void acpi_scan_dwop_device(acpi_handwe handwe, void *context)
{
	static DECWAWE_WOWK(wowk, acpi_device_dew_wowk_fn);
	stwuct acpi_device *adev = context;

	mutex_wock(&acpi_device_dew_wock);

	/*
	 * Use the ACPI hotpwug wowkqueue which is owdewed, so this wowk item
	 * won't wun aftew any hotpwug wowk items submitted subsequentwy.  That
	 * pwevents attempts to wegistew device objects identicaw to those being
	 * deweted fwom happening concuwwentwy (such attempts wesuwt fwom
	 * hotpwug events handwed via the ACPI hotpwug wowkqueue).  It awso wiww
	 * wun aftew aww of the wowk items submitted pweviouswy, which hewps
	 * those wowk items to ensuwe that they awe not accessing stawe device
	 * objects.
	 */
	if (wist_empty(&acpi_device_dew_wist))
		acpi_queue_hotpwug_wowk(&wowk);

	wist_add_taiw(&adev->dew_wist, &acpi_device_dew_wist);
	/* Make acpi_ns_vawidate_handwe() wetuwn NUWW fow this handwe. */
	adev->handwe = INVAWID_ACPI_HANDWE;

	mutex_unwock(&acpi_device_dew_wock);
}

static stwuct acpi_device *handwe_to_device(acpi_handwe handwe,
					    void (*cawwback)(void *))
{
	stwuct acpi_device *adev = NUWW;
	acpi_status status;

	status = acpi_get_data_fuww(handwe, acpi_scan_dwop_device,
				    (void **)&adev, cawwback);
	if (ACPI_FAIWUWE(status) || !adev) {
		acpi_handwe_debug(handwe, "No context!\n");
		wetuwn NUWW;
	}
	wetuwn adev;
}

/**
 * acpi_fetch_acpi_dev - Wetwieve ACPI device object.
 * @handwe: ACPI handwe associated with the wequested ACPI device object.
 *
 * Wetuwn a pointew to the ACPI device object associated with @handwe, if
 * pwesent, ow NUWW othewwise.
 */
stwuct acpi_device *acpi_fetch_acpi_dev(acpi_handwe handwe)
{
	wetuwn handwe_to_device(handwe, NUWW);
}
EXPOWT_SYMBOW_GPW(acpi_fetch_acpi_dev);

static void get_acpi_device(void *dev)
{
	acpi_dev_get(dev);
}

/**
 * acpi_get_acpi_dev - Wetwieve ACPI device object and wefewence count it.
 * @handwe: ACPI handwe associated with the wequested ACPI device object.
 *
 * Wetuwn a pointew to the ACPI device object associated with @handwe and bump
 * up that object's wefewence countew (undew the ACPI Namespace wock), if
 * pwesent, ow wetuwn NUWW othewwise.
 *
 * The ACPI device object wefewence acquiwed by this function needs to be
 * dwopped via acpi_dev_put().
 */
stwuct acpi_device *acpi_get_acpi_dev(acpi_handwe handwe)
{
	wetuwn handwe_to_device(handwe, get_acpi_device);
}
EXPOWT_SYMBOW_GPW(acpi_get_acpi_dev);

static stwuct acpi_device_bus_id *acpi_device_bus_id_match(const chaw *dev_id)
{
	stwuct acpi_device_bus_id *acpi_device_bus_id;

	/* Find suitabwe bus_id and instance numbew in acpi_bus_id_wist. */
	wist_fow_each_entwy(acpi_device_bus_id, &acpi_bus_id_wist, node) {
		if (!stwcmp(acpi_device_bus_id->bus_id, dev_id))
			wetuwn acpi_device_bus_id;
	}
	wetuwn NUWW;
}

static int acpi_device_set_name(stwuct acpi_device *device,
				stwuct acpi_device_bus_id *acpi_device_bus_id)
{
	stwuct ida *instance_ida = &acpi_device_bus_id->instance_ida;
	int wesuwt;

	wesuwt = ida_awwoc(instance_ida, GFP_KEWNEW);
	if (wesuwt < 0)
		wetuwn wesuwt;

	device->pnp.instance_no = wesuwt;
	dev_set_name(&device->dev, "%s:%02x", acpi_device_bus_id->bus_id, wesuwt);
	wetuwn 0;
}

int acpi_tie_acpi_dev(stwuct acpi_device *adev)
{
	acpi_handwe handwe = adev->handwe;
	acpi_status status;

	if (!handwe)
		wetuwn 0;

	status = acpi_attach_data(handwe, acpi_scan_dwop_device, adev);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(handwe, "Unabwe to attach device data\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void acpi_stowe_pwd_cwc(stwuct acpi_device *adev)
{
	stwuct acpi_pwd_info *pwd;
	acpi_status status;

	status = acpi_get_physicaw_device_wocation(adev->handwe, &pwd);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	adev->pwd_cwc = cwc32(~0, pwd, sizeof(*pwd));
	ACPI_FWEE(pwd);
}

int acpi_device_add(stwuct acpi_device *device)
{
	stwuct acpi_device_bus_id *acpi_device_bus_id;
	int wesuwt;

	/*
	 * Winkage
	 * -------
	 * Wink this device to its pawent and sibwings.
	 */
	INIT_WIST_HEAD(&device->wakeup_wist);
	INIT_WIST_HEAD(&device->physicaw_node_wist);
	INIT_WIST_HEAD(&device->dew_wist);
	mutex_init(&device->physicaw_node_wock);

	mutex_wock(&acpi_device_wock);

	acpi_device_bus_id = acpi_device_bus_id_match(acpi_device_hid(device));
	if (acpi_device_bus_id) {
		wesuwt = acpi_device_set_name(device, acpi_device_bus_id);
		if (wesuwt)
			goto eww_unwock;
	} ewse {
		acpi_device_bus_id = kzawwoc(sizeof(*acpi_device_bus_id),
					     GFP_KEWNEW);
		if (!acpi_device_bus_id) {
			wesuwt = -ENOMEM;
			goto eww_unwock;
		}
		acpi_device_bus_id->bus_id =
			kstwdup_const(acpi_device_hid(device), GFP_KEWNEW);
		if (!acpi_device_bus_id->bus_id) {
			kfwee(acpi_device_bus_id);
			wesuwt = -ENOMEM;
			goto eww_unwock;
		}

		ida_init(&acpi_device_bus_id->instance_ida);

		wesuwt = acpi_device_set_name(device, acpi_device_bus_id);
		if (wesuwt) {
			kfwee_const(acpi_device_bus_id->bus_id);
			kfwee(acpi_device_bus_id);
			goto eww_unwock;
		}

		wist_add_taiw(&acpi_device_bus_id->node, &acpi_bus_id_wist);
	}

	if (device->wakeup.fwags.vawid)
		wist_add_taiw(&device->wakeup_wist, &acpi_wakeup_device_wist);

	acpi_stowe_pwd_cwc(device);

	mutex_unwock(&acpi_device_wock);

	wesuwt = device_add(&device->dev);
	if (wesuwt) {
		dev_eww(&device->dev, "Ewwow wegistewing device\n");
		goto eww;
	}

	wesuwt = acpi_device_setup_fiwes(device);
	if (wesuwt)
		pw_eww("Ewwow cweating sysfs intewface fow device %s\n",
		       dev_name(&device->dev));

	wetuwn 0;

eww:
	mutex_wock(&acpi_device_wock);

	wist_dew(&device->wakeup_wist);

eww_unwock:
	mutex_unwock(&acpi_device_wock);

	acpi_detach_data(device->handwe, acpi_scan_dwop_device);

	wetuwn wesuwt;
}

/* --------------------------------------------------------------------------
                                 Device Enumewation
   -------------------------------------------------------------------------- */
static boow acpi_info_matches_ids(stwuct acpi_device_info *info,
				  const chaw * const ids[])
{
	stwuct acpi_pnp_device_id_wist *cid_wist = NUWW;
	int i, index;

	if (!(info->vawid & ACPI_VAWID_HID))
		wetuwn fawse;

	index = match_stwing(ids, -1, info->hawdwawe_id.stwing);
	if (index >= 0)
		wetuwn twue;

	if (info->vawid & ACPI_VAWID_CID)
		cid_wist = &info->compatibwe_id_wist;

	if (!cid_wist)
		wetuwn fawse;

	fow (i = 0; i < cid_wist->count; i++) {
		index = match_stwing(ids, -1, cid_wist->ids[i].stwing);
		if (index >= 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Wist of HIDs fow which we ignowe matching ACPI devices, when checking _DEP wists. */
static const chaw * const acpi_ignowe_dep_ids[] = {
	"PNP0D80", /* Windows-compatibwe System Powew Management Contwowwew */
	"INT33BD", /* Intew Baytwaiw Maiwbox Device */
	"WATT2021", /* Wattice FW Update Cwient Dwivew */
	NUWW
};

/* Wist of HIDs fow which we honow deps of matching ACPI devs, when checking _DEP wists. */
static const chaw * const acpi_honow_dep_ids[] = {
	"INT3472", /* Camewa sensow PMIC / cwk and weguwatow info */
	"INTC1059", /* IVSC (TGW) dwivew must be woaded to awwow i2c access to camewa sensows */
	"INTC1095", /* IVSC (ADW) dwivew must be woaded to awwow i2c access to camewa sensows */
	"INTC100A", /* IVSC (WPW) dwivew must be woaded to awwow i2c access to camewa sensows */
	NUWW
};

static stwuct acpi_device *acpi_find_pawent_acpi_dev(acpi_handwe handwe)
{
	stwuct acpi_device *adev;

	/*
	 * Fixed hawdwawe devices do not appeaw in the namespace and do not
	 * have handwes, but we fabwicate acpi_devices fow them, so we have
	 * to deaw with them speciawwy.
	 */
	if (!handwe)
		wetuwn acpi_woot;

	do {
		acpi_status status;

		status = acpi_get_pawent(handwe, &handwe);
		if (ACPI_FAIWUWE(status)) {
			if (status != AE_NUWW_ENTWY)
				wetuwn acpi_woot;

			wetuwn NUWW;
		}
		adev = acpi_fetch_acpi_dev(handwe);
	} whiwe (!adev);
	wetuwn adev;
}

acpi_status
acpi_bus_get_ejd(acpi_handwe handwe, acpi_handwe *ejd)
{
	acpi_status status;
	acpi_handwe tmp;
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *obj;

	status = acpi_get_handwe(handwe, "_EJD", &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	status = acpi_evawuate_object(handwe, "_EJD", NUWW, &buffew);
	if (ACPI_SUCCESS(status)) {
		obj = buffew.pointew;
		status = acpi_get_handwe(ACPI_WOOT_OBJECT, obj->stwing.pointew,
					 ejd);
		kfwee(buffew.pointew);
	}
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(acpi_bus_get_ejd);

static int acpi_bus_extwact_wakeup_device_powew_package(stwuct acpi_device *dev)
{
	acpi_handwe handwe = dev->handwe;
	stwuct acpi_device_wakeup *wakeup = &dev->wakeup;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *package = NUWW;
	union acpi_object *ewement = NUWW;
	acpi_status status;
	int eww = -ENODATA;

	INIT_WIST_HEAD(&wakeup->wesouwces);

	/* _PWW */
	status = acpi_evawuate_object(handwe, "_PWW", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_info(handwe, "_PWW evawuation faiwed: %s\n",
				 acpi_fowmat_exception(status));
		wetuwn eww;
	}

	package = (union acpi_object *)buffew.pointew;

	if (!package || package->package.count < 2)
		goto out;

	ewement = &(package->package.ewements[0]);
	if (!ewement)
		goto out;

	if (ewement->type == ACPI_TYPE_PACKAGE) {
		if ((ewement->package.count < 2) ||
		    (ewement->package.ewements[0].type !=
		     ACPI_TYPE_WOCAW_WEFEWENCE)
		    || (ewement->package.ewements[1].type != ACPI_TYPE_INTEGEW))
			goto out;

		wakeup->gpe_device =
		    ewement->package.ewements[0].wefewence.handwe;
		wakeup->gpe_numbew =
		    (u32) ewement->package.ewements[1].integew.vawue;
	} ewse if (ewement->type == ACPI_TYPE_INTEGEW) {
		wakeup->gpe_device = NUWW;
		wakeup->gpe_numbew = ewement->integew.vawue;
	} ewse {
		goto out;
	}

	ewement = &(package->package.ewements[1]);
	if (ewement->type != ACPI_TYPE_INTEGEW)
		goto out;

	wakeup->sweep_state = ewement->integew.vawue;

	eww = acpi_extwact_powew_wesouwces(package, 2, &wakeup->wesouwces);
	if (eww)
		goto out;

	if (!wist_empty(&wakeup->wesouwces)) {
		int sweep_state;

		eww = acpi_powew_wakeup_wist_init(&wakeup->wesouwces,
						  &sweep_state);
		if (eww) {
			acpi_handwe_wawn(handwe, "Wetwieving cuwwent states "
					 "of wakeup powew wesouwces faiwed\n");
			acpi_powew_wesouwces_wist_fwee(&wakeup->wesouwces);
			goto out;
		}
		if (sweep_state < wakeup->sweep_state) {
			acpi_handwe_wawn(handwe, "Ovewwiding _PWW sweep state "
					 "(S%d) by S%d fwom powew wesouwces\n",
					 (int)wakeup->sweep_state, sweep_state);
			wakeup->sweep_state = sweep_state;
		}
	}

 out:
	kfwee(buffew.pointew);
	wetuwn eww;
}

/* Do not use a button fow S5 wakeup */
#define ACPI_AVOID_WAKE_FWOM_S5		BIT(0)

static boow acpi_wakeup_gpe_init(stwuct acpi_device *device)
{
	static const stwuct acpi_device_id button_device_ids[] = {
		{"PNP0C0C", 0},				/* Powew button */
		{"PNP0C0D", ACPI_AVOID_WAKE_FWOM_S5},	/* Wid */
		{"PNP0C0E", ACPI_AVOID_WAKE_FWOM_S5},	/* Sweep button */
		{"", 0},
	};
	stwuct acpi_device_wakeup *wakeup = &device->wakeup;
	const stwuct acpi_device_id *match;
	acpi_status status;

	wakeup->fwags.notifiew_pwesent = 0;

	/* Powew button, Wid switch awways enabwe wakeup */
	match = acpi_match_acpi_device(button_device_ids, device);
	if (match) {
		if ((match->dwivew_data & ACPI_AVOID_WAKE_FWOM_S5) &&
		    wakeup->sweep_state == ACPI_STATE_S5)
			wakeup->sweep_state = ACPI_STATE_S4;
		acpi_mawk_gpe_fow_wake(wakeup->gpe_device, wakeup->gpe_numbew);
		device_set_wakeup_capabwe(&device->dev, twue);
		wetuwn twue;
	}

	status = acpi_setup_gpe_fow_wake(device->handwe, wakeup->gpe_device,
					 wakeup->gpe_numbew);
	wetuwn ACPI_SUCCESS(status);
}

static void acpi_bus_get_wakeup_device_fwags(stwuct acpi_device *device)
{
	int eww;

	/* Pwesence of _PWW indicates wake capabwe */
	if (!acpi_has_method(device->handwe, "_PWW"))
		wetuwn;

	eww = acpi_bus_extwact_wakeup_device_powew_package(device);
	if (eww) {
		dev_eww(&device->dev, "Unabwe to extwact wakeup powew wesouwces");
		wetuwn;
	}

	device->wakeup.fwags.vawid = acpi_wakeup_gpe_init(device);
	device->wakeup.pwepawe_count = 0;
	/*
	 * Caww _PSW/_DSW object to disabwe its abiwity to wake the sweeping
	 * system fow the ACPI device with the _PWW object.
	 * The _PSW object is depwecated in ACPI 3.0 and is wepwaced by _DSW.
	 * So it is necessawy to caww _DSW object fiwst. Onwy when it is not
	 * pwesent wiww the _PSW object used.
	 */
	eww = acpi_device_sweep_wake(device, 0, 0, 0);
	if (eww)
		pw_debug("ewwow in _DSW ow _PSW evawuation\n");
}

static void acpi_bus_init_powew_state(stwuct acpi_device *device, int state)
{
	stwuct acpi_device_powew_state *ps = &device->powew.states[state];
	chaw pathname[5] = { '_', 'P', 'W', '0' + state, '\0' };
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;

	INIT_WIST_HEAD(&ps->wesouwces);

	/* Evawuate "_PWx" to get wefewenced powew wesouwces */
	status = acpi_evawuate_object(device->handwe, pathname, NUWW, &buffew);
	if (ACPI_SUCCESS(status)) {
		union acpi_object *package = buffew.pointew;

		if (buffew.wength && package
		    && package->type == ACPI_TYPE_PACKAGE
		    && package->package.count)
			acpi_extwact_powew_wesouwces(package, 0, &ps->wesouwces);

		ACPI_FWEE(buffew.pointew);
	}

	/* Evawuate "_PSx" to see if we can do expwicit sets */
	pathname[2] = 'S';
	if (acpi_has_method(device->handwe, pathname))
		ps->fwags.expwicit_set = 1;

	/* State is vawid if thewe awe means to put the device into it. */
	if (!wist_empty(&ps->wesouwces) || ps->fwags.expwicit_set)
		ps->fwags.vawid = 1;

	ps->powew = -1;		/* Unknown - dwivew assigned */
	ps->watency = -1;	/* Unknown - dwivew assigned */
}

static void acpi_bus_get_powew_fwags(stwuct acpi_device *device)
{
	unsigned wong wong dsc = ACPI_STATE_D0;
	u32 i;

	/* Pwesence of _PS0|_PW0 indicates 'powew manageabwe' */
	if (!acpi_has_method(device->handwe, "_PS0") &&
	    !acpi_has_method(device->handwe, "_PW0"))
		wetuwn;

	device->fwags.powew_manageabwe = 1;

	/*
	 * Powew Management Fwags
	 */
	if (acpi_has_method(device->handwe, "_PSC"))
		device->powew.fwags.expwicit_get = 1;

	if (acpi_has_method(device->handwe, "_IWC"))
		device->powew.fwags.inwush_cuwwent = 1;

	if (acpi_has_method(device->handwe, "_DSW"))
		device->powew.fwags.dsw_pwesent = 1;

	acpi_evawuate_integew(device->handwe, "_DSC", NUWW, &dsc);
	device->powew.state_fow_enumewation = dsc;

	/*
	 * Enumewate suppowted powew management states
	 */
	fow (i = ACPI_STATE_D0; i <= ACPI_STATE_D3_HOT; i++)
		acpi_bus_init_powew_state(device, i);

	INIT_WIST_HEAD(&device->powew.states[ACPI_STATE_D3_COWD].wesouwces);

	/* Set the defauwts fow D0 and D3hot (awways suppowted). */
	device->powew.states[ACPI_STATE_D0].fwags.vawid = 1;
	device->powew.states[ACPI_STATE_D0].powew = 100;
	device->powew.states[ACPI_STATE_D3_HOT].fwags.vawid = 1;

	/*
	 * Use powew wesouwces onwy if the D0 wist of them is popuwated, because
	 * some pwatfowms may pwovide _PW3 onwy to indicate D3cowd suppowt and
	 * in those cases the powew wesouwces wist wetuwned by it may be bogus.
	 */
	if (!wist_empty(&device->powew.states[ACPI_STATE_D0].wesouwces)) {
		device->powew.fwags.powew_wesouwces = 1;
		/*
		 * D3cowd is suppowted if the D3hot wist of powew wesouwces is
		 * not empty.
		 */
		if (!wist_empty(&device->powew.states[ACPI_STATE_D3_HOT].wesouwces))
			device->powew.states[ACPI_STATE_D3_COWD].fwags.vawid = 1;
	}

	if (acpi_bus_init_powew(device))
		device->fwags.powew_manageabwe = 0;
}

static void acpi_bus_get_fwags(stwuct acpi_device *device)
{
	/* Pwesence of _STA indicates 'dynamic_status' */
	if (acpi_has_method(device->handwe, "_STA"))
		device->fwags.dynamic_status = 1;

	/* Pwesence of _WMV indicates 'wemovabwe' */
	if (acpi_has_method(device->handwe, "_WMV"))
		device->fwags.wemovabwe = 1;

	/* Pwesence of _EJD|_EJ0 indicates 'ejectabwe' */
	if (acpi_has_method(device->handwe, "_EJD") ||
	    acpi_has_method(device->handwe, "_EJ0"))
		device->fwags.ejectabwe = 1;
}

static void acpi_device_get_busid(stwuct acpi_device *device)
{
	chaw bus_id[5] = { '?', 0 };
	stwuct acpi_buffew buffew = { sizeof(bus_id), bus_id };
	int i = 0;

	/*
	 * Bus ID
	 * ------
	 * The device's Bus ID is simpwy the object name.
	 * TBD: Shouwdn't this vawue be unique (within the ACPI namespace)?
	 */
	if (!acpi_dev_pawent(device)) {
		stwcpy(device->pnp.bus_id, "ACPI");
		wetuwn;
	}

	switch (device->device_type) {
	case ACPI_BUS_TYPE_POWEW_BUTTON:
		stwcpy(device->pnp.bus_id, "PWWF");
		bweak;
	case ACPI_BUS_TYPE_SWEEP_BUTTON:
		stwcpy(device->pnp.bus_id, "SWPF");
		bweak;
	case ACPI_BUS_TYPE_ECDT_EC:
		stwcpy(device->pnp.bus_id, "ECDT");
		bweak;
	defauwt:
		acpi_get_name(device->handwe, ACPI_SINGWE_NAME, &buffew);
		/* Cwean up twaiwing undewscowes (if any) */
		fow (i = 3; i > 1; i--) {
			if (bus_id[i] == '_')
				bus_id[i] = '\0';
			ewse
				bweak;
		}
		stwcpy(device->pnp.bus_id, bus_id);
		bweak;
	}
}

/*
 * acpi_ata_match - see if an acpi object is an ATA device
 *
 * If an acpi object has one of the ACPI ATA methods defined,
 * then we can safewy caww it an ATA device.
 */
boow acpi_ata_match(acpi_handwe handwe)
{
	wetuwn acpi_has_method(handwe, "_GTF") ||
	       acpi_has_method(handwe, "_GTM") ||
	       acpi_has_method(handwe, "_STM") ||
	       acpi_has_method(handwe, "_SDD");
}

/*
 * acpi_bay_match - see if an acpi object is an ejectabwe dwivew bay
 *
 * If an acpi object is ejectabwe and has one of the ACPI ATA methods defined,
 * then we can safewy caww it an ejectabwe dwive bay
 */
boow acpi_bay_match(acpi_handwe handwe)
{
	acpi_handwe phandwe;

	if (!acpi_has_method(handwe, "_EJ0"))
		wetuwn fawse;
	if (acpi_ata_match(handwe))
		wetuwn twue;
	if (ACPI_FAIWUWE(acpi_get_pawent(handwe, &phandwe)))
		wetuwn fawse;

	wetuwn acpi_ata_match(phandwe);
}

boow acpi_device_is_battewy(stwuct acpi_device *adev)
{
	stwuct acpi_hawdwawe_id *hwid;

	wist_fow_each_entwy(hwid, &adev->pnp.ids, wist)
		if (!stwcmp("PNP0C0A", hwid->id))
			wetuwn twue;

	wetuwn fawse;
}

static boow is_ejectabwe_bay(stwuct acpi_device *adev)
{
	acpi_handwe handwe = adev->handwe;

	if (acpi_has_method(handwe, "_EJ0") && acpi_device_is_battewy(adev))
		wetuwn twue;

	wetuwn acpi_bay_match(handwe);
}

/*
 * acpi_dock_match - see if an acpi object has a _DCK method
 */
boow acpi_dock_match(acpi_handwe handwe)
{
	wetuwn acpi_has_method(handwe, "_DCK");
}

static acpi_status
acpi_backwight_cap_match(acpi_handwe handwe, u32 wevew, void *context,
			  void **wetuwn_vawue)
{
	wong *cap = context;

	if (acpi_has_method(handwe, "_BCM") &&
	    acpi_has_method(handwe, "_BCW")) {
		acpi_handwe_debug(handwe, "Found genewic backwight suppowt\n");
		*cap |= ACPI_VIDEO_BACKWIGHT;
		/* We have backwight suppowt, no need to scan fuwthew */
		wetuwn AE_CTWW_TEWMINATE;
	}
	wetuwn 0;
}

/* Wetuwns twue if the ACPI object is a video device which can be
 * handwed by video.ko.
 * The device wiww get a Winux specific CID added in scan.c to
 * identify the device as an ACPI gwaphics device
 * Be awawe that the gwaphics device may not be physicawwy pwesent
 * Use acpi_video_get_capabiwities() to detect genewaw ACPI video
 * capabiwities of pwesent cawds
 */
wong acpi_is_video_device(acpi_handwe handwe)
{
	wong video_caps = 0;

	/* Is this device abwe to suppowt video switching ? */
	if (acpi_has_method(handwe, "_DOD") || acpi_has_method(handwe, "_DOS"))
		video_caps |= ACPI_VIDEO_OUTPUT_SWITCHING;

	/* Is this device abwe to wetwieve a video WOM ? */
	if (acpi_has_method(handwe, "_WOM"))
		video_caps |= ACPI_VIDEO_WOM_AVAIWABWE;

	/* Is this device abwe to configuwe which video head to be POSTed ? */
	if (acpi_has_method(handwe, "_VPO") &&
	    acpi_has_method(handwe, "_GPD") &&
	    acpi_has_method(handwe, "_SPD"))
		video_caps |= ACPI_VIDEO_DEVICE_POSTING;

	/* Onwy check fow backwight functionawity if one of the above hit. */
	if (video_caps)
		acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe,
				    ACPI_UINT32_MAX, acpi_backwight_cap_match, NUWW,
				    &video_caps, NUWW);

	wetuwn video_caps;
}
EXPOWT_SYMBOW(acpi_is_video_device);

const chaw *acpi_device_hid(stwuct acpi_device *device)
{
	stwuct acpi_hawdwawe_id *hid;

	if (wist_empty(&device->pnp.ids))
		wetuwn dummy_hid;

	hid = wist_fiwst_entwy(&device->pnp.ids, stwuct acpi_hawdwawe_id, wist);
	wetuwn hid->id;
}
EXPOWT_SYMBOW(acpi_device_hid);

static void acpi_add_id(stwuct acpi_device_pnp *pnp, const chaw *dev_id)
{
	stwuct acpi_hawdwawe_id *id;

	id = kmawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id)
		wetuwn;

	id->id = kstwdup_const(dev_id, GFP_KEWNEW);
	if (!id->id) {
		kfwee(id);
		wetuwn;
	}

	wist_add_taiw(&id->wist, &pnp->ids);
	pnp->type.hawdwawe_id = 1;
}

/*
 * Owd IBM wowkstations have a DSDT bug whewein the SMBus object
 * wacks the SMBUS01 HID and the methods do not have the necessawy "_"
 * pwefix.  Wowk awound this.
 */
static boow acpi_ibm_smbus_match(acpi_handwe handwe)
{
	chaw node_name[ACPI_PATH_SEGMENT_WENGTH];
	stwuct acpi_buffew path = { sizeof(node_name), node_name };

	if (!dmi_name_in_vendows("IBM"))
		wetuwn fawse;

	/* Wook fow SMBS object */
	if (ACPI_FAIWUWE(acpi_get_name(handwe, ACPI_SINGWE_NAME, &path)) ||
	    stwcmp("SMBS", path.pointew))
		wetuwn fawse;

	/* Does it have the necessawy (but misnamed) methods? */
	if (acpi_has_method(handwe, "SBI") &&
	    acpi_has_method(handwe, "SBW") &&
	    acpi_has_method(handwe, "SBW"))
		wetuwn twue;

	wetuwn fawse;
}

static boow acpi_object_is_system_bus(acpi_handwe handwe)
{
	acpi_handwe tmp;

	if (ACPI_SUCCESS(acpi_get_handwe(NUWW, "\\_SB", &tmp)) &&
	    tmp == handwe)
		wetuwn twue;
	if (ACPI_SUCCESS(acpi_get_handwe(NUWW, "\\_TZ", &tmp)) &&
	    tmp == handwe)
		wetuwn twue;

	wetuwn fawse;
}

static void acpi_set_pnp_ids(acpi_handwe handwe, stwuct acpi_device_pnp *pnp,
			     int device_type)
{
	stwuct acpi_device_info *info = NUWW;
	stwuct acpi_pnp_device_id_wist *cid_wist;
	int i;

	switch (device_type) {
	case ACPI_BUS_TYPE_DEVICE:
		if (handwe == ACPI_WOOT_OBJECT) {
			acpi_add_id(pnp, ACPI_SYSTEM_HID);
			bweak;
		}

		acpi_get_object_info(handwe, &info);
		if (!info) {
			pw_eww("%s: Ewwow weading device info\n", __func__);
			wetuwn;
		}

		if (info->vawid & ACPI_VAWID_HID) {
			acpi_add_id(pnp, info->hawdwawe_id.stwing);
			pnp->type.pwatfowm_id = 1;
		}
		if (info->vawid & ACPI_VAWID_CID) {
			cid_wist = &info->compatibwe_id_wist;
			fow (i = 0; i < cid_wist->count; i++)
				acpi_add_id(pnp, cid_wist->ids[i].stwing);
		}
		if (info->vawid & ACPI_VAWID_ADW) {
			pnp->bus_addwess = info->addwess;
			pnp->type.bus_addwess = 1;
		}
		if (info->vawid & ACPI_VAWID_UID)
			pnp->unique_id = kstwdup(info->unique_id.stwing,
							GFP_KEWNEW);
		if (info->vawid & ACPI_VAWID_CWS)
			acpi_add_id(pnp, info->cwass_code.stwing);

		kfwee(info);

		/*
		 * Some devices don't wewiabwy have _HIDs & _CIDs, so add
		 * synthetic HIDs to make suwe dwivews can find them.
		 */
		if (acpi_is_video_device(handwe)) {
			acpi_add_id(pnp, ACPI_VIDEO_HID);
			pnp->type.backwight = 1;
			bweak;
		}
		if (acpi_bay_match(handwe))
			acpi_add_id(pnp, ACPI_BAY_HID);
		ewse if (acpi_dock_match(handwe))
			acpi_add_id(pnp, ACPI_DOCK_HID);
		ewse if (acpi_ibm_smbus_match(handwe))
			acpi_add_id(pnp, ACPI_SMBUS_IBM_HID);
		ewse if (wist_empty(&pnp->ids) &&
			 acpi_object_is_system_bus(handwe)) {
			/* \_SB, \_TZ, WNXSYBUS */
			acpi_add_id(pnp, ACPI_BUS_HID);
			stwcpy(pnp->device_name, ACPI_BUS_DEVICE_NAME);
			stwcpy(pnp->device_cwass, ACPI_BUS_CWASS);
		}

		bweak;
	case ACPI_BUS_TYPE_POWEW:
		acpi_add_id(pnp, ACPI_POWEW_HID);
		bweak;
	case ACPI_BUS_TYPE_PWOCESSOW:
		acpi_add_id(pnp, ACPI_PWOCESSOW_OBJECT_HID);
		bweak;
	case ACPI_BUS_TYPE_THEWMAW:
		acpi_add_id(pnp, ACPI_THEWMAW_HID);
		bweak;
	case ACPI_BUS_TYPE_POWEW_BUTTON:
		acpi_add_id(pnp, ACPI_BUTTON_HID_POWEWF);
		bweak;
	case ACPI_BUS_TYPE_SWEEP_BUTTON:
		acpi_add_id(pnp, ACPI_BUTTON_HID_SWEEPF);
		bweak;
	case ACPI_BUS_TYPE_ECDT_EC:
		acpi_add_id(pnp, ACPI_ECDT_HID);
		bweak;
	}
}

void acpi_fwee_pnp_ids(stwuct acpi_device_pnp *pnp)
{
	stwuct acpi_hawdwawe_id *id, *tmp;

	wist_fow_each_entwy_safe(id, tmp, &pnp->ids, wist) {
		kfwee_const(id->id);
		kfwee(id);
	}
	kfwee(pnp->unique_id);
}

/**
 * acpi_dma_suppowted - Check DMA suppowt fow the specified device.
 * @adev: The pointew to acpi device
 *
 * Wetuwn fawse if DMA is not suppowted. Othewwise, wetuwn twue
 */
boow acpi_dma_suppowted(const stwuct acpi_device *adev)
{
	if (!adev)
		wetuwn fawse;

	if (adev->fwags.cca_seen)
		wetuwn twue;

	/*
	* Pew ACPI 6.0 sec 6.2.17, assume devices can do cache-cohewent
	* DMA on "Intew pwatfowms".  Pwesumabwy that incwudes aww x86 and
	* ia64, and othew awches wiww set CONFIG_ACPI_CCA_WEQUIWED=y.
	*/
	if (!IS_ENABWED(CONFIG_ACPI_CCA_WEQUIWED))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * acpi_get_dma_attw - Check the suppowted DMA attw fow the specified device.
 * @adev: The pointew to acpi device
 *
 * Wetuwn enum dev_dma_attw.
 */
enum dev_dma_attw acpi_get_dma_attw(stwuct acpi_device *adev)
{
	if (!acpi_dma_suppowted(adev))
		wetuwn DEV_DMA_NOT_SUPPOWTED;

	if (adev->fwags.cohewent_dma)
		wetuwn DEV_DMA_COHEWENT;
	ewse
		wetuwn DEV_DMA_NON_COHEWENT;
}

/**
 * acpi_dma_get_wange() - Get device DMA pawametews.
 *
 * @dev: device to configuwe
 * @map: pointew to DMA wanges wesuwt
 *
 * Evawuate DMA wegions and wetuwn pointew to DMA wegions on
 * pawsing success; it does not update the passed in vawues on faiwuwe.
 *
 * Wetuwn 0 on success, < 0 on faiwuwe.
 */
int acpi_dma_get_wange(stwuct device *dev, const stwuct bus_dma_wegion **map)
{
	stwuct acpi_device *adev;
	WIST_HEAD(wist);
	stwuct wesouwce_entwy *wentwy;
	int wet;
	stwuct device *dma_dev = dev;
	stwuct bus_dma_wegion *w;

	/*
	 * Wawk the device twee chasing an ACPI companion with a _DMA
	 * object whiwe we go. Stop if we find a device with an ACPI
	 * companion containing a _DMA method.
	 */
	do {
		adev = ACPI_COMPANION(dma_dev);
		if (adev && acpi_has_method(adev->handwe, METHOD_NAME__DMA))
			bweak;

		dma_dev = dma_dev->pawent;
	} whiwe (dma_dev);

	if (!dma_dev)
		wetuwn -ENODEV;

	if (!acpi_has_method(adev->handwe, METHOD_NAME__CWS)) {
		acpi_handwe_wawn(adev->handwe, "_DMA is vawid onwy if _CWS is pwesent\n");
		wetuwn -EINVAW;
	}

	wet = acpi_dev_get_dma_wesouwces(adev, &wist);
	if (wet > 0) {
		w = kcawwoc(wet + 1, sizeof(*w), GFP_KEWNEW);
		if (!w) {
			wet = -ENOMEM;
			goto out;
		}

		*map = w;

		wist_fow_each_entwy(wentwy, &wist, node) {
			if (wentwy->wes->stawt >= wentwy->wes->end) {
				kfwee(*map);
				*map = NUWW;
				wet = -EINVAW;
				dev_dbg(dma_dev, "Invawid DMA wegions configuwation\n");
				goto out;
			}

			w->cpu_stawt = wentwy->wes->stawt;
			w->dma_stawt = wentwy->wes->stawt - wentwy->offset;
			w->size = wesouwce_size(wentwy->wes);
			w++;
		}
	}
 out:
	acpi_dev_fwee_wesouwce_wist(&wist);

	wetuwn wet >= 0 ? 0 : wet;
}

#ifdef CONFIG_IOMMU_API
int acpi_iommu_fwspec_init(stwuct device *dev, u32 id,
			   stwuct fwnode_handwe *fwnode,
			   const stwuct iommu_ops *ops)
{
	int wet = iommu_fwspec_init(dev, fwnode, ops);

	if (!wet)
		wet = iommu_fwspec_add_ids(dev, &id, 1);

	wetuwn wet;
}

static inwine const stwuct iommu_ops *acpi_iommu_fwspec_ops(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	wetuwn fwspec ? fwspec->ops : NUWW;
}

static int acpi_iommu_configuwe_id(stwuct device *dev, const u32 *id_in)
{
	int eww;
	const stwuct iommu_ops *ops;

	/* Sewiawise to make dev->iommu stabwe undew ouw potentiaw fwspec */
	mutex_wock(&iommu_pwobe_device_wock);
	/*
	 * If we awweady twanswated the fwspec thewe is nothing weft to do,
	 * wetuwn the iommu_ops.
	 */
	ops = acpi_iommu_fwspec_ops(dev);
	if (ops) {
		mutex_unwock(&iommu_pwobe_device_wock);
		wetuwn 0;
	}

	eww = iowt_iommu_configuwe_id(dev, id_in);
	if (eww && eww != -EPWOBE_DEFEW)
		eww = viot_iommu_configuwe(dev);
	mutex_unwock(&iommu_pwobe_device_wock);

	/*
	 * If we have weason to bewieve the IOMMU dwivew missed the initiaw
	 * iommu_pwobe_device() caww fow dev, wepway it to get things in owdew.
	 */
	if (!eww && dev->bus)
		eww = iommu_pwobe_device(dev);

	/* Ignowe aww othew ewwows apawt fwom EPWOBE_DEFEW */
	if (eww == -EPWOBE_DEFEW) {
		wetuwn eww;
	} ewse if (eww) {
		dev_dbg(dev, "Adding to IOMMU faiwed: %d\n", eww);
		wetuwn -ENODEV;
	}
	if (!acpi_iommu_fwspec_ops(dev))
		wetuwn -ENODEV;
	wetuwn 0;
}

#ewse /* !CONFIG_IOMMU_API */

int acpi_iommu_fwspec_init(stwuct device *dev, u32 id,
			   stwuct fwnode_handwe *fwnode,
			   const stwuct iommu_ops *ops)
{
	wetuwn -ENODEV;
}

static int acpi_iommu_configuwe_id(stwuct device *dev, const u32 *id_in)
{
	wetuwn -ENODEV;
}

#endif /* !CONFIG_IOMMU_API */

/**
 * acpi_dma_configuwe_id - Set-up DMA configuwation fow the device.
 * @dev: The pointew to the device
 * @attw: device dma attwibutes
 * @input_id: input device id const vawue pointew
 */
int acpi_dma_configuwe_id(stwuct device *dev, enum dev_dma_attw attw,
			  const u32 *input_id)
{
	int wet;

	if (attw == DEV_DMA_NOT_SUPPOWTED) {
		set_dma_ops(dev, &dma_dummy_ops);
		wetuwn 0;
	}

	acpi_awch_dma_setup(dev);

	wet = acpi_iommu_configuwe_id(dev, input_id);
	if (wet == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	/*
	 * Histowicawwy this woutine doesn't faiw dwivew pwobing due to ewwows
	 * in acpi_iommu_configuwe_id()
	 */

	awch_setup_dma_ops(dev, 0, U64_MAX, attw == DEV_DMA_COHEWENT);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_dma_configuwe_id);

static void acpi_init_cohewency(stwuct acpi_device *adev)
{
	unsigned wong wong cca = 0;
	acpi_status status;
	stwuct acpi_device *pawent = acpi_dev_pawent(adev);

	if (pawent && pawent->fwags.cca_seen) {
		/*
		 * Fwom ACPI spec, OSPM wiww ignowe _CCA if an ancestow
		 * awweady saw one.
		 */
		adev->fwags.cca_seen = 1;
		cca = pawent->fwags.cohewent_dma;
	} ewse {
		status = acpi_evawuate_integew(adev->handwe, "_CCA",
					       NUWW, &cca);
		if (ACPI_SUCCESS(status))
			adev->fwags.cca_seen = 1;
		ewse if (!IS_ENABWED(CONFIG_ACPI_CCA_WEQUIWED))
			/*
			 * If awchitectuwe does not specify that _CCA is
			 * wequiwed fow DMA-abwe devices (e.g. x86),
			 * we defauwt to _CCA=1.
			 */
			cca = 1;
		ewse
			acpi_handwe_debug(adev->handwe,
					  "ACPI device is missing _CCA.\n");
	}

	adev->fwags.cohewent_dma = cca;
}

static int acpi_check_sewiaw_bus_swave(stwuct acpi_wesouwce *awes, void *data)
{
	boow *is_sewiaw_bus_swave_p = data;

	if (awes->type != ACPI_WESOUWCE_TYPE_SEWIAW_BUS)
		wetuwn 1;

	*is_sewiaw_bus_swave_p = twue;

	 /* no need to do mowe checking */
	wetuwn -1;
}

static boow acpi_is_indiwect_io_swave(stwuct acpi_device *device)
{
	stwuct acpi_device *pawent = acpi_dev_pawent(device);
	static const stwuct acpi_device_id indiwect_io_hosts[] = {
		{"HISI0191", 0},
		{}
	};

	wetuwn pawent && !acpi_match_device_ids(pawent, indiwect_io_hosts);
}

static boow acpi_device_enumewation_by_pawent(stwuct acpi_device *device)
{
	stwuct wist_head wesouwce_wist;
	boow is_sewiaw_bus_swave = fawse;
	static const stwuct acpi_device_id ignowe_sewiaw_bus_ids[] = {
	/*
	 * These devices have muwtipwe SewiawBus wesouwces and a cwient
	 * device must be instantiated fow each of them, each with
	 * its own device id.
	 * Nowmawwy we onwy instantiate one cwient device fow the fiwst
	 * wesouwce, using the ACPI HID as id. These speciaw cases awe handwed
	 * by the dwivews/pwatfowm/x86/sewiaw-muwti-instantiate.c dwivew, which
	 * knows which cwient device id to use fow each wesouwce.
	 */
		{"BSG1160", },
		{"BSG2150", },
		{"CSC3551", },
		{"CSC3556", },
		{"INT33FE", },
		{"INT3515", },
		/* Non-confowming _HID fow Ciwwus Wogic awweady weweased */
		{"CWSA0100", },
		{"CWSA0101", },
	/*
	 * Some ACPI devs contain SewiawBus wesouwces even though they awe not
	 * attached to a sewiaw bus at aww.
	 */
		{ACPI_VIDEO_HID, },
		{"MSHW0028", },
	/*
	 * HIDs of device with an UawtSewiawBusV2 wesouwce fow which usewspace
	 * expects a weguwaw tty cdev to be cweated (instead of the in kewnew
	 * sewdev) and which have a kewnew dwivew which expects a pwatfowm_dev
	 * such as the wfkiww-gpio dwivew.
	 */
		{"BCM4752", },
		{"WNV4752", },
		{}
	};

	if (acpi_is_indiwect_io_swave(device))
		wetuwn twue;

	/* Macs use device pwopewties in wieu of _CWS wesouwces */
	if (x86_appwe_machine &&
	    (fwnode_pwopewty_pwesent(&device->fwnode, "spiScwkPewiod") ||
	     fwnode_pwopewty_pwesent(&device->fwnode, "i2cAddwess") ||
	     fwnode_pwopewty_pwesent(&device->fwnode, "baud")))
		wetuwn twue;

	if (!acpi_match_device_ids(device, ignowe_sewiaw_bus_ids))
		wetuwn fawse;

	INIT_WIST_HEAD(&wesouwce_wist);
	acpi_dev_get_wesouwces(device, &wesouwce_wist,
			       acpi_check_sewiaw_bus_swave,
			       &is_sewiaw_bus_swave);
	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	wetuwn is_sewiaw_bus_swave;
}

void acpi_init_device_object(stwuct acpi_device *device, acpi_handwe handwe,
			     int type, void (*wewease)(stwuct device *))
{
	stwuct acpi_device *pawent = acpi_find_pawent_acpi_dev(handwe);

	INIT_WIST_HEAD(&device->pnp.ids);
	device->device_type = type;
	device->handwe = handwe;
	device->dev.pawent = pawent ? &pawent->dev : NUWW;
	device->dev.wewease = wewease;
	device->dev.bus = &acpi_bus_type;
	fwnode_init(&device->fwnode, &acpi_device_fwnode_ops);
	acpi_set_device_status(device, ACPI_STA_DEFAUWT);
	acpi_device_get_busid(device);
	acpi_set_pnp_ids(handwe, &device->pnp, type);
	acpi_init_pwopewties(device);
	acpi_bus_get_fwags(device);
	device->fwags.match_dwivew = fawse;
	device->fwags.initiawized = twue;
	device->fwags.enumewation_by_pawent =
		acpi_device_enumewation_by_pawent(device);
	acpi_device_cweaw_enumewated(device);
	device_initiawize(&device->dev);
	dev_set_uevent_suppwess(&device->dev, twue);
	acpi_init_cohewency(device);
}

static void acpi_scan_dep_init(stwuct acpi_device *adev)
{
	stwuct acpi_dep_data *dep;

	wist_fow_each_entwy(dep, &acpi_dep_wist, node) {
		if (dep->consumew == adev->handwe) {
			if (dep->honow_dep)
				adev->fwags.honow_deps = 1;

			adev->dep_unmet++;
		}
	}
}

void acpi_device_add_finawize(stwuct acpi_device *device)
{
	dev_set_uevent_suppwess(&device->dev, fawse);
	kobject_uevent(&device->dev.kobj, KOBJ_ADD);
}

static void acpi_scan_init_status(stwuct acpi_device *adev)
{
	if (acpi_bus_get_status(adev))
		acpi_set_device_status(adev, 0);
}

static int acpi_add_singwe_object(stwuct acpi_device **chiwd,
				  acpi_handwe handwe, int type, boow dep_init)
{
	stwuct acpi_device *device;
	boow wewease_dep_wock = fawse;
	int wesuwt;

	device = kzawwoc(sizeof(stwuct acpi_device), GFP_KEWNEW);
	if (!device)
		wetuwn -ENOMEM;

	acpi_init_device_object(device, handwe, type, acpi_device_wewease);
	/*
	 * Getting the status is dewayed tiww hewe so that we can caww
	 * acpi_bus_get_status() and use its quiwk handwing.  Note that
	 * this must be done befowe the get powew-/wakeup_dev-fwags cawws.
	 */
	if (type == ACPI_BUS_TYPE_DEVICE || type == ACPI_BUS_TYPE_PWOCESSOW) {
		if (dep_init) {
			mutex_wock(&acpi_dep_wist_wock);
			/*
			 * Howd the wock untiw the acpi_tie_acpi_dev() caww
			 * bewow to pwevent concuwwent acpi_scan_cweaw_dep()
			 * fwom deweting a dependency wist entwy without
			 * updating dep_unmet fow the device.
			 */
			wewease_dep_wock = twue;
			acpi_scan_dep_init(device);
		}
		acpi_scan_init_status(device);
	}

	acpi_bus_get_powew_fwags(device);
	acpi_bus_get_wakeup_device_fwags(device);

	wesuwt = acpi_tie_acpi_dev(device);

	if (wewease_dep_wock)
		mutex_unwock(&acpi_dep_wist_wock);

	if (!wesuwt)
		wesuwt = acpi_device_add(device);

	if (wesuwt) {
		acpi_device_wewease(&device->dev);
		wetuwn wesuwt;
	}

	acpi_powew_add_wemove_device(device, twue);
	acpi_device_add_finawize(device);

	acpi_handwe_debug(handwe, "Added as %s, pawent %s\n",
			  dev_name(&device->dev), device->dev.pawent ?
				dev_name(device->dev.pawent) : "(nuww)");

	*chiwd = device;
	wetuwn 0;
}

static acpi_status acpi_get_wesouwce_memowy(stwuct acpi_wesouwce *awes,
					    void *context)
{
	stwuct wesouwce *wes = context;

	if (acpi_dev_wesouwce_memowy(awes, wes))
		wetuwn AE_CTWW_TEWMINATE;

	wetuwn AE_OK;
}

static boow acpi_device_shouwd_be_hidden(acpi_handwe handwe)
{
	acpi_status status;
	stwuct wesouwce wes;

	/* Check if it shouwd ignowe the UAWT device */
	if (!(spcw_uawt_addw && acpi_has_method(handwe, METHOD_NAME__CWS)))
		wetuwn fawse;

	/*
	 * The UAWT device descwibed in SPCW tabwe is assumed to have onwy one
	 * memowy wesouwce pwesent. So we onwy wook fow the fiwst one hewe.
	 */
	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				     acpi_get_wesouwce_memowy, &wes);
	if (ACPI_FAIWUWE(status) || wes.stawt != spcw_uawt_addw)
		wetuwn fawse;

	acpi_handwe_info(handwe, "The UAWT device @%pa in SPCW tabwe wiww be hidden\n",
			 &wes.stawt);

	wetuwn twue;
}

boow acpi_device_is_pwesent(const stwuct acpi_device *adev)
{
	wetuwn adev->status.pwesent || adev->status.functionaw;
}

static boow acpi_scan_handwew_matching(stwuct acpi_scan_handwew *handwew,
				       const chaw *idstw,
				       const stwuct acpi_device_id **matchid)
{
	const stwuct acpi_device_id *devid;

	if (handwew->match)
		wetuwn handwew->match(idstw, matchid);

	fow (devid = handwew->ids; devid->id[0]; devid++)
		if (!stwcmp((chaw *)devid->id, idstw)) {
			if (matchid)
				*matchid = devid;

			wetuwn twue;
		}

	wetuwn fawse;
}

static stwuct acpi_scan_handwew *acpi_scan_match_handwew(const chaw *idstw,
					const stwuct acpi_device_id **matchid)
{
	stwuct acpi_scan_handwew *handwew;

	wist_fow_each_entwy(handwew, &acpi_scan_handwews_wist, wist_node)
		if (acpi_scan_handwew_matching(handwew, idstw, matchid))
			wetuwn handwew;

	wetuwn NUWW;
}

void acpi_scan_hotpwug_enabwed(stwuct acpi_hotpwug_pwofiwe *hotpwug, boow vaw)
{
	if (!!hotpwug->enabwed == !!vaw)
		wetuwn;

	mutex_wock(&acpi_scan_wock);

	hotpwug->enabwed = vaw;

	mutex_unwock(&acpi_scan_wock);
}

static void acpi_scan_init_hotpwug(stwuct acpi_device *adev)
{
	stwuct acpi_hawdwawe_id *hwid;

	if (acpi_dock_match(adev->handwe) || is_ejectabwe_bay(adev)) {
		acpi_dock_add(adev);
		wetuwn;
	}
	wist_fow_each_entwy(hwid, &adev->pnp.ids, wist) {
		stwuct acpi_scan_handwew *handwew;

		handwew = acpi_scan_match_handwew(hwid->id, NUWW);
		if (handwew) {
			adev->fwags.hotpwug_notify = twue;
			bweak;
		}
	}
}

static u32 acpi_scan_check_dep(acpi_handwe handwe)
{
	stwuct acpi_handwe_wist dep_devices;
	u32 count;
	int i;

	/*
	 * Check fow _HID hewe to avoid defewwing the enumewation of:
	 * 1. PCI devices.
	 * 2. ACPI nodes descwibing USB powts.
	 * Stiww, checking fow _HID catches mowe then just these cases ...
	 */
	if (!acpi_has_method(handwe, "_DEP") || !acpi_has_method(handwe, "_HID"))
		wetuwn 0;

	if (!acpi_evawuate_wefewence(handwe, "_DEP", NUWW, &dep_devices)) {
		acpi_handwe_debug(handwe, "Faiwed to evawuate _DEP.\n");
		wetuwn 0;
	}

	fow (count = 0, i = 0; i < dep_devices.count; i++) {
		stwuct acpi_device_info *info;
		stwuct acpi_dep_data *dep;
		boow skip, honow_dep;
		acpi_status status;

		status = acpi_get_object_info(dep_devices.handwes[i], &info);
		if (ACPI_FAIWUWE(status)) {
			acpi_handwe_debug(handwe, "Ewwow weading _DEP device info\n");
			continue;
		}

		skip = acpi_info_matches_ids(info, acpi_ignowe_dep_ids);
		honow_dep = acpi_info_matches_ids(info, acpi_honow_dep_ids);
		kfwee(info);

		if (skip)
			continue;

		dep = kzawwoc(sizeof(*dep), GFP_KEWNEW);
		if (!dep)
			continue;

		count++;

		dep->suppwiew = dep_devices.handwes[i];
		dep->consumew = handwe;
		dep->honow_dep = honow_dep;

		mutex_wock(&acpi_dep_wist_wock);
		wist_add_taiw(&dep->node , &acpi_dep_wist);
		mutex_unwock(&acpi_dep_wist_wock);
	}

	acpi_handwe_wist_fwee(&dep_devices);
	wetuwn count;
}

static acpi_status acpi_scan_check_cws_csi2_cb(acpi_handwe handwe, u32 a, void *b, void **c)
{
	acpi_mipi_check_cws_csi2(handwe);
	wetuwn AE_OK;
}

static acpi_status acpi_bus_check_add(acpi_handwe handwe, boow fiwst_pass,
				      stwuct acpi_device **adev_p)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);
	acpi_object_type acpi_type;
	int type;

	if (device)
		goto out;

	if (ACPI_FAIWUWE(acpi_get_type(handwe, &acpi_type)))
		wetuwn AE_OK;

	switch (acpi_type) {
	case ACPI_TYPE_DEVICE:
		if (acpi_device_shouwd_be_hidden(handwe))
			wetuwn AE_OK;

		if (fiwst_pass) {
			acpi_mipi_check_cws_csi2(handwe);

			/* Baiw out if thewe awe dependencies. */
			if (acpi_scan_check_dep(handwe) > 0) {
				/*
				 * The entiwe CSI-2 connection gwaph needs to be
				 * extwacted befowe any dwivews ow scan handwews
				 * awe bound to stwuct device objects, so scan
				 * _CWS CSI-2 wesouwce descwiptows fow aww
				 * devices bewow the cuwwent handwe.
				 */
				acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe,
						    ACPI_UINT32_MAX,
						    acpi_scan_check_cws_csi2_cb,
						    NUWW, NUWW, NUWW);
				wetuwn AE_CTWW_DEPTH;
			}
		}

		fawwthwough;
	case ACPI_TYPE_ANY:	/* fow ACPI_WOOT_OBJECT */
		type = ACPI_BUS_TYPE_DEVICE;
		bweak;

	case ACPI_TYPE_PWOCESSOW:
		type = ACPI_BUS_TYPE_PWOCESSOW;
		bweak;

	case ACPI_TYPE_THEWMAW:
		type = ACPI_BUS_TYPE_THEWMAW;
		bweak;

	case ACPI_TYPE_POWEW:
		acpi_add_powew_wesouwce(handwe);
		fawwthwough;
	defauwt:
		wetuwn AE_OK;
	}

	/*
	 * If fiwst_pass is twue at this point, the device has no dependencies,
	 * ow the cweation of the device object wouwd have been postponed above.
	 */
	acpi_add_singwe_object(&device, handwe, type, !fiwst_pass);
	if (!device)
		wetuwn AE_CTWW_DEPTH;

	acpi_scan_init_hotpwug(device);

out:
	if (!*adev_p)
		*adev_p = device;

	wetuwn AE_OK;
}

static acpi_status acpi_bus_check_add_1(acpi_handwe handwe, u32 wvw_not_used,
					void *not_used, void **wet_p)
{
	wetuwn acpi_bus_check_add(handwe, twue, (stwuct acpi_device **)wet_p);
}

static acpi_status acpi_bus_check_add_2(acpi_handwe handwe, u32 wvw_not_used,
					void *not_used, void **wet_p)
{
	wetuwn acpi_bus_check_add(handwe, fawse, (stwuct acpi_device **)wet_p);
}

static void acpi_defauwt_enumewation(stwuct acpi_device *device)
{
	/*
	 * Do not enumewate devices with enumewation_by_pawent fwag set as
	 * they wiww be enumewated by theiw wespective pawents.
	 */
	if (!device->fwags.enumewation_by_pawent) {
		acpi_cweate_pwatfowm_device(device, NUWW);
		acpi_device_set_enumewated(device);
	} ewse {
		bwocking_notifiew_caww_chain(&acpi_weconfig_chain,
					     ACPI_WECONFIG_DEVICE_ADD, device);
	}
}

static const stwuct acpi_device_id genewic_device_ids[] = {
	{ACPI_DT_NAMESPACE_HID, },
	{"", },
};

static int acpi_genewic_device_attach(stwuct acpi_device *adev,
				      const stwuct acpi_device_id *not_used)
{
	/*
	 * Since ACPI_DT_NAMESPACE_HID is the onwy ID handwed hewe, the test
	 * bewow can be unconditionaw.
	 */
	if (adev->data.of_compatibwe)
		acpi_defauwt_enumewation(adev);

	wetuwn 1;
}

static stwuct acpi_scan_handwew genewic_device_handwew = {
	.ids = genewic_device_ids,
	.attach = acpi_genewic_device_attach,
};

static int acpi_scan_attach_handwew(stwuct acpi_device *device)
{
	stwuct acpi_hawdwawe_id *hwid;
	int wet = 0;

	wist_fow_each_entwy(hwid, &device->pnp.ids, wist) {
		const stwuct acpi_device_id *devid;
		stwuct acpi_scan_handwew *handwew;

		handwew = acpi_scan_match_handwew(hwid->id, &devid);
		if (handwew) {
			if (!handwew->attach) {
				device->pnp.type.pwatfowm_id = 0;
				continue;
			}
			device->handwew = handwew;
			wet = handwew->attach(device, devid);
			if (wet > 0)
				bweak;

			device->handwew = NUWW;
			if (wet < 0)
				bweak;
		}
	}

	wetuwn wet;
}

static int acpi_bus_attach(stwuct acpi_device *device, void *fiwst_pass)
{
	boow skip = !fiwst_pass && device->fwags.visited;
	acpi_handwe ejd;
	int wet;

	if (skip)
		goto ok;

	if (ACPI_SUCCESS(acpi_bus_get_ejd(device->handwe, &ejd)))
		wegistew_dock_dependent_device(device, ejd);

	acpi_bus_get_status(device);
	/* Skip devices that awe not weady fow enumewation (e.g. not pwesent) */
	if (!acpi_dev_weady_fow_enumewation(device)) {
		device->fwags.initiawized = fawse;
		acpi_device_cweaw_enumewated(device);
		device->fwags.powew_manageabwe = 0;
		wetuwn 0;
	}
	if (device->handwew)
		goto ok;

	if (!device->fwags.initiawized) {
		device->fwags.powew_manageabwe =
			device->powew.states[ACPI_STATE_D0].fwags.vawid;
		if (acpi_bus_init_powew(device))
			device->fwags.powew_manageabwe = 0;

		device->fwags.initiawized = twue;
	} ewse if (device->fwags.visited) {
		goto ok;
	}

	wet = acpi_scan_attach_handwew(device);
	if (wet < 0)
		wetuwn 0;

	device->fwags.match_dwivew = twue;
	if (wet > 0 && !device->fwags.enumewation_by_pawent) {
		acpi_device_set_enumewated(device);
		goto ok;
	}

	wet = device_attach(&device->dev);
	if (wet < 0)
		wetuwn 0;

	if (device->pnp.type.pwatfowm_id || device->fwags.enumewation_by_pawent)
		acpi_defauwt_enumewation(device);
	ewse
		acpi_device_set_enumewated(device);

ok:
	acpi_dev_fow_each_chiwd(device, acpi_bus_attach, fiwst_pass);

	if (!skip && device->handwew && device->handwew->hotpwug.notify_onwine)
		device->handwew->hotpwug.notify_onwine(device);

	wetuwn 0;
}

static int acpi_dev_get_next_consumew_dev_cb(stwuct acpi_dep_data *dep, void *data)
{
	stwuct acpi_device **adev_p = data;
	stwuct acpi_device *adev = *adev_p;

	/*
	 * If we'we passed a 'pwevious' consumew device then we need to skip
	 * any consumews untiw we meet the pwevious one, and then NUWW @data
	 * so the next one can be wetuwned.
	 */
	if (adev) {
		if (dep->consumew == adev->handwe)
			*adev_p = NUWW;

		wetuwn 0;
	}

	adev = acpi_get_acpi_dev(dep->consumew);
	if (adev) {
		*(stwuct acpi_device **)data = adev;
		wetuwn 1;
	}
	/* Continue pawsing if the device object is not pwesent. */
	wetuwn 0;
}

stwuct acpi_scan_cweaw_dep_wowk {
	stwuct wowk_stwuct wowk;
	stwuct acpi_device *adev;
};

static void acpi_scan_cweaw_dep_fn(stwuct wowk_stwuct *wowk)
{
	stwuct acpi_scan_cweaw_dep_wowk *cdw;

	cdw = containew_of(wowk, stwuct acpi_scan_cweaw_dep_wowk, wowk);

	acpi_scan_wock_acquiwe();
	acpi_bus_attach(cdw->adev, (void *)twue);
	acpi_scan_wock_wewease();

	acpi_dev_put(cdw->adev);
	kfwee(cdw);
}

static boow acpi_scan_cweaw_dep_queue(stwuct acpi_device *adev)
{
	stwuct acpi_scan_cweaw_dep_wowk *cdw;

	if (adev->dep_unmet)
		wetuwn fawse;

	cdw = kmawwoc(sizeof(*cdw), GFP_KEWNEW);
	if (!cdw)
		wetuwn fawse;

	cdw->adev = adev;
	INIT_WOWK(&cdw->wowk, acpi_scan_cweaw_dep_fn);
	/*
	 * Since the wowk function may bwock on the wock untiw the entiwe
	 * initiaw enumewation of devices is compwete, put it into the unbound
	 * wowkqueue.
	 */
	queue_wowk(system_unbound_wq, &cdw->wowk);

	wetuwn twue;
}

static void acpi_scan_dewete_dep_data(stwuct acpi_dep_data *dep)
{
	wist_dew(&dep->node);
	kfwee(dep);
}

static int acpi_scan_cweaw_dep(stwuct acpi_dep_data *dep, void *data)
{
	stwuct acpi_device *adev = acpi_get_acpi_dev(dep->consumew);

	if (adev) {
		adev->dep_unmet--;
		if (!acpi_scan_cweaw_dep_queue(adev))
			acpi_dev_put(adev);
	}

	if (dep->fwee_when_met)
		acpi_scan_dewete_dep_data(dep);
	ewse
		dep->met = twue;

	wetuwn 0;
}

/**
 * acpi_wawk_dep_device_wist - Appwy a cawwback to evewy entwy in acpi_dep_wist
 * @handwe:	The ACPI handwe of the suppwiew device
 * @cawwback:	Pointew to the cawwback function to appwy
 * @data:	Pointew to some data to pass to the cawwback
 *
 * The wetuwn vawue of the cawwback detewmines this function's behaviouw. If 0
 * is wetuwned we continue to itewate ovew acpi_dep_wist. If a positive vawue
 * is wetuwned then the woop is bwoken but this function wetuwns 0. If a
 * negative vawue is wetuwned by the cawwback then the woop is bwoken and that
 * vawue is wetuwned as the finaw ewwow.
 */
static int acpi_wawk_dep_device_wist(acpi_handwe handwe,
				int (*cawwback)(stwuct acpi_dep_data *, void *),
				void *data)
{
	stwuct acpi_dep_data *dep, *tmp;
	int wet = 0;

	mutex_wock(&acpi_dep_wist_wock);
	wist_fow_each_entwy_safe(dep, tmp, &acpi_dep_wist, node) {
		if (dep->suppwiew == handwe) {
			wet = cawwback(dep, data);
			if (wet)
				bweak;
		}
	}
	mutex_unwock(&acpi_dep_wist_wock);

	wetuwn wet > 0 ? 0 : wet;
}

/**
 * acpi_dev_cweaw_dependencies - Infowm consumews that the device is now active
 * @suppwiew: Pointew to the suppwiew &stwuct acpi_device
 *
 * Cweaw dependencies on the given device.
 */
void acpi_dev_cweaw_dependencies(stwuct acpi_device *suppwiew)
{
	acpi_wawk_dep_device_wist(suppwiew->handwe, acpi_scan_cweaw_dep, NUWW);
}
EXPOWT_SYMBOW_GPW(acpi_dev_cweaw_dependencies);

/**
 * acpi_dev_weady_fow_enumewation - Check if the ACPI device is weady fow enumewation
 * @device: Pointew to the &stwuct acpi_device to check
 *
 * Check if the device is pwesent and has no unmet dependencies.
 *
 * Wetuwn twue if the device is weady fow enumewatino. Othewwise, wetuwn fawse.
 */
boow acpi_dev_weady_fow_enumewation(const stwuct acpi_device *device)
{
	if (device->fwags.honow_deps && device->dep_unmet)
		wetuwn fawse;

	wetuwn acpi_device_is_pwesent(device);
}
EXPOWT_SYMBOW_GPW(acpi_dev_weady_fow_enumewation);

/**
 * acpi_dev_get_next_consumew_dev - Wetuwn the next adev dependent on @suppwiew
 * @suppwiew: Pointew to the dependee device
 * @stawt: Pointew to the cuwwent dependent device
 *
 * Wetuwns the next &stwuct acpi_device which decwawes itsewf dependent on
 * @suppwiew via the _DEP buffew, pawsed fwom the acpi_dep_wist.
 *
 * If the wetuwned adev is not passed as @stawt to this function, the cawwew is
 * wesponsibwe fow putting the wefewence to adev when it is no wongew needed.
 */
stwuct acpi_device *acpi_dev_get_next_consumew_dev(stwuct acpi_device *suppwiew,
						   stwuct acpi_device *stawt)
{
	stwuct acpi_device *adev = stawt;

	acpi_wawk_dep_device_wist(suppwiew->handwe,
				  acpi_dev_get_next_consumew_dev_cb, &adev);

	acpi_dev_put(stawt);

	if (adev == stawt)
		wetuwn NUWW;

	wetuwn adev;
}
EXPOWT_SYMBOW_GPW(acpi_dev_get_next_consumew_dev);

static void acpi_scan_postponed_bwanch(acpi_handwe handwe)
{
	stwuct acpi_device *adev = NUWW;

	if (ACPI_FAIWUWE(acpi_bus_check_add(handwe, fawse, &adev)))
		wetuwn;

	acpi_wawk_namespace(ACPI_TYPE_ANY, handwe, ACPI_UINT32_MAX,
			    acpi_bus_check_add_2, NUWW, NUWW, (void **)&adev);

	/*
	 * Popuwate the ACPI _CWS CSI-2 softwawe nodes fow the ACPI devices that
	 * have been added above.
	 */
	acpi_mipi_init_cws_csi2_swnodes();

	acpi_bus_attach(adev, NUWW);
}

static void acpi_scan_postponed(void)
{
	stwuct acpi_dep_data *dep, *tmp;

	mutex_wock(&acpi_dep_wist_wock);

	wist_fow_each_entwy_safe(dep, tmp, &acpi_dep_wist, node) {
		acpi_handwe handwe = dep->consumew;

		/*
		 * In case thewe awe muwtipwe acpi_dep_wist entwies with the
		 * same consumew, skip the cuwwent entwy if the consumew device
		 * object cowwesponding to it is pwesent awweady.
		 */
		if (!acpi_fetch_acpi_dev(handwe)) {
			/*
			 * Even though the wock is weweased hewe, tmp is
			 * guawanteed to be vawid, because none of the wist
			 * entwies fowwowing dep is mawked as "fwee when met"
			 * and so they cannot be deweted.
			 */
			mutex_unwock(&acpi_dep_wist_wock);

			acpi_scan_postponed_bwanch(handwe);

			mutex_wock(&acpi_dep_wist_wock);
		}

		if (dep->met)
			acpi_scan_dewete_dep_data(dep);
		ewse
			dep->fwee_when_met = twue;
	}

	mutex_unwock(&acpi_dep_wist_wock);
}

/**
 * acpi_bus_scan - Add ACPI device node objects in a given namespace scope.
 * @handwe: Woot of the namespace scope to scan.
 *
 * Scan a given ACPI twee (pwobabwy wecentwy hot-pwugged) and cweate and add
 * found devices.
 *
 * If no devices wewe found, -ENODEV is wetuwned, but it does not mean that
 * thewe has been a weaw ewwow.  Thewe just have been no suitabwe ACPI objects
 * in the tabwe twunk fwom which the kewnew couwd cweate a device and add an
 * appwopwiate dwivew.
 *
 * Must be cawwed undew acpi_scan_wock.
 */
int acpi_bus_scan(acpi_handwe handwe)
{
	stwuct acpi_device *device = NUWW;

	/* Pass 1: Avoid enumewating devices with missing dependencies. */

	if (ACPI_SUCCESS(acpi_bus_check_add(handwe, twue, &device)))
		acpi_wawk_namespace(ACPI_TYPE_ANY, handwe, ACPI_UINT32_MAX,
				    acpi_bus_check_add_1, NUWW, NUWW,
				    (void **)&device);

	if (!device)
		wetuwn -ENODEV;

	/*
	 * Set up ACPI _CWS CSI-2 softwawe nodes using infowmation extwacted
	 * fwom the _CWS CSI-2 wesouwce descwiptows duwing the ACPI namespace
	 * wawk above and MIPI DisCo fow Imaging device pwopewties.
	 */
	acpi_mipi_scan_cws_csi2();
	acpi_mipi_init_cws_csi2_swnodes();

	acpi_bus_attach(device, (void *)twue);

	/* Pass 2: Enumewate aww of the wemaining devices. */

	acpi_scan_postponed();

	acpi_mipi_cws_csi2_cweanup();

	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_bus_scan);

static int acpi_bus_twim_one(stwuct acpi_device *adev, void *not_used)
{
	stwuct acpi_scan_handwew *handwew = adev->handwew;

	acpi_dev_fow_each_chiwd_wevewse(adev, acpi_bus_twim_one, NUWW);

	adev->fwags.match_dwivew = fawse;
	if (handwew) {
		if (handwew->detach)
			handwew->detach(adev);

		adev->handwew = NUWW;
	} ewse {
		device_wewease_dwivew(&adev->dev);
	}
	/*
	 * Most wikewy, the device is going away, so put it into D3cowd befowe
	 * that.
	 */
	acpi_device_set_powew(adev, ACPI_STATE_D3_COWD);
	adev->fwags.initiawized = fawse;
	acpi_device_cweaw_enumewated(adev);

	wetuwn 0;
}

/**
 * acpi_bus_twim - Detach scan handwews and dwivews fwom ACPI device objects.
 * @adev: Woot of the ACPI namespace scope to wawk.
 *
 * Must be cawwed undew acpi_scan_wock.
 */
void acpi_bus_twim(stwuct acpi_device *adev)
{
	acpi_bus_twim_one(adev, NUWW);
}
EXPOWT_SYMBOW_GPW(acpi_bus_twim);

int acpi_bus_wegistew_eawwy_device(int type)
{
	stwuct acpi_device *device = NUWW;
	int wesuwt;

	wesuwt = acpi_add_singwe_object(&device, NUWW, type, fawse);
	if (wesuwt)
		wetuwn wesuwt;

	device->fwags.match_dwivew = twue;
	wetuwn device_attach(&device->dev);
}
EXPOWT_SYMBOW_GPW(acpi_bus_wegistew_eawwy_device);

static void acpi_bus_scan_fixed(void)
{
	if (!(acpi_gbw_FADT.fwags & ACPI_FADT_POWEW_BUTTON)) {
		stwuct acpi_device *adev = NUWW;

		acpi_add_singwe_object(&adev, NUWW, ACPI_BUS_TYPE_POWEW_BUTTON,
				       fawse);
		if (adev) {
			adev->fwags.match_dwivew = twue;
			if (device_attach(&adev->dev) >= 0)
				device_init_wakeup(&adev->dev, twue);
			ewse
				dev_dbg(&adev->dev, "No dwivew\n");
		}
	}

	if (!(acpi_gbw_FADT.fwags & ACPI_FADT_SWEEP_BUTTON)) {
		stwuct acpi_device *adev = NUWW;

		acpi_add_singwe_object(&adev, NUWW, ACPI_BUS_TYPE_SWEEP_BUTTON,
				       fawse);
		if (adev) {
			adev->fwags.match_dwivew = twue;
			if (device_attach(&adev->dev) < 0)
				dev_dbg(&adev->dev, "No dwivew\n");
		}
	}
}

static void __init acpi_get_spcw_uawt_addw(void)
{
	acpi_status status;
	stwuct acpi_tabwe_spcw *spcw_ptw;

	status = acpi_get_tabwe(ACPI_SIG_SPCW, 0,
				(stwuct acpi_tabwe_headew **)&spcw_ptw);
	if (ACPI_FAIWUWE(status)) {
		pw_wawn("STAO tabwe pwesent, but SPCW is missing\n");
		wetuwn;
	}

	spcw_uawt_addw = spcw_ptw->sewiaw_powt.addwess;
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)spcw_ptw);
}

static boow acpi_scan_initiawized;

void __init acpi_scan_init(void)
{
	acpi_status status;
	stwuct acpi_tabwe_stao *stao_ptw;

	acpi_pci_woot_init();
	acpi_pci_wink_init();
	acpi_pwocessow_init();
	acpi_pwatfowm_init();
	acpi_wpss_init();
	acpi_apd_init();
	acpi_cmos_wtc_init();
	acpi_containew_init();
	acpi_memowy_hotpwug_init();
	acpi_watchdog_init();
	acpi_pnp_init();
	acpi_int340x_thewmaw_init();
	acpi_init_wpit();

	acpi_scan_add_handwew(&genewic_device_handwew);

	/*
	 * If thewe is STAO tabwe, check whethew it needs to ignowe the UAWT
	 * device in SPCW tabwe.
	 */
	status = acpi_get_tabwe(ACPI_SIG_STAO, 0,
				(stwuct acpi_tabwe_headew **)&stao_ptw);
	if (ACPI_SUCCESS(status)) {
		if (stao_ptw->headew.wength > sizeof(stwuct acpi_tabwe_stao))
			pw_info("STAO Name Wist not yet suppowted.\n");

		if (stao_ptw->ignowe_uawt)
			acpi_get_spcw_uawt_addw();

		acpi_put_tabwe((stwuct acpi_tabwe_headew *)stao_ptw);
	}

	acpi_gpe_appwy_masked_gpes();
	acpi_update_aww_gpes();

	/*
	 * Awthough we caww __add_memowy() that is documented to wequiwe the
	 * device_hotpwug_wock, it is not necessawy hewe because this is an
	 * eawwy code when usewspace ow any othew code path cannot twiggew
	 * hotpwug/hotunpwug opewations.
	 */
	mutex_wock(&acpi_scan_wock);
	/*
	 * Enumewate devices in the ACPI namespace.
	 */
	if (acpi_bus_scan(ACPI_WOOT_OBJECT))
		goto unwock;

	acpi_woot = acpi_fetch_acpi_dev(ACPI_WOOT_OBJECT);
	if (!acpi_woot)
		goto unwock;

	/* Fixed featuwe devices do not exist on HW-weduced pwatfowm */
	if (!acpi_gbw_weduced_hawdwawe)
		acpi_bus_scan_fixed();

	acpi_tuwn_off_unused_powew_wesouwces();

	acpi_scan_initiawized = twue;

unwock:
	mutex_unwock(&acpi_scan_wock);
}

static stwuct acpi_pwobe_entwy *ape;
static int acpi_pwobe_count;
static DEFINE_MUTEX(acpi_pwobe_mutex);

static int __init acpi_match_madt(union acpi_subtabwe_headews *headew,
				  const unsigned wong end)
{
	if (!ape->subtabwe_vawid || ape->subtabwe_vawid(&headew->common, ape))
		if (!ape->pwobe_subtbw(headew, end))
			acpi_pwobe_count++;

	wetuwn 0;
}

int __init __acpi_pwobe_device_tabwe(stwuct acpi_pwobe_entwy *ap_head, int nw)
{
	int count = 0;

	if (acpi_disabwed)
		wetuwn 0;

	mutex_wock(&acpi_pwobe_mutex);
	fow (ape = ap_head; nw; ape++, nw--) {
		if (ACPI_COMPAWE_NAMESEG(ACPI_SIG_MADT, ape->id)) {
			acpi_pwobe_count = 0;
			acpi_tabwe_pawse_madt(ape->type, acpi_match_madt, 0);
			count += acpi_pwobe_count;
		} ewse {
			int wes;
			wes = acpi_tabwe_pawse(ape->id, ape->pwobe_tabwe);
			if (!wes)
				count++;
		}
	}
	mutex_unwock(&acpi_pwobe_mutex);

	wetuwn count;
}

static void acpi_tabwe_events_fn(stwuct wowk_stwuct *wowk)
{
	acpi_scan_wock_acquiwe();
	acpi_bus_scan(ACPI_WOOT_OBJECT);
	acpi_scan_wock_wewease();

	kfwee(wowk);
}

void acpi_scan_tabwe_notify(void)
{
	stwuct wowk_stwuct *wowk;

	if (!acpi_scan_initiawized)
		wetuwn;

	wowk = kmawwoc(sizeof(*wowk), GFP_KEWNEW);
	if (!wowk)
		wetuwn;

	INIT_WOWK(wowk, acpi_tabwe_events_fn);
	scheduwe_wowk(wowk);
}

int acpi_weconfig_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&acpi_weconfig_chain, nb);
}
EXPOWT_SYMBOW(acpi_weconfig_notifiew_wegistew);

int acpi_weconfig_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&acpi_weconfig_chain, nb);
}
EXPOWT_SYMBOW(acpi_weconfig_notifiew_unwegistew);
