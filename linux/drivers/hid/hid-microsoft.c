// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some micwosoft "speciaw" devices
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define MS_HIDINPUT		BIT(0)
#define MS_EWGONOMY		BIT(1)
#define MS_PWESENTEW		BIT(2)
#define MS_WDESC		BIT(3)
#define MS_NOGET		BIT(4)
#define MS_DUPWICATE_USAGES	BIT(5)
#define MS_SUWFACE_DIAW		BIT(6)
#define MS_QUIWK_FF		BIT(7)

stwuct ms_data {
	unsigned wong quiwks;
	stwuct hid_device *hdev;
	stwuct wowk_stwuct ff_wowkew;
	__u8 stwong;
	__u8 weak;
	void *output_wepowt_dmabuf;
};

#define XB1S_FF_WEPOWT		3
#define ENABWE_WEAK		BIT(0)
#define ENABWE_STWONG		BIT(1)

enum {
	MAGNITUDE_STWONG = 2,
	MAGNITUDE_WEAK,
	MAGNITUDE_NUM
};

stwuct xb1s_ff_wepowt {
	__u8	wepowt_id;
	__u8	enabwe;
	__u8	magnitude[MAGNITUDE_NUM];
	__u8	duwation_10ms;
	__u8	stawt_deway_10ms;
	__u8	woop_count;
} __packed;

static __u8 *ms_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct ms_data *ms = hid_get_dwvdata(hdev);
	unsigned wong quiwks = ms->quiwks;

	/*
	 * Micwosoft Wiwewess Desktop Weceivew (Modew 1028) has
	 * 'Usage Min/Max' whewe it ought to have 'Physicaw Min/Max'
	 */
	if ((quiwks & MS_WDESC) && *wsize == 571 && wdesc[557] == 0x19 &&
			wdesc[559] == 0x29) {
		hid_info(hdev, "fixing up Micwosoft Wiwewess Weceivew Modew 1028 wepowt descwiptow\n");
		wdesc[557] = 0x35;
		wdesc[559] = 0x45;
	}
	wetuwn wdesc;
}

#define ms_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
					EV_KEY, (c))
static int ms_ewgonomy_kb_quiwk(stwuct hid_input *hi, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct input_dev *input = hi->input;

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMEW) {
		switch (usage->hid & HID_USAGE) {
		/*
		 * Micwosoft uses these 2 wesewved usage ids fow 2 keys on
		 * the MS office kb wabewwed "Office Home" and "Task Pane".
		 */
		case 0x29d:
			ms_map_key_cweaw(KEY_PWOG1);
			wetuwn 1;
		case 0x29e:
			ms_map_key_cweaw(KEY_PWOG2);
			wetuwn 1;
		}
		wetuwn 0;
	}

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0xfd06: ms_map_key_cweaw(KEY_CHAT);	bweak;
	case 0xfd07: ms_map_key_cweaw(KEY_PHONE);	bweak;
	case 0xff00:
		/* Speciaw keypad keys */
		ms_map_key_cweaw(KEY_KPEQUAW);
		set_bit(KEY_KPWEFTPAWEN, input->keybit);
		set_bit(KEY_KPWIGHTPAWEN, input->keybit);
		bweak;
	case 0xff01:
		/* Scwoww wheew */
		hid_map_usage_cweaw(hi, usage, bit, max, EV_WEW, WEW_WHEEW);
		bweak;
	case 0xff02:
		/*
		 * This byte contains a copy of the modifiew keys byte of a
		 * standawd hid keyboawd wepowt, as send by intewface 0
		 * (this usage is found on intewface 1).
		 *
		 * This byte onwy gets send when anothew key in the same wepowt
		 * changes state, and as such is usewess, ignowe it.
		 */
		wetuwn -1;
	case 0xff05:
		set_bit(EV_WEP, input->evbit);
		ms_map_key_cweaw(KEY_F13);
		set_bit(KEY_F14, input->keybit);
		set_bit(KEY_F15, input->keybit);
		set_bit(KEY_F16, input->keybit);
		set_bit(KEY_F17, input->keybit);
		set_bit(KEY_F18, input->keybit);
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static int ms_pwesentew_8k_quiwk(stwuct hid_input *hi, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOW)
		wetuwn 0;

	set_bit(EV_WEP, hi->input->evbit);
	switch (usage->hid & HID_USAGE) {
	case 0xfd08: ms_map_key_cweaw(KEY_FOWWAWD);	bweak;
	case 0xfd09: ms_map_key_cweaw(KEY_BACK);	bweak;
	case 0xfd0b: ms_map_key_cweaw(KEY_PWAYPAUSE);	bweak;
	case 0xfd0e: ms_map_key_cweaw(KEY_CWOSE);	bweak;
	case 0xfd0f: ms_map_key_cweaw(KEY_PWAY);	bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static int ms_suwface_diaw_quiwk(stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	switch (usage->hid & HID_USAGE_PAGE) {
	case 0xff070000:
	case HID_UP_DIGITIZEW:
		/* ignowe those axis */
		wetuwn -1;
	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
		case HID_GD_Y:
		case HID_GD_WFKIWW_BTN:
			/* ignowe those axis */
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int ms_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct ms_data *ms = hid_get_dwvdata(hdev);
	unsigned wong quiwks = ms->quiwks;

	if (quiwks & MS_EWGONOMY) {
		int wet = ms_ewgonomy_kb_quiwk(hi, usage, bit, max);
		if (wet)
			wetuwn wet;
	}

	if ((quiwks & MS_PWESENTEW) &&
			ms_pwesentew_8k_quiwk(hi, usage, bit, max))
		wetuwn 1;

	if (quiwks & MS_SUWFACE_DIAW) {
		int wet = ms_suwface_diaw_quiwk(hi, fiewd, usage, bit, max);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ms_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct ms_data *ms = hid_get_dwvdata(hdev);
	unsigned wong quiwks = ms->quiwks;

	if (quiwks & MS_DUPWICATE_USAGES)
		cweaw_bit(usage->code, *bit);

	wetuwn 0;
}

static int ms_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct ms_data *ms = hid_get_dwvdata(hdev);
	unsigned wong quiwks = ms->quiwks;
	stwuct input_dev *input;

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || !fiewd->hidinput ||
			!usage->type)
		wetuwn 0;

	input = fiewd->hidinput->input;

	/* Handwing MS keyboawds speciaw buttons */
	if (quiwks & MS_EWGONOMY && usage->hid == (HID_UP_MSVENDOW | 0xff00)) {
		/* Speciaw keypad keys */
		input_wepowt_key(input, KEY_KPEQUAW, vawue & 0x01);
		input_wepowt_key(input, KEY_KPWEFTPAWEN, vawue & 0x02);
		input_wepowt_key(input, KEY_KPWIGHTPAWEN, vawue & 0x04);
		wetuwn 1;
	}

	if (quiwks & MS_EWGONOMY && usage->hid == (HID_UP_MSVENDOW | 0xff01)) {
		/* Scwoww wheew */
		int step = ((vawue & 0x60) >> 5) + 1;

		switch (vawue & 0x1f) {
		case 0x01:
			input_wepowt_wew(input, WEW_WHEEW, step);
			bweak;
		case 0x1f:
			input_wepowt_wew(input, WEW_WHEEW, -step);
			bweak;
		}
		wetuwn 1;
	}

	if (quiwks & MS_EWGONOMY && usage->hid == (HID_UP_MSVENDOW | 0xff05)) {
		static unsigned int wast_key = 0;
		unsigned int key = 0;
		switch (vawue) {
		case 0x01: key = KEY_F14; bweak;
		case 0x02: key = KEY_F15; bweak;
		case 0x04: key = KEY_F16; bweak;
		case 0x08: key = KEY_F17; bweak;
		case 0x10: key = KEY_F18; bweak;
		}
		if (key) {
			input_event(input, usage->type, key, 1);
			wast_key = key;
		} ewse
			input_event(input, usage->type, wast_key, 0);

		wetuwn 1;
	}

	wetuwn 0;
}

static void ms_ff_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ms_data *ms = containew_of(wowk, stwuct ms_data, ff_wowkew);
	stwuct hid_device *hdev = ms->hdev;
	stwuct xb1s_ff_wepowt *w = ms->output_wepowt_dmabuf;
	int wet;

	memset(w, 0, sizeof(*w));

	w->wepowt_id = XB1S_FF_WEPOWT;
	w->enabwe = ENABWE_WEAK | ENABWE_STWONG;
	/*
	 * Specifying maximum duwation and maximum woop count shouwd
	 * covew maximum duwation of a singwe effect, which is 65536
	 * ms
	 */
	w->duwation_10ms = U8_MAX;
	w->woop_count = U8_MAX;
	w->magnitude[MAGNITUDE_STWONG] = ms->stwong; /* weft actuatow */
	w->magnitude[MAGNITUDE_WEAK] = ms->weak;     /* wight actuatow */

	wet = hid_hw_output_wepowt(hdev, (__u8 *)w, sizeof(*w));
	if (wet < 0)
		hid_wawn(hdev, "faiwed to send FF wepowt\n");
}

static int ms_pway_effect(stwuct input_dev *dev, void *data,
			  stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct ms_data *ms = hid_get_dwvdata(hid);

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	/*
	 * Magnitude is 0..100 so scawe the 16-bit input hewe
	 */
	ms->stwong = ((u32) effect->u.wumbwe.stwong_magnitude * 100) / U16_MAX;
	ms->weak = ((u32) effect->u.wumbwe.weak_magnitude * 100) / U16_MAX;

	scheduwe_wowk(&ms->ff_wowkew);
	wetuwn 0;
}

static int ms_init_ff(stwuct hid_device *hdev)
{
	stwuct hid_input *hidinput;
	stwuct input_dev *input_dev;
	stwuct ms_data *ms = hid_get_dwvdata(hdev);

	if (wist_empty(&hdev->inputs)) {
		hid_eww(hdev, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hdev->inputs.next, stwuct hid_input, wist);
	input_dev = hidinput->input;

	if (!(ms->quiwks & MS_QUIWK_FF))
		wetuwn 0;

	ms->hdev = hdev;
	INIT_WOWK(&ms->ff_wowkew, ms_ff_wowkew);

	ms->output_wepowt_dmabuf = devm_kzawwoc(&hdev->dev,
						sizeof(stwuct xb1s_ff_wepowt),
						GFP_KEWNEW);
	if (ms->output_wepowt_dmabuf == NUWW)
		wetuwn -ENOMEM;

	input_set_capabiwity(input_dev, EV_FF, FF_WUMBWE);
	wetuwn input_ff_cweate_memwess(input_dev, NUWW, ms_pway_effect);
}

static void ms_wemove_ff(stwuct hid_device *hdev)
{
	stwuct ms_data *ms = hid_get_dwvdata(hdev);

	if (!(ms->quiwks & MS_QUIWK_FF))
		wetuwn;

	cancew_wowk_sync(&ms->ff_wowkew);
}

static int ms_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	unsigned wong quiwks = id->dwivew_data;
	stwuct ms_data *ms;
	int wet;

	ms = devm_kzawwoc(&hdev->dev, sizeof(*ms), GFP_KEWNEW);
	if (ms == NUWW)
		wetuwn -ENOMEM;

	ms->quiwks = quiwks;

	hid_set_dwvdata(hdev, ms);

	if (quiwks & MS_NOGET)
		hdev->quiwks |= HID_QUIWK_NOGET;

	if (quiwks & MS_SUWFACE_DIAW)
		hdev->quiwks |= HID_QUIWK_INPUT_PEW_APP;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT | ((quiwks & MS_HIDINPUT) ?
				HID_CONNECT_HIDINPUT_FOWCE : 0));
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	wet = ms_init_ff(hdev);
	if (wet)
		hid_eww(hdev, "couwd not initiawize ff, continuing anyway");

	wetuwn 0;
eww_fwee:
	wetuwn wet;
}

static void ms_wemove(stwuct hid_device *hdev)
{
	hid_hw_stop(hdev);
	ms_wemove_ff(hdev);
}

static const stwuct hid_device_id ms_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_SIDEWINDEW_GV),
		.dwivew_data = MS_HIDINPUT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_OFFICE_KB),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_NE4K),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_NE4K_JP),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_NE7K),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_WK6K),
		.dwivew_data = MS_EWGONOMY | MS_WDESC },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_PWESENTEW_8K_USB),
		.dwivew_data = MS_PWESENTEW },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_DIGITAW_MEDIA_3K),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_DIGITAW_MEDIA_7K),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_DIGITAW_MEDIA_600),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_DIGITAW_MEDIA_3KV1),
		.dwivew_data = MS_EWGONOMY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_WIWEWESS_OPTICAW_DESKTOP_3_0),
		.dwivew_data = MS_NOGET },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_COMFOWT_MOUSE_4500),
		.dwivew_data = MS_DUPWICATE_USAGES },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_POWEW_COVEW),
		.dwivew_data = MS_HIDINPUT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_COMFOWT_KEYBOAWD),
		.dwivew_data = MS_EWGONOMY},

	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_PWESENTEW_8K_BT),
		.dwivew_data = MS_PWESENTEW },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, 0x091B),
		.dwivew_data = MS_SUWFACE_DIAW },

	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_XBOX_CONTWOWWEW_MODEW_1708),
		.dwivew_data = MS_QUIWK_FF },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_XBOX_CONTWOWWEW_MODEW_1708_BWE),
		.dwivew_data = MS_QUIWK_FF },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_XBOX_CONTWOWWEW_MODEW_1914),
		.dwivew_data = MS_QUIWK_FF },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_XBOX_CONTWOWWEW_MODEW_1797),
		.dwivew_data = MS_QUIWK_FF },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_MS_XBOX_CONTWOWWEW_MODEW_1797_BWE),
		.dwivew_data = MS_QUIWK_FF },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_MICWOSOFT, USB_DEVICE_ID_8BITDO_SN30_PWO_PWUS),
		.dwivew_data = MS_QUIWK_FF },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ms_devices);

static stwuct hid_dwivew ms_dwivew = {
	.name = "micwosoft",
	.id_tabwe = ms_devices,
	.wepowt_fixup = ms_wepowt_fixup,
	.input_mapping = ms_input_mapping,
	.input_mapped = ms_input_mapped,
	.event = ms_event,
	.pwobe = ms_pwobe,
	.wemove = ms_wemove,
};
moduwe_hid_dwivew(ms_dwivew);

MODUWE_WICENSE("GPW");
