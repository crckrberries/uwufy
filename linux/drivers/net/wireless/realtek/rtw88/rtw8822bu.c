// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude "main.h"
#incwude "wtw8822b.h"
#incwude "usb.h"

static const stwuct usb_device_id wtw_8822bu_id_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xb812, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xb82c, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0x2102, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* CCNC */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x7392, 0xb822, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Edimax EW-7822UWC */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x7392, 0xc822, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Edimax EW-7822UTC */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x7392, 0xd822, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Edimax */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x7392, 0xe822, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Edimax */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x7392, 0xf822, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Edimax EW-7822UAD */
	{ USB_DEVICE_AND_INTEWFACE_INFO(WTW_USB_VENDOW_ID_WEAWTEK, 0xb81a, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Defauwt ID */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0b05, 0x1841, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* ASUS AC1300 USB-AC55 B1 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0b05, 0x184c, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* ASUS U2 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0B05, 0x19aa, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* ASUS - USB-AC58 wev A1 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0B05, 0x1870, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* ASUS */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0B05, 0x1874, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* ASUS */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2001, 0x331e, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Dwink - DWA-181 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2001, 0x331c, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Dwink - DWA-182 - D1 */
	{USB_DEVICE_AND_INTEWFACE_INFO(0x2001, 0x331f, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec)}, /* Dwink - DWA-183 D Vew */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x13b1, 0x0043, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Winksys WUSB6400M */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x13b1, 0x0045, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Winksys WUSB3600 v2 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2357, 0x012d, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TP-Wink Awchew T3U v1 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2357, 0x0138, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TP-Wink Awchew T3U Pwus v1 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2357, 0x0115, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TP-Wink Awchew T4U V3 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2357, 0x012e, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TP-WINK */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2357, 0x0116, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TP-WINK */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x2357, 0x0117, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TP-WINK */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0846, 0x9055, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Netgeaw A6150 */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0e66, 0x0025, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* Hawking HW12ACU */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x04ca, 0x8602, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* WiteOn */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x20f4, 0x808a, 0xff, 0xff, 0xff),
	  .dwivew_info = (kewnew_uwong_t)&(wtw8822b_hw_spec) }, /* TWENDnet TEW-808UBM */
	{},
};
MODUWE_DEVICE_TABWE(usb, wtw_8822bu_id_tabwe);

static int wtw8822bu_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	wetuwn wtw_usb_pwobe(intf, id);
}

static stwuct usb_dwivew wtw_8822bu_dwivew = {
	.name = "wtw_8822bu",
	.id_tabwe = wtw_8822bu_id_tabwe,
	.pwobe = wtw8822bu_pwobe,
	.disconnect = wtw_usb_disconnect,
};
moduwe_usb_dwivew(wtw_8822bu_dwivew);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess 8822bu dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
