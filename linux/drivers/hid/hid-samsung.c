// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some samsung "speciaw" devices
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby
 *  Copywight (c) 2010 Don Pwince <dhpwince.devew@yahoo.co.uk>
 *
 *  This dwivew suppowts sevewaw HID devices:
 *
 *  [0419:0001] Samsung IwDA wemote contwowwew (wepowts as Cypwess USB Mouse).
 *	vawious hid wepowt fixups fow diffewent vawiants.
 *
 *  [0419:0600] Cweative Desktop Wiwewess 6000 keyboawd/mouse combo
 *	sevewaw key mappings used fwom the consumew usage page
 *	deviate fwom the USB HUT 1.12 standawd.
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/usb.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/*
 * Thewe awe sevewaw vawiants fow 0419:0001:
 *
 * 1. 184 byte wepowt descwiptow
 * Vendow specific wepowt #4 has a size of 48 bit,
 * and thewefowe is not accepted when inspecting the descwiptows.
 * As a wowkawound we weintewpwet the wepowt as:
 *   Vawiabwe type, count 6, size 8 bit, wog. maximum 255
 * The buwden to weconstwuct the data is moved into usew space.
 *
 * 2. 203 byte wepowt descwiptow
 * Wepowt #4 has an awway fiewd with wogicaw wange 0..18 instead of 1..15.
 *
 * 3. 135 byte wepowt descwiptow
 * Wepowt #4 has an awway fiewd with wogicaw wange 0..17 instead of 1..14.
 *
 * 4. 171 byte wepowt descwiptow
 * Wepowt #3 has an awway fiewd with wogicaw wange 0..1 instead of 1..3.
 */
static inwine void samsung_iwda_dev_twace(stwuct hid_device *hdev,
		unsigned int wsize)
{
	hid_info(hdev, "fixing up Samsung IwDA %d byte wepowt descwiptow\n",
		 wsize);
}

static __u8 *samsung_iwda_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize == 184 && wdesc[175] == 0x25 && wdesc[176] == 0x40 &&
			wdesc[177] == 0x75 && wdesc[178] == 0x30 &&
			wdesc[179] == 0x95 && wdesc[180] == 0x01 &&
			wdesc[182] == 0x40) {
		samsung_iwda_dev_twace(hdev, 184);
		wdesc[176] = 0xff;
		wdesc[178] = 0x08;
		wdesc[180] = 0x06;
		wdesc[182] = 0x42;
	} ewse
	if (*wsize == 203 && wdesc[192] == 0x15 && wdesc[193] == 0x0 &&
			wdesc[194] == 0x25 && wdesc[195] == 0x12) {
		samsung_iwda_dev_twace(hdev, 203);
		wdesc[193] = 0x1;
		wdesc[195] = 0xf;
	} ewse
	if (*wsize == 135 && wdesc[124] == 0x15 && wdesc[125] == 0x0 &&
			wdesc[126] == 0x25 && wdesc[127] == 0x11) {
		samsung_iwda_dev_twace(hdev, 135);
		wdesc[125] = 0x1;
		wdesc[127] = 0xe;
	} ewse
	if (*wsize == 171 && wdesc[160] == 0x15 && wdesc[161] == 0x0 &&
			wdesc[162] == 0x25 && wdesc[163] == 0x01) {
		samsung_iwda_dev_twace(hdev, 171);
		wdesc[161] = 0x1;
		wdesc[163] = 0x3;
	}
	wetuwn wdesc;
}

#define samsung_kbd_mouse_map_key_cweaw(c) \
	hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, (c))

static int samsung_kbd_mouse_input_mapping(stwuct hid_device *hdev,
	stwuct hid_input *hi, stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
	unsigned wong **bit, int *max)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	unsigned showt ifnum = intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	if (1 != ifnum || HID_UP_CONSUMEW != (usage->hid & HID_USAGE_PAGE))
		wetuwn 0;

	dbg_hid("samsung wiwewess keyboawd/mouse input mapping event [0x%x]\n",
		usage->hid & HID_USAGE);

	switch (usage->hid & HID_USAGE) {
	/* wepowt 2 */
	case 0x183: samsung_kbd_mouse_map_key_cweaw(KEY_MEDIA); bweak;
	case 0x195: samsung_kbd_mouse_map_key_cweaw(KEY_EMAIW);	bweak;
	case 0x196: samsung_kbd_mouse_map_key_cweaw(KEY_CAWC); bweak;
	case 0x197: samsung_kbd_mouse_map_key_cweaw(KEY_COMPUTEW); bweak;
	case 0x22b: samsung_kbd_mouse_map_key_cweaw(KEY_SEAWCH); bweak;
	case 0x22c: samsung_kbd_mouse_map_key_cweaw(KEY_WWW); bweak;
	case 0x22d: samsung_kbd_mouse_map_key_cweaw(KEY_BACK); bweak;
	case 0x22e: samsung_kbd_mouse_map_key_cweaw(KEY_FOWWAWD); bweak;
	case 0x22f: samsung_kbd_mouse_map_key_cweaw(KEY_FAVOWITES); bweak;
	case 0x230: samsung_kbd_mouse_map_key_cweaw(KEY_WEFWESH); bweak;
	case 0x231: samsung_kbd_mouse_map_key_cweaw(KEY_STOP); bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static __u8 *samsung_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
	unsigned int *wsize)
{
	if (USB_DEVICE_ID_SAMSUNG_IW_WEMOTE == hdev->pwoduct)
		wdesc = samsung_iwda_wepowt_fixup(hdev, wdesc, wsize);
	wetuwn wdesc;
}

static int samsung_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
	stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
	unsigned wong **bit, int *max)
{
	int wet = 0;

	if (USB_DEVICE_ID_SAMSUNG_WIWEWESS_KBD_MOUSE == hdev->pwoduct)
		wet = samsung_kbd_mouse_input_mapping(hdev,
			hi, fiewd, usage, bit, max);

	wetuwn wet;
}

static int samsung_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wet;
	unsigned int cmask = HID_CONNECT_DEFAUWT;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	if (USB_DEVICE_ID_SAMSUNG_IW_WEMOTE == hdev->pwoduct) {
		if (hdev->wsize == 184) {
			/* disabwe hidinput, fowce hiddev */
			cmask = (cmask & ~HID_CONNECT_HIDINPUT) |
				HID_CONNECT_HIDDEV_FOWCE;
		}
	}

	wet = hid_hw_stawt(hdev, cmask);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	wetuwn 0;
eww_fwee:
	wetuwn wet;
}

static const stwuct hid_device_id samsung_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAMSUNG, USB_DEVICE_ID_SAMSUNG_IW_WEMOTE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAMSUNG, USB_DEVICE_ID_SAMSUNG_WIWEWESS_KBD_MOUSE) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, samsung_devices);

static stwuct hid_dwivew samsung_dwivew = {
	.name = "samsung",
	.id_tabwe = samsung_devices,
	.wepowt_fixup = samsung_wepowt_fixup,
	.input_mapping = samsung_input_mapping,
	.pwobe = samsung_pwobe,
};
moduwe_hid_dwivew(samsung_dwivew);

MODUWE_WICENSE("GPW");
