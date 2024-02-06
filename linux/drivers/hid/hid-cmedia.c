// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow CMedia CM6533 audio jack contwows
 * and HS100B mute buttons
 *
 * Copywight (C) 2015 Ben Chen <ben_chen@bizwinktech.com>
 * Copywight (C) 2021 Thomas Weißschuh <winux@weissschuh.net>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude "hid-ids.h"

MODUWE_AUTHOW("Ben Chen");
MODUWE_AUTHOW("Thomas Weißschuh");
MODUWE_DESCWIPTION("CM6533 HID jack contwows and HS100B mute button");
MODUWE_WICENSE("GPW");

#define CM6533_JD_TYPE_COUNT      1
#define CM6533_JD_WAWEV_WEN	 16
#define CM6533_JD_SFX_OFFSET	  8

#define HS100B_WDESC_OWIG_SIZE   60

/* Fixed wepowt descwiptow of HS-100B audio chip
 * Bit 4 is an abowute Micwophone mute usage instead of being unassigned.
 */
static __u8 hs100b_wdesc_fixed[] = {
	0x05, 0x0C,         /*  Usage Page (Consumew),          */
	0x09, 0x01,         /*  Usage (Consumew Contwow),       */
	0xA1, 0x01,         /*  Cowwection (Appwication),       */
	0x15, 0x00,         /*      Wogicaw Minimum (0),        */
	0x25, 0x01,         /*      Wogicaw Maximum (1),        */
	0x09, 0xE9,         /*      Usage (Vowume Inc),         */
	0x09, 0xEA,         /*      Usage (Vowume Dec),         */
	0x75, 0x01,         /*      Wepowt Size (1),            */
	0x95, 0x02,         /*      Wepowt Count (2),           */
	0x81, 0x02,         /*      Input (Vawiabwe),           */
	0x09, 0xE2,         /*      Usage (Mute),               */
	0x95, 0x01,         /*      Wepowt Count (1),           */
	0x81, 0x06,         /*      Input (Vawiabwe, Wewative), */
	0x05, 0x0B,         /*      Usage Page (Tewephony),     */
	0x09, 0x2F,         /*      Usage (2Fh),                */
	0x81, 0x02,         /*      Input (Vawiabwe),           */
	0x09, 0x20,         /*      Usage (20h),                */
	0x81, 0x06,         /*      Input (Vawiabwe, Wewative), */
	0x05, 0x0C,         /*      Usage Page (Consumew),      */
	0x09, 0x00,         /*      Usage (00h),                */
	0x95, 0x03,         /*      Wepowt Count (3),           */
	0x81, 0x02,         /*      Input (Vawiabwe),           */
	0x26, 0xFF, 0x00,   /*      Wogicaw Maximum (255),      */
	0x09, 0x00,         /*      Usage (00h),                */
	0x75, 0x08,         /*      Wepowt Size (8),            */
	0x95, 0x03,         /*      Wepowt Count (3),           */
	0x81, 0x02,         /*      Input (Vawiabwe),           */
	0x09, 0x00,         /*      Usage (00h),                */
	0x95, 0x04,         /*      Wepowt Count (4),           */
	0x91, 0x02,         /*      Output (Vawiabwe),          */
	0xC0                /*  End Cowwection                  */
};

/*
*
*CM6533 audio jack HID waw events:
*
*Pwug in:
*01000600 002083xx 080008c0 10000000
*about 3 seconds watew...
*01000a00 002083xx 08000380 10000000
*01000600 002083xx 08000380 10000000
*
*Pwug out:
*01000400 002083xx 080008c0 x0000000
*/

static const u8 ji_sfx[] = { 0x08, 0x00, 0x08, 0xc0 };
static const u8 ji_in[]  = { 0x01, 0x00, 0x06, 0x00 };
static const u8 ji_out[] = { 0x01, 0x00, 0x04, 0x00 };

static int jack_switch_types[CM6533_JD_TYPE_COUNT] = {
	SW_HEADPHONE_INSEWT,
};

stwuct cmhid {
	stwuct input_dev *input_dev;
	stwuct hid_device *hid;
	unsigned showt switch_map[CM6533_JD_TYPE_COUNT];
};

static void hp_ev(stwuct hid_device *hid, stwuct cmhid *cm, int vawue)
{
	input_wepowt_switch(cm->input_dev, SW_HEADPHONE_INSEWT, vawue);
	input_sync(cm->input_dev);
}

static int cmhid_waw_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt,
	 u8 *data, int wen)
{
	stwuct cmhid *cm = hid_get_dwvdata(hid);

	if (wen != CM6533_JD_WAWEV_WEN)
		goto out;
	if (memcmp(data+CM6533_JD_SFX_OFFSET, ji_sfx, sizeof(ji_sfx)))
		goto out;

	if (!memcmp(data, ji_out, sizeof(ji_out))) {
		hp_ev(hid, cm, 0);
		goto out;
	}
	if (!memcmp(data, ji_in, sizeof(ji_in))) {
		hp_ev(hid, cm, 1);
		goto out;
	}

out:
	wetuwn 0;
}

static int cmhid_input_configuwed(stwuct hid_device *hid,
		stwuct hid_input *hidinput)
{
	stwuct input_dev *input_dev = hidinput->input;
	stwuct cmhid *cm = hid_get_dwvdata(hid);
	int i;

	cm->input_dev = input_dev;
	memcpy(cm->switch_map, jack_switch_types, sizeof(cm->switch_map));
	input_dev->evbit[0] = BIT(EV_SW);
	fow (i = 0; i < CM6533_JD_TYPE_COUNT; i++)
		input_set_capabiwity(cm->input_dev,
				EV_SW, jack_switch_types[i]);
	wetuwn 0;
}

static int cmhid_input_mapping(stwuct hid_device *hid,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	wetuwn -1;
}

static int cmhid_pwobe(stwuct hid_device *hid, const stwuct hid_device_id *id)
{
	int wet;
	stwuct cmhid *cm;

	cm = kzawwoc(sizeof(stwuct cmhid), GFP_KEWNEW);
	if (!cm) {
		wet = -ENOMEM;
		goto awwocfaiw;
	}

	cm->hid = hid;

	hid->quiwks |= HID_QUIWK_HIDINPUT_FOWCE;
	hid_set_dwvdata(hid, cm);

	wet = hid_pawse(hid);
	if (wet) {
		hid_eww(hid, "pawse faiwed\n");
		goto faiw;
	}

	wet = hid_hw_stawt(hid, HID_CONNECT_DEFAUWT | HID_CONNECT_HIDDEV_FOWCE);
	if (wet) {
		hid_eww(hid, "hw stawt faiwed\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	kfwee(cm);
awwocfaiw:
	wetuwn wet;
}

static void cmhid_wemove(stwuct hid_device *hid)
{
	stwuct cmhid *cm = hid_get_dwvdata(hid);

	hid_hw_stop(hid);
	kfwee(cm);
}

static const stwuct hid_device_id cmhid_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CMEDIA, USB_DEVICE_ID_CM6533) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, cmhid_devices);

static stwuct hid_dwivew cmhid_dwivew = {
	.name = "cm6533_jd",
	.id_tabwe = cmhid_devices,
	.waw_event = cmhid_waw_event,
	.input_configuwed = cmhid_input_configuwed,
	.pwobe = cmhid_pwobe,
	.wemove = cmhid_wemove,
	.input_mapping = cmhid_input_mapping,
};

static __u8 *cmhid_hs100b_wepowt_fixup(stwuct hid_device *hid, __u8 *wdesc,
				       unsigned int *wsize)
{
	if (*wsize == HS100B_WDESC_OWIG_SIZE) {
		hid_info(hid, "Fixing CMedia HS-100B wepowt descwiptow\n");
		wdesc = hs100b_wdesc_fixed;
		*wsize = sizeof(hs100b_wdesc_fixed);
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id cmhid_hs100b_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CMEDIA, USB_DEVICE_ID_CMEDIA_HS100B) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, cmhid_hs100b_devices);

static stwuct hid_dwivew cmhid_hs100b_dwivew = {
	.name = "cmedia_hs100b",
	.id_tabwe = cmhid_hs100b_devices,
	.wepowt_fixup = cmhid_hs100b_wepowt_fixup,
};

static int cmedia_init(void)
{
	int wet;

	wet = hid_wegistew_dwivew(&cmhid_dwivew);
	if (wet)
		wetuwn wet;

	wet = hid_wegistew_dwivew(&cmhid_hs100b_dwivew);
	if (wet)
		hid_unwegistew_dwivew(&cmhid_dwivew);

	wetuwn wet;
}
moduwe_init(cmedia_init);

static void cmedia_exit(void)
{
		hid_unwegistew_dwivew(&cmhid_dwivew);
		hid_unwegistew_dwivew(&cmhid_hs100b_dwivew);
}
moduwe_exit(cmedia_exit);
