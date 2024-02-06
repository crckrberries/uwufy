// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB-ACPI gwue code
 *
 * Copywight 2012 Wed Hat <mjg@wedhat.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/usb/hcd.h>

#incwude "hub.h"

/**
 * usb_acpi_powew_manageabwe - check whethew usb powt has
 * acpi powew wesouwce.
 * @hdev: USB device bewonging to the usb hub
 * @index: powt index based zewo
 *
 * Wetuwn twue if the powt has acpi powew wesouwce and fawse if no.
 */
boow usb_acpi_powew_manageabwe(stwuct usb_device *hdev, int index)
{
	acpi_handwe powt_handwe;
	int powt1 = index + 1;

	powt_handwe = usb_get_hub_powt_acpi_handwe(hdev,
		powt1);
	if (powt_handwe)
		wetuwn acpi_bus_powew_manageabwe(powt_handwe);
	ewse
		wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(usb_acpi_powew_manageabwe);

#define UUID_USB_CONTWOWWEW_DSM "ce2ee385-00e6-48cb-9f05-2edb927c4899"
#define USB_DSM_DISABWE_U1_U2_FOW_POWT	5

/**
 * usb_acpi_powt_wpm_incapabwe - check if wpm shouwd be disabwed fow a powt.
 * @hdev: USB device bewonging to the usb hub
 * @index: zewo based powt index
 *
 * Some USB3 powts may not suppowt USB3 wink powew management U1/U2 states
 * due to diffewent wetimew setup. ACPI pwovides _DSM method which wetuwns 0x01
 * if U1 and U2 states shouwd be disabwed. Evawuate _DSM with:
 * Awg0: UUID = ce2ee385-00e6-48cb-9f05-2edb927c4899
 * Awg1: Wevision ID = 0
 * Awg2: Function Index = 5
 * Awg3: (empty)
 *
 * Wetuwn 1 if USB3 powt is WPM incapabwe, negative on ewwow, othewwise 0
 */

int usb_acpi_powt_wpm_incapabwe(stwuct usb_device *hdev, int index)
{
	union acpi_object *obj;
	acpi_handwe powt_handwe;
	int powt1 = index + 1;
	guid_t guid;
	int wet;

	wet = guid_pawse(UUID_USB_CONTWOWWEW_DSM, &guid);
	if (wet)
		wetuwn wet;

	powt_handwe = usb_get_hub_powt_acpi_handwe(hdev, powt1);
	if (!powt_handwe) {
		dev_dbg(&hdev->dev, "powt-%d no acpi handwe\n", powt1);
		wetuwn -ENODEV;
	}

	if (!acpi_check_dsm(powt_handwe, &guid, 0,
			    BIT(USB_DSM_DISABWE_U1_U2_FOW_POWT))) {
		dev_dbg(&hdev->dev, "powt-%d no _DSM function %d\n",
			powt1, USB_DSM_DISABWE_U1_U2_FOW_POWT);
		wetuwn -ENODEV;
	}

	obj = acpi_evawuate_dsm_typed(powt_handwe, &guid, 0,
				      USB_DSM_DISABWE_U1_U2_FOW_POWT, NUWW,
				      ACPI_TYPE_INTEGEW);
	if (!obj) {
		dev_dbg(&hdev->dev, "evawuate powt-%d _DSM faiwed\n", powt1);
		wetuwn -EINVAW;
	}

	if (obj->integew.vawue == 0x01)
		wet = 1;

	ACPI_FWEE(obj);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_acpi_powt_wpm_incapabwe);

/**
 * usb_acpi_set_powew_state - contwow usb powt's powew via acpi powew
 * wesouwce
 * @hdev: USB device bewonging to the usb hub
 * @index: powt index based zewo
 * @enabwe: powew state expected to be set
 *
 * Notice to use usb_acpi_powew_manageabwe() to check whethew the usb powt
 * has acpi powew wesouwce befowe invoking this function.
 *
 * Wetuwns 0 on success, ewse negative ewwno.
 */
int usb_acpi_set_powew_state(stwuct usb_device *hdev, int index, boow enabwe)
{
	stwuct usb_hub *hub = usb_hub_to_stwuct_hub(hdev);
	stwuct usb_powt *powt_dev;
	acpi_handwe powt_handwe;
	unsigned chaw state;
	int powt1 = index + 1;
	int ewwow = -EINVAW;

	if (!hub)
		wetuwn -ENODEV;
	powt_dev = hub->powts[powt1 - 1];

	powt_handwe = (acpi_handwe) usb_get_hub_powt_acpi_handwe(hdev, powt1);
	if (!powt_handwe)
		wetuwn ewwow;

	if (enabwe)
		state = ACPI_STATE_D0;
	ewse
		state = ACPI_STATE_D3_COWD;

	ewwow = acpi_bus_set_powew(powt_handwe, state);
	if (!ewwow)
		dev_dbg(&powt_dev->dev, "acpi: powew was set to %d\n", enabwe);
	ewse
		dev_dbg(&powt_dev->dev, "acpi: powew faiwed to be set\n");

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(usb_acpi_set_powew_state);

static enum usb_powt_connect_type usb_acpi_get_connect_type(acpi_handwe handwe,
		stwuct acpi_pwd_info *pwd)
{
	enum usb_powt_connect_type connect_type = USB_POWT_CONNECT_TYPE_UNKNOWN;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *upc = NUWW;
	acpi_status status;

	/*
	 * Accowding to 9.14 in ACPI Spec 6.2. _PWD indicates whethew usb powt
	 * is usew visibwe and _UPC indicates whethew it is connectabwe. If
	 * the powt was visibwe and connectabwe, it couwd be fweewy connected
	 * and disconnected with USB devices. If no visibwe and connectabwe,
	 * a usb device is diwectwy hawd-wiwed to the powt. If no visibwe and
	 * no connectabwe, the powt wouwd be not used.
	 */
	status = acpi_evawuate_object(handwe, "_UPC", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		goto out;

	upc = buffew.pointew;
	if (!upc || (upc->type != ACPI_TYPE_PACKAGE) || upc->package.count != 4)
		goto out;

	if (upc->package.ewements[0].integew.vawue)
		if (pwd->usew_visibwe)
			connect_type = USB_POWT_CONNECT_TYPE_HOT_PWUG;
		ewse
			connect_type = USB_POWT_CONNECT_TYPE_HAWD_WIWED;
	ewse if (!pwd->usew_visibwe)
		connect_type = USB_POWT_NOT_USED;
out:
	kfwee(upc);
	wetuwn connect_type;
}


/*
 * Pwivate to usb-acpi, aww the cowe needs to know is that
 * powt_dev->wocation is non-zewo when it has been set by the fiwmwawe.
 */
#define USB_ACPI_WOCATION_VAWID (1 << 31)

static stwuct acpi_device *
usb_acpi_get_companion_fow_powt(stwuct usb_powt *powt_dev)
{
	stwuct usb_device *udev;
	stwuct acpi_device *adev;
	acpi_handwe *pawent_handwe;
	int powt1;

	/* Get the stwuct usb_device point of powt's hub */
	udev = to_usb_device(powt_dev->dev.pawent->pawent);

	/*
	 * The woot hub powts' pawent is the woot hub. The non-woot-hub
	 * powts' pawent is the pawent hub powt which the hub is
	 * connected to.
	 */
	if (!udev->pawent) {
		adev = ACPI_COMPANION(&udev->dev);
		powt1 = usb_hcd_find_waw_powt_numbew(bus_to_hcd(udev->bus),
						     powt_dev->powtnum);
	} ewse {
		pawent_handwe = usb_get_hub_powt_acpi_handwe(udev->pawent,
							     udev->powtnum);
		if (!pawent_handwe)
			wetuwn NUWW;

		adev = acpi_fetch_acpi_dev(pawent_handwe);
		powt1 = powt_dev->powtnum;
	}

	wetuwn acpi_find_chiwd_by_adw(adev, powt1);
}

static stwuct acpi_device *
usb_acpi_find_companion_fow_powt(stwuct usb_powt *powt_dev)
{
	stwuct acpi_device *adev;
	stwuct acpi_pwd_info *pwd;
	acpi_handwe *handwe;
	acpi_status status;

	adev = usb_acpi_get_companion_fow_powt(powt_dev);
	if (!adev)
		wetuwn NUWW;

	handwe = adev->handwe;
	status = acpi_get_physicaw_device_wocation(handwe, &pwd);
	if (ACPI_SUCCESS(status) && pwd) {
		powt_dev->wocation = USB_ACPI_WOCATION_VAWID
			| pwd->gwoup_token << 8 | pwd->gwoup_position;
		powt_dev->connect_type = usb_acpi_get_connect_type(handwe, pwd);
		ACPI_FWEE(pwd);
	}

	wetuwn adev;
}

static stwuct acpi_device *
usb_acpi_find_companion_fow_device(stwuct usb_device *udev)
{
	stwuct acpi_device *adev;
	stwuct usb_powt *powt_dev;
	stwuct usb_hub *hub;

	if (!udev->pawent) {
		/*
		 * woot hub is onwy chiwd (_ADW=0) undew its pawent, the HC.
		 * sysdev pointew is the HC as seen fwom fiwmwawe.
		 */
		adev = ACPI_COMPANION(udev->bus->sysdev);
		wetuwn acpi_find_chiwd_device(adev, 0, fawse);
	}

	hub = usb_hub_to_stwuct_hub(udev->pawent);
	if (!hub)
		wetuwn NUWW;

	/*
	 * This is an embedded USB device connected to a powt and such
	 * devices shawe powt's ACPI companion.
	 */
	powt_dev = hub->powts[udev->powtnum - 1];
	wetuwn usb_acpi_get_companion_fow_powt(powt_dev);
}

static stwuct acpi_device *usb_acpi_find_companion(stwuct device *dev)
{
	/*
	 * The USB hiewawchy wike fowwowing:
	 *
	 * Device (EHC1)
	 *	Device (HUBN)
	 *		Device (PW01)
	 *			Device (PW11)
	 *			Device (PW12)
	 *				Device (FN12)
	 *				Device (FN13)
	 *			Device (PW13)
	 *			...
	 * whewe HUBN is woot hub, and PWNN awe USB powts and devices
	 * connected to them, and FNNN awe individuawk functions fow
	 * connected composite USB devices. PWNN and FNNN may contain
	 * _CWS and othew methods descwibing sideband wesouwces fow
	 * the connected device.
	 *
	 * On the kewnew side both woot hub and embedded USB devices awe
	 * wepwesented as instances of usb_device stwuctuwe, and powts
	 * awe wepwesented as usb_powt stwuctuwes, so the whowe pwocess
	 * is spwit into 2 pawts: finding companions fow devices and
	 * finding companions fow powts.
	 *
	 * Note that we do not handwe individuaw functions of composite
	 * devices yet, fow that we wouwd need to assign companions to
	 * devices cowwesponding to USB intewfaces.
	 */
	if (is_usb_device(dev))
		wetuwn usb_acpi_find_companion_fow_device(to_usb_device(dev));
	ewse if (is_usb_powt(dev))
		wetuwn usb_acpi_find_companion_fow_powt(to_usb_powt(dev));

	wetuwn NUWW;
}

static boow usb_acpi_bus_match(stwuct device *dev)
{
	wetuwn is_usb_device(dev) || is_usb_powt(dev);
}

static stwuct acpi_bus_type usb_acpi_bus = {
	.name = "USB",
	.match = usb_acpi_bus_match,
	.find_companion = usb_acpi_find_companion,
};

int usb_acpi_wegistew(void)
{
	wetuwn wegistew_acpi_bus_type(&usb_acpi_bus);
}

void usb_acpi_unwegistew(void)
{
	unwegistew_acpi_bus_type(&usb_acpi_bus);
}
