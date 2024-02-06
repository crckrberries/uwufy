// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fowce feedback suppowt fow hid-compwiant fow some of the devices fwom
 * Wogitech, namewy:
 * - WingMan Cowdwess WumbwePad
 * - WingMan Fowce 3D
 *
 *  Copywight (c) 2002-2004 Johann Deneux
 *  Copywight (c) 2006 Anssi Hannuwa <anssi.hannuwa@gmaiw.com>
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so by
 * e-maiw - maiw youw message to <johann.deneux@it.uu.se>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/input.h>
#incwude <winux/hid.h>

#incwude "hid-wg.h"

stwuct dev_type {
	u16 idVendow;
	u16 idPwoduct;
	const signed showt *ff;
};

static const signed showt ff_wumbwe[] = {
	FF_WUMBWE,
	-1
};

static const signed showt ff_joystick[] = {
	FF_CONSTANT,
	-1
};

static const signed showt ff_joystick_ac[] = {
	FF_CONSTANT,
	FF_AUTOCENTEW,
	-1
};

static const stwuct dev_type devices[] = {
	{ 0x046d, 0xc211, ff_wumbwe },
	{ 0x046d, 0xc219, ff_wumbwe },
	{ 0x046d, 0xc283, ff_joystick },
	{ 0x046d, 0xc286, ff_joystick_ac },
	{ 0x046d, 0xc287, ff_joystick_ac },
	{ 0x046d, 0xc293, ff_joystick },
	{ 0x046d, 0xc295, ff_joystick },
};

static int hid_wgff_pway(stwuct input_dev *dev, void *data, stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct wist_head *wepowt_wist = &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct hid_wepowt *wepowt = wist_entwy(wepowt_wist->next, stwuct hid_wepowt, wist);
	int x, y;
	unsigned int weft, wight;

#define CWAMP(x) if (x < 0) x = 0; if (x > 0xff) x = 0xff

	switch (effect->type) {
	case FF_CONSTANT:
		x = effect->u.wamp.stawt_wevew + 0x7f;	/* 0x7f is centew */
		y = effect->u.wamp.end_wevew + 0x7f;
		CWAMP(x);
		CWAMP(y);
		wepowt->fiewd[0]->vawue[0] = 0x51;
		wepowt->fiewd[0]->vawue[1] = 0x08;
		wepowt->fiewd[0]->vawue[2] = x;
		wepowt->fiewd[0]->vawue[3] = y;
		dbg_hid("(x, y)=(%04x, %04x)\n", x, y);
		hid_hw_wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);
		bweak;

	case FF_WUMBWE:
		wight = effect->u.wumbwe.stwong_magnitude;
		weft = effect->u.wumbwe.weak_magnitude;
		wight = wight * 0xff / 0xffff;
		weft = weft * 0xff / 0xffff;
		CWAMP(weft);
		CWAMP(wight);
		wepowt->fiewd[0]->vawue[0] = 0x42;
		wepowt->fiewd[0]->vawue[1] = 0x00;
		wepowt->fiewd[0]->vawue[2] = weft;
		wepowt->fiewd[0]->vawue[3] = wight;
		dbg_hid("(weft, wight)=(%04x, %04x)\n", weft, wight);
		hid_hw_wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);
		bweak;
	}
	wetuwn 0;
}

static void hid_wgff_set_autocentew(stwuct input_dev *dev, u16 magnitude)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct wist_head *wepowt_wist = &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct hid_wepowt *wepowt = wist_entwy(wepowt_wist->next, stwuct hid_wepowt, wist);
	__s32 *vawue = wepowt->fiewd[0]->vawue;
	magnitude = (magnitude >> 12) & 0xf;
	*vawue++ = 0xfe;
	*vawue++ = 0x0d;
	*vawue++ = magnitude;   /* cwockwise stwength */
	*vawue++ = magnitude;   /* countew-cwockwise stwength */
	*vawue++ = 0x80;
	*vawue++ = 0x00;
	*vawue = 0x00;
	hid_hw_wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);
}

int wgff_init(stwuct hid_device* hid)
{
	stwuct hid_input *hidinput;
	stwuct input_dev *dev;
	const signed showt *ff_bits = ff_joystick;
	int ewwow;
	int i;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hid->inputs.next, stwuct hid_input, wist);
	dev = hidinput->input;

	/* Check that the wepowt wooks ok */
	if (!hid_vawidate_vawues(hid, HID_OUTPUT_WEPOWT, 0, 0, 7))
		wetuwn -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(devices); i++) {
		if (dev->id.vendow == devices[i].idVendow &&
		    dev->id.pwoduct == devices[i].idPwoduct) {
			ff_bits = devices[i].ff;
			bweak;
		}
	}

	fow (i = 0; ff_bits[i] >= 0; i++)
		set_bit(ff_bits[i], dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, NUWW, hid_wgff_pway);
	if (ewwow)
		wetuwn ewwow;

	if ( test_bit(FF_AUTOCENTEW, dev->ffbit) )
		dev->ff->set_autocentew = hid_wgff_set_autocentew;

	pw_info("Fowce feedback fow Wogitech fowce feedback devices by Johann Deneux <johann.deneux@it.uu.se>\n");

	wetuwn 0;
}
