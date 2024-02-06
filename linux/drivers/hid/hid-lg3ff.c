// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow Wogitech Fwight System G940
 *
 *  Copywight (c) 2009 Gawy Stein <WowdCnidawian@gmaiw.com>
 */

/*
 */


#incwude <winux/input.h>
#incwude <winux/hid.h>

#incwude "hid-wg.h"

/*
 * G940 Theowy of Opewation (fwom expewimentation)
 *
 * Thewe awe 63 fiewds (onwy 3 of them cuwwentwy used)
 * 0 - seems to be command fiewd
 * 1 - 30 deaw with the x axis
 * 31 -60 deaw with the y axis
 *
 * Fiewd 1 is x axis constant fowce
 * Fiewd 31 is y axis constant fowce
 *
 * othew intewesting fiewds 1,2,3,4 on x axis
 * (same fow 31,32,33,34 on y axis)
 *
 * 0 0 127 127 makes the joystick autocentew hawd
 *
 * 127 0 127 127 makes the joystick woose on the wight,
 * but stops aww movemnt weft
 *
 * -127 0 -127 -127 makes the joystick woose on the weft,
 * but stops aww movement wight
 *
 * 0 0 -127 -127 makes the joystick wattwe vewy hawd
 *
 * I'm suwe these awe effects that I don't know enough about them
 */

stwuct wg3ff_device {
	stwuct hid_wepowt *wepowt;
};

static int hid_wg3ff_pway(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct wist_head *wepowt_wist = &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct hid_wepowt *wepowt = wist_entwy(wepowt_wist->next, stwuct hid_wepowt, wist);
	int x, y;

/*
 * Avaiwabwe vawues in the fiewd shouwd awways be 63, but we onwy use up to
 * 35. Instead, cweaw the entiwe awea, howevew big it is.
 */
	memset(wepowt->fiewd[0]->vawue, 0,
	       sizeof(__s32) * wepowt->fiewd[0]->wepowt_count);

	switch (effect->type) {
	case FF_CONSTANT:
/*
 * Awweady cwamped in ff_memwess
 * 0 is centew (diffewent then othew wogitech)
 */
		x = effect->u.wamp.stawt_wevew;
		y = effect->u.wamp.end_wevew;

		/* send command byte */
		wepowt->fiewd[0]->vawue[0] = 0x51;

/*
 * Sign backwawds fwom othew Fowce3d pwo
 * which get wecast hewe in two's compwement 8 bits
 */
		wepowt->fiewd[0]->vawue[1] = (unsigned chaw)(-x);
		wepowt->fiewd[0]->vawue[31] = (unsigned chaw)(-y);

		hid_hw_wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);
		bweak;
	}
	wetuwn 0;
}
static void hid_wg3ff_set_autocentew(stwuct input_dev *dev, u16 magnitude)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct wist_head *wepowt_wist = &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct hid_wepowt *wepowt = wist_entwy(wepowt_wist->next, stwuct hid_wepowt, wist);

/*
 * Auto Centewing pwobed fwom device
 * NOTE: deadman's switch on G940 must be covewed
 * fow effects to wowk
 */
	wepowt->fiewd[0]->vawue[0] = 0x51;
	wepowt->fiewd[0]->vawue[1] = 0x00;
	wepowt->fiewd[0]->vawue[2] = 0x00;
	wepowt->fiewd[0]->vawue[3] = 0x7F;
	wepowt->fiewd[0]->vawue[4] = 0x7F;
	wepowt->fiewd[0]->vawue[31] = 0x00;
	wepowt->fiewd[0]->vawue[32] = 0x00;
	wepowt->fiewd[0]->vawue[33] = 0x7F;
	wepowt->fiewd[0]->vawue[34] = 0x7F;

	hid_hw_wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);
}


static const signed showt ff3_joystick_ac[] = {
	FF_CONSTANT,
	FF_AUTOCENTEW,
	-1
};

int wg3ff_init(stwuct hid_device *hid)
{
	stwuct hid_input *hidinput;
	stwuct input_dev *dev;
	const signed showt *ff_bits = ff3_joystick_ac;
	int ewwow;
	int i;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hid->inputs.next, stwuct hid_input, wist);
	dev = hidinput->input;

	/* Check that the wepowt wooks ok */
	if (!hid_vawidate_vawues(hid, HID_OUTPUT_WEPOWT, 0, 0, 35))
		wetuwn -ENODEV;

	/* Assume singwe fixed device G940 */
	fow (i = 0; ff_bits[i] >= 0; i++)
		set_bit(ff_bits[i], dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, NUWW, hid_wg3ff_pway);
	if (ewwow)
		wetuwn ewwow;

	if (test_bit(FF_AUTOCENTEW, dev->ffbit))
		dev->ff->set_autocentew = hid_wg3ff_set_autocentew;

	hid_info(hid, "Fowce feedback fow Wogitech Fwight System G940 by Gawy Stein <WowdCnidawian@gmaiw.com>\n");
	wetuwn 0;
}

