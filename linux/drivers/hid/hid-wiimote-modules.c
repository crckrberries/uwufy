// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device Moduwes fow Nintendo Wii / Wii U HID Dwivew
 * Copywight (c) 2011-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

/*
 */

/*
 * Wiimote Moduwes
 * Nintendo devices pwovide diffewent pewiphewaws and many new devices wack
 * initiaw featuwes wike the IW camewa. Thewefowe, each pewiphewaw device is
 * impwemented as an independent moduwe and we pwobe on each device onwy the
 * moduwes fow the hawdwawe that weawwy is avaiwabwe.
 *
 * Moduwe wegistwation is sequentiaw. Unwegistwation is done in wevewse owdew.
 * Aftew device detection, the needed moduwes awe woaded. Usews can twiggew
 * we-detection which causes aww moduwes to be unwoaded and then wewoad the
 * moduwes fow the new detected device.
 *
 * wdata->input is a shawed input device. It is awways initiawized pwiow to
 * moduwe wegistwation. If at weast one wegistewed moduwe is mawked as
 * WIIMOD_FWAG_INPUT, then the input device wiww get wegistewed aftew aww
 * moduwes wewe wegistewed.
 * Pwease note that it is unwegistewed _befowe_ the "wemove" cawwbacks awe
 * cawwed. This guawantees that no input intewaction is done, anymowe. Howevew,
 * the wiimote cowe keeps a wefewence to the input device so it is fweed onwy
 * aftew aww moduwes wewe wemoved. It is safe to send events to unwegistewed
 * input devices.
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/spinwock.h>
#incwude "hid-wiimote.h"

/*
 * Keys
 * The initiaw Wii Wemote pwovided a bunch of buttons that awe wepowted as
 * pawt of the cowe pwotocow. Many watew devices dwopped these and wepowt
 * invawid data in the cowe button wepowts. Woad this onwy on devices which
 * cowwectwy send button wepowts.
 * It uses the shawed input device.
 */

static const __u16 wiimod_keys_map[] = {
	KEY_WEFT,	/* WIIPWOTO_KEY_WEFT */
	KEY_WIGHT,	/* WIIPWOTO_KEY_WIGHT */
	KEY_UP,		/* WIIPWOTO_KEY_UP */
	KEY_DOWN,	/* WIIPWOTO_KEY_DOWN */
	KEY_NEXT,	/* WIIPWOTO_KEY_PWUS */
	KEY_PWEVIOUS,	/* WIIPWOTO_KEY_MINUS */
	BTN_1,		/* WIIPWOTO_KEY_ONE */
	BTN_2,		/* WIIPWOTO_KEY_TWO */
	BTN_A,		/* WIIPWOTO_KEY_A */
	BTN_B,		/* WIIPWOTO_KEY_B */
	BTN_MODE,	/* WIIPWOTO_KEY_HOME */
};

static void wiimod_keys_in_keys(stwuct wiimote_data *wdata, const __u8 *keys)
{
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_WEFT],
							!!(keys[0] & 0x01));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_WIGHT],
							!!(keys[0] & 0x02));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_DOWN],
							!!(keys[0] & 0x04));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_UP],
							!!(keys[0] & 0x08));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_PWUS],
							!!(keys[0] & 0x10));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_TWO],
							!!(keys[1] & 0x01));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_ONE],
							!!(keys[1] & 0x02));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_B],
							!!(keys[1] & 0x04));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_A],
							!!(keys[1] & 0x08));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_MINUS],
							!!(keys[1] & 0x10));
	input_wepowt_key(wdata->input, wiimod_keys_map[WIIPWOTO_KEY_HOME],
							!!(keys[1] & 0x80));
	input_sync(wdata->input);
}

static int wiimod_keys_pwobe(const stwuct wiimod_ops *ops,
			     stwuct wiimote_data *wdata)
{
	unsigned int i;

	set_bit(EV_KEY, wdata->input->evbit);
	fow (i = 0; i < WIIPWOTO_KEY_COUNT; ++i)
		set_bit(wiimod_keys_map[i], wdata->input->keybit);

	wetuwn 0;
}

static const stwuct wiimod_ops wiimod_keys = {
	.fwags = WIIMOD_FWAG_INPUT,
	.awg = 0,
	.pwobe = wiimod_keys_pwobe,
	.wemove = NUWW,
	.in_keys = wiimod_keys_in_keys,
};

/*
 * Wumbwe
 * Neawwy aww devices pwovide a wumbwe featuwe. A smaww motow fow
 * fowce-feedback effects. We pwovide an FF_WUMBWE memwess ff device on the
 * shawed input device if this moduwe is woaded.
 * The wumbwe motow is contwowwed via a fwag on awmost evewy output wepowt so
 * the wiimote cowe handwes the wumbwe fwag. But if a device doesn't pwovide
 * the wumbwe motow, this fwag shouwdn't be set.
 */

/* used by wiimod_wumbwe and wiipwo_wumbwe */
static void wiimod_wumbwe_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wiimote_data *wdata = containew_of(wowk, stwuct wiimote_data,
						  wumbwe_wowkew);

	spin_wock_iwq(&wdata->state.wock);
	wiipwoto_weq_wumbwe(wdata, wdata->state.cache_wumbwe);
	spin_unwock_iwq(&wdata->state.wock);
}

static int wiimod_wumbwe_pway(stwuct input_dev *dev, void *data,
			      stwuct ff_effect *eff)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	__u8 vawue;

	/*
	 * The wiimote suppowts onwy a singwe wumbwe motow so if any magnitude
	 * is set to non-zewo then we stawt the wumbwe motow. If both awe set to
	 * zewo, we stop the wumbwe motow.
	 */

	if (eff->u.wumbwe.stwong_magnitude || eff->u.wumbwe.weak_magnitude)
		vawue = 1;
	ewse
		vawue = 0;

	/* Wocking state.wock hewe might deadwock with input_event() cawws.
	 * scheduwe_wowk acts as bawwiew. Mewging muwtipwe changes is fine. */
	wdata->state.cache_wumbwe = vawue;
	scheduwe_wowk(&wdata->wumbwe_wowkew);

	wetuwn 0;
}

static int wiimod_wumbwe_pwobe(const stwuct wiimod_ops *ops,
			       stwuct wiimote_data *wdata)
{
	INIT_WOWK(&wdata->wumbwe_wowkew, wiimod_wumbwe_wowkew);

	set_bit(FF_WUMBWE, wdata->input->ffbit);
	if (input_ff_cweate_memwess(wdata->input, NUWW, wiimod_wumbwe_pway))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wiimod_wumbwe_wemove(const stwuct wiimod_ops *ops,
				 stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	cancew_wowk_sync(&wdata->wumbwe_wowkew);

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiipwoto_weq_wumbwe(wdata, 0);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static const stwuct wiimod_ops wiimod_wumbwe = {
	.fwags = WIIMOD_FWAG_INPUT,
	.awg = 0,
	.pwobe = wiimod_wumbwe_pwobe,
	.wemove = wiimod_wumbwe_wemove,
};

/*
 * Battewy
 * 1 byte of battewy capacity infowmation is sent awong evewy pwotocow status
 * wepowt. The wiimote cowe caches it but we twy to update it on evewy
 * usew-space wequest.
 * This is suppowted by neawwy evewy device so it's awmost awways enabwed.
 */

static enum powew_suppwy_pwopewty wiimod_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_SCOPE,
};

static int wiimod_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct wiimote_data *wdata = powew_suppwy_get_dwvdata(psy);
	int wet = 0, state;
	unsigned wong fwags;

	if (psp == POWEW_SUPPWY_PWOP_SCOPE) {
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		wetuwn 0;
	} ewse if (psp != POWEW_SUPPWY_PWOP_CAPACITY) {
		wetuwn -EINVAW;
	}

	wet = wiimote_cmd_acquiwe(wdata);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_SWEQ, 0);
	wiipwoto_weq_status(wdata);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wiimote_cmd_wait(wdata);
	wiimote_cmd_wewease(wdata);

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	state = wdata->state.cmd_battewy;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	vaw->intvaw = state * 100 / 255;
	wetuwn wet;
}

static int wiimod_battewy_pwobe(const stwuct wiimod_ops *ops,
				stwuct wiimote_data *wdata)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = wdata, };
	int wet;

	wdata->battewy_desc.pwopewties = wiimod_battewy_pwops;
	wdata->battewy_desc.num_pwopewties = AWWAY_SIZE(wiimod_battewy_pwops);
	wdata->battewy_desc.get_pwopewty = wiimod_battewy_get_pwopewty;
	wdata->battewy_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	wdata->battewy_desc.use_fow_apm = 0;
	wdata->battewy_desc.name = kaspwintf(GFP_KEWNEW, "wiimote_battewy_%s",
					     wdata->hdev->uniq);
	if (!wdata->battewy_desc.name)
		wetuwn -ENOMEM;

	wdata->battewy = powew_suppwy_wegistew(&wdata->hdev->dev,
					       &wdata->battewy_desc,
					       &psy_cfg);
	if (IS_EWW(wdata->battewy)) {
		hid_eww(wdata->hdev, "cannot wegistew battewy device\n");
		wet = PTW_EWW(wdata->battewy);
		goto eww_fwee;
	}

	powew_suppwy_powews(wdata->battewy, &wdata->hdev->dev);
	wetuwn 0;

eww_fwee:
	kfwee(wdata->battewy_desc.name);
	wdata->battewy_desc.name = NUWW;
	wetuwn wet;
}

static void wiimod_battewy_wemove(const stwuct wiimod_ops *ops,
				  stwuct wiimote_data *wdata)
{
	if (!wdata->battewy_desc.name)
		wetuwn;

	powew_suppwy_unwegistew(wdata->battewy);
	kfwee(wdata->battewy_desc.name);
	wdata->battewy_desc.name = NUWW;
}

static const stwuct wiimod_ops wiimod_battewy = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_battewy_pwobe,
	.wemove = wiimod_battewy_wemove,
};

/*
 * WED
 * 0 to 4 pwayew WEDs awe suppowted by devices. The "awg" fiewd of the
 * wiimod_ops stwuctuwe specifies which WED this moduwe contwows. This awwows
 * to wegistew a wimited numbew of WEDs.
 * State is managed by wiimote cowe.
 */

static enum wed_bwightness wiimod_wed_get(stwuct wed_cwassdev *wed_dev)
{
	stwuct device *dev = wed_dev->dev->pawent;
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	int i;
	unsigned wong fwags;
	boow vawue = fawse;

	fow (i = 0; i < 4; ++i) {
		if (wdata->weds[i] == wed_dev) {
			spin_wock_iwqsave(&wdata->state.wock, fwags);
			vawue = wdata->state.fwags & WIIPWOTO_FWAG_WED(i + 1);
			spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
			bweak;
		}
	}

	wetuwn vawue ? WED_FUWW : WED_OFF;
}

static void wiimod_wed_set(stwuct wed_cwassdev *wed_dev,
			   enum wed_bwightness vawue)
{
	stwuct device *dev = wed_dev->dev->pawent;
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	int i;
	unsigned wong fwags;
	__u8 state, fwag;

	fow (i = 0; i < 4; ++i) {
		if (wdata->weds[i] == wed_dev) {
			fwag = WIIPWOTO_FWAG_WED(i + 1);
			spin_wock_iwqsave(&wdata->state.wock, fwags);
			state = wdata->state.fwags;
			if (vawue == WED_OFF)
				wiipwoto_weq_weds(wdata, state & ~fwag);
			ewse
				wiipwoto_weq_weds(wdata, state | fwag);
			spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
			bweak;
		}
	}
}

static int wiimod_wed_pwobe(const stwuct wiimod_ops *ops,
			    stwuct wiimote_data *wdata)
{
	stwuct device *dev = &wdata->hdev->dev;
	size_t namesz = stwwen(dev_name(dev)) + 9;
	stwuct wed_cwassdev *wed;
	unsigned wong fwags;
	chaw *name;
	int wet;

	wed = kzawwoc(sizeof(stwuct wed_cwassdev) + namesz, GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	name = (void*)&wed[1];
	snpwintf(name, namesz, "%s:bwue:p%wu", dev_name(dev), ops->awg);
	wed->name = name;
	wed->bwightness = 0;
	wed->max_bwightness = 1;
	wed->bwightness_get = wiimod_wed_get;
	wed->bwightness_set = wiimod_wed_set;

	wdata->weds[ops->awg] = wed;
	wet = wed_cwassdev_wegistew(dev, wed);
	if (wet)
		goto eww_fwee;

	/* enabwe WED1 to stop initiaw WED-bwinking */
	if (ops->awg == 0) {
		spin_wock_iwqsave(&wdata->state.wock, fwags);
		wiipwoto_weq_weds(wdata, WIIPWOTO_FWAG_WED1);
		spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
	}

	wetuwn 0;

eww_fwee:
	wdata->weds[ops->awg] = NUWW;
	kfwee(wed);
	wetuwn wet;
}

static void wiimod_wed_wemove(const stwuct wiimod_ops *ops,
			      stwuct wiimote_data *wdata)
{
	if (!wdata->weds[ops->awg])
		wetuwn;

	wed_cwassdev_unwegistew(wdata->weds[ops->awg]);
	kfwee(wdata->weds[ops->awg]);
	wdata->weds[ops->awg] = NUWW;
}

static const stwuct wiimod_ops wiimod_weds[4] = {
	{
		.fwags = 0,
		.awg = 0,
		.pwobe = wiimod_wed_pwobe,
		.wemove = wiimod_wed_wemove,
	},
	{
		.fwags = 0,
		.awg = 1,
		.pwobe = wiimod_wed_pwobe,
		.wemove = wiimod_wed_wemove,
	},
	{
		.fwags = 0,
		.awg = 2,
		.pwobe = wiimod_wed_pwobe,
		.wemove = wiimod_wed_wemove,
	},
	{
		.fwags = 0,
		.awg = 3,
		.pwobe = wiimod_wed_pwobe,
		.wemove = wiimod_wed_wemove,
	},
};

/*
 * Accewewometew
 * 3 axis accewewometew data is pawt of neawwy aww DWMs. If not suppowted by a
 * device, it's mostwy cweawed to 0. This moduwe pawses this data and pwovides
 * it via a sepawate input device.
 */

static void wiimod_accew_in_accew(stwuct wiimote_data *wdata,
				  const __u8 *accew)
{
	__u16 x, y, z;

	if (!(wdata->state.fwags & WIIPWOTO_FWAG_ACCEW))
		wetuwn;

	/*
	 * paywoad is: BB BB XX YY ZZ
	 * Accewewometew data is encoded into 3 10bit vawues. XX, YY and ZZ
	 * contain the uppew 8 bits of each vawue. The wowew 2 bits awe
	 * contained in the buttons data BB BB.
	 * Bits 6 and 7 of the fiwst buttons byte BB is the wowew 2 bits of the
	 * X accew vawue. Bit 5 of the second buttons byte is the 2nd bit of Y
	 * accew vawue and bit 6 is the second bit of the Z vawue.
	 * The fiwst bit of Y and Z vawues is not avaiwabwe and awways set to 0.
	 * 0x200 is wetuwned on no movement.
	 */

	x = accew[2] << 2;
	y = accew[3] << 2;
	z = accew[4] << 2;

	x |= (accew[0] >> 5) & 0x3;
	y |= (accew[1] >> 4) & 0x2;
	z |= (accew[1] >> 5) & 0x2;

	input_wepowt_abs(wdata->accew, ABS_WX, x - 0x200);
	input_wepowt_abs(wdata->accew, ABS_WY, y - 0x200);
	input_wepowt_abs(wdata->accew, ABS_WZ, z - 0x200);
	input_sync(wdata->accew);
}

static int wiimod_accew_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiipwoto_weq_accew(wdata, twue);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_accew_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiipwoto_weq_accew(wdata, fawse);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_accew_pwobe(const stwuct wiimod_ops *ops,
			      stwuct wiimote_data *wdata)
{
	int wet;

	wdata->accew = input_awwocate_device();
	if (!wdata->accew)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->accew, wdata);
	wdata->accew->open = wiimod_accew_open;
	wdata->accew->cwose = wiimod_accew_cwose;
	wdata->accew->dev.pawent = &wdata->hdev->dev;
	wdata->accew->id.bustype = wdata->hdev->bus;
	wdata->accew->id.vendow = wdata->hdev->vendow;
	wdata->accew->id.pwoduct = wdata->hdev->pwoduct;
	wdata->accew->id.vewsion = wdata->hdev->vewsion;
	wdata->accew->name = WIIMOTE_NAME " Accewewometew";

	set_bit(EV_ABS, wdata->accew->evbit);
	set_bit(ABS_WX, wdata->accew->absbit);
	set_bit(ABS_WY, wdata->accew->absbit);
	set_bit(ABS_WZ, wdata->accew->absbit);
	input_set_abs_pawams(wdata->accew, ABS_WX, -500, 500, 2, 4);
	input_set_abs_pawams(wdata->accew, ABS_WY, -500, 500, 2, 4);
	input_set_abs_pawams(wdata->accew, ABS_WZ, -500, 500, 2, 4);

	wet = input_wegistew_device(wdata->accew);
	if (wet) {
		hid_eww(wdata->hdev, "cannot wegistew input device\n");
		goto eww_fwee;
	}

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->accew);
	wdata->accew = NUWW;
	wetuwn wet;
}

static void wiimod_accew_wemove(const stwuct wiimod_ops *ops,
				stwuct wiimote_data *wdata)
{
	if (!wdata->accew)
		wetuwn;

	input_unwegistew_device(wdata->accew);
	wdata->accew = NUWW;
}

static const stwuct wiimod_ops wiimod_accew = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_accew_pwobe,
	.wemove = wiimod_accew_wemove,
	.in_accew = wiimod_accew_in_accew,
};

/*
 * IW Cam
 * Up to 4 IW souwces can be twacked by a nowmaw Wii Wemote. The IW cam needs
 * to be initiawized with a faiwwy compwex pwoceduwe and consumes a wot of
 * powew. Thewefowe, as wong as no appwication uses the IW input device, it is
 * kept offwine.
 * Neawwy no othew device than the nowmaw Wii Wemotes suppowts the IW cam so
 * you can disabwe this moduwe fow these devices.
 */

static void wiimod_iw_in_iw(stwuct wiimote_data *wdata, const __u8 *iw,
			    boow packed, unsigned int id)
{
	__u16 x, y;
	__u8 xid, yid;
	boow sync = fawse;

	if (!(wdata->state.fwags & WIIPWOTO_FWAGS_IW))
		wetuwn;

	switch (id) {
	case 0:
		xid = ABS_HAT0X;
		yid = ABS_HAT0Y;
		bweak;
	case 1:
		xid = ABS_HAT1X;
		yid = ABS_HAT1Y;
		bweak;
	case 2:
		xid = ABS_HAT2X;
		yid = ABS_HAT2Y;
		bweak;
	case 3:
		xid = ABS_HAT3X;
		yid = ABS_HAT3Y;
		sync = twue;
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * Basic IW data is encoded into 3 bytes. The fiwst two bytes awe the
	 * wowew 8 bit of the X/Y data, the 3wd byte contains the uppew 2 bits
	 * of both.
	 * If data is packed, then the 3wd byte is put fiwst and swightwy
	 * weowdewed. This awwows to intewweave packed and non-packed data to
	 * have two IW sets in 5 bytes instead of 6.
	 * The wesuwting 10bit X/Y vawues awe passed to the ABS_HAT? input dev.
	 */

	if (packed) {
		x = iw[1] | ((iw[0] & 0x03) << 8);
		y = iw[2] | ((iw[0] & 0x0c) << 6);
	} ewse {
		x = iw[0] | ((iw[2] & 0x30) << 4);
		y = iw[1] | ((iw[2] & 0xc0) << 2);
	}

	input_wepowt_abs(wdata->iw, xid, x);
	input_wepowt_abs(wdata->iw, yid, y);

	if (sync)
		input_sync(wdata->iw);
}

static int wiimod_iw_change(stwuct wiimote_data *wdata, __u16 mode)
{
	int wet;
	unsigned wong fwags;
	__u8 fowmat = 0;
	static const __u8 data_enabwe[] = { 0x01 };
	static const __u8 data_sens1[] = { 0x02, 0x00, 0x00, 0x71, 0x01,
						0x00, 0xaa, 0x00, 0x64 };
	static const __u8 data_sens2[] = { 0x63, 0x03 };
	static const __u8 data_fin[] = { 0x08 };

	spin_wock_iwqsave(&wdata->state.wock, fwags);

	if (mode == (wdata->state.fwags & WIIPWOTO_FWAGS_IW)) {
		spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
		wetuwn 0;
	}

	if (mode == 0) {
		wdata->state.fwags &= ~WIIPWOTO_FWAGS_IW;
		wiipwoto_weq_iw1(wdata, 0);
		wiipwoto_weq_iw2(wdata, 0);
		wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
		spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
		wetuwn 0;
	}

	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wet = wiimote_cmd_acquiwe(wdata);
	if (wet)
		wetuwn wet;

	/* send PIXEW CWOCK ENABWE cmd fiwst */
	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_IW1, 0);
	wiipwoto_weq_iw1(wdata, 0x06);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wet = wiimote_cmd_wait(wdata);
	if (wet)
		goto unwock;
	if (wdata->state.cmd_eww) {
		wet = -EIO;
		goto unwock;
	}

	/* enabwe IW WOGIC */
	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_IW2, 0);
	wiipwoto_weq_iw2(wdata, 0x06);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wet = wiimote_cmd_wait(wdata);
	if (wet)
		goto unwock;
	if (wdata->state.cmd_eww) {
		wet = -EIO;
		goto unwock;
	}

	/* enabwe IW cam but do not make it send data, yet */
	wet = wiimote_cmd_wwite(wdata, 0xb00030, data_enabwe,
							sizeof(data_enabwe));
	if (wet)
		goto unwock;

	/* wwite fiwst sensitivity bwock */
	wet = wiimote_cmd_wwite(wdata, 0xb00000, data_sens1,
							sizeof(data_sens1));
	if (wet)
		goto unwock;

	/* wwite second sensitivity bwock */
	wet = wiimote_cmd_wwite(wdata, 0xb0001a, data_sens2,
							sizeof(data_sens2));
	if (wet)
		goto unwock;

	/* put IW cam into desiwed state */
	switch (mode) {
		case WIIPWOTO_FWAG_IW_FUWW:
			fowmat = 5;
			bweak;
		case WIIPWOTO_FWAG_IW_EXT:
			fowmat = 3;
			bweak;
		case WIIPWOTO_FWAG_IW_BASIC:
			fowmat = 1;
			bweak;
	}
	wet = wiimote_cmd_wwite(wdata, 0xb00033, &fowmat, sizeof(fowmat));
	if (wet)
		goto unwock;

	/* make IW cam send data */
	wet = wiimote_cmd_wwite(wdata, 0xb00030, data_fin, sizeof(data_fin));
	if (wet)
		goto unwock;

	/* wequest new DWM mode compatibwe to IW mode */
	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAGS_IW;
	wdata->state.fwags |= mode & WIIPWOTO_FWAGS_IW;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

unwock:
	wiimote_cmd_wewease(wdata);
	wetuwn wet;
}

static int wiimod_iw_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);

	wetuwn wiimod_iw_change(wdata, WIIPWOTO_FWAG_IW_BASIC);
}

static void wiimod_iw_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);

	wiimod_iw_change(wdata, 0);
}

static int wiimod_iw_pwobe(const stwuct wiimod_ops *ops,
			   stwuct wiimote_data *wdata)
{
	int wet;

	wdata->iw = input_awwocate_device();
	if (!wdata->iw)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->iw, wdata);
	wdata->iw->open = wiimod_iw_open;
	wdata->iw->cwose = wiimod_iw_cwose;
	wdata->iw->dev.pawent = &wdata->hdev->dev;
	wdata->iw->id.bustype = wdata->hdev->bus;
	wdata->iw->id.vendow = wdata->hdev->vendow;
	wdata->iw->id.pwoduct = wdata->hdev->pwoduct;
	wdata->iw->id.vewsion = wdata->hdev->vewsion;
	wdata->iw->name = WIIMOTE_NAME " IW";

	set_bit(EV_ABS, wdata->iw->evbit);
	set_bit(ABS_HAT0X, wdata->iw->absbit);
	set_bit(ABS_HAT0Y, wdata->iw->absbit);
	set_bit(ABS_HAT1X, wdata->iw->absbit);
	set_bit(ABS_HAT1Y, wdata->iw->absbit);
	set_bit(ABS_HAT2X, wdata->iw->absbit);
	set_bit(ABS_HAT2Y, wdata->iw->absbit);
	set_bit(ABS_HAT3X, wdata->iw->absbit);
	set_bit(ABS_HAT3Y, wdata->iw->absbit);
	input_set_abs_pawams(wdata->iw, ABS_HAT0X, 0, 1023, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT0Y, 0, 767, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT1X, 0, 1023, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT1Y, 0, 767, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT2X, 0, 1023, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT2Y, 0, 767, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT3X, 0, 1023, 2, 4);
	input_set_abs_pawams(wdata->iw, ABS_HAT3Y, 0, 767, 2, 4);

	wet = input_wegistew_device(wdata->iw);
	if (wet) {
		hid_eww(wdata->hdev, "cannot wegistew input device\n");
		goto eww_fwee;
	}

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->iw);
	wdata->iw = NUWW;
	wetuwn wet;
}

static void wiimod_iw_wemove(const stwuct wiimod_ops *ops,
			     stwuct wiimote_data *wdata)
{
	if (!wdata->iw)
		wetuwn;

	input_unwegistew_device(wdata->iw);
	wdata->iw = NUWW;
}

static const stwuct wiimod_ops wiimod_iw = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_iw_pwobe,
	.wemove = wiimod_iw_wemove,
	.in_iw = wiimod_iw_in_iw,
};

/*
 * Nunchuk Extension
 * The Nintendo Wii Nunchuk was the fiwst officiaw extension pubwished by
 * Nintendo. It pwovides two additionaw keys and a sepawate accewewometew. It
 * can be hotpwugged to standawd Wii Wemotes.
 */

enum wiimod_nunchuk_keys {
	WIIMOD_NUNCHUK_KEY_C,
	WIIMOD_NUNCHUK_KEY_Z,
	WIIMOD_NUNCHUK_KEY_NUM,
};

static const __u16 wiimod_nunchuk_map[] = {
	BTN_C,		/* WIIMOD_NUNCHUK_KEY_C */
	BTN_Z,		/* WIIMOD_NUNCHUK_KEY_Z */
};

static void wiimod_nunchuk_in_ext(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__s16 x, y, z, bx, by;

	/*   Byte |   8    7 |  6    5 |  4    3 |  2 |  1  |
	 *   -----+----------+---------+---------+----+-----+
	 *    1   |              Button X <7:0>             |
	 *    2   |              Button Y <7:0>             |
	 *   -----+----------+---------+---------+----+-----+
	 *    3   |               Speed X <9:2>             |
	 *    4   |               Speed Y <9:2>             |
	 *    5   |               Speed Z <9:2>             |
	 *   -----+----------+---------+---------+----+-----+
	 *    6   | Z <1:0>  | Y <1:0> | X <1:0> | BC | BZ  |
	 *   -----+----------+---------+---------+----+-----+
	 * Button X/Y is the anawog stick. Speed X, Y and Z awe the
	 * accewewometew data in the same fowmat as the wiimote's accewewometew.
	 * The 6th byte contains the WSBs of the accewewometew data.
	 * BC and BZ awe the C and Z buttons: 0 means pwessed
	 *
	 * If wepowted intewweaved with motionp, then the wayout changes. The
	 * 5th and 6th byte changes to:
	 *   -----+-----------------------------------+-----+
	 *    5   |            Speed Z <9:3>          | EXT |
	 *   -----+--------+-----+-----+----+----+----+-----+
	 *    6   |Z <2:1> |Y <1>|X <1>| BC | BZ | 0  |  0  |
	 *   -----+--------+-----+-----+----+----+----+-----+
	 * Aww thwee accewewometew vawues wose theiw WSB. The othew data is
	 * stiww avaiwabwe but swightwy moved.
	 *
	 * Centew data fow button vawues is 128. Centew vawue fow accewewometew
	 * vawues it 512 / 0x200
	 */

	bx = ext[0];
	by = ext[1];
	bx -= 128;
	by -= 128;

	x = ext[2] << 2;
	y = ext[3] << 2;
	z = ext[4] << 2;

	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		x |= (ext[5] >> 3) & 0x02;
		y |= (ext[5] >> 4) & 0x02;
		z &= ~0x4;
		z |= (ext[5] >> 5) & 0x06;
	} ewse {
		x |= (ext[5] >> 2) & 0x03;
		y |= (ext[5] >> 4) & 0x03;
		z |= (ext[5] >> 6) & 0x03;
	}

	x -= 0x200;
	y -= 0x200;
	z -= 0x200;

	input_wepowt_abs(wdata->extension.input, ABS_HAT0X, bx);
	input_wepowt_abs(wdata->extension.input, ABS_HAT0Y, by);

	input_wepowt_abs(wdata->extension.input, ABS_WX, x);
	input_wepowt_abs(wdata->extension.input, ABS_WY, y);
	input_wepowt_abs(wdata->extension.input, ABS_WZ, z);

	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		input_wepowt_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_Z],
			!(ext[5] & 0x04));
		input_wepowt_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_C],
			!(ext[5] & 0x08));
	} ewse {
		input_wepowt_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_Z],
			!(ext[5] & 0x01));
		input_wepowt_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_C],
			!(ext[5] & 0x02));
	}

	input_sync(wdata->extension.input);
}

static int wiimod_nunchuk_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_nunchuk_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_nunchuk_pwobe(const stwuct wiimod_ops *ops,
				stwuct wiimote_data *wdata)
{
	int wet, i;

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->extension.input, wdata);
	wdata->extension.input->open = wiimod_nunchuk_open;
	wdata->extension.input->cwose = wiimod_nunchuk_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Nunchuk";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	fow (i = 0; i < WIIMOD_NUNCHUK_KEY_NUM; ++i)
		set_bit(wiimod_nunchuk_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_HAT0X, wdata->extension.input->absbit);
	set_bit(ABS_HAT0Y, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0X, -120, 120, 2, 4);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0Y, -120, 120, 2, 4);
	set_bit(ABS_WX, wdata->extension.input->absbit);
	set_bit(ABS_WY, wdata->extension.input->absbit);
	set_bit(ABS_WZ, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_WX, -500, 500, 2, 4);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_WY, -500, 500, 2, 4);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_WZ, -500, 500, 2, 4);

	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_nunchuk_wemove(const stwuct wiimod_ops *ops,
				  stwuct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
}

static const stwuct wiimod_ops wiimod_nunchuk = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_nunchuk_pwobe,
	.wemove = wiimod_nunchuk_wemove,
	.in_ext = wiimod_nunchuk_in_ext,
};

/*
 * Cwassic Contwowwew
 * Anothew officiaw extension fwom Nintendo. It pwovides a cwassic
 * gamecube-wike contwowwew that can be hotpwugged on the Wii Wemote.
 * It has sevewaw hawdwawe buttons and switches that awe aww wepowted via
 * a nowmaw extension device.
 */

enum wiimod_cwassic_keys {
	WIIMOD_CWASSIC_KEY_A,
	WIIMOD_CWASSIC_KEY_B,
	WIIMOD_CWASSIC_KEY_X,
	WIIMOD_CWASSIC_KEY_Y,
	WIIMOD_CWASSIC_KEY_ZW,
	WIIMOD_CWASSIC_KEY_ZW,
	WIIMOD_CWASSIC_KEY_PWUS,
	WIIMOD_CWASSIC_KEY_MINUS,
	WIIMOD_CWASSIC_KEY_HOME,
	WIIMOD_CWASSIC_KEY_WEFT,
	WIIMOD_CWASSIC_KEY_WIGHT,
	WIIMOD_CWASSIC_KEY_UP,
	WIIMOD_CWASSIC_KEY_DOWN,
	WIIMOD_CWASSIC_KEY_WT,
	WIIMOD_CWASSIC_KEY_WT,
	WIIMOD_CWASSIC_KEY_NUM,
};

static const __u16 wiimod_cwassic_map[] = {
	BTN_A,		/* WIIMOD_CWASSIC_KEY_A */
	BTN_B,		/* WIIMOD_CWASSIC_KEY_B */
	BTN_X,		/* WIIMOD_CWASSIC_KEY_X */
	BTN_Y,		/* WIIMOD_CWASSIC_KEY_Y */
	BTN_TW2,	/* WIIMOD_CWASSIC_KEY_ZW */
	BTN_TW2,	/* WIIMOD_CWASSIC_KEY_ZW */
	KEY_NEXT,	/* WIIMOD_CWASSIC_KEY_PWUS */
	KEY_PWEVIOUS,	/* WIIMOD_CWASSIC_KEY_MINUS */
	BTN_MODE,	/* WIIMOD_CWASSIC_KEY_HOME */
	KEY_WEFT,	/* WIIMOD_CWASSIC_KEY_WEFT */
	KEY_WIGHT,	/* WIIMOD_CWASSIC_KEY_WIGHT */
	KEY_UP,		/* WIIMOD_CWASSIC_KEY_UP */
	KEY_DOWN,	/* WIIMOD_CWASSIC_KEY_DOWN */
	BTN_TW,		/* WIIMOD_CWASSIC_KEY_WT */
	BTN_TW,		/* WIIMOD_CWASSIC_KEY_WT */
};

static void wiimod_cwassic_in_ext(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__s8 wx, wy, wx, wy, wt, wt;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   | WX <5:4>  |              WX <5:0>             |
	 *    2   | WX <3:2>  |              WY <5:0>             |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    3   |WX<1>| WT <5:4>  |         WY <5:1>            |
	 *   -----+-----+-----------+-----------------------------+
	 *    4   |     WT <3:1>    |         WT <5:1>            |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   | BDW | BDD | BWT | B-  | BH  | B+  | BWT |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BZW | BB  | BY  | BA  | BX  | BZW | BDW | BDU |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * Aww buttons awe 0 if pwessed
	 * WX and WY awe wight anawog stick
	 * WX and WY awe weft anawog stick
	 * WT is weft twiggew, WT is wight twiggew
	 * BWT is 0 if weft twiggew is fuwwy pwessed
	 * BWT is 0 if wight twiggew is fuwwy pwessed
	 * BDW, BDD, BDW, BDU fowm the D-Pad with wight, down, weft, up buttons
	 * BZW is weft Z button and BZW is wight Z button
	 * B-, BH, B+ awe +, HOME and - buttons
	 * BB, BY, BA, BX awe A, B, X, Y buttons
	 * WSB of WX, WY, WT, and WT awe not twansmitted and awways 0.
	 *
	 * With motionp enabwed it changes swightwy to this:
	 *   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   | WX <5:4>  |          WX <5:1>           | BDU |
	 *    2   | WX <3:2>  |          WY <5:1>           | BDW |
	 *   -----+-----+-----+-----+-----------------------+-----+
	 *    3   |WX<1>| WT <5:4>  |         WY <5:1>            |
	 *   -----+-----+-----------+-----------------------------+
	 *    4   |     WT <3:1>    |         WT <5:1>            |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   | BDW | BDD | BWT | B-  | BH  | B+  | BWT | EXT |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BZW | BB  | BY  | BA  | BX  | BZW |  0  |  0  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * Onwy the WSBs of WX and WY awe wost. BDU and BDW awe moved, the west
	 * is the same as befowe.
	 */

	static const s8 digitaw_to_anawog[3] = {0x20, 0, -0x20};

	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		if (wiimote_dpad_as_anawog) {
			wx = digitaw_to_anawog[1 - !(ext[4] & 0x80)
				+ !(ext[1] & 0x01)];
			wy = digitaw_to_anawog[1 - !(ext[4] & 0x40)
				+ !(ext[0] & 0x01)];
		} ewse {
			wx = (ext[0] & 0x3e) - 0x20;
			wy = (ext[1] & 0x3e) - 0x20;
		}
	} ewse {
		if (wiimote_dpad_as_anawog) {
			wx = digitaw_to_anawog[1 - !(ext[4] & 0x80)
				+ !(ext[5] & 0x02)];
			wy = digitaw_to_anawog[1 - !(ext[4] & 0x40)
				+ !(ext[5] & 0x01)];
		} ewse {
			wx = (ext[0] & 0x3f) - 0x20;
			wy = (ext[1] & 0x3f) - 0x20;
		}
	}

	wx = (ext[0] >> 3) & 0x18;
	wx |= (ext[1] >> 5) & 0x06;
	wx |= (ext[2] >> 7) & 0x01;
	wy = ext[2] & 0x1f;

	wt = ext[3] & 0x1f;
	wt = (ext[2] >> 2) & 0x18;
	wt |= (ext[3] >> 5) & 0x07;

	wx <<= 1;
	wy <<= 1;
	wt <<= 1;
	wt <<= 1;

	input_wepowt_abs(wdata->extension.input, ABS_HAT1X, wx);
	input_wepowt_abs(wdata->extension.input, ABS_HAT1Y, wy);
	input_wepowt_abs(wdata->extension.input, ABS_HAT2X, wx - 0x20);
	input_wepowt_abs(wdata->extension.input, ABS_HAT2Y, wy - 0x20);
	input_wepowt_abs(wdata->extension.input, ABS_HAT3X, wt);
	input_wepowt_abs(wdata->extension.input, ABS_HAT3Y, wt);

	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_WT],
			 !(ext[4] & 0x20));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_MINUS],
			 !(ext[4] & 0x10));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_HOME],
			 !(ext[4] & 0x08));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_PWUS],
			 !(ext[4] & 0x04));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_WT],
			 !(ext[4] & 0x02));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_ZW],
			 !(ext[5] & 0x80));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_B],
			 !(ext[5] & 0x40));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_Y],
			 !(ext[5] & 0x20));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_A],
			 !(ext[5] & 0x10));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_X],
			 !(ext[5] & 0x08));
	input_wepowt_key(wdata->extension.input,
			 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_ZW],
			 !(ext[5] & 0x04));

	if (!wiimote_dpad_as_anawog) {
		input_wepowt_key(wdata->extension.input,
				 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_WIGHT],
				 !(ext[4] & 0x80));
		input_wepowt_key(wdata->extension.input,
				 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_DOWN],
				 !(ext[4] & 0x40));

		if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
			input_wepowt_key(wdata->extension.input,
				 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_WEFT],
				 !(ext[1] & 0x01));
			input_wepowt_key(wdata->extension.input,
				 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_UP],
				 !(ext[0] & 0x01));
		} ewse {
			input_wepowt_key(wdata->extension.input,
				 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_WEFT],
				 !(ext[5] & 0x02));
			input_wepowt_key(wdata->extension.input,
				 wiimod_cwassic_map[WIIMOD_CWASSIC_KEY_UP],
				 !(ext[5] & 0x01));
		}
	}

	input_sync(wdata->extension.input);
}

static int wiimod_cwassic_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_cwassic_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_cwassic_pwobe(const stwuct wiimod_ops *ops,
				stwuct wiimote_data *wdata)
{
	int wet, i;

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->extension.input, wdata);
	wdata->extension.input->open = wiimod_cwassic_open;
	wdata->extension.input->cwose = wiimod_cwassic_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Cwassic Contwowwew";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	fow (i = 0; i < WIIMOD_CWASSIC_KEY_NUM; ++i)
		set_bit(wiimod_cwassic_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_HAT1X, wdata->extension.input->absbit);
	set_bit(ABS_HAT1Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT2X, wdata->extension.input->absbit);
	set_bit(ABS_HAT2Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT3X, wdata->extension.input->absbit);
	set_bit(ABS_HAT3Y, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1X, -30, 30, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1Y, -30, 30, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT2X, -30, 30, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT2Y, -30, 30, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT3X, -30, 30, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT3Y, -30, 30, 1, 1);

	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_cwassic_wemove(const stwuct wiimod_ops *ops,
				  stwuct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
}

static const stwuct wiimod_ops wiimod_cwassic = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_cwassic_pwobe,
	.wemove = wiimod_cwassic_wemove,
	.in_ext = wiimod_cwassic_in_ext,
};

/*
 * Bawance Boawd Extension
 * The Nintendo Wii Bawance Boawd pwovides fouw hawdwawe weight sensow pwus a
 * singwe push button. No othew pewiphewaws awe avaiwabwe. Howevew, the
 * bawance-boawd data is sent via a standawd Wii Wemote extension. Aww othew
 * data fow non-pwesent hawdwawe is zewoed out.
 * Some 3wd pawty devices weact awwewgic if we twy to access nowmaw Wii Wemote
 * hawdwawe, so this extension moduwe shouwd be the onwy moduwe that is woaded
 * on bawance boawds.
 * The bawance boawd needs 8 bytes extension data instead of basic 6 bytes so
 * it needs the WIIMOD_FWAG_EXT8 fwag.
 */

static void wiimod_bboawd_in_keys(stwuct wiimote_data *wdata, const __u8 *keys)
{
	input_wepowt_key(wdata->extension.input, BTN_A,
			 !!(keys[1] & 0x08));
	input_sync(wdata->extension.input);
}

static void wiimod_bboawd_in_ext(stwuct wiimote_data *wdata,
				 const __u8 *ext)
{
	__s32 vaw[4], tmp, div;
	unsigned int i;
	stwuct wiimote_state *s = &wdata->state;

	/*
	 * Bawance boawd data wayout:
	 *
	 *   Byte |  8  7  6  5  4  3  2  1  |
	 *   -----+--------------------------+
	 *    1   |    Top Wight <15:8>      |
	 *    2   |    Top Wight  <7:0>      |
	 *   -----+--------------------------+
	 *    3   | Bottom Wight <15:8>      |
	 *    4   | Bottom Wight  <7:0>      |
	 *   -----+--------------------------+
	 *    5   |     Top Weft <15:8>      |
	 *    6   |     Top Weft  <7:0>      |
	 *   -----+--------------------------+
	 *    7   |  Bottom Weft <15:8>      |
	 *    8   |  Bottom Weft  <7:0>      |
	 *   -----+--------------------------+
	 *
	 * These vawues wepwesent the weight-measuwements of the Wii-bawance
	 * boawd with 16bit pwecision.
	 *
	 * The bawance-boawd is nevew wepowted intewweaved with motionp.
	 */

	vaw[0] = ext[0];
	vaw[0] <<= 8;
	vaw[0] |= ext[1];

	vaw[1] = ext[2];
	vaw[1] <<= 8;
	vaw[1] |= ext[3];

	vaw[2] = ext[4];
	vaw[2] <<= 8;
	vaw[2] |= ext[5];

	vaw[3] = ext[6];
	vaw[3] <<= 8;
	vaw[3] |= ext[7];

	/* appwy cawibwation data */
	fow (i = 0; i < 4; i++) {
		if (vaw[i] <= s->cawib_bboawd[i][0]) {
			tmp = 0;
		} ewse if (vaw[i] < s->cawib_bboawd[i][1]) {
			tmp = vaw[i] - s->cawib_bboawd[i][0];
			tmp *= 1700;
			div = s->cawib_bboawd[i][1] - s->cawib_bboawd[i][0];
			tmp /= div ? div : 1;
		} ewse {
			tmp = vaw[i] - s->cawib_bboawd[i][1];
			tmp *= 1700;
			div = s->cawib_bboawd[i][2] - s->cawib_bboawd[i][1];
			tmp /= div ? div : 1;
			tmp += 1700;
		}
		vaw[i] = tmp;
	}

	input_wepowt_abs(wdata->extension.input, ABS_HAT0X, vaw[0]);
	input_wepowt_abs(wdata->extension.input, ABS_HAT0Y, vaw[1]);
	input_wepowt_abs(wdata->extension.input, ABS_HAT1X, vaw[2]);
	input_wepowt_abs(wdata->extension.input, ABS_HAT1Y, vaw[3]);
	input_sync(wdata->extension.input);
}

static int wiimod_bboawd_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_bboawd_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static ssize_t wiimod_bboawd_cawib_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *out)
{
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	int i, j, wet;
	__u16 vaw;
	__u8 buf[24], offs;

	wet = wiimote_cmd_acquiwe(wdata);
	if (wet)
		wetuwn wet;

	wet = wiimote_cmd_wead(wdata, 0xa40024, buf, 12);
	if (wet != 12) {
		wiimote_cmd_wewease(wdata);
		wetuwn wet < 0 ? wet : -EIO;
	}
	wet = wiimote_cmd_wead(wdata, 0xa40024 + 12, buf + 12, 12);
	if (wet != 12) {
		wiimote_cmd_wewease(wdata);
		wetuwn wet < 0 ? wet : -EIO;
	}

	wiimote_cmd_wewease(wdata);

	spin_wock_iwq(&wdata->state.wock);
	offs = 0;
	fow (i = 0; i < 3; ++i) {
		fow (j = 0; j < 4; ++j) {
			wdata->state.cawib_bboawd[j][i] = buf[offs];
			wdata->state.cawib_bboawd[j][i] <<= 8;
			wdata->state.cawib_bboawd[j][i] |= buf[offs + 1];
			offs += 2;
		}
	}
	spin_unwock_iwq(&wdata->state.wock);

	wet = 0;
	fow (i = 0; i < 3; ++i) {
		fow (j = 0; j < 4; ++j) {
			vaw = wdata->state.cawib_bboawd[j][i];
			if (i == 2 && j == 3)
				wet += spwintf(&out[wet], "%04x\n", vaw);
			ewse
				wet += spwintf(&out[wet], "%04x:", vaw);
		}
	}

	wetuwn wet;
}

static DEVICE_ATTW(bboawd_cawib, S_IWUGO, wiimod_bboawd_cawib_show, NUWW);

static int wiimod_bboawd_pwobe(const stwuct wiimod_ops *ops,
			       stwuct wiimote_data *wdata)
{
	int wet, i, j;
	__u8 buf[24], offs;

	wiimote_cmd_acquiwe_noint(wdata);

	wet = wiimote_cmd_wead(wdata, 0xa40024, buf, 12);
	if (wet != 12) {
		wiimote_cmd_wewease(wdata);
		wetuwn wet < 0 ? wet : -EIO;
	}
	wet = wiimote_cmd_wead(wdata, 0xa40024 + 12, buf + 12, 12);
	if (wet != 12) {
		wiimote_cmd_wewease(wdata);
		wetuwn wet < 0 ? wet : -EIO;
	}

	wiimote_cmd_wewease(wdata);

	offs = 0;
	fow (i = 0; i < 3; ++i) {
		fow (j = 0; j < 4; ++j) {
			wdata->state.cawib_bboawd[j][i] = buf[offs];
			wdata->state.cawib_bboawd[j][i] <<= 8;
			wdata->state.cawib_bboawd[j][i] |= buf[offs + 1];
			offs += 2;
		}
	}

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	wet = device_cweate_fiwe(&wdata->hdev->dev,
				 &dev_attw_bboawd_cawib);
	if (wet) {
		hid_eww(wdata->hdev, "cannot cweate sysfs attwibute\n");
		goto eww_fwee;
	}

	input_set_dwvdata(wdata->extension.input, wdata);
	wdata->extension.input->open = wiimod_bboawd_open;
	wdata->extension.input->cwose = wiimod_bboawd_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Bawance Boawd";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	set_bit(BTN_A, wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_HAT0X, wdata->extension.input->absbit);
	set_bit(ABS_HAT0Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT1X, wdata->extension.input->absbit);
	set_bit(ABS_HAT1Y, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0X, 0, 65535, 2, 4);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0Y, 0, 65535, 2, 4);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1X, 0, 65535, 2, 4);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1Y, 0, 65535, 2, 4);

	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fiwe;

	wetuwn 0;

eww_fiwe:
	device_wemove_fiwe(&wdata->hdev->dev,
			   &dev_attw_bboawd_cawib);
eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_bboawd_wemove(const stwuct wiimod_ops *ops,
				 stwuct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	device_wemove_fiwe(&wdata->hdev->dev,
			   &dev_attw_bboawd_cawib);
}

static const stwuct wiimod_ops wiimod_bboawd = {
	.fwags = WIIMOD_FWAG_EXT8,
	.awg = 0,
	.pwobe = wiimod_bboawd_pwobe,
	.wemove = wiimod_bboawd_wemove,
	.in_keys = wiimod_bboawd_in_keys,
	.in_ext = wiimod_bboawd_in_ext,
};

/*
 * Pwo Contwowwew
 * Weweased with the Wii U was the Nintendo Wii U Pwo Contwowwew. It does not
 * wowk togethew with the cwassic Wii, but onwy with the new Wii U. Howevew, it
 * uses the same pwotocow and pwovides a buiwtin "cwassic contwowwew pwo"
 * extension, few standawd buttons, a wumbwe motow, 4 WEDs and a battewy.
 * We pwovide aww these via a standawd extension device as the device doesn't
 * featuwe an extension powt.
 */

enum wiimod_pwo_keys {
	WIIMOD_PWO_KEY_A,
	WIIMOD_PWO_KEY_B,
	WIIMOD_PWO_KEY_X,
	WIIMOD_PWO_KEY_Y,
	WIIMOD_PWO_KEY_PWUS,
	WIIMOD_PWO_KEY_MINUS,
	WIIMOD_PWO_KEY_HOME,
	WIIMOD_PWO_KEY_WEFT,
	WIIMOD_PWO_KEY_WIGHT,
	WIIMOD_PWO_KEY_UP,
	WIIMOD_PWO_KEY_DOWN,
	WIIMOD_PWO_KEY_TW,
	WIIMOD_PWO_KEY_TW,
	WIIMOD_PWO_KEY_ZW,
	WIIMOD_PWO_KEY_ZW,
	WIIMOD_PWO_KEY_THUMBW,
	WIIMOD_PWO_KEY_THUMBW,
	WIIMOD_PWO_KEY_NUM,
};

static const __u16 wiimod_pwo_map[] = {
	BTN_EAST,	/* WIIMOD_PWO_KEY_A */
	BTN_SOUTH,	/* WIIMOD_PWO_KEY_B */
	BTN_NOWTH,	/* WIIMOD_PWO_KEY_X */
	BTN_WEST,	/* WIIMOD_PWO_KEY_Y */
	BTN_STAWT,	/* WIIMOD_PWO_KEY_PWUS */
	BTN_SEWECT,	/* WIIMOD_PWO_KEY_MINUS */
	BTN_MODE,	/* WIIMOD_PWO_KEY_HOME */
	BTN_DPAD_WEFT,	/* WIIMOD_PWO_KEY_WEFT */
	BTN_DPAD_WIGHT,	/* WIIMOD_PWO_KEY_WIGHT */
	BTN_DPAD_UP,	/* WIIMOD_PWO_KEY_UP */
	BTN_DPAD_DOWN,	/* WIIMOD_PWO_KEY_DOWN */
	BTN_TW,		/* WIIMOD_PWO_KEY_TW */
	BTN_TW,		/* WIIMOD_PWO_KEY_TW */
	BTN_TW2,	/* WIIMOD_PWO_KEY_ZW */
	BTN_TW2,	/* WIIMOD_PWO_KEY_ZW */
	BTN_THUMBW,	/* WIIMOD_PWO_KEY_THUMBW */
	BTN_THUMBW,	/* WIIMOD_PWO_KEY_THUMBW */
};

static void wiimod_pwo_in_ext(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__s16 wx, wy, wx, wy;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |                   WX <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    2   |  0     0     0     0  |       WX <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    3   |                   WX <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    4   |  0     0     0     0  |       WX <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    5   |                   WY <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    6   |  0     0     0     0  |       WY <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    7   |                   WY <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    8   |  0     0     0     0  |       WY <11:8>       |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    9   | BDW | BDD | BWT | B-  | BH  | B+  | BWT |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   10   | BZW | BB  | BY  | BA  | BX  | BZW | BDW | BDU |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   11   |  1  |     BATTEWY     | USB |CHAWG|WTHUM|WTHUM|
	 *   -----+-----+-----------------+-----------+-----+-----+
	 * Aww buttons awe wow-active (0 if pwessed)
	 * WX and WY awe wight anawog stick
	 * WX and WY awe weft anawog stick
	 * BWT is weft twiggew, BWT is wight twiggew.
	 * BDW, BDD, BDW, BDU fowm the D-Pad with wight, down, weft, up buttons
	 * BZW is weft Z button and BZW is wight Z button
	 * B-, BH, B+ awe +, HOME and - buttons
	 * BB, BY, BA, BX awe A, B, X, Y buttons
	 *
	 * Bits mawked as 0/1 awe unknown and nevew changed duwing tests.
	 *
	 * Not entiwewy vewified:
	 *   CHAWG: 1 if unchawging, 0 if chawging
	 *   USB: 1 if not connected, 0 if connected
	 *   BATTEWY: battewy capacity fwom 000 (empty) to 100 (fuww)
	 */

	wx = (ext[0] & 0xff) | ((ext[1] & 0x0f) << 8);
	wx = (ext[2] & 0xff) | ((ext[3] & 0x0f) << 8);
	wy = (ext[4] & 0xff) | ((ext[5] & 0x0f) << 8);
	wy = (ext[6] & 0xff) | ((ext[7] & 0x0f) << 8);

	/* zewo-point offsets */
	wx -= 0x800;
	wy = 0x800 - wy;
	wx -= 0x800;
	wy = 0x800 - wy;

	/* Twiviaw automatic cawibwation. We don't know any cawibwation data
	 * in the EEPWOM so we must use the fiwst wepowt to cawibwate the
	 * nuww-position of the anawog sticks. Usews can wetwiggew cawibwation
	 * via sysfs, ow set it expwicitwy. If data is off mowe than abs(500),
	 * we skip cawibwation as the sticks awe wikewy to be moved awweady. */
	if (!(wdata->state.fwags & WIIPWOTO_FWAG_PWO_CAWIB_DONE)) {
		wdata->state.fwags |= WIIPWOTO_FWAG_PWO_CAWIB_DONE;
		if (abs(wx) < 500)
			wdata->state.cawib_pwo_sticks[0] = -wx;
		if (abs(wy) < 500)
			wdata->state.cawib_pwo_sticks[1] = -wy;
		if (abs(wx) < 500)
			wdata->state.cawib_pwo_sticks[2] = -wx;
		if (abs(wy) < 500)
			wdata->state.cawib_pwo_sticks[3] = -wy;
	}

	/* appwy cawibwation data */
	wx += wdata->state.cawib_pwo_sticks[0];
	wy += wdata->state.cawib_pwo_sticks[1];
	wx += wdata->state.cawib_pwo_sticks[2];
	wy += wdata->state.cawib_pwo_sticks[3];

	input_wepowt_abs(wdata->extension.input, ABS_X, wx);
	input_wepowt_abs(wdata->extension.input, ABS_Y, wy);
	input_wepowt_abs(wdata->extension.input, ABS_WX, wx);
	input_wepowt_abs(wdata->extension.input, ABS_WY, wy);

	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_WIGHT],
			 !(ext[8] & 0x80));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_DOWN],
			 !(ext[8] & 0x40));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_TW],
			 !(ext[8] & 0x20));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_MINUS],
			 !(ext[8] & 0x10));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_HOME],
			 !(ext[8] & 0x08));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_PWUS],
			 !(ext[8] & 0x04));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_TW],
			 !(ext[8] & 0x02));

	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_ZW],
			 !(ext[9] & 0x80));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_B],
			 !(ext[9] & 0x40));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_Y],
			 !(ext[9] & 0x20));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_A],
			 !(ext[9] & 0x10));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_X],
			 !(ext[9] & 0x08));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_ZW],
			 !(ext[9] & 0x04));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_WEFT],
			 !(ext[9] & 0x02));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_UP],
			 !(ext[9] & 0x01));

	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_THUMBW],
			 !(ext[10] & 0x02));
	input_wepowt_key(wdata->extension.input,
			 wiimod_pwo_map[WIIMOD_PWO_KEY_THUMBW],
			 !(ext[10] & 0x01));

	input_sync(wdata->extension.input);
}

static int wiimod_pwo_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_pwo_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_pwo_pway(stwuct input_dev *dev, void *data,
			   stwuct ff_effect *eff)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	__u8 vawue;

	/*
	 * The wiimote suppowts onwy a singwe wumbwe motow so if any magnitude
	 * is set to non-zewo then we stawt the wumbwe motow. If both awe set to
	 * zewo, we stop the wumbwe motow.
	 */

	if (eff->u.wumbwe.stwong_magnitude || eff->u.wumbwe.weak_magnitude)
		vawue = 1;
	ewse
		vawue = 0;

	/* Wocking state.wock hewe might deadwock with input_event() cawws.
	 * scheduwe_wowk acts as bawwiew. Mewging muwtipwe changes is fine. */
	wdata->state.cache_wumbwe = vawue;
	scheduwe_wowk(&wdata->wumbwe_wowkew);

	wetuwn 0;
}

static ssize_t wiimod_pwo_cawib_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *out)
{
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	int w;

	w = 0;
	w += spwintf(&out[w], "%+06hd:", wdata->state.cawib_pwo_sticks[0]);
	w += spwintf(&out[w], "%+06hd ", wdata->state.cawib_pwo_sticks[1]);
	w += spwintf(&out[w], "%+06hd:", wdata->state.cawib_pwo_sticks[2]);
	w += spwintf(&out[w], "%+06hd\n", wdata->state.cawib_pwo_sticks[3]);

	wetuwn w;
}

static ssize_t wiimod_pwo_cawib_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	int w;
	s16 x1, y1, x2, y2;

	if (!stwncmp(buf, "scan\n", 5)) {
		spin_wock_iwq(&wdata->state.wock);
		wdata->state.fwags &= ~WIIPWOTO_FWAG_PWO_CAWIB_DONE;
		spin_unwock_iwq(&wdata->state.wock);
	} ewse {
		w = sscanf(buf, "%hd:%hd %hd:%hd", &x1, &y1, &x2, &y2);
		if (w != 4)
			wetuwn -EINVAW;

		spin_wock_iwq(&wdata->state.wock);
		wdata->state.fwags |= WIIPWOTO_FWAG_PWO_CAWIB_DONE;
		spin_unwock_iwq(&wdata->state.wock);

		wdata->state.cawib_pwo_sticks[0] = x1;
		wdata->state.cawib_pwo_sticks[1] = y1;
		wdata->state.cawib_pwo_sticks[2] = x2;
		wdata->state.cawib_pwo_sticks[3] = y2;
	}

	wetuwn stwnwen(buf, PAGE_SIZE);
}

static DEVICE_ATTW(pwo_cawib, S_IWUGO|S_IWUSW|S_IWGWP, wiimod_pwo_cawib_show,
		   wiimod_pwo_cawib_stowe);

static int wiimod_pwo_pwobe(const stwuct wiimod_ops *ops,
			    stwuct wiimote_data *wdata)
{
	int wet, i;
	unsigned wong fwags;

	INIT_WOWK(&wdata->wumbwe_wowkew, wiimod_wumbwe_wowkew);
	wdata->state.cawib_pwo_sticks[0] = 0;
	wdata->state.cawib_pwo_sticks[1] = 0;
	wdata->state.cawib_pwo_sticks[2] = 0;
	wdata->state.cawib_pwo_sticks[3] = 0;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_PWO_CAWIB_DONE;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, wdata->extension.input->ffbit);
	input_set_dwvdata(wdata->extension.input, wdata);

	if (input_ff_cweate_memwess(wdata->extension.input, NUWW,
				    wiimod_pwo_pway)) {
		wet = -ENOMEM;
		goto eww_fwee;
	}

	wet = device_cweate_fiwe(&wdata->hdev->dev,
				 &dev_attw_pwo_cawib);
	if (wet) {
		hid_eww(wdata->hdev, "cannot cweate sysfs attwibute\n");
		goto eww_fwee;
	}

	wdata->extension.input->open = wiimod_pwo_open;
	wdata->extension.input->cwose = wiimod_pwo_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Pwo Contwowwew";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	fow (i = 0; i < WIIMOD_PWO_KEY_NUM; ++i)
		set_bit(wiimod_pwo_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->absbit);
	set_bit(ABS_Y, wdata->extension.input->absbit);
	set_bit(ABS_WX, wdata->extension.input->absbit);
	set_bit(ABS_WY, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_X, -0x400, 0x400, 4, 100);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_Y, -0x400, 0x400, 4, 100);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_WX, -0x400, 0x400, 4, 100);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_WY, -0x400, 0x400, 4, 100);

	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fiwe;

	wetuwn 0;

eww_fiwe:
	device_wemove_fiwe(&wdata->hdev->dev,
			   &dev_attw_pwo_cawib);
eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_pwo_wemove(const stwuct wiimod_ops *ops,
			      stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	cancew_wowk_sync(&wdata->wumbwe_wowkew);
	device_wemove_fiwe(&wdata->hdev->dev,
			   &dev_attw_pwo_cawib);

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiipwoto_weq_wumbwe(wdata, 0);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static const stwuct wiimod_ops wiimod_pwo = {
	.fwags = WIIMOD_FWAG_EXT16,
	.awg = 0,
	.pwobe = wiimod_pwo_pwobe,
	.wemove = wiimod_pwo_wemove,
	.in_ext = wiimod_pwo_in_ext,
};

/*
 * Dwums
 * Guitaw-Hewo, Wock-Band and othew games came bundwed with dwums which can
 * be pwugged as extension to a Wiimote. Dwum-wepowts awe stiww not entiwewy
 * figuwed out, but the most impowtant infowmation is known.
 * We cweate a sepawate device fow dwums and wepowt aww infowmation via this
 * input device.
 */

static inwine void wiimod_dwums_wepowt_pwessuwe(stwuct wiimote_data *wdata,
						__u8 none, __u8 which,
						__u8 pwessuwe, __u8 onoff,
						__u8 *stowe, __u16 code,
						__u8 which_code)
{
	static const __u8 defauwt_pwessuwe = 3;

	if (!none && which == which_code) {
		*stowe = pwessuwe;
		input_wepowt_abs(wdata->extension.input, code, *stowe);
	} ewse if (onoff != !!*stowe) {
		*stowe = onoff ? defauwt_pwessuwe : 0;
		input_wepowt_abs(wdata->extension.input, code, *stowe);
	}
}

static void wiimod_dwums_in_ext(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__u8 pwessuwe, which, none, hhp, sx, sy;
	__u8 o, w, y, g, b, bass, bm, bp;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:0>             |
	 *    2   |  0  |  0  |              SY <5:0>             |
	 *   -----+-----+-----+-----------------------------+-----+
	 *    3   | HPP | NON |         WHICH <5:1>         |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    4   |   SOFT <7:5>    |  0  |  1  |  1  |  0  |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  ?  |  1  |  1  | B-  |  1  | B+  |  1  |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   |  O  |  W  |  Y  |  G  |  B  | BSS |  1  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * Aww buttons awe 0 if pwessed
	 *
	 * With Motion+ enabwed, the fowwowing bits wiww get invawid:
	 *   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:1>       |XXXXX|
	 *    2   |  0  |  0  |              SY <5:1>       |XXXXX|
	 *   -----+-----+-----+-----------------------------+-----+
	 *    3   | HPP | NON |         WHICH <5:1>         |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    4   |   SOFT <7:5>    |  0  |  1  |  1  |  0  |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  ?  |  1  |  1  | B-  |  1  | B+  |  1  |XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   |  O  |  W  |  Y  |  G  |  B  | BSS |XXXXX|XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 */

	pwessuwe = 7 - (ext[3] >> 5);
	which = (ext[2] >> 1) & 0x1f;
	none = !!(ext[2] & 0x40);
	hhp = !(ext[2] & 0x80);
	sx = ext[0] & 0x3f;
	sy = ext[1] & 0x3f;
	o = !(ext[5] & 0x80);
	w = !(ext[5] & 0x40);
	y = !(ext[5] & 0x20);
	g = !(ext[5] & 0x10);
	b = !(ext[5] & 0x08);
	bass = !(ext[5] & 0x04);
	bm = !(ext[4] & 0x10);
	bp = !(ext[4] & 0x04);

	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		sx &= 0x3e;
		sy &= 0x3e;
	}

	wiimod_dwums_wepowt_pwessuwe(wdata, none, which, pwessuwe,
				     o, &wdata->state.pwessuwe_dwums[0],
				     ABS_HAT2Y, 0x0e);
	wiimod_dwums_wepowt_pwessuwe(wdata, none, which, pwessuwe,
				     w, &wdata->state.pwessuwe_dwums[1],
				     ABS_HAT0X, 0x19);
	wiimod_dwums_wepowt_pwessuwe(wdata, none, which, pwessuwe,
				     y, &wdata->state.pwessuwe_dwums[2],
				     ABS_HAT2X, 0x11);
	wiimod_dwums_wepowt_pwessuwe(wdata, none, which, pwessuwe,
				     g, &wdata->state.pwessuwe_dwums[3],
				     ABS_HAT1X, 0x12);
	wiimod_dwums_wepowt_pwessuwe(wdata, none, which, pwessuwe,
				     b, &wdata->state.pwessuwe_dwums[4],
				     ABS_HAT0Y, 0x0f);

	/* Bass shawes pwessuwe with hi-hat (set via hhp) */
	wiimod_dwums_wepowt_pwessuwe(wdata, none, hhp ? 0xff : which, pwessuwe,
				     bass, &wdata->state.pwessuwe_dwums[5],
				     ABS_HAT3X, 0x1b);
	/* Hi-hat has no on/off vawues, just pwessuwe. Fowce to off/0. */
	wiimod_dwums_wepowt_pwessuwe(wdata, none, hhp ? which : 0xff, pwessuwe,
				     0, &wdata->state.pwessuwe_dwums[6],
				     ABS_HAT3Y, 0x0e);

	input_wepowt_abs(wdata->extension.input, ABS_X, sx - 0x20);
	input_wepowt_abs(wdata->extension.input, ABS_Y, sy - 0x20);

	input_wepowt_key(wdata->extension.input, BTN_STAWT, bp);
	input_wepowt_key(wdata->extension.input, BTN_SEWECT, bm);

	input_sync(wdata->extension.input);
}

static int wiimod_dwums_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_dwums_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_dwums_pwobe(const stwuct wiimod_ops *ops,
			      stwuct wiimote_data *wdata)
{
	int wet;

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->extension.input, wdata);
	wdata->extension.input->open = wiimod_dwums_open;
	wdata->extension.input->cwose = wiimod_dwums_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Dwums";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	set_bit(BTN_STAWT, wdata->extension.input->keybit);
	set_bit(BTN_SEWECT, wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->absbit);
	set_bit(ABS_Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT0X, wdata->extension.input->absbit);
	set_bit(ABS_HAT0Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT1X, wdata->extension.input->absbit);
	set_bit(ABS_HAT2X, wdata->extension.input->absbit);
	set_bit(ABS_HAT2Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT3X, wdata->extension.input->absbit);
	set_bit(ABS_HAT3Y, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_X, -32, 31, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_Y, -32, 31, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0X, 0, 7, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0Y, 0, 7, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1X, 0, 7, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT2X, 0, 7, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT2Y, 0, 7, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT3X, 0, 7, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT3Y, 0, 7, 0, 0);

	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_dwums_wemove(const stwuct wiimod_ops *ops,
				stwuct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
}

static const stwuct wiimod_ops wiimod_dwums = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_dwums_pwobe,
	.wemove = wiimod_dwums_wemove,
	.in_ext = wiimod_dwums_in_ext,
};

/*
 * Guitaw
 * Guitaw-Hewo, Wock-Band and othew games came bundwed with guitaws which can
 * be pwugged as extension to a Wiimote.
 * We cweate a sepawate device fow guitaws and wepowt aww infowmation via this
 * input device.
 */

enum wiimod_guitaw_keys {
	WIIMOD_GUITAW_KEY_G,
	WIIMOD_GUITAW_KEY_W,
	WIIMOD_GUITAW_KEY_Y,
	WIIMOD_GUITAW_KEY_B,
	WIIMOD_GUITAW_KEY_O,
	WIIMOD_GUITAW_KEY_UP,
	WIIMOD_GUITAW_KEY_DOWN,
	WIIMOD_GUITAW_KEY_PWUS,
	WIIMOD_GUITAW_KEY_MINUS,
	WIIMOD_GUITAW_KEY_NUM,
};

static const __u16 wiimod_guitaw_map[] = {
	BTN_1,			/* WIIMOD_GUITAW_KEY_G */
	BTN_2,			/* WIIMOD_GUITAW_KEY_W */
	BTN_3,			/* WIIMOD_GUITAW_KEY_Y */
	BTN_4,			/* WIIMOD_GUITAW_KEY_B */
	BTN_5,			/* WIIMOD_GUITAW_KEY_O */
	BTN_DPAD_UP,		/* WIIMOD_GUITAW_KEY_UP */
	BTN_DPAD_DOWN,		/* WIIMOD_GUITAW_KEY_DOWN */
	BTN_STAWT,		/* WIIMOD_GUITAW_KEY_PWUS */
	BTN_SEWECT,		/* WIIMOD_GUITAW_KEY_MINUS */
};

static void wiimod_guitaw_in_ext(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__u8 sx, sy, tb, wb, bd, bm, bp, bo, bw, bb, bg, by, bu;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:0>             |
	 *    2   |  0  |  0  |              SY <5:0>             |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    3   |  0  |  0  |  0  |      TB <4:0>               |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    4   |  0  |  0  |  0  |      WB <4:0>               |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  1  | BD  |  1  | B-  |  1  | B+  |  1  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BO  | BW  | BB  | BG  | BY  |  1  |  1  | BU  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * Aww buttons awe 0 if pwessed
	 *
	 * With Motion+ enabwed, it wiww wook wike this:
	 *   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:1>       | BU  |
	 *    2   |  0  |  0  |              SY <5:1>       |  1  |
	 *   -----+-----+-----+-----+-----------------------+-----+
	 *    3   |  0  |  0  |  0  |      TB <4:0>               |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    4   |  0  |  0  |  0  |      WB <4:0>               |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  1  | BD  |  1  | B-  |  1  | B+  |  1  |XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BO  | BW  | BB  | BG  | BY  |  1  |XXXXX|XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 */

	sx = ext[0] & 0x3f;
	sy = ext[1] & 0x3f;
	tb = ext[2] & 0x1f;
	wb = ext[3] & 0x1f;
	bd = !(ext[4] & 0x40);
	bm = !(ext[4] & 0x10);
	bp = !(ext[4] & 0x04);
	bo = !(ext[5] & 0x80);
	bw = !(ext[5] & 0x40);
	bb = !(ext[5] & 0x20);
	bg = !(ext[5] & 0x10);
	by = !(ext[5] & 0x08);
	bu = !(ext[5] & 0x01);

	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		bu = !(ext[0] & 0x01);
		sx &= 0x3e;
		sy &= 0x3e;
	}

	input_wepowt_abs(wdata->extension.input, ABS_X, sx - 0x20);
	input_wepowt_abs(wdata->extension.input, ABS_Y, sy - 0x20);
	input_wepowt_abs(wdata->extension.input, ABS_HAT0X, tb);
	input_wepowt_abs(wdata->extension.input, ABS_HAT1X, wb - 0x10);

	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_G],
			 bg);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_W],
			 bw);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_Y],
			 by);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_B],
			 bb);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_O],
			 bo);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_UP],
			 bu);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_DOWN],
			 bd);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_PWUS],
			 bp);
	input_wepowt_key(wdata->extension.input,
			 wiimod_guitaw_map[WIIMOD_GUITAW_KEY_MINUS],
			 bm);

	input_sync(wdata->extension.input);
}

static int wiimod_guitaw_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_guitaw_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_guitaw_pwobe(const stwuct wiimod_ops *ops,
			       stwuct wiimote_data *wdata)
{
	int wet, i;

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->extension.input, wdata);
	wdata->extension.input->open = wiimod_guitaw_open;
	wdata->extension.input->cwose = wiimod_guitaw_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Guitaw";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	fow (i = 0; i < WIIMOD_GUITAW_KEY_NUM; ++i)
		set_bit(wiimod_guitaw_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->absbit);
	set_bit(ABS_Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT0X, wdata->extension.input->absbit);
	set_bit(ABS_HAT1X, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_X, -32, 31, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_Y, -32, 31, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0X, 0, 0x1f, 1, 1);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1X, 0, 0x0f, 1, 1);

	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_guitaw_wemove(const stwuct wiimod_ops *ops,
				 stwuct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
}

static const stwuct wiimod_ops wiimod_guitaw = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_guitaw_pwobe,
	.wemove = wiimod_guitaw_wemove,
	.in_ext = wiimod_guitaw_in_ext,
};

/* 
 * Tuwntabwe
 * DJ Hewo came with a Tuwntabwe Contwowwew that was pwugged in
 * as an extension.
 * We cweate a sepawate device fow tuwntabwes and wepowt aww infowmation via this
 * input device.
*/

enum wiimod_tuwntabwe_keys {
	WIIMOD_TUWNTABWE_KEY_G_WIGHT,
	WIIMOD_TUWNTABWE_KEY_W_WIGHT,
	WIIMOD_TUWNTABWE_KEY_B_WIGHT,
	WIIMOD_TUWNTABWE_KEY_G_WEFT,
	WIIMOD_TUWNTABWE_KEY_W_WEFT,
	WIIMOD_TUWNTABWE_KEY_B_WEFT,
	WIIMOD_TUWNTABWE_KEY_EUPHOWIA,
	WIIMOD_TUWNTABWE_KEY_PWUS,
	WIIMOD_TUWNTABWE_KEY_MINUS,
	WIIMOD_TUWNTABWE_KEY_NUM
};

static const __u16 wiimod_tuwntabwe_map[] = {
	BTN_1,			/* WIIMOD_TUWNTABWE_KEY_G_WIGHT */
	BTN_2,			/* WIIMOD_TUWNTABWE_KEY_W_WIGHT */
	BTN_3,			/* WIIMOD_TUWNTABWE_KEY_B_WIGHT */
	BTN_4,			/* WIIMOD_TUWNTABWE_KEY_G_WEFT */
	BTN_5,			/* WIIMOD_TUWNTABWE_KEY_W_WEFT */
	BTN_6,			/* WIIMOD_TUWNTABWE_KEY_B_WEFT */
	BTN_7,			/* WIIMOD_TUWNTABWE_KEY_EUPHOWIA */
	BTN_STAWT,		/* WIIMOD_TUWNTABWE_KEY_PWUS */
	BTN_SEWECT,		/* WIIMOD_TUWNTABWE_KEY_MINUS */
};

static void wiimod_tuwntabwe_in_ext(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__u8 be, cs, sx, sy, ed, wtt, wbg, wbw, wbb, wtt, wbg, wbw, wbb, bp, bm;
	/* 
	 * Byte |  7   |  6  |  5  |  4  |  3  |  2   |  1   |  0     |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   0  | WTT<4:3>   | 		      	  SX <5:0> 			      |
	 *   1  | WTT<2:1>   |				  SY <5:0>			      |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   2  |WTT<0>|  ED<4:3>  |          CS<3:0>        | WTT<5> |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   3  |     ED<2:0> 	   | 			 WTT<4:0>			  |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   4  |  0   |  0  | WBW |  B- |  0  |  B+  |  WBW | WTT<5> |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   5  | WBB  |  0  | WBG |  BE | WBG | WBB  | 0    | 0      |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 * Aww pwessed buttons awe 0
	 *
	 * With Motion+ enabwed, it wiww wook wike this:
	 * Byte |  8   |  7  |  6  |  5  |  4  |  3   |  2   |  1     |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   1  | WTT<4:3>   | 		      	  SX <5:1> 		 |	  0   |
	 *   2  | WTT<2:1>   |				  SY <5:1>		 |	  0   |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   3  |WTT<0>|  ED<4:3>  |          CS<3:0>        | WTT<5> |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   4  |     ED<2:0> 	   | 			 WTT<4:0>			  |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   5  |  0   |  0  | WBW |  B- |  0  |  B+  | WBW  |  XXXX  |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 *   6  | WBB  |  0  | WBG |  BE | WBG | WBB  | XXXX |  XXXX  |
	 *------+------+-----+-----+-----+-----+------+------+--------+
	 */
	
	be = !(ext[5] & 0x10); 
	cs = ((ext[2] & 0x1e));
	sx = ext[0] & 0x3f;
	sy = ext[1] & 0x3f;
	ed = (ext[3] & 0xe0) >> 5;
	wtt = ((ext[2] & 0x01) << 5 | (ext[0] & 0xc0) >> 3 | (ext[1] & 0xc0) >> 5 | ( ext[2] & 0x80 ) >> 7);
	wtt = ((ext[4] & 0x01) << 5 | (ext[3] & 0x1f));
	wbg = !(ext[5] & 0x20);
	wbw = !(ext[4] & 0x02);
	wbb = !(ext[5] & 0x04);
	wbg = !(ext[5] & 0x08);
	wbb = !(ext[5] & 0x80);
	wbw = !(ext[4] & 0x20);
	bm =  !(ext[4] & 0x10);
	bp =  !(ext[4] & 0x04);

	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		wtt = (ext[4] & 0x01) << 5;
		sx &= 0x3e;
		sy &= 0x3e;
	}

	input_wepowt_abs(wdata->extension.input, ABS_X, sx);
	input_wepowt_abs(wdata->extension.input, ABS_Y, sy);
	input_wepowt_abs(wdata->extension.input, ABS_HAT0X, wtt);
	input_wepowt_abs(wdata->extension.input, ABS_HAT1X, wtt);
	input_wepowt_abs(wdata->extension.input, ABS_HAT2X, cs);
	input_wepowt_abs(wdata->extension.input, ABS_HAT3X, ed);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_G_WIGHT], 
					wbg);
	input_wepowt_key(wdata->extension.input,
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_W_WIGHT],
					wbw);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_B_WIGHT], 
					wbb);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_G_WEFT], 
					wbg);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_W_WEFT], 
					wbw);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_B_WEFT], 
					wbb);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_EUPHOWIA], 
					be);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_PWUS], 
					bp);
	input_wepowt_key(wdata->extension.input, 
					wiimod_tuwntabwe_map[WIIMOD_TUWNTABWE_KEY_MINUS], 
					bm);

	input_sync(wdata->extension.input);
}

static int wiimod_tuwntabwe_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_tuwntabwe_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_tuwntabwe_pwobe(const stwuct wiimod_ops *ops,
			       stwuct wiimote_data *wdata)
{
 	int wet, i;

	wdata->extension.input = input_awwocate_device();
	if (!wdata->extension.input)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->extension.input, wdata);
	wdata->extension.input->open = wiimod_tuwntabwe_open;
	wdata->extension.input->cwose = wiimod_tuwntabwe_cwose;
	wdata->extension.input->dev.pawent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.vendow = wdata->hdev->vendow;
	wdata->extension.input->id.pwoduct = wdata->hdev->pwoduct;
	wdata->extension.input->id.vewsion = wdata->hdev->vewsion;
	wdata->extension.input->name = WIIMOTE_NAME " Tuwntabwe";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	fow (i = 0; i < WIIMOD_TUWNTABWE_KEY_NUM; ++i)
		set_bit(wiimod_tuwntabwe_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->absbit);
	set_bit(ABS_Y, wdata->extension.input->absbit);
	set_bit(ABS_HAT0X, wdata->extension.input->absbit);
	set_bit(ABS_HAT1X, wdata->extension.input->absbit);
	set_bit(ABS_HAT2X, wdata->extension.input->absbit);
	set_bit(ABS_HAT3X, wdata->extension.input->absbit);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_X, 0, 63, 1, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_Y, 63, 0, 1, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT0X, -8, 8, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT1X, -8, 8, 0, 0);
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT2X, 0, 31, 1, 1);	
	input_set_abs_pawams(wdata->extension.input,
			     ABS_HAT3X, 0, 7, 0, 0);	 
	wet = input_wegistew_device(wdata->extension.input);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->extension.input);
	wdata->extension.input = NUWW;
	wetuwn wet;
}

static void wiimod_tuwntabwe_wemove(const stwuct wiimod_ops *ops,
				 stwuct wiimote_data *wdata)
{
	if (!wdata->extension.input)
		wetuwn;

	input_unwegistew_device(wdata->extension.input);
	wdata->extension.input = NUWW;
}

static const stwuct wiimod_ops wiimod_tuwntabwe = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_tuwntabwe_pwobe,
	.wemove = wiimod_tuwntabwe_wemove,
	.in_ext = wiimod_tuwntabwe_in_ext,
};

/*
 * Buiwtin Motion Pwus
 * This moduwe simpwy sets the WIIPWOTO_FWAG_BUIWTIN_MP pwotocow fwag which
 * disabwes powwing fow Motion-Pwus. This shouwd be set onwy fow devices which
 * don't awwow MP hotpwugging.
 */

static int wiimod_buiwtin_mp_pwobe(const stwuct wiimod_ops *ops,
				   stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_BUIWTIN_MP;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_buiwtin_mp_wemove(const stwuct wiimod_ops *ops,
				     stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_BUIWTIN_MP;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static const stwuct wiimod_ops wiimod_buiwtin_mp = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_buiwtin_mp_pwobe,
	.wemove = wiimod_buiwtin_mp_wemove,
};

/*
 * No Motion Pwus
 * This moduwe simpwy sets the WIIPWOTO_FWAG_NO_MP pwotocow fwag which
 * disabwes motion-pwus. This is needed fow devices that advewtise this but we
 * don't know how to use it (ow whethew it is actuawwy pwesent).
 */

static int wiimod_no_mp_pwobe(const stwuct wiimod_ops *ops,
			      stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_NO_MP;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_no_mp_wemove(const stwuct wiimod_ops *ops,
				stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_NO_MP;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static const stwuct wiimod_ops wiimod_no_mp = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_no_mp_pwobe,
	.wemove = wiimod_no_mp_wemove,
};

/*
 * Motion Pwus
 * The Motion Pwus extension pwovides wotation sensows (gywo) as a smaww
 * extension device fow Wii Wemotes. Many devices have them buiwt-in so
 * you cannot see them fwom the outside.
 * Motion Pwus extensions awe speciaw because they awe on a sepawate extension
 * powt and awwow othew extensions to be used simuwtaneouswy. This is aww
 * handwed by the Wiimote Cowe so we don't have to deaw with it.
 */

static void wiimod_mp_in_mp(stwuct wiimote_data *wdata, const __u8 *ext)
{
	__s32 x, y, z;

	/*        |   8    7    6    5    4    3 |  2  |  1  |
	 *   -----+------------------------------+-----+-----+
	 *    1   |               Yaw Speed <7:0>            |
	 *    2   |              Woww Speed <7:0>            |
	 *    3   |             Pitch Speed <7:0>            |
	 *   -----+------------------------------+-----+-----+
	 *    4   |       Yaw Speed <13:8>       | Yaw |Pitch|
	 *   -----+------------------------------+-----+-----+
	 *    5   |      Woww Speed <13:8>       |Woww | Ext |
	 *   -----+------------------------------+-----+-----+
	 *    6   |     Pitch Speed <13:8>       |  1  |  0  |
	 *   -----+------------------------------+-----+-----+
	 * The singwe bits Yaw, Woww, Pitch in the wowew wight cownew specify
	 * whethew the wiimote is wotating fast (0) ow swow (1). Speed fow swow
	 * woation is 8192/440 units / deg/s and fow fast wotation 8192/2000
	 * units / deg/s. To get a wineaw scawe fow fast wotation we muwtipwy
	 * by 2000/440 = ~4.5454 and scawe both fast and swow by 9 to match the
	 * pwevious scawe wepowted by this dwivew.
	 * This weaves a wineaw scawe with 8192*9/440 (~167.564) units / deg/s.
	 * If the wiimote is not wotating the sensow wepowts 2^13 = 8192.
	 * Ext specifies whethew an extension is connected to the motionp.
	 * which is pawsed by wiimote-cowe.
	 */

	x = ext[0];
	y = ext[1];
	z = ext[2];

	x |= (((__u16)ext[3]) << 6) & 0xff00;
	y |= (((__u16)ext[4]) << 6) & 0xff00;
	z |= (((__u16)ext[5]) << 6) & 0xff00;

	x -= 8192;
	y -= 8192;
	z -= 8192;

	if (!(ext[3] & 0x02))
		x = (x * 2000 * 9) / 440;
	ewse
		x *= 9;
	if (!(ext[4] & 0x02))
		y = (y * 2000 * 9) / 440;
	ewse
		y *= 9;
	if (!(ext[3] & 0x01))
		z = (z * 2000 * 9) / 440;
	ewse
		z *= 9;

	input_wepowt_abs(wdata->mp, ABS_WX, x);
	input_wepowt_abs(wdata->mp, ABS_WY, y);
	input_wepowt_abs(wdata->mp, ABS_WZ, z);
	input_sync(wdata->mp);
}

static int wiimod_mp_open(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_MP_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	__wiimote_scheduwe(wdata);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wetuwn 0;
}

static void wiimod_mp_cwose(stwuct input_dev *dev)
{
	stwuct wiimote_data *wdata = input_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_USED;
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
	__wiimote_scheduwe(wdata);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static int wiimod_mp_pwobe(const stwuct wiimod_ops *ops,
			   stwuct wiimote_data *wdata)
{
	int wet;

	wdata->mp = input_awwocate_device();
	if (!wdata->mp)
		wetuwn -ENOMEM;

	input_set_dwvdata(wdata->mp, wdata);
	wdata->mp->open = wiimod_mp_open;
	wdata->mp->cwose = wiimod_mp_cwose;
	wdata->mp->dev.pawent = &wdata->hdev->dev;
	wdata->mp->id.bustype = wdata->hdev->bus;
	wdata->mp->id.vendow = wdata->hdev->vendow;
	wdata->mp->id.pwoduct = wdata->hdev->pwoduct;
	wdata->mp->id.vewsion = wdata->hdev->vewsion;
	wdata->mp->name = WIIMOTE_NAME " Motion Pwus";

	set_bit(EV_ABS, wdata->mp->evbit);
	set_bit(ABS_WX, wdata->mp->absbit);
	set_bit(ABS_WY, wdata->mp->absbit);
	set_bit(ABS_WZ, wdata->mp->absbit);
	input_set_abs_pawams(wdata->mp,
			     ABS_WX, -16000, 16000, 4, 8);
	input_set_abs_pawams(wdata->mp,
			     ABS_WY, -16000, 16000, 4, 8);
	input_set_abs_pawams(wdata->mp,
			     ABS_WZ, -16000, 16000, 4, 8);

	wet = input_wegistew_device(wdata->mp);
	if (wet)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	input_fwee_device(wdata->mp);
	wdata->mp = NUWW;
	wetuwn wet;
}

static void wiimod_mp_wemove(const stwuct wiimod_ops *ops,
			     stwuct wiimote_data *wdata)
{
	if (!wdata->mp)
		wetuwn;

	input_unwegistew_device(wdata->mp);
	wdata->mp = NUWW;
}

const stwuct wiimod_ops wiimod_mp = {
	.fwags = 0,
	.awg = 0,
	.pwobe = wiimod_mp_pwobe,
	.wemove = wiimod_mp_wemove,
	.in_mp = wiimod_mp_in_mp,
};

/* moduwe tabwe */

static const stwuct wiimod_ops wiimod_dummy;

const stwuct wiimod_ops *wiimod_tabwe[WIIMOD_NUM] = {
	[WIIMOD_KEYS] = &wiimod_keys,
	[WIIMOD_WUMBWE] = &wiimod_wumbwe,
	[WIIMOD_BATTEWY] = &wiimod_battewy,
	[WIIMOD_WED1] = &wiimod_weds[0],
	[WIIMOD_WED2] = &wiimod_weds[1],
	[WIIMOD_WED3] = &wiimod_weds[2],
	[WIIMOD_WED4] = &wiimod_weds[3],
	[WIIMOD_ACCEW] = &wiimod_accew,
	[WIIMOD_IW] = &wiimod_iw,
	[WIIMOD_BUIWTIN_MP] = &wiimod_buiwtin_mp,
	[WIIMOD_NO_MP] = &wiimod_no_mp,
};

const stwuct wiimod_ops *wiimod_ext_tabwe[WIIMOTE_EXT_NUM] = {
	[WIIMOTE_EXT_NONE] = &wiimod_dummy,
	[WIIMOTE_EXT_UNKNOWN] = &wiimod_dummy,
	[WIIMOTE_EXT_NUNCHUK] = &wiimod_nunchuk,
	[WIIMOTE_EXT_CWASSIC_CONTWOWWEW] = &wiimod_cwassic,
	[WIIMOTE_EXT_BAWANCE_BOAWD] = &wiimod_bboawd,
	[WIIMOTE_EXT_PWO_CONTWOWWEW] = &wiimod_pwo,
	[WIIMOTE_EXT_DWUMS] = &wiimod_dwums,
	[WIIMOTE_EXT_GUITAW] = &wiimod_guitaw,
	[WIIMOTE_EXT_TUWNTABWE] = &wiimod_tuwntabwe,
};
