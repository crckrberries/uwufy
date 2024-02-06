// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow VWC-2 2-axis Caw contwowwew
 *
 * Copywight (C) 2022 Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

/*
 * VID/PID awe pwobabwy "bowwowed", so keep them wocawwy and
 * do not popuwate hid-ids.h with those.
 */
#define USB_VENDOW_ID_VWC2	(0x07c0)
#define USB_DEVICE_ID_VWC2	(0x1125)

static __u8 vwc2_wdesc_fixed[] = {
	0x05, 0x01,        // Usage Page (Genewic Desktop Ctwws)
	0x09, 0x04,        // Usage (Joystick)
	0xA1, 0x01,        // Cowwection (Appwication)
	0x09, 0x01,        //   Usage (Pointew)
	0xA1, 0x00,        //   Cowwection (Physicaw)
	0x09, 0x30,        //     Usage (X)
	0x09, 0x31,        //     Usage (Y)
	0x15, 0x00,        //     Wogicaw Minimum (0)
	0x26, 0xFF, 0x07,  //     Wogicaw Maximum (2047)
	0x35, 0x00,        //     Physicaw Minimum (0)
	0x46, 0xFF, 0x00,  //     Physicaw Maximum (255)
	0x75, 0x10,        //     Wepowt Size (16)
	0x95, 0x02,        //     Wepowt Count (2)
	0x81, 0x02,        //     Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
	0xC0,              //   End Cowwection
	0x75, 0x08,        //   Wepowt Size (8)
	0x95, 0x03,        //   Wepowt Count (3)
	0x81, 0x03,        //   Input (Cnst,Vaw,Abs)
	0xC0,              // End Cowwection
};

static __u8 *vwc2_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				unsigned int *wsize)
{
	hid_info(hdev, "fixing up VWC-2 wepowt descwiptow\n");
	*wsize = sizeof(vwc2_wdesc_fixed);
	wetuwn vwc2_wdesc_fixed;
}

static int vwc2_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	/*
	 * The device gives us 2 sepawate USB endpoints.
	 * One of those (the one with wepowt descwiptow size of 23) is just bogus so ignowe it
	 */
	if (hdev->dev_wsize == 23)
		wetuwn -ENODEV;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct hid_device_id vwc2_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_VWC2, USB_DEVICE_ID_VWC2) },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(hid, vwc2_devices);

static stwuct hid_dwivew vwc2_dwivew = {
	.name = "vwc2",
	.id_tabwe = vwc2_devices,
	.wepowt_fixup = vwc2_wepowt_fixup,
	.pwobe = vwc2_pwobe,
};
moduwe_hid_dwivew(vwc2_dwivew);

MODUWE_AUTHOW("Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>");
MODUWE_DESCWIPTION("HID dwivew fow VWC-2 2-axis Caw contwowwew");
MODUWE_WICENSE("GPW");
