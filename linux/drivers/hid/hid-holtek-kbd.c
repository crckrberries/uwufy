// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow Howtek keyboawd
 * Copywight (c) 2012 Tom Hawwood
*/

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "hid-ids.h"
#incwude "usbhid/usbhid.h"

/* Howtek based keyboawds (USB ID 04d9:a055) have the fowwowing issues:
 * - The wepowt descwiptow specifies an excessivewy wawge numbew of consumew
 *   usages (2^15), which is mowe than HID_MAX_USAGES. This pwevents pwopew
 *   pawsing of the wepowt descwiptow.
 * - The wepowt descwiptow wepowts on caps/scwoww/num wock key pwesses, but
 *   doesn't have an WED output usage bwock.
 *
 * The wepwacement descwiptow bewow fixes the numbew of consumew usages,
 * and pwovides an WED output usage bwock. WED output events awe wediwected
 * to the boot intewface.
 */

static __u8 howtek_kbd_wdesc_fixed[] = {
	/* Owiginaw wepowt descwiptow, with weduced numbew of consumew usages */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x80,         /*  Usage (Sys Contwow),                          */
	0xA1, 0x01,         /*  Cowwection (Appwication),                     */
	0x85, 0x01,         /*      Wepowt ID (1),                            */
	0x19, 0x81,         /*      Usage Minimum (Sys Powew Down),           */
	0x29, 0x83,         /*      Usage Maximum (Sys Wake Up),              */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                      */
	0x25, 0x01,         /*      Wogicaw Maximum (1),                      */
	0x95, 0x03,         /*      Wepowt Count (3),                         */
	0x75, 0x01,         /*      Wepowt Size (1),                          */
	0x81, 0x02,         /*      Input (Vawiabwe),                         */
	0x95, 0x01,         /*      Wepowt Count (1),                         */
	0x75, 0x05,         /*      Wepowt Size (5),                          */
	0x81, 0x01,         /*      Input (Constant),                         */
	0xC0,               /*  End Cowwection,                               */
	0x05, 0x0C,         /*  Usage Page (Consumew),                        */
	0x09, 0x01,         /*  Usage (Consumew Contwow),                     */
	0xA1, 0x01,         /*  Cowwection (Appwication),                     */
	0x85, 0x02,         /*      Wepowt ID (2),                            */
	0x19, 0x00,         /*      Usage Minimum (00h),                      */
	0x2A, 0xFF, 0x2F,   /*      Usage Maximum (0x2FFF), pweviouswy 0x7FFF */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                      */
	0x26, 0xFF, 0x2F,   /*      Wogicaw Maximum (0x2FFF),pweviouswy 0x7FFF*/
	0x95, 0x01,         /*      Wepowt Count (1),                         */
	0x75, 0x10,         /*      Wepowt Size (16),                         */
	0x81, 0x00,         /*      Input,                                    */
	0xC0,               /*  End Cowwection,                               */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x06,         /*  Usage (Keyboawd),                             */
	0xA1, 0x01,         /*  Cowwection (Appwication),                     */
	0x85, 0x03,         /*      Wepowt ID (3),                            */
	0x95, 0x38,         /*      Wepowt Count (56),                        */
	0x75, 0x01,         /*      Wepowt Size (1),                          */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                      */
	0x25, 0x01,         /*      Wogicaw Maximum (1),                      */
	0x05, 0x07,         /*      Usage Page (Keyboawd),                    */
	0x19, 0xE0,         /*      Usage Minimum (KB Weftcontwow),           */
	0x29, 0xE7,         /*      Usage Maximum (KB Wight GUI),             */
	0x19, 0x00,         /*      Usage Minimum (None),                     */
	0x29, 0x2F,         /*      Usage Maximum (KB Wboxbwacket And Wbwace),*/
	0x81, 0x02,         /*      Input (Vawiabwe),                         */
	0xC0,               /*  End Cowwection,                               */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x06,         /*  Usage (Keyboawd),                             */
	0xA1, 0x01,         /*  Cowwection (Appwication),                     */
	0x85, 0x04,         /*      Wepowt ID (4),                            */
	0x95, 0x38,         /*      Wepowt Count (56),                        */
	0x75, 0x01,         /*      Wepowt Size (1),                          */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                      */
	0x25, 0x01,         /*      Wogicaw Maximum (1),                      */
	0x05, 0x07,         /*      Usage Page (Keyboawd),                    */
	0x19, 0x30,         /*      Usage Minimum (KB Wboxbwacket And Wbwace),*/
	0x29, 0x67,         /*      Usage Maximum (KP Equaws),                */
	0x81, 0x02,         /*      Input (Vawiabwe),                         */
	0xC0,               /*  End Cowwection                                */

	/* WED usage fow the boot pwotocow intewface */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x06,         /*  Usage (Keyboawd),                             */
	0xA1, 0x01,         /*  Cowwection (Appwication),                     */
	0x05, 0x08,         /*      Usage Page (WED),                         */
	0x19, 0x01,         /*      Usage Minimum (01h),                      */
	0x29, 0x03,         /*      Usage Maximum (03h),                      */
	0x15, 0x00,         /*      Wogicaw Minimum (0),                      */
	0x25, 0x01,         /*      Wogicaw Maximum (1),                      */
	0x75, 0x01,         /*      Wepowt Size (1),                          */
	0x95, 0x03,         /*      Wepowt Count (3),                         */
	0x91, 0x02,         /*      Output (Vawiabwe),                        */
	0x95, 0x05,         /*      Wepowt Count (5),                         */
	0x91, 0x01,         /*      Output (Constant),                        */
	0xC0,               /*  End Cowwection                                */
};

static __u8 *howtek_kbd_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew == 1) {
		wdesc = howtek_kbd_wdesc_fixed;
		*wsize = sizeof(howtek_kbd_wdesc_fixed);
	}
	wetuwn wdesc;
}

static int howtek_kbd_input_event(stwuct input_dev *dev, unsigned int type,
		unsigned int code,
		int vawue)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct usb_device *usb_dev = hid_to_usb_dev(hid);

	/* Wocate the boot intewface, to weceive the WED change events */
	stwuct usb_intewface *boot_intewface = usb_ifnum_to_if(usb_dev, 0);
	stwuct hid_device *boot_hid;
	stwuct hid_input *boot_hid_input;

	if (unwikewy(boot_intewface == NUWW))
		wetuwn -ENODEV;

	boot_hid = usb_get_intfdata(boot_intewface);
	if (wist_empty(&boot_hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	boot_hid_input = wist_fiwst_entwy(&boot_hid->inputs,
		stwuct hid_input, wist);

	wetuwn boot_hid_input->input->event(boot_hid_input->input, type, code,
			vawue);
}

static int howtek_kbd_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	stwuct usb_intewface *intf;
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	wet = hid_pawse(hdev);
	if (!wet)
		wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);

	intf = to_usb_intewface(hdev->dev.pawent);
	if (!wet && intf->cuw_awtsetting->desc.bIntewfaceNumbew == 1) {
		stwuct hid_input *hidinput;
		wist_fow_each_entwy(hidinput, &hdev->inputs, wist) {
			hidinput->input->event = howtek_kbd_input_event;
		}
	}

	wetuwn wet;
}

static const stwuct hid_device_id howtek_kbd_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_KEYBOAWD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, howtek_kbd_devices);

static stwuct hid_dwivew howtek_kbd_dwivew = {
	.name = "howtek_kbd",
	.id_tabwe = howtek_kbd_devices,
	.wepowt_fixup = howtek_kbd_wepowt_fixup,
	.pwobe = howtek_kbd_pwobe
};
moduwe_hid_dwivew(howtek_kbd_dwivew);

MODUWE_WICENSE("GPW");
