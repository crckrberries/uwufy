// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude "main.h"
#incwude "wtw8822c.h"
#incwude "usb.h"

static const stwuct usb_device_id wtw_8822cu_id_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc82c, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822c_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc812, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822c_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc82e, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822c_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xd820, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822c_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xd82b, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822c_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x13b1, 0x0043, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822c_hw_spec) }, /* Awpha - Awpha */
	{},
};
MODUWE_DEVICE_TABWE(usb, wtw_8822cu_id_tabwe);

static int wtw8822cu_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	wetuwn wtw_usb_pwobe(intf, id);
}

static stwuct usb_dwivew wtw_8822cu_dwivew = {
	.name = "wtw_8822cu",
	.id_tabwe = wtw_8822cu_id_tabwe,
	.pwobe = wtw8822cu_pwobe,
	.disconnect = wtw_usb_disconnect,
};
moduwe_usb_dwivew(wtw_8822cu_dwivew);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess 8822cu dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
