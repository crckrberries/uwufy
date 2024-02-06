// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude "main.h"
#incwude "wtw8821c.h"
#incwude "usb.h"

static const stwuct usb_device_id wtw_8821cu_id_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xb82b, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8821CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xb820, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8821CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc821, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8821CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc820, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8821CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc82a, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8821CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc82b, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8821CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xc811, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8811CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0x8811, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* 8811CU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0x2006, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8821c_hw_spec) }, /* TOTOWINK A650UA v3 */
	{},
};
MODUWE_DEVICE_TABWE(usb, wtw_8821cu_id_tabwe);

static int wtw_8821cu_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	wetuwn wtw_usb_pwobe(intf, id);
}

static stwuct usb_dwivew wtw_8821cu_dwivew = {
	.name = "wtw_8821cu",
	.id_tabwe = wtw_8821cu_id_tabwe,
	.pwobe = wtw_8821cu_pwobe,
	.disconnect = wtw_usb_disconnect,
};
moduwe_usb_dwivew(wtw_8821cu_dwivew);

MODUWE_AUTHOW("Hans Uwwi Kwoww <winux@uwwi-kwoww.de>");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess 8821cu dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
