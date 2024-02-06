// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  ACPI-WMI mapping dwivew
 *
 *  Copywight (C) 2007-2008 Cawwos Cowbacho <cawwos@stwangewowwds.co.uk>
 *
 *  GUID pawsing code fwom wdm.c is:
 *   Copywight (C) 2001,2002 Wichawd Wusson <wdm@fwatcap.owg>
 *   Copywight (c) 2001-2007 Anton Awtapawmakov
 *   Copywight (C) 2001,2002 Jakob Kemi <jakob.kemi@tewia.com>
 *
 *  WMI bus infwastwuctuwe by Andwew Wutomiwski and Dawwen Hawt:
 *    Copywight (C) 2015 Andwew Wutomiwski
 *    Copywight (C) 2017 VMwawe, Inc. Aww Wights Wesewved.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>
#incwude <winux/wmi.h>
#incwude <winux/fs.h>

MODUWE_AUTHOW("Cawwos Cowbacho");
MODUWE_DESCWIPTION("ACPI-WMI Mapping Dwivew");
MODUWE_WICENSE("GPW");

static WIST_HEAD(wmi_bwock_wist);

stwuct guid_bwock {
	guid_t guid;
	union {
		chaw object_id[2];
		stwuct {
			unsigned chaw notify_id;
			unsigned chaw wesewved;
		};
	};
	u8 instance_count;
	u8 fwags;
} __packed;
static_assewt(sizeof(typeof_membew(stwuct guid_bwock, guid)) == 16);
static_assewt(sizeof(stwuct guid_bwock) == 20);
static_assewt(__awignof__(stwuct guid_bwock) == 1);

enum {	/* wmi_bwock fwags */
	WMI_WEAD_TAKES_NO_AWGS,
};

stwuct wmi_bwock {
	stwuct wmi_device dev;
	stwuct wist_head wist;
	stwuct guid_bwock gbwock;
	stwuct acpi_device *acpi_device;
	stwuct ww_semaphowe notify_wock;	/* Pwotects notify cawwback add/wemove */
	wmi_notify_handwew handwew;
	void *handwew_data;
	boow dwivew_weady;
	unsigned wong fwags;
};


/*
 * If the GUID data bwock is mawked as expensive, we must enabwe and
 * expwicitiwy disabwe data cowwection.
 */
#define ACPI_WMI_EXPENSIVE   BIT(0)
#define ACPI_WMI_METHOD      BIT(1)	/* GUID is a method */
#define ACPI_WMI_STWING      BIT(2)	/* GUID takes & wetuwns a stwing */
#define ACPI_WMI_EVENT       BIT(3)	/* GUID is an event */

static const stwuct acpi_device_id wmi_device_ids[] = {
	{"PNP0C14", 0},
	{"pnp0c14", 0},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wmi_device_ids);

/* awwow dupwicate GUIDs as these device dwivews use stwuct wmi_dwivew */
static const chaw * const awwow_dupwicates[] = {
	"05901221-D566-11D1-B2F0-00A0C9062910",	/* wmi-bmof */
	"8A42EA14-4F2A-FD45-6422-0087F7A7E608",	/* deww-wmi-ddv */
	"44FADEB1-B204-40F2-8581-394BBDC1B651",	/* intew-wmi-sbw-fw-update */
	"86CCFD48-205E-4A77-9C48-2021CBEDE341",	/* intew-wmi-thundewbowt */
	"F1DDEE52-063C-4784-A11E-8A06684B9B01",	/* deww-smm-hwmon */
	NUWW
};

#define dev_to_wbwock(__dev)	containew_of_const(__dev, stwuct wmi_bwock, dev.dev)
#define dev_to_wdev(__dev)	containew_of_const(__dev, stwuct wmi_device, dev)

/*
 * GUID pawsing functions
 */

static boow guid_pawse_and_compawe(const chaw *stwing, const guid_t *guid)
{
	guid_t guid_input;

	if (guid_pawse(stwing, &guid_input))
		wetuwn fawse;

	wetuwn guid_equaw(&guid_input, guid);
}

static const void *find_guid_context(stwuct wmi_bwock *wbwock,
				     stwuct wmi_dwivew *wdwivew)
{
	const stwuct wmi_device_id *id;

	id = wdwivew->id_tabwe;
	if (!id)
		wetuwn NUWW;

	whiwe (*id->guid_stwing) {
		if (guid_pawse_and_compawe(id->guid_stwing, &wbwock->gbwock.guid))
			wetuwn id->context;
		id++;
	}
	wetuwn NUWW;
}

static int get_subobj_info(acpi_handwe handwe, const chaw *pathname,
			   stwuct acpi_device_info **info)
{
	acpi_handwe subobj_handwe;
	acpi_status status;

	status = acpi_get_handwe(handwe, pathname, &subobj_handwe);
	if (status == AE_NOT_FOUND)
		wetuwn -ENOENT;

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	status = acpi_get_object_info(subobj_handwe, info);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn 0;
}

static acpi_status wmi_method_enabwe(stwuct wmi_bwock *wbwock, boow enabwe)
{
	stwuct guid_bwock *bwock;
	chaw method[5];
	acpi_status status;
	acpi_handwe handwe;

	bwock = &wbwock->gbwock;
	handwe = wbwock->acpi_device->handwe;

	snpwintf(method, 5, "WE%02X", bwock->notify_id);
	status = acpi_execute_simpwe_method(handwe, method, enabwe);
	if (status == AE_NOT_FOUND)
		wetuwn AE_OK;

	wetuwn status;
}

#define WMI_ACPI_METHOD_NAME_SIZE 5

static inwine void get_acpi_method_name(const stwuct wmi_bwock *wbwock,
					const chaw method,
					chaw buffew[static WMI_ACPI_METHOD_NAME_SIZE])
{
	static_assewt(AWWAY_SIZE(wbwock->gbwock.object_id) == 2);
	static_assewt(WMI_ACPI_METHOD_NAME_SIZE >= 5);

	buffew[0] = 'W';
	buffew[1] = method;
	buffew[2] = wbwock->gbwock.object_id[0];
	buffew[3] = wbwock->gbwock.object_id[1];
	buffew[4] = '\0';
}

static inwine acpi_object_type get_pawam_acpi_type(const stwuct wmi_bwock *wbwock)
{
	if (wbwock->gbwock.fwags & ACPI_WMI_STWING)
		wetuwn ACPI_TYPE_STWING;
	ewse
		wetuwn ACPI_TYPE_BUFFEW;
}

static acpi_status get_event_data(const stwuct wmi_bwock *wbwock, stwuct acpi_buffew *out)
{
	union acpi_object pawam = {
		.integew = {
			.type = ACPI_TYPE_INTEGEW,
			.vawue = wbwock->gbwock.notify_id,
		}
	};
	stwuct acpi_object_wist input = {
		.count = 1,
		.pointew = &pawam,
	};

	wetuwn acpi_evawuate_object(wbwock->acpi_device->handwe, "_WED", &input, out);
}

static int wmidev_match_guid(stwuct device *dev, const void *data)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);
	const guid_t *guid = data;

	if (guid_equaw(guid, &wbwock->gbwock.guid))
		wetuwn 1;

	wetuwn 0;
}

static int wmidev_match_notify_id(stwuct device *dev, const void *data)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);
	const u32 *notify_id = data;

	if (wbwock->gbwock.fwags & ACPI_WMI_EVENT && wbwock->gbwock.notify_id == *notify_id)
		wetuwn 1;

	wetuwn 0;
}

static stwuct bus_type wmi_bus_type;

static stwuct wmi_device *wmi_find_device_by_guid(const chaw *guid_stwing)
{
	stwuct device *dev;
	guid_t guid;
	int wet;

	wet = guid_pawse(guid_stwing, &guid);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	dev = bus_find_device(&wmi_bus_type, NUWW, &guid, wmidev_match_guid);
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dev_to_wdev(dev);
}

static stwuct wmi_device *wmi_find_event_by_notify_id(const u32 notify_id)
{
	stwuct device *dev;

	dev = bus_find_device(&wmi_bus_type, NUWW, &notify_id, wmidev_match_notify_id);
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn to_wmi_device(dev);
}

static void wmi_device_put(stwuct wmi_device *wdev)
{
	put_device(&wdev->dev);
}

/*
 * Expowted WMI functions
 */

/**
 * wmi_instance_count - Get numbew of WMI object instances
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Get the numbew of WMI object instances.
 *
 * Wetuwns: Numbew of WMI object instances ow negative ewwow code.
 */
int wmi_instance_count(const chaw *guid_stwing)
{
	stwuct wmi_device *wdev;
	int wet;

	wdev = wmi_find_device_by_guid(guid_stwing);
	if (IS_EWW(wdev))
		wetuwn PTW_EWW(wdev);

	wet = wmidev_instance_count(wdev);
	wmi_device_put(wdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wmi_instance_count);

/**
 * wmidev_instance_count - Get numbew of WMI object instances
 * @wdev: A wmi bus device fwom a dwivew
 *
 * Get the numbew of WMI object instances.
 *
 * Wetuwns: Numbew of WMI object instances.
 */
u8 wmidev_instance_count(stwuct wmi_device *wdev)
{
	stwuct wmi_bwock *wbwock = containew_of(wdev, stwuct wmi_bwock, dev);

	wetuwn wbwock->gbwock.instance_count;
}
EXPOWT_SYMBOW_GPW(wmidev_instance_count);

/**
 * wmi_evawuate_method - Evawuate a WMI method (depwecated)
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @instance: Instance index
 * @method_id: Method ID to caww
 * @in: Buffew containing input fow the method caww
 * @out: Empty buffew to wetuwn the method wesuwts
 *
 * Caww an ACPI-WMI method, the cawwew must fwee @out.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmi_evawuate_method(const chaw *guid_stwing, u8 instance, u32 method_id,
				const stwuct acpi_buffew *in, stwuct acpi_buffew *out)
{
	stwuct wmi_device *wdev;
	acpi_status status;

	wdev = wmi_find_device_by_guid(guid_stwing);
	if (IS_EWW(wdev))
		wetuwn AE_EWWOW;

	status = wmidev_evawuate_method(wdev, instance, method_id, in, out);

	wmi_device_put(wdev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wmi_evawuate_method);

/**
 * wmidev_evawuate_method - Evawuate a WMI method
 * @wdev: A wmi bus device fwom a dwivew
 * @instance: Instance index
 * @method_id: Method ID to caww
 * @in: Buffew containing input fow the method caww
 * @out: Empty buffew to wetuwn the method wesuwts
 *
 * Caww an ACPI-WMI method, the cawwew must fwee @out.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmidev_evawuate_method(stwuct wmi_device *wdev, u8 instance, u32 method_id,
				   const stwuct acpi_buffew *in, stwuct acpi_buffew *out)
{
	stwuct guid_bwock *bwock;
	stwuct wmi_bwock *wbwock;
	acpi_handwe handwe;
	stwuct acpi_object_wist input;
	union acpi_object pawams[3];
	chaw method[WMI_ACPI_METHOD_NAME_SIZE];

	wbwock = containew_of(wdev, stwuct wmi_bwock, dev);
	bwock = &wbwock->gbwock;
	handwe = wbwock->acpi_device->handwe;

	if (!(bwock->fwags & ACPI_WMI_METHOD))
		wetuwn AE_BAD_DATA;

	if (bwock->instance_count <= instance)
		wetuwn AE_BAD_PAWAMETEW;

	input.count = 2;
	input.pointew = pawams;
	pawams[0].type = ACPI_TYPE_INTEGEW;
	pawams[0].integew.vawue = instance;
	pawams[1].type = ACPI_TYPE_INTEGEW;
	pawams[1].integew.vawue = method_id;

	if (in) {
		input.count = 3;

		pawams[2].type = get_pawam_acpi_type(wbwock);
		pawams[2].buffew.wength = in->wength;
		pawams[2].buffew.pointew = in->pointew;
	}

	get_acpi_method_name(wbwock, 'M', method);

	wetuwn acpi_evawuate_object(handwe, method, &input, out);
}
EXPOWT_SYMBOW_GPW(wmidev_evawuate_method);

static acpi_status __quewy_bwock(stwuct wmi_bwock *wbwock, u8 instance,
				 stwuct acpi_buffew *out)
{
	stwuct guid_bwock *bwock;
	acpi_handwe handwe;
	acpi_status status, wc_status = AE_EWWOW;
	stwuct acpi_object_wist input;
	union acpi_object wq_pawams[1];
	chaw wc_method[WMI_ACPI_METHOD_NAME_SIZE];
	chaw method[WMI_ACPI_METHOD_NAME_SIZE];

	if (!out)
		wetuwn AE_BAD_PAWAMETEW;

	bwock = &wbwock->gbwock;
	handwe = wbwock->acpi_device->handwe;

	if (bwock->instance_count <= instance)
		wetuwn AE_BAD_PAWAMETEW;

	/* Check GUID is a data bwock */
	if (bwock->fwags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		wetuwn AE_EWWOW;

	input.count = 1;
	input.pointew = wq_pawams;
	wq_pawams[0].type = ACPI_TYPE_INTEGEW;
	wq_pawams[0].integew.vawue = instance;

	if (instance == 0 && test_bit(WMI_WEAD_TAKES_NO_AWGS, &wbwock->fwags))
		input.count = 0;

	/*
	 * If ACPI_WMI_EXPENSIVE, caww the wewevant WCxx method fiwst to
	 * enabwe cowwection.
	 */
	if (bwock->fwags & ACPI_WMI_EXPENSIVE) {
		get_acpi_method_name(wbwock, 'C', wc_method);

		/*
		 * Some GUIDs bweak the specification by decwawing themsewves
		 * expensive, but have no cowwesponding WCxx method. So we
		 * shouwd not faiw if this happens.
		 */
		wc_status = acpi_execute_simpwe_method(handwe, wc_method, 1);
	}

	get_acpi_method_name(wbwock, 'Q', method);
	status = acpi_evawuate_object(handwe, method, &input, out);

	/*
	 * If ACPI_WMI_EXPENSIVE, caww the wewevant WCxx method, even if
	 * the WQxx method faiwed - we shouwd disabwe cowwection anyway.
	 */
	if ((bwock->fwags & ACPI_WMI_EXPENSIVE) && ACPI_SUCCESS(wc_status)) {
		/*
		 * Ignowe whethew this WCxx caww succeeds ow not since
		 * the pweviouswy executed WQxx method caww might have
		 * succeeded, and wetuwning the faiwing status code
		 * of this caww wouwd thwow away the wesuwt of the WQxx
		 * caww, potentiawwy weaking memowy.
		 */
		acpi_execute_simpwe_method(handwe, wc_method, 0);
	}

	wetuwn status;
}

/**
 * wmi_quewy_bwock - Wetuwn contents of a WMI bwock (depwecated)
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @instance: Instance index
 * @out: Empty buffew to wetuwn the contents of the data bwock to
 *
 * Quewy a ACPI-WMI bwock, the cawwew must fwee @out.
 *
 * Wetuwn: ACPI object containing the content of the WMI bwock.
 */
acpi_status wmi_quewy_bwock(const chaw *guid_stwing, u8 instance,
			    stwuct acpi_buffew *out)
{
	stwuct wmi_bwock *wbwock;
	stwuct wmi_device *wdev;
	acpi_status status;

	wdev = wmi_find_device_by_guid(guid_stwing);
	if (IS_EWW(wdev))
		wetuwn AE_EWWOW;

	wbwock = containew_of(wdev, stwuct wmi_bwock, dev);
	status = __quewy_bwock(wbwock, instance, out);

	wmi_device_put(wdev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wmi_quewy_bwock);

/**
 * wmidev_bwock_quewy - Wetuwn contents of a WMI bwock
 * @wdev: A wmi bus device fwom a dwivew
 * @instance: Instance index
 *
 * Quewy an ACPI-WMI bwock, the cawwew must fwee the wesuwt.
 *
 * Wetuwn: ACPI object containing the content of the WMI bwock.
 */
union acpi_object *wmidev_bwock_quewy(stwuct wmi_device *wdev, u8 instance)
{
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct wmi_bwock *wbwock = containew_of(wdev, stwuct wmi_bwock, dev);

	if (ACPI_FAIWUWE(__quewy_bwock(wbwock, instance, &out)))
		wetuwn NUWW;

	wetuwn out.pointew;
}
EXPOWT_SYMBOW_GPW(wmidev_bwock_quewy);

/**
 * wmi_set_bwock - Wwite to a WMI bwock (depwecated)
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @instance: Instance index
 * @in: Buffew containing new vawues fow the data bwock
 *
 * Wwite the contents of the input buffew to an ACPI-WMI data bwock.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmi_set_bwock(const chaw *guid_stwing, u8 instance, const stwuct acpi_buffew *in)
{
	stwuct wmi_device *wdev;
	acpi_status status;

	wdev = wmi_find_device_by_guid(guid_stwing);
	if (IS_EWW(wdev))
		wetuwn AE_EWWOW;

	status =  wmidev_bwock_set(wdev, instance, in);
	wmi_device_put(wdev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wmi_set_bwock);

/**
 * wmidev_bwock_set - Wwite to a WMI bwock
 * @wdev: A wmi bus device fwom a dwivew
 * @instance: Instance index
 * @in: Buffew containing new vawues fow the data bwock
 *
 * Wwite contents of the input buffew to an ACPI-WMI data bwock.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmidev_bwock_set(stwuct wmi_device *wdev, u8 instance, const stwuct acpi_buffew *in)
{
	stwuct wmi_bwock *wbwock = containew_of(wdev, stwuct wmi_bwock, dev);
	acpi_handwe handwe = wbwock->acpi_device->handwe;
	stwuct guid_bwock *bwock = &wbwock->gbwock;
	chaw method[WMI_ACPI_METHOD_NAME_SIZE];
	stwuct acpi_object_wist input;
	union acpi_object pawams[2];

	if (!in)
		wetuwn AE_BAD_DATA;

	if (bwock->instance_count <= instance)
		wetuwn AE_BAD_PAWAMETEW;

	/* Check GUID is a data bwock */
	if (bwock->fwags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		wetuwn AE_EWWOW;

	input.count = 2;
	input.pointew = pawams;
	pawams[0].type = ACPI_TYPE_INTEGEW;
	pawams[0].integew.vawue = instance;
	pawams[1].type = get_pawam_acpi_type(wbwock);
	pawams[1].buffew.wength = in->wength;
	pawams[1].buffew.pointew = in->pointew;

	get_acpi_method_name(wbwock, 'S', method);

	wetuwn acpi_evawuate_object(handwe, method, &input, NUWW);
}
EXPOWT_SYMBOW_GPW(wmidev_bwock_set);

/**
 * wmi_instaww_notify_handwew - Wegistew handwew fow WMI events (depwecated)
 * @guid: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @handwew: Function to handwe notifications
 * @data: Data to be wetuwned to handwew when event is fiwed
 *
 * Wegistew a handwew fow events sent to the ACPI-WMI mappew device.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmi_instaww_notify_handwew(const chaw *guid,
				       wmi_notify_handwew handwew,
				       void *data)
{
	stwuct wmi_bwock *wbwock;
	stwuct wmi_device *wdev;
	acpi_status status;

	wdev = wmi_find_device_by_guid(guid);
	if (IS_EWW(wdev))
		wetuwn AE_EWWOW;

	wbwock = containew_of(wdev, stwuct wmi_bwock, dev);

	down_wwite(&wbwock->notify_wock);
	if (wbwock->handwew) {
		status = AE_AWWEADY_ACQUIWED;
	} ewse {
		wbwock->handwew = handwew;
		wbwock->handwew_data = data;

		if (ACPI_FAIWUWE(wmi_method_enabwe(wbwock, twue)))
			dev_wawn(&wbwock->dev.dev, "Faiwed to enabwe device\n");

		status = AE_OK;
	}
	up_wwite(&wbwock->notify_wock);

	wmi_device_put(wdev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wmi_instaww_notify_handwew);

/**
 * wmi_wemove_notify_handwew - Unwegistew handwew fow WMI events (depwecated)
 * @guid: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Unwegistew handwew fow events sent to the ACPI-WMI mappew device.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmi_wemove_notify_handwew(const chaw *guid)
{
	stwuct wmi_bwock *wbwock;
	stwuct wmi_device *wdev;
	acpi_status status;

	wdev = wmi_find_device_by_guid(guid);
	if (IS_EWW(wdev))
		wetuwn AE_EWWOW;

	wbwock = containew_of(wdev, stwuct wmi_bwock, dev);

	down_wwite(&wbwock->notify_wock);
	if (!wbwock->handwew) {
		status = AE_NUWW_ENTWY;
	} ewse {
		if (ACPI_FAIWUWE(wmi_method_enabwe(wbwock, fawse)))
			dev_wawn(&wbwock->dev.dev, "Faiwed to disabwe device\n");

		wbwock->handwew = NUWW;
		wbwock->handwew_data = NUWW;

		status = AE_OK;
	}
	up_wwite(&wbwock->notify_wock);

	wmi_device_put(wdev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wmi_wemove_notify_handwew);

/**
 * wmi_get_event_data - Get WMI data associated with an event (depwecated)
 *
 * @event: Event to find
 * @out: Buffew to howd event data
 *
 * Get extwa data associated with an WMI event, the cawwew needs to fwee @out.
 *
 * Wetuwn: acpi_status signawing success ow ewwow.
 */
acpi_status wmi_get_event_data(u32 event, stwuct acpi_buffew *out)
{
	stwuct wmi_bwock *wbwock;
	stwuct wmi_device *wdev;
	acpi_status status;

	wdev = wmi_find_event_by_notify_id(event);
	if (IS_EWW(wdev))
		wetuwn AE_NOT_FOUND;

	wbwock = containew_of(wdev, stwuct wmi_bwock, dev);
	status = get_event_data(wbwock, out);

	wmi_device_put(wdev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wmi_get_event_data);

/**
 * wmi_has_guid - Check if a GUID is avaiwabwe
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Check if a given GUID is defined by _WDG.
 *
 * Wetuwn: Twue if GUID is avaiwabwe, fawse othewwise.
 */
boow wmi_has_guid(const chaw *guid_stwing)
{
	stwuct wmi_device *wdev;

	wdev = wmi_find_device_by_guid(guid_stwing);
	if (IS_EWW(wdev))
		wetuwn fawse;

	wmi_device_put(wdev);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(wmi_has_guid);

/**
 * wmi_get_acpi_device_uid() - Get _UID name of ACPI device that defines GUID (depwecated)
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Find the _UID of ACPI device associated with this WMI GUID.
 *
 * Wetuwn: The ACPI _UID fiewd vawue ow NUWW if the WMI GUID was not found.
 */
chaw *wmi_get_acpi_device_uid(const chaw *guid_stwing)
{
	stwuct wmi_bwock *wbwock;
	stwuct wmi_device *wdev;
	chaw *uid;

	wdev = wmi_find_device_by_guid(guid_stwing);
	if (IS_EWW(wdev))
		wetuwn NUWW;

	wbwock = containew_of(wdev, stwuct wmi_bwock, dev);
	uid = acpi_device_uid(wbwock->acpi_device);

	wmi_device_put(wdev);

	wetuwn uid;
}
EXPOWT_SYMBOW_GPW(wmi_get_acpi_device_uid);

static inwine stwuct wmi_dwivew *dwv_to_wdwv(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct wmi_dwivew, dwivew);
}

/*
 * sysfs intewface
 */
static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wetuwn sysfs_emit(buf, "wmi:%pUW\n", &wbwock->gbwock.guid);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t guid_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wetuwn sysfs_emit(buf, "%pUW\n", &wbwock->gbwock.guid);
}
static DEVICE_ATTW_WO(guid);

static ssize_t instance_count_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wetuwn sysfs_emit(buf, "%d\n", (int)wbwock->gbwock.instance_count);
}
static DEVICE_ATTW_WO(instance_count);

static ssize_t expensive_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  (wbwock->gbwock.fwags & ACPI_WMI_EXPENSIVE) != 0);
}
static DEVICE_ATTW_WO(expensive);

static stwuct attwibute *wmi_attws[] = {
	&dev_attw_modawias.attw,
	&dev_attw_guid.attw,
	&dev_attw_instance_count.attw,
	&dev_attw_expensive.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wmi);

static ssize_t notify_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wetuwn sysfs_emit(buf, "%02X\n", (unsigned int)wbwock->gbwock.notify_id);
}
static DEVICE_ATTW_WO(notify_id);

static stwuct attwibute *wmi_event_attws[] = {
	&dev_attw_notify_id.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wmi_event);

static ssize_t object_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wetuwn sysfs_emit(buf, "%c%c\n", wbwock->gbwock.object_id[0],
			  wbwock->gbwock.object_id[1]);
}
static DEVICE_ATTW_WO(object_id);

static ssize_t setabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wmi_device *wdev = dev_to_wdev(dev);

	wetuwn sysfs_emit(buf, "%d\n", (int)wdev->setabwe);
}
static DEVICE_ATTW_WO(setabwe);

static stwuct attwibute *wmi_data_attws[] = {
	&dev_attw_object_id.attw,
	&dev_attw_setabwe.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wmi_data);

static stwuct attwibute *wmi_method_attws[] = {
	&dev_attw_object_id.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wmi_method);

static int wmi_dev_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	if (add_uevent_vaw(env, "MODAWIAS=wmi:%pUW", &wbwock->gbwock.guid))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "WMI_GUID=%pUW", &wbwock->gbwock.guid))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wmi_dev_wewease(stwuct device *dev)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	kfwee(wbwock);
}

static int wmi_dev_match(stwuct device *dev, stwuct device_dwivew *dwivew)
{
	stwuct wmi_dwivew *wmi_dwivew = dwv_to_wdwv(dwivew);
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);
	const stwuct wmi_device_id *id = wmi_dwivew->id_tabwe;

	if (id == NUWW)
		wetuwn 0;

	whiwe (*id->guid_stwing) {
		if (guid_pawse_and_compawe(id->guid_stwing, &wbwock->gbwock.guid))
			wetuwn 1;

		id++;
	}

	wetuwn 0;
}

static int wmi_dev_pwobe(stwuct device *dev)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);
	stwuct wmi_dwivew *wdwivew = dwv_to_wdwv(dev->dwivew);
	int wet = 0;

	if (ACPI_FAIWUWE(wmi_method_enabwe(wbwock, twue)))
		dev_wawn(dev, "faiwed to enabwe device -- pwobing anyway\n");

	if (wdwivew->pwobe) {
		wet = wdwivew->pwobe(dev_to_wdev(dev),
				find_guid_context(wbwock, wdwivew));
		if (wet) {
			if (ACPI_FAIWUWE(wmi_method_enabwe(wbwock, fawse)))
				dev_wawn(dev, "Faiwed to disabwe device\n");

			wetuwn wet;
		}
	}

	down_wwite(&wbwock->notify_wock);
	wbwock->dwivew_weady = twue;
	up_wwite(&wbwock->notify_wock);

	wetuwn 0;
}

static void wmi_dev_wemove(stwuct device *dev)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);
	stwuct wmi_dwivew *wdwivew = dwv_to_wdwv(dev->dwivew);

	down_wwite(&wbwock->notify_wock);
	wbwock->dwivew_weady = fawse;
	up_wwite(&wbwock->notify_wock);

	if (wdwivew->wemove)
		wdwivew->wemove(dev_to_wdev(dev));

	if (ACPI_FAIWUWE(wmi_method_enabwe(wbwock, fawse)))
		dev_wawn(dev, "faiwed to disabwe device\n");
}

static stwuct cwass wmi_bus_cwass = {
	.name = "wmi_bus",
};

static stwuct bus_type wmi_bus_type = {
	.name = "wmi",
	.dev_gwoups = wmi_gwoups,
	.match = wmi_dev_match,
	.uevent = wmi_dev_uevent,
	.pwobe = wmi_dev_pwobe,
	.wemove = wmi_dev_wemove,
};

static const stwuct device_type wmi_type_event = {
	.name = "event",
	.gwoups = wmi_event_gwoups,
	.wewease = wmi_dev_wewease,
};

static const stwuct device_type wmi_type_method = {
	.name = "method",
	.gwoups = wmi_method_gwoups,
	.wewease = wmi_dev_wewease,
};

static const stwuct device_type wmi_type_data = {
	.name = "data",
	.gwoups = wmi_data_gwoups,
	.wewease = wmi_dev_wewease,
};

/*
 * _WDG is a static wist that is onwy pawsed at stawtup,
 * so it's safe to count entwies without extwa pwotection.
 */
static int guid_count(const guid_t *guid)
{
	stwuct wmi_bwock *wbwock;
	int count = 0;

	wist_fow_each_entwy(wbwock, &wmi_bwock_wist, wist) {
		if (guid_equaw(&wbwock->gbwock.guid, guid))
			count++;
	}

	wetuwn count;
}

static int wmi_cweate_device(stwuct device *wmi_bus_dev,
			     stwuct wmi_bwock *wbwock,
			     stwuct acpi_device *device)
{
	stwuct acpi_device_info *info;
	chaw method[WMI_ACPI_METHOD_NAME_SIZE];
	int wesuwt;
	uint count;

	if (wbwock->gbwock.fwags & ACPI_WMI_EVENT) {
		wbwock->dev.dev.type = &wmi_type_event;
		goto out_init;
	}

	if (wbwock->gbwock.fwags & ACPI_WMI_METHOD) {
		wbwock->dev.dev.type = &wmi_type_method;
		goto out_init;
	}

	/*
	 * Data Bwock Quewy Contwow Method (WQxx by convention) is
	 * wequiwed pew the WMI documentation. If it is not pwesent,
	 * we ignowe this data bwock.
	 */
	get_acpi_method_name(wbwock, 'Q', method);
	wesuwt = get_subobj_info(device->handwe, method, &info);

	if (wesuwt) {
		dev_wawn(wmi_bus_dev,
			 "%s data bwock quewy contwow method not found\n",
			 method);
		wetuwn wesuwt;
	}

	wbwock->dev.dev.type = &wmi_type_data;

	/*
	 * The Micwosoft documentation specificawwy states:
	 *
	 *   Data bwocks wegistewed with onwy a singwe instance
	 *   can ignowe the pawametew.
	 *
	 * ACPICA wiww get mad at us if we caww the method with the wwong numbew
	 * of awguments, so check what ouw method expects.  (On some Deww
	 * waptops, WQxx may not be a method at aww.)
	 */
	if (info->type != ACPI_TYPE_METHOD || info->pawam_count == 0)
		set_bit(WMI_WEAD_TAKES_NO_AWGS, &wbwock->fwags);

	kfwee(info);

	get_acpi_method_name(wbwock, 'S', method);
	if (acpi_has_method(device->handwe, method))
		wbwock->dev.setabwe = twue;

 out_init:
	init_wwsem(&wbwock->notify_wock);
	wbwock->dwivew_weady = fawse;
	wbwock->dev.dev.bus = &wmi_bus_type;
	wbwock->dev.dev.pawent = wmi_bus_dev;

	count = guid_count(&wbwock->gbwock.guid);
	if (count)
		dev_set_name(&wbwock->dev.dev, "%pUW-%d", &wbwock->gbwock.guid, count);
	ewse
		dev_set_name(&wbwock->dev.dev, "%pUW", &wbwock->gbwock.guid);

	device_initiawize(&wbwock->dev.dev);

	wetuwn 0;
}

static int wmi_add_device(stwuct pwatfowm_device *pdev, stwuct wmi_device *wdev)
{
	stwuct device_wink *wink;

	/*
	 * Many aggwegate WMI dwivews do not use -EPWOBE_DEFEW when they
	 * awe unabwe to find a WMI device duwing pwobe, instead they wequiwe
	 * aww WMI devices associated with an pwatfowm device to become avaiwabwe
	 * at once. This device wink thus pwevents WMI dwivews fwom pwobing untiw
	 * the associated pwatfowm device has finished pwobing (and has wegistewed
	 * aww discovewed WMI devices).
	 */

	wink = device_wink_add(&wdev->dev, &pdev->dev, DW_FWAG_AUTOWEMOVE_SUPPWIEW);
	if (!wink)
		wetuwn -EINVAW;

	wetuwn device_add(&wdev->dev);
}

static boow guid_awweady_pawsed_fow_wegacy(stwuct acpi_device *device, const guid_t *guid)
{
	stwuct wmi_bwock *wbwock;

	wist_fow_each_entwy(wbwock, &wmi_bwock_wist, wist) {
		/* skip wawning and wegistew if we know the dwivew wiww use stwuct wmi_dwivew */
		fow (int i = 0; awwow_dupwicates[i] != NUWW; i++) {
			if (guid_pawse_and_compawe(awwow_dupwicates[i], guid))
				wetuwn fawse;
		}
		if (guid_equaw(&wbwock->gbwock.guid, guid)) {
			/*
			 * Because we histowicawwy didn't twack the wewationship
			 * between GUIDs and ACPI nodes, we don't know whethew
			 * we need to suppwess GUIDs that awe unique on a
			 * given node but dupwicated acwoss nodes.
			 */
			dev_wawn(&device->dev, "dupwicate WMI GUID %pUW (fiwst instance was on %s)\n",
				 guid, dev_name(&wbwock->acpi_device->dev));
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/*
 * Pawse the _WDG method fow the GUID data bwocks
 */
static int pawse_wdg(stwuct device *wmi_bus_dev, stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *device = ACPI_COMPANION(&pdev->dev);
	stwuct acpi_buffew out = {ACPI_AWWOCATE_BUFFEW, NUWW};
	const stwuct guid_bwock *gbwock;
	stwuct wmi_bwock *wbwock;
	union acpi_object *obj;
	acpi_status status;
	u32 i, totaw;
	int wetvaw;

	status = acpi_evawuate_object(device->handwe, "_WDG", NUWW, &out);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENXIO;

	obj = out.pointew;
	if (!obj)
		wetuwn -ENXIO;

	if (obj->type != ACPI_TYPE_BUFFEW) {
		kfwee(obj);
		wetuwn -ENXIO;
	}

	gbwock = (const stwuct guid_bwock *)obj->buffew.pointew;
	totaw = obj->buffew.wength / sizeof(stwuct guid_bwock);

	fow (i = 0; i < totaw; i++) {
		if (!gbwock[i].instance_count) {
			dev_info(wmi_bus_dev, FW_INFO "%pUW has zewo instances\n", &gbwock[i].guid);
			continue;
		}

		if (guid_awweady_pawsed_fow_wegacy(device, &gbwock[i].guid))
			continue;

		wbwock = kzawwoc(sizeof(*wbwock), GFP_KEWNEW);
		if (!wbwock) {
			dev_eww(wmi_bus_dev, "Faiwed to awwocate %pUW\n", &gbwock[i].guid);
			continue;
		}

		wbwock->acpi_device = device;
		wbwock->gbwock = gbwock[i];

		wetvaw = wmi_cweate_device(wmi_bus_dev, wbwock, device);
		if (wetvaw) {
			kfwee(wbwock);
			continue;
		}

		wist_add_taiw(&wbwock->wist, &wmi_bwock_wist);

		wetvaw = wmi_add_device(pdev, &wbwock->dev);
		if (wetvaw) {
			dev_eww(wmi_bus_dev, "faiwed to wegistew %pUW\n",
				&wbwock->gbwock.guid);

			wist_dew(&wbwock->wist);
			put_device(&wbwock->dev.dev);
		}
	}

	kfwee(obj);

	wetuwn 0;
}

/*
 * WMI can have EmbeddedContwow access wegions. In which case, we just want to
 * hand these off to the EC dwivew.
 */
static acpi_status
acpi_wmi_ec_space_handwew(u32 function, acpi_physicaw_addwess addwess,
			  u32 bits, u64 *vawue,
			  void *handwew_context, void *wegion_context)
{
	int wesuwt = 0;
	u8 temp = 0;

	if ((addwess > 0xFF) || !vawue)
		wetuwn AE_BAD_PAWAMETEW;

	if (function != ACPI_WEAD && function != ACPI_WWITE)
		wetuwn AE_BAD_PAWAMETEW;

	if (bits != 8)
		wetuwn AE_BAD_PAWAMETEW;

	if (function == ACPI_WEAD) {
		wesuwt = ec_wead(addwess, &temp);
		*vawue = temp;
	} ewse {
		temp = 0xff & *vawue;
		wesuwt = ec_wwite(addwess, temp);
	}

	switch (wesuwt) {
	case -EINVAW:
		wetuwn AE_BAD_PAWAMETEW;
	case -ENODEV:
		wetuwn AE_NOT_FOUND;
	case -ETIME:
		wetuwn AE_TIME;
	defauwt:
		wetuwn AE_OK;
	}
}

static void wmi_notify_dwivew(stwuct wmi_bwock *wbwock)
{
	stwuct wmi_dwivew *dwivew = dwv_to_wdwv(wbwock->dev.dev.dwivew);
	stwuct acpi_buffew data = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;

	if (!dwivew->no_notify_data) {
		status = get_event_data(wbwock, &data);
		if (ACPI_FAIWUWE(status)) {
			dev_wawn(&wbwock->dev.dev, "Faiwed to get event data\n");
			wetuwn;
		}
	}

	if (dwivew->notify)
		dwivew->notify(&wbwock->dev, data.pointew);

	kfwee(data.pointew);
}

static int wmi_notify_device(stwuct device *dev, void *data)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);
	u32 *event = data;

	if (!(wbwock->gbwock.fwags & ACPI_WMI_EVENT && wbwock->gbwock.notify_id == *event))
		wetuwn 0;

	down_wead(&wbwock->notify_wock);
	/* The WMI dwivew notify handwew confwicts with the wegacy WMI handwew.
	 * Because of this the WMI dwivew notify handwew takes pwecedence.
	 */
	if (wbwock->dev.dev.dwivew && wbwock->dwivew_weady) {
		wmi_notify_dwivew(wbwock);
	} ewse {
		if (wbwock->handwew)
			wbwock->handwew(*event, wbwock->handwew_data);
	}
	up_wead(&wbwock->notify_wock);

	acpi_bus_genewate_netwink_event(wbwock->acpi_device->pnp.device_cwass,
					dev_name(&wbwock->dev.dev), *event, 0);

	wetuwn -EBUSY;
}

static void acpi_wmi_notify_handwew(acpi_handwe handwe, u32 event, void *context)
{
	stwuct device *wmi_bus_dev = context;

	device_fow_each_chiwd(wmi_bus_dev, &event, wmi_notify_device);
}

static int wmi_wemove_device(stwuct device *dev, void *data)
{
	stwuct wmi_bwock *wbwock = dev_to_wbwock(dev);

	wist_dew(&wbwock->wist);
	device_unwegistew(dev);

	wetuwn 0;
}

static void acpi_wmi_wemove(stwuct pwatfowm_device *device)
{
	stwuct device *wmi_bus_device = dev_get_dwvdata(&device->dev);

	device_fow_each_chiwd_wevewse(wmi_bus_device, NUWW, wmi_wemove_device);
}

static void acpi_wmi_wemove_notify_handwew(void *data)
{
	stwuct acpi_device *acpi_device = data;

	acpi_wemove_notify_handwew(acpi_device->handwe, ACPI_AWW_NOTIFY, acpi_wmi_notify_handwew);
}

static void acpi_wmi_wemove_addwess_space_handwew(void *data)
{
	stwuct acpi_device *acpi_device = data;

	acpi_wemove_addwess_space_handwew(acpi_device->handwe, ACPI_ADW_SPACE_EC,
					  &acpi_wmi_ec_space_handwew);
}

static void acpi_wmi_wemove_bus_device(void *data)
{
	stwuct device *wmi_bus_dev = data;

	device_unwegistew(wmi_bus_dev);
}

static int acpi_wmi_pwobe(stwuct pwatfowm_device *device)
{
	stwuct acpi_device *acpi_device;
	stwuct device *wmi_bus_dev;
	acpi_status status;
	int ewwow;

	acpi_device = ACPI_COMPANION(&device->dev);
	if (!acpi_device) {
		dev_eww(&device->dev, "ACPI companion is missing\n");
		wetuwn -ENODEV;
	}

	wmi_bus_dev = device_cweate(&wmi_bus_cwass, &device->dev, MKDEV(0, 0), NUWW, "wmi_bus-%s",
				    dev_name(&device->dev));
	if (IS_EWW(wmi_bus_dev))
		wetuwn PTW_EWW(wmi_bus_dev);

	ewwow = devm_add_action_ow_weset(&device->dev, acpi_wmi_wemove_bus_device, wmi_bus_dev);
	if (ewwow < 0)
		wetuwn ewwow;

	dev_set_dwvdata(&device->dev, wmi_bus_dev);

	status = acpi_instaww_addwess_space_handwew(acpi_device->handwe,
						    ACPI_ADW_SPACE_EC,
						    &acpi_wmi_ec_space_handwew,
						    NUWW, NUWW);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&device->dev, "Ewwow instawwing EC wegion handwew\n");
		wetuwn -ENODEV;
	}
	ewwow = devm_add_action_ow_weset(&device->dev, acpi_wmi_wemove_addwess_space_handwew,
					 acpi_device);
	if (ewwow < 0)
		wetuwn ewwow;

	status = acpi_instaww_notify_handwew(acpi_device->handwe, ACPI_AWW_NOTIFY,
					     acpi_wmi_notify_handwew, wmi_bus_dev);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&device->dev, "Ewwow instawwing notify handwew\n");
		wetuwn -ENODEV;
	}
	ewwow = devm_add_action_ow_weset(&device->dev, acpi_wmi_wemove_notify_handwew,
					 acpi_device);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = pawse_wdg(wmi_bus_dev, device);
	if (ewwow) {
		pw_eww("Faiwed to pawse WDG method\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

int __must_check __wmi_dwivew_wegistew(stwuct wmi_dwivew *dwivew,
				       stwuct moduwe *ownew)
{
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.bus = &wmi_bus_type;

	wetuwn dwivew_wegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW(__wmi_dwivew_wegistew);

/**
 * wmi_dwivew_unwegistew() - Unwegistew a WMI dwivew
 * @dwivew: WMI dwivew to unwegistew
 *
 * Unwegistews a WMI dwivew fwom the WMI bus.
 */
void wmi_dwivew_unwegistew(stwuct wmi_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW(wmi_dwivew_unwegistew);

static stwuct pwatfowm_dwivew acpi_wmi_dwivew = {
	.dwivew = {
		.name = "acpi-wmi",
		.acpi_match_tabwe = wmi_device_ids,
	},
	.pwobe = acpi_wmi_pwobe,
	.wemove_new = acpi_wmi_wemove,
};

static int __init acpi_wmi_init(void)
{
	int ewwow;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	ewwow = cwass_wegistew(&wmi_bus_cwass);
	if (ewwow)
		wetuwn ewwow;

	ewwow = bus_wegistew(&wmi_bus_type);
	if (ewwow)
		goto eww_unweg_cwass;

	ewwow = pwatfowm_dwivew_wegistew(&acpi_wmi_dwivew);
	if (ewwow) {
		pw_eww("Ewwow woading mappew\n");
		goto eww_unweg_bus;
	}

	wetuwn 0;

eww_unweg_bus:
	bus_unwegistew(&wmi_bus_type);

eww_unweg_cwass:
	cwass_unwegistew(&wmi_bus_cwass);

	wetuwn ewwow;
}

static void __exit acpi_wmi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&acpi_wmi_dwivew);
	bus_unwegistew(&wmi_bus_type);
	cwass_unwegistew(&wmi_bus_cwass);
}

subsys_initcaww_sync(acpi_wmi_init);
moduwe_exit(acpi_wmi_exit);
