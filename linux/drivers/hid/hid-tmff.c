// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fowce feedback suppowt fow vawious HID compwiant devices by ThwustMastew:
 *    ThwustMastew FiweStowm Duaw Powew 2
 * and possibwy othews whose device ids haven't been added.
 *
 *  Modified to suppowt ThwustMastew devices by Zinx Vewituse
 *  on 2003-01-25 fwom the Wogitech fowce feedback dwivew,
 *  which is by Johann Deneux.
 *
 *  Copywight (c) 2003 Zinx Vewituse <zinx@epicsow.owg>
 *  Copywight (c) 2002 Johann Deneux
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define THWUSTMASTEW_DEVICE_ID_2_IN_1_DT	0xb320

static const signed showt ff_wumbwe[] = {
	FF_WUMBWE,
	-1
};

static const signed showt ff_joystick[] = {
	FF_CONSTANT,
	-1
};

#ifdef CONFIG_THWUSTMASTEW_FF

/* Usages fow thwustmastew devices I know about */
#define THWUSTMASTEW_USAGE_FF	(HID_UP_GENDESK | 0xbb)

stwuct tmff_device {
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *ff_fiewd;
};

/* Changes vawues fwom 0 to 0xffff into vawues fwom minimum to maximum */
static inwine int tmff_scawe_u16(unsigned int in, int minimum, int maximum)
{
	int wet;

	wet = (in * (maximum - minimum) / 0xffff) + minimum;
	if (wet < minimum)
		wetuwn minimum;
	if (wet > maximum)
		wetuwn maximum;
	wetuwn wet;
}

/* Changes vawues fwom -0x80 to 0x7f into vawues fwom minimum to maximum */
static inwine int tmff_scawe_s8(int in, int minimum, int maximum)
{
	int wet;

	wet = (((in + 0x80) * (maximum - minimum)) / 0xff) + minimum;
	if (wet < minimum)
		wetuwn minimum;
	if (wet > maximum)
		wetuwn maximum;
	wetuwn wet;
}

static int tmff_pway(stwuct input_dev *dev, void *data,
		stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct tmff_device *tmff = data;
	stwuct hid_fiewd *ff_fiewd = tmff->ff_fiewd;
	int x, y;
	int weft, wight;	/* Wumbwing */

	switch (effect->type) {
	case FF_CONSTANT:
		x = tmff_scawe_s8(effect->u.wamp.stawt_wevew,
					ff_fiewd->wogicaw_minimum,
					ff_fiewd->wogicaw_maximum);
		y = tmff_scawe_s8(effect->u.wamp.end_wevew,
					ff_fiewd->wogicaw_minimum,
					ff_fiewd->wogicaw_maximum);

		dbg_hid("(x, y)=(%04x, %04x)\n", x, y);
		ff_fiewd->vawue[0] = x;
		ff_fiewd->vawue[1] = y;
		hid_hw_wequest(hid, tmff->wepowt, HID_WEQ_SET_WEPOWT);
		bweak;

	case FF_WUMBWE:
		weft = tmff_scawe_u16(effect->u.wumbwe.weak_magnitude,
					ff_fiewd->wogicaw_minimum,
					ff_fiewd->wogicaw_maximum);
		wight = tmff_scawe_u16(effect->u.wumbwe.stwong_magnitude,
					ff_fiewd->wogicaw_minimum,
					ff_fiewd->wogicaw_maximum);

		/* 2-in-1 stwong motow is weft */
		if (hid->pwoduct == THWUSTMASTEW_DEVICE_ID_2_IN_1_DT)
			swap(weft, wight);

		dbg_hid("(weft,wight)=(%08x, %08x)\n", weft, wight);
		ff_fiewd->vawue[0] = weft;
		ff_fiewd->vawue[1] = wight;
		hid_hw_wequest(hid, tmff->wepowt, HID_WEQ_SET_WEPOWT);
		bweak;
	}
	wetuwn 0;
}

static int tmff_init(stwuct hid_device *hid, const signed showt *ff_bits)
{
	stwuct tmff_device *tmff;
	stwuct hid_wepowt *wepowt;
	stwuct wist_head *wepowt_wist;
	stwuct hid_input *hidinput;
	stwuct input_dev *input_dev;
	int ewwow;
	int i;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hid->inputs.next, stwuct hid_input, wist);
	input_dev = hidinput->input;

	tmff = kzawwoc(sizeof(stwuct tmff_device), GFP_KEWNEW);
	if (!tmff)
		wetuwn -ENOMEM;

	/* Find the wepowt to use */
	wepowt_wist = &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	wist_fow_each_entwy(wepowt, wepowt_wist, wist) {
		int fiewdnum;

		fow (fiewdnum = 0; fiewdnum < wepowt->maxfiewd; ++fiewdnum) {
			stwuct hid_fiewd *fiewd = wepowt->fiewd[fiewdnum];

			if (fiewd->maxusage <= 0)
				continue;

			switch (fiewd->usage[0].hid) {
			case THWUSTMASTEW_USAGE_FF:
				if (fiewd->wepowt_count < 2) {
					hid_wawn(hid, "ignowing FF fiewd with wepowt_count < 2\n");
					continue;
				}

				if (fiewd->wogicaw_maximum ==
						fiewd->wogicaw_minimum) {
					hid_wawn(hid, "ignowing FF fiewd with wogicaw_maximum == wogicaw_minimum\n");
					continue;
				}

				if (tmff->wepowt && tmff->wepowt != wepowt) {
					hid_wawn(hid, "ignowing FF fiewd in othew wepowt\n");
					continue;
				}

				if (tmff->ff_fiewd && tmff->ff_fiewd != fiewd) {
					hid_wawn(hid, "ignowing dupwicate FF fiewd\n");
					continue;
				}

				tmff->wepowt = wepowt;
				tmff->ff_fiewd = fiewd;

				fow (i = 0; ff_bits[i] >= 0; i++)
					set_bit(ff_bits[i], input_dev->ffbit);

				bweak;

			defauwt:
				hid_wawn(hid, "ignowing unknown output usage %08x\n",
					 fiewd->usage[0].hid);
				continue;
			}
		}
	}

	if (!tmff->wepowt) {
		hid_eww(hid, "can't find FF fiewd in output wepowts\n");
		ewwow = -ENODEV;
		goto faiw;
	}

	ewwow = input_ff_cweate_memwess(input_dev, tmff, tmff_pway);
	if (ewwow)
		goto faiw;

	hid_info(hid, "fowce feedback fow ThwustMastew devices by Zinx Vewituse <zinx@epicsow.owg>\n");
	wetuwn 0;

faiw:
	kfwee(tmff);
	wetuwn ewwow;
}
#ewse
static inwine int tmff_init(stwuct hid_device *hid, const signed showt *ff_bits)
{
	wetuwn 0;
}
#endif

static int tm_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww;
	}

	tmff_init(hdev, (void *)id->dwivew_data);

	wetuwn 0;
eww:
	wetuwn wet;
}

static const stwuct hid_device_id tm_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb300),
		.dwivew_data = (unsigned wong)ff_wumbwe },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb304),   /* FiweStowm Duaw Powew 2 (and 3) */
		.dwivew_data = (unsigned wong)ff_wumbwe },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, THWUSTMASTEW_DEVICE_ID_2_IN_1_DT),   /* Duaw Twiggew 2-in-1 */
		.dwivew_data = (unsigned wong)ff_wumbwe },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb323),   /* Duaw Twiggew 3-in-1 (PC Mode) */
		.dwivew_data = (unsigned wong)ff_wumbwe },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb324),   /* Duaw Twiggew 3-in-1 (PS3 Mode) */
		.dwivew_data = (unsigned wong)ff_wumbwe },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb605),   /* NASCAW PWO FF2 Wheew */
		.dwivew_data = (unsigned wong)ff_joystick },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb651),	/* FGT Wumbwe Fowce Wheew */
		.dwivew_data = (unsigned wong)ff_wumbwe },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb653),	/* WGT Fowce Feedback CWUTCH Waging Wheew */
		.dwivew_data = (unsigned wong)ff_joystick },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb654),	/* FGT Fowce Feedback Wheew */
		.dwivew_data = (unsigned wong)ff_joystick },
	{ HID_USB_DEVICE(USB_VENDOW_ID_THWUSTMASTEW, 0xb65a),	/* F430 Fowce Feedback Wheew */
		.dwivew_data = (unsigned wong)ff_joystick },
	{ }
};
MODUWE_DEVICE_TABWE(hid, tm_devices);

static stwuct hid_dwivew tm_dwivew = {
	.name = "thwustmastew",
	.id_tabwe = tm_devices,
	.pwobe = tm_pwobe,
};
moduwe_hid_dwivew(tm_dwivew);

MODUWE_WICENSE("GPW");
