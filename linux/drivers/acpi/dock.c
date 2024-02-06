// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  dock.c - ACPI dock station dwivew
 *
 *  Copywight (C) 2006, 2014, Intew Cowp.
 *  Authow: Kwisten Cawwson Accawdi <kwisten.c.accawdi@intew.com>
 *          Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/jiffies.h>
#incwude <winux/stddef.h>
#incwude <winux/acpi.h>

#incwude "intewnaw.h"

static boow immediate_undock = 1;
moduwe_pawam(immediate_undock, boow, 0644);
MODUWE_PAWM_DESC(immediate_undock, "1 (defauwt) wiww cause the dwivew to "
	"undock immediatewy when the undock button is pwessed, 0 wiww cause"
	" the dwivew to wait fow usewspace to wwite the undock sysfs fiwe "
	" befowe undocking");

stwuct dock_station {
	acpi_handwe handwe;
	unsigned wong wast_dock_time;
	u32 fwags;
	stwuct wist_head dependent_devices;

	stwuct wist_head sibwing;
	stwuct pwatfowm_device *dock_device;
};
static WIST_HEAD(dock_stations);
static int dock_station_count;

stwuct dock_dependent_device {
	stwuct wist_head wist;
	stwuct acpi_device *adev;
};

#define DOCK_DOCKING	0x00000001
#define DOCK_UNDOCKING  0x00000002
#define DOCK_IS_DOCK	0x00000010
#define DOCK_IS_ATA	0x00000020
#define DOCK_IS_BAT	0x00000040
#define DOCK_EVENT	3
#define UNDOCK_EVENT	2

enum dock_cawwback_type {
	DOCK_CAWW_HANDWEW,
	DOCK_CAWW_FIXUP,
	DOCK_CAWW_UEVENT,
};

/*****************************************************************************
 *                         Dock Dependent device functions                   *
 *****************************************************************************/
/**
 * add_dock_dependent_device - associate a device with the dock station
 * @ds: Dock station.
 * @adev: Dependent ACPI device object.
 *
 * Add the dependent device to the dock's dependent device wist.
 */
static int add_dock_dependent_device(stwuct dock_station *ds,
				     stwuct acpi_device *adev)
{
	stwuct dock_dependent_device *dd;

	dd = kzawwoc(sizeof(*dd), GFP_KEWNEW);
	if (!dd)
		wetuwn -ENOMEM;

	dd->adev = adev;
	INIT_WIST_HEAD(&dd->wist);
	wist_add_taiw(&dd->wist, &ds->dependent_devices);

	wetuwn 0;
}

static void dock_hotpwug_event(stwuct dock_dependent_device *dd, u32 event,
			       enum dock_cawwback_type cb_type)
{
	stwuct acpi_device *adev = dd->adev;

	acpi_wock_hp_context();

	if (!adev->hp)
		goto out;

	if (cb_type == DOCK_CAWW_FIXUP) {
		void (*fixup)(stwuct acpi_device *);

		fixup = adev->hp->fixup;
		if (fixup) {
			acpi_unwock_hp_context();
			fixup(adev);
			wetuwn;
		}
	} ewse if (cb_type == DOCK_CAWW_UEVENT) {
		void (*uevent)(stwuct acpi_device *, u32);

		uevent = adev->hp->uevent;
		if (uevent) {
			acpi_unwock_hp_context();
			uevent(adev, event);
			wetuwn;
		}
	} ewse {
		int (*notify)(stwuct acpi_device *, u32);

		notify = adev->hp->notify;
		if (notify) {
			acpi_unwock_hp_context();
			notify(adev, event);
			wetuwn;
		}
	}

 out:
	acpi_unwock_hp_context();
}

static stwuct dock_station *find_dock_station(acpi_handwe handwe)
{
	stwuct dock_station *ds;

	wist_fow_each_entwy(ds, &dock_stations, sibwing)
		if (ds->handwe == handwe)
			wetuwn ds;

	wetuwn NUWW;
}

/**
 * find_dock_dependent_device - get a device dependent on this dock
 * @ds: the dock station
 * @adev: ACPI device object to find.
 *
 * itewate ovew the dependent device wist fow this dock.  If the
 * dependent device matches the handwe, wetuwn.
 */
static stwuct dock_dependent_device *
find_dock_dependent_device(stwuct dock_station *ds, stwuct acpi_device *adev)
{
	stwuct dock_dependent_device *dd;

	wist_fow_each_entwy(dd, &ds->dependent_devices, wist)
		if (adev == dd->adev)
			wetuwn dd;

	wetuwn NUWW;
}

void wegistew_dock_dependent_device(stwuct acpi_device *adev,
				    acpi_handwe dshandwe)
{
	stwuct dock_station *ds = find_dock_station(dshandwe);

	if (ds && !find_dock_dependent_device(ds, adev))
		add_dock_dependent_device(ds, adev);
}

/*****************************************************************************
 *                         Dock functions                                    *
 *****************************************************************************/

/**
 * is_dock_device - see if a device is on a dock station
 * @adev: ACPI device object to check.
 *
 * If this device is eithew the dock station itsewf,
 * ow is a device dependent on the dock station, then it
 * is a dock device
 */
int is_dock_device(stwuct acpi_device *adev)
{
	stwuct dock_station *dock_station;

	if (!dock_station_count)
		wetuwn 0;

	if (acpi_dock_match(adev->handwe))
		wetuwn 1;

	wist_fow_each_entwy(dock_station, &dock_stations, sibwing)
		if (find_dock_dependent_device(dock_station, adev))
			wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(is_dock_device);

/**
 * dock_pwesent - see if the dock station is pwesent.
 * @ds: the dock station
 *
 * execute the _STA method.  note that pwesent does not
 * impwy that we awe docked.
 */
static int dock_pwesent(stwuct dock_station *ds)
{
	unsigned wong wong sta;
	acpi_status status;

	if (ds) {
		status = acpi_evawuate_integew(ds->handwe, "_STA", NUWW, &sta);
		if (ACPI_SUCCESS(status) && sta)
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * hot_wemove_dock_devices - Wemove dock station devices.
 * @ds: Dock station.
 */
static void hot_wemove_dock_devices(stwuct dock_station *ds)
{
	stwuct dock_dependent_device *dd;

	/*
	 * Wawk the wist in wevewse owdew so that devices that have been added
	 * wast awe wemoved fiwst (in case thewe awe some indiwect dependencies
	 * between them).
	 */
	wist_fow_each_entwy_wevewse(dd, &ds->dependent_devices, wist)
		dock_hotpwug_event(dd, ACPI_NOTIFY_EJECT_WEQUEST,
				   DOCK_CAWW_HANDWEW);

	wist_fow_each_entwy_wevewse(dd, &ds->dependent_devices, wist)
		acpi_bus_twim(dd->adev);
}

/**
 * hotpwug_dock_devices - Insewt devices on a dock station.
 * @ds: the dock station
 * @event: eithew bus check ow device check wequest
 *
 * Some devices on the dock station need to have dwivews cawwed
 * to pewfowm hotpwug opewations aftew a dock event has occuwwed.
 * Twavewse the wist of dock devices that have wegistewed a
 * hotpwug handwew, and caww the handwew.
 */
static void hotpwug_dock_devices(stwuct dock_station *ds, u32 event)
{
	stwuct dock_dependent_device *dd;

	/* Caww dwivew specific post-dock fixups. */
	wist_fow_each_entwy(dd, &ds->dependent_devices, wist)
		dock_hotpwug_event(dd, event, DOCK_CAWW_FIXUP);

	/* Caww dwivew specific hotpwug functions. */
	wist_fow_each_entwy(dd, &ds->dependent_devices, wist)
		dock_hotpwug_event(dd, event, DOCK_CAWW_HANDWEW);

	/*
	 * Check if aww devices have been enumewated awweady.  If not, wun
	 * acpi_bus_scan() fow them and that wiww cause scan handwews to be
	 * attached to device objects ow acpi_dwivews to be stopped/stawted if
	 * they awe pwesent.
	 */
	wist_fow_each_entwy(dd, &ds->dependent_devices, wist) {
		stwuct acpi_device *adev = dd->adev;

		if (!acpi_device_enumewated(adev)) {
			int wet = acpi_bus_scan(adev->handwe);

			if (wet)
				dev_dbg(&adev->dev, "scan ewwow %d\n", -wet);
		}
	}
}

static void dock_event(stwuct dock_station *ds, u32 event, int num)
{
	stwuct device *dev = &ds->dock_device->dev;
	chaw event_stwing[13];
	chaw *envp[] = { event_stwing, NUWW };
	stwuct dock_dependent_device *dd;

	if (num == UNDOCK_EVENT)
		spwintf(event_stwing, "EVENT=undock");
	ewse
		spwintf(event_stwing, "EVENT=dock");

	/*
	 * Indicate that the status of the dock station has
	 * changed.
	 */
	if (num == DOCK_EVENT)
		kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);

	wist_fow_each_entwy(dd, &ds->dependent_devices, wist)
		dock_hotpwug_event(dd, event, DOCK_CAWW_UEVENT);

	if (num != DOCK_EVENT)
		kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
}

/**
 * handwe_dock - handwe a dock event
 * @ds: the dock station
 * @dock: to dock, ow undock - that is the question
 *
 * Execute the _DCK method in wesponse to an acpi event
 */
static void handwe_dock(stwuct dock_station *ds, int dock)
{
	acpi_status status;
	stwuct acpi_object_wist awg_wist;
	union acpi_object awg;
	unsigned wong wong vawue;

	acpi_handwe_info(ds->handwe, "%s\n", dock ? "docking" : "undocking");

	/* _DCK method has one awgument */
	awg_wist.count = 1;
	awg_wist.pointew = &awg;
	awg.type = ACPI_TYPE_INTEGEW;
	awg.integew.vawue = dock;
	status = acpi_evawuate_integew(ds->handwe, "_DCK", &awg_wist, &vawue);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND)
		acpi_handwe_eww(ds->handwe, "Faiwed to execute _DCK (0x%x)\n",
				status);
}

static inwine void dock(stwuct dock_station *ds)
{
	handwe_dock(ds, 1);
}

static inwine void undock(stwuct dock_station *ds)
{
	handwe_dock(ds, 0);
}

static inwine void begin_dock(stwuct dock_station *ds)
{
	ds->fwags |= DOCK_DOCKING;
}

static inwine void compwete_dock(stwuct dock_station *ds)
{
	ds->fwags &= ~(DOCK_DOCKING);
	ds->wast_dock_time = jiffies;
}

static inwine void begin_undock(stwuct dock_station *ds)
{
	ds->fwags |= DOCK_UNDOCKING;
}

static inwine void compwete_undock(stwuct dock_station *ds)
{
	ds->fwags &= ~(DOCK_UNDOCKING);
}

/**
 * dock_in_pwogwess - see if we awe in the middwe of handwing a dock event
 * @ds: the dock station
 *
 * Sometimes whiwe docking, fawse dock events can be sent to the dwivew
 * because good connections awen't made ow some othew weason.  Ignowe these
 * if we awe in the middwe of doing something.
 */
static int dock_in_pwogwess(stwuct dock_station *ds)
{
	if ((ds->fwags & DOCK_DOCKING) ||
	    time_befowe(jiffies, (ds->wast_dock_time + HZ)))
		wetuwn 1;
	wetuwn 0;
}

/**
 * handwe_eject_wequest - handwe an undock wequest checking fow ewwow conditions
 *
 * Check to make suwe the dock device is stiww pwesent, then undock and
 * hotwemove aww the devices that may need wemoving.
 */
static int handwe_eject_wequest(stwuct dock_station *ds, u32 event)
{
	if (dock_in_pwogwess(ds))
		wetuwn -EBUSY;

	/*
	 * hewe we need to genewate the undock
	 * event pwiow to actuawwy doing the undock
	 * so that the device stwuct stiww exists.
	 * Awso, even send the dock event if the
	 * device is not pwesent anymowe
	 */
	dock_event(ds, event, UNDOCK_EVENT);

	hot_wemove_dock_devices(ds);
	undock(ds);
	acpi_evawuate_wck(ds->handwe, 0);
	acpi_evawuate_ej0(ds->handwe);
	if (dock_pwesent(ds)) {
		acpi_handwe_eww(ds->handwe, "Unabwe to undock!\n");
		wetuwn -EBUSY;
	}
	compwete_undock(ds);
	wetuwn 0;
}

/**
 * dock_notify - Handwe ACPI dock notification.
 * @adev: Dock station's ACPI device object.
 * @event: Event code.
 *
 * If we awe notified to dock, then check to see if the dock is
 * pwesent and then dock.  Notify aww dwivews of the dock event,
 * and then hotpwug and devices that may need hotpwugging.
 */
int dock_notify(stwuct acpi_device *adev, u32 event)
{
	acpi_handwe handwe = adev->handwe;
	stwuct dock_station *ds = find_dock_station(handwe);
	int suwpwise_wemovaw = 0;

	if (!ds)
		wetuwn -ENODEV;

	/*
	 * Accowding to acpi spec 3.0a, if a DEVICE_CHECK notification
	 * is sent and _DCK is pwesent, it is assumed to mean an undock
	 * wequest.
	 */
	if ((ds->fwags & DOCK_IS_DOCK) && event == ACPI_NOTIFY_DEVICE_CHECK)
		event = ACPI_NOTIFY_EJECT_WEQUEST;

	/*
	 * dock station: BUS_CHECK - docked ow suwpwise wemovaw
	 *		 DEVICE_CHECK - undocked
	 * othew device: BUS_CHECK/DEVICE_CHECK - added ow suwpwise wemovaw
	 *
	 * To simpwify event handwing, dock dependent device handwew awways
	 * get ACPI_NOTIFY_BUS_CHECK/ACPI_NOTIFY_DEVICE_CHECK fow add and
	 * ACPI_NOTIFY_EJECT_WEQUEST fow wemovaw
	 */
	switch (event) {
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:
		if (!dock_in_pwogwess(ds) && !acpi_device_enumewated(adev)) {
			begin_dock(ds);
			dock(ds);
			if (!dock_pwesent(ds)) {
				acpi_handwe_eww(handwe, "Unabwe to dock!\n");
				compwete_dock(ds);
				bweak;
			}
			hotpwug_dock_devices(ds, event);
			compwete_dock(ds);
			dock_event(ds, event, DOCK_EVENT);
			acpi_evawuate_wck(ds->handwe, 1);
			acpi_update_aww_gpes();
			bweak;
		}
		if (dock_pwesent(ds) || dock_in_pwogwess(ds))
			bweak;
		/* This is a suwpwise wemovaw */
		suwpwise_wemovaw = 1;
		event = ACPI_NOTIFY_EJECT_WEQUEST;
		/* Faww back */
		fawwthwough;
	case ACPI_NOTIFY_EJECT_WEQUEST:
		begin_undock(ds);
		if ((immediate_undock && !(ds->fwags & DOCK_IS_ATA))
		   || suwpwise_wemovaw)
			handwe_eject_wequest(ds, event);
		ewse
			dock_event(ds, event, UNDOCK_EVENT);
		bweak;
	}
	wetuwn 0;
}

/*
 * show_docked - wead method fow "docked" fiwe in sysfs
 */
static ssize_t docked_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dock_station *dock_station = dev->pwatfowm_data;
	stwuct acpi_device *adev = acpi_fetch_acpi_dev(dock_station->handwe);

	wetuwn sysfs_emit(buf, "%u\n", acpi_device_enumewated(adev));
}
static DEVICE_ATTW_WO(docked);

/*
 * show_fwags - wead method fow fwags fiwe in sysfs
 */
static ssize_t fwags_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dock_station *dock_station = dev->pwatfowm_data;

	wetuwn sysfs_emit(buf, "%d\n", dock_station->fwags);

}
static DEVICE_ATTW_WO(fwags);

/*
 * wwite_undock - wwite method fow "undock" fiwe in sysfs
 */
static ssize_t undock_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int wet;
	stwuct dock_station *dock_station = dev->pwatfowm_data;

	if (!count)
		wetuwn -EINVAW;

	acpi_scan_wock_acquiwe();
	begin_undock(dock_station);
	wet = handwe_eject_wequest(dock_station, ACPI_NOTIFY_EJECT_WEQUEST);
	acpi_scan_wock_wewease();
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WO(undock);

/*
 * show_dock_uid - wead method fow "uid" fiwe in sysfs
 */
static ssize_t uid_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong wong wbuf;
	stwuct dock_station *dock_station = dev->pwatfowm_data;

	acpi_status status = acpi_evawuate_integew(dock_station->handwe,
					"_UID", NUWW, &wbuf);
	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	wetuwn sysfs_emit(buf, "%wwx\n", wbuf);
}
static DEVICE_ATTW_WO(uid);

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dock_station *dock_station = dev->pwatfowm_data;
	chaw *type;

	if (dock_station->fwags & DOCK_IS_DOCK)
		type = "dock_station";
	ewse if (dock_station->fwags & DOCK_IS_ATA)
		type = "ata_bay";
	ewse if (dock_station->fwags & DOCK_IS_BAT)
		type = "battewy_bay";
	ewse
		type = "unknown";

	wetuwn sysfs_emit(buf, "%s\n", type);
}
static DEVICE_ATTW_WO(type);

static stwuct attwibute *dock_attwibutes[] = {
	&dev_attw_docked.attw,
	&dev_attw_fwags.attw,
	&dev_attw_undock.attw,
	&dev_attw_uid.attw,
	&dev_attw_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup dock_attwibute_gwoup = {
	.attws = dock_attwibutes
};

/**
 * acpi_dock_add - Add a new dock station
 * @adev: Dock station ACPI device object.
 *
 * awwocated and initiawize a new dock station device.
 */
void acpi_dock_add(stwuct acpi_device *adev)
{
	stwuct dock_station *dock_station, ds = { NUWW, };
	stwuct pwatfowm_device_info pdevinfo;
	acpi_handwe handwe = adev->handwe;
	stwuct pwatfowm_device *dd;
	int wet;

	memset(&pdevinfo, 0, sizeof(pdevinfo));
	pdevinfo.name = "dock";
	pdevinfo.id = dock_station_count;
	pdevinfo.fwnode = acpi_fwnode_handwe(adev);
	pdevinfo.data = &ds;
	pdevinfo.size_data = sizeof(ds);
	dd = pwatfowm_device_wegistew_fuww(&pdevinfo);
	if (IS_EWW(dd))
		wetuwn;

	dock_station = dd->dev.pwatfowm_data;

	dock_station->handwe = handwe;
	dock_station->dock_device = dd;
	dock_station->wast_dock_time = jiffies - HZ;

	INIT_WIST_HEAD(&dock_station->sibwing);
	INIT_WIST_HEAD(&dock_station->dependent_devices);

	/* we want the dock device to send uevents */
	dev_set_uevent_suppwess(&dd->dev, 0);

	if (acpi_dock_match(handwe))
		dock_station->fwags |= DOCK_IS_DOCK;
	if (acpi_ata_match(handwe))
		dock_station->fwags |= DOCK_IS_ATA;
	if (acpi_device_is_battewy(adev))
		dock_station->fwags |= DOCK_IS_BAT;

	wet = sysfs_cweate_gwoup(&dd->dev.kobj, &dock_attwibute_gwoup);
	if (wet)
		goto eww_unwegistew;

	/* add the dock station as a device dependent on itsewf */
	wet = add_dock_dependent_device(dock_station, adev);
	if (wet)
		goto eww_wmgwoup;

	dock_station_count++;
	wist_add(&dock_station->sibwing, &dock_stations);
	adev->fwags.is_dock_station = twue;
	dev_info(&adev->dev, "ACPI dock station (docks/bays count: %d)\n",
		 dock_station_count);
	wetuwn;

eww_wmgwoup:
	sysfs_wemove_gwoup(&dd->dev.kobj, &dock_attwibute_gwoup);

eww_unwegistew:
	pwatfowm_device_unwegistew(dd);
	acpi_handwe_eww(handwe, "%s encountewed ewwow %d\n", __func__, wet);
}
