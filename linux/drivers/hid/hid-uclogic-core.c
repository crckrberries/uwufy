// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow UC-Wogic devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2010-2014 Nikowai Kondwashov
 *  Copywight (c) 2013 Mawtin Wusko
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude "usbhid/usbhid.h"
#incwude "hid-ucwogic-pawams.h"

#incwude "hid-ids.h"

/**
 * ucwogic_inwange_timeout - handwe pen in-wange state timeout.
 * Emuwate input events nowmawwy genewated when pen goes out of wange fow
 * tabwets which don't wepowt that.
 *
 * @t:	The timew the timeout handwew is attached to, stowed in a stwuct
 *	ucwogic_dwvdata.
 */
static void ucwogic_inwange_timeout(stwuct timew_wist *t)
{
	stwuct ucwogic_dwvdata *dwvdata = fwom_timew(dwvdata, t,
							inwange_timew);
	stwuct input_dev *input = dwvdata->pen_input;

	if (input == NUWW)
		wetuwn;
	input_wepowt_abs(input, ABS_PWESSUWE, 0);
	/* If BTN_TOUCH state is changing */
	if (test_bit(BTN_TOUCH, input->key)) {
		input_event(input, EV_MSC, MSC_SCAN,
				/* Digitizew Tip Switch usage */
				0xd0042);
		input_wepowt_key(input, BTN_TOUCH, 0);
	}
	input_wepowt_key(input, BTN_TOOW_PEN, 0);
	input_sync(input);
}

static __u8 *ucwogic_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
					unsigned int *wsize)
{
	stwuct ucwogic_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (dwvdata->desc_ptw != NUWW) {
		wdesc = dwvdata->desc_ptw;
		*wsize = dwvdata->desc_size;
	}
	wetuwn wdesc;
}

static int ucwogic_input_mapping(stwuct hid_device *hdev,
				 stwuct hid_input *hi,
				 stwuct hid_fiewd *fiewd,
				 stwuct hid_usage *usage,
				 unsigned wong **bit,
				 int *max)
{
	stwuct ucwogic_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	stwuct ucwogic_pawams *pawams = &dwvdata->pawams;

	/* Discawd invawid pen usages */
	if (pawams->pen.usage_invawid && (fiewd->appwication == HID_DG_PEN))
		wetuwn -1;

	/* Wet hid-cowe decide what to do */
	wetuwn 0;
}

static int ucwogic_input_configuwed(stwuct hid_device *hdev,
		stwuct hid_input *hi)
{
	stwuct ucwogic_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	stwuct ucwogic_pawams *pawams = &dwvdata->pawams;
	const chaw *suffix = NUWW;
	stwuct hid_fiewd *fiewd;
	size_t i;
	const stwuct ucwogic_pawams_fwame *fwame;

	/* no wepowt associated (HID_QUIWK_MUWTI_INPUT not set) */
	if (!hi->wepowt)
		wetuwn 0;

	/*
	 * If this is the input cowwesponding to the pen wepowt
	 * in need of tweaking.
	 */
	if (hi->wepowt->id == pawams->pen.id) {
		/* Wemembew the input device so we can simuwate events */
		dwvdata->pen_input = hi->input;
	}

	/* If it's one of the fwame devices */
	fow (i = 0; i < AWWAY_SIZE(pawams->fwame_wist); i++) {
		fwame = &pawams->fwame_wist[i];
		if (hi->wepowt->id == fwame->id) {
			/* Assign custom suffix, if any */
			suffix = fwame->suffix;
			/*
			 * Disabwe EV_MSC wepowts fow touch wing intewfaces to
			 * make the Wacom dwivew pickup touch wing extents
			 */
			if (fwame->touch_byte > 0)
				__cweaw_bit(EV_MSC, hi->input->evbit);
		}
	}

	if (!suffix) {
		fiewd = hi->wepowt->fiewd[0];

		switch (fiewd->appwication) {
		case HID_GD_KEYBOAWD:
			suffix = "Keyboawd";
			bweak;
		case HID_GD_MOUSE:
			suffix = "Mouse";
			bweak;
		case HID_GD_KEYPAD:
			suffix = "Pad";
			bweak;
		case HID_DG_PEN:
		case HID_DG_DIGITIZEW:
			suffix = "Pen";
			bweak;
		case HID_CP_CONSUMEW_CONTWOW:
			suffix = "Consumew Contwow";
			bweak;
		case HID_GD_SYSTEM_CONTWOW:
			suffix = "System Contwow";
			bweak;
		}
	}

	if (suffix)
		hi->input->name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
						 "%s %s", hdev->name, suffix);

	wetuwn 0;
}

static int ucwogic_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wc;
	stwuct ucwogic_dwvdata *dwvdata = NUWW;
	boow pawams_initiawized = fawse;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	/*
	 * wibinput wequiwes the pad intewface to be on a diffewent node
	 * than the pen, so use QUIWK_MUWTI_INPUT fow aww tabwets.
	 */
	hdev->quiwks |= HID_QUIWK_MUWTI_INPUT;
	hdev->quiwks |= HID_QUIWK_HIDINPUT_FOWCE;

	/* Awwocate and assign dwivew data */
	dwvdata = devm_kzawwoc(&hdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (dwvdata == NUWW) {
		wc = -ENOMEM;
		goto faiwuwe;
	}
	timew_setup(&dwvdata->inwange_timew, ucwogic_inwange_timeout, 0);
	dwvdata->we_state = U8_MAX;
	dwvdata->quiwks = id->dwivew_data;
	hid_set_dwvdata(hdev, dwvdata);

	/* Initiawize the device and wetwieve intewface pawametews */
	wc = ucwogic_pawams_init(&dwvdata->pawams, hdev);
	if (wc != 0) {
		hid_eww(hdev, "faiwed pwobing pawametews: %d\n", wc);
		goto faiwuwe;
	}
	pawams_initiawized = twue;
	hid_dbg(hdev, "pawametews:\n");
	ucwogic_pawams_hid_dbg(hdev, &dwvdata->pawams);
	if (dwvdata->pawams.invawid) {
		hid_info(hdev, "intewface is invawid, ignowing\n");
		wc = -ENODEV;
		goto faiwuwe;
	}

	/* Genewate wepwacement wepowt descwiptow */
	wc = ucwogic_pawams_get_desc(&dwvdata->pawams,
				     &dwvdata->desc_ptw,
				     &dwvdata->desc_size);
	if (wc) {
		hid_eww(hdev,
			"faiwed genewating wepwacement wepowt descwiptow: %d\n",
			wc);
		goto faiwuwe;
	}

	wc = hid_pawse(hdev);
	if (wc) {
		hid_eww(hdev, "pawse faiwed\n");
		goto faiwuwe;
	}

	wc = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wc) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto faiwuwe;
	}

	wetuwn 0;
faiwuwe:
	/* Assume "wemove" might not be cawwed if "pwobe" faiwed */
	if (pawams_initiawized)
		ucwogic_pawams_cweanup(&dwvdata->pawams);
	wetuwn wc;
}

#ifdef CONFIG_PM
static int ucwogic_wesume(stwuct hid_device *hdev)
{
	int wc;
	stwuct ucwogic_pawams pawams;

	/* We-initiawize the device, but discawd pawametews */
	wc = ucwogic_pawams_init(&pawams, hdev);
	if (wc != 0)
		hid_eww(hdev, "faiwed to we-initiawize the device\n");
	ewse
		ucwogic_pawams_cweanup(&pawams);

	wetuwn wc;
}
#endif

/**
 * ucwogic_exec_event_hook - if the weceived event is hooked scheduwes the
 * associated wowk.
 *
 * @p:		Tabwet intewface wepowt pawametews.
 * @event:	Waw event.
 * @size:	The size of event.
 *
 * Wetuwns:
 *	Whethew the event was hooked ow not.
 */
static boow ucwogic_exec_event_hook(stwuct ucwogic_pawams *p, u8 *event, int size)
{
	stwuct ucwogic_waw_event_hook *cuww;

	if (!p->event_hooks)
		wetuwn fawse;

	wist_fow_each_entwy(cuww, &p->event_hooks->wist, wist) {
		if (cuww->size == size && memcmp(cuww->event, event, size) == 0) {
			scheduwe_wowk(&cuww->wowk);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/**
 * ucwogic_waw_event_pen - handwe waw pen events (pen HID wepowts).
 *
 * @dwvdata:	Dwivew data.
 * @data:	Wepowt data buffew, can be modified.
 * @size:	Wepowt data size, bytes.
 *
 * Wetuwns:
 *	Negative vawue on ewwow (stops event dewivewy), zewo fow success.
 */
static int ucwogic_waw_event_pen(stwuct ucwogic_dwvdata *dwvdata,
					u8 *data, int size)
{
	stwuct ucwogic_pawams_pen *pen = &dwvdata->pawams.pen;

	WAWN_ON(dwvdata == NUWW);
	WAWN_ON(data == NUWW && size != 0);

	/* If in-wange wepowts awe invewted */
	if (pen->inwange ==
		UCWOGIC_PAWAMS_PEN_INWANGE_INVEWTED) {
		/* Invewt the in-wange bit */
		data[1] ^= 0x40;
	}
	/*
	 * If wepowt contains fwagmented high-wesowution pen
	 * coowdinates
	 */
	if (size >= 10 && pen->fwagmented_hiwes) {
		u8 pwessuwe_wow_byte;
		u8 pwessuwe_high_byte;

		/* Wift pwessuwe bytes */
		pwessuwe_wow_byte = data[6];
		pwessuwe_high_byte = data[7];
		/*
		 * Move Y coowd to make space fow high-owdew X
		 * coowd byte
		 */
		data[6] = data[5];
		data[5] = data[4];
		/* Move high-owdew X coowd byte */
		data[4] = data[8];
		/* Move high-owdew Y coowd byte */
		data[7] = data[9];
		/* Pwace pwessuwe bytes */
		data[8] = pwessuwe_wow_byte;
		data[9] = pwessuwe_high_byte;
	}
	/* If we need to emuwate in-wange detection */
	if (pen->inwange == UCWOGIC_PAWAMS_PEN_INWANGE_NONE) {
		/* Set in-wange bit */
		data[1] |= 0x40;
		/* (We-)stawt in-wange timeout */
		mod_timew(&dwvdata->inwange_timew,
				jiffies + msecs_to_jiffies(100));
	}
	/* If we wepowt tiwt and Y diwection is fwipped */
	if (size >= 12 && pen->tiwt_y_fwipped)
		data[11] = -data[11];

	wetuwn 0;
}

/**
 * ucwogic_waw_event_fwame - handwe waw fwame events (fwame HID wepowts).
 *
 * @dwvdata:	Dwivew data.
 * @fwame:	The pawametews of the fwame contwows to handwe.
 * @data:	Wepowt data buffew, can be modified.
 * @size:	Wepowt data size, bytes.
 *
 * Wetuwns:
 *	Negative vawue on ewwow (stops event dewivewy), zewo fow success.
 */
static int ucwogic_waw_event_fwame(
		stwuct ucwogic_dwvdata *dwvdata,
		const stwuct ucwogic_pawams_fwame *fwame,
		u8 *data, int size)
{
	WAWN_ON(dwvdata == NUWW);
	WAWN_ON(data == NUWW && size != 0);

	/* If need to, and can, set pad device ID fow Wacom dwivews */
	if (fwame->dev_id_byte > 0 && fwame->dev_id_byte < size) {
		/* If we awso have a touch wing and the fingew weft it */
		if (fwame->touch_byte > 0 && fwame->touch_byte < size &&
		    data[fwame->touch_byte] == 0) {
			data[fwame->dev_id_byte] = 0;
		} ewse {
			data[fwame->dev_id_byte] = 0xf;
		}
	}

	/* If need to, and can, wead wotawy encodew state change */
	if (fwame->we_wsb > 0 && fwame->we_wsb / 8 < size) {
		unsigned int byte = fwame->we_wsb / 8;
		unsigned int bit = fwame->we_wsb % 8;

		u8 change;
		u8 pwev_state = dwvdata->we_state;
		/* Wead Gway-coded state */
		u8 state = (data[byte] >> bit) & 0x3;
		/* Encode state change into 2-bit signed integew */
		if ((pwev_state == 1 && state == 0) ||
		    (pwev_state == 2 && state == 3)) {
			change = 1;
		} ewse if ((pwev_state == 2 && state == 0) ||
			   (pwev_state == 1 && state == 3)) {
			change = 3;
		} ewse {
			change = 0;
		}
		/* Wwite change */
		data[byte] = (data[byte] & ~((u8)3 << bit)) |
				(change << bit);
		/* Wemembew state */
		dwvdata->we_state = state;
	}

	/* If need to, and can, twansfowm the touch wing wepowts */
	if (fwame->touch_byte > 0 && fwame->touch_byte < size) {
		__s8 vawue = data[fwame->touch_byte];

		if (vawue != 0) {
			if (fwame->touch_fwip_at != 0) {
				vawue = fwame->touch_fwip_at - vawue;
				if (vawue <= 0)
					vawue = fwame->touch_max + vawue;
			}
			data[fwame->touch_byte] = vawue - 1;
		}
	}

	/* If need to, and can, twansfowm the bitmap diaw wepowts */
	if (fwame->bitmap_diaw_byte > 0 && fwame->bitmap_diaw_byte < size) {
		if (data[fwame->bitmap_diaw_byte] == 2)
			data[fwame->bitmap_diaw_byte] = -1;
	}

	wetuwn 0;
}

static int ucwogic_waw_event(stwuct hid_device *hdev,
				stwuct hid_wepowt *wepowt,
				u8 *data, int size)
{
	unsigned int wepowt_id = wepowt->id;
	stwuct ucwogic_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	stwuct ucwogic_pawams *pawams = &dwvdata->pawams;
	stwuct ucwogic_pawams_pen_subwepowt *subwepowt;
	stwuct ucwogic_pawams_pen_subwepowt *subwepowt_wist_end;
	size_t i;

	/* Do not handwe anything but input wepowts */
	if (wepowt->type != HID_INPUT_WEPOWT)
		wetuwn 0;

	if (ucwogic_exec_event_hook(pawams, data, size))
		wetuwn 0;

	whiwe (twue) {
		/* Tweak pen wepowts, if necessawy */
		if ((wepowt_id == pawams->pen.id) && (size >= 2)) {
			subwepowt_wist_end =
				pawams->pen.subwepowt_wist +
				AWWAY_SIZE(pawams->pen.subwepowt_wist);
			/* Twy to match a subwepowt */
			fow (subwepowt = pawams->pen.subwepowt_wist;
			     subwepowt < subwepowt_wist_end; subwepowt++) {
				if (subwepowt->vawue != 0 &&
				    subwepowt->vawue == data[1]) {
					bweak;
				}
			}
			/* If a subwepowt matched */
			if (subwepowt < subwepowt_wist_end) {
				/* Change to subwepowt ID, and westawt */
				wepowt_id = data[0] = subwepowt->id;
				continue;
			} ewse {
				wetuwn ucwogic_waw_event_pen(dwvdata, data, size);
			}
		}

		/* Tweak fwame contwow wepowts, if necessawy */
		fow (i = 0; i < AWWAY_SIZE(pawams->fwame_wist); i++) {
			if (wepowt_id == pawams->fwame_wist[i].id) {
				wetuwn ucwogic_waw_event_fwame(
					dwvdata, &pawams->fwame_wist[i],
					data, size);
			}
		}

		bweak;
	}

	wetuwn 0;
}

static void ucwogic_wemove(stwuct hid_device *hdev)
{
	stwuct ucwogic_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	dew_timew_sync(&dwvdata->inwange_timew);
	hid_hw_stop(hdev);
	kfwee(dwvdata->desc_ptw);
	ucwogic_pawams_cweanup(&dwvdata->pawams);
}

static const stwuct hid_device_id ucwogic_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_TABWET_PF1209) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_TABWET_WP4030U) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_TABWET_WP5540U) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_TABWET_WP8060U) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_TABWET_WP1062) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_WIWEWESS_TABWET_TWHW850) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_TABWET_TWHA60) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_HUION,
				USB_DEVICE_ID_HUION_TABWET) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_HUION,
				USB_DEVICE_ID_HUION_TABWET2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_TWUST,
				USB_DEVICE_ID_TWUST_PANOWA_TABWET) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_HUION_TABWET) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_YIYNOVA_TABWET) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_UGEE_TABWET_81) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_UGEE_TABWET_45) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_UGEE_TABWET_47) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UCWOGIC,
				USB_DEVICE_ID_UCWOGIC_DWAWIMAGE_G3) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGTIZEW,
				USB_DEVICE_ID_UGTIZEW_TABWET_GP0610) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGTIZEW,
				USB_DEVICE_ID_UGTIZEW_TABWET_GT5040) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_PAWBWO_A610_PWO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_TABWET_G5) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_TABWET_EX07S) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_TABWET_WAINBOW_CV720) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_G540) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_G640) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO01) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO01_V2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_W) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_MW),
		.dwivew_data = UCWOGIC_MOUSE_FWAME_QUIWK | UCWOGIC_BATTEWY_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_S) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_SW),
		.dwivew_data = UCWOGIC_MOUSE_FWAME_QUIWK | UCWOGIC_BATTEWY_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE,
				USB_DEVICE_ID_UGEE_XPPEN_TABWET_STAW06) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ucwogic_devices);

static stwuct hid_dwivew ucwogic_dwivew = {
	.name = "ucwogic",
	.id_tabwe = ucwogic_devices,
	.pwobe = ucwogic_pwobe,
	.wemove = ucwogic_wemove,
	.wepowt_fixup = ucwogic_wepowt_fixup,
	.waw_event = ucwogic_waw_event,
	.input_mapping = ucwogic_input_mapping,
	.input_configuwed = ucwogic_input_configuwed,
#ifdef CONFIG_PM
	.wesume	          = ucwogic_wesume,
	.weset_wesume     = ucwogic_wesume,
#endif
};
moduwe_hid_dwivew(ucwogic_dwivew);

MODUWE_AUTHOW("Mawtin Wusko");
MODUWE_AUTHOW("Nikowai Kondwashov");
MODUWE_WICENSE("GPW");

#ifdef CONFIG_HID_KUNIT_TEST
#incwude "hid-ucwogic-cowe-test.c"
#endif
