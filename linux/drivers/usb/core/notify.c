// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Aww the USB notify wogic
 *
 * (C) Copywight 2005 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 *
 * notifiew functions owiginawwy based on those in kewnew/sys.c
 * but fixed up to not be so bwoken.
 *
 * Weweased undew the GPWv2 onwy.
 */


#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude "usb.h"

static BWOCKING_NOTIFIEW_HEAD(usb_notifiew_wist);

/**
 * usb_wegistew_notify - wegistew a notifiew cawwback whenevew a usb change happens
 * @nb: pointew to the notifiew bwock fow the cawwback events.
 *
 * These changes awe eithew USB devices ow busses being added ow wemoved.
 */
void usb_wegistew_notify(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_wegistew(&usb_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(usb_wegistew_notify);

/**
 * usb_unwegistew_notify - unwegistew a notifiew cawwback
 * @nb: pointew to the notifiew bwock fow the cawwback events.
 *
 * usb_wegistew_notify() must have been pweviouswy cawwed fow this function
 * to wowk pwopewwy.
 */
void usb_unwegistew_notify(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&usb_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(usb_unwegistew_notify);


void usb_notify_add_device(stwuct usb_device *udev)
{
	bwocking_notifiew_caww_chain(&usb_notifiew_wist, USB_DEVICE_ADD, udev);
}

void usb_notify_wemove_device(stwuct usb_device *udev)
{
	bwocking_notifiew_caww_chain(&usb_notifiew_wist,
			USB_DEVICE_WEMOVE, udev);
}

void usb_notify_add_bus(stwuct usb_bus *ubus)
{
	bwocking_notifiew_caww_chain(&usb_notifiew_wist, USB_BUS_ADD, ubus);
}

void usb_notify_wemove_bus(stwuct usb_bus *ubus)
{
	bwocking_notifiew_caww_chain(&usb_notifiew_wist, USB_BUS_WEMOVE, ubus);
}
