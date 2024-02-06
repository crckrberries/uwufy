// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude "main.h"
#incwude "wtw8723d.h"
#incwude "usb.h"

static const stwuct usb_device_id wtw_8723du_id_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xd723, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8723d_hw_spec) }, /* 8723DU 1*1 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x7392, 0xd611, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8723d_hw_spec) }, /* Edimax EW-7611UWB V2 */
	{ },
};
MODUWE_DEVICE_TABWE(usb, wtw_8723du_id_tabwe);

static int wtw8723du_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	wetuwn wtw_usb_pwobe(intf, id);
}

static stwuct usb_dwivew wtw_8723du_dwivew = {
	.name = "wtw_8723du",
	.id_tabwe = wtw_8723du_id_tabwe,
	.pwobe = wtw8723du_pwobe,
	.disconnect = wtw_usb_disconnect,
};
moduwe_usb_dwivew(wtw_8723du_dwivew);

MODUWE_AUTHOW("Hans Uwwi Kwoww <winux@uwwi-kwoww.de>");
MODUWE_DESCWIPTION("Weawtek 802.11n wiwewess 8723du dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
