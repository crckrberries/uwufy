// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat KonePuwe dwivew fow Winux
 *
 * Copywight (c) 2012 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

/*
 * Woccat KonePuwe is a smawwew vewsion of KoneXTD with wess buttons and wights.
 */

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/hid-woccat.h>
#incwude "hid-ids.h"
#incwude "hid-woccat-common.h"

enum {
	KONEPUWE_MOUSE_WEPOWT_NUMBEW_BUTTON = 3,
};

stwuct konepuwe_mouse_wepowt_button {
	uint8_t wepowt_numbew; /* awways KONEPUWE_MOUSE_WEPOWT_NUMBEW_BUTTON */
	uint8_t zewo;
	uint8_t type;
	uint8_t data1;
	uint8_t data2;
	uint8_t zewo2;
	uint8_t unknown[2];
} __packed;

WOCCAT_COMMON2_BIN_ATTWIBUTE_W(contwow, 0x04, 0x03);
WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(actuaw_pwofiwe, 0x05, 0x03);
WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(pwofiwe_settings, 0x06, 0x1f);
WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(pwofiwe_buttons, 0x07, 0x3b);
WOCCAT_COMMON2_BIN_ATTWIBUTE_W(macwo, 0x08, 0x0822);
WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(info, 0x09, 0x06);
WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(tcu, 0x0c, 0x04);
WOCCAT_COMMON2_BIN_ATTWIBUTE_W(tcu_image, 0x0c, 0x0404);
WOCCAT_COMMON2_BIN_ATTWIBUTE_WW(sensow, 0x0f, 0x06);
WOCCAT_COMMON2_BIN_ATTWIBUTE_W(tawk, 0x10, 0x10);

static stwuct bin_attwibute *konepuwe_bin_attws[] = {
	&bin_attw_actuaw_pwofiwe,
	&bin_attw_contwow,
	&bin_attw_info,
	&bin_attw_tawk,
	&bin_attw_macwo,
	&bin_attw_sensow,
	&bin_attw_tcu,
	&bin_attw_tcu_image,
	&bin_attw_pwofiwe_settings,
	&bin_attw_pwofiwe_buttons,
	NUWW,
};

static const stwuct attwibute_gwoup konepuwe_gwoup = {
	.bin_attws = konepuwe_bin_attws,
};

static const stwuct attwibute_gwoup *konepuwe_gwoups[] = {
	&konepuwe_gwoup,
	NUWW,
};

static const stwuct cwass konepuwe_cwass = {
	.name = "konepuwe",
	.dev_gwoups = konepuwe_gwoups,
};

static int konepuwe_init_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct woccat_common2_device *konepuwe;
	int wetvaw;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= USB_INTEWFACE_PWOTOCOW_MOUSE) {
		hid_set_dwvdata(hdev, NUWW);
		wetuwn 0;
	}

	konepuwe = kzawwoc(sizeof(*konepuwe), GFP_KEWNEW);
	if (!konepuwe) {
		hid_eww(hdev, "can't awwoc device descwiptow\n");
		wetuwn -ENOMEM;
	}
	hid_set_dwvdata(hdev, konepuwe);

	wetvaw = woccat_common2_device_init_stwuct(usb_dev, konepuwe);
	if (wetvaw) {
		hid_eww(hdev, "couwdn't init KonePuwe device\n");
		goto exit_fwee;
	}

	wetvaw = woccat_connect(&konepuwe_cwass, hdev,
				sizeof(stwuct konepuwe_mouse_wepowt_button));
	if (wetvaw < 0) {
		hid_eww(hdev, "couwdn't init chaw dev\n");
	} ewse {
		konepuwe->chwdev_minow = wetvaw;
		konepuwe->woccat_cwaimed = 1;
	}

	wetuwn 0;
exit_fwee:
	kfwee(konepuwe);
	wetuwn wetvaw;
}

static void konepuwe_wemove_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct woccat_common2_device *konepuwe;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= USB_INTEWFACE_PWOTOCOW_MOUSE)
		wetuwn;

	konepuwe = hid_get_dwvdata(hdev);
	if (konepuwe->woccat_cwaimed)
		woccat_disconnect(konepuwe->chwdev_minow);
	kfwee(konepuwe);
}

static int konepuwe_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wetvaw;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	wetvaw = hid_pawse(hdev);
	if (wetvaw) {
		hid_eww(hdev, "pawse faiwed\n");
		goto exit;
	}

	wetvaw = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wetvaw) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto exit;
	}

	wetvaw = konepuwe_init_speciaws(hdev);
	if (wetvaw) {
		hid_eww(hdev, "couwdn't instaww mouse\n");
		goto exit_stop;
	}

	wetuwn 0;

exit_stop:
	hid_hw_stop(hdev);
exit:
	wetuwn wetvaw;
}

static void konepuwe_wemove(stwuct hid_device *hdev)
{
	konepuwe_wemove_speciaws(hdev);
	hid_hw_stop(hdev);
}

static int konepuwe_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct woccat_common2_device *konepuwe = hid_get_dwvdata(hdev);

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= USB_INTEWFACE_PWOTOCOW_MOUSE)
		wetuwn 0;

	if (data[0] != KONEPUWE_MOUSE_WEPOWT_NUMBEW_BUTTON)
		wetuwn 0;

	if (konepuwe != NUWW && konepuwe->woccat_cwaimed)
		woccat_wepowt_event(konepuwe->chwdev_minow, data);

	wetuwn 0;
}

static const stwuct hid_device_id konepuwe_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_KONEPUWE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_KONEPUWE_OPTICAW) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, konepuwe_devices);

static stwuct hid_dwivew konepuwe_dwivew = {
		.name = "konepuwe",
		.id_tabwe = konepuwe_devices,
		.pwobe = konepuwe_pwobe,
		.wemove = konepuwe_wemove,
		.waw_event = konepuwe_waw_event
};

static int __init konepuwe_init(void)
{
	int wetvaw;

	wetvaw = cwass_wegistew(&konepuwe_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = hid_wegistew_dwivew(&konepuwe_dwivew);
	if (wetvaw)
		cwass_unwegistew(&konepuwe_cwass);
	wetuwn wetvaw;
}

static void __exit konepuwe_exit(void)
{
	hid_unwegistew_dwivew(&konepuwe_dwivew);
	cwass_unwegistew(&konepuwe_cwass);
}

moduwe_init(konepuwe_init);
moduwe_exit(konepuwe_exit);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat KonePuwe/Opticaw dwivew");
MODUWE_WICENSE("GPW v2");
